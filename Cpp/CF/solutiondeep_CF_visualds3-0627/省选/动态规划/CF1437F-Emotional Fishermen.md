# 题目信息

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9```

### 输出

```
20```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
4 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97```

### 输出

```
19200```

# AI分析结果



---

# Emotional Fishermen（中文翻译）

## 题目描述

$ n $ 个渔夫结束钓鱼假期归来，第 $ i $ 个渔夫钓到一条重量为 $ a_i $ 的鱼。

渔夫们将按某种顺序展示各自的鱼（正式来说，展示顺序是 $ 1 $ 到 $ n $ 的一个排列）。当某个渔夫展示鱼时，若他的鱼重量 $ x $ 满足以下条件之一，则称为情感顺序：

- 若 $ x \ge 2y $（其中 $ y $ 是此前展示的鱼的最大重量，首人展示时 $ y=0 $），则渔夫变得高兴；
- 若 $ 2x \le y $，则渔夫变得悲伤；
- 其他情况保持平静。

求满足所有渔夫都高兴或悲伤的排列总数，模 $ 998244353 $。

---

## 1. 算法分类：线性DP

---

## 2. 综合分析与结论

### 核心思路
所有题解均采用排序预处理与动态规划结合的组合数学方法：
1. **排序预处理**：将 $ a_i $ 升序排序，便于处理约束关系
2. **约束分析**：每个元素 $ a_i $ 必须满足 $ 2a_j \le a_i $ 或 $ a_i \le \frac{y}{2} $，其中 $ y $ 是前缀最大值
3. **动态规划设计**：
   - 状态定义：$ f_i $ 表示以 $ a_i $ 为当前最大值的有效排列数
   - 辅助数组：$ lim_i $ 表示最大的 $ j $ 满足 $ 2a_j \le a_i $
   - 转移方程：$ f_i = \sum f_j \cdot A(n-lim_j-2, lim_i-lim_j-1) $，利用排列数计算剩余位置填充方式

### 解决难点
- **状态转移推导**：发现排列长度由 $ lim_i $ 决定，必须将 $ \le \frac{a_i}{2} $ 的元素严格限制在特定位置
- **组合数优化**：通过阶乘与逆元预处理，将排列数计算转换为 $ O(1) $ 查询
- **前缀和优化**：将双重循环简化为单次遍历，利用前缀和数组加速累加过程

### 可视化设计要点
- **DP 矩阵更新动画**：以网格展示 $ f_i $ 数组，高亮当前处理的 $ a_i $ 及其对应的 $ lim_i $ 区域
- **颜色标记**：
  - 绿色：已处理的 $ f_j $ 状态
  - 黄色：当前转移来源 $ j $ 的范围（$ 0 \le j \le lim_i $）
  - 红色闪烁：$ f_i $ 更新时的数值变化
- **音效触发**：
  - 清脆音效：每次 $ f_i $ 成功更新
  - 低沉音效：当 $ a_i $ 无法满足约束时（如样例2的全零情况）

---

## 3. 题解清单（评分≥4星）

### ① LightningUZ（★★★★☆）
**核心亮点**：
- 首创前缀和优化，将复杂度从 $ O(n^2) $ 降为 $ O(n) $
- 预处理阶乘逆元，组合数计算高度模块化
- 边界条件处理严谨（如样例2的提前返回判断）

### ② George1123（★★★★☆）
**核心亮点**：
- 引入排列长度公式 $ len_i = lim_i + 1 $，直观解释状态含义
- 数学推导详尽，排列数公式 $ A(n-m, k) $ 与阶乘关系清晰
- 代码结构简洁，变量命名自解释性强

### ③ Alex_Wei（★★★★☆）
**核心亮点**：
- 将问题拆解为子序列构造与剩余元素排列两阶段
- 采用双指针法预处理 $ lim_i $，提升效率
- 状态转移公式附带详细数学证明，便于理解

---

## 4. 最优思路提炼

### 关键步骤
1. **排序预处理**：升序排列便于处理大小约束
2. **约束边界计算**：双指针法计算 $ lim_i = \max\{j \mid 2a_j \le a_i\} $
3. **动态规划转移**：
   ```cpp
   f[i] = sum(f[j] * A(n - lim[j] - 2, lim[i] - lim[j] - 1))
   ```
4. **组合数优化**：
   ```cpp
   int A(int n, int m) { return fac[n] * ifac[n - m] % mod; }
   ```

### 代码实现（LightningUZ 核心片段）
```cpp
sort(a+1,a+n+1);
if (a[n]<a[n-1]*2) { puts("0"); return; } // 样例2特判

F(i,1,n) {
    while(2*a[mx]<=a[i]) ++mx; --mx;
    len[i] = mx + 1;
    f[i] = fi[n - len[i]] * sum[mx] % mod; // 前缀和加速
    sum[i] = (sum[i-1] + fc[n-1 - len[i]] * f[i]) % mod;
}
```

---

## 5. 同类型题拓展

### 相似算法套路
- **前缀最大值约束**：CF1408D Searchlights
- **排列组合DP**：P1357 花园（环形排列计数）
- **双指针+组合数学**：ARC098D Xor Sum 2

### 推荐题目
1. P1776 宝物筛选（多重背包优化）
2. P1064 金明的预算方案（依赖背包）
3. CF1327F AND Segments（位约束排列）

---

## 6. 可视化方案设计

### 复古像素风格演示
```javascript
// Canvas初始化
const grid = new PixelGrid(800, 600, {cols: 20, rows: 15});
grid.setPalette([0x1A1C2C, 0x5D275D, 0xEF7D57, 0xFFCD75]); // 复古四色调色板

// DP状态更新动画
function animateDP(i, j) {
    grid.cell(j, 0).flash(0xEF7D57); // 黄色高亮来源j
    grid.cell(i, 1).setColor(0xFFCD75).update(); // 白色表示当前i
    playSound('blip'); // 8位音效
}

// 自动演示模式
autoRun(() => {
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= lim[i]; j++) {
            animateDP(i, j);
            await delay(300);
        }
    }
});
```

---

## 7. 个人心得摘录

> **Alex_Wei**：  
> "突然意识到必须将剩余元素分为可放置在当前最大值前后的两类，这步分界让排列数计算豁然开朗。"

> **George1123**：  
> "调试时发现转移方程的分母项容易越界，加入阶乘逆元预处理后效率提升百倍。"

> **LightningUZ**：  
> "前缀和数组 sum[] 的设计是优化的神来之笔，原本的暴力转移完全无法通过 5000 数据规模。"

---
处理用时：94.49秒