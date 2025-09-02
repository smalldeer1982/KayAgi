---
title: "Prefix Function Queries"
layout: "post"
diff: 提高+/省选-
pid: CF1721E
tag: ['KMP 算法', '有限状态自动机']
---

# Prefix Function Queries

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

You are asked $ q $ queries about it: given another string $ t $ , consisting of lowercase Latin letters, perform the following steps:

1. concatenate $ s $ and $ t $ ;
2. calculate the prefix function of the resulting string $ s+t $ ;
3. print the values of the prefix function on positions $ |s|+1, |s|+2, \dots, |s|+|t| $ ( $ |s| $ and $ |t| $ denote the lengths of strings $ s $ and $ t $ , respectively);
4. revert the string back to $ s $ .

The prefix function of a string $ a $ is a sequence $ p_1, p_2, \dots, p_{|a|} $ , where $ p_i $ is the maximum value of $ k $ such that $ k < i $ and $ a[1..k]=a[i-k+1..i] $ ( $ a[l..r] $ denotes a contiguous substring of a string $ a $ from a position $ l $ to a position $ r $ , inclusive). In other words, it's the longest proper prefix of the string $ a[1..i] $ that is equal to its suffix of the same length.

## 输入格式

The first line contains a non-empty string $ s $ ( $ 1 \le |s| \le 10^6 $ ), consisting of lowercase Latin letters.

The second line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries.

Each of the next $ q $ lines contains a query: a non-empty string $ t $ ( $ 1 \le |t| \le 10 $ ), consisting of lowercase Latin letters.

## 输出格式

For each query, print the values of the prefix function of a string $ s+t $ on positions $ |s|+1, |s|+2, \dots, |s|+|t| $ .

## 样例 #1

### 输入

```
aba
6
caba
aba
bababa
aaaa
b
forces
```

### 输出

```
0 1 2 3 
1 2 3 
2 3 4 5 6 7 
1 1 1 1 
2 
0 0 0 0 0 0
```

## 样例 #2

### 输入

```
aacba
4
aaca
cbbb
aab
ccaca
```

### 输出

```
2 2 3 1 
0 0 0 0 
2 2 0 
0 0 1 0 1
```

