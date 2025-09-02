---
title: "Heroes of Making Magic III"
layout: "post"
diff: 省选/NOI-
pid: CF717F
tag: []
---

# Heroes of Making Magic III

## 题目描述

I’m strolling on sunshine, yeah-ah! And doesn’t it feel good! Well, it certainly feels good for our Heroes of Making Magic, who are casually walking on a one-directional road, fighting imps. Imps are weak and feeble creatures and they are not good at much. However, Heroes enjoy fighting them. For fun, if nothing else.

Our Hero, Ignatius, simply adores imps. He is observing a line of imps, represented as a zero-indexed array of integers $ a $ of length $ n $ , where $ a_{i} $ denotes the number of imps at the $ i $ -th position. Sometimes, imps can appear out of nowhere. When heroes fight imps, they select a segment of the line, start at one end of the segment, and finish on the other end, without ever exiting the segment. They can move exactly one cell left or right from their current position and when they do so, they defeat one imp on the cell that they moved to, so, the number of imps on that cell decreases by one. This also applies when heroes appear at one end of the segment, at the beginning of their walk.

Their goal is to defeat all imps on the segment, without ever moving to an empty cell in it (without imps), since they would get bored. Since Ignatius loves imps, he doesn’t really want to fight them, so no imps are harmed during the events of this task. However, he would like you to tell him whether it would be possible for him to clear a certain segment of imps in the above mentioned way if he wanted to.

You are given $ q $ queries, which have two types:

- $ 1 $ $ a $ $ b $ $ k $ — denotes that $ k $ imps appear at each cell from the interval $ [a,b] $
- $ 2 $ $ a $ $ b $ - asks whether Ignatius could defeat all imps on the interval $ [a,b] $ in the way described above

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200000 $ ), the length of the array $ a $ . The following line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=5000 $ ), the initial number of imps in each cell. The third line contains a single integer $ q $ ( $ 1<=q<=300000 $ ), the number of queries. The remaining $ q $ lines contain one query each. Each query is provided by integers $ a $ , $ b $ and, possibly, $ k $ ( $ 0<=a<=b&lt;n $ , $ 0<=k<=5000 $ ).

## 输出格式

For each second type of query output $ 1 $ if it is possible to clear the segment, and $ 0 $ if it is not.

## 说明/提示

For the first query, one can easily check that it is indeed impossible to get from the first to the last cell while clearing everything. After we add 1 to the second position, we can clear the segment, for example by moving in the following way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF717F/932daedb58f068e3465f1f1147c5a3d7bd7a6700.png).

## 样例 #1

### 输入

```
3
2 2 2
3
2 0 2
1 1 1 1
2 0 2

```

### 输出

```
0
1

```

