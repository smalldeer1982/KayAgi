# 题目信息

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 好序列

## 题目描述
松鼠莉丝对序列很感兴趣。她对整数也有偏好。她认为 $n$ 个整数 $a_{1},a_{2},\cdots,a_{n}$ 是好的。

现在她对好序列感兴趣。一个序列 $x_{1},x_{2},\cdots,x_{k}$ 被称为好序列，如果它满足以下三个条件：
- 该序列严格递增，即对于每个 $i$ （$1\leq i\leq k - 1$），都有 $x_{i}<x_{i + 1}$。
- 任意两个相邻元素不互质，即对于每个 $i$ （$1\leq i\leq k - 1$），都有 $\gcd(x_{i},x_{i + 1})>1$（其中 $\gcd(p,q)$ 表示整数 $p$ 和 $q$ 的最大公约数）。
- 序列的所有元素都是好整数。

求最长好序列的长度。

## 说明/提示
在第一个示例中，以下序列是好序列的示例：\[2; 4; 6; 9\]，\[2; 4; 6\]，\[3; 9\]，\[6\]。最长好序列的长度是 4。

## 样例 #1
### 输入
```
5
2 3 4 6 9
```
### 输出
```
4
```

## 样例 #2
### 输入
```
9
1 2 3 5 6 7 8 9 10
```
### 输出
```
4
```

### 题解综合分析与结论
1. **思路**：大部分题解都采用动态规划（DP）的思路。先考虑朴素DP，设$dp[i]$表示结尾位置为$i$的最长好序列，转移方程为$dp[i]=\max(dp[j]) + 1$（$j\in(1,i - 1),\gcd(a[i],a[j])>1$），但该方法时间复杂度为$O(n^2\log n)$，在大数据下会超时。
2. **算法要点**：为优化转移，利用“两个数不互质则必有相同质因子”这一特性。通过预处理每个数的质因子，设$f[i]$表示含有因子$i$的$a[x]$中的最大$dp[x]$ 。转移时，枚举当前数$a[i]$的质因子，从这些质因子对应的$f$值中取最大的来更新$dp[i]$，然后再用$dp[i]$更新这些质因子对应的$f$值。
3. **解决难点**：核心难点在于优化朴素DP的转移过程，减少枚举量。通过将$\gcd$问题转化为质因子问题，大大降低了时间复杂度。不同题解在具体实现上，如质因子的预处理方式、状态转移的细节等略有差异，但整体思路一致。

### 所选的题解
1. **作者：傅思维666 (5星)**
    - **关键亮点**：思路清晰，不仅给出朴素DP解法，还详细阐述了优化思路。先分析朴素DP的不足，再从GCD入手，提出通过设置$f[i]$表示含有因子$i$的$a[x]$中的最大$dp[x]$来优化转移，极大提高枚举效率。代码实现规范，注释详细。
    - **个人心得**：在21号点折戟，促使思考优化方案，这种从失败案例中找优化方向的思路值得借鉴。
    - **重点代码核心思想**：先预处理出质数和每个数的质因子，在DP过程中，对于每个数$a[i]$，枚举其质因子，找到对应$f$值的最大值来更新$dp[i]$，然后用$dp[i]$更新这些质因子对应的$f$值。
    - **核心代码片段**：
```cpp
void init()
{
    for(int i = 2; i <= maxx; i++)
    {
        if(!v[i])
            prime[++tot] = i;
        for(int j = 1; j <= tot && i * prime[j] <= maxx; j++)
        {
            v[i * prime[j]] = 1;
            if(i % prime[j] == 0)
                break;
        }
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        dp[i] = 1;
        maxx = max(maxx, a[i]);
    }
    init();
    for(int i = 1; i <= tot; i++)
        for(int j = prime[i]; j <= maxx; j += prime[i])
            fac[j].push_back(prime[i]);
    for(int i = 1; i <= n; i++)
    {
        int tmp = 0;
        for(int j = 0; j < fac[a[i]].size(); j++)
            tmp = max(tmp, f[fac[a[i]][j]]);
        dp[i] = max(dp[i], tmp + 1);
        for(int j = 0; j < fac[a[i]].size(); j++)
            f[fac[a[i]][j]] = max(f[fac[a[i]][j]], dp[i]);
    }
    for(int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}
```
2. **作者：是个汉子 (4星)**
    - **关键亮点**：在常规DP优化思路基础上，指出更新$f_d$时可以只更新质因子的$f$，因为非质因子在枚举质因子时已更新，且质因子答案不会比非质因子差，还提到$dp$数组可省略，直接与$ans$更新，进一步优化空间和代码简洁性。
    - **重点代码核心思想**：通过`read`函数读入数据，`solve`函数处理每个数，先枚举数的因子找到最大的$f$值来更新当前数的答案，再更新这些因子对应的$f$值，同时直接更新$ans$。
    - **核心代码片段**：
