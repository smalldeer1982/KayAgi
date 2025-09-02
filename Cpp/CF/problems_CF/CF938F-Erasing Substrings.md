---
title: "Erasing Substrings"
layout: "post"
diff: 省选/NOI-
pid: CF938F
tag: []
---

# Erasing Substrings

## 题目描述

You are given a string $ s $ , initially consisting of $ n $ lowercase Latin letters. After that, you perform $ k $ operations with it, where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/c757249d7b8bdc7808476dd4f682a6142a6f6a1c.png). During $ i $ -th operation you must erase some substring of length exactly $ 2^{i-1} $ from $ s $ .

Print the lexicographically minimal string you may obtain after performing $ k $ such operations.

## 输入格式

The only line contains one string $ s $ consisting of $ n $ lowercase Latin letters ( $ 1<=n<=5000 $ ).

## 输出格式

Print the lexicographically minimal string you may obtain after performing $ k $ operations.

## 说明/提示

Possible operations in examples:

1. adcbca ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) adcba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aba;
2. abacabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) abcabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aabacaba.

## 样例 #1

### 输入

```
adcbca

```

### 输出

```
aba

```

## 样例 #2

### 输入

```
abacabadabacaba

```

### 输出

```
aabacaba

```

