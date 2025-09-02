---
title: "Vasya and Chocolate"
layout: "post"
diff: 入门
pid: CF1065A
tag: []
---

# Vasya and Chocolate

## 题目描述

There is a special offer in Vasya's favourite supermarket: if the customer buys $ a $ chocolate bars, he or she may take $ b $ additional bars for free. This special offer can be used any number of times.

Vasya currently has $ s $ roubles, and he wants to get as many chocolate bars for free. Each chocolate bar costs $ c $ roubles. Help Vasya to calculate the maximum possible number of chocolate bars he can get!

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of testcases.

Each of the next $ t $ lines contains four integers $ s, a, b, c~(1 \le s, a, b, c \le 10^9) $ — the number of roubles Vasya has, the number of chocolate bars you have to buy to use the special offer, the number of bars you get for free, and the cost of one bar, respectively.

## 输出格式

Print $ t $ lines. $ i $ -th line should contain the maximum possible number of chocolate bars Vasya can get in $ i $ -th test.

## 说明/提示

In the first test of the example Vasya can buy $ 9 $ bars, get $ 3 $ for free, buy another bar, and so he will get $ 13 $ bars.

In the second test Vasya buys $ 1000000000 $ bars and gets $ 1000000000000000000 $ for free. So he has $ 1000000001000000000 $ bars.

## 样例 #1

### 输入

```
2
10 3 1 1
1000000000 1 1000000000 1

```

### 输出

```
13
1000000001000000000

```

