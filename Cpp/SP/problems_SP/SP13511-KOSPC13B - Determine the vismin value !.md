---
title: "KOSPC13B - Determine the vismin value !"
layout: "post"
diff: 难度0
pid: SP13511
tag: []
---

# KOSPC13B - Determine the vismin value !

## 题目描述

 There are N students in a class. The teacher wants to test the acuity of the students' vision as well as mind in an entertaining way.She comes up with an idea.  
 The students were made to stand in a line and numbered from 1 to N, each carrying a board with a number K on it.The test is as follows : the teacher calls out a student X;the student can look at either sides and choose a student Y who carries a board with a number greater than or equal to the number on the board carried by X and calculates a value called as "vismin value". "vismin value" is defined as the product of the difference between the positions of X and Y and the smallest of the numbers on the boards carried by X and Y.If it is not possible to choose Y,"vismin value" will be 0. Now, the way the students are tested is how far the students maximise the "vismin value".For each student called, he/she answers with a "vismin value".If it is maximum, teacher says "Maximum".If there is a greater value possible, the teacher says the value which the student is running short of, to attain the maximum value.If the value said by the student is greater than the maximum value possible, the teacher says "Not possible".  
Consider yourself as the teacher and print the output accordingly.

**Input:**

The first line of the input consists of N,the number of students in the class.  
The second line consists of N space separated integers K representing the numbers on the boards carried by the respective students.  
Then, each line/query consists of a student number separated by the vismin value determined by the student.  
Input ends with both student number and vismin value equal to 0.  
  
**Output:**  
For each query, print what the teacher would have said.

****Constraints** :**

1<=N<=100000  
1<=k<=10^9

Number of queries <= 10000

  
Input :  
5  
5 3 6 7 1  
1 13  
1 18  
1 15  
4 5  
5 4  
0 0  
Output :  
2  
Not possible  
Maximum  
Not possible  
Maximum

