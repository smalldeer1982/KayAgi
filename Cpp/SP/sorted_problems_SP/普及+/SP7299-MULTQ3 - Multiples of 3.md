---
title: "MULTQ3 - Multiples of 3"
layout: "post"
diff: 普及+/提高
pid: SP7299
tag: []
---

# MULTQ3 - Multiples of 3

## 题目描述

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 有一个长度为 $n$ 的序列 $a$，她钦定初始所有数都是 $0$，编号从 $0$ 到 $n-1$。  

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 需要你完成两种操作：  

$0$ $l$ $r$ 将区间 $[l,r]$ 的所有数 $+1$  
$1$ $l$ $r$ 查询区间 $[l,r]$ 中能被 $3$ 整除的数个数 ( $0$ 也算在内 )  

她觉得这题很简单，但是她困了，要去睡♀觉，所以这个问题就由你来解决。

接下来 $q$ 行，每行三个整数，表示一次操作。

## 输出格式

对于每个 $1$ 操作，输出一行一个整数表示答案。

## 说明/提示

样例输入：  
```cpp
4 7
1 0 3
0 1 2
0 1 3
1 0 0
0 0 3
1 3 3
1 0 3
```
样例输出：  
```cpp
4
1
0
2
```  

$1\le n,q \le 10^5$

