---
title: "SELTEAM - Selecting Teams"
layout: "post"
diff: 普及+/提高
pid: SP5973
tag: []
---

# SELTEAM - Selecting Teams

## 题目描述

There are n players out of which atmost k players are chosen to form the team squad. Out of those players, some subset of them are selected to form a team, and a player of the selected team is appointed as the captain of the team. Given n and k, determine how many possible configurations exist. Two configurations differ if either the players in the team squad differ, or if the number of players in the team differ, or the players in the team differ, or if the captain differs.  
  
For example,the possible configurations for n = 2 and k = 2 are :  
1\) Team squad : {1}, Team : {1}, Captain : 1  
2\) Team squad : {2}, Team : {2}, Captain : 2  
3\) Team squad : {1,2}, Team : {1}, Captain : 1  
4\) Team squad : {1,2}, Team : {2}, Captain : 2  
5\) Team squad : {1,2}, Team : {1,2}, Captain : 1  
6\) Team squad : {1,2}, Team : {1,2}, Captain : 2

**Input**

  
The first line contains T the number of test cases. Each of the next T lines contain 2 integers : n,k

  
**Output**

Output T lines, one for each test case, containing the required total number of configurations. Since the answers can get very big, output the answer modulo 8388608.

**Example**

  
Sample Input :  
3  
2 2  
7 1  
5 3  
  
Sample Output :  
6  
7  
165

  
**Constraints**

1 <= T <= 10000  
1 <= k <= n <= 100000

