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
**计算几何、树状数组**

---

## 题解思路与核心难点

### 核心思路
1. **几何转化**：将直线与圆的交点转化为极角，把圆周展开为直线段，问题转化为区间相交问题。
2. **区间统计**：利用树状数组统计相交的区间对数，当处理每个区间的右端点时，查询左端点在此区间内的数量。

### 解决难点
- **几何计算**：推导直线与圆的交点公式，处理特殊情形（a=0或b=0时）。
- **极角排序**：正确计算两个交点的极角并按展开后的顺序排序。
- **高效统计**：树状数组在O(n log n)时间内统计区间交叠对数。

---

## 题解评分（≥4星）

### thmyl题解（★★★★☆）
- **亮点**：完整实现几何转化与树状数组统计，代码清晰。
- **代码**：使用atan2计算极角，通过vis数组标记区间端点。

### 3a51_题解（★★★★☆）
- **亮点**：提出逆序对思路，分情况讨论统计方法。
- **创新点**：将问题转化为逆序对问题，用归并排序处理。

---

## 最优思路提炼
1. **几何转换**：将圆周展开为线段，交点极角排序后转化为区间。
2. **树状数组优化**：按端点排序后，遇到右端点时查询左端点数量，总复杂度O(n log n)。

---

## 类似题目推荐
1. **P1884 [USACO12FEB] Overplanting S**（区间覆盖统计）
2. **P2163 [SHOI2007] 园丁的烦恼**（二维偏序问题）
3. **P1904 天际线**（扫描线算法）

---

## 代码核心实现（thmyl版）
```cpp
struct node { double ct; int id; };
bool cmp(node x, node y) { return x.ct > y.ct; }

// 计算交点并存入p数组
for (每条直线) {
    if (c*c < d*d*(a*a + b*b)) { // 判断直线与圆相交
        // 解方程计算x1,y1和x2,y2
        p[++num].ct = atan2(y1, x1); // 极角计算
        p[num].id = i;
        // 存入另一个交点...
    }
}

sort(p+1, p+num+1, cmp); // 按极角排序

// 树状数组统计区间交叠
for (每个端点) {
    if (vis[id]) { // 遇到右端点
        ans += query(i) - query(vis[id]);
        update(vis[id], -1); // 移除左端点
    } else { // 遇到左端点
        vis[id] = i;
        update(i, 1); // 加入树状数组
    }
}
```

---

## 可视化设计

### 动画演示
1. **几何转换**：动态展示圆周展开为线段，直线交点映射为区间端点。
2. **树状数组操作**：高亮当前处理的端点，显示查询范围和树状数组的更新过程。

### 复古像素风格
- **颜色方案**：绿色表示区间左端点，红色表示右端点，黄色高亮当前操作。
- **音效**：插入/删除端点时播放8-bit音效，统计时播放得分音效。
- **Canvas绘制**：用网格线表示树状数组，端点按排序位置动态移动。

---

## 个人心得
- **数学推导**：处理直线与圆相交时需注意分母为零的特殊情况。
- **精度问题**：极角排序时使用atan2确保正确性，避免浮点误差。

---
处理用时：67.06秒