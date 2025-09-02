# Black, White and Grey Tree

## 题目描述

You are given a tree with each vertex coloured white, black or grey. You can remove elements from the tree by selecting a subset of vertices in a single connected component and removing them and their adjacent edges from the graph. The only restriction is that you are not allowed to select a subset containing a white and a black vertex at once.

What is the minimum number of removals necessary to remove all vertices from the tree?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1442E/5c7fc65a67c993efea0c5b8d456685a03459e620.png)

In the first test case, both vertices are white, so you can remove them at the same time.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1442E/7fcb0fe30316c209a4dd5c5ea57299d9714ea871.png)

In the second test case, three operations are enough. First, we need to remove both black vertices (2 and 4), then separately remove vertices 1 and 3. We can't remove them together because they end up in different connectivity components after vertex 2 is removed.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1442E/a704bd67a9d5c0bd1cf54c65c7d130fa609e7e75.png)

In the third test case, we can remove vertices 1, 2, 3, 4 at the same time, because three of them are white and one is grey. After that, we can remove vertex 5.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1442E/67b7bb063d112a8f54a5b9ef736683e86b82ea81.png)

In the fourth test case, three operations are enough. One of the ways to solve the problem is to remove all black vertices at once, then remove white vertex 7, and finally, remove connected white vertices 1 and 3.

## 样例 #1

### 输入

```
4
2
1 1
1 2
4
1 2 1 2
1 2
2 3
3 4
5
1 1 0 1 2
1 2
2 3
3 4
3 5
8
1 2 1 2 2 2 1 2
1 3
2 3
3 4
4 5
5 6
5 7
5 8```

### 输出

```
1
3
2
3```

# 题解

## 作者：Rainbow_qwq (赞：13)

- [CF1442E Black, White and Grey Tree](https://www.luogu.com.cn/problem/CF1442E)

---

有趣的思维题，需要发现一些性质：

首先，所有连在一起，颜色一样的点都可以一起删。

然后，如果树只有黑和白 ，那么可以有这样一个贪心的策略：

首先对于所有边，如果两边的点颜色相同看做边权为 $0$ ，不同则为 $1$ ，那么求一下直径 $len$ 。

直径上的点是黑白相间的，贪心从直径的两头开始删，删掉次数 $=\lceil \frac{len}{2} \rceil +1$

然后如果有灰点，就要给灰点染成 黑/白 ，使直径长度最小。

考虑 DP，类似求树的直径，设 $f(u,1/2)$ 表示 $u$ 染成白/黑，子树中某个点离它最大的距离，$g(u,1/2)$ 表示 $u$ 染成白/黑 经过 $u$ 的答案。

转移从儿子 $v$ 合并：

$f(u,j)=\max(f(u,j),\min(f(v,k)+(j\neq k)))$

$g(u,j)=\max(g(u,j),\min(f(u,j)+f(v,k)+(j\neq k)))$

$answer=\max(\min(g(u,1/2)))$

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define maxn 200005
int n,m,res;
struct edge{
	int to,nxt;
}e[maxn<<1];
int tot,head[maxn];
inline void adde(int u,int v){
	e[++tot]=(edge){v,head[u]};
	head[u]=tot;
}
#define inf 0x3f3f3f3f
int a[maxn],f[maxn][3],g[maxn][3];
// f[i][1/2] : u为1/2的最大儿子链 
// g[i][1/2] : u为1/2的答案 
void dfs(int u,int pa)
{
	int c=a[u];
	if(c)f[u][c^3]=g[u][c^3]=inf,
		f[u][c]=0,g[u][c]=-inf;
	else f[u][1]=f[u][2]=0,g[u][1]=g[u][2]=-inf;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==pa)continue;
		dfs(v,u);
		For(j,1,2)
		{
			if(c+j==3)continue;
			int tf=inf,tg=inf;
			For(k,1,2){
				if(f[v][k]==inf)continue;
				tf=min(tf,f[v][k]+(j!=k));
				tg=min(tg,f[u][j]+f[v][k]+(j!=k));
			}
			f[u][j]=max(f[u][j],tf);
			g[u][j]=max(g[u][j],tg);
		}
	}
	res=max(res,min(g[u][1],g[u][2]));
}
void work()
{
	n=read();tot=1;
	For(i,1,n)head[i]=0,a[i]=read();
	For(i,2,n){
		int u=read(),v=read();
		adde(u,v),adde(v,u);
	}
	res=0;
	dfs(1,0);
	printf("%d\n",(res+1)/2+1);
}

signed main()
{
	int T=read();
	while(T--)work();
    return 0;
}
```

~~为什么我总觉的这个 dp 有漏洞啊，有人来hack一下吗（~~

---

## 作者：duyi (赞：8)

# CF1442E Black, White and Grey Tree

首先，我们把相邻的同色点缩起来，因为它们显然可以一起操作。

考虑树是一条链，且无灰点的时候。因为已经缩点，所以整条链一定是黑白相间。设链的长度为 $k$（节点数量），则答案为 $\lfloor\frac{k}{2}\rfloor + 1$。有两种方式可以达到这个答案：

1. 策略一：先把出现次数较多（出现 $\lceil\frac{k}{2}\rceil$ 次）的颜色，用一个操作删掉。然后剩下 $\lfloor\frac{k}{2}\rfloor$ 个同色连通块，可以逐个删掉。
2. 策略二：先用一次操作，把链两端的点删掉（如果链长度是偶数则只删其中一端）。然后链的两端颜色一定相同，此时每次删掉两端的点（即两个叶子）。

考虑树不是一条链，且无灰点的时候。把上述两种策略扩展到这种情况：

1. 策略一：先把整棵树里出现次数较多的颜色全部删掉。然后逐个连通块删去。
2. 策略二：选择一种颜色作为起始颜色（可以暴力把黑、白都尝试一下）。删掉这种颜色的所有叶子。再删掉另一种颜色的所有叶子。如此轮换。

发现策略一的答案上界是 $\lfloor\frac{\text{点数}}{2}\rfloor + 1$，而策略二的答案仅为 $\lfloor\frac{\text{直径长度}}{2}\rfloor + 1$。显然策略二是更优的。可以证明，不存在更优的策略。

再考虑有灰点的情况，问题相当于，我们要给每个灰点选择一种颜色（黑或白），使得再次缩点后直径长度最短。考虑执行上述贪心（策略二）的过程，如果遇到当前的叶子 $u$，它的父亲 $fa(u)$ 是灰色的，且删去 $u$ 后 $fa(u)$ 就会变成叶子（即 $u$ 是 $fa(u)$ 的最后一个儿子）。此时我们直接令 $fa(u)$ 和 $u$ 同色即可。

时间复杂度 $O(n)$。

参考代码：

```cpp
// problem: CF1442E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 2e5;
int n, a[MAXN + 5];
pii e[MAXN + 5];

