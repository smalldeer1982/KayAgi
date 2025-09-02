---
title: "Before Exam"
layout: "post"
diff: 普及+/提高
pid: CF119B
tag: []
---

# Before Exam

## 题目描述

Vasya is about to take his first university exam in about several minutes. And it's not just some ordinary exam, it's on mathematical analysis. Of course, right now Vasya can only think of one thing: what the result of his talk with the examiner will be...

To prepare for the exam, one has to study proofs of $ n $ theorems. It is known that there will be $ k $ examination cards on the exam and each card contains ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/a79102df34bfb4ac36a7e7ca20435b44cb7b516b.png) distinct theorems. Besides, no theorem is mentioned in more than one card (that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/eaf3adf2c359f646a89e2e39756bfd54a8c45754.png) theorems won't be mentioned in any card). During the exam several students may get the same card.

We do not know the exact way theorems are distributed by cards, however the students that took the exam before Vasya told him what theorems their cards contained. Vasya evaluates his level of proficiency in the $ i $ -th theorem by some number $ a_{i} $ . The level of proficiency in some card is the average of the levels of proficiency in the theorems that are included in the card. Now Vasya wants to know the minimally and maximally possible levels of his proficiency in the card he gets on the exam. Vasya wants to determine it by the data he has collected from other students. Unfortunately, Vasya has no time left to do the math and he asked you to help him.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=100 $ ) — the number of theorems and the number of cards correspondingly. The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=100 $ ), the $ i $ -th number ( $ 1<=i<=n $ ) corresponds to Vasya's proficiency in the $ i $ -th theorem.

The third line contains number $ q $ ( $ 0<=q<=100 $ ) — the number of people that have taken the exam before Vasya. Each of the following $ q $ lines contains the description of a student's card: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/a79102df34bfb4ac36a7e7ca20435b44cb7b516b.png) integers from $ 1 $ to $ n $ inclusive. They are the numbers of theorems included in the card in the order in which they are enumerated in the input data. The numbers are given in an arbitrary order. It is guaranteed that the given cards are valid (that is, that all theorems in one card are different and that different people get cards that either don't contain the same theorems or coincide up to the theorems' permutation).

## 输出格式

Print two real numbers, representing Vasya's minimum and maximum proficiency in the card he will get on the exam. The absolute or relative error should not exceed $ 10^{-6} $ .

## 说明/提示

Let's analyze the first sample. Vasya's proficiency in the cards whose content he already knows equals $ 6 $ and $ 15.5 $ correspondingly. The three theorems that are left are only enough to make one exam card. If we consider all possible variants of theorems included in the card we can see that in the best case scenario Vasya gets the card that contains theorems $ 4 $ and $ 7 $ (his proficiency would equal $ 15.5 $ ) and in the worst case scenario he gets theorems $ 3 $ and $ 5 $ (his proficiency would equal $ 5 $ ).

The $ ⌊\ x⌋ $ operation denotes taking integer part of real number $ x $ (rounding down).

## 样例 #1

### 输入

```
7 3
7 15 0 19 10 5 12
2
1 6
7 4

```

### 输出

```
5.0000000000 15.5000000000
```

## 样例 #2

### 输入

```
4 2
10 8 1 17
2
2 3
3 2

```

### 输出

```
4.5000000000 13.5000000000
```

