# [GCJ 2012 #1C] Box Factory

## 题目描述

你拥有一家拥有两条装配线的工厂。第一条装配线生产盒子，第二条装配线生产可以放入这些盒子的玩具。每种类型的盒子只对应一种类型的玩具，反之亦然。

一开始，你会从第一条装配线上取一个盒子，从第二条装配线上取一个玩具。此时你有如下几种选择：

* 你可以随时丢弃盒子，取下一个盒子。
* 你可以随时丢弃玩具，取下一个玩具。
* 如果盒子和玩具是同一种类型，你可以将玩具放入盒子，并将其发给客户。

你总是按照生产顺序依次取盒子和玩具。你已知盒子和玩具的生产顺序，并希望制定一种策略，使得你发出的装盒玩具数量尽可能多。

**注意**：两条装配线会生产大量盒子和玩具，但它们通常会长时间连续生产同一种类型后才切换。

## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- $1 \leq a_i, b_i \leq 10^{16}$
- $1 \leq A_i, B_i \leq 100$

**测试集 1（12 分，结果可见）**

- $1 \leq N \leq 3$
- $1 \leq M \leq 100$

**测试集 2（23 分，结果隐藏）**

- $1 \leq N, M \leq 100$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
3 3
10 1 20 2 25 3
10 2 30 3 20 1
3 5
10 1 6 2 10 1
5 1 3 2 10 1 3 2 5 1
3 5
10 1 6 2 10 1
5 1 6 2 10 1 6 2 5 1
1 1
5000000 10
5000000 100```

### 输出

```
Case #1: 35
Case #2: 20
Case #3: 21
Case #4: 0```

# 题解

## 作者：shenliyan (赞：3)

这道题本质是要找盒子和玩具能配成的最多对数，核心是用动态规划（DP）来记录中间状态。

首先得想清楚怎么定义状态。先用 $dp[i][j]$ 表示：处理完前 $i$ 段盒子和前 $j$ 段玩具后，能配出的最大对数。这样定义的话，我们只需要一步步计算到 $dp[n][m]$（所有盒子和玩具都处理完），就是答案了。

接下来是状态怎么转移。对于每一段盒子 $i$ 和玩具 $j$，有两种基本选择：
1. 不用当前的盒子段 $i$：那结果就和 $dp[i-1][j]$（前 $i-1$ 段盒子和前 $j$ 段玩具的结果）一样；
2. 不用当前的玩具段 $j$：那结果就和 $dp[i][j-1]$（前 $i$ 段盒子和前 $j-1$ 段玩具的结果）一样。
所以先取这两种情况的最大值，作为 $dp[i][j]$ 的初始值。

但还有一种更优的可能：如果当前盒子段 $i$ 和玩具段 $j$ 类型相同，那它们说不定能匹配。不过这里有个关键点——不能只看这两段，因为前面可能还有同类型的盒子或玩具段，累积起来匹配会更多。比如盒子前两段都是类型 $A$，玩具前三段都是类型 $A$，那把这些都算上再匹配，肯定比只算当前段更合理。

所以当 $A[i] == B[j]$（当前盒子和玩具类型相同）时，我们要回溯找所有同类型的段：\
首先，从盒子段 $i$ 往前数，把所有类型和 $A[i]$ 相同的盒子数量累加（记为 $ci$）。\
然后从玩具段 $j$ 往前数，把所有类型和 $B[j]$ 相同的玩具数量累加（记为 $cj$）。\
 这部分能匹配的对数是 $min(ci, cj)$，再加上之前的状态 $dp[k-1][l-1]$（$k$ 是盒子回溯的起点，$l$ 是玩具回溯的起点），就能更新 $dp[i][j]$ 了。

举个例子：如果盒子前 $3$ 段都是类型 $1$（数量分别是 $2$、$3$、$1$），玩具前 $2$ 段都是类型 $1$（数量分别是 $4$、$2$），那累积的盒子数量是 $6$，玩具是 $6$，能配 $6$ 对，这比单独算某一段更优。


**复杂度分析**

时间上，外层有两层循环（遍历所有 $i$ 和 $j$），内层在类型相同时又嵌套了两层回溯循环（找同类型的段），所以时间复杂度是 $O(N²M²)$（$N$ 是盒子段数，$M$ 是玩具段数）。题目给了3秒时限，这个复杂度是能过的。

空间上，主要是 $dp$ 数组，大小是 $(N+1)×(M+1)$，所以是 $O(NM)$。


