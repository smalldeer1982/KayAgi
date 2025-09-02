# 题目信息

# Bricks and Bags

## 题目描述

There are $ n $ bricks numbered from $ 1 $ to $ n $ . Brick $ i $ has a weight of $ a_i $ .

Pak Chanek has $ 3 $ bags numbered from $ 1 $ to $ 3 $ that are initially empty. For each brick, Pak Chanek must put it into one of the bags. After this, each bag must contain at least one brick.

After Pak Chanek distributes the bricks, Bu Dengklek will take exactly one brick from each bag. Let $ w_j $ be the weight of the brick Bu Dengklek takes from bag $ j $ . The score is calculated as $ |w_1 - w_2| + |w_2 - w_3| $ , where $ |x| $ denotes the absolute value of $ x $ .

It is known that Bu Dengklek will take the bricks in such a way that minimises the score. What is the maximum possible final score if Pak Chanek distributes the bricks optimally?

## 说明/提示

In the first test case, one way of achieving a final score of $ 6 $ is to do the following:

- Put bricks $ 1 $ , $ 4 $ , and $ 5 $ into bag $ 1 $ .
- Put brick $ 3 $ into bag $ 2 $ .
- Put brick $ 2 $ into bag $ 3 $ .

If Pak Chanek distributes the bricks that way, a way Bu Dengklek can take the bricks is:

- Take brick $ 5 $ from bag $ 1 $ .
- Take brick $ 3 $ from bag $ 2 $ .
- Take brick $ 2 $ from bag $ 3 $ .

The score is $ |a_5 - a_3| + |a_3 - a_2| = |3 - 5| + |5 - 1| = 6 $ . It can be shown that Bu Dengklek cannot get a smaller score from this distribution.

It can be shown that there is no other distribution that results in a final score bigger than $ 6 $ .

## 样例 #1

### 输入

```
3
5
3 1 5 2 3
4
17 8 19 45
8
265 265 265 265 265 265 265 265```

### 输出

```
6
63
0```

# AI分析结果

### 题目内容重写

#### 题目描述

有 $n$ 块砖，编号从 $1$ 到 $n$。第 $i$ 块砖的重量为 $a_i$。

Pak Chanek 有 $3$ 个袋子，编号从 $1$ 到 $3$，初始时为空。对于每块砖，Pak Chanek 必须将其放入其中一个袋子中。分配完成后，每个袋子必须至少包含一块砖。

在 Pak Chanek 分配完砖块后，Bu Dengklek 会从每个袋子中恰好取出一块砖。设 $w_j$ 为 Bu Dengklek 从第 $j$ 个袋子中取出的砖的重量。得分的计算公式为 $|w_1 - w_2| + |w_2 - w_3|$，其中 $|x|$ 表示 $x$ 的绝对值。

已知 Bu Dengklek 会以最小化得分的方式取砖。如果 Pak Chanek 以最优方式分配砖块，那么最终得分的最大可能值是多少？

#### 说明/提示

在第一个测试用例中，实现最终得分为 $6$ 的一种方式如下：

- 将砖块 $1$、$4$ 和 $5$ 放入袋子 $1$。
- 将砖块 $3$ 放入袋子 $2$。
- 将砖块 $2$ 放入袋子 $3$。

如果 Pak Chanek 以这种方式分配砖块，Bu Dengklek 可以按以下方式取砖：

- 从袋子 $1$ 中取出砖块 $5$。
- 从袋子 $2$ 中取出砖块 $3$。
- 从袋子 $3$ 中取出砖块 $2$。

得分为 $|a_5 - a_3| + |a_3 - a_2| = |3 - 5| + |5 - 1| = 6$。可以证明，Bu Dengklek 无法从这种分配方式中获得更小的得分。

可以证明，没有其他分配方式能使最终得分大于 $6$。

#### 样例 #1

##### 输入

```
3
5
3 1 5 2 3
4
17 8 19 45
8
265 265 265 265 265 265 265 265
```

##### 输出

```
6
63
0
```

### 算法分类

贪心

### 题解分析与结论

本题的核心在于如何将砖块分配到三个袋子中，使得 Bu Dengklek 在最小化得分的情况下，得分尽可能大。通过分析，可以将问题转化为对砖块重量的排序和分类讨论，最终通过贪心策略找到最优解。

### 所选高星题解

#### 题解作者：lenlen (赞：19)

**星级：5星**

**关键亮点：**
- 通过排序和分类讨论，简化了问题的复杂度。
- 提出了三种情况，并排除了不优的情况，最终通过枚举找到最大值。
- 代码简洁且高效，时间复杂度为 $O(n \log n)$。

**代码核心思想：**
- 首先对数组进行排序。
- 分别枚举两种情况，计算最大值：
  - 第一种情况：$w = a_n + a_{i+1} - 2 \times a_i$
  - 第二种情况：$w = 2 \times a_i - a_{i-1} - a_1$
- 取两种情况的最大值作为最终答案。

**核心代码：**
```cpp
for(int i=3;i<=n;i++) ans=max(ans,2*a[i]-a[i-1]-a[1]);
for(int i=1;i<n-1;i++) ans=max(ans,a[n]+a[i+1]-2*a[i]);
```

#### 题解作者：Daidly (赞：0)

**星级：4星**

**关键亮点：**
- 通过分析 $w_1, w_2, w_3$ 之间的关系，提出了两种最优策略。
- 通过枚举集合 $2$ 的前后缀，找到最大值。
- 代码清晰，逻辑严谨。

**代码核心思想：**
- 对数组进行排序。
- 分别枚举集合 $2$ 为前缀和后缀的情况，计算最大值：
  - 集合 $2$ 为前缀时，$w = a_{i+1} - a_i + a_n - a_i$
  - 集合 $2$ 为后缀时，$w = a_i - a_{i-1} + a_i - a_1$
- 取两种情况的最大值作为最终答案。

**核心代码：**
```cpp
for(int i=1;i<=n-2;++i) ans=max(ans,a[i+1]-a[i]+a[n]-a[i]);
for(int i=n;i>=3;--i) ans=max(ans,a[i]-a[i-1]+a[i]-a[1]);
```

### 最优关键思路

1. **排序**：首先对砖块的重量进行排序，简化问题。
2. **分类讨论**：通过分析 $w_1, w_2, w_3$ 之间的关系，排除不优的情况，只考虑最优的两种情况。
3. **枚举**：通过枚举可能的分配方式，计算最大值。

### 可拓展之处

本题的贪心策略可以推广到类似的分配问题中，尤其是涉及到最小化或最大化某种得分的情况。类似的题目可以通过排序和分类讨论来简化问题，找到最优解。

### 推荐题目

1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：36.68秒