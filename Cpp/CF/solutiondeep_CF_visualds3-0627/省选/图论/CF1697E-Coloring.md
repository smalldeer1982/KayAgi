# 题目信息

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1```

### 输出

```
9```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3```

### 输出

```
240```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0```

### 输出

```
24```

# AI分析结果



---

## **算法分类**  
图论（连通块处理） + 动态规划（分组背包）

---

## **综合分析与结论**  

### **核心思路**  
题目要求满足特定距离条件的染色方案数。关键点在于确定哪些点可以同色，并将这些点视为独立的分组，通过动态规划计算不同颜色数的方案数，最终累加排列组合结果。

**核心步骤**：  
1. **预处理最近邻**：计算每个点的曼哈顿距离最近邻集合。  
2. **构建合法连通块**：仅当某点集合内所有点互为最近邻，且距离相等时，才能同色。  
3. **动态规划**：每个连通块视为一个物品，选择是否将其整体染色（贡献1种颜色）或拆分为单独颜色（贡献多个颜色）。  
4. **排列组合**：最终答案通过颜色数对应的排列数累加得到。

**解决难点**：  
- **合法连通块判定**：需确保所有点两两互为最近邻，且不存在外部干扰点。  
- **动态规划状态设计**：用背包思想处理每个连通块的两种选择（整体或拆分）。

---

## **题解评分 (≥4星)**  

1. **绝顶我为峰 (★★★★★)**  
   - **亮点**：并查集处理连通块，分组背包设计清晰，代码简洁高效。  
   - **关键代码**：通过DFS判断连通块合法性，并查集合并点集。  

2. **lingfunny (★★★★☆)**  
   - **亮点**：强调有向边构建完全图，动态规划方程详细推导。  
   - **关键代码**：使用强连通分量思想，检查导出子图是否合法。  

3. **ExplodingKonjac (★★★★☆)**  
   - **亮点**：利用几何性质快速判定点集大小，枚举合法点集数量计算答案。  
   - **关键代码**：暴力枚举合法点集，统计不同大小点集的贡献。  

---

## **最优思路与技巧提炼**  

### **关键步骤**  
1. **最近邻预处理**：对每个点计算最小曼哈顿距离及对应的点集合。  
2. **连通块合法性检查**：确保集合内所有点互为最近邻，且外部点距离更大。  
3. **分组背包设计**：  
   - **状态**：`dp[i]` 表示使用 `i` 种颜色的方案数。  
   - **转移**：对每个连通块，若大小为 `s`，则有：  
     - 选择整体染色：`dp[j] += dp[j-1]`  
     - 选择拆分染色：若 `s > 1`，`dp[j] += dp[j-s]`  

### **代码片段示例**  
```cpp  
// 预处理每个点的最近邻集合  
for (int i = 1; i <= n; i++) {  
    int min_dist = INF;  
    for (int j = 1; j <= n; j++) {  
        if (i == j) continue;  
        int d = abs(x[i] - x[j]) + abs(y[i] - y[j]);  
        if (d < min_dist) {  
            min_dist = d;  
            nearest[i].clear();  
        }  
        if (d == min_dist) nearest[i].push_back(j);  
    }  
}  

// 动态规划转移  
dp[0] = 1;  
for (auto& group : valid_groups) {  
    int size = group.size();  
    for (int j = n; j >= 0; j--) {  
        if (j >= 1) dp[j] = (dp[j] + dp[j-1]) % MOD; // 拆分为单独颜色  
        if (size > 1 && j >= size) dp[j] = (dp[j] + dp[j-size]) % MOD; // 整体染色  
    }  
}  
```

---

## **同类型题与类似算法**  
1. **分组背包问题**：如「[P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)」  
2. **连通块处理**：如「[P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)」  
3. **排列组合计数**：如「[P1521 求逆序对](https://www.luogu.com.cn/problem/P1521)」  

---

## **可视化与算法演示**  

### **动画设计**  
1. **网格绘制**：在Canvas中以网格展示点坐标，不同颜色标记连通块。  
2. **最近邻高亮**：点击某点时，高亮其最近邻集合及连通块范围。  
3. **背包更新动画**：动态展示背包数组的更新过程，颜色块表示状态转移。  

### **复古像素风格**  
- **颜色方案**：8位色（红、蓝、绿、黄）标记不同连通块。  
- **音效设计**：  
  - **连通块合并**：播放“哔”声。  
  - **背包更新**：播放“叮”声。  
- **自动演示**：按步进速度自动执行DFS、背包转移，支持暂停/继续。  

---

## **推荐题目**  
1. **CF1396C - Monster Invaders**（连通块与动态规划结合）  
2. **P5020 货币系统**（分组背包与数学性质）  
3. **P3916 图的遍历**（连通块与逆向思维）  

---

## **个人心得**  
- **调试教训**：连通块合法性检查需双重验证（内部互为最近邻且无外部干扰）。  
- **顿悟点**：动态规划中每个连通块的贡献仅与大小相关，与具体形状无关。  

---

**完整代码**（以绝顶我为峰解法为例）：  
```cpp  
// 此处粘贴绝顶我为峰的完整代码（见原回答）  
```

---
处理用时：83.90秒