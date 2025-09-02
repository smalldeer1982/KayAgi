# 题目信息

# Shovels Shop

## 题目描述

There are $ n $ shovels in the nearby shop. The $ i $ -th shovel costs $ a_i $ bourles.

Misha has to buy exactly $ k $ shovels. Each shovel can be bought no more than once.

Misha can buy shovels by several purchases. During one purchase he can choose any subset of remaining (non-bought) shovels and buy this subset.

There are also $ m $ special offers in the shop. The $ j $ -th of them is given as a pair $ (x_j, y_j) $ , and it means that if Misha buys exactly $ x_j $ shovels during one purchase then $ y_j $ most cheapest of them are for free (i.e. he will not pay for $ y_j $ most cheapest shovels during the current purchase).

Misha can use any offer any (possibly, zero) number of times, but he cannot use more than one offer during one purchase (but he can buy shovels without using any offers).

Your task is to calculate the minimum cost of buying $ k $ shovels, if Misha buys them optimally.

## 说明/提示

In the first example Misha can buy shovels on positions $ 1 $ and $ 4 $ (both with costs $ 2 $ ) during the first purchase and get one of them for free using the first or the third special offer. And then he can buy shovels on positions $ 3 $ and $ 6 $ (with costs $ 4 $ and $ 3 $ ) during the second purchase and get the second one for free using the first or the third special offer. Then he can buy the shovel on a position $ 7 $ with cost $ 1 $ . So the total cost is $ 4 + 2 + 1 = 7 $ .

In the second example Misha can buy shovels on positions $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 8 $ (costs are $ 6 $ , $ 8 $ , $ 5 $ , $ 1 $ and $ 2 $ ) and get three cheapest (with costs $ 5 $ , $ 1 $ and $ 2 $ ) for free. And then he can buy shovels on positions $ 6 $ , $ 7 $ and $ 9 $ (all with costs $ 1 $ ) without using any special offers. So the total cost is $ 6 + 8 + 1 + 1 + 1 = 17 $ .

In the third example Misha can buy four cheapest shovels without using any special offers and get the total cost $ 17 $ .

## 样例 #1

### 输入

```
7 4 5
2 5 4 2 6 3 1
2 1
6 5
2 1
3 1
```

### 输出

```
7
```

## 样例 #2

### 输入

```
9 4 8
6 8 5 1 8 1 1 2 1
9 2
8 4
5 3
9 7
```

### 输出

```
17
```

## 样例 #3

### 输入

```
5 1 4
2 5 7 4 6
5 4
```

### 输出

```
17
```

# AI分析结果

### 题目翻译
# 铲子商店

## 题目描述
附近的商店里有 $n$ 把铲子。第 $i$ 把铲子的价格是 $a_i$ 布尔（货币单位）。

米莎必须正好买 $k$ 把铲子。每把铲子最多只能买一次。

米莎可以分多次购买铲子。在一次购买中，他可以选择剩余（未购买）铲子的任意子集并购买这个子集。

商店里还有 $m$ 种特殊优惠。第 $j$ 种优惠用一对 $(x_j, y_j)$ 表示，这意味着如果米莎在一次购买中正好买了 $x_j$ 把铲子，那么其中最便宜的 $y_j$ 把铲子是免费的（即他在本次购买中无需为 $y_j$ 把最便宜的铲子付款）。

米莎可以任意次数（可能为零次）使用任何一种优惠，但在一次购买中不能使用超过一种优惠（不过他也可以不使用任何优惠购买铲子）。

你的任务是计算米莎以最优方式购买 $k$ 把铲子的最小成本。

## 说明/提示
在第一个示例中，米莎可以在第一次购买中选择位置为 $1$ 和 $4$ 的铲子（价格均为 $2$），并使用第一个或第三个特殊优惠免费获得其中一把。然后，他可以在第二次购买中选择位置为 $3$ 和 $6$ 的铲子（价格分别为 $4$ 和 $3$），并使用第一个或第三个特殊优惠免费获得第二把。最后，他可以以 $1$ 的价格购买位置为 $7$ 的铲子。因此，总成本为 $4 + 2 + 1 = 7$。

在第二个示例中，米莎可以购买位置为 $1$、$2$、$3$、$4$ 和 $8$ 的铲子（价格分别为 $6$、$8$、$5$、$1$ 和 $2$），并使用优惠免费获得其中最便宜的三把（价格为 $5$、$1$ 和 $2$）。然后，他可以不使用任何优惠购买位置为 $6$、$7$ 和 $9$ 的铲子（价格均为 $1$）。因此，总成本为 $6 + 8 + 1 + 1 + 1 = 17$。

在第三个示例中，米莎可以不使用任何优惠购买四把最便宜的铲子，总成本为 $17$。

