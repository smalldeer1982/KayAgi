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



### 题解综合分析
三个题解均采用枚举子三角形顶点+预处理前缀和的思路。其中前两个题解通过行前缀和优化求和操作，时间复杂度为 $O(n^2k)$ 可满足题目要求。第三个题解未优化求和操作，导致时间复杂度为 $O(n^2k^2)$，无法通过。

---

### 精选题解推荐

#### 题解1：Log_x（★★★★★）
**关键亮点**  
1. 预处理行前缀和实现 $O(1)$ 单层求和  
2. 双循环分别处理正/倒三角形，边界判断及时终止无效枚举  
3. 代码简洁高效，变量复用减少内存开销  

**核心代码**  
```cpp
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j) {
        // 处理正三角形
        for (int k = 1; k <= 2*d; ++k) {
            int tx = i + k - 1, ty = j + k - 1;
            if (tx > n || ty > tx) break;
            res += a[tx][ty] - a[tx][j-1]; 
            if (k >= d) CkMax(Ans, res / num);
        }
        // 处理倒三角形
        for (int k = 1; k <= 2*d; ++k) {
            int tx = i - k + 1, ty = j - k + 1;
            if (tx < 1 || ty < 1 || j > tx) break;
            res += a[tx][j] - a[tx][ty-1];
            if (k >= d) CkMax(Ans, res / num);
        }
    }
```
**个人心得**  
通过 `break` 及时终止越界枚举，减少无效计算。预处理前缀和是此类问题的通用优化手段。

---

#### 题解2：lailai0916（★★★★）
**关键亮点**  
1. 将正/倒三角形分离为独立循环，逻辑更清晰  
2. 严格限制枚举范围，减少冗余判断  
3. 显式计算三角形元素个数 $\frac{k(k+1)}{2}$ 增强可读性  

**核心代码**  
```cpp
// 处理正三角形
for (int k=1; k<=n-i+1; k++) {
    sum += a[i+k-1][j+k-1] - a[i+k-1][j-1];
    if (k>=K && k<=2*K) 
        ans = max(ans, sum/(k*(k+1)/2));
}
// 处理倒三角形
for (int k=1; k<=j && k<=i-j+1; k++) {
    sum += a[i-k+1][j] - a[i-k+1][j-k];
    if (k>=K && k<=2*K)
        ans = max(ans, sum/(k*(k+1)/2));
}
```
**边界处理技巧**  
`k <= n-i+1` 和 `k <= j && k <= i-j+1` 确保枚举不越界，避免无效计算。

---

### 最优思路总结
1. **前缀和优化**：预处理每行前缀和，将单层求和复杂度从 $O(k)$ 降为 $O(1)$。  
2. **双向枚举**：分别处理正三角形（从顶点向下扩展）和倒三角形（从顶点向上扩展）。  
3. **剪枝优化**：在枚举边长时，一旦子三角形超出原三角形范围立即 `break`。  
4. **数值计算**：用整数除法避免浮点误差，直接取地板值。

---

### 拓展练习推荐
1. [P1719 寻找最大加权矩形](https://www.luogu.com.cn/problem/P1719)  
   - 二维前缀和的经典应用，求最大子矩阵和。
2. [P2280 激光炸弹](https://www.luogu.com.cn/problem/P2280)  
   - 二维前缀和 + 固定尺寸子矩阵的最值。
3. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   - 一维版本的前缀和/动态规划问题。

---
处理用时：71.89秒