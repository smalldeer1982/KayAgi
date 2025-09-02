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



### 题目内容
# 偶因子子数组

## 题目描述

给定一个整数数组 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$），求满足以下条件的子数组数量：子数组的异或和的因数个数为偶数。等价于求所有满足 $a_i \oplus a_{i+1} \oplus \dots \oplus a_j$ 不是完全平方数的子数组数量（注意：本题中 $0$ 的因数个数视为奇数）。

---

### 题解分析与结论

#### 关键思路
1. **补集思想**：总子数组数为 $\frac{n(n+1)}{2}$，减去异或和为完全平方数的子数组数。
2. **异或前缀和**：利用前缀和数组 $s_i = a_1 \oplus \dots \oplus a_i$，子数组异或和可表示为 $s_j \oplus s_{i-1}$。
3. **哈希表优化**：枚举完全平方数 $k^2$，通过哈希表动态维护前缀和出现次数，快速计算满足 $s_j \oplus s_{i-1} = k^2$ 的区间数。

#### 最优解代码（Engulf，5星）
```cpp
int main() {
    int tt;
    scanf("%d", &tt);
    while (tt -- ) {
        int n;
        scanf("%d", &n);
        vector<int> cnt(2 * n + 5);
        cnt[0] ++;
        LL res = (LL)n * (n + 1) / 2;
        int pre = 0;
        for (int i = 1, x; i <= n; i ++ ) {
            scanf("%d", &x);
            pre ^= x;
            for (int j = 0; (pre ^ j * j) <= 2 * n; j ++ )
                res -= cnt[pre ^ j * j];
            cnt[pre] ++;
        }
        printf("%lld\n", res);
    }
    return 0;
}
```
**亮点**：
- **清晰的补集转换**：直接计算非法区间数，逻辑简洁。
- **动态哈希维护**：在遍历过程中实时更新哈希表，避免重复计算。
- **高效枚举范围**：通过 $j^2 \leq 2n$ 限制枚举次数，保证 $O(n\sqrt{n})$ 时间复杂度。

---

### 扩展与习题推荐
1. **类似技巧题目**：
   - [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)（异或性质）
   - [P2303 Longge的问题](https://www.luogu.com.cn/problem/P2303)（因数个数分析）
   - [P5495 Dirichlet 前缀和](https://www.luogu.com.cn/problem/P5495)（前缀和与异或结合）

2. **调试心得**：
   - **边界处理**：注意完全平方数需覆盖到 $2n$，例如样例3中异或和为4或0。
   - **哈希表初始化**：必须包含初始状态 `cnt[0] = 1`，对应空前缀的情况。

---
处理用时：114.18秒