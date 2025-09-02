# [ARC093E] Bichrome Spanning Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc093/tasks/arc093_c

$ N $ 頂点 $ M $ 辺からなる重み付き無向グラフがあります。 グラフの $ i $ 番目の辺は頂点 $ U_i $ と頂点 $ V_i $ を結んでおり、重みは $ W_i $ です。 さらに、整数 $ X $ が与えられます。

このグラフの各辺を白または黒に塗る方法であって、以下の条件を満たすものの個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。

- 白く塗られた辺と黒く塗られた辺をともに含む全域木が存在する。さらに、そのような全域木のうち最も重みが小さいものの重みは $ X $ である。

ただし、全域木の重みとは、その全域木に含まれる辺の重みの和を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1,000 $
- $ 1\ \leq\ M\ \leq\ 2,000 $
- $ 1\ \leq\ U_i,\ V_i\ \leq\ N $ ($ 1\ \leq\ i\ \leq\ M $)
- $ 1\ \leq\ W_i\ \leq\ 10^9 $ ($ 1\ \leq\ i\ \leq\ M $)
- $ i\ \neq\ j $ のとき、$ (U_i,\ V_i)\ \neq\ (U_j,\ V_j) $ かつ $ (U_i,\ V_i)\ \neq\ (V_j,\ U_j) $
- $ U_i\ \neq\ V_i $ ($ 1\ \leq\ i\ \leq\ M $)
- 与えられるグラフは連結である。
- $ 1\ \leq\ X\ \leq\ 10^{12} $
- 入力値はすべて整数である。

## 样例 #1

### 输入

```
3 3
2
1 2 1
2 3 1
3 1 1```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3
3
1 2 1
2 3 1
3 1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
5 4
1
1 2 3
1 3 3
2 4 6
2 5 8```

### 输出

```
0```

## 样例 #4

### 输入

```
8 10
49
4 6 10
8 4 11
5 8 9
1 8 10
3 8 128773450
7 8 10
4 2 4
3 4 1
3 1 13
5 2 2```

### 输出

```
4```

# 题解

## 作者：pomelo_nene (赞：10)

首先我们枚举所有合法的状态下的生成树。有一种枚举方法是钦定一个边一定被选，然后再求这个边被选的情况下的最小生成树，这样枚举至少可以不漏地枚举出所有的情况（考虑这个边染黑，其他边随便）。

那么如果没有权值和为 $X$ 的生成树那就答案为 $0$，不然的话就继续算。

如果 $X_i < X$，那么满足条件的话这条边一定不能生成其对应的所有最小生成树。要满足要求还需要满足至少存在一条边 $\langle u_i,v_i,w_i \rangle$ 使得这条边对应的最小生成树为 $X$。

那么如果整个图的最小生成树的权值就是 $X$，比较好办。记有 $p$ 条边强制被选后满足其对应的最小生成树权值和为 $X$。首先另外 $m-p$ 条边可以随便选，因为如果选到它们肯定不优所以肯定不会选到；剩下的 $p$ 条边（可以构成若干最小生成树）有颜色不能相同的限制，答案是 $(2^p-2)2^{m-p}$。

不然就存在生成树权值小于 $X$。我们找到那些强制选了之后会让最小生成树权值小于 $X$ 的边，假设有 $p$ 条；会让最小生成树权值为 $X$ 的边假设有 $q$ 条。首先不能让那些让最小生成树权值不足 $X$ 的边形成合法生成树，它们的颜色全部相同；然后是另外的 $m-p-q$ 条边仍然任意选；最后是这 $q$ 条边，在题目边两端点不相同的情况下会至少选到一条小于当前权值的边，根据上面的结论这 $q$ 条边不应该和前 $p$ 条边颜色相同，答案是 $2(2^q-1)2^{m-p-q}$。

我觉得这个分讨简单自然阿！

```cpp
map<LL,int> K;
LL n,m,X;
int main(){
    scanf("%lld %lld %lld",&n,&m,&X);
    for(LL i=1;i<=m;++i)   scanf("%lld %lld %lld",&ed[i].u,&ed[i].v,&ed[i].w);
    sort(ed+1,ed+1+m);
    for(LL i=1;i<=m;++i)
    {
        ufs.makeSet(n);
        ufs.unionSet(ed[i].u,ed[i].v);
        LL w=ed[i].w;
        for(LL j=1;j<=m;++j)   if(ufs.unionSet(ed[j].u,ed[j].v))   w+=ed[j].w;
        ++K[w];
    }
    if(!K[X])   return puts("0")&0;
    LL key=0;
    for(auto st:K)
    {
        LL v=st.first,w=st.second;
        if(v<X) key+=w;
        else // (v=x)
        {
            LL ans=0;
            if(!key)    ans=(QuickPow(2,w)+MOD-2)%MOD;
            else    ans=(QuickPow(2,w+1)+MOD-2)%MOD;
            ans=Mul(ans,QuickPow(2,m-w-key));
            printf("%lld\n",ans);
            break;
        }
    }
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：7)

