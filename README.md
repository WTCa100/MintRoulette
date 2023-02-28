# MintRoulette
Basic game written in C++ - the idea is rather simple, simulate roulette game.

### Compiling
MintRoulette uses `std::experimental::filesystem`, which requires an additional tag if you want to compile it. 
While using g++ please include `-lstdc++fs` as an additional tag for the compiler. 

## Initial Launch
This game was designed to work only on Windows. It uses cmdlet commands in order to create a initial setup (we are talking mostly about `mkdir`). That being said, it is necessery to launch the binary `*.exe` file one shall launch it giving administration persmissions. 

## Gameplay
Welcome Internet user! 
This is `MintRoulette`, the third bigger project on my GitHub nammed after one of my cats `Mint`. As the previolsy briefed description said, the game is plainly about playing a roulette with three betting options. Let me guide you through its core features.

### Init config
The player is promped to setup the gamming participants and initial bank balance that all of the players have. The user may or may not decide that along with real human players bots should acompany them. After the player provides his desired nickname to be placed in a `Player` instance, then the program will try to locate stat file of that specific player (stats file are saved as `Nickname.pl`)
```C++
  if(checkIfPlayerExists(tmpNicknameHolder))
  {
      roulettePlayer = fManager_->makePlayerFromLoadedFile(tmpNicknameHolder, i + 1, initBankBalance_);
  }
  else
  {
      roulettePlayer = new Player(initBankBalance_, i + 1, isThisPlayerBot);
      roulettePlayer->setNickName(tmpNicknameHolder);
  }
```
Additonally user may begin an AI only match when number of people is equal to 0.

### Gameflow
Everytime a game is created it gets a new unique game Id that is based on what number there is on `nextGameId:` inside `init.cfg` file.
```C++
// In Game::Game(const FileManager* fManager) constructor
gameId_ = loadNextGameId();
```
Each game consists of `Turn`, and its functionality can be devided into 3 stages, each serving different purpose:
- `Betting` - Here human players are building bets or plainly passing their turn with no bet. On the other hand, when it comes bots, they use a separate place to build their bets, because their actions are based on randomly generated numbers.
- `Rolling` - The roullet is set to roll
  Roulette will display 3 random numbers and only one of them is going to be picked as the lucky one.
  ```C++
      std::vector<uint16_t> numbers(3, 0);
    for(auto &i : numbers)
    {
        i = randomizeNumber();
    }
    size_t luckyNumPos = rand() % numbers.size();
    setLuckyNumber(numbers[luckyNumPos]);
   ```
- `Summarizing` - Display information who won, who won and ammount of money lost/won, and teardown, since `Turn` instances are also operates with pointers.
At the very end during the game teardown, the Id is being iterated to the next highest possible number.
```C++
// In Game::~Game()
fManager_->iterateGameIdConfig(fManager_->nextGameSaveId());
```
### AI
While configuring the game, you are allowed to create bots, instead of playing with real life friends. These bots are rather simple machines since, they are operating on a predictible pattern based on randomly generated number `actionSeed`. Bots only take to account it's balance while making certain actions, the more money they have the more `"braver"` (if you can call it bravery of course!). 
## Saving system
### Logs
Logs are basic game save that is later on display inside the `Menu` class. It contains every event that had occured during every `Turn` and it is saved as `GameNrX.gm` (where `X` is a unique game Id).
In order to maintain clean structure every log file is saved in `bin/saves/` folder which is always created during the inital game launch.
To log a game a class `Logger` with it's instance is called where it can call `touchLog` to create logs, `addLog` to add a message, `buildLogs` to output all logs to a file. Funcionality `buildLogs` and `addLog` are simple vector and ofstream actions. `touchLog` is a bit different:
```C++
void Logger::touchLog(const uint32_t& gameNumber)
{
    std::string logsPath = FILE_GAME_SAVE_LOG_PATH;
    std::string logFileExt = EXT_GAME_LOG;
    logFileName_ = "GameNr" + std::to_string(gameNumber) + logFileExt;
    fManager_->touch(FileType::GameSave, std::to_string(gameNumber));
    logFile_.open(logsPath + "/" + logFileName_,
                  std::ios::out);
   // Skipping error handle

}
```
### Stats
Every bet, ammount won/lost ect. are registered in non-bot `Player` instances, and then saved in a `bin/player/stats` with `playerNickname.pl` as it's file name. These values are being appended or created (depending on the need) while a new `Player` instance will get it's nickname or if the `Game` has concluded and teardown is being processed. 
- Teardown
```C++
// In Game::~Game()
// Save player progress
     for(auto i = 0; i < players_.size(); i++)
    {
        std::cout << "Debug Info: Player: Save: " << i + 1 << std::endl;
        if(!players_[i]->getPlayerIsBot())
        {
            savePlayerStats(*players_[i]);
        }
        else
        {
            // Skipping debug messages
        }
    }   
```
- init
```C++
// In void Game::startGame()

  // Skipping unreleated entries
  for(int i = 0; i < numberOfPlayers_; i++)
  {
    // Skipping unreleated entries
    Player* roulettePlayer;
    if(!isThisPlayerBot)
    {
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
          roulettePlayer = new Player(initBankBalance_, i + 1, isThisPlayerBot);
          roulettePlayer->setNickName(tmpNicknameHolder);
      }
      // Skipping unrelated entries
    }
  }

```
<!-- TODO: Describe utilities -->
