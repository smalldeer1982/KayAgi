# 题目信息

# Misha, Grisha and Underground

## 题目描述

Misha and Grisha are funny boys, so they like to use new underground. The underground has $ n $ stations connected with $ n-1 $ routes so that each route connects two stations, and it is possible to reach every station from any other.

The boys decided to have fun and came up with a plan. Namely, in some day in the morning Misha will ride the underground from station $ s $ to station $ f $ by the shortest path, and will draw with aerosol an ugly text "Misha was here" on every station he will pass through (including $ s $ and $ f $ ). After that on the same day at evening Grisha will ride from station $ t $ to station $ f $ by the shortest path and will count stations with Misha's text. After that at night the underground workers will wash the texts out, because the underground should be clean.

The boys have already chosen three stations $ a $ , $ b $ and $ c $ for each of several following days, one of them should be station $ s $ on that day, another should be station $ f $ , and the remaining should be station $ t $ . They became interested how they should choose these stations $ s $ , $ f $ , $ t $ so that the number Grisha will count is as large as possible. They asked you for help.

## 说明/提示

In the first example on the first day if $ s $ = $ 1 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ , and Grisha would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . He would see the text at the stations $ 1 $ and $ 2 $ . On the second day, if $ s $ = $ 3 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , both boys would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . Grisha would see the text at $ 3 $ stations.

In the second examle if $ s $ = $ 1 $ , $ f $ = $ 3 $ , $ t $ = $ 2 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ , and Grisha would go on the route $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ and would see the text at both stations.

## 样例 #1

### 输入

```
3 2
1 1
1 2 3
2 3 3
```

### 输出

```
2
3
```

## 样例 #2

### 输入

```
4 1
1 2 3
1 2 3
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# Misha, Grisha和地铁

## 题目描述
Misha和Grisha是有趣的男孩，所以他们喜欢乘坐新地铁。地铁有$n$个站点，由$n - 1$条路线连接，使得每条路线连接两个站点，并且从任何一个站点都可以到达其他任何站点。

男孩们决定找点乐子并想出了一个计划。具体来说，在某天早上，Misha将从站点$s$乘坐地铁，沿最短路径到达站点$f$，并在他经过的每个站点（包括$s$和$f$）上用喷雾器写下一句丑陋的话“Misha曾到此一游”。之后，在同一天晚上，Grisha将从站点$t$乘坐地铁，沿最短路径到达站点$f$，并统计带有Misha写下文字的站点数量。然后在晚上，地铁工作人员会把这些文字洗掉，因为地铁应该保持干净。

在接下来的几天里，男孩们已经为每一天选择了三个站点$a$、$b$和$c$，其中一个应该是当天的站点$s$，另一个应该是站点$f$，剩下的一个应该是站点$t$。他们想知道应该如何选择这些站点$s$、$f$、$t$，以便Grisha统计的数量尽可能多。他们向你寻求帮助。

## 说明/提示
在第一个示例中，在第一天，如果$s = 1$，$f = 2$，$t = 3$，Misha将沿着路线$1$→$2$行驶，而Grisha将沿着路线$3$→$1$→$2$行驶。他会在站点$1$和$2$看到文字。在第二天，如果$s = 3$，$f = 2$，$t = 3$，两个男孩都会沿着路线$3$→$1$→$2$行驶。Grisha会在$3$个站点看到文字。

在第二个示例中，如果$s = 1$，$f = 3$，$t = 2$，Misha将沿着路线$1$→$2$→$3$行驶，而Grisha将沿着路线$2$→$3$行驶，并会在两个站点看到文字。

## 样例 #1
### 输入
```
3 2
1 1
1 2 3
2 3 3
```
### 输出
```
2
3
```
## 样例 #2
### 输入
```
4 1
1 2 3
1 2 3
```
### 输出
```
2
```

### 算法分类
数学（主要利用树的性质和最近公共祖先LCA相关数学计算）

### 题解综合分析与结论
这些题解主要围绕如何通过树的性质和最近公共祖先（LCA）来解决问题。思路上，大多先明确需要枚举三个点作为起点、终点的不同组合情况，再通过LCA计算路径交点数量。算法要点在于高效求出LCA，不同题解采用了倍增法、树链剖分、ST表等不同方式。解决难点在于处理三条路径关系及找到通用计算公共节点数的方法，部分题解通过分类讨论，部分通过容斥原理般的公式推导。

### 所选的题解
- **作者：Little_x_starTYJ（5星）**
  - **关键亮点**：思路清晰，先分析暴力方法的不可行，引出倍增法求LCA的思路，详细阐述利用深度差求公共节点数的原理，代码简洁明了，注释清晰。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
vector<int> v[N];
int fa[N];
int f[N][20], dep[N];
void dfs(int u) {
    f[u][0] = fa[u], dep[u] = dep[fa[u]] + 1;
    for (int i = 0; i < v[u].size(); i++)
        if (v[u][i]!= fa[u])
            dfs(v[u][i]);
}
int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    int x = a;
    for (int i = log2(dep[a] - dep[b]); i >= 0; i--)
        if ((1 << i) <= dep[a] - dep[b])
            a = f[a][i];
    if (a == b)
        return a;
    for (int i = log2(dep[a]); i >= 0; i--)
        if (f[a][i]!= f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
int dist(int u, int v) {
    int ans = lca(u, v);
    ans = dep[u] - dep[ans] + dep[v] - dep[ans];
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int k;
        scanf("%d", &k);
        fa[i + 1] = k;
        v[k].push_back(i + 1);
        v[i + 1].push_back(k);
    }
    dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            f[j][i] = f[f[j][i - 1]][i - 1];
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ans1 = (dist(a, c) + dist(b, c) - dist(a, b)) / 2;
        int ans2 = (dist(a, b) + dist(c, b) - dist(a, c)) / 2;
        int ans3 = (dist(b, a) + dist(c, a) - dist(b, c)) / 2;
        printf("%d\n", max(ans1, max(ans2, ans3)) + 1);
    }
    return 0;
}
```
  - **核心实现思想**：通过`dfs`初始化节点深度和倍增数组，`lca`函数利用倍增法求最近公共祖先，`dist`函数计算两点距离，主函数中枚举三个点不同组合计算公共节点数。
