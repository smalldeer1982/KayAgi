# 题目信息

# [CCC 2021 S4] Daily Commute

## 题目描述

已知有 $N$ 个地铁站，你家在 $1$，学校在 $N$。

有 $W$ 条单向人行道。经过需要一分钟。

此外还有一条环形地铁线路，依次经过 $S_1,S_2,\cdots,S_N$，且保证 $S_1=1$。每天**有且仅有**一辆地铁在 $0$ 时刻从 $S_1$ 出发，并且恰好在第 $i$ 分钟到达 $S_i$。

在接下来 $D$ 天中：

- 交换 $S_{X_i}$ 和 $S_{Y_i}$。注意修改是永久的。
- 查询从 $1$ 到 $N$ 的最短用时。你出发时地铁在 $1$。

## 说明/提示

$$3\leq N\leq 200000,0\leq W\leq 200000,1\leq D\leq 200000$$

译自 [CCC2021 S4](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

请注意常数。

## 样例 #1

### 输入

```
4 3 3
1 2
3 4
4 1
1 4 3 2
3 4
4 2
3 2
```

### 输出

```
1
2
3
```

# AI分析结果

### 综合分析与结论
这些题解核心思路相近，均围绕“最优方案是从起点坐一段地铁后步行到终点”展开。先建反图求各点到终点的距离，再结合坐地铁时间计算总用时，用数据结构维护最小值应对站点交换。

### 所选题解
- **作者：_•́へ•́╬_**（4星）
  - **关键亮点**：思路清晰，给出 `set` 和堆两种实现方式，对比不同数据结构的性能差异。
- **作者：CSP_Sept**（4星）
  - **关键亮点**：对“不会坐2次及以上地铁”给出严谨证明，使用线段树维护单点修改与全局最小值，思路独特。
- **作者：_zuoqingyuan**（4星）
  - **关键亮点**：详细证明核心结论，使用优先队列维护信息，代码实现简洁明了。

### 重点代码与思路
#### 作者：_•́へ•́╬_（堆实现）
```cpp
// 建反图，从终点跑bfs求各点到终点的距离
for(int i=1,u,v;i<=m;++i)read(u),read(v),--u,--v,e[i]=u,nxt[i]=h[v],h[v]=i;
for(int i=0,x;i<n;read(s[i]),a[--s[i]]=i,dis[i++]=1<<30);
q.emplace_back(n-1);dis[n-1]=0;
for(int i;q.size();)
{
    i=q.front();q.pop_front();
    for(int j=h[i];j;j=nxt[j])if(dis[e[j]]>>30)
        dis[e[j]]=dis[i]+1,q.emplace_back(e[j]);
}
// 用堆维护总用时
for(int i=0;i<n;++i)qwq.emplace(dis[i]+a[i],i);
// 处理交换操作
for(int u,v;d--;pi(qwq.top().first),pc('\n'))
{
    read(u);read(v);--u;--v;
    swap(s[u],s[v]);
    u=s[u];v=s[v];
    swap(a[u],a[v]);
    qwq.emplace(dis[u]+a[u],u);qwq.emplace(dis[v]+a[v],v);
    for(;qwq.top().first^dis[qwq.top().second]+a[qwq.top().second];qwq.pop());
}
```
**核心思想**：先建反图跑bfs求各点到终点的距离，再用堆维护总用时，每次交换站点后更新堆中的信息，弹出不符合条件的元素。

#### 作者：CSP_Sept（线段树实现）
```cpp
// 建反图，跑Dijkstra求各点到终点的距离
for(int i = 1 ; i <= m ; i++){
    int x, y, z;
    x = rd(), y = rd(), z = 1;
    add(y, x, z);
}
dij(n);
// 预处理坐地铁时间和总用时
for(int i = 1 ; i <= n ; i++){
    s[i] = rd();
    t[s[i]] = i - 1;
    tr.a[s[i]] = d[s[i]] + t[s[i]];
}
tr.build(1, n, 1);
// 处理交换操作
while(r--){
    int x = rd(), y = rd();
    int c = t[s[y]] - t[s[x]];
    tr.modify(s[x], s[x], 1, n, 1, c);
    tr.modify(s[y], s[y], 1, n, 1, -c);
    swap(t[s[x]], t[s[y]]); swap(s[x], s[y]);
    printf("%lld\n", tr.query(1, n, 1, n, 1));
}
```
**核心思想**：建反图跑Dijkstra求各点到终点的距离，用线段树维护总用时，每次交换站点后更新线段树中的信息，查询全局最小值。

#### 作者：_zuoqingyuan（优先队列实现）
```cpp
// 建反图，跑bfs求各点到终点的距离
for(int i=1,u,v;i<=m;i++){
    scanf("%d %d",&u,&v);
    add(v,u);
}
memset(dis,0x3f,sizeof(dis));
memset(mk,0,sizeof(mk));
q.push(n);dis[n]=0;
while(q.size()){
    int x=q.front();q.pop();
    for(int i=ver[x];i;i=nxt[i]){
        int y=to[i];
        if(mk[y])continue;
        mk[y]=1;
        dis[y]=dis[x]+1;
        q.push(y); 
    }
} 
// 用优先队列维护总用时
for(int i=1;i<=n;i++){
    scanf("%d",s+i);
    Q.push(mp(-(dis[s[i]]+i-1),mp(s[i],i))); 
}
// 处理交换操作
for(int i=1,u,v;i<=d;i++){
    scanf("%d %d",&u,&v);
    swap(s[u],s[v]);
    Q.push(mp(-(u+dis[s[u]]-1),mp(s[u],u)));
    Q.push(mp(-(v+dis[s[v]]-1),mp(s[v],v))); 
    while(Q.size()&&s[Q.top().second.second]!=Q.top().second.first)Q.pop();
    ans=-Q.top().first;
    printf("%d\n",ans);
}
```
**核心思想**：建反图跑bfs求各点到终点的距离，用优先队列维护总用时，每次交换站点后更新优先队列中的信息，弹出不符合条件的元素。

### 最优关键思路或技巧
- **核心结论**：最优方案是从起点坐一段地铁后步行到终点，避免多次坐地铁产生等待时间。
- **建反图**：以终点为起点跑最短路算法，可高效求出各点到终点的距离。
- **数据结构维护**：使用优先队列、线段树等数据结构维护总用时，在交换站点时快速更新信息并查询最小值。

### 可拓展之处
同类型题如带有特殊交通方式（如瞬移、限时公交等）的最短路问题，可借鉴本题思路，分析特殊交通方式的特点，结合普通路径规划，用合适的数据结构维护信息。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：考察最短路算法及路径计数。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：基础的单源最短路问题。
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：加强版的单源最短路问题。

### 个人心得
- **作者：_zuoqingyuan**：今天模拟赛挂了200分，这题贡献了100分。
  - **总结**：该作者通过本题认识到自己的不足，提醒我们在比赛中要重视每一道题。

---
处理用时：48.05秒