# 题目信息

# Polycarp Training

## 题目描述

Polycarp wants to train before another programming competition. During the first day of his training he should solve exactly $ 1 $ problem, during the second day — exactly $ 2 $ problems, during the third day — exactly $ 3 $ problems, and so on. During the $ k $ -th day he should solve $ k $ problems.

Polycarp has a list of $ n $ contests, the $ i $ -th contest consists of $ a_i $ problems. During each day Polycarp has to choose exactly one of the contests he didn't solve yet and solve it. He solves exactly $ k $ problems from this contest. Other problems are discarded from it. If there are no contests consisting of at least $ k $ problems that Polycarp didn't solve yet during the $ k $ -th day, then Polycarp stops his training.

How many days Polycarp can train if he chooses the contests optimally?

## 样例 #1

### 输入

```
4
3 1 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 1 1 2 2
```

### 输出

```
2
```

# AI分析结果

### 题目内容
#### Polycarp训练
1. **题目描述**：Polycarp想在另一场编程竞赛前进行训练。在训练的第一天，他要恰好解决1道题，第二天恰好解决2道题，第三天恰好解决3道题，依此类推。在第k天，他要解决k道题。
Polycarp有一个包含n场竞赛的列表，第i场竞赛由ai道题组成。在每一天，Polycarp必须从他尚未解决的竞赛中恰好选择一场并解决它。他从这场竞赛中恰好解决k道题，其他题目则从该竞赛中丢弃。如果在第k天没有剩余至少包含k道题的竞赛，那么Polycarp就停止训练。
问如果Polycarp以最优方式选择竞赛，他可以训练多少天？
2. **样例 #1**
    - **输入**：
```
4
3 1 4 1
```
    - **输出**：
```
3
```
3. **样例 #2**
    - **输入**：
```
3
1 1 1
```
    - **输出**：
```
1
```
4. **样例 #3**
    - **输入**：
```
5
1 1 1 2 2
```
    - **输出**：
```
2
```

### 算法分类
贪心

### 综合分析与结论
所有题解都采用贪心策略，核心思路是将竞赛题目数量数组从小到大排序，这样能保证小的题目数量匹配靠前的天数，使得训练天数最大化。各题解的主要差异在于代码细节和表述方式，整体思路和算法要点基本一致。

### 通用建议与扩展思路
1. **通用建议**：在解决此类贪心问题时，关键在于理解为什么贪心策略能得到最优解，即局部最优能导致全局最优。同时，注意代码实现中的边界条件处理，如天数的初始值设定以及最后输出结果是否需要调整。
2. **扩展思路**：类似的贪心题目还可能涉及资源分配、任务调度等场景，通常可以通过排序来确定元素的使用顺序，以达到最优目标。例如，给定一些任务的截止时间和完成所需时间，要求安排任务使得能完成的任务数量最多，可通过按截止时间或所需时间排序等方式采用贪心策略解决。

### 推荐题目
1. **P1094 [NOIP2007 普及组] 纪念品分组**：给定物品重量和背包容量，要求将物品分组，每组重量不超过背包容量，求最少分组数，可通过贪心策略解决。
2. **P1181 数列分段 Section II**：给定数列和分段最大和，求满足条件的最少分段数，同样可利用贪心思想结合二分查找求解。
3. **P2859 [USACO06DEC]Milk Patterns G**：在给定的奶牛产奶量序列中，寻找出现次数不少于k次的最长子串，可通过排序和贪心策略解决。 

---
处理用时：26.60秒