# solving-a-maze
This was my first project on my journey of teaching my self about data structures and algorithms. 

It is a program to find a path in a maze that leads on an exit from any starting point. The path (road or corridor) is marked by zeros (0) while the  walls of the maze are maked by ones (1) and the exit is labelled with the number 2. There are many possible routes that can be taken but only one leads to the exit and the program tried all possible routes until it hits and a dead end and reversing back on that path or until it reached the exit.

In my solution, I wanted to fully understand how recursion works, so intead of using recursion directly I implemented a stack that mimics that processing of recursion. The square or position being investigated is top of my stack and if we fail to find a way forward from that position we pop it and go back to the previous position that had been pushed onto the stack.

Data structures used: linked list implementation of stack, hash table, matrix.


Algorithm:
We start at a cell (we push it onto the stack) and try move to a cell on the left, right, top or bottom if the value in that neighboring cell is a zero or a two. If it is a two (our predetrmined exit), we have found the exit so the program stops. If not, we keep trying another direction from the current cell. If we have tried all directions from the current cell, we delete that cell from the start of the list. We then try to move to another direction from the next cell that was inserted in the list. The list here is actually a stack. The top cell is the cell we are looking at in the maze. If we have exhausted all possible directions from that cell, we pop it and try another direction from the cell just below this one. 

In order, to avoid moving around in a circular loop, we save the cells we have already visited in an array called visited[ ] [ ] that have the same dimensions as the 2D maze[ ] [ ]. This array is initialized with zeros, but if we visit a cell in the maze, we change it coordinates to value 1 in the visited [ ] [ ] array. Incase, we want to move to a new cell, we first check the visited [ ] [ ] array and make sure we have not already been there. We use a 2D array for saving this information because we can easily write to it in O(1) constant time and also check that data there in O(1) constant time. We never we push a cell on to the stack, we change it content data to 3 and assume it is part of our final path. But if we hit a dead end and have to pop this cell, we reverse the data back to 0 so that when the final maze is printed is in not 3.


