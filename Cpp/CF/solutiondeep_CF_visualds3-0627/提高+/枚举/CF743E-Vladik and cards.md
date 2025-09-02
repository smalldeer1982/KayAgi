# 题目信息

# Vladik and cards

## 题目描述

Vladik was bored on his way home and decided to play the following game. He took $ n $ cards and put them in a row in front of himself. Every card has a positive integer number not exceeding $ 8 $ written on it. He decided to find the longest subsequence of cards which satisfies the following conditions:

- the number of occurrences of each number from $ 1 $ to $ 8 $ in the subsequence doesn't differ by more then $ 1 $ from the number of occurrences of any other number. Formally, if there are $ c_{k} $ cards with number $ k $ on them in the subsequence, than for all pairs of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743E/0c6cc5f621659ae2ddf5ab0dac10dd28e326ec14.png) the condition $ |c_{i}-c_{j}|<=1 $ must hold.
- if there is at least one card with number $ x $ on it in the subsequence, then all cards with number $ x $ in this subsequence must form a continuous segment in it (but not necessarily a continuous segment in the original sequence). For example, the subsequence $ [1,1,2,2] $ satisfies this condition while the subsequence $ [1,2,2,1] $ doesn't. Note that $ [1,1,2,2] $ doesn't satisfy the first condition.

Please help Vladik to find the length of the longest subsequence that satisfies both conditions.

## 说明/提示

In the first sample all the numbers written on the cards are equal, so you can't take more than one card, otherwise you'll violate the first condition.

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
8
8 7 6 5 4 3 2 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
24
1 8 1 2 8 2 3 8 3 4 8 4 5 8 5 6 8 6 7 8 7 8 8 8
```

### 输出

```
17```

# AI分析结果



### 算法分类
**二分答案 + 状态压缩动态规划**

---

### 核心思路与难点分析

#### 关键算法流程
1. **二分答案框架**：枚举每个数字的最小出现次数 `k`，检查是否存在满足条件的子序列长度。
2. **状压DP验证**：用 `dp[i][j]` 表示处理到第 `i` 个位置、状态 `j`（二进制表示已选数字）时，额外多选 `k+1` 次的数字数量。
3. **预处理优化**：提前存储每个数字的出现位置数组 `pos`，通过指针 `cur` 快速定位连续段的起始位置。

#### 解决难点
- **连续性约束**：每个数字必须连续出现，预处理 `pos` 数组后，通过指针快速跳过不连续的位置。
- **次数平衡**：通过二分 `k` 保证所有数字出现次数差 ≤1，状压记录状态，动态规划维护多选次数。

#### 可视化设计
1. **像素动画**：用 8x8 网格表示状态 `j`，每个格子点亮表示选中对应数字。
2. **指针高亮**：在 `pos` 数组中高亮当前处理的连续段（如红色方块表示起始位置，绿色表示结束）。
3. **音效触发**：状态转移成功时播放“滴”声，二分失败时播放低音提示。
4. **自动演示**：模拟二分过程，逐步展示不同 `k` 对应的 DP 状态变化。

---

### 最优思路提炼
1. **二分答案**：确定每个数字的最小出现次数 `k`，将问题转化为可行性检查。
2. **状压状态设计**：`dp[i][j]` 记录位置 `i` 和状态 `j` 下的最大额外次数。
3. **预处理位置数组**：快速定位连续段的起始和结束位置，确保转移高效。
4. **指针跳跃**：通过 `cur` 数组跳过已处理的数字段，避免重复计算。

---

### 代码实现片段
```cpp
int check(int k) {
    memset(cur, 0, sizeof(cur));
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1<<8); ++j) {
            if (dp[i][j] == -1) continue;
            for (int t = 0; t < 8; ++t) {
                if (j & (1 << t)) continue;
                int now = cur[t] + k - 1;
                if (now < pos[t].size()) {
                    dp[pos[t][now]][j | (1<<t)] = max(...);
                }
                if (++now < pos[t].size()) {
                    dp[pos[t][now]][j | (1<<t)] = max(...) + 1;
                }
            }
        }
        cur[a[i]]++;
    }
    // 返回最大可能长度
}
```

---

### 相似题目推荐
1. **CF808E** - 组合背包与贪心结合
2. **洛谷P1273** - 树形DP与状态压缩
3. **洛谷P3959** - 状压DP与图的最短路径

---

### 题解评分（≥4星）

| 题解作者 | 评分 | 亮点 |
|---------|------|-----|
| Jμdge   | ⭐⭐⭐⭐ | 代码清晰，预处理位置数组，处理边界条件严谨 |
| Mihari  | ⭐⭐⭐⭐ | 状态转移方程推导详细，优化指针跳跃逻辑 |
| Celtic  | ⭐⭐⭐⭐ | 二分框架简洁，特殊处理 k=0 的情况 |

---

### 可视化示例
**动画步骤**：
1. **初始化网格**：显示所有数字的位置分布，用不同颜色标记。
2. **二分过程**：滑动条调节 `k`，展示当前检查的连续段长度。
3. **状态转移**：高亮当前处理的数字和状态，显示 `dp` 数组的更新。
4. **结果反馈**：成功时点亮全部8个格子，播放胜利音效。

**复古风格**：使用 8-bit 像素字体，背景音乐为 Chiptune 风格循环，音效采用经典 FC 音色库。

---
处理用时：67.48秒