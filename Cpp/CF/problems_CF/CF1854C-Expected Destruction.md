---
title: "Expected Destruction"
layout: "post"
diff: 提高+/省选-
pid: CF1854C
tag: []
---

# Expected Destruction

## 题目描述

You have a set $ S $ of $ n $ distinct integers between $ 1 $ and $ m $ .

Each second you do the following steps:

1. Pick an element $ x $ in $ S $ uniformly at random.
2. Remove $ x $ from $ S $ .
3. If $ x+1 \leq m $ and $ x+1 $ is not in $ S $ , add $ x+1 $ to $ S $ .

What is the expected number of seconds until $ S $ is empty?

Output the answer modulo $ 1\,000\,000\,007 $ .

Formally, let $ P = 1\,000\,000\,007 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{a}{b} $ , where $ a $ and $ b $ are integers and $ b \not \equiv 0 \pmod{P} $ . Output the integer equal to $ a \cdot b^{-1} \bmod P $ . In other words, output an integer $ z $ such that $ 0 \le z < P $ and $ z \cdot b \equiv a \pmod{P} $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq m \leq 500 $ ) — the number of elements in the set $ S $ and the upper bound on the value of the elements in $ S $ .

The second line contains $ n $ integers $ S_1,\,S_2,\,\dots,\,S_n $ ( $ 1 \leq S_1 < S_2 < \ldots < S_n \leq m $ ) — the elements of the set $ S $ .

## 输出格式

Output a single integer — the expected number of seconds until $ S $ is empty, modulo $ 1\,000\,000\,007 $ .

## 说明/提示

For test 1, here is a list of all the possible scenarios and their probabilities:

1. $ [1, 3] $ (50% chance) $ \to $ $ [1] $ $ \to $ $ [2] $ $ \to $ $ [3] $ $ \to $ $ [] $
2. $ [1, 3] $ (50% chance) $ \to $ $ [2, 3] $ (50% chance) $ \to $ $ [2] $ $ \to $ $ [3] $ $ \to $ $ [] $
3. $ [1, 3] $ (50% chance) $ \to $ $ [2, 3] $ (50% chance) $ \to $ $ [3] $ $ \to $ $ [] $

Adding them up, we get $ \frac{1}{2}\cdot 4 + \frac{1}{4} \cdot 4 + \frac{1}{4} \cdot 3 = \frac{15}{4} $ . We see that $ 750000009 \cdot 4 \equiv 15 \pmod{1\,000\,000\,007} $ .

## 样例 #1

### 输入

```
2 3
1 3
```

### 输出

```
750000009
```

## 样例 #2

### 输入

```
5 10
1 2 3 4 5
```

### 输出

```
300277731
```

## 样例 #3

### 输入

```
5 10
2 3 6 8 9
```

### 输出

```
695648216
```

## 样例 #4

### 输入

```
1 100
1
```

### 输出

```
100
```

