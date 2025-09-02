---
title: "Encryption (easy)"
layout: "post"
diff: 普及-
pid: CF958C1
tag: ['枚举', '前缀和']
---

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 输入格式

The first line of the input contains two space-separated integer $ N $ and $ p $ ( $ 2<=N<=100000 $ , $ 2<=p<=10000 $ ) – the number of elements in $ A $ , and the modulo for computing scores, respectively.

The second line contains $ N $ space-separated integers which are the elements of $ A $ . Each integer is from the interval $ [1,1000000] $ .

## 输出格式

Output the number $ S $ as described in the problem statement.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12

```

### 输出

```
13

```

