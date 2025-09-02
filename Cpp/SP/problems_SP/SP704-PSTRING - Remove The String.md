---
title: "PSTRING - Remove The String"
layout: "post"
diff: 省选/NOI-
pid: SP704
tag: ['动态规划 DP', 'KMP 算法']
---

# PSTRING - Remove The String

## 题目描述

给你两个字符串$X$和$Y$。在$X$中删除最少的字符，使得$Y$不为$X$的子串。

## 输入格式

输入包含多组测试数据。

每个测试数据的第一行为$X$,而第二行为$Y$。（保证$X$的长度小于等于10000,$Y$的长度小于等于1000）

## 输出格式

对于每一组数据，输出一个整数，也就是最少删除字符的数量。

## 样例 #1

### 输入

```
ababaa
aba
```

### 输出

```
1
```