设 $f_i$ 表示强制选第 $i$ 条边的最小生成树的权值，设 $g_i=\sum\limits_{j=1}^n [f_j=i]$。

如果不存在 $i\le X$ 存在 $g_i\ne 0$，那么显然是没有解的，因为进行的操作只能增大生成树的值。

如果 $g_{X}\ne 0$ 且 $\forall i<X$ 都有 $g_i=0$，那么显然这个图的最小生成树就是答案需要的，那么只要这 $g_X$ 条边存在一个颜色不一样就可以了，所以方案数为：

$$(2^{g_X}-2)\times2^{m-g_X}$$

如果存在 $i<X$ 且 $g_i=0$，那么：

- 如果 $f_i<X$，显然需要全部染成一个颜色。
- 如果 $f_i>X$，因为反正都不会影响答案所以可以随便填。
- 如果 $f_i=X$，那么只需要不是全部都与 $f_i<X$ 的颜色一样就行了。

设上面的情况分别有 $a,b,c$ 条边满足，那么方案数就是 $2\times 2^b\times(2^c-1)$。

时间复杂度为 $O(m^2\log n)$，但是并查集的 $\log$ 能叫 $\log$ 吗？

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=2005,mod=1e9+7;
int n,m,X,f[N],mn=1e18,s1,s2;
struct node{int x,y,v;}a[N];
bool cmp(node a,node b){return a.v<b.v;}
struct DSU{
    int fa[N];
    void init(){
        for(int i=1;i<=n;i++) fa[i]=i;
    }
    int find(int x){
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    bool merge(int x,int y){
        x=find(x),y=find(y);
        return (fa[x]!=fa[y])?fa[x]=y:0;
    }
}dsu;
int solve(int x){
    dsu.init(),dsu.merge(a[x].x,a[x].y);
    int ans=a[x].v;
    for(int i=1;i<=m;i++){
        ans+=dsu.merge(a[i].x,a[i].y)*a[i].v;
    }
    return ans;
}
int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod,b>>=1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>X;
    for(int i=1;i<=m;i++){
        cin>>a[i].x>>a[i].y>>a[i].v;
    }
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++){
        f[i]=solve(i);
        mn=min(mn,f[i]);
        s1+=(f[i]==X);
        s2+=(f[i]>X);
    }
    if(mn>X){
        cout<<0<<'\n';
    }
    else if(mn==X){
        cout<<(ksm(2,s1)-2+mod)%mod*ksm(2,m-s1)%mod<<'\n';
    }
    else{
        cout<<2*ksm(2,s2)*(ksm(2,s1)-1)%mod<<'\n';
    }
    return 0;
}
```

---

## 作者：xht (赞：6)

> [ARC093E Bichrome Spanning Tree](https://atcoder.jp/contests/arc093/tasks/arc093_c)

## 题意

- 给定一张 $n$ 个点 $m$ 条边的无重边无自环的无向图，边有边权。
- 求给边染黑白两色，使得包含两种颜色的边的边权和最小的生成树的边权和恰好为 $X$ 的方案数。
- $n \le 10^3$，$m \le 2 \times 10^3$，答案对 $10^9+7$ 取模。

## 题解

首先求出 MST 的边权和 $W$。

如果 $W>X$ 显然无解，以下不考虑这种情况。

显然最终的包含两种颜色的边的边权和最小的生成树要么就是 MST（要求 $W = X$，方案数为 $(2^{n-1}-2)\cdot 2^{m-n+1}$），要么 MST 里的边全都是同一种颜色，然后找到**一条**与这种颜色不同的边 $(u,v)$，用这条边替换 MST 中 $u,v$ 之间的最大边权，使得替换后的边权和最小。

因此我们要求出有多少条边替换后会使边权和 $< X,=X,>X$，设个数分别为 $a,b,c$，则这种情况的方案数为 $(2^b-1)2^{c+1}$。

设 $n,m$ 同阶，总时间复杂度可以做到 $\mathcal O(n \log n)$，但本题 $\mathcal O(n^2)$ 即可通过。

## 代码

```cpp
const int N = 1e3 + 7, inf = 1 << 30;
int n, m, a[N][N], d[N], f[N];
bool v[N], u[N][N];
ll X, W;
vi e[N];
modint ans;

