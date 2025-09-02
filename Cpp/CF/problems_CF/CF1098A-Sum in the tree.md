---
title: "Sum in the tree"
layout: "post"
diff: 普及+/提高
pid: CF1098A
tag: []
---

# Sum in the tree

## 题目描述

Mitya has a rooted tree with $ n $ vertices indexed from $ 1 $ to $ n $ , where the root has index $ 1 $ . Each vertex $ v $ initially had an integer number $ a_v \ge 0 $ written on it. For every vertex $ v $ Mitya has computed $ s_v $ : the sum of all values written on the vertices on the path from vertex $ v $ to the root, as well as $ h_v $ — the depth of vertex $ v $ , which denotes the number of vertices on the path from vertex $ v $ to the root. Clearly, $ s_1=a_1 $ and $ h_1=1 $ .

Then Mitya erased all numbers $ a_v $ , and by accident he also erased all values $ s_v $ for vertices with even depth (vertices with even $ h_v $ ). Your task is to restore the values $ a_v $ for every vertex, or determine that Mitya made a mistake. In case there are multiple ways to restore the values, you're required to find one which minimizes the total sum of values $ a_v $ for all vertices in the tree.

## 输入格式

The first line contains one integer $ n $ — the number of vertices in the tree ( $ 2 \le n \le 10^5 $ ). The following line contains integers $ p_2 $ , $ p_3 $ , ... $ p_n $ , where $ p_i $ stands for the parent of vertex with index $ i $ in the tree ( $ 1 \le p_i < i $ ). The last line contains integer values $ s_1 $ , $ s_2 $ , ..., $ s_n $ ( $ -1 \le s_v \le 10^9 $ ), where erased values are replaced by $ -1 $ .

## 输出格式

Output one integer — the minimum total sum of all values $ a_v $ in the original tree, or $ -1 $ if such tree does not exist.

## 样例 #1

### 输入

```
5
1 1 1 1
1 -1 -1 -1 -1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 1
1 -1 2 -1 -1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
1 2
2 -1 1

```

### 输出

```
-1

```

