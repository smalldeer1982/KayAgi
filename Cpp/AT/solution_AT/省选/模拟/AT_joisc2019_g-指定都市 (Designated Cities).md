# 指定都市 (Designated Cities)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2019/tasks/joisc2019_g



# 题解

## 作者：Rainy7 (赞：3)

### 题目大意

给定一棵树，双向边，每条边两个方向的权值分别为 $c_i,d_i$，多次询问 $k$，表示选出 $k$ 个点，依次将以每个点为根的内向树边权赋值为 $0$，需要求出最后树的边权之和的最小值。

保证 $n \le 2\times 10^6,q \le n,c_i,d_i \le 10^9$。

### 题解

我们只需要求出选出来边和的最大值即可。

先考虑 $k=1$ 的情况，对于点 $u$，他的贡献就是以他为根的内向子树边的和 $w_u$。所以可以通过换根 DP 预处理出所有点的 $w_u$，然后取最大值即可。

再考虑 $k=2$ 的情况，取两个点 $u,v$，贡献为 $u,v$ 之间双向边的和，然后路径外的点向路径方向边的和。也就是 $\dfrac{w_u+w_v+\text{dis}(u,v)}{2}$，这东西长得就很直径。

那如果再加一个点呢？考虑把刚刚取的类似直径的东西缩起来，然后以这个点为根。每次选一个叶子，叶子到这个根的内向边的和就是贡献。

所以对于 $k >1$ 的情况，可以把所有链预处理后排个序，然后一个一个取就行了。

复杂度 $\mathcal{O}(n \log n)$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
struct edge{
	int v,w,nx;
}e[N<<1];
int n,m,ne=1,l,r,tot,f[N],fa[N];
ll sum,g[N],d[N],b[N],ans[N];
bool vis[N];
void read(int u,int v,int w)
{	e[++ne].v=v;
	e[ne].nx=f[u];
	e[ne].w=w;
	f[u]=ne;
}
void dfs1(int u,int ffa)
{	for(int i=f[u];i;i=e[i].nx)
	{	int v=e[i].v;
		if(v==ffa)continue;
		dfs1(v,u);
		g[u]+=g[v]+e[i].w;
	}
}
void dfs2(int u,int ffa)
{	for(int i=f[u];i;i=e[i].nx)
	{	int v=e[i].v;
		if(v==ffa)continue;
		g[v]=g[u]-e[i].w+e[i^1].w;
		dfs2(v,u);
	}
}
void dfs3(int u,int ffa)
{	fa[u]=ffa;
	for(int i=f[u];i;i=e[i].nx)
	{	int v=e[i].v;
		if(v==ffa)continue;
		d[v]=d[u]+e[i].w+e[i^1].w;
		dfs3(v,u);
	}
}
ll solve(int u,int ffa)
{	ll res=0;
	for(int i=f[u];i;i=e[i].nx)
	{	int v=e[i].v;ll w;
		if(v==ffa)continue;
		w=solve(v,u)+e[i^1].w;
		if(!res)res=w;
		else b[++tot]=min(res,w),res=max(res,w);
	}
	return res;
}
bool cmp(ll x,ll y){return x>y;}
int main()
{	//freopen("01-02.in","r",stdin);
	scanf("%d",&n);
	for(int i=1,u,v,w,ww;i<n;i++)
	{	scanf("%d%d%d%d",&u,&v,&w,&ww);
		read(u,v,ww),read(v,u,w);
		sum+=w+ww;
	}
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++)ans[1]=max(ans[1],g[i]);
	l=r=1,dfs3(1,0);
	for(int i=1;i<=n;i++)if(d[i]+g[i]>d[l]+g[l])l=i;
	d[l]=0,dfs3(l,0);
	for(int i=1;i<=n;i++)if(d[i]+g[i]>d[r]+g[r])r=i;
	ans[2]=(g[l]+g[r]+d[r])/2;
	int u=r,j=2;
	while(u)vis[u]=1,u=fa[u];
	u=r;
	while(u)
	{	for(int i=f[u];i;i=e[i].nx)
		{	int v=e[i].v;
			if(!vis[v])b[++tot]=solve(v,u)+e[i^1].w;
		}
		u=fa[u];
	}
	sort(b+1,b+1+tot,cmp);
	for(int i=1;i<=tot;i++)ans[j+1]=ans[j]+b[i],j++;
	for(;j<n;j++)ans[j+1]=ans[j];
	scanf("%d",&m);
	while(m--)
	{	scanf("%d",&u);
		printf("%lld\n",sum-ans[u]);
	}
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

