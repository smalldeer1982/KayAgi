# [CCC 2025 Senior] 挂画 / Positioning Peter's Paintings

## 题目背景

译自 CCC 2025 Senior T1。本题满分为 $15$。

## 题目描述

有两幅矩形画，一幅长为 $A$，宽为 $B$；另一幅长为 $X$，宽为 $Y$。

要把这两幅画用一个矩形画框裱起来挂在墙上，但是要满足：

- 这两幅画必须全部在画框中；
- 这两幅画不能重叠（但是允许边缘触碰）；
- 这两幅画不能旋转；
- 这两幅画边缘必须与地面平行，或者垂直于地面。

求出符合条件的画框周长的最小值。

## 说明/提示

#### 样例解释

- 样例 $1$ 解释：如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/pe6qu57s.png?x-oss-process=image/resize,m_lfit,h_300)

该样例满足子任务 $1\sim 3$。

- 样例 $2$ 解释：如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/x3l3rp1y.png?x-oss-process=image/resize,m_lfit,h_300)


该样例满足子任务 $2, 3$。

- 样例 $3$ 解释：如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/b4ds4bth.png?x-oss-process=image/resize,m_lfit,h_300)

该样例满足子任务 $3$。

#### 子任务

对于 $100\%$ 的数据，保证 $1\le A,B,X,Y\le 10^8$。


- $\text{Subtask 0(0 points})$：样例。
- $\text{Subtask 1(5 points})$：两幅画的形状都是全等的正方形。
- $\text{Subtask 2(5 points})$：两幅画的形状都是正方形。
- $\text{Subtask 3(5 points})$：无特殊限制。


## 样例 #1

### 输入

```
3 3 3 3```

### 输出

```
18```

## 样例 #2

### 输入

```
2 2 4 4```

### 输出

```
20```

## 样例 #3

### 输入

```
1 2 3 1```

### 输出

```
12```

