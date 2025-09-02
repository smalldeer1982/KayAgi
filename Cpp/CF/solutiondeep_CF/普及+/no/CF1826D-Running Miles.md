# 题目信息

# Running Miles

## 题目描述

There is a street with $ n $ sights, with sight number $ i $ being $ i $ miles from the beginning of the street. Sight number $ i $ has beauty $ b_i $ . You want to start your morning jog $ l $ miles and end it $ r $ miles from the beginning of the street. By the time you run, you will see sights you run by (including sights at $ l $ and $ r $ miles from the start). You are interested in the $ 3 $ most beautiful sights along your jog, but every mile you run, you get more and more tired.

So choose $ l $ and $ r $ , such that there are at least $ 3 $ sights you run by, and the sum of beauties of the $ 3 $ most beautiful sights minus the distance in miles you have to run is maximized. More formally, choose $ l $ and $ r $ , such that $ b_{i_1} + b_{i_2} + b_{i_3} - (r - l) $ is maximum possible, where $ i_1, i_2, i_3 $ are the indices of the three maximum elements in range $ [l, r] $ .

## 说明/提示

In the first example, we can choose $ l $ and $ r $ to be $ 1 $ and $ 5 $ . So we visit all the sights and the three sights with the maximum beauty are the sights with indices $ 1 $ , $ 3 $ , and $ 5 $ with beauties $ 5 $ , $ 4 $ , and $ 3 $ , respectively. So the total value is $ 5 + 4 + 3 - (5 - 1) = 8 $ .

In the second example, the range $ [l, r] $ can be $ [1, 3] $ or $ [2, 4] $ , the total value is $ 1 + 1 + 1 - (3 - 1) = 1 $ .

## 样例 #1

### 输入

```
4
5
5 1 4 2 3
4
1 1 1 1
6
9 8 7 6 5 4
7
100000000 1 100000000 1 100000000 1 100000000```

### 输出

```
8
1
22
299999996```

# AI分析结果

### 题目内容重写

#### 题目描述

有一条街道上有 $n$ 个景点，第 $i$ 个景点距离街道起点 $i$ 英里。第 $i$ 个景点的美丽值为 $b_i$。你计划在早上跑步，从距离起点 $l$ 英里的地方开始，到距离起点 $r$ 英里的地方结束。跑步时，你会经过并看到沿途的所有景点（包括起点和终点的景点）。你对你跑步过程中经过的最美丽的 $3$ 个景点感兴趣，但每跑一英里，你会感到越来越累。

因此，你需要选择 $l$ 和 $r$，使得你跑步过程中至少经过 $3$ 个景点，并且这 $3$ 个最美丽景点的美丽值之和减去你跑步的距离（英里数）最大。更正式地说，选择 $l$ 和 $r$，使得 $b_{i_1} + b_{i_2} + b_{i_3} - (r - l)$ 最大，其中 $i_1, i_2, i_3$ 是区间 $[l, r]$ 内美丽值最大的三个景点的索引。

#### 说明/提示

在第一个样例中，我们可以选择 $l$ 和 $r$ 分别为 $1$ 和 $5$。这样我们会经过所有景点，其中美丽值最大的三个景点分别是第 $1$、$3$ 和 $5$ 个景点，美丽值分别为 $5$、$4$ 和 $3$。因此，总值为 $5 + 4 + 3 - (5 - 1) = 8$。

在第二个样例中，区间 $[l, r]$ 可以是 $[1, 3]$ 或 $[2, 4]$，总值为 $1 + 1 + 1 - (3 - 1) = 1$。

#### 样例 #1

##### 输入

```
4
5
5 1 4 2 3
4
1 1 1 1
6
9 8 7 6 5 4
7
100000000 1 100000000 1 100000000 1 100000000
```

##### 输出

```
8
1
22
299999996
```

### 算法分类
动态规划

### 题解分析与结论

#### 综合分析

本题的核心在于如何高效地选择一个区间 $[l, r]$，使得在该区间内选择三个最美丽的景点，并且它们的美丽值之和减去区间长度最大。题解中主要采用了动态规划的思路，通过预处理前缀和后缀的最大值来优化计算。

#### 关键思路与技巧

1. **贡献拆分**：将问题拆分为 $b_l + b_r + b_i - (r - l)$，并进一步转化为 $L(l) + b_i + R(r)$，其中 $L(l) = b_l + l$，$R(r) = b_r - r$。这种拆分使得问题可以分别处理左右两边的贡献。
  
2. **预处理前缀和后缀最大值**：通过预处理 $L(i)$ 的前缀最大值和 $R(i)$ 的后缀最大值，可以在 $O(1)$ 时间内计算每个 $i$ 的贡献。

3. **枚举中间点**：通过枚举中间点 $i$，分别计算左边和右边的最大贡献，从而得到全局最大值。

#### 题解评分与亮点

1. **作者：hello_world_djh (5星)**
   - **关键亮点**：贡献拆分的思路清晰，预处理前缀和后缀最大值的优化方法简洁高效。
   - **代码实现**：通过预处理 $L(i)$ 和 $R(i)$ 的前缀和后缀最大值，枚举中间点 $i$ 计算贡献。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], a[i] + i);
     for (int i = n; i >= 1; i--) suf[i] = max(suf[i + 1], a[i] - i);
     for (int i = 2; i < n; i++) ans = max(ans, pre[i - 1] + a[i] + suf[i + 1]);
     ```

2. **作者：ForgotDream_CHN (4星)**
   - **关键亮点**：通过递推预处理 $f_j$ 和 $g_j$，避免了单调栈的使用，简化了实现。
   - **代码实现**：通过递推预处理 $f_j$ 和 $g_j$，枚举中间点 $j$ 计算贡献。
   - **核心代码**：
     ```cpp
     for (int i = 1; i < n; i++) f[0][i] = max(f[0][i - 1], b[i - 1]) - 1;
     for (int i = n - 2; i >= 0; i--) f[1][i] = max(f[1][i + 1], b[i + 1]) - 1;
     for (int i = 1; i < n - 1; i++) ans = max(ans, f[0][i] + f[1][i] + b[i]);
     ```

3. **作者：falling_cloud (4星)**
   - **关键亮点**：通过贡献下发的思路，将问题转化为 $c_{i_1} + a_{i_2} + b_{i_3}$ 的最大值，简化了计算。
   - **代码实现**：通过预处理 $b_i$ 和 $c_i$，枚举中间点 $i$ 计算贡献。
   - **核心代码**：
     ```cpp
     for(i=2;i<=n;i++) {
         ans=max(ans,sum+c[i]);
         sum=max(sum,a[i]+la);
         la=max(la,b[i]);
     }
     ```

### 扩展思路

本题的解法可以推广到类似的选择区间并计算某种贡献最大化的问题。例如，选择区间内的最大值、最小值、或者某种组合的最大值减去区间长度的问题，都可以采用类似的贡献拆分和预处理的方法。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

### 个人心得

在实现过程中，预处理前缀和后缀最大值时，需要注意边界条件的处理，避免数组越界。此外，枚举中间点时，确保左右两边都有足够的元素可供选择，避免出现无效区间。

---
处理用时：50.66秒