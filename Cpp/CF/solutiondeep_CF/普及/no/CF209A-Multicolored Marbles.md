# 题目信息

# Multicolored Marbles

## 题目描述

Polycarpus plays with red and blue marbles. He put $ n $ marbles from the left to the right in a row. As it turned out, the marbles form a zebroid.

A non-empty sequence of red and blue marbles is a zebroid, if the colors of the marbles in this sequence alternate. For example, sequences (red; blue; red) and (blue) are zebroids and sequence (red; red) is not a zebroid.

Now Polycarpus wonders, how many ways there are to pick a zebroid subsequence from this sequence. Help him solve the problem, find the number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Let's consider the first test sample. Let's assume that Polycarpus initially had sequence (red; blue; red), so there are six ways to pick a zebroid:

- pick the first marble;
- pick the second marble;
- pick the third marble;
- pick the first and second marbles;
- pick the second and third marbles;
- pick the first, second and third marbles.

It can be proven that if Polycarpus picks (blue; red; blue) as the initial sequence, the number of ways won't change.

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
11
```

# AI分析结果



# Multicolored Marbles

## 题目描述

Polycarpus 用红色和蓝色弹珠玩耍。他将 $n$ 个弹珠从左到右排成一行。这些弹珠形成了一个交替色序列（zebroid）。

一个非空的红色和蓝色弹珠序列被称为 zebroid，如果序列中的弹珠颜色交替出现。例如，序列（红；蓝；红）和（蓝）是 zebroid，而（红；红）不是。

现在 Polycarpus 想知道有多少种方法可以从这个序列中选出一个 zebroid 子序列。结果对 $1000000007$ 取模。

## 算法分类
动态规划、递推、组合数学

---

## 题解分析与结论

各题解均采用动态规划思想，核心在于发现状态转移方程。最优思路为：定义 $dp[i]$ 表示前 $i$ 个弹珠的合法子序列数，推导出递推式 $dp[i] = dp[i-1] + dp[i-2] + 2$，最终发现其与斐波那契数列的关系，可用矩阵快速幂优化。

---

## 精选题解

### 题解1 by Areka6219 (⭐⭐⭐⭐⭐)
**关键亮点**：  
- 发现状态转移方程 $dp[i] = dp[i-1] + dp[i-2] + 2$，简洁高效。
- 进一步推导出其与斐波那契数列的关系，提出 $dp[n] = fib(n+3) - 2$，实现 $O(\log n)$ 复杂度。
  
**核心代码**：
```cpp
// 矩阵快速幂实现斐波那契计算
struct Martix {
    int f[3][3];
    Martix() { memset(f, 0, sizeof(f)); }
    friend Martix operator*(const Martix &a, const Martix &b) {
        Martix c;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                for (int k = 1; k <= 2; ++k)
                    c.f[i][j] = (c.f[i][j] + a.f[i][k] * b.f[k][j]) % p;
        return c;
    }
};

void Get_xr(int b) { // 快速幂计算
    while (b) {
        if (b & 1) B = B * A;
        A = A * A;
        b >>= 1;
    }
}
```

---

### 题解2 by VitrelosTia (⭐⭐⭐⭐)
**关键亮点**：  
- 直接应用递推式，代码简洁，适合快速实现。
- 使用一维 DP 数组，空间复杂度 $O(n)$，可进一步优化为滚动数组。

**核心代码**：
```cpp
int n, dp[MAXN];
dp[1] = 1;
for (int i = 2; i <= n; ++i)
    dp[i] = (dp[i-1] + dp[i-2] + 2) % MOD;
```

---

### 题解3 by 123456zmy (⭐⭐⭐)
**关键亮点**：  
- 初始用两个 DP 数组分奇偶状态处理，最终优化为两个变量交替更新。
- 提供从原始思路到优化的完整推导路径。

**核心代码**：
```cpp
int a1 = 0, a2 = 0;
while (n--)
    if (n & 1) a1 = (a1 + a2 + 1) % MOD;
    else a2 = (a1 + a2 + 1) % MOD;
printf("%d", (a1 + a2) % MOD);
```

---

## 关键思路总结
1. **状态设计**：定义 $dp[i]$ 表示前 $i$ 个元素的合法子序列数。
2. **转移方程**：$dp[i] = dp[i-1] + dp[i-2] + 2$，新增项对应单独选当前元素、选当前与前一元素组合、以及更早的组合扩展。
3. **数学优化**：发现 $dp$ 序列与斐波那契数列的关系，$dp[n] = fib(n+3) - 2$，可用矩阵快速幂求解。

---

## 拓展与相似题目
- **同类型题**：  
  1. [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)  
  2. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)  
  3. [P3990 [SHOI2013] 超级跳马](https://www.luogu.com.cn/problem/P3990)  

**个人心得**：注意模数运算的溢出问题，递推式推导时需结合数学归纳法验证正确性。当遇到交替模式问题时，可优先考虑奇偶性分类或斐波那契类递推。

---
处理用时：291.88秒