inline void prim() {
	for (int i = 0; i <= n; i++) d[i] = inf;
	d[1] = 0;
	for (int i = 1; i <= n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++)
			if (!v[j] && d[j] < d[x]) x = j;
		v[x] = 1, W += d[x];
		if (f[x])
			e[x].pb(f[x]), e[f[x]].pb(x),
			u[x][f[x]] = u[f[x]][x] = 1;
		for (int y = 1; y <= n; y++)
			if (!v[y] && d[y] > a[x][y])
				d[y] = a[x][y], f[y] = x;
	}
}

int dfs(int x, int f, int z) {
	for (int y : e[x])
		if (y != f) {
			if (y == z) return a[x][y];
			int ret = dfs(y, x, z);
			if (ret) return max(ret, a[x][y]);
		}
	return 0;
}

int main() {
	rd(n, m), rd(X);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = inf;
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1, x, y, z; i <= m; i++)
		rd(x, y, z), a[x][y] = a[y][x] = min(a[x][y], z);
	prim();
	if (W > X) return print(0), 0;
	if (W == X) ans = ((modint)2 ^ m) - ((modint)2 ^ (m - n + 2));
	int b = 0, c = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (a[i][j] < inf && !u[i][j]) {
				ll K = W + a[i][j] - dfs(i, 0, j);
				if (K == X) ++b;
				if (K > X) ++c;
			}
	ans += ((modint)2 ^ (b + c + 1)) - ((modint)2 ^ (c + 1));
	print(ans);
	return 0;
}
```

---

## 作者：S00021 (赞：5)

## 题意

在一张图上黑白染色，使得同时包含有黑边和白边的最小生成树权值恰好为 $x$。问有多少种染色方法。

## Sol

感谢 Etherealdream 提供思路。

现在仅有的两篇题解一篇表述不清并且没有代码，一篇上来就是大分讨，既不自然又误人子弟，因此，我来发一篇不需要用到 LCT 就可以做到相同复杂度 $\mathcal{O}{(m \log m + m \log n)}$ 的题解。

首先肯定是要建出一棵 MST 的，我们不妨思考一下这棵 MST 有何作用，考虑加入一条不存在于 MST 中的新边会产生什么影响，不妨设这条边的边权为 $w$ ，这条边两端点在最小生成树上的瓶颈为 $w_{\min}$ ，那么此时这棵 MST 边权总和的变化量为 $w-w_{\min}$。

设这棵 MST 原来的边权总和为 $u$ ，我们将 $w-w_{\min}$ 与 $x-u$ 进行比较。

- 若 $w-w_{\min} < x-u$ ，那么这条边不会对答案产生贡献。

- 若 $w-w_{\min} = x-u$ ，那么这条边可以被替换入答案。

- 若 $w-w_{\min} > x-u$ ，那么这条边可以任意染色，不影响答案。

令 $w-w_{\min} = x-u$ 的边数为 $e1$，$w-w_{\min} > x-u$ 的边数为 $e2$ ，从组合意义的角度思考：

- 若 $u < x$ ，那么最小生成树上的边可以染成任意且相同的颜色， $w-w_{\min} = x-u$ 的边可以任意染色，但不能全染成相同的颜色，$w-w_{\min} > x-u$ 的边可以任意染色，这时的方案数为 $2 \times (2^{e1}-1)\times 2^{e2}$。

- 若 $u = x$ ，那么除了累加上 $u<x$ 时已经成立的答案之外，还可以将原先的那一棵 MST 染成任意且不全相同的颜色，此时已经有了一棵树作为答案，那么不需要其他的备选项，其余的边任意染色，方案数还应加入 $(2^{n-1}-2)\times 2^{m-n+1}$。

代码不难写，只要一个倍增和一个 kruskal。

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
#define MAXN 1000000
using namespace std;
int n,m,equ,upp,xi,fa[MAXN+5],hd[MAXN+5],cnt,f[MAXN+5][20],mx[MAXN+5][20],dep[MAXN+5],vis[MAXN+5];
struct Edge{int x,y,w;}E[MAXN+5];
struct node{int nxt,to,w;}G[MAXN+5];
bool cmp(Edge p,Edge q){return p.w<q.w;}
void addE(int x,int y,int w){
	G[++cnt].nxt=hd[x],G[cnt].w=w;
	G[cnt].to=y,hd[x]=cnt;
}int Find(int x){
	if(x==fa[x]) return x;
	return fa[x]=Find(fa[x]);
}int Fast(int x,int y){
	int ret=1;
	while(y){
		if(y&1) ret=ret*x%MOD;
		x=x*x%MOD,y>>=1;
	}return ret;
}int calc(){
	int ret=0; for(int i=1;i<=n;i++) fa[i]=i;	
	for(int i=1;i<=m;i++){
		int nu=Find(E[i].x),nv=Find(E[i].y); if(nu==nv) continue; 
		addE(E[i].x,E[i].y,E[i].w),addE(E[i].y,E[i].x,E[i].w);
		fa[nu]=nv,ret+=E[i].w,vis[i]=1;
	}return ret;
}void dfs(int x,int father,int tow=1e9){
	f[x][0]=father,mx[x][0]=tow,dep[x]=dep[father]+1;
	for(int i=1;i<20;i++) f[x][i]=f[f[x][i-1]][i-1],mx[x][i]=max(mx[x][i-1],mx[f[x][i-1]][i-1]);
	for(int i=hd[x];i;i=G[i].nxt){
		int y=G[i].to; if(y==father) continue;
		dfs(y,x,G[i].w);
	}
}int getmn(int x,int y){
	if(dep[x]<dep[y]) swap(x,y); int ret=0;
	for(int i=19;~i;--i) if(dep[x]-(1<<i)>=dep[y]) ret=max(ret,mx[x][i]),x=f[x][i];
	if(x==y) return ret;
	for(int i=19;~i;--i) if(f[x][i]!=f[y][i]) ret=max(ret,max(mx[x][i],mx[y][i])),x=f[x][i],y=f[y][i];
	return max(ret,max(mx[x][0],mx[y][0]));
}signed main(){
	scanf("%lld%lld%lld",&n,&m,&xi);
	for(int i=1;i<=m;i++) scanf("%lld%lld%lld",&E[i].x,&E[i].y,&E[i].w);
	sort(E+1,E+m+1,cmp); 
	int ansi=calc(); dfs(1,0);
	for(int i=1,u;i<=m;i++){
		if(vis[i]) continue; int mn=getmn(E[i].x,E[i].y);
		//printf("%d %d %d\n",E[i].x,E[i].y,mn);
		if(E[i].w-mn>xi-ansi) ++upp;
		if(E[i].w-mn==xi-ansi) ++equ;
	}//printf("%d %d %d\n",upp,equ,ansi);
	int pi=2*(Fast(2,equ)-1+MOD)%MOD*Fast(2,upp)%MOD;
	int qi=(Fast(2,n-1)-2+MOD)%MOD*Fast(2,m-n+1)%MOD;
	if(ansi==xi) printf("%lld\n",(pi+qi)%MOD);
	else printf("%lld\n",pi);
	return 0;
}
```



