# [ABC298Ex] Sum of Min of Length

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_h

$ N $ 頂点の木が与えられます。頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

また、この木における頂点 $ x $ と頂点 $ y $ の距離を $ d(x,y) $ で表します。ただし、頂点 $ x $ と頂点 $ y $ の距離とは、頂点 $ x $ から頂点 $ y $ までの最短パス上の辺の本数のことをいいます。

$ Q $ 個のクエリが与えられるので、順番に答えてください。$ i $ 番目のクエリは以下で説明されます。

- 整数 $ L_i,\ R_i $ が与えられます。 $ \displaystyle\sum_{j\ =\ 1}^{N}\ \min(d(j,\ L_i),\ d(j,\ R_i)) $ の値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i,\ L_i,\ R_i\ \leq\ N $
- 与えられるグラフは木
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 番目のクエリについて説明します。 $ d(1,\ 4)\ =\ 2 $、$ d(1,\ 1)\ =\ 0 $ より $ \min(d(1,\ 4),\ d(1,\ 1))\ =\ 0 $ です。 $ d(2,\ 4)\ =\ 2 $、$ d(2,\ 1)\ =\ 2 $ より $ \min(d(2,\ 4),\ d(2,\ 1))\ =\ 2 $ です。 $ d(3,\ 4)\ =\ 1 $、$ d(3,\ 1)\ =\ 3 $ より $ \min(d(3,\ 4),\ d(3,\ 1))\ =\ 1 $ です。 $ d(4,\ 4)\ =\ 0 $、$ d(4,\ 1)\ =\ 2 $ より $ \min(d(4,\ 4),\ d(4,\ 1))\ =\ 0 $ です。 $ d(5,\ 4)\ =\ 1 $、$ d(5,\ 1)\ =\ 1 $ より $ \min(d(5,\ 4),\ d(5,\ 1))\ =\ 1 $ です。 $ 0\ +\ 2\ +\ 1\ +\ 0\ +\ 1\ =\ 4 $ であるため、$ 4 $ を出力します。

## 样例 #1

### 输入

```
5
3 4
4 5
2 5
1 5
3
4 1
1 2
5 3```

### 输出

```
4
6
3```

## 样例 #2

### 输入

```
8
4 2
4 1
5 6
6 1
7 6
8 1
3 7
7
8 4
4 4
7 2
4 4
5 3
4 4
6 1```

### 输出

```
14
16
10
16
14
16
8```

# 题解

## 作者：Pengzt (赞：5)

[ABC298Ex](https://www.luogu.com.cn/problem/AT_abc298_h)

这个 Ex 好水啊。

因为是求 $\sum\limits_{i = 1} ^ n\min \{d(i, L), d(i, R)\}$ 的值，考虑讨论 $d(i, L)$ 和 $d(i, R)$ 的大小。

令 $p = \text{LCA}(L, R)$，$dep_L > dep_R, dist = dep_L + dep_R - 2\times dep_p$，$now$ 满足 $dep_L - dep_{now} = \lfloor\dfrac{dist}{2}\rfloor$

则 $L$ 一定在 $now$ 的子树内，且对于 $\forall i\in \{\text{subtree}(now)\}$ 时均有 $d(i, L) \le d(i, R)$，否则 $d(i, L) > d(i, R)$。其中 $\text{subtree}(x)$ 表示 $x$ 的子树。

容易想到求一个点到其他点的距离和。

令 $val_i$ 表示 $\sum\limits_{j = 1}^{n} d(i, j)$。

在 dfs 时处理一下即可，显然可以做到 $\mathcal{O}(n)$。

最后再将 $dist$ 奇偶讨论一下即可。

时间复杂度：$\mathcal{O}(n + m\log n)$，可以使用线性 LCA 做到 $\mathcal{O}(n + m)$

[评测记录](https://www.luogu.com.cn/record/108598602)

---

## 作者：Daidly (赞：4)

> 给定一棵树，$q$ 次询问，每次给出 $L_i,R_i$，求：
> $$\sum_{j=1}^n\min(d(j,L_i),d(j,R_i))$$
> $1\leq n,q\leq 2\times10^5$

对于一次询问，每个数的贡献都是到 $L_i$ 或到 $R_i$ 的距离，可以通过 $L_i\to R_i$ 路径上的中点将 $1\sim n$ 分成两个集合，分别是离 $L$ 较近和离 $R$ 较近的，这样就将 $\min$ 转换掉了。

记 $F(x,y)$ 表示 $x$ 子树内的所有点到 $y$ 的距离和。然后分讨，假设 $L$ 离 $\text{LCA}(L_i,R_i)$ 远，$p$ 表示中点。

> $p$ 的计算方式是 $L$ 的 $\lfloor\frac{dis(L,R)-1}{2}\rfloor$ 级祖先，这里 $-1$ 是因为避免中点为 $\text{LCA}$ 导致的特殊情况。也就是说，我们可以保证 $p$ 不在 $R$ 子树内，$L$ 在 $p$ 子树内。

则有 $ans_i=F(p,L_i)+F(1,R_i)-F(p,R_i)$，离线下来，考虑如何求多组 $F(x,y)$。

- $y$ 在子树 $x$ 外：记 $f_x$ 表示子树 $x$ 内每个点到 $x$ 的距离之和，答案即为 $dis(x,y)\times siz_x+f_x$。

- $y$ 在子树 $x$ 内：一开始想复杂了，在 dfs 回溯过程中用线段树维护子树加等等，码了一百五六十行。其实有简单方法的，记 $g_x$ 表示整棵树每个点到 $x$ 的距离之和，$f_x,g_x$ 可以两遍 dfs 换根 dp 求出，然后加加减减就好了。

  具体的，$g_y=g_{x}+n-2siz_y$，答案为 $g_y-(g_x-f_x)-dis(x,y)\times(n-siz_x)$.

想对了思路的话，[代码](https://atcoder.jp/contests/abc298/submissions/40808171)写起来还是比较舒适的。

---

## 作者：harmis_yz (赞：2)

## 分析

模拟赛签到题。

考虑分讨。分两种情况：

1. $L=R$。
2. $L \ne R$。

对于第 $1$ 种情况，用换根 DP 求一个 $i$ 为根时所有点的深度和就行。

对于第 $2$ 种情况，钦定 $dep_R \ge dep_L $。

很显然，$R$ 为根的子树中所有点都是离 $R$ 更近。假设在 $L$ 到 $R$ 的路径上，除开 $L,R$ 的某个点为 $K$。那么 $K$ 的任何一个不在路径上的儿子 $W$ 为根的子树中的所有点的贡献都是 $dist_{i \to W}+dist_{W \to K}+\min(dist_{K\to L},dist_{K\to R})$。前面两项是定值，而后面一项选择的分界点一定是在 $L$ 到 $R$ 的路径上的中点。

那么就很显然了。令中点为 $M$，则 $M$ 为根的子树中所有点的贡献都为 $dist_{i \to R}$，其余所有点都为 $dist_{i\to L}$。

定义 $dsum_i$ 表示 $i$ 为根时所有点的深度和，$sum_i$ 表示 $i$ 为根子树中所有点到 $i$ 的距离和，$siz_i$ 表示 $i$ 为根子树的大小。

根据容斥，$dsum_R-(dsum_M-sum_M+(dep_R-dep_M)\times(n-siz_M))$ 就可以求出来 $M$ 为根的子树中所有点到 $R$ 的距离和。$dsum_M-sum_M$ 将除 $M$ 为根子树外所有点到 $M$ 的距离，而 $dsum_R$ 中也有这个，但每一个不在 $M$ 子树中的点距 $R$ 的距离都会比距 $M$ 的距离多 $dep_R-dep_M$，所以 $dsum_M-sum_M+(dep_R-dep_M)\times(n-siz_M)$ 减掉了 $M$ 为根子树外的点到 $R$ 的距离和。

然后距离 $L$ 更近的那些点，和 $R$ 的情况差不多。通过 $dsum_L,sum_M,siz_M$ 容斥即可。结果是：$dsum_L-(sum_M+siz_M\times dist_{M\to L})$。

复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;
#define D(x,y) ((dep[x]+dep[y]-2*dep[lca(x,y)]))

const int N=2e5+10,M=20;
int n,m;
int ne[N<<1],e[N<<1],h[N],idx;
int dep[N],f[N][M],siz[N];
int sum[N];//i子树中与i的距离和
int dsum[N];//i为根时的距离和 

il void add(int a,int b){
	ne[++idx]=h[a],e[idx]=b,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,h[b]=idx;
}
il void dfs(int now,int fa){
	dep[now]=dep[fa]+1,siz[now]=1,f[now][0]=fa;
	for(re int i=1;i<M;++i) f[now][i]=f[f[now][i-1]][i-1];
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);
		siz[now]+=siz[j];
		sum[now]+=sum[j]+siz[j];
	}
	return ;
}
il void dfs2(int now,int fa){
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dsum[j]=dsum[now]-siz[j]+(n-siz[j]);
		dfs2(j,now);
	}
	return ;
}
il int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re int i=19;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re int i=19;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
il int up(int x,int y){
	int now=0;
	while(y){
		if(y&1) x=f[x][now];
		y>>=1,++now;
	}
	return x;
}

