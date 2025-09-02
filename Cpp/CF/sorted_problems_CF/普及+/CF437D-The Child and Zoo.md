---
title: "The Child and Zoo"
layout: "post"
diff: 普及+/提高
pid: CF437D
tag: []
---

# The Child and Zoo

## 题目描述

Of course our child likes walking in a zoo. The zoo has $ n $ areas, that are numbered from $ 1 $ to $ n $ . The $ i $ -th area contains $ a_{i} $ animals in it. Also there are $ m $ roads in the zoo, and each road connects two distinct areas. Naturally the zoo is connected, so you can reach any area of the zoo from any other area using the roads.

Our child is very smart. Imagine the child want to go from area $ p $ to area $ q $ . Firstly he considers all the simple routes from $ p $ to $ q $ . For each route the child writes down the number, that is equal to the minimum number of animals among the route areas. Let's denote the largest of the written numbers as $ f(p,q) $ . Finally, the child chooses one of the routes for which he writes down the value $ f(p,q) $ .

After the child has visited the zoo, he thinks about the question: what is the average value of $ f(p,q) $ for all pairs $ p,q $ $ (p≠q) $ ? Can you answer his question?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ ; $ 0<=m<=10^{5} $ ). The second line contains $ n $ integers: $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{5} $ ). Then follow $ m $ lines, each line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n $ ; $ x_{i}≠y_{i} $ ), denoting the road between areas $ x_{i} $ and $ y_{i} $ .

All roads are bidirectional, each pair of areas is connected by at most one road.

## 输出格式

Output a real number — the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/a340d81982090a2c7886ba528802299513594a80.png).

The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-4} $ .

## 说明/提示

Consider the first sample. There are $ 12 $ possible situations:

- $ p=1,q=3,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=4,q=3,f(p,q)=30 $ .
- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=4,f(p,q)=20 $ .
- $ p=4,q=1,f(p,q)=10 $ .

Another $ 6 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/58ce2a366aa42eff918fbf0b8467c9ccbcf9601e.png).

Consider the second sample. There are $ 6 $ possible situations:

- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=1,q=3,f(p,q)=10 $ .

Another $ 3 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/ecc6155982485fab22801f99d7326020bda06f7b.png).

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 3
2 3
4 3

```

### 输出

```
16.666667

```

## 样例 #2

### 输入

```
3 3
10 20 30
1 2
2 3
3 1

```

### 输出

```
13.333333

```

## 样例 #3

### 输入

```
7 8
40 20 10 30 20 50 40
1 2
2 3
3 4
4 5
5 6
6 7
1 4
5 7

```

### 输出

```
18.571429

```

