# 题目信息

# [USACO14MAR] The Lazy Cow S

## 题目描述

It's a hot summer day, and Bessie the cow is feeling quite lazy.  She wants

to locate herself at a position in her field so that she can reach as much

delicious grass as possible within only a short distance.


The field Bessie inhabits is described by an N by N grid of square cells

(1 <= N <= 400).  The cell in row r and column c (1 <= r,c <= N) contains

G(r,c) units of grass (0 <= G(r,c) <= 1000).  From her initial square in

the grid, Bessie is only willing to take up to K steps (0 <= K <= 2\*N).

Each step she takes moves her to a cell that is directly north, south,

east, or west of her current location.


For example, suppose the grid is as follows, where (B) describes Bessie's

```cpp
50    5     25*   6     17    
14    3*    2*    7*    21    
99*   10*   1*(B) 2*    80*    
8     7*    5*    23*   11   
10    0     78*   1     9        
```

initial position (here, in row 3, column 3):

If K=2, then Bessie can only reach the locations marked with \*s.

Please help Bessie determine the maximum amount of grass she can reach, if

she chooses the best possible initial location in the grid.

奶牛贝茜非常懒惰，她希望在她的地盘内找到一点最佳位置居住，以便在有限的步数内可以吃到尽量多的青草。

她的地盘是一个 $N \times N(1\le N \le 400)$ 的矩阵，第 $r$ 行 $c$ 列包含 $G(r,c)$ 单位的青草 $(0 \le G(r,c) \le 1000)$。从她的居住点，她最多愿意走 $K$ 步 $(0 \le K \le 2 \times N)$，每一步她可以走到上与她相邻的某个格子。

## 说明/提示

OUTPUT DETAILS:


In the example above, Bessie can reach 342 total units of grass if she

locates herself in the middle of the grid.


Source: USACO 2014 March Contest, Silver


## 样例 #1

### 输入

```
5 2
50 5 25 6 17
14 3 2 7 21
99 10 1 2 80
8 7 5 23 11
10 0 78 1 9
```

### 输出

```
342```

# AI分析结果



---

## **算法分类**  
前缀和与坐标变换

---

## **综合分析与结论**  
**核心思路**：将原网格旋转45度，使菱形区域转化为矩形，利用二维前缀和快速求解最大草量。  
**难点与解决**：  
1. **坐标变换**：将原坐标$(i,j)$映射到旋转后的$(i+j-1, N-i+j)$，确保菱形区域变为矩形。  
2. **二维前缀和**：预处理旋转后的二维前缀和数组，实现O(1)查询矩形区域和。  

**可视化设计**：  
1. **旋转动画**：展示原网格旋转45度后的新坐标系，并用不同颜色标记菱形对应的矩形区域。  
2. **前缀和高亮**：在旋转后的网格中，动态绘制当前计算的矩形区域，并实时显示区域和。  
3. **复古像素风格**：用8位像素风格绘制网格，音效提示最优解发现（如“成功”音效）。  

---

## **题解清单 (≥4星)**  
1. **yxy666（5星）**  
   - **亮点**：通过坐标变换将问题转化为矩形区域求和，时间复杂度最优（O(N²)）。  
   - **代码简洁性**：仅需一次二维前缀和预处理和单次遍历。  

2. **Ajwallet（4星）**  
   - **亮点**：行前缀和清晰易懂，处理边界逻辑详细。  
   - **适用性**：适合初学者理解菱形区域的逐行累加。  

3. **nzcnnr（4星）**  
   - **亮点**：分正/倒三角形处理，代码注释详细。  

---

## **最优思路提炼**  
**关键技巧**：  
1. **坐标旋转**：通过$(i,j) \to (i+j-1, N-i+j)$的变换，菱形区域变为矩形。  
2. **二维前缀和**：快速计算旋转后网格的矩形区域和。  
**代码片段**：  
```cpp
// 坐标旋转与前缀和计算
for (int i=1;i<=N;i++)
    for (int j=1;j<=N;j++)
        mp[i+j-1][N-i+j] = G[i][j];
for (int i=1;i<2*N;i++)
    for (int j=1;j<2*N;j++)
        F[i][j] = F[i-1][j] + F[i][j-1] - F[i-1][j-1] + mp[i][j];
```

---

## **类似题目推荐**  
1. **P1719 最大加权矩形**（二维前缀和经典题）  
2. **P2004 领地选择**（前缀和优化区域选择）  
3. **P2280 激光炸弹**（二维前缀和的应用）  

---

## **个人心得摘录**  
- **Ajwallet**：处理边界时需注意坐标越界，如`j-k+uuu`可能为负数，需修正为1。  
- **Expecto**：未处理K≥2N的特殊情况导致被卡点，需特判直接输出总和。  

---

## **可视化算法演示**  
**核心流程**：  
1. **坐标旋转动画**：原网格逐步旋转45度，显示新坐标系的建立过程。  
2. **前缀和计算**：动态填充旋转后的二维前缀和数组，高亮当前累加区域。  
3. **最优解搜索**：遍历每个中心点，实时显示其对应矩形区域和，并标记最大值。  

**复古风格实现**：  
- **像素网格**：用Canvas绘制8位风格的网格，每个格子为16x16像素。  
- **音效设计**：  
  - 坐标旋转时播放“旋转”音效。  
  - 发现更大草量时播放“得分”音效。  
- **自动演示**：按步长遍历中心点，自动计算并显示结果，支持暂停/继续。  

**示例代码片段（JS）**：  
```javascript
// 绘制旋转后的网格（伪代码）
ctx.fillStyle = "#8B00FF"; // 紫色像素风格
for (let i = 0; i < 2*N; i++) {
    for (let j = 0; j < 2*N; j++) {
        if (F[i][j] > 0) {
            ctx.fillRect(i*16, j*16, 16, 16);
        }
    }
}
```

---

**总结**：通过坐标变换将复杂区域转化为矩形，结合前缀和优化，是解决此类问题的经典思路。

---
处理用时：87.47秒