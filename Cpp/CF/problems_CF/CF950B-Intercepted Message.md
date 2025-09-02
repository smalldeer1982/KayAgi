---
title: "Intercepted Message"
layout: "post"
diff: 普及-
pid: CF950B
tag: ['贪心', '前缀和']
---

# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=10^{5} $ ) — the number of blocks in the first and in the second messages.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ 1<=x_{i}<=10^{6} $ ) — the length of the blocks that form the first message.

The third line contains $ m $ integers $ y_{1},y_{2},...,y_{m} $ ( $ 1<=y_{i}<=10^{6} $ ) — the length of the blocks that form the second message.

It is guaranteed that $ x_{1}+...+x_{n}=y_{1}+...+y_{m} $ . Also, it is guaranteed that $ x_{1}+...+x_{n}<=10^{6} $ .

## 输出格式

Print the maximum number of files the intercepted array could consist of.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1

```

### 输出

```
1

```

