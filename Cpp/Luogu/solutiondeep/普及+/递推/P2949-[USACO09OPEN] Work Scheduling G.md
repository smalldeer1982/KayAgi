# 题目信息

# [USACO09OPEN] Work Scheduling G

## 题目描述

Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs

conveniently numbered 1..N for work to do. It is possible but

extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.

Job i has deadline D\_i (1 <= D\_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P\_i (1 <= P\_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.




## 说明/提示

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2 to maximize the earnings (7 + 10 -> 17).


## 样例 #1

### 输入

```
3 
2 10 
1 5 
1 7 
```

### 输出

```
17 
```

# AI分析结果

### 综合分析与结论

本题的核心是贪心算法，结合优先队列（小根堆）来实现“反悔”机制。大多数题解都采用了类似的思路：按截止时间排序，使用小根堆维护当前已选任务的最小利润，当遇到新任务时，若时间不足且新任务利润更高，则替换堆顶任务。这种思路的时间复杂度为 \(O(n \log n)\)，能够有效处理大规模数据。

### 所选高星题解

#### 1. 题解作者：Taduro（5星）
**关键亮点**：
- 思路清晰，详细解释了“反悔贪心”的核心思想。
- 代码简洁，使用了优先队列（小根堆）来维护最小利润任务。
- 提供了对单调队列的讨论，虽然最终未采用，但增加了题解的深度。

**代码核心**：
```cpp
priority_queue<int, vector<int>, greater<int>> q;
for (int i = 1; i <= n; i++) {
    if (w[i].tim <= q.size()) {
        if (w[i].mny > q.top()) {
            ans -= q.top();
            q.pop();
            q.push(w[i].mny);
            ans += w[i].mny;
        }
    } else {
        q.push(w[i].mny);
        ans += w[i].mny;
    }
}
```
**实现思想**：通过小根堆维护当前已选任务的最小利润，当新任务利润更高时，替换堆顶任务。

#### 2. 题解作者：Ace_Heart（4星）
**关键亮点**：
- 详细解释了贪心策略的不足之处，并提出了“反悔”的必要性。
- 代码结构清晰，使用了小根堆来动态维护最优解。
- 提供了对时间复杂度的分析，增强了题解的可信度。

**代码核心**：
```cpp
priority_queue<int, vector<int>, greater<int>> q;
for (int i = 1; i <= n; i++) {
    if (a[i].d > day) {
        Add(a[i].p);
        money += a[i].p;
    } else if (a[i].p > d[1]) {
        Add(a[i].p);
        money += a[i].p - Del();
    }
}
```
**实现思想**：通过小根堆维护已选任务的最小利润，当新任务利润更高时，替换堆顶任务。

#### 3. 题解作者：Imakf（4星）
**关键亮点**：
- 提出了逆向思维，从截止时间最大的任务开始处理，避免了正向处理时的复杂情况。
- 代码实现简洁，使用了大根堆来维护当前可选任务的最大利润。
- 提供了对时间复杂度的优化，减少了不必要的操作。

**代码核心**：
```cpp
priority_queue<int> q;
for (int i = 1; i <= n; ) {
    while (true) {
        q.push(P[i++].val);
        if (P[i].pos != P[i - 1].pos) break;
    }
    int cnt = P[i - 1].pos - P[i].pos;
    while (!q.empty() && cnt--) {
        Ans += q.top();
        q.pop();
    }
}
```
**实现思想**：从截止时间最大的任务开始处理，使用大根堆维护当前可选任务的最大利润。

### 最优关键思路与技巧
1. **反悔贪心**：通过优先队列（小根堆）维护当前已选任务的最小利润，当新任务利润更高时，替换堆顶任务。
2. **逆向思维**：从截止时间最大的任务开始处理，避免了正向处理时的复杂情况。
3. **时间复杂度优化**：通过减少不必要的操作，确保算法的高效性。

### 可拓展之处
- **同类型题**：类似的反悔贪心问题可以应用于其他资源分配问题，如任务调度、背包问题等。
- **算法套路**：优先队列与贪心算法的结合是解决动态选择问题的常见套路，适用于多种场景。

### 推荐题目
1. [P1484 种树](https://www.luogu.com.cn/problem/P1484)
2. [P4053 [JSOI2007]建筑抢修](https://www.luogu.com.cn/problem/P4053)
3. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)

### 个人心得摘录
- **调试经历**：部分题解提到在调试过程中发现单调队列不适用，最终选择了优先队列，体现了对算法选择的深思熟虑。
- **顿悟感想**：通过反悔贪心，能够在不增加时间复杂度的情况下，动态调整选择策略，确保全局最优解。

---
处理用时：35.16秒