# 题目信息

# Approximating a Constant Range

## 题目描述

When Xellos was doing a practice course in university, he once had to measure the intensity of an effect that slowly approached equilibrium. A good way to determine the equilibrium intensity would be choosing a sufficiently large number of consecutive data points that seems as constant as possible and taking their average. Of course, with the usual sizes of data, it's nothing challenging — but why not make a similar programming contest problem while we're at it?

You're given a sequence of $ n $ data points $ a_{1},...,a_{n} $ . There aren't any big jumps between consecutive data points — for each $ 1<=i&lt;n $ , it's guaranteed that $ |a_{i+1}-a_{i}|<=1 $ .

A range $ [l,r] $ of data points is said to be almost constant if the difference between the largest and the smallest value in that range is at most $ 1 $ . Formally, let $ M $ be the maximum and $ m $ the minimum value of $ a_{i} $ for $ l<=i<=r $ ; the range $ [l,r] $ is almost constant if $ M-m<=1 $ .

Find the length of the longest almost constant range.

## 说明/提示

In the first sample, the longest almost constant range is $ [2,5] $ ; its length (the number of data points in it) is 4.

In the second sample, there are three almost constant ranges of length $ 4 $ : $ [1,4] $ , $ [6,9] $ and $ [7,10] $ ; the only almost constant range of the maximum length $ 5 $ is $ [6,10] $ .

## 样例 #1

### 输入

```
5
1 2 3 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
11
5 4 5 5 6 7 8 8 8 7 6
```

### 输出

```
5
```

# AI分析结果



【题目重写】
# 近似恒定范围

## 题目描述

给定一个包含 n 个数据点的序列 a₁,...,aₙ，其中相邻元素的绝对差不超过 1。寻找最长的子区间 [l,r]，使得该区间内的最大值与最小值之差不超过 1。输出最长子区间的长度。

## 样例解释
- 样例1输入 [1,2,3,3,2]，最长子区间 [2,5] 长度4
- 样例2输入 [5,4,5,5,6,7,8,8,8,7,6]，最长子区间 [6,10] 长度5

【算法分类】
滑动窗口/双指针（基于题目特性可归属为贪心策略）

【题解分析】
1. **贪心双指针法**（Holy_Push，5★）
- 核心思路：维护包含最多两种数值的滑动窗口，当新元素破坏条件时调整左边界
- 亮点：利用相邻差≤1的特性，O(n)时间复杂度，代码简洁高效
- 关键代码：
```cpp
for (int i=2;i<=n;i++) {
    if (sum1==a[i]) cnt1++;
    else if (sum2==a[i]) cnt2++;
    else { // 出现第三个数
        while (cnt1 && cnt2) { // 收缩左边界直到只剩一种数
            a[l] == sum1 ? cnt1-- : cnt2--;
            l++;
        }
        // 用新数替换空出来的类型位
        !cnt1 ? (sum1=a[i], cnt1=1) : (sum2=a[i], cnt2=1); 
    }
    ans = max(ans, cnt1 + cnt2);
}
```

2. **动态规划法**（AFOier，5★）
- 核心思路：逆向遍历维护两种状态（与当前值差±1的最长延伸长度）
- 亮点：O(n)时间复杂度，状态转移设计巧妙
- 关键代码：
```cpp
for(int i=n-1;i>=1;i--) {
    if(a[i]==a[i+1]) 
        dp[i][0] = dp[i+1][0]+1, dp[i][1] = dp[i+1][1]+1;
    else if(a[i]==a[i+1]-1) 
        dp[i][0] = dp[i+1][1]+1; // 当前比后一个大1
    else if(a[i]==a[i+1]+1) 
        dp[i][1] = dp[i+1][0]+1; // 当前比后一个小1
    ans = max(ans, max(dp[i][0], dp[i][1]));
}
```

3. **单调队列法**（pipiispig，4★）
- 核心思路：使用递增/递减双队列维护窗口极值
- 亮点：通用性强，适合未给定相邻差约束的情况
- 关键实现：
```cpp
while(窗口极差>1) {
    移动左边界并清理队列头部过期元素
}
```

【最优策略总结】
利用相邻差≤1的特性，滑动窗口只需维护两个数值类型。当新元素超出类型时，快速收缩左边界并更新类型，实现O(n)高效求解。

【举一反三】
- 类型维护技巧可拓展至允许k种数值的问题
- 动态规划状态设计思路适用于相邻元素有特定关系的场景

【推荐练习】
1. P1886 滑动窗口（单调队列经典）
2. P1440 求m区间内的最小值（区间极值维护）
3. P1714 切蛋糕（前缀和+单调队列）

---
处理用时：127.09秒