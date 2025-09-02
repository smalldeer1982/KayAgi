# Birthday

## 题目描述

Ali is Hamed's little brother and tomorrow is his birthday. Hamed wants his brother to earn his gift so he gave him a hard programming problem and told him if he can successfully solve it, he'll get him a brand new laptop. Ali is not yet a very talented programmer like Hamed and although he usually doesn't cheat but this time is an exception. It's about a brand new laptop. So he decided to secretly seek help from you. Please solve this problem for Ali.

An $ n $ -vertex weighted rooted tree is given. Vertex number $ 1 $ is a root of the tree. We define $ d(u,v) $ as the sum of edges weights on the shortest path between vertices $ u $ and $ v $ . Specifically we define $ d(u,u)=0 $ . Also let's define $ S(v) $ for each vertex $ v $ as a set containing all vertices $ u $ such that $ d(1,u)=d(1,v)+d(v,u) $ . Function $ f(u,v) $ is then defined using the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF494D/a49e19fad915afd07784c02308a91dfcb85750c8.png)The goal is to calculate $ f(u,v) $ for each of the $ q $ given pair of vertices. As the answer can be rather large it's enough to print it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5
1 2 1
4 3 1
3 5 1
1 3 1
5
1 1
1 5
2 4
2 1
3 5
```

### 输出

```
10
1000000005
1000000002
23
1000000002
```

## 样例 #2

### 输入

```
8
1 2 100
1 3 20
2 4 2
2 5 1
3 6 1
3 7 2
6 8 5
6
1 8
2 3
5 8
2 6
4 7
6 1
```

### 输出

```
999968753
49796
999961271
999991235
999958569
45130
```

# 题解

## 作者：wwwwwza (赞：9)

求 $f(u,v)=\sum\limits_{x\in S(v)} d(u,x)^2-\sum\limits_{x \notin S(v)} d(u,x)^2$。

$S(u)$ 表示 $u$ 子树内的节点。

- 当 $lca(u,v)=v$ 时。

$f(u,v)=\sum\limits_{i=1}^n d(u,i)^2-2\times\sum\limits_{x \notin S(v)} d(u,x)^2$。

- 当 $lca(u,v) \ne v$ 时。

$f(u,v)=2\times\sum\limits_{x\in S(v)}d(u,x)^2-\sum\limits_{i=1}^n d(u,i)^2$。

接下来直接换根 dp 推式子即可，式子不难推。

对于每一个 $u$ 需要求出 $\sum\limits_{i\in S(u)} d(u,i),\sum\limits_{i\in S(u)} d(u,i)^2,\sum\limits_{i=1}^n d(u,i),\sum\limits_{i=1}^n d(u,i)^2$。

答案式子只需要容斥一下即可求出。

赠送一个完全平方公式：$(a+b)^2=a^2+2ab+b^2$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
int n,m,x,y,z,dis[N],siz[N],num[N],sum[N],add[N],mul[N],fat[N][20],dep[N];
struct node{
	int v,w;
};
vector<node>g[N];
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int len=dep[x]-dep[y];
	for(int i=18;i>=0;i--){
		if(len>=(1<<i)){
			x=fat[x][i];
			len-=(1<<i);
		}
	}
	if(x==y)return x;
	for(int i=18;i>=0;i--){
		if(fat[x][i]!=fat[y][i]){
			x=fat[x][i];
			y=fat[y][i];
		}
	}
	return fat[x][0];
}
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v,w=g[u][i].w;
		if(v==fa)continue;
		dis[v]=(dis[u]+w)%mod;
		fat[v][0]=u;
		dep[v]=dep[u]+1;
		for(int j=1;j<=18;j++)fat[v][j]=fat[fat[v][j-1]][j-1];
		dfs1(v,u);
		siz[u]+=siz[v];
		num[u]=(num[u]+num[v]+siz[v]*w%mod)%mod;
		sum[u]=(sum[u]+sum[v]+(w*w%mod)*siz[v]%mod+2*num[v]*w%mod)%mod;
	}
} 
void dfs2(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v,w=g[u][i].w;
		if(v==fa)continue;
		add[v]=(add[u]-siz[v]*w%mod+(n-siz[v])*w%mod+mod)%mod;
		mul[v]=(mul[u]-2ll*w*num[v]%mod-(w*w%mod)*siz[v]%mod+(w*w%mod)*(n-siz[v])%mod+2ll*w*(add[u]-num[v]-w*siz[v]%mod+2*mod)%mod+2*mod)%mod;
		dfs2(v,u);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n;
	for(int i=1;i<n;i++){
		cin >>x>>y>>z;
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}
	dfs1(1,0);
	add[1]=num[1],mul[1]=sum[1];
	dfs2(1,0);
	cin >>m;
	while(m--){
		cin >>x>>y;
		if(lca(x,y)==y){
			int ans=(mul[y]-sum[y]+mod)%mod;
			int cnt=(dis[x]-dis[y]+mod)%mod;
			ans=(ans+2ll*cnt*((add[y]-num[y]+mod)%mod)%mod
			+(cnt*cnt%mod)*(n-siz[y])%mod)%mod;
			ans=(mul[x]-2ll*ans%mod+mod)%mod;
			cout <<ans<<"\n";
		}else{
			int cnt=(dis[x]+dis[y]-2*dis[lca(x,y)]%mod+mod)%mod;
			int ans=(sum[y]+(cnt*cnt%mod)*siz[y]%mod+2*cnt*num[y]%mod)%mod;
			ans=(2*ans%mod-mul[x]+mod)%mod;
			cout <<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：5)

$\textbf{CF494D	*2700}$

> - 给定一棵树和 $q$ 次询问，每次给出 $u,v$，询问 $\sum\limits_{x \in S(v)} d(u,x)^2 - \sum\limits_{x \notin S(v)} d(u,x)^2$，其中 $d(u,x)$ 指点 $u,x$ 的距离，$S(v)$ 指 $v$ 的子树内的点的集合。答案对 $10^9+7$ 取模。
> - $1 \le n,q \le 10^5$。

一个魔怔做法。容易发现上式等于 $2\sum\limits_{x \in S(v)} d(u,x)^2 - \sum\limits_{x \in S(1)} d(u,x)^2$，因此我们只需要计算 $\sum\limits_{x \in S(v)} d(u,x)^2 $ 的值。

把 $d(u,v)$ 写成 $(d_u + d_v-2d_l)$ 的形式（$d$ 是带权深度，$l$ 是最近公共祖先），推柿子：

$$\begin{aligned}&\sum (d_u+d_v-2d_l)^2\\=&\sum (d_u+d_v)^2 - 4d_l(d_u+d_v)+4d_l^2\\=&\sum d_u^2 + 2d_ud_v + d_v^2 - 4d_{l}(d_u+d_v)+4 \sum d_l^2\\=&nd_u^2+2d_u \sum d_v + \sum d_v^2 - 4d_u \sum d_l - 4 \sum d_vd_l + 4 \sum d_l^2\end{aligned}$$

子树在 dfn 序上即区间，因此差分后按 dfn 序加点，我们只需要维护 $\sum d_l,\sum d_vd_l,\sum d_l^2$，可以简单树剖线段树完成。

时间复杂度 $\mathcal O((n+q) \log^2 n)$，可能需要稍微卡一卡常数。[代码](https://codeforces.com/contest/494/submission/264096635)。

---

## 作者：Star_Cried (赞：2)

## CF494D Birthday

### 题意

一个1为根的带边权有根树，每次询问给定两个点 $u,v$ 求 $\sum_{x\in S(v)} d(u,x)^2-\sum_{x\not\in S(v)}d(u,x)^2$ 其中 $d(u,v)$ 表示 $u,v$ 简单路径长度， $S(u)$ 表示 $u$ 的子树内点的集合。

### 思路

考虑 $u$ 在 $v$ 内和在 $v$ 外的情况，发现可以通过每个点维护四个值——子树内所有点到其距离的和、子树内所有点到其距离的平方的和、所有点到其的距离和、所有点到其距离的平方和——来回答询问。

具体转移细节请自推，这里总结一个重点：

设 $v$ 与 $u$ 两点，$f2[v]$ 为 $v$ 子树内距离平方的和，$f[v]$ 为 $v$ 子树内距离的和，$siz[v]$ 为 $v$ 子树大小，$w$ 为两点间距离，则 $v$ 子树内所有点到 $u$ 的距离的平方和为
$$
f2[v]+2*f[v]*w+siz[v]*w^2
$$
深度优先搜索两边换根处理出以上信息后分类讨论即可。

### 代码

请注意取模。

代码中的一些取模可以被优化。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10,mod=1e9+7;
	int n;
	int ecnt,head[maxn],to[maxn<<1],nxt[maxn<<1],v[maxn<<1];
	inline void addedge(int a,int b,int c){
		to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt,v[ecnt]=c;
		to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt,v[ecnt]=c;
	}
	inline int up(int a){return a>=mod?a-mod:a;}
	inline int dn(int a){return a<0?a+mod:a;}
	int f[maxn],f2[maxn],g[maxn],g2[maxn],dep[maxn],fa[maxn][21],dis[maxn],siz[maxn];
	void dfs(int x,int father){
		fa[x][0]=father;siz[x]=1;
		dep[x]=dep[father]+1;
		for(int i=0;i<20;i++) fa[x][i+1]=fa[fa[x][i]][i];
		for(int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(u==father)continue;
			dis[u]=dis[x]+v[i];
			dfs(u,x);
			siz[x]+=siz[u];
			f[x]=up(f[x]+up(f[u]+siz[u]*v[i]%mod))%mod;
			f2[x]=((f2[x]+f2[u])%mod+(siz[u]*v[i]%mod*v[i]%mod+2*v[i]*f[u]%mod)%mod)%mod;
		}
	}
	void dfs2(int x){
		for(int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(u==fa[x][0])continue;
			g[u]=(g[x]+(n-2*siz[u]+mod)%mod*v[i]%mod)%mod;
			g2[u]=((f2[u]+(g2[x]-((f2[u]+2*v[i]%mod*f[u]%mod)%mod+siz[u]*v[i]%mod*v[i]%mod)%mod+mod)%mod)%mod+((g[x]-f[u]+mod-siz[u]*v[i]%mod+mod)%mod*2%mod*v[i]%mod+(n-siz[u])*v[i]%mod*v[i]%mod)%mod)%mod;
			dfs2(u);
		}
	}
	inline int LCA(int x,int y){
		if(dep[x]<dep[y])swap(x,y);
		for(int i=20;~i;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
		if(x==y) return x;
		for(int i=20;~i;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline void work(){
		n=read();
		for(int u,v,i=1;i<n;i++) u=read(),v=read(),addedge(u,v,read());
		dfs(1,0);
		g[1]=f[1],g2[1]=f2[1];
		dfs2(1);
		int Q=read();
		while(Q--){
			int y=read(),x=read(),lca=LCA(x,y),d=dis[x]+dis[y]-dis[lca]*2;
			d%=mod;
			if(lca==x){
				printf("%lld\n",(g2[y]-2*((((g2[x]-f2[x]+mod)%mod+2*d%mod*(g[x]-f[x]+mod)%mod)%mod+d*d%mod*(n-siz[x])%mod)%mod+mod)%mod+mod)%mod);
			}else{
				printf("%lld\n",((((f2[x]%mod+2%mod*d%mod*f[x]%mod)%mod+d%mod*d%mod*siz[x]%mod)%mod*2%mod-g2[y]%mod)%mod+mod)%mod);
			}
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：GavinZheng (赞：1)

先简述一下题意：定义$f(u,v)$为以1号点为根时，$u$点到$v$子树内的所有点的距离的平方和减去$u$点到$v$点子树外的所有点的平方和。多次询问，可以离线。

我们先试着考虑离线询问然后换根。同时维护以当前点为根，每个点到其子树内所有点的距离的和$sum1$,距离的平方和$sum2$以及子树大小$size$。

考虑如何维护。我们定义函数$trans(u,val)$表示让$sum2(u)$从子树内每个点距离的平方和变成子树内每个点距离加上$val$的平方和。根据初中数学知识就有$trans(u,val)=sum2(u)+size\times val^2+2\times val\times sum1(u)$。知道了这个以后，如何维护就很简单了，大家可以自己推推看。

然后考虑维护了这个东西之后如何求解答案。对于询问$f(u,v)$来说，当以1为根时，若$u$不在$v$子树内，那当$u$为根时,$v$换根前的子树一定等于换根后的子树。答案就是$ans=trans(v,dis(u,v))-(sum2(u)-trans(v,dis(u,v)))$。

然后我们考虑换根前，$u$在$v$子树内的情况。令$v$换根前的父亲为$fa$，答案就是$ans=(sum2(u)-trans(fa,dis(fa,u)))-trans(fa,dis(fa,u))$。

不需要任何高级数据结构，只需要一个倍增即可。（卓为啥要把这道题放数据结构专题啊喂）
```cpp
/*
                                                  
  _|_|                              _|  _|    _|  
_|    _|  _|  _|_|  _|_|_|_|        _|  _|  _|    
_|    _|  _|_|          _|          _|  _|_|      
_|    _|  _|          _|      _|    _|  _|  _|    
  _|_|    _|        _|_|_|_|    _|_|    _|    _|  
                                                                                                    
*/ 
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
//#define ls (rt<<1)
//#define rs (rt<<1|1)
#define vi vector<int>
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define fi first
#define se second
typedef long long ll;
using namespace std;
const int maxn=1e5+100;
const int mod=1e9+7;
ll sum1[maxn],sum2[maxn],size[maxn];
int dfn[maxn],dfncnt,f[maxn][20],d[maxn][20],n,dep[maxn];
vi side[maxn],w[maxn];
int trans(int u,int val){
	return (sum2[u]+size[u]*val%mod*val%mod+2*val*sum1[u]%mod)%mod;
}
void dfs1(int u,int fa){
	f[u][0]=fa;dfn[u]=++dfncnt;size[u]=1;dep[u]=dep[fa]+1;
	for(int i=0;i<side[u].size();i++){
		int v=side[u][i];if(v==fa)continue;
		dfs1(v,u);size[u]+=size[v];d[v][0]=w[u][i];
		sum1[u]=(sum1[u]+sum1[v]+w[u][i]*size[v]%mod)%mod;
		sum2[u]=(sum2[u]+trans(v,w[u][i]))%mod;
	}
}
void init(){
	rep(i,1,19)rep(j,1,n)f[j][i]=f[f[j][i-1]][i-1];
	rep(i,1,19)rep(j,1,n)d[j][i]=(d[j][i-1]+d[f[j][i-1]][i-1])%mod;
}
int get_dis(int u,int v){
	ll ans=0;
	if(dep[u]<dep[v])swap(u,v);
	for(int i=19;i>=0;i--)if(dep[f[u][i]]>=dep[v])ans=(ans+d[u][i])%mod,u=f[u][i];
	if(u==v)return ans;
	for(int i=19;i>=0;i--)if(f[u][i]!=f[v][i])ans=(1ll*ans+d[u][i]+d[v][i])%mod,u=f[u][i],v=f[v][i];
	return (1ll*ans+d[u][0]+d[v][0])%mod;
}
struct Query{
	int u,v,idx;
	bool insubtree;
}q[maxn];
int ans[maxn];
bool cmp(Query a,Query b){return dfn[a.u]<dfn[b.u];}
int now=1,t;
void dfs2(int u,int fa){
	while(now<=t&&q[now].u==u){
		int v=q[now].v,idx=q[now].idx;
		if(q[now].insubtree){
			ans[idx]=(sum2[u]-2*trans(f[v][0],get_dis(f[v][0],u)))%mod;
			ans[idx]=(ans[idx]+mod)%mod;
		}
		else{
			ans[idx]=(2*trans(v,get_dis(u,v))-sum2[u])%mod;
			ans[idx]=(ans[idx]+mod)%mod;
		}
		now++;
	}
	for(int i=0;i<side[u].size();i++){
		int v=side[u][i];if(v==fa)continue;
		ll bku1=sum1[u],bku2=sum2[u],bku3=size[u];
		ll bkv1=sum1[v],bkv2=sum2[v],bkv3=size[v];
		int tmp1=trans(v,w[u][i]),tmp2=trans(u,w[u][i])-trans(v,2*w[u][i]%mod);tmp2=(tmp2%mod+mod)%mod;
		sum1[u]=(bku1-(bkv1+w[u][i]*bkv3)%mod)%mod;sum1[u]=(sum1[u]%mod+mod)%mod;
		sum1[v]=((bku1-(bkv1+w[u][i]*bkv3)%mod)+(bku3-bkv3)*w[u][i]%mod+bkv1)%mod;sum1[v]=(sum1[v]%mod+mod)%mod;
		
		sum2[u]=(bku2-tmp1)%mod;sum2[u]=(sum2[u]%mod+mod)%mod;
		sum2[v]=tmp2+bkv2;sum2[v]=(sum2[v]%mod+mod)%mod;
		
		size[u]=bku3-bkv3;size[v]=bku3;
		dfs2(v,u);
		sum1[u]=bku1,sum2[u]=bku2,size[u]=bku3;
		sum1[v]=bkv1,sum2[v]=bkv2,size[v]=bkv3;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n-1){
		int u,v,val;cin>>u>>v>>val;
		side[u].pb(v);w[u].pb(val);
		side[v].pb(u);w[v].pb(val);
	}
	dfs1(1,0);
	init();cin>>t;
	rep(i,1,t){
		cin>>q[i].u>>q[i].v;q[i].idx=i;
		if(dfn[q[i].v]<=dfn[q[i].u]&&dfn[q[i].u]<=dfn[q[i].v]+size[q[i].v]-1)q[i].insubtree=1;
	}
	sort(q+1,q+1+t,cmp);
	dfs2(1,0);
	rep(i,1,t){
		cout<<(ans[i]%mod+mod)%mod<<endl;
	}
	return 0;
}
```




---

## 作者：ty_mxzhn (赞：1)

无聊透顶题。考虑转化原式变为 $\displaystyle 2\sum_{i\in S(v)} d(u,i)^2 -\displaystyle\sum_{i\in S(1)}d(u,i)^2$。

问题变为如何求 $\displaystyle \sum_{i\in S(v)}d(u,i)^2$。

分类讨论 $u$ 是否在 $v$ 子树下。如果 $u$ 不在 $v$ 子树下，则直接拆解完全平方式，每一部分都是可以简单预处理的。具体的来说就是预处理每个点子树到子树根的距离的和与平方和。

如果 $u$ 在 $v$ 子树下，则在 $u$ 子树内的答案直接预处理。其他贡献考虑额外预处理所有点到某个点的距离的和与平方和，这样计算贡献是简单的。

代码太无聊透顶，就不放了。大概就是用完全平方式子计算贡献，所有点到一个点就换根 dp 即可。

---

## 作者：baka24 (赞：0)

提供一个细节少的好写做法。

首先 $S(u)$ 就是在 $u$ 子树内的点。

我们可以把答案拆成两种形式：

$$
2\times\sum_{x\in S(v)}d(x,u)-\sum_{x=1}^nd(x,u)
$$
或者
$$
\sum_{x=1}^nd(x,u)-2\times\sum_{x\notin S(v)}d(x,u)
$$

考虑如何维护平方和。根据平方和公式，有：

$$
\sum_{i=1}^k (x_i+y)^2=\sum_{i=1}^k x_i^2+\sum_{i=1}^k 2xy+k\times y^2
$$

维护平方和、和、数的数量即可。

为了避免麻烦，这部分的计算都可以通过封装一个结构体来完成。

设 $f_x=\sum_{i\in S(x)}d(x,i),g_x=\sum_{i\notin S(x)}d(x,i)$。

我们定义 $*$ 表示平方数的合并（平方数只会与常数合并）。

$$
f_u=\sum f_v*w\\
g_v=g_u+f_u-f_v*w
$$

按照如上方式递推，即可求出 $f,g$。

关于递推式，分别相当于：合并所有子树的答案，$v$ 子树外的点等价于 $u$ 子树外的点和 $u$ 子树内去掉 $v$ 子树的点。

得到 $f,g$ 后考虑询问如何做。

对于一个询问，它有这样两种形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/8dax0r6g.png)

对于图一，求出 $\sum_{x\notin S(v)}d(x,u)$，即 $g_v$ 和 $dis(u,v)$ 合并在一起。

对于图二，求出 $2\times\sum_{x\in S(v)}d(x,u)$，即 $f_v$ 和 $dis(u,v)$ 合并在一起。

而对于 $\sum_{i=1}^n d(x,i)$，直接把 $f_x,g_x$ 加起来即可。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inx(u) int I=h[(u)],v=edge[I].v,w=edge[I].w;I;I=edge[I].nx,v=edge[I].v,w=edge[I].w
int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return x*f;}
const int MAXN=200010,N=20,M=15,Mod=1e9+7;
struct Edge{int v,nx,w;}edge[MAXN<<1];int h[MAXN],CNT=1;void add_side(int u,int v,int w){edge[++CNT]={v,h[u],w};h[u]=CNT;edge[++CNT]={u,h[v],w};h[v]=CNT;}
int n,m,k,ans,fa[MAXN][N+3],dep[MAXN],sd[MAXN];
struct node{
    int z,p,p2;
    node operator*(const int&G)const{
        node res;
        res.z=z;
        res.p=(p+G*z%Mod)%Mod;
        res.p2=(p2+2*p%Mod*G%Mod+G%Mod*G%Mod*z%Mod)%Mod;
        return res;
    }
    node operator+(const node&G)const{
        node res;
        res.z=(z+G.z)%Mod;
        res.p=(p+G.p)%Mod;
        res.p2=(p2+G.p2)%Mod;
        return res;
    }
    node operator-(const node&G)const{
        node res;
        res.z=(z-G.z)%Mod;
        res.p=(p-G.p)%Mod;
        res.p2=(p2-G.p2)%Mod;
        return res;
    }
}f[MAXN],g[MAXN];
int lca(int x,int y){
    if(sd[x]<sd[y])swap(x,y);
    for(int i=N;~i;i--)if(sd[fa[x][i]]>=sd[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=N;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void dfs1(int u,int lst){
    fa[u][0]=lst;
    f[u]={1,0,0};
    for(inx(u))if(v!=lst){
        dep[v]=(dep[u]+w)%Mod;
        sd[v]=sd[u]+1;
        dfs1(v,u);
        f[u]=f[u]+(f[v]*w);
    }
}
void dfs2(int u,int lst){
    if(u==1)g[u]={0,0,0};
    for(inx(u))if(v!=lst){
        g[v]=(g[u]+(f[u]-(f[v]*w)))*w;
        dfs2(v,u);
    }
}
void slv(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add_side(u,v,w);
    }
    dfs1(1,1),dfs2(1,1);
    for(int i=1;i<=N;i++)for(int j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
    m=read();
    while(m--){
        int x=read(),y=read(),l=lca(x,y),ds=(dep[x]+dep[y]-dep[l]*2)%Mod;
        if(l==y)printf("%lld\n",((f[x].p2+g[x].p2-(g[y]*ds).p2*2)%Mod+Mod)%Mod);
        else printf("%lld\n",(((f[y]*ds).p2*2-f[x].p2-g[x].p2)%Mod+Mod)%Mod);
    }
}
signed main(){
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    slv();
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<"s\n";    
    return 0;
}
```

