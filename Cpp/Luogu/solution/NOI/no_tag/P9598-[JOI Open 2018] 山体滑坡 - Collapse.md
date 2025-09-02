# [JOI Open 2018] 山体滑坡 / Collapse

## 题目描述

I 先生有一个 $C$ 天的电缆建设计划。第 $(i+1)\ (0\le i\le C-1)$​ 天的计划用三个整数 $T_i,X_i,Y_i$ 表示，分别表示：

- 如果 $T_i=0$，他们会架设一段连接城镇 $X_i$ 与城镇 $Y_i$ 的电缆。保证在第 $(i+1)$ 天开始的时候城镇 $X_i$ 与城镇 $Y_i$ 之间没有电缆。
- 如果 $T_i=1$​，他们会拆除一段连接城镇 $X_i$​ 与城镇 $Y_i$​ 的电缆。保证在第 $(i+1)$​ 天开始的时候城镇 $X_i$​ 与城镇 $Y_i$​ 之间有电缆。

JOI 国经常发生山体滑坡。如果在城镇 $x$ 与 $x+1\ (0\le x\le N-2)$​ 之间发生山体滑坡，则只有连接两端编号均不超过 $x$ 与编号均不少于 $x+1$ 城镇的电缆可用。在 JOI 国，每当山体滑坡发生，他们就会选择一些城镇建设基站。基站应满足对于任意城镇，都可以通过一些可用的电缆与基站连通。

I 先生在建设阶段就在考虑山体滑坡发生时应建设多少基站。他有 $Q$ 个问题：第 $(j+1)$ 个问题用两个整数 $W_j,P_j$ 表示，表示他想知道在 $(W_j+1)$ 天结束时，如果在城镇 $P_j$ 和 $P_j+1$ 之间发生山体滑坡，至少应该建立多少基站。

你作为 I 先生的助理，负责写一个程序去回答 I 先生的问题。

## 说明/提示

**【样例】**

考虑有 $5$ 个城镇的情况。接下来用 $(x,y)$ 代表连接城镇 $x$ 和城镇 $y$ 的电缆。

- 假设当有四根电缆 $(0,1),(1,3),(2,4),(4,0)$ 时，在城镇 $1$ 和 $2$ 之间发生了滑坡。电缆 $(1,3)$ 和 $(4,0)$ 不可用了，因此可用的电缆是 $(0,1)$ 和 $(2,4)$。你需要在城镇 $0,2,3$ 建立基站。最少要建立基站数为 $3$。
- 假设当有六根电缆 $(0, 1), (0, 3), (1, 2), (2, 4), (4, 0)$​​ 和 $(4,3)$​​ 时，在城镇 $3$​​ 和 $4$​​ 之间发生了滑坡。电缆 $(2,4),(4,0)$​​ 和 $(4,3)$​​ 不可用了，因此可用的电缆是 $(0,1),(0,3)$​​ 和 $(1,2)$​​。你需要在城镇 $0$​​ 和 $4$ 建立基站。最少要建立基站数为 $2$​​。

**【数据范围】**

本题有四个子任务。子任务分值及附加限制如下表所示：

| 子任务编号 | 分值 |              $N$               |              $C,Q$               |              附加限制              |
| :--------: | :--: | :----------------------------: | :------------------------------: | :--------------------------------: |
|    $1$     | $5$  |       $2\le N\le 5\ 000$       |       $1\le C,Q\le 5\ 000$       |                 无                 |
|    $2$     | $30$ |      $2\le N\le 100\ 000$      |      $1\le C,Q\le 100\ 000$      | 所有 $P_j\ (0\le j\le Q-1)$ 都相等 |
|    $3$     | $30$ | $2\le N\le 100\ 000$ | $1\le C,Q\le 100\ 000$ |      $T_i=0\ (0\le i\le C-1)$      |
|    $4$     | $35$ |      $2\le N\le 100\ 000$      |      $1\le C,Q\le 100\ 000$      |                 无                 |



## 样例 #1

### 输入

```
5 8 2
0 0 1
0 1 3
0 2 4
0 4 0
1 1 3
0 0 3
0 1 2
0 4 3
3 1
7 3
```

### 输出

```
3
2```

# 题解

## 作者：forest114514 (赞：9)

### P9598 [JOI Open 2018] 山体滑坡

给一个认为 $\alpha(n)$ 近似于 $O(1)$ 和 $n,q,c$ 同阶时时间复杂度为 $O(n\sqrt n)$ 的做法。

一句话，多次删边和加边，问你 $[0,x]$ 和 $[x+1,n-1]$ 两个点集和其点集间的连边构成的联通块数之和，然后不难发现两部分是独立的，以 $[0,x]$ 为例。

没有修改考虑按 $x$ 排序用并查集加点维护联通块数量，可以做到线性对数；有修改时发现修改对询问的贡献需要花费 $\Theta(\text{修改数量})$ 的时间，自然想到操作分块，吐槽一下删除操作就是纯纯增加代码量但没有任何思维含量的东西。

我们 $B$ 个操作分一块，块内询问按 $x$ 排序，然后每次询问相当于在原图基础上加 $O(B)$ 条边再问你连通块的数量。

新加边还要撤回操作的话使用可撤销并查集多一个 $\log n$ 的复杂度，此时时间为 $O(qB\log n+\frac{nc}{B}\log n)=O(n\sqrt n\log n)$ ，注意到除了询问的时候加边之外不需要撤销直接路径压缩，可以做到 $O(qB\log n+\frac{nc}{B})=O(n\sqrt {n\log n})$。

不过都不是很牛，我们想一想怎么优化？

我们考虑在 $[0,x]$ 点集加上 $B$ 条边后的连通块数就是 $[0,x]$ 形成的连通块数减去 $B$ 条边合并的联通块数，考虑把 $[0,x]$ 的联通块按其 $fa$ 缩成一个点，然后再这个 $O(B)$ 个点的新图上看减少了几个连通块，可以用一个新的并查集来维护，然后就能 $O(B)$ 完成单组询问，最后做到 $O(qB+\frac{nc}{B})=O(n\sqrt n)$ 的时间复杂度，当然空间复杂度是 $O(n)$。

代码：

