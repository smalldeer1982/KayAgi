# 题目信息

# [ABC362D] Shortest Path 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_d

$ N $ 頂点 $ M $ 辺の単純連結無向グラフが与えられます。頂点 $ i\,(1\leq\ i\ \leq\ N) $ は重み $ A_i $ を持ちます。また、辺 $ j\,(1\leq\ j\ \leq\ M) $ は頂点 $ U_j,V_j $ を双方向に結び、重み $ B_j $ を持ちます。

このグラフ上のパスの重みを、パス上に現れる頂点の重みと辺の重みの総和と定義します。

各 $ i=2,3,\dots,N $ について、以下の問題を解いてください。

- 頂点 $ 1 $ から頂点 $ i $ までのパスであって、重みが最小となるものの重みを求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_j\ <\ V_j\ \leq\ N $
- $ i\neq\ j $ なら $ (U_i,V_i)\ \neq\ (U_j,V_j) $
- グラフは連結である
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- $ 0\ \leq\ B_j\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

頂点 $ 1 $ から頂点 $ 2 $ へのパスを考えます。 パス $ 1\ \to\ 2 $ の重みは $ A_1+B_1+A_2=1+1+2=4 $、パス $ 1\ \to\ 3\ \to\ 2 $ の重みは $ A_1+B_2+A_3+B_3+A_2=1+6+3+2+2=14 $ であり、最小の重みは $ 4 $ です。 頂点 $ 1 $ から頂点 $ 3 $ へのパスを考えます。 パス $ 1\ \to\ 3 $ の重みは $ A_1+B_2+A_3=1+6+3=10 $、パス $ 1\ \to\ 2\ \to\ 3 $ の重みは $ A_1+B_1+A_2+B_3+A_3=1+1+2+2+3=9 $ であり、最小の重みは $ 9 $ です。

### Sample Explanation 3

答えが 32-bit 整数に収まらないことがあることに注意してください。

## 样例 #1

### 输入

```
3 3

1 2 3

1 2 1

1 3 6

2 3 2```

### 输出

```
4 9```

## 样例 #2

### 输入

```
2 1

0 1

1 2 3```

### 输出

```
4```

## 样例 #3

### 输入

```
5 8

928448202 994752369 906965437 942744902 907560126

2 5 975090662

1 2 908843627

1 5 969061140

3 4 964249326

2 3 957690728

2 4 942986477

4 5 948404113

1 3 988716403```

### 输出

```
2832044198 2824130042 4696218483 2805069468```

# AI分析结果

### 题目翻译
## [ABC362D] 最短路径 3

### 题目描述
给定一个具有 $N$ 个顶点和 $M$ 条边的简单连通无向图。顶点 $i\,(1\leq i\leq N)$ 的权重为 $A_i$。此外，边 $j\,(1\leq j\leq M)$ 双向连接顶点 $U_j$ 和 $V_j$，其权重为 $B_j$。

我们将图上路径的权重定义为该路径上出现的顶点权重与边权重的总和。

对于每个 $i = 2,3,\dots,N$，请解决以下问题：
- 找出从顶点 $1$ 到顶点 $i$ 的路径中权重最小的路径，并求出其权重。

### 说明/提示
#### 限制条件
- $2\leq N\leq 2\times 10^5$
- $N - 1\leq M\leq 2\times 10^5$
- $1\leq U_j < V_j\leq N$
- 若 $i\neq j$，则 $(U_i,V_i)\neq (U_j,V_j)$
- 图是连通的
- $0\leq A_i\leq 10^9$
- $0\leq B_j\leq 10^9$
- 所有输入均为整数

#### 示例解释 1
考虑从顶点 $1$ 到顶点 $2$ 的路径。路径 $1\to 2$ 的权重为 $A_1 + B_1 + A_2 = 1 + 1 + 2 = 4$，路径 $1\to 3\to 2$ 的权重为 $A_1 + B_2 + A_3 + B_3 + A_2 = 1 + 6 + 3 + 2 + 2 = 14$，因此最小权重为 $4$。

考虑从顶点 $1$ 到顶点 $3$ 的路径。路径 $1\to 3$ 的权重为 $A_1 + B_2 + A_3 = 1 + 6 + 3 = 10$，路径 $1\to 2\to 3$ 的权重为 $A_1 + B_1 + A_2 + B_3 + A_3 = 1 + 1 + 2 + 2 + 3 = 9$，因此最小权重为 $9$。

#### 示例解释 3
请注意，答案可能无法用 32 位整数表示。

### 样例 #1
#### 输入
```
3 3
1 2 3
1 2 1
1 3 6
2 3 2
```
#### 输出
```
4 9
```

### 样例 #2
#### 输入
```
2 1
0 1
1 2 3
```
#### 输出
```
4
```

### 样例 #3
#### 输入
```
5 8
928448202 994752369 906965437 942744902 907560126
2 5 975090662
1 2 908843627
1 5 969061140
3 4 964249326
2 3 957690728
2 4 942986477
4 5 948404113
1 3 988716403
```
#### 输出
```
2832044198 2824130042 4696218483 2805069468
```

### 综合分析与结论
- **思路对比**：大部分题解思路一致，将点权转化为边权处理，把从 $u$ 到 $v$ 的边权看作原边权加上 $v$ 的点权，再使用单源最短路算法求解。xixisuper 采用分层图最短路算法，将图分为两层处理点权。
- **算法要点**：多数使用 Dijkstra 算法，部分使用 BFS 或 SPFA。Dijkstra 算法利用优先队列优化，按路径权重从小到大处理节点；BFS 或 SPFA 则通过队列不断更新最短路径。
- **解决难点**：核心难点是处理点权，各题解通过将点权合并到边权，或采用分层图的方式解决。

