# 题目信息

# Reducing Delivery Cost

## 题目描述

You are a mayor of Berlyatov. There are $ n $ districts and $ m $ two-way roads between them. The $ i $ -th road connects districts $ x_i $ and $ y_i $ . The cost of travelling along this road is $ w_i $ . There is some path between each pair of districts, so the city is connected.

There are $ k $ delivery routes in Berlyatov. The $ i $ -th route is going from the district $ a_i $ to the district $ b_i $ . There is one courier on each route and the courier will always choose the cheapest (minimum by total cost) path from the district $ a_i $ to the district $ b_i $ to deliver products.

The route can go from the district to itself, some couriers routes can coincide (and you have to count them independently).

You can make at most one road to have cost zero (i.e. you choose at most one road and change its cost with $ 0 $ ).

Let $ d(x, y) $ be the cheapest cost of travel between districts $ x $ and $ y $ .

Your task is to find the minimum total courier routes cost you can achieve, if you optimally select the some road and change its cost with $ 0 $ . In other words, you have to find the minimum possible value of $ \sum\limits_{i = 1}^{k} d(a_i, b_i) $ after applying the operation described above optimally.

## 说明/提示

The picture corresponding to the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/458c58c5f1fe2e61828172bc475f01c796e3199a.png)

There, you can choose either the road $ (2, 4) $ or the road $ (4, 6) $ . Both options lead to the total cost $ 22 $ .

The picture corresponding to the second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/b1ea600359edb25eb81785c2a8e73df295a9c0a5.png)

There, you can choose the road $ (3, 4) $ . This leads to the total cost $ 13 $ .

## 样例 #1

### 输入

```
6 5 2
1 2 5
2 3 7
2 4 4
4 5 2
4 6 8
1 6
5 3```

### 输出

```
22```

## 样例 #2

### 输入

```
5 5 4
1 2 5
2 3 4
1 4 3
4 3 7
3 5 2
1 5
1 3
3 3
1 5```

### 输出

```
13```

# AI分析结果

### 题目内容翻译
# 降低配送成本

## 题目描述
你是贝利亚托夫市的市长。该市有 $n$ 个行政区和 $m$ 条连接这些行政区的双向道路。第 $i$ 条道路连接行政区 $x_i$ 和 $y_i$，沿着这条道路行驶的成本是 $w_i$。任意两个行政区之间都存在路径，因此城市是连通的。

贝利亚托夫市有 $k$ 条配送路线。第 $i$ 条路线是从行政区 $a_i$ 到行政区 $b_i$。每条路线上都有一名快递员，快递员总是会选择从行政区 $a_i$ 到行政区 $b_i$ 的最便宜（总成本最小）的路径来配送货物。

路线可以从一个行政区到其自身，某些快递员的路线可能会重合（并且你必须独立计算它们）。

你最多可以将一条道路的成本设为 $0$（即你最多选择一条道路并将其成本改为 $0$）。

设 $d(x, y)$ 为行政区 $x$ 和 $y$ 之间的最便宜的行驶成本。

你的任务是找出，如果你最优地选择某条道路并将其成本改为 $0$，你能实现的最小总快递路线成本。换句话说，你必须找出在最优地应用上述操作后，$\sum\limits_{i = 1}^{k} d(a_i, b_i)$ 的最小可能值。

## 说明/提示
对应第一个样例的图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/458c58c5f1fe2e61828172bc475f01c796e3199a.png)

在这个例子中，你可以选择道路 $(2, 4)$ 或道路 $(4, 6)$。这两种选择都会使总成本为 $22$。

对应第二个样例的图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/b1ea600359edb25eb81785c2a8e73df295a9c0a5.png)

在这个例子中，你可以选择道路 $(3, 4)$。这会使总成本为 $13$。

## 样例 #1
### 输入
```
6 5 2
1 2 5
2 3 7
2 4 4
4 5 2
4 6 8
1 6
5 3
```
### 输出
```
22
```

