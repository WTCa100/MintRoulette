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
#include "../../utilities/src/DebugLogger.cpp"

/// @brief Sets up information about number of players and initial bank account
void Game::setGameConfig()
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameSetupConfig}
    );

    dbgLog_->buildDebugLogs();
    
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

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameGetInput,
                 dbgLog_->dbLogGameGetInputCheck(userInput, isInputGood)}
            );

            dbgLog_->buildDebugLogs();

        } while (!isInputGood);
        // Everything in order we can set config count

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGamePlayerCountSet(std::stoi(userInput))}
        );
        dbgLog_->buildDebugLogs();

        setPlayerCount(std::stoi(userInput));
    }
    // Allow bots
    {
        std::cout << "Would you like Ai companions? (y/n)\n";
        do
        {
            std::getline(std::cin, userInput);
            if(!this->isStringValid(userInput))
            {
                std::cout << "It's either yes or no\n";
            } 

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameGetInput,
                 dbgLog_->dbLogGameGetInputCheck(userInput, this->isStringValid(userInput))}
            );            
           
        } while (!this->isStringValid(userInput));

        if(tolower(userInput[0]) == 'y')
        {
            hasBots_ = true;
        }   

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameCheckForBots(hasBots_)}
        );

        dbgLog_->buildDebugLogs();

    }
    // Setup bots if necessery
    {
        if(hasBots_)
        {
            std::cout << "How many human players will be playing?\n";
            do
            {
                do
                {
                    std::getline(std::cin, userInput);

                    dbgLog_->addDebugLog(
                        {dbgLog_->dbLogGameGetInput,
                         dbgLog_->dbLogGameGetInputCheck(userInput, ValidateInput::isStringNumber(userInput))}
                    );

                    dbgLog_->buildDebugLogs();

                    if(!ValidateInput::isStringNumber(userInput))
                    {
                        std::cout << "Please enter a numeric value\n";
                    }
                } while (!ValidateInput::isStringNumber(userInput));

                if(std::stoi(userInput) == 0)
                {
                    std::cout << "It's AI only match!\n";
                }
                else if(std::stoi(userInput) > numberOfPlayers_)
                {
                    std::cout << "There cannot be more players than perviosly declared!\n";
                }
                else if(std::stoi(userInput) == numberOfPlayers_)
                {
                    std::cout << "No space for bots, removing.\n";
                    hasBots_ = false;

                }

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameGetInput,
                     dbgLog_->dbLogGameGetInputCheck(userInput, std::stoi(userInput) < 0 || std::stoi(userInput) > numberOfPlayers_)}
                );

                dbgLog_->buildDebugLogs();

        } while (std::stoi(userInput) < 0 || std::stoi(userInput) > numberOfPlayers_);
        
            numOfBots_ = numberOfPlayers_ - std::stoi(userInput);

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameSetBotCount(numOfBots_)}
            );

            dbgLog_->buildDebugLogs();

        }
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


            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameGetInput,
                 dbgLog_->dbLogGameGetInputCheck(userInput, ValidateInput::isStringNumber(userInput))}
            );

            dbgLog_->buildDebugLogs();

        } while (!isInputGood);
        setInitialBankBalance(std::stoi(userInput));
    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameSetBankBalance(std::stoi(userInput)),
         dbgLog_->dbLogLoggerGetMessage(gameLog_->logInitialGameConfig(1, numberOfPlayers_, initBankBalance_))}
    );

    dbgLog_->buildDebugLogs();

    gameLog_->addLog(
        gameLog_->logInitialGameConfig(1, numberOfPlayers_, initBankBalance_)
    );

}

/// @brief  Checks if player is a returning one or not
/// @param name player nickname used as filename
/// @return if file nammed [playerNickname].pl exists
bool Game::checkIfPlayerExists(const std::string& name) const
{   
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameCheckIfPlayerExists(name)}
    );

    dbgLog_->buildDebugLogs();

    return fManager_->isFileGood(FILE_PLAYER_STATS_PATH, name + EXT_PLAYER_STATS);
}

bool Game::isPlayerNameGood(const std::string& name) const
{
    if(name.empty() || (name.size() < MIN_NICKNAME_LENGTH || name.size() > MAX_NICKNAME_LENGTH))
    {
        return false;
    }

    for(auto letter : name)
    {
        if(letter == '\\' || letter == '/' || letter == ':' || letter == '*' || letter == '?' || letter == '\"' || letter == '<' || letter == '>' || letter == '|' )
        {
            return false;
        }
    }

    return true;
}

