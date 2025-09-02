# 题目信息

# [USACO06DEC] Milk Patterns G

## 题目描述

Farmer John has noticed that the quality of milk given by his cows varies from day to day. On further investigation, he discovered that although he can't predict the quality of milk from one day to the next, there are some regular patterns in the daily milk quality.

To perform a rigorous study, he has invented a complex classification scheme by which each milk sample is recorded as an integer between 0 and 1,000,000 inclusive, and has recorded data from a single cow over N (1 ≤ N ≤ 20,000) days. He wishes to find the longest pattern of samples which repeats identically at least K (2 ≤ K ≤ N) times. This may include overlapping patterns -- 1 2 3 2 3 2 3 1 repeats 2 3 2 3 twice, for example.

Help Farmer John by finding the longest repeating subsequence in the sequence of samples. It is guaranteed that at least one subsequence is repeated at least K times.


## 样例 #1

### 输入

```
8 2
1
2
3
2
3
2
3
1```

### 输出

```
4```

# AI分析结果



### 综合分析与结论
本题核心是求至少出现k次的最长子串，主流解法集中在后缀数组（SA）、哈希二分、后缀自动机（SAM）三类。关键思路包括：
1. **后缀数组+单调队列**：利用height数组连续k-1个元素最小值代表k后缀的LCP，通过单调队列维护滑动窗口极值。
2. **后缀数组+二分+RMQ**：二分答案后用ST表验证区间最小值是否满足条件。
3. **SAM统计出现次数**：通过统计每个状态的出现次数，筛选满足条件的最大长度。

### 高星题解推荐
#### 1. 作者：kczno1（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 思路清晰，直接利用height数组连续性的性质  
- 单调队列O(n)维护滑动窗口极值，高效简洁  
- 代码实现简洁，仅需SA模板+单调队列处理  

**核心代码**：
```cpp
// 单调队列处理部分
deque<int> Q;
for(int i=1; i<=n; i++) {
    while(!Q.empty() && Q.front() <= i - k) Q.pop_front();
    while(!Q.empty() && height[Q.back()] >= height[i]) Q.pop_back();
    Q.push_back(i);
    if(i >= k) ans = max(ans, height[Q.front()]);
}
```

#### 2. 作者：hongzy（⭐⭐⭐⭐）
**关键亮点**：  
- 明确解释height数组与LCP的关系  
- 代码结构清晰，离散化处理完善  
- 使用deque实现简洁的单调队列  

**核心代码**：
```cpp
deque<int> Q;
for(int i=1; i<=n; i++) {
    while(!Q.empty() && Q.front() <= i - (k-1)) Q.pop_front();
    while(!Q.empty() && height[Q.back()] >= height[i]) Q.pop_back();
    Q.push_back(i);
    if(i >= (k-1)) ans = max(ans, height[Q.front()]);
}
```

#### 3. 作者：Treeloveswater（⭐⭐⭐⭐）
**关键亮点**：  
- 二分思路易于理解，适合新手  
- 结合离散化处理扩展性更强  
- RMQ预处理提升查询效率  

**核心代码**：
```cpp
bool check(int len) {
    int cnt = 0;
    for (int i=1; i+k-1<=n; i++) 
        if (query_min(i, i+k-2) >= len) return true;
    return false;
}
```

### 关键思路总结
1. **后缀数组核心应用**：利用height数组的区间最小值性质，结合滑动窗口极值算法（单调队列）或二分+RMQ。
2. **离散化优化**：处理大值域时对输入数据进行离散化，降低SA的基数排序复杂度。
3. **滑动窗口极值**：单调队列维护窗口最小值是处理连续区间问题的经典技巧。

### 扩展建议
- **同类问题**：最长重复k次不可重叠子串（POJ 1743）、统计不同子串个数（P2408）。
- **推荐题目**：  
  1. [P3804 【模板】后缀自动机](https://www.luogu.com.cn/problem/P3804)  
  2. [P3975 [TJOI2015]弦论](https://www.luogu.com.cn/problem/P3975)  
  3. [P4070 [SDOI2016]生成魔咒](https://www.luogu.com.cn/problem/P4070)  

### 个人心得摘录
> "出现k次相当于选择k个后缀，求最长公共前缀。连续k个后缀的height最小值即为答案。"  
> —— kczno1  
> 总结：抓住height数组的连续性特征是解题关键，将抽象问题转化为区间极值问题。

---
处理用时：62.39秒