```cpp
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)){x = x * 10 + (ch ^ 48); ch = getchar();}
    return x * f;
}
inline void solve(int x)
{
    int m = sqrt(x), sum = 0;
    for(int i = 2; i <= m; i++)
        if(x % i == 0) sum = max(max(sum, f[i]), f[x / i]);
    sum = max(sum, f[x]);
    for(int i = 2; i <= m; i++)
        if(x % i == 0)
        {
            f[i] = sum + 1;
            while(x % i == 0) x /= i;
        }
    f[x] = sum + 1;
    ans = max(ans, sum + 1);
}
int main()
{
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= n; i++) solve(a[i]);
    printf("%d\n", ans);
    return 0;
}
```
3. **作者：xuantianhao (4星)**
    - **关键亮点**：状态定义清晰，转移过程简洁明了。通过线性筛预处理质数，利用每个数的质因子来优化DP转移，准确把握问题本质，代码实现简洁高效，时间复杂度分析准确。
    - **重点代码核心思想**：先通过`prime`函数线性筛预处理质数，在处理每个数$x$时，通过两次循环，一次根据质因子更新$f[i]$，一次根据$f[i]$更新对应质因子的$mx$值，并不断更新$res$。
    - **核心代码片段**：
```cpp
void prime()
{
    for(int i = 2; i <= N; i++)
    {
        if(!p[i]){p[++p[0]] = i; pre[i] = p[0];}
        for(int j = 1; j <= p[0] && i * p[j] <= N; j++)
        {
            p[i * p[j]] = true;
            pre[i * p[j]] = j;
            if(!(i % p[j])) break;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    prime();
    for(int i = 1; i <= n; i++)
    {
        cin >> x;
        f[i] = 1;
        t = x;
        while(t!= 1)
        {
            f[i] = max(f[i], mx[pre[t]] + 1);
            t /= p[pre[t]];
        }
        t = x;
        while(t!= 1)
        {
            mx[pre[t]] = f[i];
            t /= p[pre[t]];
        }
        res = max(res, f[i]);
    }
    printf("%d\n", res);
    return 0;
}
```

### 最优关键思路或技巧
将$\gcd$问题转化为质因子问题，通过预处理质因子和设置辅助数组$f[i]$（表示含有因子$i$的$a[x]$中的最大$dp[x]$），优化动态规划的转移过程，降低时间复杂度。在实现过程中，注意可以只更新质因子对应的辅助数组值，以减少不必要计算，还可根据情况省略一些中间数组，优化空间复杂度和代码简洁性。

### 可拓展之处
同类型题常出现在序列相关的动态规划题目中，条件可能会围绕数论关系（如整除、同余等）设置。类似算法套路是当朴素DP在时间复杂度上无法满足要求时，分析条件中的数论关系，利用数论性质（如质因数分解、约数等）优化转移过程。

### 相似知识点洛谷题目
1. **P1439 【模板】最长公共子序列**：通过动态规划求解最长公共子序列，与本题类似在于都涉及序列的动态规划，锻炼状态定义和转移方程推导能力。
2. **P1020 导弹拦截**：经典的动态规划题目，涉及最长上升子序列和最长不上升子序列问题，与本题在序列相关DP思路上有相似之处。
3. **P3957 [NOIP2017 普及组] 跳房子**：同样是序列上的动态规划问题，结合了一些条件限制，可进一步巩固动态规划优化的技巧。 

---
处理用时：43.32秒