---

## 作者：cwfxlh (赞：4)

# [AT_arc093_c](https://www.luogu.com.cn/problem/AT_arc093_c)

非常好玩的一道题。    

首先我们求出最小生成树大小 $T$，把 $T>X$ 的无解判掉。     

对于每一条边 $i$ 考虑，如果这一条边所在的所有生成树中，最小的那个仍旧比 $X$ 大，则这条边无论如何染色都不会被考虑进去，于是就不受限了。具体一点的计算就是，钦定这条边选中，计算出最小生成树 $ans_i$ 后判大小关系。    

令这张图所有最小生成树组成一个集合 $S$，对于每条边 $i$，钦定 $i$ 被选中后的最小生成树的集合为 $G_i$。    

我们发现有这样一个特性，对于任意一个 $i$，一定存在两棵生成树 $P\in G_i$ 与 $Q\in S$ 满足 $Q$ 截断一条边后再连接边 $i$ 可以得到 $P$。证明如下：     

首先，如果 $i$ 本身就属于 $S$ 中的某个元素，这就是很明显的。考虑任选一个 $C\in S$，在 $C$ 上连接 $i$ 这条边，形成一棵基环树，则再割断环上另一条边，得到一棵生成树 $I$。如果可以证明 $I\in G_i$，则命题得证。这是很明显的，不妨证其逆否命题，如果存在一棵比 $I$ 更小的生成树 $U\in G_i$，考虑 $I$ 如何变换成 $U$，很明显是割断了除 $i$ 以外的所有边，再按 $U$ 的边连接。则因为 $U$ 更小，在 $C$ 上同样如此操作，可得到一棵更小的生成树，发生矛盾。证毕。     

