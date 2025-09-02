---
title: "Parallel Universes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: CF1184D2
tag: []
---

# Parallel Universes (Hard)

## 题目描述

Heidi enjoyed performing the simulation because she knew exactly when a new universe would be formed and where, and when a non-existent link would be broken and where.

However, the multiverse itself works in mysterious ways. Well, it works using probabilities, which to some people is mysterious.

At each unit time, when a decision is made, one of the two events will happen randomly. Let's denote $ l $ as the current length of the multiverse. With a probability of $ p_{create} = 1 - \frac{l}{m} $ , a universe will be created. With a probability of $ p_{break}=\frac{l}{m} $ , a non-existent link will be broken at some position.

More specifically,

- When a universe is created, it will manifest itself between any two adjacent universes or at one of the ends. Each position occurs with a probability of $ \frac{1}{l + 1} $ .
- When a link is broken, it could be cut between any two adjacent universes, each with a probability of $ \frac{1}{l-1} $ . After separating the multiverse into two segments, the segment NOT containing the Doctor will cease to exist.

As earlier, the Doctor remains in the same universe. However, if at some point the multiverse breaks in such a way that the Doctor finds himself at the leftmost or rightmost end of it, the TARDIS stops functioning.

In such a case, the Doctor must actually walk across the multiverse to find the tools to fix it.

We are interested in the expected value of the length of the multiverse when such an event occurs.

## 输入格式

The first and only line contains three integers $ n $ , $ k $ and $ m $ $ (1 \le k \le n \le m \le 250) $ , the initial length of the multiverse, the initial position of the Doctor, and the maximum possible length of the multiverse.

## 输出格式

Output a single integer on a single line, indicating the expected length of the multiverse.

If the answer is $ \frac{p}{q} $ , please print $ r $ where $ p \equiv r \cdot q (\text{mod } 10^9 + 7) $ .

## 说明/提示

For the first and the second test case, without any change to the multiverse, the Doctor is already at one of the ends.

For the third test case, the multiverse can only break at a position, which renders the Doctor at one of its ends.

For the fourth case, things seem to be a little more complicated, because the multiverse can grow and then be broken again.

## 样例 #1

### 输入

```
2 1 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2 10

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 2 3

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 2 5

```

### 输出

```
941659828

```

## 样例 #5

### 输入

```
10 4 20

```

### 输出

```
196683114

```

