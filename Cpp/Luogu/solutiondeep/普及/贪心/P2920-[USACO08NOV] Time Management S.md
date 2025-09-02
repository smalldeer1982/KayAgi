# 题目信息

# [USACO08NOV] Time Management S

## 题目描述

Ever the maturing businessman, Farmer John realizes that he must manage his time effectively. He has N jobs conveniently numbered 1..N (1 <= N <= 1,000) to accomplish (like milking the cows, cleaning the barn, mending the fences, and so on).

To manage his time effectively, he has created a list of the jobs that must be finished. Job i requires a certain amount of time T\_i (1 <= T\_i <= 1,000) to complete and furthermore must be finished by time S\_i (1 <= S\_i <= 1,000,000). Farmer John starts his day at time t=0 and can only work on one job at a time until it is finished.

Even a maturing businessman likes to sleep late; help Farmer John determine the latest he can start working and still finish all the jobs on time.

作为一名忙碌的商人，约翰知道必须高效地安排他的时间。他有 $N(1\le N\le 1000)$ 个工作要做，比如给奶牛挤奶，清洗牛棚，修理栅栏之类的。

为了高效，约翰列出了所有工作的清单。第 $i(1\le i\le N)$ 个工作需要 $T_i(1\le T_i\le 1000)$ 单位的时间来完成，而且必须在 $1\le S_i\le 10^6$ 或之前完成。现在是 $0$ 时刻。约翰做一份工作必须直到做完才能停止。

所有的商人都喜欢睡懒觉。请帮约翰计算他最迟什么时候开始工作，可以让所有工作按时完成。（如果始终无法完成全部任务，输出 $-1$）


## 说明/提示

Farmer John has 4 jobs to do, which take 3, 8, 5, and 1 units of time, respectively, and must be completed by time 5, 14, 20, and 16, respectively.


Farmer John must start the first job at time 2. Then he can do the second, fourth, and third jobs in that order to finish on time.


## 样例 #1

### 输入

```
4 
3 5 
8 14 
5 20 
1 16 
```

### 输出

```
2 
```

# AI分析结果

### 综合分析与结论

本题的核心是求解约翰最晚可以开始工作的时间，确保所有任务都能按时完成。题解中主要采用了以下几种思路：

1. **二分答案**：通过二分查找确定最晚开始时间，结合贪心策略验证是否可行。
2. **贪心策略**：按照任务的截止时间排序，从后向前模拟任务完成过程，确保每个任务都能按时完成。
3. **直接模拟**：通过枚举开始时间，模拟任务完成过程，找到最晚开始时间。

其中，**二分答案**和**贪心策略**是较为常见的解法，且代码实现较为简洁。**直接模拟**虽然思路简单，但在大数据量下可能效率较低。

### 所选高星题解

#### 1. 作者：Rbu_nas (赞：7)  
**星级**：★★★★★  
**关键亮点**：  
- 使用了二分答案的思路，结合贪心策略验证是否可行，时间复杂度为O(nlogn)，效率较高。
- 代码结构清晰，注释详细，易于理解。
- 提供了二分答案的模板，适合初学者学习。

**核心代码**：
```cpp
bool check(int x) {
    int now = x;
    for (int i = 1; i <= n; i++) {
        if (now + a[i].t <= a[i].s) now += a[i].t;
        else return false;
    }
    return true;
}
```
**实现思想**：通过二分查找确定最晚开始时间，使用`check`函数验证是否所有任务都能按时完成。

#### 2. 作者：Youngsc (赞：5)  
**星级**：★★★★  
**关键亮点**：  
- 采用贪心策略，从后向前模拟任务完成过程，确保每个任务都能按时完成。
- 代码简洁，逻辑清晰，适合快速实现。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    minn(now, a[i].s);
    now -= a[i].t;
}
```
**实现思想**：从最晚截止时间的任务开始，逐步向前模拟任务完成过程，更新最晚开始时间。

#### 3. 作者：Diamiko (赞：10)  
**星级**：★★★★  
**关键亮点**：  
- 使用二分答案的思路，结合贪心策略验证是否可行，代码结构清晰。
- 提供了详细的二分答案解释，适合初学者学习。

**核心代码**：
```cpp
bool check(int x) {
    int now = x;
    for (int i = 1; i <= n; i++) {
        if (now + a[i].Cost <= a[i].End) now += a[i].Cost;
        else return false;
    }
    return true;
}
```
**实现思想**：通过二分查找确定最晚开始时间，使用`check`函数验证是否所有任务都能按时完成。

### 最优关键思路与技巧

1. **二分答案**：通过二分查找确定最晚开始时间，结合贪心策略验证是否可行，适合处理单调性问题。
2. **贪心策略**：按照任务的截止时间排序，从后向前模拟任务完成过程，确保每个任务都能按时完成。

### 可拓展之处

1. **类似问题**：可以扩展到其他需要确定最优开始时间的问题，如任务调度、资源分配等。
2. **算法套路**：二分答案和贪心策略的结合在解决最优化问题时非常常见，可以应用到其他类似问题中。

### 推荐题目

1. **P2440 木材加工**：考察二分答案的应用。
2. **P1873 砍树**：考察二分答案和贪心策略的结合。
3. **P1083 借教室**：考察二分答案和差分数组的应用。

### 个人心得摘录

- **Rbu_nas**：二分答案的精髓在于判断函数，每次二分找到一个x，判断从x开始如果每个工作都能按时完成说明解符合条件。
- **Youngsc**：从后向前模拟任务完成过程，确保每个任务都能按时完成，代码简洁，逻辑清晰。
- **Diamiko**：二分答案的`check`函数是关键，通过遍历每个事件，判断当前时间点加上事件所需时间是否小于等于结束时间。

---
处理用时：35.75秒