/// @brief Core gameplay - create player instances, assign them nicknames, and play
void Game::startGame()
{
    std::cout << "Player count: " << numberOfPlayers_ << std::endl;
    std::cout << "Init balance: " << initBankBalance_ << std::endl;

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameStartOfTheGame(gameId_)}
    );


    bool isThisPlayerBot = false;

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameSetPlayerNameSection}
    );

    dbgLog_->buildDebugLogs();
    // ask for names
    for(int i = 0; i < numberOfPlayers_; i++)
    {
        // Check if there will be a bot setup.
        if(i == numberOfPlayers_ - numOfBots_)
        {
            isThisPlayerBot = true;
        }
        
        Player* roulettePlayer;

        if(!isThisPlayerBot)
        {
            std::string tmpNicknameHolder = "";
            std::cout << "Please provide name for player " << i + 1 << std::endl;
            do
            {
                do
                {
                    std::getline(std::cin, tmpNicknameHolder);
                    if(!isPlayerNameGood(tmpNicknameHolder))
                    {
                        std::cout << "Player must have a name, and cannot contain < > | : \\ / \" * = sings and be no shorer than " << MIN_NICKNAME_LENGTH << std::endl;
                    }

                    dbgLog_->addDebugLog(
                        {dbgLog_->dbLogGameGetInput,
                         dbgLog_->dbLogGameGetInputCheck(tmpNicknameHolder, isPlayerNameGood(tmpNicknameHolder))}
                    );         

                    dbgLog_->buildDebugLogs();           

                } while (!isPlayerNameGood(tmpNicknameHolder));
                if(ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder))
                {
                    std::cout << "2 Players cannot have the same nickname!\n";
                }

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameGetInput,
                     dbgLog_->dbLogGameGetInputCheck(tmpNicknameHolder, ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder))}
                );         

                dbgLog_->buildDebugLogs();     

            } while (ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder));

            // Check if player is returning one or not
            bool ifPlayerExists = checkIfPlayerExists(tmpNicknameHolder);

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameIfPlayerExists(tmpNicknameHolder, ifPlayerExists)}
            );

            dbgLog_->buildDebugLogs();

            if(ifPlayerExists)
            {
                roulettePlayer = fManager_->makePlayerFromLoadedFile(tmpNicknameHolder, i + 1, initBankBalance_);
            }
            else
            {
                roulettePlayer = new Player(initBankBalance_, i + 1, dbgLog_, isThisPlayerBot);
                roulettePlayer->setNickName(tmpNicknameHolder);

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogPlayerSetNickname(tmpNicknameHolder)}
                );

            }

        }
        else
        {
            roulettePlayer = new Player(initBankBalance_, i + 1, dbgLog_, isThisPlayerBot);
            std::string* randomlyPickedName = new std::string; 
            do
            {
                *randomlyPickedName = Ai::pickBotName(fManager_);
                roulettePlayer->setNickName(*randomlyPickedName);


            }while(ValidateInput::isADuplicatePlayer(players_, *randomlyPickedName));
            
            dbgLog_->addDebugLog(
                {dbgLog_->dbLogPlayerSetNickname(*randomlyPickedName)}
            );

            delete randomlyPickedName;
        }
        players_.push_back(roulettePlayer);

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGamePushPlayers(roulettePlayer->getNickName(), players_.size()),
             dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerCreation(roulettePlayer->getNickName(), roulettePlayer->getPlayerOrderNumber()))}
        );

        gameLog_->addLog(
            gameLog_->logGamePlayerCreation(roulettePlayer->getNickName(), roulettePlayer->getPlayerOrderNumber())
        );

    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameSetPlayerAliveVector}
    );

    dbgLog_->buildDebugLogs();
    playersAlive_ = players_;

    // Start turns
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameFlowStarts}
    );

    dbgLog_->buildDebugLogs();
    
    bool canGameProgress = true;
    uint16_t turnId = 0;
    while(canGameProgress)
    {
        turnId ++;
        bool stopGameEarly = false;
        Turn* currentTurn = new Turn(playersAlive_, turnId, gameLog_, dbgLog_);
        currentTurn->playTurn();
        gameTurns_.push_back(currentTurn);
        playersAndBetsSave_.push_back(currentTurn->getPlayersBets());

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGamePushTurn(gameTurns_.size()),
             dbgLog_->dbLogGameInsertBetsAndPlayer(playersAndBetsSave_.size())}
        );

        dbgLog_->buildDebugLogs();

        eliminatePlayers();

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameCheckConditionsIfEndEarly(playersAlive_.size() <= 1)}
        );

        // Check if players want to continue
        if(playersAlive_.size() > 1)
        {
            stopGameEarly = askForStopGameEarly(stopGameEarly);

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameCheckConditionsIfEndEarly(stopGameEarly)}
            );

        }
        canGameProgress = checkGameCondition(stopGameEarly);

        dbgLog_->buildDebugLogs();
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

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGamePushPlayersEliminated(checkPlayer->getNickName(), playersEliminated_.size()),
                 dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerElimination(checkPlayer->getNickName()))}
            );

            gameLog_->addLog(
                gameLog_->logGamePlayerElimination(checkPlayer->getNickName())
            );


        }
    }
    for(auto& killPlayer : playersEliminated_)
    {
        playersAlive_.erase(std::remove(playersAlive_.begin(), playersAlive_.end(), killPlayer), playersAlive_.end());

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameEraseEliminatedPlayers(killPlayer->getNickName(), playersAlive_.size())}
        );

    }

    dbgLog_->buildDebugLogs();

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

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameGetInput}
    );

    std::string userInput = "";
    std::cout << "Do you wish to proccede? y/n\n";
    do
    {
        std::getline(std::cin, userInput);
        if(!this->isStringValid(userInput))
        {
            std::cout << "It's either yes or no\n";

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameGetInputCheck(userInput, this->isStringValid(userInput))}
            );
        }

        dbgLog_->buildDebugLogs();

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

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameFlowEndsSummary,
         dbgLog_->dbLogLoggerGetMessage(gameLog_->logGameHasEnded())}
    );

    gameLog_->addLog(
        gameLog_->logGameHasEnded()
    );

    std::cout << "Game summary\n";
    for(auto& players : players_)
    {
        players->displayMoneyWonLoss(initBankBalance_);
        players->displayBetPassCounts();
        if(!players->getPlayerIsBot())
        {
            players->moveToGlobalStats();
        }

        gameLog_->addLog(
            gameLog_->logGamePlayerSummerizeGame(players)
        );

    }

    std::cout << "Press any key to continue...\n";
    std::cin.ignore();
}

