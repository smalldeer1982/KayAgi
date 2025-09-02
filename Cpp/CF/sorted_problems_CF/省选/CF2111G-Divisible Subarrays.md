---
title: "Divisible Subarrays"
layout: "post"
diff: 省选/NOI-
pid: CF2111G
tag: []
---

# Divisible Subarrays

## 题目描述

Technically, this is an interactive problem.

An array $ a $ of $ m $ numbers is called divisible if at least one of the following conditions holds:

- There exists an index $ i $ ( $ 1 \le i < m $ ) and an integer $ x $ such that for all indices $ j $ ( $ j \le i $ ), it holds that $ a_{j} \le x $ and for all indices $ k $ ( $ k > i $ ), it holds that $ a_{k} > x $ .
- There exists an index $ i $ ( $ 1 \le i < m $ ) and an integer $ x $ such that for all indices $ j $ ( $ j \le i $ ), it holds that $ a_{j} > x $ and for all indices $ k $ ( $ k > i $ ), it holds that $ a_{k} \le x $ .

You are given a permutation $ p $ of integers $ 1, 2, \dots, n $ . Your task is to answer queries of the following form fast: if we take only the segment \[ $ l $ , $ r $ \] from the permutation, that is, the numbers $ p_{l}, p_{l + 1}, \dots, p_{r} $ , is this subarray of numbers divisible?

Queries will be submitted in interactive mode in groups of $ 10 $ , meaning you will not receive the next group of queries until you output all answers for the current group.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^{5} $ ) — the size of the permutation.

The second line contains $ n $ integers $ p_{i} $ ( $ 1 \le p_{i} \le n $ ) — the permutation of natural numbers itself.

The third line contains one integer $ q $ ( $ 10 \le q \le 10^{6}, q \bmod 10 = 0 $ ) — the number of queries.

The following $ q $ lines contain two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) — the parameters of the query.

## 输出格式

For each query, output the string "YES" if the subarray from this query is divisible and "NO" otherwise.

After printing the answers to a group of queries, do not forget to output the end of line and flush the output buffer. Otherwise, you may get the Idleness Limit Exceeded verdict. To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- refer to the documentation for other languages.

You have to flush the output buffer after the $ 10 $ -th, $ 20 $ -th, $ 30 $ -th query (and so on), i. e. after each query with index divisible by $ 10 $ . After that, you can read the next group of queries.

## 样例 #1

### 输入

```
7
4 2 3 6 1 5 7
20
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
1 7
2 7
3 7
4 7
5 7
```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
NO
YES
YES
YES
YES
YES
YES
YES
YES
```

