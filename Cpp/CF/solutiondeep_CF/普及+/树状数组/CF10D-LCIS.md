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

### 题目翻译
## 最长公共上升子序列（LCIS）

### 题目描述
本题与在线竞赛中的题目有所不同。

如果对于 $i < n$ 都有 $a_{i} < a_{i + 1}$，则序列 $a_{1}, a_{2}, \cdots, a_{n}$ 被称为递增序列。

如果存在一组索引 $1 \leq i_{1} < i_{2} < \cdots < i_{k} \leq n$ 使得 $a_{i_{j}} = s_{j}$，则序列 $s_{1}, s_{2}, \cdots, s_{k}$ 被称为序列 $a_{1}, a_{2}, \cdots, a_{n}$ 的子序列。换句话说，序列 $s$ 可以通过从序列 $a$ 中删除一些元素得到。

给定两个整数序列，你需要找出它们的最长公共上升子序列，即一个长度最大的递增序列，它同时是这两个序列的子序列。

### 样例 #1
#### 输入
```
7
2 3 1 6 5 4 6
4
1 3 5 6
```
#### 输出
```
3
3 5 6 
```

### 样例 #2
#### 输入
```
5
1 2 0 2 1
3
1 0 1
```
#### 输出
```
2
0 1 
```

### 题解综合分析与结论
这几道题解均围绕最长公共上升子序列（LCIS）问题展开，核心思路是通过动态规划求解。定义状态 $f[i][j]$ 表示以 $b[j]$ 结尾，与 $a$ 数组前 $i$ 个数匹配的最长公共上升子序列长度。

- **思路对比**：Nishikino_Curtis、Xx_queue 和 Hanzire76 都给出了 $O(n^3)$ 的基础状态转移方程，当 $a[i] \neq b[j]$ 时，$f[i][j] = f[i - 1][j]$；当 $a[i] = b[j]$ 时，$f[i][j] = \max\{f[i - 1][k]\} + 1$（$0 \leq k < j$ 且 $b[k] < a[i]$）。李若谷和 Hanzire76 进一步将时间复杂度优化到了 $O(n^2)$，通过用一个变量存储前 $j$ 个最大的 $f[i][k]$ 避免了重复计算。
- **算法要点**：基础算法需要三重循环枚举 $i$、$j$、$k$ 进行状态转移；优化算法通过记录最大值减少一层循环。在路径输出方面，Nishikino_Curtis 维护方案数组，李若谷记录状态转移来源，Xx_queue 采用递归输出。
- **解决难点**：主要难点在于状态转移方程的推导和路径输出的实现。优化算法的难点在于发现并利用状态转移中的重复计算进行优化。

### 所选题解
- **李若谷（5星）**
    - **关键亮点**：思路清晰，详细解释了从 $O(n^3)$ 到 $O(n^2)$ 的优化过程，代码可读性高，路径输出部分处理得当。
    - **核心代码**：
```cpp
for(register int i=1;i<=n;i++)
{
    int val = 0;
    int pos = 0;
    for(register int j=1;j<=m;j++)
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
核心思想：在遍历 $j$ 时，用变量 $val$ 记录前 $j$ 个满足条件的最大 $f[i - 1][k]$，避免了重复的 $k$ 循环。

- **Hanzire76（4星）**
    - **关键亮点**：对状态转移方程解释清晰，重点突出了优化思路，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。
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
核心思想：同样用变量 $val$ 记录满足条件的最大 $dp[i - 1][k]$，在 $j$ 增加时动态更新 $val$。

### 最优关键思路或技巧
- **动态规划状态定义**：定义 $f[i][j]$ 表示以 $b[j]$ 结尾，与 $a$ 数组前 $i$ 个数匹配的最长公共上升子序列长度，便于状态转移。
- **优化技巧**：利用状态转移中的重复计算，用一个变量记录前 $j$ 个最大的 $f[i - 1][k]$，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 拓展思路
同类型题目可以是多个序列的最长公共上升子序列问题，或者在序列上增加一些限制条件，如元素取值范围、元素个数限制等。算法套路仍然是通过合理定义状态和状态转移方程，利用动态规划求解。

### 洛谷相似题目推荐
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
- [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
- [P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)

### 个人心得摘录与总结
- **Xx_queue**：提到要初始化 $A_0 = B_0 = -\infty$，否则可能检测不到第一个元素而导致错误，如第二个样例就会WA。总结：在处理动态规划问题时，边界条件的初始化非常重要，需要仔细考虑，避免因边界问题导致错误。 

---
处理用时：34.18秒