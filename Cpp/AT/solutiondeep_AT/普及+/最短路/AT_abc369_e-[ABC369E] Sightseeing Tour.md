# 题目信息

# [ABC369E] Sightseeing Tour

## 题目描述

#### 题目大意
给你一张 $N$ 个点，$M$ 条边的无向图（可能有重边）。第 $i$ 条边的端点是 $U_i$ 和 $V_i$，长度是 $T_i$。

给定 $Q$ 个询问，每个询问会给出 $K$ 条边。对于每个询问，请求出经过这 $K$ 条边（一定经过这 $K$ 条边，但是也可以经过其他的边）的 $1$ 到 $N$ 的最短路的长度。

## 说明/提示

- $2 \leq N \leq 400$
- $N-1 \leq M \leq 2 \times 10^5$
- $1 \leq U_i < V_i \leq N$
- $1 \leq T_i \leq 10^9$
- $1 \leq Q \leq 3000$
- $1 \leq K_i \leq 5$
- $1 \leq B_{i,1} < B_{i,2} < \cdots < B_{i,K_i} \leq M$
- 所有输入值都是整数。
- 这个图是连通图。

translate by @wujiawei36

## 样例 #1

### 输入

```
3 5

1 2 10

1 3 20

1 3 30

2 3 15

2 3 25

2

1

1

2

3 5```

### 输出

```
25

70```

## 样例 #2

### 输入

```
6 6

1 5 1

2 5 1

2 4 1

3 4 1

3 6 1

1 6 1

2

5

1 2 3 4 5

1

5```

### 输出

```
5

3```

## 样例 #3

### 输入

```
5 5

1 2 1000000000

2 3 1000000000

3 4 1000000000

4 5 1000000000

1 5 1000000000

1

1

3```

### 输出

```
4000000000```

# AI分析结果

### 题目中文重写
# [ABC369E] 观光之旅

## 题目描述

#### 题目大意
给你一张 $N$ 个点，$M$ 条边的无向图（可能有重边）。第 $i$ 条边的端点是 $U_i$ 和 $V_i$，长度是 $T_i$。

给定 $Q$ 个询问，每个询问会给出 $K$ 条边。对于每个询问，请求出经过这 $K$ 条边（一定经过这 $K$ 条边，但是也可以经过其他的边）的 $1$ 到 $N$ 的最短路的长度。

## 说明/提示

- $2 \leq N \leq 400$
- $N-1 \leq M \leq 2 \times 10^5$
- $1 \leq U_i < V_i \leq N$
- $1 \leq T_i \leq 10^9$
- $1 \leq Q \leq 3000$
- $1 \leq K_i \leq 5$
- $1 \leq B_{i,1} < B_{i,2} < \cdots < B_{i,K_i} \leq M$
- 所有输入值都是整数。
- 这个图是连通图。

## 样例 #1

### 输入
```
3 5
1 2 10
1 3 20
1 3 30
2 3 15
2 3 25
2
1
1
2
3 5
```

### 输出
```
25
70
```

## 样例 #2

### 输入
```
6 6
1 5 1
2 5 1
2 4 1
3 4 1
3 6 1
1 6 1
2
5
1 2 3 4 5
1
5
```

### 输出
```
5
3
```

## 样例 #3

### 输入
```
5 5
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
1 5 1000000000
1
1
3
```

### 输出
```
4000000000
```

### 综合分析与结论
这些题解的核心思路都是先使用 Floyd 算法预处理出图中任意两点间的最短距离，以解决图中多源最短路问题，同时处理重边情况，取边权最小值。对于每次询问给定的 $K$ 条必须经过的边，由于 $K$ 较小（$K \leq 5$），主要通过枚举边的经过顺序和方向，结合预处理的最短路信息来计算经过这些边从点 $1$ 到点 $N$ 的最短路径。

不同题解在实现枚举边的顺序和方向的方式上有所不同，有的使用全排列函数 `next_permutation`，有的使用深度优先搜索（DFS）进行枚举；在状态记录和转移方面也存在差异，部分题解使用动态规划记录状态以优化计算过程。

