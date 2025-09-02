---
title: "Shave Beaver!"
layout: "post"
diff: 提高+/省选-
pid: CF331B2
tag: []
---

# Shave Beaver!

## 题目描述

The Smart Beaver has recently designed and built an innovative nanotechnologic all-purpose beaver mass shaving machine, "Beavershave 5000". Beavershave 5000 can shave beavers by families! How does it work? Very easily!

There are $ n $ beavers, each of them has a unique id from 1 to $ n $ . Consider a permutation $ a_{1},a_{2},...,a_{n} $ of $ n $ these beavers. Beavershave 5000 needs one session to shave beavers with ids from $ x $ to $ y $ (inclusive) if and only if there are such indices $ i_{1}<i_{2}<...<i_{k} $ , that $ a_{i1}=x $ , $ a_{i2}=x+1 $ , ..., $ a_{ik-1}=y-1 $ , $ a_{ik}=y $ . And that is really convenient. For example, it needs one session to shave a permutation of beavers $ 1,2,3,...,n $ .

If we can't shave beavers from $ x $ to $ y $ in one session, then we can split these beavers into groups $ [x,p_{1}] $ , $ [p_{1}+1,p_{2}] $ , ..., $ [p_{m}+1,y] $ $ (x<=p_{1}<p_{2}<...<p_{m}<y) $ , in such a way that the machine can shave beavers in each group in one session. But then Beavershave 5000 needs $ m+1 $ working sessions to shave beavers from $ x $ to $ y $ .

All beavers are restless and they keep trying to swap. So if we consider the problem more formally, we can consider queries of two types:

- what is the minimum number of sessions that Beavershave 5000 needs to shave beavers with ids from $ x $ to $ y $ , inclusive?
- two beavers on positions $ x $ and $ y $ (the beavers $ a_{x} $ and $ a_{y} $ ) swapped.

You can assume that any beaver can be shaved any number of times.

## 输入格式

The first line contains integer $ n $ — the total number of beavers, $ 2<=n $ . The second line contains $ n $ space-separated integers — the initial beaver permutation.

The third line contains integer $ q $ — the number of queries, $ 1<=q<=10^{5} $ . The next $ q $ lines contain the queries. Each query $ i $ looks as $ p_{i} $ $ x_{i} $ $ y_{i} $ , where $ p_{i} $ is the query type ( $ 1 $ is to shave beavers from $ x_{i} $ to $ y_{i} $ , inclusive, $ 2 $ is to swap beavers on positions $ x_{i} $ and $ y_{i} $ ). All queries meet the condition: $ 1<=x_{i}<y_{i}<=n $ .

- to get 30 points, you need to solve the problem with constraints: $ n<=100 $ (subproblem B1);
- to get 100 points, you need to solve the problem with constraints: $ n<=3·10^{5} $ (subproblems B1+B2).

Note that the number of queries $ q $ is limited $ 1<=q<=10^{5} $ in both subproblem B1 and subproblem B2.

## 输出格式

For each query with $ p_{i}=1 $ , print the minimum number of Beavershave 5000 sessions.

## 样例 #1

### 输入

```
5
1 3 4 2 5
6
1 1 5
1 3 4
2 2 3
1 1 5
2 1 5
1 1 5

```

### 输出

```
2
1
3
5

```

