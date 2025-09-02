# 题目信息

# [ABC254E] Small d and k

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_e

$ N $ 頂点 $ M $ 辺の単純無向グラフがあり、各頂点には $ 1,\ldots,N $ と番号が付けられています。 $ i=1,\ldots,M $ に対し、 $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結びます。また、**各頂点の次数は $ 3 $ 以下です。**

$ i=1,\ldots,Q $ に対し、次のクエリに答えてください。

- 頂点 $ x_i $ との距離が $ k_i $ 以下であるような頂点の番号の総和を求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1.5\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min\ (\frac{N(N-1)}{2},\frac{3N}{2}) $
- $ 1\ \leq\ a_i\ \lt\ b_i\ \leq\ N $
- $ i\neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- 与えられるグラフの各頂点の次数は $ 3 $ 以下
- $ 1\ \leq\ Q\ \leq\ 1.5\ \times\ 10^5 $
- $ 1\ \leq\ x_i\ \leq\ N $
- $ 0\ \leq\ k_i\ \leq\ 3 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは、頂点 $ 1 $ との距離が $ 1 $ 以下であるような頂点は頂点 $ 1 $ のみなので $ 1 $ が答えです。 $ 2 $ 番目のクエリでは、頂点 $ 2 $ との距離が $ 2 $ 以下であるような頂点は頂点 $ 2,3,4,5,6 $ なのでこれらの総和の $ 20 $ が答えになります。 $ 3 $ 番目以降のクエリも同様にして答えを求められます。

## 样例 #1

### 输入

```
6 5
2 3
3 4
3 5
5 6
2 6
7
1 1
2 2
2 0
2 3
4 1
6 0
4 3```

### 输出

```
1
20
2
20
7
6
20```

# AI分析结果

### 题目翻译
有一个包含 $N$ 个顶点和 $M$ 条边的简单无向图，每个顶点的编号为 $1,\ldots,N$。对于 $i = 1,\ldots,M$，第 $i$ 条边连接顶点 $a_i$ 和顶点 $b_i$。此外，**每个顶点的度数不超过 3**。

对于 $i = 1,\ldots,Q$，请回答以下查询：
- 求出与顶点 $x_i$ 的距离不超过 $k_i$ 的顶点的编号总和。

### 综合分析与结论
- **思路**：所有题解均采用广度优先搜索（BFS）来解决问题。依据题目中每个顶点度数不超过 3 以及 $k$ 最大为 3 的条件，可知距离顶点 $x$ 不超过 $k$ 的顶点数量较少，直接使用 BFS 可以满足时间复杂度要求。
- **算法要点**：构建图结构（使用邻接表，如 `vector` 或链式前向星），每次查询时从顶点 $x$ 开始 BFS，使用 `vis` 数组标记已访问的顶点，使用距离数组记录各顶点到 $x$ 的距离，当距离超过 $k$ 时停止搜索，累加符合条件的顶点编号。
- **解决难点**：多次查询时需要注意清空标记数组和距离数组，部分题解通过记录访问过的顶点或使用额外数组记录最后一次更新最短路的询问编号来优化清空操作，避免使用 `memset` 带来的时间开销。

### 所选题解
- **zhujiangyuan（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `vector` 存图，码量少，注释详细，易于理解。
    - **核心代码**：
```cpp
void bfs()
{
    ans=0;
    memset(vis,0,sizeof(vis));
    queue<int>q;
    q.push(x);
    d[x]=0;
    vis[x]=1;
    while(q.size())
    {
        int y=q.front();q.pop();
        if(d[y]>k) break;
        ans+=y;
        for(auto i:G[y])
        {
            if(!vis[i]) vis[i]=1,q.push(i),d[i]=d[y]+1;
        }
    }
}
```
- **fuwei123（4星）**
    - **关键亮点**：考虑到复杂度优化，指出 `vis` 数组清空不能使用 `memset`，通过记录访问过的顶点来只清空这些点，保证复杂度。
    - **核心代码**：
```cpp
int bfs(int x, int k){
    vis[x] = 1;
    q.push({0, x});
    a[cnt = 1] = x;
    int res = 0;
    while(!q.empty()){
        node fr = q.front();
        q.pop();
        int u = fr.pos, d = fr.now;
        if(d > k)break;
        res += u;
        if(d == k)continue;
        for(int i = 0;i < G[u].size();i++){
            int v = G[u][i];
            if(vis[v])continue;
            q.push({d + 1, v});
            vis[v] = 1;
            a[++cnt] = v;
        }
    }
    for(int i = 1;i <= cnt;i++)vis[a[i]] = 0;
    return res;
}
```
- **chengning0909（4星）**
    - **关键亮点**：使用额外数组 `mmax` 记录最后一次更新最短路是在第几次询问，避免每次都清空标记数组，优化时间复杂度。
    - **核心代码**：
```cpp
long long Solve(int x, int k, int id) {
    long long ans = x;
    queue<int> que;
    que.push(x), mmax[x] = id, d[x] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (d[u] >= k) {
            break;
        }
        for (int v : g[u]) {
            if (mmax[v] < id) {
                mmax[v] = id, que.push(v), ans += v, d[v] = d[u] + 1;
            }
        }
    }
    return ans;
}
```

### 最优关键思路或技巧
- **数据结构**：使用邻接表（`vector` 或链式前向星）存储图，节省空间且便于遍历。
- **算法优化**：避免每次使用 `memset` 清空标记数组，可通过记录访问过的顶点或使用额外数组记录最后一次更新最短路的询问编号来优化。
- **思维方式**：根据题目中顶点度数和 $k$ 的范围较小的条件，确定可以使用 BFS 暴力搜索。

### 可拓展之处
同类型题或类似算法套路：对于图的遍历问题，若图的规模较大且有一定限制条件（如顶点度数、距离限制等），可考虑使用 BFS 或 DFS 进行搜索，同时注意优化标记数组的清空操作，避免不必要的时间开销。

### 推荐洛谷题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及图的 BFS 搜索，通过电梯的上下移动来寻找最短路径。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：经典的迷宫搜索问题，可使用 BFS 或 DFS 求解。
- [P2853 [USACO06DEC]Cow Picnic S](https://www.luogu.com.cn/problem/P2853)：图的遍历问题，需要计算从多个起点出发能到达的顶点数量。

### 个人心得摘录与总结
- **Redamancy_Lydic**：提到判断是否访问过的数组 `vis` 标记最好写在前面，否则可能会漏掉初始点，这是在调试过程中发现的问题，提醒我们在实现 BFS 时要注意标记的时机。

---
处理用时：37.73秒