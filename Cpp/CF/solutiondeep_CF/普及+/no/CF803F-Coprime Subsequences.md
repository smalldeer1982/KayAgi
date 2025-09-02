# 题目信息

# Coprime Subsequences

## 题目描述

Let's call a non-empty sequence of positive integers $ a_{1},a_{2}...\ a_{k} $ coprime if the greatest common divisor of all elements of this sequence is equal to $ 1 $ .

Given an array $ a $ consisting of $ n $ positive integers, find the number of its coprime subsequences. Since the answer may be very large, print it modulo $ 10^{9}+7 $ .

Note that two subsequences are considered different if chosen indices are different. For example, in the array $ [1,1] $ there are $ 3 $ different subsequences: $ [1] $ , $ [1] $ and $ [1,1] $ .

## 说明/提示

In the first example coprime subsequences are:

1. $ 1 $
2. $ 1,2 $
3. $ 1,3 $
4. $ 1,2,3 $
5. $ 2,3 $

In the second example all subsequences are coprime.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
15
```

## 样例 #3

### 输入

```
7
1 3 5 15 3 105 35
```

### 输出

```
100
```

# AI分析结果

### 题目内容
# 互质子序列

## 题目描述
我们称一个由正整数 \(a_{1},a_{2},\cdots,a_{k}\) 组成的非空序列是互质的，如果该序列所有元素的最大公约数等于 \(1\)。

给定一个由 \(n\) 个正整数组成的数组 \(a\)，求其互质子序列的数量。由于答案可能非常大，请将结果对 \(10^{9}+7\) 取模后输出。

注意，如果选择的索引不同，则两个子序列被认为是不同的。例如，在数组 \([1,1]\) 中有 \(3\) 个不同的子序列：\([1]\)，\([1]\) 和 \([1,1]\)。

## 说明/提示
在第一个示例中，互质子序列为：
1. \(1\)
2. \(1,2\)
3. \(1,3\)
4. \(1,2,3\)
5. \(2,3\)

在第二个示例中，所有子序列都是互质的。

## 样例 #1
### 输入
```
3
1 2 3
```
### 输出
```
5
```

## 样例 #2
### 输入
```
4
1 1 1 1
```
### 输出
```
15
```

## 样例 #3
### 输入
```
7
1 3 5 15 3 105 35
```
### 输出
```
100
```

### 算法分类
数学（容斥原理、莫比乌斯反演相关）

### 综合分析与结论
所有题解核心思路均围绕容斥原理展开，通过计算非互质子序列（即\(\gcd > 1\)的子序列）的数量，从总子序列数量\(2^n - 1\)中减去，从而得到互质子序列的数量。部分题解利用莫比乌斯反演优化计算过程。各题解在具体实现细节上略有不同，例如计算倍数个数的方式、容斥的具体实现形式等，但整体思路相近。

### 所选的题解
- **作者：Lauzun（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了容斥原理在本题中的应用，对取模操作的细节处理有明确说明，代码可读性高。
    - **个人心得**：写题写累了摸鱼写题解，从朴素DP思路引入容斥原理解题。
    ```cpp
    #include<stdio.h>
    #define maxn 100005
    #define mod 1000000007
    using namespace std;
    int n, x;
    long long dp[maxn], cnt[maxn], pow[maxn];
    int main() {
        scanf("%d", &n);
        pow[0] = 1;
        for(int i = 1; i <= n; i ++) {
            scanf("%d", &x);
            cnt[x] ++;
            pow[i] = (long long)(pow[i - 1] * 2ll) % mod;
        }
        for(int i = maxn - 1; i >= 1; i --) {
            long long sum = 0;
            for(int j = i; j < maxn; j += i)
                sum = (sum + cnt[j]) % mod;
            dp[i] = pow[sum] - 1;
            for(int j = 2 * i; j < maxn; j += i)
                dp[i] = (dp[i] - dp[j] + mod) % mod;
        }
        printf("%lld\n", dp[1]);
    }
    ```
    - **核心代码简述**：倒序枚举因子\(i\)，计算序列中\(i\)的倍数总数\(sum\)，得到\(dp[i] = 2^{sum} - 1\)，再通过枚举\(i\)的倍数\(j\)，从\(dp[i]\)中减去\(dp[j]\)避免重复，最后输出\(dp[1]\)。
- **作者：forever_nope（4星）**
    - **关键亮点**：清晰阐述容斥原理，定义明确，对时间复杂度有分析，代码使用C++ 11特性，简洁明了。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    constexpr int N = 1e5 + 10;
    constexpr ll MOD = 1e9 + 7;
    int app[N];
    ll fac[N], g[N];
    inline ll mns(ll a, ll b) {
        return (a - b + MOD) % MOD;
    }
    signed main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr), cout.tie(nullptr);
        int n, x; cin >> n;
        for (int i = 0; i < n; ++i) cin >> x, ++app[x];
        fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * 2 % MOD;
        for (int i = N - 1; i; --i) {
            int cnt = 0; for (int j = i; j < N; j += i) cnt += app[j];
            g[i] = fac[cnt] - 1;
            for (int j = i + i; j < N; j += i) g[i] = mns(g[i], g[j]);
        } cout << g[1] << endl;
        return 0;
    }
    ```
    - **核心代码简述**：倒序遍历\(i\)，统计\(i\)的倍数个数\(cnt\)，得出\(g[i] = 2^{cnt} - 1\)，再通过枚举\(i\)的倍数\(j\)，从\(g[i]\)中减去\(g[j]\)，最后输出\(g[1]\)。
- **作者：fanfansann（4星）**
    - **关键亮点**：详细推导了容斥原理下的公式，指出系数与莫比乌斯函数的关系，对时间复杂度有分析。
    - **核心思路**：设\(cnt_i\)表示权值为\(i\)的数的个数，\(sum_i\)表示含有因子\(i\)的数的个数，\(f_i\)表示含有因子\(i\)的子序列个数。根据容斥原理，答案为\(2^n - 1+\sum_{i = 2}^{m}\mu(i)\times f_i\)。
    - **代码链接**：[https://paste.ubuntu.com/p/T8dcy6cGS2/](https://paste.ubuntu.com/p/T8dcy6cGS2/) 

### 最优关键思路或技巧
利用容斥原理，通过倒序枚举因子，计算每个因子倍数构成的子序列数量，并处理重复计算部分，避免直接暴力枚举所有子序列计算\(\gcd\)，有效降低时间复杂度。部分题解利用莫比乌斯反演优化计算过程，使计算更简洁高效。

### 可拓展之处
此类题目属于数论与组合结合的问题，常见套路为利用容斥原理或莫比乌斯反演，通过统计倍数关系来间接计算目标子序列数量。类似题目通常围绕数的整除关系、最大公约数等数论概念与序列组合问题相结合。

### 洛谷推荐题目
- [P1829 [国家集训队]Crash的数字表格 / JZPTAB](https://www.luogu.com.cn/problem/P1829)
- [P3455 [POI2007]ZAP-Queries](https://www.luogu.com.cn/problem/P3455)
- [P2257 YY的GCD](https://www.luogu.com.cn/problem/P2257)

---
处理用时：63.35秒