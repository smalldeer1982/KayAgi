# [ARC157E] XXYX Binary Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc157/tasks/arc157_e

$ N $ 頂点の根付き木が与えられます． 頂点には $ 1 $ から $ N $ の相異なる整数の番号が付いており，根は頂点 $ 1 $ です． 根以外の各頂点 $ i $ の親は頂点 $ P_i $ であり，根を含む各頂点は，**子を持たないか，ちょうど $ 2 $ 個の子を持つか**のいずれかです．

与えられた木の各頂点に `X`, `Y` のいずれかの文字を書き込んで，以下の条件を満たすことが可能かどうかを判定してください．

**条件:** 木の各辺に関して，両端点に書き込まれた文字を親 $ P_i $ から子 $ i $ に向かう順に並べて得られる長さ $ 2 $ の文字列を考える． そのような文字列はのべ $ (N\ -\ 1) $ 個あるが，そのうち

- ちょうど $ A $ 個が `XX`，
- ちょうど $ B $ 個が `XY`，
- ちょうど $ C $ 個が `YX` であり，
- `YY` は存在しない．
 
$ T $ 個のテストケースが与えられるので，それぞれについて答えてください．

## 说明/提示

### 制約

- $ T\ \geq\ 1 $
- $ N\ \geq\ 1 $
- $ 1 $ つの入力に含まれるテストケースについて，$ N $ の総和は $ 10^4 $ 以下である．
- $ A\ \geq\ 0 $
- $ B\ \geq\ 0 $
- $ C\ \geq\ 0 $
- $ A\ +\ B\ +\ C\ =\ N\ -\ 1 $
- $ 1\ \leq\ P_i\ <\ i\ (2\ \leq\ i\ \leq\ N) $
- 各頂点 $ k\ (1\ \leq\ k\ \leq\ N) $ は親 $ P_i\ (2\ \leq\ i\ \leq\ N) $ として**合計 $ 0 $ 回または $ 2 $ 回**現れる．
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて，たとえば頂点 $ 1 $ から $ 7 $ の順に `XXYXYXX` と書き込めば， - 辺 $ (1,\ 2) $ で得られる文字列は `XX`， - 辺 $ (1,\ 3) $ で得られる文字列は `XY`， - 辺 $ (2,\ 4) $ で得られる文字列は `XX`， - 辺 $ (2,\ 5) $ で得られる文字列は `XY`， - 辺 $ (3,\ 6) $ で得られる文字列は `YX`， - 辺 $ (3,\ 7) $ で得られる文字列は `YX`， であり，`XX`, `XY`, `YX` がそれぞれ $ 2 $ 個ずつとなって条件を満たします． $ 2 $ 番目のテストケースについて，たとえば `XYYXXXX` と書き込めば条件を満たします． $ 3 $ 番目のテストケースについては，どのように書き込んでも条件を満たしません．

## 样例 #1

### 输入

```
3
7 2 2 2
1 1 2 2 3 3
7 0 2 4
1 1 2 2 3 3
7 2 0 4
1 1 2 2 4 4```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：william555 (赞：7)

题意：

你有一个 $ N $ 个节点的有根树，节点编号 $ 1\sim N $ ，其中节点 $ 1 $ 是根。除了根节点外，第 $ i $ 个节点的父亲是 $ P_i $ 。所有节点要么有 $ 0 $ 个儿子，要么有 $ 2 $ 个儿子。

你需要给每个节点写一个 `X` 或者 `Y` 。每条边按从上往下可以得到一个长度为 $ 2 $ 的字符串。你需要满足：

- 恰有 $ A $ 条边的字符串是 `XX` ；
- 恰有 $ B $ 条边的字符串是 `XY` ；
- 恰有 $ C $ 条边的字符串是 `YX` ；
- 没有任何边的字符串是 `YY` 。

共有 $ T $ 组测试数据。$\sum N \le 10000$。



没有 `YY` ，说明写 `Y` 的节点一定是形成独立集。由此可以发现一定有 $\frac C 2$ 个非叶子节点是 Y，根据根节点是否是 `Y` 讨论，写 `Y` 的叶子节点有 $B-\frac C 2 $ 或 $B-\frac C 2 +1$ 个。于是我们把问题转化成：判断能否在树上选一个独立集，其中有 $p$ 个叶子，$q$ 个非叶子。

于是我们可以直接写出 dp：$f_{x,i,0/1}$ 表示 $x$ 子树，选了 $i$ 个叶子，$x$ 是否被选的情况下最多能选多少个非叶子。然后我们就可以做树上背包。时间复杂度 $O(n^2)$。

