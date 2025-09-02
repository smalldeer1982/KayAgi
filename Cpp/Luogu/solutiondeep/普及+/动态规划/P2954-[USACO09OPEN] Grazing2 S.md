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
该题核心思路为通过动态规划处理最优间隔分配问题。所有题解均采用以下关键步骤：
1. 排序初始牛的位置，确定基准间距d和d+1间隔数c2。
2. 使用二维DP状态f[i][j]表示前i头牛中j个间隔为d+1时的最小移动距离。
3. 通过状态转移方程结合当前位置计算进行优化。

### 高星题解推荐（4星及以上）

#### 1. 作者：Rainbow_qwq（4星）
**关键亮点**：
- 清晰的数学推导，明确列出方程组解c2
- 详细注释代码结构，便于理解状态转移逻辑
- 完整展示边界条件处理（f[1][1]初始化）

**核心代码思想**：
```cpp
sort(a+1,a+n+1);
f[1][1] = a[1]-1; // 边界：第一头牛移动到1号棚
for(int i=2;i<=n;i++)
    for(int j=1;j<=min(c2,i);j++)
        f[i][j] = min(f[i-1][j], f[i-1][j-1]) 
                + abs(a[i] - (d*(i-1)+j));
```

#### 2. 作者：shadowice1984（4星）
**关键亮点**：
- 引入滚动数组优化空间复杂度至O(n)
- 处理坐标偏移简化计算（所有位置减1）
- 逆序更新避免状态覆盖问题

**核心代码技巧**：
```cpp
for(int i=1;i<n;i++) { // 滚动数组更新
    for(int j=min(i,m-(n-1)*d); j>=1; j--) { // 逆序是关键
        dp[j] = min(dp[j], dp[j-1]) 
              + abs(dis[i] - (i*d + j));
    }
    dp[0] += abs(dis[i] - i*d); // 单独处理j=0情况
}
```

### 关键思路与技巧总结
1. **数学建模**：通过解方程确定d+1间隔数c2 = s-1 - d*(n-1)
2. **状态压缩**：利用滚动数组将空间复杂度从O(n²)优化到O(n)
3. **坐标计算**：第i头牛的理论位置为d*(i-1)+j，其中j为已使用的d+1间隔数
4. **逆序更新**：在滚动数组实现中必须倒序处理j以避免状态覆盖

### 类似题目推荐
1. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 双向LIS模型
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020) - 贪心+DP优化
3. [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944) - 区间DP应用

### 题解心得摘录
**staygone**调试经验：
> "滚动数组需要逆序处理j，否则会覆盖前面的状态。实现时因正序更新WA多次，最终发现必须倒序扫描。"

**shadowice1984**提醒：
> "题目坐标描述含混，将整体位置减1后更易处理，最终输出时需注意还原偏移量。"

---
处理用时：43.77秒