## Installation & Setup (Linux)  

#### 1. Clone the repository  
```sh
https://github.com/greenbinjack/pirates-vs-predators.git
cd pirate-vs-predators
```

#### 2. Install SFML
```sh
sudo apt update
sudo apt install libsfml-dev
```

#### 3. Compile and Run the Game
```sh
g++ main.cpp Game.cpp MenuScreen.cpp Instructions.cpp HighScore.cpp BattleGround.cpp Grid.cpp Spawner.cpp Predator.cpp Pirate.cpp Gunner.cpp CannonShooter.cpp Bullet.cpp Currency.cpp Entity.cpp GameOver.cpp NameEntryScreen.cpp Constants.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
./game
```

