# 题目信息

# [USACO14DEC] Cow Jog S

## 题目描述

 

The cows are out exercising their hooves again!  There are N cows

jogging on an infinitely-long single-lane track (1 <= N <= 100,000).

Each cow starts at a distinct position on the track, and some cows jog

at different speeds.


 

With only one lane in the track, cows cannot pass each other.  When a

faster cow catches up to another cow, she has to slow down to avoid

running into the other cow, becoming part of the same running group.

 

The cows will run for T minutes (1 <= T <= 1,000,000,000).  Please

help Farmer John determine how many groups will be left at this time.

Two cows should be considered part of the same group if they are at


the same position at the end of T minutes. 

有N (1 <= N <= 100,000)头奶牛在一个单人的超长跑道上慢跑，每头牛的起点位置都不同。由于是单人跑道，所有他们之间不能相互超越。当一头速度快的奶牛追上另外一头奶牛的时候，他必须降速成同等速度。我们把这些跑走同一个位置而且同等速度的牛看成一个小组。


请计算T (1 <= T <= 1,000,000,000)时间后，奶牛们将分为多少小组。



## 样例 #1

### 输入

```
5 3 
0 1 
1 2 
2 3 
3 2 
6 1 

 

```

### 输出

```
 

3 

 
```

# AI分析结果

### 综合分析与结论

本题的核心在于判断奶牛在给定时间T后是否会形成小组，且由于奶牛不能相互超越，因此需要从后向前处理奶牛的最终位置。大部分题解都采用了类似的思路：先计算每头奶牛的最终位置，然后从后向前遍历，如果前一头奶牛的最终位置大于等于后一头奶牛，则认为它们会合并成一个小组，否则小组数加一。

### 所选高星题解

#### 题解1：NewErA (5星)
**关键亮点**：
- 思路清晰，代码简洁，直接从后向前遍历并更新最终位置。
- 使用了`long long`类型处理大数，避免了溢出问题。
- 代码可读性强，逻辑简单明了。

**核心代码**：
```cpp
for(int i=n-1;i>=1;i--)
{
    if(last[i]>=last[i+1])
    {
        last[i]=last[i+1];
    }
    else
    {
        res++;
    }
}
```
**实现思想**：从后向前遍历，如果前一头奶牛的最终位置大于等于后一头奶牛，则更新前一头奶牛的位置，否则小组数加一。

#### 题解2：Tarsal (4星)
**关键亮点**：
- 与NewErA的思路类似，代码结构清晰，逻辑简单。
- 使用了`long long`类型，处理了大数问题。
- 代码风格良好，注释清晰。

**核心代码**：
```cpp
for(int i = n - 1; i >= 1; -- i)
{
    if(last[i] >= last[i + 1])
        last[i] = last[i + 1];
    else
        ++ ans;
}
```
**实现思想**：从后向前遍历，如果前一头奶牛的最终位置大于等于后一头奶牛，则更新前一头奶牛的位置，否则小组数加一。

#### 题解3：Thomasguo666 (4星)
**关键亮点**：
- 提供了Python和C++两种语言的实现，适合不同语言的学习者。
- 思路清晰，代码简洁，逻辑简单。
- 使用了`long long`类型，处理了大数问题。

**核心代码**：
```cpp
for (ll i=n-1;i>0;i--) ans+=(p[i]<p[i+1]?1:(p[i]=p[i+1])*0);
```
**实现思想**：从后向前遍历，如果前一头奶牛的最终位置小于后一头奶牛，则小组数加一，否则更新前一头奶牛的位置。

### 最优关键思路与技巧

1. **从后向前处理**：由于奶牛不能相互超越，从后向前遍历可以确保每头奶牛只与后面的奶牛进行比较，避免了复杂的逻辑。
2. **使用`long long`类型**：由于T的范围很大，使用`long long`类型可以避免溢出问题。
3. **更新最终位置**：如果前一头奶牛的最终位置大于等于后一头奶牛，则更新前一头奶牛的位置，这样可以简化后续的判断。

### 可拓展之处

- **类似题目**：可以扩展到多车道的情况，或者考虑奶牛在不同时间点的速度变化。
- **算法套路**：这种从后向前处理的思路可以应用于其他类似的模拟问题，如车辆行驶、任务调度等。

### 推荐相似题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 考察贪心算法和优先队列的使用。
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 考察单调队列的应用。
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 考察动态规划的基本应用。

### 个人心得总结

- **调试经历**：在处理大数时，使用`long long`类型可以有效避免溢出问题，确保程序的正确性。
- **踩坑教训**：在从后向前遍历时，确保每头奶牛只与后面的奶牛进行比较，避免逻辑错误。
- **顿悟感想**：从后向前处理的思路可以简化很多复杂的模拟问题，值得在类似题目中应用。

---
处理用时：21.26秒