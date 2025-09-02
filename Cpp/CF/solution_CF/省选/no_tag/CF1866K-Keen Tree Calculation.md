# Keen Tree Calculation

## 题目描述

给定一棵 $N$ 个点，$N-1$ 条边的树，第 $i$ 条边连接 $U_i$ 和 $V_i$，长度为 $W_i$。

这棵树的拥有者 Chaneka 想问你 $Q$ 个问题，对于第 $j$ 个问题，格式如下：

* $X_j,K_j$ 表示询问当与第 $X_j$ 个点连接的所有边长度变成原来的 $K_j$ 倍时，树的直径长度为多少。

## 说明/提示

* 询问不会真实影响这棵树的任何边，即询问间互相独立。
* 树的直径为树上不同两点的最短路径长度的最大值。

## 样例 #1

### 输入

```
7
5 1 2
1 4 2
3 4 1
2 5 3
6 1 6
4 7 2
2
4 3
3 2```

### 输出

```
18
11```

## 样例 #2

### 输入

```
3
1 2 1000000000
2 3 1000000000
1
2 1000000000```

### 输出

```
2000000000000000000```

# 题解

## 作者：ღꦿ࿐ (赞：2)

简单题。

新树的直径一定经过了翻倍的点或者为原树的直径。

先使用换根求出每个点子树内以及子树外最远点的距离，然后接下来对于一个询问的点，我们关心每个儿子内及这个子树的补树内最远的点距离加上这条边翻倍后的长度的最大值和次大值。

假设某个子树内最远点为 $f_v$，到该子树的边的长度为 $w_v$，那么我们相当于要对于某个给出的 $k$，求出 $k w_v + f_v$ 的最大值及次大值。

求最大值是简单的，使用李超线段树或者凸包维护即可。

考虑如何求次大值：（与最大值不同的次大值）

凸包求法：

维护所有 $f_i(x)=k_ix+b_i$ 构成的下凸包，查询最大值对应的直线。

次大值一定被这两种情况包含：

- 不在这个下凸包上的直线上：用这些直线再建一个凸包查询即可。
- 凸包上的前一条或者后一条直线。

一定不可能被凸包上的其它直线包含，因为这些值以及在对应位置是低于前一条或后一条直线的。


李超树求法：

查询最大值及其位置。

查询去除这个最大值后的最大值。

扣掉某个元素的常见做法是维护后缀和前缀信息：维护每个点的前 $i$ 条直线，后 $i$ 条直线的李超树 $pre_i,suf_i$，然后在 $pre_{mx-1},suf_{mx+1}$ 里面查就行了。实现可以离线或者使用可持久化李超树。

