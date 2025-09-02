# Bribes

## 题目描述

Ruritania is a country with a very badly maintained road network, which is not exactly good news for lorry drivers that constantly have to do deliveries. In fact, when roads are maintained, they become one-way. It turns out that it is sometimes impossible to get from one town to another in a legal way – however, we know that all towns are reachable, though illegally!

Fortunately for us, the police tend to be very corrupt and they will allow a lorry driver to break the rules and drive in the wrong direction provided they receive ‘a small gift’. There is one patrol car for every road and they will request 1000 Ruritanian dinars when a driver drives in the wrong direction. However, being greedy, every time a patrol car notices the same driver breaking the rule, they will charge double the amount of money they requested the previous time on that particular road.

Borna is a lorry driver that managed to figure out this bribing pattern. As part of his job, he has to make $ K $ stops in some towns all over Ruritania and he has to make these stops in a certain order. There are $ N $ towns (enumerated from 1 to $ N $ ) in Ruritania and Borna’s initial location is the capital city i.e. town 1. He happens to know which ones out of the $ N-1 $ roads in Ruritania are currently unidirectional, but he is unable to compute the least amount of money he needs to prepare for bribing the police. Help Borna by providing him with an answer and you will be richly rewarded.

## 说明/提示

Borna first takes the route $ 1→5 $ and has to pay 1000 dinars. After that, he takes the route $ 5→1→2→3→4 $ and pays nothing this time. However, when he has to return via $ 4→3→2→1→5 $ , he needs to prepare 3000 (1000+2000) dinars. Afterwards, getting to 2 via $ 5→1→2 $ will cost him nothing. Finally, he doesn't even have to leave town 2 to get to 2, so there is no need to prepare any additional bribe money. Hence he has to prepare 4000 dinars in total.

## 样例 #1

### 输入

```
5
1 2 0
2 3 0
5 1 1
3 4 1
5
5 4 5 2 2
```

### 输出

```
4
```

# 题解

## 作者：ChPu437 (赞：4)

### UPD(2020/10/20):修复了题目大意的锅
---
# CF575B Bribes 题解

