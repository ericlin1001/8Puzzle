# 8Puzzle
This is Eight Puzzle Game.<br>
And i solve  it using heuristic search algorith.(f=g+h)<br>
H is evalated by summing the hanming distance of each tile's position and its corresponding target position.<br/>
<br/>

## Whether a puzzle is solvable? 
<p>
We denote a puzzle as A[i][j], where i=0,1,2; j=0,1,2; A[i][j]=0,1...8;<br/>
And A[i][j] is the coresponding number of ith row and jth column.
A[i][j]=0 iff. the ith row and jth column is empty.
</p>


<p>
Let C[i*3+j]=A[i][j], and 
we denote inverted number of A as IA, IA is calculated by letting C[i*3+j]=A[i][j], and calculate C's inverted number as IA while ignore the number 0.(i.e. ignoring the empty position).
</p>

<p>
Give a Puzzle A, and it's goal Puzzle G.
We calculate the inverted number of A as IA, and G as IG.
If parity of IA is the same as IG, we say A is compatiable with G, i.e. G is reachable from A.
</p>

<p>
So, to test a puzzle A is solvable, first calculate it's inverted number IA, and goal Puzzle G's inverted number IG, then if (IA-IG) is even number, then A is solvable, otherwise it's unsolvable.
</p>


### The max number of motion to solve any Puzzle is 31!!!
---
Well, this number is calculated by computer.<br/>
It simply runs over all possibilities, and calculates the minimized number of motion to solve each Puzzle to get the max number of motion to solve any Puzzle.
And the result is 31.<br/>
The program's also included in the main.cpp.

### The most difficult Puzzle(needs at leat 31 motion), and corresponding goal position.
---
Puzzle needed to solve:

	  2 1 
	3 5 8 
	4 6 7 


Goal Puzzle needed to reach:

	1 2 3 
	8   4 
	7 6 5 
