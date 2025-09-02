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

本题的核心目标是找到农夫约翰最晚可以开始工作的时间，以确保所有任务都能按时完成。题解中主要采用了以下几种思路：

1. **贪心算法**：大多数题解通过贪心策略，按照任务的截止时间进行排序，然后从后向前模拟任务的完成时间，逐步推导出最晚开始时间。
2. **二分查找**：部分题解通过二分查找来枚举可能的开始时间，并通过检查函数验证该时间是否满足所有任务的完成条件。
3. **直接模拟**：少数题解通过直接模拟任务的完成过程，逐步调整开始时间，最终得出结果。

从题解的质量来看，**贪心算法**和**二分查找**是较为高效且清晰的解决方案，而直接模拟的方法虽然简单，但在某些情况下可能不够优化。

### 精选题解

#### 1. 作者：Dr_殇 (5星)
- **关键亮点**：采用贪心算法，按照任务的截止时间从晚到早排序，从最后一个任务开始模拟，逐步推导出最晚开始时间。思路清晰，代码简洁。
- **代码核心**：
  ```cpp
  sort(work+1,work+1+n,cmp); // 按截止时间从晚到早排序
  ans=work[1].f; // 初始化为最后一个任务的截止时间
  for(int i=1;i<=n;i++){
      if(ans<=work[i].f) ans-=work[i].v; // 如果当前任务可以在截止时间前完成，更新开始时间
      else ans=work[i].f-work[i].v; // 否则，调整开始时间
  }
  ```
- **个人心得**：通过从后向前模拟任务的完成时间，能够更直观地推导出最晚开始时间，避免了复杂的计算。

#### 2. 作者：Benson2005 (4.5星)
- **关键亮点**：同样采用贪心算法，但通过`min`函数动态调整任务的开始时间，代码简洁且高效。
- **代码核心**：
  ```cpp
  sort(a+1,a+n+1,cmp); // 按截止时间从晚到早排序
  lst=a[1].l; // 初始化为最后一个任务的截止时间
  for(int i=1;i<=n;i++) 
      lst=min(lst,a[i].l)-a[i].t; // 动态调整开始时间
  ```
- **个人心得**：通过`min`函数动态调整开始时间，确保了任务的完成时间不会超过截止时间，思路清晰且易于实现。

#### 3. 作者：Rbu_nas (4星)
- **关键亮点**：采用二分查找枚举可能的开始时间，并通过检查函数验证该时间是否满足所有任务的完成条件，思路清晰且优化程度较高。
- **代码核心**：
  ```cpp
  while(l <= r){
      mid=(l+r)>>1;
      if(check(mid)) ans=mid, l=mid+1; // 如果当前时间满足条件，尝试更晚的时间
      else r=mid-1; // 否则，尝试更早的时间
  }
  ```
- **个人心得**：二分查找的优化思路使得算法的时间复杂度降低，适合处理较大规模的数据。

### 最优关键思路与技巧

1. **贪心算法**：按照任务的截止时间进行排序，从后向前模拟任务的完成时间，逐步推导出最晚开始时间。这种思路简单直观，且时间复杂度较低。
2. **二分查找**：通过二分查找枚举可能的开始时间，并通过检查函数验证该时间是否满足所有任务的完成条件。这种思路适合处理较大规模的数据，且优化程度较高。

### 可拓展之处

- **类似问题**：类似的任务调度问题可以通过贪心算法或二分查找来解决，例如任务调度中的最小化延迟问题、最大化任务完成数量问题等。
- **算法套路**：贪心算法和二分查找是解决任务调度问题的常见套路，掌握这两种算法可以应对多种类似问题。

### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880) - 考察贪心算法和动态规划。
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090) - 考察贪心算法和优先队列。
3. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048) - 考察动态规划和背包问题。

### 个人心得总结

- **调试经历**：在调试过程中，发现直接模拟的方法在某些情况下会出现边界问题，通过引入`min`函数动态调整开始时间，解决了这一问题。
- **踩坑教训**：在二分查找的实现中，初始边界的选择非常重要，选择不当会导致死循环或无法找到最优解。
- **顿悟感想**：通过从后向前模拟任务的完成时间，能够更直观地推导出最晚开始时间，避免了复杂的计算，思路清晰且易于实现。

---
处理用时：33.46秒