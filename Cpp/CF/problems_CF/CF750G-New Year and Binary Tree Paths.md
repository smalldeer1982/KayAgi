---
title: "New Year and Binary Tree Paths"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF750G
tag: ['动态规划 DP', '线段树', '枚举']
---

# New Year and Binary Tree Paths

## 题目描述

The New Year tree is an infinite perfect binary tree rooted in the node $ 1 $ . Each node $ v $ has two children: nodes indexed $ (2·v) $ and $ (2·v+1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/5f3fba6843b56e8c74120fa68d53319463f26696.png)Polar bears love decorating the New Year tree and Limak is no exception. As he is only a little bear, he was told to decorate only one simple path between some pair of nodes. Though he was given an opportunity to pick the pair himself! Now he wants to know the number of unordered pairs of indices $ (u,v) $ ( $ u<=v $ ), such that the sum of indices of all nodes along the simple path between $ u $ and $ v $ (including endpoints) is equal to $ s $ . Can you help him and count this value?

## 输入格式

The only line of the input contains a single integer $ s $ ( $ 1<=s<=10^{15} $ ).

## 输出格式

Print one integer, denoting the number of unordered pairs of nodes indices defining simple paths with the sum of indices of vertices equal to $ s $ .

## 说明/提示

In sample test, there are $ 4 $ paths with the sum of indices equal to $ 10 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/c83b62a188e719702078b419fb6e934500dacd07.png)

## 样例 #1

### 输入

```
10

```

### 输出

```
4

```