如果 $T<X$，则 $S$ 内所有边都要染一个颜色，同理，对于 $ans_i<X$，由上面的命题可知，它们与 $S$ 存在公共边，于是大家都强制染一个颜色了。而对于 $ans_i=X$ 的边，可以任意染色，只要保证不与 $S$ 全部同色就可以了。于是枚举 $S$ 中的边的颜色，答案就是 $2\times 2^z\times (2^y-1)$。关于为什么不是 $(2^y-2)$，可以考虑 $ans_i=X$ 的最小生成树必与 $S$ 内的树有交，于是只要不是全同色，连下去就可以了。          

如果 $T=X$，则 $S$ 内所有边都任意染色，只要不是全部同色就可以了，于是答案就是 $2^z\times (2^y-2)$。    

PS：$y$ 指 $ans_i=X$ 的个数，$z$ 指 $ans_i>X$ 的个数。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int n,m,x,T,ans[100003],k1,k2,k3,k4,k5,k6,k7,k8,k9,totE,bcj[100003];
struct Edge{
	int st;
	int ed;
	int v;
}E[400003];
bool comp(Edge X,Edge Y){
	return X.v<Y.v;
}
int finf(int now){
	if(bcj[now]!=now)bcj[now]=finf(bcj[now]);
	return bcj[now];
}
int getans(){
	int ret=0;
	for(int i=1;i<=totE;i++){
		if(finf(E[i].st)!=finf(E[i].ed)){
			bcj[finf(E[i].st)]=finf(E[i].ed);
			ret+=E[i].v;
		}
	}
	return ret;
}
void addEdge(int st,int ed,int v){
	E[++totE].st=st;
	E[totE].ed=ed;
	E[totE].v=v;
	return;
}
int fstp(int X,int Y){
	int ret=1,bse=X;
	while(Y>0){
		if(Y&1)ret*=bse;
		bse*=bse;
		ret%=MOD;
		bse%=MOD;
		Y>>=1;
	}
	return ret;
}
void mem(){
	for(int i=1;i<=n;i++)bcj[i]=i;
	return;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	scanf("%lld",&x);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
	}
	sort(E+1,E+totE+1,comp);
	mem();
	T=getans();
	if(T>x){
		puts("0");
		return 0;
	}
	k1=k2=k3=0;
	for(int i=1;i<=totE;i++){
		mem();
		bcj[E[i].st]=E[i].ed;
		ans[i]=getans()+E[i].v;
		if(ans[i]<x)k1++;
		if(ans[i]==x)k2++;
		if(ans[i]>x)k3++; 
	}
	
	if(T==x){
		printf("%lld",fstp(2,k3)*(fstp(2,k2)-2+MOD)%MOD);
		return 0;
	}
	printf("%lld",fstp(2,k3+1)*(fstp(2,k2)-1+MOD)%MOD);
	return 0;
}
```


---

## 作者：Kinandra (赞：4)

标签: 计数

% xmy 意识流大王.

首先求出任意一个最小生成树 $T$, 记权值和为 $ans$ , 显然若 $ans > x$ 方案书为 $0$ . 

#### Part 1

若 $ans < x$ :

$T$ 的颜色必定要染成同一种颜色(不妨染为白色, 最后将方案数乘 $2$), 记强制选 $i$ 的最小生成树权值为 $tans_i$.

若 $tans_i< x$ , 那么 $i$ 要与所处的最小生成树同色. 显然强制选 $i$ 的最小生成树可以由 $T$ 删去一条边再加上一条边构造得来, 所以 $i$ 也必须染成白色.

若 $tans_i>x$ , 那么 $i$ 不管怎么染都不会影响最小异色生成树.

对于剩余 $tans_i=x$ 的边, 我们**依次枚举这些边**, 记被强制选择某种颜色的边数为 $cnt$ (初始 $cnt$ 为 $tans_i<x$ 的 $i$ 的数量). 首先强制枚举到的边 $j$ 为黑色, 那么未被强制的边随意染, 贡献为 $2^{m-cnt-1}$ , 然后强制 $j$ 为白色, $++cnt$, 枚举下一条边.

不难发现(等比数列求和或组合意义)最终方案数为 $2\times(2^c-1)\times2^{m-n-z}$ , 其中 $c$ 为 $tans_i=x$ 的 $i$ 的数量.

#### Part 2

若 $ans=x$ .

那么首先可以计算以 $T$ 为最小异色生成树的答案, 强制 $T$ 异色, 贡献为 $(2^{n-1}-2)\times2^{m-n+1}$ , 然后强制 $T$ 同色.

发现计算完上面的贡献后问题转化成了 $ans<x$ 的情况, 套用上面的方法即可, 注意不能直接使用 $2\times(2^c-1)\times2^{m-n-z}$ 这个公式, 要先将 $c$ 减去 $T$ 包含的 $n-1$ 条边后再做计算.

时间复杂度 $\mathcal O(m^2)$ , 可以用 LCT 做到更优, 但没必要.

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
long long read();
void Add(int &x, int y) { (x += y) > mod ? x -= mod : x; }
int fsp(long long bs, int p) {
    int rt = 1;
    while (p) {
        if (p & 1) rt = bs * rt % mod;
        bs = bs * bs % mod, p >>= 1;
    }
    return rt;
}
int n, m, res;
long long x, ans;
struct E {
    int u, v, w;
    void init() { u = read(), v = read(), w = read(); }
} e[2003];

bool cmp(E a, E b) { return a.w < b.w; }

int fa[1003];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void init_fa() {
    for (int i = 1; i <= n; ++i) fa[i] = i;
}

long long get_ans(int c) {
    long long rt = 0;
    for (int i = 1; i <= m; ++i) {
        if (find(e[i].u) != find(e[i].v))
            rt += e[i].w, ++c, fa[find(e[i].u)] = find(e[i].v);
        if (c == n - 1) return rt;
    }
    return rt;
}

long long tans[2003];

int main() {
    n = read(), m = read(), x = read();
    for (int i = 1; i <= m; ++i) e[i].init();
    sort(e + 1, e + 1 + m, cmp), init_fa(), ans = get_ans(0);
    if (ans > x) return puts("0"), 0;
    if (ans == x) Add(res, 1ll * (fsp(2, n - 1) - 2) * fsp(2, m - n + 1) % mod);
    int used = n - 1;
    for (int i = 1; i <= m; ++i)
        init_fa(), fa[e[i].u] = fa[e[i].v], tans[i] = get_ans(1) + e[i].w;
    sort(tans + 1, tans + 1 + m);
    for (int i = n; i <= m; ++i)
        if (tans[i] == x) Add(res, fsp(2, m - i + 1));

    printf("%d\n", res);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
long long read() {
    long long x = 0;
    char c = gc;
    while (!isdigit(c)) c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x;
}
```

