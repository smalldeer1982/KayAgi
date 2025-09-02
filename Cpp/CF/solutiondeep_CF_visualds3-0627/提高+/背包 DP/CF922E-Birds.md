# 题目信息

# Birds

## 题目描述

Apart from plush toys, Imp is a huge fan of little yellow birds!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/3bbf7144a65fde520de46a3e8b677997bfb55fe8.png)To summon birds, Imp needs strong magic. There are $ n $ trees in a row on an alley in a park, there is a nest on each of the trees. In the $ i $ -th nest there are $ c_{i} $ birds; to summon one bird from this nest Imp needs to stay under this tree and it costs him $ cost_{i} $ points of mana. However, for each bird summoned, Imp increases his mana capacity by $ B $ points. Imp summons birds one by one, he can summon any number from $ 0 $ to $ c_{i} $ birds from the $ i $ -th nest.

Initially Imp stands under the first tree and has $ W $ points of mana, and his mana capacity equals $ W $ as well. He can only go forward, and each time he moves from a tree to the next one, he restores $ X $ points of mana (but it can't exceed his current mana capacity). Moving only forward, what is the maximum number of birds Imp can summon?

## 说明/提示

In the first sample base amount of Imp's mana is equal to $ 12 $ (with maximum capacity also equal to $ 12 $ ). After he summons two birds from the first nest, he loses $ 8 $ mana points, although his maximum capacity will not increase (since $ B=0 $ ). After this step his mana will be $ 4 $ of $ 12 $ ; during the move you will replenish $ 4 $ mana points, and hence own $ 8 $ mana out of $ 12 $ possible. Now it's optimal to take $ 4 $ birds from the second nest and spend $ 8 $ mana. The final answer will be — $ 6 $ .

In the second sample the base amount of mana is equal to $ 1000 $ . The right choice will be to simply pick all birds from the last nest. Note that Imp's mana doesn't restore while moving because it's initially full.

## 样例 #1

### 输入

```
2 12 0 4
3 4
4 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 1000 10 35
1 2 4 5
1000 500 250 200
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 10 7 11
2 10
6 1
```

### 输出

```
11
```

# AI分析结果



---

## 算法分类  
**动态规划/背包DP**

---

## 题解思路与算法要点  
### 核心思路  
1. **状态设计**  
   - 定义 `dp[i][j]` 表示走到第 `i` 棵树时，已召唤 `j` 只鸟的剩余最大魔力值。  
   - 魔力上限可通过 `W + B * j` 计算，无需额外记录。

2. **状态转移**  
   - **转移方程**：  
     \[
     dp[i][j] = \max_{k=0}^{\min(c_i, j)} \left( dp[i-1][j-k] - k \cdot cost_i + X \right)
     \]
   - **约束条件**：  
     - 剩余魔力必须非负（`dp[i-1][j-k] - k * cost_i ≥ 0`）。  
     - 转移后魔力不超过当前上限（`min(dp[i][j], W + B * j)`）。

3. **初始条件**  
   - `dp[0][0] = W`，初始状态未召唤任何鸟，魔力为初始值。

4. **优化手段**  
   - **滚动数组**：仅保留前一棵树的状态，节省空间。  
   - **二进制拆分**：将每棵树的鸟数拆分为二进制组合，优化多重背包转移（如题解3）。  
   - **ST表优化**：快速查询区间最大值（如题解4）。

### 解决难点  
- **状态维度爆炸**：直接记录魔力值会导致状态过多，通过将鸟数作为状态维度，魔力值为值，规避数值过大问题。  
- **多重背包转移**：每棵树的召唤次数为 `c_i`，通过二进制拆分或直接枚举优化时间复杂度。  
- **魔力恢复与上限**：每次移动后恢复 `X` 点魔力，需与当前上限取最小值。

---

## 题解评分 (≥4星)  
1. **开始新的记忆（4星）**  
   - **亮点**：代码简洁，状态转移清晰，适合快速理解核心逻辑。  
   - **不足**：三重循环未优化，时间复杂度较高。  
   ```cpp
   for (int i=1; i<=n; ++i) {
       sum += c[i];
       for (int j=0; j<=sum; ++j)
           for (int k=0; k<=c[i] && k<=j; ++k) {
               if (dp[i-1][j-k] - k*cost[i] < 0) continue;
               dp[i][j] = max(dp[i][j], min(dp[i-1][j-k] -k*cost[i] +x, w+j*b));
           }
   }
   ```

2. **Vsinger_洛天依（4星）**  
   - **亮点**：明确解释魔力上限计算方式，代码逻辑完整。  
   - **不足**：未显式处理滚动数组，空间复杂度较高。  

3. **ChthollyTree（4.5星）**  
   - **亮点**：使用ST表优化区间查询，时间复杂度降至 `O(n log sumc)`。  
   - **代码片段**：  
   ```cpp
   for (int j=0; j<=C; j++) {
       int len = min(j, c[i]);
       f[i][j] = rmq(j-len, j) - j*cost[i] + X;
   }
   ```

---

## 最优思路提炼  
1. **状态设计**：以鸟数为状态维度，魔力值为值，避免数值爆炸。  
2. **转移优化**：  
   - **二进制拆分**：将每棵树的鸟数按二进制分解，转为01背包问题。  
   - **ST表查询**：预处理区间最大值，加速多重背包转移。  
3. **滚动数组**：仅维护当前树和前一棵树的状态，空间复杂度从 `O(n*sumc)` 降为 `O(sumc)`。

---

## 同类型题与算法套路  
- **类似题目**：  
  - **多重背包**：POJ 1742（Coins）  
  - **资源管理DP**：CF 1974E（Money Transfer）  
- **通用套路**：  
  - **状态交换**：当数值范围过大时，将值作为状态，目标作为值。  
  - **多重背包优化**：二进制拆分、单调队列优化。

---

## 推荐洛谷题目  
1. **P1048 采药**（01背包基础）  
2. **P1776 宝物筛选**（多重背包优化）  
3. **P1941 飞扬的小鸟**（动态规划结合状态转移约束）

---

## 个人心得摘录  
- **数据类型**：`cost[i] * k` 可能溢出，需用 `long long`（题解4作者提到因此WA多次）。  
- **初始化**：`memset(dp, -1, ...)` 表示无效状态，转移时需跳过（题解1强调）。  

---

## 可视化与算法演示  
### 动画方案  
1. **核心流程**：  
   - **树与鸟数网格**：Canvas绘制 `n` 棵树和 `sumc` 鸟数的网格，每个单元格表示 `dp[i][j]`。  
   - **颜色标记**：  
     - **当前树**：红色边框。  
     - **有效状态**：绿色填充（`dp[i][j] ≥ 0`）。  
     - **无效状态**：灰色填充（`dp[i][j] = -1`）。  
   - **转移高亮**：当处理 `dp[i][j]` 时，显示从 `dp[i-1][j-k]` 到 `dp[i][j]` 的箭头，并动态更新数值。

2. **复古像素风格**：  
   - **8位调色板**：使用16色像素风格，树用棕色方块，鸟数用蓝色数字。  
   - **音效设计**：  
     - **召唤成功**：8-bit "coin" 音效。  
     - **魔力不足**：短促低音。  
   - **自动演示**：按树顺序自动播放，用户可暂停观察状态转移。

3. **交互设计**：  
   - **步进控制**：按钮控制单步执行或连续播放。  
   - **参数调节**：滑动条调整 `B` 和 `X`，实时观察对结果的影响。

---

## 代码片段（关键逻辑）  
```cpp
// 滚动数组实现（题解2）
memset(f, -1, sizeof(f));
f[0][0] = W;
for (int i=1; i<=n; i++) {
    for (int j=0; j<=sum[i]; j++) {
        int len = min(j, c[i]);
        for (int k=0; k<=len; k++) {
            if (f[i-1][j-k] - C[i]*k >= 0) {
                f[i][j] = max(f[i][j], f[i-1][j-k] + X - C[i]*k);
            }
        }
        f[i][j] = min(f[i][j], W + B*j);
    }
}
```

---

**总结**：本题通过动态规划将鸟数作为状态维度，巧妙规避了直接记录魔力值的高维问题，结合背包优化技巧，是资源管理类DP的典型应用。

---
处理用时：101.67秒