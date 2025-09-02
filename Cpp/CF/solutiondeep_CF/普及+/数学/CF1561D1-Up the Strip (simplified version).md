# 题目信息

# Up the Strip (simplified version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

Note that the memory limit in this problem is lower than in others.

You have a vertical strip with $ n $ cells, numbered consecutively from $ 1 $ to $ n $ from top to bottom.

You also have a token that is initially placed in cell $ n $ . You will move the token up until it arrives at cell $ 1 $ .

Let the token be in cell $ x > 1 $ at some moment. One shift of the token can have either of the following kinds:

- Subtraction: you choose an integer $ y $ between $ 1 $ and $ x-1 $ , inclusive, and move the token from cell $ x $ to cell $ x - y $ .
- Floored division: you choose an integer $ z $ between $ 2 $ and $ x $ , inclusive, and move the token from cell $ x $ to cell $ \lfloor \frac{x}{z} \rfloor $ ( $ x $ divided by $ z $ rounded down).

Find the number of ways to move the token from cell $ n $ to cell $ 1 $ using one or more shifts, and print it modulo $ m $ . Note that if there are several ways to move the token from one cell to another in one shift, all these ways are considered distinct (check example explanation for a better understanding).

## 说明/提示

In the first test, there are three ways to move the token from cell $ 3 $ to cell $ 1 $ in one shift: using subtraction of $ y = 2 $ , or using division by $ z = 2 $ or $ z = 3 $ .

There are also two ways to move the token from cell $ 3 $ to cell $ 1 $ via cell $ 2 $ : first subtract $ y = 1 $ , and then either subtract $ y = 1 $ again or divide by $ z = 2 $ .

Therefore, there are five ways in total.

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
5```

## 样例 #2

### 输入

```
5 998244353```

### 输出

```
25```

## 样例 #3

### 输入

```
42 998244353```

### 输出

```
793019428```

# AI分析结果



### 题目翻译（保持原题格式）

# 向上移动令牌（简化版）

## 题目描述

本问题与进阶版的唯一区别在于 $n$ 的约束条件。

注意本题内存限制较其他题目更低。

你有一个垂直排列的 $n$个单元格，从上到下依次编号为 $1$ 到 $n$。

令牌初始位于单元格 $n$，你需要将其移动到单元格 $1$。

当令牌位于单元格 $x > 1$ 时，每次移动可采取以下两种方式之一：

- **减法操作**：选择 $1 \leq y \leq x-1$，将令牌移动到 $x-y$。
- **向下取整除法**：选择 $2 \leq z \leq x$，将令牌移动到 $\lfloor \frac{x}{z} \rfloor$。

求从 $n$ 到 $1$ 的不同移动方案总数（模 $m$ 输出）。不同操作序列视为不同方案，即使结果相同。

## 说明/提示

样例1中，从3到1有三种单步方案（减2、除以2、除以3），两种两步方案（先减1到2，再减1或除以2），总方案数5。

---

### 题解综合分析

#### 关键算法思路
所有题解均采用动态规划（DP）思想，核心差异在状态转移优化：
1. **主动转移**（正推）：计算当前状态对后续状态的贡献，用整除分块优化除法转移，时间复杂度 $O(n\sqrt{n})$。
2. **被动转移**（逆推）：计算当前状态被哪些前驱状态贡献，用调和级数优化，时间复杂度 $O(n\log n)$。

#### 最优技巧总结
1. **状态定义**：设 $f[i]$ 表示从 $n$ 到 $i$ 的方案数，最终目标为 $f[1]$。
2. **减法优化**：通过维护后缀和数组 $sum[i]$ 快速计算区间和。
3. **除法优化**：
   - 整除分块：将相同商值的区间合并计算。
   - 调和级数枚举：通过分段累加贡献区间，将复杂度降为 $O(n\log n)$。

---

### 精选题解（评分≥4★）

#### 题解1：henrytb（5★）
**核心思路**：
- 逆序DP，维护后缀和数组。
- 通过整除分块处理除法转移，主动转移时合并相同商值的区间贡献。
**代码亮点**：
```cpp
per(i, n-1, 1) {
    f[i] = (f[i] + sum[i+1]) % p; // 减法部分用后缀和
    for(int j=2; i*j<=n; ++j) {   // 调和级数枚举除数
        // 计算区间 [i*j, min(i*j+j, n+1)) 的贡献
        f[i] = (f[i] + sum[i*j] - sum[min(i*j+j, n+1)]) % p;
    }
    sum[i] = (sum[i+1] + f[i]) % p;
}
```

#### 题解2：Zxsoul（4★）
**核心思路**：
- 被动转移思路，通过枚举除数 $z$ 计算贡献区间。
- 使用后缀和数组避免重复计算。
**优化启示**：
```cpp
for(int z=2; z*i<=n; ++z)
    f[i] += sum[i*z] - sum[min(i*z + z, n+1)]; // 区间和差分
```

#### 题解3：James0602（4★）
**实现技巧**：
- 正向转移时维护前缀和。
- 数论分块处理除法转移段。
**代码简析**：
```cpp
for(int i=2; i<=n; i++) {
    f[i] = (sum[i-1] + 分段贡献计算) % mod;
    sum[i] = (sum[i-1] + f[i]) % mod;
}
```

---

### 关键代码实现（henrytb版）
```cpp
int f[4000005], sum[4000005];
per(i, n-1, 1) {
    f[i] = sum[i+1]; // 减法贡献（后缀和）
    for(int z=2; z*i <= n; ++z) { // 枚举除数z
        int L = z*i, R = min(z*i + z, n+1);
        f[i] = (f[i] + sum[L] - sum[R]) % mod;
    }
    sum[i] = (sum[i+1] + f[i]) % mod; // 更新后缀和
}
```

---

### 拓展练习
1. **整除分块应用**：[P2260 [清华集训] 模积和](https://www.luogu.com.cn/problem/P2260)
2. **调和级数优化**：[P2305 [NOI2017] 分身术](https://www.luogu.com.cn/problem/P2305)
3. **逆向DP思想**：[P3572 [POI2014]PTA-Little Bird](https://www.luogu.com.cn/problem/P3572)

---

### 总结心得
- **调试经验**：多位作者提到需特别注意模运算中的负数处理，如 `(x % mod + mod) % mod`。
- **优化顿悟**：反向转移时通过调和级数枚举除数，将复杂度从 $O(n\sqrt{n})$ 优化到 $O(n\log n)$。
- **易错点**：数论分块中区间端点计算需仔细验证，避免遗漏边界情况。

---
处理用时：63.08秒