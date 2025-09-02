---
title: "CUCKOO - Cuckoo Hashing"
layout: "post"
diff: 难度0
pid: SP4036
tag: []
---

# CUCKOO - Cuckoo Hashing

## 题目描述

## **题意描述**
哈希可以用来解决一个经典的问题：给定一个字典 $D$，查找一个字符串 $q$ 是否存在于字典 $D$ 中。

这里我们介绍一个新的哈希变体：$\text{Cuckoo \  Hashing}$。对于每个字符串 $q$ 我们使用两个哈希函数 $h_1$ 与 $h_2$。对于当前的哈希数组 $T$,如果 $T[h_1(q)]$ 为空，则令 $T[h_1(q)] = q$，否则如果 $T[h_2(q)]$ 为空，则令 $T[h_2(q)] = q$。若两者皆不为空，则如同 $\text{Cuckoo}$ (杜鹃)一样，将 $T[h_1(q)]$ 设置为 $q$ 并让原来存放在此位置的字符串移出哈希表，然后重新插入哈希表。如果还是有冲突，则继续上述过程，直至没有冲突，所有字符串都可以放入哈希表中，这时输出 $\text{"successful \  hashing"}$。如果冲突不能解决，则输出 $\text{"rehash \ necessary"}$

## 输入格式

第一行输入一个 $t \ (1 \leq t \leq 50)$ 表示测试数据个数

每个数据包含一个 $m$ 和 $n\ (1 \leq m \leq n\leq10000)$ ，分别表示有 $m$ 个字符串和哈希数组大小 $n$

然后输入 $m$ 行，每行两个数，分别表示 $h_1(q)$ 与 $h_2(q)$。数据保证 $0 \leq h_1(q),h_2(q) < n$

## 输出格式

对于每一个样例，如果不可解决冲突，输出 $\text{"successful \  hashing"}$，否则输出 $\text{"rehash \ necessary"}$

## 样例 #1

### 输入

```
2
3 3
0 1
1 2
2 0
5 6
2 3
3 1
1 2
5 1
2 5
```

### 输出

```
successful hashing
rehash necessary
```