## 样例 #1
### 输入
```
7 4 5
2 5 4 2 6 3 1
2 1
6 5
2 1
3 1
```
### 输出
```
7
```

## 样例 #2
### 输入
```
9 4 8
6 8 5 1 8 1 1 2 1
9 2
8 4
5 3
9 7
```
### 输出
```
17
```

## 样例 #3
### 输入
```
5 1 4
2 5 7 4 6
5 4
```
### 输出
```
17
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先利用贪心思想，确定购买价格最低的 $k$ 把铲子，然后使用动态规划来计算最小花费。具体做法是对铲子价格进行排序并计算前缀和，对于每个购买数量 $x$ 的优惠套餐，记录能免费的最大数量 $y$ 。通过两层循环进行动态规划转移，外层循环枚举购买的铲子数量，内层循环枚举之前购买的铲子数量，利用状态转移方程计算最小花费。

### 所选的题解
- **作者：字如其人 (赞：8)，4星**
    - **关键亮点**：思路清晰，先证明了购买价格最低的 $k$ 把铲子的贪心策略，然后详细阐述了动态规划的状态定义和转移方程，代码简洁易懂。
- **作者：1saunoya (赞：2)，4星**
    - **关键亮点**：代码简洁，使用自定义的 `cmax` 和 `cmin` 函数，逻辑清晰，同样先确定贪心策略，再进行动态规划求解。
- **作者：I_have_been_here (赞：1)，4星**
    - **关键亮点**：思路解析详细，对状态数组和状态转移方程的解释很清楚，通过定义最大优惠价格的状态数组，最后用前缀和减去最大优惠得到最小花费。

### 重点代码
#### 作者：字如其人
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
int n,m,k,a[N],cal[N],f[N];
signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%lld%lld",&x,&y);
        cal[x]=max(cal[x],y);
    }
    memset(f,0x7f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=k;i++){
        for(int j=0;j<=i-1;j++)
            f[i]=min(f[i],f[j]+a[i]-a[j+cal[i-j]]); 
    }
    printf("%lld",f[k]);
    return 0;
}
```
**核心实现思想**：先对铲子价格排序并计算前缀和，记录每个购买数量对应的最大免费数量，然后通过动态规划，枚举购买数量和之前购买数量，更新最小花费。

#### 作者：1saunoya
```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}

int n,m,k;
const int N=2e5+2;
int a[N];
int f[N];
int dp[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m>>k;
    rep(i,1,n){cin>>a[i];}sort(a+1,a+n+1);rep(i,1,k){a[i]+=a[i-1];}
    while(m--){int x,y;cin>>x>>y;cmax(f[x],y);}
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    rep(i,1,k){rep(j,0,i-1){cmin(dp[i],dp[j]+a[i]-a[j+f[i-j]]);}}
    cout<<dp[k]<<'\n';
    return 0;
}
```
**核心实现思想**：同样先排序和计算前缀和，记录最大免费数量，然后通过两层循环进行动态规划更新最小花费。

#### 作者：I_have_been_here
```cpp
#include <bits/stdc++.h>
#define maxn 200005
using namespace std;
int dp[maxn], pre[maxn], buy[maxn], a[maxn];
int n, m, k;
int main() {
    cin >> n >> m >> k;
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= k; i++)
        pre[i] = pre[i - 1] + a[i];
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        buy[x] = max(buy[x], y);
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = max(dp[i], dp[j] + pre[j + buy[i - j]] - pre[j]);
        }
    }
    cout << pre[k] - dp[k] << endl;
}
```
**核心实现思想**：先排序和计算前缀和，记录最大免费数量，通过动态规划计算最大优惠价格，最后用前缀和减去最大优惠得到最小花费。

### 最优关键思路或技巧
- **贪心策略**：先证明购买价格最低的 $k$ 把铲子能使总花费最小，简化问题。
- **前缀和优化**：通过计算前缀和，可以在 $O(1)$ 时间内得到区间和，提高动态规划的效率。
- **动态规划**：定义合适的状态数组和状态转移方程，通过两层循环进行状态转移，计算最小花费。

### 可拓展之处
同类型题可能会改变优惠套餐的规则，或者增加更多的限制条件，如购买次数限制、不同类型的铲子等。类似算法套路可以应用于其他需要在多种选择中求最优解的问题，如背包问题、区间选择问题等。

### 推荐洛谷题目
- P1048 [NOIP2005 普及组] 采药：经典的 0 - 1 背包问题，与本题的动态规划思想类似。
- P1216 [USACO1.5] [IOI1994] 数字三角形 Number Triangles：简单的动态规划入门题，通过递推求解最优路径。
- P1802 5 倍经验日：同样是动态规划问题，需要在不同的选择中求最大经验值。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：63.71秒