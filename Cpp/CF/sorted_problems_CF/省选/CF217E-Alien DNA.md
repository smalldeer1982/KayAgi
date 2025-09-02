---
title: "Alien DNA"
layout: "post"
diff: 省选/NOI-
pid: CF217E
tag: ['字符串', '并查集', '递归']
---

# Alien DNA

## 题目描述

Professor Bajtocy is conducting experiments on alien DNA. He has discovered that it is subject to repetitive mutations — each mutation happens in the same way: some continuous subsequence of the alien DNA becomes active, copies itself, the copy gets mangled and inserts itself right after the original subsequence. The mangled copy of the activated continuous subsequence is formed by first joining all the elements at the even positions in that subsequence, and then joining all the elements at the odd ones at the end. That is, if the activated subsequence consists of 11 elements and represented as $ s_{1}s_{2}...\ s_{11} $ , its mangled copy is $ s_{2}s_{4}s_{6}s_{8}s_{10}s_{1}s_{3}s_{5}s_{7}s_{9}s_{11} $ .

For example, if the original sequence was "ACTGG" and the mutation happened on the segment $ [2,4] $ (that is the activated subsequence is "CTG"), the mutated DNA is: "ACTGTCGG". The mangled copy of the activated subsequence is marked with bold font.

Professor Bajtocy has written down the original DNA sequence and the mutations that sequentially happened to it, and he now asks you to recover the first $ k $ elements of the DNA sequence after all the mutations.

## 输入格式

The first line of input contains the original DNA sequence, consisting only of letters "A", "C", "T" and "G" and not exceeding $ 3·10^{6} $ in length.

The second line contains a single integer $ k $ ( $ 1<=k<=3·10^{6} $ ).

The third line contains a single integer $ n $ ( $ 0<=n<=5000 $ ) — the number of mutations. The next $ n $ lines describe the mutations in chronological order — each mutation is described by two numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ), meaning that the continuous subsequence $ [l_{i},r_{i}] $ has become active and cloned itself, joining itself with the mangled copy.

It is guaranteed that the input data is correct, that is, no mutation acts on non-existing elements of the DNA sequence, and the resulting DNA sequence has at least $ k $ elements.

Assume that the DNA elements are indexed starting from 1 and that the notation $ [l,r] $ meaning the continuous subsequence of DNA sequence that consists of $ r-l+1 $ elements starting at the $ l $ -th DNA sequence element and ending at the $ r $ -th DNA sequence element.

## 输出格式

Output a single line, containing the first $ k $ letters of the mutated DNA sequence.

## 说明/提示

In the second example, after the first mutation the sequence is "ACCAGTACGT". After the second mutation it's "ACCAGTACCGACATCGT".

## 样例 #1

### 输入

```
GAGA
4
0

```

### 输出

```
GAGA

```

## 样例 #2

### 输入

```
ACGTACGT
16
2
1 2
2 8

```

### 输出

```
ACCAGTACCGACATCG

```