il void solve(){
	n=rd;
	for(re int i=1,a,b;i<n;++i)
		a=rd,b=rd,add(a,b);
	dfs(1,0),dsum[1]=sum[1],dfs2(1,0);
	m=rd;
	for(re int i=1;i<=m;++i){
		int l=rd,r=rd;
		if(dep[l]>dep[r]) swap(l,r);
		if(l==r) printf("%lld\n",dsum[l]);
		else{
			int ans=0,dis=D(l,r)-1;
			int m_=up(r,dis/2);//中点 
			ans+=dsum[r]-(dsum[m_]-sum[m_]+(dep[r]-dep[m_])*(n-siz[m_]));//离R近的 
			ans+=dsum[l]-(sum[m_]-siz[m_]*D(m_,l));//离L近的 
			printf("%lld\n",ans);
		}
	}
	return ;
}

signed main(){
// 	freopen("sum.in","r",stdin);
// 	freopen("sum.out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：ダ月 (赞：2)

### 题意概要：

给定一棵有 $n$ 个结点的树，共 $m$ 次询问，每次询问结点 $L,R$，求 $\begin{aligned}\sum_{i=1}^n\min\{d(i,L),d(i,R)\}\end{aligned}$，其中 $d(x,y)$ 表示 $x$ 结点到 $y$ 结点的距离。

### 题目分析：

记每个结点的深度为 $dep_i$，子树大小为 $sz_i$，不妨令 $dep_L\le dep_R$。

我们令 $\begin{aligned}f(x)=\sum_{i=1}^nd(i,x)\end{aligned}$，显然，这个可以在 $O(n)$ 时间内预处理 $f(1)\sim f(n)$。

我们考虑这个 $\min$ 的临界情况。

- 若 $d(L,R)$ 为偶数。

那么显然临界点在 $L$ 到 $R$ 的中点上。因为不妨令 $dep_L\le dep_R$，所以就是 $R$ 结点 $\frac{d(L,R)}{2}$ 级祖先。这个可以 $O(\log n)$ 内完成查询。记这个中点为 $M$。有个结论 

$\begin{aligned}\min\{d(i,L),d(i,R)\}&=d(i,L)+d(i,R)-d(i,M)-\frac{d(L,R)}{2}\end{aligned}$

理解一下，就是如果 $i$ 在 $L$ 到 $R$ 中间部分上，$d(i,L)+d(i,R)-\frac{d(L,R)}{2}=\frac{d(L,R)}{2}$。无论 $i$ 更侧重于谁， $\frac{d(L,R)}{2}-d(i,M)$ 都是最终贡献。如果不在 $L$ 到 $R$ 中间部分，那么不妨让结点在 $L$ 的子树下， $d(i,L)+d(i,R)-\frac{d(L,R)}{2}-d(i,M)=2 d(i,L)+\frac{d(L,R)}{2}-(\frac{d(L,R)}{2}-d(i,L))=d(i,L)$。

因此

$\begin{aligned}\sum_{i=1}^n\min\{d(i,L),d(i,R)\}&=f(L)+f(R)-f(M)-\frac{n\times d(L,R)}{2}\end{aligned}$

- 若 $d(L,R)$ 为奇数。

显然这个临界点在 $R$ 的 $\frac{d(L,R)-1}{2}$ 与 $\frac{d(L,R)+1}{2}$ 级的祖先中间，分别记这两个点为 $M_1,M_2$。

$\begin{aligned}\sum_{i=1}^n\min\{d(i,L),d(i,R)\}&=f(L)+f(R)-f(M_1)-\frac{n(d(L,R)-1)}{2}-sz(M_1)\end{aligned}$.

证明方式跟上面类似。无非多减去了 $M_1$ 与真正的中点带来的贡献。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
//===
//缺省源
//===
int n,m;
vector<int> a[N];
int dep[N],sz[N],st[N][22];
ll S1[N],S2[N];
void dfs1(int x,int F){
	st[x][0]=F;dep[x]=dep[F]+1;sz[x]=1;S1[x]=dep[x];
	for(int i=1;i<=20;i++)st[x][i]=st[st[x][i-1]][i-1];
	for(auto y:a[x]){
		if(y==F)continue;
		dfs1(y,x);
		S1[x]+=S1[y];sz[x]+=sz[y];
	}
}void dfs2(int x){
	int F=st[x][0];
	if(x==1) S2[x]=S1[x];
	else S2[x]=S2[F]+(sz[1]-sz[x])-sz[x];
	for(auto y:a[x]){
		if(y==F)continue;
		dfs2(y);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])x^=y^=x^=y;
	for(int i=20;~i;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=st[x][i];
	if(x==y)return x;
	for(int i=20;~i;i--)
		if(st[x][i]!=st[y][i])
			x=st[x][i],
			y=st[y][i];
	return st[x][0];
}int D(int x,int y,int l){
	if(l==-1)l=LCA(x,y);
	return dep[x]+dep[y]-2*dep[l];
}int Anc(int x,int k){
	for(int i=20;~i;i--)
		if((1<<i)<=k)
			k-=(1<<i),
			x=st[x][i];
	return x;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x].pd(y),a[y].pd(x);
	}
	dep[0]=-1;
	dfs1(1,0);dfs2(1);scanf("%d",&m);
	while(m--){
		int L,R;scanf("%d%d",&L,&R);
		int l=LCA(L,R);
		int d=D(L,R,l);
		if(dep[L]>dep[R])L^=R^=L^=R;
		if(d%2==0){
			int M=Anc(R,d>>1);
			printf("%lld\n",S2[L]+S2[R]-S2[M]-1ll*n*d/2);
		}
		else{
			int M1=Anc(R,d-1>>1),M2=Anc(R,d+1>>1);
			printf("%lld\n",S2[L]+S2[R]-S2[M1]-1ll*n*(d-1)/2-sz[M1]);
		}
	}return 0;
}
```


---

## 作者：dengchengyu (赞：1)

## AT_abc298_h [ABC298Ex] Sum of Min of Length 题解

很简单的树上 DP 练习题。

找出 $L_i,R_i$ 的路径上的中点，中点左侧走向 $L_i$，右侧走向 $R_i$。

于是处理出子树大小、每个点到所有点的距离和、每个点到子树所有点的距离和、每个点到子树外所有点的距离和，知道中点后就能 $O(1)$ 算答案。

通过一些简单的分讨就可以倍增找到路径中点。

复杂度 $O(n\log n)$。

代码：

```cpp
const int N=2e5+5;
int n,Q;
vi G[N];
int fa[N],sz[N],dep[N];
int pa[N][19];
ll f[N],g[N],h[N];
int getsz(int x,int y) {
	if(fa[x]==y) return sz[x];
	return n-sz[y];
}
int getval(int x,int y) {
	if(fa[x]==y) return g[x]+sz[x];
	return h[y];
}
int getfa(int x,int y) {
	for(int i=0;y;++i,y>>=1) if(y&1) x=pa[x][i];
	return x;
}
void dfs(int x,int y) {
	sz[x]=1, fa[x]=y, dep[x]=dep[y]+1;
	pa[x][0]=y;
	fu(i,1,19) pa[x][i]=pa[pa[x][i-1]][i-1];
	for(int v:G[x]) {
		if(v==y) continue;
		dfs(v,x);
		sz[x]+=sz[v];
		g[x]+=g[v]+sz[v];
	}
}
void dfs2(int x,int y) {
	if(x>1) h[x]=h[y]+g[y]-g[x]+n-2*sz[x];
	f[x]=h[x]+g[x];
	for(int v:G[x]) {
		if(v==y) continue;
		dfs2(v,x);
	}
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	x=getfa(x,dep[x]-dep[y]);
	if(x==y) return x;
	fd(i,18,0) if(pa[x][i]!=pa[y][i]) x=pa[x][i],y=pa[y][i];
	return pa[x][0];
}
int getdis(int x,int y) {
	int l=lca(x,y);
	return dep[x]+dep[y]-2*dep[l];
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n;
	fu(i,1,n) {
		int u,v;
		cin>>u>>v;
		G[u].pb(v),G[v].pb(u);
	}
	dfs(1,0);
	dfs2(1,0);
	cin>>Q;
	while(Q--) {
		int x,y; cin>>x>>y;
		if(x==y) {cout<<f[x]<<'\n'; continue;}
		int l=lca(x,y),dis=dep[x]+dep[y]-2*dep[l];
		int z=0,w=0;
		if(dep[x]<dep[y]) swap(x,y);
		z=getfa(x,dis/2),w=getfa(x,dis/2+1);
		if(z==l) w=getfa(y,dep[y]-dep[l]-1);
		int d1=getdis(x,z),d2=getdis(w,y);
		cout<<f[x]+f[y]-getval(z,w)-d2*getsz(z,w)-getval(w,z)-d1*getsz(w,z)<<'\n';
	}
	return 0;
}
```

---

## 作者：BYR_KKK (赞：1)

>多次询问 $L,R$，求 $\sum\limits_{i}\min(d(i,L),d(i,R))$。

不失一般性的令 $dep_L\ge dep_R$。

考虑 $i$ 到 $L/R$ 的路径是怎样的。一定是 $i$ 到 $L\rightarrow$ 上的某一点 $x$ 再到 $L/R$。

>如果按照每个点到达 $L/R$ 对其进行染色，则每种颜色都只有一个联通块，换句话说，颜色是树的一个划分。

考虑 $L\rightarrow R$ 路径上的染色情况，一定有一个阈值 $m$，满足路径上到 $L$ 距离不超过 $m$ 的点到达 $L$，其余到达 $R$。利用倍增求出 $L$ 的树上 $m$ 级祖先 $x$，设 $\operatorname{lca}(L,R)=k$，则 $x$ 必然位于 $L\rightarrow k$ 的路径上（保证了 $dep_L\ge dep_R$）。不难发现所有位于 $x$ 子树内的点都会走到 $L$，其余都会走到 $R$。

但是如果 $x=k$，由于 $R$ 也在 $x$ 的子树中，因此会出错。但是此时当且仅当 $d(L,x)=d(x,R)$，我们选择 $L\rightarrow R$ 路径上 $x$ 的前一个点，即 $L$ 的 $m-1$ 级祖先即可。

因此答案就是 $\sum\limits_{i\in\text{subtree}_x}d(i,L)+\sum\limits_{i\notin\text{subtree}_x}d(i,R)$。

$i\notin\text{subtree}_x$ 并不好处理，将答案改写为 $\sum\limits_{i\in\text{subtree}_x}d(i,L)+\sum\limits_{i}d(i,R)-\sum\limits_{i\in\text{subtree}_x}d(i,R)$。

此时式子已经相较于一开始变得更好处理，只需要求出一棵子树的所有点到子树内某点的距离和即可。即 $\sum\limits_{i\in\text{subtree}_x}d(1,i)+d(1,p)-2\times d(1,\operatorname{lca}(i,p))$。

$\sum\limits_{i\in\text{subtree}_x}d(1,i)+d(1,p)$ 是好求的，考虑怎么求 $\sum\limits_{i\in\text{subtree}_x}d(1,\operatorname{lca}(i,p))$。

对 $\operatorname{lca}(i,p)$ 拆贡献。设 $p\rightarrow x$ 经过的点为 $\{\alpha_z\}$。则为 $\sum\limits_{1\le j\le z}d(1,\alpha_j)\times(s_{\alpha_j}-s_{\alpha_{j-1}})$。

其中 $s_i$ 代表 $i$ 的子树大小，$s_{\alpha_0}=0$。

充分发挥人类智慧，改写为 $s_{\alpha_z}\times d(1,\alpha_z)+\sum\limits_{1\le i<z}s_{\alpha_i}\times(d(1,\alpha_i)-d(1,\alpha_{i+1}))$。

发现路径上的点满足 $\alpha_i=fa_{\alpha_{i-1}}$，且 $\alpha_z=x$。因此得到 $s_x\times d(1,x)+\sum\limits_{1\le i<z}s_{\alpha_i}$。维护 $t_i=\sum\limits_{1\rightarrow i}s_i$，则得到 $s_x\times d(1,x)+t_p-t_x$。

注意，如果 $p$ 在 $x$ 的子树外，则应该加上 $d(p,x)\times s_x$。

如果令 $f(x,p)$ 代表上面所写的 $\sum\limits_{i\in\text{subtree}_x}d(i,p)$。则答案为 $f(x,L)+f(1,R)-f(x,R)$。

时间复杂度 $O(q\log n)$，瓶颈在于倍增求树上 $k$ 级祖先。

```cpp
#include <bits/stdc++.h>
#define int long long
#define debug(...) fprintf(stderr,##__VA_ARGS__)