## 样例 #2
### 输入
```
5 5 4
1 2 5
2 3 4
1 4 3
4 3 7
3 5 2
1 5
1 3
3 3
1 5
```
### 输出
```
13
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先通过对每个顶点跑一遍 Dijkstra 算法，求出任意两点间的最短路。然后枚举每一条边，将其边权置为 $0$，计算此时所有配送路线的总费用，取最小值作为最终结果。在计算经过边权为 $0$ 的边的最短路时，由于是无向图，需要考虑经过这条边的顶点的先后顺序。

各题解的主要区别在于代码实现风格和细节处理上，但整体思路和算法要点基本一致。难点在于理解如何计算经过某条边的最短路，以及处理无向图的情况。

### 所选题解
- **vectorwyx（4星）**
    - **关键亮点**：思路清晰，对核心思路的解释详细，代码注释丰富，易于理解。
    - **个人心得**：无

### 重点代码
```cpp
// 计算从起点 s 出发的单源最短路
void dij(int s){
    ++ti;
    dis[s][s]=0;
    q.push((Node){s,0});
    fo(i,1,n){
        while(!q.empty()&&d[q.top().num]==ti) q.pop();
        if(q.empty()) break;
        int x=q.top().num;q.pop();d[x]=ti;
        for(int j=head[x];j;j=e[j].next){
            int p=e[j].to;
            if(d[p]==ti) continue;
            if(dis[s][p]>dis[s][x]+e[j].val){
                dis[s][p]=dis[s][x]+e[j].val;
                q.push((Node){p,dis[s][p]}); 
            }
        }
    }
    while(!q.empty()) q.pop();
}

// 主函数
int main(){
    memset(dis,0x3f,sizeof dis);
    n=read(),m=read(),k=read();
    fo(i,1,m){
        int x=read(),y=read(),v=read();
        connect(x,y,v);
        connect(y,x,v);
    }
    int ans=0;
    fo(i,1,n) dij(i);
    fo(i,1,k){
        a[i]=read();
        b[i]=read();
        ans+=dis[a[i]][b[i]];
    }
    fo(i,1,n){
        for(int j=head[i];j;j=e[j].next){
            int p=e[j].to;
            int sum=0;
            fo(w,1,k){
                // 处理无向图，考虑经过边的顶点先后顺序
                int yrztxdy=min(dis[a[w]][i]+dis[p][b[w]],dis[a[w]][p]+dis[i][b[w]]);
                if(yrztxdy<=dis[a[w]][b[w]]) sum+=yrztxdy;
                else sum+=dis[a[w]][b[w]];
            }
            ans=min(ans,sum);
        }
    }
    cout<<ans;
    return 0;
} 
```
**核心实现思想**：先初始化距离数组，然后构建图。对每个顶点跑一遍 Dijkstra 算法，求出任意两点间的最短路。接着读取配送路线，计算初始的总费用。最后枚举每一条边，将其边权置为 $0$，重新计算所有配送路线的总费用，取最小值作为最终结果。

### 关键思路或技巧
- 使用 Dijkstra 算法预处理任意两点间的最短路，时间复杂度为 $O(n^2\log{n})$。
- 枚举每一条边，将其边权置为 $0$，计算经过该边的最短路，由于是无向图，需要考虑经过这条边的顶点的先后顺序。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及图的最短路问题，如多源最短路（Floyd 算法）、有负权边的最短路（Bellman - Ford 算法、SPFA 算法）。
- 图的优化问题，如最小生成树（Prim 算法、Kruskal 算法）。

### 推荐题目
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P2865 [USACO06NOV]Roadblocks G](https://www.luogu.com.cn/problem/P2865)

### 个人心得总结
部分题解提到了错误的贪心思路，即将最短路上经过次数乘以边权最大的边的边权置为 $0$，但这种思路是错误的，因为删边前后的最短路径不一定重合，这提醒我们在解题时要仔细思考，不能盲目使用贪心策略。 

---
处理用时：53.22秒