---

## 作者：sosksyx_is_my_wife (赞：0)

考察一下本题给出的一些抽象定义。

先考察 $S(u)$，这显然是愚蠢的，因为显然表示的是 $u$ 的子树。

再考察一下 $f(u,v)=\sum_{x \in S(v)} d(u,x)^2-\sum_{x \notin S(v)} d(u,x)^2$，这显然可以转化为 $f(u,v)=2\sum_{x \in S(v)} d(u,x)^2-\sum_{x \in S(1)} d(u,x)^2$。

后面那一坨换根算：

设 $f_u$ 表示 $u$ 子树内的点到 $u$ 的距离之和，$g_u$ 表示 $u$ 子树内的点到 $u$ 的距离平方之和。

则有转移：

$f_u\gets f_v+w\cdot siz_v$；

$g_u\gets g_v + 2w\cdot f_v + siz_v\cdot w^2$；

直接换根即可。

前面那一坨相当于算 $v$ 子树内的点到 $u$ 的距离的平方和，考虑用点什么技巧维护。

发现 $u$ 在 $v$ 内的数量计算有点复杂，但是如果在 $v$ 的子树外就很简单，所以情况讨论。

#### Case I

当 $u$ 不在 $v$ 的子树内，这是简单的。

考虑把贡献拆成两部分：$u\to v$，$v \to x$。

