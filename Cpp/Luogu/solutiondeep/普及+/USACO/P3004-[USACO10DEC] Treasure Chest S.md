# 题目信息

# [USACO10DEC] Treasure Chest S

## 题目描述

Bessie and Bonnie have found a treasure chest full of marvelous gold coins! Being cows, though, they can't just walk into a store and buy stuff, so instead they decide to have some fun with the coins.

The N (1 <= N <= 5,000) coins, each with some value C\_i (1 <= C\_i <= 5,000) are placed in a straight line. Bessie and Bonnie take turns, and for each cow's turn, she takes exactly one coin off of either the left end or the right end of the line. The game ends when there are no coins left.

Bessie and Bonnie are each trying to get as much wealth as possible for themselves. Bessie goes first. Help her figure out the maximum value she can win, assuming that both cows play optimally.

Consider a game in which four coins are lined up with these values:

30  25  10  35

Consider this game sequence:

Bessie    Bonnie       New Coin

Player   Side   CoinValue   Total     Total         Line

Bessie   Right     35        35         0       30  25  10

Bonnie   Left      30        35        30         25  10

Bessie   Left      25        60        30           10

Bonnie   Right     10        60        40           --

This is the best game Bessie can play.

小 A 和小 B 在玩游戏。

初始时，有 $n$ 个硬币被摆成了一行，从左至右数第 $i$ 个硬币的价值为 $c_i$。

小 A 和小 B 每人一回合，在一个人的回合中，他可以选择**当前**硬币序列最左侧或者最右侧的硬币，并将他从序列中取出，将其价值累加到自己获得的累计价值中，然后进行另一个人的回合。当硬币全部被取走时，游戏结束。

请求出在双方都尽可能的使自己累计价值最大的情况下，若由小 A 进行第一回合，那么他能获得的累计价值最大是多少。

## 说明/提示

#### 输入输出样例 $1$ 解释

初始时，硬币序列为 $\{30,~25,~10,~35\}$。

第一回合，小 A 取走最右侧的硬币，序列变为 $\{30,~25,~10\}$，小 A 的累加价值为 $35$。

第二回合，小 B 取走最左侧的硬币，序列变为 $\{25,~10\}$，小 B 的累加价值为 $30$。

第三回合，小 A 取走最左侧的硬币，序列变为 $\{10\}$，小 A 的累加价值为 $35 + 25 = 60$。

第四回合，小 B 取走最左侧的硬币，序列变为空，小 B 的累加价值为 $30 + 10 = 40$，游戏结束。

小 A 获得的最大累计价值为 $60$。

#### 数据范围与约定

对于全部的测试点，$1 \leq n \leq 5 \times 10^3$，$1 \leq c_i \leq 5 \times 10^3$。

**提示：请注意，本题的空间限制为 $64$ Mib。**

## 样例 #1

### 输入

```
4 
30 
25 
10 
35 
```

### 输出

```
60 
```

# AI分析结果

### 综合分析与结论
本题是一个博弈类型的区间动态规划问题，核心是在双方都采取最优策略的情况下，计算先手能获得的最大价值。各题解的思路大多围绕区间DP展开，状态定义通常为`f[l][r]`表示区间`[l, r]`内先手能获得的最大值，转移方程为`f[l][r] = sum[l][r] - min(f[l + 1][r], f[l][r - 1])`，即区间总和减去对手在剩余区间的最优值。

本题的主要难点在于空间限制，直接使用二维数组会导致MLE。为解决这一问题，多个题解采用了滚动数组、动态内存分配、前缀和优化等方法来压缩空间。此外，还有部分题解尝试使用贪心算法，但正确性有待证明。

### 所选题解
- **作者：逝星DS（5星）**
    - **关键亮点**：思路清晰，详细阐述了二维数组会爆内存的问题，并给出了滚动数组优化的方法，代码简洁易懂。
    - **核心代码**：
