---
title: "String Multiplication"
layout: "post"
diff: 省选/NOI-
pid: CF1131E
tag: []
---

# String Multiplication

## 题目描述

Roman and Denis are on the trip to the programming competition. Since the trip was long, they soon got bored, and hence decided to came up with something. Roman invented a pizza's recipe, while Denis invented a string multiplication. According to Denis, the result of multiplication (product) of strings $ s $ of length $ m $ and $ t $ is a string $ t + s_1 + t + s_2 + \ldots + t + s_m + t $ , where $ s_i $ denotes the $ i $ -th symbol of the string $ s $ , and "+" denotes string concatenation. For example, the product of strings "abc" and "de" is a string "deadebdecde", while the product of the strings "ab" and "z" is a string "zazbz". Note, that unlike the numbers multiplication, the product of strings $ s $ and $ t $ is not necessarily equal to product of $ t $ and $ s $ .

Roman was jealous of Denis, since he invented such a cool operation, and hence decided to invent something string-related too. Since Roman is beauty-lover, he decided to define the beauty of the string as the length of the longest substring, consisting of only one letter. For example, the beauty of the string "xayyaaabca" is equal to $ 3 $ , since there is a substring "aaa", while the beauty of the string "qwerqwer" is equal to $ 1 $ , since all neighboring symbols in it are different.

In order to entertain Roman, Denis wrote down $ n $ strings $ p_1, p_2, p_3, \ldots, p_n $ on the paper and asked him to calculate the beauty of the string $ ( \ldots (((p_1 \cdot p_2) \cdot p_3) \cdot \ldots ) \cdot p_n $ , where $ s \cdot t $ denotes a multiplication of strings $ s $ and $ t $ . Roman hasn't fully realized how Denis's multiplication works, so he asked you for a help. Denis knows, that Roman is very impressionable, he guarantees, that the beauty of the resulting string is at most $ 10^9 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \leq n \leq 100\,000 $ ) — the number of strings, wroted by Denis.

Next $ n $ lines contain non-empty strings $ p_1, p_2, \ldots, p_n $ , consisting of lowercase english letters.

It's guaranteed, that the total length of the strings $ p_i $ is at most $ 100\,000 $ , and that's the beauty of the resulting product is at most $ 10^9 $ .

## 输出格式

Print exactly one integer — the beauty of the product of the strings.

## 说明/提示

In the first example, the product of strings is equal to "abaaaba".

In the second example, the product of strings is equal to "abanana".

## 样例 #1

### 输入

```
3
a
b
a

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
bnn
a

```

### 输出

```
1

```

