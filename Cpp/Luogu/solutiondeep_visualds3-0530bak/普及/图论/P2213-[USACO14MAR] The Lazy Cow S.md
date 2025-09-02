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



## 唯一算法分类
**前缀和优化**

---

## 综合分析与结论
### 题解思路与核心难点
所有题解的核心思路都是计算每个中心点的曼哈顿距离范围内的草总和。核心难点在于高效处理菱形区域的边界计算。主要有两种优化思路：

1. **坐标旋转+二维前缀和**  
   - 通过将原坐标系旋转45°，菱形区域转化为矩形区域，利用二维前缀和实现 O(1) 的区间查询。  
   - 关键变量：`now_x = i+j-1`, `now_y = N-i+j` 实现坐标变换，`F` 为旋转后的二维前缀和数组。

2. **逐行一维前缀和**  
   - 对每行维护一维前缀和，枚举每个中心点时，遍历上下 `k` 行，计算每行可覆盖的左右边界。  
   - 时间复杂度 O(n³)，但实现直观，适合小规模数据。

### 算法流程可视化设计
1. **旋转坐标系演示**  
   - **动画方案**：左侧展示原始网格，右侧展示旋转后的坐标系。当用户点击某个中心点时，高亮原始菱形的覆盖区域，并同步在右侧显示对应的矩形区域。  
   - **颜色标记**：原始中心点用红色方块，旋转后的矩形区域用半透明绿色覆盖。  
   - **步进控制**：单步展示坐标变换公式的推导过程。

2. **逐行计算演示**  
   - **网格动态绘制**：用不同颜色表示当前处理的行（黄色高亮），左右边界用红色虚线标记，已累加区域用渐变色填充。  
   - **音效提示**：每次累加一行时播放短促的“滴答”音效，找到最大值时播放胜利音效。

---

## 题解清单 (≥4星)
1. **yxy666（5星）**  
   - 关键亮点：坐标旋转将问题转化为矩形区域求和，时间复杂度 O(n²)，代码简洁高效。  
   - 核心代码片段：  
     ```cpp
     // 坐标变换与二维前缀和计算
     int now_x = i + j - 1, now_y = N - i + j;
     int x_l = max(0, now_x - K - 1), y_l = max(0, now_y - K - 1);
     int x_r = min(2 * N - 1, now_x + K), y_r = min(2 * N - 1, now_y + K);
     ans = max(ans, F[x_r][y_r] - F[x_l][y_r] - F[x_r][y_l] + F[x_l][y_l]);
     ```

2. **Ajwallet（4星）**  
   - 关键亮点：逐行边界处理清晰，代码注释详细，适合理解前缀和基础应用。  
   - 个人心得摘录：*“处理边界，如果小于1直接变成1，大于n直接退出”* 强调边界条件的处理技巧。

---

## 最优思路提炼
**坐标旋转 + 二维前缀和**  
1. 将曼哈顿距离转化为切比雪夫距离，菱形区域变为矩形。  
2. 预处理旋转后的二维前缀和数组，实现 O(1) 区间查询。  
3. 时间复杂度 O(n²)，完美适配 n=400 的数据规模。

---

## 相似题目推荐
1. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)  
   （二维前缀和求最大子矩阵）
2. [P2280 激光炸弹](https://www.luogu.com.cn/problem/P2280)  
   （二维前缀和+固定大小区域最值）
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)  
   （差分数组+前缀和优化）

---

## 复古游戏化动画效果（示例）
### 实现要点
1. **8位像素风格**  
   - 使用 16 色调色板，草地用绿色渐变，中心点用闪烁的奶牛像素图表示。
2. **Canvas 动画**  
   ```javascript
   // 绘制旋转后的坐标系（伪代码）
   function drawRotatedGrid() {
     for (let i = 0; i < 2*N; i++) {
       for (let j = 0; j < 2*N; j++) {
         ctx.fillStyle = getColorByValue(F[i][j]);
         ctx.fillRect(i*8, j*8, 8, 8); // 8x8 像素块
       }
     }
   }
   ```
3. **音效设计**  
   - 移动中心点时播放 `move.wav`（8-bit 风格音效），计算结果时播放 `coin.wav`。

---

## 代码片段（yxy666 核心实现）
```cpp
// 坐标系变换与二维前缀和
for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
        mp[i+j-1][N-i+j] = read();

// 二维前缀和预处理
for (int i = 1; i < 2*N; i++)
    for (int j = 1; j < 2*N; j++)
        F[i][j] = F[i-1][j] + F[i][j-1] - F[i-1][j-1] + mp[i][j];

// 查询旋转后的矩形区域
int x_l = max(0, now_x-K-1), y_l = max(0, now_y-K-1);
int x_r = min(2*N-1, now_x+K), y_r = min(2*N-1, now_y+K);
ans = max(ans, F[x_r][y_r] - F[x_l][y_r] - F[x_r][y_l] + F[x_l][y_l]);
```

---
处理用时：86.45秒