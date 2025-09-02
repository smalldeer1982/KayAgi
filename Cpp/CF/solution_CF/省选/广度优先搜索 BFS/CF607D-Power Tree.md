# Power Tree

## 题目描述

Genos and Saitama went shopping for Christmas trees. However, a different type of tree caught their attention, the exalted Power Tree.

A Power Tree starts out as a single root vertex indexed $ 1 $ . A Power Tree grows through a magical phenomenon known as an update. In an update, a single vertex is added to the tree as a child of some other vertex.

Every vertex in the tree (the root and all the added vertices) has some value $ v_{i} $ associated with it. The power of a vertex is defined as the strength of the multiset composed of the value associated with this vertex ( $ v_{i} $ ) and the powers of its direct children. The strength of a multiset is defined as the sum of all elements in the multiset multiplied by the number of elements in it. Or in other words for some multiset $ S $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF607D/e4544f58f9cc15f32e75061d79960f17ec2c1efb.png)Saitama knows the updates that will be performed on the tree, so he decided to test Genos by asking him queries about the tree during its growth cycle.

An update is of the form $ 1 p v $ , and adds a new vertex with value $ v $ as a child of vertex $ p $ .

A query is of the form $ 2 u $ , and asks for the power of vertex $ u $ .

Please help Genos respond to these queries modulo $ 10^{9}+7 $ .

## 说明/提示

For the first sample case, after all the updates the graph will have vertices labelled in the following manner: 1 — 2 — 3 — 4 — 5

These vertices will have corresponding values: 2 — 3 — 5 — 7 — 11

And corresponding powers: 344 — 170 — 82 — 36 — 11

## 样例 #1

### 输入

```
2 5
1 1 3
1 2 5
1 3 7
1 4 11
2 1
```

### 输出

```
344
```

## 样例 #2

### 输入

```
5 5
1 1 4
1 2 3
2 2
1 2 7
2 1
```

### 输出

```
14
94
```

# 题解

## 作者：daniEl_lElE (赞：1)

考虑节点 $u$ 的权值 $w_u$ 给 $f(v)$ 的贡献。

通过归纳可以发现，$w_u$ 给 $f(v)$ 贡献当且仅当 $u$ 在 $v$ 子树内。

考虑贡献的系数，$w_u$ 给 $f(u)$ 的贡献系数是 $son_u+1$，其中 $son_i$ 表示 $i$ 的儿子个数。$f(u)$ 给 $f(fa_u)$ 的贡献系数是 $son_{fa_u}+1$，其中 $fa_i$ 表示 $i$ 节点的父亲节点编号。通过归纳可以发现 $w_u$ 给 $f(v)$ 的贡献的系数实际上就是 $u\to v$ 路径上 $son_i$ 的乘积。