```cpp
const int N=1e5+100,B=350;
int n,c,q,x[N],y[N],e[N],op[N],ans[N],fa[N],ff[N],tot,cnt,cnt2,ct;
LL hs[N];
int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);} 
int getf2(int x){return x==ff[x]?x:ff[x]=getf2(ff[x]);}
vector<pii> que[N],opt[N];
vector<int> E[N];
bool vis[N],fl[N];
void merge(int x,int y){
	x=getf(x),y=getf(y);
	if(x==y) return;
	++cnt,fa[x]=y;
}
void add(int x,int y){
	x=getf(x),y=getf(y);
	if(x==y) return;
	x=getf2(x),y=getf2(y);
	if(x==y) return;
	ff[x]=y,++cnt2;
}
void del(int x,int y){
	x=getf(x),y=getf(y);
	ff[x]=x,ff[y]=y;
}
//bool _ED;
signed main(){
	//fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,c,q);
	rep(i,1,c) {
		read(op[i],x[i],y[i]);
		++x[i],++y[i];
		if(x[i]>y[i]) swap(x[i],y[i]);
		hs[i]=1ll*x[i]*n+y[i];
	}
	sort(hs+1,hs+1+c);
	ct=unique(hs+1,hs+1+c)-hs-1;
	rep(i,1,c) e[i]=lower_bound(hs+1,hs+1+ct,1ll*x[i]*n+y[i])-hs;
	rep(i,1,q){
		int t,x;
		read(t,x);
		++t,++x;
		que[t].pb({x,i});
	}
	tot=(c+B-1)/B;
	int l=0,r=0;
	
	rep(T,1,tot){
		l=r+1,r=min(l+B-1,c);
		rep(i,l,r) fl[e[i]]=1;
		
		rep(i,1,n) opt[i].clear(),ff[i]=fa[i]=i,E[i].clear();
		rep(i,l,r) for(auto j:que[i]) opt[j.fi].pb({i,j.sc});
		rep(i,1,l-1) if(vis[e[i]]&&(!fl[e[i]])) E[y[i]].pb(x[i]);
		cnt=0;
		rep(u,1,n){
			for(auto v:E[u]) merge(u,v);
			for(auto j:opt[u]){
				int t=j.fi,id=j.sc;
				cnt2=0;
				rep(i,l,t) vis[e[i]]^=1;
				rep(i,l,r) if(vis[e[i]]&&y[i]<=u) add(x[i],y[i]);
				ans[id]-=cnt+cnt2;
				rep(i,l,r) del(x[i],y[i]);
				rep(i,l,t) vis[e[i]]^=1;
			}
		}
		
		rep(i,1,n) opt[i].clear(),ff[i]=fa[i]=i,E[i].clear();
		rep(i,l,r) for(auto j:que[i]) opt[j.fi+1].pb({i,j.sc});
		rep(i,1,l-1) if(vis[e[i]]&&(!fl[e[i]])) E[x[i]].pb(y[i]);
		cnt=0;
		per(u,n,1){
			for(auto v:E[u]) merge(u,v);
			for(auto j:opt[u]){
				int t=j.fi,id=j.sc;
				cnt2=0;
				rep(i,l,t) vis[e[i]]^=1;
				rep(i,l,r) if(vis[e[i]]&&x[i]>=u) add(x[i],y[i]);
				ans[id]-=cnt+cnt2;
				rep(i,l,r) del(x[i],y[i]);
				rep(i,l,t) vis[e[i]]^=1;
			}
		}
		rep(i,l,r) vis[e[i]]^=1,fl[e[i]]=0;
	}
	rep(i,1,q) write(n+ans[i],'\n');
	//fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：Luciylove (赞：8)

给出一个比较好想的 $O(n \log^2 n)$ 做法。

注意到有一个很暴力的 $O(n \sqrt n \log n)$ 的 KDT 分治做法，我们想一想能不能用条件刻画掉一个维度将原问题放在线段树分治上面解决。

注意到连通性问题还是要往 LCT 上面想，我们考虑挑 $W_i$ 这一个维度进行线段树分治，然后就变成了数我们最爱的连通块个数。

这里可以利用 P5385 复习一下 LCT 维护生成树数连通块。

注意到中间劈开的一刀 $[P_i, P_i + 1]$ 分成的左右两边的连通块答案是独立的，然后只要利用 LCT 维护 $\max(X, Y)$ 的最小生成树和 $\min(X, Y)$ 的最大生成树，分别统计这两棵树上满足 $\max(X, Y) \leq P_i$ 和 $\min(X, Y) \geq (P_i + 1)$ 的边的个数，拿一个树状数组即可。

复杂度 $O(n \log^2 n)$。

实现注意封装一下估计会写的短一些。

[Code](https://www.luogu.com.cn/paste/7ug60zn6)

---

## 作者：_lbw_ (赞：3)

将题目中的编号加 $1$。

我们考虑每条边对答案的贡献，边 $(X,Y)$ 能贡献到区间 $[1,X-1]$ 和 $[Y,n]$ 的 $P$。

于是问题剩下两维，每条边会作用到一个矩阵内，问连通块个数。

建出 kdt，在 kdt 上面跑类似线段树分治的 kdt 分治。

需要注意空间，本做法在 $T=0$ 时好像是最慢的。

```cpp
#define ll long long
using namespace std;
#define I ll
#define her1 20081214
#define IV void
#define cht 1000000007
#define ld long double
#define Aestas16 392699
#define ull unsigned long long
#define cp(x,y)memcpy(x,y,sizeof y)
#define mem(x,val)memset(x,val,sizeof x)
#define D(i,j,n)for(register int i=j;i>=n;i--)
#define E(i,now)for(register int i=first[now];i;i=e[i].nxt)
#define F(i,j,n)for(register int i=j;i<=n;i++)
#define DL(i,j,n)for(register i64 i=j;i>=n;i--)
#define EL(i,now)for(register i64 i=first[now];i;i=e[i].nxt)
#define FL(i,j,n)for(register i64 i=j;i<=n;i++)
ll read(){
	ll ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')ans=ans*10+c-'0',c=getchar();
	return ans*f;
}
#undef ll
#include "assert.h"
mt19937_64 rnd(her1);
#include "functional"
using i64 = long long;
const int maxn = 2e5+5;
i64 n,c,q,T[maxn],X[maxn],Y[maxn],Ans[maxn];

i64 fa[maxn],dep[maxn],ans,top;
struct node{i64 x,y,d;}stk[maxn];
i64 find(i64 x){return fa[x]==x?x:find(fa[x]);}
IV Merge(i64 x,i64 y){
	i64 svx=x,svy=y;
	x=find(x);y=find(y);if(x==y)return;
	if(dep[x]<dep[y])swap(x,y);fa[y]=x;
	stk[++top]={x,y,dep[x]==dep[y]};dep[x]+=(dep[x]==dep[y]);ans--;
}
IV Back(){auto[x,y,d]=stk[top--];fa[y]=y;dep[x]-=d;ans++;}
struct point{i64 x,y,id;}qwq[maxn];

