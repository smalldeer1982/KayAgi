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

### 题目内容重写

#### LCIS

#### 题目描述

这个问题与在线竞赛中的一个问题有所不同。

序列 $ a_{1},a_{2},...,a_{n} $ 被称为递增的，如果对于所有 $ i<n $，都有 $ a_{i}<a_{i+1} $。

序列 $ s_{1},s_{2},...,s_{k} $ 被称为序列 $ a_{1},a_{2},...,a_{n} $ 的子序列，如果存在一组索引 $ 1<=i_{1}<i_{2}<...<i_{k}<=n $，使得 $ a_{ij}=s_{j} $。换句话说，序列 $ s $ 可以通过从序列 $ a $ 中删除一些元素得到。

给定两个整数序列，你需要找到它们的最长公共递增子序列，即一个最长的递增序列，它同时是两个序列的子序列。

#### 样例 #1

##### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6
```

##### 输出

```
3
3 5 6 
```

#### 样例 #2

##### 输入

```
5
1 2 0 2 1
3
1 0 1
```

##### 输出

```
2
0 1 
```

---

### 题解分析与结论

#### 综合分析

本题是LCS（最长公共子序列）和LIS（最长递增子序列）的结合，要求找到两个序列的最长公共递增子序列（LCIS）。题解中主要采用了动态规划（DP）的方法，时间复杂度从$O(n^3)$优化到$O(n^2)$。

#### 最优关键思路

1. **状态定义**：$f[i][j]$表示以$b[j]$结尾的，与$a$数组前$i$个数匹配的最长公共递增子序列的长度。
2. **状态转移**：
   - 如果$a[i] \neq b[j]$，则$f[i][j] = f[i-1][j]$。
   - 如果$a[i] = b[j]$，则$f[i][j] = \max(f[i-1][k] + 1)$，其中$0 \leq k < j$且$b[k] < a[i]$。
3. **优化**：通过维护一个变量`val`来记录前$j$个最大的$f[i][j]$，从而省去$k$的循环，将时间复杂度从$O(n^3)$优化到$O(n^2)$。

#### 推荐题解

1. **作者：李若谷 (赞：9)**  
   - **星级**：★★★★★  
   - **关键亮点**：通过维护变量`val`优化了时间复杂度，代码清晰，路径输出处理得当。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
     {
         int val = 0;
         int pos = 0;
         for(int j=1;j<=m;j++)
         {
             f[i][j] = f[i-1][j];
             pre[i][j] = j;
             if(a[i] == b[j])
             {
                 if(f[i][j] < val+1)
                 {
                     f[i][j] = val + 1;
                     pre[i][j] = pos;
                 }
             }
             if(b[j] < a[i])
             {
                 if(f[i-1][j] > val) 
                 {
                     val = f[i-1][j];
                     pos = j;
                 }
             }
         }
     }
     ```

2. **作者：Hanzire76 (赞：1)**  
   - **星级**：★★★★  
   - **关键亮点**：详细解释了状态转移方程，优化思路清晰，代码简洁。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
     {
         int val=0;
         if(b[0]<a[i]) val=dp[i-1][0];
         for(int j=1;j<=m;j++)
         {
             if(a[i]==b[j])
             {
                 dp[i][j]=val+1;
                 if(Max<dp[i][j]) Max=dp[i][j],x=i,y=j;
             }
             else dp[i][j]=dp[i-1][j];
             if(b[j]<a[i]) val=max(val,dp[i-1][j]);
         }
     }
     ```

#### 扩展思路

1. **同类型题**：可以尝试解决LCS和LIS的单独问题，以及它们的变种问题。
2. **类似算法套路**：动态规划在解决序列问题中的应用，如最长公共子序列、最长递增子序列等。

#### 推荐题目

1. **P1020 导弹拦截**（LIS问题）
2. **P1439 【模板】最长公共子序列**（LCS问题）
3. **P1091 合唱队形**（LIS与LDS结合问题）

#### 个人心得摘录

- **调试经历**：在优化过程中，发现$k$循环的重复计算，通过维护变量`val`成功优化了时间复杂度。
- **踩坑教训**：初始化$a[0]$和$b[0]$为$-inf$，避免第一个元素被漏掉。
- **顿悟感想**：动态规划的状态转移方程设计是关键，理解每个状态的含义和转移条件是解决问题的核心。

---
处理用时：39.89秒