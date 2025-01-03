<h1 align="center">🔲 RayTris 🔲</h1>

![RayTetris](data/RayTetrisDemo.png)

## Introduction

**RayTris** is a game I created in C using the `ncurses` library during my second year of preparatory engineering studies to enhance my programming skills. Inspired by the iconic game **Tetris**, it features a grid where various forms fall until they reach a solid surface. When a horizontal line is completed, it is cleared, and all the forms above it drop down by one row. The player's score increases based on the number of lines cleared simultaneously. The forms dropping speed increased each 30 seconds. The objective is to achieve the highest score possible while ensuring no blocks exceed the upper limit of the grid.

## Prerequisites

- **C compiler** such as `gcc` is required to compile the game.
- `ncurses` library to manage the game's terminal-based interface.

## Installation

1. **Install the `ncurses` library with the following command :** 
```sh
sudo apt-get install libncurses5-dev libncursesw5-dev libncurses5 libncursesw5
```

2. **Clone the repository :** 
```sh
git clone https://github.com/RayyyZen/RayTris.git
```

3. **Move into the project folder :** 
```sh
cd RayTris
```

4. **Compile and run the project :**
```sh
make run
```
- **OR**
```sh
make && ./RayTris
```

## Game instructions

![RayTetris](data/RayTetrisMenu.png)

### Menu options 
- New : Start a new game session
- Resume : Load the last saved game session
- Exit : Quit the game

### Game modes

#### Normal mode 
- Username : Chosen by the player under 10 caracters
- Lines : 15
- Columns : 10
- Simple Line : 100 points
- Double Line : 300 points
- Triple Line : 500 points
- Tetris Line : 800 points

#### Custom mode
- Username : Chosen by the player under 10 caracters
- Lines : Chosen by the player between 10 and 18
- Columns : Chosen by the player between 10 and 25
- Simple Line : Chosen by the player between 0 and 10000 points
- Double Line : Chosen by the player between 0 and 10000 points
- Triple Line : Chosen by the player between 0 and 10000 points
- Tetris Line : Chosen by the player between 0 and 10000 points

### Game controls :
- `ENTER` : Select a menu option
- `SPACE` : Rotate a form
- `←` or `q` : Move left
- `→` or `d` : Move right
- `↓` or `s` : Move down
- `b` : Return back in menu
- `l` : Stop or leave the game
- `m` : Return to menu

### Gameplay :

A form appears at the top middle of the grid, and it can be moved using the keys shown in the "Game controls" section. Due to gravity, the form gradually falls until it hits a solid surface, and the process repeats until a block exceeds the top limit. In normal mode, after the game ends, the screen displays the top 3 players with the highest scores.

## License

This project is licensed under the BSD 2-Clause License. See the [LICENSE](LICENSE) file for details.