i64 lx[maxn],rx[maxn],ly[maxn],ry[maxn],id[maxn],oc,ls[maxn],rs[maxn];
IV Build(i64&o,i64 l,i64 r,bool tp){
	o=++oc;
	if(l==r){
		lx[o]=rx[o]=qwq[l].x,ly[o]=ry[o]=qwq[l].y,id[o]=qwq[l].id;
		return;
	}
	i64 mid=l+r>>1;
	if(!tp)nth_element(qwq+l,qwq+mid,qwq+r+1,[](point A,point B){return A.x==B.x?A.y<B.y:A.x<B.x;});
	if( tp)nth_element(qwq+l,qwq+mid,qwq+r+1,[](point A,point B){return A.y==B.y?A.x<B.x:A.y<B.y;});
	Build(ls[o],l,mid,!tp);Build(rs[o],mid+1,r,!tp);
	lx[o]=min({lx[ls[o]],lx[rs[o]]});rx[o]=max({rx[ls[o]],rx[rs[o]]});
	ly[o]=min({ly[ls[o]],ly[rs[o]]});ry[o]=max({ry[ls[o]],ry[rs[o]]});
}
bool check_Union(i64 Lx,i64 Rx,i64 Ly,i64 Ry,i64 lx,i64 rx,i64 ly,i64 ry){
	return Rx<lx||rx<Lx||Ry<ly||ry<Ly;
}
bool check_In(i64 Lx,i64 Rx,i64 Ly,i64 Ry,i64 lx,i64 rx,i64 ly,i64 ry){
	return Lx<=lx&&rx<=Rx&&Ly<=ly&&ry<=Ry;
}
struct Node{i64 Lx,Rx,Ly,Ry,u,v;};
map<pair<i64,i64>,i64>mp;vector<Node>vi;
IV clr(vector<Node>&Tmp){
	vector<Node>tmp;tmp.swap(Tmp);
}
IV Q(i64 o,vector<Node>V){
	i64 siz=top;
	vector<Node>vl,vr;
	for(auto[Lx,Rx,Ly,Ry,u,v]:V){
		if(check_In(Lx,Rx,Ly,Ry,lx[o],rx[o],ly[o],ry[o]))
			Merge(u,v);
		else{
			if(!check_Union(Lx,Rx,Ly,Ry,lx[ls[o]],rx[ls[o]],ly[ls[o]],ry[ls[o]]))
				vl.push_back({Lx,Rx,Ly,Ry,u,v});
			if(!check_Union(Lx,Rx,Ly,Ry,lx[rs[o]],rx[rs[o]],ly[rs[o]],ry[rs[o]]))
				vr.push_back({Lx,Rx,Ly,Ry,u,v});
		}
	}
	if(!ls[o]&&!rs[o])Ans[id[o]]=ans;
	else Q(ls[o],vl),Q(rs[o],vr);
	while(top>siz)Back();
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	lx[0]=ly[0]=1e9;
	n=read();c=read();q=read();
	F(i,1,c){
		T[i]=read(),X[i]=read()+1,Y[i]=read()+1;
		if(X[i]>Y[i])swap(X[i],Y[i]);
		if(!T[i])mp[{X[i],Y[i]}]=i;
		else{
			vi.push_back({mp[{X[i],Y[i]}],i-1,1,X[i]-1,X[i],Y[i]});
			vi.push_back({mp[{X[i],Y[i]}],i-1,Y[i],n-1,X[i],Y[i]});
			mp.erase({X[i],Y[i]});
		}
	}
	for(auto[A,i]:mp){
		vi.push_back({i,c,1,X[i]-1,X[i],Y[i]});
		vi.push_back({i,c,Y[i],n-1,X[i],Y[i]});
	}
	F(i,1,q){
		i64 w=read()+1,p=read()+1;
		qwq[i]={w,p,i};
	}
	F(i,1,n)fa[i]=i;i64 rt;Build(rt,1,q,0);
	ans=n;Q(rt,vi);F(i,1,q)printf("%d\n",Ans[i]);


	return 0;
}
```

---

## 作者：C1942huangjiaxu (赞：3)

可以发现，对于询问中的 $x$，我们要求的就是仅保留 $[0,x]$ 中的点和边的连通块数，和仅保留 $[x+1,N-1]$ 中的点和边的连通块数。

前缀和后缀本质相同，考虑如何求出 $[0,x]$ 的连通块数。

对于每条边 $(x_i,y_i)(x_i\lt y_i)$，求出其存在的时间 $[l_i,r_i]$。

考虑对询问分块，将询问按照**时间**排好序后，每 $B$个询问一起处理。

设当前 $B$ 个询问的时间区间为 $[L,R]$。

将询问按照 $x$ 排序，按照 $x$ 从小到大扫描线。

对于 $(x_i,y_i)(x_i\lt y_i)$，如果 $[l_i,r_i]$ 包含 $[L,R]$，称其为 **类型 1** 的边，否则，若 $[l_i,r_i]$ 与 $[L,R]$ 有交，称其为 **类型 2** 的边。

对于每条类型 1 的边，在扫描到 $y_i$ 时加入，这部分会进行 $O(\frac {CQ} B)$ 次。

对于类型 2 的边，每个询问暴力加入合法的边，类似序列分块，每条边只会成为类型 2 的边 $O(1)$ 次，这一部分会进行 $O(CB)$ 次。

使用可撤销并查集维护连通块数，取 $B=\sqrt Q$，时间复杂度 $O(C\sqrt Q\log N)$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,B=400;
int n,c,q,ce,ans[N],fa[N],sz[N],st[N],tp;
struct edge{
	int t,x,y;
}e[N];
struct Edge{
	int t1,t2,x,y;
}E[N];
struct qry{
	int p,w,id;
}a[N];
map<pair<int,int>,int>mp;
vector<int>e1[N],e2[N];
bool cmp1(qry a,qry b){
	return a.p<b.p;
}
bool cmp2(qry a,qry b){
	return a.w<b.w;
}
int gf(int x){
	return fa[x]==x?x:gf(fa[x]);
}
void merge(int x,int y){
	x=gf(x),y=gf(y);
	if(x==y)return;
	if(sz[x]<sz[y])swap(x,y);
	fa[y]=x,sz[x]+=sz[y],st[++tp]=y;
}
void pop(int tmp){
	while(tp!=tmp){
		int y=st[tp--];
		sz[fa[y]]-=sz[y];
		fa[y]=y;
	}
}
int main(){
	scanf("%d%d%d",&n,&c,&q);
	for(int i=1;i<=c;++i)scanf("%d%d%d",&e[i].t,&e[i].x,&e[i].y);
	for(int i=c;i;--i){
		if(e[i].x>e[i].y)swap(e[i].x,e[i].y);
		++e[i].x,++e[i].y;
		if(e[i].t)mp[make_pair(e[i].x,e[i].y)]=i-1;
		else{
			if(mp.count(make_pair(e[i].x,e[i].y)))E[++ce]={i,mp[make_pair(e[i].x,e[i].y)],e[i].x,e[i].y};
			else E[++ce]={i,c,e[i].x,e[i].y};
		}
	}
	for(int i=1;i<=q;++i){
		scanf("%d%d",&a[i].w,&a[i].p);
		++a[i].w,++a[i].p,a[i].id=i,ans[i]=n;
	}
	sort(a+1,a+q+1,cmp2);
	for(int i=1,L,R;i<=q;i+=B){
		L=i,R=min(q,i+B-1);
		vector<int>b;
		for(int j=1;j<=n;++j)e1[j].clear(),e2[j].clear();
		for(int j=1;j<=ce;++j){
			if(E[j].t1<=a[L].w&&E[j].t2>=a[R].w){
				e1[E[j].y].push_back(E[j].x);
				e2[E[j].x].push_back(E[j].y);
				continue;
			}
			if(E[j].t2<a[L].w||E[j].t1>a[R].w)continue;
			b.push_back(j);
		}
		sort(a+L,a+R+1,cmp1);
		for(int j=1;j<=n;++j)fa[j]=j,sz[j]=1;
		tp=0;
		for(int j=L,k=1;j<=R;++j){
			while(k<=a[j].p){
				for(auto v:e1[k])merge(v,k);
				++k;
			}
			int tmp=tp;
			for(auto v:b)if(E[v].t1<=a[j].w&&E[v].t2>=a[j].w&&E[v].y<=a[j].p)merge(E[v].x,E[v].y);
			ans[a[j].id]-=tp;
			pop(tmp);
		}
		for(int j=1;j<=n;++j)fa[j]=j,sz[j]=1;
		tp=0;
		for(int j=R,k=n;j>=L;--j){
			while(k>a[j].p){
				for(auto v:e2[k])merge(v,k);
				--k;
			}
			int tmp=tp;
			for(auto v:b)if(E[v].t1<=a[j].w&&E[v].t2>=a[j].w&&E[v].x>a[j].p)merge(E[v].x,E[v].y);
			ans[a[j].id]-=tp;
			pop(tmp);
		}
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Daniel1234 (赞：2)

## 思路

来一个优秀的 $O(n \log ^2 n)$。

方便起见，本文默认所有起始点为 $1$。

首先，我们只需解决 $ \left[ 1,p \right ] $ 的询问即可。

考虑定义 $u,v$ 之间的边权为 $\max(u,v)$，问题转化为求一个当前时间下的最小生成森林中边权小于等于 $p$ 的有几条边。

由于既有插入也有删除操作，使用线段树分治将操作变为插入和撤销。

参考 [P3206 [HNOI2010] 城市建设](https://www.luogu.com.cn/problem/P3206) 的做法，每次使用 kruskal 优化边数：

若把当前区间涉及到的边的边权都设为 $\inf$，跑完 kruskal 后没有连接的边在这段区间内的任意一个叶子都不会连接，也就是说我们可以删掉这条边。

同理，若把当前区间涉及到的边的边权都设为 $-\inf$，跑完 kruskal 后仍然连接的边最后一定会连接，也就是说我们可以保留这条边。

容易证明，操作后仍然不确定是否连接的边只有 $O(len)$
 条，其中 $len$ 为当前分治区间的长度。

 所以使用可撤销并查集同时维护一个树状数组记录边权即可，时间复杂度 $O(n \log ^2 n)$，默认 $n,c,q$ 同阶。

 ## code

 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, c, q;
map<pair<int, int>, int> mp;
int in[100005];
int times[100005];
pair<int, int> a[100005];
int len;
vector<pair<int, int> > f[400005], F[400005];
int w[100005], p[100005];
int t[100005], x[100005], y[100005];
void chg(int now, int l, int r, int x, int y, pair<int, int> k){//加入边数
    if(x > y)return;
    F[now].emplace_back(k);
    if(x <= l && r <= y){
        f[now].emplace_back(k);
        return;
    }
    int mid = l+r>>1;
    if(x <= mid)chg(now * 2, l, mid, x, y, k);
    if(y > mid)chg(now * 2 + 1, mid + 1, r, x, y, k);
}
struct DSU{//可撤销并查集 + 树状数组
    int fa[100005], sz[100005];
    int f[100005];
    struct node{
        int x, y, val;
    };
    stack<node> stk;
    int lowbit(int x){
        return x & (-x);
    }
    void chg(int x, int delta){
        while(x <= n){
            f[x] += delta;
            x += lowbit(x);
        }
    }
    int qry(int x){
        int ans = 0;
        while(x){
            ans += f[x];
            x -= lowbit(x);
        }
        return ans;
    }
    void init(int n){//初始化
        for(int i = 1; i <= n; i++){
            fa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return fa[x] == x ? fa[x] : find(fa[x]);
    }
    bool merge(int x, int y, int val = 1){//合并两个点
        x = find(x), y = find(y);
        if(x == y)return 0;
        chg(val, 1);
        if(sz[x] < sz[y])swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        stk.emplace(node{x, y, val});
        return 1;
    }
    void set(){//设置断点
        stk.emplace(node{-1, -1, -1});
    }
    void back(){//撤销至上一个断点
        while(stk.size()){
            auto [x, y, val] = stk.top();stk.pop();
            if(x == -1)break;
            fa[y] = y;
            sz[x] -= sz[y];
            chg(val, -1);
        }
    }
}B;
vector<pair<int, int> > useful, nw, h[100005];
int flag[100005];
int ans[100005];
void run(int now, int l, int r){
    for(int i = 0; i < useful.size(); i++)flag[i] = 0;
    B.set();
    int num = 0;
    for(auto [x, y] : useful){
        if(!B.merge(a[x].first, a[x].second))flag[num] = -1;
        num++;
    }
    B.back();
    B.set();
    B.set();
    for(auto [x, y] : F[now])B.merge(a[x].first, a[x].second);
    num = 0;
    for(auto [x, y] : useful){
        if(B.merge(a[x].first, a[x].second))flag[num] = 1;
        num++;
    }
    B.back();
    nw.clear();
    for(int i = 0; i < useful.size(); i++){
        auto [x,y] = useful[i];
        if(flag[i] == -1)continue;
        if(flag[i] == 1)B.merge(a[x].first, a[x].second, y);
        else nw.emplace_back(useful[i]);
    }
    useful = nw;
}
void px(vector<pair<int, int> > &x, vector<pair<int, int> > y){//排序
    vector<pair<int, int> > ans;
    ans.reserve(x.size() + y.size());
    int z1 = 0, z2 = 0;
    while(z1 < x.size() && z2 < y.size()){
        if(x[z1].second < y[z2].second)ans.emplace_back(x[z1++]);
        else ans.emplace_back(y[z2++]);
    }
    while(z1 < x.size())ans.emplace_back(x[z1++]);
    while(z2 < y.size())ans.emplace_back(y[z2++]);
    x = ans;
}
void solve(int now, int l, int r){//线段树分治
    auto bf = useful;
    px(useful, f[now]);
    if(l == r){
        B.set();
        for(auto [x, y] : useful)B.merge(a[x].first, a[x].second, y);
        for(auto [x, y] : h[l])ans[y] += x - B.qry(x);
        useful = bf;
        B.back();
        return;
    }
    int mid = l+r>>1;
    run(now * 2, l, mid);
    solve(now * 2, l, mid);
    B.back();
    useful = bf;
    px(useful, f[now]);
    run(now * 2 + 1, mid + 1, r);
    solve(now * 2 + 1, mid + 1, r);
    B.back();
    useful = bf;
}
void solve(){
    for(int i = 1; i <= c; i++){
        auto [u, v] = a[x[i]];
        chg(1, 1, c, times[x[i]] + 1, i - 1, make_pair(x[i], t[i]==0?n+1:v));
        times[x[i]] = i - 1;
        in[x[i]] ^= 1;
    }
    for(int i = 1; i <= len; i++){
        auto [u, v] = a[i];
        chg(1, 1, c, times[i]+1, c, make_pair(i, in[i]?v:n+1));
        in[i] = 0;
        times[i] = 0;
    }
    B.init(n);
    for(int i = 1; i <= q; i++){
        h[w[i]].emplace_back(p[i], i);
    }
    for(int i = 1; i <= c * 4; i++)sort(f[i].begin(), f[i].end(), [&](auto x, auto y){
        return x.second < y.second;
    });
    solve(1, 1, c);
    for(int i = 1; i <= c; i++)h[i].clear();
    for(int i = 1; i <= c * 4; i++)f[i].clear();
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> c >> q;
    for(int i = 1; i <= c; i++){
        cin >> t[i] >> x[i] >> y[i];
        if(x[i] > y[i])swap(x[i], y[i]);
        x[i]++, y[i]++;
        if(!mp[{x[i], y[i]}]){
            mp[{x[i], y[i]}] = ++len;
            a[len] = {x[i], y[i]};
        }
        x[i] = mp[{x[i], y[i]}];
    }
    for(int i = 1; i <= q; i++){
        cin >> w[i] >> p[i];
        w[i]++;
        p[i]++;
    }
    solve();
    for(int i = 1; i <= q; i++)p[i] = n - p[i];
    for(int i = 1; i <= len; i++)swap(a[i].first, a[i].second), a[i].first = n - a[i].first + 1, a[i].second = n - a[i].second + 1;
    solve();
    for(int i = 1; i <= q; i++){
        cout << ans[i] << '\n';
    }
    return 0;
}
```

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/19015260)

