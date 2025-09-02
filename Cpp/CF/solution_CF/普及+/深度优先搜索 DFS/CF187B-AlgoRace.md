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

# 题解

## 作者：傅思维666 (赞：1)


## 题解：

一眼DP，看到这个数据范围觉得应该是多维状态。

所以直接按题意设：

$dp[i][j][k]$表示从i到j一共使用的车次不超过k的最短时间

那么可以看出，这个转移和中转点有关系。也就是枚举断点，类似$Floyd$的转移。但是还有这个换车的一维比较难搞。

稍加思索，觉得转移应该是这样的：
$$
dp[i][j][k]=\min(dp[i][l][k-1]+dp[l][j][0])\quad(l\in (1,n))
$$
也就是，先换不超过k-1次车，最后不换车直接到达，因为断点处必然换一次车。

那么初值也就是不换车直达的时间。这个需要开始就做一遍松弛。

然后就看代码吧：

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



---

## 作者：frankchenfu (赞：0)

我们考虑动态规划。

------------


假设我们已经知道了
* $i\to j$只用第$k$部车的最短时间为$g_{i,j,k}$；
* 并且设$f_{i,j,p}$表示$(i,j)$**换$p$次车**的最短时间。

于是我们考虑使用`Floyd`算法，可以得到转移方程：
### $$f_{i,j,p}=\displaystyle\min_{k}^{k\in V}\{f_{i,k,p-1}+f_{k,j,0}\}$$
这是什么意思呢？一般的`Floyd`在进行松弛操作的时候，并不需要考虑这里的$p$，而在这里，我们发现每次松弛操作的时候，都需要“换一次车”。这也就意味着，如果我们要求换$p$次车的最小值，一定是换$p-1$次车之后，再换一次车。而前$p-1$次换车对应的就是$i\to k$，而最后再换一次车$k\to j$。

这样，我们通过$1000$次（询问中$k$的最大值）`Floyd`就可以求出答案了。那么$g_{i,j,k}$怎么求呢？很简单，读入之后做$m$次`Floyd`即可。这样这个算法就结束了，时间复杂度为$O(k_{\max}\cdot n^3)=2.16\times 10^8$，看起来勉强可以通过2000ms的实现，然后最后我`TLE 36`了（加上优化之后仍然`TLE 53`）.所以我们有没有什么好的办法进一步优化呢？

------------

其实算法上并不需要优化！
我们注意到因为只有$60$个城市，所以换车次数不会超过$60$，那么我们把$k_{\max}$就可以可看做是$60$，于是$O(k_{\max}\cdot n^3)=60^4=1.296\times 10^7$.于是就很愉快地通过了。

------------
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

---

