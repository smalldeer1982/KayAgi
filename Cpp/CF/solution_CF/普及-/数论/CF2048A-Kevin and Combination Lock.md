# Kevin and Combination Lock

## 题目描述

Kevin is trapped in Lakeside Village by Grace. At the exit of the village, there is a combination lock that can only be unlocked if Kevin solves it.

The combination lock starts with an integer $  x  $ . Kevin can perform one of the following two operations zero or more times:

1. If $  x \neq 33  $ , he can select two consecutive digits $  3  $ from $  x  $ and remove them simultaneously. For example, if $  x = 13\,323  $ , he can remove the second and third $  3  $ , changing $  x  $ to $  123  $ .
2. If $  x \geq 33  $ , he can change $  x  $ to $  x - 33  $ . For example, if $  x = 99  $ , he can choose this operation to change $  x  $ to $  99 - 33 = 66  $ .

When the value of $  x  $ on the combination lock becomes $  0  $ , Kevin can unlock the lock and escape from Lakeside Village. Please determine whether it is possible for Kevin to unlock the combination lock and escape.

## 说明/提示

For the first test case, $ 165\xrightarrow{-33}132\xrightarrow{-33}99\xrightarrow{-33}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the second test case, $ 6369\xrightarrow{-33}6{\color{red}{33}}6\xrightarrow{\text{remove "33"}}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the third test case, it can be proven that, regardless of the operations performed, $ 666 $ cannot be transformed into $ 0 $ .

## 样例 #1

### 输入

```
5
165
6369
666
114514
133333332```

### 输出

```
YES
YES
NO
NO
YES```