主播主播，你怎么调了一上午这个题，是不是可撤销并查集写了路径压缩啊 /yun

# 思路

为了方便，将题目中所有 0-index 改为 1-index。

切掉 $[p,p + 1]$ 等价于计算 $[1,p],[p + 1,n]$ 两个点集和其连边构成的连通块数之和。两个问题相互独立，现只考虑 $[1,p]$ 的计算方法。

对时间轴分块，设块长为 $B$，$L_i,R_i$ 分别表示块 $i$ 的左右端点。考虑计算时间在块 $i$ 中的询问，注意到此时在 $[1,i)$ 块中的操作一定会被使用，因此可以将所有 $[1,i)$ 块中的操作全部丢到并查集中。

需要注意的是，记 $nxt_i$ 表示对于一个加边操作 $i$，删除这条边的时间，特别的若没有删除这条边的操作，$nxt_i = +\infty$。若对于块 $x$ 有一个操作 $i$，那么当 $L_x \leq nxt_i \leq R_x$ 时不能提前将这条边丢到并查集里面，因为对于一个询问不知道这个删除时间在其之前还是在其之后。我们记可以直接丢进并查集的边集为 $E_1$，不可以直接丢进去的边集为 $E_2$。

对于在块 $x$ 中的询问按照 $p$ 从小到大排序离线，对于在块 $x$ 的 $E_1$ 边按照 $\max(u,v)$ 排序。考虑双指针，将所有 $E_1$ 中 $\max(u,v)$ 小于等于当前询问 $p$ 的边全部加到并查集里面。

