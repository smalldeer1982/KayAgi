---
title: "Beautiful Numbers"
layout: "post"
diff: 普及+/提高
pid: CF300C
tag: []
---

# Beautiful Numbers

## 题目描述

Vitaly is a very weird man. He's got two favorite digits $ a $ and $ b $ . Vitaly calls a positive integer good, if the decimal representation of this integer only contains digits $ a $ and $ b $ . Vitaly calls a good number excellent, if the sum of its digits is a good number.

For example, let's say that Vitaly's favourite digits are $ 1 $ and $ 3 $ , then number $ 12 $ isn't good and numbers $ 13 $ or $ 311 $ are. Also, number $ 111 $ is excellent and number $ 11 $ isn't.

Now Vitaly is wondering, how many excellent numbers of length exactly $ n $ are there. As this number can be rather large, he asks you to count the remainder after dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

A number's length is the number of digits in its decimal representation without leading zeroes.

## 输入格式

The first line contains three integers: $ a $ , $ b $ , $ n $ $ (1<=a<b<=9,1<=n<=10^{6}) $ .

## 输出格式

Print a single integer — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
1 3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 3 10

```

### 输出

```
165

```

