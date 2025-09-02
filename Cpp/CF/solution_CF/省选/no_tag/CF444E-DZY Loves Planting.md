# DZY Loves Planting

## 题目描述

给出一个 $n$ 个点的带边权的树。  
定义 $g(x,y)$ 为 $x, y$ 两点路径上权值最大边的权值，并且如果 $x=y$ 则 $g(x,y)=0$ 。  
对于一个长度为 $n$ 的序列 $P=\{p_1,p_2, \dots , p_n\},(1 \leq p_i \leq n)$ ，定义 $f(P)=\min\limits_{i=1}^n g(i,p_i)$。  
如果一个序列 $P$ 是合法的，当且仅当元素 $j$ 在序列 $P$ 中出现的次数不超过 $x_j$ 次。  
求所有合法的序列 $P$ 中， $f(P)$ 的最大值。

## 样例 #1

### 输入

```
4
1 2 1
2 3 2
3 4 3
1
1
1
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1
2 3 2
3 4 3
4
4
4
4
```

### 输出

```
3
```

# 题解

## 作者：蒟蒻初音ミク (赞：7)

# $CF444E \ DZY \ Loves \ Planting$

首先，这道题的一个非常明显的思路就是：二分答案+网络流 $or$ 二分图带权匹配验证。

~~听说正解就是这个。。~~

但是这里我们不需要这么高级的算法。

## $Sol$::并查集

这种问题并查集能干什么？？？

$ans$::用于维护两个联通块的点之间的路径的极值。

怎么维护呢？？我们就把边按照权值从小到大排序，然后从小到大枚举边，那么对于我们枚举的边，他两边的点如果要联通，必须走这个边，而他们路径上的其他的边的边权都是<=这个边的（因为我们排了序），所以这两个联通块的点之间的路径最大值就是这个边的权值。

对于这道题，完全可以不用二分，只需要把边从小到大排序，看一下每一个边能否作为答案就行了，即一边维护一边验证。

设$size[a]$表示$a$的联通块的大小，$sum$为所有$x[i]$的和，$val[a]$表示$a$的联通块中$x[i]$的和。

然后对于一条边来说，如果这条边可以成为答案，那么对于当前已经合并的每个点，我们都需要给它分配一个未被合并的点(注意这里边权是已经排好序的)，即可以成为的条件为：

## $size[a] \leq sum-val[a]$

蒟蒻可能讲地不太好，如果有问题可以私信哦~~~

## code：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define re register
#define int long long
#define N 100000

inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}

struct bian{
	int u,v,w;
}e[N+10];

inline bool mmp(bian a,bian b){return a.w<b.w;}

int fa[N+10],size[N+10],val[N+10],n,sum;

inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

