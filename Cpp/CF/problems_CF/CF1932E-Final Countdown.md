---
title: "Final Countdown"
layout: "post"
diff: 普及/提高-
pid: CF1932E
tag: ['数学', '高精度']
---

# Final Countdown

## 题目描述

You are in a nuclear laboratory that is about to explode and destroy the Earth. You must save the Earth before the final countdown reaches zero.

The countdown consists of $ n $ ( $ 1 \le n \le 4 \cdot 10^5 $ ) mechanical indicators, each showing one decimal digit. You noticed that when the countdown changes its state from $ x $ to $ x-1 $ , it doesn't happen in one move. Instead, each change of a single digit takes one second.

So, for example, if the countdown shows 42, then it will change to 41 in one second, because only one digit is changed, but if the countdown shows 2300, then it will change to 2299 in three seconds, because the three last digits are changed.

Find out how much time is left before the countdown reaches zero.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 4\cdot 10^5 $ ).

The second line contains a string of $ n $ digits, the current state of the countdown. It is guaranteed that at least one digit is not zero.

The sum of $ n $ for all tests does not exceed $ 4\cdot 10^5 $ .

## 输出格式

For each test case, print a single integer without leading zeroes, the number of seconds left before the countdown reaches zero. Note that this number may be huge.

## 说明/提示

In the first example, there are four changes that take 2 seconds: 40 to 39, 30 to 29, 20 to 19, and 10 to 09, other changes take 1 second each. So the total time is $ 2\cdot 4 + 1\cdot(42-4) = 46 $ .

## 样例 #1

### 输入

```
5
2
42
5
12345
2
99
4
0005
27
456480697259671309012631002
```

### 输出

```
46
13715
108
5
507200774732968121125145546
```

