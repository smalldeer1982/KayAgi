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
这些题解均采用动态规划（DP）算法解决奶牛移动问题。核心思路是先对奶牛初始位置排序，确定相邻奶牛间距为 \(d\) 或 \(d + 1\)（\(d=(s - 1)/(n - 1)\)），并计算出间距为 \(d + 1\) 的数量。通过定义状态 \(f[i][j]\) 表示前 \(i\) 头牛有 \(j\) 个间距为 \(d + 1\) 时的最小移动距离，利用状态转移方程 \(f[i][j]=\min(f[i - 1][j], f[i - 1][j - 1])+\vert a[i]-(d\times(i - 1)+j)\vert\) 进行状态转移，最终答案为 \(f[n][c_2]\)（\(c_2\) 为间距为 \(d + 1\) 的数量）。部分题解还使用了滚动数组优化空间复杂度。

### 所选题解
- **作者：Rainbow_qwq（5星）**
  - 关键亮点：思路清晰，详细推导了间距为 \(d + 1\) 的数量，代码注释详细，可读性高。
  - 核心代码：
```cpp
For(i,2,n)//dp
    For(j,1,min(c2,i))
        f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-(d*(i-1)+j));
```
- **作者：Elegy_of_Green_Kite（4星）**
  - 关键亮点：对结论的推导过程解释详细，适合初学者理解。
  - 核心代码：
```cpp
for(int i=2;i<=n;i++)
    for(int j=0;j<=min(i-1,s-1-d*(n-1));j++)
        f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-1-((i-1)*d+j));
```
- **作者：wei2013（4星）**
  - 关键亮点：状态定义和转移方程解释清晰，代码简洁。
  - 核心代码：
```cpp
for(int i=2;i<=n;i++){
    for(int j=1;j<=min(y,i);j++){
        dp[i][j]=min(dp[i-1][j],dp[i-1][j-1])+abs((d*(i-1)+j)-a[i]);
    }
}
```

### 最优关键思路或技巧
- **思维方式**：通过分析题目条件，确定相邻奶牛间距的可能情况，将问题转化为动态规划问题。
- **算法优化**：使用滚动数组可以将空间复杂度从 \(O(n^2)\) 优化到 \(O(n)\)。

### 可拓展之处
同类型题或类似算法套路：此类问题属于区间划分的动态规划问题，关键在于确定状态定义和状态转移方程。可以拓展到其他需要对元素进行排列并满足一定间距条件的问题，如货物摆放、座位安排等。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：基础的 0 - 1 背包问题，考察动态规划的基本思想。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划入门题，通过状态转移求解最优路径。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，进一步加深对动态规划的理解。

### 个人心得摘录与总结
- **作者：shadowice1984**：提到审题坑爹，一开始扫反了导致 WA 了一次，强调了审题和正确遍历顺序的重要性。
- **作者：staygone**：发现原做法可能会 RE，思考并尝试用滚动数组优化空间，体现了对代码优化的探索精神。 

---
处理用时：27.03秒