# 题目信息

# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 说明/提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 样例 #1

### 输入

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4```

### 输出

```
5
-1
6
19
14
12```

# AI分析结果

### 题目中文重写
# 玛丽安与罗宾的约会

## 题目描述
在平凡的相遇中，喜悦如绽放的花朵般徐徐展开。

小别胜新婚。玛丽安在集市卖完了她的最后一件商品，与此同时，罗宾也在大橡树下结束了训练。他们迫不及待地想要见面，于是立刻出发。

交通网络用 $n$ 个顶点（编号从 $1$ 到 $n$）和 $m$ 条边来表示。第 $i$ 条边连接顶点 $u_i$ 和 $v_i$，通过这条边需要 $w_i$ 秒（所有的 $w_i$ 都是偶数）。玛丽安从顶点 $1$（集市）出发，罗宾从顶点 $n$（大橡树）出发。

此外，$n$ 个顶点中有 $h$ 个顶点各有一匹马。玛丽安和罗宾都是熟练的骑手，他们可以瞬间（即 $0$ 秒）骑上马匹。骑马时，通过边的时间会减半。一旦骑上了马，这匹马可以一直使用到行程结束。两人必须在顶点处见面（即不能在边上见面）。两人都可以选择在任何顶点等待。

输出玛丽安和罗宾最早可以见面的时间。如果顶点 $1$ 和顶点 $n$ 不连通，则输出 $-1$，表示约会取消。

## 说明/提示
在第一个测试用例中，玛丽安骑马从顶点 $1$ 到顶点 $2$，罗宾等待。
在第二个测试用例中，顶点 $1$ 和顶点 $3$ 不连通。
在第三个测试用例中，玛丽安和罗宾都前往顶点 $2$ 见面。
在第四个测试用例中，玛丽安不骑马前往顶点 $2$，在顶点 $2$ 骑上马匹，然后骑马前往顶点 $3$ 与罗宾见面。
在第五个测试用例中，玛丽安不骑马前往顶点 $2$，在顶点 $2$ 骑上马匹，然后骑马返回顶点 $1$，再前往顶点 $3$。罗宾等待。

## 样例 #1
### 输入
```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4
```

### 输出
```
5
-1
6
19
14
12
```

### 综合分析与结论
这些题解的核心思路都是使用分层图结合 Dijkstra 算法来解决问题。由于存在骑马和不骑马两种状态，所以将图分为两层，第一层是原图，第二层是边权减半的图，在有马的点处建立两层之间边权为 0 的连接边。然后分别从起点 1 和终点 n 跑 Dijkstra 算法，最后枚举相遇点，计算两人到达该点的最短时间，取最大值中的最小值作为答案。

不同题解在代码实现上略有差异，如建图方式（邻接表或邻接矩阵）、优先队列的使用、状态数组的定义等，但整体思路一致。解决的难点在于如何处理骑马状态下的边权变化，以及如何正确枚举相遇点并计算最短相遇时间。

### 题解评分与选择
- **thh_loser**：5 星。思路清晰，代码简洁，注释详细，对分层图和 Dijkstra 算法的实现都很标准。
- **WRT_Partisan**：4 星。代码结构清晰，有详细的注释，对算法的实现和多组数据的处理都很规范。
- **zengziqvan**：4 星。对分层图的解释较为详细，代码实现合理，时间复杂度分析准确。

### 所选题解
- **thh_loser**（5 星）
    - 关键亮点：思路清晰，代码简洁易懂，注释详细，标准的分层图 Dijkstra 实现。
    - 核心代码：
```c++
void dij(int s){
    for(int i=1;i<=n*2;i++){
        d[i]=1e13;
        vis[i]=0;
    }
    priority_queue<pair<int,int> >q;
    d[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int x=q.top().second;
        q.pop();
        if(vis[x])continue;
        vis[x]=1;
        for(int i=fir[x];i;i=ne[i]){
            int e=to[i];
            if(d[e]>d[x]+w[i]){
                d[e]=d[x]+w[i];
                if(!vis[e])q.push(make_pair(-d[e],e));
            }
        }
    }	
}
```
    - 核心实现思想：使用优先队列优化的 Dijkstra 算法，从起点 s 开始，更新到每个点的最短距离。

- **WRT_Partisan**（4 星）
    - 关键亮点：代码结构清晰，有详细的注释，对算法的实现和多组数据的处理都很规范。
    - 核心代码：
```cpp
while (!q.empty())
{
    int t = q.top().x;
    q.pop();
    if (book[t])
        continue;
    book[t] = 1;
    for (auto &i : mp[t])
    {
        if (book[i.x] == 0 && dis1[t] + i.k < dis1[i.x])
        {
            dis1[i.x] = dis1[t] + i.k;
            q.push({dis1[i.x], i.x});
        }
    }
}
```
    - 核心实现思想：使用优先队列优化的 Dijkstra 算法，从起点开始，遍历邻接表更新最短距离。

- **zengziqvan**（4 星）
    - 关键亮点：对分层图的解释较为详细，代码实现合理，时间复杂度分析准确。
    - 核心代码：
```c++
void Dijkstra1() {
    FOR(i,1,n<<1) dis[i]=1e18,vis[i]=0;
    dis[1]=0;
    priority_queue<pair<int,int>>q;
    q.push({0,1});
    while(q.size()) {
        int x=q.top().se;q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(pair<int,int>o:e[x]) {
            int y=o.fr,z=o.se;
            if(dis[y]>dis[x]+z) {
                dis[y]=dis[x]+z;
                q.push({-dis[y],y});
            }
        }
    }
}
```
    - 核心实现思想：使用优先队列优化的 Dijkstra 算法，从起点 1 开始更新最短距离。

### 最优关键思路或技巧
- **分层图思想**：将图分为两层，分别表示不骑马和骑马的状态，通过在有马的点建立两层之间的连接边，将骑马状态的变化转化为图的结构变化，方便使用最短路算法求解。
- **Dijkstra 算法**：由于边权非负，使用优先队列优化的 Dijkstra 算法可以高效地求解最短路径。

### 可拓展之处
同类型题或类似算法套路：
- 其他涉及状态变化的最短路问题，如带有魔法、技能等特殊状态，可通过分层图将不同状态表示为不同层的图，再使用最短路算法求解。
- 多源最短路问题，可通过多次调用 Dijkstra 算法或使用 Floyd 算法求解。

### 洛谷推荐题目
- [P4568 [JLOI2011]飞行路线](https://www.luogu.com.cn/problem/P4568)：分层图最短路经典题目，有 k 次免费机会，可将图分为 k+1 层。
- [P2939 [USACO09FEB]Revamping Trails G](https://www.luogu.com.cn/problem/P2939)：类似飞行路线，有 k 条边可以免费，使用分层图求解。
- [P1073 [NOIP2009 提高组] 最优贸易](https://www.luogu.com.cn/problem/P1073)：可通过分层图处理买卖状态，使用最短路算法求解最大利润。

### 个人心得摘录与总结
- **zengziqvan**：赛时 `long long` 没开全导致赛后被 hack，提醒我们在处理可能出现大数值的问题时，要注意数据类型的选择。

---
处理用时：46.31秒