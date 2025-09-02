# Prince's Problem

## 题目描述

Let the main characters of this problem be personages from some recent movie. New Avengers seem to make a lot of buzz. I didn't watch any part of the franchise and don't know its heroes well, but it won't stop me from using them in this problem statement. So, Thanos and Dr. Strange are doing their superhero and supervillain stuff, but then suddenly they stumble across a regular competitive programming problem.

You are given a tree with $ n $ vertices.

In each vertex $ v $ there is positive integer $ a_{v} $ .

You have to answer $ q $ queries.

Each query has a from $ u $ $ v $ $ x $ .

You have to calculate $ \prod_{w \in P} gcd(x, a_{w}) \mod (10^{9} + 7) $ , where $ P $ is a set of vertices on path from $ u $ to $ v $ . In other words, you are to calculate the product of $ gcd(x, a_{w}) $ for all vertices $ w $ on the path from $ u $ to $ v $ . As it might be large, compute it modulo $ 10^9+7 $ . Here $ gcd(s, t) $ denotes the greatest common divisor of $ s $ and $ t $ .

Note that the numbers in vertices do not change after queries.

I suppose that you are more interested in superhero business of Thanos and Dr. Strange than in them solving the problem. So you are invited to solve this problem instead of them.

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
6 4 9 5
3
2 3 6
2 3 2
3 4 7
```

### 输出

```
36
4
1
```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
1 5
5 6
100000 200000 500000 40000 800000 250000
3
3 5 10000000
6 2 3500000
4 1 64000
```

### 输出

```
196000
12250
999998215
```

# 题解

## 作者：谁是鸽王 (赞：5)

## 【题解】CF986E Prince's Problem(树上差分+数论性质)

题目大意：

> 给定你一棵树，有点权$val_i\le 10^7$。现在有$m$组询问给定参数$x,y,w$问你对于$(x->y)$的路径经过的点集$P$，问你这个东西：
> $$
> \prod_{u \in P} {\mathrm{gcd}(w,val_u)} \mod 1000000007
> $$

考虑这样一种做法：

- 把询问差分成
$$
	ans(1,x) \times ans(1,y) \times \mathrm{gcd}(w,val_{lca(x,y)})\over ans(w,lca_{x,y})^2
$$
	现在就把问题转换为了从根到节点的询问。考虑这样然后怎么做。

- 考虑这类从根出发如何解决，直接遍历整棵树，对于每个节点先将自己的贡献加入某种数据结构，再递归子树，最后回溯时撤回贡献。问题就变为如何快速求$\prod \mathrm{gcd}$

- 考虑$gcd$的本质就是对于质因子取$min$且求和，而且我们知道$1e7$以内的质数是不多的($5e6$左右)，所以直接对于每个质数开一个$vector$。$vector_i$中的下标$j$表示唯一分解后$\alpha(prime[i])=j$的树上节点有多少个。($\alpha$是唯一分解后的指数)。考虑到$\sum \alpha$很小是$\log$级别，这样复杂度就是$O(1e7+(n+m)\log 1e7)$空间复杂度$O((n +q)\log 1e7)$

主要就是树上差分，还有处理$\sum \min\{...\}$的方法。

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#define inv(x) (ksm((x)%mod,mod-2))

using namespace std;  typedef long long ll;   
inline int qr(){
      register int ret=0,f=0;
      register char c=getchar();
      while(c<48||c>57)f|=c==45,c=getchar();
      while(c>=48&&c<=57) ret=ret*10+c-48,c=getchar();
      return f?-ret:ret;
}

const int mod=1e9+7;
int n,m;
inline int ksm(const int&ba,const int&p){
      int ret=1;
      for(int t=p,b=ba%mod;t;t>>=1,b=1ll*b*b%mod)
	    if(t&1) ret=1ll*ret*b%mod;
      return ret;
}

vector< vector<int> > s;
namespace PRE{
      const int maxn=1e7+5;
      int rank[maxn],usd[maxn],arc[maxn],Min[maxn];
      vector<int> pr;
      inline void pre(const int&n){
	    usd[1]=1; Min[1]=10;
	    for(int t=2;t<=n;++t){
		  if(!usd[t]) Min[t]=t,pr.push_back(t),rank[t]=pr.size(),arc[rank[t]]=t;
		  for(auto f:pr){
			if(1ll*f*t>n)break;
			usd[f*t]=1;
			Min[f*t]=f;
			if(t%f==0)break;
		  }
	    }
	    s.resize(pr.size()+1);
      }
}