bool Mbe;

const int inf=1e18;

const int maxn=2e5+10;

std::vector<int>a[maxn];

int t[maxn],dep[maxn],s[maxn],f[maxn][20],lg[maxn],n,q,h[maxn];

template<typename T,typename I>
void chkmin(T &a,I b){
	a=std::min(a,b);
}

template<typename T,typename I>
void chkmax(T &a,I b){
	a=std::max(a,b);
} 

namespace ST{
	void dfs(int p,int fa){
		f[p][0]=fa,dep[p]=dep[fa]+1;
		s[p]=1;
		h[p]=dep[p];
		for(int i:a[p]){
			if(i==fa) continue;
			dfs(i,p);
			s[p]+=s[i];
			h[p]+=h[i];
		}
//		t[p]=t[fa]+s[p];
	}
	void dfs2(int p,int fa){
		t[p]=t[fa]+s[p];
		for(int i:a[p]){
			if(i==fa) continue;
			dfs2(i,p);
		}
	}
	void init(int rt){
		dfs(rt,rt);
		dfs2(rt,rt);
		lg[0]=-1;
		for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int j=1;j<20;j++)
			for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	}
	int kth(int p,int k){
		for(int i=19;i>=0;i--)
			if(k>=(1ll<<i)) k-=(1ll<<i),p=f[p][i];
		return p;
	}
	int lca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		for(int i=19;i>=0;i--)
			if(dep[f[x][i]]>=dep[y]) x=f[x][i];
		if(x==y) return x;
		for(int i=19;i>=0;i--)
			if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
		return f[x][0];
	}
	int dis(int x,int y){
		return dep[x]+dep[y]-dep[lca(x,y)]*2;
	}
	int query(int x,int p){//求出 x 子树中的所有点到 p 的距离和 
		int res=s[x]*(dep[x]-1)+t[p]-t[x];
//		debug("qwq res=%lld x=%lld p=%lld\n",res,x,p);
		if(lca(x,p)!=x) res=(dep[x]-1)*s[x];
		res=h[x]-s[x]+s[x]*dis(1,(lca(x,p)==x?p:x))-2*res;
		if(lca(x,p)!=x) res+=s[x]*dis(p,x);
//		debug("res=%lld x=%lld h%lld s=%lld lca=%lld\n",res,x,h[x],s[x],lca(x,p));
		return res;
	}
}