int fa[MAXN + 5], sz[MAXN + 5];
int get_fa(int u) { return (fa[u] == u) ? u : (fa[u] = get_fa(fa[u])); }
void unite(int u, int v) {
	u = get_fa(u); v = get_fa(v);
	if (u != v) {
		if (sz[u] > sz[v])
			swap(u, v);
		fa[u] = v;
		sz[v] += sz[u];
	}
}

struct EDGE { int nxt, to; } edge[MAXN * 2 + 5];
int head[MAXN + 5], tot;
inline void add_edge(int u, int v) { edge[++tot].nxt = head[u]; edge[tot].to = v; head[u] = tot; }

bool vis[MAXN + 5];
int _deg[MAXN + 5], deg[MAXN + 5];
int leaves[MAXN + 5], cnt_leaf;
int work(int c) {
	cnt_leaf = 0;
	for (int i = 1; i <= n; ++i) {
		vis[i] = 0;
		deg[i] = _deg[i];
		if (deg[i] <= 1) {
			leaves[++cnt_leaf] = i;
			vis[i] = 1;
		}
	}
	int res = 0;
	while (cnt_leaf) {
		res++;
		queue<int> q;
		for (int i = 1; i <= cnt_leaf; ++i) {
			int u = leaves[i];
			if (a[u] == 0 || a[u] == c) {
				q.push(u);
				if (i != cnt_leaf) {
					swap(leaves[i], leaves[cnt_leaf]);
				}
				--cnt_leaf;
				--i;
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				if (vis[v])
					continue;
				deg[v]--;
				if (deg[v] <= 1) {
					vis[v] = 1;
					if ((a[v] == 0 || a[v] == c)) {
						q.push(v);
					} else {
						leaves[++cnt_leaf] = v;
					}
				}
			}
		}
		c = 3 - c;
	}
	return res;
}
void solve_case() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		fa[i] = i;
		sz[i] = 1;
		head[i] = 0;
		_deg[i] = 0;
	}
	tot = 0;
	
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		if (a[u] == a[v])
			unite(u, v);
		e[i] = mk(u, v);
	}
	for (int i = 1; i < n; ++i) {
		int u = e[i].fi, v = e[i].se;
		u = get_fa(u);
		v = get_fa(v);
		if (u != v) {
			add_edge(u, v);
			add_edge(v, u);
			_deg[u]++;
			_deg[v]++;
		}
	}
	int ans = n;
	for (int i = 1; i <= 2; ++i) {
		ckmin(ans, work(i));
	}
	// cerr << "**********************" << endl;
	cout << ans << endl;
}
int main() {
	int T; cin >> T; while (T--) {
		solve_case();
	}
	return 0;
}
```





---

## 作者：do_while_true (赞：6)

~~怎么题解都是清一色的 dp 啊~~

我们需要做的是，从简单的情景出发，找到性质。

不难想到的是，相邻的同色节点可以合并到一起，因为如果无论何种最优操作，总是可以将这个同色连通块里的点删除延后，和连通块中最晚删除的那个点一起删除。

考虑合并同色节点后若得到了一条黑白相间的长度为 $m$ 的链，通过归纳法证明其最少操作次数为 $\left \lfloor\frac{m}{2}\right \rfloor+1$．

我口胡的归纳方法是按照奇偶性进行一个分类讨论，不知道有没有更简便的方法：假设长度为 $n$ 的链，删去了 $k$ 个点，剩余的连通块大小为 $b_1,b_2,\cdots$．

- $n=1,2$：显然成立。
- $n$ 为偶数：
  - 链的两端不能同时被选，因为它们不同色。
  - 链只有其中一端被选，剩下 $k$ 个连通块，它们大小一定都是奇数，则答案是 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\sum\frac{b_i+1}{2}=1+\frac{\sum(b_i+1)}{2}=1+\frac{n-k+k}{2}=\frac{n}{2}+1$．
  - 链两端都没有被选，剩下 $(k+1)$ 个连通块，连通块大小是 $k$ 个奇数，$1$ 个偶数，那么答案是 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\frac{\sum (b_i+1+[b_i\bmod 2=0])}{2}=1+\frac{n-k+(k+1)+1}{2}=\frac{n}{2}+2$．
- $n$ 为奇数：
  - 链的两端同时被选，剩下 $(k-1)$ 个连通块，大小一定都是奇数，答案为 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\sum\frac{b_i+1}{2}=1+\frac{\sum(b_i+1)}{2}=1+\frac{n-k+(k-1)}{2}=\frac{n-1}{2}+1$．
  - 链只有一端被选，剩下 $k$ 个连通块，连通块大小 $(k-1)$ 个奇数，$1$ 个偶数，答案为 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\frac{\sum (b_i+1+[b_i\bmod 2=0])}{2}=1+\frac{n-k+k+1}{2}=\frac{n+1}{2}+1$．
  - 链两端都没有被选，剩下 $(k+1)$ 个连通块：
    - 选择的颜色和链端点颜色相同，连通块大小 $(k-1)$ 个奇数，$2$ 个偶数，答案为 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\frac{\sum (b_i+1+[b_i\bmod 2=0])}{2}=1+\frac{n-k+(k+1)+2}{2}=\frac{n+3}{2}+1$．
    - 选择的颜色和链端点颜色不同，连通块大小 $(k+1)$ 个奇数，答案为 $1+\sum \left(\left\lfloor\frac{b_i}{2}\right\rfloor+1\right)=1+\sum\frac{b_i+1}{2}=1+\frac{\sum(b_i+1)}{2}=1+\frac{n-k+(k+1)}{2}=\frac{n+1}{2}+1$．

无论 $n$ 是偶数还是奇数，尽可能的选两端都可以达到 $\left\lfloor\frac{n}{2}\right\rfloor+1$ 的答案下界，也就是其最优方案之一是每次从两端删除叶子（异色则只删一个）。

现在考虑缩同色点后是一棵树的情况，但并不包含灰色点。那么找出树的直径，其大小为 $k$，根据上述结论，至少需要 $(\left\lfloor\frac{k}{2}\right\rfloor+1)$ 次操作，由于直径可能存在多个，而直径长度是奇数的话必须选择直径端点的颜色删除才能得到这个下界。由于树的直径的中点一定重合，所以这些直径的端点一定是同一颜色。那么每次选择直径两段的颜色，对这个颜色尽可能地删叶子，即为最优方案。

现在有了灰色，不确定其应该和黑色一起删还是和白色一起删，选择和不同的颜色的一起删可能会带来不同的直径长度。

大部分题解的处理方法是 dp，我这里的方法是贪心。

根据上述证明，最优操作一定是每次不断地剥叶子，能剥就剥。而每次尽可能地剥完黑色（及灰色）之后，不能再选择黑色剥，只能选择白色剥。所以选择的颜色一定是黑白交替的。如果没有灰色，可以直接通过直径端点确定剥哪个更优。

现在有了灰色，不知道先剥哪个颜色更优，但是一定是黑白交替剥。所以黑色打头阵和白色打头阵两种情况都算一遍，取一个最优的答案即可。具体实现方法即为拓扑排序。

时间复杂度 $\mathcal{O}(n)$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
//0 Gray
//1 white
//2 black
const int N=200010;
int n,fa[N],ans,sum;
int a[N],d[N],eu[N],ev[N];
vi eg[N];
queue<int>q[3];
#define relax(i) do{\
	int x=q[i].front();q[i].pop();\
	for(auto v:eg[x]){\
		--d[v];\
		if(d[v]==1)\
			q[a[v]].push(v);\
	}\
}while(0)
void solve(){
	read(n);ans=N;sum=0;
	for(int i=1;i<=n;i++)fa[i]=d[i]=a[i]=0,vi().swap(eg[i]);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1,x,y;i<n;i++){
		read(x,y);eu[i]=x,ev[i]=y;
		eg[x].pb(y);eg[y].pb(x);
		++d[x];++d[y];
	}
	for(int i=1;i<=n;i++)
		if(d[i]<=1){
			q[a[i]].push(i);
		}
	int fl=1;
	while(!(q[0].empty() && q[1].empty() && q[2].empty())){
		while(!(q[0].empty() && q[fl].empty())){
			if(!q[0].empty())relax(0);
			if(!q[fl].empty())relax(fl);
		}
		++sum;
		fl=3-fl;
	}
	cmin(ans,sum);
	sum=0;
	for(int i=1;i<=n;i++)d[i]=0;
	for(int i=1;i<n;i++){
		++d[eu[i]];++d[ev[i]];
	}
	for(int i=1;i<=n;i++)
		if(d[i]<=1){
			q[a[i]].push(i);
		}
	fl=2;
	while(!(q[0].empty() && q[1].empty() && q[2].empty())){
		while(!(q[0].empty() && q[fl].empty())){
			if(!q[0].empty())relax(0);
			if(!q[fl].empty())relax(fl);
		}
		++sum;
		fl=3-fl;
	}
	cmin(ans,sum);
	cout << ans << '\n';
	return ;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	int T;read(T);
	while(T--){
		solve();
//		cerr << "-----------------------\n";
	}
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18733014)

应该是一个没人写的做法。

# 思路

显然对于一个仅由白点或仅由黑点构成的连通块均可以被一次操作给消除，考虑将所有仅有一种颜色的连通块先缩成一个点。

接着发掘一下灰点的性质，发现若一个灰点连接了多个黑色连通块，那么这些黑色连通块都可以在一次操作中全部消除掉。于是我们将这些由同一个灰点连接的所有同色连通块全部缩成一个点。

注意到灰点对操作次数毫无影响，因此此时直接删除灰点即可，那么现在我们得到了一个节点颜色黑白相间的一棵树。

令此时这棵树的直径为 $L$，则容易证明答案为 $\lfloor \frac{L}{2} \rfloor + 1$。考虑如下证明：

> 根据直径的定义，直径一定是树上最长的一条链，因此我们消除直径上的点的过程中一定可以将直径上的点挂着的点全部删掉。此时只需计算删除直径所需的操作次数是多少即可。（下文中的点数均为仅保留直径的点数）
> 1. 若 $L \equiv 1 \pmod 2$，则直径两端点的颜色相同，每次删除直径的端点即可，操作次数为 $\lfloor \frac{L}{2} \rfloor + 1$。接下来证明不可能有答案比 $\lfloor \frac{L}{2} \rfloor + 1$ 小，考虑上述构造答案的方式，若有另一种构造答案的方式则必定是在一次操作中删掉了三个点，那么必定会将直径拆成了两个连通块，并且这两个连通块大小均为奇数，则最终必定会剩下单独的一个节点次数将会多消耗一次操作，但是若我们不选择拆成两个连通块则不会多这一步。由此得证！
> 2. 若 $L \equiv 0 \pmod 2$，则直径两段颜色不同，我们先随便删掉任意一个直径端点，然后直径长度变成了一个偶数，由此得到答案为 $\lfloor \frac{L}{2} \rfloor + 1$。其余证明与 $L \equiv 1 \pmod 2$ 类似，不再细说。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define chmax(a,b) (a = max(a,b))
 
using namespace std;
 
typedef pair<int,int> pii;
const int N = 2e5 + 10,M = N * 2;
int n; bool vis[N];
int rt,arr[N],f[N],dep[N];
vector<int> g[N],v[N],E[N];
 
inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}
 
inline int find(int x){
    if (f[x] == x) return f[x];
    else return f[x] = find(f[x]);
}
 
inline void merge(int a,int b){
    int x = find(a),y = find(b);
    if (x != y) f[x] = y;
}
 
inline void dfs(int u,int fa){
    dep[u] = dep[fa] + (bool)(arr[u]);
    if (dep[rt] < dep[u]) rt = u;
    for (int v:g[u]){
        if (v != fa) dfs(v,u);
    }
}
 
inline void solve(){
    n = read(); rt = 0;
    fill(dep + 1,dep + n + 1,0);
    fill(vis + 1,vis + n + 1,false);
    for (re int i = 1;i <= n;i++){
        g[i].clear(); v[i].clear(); E[i].clear();
    }
    for (re int i = 1;i <= n;i++) arr[f[i] = i] = read();
    for (re int i = 1,a,b;i < n;i++){
        a = read(),b = read();
        E[a].push_back(b);
        E[b].push_back(a);
        if (arr[a] == arr[b]) merge(a,b);
    }
    for (re int i = 1;i <= n;i++) v[find(i)].push_back(i);
    for (re int i = 1;i <= n;i++){
        if (!arr[i] && !vis[i]){
            vector<int> a,b;
            for (int u:v[find(i)]){
                vis[u] = true;
                for (int v:E[u]){
                    if (arr[v] == 1) a.push_back(v);
                    else if (arr[v] == 2) b.push_back(v);
                }
            }
            for (re int i = 1;i < a.size();i++) merge(a[i - 1],a[i]);
            for (re int i = 1;i < b.size();i++) merge(b[i - 1],b[i]);
        }
    } fill(vis + 1,vis + n + 1,false);
    for (re int i = 1;i <= n;i++){
        if (!arr[i] && !vis[i]){
            vector<int> a,b;
            for (int u:v[find(i)]){
                vis[u] = true;
                for (int v:E[u]){
                    if (arr[v] == 1) a.push_back(v);
                    else if (arr[v] == 2) b.push_back(v);
                }
            }
            if (!a.empty()){
                int x = find(i),y = find(a.front());
                g[x].push_back(y); g[y].push_back(x);
            }
            if (!b.empty()){
                int x = find(i),y = find(b.front());
                g[x].push_back(y); g[y].push_back(x);
            }
        }
    }
    for (re int u = 1;u <= n;u++){
        if (!arr[u]) continue;
        for (int v:E[u]){
            if (!arr[v]) continue;
            int x = find(u),y = find(v);
            if (x != y) g[x].push_back(y);
        }
    }
    for (re int i = 1;i <= n;i++){
        if (!g[i].empty()){
            dfs(i,0); dfs(rt,0);
            break;
        }
    }
    int Max = 0;
    for (re int i = 1;i <= n;i++) chmax(Max,dep[i]);
    printf("%d\n",Max / 2 + 1);
}
 
int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：hegm (赞：3)

好题一道。

首先我们先考虑链子如何处理。

容易发现在链子上，我们同色相邻可以缩起来答案不变，因此我们现在处理的是相邻之间颜色不同的序列。

考虑灰色如何处理，我们不妨将灰色的策略定死，当最后一个和灰色相邻的点被删除的时候，我们顺便删除灰色。

那么显然，灰色存在与否完全不影响，因此我们可以直接把整个序列缩减成仅剩下黑色和白色的情况，问当前情况下的最小花费。

显然答案就是 $\left\lfloor\dfrac{len}{2}\right\rfloor$ 其中 $len$ 为序列长度。

考虑我们以何种策略可以完成这一步，

1. 一口气删掉颜色较多的一种，剩余的颜色一个一个删。

2. 每次删链子两侧即可。

我们不妨先把方案保留，现在着眼于树上。

首先树上我们依然可以如法炮制上面的大致思路。

先将同颜色段合并，然后考虑在树上灰色节点的效果是什么。

我们发现在树上的时候灰色节点就不太好删除了，那么我们不妨直接考虑答案。

我们的删除方案 $1$ 的答案在树上效果为 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 其中 $n$ 为节点数。

而反观删除方案 $2$ 我们将树上的直径提溜出来，将灰色节点忽略，我们就会发现答案为 $\left\lfloor\dfrac{len}{2}\right\rfloor$ 其中 $len$ 为树直径长度。那么毋庸置疑我们 $2$ 方案优于 $1$ 方案。同时我们可以归纳出 $2$ 方案绝对是最优解。

那么回首看我们的灰色节点如何处理，我们容易发现灰色节点其实只有两种选择：1.最后和白色一起删。 2.最后和黑色一起删。

那么我们可以在维护上述操作的过程中顺道处理出直径。

设 $f_{i,0/1}$  表示考虑 $i$ 子树内部，当前 $i$ 作为 白/黑 色情况下距离最远的叶子距离当前节点最小是多少。

转移就考虑当前节点的颜色如果和上一个节点颜色不同，那么答案 $+1$，灰色节点可以自由选择颜色。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define inf 1000000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int T,n,a[N],f[N][4],g[N][4],ans;
vector<int> v[N];
void dfs(int now,int fa)
{
	f[now][a[now]^1]=inf;
	g[now][a[now]^1]=inf;
	for(int x:v[now])
	{
		if(x==fa)continue;
		dfs(x,now);
		for(int j=0;j<2;j++)
		{
			if(a[now]==(j^1))continue;
			int pos=min(f[x][j],f[x][j^1]+1);
			g[now][j]=max(g[now][j],f[now][j]+pos);
			f[now][j]=max(f[now][j],pos);
		}
	}
	ans=max(ans,min(g[now][0],g[now][1]));
}
signed main()
{
	T=read();
	while(T--)
	{
		n=read();ans=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=2-read();
			v[i].clear();
			f[i][0]=f[i][1]=1;
			g[i][0]=g[i][1]=1;
		}
		for(int i=1,a,b;i<n;i++)
		{
			a=read();b=read();
			v[a].push_back(b);
			v[b].push_back(a);
		}
		dfs(1,0);
		cout<<(ans+1)/2<<"\n";
	}
	return 0;
}
```

