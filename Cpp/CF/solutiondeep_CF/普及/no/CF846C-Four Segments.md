# 题目信息

# Four Segments

## 题目描述

You are given an array of $ n $ integer numbers. Let $ sum(l,r) $ be the sum of all numbers on positions from $ l $ to $ r $ non-inclusive ( $ l $ -th element is counted, $ r $ -th element is not counted). For indices $ l $ and $ r $ holds $ 0<=l<=r<=n $ . Indices in array are numbered from $ 0 $ .

For example, if $ a=[-5,3,9,4] $ , then $ sum(0,1)=-5 $ , $ sum(0,2)=-2 $ , $ sum(1,4)=16 $ and $ sum(i,i)=0 $ for each $ i $ from $ 0 $ to $ 4 $ .

Choose the indices of three delimiters $ delim_{0} $ , $ delim_{1} $ , $ delim_{2} $ ( $ 0<=delim_{0}<=delim_{1}<=delim_{2}<=n $ ) and divide the array in such a way that the value of $ res=sum(0,delim_{0}) $ - $ sum(delim_{0},delim_{1}) $ + $ sum(delim_{1},delim_{2}) $ - $ sum(delim_{2},n) $ is maximal.

Note that some of the expressions $ sum(l,r) $ can correspond to empty segments (if $ l=r $ for some segment).

## 样例 #1

### 输入

```
3
-1 2 3
```

### 输出

```
0 1 3
```

## 样例 #2

### 输入

```
4
0 0 -1 0
```

### 输出

```
0 0 0
```

## 样例 #3

### 输入

```
1
10000
```

### 输出

```
1 1 1
```

# AI分析结果



# Four Segments

## 题目描述

给定一个包含 $n$ 个整数的数组。定义 $sum(l,r)$ 表示从位置 $l$ 到 $r$（不包含 $r$）的元素之和（满足 $0 \leq l \leq r \leq n$）。需要选择三个分界点 $delim_0 \leq delim_1 \leq delim_2$，使得 $res = sum(0,delim_0) - sum(delim_0,delim_1) + sum(delim_1,delim_2) - sum(delim_2,n)$ 的值最大。

## 样例 #1

### 输入

```
3
-1 2 3
```

### 输出

```
0 1 3
```

---

## 算法分类
**动态规划**（核心解法涉及状态转移与多阶段决策）

---

## 题解对比分析

### 高星题解推荐

#### 1. Sol1 的线性动态规划解法（⭐⭐⭐⭐⭐）
**核心亮点**：
- 将四段划分转化为四个状态转移阶段，定义 $dp[i][j]$ 表示前 $i$ 个元素划分到第 $j$ 段的最大值
- 通过符号交替变化设计状态转移方程，实现 $O(n)$ 时间复杂度
- 路径回溯机制确保能输出具体分界点

**代码核心**：
```cpp
long long dp[5005][5], a[5005];
memset(dp, 0xcf, sizeof(dp)); 
dp[0][1] = 0;  // 初始化第一个段

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 4; j++) {
        for (int k = 1; k <= j; k++) {  // 从前k段转移
            long long cur = ((j & 1) ? 1 : -1) * a[i] + dp[i - 1][k];
            if (cur > dp[i][j]) {
                dp[i][j] = cur;
                path[i][j] = k;  // 记录转移路径
            }
        }
    }
}
```

#### 2. Uuuuuur_ 的分步贪心解法（⭐⭐⭐⭐）
**核心亮点**：
- 枚举中间分界点 $j$，分别独立求解左右最优解
- 利用前缀和快速计算区间和，时间复杂度 $O(n^2)$
- 代码直观易懂，适合小规模数据

**实现要点**：
```cpp
for (int j = 0; j <= n; j++) {
    // 求左侧最优i
    ll max_left = -inf;
    for (int i = 0; i <= j; i++) 
        max_left = max(max_left, sum(0,i) - sum(i,j));
    
    // 求右侧最优k
    ll max_right = -inf;
    for (int k = j; k <= n; k++)
        max_right = max(max_right, sum(j,k) - sum(k,n));
    
    // 更新全局最优解
    if (max_left + max_right > ans) 更新分界点
}
```

---

## 关键思路总结
1. **状态划分思想**：将四段划分转化为四个阶段的状态转移，通过动态规划记录最优值
2. **符号交替处理**：利用奇偶性判断加减符号，统一状态转移方程的形式
3. **路径回溯机制**：通过记录转移路径，逆向推导分界点位置

---

## 拓展与心得
**同类问题套路**：
- 多段划分最值问题可考虑动态规划状态设计（如[最大子数组和](https://www.luogu.com.cn/problem/P1115)）
- 交替符号表达式可尝试分解为分阶段决策问题
- 路径回溯技巧适用于需要输出具体方案的动态规划问题

**调试心得**：
> "十年OI一场空，不开long long见祖宗" —— 数据范围分析不足会导致溢出错误

---

## 推荐习题
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（一维最值问题）
2. [P2679 子串](https://www.luogu.com.cn/problem/P2679)（多维动态规划）
3. [P2367 区间分割](https://www.luogu.com.cn/problem/P2367)（多段划分优化）

---
处理用时：128.03秒