考虑如何维护。记 $prod_x$ 表示 $x$ 到根节点的路径上 $son_i$ 的乘积。$w_u$ 给 $f(v)$ 的贡献是 $\frac{prod_{u}}{prod_{fa_v}}\times w_u$。考虑对于每个点维护 $prod_u\times w_u$，最后求 $f(v)$ 时再除以 $prod_{fa_v}$ 即可。由于添加节点会导致某个点 $son_x$ 变化，这会导致其子树内所有点的 $prod_i$ 变化，于是我们需要一个数据结构维护子树单点修改，子树乘，子树求和。可以使用线段树维护。总复杂度 $O(q\log q)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
} 
struct sgt{
	int f[1000005],siz[1000005],lzt[1000005];
	void pushdown(int i){
		(f[i*2]*=lzt[i])%=mod;
		(f[i*2+1]*=lzt[i])%=mod;
		(lzt[i*2]*=lzt[i])%=mod;
		(lzt[i*2+1]*=lzt[i])%=mod;
		lzt[i]=1;
	}
	void pushup(int i){
		f[i]=(f[i*2]+f[i*2+1])%mod;
	}
	void build(int i,int l,int r){
		lzt[i]=1;
		if(l==r) return ;
		build(i*2,l,mid),build(i*2+1,mid+1,r);
	}
	void add(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i]=siz[i]=cg;
			return ;
		}
		pushdown(i);
		if(pos<=mid) add(i*2,l,mid,pos,cg);
		else add(i*2+1,mid+1,r,pos,cg);
		pushup(i);
	}
	void mul(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			(f[i]*=cg)%=mod;
			(lzt[i]*=cg)%=mod;
			return ;
		}
		pushdown(i);
		if(ql<=mid) mul(i*2,l,mid,ql,qr,cg);
		if(qr>mid) mul(i*2+1,mid+1,r,ql,qr,cg);
		pushup(i);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return (qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr))%mod;
	}
}tree;
vector<pair<int,int>> qry;
vector<int> vc[200005];
int ind[200005],outd[200005],cnt,w[200005],n,son[200005];
void dfs(int now){
	ind[now]=++cnt;
	for(auto v:vc[now]){
		dfs(v);
	}
	outd[now]=cnt;
}
signed main(){
	int q; cin>>w[1]>>q; n=1;
	for(int i=1;i<=q;i++){
		int opt,p; cin>>opt>>p;
		if(opt==1) cin>>w[++n],vc[p].push_back(n);
		qry.push_back(make_pair(opt,p));
	}
	dfs(1);
	tree.build(1,1,n);
	tree.add(1,1,n,1,w[1]);
	son[1]=1;
	int m=1;
	for(auto v:qry){
		if(v.first==1){
			++m;
			tree.add(1,1,n,ind[m],w[m]);
			int tmp=tree.qry(1,1,n,ind[v.second],ind[v.second])*qp(w[v.second],mod-2)%mod;
			tree.mul(1,1,n,ind[m],ind[m],tmp);
			son[m]=1;
			tree.mul(1,1,n,ind[v.second],outd[v.second],(son[v.second]+1)*qp(son[v.second],mod-2)%mod); 
			son[v.second]++;
		}
		else{
			int tmp=tree.qry(1,1,n,ind[v.second],ind[v.second])*qp(w[v.second]*son[v.second]%mod,mod-2)%mod;
			cout<<tree.qry(1,1,n,ind[v.second],outd[v.second])*qp(tmp,mod-2)%mod<<"\n";
		}
	} 
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

观察到 $u$ 子树中 $v$ 对它的贡献，为 $a_v\prod\limits_{w \in path(u,v)} (son_w +1)$。设 $g_u=\prod\limits_{v\in path(1,u)} (son_v +1)$，那就是 $a_v \times \dfrac{g_v}{g_{fa_u}}$，那么 $u$ 的答案就是 $\dfrac{1}{g_{fa_{u}}} \sum\limits_{v \in G(u)} a_v g_v$。

所以只需要维护每个点的 $g_u a_u$，加入一个点 $v$，会影响 $fa_v$ 的整棵子树，需要子树乘，单点改。查询就是子树和。

dfs 序维护即可，复杂度 $\Theta(n \log n)$。

---

## 作者：Mobius127 (赞：0)

[题传](https://www.luogu.com.cn/problem/CF607D)

记 $(a, b)$ 为树上 $a$ 到 $b$ 路径上的所有点的集合。

这个贡献太难算了，一统计就是整颗子树，我们不妨统计 $u$ 的子树中每个节点 $z$ 的贡献，在 $z$ 不断向上跳的过程中，每经过一个点 $y$，就要乘上 $siz_y$，所以不难得出：

$$f(u)=\sum_{z \in S_u} w_z \times \prod_{y \in (u, z)} siz_y$$

我们有多次询问，$x$ 不定，所以 $\prod_{y \in (x, z)} siz_y$ 比较难搞，令 $f_x$ 为 $x$ 的父亲，类似于前缀和优化，有：

$$\prod_{y \in (x, z)} siz_y=\frac{\prod_{y \in (1, z)} siz_y}{\prod_{y \in (1, f_x)} siz_y}$$

令 $pre_x=\prod_{y \in (1, x)} siz_y$，带回原式，可得：

$$f(u)=\sum_{z \in S_u} w_z \times \frac{pre_z}{pre_{f_u}}$$

注意到 $pre_x$ 是定值，所以珂以提出，

$$=\frac{\sum_{z \in S_u} w_z \times pre_z}{pre_{f_u}}$$

现在着手考虑 $w_z \times pre_z$ 与 $pre_{f_u}$ 的维护。

考虑新增一个点的影响，它的父亲只影响到整颗父亲的子树，且每次增加 1，我们需要先除去旧的 $siz_{f}$ 的贡献，再乘上新的贡献 $siz_f+1$。即乘上 $\frac{siz_f+1}{siz_f}$，这个拿线段树珂以轻松解决（记得拍成 dfs 序），注意，这里的整棵子树是包括 **还未建出的点**！（不然你以后还得把贡献算上）

需要注意的一个点是，算完父的贡献之后，需要把自己的贡献补上。

复杂度 $O(Q\log n)$。

### Code：


```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <vector>
using namespace std;
const int N=200005;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)) f=(ch=='-'?-1:f), ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0', ch=getchar();
	return x*f;
}
inline int ksm(int a, int b){
	int res=1;for(; b; b>>=1, a=1ll*a*a%mo) if(b&1) res=1ll*res*a%mo;
	return res;
}
#define ls k<<1
#define rs k<<1|1
#define mid (l+r>>1)
int sum[N*4], mu[N*4];
void build(int k, int l, int r){mu[k]=1;if(l==r) return ;build(ls, l, mid), build(rs, mid+1, r);}
void upd(int k, int t){
	sum[k]=1ll*sum[k]*t%mo;
	mu[k]=1ll*mu[k]*t%mo;
}
void pushdown(int k){
	if(mu[k]==1) return ;
	upd(ls, mu[k]), upd(rs, mu[k]);mu[k]=1;
	return ; 
}
void pushup(int k){
	sum[k]=(sum[ls]+sum[rs])%mo;
	return ;
}
void insert(int k, int l, int r, int x, int w){
	if(l==r){
		sum[k]=1ll*w*mu[k]%mo;
		return ;
	}pushdown(k);
	if(x<=mid) insert(ls, l, mid, x, w);
	else insert(rs, mid+1, r, x, w);
	return pushup(k);
}
void mul(int k, int l, int r, int x, int y, int w){
	if(x<=l&&r<=y) return upd(k, w);pushdown(k);
	if(x<=mid) mul(ls, l, mid, x, y, w);
	if(mid<y) mul(rs, mid+1, r, x, y, w);
	return pushup(k);
}
int query(int k, int l, int r, int x, int y, bool flg){
	if(x>r||y<l) return 0;
	if(x<=l&&r<=y) return flg?mu[k]:sum[k];pushdown(k);
	return (query(ls, l, mid, x, y, flg)+query(rs, mid+1, r, x, y, flg))%mo;
}
#undef ls
#undef rs
#undef mid
int n=1, Q, W[N], pos[N], op[N], dfn[N], siz[N], f[N], tot, nw[N];
vector <int> G[N];
void dfs(int x){
	siz[x]=1;dfn[x]=++tot;
	for(int i=0; i<G[x].size(); i++)
		f[G[x][i]]=x, dfs(G[x][i]), siz[x]+=siz[G[x][i]];
}
signed main(){
	W[1]=read(), Q=read();
	for(int i=1; i<=Q; i++){
		op[i]=read(), pos[i]=read();
		if(op[i]&1) W[++n]=read(), G[pos[i]].push_back(n), pos[i]=n;
	}
	dfs(1);build(1, 1, n);
	insert(1, 1, n, 1, W[1]);
	for(int i=1; i<=n; i++) nw[i]=1;
	for(int i=1; i<=Q; i++){
		int x=pos[i], fa=f[x];
		if(op[i]&1){
			int w=1ll*(nw[fa]+1)*ksm(nw[fa], mo-2)%mo;nw[fa]++;
			mul(1, 1, n, dfn[fa], dfn[fa]+siz[fa]-1, w);
			insert(1, 1, n, dfn[x], W[x]);
		}
		else{
			int S=query(1, 1, n, dfn[x], dfn[x]+siz[x]-1, 0);
			int Z=1;
			if(x>1) Z=query(1, 1, n, dfn[fa], dfn[fa], 1);
			printf("%d\n", 1ll*S*ksm(Z, mo-2)%mo);
		}
	}
	return 0;
}
```




---

## 作者：弦巻こころ (赞：0)

题意:给你一些操作,其中一个操作是加入一个点,另一个操作是查询一个点的贡献.

对于一个点,它的贡献为:$|S|*\sum_{d \in s}d$

其中S是它的权值$w_i$与它的儿子 **(不是子树)** 的可重集合.

考虑如何维护.

当加入一个点$i$时,它只会让它的父亲的$|S|$加一,并且对包含它的祖先产生$w_i$的贡献.

我们可以想到,维护dfs序,并用线段树维护权值.

那么如何维护呢.

我们发现如果我们将$f(i)$视为$query(d[i],d[i]+sz[i]-1)$ 的话,当加入一个点时,它的父亲的$|S|$会变成$|S|+1$,所以我们将$d[f]+sz[f]-1$区间除上$|S|$再乘上$|S|+1$,就不会出错.,但此时加入的点权不能设成$w_i$了,需要设成$w_i * query(d[f],d[f])/w[f]$ .这么做是因为你需要维护总体的和.在查询时我们再除上$query(d[f],d[f])/w[f]$就行了.至于不单纯乘上$s_f$的原因,是因为你的祖先也对你进行了乘法操作,如果你单纯的去乘$s_f$的话那么贡献就不对了.

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define ll long long
const int N=1514514;
const int mod=1e9+7;
vector<int> v[N],q[N];
int fa[N],sz[N],d[N];
int n,m,pos,as[N];
ll tr[N],s[N],lz[N],w[N];
ll msk(ll a){ll b=mod-2,k=1;
	while(b){if(b&1)k=k*a%mod;a=a*a%mod;b>>=1;}return k;
}
void down(int i){
 	ll k=lz[i];lz[i]=1;if(k<=1)return;
 	lz[ls]=lz[ls]*k%mod;lz[rs]=lz[rs]*k%mod;
 	tr[ls]=tr[ls]*k%mod;tr[rs]=tr[rs]*k%mod;
}
void add(int i,int l,int r,int s,int t,ll w1,ll w2){
	if(s<=l&&r<=t){tr[i]=(tr[i]+w1)*w2%mod;lz[i]=lz[i]*w2%mod;return;}
	down(i);if(s<=mid)add(ls,l,mid,s,t,w1,w2);
	if(t>mid) add(rs,mid+1,r,s,t,w1,w2);tr[i]=(tr[ls]+tr[rs])%mod;
}//乘法和加法放一起了()
void dfs(int x){d[x]=++pos;sz[x]=1;
	for(int i=0;i<v[x].size();i++)
		dfs(v[x][i]),sz[x]+=sz[v[x][i]];
}ll query(int i,int l,int r,int s,int t){
	if(s<=l&&r<=t)return tr[i];down(i);
	ll ans=0;if(s<=mid)ans=query(ls,l,mid,s,t);
	if(t>mid)ans=(ans+query(rs,mid+1,r,s,t))%mod;return ans;
}
int main(){
	scanf("%d%d",&w[1],&m);n=1;
	for(int i=1,op,x;i<=m;i++){
		scanf("%d%d",&op,&x);
		if(op==1)n++,scanf("%d",&w[n]),fa[n]=x,v[x].push_back(n);
		else q[n].push_back(x);
	}dfs(1);add(1,1,n,1,1,w[1],1);s[1]=1;
	for(int j=0;j<q[1].size();j++)printf("%lld\n",w[1]);
	rep(i,2,n){int f=fa[i];
		add(1,1,n,d[f],d[f]+sz[f]-1,0,(s[f]+1)*msk(s[f])%mod);s[f]++;s[i]=1;
		add(1,1,n,d[i],d[i],query(1,1,n,d[f],d[f])*msk(w[f])%mod*w[i]%mod,1);
        //这里先乘再加与先加再乘没有区别
		for(int j=0;j<q[i].size();j++){
			int u=q[i][j];ll kkr=query(1,1,n,d[u],d[u]+sz[u]-1);
			if(u==1)printf("%lld\n",kkr);//特判1防止查询 0
			else printf("%lld\n",kkr*w[fa[u]]%mod*msk(query(1,1,n,d[fa[u]],d[fa[u]]))%mod);//记得除上自己乘的贡献数
		}
	}
}

```

---

