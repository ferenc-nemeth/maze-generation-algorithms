# maze-generation-algorithms
Collection of maze generation and solving algorithms.

### Table of Contents
- [Introduction](#introduction)
- [How it works](#how-it-works)
  - [File structure](#file-structure)
  - [Maze generators](#maze-generators)
  - [Maze solvers](#maze-solvers)
- [How to use it](#how-to-use-it)
- [References](#references)

### Introduction

A software that generates and solves different kind of mazes with variable height and width. There are a lot of supporting features. Also, the generated mazes can be saved/loaded as an image.

### How it works

***[Demonstration videos on youtube.](https://www.youtube.com/playlist?list=PLwIV1dqznwSfvkh5YVYF3ioumOVpMR9KV)***

The generation algorithms:
- Aldous-Broder [[1]](#references)
- Binary tree [[2]](#references)
- Kruskal's [[3]](#references)
- Prim's [[4]](#references)
- Recursive backtracking [[5]](#references)
- Recursive division [[6]](#references)

The solving algorithms:
- Dead-end filling [[7]](#references)
- Dijkstra's [[8]](#references)
- Wall follower [[9]](#references)

<img src="https://raw.githubusercontent.com/ferenc-nemeth/maze-generation-algorithms/master/design/sample.png" > <br>
*Figure 1. Sample mazes.*

The references have clear explanation about how the algorithms work, I won't go into details. Also, my code is fully commented, so it's good reference too.

#### File structure

The folder structure can be seen below.
```bash
.
├── common
│   ├── file_system
│   ├── main
│   └── maze_generator
├── design
├── LICENSE
├── makefile
├── mazes
│   ├── aldous_broder
│   ├── binary_tree
│   ├── kruskal
│   ├── prim
│   ├── recursive_backtracking
│   └── recursive_division
├── output
├── README.md
└── solver

```
Details about the important folders and files:

- common:
  - main: Main() function, with a demonstration software.
  - file_system: Saves/loads the maze as an image.
  - maze_generator: Base class for every other class.
- design: Pictures needed by this readme.
- makefile: Generates the target.
- mazes: Every maze generation algorithm (and class) in their own sub folder.
- output: Pictures generated by the software.
- solver: The solver algorithms.


#### Maze generators

A maze is represented by a **vector<vector<uint32_t>>**, where 0 is a hole or passage, 1 is a wall and 2 is solution.

Every algorithm has its own class and a common base class, called maze_generator.

Each class has the following public member function:

| Function    | Purpose                                                                       |
| ---         | ---                                                                           |
| constructor | Creates the 2D vector with the given height and width.                        |
| get_cell    | Returns the value of the cell.                                                |
| set_cell    | Manually changes the value of a cell (turns it into a wall (1) or a hole(0).  |
| get_maze    | Returns the maze as a 2D vector.                                              |
| set_maze    | Manually overwrites the whole maze.                                           |
| reshape     | Changes the height and width of the maze.                                     |
| get_height  | Returns the height of the maze.                                               |
| get_width   | Returns the width of the maze.                                                |
| generate    | Does the actual generation.                                                   |

The first six member functions are inherited from the base class, the last is different for every algorithm.

#### Maze solvers

The solving algorithms are way simpler, than the generators. There are only one class (solver) and every algorithm is a single member function.

### How to use it

If you are only interested in reusing the classes/algorithms, then read the previous chapter and the comments inside the code.

If you would like to use the actual software:
Make sure, that you have gcc, which support c++14 and OpenCV.
I have the following, but older/newer versions might be good too:
```
gcc version 5.4.0
GNU Make 4.1
OpenCV 4.0.0
```
If you have everything, then clone the repository, get into the root folder and build:
```
make
```
If it worked, then run:
```
./maze_generator
```
Enjoy!

There is also 
```
make clean
```
and
```
make clean_output
```
First one is the normal clean, the second one cleans the output folder.

### References
[1] [Jamis Buck (The Buckblog) - Aldous-Broder algorithm](https://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm)<br>
[2] [Jamis Buck (The Buckblog) - Binary tree algorithm](https://weblog.jamisbuck.org/2011/2/1/maze-generation-binary-tree-algorithm)<br>
[3] [Jamis Buck (The Buckblog) - Kruskal's algorithm](https://weblog.jamisbuck.org/2011/1/3/maze-generation-kruskal-s-algorithm)<br>
[4] [Jamis Buck (The Buckblog) - Prim's algorithm](https://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm)<br>
[5] [Jamis Buck (The Buckblog) - Recursive backtracking algorithm](https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking)<br>
[6] [Jamis Buck (The Buckblog) - Recursive division algorithm](https://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm)<br>
[7] [Wikipedia - Dead-end filling algorithm](https://en.wikipedia.org/wiki/Maze_solving_algorithm#Dead-end_filling)<br>
[8] [Wikipedia - Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra's_algorithm)<br>
[9] [Wikipedia - Wall follower algorithm](https://en.wikipedia.org/wiki/Maze_solving_algorithm#Wall_follower)<br>