简单题，模拟赛场切纪念一下。

肯定是提前预处理出所有答案，一次性回答。

首先我们可能会猜想：以前选的点一定不会被丢掉，但是这个结论是错误的，可以被下面 HACK：

```cpp
input:
4
1 2 1 2
1 3 3 4
1 4 5 6
2
1
2

output:
9
1
```

但这个结论完全是错的吗？也不尽然。实际上当 $k\geq2$ 时再加点是不会把以前的点丢掉的（即不会反悔），理由可以考虑调整法，或者看 @Graphcity 的证明。

还有一个结论：当 $k\geq 2$ 时，我们只会选叶子，理由如下：

假如有如下树且我们选了 $1$ 和 $6$：

![](https://cdn.luogu.com.cn/upload/image_hosting/rn5qi3m6.png)

但是如果我们把 $1$ 换成 $2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/dbk8x6u7.png)

就凭空多了一条边，这寓示着若选了非叶子节点，则一定能被叶子节点替代。

有了上面的两个结论做基础，我们可以得到进一步的思考。

性质一保证如果我们知道了选两个点时的答案，则选出的这两个点以后一定不会换掉，这说明我们可以直接选一个当作根，且在 $k\geq 2$ 时根必选。

性质二保证了我们每次选出的肯定是一条由根到叶子的外向链，所以问题被分成了三个部分。

1. $k=1$ 时怎么算答案，明显可以换根求出内向边权值和，具体见代码。
2. $k=2$ 时怎么算选了哪个点，这个可以在上一个问题的基础上再换根出以每个点为根时的最长外向链，代码中使用的是线段树求最长链（因为不是很会换根）。
3. $k > 2$ 时怎么累计答案。

发现第三个问题比较关键，这里有一个比较显然的贪心。

对树进行长链剖分，然后把每一条长链拿下来，每次贪心地选走权值最大的一条链。

当然也可以线段树暴力跳，每次碰到之前被跳过的链就停止，其实也是对的，但是太不优雅了。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define int ll
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout
typedef long long ll;

const int N=5e5+10;
struct edge{
	int to,ne,val;
	edge(int to=0,int ne=0,int val=0):
		to(to),ne(ne),val(val){;}
}a[N<<1];
int h[N],cnt,dp[N],f[N],s[N],A[N],B[N],n,q,fa[N],g[N],H[N];
int res,ans,Ans[N],DP[N],siz[N],id[N],idx,rev[N],w[N],tot,son[N];
inline void add(int x,int y,int d){a[++cnt]=edge(y,h[x],d);h[x]=cnt;}
struct SegmentTree{
	#define ls now<<1
	#define rs now<<1|1
	int tag[N<<2],maxx[N<<2];
	inline void pushup(int now){maxx[now]=max(maxx[ls],maxx[rs]);}
	inline void add(int now,int v){tag[now]+=v;maxx[now]+=v;}
	inline void pushdown(int now){
		if(!tag[now]) return ;
		add(ls,tag[now]);add(rs,tag[now]);tag[now]=0;
	}
	void build(int now,int l,int r){
		if(l==r){maxx[now]=dp[rev[l]];return ;}
		int mid=(l+r)>>1;build(ls,l,mid);build(rs,mid+1,r);pushup(now);
	}
	void update(int now,int l,int r,int x,int y,int v){
		if(x<=l&&r<=y) return add(now,v);
		int mid=(l+r)>>1;pushdown(now);
		if(mid>=x) update(ls,l,mid,x,y,v);
		if(mid<y) update(rs,mid+1,r,x,y,v);
		pushup(now);
	}
	void out(int now,int l,int r){
		if(l==r){
			cout<<maxx[now]<<' ';
			if(r==n) cout<<endl;
			return ;
		}
		int mid=(l+r)>>1;pushdown(now);
		out(ls,l,mid);out(rs,mid+1,r);pushup(now);
	}
	inline int Get(){return maxx[1];}
}t;

