# 题目信息

# AlgoRace

## 题目描述

有 $n$ 个城市，两两之间有直接连边，还有 $m$ 辆车。

已知每辆车经过边 $(i,j)$ 所需要的时间，即 $w_{i,j}$。你可以在到达一个城市之后选择换车，换车视为瞬间完成。对于每组询问 $(s,t,k)$，求从 $s$ 到 $t$ 的最短时间，其中换车总次数不超过 $k$，即全程使用的车次不超过 $k + 1$。注意：**同一辆车可以重复使用**。

询问共有 $r$ 组数据。

## 说明/提示

$n,m\le 60$

$w_{i,j}\le 10^6 $

$r\le 10^5$

$1\le s,t\le n,k\le 1000$

感谢 @frankchenfu、@yuhaocheng 提供的翻译

## 样例 #1

### 输入

```
4 2 3
0 1 5 6
2 0 3 6
1 3 0 1
6 6 7 0
0 3 5 6
2 0 1 6
1 3 0 2
6 6 7 0
1 4 2
1 4 1
1 4 3
```

### 输出

```
3
4
3
```

## 样例 #2

### 输入

```
4 2 3
0 7 3 3
8 0 10 5
1 1 0 4
8 9 2 0
0 3 3 9
7 0 4 9
3 8 0 4
4 8 9 0
2 3 3
2 1 3
1 2 2
```

### 输出

```
4
5
3
```

# AI分析结果

### 题目内容
# AlgoRace

## 题目描述
有 $n$ 个城市，两两之间有直接连边，还有 $m$ 辆车。
已知每辆车经过边 $(i,j)$ 所需要的时间，即 $w_{i,j}$ 。你可以在到达一个城市之后选择换车，换车视为瞬间完成。对于每组询问 $(s,t,k)$ ，求从 $s$ 到 $t$ 的最短时间，其中换车总次数不超过 $k$ ，即全程使用的车次不超过 $k + 1$ 。注意：**同一辆车可以重复使用**。
询问共有 $r$ 组数据。

## 说明/提示
$n,m\le 60$
$w_{i,j}\le 10^6 $
$r\le 10^5$
$1\le s,t\le n,k\le 1000$
感谢 @frankchenfu、@yuhaocheng 提供的翻译

## 样例 #1
### 输入
```
4 2 3
0 1 5 6
2 0 3 6
1 3 0 1
6 6 7 0
0 3 5 6
2 0 1 6
1 3 0 2
6 6 7 0
1 4 2
1 4 1
1 4 3
```
### 输出
```
3
4
3
```

## 样例 #2
### 输入
```
4 2 3
0 7 3 3
8 0 10 5
1 1 0 4
8 9 2 0
0 3 3 9
7 0 4 9
3 8 0 4
4 8 9 0
2 3 3
2 1 3
1 2 2
```
### 输出
```
4
5
3
```

### 算法分类
动态规划

### 题解综合分析与结论
这两篇题解思路相近，均采用动态规划解决问题，核心都是利用类似Floyd的方式进行状态转移。
- **思路**：都通过设定状态来表示从一个城市到另一个城市在不同换车次数限制下的最短时间，然后基于换车次数进行状态转移。
- **算法要点**：先对每辆车单独进行Floyd算法处理，得到不换车情况下的最短路径。之后通过枚举换车次数、起点、终点和中转点来更新动态规划数组。
- **解决难点**：难点在于如何结合换车次数这一维度进行状态转移。两篇题解都通过在转移方程中体现换车次数的变化来解决，即通过前一次换车次数的状态推出当前换车次数的状态。

