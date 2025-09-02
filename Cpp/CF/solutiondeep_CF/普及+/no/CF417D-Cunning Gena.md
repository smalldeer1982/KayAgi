# 题目信息

# Cunning Gena

## 题目描述

Gena非常想参加“俄罗斯code cup”的决赛，或是至少得到一件T恤。 但是比赛的题目太复杂了，所以他安排他的n个朋友帮他解决这些问题。

在比赛中会有m道题目提供给参赛者。对于每个朋友，Gena知道他能解决什么问题。 但是Gena的朋友不会无偿的去帮助Gena的， 第i个朋友会因为帮助Gena解决所有他会的问题而向Gena索要x卢布。 并且，只有在Gena的电脑连接到至少k台显示器时，这个朋友才会去帮助Gena写代码。 且每台显示器需要花费b卢布。

Gena很节约用钱，所以他希望尽可能少的花钱去解决所有问题。 请你帮助Gena，告诉他怎样花费最少的钱。 最初，Gena的电脑没有连接任何显示器。

## 样例 #1

### 输入

```
2 2 1
100 1 1
2
100 2 1
1
```

### 输出

```
202
```

## 样例 #2

### 输入

```
3 2 5
100 1 1
1
100 1 1
2
200 1 2
1 2
```

### 输出

```
205
```

## 样例 #3

### 输入

```
1 2 1
1 1 1
1
```

### 输出

```
-1
```

# AI分析结果

### 题目重写
# 狡猾的吉娜

## 题目描述
吉娜非常渴望参加“俄罗斯代码杯”的决赛，或者至少能得到一件T恤。然而，比赛的题目实在是太复杂了，于是她安排了n个朋友来帮她解决这些问题。

在比赛中，会提供给参赛者m道题目。对于每一个朋友，吉娜都清楚他们能够解决哪些问题。但是，吉娜的朋友们并不会无偿地帮助她，第i个朋友会因为帮助吉娜解决他们所能解决的所有问题而向吉娜索要x卢布。并且，只有当吉娜的电脑连接到至少k台显示器时，这个朋友才会帮吉娜写代码。每台显示器的花费是b卢布。

吉娜很节俭，希望尽可能少地花钱来解决所有问题。请你帮助吉娜，告诉她最少需要花费多少钱。最初，吉娜的电脑没有连接任何显示器。

## 样例 #1
### 输入
```
2 2 1
100 1 1
2
100 2 1
1
```
### 输出
```
202
```

## 样例 #2
### 输入
```
3 2 5
100 1 1
1
100 1 1
2
200 1 2
1 2
```
### 输出
```
205
```

## 样例 #3
### 输入
```
1 2 1
1 1 1
1
```
### 输出
```
-1
```

### 算法分类
动态规划

### 综合分析与结论
这些题解都基于状态压缩动态规划来解决问题，核心思路是通过二进制表示题目解决状态，利用dp数组记录不同状态下的最小花费。主要难点在于如何处理显示器数量对花费的影响。多数题解通过将朋友按所需显示器数量排序，使得在计算总花费时能简单地取最后一个朋友所需显示器数量乘以单价，避免了复杂的枚举。在状态转移方面，基本采用从前一个状态推出当前状态的方式，以降低复杂度。不同题解在状态定义、空间优化及代码实现细节上略有差异。

### 所选的题解
- **作者：lenlen (赞：15)  5星**
    - **关键亮点**：状态设计清晰，详细解释了按显示器所需数量排序的原因，考虑到空间优化使用滚动数组，对初始最大值的设置有特别说明。
    - **个人心得**：提到初始将 `inf` 设为 `10^{18}` 发现答案有更大值，需开大。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=732,inf=2e18+7;