---

## 作者：yyxmy (赞：3)

我们发现这道题有一个最主要的性质， 得到的生成树最多只有一条边不是$MST$上的边， 而它取代的一定是其所覆盖的链上最小的边。 

它要使得$MST - max(u,v) + w[i] = x$,	于是我们就可以找到所有满足这个条件的边。假设这种边有z条。

那么最后的答案显然为$2(2^z-1)2^{(m- n - z)}$,这表示所有$mst$上的边只可能是同一种颜色， 这$z$条边的方案不能全与前面一致， 后面的边可以随意染色。

---

## 作者：E_M_T (赞：2)

设原图 MST 边权和为 $d$。

可以证明，染色后一定存在一个满足条件的最小生成树是原 MST 或是原 MST 改变一条边。

若原 MST 同时存在异色边，则最小生成树就是原 MST，否则可以从外找一条异色边 $(u,v)$ 加入，并删去原 MST 上 $u$ 到 $v$ 路径上最大的一条边，一定存在 $(u,v)$ 使得操作后是最小生成树。

考虑分别计算“原 MST”和”原 MST 改变一条边“作为染色后满足条件的最小生成树的方案并相加。

* $d=x$

这种情况原 MST 可以作为最小生成树，方案数 $(2^{n-1}-2)2^{m-n+1}$，即 MST 中边随便染但不能全相同，其他边任意染。

