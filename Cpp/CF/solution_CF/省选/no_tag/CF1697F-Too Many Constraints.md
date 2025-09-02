# Too Many Constraints

## 题目描述

You are asked to build an array $ a $ , consisting of $ n $ integers, each element should be from $ 1 $ to $ k $ .

The array should be non-decreasing ( $ a_i \le a_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ ).

You are also given additional constraints on it. Each constraint is of one of three following types:

- $ 1~i~x $ : $ a_i $ should not be equal to $ x $ ;
- $ 2~i~j~x $ : $ a_i + a_j $ should be less than or equal to $ x $ ;
- $ 3~i~j~x $ : $ a_i + a_j $ should be greater than or equal to $ x $ .

Build any non-decreasing array that satisfies all constraints or report that no such array exists.

## 样例 #1

### 输入

```
4
4 0 4
2 2 3
3 1 2 3
1 2 2
3 3 2
1 1 1
2 2 3 2
3 2 3 2
5 5 5
3 2 5 7
2 4 5 10
3 4 5 6
3 3 4 7
2 1 5 7```

### 输出

```
1 2 3 4
1 3
-1
1 2 2 5 5```

# 题解

## 作者：lingfunny (赞：13)

看起来就像 2-sat。但每个点的取值为 $1\sim k$，似乎是 k-sat。

注意到 $k$ 比较小，可以想到把每个点 $p$ 拆成 $k$ 个 `bool` 变量，其中第 $i$ 个 `bool` 变量 $X_{p,i}$ 表示 $a_p$ 是否 $\le i$。

显然此时要连接 $T_{p,i}\to T_{p_,i+1}$（满足变量含义）和 $T_{p, i} \to T_{p-1, i}$（满足单调不降）。还有它们的反边（$u\to v$ 的反边指 $v' \to u'$）。

