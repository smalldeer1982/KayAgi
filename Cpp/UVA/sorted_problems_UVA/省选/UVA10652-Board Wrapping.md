---
title: "Board Wrapping"
layout: "post"
diff: 省选/NOI-
pid: UVA10652
tag: []
---

# Board Wrapping

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1593

[PDF](https://uva.onlinejudge.org/external/106/p10652.pdf)

SK 酱在纸上画了 $n$ 个长方形，其中第 $i$ 个长方形用五元组 $(x_i,y_i,w_i,h_i,\phi_i)$ 来描述。具体地说，这个长方形的宽（水平方向）为 $w_i$，高（垂直方向）为 $h_i$，**几何中心**的坐标为 $(x_i,y_i)$，且绕中心向**顺时针**方向旋转了 ${\phi_i}^{\circ}$。

## 输入格式

**本题含多组测试数据。**

输入文件的第一行为整数 $T$，代表数据组数；

对于每组数据，共 $(n+1)$ 行：

- 第 $1$ 行，一个整数 $n$，代表长方形的个数；

- 接下来 $n$ 行，第 $(i+1)$ 行五个**实数** $x_i,y_i,w_i,h_i,\phi_i$，描述一个长方形。

## 输出格式

你需要解决 $T$ 组测试数据。


对于每组数据，输出一行。设你算出的百分比为 $p\%$，则你需要输出 `p %`**（中间有一个空格）**，**其中 $\boldsymbol{p}$ 保留一位小数。**

## 说明/提示

对于 $100\%$ 的数据，保证：

- $1\le T\le 50$；
- $1\le n\le 600$；
- $0\le x_i,y_i,w_i,h_i\le 10^4$；
- $\phi\in (-90,90]$；
- 给出的长方形两两不交。

$\texttt{Statement fixed by Starrykiller.}$

下图是样例的示意图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fs6w5nj3.png)

## 样例 #1

### 输入

```
1
4
4 7.5 6 3 0
8 11.5 6 3 0
9.5 6 6 3 90
4.5 3 4.4721 2.2361 26.565
```

### 输出

```
64.3 %
```

