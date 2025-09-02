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



**唯一算法分类**：前缀和与差分、坐标变换

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
- **问题转化**：将原网格旋转45度，使菱形区域变为矩形，便于二维前缀和计算。
- **关键技巧**：坐标变换公式 `(r,c) → (r+c-1, N-r+c)`，将菱形映射为矩形区域。
- **前缀和优化**：预处理旋转后二维前缀和数组，以O(1)时间计算任意矩形区域和。

#### **解决难点**
1. **菱形区域的数学建模**：直接处理菱形边界复杂，通过坐标变换转化为标准矩形。
2. **高效区域求和**：利用二维前缀和避免重复遍历，时间复杂度从O(N³)优化到O(N²)。

---

### **题解评分 (≥4星)**

1. **yxy666 (★★★★★)**  
   - **亮点**：独创性坐标变换 + 二维前缀和，时间复杂度O(N²)，代码简洁高效。  
   - **关键代码**：
     ```cpp
     // 坐标变换与二维前缀和计算
     mp[i+j-1][N-i+j] = G[i][j];
     F[i][j] = F[i-1][j] + F[i][j-1] - F[i-1][j-1] + mp[i][j];
     ```
   - **心得**：“旋图后处理更简单” —— 数学思维突破问题限制。

2. **Ajwallet (★★★★)**  
   - **亮点**：行前缀和逐行累加，直观处理菱形边界，O(N³)可过。  
   - **关键代码**：
     ```cpp
     // 处理每行的列范围
     int l = max(1, j - (k - abs(i - u)));
     int r = min(n, j + (k - abs(i - u)));
     now += h[u][r] - h[u][l-1];
     ```
   - **心得**：“注意边界条件” —— 调试经验强调边界处理。

3. **nzcnnr (★★★★)**  
   - **亮点**：清晰的分步处理菱形上下部分，代码可读性强。  
   - **关键代码**：
     ```cpp
     for (int l = i-k; l <= i; l++) { /* 正三角形部分 */ }
     for (int l = i+1; l <= i+k; l++) { /* 倒三角形部分 */ }
     ```

---

### **最优思路提炼**
- **坐标变换**：菱形→矩形，消除复杂边界判断。  
- **二维前缀和**：O(1)时间计算区域和，避免重复遍历。  
- **数学建模**：通过几何变换将问题转化为已知高效解法。

---

### **同类型题与算法套路**
- **通用解法**：区域求和问题优先考虑前缀和；复杂形状尝试坐标变换。  
- **相似题目**：  
  1. **P1719 最大加权矩形**（二维前缀和模板）  
  2. **P3406 海底高铁**（差分与前缀和结合）  
  3. **P2004 领地选择**（二维前缀和+区域最值）

---

### **可视化与算法演示**
#### **动画设计**
1. **坐标变换演示**：  
   - **原网格**：显示奶牛当前位置及可达菱形区域（红色高亮）。  
   - **旋转后网格**：同步显示菱形变为矩形，蓝色框表示查询区域。  
   - **颜色标记**：当前中心点黄色，查询区域绿色渐变。  

2. **前缀和计算**：  
   - **步进显示**：逐行逐列填充前缀和数组，高亮当前计算单元格。  
   - **区域查询**：用半透明色块覆盖查询矩形，显示求和公式 `F[x2][y2] - F[x1][y2] - ...`。

#### **复古像素风格**
- **8位色彩**：草地用绿色像素块，奶牛用棕色，路径用亮黄色。  
- **音效**：  
  - **移动**：8-bit “哔”声。  
  - **区域计算**：短促“滴”声。  
- **Canvas实现**：网格绘制 + 色块填充，支持暂停/步进。

---

### **核心代码实现**
```cpp
// 坐标变换与前缀和预处理
for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
        rotated[i+j-1][N-i+j] = G[i][j];

// 二维前缀和
for (int i = 1; i < 2*N; i++)
    for (int j = 1; j < 2*N; j++)
        F[i][j] = F[i-1][j] + F[i][j-1] - F[i-1][j-1] + rotated[i][j];

// 查询最大值
int x_l = max(0, now_x-K-1), y_l = max(0, now_y-K-1);
int x_r = min(2*N-1, now_x+K), y_r = min(2*N-1, now_y+K);
ans = max(ans, F[x_r][y_r] - F[x_l][y_r] - F[x_r][y_l] + F[x_l][y_l]);
```

---

**总结**：通过坐标系转换将复杂区域求和转化为标准二维前缀和问题，是本题的最优解。核心在于数学建模与高效预处理，适合作为类似问题的通用解决思路。

---
处理用时：75.71秒