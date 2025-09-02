---
title: "Beautiful Set"
layout: "post"
diff: 提高+/省选-
pid: CF364C
tag: []
---

# Beautiful Set

## 题目描述

We'll call a set of positive integers $ a $ beautiful if the following condition fulfills: for any prime $ p $ , if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF364C/de99426f3fbaa26518074daf10b8f9b390d1a140.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF364C/04ac8a5d83c7f06e74fe73e1ed271d0d74dd42cb.png). In other words, if one number from the set is divisible by prime $ p $ , then at least half of numbers from the set is divisible by $ p $ .

Your task is to find any beautiful set, where the number of elements is equal to $ k $ and each element doesn't exceed $ 2k^{2} $ .

## 输入格式

The first line contains integer $ k $ ( $ 10<=k<=5000 $ ) that shows how many numbers the required beautiful set should have.

## 输出格式

In the first line print $ k $ space-separated integers that are a beautiful set. If there are multiple such sets, you are allowed to print any of them.

## 样例 #1

### 输入

```
10

```

### 输出

```
16 18 24 27 36 48 54 72 108 144 

```

