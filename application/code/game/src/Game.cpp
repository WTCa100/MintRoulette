#include <ctime>
#include <limits.h>
#include <fstream>
#include <algorithm>

// Get header
#include "../include/Game.h"
#include "../include/Turn.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"
#include "../../utilities/include/Paths.h"


// Get source
#include "./Turn.cpp"
#include "../src/Player.cpp"

/// @brief Sets up information about number of players and initial bank account
void Game::setGameConfig()
{
    std::string userInput = "";
    bool isInputGood = false;
    // Ask for player count info
    {
        std::cout << "How many players will play (max 8)\n";
        do
        {
            std::getline(std::cin, userInput);
            if(ValidateInput::isStringNumber(userInput))
            {
                if(std::stoi(userInput) <= MAX_PLAYERS_PER_SESSION && std::stoi(userInput) > 1)
                {
                    isInputGood = true;
                }
                else
                {
                    std::cout << "Max player count is 8, and there must be at least two players\n";
                }
            }
            else
            {
                std::cout << "Input must be a numeric value!\n";
            }
        } while (!isInputGood);
        // Everything in order we can set config count
        setPlayerCount(std::stoi(userInput));
    }
    // Ask for player initial bank balance info
    {
        isInputGood = false;
        userInput.clear();
        std::cout << "What will be the initial bank balance?\n";
        do
        {
            std::getline(std::cin, userInput);
            if(ValidateInput::isStringNumber(userInput))
            {
                if(std::stoi(userInput) <= INT_MAX / 4 && std::stoi(userInput) >= 100)
                {
                    isInputGood = true;
                }   
                else
                {
                    std::cout << "Value cannot be greater than " << INT_MAX / 4 
                              << " and cannot be lower than 100!" << std::endl; 
                }
            }
            else
            {
                std::cout << "Input must be a numeric value!\n";
            }
        } while (!isInputGood);
        setInitialBankBalance(std::stoi(userInput));
    }

    gameLog_->addLog(
        gameLog_->logInitialGameConfig(1, numberOfPlayers_, initBankBalance_)
    );

}

/// @brief  Checks if player is a returning one or not
/// @param name player nickname used as filename
/// @return if file nammed [playerNickname].pl exists
bool Game::checkIfPlayerExists(const std::string& name) const
{
    return fManager_->isFileGood(FILE_PLAYER_STATS_PATH, name + EXT_PLAYER_STATS);
}

/// @brief Core gameplay - create player instances, assign them nicknames, and play
void Game::startGame()
{
    std::cout << "WIP!\n";
    std::cout << "Player count: " << numberOfPlayers_ << std::endl;
    std::cout << "Init balance: " << initBankBalance_ << std::endl;

    // ask for names
    for(int i = 0; i < numberOfPlayers_; i++)
    {
        std::string tmpNicknameHolder = "";
        Player* roulettePlayer;
        std::cout << "Please provide name for player " << i + 1 << std::endl;
        do
        {
            do
            {
                std::getline(std::cin, tmpNicknameHolder);
                if(tmpNicknameHolder.empty())
                {
                    std::cout << "Player must have a name!\n";
                }
            } while (tmpNicknameHolder.size() < MIN_NICKNAME_LENGTH || tmpNicknameHolder.size() > MAX_NICKNAME_LENGTH);
            if(ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder))
            {
                std::cout << "2 Players cannot have the same nickname!\n";
            }
        } while (ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder));

        // Check if player is returning one or not
        if(checkIfPlayerExists(tmpNicknameHolder))
        {
            roulettePlayer = fManager_->makePlayerFromLoadedFile(tmpNicknameHolder, i + 1, initBankBalance_);
        }
        else
        {
            roulettePlayer = new Player(initBankBalance_, i + 1);
            roulettePlayer->setNickName(tmpNicknameHolder);
        }
        players_.push_back(roulettePlayer);

        gameLog_->addLog(
            gameLog_->logGamePlayerCreation(roulettePlayer->getNickName(), roulettePlayer->getPlayerOrderNumber())
        );

    }
    playersAlive_ = players_;
    std::cout <<"there are " << playersAlive_.size() << " players\n";
    for(auto i : players_)
    {
        std::cout << "Player nick: " << i->getNickName() << std::endl;
    }

    // Start turns
    std::cout << "Debug info: Start of turns\n";
    bool canGameProgress = true;
    uint16_t turnId = 0;
    while(canGameProgress)
    {
        turnId ++;
        bool stopGameEarly = false;
        Turn* currentTurn = new Turn(playersAlive_, turnId, gameLog_);
        currentTurn->playTurn();
        gameTurns_.push_back(currentTurn);
        playersAndBetsSave_.push_back(currentTurn->getPlayersBets());
        eliminatePlayers();

        // Check if players want to continue
        if(playersAlive_.size() > 1)
        {
            stopGameEarly = askForStopGameEarly(stopGameEarly);
        }
        canGameProgress = checkGameCondition(stopGameEarly);

        gameLog_->buildLogs();
    }
}

/// @brief removes player from playersAlive_ and assigns it to playersEliminated_
/// @note Player is eliminated when his balance reaches zero
void Game::eliminatePlayers()
{
    for(auto& checkPlayer : playersAlive_)
    {
        if(checkPlayer->getBalance() == 0)
        {
            std::cout << "Player: " << checkPlayer->getNickName() << " got eliminated!\n";
            playersEliminated_.push_back(checkPlayer);

            gameLog_->addLog(
                gameLog_->logGamePlayerElimination(checkPlayer->getNickName())
            );

        }
    }
    for(auto& killPlayer : playersEliminated_)
    {
        playersAlive_.erase(std::remove(playersAlive_.begin(), playersAlive_.end(), killPlayer), playersAlive_.end());
    }
}

