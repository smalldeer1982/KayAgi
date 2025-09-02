---
title: "Pasha and Hamsters"
layout: "post"
diff: 入门
pid: CF421A
tag: []
---

# Pasha and Hamsters

## 题目描述

Pasha has two hamsters: Arthur and Alexander. Pasha put $ n $ apples in front of them. Pasha knows which apples Arthur likes. Similarly, Pasha knows which apples Alexander likes. Pasha doesn't want any conflict between the hamsters (as they may like the same apple), so he decided to distribute the apples between the hamsters on his own. He is going to give some apples to Arthur and some apples to Alexander. It doesn't matter how many apples each hamster gets but it is important that each hamster gets only the apples he likes. It is possible that somebody doesn't get any apples.

Help Pasha distribute all the apples between the hamsters. Note that Pasha wants to distribute all the apples, not just some of them.

## 输入格式

The first line contains integers $ n $ , $ a $ , $ b $ $ (1<=n<=100; 1<=a,b<=n) $ — the number of apples Pasha has, the number of apples Arthur likes and the number of apples Alexander likes, correspondingly.

The next line contains $ a $ distinct integers — the numbers of the apples Arthur likes. The next line contains $ b $ distinct integers — the numbers of the apples Alexander likes.

Assume that the apples are numbered from $ 1 $ to $ n $ . The input is such that the answer exists.

## 输出格式

Print $ n $ characters, each of them equals either 1 or 2. If the $ i $ -h character equals 1, then the $ i $ -th apple should be given to Arthur, otherwise it should be given to Alexander. If there are multiple correct answers, you are allowed to print any of them.

## 样例 #1

### 输入

```
4 2 3
1 2
2 3 4

```

### 输出

```
1 1 2 2

```

## 样例 #2

### 输入

```
5 5 2
3 4 1 2 5
2 3

```

### 输出

```
1 1 1 1 1

```

