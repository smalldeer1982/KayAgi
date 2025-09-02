---
title: "Swedish Heroes"
layout: "post"
diff: 省选/NOI-
pid: CF1421E
tag: []
---

# Swedish Heroes

## 题目描述

While playing yet another strategy game, Mans has recruited $ n $ [Swedish heroes](https://www.youtube.com/watch?v=5sGOwFVUU0I), whose powers which can be represented as an array $ a $ .

Unfortunately, not all of those mighty heroes were created as capable as he wanted, so that he decided to do something about it. In order to accomplish his goal, he can pick two consecutive heroes, with powers $ a_i $ and $ a_{i+1} $ , remove them and insert a hero with power $ -(a_i+a_{i+1}) $ back in the same position.

For example if the array contains the elements $ [5, 6, 7, 8] $ , he can pick $ 6 $ and $ 7 $ and get $ [5, -(6+7), 8] = [5, -13, 8] $ .

After he will perform this operation $ n-1 $ times, Mans will end up having only one hero. He wants his power to be as big as possible. What's the largest possible power he can achieve?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 200000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — powers of the heroes.

## 输出格式

Print the largest possible power he can achieve after $ n-1 $ operations.

## 说明/提示

Suitable list of operations for the first sample:

 $ [5, 6, 7, 8] \rightarrow [-11, 7, 8] \rightarrow [-11, -15] \rightarrow [26] $

## 样例 #1

### 输入

```
4
5 6 7 8
```

### 输出

```
26
```

## 样例 #2

### 输入

```
5
4 -5 9 -2 1
```

### 输出

```
15
```

