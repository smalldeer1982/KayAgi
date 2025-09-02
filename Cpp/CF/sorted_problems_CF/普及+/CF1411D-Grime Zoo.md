---
title: "Grime Zoo"
layout: "post"
diff: 普及+/提高
pid: CF1411D
tag: []
---

# Grime Zoo

## 题目描述

Currently, XXOC's rap is a string consisting of zeroes, ones, and question marks. Unfortunately, haters gonna hate. They will write $ x $ angry comments for every occurrence of subsequence 01 and $ y $ angry comments for every occurrence of subsequence 10. You should replace all the question marks with 0 or 1 in such a way that the number of angry comments would be as small as possible.

String $ b $ is a subsequence of string $ a $ , if it can be obtained by removing some characters from $ a $ . Two occurrences of a subsequence are considered distinct if sets of positions of remaining characters are distinct.

## 输入格式

The first line contains string $ s $ — XXOC's rap ( $ 1 \le |s| \leq 10^5 $ ). The second line contains two integers $ x $ and $ y $ — the number of angry comments XXOC will recieve for every occurrence of 01 and 10 accordingly ( $ 0 \leq x, y \leq 10^6 $ ).

## 输出格式

Output a single integer — the minimum number of angry comments.

## 说明/提示

In the first example one of the optimum ways to replace is 001. Then there will be $ 2 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 2 \cdot 2 + 0 \cdot 3 = 4 $ .

In the second example one of the optimum ways to replace is 11111. Then there will be $ 0 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 13 + 0 \cdot 37 = 0 $ .

In the third example one of the optimum ways to replace is 1100. Then there will be $ 0 $ subsequences 01 and $ 4 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 239 + 4 \cdot 7 = 28 $ .

In the fourth example one of the optimum ways to replace is 01101001. Then there will be $ 8 $ subsequences 01 and $ 8 $ subsequences 10. Total number of angry comments will be equal to $ 8 \cdot 5 + 8 \cdot 7 = 96 $ .

## 样例 #1

### 输入

```
0?1
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
?????
13 37
```

### 输出

```
0
```

## 样例 #3

### 输入

```
?10?
239 7
```

### 输出

```
28
```

## 样例 #4

### 输入

```
01101001
5 7
```

### 输出

```
96
```

