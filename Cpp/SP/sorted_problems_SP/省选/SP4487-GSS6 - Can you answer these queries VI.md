---
title: "GSS6 - Can you answer these queries VI"
layout: "post"
diff: 省选/NOI-
pid: SP4487
tag: []
---

# GSS6 - Can you answer these queries VI

## 题目描述

## 题目大意
给出一个由$N$个整数组成的序列$A$，你需要应用$M$个操作：

*   `I p x` 在$~p~$处插入插入一个元素$~x~$
*   `D p` 删除$~p~$处的一个元素
*   `R p x` 修改$~p~$处元素的值为$~x~$
*   `Q l r` 查询一个区间$\left[l,r\right]$的最大子段和

## 输入格式

第一行一个数$N$，表示序列的长度

第二行$N$个数，表示初始序列$A$

第三行一个数$M$，表示操作的次数

## 输出格式

输出若干行，每行一个整数，表示查询区间的最大子段和

## 数据规模
对于 $100\%$ 的数据，保证 $1\le N\le 10^5,1\le Q\le 10^5,0\le|A_i|\le 10^4,0\le|x|\le 10^4$


感谢@Anoxiacxy 提供的翻译

## 样例 #1

### 输入

```
5
3 -4 3 -1 6
10
I 6 2
Q 3 5
R 5 -4
Q 3 5
D 2
Q 1 5
I 2 -10
Q 1 6
R 2 -1
Q 1 6

```

### 输出

```
8
3
6
3
5

```

