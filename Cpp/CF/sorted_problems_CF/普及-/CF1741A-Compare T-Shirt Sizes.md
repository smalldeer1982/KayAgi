---
title: "Compare T-Shirt Sizes"
layout: "post"
diff: 普及-
pid: CF1741A
tag: []
---

# Compare T-Shirt Sizes

## 题目描述

Two T-shirt sizes are given: $ a $ and $ b $ . The T-shirt size is either a string M or a string consisting of several (possibly zero) characters X and one of the characters S or L.

For example, strings M, XXL, S, XXXXXXXS could be the size of some T-shirts. And the strings XM, LL, SX are not sizes.

The letter M stands for medium, S for small, L for large. The letter X refers to the degree of size (from eXtra). For example, XXL is extra-extra-large (bigger than XL, and smaller than XXXL).

You need to compare two given sizes of T-shirts $ a $ and $ b $ .

The T-shirts are compared as follows:

- any small size (no matter how many letters X) is smaller than the medium size and any large size;
- any large size (regardless of the number of letters X) is larger than the medium size and any small size;
- the more letters X before S, the smaller the size;
- the more letters X in front of L, the larger the size.

For example:

- XXXS &lt; XS
- XXXL &gt; XL
- XL &gt; M
- XXL = XXL
- XXXXXS &lt; M
- XL &gt; XXXS

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, in which $ a $ and $ b $ T-shirt sizes are written. The lengths of the strings corresponding to the T-shirt sizes do not exceed $ 50 $ . It is guaranteed that all sizes are correct.

## 输出格式

For each test case, print on a separate line the result of comparing $ a $ and $ b $ T-shirt sizes (lines "&lt;", "&gt;" or "=" without quotes).

## 样例 #1

### 输入

```
6
XXXS XS
XXXL XL
XL M
XXL XXL
XXXXXS M
L M
```

### 输出

```
<
>
>
=
<
>

```