```c++
#include<bits/stdc++.h>
using namespace std;
inline int in(){
    int x;
    scanf("%d",&x);
    return x;
}
const int N=1e4+5,inf=1e9;
int n,A,B,C;
vector<int> e[N];
int f[N][2][5005];
int sz[N];
void dfs(int x){
    sz[x]=0;
    if(!e[x].size()){
        sz[x]=1,f[x][0][0]=0,f[x][0][1]=-inf,f[x][1][1]=0,f[x][1][0]=-inf;
        return;
    }
    f[x][0][0]=0,f[x][1][0]=1;
    for(int y:e[x]){
        dfs(y);
        for(int j=sz[x]+1;j<=sz[x]+sz[y];j++)
            f[x][0][j]=f[x][1][j]=-inf;
        for(int i=sz[x];i>=0;i--){
            for(int j=sz[y];j>=0;j--){
                f[x][1][i+j]=max(f[x][1][i+j],f[x][1][i]+f[y][0][j]);
                f[x][0][i+j]=max(f[x][0][i+j],f[x][0][i]+max(f[y][0][j],f[y][1][j]));
            }
        }
        sz[x]+=sz[y];
    }
}
void solve(){
    n=in(),A=in(),C=in(),B=in();
    for(int i=1;i<=n;i++)e[i].clear();
    for(int i=2;i<=n;i++)e[in()].push_back(i);
    if(n==1){puts("Yes");return;}
    if(B&1){puts("No");return;}
    B>>=1;
    dfs(1);
    if(sz[1]>=C-B&&C-B>=0&&f[1][0][C-B]>=B)puts("Yes");
    else if(sz[1]>=C-B+1&&C-B+1>=0&&f[1][1][C-B+1]>=B)puts("Yes");
    else puts("No");
}
int main(){
    int T=in();
    while(T--)solve();
    return 0;
}
```

 

---

## 作者：cwfxlh (赞：3)

# [AT_arc157_e](https://www.luogu.com.cn/problem/AT_arc157_e)    

唐氏 2800。       

称标为 Y 的点为选中的点。第四条限制表明，选中的点集是一个独立集。根据第三条限制还可以得出选中的点集中恰好有 $\frac{c}{2}$ 个点不是叶子。第二条限制可以得出点集大小为 $b+1$  或 $b$，两种情况分别对应根节点选和不选。             

分类讨论，对于根节点选的情况，就是要选出 $b+1-\frac{c}{2}$ 个叶子与 $\frac{c}{2}$ 个非叶子节点，并且构成独立集。根节点不选的话，就要选出 $b-\frac{c}{2}$ 个叶子与 $\frac{c}{2}$ 个非叶子节点。令 $dp_{i,j,0/1}$ 表示 $i$ 子树内选中了 $j$ 个叶子，$i$ 是否被选中，选中的非叶子节点个数的最大值。判断一下最大值是否不小于要求的非叶子节点数即可。树上背包复杂度 $O(n^2)$。      

