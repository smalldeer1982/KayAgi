---
title: "GCJ1C09C - Bribe the Prisoners"
layout: "post"
diff: 普及+/提高
pid: SP14846
tag: []
---

# GCJ1C09C - Bribe the Prisoners

## 题目描述

  
  **Problem**

In a kingdom there are prison cells (numbered 1 to **P**) built to form a straight line segment. Cells number **i** and **i+1** are adjacent, and prisoners in adjacent cells are called "neighbours." A wall with a window separates adjacent cells, and neighbours can communicate through that window.

All prisoners live in peace until a prisoner is released. When that happens, the released prisoner's neighbours find out, and each communicates this to his other neighbour. That prisoner passes it on to _his_ other neighbour, and so on until they reach a prisoner with no other neighbour (because he is in cell 1, or in cell **P**, or the other adjacent cell is empty). A prisoner who discovers that another prisoner has been released will angrily break everything in his cell, unless he is bribed with a gold coin. So, after releasing a prisoner in cell **A**, all prisoners housed on either side of cell **A** - until cell 1, cell **P** or an empty cell - need to be bribed.

Assume that each prison cell is initially occupied by exactly one prisoner, and that only one prisoner can be released per day. Given the list of **Q** prisoners to be released in **Q** days, find the minimum total number of gold coins needed as bribes if the prisoners may be released in any order.

Note that each bribe only has an effect for one day. If a prisoner who was bribed yesterday hears about another released prisoner today, then he needs to be bribed again.

**Input**

The first line of input gives the number of cases, **N**. **N** test cases follow. Each case consists of 2 lines. The first line is formatted as

P Q

 where **P** is the number of prison cells and **Q** is the number of prisoners to be released.  
 This will be followed by a line with **Q** distinct cell numbers (of the prisoners to be released), space separated, sorted in ascending order. **Output**

For each test case, output one line in the format

 `Case #X: C` where **X** is the case number, starting from 1, and **C** is the minimum number of gold coins needed as bribes. **Limits**

1 N **Q** P  
 Each cell number is between 1 and **P**, inclusive.

Large dataset

1 P 1 Q

**Sample**

   
Input   
    
Output   
  ` 2<br></br> 8 1<br></br> 3<br></br> 20 3<br></br> 3 6 14<br></br>` ` Case #1: 7<br></br> Case #2: 35<br></br>`

