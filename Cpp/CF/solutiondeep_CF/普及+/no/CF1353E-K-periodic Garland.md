# 题目信息

# K-periodic Garland

## 题目描述

You are given a garland consisting of $ n $ lamps. States of the lamps are represented by the string $ s $ of length $ n $ . The $ i $ -th character of the string $ s_i $ equals '0' if the $ i $ -th lamp is turned off or '1' if the $ i $ -th lamp is turned on. You are also given a positive integer $ k $ .

In one move, you can choose one lamp and change its state (i.e. turn it on if it is turned off and vice versa).

The garland is called $ k $ -periodic if the distance between each pair of adjacent turned on lamps is exactly $ k $ . Consider the case $ k=3 $ . Then garlands "00010010", "1001001", "00010" and "0" are good but garlands "00101001", "1000001" and "01001100" are not. Note that the garland is not cyclic, i.e. the first turned on lamp is not going after the last turned on lamp and vice versa.

Your task is to find the minimum number of moves you need to make to obtain $ k $ -periodic garland from the given one.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
9 2
010001010
9 3
111100000
7 4
1111111
10 3
1001110101
1 1
1
1 1
0```

### 输出

```
1
2
5
4
0
0```

# AI分析结果

### 题目翻译
## K 周期花环

### 题目描述
你有一个由 $n$ 个灯组成的花环。灯的状态由长度为 $n$ 的字符串 $s$ 表示。如果第 $i$ 个字符 $s_i$ 等于 '0'，则表示第 $i$ 个灯是关闭的；如果等于 '1'，则表示第 $i$ 个灯是打开的。同时，你还会得到一个正整数 $k$。

在一次操作中，你可以选择一个灯并改变它的状态（即如果它是关闭的就打开它，如果它是打开的就关闭它）。

如果每对相邻的打开的灯之间的距离恰好为 $k$，则称这个花环是 $k$ 周期的。考虑 $k = 3$ 的情况。那么花环 "00010010"、"1001001"、"00010" 和 "0" 是符合要求的，但花环 "00101001"、"1000001" 和 "01001100" 不符合要求。注意，花环不是循环的，即第一个打开的灯不会在最后一个打开的灯之后，反之亦然。

你的任务是找出将给定的花环变成 $k$ 周期花环所需的最少操作次数。

你需要回答 $t$ 个独立的测试用例。

### 样例 #1
#### 输入
```
6
9 2
010001010
9 3
111100000
7 4
1111111
10 3
1001110101
1 1
1
1 1
0
```
#### 输出
```
1
2
5
4
0
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕动态规划的思想来解决问题，部分题解结合了前缀和优化。不同题解在状态定义和转移方程的表达上略有差异，但核心都是通过动态规划来计算最少操作次数。
- **思路对比**：多数题解通过定义不同的动态规划状态来表示不同的情况，如到第 $i$ 位为 $1$ 且前面状态不同时的最少操作次数。部分题解还结合了贪心思想，如先将所有 $1$ 变成 $0$ 再考虑恢复某些 $1$ 来优化结果。
- **算法要点**：普遍使用前缀和来快速计算区间内 $1$ 的数量，从而优化状态转移的计算。
- **解决难点**：处理好状态的定义和转移，考虑到所有可能的情况，如第一个 $1$ 的位置、最后一个 $1$ 后面的 $1$ 要全部变成 $0$ 等。

### 高评分题解
- **作者：H6_6Q (4星)**
    - **关键亮点**：思路清晰，对动态规划状态的定义和转移方程的推导解释详细，代码注释丰富，易于理解。
    - **个人心得**：提到直接使用 `memset` 会超时，必须手动清空数组，这是一个需要注意的坑点。
- **作者：RemiliaScar1et (4星)**
    - **关键亮点**：通过状态机的方式直观地展示状态转移，对状态转移方程的推导和解释详细，代码实现简洁明了。
- **作者：harmis_yz (4星)**
    - **关键亮点**：状态定义和转移方程的推导逻辑清晰，代码中封装了一些常用函数，结构清晰。