代码：    


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,c,p[10003],dp[10003][10003][2],g[10003][2],sz[10003];
vector<int>son[10003];
void dfs(int now){
	sz[now]=1;
	if(son[now].size()==0){
		dp[now][0][0]=0;
		dp[now][1][1]=0;
		return;
	}
	dp[now][0][0]=0;
	dp[now][0][1]=1;
	for(auto i:son[now]){
		dfs(i);
		for(int j=0;j<=sz[now];j++){
			g[j][0]=dp[now][j][0];
			g[j][1]=dp[now][j][1];
		}
		for(int j=0;j<=sz[i]+sz[now];j++)dp[now][j][0]=dp[now][j][1]=-100000;
		for(int j=0;j<=sz[now];j++){
			for(int u=0;u<=sz[i];u++){
				dp[now][j+u][0]=max(dp[now][j+u][0],g[j][0]+max(dp[i][u][1],dp[i][u][0]));
				dp[now][j+u][1]=max(dp[now][j+u][1],g[j][1]+dp[i][u][0]);
			}
		}
		sz[now]+=sz[i];
	}
	return;
}
void sol(){
	cin>>n>>a>>b>>c;
	for(int i=1;i<=n;i++){
		son[i].clear();
		son[i].shrink_to_fit();
		dp[i][0][0]=dp[i][0][1]=dp[i][1][0]=dp[i][1][1]=-100000;
	}
	for(int i=2;i<=n;i++)cin>>p[i];
	for(int i=2;i<=n;i++)son[p[i]].emplace_back(i);
	dfs(1);
	if(n==1){
		cout<<"Yes\n";
		return;
	}
	if(c%2==0&&b-(c/2)>=0&&dp[1][b-(c/2)][0]>=(c/2)){
		cout<<"Yes\n";
		return;
	}
	if(c%2==0&&b-(c/2)+1>=0&&dp[1][b-(c/2)+1][1]>=(c/2)){
		cout<<"Yes\n";
		return;
	}
	cout<<"No\n";
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)sol();
	return 0;
}
```

---

## 作者：Dovish (赞：1)

## 分析

直接设 $f_{i,x,y}$ 表示子树 $i$ 能否构造出有 $x$ 个 ```XY```，$y$ 个 ```YX``` 。直接转移似乎可以做到 $O(\frac {n^3}{\omega})$。

但是我们希望通过只设两个维度来做。

考虑设有 $a$ 个叶子为 ```Y```，$b$ 个非根节点为 ```Y```，分讨一下根的情况：

那么 ```XY``` 的个数即为 $a+b$，```YX``` 的个数为 $2b+2[root=y]$。

容易发现，如果 $b$ 的个数一定，那么 $a$ 的取值是从 $0$ 开始连续的一段。

设 $f_{u,s,0/1}$ 表示 $u$ 子树内，有 $s$ 个节点为 ```Y```，当前节点为 ```X/Y``` 时可选为 ```Y``` 的叶子的最大值。

然后直接转移就可以了。

最后我们需要的节点 ```Y``` 和叶子 ```Y``` 的个数都是确定的，直接判断即可。

复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc(u) (ch[u][0])
#define rc(u) (ch[u][1])
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define fst first
#define sed second
using namespace std;
const int N=1e4+10,M=1e6+10,inf=1e9,mod=1e9+7;
bool MS;int used;
int f[N][N/2][2];// 0:X 1:Y
int ch[N][2],sz[N],n;
void init()
{
	rep(i,1,n)
	{
		rep(j,0,(n-1)/2)
		f[i][j][0]=f[i][j][1]=-inf;
		lc(i)=rc(i)=0;
	}
}
void check_min(int k,int&x){x=min(x,k);}
void check_max(int k,int&x){x=max(x,k);}
bool tag[N];
void dfs(int u)
{
	sz[u]=1;
	if(lc(u))dfs(lc(u)),sz[u]+=sz[lc(u)];
	if(rc(u))dfs(rc(u)),sz[u]+=sz[rc(u)];
	
	if(lc(u))
	{
		tag[u]=1;
		rep(i,0,(sz[lc(u)]-1)/2)
		rep(j,0,(sz[rc(u)]-1)/2)
		{
			check_max(f[lc(u)][i][0]+f[rc(u)][j][0],f[u][i+j][0]);
			check_max(f[lc(u)][i][1]+f[rc(u)][j][0],f[u][i+j+tag[lc(u)]][0]);
			check_max(f[lc(u)][i][0]+f[rc(u)][j][1],f[u][i+j+tag[rc(u)]][0]);
			check_max(f[lc(u)][i][1]+f[rc(u)][j][1],f[u][i+j+tag[lc(u)]+tag[rc(u)]][0]);
			check_max(f[lc(u)][i][0]+f[rc(u)][j][0],f[u][i+j][1]);
		}
	}
	else
	{
		f[u][0][0]=0;
		f[u][0][1]=1;
		tag[u]=0;
	}
}
int a,b,c;
bool solve()
{
	cin>>n>>a>>b>>c;
	init();
	rep(i,2,n)
	{
		int fa;
		cin>>fa;
		if(!lc(fa))lc(fa)=i;
		else rc(fa)=i;
	}
	dfs(1);
	if(c%2==0)
	{
		int need=b-c/2;
		if(need>=0&&need<=f[1][c/2][0])
		return 1;
		
		need=b-(c-2)/2;
		if(need>=0&&need<=f[1][(c-2)/2][1])
		return 1;
	}
	return 0;
}
bool MT;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	if(solve())cout<<"Yes\n";
	else cout<<"No\n";
	cerr<<"Memory:"<<(&MS-&MT)/1048576.0<<"MB Time:"<<clock()/1000.0<<"s\n";
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言
比较有趣的一道观察性质题，没有独立做出来，有点可惜。

# Part 2：正文

第一个观察是没有 $\texttt{YY}$ 的这个要求告诉我们如果我们把填 $\texttt{Y}$ 的点看成白色，那么所有白点构成了一个独立集。但是只有这一点做不了，所以我们考虑其它限制带来的信息。

观察 $\texttt{YX}$。由于原树是一个满二叉树，而 $\texttt{Y}$ 又构成独立集，所以每个填 $\texttt{Y}$ 的节点都会贡献零个或两个 $\texttt{YX}$。因此 $\texttt{YX}$ 的个数一定是偶数个。这也启示我们一件事，如果填在叶子上的 $\texttt{Y}$ 的个数固定了，$\texttt{Y}$ 的总个数也随之确定，即在非叶子上的 $\texttt{Y}$ 为定值。

再考虑 $\texttt{XY}$ 的个数带给我们的限制。我们惊讶的发现，由于 $\texttt{Y}$ 是独立集，所以每一个不在根节点上的 $\texttt{Y}$ 会恰好贡献一个 $\texttt{XY}$ 结构，也就是说不在根节点上的 $\texttt{Y}$ 的个数为定值。结合上文所述，如果我们固定了根节点填什么，我们就可以直接知道我们要在叶子上填多少个 $\texttt{Y}$，在非叶子上填多少个 $\texttt{Y}$。由于 $A+B+C=n-1$，此时 $\texttt{XX}$ 的限制一定天然满足。

此时正解已经呼之欲出了。考虑一个 dp，设 $f(i,j,0/1)$ 表示考虑到位置 $i$，已经在 $j$ 个叶子上填了 $\texttt{Y}$，当前节点是否填 $\texttt{Y}$ 能填的最多的 $\texttt{Y}$ 的个数。转移是容易的，即 $f(u,i+j,0)\leftarrow \max(f(v,i,0),f(v,i,1))+\max(f(w,j,0),f(w,j,1)),f(u,i+j,1)\leftarrow f(v,i,0)+f(w,j,0)$。然后我们分根节点是否填 $\texttt{Y}$ 讨论，方案合法当且仅当对应的根节点上的 dp 值不小于需要填的 $\texttt{Y}$ 的数量。具体数量参数可以参考代码。

复杂度分析同树形背包。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=1e4+7,inf=1e9+7;
int n,A,B,C;
vector<int>g[N];

int f[N][N][2],siz[N],tmp[N][2];

bool memed=0;

//=========================================================================================================
// Code here.

void dfs(int u){
	if((int)g[u].size()==0){
		siz[u]=1;
		f[u][0][0]=0,f[u][1][1]=1;
		return;
	}
	for(auto v:g[u])dfs(v);
	f[u][0][0]=0;f[u][0][1]=1;siz[u]=0;
	for(auto v:g[u]){
		for(int i=0;i<=siz[u];i++)
			tmp[i][0]=f[u][i][0],tmp[i][1]=f[u][i][1];
		for(int i=siz[u]+1;i<=siz[u]+siz[v];i++)
			tmp[i][0]=tmp[i][1]=-inf;
		for(int i=0;i<=siz[u];i++)
			for(int j=0;j<=siz[v];j++)
				tmp[i+j][0]=max(tmp[i+j][0],f[u][i][0]+max(f[v][j][0],f[v][j][1])),
				tmp[i+j][1]=max(tmp[i+j][1],f[u][i][1]+f[v][j][0]);
		for(int i=0;i<=siz[u]+siz[v];i++)
			f[u][i][0]=tmp[i][0],f[u][i][1]=tmp[i][1];
		siz[u]+=siz[v];
	}
}

void solve(){
	read(n,A,B,C);
	for(int i=1;i<=n;i++)g[i].clear();
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			f[i][j][0]=f[i][j][1]=-inf;
	for(int i=2,anc;i<=n;i++)
		read(anc),g[anc].eb(i);
	if(C&1)return printf("No\n"),void();
	dfs(1);
	if((0<=B-C/2&&B-C/2<=siz[1]&&f[1][B-C/2][0]>=B)||(0<=B-C/2+1&&B-C/2+1<=siz[1]&&f[1][B-C/2+1][1]>=B+1))
		printf("Yes\n");
	else printf("No\n");
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;read(T);
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

给一棵有根二叉树，根为 $1$。你需要把每个点标号为 `X`，`Y` 之一，使得对于 $n-1$ 个由父亲和儿子顺序组成的长度为 $2$ 的字符串中：

1. 有 $A$ 个 `XX`。
2. 有 $B$ 个 `XY`。
3. 有 $C$ 个 `YX`。
4. 不存在 `YY`。

保证 $A+B+C=n-1$，**保证每个点只有 $0$ 个或 $2$ 个儿子**，你只需要判断是否有解。

多测，$\sum n \leq 10^4$，时限 $3$ 秒，空间限制 $1$ GB。

解法：

考虑 `Y` 选择的必然是一个独立集。

进一步，可以发现除了根的每个 `Y` 都会对 `XY` 贡献 $1$。所以 `Y` 的数量只有可能是 $B$ 或 $B+1$。

同时，考虑 `YX` 的贡献。每个非叶子的 `Y` 都会对 `YX` 贡献 $2$，所以 $C$ 必然是偶数，必然有 $\dfrac C 2$ 个非叶子节点被选择为 `Y`。

考虑 DP，记 $f_{i,j,0/1}$ 表示点 $i$ 为根的子树，选了 $j$ 个叶子节点，$i$ 是否被选时最大独立集大小的最大值。转移是朴素的树上背包，复杂度 $O(n^2)$。

[Submission Link.](https://atcoder.jp/contests/arc157/submissions/60628641)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc157_e)

**题目大意**

> 给你一棵二叉树（儿子数 $0/2$），你需要给每个点黑白染色，使得对于 $n-1$ 条父亲到儿子的边中：
>
> 1. 有 $A$ 个黑 - 黑。
> 2. 有 $B$ 个黑 - 白。
> 3. 有 $C$ 个白 - 黑。
> 4. 没有白 - 白。
>
> 数据范围：$n\le 10^4$。

**思路分析**

首先所有白色都是独立集，因此有 $B/B+1$ 个白点（根据根的颜色决定）。

并且每个白点对 $C$ 的贡献都是 $0$ 或 $2$，因此有 $\dfrac{C}2$ 个非叶节点。

因此我们要找一个独立集包含 $B$ 个点和 $B-\dfrac C2$ 个叶子，或者 $B+1$ 个点和 $B-\dfrac C2+1$ 个叶子。

那么我们可以 dp，设 $f_{u,i}$  表示 $u$ 子树选 $i$ 个叶子，独立集最大是多少，转移直接树形背包。

时间复杂度：$\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e4+5;
vector <int> G[MAXN];
int dp[MAXN][5005][2],tmp[5005][2],siz[MAXN];
//select leaves, cur state, max no-leaf
void upd(int &x,int y) { x=x<y?y:x; }
void dfs(int u) {
	if(G[u].empty()) return siz[u]=1,dp[u][0][0]=0,dp[u][1][1]=1,void();
	dp[u][0][0]=0,dp[u][0][1]=1;
	for(int v:G[u]) {
		dfs(v);
		memset(tmp,-0x3f,sizeof(tmp));
		for(int i=0;i<=siz[u];++i) for(int j=0;j<=siz[v];++j) {
			upd(tmp[i+j][0],dp[u][i][0]+max(dp[v][j][0],dp[v][j][1]));
			upd(tmp[i+j][1],dp[u][i][1]+dp[v][j][0]);
		}
		memcpy(dp[u],tmp,sizeof(dp[u]));
		siz[u]+=siz[v];
	}
}
void solve() {
	int n,a,b,c;
	scanf("%d%d%d%d",&n,&a,&b,&c);
	for(int i=1;i<=n;++i) memset(dp[i],-0x3f,sizeof(dp[i])),G[i].clear(),siz[i]=0;
	for(int u=2,v;u<=n;++u) scanf("%d",&v),G[v].push_back(u);
	if(c&1) return puts("No"),void();
	dfs(1);
	auto in=[&](int x) { return 0<=x&&x<=siz[1]; };
	if(in(b-c/2)&&dp[1][b-c/2][0]>=b) return puts("Yes"),void();
	if(in(b-c/2+1)&&dp[1][b-c/2+1][1]>=b+1) return puts("Yes"),void();
	puts("No");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

虚高 *2800，如果放模拟赛的话人均场切了。

发现不存在两个 `Y` 的情况，分类讨论其他几种有关 `Y` 的情况：

- 对于 `YX`，在发现这个东西的数量对应一个不为叶子节点的 `Y` 节点的数量的子节点的数量的和。

- 对于 `XY`，在发现这个东西的数量对应不为根节点的 `Y` 节点的数量。

仔细看原题体面，得知这棵树是一棵二叉树，所以每个非根节点的儿子数量都为 $2$。

分类讨论根节点是否为 `Y`，可以发现叶子节点为 `Y` 的数量可以为 $b-\frac{c}{2}$ 或 $b-\frac{c}{2}+1$ 个，然后问题转化为在树上选出固定数量个叶子和非叶子节点问题。

直接设状态 $dp1_{i,j}$ 表示节点 $i$ 的子树中选了 $j$ 个叶子节点，$i$ 是 `Y` 的情况下能选多少非叶子节点，$dp0_{i,j}$ 表示节点 $i$ 的子树中选了 $j$ 个叶子节点，$i$ 不是 `Y` 的情况下能选多少非叶子节点，设 $v$ 为 $i$ 的儿子节点，得到转移如下：

$$dp1_{i,j+k}=\max (dp1_{i,j}+dp0_{v,k})$$

$$dp0_{i,j+k}=\max (dp0_{i,j}+\max(dp0_{v,k},dp1_{v,k}))$$

其中 $j\in [0,siz_{i}]$，$k\in [0,siz_{v}]$。

$siz_{x}$ 表示以 $x$ 为根的子树大小。

最后判断即可。


### $\text{code}$

```cpp
int n,a,b,c;

