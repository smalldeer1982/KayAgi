# [ARC048D] たこ焼き屋とQ人の高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc048/tasks/arc048_d

AtCoder市には $ 1 $ から $ N $ までの番号のついた $ N $ 個の町があり、それらは $ N-1 $ 本の双方向に通行可能な距離 $ 1 $ の道路によって結ばれています。 どの町からどの町へも、いくつかの道を経由してたどり着くことが出来ます。

AtCoder市には高橋君が $ Q $ 人おり、$ i $ 人目の高橋君は町 $ s_i $ から町 $ t_i $ に行きたいです。

AtCoder市のいくつかの町にはたこ焼き屋があります。高橋君たちはみな、$ 2 $ 秒間に距離 $ 1 $ 進む速度で歩きますが、たこ焼き屋のある町でたこ焼きを食べたあとは歩く速度が $ 1 $ 秒間に距離 $ 1 $ 進む速度になります。 また高橋君たちはみな小食なので、たこ焼きを複数回食べることはしません。もちろん、たこ焼き屋のある町をたこ焼きを食べずに通過することは可能です。 また、たこ焼きを食べずに町 $ t_i $ に到着してもかまいません。

AtCoder市の町の接続関係が与えられるので、 $ Q $ 人の高橋君すべてに対し、最適に行動したときの町 $ s_i $ から町 $ t_i $への移動に費やされる時間の最小値を求めてください。 高橋君たちはみなたこ焼きのプロなので、たこ焼きを食べるのにかかる時間は無視できるものとします。

## 说明/提示

### Sample Explanation 1

最初のクエリでは、町 $ 1,2,4,5 $ を順に訪れる場合が最善となります。 $ 2 $ 番目のクエリでは、町 $ 1,2,3,2,4,5,6,7 $ と順に訪れ、途中町 $ 3 $ のたこ焼き屋に寄る場合が最善となります。

## 样例 #1

### 输入

```
7 4
1 2
2 3
2 4
4 5
5 6
6 7
0010000
1 5
1 7
6 1
3 3```

### 输出

```
6
9
8
0```

## 样例 #2

### 输入

```
5 2
3 2
2 4
1 4
2 5
00000
1 5
2 3```

### 输出

```
6
2```

## 样例 #3

### 输入

```
12 10
1 2
2 3
2 4
10 12
1 5
3 11
5 6
9 10
5 7
3 9
8 7
000100100010
1 2
1 4
8 3
6 12
12 8
8 12
6 8
8 6
1 12
5 12```

### 输出

```
2
4
6
11
14
9
5
4
9
9```

# 题解

## 作者：jucason_xu (赞：4)

_阅读这篇题解前，你需要了解：任意求最近公共祖先的方法，树上倍增，换根 dp 树上最短路计算。_

对于本题，我们很明显可以把路径拆分成两个部分。假设我们从 $x$ 到 $y$，经过的第一个章鱼烧是 $w$，那么路径的总长度就是 $2\cdot dist_{x,w}+dist_{w,y}$。

我们不考虑章鱼烧的最短路，就是 $x\rightarrow lca_{x,y}\rightarrow y$。而现在我们需要吃一个章鱼烧，假设是 $w$，那么考虑 $x\rightarrow y$ 的路径和 $x\rightarrow w$ 的最后一个重合的位置 $t$，路径总长度：

 $$2\cdot dist_{x,t}+2\cdot dist_{t,w}+dist_{w,t}+dist_{t,y}$$ 

 $$=2\cdot dist_{x,t}+3\cdot dist_{t,w}+dist_{t,y}$$ 

现在，我们尝试把这一系列 $dist_{a,b}$ 转化成深度之间的关系。

__注：下文所述的“链”是不包含头尾的__

#### 我是分隔符一号 分类讨论第一种情况

