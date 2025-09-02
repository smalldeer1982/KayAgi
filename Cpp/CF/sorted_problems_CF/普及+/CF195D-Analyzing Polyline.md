---
title: "Analyzing Polyline"
layout: "post"
diff: 普及+/提高
pid: CF195D
tag: []
---

# Analyzing Polyline

## 题目描述

As Valeric and Valerko were watching one of the last Euro Championship games in a sports bar, they broke a mug. Of course, the guys paid for it but the barman said that he will let them watch football in his bar only if they help his son complete a programming task. The task goes like that.

Let's consider a set of functions of the following form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF195D/bc3a6f827f49bee100d9da6adde48766963384ee.png) Let's define a sum of $ n $ functions $ y_{1}(x),...,y_{n}(x) $ of the given type as function $ s(x)=y_{1}(x)+...+y_{n}(x) $ for any $ x $ . It's easy to show that in this case the graph $ s(x) $ is a polyline. You are given $ n $ functions of the given type, your task is to find the number of angles that do not equal 180 degrees, in the graph $ s(x) $ , that is the sum of the given functions.Valeric and Valerko really want to watch the next Euro Championship game, so they asked you to help them.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the number of functions. Each of the following $ n $ lines contains two space-separated integer numbers $ k_{i},b_{i} $ $ (-10^{9}<=k_{i},b_{i}<=10^{9}) $ that determine the $ i $ -th function.

## 输出格式

Print a single number — the number of angles that do not equal 180 degrees in the graph of the polyline that equals the sum of the given functions.

## 样例 #1

### 输入

```
1
1 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 0
0 2
-1 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
-2 -4
1 7
-5 1

```

### 输出

```
3

```

