# 题目信息

# [USACO11FEB] The Triangle S

## 题目描述

For her spectacular milk output for the previous month, Farmer John has awarded Bessie a prize -- with a twist.  He has given her a triangular grid with N (1 <= N <= 700) rows (whose lengths vary from 1 through N, of course). Row i of the the grid has i values labeled v\_ij (-1,000,000,000 <= v\_ij <= 1,000,000,000) where j is in the range 1..i.

Bessie chooses a sub-triangle whose side length is at least K (1 <= K <= 20; 1 <= K <= N) within the triangular grid. The sub-triangle is another triangular grid which might be oriented the same as the original triangle or might be 'upside down' with its shorter rows on the bottom instead of the top.

After she chooses her sub-triangle, Farmer John will take the average of all the numbers in the sub-triangle, discarding the digits to the right of the decimal point, and give her that many gold coins (or take that many gold coins from her if the number is negative). Naturally, Bessie would like to maximize her prize (or minimize her loss). Help her solve this problem.

By way of example, Bessie is given this triangular grid with N = 3 rows and must choose a sub-triangle with a side length of at least K = 2. A graphical representation of the triangle is shown below:

```cpp
    / \
   / 5 \
  /-8  4\
 /2 -3  6\
 ---------
```
She could choose any of five valid sub-triangles (one of which is the entire original triangle):

```cpp
                                                   /\
    / \         / \        / \         / \        /5 \       
   / 5 \       / \5\      / 5 \       / 5/\      /----\    
  /-8  4\     /-8 \4\    /-8  4\     /-8/ 4\    /\-8 4/\ 
 /2 -3  6\   / 2 -3\6\  /-------\   / 2/-3 6\  / 2\-3/6 \ 
 ---------   ---------  -2  -3  6   ---------  ----------  
  entire      lower        top          lower     upside
 triangle     left                      right      down
```
The one that is lined below is the one with the highest average:

```cpp
    / \
   / 5/\
  /-8/ 4\
 / 2/-3 6\
 ---------
```
The average of this sub-triangle is (4+6-3)/3, which is about

2.3333...; without the fraction, the answer is 2. 

Help Bessie calculate the maximum amount of coins which she could receive.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 32 MB

有一个n(1<=n<=700)行的等腰三角形，里面有很多数(-1,000,000,000 <= 数 <= 1,000,000,000)，现在可以选择边长至少为k(1<=k<=20,1<=k<=n)，至多为2k的相似等腰三角形，并且可以倒着选，比如样例可以有这些选择方法：


样例：

```cpp
                                                   /\
    / \         / \        / \         / \        /5 \       
   / 5 \       / \5\      / 5 \       / 5/\      /----\    
  /-8  4\     /-8 \4\    /-8  4\     /-8/ 4\    /\-8 4/\ 
 /2 -3  6\   / 2 -3\6\  /-------\   / 2/-3 6\  / 2\-3/6 \ 
 ---------   ---------  -2  -3  6   ---------  ----------  
  entire      lower        top          lower     upside
 triangle     left                      right      down
```
最后问你可以得到的最大平均值为多少（平均值：选出的三角形的累加和div选出个数）


## 说明/提示

感谢 zzkksunboy 提供翻译。


## 样例 #1

### 输入

```
3 2 
5 
-8 4 
2 -3 6 
```

### 输出

```
2 
```

# AI分析结果



---

## **算法分类**
枚举 + 前缀和

---

## **综合分析与结论**
### **题目核心思路**
- 给定一个三角形网格，要求找到边长相至少为 K 的子三角形（可正可倒），使得其元素平均值的整数部分最大。
- **关键难点**在于高效枚举所有可能的子三角形并快速计算其总和。直接暴力枚举所有子三角形的时间复杂度为 O(n^3k)，无法通过时间限制。
- **核心优化**：预处理每行的前缀和，将单层元素和的计算复杂度降至 O(1)。通过枚举顶点和边长，累加各层和，并在满足条件时更新最大值。

### **核心算法流程**
1. **预处理**：对每一行计算前缀和，方便快速计算任意区间的和。
2. **枚举顶点**：遍历原三角形中的每个顶点 (i, j)。
3. **枚举边长**：
   - **正方向**：以 (i, j) 为顶点，向右下扩展。每扩展一层 k，计算该层的元素和，累加到总和。若 k ≥ K，更新最大值。
   - **倒方向**：以 (i, j) 为顶点，向左上扩展。类似正方向的处理。
4. **边界处理**：当扩展的子三角形超出原三角形范围时终止枚举。

### **可视化设计思路**
- **网格展示**：用 Canvas 绘制原三角形，每个元素以网格形式显示。
- **动态扩展**：高亮当前枚举的顶点，逐步扩展子三角形的边长，用不同颜色区分正/倒方向。
- **实时计算**：显示当前子三角形的总和、元素个数和平均值。
- **交互控制**：允许单步执行或调整动画速度，观察扩展过程。

---

## **题解清单 (≥4星)**

### **Log_x 题解 (⭐⭐⭐⭐)**
- **亮点**：通过前缀和优化计算，代码简洁高效。
- **不足**：错误限制边长为 2K，可能导致漏解。
- **关键代码**：
  ```cpp
  for (int k = 1; k <= (d << 1); ++k) {
    int tx = i + k - 1, ty = j + k - 1;
    if (tx > n || ty > tx) break;
    res += a[tx][ty] - a[tx][j - 1]; 
    num += k;
    if (k >= d) CkMax(Ans, res / num);
  }
  ```

### **lailai0916 题解 (⭐⭐⭐⭐⭐)**
- **亮点**：正确处理边界条件，允许任意边长 ≥K，时间复杂度严格 O(n²k)。
- **关键代码**：
  ```cpp
  for (int k=1; k<=n-i+1; k++) {
    sum += a[i+k-1][j+k-1] - a[i+k-1][j-1];
    if (k >= K) ans = max(ans, sum / (k*(k+1)/2));
  }
  ```

---

## **最优思路与技巧提炼**
### **核心技巧**
1. **前缀和优化**：预处理每行前缀和，快速计算区间和。
2. **分层累加**：按子三角形边长逐层扩展，累加各层和。
3. **方向分离**：正/倒方向分别枚举，避免复杂条件判断。

### **关键实现**
```cpp
// 预处理前缀和
for (int i=1; i<=n; ++i)
  for (int j=1; j<=i; ++j)
    a[i][j] += a[i][j-1];

// 正方向枚举
for (int k=1; k<=n-i+1; k++) {
  sum += a[i+k-1][j+k-1] - a[i+k-1][j-1];
  if (k >= K) update_max(ans, sum / (k*(k+1)/2));
}
```

---

## **相似题目推荐**
1. **洛谷 P1115** 最大子段和（一维前缀和）
2. **洛谷 P1719** 最大加权矩形（二维前缀和）
3. **LeetCode 120** 三角形最小路径和（动态规划）

---

## **可视化与算法演示**
### **动画设计**
- **网格绘制**：用 Canvas 绘制原三角形，元素值以文本显示。
- **扩展效果**：当前子三角形以半透明色覆盖，边长为 k 时逐步扩展。
- **数据面板**：实时显示总和、元素个数、平均值。

### **复古像素风格**
- **颜色方案**：16 色调色板，原三角形用绿色系，子三角形用红/蓝区分方向。
- **音效**：扩展时播放“哔”声，找到更优解时播放上升音调。

---

**注**：Log_x 题解因错误限制边长被扣分，lailai0916 题解为最优实现。

---
处理用时：215.97秒