我们分类讨论 $t$。

 $t$ 在链 $x\rightarrow lca_{x,y}$ 上。那么， 
 $$2\cdot dist_{x,t}=2\cdot dep_{x}-2\cdot dep_{t}$$ 
 
 $$dist_{t,y}=dep_{t}-2\cdot dep_{lca_{x,y}}+dep_{y}$$ 
 
 总长度是：
 
 $$2\cdot dep_{x}-dep_{t}-2\cdot dep_{lca_{x,y}}+dep_{y}+3\cdot dist_{t,w}$$
 
 我们发现，这整个式子中，只有 $-dep_{t}+3\cdot dist_{t,w}$ 和 $t$ 有关。而和 $w$ 有关的只有 $3\cdot dist_{t,w}$。
 
 那么，我们就应当贪心的选择距离 $t$ 最近的 $w$，则我们可以把贡献拆分成两部分：只和 $t$ 有关、只和 $x,y$ 有关。
 
#### 我是分隔符二号 下面介绍下一种情况
 
 $t$ 在链 $lca_{x,y}\rightarrow y$ 上。那么，
 
 $$2\cdot dist_{x,t}=2\cdot dep_{x}-4\cdot dep_{lca_{x,y}}+2\cdot dep_{t}$$ 
 
 $$dist_{t,y}=dep_{y}-dep_{t}$$ 
 
 总长度是 
 
 $$2\cdot dep_{x}+dep_{t}-4\cdot dep_{lca_{x,y}}+dep_{y}+3\cdot dist_{t,w}$$ 
 
 我们发现，整个式子中，只有 $dep_{t}+3\cdot dist_{t,w}$ 和 $t$ 有关，同样可以贪心选择离 $t$ 最近的 $w$。
 
 贡献依旧拆成了两部分，并且和 $t$ 有关部分只有 $dep_{t}$ 的符号不同。
 
#### 我是分隔符三号 下面介绍下一种情况

 $t$ 是 $lca_{x,y}$，长度就是 
 $$2\cdot dep_{x}-2\cdot dep_{t}+3\cdot dist_{t,w}-dep_{t}+dep_{y}$$
 
#### 我是分隔符四号 下面介绍下一种情况

 $t$ 是 $x$，长度是 
 $$dep_{x}-2\cdot dep_{lca_{x,y}}+dep_{y}+3\cdot dist_{t,w}$$
 
#### 我是分隔符五号 我认为下一种情况就是在水字数

 $t$ 是 $y$，都已经到 $y$ 了，再去吃章鱼烧还有什么意义呢？
 
#### 我是分隔符六号 下面介绍预处理内容

 四种情况都需要 $dist_{t,w}$，并且 $w$ 的选择只和 $dist_{t,w}$，我们很明显可以对于每个 $t$ 都选择距离它最近的 $w$。
 
 考虑预处理每个节点到距离它最近的有章鱼烧节点的距离最小值 $dp_{x}$ 对于有章鱼烧的点，$dp_{x}=0$，否则 $dp_{x}=\inf$。
 
 接下来我们进行 dp，首先跑一遍树形 dp 处理每个点到子树中章鱼烧最小值，然后进行一次换根 dp 得到所有的 $dp_{x}$。
 
 在这里，我们认为这种 dp 的转移和计算是基础内容，并没有进行详细介绍。
 
#### 我是分隔符七号 下面介绍正解算法

 现在，我们已经预处理出 $dp_{x}$，就可以直接 $O(1)$ 计算 $t=x$ 和 $t=lca_{x,y}$ 的情况。考虑如何计算 $t$ 在链上的情况。
 
 为了方便我们统一介绍，我们定义：$a$ 为链的最低点，$b$ 为链的最高点，选择的点 $s$ 作为 $t$ 的代价是 $cost_{s}$。在两种情况中，$cost_{s}$ 和 $x,y$ 都是无关的，也就是，我们可以预处理 $cost_{s}$。
 
 在第一种情况中，$cost_{1,s}=-dep_t+3\cdot dist_{t,w}$ 
 
 在第二种情况中，$cost_{2,s}=dep_t+3\cdot dist_{t,w}$ 
 
 接下来考虑树上倍增，$f_{1,x,y}$ 表示从 $x$ 的第 $1$ 级祖先到第 $2^y$ 级祖先中，最小的 $cost_1$。$f_{2,x,y}$ 的定义同理。
 
 每次计算的时候，通过倍增分别求出 $t$ 在 $x\rightarrow lca_{x,y}$ 和 $lca_{x,y}\rightarrow y$ 的 $cost_t$ 最小值，再加上两种方法中，$x,y$ 造成的贡献。
 
 四种方法的答案取最小值，当然不要忘了不吃章鱼烧的情况，也就是 $2\cdot(dep_x+dep_y-2\cdot dep_{lca_{x,y}})$。
 
 我们就可以在 $O(n\log n)$ 的时间内预处理，在 $O(q\log n)$ 的时间内查询，以 $O((n+q)\log n)$ 的复杂度做出了这道题。
 
