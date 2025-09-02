---
title: "Tennis Rackets"
layout: "post"
diff: 省选/NOI-
pid: CF309D
tag: []
---

# Tennis Rackets

## 题目描述

Professional sport is more than hard work. It also is the equipment, designed by top engineers. As an example, let's take tennis. Not only should you be in great shape, you also need an excellent racket! In this problem your task is to contribute to the development of tennis and to help to design a revolutionary new concept of a racket!

The concept is a triangular racket. Ant it should be not just any triangle, but a regular one. As soon as you've chosen the shape, you need to stretch the net. By the time you came the rocket had $ n $ holes drilled on each of its sides. The holes divide each side into equal $ n+1 $ parts. At that, the $ m $ closest to each apex holes on each side are made for better ventilation only and you cannot stretch the net through them. The next revolutionary idea as to stretch the net as obtuse triangles through the holes, so that for each triangle all apexes lay on different sides. Moreover, you need the net to be stretched along every possible obtuse triangle. That's where we need your help — help us to count the number of triangles the net is going to consist of.

Two triangles are considered to be different if their pictures on the fixed at some position racket are different.

## 输入格式

The first and the only input line contains two integers $ n $ , $ m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF309D/5b67b8a10e3dafb3e26549923a76f8f7d64e31be.png).

## 输出格式

Print a single number — the answer to the problem.

## 说明/提示

For the following picture $ n=8 $ , $ m=2 $ . White circles are the holes for ventilation, red circles — holes for net stretching. One of the possible obtuse triangles is painted red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF309D/5d9eb90db15e7284257442b91590b3953ad87f5e.png)

## 样例 #1

### 输入

```
3 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
4 0

```

### 输出

```
24

```

## 样例 #3

### 输入

```
10 1

```

### 输出

```
210

```

## 样例 #4

### 输入

```
8 4

```

### 输出

```
0

```

