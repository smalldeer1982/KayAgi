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



### 题目重写
题目名：偶数因数的子数组

**题目描述**  
给定一个整数数组 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$），求满足以下条件的子数组 $[i,j]$（$i \le j$）的数量：子数组的异或和 $a_i \oplus a_{i+1} \oplus \dots \oplus a_j$ 的因数个数为偶数。例如，数字 2、3、5、6 的因数个数为偶数，而 1、4 的因数个数为奇数，0 在此题中被视为有奇数个因数。

**输入输出样例**  
见原题。

---

### 题解综合分析
#### 核心思路
1. **数学性质**：完全平方数的因数个数为奇数，非完全平方数的因数个数为偶数。问题转化为求异或和不为完全平方数的子数组数量。
2. **前缀异或和**：计算前缀异或数组 $s_i = a_1 \oplus \dots \oplus a_i$，子数组 $[i,j]$ 的异或和为 $s_j \oplus s_{i-1}$。
3. **补集优化**：总子数组数为 $\frac{n(n+1)}{2}$，减去异或和为完全平方数的子数组数。
4. **哈希桶计数**：枚举可能的完全平方数 $k^2$，用哈希表统计前缀异或和的出现次数，快速计算符合条件的区间数。

#### 最优题解
##### 1. 题解作者：Engulf（★★★★★）
**关键亮点**  
- 精确枚举到 $k^2 \le 2n$，覆盖所有可能的异或和范围。
- 动态维护哈希表，空间优化合理，时间复杂度 $O(n\sqrt{n})$。
- 代码简洁，逻辑清晰，直接通过总子数组数减去非法情况。

**核心代码**  
```cpp
vector<int> cnt(2 * n + 5);
cnt[0] = 1;
LL res = (LL)n * (n + 1) / 2;
int pre = 0;
for (int i = 1, x; i <= n; ++i) {
    scanf("%d", &x);
    pre ^= x;
    for (int j = 0; (pre ^ j * j) <= 2 * n; ++j)
        res -= cnt[pre ^ j * j];
    cnt[pre]++;
}
```

##### 2. 题解作者：Jasper08（★★★★☆）
**关键亮点**  
- 预处理平方数范围（j ≤ 650），适用于大部分数据规模。
- 桶数组高效统计前缀和，时间复杂度接近线性。
- 代码结构清晰，桶的初始化和管理简洁。

**核心代码**  
```cpp
int nums[M] = {0};
nums[0] = 1;
for (int i = 1; i <= n; ++i) {
    int cnt = i;
    for (int j = 0; j <= 650; ++j) {
        int t = j * j ^ s[i];
        if (nums[t]) cnt -= nums[t];
    }
    nums[s[i]]++;
    ans += cnt;
}
```

---

### 关键技巧总结
1. **异或前缀和转换**：将子数组异或和转换为前缀异或的异或操作，简化区间查询。
2. **完全平方数枚举**：利用完全平方数数量稀疏性，将问题复杂度降至 $O(n\sqrt{n})$。
3. **哈希桶动态维护**：实时更新前缀和出现次数，快速匹配历史值。

---

### 拓展练习
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469) - 异或性质应用。
2. [P2303 Longge的问题](https://www.luogu.com.cn/problem/P2303) - 因数分析与数学优化。
3. [P4597 序列求余](https://www.luogu.com.cn/problem/P4597) - 完全平方数性质与动态规划。

---
处理用时：70.79秒