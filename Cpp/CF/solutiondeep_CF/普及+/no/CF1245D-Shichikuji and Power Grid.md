# 题目信息

# Shichikuji and Power Grid

## 题目描述

Shichikuji is the new resident deity of the South Black Snail Temple. Her first job is as follows:

There are $ n $ new cities located in Prefecture X. Cities are numbered from $ 1 $ to $ n $ . City $ i $ is located $ x_i $ km North of the shrine and $ y_i $ km East of the shrine. It is possible that $ (x_i, y_i) = (x_j, y_j) $ even when $ i \ne j $ .

Shichikuji must provide electricity to each city either by building a power station in that city, or by making a connection between that city and another one that already has electricity. So the City has electricity if it has a power station in it or it is connected to a City which has electricity by a direct connection or via a chain of connections.

- Building a power station in City $ i $ will cost $ c_i $ yen;
- Making a connection between City $ i $ and City $ j $ will cost $ k_i + k_j $ yen per km of wire used for the connection. However, wires can only go the cardinal directions (North, South, East, West). Wires can cross each other. Each wire must have both of its endpoints in some cities. If City $ i $ and City $ j $ are connected by a wire, the wire will go through any shortest path from City $ i $ to City $ j $ . Thus, the length of the wire if City $ i $ and City $ j $ are connected is $ |x_i - x_j| + |y_i - y_j| $ km.

Shichikuji wants to do this job spending as little money as possible, since according to her, there isn't really anything else in the world other than money. However, she died when she was only in fifth grade so she is not smart enough for this. And thus, the new resident deity asks for your help.

And so, you have to provide Shichikuji with the following information: minimum amount of yen needed to provide electricity to all cities, the cities in which power stations will be built, and the connections to be made.

If there are multiple ways to choose the cities and the connections to obtain the construction of minimum price, then print any of them.

## 说明/提示

For the answers given in the samples, refer to the following diagrams (cities with power stations are colored green, other cities are colored blue, and wires are colored red):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1245D/251d50cda099f4e4be2994b6b01574cc32a17cd3.png)

For the first example, the cost of building power stations in all cities is $ 3 + 2 + 3 = 8 $ . It can be shown that no configuration costs less than 8 yen.

For the second example, the cost of building a power station in City 2 is 2. The cost of connecting City 1 and City 2 is $ 2 \cdot (3 + 2) = 10 $ . The cost of connecting City 2 and City 3 is $ 3 \cdot (2 + 3) = 15 $ . Thus the total cost is $ 2 + 10 + 15 = 27 $ . It can be shown that no configuration costs less than 27 yen.

## 样例 #1

### 输入

```
3
2 3
1 1
3 2
3 2 3
3 2 3
```

### 输出

```
8
3
1 2 3 
0
```

## 样例 #2

### 输入

```
3
2 1
1 2
3 3
23 2 23
3 2 3
```

### 输出

```
27
1
2 
2
1 2
2 3
```

# AI分析结果

### 题目翻译
Shichikuji 是南黑蜗牛神庙的新主神。她的第一项工作如下：

在 X 县有 $n$ 个新城市。城市编号从 $1$ 到 $n$。城市 $i$ 位于神庙以北 $x_i$ 公里和以东 $y_i$ 公里处。即使 $i \ne j$，也有可能 $(x_i, y_i) = (x_j, y_j)$。

Shichikuji 必须为每个城市供电，要么在该城市建造一个发电站，要么在该城市与另一个已经通电的城市之间建立连接。因此，如果一个城市有发电站，或者通过直接连接或一系列连接与一个通电的城市相连，那么这个城市就有电。
- 在城市 $i$ 建造一个发电站将花费 $c_i$ 日元；
- 在城市 $i$ 和城市 $j$ 之间建立连接，每公里电线将花费 $k_i + k_j$ 日元。然而，电线只能沿基本方向（北、南、东、西）铺设。电线可以相互交叉。每根电线的两端都必须位于某个城市。如果城市 $i$ 和城市 $j$ 通过电线连接，电线将沿着从城市 $i$ 到城市 $j$ 的任何最短路径铺设。因此，如果城市 $i$ 和城市 $j$ 相连，电线的长度为 $|x_i - x_j| + |y_i - y_j|$ 公里。

Shichikuji 希望尽可能少地花钱来完成这项工作，因为在她看来，世界上除了钱没有别的东西。然而，她在五年级时就去世了，所以她不够聪明来完成这项工作。因此，新主神向你寻求帮助。

因此，你必须向 Shichikuji 提供以下信息：为所有城市供电所需的最少日元数、将建造发电站的城市以及要建立的连接。

如果有多种选择城市和连接的方式来实现最低成本的建设，那么打印其中任何一种即可。

### 算法分类
图论