void dfs1(int x,int y){//预处理出内向和、外向最大值、到根的外向距离等。
	id[x]=++idx;rev[idx]=x;siz[x]=1;
	for(int i=h[x];i;i=a[i].ne) if(a[i].to==y) f[y]+=a[i].val;
	for(int i=h[x];i;i=a[i].ne){
		if(a[i].to==y) continue;
		dp[a[i].to]=dp[x]+a[i].val;
		dfs1(a[i].to,x);f[x]+=f[a[i].to];
		s[x]=max(s[x],s[a[i].to]+a[i].val);
		siz[x]+=siz[a[i].to];
	}
}
void dfs2(int x,int y,int v){//处理出内向总和、总树外向最大值
	int w=0;
	for(int i=h[x];i;i=a[i].ne) if(a[i].to==y) w=a[i].val;
	g[x]-=w;t.add(1,w);t.update(1,1,n,id[x],siz[x]+id[x]-1,-w-v);DP[x]=t.Get();
	for(int i=h[x];i;i=a[i].ne){
		if(a[i].to==y) continue;
		g[a[i].to]=g[x]+a[i].val;
		dfs2(a[i].to,x,a[i].val);
	}
	t.add(1,-w);t.update(1,1,n,id[x],siz[x]+id[x]-1,w+v);
}
void ChainCut(int x,int y){
	for(int i=h[x];i;i=a[i].ne){
		if(a[i].to==y) continue;
		ChainCut(a[i].to,x);H[a[i].to]+=a[i].val;
		if(H[a[i].to]>=H[x]){H[x]=H[a[i].to];son[x]=a[i].to;}
	}
	for(int i=h[x];i;i=a[i].ne) if(a[i].to!=y&&a[i].to!=son[x]) w[++tot]=H[a[i].to];
}

