# 题目信息

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0```

# AI分析结果



### **唯一算法分类**
**扫描线 + 树状数组**

---

### **题解思路、算法要点与解决难点**
1. **核心问题**  
   在平面上选择分割点 $(x_0, y_0)$，使得四个区域的最小城市数最大化。关键在于：
   - **离散化**：将坐标映射到有序整数区间。
   - **扫描线**：按 $x$ 坐标从小到大遍历，动态维护左右两部分的 $y$ 分布。
   - **树状数组**：快速统计各区域点的数量。

2. **解决难点**  
   - **动态维护左右两部分的 $y$ 分布**：通过扫描线逐步将左侧点加入树状数组，右侧点移出。
   - **高效求最优 $y_0$**：在固定 $x_0$ 后，通过树状数组上二分或分类讨论，快速找到使四个区域最小值最大的 $y_0$。

---

### **题解评分（≥4星）**
1. **题解作者：__Louis__（4星）**  
   - **亮点**：清晰的离散化+扫描线框架，树状数组维护左右区域，分类讨论四种情况。
   - **代码可读性**：结构清晰，但变量命名较简略。

2. **题解作者：lfxxx（4星）**  
   - **亮点**：树状数组上倍增求第 $k$ 大，类似“冰火战士”二分思想。
   - **优化**：非递增/非递减序列取最小值，避免复杂分类。

3. **题解作者：内拉组里（4星）**  
   - **亮点**：树状数组上倍增求 $k$ 小值，结合剪枝优化（跳过不必要计算）。

---

### **最优思路或技巧提炼**
1. **离散化与扫描线框架**  
   - 将 $x$ 和 $y$ 离散化后排序，按 $x$ 从小到大遍历，维护左右两部分点的 $y$ 分布。
   - **代码片段**：
     ```cpp
     sort(arr+1, arr+1+n, cmp_x); // 按x排序
     for (int i=1; i<=n; i++) {
         // 将当前x的点从右侧移到左侧
         lt.insert(y_i, 1);
         rt.insert(y_i, -1);
     }
     ```

2. **树状数组上二分**  
   - 通过树状数组的前缀和性质，快速找到满足条件的 $y_0$。
   - **代码片段**（树状数组倍增找第 $k$ 小）：
     ```cpp
     int kth(int k) {
         int idx = 0;
         for (int i=log2(n); i>=0; i--) {
             if (idx + (1<<i) <= n && c[idx + (1<<i)] < k) {
                 idx += (1<<i);
                 k -= c[idx];
             }
         }
         return idx + 1;
     }
     ```

---

### **同类型题或类似算法套路**
- **二维数点问题**：统计矩形区域内点的数量。
- **最大值最小化/最小值最大化**：二分答案结合数据结构验证。
- **离散化+扫描线+树状数组**：经典组合，如逆序对、区间统计问题。

---

### **推荐相似题目**
1. **P1908 逆序对**（树状数组基础）
2. **P1972 [SDOI2009]HH的项链**（区间统计+树状数组）
3. **P4054 [JSOI2009]计数问题**（二维树状数组）

---

### **个人心得摘录**
- **lfxxx**：  
  > “观察到移动 $y_0$ 时形如非递增序列与非递减序列取最小值，类似冰火战士二分思路。”  
  → 将问题转化为经典模型，避免复杂分类。

- **Xy_top**：  
  > “比赛时在学校偷看题目，一眼秒了。”  
  → 离散化+扫描线是二维问题的常见解法。

---

### **可视化与算法演示**
#### **动画方案**
1. **扫描线动态移动**  
   - **颜色标记**：当前扫描的 $x$ 坐标（红色竖线），左侧树状数组（蓝色），右侧树状数组（绿色）。
   - **步进控制**：单步展示点的移动（从右侧移到左侧）。

2. **树状数组操作**  
   - **高亮**：当前二分查找的 $y$ 位置，四个区域的计数变化。
   - **音效**：点移动时播放“像素移动”音效，找到最优解时播放胜利音效。

3. **复古像素风格**  
   - **Canvas 绘制**：  
     - 平面网格化，每个点用像素块表示，分割线为红色像素线。
     - 树状数组的更新以“方块堆积”动画呈现。

#### **代码片段（Canvas绘制分割线）**
```javascript
function drawSplitLine(x, y) {
    ctx.fillStyle = "#FF0000";
    ctx.fillRect(x * gridSize, 0, 2, canvas.height); // 竖线
    ctx.fillRect(0, y * gridSize, canvas.width, 2); // 横线
}
```

---

### **总结**
本题核心是**离散化+扫描线+树状数组**的组合应用，通过动态维护点的分布，结合二分或树状数组特性快速求解最优分割点。可视化设计可突出扫描线与树状数组的联动，辅以复古像素风格增强理解。

---
处理用时：73.44秒