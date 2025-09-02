---
title: "Defender of Childhood Dreams"
layout: "post"
diff: 省选/NOI-
pid: CF1583F
tag: []
---

# Defender of Childhood Dreams

## 题目描述

Even if you just leave them be, they will fall to pieces all by themselves. So, someone has to protect them, right?

You find yourself playing with Teucer again in the city of Liyue. As you take the eccentric little kid around, you notice something interesting about the structure of the city.

Liyue can be represented as a directed graph containing $ n $ nodes. Nodes are labeled from $ 1 $ to $ n $ . There is a directed edge from node $ a $ to node $ b $ if and only if $ a < b $ .

A path between nodes $ a $ and $ b $ is defined as a sequence of edges such that you can start at $ a $ , travel along all of these edges in the corresponding direction, and end at $ b $ . The length of a path is defined by the number of edges. A rainbow path of length $ x $ is defined as a path in the graph such that there exists at least 2 distinct colors among the set of $ x $ edges.

Teucer's favorite number is $ k $ . You are curious about the following scenario: If you were to label each edge with a color, what is the minimum number of colors needed to ensure that all paths of length $ k $ or longer are rainbow paths?

Teucer wants to surprise his older brother with a map of Liyue. He also wants to know a valid coloring of edges that uses the minimum number of colors. Please help him with this task!

## 输入格式

The only line of input contains two integers $ n $ and $ k $ ( $ 2 \leq k < n \leq 1000 $ ).

## 输出格式

On the first line, output $ c $ , the minimum colors you need to satisfy the above requirements.

On the second line, print a valid edge coloring as an array of $ \frac{n(n-1)}{2} $ integers ranging from $ 1 $ to $ c $ . Exactly $ c $ distinct colors should exist in the construction. Print the edges in increasing order by the start node first, then by the second node.

For example, if $ n=4 $ , the edge colors will correspond to this order of edges: ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), ( $ 3 $ , $ 4 $ )

## 说明/提示

The corresponding construction for the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583F/801e0382f5a18f576bb5e0cead518269b69fb25e.png) It is impossible to satisfy the constraints with less than $ 2 $ colors.The corresponding construction for the second test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583F/e9f61e2ad637bf2a7f7bff1fd5146004ff52820b.png) One can show there exists no construction using less than $ 3 $ colors.

## 样例 #1

### 输入

```
5 3
```

### 输出

```
2
1 2 2 2 2 2 2 1 1 1
```

## 样例 #2

### 输入

```
5 2
```

### 输出

```
3
3 2 2 1 2 2 1 3 1 1
```

## 样例 #3

### 输入

```
8 7
```

### 输出

```
2
2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

## 样例 #4

### 输入

```
3 2
```

### 输出

```
2
1 2 2
```