---

## 作者：Gao_yc (赞：2)

# Solution：

一种完全不需要 dp 的做法。

发现对于所有的同色连通块，一定能同时删去，故考虑用并查集进行缩点。

如果不存在灰色点，发现缩点后得到一个黑白相间的树，如果把树中一个点拎起来作为根，每个深度中都是同色的，发现按深度从深至浅删除一定符合条件。

所以只要找到树中的一个点使得最大深度最小即可，容易证明这个最大的深度是树直径长度的一半。

而如果存在灰色点，灰色点一定是与黑或白点一起删去。故考虑进行拆点，将灰点拆为一个黑点与一个白点相连，并拆出的黑点连黑点，拆出的白点连白点。（如果这个灰点只连向黑点或白点，则不进行拆点，直接作为这个颜色的点）

处理完灰点，再次进行同色缩点后，则又转化为黑白相间的树，如上处理即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+10;
int n,c[N],d[N];
int cnt;
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int m;
struct edg{
    int u,v;
}e[N],e2[N];
vector<int> G[N];
int p[N][2];
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x!=y) fa[x]=y;
}
void add(int x,int y){G[x].push_back(y);G[y].push_back(x);
// printf("add %d %d\n",x,y);
}
int dep[N];
void dfs(int x,int fa,int &rt){
    // printf("dep[%d]=%d\n",x,dep[x]);
    if(dep[rt]<dep[x]) rt=x;
    for(int y:G[x]){
        if(y==fa) continue;
        dep[y]=dep[x]+1;
        dfs(y,x,rt);
    }
}
int rt,ed;
int main(){
    scanf("%d",&n);cnt=n;
    for(int i=1;i<=n;++i) scanf("%d",c+i),fa[i]=i;
    for(int i=1;i<n;++i){
        scanf("%d%d",&e[i].u,&e[i].v);
        if(c[e[i].u]==c[e[i].v]) merge(e[i].u,e[i].v);
    }
    for(int i=1;i<=n;++i)
        if(find(i)==i&&!c[i])
            c[p[i][0]=++cnt]=1,c[p[i][1]=++cnt]=2;
    for(int i=1;i<n;++i)
        if(c[e[i].u]!=c[e[i].v]){
            e[i].u=find(e[i].u),e[i].v=find(e[i].v);
            if(c[e[i].u]>c[e[i].v]) swap(e[i].u,e[i].v);
            // printf("%d %d ->  ",e[i].u,e[i].v);
            if(!c[e[i].u]) e[i].u=p[e[i].u][c[e[i].v]-1],++d[e[i].u];
            e2[++m]={e[i].u,e[i].v};
            // printf("%d %d\n",e[i].u,e[i].v);
        }
    for(int i=1;i<=n;++i)
        if(find(i)==i&&!c[i]){
            if(d[p[i][0]]) fa[p[i][0]]=p[i][0];
            if(d[p[i][1]]) fa[p[i][1]]=p[i][1];
            if(d[p[i][0]]&&d[p[i][1]])
                e2[++m]={p[i][0],p[i][1]};
        }
    for(int i=1;i<=m;++i)
        if(c[e2[i].u]==c[e2[i].v]) merge(e2[i].u,e2[i].v);
    for(int i=1;i<=m;++i)
        if(c[e2[i].u]!=c[e2[i].v]){
            e2[i].u=find(e2[i].u);e2[i].v=find(e2[i].v);
            if(!rt) rt=e2[i].u;
            add(e2[i].u,e2[i].v);
        }
    if(!rt){puts("1");return 0;}
    dep[rt]=0;dfs(rt,0,rt);
    dep[rt]=1;dfs(rt,0,ed);
    printf("%d\n",(dep[ed]>>1)+1);
    return 0;
}
```


---

## 作者：AtomAlpaca (赞：2)

发现我的 dp 方式和别人都不一样啊。当场决定发篇题解。

首先考虑没有灰点怎么做。观察样例可以很轻易得出一个错误的解法：考虑一次删掉所有白/黑点，然后依次删掉剩下的所有联通块。

但我们考虑这样一个 hack：

![](https://cdn.luogu.com.cn/upload/image_hosting/re5qp92x.png)

按照上述的做法我们至少需要删除至少四次，但实际上我们最少只需要三次就可以了。

顺着这个 hack 往下想。我们最优的策略应该是钦定某一个点为根之后，将所有链按照颜色分层，一条链层数增加当且仅当一条边的两个点颜色不同。然后从深层到浅层依次删除，令最长的一条链最短时就能够使得答案最小。不难发现这时的根节点就是树的“直径”的中点，层数为 $ \lceil \dfrac{len}{2} \rceil  + 1$。

然后考虑加入灰点。不难发现其实灰点可以视作白点和黑点的任意一种，我们只需要将 dp 求树直径的方法稍微改造一下即可。令 $f_{u,x,1/2}$ 为节点 $u$ 在颜色为 $x$ 时的第一/二长链，其中第一、第二长链没有公共边。令 $u$ 为树上 $v$ 的父亲，当 $u$ 是灰点时，分别视作黑/白点转移即可；当 $v$ 是灰点时，用 $v$ 分别为黑/白点时的最小值更新 $u$，简单分讨一下即可。具体的实现方法不是很好描述，建议参考代码。


```c++
#include <bits/stdc++.h>

