# 题目信息

# New Year and Permutation

## 题目描述

Recall that the permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A sequence $ a $ is a subsegment of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. We will denote the subsegments as $ [l, r] $ , where $ l, r $ are two integers with $ 1 \le l \le r \le n $ . This indicates the subsegment where $ l-1 $ elements from the beginning and $ n-r $ elements from the end are deleted from the sequence.

For a permutation $ p_1, p_2, \ldots, p_n $ , we define a framed segment as a subsegment $ [l,r] $ where $ \max\{p_l, p_{l+1}, \dots, p_r\} - \min\{p_l, p_{l+1}, \dots, p_r\} = r - l $ . For example, for the permutation $ (6, 7, 1, 8, 5, 3, 2, 4) $ some of its framed segments are: $ [1, 2], [5, 8], [6, 7], [3, 3], [8, 8] $ . In particular, a subsegment $ [i,i] $ is always a framed segments for any $ i $ between $ 1 $ and $ n $ , inclusive.

We define the happiness of a permutation $ p $ as the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ , and $ [l, r] $ is a framed segment. For example, the permutation $ [3, 1, 2] $ has happiness $ 5 $ : all segments except $ [1, 2] $ are framed segments.

Given integers $ n $ and $ m $ , Jongwon wants to compute the sum of happiness for all permutations of length $ n $ , modulo the prime number $ m $ . Note that there exist $ n! $ (factorial of $ n $ ) different permutations of length $ n $ .

## 说明/提示

For sample input $ n=3 $ , let's consider all permutations of length $ 3 $ :

- $ [1, 2, 3] $ , all subsegments are framed segment. Happiness is $ 6 $ .
- $ [1, 3, 2] $ , all subsegments except $ [1, 2] $ are framed segment. Happiness is $ 5 $ .
- $ [2, 1, 3] $ , all subsegments except $ [2, 3] $ are framed segment. Happiness is $ 5 $ .
- $ [2, 3, 1] $ , all subsegments except $ [2, 3] $ are framed segment. Happiness is $ 5 $ .
- $ [3, 1, 2] $ , all subsegments except $ [1, 2] $ are framed segment. Happiness is $ 5 $ .
- $ [3, 2, 1] $ , all subsegments are framed segment. Happiness is $ 6 $ .

Thus, the sum of happiness is $ 6+5+5+5+5+6 = 32 $ .

## 样例 #1

### 输入

```
1 993244853```

### 输出

```
1```

## 样例 #2

### 输入

```
2 993244853```

### 输出

```
6```

## 样例 #3

### 输入

```
3 993244853```

### 输出

```
32```

## 样例 #4

### 输入

```
2019 993244853```

### 输出

```
923958830```

## 样例 #5

### 输入

```
2020 437122297```

### 输出

```
265955509```

# AI分析结果

### 题目翻译
#### 新年与排列

### 题目描述
回顾一下，排列是一个由 $n$ 个不同整数组成的数组，这些整数的范围是从 $1$ 到 $n$，顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是一个排列（$ 2 $ 在数组中出现了两次），$ [1,3,4] $ 也不是一个排列（$ n = 3 $，但数组中有 $ 4 $）。

序列 $ a $ 是序列 $ b $ 的一个子段，如果 $ a $ 可以通过从 $ b $ 的开头删除若干（可能为零个或全部）元素，以及从 $ b $ 的结尾删除若干（可能为零个或全部）元素得到。我们将子段表示为 $ [l, r] $，其中 $ l $ 和 $ r $ 是两个整数，且 $ 1 \le l \le r \le n $。这表示从序列中删除开头的 $ l - 1 $ 个元素和结尾的 $ n - r $ 个元素后得到的子段。

