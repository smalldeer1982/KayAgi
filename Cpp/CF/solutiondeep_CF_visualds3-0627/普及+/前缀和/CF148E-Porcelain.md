# 题目信息

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2
```

### 输出

```
9
```

# AI分析结果



## 算法分类
**分组背包**

---

## 题解思路与核心难点

### 核心思路
1. **预处理单层取数**：对每个架子，预先计算取 1~k 个物品时的最大价值。使用前缀和快速计算左右组合。
2. **分组背包**：将每个架子视为物品组，每组内物品的“重量”为取的数量，“价值”为预处理的最大值。最终用分组背包求解取 m 个物品的最大总和。

### 解决难点
- **单层取数优化**：通过枚举左边取 l 个、右边取 r 个（l + r = s），利用前缀和快速计算总和，时间复杂度 O(k²)。
- **背包空间优化**：使用滚动数组或逆序枚举，将二维状态压缩为一维，空间复杂度从 O(nm) 降为 O(m)。

---

## 题解评分（≥4星）

### 1. 作者：wanggiaoxing（⭐⭐⭐⭐⭐）
- **亮点**：代码简洁，分组背包实现清晰，预处理与背包转移分离。
- **优化点**：变量命名可读性稍差，但逻辑紧凑。

### 2. 作者：_Album_（⭐⭐⭐⭐）
- **亮点**：详细注释与思路说明，适合教学，预处理部分使用区间 DP。
- **不足**：区间 DP 实现复杂度略高，但思路新颖。

### 3. 作者：Max_QAQ（⭐⭐⭐⭐）
- **亮点**：前缀和与后缀和分开处理，代码结构清晰，变量命名规范。
- **优化点**：未使用滚动数组，但可读性极佳。

---

## 最优思路提炼
1. **前缀和优化**：对每层物品计算前缀和，快速组合左右取数。
   ```cpp
   sum[i][j] = sum[i][j-1] + a[i][j]; // 前缀和
   max_val = sum_left[l] + sum_right[r]; // 左取 l 个，右取 r 个
   ```
2. **分组背包转移**：
   ```cpp
   for (int i = 1; i <= n; i++)
       for (int j = m; j >= 0; j--)
           for (int k = 0; k <= min(j, max_take); k++)
               dp[j] = max(dp[j], dp[j-k] + pre_max[i][k]);
   ```

---

## 同类题目推荐
1. **P1064 金明的预算方案**（分组背包）
2. **P2014 选课**（树形背包）
3. **P1757 通天之分组背包**（标准分组背包）

---

## 可视化与算法演示

### 核心动画设计
1. **单层预处理**：  
   - **左侧高亮**：蓝色方块表示已选的左端物品，实时显示 `sum_left[l]`。  
   - **右侧高亮**：红色方块表示已选的右端物品，显示 `sum_right[r]`。  
   - **动态合并**：当 `l + r = s` 时，用绿色背景显示当前最大值。

2. **分组背包转移**：  
   - **背包表格**：Canvas 绘制二维表格，横向为总取数 `m`，纵向为架子编号。  
   - **颜色标记**：黄色表示当前更新的 `dp[j]`，箭头指示从 `dp[j-k]` 转移而来。

### 复古像素风格
- **8位音效**：  
  - **点击物品**：8-bit 短音（类似《超级马里奥》金币声）。  
  - **背包更新**：低音鼓点提示状态变化。  
- **自动演示**：按空格键切换“手动步进”与“AI 自动”模式，速度可调。

---

## 关键代码实现
```cpp
// 预处理单层最大价值
for (int i = 1; i <= n; i++) {
    for (int s = 1; s <= k[i]; s++) {
        int max_val = 0;
        for (int l = 0; l <= s; l++) {
            int r = s - l;
            int curr = sum[i][l] + (sum_total[i] - sum[i][k[i]-r]);
            max_val = max(max_val, curr);
        }
        pre_max[i][s] = max_val;
    }
}

// 分组背包
vector<int> dp(m+1, 0);
for (int i = 1; i <= n; i++) {
    for (int j = m; j >= 0; j--) {
        for (int s = 1; s <= min(j, k[i]); s++) {
            dp[j] = max(dp[j], dp[j-s] + pre_max[i][s]);
        }
    }
}
```

---

## 总结
本题通过 **分组背包 + 前缀和预处理** 将复杂取数问题分解为两步，既降低思维难度又保证效率。实现时需注意循环顺序与状态转移的细节，可结合可视化加深对动态规划过程的理解。

---
处理用时：98.17秒