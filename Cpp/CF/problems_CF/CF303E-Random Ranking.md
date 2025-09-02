---
title: "Random Ranking"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF303E
tag: []
---

# Random Ranking

## 题目描述

Imagine a real contest or exam of $ n $ participants. Every participant will get a particular score. We can predict the standings board more or less, if we do some statistics on their previous performance.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303E/90ca89756b8ef44c141ac7d916aaf35a953a7ec7.png)Let's say the score of the participants will be uniformly distributed in interval $ [l_{i},r_{i}] $ (the score can be a real number). Can you predict the standings board according to these data? In other words you should say for each participant the probability that he gets some fixed place in the scoreboard. The participants are sorted by increasing of their scores in the scoreboard. So, the participant with the largest score gets the last place.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=80 $ ), showing how many participants we have. Each of the next $ n $ lines contains our predictions, the $ i $ -th line contains a pair of integers $ l_{i},r_{i} $ $ (0<=l_{i}&lt;r_{i}<=10^{9}) $ as the distributed interval for participant $ i $ .

Consider the participants numbered from $ 1 $ to $ n $ in some way.

## 输出格式

Output a distributed matrix $ a $ of order $ n $ . The element $ a_{ij} $ of the matrix is the probability that participant $ i $ has rank $ j $ .

Your answer will considered correct if it has at most $ 10^{-6} $ absolute or relative error.

## 说明/提示

The score probability distribution is continuous, which means, there is no possibility for a draw.

## 样例 #1

### 输入

```
2
1 6
4 9

```

### 输出

```
0.9200000000 0.080 
0.080 0.9200000000 

```

## 样例 #2

### 输入

```
8
0 2
1 3
2 4
3 5
4 6
5 7
6 8
7 9

```

### 输出

```
0.875 0.125 0 0 0 0 0 0 
0.125 0.750 0.125 0 0 0 0 0 
0 0.125 0.750 0.125 0 0 0 0 
0 0 0.125 0.750 0.125 0 0 0 
0 0 0 0.125 0.750 0.125 0 0 
0 0 0 0 0.125 0.750 0.125 0 
0 0 0 0 0 0.125 0.750 0.125 
0 0 0 0 0 0 0.125 0.875 

```