namespace TREE{
      const int maxn=1e5+5;
      int d[maxn];
      vector<int> e[maxn];
      vector<int> q[maxn];
      int W[maxn],ans[maxn],w[maxn];
      inline void add(const int&fr,const int&to){
	    e[fr].push_back(to);
	    e[to].push_back(fr);
      }
      int son[maxn],top[maxn],r[maxn],siz[maxn];
      void pre(const int&now,const int&last){
	    siz[now]=1;
	    r[now]=last;
	    d[now]=d[last]+1;
	    for(auto t:e[now])
		  if(t^last) {
			pre(t,now); siz[now]+=siz[t];
			if(siz[now]>siz[son[now]]) son[now]=t;
		  }
      }
      void qaq(const int&now,const int&last){
	    top[now]=last;
	    if(son[now]) qaq(son[now],last);
	    for(auto t:e[now])
		  if((t^r[now])&&(t^son[now]))
			qaq(t,t);
      }
      inline void init(const int&n){pre(1,0);qaq(1,0);}
      inline int lca(int u,int v){
	    if(d[u]<d[v])swap(u,v);
	    while(top[u]^top[v]){
		  if(d[top[u]]<d[top[v]]) swap(u,v);
		  u=r[top[u]];
	    }
	    return d[u]<d[v]?u:v;
      }
      inline void addq(const int&x,const int&y,const int&id,const int&w){
	    ans[id]=1;
	    q[x].push_back(id);
	    q[y].push_back(id);
	    q[lca(x,y)].push_back(-id);
	    W[id]=w;
      }
}

namespace sol{
      const int maxn=1e5+5;
      using namespace TREE;
      using PRE::rank;
      using PRE::Min;
      inline void add(const int&now,const int&tag){
	    //now 是节点编号 tag 是操作类型
	    int k=w[now],cnt=0;
	    static int a[23],p[23];
	    while(k>1){
		  int f=Min[k];
		  a[++cnt]=0;
		  p[cnt]=f;
		  while(k%f==0) k/=f,++a[cnt];
	    }
	    for(int t=1;t<=cnt;++t){
		  if(((int)s[rank[p[t]]].size())<=1+a[t])
			s[rank[p[t]]].resize(a[t]+2);
		  s[rank[p[t]]][a[t]]+=tag;
	    }
      }
      inline void que(const int&now,const int&id){
	    //now 是询问编号
	    int k=W[now>0?now:-now],cnt=0,ret=1;
	    static int a[23],p[23];
	    while(k>1){
		  int f=Min[k];
		  a[++cnt]=0;
		  p[cnt]=f;
		  while(k%f==0) k/=f,++a[cnt];
	    }
	    for(int t=1;t<=cnt;++t)
		  for(int i=1,ed=s[rank[p[t]]].size();i<ed;++i)
			ret=1ll*ret*ksm(p[t],1ll*s[rank[p[t]]][i]*min(a[t],i)%(mod-1))%mod;
	    if(now<0)  ans[-now]=1ll*ans[-now]*inv(ret)%mod*inv(ret)%mod*__gcd(W[-now],w[id])%mod;
	    else  ans[now]=1ll*ans[now]*ret%mod;
	    
      }
      void dfs(const int&now,const int&last){
	    add(now,1);
	    for(auto t:q[now]) que(t,now);
	    for(auto t:e[now])
		  if(t^last) dfs(t,now);
	    add(now,-1);
      }
}

int main(){
      PRE::pre(1e7);
      n=qr();
      for(int t=2;t<=n;++t) TREE::add(qr(),qr());
      for(int t=1;t<=n;++t) TREE::w[t]=qr();
      TREE::init(n);
      m=qr();
      for(int t=1,t1,t2,t3;t<=m;++t) {
	    t1=qr(); t2=qr(); t3=qr();
	    TREE::addq(t1,t2,t,t3);
      }
      sol::dfs(1,0);
      for(int t=1;t<=m;++t) printf("%d\n",TREE::ans[t]);
      return 0;
}


