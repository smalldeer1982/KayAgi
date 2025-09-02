---
title: "Light Bulbs (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1914G1
tag: []
---

# Light Bulbs (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on $ n $ . In the easy version, the sum of values of $ n^2 $ over all test cases does not exceed $ 10^6 $ . Furthermore, $ n $ does not exceed $ 1000 $ in each test case.

There are $ 2n $ light bulbs arranged in a row. Each light bulb has a color from $ 1 $ to $ n $ (exactly two light bulbs for each color).

Initially, all light bulbs are turned off. You choose a set of light bulbs $ S $ that you initially turn on. After that, you can perform the following operations in any order any number of times:

- choose two light bulbs $ i $ and $ j $ of the same color, exactly one of which is on, and turn on the second one;
- choose three light bulbs $ i, j, k $ , such that both light bulbs $ i $ and $ k $ are on and have the same color, and the light bulb $ j $ is between them ( $ i < j < k $ ), and turn on the light bulb $ j $ .

You want to choose a set of light bulbs $ S $ that you initially turn on in such a way that by performing the described operations, you can ensure that all light bulbs are turned on.

Calculate two numbers:

- the minimum size of the set $ S $ that you initially turn on;
- the number of sets $ S $ of minimum size (taken modulo $ 998244353 $ ).

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 1000 $ ) — the number of pairs of light bulbs.

The second line of each test case contains $ 2n $ integers $ c_1, c_2, \dots, c_{2n} $ ( $ 1 \le c_i \le n $ ), where $ c_i $ is the color of the $ i $ -th light bulb. For each color from $ 1 $ to $ n $ , exactly two light bulbs have this color.

Additional constraint on the input: the sum of values of $ n^2 $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output two integers:

- the minimum size of the set $ S $ that you initially turn on;
- the number of sets $ S $ of minimum size (taken modulo $ 998244353 $ ).

## 样例 #1

### 输入

```
4
2
2 2 1 1
2
1 2 2 1
2
1 2 1 2
5
3 4 4 5 3 1 1 5 2 2
```

### 输出

```
2 4
1 2
1 4
2 8
```

