# 题目信息

# [USACO07DEC] Building Roads S

## 题目描述

Farmer John had just acquired several new farms! He wants to connect the farms with roads so that he can travel from any farm to any other farm via a sequence of roads; roads already connect some of the farms.

Each of the N (1 ≤ N ≤ 1,000) farms (conveniently numbered 1..N) is represented by a position (Xi, Yi) on the plane (0 ≤ Xi ≤ 1,000,000; 0 ≤ Yi ≤ 1,000,000). Given the preexisting M roads (1 ≤ M ≤ 1,000) as pairs of connected farms, help Farmer John determine the smallest length of additional roads he must build to connect all his farms.

给定 $n$ 个点的坐标，第 $i$ 个点的坐标为 $(x_i,y_i)$，这 $n$ 个点编号为 $1$ 到 $n$。给定 $m$ 条边，第 $i$ 条边连接第 $u_i$ 个点和第 $v_i$ 个点。现在要求你添加一些边，并且能使得任意一点都可以连通其他所有点。求添加的边的总长度的最小值。


## 说明/提示

### 数据规模与约定

对于 $100\%$ 的整数，$1 \le n,m \le 1000$，$1 \le x_i,y_i \le 10^6$，$1 \le u_i,v_i \le n$。

### 说明

Translated by 一只书虫仔。

## 样例 #1

### 输入

```
4 1
1 1
3 1
2 3
4 3
1 4```

### 输出

```
4.00```

# AI分析结果



### 综合分析与结论
本题是典型的最小生成树问题，所有题解均采用 Kruskal 或 Prim 算法。核心难点在于处理已有边的权值优化、计算欧式距离时的精度控制，以及大规模边集的高效处理。最优解法普遍采用 Kruskal 算法，通过预处理已有边直接合并集合，显著减少无效边参与排序。

---

### 精选题解与亮点分析

#### 1. 作者：lzpclxf（⭐⭐⭐⭐⭐）
**关键亮点**  
- 预处理边时通过 `i<j` 避免重复边，降低边集规模  
- 使用双重强制类型转换保证距离计算精度  
- 详细记录调试过程，强调 `double` 精度问题的教训  
**个人心得**  
> "我交了7遍都不过原因竟是double的问题...必须将运算结果强制转为double类型"

#### 2. 作者：Blue_wonders（⭐⭐⭐⭐）
**关键亮点**  
- 预处理时直接合并已有边的集合，减少后续计算量  
- 采用平方暂存距离，排序后再开方优化精度  
- 代码中通过 `l[][]` 快速定位已有边索引  
**核心代码片段**  
```cpp
for(int i=1;i<=m;i++){
    cin>>Q>>W;
    g[l[Q][W]].w=0.0; // 直接修改已有边权值
}
```

#### 3. 作者：Victorique（⭐⭐⭐）
**关键亮点**  
- 使用 Prim 算法实现，适合稠密图场景  
- 邻接矩阵存储边权，方便已有边快速置零  
- 明确标注计算时必须强制转换类型  
**核心代码片段**  
```cpp
a[h][l]=a[l][h]=0; // 邻接矩阵直接置零已有边
```

---

### 最优思路与技巧总结
1. **边集预处理优化**：对已有边直接合并集合（`find/union`），减少后续参与排序的无效边数量  
2. **精度控制技巧**：计算欧式距离时，将中间结果强制转为 `double` 类型，避免整数溢出  
3. **边生成优化**：仅生成 `i<j` 的边避免重复，将边集规模从 O(n²) 降为 O(n²/2)  
4. **数据类型选择**：使用 `double` 存储距离，输出时保留两位小数  

---

### 举一反三推荐
1. [P1547 Out of Hay](https://www.luogu.com.cn/problem/P1547) - 最小生成树最大边问题  
2. [P2330 [SCOI2005] 繁忙的都市](https://www.luogu.com.cn/problem/P2330) - 最小生成树+边数限制  
3. [P2504 聪明的猴子](https://www.luogu.com.cn/problem/P2504) - 距离阈值判断与MST结合

---
处理用时：47.40秒