---
title: "The Last Fight Between Human and AI"
layout: "post"
diff: 提高+/省选-
pid: CF676E
tag: []
---

# The Last Fight Between Human and AI

## 题目描述

100 years have passed since the last victory of the man versus computer in Go. Technologies made a huge step forward and robots conquered the Earth! It's time for the final fight between human and robot that will decide the faith of the planet.

The following game was chosen for the fights: initially there is a polynomial

 $ P(x)=a_{n}x^{n}+a_{n-1}x^{n-1}+...+a_{1}x+a_{0}, $  with yet undefined coefficients and the integer $ k $ . Players alternate their turns. At each turn, a player pick some index $ j $ , such that coefficient $ a_{j} $ that stay near $ x^{j} $ is not determined yet and sets it to any value (integer or real, positive or negative, $ 0 $ is also allowed). Computer moves first. The human will be declared the winner if and only if the resulting polynomial will be divisible by $ Q(x)=x-k $ .Polynomial $ P(x) $ is said to be divisible by polynomial $ Q(x) $ if there exists a representation $ P(x)=B(x)Q(x) $ , where $ B(x) $ is also some polynomial.

Some moves have been made already and now you wonder, is it true that human can guarantee the victory if he plays optimally?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=100000,|k|<=10000 $ ) — the size of the polynomial and the integer $ k $ .

The $ i $ -th of the following $ n+1 $ lines contain character '?' if the coefficient near $ x^{i-1} $ is yet undefined or the integer value $ a_{i} $ , if the coefficient is already known ( $ -10000<=a_{i}<=10000 $ ). Each of integers $ a_{i} $ (and even $ a_{n} $ ) may be equal to $ 0 $ .

Please note, that it's not guaranteed that you are given the position of the game where it's computer's turn to move.

## 输出格式

Print "Yes" (without quotes) if the human has winning strategy, or "No" (without quotes) otherwise.

## 说明/提示

In the first sample, computer set $ a_{0} $ to $ -1 $ on the first move, so if human can set coefficient $ a_{1} $ to $ 0.5 $ and win.

In the second sample, all coefficients are already set and the resulting polynomial is divisible by $ x-100 $ , so the human has won.

## 样例 #1

### 输入

```
1 2
-1
?

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2 100
-10000
0
1

```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
4 5
?
1
?
1
?

```

### 输出

```
No
```