/// @brief Defult constructor
Game::Game(DebugLogger* dbLog, const FileManager* fManager)
{
    dbgLog_ = dbLog;
    dbgLog_->addDebugLog(
        {dbLog->dbLogClassGameInitialize}
    );

    dbgLog_->buildDebugLogs();
    // For checking and manipulating files
    fManager_ = new FileManager(dbgLog_);

    // For creating logs
    gameLog_ = new Logger;
    // Dummy value for now


    gameId_ = loadNextGameId();

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameGetGameId,
         dbgLog_->dbLogGameGetGameIdObtained(gameId_)}
    );

    dbgLog_->buildDebugLogs();

    gameLog_->touchLog(gameId_);
    highscores_ = fManager_->loadHighscores();

    hasBots_ = false;
    inProgress_ = false;
    // For proper setup
    setGameConfig();
}

/// @brief Deconstructs the game with it's content
Game::~Game()
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassGameDestruct}
    );

    dbgLog_->buildDebugLogs();
    // Summarize game
    endScreen();

    // Save game logs
    gameLog_->buildLogs();
    
    // Save player progress

    std::cout << "Saving game..."  << std::endl;

     for(auto i = 0; i < players_.size(); i++)
    {
        if(!players_[i]->getPlayerIsBot())
        {
            savePlayerStats(*players_[i]);
        }
    }   

    std::cout << "Saved!\n";

    Game::updateHighscores();
    
    dbgLog_->addDebugLog({"Teardown game"});
    playersAlive_.clear(); 
    playersEliminated_.clear(); 

    // Delete bets
    for(auto turn = 0; turn < playersAndBetsSave_.size(); turn++)
    {
        dbgLog_->addDebugLog({"Bets from turn: " + std::to_string(turn)});
        // Itarate throught the map and delete it's second argument
        for(auto& pAndB : playersAndBetsSave_[turn])
        {
            dbgLog_->addDebugLog({"Delete bet from " + pAndB.first->getNickName() + " of size " + std::to_string(pAndB.second->getAmmountBetted())});
            delete pAndB.second;
        }
    }
    
    // Delete turn info
    for(auto i = 0; i < gameTurns_.size(); i++)
    {
        dbgLog_->addDebugLog({"Delete turn: " + std::to_string(gameTurns_[i]->getTurnNumber())});
        delete gameTurns_[i];
    }
    
    // Delete player info
    for(auto i = 0; i < players_.size(); i++)
    {
        dbgLog_->addDebugLog({"Delete player: " + players_[i]->getNickName()});
        delete players_[i];
    }

    fManager_->iterateGameIdConfig(fManager_->nextGameSaveId());
    
    dbgLog_->addDebugLog({"Finalized teardown"});
    dbgLog_->buildDebugLogs();
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
    if (fManager_->isFileGood(INIT_CONFIG_PATH, INIT_CONFIG_FILE))
    {   
        std::string path = INIT_CONFIG_PATH;
        std::vector<std::string> configFileContent = fManager_->loadFileContent(INIT_CONFIG_PATH, INIT_CONFIG_FILE);
        for(auto line : configFileContent)
        {
            if(line.find("NextGameNumber") != std::string::npos)
            {
                line.erase(line.begin(), line.begin() + line.rfind(":") + 1);
                return std::stoi(line);
            }
        }
    }
    // If nothing found check game folder for any game registered
    else
    {
        std::vector<std::string> gameFiles = fManager_->loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);
        
        // Make sure that there are no folders inside the container
        for(auto checkFolder : gameFiles)
        {
            if(fManager_->isEntryFolder(checkFolder))
            {
                gameFiles.erase(std::remove(gameFiles.begin(), gameFiles.end(), checkFolder), gameFiles.end());
            }
        }

        if(!gameFiles.empty())
        {
            // If there are any entries we need to get a specific numbers and save them to a vector
            std::vector<uint16_t> gameIds;


            for(auto gFile : gameFiles)
            {
                // Check if entry is a folder
                if(fManager_->isEntryFolder(gFile))
                {
                    continue;
                }
                std::string numberText = fManager_->trimPath(gFile);
                numberText.erase(numberText.begin(), numberText.begin() + 6);
                gameIds.push_back(std::stoi(numberText));
            }
            gameFiles.clear();
            return *std::max_element(std::begin(gameIds), std::end(gameIds)) + 1;
        }
        // if none has been found return 1
        else 
        {
            return 1;
        }
    }

    // In case something is missing return 1
    return 1;

}

