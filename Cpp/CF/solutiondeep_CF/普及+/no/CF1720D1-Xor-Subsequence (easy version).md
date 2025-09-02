# 题目信息

# Xor-Subsequence (easy version)

## 题目描述

这是此问题的简单版本。简单版本与困难版本的唯一区别在于：在简单版本中，$a_i\leq 200$。

给你一个长为 $n$ 的整数数组 $a$，从 $0$ 开始编号。

一个长为 $m$ ，从 $0$ 开始编号的整数数组 $b$ 是数组 $a$ 的 subsequence，当且仅当 $0\leq b_0<b_1<\dots<b_{m-1}<n$。

若 $b$ 是 $a$ 的 beautiful subsequence，当且仅当满足以下条件：

+ $b$ 是 $a$ 的 subsequence；
+ $\forall p\in[0,m)\cap\textbf{N},a_{b_p}\oplus b_{p+1}<a_{b_{p+1}}\oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的 beautiful subsequence 有多长。

## 说明/提示

$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 200,\sum n\leq 3\times 10^5$。

## 样例 #1

### 输入

```
3
2
1 2
5
5 2 4 3 1
10
3 8 8 2 9 1 6 2 8 3```

### 输出

```
2
3
6```

# AI分析结果

### 题目中文重写
# Xor - 子序列（简单版本）

## 题目描述
这是此问题的简单版本。简单版本与困难版本的唯一区别在于：在简单版本中，$a_i\leq 200$。

给你一个长度为 $n$ 的整数数组 $a$，数组下标从 $0$ 开始。

一个长度为 $m$ 且下标从 $0$ 开始的整数数组 $b$ 是数组 $a$ 的子序列，当且仅当 $0\leq b_0 < b_1 < \cdots < b_{m - 1} < n$。

若 $b$ 是 $a$ 的美丽子序列，当且仅当满足以下条件：
- $b$ 是 $a$ 的子序列；
- $\forall p\in[0,m)\cap\mathbb{N},a_{b_p}\oplus b_{p + 1}<a_{b_{p + 1}}\oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的美丽子序列的长度。

## 说明/提示
$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 200,\sum n\leq 3\times 10^5$。

## 样例 #1
### 输入
```
3
2
1 2
5
5 2 4 3 1
10
3 8 8 2 9 1 6 2 8 3
```

### 输出
```
2
3
6
```

### 算法分类
动态规划

### 综合分析与结论
这些题解大多先提出朴素的 $O(n^2)$ 动态规划解法，设 $dp_i$ 表示以 $i$ 结尾的最长美丽子序列长度，状态转移方程为 $dp_i=\max\limits_{j = 1}^{i - 1}[a_j \oplus i < a_i \oplus j] \{dp_j + 1\}$。然后利用题目中 $a_i\leq 200$ 这个条件进行优化，主要有两种优化思路：
1. **利用异或性质推导范围**：根据异或的性质 $x - y\leq x \oplus y \leq x + y$，推导出 $i - j < a_i + a_j\leq 400$，从而将 $j$ 的枚举范围缩小到 $\max\{0, i - 400\}$ 到 $(i - 1)$，时间复杂度降为 $O(400n)$。
2. **利用二进制位数分析**：由于 $a_i$ 的二进制表示最多八位，最多影响 $i$ 的低八位，所以满足条件的 $i,j$ 除低八位以外的所有位数必定相同，对于所有的 $i$，只需要枚举到 $i - 256$ 即可，时间复杂度降为 $O(256n)$。

### 所选题解
- **作者：liangbowen (赞：25)，4星**
    - **关键亮点**：思路清晰，先给出朴素 DP 思路，再详细推导如何利用异或性质优化枚举范围，代码注释详细，可读性高。
- **作者：Blunt_Feeling (赞：9)，4星**
    - **关键亮点**：推导过程详细，从按位异或的性质出发，逐步推导出 $j$ 的枚举范围，代码简洁明了。