**题面：**[CodeForces](https://codeforces.com/problemset/problem/575/B) [洛谷](https://www.luogu.com.cn/problem/CF575B)

大意：给定一颗树，其中一些边在沿指定方向通过时会有 $2^{i-1}$ 的代价 ( $i$ 为**沿该方向**通过此边的次数 )，求沿给定路径走完全程的花费。

---

[这道题](https://www.luogu.com.cn/problem/P3258)和此题思路类似，没有做过的可以先去做做。

如果做过上面这道题的话，容易想到要用树上差分来解决这样的问题，可是这题的不同之处在于，它的边是有向的。考虑到树上差分是从**根节点**一直**向下**拓展到**叶子节点**的 ( 可以进行**统一的**维护 ) ，而且此题的费用计算是按照**沿有向边的正方向经过该边的次数**计算的 ( 不同的方向之间**没有**相互干扰 )，所以我们可以用两个差分数组，分别记录：


	1. 沿根节点到叶子节点的方向经过该边的次数
 	2. 沿叶子结点到根节点的方向经过该边的次数


然后将这两个数组下放，得到分别沿两个方向通过一条边的次数，把所有产生代价的部分统计在答案中即可。

**代码：**

```c
# include <iostream>
# include <cstdio>
# define MAXN 100005
# define MAXK 1000005
# define fa(x) nd[x].fa
# define top(x) nd[x].top
# define hSon(x) nd[x].hSon
# define siz(x) nd[x].siz
# define dep(x) nd[x].dep

const long long MOD = 1e9+7;

struct edge{
	int u, v, next;
	bool uToV; // 是否沿边的方向
}e[MAXN<<1]; int hd[MAXN], cntE;
struct node{
	int fa, top, hSon;
	int siz, dep, dfn;
}nd[MAXN];
int diffA[MAXN], diffB[MAXN];
// diffA -> 从叶子到根
// diffB -> 从根到叶子

void AddE(int u, int v, bool dire);
void PreDFS(int now, int fa);
void SegDFS(int now, int top);
int GetLCA(int x, int y);
long long QPow(long long x, long long y);
void AnsDFS(int now, int fa);

int main(){
	int n, k;

	scanf("%d", &n);

	for(int i = 1, a, b, x; i <= n-1; i++){
		scanf("%d%d%d", &a, &b, &x);
		if(x){
			AddE(a, b, 1); AddE(b, a, 0);
		}
		else{
			AddE(a, b, 0); AddE(b, a, 0);
		}
	}

	PreDFS(1, 0); SegDFS(1, 1); // 树剖 LCA

	scanf("%d", &k);

	int cur = 1; // 从根节点开始
	for(int i = 1, to, lca; i <= k; i++){
		scanf("%d", &to);
		lca = GetLCA(cur, to);
		diffA[cur]++, diffA[lca]--;
		diffB[to]++, diffB[lca]--;
		cur = to;
	}

	AnsDFS(1, 0); // 下放差分数组

	long long ans = 0;

	for(int i = 1; i <= cntE; i++){ // 统计答案
		if(e[i].uToV){
			if(dep(e[i].u) > dep(e[i].v)){
				ans = ((ans + QPow(2, diffB[e[i].u])%MOD) + MOD - 1) % MOD;
			}
			else{
				ans = ((ans + QPow(2, diffA[e[i].v])%MOD) + MOD - 1) % MOD;
			}
		}
	}

	printf("%lld", ans);

	return 0;
}

void AnsDFS(int now, int fa){
	for(int i = hd[now]; i; i = e[i].next){
		if(e[i].v == fa){
			continue;
		}
		AnsDFS(e[i].v, now);
		diffA[now] += diffA[e[i].v];
		diffB[now] += diffB[e[i].v];
	}
}

long long QPow(long long x, long long y){
	long long ans = 1, base = x % MOD;
	for(	; y; y >>= 1){
		if(y & 1){
			ans = (ans * base) % MOD;
		}
		base = (base * base) % MOD;
	}
	return ans;
}

int GetLCA(int x, int y){
	while(top(x) != top(y)){
		if(dep(top(x)) < dep(top(y))){
			std::swap(x, y);
		}
		x = fa(top(x));
	}
	return dep(x) < dep(y) ? x : y;
}

void SegDFS(int now, int top){
	top(now) = top;
	if(hSon(now)){
		SegDFS(hSon(now), top);
		for(int i = hd[now]; i; i = e[i].next){
			if(e[i].v == fa(now) || e[i].v == hSon(now)){
				continue;
			}
			SegDFS(e[i].v, e[i].v);
		}
	}
}

void PreDFS(int now, int fa){
	fa(now) = fa, siz(now) = 1, dep(now) = dep(fa) + 1;
	for(int i = hd[now]; i; i = e[i].next){
		if(e[i].v == fa){
			continue;
		}
		PreDFS(e[i].v, now);
		siz(now) += siz(e[i].v);
		if(siz(e[i].v) > siz(hSon(now))){
			hSon(now) = e[i].v;
		}
	}
}

void AddE(int u, int v, bool dire){
	e[++cntE] = (edge){u, v, hd[u], dire};
	hd[u] = cntE;
}

```


~~不要吐槽为什么用树剖求LCA~~

---

## 作者：_AyachiNene (赞：2)

# 思路：
一个很常见的套路，先把操作处理完，最后在算每条边的贡献。对于从 $s_{i-1}$ 移到 $s_i$，题目问最小花费就是句废话，直接走肯定是最优的，把向上和向下走分开讨论，树上差分就做完了。具体的，设 $p$ 为 $s_{i-1}$ 和 $s_i$ 的 Lca，把 $s_{i-1}$ 到 $p$，和 $p$ 到 $s_i$ 的路径分别插在两个差分数组里，最后算每条边的贡献即可。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
struct node
{
	int nxt,to;
}e[114514<<1];
int head[114514],cnt_edge;
void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
struct edge
{
	int u,v,op;
}tmp[114514];
int n,m;
int a[1145141];
int dep[114514],dfn[114514],son[114514],siz[114514],top[114514],f[114514],cnt;
void dfs1(int u,int fa)
{
	f[u]=fa;
	dep[u]=dep[fa]+1;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t)
{
	top[u]=t;
	dfn[u]=++cnt;
	if(son[u]) dfs2(son[u],t);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=f[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
int sum[2][114514];
void dfs3(int u)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]) continue;
		dfs3(v);
		for(int j=0;j<=1;j++) sum[j][u]+=sum[j][v];
	}
}
const int mod=1e9+7;
int Pow[1145141];
int ans;
signed main()
{
	read(n);
	for(int i=1;i<n;i++)
	{
		read(tmp[i].u,tmp[i].v,tmp[i].op);
		add_edge(tmp[i].u,tmp[i].v);add_edge(tmp[i].v,tmp[i].u);
	}
	dfs1(1,0);dfs2(1,1);
	read(m);
	for(int i=1;i<=m;i++) read(a[i]);
	a[0]=1;
	for(int i=1;i<=m;i++)
	{
		int Lca=lca(a[i],a[i-1]);
		--sum[0][Lca];++sum[0][a[i-1]];
		--sum[1][Lca];++sum[1][a[i]];
	}
	dfs3(1);
	Pow[1]=1;
	for(int i=2;i<=1e6+1;i++) Pow[i]=Pow[i-1]*2%mod;
	for(int i=1;i<=1e6+1;i++) Pow[i]=(Pow[i]+Pow[i-1])%mod;
	for(int i=1;i<n;i++)
	{
		if(!tmp[i].op) continue;
		int op=(dep[tmp[i].u]<dep[tmp[i].v])^1;
		if(op) swap(tmp[i].u,tmp[i].v);
		ans=(ans+Pow[sum[op][tmp[i].v]])%mod;
	}
	write(ans);
	flush();
}
```

---

## 作者：Ishy (赞：1)

# CF575B Bribes

[洛谷：CF575B Bribes](https://www.luogu.com.cn/problem/CF575B) 

[Codeforces：CF575B Bribes](https://codeforces.com/problemset/problem/575/B) 

## Solution

对 “有效边” 统计被反向经过的数量然后等比数列求和。

考虑一条路径 $s \to t$ 对 "有效边 $u \to v$ 是否有贡献。

- $u \to v$ 自叶向根：$s$ 不在 $u$ 子树内，$t$ 在 $u$ 子树内。
- $u \to v$ 自根向叶：$s$ 在 $u$ 子树内，$t$ 不在 $u$ 子树内。

判断在不在子树内可以用 `dfs` 序。

对每一条 “有效边”，都需要求出给定序列中满足条件的 $(s, t)$ 的数量。

考虑枚举 “有效边”，此时子树区间固定。

考虑将给定序列分成若干有向线段（线段端点位置是 `dfs` 序）。

具体地：若 $dfn_{u} < dfn_v$，自根向叶；否则自叶向根。

把正序线段称作一类线段，逆序线段称作二类线段，分别计算。

分类讨论哪些线段会对当前询问产生贡献：

- 自叶向根：询问区间为 $u$ 子树对应的区间，
  - 对于一类线段：左端点在区间左侧，右端点在区间内。
  - 对于二类线段：左端点在区间内，右端点在区间右侧。
- 自根向叶：询问区间为 $v$ 子树对应的区间，
  - 对于一类线段：左端点在区间内，右端点在区间右侧。
  - 对于二类线段：左端点在区间左侧，右端点在区间内。

需要预处理：

- 以点 $x$ 为左端点向右延伸的线段数量 $lc_x$ 
- 以点 $x$ 为右端点向左延伸的线段数量 $rc_x$ 
- 对上面两个量求前缀和数组 $lsum_x, rsum_x$ 

左端点在区间左侧，右端点在区间内的线段数量可以转为 $rsum_{r} - rsum_{l - 1} - cnt$。其中 $l, r$ 是区间端点，$cnt$ 是完全被包含在区间内的线段数量，而 $cnt$ 可以用二维数点求出来。

瓶颈在求 $cnt$，单 $\log$。

[code CF575B Bribes](https://codeforces.com/problemset/submission/575/194787946) 

 

---

## 作者：SUNCHAOYI (赞：1)

由题可知这是一棵树，因此求每一条边经过的次数可以通过树上差分解决。而现在只有部分（有向）边需要花费，因此就需要找到一种能够记录单向花费的信息。考虑到一条边连接的两个点因在树上而深度不同，所以可以分为叶子指向父节点与父节点指向叶子两种边。形象化地，第一种可以称为上行边，第二种称为下行边。

首先通过树上差分，将信息分别储存在上行边的起点与下行边的中点。

```cpp
for (int i = 1;i <= k;++i)
{
	int lca = getLCA (a[i],a[i - 1]);
	++up[a[i - 1]];++down[a[i]];//up 加的位置为起点，down 加的位置为终点
	--up[lca];--down[lca];
} 
```

然后通过一次 `dfs` 和差分数组还原每一条边经过的次数。最后统计答案，对于一条 $v \to u$ 需要花费的边，若是上行边，那么通过的次数记录在 $v$ 上，否则是 $u$ 上。设某条边经过了 $x$ 次，则总花费为 $1 + 2 + \cdots + 2^{x - 1} = 2^x - 1$，所以直接预处理 $2$ 的幂次即可。

总代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,k,a[MAX * 10],f[MAX][20],dep[MAX],up[MAX],down[MAX];
vector <int> ve[MAX];
map <pair <int,int>,int> co;
ll ans,pw[MAX * 10];
int getLCA (int x,int y);
void dfs (int u,int fa);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i < n;++i)
	{
		int x = read (),y = read (),ty = read ();
		ve[x].push_back (y);co[{x,y}] = 0;
		ve[y].push_back (x);co[{y,x}] = ty;
	}
	k = read ();
	for (int i = 1;i <= k;++i) a[i] = read ();
	dfs (1,0);
	a[0] = pw[0] = 1;
	for (int i = 1;i <= k;++i) pw[i] = 	pw[i - 1] * 2 % MOD;
	for (int i = 1;i <= k;++i)
	{
		int lca = getLCA (a[i],a[i - 1]);
		++up[a[i - 1]];++down[a[i]];//up 加的位置为起点，down 加的位置为终点 
		--up[lca];--down[lca];
	} 
	dfs (1,0);
	for (int u = 1;u <= n;++u)
	{
		for (auto v : ve[u]) // u -> v 时不需花费 
		{
			if (!co[{v,u}]) continue;
			//v -> u 时此时需要花费
			if (dep[u] < dep[v]) ans = (ans + pw[up[v]] - 1 + MOD) % MOD; 
			else ans = (ans + pw[down[u]] - 1 + MOD) % MOD; 
		}
	}
	printf ("%lld\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void dfs (int u,int fa)
{
	f[u][0] = fa;dep[u] = dep[fa] + 1;
	for (int i = 1;i <= 18;++i) f[u][i] = f[f[u][i - 1]][i - 1];
	for (auto v : ve[u])
	{
		if (v == fa) continue;
		dfs (v,u);
		up[u] += up[v];down[u] += down[v];//第二次 dfs 时才用到 （通过差分数组进行还原）    第一次 dfs 时值均为 0，所以没有影响
	}
}
int getLCA (int x,int y)
{
	if (dep[x] < dep[y]) swap (x,y);
	for (int i = 18;~i;--i)
	{
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];
		if (x == y) return x;
	}
	for (int i = 18;~i;--i)
		if (f[x][i] != f[y][i]) x = f[x][i],y = f[y][i];
	return f[x][0];
}
```