```cpp
#include <iostream>
#define maxN 5010
using namespace std;
int N;
int s[maxN];  //前缀和; 
int f[maxN];  //一维滚动数组; 
int main()  {
    cin>>N;
    int v;
    for(int i=1;i<=N;i++)  {
        cin>>v;
        f[i]=v;  //初始化，f[i]一开始即相当于二维中的f[i][i]； 
        s[i]=s[i-1]+v;  //前缀和累加; 
    }
    for(int l=2;l<=N;l++)  {  //l为长度,注意从2开始； 
        for(int i=1;i+l-1<=N;i++)  {  //枚举head; 
            int j=i+l-1;  //计算出tail; 
            f[i]=s[j]-s[i-1]-min(f[i],f[i+1]);
            //‘s[j]-s[i-1]’为i到j区间总价值，
            //f[i]为从i到i+l-2区间最优解（已在上一步算出，f[i+1]同）; 
        }
    }
    cout<<f[1];  //输出即可; 
    return 0;
}
```
    - **核心实现思想**：使用一维滚动数组`f[i]`表示以`i`为起点的区间的最优解，通过枚举区间长度和起点，利用前缀和计算区间总和，不断更新`f[i]`的值。

- **作者：＂黎筱っ（5星）**
    - **关键亮点**：不仅给出了状态转移方程，还详细分析了如何将二维数组压缩为一维数组，通过观察状态转移的特点，使用滚动数组优化空间。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long read(){
    long long x = 0; int f = 0; char c = getchar();
    while(c < '0' || c > '9') f |= c == '-', c = getchar();
    while(c >= '0' && c <= '9') x = (x <<1) + (x << 3) + (c ^ 48), c = getchar();
    return f? -x:x; 
}

int n, a[5005], f[5005];
int main(){
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) f[i] = a[i], a[i] += a[i - 1];
    for(int l = 2; l <= n; ++l)
        for(int i = 1; i + l - 1 <= n; ++i)
            f[i] = a[i + l - 1] - a[i - 1] - min(f[i + 1], f[i]);
    printf("%d\n", f[1]);
    return 0;
}
```
    - **核心实现思想**：同样使用一维滚动数组`f[i]`，通过前缀和计算区间总和，在更新`f[i]`时，利用未修改的`f[i]`表示上一个长度的区间最优解，从而实现空间压缩。

- **作者：kkxhh（4星）**
    - **关键亮点**：先给出了未优化的二维数组代码，便于理解状态转移方程，然后详细说明了如何使用滚动数组优化空间，代码注释清晰。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n,a[5010],sum[5010]={0},d[2][5010]={0},k=0;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(a[i]=d[k][i]=read());
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++)
            d[k^1][l]=sum[l+len-1]-sum[l-1]-min(d[k][l],d[k][l+1]);
        k^=1;
    }
    printf("%d",d[k][1]);
    return 0;
}
```
    - **核心实现思想**：使用二维滚动数组`d[2][5010]`，通过异或运算`k^1`在两个数组间滚动，不断更新当前区间的最优解。

### 最优关键思路或技巧
- **区间DP思想**：将问题转化为区间上的动态规划，通过枚举区间长度和起点，逐步计算出整个区间的最优解。
- **滚动数组优化**：观察状态转移方程，发现当前状态只与上一个状态有关，因此可以使用滚动数组将二维空间压缩为一维或二维滚动数组，减少内存使用。
- **前缀和优化**：使用前缀和数组快速计算区间总和，避免重复计算，提高时间效率。

### 可拓展之处
本题的思路可以拓展到其他博弈类型的区间DP问题，例如在不同规则下的取数游戏、石子合并等问题。关键在于准确定义状态和转移方程，同时注意空间和时间的优化。

### 推荐题目
- [P2734 游戏 A Game](https://www.luogu.com.cn/problem/P2734)：与本题极为相似，都是博弈类型的区间DP问题。
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：经典的区间DP问题，通过合并石子来计算最优解。
- [P3146 [USACO16OPEN]248 G](https://www.luogu.com.cn/problem/P3146)：同样是区间DP问题，需要在区间内进行合并操作以达到目标。

### 个人心得摘录与总结
- **作者：ghj1222**：最初使用二维数组和区间和数组提交代码，出现MLE问题，通过前缀和优化和动态内存分配解决了空间问题。总结是做题要早，及时考虑内存限制。
- **作者：StephenYoung**：最开始尝试简单模拟，只通过了一半测试点，后来改用DP并使用滚动数组优化，成功解决问题。说明简单模拟可能无法解决复杂问题，需要使用更合适的算法。

---
处理用时：47.10秒