/// @brief Check if user inputed 'y' or 'n'
/// @param userInput 
/// @return if user input has it's first value of 'y' or 'n'
bool Game::isStringValid(const std::string& userInput)
{
    return (tolower(userInput[0]) == 'y' ||
            tolower(userInput[0]) == 'n');
}

/// @brief Prompt players if they want to still playing
/// @param stopEarly game loop boolean value
/// @return if players wants to stop early
bool Game::askForStopGameEarly(bool& stopEarly)
{
    std::string userInput = "";
    std::cout << "Do you wish to proccede? y/n\n";
    do
    {
        std::getline(std::cin, userInput);
        if(!this->isStringValid(userInput))
        {
            std::cout << "It's either yes or no\n";
        }
    } while (!this->isStringValid(userInput));

    if(tolower(userInput[0]) == 'y')
    {
        return false;
    }
    return true;
}

/// @brief Checks if game is eligable for further progression
/// @param canGameProgress
/// @todo Ask if player wants to continue games
/// @return 1: can progress 0: cannot progress
bool Game::checkGameCondition(const bool& stopEarly)
{
    if(playersAlive_.size() <= 1)
    {
        return false;
    }
    if(stopEarly)
    {
        return false;
    }
    return true;
}

/// @brief Summerizes game progress. Display how much money player lost and how many bets and passes they have placed
void Game::endScreen()
{

    gameLog_->addLog(
        gameLog_->logGameHasEnded()
    );

    std::cout << "Game summary\n";
    for(auto& players : players_)
    {
        players->displayMoneyWonLoss();
        players->displayBetPassCounts();
        players->moveToGlobalStats();

        gameLog_->addLog(
            gameLog_->logGamePlayerSummerizeGame(players)
        );

    }
}

/// @brief Defult constructor
Game::Game(const FileManager* fManager)
{
    // For checking and manipulating files
    fManager_ = new FileManager;

    // For creating logs
    gameLog_ = new Logger(fManager_);
    // Dummy value for now
    gameLog_->touchLog(1);

    // For proper setup
    setGameConfig();
}

/// @brief Deconstructs the game with it's content
Game::~Game()
{
    // Summarize game
    endScreen();

    // Save game logs
    gameLog_->buildLogs();
    
    // Save player progress
     for(auto i = 0; i < players_.size(); i++)
    {
        std::cout << "Debug Info: Player: Save: " << i + 1 << std::endl;
        savePlayerStats(*players_[i]);
    }   
    std::cout << "Teardown game\n";
    std::cout << "Debug: Info: Players: Alive: Clear\n";
    playersAlive_.clear(); 
    std::cout << "Debug: Info: Players: Elimineted: Clear\n";
    playersEliminated_.clear(); 

    // Delete bets
    for(auto turn = 0; turn < playersAndBetsSave_.size(); turn++)
    {
        std::cout << "Turn: " << turn << std::endl;
        // Itarate throught the map and delete it's second argument
        for(auto& pAndB : playersAndBetsSave_[turn])
        {
            std::cout << "Debug: Deleting bet for " << pAndB.first->getNickName() << std::endl;
            std::cout << "Debug: Bet info: Type:" << pAndB.second->getBetType() << std::endl;
            std::cout << "Debug: Bet info: Value: " << pAndB.second->getAmmountBetted() << std::endl;
            delete pAndB.second;
        }
    }
    
    // Delete turn info
    for(auto i = 0; i < gameTurns_.size(); i++)
    {
        std::cout << "Debug Info: Delete turn " << i << std::endl;
        delete gameTurns_[i];
    }
    
    // Delete player info
    for(auto i = 0; i < players_.size(); i++)
    {
        std::cout << "Debug Info: Delete player " << i + 1 << std::endl;
        delete players_[i];
    }

    delete gameLog_;
}

/// @brief Saves player statistis into a file with .pl extension.
/// @note This function appends player's global stats.
/// @param savePlayer which player instance to save
void Game::savePlayerStats(const Player& savePlayer)
{
    if(!fManager_->isFileGood(FILE_PLAYER_STATS_PATH, savePlayer.getNickName() + EXT_PLAYER_STATS))
    {
        std::cout << "No save found!\n";
        fManager_->touch(FileType::PlayerStat, savePlayer.getNickName() + EXT_PLAYER_STATS);
    }
    fManager_->appendPlayerSaveFile(savePlayer);
}

uint16_t Game::loadNextGameId()
{
    // Find init.cfg
    {
    if (fManager_->isFileGood(INIT_CONFIG_PATH, INIT_CONFIG_PATH))
    {
        std::string path = INIT_CONFIG_PATH;
        std::ifstream initFile;
        initFile.open(path + "/" + INIT_CONFIG_FILE);
        std::string configLine;
        while(std::getline(initFile, configLine))
        {
            if(configLine.find("NextGameNumber") != std::string::npos)
            {
                configLine.erase(configLine.begin(), configLine.begin() + configLine.rfind(":"));
            }
        }
    }
    }
    // Check if there are any save files.

}