### 所选的题解
#### 作者：傅思维666 (5星)
- **关键亮点**：思路清晰，代码简洁明了，直接按题意设状态，转移方程的推导自然合理，对数据范围的处理得当，直接利用题目中城市数量限制对换车次数进行优化。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxq=1e5+5;
int n,m,r,maxx;
int dp[62][62][62];
//dp[i][j][k]表示i->j换k次车的最小时间
int a[62][62][62];
//a[k][i][j]表示i->j的原始时间
int q[maxq][3];
int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for(int k=1;k<=m;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&a[k][i][j]);
    for(int i=1;i<=r;i++)
    {
        scanf("%d%d%d",&q[i][0],&q[i][1],&q[i][2]);
        maxx=max(maxx,q[i][2]);
    }
    maxx=min(maxx,n);
    for(int op=1;op<=m;op++)
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    a[op][i][j]=min(a[op][i][j],a[op][i][k]+a[op][k][j]);
    memset(dp,127,sizeof(dp));
    for(int op=1;op<=m;op++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dp[i][j][0]=min(dp[i][j][0],a[op][i][j]);
    for(int k=1;k<=maxx+1;k++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dp[i][j][k]=dp[i][j][k-1];
        for(int l=1;l<=n;l++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    dp[i][j][k]=min(dp[i][j][k],dp[i][l][k-1]+dp[l][j][0]);
    }
    for(int i=1;i<=r;i++)
    {
        q[i][2]=min(q[i][2],maxx);
        printf("%d\n",dp[q[i][0]][q[i][1]][q[i][2]]);
    }
    return 0;
}
```
核心代码实现思想：首先读入每辆车经过各边的时间，对每辆车单独进行Floyd算法更新距离。初始化不换车情况下的最短时间，之后通过三层循环，根据换车次数进行状态转移，最后根据询问输出结果。

#### 作者：frankchenfu (4星)
- **关键亮点**：详细阐述了状态和转移方程的含义，对时间复杂度分析清晰，并指出可利用城市数量对换车次数上限进行优化。
```cpp
#include<cstdio>
#include<cstring>
#include<assert.h>
#define NDEBUG
const int MAXN=65,MAXK=1010;
const int MAXQ=100010;
int n,m,r,max_k=1<<31;
int f[MAXN][MAXN][MAXK],g[MAXN][MAXN][MAXN];
int q[MAXQ][3];
//f_{i,j,k}=(i,j)换k次车. g_{k,i,j}=(i,j)用第k种车直接跑.

inline int max(int x,int y){
    return x>y?x:y;
}
inline int min(int x,int y){
    return x<y?x:y;
}
int main(){
//	freopen("test.in","r",stdin);
    scanf("%d%d%d",&n,&m,&r);
    for(int k=1;k<=m;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&g[k][i][j]);
    for(int i=1;i<=r;i++){
        scanf("%d%d%d",&q[i][0],&q[i][1],&q[i][2]);
        max_k=max(max_k,q[i][2]);
    }
    max_k=min(max_k,n);
                
    //floyd O(m* n^3)=O(n^4)=1.296e+7;
    for(int p=1;p<=m;p++)
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    g[p][i][j]=min(g[p][i][j],g[p][i][k]+g[p][k][j]);
                
    for(int i=1;i<=n;i++)
   		for(int j=1;j<=n;j++)
   			f[i][j][0]=~(1<<31);
    for(int k=1;k<=m;k++)//初值：不换车，从头跑到尾.
       	for(int i=1;i<=n;i++)
       		for(int j=1;j<=n;j++)
                f[i][j][0]=min(f[i][j][0],g[k][i][j]);
                
    for(int p=1;p<=max_k+1;p++){
        for(int i=1;i<=n;i++)
        	for(int j=1;j<=n;j++)
                f[i][j][p]=f[i][j][p-1];
        for(int k=1;k<=n;k++)
        	for(int i=1;i<=n;i++)
        		for(int j=1;j<=n;j++)
        			f[i][j][p]=min(f[i][j][p],f[i][k][p-1]+f[k][j][0]);
    }
       
    for(int i=1;i<=r;i++){
        q[i][2]=min(q[i][2],max_k);
        printf("%d\n",f[q[i][0]][q[i][1]][q[i][2]]);
    }
    return 0;
}
```
核心代码实现思想：读入每辆车在各边行驶时间，对每辆车做Floyd算法。初始化不换车时的最短时间，通过循环根据换车次数更新动态规划数组，根据询问输出结果。

### 最优关键思路或技巧
利用动态规划，将问题状态设为从一个城市到另一个城市在不同换车次数限制下的最短时间，通过枚举中转点和换车次数进行状态转移。同时利用城市数量的限制优化换车次数上限，从而降低时间复杂度。

### 同类型题或类似算法套路拓展
此类题目属于带限制条件的最短路问题，一般思路是在传统最短路算法（如Floyd、Dijkstra等）基础上，增加限制条件的维度，通过动态规划进行状态转移。常见的限制条件除了换车次数，还可能有费用限制、路径长度限制等。

### 洛谷相似题目推荐
- [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)：状态压缩动态规划，与本题类似，需考虑多种限制条件进行状态转移。
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：简单的动态规划，通过状态转移方程求解问题，可锻炼动态规划思维。
- [P3211 [HNOI2011] 防线修建](https://www.luogu.com.cn/problem/P3211)：结合了动态规划与数据结构优化，与本题优化思路类似，通过合理利用条件降低时间复杂度。 

---
处理用时：99.61秒