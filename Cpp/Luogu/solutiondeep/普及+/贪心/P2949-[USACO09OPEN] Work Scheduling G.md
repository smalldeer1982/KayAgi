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
本题考察带反悔的贪心策略，核心矛盾在于如何动态维护最优工作集合。主流解法通过排序+小根堆实现，时间复杂度O(N logN)，空间复杂度O(N)。关键点在于通过堆结构快速获取当前已选工作中的最小利润，并通过替换操作实现"撤销劣质选择"的贪心反悔机制。

---

### 精选题解与评分

#### 1. 作者：Taduro（⭐⭐⭐⭐⭐）
**核心亮点**：
- 使用最简洁的排序+小根堆实现反悔贪心
- 代码仅20行，优先队列直接处理替换逻辑
- 时间复杂度严格证明，变量命名清晰

**核心代码**：
```cpp
for(int i=1; i<=n; i++){
    if(w[i].tim <= q.size()){
        if(w[i].mny > q.top()) {
            ans += w[i].mny - q.top();
            q.pop(); q.push(w[i].mny);
        }
    } else {
        q.push(w[i].mny);
        ans += w[i].mny;
    }
}
```
**实现思路**：按截止时间排序后，用堆维护已选工作集合，当时间冲突时替换最小利润工作。

---

#### 2. 作者：Imakf（⭐⭐⭐⭐）
**创新点**：
- 逆向思维从大时间往小时间处理
- 使用大根堆存储可用任务，按时间段批量处理
- 通过计算时间差减少堆操作次数

**核心代码片段**：
```cpp
for(int i=1 ; i<=n ; ){
    while(job[i].pos == job[i-1].pos) 
        q.push(job[i++].val);
    int cnt = job[i-1].pos - job[i].pos;
    while(cnt-- && !q.empty()){
        ans += q.top(); q.pop();
    }
}
```
**思维突破**：将时间视为从后向前的资源分配，利用时间段跳跃优化处理效率。

---

#### 3. 作者：Ace_Heart（⭐⭐⭐⭐）
**亮点**：
- 详细图解错误贪心案例
- 用堆模拟"时间倒流"替换过程
- 完整的手写堆实现展示底层原理

**调试心得**：
> "最初以为简单排序即可，但测试用例发现可能丢失后期高利润任务，意识到必须保留替换劣质选择的可能性"

---

### 关键技巧总结
1. **贪心反悔机制**：通过维护当前选择集合的最小值，为后续更优选择保留替换可能
2. **堆的妙用**：小根堆O(1)时间获取最小值，完美适配反悔需求
3. **时间排序策略**：正序处理保障截止时间约束，逆序处理优化批量操作
4. **离散化技巧**：对大数据范围的时间戳进行离散化处理（如并查集优化法）

---

### 拓展练习
1. [P1484 种树](https://www.luogu.com.cn/problem/P1484) - 环形反悔贪心经典
2. [P4053 建筑抢修](https://www.luogu.com.cn/problem/P4053) - 带时间消耗的反悔贪心
3. [P2107 小Z的AK计划](https://www.luogu.com.cn/problem/P2107) - 结合位置移动的贪心决策

---

### 共性套路总结
此类问题的通用解法可抽象为：
1. **排序预处理**：按某一维度（时间/位置等）排序
2. **动态维护集合**：使用堆/并查集等结构维护当前最优解
3. **反悔替换**：当新元素更优时，替换历史选择中的劣质项
4. **复杂度控制**：通过数据结构优化将时间复杂度控制在O(N logN)级别

掌握这一模式可快速解决90%的贪心类调度问题。

---
处理用时：57.79秒