**代码实现**
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
int main(){
    int T;
    cin>>T;
    for(int t=1;t<=T;t++){
        int n,m;
        cin>>n>>m;
        vector<ll>a(n+1);
        vector<int>A(n+1);
        vector<ll>b(m+1);
        vector<int>B(m+1);
        for(int i=1;i<=n;i++){
            cin>>a[i]>>A[i];
        }
        for(int i=1;i<=m;i++){
            cin>>b[i]>>B[i];
        }
        vector<vector<ll>>dp(n+1,vector<ll>(m+1,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                if(A[i]==B[j]){
                    ll ci=0;
                    for(int k=i;k>=1;k--){
                        if(A[k]==A[i]){
                            ci+=a[k];
                            ll cj=0;
                            for(int l=j;l>=1;l--){
                                if(B[l]==A[i]){
                                    cj+=b[l];
                                    dp[i][j]=max(dp[i][j],dp[k-1][l-1]+min(ci,cj));
                                }
                            }
                        }
                    }
                }
            }
        }
        cout<<"Case #"<<t<<": "<<dp[n][m]<<endl;
    }
    return 0;
}
```

---

## 作者：wurang (赞：1)

注意到数据范围 $1 \le a_i,b_i \le 10^{16}$，想到可以用动态规划解决。

首先考虑前两种情况，即扔掉盒子或玩具，设 $dp_{i,j}$ 表示考虑前 $i$ 段连续的盒子，$j$ 段连续的玩具，容易得到转移方程：

$$
dp_{i,j} = \max(dp_{i,j-1}, dp_{i-1, j})
$$

其次考虑产生贡献的情况，若 $A_i = B_j$ 时显然有一下转移：

$$
dp_{i,j} = dp_{i-1,j-1} + \min(a_i, b_j)
$$

但此时考虑这样一组样例：
  
```
1
2 2
2 3 6 1
3 1 2 1
```

显然我们应该扔掉第一段类型为 $3$ 的盒子，答案为 $6$。

所以我们需要将与 $A_i$ 相同类型的盒子数量累加，与 $B_j$ 相同类型的玩具数量累加。设第 $k$ 到 $i$ 段盒子中有 $sum_{k,i}$ 个类型为 $A_i$ 的盒子，第 $t$ 到 $i$ 段盒子中有 $cnt_{t,j}$ 个类型为 $B_j$ 的玩具，有转移方程：

$$
dp_{i,j} = \max(dp_{i,j}, \min(sum_{k,i}, cnt_{t,j}) + dp_{k-1, t-1})
$$

枚举 $k$ 和 $t$ 即可。

答案即为 $dp_{n,m}$。

时间复杂度为 $O(TN^2M^2)$，然而这个时间根本跑不满，似乎能过。

但此时只计算类型相同的盒子（玩具），可以提前预处理出第 $i$ 个类型为 $j$ 的盒子（玩具），优化复杂度。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}

struct node{int pos, sum;} ; // 位置/前缀和
vector <node> x[205], y[205]; // 不同种类提前预处理

int T, n, m;
int a[205], b[205], A[205], B[205];
int dp[205][205], posa[205], posb[205]; // dp/第i个盒子对应的下标/第i个玩具对应的下标

signed main()
{
    T = read();
    for(int hcx = 1; hcx <= T; hcx++)
    {
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < 205; i++)
            x[i].clear(), y[i].clear(), x[i].push_back({0, 0}), y[i].push_back({0, 0});
        n = read(), m = read(); 
        for(int i = 1; i <= n; i++)
        {
            a[i] = read(), A[i] = read();
            x[A[i]].push_back({i, a[i]+x[A[i]][x[A[i]].size()-1].sum});
            posa[i] = x[A[i]].size() - 1;
        }
        for(int i = 1; i <= m; i++)
        {
            b[i] = read(), B[i] = read();
            y[B[i]].push_back({i, b[i]+y[B[i]][y[B[i]].size()-1].sum});
            posb[i] = y[B[i]].size() - 1;
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                if(A[i] == B[j])
                {
                    for(int k = posa[i]; k >= 1; k--)
                    {
                        for(int t = posb[j]; t >= 1; t--)
                            dp[i][j] = max(dp[i][j], min(
                            x[A[i]][posa[i]].sum - x[A[i]][k-1].sum, 
                            y[B[j]][posb[j]].sum - y[B[j]][t-1].sum)
                            + dp[ x[A[i]][k].pos-1 ][ y[B[j]][t].pos-1 ]);
                    }
                }
            }
        }
        cout <<"Case #" << hcx << ": " << dp[n][m] << "\n";
    }
    return 0;
}
```

---

