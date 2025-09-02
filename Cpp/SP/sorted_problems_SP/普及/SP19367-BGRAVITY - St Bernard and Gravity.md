---
title: "BGRAVITY - St Bernard and Gravity"
layout: "post"
diff: 普及/提高-
pid: SP19367
tag: []
---

# BGRAVITY - St Bernard and Gravity

## 题目描述

**St. Bernard's** new game is played on an R×C board. Initially every square is either empty or blocked by a wall. Bernard throws a rock into the board by putting it in the topmost row of a column and then letting gravity do the rest.

Gravity works as follows:  
 => If the square under the rock is a wall or if the rock is in the bottom row of a column, then the rock remains there.  
 => If the square under the rock is empty, then the rock moves to that square.  
 => If the square under the rock contains another rock, then the falling rock may slide sideways :  
 o If the squares left and left-down of the rock are empty, then the rock slides one square left.  
 o If the rock doesn't slide left and the squares to the right and right-down are empty, then the rock slides one square right.  
 o Otherwise, the rock remains there and never moves again.  
 Bernard will never throw another rock while the previous rock hasn't settled down.  
 Write a program that draws the board after Bernard throws all his rocks into the board, if we know the columns that Bernard threw his rocks into, in order.  
**Note:** Bernard will never throw a rock into column in which the top row isn't empty.

**INPUT**

The first line contains integers R and C (1<=R<=30000,1<=C<=30), the size of the board.  
 Each of the following R lines contains C characters, the initial layout of the board. A '.' represents an empty field, while the uppercase letter 'X' is a square blocked by a wall.  
 The next line contains an integer N (1<=N<=100000), the number of rocks Bernard throws.  
 Each of the following N lines contains an integer between 1 and C, the column into which Bernard throws a rock (the leftmost column is column 1).

**OUTPUT**

Output R lines, each containing C characters, the final layout of the board. Rocks should be presented with an uppercase letter 'O'.

**SAMPLE**

**Input**  
 5 4  
 ....  
 ....  
 X...  
 ....  
 ....  
 4  
 1  
 1  
 1  
 1  
**Output**  
 ....  
 O...  
 X...  
 ....  
 OOO.  
  
**Input**  
 7 6  
 ......  
 ......  
 ...XX.  
 ......  
 ......  
 .XX...  
 ......  
 6  
 1  
 4  
 4  
 6  
 4  
 4  
**Output**  
 ......  
 ...O..  
 ...XX.  
 ......  
 .OO...  
 .XX...  
 O..O.O  
  
**In the first example**, all rocks are thrown in the first column. The first rock stops on the wall. The second rock falls on the first, slides right and stops at the bottom of the second column. The third rock falls on the first then on the second rock, slides left and rests at the bottom of the first column. The fourth rock falls on the first then on the second, then slides right.

