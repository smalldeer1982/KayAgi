---
title: "Magic Five"
layout: "post"
diff: 提高+/省选-
pid: CF327C
tag: []
---

# Magic Five

## 题目描述

There is a long plate $ s $ containing $ n $ digits. Iahub wants to delete some digits (possibly none, but he is not allowed to delete all the digits) to form his "magic number" on the plate, a number that is divisible by $ 5 $ . Note that, the resulting number may contain leading zeros.

Now Iahub wants to count the number of ways he can obtain magic number, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ). Two ways are different, if the set of deleted positions in $ s $ differs.

Look at the input part of the statement, $ s $ is given in a special form.

## 输入格式

In the first line you're given a string $ a $ ( $ 1<=|a|<=10^{5} $ ), containing digits only. In the second line you're given an integer $ k $ ( $ 1<=k<=10^{9} $ ). The plate $ s $ is formed by concatenating $ k $ copies of $ a $ together. That is $ n=|a|·k $ .

## 输出格式

Print a single integer — the required number of ways modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first case, there are four possible ways to make a number that is divisible by 5: 5, 15, 25 and 125.

In the second case, remember to concatenate the copies of $ a $ . The actual plate is 1399013990.

In the third case, except deleting all digits, any choice will do. Therefore there are $ 2^{6}-1=63 $ possible ways to delete digits.

## 样例 #1

### 输入

```
1256
1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
13990
2

```

### 输出

```
528

```

## 样例 #3

### 输入

```
555
2

```

### 输出

```
63

```

