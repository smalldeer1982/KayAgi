---
title: "Patrick and Shopping"
layout: "post"
diff: 入门
pid: CF599A
tag: []
---

# Patrick and Shopping

## 题目描述

Today Patrick waits for a visit from his friend Spongebob. To prepare for the visit, Patrick needs to buy some goodies in two stores located near his house. There is a $ d_{1} $ meter long road between his house and the first shop and a $ d_{2} $ meter long road between his house and the second shop. Also, there is a road of length $ d_{3} $ directly connecting these two shops to each other. Help Patrick calculate the minimum distance that he needs to walk in order to go to both shops and return to his house.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/5683c1a51ecc7bb98c898443df309a2210ffe932.png)Patrick always starts at his house. He should visit both shops moving only along the three existing roads and return back to his house. He doesn't mind visiting the same shop or passing the same road multiple times. The only goal is to minimize the total distance traveled.

## 输入格式

The first line of the input contains three integers $ d_{1} $ , $ d_{2} $ , $ d_{3} $ ( $ 1<=d_{1},d_{2},d_{3}<=10^{8} $ ) — the lengths of the paths.

- $ d_{1} $ is the length of the path connecting Patrick's house and the first shop;
- $ d_{2} $ is the length of the path connecting Patrick's house and the second shop;
- $ d_{3} $ is the length of the path connecting both shops.

## 输出格式

Print the minimum distance that Patrick will have to walk in order to visit both shops and return to his house.

## 说明/提示

The first sample is shown on the picture in the problem statement. One of the optimal routes is: house ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) first shop ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) second shop ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) house.

In the second sample one of the optimal routes is: house ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) first shop ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) house ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) second shop ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599A/355fee5161a1808ee95ea5dc6d815d4071657131.png) house.

## 样例 #1

### 输入

```
10 20 30

```

### 输出

```
60

```

## 样例 #2

### 输入

```
1 1 5

```

### 输出

```
4

```