对于一个询问时间为 $t$，则在块中满足条件的在 $t$ 之前的边也应该加入并查集，但是这些边对于后面的询问不一定会加入所以需要可撤销并查集。时间复杂度 $\Theta(\frac{n^2 \log n}{B} + nB)$，当 $B = \sqrt{n \log n}$ 时最优，得复杂度 $\Theta(n \sqrt{n \log n})$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> pip;
const int N = 1e5 + 10;
const int inf = 1e9 + 10;
int n,m,q;
map<pii,int> lst;
vector<pii> Q[N];
int nxt[N],ans[N];
int tp,fp[N],sz[N],stk[N];

struct operation{
    int op,x,y;
}O[N];

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
    if (fp[x] == x) return fp[x];
    else return find(fp[x]);
}

inline int merge(int a,int b){
    int x = find(a),y = find(b);
    if (x == y) return 0;
    if (sz[x] < sz[y]) swap(x,y);
    sz[fp[stk[++tp] = y] = x] += sz[y];
    return 1;
}

inline void remove(){
    int y = stk[tp--];
    sz[fp[y]] -= sz[y];
    fp[y] = y;
}

inline void solve(){
    #define L(x) ((x - 1) * B + 1)
    #define R(x) (min(m,(x) * B))

    const int B = sqrt(m * 16);
    for (re int i = 1;L(i) <= m;i++){
        tp = 0;
        vector<pii> pv;
        vector<int> nv;
        vector<pip> qv;
        for (re int i = 1;i <= n;i++) sz[fp[i] = i] = 1;
        for (re int j = L(i);j <= R(i);j++){
            for (pii p:Q[j]) qv.push_back({p.snd,{j,p.fst}});
        }
        for (re int j = 1;j < L(i);j++){
            if (!O[j].op){
                if (nxt[j] > R(i)) pv.push_back({max(O[j].x,O[j].y),j});
                else if (L(i) <= nxt[j] && nxt[j] <= R(i)) nv.push_back(j);
            }
        } sort(pv.begin(),pv.end());
        sort(qv.begin(),qv.end(),[](const pip &a,const pip &b){ return a.snd.snd < b.snd.snd; });
        for (re int p = 0,q = 0,cnt = 0;p < qv.size();p++){
            int tot = 0;
            while (q < pv.size() && pv[q].fst <= qv[p].snd.snd) cnt += merge(O[pv[q].snd].x,O[pv[q].snd].y),q++;
            for (int x:nv){
                if (max(O[x].x,O[x].y) <= qv[p].snd.snd && nxt[x] > qv[p].snd.fst) tot += merge(O[x].x,O[x].y);
            }
            for (re int j = L(i);j <= qv[p].snd.fst;j++){
                if (!O[j].op){
                    if (max(O[j].x,O[j].y) <= qv[p].snd.snd && nxt[j] > qv[p].snd.fst) tot += merge(O[j].x,O[j].y);
                }
            } ans[qv[p].fst] += (qv[p].snd.snd - cnt - tot);
            while (tot--) remove();
        }
    }

    #undef L
    #undef R
}

