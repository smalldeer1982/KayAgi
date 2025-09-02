# 题目信息

# [USACO20FEB] Help Yourself G

## 题目描述

在一个数轴上有 $N$ 条线段，第 $i$ 条线段覆盖了从 $l_i$ 到 $r_i$ 的所有实数（包含 $l_i$ 和 $r_i$）。

定义若干条线段的**并**为一个包含了所有被至少一个线段覆盖的点的集合。

定义若干条线段的**复杂度**为这些线段的并形成的连通块的数目。

现在 Bessie 想要求出给定 $N$ 条线段的所有子集（共有 $2^N$ 个）的复杂度之和对 $10^9+7$ 取模的结果。

你也许猜到了，你需要帮 Bessie 解决这个问题。但不幸的是，你猜错了！在这道题中你就是 Bessie，而且没有人来帮助你。一切就靠你自己了！

## 说明/提示

### 样例解释

所有非空子集的复杂度如下所示（显然空集的复杂度为零）：
$$
\{[1,6]\} \implies 1, \{[2,3]\} \implies 1, \{[4,5]\} \implies 1
$$

$$
\{[1,6],[2,3]\} \implies 1, \{[1,6],[4,5]\} \implies 1, \{[2,3],[4,5]\} \implies 2
$$

$$
\{[1,6],[2,3],[4,5]\} \implies 1
$$

故答案为 $1+1+1+1+1+2+1=8$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 16$；
- 测试点 $4 \sim 7$ 满足 $N \leq 1000$；
- 测试点 $8 \sim 12$ 没有特殊限制。

## 样例 #1

### 输入

```
3
1 6
2 3
4 5```

### 输出

```
8```

# AI分析结果

• 综合分析与结论：
    - 思路：多数题解先将线段按左端点升序排序，通过动态规划思想，考虑新增线段对复杂度的影响。对于新增线段，从选与不选两种情况分析，选时计算与之前线段不相交的数量，进而得到状态转移方程。少数题解从每条线段贡献角度出发，通过线段树等数据结构辅助计算。
    - 算法要点：利用排序简化问题，通过动态规划递推计算答案，借助前缀和或线段树等数据结构维护与当前线段不相交的线段数量，快速幂计算 $2$ 的幂次方。
    - 解决难点：避免枚举所有子集带来的高复杂度，通过合理顺序添加线段，巧妙分析每条线段对答案的贡献，利用数据结构优化计算不相交线段数量的过程。
    - 整体来看，各题解思路相近，主要区别在于数据结构的选择和代码实现细节。

