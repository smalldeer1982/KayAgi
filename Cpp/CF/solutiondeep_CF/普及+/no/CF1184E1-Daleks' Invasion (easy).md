# 题目信息

# Daleks' Invasion (easy)

## 题目描述

Heidi found out that the Daleks have created a network of bidirectional Time Corridors connecting different destinations (at different times!). She suspects that they are planning another invasion on the entire Space and Time. In order to counter the invasion, she plans to deploy a trap in the Time Vortex, along a carefully chosen Time Corridor. She knows that tinkering with the Time Vortex is dangerous, so she consulted the Doctor on how to proceed. She has learned the following:

- Different Time Corridors require different amounts of energy to keep stable.
- Daleks are unlikely to use all corridors in their invasion. They will pick a set of Corridors that requires the smallest total energy to maintain, yet still makes (time) travel possible between any two destinations (for those in the know: they will use a minimum spanning tree).
- Setting the trap may modify the energy required to keep the Corridor stable.

Heidi decided to carry out a field test and deploy one trap, placing it along the first Corridor. But she needs to know whether the Daleks are going to use this corridor after the deployment of the trap.

She gives you a map of Time Corridors (an undirected graph) with energy requirements for each Corridor.

For a Corridor $ c $ , $ E_{max}(c) $ is the largest $ e \le 10^9 $ such that if we changed the required amount of energy of $ c $ to $ e $ , then the Daleks may still be using $ c $ in their invasion (that is, it belongs to some minimum spanning tree). Your task is to calculate $ E_{max}(c_1) $ for the Corridor $ c_1 $ that Heidi plans to arm with a trap, which is the first edge in the graph.

## 说明/提示

After the trap is set, the new energy requirement for the first Corridor may be either smaller, larger, or equal to the old energy requiremenet.

In the example, if the energy of the first Corridor is set to $ 4 $ or less, then the Daleks may use the set of Corridors $ \{ \{ 1,2 \}, \{ 2,3 \} \} $ (in particular, if it were set to less than $ 4 $ , then this would be the only set of Corridors that they would use). However, if it is larger than $ 4 $ , then they will instead use the set $ \{ \{2,3\}, \{3,1\} \} $ .

## 样例 #1

### 输入

