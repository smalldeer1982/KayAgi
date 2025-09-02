# 题目信息

# Strip

## 题目描述

Alexandra has a paper strip with $ n $ numbers on it. Let's call them $ a_{i} $ from left to right.

Now Alexandra wants to split it into some pieces (possibly $ 1 $ ). For each piece of strip, it must satisfy:

- Each piece should contain at least $ l $ numbers.
- The difference between the maximal and the minimal number on the piece should be at most $ s $ .

Please help Alexandra to find the minimal number of pieces meeting the condition above.

## 说明/提示

For the first sample, we can split the strip into $3$ pieces: $[1,3,1], [2,4], [1,2]$.

For the second sample, we can't let $1$ and $100$ be on the same piece, so no solution exists.

## 样例 #1

### 输入

```
7 2 2
1 3 1 2 4 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7 2 2
1 100 1 100 1 100 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 纸条分段

## 题目描述
亚历山德拉有一张写有$n$个数字的纸条。我们从左到右将它们称为$a_{i}$ 。
现在亚历山德拉想把它分成若干段（可能是$1$段）。对于纸条的每一段，必须满足：
- 每段应至少包含$l$个数字。
- 该段上最大数与最小数的差值应至多为$s$。
请帮助亚历山德拉找到满足上述条件的最少段数。

## 说明/提示
对于第一个样例，我们可以将纸条分成$3$段：$[1,3,1], [2,4], [1,2]$ 。
对于第二个样例，我们不能让$1$和$100$在同一段，所以无解。

## 样例 #1
### 输入
```
7 2 2
1 3 1 2 4 1 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
7 2 2
1 100 1 100 1 100 1
```
### 输出
```
-1
```

### 算法分类
动态规划

### 题解综合分析与结论
这些题解均围绕动态规划展开，核心是定义状态 `dp[i]` 表示序列前 `i` 个数字的最少分段数，状态转移方程为 `dp[i] = min{dp[j] + 1} (j ∈ [1, i - l], max{a[k] (k ∈ [j, i])} - min{a[k] (k ∈ [j, i])} ≤ s)`。主要难点在于优化极差计算和状态转移的时间复杂度。各题解通过不同方式进行优化，如利用单调队列、ST表、线段树等数据结构。

### 所选的题解
- **作者：critnos (5星)**
    - **关键亮点**：思路清晰，利用单调队列优化，时间复杂度为 $\Theta(n)$。通过反证得出满足极差条件的 $w$ 随 $i$ 不减，进而用单调队列维护 $a$ 区间的最值和 $dp$ 的取值区间。
    - **重点代码 - 核心实现思想**：用两个单调队列 `mn`、`mx` 维护区间 $[w, i]$ 的最大值和最小值，用 `dpmn` 维护 $dp$ 的取值区间。
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100005];
int a[100005];
deque<int> dpmn,mn,mx;
int main()
{
    memset(dp,127,sizeof(dp));
    int n,l,s,p,i,j,w;
    scanf("%d%d%d",&n,&s,&l);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    w=1;
    dp[0]=0;
    for(i=1;i<l;i++)
    {
        while(mn.size()&&a[mn.back()]>=a[i])
            mn.pop_back();
        mn.push_back(i);
        while(mx.size()&&a[mx.back()]<=a[i])
            mx.pop_back();
        mx.push_back(i);
    }
    for(i=l;i<=n;i++)
    {
        while(mn.size()&&a[mn.back()]>=a[i])
            mn.pop_back();
        mn.push_back(i);
        while(mx.size()&&a[mx.back()]<=a[i])
            mx.pop_back();
        mx.push_back(i);
        for(;w<=i;w++)
        {
            while(mn.front()<w) mn.pop_front();
            while(mx.front()<w) mx.pop_front();
            if(a[mx.front()]-a[mn.front()]<=s) break;
        }
        while(dpmn.size()&&dp[dpmn.back()]>=dp[i-l]) dpmn.pop_back();
        dpmn.push_back(i-l);
        while(dpmn.size()&&dpmn.front()<w-1) dpmn.pop_front();
        if(w<=i-l+1&&dpmn.size())
            dp[i]=dp[dpmn.front()]+1;
    }
    cout<<(dp[n]>1e9?-1:dp[n]);
}
```
- **作者：Honor誉 (4星)**
    - **关键亮点**：采用RMQ（用ST表实现）求区间最值，再结合简单DP。代码简洁，逻辑明确。
    - **重点代码 - 核心实现思想**：先通过ST表预处理出区间最值，然后在DP过程中利用 `ask` 函数查询区间极差来更新 `dp` 值。