#### 我是分隔符8号 下面展示美丽的代码

```cpp
using namespace std;
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define st string
#define vt vector
#define pb push_back
#define int long long
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
vt<int>vv[100005];
int fa[100005][22],ls[100005],dep[100005],exi[100005];
int f1[100005][22],f2[100005][22];
int dp[100005];
inline void dfs1(int x,int p){
	if(exi[x])dp[x]=0;
	else dp[x]=1e9;
	for(auto j:vv[x])if(j!=p){
		dfs1(j,x);
		dp[x]=min(dp[x],dp[j]+1);
	}
}
inline void dfs2(int x,int p){
	dp[x]=min(dp[x],dp[p]+1);
	for(auto j:vv[x])if(j!=p)dfs2(j,x);
}
inline void dfs(int x,int p){
	fa[x][0]=p,dep[x]=dep[p]+1;
	f1[x][0]=3*dp[p]-dep[p];
	f2[x][0]=3*dp[p]+dep[p];
	rep(j,1,20)fa[x][j]=fa[fa[x][j-1]][j-1];
	rep(j,1,20)f1[x][j]=min(f1[x][j-1],f1[fa[x][j-1]][j-1]);
	rep(j,1,20)f2[x][j]=min(f2[x][j-1],f2[fa[x][j-1]][j-1]);
	for(auto j:vv[x])if(j!=p){
		dfs(j,x);
	}
}
inline int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	per(j,0,20)if(dep[fa[x][j]]>=dep[y])x=fa[x][j];
	if(x==y)return x;
	per(j,0,20)if(fa[x][j]!=fa[y][j])x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}
inline int val(int x,int y){
	int z=lca(x,y),dis=dep[x]+dep[y]-2*dep[z],ans=2*dis,p=x;
	ans=min(ans,3*dp[x]+dis);
	per(j,0,20)if(dep[fa[p][j]]>=dep[z]){
		ans=min(ans,dis+f1[p][j]+dep[x]);
		p=fa[p][j];
	}
	p=y;
	per(j,0,20)if(dep[fa[p][j]]>=dep[z]){
		ans=min(ans,dis+f2[p][j]-dep[z]+dep[x]-dep[z]);
		p=fa[p][j];
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,q,a,b;
	cin>>n>>q;
	rp(i,n-1){
		cin>>a>>b;
		vv[a].pb(b);
		vv[b].pb(a);
	}
	st s;
	cin>>s;dp[0]=1e9;
	rp(i,n)exi[i]=s[i-1]-'0';
	dfs1(1,0);
	dfs2(1,0);
	dfs(1,0);
	rp(i,q){
		cin>>a>>b;
		cout<<val(a,b)<<endl;
	}
	return 0;
}
//Crayan_r

```



---

## 作者：RedLycoris (赞：2)

