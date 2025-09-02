---
title: "Neko Rules the Catniverse (Large Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1152F2
tag: []
---

# Neko Rules the Catniverse (Large Version)

## 题目描述

This problem is same as the previous one, but has larger constraints.

Aki is playing a new video game. In the video game, he will control Neko, the giant cat, to fly between planets in the Catniverse.

There are $ n $ planets in the Catniverse, numbered from $ 1 $ to $ n $ . At the beginning of the game, Aki chooses the planet where Neko is initially located. Then Aki performs $ k - 1 $ moves, where in each move Neko is moved from the current planet $ x $ to some other planet $ y $ such that:

- Planet $ y $ is not visited yet.
- $ 1 \leq y \leq x + m $ (where $ m $ is a fixed constant given in the input)

This way, Neko will visit exactly $ k $ different planets. Two ways of visiting planets are called different if there is some index $ i $ such that, the $ i $ -th planet visited in the first way is different from the $ i $ -th planet visited in the second way.

What is the total number of ways to visit $ k $ planets this way? Since the answer can be quite large, print it modulo $ 10^9 + 7 $ .

## 输入格式

The only line contains three integers $ n $ , $ k $ and $ m $ ( $ 1 \le n \le 10^9 $ , $ 1 \le k \le \min(n, 12) $ , $ 1 \le m \le 4 $ ) — the number of planets in the Catniverse, the number of planets Neko needs to visit and the said constant $ m $ .

## 输出格式

Print exactly one integer — the number of different ways Neko can visit exactly $ k $ planets. Since the answer can be quite large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, there are $ 4 $ ways Neko can visit all the planets:

- $ 1 \rightarrow 2 \rightarrow 3 $
- $ 2 \rightarrow 3 \rightarrow 1 $
- $ 3 \rightarrow 1 \rightarrow 2 $
- $ 3 \rightarrow 2 \rightarrow 1 $

In the second example, there are $ 9 $ ways Neko can visit exactly $ 2 $ planets:

- $ 1 \rightarrow 2 $
- $ 2 \rightarrow 1 $
- $ 2 \rightarrow 3 $
- $ 3 \rightarrow 1 $
- $ 3 \rightarrow 2 $
- $ 3 \rightarrow 4 $
- $ 4 \rightarrow 1 $
- $ 4 \rightarrow 2 $
- $ 4 \rightarrow 3 $

In the third example, with $ m = 4 $ , Neko can visit all the planets in any order, so there are $ 5! = 120 $ ways Neko can visit all the planets.

In the fourth example, Neko only visit exactly $ 1 $ planet (which is also the planet he initially located), and there are $ 100 $ ways to choose the starting planet for Neko.

## 样例 #1

### 输入

```
3 3 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4 2 1

```

### 输出

```
9

```

## 样例 #3

### 输入

```
5 5 4

```

### 输出

```
120

```

## 样例 #4

### 输入

```
100 1 2

```

### 输出

```
100

```