### 综合分析与结论
这几道题解都是围绕图论中的最小生成树算法来解决问题。因为题目中有点权和边权，关键在于如何将点权转化为边权，从而利用最小生成树算法求解最小花费。
- **思路对比**：
    - yi_fan0305、wheneveright 和寒鸽儿 三位作者都是通过建立一个虚点，将点权转化为虚点到各点的边权，然后使用 prim 算法求最小生成树。
    - luan341502 作者则是采用 kruskal 算法，先在每个点建发电站，再根据边权和连通块内最小点权的关系判断是否连接电缆。
- **算法要点**：
    - prim 算法适用于稠密图，时间复杂度为 $O(N^2)$。
    - kruskal 算法需要先对边排序，时间复杂度为 $O(n^2\log n^2)$。
- **解决难点**：
    - 如何将点权转化为边权，是解决本题的关键。
    - 统计答案时，需要区分哪些点建发电站，哪些点之间有连接。

### 所选题解
- **yi_fan0305（4星）**：
    - **关键亮点**：思路清晰，代码注释详细，通过记录每条边的起始点和终点，方便判断是否建发电站。
- **wheneveright（4星）**：
    - **关键亮点**：对 prim 算法的复杂度进行了分析，选择 prim 算法是因为其在稠密图中的优势，代码简洁。
- **luan341502（4星）**：
    - **关键亮点**：采用不同的思路，使用 kruskal 算法，通过比较连通块内最小点权和边权的大小来判断是否连接电缆。

### 重点代码
#### yi_fan0305 的 prim 算法实现
```cpp
void prim(int s) {
    q.push({0, {s, 0}});
    for (int i = 0; i <= n; ++ i) {
        dis[i] = 1e18;
    }
    dis[s] = 0;
    while (! q.empty()) {
        plii it = q.top();
        q.pop();
        int u = it.second.first;
        if (vis[u]) continue;
        ++ cnt;
        tot += dis[u];
        vis[u] = 1;
        ans[cnt] = edge{it.second.second, it.second.first, dis[u]};
        if (it.second.second == 0) {
            ok[u] = 1;
            ++ cot;
        }
        if (cnt >= n + 1) return ;
        for (auto it : son[u]) {
            int v = it.first;
            ll w = it.second;
            if (dis[v] > w) {
                dis[v] = w;
                q.push({dis[v], {v, u}});
            }
        }
    }
}
```
核心思想：从虚点开始，不断选择距离当前生成树最近的点加入树中，更新距离数组和答案数组，同时判断是否建发电站。

#### wheneveright 的 prim 算法实现
```cpp
for (register int t = 1; t <= N; t++) {
    register int minn = 2147483640, id;
    for (register int i = 1; i <= N; i++)
        if (!vis[i] && dis[i] < minn) minn = dis[i], id = i;
    vis[id] = true; res += minn; if (las[id] == 0) bd++;
    for (register int i = 1; i <= N; i++)
        if (!vis[i] && dis[i] > (K[i] + K[id]) * (abs (X[id] - X[i]) + abs (Y[id] - Y[i])))
            dis[i] = (K[i] + K[id]) * (abs (X[id] - X[i]) + abs (Y[id] - Y[i])), las[i] = id;
}
```
核心思想：每次选择距离当前生成树最近的未访问点加入树中，更新距离数组和记录上一次更新该点的点，同时统计建发电站的点的数量。

#### luan341502 的 kruskal 算法实现
```cpp
sort(e+1,e+tot+1,cmp);
for(int i=1;i<=tot;i++){
    if(find(e[i].u)==find(e[i].v)) continue;
    int fu=find_link(e[i].u),fv=find_link(e[i].v);
    if(c[fu]<c[fv]) swap(fu,fv);
    if(c[fu]>=e[i].w){
        ans+=e[i].w-c[fu],link[fu]=fv;
        v_edge.push_back(make_pair(e[i].u,e[i].v));
    }
    fa[fu]=fv;
}
```
核心思想：先对边按边权从小到大排序，然后依次枚举边，若边连接的两个点不在同一连通块中，比较连通块内最小点权和边权的大小，若边权小于等于最大的最小点权，则连接电缆，更新答案和并查集。

### 关键思路或技巧
- 建立虚点，将点权转化为边权，是解决本题的关键技巧，使得问题可以转化为最小生成树问题。
- 在统计答案时，通过记录边的信息或上一次更新点的信息，方便判断哪些点建发电站，哪些点之间有连接。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及点权和边权的最小生成树问题，都可以考虑通过建立虚点将点权转化为边权。
- 对于不同的图，根据图的稠密程度选择合适的最小生成树算法，如稠密图选择 prim 算法，稀疏图选择 kruskal 算法。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)

### 个人心得
- 寒鸽儿：考场上当 Dijkstra 写了，说明在考试时可能会因为紧张或思路不清晰而选错算法，需要在平时练习中加强对不同算法的理解和区分。
- wheneveright：提到“十年 OI 一场空，不开 longlong 见祖宗”，强调了在处理可能出现大数值的问题时，要注意数据类型的选择，避免因数据溢出而导致错误。

---
处理用时：61.24秒