[link](https://www.luogu.com.cn/problem/AT_arc048_d)

题目大意：

给你一棵有 $n$ ($1 \le n \le 10^5$) 个节点的树，其中一些节点是特殊节点，相邻两个点的距离为 $1$。

有 $q$ ($1 \le q \le 10^5$) 次询问，每次给你两个点 $u,v$，你需要求出从 $u$ 走到 $v$ 的最小时间。

一开始，你的速度是每 $2$ 个时间单位走 $1$ 个距离单位。假设在某一时刻你到了一个特殊节点，那么你的速度就会变为 $1$ 个时间单位走 $1$ 个距离单位，这次询问内有效。

题解：

显然有两种过程：

+ 从 $u$ 直接走到 $v$，花费时间 $2\times dist(u,v)$。

+ 从 $u$ 走到 $u,v$ 链上某个节点 $x$，再从 $x$ 走到某个特殊节点 $y$，再从 $y$ 返回 $x$，最后从 $x$ 走到 $v$。

第一种情况平凡，我们考虑第二种。

有以下结论：

+ 第二种情况下的答案 $ans=dist(u,v)+dist(u,x)+3\times dist(x,y)$

+ $y$ 一定是到 $x$ 距离最近的特殊节点。显然，因为 $y$ 只和 $3\times dist(x,y)$ 一项有关。

所以我们可以跑一遍 bfs 处理出到所有节点最近的特殊节点的距离 $\times 3$ （记为 $C(x)$） 是多少。

然后在 $u,v$ 已知的情况下，$dist(u,v)$ 容易算出，我们只需要求出 $dist(u,x)+3\times C(x)$ 的最小值就可以了。

$dist(u,x)$ 比较难算，但我们可以用一个分类讨论的套路把它拆开来：

令 $l$ 为 $u,v$ 的 LCA，进行分类：

+ $x$ 在 $u \rightarrow l$ 这条链上

此时 $dist(u,x)=deep_u-deep_x$（$deep_x$ 为节点 $x$ 的深度），所以在 $u$ 给定的情况下，我们需要求得的是 $C(x)-deep_x$ 的最小值，可以直接树剖或者倍增维护。

+ $x$ 在 $l\rightarrow v$ 这条链上

同理，不过 $dist(u,x)$ 变为 $deep_u+deep_x-2\times deep_l$，维护 $C(x)+deep_x$ 的最小值即可。

---

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=1e5+5;
string s;
int n,k,dst[mxn],top[mxn],sz[mxn],dep[mxn],ord[mxn],cc,fa[mxn],son[mxn];
int st[mxn],ed[mxn];
vector<int>g[mxn];
inline void dfs(int x,int par=1){              //树剖
	fa[x]=par;sz[x]=1;dep[x]=dep[par]+1;
	for(int y:g[x])if(y!=par){
		dfs(y,x);
		if(sz[y]>sz[son[x]])son[x]=y;
		sz[x]+=sz[y];
	}
}
inline void go(int x,int par=1,int tpf=1){
	st[x]=++cc;ord[cc]=x,top[x]=tpf;
	if(son[x]){
		go(son[x],x,tpf);
		for(int y:g[x])if(y!=par and y!=son[x])go(y,x,y);
	}
	ed[x]=cc;
}
int F1(int x){return dst[x]-dep[x];}//left
int F2(int x){return dst[x]+dep[x];}//right
struct SP{                     
	int VAL[mxn],val[mxn<<2];
	inline void build(int x,int l,int r){
		if(l==r){val[x]=VAL[ord[l]];return;}
		int md=l+r>>1;
		build(x<<1,l,md);
		build(x<<1|1,md+1,r);
		val[x]=min(val[x<<1],val[x<<1|1]);
	}
	inline int ask(int x,int l,int r,int a,int b){
		if(a<=l and r<=b)return val[x];
		if(b<l or r<a)return 1145141;
		int md=l+r>>1;
		return min(ask(x<<1,l,md,a,b),ask(x<<1|1,md+1,r,a,b));
	}
	inline void init(int (*F)(int)){
		for(int i=1;i<=n;++i)VAL[i]=F(i);
		build(1,1,n);
	}
	inline int qryRange(int x,int y){
		int ans=1145141;
		for(;top[x]!=top[y];){
			if(dep[top[x]]>dep[top[y]])swap(x,y);
			ans=min(ans,ask(1,1,n,st[top[y]],st[y]));
			y=top[y],y=fa[y];
		}
		if(dep[x]>dep[y])swap(x,y);
		ans=min(ans,ask(1,1,n,st[x],st[y]));
		return ans;
	}
	inline int lca(int x,int y){
		for(;top[x]!=top[y];){
			if(dep[top[x]]>dep[top[y]])swap(x,y);
			y=top[y],y=fa[y];
		}
		if(dep[x]>dep[y])swap(x,y);
		return x;
	}
}s1,s2;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1,u,v;i<n;++i){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);go(1);
	cin>>s;s=" "+s;queue<int>q;
	for(int i=1;i<=n;++i)dst[i]=6*n;
	for(int i=1;i<=n;++i)if(s[i]=='1')dst[i]=0,q.push(i);  //bfs
	for(;q.size();){
		int x=q.front();q.pop();
		for(int y:g[x])if(dst[y]>dst[x]+3){
			dst[y]=dst[x]+3;
			q.push(y);
		}
	}
	s1.init(F1);
	s2.init(F2);
	for(;k--;){
		int u,v,l;cin>>u>>v;
		l=s1.lca(u,v);
		cout<<dep[u]+dep[v]-2*dep[l]+min(min(dep[u]+s1.qryRange(u,l),dep[u]+s2.qryRange(l,v)-2*dep[l]),dep[u]+dep[v]-2*dep[l])<<'\n';
	}
}
```

---

## 作者：Phobia (赞：0)

~~题解区为什么全是简洁的做法，没有麻烦的三数组分类讨论的做法，深深地感到自己的弱小。~~

钦定以 $1$ 为根，先把题目中的东西转化为一下。

$$
\begin{aligned}
&2\times\operatorname{dist}(s,d)+\operatorname{dist}(d,t)\\
=\ &2\times(dep[s]+dep[d]-2\times dep[\operatorname{lca}(s,d)])+(dep[d]+dep[t]-2\times dep[\operatorname{lca}(d,t)])
\end{aligned}
$$

发现这个 $\operatorname{lca}$ 函数相当不好处理，于是考虑分类讨论。

- 当 $\operatorname{lca}(s,d)$ 在 $s\to\operatorname{lca}(s,t)$ 上时。

![](https://cdn.luogu.com.cn/upload/image_hosting/zzpgf7sl.png)

如图，此时 $\operatorname{lca}(d,t)=\operatorname{lca}(s,t)$。

则有：

$$
\begin{aligned}
\text{原式}
&=2\times(dep[s]+dep[d]-2\times dep[\operatorname{lca}(s,d)])+(dep[d]+dep[t]-2\times dep[\operatorname{lca}(s,t)])\\
&=(2\times dep[s]+dep[t]-2\times dep[\operatorname{lca}(s,t)])+(3\times dep[d]-4\times dep[\operatorname{lca}(s,d)])
\end{aligned}
$$

前面那一坨直接求，后面那一坨倍增维护即可。

- 当 $\operatorname{lca}(s,d)=\operatorname{lca}(s,t)$ 时。

![](https://cdn.luogu.com.cn/upload/image_hosting/u5rb5s9g.png)

如图，此时

$$
\begin{aligned}
\text{原式}
&=2\times(dep[s]+dep[d]-2\times dep[\operatorname{lca}(s,t)])+(dep[t]+dep[d]-2\times dep[\operatorname{lca}(d,t)])\\
&=(2\times dep[s]+dep[t]-4\times dep[\operatorname{lca}(s,t)])+(3\times dep[d]-2\times dep[\operatorname{lca}(d,t)])
\end{aligned}
$$

同上求解。

- 当 $\operatorname{lca}(s,d)$ 在 $\operatorname{lca}(s,t)\to 1$ 上时。

![](https://cdn.luogu.com.cn/upload/image_hosting/1snmvcnw.png)

如图，此时 $\operatorname{lca}(s,d)=\operatorname{lca}(d,t)$。

则有：

$$
\begin{aligned}
\text{原式}
&=2\times(dep[s]+dep[d]-2\times dep[\operatorname{lca}(s,d)])+(dep[t]+dep[d]-2\times dep[\operatorname{lca}(s,d)])\\
&=(2\times dep[s]+dep[t])+(3\times dep[d]-6\times dep[\operatorname{lca}(s,d)])
\end{aligned}
$$

同理可求。

最后别忘了 $s$ 不吃饭直接到 $t$ 这种情况。

时间复杂度 $O(n\log{n})$，空间复杂度 $O(n\log{n})$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100005, maxe = maxn * 2, maxlogn = 18, inf = 1 << 30;

int n, q, logn;

char s[maxn];

int son[maxe], nxt[maxe], lnk[maxn], tot;

int dep[maxn], f[maxn][maxlogn], w32[maxn][maxlogn], w34[maxn][maxlogn], w36[maxn][maxlogn]; // w32 表示 3*dep[d]-2*dep[lca] 的最小值，其他同理。

int read()
{
	int ret = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		;
	for (; isdigit(ch); ch = getchar())
		ret = (ret << 3) + (ret << 1) + (ch & 15);
	return ret;
}

void add_edge(int x, int y)
{
	son[++tot] = y, nxt[tot] = lnk[x], lnk[x] = tot;
	son[++tot] = x, nxt[tot] = lnk[y], lnk[y] = tot;
}

void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	if (s[u] == '1')
	{
		w32[u][0] = dep[u];
		w34[u][0] = -dep[u];
		w36[u][0] = -dep[u] * 3;
	}
	else
		w32[u][0] = w34[u][0] = w36[u][0] = inf;
	for (int i = lnk[u]; i; i = nxt[i])
	{
		int v = son[i];
		if (v == fa)
			continue;
		dfs(v, u);
		w32[u][0] = min(w32[u][0], w32[v][0] + 2);
		w34[u][0] = min(w34[u][0], w34[v][0] + 4);
		w36[u][0] = min(w36[u][0], w36[v][0] + 6);
	}
}

int lca(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = logn; i >= 0; --i)
	{
		if (dep[f[x][i]] >= dep[y])
			x = f[x][i];
	}
	if (x == y)
		return x;
	for (int i = logn; i >= 0; --i)
	{
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	}
	return f[x][0];
}

int get(int w[maxn][maxlogn], int s, int t) // 往上窜的当前节点就是 lca，因此可以倍增快速维护。
{
	int ans = inf;
	for (int i = logn; i >= 0; --i)
	{
		if (dep[f[s][i]] >= dep[t])
		{
			ans = min(ans, w[s][i]);
			s = f[s][i];
		}
	}
	return min(ans, w[s][0]);
}

int min4(int a, int b, int c, int d)
{
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	if (a > d)
		a = d;
	return a;
}

int main()
{
	n = read(), q = read(), logn = log2(n);
	for (int i = 1; i < n; ++i)
		add_edge(read(), read());
	scanf("%s", s + 1);
	dfs(1, 0);
	for (int j = 1; j <= logn; ++j)
	{
		for (int i = 1; i <= n; ++i)
		{
			f[i][j] = f[f[i][j - 1]][j - 1];
			w32[i][j] = min(w32[i][j - 1], w32[f[i][j - 1]][j - 1]);
			w34[i][j] = min(w34[i][j - 1], w34[f[i][j - 1]][j - 1]);
			w36[i][j] = min(w36[i][j - 1], w36[f[i][j - 1]][j - 1]);
		}
	}
	while (q--)
	{
		int x = read(), y = read(), l = lca(x, y);
		printf("%d\n", min4(
			(dep[x] + dep[y] - dep[l] * 2) * 2, // 不要忘了不吃饭这种情况
			get(w34, x, l) + dep[x] * 2 + dep[y] - dep[l] * 2,
			get(w32, y, l) + dep[x] * 2 + dep[y] - dep[l] * 4, 
			get(w36, l, 1) + dep[x] * 2 + dep[y])
		);
	}
	return 0;
}
```

~~我绝对不会告诉你我把章鱼烧认为成烧鸟了。~~

---

