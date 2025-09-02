---
title: "PolandBall and Many Other Balls"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF755G
tag: []
---

# PolandBall and Many Other Balls

## 题目描述

PolandBall is standing in a row with Many Other Balls. More precisely, there are exactly $ n $ Balls. Balls are proud of their home land — and they want to prove that it's strong.

The Balls decided to start with selecting exactly $ m $ groups of Balls, each consisting either of single Ball or two neighboring Balls. Each Ball can join no more than one group.

The Balls really want to impress their Enemies. They kindly asked you to calculate number of such divisions for all $ m $ where $ 1<=m<=k $ . Output all these values modulo $ 998244353 $ , the Enemies will be impressed anyway.

## 输入格式

There are exactly two numbers $ n $ and $ k $ ( $ 1<=n<=10^{9} $ , $ 1<=k&lt;2^{15} $ ), denoting the number of Balls and the maximim number of groups, respectively.

## 输出格式

You should output a sequence of $ k $ values. The $ i $ -th of them should represent the sought number of divisions into exactly $ i $ groups, according to PolandBall's rules.

## 说明/提示

In the first sample case we can divide Balls into groups as follows:

 $ {1} $ , $ {2} $ , $ {3} $ , $ {12} $ , $ {23} $ .

 $ {12}{3} $ , $ {1}{23} $ , $ {1}{2} $ , $ {1}{3} $ , $ {2}{3} $ .

 $ {1}{2}{3} $ .

Therefore, output is: 5 5 1.

## 样例 #1

### 输入

```
3 3

```

### 输出

```
5 5 1 
```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
1 
```

## 样例 #3

### 输入

```
5 10

```

### 输出

```
9 25 25 9 1 0 0 0 0 0 
```