int main(){
    n = read(),m = read(),q = read();
    fill(nxt,nxt + m + 1,inf);
    for (re int i = 1,op,x,y;i <= m;i++){
        op = read(),x = read(),y = read();
        if (x > y) swap(x,y);
        O[i] = {op,++x,++y};
        if (!op) lst[{x,y}] = i;
        else nxt[lst[{x,y}]] = i;
    }
    for (re int i = 1,a,b;i <= q;i++){
        a = read(),b = read();
        Q[++a].push_back({++b,i});
    } solve();
    for (re int i = 1;i <= m;i++) O[i] = {O[i].op,n - O[i].x + 1,n - O[i].y + 1};
    for (re int i = 1;i <= m;i++){
        for (re int j = 0;j < Q[i].size();j++) Q[i][j].fst = n - Q[i][j].fst;
    } solve();
    for (re int i = 1;i <= q;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

模拟赛被创飞了。

我们先发现，$[0,p]$ 和 $(p,n)$ 的点一定不连通，所以我们先将贡献拆成两份，并且问题是相似的。

问题变成编号在 $[0,p]$ 的连通块数。

考虑线段树分治，然后我们发现根本没法做。

要是边端点编号是不降的，可以很好维护。那么考虑时间轴分块。

默认边 $(u,v)$，$u<v$。

考虑将 $B$ 为一块，那么在我们可以找出这段时间上一定会出现的边，将这些边按照 $v$ 从小到大加入，对于每个询问，在所有 $v\le x$ 的边被加入的时候，我们再把所有在块内会造成影响的边，这是 $O(B)$ 的，可以统计答案，最后撤销。

需要撤销，所以时间复杂度为 $O((\frac mB\times m+qB)\log n)$，默认 $n,m,q$ 同阶的话，取 $B=\sqrt n$。

有 $O(n\sqrt n \log n)$，至少我过不去。

下一步，考虑只有里面要撤销，考虑外面用路径压缩，里面撤销，$O(\frac mB\times m\alpha (n)+qB\log n)$，认为 $\alpha (n)$，为常数的话。

取 $B=\sqrt{\frac{n}{\log n}}$，那么为 $O(n\sqrt{n\log n})$，有较小常数的人过了，我还是过不去。

最后我们发现，不妨，并查集合并外边后，在内部又建并查集。

在原图上连通块缩点，然后又再一个新并查集上合并，这时可以路径压缩了，撤销由于只有 $O(B)$ 个点，可以直接改。

时间复杂度 $O(n^{1.5})$，轻松跑过。

:::info[代码]
```cpp
#include<bits/stdc++.h>
using namespace std;;
const int B=350,Maxn=1e5+5;
struct Edge{
	int l,r,u,v;
}E[Maxn];
bool cmp(Edge x,Edge y){
	return x.v<y.v;
}
struct Quest{
	int id,ti,p;
};
int sz[Maxn],fa[Maxn],ff[Maxn];
int find(int u){
//	cout<<u<<"\n";
	if(ff[u]==u)return u;
	return ff[u]=find(ff[u]);
}
int find2(int u){
	if(fa[u]==u)return u;
	return fa[u]=find2(fa[u]);
}
int cnt2;
void add(int x,int y){
	x=find2(x),y=find2(y);
	if(x==y)return;
	x=find(x);y=find(y);
	if(x==y)return;
	cnt2++;
	ff[x]=y;
}
void del(int x,int y){
	x=find2(x);y=find2(y);
	ff[x]=x;ff[y]=y;
}

vector<int>vec[Maxn/B+5];
vector<int>vec3[Maxn],vecu[Maxn];
vector<Quest>vec2[Maxn/B+5];
int ans[Maxn];
int n,m,q,cnt,tim;
int Bid[Maxn],lcnt;
pair<int,int>Log[Maxn];
map<pair<int,int>,int >mp;
int main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0),cout.tie(0);
////	freopen("random3.in","r",stdin);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		Bid[i]=(i-1)/B+1;
	}
	tim=m;
	for(int i=1;i<=m;i++){
		int t,u,v;
		cin>>t>>u>>v;
		u++;v++;
		if(u>v)swap(u,v);
		if(t==0)mp[{u,v}]=i;
		else {
			E[++cnt]={mp[{u,v}],i-1,u,v};
			mp[{u,v}]=0;
		}
	}
	for(auto& y:mp){
//		
		if(y.second==0)continue;
//		cout<<y.second<<" "<<m<<" "<<y.first.first<<" "<<y.first.second<<"\n";
		E[++cnt]={y.second,m,y.first.first,y.first.second};
	}
	m=cnt;cnt=0;
	sort(E+1,E+m+1,cmp);
	for(int i=1;i<=m;i++){
//		cout<<"add"<<E[i].v<<" "<<i<<"\n";
		vec3[E[i].v].push_back(i);
		vecu[E[i].u].push_back(i);
		vec[Bid[E[i].l]].push_back(i);
		vec[Bid[E[i].r]].push_back(i);
	}
	for(int i=1;i<=q;i++){
		int t,p;
		cin>>t>>p;
		p++;t++;
		vec2[Bid[t]].push_back({i,t,p});
	}
	/*
	n/B()
	nBlogn+n^2/B
	B^2=n/logn 
	
	*/
	//1~S S+1 2*S
	for(int i=1;i<=Bid[tim];i++){
		sort(vec2[i].begin(),vec2[i].end(),[](Quest x,Quest y){return x.p<y.p;});
		int Bl=(i-1)*B+1,Br=min(tim,B*i);
		for(int i=1;i<=n;i++)ff[i]=fa[i]=i,sz[i]=1;
		int pos=0;
		cnt=0;
		for(int j=1;j<=n;j++){
			cnt++;
			for(int k=0;k<vec3[j].size();k++){
				Edge e=E[vec3[j][k]];
				if(e.l<Bl&&Br<e.r){
				int u=find2(e.u),v=find2(e.v);
				if(u==v)continue;
				cnt--;
				if(sz[u]>sz[v])swap(u,v);
				fa[u]=v;sz[v]+=sz[u];
				}
				
			}
			while(pos<vec2[i].size()&&vec2[i][pos].p<=j){
				Quest Qu=vec2[i][pos];
//				cout<<"solve "<<Qu.p<<" "<<Qu.ti<<"\n";cout<<cnt<<'\n';
				cnt2=0;
				for(int k=0;k<vec[i].size();k++){
					Edge e=E[vec[i][k]];
					if(e.l<=Qu.ti&&Qu.ti<=e.r){
						if(e.v>Qu.p)continue;
						add(e.u,e.v);
					}
				}
//				cout<<cnt-cnt2<<"\n";
				ans[Qu.id]+=cnt-cnt2;
				for(int k=0;k<vec[i].size();k++){
					Edge e=E[vec[i][k]];
					if(e.l<=Qu.ti&&Qu.ti<=e.r){
						if(e.v>Qu.p)continue;
						del(e.u,e.v);
					}
				}
				pos++;
			}
		}		
		
		for(int i=1;i<=n;i++)ff[i]=fa[i]=i,sz[i]=1;
		pos=vec2[i].size()-1;cnt=-1;
		for(int j=n+1;j>=1;j--){
			cnt++;
			for(int k=0;k<vecu[j].size();k++){
				Edge e=E[vecu[j][k]];
				if(e.l<Bl&&Br<e.r){
					int u=find2(e.u),v=find2(e.v);
					if(u==v)continue;
					cnt--;
					if(sz[u]>sz[v])swap(u,v);
					fa[u]=v;sz[v]+=sz[u];
				}
				
			}

			while(pos>=0&&vec2[i][pos].p==j-1){
				
				Quest Qu=vec2[i][pos];
//				cout<<"solve "<<Qu.p<<" "<<Qu.ti<<"\n";cout<<cnt<<'\n';
				cnt2=0;
				for(int k=0;k<vec[i].size();k++){
					
					Edge e=E[vec[i][k]];
					if(e.l<=Qu.ti&&Qu.ti<=e.r){
						if(e.u<=Qu.p)continue;
						add(e.u,e.v);
					}
				}
				ans[Qu.id]+=cnt-cnt2;
				for(int k=0;k<vec[i].size();k++){
					Edge e=E[vec[i][k]];
					if(e.l<=Qu.ti&&Qu.ti<=e.r){
						if(e.u<=Qu.p)continue;
						del(e.u,e.v);
					}
				}
				pos--;
			}
		}
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
	return 0;
}

```

:::

---

## 作者：masterhuang (赞：0)

> $n$ 个点的图（初始一条边都没有），$q$ 次操作：
>
> - 加边 $(x,y)$​，保证当前不在图中。
> - 删边 $(x,y)$，保证当前在图中。
> - 询问 $x$，问删除一端在 $[1,x]$，一端在 $[x+1,n]$ 中的所有边后，图中的连通块数目。
>
> $2\le n\le 10^5,q\le 2\times 10^5$，**前两种操作总数**和**询问操作**各不超过 $10^5$ 次。

显然 $[1,x]$ 和 $[x+1,n]$ 是对称的，接下来只考虑 $[1,x]$​ 的答案。

下面不妨 $n,q$ 同阶，$\alpha(n)\sim O(1)$。

### 做法 1

单根号做法。

- 操作分块（根号重构）的一些特征：一般是**单点操作**而非区间操作。单挂 $O(\sqrt n)$ 个操作在询问上的问题是好做的。

这题比较符合，考虑操作分块。

先考虑怎么搞掉删边操作，经典套路是变成加边和撤销。

每次根号重构的时候，把接下来要删的 $O(\sqrt n)$​ 条边，直接在加边的时候**不加它们**。

并且按 $x$ 排序扫描线并查集（这东西用桶排就没 $\log$ 了），维护 $[1,x]$ 的答案。

然后转化为：不包含删这条边的询问集合要加这条边。

此时由于每个询问 $O(\sqrt n)$ 次加边，但是要支持**可撤销并查集**，于是复杂度 $O(n\sqrt n\log n)$。

---

但是你发现：重构的时候只需**普通并查集**。你每次重构完，**可撤销并查集部分**也只用到 $O(\sqrt n)$ 个点。你发现**抱抱我真唐！**

我们每次重构完，对于每个询问拎出来所有可能要加边的 $O(\sqrt n)$​ 端点，把这些端点单独拿出来做并查集。

这样总共只需要拎 $O(n\sqrt n)$ 次，但是并查集变成普通并查集。

于是总复杂度 $O(n\sqrt n)$​。

### 做法 2

考虑定义 $u, v$ 之间的边权为 $\max(u, v)$，根据 **Kruskal** 过程，问题转化为求一个当前时间下的 **MST** 中边权 $\le x$ 的有几条边。

由于既有插入也有删除操作，使用线段树分治将操作变为插入和撤销。

接下来考虑怎么维护前缀 $[1,l-1]$ 的 **MST** 信息。

参考 [P3206 [HNOI2010] 城市建设](https://www.luogu.com.cn/problem/P3206) 的做法，每次使用 **Kruskal** 优化边数：

若把当前区间的边的边权都设为 $\infty$，跑完 **Kruskal** 后没有连接的、边权不为 $\infty$ 的边，在区间中任意一个分治叶子处也都不会出现，我们就**不考虑这条边**。

同理，若把当前区间的边的边权都设为 $-\infty$，跑完 **Kruskal** 后连接的、边权不为 $-\infty$ 的边最后一定会连接，也就是说我们**一定保留这条边**。

容易证明，操作后仍然不确定是否连接的边只有 $O(\text{len})$ 条，其中 $\text{len}$ 为当前分治区间的长度。

所以使用可撤销并查集同时维护一个树状数组记录边权 $\le x$ 的个数即可，时间复杂度 $O(n \log^2 n)$。

---

## 作者：gdf_yhm (赞：0)

[P9598](https://www.luogu.com.cn/problem/P9598)

[my blog](https://yhddd123.github.io/post/p9598-ti-jie/)

比较蠢的做法，原因是分块的对象错完了。

### 思路

加边删边可以线段树分治。只考虑 $[1,p]$ 部分。可以在 $[1,p-1]$ 的图的基础上加入右端点为 $p$ 的边，然后线段树分治回答所有在 $p$ 隔开的询问。同理，如果在 $[1,pl]$ 的图上线段树分治，到一个时间枚举在这个时间且 $p\in [pl,pr]$ 的询问，直接加入小于当前时间且右端点属于 $[pl+1,p]$ 的边，询问，再删除这些边。

所以分块，复杂度取决于右端点属于 $[pl+1,pr]$ 的边的数量和 $[pl,pr]$ 块数。设阈值 $B$，按右端点排序大概 $B$ 条边分成一块。对于当前左端点 $pl$，找到最小 $pr$ 满足右端点属于 $[pl,pr]$ 的边数 $>B$。但如果右端点等于 $pr$ 的边数 $>B$，就分 $[pl,pr)$ 和 $[pr,pr]$。这样可以保证右端点属于 $[pl+1,pr]$ 的边数 $<2\times B$， $[pl,pr]$ 块数 $<2\times \frac{n}{B}$。

对于每一块，都要对之前的边重新线段树分治一遍；对于每个询问，都要遍历块内之前的边。所有的加边删边操作都要可撤销并查集。复杂度 $O(\frac{n}{B}n\log^2 n+mB\log n)$。取 $B=1000$ 跑的飞快。

### code

```cp
int n,m,q,B=1000;
pii upd[maxn],que[maxn];
int ans[maxn];
vector<pii> edge[maxn],qq[maxn],ask[maxn];
int num[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<pii> tree[maxn<<2];
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxn],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u,siz[u]+=siz[v],st[++tp]=v;
}
void del(){
	int v=st[tp],u=f[v];
	f[v]=v,siz[u]-=siz[v];
	tp--;
}
void build(int nd,int l,int r){
	tree[nd].clear();
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
bool vis[maxn<<2];
void modif(int nd,int l,int r,int p){
	vis[nd]=1;
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
}
int lst[maxn];
vector<int> pos;
void dfs(int nd,int l,int r){
	if(!vis[nd])return ;vis[nd]=0;
	int tmp=tp;
	for(auto[u,v]:tree[nd])merge(u,v);
	if(l==r){
		for(auto[p,id]:ask[l]){
			int nw=tp;
			for(int i:pos){
				if(i>p)break;
				for(auto[u,t]:edge[i]){
					if(t>l)break;
					lst[u]^=1;
				}
				for(auto[u,t]:edge[i]){
					if(t>l)break;
					if(lst[u])merge(u,i),lst[u]=0;
				}
			}
			ans[id]+=p-tp;
			while(tp>nw)del();
		}
		ask[l].clear();
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(tp>tmp)del();
}
void sovle(){
	for(int i=1;i<=n;i++)edge[i].clear();
	for(int i=1;i<=m;i++){
		auto[u,v]=upd[i];
		if(u>v)swap(u,v);
		edge[v].pb({u,i});
	}
	for(int i=1;i<=n;i++)num[i]=num[i-1]+edge[i].size();
	for(int i=1;i<=n;i++)qq[i].clear();
	for(int i=1;i<=q;i++){
		auto[t,p]=que[i];
		qq[p].pb({t,i});
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	build(1,1,m);
	for(int l=1,r=1;l<=n;l=r+1,r=l){
		while(r<n&&num[r]-num[l-1]<B)r++;
		if(edge[r].size()>B&&l<r)r--;
		for(auto[u,t]:edge[l]){
			if(lst[u])updata(1,1,m,lst[u],t-1,{u,l}),lst[u]=0;
			else lst[u]=t;
		}
		for(auto[u,t]:edge[l])if(lst[u])updata(1,1,m,lst[u],m,{u,l}),lst[u]=0;
		for(int i=l;i<=r;i++){
			for(auto[t,id]:qq[i])ask[t].pb({i,id}),modif(1,1,m,t);
		}
		pos.clear();for(int i=l+1;i<=r;i++)if(edge[i].size())pos.pb(i);
		dfs(1,1,m);
		for(int i=l+1;i<=r;i++){
			for(auto[u,t]:edge[i]){
				if(lst[u])updata(1,1,m,lst[u],t-1,{u,i}),lst[u]=0;
				else lst[u]=t;
			}
			for(auto[u,t]:edge[i])if(lst[u])updata(1,1,m,lst[u],m,{u,i}),lst[u]=0;
		}
	}
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int op=read(),u=read()+1,v=read()+1;
		upd[i]={u,v};
	}
	for(int i=1;i<=q;i++){
		int t=read()+1,p=read()+1;
		que[i]={t,p};
	}
	sovle();
	for(int i=1;i<=m;i++){
		auto[u,v]=upd[i];
		upd[i]={n-u+1,n-v+1};
	}
	for(int i=1;i<=q;i++){
		auto[t,p]=que[i];
		que[i]={t,n-p};
	}
	sovle();
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
```

---

## 作者：takanashi_mifuru (赞：0)

想了两个小时怎么用分块实现线段树分治，结果是操作分块……

---

容易发现每次山体滑坡都把这条边左部和右部拆成了完全独立的部分，所以我们分开来做。

一个很容易想到的思路是按照山体滑坡的点来排序，然后把“可能可用的边”按照时间区间打到一个数据结构上面去，最后实现时间上的单点查询。

这个是做不了的，因为标记没办法合并。

考虑操作分块，块内节点按照山体滑坡的点排序，然后枚举山体滑坡的点，找出新的合法边，如果这个边在大块中并且仍未删除就加入，否则就不管。

啊然后出现了第一托狗屎，考虑散块的删除操作非常的唐氏，所以如果一条边可能被散块删除，那就把他记录下来，然后后面处理询问的时候再来考虑他有没有被删除，把没删除的丢进去就好了。

呃呃这样的话你往这个大并查集里面拉的石肯定是不能影响下一次询问的，所以你要写个可撤销并查集把你拉的石清理掉，这就带 $\log$ 了，非常的垃圾。

所以考虑我们只有块长条边会影响到的点也只有这么多，对于其中每个点，我根本不需要实时求解他们的联通状态，我可以用他们在大图上的并查集代表点建立新的并查集，然后再做，然后就一个根号了。

---

## 作者：Genius_Star (赞：0)

### 思路：

省选模拟赛题，场切了，来写个题解。

我们发现，如果图形态固定，考虑从 $[1, p]$ 算 $[1, p + 1]$ 的答案，显然只需要计算出 $p + 1$ 连接了 $[1, p]$ 的导出子图中多少个联通块即可；直接并查集维护。

考虑如何做动态加边，删边；容易发现我们做加边似乎是容易的，故考虑回滚莫队的思想。

按照时间轴分块，先将 $[1, id - 1]$ 块内的操作和询问做完，然后再做 $id$ 块的询问；考虑按照 $p$ 作扫描线，设 $L_{id}$ 为这个块的左端点，然后对于询问 $(w, p)$ 暴力将 $[L_{id}, w]$ 的操作加入进来，算合并的联通块个数，然后再撤回。

看起来很对，但是在 $[L_{id}, w]$ 的操作时可能会删除 $[1, id - 1]$ 块内的边，于是考虑先对于 $[L_{id}, R_{id}]$ 会造成影响的边，在扫描 $p$ 的时候，先不加入进来，每次将 $[L_{id}, w]$ 内的边的状态取反，然后再插入 $[L_{id}, R_{id}]$ 内的边，这样就是对的。

时间复杂度为 $O((N + Q) \sqrt{N})$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define hash(x, y) 1ll * x * (n - 1) + y
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, q, x, y, cnt, t, k, s, _s;
int a[N], b[N], g[N], id[N], ans[N];
ll h[N];
bool f[N], _f[N];
vector<int> E[N];
vector<pair<int, int>> Q[N];
vector<pair<pair<int, int>, int>> V[N];
inline void add(int u, int v){
	E[u].push_back(v);
}
namespace DSU{
	int fa[N], _fa[N];
	inline void init(){
		s = _s = 0;
		for(int i = 1; i <= n; ++i)
		  fa[i] = _fa[i] = i;
	}
	inline int Find(int x){
		if(x != fa[x])
		  return fa[x] = Find(fa[x]);
		return fa[x];
	}
	inline int _Find(int x){
		if(x != _fa[x])
		  return _fa[x] = _Find(_fa[x]);
		return _fa[x];
	}
	inline void merge(int x, int y){
		x = Find(x), y = Find(y);
		if(x == y)
		  return ;
		fa[x] = y;
		++s;
	}
	inline void _merge(int x, int y){
		x = Find(x), y = Find(y);
		if(x == y)
		  return ;
		x = _Find(x), y = _Find(y);
		if(x == y)
		  return ;
		_fa[x] = y;
		++_s;
	}
	inline void tidy(int x){
		x = Find(x);
		_fa[x] = x;
	}
};
inline void sol(int now, bool F){
	int l = (now - 1) * t + 1, r = min(now * t, m);
	DSU::init();
	for(int i = 1; i <= n; ++i)
	  E[i].clear(), Q[i].clear();
	for(auto t : V[now]){
		if(F)
		  Q[t.fi.se + 1].push_back({t.fi.fi, t.se});
		else
		  Q[t.fi.se].push_back({t.fi.fi, t.se});
	}
	for(int i = 1; i < l; ++i)
	  if(f[g[i]] && !_f[g[i]])
	    F ? add(a[i], b[i]) : add(b[i], a[i]);
	for(int u = (F ? n : 1); (F ? u >= 1 : u <= n); (F ? (--u) : (++u))){
		for(auto v : E[u])
		  DSU::merge(u, v);
		for(auto t : Q[u]){
			_s = 0;
			for(int i = l; i <= t.fi; ++i)
			  f[g[i]] ^= 1;
//			cerr << l << ' ' << r << ' ' << s << '\n';
			for(int i = l; i <= r; ++i)
			  if(f[g[i]] && (F ? a[i] >= u : b[i] <= u))
			    DSU::_merge(a[i], b[i]);
			ans[t.se] += s + _s;
			for(int i = l; i <= r; ++i)
			  if(f[g[i]] && (F ? a[i] >= u : b[i] <= u))
			    DSU::tidy(a[i]), DSU::tidy(b[i]);
			for(int i = l; i <= t.fi; ++i)
			  f[g[i]] ^= 1;
		}
	}
}
bool End;
int main(){
//	open("cruising.in", "cruising.out");
	n = read(), m = read(), q = read();
	for(int i = 1; i <= m; ++i){
		read(), a[i] = read() + 1, b[i] = read() + 1;
		if(a[i] > b[i])
		  swap(a[i], b[i]);
		h[++cnt] = hash(a[i], b[i]);
	}
	sort(h + 1, h + cnt + 1);
	cnt = unique(h + 1, h + cnt + 1) - (h + 1);
	for(int i = 1; i <= m; ++i)
	  g[i] = lower_bound(h + 1, h + cnt + 1, hash(a[i], b[i])) - h;
	t = 705;
	for(int i = 1; i <= m; ++i)
	  id[i] = (i - 1) / t + 1;
	for(int i = 1; i <= q; ++i){
		x = read() + 1, y = read() + 1;
		V[id[x]].push_back({{x, y}, i});
	}
	for(int now = 1; now <= (m + t - 1) / t; ++now){
		int l = (now - 1) * t + 1, r = min(now * t, m);
		for(int i = l; i <= r; ++i)
		  _f[g[i]] = 1;
		sol(now, 0);
		sol(now, 1);
		for(int i = l; i <= r; ++i){
			_f[g[i]] = 0;
			f[g[i]] ^= 1;
		}
	}
	for(int i = 1; i <= q; ++i){
		write(n - ans[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
``

---

