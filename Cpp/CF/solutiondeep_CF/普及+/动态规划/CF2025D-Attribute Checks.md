# 题目信息

# Attribute Checks

## 题目描述

Imagine a game where you play as a character that has two attributes: "Strength" and "Intelligence", that are at zero level initially.

During the game, you'll acquire $ m $ attribute points that allow you to increase your attribute levels — one point will increase one of the attributes by one level. But sometimes, you'll encounter a so-called "Attribute Checks": if your corresponding attribute is high enough, you'll pass it; otherwise, you'll fail it.

Spending some time, you finally prepared a list which contains records of all points you got and all checks you've met. And now you're wondering: what is the maximum number of attribute checks you can pass in a single run if you'd spend points wisely?

Note that you can't change the order of records.

## 说明/提示

In the first test, it's optimal to spend each point in Strength, so you'll fail $ 2 $ Intelligence checks but pass $ 3 $ Strength checks.

In the second test, you'll fail both checks, since the first point you get comes after the checks.

In the third test, one of the optimal strategies is:

1. spend the first point on Intelligence;
2. spend the second point on Strength;
3. spend the third point on Strength;

 As a result, you'll pass $ 2 $ Intelligence checks $ r_3 $ and $ r_9 $ and $ 2 $ Strength checks $ r_7 $ and $ r_8 $ .

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1
1 -1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
9 3
0 0 1 0 2 -3 -2 -2 1```

### 输出

```
4```

# AI分析结果

### 题目内容重写

#### 属性检查

**题目描述**

想象一个游戏，你扮演一个角色，拥有两个属性：“力量”和“智力”，初始时这两个属性的等级均为0。

在游戏过程中，你将获得 $m$ 个属性点，这些属性点可以用来提升你的属性等级——每个属性点可以将其中一个属性提升一级。但有时，你会遇到所谓的“属性检查”：如果你的相应属性等级足够高，你将通过检查；否则，你将失败。

经过一段时间，你终于准备了一个列表，其中包含了所有你获得的属性点和所有你遇到的检查。现在你想知道：如果你明智地分配这些属性点，在一次游戏中你最多能通过多少个属性检查？

注意，你不能改变记录的顺序。

**说明/提示**

在第一个测试用例中，最优策略是将每个属性点都分配给力量，因此你将通过3个力量检查，但会失败2个智力检查。

在第二个测试用例中，你将失败所有检查，因为你获得的第一个属性点出现在检查之后。

在第三个测试用例中，其中一个最优策略是：

1. 将第一个属性点分配给智力；
2. 将第二个属性点分配给力量；
3. 将第三个属性点分配给力量；

结果，你将通过2个智力检查 $r_3$ 和 $r_9$，以及2个力量检查 $r_7$ 和 $r_8$。

**样例 #1**

**输入**

```
10 5
0 1 0 2 0 -3 0 -4 0 -5
```

**输出**

```
3
```

**样例 #2**

**输入**

```
3 1
1 -1 0
```

**输出**

```
0
```

**样例 #3**

**输入**

```
9 3
0 0 1 0 2 -3 -2 -2 1
```

**输出**

```
4
```

### 题解分析与结论

本题的核心在于如何通过动态规划（DP）来优化属性点的分配，以最大化通过属性检查的次数。由于属性点的分配顺序不能改变，且每次分配都会影响后续的检查结果，因此需要一种高效的DP策略来处理这个问题。

### 所选高星题解

#### 题解1：Phrvth (5星)

**关键亮点：**
- 使用了DP状态 $f_{i,j}$ 表示前 $i$ 个点，智力值为 $j$ 时的最大通过检查次数。
- 通过差分优化了区间修改操作，将时间复杂度从 $O(nm)$ 降低到 $O(m^2+n)$。
- 使用了滚动数组进一步优化空间复杂度。

**代码核心思想：**
```cpp
int dp[5005], d[5005];
for(int i = 1, s = 0; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    if(x > 0) {
        if(x <= s) ++d[x], --d[s+1];
    } else if(x < 0) {
        if(0 <= s + x) ++d[0], --d[s + x + 1];
    } else {
        ++s;
        dp[0] += d[0];
        for(int j = 1; j <= s; ++j) dp[j] += (d[j] += d[j-1]);
        for(int j = s; j; --j) dp[j] = max(dp[j], dp[j - 1]);
        memset(d, 0, s + 1 << 2);
    }
}
```

#### 题解2：Super_Cube (4星)

**关键亮点：**
- 使用了DP状态 $dp_i$ 表示智力值为 $i$ 时的最大通过检查次数。
- 通过差分维护区间加操作，简化了代码实现。
- 在 $r_i=0$ 时暴力修改，确保DP状态正确。

**代码核心思想：**
```cpp
int dp[5005], d[5005];
for(int i = 1, s = 0; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    if(x > 0) {
        if(x <= s) ++d[x], --d[s+1];
    } else if(x < 0) {
        if(0 <= s + x) ++d[0], --d[s + x + 1];
    } else {
        ++s;
        dp[0] += d[0];
        for(int j = 1; j <= s; ++j) dp[j] += (d[j] += d[j-1]);
        for(int j = s; j; --j) dp[j] = max(dp[j], dp[j - 1]);
        memset(d, 0, s + 1 << 2);
    }
}
```

#### 题解3：lijunxi20231818 (4星)

**关键亮点：**
- 使用了DP状态 $dp_{i,I}$ 表示前 $i$ 个操作，智力值为 $I$ 时的最大通过检查次数。
- 通过滚动数组优化空间复杂度。
- 在 $r_i=0$ 时暴力修改，确保DP状态正确。

**代码核心思想：**
```cpp
int dp[5005], d[5005];
for(int i = 1, s = 0; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    if(x > 0) {
        if(x <= s) ++d[x], --d[s+1];
    } else if(x < 0) {
        if(0 <= s + x) ++d[0], --d[s + x + 1];
    } else {
        ++s;
        dp[0] += d[0];
        for(int j = 1; j <= s; ++j) dp[j] += (d[j] += d[j-1]);
        for(int j = s; j; --j) dp[j] = max(dp[j], dp[j - 1]);
        memset(d, 0, s + 1 << 2);
    }
}
```

### 最优关键思路与技巧

1. **DP状态设计**：通过设计合理的DP状态（如 $f_{i,j}$ 或 $dp_i$），能够有效地表示当前的状态并推导出最优解。
2. **差分优化**：通过差分维护区间加操作，能够显著降低时间复杂度，尤其是在需要频繁进行区间修改的情况下。
3. **滚动数组**：使用滚动数组优化空间复杂度，避免存储不必要的中间状态，减少内存使用。

### 可拓展之处

本题的DP思路可以拓展到其他类似的资源分配问题，如任务调度、背包问题等。通过合理设计DP状态和优化策略，可以解决更多复杂的多阶段决策问题。

### 推荐题目

1. **P1048 采药**：考察背包问题的经典题目，与本题的资源分配思路相似。
2. **P1060 开心的金明**：涉及资源分配和优先级排序，与本题的DP思路相关。
3. **P2014 选课**：树形DP问题，考察资源在树结构中的分配，与本题的多阶段决策思路类似。

### 个人心得总结

在调试过程中，发现差分数组的初始化非常重要，尤其是在 $r_i=0$ 时需要将差分数组归零，否则会导致后续的DP状态错误。此外，滚动数组的使用能够显著减少内存占用，但需要注意遍历顺序，避免覆盖未使用的状态。

---
处理用时：59.39秒