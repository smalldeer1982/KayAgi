# 题目信息

# [USACO17JAN] Cow Dance Show S

## 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。

## 样例 #1

### 输入

```
5 8
4
7
8
6
4```

### 输出

```
4
```

# AI分析结果



### 综合分析与结论
本题需通过二分答案确定最小舞台容量K，结合优先队列模拟奶牛上台过程。所有题解均采用二分+堆维护的核心思路，正确性关键在于维护当前最早结束时间并按顺序替换奶牛。最优解法需注意总时间的正确计算方式与输入顺序的保持。

---

### 高评分题解（≥4星）

#### 1. Strong_Jelly（4.5星）
**关键亮点**：  
- 详细注释与分阶段处理逻辑，确保时间差累加的正确性  
- 明确强调输入顺序不可排序的陷阱  
- 完整处理剩余队列的逻辑，避免遗漏  

**核心代码**：
```cpp
bool f(int x) {
    priority_queue<int, vector<int>, greater<int>> pru;
    for (int i = 1; i <= x; ++i) pru.push(q[i]); // 初始填充
    // 处理后续奶牛
    for (int i = x + 1; i <= n; ++i) {
        int y = pru.top(); 
        pru.pop();
        pru.push(q[i] + y); // 新牛结束时间 = 当前时间 + 自身耗时
        // 累加时间差并检查T_max
    }
    // 处理剩余队列
    while (x--) {
        ans += pru.top() - y;
        y = pru.top();
        pru.pop();
    }
    return ans <= m;
}
```

---

#### 2. 从不再见（4星）
**关键亮点**：  
- 直观取最终堆中最大值作为总时间，逻辑简洁  
- 采用更稳健的二分写法（`l+1 < r`）  
- 代码结构清晰，适合快速理解  

**核心代码**：
```cpp
bool check(int x) {
    priority_queue<int, vector<int>, greater<int>> dance;
    for (int i = 1; i <= x; i++) dance.push(cow[i]);
    for (int i = x + 1; i <= n; i++) {
        int cur = dance.top();
        dance.pop();
        dance.push(cur + cow[i]); // 更新结束时间
    }
    int max_time = 0;
    while (!dance.empty()) max_time = max(max_time, dance.top());
    return max_time <= t_max;
}
```

---

#### 3. Histone（4星）
**关键亮点**：  
- 代码极简风格，突出算法核心逻辑  
- 提供暴力枚举版本代码供参考  
- 明确总时间由最后结束的牛决定  

**核心代码**：
```cpp
bool c(int x) {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= x; i++) q.push(num[i]);
    for (int i = x + 1; i <= n; i++) {
        int temp = q.top();
        q.pop();
        q.push(temp + num[i]); // 直接叠加时间
    }
    return q.top() <= t; // 最终队列最大值即为总时间
}
```

---

### 最优思路总结
1. **二分框架**：在[1, N]范围内二分K，判断是否满足T ≤ T_max。
2. **堆维护策略**：用小根堆动态维护当前舞台上最早结束的牛，每次替换为下一头牛，时间复杂度O(N logK)。
3. **时间计算**：总时间等于所有牛结束时间的最大值，可通过最终堆中最大值或分阶段累加差实现。

---

### 推荐相似题目
1. [P1843 奶牛晒衣服](https://www.luogu.com.cn/problem/P1843)（二分+贪心）  
2. [P2983 [USACO10FEB]Chocolate Buying S](https://www.luogu.com.cn/problem/P2983)（二分+优先队列）  
3. [P4058 [Code+#1]木材](https://www.luogu.com.cn/problem/P4058)（二分答案+时间模拟）  

---

### 题解心得摘录
- **Strong_Jelly**：强调输入顺序的重要性，避免错误排序导致WA。  
- **zy小可爱ღ**：冒泡排序在部分情况下优于快速排序，但需警惕O(nk)的极端情况。  
- **封禁用户**：手写线段树实现堆功能，展示数据结构灵活运用，但代码复杂度较高。

---
处理用时：116.10秒