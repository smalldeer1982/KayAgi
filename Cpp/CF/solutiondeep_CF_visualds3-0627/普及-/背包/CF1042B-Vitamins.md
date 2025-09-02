# 题目信息

# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
10 AB
15 BA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B
```

### 输出

```
13
```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

### 输出

```
250
```

## 样例 #5

### 输入

```
2
5 BA
11 CB
```

### 输出

```
16
```

# AI分析结果



# Vitamins 题解分析

## 算法分类
动态规划（状态压缩）

---

## 题解思路与核心难点

### 核心思路
将维生素组合（A/B/C）转化为二进制状态，用动态规划求解覆盖所有维生素的最小花费。例如：
- A（001）-> 1
- B（010）-> 2
- C（100）-> 4
目标状态为 111（7）。

### 解决难点
1. **状态表示**：如何将维生素组合编码为可处理的状态。
2. **转移方程**：合并两个果汁的状态时通过按位或操作（`|`）实现维生素集合的合并。
3. **初始化与边界**：初始状态 `f[0] = 0`，其他状态初始化为极大值。

### 题解对比
| 方法               | 时间复杂度 | 空间复杂度 | 扩展性                     |
|--------------------|------------|------------|---------------------------|
| 状压DP（背包）     | O(n)       | O(1)       | 易扩展到更多维生素类型     |
| 暴力枚举组合       | O(1)       | O(1)       | 仅适用于固定3种维生素      |
| 三维状态DP         | O(n)       | O(n)       | 状态维度随维生素种类指数增长 |
| 预处理+组合数学    | O(n)       | O(1)       | 依赖组合覆盖的逻辑完整性   |

---

## 题解评分（≥4星）

1. **ZigZagKmp（5星）**
   - 思路清晰：将问题转化为状态压缩背包问题。
   - 代码简洁：仅需 20 行核心代码。
   - 优化程度：O(n) 时间复杂度，无需预处理。
   ```cpp
   for(int i=1;i<=n;++i) {
     for(int j=7;j>=0;--j) {
       f[j|pv[i]] = min(f[j|pv[i]], f[j]+w[i]);
     }
   }
   ```

2. **览遍千秋（4星）**
   - 直观暴力：枚举所有可能的组合（如 A+B+C、AB+C 等）。
   - 可读性强：直接处理每种维生素组合的最小价格。
   ```cpp
   ans = min(abcm, min(am+bm+cm, min(abm+cm, ... )));
   ```

3. **周子衡（4星）**
   - 状态明确：三维布尔数组表示维生素需求是否满足。
   - 空间优化：滚动数组降低空间复杂度。
   ```cpp
   for(int A=1; A>=0; A--) {
     for(int B=1; B>=0; B--) {
       for(int C=1; C>=0; C--) {
         // 状态转移
       }
     }
   }
   ```

---

## 最优思路提炼
1. **状态压缩**：用 3 位二进制表示维生素集合，状态数仅 8 种。
2. **动态规划转移**：通过 `j | pv[i]` 合并状态，保证维生素覆盖。
3. **逆向遍历状态**：避免同一果汁被重复选取（类似 01 背包优化）。

---

## 同类型题推荐
1. **洛谷 P1896**：状态压缩 DP 的代表题（互不侵犯）。
2. **LeetCode 698**：集合划分问题（Partition to K Equal Sum Subsets）。
3. **Codeforces 8C**：状压 DP 优化（枚举子集）。

---

## 可视化设计

### 算法演示方案
1. **状态网格**：
   - 8x8 像素网格表示当前状态（行：当前状态，列：新果汁状态）。
   - 颜色标记：绿色（已更新）、红色（未更新）、黄色（当前操作）。

2. **动画流程**：
   ```plaintext
   Step 1: 初始化 f[0]=0，其他为 ∞
   Step 2: 遍历果汁 i=1 到 n
     遍历状态 j=7 downto 0:
       if f[j] + w[i] < f[j|pv[i]]:
         更新 f[j|pv[i]]，触发闪光特效
   ```

3. **复古像素风格**：
   - **调色板**：深蓝（背景）、绿（有效状态）、红（无效状态）。
   - **音效**：8-bit 音效（状态更新：短促 "beep"，完成：胜利音效）。

4. **交互功能**：
   - **速度控制**：滑块调节遍历速度（10ms~1000ms/步）。
   - **单步调试**：按空格键逐步执行状态转移。

---

## 核心代码实现
```cpp
// 状态压缩 DP 核心代码
int f[8];
memset(f, 0x3f, sizeof(f));
f[0] = 0;
for (int i = 1; i <= n; i++) {
  int vit = 0;
  for (char c : s[i]) {
    if (c == 'A') vit |= 1;
    if (c == 'B') vit |= 2;
    if (c == 'C') vit |= 4;
  }
  for (int j = 7; j >= 0; j--) {
    f[j | vit] = min(f[j | vit], f[j] + cost[i]);
  }
}
cout << (f[7] < INF ? f[7] : -1);
```

---

## 个人心得摘录
- **Viston 的调试经验**：WA 后发现未考虑两种两维生素果汁的组合（如 AB + BC）。
- **ZigZagKmp 的优化**：逆向遍历状态避免重复选择同一果汁，类似 01 背包的空间优化。

---

## 扩展思考
若维生素种类扩展到 10 种，状态数将达 2^10=1024，仍可用状压 DP 在 O(n·2^k) 时间内求解，而暴力枚举组合将不可行。

---
处理用时：74.69秒