考虑加入一条边生成树不变的情况，设这样的边有 $k$ 条，方案数 $2(2^k-1)2^{m-k-n+1}$，即 MST 中边全染相同颜色，$k$ 条边任意染但不能全与 MST 中颜色相等，其他 $m-k-(n-1)$ 条边任意染。

* $d<x$

这种情况原 MST 无法作为最小生成树。

考虑加入一条边使得最小生成树变为 $x$ 的情况，设这样的边有 $k$ 条，方案数 $2(2^k-1)2^{m-k-n+1}$，原因和上一种一样。

但这样并不完全对，写出来发现样例三错了。

考虑有一条边 $(u,v,w)$ 加入使得最小生成树变为 $x$，如果存在某一条边，边权比 $w$ 小且与 MST 颜色异色，此时最小生成树肯定会选择这条边，不符合条件。

于是处理出加入一条边使得最小生成树 $<x$ 的情况，设这样的边有 $t$ 条，则这 $t$ 条边都必须与原 MST 的颜色相同，方案数 $2(2^k-1)2^{m-k-n-t+1}$。

而 $d=x$ 时并不会出现这种情况，因为不可能有一条边加入最小生成树后边权和更小，这与原 MST 是最小矛盾。

* $d>x$

发现两种情况都无法成为满足条件的最小生成树，方案数为 $0$。