void check_s_t(){
	debug("checking\n");
	for(int i=1;i<=n;i++) debug("i=%lld s=%lld t=%lld h=%lld\n",i,s[i],t[i],h[i]);
}

bool Men;

signed main(){
	debug("%.8f\n",((&Men-&Mbe)/1048576.0));
	std::cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		std::cin>>u>>v;
		a[u].push_back(v),a[v].push_back(u);
	}
	ST::init(1);
//	debug("check:%lld\n",ST::query(4,1));
//	check_s_t();
	std::cin>>q;
	while(q--){
		int x,y;
		std::cin>>x>>y;
		if(dep[x]<dep[y]) std::swap(x,y);
		int k=ST::lca(x,y);//x y 的 lca 
//		debug("k=%lld\n",k);
		int m=ST::dis(x,y)/2;//阈值 
		int _x=ST::kth(x,m);//树上阈值级祖先 
//		debug("lca=%lld 阈值=%lld kth=%lld Q1=%lld Q2=%lld Q3=%lld 大家觉得呢:%lld\n",k,m,_x,ST::query(_x,x),ST::query(1,y),ST::query(_x,y),114);
		int ans=inf;
		if(_x==k) _x=ST::kth(x,m-1);
		chkmin(ans,ST::query(_x,x)+ST::query(1,y)-ST::query(_x,y));
//		chkmin(ans,ST::query(_x,x)+ST::query(1,y)-2*ST::query(_x,y));
//		if(ST::dis(x,y)&1) _x=f[_x][0],chkmin(ans,ST::query(_x,x)+ST::query(1,y)-2*ST::query(_x,y));
		std::cout<<ans<<"\n";
	}