- **作者：一只书虫仔（4星）**
  - **关键亮点**：对问题分析详细，从路径交点出发，通过公式推导得出通用计算公共节点数的式子，代码采用ST表求LCA，注释清晰。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

//
struct node {
    int u, v;
} e[N];

int cnt;
int head[N];

void AddEdge (int u, int v) {
    e[++cnt].u = v;
    e[cnt].v = head[u];
    head[u] = cnt;
}
//
struct to {
    int id; // 节点编号 
    int dep; // 节点深度 
    bool operator < (const to &oth) const {
        return dep < oth.dep;
    } // 重载运算符 '<'
} dfn[N], dp[N][20]; // dfs 序 & ST 

int dep[N], id[N]; // 节点深度 & 第一次出现在 dfs 序的位置
int len; // dfs 序长度

void dfs (int cur, int fa) {
    dep[cur] = dep[fa] + 1;
    dfn[++len] = (to){cur, dep[cur]};
    id[cur] = len;
    for (int p = head[cur]; p; p = e[p].v) {
        if (e[p].u == fa) continue;
        dfs(e[p].u, cur);
        dfn[++len] = (to){cur, dep[cur]};
    }
} 
//
int LCA (int u, int v) {
    int l = id[u], r = id[v];
    if (l > r) swap(l, r);
    int k = log2(r - l + 1);
    to tmp = min(dp[l][k], dp[r - (1 << k) + 1][k]);
    int ans = tmp.id;
    return ans;
}

int dist (int u, int v) {
    int ans = LCA(u, v);
    ans = dep[u] - dep[ans] + dep[v] - dep[ans];
    return ans;
}

