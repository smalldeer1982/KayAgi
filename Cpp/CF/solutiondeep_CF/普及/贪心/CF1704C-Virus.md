# 题目信息

# Virus

## 题目描述

There are $ n $ houses numbered from $ 1 $ to $ n $ on a circle. For each $ 1 \leq i \leq n - 1 $ , house $ i $ and house $ i + 1 $ are neighbours; additionally, house $ n $ and house $ 1 $ are also neighbours.

Initially, $ m $ of these $ n $ houses are infected by a deadly virus. Each morning, Cirno can choose a house which is uninfected and protect the house from being infected permanently.

Every day, the following things happen in order:

- Cirno chooses an uninfected house, and protect it permanently.
- All uninfected, unprotected houses which have at least one infected neighbor become infected.

Cirno wants to stop the virus from spreading. Find the minimum number of houses that will be infected in the end, if she optimally choose the houses to protect.

Note that every day Cirno always chooses a house to protect before the virus spreads. Also, a protected house will not be infected forever.

## 说明/提示

In the first test case:

At the start of the first day, house $ 3 $ , $ 6 $ , $ 8 $ are infected. Choose house $ 2 $ to protect.

At the start of the second day, house $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ are infected. Choose house $ 10 $ to protect.

At the start of the third day, no more houses are infected.

In the second test case:

At the start of the first day, house $ 2 $ , $ 5 $ are infected. Choose house $ 1 $ to protect.

At the start of the second day, house $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ are infected. No more available houses can be protected.

## 样例 #1

### 输入

```
8
10 3
3 6 8
6 2
2 5
20 3
3 7 12
41 5
1 11 21 31 41
10 5
2 4 6 8 10
5 5
3 2 5 4 1
1000000000 1
1
1000000000 4
1 1000000000 10 16```

### 输出

```
7
5
11
28
9
5
2
15```

# AI分析结果

### 题目内容重写（中文）

#### 病毒传播

**题目描述**

有 $n$ 个房子编号从 $1$ 到 $n$，排列成一个圆圈。对于每个 $1 \leq i \leq n - 1$，房子 $i$ 和房子 $i + 1$ 是邻居；此外，房子 $n$ 和房子 $1$ 也是邻居。

最初，这 $n$ 个房子中有 $m$ 个被一种致命的病毒感染。每天早晨，Cirno 可以选择一个未被感染的房子，并永久保护它，使其不会被感染。

每天，以下事情按顺序发生：

1. Cirno 选择一个未被感染的房子，并永久保护它。
2. 所有未被感染且未被保护的房子，如果至少有一个被感染的邻居，就会被感染。

Cirno 想要阻止病毒的传播。如果她最优地选择要保护的房子，求最终被感染的房子的最小数量。

注意，每天 Cirno 总是在病毒传播之前选择一个房子进行保护。此外，被保护的房子将永远不会被感染。

**说明/提示**

在第一个测试用例中：

- 第一天开始时，房子 $3$、$6$、$8$ 被感染。选择保护房子 $2$。
- 第二天开始时，房子 $3$、$4$、$5$、$6$、$7$、$8$、$9$ 被感染。选择保护房子 $10$。
- 第三天开始时，没有更多的房子被感染。

在第二个测试用例中：

- 第一天开始时，房子 $2$、$5$ 被感染。选择保护房子 $1$。
- 第二天开始时，房子 $2$、$3$、$4$、$5$、$6$ 被感染。没有更多的房子可以保护。

**样例 #1**

#### 输入

```
8
10 3
3 6 8
6 2
2 5
20 3
3 7 12
41 5
1 11 21 31 41
10 5
2 4 6 8 10
5 5
3 2 5 4 1
1000000000 1
1
1000000000 4
1 1000000000 10 16
```

#### 输出

```
7
5
11
28
9
5
2
15
```

---

### 题解综合分析与结论

本题的核心在于如何通过最优策略选择要保护的房子，以最小化最终被感染的房子数量。题解的主要思路是贪心算法，即优先保护最长的未被感染的连续区间，从而最大化保护效果。

#### 关键思路与技巧

1. **贪心策略**：优先保护最长的未被感染的连续区间，因为保护这些区间可以最大化减少被感染的房子数量。
2. **区间计算**：首先计算所有未被感染的连续区间的长度，并对其进行排序。
3. **保护操作**：对于每个区间，计算在保护操作后可以保留的房子数量，并根据区间长度进行相应的保护操作。
4. **时间复杂度**：大部分题解的时间复杂度为 $O(m \log m)$，主要来自于对区间长度的排序。

#### 最优题解推荐

1. **作者：Hovery (赞：8)**  
   - **星级**：5  
   - **关键亮点**：思路清晰，代码简洁，详细解释了贪心策略的正确性，并通过排序和循环实现了最优保护策略。  
   - **核心代码**：
     ```cpp
     sort(b + 1, b + cnt + 1, cmp);
     int now = 0, ans = 0;
     for (int i = 1; i <= cnt; i++)
         if (now * 2 < b[i]) {
             ans += b[i] - now * 2 - ((b[i] - now * 2 == 1) ? 0 : 1);
             now += ((b[i] - now * 2 == 1) ? 1 : 2);
         }
     cout << n - ans << endl;
     ```

2. **作者：yinhy09 (赞：5)**  
   - **星级**：4  
   - **关键亮点**：详细解释了贪心策略的实现过程，并提供了特判处理，代码可读性较好。  
   - **核心代码**：
     ```cpp
     if (b[tot] <= 2) {
         printf("%lld\n", n - 1);
         continue;
     }
     if (b[tot] > 2) ans += b[tot] - 1;
     k = 0;
     for (int i = tot - 1; i >= 1; i--) {
         k++;
         if (b[i] == 4 * k + 1) ans++;
         else if (b[i] > 4 * k + 1) ans += b[i] - 4 * k - 1;
     }
     printf("%lld\n", n - ans);
     ```

3. **作者：litachloveyou (赞：3)**  
   - **星级**：4  
   - **关键亮点**：使用优先队列实现贪心策略，代码结构清晰，逻辑严谨。  
   - **核心代码**：
     ```cpp
     priority_queue<int, vector<int>, less<int>> q;
     for (int i = 0; i < m - 1; i++) {
         q.push(a[i + 1] - a[i] - 1);
     }
     int dis = n - a[m - 1], diss = a[0] - 1;
     q.push(dis + diss);
     int cnt = 0;
     int sum = 1;
     while (!q.empty()) {
         if (q.top() - sum >= 0) {
             cnt += max(q.top() - sum, 1);
             sum += 4;
             q.pop();
         } else break;
     }
     printf("%d\n", n - cnt);
     ```

#### 可拓展之处

1. **类似题目**：本题的贪心策略可以应用于其他需要最大化保护或最小化损失的场景，如资源分配、任务调度等。
2. **数据结构**：优先队列的使用可以优化贪心算法的实现，适用于需要动态维护最大或最小值的场景。

#### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)  
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：46.35秒