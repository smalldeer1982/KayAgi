# 题目信息

# Weak Memory

## 题目描述

Zart PMP is qualified for ICPC World Finals in Harbin, China. After team excursion to Sun Island Park for snow sculpture art exposition, PMP should get back to buses before they leave. But the park is really big and he does not know how to find them.

The park has $ n $ intersections numbered $ 1 $ through $ n $ . There are $ m $ bidirectional roads that connect some pairs of these intersections. At $ k $ intersections, ICPC volunteers are helping the teams and showing them the way to their destinations. Locations of volunteers are fixed and distinct.

When PMP asks a volunteer the way to bus station, he/she can tell him the whole path. But the park is fully covered with ice and snow and everywhere looks almost the same. So PMP can only memorize at most $ q $ intersections after each question (excluding the intersection they are currently standing). He always tells volunteers about his weak memory and if there is no direct path of length (in number of roads) at most $ q $ that leads to bus station, the volunteer will guide PMP to another volunteer (who is at most $ q $ intersections away, of course). ICPC volunteers know the area very well and always tell PMP the best way. So if there exists a way to bus stations, PMP will definitely find it.

PMP's initial location is intersection $ s $ and the buses are at intersection $ t $ . There will always be a volunteer at intersection $ s $ . Your job is to find out the minimum $ q $ which guarantees that PMP can find the buses.

## 说明/提示

The first sample is illustrated below. Blue intersections are where volunteers are located. If PMP goes in the path of dashed line, it can reach the buses with $ q=3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF187C/c6f84f7d8e65e3d0b7f7fc6b41fb9b6c090dc4ed.png)In the second sample, PMP uses intersection 6 as an intermediate intersection, thus the answer is 3.

## 样例 #1

### 输入

```
6 6 3
1 3 6
1 2
2 3
4 2
5 6
4 5
3 4
1 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 5 3
1 5 6
1 2
2 3
3 4
4 5
6 3
1 5
```

### 输出

```
3
```

# AI分析结果

### 题目重写
# 弱记忆

## 题目描述
Zart PMP 获得了在中国哈尔滨举行的 ICPC 世界总决赛的参赛资格。在团队前往太阳岛公园参观雪雕艺术博览会后，PMP 需要在大巴离开前回到车上。但公园非常大，他不知道如何找到大巴。

公园有 $n$ 个编号从 $1$ 到 $n$ 的十字路口。有 $m$ 条双向道路连接这些十字路口中的一些对。在 $k$ 个十字路口，有 ICPC 志愿者帮助参赛队伍并为他们指明前往目的地的路。志愿者的位置是固定且不同的。

当 PMP 向志愿者询问去公交车站的路时，志愿者可以告诉他完整的路径。但是公园完全被冰雪覆盖，到处看起来几乎一样。所以 PMP 在每次询问后最多只能记住 $q$ 个十字路口（不包括他们当前所在的十字路口）。他总是告诉志愿者他记忆力不好，如果没有长度（道路数量）最多为 $q$ 的直接路径通向公交车站，志愿者会将 PMP 引导到另一个志愿者（当然，这个志愿者距离最多为 $q$ 个十字路口）。ICPC 志愿者非常了解这个区域，总是告诉 PMP 最佳路线。所以如果存在去公交车站的路，PMP 肯定能找到。

PMP 的初始位置是十字路口 $s$，公交车在十字路口 $t$。十字路口 $s$ 总会有一个志愿者。你的任务是找出保证 PMP 能找到公交车的最小的 $q$。

## 说明/提示
第一个样例如下图所示。蓝色的十字路口是志愿者所在的位置。如果 PMP 沿着虚线的路径走，在 $q = 3$ 时他可以到达公交车处：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF187C/c6f84f7d8e65e3d0b7f7fc6b41fb9b6c090dc4ed.png)
在第二个样例中，PMP 使用十字路口 6 作为中间十字路口，因此答案是 3。

## 样例 #1
### 输入
```
6 6 3
1 3 6
1 2
2 3
4 2
5 6
4 5
3 4
1 6
```
### 输出
```
3
```
## 样例 #2
### 输入
```
6 5 3
1 5 6
1 2
2 3
3 4
4 5
6 3
1 5
```
### 输出
```
3
```
### 算法分类
二分

### 综合分析与结论
这些题解主要围绕如何找到保证 PMP 能从起点 $s$ 到达终点 $t$ 的最小 $q$ 值展开。多数题解采用二分答案的方式，将问题转化为可行性判断问题。难点在于处理特殊点（志愿者所在点）对路径查找的影响。不同题解在处理特殊点、更新路径以及判断可行性的具体实现方式上有所不同。

