---
title: "Coloring Rectangles"
layout: "post"
diff: 普及-
pid: CF1584B
tag: []
---

# Coloring Rectangles

## 题目描述

David was given a red checkered rectangle of size $ n \times m $ . But he doesn't like it. So David cuts the original or any other rectangle piece obtained during the cutting into two new pieces along the grid lines. He can do this operation as many times as he wants.

As a result, he will get a set of rectangles. Rectangles $ 1 \times 1 $ are forbidden.

David also knows how to paint the cells blue. He wants each rectangle from the resulting set of pieces to be colored such that any pair of adjacent cells by side (from the same piece) have different colors.

What is the minimum number of cells David will have to paint?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The next lines contain descriptions of test cases.

The only line of each test case contains two integers $ n $ , $ m $ ( $ 1 \leq n, m \leq 3 \cdot 10^4 $ , $ n \cdot m \geq 2 $ ).

## 输出格式

For each test case print a single integer — the minimum number of cells David will have to paint blue.

## 说明/提示

The following pictures show how the initial rectangle can be split and cells colored blue.

In the first test case:

 ![](https://espresso.codeforces.com/d4181663ab2adbfb9f518c9f09390152197a7da9.png)In the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/031877f8fff4a791933910251c89a32c8e77053c.png)In the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/56c02ce81081236d5a7f494f32a723cf9e1c4a6e.png)In the fourth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/13bf05e608fac4f3bd0b4c9984699891f97a32fe.png)

## 样例 #1

### 输入

```
4
1 3
2 2
2 5
3 5
```

### 输出

```
1
2
4
5
```

