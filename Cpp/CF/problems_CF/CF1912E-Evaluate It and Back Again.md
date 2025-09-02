---
title: "Evaluate It and Back Again"
layout: "post"
diff: 提高+/省选-
pid: CF1912E
tag: []
---

# Evaluate It and Back Again

## 题目描述

Aidan and Nadia are long-time friends with a shared passion for mathematics. Each of them has a favorite number: Aidan's favorite number is $ p $ , and Nadia's is $ q $ .

To commemorate their friendship, their friends want to make a present: a plaque with an arithmetic expression whose value is equal to their favorite numbers. At first glance, it sounds impossible, but the answer is simple: Aidan reads left-to-right, while Nadia reads right-to-left, so the same expression can have different values for them.

For example, if 2023-12-13 is written on the plaque, then Aidan would calculate the result as $ 2023-12-13 = 1998 $ , and Nadia would calculate it as $ 31-21-3202=-3192 $ .

Find an arithmetic expression that, when read left-to-right, evaluates to $ p $ , and, when read right-to-left, evaluates to $ q $ . Its length must be at most $ 1000 $ characters. It's guaranteed that such an expression exists for all valid inputs.

## 输入格式

The first line of the input contains two integers $ p $ and $ q $ ( $ -10^{18} \le p, q \le 10^{18} $ ).

## 输出格式

Print the expression without spaces or line breaks. It can only contain digits 0 through 9, '+', '-', and '\*' characters.

The expression must contain at most $ 1000 $ characters. Leading zeros in numbers are not allowed (the only exception is the notation '0' representing the number $ 0 $ ) in both the expression and its reverse. Use of unary '+' or '-' is not allowed. The expression must be well-formed in both directions. The calculation uses the standard operator precedence.

## 样例 #1

### 输入

```
1998 -3192
```

### 输出

```
2023-12-13
```

## 样例 #2

### 输入

```
413 908
```

### 输出

```
12*34+5
```

