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



## 算法分类
单源最短路径（多源应用）

---

## 算法分析与结论
### 核心逻辑
1. **多源最短路径思想**：将每个牧场视为潜在起点，分别计算所有奶牛到该点的最短路径和
2. **算法选择**：SPFA（队列优化Bellman-Ford）或堆优化Dijkstra，在稀疏图（边数C=1450）中时间复杂度约为O(kE)，k为常数
3. **数据结构**：邻接表存储图结构（避免邻接矩阵的O(P²)空间浪费）
4. **关键优化**：每个起点的最短路计算相互独立，可复用数据结构

### 难点对比
| 算法类型       | 时间复杂度   | 空间复杂度 | 适用场景             |
|----------------|-------------|------------|---------------------|
| SPFA          | O(k*P*C)   | O(P+C)     | 稀疏图，允许负权边   |
| 堆优化Dijkstra | O(P*(C+P)logP) | O(P+C)     | 无负权边，稳定时间复杂度 |
| Floyd+剪枝     | O(P³/2)    | O(P²)      | 极低密度图（不推荐） |

---

## 高星题解推荐（≥4星）
1. **Obito（SPFA）** ★★★★☆  
   亮点：邻接表实现规范，SPFA流程注释详细，包含算法对比分析  
   核心代码段：
   ```cpp
   void spfa(int s) {
       memset(p,0,sizeof(p));
       for(int i=1;i<=n;i++) d[i]=INF;
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

2. **shadowice1984（堆优化Dijkstra）** ★★★★☆  
   亮点：STL优先队列应用优雅，结构体运算符重载实现最小堆  
   核心代码段：
   ```cpp
   void dijkstra(int s) {
       for(int i=1;i<=p;++i) dis[i]=INF;
       memset(vis,0,sizeof(vis));
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

---

## 可视化设计
### 算法演示方案
1. **动态图例**：
   - 🔴当前处理节点 🟢已确定最短路径节点 🟡队列中节点
   - 边权值实时显示，松弛成功时高亮显示边

2. **控制面板**：
   ```javascript
   class Animator {
       constructor() {
           this.speed = 500; // 毫秒/步
           this.autoMode = true;
           this.currentPasture = 0;
       }
       
       step() { /* 单步执行 */ }
       toggleAuto() { /* 自动/手动切换 */ }
       highlightPath(target) { /* 高亮奶牛聚集路径 */ }
   }
   ```

3. 复古像素风格实现：
   ```javascript
   // Canvas绘制示例
   function drawPixelNode(ctx, x, y, color) {
       ctx.fillStyle = color;
       ctx.fillRect(x*30+5, y*30+5, 20, 20); // 30px间隔的像素节点
   }
   
   // 8-bit音效
   const sfx = {
       enqueue: new Audio('data:audio/wav;base64,UklGRl9...'), // 入队音
       dequeue: new Audio('data:audio/wav;base64,UklGRl...')   // 出队音
   };
   ```

---

## 举一反三
1. **同类型题**：
   - 多起点最短路：P1346 电车
   - 路径和最小化：P3406 海底高铁

2. **推荐练习**：
   - P4779 【模板】单源最短路径（标准Dijkstra）
   - P3371 【模板】单源最短路径（SPFA验证）
   - P1462 通往奥格瑞玛的道路（带条件最短路）

---

## 核心代码实现
SPFA完整模板：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f, MAXP=805, MAXC=3000;

struct Edge { int to, w, next; } edges[MAXC*2];
int head[MAXP], cnt;
int dis[MAXP], cow[MAXP], P, C, N;

void addEdge(int u, int v, int w) {
    edges[++cnt] = {v, w, head[u]};
    head[u] = cnt;
}

void spfa(int s) {
    queue<int> q;
    vector<bool> inq(P+1, false);
    fill(dis, dis+P+1, INF);
    
    dis[s]=0, q.push(s), inq[s]=true;
    while(!q.empty()) {
        int u=q.front(); q.pop(); inq[u]=false;
        for(int i=head[u]; i; i=edges[i].next) {
            int v=edges[i].to;
            if(dis[v] > dis[u]+edges[i].w) {
                dis[v] = dis[u]+edges[i].w;
                if(!inq[v]) q.push(v), inq[v]=true;
            }
        }
    }
}

int main() {
    cin >> N >> P >> C;
    for(int i=0,t; i<N; ++i) cin >> t, cow[t]++;
    for(int i=0,u,v,w; i<C; ++i) {
        cin >> u >> v >> w;
        addEdge(u,v,w), addEdge(v,u,w);
    }
    
    int ans=INF;
    for(int i=1; i<=P; ++i) {
        spfa(i);
        int sum=0;
        for(int j=1; j<=P; ++j) sum += cow[j]*dis[j];
        ans = min(ans, sum);
    }
    cout << ans;
}
```

---
处理用时：101.88秒