两个部分分别拼起来，就是 $v$ 子树的点到 $u$ 的距离的平方和了。

具体的：

先计算出 $u\to v$ 的距离 $d$，这显然可以用差分一步到位，然后和考虑用 $d$ 和 $v$ 内的点拼起来。

推敲一下组合意义即可：

设 $v$ 子树内的点到 $v$ 的距离分别为 $x_1,x_2,\cdots,x_k$。

则距离平方之和 $D$ 为：
$$
\begin{aligned}
  D&=(x_1+d)^2+(x_2+d)^2+\cdots+(x_k+d)^2\\
  &=(x_1^2+x_2^2+\cdots+x_k^2)+2d(x_1+x_2+\cdots+x_k)+kd^2\\
  &= g_v^2+2df_v+d^2\cdot siz_v
  \end{aligned}
$$

该情况得到解决。
#### Case II

当 $u$ 在 $v$ 的子树内，这稍微复杂一点，还是把距离拆成两部分：一部分在 $u$ 的子树内，一部分不在 $u$ 的子树内。

前者很显然就是 $g_u$，后者发现有点复杂。

考虑把 $u\to v$ 的路径及子树剥离出来，构成一只毛毛虫，发现别的点的贡献算在 $u\to v$ 这条链上的点是一个比较简单的方法。