[代码](https://codeforces.com/contest/1866/submission/221707553)

---

## 作者：CuCl4Loliko (赞：1)

### Preface

跟同学组队 VP 这场 ICPC，整场都在调这一题，结果赛后发现二分写错了。

### Problem

给出一棵树，边有边权，每次询问给出一个点 $u$ 和一个常数 $k$，求与这个点相连的边的边权乘 $k$ 后的树的直径。

### Solution

不难想到，树的直径只有两种情况，即原树的直径或从这个点出发的两个最长链组成的直径。前者是好求得的，而后者则略有困难。

注意到只有与点 $u$ 相连的边会乘 $k$，那么从 $u$ 出发的链的长度都应该为形如 $w_i \times k + l_i$ 的形式。其中 $w_i$ 为 $u$ 与 $v$ 之间的边权，$l_i$ 为点 $v$ 向外的最长链的长度。

$l_i$ 是易得的，做简单的换根 DP 就可以得到子树内最长链和子树外最长链，不再赘述。

关键在于如何求上面式子的最值。我们将询问全部离线到每个节点上，将这个形式的贡献看做是平面上的直线，维护一个凸包，询问最大值。

假设直线 $i$ 是 $x$ 取值时的最大值，那么次大值就肯定位于直线 $1$ 到 $i-1$ 和直线 $i+1$ 到 $tot$ 组成的集合中的最大值，也就是一个前缀跟一个后缀拼起来的最大值。

对于每个节点，先从凸包上找出最大值，并记录下来他的位置，再将这些位置全部排序，重新正序将直线插入凸包，再倒序插入凸包。

维护一个双指针，当插入到需要查询次大值的时候，直接在当前凸包求出答案。有点二次离线的味道。

注意答案还要和原树的直径取一次 $\max$。

维护凸包可以用单调栈或者李超树实现，赛时代码用的单调栈。

### Code

[单调栈二分版本](https://codeforces.com/contest/1866/submission/222528547)

[可持久化李超树版本](https://codeforces.com/contest/1866/submission/222527534)

---

## 作者：activeO (赞：0)

## 题目大意

给定一棵树，边有边权，每次询问 $ x,y $，问将于点 $ x $ 相连的边的边权都乘 $ k $ 时，树的直径。

## 做法

每次询问改变边权后，答案可以分成两种情况：经过 $ x $ 的，和不经过 $ x $ 的。

- 不经过 $ x $ 的就是原来的树的直径（如果树的直径包括 $ x $，那么显然经过 $ x $ 的路径更优，不用讨论），这个可以直接预处理。

- 经过 $ x $ 的路径：

我们可以考虑把路径拆开，提前预处理出以 $ x $ 为开头的路径的最大值和次大值，注意这里最大值和次大值不能经过同一个点，这样就可以把最大值和次大值拼接成一条路径。

对于一次查询，发现改变后出现的以 $ x $ 为开头的路径就变为：

$$ k \times dis(x,v) + maxdis_v $$

这里 $ k $ 表示这次询问翻的倍数，$ v $ 表示与 $ x $ 相接的点（可以是父亲），$ dis(x,v) $ 是 $ x $ 和 $ v $ 连的边的权值，$ maxdis_v $，表示**不经过 $ x $ 的以 $ v $ 为开头的权值最大**的路径。

然后发现上面的那个式子是一个一次函数的形式，容易想到可以把询问离线下来，对于每个点的答案用李超线段树维护。但是我们要知道最大值和次大值。

然后有一个求次大值的套路，就是剔除最大直线后，他前一条的前缀的最大值和后一条的后缀最大值的 $ \max $。于是可以用可持久化李超线段树来维护前缀最大值，后后缀最大值。

## 代码

```cpp
// Problem: Keen Tree Calculation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1866K
// Memory Limit: 500 MB
// Time Limit: 2000 ms

#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef pair<int,int> pii;

const int maxn=2e5+5;
// const int inf=0x3f3f3f3f;
struct edge{
	int to,nxt,d;
}e[maxn<<1];
int head[maxn],len;
int prert[maxn],sufrt[maxn],lsh[maxn],cnt=0;
struct func{
	int k,b;
	func(){
		k=b=0;
	}
	func(int kk,int bb){
		k=kk;
		b=bb;
	}
	int f(int x){
		return k*lsh[x]+b;
	}
}ln[maxn];
int tr[maxn<<6],lc[maxn<<6],rc[maxn<<6],tot=0,ltot=0,maxx=0;

inline void init(){
	memset(head,-1,sizeof(head));
	len=0;
}
void add(int u,int v,int d){
	e[++len].to=v;
	e[len].d=d;
	e[len].nxt=head[u];
	head[u]=len;
}

int update(int root,int l,int r,int x){
	int now=++tot;
	tr[now]=tr[root];
	lc[now]=lc[root];
	rc[now]=rc[root];
	if(l==r){
		if(ln[tr[now]].f(l)<ln[x].f(l)) tr[now]=x;
		return now;
	}
	int mid=(l+r)>>1;
	if(ln[tr[now]].f(mid)<ln[x].f(mid)) swap(tr[now],x);
	if(ln[tr[now]].f(l)<ln[x].f(l)) lc[now]=update(lc[now],l,mid,x);
	else if(ln[tr[now]].f(r)<ln[x].f(r)) rc[now]=update(rc[now],mid+1,r,x);
	return now;
}
int query(int now,int l,int r,int x){
	// printf("%lld %lld %lld %lld : %lld %lld\n",now,l,r,lsh[x],ln[tr[now]].k,ln[tr[now]].b);
	if(!now) return 0;
	if(l==r) return tr[now];
	int mid=(l+r)>>1,res=tr[now];
	if(x<=mid){
		int tmp=query(lc[now],l,mid,x);
		if(ln[res].f(x)<ln[tmp].f(x)) res=tmp;
	}else{
		int tmp=query(rc[now],mid+1,r,x);
		if(ln[res].f(x)<ln[tmp].f(x)) res=tmp;
	}
	return res;
}

int dis[maxn][3],up[maxn],w[maxn];

void dfs1(int u,int f){// 预处理向下的最大路径和向下的次大路径
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		w[v]=e[i].d;
		dfs1(v,u);
		if(dis[v][0]+e[i].d>dis[u][0]){
			dis[u][1]=dis[u][0];
			dis[u][0]=dis[v][0]+e[i].d;
		}else if(dis[v][0]+e[i].d>dis[u][1]) dis[u][1]=dis[v][0]+e[i].d;
	}
	maxx=max(maxx,dis[u][0]+dis[u][1]);
	// printf("%lld : %lld %lld\n",u,dis[u][0],dis[u][1]);
}
void dfs2(int u,int f){// 预处理向上的最大路径
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		up[v]=up[u]+e[i].d;
		if(dis[u][0]!=dis[v][0]+e[i].d) up[v]=max(up[v],dis[u][0]+e[i].d);
		else up[v]=max(up[v],dis[u][1]+e[i].d);
		// printf("%lld : %lld %lld %lld\n",v,up[v],dis[u][0],dis[v][0]);
		dfs2(v,u);
	}
	// printf("kk%d : %lld %lld %lld\n",u,up[u],dis[u][0],dis[u][1]);
}

vector<pii> que[maxn];
int res[maxn];

void dfs3(int u,int f){
	tot=0;
	ltot=0;
	prert[0]=0;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f){
			int tt=up[v];
			if(dis[v][0]!=dis[u][0]+e[i].d) tt=max(tt,dis[v][0]);
			else tt=max(tt,dis[v][1]);
			ln[++ltot]=func(e[i].d,tt);
			prert[ltot]=update(prert[ltot-1],1,cnt,ltot);
			continue;
		}
		ln[++ltot]=func(e[i].d,dis[v][0]);
		prert[ltot]=update(prert[ltot-1],1,cnt,ltot);
	}
	sufrt[ltot+1]=0;
	for(int j=ltot;j>=1;j--) sufrt[j]=update(sufrt[j+1],1,cnt,j);
	for(pii x : que[u]){
		int tt=query(prert[ltot],1,cnt,x.first);// 最大路径
		// if(tt==0) printf("oh no%lld : %lld %lld %lld\n",x.second,x.first,tt,ln[tt].f(x.first));
		// printf("kk%lld %lld %lld %lld %lld\n",prert[tt-1],tt,cnt,x.first,sufrt[tt+1]);
		// printf("pair %lld %lld %lld %lld\n",sufrt[tt+1],x.first,ltot,cnt);
		int tt3=query(sufrt[tt+1],1,cnt,x.first);// 后缀最大
		int tt2=query(prert[tt-1],1,cnt,x.first);// 前缀最大
		// printf("kk%lld %lld\n",cnt,x.first);
		// printf("%lld %lld\n",x.first,cnt);
		// printf("kk%lld %lld %lld %lld %lld %lld\n",tt-1,prert[tt-1],1ll,cnt,x.first,tot);
		if(ln[tt2].f(x.first)<ln[tt3].f(x.first)) tt2=tt3;
		res[x.second]=max(maxx,ln[tt].f(x.first)+ln[tt2].f(x.first));
	}
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		dfs3(v,u);
	}
}

struct Que{
	int x,y;
	Que(){}
	Que(int xx,int yy){
		x=xx;
		y=yy;
	}
}qq[maxn];

signed main(){
	
	init();
	
	int n,q;
	
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		int u,v,d;
		scanf("%lld %lld %lld",&u,&v,&d);
		add(u,v,d);
		add(v,u,d);
	}
	
	dfs1(1,0);
	dfs2(1,0);
	
	scanf("%lld",&q);
	for(int i=1;i<=q;i++){
		scanf("%lld %lld",&qq[i].x,&qq[i].y);
		lsh[++cnt]=qq[i].y;
	}
	
	sort(lsh+1,lsh+cnt+1);
	cnt=unique(lsh+1,lsh+cnt+1)-lsh-1;
	for(int i=1;i<=q;i++){
		int tmp=lower_bound(lsh+1,lsh+cnt+1,qq[i].y)-lsh;
		que[qq[i].x].push_back(make_pair(tmp,i));
	}
	
	dfs3(1,0);
	
	for(int i=1;i<=q;i++) printf("%lld\n",res[i]);
	
	return 0;
}
```


---

## 作者：JWRuixi (赞：0)

~~终于在 duel 你面赢了龟一场~~

### 题意

给定一棵带边权树，$Q$ 此询问 `u k`：若将与 $u$ 相连的边边权 $\times k$，那么树的直径会是多少。

$n,Q \le 10^5, 1 \le k$，提交地址：<https://www.luogu.com.cn/problem/CF1866K>。

### 分析

考虑将贡献分两类，路径经过 $u$ 和不经过 $u$。如果不经过 $u$，则不受 $\times k$ 的影响，所以可以直接用原树直径，因为原直径若经过  $u$， $\times k$ 后必会变大。

考虑经过 $u$ 怎么统计，不难在将其分成在其子树内和子树外两种贡献。

对于上方的点，只有 $w(u, par_u)$ 收 $\times k$ 的影响，直接对于 $u$ 的每一个祖先，统计其子树中（且不是指向 $u$ 的方向）的最深 $dep$，可以从上到下预处理。具体的，对每个点预处理子树内最大深度 $d_u$，让后对于每个点的儿子预处理前后缀 $d$ 的最大值。

考虑叶子部分的贡献形如 $\max\limits_{v \in son_u}d_v - dep_v + k \times w(u, v)$，稍加转换就成了上凸包求最大截距，注意到可能需要求次大值，考虑将询问离线下来，找出最大值的取值点，动态的维护前缀和后缀的凸包，在对应的位置查询次大值。

时间复杂度 $\mathcal O(n \log n)$。

### Code

提交记录：<https://codeforces.com/contest/1866/submission/229700714>。

---

## 作者：shinkuu (赞：0)

~~李超线段树二次离线~~。

容易发现，将和某个点 $x$ 相邻的边权翻若干倍后，直径所在位置有两种可能：经过或不经过该点。不经过可以跑一次直接求，否则还要分类讨论一下。

- $\operatorname{deg}_x=1$

那么它会作为直径的一个端点。

- 否则

直径会从一条边进，另一条边出。

前者是简单的，后者发现将 $x$ 变为根后，直径长度可以写成 $\max_{(x,u,w)\in E}(w\times k+dis_u)+\operatorname{secmax}_{(x,u,w)\in E}(w\times k+dis_u)$，其中 $dis_i$ 表示点 $i$ 到以 $i$ 为根的子树中的点距离的最大值。

这是若干个一次函数的形式，可以上李超树维护。但是要求次大值，怎么办呢？可以考虑先求出最大值的位置，并求出除了这个位置外的最大值。发现这是一段前缀加一段后缀。把这个问题再离线下来跑一次就行了。

code：

```cpp
bool Mbe;
int n,m,q,V=1e9,c[N],fa[N];
ll firlen,ans[N],res[N],dw[N],up[N];
int tot,head[N];
vector<pii> g[N],h[N][2];
struct node{int to,nxt,cw;}e[N<<1];
struct Node{ll k,b;}ln[N];
il void add(int u,int v,int w){e[++tot]={v,head[u],w},head[u]=tot;}
il ll calc(int i,ll x){return ln[i].k*x+ln[i].b;}
struct SGT{
	int tr[M],ls[M],rs[M],cur,rt;
	il void init(){while(cur)tr[cur]=ls[cur]=rs[cur]=0,cur--;rt=0;}
	void update(int l,int r,int &o,int x){
		if(!o)o=++cur;
		if(l==r){
			if(calc(x,l)>calc(tr[o],l))tr[o]=x;
			return;
		}
		int mid=(l+r)>>1;
		if(calc(x,mid)>calc(tr[o],mid))swap(x,tr[o]);
		if(calc(x,l)>calc(tr[o],l))update(l,mid,ls[o],x);
		else update(mid+1,r,rs[o],x);
	}
	int query(int l,int r,int o,int x){
		if(!o||l==r)return tr[o];
		int mid=(l+r)>>1,ret=0;
		if(x<=mid)ret=query(l,mid,ls[o],x);
		else ret=query(mid+1,r,rs[o],x);
		if(!ret||!tr[o])return ret|tr[o];
		return calc(ret,x)>calc(tr[o],x)?ret:tr[o];
	}
}T;
void dfs1(int u,int f){
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u),dw[u]=max(dw[u],dw[v]+e[i].cw);
	}
}
void dfs2(int u,int f){
	ll mx=0,secmx=0;fa[u]=f;
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		if(dw[v]+e[i].cw>mx)secmx=mx,mx=dw[v]+e[i].cw;
		else if(dw[v]+e[i].cw>secmx)secmx=dw[v]+e[i].cw;
	}
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		if(dw[v]+e[i].cw==mx)up[v]=max(up[u]+c[u],secmx);
		else up[v]=max(up[u]+c[u],mx);
		c[v]=e[i].cw,dfs2(v,u);
	}
	if(up[u]>mx)secmx=mx,mx=up[u];
	else if(up[u]>secmx)secmx=up[u];
	firlen=max(firlen,mx+secmx);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	dfs1(1,0),dfs2(1,0);
	scanf("%d",&q);
	rep(i,1,q){
		int x,y;scanf("%d%d",&x,&y);
		g[x].eb(Mp(y,i));
	}
	rep(u,1,n){
		T.init(),m=0;
		go(i,u){
			int v=e[i].to;
			if(v==fa[u])continue;
			ln[++m]={e[i].cw,dw[v]};
		}
		if(u!=1)ln[++m]={c[u],up[u]};
		rep(i,1,m)T.update(1,V,T.rt,i);
		if(m==1){
			for(auto [i,j]:g[u])ans[j]=calc(T.query(1,V,T.rt,i),i);
			continue;
		}
		rep(i,1,m)h[i][0].clear(),h[i][1].clear();
		for(auto [i,j]:g[u]){
			int p=T.query(1,V,T.rt,i);
			ans[j]=calc(p,i);
			h[p-1][0].eb(Mp(i,j));
			h[p+1][1].eb(Mp(i,j));
		}
		T.init();
		rep(i,1,m){
			T.update(1,V,T.rt,i);
			for(auto [j,k]:h[i][0])res[k]=max(res[k],calc(T.query(1,V,T.rt,j),j));
		}
		T.init();
		drep(i,m,1){
			T.update(1,V,T.rt,i);
			for(auto [j,k]:h[i][1])res[k]=max(res[k],calc(T.query(1,V,T.rt,j),j));
		}
	}
	rep(i,1,q)printf("%lld\n",max(firlen,ans[i]+res[i]));
}
bool Med;
signed main(){
	cerr<<1.*(&Mbe-&Med)/1048576<<'\n';
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