const int MAX = 2e5 + 5;

int T, n, tot, ans, u, v;
int h[MAX], a[MAX], f[MAX][3][3];
struct E { int v, x; } e[MAX << 2];

void clear()
{
  tot = ans = 0;
  for (int i = 1; i <= n; ++i) { h[i] = 0; f[i][1][1] = f[i][1][2] = f[i][2][1] = f[i][2][2] = 0; }
}

void add(int u, int v)
{
  e[++tot] = {v, h[u]}; h[u] = tot;
  e[++tot] = {u, h[v]}; h[v] = tot;
}

void work(int u, int x, int v)
{
  if (v > f[u][x][1]) { f[u][x][2] = f[u][x][1]; f[u][x][1] = v; }
  else if (v > f[u][x][2]) { f[u][x][2] = v; }
}

void dfs(int u, int fa)
{
  for (int i = h[u]; i; i = e[i].x)
  {
    int v = e[i].v; if (v == fa) { continue; } dfs(v, u);
    if (a[u])
    {
      if (a[v]) { work(u, a[u], f[v][a[v]][1] + (a[u] != a[v])); }
      else { work(u, a[u], std::min(f[v][1][1] + (a[u] != 1), f[v][2][1] + (a[u] != 2))); }
    }
    else
    {
      if (a[v])
      {
        work(u, 1, f[v][a[v]][1] + (a[v] != 1));
        work(u, 2, f[v][a[v]][1] + (a[v] != 2));
      }
      else
      {
        work(u, 1, std::min(f[v][1][1], f[v][2][1] + 1));
        work(u, 2, std::min(f[v][1][1] + 1, f[v][2][1]));
      }
    }
  }
}

