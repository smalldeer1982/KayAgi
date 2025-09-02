---
title: "Tavas and Malekas"
layout: "post"
diff: 普及+/提高
pid: CF535D
tag: []
---

# Tavas and Malekas

## 题目描述

Tavas is a strange creature. Usually "zzz" comes out of people's mouth while sleeping, but string $ s $ of length $ n $ comes out from Tavas' mouth instead.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535D/edec2eae8d180d77009c457fa18d1007b3d9ea05.png)Today Tavas fell asleep in Malekas' place. While he was sleeping, Malekas did a little process on $ s $ . Malekas has a favorite string $ p $ . He determined all positions $ x_{1}&lt;x_{2}&lt;...&lt;x_{k} $ where $ p $ matches $ s $ . More formally, for each $ x_{i} $ ( $ 1<=i<=k $ ) he condition $ s_{xi}s_{xi}+1...\ s_{xi}+|p|-1=p $ is fullfilled.

Then Malekas wrote down one of subsequences of $ x_{1},x_{2},...\ x_{k} $ (possibly, he didn't write anything) on a piece of paper. Here a sequence $ b $ is a subsequence of sequence $ a $ if and only if we can turn $ a $ into $ b $ by removing some of its elements (maybe no one of them or all).

After Tavas woke up, Malekas told him everything. He couldn't remember string $ s $ , but he knew that both $ p $ and $ s $ only contains lowercase English letters and also he had the subsequence he had written on that piece of paper.

Tavas wonders, what is the number of possible values of $ s $ ? He asked SaDDas, but he wasn't smart enough to solve this. So, Tavas asked you to calculate this number for him.

Answer can be very large, so Tavas wants you to print the answer modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ , the length of $ s $ and the length of the subsequence Malekas wrote down ( $ 1<=n<=10^{6} $ and $ 0<=m<=n-|p|+1 $ ).

The second line contains string $ p $ ( $ 1<=|p|<=n $ ).

The next line contains $ m $ space separated integers $ y_{1},y_{2},...,y_{m} $ , Malekas' subsequence ( $ 1<=y_{1}&lt;y_{2}&lt;...&lt;y_{m}<=n-|p|+1 $ ).

## 输出格式

In a single line print the answer modulo $ 1000000007 $ .

## 说明/提示

In the first sample test all strings of form "ioioi?" where the question mark replaces arbitrary English letter satisfy.

Here $ |x| $ denotes the length of string x.

Please note that it's possible that there is no such string (answer is 0).

## 样例 #1

### 输入

```
6 2
ioi
1 3

```

### 输出

```
26

```

## 样例 #2

### 输入

```
5 2
ioi
1 2

```

### 输出

```
0

```

