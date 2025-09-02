# 题目信息

# LCIS

## 题目描述

This problem differs from one which was on the online contest.

The sequence $ a_{1},a_{2},...,a_{n} $ is called increasing, if $ a_{i}<a_{i+1} $ for $ i<n $ .

The sequence $ s_{1},s_{2},...,s_{k} $ is called the subsequence of the sequence $ a_{1},a_{2},...,a_{n} $ , if there exist such a set of indexes $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ that $ a_{ij}=s_{j} $ . In other words, the sequence $ s $ can be derived from the sequence $ a $ by crossing out some elements.

You are given two sequences of integer numbers. You are to find their longest common increasing subsequence, i.e. an increasing sequence of maximum length that is the subsequence of both sequences.

## 样例 #1

### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6
```

### 输出

```
3
3 5 6 
```

## 样例 #2

### 输入

```
5
1 2 0 2 1
3
1 0 1
```

### 输出

```
2
0 1 
```

# AI分析结果



# LCIS（题目中文翻译）

## 题目描述

这个问题与在线比赛中的某个题目有所不同。

序列 $ a_{1},a_{2},...,a_{n} $ 被称为递增的，如果对于所有 $ i < n $ 有 $ a_{i} < a_{i+1} $。

序列 $ s_{1},s_{2},...,s_{k} $ 被称为序列 $ a_{1},a_{2},...,a_{n} $ 的子序列，如果存在一组下标 $ 1 \leq i_{1} < i_{2} < ... < i_{k} \leq n $，使得 $ a_{i_j} = s_j $。换句话说，序列 $ s $ 可以通过从序列 $ a $ 中删除一些元素得到。

给定两个整数序列，你需要找到它们的最长公共上升子序列，即同时是两个序列子序列的最长递增序列。

## 样例 #1

### 输入
```
7
2 3 1 6 5 4 6
4
1 3 5 6
```

### 输出
```
3
3 5 6 
```

## 样例 #2

### 输入
```
5
1 2 0 2 1
3
1 0 1
```

### 输出
```
2
0 1 
```

---

# 题解综合分析

## 最优算法思路总结
**关键技巧：动态规划+双优化**
1. **状态定义**：`f[i][j]` 表示考虑数组 `a` 前 `i` 个元素，以 `b[j]` 结尾的 LCIS 长度
2. **转移优化**：利用 `val` 维护满足 `b[k] < a[i]` 时的最大 `f[i-1][k]`，将 O(n³) 优化为 O(n²)
3. **路径记录**：使用 `pre` 数组记录前驱节点，通过反向回溯构造最终序列

## 高星题解推荐

### 题解1：李若谷（⭐⭐⭐⭐⭐）
**核心亮点**：
- 时间复杂度优化至 O(n²) 的完整实现
- 通过维护 `val` 变量消除内层循环
- 路径记录采用前驱指针方式，空间效率高
```cpp
for(int i=1;i<=n;i++) {
    int val = 0, pos = 0;
    for(int j=1;j<=m;j++) {
        if(a[i] == b[j]) {
            f[i][j] = val + 1;
            pre[i][j] = pos;  // 记录前驱位置
        } else {
            f[i][j] = f[i-1][j];
        }
        if(b[j] < a[i] && f[i-1][j] > val) {
            val = f[i-1][j];  // 维护最大值
            pos = j;          // 记录转移来源
        }
    }
}
```

### 题解2：Hanzire76（⭐⭐⭐⭐）
**核心亮点**：
- 决策集合优化的清晰数学解释
- 给出状态转移的完整推导过程
```cpp
for(int i=1;i<=n;i++) {
    int val=0;
    for(int j=1;j<=m;j++) {
        if(a[i]==b[j]) dp[i][j] = val+1;
        else dp[i][j] = dp[i-1][j];
        if(b[j]<a[i]) val = max(val, dp[i-1][j]);
    }
}
```

---

# 拓展与总结

## 关键优化思想
1. **决策集合单调性**：当 `j` 递增时，`k` 的取值范围单调扩大，可用变量维护当前最大值
2. **状态复用**：利用滚动数组思想，`i` 维度可以优化为两行以节省空间

## 类似题目推荐
1. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)（LCS 优化）
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（LIS 变形）
3. [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)（二维偏序+LIS）

## 调试心得摘录
> "在循环 j 时，i 是定值，因此可以维护一个全局最大值变量" —— 李若谷  
> "决策集合 S(i,j) 随着 j 增加而单调扩展，只需检查新增元素" —— Hanzire76  
> "初始化 a[0]=b[0]=-INF 处理边界条件非常重要" —— Xx_queue

---
处理用时：58.52秒