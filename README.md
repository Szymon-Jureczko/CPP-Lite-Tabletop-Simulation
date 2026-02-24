# C--Lite-Tabletop-Simulation
A turn-based combat simulator inspired by Dungeons & Dragons mechanics, built in C++ with SFML graphics rendering. Assemble a party of heroes and engage in tactical battles against a randomised set of enemies.

## Features

- **Character Classes**: Choose from Knight, Wizard, Samurai, Cleric
- **Turn-Based Combat**: Action turn system
- **Character Stats**: Health, Attack Power, Armor Class, Magic Resistance
- **Enemy Types**: procedurally generated teams of enemies from a set of: Goblins, Skeletons, Wraiths, Dragons
- **Visual Rendering**: SFML-powered graphics with character sprites and action logs
- **Battle Logging**: Real-time action history tracking for game events

## How to Play
Start a Battle: Launch the executable to begin combat
Build Your Party: Select from available character classes for your 4-character party
Knight and cleric have higher health pools but lower damage rolls, they are intended as tank characters
Samurai and wizard are the opposite - lower health pools and higher damage rolls - intended as dps characters
Engage Enemies: Face randomly generated enemy groups
Monitor Stats: Watch health, armor class, and other attributes in the UI
Victory/Defeat: Continue until your party falls or enemies are vanquished

## Game Mechanics
Attack type determines whether the character deals physical or magical damage. Characters dealing physical will prioritize attacking the enemy with the highest armor class.
Characters dealing magical will prioritize attacking the enemy with the highest magic resistance.
Attack Power vs Armor Class/Magic Resistance determines hit success
Armor/Magic Resistance reduces magical damage
Each turn all characters on each team make an attack roll against the opponent they're targetting. The attack roll number is randomized. Each character has their own maximum
attack roll value.

## Requirements

- **C++ 11 or later**
- **SFML 2.5.1** - Simple and Fast Multimedia Library
  - Download from: https://www.sfml-dev.org/download.php
  - Extract to `C:\SFML\SFML-2.5.1\` (Windows)
- **GCC/G++** (MinGW on Windows or native on Linux/Mac)
- 

## Build & Run

### Windows (Visual Studio Code or Command Line)

g++ -fdiagnostics-color=always -g main.cpp classes.cpp -o main.exe \
  -I C:\SFML\SFML-2.5.1\include \
  -L C:\SFML\SFML-2.5.1\lib \
  -lsfml-graphics -lsfml-window -lsfml-system

./main.exe

Or use the built-in VS Code build task: C/C++: g++.exe build active file

Linux/Mac
g++ -fdiagnostics-color=always -g main.cpp classes.cpp -o main \
  -I /usr/include/SFML \
  -L /usr/lib \
  -lsfml-graphics -lsfml-window -lsfml-system

./main

## Author
Szymon Jureczko
