---
title: "Tasty Cookie"
layout: "post"
diff: 省选/NOI-
pid: CF1358F
tag: []
---

# Tasty Cookie

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 说明/提示

In the first example, the arrays $ A $ and $ B $ already equal, so the number of required operations $ =0 $ .

In the second example, we need to replace $ A $ with the prefix sums $ 299999 $ times and then reverse the array. Since $ 299999>2\cdot 10^5 $ , there is no need to restore the answer.

In the fourth example, you cannot get $ B $ from the $ A $ .

## 样例 #1

### 输入

```
2
5 7
5 7
```

### 输出

```
SMALL
0
```

## 样例 #2

### 输入

```
2
1 1
300000 1
```

### 输出

```
BIG
299999
```

## 样例 #3

### 输入

```
2
10 1
13 14
```

### 输出

```
SMALL
6
RPPPRP
```

## 样例 #4

### 输入

```
3
1 2 1
2 1 2
```

### 输出

```
IMPOSSIBLE
```

