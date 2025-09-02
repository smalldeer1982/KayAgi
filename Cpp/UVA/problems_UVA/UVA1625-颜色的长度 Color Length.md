---
title: "颜色的长度 Color Length"
layout: "post"
diff: 提高+/省选-
pid: UVA1625
tag: []
---

# 颜色的长度 Color Length

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4500

[PDF](https://uva.onlinejudge.org/external/16/p1625.pdf)

输入两个长度分别是 $n$ 和 $m(n,m\leq 5000)$ 的颜色序列，要求按顺序合并成同一个序列，即每次可以把一个序列开头的颜色放到新序列的尾部。

例如，两个颜色序列 `GBBY` 和 `YRRGB`，至少有两种合并结果：`GBYBRYRGB` 和 `YRRGGBBYB`。对于每种颜色来说其跨度 $L(c)$ 等于最大位置和最小位置之差。例如，对于上面两种合并结果，每种颜色的 $L(c)$ 和所有 $L(c)$ 的总和如下表所示：

| Color | G | Y | B | R |->| Sum |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| `GBYBRYRGB` | 7 | 3 | 7 | 2 | -> | 19 |
| `YRRGGBBYB` | 1 | 7 | 3 | 1 | -> | 12 |

你的任务是找一种合并方式，使得所有 $L(c)$ 的总和最小。

感谢 @Bruce·Darwin·Xu  提供的翻译。

## 输入格式

第一行，一个正整数 $T$，表示测试数据组数。

接下来描述 $T$ 组测试数据：每组测试数据两行，每行一个字符串（字符集为大写英文字母），表示要合并的两个字符串。

## 输出格式

对于每组测试数据，输出一行一个整数，表示答案。

## 样例 #1

### 输入

```
2
AAABBCY
ABBBCDEEY
GBBY
YRRGB
```

### 输出

```
10
12
```

