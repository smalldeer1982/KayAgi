---
title: "Robin Hood in Town"
layout: "post"
diff: 普及-
pid: CF2014C
tag: ['数学', '二分']
---

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 输入格式

The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2\cdot10^5 $ ) — the total population.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the wealth of each person.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum number of gold that the richest person must find for Robin Hood to appear. If it is impossible, output $ -1 $ instead.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25
```

### 输出

```
-1
-1
0
15
16
0
```

