# 题目信息

# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1
```

### 输出

```
5
```

# AI分析结果



# Fragile Bridges 题目描述

你正在玩一个电子游戏，并刚刚进入一个奖励关卡。该关卡的目标是尽可能获得最高分数。你决定必须获得最高分才能离开。

关卡由 $n$ 个平台排成一行，从左到右编号为 $1$ 到 $n$，相邻平台间有 $n-1$ 座桥。每座桥有预先设定的最大通过次数（从一端到另一端视为一次）。

玩家操作流程：
1. 选择一个起始平台。
2. 自由移动，直到无法移动时自动结束。
3. 得分为通过桥的次数总和。

求能确保无法被超越的最高得分。

## 样例 #1
### 输入
```
5
2 1 2 1
```
### 输出
```
5
```

---

### 题解综合分析

各题解核心思路均为动态规划，通过分解路径方向与返回状态进行状态转移。关键技巧在于：
1. 将路径拆分为向左/向右两段独立处理
2. 利用桥的奇偶性计算最大榨取次数
3. 合并左右两段的最优解

---

### 精选题解与评分

#### 题解1：Liynw（★★★★★）
**亮点**：
- 四状态DP清晰描述路径形态
- 包含完整推导过程和错误思路演进
- 代码简洁易读，含关键注释

**核心思路**：
```cpp
long long a[100005], dp[100005][4];
for(int i=2; i<=n-1; i++) { // 向左DP
    dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + ((a[i-1]&1)?a[i-1]:(a[i-1]-1));
    if(a[i-1]>1) 
        dp[i][1] = dp[i-1][1] + ((a[i-1]&1)?(a[i-1]-1):a[i-1]);
}
for(int i=n; i>=1; i--) { // 向右DP
    dp[i][2] = max(dp[i+1][2], dp[i+1][3]) + ((a[i]&1)?a[i]:(a[i]-1));
    if(a[i]>1)
        dp[i][3] = dp[i+1][3] + ((a[i]&1)?(a[i]-1):a[i]);
}
// 合并答案：左去右回 + 右去左回
ans = max(ans, max(dp[i][0]+dp[i][3], dp[i][1]+dp[i][2]));
```

#### 题解2：pythoner713（★★★★☆）
**亮点**：
- 双DP数组思路简洁
- 图解辅助理解路径形态
- 数学推导完整

**关键公式**：
```cpp
f[i][1] = f[i-1][1] + a[i-1]/2*2; // 保证返回
f[i][0] = max(f[i][1], f[i-1][0]+a[i-1] - parity);
```

---

### 最优技巧总结
1. **路径分解**：将完整路径分解为左/右两段，分别计算后合并
2. **奇偶榨取**：根据桥的耐久度奇偶性计算最大利用次数：
   - 奇数耐久可全用（不返回）或减1（返回）
   - 偶数耐久需减1（不返回）或全用（返回）
3. **状态设计**：DP状态需区分是否返回起点，确保不遗漏路径形态

---

### 拓展训练
1. 类似路径分解：[CF201C](https://codeforces.com/problemset/problem/201/C)（本题原型）
2. 奇偶性处理：[洛谷P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
3. 双向DP应用：[洛谷P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)
4. 状态分治：[洛谷P1854 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)

---

### 调试心得摘录
"最初尝试暴力搜索，发现时间复杂度爆炸。转而分析路径形态，意识到必须返回的路径具有偶数次过桥特性，由此设计四状态DP。调试时发现未处理桥耐久为1时的边界条件，添加`if(a[i-1]>1)`后AC。" —— Liynw的调试经验凸显了状态转移的边界处理重要性。

---
处理用时：47.31秒