---

## 作者：Mu_leaf (赞：0)

注意一开始是要从 $1$ 出发到点 $s_1$ 的，翻译没写。

## [思路]

还是挺好想的，代码挺短。

显然，直接算一条路径上边的贡献极其难算。考虑把贡献拆开，考虑每条边的经过次数及对答案的贡献。这一点很容易用树上差分实现。

设每条有向边逆向经过次数为 $x$，则显然对答案的贡献为 $2^x-1$。

瓶颈在于求公共祖先。

```cpp
#include <bits/stdc++.h>
//#define int long long

using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>
	void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T,typename ...Args>
	void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>
	void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>
	void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=1e6+5,mod=1e9+7;
vector<int> V[N];
int sum1[N],sum2[N],top[N],pw[N],dep[N],siz[N],son[N],fa[N];
int s[N],k,n,eu[N],ev[N],e[N],ans;
void dfs1(int x,int f){
	dep[x]=dep[f]+1;fa[x]=f;siz[x]=1;
	int fat=-1;
	for(auto v:V[x]){
		if(v==f) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>fat) fat=siz[v],son[x]=v;
	}
} 
void dfs2(int x,int tp){
	top[x]=tp;
	if(!son[x]) return;
	dfs2(son[x],tp);
	for(auto v:V[x]){
		if(v==son[x] || v==fa[x]) continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]>dep[y]?y:x;
}
void solve(int x,int f){
	for(auto v:V[x]){
		if(v==f) continue;
		solve(v,x);
		sum1[x]+=sum1[v];
		sum2[x]+=sum2[v];
	}
}
signed main(){
	read(n);
	pw[0]=1;
	for(int i=1;i<N;i++) pw[i]=1ll*pw[i-1]*2%mod;
	for(int i=1,u,v,op;i<n;i++){
		read(u,v,op);
		V[u].push_back(v);
		V[v].push_back(u);
		eu[i]=u,ev[i]=v,e[i]=op;
	}
	dfs1(1,0);
	dfs2(1,1);
	read(k);
	s[1]=1;k++;
	for(int i=2;i<=k;i++) read(s[i]);
	for(int i=2;i<=k;i++){
		int L=lca(s[i-1],s[i]);
		sum1[s[i-1]]++;sum1[L]--;
		sum2[s[i]]++;sum2[L]--;
	}
	solve(1,0);
	for(int i=1;i<n;i++){
		if(e[i]==0) continue;
		int op=0,x;
		if(dep[eu[i]]>dep[ev[i]])x=eu[i];
		else x=ev[i],op=1;
		if(op==0) ans=(ans+pw[sum2[x]]-1)%mod;
		else ans=(ans+pw[sum1[x]]-1)%mod;
	}
	write((ans+mod)%mod);
	flush();
	return 0;
}
/*

sum[r]^sum[l-1]
*/ 
```