```
3 3
1 2 8
2 3 3
3 1 4
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 戴立克的入侵（简单版）

## 题目描述
海蒂发现戴立克人创建了一个双向时间走廊网络，这些走廊连接着不同的目的地（处于不同的时间！）。她怀疑他们正在策划另一场对整个时空的入侵。为了应对这次入侵，她计划在时间漩涡中沿着一条精心挑选的时间走廊布置一个陷阱。她知道摆弄时间漩涡很危险，所以她向博士咨询该如何行动。她了解到以下信息：
- 不同的时间走廊需要不同数量的能量来维持稳定。
- 戴立克人不太可能在入侵中使用所有的走廊。他们会选择一组维持总能量最小的走廊，同时仍能保证任意两个目的地之间都可以（时间）旅行（对于了解相关知识的人来说：他们会使用最小生成树）。
- 设置陷阱可能会改变维持走廊稳定所需的能量。

海蒂决定进行一次实地测试，布置一个陷阱，将其放置在第一条走廊上。但她需要知道在布置陷阱后，戴立克人是否会使用这条走廊。

她给你一张时间走廊的地图（一个无向图），以及每条走廊所需的能量。

对于一条走廊 $c$，$E_{max}(c)$ 是最大的 $e \leq 10^9$，使得如果我们将 $c$ 所需的能量改为 $e$，那么戴立克人仍可能在入侵中使用 $c$（即它属于某个最小生成树）。你的任务是计算海蒂计划布置陷阱的第一条走廊 $c_1$ 的 $E_{max}(c_1)$。

## 说明/提示
设置陷阱后，第一条走廊的新能量需求可能小于、大于或等于旧的能量需求。

在示例中，如果第一条走廊的能量设置为 4 或更小，那么戴立克人可能会使用走廊集合 $\{ \{ 1,2 \}, \{ 2,3 \} \}$（特别地，如果设置为小于 4，那么这将是他们唯一会使用的走廊集合）。然而，如果它大于 4，那么他们将改为使用集合 $\{ \{2,3\}, \{3,1\} \}$。

## 样例 #1
### 输入
```
3 3
1 2 8
2 3 3
3 1 4
```
### 输出
```
4
```

### 算法分类
图论、并查集

### 综合分析与结论
这些题解的核心思路都是基于 Kruskal 算法来解决问题。通过忽略第一条边，对其余边按权值从小到大排序后跑 Kruskal 算法，在这个过程中判断第一条边连接的两点是否联通，若联通则记录此时加入的边的权值作为答案；若最后都未联通，则说明第一条边是割边，答案为 $10^9$。不同题解在代码实现细节和辅助函数上有所差异，但整体思路一致。

### 所选题解
- **water_tomato（5星）**
    - **关键亮点**：思路清晰，对 Kruskal 算法的应用解释详细，代码简洁明了，注释清晰，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
int n,m,fa[N],cnt;
struct edge{
    int u,v,val;
}e[N];
inline int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
inline bool cmp(edge i,edge j){
    return i.val<j.val;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].val);
    }
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(e+2,e+1+m,cmp); // 忽略第一条边跑 kruskal 
    for(int i=2;i<=m&&cnt<n-1;i++){
        int u=e[i].u,v=e[i].v;
        if(find(u)==find(v)) continue;
        fa[find(u)]=find(v);
        cnt++;
        if(find(e[1].u)==find(e[1].v)){
            printf("%d\n",e[i].val);
            return 0;
        }   
    }
    if(cnt<n-1){ // 如果是割边 
        cout<<(int)1e9;
    }
    return 0;
}
```
**核心实现思想**：先读取图的点数和边数以及每条边的信息，对边按权值排序（忽略第一条边），使用并查集来判断两点是否联通，在跑 Kruskal 算法过程中，当第一条边连接的两点联通时，输出当前边的权值，若最后都未联通则输出 $10^9$。

- **rouxQ（4星）**
    - **关键亮点**：对 Kruskal 算法的实现过程解释清晰，代码结构清晰，注释明确。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 1e6 + 5;
struct edge{int u, v, w;}e[M];
bool cmp(edge x, edge y){return x.w < y.w;}
int fa[N];
int find(int k){return k == fa[k] ? k : fa[k] = find(fa[k]);}
int main (){
    int n, m;
    scanf("%d%d", &n, &m);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c); // 事先把第一条边拎出来
    for (int i = 1; i < m; i++)scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m, cmp);
    for (int i = 1; i <= n; i++)fa[i] = i;
    int sum = 0, ans = 1e9;
    for (int i = 1; i < m; i++){
        int uf = find(e[i].u), vf = find(e[i].v);
        if (uf != vf){
            fa[uf] = vf;
            sum++;
            if (find(a) == find(b)){ // 若连接了一条边后发现
                ans = e[i].w; // 第一条边连接的两个点已联通
                break;
            }
            if (sum == n - 1)break;
        }
    }
    cout << ans << endl;
    return 0;
}
```
**核心实现思想**：先读取图的信息，将第一条边单独拎出，对其余边按权值排序，使用并查集判断联通性，在跑 Kruskal 算法过程中，当第一条边连接的两点联通时，记录当前边的权值作为答案，若最后都未联通则答案为 $10^9$。

### 最优关键思路或技巧
- 利用 Kruskal 算法的特性，按边权从小到大添加边，忽略第一条边，在添加边的过程中判断第一条边连接的两点是否联通，从而确定第一条边的最大权值。
- 使用并查集来高效判断两点是否联通，优化算法复杂度。

### 可拓展之处
同类型题目可能会在图的类型（有向图、带负权边等）、边的限制条件（边权范围、边的数量限制等）、问题的变种（求最小生成树的数量、修改多条边的权值等）上进行拓展。类似算法套路可以应用在其他图论问题中，如求次小生成树、最大生成树等。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)

### 个人心得
题解中未包含个人心得内容。

---
处理用时：54.48秒