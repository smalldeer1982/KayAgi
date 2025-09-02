# 题目信息

# Quests

## 题目描述

Monocarp is playing a computer game. In order to level up his character, he can complete quests. There are $ n $ quests in the game, numbered from $ 1 $ to $ n $ .

Monocarp can complete quests according to the following rules:

- the $ 1 $ -st quest is always available for completion;
- the $ i $ -th quest is available for completion if all quests $ j < i $ have been completed at least once.

Note that Monocarp can complete the same quest multiple times.

For each completion, the character gets some amount of experience points:

- for the first completion of the $ i $ -th quest, he gets $ a_i $ experience points;
- for each subsequent completion of the $ i $ -th quest, he gets $ b_i $ experience points.

Monocarp is a very busy person, so he has free time to complete no more than $ k $ quests. Your task is to calculate the maximum possible total experience Monocarp can get if he can complete no more than $ k $ quests.

## 说明/提示

In the first test case, one of the possible quest completion sequences is as follows: $ 1, 1, 2, 3, 2, 4, 4 $ ; its total experience is equal to $ \underline{4} + 1 + \underline{3} + \underline{1} + 1 + \underline{2} + 1 = 13 $ (the underlined numbers correspond to the instances when we complete a quest for the first time).

In the second test case, one of the possible quest completion sequences is as follows: $ 1, 1 $ ; its total experience is equal to $ \underline{1} + 3 = 4 $ .

In the third test case, one of the possible quest completion sequences is as follows: $ 1, 2, 2, 2, 3 $ ; its total experience is equal to $ \underline{3} + \underline{2} + 3 + 3 + \underline{4} = 15 $ .

## 样例 #1

### 输入

```
4
4 7
4 3 1 2
1 1 1 1
3 2
1 2 5
3 1 8
5 5
3 2 4 1 4
2 3 1 4 7
6 4
1 4 5 4 5 10
1 5 1 2 5 1```

### 输出

```
13
4
15
15```

# AI分析结果



# 题目内容
## 题目描述

Monocarp 正在玩一款电脑游戏。为了升级他的角色，他需要完成任务。游戏中有 $n$ 个任务，编号从 $1$ 到 $n$。

Monocarp 完成任务的规则如下：
- 第 $1$ 个任务始终可以完成；
- 只有当所有编号小于 $i$ 的任务都至少完成一次时，第 $i$ 个任务才能被完成。

注意：Monocarp 可以多次完成同一个任务。

每次完成任务时，角色会获得一定经验值：
- 第一次完成第 $i$ 个任务时，获得 $a_i$ 点经验；
- 后续每次完成第 $i$ 个任务时，获得 $b_i$ 点经验。

Monocarp 最多有 $k$ 次完成任务的机会。请计算他最多能获得的总经验值。

---

# 题解综合分析

## 核心思路总结
所有题解均基于以下贪心策略：
1. **枚举前导任务范围**：假设完成前 $i$ 个任务各至少一次（$i \leq \min(n, k)$）。
2. **计算基础收益**：前 $i$ 个任务的首次完成收益之和 $\sum_{j=1}^i a_j$。
3. **优化剩余次数**：剩余 $k-i$ 次选择当前已解锁任务中 $b_j$ 最大的任务重复完成，总收益为 $max\_b_i \times (k-i)$。
4. **遍历取最大值**：对所有可能的 $i$ 计算总收益，取最大值。

## 最优题解亮点

### 题解作者：tbdsh（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：
- 动态维护前缀和与最大值，无需预处理数组。
- 代码简洁高效，时间复杂度 $O(n)$。
- 处理边界条件（如 $k < n$）清晰。

**核心代码**：
```cpp
int maxx = -1, ans = 0, sum = 0;
for (int i = 1; i <= min(n, k); i++) {
    maxx = max(maxx, b[i]);
    sum += a[i];
    ans = max(ans, sum + (k - i) * maxx);
}
```

---

### 题解作者：infinite2021（⭐️⭐️⭐️⭐️）
**关键亮点**：
- 显式维护前缀最大值数组，逻辑直观。
- 通过分离前缀和与最大值计算，增强可读性。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) 
    maxn[i] = max(maxn[i-1], b[i]);
for (int i = 1; i <= min(n,k); i++) {
    int now = s[i] + max(k-i, 0) * maxn[i];
    res = max(res, now);
}
```

---

## 关键技巧与优化
1. **线性维护前缀信息**：通过单次遍历同时计算前缀和与最大值，避免冗余计算。
2. **贪心选择剩余操作**：剩余次数必定选择当前最大 $b_i$ 的任务，无需复杂决策。
3. **边界处理**：通过 `min(n, k)` 限制枚举范围，避免无效计算。

---

## 拓展与举一反三
**类似问题特征**：
- 需要先完成前置条件（如解锁任务）再优化后续选择。
- 将问题分解为"固定部分+重复最优部分"的贪心结构。

**推荐题目**：
1. [CF1526C2. Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2)  
   （选择药水使生命值非负，涉及前缀和与贪心）
2. [洛谷 P1208. 混合牛奶](https://www.luogu.com.cn/problem/P1208)  
   （贪心选择单价最低的牛奶供应商）
3. [洛谷 P1090. 合并果子](https://www.luogu.com.cn/problem/P1090)  
   （贪心选择最小代价合并，优先队列优化）

---

## 题解中的个人心得
1. **变量命名清晰性**：如 `maxx` 和 `sum` 直观表达含义，提高代码可读性（见 tbdsh 题解）。
2. **避免冗余数组**：动态维护代替预处理数组，减少空间复杂度（对比 myyyIisq2R 题解的 `qzh` 数组）。
3. **边界条件验证**：需注意 `k-i` 可能为负数的情况，通过 `max(k-i, 0)` 处理（见 infinite2021 题解）。

---
处理用时：64.51秒