## Pirates vs Predators
**Pirates vs Predators** is a strategy-based tower defense game where players place different types of pirates on a grid to defend their base from a variety of predators. Players need to carefully manage resources (gold) to place pirates and use them to fight off increasingly difficult waves of enemies. The game includes dynamic gameplay elements, such as pirate selection, gold management, enemy AI, and collision detection for bullets and predators.

## Features
- **Grid-based Gameplay**: Players can place pirates on a grid to create a defense line against incoming predators.
- **Multiple Pirate Types**: Choose from different types of pirates with unique abilities, such as Gunner and CannonShooter.
- **Predator Enemies**: Various predators with different movement speeds and health values that try to breach the player's defenses.
- **Bullet Mechanics**: Pirates fire bullets that track and damage predators.
- **Gold System**: Players earn gold by defeating predators and can spend it to place more pirates or upgrade their defenses.
- **Score and High Score**: The game tracks the player's score based on defeated predators, and the top scores are stored.
- **Pause and Resume**: Players can pause the game at any time and resume it later without losing progress.
- **Game Over & Restart**: The game ends when a predator reaches the base. The player can then view their score, restart, or return to the main menu.
- **Intuitive User Interface**: Easy-to-use UI for navigating between different screens (Menu, Instructions, High Scores, Game Over).

## Technology Used
- **Language**: C++
- **Libraries and Frameworks**: SFML (Simple and Fast Multimedia Library): Used for handling graphics, window management, and user input.

## Installation & Setup (Linux)  

#### 1. Install SFML
```sh
sudo apt update
sudo apt install libsfml-dev
```

#### 2. Clone the repository  
```sh
https://github.com/greenbinjack/pirates-vs-predators.git
cd pirate-vs-predators
```

#### 3. Compile and Run the Game
```sh
g++ *.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
./game
```



