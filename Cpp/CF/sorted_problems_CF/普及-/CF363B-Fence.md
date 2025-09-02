---
title: "Fence"
layout: "post"
diff: 普及-
pid: CF363B
tag: []
---

# Fence

## 题目描述

There is a fence in front of Polycarpus's home. The fence consists of $ n $ planks of the same width which go one after another from left to right. The height of the $ i $ -th plank is $ h_{i} $ meters, distinct planks can have distinct heights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF363B/89891f9a8aa0dbd268db12cc4f373a8fc8629b6b.png)Fence for $ n=7 $ and $ h=[1,2,6,1,1,7,1] $ Polycarpus has bought a posh piano and is thinking about how to get it into the house. In order to carry out his plan, he needs to take exactly $ k $ consecutive planks from the fence. Higher planks are harder to tear off the fence, so Polycarpus wants to find such $ k $ consecutive planks that the sum of their heights is minimal possible.

Write the program that finds the indexes of $ k $ consecutive planks with minimal total height. Pay attention, the fence is not around Polycarpus's home, it is in front of home (in other words, the fence isn't cyclic).

## 输入格式

The first line of the input contains integers $ n $ and $ k $ ( $ 1<=n<=1.5·10^{5},1<=k<=n $ ) — the number of planks in the fence and the width of the hole for the piano. The second line contains the sequence of integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=100 $ ), where $ h_{i} $ is the height of the $ i $ -th plank of the fence.

## 输出格式

Print such integer $ j $ that the sum of the heights of planks $ j $ , $ j+1 $ , ..., $ j+k-1 $ is the minimum possible. If there are multiple such $ j $ 's, print any of them.

## 说明/提示

In the sample, your task is to find three consecutive planks with the minimum sum of heights. In the given case three planks with indexes 3, 4 and 5 have the required attribute, their total height is 8.

## 样例 #1

### 输入

```
7 3
1 2 6 1 1 7 1

```

### 输出

```
3

```

