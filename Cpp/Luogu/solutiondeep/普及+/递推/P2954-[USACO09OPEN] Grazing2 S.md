# 题目信息

# [USACO09OPEN] Grazing2 S

## 题目描述

Farmer John has N (2 <= N <= 1,500) prize milk cows conveniently numbered 1..N. His newly-painted barn has S (N <= S <= 1,000,000) stalls (conveniently numbered 1..S) in a single long line; each stall is a unit distance from its neighboring stall(s).

The cows have made their way to the stalls for a rest; cow i is in stall P\_i. Antisocial as they are, the cows get grumpy if they are situated in stalls very close to each other, so Farmer John wants to move the cows to be as spread out as possible.

FJ wants to make sure that the N - 1 distances between adjacent cows are as large as possible, and he would also like them to be similar to each other (i.e., close to equi-distant spacing).

In particular, FJ would like all distances between adjacent cows to be at most 1 different from (S - 1) / (N - 1), where integer division is used. Moreover, he would like as many of these distances as possible to be exactly equal to (S - 1) / (N - 1) [integer

division]. Thus, with four cows and eight stalls, one can place the cows at positions 1, 3, 5, 8 or 1, 3, 6, 8 but not at 1, 2, 4, 7 or 1, 2, 4, 8.

Help FJ spread the cows as efficiently as possible by calculating and reporting the minimum total distance that the cows have to move in order to achieve proper spacing. Ignore the distance it takes for a cow to enter or exit a stall.

约翰有N(2≤N≤1500)头奶牛，S(N≤S≤1,000,000)个一字排开的牛棚．相邻牛棚间的距离恰好为1．

奶牛们已经回棚休息，第i只奶牛现在待在牛棚Pi．如果两只奶牛离得太近，会让奶牛们变得很暴躁．所以约翰想给一些奶牛换一个棚，让她们之间的距离变得尽量大，并且尽管接近．令d=Trunc((s-1)/(n-1))

所以约翰希望最终的奶牛的状态是：两只相邻奶牛间的距离与d之差不超过1，而且让尽量多的间距等于d．因此，对于4只奶牛8个棚的情况，1，3，5，8或1，3，6，8这样的安置情况是允许的，而1，2，4，7或1，2，4，8这样的情况是不允许的．    帮助约翰移动奶牛，让所有奶牛的移动距离之和最小，同时让最终的安置情况符合约翰心意．


## 说明/提示

1   2   3   4   5   6   7   8   9  10

Cow Locs     | A | B | C | . | . | . | . | D | E | . | 

Cows move from stall 2 to 3, 3 to 5, and 9 to 10. The total distance moved is 1 + 2 + 1 = 4. The final positions of the cows are in stalls 1, 3, 5, 8, and 10.

1   2   3   4   5   6   7   8   9  10

Init Stall     | A | B | C | . | . | . | . | D | E | . | 
Final Stall    | A | . | B | . | C | . | . | D | . | E | 
Distance moved | 0 | . | 1 | . | 2 | . | . | 0 | . | 1 | 

## 样例 #1

### 输入

```
5 10 
2 
8 
1 
3 
9 
```

### 输出

```
4 
```

# AI分析结果

### 综合分析与结论

本题的核心是通过动态规划（DP）来最小化奶牛的移动距离，同时满足相邻奶牛间距为 `d` 或 `d+1` 的条件。所有题解都采用了类似的DP思路，但在状态定义、转移方程、边界条件和优化细节上有所不同。整体来看，题解的质量参差不齐，部分题解在思路清晰度和代码可读性上表现较好，但大多数题解在优化和细节处理上仍有提升空间。

### 所选高星题解

#### 1. 题解作者：Rainbow_qwq (4星)
- **关键亮点**：
  - 状态定义清晰：`f[i][j]` 表示前 `i` 头牛，`j` 个间隔为 `d+1` 的最小移动距离。
  - 转移方程简洁：`f[i][j] = min(f[i-1][j], f[i-1][j-1]) + abs(a[i] - (d*(i-1)+j))`。
  - 边界条件明确：`f[1][1] = a[1] - 1`。
  - 代码结构清晰，易于理解。
- **个人心得**：
  - 通过手推数据，发现相邻奶牛间距只能是 `d` 或 `d+1`，这一观察是解题的关键。
- **核心代码**：
  ```cpp
  For(i,2,n)
      For(j,1,min(c2,i))
          f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-(d*(i-1)+j));
  ```

#### 2. 题解作者：Elegy_of_Green_Kite (4星)
- **关键亮点**：
  - 状态定义与转移方程与Rainbow_qwq类似，但增加了对间距选择的详细解释。
  - 强调了初始排序的重要性，并提供了详细的初始化步骤。
  - 代码结构清晰，注释详细。
- **个人心得**：
  - 通过观察发现所有奶牛间距只能是 `d` 或 `d+1`，这一结论是解题的基础。
- **核心代码**：
  ```cpp
  for(int i=2;i<=n;i++)
      for(int j=0;j<=min(i-1,s-1-d*(n-1));j++)
          f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-1-((i-1)*d+j));
  ```

#### 3. 题解作者：shadowice1984 (3.5星)
- **关键亮点**：
  - 使用了滚动数组优化，节省了空间复杂度。
  - 通过枚举误差范围，进一步优化了DP的转移过程。
  - 代码简洁，但缺乏详细解释。
- **个人心得**：
  - 通过滚动数组优化，减少了内存使用，但在实现时需要注意循环顺序。
- **核心代码**：
  ```cpp
  for(int i=1;i<n;i++)
      for(int j=min(i,m-(n-1)*d);j>=1;j--)
          dp[j]=min(dp[j],dp[j-1])+abso(dis[i]-i*d-j);
  ```

### 最优关键思路与技巧

1. **状态定义**：`f[i][j]` 表示前 `i` 头牛，`j` 个间隔为 `d+1` 的最小移动距离。
2. **转移方程**：`f[i][j] = min(f[i-1][j], f[i-1][j-1]) + abs(a[i] - (d*(i-1)+j))`。
3. **边界条件**：`f[1][1] = a[1] - 1`。
4. **优化技巧**：使用滚动数组优化空间复杂度，减少内存使用。

### 可拓展之处

- **类似算法套路**：本题的DP思路可以推广到其他需要最小化移动距离或最大化间距的问题，如任务调度、资源分配等。
- **同类型题目**：
  - [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
  - [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
  - [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得总结

- **调试经历**：在实现DP时，边界条件和转移方程的细节处理非常重要，稍有不慎就会导致错误。
- **踩坑教训**：在优化空间复杂度时，滚动数组的实现需要注意循环顺序，否则会导致状态更新错误。
- **顿悟感想**：通过手推数据，发现相邻奶牛间距只能是 `d` 或 `d+1`，这一观察是解题的关键。

---
处理用时：32.42秒