对于一个排列 $ p_1, p_2, \ldots, p_n $，我们将有框子段定义为一个子段 $ [l, r] $，其中 $ \max\{p_l, p_{l + 1}, \dots, p_r\} - \min\{p_l, p_{l + 1}, \dots, p_r\} = r - l $。例如，对于排列 $ (6, 7, 1, 8, 5, 3, 2, 4) $，它的一些有框子段是：$ [1, 2], [5, 8], [6, 7], [3, 3], [8, 8] $。特别地，对于任何介于 $ 1 $ 到 $ n $（包含 $ 1 $ 和 $ n $）之间的 $ i $，子段 $ [i, i] $ 总是有框子段。

我们将排列 $ p $ 的幸福度定义为满足 $ 1 \le l \le r \le n $ 且 $ [l, r] $ 是有框子段的数对 $ (l, r) $ 的数量。例如，排列 $ [3, 1, 2] $ 的幸福度是 $ 5 $：除了 $ [1, 2] $ 之外的所有子段都是有框子段。

给定整数 $ n $ 和 $ m $，Jongwon 想要计算长度为 $ n $ 的所有排列的幸福度之和，并对质数 $ m $ 取模。注意，长度为 $ n $ 的不同排列有 $ n! $（$ n $ 的阶乘）个。

### 说明/提示
对于样例输入 $ n = 3 $，让我们考虑所有长度为 $ 3 $ 的排列：
- $ [1, 2, 3] $，所有子段都是有框子段。幸福度是 $ 6 $。
- $ [1, 3, 2] $，除了 $ [1, 2] $ 之外的所有子段都是有框子段。幸福度是 $ 5 $。
- $ [2, 1, 3] $，除了 $ [2, 3] $ 之外的所有子段都是有框子段。幸福度是 $ 5 $。
- $ [2, 3, 1] $，除了 $ [2, 3] $ 之外的所有子段都是有框子段。幸福度是 $ 5 $。
- $ [3, 1, 2] $，除了 $ [1, 2] $ 之外的所有子段都是有框子段。幸福度是 $ 5 $。
- $ [3, 2, 1] $，所有子段都是有框子段。幸福度是 $ 6 $。

因此，幸福度之和是 $ 6 + 5 + 5 + 5 + 5 + 6 = 32 $。

### 样例 #1
#### 输入
```
1 993244853
```
#### 输出
```
1
```

### 样例 #2
#### 输入
```
2 993244853
```
#### 输出
```
6
```

### 样例 #3
#### 输入
```
3 993244853
```
#### 输出
```
32
```

### 样例 #4
#### 输入
```
2019 993244853
```
#### 输出
```
923958830
```

### 样例 #5
#### 输入
```
2020 437122297
```
#### 输出
```
265955509
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是通过组合数学的方法来计算长度为 $n$ 的所有排列的幸福度之和。具体做法是枚举不同长度的区间，计算每个长度区间对答案的贡献，最后累加得到结果。

不同题解在思路的阐述和公式的推导上略有不同，但最终得到的计算公式本质上是相同的，大多为 $\sum_{i = 1}^{n} (n - i + 1)! \times i! \times (n - i + 1)$ 或等价形式。

在实现上，都需要预处理阶乘以提高效率，并且要注意取模操作，避免溢出。

### 所选题解
- **作者：Meatherm (赞：3)，4星**
  - **关键亮点**：思路清晰，公式推导简洁明了，代码实现简单易懂，使用了预处理阶乘的优化方法。
  - **核心代码**：
```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N = 250010;
int MOD;
int n;
int sum;
int seque[N];
signed main(void) {
    scanf("%I64d%I64d", &n, &MOD);
    seque[0] = 1;
    for (rr int i = 1; i <= n; ++i) {
        seque[i] = (seque[i - 1] * i) % MOD;
    }
    for (rr int i = 1; i <= n; ++i) {
        sum = (sum + ((n - i + 1) % MOD * (seque[i]) % MOD) % MOD * (seque[n - i + 1]) % MOD);
    }
    printf("%I64d", sum % MOD);
    return 0;
}
```
**核心实现思想**：先预处理出 $1$ 到 $n$ 的阶乘对 $MOD$ 取模的结果，存储在 `seque` 数组中。然后枚举区间长度 $i$，根据公式 $(n - i + 1)! \times i! \times (n - i + 1)$ 计算每个长度区间的贡献，并累加到 `sum` 中，最后输出 `sum` 对 $MOD$ 取模的结果。

- **作者：I_am_Accepted (赞：1)，4星**
  - **关键亮点**：思路清晰，通过具体例子解释了计算过程，代码注释详细，适合新手学习。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, j, k) for(register int i = j; (j < k)?(i <= k):(i >= k); i += (j < k)?1:(-1))
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 255000

ll n, mod;
ll f[N];//带模阶乘 
ll sum = 0;//ans求和 
void init() {
    f[0] = 1;
    FOR(i, 1, n) f[i] = f[i - 1] * i % mod;
}
signed main() {
    IO;
    cin >> n >> mod;
    init();
    FOR(i, 1, n) sum = (sum + f[n - i + 1] * f[i] % mod * (n - i + 1) % mod) % mod;
    cout << sum << endl;
    return 0;
}
```
**核心实现思想**：`init` 函数预处理出 $1$ 到 $n$ 的阶乘对 $mod$ 取模的结果，存储在 `f` 数组中。在 `main` 函数中，枚举区间长度 $i$，根据公式 $(n - i + 1)! \times i! \times (n - i + 1)$ 计算每个长度区间的贡献，并累加到 `sum` 中，最后输出 `sum` 对 $mod$ 取模的结果。