void Game::updateHighscores()
{  
    std::vector<std::pair<double, std::string>> fullPlayerList = highscores_;

    //std::sort(players_.begin(), players_.end());

    // Add every player from session to the list
    for(auto sessionPlayer : players_)
    {
        // Avoid adding bots
        if(!sessionPlayer->getPlayerIsBot())
        {
            fullPlayerList.push_back(std::make_pair<double, std::string>(sessionPlayer->getGlobalGoodBetRatio(), sessionPlayer->getNickName()));
        }
    }

    // Sort ascending
    std::sort(fullPlayerList.begin(), fullPlayerList.end());
    fullPlayerList.erase(std::unique(fullPlayerList.begin(), fullPlayerList.end()), fullPlayerList.end());
    // Remove duplicates
    for(int playerPos = 0; playerPos < fullPlayerList.size(); playerPos++)
    {
        for(int checkPlayerPos = 0; checkPlayerPos < fullPlayerList.size(); checkPlayerPos++)
        {
            if(fullPlayerList[playerPos].second == fullPlayerList[checkPlayerPos].second)
            {
                if(fullPlayerList[playerPos].first < fullPlayerList[checkPlayerPos].first)
                {
                    fullPlayerList.erase(fullPlayerList.begin() + playerPos);
                }
                else if(fullPlayerList[playerPos].first > fullPlayerList[checkPlayerPos].first)
                {
                    fullPlayerList.erase(fullPlayerList.begin() + checkPlayerPos);
                }
                else
                {
                    continue;
                }
            }
        }
    }

    // Make vector descending
    std::reverse(fullPlayerList.begin(), fullPlayerList.end());

    // Remove entries past 10
    while(fullPlayerList.size() > 10)
    {
        fullPlayerList.pop_back();
    }

    // Update file content
    fManager_->updateHighscores(fullPlayerList);

}

