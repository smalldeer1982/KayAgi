---
title: "Economy Game"
layout: "post"
diff: 普及/提高-
pid: CF681B
tag: []
---

# Economy Game

## 题目描述

Kolya is developing an economy simulator game. His most favourite part of the development process is in-game testing. Once he was entertained by the testing so much, that he found out his game-coin score become equal to $ 0 $ .

Kolya remembers that at the beginning of the game his game-coin score was equal to $ n $ and that he have bought only some houses (for $ 1234567 $ game-coins each), cars (for $ 123456 $ game-coins each) and computers (for $ 1234 $ game-coins each).

Kolya is now interested, whether he could have spent all of his initial $ n $ game-coins buying only houses, cars and computers or there is a bug in the game. Formally, is there a triple of non-negative integers $ a $ , $ b $ and $ c $ such that $ a×1234567+b×123456+c×1234=n $ ?

Please help Kolya answer this question.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=10^{9} $ ) — Kolya's initial game-coin score.

## 输出格式

Print "YES" (without quotes) if it's possible that Kolya spent all of his initial $ n $ coins buying only houses, cars and computers. Otherwise print "NO" (without quotes).

## 说明/提示

In the first sample, one of the possible solutions is to buy one house, one car and one computer, spending $ 1234567+123456+1234=1359257 $ game-coins in total.

## 样例 #1

### 输入

```
1359257

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
17851817

```

### 输出

```
NO
```