```cpp
#include<bits/stdc++.h>
#define inf 2147483647
#define N 100010
using namespace std;
int maxn[N][22],minn[N][22],n,s,ll,dp[N],cnt;
int ask(int l,int r)//求差的最大值
{
    int ans=0;
    while((1<<(ans+1))<=r-l+1)
    {
        ans++;
    }
    return max(maxn[l][ans],maxn[r-(1<<ans)+1][ans])-min(minn[l][ans],minn[r-(1<<ans)+1][ans]);
}
int read()
{
    int sum=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*f;
}
int main()
{
    n=read();
    s=read();
    ll=read();
    for(int i=1;i<=n;i++)
    {
        maxn[i][0]=minn[i][0]=read();
    }
    for(int i=1;(1<<i)<=n;i++)
    {
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            minn[j][i]=min(minn[j][i-1],minn[j+(1<<(i-1))][i-1]);
            maxn[j][i]=max(maxn[j][i-1],maxn[j+(1<<(i-1))][i-1]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[i]=inf;
    }
    for(int i=ll;i<=n;i++)//DP
    {
        while(i-cnt>=ll&&(ask(cnt+1,i)>s||dp[cnt]==inf))
        {
            cnt++;
        }
        if(i-cnt>=ll)
        {
            dp[i]=min(dp[i],dp[cnt]+1);
        }
    }
    if(dp[n]==inf)
    {
        puts("-1");
    }else{
        printf("%d\n",dp[n]);
    }
    return 0;
}
```
- **作者：rainygame (4星)**
    - **关键亮点**：对DP优化讲解详细，通过维护决策点和单调队列优化极差计算，将时间复杂度从 $\mathcal{O}(n^3)$ 优化到 $\Theta(n)$。
    - **重点代码 - 核心实现思想**：用 `minn` 和 `maxn` 两个单调队列维护区间最值，通过 `query` 函数查询极差，在DP过程中维护决策点 `c` 来更新 `dp` 值。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define INF 0x3f3f3f3f

int n, k, s, c;
int dp[MAXN], b[MAXN];
deque<int> minn, maxn;

inline int query(){  // 查询极差
    while (!minn.empty() && minn.front() < c+1) minn.pop_front();
    while (!maxn.empty() && maxn.front() < c+1) maxn.pop_front();
    return b[maxn.front()] - b[minn.front()];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    memset(dp, 0x3f, sizeof(dp));
    cin >> n >> s >> k;
    for (int i=1; i<=n; i++) cin >> b[i];
    dp[0] = 0;  // 边界条件
    
    for (int i=1; i<=n; i++){
        while (!minn.empty() && b[minn.back()] >= b[i]) minn.pop_back();  // 维护单调性
        minn.push_back(i);
        while (!maxn.empty() && b[maxn.back()] <= b[i]) maxn.pop_back();
        maxn.push_back(i);
        if (i >= k){
            while ((i-c >= k) && (query() > s || dp[c] == INF)) c++;  // 维护决策点
            if (i-c >= k) dp[i] = dp[c]+1;  // 转移
        }
    }
    
    cout << (dp[n] == INF? -1 : dp[n]);  // 注意转移不到的问题
    
    return 0;
}
```

### 最优关键思路或技巧
- **单调性利用**：利用极差随区间端点移动的单调性，减少无效状态转移，如通过维护单调队列来优化极差计算和状态转移区间。
- **数据结构辅助**：使用ST表或单调队列等数据结构优化区间最值查询和状态转移，从而降低时间复杂度。

### 可拓展之处
此类题目属于序列分段的动态规划问题，常见拓展方向是改变分段条件，如对段内数字和、乘积等设置条件，解题思路依然是通过合理定义状态和转移方程，并利用数据结构优化计算。

### 相似知识点洛谷题目
- **P1880 [NOI1995] 石子合并**：经典的区间DP问题，涉及到将多个石子堆合并，通过动态规划求解最小或最大合并代价，与本题类似之处在于都需要合理定义状态和状态转移方程。
- **P1091 [NOIP2004 提高组] 合唱队形**：通过两次动态规划，分别求出从左到右和从右到左的最长上升子序列，进而得出满足条件的最少出列人数，与本题一样考察对动态规划的应用和状态转移的设计。
- **P3951 [NOIP2017 提高组] 小凯的疑惑**：虽然表面是数论问题，但也可通过动态规划思想求解，与本题类似在于都是通过状态转移来解决问题，只不过本题是序列分段类型的动态规划。 

---
处理用时：101.18秒