可问题是，$u\to v$ 这条链上的点到 $u$ 的距离都不一样，怎么做啊？

基本功好一点的同学应该能看出来，这是可以用倍增维护的。

具体地：

设 $G_{u,0}$ 表示对于 $u$ 父亲的子树内，刨除 $u$ 子树内的点，其余点到 $u$ 的距离的平方和，$G_{u,i}$ 可以推广到 $u$ 的 $2^i$ 的祖先的情况。

这是好维护的，考虑一次更新，假如我们现在要更新 $G_{u,i}$，设 $p=fa_{u,i-1}$；

那么，$G_{u,i}$ 相当于把 $G_{u,i-1}$ 和 $G_{p,i-1}$ 这两段拼起来，前面那一段是简单的，后面那一段发现只需要同意加上 $p\to u$ 的距离即可！

仿照上面的分析方式，仿照 $G$，设 $F_{u,i}$ 表示向上跳 $2^i$ 次，刨除链上经过的点的子树，其余点到 $u$ 的距离和。

设 $S_{u,i}$ 表示扣除向上跳 $2^i$ 的链上经过点的子树总共经过的点数，这个也是好倍增维护的。

则有转移：

$F_{u,i}\gets F_{u,i-1}+F_{p,i-1}+S_{p,i-1}\cdot dis_{u,p}$；

