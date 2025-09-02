# 题目信息

# [USACO11NOV] Tile Exchanging S

## 题目描述

Farmer John wants to remodel the floor of his barn using a collection of square tiles he recently purchased from the local square mart store (which of course, only sells square objects).  Unfortunately, he didn't measure the size of the barn properly before making his purchase, so now he needs to exchange some of his tiles for new square tiles of different sizes.

The N square tiles previously purchased by FJ have side lengths A\_1...A\_N. He would like to exchange some of these with new square tiles so that the total sum of the areas of the his tiles is exactly M.  Square mart is currently offering a special deal: a tile of side length A\_i can be exchanged for a new tile of side length B\_i for a cost of

|A\_i-B\_i|\*|A\_i-B\_i| units. However, this deal only applies to 
previously-purchased tiles -- FJ is not allowed to exchange a tile that he has already obtained via exchanging some other tile (i.e., a size-3 tile cannot be exchanged for a size-2 tile, which is then exchanged for a size-1 tile).

Please determine the minimum amount of money required to exchange tiles so that the sum of the areas of the tiles becomes M.  Output -1 if it is impossible to obtain an area of M.



## 说明/提示

There are 3 tiles.  Two are squares of side length 3, and one is a square with side length 1.  We would like to exchange these to make a total area of 6.


Exchange one of the side-3 squares for a side-2 square, and another side-3 square for a side-1 square.  This gives the desired area of 4+1+1=6 and costs 4+1=5 units.

感谢 wjcwinmt 提供翻译


## 样例 #1

### 输入

```
3 6 
3 
3 
1 
```

### 输出

```
5 
```

# AI分析结果



**算法分类**  
动态规划

---

### **题解综合分析**  
所有题解均采用**动态规划**，核心思路为：  
- **状态定义**：`dp[i][j]` 表示前 `i` 个瓷砖组成面积 `j` 的最小代价。  
- **状态转移**：枚举第 `i` 个瓷砖的可能边长 `k`，更新 `dp[i][j + k²]`。  
- **初始化**：`dp[0][0] = 0`，其他初始为极大值，确保无效状态不被选中。  

**解决难点**：  
1. **状态转移的正确性**：需保证枚举的 `k` 合法（`k² ≤ j`）。  
2. **无效状态过滤**：仅在前驱状态有效时更新当前状态。  
3. **空间优化**：部分题解尝试一维数组优化，但需注意循环顺序。  

---

### **精选题解与关键代码**  

#### 1. **作者：Meowco**（⭐⭐⭐⭐）  
**亮点**：  
- 明确前驱状态有效性检查（`if (dp[i-1][j] != inf)`），避免无效转移。  
- 清晰的循环边界控制（`k * k + j <= m`）。  

**核心代码**：  
```cpp
for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++)
        if (dp[i - 1][j] != inf)
            for (int k = 1; k * k + j <= m; k++) {
                int x = abs(a[i] - k);
                dp[i][j + k * k] = min(dp[i][j + k * k], dp[i - 1][j] + x * x);
            }
```

#### 2. **作者：_cmh**（⭐⭐⭐⭐）  
**亮点**：  
- 初始化 `dp[0][0] = 0`，其他为极大值，逻辑严谨。  
- 使用 `k <= sqrt(j)` 优化枚举范围。  

**核心代码**：  
```cpp
for(int i=1;i<=n;i++)
    for(int j=0;j<=m;j++)
        for(int k=0;k<=sqrt(j);k++)
            dp[i][j]=min(dp[i][j],dp[i-1][j-k*k]+abs(a[i]-k)*abs(a[i]-k));
```

#### 3. **作者：Water_Cows**（⭐⭐⭐⭐）  
**亮点**：  
- 代码简洁，使用 `memset` 初始化极大值。  
- 正确处理边界条件（输出 `-1` 的判断）。  

**核心代码**：  
```cpp
memset(f, 0x3f, sizeof(f));
f[0][0] = 0;
for(int i=1; i<=n; i++)
    for(int j=0; j<=m; j++)
        for(int k=0; k*k<=j; k++)
            f[i][j] = min(f[i][j], f[i-1][j-k*k] + (a[i]-k)*(a[i]-k));
```

---

### **最优关键思路**  
1. **状态设计**：二维数组表示前 `i` 个物品达到面积 `j` 的最小代价。  
2. **枚举策略**：对每个瓷砖的边长 `k` 枚举，确保 `k² ≤ 剩余面积`。  
3. **无效状态过滤**：仅当 `dp[i-1][j]` 有效时更新，避免错误累加。  

---

### **拓展与举一反三**  
- **同类问题**：背包问题变种（如完全背包、多重背包）。  
- **类似题目**：  
  1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)（01背包）  
  2. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)（完全背包）  
  3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)（依赖背包）  

---

### **个人心得摘录**  
- **初始化陷阱**：`dp[0][0]` 必须初始化为 `0`，否则后续状态无法正确转移。  
- **枚举优化**：限制 `k` 的范围为 `k² ≤ j`，避免无效枚举。  
- **代码可读性**：使用 `abs(a[i]-k)` 而非 `a[i]-k`，防止负数平方干扰逻辑。

---
处理用时：61.74秒