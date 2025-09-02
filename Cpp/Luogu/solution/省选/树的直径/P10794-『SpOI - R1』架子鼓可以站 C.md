# 『SpOI - R1』架子鼓可以站 C

## 题目描述

现在有一棵 $n$ 个点的树，树根是节点 $1$。

可以对这棵树做任意次**站 C 操作**，每次**站 C 操作**为：选择树上的一个叶子结点 $x$，再选择根节点到 $x$ 路径上的一条边，删除它；然后添加一条连接 $x$ 和根节点的边。

你需要求出经过若干次**站 C 操作**后树的直径的最大值。

**注意：叶子结点的定义是不为根节点，且度数为 $1$ 的节点。**

## 说明/提示

### 样例 #1 解释

不做操作时，树的直径为 $2$。可以证明这是最大的直径。

### 样例 #2 解释

样例中的树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/23wosgfo.png)

只需要一次站 C 操作：选择叶子结点 $6$，断开 $1$ 到 $4$ 的边，再连接 $6$ 和 $1$。

这将会使树形成一条链，直径为 $6$。可以证明这是最大的直径。

### 数据范围

**请注意常数因子对程序效率的影响。**

**本题开启子任务捆绑与子任务依赖。**

对于所有数据，满足 $1\leq T\leq 10^4$，$2 \leq n \leq 2\times 10^5$，保证输入数据构成一棵树。

| Subtask | $T\leq$ | $n\leq$ | 特殊性质 | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $10^4$ | $10$ | 无 | $15$ | 无 |
| 2 | $10^4$ | $20$ | 无 | $15$ | 1 |
| 3 | $10^4$ | $90$ | 无 | $20$ | 1,2 |
| 4 | $10^4$ | $2\times 10^5$ | $A$ | $15$ | 无 |
| 5 | $15$ | $2\times 10^5$ | 无 | $35$ | 1,2,3,4 |

**特别地，对于 Subtask 4，保证 $\sum n\leq 3\times 10^6$。**

特殊性质 $A$：不存在一对 $x\neq 1\land y\neq 1$ 的 $(x,y)$ 满足 $\text{LCA}(x,y)=1$。

## 样例 #1

### 输入

```
1
3
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
1
7
1 2 1 4 4 5```

### 输出

```
6```

# 题解

## 作者：JHR100330 (赞：10)

## 题目大意

可以任意进行多次操作，每次可以选择一个叶子节点 $v$，将 $v$ 到根的简单路径中的一条边删掉，再在 $v$ 与根之间连一条边，问最终树的直径最长为多少。

## 分析

一开始本人考虑每个子树内的最长链，最后找到根节点的两个最大子树求和，但是两条链可能在同一个子树内，这也是这道题的难点。

我们分步考虑：

1. 不做操作：答案是树的直径。
1. 只进行 $1$ 次操作：选一条从叶子出发的、不经过根节点的路径，删除路径上深度最小的点的父亲边，然后将其挂在根节点的下方。再选另一条从根节点出发的路径拼成答案（注意：两条路径不能相交，否则找不到合法的可以删除的边）。
1. 进行 $2$ 次操作：等价于选择了两条不交的、且不经过根节点的路径分别挂在根节点下方，答案为选择的两条路径长度之和加上 $2$。
1. 进行 $3$ 次及以上的操作是没有意义的，因为不可能存在一条路径同时覆盖了三条新增的边。
1. 不做操作和只做一次操作的情况下，也可以认为是选择了两条不交且不经过根节点的路径。可以统一用树形 DP 来做。

