# 题目信息

# Crop Squares

## 题目描述

This is an interactive problem.

Farmer Stanley grows corn on a rectangular field of size $  n \times m  $ meters with corners in points $ (0, 0) $ , $ (0, m) $ , $ (n, 0) $ , $ (n, m) $ . This year the harvest was plentiful and corn covered the whole field.

The night before harvest aliens arrived and poisoned the corn in a single $ 1 \times 1 $ square with sides parallel to field borders. The corn inside the square must not be eaten, but you cannot distinguish it from ordinary corn by sight. Stanley can only collect a sample of corn from an arbitrary polygon and bring it to the laboratory, where it will be analyzed and Stanley will be told the amount of corn in the sample that was poisoned. Since the harvest will soon deteriorate, such a study can be carried out no more than $ 5 $ times.

More formally, it is allowed to make no more than $ 5 $ queries, each of them calculates the area of intersection of a chosen polygon with a square of poisoned corn. It is necessary to find out the coordinates of the lower-left corner of the drawn square (the vertex of the square with the smallest $ x $ and $ y $ coordinates).

## 说明/提示

In the first test from the statement, the aliens poisoned a square of corn with vertices at points with coordinates $ (1.5, 0.5) $ , $ (1.5, 1.5) $ , $ (2.5, 1.5) $ , $ (2.5, 0.5) $ . In the picture, it is red, the polygon selected in the query is blue, and their intersection is green.

Picture for the first query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/5905e23dc243a04aad10e5bcbe0e2cd6bb70131e.png)Picture for the second query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/55886132a04f6c81b89194c1c281874f100d6c79.png)

## 样例 #1

### 输入

```
3 3





0.5





0.5```

### 输出

```
? 4
0 0
2 0
2 3
0 3

? 4
0 0
0 1
3 1
3 0

! 1.5 0.5```

# AI分析结果



## 算法分类
几何构造/交互问题

---

## 题解思路、算法要点与解决难点

### 核心思路
通过构造特定几何图形，使得毒方块与查询多边形的交集面积直接映射到坐标轴上。利用两次锯齿形查询，分别解算x和y坐标。

### 算法要点
1. **锯齿形结构**：构造锯齿状多边形，使得毒方块的纵向移动导致面积变化仅与y坐标相关，横向同理。
2. **面积-坐标映射公式**：  
   - 纵向查询：面积公式为 $s_0 = \frac{y + 0.5}{m} \Rightarrow y = s_0 \cdot m - 0.5$  
   - 横向查询：面积公式为 $s_1 = \frac{x + 0.5}{n} \Rightarrow x = s_1 \cdot n - 0.5$
3. **精度处理**：通过微调多边形顶点（如±1e-7偏移）避免边界问题。

### 解决难点
- **几何构造**：设计形状使得面积仅依赖单一坐标轴。
- **公式推导**：通过相似三角形或积分计算面积与坐标的线性关系。
- **交互实现**：确保多边形不自交且符合题目要求。

---

## 题解评分 (≥4星)

1. **ExplodingKonjac 的题解（5星）**  
   - 思路清晰度：直接构造锯齿形，公式推导简洁。  
   - 代码可读性：仅需两次查询，代码极简。  
   - 优化程度：最优的两次查询解法。

2. **NoirCube1 的题解（4.5星）**  
   - 思路清晰度：详细分步推导，配图辅助理解。  
   - 实践操作性：提供顶点微调方案，避免精度问题。

3. **周子衡的题解（4星）**  
   - 核心思路正确，但缺乏代码实现细节。  
   - 配图说明构造逻辑，适合直观理解。

---

## 最优思路或技巧提炼

**关键技巧**：  
1. **单轴依赖构造**：通过锯齿或波浪形多边形，将二维坐标解耦为两个一维问题。  
2. **面积线性映射**：利用几何形状特性，使面积与坐标呈线性关系，直接公式求解。  
3. **交互优化**：最少两次查询，充分利用题目允许的精度误差。

---

## 同类型题或类似算法套路

- **交互构造题**：通过几何/数学关系将复杂问题分解为简单查询。  
- **坐标轴解耦**：将高维问题拆分为多个一维子问题。  
- **面积映射法**：利用几何形状特性将测量值映射为待求参数。

---

## 推荐相似题目
1. [CF1139E] Maximize Mex（坐标轴映射与交互）  
2. [CF1523D] Love-Hate（位运算与交互构造）  
3. [CF1452E] Two Editorials（区间覆盖与极值优化）

---

## 个人心得摘录

- **NoirCube1**：注意多边形顶点需微调避免被误判为开放形状。  
- **BigSmall_En**：调整矩形宽度至极小值，通过排序快速定位大致区间。  
- **ExplodingKonjac**：题目看似复杂，实则为纯数学构造，避免过度设计。

---

## 可视化与算法演示

### 动画方案
1. **锯齿形构造**：  
   - **步骤1**：绘制纵向锯齿多边形，高亮每个锯齿的上升沿。  
   - **步骤2**：毒方块沿y轴移动，动态显示交集面积变化。  
   - **步骤3**：展示面积公式推导过程，如红色三角形叠加蓝色矩形。  

2. **坐标解算**：  
   - **输入查询面积**：用户输入s0值，自动计算y坐标并标记在坐标轴上。  
   - **横向查询同理**：旋转视角，展示横向锯齿构造与x坐标解算。

### 复古像素化设计
- **颜色方案**：  
  - 毒方块：红色（#FF0000）  
  - 查询多边形：蓝色（#0000FF）  
  - 交集区域：绿色（#00FF00）  
- **音效**：  
  - 查询提交：8-bit“哔”声  
  - 成功定位：经典马里奥过关音效  
- **自动演示**：  
  - 毒方块随机生成，AI自动构造多边形并计算坐标。

### 代码片段（关键逻辑）
```cpp
// 纵向查询构造锯齿多边形
cout << "? " << 2*n + 2 << endl;
for (int i=0; i<n; i++) {
    cout << i << " 0" << endl;          // 左竖线起点
    cout << i+1 << " " << m << endl;    // 右竖线终点（锯齿顶部）
}
cout << n << " -1" << endl << "0 -1" << endl; // 闭合底部
```

---

**总结**：通过几何构造将复杂交互问题转化为数学公式，两次查询即可精准定位毒方块坐标，是交互题中“数学即算法”的典范。

---
处理用时：66.04秒