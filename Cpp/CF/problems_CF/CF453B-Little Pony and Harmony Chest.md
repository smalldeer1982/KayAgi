---
title: "Little Pony and Harmony Chest"
layout: "post"
diff: 普及+/提高
pid: CF453B
tag: []
---

# Little Pony and Harmony Chest

## 题目描述

### 题目背景

紫悦正在宇宙公主和月亮的城堡里研究和谐之元的宝箱。


对于一个正整数序列 $b_i$，当且仅当它的任意两个元素都互质时，这个序列 $b_i$ 才是和谐的。据古书记载，宝箱的钥匙是能让以下表达式的值最小的和谐序列 $b_i$：

$$ \sum_{i=1}^n|a_i-b_i| $$

现在紫悦已经得到了序列 $a_i$，你能帮助紫悦找到开启宝箱的钥匙吗？

## 输入格式

第一行包含一个正整数 $n(1 \le n \le 100)$，表示 $a$、$b$ 序列的长度。

第二行包含一串长度为 $n$ 的整数 $a_1, a_2,\dots, a_n (1 \le  a_i\le 30)$。

## 输出格式

输出一行 $n$ 个整数，表示满足条件的 $b_i$ 序列。

Translated by @[Rockdu](https://www.luogu.com.cn/user/39907)，reformed by @[Rainy_chen](https://www.luogu.com.cn/user/74020)。

## 样例 #1

### 输入

```
5
1 1 1 1 1

```

### 输出

```
1 1 1 1 1 
```

## 样例 #2

### 输入

```
5
1 6 4 2 8

```

### 输出

```
1 5 3 1 8 
```

