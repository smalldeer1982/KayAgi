---
title: "Square Difference"
layout: "post"
diff: 普及-
pid: CF1033B
tag: []
---

# Square Difference

## 题目描述

Alice has a lovely piece of cloth. It has the shape of a square with a side of length $ a $ centimeters. Bob also wants such piece of cloth. He would prefer a square with a side of length $ b $ centimeters (where $ b < a $ ). Alice wanted to make Bob happy, so she cut the needed square out of the corner of her piece and gave it to Bob. Now she is left with an ugly L shaped cloth (see pictures below).

Alice would like to know whether the area of her cloth expressed in square centimeters is [prime.](https://en.wikipedia.org/wiki/Prime_number) Could you help her to determine it?

## 输入格式

The first line contains a number $ t $ ( $ 1 \leq t \leq 5 $ ) — the number of test cases.

Each of the next $ t $ lines describes the $ i $ -th test case. It contains two integers $ a $ and $ b~(1 \leq b < a \leq 10^{11}) $ — the side length of Alice's square and the side length of the square that Bob wants.

## 输出格式

Print $ t $ lines, where the $ i $ -th line is the answer to the $ i $ -th test case. Print "YES" (without quotes) if the area of the remaining piece of cloth is prime, otherwise print "NO".

You can print each letter in an arbitrary case (upper or lower).

## 说明/提示

The figure below depicts the first test case. The blue part corresponds to the piece which belongs to Bob, and the red part is the piece that Alice keeps for herself. The area of the red part is $ 6^2 - 5^2 = 36 - 25 = 11 $ , which is prime, so the answer is "YES".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/26aa17f955334a29eef8994b7c5af8ed29b66689.png)In the second case, the area is $ 16^2 - 13^2 = 87 $ , which is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/bb700dc40c3e1b73968059e8f9c3fba6a4d8a953.png)In the third case, the area of the remaining piece is $ 61690850361^2 - 24777622630^2 = 3191830435068605713421 $ . This number is not prime because $ 3191830435068605713421 = 36913227731 \cdot 86468472991  $ .

In the last case, the area is $ 34^2 - 33^2 = 67 $ .

## 样例 #1

### 输入

```
4
6 5
16 13
61690850361 24777622630
34 33

```

### 输出

```
YES
NO
NO
YES

```

