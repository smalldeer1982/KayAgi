---
title: "GENETICS - Genetics"
layout: "post"
diff: 难度0
pid: SP9447
tag: []
---

# GENETICS - Genetics

## 题目描述

基因工程是一项十分有趣的工作。科学家们已经收集了多种 DNA，并希望利用这些 DNA 创造出新的东西。DNA 可以用由 A、G、T、C 四种碱基组成的序列来表示。定义 DNA\[a..b\] 为从索引 a 开始到 b 结束（包含 a 和 b）的子序列，DNA\[a..\] 表示从索引 a 到序列末尾的子序列。科学家们可以对 DNA 执行以下操作：

- 交叉操作：选择 DNA1 和 DNA2，以及两个整数 k1 和 k2，然后创建两个新的 DNA：DNA3 = DNA1\[1..k1\] 加 DNA2\[k2+1..\]，和 DNA4 = DNA2\[1..k2\] 加 DNA1\[k1+1..\]。
  
- 突变操作：选择一个 DNA、一个索引 k 和一个碱基，然后将 DNA 中第 k 个位置的碱基替换为指定的碱基。
  
- 计数操作：选择一个 DNA 和两个整数 k1 和 k2（k1 ≤ k2），返回 DNA\[k1..k2\] 子序列中 A、G、T、C 四种碱基的数量。

初始的 DNA 从 1 到 n 进行编号，其中 n 是 DNA 的总数量。通过交叉操作生成的新 DNA 按序号依次编号。你的任务是编写程序帮助科学家执行这些操作。

## 输入格式

输入的第一行包含一个整数 n，表示初始 DNA 的数量。接下来的 n 行，每行描述一个 DNA。接下来的一行包含一个整数 q，表示将要执行的操作数量。接下来的 q 行中，每行表示一个操作，其格式如下：

- `CROSS id1 id2 k1 k2`
- `MUTATE id k m`
- `COUNT id k1 k2`

## 输出格式

对于每个计数操作，输出四个整数，分别表示给定 DNA 子序列中 A、G、T、C 碱基的数量。

## 说明/提示

- $1 \le n, q \le 10^5$
- $1 \le |DNA_i| \le 10^5$
- $1 \le k1, k2 \le |DNA_i|$
- $1 \le id1, id2, id \le 10^5$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
CTCGC
TGCGG
5
MUTATE 1 2 A
COUNT 2 2 4
MUTATE 2 1 G
CROSS 2 1 1 5
COUNT 4 3 6
```

### 输出

```
0 2 0 1
0 2 0 2
```

