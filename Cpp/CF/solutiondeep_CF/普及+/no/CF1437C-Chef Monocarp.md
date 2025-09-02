# 题目信息

# Chef Monocarp

## 题目描述

Chef Monocarp has just put $ n $ dishes into an oven. He knows that the $ i $ -th dish has its optimal cooking time equal to $ t_i $ minutes.

At any positive integer minute $ T $ Monocarp can put no more than one dish out of the oven. If the $ i $ -th dish is put out at some minute $ T $ , then its unpleasant value is $ |T - t_i| $ — the absolute difference between $ T $ and $ t_i $ . Once the dish is out of the oven, it can't go back in.

Monocarp should put all the dishes out of the oven. What is the minimum total unpleasant value Monocarp can obtain?

## 说明/提示

In the first example Monocarp can put out the dishes at minutes $ 3, 1, 5, 4, 6, 2 $ . That way the total unpleasant value will be $ |4 - 3| + |2 - 1| + |4 - 5| + |4 - 4| + |6 - 5| + |2 - 2| = 4 $ .

In the second example Monocarp can put out the dishes at minutes $ 4, 5, 6, 7, 8, 9, 10 $ .

In the third example Monocarp can put out the dish at minute $ 1 $ .

In the fourth example Monocarp can put out the dishes at minutes $ 5, 1, 2, 4, 3 $ .

In the fifth example Monocarp can put out the dishes at minutes $ 1, 3, 4, 5 $ .

## 样例 #1

### 输入

```
6
6
4 2 4 4 5 2
7
7 7 7 7 7 7 7
1
1
5
5 1 2 4 3
4
1 4 4 4
21
21 8 1 4 1 5 21 1 8 21 11 21 11 3 12 8 19 15 9 11 13```

### 输出

```
4
12
0
0
2
21```

# AI分析结果

### 题目翻译
Chef Monocarp刚刚把 $n$ 道菜放进了烤箱。他知道第 $i$ 道菜的最佳烹饪时间为 $t_i$ 分钟。

在任何正整数分钟 $T$，Chef Monocarp最多只能从烤箱中取出一道菜。如果第 $i$ 道菜在某一分钟 $T$ 取出，那么它的不愉快值为 $|T - t_i|$，即 $T$ 和 $t_i$ 之间的绝对差值。一旦菜从烤箱中取出，就不能再放回去。

Chef Monocarp应该把所有的菜都从烤箱中取出来。他能获得的最小总不愉快值是多少？

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕动态规划展开，部分涉及贪心和图论（费用流）的方法。大部分题解先对菜品的最佳取出时间进行排序，然后通过定义不同的状态和状态转移方程来求解最小不美味度。不同题解的时间复杂度有所不同，从 $O(n^3)$ 到 $O(n \log n)$ 不等。

### 所选题解
- **Tony102（4星）**
  - **关键亮点**：思路清晰，先介绍了暴力DP的方法，然后通过贪心优化，对状态转移方程进行了详细的分析，代码实现规范，注释清晰。
  - **核心实现思想**：设 $f[i][j]$ 表示在 $i$ 时刻拿出了前 $j$ 个菜品可以获得的最小不美味度。状态转移时考虑不选和选两种情况，通过排序保证选出的菜品是连续的一段。
  - **核心代码**：
```cpp
const int SIZE = 6e2 + 5;
const int inf = 0x7f7f7f7f;
int T, n;
int a[SIZE], f[SIZE][SIZE];
// ...
T = read();
while (T --) {
    n = read();
    for (int i = 1; i <= n; ++ i) a[i] = read();
    std::sort(a + 1, a + n + 1);
    memset(f, inf, sizeof(f));
    int minn = inf;
    f[0][0] = 0;
    for (int i = 1; i <= 2 * n; ++ i) {
        f[i][0] = 0;
        for (int j = 1; j <= std::min(i, n); ++ j) {
            f[i][j] = std::min(f[i][j], f[i - 1][j]);
            f[i][j] = std::min(f[i - 1][j - 1] + abs(i - a[j]), f[i][j]);
        }
        if (i >= n) minn = std::min(minn, f[i][n]);
    }
    printf("%d\n", minn);
}
```
- **lytqwq（4星）**
  - **关键亮点**：提供了两种思路，其中堆的方法时间复杂度为 $O(n \log n)$，优化程度较高，并且给出了详细的思路解释和代码实现。
  - **核心实现思想**：先对菜品按时间排序，将时间不能重复的问题转化为求不下降序列，通过大根堆来维护，每次看前面的最大值并进行调整。
  - **核心代码**：
```cpp
const int N=1000010;
int n,a[N];
long long int ans;
priority_queue<int>ovo;
// ...
int t;
scanf("%d",&t);
while(t--){
    while(!ovo.empty())ovo.pop();
    ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)ovo.push(0);
    for(int i=1;i<=n;i++){
        a[i]-=i;
        ovo.push(a[i]);
        if(ovo.top()>a[i]){
            ans+=ovo.top()-a[i];
            ovo.pop();ovo.push(a[i]);
        }
    }
    printf("%lld\n",ans);
}
```
- **fisheep（4星）**
  - **关键亮点**：将问题类比为背包问题，通过状态压缩将二维DP优化为一维DP，思路独特，代码简洁。
  - **核心实现思想**：设 $dp[i]$ 表示容量为 $i$ 的时候的最小价值，用背包方程求解 $dp[n]$。
  - **核心代码**：
```cpp
const int inf=0x3f3f3f3f;
const int maxn=207;
int a[maxn],dp[maxn];
// ...
int t=read();
while(t--) {
    int n=read();
    for(int i=1; i<=n; i++) {
        a[i]=read();
    }
    sort(a+1,a+n+1);
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=1; i<=2*n; i++) {
        for(int j=n; j>=0; j--) {
            dp[j]=min(dp[j],dp[j-1]+abs(a[j]-i));
        }
    }
    printf("%lld\n",dp[n]);
}
```

### 最优关键思路或技巧
- **贪心排序**：先对菜品的最佳取出时间进行排序，使得 $t_i$ 小的物品在比较靠前的时间被选中，这样可以保证结果更优。
- **状态压缩**：部分题解通过倒序转移将二维DP优化为一维DP，减少了空间复杂度。
- **堆优化**：使用大根堆来维护时间，将时间不能重复的问题转化为求不下降序列，时间复杂度优化到 $O(n \log n)$。

### 可拓展之处
同类型题可能会有更多的限制条件，如烤箱的容量限制、不同菜品的权重不同等。类似的算法套路包括在动态规划中通过贪心策略优化状态转移，以及使用堆、优先队列等数据结构来优化算法复杂度。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的01背包问题，与本题的动态规划思想类似。
- [P1802 5倍经验日](https://www.luogu.com.cn/problem/P1802)：同样是动态规划问题，通过状态转移方程求解最优解。
- [P4331 [COCI2009-2010#1] ALADIN](https://www.luogu.com.cn/problem/P4331)：与本题有相似之处，可参考相关思路。

### 个人心得摘录与总结
- **E1_de5truct0r**：第一次秒掉 `*1800` 的 dp（几乎想都没想的那种），受之前问的一道题的启发，发现了 $O(n^2)$ 做法，还在考虑怎么优化成 $O(n \log n)$。总结：多做相关题目，从已有题目中获取灵感，不断尝试优化算法。

---
处理用时：48.94秒