signed main(){
	cin>>n;
	for(int i=1,x,y;i<n;++i){
		cin>>x>>y>>A[i]>>B[i];res+=A[i]+B[i];
		add(x,y,A[i]);add(y,x,B[i]);
	}
	dfs1(1,0);g[1]=f[1];t.build(1,1,n);dfs2(1,0,0);
	for(int i=1;i<=n;++i) Ans[1]=max(Ans[1],g[i]);
	for(int i=1;i<=n;++i) ans=max(ans,g[i]+DP[i]);
	int rt=0;for(int i=1;i<=n;++i) if(ans==g[i]+DP[i]) rt=i;
	ChainCut(rt,0);res-=g[rt];w[++tot]=H[rt];sort(w+1,w+1+tot);reverse(w+1,w+1+tot);
	Ans[1]=res-Ans[1]+g[rt];
//	cout<<endl<<rt<<endl<<endl;
//	for(int i=1;i<=tot;++i) cout<<w[i]<<' ';cout<<endl;
	for(int i=2;i<=n;++i) Ans[i]=(res-=w[i-1]);
	cin>>q;for(int i=1,x;i<=q;++i){cin>>x;cout<<Ans[x]<<endl;}
	return 0;
}
/*
	不会换根，试试线段树吧！！！
*/
```

---

## 作者：Inzaghi_Luo (赞：1)

### 分析
首先看 $k=1$ 的情况。容易发现，点 $u$ 不用支付代价的道路就是以 $u$ 为根的内向树边权和。这个可以换根求出。

然后看 $k=2$ 的情况。两个点相比一个点可以多覆盖的部分就是他们路径上的边。想要最大，也就是要求出来直径。只是同时带点权和边权的直径而已。点权就是 $k=1$ 时这个点的内向树边权和。

考虑往上扩展。容易发现每次选一个点就是获得它到直径上还没被覆盖的边权和。贪心就好，我选的做法是先把直径缩成点，然后用类似长链剖分的方法，然后把每个链头的长度排个序就好。

代码有注释
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 200005;
int head[MAXN], CNT;
struct edge{
	int next, to, val;
}ed[MAXN << 1];
void add_edge(int u, int v, int w){
	ed[++CNT] = (edge){head[u], v, w};
	head[u] = CNT;
}
int w[MAXN], ans[MAXN];
void predfs(int u, int fa){
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		w[1] += ed[i ^ 1].val;
		predfs(v, u);
	}
}
void change_root(int u, int fa){
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		w[v] = w[u] + ed[i].val - ed[i ^ 1].val;
		change_root(v, u);
	}
}
int dis[MAXN];
void get_d(int u, int fa){
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		dis[v] = dis[u] + ed[i].val + ed[i ^ 1].val;
		get_d(v, u);
	}
}
bool bel[MAXN];
bool bedot(int u, int fa, int t){
	if(u == t){
		bel[t] = 1;
		return 1;
	}
	bool flag = 0;
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		flag |= bedot(v, u, t);
	}
	if(flag) bel[u] = 1;
	return flag;
} 
int dist[MAXN], son[MAXN];
void dfs1(int u, int fa){
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		dfs1(v, u);
		dist[v] += ed[i].val; 
		if(dist[u] < dist[v]){
			dist[u] = dist[v];
			son[u] = v;
		}
	}
}
int top[MAXN], D[MAXN], num;
void dfs2(int u, int fa, int Top){
	if(u == Top) D[++num] = dist[u];
	top[u] = Top;
	if(son[u]) dfs2(son[u], u, Top);
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa || v == son[u]) continue;
		dfs2(v, u, v);
	}
}
int u[MAXN], v[MAXN], w1[MAXN], w2[MAXN];
signed main(){
	CNT = 1; 
	int n, all = 0;
	scanf("%lld", &n);
	for(int i = 1;i < n;i++){
		scanf("%lld%lld%lld%lld", &u[i], &v[i], &w1[i], &w2[i]);
		add_edge(u[i], v[i], w1[i]);
		add_edge(v[i], u[i], w2[i]);
		all += w1[i];
		all += w2[i];
	}
	//处理每个点的点权 
	predfs(1, 0);
	change_root(1, 0);
	for(int i = 1;i <= n;i++) ans[1] = max(ans[1], w[i]);
	//双DFS求直径 
	int x = 1, y = 1;
	get_d(1, 0);
	for(int i = 1;i <= n;i++) if(dis[i] + w[i] > dis[x] + w[x]) x = i;
	dis[x] = 0;
	get_d(x, 0);
	for(int i = 1;i <= n;i++) if(dis[i] + w[i] > dis[y] + w[y]) y = i;
	ans[2] = w[x] + w[y] + dis[y] >> 1;
	//直径缩点
	bedot(x, 0, y);
	//重新建图
	CNT = 1;
	for(int i = 1;i <= n;i++) head[i] = 0;
	for(int i = 1;i < n;i++){
		if(bel[u[i]]) u[i] = x;
		if(bel[v[i]]) v[i] = x;
		if(u[i] == v[i]) continue;
		add_edge(u[i], v[i], w1[i]);
		add_edge(v[i], u[i], w2[i]);
	} 
	//长链剖分
	dfs1(x, 0); 
	dfs2(x, 0, x);
	sort(D + 1, D + num + 1);
	int now = 3;
	while(num){
		ans[now] = ans[now - 1] + D[num--];
		now++;
	}
	while(now <= n){
		ans[now] = ans[now - 1];
		now++;
	}
	int q;
	scanf("%lld", &q);
	for(int i = 1, e;i <= q;i++){
		scanf("%lld", &e);
		printf("%lld\n", all - ans[e]);
	} 
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

我们考察已经选择的点构成集合 $S$，新选点 $x$ 对答案的贡献，此处保证 $S$ 非空，因为第一个选择的点的贡献为所有指向其的边，可以通过换根 dp 简单求解，下文将指向 $x$ 的所有边和记为 $dp_x$。

新加入的点 $x$ 若不在包含 $S$ 的极小连通块中（即不在 $S$ 构成的虚树上），则会带来等于包含 $S$ 的极小连通块上到 $x$ 最近的点走到 $x$ 的边的贡献，这告诉我们假若钦定答案必须包含点 $x$，那么每加入一个点的贡献为以 $x$ 为根的树内向树上加入的点到 $x$ 的链，而总贡献是链并，启发我们可以对以 $x$ 为根的内向树长坡，通过调整法可以得到最优策略是选前 $k-1$ 条长链，但是问题是你不知道答案会不会包含点 $x$，于是你想着对每个点都做一遍上述算法看看是不是最优策略都在一个 $x$ 处取到。

打表发现，很遗憾不是，但是继续打表，你发现 $k \geq 2$ 时的最优策略都在一个 $x$ 处取到，也就是 $k \geq 2$ 时 $k+1$ 的最优策略是在 $k$ 的最优策略上新增一个点，下面我们通过归纳来说明这件事。

现在已知 $2 \leq k < p$ 时，$k+1$ 的最优策略是在 $k$ 的最优策略上新加一个点取到，接下来要说明这对 $k = p$ 也成立。

考虑既然 $2 \leq k < p$ 时结论成立，那么 $k = p-1$ 的策略一定是选取一个点 $s$，再选以其为根的前 $p-2$ 条长链，也就是贡献可以写作 $dp_s + \sum_{i=1}^{p-2} a_i$，任取 $k = p$ 的最优策略选取的一个点 $t$，显然 $k = p$ 时的策略能写作 $dp_t + \sum_{i=1}^{p-1} b_i$ 的形式，假若 $s = t$ 那么一定可以从 $k = p-1$ 的策略调整过来，否则你发现 $dp_s + \sum_{i=1}^{p-2} a_i > dp_t + \sum_{i=1}^{p-2} b_i,dp_s + \sum_{i=1}^{p-1} a_i < dp_t + \sum_{i=1}^{p-1} b_i$，那一定有 $b_{p-1} - a_{p-1} > dp_s + \sum_{i=1}^{p-2} a_i - (dp_t + \sum_{i=1}^{p-2} b_i)$，这个时候你拿 $b_{p-1}$ 去替换掉前面最小的项时会使得 $k = p - 1$ 时的最优策略也变成 $t$，与 $s \not = t$ 矛盾。

说明了这件事后只需要求出 $k = 2$ 时最优的两点 $s,t$ 然后任取其中一个点跑长链剖分即可，寻找 $s,t$ 可以再用一次换根 dp 对每个点求解以其为根的外箱树上最远点，总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
int n,q,sum;
int g[maxn],dp[maxn];
pair<int,int> f[maxn],p[maxn];
int head[maxn],nxt[maxn<<1],to[maxn<<1],w[maxn<<1];
int tot=1;
void add(int u,int v,int c,int d){
    sum+=c;
    sum+=d;
    tot++;
    w[tot]=c;
    to[tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
    tot++;
    w[tot]=d;
    to[tot]=u;
    nxt[tot]=head[v];
    head[v]=tot;
}
void DP1(int u,int fa){
    //the value to point - u
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            DP1(to[i],u);
            g[u]+=g[to[i]]+w[i^1];
        }
    }
}
void DP2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            dp[to[i]]=dp[u]+w[i]-w[i^1];
            DP2(to[i],u);
        }
    }
}
void DP3(int u,int fa){
    f[u]=make_pair(0,u);
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            DP3(to[i],u);
            f[u]=max(f[u],make_pair(f[to[i]].first+w[i],f[to[i]].second));
        }
    }
}
void DP4(int u,int fa){
    p[u]=max(p[u],make_pair(0*1ll,u));
    pair<int,int> mx=make_pair(0,0),cmx=make_pair(0,0);
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            cmx=max(cmx,make_pair(f[to[i]].first+w[i],f[to[i]].second));
            if(cmx>mx) swap(cmx,mx);
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            p[to[i]]=max(p[to[i]],make_pair(p[u].first+w[i^1],p[u].second));
            if(to[i]==mx.second){
                p[to[i]]=max(p[to[i]],make_pair(cmx.first+w[i^1],cmx.second));
            }else{
                p[to[i]]=max(p[to[i]],make_pair(mx.first+w[i^1],mx.second));
            }
            DP4(to[i],u);
        }
    }
}
int ans[maxn];
vector<int> vec;
int dfs(int u,int fa){
    vector<int> son;
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=fa){
            son.push_back(dfs(to[i],u)+w[i]);
        }
    }
    if(son.size()==0) return 0;
    sort(son.begin(),son.end());
    for(int i=0;i+1<son.size();i++) vec.push_back(son[i]);
    return son.back();
}
bool cmp(int x,int y){
    return x>y;
}
void work(int u){
    vec.clear();
    vec.push_back(dfs(u,0));
    sort(vec.begin(),vec.end(),cmp);
    for(int i=0;i<vec.size();i++) ans[i+2]=vec[i];
    ans[1]+=dp[u];
    for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
    return ;
}
int s,t,answer;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,c,d;
        cin>>u>>v>>c>>d;
        add(u,v,c,d);
    }
    DP1(1,0);
    dp[1]=g[1];
    DP2(1,0);
    DP3(1,0);
    DP4(1,0);
    for(int i=1;i<=n;i++){
        if(dp[i]+max(f[i],p[i]).first>answer){
            answer=dp[i]+max(f[i],p[i]).first;
            s=i,t=max(f[i],p[i]).second;
        }
    }
    work(s);
    for(int i=1;i<=n;i++) ans[1]=max(ans[1],dp[i]);
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        cout<<sum-ans[k]<<'\n';
    }
    return 0;
}
/*
6
1 6 6 12
6 2 5 16
1 4 13 4
5 1 19 3
3 1 9 13
1
2
*/
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2019G 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_g)

**题目大意**

> 给定一棵树，每条边有正向和反向，正向边权值为 $c_i$，反向边权值为 $d_i$。
>
> 定义一次操作为：选择一个点 $u$，然后把以 $u$ 为根的内向树上的有向边全部删掉。
>
> $q$ 次询问，每次给定 $k$，求出进行 $k$ 次操作后剩余的边权值和最小是多少。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

考虑贪心，可以证明在 $k\ge 2$ 时，$k+1$ 所选的答案一定是在 $k$ 所选答案的基础上增加一个点。

$k=1$ 的情形是简单换根，设以 $x$ 为根的内向树权值和为 $w(x)$，$k=2$ 的情形就是最大化 $\dfrac 12(w(x)+w(y)+\mathrm{dist}(x,y))$，其中 $\mathrm{dist}(x,y)$ 的边权为 $c_i+d_i$ ，显然求直径即可。

以直径一端为根，每次操作就是删掉一条链，这显然是经典的贪心结论，长链剖分后排序即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
struct Edge { int v,x,y; }; //x:u->v,y:v<-u
vector <Edge> G[MAXN];
int n,q,fa[MAXN];
bool ind[MAXN];
ll sum=0,ans[MAXN],rt[MAXN],dis[MAXN];
inline void dfs0(int u,int fz) {
	for(auto e:G[u]) if(e.v^fz) rt[1]+=e.y,dfs0(e.v,u);
}
inline void dfs1(int u,int fz) {
	ans[1]=max(ans[1],rt[u]);
	for(auto e:G[u]) if(e.v^fz) rt[e.v]=rt[u]-e.y+e.x,dfs1(e.v,u);
}
inline void dfs2(int u,int fz,ll d,int &p) {
	fa[u]=fz,dis[u]=d;
	if(!p||dis[u]+rt[u]>dis[p]+rt[p]) p=u;
	for(auto e:G[u]) if(e.v^fz) dfs2(e.v,u,d+e.x+e.y,p);
}
vector <ll> len;
inline ll dfs3(int u,int fz) {
	ll mx=0;
	for(auto e:G[u]) if(e.v^fz) {
		ll tmp=e.x+dfs3(e.v,u);
		if(!mx) mx=tmp;
		else len.push_back(min(mx,tmp)),mx=max(mx,tmp);
	}
	return mx;
}
signed main() {
	scanf("%d",&n);
	for(int i=1,u,v,x,y;i<n;++i) {
		scanf("%d%d%d%d",&u,&v,&x,&y);
		sum+=x+y;
		G[u].push_back({v,x,y});
		G[v].push_back({u,y,x});
	}
	dfs0(1,0),dfs1(1,0);
	int S=0,T=0;
	dfs2(1,0,0,S);
	dfs2(S,0,0,T);
	ans[2]=(rt[S]+rt[T]+dis[T])>>1;
	for(int u=T;u;u=fa[u]) ind[u]=true;
	for(int u=T;u;u=fa[u]) {
		for(auto e:G[u]) if(e.v!=fa[u]&&!ind[e.v]) {
			len.push_back(dfs3(e.v,u)+e.x);
		}
	}
	sort(len.begin(),len.end(),greater<ll>());
	for(int i=0;i<(int)len.size();++i) ans[i+3]=ans[i+2]+len[i];
	for(int lst=len.size()+2,i=lst+1;i<=n;++i) ans[i]=ans[lst];
	scanf("%d",&q);
	for(int x;q--;) scanf("%d",&x),printf("%lld\n",sum-ans[x]);
	return 0;
}
```