---

## 作者：wwwwwza (赞：0)

思路简单。

记录一条边的两个值，从 $lca$ 经过这条边的次数和经过这条边去 $lca$ 的次数。

树链剖分+树上差分。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int mod=1e9+7;
int n,q,x,y,opt,tot=0,id[N],ans=0;
int dfn[N],siz[N],dep[N],fat[N],son[N],top[N],cnt=0;
int tree[2][N];
vector<int>g[N];
struct edge{
	int u,v;
}r[N];
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}     
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar((x%10)^48);
	return;
}
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fat[u])continue;
		dep[v]=dep[u]+1,fat[v]=u;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void dfs2(int u,int topx){
	dfn[u]=++cnt;
	top[u]=topx;
	if(son[u])dfs2(son[u],topx);
	else return;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fat[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fat[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	return u;
}
void dfs3(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fat[u])continue;
		dfs3(v);
		tree[0][u]+=tree[0][v];
		tree[1][u]+=tree[1][v];
		tree[0][u]=(tree[0][u]+mod)%mod;
		tree[1][u]=(tree[1][u]+mod)%mod;
	}
}
int ksm(int a,int b){
	int sum=1;
	while(b){
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		cin >>x>>y>>opt;
		g[x].push_back(y);
		g[y].push_back(x);
		if(opt==1)r[++tot]={x,y};
	}
	dfs1(1,0);
	dfs2(1,1);
	q=read();
	q++,id[1]=1;
	for(int i=2;i<=q;i++){
		id[i]=read();
	}
	for(int i=1;i<q;i++){
		int u=id[i],v=id[i+1];
		int l=lca(u,v);
		tree[0][u]++,tree[0][l]--;
		tree[1][v]++,tree[1][l]--;
	}
	dfs3(1);
	for(int i=1;i<=tot;i++){
		int u=r[i].u,v=r[i].v,cnt;
		if(fat[u]==v){
			cnt=tree[1][u];
		}else{
			cnt=tree[0][v];
		}
		ans=ans+ksm(2,cnt)-1+mod;
		ans%=mod;
	} 
	write(ans);
	return 0;
}
```

---

## 作者：robertuu (赞：0)

# CF575B Bribes

### 树上差分求边的经过次数

对于从 $i$ 到 $j$ 的路线：一定是先从 $i$ 向上走到 $\operatorname{lca}(i,j)$，再从 $\operatorname{lca}(i,j)$ 向下走到 $j$

因此，可以用差分表示这条路径走过了哪些边。

可以用 $b[i]$ 表示从点 $i$ 到父节点的边的差分值。

直接使用 `dfs` 就可以将差分值进行累加，得到每条边经过的次数。

对于路径 $i \to j$，对差分值的修改如下：

```cpp
b[x]++;
b[y]++;
b[lca(x,y)] -= 2;
```

将差分值转换为答案的 `dfs`：

```cpp
void dfs(int x)
{
	for(int i = head[x];i;i = nxt[i])
		if(to[i] != f[x][0])
		{
			get_ans(to[i],i);
			b[x] += b[to[i]];
		}
}
```


### 突破口：路线方向很重要

因为路线方向决定是否收费，因此在差分时还要额外记录这条边是 从儿子往父亲走 还是 从父亲往儿子走。

这个方向信息可以直接通过树上路径的性质得到。

对差分值的修改如下：（$0$ 表示儿子向父亲，$1$ 表示父亲向儿子）

```cpp
b[x][0]++;
b[lca(x,y)][0]--;
b[y][1]++;
b[lca(x,y)][1]--;
```

dfs 只需要把两个方向分别合并就行了！

### 注意！

要处理边的编号与点的对应问题（即 $b[i]$ 表示的是哪个编号的边），否则不知道那一条边要收费！

收费的 $2$ 的幂次和的问题直接预处理就完事了！

----
AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() // 快读，防止卡常
{
	int x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+ch-'0', ch = getchar();
	return x;
}
const int N = 1e5 + 1,M = 5e5 + 1,mod = 1e9 + 7;
int head[N],to[2*N],nxt[2*N],cnt,ans[2*N];
bool pay[2*N];
void add(int x,int y)
{
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}
int pow2[M]; // 每条路最多只会走m/2次
void init() // 初始化2的幂次和 （2^1+2^2+...+2^n = 2^n+1 - 1）
{
	int nowp = 2;
	for(int i = 1;i <= 5e5;i++)
	{
		pow2[i] = nowp - 1;
		nowp *= 2;
		nowp %= mod;
	}
}
int f[N][20],dep[N],b[N][2];
void dfs(int x) // 遍历树，得到每个点的父亲和深度
{
	for(int i = head[x];i;i = nxt[i])
		if(to[i] != f[x][0])
		{
			f[to[i]][0] = x;
			dep[to[i]] = dep[x] + 1;
			dfs(to[i]);
		}
}
int maxL;
int lca(int x,int y) // 求lca（树上差分要用）
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i = maxL;i >= 0;i--)
		if(dep[x]-dep[y] >= (1<<i)) x = f[x][i];
	if(x == y) return x;
	for(int i = maxL;i >= 0;i--)
		if(f[x][i] != f[y][i])
		{
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}
int opp(int x) // 找一个路的反向路编号
{
	if(x == 0) return 0; // 防止根节点-1暴死
	if(x % 2 == 0) return x-1;
	return x+1;
}
void get_ans(int x,int roadto) // 通过树上差分代码求答案，roadto是点到父亲边的编号
{
	ans[roadto] = b[x][1];
	ans[opp(roadto)] = b[x][0];
	for(int i = head[x];i;i = nxt[i])
		if(to[i] != f[x][0])
		{
			get_ans(to[i],i);
			ans[roadto] += ans[i];
			ans[opp(roadto)] += ans[opp(i)];
		}
}
int main()
{
	init();
	int n = read(),m,x,y,z;
	maxL = log2(n);
	for(int i = 1;i < n;i++)
	{
		x = read(); y = read(); z = read();
		add(x,y); add(y,x);
		if(z) pay[cnt] = 1;
	}
	dfs(1);
	for(int i = 1;i <= maxL;i++)
		for(int x = 1;x <= n;x++)
			f[x][i] = f[f[x][i-1]][i-1];
	m = read();
	x = 1;
	for(int i = 1;i <= m;i++)
	{
		y = read();
		b[x][0]++; b[lca(x,y)][0]--;
		b[y][1]++; b[lca(x,y)][1]--;
		x = y;
	}
	get_ans(1,0);
	int anss = 0;
	for(int i = 1;i <= cnt;i++)
		if(pay[i]) anss = (anss + pow2[ans[i]]) % mod;
	printf("%d",anss);
	return 0;
}
```


