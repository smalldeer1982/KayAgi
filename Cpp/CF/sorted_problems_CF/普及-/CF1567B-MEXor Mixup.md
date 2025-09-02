---
title: "MEXor Mixup"
layout: "post"
diff: 普及-
pid: CF1567B
tag: []
---

# MEXor Mixup

## 题目描述

给你两个数字 $a$，$b$，问使得一个非负整数数组的 $\operatorname{MEX}$ 为 $a$ ，数组内所有数的 $\operatorname{XOR}$ 为 $b$ 的最短长度。

称不属于该数组的最小非负整数为该数组的 $\operatorname{MEX}$ ，数组的 $\operatorname{XOR}$ 为数组所有元素的按位异或。

## 输入格式

多组数据。

第一行一个 $t$ ，表示数据组数。

接下来每组数据包含两个整数 $a$ 和 $b$ 。

## 输出格式

对于每一组数据，输出一个数表示所能构成的最短长度。

## 说明/提示

$1\leq t \leq 5\cdot10^5,1\leq  a \leq 3\cdot10^5,0\leq b\leq 3\cdot10^5$

译者：@smyslenny

## 样例 #1

### 输入

```
5
1 1
2 1
2 0
1 10000
2 10000
```

### 输出

```
3
2
3
2
3
```

