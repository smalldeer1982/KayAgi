---
title: "Count Voting"
layout: "post"
diff: 省选/NOI-
pid: CF1799G
tag: ['动态规划 DP', '组合数学', '容斥原理']
---

# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the number of people.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ) — desired number of votes. It is guaranteed, that $ \sum\limits_{i=1}^{n} c_i = n $ .

The third line contains $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 1 \leq t_i \leq n $ ) — team numbers.

## 输出格式

Print a single integer — the number of possible votings by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4
```

### 输出

```
5
```