void solve()
{
  scanf("%d", &n);
  clear();
  for (int i = 1; i <= n; ++i) { scanf("%d", &a[i]); }
  for (int i = 1; i <  n; ++i) { scanf("%d%d", &u, &v); add(u, v); }
  dfs(1, 0);
  for (int i = 1; i <= n; ++i)
  {
    if (a[i]) { ans = std::max(ans, f[i][a[i]][1] + f[i][a[i]][2]); }
    else { ans = std::max(ans, std::min(f[i][1][1] + f[i][1][2], f[i][2][1] + f[i][2][2])); }
	}
  printf("%d\n", ((ans + 1) >> 1) + 1);
}

int main()
{
  scanf("%d", &T); while (T--) { solve(); }
}
```

---

## 作者：541forever (赞：2)

一个有趣而不那么套路的题。

首先可以发现，颜色相同的一个连通块，在一次操作中同时删去一定不劣，那么可以把颜色相同的联通块缩为一个点。考虑一棵树若只有黑白两种颜色的情况，发现可以考虑将一个点拉出来做根，每次删掉深度相同的点（容易证明他们一定同色），当这个点为直径的中点时，设直径上有 $x$ 个点，答案取最小值 $\lfloor {x\over2} \rfloor$。而当有灰色点时，问题相当于变为给一些灰色点染成黑或白两种颜色，使得最后的树的直径最小，简单树形 dp 即可，具体地，可以设 $f_{x,0/1},g_{x,0/1}$，表示当 $x$ 点为黑 / 白色时到 $x$ 的最长链的长度和直径长度，转移显然。 

[Code](https://codeforces.com/contest/1442/submission/210300048)

---

## 作者：zym113 (赞：1)

主要补充一下对结论的证明。

对于一个只含有一种颜色的连通块一定是会将其一同删去，否则此次操作没有意义。所以将所有同色连通块缩成一个点。

简化问题，先考虑一条只有黑白两色的链。我们有两种选择：
1. 先删去颜色最多的一种，然后删去另一种颜色。
2. 从两头依次一层一层地删。

对于链，两种选择的答案都是 $\lfloor \frac{len}{2} \rfloor + 1$。

考虑扩展一下，现在考虑一棵只有黑白两色的树。

对于第一种方案，其答案为黑白两种个数较小者 $+1$。

对于第二种方案，其答案为直径的点数除以 $2$ 下取整 $+1$。
对于直径是偶数，选择任意一种颜色都能在答案次数内删完。
对于直径是奇数的，只能选择直径端点的颜色删除。对于其它与直径等长的链，其位于直径外的部分，一定与一端等长，所以其端点颜色和直径一样。

显然第二种情况优于第一种情况。

接下来考虑加入灰色点。

我们将所有与同一个灰色点连边的黑白点分别缩成两个点，且将缩成的两点连边。

我们断言答案为新图的直径的点数除以 $2$ 下取整 $+1$。

首先我们能够构造一种方案使得原图与新图等价，即轮到删除与此灰点相连的黑点时，我们可以将黑点全部删掉，但保留灰点，这样就保证了之后白点依然连通，所以与新图等价。新图只有黑白两色，所以答案能取到方案二的答案。

接下来我们证明答案的下界为此答案。

显然树的答案不会比链更优。对于链，灰色点对答案没有任何影响。所以等价与证明只含黑白两色的链的答案下界。

考虑归纳，设 $L$ 为链的长度。对于 $L$ 值为 $1$ 和 $2$ 时，显然成立。

考虑现在删去了若干点，分成了 $k$ 个联通块，第 $i$ 个连通块大小为 $L_i$。


答案为：
$$
1 + \sum_{i = 1}^{k} (\lfloor \frac{L_i}{2} \rfloor + 1)
= 1 + \sum_{i = 1}^{k} \lceil \frac{L_i + 1}{2} \rceil
\geq 1 + \lceil \frac{\sum_{i = 1}^{k} (L_i + 1)}{2} \rceil
\geq 1 + \lceil \frac{L - 1}{2} \rceil
= 1 + \lfloor \frac{L}{2} \rfloor
$$

所以 $1 + \lfloor \frac{L}{2} \rfloor$ 是答案的下界得证。

---

## 作者：Sio_ (赞：0)

考虑如果没有灰色，答案会是什么。容易发现，我们选择一个点作为根，每次删掉深度最大的那些点一定一定不劣，所以答案一定是树的中心出发的最长链。     
当我们加上灰色，我们可以使用动态规划求解这个问题。我们设计状态 $f_{i,0/1}$ 表示已经考虑完节点 $i$ 的子树，节点 $i$ 的颜色是白色还是黑色。使用换根 dp 维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5,inf=1e9;
int n,a[maxn],dep[maxn];
pair<int,int> f[maxn];
vector<int> nbr[maxn];
void dfs(int cur,int fa)
{
    if(nbr[cur].size()==1&&cur!=1)
    {
        f[cur]={1,1};
        if(a[cur]==1) f[cur].second=inf;
        if(a[cur]==2) f[cur].first=inf;
        return ;
    }
    f[cur]={0,0};
    for(auto son:nbr[cur])
    {
        if(son==fa) continue;
        dfs(son,cur);
        f[cur].first=max(min(f[son].first,f[son].second+1),f[cur].first);
        f[cur].second=max(min(f[son].first+1,f[son].second),f[cur].second);
    }
    if(a[cur]==1) f[cur].second=inf;
    if(a[cur]==2) f[cur].first=inf;
}
int res;
void dfs(int cur,int fa,pair<int,int> g)
{
    dep[cur]=dep[fa]+1;
    pair<int,int> ans1={min(g.first,g.second+1),0};
    pair<int,int> ans2={min(g.first+1,g.second),0};
    for(auto son:nbr[cur])
    {
        if(son==fa) continue;
        int val=min(f[son].first,f[son].second+1);
        if(val>ans1.first) ans1.second=ans1.first,ans1.first=val;
        else if(val>ans1.second) ans1.second=val;
        val=min(f[son].first+1,f[son].second);
        if(val>ans2.first) ans2.second=ans2.first,ans2.first=val;
        else if(val>ans2.second) ans2.second=val;
    }
    if(a[cur]==2) ans1.first=ans1.second=inf;
    if(a[cur]==1) ans2.first=ans2.second=inf;
    res=min({res,ans1.first,ans2.first});
    for(auto son:nbr[cur])
    {
        if(son==fa) continue;
        pair<int,int> tmp={ans1.first,ans2.first};
        int val=min(f[son].first,f[son].second+1);
        if(val==ans1.first) tmp.first=ans1.second;
        val=min(f[son].first+1,f[son].second);
        if(val==ans2.first) tmp.second=ans2.second;
        dfs(son,cur,tmp);
    }
}
void solve()
{
    cin>>n,res=inf;
    for(int i=1;i<=n;i++) nbr[i].clear();
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,x,y;i<n;i++) cin>>x>>y,nbr[x].push_back(y),nbr[y].push_back(x);
    dfs(1,0);
    dfs(1,0,{1,1});
    cout<<res<<'\n';
}
int main()
{
    int t;
    cin>>t;
    while(t--) solve();
}
```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1442E)