所选的题解：
  - **作者：StudyingFather (5星)**
    - **关键亮点**：思路清晰，代码简洁，直接利用前缀和预处理，递推过程明了。
    ```cpp
    #include <iostream>
    #include <algorithm>
    #define MOD 1000000007
    using namespace std;
    struct seg
    {
        int l,r;
    }a[100005];
    int s[200005];
    long long f[100005];
    bool cmp(const seg&a,const seg&b)
    {
        return a.l<b.l;
    }
    long long fpow(long long x,long long y)
    {
        long long ans=1;
        while(y)
        {
            if(y&1)ans=ans*x%MOD;
            x=x*x%MOD;
            y>>=1;
        }
        return ans;
    }
    int main()
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i].l>>a[i].r;
            s[a[i].r]++;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=2*n;i++)
            s[i]+=s[i-1];
        for(int i=1;i<=n;i++)
            f[i]=(2*f[i-1]+fpow(2,s[a[i].l-1]))%MOD;
        cout<<f[n]<<endl;
        return 0;
    }
    ```
    - **核心实现思想**：先对线段按左端点排序，用数组 `s` 统计每个右端点出现次数并转化为前缀和，通过 `fpow` 函数计算 $2$ 的幂次方，利用递推式 `f[i]=(2*f[i-1]+fpow(2,s[a[i].l-1]))%MOD` 计算前 $i$ 条线段所有子集的复杂度之和。
  - **作者：LTb_ (4星)**
    - **关键亮点**：结论清晰，证明过程详细，代码结构完整。
    ```cpp
    #include <iostream>
    #include <algorithm>
    #include <fstream>
    using namespace std;
    #define int long long
    const int MAXN=200005;
    const int MOD=1e9+7;
    int n;
    pair<int,int> a[MAXN];
    int l[MAXN],r[MAXN];
    int tmp[MAXN];
    int sum[MAXN];
    int dp[MAXN];

    inline int pow(int x,int y){
        int ans=1;
        while (y>0){
            if (y%2==0){
                x*=x;
                x%=MOD;
                y/=2;
            }
            ans*=x;
            ans%=MOD;
            y--;
        }
        return ans;
    }

    signed main()
    {
        freopen("help.in","r",stdin);
        freopen("help.out","w",stdout);
        cin>>n;
        for (int i=1;i<=n;i++)
            cin>>a[i].first>>a[i].second;

        sort(a+1,a+1+n);

        for (int i=1;i<=n;i++){
            l[i]=a[i].first;
            r[i]=a[i].second;
            tmp[r[i]]++;
        }

        for (int i=1;i<=MAXN-5;i++)
            sum[i]=sum[i-1]+tmp[i];

        for (int i=1;i<=n;i++)
            dp[i]=(dp[i-1]*2ll+pow(2ll,sum[l[i]-1]))%MOD;

        cout<<dp[n]<<endl;
        return 0;
    }
    ```
    - **核心实现思想**：同样先排序，用 `tmp` 数组统计右端点出现次数并转化为前缀和 `sum`，通过 `pow` 函数计算幂次方，利用递推式 `dp[i]=(dp[i-1]*2ll+pow(2ll,sum[l[i]-1]))%MOD` 计算答案。
  - **作者：一只书虫仔 (4星)**
    - **关键亮点**：解题思路阐述详细，动态规划的状态转移分析清晰，代码实现简洁易懂。
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;

    struct line {long long l, r;} a[100086];
    bool fjrakioi (line x, line y) {return x.l < y.l;}

    long long box[200086];
    long long cnt[200086];
    long long dp[100086];
    long long Mod = 1e9 + 7;

    long long binpow (long long b, long long p, long long k) {
        b %= k;
        long long res = 1;
        while (p > 0) {
            if (p & 1)
                res = res * b % k;
            b = b * b % k;
            p >>= 1;
        }
        return res;
    }

    int main () {
        long long n;
        scanf("%lld", &n);
        for (long long i = 1; i <= n; i++) scanf("%lld%lld", &a[i].l, &a[i].r);
        sort(a + 1, a + n + 1, fjrakioi);
        for (long long i = 1; i <= n; i++) box[a[i].r]++;
        for (long long i = 1; i <= 2 * n; i++) cnt[i] = cnt[i - 1] + box[i];
        for (long long i = 1; i <= n; i++) {
            dp[i] += dp[i - 1];
            dp[i] %= Mod;
            dp[i] += (dp[i - 1] + binpow(2, cnt[a[i].l - 1], Mod));
            dp[i] %= Mod;
        }
        printf("%lld", dp[n]);
        return 0;
    }
    ```
    - **核心实现思想**：对线段按左端点排序，用 `box` 数组统计右端点出现次数并转化为前缀和 `cnt`，通过 `binpow` 计算幂次方，利用递推式 `dp[i] += dp[i - 1]; dp[i] %= Mod; dp[i] += (dp[i - 1] + binpow(2, cnt[a[i].l - 1], Mod)); dp[i] %= Mod;` 计算答案。

• 最优关键思路或技巧：
    - **排序简化问题**：按左端点排序后，新增线段只需考虑与之前线段右端点的关系，大大简化分析过程。
    - **动态规划递推**：通过分析新增线段选与不选的情况，得到简洁的递推式，避免暴力枚举子集。
    - **前缀和优化**：利用前缀和快速统计与当前线段不相交的线段数量，降低时间复杂度。

• 同类型题或类似算法套路：
    - 此类题目通常涉及集合、子集的某些统计量计算，关键在于避免暴力枚举子集。套路是先对元素排序，通过动态规划分析每个元素加入集合时对目标统计量的影响，常借助数据结构优化某些计算过程。

• 推荐洛谷题目：
    - P1439 【模板】最长公共子序列：涉及动态规划，通过分析状态转移计算最长公共子序列长度。
    - P1880 [NOI1995] 石子合并：经典区间动态规划问题，分析合并石子过程中的最优决策。
    - P3146 [USACO16OPEN]248 G：同样是动态规划，通过合并数字得到最大数字，分析合并过程状态转移。

• 个人心得：无。 

---
处理用时：81.28秒