- **作者：simonG (赞：7)，4星**
    - **关键亮点**：从二进制位数的角度分析，合理地缩小了枚举范围，代码结构清晰。

### 重点代码
#### 作者：liangbowen
```cpp
const int N = 3e5 + 5;
int a[N], dp[N];
void solve()
{
    int n = read(), maxn = 0;
    for (int i = 0; i < n; i++) a[i] = read(), dp[i] = 1; 
    for (int i = 0; i < n; maxn = max(maxn, dp[i]), i++) 
        for (int j = max(i - 400, 0); j < i; j++)  
            if ( (a[j] ^ i) < (a[i] ^ j) ) 
                dp[i] = max(dp[i], dp[j] + 1);
    write(maxn), endl;
}
```
**核心实现思想**：先初始化数组 $a$ 和 $dp$ 数组，然后枚举每个位置 $i$，对于每个 $i$，从 $\max(i - 400, 0)$ 到 $i - 1$ 枚举 $j$，若满足 $a_j \oplus i < a_i \oplus j$，则更新 $dp[i]$。

#### 作者：Blunt_Feeling
```cpp
const int maxn = 300050;
int T, n, a[maxn], f[maxn], ans;
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        For(i, 0, n - 1) cin >> a[i];
        ans = f[0] = 1;
        For(i, 1, n - 1)
        {
            f[i] = 1;
            For(j, max(0, i - 401), i - 1)
                if ((a[j] ^ i) < (a[i] ^ j))
                    f[i] = max(f[i], f[j] + 1);
            ans = max(ans, f[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
```
**核心实现思想**：多组数据输入，对于每组数据，初始化数组 $a$ 和 $f$ 数组，然后枚举每个位置 $i$，从 $\max(0, i - 401)$ 到 $i - 1$ 枚举 $j$，若满足 $a_j \oplus i < a_i \oplus j$，则更新 $f[i]$，最后输出最大的 $f[i]$。

#### 作者：simonG
```cpp
const int N = 3e5 + 10, M = 256;
int t, n, a[N], f[N], ans;
int main() {
    scanf("%d", &t);
    for (; t; t--) {
        scanf("%d", &n);
        ans = 0;
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = 0; i < n; i++)
            f[i] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = max(0, i - M + 1); j < i; j++) {
                if ((a[j] ^ i) < (a[i] ^ j)) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
        }
        for (int i = 0; i < n; i++) ans = max(ans, f[i]);
        printf("%d\n", ans);
    }
    return 0;
}
```
**核心实现思想**：多组数据输入，对于每组数据，初始化数组 $a$ 和 $f$ 数组，然后枚举每个位置 $i$，从 $\max(0, i - 256 + 1)$ 到 $i - 1$ 枚举 $j$，若满足 $a_j \oplus i < a_i \oplus j$，则更新 $f[i]$，最后输出最大的 $f[i]$。

### 最优关键思路或技巧
- **利用题目条件优化枚举范围**：通过分析异或的性质和 $a_i$ 的范围，将原本 $O(n^2)$ 的枚举范围缩小，从而降低时间复杂度。
- **二进制位数分析**：从二进制的角度分析 $a_i$ 对异或结果的影响，合理地缩小枚举范围。

### 可拓展之处
同类型题可能会改变数组元素的范围或异或条件，解题思路可以类似，先考虑朴素的动态规划解法，再根据题目给定的特殊条件进行优化。例如，若改变异或条件，可以从新条件的数学性质或二进制性质入手，寻找优化枚举范围的方法。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：经典的最长上升子序列问题，与本题的动态规划思想有相似之处。
2. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：涉及动态规划求解最长公共子序列，有助于加深对动态规划的理解。
3. [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)：动态规划求解字符串编辑距离问题，锻炼动态规划的状态设计和转移方程推导能力。

### 个人心得摘录与总结
- **作者：lndjy**：提到做 dp 优化题一般想办法把和 $i,j$ 有关的项分离开，当遇到异或无法分离时可以考虑拆位，为解决类似问题提供了思路。

---
处理用时：57.45秒