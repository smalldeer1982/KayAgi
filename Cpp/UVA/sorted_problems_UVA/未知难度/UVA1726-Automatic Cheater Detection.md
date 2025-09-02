---
title: "Automatic Cheater Detection"
layout: "post"
diff: 难度0
pid: UVA1726
tag: []
---

# Automatic Cheater Detection

## 题目描述

#### 题意简述

编写一个程序用来检测考试作弊。

定义作弊为：正确回答难度为 $d_1$ 的已泄露题，但错误回答了难度为 $d_2$ 的未泄露题，$(d_1>d_2)$ 。

## 输入格式

$T$ 组数据

对于每组数据，第一行一个整数 $Q$ ，表示题目数；

接下来 $Q$ 行，每行包含两个数字 $d_i,s_i$ 和一个字符 $r_i$ ，分别表示题目难度，是否泄露和回答情况。

其中 $1\le d_i \le 10$ , $d_i$ 越大，题目越难；

$s_i\in \{0,1\}$  ，$0$ 表示未泄露， $1$ 表示已泄露；

$r_i\in \{\texttt{i},\texttt{c}\}$ ，$\texttt i$ 表示回答正确， $\texttt c$ 表示回答错误。

## 输出格式

一个整数，表示作弊的题目数。

#### 样例输入

```plain
2
4
2 0 i
3 1 c
4 1 c
5 1 i
4
2 0 i
4 1 c
3 0 i
5 1 c
```

#### 样例输出

```plain
2
4
```

