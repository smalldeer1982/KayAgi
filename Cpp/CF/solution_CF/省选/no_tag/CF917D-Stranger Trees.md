# Stranger Trees

## 题目描述

Will shares a psychic connection with the Upside Down Monster, so everything the monster knows, Will knows. Suddenly, he started drawing, page after page, non-stop. Joyce, his mom, and Chief Hopper put the drawings together, and they realized, it's a labeled tree!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917D/df747e5880f95d5a7f2a7fa3db2b2bf252f41ce9.png)A tree is a connected acyclic graph. Will's tree has $ n $ vertices. Joyce and Hopper don't know what that means, so they're investigating this tree and similar trees. For each $ k $ such that $ 0<=k<=n-1 $ , they're going to investigate all labeled trees with $ n $ vertices that share exactly $ k $ edges with Will's tree. Two labeled trees are different if and only if there's a pair of vertices $ (v,u) $ such that there's an edge between $ v $ and $ u $ in one tree and not in the other one.

Hopper and Joyce want to know how much work they have to do, so they asked you to tell them the number of labeled trees with $ n $ vertices that share exactly $ k $ edges with Will's tree, for each $ k $ . The answer could be very large, so they only asked you to tell them the answers modulo $ 1000000007=10^{9}+7 $ .

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
0 2 1 ```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
1 7 7 1 ```

## 样例 #3

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
0 9 6 1 ```

# 题解

## 作者：Soulist (赞：73)


怎么别的做法都是 $\mathcal{O(n^4)}$ 的神仙解法

先考虑设 $g_i$ 表示至少有 $i$ 条边重合的方案数，这等价于有 $n-i$ 个联通块的方案数。那么对于 $f_i$ 的计算就只需要二项式反演即可。

然后考虑如果我们已经知道了一个联通块划分 S 之后我们怎么做，可以证明假设当前有 $k$ 个联通块，第 $i$ 个联通块大小为 $a_i$，$n=\sum a_i$，则有生成树的数量为 $\prod a\times n^{k-2}$，证明的话放文章结尾，两种方式，可以挑选你喜欢的看（

于是对于一组划分，假设有 $k$ 个联通块，则对于答案的贡献为 $\prod a_i\times n^{k-2}$，如果考虑 $f_{i,j,k}$ 为 $i$ 为根的子树划分了 $j$ 个联通块，当前点所在的联通块大小为 $k$ 的贡献和是可以轻易做到 $\mathcal O(n^3)$ 的。

考虑 $\prod a$ 的组合意义，我们可以视为将树划分为若干个联通块，每个联通块内放入一个球的方案数，这样通过树上背包的 trick 直接 dp 复杂度就是 $\mathcal O(n^2)$ 了，然后 $\mathcal O(n^2)$ 的二项式反演就可以了。

核心代码：

```cpp

