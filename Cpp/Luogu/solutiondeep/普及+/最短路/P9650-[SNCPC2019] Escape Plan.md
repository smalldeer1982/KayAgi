# 题目信息

# [SNCPC2019] Escape Plan

## 题目描述

宝宝被困在了 Heltion 城中。

城市可以看做由 $n$ 个点与 $m$ 条边组成的**有权无向图**，最开始宝宝在 $1$ 号节点。城市中存在 $k$ 个出口，第 $i$ 个出口位置在 $e_i$ 号点 ，而宝宝需要以最快的速度到达**这些出口中的任意一个**以逃离 Heltion 城。

不巧的是，城市中有怪物游荡，对于点 $i$，有 $d_i$ 只怪物驻守在此。当宝宝到达点 $i$ 时，怪物会**随机封锁至多** $d_i$ **条**与之相邻的道路，宝宝不能通过这些被封锁的道路。而当宝宝**离开后**，点 $i$ 的怪物会回窝，这时被封锁的**道路会解开**。

请帮帮宝宝，求出最坏情况下，他逃出 Heltion 城需要多久。

## 说明/提示

对于 $100\%$ 的数据，$1\le n \le 10^5$，$\sum n \le 10^6$，$1\le m \le 10^6$，$\sum m \le 3\times 10^6$，$1\le k \le n$，$1\le e_i \le n$，$0\le d_i \le m$，$1\le x_i,y_i \le n$，$1\le w_i \le 10^4$。数据保证 $x_i \neq y_i$。

## 样例 #1

### 输入

```
2
3 4 1
3
1 1 1
1 2 1
1 2 2
2 3 1
2 3 2
3 2 2
2 3
2 0 0
1 2 1
1 3 1
```

### 输出

```
4
-1
```

# AI分析结果

### 综合分析与结论
这些题解均采用 Dijkstra 算法解决问题，核心思路是将多个终点当作起点反向跑图，以处理怪物随机封锁道路的情况。在每次从优先队列取出节点时，若该节点还有剩余的封锁次数，则减少其封锁次数并跳过；若封锁次数用完，则更新该节点的最短距离并扩展相邻节点。各题解在代码实现细节上有所不同，但整体思路一致。

### 所选题解
- **作者：liaoxingrui (赞：6)  ★★★★**
    - **关键亮点**：思路清晰，代码简洁，注释使用宏定义简化代码，提高了代码的可读性。
- **作者：keepwatcher_kensap (赞：3)  ★★★★**
    - **关键亮点**：详细阐述了思路和算法复杂度分析，代码结构清晰，使用了快读优化输入。
- **作者：WhitD (赞：2)  ★★★★**
    - **关键亮点**：思路阐述简洁明了，代码使用 `vector` 存储图，实现较为简洁。

### 重点代码及核心实现思想
#### liaoxingrui 的代码
```cpp
inline void dijkstra(){
    while(!a.empty()){
        int x=a.top().second,val=a.top().first;
        a.pop();
        if(d[x]){
            d[x]--;
            continue;
        }
        if(flag[x])
            continue;
        flag[x]=true;
        dis[x]=val;
        for(int i=head[x];i;i=next[i].y)
            if(!flag[now])
                a.push(m(val+vall,now));
    }
}
```
**核心思想**：从优先队列中取出节点，若该节点还有封锁次数则减少次数并跳过；若已访问则跳过；否则标记为已访问，更新最短距离，并将相邻未访问节点加入优先队列。

#### keepwatcher_kensap 的代码
```cpp
inline void dijkstra()
{
    for (int i=1;i<=n;i++) dis[i]=1e18;
    for (int i=1;i<=k;i++)
    {
        dis[out[i]]=0;sca[out[i]]=0;que.push(make_pair(0,out[i]));
    }
    while (!que.empty())
    {
        int x=que.top().second,z=que.top().first;
        que.pop();
        if (sca[x]!=0) { sca[x]--;continue;	}
        if (vis[x]) continue;
        vis[x]=true;
        dis[x]=-z;
        for (int i=las[x];i;i=nex[i])
        {
            int y=to[i],lon=len[i];
            if (vis[y]) continue;
            que.push(make_pair(z-lon,y));
        }
    }
    return ;
}
```
**核心思想**：初始化距离数组，将所有终点的距离设为 0 并加入优先队列。从队列中取出节点，若有封锁次数则减少并跳过；若已访问则跳过；否则标记为已访问，更新最短距离，并将相邻未访问节点加入队列。

#### WhitD 的代码
```cpp
void dij()
{
    priority_queue<pi,vector<pi>,greater<pi>> q;
    for(int i:e)
        q.push(pi(0,i));
    while(!q.empty())
    {
        pi x=q.top();
        q.pop();
        int s=x.second;
        if(dis[s]>=0||--d[s]>=0)
            continue;
        dis[s]=x.first;
        for(int i=0;i<g[s].size();i++)
            q.push(pi(dis[s]+v[s][i],g[s][i]));
    }
}
```
**核心思想**：将所有终点加入优先队列，从队列中取出节点，若该节点距离已更新或还有封锁次数则跳过；否则更新距离，并将相邻节点加入队列。

### 最优关键思路或技巧
- **反向跑图**：将多个终点当作起点反向跑 Dijkstra 算法，避免了正向跑时不知道该封锁哪条路的问题。
- **优先队列优化**：使用优先队列存储节点，每次取出距离最小的节点进行扩展，提高了算法效率。

### 拓展思路
同类型题或类似算法套路：
- 带有条件限制的最短路问题，如道路有时间限制、有通行费用等，可通过修改 Dijkstra 算法的判断条件来解决。
- 多源最短路问题，可使用 Floyd 算法或多次 Dijkstra 算法解决。

### 推荐题目
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)
- [P2865 [USACO06NOV]Roadblocks G](https://www.luogu.com.cn/problem/P2865)

### 个人心得
- WhitD：“第一眼以为是个 Dijkstra，其实它就是 Dijkstra”，表明该题本质上是 Dijkstra 算法的应用，关键在于对题目条件的处理。
- FarmarJohn：指出这题是 Dijkstra 最短路算法的改版，强调了对算法的灵活运用。
- SDLTF_凌亭风：认为明白 Dijkstra 算法的原理就能解决该题，突出了理解算法本质的重要性。 

---
处理用时：34.09秒