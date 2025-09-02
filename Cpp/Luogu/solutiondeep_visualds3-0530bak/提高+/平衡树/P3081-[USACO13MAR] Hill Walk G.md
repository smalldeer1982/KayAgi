# 题目信息

# [USACO13MAR] Hill Walk G

## 题目描述

There are N hills (1 <= N <= 100,000). Each hill takes the form of a line segment from (x1, y1) to (x2, y2) where x1 < x2 and y1 < y2. None of these segments intersect or touch, even at their endpoints, and furthermore, the first hill satisfies (x1, y1) = (0,0).

Bessie the cow starts at (0,0) on the first hill. Whenever Bessie is on a hill, she climbs up until she reaches the end. Then she jumps off the edge. If she lands on another hill, she continues walking on that hill; otherwise, she falls very far until she lands safely on a cushion of pillows at y = -infinity.  Each hill (x1, y1) -> (x2, y2) should be regarded as containing the point (x1, y1) but not containing the point (x2, y2), so that Bessie will land on the hill if she falls on it from above at a position with x = x1, but she will not land on the hill if she falls on it from above at x = x2.

Please count the total number of hills that Bessie touches at some point during her walk.

有 $N(1 \le N \le 10 ^ 5)$座小山，每座山所占的区域用直线 $(x1, y1)$ 到 $(x2, y2)$ 来表示（$x1 < x2$ 并且 $y1 < y2$）。也就是说这些山用笛卡尔坐标系里的线段来表示，这些用于表示小山的线段都没有任何交点，第一座山的一端位于 $(x1, y1) = (0,0)$。


贝西从 $(0,0)$ 开始在第一座山上漫步，一旦贝西到了一座山，她会一直走到该山的终点，这时，她会从边缘处起跳，如果她降落到另一座山上，她会继续在新的山上漫步。贝西起跳后沿 $y$ 轴方向下落，如果贝西不能降落到一座山上，她会一直下落，直到到达 $y$ 轴的负无穷大位置（$y = -\infin$）。


每座用线段表示的山 $(x1, y1) \to (x2, y2)$ 包含 $(x1, y1)$ 这个点，但不包含 $(x2, y2)$，请计算出贝西总共在多少座山上漫步了。


## 说明/提示

There are four hills.  The first hill runs from (0,0) to (5,6), and so on.


Bessie walks on hills #1, #4, and finally #3.


## 样例 #1

### 输入

```
4 
0 0 5 6 
1 0 2 1 
7 2 8 5 
3 0 7 7 
```

### 输出

```
3 
```

# AI分析结果



---

**算法分类**：扫描线、李超线段树

---

### **题解思路与核心难点**

**核心逻辑**：贝西每次从当前山终点垂直下落时，需快速找到最高且覆盖该 x 坐标的下一座山。  
**核心步骤**：
1. **离散化**：将线段端点离散化以降低数据规模。
2. **事件排序**：按线段左端点排序，用扫描线按 x 坐标逐步处理线段。
3. **动态维护候选线段**：使用李超树维护当前可能覆盖的线段，插入符合条件的线段。
4. **跳跃查询**：在离散化的 x 坐标处查询李超树，找到最高有效线段。

**解决难点**：
- **动态插入与查询**：需在离散化后的 x 坐标区间内插入线段，并在跳跃时快速查询。
- **正确性保证**：离散化后需保留原始坐标计算高度，避免几何关系错误。

---

### **题解评分（≥4星）**

1. **灵乌路空（5星）**  
   - 结合扫描线与李超树，离散化处理完善，代码结构清晰。
2. **Prms_Prmt（4星）**  
   - 平衡树维护线段优先级，几何比较逻辑严谨，代码简洁。
3. **hzoi_Shadow（4星）**  
   - 李超树动态开点实现，离散化与扫描线结合紧密。

---

### **最优思路提炼**

1. **扫描线事件驱动**  
   按线段左端点排序，逐步插入可能覆盖当前 x 的线段，确保候选集动态更新。
2. **李超树高效查询**  
   在离散化后的 x 坐标区间插入线段，查询时直接获取当前 x 的最高线段。
3. **几何比较逻辑**  
   比较线段右端点与斜率，确保在平衡树中正确维护线段优先级。

---

### **类似题目推荐**

1. **P4097 [HEOI2013] Segment**（李超树模板题）  
2. **P4254 [JSOI2008] Blue Mary开公司**（动态维护线段）  
3. **P3299 [SDOI2016] 齿轮**（扫描线与几何判断）

---

### **可视化设计（李超树版本）**

**动画流程**：
1. **坐标网格**：Canvas 绘制离散化后的 x 轴，高亮当前跳跃点 `(x2, y2)`。
2. **线段插入**：扫描线从左向右移动，触发线段插入事件时，动态绘制线段插入李超树的过程。
3. **跳跃查询**：在 `x2` 处显示垂直射线，李超树节点递归查询时高亮当前比较的线段。
4. **结果反馈**：若找到新线段，贝西像素小人跳跃至新山起点；否则坠落至屏幕底部。

**交互设计**：
- **复古像素风格**：贝西用 8x8 像素块表示，线段用不同颜色区分。
- **音效触发**：插入线段时播放“滴”声，查询命中时播放上扬音效，坠落时播放低沉音效。
- **自动演示**：按事件顺序逐步执行，支持暂停/继续/步进控制。

---

### **核心代码片段（灵乌路空题解）**

```cpp
// 离散化与扫描线初始化
for (int i = 1; i <= n; ++ i) {
    l[i].l = std::lower_bound(data + 1, data + datanum + 1, l[i].l) - data;
    l[i].r = std::lower_bound(data + 1, data + datanum + 1, l[i].r) - data;
}
std::sort(l + 2, l + n + 1, cmp1); // 按左端点排序

// 李超树查询与更新
int ret = LSeg::Query(1, 1, datanum, l[now].p).second;
if (!ret) break;
++ ans;
now = ret, nowp = l[now].x2, nowh = l[now].y2;
```

---

### **总结**

本题核心在于通过扫描线动态维护候选线段，并利用高效数据结构（李超树/平衡树）快速查询。离散化处理是关键优化手段，确保算法在合理复杂度内运行。不同题解在实现细节上各有亮点，但核心思路均为事件驱动与高效几何查询的结合。

---
处理用时：87.26秒