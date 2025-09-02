# 题目信息

# 贪婪的Copy

## 题目描述

Copy 从卢牛那里听说在一片叫 yz 的神的领域埋藏着不少宝藏，于是 Copy 来到了这个被划分为 $n$ 个区域的神地。卢牛告诉了Copy这里共有 $n$ 个宝藏，分别放在第 $P_i$ 个 $(1\le P_i\le N)$ 区域。Copy还得知了每个区域之间的距离。现在 Copy 从 $1$ 号区域出发，要获得所有的宝藏并到 $n$ 号区域离开。Copy 很懒，只好来找你为他寻找一条合适的线路，使得他走过的距离最短。


## 说明/提示

- 对 $30\%$ 的数据，$1\le n\le 15$，其余如题所述。
- 对 $100\%$ 的数据，全部数据范围如题所述。


## 样例 #1

### 输入

```
2
0 4
5 0
2
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
0 2 6
1 0 4
7 10 0
1
2
```

### 输出

```
6
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何求出从1号区域出发获取所有宝藏并到达n号区域的最短路径。大多题解先用Floyd算法预处理出各点间最短距离，再通过不同方式枚举经过宝藏点的顺序。
1. **算法要点**：
    - **Floyd算法**：用于在$O(n^3)$时间内求出任意两点间最短距离，适用于本题$1\leq n\leq100$的数据范围。
    - **枚举方式**：有使用全排列枚举（如`next_permutation`函数、DFS枚举所有可能路径）、状压DP枚举带宝藏区域的状态。
2. **解决难点**：难点在于如何高效地找到经过所有宝藏点的最短路径。由于宝藏点数量相对较少（$1\leq p\leq10$），可通过不同枚举方式实现，但需考虑时间复杂度。

### 所选题解
#### 作者：The_Key (4星)
- **关键亮点**：思路清晰，代码简洁。使用`next_permutation`函数进行全排列枚举，方便快捷，代码可读性强。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,sum,ans=0x7fffffff,po[12],mp[105][105];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    cin>>mp[i][j];
    cin>>m;
    for(int i=1;i<=m;i++)
    cin>>po[i];
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
    sort(po+1,po+m+1);
    do
    {
        sum=0;
        sum+=mp[1][po[1]]+mp[po[m]][n];
        for(int i=1;i<m;i++)
        sum+=mp[po[i]][po[i+1]];
        ans=min(ans,sum);
    }while(next_permutation(po+1,po+m+1));
    cout<<ans;
    return 0;
}
```
核心实现思想：先通过Floyd算法预处理距离矩阵，对宝藏位置数组排序后，利用`next_permutation`生成所有排列，计算每种排列下的路径长度并更新最短路径。

#### 作者：DDOSvoid (4星)
- **关键亮点**：将问题看作TSP变形，利用状压DP优化枚举，时间复杂度$O(2^p * p^2)$，对于$p$较小的情况效率较高。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxm 11
#define maxn 101
#define INF 1000000000
using namespace std;
int f[1<<maxm][maxn];
int map[maxn][maxn],a[maxm];
int n,m;
int main(){
    memset(f,10,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&map[i][j]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(k!=i && k!=j && i!=j)
                    map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
    int M=(1<<m)-1;
    for(int i=1;i<=m;i++)f[1<<i-1][a[i]]=map[1][a[i]];
    for(int i=1;i<=M;i++)
        for(int j=1;j<=m;j++)
            if(i&(1<<j-1))
                for(int k=1;k<=m;k++)
                    if(!(i&(1<<k-1)))
                        f[i|(1<<k-1)][a[k]]=min(f[i|(1<<k-1)][a[k]],f[i][a[j]]+map[a[j]][a[k]]);
    int ans=INF;
    for(int i=1;i<=m;i++)
        ans=min(ans,f[M][a[i]]+map[a[i]][n]);
    cout<<ans;
    return 0;
}
```
核心实现思想：用Floyd预处理距离，通过状压DP记录已访问宝藏区域状态，状态转移方程为`f[i|(1<<k - 1)][a[k]] = min(f[i|(1<<k - 1)][a[k]], f[i][a[j]] + map[a[j]][a[k]])`，最后计算到n号区域的最短路径。

### 最优关键思路或技巧
1. **Floyd预处理**：利用Floyd算法能在$O(n^3)$时间内求出任意两点间最短距离，为后续计算路径长度提供基础。
2. **枚举优化**：状压DP利用二进制状态压缩，减少枚举量，在$p$较小时时间复杂度优于全排列枚举，是一种高效的优化方式。

### 可拓展思路
同类型题常涉及带限制条件的最短路径问题，可通过预处理距离，结合不同枚举方式求解。类似算法套路如在满足特定条件下的路径搜索，可考虑使用Floyd、Dijkstra等算法预处理距离，再用枚举、DP等方法解决限制条件。

### 推荐洛谷题目
1. **P1144 最短路计数**：涉及最短路及路径数量统计，考察对最短路算法的理解与应用。
2. **P3371 【模板】单源最短路径（弱化版）**：单源最短路径模板题，可巩固Dijkstra等最短路算法。
3. **P1739 表达式括号匹配**：虽非直接最短路问题，但可锻炼对栈、状态处理等技巧，与状压DP有相通之处。

### 个人心得摘录与总结
1. **作者：king_xbz**：提醒在函数中避免使用`++y`之类操作，因为可能导致错误，应使用`y + 1`，强调了代码细节对正确性的影响。 

---
处理用时：26.41秒