```

---

## 作者：chenxia25 (赞：4)

怎么评价这个题呢……是自己做出来了，但做完之后感觉无法理解自己的做法，因为我是 DS 菜鸡嘛……想了一会儿之后，来写了这个题解。

---

**[Portal]( https://www.luogu.com.cn/problem/CF986E )**

要处理 $\gcd$，考虑分解质因数。然后链上每个数对答案的贡献就是它每个质因子的次数与 $w$ 的该质因子的次数取个 $\min$。

我们考虑树剖。于是问题转化到区间上。注意到任意一个数的质因子个数是 $\mathrm O(\log v)$ 级别的，那么直接枚举 $w$ 的每个质因子。于是问题转化为如何计算一个区间上某个质因子的次数们与给定数的 $\min$ 的和。直接 DS 维护貌似不太可做，但注意到次数也是 $\mathrm O(\log v)$ 级别的，于是我们枚举次数。于是问题转化为如何计算一个区间上某个质因子次数为给定数的个数。这个就比较好办了，在预处理分解质因数的时候，把这些质因子的次数压入质因子所对应的 `vector`，每个 `vector` 记录前缀和，然后在里面二分。然后这个二分操作是和枚举次数平行的，数一下发现是 3log。

注意到这是个静态问题，于是想到树上前缀和 instead of 树剖。依然枚举 $w$ 的质因子，对于每个质因子依然枚举次数（这样 $\sum\alpha$ 依然是 1log 级别的，前面虽然也涉及到这个 $\sum\alpha$，但还有一个二分强制增加了一个 log）。于是我们现在想知道的是一条链上某个质因子次数为给定数的个数。考虑对这个进行前缀和。但是要是在树的某处都放一个前缀和的数组的话，那时空都会炸，但是注意到这是有可优化性的，因为总共更新前缀和的次数是不会炸的，炸的是复制粘贴数组的代价。于是我们考虑惯用套路：在 DFS 的过程中实时维护前缀和数组，该回溯回溯，这个类似于扫描线的思想。然后将需要查询前缀和的地方给标记到对应节点上，到时贡献给相应询问。这样子是 1log 的。

除此之外还有一些小细节。分解质因数的根号复杂度要算上。前缀和算 lca 需要树上倍增。还要把质数筛一下来缩小值域，不然数组开不下。总的来说挺难写的。

**_[code]( https://www.luogu.com.cn/paste/zzjv2jrs )_**

---

## 作者：tzc_wk (赞：2)

[题面传送门](https://codeforces.ml/contest/986/problem/E)

题意：

有一棵 $n$ 个节点的树，点上有点权 $a_i$，$q$ 组询问，每次询问给出 $u,v,w$，要求：

- $\prod\limits_{x\in P(u,v)}\operatorname{gcd}(a_x,w)$

其中 $P(u,v)$ 为 $u$ 到 $v$ 的简单路径上经过的点的集合。

$n,q \leq 10^5,a_i \leq 10^7$

显然本题需要分解质因数，不妨设 $w$ 分解质因数得到 $p_1^{f_1}\times p_2^{f_2}\times\dots\times p_k^{f_k}$。

我们对 $w$ 的每个质因子 $p_i$ 计算对应的贡献，对于链上的每个数 $a_x$，假设它质因数 $p_i$ 的次数为 $g_i$，那么它的贡献就是 $p_i^{\min(f_i,g_i)}$。

于是我们可以暴力枚举 $p_i$ 的次数 $g_i$，假设 $u\to v$ 的路径上有 $cnt$ 个 $a_x$ 中 $p_i$ 的次数恰好为 $g_i$，这部分的答案应为 $(p_i^{\min(f_i,g_i)})^{cnt}$。

接下来就是怎样求这个 $cnt$，对 $a_i$ 分解质因数得到 $a_i=q_1^{h_1}\times q_2^{h_2}\times\dots\times q_l^{h_l}$，将每个 $(q_i,h_i)$ 看作一种“颜色”，每个点上最多有 $7$ 种颜色。那么题目就转化为求 $u$ 到 $v$ 路径上有某种“颜色”的点的个数。

考虑用树剖把原区间拆成 $\log n$ 个小区间，然后用主席树维护区间内值为 $x$ 的数的个数就可以求出 $cnt$ 的值。

算算复杂度，暴力枚举 $g_i$  的常数最大可以达到为 $\log_2(10^7)+\log_3(10^7)+\log_5(10^7)+\log_7(10^7)+\log_{11}(10^7)+\log_{13}(10^7)$ ，大约 $60$，树剖+主席树各有一个 $\log$，所以总复杂度是 $60q\log^2n$，太逊了。

发现本题并没有强制在线，所以可以离线地去完成路径上数颜色这一工作。这玩意儿可以利用树上差分拆为 $u,v,\operatorname{lca}(u,v),fa_{\operatorname{lca}(u,v)}$ 四个部分，最终的 $cnt=cnt_u+cnt_v-cnt_{\operatorname{lca}(u,v)}-cnt_{fa_{\operatorname{lca}(u,v)}}$。

枚举每一种颜色 $c$，然后依次处理查询颜色为 $c$ 的询问。假设某个点 $x$ 拥有颜色 $c$，那么它会对 $x$ 的子树内的询问产生 $1$ 的贡献，利用 DFS 序将子树变为 DFS 序上的一个区间，于是本题就变为区间加、单点查询的问题，一个线段树就可以搞定了。

复杂度可以少掉一个 $\log$， $60q\log n$ 大约为 $1.5\times 10^8$。

想到这里，我就没有再想下去。当我美滋滋地交上去，拥有十足的信心 A 掉这道题的时候……

TLE on test 9？

虽然理论复杂度是 ok 的，但实测常数很大。首先你要将每个找颜色的询问拆成四个询问，就已经有了 $4$ 的常数，再加上快速幂、取模的常数，将近有 $10^9$。对这种情况，哪怕再神的评测机也没法儿给你跑过啊……

顺便附上 T 掉了的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
const int MOD=1e9+7; 
const int MAXN=1e5+5;
const int MAXC=MAXN*10;
const int MAXQ=MAXN*150;
int n,q,qn,a[MAXN],tnum=0,num=0;
vector<pii> fac[MAXN];
pii key[MAXC],hs[MAXC];
map<pii,bool> vis;
int hd[MAXN],nxt[MAXN<<1],to[MAXN<<1],ec=0;
void adde(int u,int v){
	to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;
}
int fa[MAXN][22],dfn[MAXN],ed[MAXN],tim=0,dep[MAXN];
void dfs(int x,int f){
	fa[x][0]=f;dfn[x]=++tim;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dep[y]=dep[x]+1;dfs(y,x);
	} ed[x]=tim;
}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;~i;i--) if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=20;~i;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
struct Query{
	int f,id,x,v;//ans[id]*=v^{num}
	Query(){/*var nothing*/}
	Query(int _f,int _id,int _x,int _v){
		f=_f;id=_id;x=_x;v=_v;
	}
	friend bool operator <(Query lhs,Query rhs){
		return lhs.f<rhs.f;
	}
} qu[MAXQ];
vector<int> add[MAXC];
int qpow(int x,int e){
	int ret=1;
	while(e){
		if(e&1) ret=1ll*ret*x%MOD;
		x=1ll*x*x%MOD;e>>=1;
	} return ret;
}
int ans[MAXN];
struct node{
	int l,r,val,lz;
} s[MAXN<<2];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r) return;
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].val+=s[k].lz*(s[k<<1].r-s[k<<1].l+1);
		s[k<<1].lz+=s[k].lz;
		s[k<<1|1].val+=s[k].lz*(s[k<<1|1].r-s[k<<1|1].l+1);
		s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].val+=(s[k].r-s[k].l+1)*x;s[k].lz+=x;return;
	} pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	s[k].val=s[k<<1].val+s[k<<1|1].val;
}
int query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].val;
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);adde(u,v);adde(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int tmp=a[i];
		for(int j=2;j*j<=tmp;j++){
			if(tmp%j==0){
				int cnt=0;
				while(tmp%j==0) tmp/=j,cnt++;
				fac[i].pb(mp(j,cnt));
//				printf("{%d,%d} ",j,cnt);
				key[++tnum]=mp(j,cnt);
			}
		}
		if(tmp>1){
			fac[i].pb(mp(tmp,1));
//			printf("{%d,%d} ",tmp,1);
			key[++tnum]=mp(tmp,1);
		}
//		printf("\n");
	}
	sort(key+1,key+tnum+1);
	for(int i=1;i<=tnum;i++) if(key[i]!=key[i-1])
		hs[++num]=key[i],vis[key[i]]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<fac[i].size();j++){
			int id=lower_bound(hs+1,hs+num+1,fac[i][j])-hs;
			add[id].push_back(i);//printf("%d %d\n",id,i);
		}
	}
	dfs(1,0);
	for(int i=1;i<=20;i++) for(int j=1;j<=n;j++)
		fa[j][i]=fa[fa[j][i-1]][i-1];
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		int tmp=w;vector<pii> ff;ans[i]=1;
		for(int j=2;j*j<=tmp;j++){
			if(tmp%j==0){
				int cnt=0;
				while(tmp%j==0) tmp/=j,cnt++;
				ff.pb(mp(j,cnt));
			}
		}
		if(tmp>1) ff.pb(mp(tmp,1));
		for(int j=0;j<ff.size();j++){
			int val=1,pw=qpow(ff[j].fi,ff[j].se);
			for(int k=1;val<=1e7;k++){
				val*=ff[j].fi;
				if(!vis[mp(ff[j].fi,k)]) continue;
				int f=lower_bound(hs+1,hs+num+1,mp(ff[j].fi,k))-hs;
				qu[++qn]=Query(f,i,u,min(val,pw));
				qu[++qn]=Query(f,i,v,min(val,pw));
				int lca=getlca(u,v);
				qu[++qn]=Query(f,i,lca,qpow(min(val,pw),MOD-2));
				if(lca!=1) qu[++qn]=Query(f,i,fa[lca][0],qpow(min(val,pw),MOD-2));
			}
		}
	}
	build(1,1,n);sort(qu+1,qu+qn+1);int j=1;
	for(int i=1;i<=num;i++){
		ffe(it,add[i]) modify(1,dfn[*it],ed[*it],1);
		while(j<=qn&&qu[j].f==i){
			int cnt=query(1,dfn[qu[j].x],dfn[qu[j].x]);
//			printf("%d %d\n",j,cnt);
			ans[qu[j].id]=1ll*ans[qu[j].id]*qpow(qu[j].v,cnt)%MOD;j++;
		}
		ffe(it,add[i]) modify(1,dfn[*it],ed[*it],-1);
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

wtcl 啊，下面开始讲正解，其实稍微变通一下就行了。

正解还是基于之前那个“数颜色”的做法，不过我们想想，之前我们离线是枚举颜色，然后维护树上每个点询问的答案。如果是枚举树上的点，然后用个什么东西维护每种颜色的数量会不会好一些啊？

树上前缀和啊！

按照套路对树进行一遍 DFS，将询问标记在点上。我们维护一个 $sum_x$ 表示根节点到当前节点的路径上颜色为 $x$ 的节点的个数。在 DFS 的过程中实时维护 $sum$ 数组，回溯的时候就减掉当前节点的贡献。

前缀和可以 $\mathcal O(1)$ 的时间内维护，这样又少掉一个 $\log$，可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
const int MOD=1e9+7; 
const int MAXN=1e5+5;
const int MAXV=1e7+5;
int n,q,qn,a[MAXN];
int hd[MAXN],nxt[MAXN<<1],to[MAXN<<1],ec=0;
void adde(int u,int v){
	to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;
}
int fa[MAXN][22],dep[MAXN];
void dfs(int x,int f){
	fa[x][0]=f;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dep[y]=dep[x]+1;dfs(y,x);
	}
}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;~i;i--) if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=20;~i;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
vector<pii> fac[MAXN];
struct Query{
	int w,x,id,mul;
} qu[MAXN<<2];
int qpow(int x,int e){
	int ret=1;
	while(e){
		if(e&1) ret=1ll*ret*x%MOD;
		x=1ll*x*x%MOD;e>>=1;
	} return ret;
}
int ans[MAXN];
int sum[MAXV/5][24];
vector<int> qv[MAXN];
int pid[MAXV],pr[MAXV/5],pcnt=0;
bitset<MAXV> vis;
void prework(){
	for(int i=2;i<MAXV;i++){
		if(!vis[i]){pr[++pcnt]=i;pid[i]=pcnt;}
		for(int j=1;j<=pcnt&&pr[j]*i<MAXV;j++){
			vis[pr[j]*i]=1;if(i%pr[j]==0) break;
		}
	}
}
void calc(int x){
	ffe(it,fac[x]) sum[pid[it->fi]][it->se]++;
	ffe(it,qv[x]){
		int id=*it,tmp=qu[id].w;
		vector<pii> ff;
		for(int i=2;i*i<=tmp;i++){
			if(tmp%i==0){
				int cnt=0;
				while(tmp%i==0) tmp/=i,cnt++;
				ff.pb(mp(i,cnt));
			}
		}
		if(tmp>1) ff.pb(mp(tmp,1));
		int tot_mul=1;
		for(int i=0;i<ff.size();i++){
			int pw=1,val=ff[i].fi;
			for(int j=1;j<=ff[i].se;j++) pw*=ff[i].fi;
			for(int j=1;val<MAXV;j++,val*=ff[i].fi){
				int cnt=sum[pid[ff[i].fi]][j];
				int mul=qpow(min(val,pw),cnt);
				tot_mul=1ll*tot_mul*mul%MOD;
			}
		}
		if(qu[id].mul==1) ans[qu[id].id]=1ll*ans[qu[id].id]*tot_mul%MOD;
		else ans[qu[id].id]=1ll*ans[qu[id].id]*qpow(tot_mul,MOD-2)%MOD;
	}
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==fa[x][0]) continue;calc(y);
	}
	ffe(it,fac[x]) sum[pid[it->fi]][it->se]--;
}
int main(){
	prework();
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);adde(u,v);adde(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int tmp=a[i];
		for(int j=2;j*j<=tmp;j++){
			if(tmp%j==0){
				int cnt=0;
				while(tmp%j==0) tmp/=j,cnt++;
				fac[i].pb(mp(j,cnt));
			}
		}
		if(tmp>1) fac[i].pb(mp(tmp,1));
	}
	dfs(1,0);
	for(int i=1;i<=20;i++) for(int j=1;j<=n;j++)
		fa[j][i]=fa[fa[j][i-1]][i-1];
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);ans[i]=1;
		int lca=getlca(u,v);
		qu[++qn]={w,u,i,1};qu[++qn]={w,v,i,1};
		qu[++qn]={w,lca,i,-1};if(lca!=1) qu[++qn]={w,fa[lca][0],i,-1};
	}
	for(int i=1;i<=qn;i++) qv[qu[i].x].pb(i);calc(1);
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

最后，ycxtxdy！

---

## 作者：daniEl_lElE (赞：1)

考虑拆出每个质因子的贡献。对于 $x^y(y>1)$，我们同样给所有 $x^y$ 的倍数一个 $x$ 的贡献。对于每次查询，求出 $w$ 所可能产生的贡献（即 $w$ 的仅包含一种质数的因子），在树上使用差分维护区间的贡献即可。总复杂度 $O((n+q)\log V)$。

```cpp
#pragma GCC optimize("Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	if(b<0) b=(mod-1+b);
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
vector<int> vc[100005];
int p[10000005];
int rl[10000005],cnt;
vector<int> d[100005];
int f[100005][20],dep[100005],ans[100005],pre[10000005];
vector<pair<pair<int,int>,int>> qry[100005];
void dfs(int now,int fa){
	f[now][0]=fa,dep[now]=dep[fa]+1;
	for(int j=1;j<20;j++) f[now][j]=f[f[now][j-1]][j-1];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
	}
}
int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=19;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
	if(u==v) return u;
	for(int i=19;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
void dfs2(int now,int fa){
	for(auto v:d[now]){
		(pre[v]*=rl[v])%=mod;
	}
	for(auto v:qry[now]){
		(ans[v.second]*=qp(pre[v.first.second],v.first.first))%=mod;
	}
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs2(v,now);
	}
	for(auto v:d[now]){
		(pre[v]*=qp(rl[v],-1))%=mod;
	}
}
signed main(){
	for(int i=1;i<=10000000;i++) pre[i]=1;
	for(int i=2;i<=10000000;i++) p[i]=1;
	for(int i=2;i<=10000000;i++){
		if(p[i]){
			rl[++cnt]=i; p[i]=cnt;
			for(int j=i*i;j<=10000000;j*=i){
				rl[++cnt]=i;
			}
			for(int j=i*2;j<=10000000;j+=i){
				p[j]=0;
			}
		}
	}
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		int a; cin>>a;
		for(int j=2;j*j<=a;j++){
			if(a%j==0){
				int t=p[j];
				while(a%j==0){
					d[i].push_back(t);
					t++;
					a/=j;
				}
			}
		}
		if(a!=1){
			d[i].push_back(p[a]);
		}
	}
	dfs(1,0);
	int q; cin>>q;
	for(int i=1;i<=q;i++){
		ans[i]=1;
		int u,v,w; cin>>u>>v>>w;
		int l=lca(u,v),pr=f[l][0];
		for(int j=2;j*j<=w;j++){
			if(w%j==0){
				int t=p[j];
				while(w%j==0){
					qry[u].push_back(make_pair(make_pair(1,t),i));
					qry[v].push_back(make_pair(make_pair(1,t),i));
					qry[l].push_back(make_pair(make_pair(-1,t),i));
					qry[pr].push_back(make_pair(make_pair(-1,t),i));
					t++;
					w/=j;
				}
			}
		}
		if(w!=1){
			int t=p[w];
			qry[u].push_back(make_pair(make_pair(1,t),i));
			qry[v].push_back(make_pair(make_pair(1,t),i));
			qry[l].push_back(make_pair(make_pair(-1,t),i));
			qry[pr].push_back(make_pair(make_pair(-1,t),i));
		}
	}
	dfs2(1,0);
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<"\n";
	}
	return 0; 
}
```

---

## 作者：yeaDonaby (赞：1)

一种方法是离线差分转为根到点的贡献然后算一下，比较常见的差分方法。

但是如果你~~困了~~思维僵化了：

先观察到，所有权的质因子个数 $\le n \log$,然后一个一个质因子考虑，设当前质因子为 $p$，把包含 $p$ 这个质因子的点建虚树。对于每个包含 $p$ 这个质因子的询问，按含 $p$ 的次数排序，容易发现不同的次数 $\le \log$，就对于每个次数，限制一下虚树上的权。

然后讨论一下。设询问的两个点为 $x,y(dep_x \le dep_y)$，在虚树上第一个 $dep < dep_{x/y}$ 的点为 $X,Y$，如果两点都在原树上的 $LCA$ 之上，就跳过。否则

设虚树上 $LCA$ 为 $l2$ ,当前 $lim$ 的桶为 $finval$。

1. $x=X:finval[y]-finval[x]$。

2. $y=Y:finval[x]-finval[y]$。

else 3.$finval[x]+finval[y]-finval[l2]-finval[fa[l2]]$。

如果不考虑排序的复杂度，理论时间复杂度也是不优的，上限为 ：$n \log n \times $ 不同质因子个数。但是常数实际很小（？），可以跑进一秒。

比较好想，比较难写。

[代码太长了，被要求放了。](https://www.luogu.com.cn/paste/2hsfeodm)

太蠢了，打个公式又冗余又丑！！

---

## 作者：intel_core (赞：0)

首先先转化成 4 条到根的链的询问。

考虑将 $\gcd(w,val_u)$ 拆开，拆成 $\prod_p \prod_{p^i\mid w} p^{[p^i\mid val_u]}$，然后注意到上式中 $p^i$ 的部分最多只有 $10^7$ 个，所以我们可以开个桶记录每个 $p^i$ 的倍数有多少个。

考虑如何计算答案，在 dfs 的过程中进入到 $u$ 点，就把 $p^i\mid u$ 的所有 $p^i$ 对应的值 $+1$，在回溯的时候撤销。

算答案直接枚举所有 $p^i\mid w$ 的 $p_i$ 简单相乘即可。

复杂度 $O((n+q)\log V+n\pi(\sqrt{V}))$。

---

## 作者：CDFLS_mao_zx (赞：0)

## 题解：$CF986E$

### 废话：

万里长征第二步。

[第一步](https://www.luogu.com.cn/blog/CDFLS-stu4-60/solution-cf1140f)

### 题意：

给出一颗带点权的树，给若干询问，每条询问给一个数$w$。

求一条路径上所有点点权与 $w$ 的 $gcd$ 乘积。

$\bmod1e9+7$

### 思路:

咋一看肯定要维护不同质数，于是想到了树剖套主席树，然鹅并不好实现，于是 $yyh$ 大佬来了，留下了两个字“离线”。

恍然大悟，需要处理的质数的个数是很少的，因为每个数质因数个数的级别是 $log$ 的，完全可以每一个质数分开处理。

所以我们先搞出每个点上权值的质因数分解，对每个质数开一个 $vector$ 存一下哪些点的质因数中有它，并记录指数。再开一个 $vector$ 记录哪些询问中的 $w$ 的质因数中有它，同样记录指数，再用一个数据结构操作就可以了，发现这样的操作次数和查询次数都是 $nlogn$ 的，所以我们需要一个数据结构，支持树上路径查询每个点权值与给定数字最小值的和（就是求 $gcd $ 的过程 ）树链剖分套主席树即可。

结果似乎有$4$个 $log$，显然不太可行，我们发现质因数的指数是 $log$ 级别的，非常小，所以完全没必要主席树，只需要统计每一个值的个数就可以了，而且这个 $log$ 非常的小，可以忽略了。我们使用树状数组代替主席树，常数大大下降，理论复杂度 $O(nlog^3n)$  ，可以通过本题。

仔细一看原来不需要支持修改，对询问差分一下，还可以做到 $O(nlogn)$ ，但由于差分之后会有 $4$  个询问，实际运行并不比树链剖分快多少(楼上楼下的大佬对其有详细讲解)。

### 代码及实现细节（树链剖分）:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<stack>
#include<bitset>
#include<vector>
#define next nxt
#define itn int
#define y1 y3647
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')
	ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
int i,j,k,m,n,s,t,dfxn;
const int N=7e5+10,mod=1e9+7;//模数记得开常量，会快很多。
struct q{
	int u,v,w,rk;
};
struct q2{
	int first,second;
};
int p[10000010];
int zs[N],head[N],son[N],size[N],dfn[N],rak[N];
int fa[N],ans[N],c[N][29],dep[N],top[N];
vector <q2> vct[N];
vector <q> vctt[N];
struct fu{
	int v,next;
}a[N<<1];
void work(int aa,int bb)
{
	a[++k].next=head[aa];
	head[aa]=k;
	a[k].v=bb;
}
void init()
{
	dep[1]=1;
	for(i=2;i<=1e7;i++)
	{
		if(p[i]!=1)zs[++t]=i,p[i]=t;//记录一下这个质数是第几个，要用。
		for(j=1;j<=t&&zs[j]*i<=1e7;j++)
		{
			p[i*zs[j]]=1;
			if(i%zs[j]==0)//先break还是先赋值为1搞清楚。
			break;
		}
	}
}
void dfs(int u)
{
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].v;
		if(fa[u]==v)
		continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		dfs(v);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
		son[u]=v;
	}
	size[u]++;
}
void dfs2(int u)
{
	dfn[u]=++dfxn;
	rak[dfn[u]]=u;
	if(son[fa[u]]==u)
	top[u]=top[fa[u]];
	else
	top[u]=u;
	if(son[u])
	dfs2(son[u]);
	for(itn i=head[u];i;i=a[i].next)
	{
		int v=a[i].v;
		if(v==son[u]||v==fa[u])
		continue;
		dfs2(v);
	}
}
void fj(int x,int u)
{
	int tmp=sqrt(x+1);
	for(int i=1;zs[i]<=tmp;i++)
	{
		int cnt=0;
		while(x%zs[i]==0)
		{
			cnt++;
			x/=zs[i];
		}
		if(cnt)
		vct[i].push_back((q2){u,cnt});
	}//只需要尝试到sqrt(x)
	if(x!=1)
	vct[p[x]].push_back((q2){u,1});//如果还没分完那么就有一个大于sqrt(n)的质数，要记录。
    //所以说要记录一下每个数是第几个质数。
}
int quick(int aa,int ss)
{
	int ret=1;
	while(ss)
	{
		if(ss&1)
		ret=(LL)ret*aa%mod;
		aa=(LL)aa*aa%mod;
		ss>>=1;
	}
	return ret;
}
void fj2(int x,int u,int v,int rk)
{
	int tmp=sqrt(x+1);
	for(int i=1;zs[i]<=tmp;i++)
	{
		int cnt=0;
		while(x%zs[i]==0)
		{
			cnt++;
			x/=zs[i];
		}
		if(cnt)
		vctt[i].push_back((q){u,v,cnt,rk});
	}
	if(x!=1)
	vctt[p[x]].push_back((q){u,v,1,rk});
}
void updata(int x,int pp,int cc)
{
	for(int i=x;i<=n;i+=i&(-i))
	c[i][pp]+=cc;
}
int quert(int x,int tc)
{
	int ss=0;
	for(int i=x;i>=1;i-=i&(-i))
	ss+=c[i][tc]；
	return ss;
}
int query(int u,int v,int tc)
{
	if(dep[u]<dep[v])
	swap(u,v);
	if(top[u]==top[v])
	return quert(dfn[u],tc)-quert(dfn[v]-1,tc);//注意树剖的细节。
	if(dep[top[u]]<dep[top[v]])
	swap(u,v);
	return quert(dfn[u],tc)-quert(dfn[top[u]]-1,tc)+query(fa[top[u]],v,tc);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	init();
	read(n);
	for(i=1;i<n;i++)
	{
		int x,y;
		read(x),read(y);
		work(x,y);
		work(y,x);
	}
	dfs(1);
	dfs2(1);
	for(i=1;i<=n;i++)
	{
		int x;
		read(x);
		fj(x,i);
	}
	read(m);
	for(i=1;i<=m;i++)
	{
		int x,y,w;
		read(x),read(y),read(w);
		ans[i]=1;
		fj2(w,x,y,i);
	}
	for(i=1;i<=t;i++)
	{	//注意枚举的是质数。
		for(j=0;j<vct[i].size();j++)
		updata(dfn[vct[i][j].first],vct[i][j].second,1);
		for(j=0;j<vctt[i].size();j++)
		{
			int tmp=0;
			int rc=log2(1e7)/log2(zs[i])+1;//计算上界。
			for(int k=1;k<=rc;k++)
			tmp+=(long long)query(vctt[i][j].u,vctt[i][j].v,k)*min(k,vctt[i][j].w);
			ans[vctt[i][j].rk]=(long long)ans[vctt[i][j].rk]*quick(zs[i],tmp)%mod;
		}
		for(j=0;j<vct[i].size();j++)	
		updata(dfn[vct[i][j].first],vct[i][j].second,-1);//记得把当前的修改该回去，处理下一个质数。
	}
	for(i=1;i<=m;i++)
	printf("%d ",ans[i]);
	return 0;
}

```

### 自我反思：

看到有关质因数的处理就应该想到对于每个质数分别处理。

选择数据结构时观察好值域。







---

