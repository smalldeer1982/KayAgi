---
title: "Remainders Game"
layout: "post"
diff: 普及+/提高
pid: CF687B
tag: []
---

# Remainders Game

## 题目描述

Today Pari and Arya are playing a game called Remainders.

Pari chooses two positive integer $ x $ and $ k $ , and tells Arya $ k $ but not $ x $ . Arya have to find the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png). There are $ n $ ancient numbers $ c_{1},c_{2},...,c_{n} $ and Pari has to tell Arya ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/d6826eab3568be14654e0e163000c670f1c64e14.png) if Arya wants. Given $ k $ and the ancient values, tell us if Arya has a winning strategy independent of value of $ x $ or not. Formally, is it true that Arya can understand the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png) for any positive integer $ x $ ?

Note, that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means the remainder of $ x $ after dividing it by $ y $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n,\ k<=1000000 $ ) — the number of ancient integers and value $ k $ that is chosen by Pari.

The second line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 1<=c_{i}<=1000000 $ ).

## 输出格式

Print "Yes" (without quotes) if Arya has a winning strategy independent of value of $ x $ , or "No" (without quotes) otherwise.

## 说明/提示

In the first sample, Arya can understand ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/b93dce9b9ef400fa12cce1ab52784e3449739731.png) because $ 5 $ is one of the ancient numbers.

In the second sample, Arya can't be sure what ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/34daaca50b46751e5d9e1271dc07f186fd9fd248.png) is. For example $ 1 $ and $ 7 $ have the same remainders after dividing by $ 2 $ and $ 3 $ , but they differ in remainders after dividing by $ 7 $ .

## 样例 #1

### 输入

```
4 5
2 3 5 12

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2 7
2 3

```

### 输出

```
No

```

