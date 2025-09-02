# 题目信息

# Node Pairs

## 题目描述

Let's call an ordered pair of nodes $ (u, v) $ in a directed graph unidirectional if $ u \neq v $ , there exists a path from $ u $ to $ v $ , and there are no paths from $ v $ to $ u $ .

A directed graph is called  $ p $ -reachable if it contains exactly $ p $ ordered pairs of nodes $ (u, v) $ such that $ u < v $ and $ u $ and $ v $ are reachable from each other. Find the minimum number of nodes required to create a $ p $ -reachable directed graph.

Also, among all such $ p $ -reachable directed graphs with the minimum number of nodes, let $ G $ denote a graph which maximizes the number of unidirectional pairs of nodes. Find this number.

## 说明/提示

In the first test case, the minimum number of nodes required to create a $ 3 $ -reachable directed graph is $ 3 $ . Among all $ 3 $ -reachable directed graphs with $ 3 $ nodes, the following graph $ G $ is one of the graphs with the maximum number of unidirectional pairs of nodes, which is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1763E/056ef4fb4b6b27a5f901099fab6d214793a2d54c.png)

## 样例 #1

### 输入

```
3```

### 输出

```
3 0```

## 样例 #2

### 输入

```
4```

### 输出

```
5 6```

## 样例 #3

### 输入

```
0```

### 输出

```
0 0```

# AI分析结果

### 题目中文重写
# 节点对

## 题目描述
在有向图中，如果有序节点对 $(u, v)$ 满足 $u \neq v$，存在从 $u$ 到 $v$ 的路径，且不存在从 $v$ 到 $u$ 的路径，则称该节点对为单向节点对。

如果一个有向图恰好包含 $p$ 个有序节点对 $(u, v)$，其中 $u < v$ 且 $u$ 和 $v$ 相互可达，则称该有向图为 $p$ -可达图。求创建一个 $p$ -可达图所需的最少节点数。

此外，在所有具有最少节点数的 $p$ -可达图中，设 $G$ 是单向节点对数量最多的图，求出这个数量。

## 说明/提示
在第一个测试用例中，创建一个 $3$ -可达图所需的最少节点数是 $3$。在所有具有 $3$ 个节点的 $3$ -可达图中，下图 $G$ 是单向节点对数量最多的图之一，其数量为 $0$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1763E/056ef4fb4b6b27a5f901099fab6d214793a2d54c.png)

## 样例 #1
### 输入
```
3
```
### 输出
```
3 0
```

## 样例 #2
### 输入
```
4
```
### 输出
```
5 6
```

