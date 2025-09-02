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



---

## 算法分类
**计算几何 + 树状数组**

---

## 题解思路与核心难点

### 核心思路
将圆形交点问题转化为一维区间相交问题：  
1. **几何转化**：将每条直线与圆的交点转换为极角参数，将圆周展开为一条直线。  
2. **区间相交判定**：若两条直线的交点极角区间相交且不包含，则它们在圆内相交。  
3. **高效统计**：用树状数组维护区间端点，统计相交的区间对数。

### 解决难点
1. **极角计算与排序**：通过 `atan2` 计算交点极角并按降序排序，确保展开后的线性顺序正确。  
2. **树状数组维护**：遍历排序后的端点，遇到第二个端点时查询区间内的其他端点数量，实现 O(n log n) 统计。

---

## 题解评分（≥4星）

### 题解1：thmyl（★★★★☆）
- **亮点**：代码简洁，直接使用极角排序和树状数组实现，逻辑清晰。  
- **关键代码**：极角排序后动态维护树状数组，通过 `vis` 数组记录首次出现的位置。

### 题解2：SimonSu（★★★★☆）
- **亮点**：详细处理了不同情况下的交点计算，并分段排序上下半圆。  
- **关键代码**：将圆周拆分为上下两部分分别排序，确保展开顺序正确。

### 题解3：3a51_（★★★★☆）
- **亮点**：提出逆序对统计的替代方法，避免树状数组的使用。  
- **关键思路**：将问题转化为逆序对计数，通过归并排序求解。

---

## 最优思路提炼

### 几何转化与树状数组
1. **极角参数化**：将每个交点映射为极角，圆周展开为线性序列。  
2. **区间相交判定**：若区间 `[a1, a2]` 和 `[b1, b2]` 满足 `a1 < b1 < a2 < b2`，则两直线在圆内相交。  
3. **树状数组维护**：遍历排序后的端点，动态统计已处理但未闭合的区间数量。

### 关键代码片段（thmyl）
```cpp
sort(p+1, p+1+num, cmp); // 按极角降序排序
for (int i=1; i<=num; i++) {
    if (vis[p[i].id]) { // 遇到第二个端点
        ans += query(i) - query(vis[p[i].id]); // 查询区间内端点数量
        update(vis[p[i].id], -1); // 移除第一个端点
    } else { // 遇到第一个端点
        vis[p[i].id] = i; 
        update(i, 1); // 加入树状数组
    }
}
```

---

## 相似题目推荐
1. **P1904 天际线**（区间覆盖与统计）  
2. **P1355 三角形的最大面积**（几何计算与极角排序）  
3. **P1882 环状线**（环形问题展开为线性区间）

---

## 可视化设计

### 动画演示方案
1. **展开圆周**：将圆动态展开为一条直线，标记每条直线的两个端点。  
2. **区间高亮**：用不同颜色表示当前处理区间和已存在的区间。  
3. **树状数组更新**：在 Canvas 上显示树状数组的节点更新过程，步进时高亮当前操作位置。  
4. **音效提示**：插入端点时播放“点击”音效，统计相交时播放“成功”音效。

### 复古像素风格
- **颜色方案**：使用 8-bit 像素风格，圆为绿色网格，区间为红/蓝方块。  
- **自动演示**：按空格键步进，展示极角排序和树状数组维护过程。  
- **音效设计**：背景音乐为 8-bit 循环曲，关键操作触发不同音效。

---

## 个人心得摘录
- **极角排序方向**：必须统一排序方向（如降序），否则无法正确展开圆周。  
- **边界处理**：注意直线与圆相切或无交点的情况，需提前过滤。  
- **调试技巧**：手动验证极角计算结果，确保展开后的线性顺序正确。

---
处理用时：118.02秒