---
title: "Dr. Evil Underscores"
layout: "post"
diff: 普及+/提高
pid: CF1285D
tag: ['字符串', '树形 DP', '字典树 Trie']
---

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 输入格式

The first line contains integer $ n $ ( $ 1\le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ).

## 输出格式

Print one integer — the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 5
```

### 输出

```
4
```

