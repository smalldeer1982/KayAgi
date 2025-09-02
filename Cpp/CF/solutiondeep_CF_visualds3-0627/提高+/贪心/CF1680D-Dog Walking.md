# 题目信息

# Dog Walking

## 题目描述

You are walking with your dog, and now you are at the promenade. The promenade can be represented as an infinite line. Initially, you are in the point $ 0 $ with your dog.

You decided to give some freedom to your dog, so you untied her and let her run for a while. Also, you watched what your dog is doing, so you have some writings about how she ran. During the $ i $ -th minute, the dog position changed from her previous position by the value $ a_i $ (it means, that the dog ran for $ a_i $ meters during the $ i $ -th minute). If $ a_i $ is positive, the dog ran $ a_i $ meters to the right, otherwise (if $ a_i $ is negative) she ran $ a_i $ meters to the left.

During some minutes, you were chatting with your friend, so you don't have writings about your dog movement during these minutes. These values $ a_i $ equal zero.

You want your dog to return to you after the end of the walk, so the destination point of the dog after $ n $ minutes should be $ 0 $ .

Now you are wondering: what is the maximum possible number of different integer points of the line your dog could visit on her way, if you replace every $ 0 $ with some integer from $ -k $ to $ k $ (and your dog should return to $ 0 $ after the walk)? The dog visits an integer point if she runs through that point or reaches in it at the end of any minute. Point $ 0 $ is always visited by the dog, since she is initially there.

If the dog cannot return to the point $ 0 $ after $ n $ minutes regardless of the integers you place, print -1.

## 样例 #1

### 输入

```
3 2
5 0 -4```

### 输出

```
6```

## 样例 #2

### 输入

```
6 4
1 -2 0 3 -4 5```

### 输出

```
7```

## 样例 #3

### 输入

```
3 1000000000
0 0 0```

### 输出

```
1000000001```

## 样例 #4

### 输入

```
5 9
-7 -3 8 12 0```

### 输出

```
-1```

## 样例 #5

### 输入

```
5 3
-1 0 3 3 0```

### 输出

```
7```

## 样例 #6

### 输入

```
5 4
0 2 0 3 0```

### 输出

```
9```

# AI分析结果



### 综合分析与结论

**题目核心**：通过替换数组中的0为[-k, k]的整数，使得最终总和为0，并最大化前缀和数组的极差（max(s) - min(s) + 1）。

**核心难点**：
1. **总和归零条件**：替换后的数组总和必须为0，需动态平衡区间内外的调整范围。
2. **极差最大化**：需要找到最优的区间，使得其内部和与外部和的可调整范围最大化极差。

**题解思路统一性**：所有题解均采用枚举区间（O(n²)）的策略，计算区间内外的和调整范围，通过数学约束确保总和为0，并取极差最大值。

**贪心策略**：在枚举的区间内，尽可能让替换的0取最大绝对值（k或-k），从而使得该区间的和达到极值，同时区间外的调整范围满足总和为0的条件。

---

### 题解评分（≥4星）

1. **CGDGAD（4星）**
   - **亮点**：直接枚举区间，代码简洁，逻辑清晰。通过`sum + cnt*k`和`sum - cnt*k`快速计算极值。
   - **代码**：关键逻辑仅需两轮比较，高效且易理解。

2. **I_am_Accepted（4星）**
   - **亮点**：预处理极值情况，分情况讨论区间内外调整范围。通过`min/max`函数约束极差。
   - **心得**：通过“盒子放球”模型解释调整范围，直观性强。

3. **daniEl_lElE（4星）**
   - **亮点**：预处理前缀和的最大/最小值，分三段处理方向。枚举端点快速计算极差。
   - **彩蛋**：提供易错点提醒，如初始化`maxv=0`而非1。

---

### 最优思路提炼

1. **枚举区间**：遍历所有可能的区间[i,j]，计算区间内和与0的调整范围。
2. **数学约束**：
   - 区间内和为`sum`，含`cnt`个0，可调整范围为`sum ± cnt*k`。
   - 区间外和为`total - sum`，含剩余0的调整范围为`(total - sum) ± (total_cnt - cnt)*k`。
3. **极差计算**：取`min(区间内极大值, 区间外极小绝对值)`或`min(区间内极小绝对值, 区间外极大值)`的最大值。
4. **总和归零**：通过调整后的总和的相反数必须落在区间外的可调整范围内。

---

### 同类型题与算法套路

**常见场景**：
- 极差最大化：如最大子数组和、最长波动子序列。
- 动态调整范围：如背包问题中的容量限制，区间调度中的资源分配。

**通用解法**：
1. **前缀和极值枚举**：适用于需要计算区间贡献的问题。
2. **数学约束优化**：通过预处理和范围计算快速验证可行性。

---

### 推荐题目

1. **洛谷 P1115**：最大子段和（基础极差模型）。
2. **洛谷 P4550**：收集邮票（动态调整与极值结合）。
3. **洛谷 P4095**：[HEOI2013] Eden的新背包问题（多重约束下的极值优化）。

---

### 个人心得摘录

- **daniEl_lElE**：初始化`maxv=0`而非1，避免Hack数据（如全0时初始化为1会错误）。
- **I_am_Accepted**：将0的调整范围视为“盒子容量”，用`min/max`约束极差。
- **Yasuraoka_Hanabi**：极差计算需考虑区间内外反向调整，避免遗漏情况。

---

### 可视化与算法演示

**核心贪心过程动画设计**：
1. **像素网格**：用Canvas绘制前缀和变化，当前区间[i,j]高亮为红色。
2. **动态调整**：滑块控制k值，实时显示极差变化。
3. **音效提示**：
   - **选择区间**：8-bit音效（如“哔”声）。
   - **极差更新**：上扬音调（如“叮”声）。
4. **自动模式**：AI逐步枚举区间，显示极差最大值的变化过程。

**复古游戏化设计**：
- **背景音乐**：循环播放8-bit风格BGM。
- **积分系统**：每找到更优解增加积分，连击奖励特效。
- **关卡模式**：将测试样例作为关卡，用户需通过调整k值达成目标极差。

---

### 代码片段（CGDGAD题解核心）

```cpp
int max = -1;
for (int l = 1; l <= n; l++) {
    for (int r = l; r <= n; r++) {
        int sum = p[r] - p[l - 1], cnt = d[r] - d[l - 1];
        int lSum = p[n] - sum, lCnt = d[n] - cnt;
        // 计算两种极端情况下的极差
        max = std::max(max, std::min(abs(sum + cnt * k), abs(lSum - lCnt * k)));
        max = std::max(max, std::min(abs(sum - cnt * k), abs(lSum + lCnt * k)));
    }
}
printf("%lld\n", max + 1);
```

**核心逻辑**：枚举区间，计算内部取±k时的极值，并与外部调整范围取最小值，确保总和为0。

---
处理用时：68.22秒