- **作者：gyh20 (赞：1)，4星**
  - **关键亮点**：思路简洁，代码实现简单，直接根据公式进行计算。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read() {
    re int t = 0;
    re char v = getchar();
    while (v < '0' || v > '9') v = getchar();
    while (v >= '0' && v <= '9') {
        t = (t << 3) + (t << 1) + (v ^ 48);
        v = getchar();
    }
    return t;
}
long long n, m, jc[250002];
long long ans;
int main() {
    n = read();
    m = read();
    jc[0] = 1;
    for (re int i = 1; i <= n; ++i) jc[i] = jc[i - 1] * i % m;
    for (re int i = 1; i <= n; ++i) {
        ans += (n - i + 1) * jc[i] % m * (n - i + 1) % m * jc[n - i] % m;
        ans %= m;
    }
    printf("%lld", ans);
}
```
**核心实现思想**：先预处理出 $1$ 到 $n$ 的阶乘对 $m$ 取模的结果，存储在 `jc` 数组中。然后枚举区间长度 $i$，根据公式 $(n - i + 1)! \times i! \times (n - i + 1)$ 计算每个长度区间的贡献，并累加到 `ans` 中，最后输出 `ans` 对 $m$ 取模的结果。

### 最优关键思路或技巧
- **转换思维**：从直接计算每个排列的幸福度，转换为计算每个长度区间对答案的贡献，大大简化了计算过程。
- **预处理阶乘**：在计算过程中，多次用到阶乘，预处理阶乘可以将每次计算阶乘的时间复杂度从 $O(n)$ 降低到 $O(1)$，提高了效率。
- **取模操作**：由于结果可能很大，在计算过程中及时取模，避免溢出。

### 拓展思路
同类型的题目通常会涉及到排列组合的计算，例如计算满足某种条件的排列或组合的数量。类似的算法套路包括枚举不同的情况，计算每种情况的贡献，最后累加得到结果。在实现上，可能需要预处理一些数据，如阶乘、组合数等，以提高效率。

### 推荐题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：涉及数论和数学推导，与本题的数学思维有一定的相似性。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：需要运用组合数学的知识来计算系数，与本题的组合数学知识点相关。
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要通过数学分析和枚举来计算满足条件的数对的和，与本题的枚举和计算贡献的思路类似。

### 个人心得
- **作者：liuyz11**：提到一开始看题有点慌，浪费了好多时间，后来才想到分别统计长度为 $i$ 的子段满足条件。这提醒我们在遇到难题时要冷静思考，尝试从不同的角度去分析问题。

---
处理用时：79.14秒