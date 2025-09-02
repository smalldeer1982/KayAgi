---
title: "Nested Segments"
layout: "post"
diff: 普及+/提高
pid: CF652D
tag: []
---

# Nested Segments

## 题目描述

You are given $ n $ segments on a line. There are no ends of some segments that coincide. For each segment find the number of segments it contains.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of segments on a line.

Each of the next $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ -10^{9}<=l_{i}&lt;r_{i}<=10^{9} $ ) — the coordinates of the left and the right ends of the $ i $ -th segment. It is guaranteed that there are no ends of some segments that coincide.

## 输出格式

Print $ n $ lines. The $ j $ -th of them should contain the only integer $ a_{j} $ — the number of segments contained in the $ j $ -th segment.

## 样例 #1

### 输入

```
4
1 8
2 3
4 7
5 6

```

### 输出

```
3
0
1
0

```

## 样例 #2

### 输入

```
3
3 4
1 5
2 6

```

### 输出

```
0
1
1

```

