# 题目信息

# [USACO14MAR] Watering the Fields S

## 题目描述

Due to a lack of rain, Farmer John wants to build an irrigation system to


send water between his N fields (1 <= N <= 2000).

Each field i is described by a distinct point (xi, yi) in the 2D plane,

with 0 <= xi, yi <= 1000.  The cost of building a water pipe between two

fields i and j is equal to the squared Euclidean distance between them:



(xi - xj)^2 + (yi - yj)^2

FJ would like to build a minimum-cost system of pipes so that all of his

fields are linked together -- so that water in any field can follow a

sequence of pipes to reach any other field.


Unfortunately, the contractor who is helping FJ install his irrigation

system refuses to install any pipe unless its cost (squared Euclidean


length) is at least C (1 <= C <= 1,000,000).  

Please help FJ compute the minimum amount he will need pay to connect all

his fields with a network of pipes.


给定 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，如果想连通第 $i$ 个点与第 $j$ 个点，需要耗费的代价为两点的距离。第 $i$ 个点与第 $j$ 个点之间的距离使用欧几里得距离的平方进行计算，即：
$$(x_i-x_j)^2+(y_i-y_j)^2$$
我们规定耗费代价小于 $c$ 的两点无法连通，求使得每两点都能连通下的最小代价，如果无法连通输出 `-1`。

## 说明/提示

INPUT DETAILS:


There are 3 fields, at locations (0,2), (5,0), and (4,3).  The contractor

will only install pipes of cost at least 11.

OUTPUT DETAILS:


FJ cannot build a pipe between the fields at (4,3) and (5,0), since its

cost would be only 10.  He therefore builds a pipe between (0,2) and (5,0)


at cost 29, and a pipe between (0,2) and (4,3) at cost 17.  

Source: USACO 2014 March Contest, Silver

### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 2000$，$0 \le x_i,y_i \le 1000$，$1 \le c \le 10^6$。

### 说明

Translated by 一只书虫仔。

## 样例 #1

### 输入

```
3 11
0 2
5 0
4 3```

### 输出

```
46```

# AI分析结果



### 综合分析与结论
本题是典型的最小生成树问题，核心难点在于处理边权限制（≥C）和算法效率。各题解均采用Kruskal或Prim算法，关键差异在于优化策略与实现细节。稠密图场景下，朴素Prim时间复杂度更优；Kruskal通过预过滤边和排序处理更易实现。

---

### 高星题解推荐

#### 1. origin_star（五星）
**关键亮点**：  
- 采用朴素Prim算法，代码简洁高效（336ms）  
- 特殊处理无法连通情况（剩余点无法加入时break）  
- 提出正确Prim松弛逻辑，批判伪优化代码  

**核心代码片段**：
```cpp
void prim(){
    int d[maxn], cnt=0, ans=0, q=n-1;
    bool vis[maxn] = {0};
    fill(d, d+maxn, INF);
    d[1]=0;
    for(int i=1; i<n; i++){ // 只需n-1次循环
        int u=-1, min=INF;
        // 找最小边...
        for(int j=1;j<=n;j++)
            if(!vis[j] && d[j]<min) 
                {min=d[j]; u=j;}
        // 更新相邻边...
    }
}
```
**个人心得**：  
_"网上很多Prim堆优化代码是假的，正确松弛逻辑应更新所有相邻边"_  

#### 2. Rye_Catcher（四星）
**关键亮点**：  
- 同时实现Kruskal和Prim+优先队列优化  
- 对比三种实现性能（Kruskal 344ms，Prim+PQ 336ms）  
- 强调稠密图Prim的优势  

**核心对比**：
```cpp
// Kruskal核心
sort(edges);
for(edge : edges){
    if(Union(u,v)) ans += w;
    if(cnt == n-1) break;
}

// Prim核心
priority_queue<Ele> pq;
while(!pq.empty()){
    u = 堆顶;
    for(邻接边){
        if(d[v] > edge.dis){
            d[v] = edge.dis;
            pq.push(v, d[v]);
        }
    }
}
```

#### 3. zybnxy（四星）
**关键亮点**：  
- 清晰的Kruskal教程式题解  
- 图解最小生成树构建过程  
- 强调并查集路径压缩的重要性  

**代码亮点**：
```cpp
inline int addedge(int a,int b,int c){
    e[++tot].x=a; e[tot].y=b; e[tot].wgt=c;
}
```

---

### 关键思路总结
1. **边预处理**：计算所有点对距离，过滤掉<C的边（时间复杂度O(n²)）
2. **算法选择**：
   - **Kruskal**：适合稀疏图，需排序O(mlogm)，通过并查集维护连通性
   - **Prim**：适合稠密图，O(n²)时间复杂度更优
3. **连通性判断**：统计有效边数是否达到n-1
4. **优化技巧**：
   - 并查集路径压缩+按秩合并
   - Prim中维护d[]数组避免重复计算
   - 提前终止条件（边数足够时break）

---

### 拓展训练建议
1. **同类型题目**：
   - P3366 【模板】最小生成树（基础练习）
   - P2872 [USACO07DEC]道路建设（带坐标计算）
   - P1991 无线通讯网（最小生成树特殊应用）

2. **进阶技巧**：
   - Boruvka算法处理特殊图
   - 次小生成树求法
   - 动态最小生成树（LCT维护）

3. **调试经验**：
   - 使用断言检查并查集状态
   - 验证距离计算避免整数溢出
   - 对大规模数据优先测试连通性

---
处理用时：51.50秒