signed main()
{
	n=read();
	for(re int i=1;i<n;++i)
	{
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	}
	for(re int i=1;i<=n;++i)val[i]=read(),sum+=val[i];
	for(re int i=1;i<=n;++i)fa[i]=i,size[i]=1;
	sort(e+1,e+n,mmp);
	for(re int i=1;i<n;++i)
	{
		int fx=find(e[i].u),fy=find(e[i].v);
		fa[fx]=fy;size[fy]+=size[fx];val[fy]+=val[fx];
		if(size[fy]>sum-val[fy]){printf("%lld\n",e[i].w);return 0;}
	}
	printf("%lld\n",e[n-1].w);
	return 0;
}
```

---

## 作者：Star_Cried (赞：1)

## CF444E DZY Loves Planting

### 题意简述

为每一个点配对另一个点，使得所有配对的点对必然经过至少一条权值大于等于$ans$的边。每个点被选为其他点配对点的次数有限且为$x_i$。求出$ans$的最大值。

#### 一些废话

这个题是在我模拟赛时考的，我独立做出来的紫题数量+1~

然而模拟赛WA了后面两个点，但是我觉得我的做法没错，然后交了原题AC了……于是发现是对于模拟赛的数据我空间开小了。幸好做法没错。

### 思路

想到了把边按照权值排序从大到小删除边，但是我太菜了写不了并查集，所以决定二分$ans$然后每次dfs检查。（复杂度凭空多个$\log$不过无伤大雅）

那么怎么检查呢？

考虑对于每一条边权大于$ans$的边，实际上把整棵树分成了若干个连通块。考虑对于一个连通块内的点数$siz_x$，只要满足其他连通块内的$x$值的和不小于它，那么就一定会有一种配对方法使得这个连通块内的点被配对。然后我们进行拓展，发现只要对于分割成的所有连通块都满足这个条件那么此时就一定有解，可以把答案上调。

### 具体实现

> 因为是模拟赛时写的，所以实现方式可能有一点麻烦。不过为了完整保留自己做题时的经历我决定放出我做时的代码。（并且请您忽略我代码中写的乱七八糟的思路过程）

从根dfs的时候将每一个边权大于答案的子节点作为一个新分出的连通块，并把dfs的所有数据更新到这个节点上。只要有一个连通块不符条件就判false。

原题不用全开longlong，也不用把空间开的那么大。（但是我不改了）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#define int long long
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
typedef long long ll;
//二分答案
/*
分成了若干个连通块？
如果每次二分之后dfs一边，向上转移时每次遇到一个合法边扩大一次边界，
反向考虑，什么情况下会无解？
对于每一个子树，若外部sum大于siz，先上转移时
等等。。。每个子树内sum都大于等于siz就OK？
非。。。？然后最后到外面的时候判断sum大于外面的siz就行。 
oh得再加个res为内部消耗之后能得到的最小siz和外面比较。 
试试嘛owo
false了，非得分成连通块不可。对于一个连通块，只要满足和其他连通块的sum大于自身siz就行。
连通块怎么做。。。用树吗，把每一个深搜的顶部节点作为连通块端点，每次回去的时候判断。 
诶嘿样例过了开心owo 
sum可能会爆int 
*/ 
namespace star
{
	const int maxn=2e5+10;
	int n,m;
	int ecnt,head[maxn],nxt[maxn<<1],to[maxn<<1],v[maxn],mid;
	inline void addedge(int a,int b,int c){
		to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt;v[ecnt]=c;
		to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt;v[ecnt]=c;
	}
	int siz[maxn],fsiz[maxn];
	ll sum[maxn],fsum[maxn];
	void dfs(int x,int f){
		siz[x]=1;
		for(int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(u==f)continue;
			dfs(u,x);
			siz[x]+=siz[u];
			sum[x]+=sum[u];
		}
	}
	bool ok;
	void dfs1(int x,int top,int fa){
		for(int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(u==fa)continue;
			if(v[i]>=mid)
				dfs1(u,u,x),fsiz[top]-=siz[u],fsum[top]+=sum[u];
			else dfs1(u,top,x);
		}
		if(x==top){
			if((sum[1]-sum[x])+fsum[x]<1LL*fsiz[x])ok=0;
		}
	}
	inline bool check(){
		ok=1;
		memcpy(fsiz,siz,sizeof fsiz);
		memset(fsum,0,sizeof fsum);
		dfs1(1,1,1);
		return ok;
	}
	inline void work(){
		n=read();
		int l=0,r=0,ans=0;
		for(int a,b,c,i=1;i<n;i++)a=read(),b=read(),c=read(),r=max(r,c),addedge(a,b,c);
		for(int i=1;i<=n;i++)sum[i]=read();
		dfs(1,1);
		while(l<=r){
			mid=l+r>>1;
			if(check())ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld",ans);
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：Arghariza (赞：0)

考虑二分答案 $v$，相当于每个 $(i,p_i)$ 的路径都需要经过 $\ge v$ 的边。

仅保留 $<v$ 的边，那么每个 $(i,p_i)$ 在不同连通块中。这是一个二分图匹配问题。

根据 Hall 定理，相当于每个连通块点数 $\le$ 连通块外的 $x$ 之和，对每个连通块 check 一遍即可。

可以去掉二分，从小到大枚举答案。用并查集动态合并连通块，不难发现每次合并需要的 check 是 $O(1)$ 的。

复杂度 $O(n\log n+\alpha n)$，换成基于值域的排序算法可以做到 $O(w+\alpha n)$。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 3e3 + 5;

int n;
int x[N];

struct E {
	
	int u, v, w;
	
	E () { }
	E (int _u, int _v, int _w) : u(_u), v(_v), w(_w) { }
	
};

vector<E> e;

struct DSU {
	
	int f[N], c[N], s[N];
	
	void init() {
		F (i, 1, n) {
			f[i] = i;
			c[i] = 1, s[i] = x[i];
		}
	}
	
	int g(int x) {
		if (x == f[x]) {
			return x;
		}
		return f[x] = g(f[x]);
	}
	
	void m(int u, int v) {
		if ((u = g(u)) == (v = g(v))) {
			return;
		}
		f[v] = u;
		s[u] += s[v], c[u] += c[v];
	}
	
	int qc(int u) {
		return c[g(u)];
	}
	
	int qs(int u) {
		return s[g(u)];
	}
	
} D;

void solve() {
	cin >> n;
	F (i, 1, n - 1) {
		int u, v, w;
		cin >> u >> v >> w;
		e.eb(E(u, v, w));
	}
	if (n == 1) {
		cout << 0 << '\n';
		return;
	}
	int sum = 0;
	F (i, 1, n) {
		cin >> x[i];
		sum += x[i];
	}
	sort(e.begin(), e.end(), [](E &x, E &y) {
		return x.w < y.w;
	});
	D.init();
	for (E p : e) {
		int u = p.u, v = p.v, w = p.w;
		D.m(u, v);
		if (D.qc(u) > sum - D.qs(u)) {
			cout << w << '\n';
			return;
		}
	}
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑枚举 $f(P)$ 的最大值 $x$，显然 $x\in w_i$。

将所有 $w_i\geq x$ 取出，不难发现一个满足要求的序列 $P$ 需要 $i$ 与 $p_i$ 之间经过至少一个取出的边。也就是说，每个连通块不能与内部的点对应。对于每个连通块求出其中所有点 $x_i$ 之和，并判断其中的点数是否小于等于其他连通块的 $x_i$ 之和即可。（否则就需要跟该连通块内的点匹配了）

总复杂度 $O(n^2)$，可以将第一步改为二分答案做到 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int p[10005];
int u[10005],v[10005],w[10005];
vector<int> vc[10005];
int siz[10005],totp[10005];
void dfs(int now,int fa){
	siz[now]=1,totp[now]=p[now];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		siz[now]+=siz[v];
		totp[now]+=totp[v]; 
	}
}
signed main(){
    int n; cin>>n;
    for(int i=1;i<n;i++){
    	cin>>u[i]>>v[i]>>w[i];
	}
	int tot=0;
	for(int i=1;i<=n;i++) cin>>p[i],tot+=p[i];
	int maxv=0;
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++) vc[j].clear(),siz[j]=totp[j]=0;
		for(int j=1;j<n;j++){
			if(w[j]<w[i]){
				vc[u[j]].push_back(v[j]);
				vc[v[j]].push_back(u[j]);
			}
		}
		bool ok=1;
		for(int j=1;j<=n;j++){
			if(!siz[j]){
				dfs(j,0);
				if(siz[j]>tot-totp[j]){
					ok=0;
				}
			}
		}
		if(ok){
			maxv=max(maxv,w[i]);
		}
	}
	cout<<maxv;
	return 0;
}
```

---

## 作者：AKPC (赞：0)

二分典题。

>构造一个长度为 $n$ 的 $p$ 序列，使得 $\min\limits_{i=1}^n g(i\to p_i)$ 最大，输出这个最大值，其中 $g(u\to v)$ 表示 $u\to v$ 唯一简单路径上经过的最大边权。

求最小值最大，很显然可以二分答案。

每次检查答案 $mid$ 是否合法时，考虑把边权 $\geq mid$ 的边全部删掉。剩下的连通块中连的边的边权 $<mid$，所以若此时两个点 $u,v$ 在同一连通块内，说明 $g(u\to v)<mid$。判连通块可以使用并查集。

显然，检查答案时，需要让每对 $i,p_i$ 互不在同一连通块内才能保证答案 $\geq mid$。维护每个连通块的大小 $siz$ 以及除连通块以外所有节点的 $x$ 值之和，记为 $sum$。容易发现 $siz$ 记录的是需要匹配的节点个数，$sum$ 则是能够选择的对应节点个数，直接判断每个连通块的 $sum\leq siz$ 是否成立即可。

发现答案一定是某一条边的边权，所以可以改成对边排序后二分哪条边作为答案，时间复杂度 $\Theta(n\log n\alpha(n))$。

---