### 所选题解
- **作者：沃若 - 做法二（5星）**
    - **关键亮点**：思路清晰，代码简洁高效。通过全排列枚举过桥顺序，避免了额外的 $O(2^k)$ 状压枚举，使用两个变量维护上一次过桥的两种方向的最短路径，减少了状态记录的复杂度，时间复杂度为 $O(n^3+m+q\cdot k!\cdot k)$。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
long long g[405][405];
int u[200005], v[200005], w[200005];
int q;
int b[5];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            g[i][j] = g[j][i] = LLONG_MAX / 2;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]][v[i]] = min<long long>(g[u[i]][v[i]], w[i]);
        g[v[i]][u[i]] = min<long long>(g[v[i]][u[i]], w[i]);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for (cin >> q; q--; ) {
        int k;
        cin >> k;
        for (int i = 0; i < k; i++)
            cin >> b[i];
        sort(b, b + k);
        long long res = LLONG_MAX;
        do {
            int pu = 1, pv = 1;
            long long ansu = 0, ansv = 0;
            for (int i = 0; i < k; i++) {
                const long long preu = ansu, prev = ansv;
                ansu = min(preu + g[pu][v[b[i]]], prev + g[pv][v[b[i]]]) + w[b[i]];
                ansv = min(preu + g[pu][u[b[i]]], prev + g[pv][u[b[i]]]) + w[b[i]];
                pu = u[b[i]];
                pv = v[b[i]];
            }
            res = min(res, min(ansu + g[pu][n], ansv + g[pv][n]));
        } while (next_permutation(b, b + k));
        cout << res << '\n';
    }
    return 0;
}
```
- **作者：Shunpower（4星）**
    - **关键亮点**：提出了一种优化的动态规划思路，在枚举全排列得到桥的顺序后，无需再次枚举桥加入答案的方向，通过两个变量维护第 $i$ 座桥梁以两种方向加入答案时的最短路，时间复杂度为 $\mathcal O(n^3+qk!k)$。
    - **核心代码**：
```cpp
int n,m;
ll dis[410][410];
struct edge{
    int u,v;
    ll w;
} E[N];
int p[N];
int k[10];
int main(){
    ios::sync_with_stdio(false);
    memset(dis,0x3f,sizeof dis);
    cin>>n>>m;
    fr1(i,1,n) dis[i][i]=0;
    fr1(i,1,m){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        E[i]={u,v,w};
        dis[v][u]=min(dis[v][u],w);
        dis[u][v]=min(dis[u][v],w);
    }
    fr1(k,1,n){
        fr1(i,1,n){
            fr1(j,1,n) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
    int q;
    cin>>q;
    while(q--){
        int l;
        cin>>l;
        fr1(i,1,l) cin>>k[i];
        fr1(i,1,l) p[i]=i;
        ll minn=1e18;
        do{
            ll sumu=dis[1][E[k[p[1]]].u],sumv=dis[1][E[k[p[1]]].v];
            fr1(i,1,l-1){
                int u=E[k[p[i]]].u,v=E[k[p[i]]].v;
                int u2=E[k[p[i+1]]].u,v2=E[k[p[i+1]]].v;
                ll w=E[k[p[i]]].w;
                sumu+=w;
                sumv+=w;
                ll tmpu=min(sumu+dis[v][u2],sumv+dis[u][u2]);
                ll tmpv=min(sumu+dis[v][v2],sumv+dis[u][v2]);
                sumu=tmpu,sumv=tmpv;
            }
            minn=min(minn,min(sumu+E[k[p[l]]].w+dis[E[k[p[l]]].v][n],sumv+E[k[p[l]]].w+dis[E[k[p[l]]].u][n]));
        }while(next_permutation(p+1,p+l+1));
        cout<<minn<<'\n';
    }
    ET;
}
```
- **作者：I_will_AKIOI（4星）**
    - **关键亮点**：思路清晰，代码规范，详细解释了分层图思路不可行的原因，采用枚举全排列和边的方向的方法，结合预处理的全源最短路，能正确解决问题，时间复杂度为 $O(n^3+q\cdot k! \cdot 2^k \cdot k)$。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 405
#define M 200005
#pragma GCC optimize("O3")
using namespace std;
int n,m,q,x[M],y[M],z[M],a[N][N];
signed main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=1e18;
    for(int i=1;i<=m;i++)
    {
        cin>>x[i]>>y[i]>>z[i];
        a[x[i]][y[i]]=a[y[i]][x[i]]=min(a[x[i]][y[i]],z[i]);
    }
    for(int i=1;i<=n;i++) a[i][i]=0;
    for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
    cin>>q;
    while(q--)
    {
        int len,v[5],ans=1e18;
        cin>>len;
        for(int i=0;i<len;i++) cin>>v[i];
        sort(v,v+len);
        do
        {
            for(int i=0;i<(1<<len);i++)
            {
                int sum=0,last=1;
                for(int j=0;j<len;j++)
                {
                    if(i&(1<<j))
                    {
                        sum+=a[last][x[v[j]]]+z[v[j]];
                        last=y[v[j]];
                    }
                    else
                    {
                        sum+=a[last][y[v[j]]]+z[v[j]];
                        last=x[v[j]];
                    }
                }
                ans=min(ans,sum+a[last][n]);
            }
        }
        while(next_permutation(v,v+len));
        cout<<ans<<"\n";
    }
    return 0;
}
```

### 最优关键思路或技巧
- **Floyd 算法预处理**：利用 Floyd 算法在 $O(n^3)$ 时间复杂度内求出图中任意两点间的最短距离，为后续计算经过指定边的最短路径提供基础。
- **枚举优化**：对于询问中给定的少量边（$K \leq 5$），采用全排列枚举边的经过顺序，结合二进制枚举边的方向，避免了复杂的状态转移，同时利用排列组合的特性确保所有可能情况都被考虑。
- **动态规划优化**：部分题解使用动态规划记录状态，减少重复计算，如沃若的做法二和 Shunpower 的题解，通过维护上一次过桥的状态，避免了不必要的枚举，降低了时间复杂度。

### 可拓展之处
此类问题可以拓展到更复杂的图结构和约束条件，例如：
- **有向图**：当图为有向图时，边的方向固定，需要重新考虑枚举边的方向的方式。
- **更多约束条件**：增加边的使用次数限制、时间限制等约束条件，需要在原有的算法基础上增加状态记录和转移的逻辑。
- **更大的数据范围**：当 $K$ 的值增大时，枚举所有排列和方向的方法将不再适用，需要寻找更高效的算法，如启发式搜索、近似算法等。

### 推荐题目
1. [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：同样涉及 Floyd 算法，题目在图的基础上增加了时间维度的变化，需要根据时间动态更新最短路。
2. [P2934 [USACO09JAN]Safe Travel G](https://www.luogu.com.cn/problem/P2934)：考察最短路算法和路径的修改，在最短路的基础上需要处理删除某条边后的次短路问题。
3. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：可以作为最短路算法的基础练习，掌握 Dijkstra 算法和堆优化的实现。

### 个人心得摘录与总结
- **沃若**：提到记录最后位置的优化从 TSP 问题出发可以自然想到，写过 Hamilton 路径/环路的话应该比较显然，强调了知识迁移和经验积累在解题中的重要性。
- **Shadow_T**：因 `const int inf=1e18;` 这一行代码吃了罚时，提醒在代码实现中要注意数据类型和边界值的处理。
- **__Allen_123__**：赛时往 dij 分层图想，花费 50 分钟左右才通过，掉大分，说明在解题时要根据数据范围和题目特点选择合适的算法，避免陷入复杂且不可行的思路。
- **Liyunze123**：赛时 dfs 时仅恢复了不选的状态没恢复答案无缘 AC，痛失 8 rating，降到 1201 蓝名的最低下限，强调了在回溯算法中正确恢复状态的重要性。 

---
处理用时：83.19秒