### 所选的题解
#### 作者：Sakuya_maid (5星)
- **关键亮点**：采用二分 + 并查集 + bfs 的做法，复杂度稳定在 $n \log n$ 。通过二分最小能量（即 $q$ 值），利用并查集存储能在二分值范围内更新到的点所形成的连通块，bfs 用于遍历更新。
- **个人心得**：指出远古场用 dij 重复入队更新点的做法能过是因为数据水，强调自己做法的稳定性。
```c
    auto check = [&](int x)->bool{
        vector<int>fa(n + 1), dist(n + 1), ss(n + 1);
        queue<int>q;
        auto find = [&](auto self, int x) -> int{
            return fa[x] == x? x : fa[x] = self(self, fa[x]);
        };

        auto merge = [&](int x, int y)->void{
            if(find(find, x)!= find(find, y)){
                fa[find(find, x)] = find(find, y);
            }
        };

        for(int i = 1; i <= n; ++ i){
            fa[i] = i;
            if(vis[i])q.push(i), ss[i] = i;
        }

        while(q.size()){
            auto u = q.front();
            q.pop();
            for(auto v : g[u]){
                if(!ss[v]){
                    ss[v] = ss[u];
                    dist[v] = dist[u] + 1;
                    merge(v, u);
                    if(dist[v] < x)q.push(v);
                }else{
                    if(dist[v] + dist[u] + 1 <= x){
                        merge(u, v);
                    }
                }
            }
        }

        return  find(find, s) == find(find, t);
    };
```
核心实现思想：check 函数用于判断二分的 $x$ 值是否可行。初始化并查集和相关数组，通过 bfs 遍历图，在遍历过程中根据条件更新并查集，最后判断起点和终点是否在同一连通块。

#### 作者：YCS_GG (4星)
- **关键亮点**：二分答案后，通过 bfs 来判断可行性。利用优先队列维护当前点的最大能量值，在 bfs 过程中，遇到特殊点将能量补满，更新每个点能达到的最大能量值，判断能否到达终点。
```cpp
bool check(int x) {
    while (!q.empty())
        q.pop();
    memset(dis, -1, sizeof(dis));
    dis[s] = x;
    q.push({s, x});
    while (!q.empty()) {
        Data now = q.top();
        q.pop();
        if (now.w == 0) {
            continue;
        }
        for (int i = head[now.x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            int w = now.w - 1;
            if (v == t)
                return true;
            if (pos[v]) {
                w = x;
            }
            if (dis[v] < w) {
                dis[v] = w;
                q.push({v, w});
            }
        }
    }
    return false;
}
```
核心实现思想：check 函数判断二分的 $x$ 是否可行。初始化队列和距离数组，从起点开始 bfs，每次取出队首元素，根据是否为特殊点更新能量值，若能更新则入队，判断是否能到达终点。

#### 作者：ZLCT (4星)
- **关键亮点**：提出多种方法。法 1 二分答案后用可重复入队的 bfs（类似 spfa）判断可行性，先求出每个点到最近特殊点的距离，在 bfs 中考虑此距离更新到每个点的最小油量；法 2 以终点和每个特殊点为起点扩展连通块，直到起点和终点在同一连通块；法 3 结合前两种方法，先排序再扩展连通块。
```cpp
// 法1代码
bool check(int x){
    queue<int>q;
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[S]=0;
    q.push(S);
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        if(d[u]+d1[u]<=x)d[u]=min(d[u],d1[u]);
        if(d[u]==x)continue;
        for(int v:G[u]){
            if(d[v]>d[u]+1){
                d[v]=d[u]+1;
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
    return d[T]<=n;
}
```
核心实现思想：check 函数判断二分的 $x$ 是否可行。初始化队列和距离数组，从起点 bfs，每次取出队首元素，根据到最近特殊点的距离更新当前点距离，若当前点距离达到 $x$ 则停止扩展，判断是否能到达终点。

### 最优关键思路或技巧
二分答案将求最小值问题转化为可行性判断问题，降低问题复杂度。结合并查集、bfs 等数据结构和算法，有效处理特殊点对路径查找的影响，优化时间复杂度。

### 同类型题或类似算法套路
此类题目通常涉及在图结构上寻找满足某种条件的最小参数值。常见套路为二分参数值，然后通过搜索算法（如 bfs、dfs）或其他图论算法判断可行性。

### 洛谷题目推荐
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：同样是二分答案，通过判断可行性来求解最优值，涉及在序列上的操作。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分答案，结合贪心思想解决在公路上设置路标的问题。
- [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)：二分查找满足条件的最小距离，通过判断可行性来确定答案。 

---
处理用时：73.36秒