# 题目信息

# Learning to Paint

## 题目描述

[Pristine Beat - Touhou](https://soundcloud.com/jackaltroy/sets/primordial-beat-pristine-beat)

⠀



Elsie is learning how to paint. She has a canvas of $ n $ cells numbered from $ 1 $ to $ n $ and can paint any (potentially empty) subset of cells.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3277b406102b440ccbe0c485777db99ec89618eb.png)Elsie has a 2D array $ a $ which she will use to evaluate paintings. Let the maximal contiguous intervals of painted cells in a painting be $ [l_1,r_1],[l_2,r_2],\ldots,[l_x,r_x] $ . The beauty of the painting is the sum of $ a_{l_i,r_i} $ over all $ 1 \le i \le x $ . In the image above, the maximal contiguous intervals of painted cells are $ [2,4],[6,6],[8,9] $ and the beauty of the painting is $ a_{2,4}+a_{6,6}+a_{8,9} $ .

There are $ 2^n $ ways to paint the strip. Help Elsie find the $ k $ largest possible values of the beauty of a painting she can obtain, among all these ways. Note that these $ k $ values do not necessarily have to be distinct. It is guaranteed that there are at least $ k $ different ways to paint the canvas.

## 说明/提示

In the first test case, Elsie can either paint the only cell or not paint it. If she paints the only cell, the beauty of the painting is $ -5 $ . If she chooses not to paint it, the beauty of the painting is $ 0 $ . Thus, the largest beauty she can obtain is $ 0 $ and the second largest beauty she can obtain is $ -5 $ .

Below is an illustration of the third test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3d3d08bddad77d78ec4518a724cf3c2c6ce9ab10.png)

## 样例 #1

### 输入

```
4
1 2
-5
2 4
2 -3
-1
3 8
2 4 3
1 3
5
6 20
0 -6 -3 0 -6 -2
-7 -5 -2 -3 -4
7 0 -9 -4
2 -1 1
1 -2
-6```

### 输出

```
0 -5 
2 0 -1 -3 
7 5 4 3 3 2 1 0 
8 8 7 7 5 5 2 2 1 1 1 1 1 1 0 0 0 0 0 -1```

# AI分析结果



**算法分类**  
动态规划 + 优先队列（堆）优化

---

### 题解思路、算法要点与解决难点

#### 核心思路
1. **状态设计**：定义 `f[i]` 为前 `i` 个格子的前 `k` 大美观度值的有序集合。
2. **转移策略**：枚举最后一个连续染色区间 `[j+1, i]`，将 `f[j]` 的所有可能值与 `a[j+1][i]` 相加，合并这些候选值并取前 `k` 大。
3. **优化手段**：使用优先队列高效合并多个有序数组（每个 `f[j]` 的候选值），避免暴力枚举所有可能的 `j`。

#### 解决难点
- **多来源合并**：每个 `f[i]` 可能从任意 `f[j] (j < i)` 转移，直接合并所有候选值的复杂度为 `O(nk)`，不可接受。
- **堆优化**：将每个 `f[j]` 视为一个降序数组，维护堆存储所有 `f[j]` 的当前最大值，每次弹出堆顶并插入该数组的下一个元素，确保每次转移只需 `O(k log n)` 时间。

---

### 最优思路或技巧提炼
1. **堆维护候选值**：将动态规划的转移转化为多个有序数组的合并问题，优先队列用于快速获取最大值。
2. **临时队列处理**：在弹出堆顶元素后，用临时队列 `tmp[j]` 暂存已访问的 `f[j]` 元素，处理完 `f[i]` 后恢复原队列，避免数据丢失。
3. **边界处理**：引入 `j = -1` 处理以 `i` 为右端点的第一个区间的情况，简化代码逻辑。

---

### 题解评分（≥4星）

#### Drind（4.5⭐️）
- **亮点**：思路简洁，代码高效，通过堆优化将复杂度降至 `O(nk log n)`。
- **代码实现**：使用优先队列和临时队列维护候选值，逻辑清晰。

#### Luzhuoyuan（4.0⭐️）
- **亮点**：详细的状态转移描述和边界处理，适合深入理解。
- **实现细节**：通过 `getv()` 和 `tmp` 队列管理 `f[j]` 的弹出与恢复。

#### N1K_J（4.0⭐️）
- **亮点**：代码简洁，直接枚举 `j` 并维护堆，易于实现。
- **关键代码**：
  ```cpp
  q.push({a[j+2][i]+(j<0?0:dp[j][0]),j,0});
  ```

---

### 核心代码实现（Luzhuoyuan 题解片段）
```cpp
for (int i = 1; i <= n; i++) {
    q.push({-1, a[1][i]}); // 处理 j = -1 的区间 [1, i]
    for (int j = 0; j < i; j++) {
        if (!f[j].empty()) {
            int val = getv(j) + a[j + 2][i]; // 从 f[j] 转移
            q.push({j, val});
        }
    }
    // 取出前 k 大值存入 f[i]
    while (!q.empty() && f[i].size() < k) {
        auto [j, v] = q.top(); q.pop();
        f[i].push(v);
        if (j != -1 && !f[j].empty()) {
            int next_val = getv(j) + a[j + 2][i];
            q.push({j, next_val});
        }
    }
    // 恢复 f[j] 的队列
    for (int j = 0; j < i; j++) {
        while (!tmp[j].empty()) {
            f[j].push(tmp[j].front());
            tmp[j].pop();
        }
    }
}
```

---

### 可视化与算法演示设计

#### 动画方案
1. **网格绘制**：将 `n` 个格子绘制为像素网格，染色区间用不同颜色标记。
2. **堆操作高亮**：
   - **当前选中区间**：用闪烁边框标记 `[j+1, i]`。
   - **堆顶元素**：显示 `val = f[j].top() + a[j+1][i]` 的数值和来源 `j`。
3. **队列更新**：每次弹出堆顶后，用箭头动画表示将下一个候选值 `f[j].next()` 加入堆。

#### 复古游戏化效果
- **8位像素风格**：
  - **格子**：16x16 像素块，用绿色（未染色）和红色（染色）表示。
  - **堆状态**：右侧面板以 8-bit 字体显示堆中元素的 `j` 和 `val`。
- **音效**：
  - **弹出堆顶**：短促“哔”声。
  - **插入新值**：低沉“咚”声。
- **自动演示**：按空格键切换自动/手动模式，自动模式下算法以 1 步/秒执行。

---

### 相似题目推荐
1. **P1858 多人背包**：合并前 `k` 优解的动态规划问题。
2. **P1631 序列合并**：优先队列合并有序数组。
3. **CF1843F2 最大子段和（困难版）**：动态维护前 `k` 大值。

---
处理用时：84.31秒