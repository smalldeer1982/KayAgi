# 题目信息

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3```

### 输出

```
4
11
0
20```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

给定一个整数数组 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$）。

找出数组中满足以下条件的子数组数量：子数组的异或和的除数个数为偶数。换句话说，找出所有满足 $i \le j$ 的索引对 $(i, j)$，使得 $a_i \oplus a_{i + 1} \oplus \dots \oplus a_j$ 的除数个数为偶数。

例如，数字 $2$、$3$、$5$ 或 $6$ 的除数个数为偶数，而 $1$ 和 $4$ 的除数个数为奇数。在此任务中，假设 $0$ 的除数个数为奇数。

这里的 $\operatorname{XOR}$（或 $\oplus$）表示[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

输出满足条件的子数组数量。

**说明/提示**

在第一个测试用例中，有 $4$ 个子数组的异或和的除数个数为偶数：$[3]$、$[3,1]$、$[1,2]$、$[2]$。

在第二个测试用例中，有 $11$ 个子数组的异或和的除数个数为偶数：$[4,2]$、$[4,2,1]$、$[4,2,1,5]$、$[2]$、$[2,1]$、$[2,1,5]$、$[2,1,5,3]$、$[1,5,3]$、$[5]$、$[5,3]$、$[3]$。

在第三个测试用例中，没有任何子数组的异或和的除数个数为偶数，因为任何子数组的异或和要么是 $4$，要么是 $0$。

**样例 #1**

**输入**

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3
```

**输出**

```
4
11
0
20
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何高效地计算满足条件的子数组数量。所有题解都利用了异或前缀和的性质，即子数组的异或和可以通过前缀和的异或得到。此外，题解普遍采用了补集思想，即先计算所有子数组的数量，再减去不满足条件的子数组数量（即异或和为完全平方数的子数组数量）。

**关键思路与技巧：**

1. **异或前缀和**：通过计算前缀异或和，可以将子数组的异或和转化为两个前缀异或和的异或。
2. **完全平方数的性质**：完全平方数的除数个数为奇数，因此可以通过枚举完全平方数来统计不满足条件的子数组数量。
3. **补集思想**：通过总子数组数减去不满足条件的子数组数，得到满足条件的子数组数。
4. **哈希表优化**：使用哈希表（或数组）来记录前缀异或和的出现次数，从而快速统计满足条件的子数组数量。

#### 评分较高的题解

**题解1：Jasper08（5星）**

- **关键亮点**：思路清晰，代码简洁，使用了哈希表来优化统计过程，时间复杂度为 $O(Tn)$。
- **核心代码**：
  ```cpp
  for (int i = 1; i <= n; ++i) {
      int cnt = i;
      for (int j = 0; j <= 650; ++j) {
          int t = j * j ^ s[i];
          if (nums[t])
              cnt -= nums[t];
      }
      nums[s[i]] ++;
      ans += cnt;
  }
  ```

**题解2：Engulf（4星）**

- **关键亮点**：使用了容斥原理，代码结构清晰，时间复杂度为 $O(n \sqrt{n})$。
- **核心代码**：
  ```cpp
  for (int i = 1, x; i <= n; i ++ ) {
      scanf("%d", &x);
      pre ^= x;
      for (int j = 0; (pre ^ j * j) <= 2 * n; j ++ )
          res -= cnt[pre ^ j * j];
      cnt[pre] ++ ;
  }
  ```

**题解3：tZEROちゃん（4星）**

- **关键亮点**：代码简洁，使用了补集思想，时间复杂度为 $O(n \sqrt{n})$。
- **核心代码**：
  ```cpp
  for (int i = 1; i <= n; ++i) {
      for (int x : perfectSquare) {
          ans += sum[s[i] ^ x];
      }
      sum[s[i]]++; 
  }
  ```

### 最优关键思路或技巧

1. **异或前缀和**：通过计算前缀异或和，可以将子数组的异或和转化为两个前缀异或和的异或，从而简化问题。
2. **补集思想**：通过总子数组数减去不满足条件的子数组数，得到满足条件的子数组数。
3. **哈希表优化**：使用哈希表（或数组）来记录前缀异或和的出现次数，从而快速统计满足条件的子数组数量。

### 可拓展之处

1. **类似问题**：可以扩展到其他位运算问题，如与、或等操作。
2. **其他优化**：可以考虑使用更高效的哈希表实现，如C++中的`unordered_map`，或者使用更高级的数据结构如Trie树来优化统计过程。

### 推荐题目

1. [P3919 【模板】可持久化线段树 1（主席树）](https://www.luogu.com.cn/problem/P3919)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得摘录

- **调试经历**：在处理完全平方数时，需要注意枚举的范围，避免超出数组边界。
- **踩坑教训**：在统计前缀异或和时，需要特别注意初始值的设置，如`nums[0] = 1`。
- **顿悟感想**：通过补集思想，可以将复杂的问题转化为简单的统计问题，大大降低了问题的难度。

---
处理用时：53.72秒