![img1](https://cdn.luogu.com.cn/upload/image_hosting/g64ndtsc.png)

---

### 目标

在以 $u$ 为根的子树内，划分出两条**没有交点**的长链。

### 状态

`d[u]` 表示 $u$ 子树中端点为 $u$ 的最大链长。

`f[u]` 表示 $u$ 子树中端点任意的最大链长。

`g[u]` 表示 $u$ 子树中 $2$ 条链的最大链长和，其中 $1$ 条链端点为 $u$。

`h[u]` 表示 $u$ 子树中 $2$ 条链的最大链长和，并且 $2$ 条链端点任意。

`D[u][3]` 表示端点为儿子 $v$ 的最大、次大、三大链长。

`S[u][3]` 表示对应的三个儿子的编号。

### 状态转移

1. $u$ 子树中端点为 $u$ 的最大链长：`d[u]=max(d[u],d[v]+1)`。
2. $u$ 子树中端点任意的最大链长：
   1. 从 $v$ 子树继承：`f[u]=max(f[u],f[v])`。
   2. 经过 $u$ 点：`f[u]=max(f[u],D[u][0]+D[u][1]+2)`。

![img2](https://cdn.luogu.com.cn/upload/image_hosting/flamo871.png)

---

3. $u$ 子树中最大链长和，其中一条端点为 $u$：
   1. 从 $v$ 子树继承：`g[u]=max(g[u],g[v]+1)`。
   2. 以 $u$ 为端点不过 $v$ 的最长链与 $v$ 中的任意最长链拼凑：`g[u]=max(g[u],f[v]+(s[u][0]==v?D[u][1]:D[u][0])+1)`。

![img3](https://cdn.luogu.com.cn/upload/image_hosting/cvkxa6in.png)

---

4. $u$ 子树中最大链长和，$2$ 条链端点任意：
   1. 从 $v$ 子树继承：`h[u]=max(h[u],h[v])`。
   2. $2$ 条链来自不同子树：`h[u]=max(h[u],f1+f2)`。
   3. $1$ 条来自 $v$，$1$ 条过 $u$：`h[u]=max(h[u],f[v]+res+2)`。
   4. $1$ 条来自 $v$，$1$ 条过 $u,v$：`h[u]=max(h[u],g[v]+(S[u][0]==v?D[u][1]:D[u][0])+2)`。

![img4](https://cdn.luogu.com.cn/upload/image_hosting/c96u6i23.png)

---

5. 由于链不能经过根节点 $1$，需要对根的每个子树分别讨论并计算答案，注意加上新建的两条边的贡献：
   1. 子树之内的 $2$ 条链长和，用 `h[i]` 计算。
   2. 子树之间的 $2$ 条链长和，用 `f[i]` 拼凑。

![img5](https://cdn.luogu.com.cn/upload/image_hosting/32hiuqwl.png)

---

这道题也就迎刃而解了。

## AC Code：


```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define PII pair<int, int>
#define PLL pair<ll, ll>

const ll inf = 2e9, N = 200050, M = 2050, MOD = 1e9 + 7;

ll t, n, u, ans, mx1, mx2; 
ll d[N], f[N], g[N], h[N];
ll D[N][3], S[N][3];
vector<ll> e[N]; 

// 更新最大，次大，三大儿子 分类讨论 
void upd(ll x, ll y, ll dep){
	if(dep > D[x][0]){
		D[x][2] = D[x][1], S[x][2] = S[x][1];
		D[x][1] = D[x][0], S[x][1] = S[x][0];
		D[x][0] = dep, S[x][0] = y;
	}
	else if(dep > D[x][1]){
		D[x][2] = D[x][1], S[x][2] = S[x][1];
		D[x][1] = dep, S[x][1] = y;
	}
	else if(dep > D[x][2]) D[x][2] = dep, S[x][2] = y;
}

// 树形DP 
void dfs(ll now){
	ll f1 = 0, f2 = 0;
	for(ll i : e[now]){
		dfs(i);
		// 从v子树继承 
		d[now] = max(d[now], d[i] + 1);
		upd(now, i, d[i]);
		f[now] = max(f[now], f[i]);
		g[now] = max(g[now], g[i] + 1);
		h[now] = max(h[now], h[i]);
		// 保存两个最佳子树，便于更新h 
		if(f[i] > f1) f2 = f1, f1 = f[i];
		else if(f[i] > f2) f2 = f[i];
	}
	// 从两个最佳子树更新 
	f[now] = max(f[now], D[now][0] + D[now][1] + 2);
	h[now] = max(h[now], f1 + f2);
	// 子树遍历完后再更新 
	for(int i : e[now]){
		g[now] = max(g[now], f[i] + (S[now][0] == i ? D[now][1] : D[now][0]) + 1);
		ll res = 0, cnt = 0;
		if(S[now][0] != i) res += D[now][0], cnt ++;
		if(S[now][1] != i) res += D[now][1], cnt ++;
		if(cnt < 2 && S[now][2] != i) res += D[now][2];
		h[now] = max(h[now], f[i] + res + 2);
		h[now] = max(h[now], g[i] + (S[now][0] == i ? D[now][1] : D[now][0]) + 2);
	}
}

int main(){
	scanf("%lld", &t);
	while(t --){
		scanf("%lld", &n);
		// 记得全部清空！！！ 
		for(int i = 1; i <= n; i ++){
			e[i].clear();
			S[i][0] = S[i][1] = S[i][2] = f[i] = d[i] = h[i] = 0;
			D[i][0] = D[i][1] = D[i][2] = g[i] = -1;
		}
		for(int i = 2; i <= n; i ++){
			scanf("%lld", &u);
			e[u].push_back(i);
		}
		dfs(1);
		// 统计最大链，次大链之和与子树中的两大链的最大值作为答案 
		ans = 0; mx1 = -inf, mx2 = -inf;
		for(int i : e[1]){
			ans = max(ans, h[i] + 2);
			if(f[i] > mx1) mx2 = mx1, mx1 = f[i];
			else if(f[i] > mx2) mx2 = f[i];
		}
		if(n == 2) puts("1"); // 特判 
		else printf("%lld\n", max(ans, mx1 + mx2 + 2));
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：4)

出题人题解。

首先容易发现，操作完后的树的直径，一定经过根节点。

> 容易证明，如果直径不经过根，可以用一次操作将直径的一端操作到根上，直径长度会变长。

这个结论换句话说就是最终的直径一定来自根上的两个不同儿子的子树。于是我们可以发现进行两次以上操作没有任何意义，因为最后的答案只占用根的两个儿子子树。

然后考虑操作的本质。可以发现，我们的操作等价于选择一个子树，把它的直径挂到根上（事实上是断掉的边两端深度更深的那个点的子树的直径）。因为虽然我们把整个子树都挂过去了，但是对答案有贡献的肯定只有它本身的直径，而这个直径操作后形成了一条到根的链。

不妨考虑两次选点的位置，进行讨论：

1. 两次选点在原树上位于同一个子树 $x$ 内，那么问题就是在这个 $x$ 中断开一条边之后形成的两个部分的直径之和的最大值。很明显我们只需要考虑 $x$ 是根节点的儿子的子树的情况。
2. 两次选点在原树上位于两个子树 $x,y$，那么问题就是 $x$ 的直径和 $y$ 的直径的和的最大值。很明显我们只需要考虑 $x,y$ 是根节点的儿子的子树的情况。

第二种情况很容易，但第一种情况比较麻烦。

对于树上断一条边求最大直径和，这东西有一个树形 dp 的线性做法，还有一个基于直径可合并的线段树做法（我应该是卡了 $\log$ 的）。我自己发明了另一个做法。

考虑先求出该树的直径，若断掉一条边砍断了直径，则一定把直径变成了一个前缀和一个后缀，分出来的两个子树的直径一定有一端是原来的直径端点。证明通过刻画新直径的形态是容易的（假设新直径经过旧直径的前后缀，那么肯定转到旧直径上更长，如果不经过，那么也是转过去肯定更长）。

于是我们可以直接把直径给拉出来，其他子树挂到直径上，垒一下前后缀的距离端点最远点的距离就可以了，这是简单的。

若断掉一条边没有砍断直径，那么答案就是砍下去那个子树的直径加上原直径的长度，这个东西也可以用拉直直径容易算出。

这样就做完了。

std 用的是验题人做法：[戳这里](https://www.luogu.com.cn/article/tavb95ps)。

-----------

还有一点：我们可以证明零次操作或一次操作是不优的。

零次操作不优的证明：

> 零次操作不优，也就是最终答案一定大于原直径。显然，如果直径不经过根，直接将直径整体所在子树操作上来直径不会变短；如果直径经过根，把叉开的两边的其中一边整体操作上来，直径不会变短。  

一次操作不优的证明：

> 若根至少有两个儿子，在进行了一次操作之后，直径要么开始穿过根，要么仍然在某个子树内。对于前者，直径有一端仍然在一个未被操作过的子树内，将它操作上去直径不会变短；对于后者，将那个子树操作，直径不会变短（尽管我们似乎浪费了操作）。  
> 特别地，若根只有一个儿子，如果第一次操作没有把这唯一一个儿子的整个子树操作上来，得到的东西会和两个儿子的情况等价。而如果第一次操作把整个子树操作上来，若该子树不是所有点都在直径上，随便拉一个不在直径上的点操作都能把直径变长；若该子树所有点都在直径上，那么现在的树应该是一个链，随便操作直径都不会发生变化。

---

## 作者：是青白呀 (赞：4)

不妨逐步考虑。

- 不做操作。答案是树的直径。

- 只进行一次操作。我们肯定是要选新建的这条边的，否则此次操作没有意义。你发现这个操作等价于任选一条从叶子出发的、不经过根节点的路径，删除路径上深度最小的点的父亲边，然后将其挂在根节点的下方。那么我们需要选择另一条从根节点出发的路径拼成答案。注意两条路径不能相交，否则找不到合法的可以删除的边。

- 进行两次操作。进一步推广，这等价于你选择了两条不交的、且不经过根节点的路径，分别挂在根节点下方，答案显然为选择的两条路径长度之和 $+2$。

进一步地，你发现进行 $3$ 次及以上的操作是没有意义的，因为不可能存在一条路径同时覆盖了三条新增的边。同时，不做操作和只做一次操作的情况下，也可以认为是选择了两条不交、且不经过根节点的路径。因此原问题得到转化。

对于这个新问题，考虑树形 dp 解决。设 $dp_i$、$f_i$、$g_i$、$h_i$ 分别表示在以 $i$ 为根的子树中划分出 $1$ 条以 $i$ 为端点的链的最大链长、划分出 $2$ 条链，其中一条以 $i$ 为端点的最大链长和、划分 $1$ 条端点任意的链的最大链长、以及划分 $2$ 条端点任意的链的最大链长和。利用这四个数组进行转移是容易的。

注意由于链不能经过根节点，需要对根的每个子树分别讨论并计算答案。最后记得加上新建的两条边的贡献。复杂度不难做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e6+5,M=3e5+5,mo=998244353,inf=1e9+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n;
int T;
struct edge{
	int to,nxt;
}e[2*N];
int fir[N],np;
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
}
int dp[N],f[N],g[N],h[N];
pii maxn[N][3];
void getmax(int x,pii nw){
	if(nw.fir>maxn[x][0].fir)maxn[x][2]=maxn[x][1],maxn[x][1]=maxn[x][0],maxn[x][0]=nw;
	else if(nw.fir>maxn[x][1].fir)maxn[x][2]=maxn[x][1],maxn[x][1]=nw;
	else if(nw.fir>maxn[x][2].fir)maxn[x][2]=nw;
}
void dfs(int x,int fa){
	int mxg1=0,mxg2=0;
	for(int i=fir[x];i;i=e[i].nxt){
		int j=e[i].to;
		if(j==fa)continue;
		dfs(j,x);
		dp[x]=max(dp[x],dp[j]+1);
		getmax(x,mp(dp[j],j));
		g[x]=max(g[x],g[j]),h[x]=max(h[x],h[j]),f[x]=max(f[x],f[j]+1);
		if(g[j]>mxg1)mxg2=mxg1,mxg1=g[j];
		else if(g[j]>mxg2)mxg2=g[j];
	}
	h[x]=max(h[x],mxg1+mxg2);
	g[x]=max(g[x],maxn[x][0].fir+maxn[x][1].fir+2);
	for(int i=fir[x];i;i=e[i].nxt){
		int j=e[i].to;
		if(j==fa)continue;
		int res=0,cnt=0;
		rep(l,0,2)
		    if(cnt<2&&maxn[x][l].sec!=j)res+=maxn[x][l].fir,cnt++;
		h[x]=max(g[j]+res+2,h[x]);
		h[x]=max(h[x],f[j]+(maxn[x][0].sec==j?maxn[x][1].fir:maxn[x][0].fir)+2);
		if(maxn[x][1].sec)f[x]=max(f[x],g[j]+(maxn[x][0].sec==j?maxn[x][1].fir:maxn[x][0].fir)+1);
	}
	h[x]=max(h[x],f[x]);
}
void solve(){
	read(n); 
	rep(i,1,n)
	    fir[i]=0;
	np=0;
	rep(i,2,n){
		int x;
		read(x);
		add(x,i),add(i,x);
	}
	if(n==2){
		puts("1");
		return;
	}
	rep(i,1,n){
	    rep(j,0,2)
	        maxn[i][j]=mp(-1,0);
	    f[i]=-inf;
	    dp[i]=g[i]=h[i]=0;
	}  
	dfs(1,0);
	int ans=maxn[1][0].fir+maxn[1][1].fir+2,mx1=-1,mx2=-1;
	for(int i=fir[1];i;i=e[i].nxt){
		int j=e[i].to;
		ans=max(h[j]+2,ans);
		if(g[j]>mx1)mx2=mx1,mx1=g[j];
		else if(g[j]>mx2)mx2=g[j];
	}
	ans=max(ans,mx1+mx2+2);
	printf("%d\n",ans);
}
int main(){
	// freopen("drumset28.in","r",stdin);
	read(T);
	while(T--)
	    solve();
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：3)

我怎么又成首 A 杀手了，开始写的时候必然没首 A 写完的时候首 A 已经没了，沃日。

你容易发现一次操作都只会连到 $1$ 上面去，而观察样例容易发现我们肯定是把一个子树的直径拉上去做转移。

那么最后的答案如果动了操作那肯定就是经过 $1$ 了，这个问题变成了选一个子树使得子树内的直径和子树外的直径加和最大。（注意子树外的不能经过 $1$）

子树内的直径树形 dp 就可以了，子树外的直径换根 dp 就可以了。

读入有卡常。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define ll long long
#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
#define re(i, t) rep (i, 1, t)
#define per(i, t, f) for (int i = (t), ed##i = (f); i >= ed##i; --i)
#define ste(i, f, t, s) for (int i = (f), ed##i = (t); i <= ed##i; i += s)
#define each(i, x) for (auto& i : (x))
#define nxt(i, f, g) for (int i = g.h[f]; i; i = g.e[i].n)
#define dbg(x) (cerr << "(dbg) " << #x " = " << (x) << '\n')
#define umod(x) ((x) >= mo && ((x) -= mo))
#define dmod(x) ((x) < 0 && ((x) += mo))
#define up(x, y) (((x) < (y)) && ((x) = (y)))
#define down(x, y) (((x) > (y)) && ((x) = (y)))
#define y1 y1__
namespace FastIO {
    const int SZ=(1<<23)+1;
    struct I {
        char ibuf[SZ],*iS,*iT,c;int f,_eof;FILE*fi;
        I(FILE*f):fi(f){}
        inline char Gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SZ,fi),(iS==iT?EOF:*iS++)):*iS++;}
        inline ll operator()(){ll x;operator()(x);return x;}
        inline I&operator()(char&x){x=Gc();return*this;}
        inline I&operator()(char*s){for(c=Gc();c<32||c>126||c==' ';)c=Gc();for(;c>31&&c<127&&c!=' '&&c!='\n'&&c!='\r';++s,c=Gc())*s=c;*s=0;return*this;}
        template<class T>inline I&operator()(T&x){_eof=0;for(f=1,c=Gc();(c<'0'||c>'9')&&!_eof;c=Gc()){if(c=='-')f=-1;_eof|=c==EOF;}for(x=0;c<='9'&&c>='0'&&!_eof;c=Gc())x=x*10+(c&15),_eof|=c==EOF;x*=f;return*this;}
        template<class T>I&operator()(T*x,const int&n,const int&st=1){rep(i,st,n){operator()(x[i]);}return*this;}
    } in(stdin);
    struct O {
        char obuf[SZ],*oS=obuf,*oT=oS+SZ-1,qu[55];int f,qr;FILE*fi;
        O(FILE*f):fi(f){}
        ~O(){Flush();}
        inline void Flush(){fwrite(obuf,1,oS-obuf,fi),oS=obuf;}
        inline O&operator()(char x){*oS++=x;if(oS==oT)Flush();return*this;}
        inline O&operator()(const char*s){int len=strlen(s);for(f=0;f<len;++f)operator()(s[f]);return*this;}
        template<class T>inline O&operator()(T x){if(!x)operator()('0');if(x<0)operator()('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)operator()(qu[qr--]);return*this;}
        template<class T>O&operator()(T*x,const int&n,const char&ed=' ',const int&st=1){rep(i,st,n)operator()(x[i])(ed);return*this;}
    } out(stdout);
}
using FastIO::in;using FastIO::out;

using namespace std;
int T;
int n;
int father[200005];
vector<int> ljb[200005];
int dp[200005];
int f[200005];
int dfn[200005];
int pre[200005];
int suf[200005];

void getdp(int cur,int fa){
    f[cur]=0;
    dp[cur]=0;
    int Max=0,MMax=0;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getdp(v,cur);
        f[cur]=max(f[cur],f[v]+1);
        dp[cur]=max(dp[cur],dp[v]);
        if(f[v]+1>Max){
            MMax=Max;
            Max=f[v]+1;
        }
        else{
            if(f[v]+1>MMax){
                MMax=f[v]+1;
            }
        }
    }
    dp[cur]=max(dp[cur],MMax+Max);
    return;
}

struct node{
    int Max,MMax;
};
node cmp(node a,node b){
    node c=node{0,0};
    c.Max=max(a.Max,b.Max);
    c.MMax=max(min(a.Max,b.Max),max(a.MMax,b.MMax));
    return c;
}
int getans(int cur,int fa,int dpans,int fans){
    int neta=dp[cur]+dpans+1+(!!fa);
    vector<node> shaberpre,shabersuf;
    vector<int> dinnerpre,dinnersuf;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        shaberpre.push_back(node{f[v]+1,0});
        shabersuf.push_back(node{f[v]+1,0});
        dinnerpre.push_back(dp[v]);
        dinnersuf.push_back(dp[v]);
    }
    for(int i=1;i<ljb[cur].size();i++){
        shaberpre[i]=cmp(shaberpre[i],shaberpre[i-1]);
        dinnerpre[i]=max(dinnerpre[i],dinnerpre[i-1]);
    }
    for(int i=ljb[cur].size()-2;i>=0;i--){
        shabersuf[i]=cmp(shabersuf[i],shabersuf[i+1]);
        dinnersuf[i]=max(dinnersuf[i],dinnersuf[i+1]);
    }
    node now=node{fans+1,0};
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        node tmp=now;
        if(i)tmp=cmp(tmp,shaberpre[i-1]);
        if(i+1<ljb[cur].size())tmp=cmp(tmp,shabersuf[i+1]);
        int need=dpans;
        if(i)need=max(need,dinnerpre[i-1]);
        if(i+1<ljb[cur].size())need=max(need,dinnersuf[i+1]);
        neta=max(getans(v,cur,max(dpans,max(tmp.Max+tmp.MMax,need)),tmp.Max),neta);
    }
    return neta;
}
int main(){
    in(T);
    while(T--){
        in(n);
        for(int i=1;i<=n;i++){
            ljb[i].clear();
        }
        for(int i=2;i<=n;i++){
            in(father[i]);
            ljb[father[i]].push_back(i);
        }
        getdp(1,0);
        for(int i=0;i<ljb[1].size();i++){
            int v=ljb[1][i];
            pre[i]=dp[v]+1;
            suf[i]=dp[v]+1;
        }
        for(int i=1;i<ljb[1].size();i++){
            pre[i]=max(pre[i-1],pre[i]);
        }
        for(int i=ljb[1].size()-2;i>=0;i--){
            suf[i]=max(suf[i],suf[i+1]);
        }
        int ans=dp[1];
        for(int i=0;i<ljb[1].size();i++){
            int v=ljb[1][i];
            int tmp=0;
            if(i)tmp=max(tmp,pre[i-1]);
            if(i+1<ljb[1].size())tmp=max(tmp,suf[i+1]);
            ans=max(ans,dp[v]+1+tmp);
            ans=max(ans,getans(v,0,0,-1));
        }
        out(ans)('\n');
    }
    return 0;
}
```

---

## 作者：Richard_Whr (赞：2)

很好的题目。

首先注意到一件事，最优解重新连接的根到叶子的边一定在直径中。

否则的话你相当于没连这条边，还删了一条边，直径一定只减不增。

那么进一步，一条链中一个点的度数最多为 $2$，也就是说最多进行两次操作。

操作次数不多，分类讨论：

- $0$ 次操作：树的直径
- $1$ 次操作：选某个叶子，然后选上这个叶子不跨过根的最长链（肯定在根的某个子树里），再在其他子树里选一个以根开头的最长链
- $2$ 次操作，继续分类：

  - 不在同一个子树，和上一个差不多。
  - 在同一个子树，选两条不交的链，最大化长度和。

然后你会发现所有情况都是最后一种的特化版或泛化版，因此我们应该可以规整到一种情况。

发现这个就是选两条不包含根的，不交的链，最大化长度和.

如果您做过 [[八省联考 2018] 林克卡特树](https://www.luogu.com.cn/problem/P4383)，那这个题就是 $k=2$ 的部分分。

但是可以有更特殊的做法，考虑选的两个不交的链，一定属于两颗子树中，因此我们可以枚举断边，然后分别求出两颗子树的直径。

子树内直径很好搞，关键是子树外直径如何搞，看到子树外很自然想到换根 $dp$。

首先直径 $dp$ 先设 $g_u$ 表示最长链， $f_u$ 表示 $u$ 子树内的答案 

设 $k_u$ 表示不包含 $u$ 为根的子树的直径，考虑向儿子 $v$ 转移求出 $k_v$ 需要什么。

首先 $k_v = k_u$，这是显然的，先继承父亲子树以外的信息。

然后就是考虑 $v$ 的兄弟和以 $u$ 为根时不包含 $v$ 的直径了。

一个一个来，兄弟节点需要他们的 $\max\{f_{v'}\}$，前缀后缀一下就可以容易的处理。

最困难的是求出以 $u$ 为根，且不包含 $v$ 子树节点的直径。

发现这个直径可以由两部分贡献最长链拼合而成：兄弟方向，父亲方向。

两个方向总共出两条链即可，一个方向最多两条链，父亲方向最多一条链。

考虑直接记录儿子前三大，这样顶多一个用不了，父亲方向的 dfs 的时候下传就可以了，具体而言就是维护一个往父亲方向走的最长链，设为 $d_u$。

设 $Max_2$ 表示前两长的可用最长链，$Max_1$ 表示最长的可用最长链。

$$k_v=\max\{k_u,pre,suf,Max_2+1\}$$

$$d_v=\max\{d_u,Max_1+1\}$$

其中 $pre,suf$ 就是兄弟的 $f$ 前缀后缀 $\max$。

统计答案就比较轻松了，要么是一棵子树内的，每个点的贡献是 $f_u+k_u+2$，要么是两颗子树分别选，子树合并过程中完成即可。

有点卡常啊，看评测机状态给分。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,Inf=1e8;
vector<int> e[N];
int f[N],g[N],k[N];
int G[N][3],P[N][3]; 
vector<int> pf[N],sf[N];
int n,T,res;
namespace io{
    template <typename T> inline void read(T& x){x = 0; bool f = false; char ch = getchar(); while(ch < '0' || ch > '9'){if(ch == '-') f = !f; ch = getchar();}while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();} x = (f ? -x : x); return;}
    template <typename T, typename... Args> inline void read(T& x, Args&...x_){read(x), read(x_...);}
    template <typename T> inline void put(T x){if(x < 0) putchar('-'), x = -x; if(x > 9) put(x / 10); putchar(x % 10 + '0'); return ;}
    template <typename T> inline void write(T x){put(x);}
    template <typename T, typename... Args> inline void write(T x, Args...x_){write(x), write(x_...);}
}

inline void upd(int u,int x,int c)
{
	if(c>=G[u][0]) G[u][2]=G[u][1],P[u][2]=P[u][1],G[u][1]=G[u][0],P[u][1]=P[u][0],G[u][0]=c,P[u][0]=x;
	else if(c>=G[u][1]) G[u][2]=G[u][1],P[u][2]=P[u][1],G[u][1]=c,P[u][1]=x;
	else if(c>G[u][2]) G[u][2]=c,P[u][2]=x;
}

void dfs(int u)
{
	f[u]=0,g[u]=0,k[u]=-Inf;
	int sz=e[u].size();
	sf[u].resize(sz),pf[u].resize(sz);
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		dfs(v);
		sf[u][i]=pf[u][i]=f[v];
		upd(u,v,g[v]+1);
		f[u]=max(f[u],g[u]+g[v]+1);
		g[u]=max(g[u],g[v]+1); 
		f[u]=max(f[u],f[v]); 
	}
	
	for(int i=1;i<(int)e[u].size();i++) pf[u][i]=max(pf[u][i-1],pf[u][i]);
	for(int i=(int)e[u].size()-2;i>=0;i--) sf[u][i]=max(sf[u][i+1],sf[u][i]);
	
}

inline int Max(int u,int v,int t)
{
	int cnt=0,res=0;
	for(int i=0;i<3;i++)
	{
		if(P[u][i]==v) continue;
		res+=G[u][i],cnt++;
		if(cnt>=t) break;
	}
	return res;
} 

void dfs2(int u,int d)
{
	upd(u,0,d);
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		vector<int> vec;
		k[v]=k[u];
		if(i) k[v]=max(k[v],pf[u][i-1]);
		if(i+1<e[u].size()) k[v]=max(k[v],sf[u][i+1]);
		k[v]=max(k[v],Max(u,v,2));
		dfs2(v,Max(u,v,1)+1);
	}
	res=max(res,f[u]+k[u]+2);
}

signed main()
{
	using namespace io; 
	read(T);
	while(T--)
	{
		read(n);
		for(int i=1;i<=n;i++) e[i].clear(),memset(G[i],0,sizeof G[i]),memset(P[i],0,sizeof P[i]);
		for(int i=2,p;i<=n;i++)
		{
			read(p);
			e[p].push_back(i);
		}
		res=0;
		int maxv=-Inf;
		for(auto v:e[1])
		{
			dfs(v);
			res=max(res,maxv+f[v]+2);
			maxv=max(maxv,f[v]); 
			k[v]=-Inf;
			dfs2(v,0);
		}
		res=max(res,maxv+1);
		write(res),putchar('\n');
	}
	
	return 0;
}
```

---