### 评分较高的题解
- **qhr2023（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，详细解释了将点权转化为边权的过程，易于理解和实现。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int n, m, u, v, w, a[N];
struct edge { ll v, w; };
vector<edge> e[N];
long long dis[N];
bool vis[N];
struct node{
    ll u, dis;
    bool operator<(const node &b) const { return dis>b.dis; }
};
void dij () {
    memset(dis, 0x3f, sizeof dis);
    priority_queue<node> q;
    q.push({1, a[1]});
    while (q.size()) {
        ll u=q.top().u, d=q.top().dis;
        q.pop();
        if (vis[u])
            continue;
        vis[u]=1;
        dis[u]=d;
        for (auto i:e[u])
            if (dis[i.v]>i.w+d)
                dis[i.v]=i.w+d,
                q.push({i.v, dis[i.v]});
    }
}
int main(){
    cin >> n >> m;
    for (int i=1; i<=n; i++)
        cin >> a[i];
    while (m--) 
        cin >> u >> v >> w,
        e[u].push_back({v, w+a[v]}),
        e[v].push_back({u, w+a[u]});
    dij();
    for (int i=2; i<=n; i++)
        cout << dis[i] << ' ';
    return 0;
}
```
    - **核心实现思想**：将每条边的边权更新为原边权加上指向点的点权，然后使用优先队列优化的 Dijkstra 算法求解从顶点 1 到其他顶点的最短路径。
- **_zqh_（4星）**
    - **关键亮点**：详细解释了将点权合并到边权的思路，代码中包含了输入输出优化和组合数相关代码，功能丰富。
    - **核心代码**：
```cpp
void Bfs(int Stt) {
    memset(Dist, 0x3f, sizeof(Dist));
    queue<int> q;
    q.push(Stt);
    Dist[Stt] = val[Stt];
    while (q.size()) {
        int tmp = q.front();
        q.pop();
        vis[tmp] = true;
        for (pii x : G[tmp]) {
            if (Dist[x.first] > Dist[tmp] + val[x.first] + x.second) {
                Dist[x.first] = Dist[tmp] + val[x.first] + x.second;
                q.push(x.first);
            }
        }
    }
}
```
    - **核心实现思想**：使用 BFS 算法，在更新最短路径时将点权和边权一起考虑，不断更新每个顶点的最短路径。
- **stripe_python（4星）**
    - **关键亮点**：采用堆优化的 Dijkstra 算法，代码结构清晰，注释详细，便于理解。
    - **核心代码**：
```cpp
namespace Dijkstra {
    struct node {
        int to, dis;
        node() : to(0), dis(0) {}
        node(int x, int y) : to(x), dis(y) {}
        
        bool operator< (const node& other) const {
            return dis > other.dis;
        }
    };
    priority_queue<node> q;
    int dis[N];
    
    inline void dijkstra(int s) {
        memset(dis, 0x3f, sizeof(dis));
        dis[s] = a[s];   // 加上源点的点权
        q.emplace(s, a[s]);
        while (!q.empty()) {
            int u = q.top().to, d = q.top().dis;
            q.pop();
            if (d!= dis[u]) continue;
            for (int j = head[u]; j!= 0; j = edge[j].next) {
                int v = edge[j].to, w = edge[j].dis;
                if (dis[v] > dis[u] + a[v] + w) {
                    dis[v] = dis[u] + a[v] + w;
                    q.emplace(v, dis[v]);
                }
            }
        }
    }
}
```
    - **核心实现思想**：使用堆优化的 Dijkstra 算法，在更新最短路径时将点权和边权一起考虑，通过优先队列按路径权重从小到大处理节点。

### 最优关键思路或技巧
- **点权转化为边权**：将从 $u$ 到 $v$ 的边权看作原边权加上 $v$ 的点权，简化了点权的处理，将问题转化为普通的单源最短路问题。
- **优先队列优化**：使用优先队列优化 Dijkstra 算法，按路径权重从小到大处理节点，提高了算法效率。

### 拓展思路
- **同类型题**：涉及点权和边权的最短路问题，如一些地图导航问题，节点代表地点有权重，边代表路径也有权重，求最短路径。
- **类似算法套路**：分层图最短路，当遇到复杂的状态转移时，可以通过分层图将状态转移转化为图的边，从而使用最短路算法求解。

### 洛谷相似题目推荐
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：基础的单源最短路问题，可用于练习 Dijkstra 算法。
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：同样是单源最短路问题，难度稍低，适合初学者。
- [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)：涉及有向图的单源最短路和多源最短路问题，需要一定的思维转换。

### 个人心得摘录与总结
- **_zqh_**：提醒不要用标记数组，最开始赋初值时要将 $dst_1$ 赋值成 $pval_1$ 而不是 $0$，避免错误。
- **Cosine_Func**：提醒开 `long long`，无向图数组开够，初始化要给 $dis_1$ 赋值为 $a_1$，注意细节防止出错。
- **2c_s**：强调记得开 `long long`，把点权和边权一块算上，初始点也算，一定要标点，否则会超过时限，注重代码实现的细节。 

---
处理用时：63.74秒