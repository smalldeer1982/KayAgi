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



**算法分类**  
前缀和、枚举

**综合分析与结论**  
本题需在三角形中寻找边长≥k的子三角形（正/倒置），求最大平均值。关键点在于高效计算子三角形和，各题解均采用前缀和优化。最优思路为预处理每行前缀和，枚举顶点并逐层扩展，利用前缀和O(1)计算每层和，总时间复杂度O(n²k)。

**高星题解推荐**  
1. **Log_x (5星)**  
   **关键亮点**：高效利用行前缀和，正/倒三角形统一处理，及时剪枝跳出越界循环。  
   **代码核心**：  
   ```cpp
   for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= i; ++j) {
         // 正三角形：向下扩展
         for (int k = 1; k <= (d << 1); ++k) {
             int tx = i + k - 1, ty = j + k - 1;
             if (tx > n || ty > tx) break;
             res += a[tx][ty] - a[tx][j - 1];
             if (k >= d) CkMax(Ans, res / num);
         }
         // 倒三角形：向上扩展
         for (int k = 1; k <= (d << 1); ++k) {
             int tx = i - k + 1, ty = j - k + 1;
             if (tx < 1 || ty < 1 || j > tx) break;
             res += a[tx][j] - a[tx][ty - 1];
             if (k >= d) CkMax(Ans, res / num);
         }
     }
   ```

2. **lailai0916 (4星)**  
   **关键亮点**：代码结构清晰，正/倒三角形分开处理，显式维护总和与元素个数。  
   **代码核心**：  
   ```cpp
   // 正三角形处理
   for (int k=1; k<=n-i+1; k++) {
       sum += a[i+k-1][j+k-1] - a[i+k-1][j-1];
       if (k >= K) ans = max(ans, sum/(k*(k+1)/2));
   }
   // 倒三角形处理
   for (int k=1; k<=j && k<=i-j+1; k++) {
       sum += a[i-k+1][j] - a[i-k+1][j-k];
       if (k >= K) ans = max(ans, sum/(k*(k+1)/2));
   }
   ```

**最优技巧总结**  
- **行前缀和**：每行预处理前缀和，快速计算任意区间和。  
- **逐层扩展**：枚举顶点后，逐层计算扩展后的子三角形和，避免重复计算。  
- **方向分离**：正/倒三角形分别处理，统一使用行列坐标变换。  
- **剪枝优化**：当扩展超出原三角形边界时立即终止循环。  

**同类题目推荐**  
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（一维前缀和）  
2. [P1719 寻找二维最大子矩阵](https://www.luogu.com.cn/problem/P1719)（二维前缀和）  
3. [P2671 求和](https://www.luogu.com.cn/problem/P2671)（分组前缀和优化）

---
处理用时：60.32秒