手玩几组可以发现一定是从外往内一层一层删。

枚举第一次删的颜色是什么，如果叶子节点和第一次删的节点颜色不同，就补一个第一次要删的颜色作为儿子。

定义一个路径的长度是连续段的个数，则答案就是 $\lfloor\frac {d+1}2\rfloor$，$d$ 表示直径。

对于灰点，让它变成白点或黑点。

设 $f_{x,0/1}$ 表示节点 $x$，当前的点颜色为白或黑时的直径的最小值。

类似求直径树形 dp 一下即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,t,f[N][2],w[N],mk[N],g[N][2];
vector<int>p[N];
void dfs(int x,int y){
    mk[x]=1;
    if(w[x]<0){
        f[x][y]=g[x][y]=1;
        f[x][y^1]=g[x][y^1]=2;
    }else{
        if(w[x]==y)f[x][w[x]]=g[x][w[x]]=1;
        else f[x][w[x]]=g[x][w[x]]=2;
    }
    for(int i=0;i<p[x].size();i++){
        int c=p[x][i];
        if(mk[c])continue;
        dfs(c,y);
        int ans1=0,ans2=0;
        ans1=max(f[x][0],f[c][0]),ans2=max(f[x][0],f[c][1]);
        ans1=max(ans1,g[x][0]+g[c][0]-1);ans2=max(ans2,g[x][0]+g[c][1]);
        f[x][0]=min(ans1,ans2);
        ans1=ans2=0;
        ans1=max(f[x][1],f[c][0]),ans2=max(f[x][1],f[c][1]);
        ans1=max(ans1,g[x][1]+g[c][0]),ans2=max(ans2,g[x][1]+g[c][1]-1);
        f[x][1]=min(ans1,ans2);
        g[x][0]=min(max(g[x][0],g[c][0]),max(g[x][0],g[c][1]+1));
        g[x][1]=min(max(g[x][1],g[c][0]+1),max(g[x][1],g[c][1]));
    }
    mk[x]=0;
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)scanf("%lld",&w[i]),p[i].clear(),w[i]--;
        for(int i=1;i<n;i++){
            int x,y;
            scanf("%lld%lld",&x,&y);
            p[x].push_back(y);
            p[y].push_back(x);
        }
        for(int i=1;i<=n;i++)f[i][0]=f[i][1]=g[i][0]=g[i][1]=1e9;
        dfs(1,0);
        int res=min(f[1][0],f[1][1]);
        for(int i=1;i<=n;i++)f[i][0]=f[i][1]=g[i][0]=g[i][1]=1e9;
        dfs(1,1);
        res=min(res,min(f[1][0],f[1][1]));
        printf("%lld\n",(res+1)>>1);
    }
}
```


---

## 作者：ganpig (赞：0)

一种完全不需要 dp 的做法。

我们每次在黑与白中选择一种颜色，只删这种颜色或灰色的叶子结点和删去后新露出的叶子结点，直到所有叶子结点都为未被选择的那种颜色为止。每轮交替选择黑、白、黑、白……直到整棵树被删完。

为什么只能删叶子结点呢？因为如果删了非叶子结点，树就会被砍成两部分或多部分，各部分中本来可以一次删掉的结点就得分多次删掉，可能会得不偿失。

有了这个结论，拓扑排序一下，统计删的轮数即可。

第一轮选择黑色与白色得到的答案可能不同，因此两种需要分别尝试。

注意特判 $n=1$，不然会 WA on 2。

## $\text{Code}$

```cpp
#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> c(n + 1);
    std::for_each(c.begin() + 1, c.end(), [](int &x) { std::cin >> x; });
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> d(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u), d[u]++, d[v]++;
    }
    auto calc = [=](std::vector<int> deg, int col) {
        std::queue<int> zr, nx;
        for (int i = 1; i <= n; i++)
            if (deg[i] == 1)
                zr.emplace(i);
        int step = 0;
        for (; !zr.empty(); step++, col = 3 - col, std::swap(zr, nx))
            while (!zr.empty()) {
                int u = zr.front();
                zr.pop();
                if (!c[u] || c[u] == col) {
                    for (int v : g[u])
                        if (--deg[v] == 1)
                            zr.emplace(v);
                } else
                    nx.emplace(u);
            }
        return step;
    };
    std::cout << (n == 1 ? 1 : std::min(calc(d, 1), calc(d, 2))) << '\n';
}

