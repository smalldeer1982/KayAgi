---
title: "Mahmoud and Ehab and the xor-MST"
layout: "post"
diff: 提高+/省选-
pid: CF959E
tag: ['生成树', '进制', '前缀和']
---

# Mahmoud and Ehab and the xor-MST

## 题目描述

Ehab is interested in the bitwise-xor operation and the special graphs. Mahmoud gave him a problem that combines both. He has a complete graph consisting of $ n $ vertices numbered from $ 0 $ to $ n-1 $ . For all $ 0<=u<v<n $ , vertex $ u $ and vertex $ v $ are connected with an undirected edge that has weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/31294aedffbec70e119efb89ca1f6d2afecc694a.png) (where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/bc47da33894a98df53134f30108d8405a90ea418.png) is the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Can you find the weight of the minimum spanning tree of that graph?

You can read about complete graphs in [https://en.wikipedia.org/wiki/Complete\_graph](https://en.wikipedia.org/wiki/Complete_graph)

You can read about the minimum spanning tree in [https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)

The weight of the minimum spanning tree is the sum of the weights on the edges included in it.

## 输入格式

The only line contains an integer $ n $ $ (2<=n<=10^{12}) $ , the number of vertices in the graph.

## 输出格式

The only line contains an integer $ x $ , the weight of the graph's minimum spanning tree.

## 说明/提示

In the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/da1dd366c44de9a7fa58c6a7748f6a57cd6a4b83.png) The weight of the minimum spanning tree is 1+2+1=4.

## 样例 #1

### 输入

```
4

```

### 输出

```
4
```