//	debug("%.11lfms %.8f\n",clock(),(clock()/CLOCKS_PER_SEC)*1e3);
}
/*
North London forever
*/
```

---

## 作者：sunkuangzheng (赞：1)

**【题目大意】**

$n$ 个点的树，$q$ 次询问，每次询问给出 $u,v$，求 $\sum \limits_{i=1}^n \min(\operatorname{dis}(u,i),\operatorname{dis}(v,i))$。$1 \le n,q \le 2 \times 10^5$。

**【题解】**

一遍过编译一遍过样例一遍 AC，写这题真的太舒服啦！！111

考虑我们把点分为两种类型：距离 $u$ 近和距离 $v$ 近。容易发现两部分各自构成连通块，且分界点是 $u,v$ 的路径中点，那么分开计算贡献。为了方便，以下令 $dep_u \ge dep_v,d = \operatorname{mid}(u,v),l = \operatorname{lca}(u,v)$。计算 $d,l$ 可以简单倍增完成。

$\operatorname{dis}(u,v) = dep_u+dep_v-2dep_{\operatorname{lca}(u,v)}$，显然前两部分可以直接算，最后一部分分类计算。 $T_d$ 指的是 $d$ 的子树。

- 距离 $u$ 更近的点都在 $d$ 的子树里，也即求 $\sum \limits_{v \in T_d} dep_{{\operatorname{lca}(u,v)}}$，枚举 $\operatorname{lca}(u,v)$，考虑有多少符合条件的 $v$，容易发现这个和式的值等于 $u \to d$ 的链上 $siz_u$ 的和，加上 $(dep_d-1)siz_u$。

- 距离 $v$ 更近的点都在 $d$ 的子树外。我们先计算 $\sum \limits_{i=1}^n dep_{\operatorname{lca}(u,i)}$，再减去 $i \in T_d$ 部分 $i$ 的贡献。第一部分的计算和上面一样，第二部分由于 $d$ 子树内任意点和 $v$ 的 $\operatorname{lca}$ 都是 $l$，所以贡献是 $-siz_d \cdot dep_{l}$。

据此计算即可。时间复杂度 $\mathcal O((n+q) \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 16.02.2024 20:17:27
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,fa[N][22],siz[N],dep[N],u,v,q; ll sm[N],sum; vector<int> g[N];
void dfs(int u,int f){
    fa[u][0] = f,siz[u] = 1,dep[u] = dep[f] + 1,sum += dep[u];
    for(int i = 1;i <= __lg(dep[u]);i ++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}void dfs2(int u,int f){sm[u] = sm[f] + siz[u]; for(int v : g[u]) if(v != f) dfs2(v,u);}
int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    while(dep[u] > dep[v]) u = fa[u][__lg(dep[u] - dep[v])];
    for(int i = __lg(dep[u]);i >= 0;i --) if(fa[u][i] != fa[v][i]) u = fa[u][i],v = fa[v][i];
    return (u == v ? u : fa[u][0]);
}int kfa(int u,int k){
    for(int i = __lg(dep[u]);i >= 0;i --) if((k >> i) & 1) u = fa[u][i];
    return u;
}int dis(int u,int v){return dep[u] + dep[v] - 2 * dep[lca(u,v)];}
void los(){
    cin >> n; 
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    dfs(1,0),dfs2(1,0);
    for(cin >> q;q --;){
        if(cin >> u >> v,dep[u] < dep[v]) swap(u,v);
        int di = dis(u,v),d = kfa(u,di / 2);
        auto calc = [&](int u,int v){return sm[v] - sm[fa[u][0]];};
        ll k = calc(d,u) + 1ll * siz[d] * (dep[d] - 1),p = calc(1,v) - 1ll * siz[d] * dep[lca(u,v)];
        cout << 1ll * dep[u] * siz[d] + 1ll * dep[v] * (n - siz[d]) + sum - 2 * (k + p) << "\n";
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```