void dfs( int x, int fa ) {
	dp[x][1][0] = 1, dp[x][1][1] = 1, sz[x] = 1 ; 
	for( int v : G[x] ) {
		if( v == fa ) continue ; dfs( v, x ) ;
		drep( j, 1, sz[x] ) drep( k, 1, sz[v] ) {
			inc( bef[x][j + k][0], dp[x][j][0] * dp[v][k][1] % P ) ;
			inc( bef[x][j + k][1], dp[x][j][1] * dp[v][k][1] % P ) ; 
			inc( bef[x][j + k - 1][0], dp[x][j][0] * dp[v][k][0] % P ) ;
			inc( bef[x][j + k - 1][1], ( dp[x][j][1] * dp[v][k][0] + dp[x][j][0] * dp[v][k][1] ) % P ) ; 
		}
		sz[x] += sz[v] ; 
		rep( j, 1, sz[x] ) dp[x][j][0] = bef[x][j][0], dp[x][j][1] = bef[x][j][1], bef[x][j][0] = 0, bef[x][j][1] = 0 ; 
	}
}
```

证明：


- $\rm Matrix-Tree$ 定理。

我们先将 S 中的所有联通块缩起来，考虑构建一张新图，我们连接 $i\to j$ 的无向边，但是连接重边数量为 $a_i\times a_j$

那么根据矩阵树定理，我们可以得到其 Kirchhoff 矩阵为：

$\begin{bmatrix}a_1(\sum a -a_{1})&...& 0\\0&a_2(\sum a-a_{2})&...0\\0&...&0\\0&...&a_k(\sum a-a_{k})\end{bmatrix}-\begin{bmatrix}0&...& a_{1}\times a_{k}\\a_{2}\times a_{1}&0&...a_{2}\times a_{k}\\a_{k-1}\times a_{1}&...&a_{k-1}\times a_{k}\\a_{k}\times a_{1}&...&0\end{bmatrix}$

即：

$$\begin{bmatrix}a_1(n -a_{1})&...& ...&-a_1\times a_k\\-a_2\times a_1&a_2(n-a_{2})&...&a_2\times a_k\\...&...&...&...\\-a_{k-1}\times a_1&...&a_{k-1}\times(n-a_{k-1})&-a_{k-1}\times a_k\\-a_1\times a_{k}&...&...&a_k(n-a_{k})\end{bmatrix}$$

然后我们删除一行一列后的行列式即为答案：

$$\begin{bmatrix}a_1(n -a_{1})&...& ...\\-a_2\times a_1&a_2(n-a_{2})&...\\...&...&...\\-a_{k-1}\times a_1&...&a_{k-1}\times(n-a_{k-1})\end{bmatrix}$$

根据行列式的性质，我们把每行的一个公共系数 $a_i$ 都提取出来后得到：

$$\prod_{i=1}^{n-1}a_i\begin{bmatrix}(n -a_{1})&...& ...\\-a_1&(n-a_{2})&...\\...&...&...\\-a_{1}&...&(n-a_{k-1})\end{bmatrix}$$

然后我们将第 $2\to n-1$ 列都加到第 $1$ 列上会得到：（这里的 $n$ 指联通块数量）

$$\begin{bmatrix}a_k&...& ...\\a_k&(n-a_{2})&...\\...&...&...\\a_k&...&(n-a_{k-1})\end{bmatrix}$$

然后我们把每行都减去第一行得到：

$$\begin{bmatrix}a_k&...& ...\\0&n&...\\...&...&...\\0&...&n\end{bmatrix}$$

于是其行列式为 $n^{k-2}a_k$，所以答案为：$\Big(\prod a_i \Big)n^{k-2}$

- $\rm prufer$ 序列。

将每个联通块视为一个大联通块，设其出现次数为 $k$，则其对于答案的贡献为 $a_i^{k+1}$

由于每个 $\rm prufer$ 序列都是合法的，我们等价于求有 $k-2$ 个位置，每个数出现次数为 $i$ 时对于答案的贡献为 $a_j^{i+1}$，求所有方案的权值。

构建每个数的 EGF 为 $F(a_i)$，我们得到：

$$Ans=\prod a_i \bigg((k-2)![x^{k-2}]\prod F(a_i)\bigg)$$

$$Ans=\prod a_i\bigg((k-2)![x^{k-2}]\prod e^{a_ix}\bigg)$$

$$Ans=\prod a_i\frac{(k-2)!(\sum a_i)^{k-2}}{(k-2)!}$$

$$Ans=\prod a_i \times n^{k-2}$$

---

## 作者：wsyhb (赞：28)

## 题意

给定 $n$ 个节点的树，考虑下列问题：

> 求有多少棵不同的树满足：与给定树重合的边恰好有 $x$ 条。  
> 两棵树不同当且仅当存在边 $(u,v)$ 在一棵树中出现且不在另一棵树中出现。

对 $x=0,1,\cdots,n-1$ 分别求出上述问题的答案。

**数据范围**：$n \le 100$。（可做到 $O(n^2)$ 或更低的时间复杂度）

## 题解

记上述问题的答案为 $f_x$，发现 $f$ 很难求，考虑转化。

考虑容斥：设 $g_x$ 表示包含给定树中 $x$ 条边的树的数量（不要求其它 $n-1-x$ 条边不被包含；对于不同的 $x$ 条边，同一棵树可能被计算多次），则有：

$$f_x=\sum_{i=x}^{n-1}(-1)^{i-x}\binom{i}{x}g_i$$

（即运用了**二项式反演**，证明可参考[xyyxyyx 的博客 - 二项式反演证明](https://blog.csdn.net/xyyxyyx/article/details/103523894)，亦可仿照[这篇题解](https://www.luogu.com.cn/blog/wsyhb/post-ti-xie-luo-gu-p3349-zjoi2016-xiao-xing-xing)中子集反演证明的部分，列出**初始恒等式**进行证明）

因此可以在 $O(n^2)$ 的时间里用 $g$ 求得 $f$，接下来考虑如何求 $g$。

------------

有一个重要的结论：

> 若 $n$ 个点的无向图中有 $k$ 个连通块，且其中第 $i$ 个连通块大小为 $s_i$，则把这 $k$ 个连通块用 $k-1$ 条边连通起来的方案数为 $\prod{s_i} \cdot n^{k-2}$。

可以使用**无根树的 Prufer 序列**证明，也可以使用**矩阵树定理**证明。

具体可参考[OI Wiki - 图连通方案数](https://oi-wiki.org/graph/prufer/#_3)（Prufer 序列+多项式定理）和[Soulist 的题解](https://www.luogu.com.cn/blog/Soulist/solution-cf917d)（矩阵树定理 & Prufer 序列+EGF）

------------

包含给定树中 $x$ 条边等价于有 $n-x$ 个连通块，因此我们只需对每个 $x$ 计算出所有情况的 $\prod{s_i}$ 之和，并乘上 $n^{n-x-2}$ 即可。

考虑**树形背包 DP**，设 $f_{u,i,j}$ 表示：考虑以 $u$ 为根的子树，将其分成 $i$ 个连通块，且 $u$ 所在连通块大小为 $j$ 的所有情况的 $\prod{s_i}$ 之和（还未乘上 $j$）。不难想到转移：

$$f_{u,x,a} \cdot f_{v,y,b} \cdot b \to f'_{u,x+y,a}$$

$$f_{u,x,a} \cdot f_{v,y,b} \to f'_{u,x+y-1,a+b}$$

其中 $f'$ 表示更新后的 $f$，$v$ 是 $u$ 的儿子。（后文表示相同含义）

**说明**：第一行表示不合并，第二行表示将 $v$ 所在连通块与 $u$ 所在连通块合并。

树上背包是 $O(n^2)$ 的（因为任意两个点只会在它们的 LCA 处合并恰好一次），算上额外的一维是 $O(n^3)$ 的，可以继续优化。

------------

有一个经典的 Trick：**各部分数量之积等于在每一部分选一个元素的方案数**。

因此把第三维改为是否已选过：设 $f_{u,i,k}$ 表示，考虑以 $u$ 为根的子树，将其分成 $i$ 个连通块，且未/已选择好 $u$ 所在连通块的点（$k=0/1$）。类似地可得转移：

$$f_{u,x,0} \cdot f_{v,y,1} \to f'_{u,x+y,0}$$

$$f_{u,x,1} \cdot f_{v,y,1} \to f'_{u,x+y,1}$$

$$f_{u,x,0} \cdot f_{v,y,0} \to f'_{u,x+y-1,0}$$

$$f_{u,x,1} \cdot f_{v,y,0}+f_{u,x,0} \cdot f_{v,y,1} \to f'_{u,x+y-1,1}$$

**说明**：

- 前两行表示不合并。
	- $v$ 所在连通块必须已选点。
	- $u$ 所在连通块是否选点与 $v$ 无关。
- 后两行表示将 $v$ 所在连通块与 $u$ 所在连通块合并。
	- 若合并前两个连通块都未选点，则合并后未选点。
	- 若合并前恰有一个连通块已选点，则合并后已选点。
	- 注意两个连通块不能都选点。

初始时 $f_{u,1,0}=f_{u,1,1}=1$。

总时空复杂度为 $O(n^2)$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=100+5;
int End[max_n<<1],Last[max_n],Next[max_n<<1],e;
inline void add_edge(int x,int y)
{
	End[++e]=y,Next[e]=Last[x],Last[x]=e;
	End[++e]=x,Next[e]=Last[y],Last[y]=e;
}
const int mod=1e9+7;
inline int get_sum(int a,int b)
{
	return a+b-(a+b>=mod?mod:0);
}
int sz[max_n],dp[max_n][max_n][2],f[max_n][2];
void dfs(int x,int fa)
{
	dp[x][1][0]=dp[x][1][1]=1,sz[x]=1;
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
		{
			dfs(y,x);
			for(int j=1;j<=sz[x];++j)
				for(int k=1;k<=sz[y];++k)
				{
					f[j+k][0]=(f[j+k][0]+1ll*dp[x][j][0]*dp[y][k][1])%mod;
					f[j+k][1]=(f[j+k][1]+1ll*dp[x][j][1]*dp[y][k][1])%mod;
					f[j+k-1][0]=(f[j+k-1][0]+1ll*dp[x][j][0]*dp[y][k][0])%mod;
					f[j+k-1][1]=(f[j+k-1][1]+1ll*dp[x][j][1]*dp[y][k][0]+1ll*dp[x][j][0]*dp[y][k][1])%mod;
				}
			sz[x]+=sz[y];
			for(int j=1;j<=sz[x];++j)
				for(int k=0;k<=1;++k)
				{
					dp[x][j][k]=f[j][k];
					f[j][k]=0;
				}
		}
	}
}
int C[max_n][max_n],Pow[max_n];
inline void init(int n)
{
	for(int i=0;i<=n;++i)
	{
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=get_sum(C[i-1][j-1],C[i-1][j]);
	}
	Pow[0]=1;
	for(int i=1;i<=n;++i)
		Pow[i]=1ll*Pow[i-1]*n%mod;
}
int F[max_n],G[max_n];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	dfs(1,0);
	init(n);
	for(int i=0;i<=n-2;++i)
		G[i]=1ll*dp[1][n-i][1]*Pow[n-i-2]%mod;
	G[n-1]=1;
	for(int i=0;i<=n-1;++i)
	{
		for(int j=i;j<=n-1;++j)
		{
			if((j^i)&1) // (j-i)&1
				F[i]=(F[i]-1ll*C[j][i]*G[j])%mod;
			else
				F[i]=(F[i]+1ll*C[j][i]*G[j])%mod;
		}
		F[i]+=F[i]<0?mod:0;
		printf("%d%c",F[i],i<n-1?' ':'\n');
	}
	return 0;
}
```