至于为什么不拆成 $X_{p,i}$ 表示 $a_p$ 是否 $=i$，见[此](https://280800.blog.luogu.org/2-sat)。

> 取值型问题一般状态设计是变量 $x\ge k$。形如 $x=k$ 的状态设计不好做，因为默认了 $x$ 的若干个状态中必须有且只有一个为 $\text{True}$，然而实际建图中无法建出这样的限制条件，也可能是我太菜了所以建不出。

那么对于题目中给出的若干种限制：

1. $a_i\neq x$：$T_{i,x}\to T_{i,x-1}$ 及其反边。
2. $a_i+a_j\le x$：$F_{i, p} \to T_{j, x-p-1}$ 及其反边。$F_{j,p}$ 同理。
3. $a_i+a_j\ge x$：$T_{i,p}\to F_{j, x-p-1}$ 及其反边。$T_{j,p}$ 同理。

最后注意一下上面的下标显然会越界，越界的时候特判一下即可。如 $a_i+a_j\le k-2$，暗含 $a_i, a_j\le k-3$。

然后你就做完了。~~（还挺套路的，除了建图真的麻烦~~

丑陋的代码：

```cpp
// Problem: F. Too Many Constraints
// From: Codeforces - Educational Codeforces Round 130 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1697/problem/F
// Time: 2022-06-12 22:35
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e4+10, mxz = 20*mxn;

int n, m, k, tot;
vector <int> G[mxz];
#define _(x) (x > tot ? x - tot : x + tot)
inline void add(int u, int v) { G[u].emplace_back(v);
// int u_ = u > tot ? u - tot : u, v_ = v > tot ? v - tot: v;
// printf("(%d, %d) %c -> (%d, %d) %c\n", u_%n?u_%n:n, (u_%n?u_/n:(u_-1)/n)+1, u>tot?'F':'T',
// v_%n?v_%n:n, (v_%n?v_/n:(v_-1)/n)+1, v>tot?'F':'T');
}
inline void dadd(int u, int v) { add(u, v), add(_(v), _(u)); }
int low[mxz], dfn[mxz], dfc, in[mxz], stk[mxz], top, scc[mxz], cnt;
void tarjan(int u) {
	low[u] = dfn[u] = ++dfc, in[stk[++top] = u] = 1;
	for(int v: G[u]) {
		if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(in[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u] && ++cnt) do scc[stk[top]] = cnt, in[stk[top]] = 0; while(stk[top--] != u);
}

inline void solve() {
	scanf("%d%d%d", &n, &m, &k);
	tot = n * k;
	// printf("n = %d, m = %d, k = %d\n", n, m, k);
	for(int i = 1; i <= tot*2; ++i) dfn[i] = 0, vector <int> ().swap(G[i]);
	dfc = top = cnt = 0;
	for(int p = 1; p <= n; ++p) for(int i = 1; i < k; ++i) dadd(p+(i-1)*n, p+i*n);
	for(int p = 2; p <= n; ++p) for(int i = 1; i <= k; ++i) dadd(p+(i-1)*n, p-1+(i-1)*n);
	add(2*tot, tot);
	// puts("END");
	for(int op, i, j, x; m--;) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d", &i, &x);
			if(x == 1) add(i, _(i));
			else dadd(i+(x-1)*n, i+(x-2)*n);
		} else {
			scanf("%d%d%d", &i, &j, &x);
			if(op == 2) {
				if(x-1 < k)
				add(_(i+(x-2)*n), i+(x-2)*n),
				add(_(j+(x-2)*n), j+(x-2)*n);
				for(int p = 1; p <= k; ++p) {
					int oth = x - p - 1;
					if(oth >= 1 && oth <= k)
					dadd(_(i+(p-1)*n), j+(oth-1)*n),
					dadd(_(j+(p-1)*n), i+(oth-1)*n);
				}
			} else {
				if(x-k > 1)
				add(i+(x-k-2)*n, _(i+(x-k-2)*n)),
				add(j+(x-k-2)*n, _(j+(x-k-2)*n));
				for(int p = 1; p <= k; ++p) {
					int oth = x - p - 1;
					if(oth >= 1 && oth <= k)
					dadd(i+(p-1)*n, _(j+(oth-1)*n)),
					dadd(j+(p-1)*n, _(i+(oth-1)*n));
				}
			}
		}
	}
	for(int i = 1; i <= 2*tot; ++i) if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= tot; ++i) if(scc[i] == scc[i+tot]) return puts("-1"), void();
	for(int i = 1; i <= n; ++i) {
		for(int p = 0; p < k; ++p) if(scc[i+p*n] < scc[_(i+p*n)]) { printf("%d%c", p+1, " \n"[i==n]); break; }
	}
}

int main() {
	int tt;
	scanf("%d", &tt);
	while(tt--) solve();
}
```



---

## 作者：GaryH (赞：6)

## CF1697F 题解
一道简单的 `2-SAT` 题，难点在于想到用 `2-SAT` 做。

考虑创建 $n\times m$ 个 $01$ 变量来表示序列 $a$，
其中变量 $X_{i,j}(1\le i\le n,1\le j\le k)=[a_i\le j]$。
为方便叙述，我们规定 $[X_{i,j}=p]\rightarrow[X_{i',j'}=q]$ 代表，若满足 $X_{i,j}=p$，则 $X_{i',j'}$ 必须等于 $q$。

那么我们可以将所有限制表示成这些变量间的关系，如：

1. $a_i \ne j$ 等价于满足 $[X_{i,j+1}=1]\rightarrow [X_{i,j}=1]$ 与 $[X_{i,j-1}=0]\rightarrow [X_{i,j}=0]$；

2. $a_i+a_j\ge x$ 等价于对 $\forall s+t<x$ 满足 $[X_{i,s}=1]\rightarrow [X_{j,t}=0]$ 和 $[X_{j,s}=1]\rightarrow [X_{i,t}=0]$；

3. $a_i+a_j\le x$ 等价于对 $\forall s+t\ge x-1$ 满足 $[X_{i,s}=0]\rightarrow [X_{j,t}=0]$ 和 $[X_{j,s}=0]\rightarrow [X_{i,t}=0]$；

4. $a$ 序列递增等价于对 $\forall i\in[1,n-1],s\in[1,k]$ 满足 $[X_{i,s}=0]\rightarrow [X_{i+1,s}=0]$ 和 $[X_{i+1,s}=1]\rightarrow [X_{i,s}=1]$；

5. 对 $\forall i\in[1,n]$，$a_i$ 有值且值唯一等价于 $[X_{i,k}=0]\rightarrow [X_{i,k}=1]$ 和 $\forall s,t\in[1,k],s\ne t$，满足 $[X_{i,s}=1]\rightarrow [X_{i,t}=0]$。

然后建出图后跑个缩点就做完了。

---

## 作者：vectorwyx (赞：3)

第一眼是拆点差分约束，但是嘛，它这个 $a_i\not= x$ 就基本上为差分约束宣告了死刑。

2-SAT。把每个点拆成 $k$ 个布尔变量，第 $j$ 个布尔变量表示 $a_i$ 是否 $\ge j$。记 $(i,j,o)$ 表示第 $i$ 个点的第 $j$ 个布尔变量取值为 $o$ 代表第的点。初始时，$(i,j,0)\to (i,j+1,0),(i,j+1,1)\to(i,j,1)$，$(i,1,0)\to(i,1,1)$。

为了方便处理边界，再加一个布尔变量 $(i,k+1,1)\to(i,k+1,0)$。

对于 $a_i\le a_{i+1}$，枚举 $w\in[1,k]$，连 $(i,w,1)\to(i+1,w,1),(i+1,w,0)\to(i,w,0)$。

对于 $a_i\not= x$，连 $(i,x,1)\to (i,x+1,1),(i,x+1,0)\to(i,x,0)$。

对于 $a_i+a_j\le x$，枚举 $w\in[1,k]$，连 $(i,w,1)\to(j,x-w+1,0),(j,x-w+1,1)\to(i,w,0)$。

对于 $a_i+a_j\ge x$，枚举 $w\in[1,k]$，连 $(i,w+1,0)\to(j,x-w,1),(j,x-w,0)\to(i,w+1,1)$。

发现除了处理边界时用到的单点赋值型语句，所有边都形如 $(X,p)\to(Y,q),(Y,!q)\to (X,!p)$，那么这是一个标准的 2-SAT 形式。直接上板子就行。

代码如下：
```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define gtc getchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
//#define int ll 
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e6+5;
int a[N],n,k,nk,nn,b[N];
namespace Graph{
vector<int> e[N>>1];
int dfn[N],ti,low[N],stk[N],top,ins[N],bel[N],num;

void connect(int x,int y){e[x].eb(y);}//printf("%d -> %d\n",x,y);}

void add(int x,int y){
	int p=x>nk?-1:1,q=y>nk?-1:1;
//	printf("add(%d,p=%d,%d,q=%d)\n",x,p,y,q);
	connect(x,y);
	if(abs(x-y)==nk) re;
	connect(y+q*nk,x+p*nk);
}
void clear(){
	ti=top=0;
	fo(i,1,nn) b[i]=dfn[i]=low[i]=stk[i]=ins[i]=bel[i]=0,e[i].clear();
}
void dfs(int x){
//	printf("dfs(%d)\n",x);
	dfn[x]=low[x]=++ti;
	stk[++top]=x;ins[x]=1;
	for(int i:e[x]){
		if(!dfn[i]) dfs(i),sml(low[x],low[i]);
		else if(ins[i]) sml(low[x],dfn[i]);
	}
	if(low[x]==dfn[x]){
		++num;
//		cout<<num<<":";
		while(1){
			int p=stk[top--];
//			cout<<p<<' ';
			bel[p]=num;ins[p]=0;
			if(p==x) brk;
		}
//		HH;
	}
}
bool tarjan(){
	fo(i,1,nn) if(!dfn[i]) dfs(i);
	fo(i,1,nk) if(bel[i]==bel[i+nk]) re 0;
	fo(i,1,nk) b[i]=bel[i+nk]<bel[i];
	re 1;
}
}
using Graph::tarjan;
using Graph::add;
using Graph::clear;
int F(int i,int j,int o=0){
	big(j,1);sml(j,k+1);
	re (i-1)*(k+1)+j+o*nk;
}

void solve(){
	int q;
	cin>>n>>q>>k;nk=n*(k+1);nn=2*nk;
//	printf("nk=%d\n",nk);
	clear();
	fo(i,1,n){
		fo(j,1,k) add(F(i,j,0),F(i,j+1,0));
//		go(j,k+1,2) add(F(i,j,1),F(i,j-1,1));
		add(F(i,1,0),F(i,1,1));
		add(F(i,k+1,1),F(i,k+1,0));
	}
	fo(i,1,n-1) fo(w,1,k) add(F(i,w,1),F(i+1,w,1));
	while(q--){
		int o=read(),i=read();
		if(o==1){
			int x=read();
			add(F(i,x,1),F(i,x+1,1));
			co;
		}
		int j=read(),x=read();
		if(o==2) fo(w,1,k) add(F(i,w,1),F(j,x-w+1,0));
		else fo(w,1,k) add(F(i,w+1,0),F(j,x-w,1)); 
	}
	if(!tarjan()){puts("-1");re;}
	fo(i,1,n){
		a[i]=k;
		fo(j,1,k) if(!b[F(i,j)]){a[i]=j-1;brk;}
	}
	out(a,1,n);
}

signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：I_am_Accepted (赞：2)

2-sat 好题。

首先我们每一个 bool 变量表示「$a_i$ 是否 $\ge j$」，由于必然 $a_i\ge 1$，所以我们的变量数为 $n(k-1)$。

然后我们根据题目条件来建有向边，注意 2-sat 要满足**对称性**，所以下文中每一个条件的**逆否命题都要建边**：

* $a_i\le a_{i+1}$，等价于「对于所有的 $v$，若 $a_i\ge v$，则 $a_{i+1}\ge v$」。

* $a_i\ne x$，等价于「若 $a_i\ge x$，则 $a_i\ge x+1$」。

* $a_i+a_j\le x$，等价于「对于所有的 $v$，若 $a_i\ge v$，则 $\neg(a_j\ge x-v+1)$」。

* $a_i+a_j\ge x$，等价于「对于所有的 $v$，若 $\neg(a_i\ge v)$，则 $a_j\ge x-v+1$」。

当然还有一个最浅显的别忘了：

* 若 $a_i\ge v$，则 $a_i\ge v-1$。

跑 Tarjan 缩点即可。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define ckmn(a,b) a=min(a,b)
#define N 360000
vector<int> e[N];
int n,m,k,dfn[N],low[N],col[N],tim,ct,s[N],st;
inline void adde(int x,int y){e[x].pb(y);if(x!=(y^1))e[y^1].pb(x^1);} 
inline int num(int id,int x,bool y){return ((id-1)*(k-1)+(x-2))<<1|y;}//第 id 个数 >= x 的 y 状态的下标 
void build(int x){For(i,2,k-1)adde(num(x,i,0),num(x,i+1,0));}
void le(int x,int y){For(i,2,k) adde(num(x,i,1),num(y,i,1));}
void ne(int x,int val){
	if(val==1) adde(num(x,val+1,0),num(x,val+1,1));
	else if(val==k) adde(num(x,val,1),num(x,val,0));
	else adde(num(x,val,1),num(x,val+1,1));
}
void sumle(int x,int y,int val){
	For(i,2,k)
		if(i+1>val) adde(num(x,i,1),num(x,i,0)),adde(num(y,i,1),num(y,i,0));
		else if(val-i+1<=k) adde(num(x,i,1),num(y,val-i+1,0));
}
void sumge(int x,int y,int val){
	For(i,2,k)
		if(i+k<=val) adde(num(x,i,0),num(x,i,1)),adde(num(y,i,0),num(y,i,1));
		else if(val-i+1>=2) adde(num(x,i,0),num(y,val-i+1,1));
}
void dfs(int x){
	dfn[x]=low[x]=++tim;
	s[++st]=x;
	for(int i:e[x]){
		if(!dfn[i]) dfs(i),ckmn(low[x],low[i]);
		else if(!col[i]) ckmn(low[x],dfn[i]);
	}
	if(low[x]==dfn[x]){
		col[x]=++ct;
		while(s[st]!=x) col[s[st--]]=ct;
		st--;
	}
}
void work(){
	scanf("%d%d%d",&n,&m,&k);
	int lim=(k-1)*2*n;
	For(i,0,lim-1) e[i].clear();
	For(i,1,n) build(i);
	For(i,1,n-1) le(i,i+1);
	int x,y,val,opt;
	For(i,1,m){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d",&x,&val);
			ne(x,val);
		}else if(opt==2){
			scanf("%d%d%d",&x,&y,&val);
			sumle(x,y,val);
		}else{
			scanf("%d%d%d",&x,&y,&val);
			sumge(x,y,val);
		}
	}
	fill(dfn,dfn+lim,0);
	fill(col,col+lim,0);
	tim=ct=st=0;
	For(i,0,lim-1) if(!dfn[i]) dfs(i);
	for(int i=0;i<lim;i+=2) if(col[i]==col[i^1]){
		puts("-1");
		return ;
	}
	For(i,1,n){
		val=1;
		For(j,2,k) if(col[num(i,j,1)]<col[num(i,j,0)]) val=j;
		printf("%d ",val);
	}
	puts("");
}
int main(){
	int T;scanf("%d",&T);
	while(T--)work();
return 0;}
```

---

## 作者：Aisaka_Taiga (赞：1)

建图曹丹的 2-SAT 问题。

我们可以看到 $k$ 的值是很小的，所以我们可以考虑把每一个点拆成 $2\times k$ 个点，$a_{i}$ 表示 $a\le x$，$a_{i+k}$ 表示 $a> x$。

显然我们根据数的基本关系可以得到：

$$
  \left\{\begin{matrix} 
  a_{i}\le x \Rightarrow a_{i}\le x+1 \\  
  a_{i}> x \Rightarrow a_{i}> x-1 
\end{matrix}\right. 
$$

也就是连接 $a_{i}\to a_{i+1}$ 和 $a_{i+k}\to a_{i+k-1}$。

由于要满足单调性，我们又可以得到：

$$
  \left\{\begin{matrix} 
  a_{i}\le x \Rightarrow a_{i-1}\le x  \\  
  a_{i}> x \Rightarrow a_{i+1}> x 
\end{matrix}\right. 
$$

也就是要连接 $a_{i}\to a_{i-1}$ 和 $a_{i+k}\to a_{i+k+1}$。

但是我们要考虑限制一下最后一个元素的值是不大于 $k$ 的，因为我们只开了 $2\times k$ 个点，如果要是出现大于 $k$ 的元素就直接 G 了，所以们直接来连一条 $2\times tot\to tot$ 连一条边，然后我们就可以完美的解决这个问题了。

对于题目的三个限制，我们分别这样连：

1. 对于第一个，$a_{i} \le x$ 要连向 $a_{i} \le x-1$ 来让 $a_{i}\ne x$，以及 $a_{i} > x-1$ 连向 $a_{i} > x$。

2. 对于第二个，$a_{i} > y$ 要连向 $a_{j} \le x-y-1$，以及 $a_{j} > y$ 要连向 $a_{i}\le x-y-1$，当然我们这里的 $y$ 其实是从 $1$ 枚举到 $k$ 的值，当然我们要注意的是如果 $x\le k$ 的话我们就会出现和上面一样需要限制边界的情况，所以我们需要特判 $x\le k$ 的情况，并和上面一样加上这两个数的值不能大于等于 $x$ 的限制。

3. 对于第三个，$a_{i}\le y$ 要连向 $a_{j}> x-y-1$，以及 $a_{j}\le y$ 要连向 $a_{i}> y$，当然这个也会出现和上面一样的边界问题，但是这里不同的是要处理的是大于等于 $k+2$ 的情况，因为这个时候两个各一个 $1$ 的话还是多出来个 $k$，所以最后肯定有一个数会大于 $k$，此时我们就要加限制了，还是保证在 $k$ 的范围内，~~但我后面发现不加也可以应该是因为之前有 $\le k$ 的限制的原因。~~

code:

```cpp

#include<bits/stdc++.h>
#define ARK(X) (X>tot?X-tot:X+tot)
#define INF 0x3f3f3f3f
#define N 1000100
#define M 20010
#define endl '\n'
using namespace std;
int t,n,m,k,tot,low[N],dfn[N],tim,vis[N],stk[N],top,sd[N],cnt;
vector<int>G[N];
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
inline void add(int u,int v){G[u].push_back(v),G[ARK(v)].push_back(ARK(u));}
inline void tarjan(int u) 
{
	low[u]=dfn[u]=++tim,vis[stk[++top]=u]=1;
	for(int v:G[u]) 
	{
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(vis[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]&&++cnt)while(1){sd[stk[top]]=cnt,vis[stk[top]]=0;if(stk[top--]==u)break;}
}
inline void work()
{
	n=read(),m=read(),k=read();
	tot=n*k;
	for(int i=1;i<=tot*2;i++)vector<int>().swap(G[i]),dfn[i]=low[i]=0;
	tim=top=cnt=0;
//	cout<<"cao>"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=1;j<k;j++)
			add(i+(j-1)*n,i+j*n);
//	cout<<"cao>"<<endl;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=k;j++)
			add(i+(j-1)*n,i+(j-1)*n-1);
	add(2*tot,tot);
//	cout<<"cao>"<<endl;
	for(int o=1;o<=m;o++)
	{
//		cout<<"cao>"<<endl;
		int op=read();
		if(op==1)
		{
			int x=read(),z=read();
			if(z==1)G[x].push_back(ARK(x));
			else add(x+(z-1)*n,x+(z-2)*n);
		}
		else if(op==2)
		{
			int x=read(),y=read(),z=read();
			if(z<=k)G[ARK(x+(z-2)*n)].push_back(x+(z-2)*n),G[ARK(y+(z-2)*n)].push_back(y+(z-2)*n);
			for(int i=1;i<=k;i++)
			{
				int cao=z-i-1;
				if(cao>=1&&cao<=k)add(ARK(x+(i-1)*n),y+(cao-1)*n),add(ARK(y+(i-1)*n),x+(cao-1)*n);
			}
		}
		else if(op==3)
		{
			int x=read(),y=read(),z=read();
//			if(z-1>k)G[x+(z-k-2)*n].push_back(ARK(x+(z-k-2)*n)),G[y+(z-k-2)*n].push_back(ARK(y+(z-k-2)*n));
			for(int i=1;i<=k;i++)
			{
				int cao=z-i-1;
				if(cao>=1&&cao<=k)add(x+(i-1)*n,ARK(y+(cao-1)*n)),add(y+(i-1)*n,ARK(x+(cao-1)*n));
			}
		}
	}
//	cout<<"cao>"<<endl;
	for(int i=1;i<=2*tot;i++)if(!dfn[i])tarjan(i);
//	cout<<"scc:";
//	for(int i=1;i<=2*tot;i++)cout<<sd[i]<<" ";
//	cout<<endl;
	for(int i=1;i<=tot;i++)if(sd[i]==sd[i+tot]){cout<<"-1"<<endl;return ;}
	for(int i=1;i<=n;i++) 
	{
		for(int j=0;j<k;j++)
			if(sd[i+j*n]<sd[ARK(i+j*n)]){cout<<(j+1)<<" ";if(i==n)cout<<endl;break;}
	}
}
signed main()
{
	t=read();
	while(t--)work();
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [CF1697F](https://www.luogu.com.cn/problem/CF1697F)     

直接上 2-SAT。令 $f_{i,j}$ 表示 $a_i\ge j$ 是否成立，则初始条件有：要么 $f_{i,j}$ 为真，要么 $f_{i,j+1}$ 为假。$f_{i,1}$ 为真。要么 $f_{i,j}$ 为假，要么 $f_{i+1,j}$ 为真。     

考虑三种情况的限制：   

1：如果 $x=k$，则需满足 $f_{i,k}$ 为假。否则需满足：要么 $f_{i,x}$ 为假，要么 $f_{i,x+1}$ 为真。    

2：对于所有的 $p$，需满足要么 $f_{i,p}$ 为假，要么 $f_{j,x-p+1}$ 为假（如果 $x-p+1$ 越界的话，要么不受限制，要么必须令 $f_{i,p}$ 为假）。      

3：对于所有的 $p$，需满足要么 $f_{i,p}$ 为真，要么 $f_{j,x-p+1}$ 为真（如果 $x-p+1$ 越界的话，要么不受限制，要么必须令 $f_{i,p}$ 为真）。      

按上述方案连边（要双向连边），跑 2-SAT 即可。     

代码（略丑）：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t,k1,k2,k3,k4,k5,k6,k7,k8,k9,ans[500003];
int stk[500003],instk[500003],tot,dfn[500003],low[500003],idx,scc,col[500003];
vector<int>E[500003];
void mkset(int X){
	E[X*2].emplace_back(X*2-1);
	return;
}
void mkset2(int X){
	E[X*2-1].emplace_back(X*2);
	return;
}
int hs(int X,int Y){return X*2-1+Y;}
void addEdge(int st,int stv,int ed,int edv){
	E[hs(st,1-stv)].emplace_back(hs(ed,edv));
	E[hs(ed,1-edv)].emplace_back(hs(st,stv));
	return;
}
void tarjan(int now){
	stk[++tot]=now;
	instk[now]=1;
	dfn[now]=low[now]=++idx;
	for(auto i:E[now]){
		if(!dfn[i]){
			tarjan(i);
			low[now]=min(low[now],low[i]);
		}
		else{
			if(instk[i])low[now]=min(low[now],dfn[i]);
		}
	}
	if(dfn[now]==low[now]){
		scc++;
		while(1){
			k1=stk[tot];
			tot--;
			instk[k1]=0;
			col[k1]=scc;
			if(k1==now)break;
		}
	}
	return;
}
void sol(){
	ans[0]=0;
	for(int i=1;i<=n*k*2;i++)dfn[i]=low[i]=stk[i]=instk[i]=col[i]=0;
	idx=scc=tot=0;
	for(int i=1;i<=n*k*2;i++){
		if(!dfn[i])tarjan(i);
	}
	for(int i=1;i<=n*k;i++){
		if(col[hs(i,0)]==col[hs(i,1)]){
			ans[0]=-1000;
			return;
		}
		ans[i]=(col[hs(i,0)]>col[hs(i,1)]);
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			for(int j=1;j<k;j++)addEdge((i-1)*k+j,1,(i-1)*k+j+1,0);
			mkset2((i-1)*k+1);
		}
		for(int i=2;i<=n;i++){
			for(int j=1;j<=k;j++)addEdge((i-2)*k+j,0,(i-1)*k+j,1);
		}
		for(int i=1;i<=m;i++){
			cin>>k1>>k2>>k3;
			if(k1==1){
				if(k3==k)mkset((k2-1)*k+k3);
				else addEdge((k2-1)*k+k3,0,(k2-1)*k+k3+1,1);
			}
			if(k1==2){
				cin>>k4;
				for(int j=1;j<=k;j++){
					if(j>1&&(k4-j+1)>0&&(k4-j+1)<=k){
						E[hs((k2-1)*k+j,1)].emplace_back(hs((k3-1)*k+(k4-j+1),0));
						E[hs((k3-1)*k+j,1)].emplace_back(hs((k2-1)*k+(k4-j+1),0));
					}
					if(k4-j<=0){
						if(j==k){
							mkset((k2-1)*k+j);
							mkset((k3-1)*k+j);
						}
						else{
							addEdge((k2-1)*k+j,0,(k2-1)*k+j+1,1);
							addEdge((k3-1)*k+j,0,(k3-1)*k+j+1,1);
						}
					}
				}
			}
			if(k1==3){
				cin>>k4;
				for(int j=1;j<=k;j++){
					if(j>1&&(k4-j+1)>0&&(k4-j+1)<=k){
						E[hs((k2-1)*k+j,0)].emplace_back(hs((k3-1)*k+(k4-j+1),1));
						E[hs((k3-1)*k+j,0)].emplace_back(hs((k2-1)*k+(k4-j+1),1));
					}
					if(k4-j>k){
						if(j==k){
							mkset((k2-1)*k+j);
							mkset((k3-1)*k+j);
						}
						else{
							addEdge((k2-1)*k+j,0,(k2-1)*k+j+1,1);
							addEdge((k3-1)*k+j,0,(k3-1)*k+j+1,1);
						}
					}
				}
			}
		}
		sol();
		for(int i=1;i<=n*k*2;i++){
			E[i].clear();
			E[i].shrink_to_fit();
		}
		if(ans[0]==-1000){
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				if(j==k||(ans[(i-1)*k+j]==1&&ans[(i-1)*k+j+1]==0)){
					cout<<j<<" ";
					break;
				}
			}
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：ax_by_c (赞：0)

考虑 2-SAT，如果设 $(i,j,0/1)$ 表示 $a_i$ 是否等于 $j$ 则需要 $(i,1,1),\dots,(i,k,1)$ 中某一个被选，2-SAT 很难处理。

于是设 $(i,j,0/1)$ 表示 $a_i$ 是否大于等于 $j$，最后找任意一个合法的即可。

由于边界上有可能会出现问题，所以我们可以加上 $0$ 和 $k+1$ 来方便操作。

1. 本身含义。

$(i,j,1)\rightarrow(i,j-1,1),(i,j-1,0)\rightarrow(i,j,0),(i,0,0)\rightarrow(i,0,1),(i,1,0)\rightarrow(i,1,1),(i,k+1,1)\rightarrow(i,k+1,0)$。

2. 单调要求。
   
$(i,j,1)\rightarrow(i+1,j,1),(i+1,j,0)\rightarrow(i,j,0)$。

3. $a_i\neq j$。

若 $j=k$，则 $(i,j,1)\rightarrow(i,j,0)$。

否则，$(i,j,1)\rightarrow(i,j+1,1),(i,j+1,0)\rightarrow(i,j,0)$。

4. $a_i+a_j\le x$。

若 $a_i\ge w$，则 $a_j\le x-w$。

若 $v\le w,a_j\le x-w$，则 $a_j\le x-v$。

所以只需要考虑 $a_j\le x-w$。

于是 $x-w\ge k$ 时直接忽略，$1\le x-w$ 时 $(i,w,1)\rightarrow(j,x-w+1,0)$，否则类似第 3 类操作。

反向同理。

5. $a_i+a_j\ge x$。

若 $a_i\le w$，则 $a_j\ge x-w$。

若 $v\ge w,a_j\ge x-w$，则 $a_j\ge x-v$。

所以只需要考虑 $a_j\ge x-w$。

于是 $x-w\le 1$ 时直接忽略，$x-w\le k$ 时 $(i,w+1,0)\rightarrow(j,x-w,1)$ ，否则类似第 3 类操作。

反向同理。
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,l,r) for(int i=(r);i>=(l);i--)
#define pb push_back
#define clr clear
using namespace std;
const int N=1e6+5;
int n,m,k;
int f(int x,int y,int z){
	return n*(k+2)*z+(x-1)*(k+2)+(y+1);
}
vector<int>g[N];
void makeneq(int pos,int val){
	if(1<=val&&val<=k){
		g[f(pos,val,1)].pb(f(pos,val+1,1));
		g[f(pos,val+1,0)].pb(f(pos,val,0));
	}
}
int dfn[N],low[N],Tim;
int stk[N],top;
bitset<N>mk;
int col[N],idx;
void tarjan(int u){
	dfn[u]=low[u]=++Tim;
	stk[++top]=u;
	mk[u]=1;
	for(auto v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(mk[v]){
			low[u]=min(low[u],low[v]);
		}
	}
	if(dfn[u]==low[u]){
		idx++;
		while(stk[top]!=u){
			col[stk[top]]=idx;
			mk[stk[top]]=0;
			top--;
		}
		col[u]=idx;
		mk[u]=0;
		top--;
	}
}
bool cmp(int x,int y){
	return x>y;
}
void slv(){
	scanf("%d %d %d",&n,&m,&k);
	int nds=f(n,k+1,1);
	rep(i,1,nds){
		g[i].clr();
	}
	rep(i,1,n){
		rep(j,0,k){
			g[f(i,j,0)].pb(f(i,j+1,0));
			g[f(i,j+1,1)].pb(f(i,j,1));
		}
		g[f(i,0,0)].pb(f(i,0,1));
		g[f(i,1,0)].pb(f(i,1,1));
		g[f(i,k+1,1)].pb(f(i,k+1,0));
	}
	rep(i,1,n-1){
		rep(j,1,k){
			g[f(i,j,1)].pb(f(i+1,j,1));
			g[f(i+1,j,0)].pb(f(i,j,0));
		}
	}
	while(m--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int pos,val;
			scanf("%d %d",&pos,&val);
			makeneq(pos,val);
		}
		if(op==2){
			int x,y,val;
			scanf("%d %d %d",&x,&y,&val);
			rep(w,1,k){
				if(w>=val){
					makeneq(x,w);
				}
				else if(w+k>val){
					g[f(x,w,1)].pb(f(y,val-w+1,0));
					g[f(y,val-w+1,1)].pb(f(x,w,0));
				}
			}
			swap(x,y);
			rep(w,1,k){
				if(w>=val){
					makeneq(x,w);
				}
				else if(w+k>val){
					g[f(x,w,1)].pb(f(y,val-w+1,0));
					g[f(y,val-w+1,1)].pb(f(x,w,0));
				}
			}
		}
		if(op==3){
			int x,y,val;
			scanf("%d %d %d",&x,&y,&val);
			rep(w,1,k){
				if(w+k<val){
					makeneq(x,w);
				}
				else if(w<val-1){
					g[f(x,w+1,0)].pb(f(y,val-w,1));
					g[f(y,val-w,0)].pb(f(x,w+1,1));
				}
			}
			swap(x,y);
			rep(w,1,k){
				if(w+k<val){
					makeneq(x,w);
				}
				else if(w<val-1){
					g[f(x,w+1,0)].pb(f(y,val-w,1));
					g[f(y,val-w,0)].pb(f(x,w+1,1));
				}
			}
		}
	}
	Tim=0;
	mk=0;
	idx=0;
	rep(i,1,nds){
		dfn[i]=0;
		low[i]=0;
		sort(g[i].begin(),g[i].end(),cmp);
	}
	per(i,1,nds){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	rep(i,1,n){
		bool fd=0;
		rep(j,1,k){
			if(col[f(i,j,0)]==col[f(i,j,1)]){
				printf("-1\n");
				return ;
			}
			if(col[f(i,j,1)]<col[f(i,j,0)]){
				fd=1;
			}
		}
		if(!fd){
			printf("-1\n");
			return ;
		}
	}
	rep(i,1,n){
		per(j,1,k){
			if(col[f(i,j,1)]<col[f(i,j,0)]){
				printf("%d ",j);
				break;
			}
		}
	}
	putchar('\n');
}
int main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

学到了 2-sat 的一种新用法，可以用来解决此类求值问题。

对每个 
$a_
i$，设 
$k$
 个 bool 变量，其中 
$b_{
i
,
j}$
 表示 
$a_
i$
 是否 $\le j4$。于是所有条件都容易满足。复杂度 
$O
(
(
n
+
m
)
k
)$。

需要注意的是，此类问题不能设 
$b_{
i
,
j}$
 表示 
$a_
i$
 是否 
$=
j$。因为 2-sat 的要求是所有约束同时成立，故无法表示不等式。

另外，将一个非 bool 变量拆成若干个 bool 变量，一定要注意它们之间的联系，充分思考后得出等价刻画，否则极易遗漏。

---

## 作者：Aigony (赞：0)

~~调不出来。调不出来。调不出来。~~

发现 $k\le 10$，从值域上下手。第一个操作告诉我们差分约束是不可行的，考虑对所有变量拆点，设出共 $nk$ 个 `bool` 变量，其中 $A_{i,j}$ 表示 $[a_i\le j]$。这里不设为 $[a_i=j]$，是因为这样难以刻画「一些变量中恰有一个为 $1$」的条件。

那么对于同一个 $i$，一定是一个前缀 $j$ 的值为 $0$，后面为 $1$。故连边 $A_{i,j,1}\to A_{i,j+1,1}$，且有 $A_{i,k}$ 恒为 $1$。

序列递增，有 $A_{i,j,1}\to A_{i,j-1,1}$。

对于 $1$ 操作，实质上是保证 $A_{i,x}=A_{i,x-1}$，即 $A_{i,x,1}\to A_{i,x-1,1},A_{i,x,0}\to A_{i,x-1,0}$。

另外两个操作本质相同，这里以 $2$ 操作为例：枚举一个变量 $s$。若 $a_i>s$，则有 $a_j\le x-s-1$。连边即为 $A_{i,s,0}\to A_{j,x-s-1,1}$。当然，下标越界的情况要进行若干特判。

跑 2-SAT，时间复杂度 $\mathcal{O}(nk)$。

```cpp
const int N=4e5+5;
int T,n,m,k,a[N];
vector<int> e[N];
il int get(int x,int y,int tp) {return (x-1)*k+y+tp*n*k;}
il void add(int x,int p,int a,int y,int q,int b)
{
    if(x<1||x>n||y<1||y>n||p<1||p>k||q<1||q>k) return;
    e[get(x,p,a)].push_back(get(y,q,b));
    e[get(y,q,b^1)].push_back(get(x,p,a^1));
}
int Ans[40005][15];
int dfn[N],low[N],tot,in[N];
int num,bel[N]; 
stack<int> q;
void tarjan(int u)
{
    dfn[u]=low[u]=++tot,in[u]=1; q.push(u);
    for(auto v:e[u]) 
    {
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(in[v]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        num++;
        while("qwq")
        {
            int x=q.top(); q.pop();
            in[x]=0,bel[x]=num;
            if(x==u) break;
        }
    }
}
il void solve()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=2*n*k;i++) e[i].clear(),dfn[i]=0; tot=0,num=0;
    for(int i=1;i<=n;i++)
    {
        e[get(i,k,0)].push_back(get(i,k,1));
        for(int j=1;j<k;j++) add(i,j,1,i,j+1,1);
    }
    for(int i=2;i<=n;i++)
        for(int j=1;j<=k;j++) add(i,j,1,i-1,j,1);
    while(m--)
    {
        int op=read();
        if(op==1)
        {
            int i=read(),x=read();
            if(x>1) add(i,x,1,i,x-1,1);
            else e[get(i,x,1)].push_back(get(i,x,0));
        }
        else if(op==2)
        {
            int i=read(),j=read(),x=read();
            for(int k=1;k<=min(x,::k);k++)
            {
                if(x-k-1>=1) add(i,k,0,j,min(::k,x-k-1),1);
                else 
                {
                    e[get(i,k,0)].push_back(get(i,k,1));
                    if(x>1) e[get(j,x-1,0)].push_back(get(j,x-1,1));
                }
            }
        }
        else
        {
            int i=read(),j=read(),x=read();
            for(int k=1;k<=min(x,::k);k++)
            {
                if(x-k-1>=1&&x-k-1<::k) add(i,k,1,j,x-k-1,0);
                else if(x-k-1>=::k) e[get(i,k,1)].push_back(get(i,k,0));
            }
        }
    }
    for(int i=1;i<=2*n*k;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)   
    {
        Ans[i][0]=0;
        for(int j=1;j<=k;j++)
        {
            if(bel[get(i,j,0)]==bel[get(i,j,1)]) {printf("-1\n");return;}
            else if(bel[get(i,j,0)]<bel[get(i,j,1)]) Ans[i][j]=0;
            else Ans[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k;j++) if(Ans[i][j]&&!Ans[i][j-1]) a[i]=j;
    for(int i=1;i<=n;i++) printf("%d ",a[i]); printf("\n");
}
int main() {T=read();while(T--) solve();return 0;}
```

---