## 样例 #3
### 输入
```
0
```
### 输出
```
0 0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先将问题转化为完全背包问题来解决第一问，即求创建 $p$ -可达图所需的最少节点数，再在此基础上解决第二问，求单向节点对的最大数量。
- **思路**：由于相互可达的节点对必在同一个强连通分量中，一个大小为 $n$ 的强连通分量能产生 $\frac{n(n - 1)}{2}$ 对相互可达的节点对，所以可将问题转化为从各种大小的强连通图中选若干种，使它们的节点对数之和为 $p$ 且节点数最少，这是一个完全背包问题。对于第二问，不同题解采用了不同的方法来计算单向节点对的最大数量，如用总节点对数减去双向节点对数量，或通过构造有向边来计算等。
- **算法要点**：第一问使用动态规划，通过枚举强连通分量的大小进行状态转移；第二问则根据不同的思路计算单向节点对数量。
- **解决难点**：主要难点在于将问题转化为完全背包问题，以及如何在节点数最少的情况下最大化单向节点对数量。部分题解在证明第二问的构造方法最优性时也有一定难度。

### 所选题解
- **作者：nullqtr_pwp (4星)**
    - **关键亮点**：思路清晰，先明确问题与强连通分量的关系，再分别用动态规划解决两问，代码简洁易懂。
- **作者：stntn (4星)**
    - **关键亮点**：将问题分析得很透彻，先贪心思考第一问，再用完全背包求解，第二问的计算方法也很清晰。
- **作者：Polaris_Australis_ (4星)**
    - **关键亮点**：简洁明了地指出两问的解决方法，代码实现也很简洁。

### 重点代码
#### nullqtr_pwp 的代码
```cpp
int f[maxn];
signed main(){
    int n=read();
    memset(f,0x3f,sizeof f);
    f[0]=0,f[1]=2;
    F(i,2,n) F(j,2,i){
        int cur=j*(j-1)/2;
        if(i<cur) break;
        f[i]=min(f[i-cur]+j,f[i]);
    }
    printf("%d ",f[n]);
    ll ans=1ll*f[n]*(f[n]-1);
    ans>>=1;
    printf("%lld\n",ans-n);
}
```
**核心实现思想**：用 `f[i]` 表示产生 $i$ 对互相可达点对至少需要的节点数，通过枚举强连通分量的大小进行状态转移。第二问用总节点对数减去双向节点对数量得到单向节点对数量。

#### stntn 的代码
```cpp
#include<bits/stdc++.h>
#define N 110
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
#define mod 1000000007
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
// 省略部分代码
int n,sum,ans,f[200010],fr[200010];
vector<int> b;
inline int calc(int x){return (x*(x-1))>>1;}
signed main()
{
    read(n);
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    rep(i,2,633)
    {
        int w=calc(i);
        rep(j,w,n) if(f[j-w]+i<f[j]) f[j]=f[j-w]+i,fr[j]=i;
    }
    for(int i=n;i;i-=calc(fr[i])) b.push_back(fr[i]);
    for(int x:b)
    {
        ans+=sum*x;sum+=x;
    }
    printf("%d %d\n",f[n],ans);
    return 0;
}
```
**核心实现思想**：同样用 `f[i]` 表示产生 $i$ 对互相可达点对至少需要的节点数，通过完全背包进行状态转移。第二问通过记录每个强连通分量的大小，计算单向节点对数量。

#### Polaris_Australis_ 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

namespace Wilson_Inversion{

void main();

}

int main(){
    Wilson_Inversion::main();
    return 0;
}

namespace Wilson_Inversion{

int n,dp[200010];

void main(){
    scanf("%d",&n);
    for(int i(1);i<=n;++i){
        dp[i]=0x3f3f3f3f;
        for(int j(2);j*(j-1)/2<=i;++j){
            dp[i]=min(dp[i],dp[i-j*(j-1)/2]+j);
        }
    }
    printf("%d %lld\n",dp[n],1ll*dp[n]*(dp[n]-1)/2-n);
}

}
```
**核心实现思想**：用 `dp[i]` 表示产生 $i$ 对互相可达点对至少需要的节点数，通过枚举强连通分量的大小进行状态转移。第二问用总节点对数减去双向节点对数量得到单向节点对数量。

### 关键思路或技巧
- **问题转化**：将问题转化为完全背包问题，把强连通分量的大小看作物品，其产生的节点对数看作价值，节点数看作代价。
- **构造方法**：在计算单向节点对数量时，通过合理构造有向边，如将强连通分量排列成链，可使单向节点对数量最大化。

### 拓展思路
同类型题或类似算法套路包括其他与图的连通性和节点对相关的问题，以及完全背包的变形问题。在处理这类问题时，关键是要准确分析问题的本质，将其转化为已知的算法模型。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，可帮助理解背包问题的基本思想。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，与本题第一问的算法模型相同。
- [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)：动态规划问题，可锻炼动态规划的思维能力。

### 个人心得
- wind_seeker 提到自己的做法很烂，认为楼上 Wilson_Inversion 的做法更好，意识到拿所有点对数减去 $p$ 来计算单向节点对数更优，这表明在解题过程中要多学习他人的优秀思路，不断优化自己的解法。

---
处理用时：62.05秒