---

## 作者：Gorenstein (赞：0)

### 题意

一棵树，从根节点 $1$ 按顺序通过树上的边走到若干个点 $s[1],s[2],\dots,s[k]$。树的边有两类，一类是无向边，通过不需要花费；一类是有向边，如 $(x,y)$，则 $x\to y$ 不需要花费，而第 $i$ 次走 $y\to x$ 需要花费 $2^{i-1}$，求总花费。

### 题解

某些边从一个方向通过需要花费而从另一个方向通过不需要花费，就说明了有一些边从上往下需要花费，从下往上不需要；而另一些边从下往上需要花费，从上往下不需要。

从而可以把路径拆分为上行和下行，进行两次差分，分别计算。设 $s[0]=1$，即对于路径 $s[i-1]$ 到 $s[i]$，拆分为 $s[i-1]$ 到 $\text{lca}(s[i-1),s[i])$ 和 $\text{lca}(s[i-1),s[i])$ 到 $s[i]$ 这两段，分别算入两个差分数组中，含义为上行经过的次数和下行经过的次数。

查询的时候对于每条边分别计算即可，若是下行需要花费，那么就统计深度较大的点的第二个差分；反之若是上行，统计深度较大的点的第一个差分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
const ll N=100010,p=1000000007;
ll qpow(ll x,ll y){
	ll z=1;
	for(;y;y>>=1){
		if(y&1)z=z*x%p;
		x=x*x%p;
	}
	return (z%p);
}
ll n,k,f[N][25],d[N],b[N],c[N],s[N*10],t,ans;
ll ver[N<<1],nxt[N<<1],head[N],tot,v[N<<1],frm[N<<1];
void add(ll x,ll y,ll z){
	ver[++tot]=y,frm[tot]=x,v[tot]=z,
	nxt[tot]=head[x],head[x]=tot;
}
queue<ll> q;
void bfs(){
	q.push(1),d[1]=1;
	while(q.size()){
		ll x=q.front();q.pop();
		for(ll i=head[x];i;i=nxt[i]){
			ll y=ver[i];if(d[y])continue;
			d[y]=d[x]+1,f[y][0]=x;
			for(ll j=1;j<=t;j++)
				f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
ll LCA(ll x,ll y){
	if(d[x]>d[y])swap(x,y);
	for(ll i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x])y=f[y][i];
	if(x==y)return x;
	for(ll i=t;i>=0;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
void dfs(ll x,ll fa){
	for(ll i=head[x];i;i=nxt[i]){
		ll y=ver[i];if(y==fa)continue;
		dfs(y,x),b[x]+=b[y],c[x]+=c[y];
	}
}
int main(){
	n=read(),s[0]=1;
	for(ll i=1,x,y,z;i<n;i++){
		x=read(),y=read(),z=read();
		if(z)add(x,y,0),add(y,x,1);
		else add(x,y,0),add(y,x,0);
	}
	k=read();
	for(ll i=1;i<=k;i++)s[i]=read();
	t=1+(int)log(n)/log(2),bfs();
	for(ll i=1;i<=k;i++){
		ll lca=LCA(s[i-1],s[i]);
		++b[s[i-1]],--b[lca],++c[s[i]],--c[lca];
	}
	dfs(1,0);
	for(ll i=1;i<=tot;i++)
		if(v[i]&&d[frm[i]]>d[ver[i]])
			ans=(ans+qpow(2,b[frm[i]])%p-1+p)%p;
		else if(v[i])
			ans=(ans+qpow(2,c[ver[i]])%p-1+p)%p;
	printf("%lld\n",ans);
	return 0;
}
```

---

