# 题目信息

# [USACO12NOV] Distant Pastures S

## 题目描述

Farmer John's farm is made up of an N x N grid of pastures, where each pasture contains one of two different types of grass.  To specify these two types of grass, we use the characters ( and ), so for example FJ's farm might look like the following grid:

(()) 
)()( 
)((( 
))))
When Bessie the cow travels around the farm, it takes her A units of time to move from a pasture to an adjacent pasture (one step north, south, east, or west) with the same grass type, or B units of time to move to an adjacent pasture with a different grass type.  Whenever Bessie travels from one pasture to a distant pasture, she always uses a sequence of steps that takes the minimum amount of time.  Please compute the greatest amount of time Bessie will ever need to take while traveling between some pair of pastures on the farm.

给出一个n\*n的括号矩阵，从一个点走到相邻的同字符点需付出A的代价，到不同字符点需付出B的代价。求所有点对之间最短路的最大值。


## 说明/提示

It takes Bessie 5 units of time to travel between the upper-left corner and the lower-right corner of the grid.  No other pair of pastures causes her to travel for more time than this.


## 样例 #1

### 输入

```
3 1 2 
((( 
()( 
(() 
```

### 输出

```
5 
```

# AI分析结果



**算法分类**: 最短路

---

### 综合分析
本题要求计算网格中所有点对的最长最短路。核心思路是将网格点转换为图节点，建立相邻点间的边权（根据字符异同设为A/B），通过多次单源最短路算法（Dijkstra优先队列优化）求解最大值。主要难点在于处理网格转图的结构优化和算法效率控制。

---

### 精选题解与亮点

#### 1. 作者：liangbowen (★★★★☆)
**关键亮点**  
- 采用堆优化Dijkstra，时间复杂度合理（O(n²(n²+E)logn²)）
- 使用离散化方法将二维坐标映射为一维编号，提升代码可维护性  
- 完整处理了输入和边的双向建立逻辑  
**核心代码**  
```cpp
void add(int x, int y, int type) { ... }
void get_edge() {
    for (每个点四周合法邻点)
        if(同字符) add(u,v,A); else add(u,v,B);
}
int dijkstra(int start) {
    priority_queue优化实现，记录最大距离
}
```

#### 2. 作者：ZolaWatle (★★★★☆)
**关键亮点**  
- 代码结构简洁，直接基于坐标计算邻接关系  
- 使用STL优先队列实现Dijkstra，逻辑清晰  
- 通过离散化公式`idx[(i,j)]=n*(i-1)+j`高效处理节点编号  
**核心代码**  
```cpp
int id(int i,int j) { return n*(i-1)+j; }
void Dijkstra(int s) {
    // 标准堆优化实现，维护全局最大ans
}
```

---

### 关键思路总结
1. **网格转图**：将每个网格点视为节点，通过坐标公式（如`id(i,j) = n*(i-1)+j`）离散化为唯一ID。
2. **边权动态计算**：相邻点根据字符异同建立A/B权值的边。
3. **多次单源最短路**：对每个节点运行Dijkstra，维护全局最大距离。
4. **输入优化**：避免使用cin直接读字符，改用getchar或scanf提升效率。

---

### 拓展与相似题推荐
**同类套路**：网格中的路径问题常通过坐标离散化和图论算法解决，类似问题包括多状态最短路（如带油量限制）、动态权值调整等。  
**推荐题目**：  
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)  
2. [P1339 [USACO09OCT]Heat Wave G](https://www.luogu.com.cn/problem/P1339)  
3. [P1828 [USACO3.2] 香甜的黄油 Sweet Butter](https://www.luogu.com.cn/problem/P1828)  

**个人心得摘录**  
> "注意c++的流输入比c慢，需用ios::sync_with_stdio(false)加速" —— 输入优化是避免TLE的关键细节  
> "离散化之后连边代码更美观，方便调试" —— 强调代码结构的工程化处理  
> "每个点会被多次松弛，必须用优先队列优化" —— 正确选择数据结构直接影响算法效率

---
处理用时：51.70秒