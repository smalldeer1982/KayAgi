---
title: "Elections"
layout: "post"
diff: 普及+/提高
pid: CF457C
tag: []
---

# Elections

## 题目描述

You are running for a governor in a small city in Russia. You ran some polls and did some research, and for every person in the city you know whom he will vote for, and how much it will cost to bribe that person to vote for you instead of whomever he wants to vote for right now. You are curious, what is the smallest amount of money you need to spend on bribing to win the elections. To win elections you need to have strictly more votes than any other candidate.

## 输入格式

First line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — number of voters in the city. Each of the next $ n $ lines describes one voter and contains two integers $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i}<=10^{5}; 0<=b_{i}<=10^{4} $ ) — number of the candidate that voter is going to vote for and amount of money you need to pay him to change his mind. You are the candidate $ 0 $ (so if a voter wants to vote for you, $ a_{i} $ is equal to zero, in which case $ b_{i} $ will also be equal to zero).

## 输出格式

Print one integer — smallest amount of money you need to spend to win the elections.

## 样例 #1

### 输入

```
5
1 2
1 2
1 2
2 1
0 0

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 2
1 2
2 1
0 0

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1
100000 0

```

### 输出

```
0

```

