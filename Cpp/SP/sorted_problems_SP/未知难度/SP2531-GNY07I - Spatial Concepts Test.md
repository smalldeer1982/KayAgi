---
title: "GNY07I - Spatial Concepts Test"
layout: "post"
diff: 难度0
pid: SP2531
tag: []
---

# GNY07I - Spatial Concepts Test

## 题目描述

Flathead 测试公司（FTC）为许多公司的 HR 部门提供各种测试。其中一种测试包括空间概念问题，比如：

当下面的图形沿着内线折叠时，会形成一个立方体。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/b63fb1635fe3cee026f30607df6231017de7addb.png)

那么，以下哪个可能是这个立方体的一个角落的图像？

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/8dded3d123abf9ad18be2045a07ff6ed66567f2b.png)

不幸的是，最近 FTC 在测试中遇到了一个问题——一个问题没有正确答案，而另一个问题（例子中所示）有两个正确答案（第 1 个和第 3 个）。

FTC 需要一个程序来读取展开的立方体规格和角视图规格，并确定每个角视图是否是展开后的立方体的一个角。

FTC 使用以下图案作为立方体的面。每个图案关于垂直轴对称，并且都有一个显眼的一端（在图中为顶部）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/c2a201883eac47559cf842d567a9c005ba8db856.png)

展开立方体的规格由六个字母和数字对组成。字母表示面上的图案，数字表示该面上特殊端的方向：1 表示向上，2 表示向右，3 表示向下，4 表示向左。面的顺序如下图所示，方向用右侧方块中的数字表示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/711428538587a52d16c3dec8ce2e9b2d39fbc1fa.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/bd7a1b87f4196377a4c6c912dfe3d8b9c61a1ea2.png)

因此，上述示例中的展开立方体被表示为“F3E4E2D3C2F3”。FTC 有一个程序能生成该规格对应的展开图。

答案图像则由三个字母和数字对组成，字母表示面上的图案，数字表示方向。如下图，面按顶、右、左（图中括号内的数字）顺序指定，即从顶点开始顺时针排列。每个面的特殊端方向用图中边缘上的数字指示，从中心顶点开始按顺时针方向依次排列。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2531/f1422cc1f6bfa6ea65bf8e8163c477f333d72b8b.png)

在例子中，答案图像分别表示为“C2D2F2”、“E3F3C4”、“F2C2D2”、“D1E1F3”和“E1C1E1”。FTC 已经有一个程序生成每个答案的图像，他们需要通过你的程序确保每个问题只有一个正确答案。

## 输入格式

输入的第一行为一个整数 $N$（$1 < N \leq 100$），表示数据集的数量。每个数据集包括六行输入。第一行是展开立方体的规格。后面五行分别为每个答案图像的规格。

## 输出格式

对于每个数据集，输出一行。内容依次为数据集编号（从 1 到 $N$），空格，正确答案的数量，空格，然后是五个‘Y’或‘N’字符，用空格分隔。这些字符表示每个答案图像是否为正确答案（‘Y’表示是，‘N’表示不是）。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
F3E4E2D3C2F3
C2D2F2
E3F3C4
F2C2D2
D1E1F3
E1C1E1
A2F4F1A3A3C4
C3A4A2
F3F4A1
F3C4A1
A2C3A2
A4A4F1
```

### 输出

```
1 2 Y N Y N N
2 0 N N N N N
```

