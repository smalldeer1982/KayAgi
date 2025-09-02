---
title: "Amr and Chemistry"
layout: "post"
diff: 普及+/提高
pid: CF558C
tag: ['动态规划 DP', '贪心', '枚举', '进制', '字典树 Trie']
---

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the number of chemicals.

The second line contains $ n $ space separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{5} $ ), representing the initial volume of the $ i $ -th chemical in liters.

## 输出格式

Output one integer the minimum number of operations required to make all the chemicals volumes equal.

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 5 6

```

### 输出

```
5
```

