# 题目信息

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 瓷器

## 题目描述
在公主发脾气的时候，她通常会打碎一些收藏的瓷器。每次愤怒的尖叫都会伴随着打碎一件物品。

瓷器收藏品整齐地摆放在 $n$ 个架子上。在每个架子上，物品排成一排，所以人们只能拿到最外面的物品——最左边或最右边的物品，而不是架子中间的物品。一旦拿走一件物品，就可以拿到该架子同一侧的下一件物品（见示例）。一旦拿走一件物品，就不能再放回架子上。

给定所有物品的价值。你的任务是找出公主发 $m$ 次脾气时，对瓷器收藏品造成的最大破坏值。

## 说明/提示
在第一个例子中，有两个架子，每个架子有三个物品。为了使所选物品的总价值最大化，可以从第一个架子的左边拿走两个物品，从第二个架子的右边拿走一个物品。

在第二个例子中，只有一个架子，所以从这个架子上拿走三个物品——从左边拿走两个，从右边拿走一个。

## 样例 #1
### 输入
```
2 3
3 3 7 2
3 4 1 5
```
### 输出
```
15
```

## 样例 #2
### 输入
```
1 3
4 4 3 1 2
```
### 输出
```
9
```

### 综合分析与结论
这些题解的核心思路都是通过动态规划解决问题，将问题分为两个子问题：首先计算每一层取不同数量物品的最大价值，然后基于这些结果计算前 $n$ 层取 $m$ 个物品的最大价值。
1. **思路**：大多题解先处理出每层取若干物品的最大价值，再通过类似分组背包的方式，结合前 $n - 1$ 层取物品的情况，得到前 $n$ 层取 $m$ 个物品的最大价值。不同点在于状态定义和转移方程的具体写法，部分题解在状态转移时对边界条件的处理方式略有不同。
2. **算法要点**：利用前缀和优化计算每层取物品价值的过程，通过三重循环分别枚举层数、总取物品数以及当前层取物品数来完成状态转移。
3. **解决难点**：难点在于如何准确地定义状态和状态转移方程，确保在计算每层取物品价值时能考虑到所有从左或从右取的组合情况，同时在多层计算时避免重复选择物品。