## 彩蛋

**这里是本题解的写作背景。**（果然有题目背景就会有题解背景吗（雾））

本文的目的之一：~~祭奠~~纪念自己在模拟赛中做不出来原题。

~~同时谴责出题人/组题人在模拟赛中放（我不会大家都会的）原题！！！~~

本篇文章的完成时间为 2021.11.2，结合创建时间可知，这是当时留的一个坑。

大约四个月前的我在阅读了 Soulist 的题解以后大有收获，打算写一篇题解。

可后来由于各种各样的原因咕掉了……

今天模拟赛恰好考到了这道题（唯一的区别：$n$ 开大到了 $8000$，且略微卡空间），而我完全没有意识到这是自己做过的原题 /wul。

尽管我想到了用二项式反演做恰好和至少的转化，想到了用 Prufer 序列和 Matrix Tree 定理推一推式子，且隐隐约约觉得会有什么结论。

我最终没能推出来式子，并且还发现自己对 Matrix Tree 定理的记忆十分模糊，以至于根本无法应用……

最终只好打了个 $O(n^{n-1})$ 的暴力走人……

经同学一提醒，翻出原题瞬间想起了一切……

于是我今天一口气把这个坑填了！

---

## 作者：Prean (赞：11)

# 题目大意
一张有 $ n $ 个节点的完全图，再给出这张图的一棵生成树，问该图有多少颗生成树和这颗生成树的公共边总共有 $ k $ 条，求助 $ 0 \leq k \leq n-1 $ 时所有 $ k $ 的答案。

# 做法
首先我们知道矩阵树定理求的是 所有生成树的边权之积的和。

那么我们设树边的边权为 $ x $，非树边的边权为 $ 1 $，若一棵生成树和该树有 $ k $ 条公共边，则该生成树的边权之积为 $ x^k $。

求和之后的 $ k $ 次项就是答案了。

但是每一次行变换我们需要做 $ 1 $ 次乘法和 $ n $ 次减法，复杂度虽然是 $ O(n^4\log n) $ 的，但是如此大的常数即使是 CF 的机子也会 T。。。

我们换个思路，FFT 的运算过程就是 带入+差值，那我们把这个过程提到外面来做不就好了？

答案一定是一个 $ n-1 $ 次多项式，根据代数基本定理，我们只需要 $ n $ 个点值就能把它插出来。

我们枚举 $ x $ 从 $ 1 $ 到 $ n $，对于每一个 $ x $ 跑一次矩阵树，复杂度 $ O(n^4) $。

最后我们可以 $ O(n) $ 拉格朗日差值，也可以 $ O(n^3) $ 高斯消元，我写的是高斯消元，因为最近刷矩阵树逐渐熟悉了高斯消元（

code:
```cpp#include<cstdio>
const int M=105,mod=1e9+7;
int n,u[M],v[M],x[M];
int G[M][M],Matrix[M][M];
inline int Add(const int&a,const int&b){
    return a+b>=mod?a+b-mod:a+b;
}
inline int Del(const int&a,const int&b){
    return a-b<0?a-b+mod:a-b;
}
inline int pow(int a,int b=mod-2){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
inline int Matrix_Tree(){
    register int i,j,k,d,inv,ans=1;
    for(i=2;i<=n;++i){
        inv=pow(Matrix[i][i]);
        for(j=i+1;j<=n;++j){
            d=1ll*Matrix[j][i]*inv%mod;
            for(k=i;k<=n;++k)Matrix[j][k]=Del(Matrix[j][k],1ll*d*Matrix[i][k]%mod);
        }
        ans=1ll*ans*Matrix[i][i]%mod;
    }
    return ans;
}
inline void Gauss(){
    register int i,j,k,d,inv;
    for(i=1;i<=n;++i){
        inv=pow(G[i][i]);
        for(j=1;j<=n;++j){
            if(i==j)continue;
            d=1ll*G[j][i]*inv%mod;
            for(k=i;k<=n+1;++k)G[j][k]=Del(G[j][k],1ll*d*G[i][k]%mod);
        }
    }
}
signed main(){
    register int i,j,k,X;
    scanf("%d",&n);
    for(i=1;i<=n;++i){
        for(j=1;j<=n;++j){
            if(i==j)G[i][j]=n-1;
            else G[i][j]=mod-1;
        }
    }
    for(i=1;i<n;++i)scanf("%d%d",u+i,v+i);
    for(i=1;i<=n;++i){
        for(j=1;j<=n;++j){
            for(k=1;k<=n;++k){
                Matrix[j][k]=G[j][k];
            }
        }
        x[i]=i;G[i][n+1]=Matrix_Tree();
        for(j=1;j<n;++j){
            ++G[u[j]][u[j]];++G[v[j]][v[j]];
            --G[u[j]][v[j]];--G[v[j]][u[j]];
        }
    }
    for(i=1;i<=n;++i){
        G[i][1]=1;X=x[i];
        for(j=2;j<=n;++j){
            G[i][j]=X;X=1ll*X*x[i]%mod;
        }
    }
    Gauss();
    for(i=1;i<=n;++i)printf("%d ",1ll*G[i][n+1]*pow(G[i][i])%mod);
}
```

---

## 作者：asuldb (赞：8)

