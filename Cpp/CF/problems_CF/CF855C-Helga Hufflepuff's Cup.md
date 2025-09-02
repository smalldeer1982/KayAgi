---
title: "Helga Hufflepuff's Cup"
layout: "post"
diff: 普及+/提高
pid: CF855C
tag: []
---

# Helga Hufflepuff's Cup

## 题目描述

Harry, Ron and Hermione have figured out that Helga Hufflepuff's cup is a horcrux. Through her encounter with Bellatrix Lestrange, Hermione came to know that the cup is present in Bellatrix's family vault in Gringott's Wizarding Bank.

The Wizarding bank is in the form of a tree with total $ n $ vaults where each vault has some type, denoted by a number between $ 1 $ to $ m $ . A tree is an undirected connected graph with no cycles.

The vaults with the highest security are of type $ k $ , and all vaults of type $ k $ have the highest security.

There can be at most $ x $ vaults of highest security.

Also, if a vault is of the highest security, its adjacent vaults are guaranteed to not be of the highest security and their type is guaranteed to be less than $ k $ .

Harry wants to consider every possibility so that he can easily find the best path to reach Bellatrix's vault. So, you have to tell him, given the tree structure of Gringotts, the number of possible ways of giving each vault a type such that the above conditions hold.

## 输入格式

The first line of input contains two space separated integers, $ n $ and $ m $ — the number of vaults and the number of different vault types possible. ( $ 1<=n<=10^{5},1<=m<=10^{9} $ ).

Each of the next $ n-1 $ lines contain two space separated integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) representing the $ i $ -th edge, which shows there is a path between the two vaults $ u_{i} $ and $ v_{i} $ . It is guaranteed that the given graph is a tree.

The last line of input contains two integers $ k $ and $ x $ ( $ 1<=k<=m,1<=x<=10 $ ), the type of the highest security vault and the maximum possible number of vaults of highest security.

## 输出格式

Output a single integer, the number of ways of giving each vault a type following the conditions modulo $ 10^{9}+7 $ .

## 说明/提示

In test case $ 1 $ , we cannot have any vault of the highest security as its type is $ 1 $ implying that its adjacent vaults would have to have a vault type less than $ 1 $ , which is not allowed. Thus, there is only one possible combination, in which all the vaults have type $ 2 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
1 4
1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3
1 2
1 3
2 1

```

### 输出

```
13

```

## 样例 #3

### 输入

```
3 1
1 2
1 3
1 1

```

### 输出

```
0

```

