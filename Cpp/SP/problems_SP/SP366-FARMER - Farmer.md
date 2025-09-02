---
title: "FARMER - Farmer"
layout: "post"
diff: 难度0
pid: SP366
tag: []
---

# FARMER - Farmer

## 题目描述

 A farmer has a set of fields, each of which is surrounded by cypress trees. Also, the farmer has a set of strips of land, each of which has a row of cypress trees. In both fields and strips, between every two consecutive cypress trees is a single olive tree. All of the farmer’s cypress trees either surround a field or are in a strip and all of the farmer’s olive trees are between two consecutive cypress trees in a field or in a strip.  
  
 One day the farmer became very ill and he felt that he was going to die. A few days before he passed away he called his eldest son and told him, “I give you any Q cypress trees of your choice and all the olive trees which are between any two consecutive cypress trees you have chosen.” >From each field and from each strip the son can pick any combination of cypress trees. Since the eldest son loves olives he wants to pick the Q cypress trees which will allow him to inherit as many olive trees as possible.

## 输入格式

 t - the number of test cases \[t <= 20\], then t test cses follows. The first line of each test case contains first the integer Q: the number of cypress trees the son is to select; then the integer M, the number of fields; and then the integer K, the number of strips. The second line contains M integers N1, N2,… NM, : the numbers of cypress trees in fields. The third line contains K integers R1, R2,… RK: the numbers of cypress trees in strips.  
 In all test cases, 0 <= Q <= 150000, 0 <= M <= 2000, 0 <= K <= 2000, 3 <= N1 <= 150, 3 <= N2 <= 150,… 3 <= NM <=150, 2 <= R1 <= 150, 2 <= R2 <= 150,… 2 <= RK <= 150. The total number of cypress trees in the fields and strips is at least Q. Additionally, in 50% of the test cases, Q <= 1500.

## 输出格式

For each test case output ont integer: largest possible number of olive trees the son may inherit.

## 样例 #1

### 输入

```
1
17 3 3 
13 4 8 
4 8 6
```

### 输出

```
17
```

