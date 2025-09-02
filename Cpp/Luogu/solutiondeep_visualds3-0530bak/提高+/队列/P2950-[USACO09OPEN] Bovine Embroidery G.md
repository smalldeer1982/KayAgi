# 题目信息

# [USACO09OPEN] Bovine Embroidery G

## 题目描述

Bessie has taken up the detailed art of bovine embroidery. Cows embroider a cloth mounted in a circular hoop of integer radius d (1 <= d <= 50,000). They sew N (2 <= N <= 50,000) threads, each in a straight line from one point on the edge of the hoop to another point on the edge of the hoop (no two embroidered points share a location on the hoop's edge).

Being mathematically inclined, Bessie knows a formula of the form ax + by + c = 0 for each straight line piece of thread. Conveniently, a, b, and c are integers (-1,000,000 <= a <= 1,000,000; -1,000,000 <= b <= 1,000,000; -1,000,000 <= c <= 1,000,000). Even more

conveniently, no two threads coincide exactly.

Perhaps less conveniently, Bessie knows that her set of formula coefficients also includes a number of formulae for threads that do not appear to pass inside the hoop's circle. She regrets this greatly.

The origin (0,0) is in the precise middle of the hoop, so all points on the hoop's edge are distance d from the origin. At least one of the coefficients a and b is non-zero for each thread's formula.

Bovine embroidery is more highly regarded when the number of thread intersections is maximized. Help Bessie: count the number of pairs of threads that intersect on the cloth (i.e., within distance d of the origin). Note that if three threads happen to coincide at the same point, that would be three pairs of intersections. Four threads at the same point -> six pairs of intersections, etc.

Bessie学会了刺绣这种精细的工作。牛们在一片半径为d(1 <= d <= 50000)的圆形布上绣花. 它们一共绣了N (2 <= N <= 50000)条直线，每条直线连接布的边缘上的两个点(没有两条线通过边上同一个点)。

作为一只热爱数学的牛，Bessie 知道每条线的公式, ax + by + c = 0. a, b, 和 c 为整数(-1000000 <= a <= 1000000; -1000000 <= b <= 1000000; -1000000 <= c <= 1000000).没有两条线完全重合。

不幸的是, 一部分线不通过圆布的内部. 原点(0,0)在布的正中央, 所有边上的点离原点距离为d. 每条线的公式满足至少a,b中的一个非零. 对于牛来说，刺绣作品中线的交点越多，便越有价值。帮助Bessie计算在圆中相交的线的对数，也就是说交点与原点的距离小于d。注意如果三条线在圆内同一点相交,这算3对线。4线共点->6对线.


## 说明/提示

The two lines are x=0 and y=0. 

The two lines intersect at (0,0), which is clearly with 1 of the origin. 



## 样例 #1

### 输入

```
2 1 
1 0 0 
0 1 0 
```

### 输出

```
1 
```

# AI分析结果



## 算法分类
**计算几何、扫描线算法、树状数组**

---

## 题解思路、算法要点与解决难点

### 核心思路
1. **几何转化**：将圆展开为线段，直线与圆的交点转化为极角排序后的区间。
2. **区间相交统计**：两条直线在圆内相交的条件等价于它们的极角区间相交。
3. **树状数组优化**：通过极角排序和离线处理，用树状数组高效统计相交区间对数。

### 解决难点
- **几何推导**：将直线与圆的交点转换为极角，正确排序后形成区间。
- **高效统计**：处理5e4量级数据时，必须采用O(n log n)算法，树状数组或逆序对方法适用。

---

## 题解评分（≥4星）

### 1. thmyl的题解（4.5星）
- **亮点**：代码简洁，直接计算交点极角并排序，树状数组统计相交区间。
- **关键代码**：正确处理直线与圆交点，极角排序后离线处理区间端点。

### 2. SimonSu的题解（4星）
- **亮点**：详细注释和分情况处理直线方程，可视化思路清晰。
- **特色**：将圆的上半部和下半部分别处理，避免极角排序的特殊问题。

### 3. 3a51_的题解（4星）
- **亮点**：提出逆序对替代树状数组的思路，扩展了统计方法多样性。

---

## 最优思路或技巧提炼

1. **极角展开法**：
   - 将圆上的交点转换为极角，排序后展开为线性区间。
   - 使用`atan2`计算角度，避免直接处理坐标的复杂性。

2. **离线扫描线**：
   - 按极角排序所有端点，依次处理每个区间的左右端点。
   - 树状数组动态维护已处理的左端点，快速统计区间相交数。

3. **分情况处理直线方程**：
   - 单独处理`a=0`或`b=0`的直线，避免除零错误。
   - 利用二次方程求根公式计算一般情况的交点。

---

## 同类型题或类似算法套路

1. **区间相交统计**：如[P2161 会场预约](https://www.luogu.com.cn/problem/P2161)。
2. **极角排序应用**：如[CF598C Nearest vectors](https://codeforces.com/contest/598/problem/C)。
3. **扫描线算法**：如[P1904 矩形覆盖](https://www.luogu.com.cn/problem/P1904)。

---

## 推荐洛谷题目

1. **P2161 [SHOI2009] 会场预约**（区间统计）
2. **CF598C Nearest vectors**（极角排序）
3. **P1904 矩形覆盖**（扫描线应用）

---

## 可视化与算法演示

### 核心流程
1. **极角展开**：圆被展开为线段，动态显示每个直线端点对应的极角。
2. **区间绘制**：用不同颜色标记各直线对应的极角区间。
3. **树状数组更新**：高亮当前处理的端点，显示树状数组的更新和查询操作。

### 复古像素风格设计
- **颜色方案**：使用8位机风格的16色调色板，区间用不同色块表示。
- **音效触发**：
  - **点击端点**：播放“哔”声。
  - **统计相交**：播放上升音调。
- **自动演示模式**：逐步展示极角排序和树状数组更新过程。

---

## 代码片段（关键逻辑）

```cpp
// thmyl的代码核心部分（极角排序与树状数组）
for (int i=1;i<=num;i++) {
    if (vis[p[i].id]) {
        ans += query(i) - query(vis[p[i].id]);
        update(vis[p[i].id], -1);
    } else {
        vis[p[i].id] = i;
        update(i, 1);
    }
}
```

**说明**：
- `vis`数组记录每个直线的第一个端点位置。
- 树状数组动态维护区间，遇到右端点时统计区间内已记录的左端点数目。

---
处理用时：90.82秒