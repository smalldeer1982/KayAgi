---
title: "Vlad and a Pair of Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1790E
tag: ['数学']
---

# Vlad and a Pair of Numbers

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a,b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 输入格式

The first line of the input data contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

Each test case is described by a single integer $ x $ ( $ 1 \le x \le 2^{29} $ ) — the number that Vlad remembered.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As the answer, output $ a $ and $ b $ ( $ 0 < a,b \le 2^{32} $ ), such that $ x = a \oplus b = \frac{a + b}{2} $ . If there are several answers, output any of them. If there are no matching pairs, output -1.

## 样例 #1

### 输入

```
6
2
5
10
6
18
36
```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22
```