---

## 作者：Graphcity (赞：0)

首先 $k=1$ 的情况就是以每个点为根的外向树权值和最小值，容易换根 DP 求出。接下来仅讨论 $k\ge 2$ 的情况。

- **观察一** ：假设选的点为 $p_{1\cdots k}$，那么这些点组成的虚树中的边不产生花费，只有从虚树向外连的边才会产生花费。

- **观察二** ：$p_{1\cdots k}$ 一定是叶子结点才最优。

  **证明** ：如果其中有虚树上的非叶子结点，显然可以删掉并加入另一个虚树外的点。对于非原树的叶子结点，把它拉长到某一个叶子只会去掉一些有花费的边。

- **观察三** ：如果 $k>2$，那么 $k$ 处的最优解一定可以由 $k-1$ 处的最优解新增一个叶子得到。

  假设的最优解必定包含 $s$。考虑以 $s$ 为根的树，容易发现加入一个叶子减少的花费为根到叶子的所有（未被选择的）有向边权值和。问题则变成了选择 $k-1$ 条边不相交的祖先链使得权值和最大。

  这是经典结论，答案肯定是前 $k-1$ 条长链之和。感性理解一下，那么 $k-1$ 处的最优解就是前 $k-2$ 条长链之和。那么 $k$ 处的最优解一定可以由 $k-1$ 处最优解新增一个叶子得到。

