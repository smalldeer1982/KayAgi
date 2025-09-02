---
title: "Kevin and Puzzle"
layout: "post"
diff: 普及/提高-
pid: CF2061C
tag: []
---

# Kevin and Puzzle

## 题目描述

有 $n$ 个人排成一行，第 $i$ 个人说他的左边有 $a_i$ 个说谎的人。

每个人要么诚实，要么说谎，诚实的人总是说真话，说谎的人说的话可真可假，没有两个说谎的人站在一起。

两个方案被认为是不同的，应当使至少一个人在一个方案诚实，在另外一个方案说谎。请输出不同的方案数对 $998244353$ 取模的结果。

## 输入格式

多组测试用例，第一行输入 $t (1 \le t \le 10 ^ 4)$，表示测试用例组数。

对于每组测试用例，第一行输入一个正整数 $n (n \le 2 \times 10 ^ 5, \sum n \le 2 \times 10 ^ 5)$，表示人数。

第二行输入 $n$ 个整数 $a_1, a_2, \ldots, a_n (0 \le a_i \le n)$。

## 输出格式

对于每组测试用例，输出不同的方案数对 $998244353$ 取模的结果。

### 样例解释

将使用 $\color{red} \textbf{红色}$ 表示说谎的人，$\color{blue} \textbf{蓝色}$ 表示诚实的人。

- 测试用例 $1$ : $(\color{red}0, \color{blue} 1, \color{red} 2)$；  
- 测试用例 $2$ : $(\color{blue}0, 0, 0, 0, 0)$ 或 $(\color{blue}0, 0, 0, 0, \color{red} 0)$；  
- 测试用例 $3$ : $(\color{blue}0, 0, \color{red} 1, \color{blue} 1, \color{red} 2)$ 或 $(\color{blue}0, \color{red} 0, \color{blue} 1, \color{red} 1, \color{blue} 2)$ 或 $(\color{blue}0, \color{red} 0, \color{blue} 1, \color{blue} 1, \color{red} 2)$。

## 样例 #1

### 输入

```
8
3
0 1 2
5
0 0 0 0 0
5
0 0 1 1 2
5
0 1 2 3 4
5
0 0 1 1 1
5
5 1 5 2 5
1
0
4
2 3 1 1
```

### 输出

```
1
2
3
0
4
1
2
0
```

