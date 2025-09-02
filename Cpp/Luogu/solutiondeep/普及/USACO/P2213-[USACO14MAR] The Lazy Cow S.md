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



### 综合分析与结论
该题的核心是计算菱形区域内的最大值，各题解主要围绕如何高效统计菱形区域和展开。主流解法分为两类：
1. **坐标旋转+二维前缀和**：通过坐标变换将菱形转换为矩形区域，实现O(N²)时间复杂度
2. **行前缀和+逐行处理**：利用行前缀和优化区域统计，时间复杂度O(N³)，但代码更直观

关键优化点在于将曼哈顿距离约束转化为可快速计算的形式，其中坐标旋转的思路最具算法价值。

---

### 高评分题解推荐

#### 1. yxy666（⭐⭐⭐⭐⭐）
**核心亮点**：
- 创新性坐标旋转：将原坐标系(i,j)映射到(i+j-1, n-i+j)，使菱形区域变为矩形
- 二维前缀和高效计算：预处理后可在O(1)时间查询任意矩形区域和
- 时间复杂度O(N²)，完美适配N=400的数据规模

**关键代码解析**：
```cpp
// 坐标映射与预处理
mp[i+j-1][N-i+j] = read(); // 原坐标存入旋转后的位置
F[i][j] = F[i-1][j] + F[i][j-1] - F[i-1][j-1] + mp[i][j]; // 二维前缀和

// 查询旋转后的菱形区域（此时已是矩形）
int x_l = max(0,now_x-K-1), y_l = max(0,now_y-K-1);
ans = max(ans, F[x_r][y_r] - F[x_l][y_r] - F[x_r][y_l] + F[x_l][y_l]);
```

#### 2. 一只野生蒟蒻（⭐⭐⭐⭐）
**核心亮点**：
- 直观的行前缀和实现：每行单独处理前缀和
- 清晰的分层处理：将菱形分为上下两部分处理边界
- 代码可读性强，适合理解问题本质

**关键代码解析**：
```cpp
// 处理菱形的上下两部分
for(int i=x-k; i<=x+k; i++) {
    if(i <= x) { // 上半部分
        l = y - (i-x+k);
        r = y + (i-x+k);
    } else { // 下半部分
        l = y - (x+k-i);
        r = y + (x+k-i);
    }
    t += s[i][min(r,n)] - s[i][max(l,1)-1];
}
```

#### 3. moosssi（⭐⭐⭐⭐）
**核心亮点**：
- 分正/倒三角形处理：将菱形拆解为两个三角形
- 动态调整边界：通过d值控制每行覆盖范围
- 清晰的代码结构，便于调试

**关键代码解析**：
```cpp
// 处理正三角形（上半）
for(int l=i-k; l<=i; l++, d++) {
    int r2 = min(n,j+d);
    sum += h[l][r2] - h[l][max(1,j-d)-1];
}

// 处理倒三角形（下半）
for(int l=i+1; l<=i+k; l++, d--) {
    int r2 = min(n,j+d);
    sum += h[l][r2] - h[l][max(1,j-d)-1];
}
```

---

### 关键思路总结
**坐标转换技巧**：将曼哈顿距离约束下的菱形区域，通过旋转坐标系转换为矩形区域，可利用二维前缀和快速求解。具体映射关系为：
- 原坐标(r,c) → 新坐标(r+c-1, n-r+c)
- 此时曼哈顿距离K的区域转换为边长为2K+1的矩形

**行前缀和优化**：对每行单独计算前缀和，处理菱形区域时按行扫描，动态计算每行的左右边界，时间复杂度O(N³)但实现简单。

---

### 同类题目推荐
1. [P1719 寻找宝藏](https://www.luogu.com.cn/problem/P1719) - 二维前缀和经典应用
2. [P2004 领地选择](https://www.luogu.com.cn/problem/P2004) - 固定区域最大值问题
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 差分与前缀和的综合应用

---

### 心得摘录
1. **yxy666**：旋转坐标系将问题转化为矩形区域，是典型的"降维打击"思维，需熟悉坐标系变换的应用场景
2. **野生蒟蒻**："当数据规模允许时，清晰的O(N³)实现优于难以调试的O(N²)"，提醒算法选择需权衡实现复杂度
3. **Expecto**：在尝试优化时漏判k=2N的特殊情况，强调边界条件测试的重要性

---
处理用时：78.74秒