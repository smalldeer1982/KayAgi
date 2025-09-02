---
title: "Mike and distribution"
layout: "post"
diff: 提高+/省选-
pid: CF798D
tag: []
---

# Mike and distribution

## 题目描述

Mike has always been thinking about the harshness of social inequality. He's so obsessed with it that sometimes it even affects him while solving problems. At the moment, Mike has two sequences of positive integers $ A=[a_{1},a_{2},...,a_{n}] $ and $ B=[b_{1},b_{2},...,b_{n}] $ of length $ n $ each which he uses to ask people some quite peculiar questions.

To test you on how good are you at spotting inequality in life, he wants you to find an "unfair" subset of the original sequence. To be more precise, he wants you to select $ k $ numbers $ P=[p_{1},p_{2},...,p_{k}] $ such that $ 1<=p_{i}<=n $ for $ 1<=i<=k $ and elements in $ P $ are distinct. Sequence $ P $ will represent indices of elements that you'll select from both sequences. He calls such a subset $ P $ "unfair" if and only if the following conditions are satisfied: $ 2·(a_{p1}+...+a_{pk}) $ is greater than the sum of all elements from sequence $ A $ , and $ 2·(b_{p1}+...+b_{pk}) $ is greater than the sum of all elements from the sequence $ B $ . Also, $ k $ should be smaller or equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF798D/063c1ec1fbcd406bc727adffa50b1420ca2cf4be.png) because it will be to easy to find sequence $ P $ if he allowed you to select too many elements!

Mike guarantees you that a solution will always exist given the conditions described above, so please help him satisfy his curiosity!

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of elements in the sequences.

On the second line there are $ n $ space-separated integers $ a_{1},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of sequence $ A $ .

On the third line there are also $ n $ space-separated integers $ b_{1},...,b_{n} $ ( $ 1<=b_{i}<=10^{9} $ ) — elements of sequence $ B $ .

## 输出格式

On the first line output an integer $ k $ which represents the size of the found subset. $ k $ should be less or equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF798D/063c1ec1fbcd406bc727adffa50b1420ca2cf4be.png).

On the next line print $ k $ integers $ p_{1},p_{2},...,p_{k} $ ( $ 1<=p_{i}<=n $ ) — the elements of sequence $ P $ . You can print the numbers in any order you want. Elements in sequence $ P $ should be distinct.

## 样例 #1

### 输入

```
5
8 7 4 8 3
4 2 5 3 7

```

### 输出

```
3
1 4 5

```

