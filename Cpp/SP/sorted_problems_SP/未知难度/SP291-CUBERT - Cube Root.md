---
title: "CUBERT - Cube Root"
layout: "post"
diff: 难度0
pid: SP291
tag: []
---

# CUBERT - Cube Root

## 题目描述

Your task is to calculate the cube root of a given positive integer. We can not remember why exactly we need this, but it has something in common with a princess, a young peasant, kissing and half of a kingdom (a huge one, we can assure you).

Write a program to solve this crucial task.

## 输入格式

The input starts with a line containing a single integer **t** <= 20, the number of test cases. **t** test cases follow.

The next lines consist of large positive integers of up to 150 decimal digits. Each number is on its own separate line of the input file. The input file may contain empty lines. Numbers can be preceded or followed by whitespaces but no line exceeds 255 characters.

## 输出格式

For each number in the input file your program should output a line consisting of two values separated by single space. The second value is the cube root of the given number, truncated (not rounded!) after the 10th decimal place. First value is a checksum of all printed digits of the cube root, calculated as the sum of the printed digits modulo 10.

## 样例 #1

### 输入

```
5
1
        8
   1000

2
33076161
```

### 输出

```
1 1.0000000000
2 2.0000000000
1 10.0000000000
0 1.2599210498
6 321.0000000000
```

