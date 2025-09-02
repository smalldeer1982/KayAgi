---
title: "Sets and Union"
layout: "post"
diff: 普及/提高-
pid: CF1882B
tag: []
---

# Sets and Union

## 题目描述

You have $ n $ sets of integers $ S_{1}, S_{2}, \ldots, S_{n} $ . We call a set $ S $ attainable, if it is possible to choose some (possibly, none) of the sets $ S_{1}, S_{2}, \ldots, S_{n} $ so that $ S $ is equal to their union $ ^{\dagger} $ . If you choose none of $ S_{1}, S_{2}, \ldots, S_{n} $ , their union is an empty set.

Find the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

 $ ^{\dagger} $ The union of sets $ A_1, A_2, \ldots, A_k $ is defined as the set of elements present in at least one of these sets. It is denoted by $ A_1 \cup A_2 \cup \ldots \cup A_k $ . For example, $ \{2, 4, 6\} \cup \{2, 3\} \cup \{3, 6, 7\} = \{2, 3, 4, 6, 7\} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ).

The following $ n $ lines describe the sets $ S_1, S_2, \ldots, S_n $ . The $ i $ -th of these lines contains an integer $ k_{i} $ ( $ 1 \le k_{i} \le 50 $ ) — the number of elements in $ S_{i} $ , followed by $ k_{i} $ integers $ s_{i, 1}, s_{i, 2}, \ldots, s_{i, k_{i}} $ ( $ 1 \le s_{i, 1} < s_{i, 2} < \ldots < s_{i, k_{i}} \le 50 $ ) — the elements of $ S_{i} $ .

## 输出格式

For each test case, print a single integer — the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

## 说明/提示

In the first test case, $ S = S_{1} \cup S_{3} = \{1, 2, 3, 4\} $ is the largest attainable set not equal to $ S_1 \cup S_2 \cup S_3 = \{1, 2, 3, 4, 5\} $ .

In the second test case, we can pick $ S = S_{2} \cup S_{3} \cup S_{4} = \{2, 3, 4, 5, 6\} $ .

In the third test case, we can pick $ S = S_{2} \cup S_{5} = S_{2} \cup S_{3} \cup S_{5} = \{3, 5, 6, 8, 9, 10\} $ .

In the fourth test case, the only attainable set is $ S = \varnothing $ .

## 样例 #1

### 输入

```
4
3
3 1 2 3
2 4 5
2 3 4
4
4 1 2 3 4
3 2 5 6
3 3 5 6
3 4 5 6
5
1 1
3 3 6 10
1 9
2 1 3
3 5 8 9
1
2 4 28
```

### 输出

```
4
5
6
0
```

