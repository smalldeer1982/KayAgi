# 题目信息

# [USACO10FEB] Chocolate Eating S

## 题目描述

Bessie has received N (1 <= N <= 50,000) chocolates from the bulls, but doesn't want to eat them too quickly, so she wants to plan out her chocolate eating schedule for the next D (1 <= D <= 50,000) days in order to maximize her minimum happiness level over the set of those days.

Bessie's happiness level is an integer that starts at 0 and halves (rounding down if necessary) over night as she sleeps. However, when she eats chocolate i, her happiness level increases by integer H\_i (1 <= H\_i <= 1,000,000). If she eats chocolates on a day, her happiness for that day is considered the happiness level after she eats the chocolates. Bessie insists that she eat the chocolates in the order that she received them.

If more than one optimal solution exists, print any one of them.

Consider a sequence of 5 chocolates to be eaten over a period of 5 days; they respectively bring happiness (10, 40, 13, 22, 7).

If Bessie eats the first chocolate (10 happiness) on the first day and then waits to eat the others, her happiness level is 10 after the first day.

Here is the complete schedule which turns out to maximize her minimum happiness:

Day  Wakeup happiness   Happiness from eating   Bedtime happiness 1            0                10+40                  50

2           25                 ---                   25

3           12                  13                   25

4           12                  22                   34

5           17                   7                   24

The minimum bedtime happiness is 24, which turns out to be the best Bessie can do.

Bessie 拿到了 $N$（$1 \leq N \leq 5\times 10 ^ 4$）块巧克力。她决定想个办法吃掉这些巧克力，使得它在吃巧克力的这段时间里，最不开心的一天尽可能的开心。并且一共吃 $D$（$1 \leq D \leq 5\times 10 ^ 4$）天。

每块巧克力有一个开心值 $H_i$（$1 \leq H_i \leq 10 ^ 6$），当某天你吃下那块巧克力时，你将获得那块巧克力的开心值。每一天的开心值是所有当天吃掉的巧克力的总开心值之和。每天晚上 Bessie 睡觉之后，它的开心值会减半。也就是说，比如昨天 Bessie 的开心值为 $50$，那么今天早上一醒来就会有 $25$ 点的开心值，舍去小数点后数字。另外，Bessie 还有一个怪癖，她喜欢按照巧克力本来的排列顺序吃。

Bessie 第一天的开心值为 $0$，求一个每天吃巧克力的方案，使得 Bessie 最不开心的一天尽可能的开心。


## 样例 #1

### 输入

```
5 5 
10 
40 
13 
22 
7 
```

### 输出

```
24 
1 
1 
3 
4 
5 
```

# AI分析结果

### 综合分析与结论

本题的核心是二分答案结合贪心策略，通过二分查找确定最小幸福值的最大值，并通过贪心策略安排巧克力的食用顺序。难点在于如何正确记录巧克力的食用日期，并确保所有巧克力都被吃完。以下是对各题解的总结与对比：

1. **思路清晰度**：大部分题解都采用了二分答案和贪心的思路，但部分题解在记录日期时存在逻辑漏洞，导致输出错误。
2. **代码可读性**：部分题解代码结构清晰，注释详细，易于理解；而有些题解代码较为混乱，缺乏必要的注释。
3. **优化程度**：部分题解在二分查找和贪心策略的实现上进行了优化，如使用位运算代替除法，提高了代码效率。

### 所选高分题解

#### 1. 作者：Yae_Sakura (★★★★★)
**关键亮点**：
- 思路清晰，先通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期。
- 代码结构清晰，注释详细，易于理解。
- 优化了二分查找和贪心策略的实现，使用位运算代替除法，提高了代码效率。

**核心代码**：
```cpp
inline bool check(ll x)
{
    ll tot=0,sum=0;
    for(int i=1;i<=d;i++){
        sum=sum>>1;
        while(sum<x){
            sum+=a[++tot];
            if(tot>n) return false;
            if(x&&x==ans) day[tot]=i;
        }
    }
    return true;
}
```
**实现思想**：通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期。

#### 2. 作者：funky_monkey (★★★★☆)
**关键亮点**：
- 思路清晰，先通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期。
- 代码结构清晰，注释详细，易于理解。
- 在记录日期时，确保所有巧克力都被吃完。

**核心代码**：
```cpp
inline bool check(ll x,bool f)
{
    ll tmp=0,cur=1;
    for(int i=1; i<=d; i++)
    {
        tmp>>=1;
        while(cur<=n && tmp<x)
        {
            tmp+=h[cur];
            if(f) a[cur]=i;
            cur++;
        }
        if(tmp<x)return 0;
    }
    if(f)
        for(int i=cur+1; i<=n; i++)
            a[cur]=d;
    return 1;
}
```
**实现思想**：通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期，并确保所有巧克力都被吃完。

#### 3. 作者：shiroi (★★★★☆)
**关键亮点**：
- 思路清晰，先通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期。
- 代码结构清晰，注释详细，易于理解。
- 在记录日期时，确保所有巧克力都被吃完。

**核心代码**：
```cpp
inline bool jud(ll x,bool f)
{
    ll tmp=0,cur=1;
    for(int i=1; i<=d; i++)
    {
        tmp>>=1;
        while(cur<=n && tmp<x)
        {
            tmp+=h[cur];
            if(f) a[cur]=i;
            cur++;
        }
        if(tmp<x)return 0;
    }
    if(f)
        for(int i=cur+1; i<=n; i++)
            a[cur]=d;
    return 1;
}
```
**实现思想**：通过二分查找确定最小幸福值的最大值，再通过贪心策略记录正确的食用日期，并确保所有巧克力都被吃完。

### 最优关键思路与技巧

1. **二分答案**：通过二分查找确定最小幸福值的最大值，减少时间复杂度。
2. **贪心策略**：在确定最小幸福值后，通过贪心策略安排巧克力的食用顺序，确保每天的幸福值尽可能大。
3. **位运算优化**：使用位运算代替除法，提高代码效率。

### 可拓展之处

1. **类似算法套路**：二分答案结合贪心策略的算法套路可以应用于其他最小值最大化或最大值最小化的问题。
2. **同类型题**：可以尝试解决其他需要二分答案和贪心策略的题目，如背包问题、调度问题等。

### 推荐题目

1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
2. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)

### 个人心得总结

- **调试经历**：部分题解在记录日期时存在逻辑漏洞，导致输出错误，调试时需要特别注意。
- **踩坑教训**：在二分查找和贪心策略的实现中，确保所有巧克力都被吃完是关键，否则会导致输出错误。
- **顿悟感想**：二分答案结合贪心策略的算法套路在解决最小值最大化或最大值最小化问题时非常有效，值得深入学习和掌握。

---
处理用时：42.32秒