int main () {
    int n, q;
    scanf("%d%d", &n, &q);
    int s = 1;
    for (int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        AddEdge(i, p);
        AddEdge(p, i);
    }
    dfs(s, 0);
    for (int i = 1; i <= len; i++) dp[i][0] = dfn[i];
    for (int k = 1; (1 << k) <= len; k++)
        for (int i = 1; i + (1 << k) - 1 <= len; i++)
            dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
    while (q--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ans1 = (dist(a, c) + dist(b, c) - dist(a, b)) / 2;
        int ans2 = (dist(a, b) + dist(c, b) - dist(a, c)) / 2;
        int ans3 = (dist(b, a) + dist(c, a) - dist(b, c)) / 2;
        printf("%d\n", max(ans1, max(ans2, ans3)) + 1);
    }
    return 0;
}
```
  - **核心实现思想**：`dfs`记录节点深度和dfs序，`LCA`函数利用ST表求最近公共祖先，`dist`函数计算两点距离，主函数通过枚举不同组合并利用推导公式计算公共节点数。
- **作者：Fairicle（4星）**
  - **关键亮点**：提出一种分类讨论后得到的通解，无需在代码里过多分类讨论，通过分析三个点两两求LCA的情况得出答案计算方式，代码逻辑清晰。
  - **重点代码**：
```cpp
#define N 100010
#define ri register int
int n,q,x,y,head[N],wl,dep[N],f[N][18],a,b,c;
struct node{
    int nxt,to;
}star[N<<1];
inline void add(int from,int to){
    wl++;
    star[wl].to=to;
    star[wl].nxt=head[from];
    head[from]=wl;
}
inline void dfs(int x,int fa){
    dep[x]=dep[fa]+1;f[x][0]=fa;
    for(ri j=1;j<=17;++j) f[x][j]=f[f[x][j-1]][j-1];
    for(ri i=head[x];i;i=star[i].nxt){
        int u=star[i].to;if(u==fa) continue;
        dfs(u,x);
    }
}
inline int get_lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    int t=dep[x]-dep[y];
    for(ri i=0;i<=17;++i) if(t&(1<<i)) x=f[x][i];if(x==y) return x;
    for(ri i=17;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
inline int get_dis(int x,int y){return dep[x]+dep[y]-2*dep[get_lca(x,y)];}
int main(){
    cin>>n>>q;
    for(ri i=2;i<=n;++i) cin>>x,add(x,i),add(i,x);
    dfs(1,0);
    while(q--){
        int lca1=get_lca(a,b),lca2=get_lca(b,c),lca3=get_lca(a,c),tar;
        if(lca1==lca2){
            if(dep[lca1]<dep[lca3]) tar=lca3;
            else tar=lca1;
        }
        else{
            if(dep[lca1]<dep[lca2]) tar=lca2;
            else tar=lca1;
        }
        cout<<max(get_dis(tar,a),max(get_dis(tar,b),get_dis(tar,c)))+1<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：`dfs`初始化深度和倍增数组，`get_lca`利用倍增法求LCA，`get_dis`计算两点距离，主函数通过比较三个点两两LCA的深度确定计算答案的关键点，进而求出公共节点数。

### 最优关键思路或技巧
利用最近公共祖先LCA来解决问题，通过数学推导得出通用的计算公共节点数的公式，避免复杂的分类讨论。如`(dist(a, c) + dist(b, c) - dist(a, b)) / 2 + 1`这种通过距离计算公共节点数的方式。同时，采用倍增法、ST表等高效求LCA的方式优化算法。

### 拓展
同类型题常围绕树结构，结合LCA考察路径相关问题，类似套路为分析路径关系，利用LCA及节点深度等信息推导计算目标值的公式。

### 推荐题目
- [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)：基础的LCA模板题，用于巩固LCA算法。
- [P4281 [AHOI2008]紧急集合 / 聚会](https://www.luogu.com.cn/problem/P4281)：同样是在树上分析路径交点相关问题，可加深对树结构和LCA应用的理解。
- [P1852 跳跳棋](https://www.luogu.com.cn/problem/P1852)：结合了LCA思想与其他数学推导，锻炼综合运用能力。

### 个人心得摘录
部分题解提到在处理三个点在树上的路径关系时，直接分类讨论情况复杂易错，而通过推导通用公式的方式能更简洁准确地解决问题，避免因情况考虑不全导致错误。 

---
处理用时：129.82秒