int head[maxn],tot;
struct edge{
	int to,nxt;
}e[maxn<<1];

int siz[maxn];

vector<int> son[maxn];

int dp0[maxn][maxn],dp1[maxn][maxn];

void add(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	head[u]=tot;
}

void init(){
	for(int i=1;i<=n;i++){
		son[i].clear();
		siz[i]=0;
	}
	for(int i=1;i<=n;i++){
		head[i]=0;
	}
	tot=0;
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			son[u].push_back(v);
			dfs(v,u);
		}
	}
}

void dfs1(int u,int fa){
	siz[u]=0;
	if(son[u].size()){
		dp0[u][0]=0;
		dp1[u][0]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v!=fa){
				dfs1(v,u);
				for(int j=siz[u]+1;j<=siz[u]+siz[v];j++){
					dp0[u][j]=-inf;
					dp1[u][j]=-inf;
				}
				for(int j=siz[u];j>=0;j--){
					for(int k=siz[v];k>=0;k--){
						dp1[u][j+k]=max(dp1[u][j+k],dp1[u][j]+dp0[v][k]);
						dp0[u][j+k]=max(dp0[u][j+k],dp0[u][j]+max(dp0[v][k],dp1[v][k]));
					}
				}
				siz[u]=siz[u]+siz[v];
			}
		}
	}
	else{
		siz[u]=1;
		dp0[u][0]=0;
		dp0[u][1]=-inf;
		dp1[u][1]=0;
		dp1[u][0]=-inf;
		return ;
	}
}