显然树剖可以做到 $O(m\log n)$。代码采用了暴力计算 $u\sim v$ 路径上最大边权的方式（边权下放到儿子变为点权），复杂度 $O(nm)$，仍然可过。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define ff(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define Fr(a) for(auto it:a)
int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
void put(int x){print(x);putchar('\n');}
void printk(int x){print(x);putchar(' ');}
const int N=2010,P=1e9+7;
int n,m,x,fa[N],tot,head[N],vis[N],f[N],val[N],dep[N];
struct node
{
	int nex,to,w;
}a[N<<1],e[N<<1];
void add(int u,int v,int w)
{
	a[++tot].nex=head[u];
	head[u]=tot;
	a[tot].to=v;
	a[tot].w=w;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y) fa[x]=y;
}
int cmp(node p,node q){return p.w<q.w;}
void dfs(int u,int da)
{
	dep[u]=dep[da]+1;
	f[u]=da;
	for(int i=head[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(v==da) continue;
		val[v]=a[i].w;
		dfs(v,u);
	}
}
int find_max(int u,int v)
{
	if(dep[u]<dep[v]) sd swap(u,v);
	int ans=0;
	while(dep[u]!=dep[v])
	{
		ans=MAX(ans,val[u]);
		u=f[u];
	}
	if(u==v) return ans;
	while(u!=v)
	{
		ans=MAX(ans,MAX(val[u],val[v]));
		u=f[u],v=f[v];
	}
	return ans;
}
int ksm(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%P;
		a=a*a%P;
		b>>=1;
	}
	return res;
}
void solve()
{
	n=read();m=read();x=read();
	F(i,1,n) fa[i]=i;
	F(i,1,m) e[i].nex=read(),e[i].to=read(),e[i].w=read();
	sd sort(e+1,e+1+m,cmp);
	int d=0,cnt=0;
	F(i,1,m)
	{
		int u=e[i].nex,v=e[i].to;
		if(find(u)==find(v)) continue;
		vis[i]=1;
		add(u,v,e[i].w),add(v,u,e[i].w);
		// printk(u),put(v);
		merge(u,v);
		d+=e[i].w;
		if(++cnt==n-1) break;
	}
	dfs(1,0);
	if(d>x) return put(0);
	int k=0,t=0;
	F(i,1,m)
	{
		if(vis[i]) continue;
		if(d+e[i].w-find_max(e[i].nex,e[i].to)==x)
		{
			k++;
		}
		if(d+e[i].w-find_max(e[i].nex,e[i].to)<x)
		{
			t++;
		}
	}
	// put(k);
	if(d==x)
	{
		int ans=(ksm(2,n-1)-2+P)*ksm(2,m-n+1)%P;
		(ans+=2*(ksm(2,k)-1+P)%P*ksm(2,m-k-n+1)%P)%=P;
		put(ans);
	}
	else
	{
		int ans=2*(ksm(2,k)-1+P)%P*ksm(2,m-k-n-t+1)%P;
		put(ans);
	}
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：Terac (赞：1)

萌萌题。

先将边按边权排序，求出最小生成树。

先考虑最小生成树权值为 $X$ 的情况，严格来说是不更换最小生成树的边的情况，即保证最小生成树的边不全是同色即可，方案数为 $(2^{n-1}-2)\times 2^{m-n+1}$。

接下来考虑更换最小生成树的边的情况，考虑什么时候最小生成树取不到，是不是最小生成树的所有边都染了同个颜色？因为可以染黑色或白色，答案要乘 $2$。不妨设其染成白色。

然后考虑有两种颜色的最小生成树，发现一个性质，即黑色边最多仅有一条，因为每次黑色边 $(u,v)$ 的加入，要减去原最小生成树上的 $u\to v$ 路径上最大边权，再加上 $w(u,v)$，因为 $(u,v)$ 本身不在最小生成树上，所以加入它肯定不优，于是只需一条黑边即可。

所以这个问题只需要对于每条不在树上的边，求一下加入它的最小生成树并判一下是否等于 $X$ 即可。

按每条边加入后的最小生成树权值排序，对于排序后的非树边 $(u_i,v_i)$，若加入它后的最小生成树权值为 $X$，其可以成为答案，但需保证前 $i-1$ 条边不能被染黑，否则异色最小生成树就不会是包含 $(u_i,v_i)$ 的，所以方案数为 $2\times2^{m-n+1-i}$。

时间复杂度 $O(n\log n)$。

---

## 作者：Conan15 (赞：0)

看到生成树，想到最小生成树 MST。记 MST 的边权和为 $res$。

若 $res \gt x$，显然无解。\
若 $res = x$，保证 MST 上的边不全都同色即可，所以方案数先加上 $(2^{n-1} - 2) \times 2^{m-n+1}$。\
然后再考虑 $res \lt x$ 的情况，可以想到从 MST 上改一条边得到新的树。因此求出 $r_i$ 表示强制选择第 $i$ 条边时的最小生成树边权和。\
接下来分三种情况讨论：

1. $r_i \gt x$：无论如何涂色它都不会对答案有影响，所以忽略。
2. $r_i \lt x$：若此时 $i$ 与 MST 异色，那么最小异色生成树就是 $r_i$，因此需要保证 $r_i$ 和 MST 同色。
3. $r_i = x$：设此时有 $c$ 条边被固定颜色，则第 $i$ 条边的贡献为 $2^{m-c-1}$，即钦定 $i$ 与 MST 异色。然后再钦定它与 MST 同色，即 $c \leftarrow c+1$。

在实现上可以把 $r_i$ 排序，这样 $c=i-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1015, M = N << 1, mod = 1e9 + 7;
int n, m;
long long x;

struct node {
    int u, v;
    int w;
} edge[M];

bool cmp(node a, node b) { return a.w < b.w; }

int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = (res * 1ll * a) % mod;
        a = (a * 1ll * a) % mod;
        k >>= 1;
    }
    return res;
}

int p[N];
int find(int x) { return (p[x] == x) ? x : p[x] = find(p[x]); }
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    p[x] = y;
}
long long res = 0, ans = 0;
void init(int id) {
    for (int i = 1; i <= n; i++) p[i] = i; res = 0;
    if (id) merge(edge[id].u, edge[id].v), res = edge[id].w;
}
long long r[M];
void Kruskal(int id) {
    init(id);
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u, v = edge[i].v;
        u = find(u), v = find(v);
        if (u == v) continue;
        res += edge[i].w, p[u] = v;
    }
    if (id) r[id] = res;
}

int main() {
    scanf("%d%d%lld", &n, &m, &x);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    sort(edge + 1, edge + 1 + m, cmp);
    Kruskal(0);
    if (res > x) return puts("0"), 0;
    if (res == x) ans = ((qmi(2, n - 1) - 2 + mod) * 1ll * qmi(2, m - n + 1)) % mod, ans = (ans * 1ll * qmi(2, mod - 2)) % mod;
    for (int i = 1; i <= m; i++) Kruskal(i);
    sort(r + 1, r + 1 + m);
    for (int i = n; i <= m; i++) //不能是 MST
        if (r[i] == x) (ans += qmi(2, m - i)) %= mod;
    printf("%lld\n", (ans * 2) % mod);
    return 0;
}
```

---