---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/article/uby7sza8) $|$ 
[题目传送门](/problem/AT_abc298_h) $|$ 
[我的其他题解](/user/523641#article.2)

模拟赛搬了这个题，来水一篇题解。

------------
### ${\color{#00CD00}\text{思路}}$

不难想到考虑哪些点距离 $L$ 更近，哪些点距离 $R$ 更近。

不妨令 $1$ 号点为根，$L$ 为 $L,R$ 中深度更大的点。定义 $u$ 为 **$L,R$ 两点之间简单路径的中点**，它可以通过 $L$ 向上跳 $\lfloor\frac{\operatorname{dis}(L, R)}{2}\rfloor$ 个点得到。

显然，在 $L,R$ 两点的简单路径上的点，$[L, u]$ 这些点距离 $L$ 更近，$(u,R]$ 这些点距离 $R$ 更近。

进一步可以发现，**所有在 $u$ 子树内的点都距离 $L$ 更近，在 $u$ 子树外的点距离 $R$ 更近**。

![](https://cdn.luogu.com.cn/upload/image_hosting/v3r7t7n1.png)

（图丑勿怪）

于是这个题就做完了。跑一遍换根 DP，对于每个点 $u$，预处理出 **$u$ 子树内所有点到 $u$ 的距离之和**以及**树上所有点到 $u$ 的距离之和**，查询时 $O(1)$ 计算 $L$ 和 $R$ 的答案就行了。

具体实现见代码。

------------
### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
long long n, m;
int dep[N], sz[N], f[N][20];
int s[N], ss[N];
// s[u]: u 子树内所有点到 u 的距离之和
// ss[u]: 树上所有点到 u 的距离之和 
vector<int> G[N];
void dfs(int u, int fa){ //第一遍 dfs，预处理倍增，计算 s[] 
	dep[u] = dep[fa] + 1, sz[u] = 1;
	for(int v: G[u]){
		if(v == fa) continue;
		f[v][0] = u; // 倍增预处理 
		for(int i=1; i<=19; i++) f[v][i] = f[f[v][i-1]][i-1];
		dfs(v, u); sz[u] += sz[v]; s[u] += s[v] + sz[v];
	}
}
void dfss(int u, int fa){ //第二遍 dfs（换根 dp），计算 ss[]
	for(int v: G[u]){
		if(v == fa) continue;
		ss[v] = ss[u] - 2 * sz[v] + n;
		dfss(v, u);
	}
}
int lca(int x, int y){ //求 x,y 的最近公共祖先 
	if(dep[x] < dep[y]) swap(x, y);
	for(int i=19; i>=0; i--) if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if(x == y) return x;
	for(int i=19; i>=0; i--) if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
int dis(int x, int y){ //求 x,y 之间的简单路径的长度 
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}
signed main(){
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<n; i++){
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, 0); ss[1] = s[1]; dfss(1, 0);
	for(cin >> m; m --> 0;){
		int L, R; cin >> L >> R;
		if(dep[L] < dep[R]) swap(L, R); //令 L 为深度更大的那个点 
		int jump = dis(L, R) / 2, u = L; //求 L,R 之间简单路径的中点 u 
		for(int i=19; i>=0; i--) if(jump >> i & 1) u = f[u][i];
		int resL = ss[L] - (ss[u] - s[u] + (n - sz[u]) * dis(L, u));
		int resR = ss[R] - (s[u] + sz[u] * dis(R, u));
		// 上面这一行的意思是：计算树上所有点到 R 的距离之和，减去 u 子树内所有点到 R 的距离之和
		//  (s[u] + sz[u] * dis(R, u))：u 子树内所有点到 u 的距离之和，加上每个点从 u 到 R 的距离之和
		// 计算 resL 的方法同理，稍微复杂一点 
		cout << resL + resR << "\n";
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

不同与其他题解，考虑暴力推式子然后树剖。

考虑分成两种情况考虑：

### $y$ 是 $x$ 的祖先 
那么不难得到 $x$ 控制的最远的点 $p=f(x,\frac{dep_x-dep_y}{2})$，$f(i,j)$ 表示 $i$ 的 $2^j$ 级祖先。那么 $x$ 的答案即为 $x$ 子树内的和 $p$ 子树内除开 $x$ 子树内的，$x$ 子树内的答案很好求，但是如何求出 $p$ 子树除开 $x$ 子树内的点到 $x$ 的距离和呢？不妨展开答案为：$sum_{u1}-sum_x-(k-1)(siz_{u1}-siz_x)+sum_{u2}-sum_{u1}-(k-3)(siz_{u2}-siz_{u1})+\dots+sum_p-sum_{u_{dep_u-dep_p-1}}-(k-2 \times len -1)(siz_p-siz_{u_{len-1}})$，其中 $sum_u$ 表示 $u$ 子树内的深度和，$u_i$ 表示 $x$ 节点的 $i$ 级祖先，$len$ 为 $x$ 和 $p$ 的深度差。

考虑合并答案变为：$sum_p-sum_x+(k-1)siz_x-(k-2\times len-1)-2 \times (siz_{u1}+siz_{u2}+\dots +siz_p)$，$(siz_{u1}+siz_{u2}+\dots +siz_p)$ 可以用树剖优化。$y$ 的贡献同理。

### $y$ 不是 $x$ 祖先

同理计算出 $x$ 控制的最远点 $p$，并用相同的方法算出贡献，$y$ 的贡献即为令 $p=1$ 时的贡献减去 $p$ 子树对 $y$ 的贡献。

时间复杂度 $O(m\log^2 n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10,M=22; 
int n,m; 
int mp[N]; 
int sum[N]; 
int top[N]; 
int h[N],idx=0; 
int id[N],cnt=0; 
int siz[N],son[N];  
int f[N][M],dep[N]; 
struct Edge{ 
	int to,ne; 
}e[N<<1]; 
struct Node{
	int l,r; 
	int w; 
}tr[N<<2]; 
il void add(int u,int v){ 
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il void dfs1(int u,int fa){ 
	siz[u]=1;  
	f[u][0]=fa,dep[u]=dep[fa]+1; sum[u]=dep[u]; 
	for(int j=1;j<M;j++) f[u][j]=f[f[u][j-1]][j-1]; 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		dfs1(to,u); siz[u]+=siz[to],sum[u]+=sum[to]; 
		if(siz[to]>siz[son[u]]) son[u]=to; 
	} 
} 
il void dfs2(int u,int fa,int Top){ 
	id[u]=++cnt; mp[cnt]=u; top[u]=Top; 
	if(son[u]) dfs2(son[u],u,Top); 
	for(int i=h[u];i!=-1;i=e[i].ne){
		int to=e[i].to; 
		if(to==fa||to==son[u]) continue; 
		dfs2(to,u,to); 
	} 
} 
il void build(int u,int l,int r){ 
	tr[u]={l,r}; 
	if(l==r){ 
		tr[u].w=siz[mp[l]]; 
		return ; 
	} int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	tr[u].w=tr[u<<1].w+tr[u<<1|1].w; 
} 
il int query(int u,int l,int r){ 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w; 
	int w=0,mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) w=query(u<<1,l,r); 
	if(r>mid) w+=query(u<<1|1,l,r); 
	return w; 
} 
il int qsec(int x,int y){ 
	int ans=0; 
	while(top[x]!=top[y]){ 
		if(dep[top[x]]<dep[top[y]]) swap(x,y); 
		ans+=query(1,id[top[x]],id[x]); 
		x=f[top[x]][0]; 
	} if(dep[x]>dep[y]) swap(x,y); 
	ans+=query(1,id[x],id[y]); return ans; 
} 
il int plc(int x,int k){ 
	if(k==-1) return x; 
	int p=0; 
	while(k){ 
		if(k&1) x=f[x][p]; 
		p++; k>>=1; 
	} return x; 
} 
il int LCA(int x,int y){ 
	if(dep[x]<dep[y]) swap(x,y); 
	x=plc(x,dep[x]-dep[y]); 
	if(x==y) return x; 
	for(int j=M-1;j>=0;j--) if(f[x][j]!=f[y][j]) x=f[x][j],y=f[y][j]; 
	return f[x][0]; 
} 
il int calc_in(int x){ return sum[x]-siz[x]*dep[x]; } 
il int calc_out(int x,int p){ 
	if(x==p) return 0; 
	int to=plc(x,dep[x]-dep[p]-1),k=dep[f[x][0]]; 
	int len=dep[x]-dep[p]-1; 
	int ans=sum[p]-sum[x]+(k-1)*siz[x]; 
	if(len>0) ans-=2*qsec(f[x][0],to); 
	ans-=(k-len*2-1)*siz[p]; return ans; 
} 
signed main(){ 
// 	freopen("sum.in","r",stdin); 
// 	freopen("sum.out","w",stdout); 
	memset(h,-1,sizeof h); 
	n=read(); 
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v),add(v,u); 
	dfs1(1,0),dfs2(1,0,1); build(1,1,n); 
	m=read(); 
	while(m--){ 
		int x=read(),y=read(); 
		if(dep[x]<dep[y]) swap(x,y); 
		int ans=0,rt=LCA(x,y); 
		if(rt==y){ 
			int p=plc(x,(dep[x]-dep[y])/2); 
			ans=calc_in(x)+calc_out(x,p)+calc_out(y,1); 
			ans+=(sum[y]-sum[p]-(siz[y]-siz[p])*dep[y]); 
		} else{ 
			int to=plc(y,dep[y]-dep[rt]-1); 
			int p=plc(x,(dep[x]+dep[y]-2*dep[rt])/2); 
			ans=calc_in(x)+calc_out(x,p)+calc_in(y); 
			ans+=calc_out(y,1); 
			ans-=(sum[p]-siz[p]*dep[rt]+siz[p]*(dep[y]-dep[rt])); 
		} printf("%lld\n",ans); 
	} return 0; 
} 
```

---

## 作者：xkcdjerry (赞：0)

很好想但是常数超大的 $O(n \log n)$ 做法。  

这个 $\min$ 很烦人，发现在链 $u,v$ 的中点 $l$ 靠近 $u$ 一侧有 $d(i,u) \leqslant d(i,v)$，否则 $d(i,u) \geqslant d(i,v)$。  
因此求出 $l$ 的位置即可转化为常数个子树到点的距离和。  
此处钦定 $u$ 为深度较大的点，$l$ 为 $u$ 的 $\lfloor \dfrac{d(u,v)-1}2 \rfloor$ 级祖先，即可在满足上述条件的情况下保证 $u$ 在 $l$ 子树内，$v$ 在 $l$ 子树外。  
这段需要 LCA 和树上 $k$ 级祖先，随便 $O(q \log n)$ 一做就行。

---
现在问题转化为求
$$\sum_{i \in subtree(l)} d(i,u)+\sum_{i \notin subtree(l)} d(i,v)$$

套路的通过 dfn 序把树上问题转化为区间问题：
$$\sum_{dfn_l \leqslant dfn_i < dfn_l+sz_l} d(i,u) + \sum_{dfn_i<dfn_l} d(i,v) + \sum_{dfn_i \geqslant dfn_l+sz_l} d(i,v)$$

把这三个区间询问离线下来挂在对应点上，考虑线段树优化换根：  
从 $u$ 的父亲转移到 $u$ 会导致满足 $dfn_u \leqslant d_i < dfn_u+sz_u$ 的 $d(i,u)$ 减少 $1$，否则增加 $1$。由于询问为区间和可以使用区间加区间查询线段树支持。

复杂度：时间 $O((n+q) \log n)$，空间 $O(n+q)$。  
刚开始使用的是倍增和线段树，常数极大，换成树剖和树状数组或能显著减小常数。

如果强制在线可以主席树，时间复杂度不变，空间复杂度变成 $O(q+n \log n)$。

代码：
```c++
#include <cstdio>
#include <vector>
#define N 200010
#define ll long long
using std::vector;
int n,q; vector<int> e[N];
int f[21][N],dep[N],dfn[N],sz[N],cur;
void dfs1(int x,int F)
{
    dep[x]=dep[F]+1, f[0][x]=F;
    dfn[x]=++cur, sz[x]=1;
    for(auto i:e[x]) if(i!=F)
        dfs1(i,x), sz[x]+=sz[i];
}
int lca(int u,int v)
{
    if(dep[u]<dep[v]) {int t=u; u=v; v=t;}
    for(int i=20;i>=0;i--) if(dep[f[i][u]]>=dep[v])
        u=f[i][u];
    if(u==v) return u;
    for(int i=20;i>=0;i--) if(f[i][u]!=f[i][v])
        u=f[i][u], v=f[i][v];
    return f[0][u];
}
int dis(int u,int v) {return dep[u]+dep[v]-2*dep[lca(u,v)];}
struct seg
{
    int l,r;
    ll add,sum;
}T[N*4];
void upd(int o) {T[o].sum=T[o<<1].sum+T[o<<1|1].sum+(T[o].r-T[o].l+1)*T[o].add;}
void init(int l,int r,int o)
{
    T[o].l=l, T[o].r=r;
    if(l==r) {T[o].sum=dep[l]; return;}
    int mid=(l+r)/2;
    init(l,mid,o<<1), init(mid+1,r,o<<1|1);
    upd(o);
}
void add(int l,int r,int v,int o)
{
    if(T[o].l==l&&T[o].r==r) {T[o].add+=v, T[o].sum+=1ll*(r-l+1)*v; return;}
    int mid=(T[o].l+T[o].r)/2;
    if(r<=mid) add(l,r,v,o<<1);
    else if(l>mid) add(l,r,v,o<<1|1);
    else add(l,mid,v,o<<1), add(mid+1,r,v,o<<1|1);
    upd(o);
}
ll ask(int l,int r,int o)
{
    if(T[o].l==l&&T[o].r==r) return T[o].sum;
    int mid=(T[o].l+T[o].r)/2; ll ans;
    if(r<=mid) ans=ask(l,r,o<<1);
    else if(l>mid) ans=ask(l,r,o<<1|1);
    else ans=ask(l,mid,o<<1)+ask(mid+1,r,o<<1|1);
    return ans+1ll*(r-l+1)*T[o].add;
}
ll ans[N]; struct Q{int l,r,i;}; vector<Q> query[N];
void dfs2(int x,int F)
{
    add(1,n,1,1); add(dfn[x],dfn[x]+sz[x]-1,-2,1);
    for(auto i:query[x]) ans[i.i]+=ask(i.l,i.r,1);
    for(auto i:e[x]) if(i!=F) dfs2(i,x);
    add(1,n,-1,1); add(dfn[x],dfn[x]+sz[x]-1,2,1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),
        e[u].push_back(v),
        e[v].push_back(u);
    dfs1(1,0);
    for(int i=1;i<=20;i++) for(int j=1;j<=n;j++)
        f[i][j]=f[i-1][f[i-1][j]];
    scanf("%d",&q); for(int idx=0;idx<q;idx++)
    {
        int u,v; scanf("%d%d",&u,&v);
        if(dep[u]<dep[v]) {int t=u; u=v; v=t;}
        int d=dis(u,v); int l=(d-1)/2;
        int p=u; for(int i=20;i>=0;i--) if((l>>i)&1)
            p=f[i][p];
        //贡献：
        //dfn[p]~dfn[p]+sz[p]-1 到 u 的距离
        //1~dfn[p]-1 和 dfn[p]+sz[p]~n 到 v 的距离
        query[u].push_back({dfn[p],dfn[p]+sz[p]-1,idx});
        if(dfn[p]>1) query[v].push_back({1,dfn[p]-1,idx});
        if(dfn[p]+sz[p]<=n) query[v].push_back({dfn[p]+sz[p],n,idx});
    }
    init(1,n,1); dfs2(1,0);
    for(int i=0;i<q;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：User_Unauthorized (赞：0)

在下文的推导中假设 $\operatorname{depth}_{L} \le \operatorname{depth}_R$，若不符合则交换 $L$ 和 $R$。

首先我们可以发现，我们可以找到 $R$ 的 $\left\lfloor\frac{\operatorname{dist}\left(L, R\right)}{2}\right\rfloor$ 级祖先 $M$。可以发现，在 $M$ 子树内的节点距离 $R$ 更近，而在 $M$ 子树外的节点距离 $L$ 更近。因此我们可以将问题转化为求 $M$ 子树内的节点到 $R$ 的距离和 $M$ 子树外的节点到 $L$ 的距离和。若 $M$ 为 $L$ 和 $R$ 的最近公共祖先那么特殊考虑即可。

考虑如何计算答案，首先以求 $M$ 子树内的节点到 $R$ 的距离和为例，我们不妨求出所有节点到 $R$ 的距离和后排除非 $M$ 子树节点的贡献。具体的，通过换根 DP 我们可以对于每个节点 $u$ 求出 $f_u$ 代表所有节点到 $u$ 的距离和，$g_u$ 代表其子树内的全部节点到 $u$ 的距离和。那么 $M$ 子树内的节点到 $R$ 的距离和即为：

$$f_R - \left(f_M - g_M\right) - \left(N - \operatorname{size}_M\right) \times \operatorname{dist}\left(M, R\right)$$

其中 $N$ 为节点总数，$\operatorname{size}_M$ 为 $M$ 子树的节点数。同理，$M$ 子树外的节点到 $L$ 的距离和为：

$$f_L - g_M - \operatorname{size}_M \times \operatorname{dist}\left(M, L\right)$$

直接计算即可。

---

## 作者：EuphoricStar (赞：0)

挺无脑的。是不是因为 unr 所以评分虚高啊/qd

考虑把 $L_i \to R_i$ 的路径拎出来，那么路径中点（或中边）左边的点挂的子树到 $L_i$ 更优，右边的点挂的子树到 $R_i$ 更优。

差分一下，可以转化成 $O(q)$ 次询问，每次询问形如 $(u, v)$ 表示求 $v$ 子树中所有点到 $u$ 的距离之和。

考虑离线，把 $(u, v)$ 的询问挂到 $u$ 子树，然后一遍 dfs。dfs 的同时维护所有点到当前点的距离，那么从父亲转移到儿子就相当于，儿子的这棵子树的距离全部 $- 1$，子树外的距离全部 $+ 1$。处理挂在这个点的查询，就做一次区间查询和即可。区间加、区间查询和，使用线段树维护。

总时间复杂度 $O((n + q) \log n)$。

[code](https://atcoder.jp/contests/abc298/submissions/42288917)

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DAT_abc298_h%20%5BABC298Ex%5D%20Sum%20of%20Min%20of%20Length/)

模拟赛怒码 7KB 错解，赛后 10min AC。

# 思路

首先观察 $l,r$ 不同的关系对于结果的构成有什么影响，记 $gf = LCA(l,r)$。

1. $l = r$。很显然，答案就是以 $l$ 为根的节点的深度和。

2. $gf \neq l \wedge gf \neq r$。在 $l$ 子树中的节点在式子中一定会取 $dist(i,l)$，在 $r$ 子树中的节点在式子中一定会取 $dist(i,r)$。如果 $d_l \leq d_r$，则在 $gf$ 之上的节点（包括 $gf$ 除开 $l,r$ 所在的子树）；否则是同理的。其次对于 $l \rightsquigarrow r$ 这段路径，长度为 $len$，则前 $\frac{len}{2}$ 个节点及其不在链上的子树归 $l$，后 $\frac{len}{2}$ 个节点及其不在链上的子树归 $r$。

3. $gf = l \vee gf = r$。与情况 2 同理，除了在处理 $gf$ 子树的时候需要除去包含链的子树。

发现这些贡献可以离线下来换根。发现需要动态求子树深度和，所以用线段树换根即可。注意判断中点与需要处理的点的位置关系。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10,K = 24,inf = 1e9 + 10;
int n,q,ans[N];
int num,id[N],d[N],sz[N],val[N];
int lg[N],f[N][K];
int idx,h[N],ne[M],e[M];

struct Query{
    int u,id;
    int gf,midx,midy;
};
vector<Query> Q[N];

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

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int sum,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].sum += k * (tr[u].r - tr[u].l + 1); tr[u].tag += k;
    }

    inline void pushup(int u){
        tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag); calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return tr[u].sum = val[l] - 1,void();
        int mid = l + r >> 1;
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r) return calc(u,k);
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline int query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query(ls(u),l,r);
        if (r > mid) res += query(rs(u),l,r);
        return res;
    }

    #undef ls
    #undef rs
}T;