[题目](https://www.luogu.org/problemnew/show/CF917D)

看题解的时候才突然发现$zky$讲过这道题啊，我现在怕不是一个老年人了

众所周知矩阵树求得是这个

$$\sum_{T}\prod_{e\in T}w_e$$

而我们现在的这个问题有些鬼畜了，给定一棵树，求和这棵树有$k$条公共边的生成树个数

我们如何区分出和原生成树有几条边呢，容斥显然不是很可做，于是之后就不会啦

看了题解发现这是神仙题，引用潮子名言我可能这辈子是做不出来了

对于不在给定生成树里的边$w_e$我们设$w_e=1$，对于在生成树里的边我们将其设成$w_e=x$，没错就是$x$，就是一个多项式

这样矩阵树得到的结果必然也是一个多项式，其中$k$次项系数就对应了和原树有$k$条公共边的方案数

如果模数是$NTT$模数那么我们直接矩阵树套多项式就好啦，但是$O(n^4logn)$的复杂度显然不科学啊

考虑一些其他求多项式系数的方法，暴力一点也行

于是我们可以高斯消元

这个多项式是一个$n-1$的多项式，于是我们可以直接给$x$找$n$种取值，之后得到$n$个方程，之后高斯消元就可以求出系数来了

代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=105;
const int mod=1e9+7;
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
int n,x[maxn],y[maxn],ans[maxn];
int a[maxn][maxn],b[maxn][maxn];
inline int ksm(int a,int b) {
	int S=1;
	while(b) {if(b&1) S=(1ll*S*a)%mod;b>>=1;a=(1ll*a*a)%mod;}
	return S;
}
inline void reBuild() {
	for(re int i=1;i<=n;i++) a[i][i]=n-1;
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++) {
			if(i==j) continue;
			a[i][j]=mod-1;
		}
}
inline int solve(int t) {
	reBuild();
	for(re int i=1;i<n;i++) {
		int u=x[i],v=y[i];
		a[u][u]--,a[v][v]--;
		a[u][u]+=t,a[v][v]+=t;
		a[u][v]=a[v][u]=mod-t;
	}
	int o=0;
	for(re int i=1;i<n;i++) {
		int p;
		for(p=i;p<n;++p) if(a[p][i]) break;
		if(p!=i) std::swap(a[p],a[i]),o^=1;
		int Inv=ksm(a[i][i],mod-2);
		for(re int j=i+1;j<n;j++) {
			int mul=(1ll*a[j][i]*Inv)%mod;
			for(re int k=i;k<n;k++)
				a[j][k]=(a[j][k]-1ll*a[i][k]*mul%mod+mod)%mod;
		}
	}
	int now=1;
	for(re int i=1;i<n;i++) now=(1ll*now*a[i][i])%mod;
	return o?(mod-now)%mod:now;
}
int main() {
	n=read();
	for(re int i=1;i<n;i++) x[i]=read(),y[i]=read();
	for(re int i=0;i<n;i++) {
		b[i][n]=solve(i+1);
		b[i][0]=1;
		for(re int j=1;j<n;j++) b[i][j]=ksm(i+1,j);
	}
	for(re int i=0;i<n;i++) {
		int p;
		for(p=i;p<n;++p) if(b[p][i]) break;
		if(p!=i) std::swap(b[p],b[i]);
		int Inv=ksm(b[i][i],mod-2);
		for(re int j=n;j>=i;--j) b[i][j]=(1ll*b[i][j]*Inv)%mod;
		for(re int j=i+1;j<n;j++)
			for(re int k=n;k>=i;--k)
				b[j][k]=(b[j][k]-1ll*b[j][i]*b[i][k]%mod+mod)%mod;
	}
	ans[n-1]=b[n-1][n];
	for(re int i=n-2;i>=0;--i) {
		ans[i]=b[i][n];
		for(re int j=n-1;j>i;--j)
			ans[i]=(ans[i]-1ll*ans[j]*b[i][j]%mod+mod)%mod;
	}
	for(re int i=0;i<n;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：谁是鸽王 (赞：7)

## 【题解】CF917D Stranger Trees(prufer序列+二项式反演)

考虑有一个东西叫做$prufer$序列，然后个东西叫做[图联通方案数](https://oi-wiki.org/graph/prufer/#_3)。

然后我们考虑先算一下**至少**$k$条边在方案里的方案数，我们可以用树形dp

$dp(i,j,k)$表示对于$i$节点及其子树，共有$j$条边被选中，且和$i$共有$k$个点是在一个联通块里的$\prod siz[]$之和。转移很简单啦。(但是CF的内存访问极慢！要用对内存友好的写法)

通过$dp()$可以很方便的求出来是$f(k)$表示至少有$k$条边在方案里的方案数。

我们设$g(k)$为答案，那么考虑$f(k)$和$g(k)$的关系

值得注意的事情是，由于我们是在树上选择边，所以我们钦定选择的边是不会成环的，也就是说任何一个选树边的方案都是合法的，所以我们有
$$
f(k)=\sum_{j\ge k} {j\choose k} g(j)
$$
根据二项式反演直接得到
$$
g(k)=\sum_{j\ge k}{j\choose k}(-1)^{k-j}f(j)
$$

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<assert.h>

using namespace std;  typedef long long ll; 
inline int qr(){
	int ret=0,f=0,c=getchar();
	while(!isdigit(c))f|=c==45,c=getchar();
	while(isdigit(c)) ret=ret*10+c-48,c=getchar();
	return f?-ret:ret;
}

const int maxn=105;
const int mod=1e9+7;
int dp[maxn][maxn][maxn],n,siz[maxn],ans[maxn];
int invs[maxn*maxn],c[maxn][maxn];
int inv[maxn][maxn*maxn];
vector<int>e[maxn];
void add(int fr,int to){e[fr].push_back(to);e[to].push_back(fr);}
int MOD(const int&x){return x>=mod?x-mod:x;}
int MOD(const int&x,const int&y){return 1ll*x*y%mod;}
int MOD(const int&x,const int&y,const int&z,const int&b){return 1ll*x*y%mod*b%mod*z%mod;}
int ksm(const int&ba,const int&p){
	int ret=1;
	for(int t=p,b=ba;t;t>>=1,b=MOD(b,b))
		if(t&1) ret=MOD(ret,b);
	return ret;
}

void pre(const int&n){
	invs[1]=1;
	for(int t=2;t<=n;++t) invs[t]=MOD(mod-mod/t,invs[mod%t]),assert(MOD(t,invs[t])==1);
	for(int t=n+1;t<=n*n;++t) invs[t]=MOD(mod-mod/t,invs[mod%t]);
	for(int t=1;t<=n*n;++t)
		for(int i=1;i<=n;++i)
			inv[i][t]=MOD(i,invs[t]);
	for(int t=0;t<=n;++t)
		for(int i=c[t][0]=1;i<=t;++i)
			c[t][i]=MOD(c[t-1][i-1]+c[t-1][i]);
	//cerr<<"c[5][2]="<<c[5][2]<<endl;
}

void dfs(const int&now,const int&last){
	dp[now][0][1]=1;
	siz[now]=1;
	for(auto t:e[now]){
		if(t^last){
			dfs(t,now);
			int g[maxn][maxn];
			memset(g,0,sizeof g);
			/*
			for(int i=siz[now]-1;~i;--i){// edge_totol
				for(int j=0,edj=min(siz[t]-1,i);j<=edj;++j){// edge_target
					for(int p=1,edp=siz[t];p<=edp;++p){// vertices_target
						if(dp[t][j][p]){
							for(int k=siz[now];k;--k){// vertices_total
								int&s=g[i][k];
								//connect
								if(i-j-1>=0&&k>p) s=(s+1ll*dp[now][i-j-1][k-p]*dp[t][j][p]%mod*inv[k][(k-p)*p])%mod;
								//dont connect
								if(i>=j) s=(s+1ll*dp[now][i-j][k]*dp[t][j][p])%mod;
							}
						}
					}
				}
			}这种写法很不优秀，内存访问非常不连续！
			*/
			for(int i=0;i<siz[now];++i)
				for(int k=1;k<=siz[now];++k)
					for(int j=0;j<siz[t];++j)
						for(int p=1;p<=siz[t];++p){
							ll l=1ll*dp[now][i][k]*dp[t][j][p]%mod;
							g[i+j+1][k+p]=(g[i+j+1][k+p]+l*inv[k+p][k*p])%mod;
							g[i+j][k]=MOD(g[i+j][k]+l);
						}
			siz[now]+=siz[t];
			memcpy(dp[now],g,sizeof g);
		}
	}
}

int rt,val=1e9;
void dfsrt(int now,int last){
	siz[now]=1;
	int k=0;
	for(auto t:e[now])
		if(!siz[t])
			siz[now]+=siz[t],k=max(k,siz[t]);
	k=max(k,n-siz[now]);
	if(k<val) rt=now;
}

int main(){
	n=qr();
	pre(101);
	for(int t=1;t<n;++t) add(qr(),qr());
	int k=min(n,55);
	dfs(k,0);
	for(int e=0;e<=n-1;++e){
		for(int i=1;i<=e+1;++i)
			ans[e]=MOD(ans[e]+dp[k][e][i]);
		if(e<=n-2) ans[e]=MOD(ksm(n,n-2-e),ans[e]);
		if(e==n-1) ans[e]=1;
	}
	for(int t=0;t<=n-1;++t){
		int ret=0;
		for(int i=t;i<=n-1;++i){
			int d=MOD(c[i][t],ans[i]);
			if((t^i)&1) ret=MOD(ret-d+mod);
			else ret=MOD(ret+d);
		}
		cout<<ret<<' ';
	}
	cerr<<endl;
	return 0;
}
```

---

## 作者：Karry5307 (赞：7)

### 题意

给定一个 $n$ 个点的树，对于 $0\leq k\leq n-1$ 求 $K_{n}$ 中与给定树的 $n$ 条边重合生成树的数量。

数据范围：$1\leq n\leq 100$。

### 题解

简单题，但 $O(n^2)$ 做法实属牛逼，我写的 $O(n^4)$。

如果做过 P5296 或者 P6624 的看一眼就知道将是给定树上的边的那些边权值设为 $x$，不是的设为 $1$，然后 Matrix-Tree 即可。

但是高斯消元是 $O(n^3)$，多项式乘法 $O(n^2)$，总时间复杂度 $O(n^5)$ 过不去，于是需要优化。

考虑不直接用多项式算而是将具体的 $x$ 代入进去，然后由于答案是多项式所以最后插值回来，这个时候复杂度为 $O(n^4)$ 就可以过题了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=151,MOD=1e9+7;
ll n,w,fd,rr;
ll x[MAXN],y[MAXN],mat[MAXN][MAXN],f[MAXN],g[MAXN],r[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void add(ll x,ll y,ll w)
{
	mat[x][x]=(mat[x][x]+w)%MOD,mat[y][y]=(mat[y][y]+w)%MOD;
	mat[x][y]=(mat[x][y]-w+MOD)%MOD,mat[y][x]=(mat[y][x]-w+MOD)%MOD;
}
inline ll det()
{
	ll pivot,cof,res=1,sgn=1;
	for(register int i=1;i<n;i++)
	{
		pivot=n;
		for(register int j=i;j<n;j++)
		{
			if(mat[j][i])
			{
				pivot=i;
				break;	
			}
		}
		if(pivot==n)
		{
			return 0;
		}
		pivot!=i?swap(mat[pivot],mat[i]),sgn*=-1:1;
		for(register int j=i+1;j<n;j++)
		{
			cof=(li)mat[j][i]*qpow(mat[i][i],MOD-2)%MOD;
			for(register int k=i;k<n;k++)
			{
				mat[j][k]=(mat[j][k]-(li)mat[i][k]*cof%MOD+MOD)%MOD;
			}
		}
		res=(li)res*mat[i][i]%MOD;
	}
	return sgn==1?res:(MOD-res)%MOD;
}
inline ll calc(ll w)
{
	memset(mat,0,sizeof(mat));
	for(register int i=1;i<=n;i++)
	{
		for(register int j=i+1;j<=n;j++)
		{
			add(i,j,1);
		}
	}
	for(register int i=1;i<=n-1;i++)
	{
		add(x[i],y[i],w-1);
	}
	return det();
}
inline void mul(ll x)
{
	g[fd+1]=0;
	for(register int i=fd-1;i>=0;i--)
	{
		g[i+1]=(g[i+1]+g[i])%MOD,g[i]=(li)g[i]*(MOD-x)%MOD;
	}
	fd++;
}
inline void div(ll x)
{
	ll invl=qpow(x,MOD-2);
	for(register int i=0;i<fd;i++)
	{
		g[i]=(MOD-(li)g[i]*invl%MOD)%MOD,g[i+1]=(g[i+1]-g[i]+MOD)%MOD;
	}
	fd--;
}
int main()
{
	n=read(),g[0]=fd=1;
	for(register int i=1;i<=n-1;i++)
	{
		x[i]=read(),y[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		r[i]=calc(i),mul(i);
	}
	for(register int i=1;i<=n;i++)
	{
		div(i),rr=1;
		for(register int j=1;j<=n;j++)
		{
			j!=i?rr=(li)rr*(i-j+MOD)%MOD:1;
		}
		rr=(li)r[i]*qpow(rr,MOD-2)%MOD;
		for(register int i=0;i<fd;i++)
		{
			f[i]=(f[i]+(li)rr*g[i])%MOD;
		}
		mul(i);
	}
	for(register int i=0;i<n;i++)
	{
		printf("%d ",f[i]);
	}
}
```

---

## 作者：sry_ (赞：4)

#### 题意

给定一个 $n$ 个结点的有标号树，共 $k$ 次操作，每次可以将树上一条边删去再加上一条，使得他仍然是一棵树。

问 $k$ 次操作结束后有多少个本质不同的树。

$n\leq 50,1\leq k\leq n$ 。

#### 题解

虽然场上过了，但是有更优秀的做法（

先把问题简化一下，考虑当前树为 $T$ ，我们 $k$ 次操作以后的树为 $T'$ ，只要 $T$ 与 $T'$ 的重边个数 $\leq k$ 个就为一种方案。

设 $f(i)$ 表示联通块恰好为 $i$ 个的方案。

~~显然我没想到~~对图跑矩阵树定理，每个位置为 $1/x$ ，最后 $f(i)$ 就为 $[x^{n-i}]$ 。

暴力的复杂度为 $\mathcal O(n^5)/O(n^3\log n)$ ，但可以插 $n$ 个值最后还原此多项式，时间复杂度为 $O(n^4)$ 。 

一个较为明显的做法为假设我们已经知道重边是哪几条如何计算答案，一个经典结论是如果当前联通块个数为 $x_1,x_2,...,x_r$ ，那么将该联通块连成树的方案数为 $\prod_{i=1}^{r} x_i n^{r_2}$ 。那么我们直接上该方案数会忽略到新加进来的边是重边的情况，那么容斥计算。

形式化的讲，设 $g(i)$ 表示钦定联通块个数有 $i$ 个的方案，那么
$$
f(i)=\sum_{j=1}^i (-1)^{i-j} g(j)\dbinom{n-j}{i-j}
$$
而 
$$
g(i)=\sum n^{i-2} \prod_{\sum^ix =n} x_i
$$
显然 $g(i)$ 可以通过树形 $dp$ 解决，时间复杂度 $\mathcal O(n^4)$ 。

更优秀的做法是考虑 $\prod_{i} x_i$ 的组合意义，相当于在每个联通块内选择一个特殊点，问最后方案数。

那么设 $f_{i,j,0/1}$ 表示在以 $i$ 为根的子树中选择 $j$ 个联通块，其中包含 $i$ 的联通块是否有特殊点被选择。

转移时考虑子树合并 $(u,v)$ 的联通块是否有特殊点。

时间复杂度 $\mathcal O(n^2)$ 。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long
#define mod 1000000007
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
inline int read(){
	int f=1,ans=0; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return f*ans;
}
const int MAXN=111;
int binom[MAXN][MAXN],N,K,U[MAXN],V[MAXN],pw[MAXN],Invn,inv[MAXN]; vector<int> vec[MAXN];
int ksm(int a,int b){int ans=1;while(b){if(b&1) ans*=a,ans%=mod;a*=a,a%=mod;b>>=1;}return ans;}
namespace Force{
	int Ans[MAXN],F[MAXN];
	struct Union{
		int siz[MAXN],f[MAXN];
		void init(){for(int i=1;i<=N;i++) f[i]=i,siz[i]=1;return;}
		int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
		void merge(int x,int y){int t1=find(x),t2=find(y);f[t2]=t1,siz[t1]+=siz[t2];return;}
	}UU;
	bool G[MAXN];
	void calc(){
		UU.init(); for(int i=1;i<=N-1;i++) if(G[i]) UU.merge(U[i],V[i]); 
		int mul=1,cnt=0;
		for(int i=1;i<=N;i++) if(UU.find(i)==i) mul*=UU.siz[i],mul%=mod,mul*=N,mul%=mod,++cnt;
		int res=mul*Invn%mod*Invn%mod;
		Ans[cnt]+=res,Ans[cnt]%=mod;
	}
	void dfs(int u){
		if(u==N){
			calc(); return;
		}
		G[u]=1; dfs(u+1);
		G[u]=0; dfs(u+1);
		return;
	}
	void Main(){
		dfs(1);
		for(int i=1;i<=N;i++){
			for(int j=1;j<=i;j++){
				int opt=((i-j)&1?mod-1:1);
				F[i]+=opt*Ans[j]*binom[N-j][i-j]%mod; F[i]%=mod;
			}
		}
		int res=0;
		for(int i=1;i<=K+1;i++) res+=F[i],res%=mod;
		printf("%lld\n",res); exit(0);
	}
}
namespace std{
	int f[MAXN][MAXN][MAXN][2],siz[MAXN],g[MAXN][MAXN][2];
	int Ans[MAXN],F[MAXN];
	void dfs(int u,int fath){
		siz[u]=1,f[u][0][1][0]=1;
		for(auto v:vec[u]) if(v!=fath){
			dfs(v,u);
			memset(g,0,sizeof(g));
			for(int i=0;i<=siz[u];i++) for(int j=0;j<=siz[u];j++){
				for(int I=0;I<=siz[v];I++) for(int J=0;J<=siz[v];J++){
					g[i+I][j][0]+=f[u][i][j][0]*f[v][I][J][1]; g[i+I][j][0]%=mod;
					g[i+I][j+J][0]+=f[u][i][j][0]*f[v][I][J][0]; g[i+I][j+J][0]%=mod;
				}
			}
			siz[u]+=siz[v];
			for(int i=0;i<=siz[u];i++) for(int j=0;j<=siz[u];j++) f[u][i][j][0]=g[i][j][0];
		}
		for(int i=siz[u];i>=1;i--) for(int j=1;j<=siz[u];j++) f[u][i][j][1]=f[u][i-1][j][0]*j%mod*N%mod;
		return;
	}
	void Main(){
		dfs(1,0);
		for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) Ans[i]+=f[1][i][j][1],Ans[i]%=mod;
		for(int i=1;i<=N;i++) Ans[i]=Ans[i]*Invn%mod*Invn%mod;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=i;j++){
				int opt=((i-j)&1?mod-1:1);
				F[i]+=opt*Ans[j]%mod*binom[N-j][i-j]%mod; F[i]%=mod;
			}
		}
		for(int i=N;i>=1;i--) printf("%lld ",F[i]);printf("\n");
		exit(0);
	}
}
namespace faster{
	int f[MAXN][MAXN][2],g[MAXN][2],siz[MAXN],Ans[MAXN],F[MAXN];
	void dfs(int u,int fath){
		f[u][1][0]=1,f[u][1][1]=N; siz[u]=1;
		for(auto v:vec[u]) if(v!=fath){
			dfs(v,u); memset(g,0,sizeof(g));
			for(int i=0;i<=siz[u];i++) for(int j=0;j<=siz[v];j++){
				if(i+j) g[i+j-1][0]+=f[u][i][0]*f[v][j][0],g[i+j-1][0]%=mod;
				g[i+j][0]+=f[u][i][0]*f[v][j][1]; g[i+j][0]%=mod;
				if(i+j) g[i+j-1][1]+=f[u][i][0]*f[v][j][1],g[i+j-1][1]%=mod;
				if(i+j) g[i+j-1][1]+=f[u][i][1]*f[v][j][0],g[i+j-1][1]%=mod;
				g[i+j][1]+=f[u][i][1]*f[v][j][1],g[i+j][1]%=mod;
			}
			siz[u]+=siz[v];
			for(int i=0;i<=siz[u];i++) f[u][i][0]=g[i][0],f[u][i][1]=g[i][1];
		}return;
	}
	void Main(){
		dfs(1,0);
		for(int i=1;i<=N;i++) Ans[i]=f[1][i][1],Ans[i]%=mod;
		for(int i=1;i<=N;i++) Ans[i]=Ans[i]*Invn%mod*Invn%mod;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=i;j++){
				int opt=((i-j)&1?mod-1:1);
				F[i]+=opt*Ans[j]%mod*binom[N-j][i-j]%mod; F[i]%=mod;
			}
		}
		for(int i=N;i>=1;i--) printf("%lld ",F[i]);printf("\n");
		exit(0);
	}
}
signed main(){
	//freopen("1.in","r",stdin);
	//freopen("kaisou.out","w",stdout);
	binom[0][0]=1; N=read(); for(int i=1;i<N;i++){U[i]=read(),V[i]=read();vec[U[i]].pb(V[i]),vec[V[i]].pb(U[i]);}
	Invn=ksm(N,mod-2);
	inv[1]=1; for(int i=2;i<=N;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	pw[0]=1; for(int i=1;i<=N;i++) pw[i]=pw[i-1]*N%mod;
	for(int i=1;i<=N;i++){
		binom[i][0]=1; for(int j=1;j<=i;j++) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%mod;
	}
	//Force::Main();
	//std::Main();
	faster::Main();
}

```


---

## 作者：1saunoya (赞：3)

学到了……

这里是一个不会 $prufer$ 序列的菜鸡。被 $\texttt{S\red{oulist}}$ 看不起的垃圾 $\Theta(n^4)$ 的做法。

## 题目大意:

给一棵 $n$ 个点的树，有多少棵由这 $n$ 个点之间的边构造成的树，与给定的树恰好有 $k$ 条边重复。（对于任意的 $k \in[1, n]$ 输出答案）

## 生成树，计数，优先想到的是矩阵树定理。

矩阵树定理是干这么一件事情。

$$\sum_{w\in T} \prod w$$

我们可以令**每条被选中的边**的边权为 $x^1$。 **没有被选中的边** 的边权为 $x^0$。

然后对应的 $x^k$ 系数就是 $k$ 条边重复的答案，可以自己玩一下（

这个玩意我们其实可以直接暴力 dft，但是过不去（

然后我们发现一件事情，我们可以先用矩阵树定理算出来把各种 $k \in [1,n]$ 的值算出来？不就可以高斯消元了吗。

令 $p_i$ 为答案，$b_i$ 为把 $i$ 带进去的值。

$$b_j = \sum_{i=0}^n p_i \times i^j$$

高斯消元大概是这样一个事情。

假设你有 $n$ 个未知数为 $p_1, ... , p_n$。已知数为 $g\{\}, b\{\}$

($b_i$ 已经计算过了，$g_{i,j} = i ^{j-1}$)

通过初中知识你知道。（

$n$ 元一次是可以用 $n$ 个式子解出来的。

$$\large\lceil g_{1,1} \times p_1 + ... + g_{1, n} \times p_n = b_1\rceil$$
$$\large| g_{2,1} \times p_1 + ... + g_{2, n} \times p_n = b_2|$$
$$......$$
$$\large\lfloor g_{n,1} \times p_1 + ... + g_{n, n} \times p_n = b_n\rfloor$$

把这个部分高斯消元板子搞搞就做完了。

---

## 作者：Freopen (赞：1)

题目需要求出恰好$k$条边不相同的方案数$f(k)$

考虑求出固定$n-1-k$条边一定和原来的树相同的方案$g(k)$

$g(k) =\ sum_{i=0}^{k} f(i) \binom{k}{i}$

然后二项式反演即可求出$f$

考虑如果求$g$

固定$n-1-k$条边，那么我们就是要对$k+1$个联通块求生成树个数。

根据[WC2019数树](https://www.luogu.com.cn/problem/P5206)中的结论我们可以知道方案数为$n^{k-1}\prod_{1\leq i \leq k-1} a_i$

其中$a_i$是第$i$个联通块的大小。

那么在每个连通块都选择一个点的方案数就是$\prod_{1\leq i \leq k-1} a_i$。

所以我们可以$f_{i,j,0/1}$表示以$i$为根的子树内固定了$size_i-1-j$条边一定和原来的树相同，而且$i$的连通块有没有选择点的方案数。

然后就可以算出$g$了。
时间复杂度$O(n^2)$

代码：
```cpp
#include<bits/stdc++.h>
#define maxn 105
#define mod 1000000007
#define rep(i,j,k) for(int i=(j),LIM=(k);i<=LIM;i++)
#define per(i,j,k) for(int i=(j),LIM=(k);i>=LIM;i--)
using namespace std;

int n;
vector<int>G[maxn];
#define pb push_back
int sz[maxn],f[maxn][maxn][2],ans[maxn];

int C[maxn][maxn];
int Pow(int b,int k){ int r=1;for(;k;k>>=1,b=1ll*b*b%mod) if(k&1) r=1ll*r*b%mod; return r; }

void dfs(int u,int ff,int v=0){
	sz[u] = f[u][0][0] = f[u][0][1] = 1;
	rep(i,0,G[u].size()-1) if((v=G[u][i])^ff){
		dfs(v,u);
		static int g[maxn][2]={};
		rep(j,0,sz[u]+sz[v]) g[j][0] = g[j][1] = 0;
		rep(j,0,sz[u]) rep(k,0,sz[v])
			g[j+k][0] = (g[j+k][0] + f[u][j][0] * 1ll * f[v][k][0]) % mod,
			g[j+k][1] = (g[j+k][1] + f[u][j][0] * 1ll * f[v][k][1] + f[u][j][1] * 1ll * f[v][k][0]) % mod,
			g[j+k+1][0] = (g[j+k+1][0] + f[u][j][0] * 1ll * f[v][k][1]) % mod,
			g[j+k+1][1] = (g[j+k+1][1] + f[u][j][1] * 1ll * f[v][k][1]) % mod;
		sz[u] += sz[v];
		rep(j,0,sz[u]) 
			f[u][j][0] = g[j][0],
			f[u][j][1] = g[j][1];
	}
}

int main(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		G[u].pb(v),G[v].pb(u);
	}
	dfs(1,0);
	ans[0] = 1;
	rep(i,1,n-1) ans[i] = f[1][i][1] * 1ll * Pow(n,i-1) % mod;
	rep(i,(C[0][0]=1),n) rep(j,(C[i][0]=1),i) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
	rep(i,1,n-1) rep(j,0,i-1) ans[i] = (ans[i] - 1ll * C[n-1-j][i-j] * ans[j]) % mod;
	per(i,n-1,0) printf("%d%c",(ans[i]+mod)%mod," \n"[i==0]);
} 
```


---

## 作者：lhm_ (赞：1)

生成树计数问题用矩阵树定理来考虑。

矩阵树定理求得的为$\sum\limits_T\prod\limits_{e\in T}v_e$，也就是所有生成树的边权积的和。

这题边是不带权的，应用矩阵树定理前，我们必须考虑给每条边赋上一个权值。

可以从多项式的角度来考虑解决生成树和给定树有$k$条边重复这一条件，将给定树的边边权赋为$x$，其余边赋为$1$，那么应用矩阵树定理后得到的多项式中第$k$次项$x^k$的系数即为恰好有$k$条边重复的方案数。

发现直接代入多项式来求行列式不太现实，那么可以先求得$x$在取$1$到$n$时行列式的值，然后就得到了$n$个方程，把原多项式的系数看作未知数，代入$x$得到的值来作为现在的系数，那么就可以通过高斯消元来求解了。

具体实现看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 210
#define mod 1000000007
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n;
ll a[maxn][maxn],b[maxn][maxn],e[maxn][maxn];
ll inv(ll x)
{
    ll y=mod-2,ans=1;
    while(y)
    {
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
ll det()
{
    ll ans=1;
    for(int i=1;i<n;++i)
    {
        ll p=inv(b[i][i]);
        for(int j=i+1;j<n;++j)
        {
            ll d=b[j][i]*p%mod;
            for(int k=i;k<n;++k)
                b[j][k]=(b[j][k]-b[i][k]*d%mod+mod)%mod;
        }
        ans=ans*b[i][i]%mod;
        if(!b[i][i]) return 0;
    }
    return ans;
}
void gauss()
{
    for(int i=1;i<=n;++i)
    {
        ll d=inv(a[i][i]);
        for(int j=i;j<=n+1;++j) a[i][j]=a[i][j]*d%mod;
        for(int j=i+1;j<=n;++j)
        {
            d=a[j][i];
            for(int k=i;k<=n+1;++k)
                a[j][k]=(a[j][k]-a[i][k]*d%mod+mod)%mod;
        }
    }
    for(int i=n;i;--i)
        for(int j=i-1;j;--j)
            a[j][n+1]=(a[j][n+1]-a[j][i]*a[i][n+1]%mod+mod)%mod;
}
int main()
{
    read(n);
    for(int i=1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        e[x][y]=e[y][x]=1;
    }
    for(int i=1;i<=n;++i)
    {
        a[i][1]=1;
        for(int j=2;j<=n;++j)
            a[i][j]=a[i][j-1]*i%mod;
    }
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=n;++i)
        {
            b[i][i]=0;
            for(int j=1;j<=n;++j)
            {
                if(i==j) continue;
                if(e[i][j]) b[i][j]=mod-k,b[i][i]+=k;
                else b[i][j]=mod-1,b[i][i]++;
            }
        }
        a[k][n+1]=det();
    }
    gauss();
    for(int i=1;i<=n;++i) printf("%lld ",a[i][n+1]);
    return 0;
}
```


