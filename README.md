# 8Puzzle
This is 8 Puzzle Game, an easy version of [15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle).
And I use a heuristic search algorithm [A*](https://en.wikipedia.org/wiki/A*_search_algorithm) to solve it, the heuristic infomation is calculated by summing up all of [Hamming Distance](https://en.wikipedia.org/wiki/Hamming_distance) of each tile's position and its corresponding target position.

# Whether a puzzle is solvable? 
A 8 Puzzle in any state can be represented by a 3x3 array A[i][j], where i, j =0, 1, 2; A[i][j] = 0, 1 ... 8; and A[i][j] = 0, if tile (i, j) is empty. A puzzle A is solvable is defined as: starting from A, after a number of eligible moves, it can reach goal G.
## How to check whether goal state G is reachable from A.
1. Calculate inversion number of A as IA.  
We denote [inversion number](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)#Inversion_number) of A as IA, which is calculated by letting C[i*3+j]=A[i][j], and calculating inversion number of C as IA, while ignore the number 0 (i.e. ignoring the empty tile).
2. Calculate inversion number of G as IG.  
Calculate IG just like IA.
3. If (IA - IG) % 2 == 0, then G is reachable from A, otherwise it's unreachable.

# The max number of motion to solve any Puzzle is 31!!!
Well, this number is calculated by computer.  
It simply runs over all possibilities, and calculates the minimized number of motion to solve each Puzzle to get the max number of motion to solve any Puzzle.
And the result is 31.  
The program's also included in the main.cpp.

# The most difficult Puzzle(needs at leat 31 motion), and corresponding goal position.
1. Puzzle needed to solve:
~~~
  2 1 
3 5 8 
4 6 7 
~~~

2. Goal Puzzle needed to reach:
~~~
1 2 3 
8   4 
7 6 5 
~~~
