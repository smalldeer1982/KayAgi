---
title: "Danger Point"
layout: "post"
diff: 入门
pid: UVA10649
tag: []
---

# Danger Point

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/ha0gtgnc.png)

如图，$AB$ 交 $CD$ 于 $E$ 点，夹角为 $45 \degree$。

$\angle ACB = \angle ADB = 90 \degree$，$ED \gt CE$。

给出 $AB$，$ED$ 求 $CE$ （保留 $6$ 位小数）。

## 输入格式

**每个测试点由多组数据组成。**

每行共两个整数，分别表示 $AB$，$ED$ 的长度，以 `0 0` 结尾。

## 输出格式

对于每组数据，若有解输出 $CE$ 的长度，否则输出 ```INCORRECT INFORMATION !!!```。

## 样例 #1

### 输入

```
333.25 101.154
50.50 10.10
10.10 50.50
0 0
```

### 输出

```
212.827746
34.250766
INCORRECT INFORMATION !!!
```