$G_{u,i}\gets G_{u,i-1}+G_{p,i-1}+S_{p,i-1}\cdot dis_{u,p}^2+2dis_{u,p}\cdot F_{p,i-1}$；

至于 $dis_{u,p}$ 也是好维护的，倍增即时记录即可。

最后答案拼起来就可以啦！

时间复杂度 $\mathcal{O}(n\log n)$，巨大常数巨难写。

讲个笑话，我忘记可以差分直接大力倍增维护距离，写了一下午，居然通过了：

好孩子别学我。

```cpp
void dfs1(int u){
    	dfn[u]=++times;
    	dep[u]=dep[fa[u][0]]+1;
    	siz[u]=1;
    	for(int i=p[u];i;i=e[i].nxt){
    		int  v=e[i].v,w=e[i].w;
    		if(v==fa[u][0]) continue;
    		fa[v][0]=u;F[v][0]=w;G[v][0]=w*w%mod;
    		dfs1(v);
    		L[v]=f[v]+siz[v]*w%mod;R[v]=(dp[v]+2*f[v]*w%mod+siz[v]*w%mod*w%mod)%mod;
    		f[u]=(f[u]+L[v])%mod;
    		dp[u]=(dp[u]+R[v])%mod;
    		siz[u]+=siz[v];
    	}
    	for(int i=p[u];i;i=e[i].nxt){
    		int v=e[i].v,w=e[i].w;
    		if(v==fa[u][0]) continue;
    		J[v][0]=siz[u]-siz[v];
    		H[v][0]=((mod+f[u]-L[v])%mod+J[v][0]*w)%mod;
    		I[v][0]=(((mod+dp[u]-R[v])%mod+w*w%mod*J[v][0]%mod)%mod+2*(mod+H[v][0]-J[v][0]*w%mod)%mod*w%mod)%mod;
    	}
    	tf[u]=f[u];tdp[u]=dp[u];
    }
    void dfs2(int u){
    	for(int i=1;i<=17;i++){
    		fa[u][i]=fa[fa[u][i-1]][i-1];
    		F[u][i]=(F[u][i-1]+F[fa[u][i-1]][i-1])%mod;
    		G[u][i]=((G[u][i-1]+G[fa[u][i-1]][i-1])%mod+2*F[u][i-1]%mod*F[fa[u][i-1]][i-1]%mod)%mod;
    		
    		J[u][i]=J[u][i-1]+J[fa[u][i-1]][i-1];
    		H[u][i]=((H[u][i-1]+H[fa[u][i-1]][i-1])%mod+(J[fa[u][i-1]][i-1]*F[u][i-1])%mod)%mod;
    		I[u][i]=(I[u][i-1]+((I[fa[u][i-1]][i-1]+G[u][i-1]*J[fa[u][i-1]][i-1]%mod)%mod+2*H[fa[u][i-1]][i-1]%mod*F[u][i-1]%mod)%mod)%mod;
    	}
    	for(int i=p[u];i;i=e[i].nxt){
    		int v=e[i].v,w=e[i].w;
    		if(v==fa[u][0]) continue;
    		int x3=(mod+f[u]-L[v])%mod,x4=(mod+dp[u]-R[v])%mod;
    		x4=(x4+(n-siz[v])*w%mod*w%mod+2*x3%mod*w%mod)%mod;x3=(x3+(n-siz[v])*w%mod)%mod;		
    		f[v]=(f[v]+x3)%mod;dp[v]=(dp[v]+x4)%mod;
    		dfs2(v);
    	}
    }
    int lca(int x,int y){
    	if(dep[x]<dep[y]) swap(x,y);
    	for(int i=17;i>=0;i--){
    		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    	}
    	if(x==y)return x;
    	for(int i=17;i>=0;i--){
    		if(fa[x][i]!=fa[y][i]){
    			x=fa[x][i];y=fa[y][i];
    		}
    	}
    	return fa[x][0];
    }
    void getup(int &a,int &b,int v,int lca){
    	for(int i=17;i>=0;i--){
    		if(dep[fa[v][i]]>=dep[lca]){
    			b=((b+G[v][i])%mod+2*F[v][i]%mod*a%mod)%mod;
    			a=(a+F[v][i])%mod;
    			v=fa[v][i];
    		}
    	}
    }
    void calc(int u,int v){
    	int l=lca(u,v);
    	int a=0,b=0,c=0,d=0;
    	getup(a,b,u,l);getup(c,d,v,l);
    	int sz=siz[v];
    	d=((d*sz%mod+tdp[v])%mod+2*tf[v]%mod*c%mod)%mod;
    	c=(sz*c+tf[v])%mod;
    	int ans=2*((sz*b%mod+d)%mod+2*c%mod*a%mod)%mod;
    	cout<<(mod+ans-dp[u])%mod<<'\n';
    }
    void sbcalc(int &b,int v,int lca){
    	int x=0,y=0;
    	for(int i=17;i>=0;i--){
    		if(dep[fa[v][i]]>=dep[lca]){
    			b=(b+((I[v][i]+J[v][i]*y%mod)%mod+2*x%mod*H[v][i]%mod)%mod)%mod;
    			y=((y+G[v][i])%mod+2*x%mod*F[v][i]%mod)%mod;x=(x+F[v][i])%mod;
    			v=fa[v][i];
    		}
    	}
		b=((b+I[v][0]+J[v][0]*y%mod)%mod+2*x%mod*H[v][0]%mod)%mod;
    }
    void sbti(int u,int v){
    	int l=u;
    	for(int i=17;i>=0;i--){
    		if(dep[fa[l][i]]>=dep[v]+1) l=fa[l][i];
    	}
		int b=0;
    	sbcalc(b,u,l);
    	int ans=2*(b+tdp[u])%mod;			
    	cout<<(mod+ans-dp[u])%mod<<'\n';
    }



```

---

