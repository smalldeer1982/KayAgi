---
title: "VISIBLEBOX - Decreasing Number of Visible Box"
layout: "post"
diff: 难度0
pid: SP25780
tag: []
---

# VISIBLEBOX - Decreasing Number of Visible Box

## 题目描述

Shadowman 喜欢收集盒子，但他的室友 Woogieman 和 Itman 不喜欢盒子，因此 Shadowman 想尽可能多地隐藏盒子。一个盒子可以被隐藏在另一个盒子里，当且仅当这个盒子是空的，并且它的大小至少是被隐藏盒子大小的两倍。

输出最少需要展示的盒子数量。

## 输入格式

输入数据以一行整数 **T**（$1 \le T \le 50$）开始，表示测试用例的数量。接下来有 **T** 个测试用例，每个测试用例首先包含一个整数 **N**（$1 \le N \le 100000$），表示盒子的数量。下一行包含 **N** 个空格分隔的正整数，第 **i** 个数 **A $ _{i} $**（$1 \le A_{i} \le 100000$）表示第 **i** 个盒子的大小。

## 输出格式

对于每个测试用例，输出一行，包含用例编号和最少需要展示的盒子数量。

## 说明/提示

- $1 \le T \le 50$
- $1 \le N \le 100000$
- $1 \le A_{i} \le 100000$

## 样例 #1

### 输入

```
2
4
1 2 4 8
4
1 3 4 5
```

### 输出

```
Case 1: 1
Case 2: 3
```