现在我们考虑 $k=2$ 的情况。利用之前的换根 DP 和观察一能够快速找到最优解的两个叶子 $s,t$。然后以 $s$ 为根把所有长链拉出来，排个序就行了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,S,T,val[Maxn+5],son[Maxn+5];
ll ans[Maxn+5],sum[Maxn+5],sup[Maxn+5],maxd[Maxn+5],all;
pair<ll,int> dwn[Maxn+5];
vector<pair<int,int>> v[Maxn+5];
vector<ll> w;

inline void dfs1(int x,int f)
{
    for(auto [y,z]:v[x])
    {
        if(y==f) {val[x]=z; continue;}
        dfs1(y,x),sum[x]+=sum[y]+z;
    }
}
inline void dfs2(int x,int f)
{
    ll res=sum[x]+sup[x];
    for(auto [y,z]:v[x]) if(y!=f) sup[y]=res-sum[y]-z+val[y],dfs2(y,x);
}
inline void dfs3(int x,int f)
{
    dwn[x]=make_pair(0ll,x);
    for(auto [y,z]:v[x]) if(y!=f)
    {
        dfs3(y,x); auto k=dwn[y]; k.first+=z;
        if(sup[x]+sum[x]-k.first-dwn[x].first<ans[2])
        {
            ans[2]=sup[x]+sum[x]-k.first-dwn[x].first;
            S=k.second,T=dwn[x].second;
        } dwn[x]=max(dwn[x],k);
    }
}
inline void dfs3(int x,int f,ll d)
{
    maxd[x]=d;
    for(auto [y,z]:v[x]) if(y!=f)
    {
        dfs3(y,x,d+z),all+=z,maxd[x]=max(maxd[x],maxd[y]);
        if(maxd[y]>maxd[son[x]]) son[x]=y;
    }
}
inline void dfs(int x,int f,ll d)
{
    if(!son[x]) w.push_back(d);
    for(auto [y,z]:v[x]) if(y!=f)
        {if(y==son[x]) dfs(y,x,d+z); else dfs(y,x,z);}
}
inline void Solve1()
{
    dfs1(1,0),dfs2(1,0);
    For(i,1,n) ans[1]=min(ans[1],sum[i]+sup[i]);
}
inline void Solve2() {dfs3(1,0);}

int main()
{
    n=read();
    For(i,1,n) ans[i]=inf;
    For(i,1,n-1)
    {
        int a=read(),b=read(),c=read(),d=read();
        v[a].emplace_back(b,c),v[b].emplace_back(a,d);
    }
    Solve1(),Solve2(),dfs3(S,0,0ll),dfs(S,0,0ll);
    sort(w.begin(),w.end()),reverse(w.begin(),w.end());
    for(int i=0;i<w.size();++i) all-=w[i],ans[i+2]=min(ans[i+2],all);
    For(i,2,n) ans[i]=min(ans[i],ans[i-1]);
    int q=read();
    while(q--) printf("%lld\n",ans[read()]);
    return 0;
}
```



---

