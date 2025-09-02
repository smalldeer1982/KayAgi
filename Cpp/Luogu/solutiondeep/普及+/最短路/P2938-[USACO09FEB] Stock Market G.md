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
这些题解的核心思路都是将股票交易问题转化为完全背包问题。由于每天可以多次买卖同一只股票，且股票数量不限，只要将相邻两天的股票交易看作一次完全背包过程，就能通过每天最大化收益来实现最终总获利的最大化。

各题解的主要区别在于代码实现细节和优化程度，如部分题解使用了快读、对状态转移方程的理解和实现略有差异等，但整体算法框架一致。

### 所选题解
- **作者：傅思维666（4星）**
    - **关键亮点**：思路清晰，详细分析了DP的决策方式，将复杂的股票持有多日再卖的决策转化为相邻两天的买卖决策，解决了DP的无后效性问题，代码简洁明了。
    - **核心代码**：
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
- **作者：fy0123（4星）**
    - **关键亮点**：明确指出将问题转化为完全背包问题的思路，并且提醒了数组大小和卡常的问题，给出了快读优化代码，代码结构清晰。
    - **核心代码**：
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
- **作者：inoichi_lim（4星）**
    - **关键亮点**：指出本题与其他类似题的细节差异，对完全背包的状态转移方程进行了详细解释，代码有注释，便于理解。
    - **核心代码**：
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

### 最优关键思路或技巧
- **思维转化**：将股票持有多日再卖的复杂决策转化为相邻两天的买卖决策，解决了DP的无后效性问题，使问题可以用完全背包模型解决。
- **完全背包模型应用**：每天的资金看作背包容量，当天股票价格看作物品体积，相邻两天的差价看作物品价值，通过完全背包的状态转移方程来计算每天的最大收益。

### 可拓展之处
同类型题如洛谷的[P5662 纪念品](https://www.luogu.org/problem/P5662) 、[P2938 [USACO09FEB]Bullcow S](https://www.luogu.com.cn/problem/P2938) 等，都是类似的物品买卖求最大获利问题，可使用完全背包模型解决。类似算法套路还有多重背包、0 - 1背包等，可根据题目条件中物品的数量限制进行选择。

### 推荐题目
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：多重背包问题，考察对不同类型背包问题的理解和应用。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：0 - 1背包经典问题，可帮助巩固背包问题的基础。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，与本题算法模型一致，可进一步练习。

### 个人心得摘录与总结
- **作者：hater**：考场上倒数三分钟调出来代码，使用了枚举两个交易时间再用完全背包的方法，虽复杂度较高但吸口氧能过，提醒在考场上遇到难题时可以尝试暴力解法。
- **作者：ql12345**：在调试过程中发现第二天用不完所有钱的问题，通过不断优化代码最终AC，提醒在做题时要仔细分析样例，对代码进行优化。 

---
处理用时：45.39秒