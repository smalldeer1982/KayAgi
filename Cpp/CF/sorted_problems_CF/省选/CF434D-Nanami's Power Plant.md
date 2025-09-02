---
title: "Nanami's Power Plant"
layout: "post"
diff: 省选/NOI-
pid: CF434D
tag: []
---

# Nanami's Power Plant

## 题目描述

Nanami likes playing games, and is also really good at it. This day she was playing a new game which involved operating a power plant. Nanami's job is to control the generators in the plant and produce maximum output.

There are $ n $ generators in the plant. Each generator should be set to a generating level. Generating level is an integer (possibly zero or negative), the generating level of the $ i $ -th generator should be between $ l_{i} $ and $ r_{i} $ (both inclusive). The output of a generator can be calculated using a certain quadratic function $ f(x) $ , where $ x $ is the generating level of the generator. Each generator has its own function, the function of the $ i $ -th generator is denoted as $ f_{i}(x) $ .

However, there are $ m $ further restrictions to the generators. Let the generating level of the $ i $ -th generator be $ x_{i} $ . Each restriction is of the form $ x_{u}<=x_{v}+d $ , where $ u $ and $ v $ are IDs of two different generators and $ d $ is an integer.

Nanami found the game tedious but giving up is against her creed. So she decided to have a program written to calculate the answer for her (the maximum total output of generators). Somehow, this became your job.

## 输入格式

The first line contains two integers $ n $ and $ m (1<=n<=50; 0<=m<=100) $ — the number of generators and the number of restrictions.

Then follow $ n $ lines, each line contains three integers $ a_{i} $ , $ b_{i} $ , and $ c_{i} (|a_{i}|<=10; |b_{i}|,|c_{i}|<=1000) $ — the coefficients of the function $ f_{i}(x) $ . That is, $ f_{i}(x)=a_{i}x^{2}+b_{i}x+c_{i} $ .

Then follow another $ n $ lines, each line contains two integers $ l_{i} $ and $ r_{i} (-100<=l_{i}<=r_{i}<=100) $ .

Then follow $ m $ lines, each line contains three integers $ u_{i} $ , $ v_{i} $ , and $ d_{i} (1<=u_{i},v_{i}<=n; u_{i}≠v_{i}; |d_{i}|<=200) $ , describing a restriction. The $ i $ -th restriction is $ x_{ui}<=x_{vi}+d_{i} $ .

## 输出格式

Print a single line containing a single integer — the maximum output of all the generators. It is guaranteed that there exists at least one valid configuration.

## 说明/提示

In the first sample, $ f_{1}(x)=x $ , $ f_{2}(x)=x+1 $ , and $ f_{3}(x)=x+2 $ , so we are to maximize the sum of the generating levels. The restrictions are $ x_{1}<=x_{2} $ , $ x_{2}<=x_{3} $ , and $ x_{3}<=x_{1} $ , which gives us $ x_{1}=x_{2}=x_{3} $ . The optimal configuration is $ x_{1}=x_{2}=x_{3}=2 $ , which produces an output of 9.

In the second sample, restrictions are equal to $ |x_{i}-x_{i+1}|<=3 $ for $ 1<=i&lt;n $ . One of the optimal configurations is $ x_{1}=1 $ , $ x_{2}=4 $ , $ x_{3}=5 $ , $ x_{4}=8 $ and $ x_{5}=7 $ .

## 样例 #1

### 输入

```
3 3
0 1 0
0 1 1
0 1 2
0 3
1 2
-100 100
1 2 0
2 3 0
3 1 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5 8
1 -8 20
2 -4 0
-1 10 -10
0 1 0
0 -1 1
1 9
1 4
0 10
3 11
7 9
2 1 3
1 2 3
2 3 3
3 2 3
3 4 3
4 3 3
4 5 3
5 4 3

```

### 输出

```
46

```

