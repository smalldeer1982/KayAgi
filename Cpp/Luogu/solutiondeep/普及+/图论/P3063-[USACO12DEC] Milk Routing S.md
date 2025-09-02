# 题目信息

# [USACO12DEC] Milk Routing S

## 题目描述

Farmer John's farm has an outdated network of M pipes (1 <= M <= 500) for pumping milk from the barn to his milk storage tank.  He wants to remove and update most of these over the next year, but he wants to leave exactly one path worth of pipes intact, so that he can still pump milk from the barn to the storage tank.

The pipe network is described by N junction points (1 <= N <= 500), each of which can serve as the endpoint of a set of pipes.  Junction point 1 is the barn, and junction point N is the storage tank.  Each of the M bi-directional pipes runs between a pair of junction points, and has an associated latency (the amount of time it takes milk to reach one end of the pipe from the other) and capacity (the amount of milk per unit time that can be pumped through the pipe in steady state).  Multiple pipes can connect between the same pair of junction points.

For a path of pipes connecting from the barn to the tank, the latency of the path is the sum of the latencies of the pipes along the path, and the capacity of the path is the minimum of the capacities of the pipes along the path (since this is the "bottleneck" constraining the overall rate at which milk can be pumped through the path).  If FJ wants to send a total of X units of milk through a path of pipes with latency L and capacity C, the time this takes is therefore L + X/C.

Given the structure of FJ's pipe network, please help him select a single path from the barn to the storage tank that will allow him to pump X units of milk in a minimum amount of total time.




## 说明/提示

FJ wants to send 15 units of milk through his pipe network.  Pipe #1 connects junction point 1 (the barn) to junction point 2, and has a latency of 10 and a capacity of 3.  Pipes #2 and #3 are similarly defined.


The path 1->3 takes 14 + 15/1 = 29 units of time.  The path 1->2->3 takes 20 + 15/2 = 27.5 units of time, and is therefore optimal.


约翰想要通过管网运送15个单位的牛奶。管道1连接节点1（谷仓）和节点2，延迟为10，容量为3。管道2和管道3也以相似的方式来定义。


路径1->3花费14+15/1=29个单位的时间。路径1->2->3花费20+15/2=27.5个单位的时间，用时最少。


## 样例 #1

### 输入

```
3 3 15 
1 2 10 3 
3 2 10 2 
1 3 14 1 
```

### 输出

```
27 
```

# AI分析结果

### 综合分析与结论
本题目标是在给定的管道网络中找到一条路径，使得运送指定量牛奶的总时间（$L + X/C$）最小，其中$L$为路径延迟总和，$C$为路径上的最小容量。各题解主要思路为枚举容量，再通过最短路算法求出对应延迟，进而计算总时间并取最小值。

### 所选题解
- **作者：Eleven谦（5星）**
    - **关键亮点**：思路清晰，详细阐述了同时维护$L$和$C$的困难及解决办法，通过枚举$C$并跑最短路求$L$来解决问题。代码有详细注释，还给出了双倍经验的类似题目。
    - **核心代码**：
```cpp
inline void dijkstra(int li) {
    for(register int i=1;i<=n;i++) {
        vis[i]=0;
        dis[i]=20050206;
    }
    dis[1]=0;
    shan.push(make_pair(0,1));
    while(!shan.empty()) {
        int xx=shan.top().second;
        shan.pop();
        if(vis[xx]) continue;
        vis[xx]=1;
        for(register int i=head[xx];i;i=e[i].net) {
            int v=e[i].to;
            if(e[i].liu<li) continue;
            if(dis[v]>dis[xx]+e[i].val) {
                dis[v]=dis[xx]+e[i].val;
                shan.push(make_pair(-dis[v],v));
            }
        }
    }
}
```
    - **核心实现思想**：在Dijkstra算法基础上，加入对边容量的判断，只考虑容量不小于枚举值的边，更新最短路径。

- **作者：x_miracle（4星）**
    - **关键亮点**：明确指出不能想当然认为最短路上的流量与花费比就是答案，采用枚举容量控制变量的方法，代码结构清晰。
    - **核心代码**：
```cpp
void Dijkstra(int mincan) {
    std::memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i) dis[i]=INF;
    while(!q.empty()) q.pop(); 
    dis[1]=0; q.push((node) {1,0});
    while(!q.empty()) {
        node temp=q.top(); q.pop();
        int u=temp.pos;
        if(vis[u]) continue; vis[u]=1;
        for(int i=adj[u];i;i=e[i].nxt) {
            int v=e[i].to;
            if(mincan>e[i].can) continue;
            if(dis[v]>dis[u]+e[i].late) {
                dis[v]=dis[u]+e[i].late;
                if(!vis[v])
                    q.push((node) {v,dis[v]});
            }
        }
    }
}
```
    - **核心实现思想**：堆优化的Dijkstra算法，在遍历边时，跳过容量小于枚举最小容量的边，更新最短路径。

- **作者：CHGM（4星）**
    - **关键亮点**：清晰指出问题难点在于$c$，并提出枚举$c$跑Dijkstra取最小值的解决办法，代码注释明确。
    - **核心代码**：
```cpp
void dijkstra(int x) {
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    priority_queue<node,vector<node>,decltype(cmp)* > q(cmp);
    dis[1]=0;
    q.push((node){1,0});
    while(q.size()) {
        node t=q.top();
        q.pop();
        if(vis[t.v]==1)continue;
        vis[t.v]=1;
        for(int j=0;j<g[t.v].size();j++) {
            int v=g[t.v][j].v,w=g[t.v][j].w,l=g[t.v][j].l;
            if(dis[v]>dis[t.v]+w&&l>=x) {
                dis[v]=dis[t.v]+w;
                q.push((node){v,dis[v]});
            }
        }
    }
    if(dis[n]==0x3f3f3f3f)return;
    else d=min(d,dis[n]+s/x);
    return;
}
```
    - **核心实现思想**：Dijkstra算法模板稍作修改，在更新最短路径时，只考虑容量不小于枚举值的边，最后更新最小总时间。

### 最优关键思路或技巧
- **枚举容量**：由于要同时考虑延迟$L$和容量$C$两个相互矛盾的因素，通过枚举容量$C$，再利用最短路算法求出对应延迟$L$，从而解决问题。
- **最短路算法**：使用Dijkstra或SPFA算法求最短路径，在算法中加入对边容量的判断，确保路径上的最小容量不小于枚举值。

### 拓展思路
同类型题可考虑有多个权值需要同时优化的最短路问题，类似算法套路为枚举其中一个权值，再通过最短路算法求出其他权值，进而计算目标函数的最值。

### 推荐题目
- [P5837 [USACO19DEC]Milk Pumping G](https://www.luogu.com.cn/problem/P5837)
- [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)
- [P3063 [USACO12DEC]Milk Routing S](本题原题)

### 个人心得摘录与总结
- **作者：sunxiaofan**：提到本题被hack后变难，原本的spfa做法在第11个测试点会出现“后效性”问题，即路线容量变化导致结果不准确，于是采用跑两次spfa（一次从1到n，一次从n到1）的方法解决。总结为在处理最短路问题时，要注意权值变化可能带来的后效性问题，可尝试多次计算来避免。 

---
处理用时：38.56秒