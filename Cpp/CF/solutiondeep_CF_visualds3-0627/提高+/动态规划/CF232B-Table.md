# 题目信息

# Table

## 题目描述

John Doe has an $ n×m $ table. John Doe can paint points in some table cells, not more than one point in one table cell. John Doe wants to use such operations to make each square subtable of size $ n×n $ have exactly $ k $ points.

John Doe wondered, how many distinct ways to fill the table with points are there, provided that the condition must hold. As this number can be rather large, John Doe asks to find its remainder after dividing by $ 1000000007 $ $ (10^{9}+7) $ .

You should assume that John always paints a point exactly in the center of some cell. Two ways to fill a table are considered distinct, if there exists a table cell, that has a point in one way and doesn't have it in the other.

## 说明/提示

Let's consider the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232B/8876a3223960f71627c5d6c6a4c6ddb988dcaef6.png) The gray area belongs to both $ 5×5 $ squares. So, if it has one point, then there shouldn't be points in any other place. If one of the white areas has a point, then the other one also must have a point. Thus, there are about $ 20 $ variants, where the point lies in the gray area and $ 25 $ variants, where each of the white areas contains a point. Overall there are $ 45 $ variants.

## 样例 #1

### 输入

```
5 6 1
```

### 输出

```
45```

# AI分析结果



# 题目翻译

## 题目描述

John Doe 有一个 $n×m$ 的表格。他可以在某些单元格中画点，每个单元格最多画一个点。John Doe 希望通过这样的操作，使得表格中每个大小为 $n×n$ 的正方形子表格都恰好包含 $k$ 个点。

John Doe 想知道满足条件的画点方案有多少种。由于结果可能很大，你需要输出其对 $1000000007$（即 $10^9+7$）取模后的值。

两种方案不同，当且仅当存在至少一个单元格，在其中一种方案中画了点，而在另一种方案中没有画点。

## 样例 #1

### 输入

```
5 6 1
```

### 输出

```
45
```

---

# 算法分类：线性DP

---

# 综合分析与结论

## 题解思路与核心难点
### 核心思路
1. **循环规律发现**  
   由于每 $n$ 列形成一组循环，第 $i$ 列与第 $i+kn$ 列的点数必须相同。只需计算前 $n$ 列的方案，即可推导整张表格的方案。
   
2. **动态规划状态设计**  
   - 状态定义：`f[i][j]` 表示前 $i$ 列（考虑所有循环中的等价列）共放 $j$ 个点的方案数。
   - 状态转移：枚举第 $i$ 列放 $t$ 个点，贡献为组合数 $\binom{n}{t}$ 的幂次（由该列出现次数决定）。

3. **组合数幂次预处理**  
   对每个列的出现次数 `cnt_i`，预处理 $\binom{n}{t}^{\text{cnt}_i}$，避免重复计算快速幂。

### 解决难点
- **大数 $m$ 的处理**：通过数学公式直接计算每列的出现次数 `cnt_i = (m-1)/n + (i <= (m-1)%n+1)`，将 $m$ 压缩到 $n$ 的规模。
- **高效状态转移**：使用分组背包思想，每组对应一列的不同点数选择，总复杂度优化为 $O(n^4)$。

---

# 题解清单（≥4星）

## 1. MCAdam（★★★★☆）
- **亮点**  
  - 代码简洁，预处理组合数与幂次分离清晰。
  - 状态转移循环边界处理精确，直接使用三重循环实现分组背包。
- **核心代码**  
  ```cpp
  for(int i=1;i<=n;i++)
    for(int j=0;j<=min(k,i*n);j++)
      for(int t=0;t<=min(j,n);t++)
        f[i][j]=(f[i][j]+f[i-1][j-t]*fp[i][t]%mod)%mod;
  ```

## 2. feecle6418（★★★★☆）
- **亮点**  
  - 预处理幂次时使用统一公式 `(i<=(m-1)%n+1)`，简化计算逻辑。
  - 代码结构紧凑，直接使用 `min(n, q)` 优化循环次数。
- **关键优化**  
  ```cpp
  w[i][j]=Power(c[n][j], (i<=(m-1)%n+1)?(m-1)/n+1:(m-1)/n);
  ```

## 3. ZHR100102（★★★★☆）
- **亮点**  
  - 手绘示意图辅助理解循环规律，直观展示等价列关系。
  - 使用倒序更新背包空间优化，减少内存占用。
- **个人心得**  
  > “发现正方形移动时首尾列点数相同，是解题的关键突破口。”

---

# 最优思路与技巧提炼

## 关键步骤
1. **等价列发现**  
   通过观察样例，发现每 $n$ 列形成循环，转化为处理前 $n$ 列的问题。
2. **数学公式压缩规模**  
   计算列出现次数：`cnt_i = (m-1)/n + (i <= (m-1)%n+1)`。
3. **组合数幂次预处理**  
   对每个可能的点数 $t$，预计算 $\binom{n}{t}^{\text{cnt}_i}$。
4. **分组背包式DP**  
   每列视为一组物品，物品体积为点数 $t$，价值为组合数幂次。

---

# 同类型题与算法套路

## 相似算法套路
- **循环压缩**：将大数问题转化为周期性小规模问题（如 CF1585F Non-equal Neighbours）。
- **组合数幂次优化**：常见于需要重复选择同一组合方案的计数问题（如 LOJ 2023 礼物）。
- **分组背包变种**：处理每组可选多个独立物品的情况（如 P1776 宝物筛选）。

## 推荐练习题
1. **P1776 宝物筛选**（多重背包优化）  
2. **CF1585F Non-equal Neighbours**（循环规律与线性DP）  
3. **LOJ 2023 礼物**（组合数幂次与模运算）

---

# 可视化与算法演示

## 动态规划动画设计
- **网格绘制**：用 Canvas 绘制 $n×k$ 的网格，每个格子表示 `f[i][j]`。
- **颜色标记**：  
  - 当前处理列 `i` 用黄色高亮。
  - 转移来源格子 `j-t` 用蓝色边框标记。
  - 新增贡献值用绿色渐变动画展示。
- **音效设计**：  
  - 状态更新时播放 "滴" 声（8-bit 音效）。
  - 完成一列处理时播放短促上扬音效。

## 复古像素风格实现
```javascript
// 示例代码：绘制 DP 网格
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');
const colors = ['#000', '#0f0', '#00f', '#ff0']; // 黑、绿、蓝、黄

function drawGrid(f) {
  for (let i = 0; i <= n; i++) {
    for (let j = 0; j <= k; j++) {
      ctx.fillStyle = colors[Math.min(f[i][j], 3)];
      ctx.fillRect(i * 20, j * 20, 18, 18);
    }
  }
}
```

---

# 代码实现（核心片段）

## MCAdam 题解核心代码
```cpp
// 预处理组合数
for(int i=1;i<=100;i++) {
  C[i][0]=C[i][i]=1;
  for(int j=1;j<i;j++)
    C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
}

// 计算每列出现次数与幂次
for(int i=1;i<=n;i++)
  for(int j=0;j<=n;j++)
    fp[i][j]=power(C[n][j], (m-1)/n + (i<=(m-1)%n+1));

// DP 转移
f[0][0] = 1;
for(int i=1;i<=n;i++)
  for(int j=0;j<=min(k,i*n);j++)
    for(int t=0;t<=min(j,n);t++)
      f[i][j] = (f[i][j] + f[i-1][j-t] * fp[i][t]) % mod;
```

---
处理用时：100.57秒