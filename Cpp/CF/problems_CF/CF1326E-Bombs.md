---
title: "Bombs"
layout: "post"
diff: 省选/NOI-
pid: CF1326E
tag: []
---

# Bombs

## 题目描述

You are given a permutation, $ p_1, p_2, \ldots, p_n $ .

Imagine that some positions of the permutation contain bombs, such that there exists at least one position without a bomb.

For some fixed configuration of bombs, consider the following process. Initially, there is an empty set, $ A $ .

For each $ i $ from $ 1 $ to $ n $ :

- Add $ p_i $ to $ A $ .
- If the $ i $ -th position contains a bomb, remove the largest element in $ A $ .

After the process is completed, $ A $ will be non-empty. The cost of the configuration of bombs equals the largest element in $ A $ .

You are given another permutation, $ q_1, q_2, \ldots, q_n $ .

For each $ 1 \leq i \leq n $ , find the cost of a configuration of bombs such that there exists a bomb in positions $ q_1, q_2, \ldots, q_{i-1} $ .

For example, for $ i=1 $ , you need to find the cost of a configuration without bombs, and for $ i=n $ , you need to find the cost of a configuration with bombs in positions $ q_1, q_2, \ldots, q_{n-1} $ .

## 输入格式

The first line contains a single integer, $ n $ ( $ 2 \leq n \leq 300\,000 $ ).

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n) $ .

The third line contains $ n $ distinct integers $ q_1, q_2, \ldots, q_n $ ( $ 1 \leq q_i \leq n) $ .

## 输出格式

Print $ n $ space-separated integers, such that the $ i $ -th of them equals the cost of a configuration of bombs in positions $ q_1, q_2, \ldots, q_{i-1} $ .

## 说明/提示

In the first test:

- If there are no bombs, $ A $ is equal to $ \{1, 2, 3\} $ at the end of the process, so the cost of the configuration is $ 3 $ .
- If there is one bomb in position $ 1 $ , $ A $ is equal to $ \{1, 2\} $ at the end of the process, so the cost of the configuration is $ 2 $ ;
- If there are two bombs in positions $ 1 $ and $ 2 $ , $ A $ is equal to $ \{1\} $ at the end of the process, so the cost of the configuration is $ 1 $ .

In the second test:

Let's consider the process for $ i = 4 $ . There are three bombs on positions $ q_1 = 5 $ , $ q_2 = 2 $ , and $ q_3 = 1 $ .

At the beginning, $ A = \{\} $ .

- Operation $ 1 $ : Add $ p_1 = 2 $ to $ A $ , so $ A $ is equal to $ \{2\} $ . There exists a bomb in position $ 1 $ , so we should delete the largest element from $ A $ . $ A $ is equal to $ \{\} $ .
- Operation $ 2 $ : Add $ p_2 = 3 $ to $ A $ , so $ A $ is equal to $ \{3\} $ . There exists a bomb in position $ 2 $ , so we should delete the largest element from $ A $ . $ A $ is equal to $ \{\} $ .
- Operation $ 3 $ : Add $ p_3 = 6 $ to $ A $ , so $ A $ is equal to $ \{6\} $ . There is no bomb in position $ 3 $ , so we do nothing.
- Operation $ 4 $ : Add $ p_4 = 1 $ to $ A $ , so $ A $ is equal to $ \{1, 6\} $ . There is no bomb in position $ 4 $ , so we do nothing.
- Operation $ 5 $ : Add $ p_5 = 5 $ to $ A $ , so $ A $ is equal to $ \{1, 5, 6\} $ . There exists a bomb in position $ 5 $ , so we delete the largest element from $ A $ . Now, $ A $ is equal to $ \{1, 5\} $ .
- Operation $ 6 $ : Add $ p_6 = 4 $ to $ A $ , so $ A $ is equal to $ \{1, 4, 5\} $ . There is no bomb in position $ 6 $ , so we do nothing.

In the end, we have $ A = \{1, 4, 5\} $ , so the cost of the configuration is equal to $ 5 $ .

## 样例 #1

### 输入

```
3
3 2 1
1 2 3
```

### 输出

```
3 2 1
```

## 样例 #2

### 输入

```
6
2 3 6 1 5 4
5 2 1 4 6 3
```

### 输出

```
6 5 5 5 4 1
```

