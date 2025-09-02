---
title: "Dual Trigger"
layout: "post"
diff: 普及-
pid: CF1951A
tag: ['数学']
---

# Dual Trigger

## 题目描述

[Ngọt - LẦN CUỐI (đi bên em xót xa người ơi)](https://youtu.be/kSjj0LlsqnI)

ඞ



There are $ n $ lamps numbered $ 1 $ to $ n $ lined up in a row, initially turned off. You can perform the following operation any number of times (possibly zero):

- Choose two non-adjacent $ {}^\dagger $ lamps that are currently turned off, then turn them on.

Determine whether you can reach configuration $ s $ , where $ s_i = 1 $ means the $ i $ -th lamp is turned on, and $ s_i = 0 $ otherwise.

 $ {}^\dagger $ Only lamp $ i $ and $ i + 1 $ are adjacent for all $ 1 \le i < n $ . Note that lamp $ n $ and $ 1 $ are not adjacent when $ n \ne 2 $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 50 $ ) — the number of lamps.

The second line of each test case contains a binary string $ s $ of size $ n $ — the final desired configuration.

## 输出格式

For each test case, print on one line "YES" if we can reach the configuration $ s $ via applying the given operation any number of times. Otherwise, print "NO".

## 说明/提示

In the first test case, the sequence of operation could have been as follows (note that initially $ s $ is all zero): $ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ .

In the third test case, we don't have to do any operation.

In the fourth test case, we cannot do any operation, but we need the first lamp to be on. Therefore, it is impossible to achieve the desired state.

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111
```

### 输出

```
YES
NO
YES
NO
YES
```