---

## 作者：liangzihao (赞：1)

生成树计数可以想到矩阵树定理，但是显然矩阵树跑出来的值是边权的乘积的和，不能统计该树上的边与给出的树的重合边数。

考虑把一条边看做一个多项式，如果这条边在原树上，这条边的权值看作是$x^1$，否则看做$1$。于是一棵树的总权值就是$x^k$，其中$k$是与原树重合的边的数目。然后我们可以把这些多项式求和，用矩阵树算出来，总和就是一个多项式，其中$x^k$的系数表示有$k$条边与原树相同。

我们不能把多项式带人进去算，但是我们知道最终的多项式的次数是$n-1$的。所以我们可以取$n$个数代替$x$去求行列式，因为是要求出系数，所以直接暴力高斯消元插值就好了。复杂度是$O(n^4)$的。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define LL long long

const int maxn=105;
const LL mod=1e9+7;

using namespace std;

int n,x,y;
LL a[maxn][maxn],c[maxn][maxn],b[maxn];

LL power(LL x,LL y)
{
    if (y==1) return x;
    LL c=power(x,y/2);
    c=(c*c)%mod;
    if (y%2) c=(c*x)%mod;
    return c; 
}

LL det(int n)
{
    LL ans=1;
    for (int i=1;i<=n;i++)
    {
    	LL inv=power(c[i][i],mod-2);
        for (int j=i+1;j<=n;j++)
        {
            LL rate=c[j][i]*inv%mod;
            for (int k=i;k<=n;k++)
            {
                c[j][k]=(c[j][k]+mod-rate*c[i][k]%mod)%mod;
            }
        }
        ans=(ans*c[i][i])%mod;
        if (!c[i][i]) break;
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        a[x][y]=1;
        a[y][x]=1;
    }
    for (int k=1;k<=n;k++)
    {
        memset(c,0,sizeof(c));
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=n;j++)
            {
                if (i!=j)
                {
                    if (a[i][j]) c[i][j]=mod-k,c[i][i]+=k;
                            else c[i][j]=mod-1,c[i][i]+=1;
                } 
            }
        }		
        b[k]=det(n-1);
    }
    
    for (int i=1;i<=n;i++)
    {
        c[i][1]=1;
        for (int j=2;j<=n;j++) c[i][j]=(c[i][j-1]*i)%mod;
    }
    for (int i=1;i<=n;i++)
    {
        LL inv=power(c[i][i],mod-2);
        for (int j=1;j<=n;j++)
        {
            if (i==j) continue;
            LL rate=c[j][i]*inv%mod;
            for (int k=i;k<=n;k++)
            {
                c[j][k]=(c[j][k]+mod-rate*c[i][k]%mod)%mod;
            }
            b[j]=(b[j]+mod-rate*b[i]%mod)%mod;
        }
    }
    for (int i=1;i<=n;i++)
    {
        b[i]=b[i]*power(c[i][i],mod-2)%mod;
        printf("%lld ",b[i]);
    }
}
```

---

