# [BalticOI 2014] Demarcation (Day2)

## 题目描述

给定一个多边形，求画一条线段将这个多边形分为两个全等的多边形。

需要保证这条线段与坐标轴平行。

## 说明/提示

#### 样例说明

对于样例 $1$，如下图所示，可以分成两个全等的多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ueohtd3.png)

同理，输出 `3 2 1 2` 也可。

对于样例 $2$，如下图所示，不可以分为两个全等的多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/yl64yxp9.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（12 pts）：保证有解。
- Subtask 2（15 pts）：$N \le 200$。
- Subtask 3（23 pts）：$N \le 2000$。
- Subtask 4（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$4 \le N \le 10^5$。

**本题采用 Special Judge。**

#### 说明

翻译自 [BalticOI 2014 Day2 A Demarcation](https://boi.cses.fi/files/boi2014_day2.pdf)。

## 样例 #1

### 输入

```
10
0 0
1 0
1 1
3 1
3 5
2 5
2 3
1 3
1 2
0 2```

### 输出

```
1 2 3 2```

