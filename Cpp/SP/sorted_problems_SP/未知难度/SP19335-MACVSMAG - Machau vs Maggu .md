---
title: "MACVSMAG - Machau vs Maggu "
layout: "post"
diff: 难度0
pid: SP19335
tag: []
---

# MACVSMAG - Machau vs Maggu 

## 题目描述

在某工程学院中，有三类人：Maggu、Machau 和其他人。大家都知道，Maggu 们总是努力想把自己装成 Machau，却总是失败。今天，Machau 决定招募一部分 Maggu 并把他们转化为 Machau。所有想成为 Machau 的 Maggu 须从其当前所在位置 $A$ 出发，抵达位于标记为「YAY MACHAU」的 Machau 俱乐部。为了分散 Maggu 的注意力，让他们更加不易到达俱乐部，Machau 在校园内的多个地方放置了书。校园可以被看作是一个 $N \times N$ 的大网格，其中 Maggu 位于坐标 $(A_x, A_y)$，而 Machau 俱乐部的坐标是 $(B_x, B_y)$。Machau 在网格上的 $M$ 个随机位置 $(X_i, Y_i)$ 放置了书（$1 \le i \le M$）。此外，为了防止接收挑战的 Maggu 逃跑，Machau 还在矩形区域外放置了书，这个矩形区域的对角线端点正是 Maggu 的位置 $A$ 和 Machau 俱乐部的位置 $B$。Maggu 只能在网格内上下左右移动，而不能离开这个 $N \times N$ 的网格。如果一个 Maggu 想成功成为 Machau，他必须在不碰到任何书的情况下到达俱乐部。

具体来说，问题可以表述为：给定一个 $N \times N$ 的网格，其中有 $M$ 个不可通行的书本区域，检测从位置 $A$ 是否可以通过上下左右移动到达位置 $B$。

若 Maggu 能够到达 Machau 俱乐部，则输出 "YAY MACHAU"；否则输出 "MAGGU FOREVER"。

## 输入格式

第一行输入六个整数 $N, M, A_x, A_y, B_x, B_y$，其中：
- $N$ 是校园网格的边长。
- $M$ 是校园内放置的书本数量。
- $A_x, A_y$ 是 Maggu 的起始坐标。
- $B_x, B_y$ 是 Machau 俱乐部的目标坐标。

接下来的 $M$ 行，每行两个整数 $X_i, Y_i$，表示在网格上放置书本的坐标。

**注意**：如果在位置 $A$ 或 $B$ 放置了书，Maggu 将必然被分心（无法完成挑战）。所有的坐标对 $(X_i, Y_i)$ 不保证唯一。

## 输出格式

如果 Maggu 能成功到达 Machau 俱乐部，输出 "YAY MACHAU"；否则输出 "MAGGU FOREVER"。

## 说明/提示

$$1 \le N \le 10^9$$
$$1 \le M \le 10^5$$
$$1 \le A_x, A_y, B_x, B_y, X_i, Y_i \le N$$

 **本翻译由 AI 自动生成**

