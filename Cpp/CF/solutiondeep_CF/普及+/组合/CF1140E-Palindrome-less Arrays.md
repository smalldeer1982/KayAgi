# 题目信息

# Palindrome-less Arrays

## 题目描述

Let's denote that some array $ b $ is bad if it contains a subarray $ b_l, b_{l+1}, \dots, b_{r} $ of odd length more than $ 1 $ ( $ l < r $ and $ r - l + 1 $ is odd) such that $ \forall i \in \{0, 1, \dots, r - l\} $ $ b_{l + i} = b_{r - i} $ .

If an array is not bad, it is good.

Now you are given an array $ a_1, a_2, \dots, a_n $ . Some elements are replaced by $ -1 $ . Calculate the number of good arrays you can obtain by replacing each $ -1 $ with some integer from $ 1 $ to $ k $ .

Since the answer can be large, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 3
-1 -1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 2
1 -1 -1 1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 3
1 -1 -1 1 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
4 200000
-1 -1 12345 -1
```

### 输出

```
735945883
```

# AI分析结果

### 题目翻译
#### 无回文数组
#### 题目描述
如果一个数组 $b$ 包含一个长度大于 $1$ 的奇数长度的子数组 $b_l, b_{l + 1}, \dots, b_{r}$（$l < r$ 且 $r - l + 1$ 为奇数），使得 $\forall i \in \{0, 1, \dots, r - l\}$ 都有 $b_{l + i} = b_{r - i}$，那么我们称这个数组 $b$ 是坏的。

如果一个数组不是坏的，那么它就是好的。

现在给定一个数组 $a_1, a_2, \dots, a_n$，其中一些元素被替换成了 $-1$。计算通过将每个 $-1$ 替换为 $1$ 到 $k$ 之间的某个整数可以得到的好数组的数量。

由于答案可能很大，将结果对 $998244353$ 取模后输出。

#### 样例 #1
##### 输入
```
2 3
-1 -1
```
##### 输出
```
9
```

#### 样例 #2
##### 输入
```
5 2
1 -1 -1 1 2
```
##### 输出
```
0
```

#### 样例 #3
##### 输入
```
5 3
1 -1 -1 1 2
```
##### 输出
```
2
```

#### 样例 #4
##### 输入
```
4 200000
-1 -1 12345 -1
```
##### 输出
```
735945883
```

### 综合分析与结论
这些题解的核心思路都是先将“不存在长度大于 1 的奇数回文串”转化为“不存在长度为 3 的回文串”，进而得出数组中距离为 2 的元素不能相等，通过分奇偶处理数组来简化问题。在处理连续的 -1 序列时，大部分题解使用动态规划来计算方案数，根据连续 -1 序列两端元素的情况（是否相等、是否有限制）进行分类讨论。

### 所选题解
- **Leap_Frog（5 星）**
    - **关键亮点**：思路清晰，详细证明了“有一个长度为 3 的回文子串”和“这个串是不好的”是充分必要条件，代码简洁且有详细注释，还分享了调试过程中的错误及解决方法。
    - **个人心得**：作者一开始提交代码出现 `Wrong Answer On 14` 的错误，原因是没有考虑所有数都放好后答案不符合的情况，后续添加特判解决了问题。
- **DPair（4 星）**
    - **关键亮点**：思路超详细，对问题进行逐步转化、简化和分类，每种情况的处理都有详细说明，代码注释丰富，可读性强。
- **Rui_R（4 星）**
    - **关键亮点**：思路清晰，通过图片辅助理解动态规划的转移方程，代码中有详细注释，方便理解。

### 重点代码及核心实现思想
#### Leap_Frog
```cpp
inline int wrk(int n, int a[])
{
    int ret = 1;
    for(int i = 1; i < n; i++) if(a[i]!= -1 && a[i] == a[i + 1]) return 0;
    for(int i = 1, j; i <= n; i = j + 1)
    {
        while(i <= n && a[i]!= -1) i++; j = i;
        while(j <= n && a[j] == -1) j++; j--;
        if(i > j || i < 1 || j > n) continue;
        else if(i == 1 && j == n) ret = 1ll * ret * ksm(k - 1, n - 1) % P * k % P;
        else if(i == 1 || j == n) ret = 1ll * (dp[j - i][0] + 1ll * (k - 1) * dp[j - i][1] % P) % P * ret % P;
        else ret = 1ll * ret * dp[j - i + 1][a[i - 1]!= a[j + 1]] % P;
    }
    return ret;
}
```
核心实现思想：先进行特判，若数组中存在相邻且相等的非 -1 元素，则方案数为 0。然后遍历数组，找到连续的 -1 序列，根据序列两端的情况（是否为数组边界、两端元素是否相等）计算方案数。

#### DPair
```cpp
inline void work(int len, int type)
{
    if(type >= 2) ans = (ans * dp[len][type & 1]) % MOD;
    if(type == 1)
    {
        if(len == 1) ans = (ans * (k - 1)) % MOD;
        else ans = (ans * ((((k - 1) * dp[len - 1][1]) % MOD + dp[len - 1][0]) % MOD)) % MOD;
    }
    if(type == 0)
    {
        if(len == 1) ans = (ans * k) % MOD;
        else if(len == 2) ans = (ans * ((k * (k - 1)) % MOD)) % MOD;
        else ans = (ans * (k * (((k - 1) * dp[len - 2][1] + dp[len - 2][0]) % MOD) % MOD) % MOD) % MOD;
    }
}
```
核心实现思想：根据连续 -1 序列的类型（两端元素情况）和长度，使用动态规划数组 `dp` 计算方案数，并更新最终答案。

#### Rui_R
```cpp
ll count(std::vector<int> v)
{
    ll res = 1;
    for(int i = 0; i < v.size();)
    {
        int j;
        if(v[i] == -1)
        {
            for(j = i + 1; v[j] == -1 && j < v.size(); j++);
            if(j == v.size())
            {
                if(v.size() == 1) return k;
                res = (dp[v.size() - 2][0] * (k - 1) + dp[v.size() - 2][1]) % mod;
                res *= k;
                res %= mod;
                return res;
            }
            else
            {
                res *= (dp[j - 1][0] * (k - 1) + dp[j - 1][1]);
                res %= mod; i = j;
            }
        }
        else
        {
            if(i == v.size() - 1) return res;
            for(j = i + 1; v[j] == -1 && j < v.size(); j++);
            if(j == v.size())
            {
                res *= (dp[v.size() - i - 2][0] * (k - 1) + dp[v.size() - i - 2][1]) % mod;
                res %= mod;
            }
            else
            {
                if(v[i] == v[j]) res *= dp[j - i - 1][1];
                else res *= (dp[j - i - 1][0]);
                res %= mod;
            }
            i = j;
        }
    }
    return res;
}
```
核心实现思想：遍历数组，找到连续的 -1 序列，根据序列两端的情况（是否为数组边界、两端元素是否相等）计算方案数，最终返回该数组的合法方案数。

### 最优关键思路或技巧
- **问题转化**：将“不存在长度大于 1 的奇数回文串”转化为“不存在长度为 3 的回文串”，进而得出数组中距离为 2 的元素不能相等，通过分奇偶处理数组，将问题简化为求相邻元素不相等的数组的方案数。
- **动态规划**：使用动态规划计算连续 -1 序列的方案数，根据序列两端元素的情况（是否相等、是否有限制）进行分类讨论，减少重复计算。

### 可拓展之处
同类型题或类似算法套路：
- 其他涉及回文串限制的计数问题，可尝试将问题转化为更简单的条件进行处理。
- 对于数组中部分元素可修改的计数问题，可考虑使用动态规划，根据元素之间的关系进行状态定义和转移。

### 推荐题目
- [P1879 [USACO06NOV]Corn Fields G](https://www.luogu.com.cn/problem/P1879)：状态压缩动态规划，与本题使用动态规划解决计数问题的思路类似。
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)：同样是状态压缩动态规划，在处理元素之间的限制关系上有相似之处。
- [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)：区间动态规划，通过对区间的划分和状态转移来解决问题，与本题中对连续 -1 序列的处理有一定的相似性。

---
处理用时：49.80秒