### 所选的题解
1. **作者：wanggiaoxing (5星)**
    - **关键亮点**：思路清晰，状态定义简洁明了，代码实现紧凑，对分组背包的应用和状态转移方程的推导详细且准确。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[101][10001],dp1[101][101],n,m,v[101],sum[101][101],q[101];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int k;
        cin>>k;
        for(int j=1;j<=k;j++)
            cin>>v[j],sum[i][j]=sum[i][j-1]+v[j];
        for(int j=1;j<=k;j++)
            for(int l=0;l<=j;l++)
            {
                int r=k-(j-l);
                dp1[i][j]=max(dp1[i][j],sum[i][l]+sum[i][k]-(r==0?0:sum[i][r]));//边界处理
            }
        q[i]=k;
    }
    for(int i=1;i<=n;i++)
        for(int k=0;k<=m;k++)
            for(int j=0;j<=q[i];j++)
                if(k>=j)
                    dp[i][k]=max(dp[i][k],dp[i-1][k-j]+dp1[i][j]);//分组背包
    cout<<dp[n][m];
}
```
核心实现思想：先通过前缀和数组 `sum` 预处理每层数据，再利用两层循环枚举每层取物品数和左右取物品的分割点，计算出每层取不同数量物品的最大价值 `dp1`。最后通过三层循环，利用分组背包的思想，计算出前 $n$ 层取 $m$ 个物品的最大价值 `dp`。
2. **作者：SSHhh (4星)**
    - **关键亮点**：对思路的阐述详细，从题意分析到状态转移方程的推导逐步展开，代码中使用 `vector` 存储每层物品，使代码更具灵活性，对边界条件和状态转移的处理清晰。
    - **核心代码**：
```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,m,N,ans,dp1[105][105],sum[105][105]/*每一层的前缀和*/,dp2[105][10005];
vector<int> a[105];
int cal(int k,int i,int j) //第 k 层取了前 i 个和后 j 个的总价值
{
    int N=a[k].size();
    return sum[k][N]-sum[k][N-j]+sum[k][i];
}
int main()
{
    int N,x;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>N;
        for(int k=1;k<=N;k++)
            cin>>x,a[i].push_back(x),sum[i][k]=sum[i][k-1]+x;//因为每一层长度不定，用一个vector保存，同时计算前缀和
    }
    for(int k=1;k<=n;k++)
        for(int l=1;l<=a[k].size();l++)
            for(int i=0;i<=l;i++) {int j=l-i;dp1[k][l]=max(dp1[k][l],cal(k,i,j));}//dp1转移
    for(int k=1;k<=n;k++)
        for(int i=0;i<=m;i++)
            for(int j=0;j<=a[k].size() && j<=i;j++)
                dp2[k][i]=max(dp2[k][i],dp2[k-1][i-j]+dp1[k][j]);//dp2转移
    cout<<dp2[n][m];
    return 0;
}
```
核心实现思想：通过 `vector` `a` 存储每层物品，利用 `sum` 数组计算前缀和。`cal` 函数用于计算每层取特定数量左右物品的价值。通过三层循环分别枚举层数、每层取物品数以及左右取物品的数量，计算出每层取不同数量物品的最大价值 `dp1`。最后同样通过三层循环，利用分组背包思想计算出前 $n$ 层取 $m$ 个物品的最大价值 `dp2`。
3. **作者：activeO (4星)**
    - **关键亮点**：对题目大意的提炼准确，状态定义清晰，转移方程书写简洁明了，整体代码结构清晰，对动态规划的实现过程展示得较为完整。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>//祝大家学习愉快

using namespace std;

const int maxn=110;
int v[maxn],a[maxn][maxn],sum[maxn][maxn*maxn];
int dp[maxn][maxn*maxn],f[maxn][maxn*maxn];

int main(){

    int n,m;

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++){
        scanf("%d",&v[i]);//第 i 行的个数
        for(int j=1;j<=v[i];j++){
            scanf("%d",&a[i][j]);
            sum[i][j]=sum[i][j-1]+a[i][j];//前缀和
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=v[i];j++){
            for(int k=0;k<=j;k++) f[i][j]=max(f[i][j],sum[i][k]+sum[i][v[i]]-sum[i][v[i]-j+k]);//转移1
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<=min(j,v[i]);k++) dp[i][j]=max(dp[i][j],dp[i-1][j-k]+f[i][k]);//转移2
        }
    }

    printf("%d\n",dp[n][m]);

    return 0;
}
```
核心实现思想：利用 `sum` 数组计算前缀和，通过三层循环分别枚举层数、每层取物品数以及左右取物品的分割点，计算出每层取不同数量物品的最大价值 `f`。最后再通过三层循环，基于分组背包思想，计算出前 $n$ 层取 $m$ 个物品的最大价值 `dp`。

### 最优关键思路或技巧
1. **状态定义与转移**：准确地定义状态，将问题划分为计算每层取物品的最大价值和多层综合取物品的最大价值两个子问题，并通过合理的状态转移方程进行求解。
2. **前缀和优化**：利用前缀和数组快速计算从左或从右取若干物品的价值总和，减少计算量。

### 可拓展之处
此类题目属于动态规划中的分组背包类型，相似的题目套路通常是将问题分解为多个子问题，先解决每个子问题（如本题中每层的情况），再综合子问题的解得到最终答案。类似算法套路还可应用于有依赖的背包问题等。

### 相似知识点洛谷题目
1. **P1757 通天之分组背包**：同样是分组背包问题，通过合理规划每组物品的选择来求最大价值。
2. **P2014 [CTSC1997]选课**：有依赖的背包问题，与本题将问题分层解决思路类似，需要处理好不同层之间的依赖关系。
3. **P1060 开心的金明**：基础的背包问题，可作为理解背包问题概念和状态转移的入门练习，与本题在动态规划思想上有相通之处。

### 个人心得摘录与总结
作者 _Album_ 提到在转移时要按照顺序转移，不要随意改变转移顺序，否则可能导致结果错误。这强调了动态规划中状态转移顺序的重要性，在实际解题时需要严格按照状态转移方程的逻辑顺序进行计算，以确保每个状态能正确地从前序状态推导得出。 

---
处理用时：50.71秒