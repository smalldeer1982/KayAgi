# 题目信息

# Right Triangles

## 题目描述

You are given a $ n×m $ field consisting only of periods ('.') and asterisks ('\*'). Your task is to count all right triangles with two sides parallel to the square sides, whose vertices are in the centers of '\*'-cells. A right triangle is a triangle in which one angle is a right angle (that is, a 90 degree angle).

## 样例 #1

### 输入

```
2 2
**
*.
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
*..*
.**.
*.**
```

### 输出

```
9
```

# AI分析结果



# Right Triangles

## 题目描述

给定一个 $n×m$ 的网格，每个格子为句点（'.'）或星号（'*'）。要求统计所有满足以下条件的直角三角形的数量：  
1. 直角三角形的三个顶点均为星号  
2. 两条直角边分别平行于网格的边  

## 样例解释

**样例1**：  
输入为 2x2 网格：  
**  
*.  
输出为 1。解释：仅存在一个以三个星号构成的直角三角形。  

**样例2**：  
输入为 3x4 的复杂网格，输出为 9。  

---

**算法分类**：组合数学  

---

## 题解分析与结论

### 核心思路  
所有题解均采用以下思路：  
1. **预处理统计**：记录每行、每列中的星号数量（记为 $row[i]$ 和 $col[j]$）。  
2. **枚举直角顶点**：遍历每个星号点 $(i,j)$，其贡献的三角形数量为 $(row[i]-1) \times (col[j]-1)$。  
3. **累加求和**：所有星号点的贡献之和即为答案。  

**关键证明**：  
- 每个星号点作为直角顶点时，水平方向可选 $row[i]-1$ 个点（同一行其他星号），垂直方向可选 $col[j]-1$ 个点（同一列其他星号）。  
- 根据乘法原理，这两个方向的点可两两组合形成不同的三角形。  

**难点对比**：  
- **理解贡献公式**：需明确每个星号点的组合意义，而非直接暴力枚举三个点。  
- **数据范围处理**：当 $n,m=1000$ 时，答案最大可达 $10^{12}$，必须使用 `long long`。  

**最优技巧**：  
- 预处理行、列星号数，将时间复杂度从 $O(nm(n+m))$ 优化至 $O(nm)$。  
- 利用组合数学思想，避免暴力枚举所有可能三角形。  

---

## 精选题解

### 1. 作者：codeLJH114514（5星）  
**关键亮点**：  
- 详细列出数据范围分析的坑点，强调 `long long` 的必要性。  
- 代码可读性高，变量命名清晰（如 `count_x`, `count_y`）。  

**核心代码**：  
```cpp
int64_t ans = 0; // 明确使用 64 位整数
for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= m; j++)
        if (mp[i][j] == '*') 
            ans += (count_x[i] - 1) * (count_y[j] - 1);
```

### 2. 作者：Hisaishi_Kanade（4星）  
**关键亮点**：  
- 通过图形示例辅助解释贡献公式，增强直观理解。  
- 包含输入加速优化（`getchar` 快速读入）。  

**代码片段**：  
```cpp
for(int i=1;i<=n;getchar(),i++) // 跳过换行符
    for(int j=1;j<=m;j++){
        s[i][j]=c=getchar();
        if(c=='*') ++row[i], ++col[j];
    }
```

### 3. 作者：songhongyi（4星）  
**关键亮点**：  
- 代码简洁，变量命名规范（`cntx`, `cnty` 对应行、列计数）。  
- 强调与类似题目（P6355）的关联性。  

**核心实现**：  
```cpp
long long ans = 0;
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        if (map[i][j] == '*')
            ans += (cntx[i] - 1) * (cnty[j] - 1);
```

---

## 拓展与练习

**同类问题推荐**：  
1. [P2181 对角线](https://www.luogu.com.cn/problem/P2181) - 组合数学公式应用。  
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 前缀和与计数结合。  
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144) - BFS 与组合计数结合。  

**调试心得**（摘自题解）：  
> "不开 `long long` 见祖宗！当全为星号时，答案达到 $999 \times 999 \times 10^6$，必须用 64 位整数。" —— 来自 codeLJH114514 的题解。

---
处理用时：58.41秒