# 题目信息

# [USACO09FEB] Stock Market G

## 题目描述

尽管奶牛天生谨慎，它们仍然在住房抵押信贷市场中大受打击，现在它们准备在股市上碰碰运气。贝西有内部消息，她知道 $S$ 只股票在今后 $D$ 天内的价格。

假设在一开始，她筹集了 $M$ 元钱，那么她该怎样操作才能赚到最多的钱呢？贝西在每天可以买卖多只股票，也可以多次买卖同一只股票，交易单位必须是整数，数量不限。举一个牛市的例子：

假设贝西有 $10$ 元本金，股票价格如下：

|  股票 | 今天的价格 | 明天的价格 | 后天的价格 |
| :-: | :---: | :---: | :---: |
| $A$ |   $10$  |   $15$  |   $15$  |
| $B$ |   $13$  |   $11$  |   $20$  |

最赚钱的做法是：今天买入 $A$ 股 $1$ 张，到明天把它卖掉并且买入 $B$ 股 $1$ 张，在后天卖掉 $B$ 股，这样贝西就有 $24$ 元了。

## 样例 #1

### 输入

```
2 3 10 
10 15 15 
13 11 20 
```

### 输出

```
24 
```

# AI分析结果

### 综合分析与结论
这些题解大多将股票买卖问题转化为完全背包问题来解决。核心思路是把每天的资金看作背包容量，股票价格作为物品体积，相邻两天股票的差价作为物品价值，通过多次进行完全背包求解来最大化最终收益。部分题解还对决策进行了简化，如将非相邻天的买卖转化为相邻天的买卖，以满足无后效性。各题解在代码实现、细节处理和优化程度上存在差异。

### 所选题解
- **作者：傅思维666（4星）**
    - **关键亮点**：思路清晰，详细分析了DP的决策方式，将复杂的买卖情况简化为相邻两天的操作，解决了DP的无后效性问题，代码实现简洁明了。
    - **个人心得**：无
- **作者：fy0123（4星）**
    - **关键亮点**：不仅准确地将问题转化为完全背包问题，还指出了数组大小和卡常的注意事项，并给出了快读优化代码，考虑较为全面。
    - **个人心得**：无
- **作者：inoichi_lim（4星）**
    - **关键亮点**：明确指出本题与其他类似题的细节差异，对DP数组和状态转移方程的解释较为清晰，同时提到了测试点的时间情况。
    - **个人心得**：无

### 重点代码
#### 傅思维666的代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int s,d,m,maxx;
int map[60][20],dp[500001];
int main()
{
    scanf("%d%d%d",&s,&d,&m);
    for(int i=1;i<=s;i++)
        for(int j=1;j<=d;j++)
            scanf("%d",&map[i][j]);
    for(int i=2;i<=d;i++)
    {
        maxx=-1;
        memset(dp,0,sizeof(dp));
        for(int j=1;j<=s;j++)
            for(int k=map[j][i-1];k<=m;k++)
            {
                dp[k]=max(dp[k],dp[k-map[j][i-1]]+map[j][i]-map[j][i-1]);
                maxx=max(maxx,dp[k]);
            }
        m+=maxx;
    }
    printf("%d",m);
    return 0;
}
```
**核心实现思想**：通过两层循环遍历每天的股票，对于每只股票，使用完全背包的状态转移方程更新`dp`数组，记录当天能获得的最大收益`maxx`，并更新总资金`m`。

#### fy0123的代码
```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;

const int N = 15, M = 55, MAX = 500010;
int n, m, limit;
int a[M][N], f[MAX];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

