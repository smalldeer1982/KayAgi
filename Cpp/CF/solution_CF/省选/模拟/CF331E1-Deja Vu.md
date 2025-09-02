# Deja Vu

## 题目描述

Everybody knows that we have been living in the Matrix for a long time. And in the new seventh Matrix the world is ruled by beavers.

So let's take beaver Neo. Neo has so-called "deja vu" outbursts when he gets visions of events in some places he's been at or is going to be at. Let's examine the phenomenon in more detail.

We can say that Neo's city is represented by a directed graph, consisting of $ n $ shops and $ m $ streets that connect the shops. No two streets connect the same pair of shops (besides, there can't be one street from A to B and one street from B to A). No street connects a shop with itself. As Neo passes some streets, he gets visions. No matter how many times he passes street $ k $ , every time he will get the same visions in the same order. A vision is a sequence of shops.

We know that Neo is going to get really shocked if he passes the way from some shop $ a $ to some shop $ b $ , possible coinciding with $ a $ , such that the list of visited shops in the real life and in the visions coincide.

Suggest beaver Neo such path of non-zero length. Or maybe you can even count the number of such paths modulo $ 1000000007 $ $ (10^{9}+7) $ ?..

## 说明/提示

The input in both samples are the same. The first sample contains the answer to the first subproblem, the second sample contains the answer to the second subproblem.

## 样例 #1

### 输入

```
6 6
1 2 2 1 2
2 3 1 3
3 4 2 4 5
4 5 0
5 3 1 3
6 1 1 6
```

### 输出

```
4
6 1 2 3
```

## 样例 #2

### 输入

```
6 6
1 2 2 1 2
2 3 1 3
3 4 2 4 5
4 5 0
5 3 1 3
6 1 1 6
```

### 输出

```
1
2
1
1
2
1
1
2
1
1
2
1```

# 题解

## 作者：EuphoricStar (赞：1)

考虑一条好的路径 $x \to y$ 中一定至少存在一条边 $(u, v)$，满足这条边的序列 $a$ 存在一个 $j \in [1, |a| - 1]$，满足 $a_j = u, a_{j + 1} = v$，就是说 $a$ 包含一对相邻的 $(u, v)$。

那么我们可以枚举这样的边 $u \to v$，将这条边的序列 $a$ 分成 $[\ldots, u], [v, \ldots]$ 的部分，然后两端独立地分别扩展，直到当前序列长度等于已经经过的点数。

找这样的一条路径复杂度 $O(nm)$，[可以通过 E1](https://codeforces.com/contest/331/submission/238342028)。

---

