# 题目信息

# George and Job

## 题目描述

新款手机 iTone6 近期上市，George 很想买一只。不幸地，George 没有足够的钱，所以 George 打算当一名程序猿去打工。现在George遇到了一个问题。
给出一组有 $n$ 个整数的数列 $p_1,p_2,...,p_n$ ,你需要挑出 $k$ 组长度为 $m$ 的数，要求这些数互不重叠
即$ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{k},r_{k}] (1<=l_{1}<=r_{1}<l_{2}<=r_{2}<...<l_{k}<=r_{k}<=n; r_{i}-l_{i}+1=m)$
使选出的数的和值最大，请你帮助George码出这份代码

## 样例 #1

### 输入

```
5 2 1
1 2 3 4 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
7 1 3
2 10 7 18 5 33 0
```

### 输出

```
61
```

# AI分析结果

### 题目内容
# George和工作

## 题目描述
新款手机iTone6近期上市，George很想买一只。不幸的是，George没有足够的钱，所以George打算当一名程序员去打工。现在George遇到了一个问题。
给出一组有$n$个整数的数列$p_1,p_2,\cdots,p_n$ ，你需要挑出$k$组长度为$m$的数，要求这些数互不重叠，即$ [l_{1},r_{1}],[l_{2},r_{2}],\cdots,[l_{k},r_{k}] (1\leq l_{1}\leq r_{1}<l_{2}\leq r_{2}<\cdots<l_{k}\leq r_{k}\leq n; r_{i}-l_{i}+1=m)$，使选出的数的和值最大，请你帮助George写出这份代码。

## 样例 #1
### 输入
```
5 2 1
1 2 3 4 5
```
### 输出
```
9
```

## 样例 #2
### 输入
```
7 1 3
2 10 7 18 5 33 0
```
### 输出
```
61
```

### 综合分析与结论
这些题解的核心思路都是使用动态规划（DP）来解决问题，同时借助前缀和优化计算区间和的时间复杂度。
1. **思路**：定义二维数组`dp[i][j]`表示前`i`个数中选`j`个区间能取得的最大值。对于每个`dp[i][j]`，考虑当前位置`i`是否作为一个新区间的结尾，从而得到状态转移方程。
2. **算法要点**：通过前缀和数组`sum`快速计算长度为`m`的区间和。状态转移方程一般为`dp[i][j] = max(dp[i - 1][j], dp[i - m][j - 1] + sum[i] - sum[i - m])`，其中`dp[i - 1][j]`表示不选以`i`结尾的新区间，`dp[i - m][j - 1] + sum[i] - sum[i - m]`表示选以`i`结尾的新区间。
3. **解决难点**：如何准确地定义状态和状态转移方程，以及理解每个状态转移的含义。部分题解还涉及到优化，如使用单调队列将时间复杂度从$O(n^3)$降到$O(n^2)$，或使用滚动数组优化空间。

### 所选的题解
1. **作者：_JF_ (赞：7)  星级：4星**
    - **关键亮点**：思路清晰，直接定义`dp[i][j]`表示前`i`个数选`j`组的最大值，状态转移方程明确，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5010;
#define int long long
int dp[N][N],a[N],sum[N];
signed main()
{
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    dp[1][1]=sum[1];
    for(int i=m;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
            dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+sum[i]-sum[i-m]);
    }
    cout<<dp[n][k]<<endl;
}
```
    - **核心实现思想**：先通过循环读入数据并计算前缀和。然后通过两层循环，外层枚举前`i`个数，内层枚举选`j`组，根据状态转移方程更新`dp[i][j]`的值，最后输出`dp[n][k]`。
2. **作者：VenusM1nT (赞：8)  星级：4星**
    - **关键亮点**：详细解释了DP的思路和前缀和的使用，对状态转移方程的推导有清晰说明，代码注释丰富。
    - **个人心得**：提到对DP感到有难度，强调前缀和思想对DP的帮助。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,m,k,a[5005],s[5005],f[5005][5005];
int main()
{
    scanf("%lld %lld %lld",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    long long tot=0;
    for(int i=1;i<=n;i++)
    {
        tot+=a[i];
        if(i>=m)
        {
            s[i]=tot;
            tot-=a[i-m+1];
        }
    }
    memset(f,-1,sizeof(f));
    for(int i=0;i<=n;i++) f[i][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            f[i][j]=f[i-1][j];
            if(i>=m && f[i-m][j-1]>-1) f[i][j]=max(f[i][j],f[i-m][j-1]+s[i]);
        }
    }
    printf("%lld",f[n][k]);
    return 0;
}
```
    - **核心实现思想**：先读入数据，通过一个循环计算前缀和`s`数组。初始化`f`数组并设置边界条件。通过两层循环，根据状态转移方程更新`f[i][j]`，最后输出`f[n][k]`。
3. **作者：Supor__Shoep (赞：2)  星级：4星**
    - **关键亮点**：对状态定义和状态转移方程的解释详细，清晰阐述了每个部分的含义，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5005;
int n,m,k;
long long dp[MAXN][MAXN];
long long a[MAXN],sum[MAXN];
signed main()
{
    cin>>n>>m>>k;
    for(register int i=1;i<=n;i++)	cin>>a[i];
    for(register int i=1;i<=n;i++)	sum[i]=sum[i-1]+a[i];
    for(register int i=m;i<=n;i++)
    {
        for(register int j=1;j<=k;j++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+sum[i]-sum[i-m]);
        }
    }
    cout<<dp[n][k];
    return 0;
}
```
    - **核心实现思想**：读入数据并计算前缀和。通过两层循环，依据状态转移方程更新`dp[i][j]`，最终输出`dp[n][k]`。

### 最优关键思路或技巧
1. **状态定义与转移**：准确地定义二维DP数组表示前`i`个数选`j`个区间的最大值，并根据是否选择当前区间得到简洁有效的状态转移方程。
2. **前缀和优化**：利用前缀和数组快速计算长度为`m`的区间和，将区间和的计算复杂度从$O(m)$降到$O(1)$。

### 可拓展之处
此类题目属于线性DP结合区间选择的类型，类似套路可用于解决子序列选择求和、子数组划分等问题。通常可以通过合理定义状态和状态转移方程，结合前缀和、单调队列等优化手段来解决。

### 相似知识点洛谷题目
1. [P1474 货币系统](https://www.luogu.com.cn/problem/P1474)：涉及背包类DP，与本题类似，需定义合适状态和转移方程。
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的01背包问题，与本题在DP思路上有相似之处。
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)：需要通过排序后利用DP解决最长上升子序列相关问题，和本题的DP思维有共通点。 

---
处理用时：41.12秒