### 重点代码
#### H6_6Q 的代码核心片段
```cpp
const int N=1e6+5,inf=0x7f7f7f7f;
int t,n,k,dp[N][2],sum[N],ans;
char s[N]; 

int main()
{
    memset(dp,0x7f,sizeof(dp));
    t=read();
    while(t--)
    {
        n=read();k=read();
        scanf("%s",s+1);
        for(int i=1;i<=n;++i)
            sum[i]=sum[i-1]+(s[i]-'0');
        ans=sum[n];
        for(int i=1;i<=n;++i)
        {
            dp[i][0]=sum[i-1];
            if(i-k>=1)
                dp[i][1]=min(dp[i-k][1]+sum[i-1]-sum[i-k],dp[i-k][0]+sum[i-1]-sum[i-k]);
            if(s[i]=='0')
            {
                if(dp[i][0]!=inf)
                    dp[i][0]++;
                if(dp[i][1]!=inf)
                    dp[i][1]++;
            }
        }
        int num=0;
        for(int i=n;i>=1;--i)
        {
            ans=min(ans,min(dp[i][1]+num,dp[i][0]+num));
            if(s[i]=='1')
                num++;
        }
        for(int i=1;i<=n;++i)
        {
            sum[i]=0;
            dp[i][0]=inf;
            dp[i][1]=inf;
        } 
        printf("%d\n",ans);
    }
    return 0;
} 
```
**核心实现思想**：通过前缀和数组 `sum` 统计前 $i$ 个字符中 $1$ 的数量，定义 `dp[i][0]` 表示到第 $i$ 个字符为止，只让第 $i$ 位为 $1$，其余 $i - 1$ 位均为 $0$ 时需要的操作次数；`dp[i][1]` 表示到第 $i$ 个字符为止，让第 $i$ 位为 $1$，且保证在这之前合法所需要的最少操作次数。最后从后往前遍历，统计答案。

#### RemiliaScar1et 的代码核心片段
```cpp
const int N=4e6+10;
int f[N],g[N],sum[N];
char str[N];

int main()
{
    int t; cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k>>(str+1);
        for(int i=0;i<=n;i++) f[i]=0x3f3f3f3f,sum[i]=0;
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+(str[i]-'0'), g[i]=sum[i-1]+int(str[i]=='0');
        for(int i=1;i<=n;i++)
            if(i>k) f[i]=min(f[i-k],g[i-k])+sum[i-1]-sum[i-k]+int(str[i]=='0');
        int ans=sum[n];
        for(int i=1;i<=n;i++)
            ans=min(ans,min(f[i],g[i])+sum[n]-sum[i]);
        cout<<ans<<'\n';
    }
    return 0;
}
```
**核心实现思想**：通过前缀和数组 `sum` 统计前 $i$ 个字符中 $1$ 的数量，定义 $g(i)$ 表示把前 $i - 1$ 位设为 $0$，第 $i$ 位设成 $1$ 的代价，$f(i)$ 表示到第 $i$ 位为 $1$ 时，前面均合法且至少有一个 $1$ 的最小代价。最后枚举构造序列长度 $i$，统计答案。

#### harmis_yz 的代码核心片段
```cpp
const int N=1e6+10;
int n,k;
int f[N],s[N];
char c[N];

il int w(int l,int r){
    if(l>r) return 0;
    return s[r]-s[l-1];
}

il void solve(){
    n=rd,k=rd,scanf("%s",c+1);
    for(re int i=1;i<=n;++i) s[i]=s[i-1]+c[i]-'0';
    int ans=1e9+7;
    for(re int i=1;i<=n;++i)
        f[i]=min(f[max(0*1ll,i-k)]+w(max(0*1ll,i-k)+1,i-1),f[0]+w(1,i-1))+(c[i]!='1');
    for(re int i=0;i<=n;++i)
        ans=min(ans,f[i]+w(i+1,n));
    printf("%lld\n",ans);
    return ;
}

signed main(){
    int t=rd;while(t--)
        solve();
    return 0;
}
```
**核心实现思想**：通过前缀和数组 `s` 统计前 $i$ 个字符中 $1$ 的数量，定义 $f(i)$ 表示处理完前 $i$ 个字符且第 $i$ 个字符为 $1$ 时的最小代价。最后枚举最后一个 $1$ 的位置，统计答案。

### 关键思路与技巧
- **动态规划状态定义**：通过合理定义状态来表示不同的情况，如到第 $i$ 位为 $1$ 且前面状态不同时的最少操作次数。
- **前缀和优化**：使用前缀和数组快速计算区间内 $1$ 的数量，减少时间复杂度。

### 拓展思路
同类型题可以考虑一些变形，如花环变成循环的情况，或者灯的状态有更多种，操作也更复杂等。类似算法套路可以应用在其他需要状态转移和优化计算的动态规划问题中。

### 推荐洛谷题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划的基本思想。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的线性动态规划问题，通过状态转移求解最大路径和。
- [P1802 5 倍经验日](https://www.luogu.com.cn/problem/P1802)：类似于 0 - 1 背包问题的动态规划问题，需要考虑不同选择的代价和收益。

---
处理用时：67.12秒