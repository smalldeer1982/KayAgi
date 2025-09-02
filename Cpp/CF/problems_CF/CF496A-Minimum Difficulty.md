---
title: "Minimum Difficulty"
layout: "post"
diff: 普及-
pid: CF496A
tag: []
---

# Minimum Difficulty

## 题目描述

Mike is trying rock climbing but he is awful at it.

There are $ n $ holds on the wall, $ i $ -th hold is at height $ a_{i} $ off the ground. Besides, let the sequence $ a_{i} $ increase, that is, $ a_{i}<a_{i+1} $ for all $ i $ from 1 to $ n-1 $ ; we will call such sequence a track. Mike thinks that the track $ a_{1} $ , ..., $ a_{n} $ has difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF496A/6c4805b013b934a5f994bca3651000871cc18881.png). In other words, difficulty equals the maximum distance between two holds that are adjacent in height.

Today Mike decided to cover the track with holds hanging on heights $ a_{1} $ , ..., $ a_{n} $ . To make the problem harder, Mike decided to remove one hold, that is, remove one element of the sequence (for example, if we take the sequence $ (1,2,3,4,5) $ and remove the third element from it, we obtain the sequence $ (1,2,4,5) $ ). However, as Mike is awful at climbing, he wants the final difficulty (i.e. the maximum difference of heights between adjacent holds after removing the hold) to be as small as possible among all possible options of removing a hold. The first and last holds must stay at their positions.

Help Mike determine the minimum difficulty of the track after removing one hold.

## 输入格式

Mike is trying rock climbing but he is awful at it.

There are $ n $ holds on the wall, $ i $ -th hold is at height $ a_{i} $ off the ground. Besides, let the sequence $ a_{i} $ increase, that is, $ a_{i}<a_{i+1} $ for all $ i $ from 1 to $ n-1 $ ; we will call such sequence a track. Mike thinks that the track $ a_{1} $ , ..., $ a_{n} $ has difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF496A/6c4805b013b934a5f994bca3651000871cc18881.png). In other words, difficulty equals the maximum distance between two holds that are adjacent in height.

Today Mike decided to cover the track with holds hanging on heights $ a_{1} $ , ..., $ a_{n} $ . To make the problem harder, Mike decided to remove one hold, that is, remove one element of the sequence (for example, if we take the sequence $ (1,2,3,4,5) $ and remove the third element from it, we obtain the sequence $ (1,2,4,5) $ ). However, as Mike is awful at climbing, he wants the final difficulty (i.e. the maximum difference of heights between adjacent holds after removing the hold) to be as small as possible among all possible options of removing a hold. The first and last holds must stay at their positions.

Help Mike determine the minimum difficulty of the track after removing one hold.

## 输出格式

Print a single number — the minimum difficulty of the track after removing a single hold.

## 说明/提示

In the first sample you can remove only the second hold, then the sequence looks like $ (1,6) $ , the maximum difference of the neighboring elements equals 5.

In the second test after removing every hold the difficulty equals 2.

In the third test you can obtain sequences $ (1,3,7,8) $ , $ (1,2,7,8) $ , $ (1,2,3,8) $ , for which the difficulty is 4, 5 and 5, respectively. Thus, after removing the second element we obtain the optimal answer — 4.

## 样例 #1

### 输入

```
3
1 4 6

```

### 输出

```
5

```

## 样例 #2

### 输入

```
5
1 2 3 4 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5
1 2 3 7 8

```

### 输出

```
4

```

