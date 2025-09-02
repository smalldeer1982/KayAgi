# 题目信息

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

小苏西每天睡前都会听童话故事。今天的童话故事是关于伐木工人的，小女孩立刻开始想象伐木工人砍伐树木的情景。她想象了以下场景：

在一条路上有 $n$ 棵树，分别位于坐标 $x_{1},x_{2},...,x_{n}$ 处。每棵树的高度为 $h_{i}$。伐木工人可以砍倒一棵树，并将其向左或向右倒下。倒下后，树会占据区间 $[x_{i}-h_{i},x_{i}]$ 或 $[x_{i};x_{i}+h_{i}]$。未被砍倒的树仍然占据坐标点 $x_{i}$。伐木工人可以砍倒一棵树，前提是倒下后占据的区间不包含任何已被占据的点。伐木工人希望尽可能多地砍倒树木，因此苏西想知道，最多可以砍倒多少棵树。

**说明/提示**

在第一个样例中，可以按以下方式砍倒树木：

- 将第 $1$ 棵树向左倒下——现在它占据区间 $[-1;1]$
- 将第 $2$ 棵树向右倒下——现在它占据区间 $[2;3]$
- 保留第 $3$ 棵树——它占据点 $5$
- 保留第 $4$ 棵树——它占据点 $10$
- 将第 $5$ 棵树向右倒下——现在它占据区间 $[19;20]$

在第二个样例中，也可以将第 $4$ 棵树向右倒下，之后它将占据区间 $[10;19]$。

**样例 #1**

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

**样例 #2**

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

### 题解综合分析与结论

本题的主要目标是通过贪心算法或动态规划来求解最多可以砍倒的树木数量。大多数题解采用了贪心算法，优先让树木向左倒下，若无法向左倒下则考虑向右倒下，最后才选择不砍倒。这种贪心策略的合理性在于，优先向左倒下不会影响后续树木的选择，而向右倒下可能会影响下一棵树的选择，但通过合理的处理，仍然可以保证最优解。

### 所选高分题解

#### 题解1：作者：yzx72424 (赞：24)
- **星级**：5星
- **关键亮点**：简洁明了的贪心策略，优先向左倒下，若无法向左倒下则考虑向右倒下，最后选择不砍倒。代码实现清晰，逻辑简单。
- **代码核心思想**：
  ```cpp
  for(int i=2;i<=a-1;i++){
      if(xx[i]-h[i]>xx[i-1])t++;
      else if(xx[i]+h[i]<xx[i+1]){
          t++;xx[i]+=h[i];
      }
  }
  ```
  **核心代码**：
  ```cpp
  for(int i=2;i<=a-1;i++){
      if(xx[i]-h[i]>xx[i-1])t++;
      else if(xx[i]+h[i]<xx[i+1]){
          t++;xx[i]+=h[i];
      }
  }
  ```

#### 题解2：作者：ddmd (赞：7)
- **星级**：4星
- **关键亮点**：详细解释了贪心策略的正确性，优先向左倒下，若无法向左倒下则考虑向右倒下，最后选择不砍倒。代码实现较为清晰。
- **代码核心思想**：
  ```cpp
  for(int i=2;i<n;i++){
      if(x[i]-x[i-1]>h[i]) ans++;
      else if(x[i+1]-x[i]>h[i]) ans++, x[i]+=h[i];
  }
  ```
  **核心代码**：
  ```cpp
  for(int i=2;i<n;i++){
      if(x[i]-x[i-1]>h[i]) ans++;
      else if(x[i+1]-x[i]>h[i]) ans++, x[i]+=h[i];
  }
  ```

#### 题解3：作者：When (赞：4)
- **星级**：4星
- **关键亮点**：对贪心策略进行了详细的分类讨论，解释了为什么优先向左倒下是最优的，并提供了代码实现。
- **代码核心思想**：
  ```cpp
  for(int i=2;i<n;++i){
      if(t[i].x - t[i-1].x > t[i].h) ans++;
      else if(t[i+1].x - t[i].x > t[i].h) ans++, t[i].x += t[i].h;
  }
  ```
  **核心代码**：
  ```cpp
  for(int i=2;i<n;++i){
      if(t[i].x - t[i-1].x > t[i].h) ans++;
      else if(t[i+1].x - t[i].x > t[i].h) ans++, t[i].x += t[i].h;
  }
  ```

### 最优关键思路或技巧

1. **贪心策略**：优先让树木向左倒下，若无法向左倒下则考虑向右倒下，最后选择不砍倒。这种策略保证了每一步的局部最优，最终达到全局最优。
2. **动态规划**：部分题解采用了动态规划的思路，通过状态转移方程来求解最优解，但实现较为复杂，贪心算法更为简洁高效。

### 可拓展之处

- **类似问题**：在处理区间覆盖或选择问题时，贪心算法通常是一种有效的策略。例如，区间调度问题、区间覆盖问题等。
- **算法优化**：在某些情况下，动态规划可以进一步优化贪心算法的结果，特别是在需要考虑更多约束条件时。

### 推荐相似题目

1. [P2887 [USACO07NOV]Sunscreen G](https://www.luogu.com.cn/problem/P2887)
2. [P2859 [USACO06FEB]Stall Reservations S](https://www.luogu.com.cn/problem/P2859)
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)

### 个人心得摘录

- **调试经历**：部分题解中提到在处理边界条件时容易出错，特别是在处理第一棵树和最后一棵树时，需要特别注意。
- **踩坑教训**：在贪心算法中，优先向左倒下是最优的，但若无法向左倒下，则需要谨慎处理向右倒下的情况，避免影响后续树木的选择。
- **顿悟感想**：贪心算法在处理区间选择问题时，通常能够通过局部最优达到全局最优，但需要仔细验证每一步的正确性。

---
处理用时：53.11秒