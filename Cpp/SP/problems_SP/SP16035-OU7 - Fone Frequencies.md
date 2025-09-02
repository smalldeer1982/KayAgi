---
title: "OU7 - Fone Frequencies"
layout: "post"
diff: 难度0
pid: SP16035
tag: []
---

# OU7 - Fone Frequencies

## 题目描述

在移动电话网络中，当中继塔和移动设备进行通信时，如果两个中继塔之间的距离不超过 20，我们就称它们是“相邻”的。你的任务是计算出覆盖所有中继塔所需的最少频率数量。

## 输入格式

输入包含多组测试用例。每组测试用例由两行组成：第一行是一个整数 $n$，表示中继塔的数量。第二行包含 $2n$ 个整数，依次表示每个中继塔的坐标：$x_1\ y_1\ x_2\ y_2\ \ldots\ x_n\ y_n$，其中 $(x_i, y_i)$ 是第 $i$ 个中继塔的坐标。请注意，中继塔的数量最多为 12，并且每个中继塔最多只能与 4 个其他中继塔相邻。输入以 $n = 0$ 结束。

## 输出格式

对于每组测试用例，输出一行，格式如下：

```
The towers in case n can be covered in f frequencies.
```

其中 $f$ 是你计算出的最小频率数，$n$ 是测试用例的编号，从 1 开始。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
0 0 5 7.5 1 -3 10.75 -20.1 12.01 -22
6
0 1 19 0 38 1 38 21 19 22 0 21
0
```

### 输出

```
The towers in case 1 can be covered in 3 frequencies.
The towers in case 2 can be covered in 2 frequencies.
```

