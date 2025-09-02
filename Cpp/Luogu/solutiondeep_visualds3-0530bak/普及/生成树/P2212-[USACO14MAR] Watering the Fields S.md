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



# 最小生成树

## 题解思路与算法要点

### 核心思路对比
各题解均采用最小生成树算法，主要分为两类实现方式：

1. **Kruskal算法**（主流选择）
- 预处理所有距离≥C的边
- 按边权排序后贪心选择
- 使用并查集维护连通性
- 时间复杂度 O(E logE) 但实际通过预处理减少E

2. **Prim算法**（适合稠密图）
- 维护顶点到生成树的距离数组
- 每次选择最近的顶点加入生成树
- 朴素版复杂度O(n²)无需堆优化
- 堆优化版可降低到O(E + n logn)

### 解决难点
- **边数爆炸**：n=2000时完全图边数约2e6，但有效边（距离≥C）可能大幅减少
- **空间优化**：Kruskal题解采用动态计算边权而非存储所有坐标组合
- **连通性判断**：通过并查集合并次数是否达到n-1次判断解的存在性
- **距离计算优化**：直接比较平方值避免浮点运算

## 高分题解推荐（≥4星）

1. **Rye_Catcher（Kruskal版）** ★★★★☆
- 预处理时动态计算有效边
- 使用带路径压缩的并查集
- 代码结构清晰，实测344ms通过
- 关键代码段：
```cpp
for(ri j=1;j<i;j++){
    int d=(px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]);
    if(d>=c) edge[++tot] = {i,j,d};
}
sort(edge+1,edge+1+tot);
```

2. **origin_star（朴素Prim）** ★★★★
- 采用O(n²)朴素实现
- 动态计算顶点距离避免存储所有边
- 实测336ms通过，适合稠密图
- 核心逻辑：
```cpp
for(int j=1;j<=n;j++){
    if(minn[j] && (x[i]-x[j])²+(y[i]-y[j])² < minn[j])
        minn[j] = (x[i]-x[j])²+(y[i]-y[j])²;
}
```

3. **zybnxy（Kruskal教学版）** ★★★★
- 详细注释配合分步讲解
- 使用结构体存储边集
- 突出算法教学价值
```cpp
struct node{int x,y,wgt;};
sort(e+1,e+1+tot,cmp);
for(ri i=1;i<=tot;i++){
    if(find(u)!=find(v)) merge(u,v), ans+=w;
}
```

## 最优技巧提炼

1. **动态计算边权**
- 预处理时直接过滤无效边（距离<C）
- 节省内存空间和排序时间

2. **并查集路径压缩**
- 查找时直接修改父节点指针
- 关键代码：
```cpp
int find(int x){
    return fa[x]==x ? x : fa[x]=find(fa[x]);
}
```

3. **距离计算优化**
- 使用整数运算避免浮点误差
- 保留平方值直接比较

## 可视化设计建议

### 算法演示方案
1. **Kruskal动态展示**
- 用绿色高亮当前候选边
- 红色标记已选入生成树的边
- 实时显示并查集的树形结构

2. **Prim扩展过程**
- 蓝色表示已加入生成树的节点
- 黄色标注候选边界点
- 动态更新顶点距离值

### 复古像素风格实现
```javascript
// Canvas初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 10;

function drawNode(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

// 音效触发
const selectSound = new Audio('data:audio/wav;base64,UklGRl9v...');
function playSelectSound() {
    selectSound.currentTime = 0;
    selectSound.play();
}
```

## 相似题目推荐
1. P3366 【模板】最小生成树
2. P2872 [USACO07DEC]道路建设
3. P1546 [USACO3.1]最短网络

## 调试经验总结
- **边界情况**：n=1时应直接输出0
- **整数溢出**：距离平方可能超过int范围，需用long long
- **连通性判断**：最终选择的边数必须为n-1

## 核心代码实现
Kruskal算法完整实现：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };
Edge edges[2000000];
int fa[2001], x[2001], y[2001];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    int n, c, cnt = 0;
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
        fa[i] = i;
        for (int j = 1; j < i; ++j) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            int w = dx*dx + dy*dy;
            if (w >= c) edges[cnt++] = {i, j, w};
        }
    }
    
    sort(edges, edges + cnt, [](auto& a, auto& b){ return a.w < b.w; });
    
    int ans = 0, ecnt = 0;
    for (int i = 0; i < cnt; ++i) {
        int u = find(edges[i].u), v = find(edges[i].v);
        if (u != v) {
            fa[u] = v;
            ans += edges[i].w;
            if (++ecnt == n-1) break;
        }
    }
    
    cout << (ecnt == n-1 ? ans : -1);
    return 0;
}
```

---
处理用时：73.10秒