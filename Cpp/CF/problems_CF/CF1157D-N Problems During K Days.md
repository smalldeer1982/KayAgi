---
title: "N Problems During K Days"
layout: "post"
diff: 普及+/提高
pid: CF1157D
tag: []
---

# N Problems During K Days

## 题目描述

Polycarp has to solve exactly $ n $ problems to improve his programming skill before an important programming competition. But this competition will be held very soon, most precisely, it will start in $ k $ days. It means that Polycarp has exactly $ k $ days for training!

Polycarp doesn't want to procrastinate, so he wants to solve at least one problem during each of $ k $ days. He also doesn't want to overwork, so if he solves $ x $ problems during some day, he should solve no more than $ 2x $ problems during the next day. And, at last, he wants to improve his skill, so if he solves $ x $ problems during some day, he should solve at least $ x+1 $ problem during the next day.

More formally: let $ [a_1, a_2, \dots, a_k] $ be the array of numbers of problems solved by Polycarp. The $ i $ -th element of this array is the number of problems Polycarp solves during the $ i $ -th day of his training. Then the following conditions must be satisfied:

- sum of all $ a_i $ for $ i $ from $ 1 $ to $ k $ should be $ n $ ;
- $ a_i $ should be greater than zero for each $ i $ from $ 1 $ to $ k $ ;
- the condition $ a_i < a_{i + 1} \le 2 a_i $ should be satisfied for each $ i $ from $ 1 $ to $ k-1 $ .

Your problem is to find any array $ a $ of length $ k $ satisfying the conditions above or say that it is impossible to do it.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^9, 1 \le k \le 10^5 $ ) — the number of problems Polycarp wants to solve and the number of days Polycarp wants to train.

## 输出格式

If it is impossible to find any array $ a $ of length $ k $ satisfying Polycarp's rules of training, print "NO" in the first line.

Otherwise print "YES" in the first line, then print $ k $ integers $ a_1, a_2, \dots, a_k $ in the second line, where $ a_i $ should be the number of problems Polycarp should solve during the $ i $ -th day. If there are multiple answers, you can print any.

## 样例 #1

### 输入

```
26 6

```

### 输出

```
YES
1 2 4 5 6 8 

```

## 样例 #2

### 输入

```
8 3

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
YES
1 

```

## 样例 #4

### 输入

```
9 4

```

### 输出

```
NO

```

