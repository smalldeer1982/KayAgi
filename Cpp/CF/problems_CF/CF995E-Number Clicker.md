---
title: "Number Clicker"
layout: "post"
diff: 省选/NOI-
pid: CF995E
tag: []
---

# Number Clicker

## 题目描述

Allen is playing Number Clicker on his phone.

He starts with an integer $ u $ on the screen. Every second, he can press one of 3 buttons.

1. Turn $ u \to u+1 \pmod{p} $ .
2. Turn $ u \to u+p-1 \pmod{p} $ .
3. Turn $ u \to u^{p-2} \pmod{p} $ .

Allen wants to press at most 200 buttons and end up with $ v $ on the screen. Help him!

## 输入格式

The first line of the input contains 3 positive integers: $ u, v, p $ ( $ 0 \le u, v \le p-1 $ , $ 3 \le p \le 10^9 + 9 $ ). $ p $ is guaranteed to be prime.

## 输出格式

On the first line, print a single integer $ \ell $ , the number of button presses. On the second line, print integers $ c_1, \dots, c_\ell $ , the button presses. For $ 1 \le i \le \ell $ , $ 1 \le c_i \le 3 $ .

We can show that the answer always exists.

## 说明/提示

In the first example the integer on the screen changes as $ 1 \to 2 \to 3 $ .

In the second example the integer on the screen changes as $ 3 \to 2 $ .

## 样例 #1

### 输入

```
1 3 5

```

### 输出

```
2
1 1

```

## 样例 #2

### 输入

```
3 2 5

```

### 输出

```
1
3

```

