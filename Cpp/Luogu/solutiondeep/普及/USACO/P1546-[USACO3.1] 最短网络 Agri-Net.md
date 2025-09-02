# 题目信息

# [USACO3.1] 最短网络 Agri-Net

## 题目背景

Farmer John 被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。


## 题目描述

FJ 已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过 $10^5$。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.1


## 样例 #1

### 输入

```
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0```

### 输出

```
28```

# AI分析结果



### 综合分析与结论
本题为最小生成树模板题，所有题解均围绕Kruskal/Prim算法展开。核心差异在于数据存储优化、算法实现方式及代码可读性。关键技巧集中在邻接矩阵处理、并查集优化、堆优化Prim等方面。

### 精选题解推荐（评分≥4星）

1. **chengni（Kruskal） - 5星**
   - 亮点：利用邻接矩阵对称性仅存一半边，代码简洁高效，路径压缩优化明显
   - 代码核心思想：
     ```cpp
     // 只存上三角邻接矩阵
     if(j > i) { m++; a[m].x=i; a[m].y=j; a[m].w=k; }
     // Kruskal主循环
     for(int i=1; i<=m; i++){
         if(find(a[i].x) != find(a[i].y)){
             ans += a[i].w;
             f[find(a[i].x)] = a[i].y;
             if(++p == n) break;
         }
     }
     ```

2. **Strong_Jelly（双算法对比） - 5星**
   - 亮点：详细对比Prim/Kruskal优劣，提供双算法模板代码，适合不同场景
   - 关键对比结论：
     - Prim+堆优化适合稠密图（时间复杂度O(n²)）
     - Kruskal适合边数较多场景（O(m log m)）
   - 调试心得："注意邻接矩阵对角线为0的特殊处理"

3. **yyy2015c01（堆优化Prim） - 4星**
   - 亮点：STL优先队列实现堆优化Prim，适合稠密图场景
   - 核心代码片段：
     ```cpp
     priority_queue<Node> edge;
     while(!q.empty()){
         Node tmp = q.top(); q.pop();
         if(visted[tmp.to]) continue;
         visted[tmp.to] = true;
         ans += tmp.w;
         for(auto &e : G[tmp.to]){
             if(!visted[e.to]) q.push(e);
         }
     }
     ```

### 关键技巧总结
1. **邻接矩阵优化**：利用对称性仅存i<j的边（节省50%空间）
2. **并查集路径压缩**：`f[x] = find(f[x])`的递归写法简洁高效
3. **堆优化Prim**：优先队列维护候选边集，适合稠密图
4. **边数提前终止**：当已选边数达到n-1时直接跳出循环

### 拓展训练推荐
1. [P3366 最小生成树模板](https://www.luogu.org/problem/P3366)
2. [P1265 公路修建](https://www.luogu.org/problem/P1265)（Prim优化练习）
3. [P1550 浇水](https://www.luogu.org/problem/P1550)（带权值处理的最小生成树）

### 核心代码示例（Kruskal完整实现）
```cpp
struct Edge{ int u, v, w; };
vector<Edge> edges;

int kruskal() {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){ 
        return a.w < b.w; 
    });
    
    UnionFind uf(n);
    int ans = 0, cnt = 0;
    for(auto &e : edges) {
        if(uf.unite(e.u, e.v)) {
            ans += e.w;
            if(++cnt == n-1) break;
        }
    }
    return ans;
}
```

---
处理用时：45.54秒