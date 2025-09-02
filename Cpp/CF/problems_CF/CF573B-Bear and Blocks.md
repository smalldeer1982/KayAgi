---
title: "Bear and Blocks"
layout: "post"
diff: 普及/提高-
pid: CF573B
tag: ['递推', '线段树', '线性递推']
---

# Bear and Blocks

## 题目描述

Limak is a little bear who loves to play. Today he is playing by destroying block towers. He built $ n $ towers in a row. The $ i $ -th tower is made of $ h_{i} $ identical blocks. For clarification see picture for the first sample.

Limak will repeat the following operation till everything is destroyed.

Block is called internal if it has all four neighbors, i.e. it has each side (top, left, down and right) adjacent to other block or to the floor. Otherwise, block is boundary. In one operation Limak destroys all boundary blocks. His paws are very fast and he destroys all those blocks at the same time.

Limak is ready to start. You task is to count how many operations will it take him to destroy all towers.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line contains $ n $ space-separated integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9}) $ — sizes of towers.

## 输出格式

Print the number of operations needed to destroy all towers.

## 说明/提示

The picture below shows all three operations for the first sample test. Each time boundary blocks are marked with red color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png) After first operation there are four blocks left and only one remains after second operation. This last block is destroyed in third operation.

## 样例 #1

### 输入

```
6
2 1 4 6 2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
3 3 3 1 3 3 3

```

### 输出

```
2

```

