---
title: "NAJ0001 - Divisible Number Sum"
layout: "post"
diff: 难度0
pid: SP21356
tag: []
---

# NAJ0001 - Divisible Number Sum

## 题目描述

Hazzat is a new guys in computer science. Now he read in 4rd semester. Recently he completed the course data structure. After finished data structure course he can realize that those are not enough for his. Every day he fall in a new (data structure) problem and want solve it, but those problem he can’t solve using his know data structure. He want to establish new data structure. But he always failed to establish it. Now help hazzat to establish a new data structure following problems.

You will be given an array **A** of **N** integers. You need to answer **M** queries.  
 Each query is of the form **V x y**.

For each query, find the sum of set S which is a sub set of array A index x to y and fully divisible by V.

That means find sum of set S (subset of A), where A\[i\] is included in S if x

**Input:**

First line consists of a number T (1

For each case given two integer number N M, (1

Next line has N integers representing the elements of array A. 1

 M lines follow, one per query.

Each line has 3 integers V, x and y (1

**Output:**

For each case print Case No and query answer.

There will be a blank line between two cases.

**Sample:**

 Input

  Output

  2  
5 2  
1 2 3 4 6  
2 1 5  
5 1 4  
   
5 2  
2 3 5 3 7  
3 2 4  
5 1 5

  Case #1  
12  
0  
   
Case #2  
6  
5

 Hints:

Query 1:  
In array index 1 to 5 the set S is {2,4,6} because those are fully divisible by 2. so sum is 12

Query 2:  
In array index 1 to 4 the set S is {} because there are not any number which fully divisible by 5. so sum is 0

Data set is so huge. Use faster I/O

