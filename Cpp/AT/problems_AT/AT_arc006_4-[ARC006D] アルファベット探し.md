---
title: "[ARC006D] アルファベット探し"
layout: "post"
diff: 普及+/提高
pid: AT_arc006_4
tag: []
---

# [ARC006D] アルファベット探し

## 题目描述

在长为H，宽为W的矩阵中，可以用黑格子组成一些字母。

例如图1

![图1](https://cdn.luogu.com.cn/upload/image_hosting/8yah7syy.png)
图1（用7*7的格子分别组成了A，B，C）

矩阵中只能由黑格组成A，B，C字母，并且将A，B，C分别放大或缩小后的图案以及将3个字母分别旋转90°后的图案都算A，B，C的相同形状。

例如图2

![图2](https://cdn.luogu.com.cn/upload/image_hosting/zb1lce1g.png)

图2（以上字母均为合法字母，并分别属于A，B，C）

设这个字母最长的长为h，最长的宽为w，则该字母所占的矩阵大小为：（h+1）*（w+1）

如果两个字母的矩阵相互重叠，则两个字母均为不合法。

例如图3

![图3](https://cdn.luogu.com.cn/upload/image_hosting/v3hirerx.png)

图3（因为两个A所占的矩阵有重叠部分，所以均为不合法）

现在给出H*W的矩阵，分别求其中A，B，C 3个字母的个数。

## 输入格式

第一行两个整数H，W

接下来输入H*M大小的矩阵，由"o"和"."组成。

"o"代表黑块，可以算作字母的一部分。

"."代表白块，不能算作字母的一部分

## 输出格式

分别输出矩阵中所含的合法的A，B，C个数。中间用空格隔开。

