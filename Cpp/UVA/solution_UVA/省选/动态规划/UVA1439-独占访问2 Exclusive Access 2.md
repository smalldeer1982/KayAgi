# 独占访问2 Exclusive Access 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4185

[PDF](https://uva.onlinejudge.org/external/14/p1439.pdf)

## 样例 #1

### 输入

```
2
P Q
R S
6
P Q
Q R
R S
S T
T U
U P
4
P Q
P Q
P Q
P Q
3
P Q
Q R
R P
6
P Q
Q S
S R
R P
P S
R Q```

### 输出

```
0
P Q
R S
0
P Q
R Q
R S
T S
T U
P U
0
P Q
P Q
P Q
P Q
1
P Q
Q R
P R
2
P Q
Q S
R S
P R
P S
R Q```

# 题解

## 作者：_兰_ (赞：10)

简化版题面：

给定一张无向图，求给这张图定向成$\rm DAG$之后最长路最短是多少。$n\leq 15$

### $\rm{Sol~1}$

考虑直接$dp$。$f_{s,u,v}$表示考虑了点集$s$，最长路端点是$u,v$的最小值。每次转移的时候枚举$u,v,w$，从$(u,v),(v,w)$两个状态转移到$(u,w)$。复杂度$O(3^nn^3)$ 

### $\rm Sol~2$

考虑证明一个二级定理：

>定理 $1.1$
>
>* 一张无向图定向成的$\rm DAG$，当其最长路最短时，其最长路为$\rm X-1$，其中$\rm X$表示**不连通集覆盖数**。也就是对于一张有向图图$\rm \{V,E\}$，定义一种划分$P$，使得划分出的每个集合中所有点不连通。

考虑一种证明：

* 首先一定有$\rm X-1\geq maxL$。因为其上的每个点是连通的。
* 其次我们考虑，如果每次删除全部出度为$0$点，放到一个集合里，那么一定合法，并且可以满足$\rm X=maxL+1$。

但其实这东西也可以直接用$\rm dilworth$定理的对偶定理证出来：

> 定理 $2.1$（$\rm dilworth$定理）
>
> **令$\rm (X,≤)$是一个有限偏序集，并令$m$是反链的最大的大小。则$\rm X$可以被划分成$m$个但不能再少的链。**

对偶一下：

> 定理 $2.2$:
> 令$\rm (X,≤)$是一个有限偏序集，并令$r$是其最大链的大小。则$X$可以被划分成$r$个但不能再少的反链。

然后”反链“连接的是”不可比的点“，也就是本题中”不连通的点“。

于是我们就可以快乐地状压了。

```cpp
int *g, *f ;
int main(){
	cin >> N >> M ; 
	memset(f, 63, sizeof(f)) ; 
	int u, v, i, j ; T = (1 << N) - 1 ;
	for (i = 1 ; i <= M ; ++ i)
		cin >> u >> v, -- u, -- v, E[u] |= (1 << v), E[v] |= (1 << u) ;
	f[0] = 0, g[0] = 1 ; 
	for (i = 0 ; i <= N ; ++ i) Sz[1 << i] = i ; 
	for (i = 1 ; i <= T ; ++ i){
		j = (i & (-i)) ;
		if (!g[i ^ j]) continue ; 
		if (E[Sz[j]] & (i ^ j)) continue ; 
		g[i] = 1 ; 
	}
	for (i = 1 ; i <= T ; ++ i)
		for (j = i ; j ; j = (j - 1) & i)
			if (g[j]) f[i] = min(f[i], f[i ^ j] + 1) ; 
	cout << f[T] - 1 << endl ; return 0 ;
}
```



---

## 作者：Filberte (赞：2)

## [UVA-1439](https://www.luogu.com.cn/problem/UVA1439)

题意简化：给定一张无向图，把图中每条边定向，使得新的图是一个 $\mathrm{DAG}$，问最长路最短是多少。

以 $d_i$ 表示以 $i$ 结尾的路径的最长长度。注意到如果 $i$ 和 $j$ 之间有边，那么  $d_i \not= d_j$。对于 $\mathrm{DAG}$，我们可以按照 $d$ 分层，层内两点间无边。此时问题转化为给原图分成 $k$ 层，层内无边，我们需要最小化 $k$。或者说，我们需要把一个图中的点分成若干个独立集，问最少需要多少个独立集。

这个问题是可以用动态规划来求解的。题目中规定点数小于等于 $15$，再结合集合，不难想到状压 DP。用 $f[s]$ 表示把 $s$ 对应的点（$s$ 是把所有点选与不选二进制压缩后的数）划分成若干个独立集，最少需要多少个。$f[s] = \min\{f[s - a]\} +1$，其中 $a$ 是一个独立集且 $a \subseteq s$。

（以下的 $n$ 说的是点数，而不是 PDF 中指的边数）

直接转移的复杂度是 $O(3^n \times n)$ 的（因为每个集合还需要判断是否为独立集）。但其实可以用 $O(2^n\times n^2)$ 的时间复杂度先预处理出所有独立集，对于每条边 $(u,v)$，标记 $(u,v)$ 不在同一个集合内。然后枚举每个集合 $s$，用 $i,j$ 枚举集合内两个不同的点，如果这两个点不能在一个集合内，就把 $s$ 判定为不是独立集。如果 $s$ 通过了所有检验，则 $s$ 为独立集。

预处理完后就可以 $O(1)$ 判断一个集合是否为独立集了。输出方案乱搞就好了。总时间复杂度为 $O(2^n \times n^2 + 3^n)$。

代码（因为点的编号不一定连续，所以用搜索的方法来写好写一点，类似数位 DP 那样）：

```C++
#include <bits/stdc++.h>
using namespace std;
const int N = 17;
int f[1 << N], du[1 << N], pre[1 << N], d[N];
int m , inf;
char u[N * N], v[N * N];  
bool e[N][N];
void dfs(int S){
	if(!S || f[S] != inf) return ;
	for(int a = S;a;a = S & (a - 1)) if(du[a]){
		int T = S - a;
		dfs(T);
		if(f[T] + 1 < f[S]) f[S] = f[T] + 1, pre[S] = T;
	}
}
void init(){
 	memset(f, 0x3f, sizeof(f));	
	memset(du, 1, sizeof(du));
	memset(e, 0, sizeof(e));
	memset(pre, -1, sizeof(pre));
	inf = f[0];
	f[0] = 0, du[0] = 1;
}
int main(){
	while(scanf("%d",&m) != EOF){
		int S = 0;	
		init();
		for(int i = 1;i <= m;i++){
			cin >> u[i] >> v[i];
			int x = u[i] - 'L', y = v[i] - 'L';
			S = S | (1 << x) | (1 << y);
			e[x][y] = e[y][x] = 1;
		}
		for(int s = S;s;s = S & (s - 1)){
			for(int i = 0;i < 15;i++)
				for(int j = 0;j < 15;j++) if(i != j){
					if(((s >> i) & 1) && ((s >> j) & 1) && e[i][j]) du[s] = 0;
				}
		}
		dfs(S);	
		int D = f[S];
		printf("%d\n",D - 2);
		for(int s = S;s != -1;s = pre[s], D--) 
			for(int i = 0;i < 15;i++) if((s >> i) & 1) d[i] = D;//D越来越小，不用取min 
		for(int i = 1;i <= m;i++){
			int x = u[i] - 'L', y = v[i] - 'L';
			if(d[x] > d[y]) swap(u[i], v[i]);
			printf("%c %c\n",u[i],v[i]);
		}
	}
	return 0;
}
```



---

## 作者：iiiiiyang (赞：2)

[心动的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17406146.html)

[题目链接](https://www.luogu.com.cn/problem/UVA1439)

怎么唯一一篇题解这么抽象，完全看不懂![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)。

给定一张无向图，求给这张图定向成 DAG 之后的最长路最短是多少。转化一下变成对 DAG 进行分层，每一层之间的点没有连边，使得层数尽可能少，那么最后的层数就是答案。

那么就求出若干个独立集，让独立集总数尽可能少。这是经典的色数问题，我们使用状压 DP，可以在 $\mathcal O(3^n)$ 的复杂度下解决。

具体方法是设 $f_S$ 表示当前选择的点的集合为 $S$ 最少需要分成几个独立集。转移式子是平凡的，即 $f_{S} = \min_{T \subseteq S \wedge T \text{是独立集}} \{ f_{S \oplus T} \} + 1$。还需要做的就是预处理出哪些集合状态是独立集，暴力枚举集合，枚举集合中的两两点判断有无连边即可，这部分复杂度是 $\mathcal O(2^n \times n^2)$。

至于具体的定向方案，我们只需要给几个独立集每个分配一个层数，然后让层数小的统一指向层数大的即可，于是我们需要知道钦定出来的每个独立集具体包含哪些元素，记一个前驱数组看是由什么状态转移而来即可。

代码实现用了记搜，总复杂度是 $\mathcal O(n + 2^n \times n^2 + 3^n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define mp make_pair
#define fi first
#define se second
#define pii pair<int,int> 
using namespace std;
 
template<typename T=int> inline T read()
{
	T s=0,w=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}
template<typename T=long long> inline void write(T x,char ch)
{
	if(x<0) x=-x,putchar('-');
	static char stk[25]; int top=0;
	do {stk[top++]=x%10+'0',x/=10;} while(x);
	while(top) putchar(stk[--top]);
	putchar(ch);
	return;
}
 
namespace MyTool
{
	static const int Mod=998244353;
	template<typename T> inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
	template<typename T> inline void cmax(T &a,T b) {a=a>b?a:b;}
	template<typename T> inline void cmin(T &a,T b) {a=a<b?a:b;}
	inline void Madd(int &a,int b) {a=a+b>Mod?a+b-Mod:a+b;}
	inline void Mdel(int &a,int b) {a=a-b<0?a-b+Mod:a-b;}
	inline void Mmul(int &a,int b) {a=1ll*a*b%Mod;}
	inline void Mmod(int &a) {a=(a%Mod+Mod)%Mod;}
	inline int  Cadd(int a,int b)  {return a+b>=Mod?a+b-Mod:a+b;}
	inline int  Cdel(int a,int b)  {return a-b<0?a-b+Mod:a-b;}
	inline int  Cmul(int a,int b)  {return a*b%Mod;}
	inline int  Cmod(int a)  {return (a%Mod+Mod)%Mod;}
	inline int  gcd(int a,int b)   {return b?gcd(b,a%b):a;}
	inline int  qpow(int a,int b)  {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
	inline int  qmul(int a,int b)  {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
	template<typename T> inline T power(T x)    {return x*x;}
}
using namespace MyTool;
 
inline void file()
{
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	return;
}
 
bool Mbe;

namespace LgxTpre
{
	static const int MAX=16;
	static const int inf=2147483647;
	static const int INF=4557430888798830399;
	static const int mod=1e9+7;
	static const int bas=131;
	
	static const int N=15;
	int n,G[MAX][MAX],d[MAX],k;
	struct edge{char x,y;}e[MAX<<3];
	int all,f[1<<MAX],g[1<<MAX],pre[1<<MAX];
	
	void dfs(int S)
	{
		if(!S) return f[S]=0,void();
		if(~f[S]) return;
		f[S]=INF;
		for(int T=S;T;T=S&(T-1)) if(!g[T])
		{
			dfs(S^T);
			if(f[S^T]+1<f[S]) f[S]=f[S^T]+1,pre[S]=S^T;
		}
		return;
	}
	
	inline void lmy_forever()
	{
		while(scanf("%lld",&n)!=EOF)
		{
			all=0,k=0;
			memset(G,0,sizeof G),memset(f,-1,sizeof f);
			memset(d,0,sizeof d),memset(g,0,sizeof g);
			for(int i=1;i<=n;++i)
			{
				scanf(" %c %c",&e[i].x,&e[i].y);
				all|=1<<(e[i].x-'L'),all|=1<<(e[i].y-'L');
				G[e[i].x-'L'][e[i].y-'L']=G[e[i].y-'L'][e[i].x-'L']=1;
			}
			for(int S=all;S;S=all&(S-1))
				for(int i=0;i<N;++i) if(S>>i&1)
					for(int j=0;j<N;++j) if(S>>j&1)
						if(i!=j&&G[i][j]) 
							g[S]=1;
			dfs(all),write(f[all]-2,'\n');
			while(all)
			{
				for(int i=0;i<N;++i) if(all>>i&1) d[i]=k;
				all=pre[all],++k;
			}
			for(int i=1;i<=n;++i)
			{
				if(d[e[i].x-'L']>d[e[i].y-'L']) Swp(e[i].x,e[i].y);
				putchar(e[i].x),putchar(' '),putchar(e[i].y),putchar('\n');
			}
		}
		return;
	}
}
 
bool Med;
 
signed main()
{
//	file();
	fprintf(stderr,"%.3lf MB\n",(&Med-&Mbe)/1048576.0);
	LgxTpre::lmy_forever();
	cerr<<1e3*clock()/CLOCKS_PER_SEC<<" ms\n";
	return (0-0);
}
```

---