inline void get(int u,int fa){
    sz[u] = 1; f[u][0] = fa;
    val[id[u] = ++num] = d[u] = d[fa] + 1;
    for (re int i = 1;i <= lg[d[u]];i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        get(j,u); sz[u] += sz[j];
    }
}

inline int lca(int x,int y){
    while (d[x] != d[y]){
        if (d[x] < d[y]) swap(x,y);
        x = f[x][lg[d[x] - d[y]]];
    }
    if (x == y) return x;
    for (re int i = lg[d[x]];~i;i--){
        if (f[x][i] != f[y][i]) x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

inline bool check(int u,int v){
    if (d[v] > d[u]) return false;
    while (d[u] != d[v]) u = f[u][lg[d[u] - d[v]]];
    return (u == v);
}

inline void dfs(int u,int fa){
    for (auto p:Q[u]){
        int res = 0;
        int v = p.u,gf = p.gf;
        int midx = p.midx,midy = p.midy;
        if (u == v) ans[p.id] = T.tr[1].sum;
        else if (check(u,midx) && !check(v,midx)) res = T.query(1,id[midx],id[midx] + sz[midx] - 1);
        else res = T.tr[1].sum - T.query(1,id[midy],id[midy] + sz[midy] - 1);
        ans[p.id] += res;
    }
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        T.modify(1,1,n,1); T.modify(1,id[j],id[j] + sz[j] - 1,-2);
        dfs(j,u);
        T.modify(1,1,n,-1); T.modify(1,id[j],id[j] + sz[j] - 1,2);
    }
}

signed main(){
    memset(h,-1,sizeof(h));
    n = read();
    for (re int i = 2;i <= n;i++) lg[i] = lg[i >> 1] + 1;
    for (re int i = 1;i < n;i++){
        int a,b; a = read(),b = read();
        add(a,b); add(b,a);
    }
    get(1,0); T.build(1,1,n);
    q = read();
    for (re int i = 1;i <= q;i++){
        int x,y;
        int gf = lca(x = read(),y = read());
        int len = d[x] + d[y] - 2 * d[gf] - 1;
        int mid = len / 2,midx,midy;
        int u = x,v = y;
        if (d[u] <= d[v]){
            for (re int j = 20;~j;j--){
                if ((1ll << j) <= mid){
                    v = f[v][j]; mid -= (1ll << j);
                }
            }
            midx = f[v][0],midy = v;
        }
        else{
            for (re int j = 20;~j;j--){
                if ((1ll << j) <= mid){
                    u = f[u][j]; mid -= (1ll << j);
                }
            }
            midx = u,midy = f[u][0];
        }
        Q[x].push_back({y,i,gf,midx,midy});
        Q[y].push_back({x,i,gf,midy,midx});
    }
    dfs(1,0);
    for (re int i = 1;i <= q;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

