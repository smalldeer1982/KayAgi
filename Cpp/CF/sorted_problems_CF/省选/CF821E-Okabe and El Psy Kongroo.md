---
title: "Okabe and El Psy Kongroo"
layout: "post"
diff: 省选/NOI-
pid: CF821E
tag: []
---

# Okabe and El Psy Kongroo

## 题目描述

Okabe likes to take walks but knows that spies from the Organization could be anywhere; that's why he wants to know how many different walks he can take in his city safely. Okabe's city can be represented as all points $ (x,y) $ such that $ x $ and $ y $ are non-negative. Okabe starts at the origin (point $ (0,0) $ ), and needs to reach the point $ (k,0) $ . If Okabe is currently at the point $ (x,y) $ , in one step he can go to $ (x+1,y+1) $ , $ (x+1,y) $ , or $ (x+1,y-1) $ .

Additionally, there are $ n $ horizontal line segments, the $ i $ -th of which goes from $ x=a_{i} $ to $ x=b_{i} $ inclusive, and is at $ y=c_{i} $ . It is guaranteed that $ a_{1}=0 $ , $ a_{n}<=k<=b_{n} $ , and $ a_{i}=b_{i-1} $ for $ 2<=i<=n $ . The $ i $ -th line segment forces Okabe to walk with $ y $ -value in the range $ 0<=y<=c_{i} $ when his $ x $ value satisfies $ a_{i}<=x<=b_{i} $ , or else he might be spied on. This also means he is required to be under two line segments when one segment ends and another begins.

Okabe now wants to know how many walks there are from the origin to the point $ (k,0) $ satisfying these conditions, modulo $ 10^{9}+7 $ .

## 输入格式

The first line of input contains the integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{18} $ ) — the number of segments and the destination $ x $ coordinate.

The next $ n $ lines contain three space-separated integers $ a_{i} $ , $ b_{i} $ , and $ c_{i} $ ( $ 0<=a_{i}&lt;b_{i}<=10^{18} $ , $ 0<=c_{i}<=15 $ ) — the left and right ends of a segment, and its $ y $ coordinate.

It is guaranteed that $ a_{1}=0 $ , $ a_{n}<=k<=b_{n} $ , and $ a_{i}=b_{i-1} $ for $ 2<=i<=n $ .

## 输出格式

Print the number of walks satisfying the conditions, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/f658e3b02a94b26e1ceda15b31b9ad31fd8decfb.png)The graph above corresponds to sample 1. The possible walks are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/fe5ddffd345db7dbc9811066d89af8164e156a48.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/3c1f68141260e9f0faf2c18d37cc945fe3064803.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/6d7eca326042aa73d0e36209e3dcf0b53f326988.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/b384b506ab41aac1cef00012023de00c92c6ca52.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/808ba51553ca63393b29c100184e006bbe68cb46.png)The graph above corresponds to sample 2. There is only one walk for Okabe to reach $ (3,0) $ . After this, the possible walks are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/c65499d5e0d037bc0e099631cfbdc3b47191ec5c.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/ea64d72ce9bbedf50ad31137fb330842e8e48b14.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/f552304e1f485b618079fd34e72f22adaf988bc2.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/9c27a4273309f39ff98075265ceb3af61e3cd1cb.png)

## 样例 #1

### 输入

```
1 3
0 3 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 6
0 3 0
3 10 2

```

### 输出

```
4

```

