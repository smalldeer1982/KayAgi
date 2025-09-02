# 题目信息

# Seraphim the Owl

## 题目描述

The guys lined up in a queue of $ n $ people, starting with person number $ i = 1 $ , to ask Serafim the Owl about the meaning of life. Unfortunately, Kirill was very busy writing the legend for this problem, so he arrived a little later and stood at the end of the line after the $ n $ -th person. Kirill is completely dissatisfied with this situation, so he decided to bribe some people ahead of him.

For the $ i $ -th person in the queue, Kirill knows two values: $ a_i $ and $ b_i $ . If at the moment Kirill is standing at position $ i $ , then he can choose any position $ j $ such that $ j < i $ and exchange places with the person at position $ j $ . In this case, Kirill will have to pay him $ a_j $ coins. And for each $ k $ such that $ j < k < i $ , Kirill will have to pay $ b_k $ coins to the person at position $ k $ . Kirill can perform this action any number of times.

Kirill is thrifty, so he wants to spend as few coins as possible, but he doesn't want to wait too long, so Kirill believes he should be among the first $ m $ people in line.

Help Kirill determine the minimum number of coins he will have to spend in order to not wait too long.

## 样例 #1

### 输入

```
4
4 2
7 3 6 9
4 3 8 5
6 2
6 9 7 1 8 3
5 8 8 1 4 1
7 7
7 2 9 2 6 5 9
9 1 10 7 1 4 9
2 1
2 3
1 1```

### 输出

```
14
22
9
3```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

有 $n$ 个人排成一队，编号从 $1$ 到 $n$，Kirill 是第 $n+1$ 个人，他站在队伍的最后。Kirill 对这种情况非常不满，因此他决定贿赂前面的一些人，以便能够插队到前面。

对于第 $i$ 个人，Kirill 知道两个值：$a_i$ 和 $b_i$。如果 Kirill 当前站在位置 $i$，他可以选择任意一个位置 $j$（$j < i$），并与位置 $j$ 的人交换位置。在这种情况下，Kirill 需要支付 $a_j$ 个硬币给位置 $j$ 的人，并且对于每个 $k$（$j < k < i$），Kirill 还需要支付 $b_k$ 个硬币给位置 $k$ 的人。Kirill 可以执行这个操作任意多次。

Kirill 非常节俭，因此他希望花费尽可能少的硬币，但他也不想等太久，因此 Kirill 认为他应该在前 $m$ 个人的位置中。

请你帮助 Kirill 确定他需要花费的最少硬币数。

#### 样例 #1

##### 输入

```
4
4 2
7 3 6 9
4 3 8 5
6 2
6 9 7 1 8 3
5 8 8 1 4 1
7 7
7 2 9 2 6 5 9
9 1 10 7 1 4 9
2 1
2 3
1 1
```

##### 输出

```
14
22
9
3
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是动态规划（DP）优化。大部分题解都采用了从后向前遍历的思路，利用贪心策略或单调队列优化来减少时间复杂度。主要思路是：

1. **贪心策略**：对于位置 $m+1$ 到 $n$，Kirill 可以选择支付 $a_i$ 或 $b_i$ 的最小值，因为这些位置不会影响最终的插队位置。
2. **动态规划**：对于位置 $1$ 到 $m$，Kirill 需要选择一个位置作为最终的插队位置，并计算从 $n+1$ 到该位置的最小代价。

#### 最优关键思路或技巧

1. **从后向前遍历**：通过从后向前遍历，可以避免重复计算，并且可以利用贪心策略选择最小代价。
2. **前缀和优化**：使用前缀和来快速计算区间和，减少时间复杂度。
3. **单调队列优化**：通过单调队列维护最小值，进一步优化 DP 转移。

#### 推荐题目

1. [P1725 琪露诺的冰雹](https://www.luogu.com.cn/problem/P1725) - 单调队列优化 DP
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 单调队列的应用
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划基础题

### 精选题解

#### 题解1：作者：spfa_ (赞：6)

**星级**：★★★★★  
**关键亮点**：  
- 使用单调队列优化 DP，时间复杂度为 $O(n)$。  
- 思路清晰，代码简洁，优化到位。

**核心代码**：
```cpp
for (int i = n; i >= 1; i--) {
    while (!q.empty() && dp[q.back()] >= dp[i]) q.pop_back();
    q.push_back(i);
    dp[i] = dp[q.front()] + a[i] + sum[i - 1] - sum[q.front() - 1];
}
```
**核心思想**：通过单调队列维护最小值，优化 DP 转移。

#### 题解2：作者：ZhaoV1 (赞：4)

**星级**：★★★★  
**关键亮点**：  
- 使用贪心策略和前缀和优化，代码简洁易懂。  
- 通过前缀和快速计算区间和，减少时间复杂度。

**核心代码**：
```cpp
for (int i = m + 1; i <= n; i++) res += min(a[i], b[i]);
int sum = INF; s[0] = 0;
for (int i = 1; i <= m; i++) s[i] = s[i - 1] + b[i];
for (int i = 1; i <= m; i++) sum = min(sum, a[i] + s[m] - s[i]);
res += sum;
```
**核心思想**：通过前缀和快速计算区间和，选择最小代价。

#### 题解3：作者：__Floze3__ (赞：4)

**星级**：★★★★  
**关键亮点**：  
- 从后向前遍历，利用贪心策略选择最小代价。  
- 代码简洁，思路清晰，优化到位。

**核心代码**：
```cpp
for (int i = n; i > m; --i) res += std::min(a[i], b[i]);
ll ans = 1e18;
for (int i = m; i; --i) {
    ans = std::min(ans, res + a[i]);
    res += b[i];
}
```
**核心思想**：从后向前遍历，利用贪心策略选择最小代价。

---
处理用时：39.78秒