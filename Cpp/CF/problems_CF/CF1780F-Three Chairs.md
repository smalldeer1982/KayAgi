---
title: "Three Chairs"
layout: "post"
diff: 提高+/省选-
pid: CF1780F
tag: ['最大公约数 gcd', '莫比乌斯反演', '前缀和']
---

# Three Chairs

## 题目描述

One day Kira found $ n $ friends from Morioh and decided to gather them around a table to have a peaceful conversation. The height of friend $ i $ is equal to $ a_i $ . It so happened that the height of each of the friends is unique.

Unfortunately, there were only $ 3 $ chairs in Kira's house, and obviously, it will not be possible to seat all friends! So, Kira has to invite only $ 3 $ of his friends.

But everything is not so simple! If the heights of the lowest and the tallest of the invited friends are not coprime, then the friends will play tricks on each other, which will greatly anger Kira.

Kira became interested, how many ways are there to choose $ 3 $ of his friends so that they don't play tricks? Two ways are considered different if there is a friend invited in one way, but not in the other.

Formally, if Kira invites friends $ i $ , $ j $ , and $ k $ , then the following should be true: $ \gcd(\min(a_i, a_j, a_k), \max(a_i, a_j, a_k)) = 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the numbers $ x $ and $ y $ .

Kira is not very strong in computer science, so he asks you to count the number of ways to invide friends.

## 输入格式

The first line contains the number $ n $ ( $ 3 \le n \le 3\cdot10^5 $ ) — the number of Kira's friends.

The next line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 3\cdot10^5 $ ) — heights of Kira's friends.

## 输出格式

In a single line output the number of ways to invite three friends.

## 说明/提示

In the first example, only one way is suitable: invite friends $ 1 $ , $ 2 $ , and $ 3 $ . Here $ 1 < 2 < 3 $ , and the numbers $ 1 $ and $ 3 $ are coprime.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 6 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
16 4 8 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
10
10 1 6 7 9 8 4 3 5 2
```

### 输出

```
77
```