int main()
{
    n = read(), m = read(), limit = read();
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++) a[i][j] = read();
    for (int i = 2; i <= m; i ++){
        int Max = 0;
        memset(f, 0, sizeof f);
        for (int j = 1; j <= n; j ++)
            for (int k = a[j][i-1]; k <= limit; k ++){
                f[k] = max(f[k], f[k-a[j][i-1]]+a[j][i]-a[j][i-1]);
                Max = max(Max, f[k]);
            }
        limit += Max;
    }
    printf("%d\n", limit);
    return 0;
}
```
**核心实现思想**：使用快读优化输入，通过两层循环遍历每天的股票，使用完全背包的状态转移方程更新`f`数组，记录当天能获得的最大收益`Max`，并更新总资金`limit`。

#### inoichi_lim的代码
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int N=1000001,inf=0x7f7f7f7f;
int n,a[N][101],f[N],m,t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>t>>m;
    if(t==1){
        cout<<m;
        return 0;
    }
    fs(i,1,n,1){
        fs(j,1,t,1){
            cin>>a[i][j];
        }
    }
    fs(i,2,t,1){
        ms(f,0);
        int maxx=-1;
        fs(j,1,n,1){
            fs(k,a[j][i-1],m,1){
                f[k]=max(f[k],f[k-a[j][i-1]]+a[j][i]-a[j][i-1]);
                maxx=max(maxx,f[k]);
            }
        }
        m+=maxx;
    }
    cout<<m;
    return 0;
}
```
**核心实现思想**：先处理特殊情况，然后通过两层循环遍历每天的股票，使用完全背包的状态转移方程更新`f`数组，记录当天能获得的最大收益`maxx`，并更新总资金`m`。

### 最优关键思路或技巧
- **决策简化**：将非相邻天的买卖转化为相邻天的买卖，解决了DP的无后效性问题，使问题可以用完全背包求解。
- **完全背包模型**：把每天的资金看作背包容量，股票价格作为物品体积，相邻两天股票的差价作为物品价值，通过多次进行完全背包求解来最大化最终收益。

### 可拓展之处
同类型题或类似算法套路：
- 其他买卖物品求最大收益的问题，如买卖纪念品、买卖黄金等，只要满足可以多次买卖同一种物品且有不同时间的价格信息，都可以考虑用完全背包来解决。
- 对于一些需要在多个阶段进行决策的问题，若每个阶段的决策可以简化为有限的几种，且满足无后效性，也可以尝试用动态规划的思想来解决。

### 推荐题目
- [P5662 纪念品](https://www.luogu.org/problem/P5662)
- [P2938 [USACO09FEB]Bullcow S](https://www.luogu.com.cn/problem/P2938)
- [P1853 投资的最大效益](https://www.luogu.com.cn/problem/P1853)

### 个人心得摘录与总结
- **ql12345**：一开始代码`m=f[m];`过不了样例，发现问题是第二天用不完所有的钱。之后尝试`int ans=m; while(f[ans-1]==f[m])--ans; m=f[ans]+m-ans;`得84分，觉得`while`循环有问题，最终改为`int ans=m; for(re int j=1;j<=m;++j)ans=max(ans,f[j]+m-j); m=ans;`才AC。总结：在处理资金更新时要考虑到当天资金可能用不完的情况，避免简单地直接赋值，同时要对代码的逻辑进行仔细推敲。
- **asdfghjkl123**：觉得自己时间已经比较优秀了，但还是没有A，加了O2以后A了，希望有朋友有兴趣加一下快读等优化。总结：在遇到时间超限的问题时，可以考虑使用O2优化或快读等优化手段。
- **A_Đark_Horcrux**：论一个CSP - J选手在洛谷看到了考试题的心情，考场上想到了思路但不会写。总结：平时要加强对算法的实践和运用，提高代码实现能力。
- **hater**：考场上倒数三分钟调了出来，用的是枚举两个交易时间再用完全背包做的n^3*max(钱数)的解法，看到题解才发现有n^3的解法，不过这个解法吸口氧还是过了，没吸氧85分。总结：考场上时间紧张，可能无法想出最优解法，但可以先实现一个可行的解法，同时要注意优化，如吸氧等。

---
处理用时：68.59秒