void solve(){
	init();
	n=read(),a=read(),b=read(),c=read();
	for(int i=2;i<=n;i++){
		int x=read();
		add(x,i);
	}
	dfs(1,0);
	dfs1(1,0);
	
	if(c&1){
		puts("No");
		return ;
	}
	else{
		if((0<=b-c/2&&b-c/2<=siz[1]&&dp0[1][b-c/2]>=c/2)||(0<=b-c/2+1&&b-c/2+1<=siz[1]&&dp1[1][b-c/2+1]>=c/2)){
			puts("Yes");
			return ;
		}
		else{
			puts("No");
			return ;
		}
	}
	return ;
}

```

---

## 作者：WRuperD (赞：0)

虚高 *2800，如果放模拟赛的话人均场切了。

首先，这题的关键点这是一颗 **二叉树** 洛谷没有翻译出来。![/wul](https://www.emojiall.com/images/60/qq/1f926.gif)

读一下题目容易发现有一个不存在父亲和儿子同时是 Y 这个很强的限制。这启发了我们去看有关于 Y 的限制。发现给你了个什么 YX 的数量，这是什么？这个显然是非叶子节点的 Y 的数量的两倍。再看 XY 的数量是什么，这个也显然是非根节点 Y 的数量的两倍。知道了这些性质，再分类讨论一下根节点是否是 Y 你就知道了叶子节点上 Y 的个数了！

现在整道题的限制只剩下两个了,一个是在非叶子节点放置 Y 的数量和在叶子节点放置 Y 的数量。由于这题只是让你验证是否有解而非计数，所以你设 $f_{u,j,0/1}$ 表示在节点 $u$ 子树中选了 $j$ 个叶子为 Y，有没有选择当前节点时最多选择多少个非叶子节点放 Y。直接转移即可。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/arc157/submissions/49673088)

---

