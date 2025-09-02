---
title: "EMPODIA - Empodia"
layout: "post"
diff: 难度0
pid: SP367
tag: []
---

# EMPODIA - Empodia

## 题目描述

 The ancient mathematician and philosopher Pythagoras believed that reality is mathematical in nature. Present-day biologists study properties of biosequences. A biosequence is a sequence of M integers, which  
 • contains each of the numbers 0,1,…,M-1,  
 • starts with 0 and ends with M-1, and  
 • has no two elements E,E+1 in adjacent positions in this order.  
 A subsequence consisting of adjacent elements of a biosequence is called a segment..  
  
 A segment of a biosequence is called a framed interval if it includes all integers whose values are between the value of the first element, which must be the smallest element in the segment, and the last element, which must be the largest and different from the first. A framed interval is called an empodio if it does not contain any shorter framed intervals.  
  
 As an example, consider the biosequence (0,3,5,4,6,2,1,7). The whole biosequence is a framed interval. However, it contains another framed interval (3,5,4,6) and therefore it is not an empodio. The framed interval (3,5,4,6) does not contain a shorter framed interval, so it is an empodio. Furthermore, it is the only empodio in that biosequence.  
  
 You are to write a program that, given a biosequence, finds all empodia (plural for empodio) in that biosequence.

## 输入格式

 t - the number of test cases \[t <= 20\], then t test cses follows. The first line of each test case contains a single integer M: the number of integers in the input biosequence. The following M lines contain the integers of the biosequence in the order of the sequence. Each of these M lines contains a single integer. In one test case, 1000000 <= M <= 1100000. In all other test cases, 1 <= M <= 60000. Additionally, in 50% of the test cases, M <= 2600.

## 输出格式

The first line for each test case is to contain one integer H: the number of empodia in the input biosequence. The following H lines describe all empodia of the input biosequence in the order of appearance of the starting point in the biosequence. Each of these lines is to contain two integers A and B (in that order) separated by a space, where the Ath element of the input biosequence is the first element of the empodio and the Bth element of the input biosequence is the last element of the empodio.

## 样例 #1

### 输入

```
1
8 
0 
3 
5 
4 
6 
2 
1 
7
```

### 输出

```
1
2 5
```

