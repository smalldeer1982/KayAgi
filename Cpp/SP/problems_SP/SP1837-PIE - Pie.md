---
title: "PIE - Pie"
layout: "post"
diff: 普及/提高-
pid: SP1837
tag: []
---

# PIE - Pie

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1837/20a8316f0ed11149087122427b861d870d28a07f.png)

 My birthday is coming up and traditionally I'm serving pie. Not just one pie, no, I have a number _N_ of them, of various tastes and of various sizes. _F_ of my friends are coming to my party and each of them gets a piece of pie. This should be one piece of one pie, not several small pieces since that looks messy. This piece can be one whole pie though.

 My friends are very annoying and if one of them gets a bigger piece than the others, they start complaining. Therefore all of them should get equally sized (but not necessarily equally shaped) pieces, even if this leads to some pie getting spoiled (which is better than spoiling the party). Of course, I want a piece of pie for myself too, and that piece should also be of the same size.

 What is the largest possible piece size all of us can get? All the pies are cylindrical in shape and they all have the same height 1, but the radii of the pies can be different.

## 输入格式

 One line with a positive integer: the number of test cases. Then for each test case:

- One line with two integers _N_ and _F_ with 1 ≤ _N, F_ ≤ 10000: the number of pies and the number of friends.
- One line with _N_ integers _r $ _{i} $_  with 1 ≤ _r $ _{i} $_  ≤ 10000: the radii of the pies.

## 输出格式

 For each test case, output one line with the largest possible volume _V_ such that me and my friends can all get a pie piece of size _V_. The answer should be given as a floating point number with an absolute error of at most 10 $ ^{-3} $ .

## 样例 #1

### 输入

```
3
3 3
4 3 3
1 24
5
10 5
1 4 2 3 4 5 6 5 4 2
```

### 输出

```
25.1327
3.1416
50.2655
```

