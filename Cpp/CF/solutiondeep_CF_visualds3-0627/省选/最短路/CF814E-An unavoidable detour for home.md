# 题目信息

# An unavoidable detour for home

## 题目描述

Those unwilling to return home from a long journey, will be affected by the oddity of the snail and lose their way. Mayoi, the oddity's carrier, wouldn't like this to happen, but there's nothing to do with this before a cure is figured out. For now, she would only like to know the enormous number of possibilities to be faced with if someone gets lost.

There are $ n $ towns in the region, numbered from $ 1 $ to $ n $ . The town numbered $ 1 $ is called the capital. The traffic network is formed by bidirectional roads connecting pairs of towns. No two roads connect the same pair of towns, and no road connects a town with itself. The time needed to travel through each of the roads is the same. Lost travelers will not be able to find out how the towns are connected, but the residents can help them by providing the following facts:

- Starting from each town other than the capital, the shortest path (i.e. the path passing through the minimum number of roads) to the capital exists, and is unique;
- Let $ l_{i} $ be the number of roads on the shortest path from town $ i $ to the capital, then $ l_{i}>=l_{i-1} $ holds for all $ 2<=i<=n $ ;
- For town $ i $ , the number of roads connected to it is denoted by $ d_{i} $ , which equals either $ 2 $ or $ 3 $ .

You are to count the number of different ways in which the towns are connected, and give the answer modulo $ 10^{9}+7 $ . Two ways of connecting towns are considered different if a pair $ (u,v) $ ( $ 1<=u,v<=n $ ) exists such there is a road between towns $ u $ and $ v $ in one of them but not in the other.

## 说明/提示

In the first example, the following structure is the only one to satisfy the constraints, the distances from towns $ 2,3,4 $ to the capital are all $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/41aec6960c240a1fb09480a0a613ecf71bad9b6b.png)In the second example, the following two structures satisfy the constraints.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/5dfe5b5d19d9938739604a89ad14ef6620891ff1.png)

## 样例 #1

### 输入

```
4
3 2 3 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 3 3 2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
2 2 2 2 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
20
2 2 2 2 3 2 3 2 2 2 2 2 2 2 2 2 2 3 3 2
```

### 输出

```
82944
```

# AI分析结果



# An unavoidable detour for home 题解分析

## 算法分类
动态规划（DP）与组合数学

---

## 题解思路与核心难点

### 核心思路
1. **分层结构**：将图按到1号点的最短路长度分层，每层节点编号连续。
2. **动态规划状态**：
   - `f[i][j]` 表示前i个点中，最后j个点与i在同一层的方案数。
   - `g[i][j][k]` 表示当前层有i个点，上一层剩余j个度数为2的点、k个度数为3的点的方案数。
3. **组合数学处理**：同层内部连边需考虑环、链等结构，通过预处理避免重复计算。

### 解决难点
- **同层边合法性**：确保同层边不形成奇环或破坏最短路唯一性。
- **状态转移方程**：通过分层递推，处理度数的消耗与转移关系。
- **复杂度优化**：通过预处理组合数和排列数，将复杂度优化至O(n³)。

---

## 题解评分（≥4星）

1. **Karry5307（4.5星）**  
   - 亮点：完整推导状态转移方程，预处理`g`数组逻辑清晰，代码结构规范。
   - 代码：使用三维数组预处理层间转移，主DP逻辑简洁。

2. **CXY07（4星）**  
   - 亮点：引入容斥优化同层边计算，降低时间复杂度。
   - 代码：通过`v_s`预处理容斥系数，实现高效组合计算。

3. **Styx（4星）**  
   - 亮点：详细解释状态转移的组合意义，便于理解。
   - 代码：明确分层处理逻辑，注释丰富。

---

## 最优思路提炼

### 关键技巧
1. **分层DP**：将图的构造分解为逐层扩展，利用`f[i][j]`记录当前层状态。
2. **预处理`g`数组**：  
   - 处理同层边时，通过组合数计算合法连边方式（如环的排列公式）。
   - 状态转移方程：
     ```text
     g[i][j][k] = j*g[i-1][j-1][k] + k*g[i-1][j+1][k-1]
     ```
3. **度数分配**：将度数拆分为树边贡献（固定1度）和同层边贡献（剩余度数）。

### 代码核心片段
```cpp
// 预处理g数组（Karry5307）
g[0][0][0] = 1;
for (int i=0; i<=n; i++)
for (int j=0; j<=n; j++)
for (int k=0; k<=n; k++) {
    if (i == 0) {
        if (j == 0) { // 处理全3度点连环
            for (int l=3; l<=k; l++)
                g[0][0][k] += ... // 组合数计算环排列
        } else { // 处理混合度数
            if (j >= 2) g[i][j][k] += (j-1)*g[i][j-2][k];
            if (k >= 1) g[i][j][k] += k*g[i][j][k-1];
        }
    } else { // 处理非最后一层
        if (j >= 1) g[i][j][k] += j*g[i-1][j-1][k];
        if (k >= 1) g[i][j][k] += k*g[i-1][j+1][k-1];
    }
}
```

---

## 类似题目推荐
1. **P4258 [WC2016]挑战NPC**  
   - 图的构造与度数约束，需分层处理。
2. **P4436 [HNOI/AHOI2018]游戏**  
   - 最短路相关计数问题，结合DP优化。
3. **P6775 [NOI2020]制作菜品**  
   - 组合数学与动态规划结合的高难度计数问题。

---

## 可视化设计

### 动画方案
1. **分层展示**：  
   - 用不同颜色方块表示不同层，动态扩展层数。
   - 高亮当前处理的层和上一层的连接边。

2. **状态转移演示**：  
   - 显示`f[i][j]`和`g[i][j][k]`的值变化，用箭头表示转移方向。
   - 示例：当处理第i层时，用闪烁效果展示`g`数组的更新步骤。

3. **像素风格实现**：  
   - **Canvas绘制**：每层用8位色块（如绿色表示当前层，蓝色表示上一层）。
   - **音效**：在状态转移时播放短促“滴”声，错误时播放“哔”声。
   - **自动演示**：按步长自动推进算法，允许暂停/调整速度。

### 交互设计
- **控制面板**：包含播放/暂停、步进按钮、速度滑块。
- **状态面板**：实时显示`f`和`g`的当前值，高亮变化的元素。

---

## 个人心得摘录
- **调试教训**：初始未考虑同层奇环的排除，导致计数错误。需严格证明边合法性。
- **优化顿悟**：通过预处理组合数，将O(n⁵)暴力优化至O(n³)，显著提升效率。

---

通过分层动态规划与组合数学的巧妙结合，本题解在O(n³)复杂度内高效解决了复杂图的计数问题，其思路可推广至类似分层构造场景。

---
处理用时：65.67秒