int main() {
    int T;
    std::cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：o51gHaboTei1 (赞：0)

**sol of CF1442E** 

一眼不会树，先做链；链也不会做，先做只有黑白色的链。

一个很萌的贪心是直接合并颜色相同的节点，然后我们得到了一条黑白相间的链。

定义树上任意链长计数单位为边数。

先进行数学归纳法，我们发现链的最少操作次数是 $\lceil \frac{\text {len}}{2}\rceil + 1$，即答案下界。


通过大量手玩发现存在一种构造方法可以达到此下界：将链的中心拉出来成根，每次删所有当前深度最深的节点，显然根据二分图染色定理它们是同色的。然后删的次数就为当前树的最大深度即 $\lceil \frac{\text {len}}{2}\rceil + 1$。

考虑扩展到有灰色的链上，我们可以设一个序列 $\text{dp}_{\text x,0/1}$ 表示第 $x$ 个位置是白色或黑色时当前链最小化的最大长度（注意到使用最开始的萌萌贪心，灰色节点涂色后链又可能产生收缩），处理一下边界进行转移即可。

考虑做黑白树。我们发现上面的构造扩展到树上就会将直径代入 $\text {len}$。由于树的问题比链强容易得到这是树问题答案的下界，又由于上面的构造证明了树问题的下界可以被构造出来，所以这就是树问题的答案。

然后就是很套路地树 dp。效仿直径的求法我们维护 $\text{dp}_{\text x,0/1}$ 表示在经过贪心地压缩后，点 $\text x$ 涂白/黑向下的最长链长度，而 $\text{mx}_{\text x,0/1}$ 表示经过贪心地压缩后，点 $\text x$ 涂白/黑向下时子树内的直径长度。

转移很简单：

- $\text{dp}_{\text x,\text j} \leftarrow \max_{\text u\in \text{Son}}(\min(\text{dp}_{\text u,0}+(0\not=\text j),\text{dp}_{\text u,1} + (1 \not = \text j)))$

- $\text{mx}_{\text x,\text j} \leftarrow \max_{\text u\in \text{Son}}(dp_{x,j} + \min(\text{dp}_{\text u,0}+(0\not=\text j),\text{dp}_{\text u,1} + (1 \not = \text j)))$

时间复杂度 $O(n)$。

```cpp
/*
贪心策略：选直径中点为根，然后将深度从深往浅删。
然后正常 dp 即可。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5 , Inf = 1e9;
int n,m,head[Len],cnt,col[Len];
struct node
{
	int next,to;
}edge[Len << 1];
inline void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
int dp[Len][2],mx[Len][2],as;
void DP(int x,int f)
{
	dp[x][0] = dp[x][1] = mx[x][0] = mx[x][1] = 0;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		DP(to , x);
		for(int j = 0 ; j <= 1 ; j ++) mx[x][j] = max(mx[x][j] , min(dp[to][0] + dp[x][j] + (0 != j) , dp[to][1] + dp[x][j] + (1 != j)));
		for(int j = 0 ; j <= 1 ; j ++) dp[x][j] = max(dp[x][j] , min(dp[to][0] + (0 != j) , dp[to][1] + (1 != j)));
	}
	if(col[x] == 1) mx[x][1] = dp[x][1] = Inf;
	if(col[x] == 2) mx[x][0] = dp[x][0] = Inf; 
	as = max(as , min(mx[x][0] , mx[x][1]));
}
int main()
{
	int T;scanf("%d",&T);
	while(T --)
	{
		scanf("%d",&n);as = 0;for(int i = 1 ; i <= n ; i ++) scanf("%d",&col[i]);
		for(int i = 1 ; i < n ; i ++)
		{
			int x,y;scanf("%d %d",&x,&y);
			add(x , y) , add(y , x);
		}
		DP(1 , 0);
		printf("%d\n",(as + 1) / 2 + 1);
		for(int i = 0 ; i <= n ; i ++) head[i] = 0;
		cnt = 0;
	}
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 分析

类似 `CF1089D`，我们可以把相同颜色的相邻点缩在一起，缩完之后我们就没有相邻的同色点了。

不难发现，如果树没有灰色这种模棱两可的点，那么我们就有一个贪心：因为直径肯定是黑白相间的，所以从直径的两头开始删颜色相同的点，次数为 $\lfloor \dfrac{len}2 \rfloor + 1$

现在考虑如果有灰色点的情况，就尝试把它染成黑色或者白色来变成上面的情况。

接下来考虑 `dp`。令 $f(u, c)
$ 表示 $u$ 染成颜色 $c$ 时子树的某个点离它最大的距离（这里的距离定义为经过边的权值和，边 $u, v$ 的权值为 $[u \neq v]$），$g(u, c)$ 表示 $u$ 染成颜色 $c$ 时经过 $u$ 的答案。

由我们刚刚的边的权值定义，得到 $f(u, c) = \max(\{\min{f(v, t) + [c \neq t]\}, t \in \{1, 2\}, v \in sons[u]})$

于是就能得到 $g(u, c) = \max(\{\min\{f(u, j) + f(v, t) + [j != t]\}, t \in \{1, 2\}, v in sons[u]\})$

而因为是从直径两端开始染色，所以答案为 $\max\{\min\{g(u, 0), g(u, 1)\}, u \in V\}$

## 代码

```cpp
#include <stdio.h>
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x < y ? y : x; }
const int N = 200010;
const int inf = 0x3f3f3f3f;
struct edge {
    int to, nxt;
} es[N << 1];
int head[N], ecnt;
inline void addedge(int u, int v) {
    es[++ ecnt] = (edge){v, head[u]};
    head[u] = ecnt;
}
int T, n, ans;
int a[N];
int f[N][3], g[N][3];
inline void dfs(int u, int fa) {
    if (a[u]) {
        f[u][3 - a[u]] = inf;
        g[u][3 - a[u]] = inf;
        f[u][a[u]] = 0;
        g[u][a[u]] = -inf;
    } else {
        f[u][1] = f[u][2] = 0;
        g[u][1] = g[u][2] = -inf;
    }
    for (int e = head[u], v; v = es[e].to, e; e = es[e].nxt)
        if (v != fa) {
            dfs(v, u);
            for (int j = 1; j <= 2; ++ j)
                if (a[u] != 3 - j) {
                    int t1 = inf, t2 = inf;
                    for (int k = 1; k <= 2; ++ k) {
                        t1 = min(t1, f[v][k] + (j != k));
                        t2 = min(t2, f[u][j] + f[v][k] + (j != k));
                    }
                    f[u][j] = max(f[u][j], t1);
                    g[u][j] = max(g[u][j], t2);
                }
        }
    ans = max(ans, min(g[u][1], g[u][2]));
}
int main() {
//  freopen("B_test.in", "r", stdin);
    scanf("%d", &T);
    for (; T --; ) {
        scanf("%d", &n);
        ecnt = 1;
        for (int i = 1; i <= n; ++ i) head[i] = 0;
        for (int i = 1; i <= n; ++ i) scanf("%d", a + i);
        for (int i = 1, u, v; i < n; ++ i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        ans = 0;
        dfs(1, 0);
        printf("%d\n", (ans + 1) / 2 + 1);
    }
}
```

---

## 作者：chlchl (赞：0)

## 题意
给定一棵染了灰、白、黑色的树，每次可以选择若干个可以相互连通的点，但不能同时含有黑白两色。一次操作定义为将选择的点全部删去。问最少几次可以删除全部的点。

## 做法
本题为一道树形 DP。

我们先不考虑灰点。若只有黑白两色，那最少删除次数必定为 $\lceil\frac{d}{2}\rceil +1$（$d$ 为树的直径）。

简单的证明：将同色的点视为一个极大的点（缩点）。这样，我们得到了一棵相邻节点必定异色的树。此时，我们不停地在直径上删掉与某一端同色的所有叶节点。
1. 如果 $d\equiv 1\pmod 2$，那么每次会将直径两端的点都删掉，删 $\lceil\frac{d}{2}\rceil +1$ 次就没点了（比直径小的必定在某次删除中被当成叶子节点删掉了）。
2. 如果 $d\equiv 0\pmod 2$，删掉一端就成了第一种情况，答案依然是 $\lceil\frac{d}{2}\rceil+1$。

关于树的直径，这里不再赘述，有需要的请自行学习树形 DP 求直径。

构造：**不需要缩点**，只需要将同色点边权设为 $0$，异色点边权设为 $1$，就可以求出缩点后树的直径。

现在，我们加入灰点。如果你真正理解了上面的思路，那灰点的处理并不难。所有的灰点，无非跟着黑、白一起删除。而这个删除的过程必定是当它成为了叶节点后与其他叶节点一起删除的。所以，我们只需要考虑灰点到底跟着哪种颜色一起删除，即它到底染上黑色还是白色。

想要在较低复杂度内求出这个问题，树形 DP 无疑是最好的选择。我们设 $f1_{u,1/2}$ 为若将 $u$ 染上白色、黑色后离其最远的节点到 $u$ 的距离（讲人话，$u$ 能到达的最远的地方）。这个是不一样的，因为染上黑白两色边权是会变的。但是，有了这个我们还不能求出答案，我们还需要求出经过 $u$ 的直径长，才能统计出最少删除次数。所以，我们加多一个 $f2_{u,1/2}$ 表示经过 $u$ 的最短直径长度。

接下来重点讲讲转移。

设 $u$ 的所有出边为 $v_1,v_2,\cdots,v_k$。$f$ 数组的转移很好求，
$f1_{u,i}=\max_{col=1}^{2}\{f1_{{v_j},col}+w_{u,v_j}\}$（$col$ 为 $v$ 的颜色）。讲人话，离 $u$ 最远的就是离 $v_i$ 最远的加上 $u\rightarrow v$ 这条边的权值。

因为我们希望次数尽量少，所以在 $v_j$ 中取**最小值**。

$f2$ 数组与求直径相似，即经过 $u$ 的最长路径加上经过 $v_i$ 的最长路径及 $u\rightarrow v$ 的权值。我们也得到了 $f2$ 的递推式：$f2_{u,i}=\max_{col=1}^{2}\{f1_{u,i}+f1_{v_j,col}+w_{u,v}\}$。

同样，我们求的是最小次数，所以在所有 $v_j$ 中取**最小值**。

最后的答案就是 $\lceil\dfrac{\max_{u=1}^{n}\{\min(f2_{u,1},f2_{u,2})\}}{2}\rceil+1$，即所有点染黑色或白色的答案 $\div 2$ 向上取整再 $+1$。

## 代码
实现还是有点难度的，给个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 10;
int T, n, ans, col[N];
int f1[N][3], f2[N][3];
vector<int> g[N];
 
void dfs(int u, int fa){
	if(col[u])	f1[u][col[u] ^ 3] = f2[u][col[u] ^ 3] = 1e9, f1[u][col[u]] = 0, f2[u][col[u]] = -1e9;//初始化 
	else	f1[u][1] = f1[u][2] = 0, f2[u][1] = f2[u][2] = -1e9;//灰点
	for(int v: g[u]){
		if(v == fa)	continue;
		dfs(v, u);
		for(int i=1;i<=2;i++){//u 染成什么颜色 
			if(col[u] + i == 3)	continue;//黑白都出现了
			int mnf = 1e9, mng = 1e9;//u被染成了i，mnf求所有路径最小值，mng则记录最小直径
			for(int j=1;j<=2;j++){//v 染成什么颜色
				mnf = min(mnf, f1[v][j] + (i != j));//儿子染成了j，那就从它的状态加上边权转移过来 
				mng = min(mng, f1[u][i] + f1[v][j] + (i != j));
			}
			f1[u][i] = max(f1[u][i], mnf);//这个跟上面同理 
			f2[u][i] = max(f2[u][i], mng);//v这个儿子的最小直径不一定是整棵树的直径，所以取 max 才能求出真正直径 
		}
	}
	ans = max(ans, min(f2[u][1], f2[u][2]));//答案与两种颜色的较小值取最大值
}

int main(){
    scanf("%d", &T);
    while(T--){
    	ans = 0;//记得清零 
        for(int i=1;i<=n;i++)    g[i].clear();//记得清空 
        scanf("%d", &n);
        for(int i=1;i<=n;i++)    scanf("%d", &col[i]);
        for(int i=1;i<n;i++){
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v), g[v].push_back(u); 
        }
        dfs(1, 0);
        printf("%d\n", ((ans + 1) >> 1) + 1);//输出答案 
    }
    return 0;
}

```


---

