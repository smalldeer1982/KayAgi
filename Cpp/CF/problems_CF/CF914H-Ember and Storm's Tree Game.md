---
title: "Ember and Storm's Tree Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF914H
tag: []
---

# Ember and Storm's Tree Game

## 题目描述

Ember and Storm play a game. First, Ember picks a labelled tree $ T $ of $ n $ vertices, such that the degree of every vertex is at most $ d $ . Then, Storm picks two distinct vertices $ u $ and $ v $ in this tree and writes down the labels of the vertices in the path from $ u $ to $ v $ in a sequence $ a_{1},a_{2}...\ a_{k} $ . Finally, Ember picks any index $ i $ ( $ 1<=i<k $ ) in the array. Now he performs one of the following two operations exactly once:

- flip the subrange $ [i+1,k] $ and add $ a_{i} $ to it. After this, the sequence becomes $ a_{1},...\ a_{i},a_{k}+a_{i},a_{k-1}+a_{i},...\ a_{i+1}+a_{i} $
- negate the subrange $ [i+1,k] $ and add $ a_{i} $ to it. i.e., the array becomes $ a_{1},...\ a_{i},-a_{i+1}+a_{i},-a_{i+2}+a_{i},...-a_{k}+a_{i} $

Ember wins if the array is monotonically increasing or decreasing after this. Otherwise Storm wins.

The game can be described by the tuple $ (T,u,v,i,op) $ where $ op $ is «flip» or «negate» depending on the action Ember chose in the last turn. Find the number of tuples that can occur if Ember and Storm play optimally. When they play optimally, if there are multiple moves by which they are guaranteed to win, then they may play any of the winning moves. Otherwise, if someone loses no matter what they play, then they may play any of the possible moves.

Report the answer modulo $ m $ .

## 输入格式

The input consists of a single line containing three integers $ n $ , $ d $ and $ m $ ( $ 2<=n<=200,1<=d<n,1<=m<=2·10^{9} $ ).

## 输出格式

Print a single number — the number of possible tuples if Ember and Storm play as described, modulo $ m $ .

## 说明/提示

In the first sample case, there is only one possible tree. There are two possible paths, $ 1 $ to $ 2 $ and $ 2 $ to $ 1 $ . For both paths, $ i $ can only be $ 1 $ , and $ op $ can take both possibilities. Therefore, the answer is $ 4 $ .

In the second sample, there are no possible trees.

In the third sample, there are three possible trees.

## 样例 #1

### 输入

```
2 1 1000000007

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 1 250

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2 100

```

### 输出

```
36

```

