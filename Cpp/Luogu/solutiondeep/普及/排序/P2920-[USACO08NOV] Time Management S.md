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
这些题解主要围绕贪心和二分答案两种思路来解决问题。贪心思路是按任务结束时间排序，从后往前模拟任务安排，确定最晚开始时间；二分答案思路则是在可能的时间区间内二分查找，通过检查函数判断该时间是否可行。

### 所选题解
- **作者：zhz小蒟蒻（5星）**
    - **关键亮点**：思路清晰，详细解释了二分答案的过程，包括变量定义、判断函数的实现和二分查找的模板使用，代码注释丰富，易于理解。
    - **个人心得**：作者提到自己在判断函数处卡了很久，提醒读者在处理关键逻辑时要仔细。
    - **核心代码**：
```cpp
bool check(int cnt)
{
    int x,y,tnt=cnt;
    for(x=1;x<=n;x++)
    {
        if(que[x].start+tnt<=que[x].comes)
            tnt=que[x].start+tnt;
        else
            return false;
    }
    return true;
}
while(left<=right)
{
    mid=(left+right+1)/2;
    if(check(mid))
    {
        ans=mid;
        left=mid+1;
    }
    else
        right=mid-1;
}
```
核心实现思想：通过`check`函数判断从某个时间开始是否能完成所有任务，在二分查找中不断缩小范围，找到最大的可行时间。

- **作者：Dr_殇（4星）**
    - **关键亮点**：使用AOE网的思路，从最后完成的任务开始模拟，逻辑简单直接，代码简洁。
    - **核心代码**：
```cpp
sort (work+1,work+1+n,cmp);
ans=work[1].f;
for (int i=1;i<=n;i++)
{
    if (ans<=work[i].f)ans-=work[i].v;
    else ans=work[i].f-work[i].v;
}
```
核心实现思想：按结束时间从大到小排序任务，从最后一个任务的结束时间开始模拟，根据当前结束时间和任务所需时间更新开始时间。

- **作者：Diamiko（4星）**
    - **关键亮点**：详细解释了二分答案的原理和适用条件，代码结构清晰，注释明确。
    - **核心代码**：
```cpp
bool check(int x)
{
    int now=x;
    for(int i=1;i<=n;i++)
    {
        if(now+a[i].Cost<=a[i].End)
        {
            now+=a[i].Cost;
        }
        else
        {
            return false;
        }
    }
    return true;
}
while(l<=r)
{
    int mid=l+r>>1;
    if(check(mid))
    {
        ans=mid,l=mid+1;
    }
    else
    {
        r=mid-1;
    }
}
```
核心实现思想：`check`函数判断从某个时间开始能否完成所有任务，二分查找最大的可行时间。

### 最优关键思路或技巧
- **贪心排序**：按任务结束时间排序，优先处理结束时间早的任务，能更合理地安排时间。
- **二分答案**：在单调区间内二分查找答案，通过检查函数判断可行性，将时间复杂度从枚举的 $O(n)$ 降低到 $O(logn)$。

### 拓展思路
同类型题可考虑其他任务安排问题，如任务有优先级、任务可并行等。类似算法套路可用于解决最大值最小、最小值最大等问题，通过二分答案和贪心策略结合求解。

### 推荐题目
- P2440 木材加工：二分答案求解最大切割长度。
- P1873 砍树：二分答案确定合适的砍树高度。
- P3853 [TJOI2007]路标设置：二分答案求最小的最大间距。

### 个人心得总结
- zhz小蒟蒻在判断函数处遇到困难，提醒我们在处理关键逻辑时要仔细思考。
- RainShalder提到第八组数据有坑，某项工作的 $T_i>S_i$ 会导致问题，强调了数据边界的重要性。

---
处理用时：26.57秒