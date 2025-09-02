# 题目信息

# [USACO3.2] 香甜的黄油 Sweet Butter

## 题目描述

Farmer John 发现了做出全威斯康辛州最甜的黄油的方法：糖。

把糖放在一片牧场上，他知道 $N$ 只奶牛会过来舔它，这样就能做出能卖好价钱的超甜黄油。当然，他将付出额外的费用在奶牛上。

Farmer John 很狡猾。像以前的 Pavlov，他知道他可以训练这些奶牛，让它们在听到铃声时去一个特定的牧场。他打算将糖放在那里然后下午发出铃声，以至他可以在晚上挤奶。

Farmer John 知道每只奶牛都在各自喜欢的牧场（一个牧场不一定只有一头牛）。给出各头牛在的牧场和牧场间的路线，找出使所有牛到达的路程和最短的牧场（他将把糖放在那）。

## 说明/提示

**数据范围**

对于所有数据，$1 \le N \le 500$，$2 \le P \le 800$，$1 \le A,B \le P$，$1 \le C \le 1450$，$1 \le D \le 255$。

---

**样例解释**

作图如下：

```cpp
          P2  
P1 @--1--@ C1
         |
         | 
       5  7  3
         |   
         |     C3
       C2 @--5--@
          P3    P4
```

把糖放在4号牧场最优。

## 样例 #1

### 输入

```
3 4 5
2
3
4
1 2 1
1 3 5
2 3 7
2 4 3
3 4 5```

### 输出

```
8```

# AI分析结果



### 综合分析
本题核心是多次单源最短路计算，各题解主要围绕SPFA、堆优化Dijkstra和优化Floyd展开。最优解需在时间效率与实现复杂度间平衡，SPFA在稀疏图中表现最佳，堆优化Dijkstra适用于稳定场景，Floyd优化后在小规模数据可行。

---

### 精选题解

#### 1. Obito（★★★★☆）
**亮点**：  
- 详细解析SPFA原理及与Bellman-Ford的对比  
- 邻接表实现节约空间  
- 指出SPFA判负环的延伸应用  
**核心代码**：
```cpp
void spfa(int s) {
    memset(p,0,sizeof(p));
    for(int i=1;i<=n;i++)d[i]=10000;
    d[s]=0; q.push(s); p[s]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop(); p[u]=0;
        for(int i=first[u];i;i=next[i]) {
            int v=to[i];
            if(d[v]>d[u]+w[i]) {
                d[v]=d[u]+w[i];
                if(!p[v]) q.push(v), p[v]=1;
            }	
        }
    }
}
```
**实现思路**：对每个牧场作为起点跑SPFA，累加所有奶牛所在牧场的最短距离。

#### 2. Refined_heart（★★★★☆）
**亮点**：  
- 堆优化Dijkstra提升稳定性  
- 前向星存图节省内存  
- 代码结构清晰易移植  
**核心代码**：
```cpp
void dijkstra(int s) {
    priority_queue<node> q;
    for(int i=1;i<=p;++i) dis[i]=inf;
    dis[s]=0, q.push({0,s});
    while(!q.empty()) {
        node tmp=q.top(); q.pop();
        int x=tmp.pos;
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=e[i].next) {
            int y=e[i].to;
            if(dis[y]>dis[x]+e[i].dis) {
                dis[y]=dis[x]+e[i].dis;
                q.push({dis[y],y});
            }
        }
    }
}
```
**实现思路**：使用优先队列优化Dijkstra，避免裸Dijkstra的O(n²)时间复杂度。

#### 3. shadowice1984（★★★★☆）
**亮点**：  
- Floyd算法双向边优化  
- 矩阵存储简化代码  
- 内积计算总距离提升效率  
**关键优化**：  
```cpp
for(int k=0;k<p;k++) 
    for(int i=0;i<p;i++)
        for(int j=0;j<i;j++) // 仅计算一半矩阵
            if(d[i][j]>d[i][k]+d[k][j])
                d[i][j]=d[j][i]=d[i][k]+d[k][j];
```

---

### 关键技巧总结
1. **邻接表+SPFA组合**：适合稀疏图，时间复杂度接近O(m)
2. **堆优化Dijkstra**：稳定O(mlogn)，避免极端数据退化
3. **双向边剪枝**：在Floyd中减少50%计算量
4. **距离预计算+累加**：避免重复计算奶牛路径

---

### 拓展练习
1. [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)  
2. [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)  
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---

### 调试经验摘录
1. **邻接表空间**：`BeyondStars`指出边数需开双倍，否则RE  
2. **队列初始化**：`EarthGiao`使用循环队列防止内存溢出  
3. **双向边处理**：`TJor`强调必须添加反向边，否则WA  
4. **数据类型**：`shadowice1984`用`inner_product`避免手工累加错误

---
处理用时：59.36秒