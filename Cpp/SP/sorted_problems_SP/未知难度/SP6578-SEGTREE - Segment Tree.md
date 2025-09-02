---
title: "SEGTREE - Segment Tree"
layout: "post"
diff: 难度0
pid: SP6578
tag: []
---

# SEGTREE - Segment Tree

## 题目描述

**题目大意：**

植树节到了（雾）！小A种了一棵[红黑树](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)，小B种了一棵[线段树](https://en.wikipedia.org/wiki/Segment_tree)，我种了一棵[二叉树](https://en.wikipedia.org/wiki/Binary_tree)，我们都有光明的前途

然而小L种线段树总是出错（请见ta的历史提交记录~~我也没找到~~），一怒之下ta决定画一棵线段树。ta把$n$个点$(x_i,y_i)$放在平面上，将某对点连起来形成一条线段，所有的线段构成一棵树，这棵树满足以下条件：

1.这棵树是[有根树](https://en.wikipedia.org/wiki/Tree_%28graph_theory%29)

2.子节点的$y$值大于ta的父节点的$y$值

3.两条线段只能在端点相交

求线段最小总长度，注意可以旋转树来满足上述条件

## 输入格式

第一行一个整数$n$，下面$n$行每行两个整数$x_i,y_i$

## 输出格式

一行，一个四舍五入到小数点后的4位实数，即线段最小总长度

感谢@守望 提供翻译

