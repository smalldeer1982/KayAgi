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
本题核心是求最大可行起始时间，需满足所有任务按特定顺序完成。题解主要采用两种思路：
1. **贪心+逆推法**：按截止时间降序排序，从最晚任务逆推起始时间，维护当前最晚开始时间。时间复杂度O(n log n)，最优解法。
2. **二分答案**：在时间轴上二分起始时间，通过贪心顺序验证可行性。时间复杂度O(n log S)，通用但稍慢。

最优解法为贪心逆推法，其正确性基于：处理更紧迫的任务后，剩余时间约束不会影响后续任务。关键难点在于正确排序策略的证明与时间维护方式。

---

### 高星题解推荐

#### 1. 题解作者：Benson2005（★★★★★）
**关键亮点**：代码极简（仅14行），正确性高，时间复杂度最优。  
**核心思路**：按截止时间降序排序，逆序维护当前最晚开始时间。
```cpp
sort(a+1,a+n+1,cmp); // 按截止时间降序排序
lst = a[1].l;
for(int i=1;i<=n;i++) 
    lst = min(lst,a[i].l) - a[i].t; // 维护最晚开始时间
```

#### 2. 题解作者：Dr_殇（★★★★☆）
**关键亮点**：清晰展示逆推过程，代码可读性强。  
**核心思路**：从最晚任务开始，逐步计算各任务最晚开始时间。
```cpp
sort(work+1,work+1+n,cmp); // 按截止时间降序排序
ans = work[1].f;
for(int i=1;i<=n;i++){
    if(ans <= work[i].f) ans -= work[i].v; // 时间充裕则直接扣除
    else ans = work[i].f - work[i].v; // 否则按当前任务调整
}
```

#### 3. 题解作者：Diamiko（★★★★☆）
**关键亮点**：详细讲解二分答案原理，代码结构规范。  
**核心思路**：二分起始时间，按截止时间升序验证可行性。
```cpp
bool check(int x){
    int now = x;
    for(int i=1;i<=n;i++){
        if(now+a[i].Cost > a[i].End) return false;
        now += a[i].Cost; // 顺序累加时间
    }
    return true;
}
```

---

### 最优关键思路总结
**贪心逆推法**：
1. **排序策略**：按截止时间从晚到早排序（降序）
2. **时间维护**：初始化为最晚任务的截止时间，依次处理每个任务：`当前时间 = min(当前时间, 任务截止时间) - 任务耗时`
3. **终止条件**：若最终时间 ≥0 则输出，否则输出-1

**正确性证明**：按截止时间降序处理可确保每次选择的任务在当前剩余时间中最紧迫的约束，避免后续任务时间冲突。

---

### 相似题目推荐
1. [P1181 数列分段Section I](https://www.luogu.com.cn/problem/P1181)（贪心分段）
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（二分答案经典题）
3. [P1843 奶牛晒衣服](https://www.luogu.com.cn/problem/P1843)（贪心+二分答案结合）

---
处理用时：57.04秒