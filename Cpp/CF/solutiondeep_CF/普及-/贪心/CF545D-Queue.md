# 题目信息

# Queue

## 题目描述

Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are $ n $ people in the queue. For each person we know time $ t_{i} $ needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

## 说明/提示

Value $ 4 $ is achieved at such an arrangement, for example: $ 1,2,3,5,15 $ . Thus, you can make everything feel not disappointed except for the person with time 5.

## 样例 #1

### 输入

```
5
15 2 1 5 3
```

### 输出

```
4
```

# AI分析结果



# Queue

## 题目描述

小女孩Susie和妈妈去购物时，思考如何改善服务质量。

队列中有$n$个人，每个人有一个服务所需时间$t_i$。如果某人的等待时间超过其所需服务时间，他就会失望。等待时间指排在他前面的所有人被服务的时间总和。通过调整队列顺序，求最多有多少人不会失望。

## 输入样例

```
5
15 2 1 5 3
```

## 输出样例

```
4
```

---

### 题解综合分析

所有题解均采用**贪心算法**，核心思路为：  
1. 将服务时间升序排列  
2. 维护累计时间，依次选择满足条件（累计时间 ≤ 当前服务时间）的人  
3. 仅当满足条件时才累加时间并计数  

关键证明：  
若存在最优解不满足升序排列，总可通过交换逆序元素得到更优解，因此贪心策略正确。

---

### 精选题解（评分≥4星）

#### 1. Michael123456（⭐⭐⭐⭐⭐）
**核心亮点**  
- 最简洁直观的排序实现  
- 时间复杂度O(n log n)，空间O(1)  
- 代码可读性极佳  

```cpp
sort(a+1, a+1+n);
int _time=0, ans=0;
for(int i=1; i<=n; i++) 
    if(_time <= a[i]) 
        ans++, _time += a[i];
```

#### 2. 宁_缺（⭐⭐⭐⭐）
**创新点**  
- 使用优先队列实现排序  
- 展示STL容器的灵活运用  

```cpp
priority_queue<LL, vector<LL>, greater<LL>> q;
for(LL i=1; i<=n; i++) q.push(read());
while (!q.empty()) {
    if (sum <= q.top()) ans++, sum += q.top();
    q.pop();
}
```

#### 3. WKAHPM（⭐⭐⭐⭐）
**理论贡献**  
- 给出贪心策略的数学证明  
- 推导等待时间总和公式  

```cpp
sort(t+1, t+n+1);
int time = 0, sum = 0;
for(int i=1; i<=n; i++) {
    if(time <= t[i]) sum++, time += t[i];
}
```

---

### 关键技巧总结
1. **贪心排序**：升序排列是核心，确保每一步选择最小可行值  
2. **累计时间处理**：仅累加满足条件的元素，避免无效计算  
3. **数据结构选择**：数组排序或优先队列均可实现，前者更高效  

---

### 拓展与关联
**同类问题**  
- 活动选择问题（选最多不重叠区间）  
- 最小等待时间调度（如银行窗口调度）  

**推荐练习**  
1. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)  

**调试心得**  
- 封禁用户题解提到初始代码未处理累加逻辑导致WA，强调必须仅在满足条件时更新累计时间  
- s_ShotღMaki尝试用队列模拟过程，验证贪心策略的正确性

---
处理用时：38.38秒