long long f[2][1<<21];
int n,m,x,y;
long long ans=inf,b;
struct hl{
    int a;
    long long w,k;
}t[N];
bool cmp(hl x,hl y)
{
    return x.k<y.k;
}
long long mi(long long x,long long y)
{
    return x>y?y:x;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld%d",&t[i].w,&t[i].k,&x);
        while(x--) scanf("%d",&y),t[i].a|=(1<<y-1);
    }
    sort(t+1,t+n+1,cmp);
    for(int i=1;i<(1<<m);i++) f[0][i]=inf; 
    for(int j=0;j<n;j++)
    {
        for(int i=0;i<(1<<m);i++) f[j+1&1][i]=inf;
        for(int i=0;i<(1<<m);i++)
        {
            if(f[j&1][i]==inf) continue;
            f[j+1&1][i|t[j+1].a]=mi(f[j+1&1][i|t[j+1].a],f[j&1][i]+t[j+1].w);
            f[j+1&1][i]=mi(f[j+1&1][i],f[j&1][i]);
        }
        ans=mi(ans,f[j+1&1][(1<<m)-1]+t[j+1].k*b);
    }
    printf("%lld\n",ans!=inf?ans:-1);
}
```
核心实现思想：定义 `f[i][j]` 表示前 `i` 个人完成了 `j` 状态的题目的最小价值，通过滚动数组优化空间。在循环中，根据是否选择第 `i` 个人进行状态转移，最后得出完成所有题目（`(1<<m)-1` 状态）的最小花费。

- **作者：aRenBigFather (赞：6)  4星**
    - **关键亮点**：状态定义简洁，明确阐述了状态转移方程，对转移思路的取舍有清晰解释，考虑到数据范围大坑，使用 `unsigned long long` 避免溢出。
    - **个人心得**：提到因数据范围问题，`INF` 开到 `1e18` 不够，需开成 `1e19` 且要用 `unsigned long long`，WA多次。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;
const ll inf = 1e19;
const int maxn = 110;
ll n,m,b;
struct Frd{
    ll x,k,prob;
}Frds[maxn];
ll dp[(1 << 20)+10];
inline bool cmp(const Frd &_a,const Frd &_b) { return _a.k < _b.k; }
int main(){
    scanf("%lld%lld%lld",&n,&m,&b);
    for(int i=0;i<maxn;i++) Frds[i].prob = 0;
    for(int i=1;i<=n;i++){
        int mm;
        scanf("%lld%lld%d",&Frds[i].x,&Frds[i].k,&mm);
        for(int j=0;j<mm;j++){
            int pid;
            scanf("%d",&pid);
            Frds[i].prob |= (1 << (pid-1));
        }
    }
    sort(Frds+1,Frds+1+n,cmp);
    for(int i=0;i<1048586;i++) dp[i] = inf;
    dp[0] = 0;
    ll dpans = inf;
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<m);j++){
            if(dp[j] == inf) continue;
            dp[j | Frds[i].prob] = min(1ll * dp[j | Frds[i].prob],dp[j] + Frds[i].x);
        }
        if(dp[(1<<m)-1]!= inf) dpans = min(1ll*dpans,dp[(1 << m) - 1] + Frds[i].k * b); 
    }
    ll ans;
    if(dpans == inf) ans = -1;
    else ans = dpans;
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：定义 `dp[sta]` 表示做题状态为 `sta` 状态下不加显示器的花费，通过循环和状态转移方程更新 `dp` 数组，最后得出完成所有题目（`(1<<m)-1` 状态）加上显示器花费的最小总花费。

- **作者：jasonliujiahua (赞：1)  4星**
    - **关键亮点**：对状态转移方程的推导过程详细，对滚动数组优化空间及循环顺序有深入分析，与背包问题做对比加深理解。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=101;
const int inf=2e18;
int n,m,mm,b,ans=inf,dp[1<<21];
struct node
{
    int x,k,num,t;
}a[maxn];
bool cmp(node x,node y)
{
    return x.k<y.k;
}
void init()
{
    cin>>n>>m>>b;
    mm=((1<<m)-1)<<1;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].k>>a[i].num;
        for(int j=1;j<=a[i].num;j++)
        {
            int x;
            cin>>x;
            a[i].t|=(1<<x);
        }
    }
    a[0].k=0;
}
void DP()
{
    sort(a+1,a+n+1,cmp);
    for(int s=0;s<=mm;s++)
        dp[s]=inf;
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int s=0;s<=mm;s++)
        {
            dp[s|a[i].t]=min(dp[s|a[i].t],dp[s]+a[i].x);
        }
        ans=min(ans,dp[mm]+a[i].k*b);
    }
    if(ans>=inf) ans=-1;
    cout<<ans<<endl;
}
signed main()
{
    init();
    DP();
    return 0;
}
```
核心实现思想：定义 `dp` 数组表示选前 `i` 个朋友帮忙解决状态为 `s` 的题目所需除显示器外的代价，通过滚动数组优化空间，利用状态转移方程更新 `dp` 数组，最后得出完成所有题目（`mm` 对应的状态）加上显示器花费的最小总花费。

### 最优关键思路或技巧
- **状态压缩**：利用二进制表示题目解决状态，将复杂的题目选择情况简化为二进制位的操作，方便状态的表示与转移。
- **按显示器需求排序**：将朋友按所需显示器数量排序，使得在计算总花费时，可简单地以最后一个朋友所需显示器数量计算显示器花费，避免了对显示器数量复杂的枚举与状态维护。
- **滚动数组优化**：由于状态转移只与上一个状态有关，使用滚动数组可将空间复杂度从 $O(n\times2^m)$ 降低到 $O(2^m)$，避免空间溢出。

### 同类型题或类似算法套路
此类题目通常具有有限状态且状态间存在依赖关系，可考虑状态压缩动态规划。常见套路为用二进制表示状态，根据问题特点设计状态转移方程。在处理有附加条件（如本题显示器数量限制）时，可通过排序等方式简化条件处理。

### 洛谷推荐题目
- [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)：同样是状态压缩动态规划，处理在棋盘上放置棋子满足特定条件的问题，需考虑状态表示及转移。
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)：涉及状态压缩和空间优化，在棋盘上放置炮兵满足射击范围限制，与本题在状态处理和优化上思路类似。
- [P1171 售货员的难题](https://www.luogu.com.cn/problem/P1171)：状态压缩动态规划解决旅行商问题的简化版，重点在于状态表示与转移方程的设计，与本题算法思想契合。

### 个人心得摘录与总结
多位作者提到数据范围的坑，初始设置的最大值过小导致WA，需将 `INF` 设得足够大，如 `2e18 + 7` 或 `1e19` 甚至更大，并且要注意数据类型选择（如 `unsigned long long`）以防止溢出。这提醒在处理大数据范围题目时，对边界值和数据类型需谨慎考虑。 

---
处理用时：110.89秒