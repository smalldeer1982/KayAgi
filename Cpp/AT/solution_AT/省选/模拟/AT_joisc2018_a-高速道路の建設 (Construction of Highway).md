# 高速道路の建設 (Construction of Highway)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_a



# 题解

## 作者：Reunite (赞：2)

水题。

## 一
---
题目给的连边条件实在是太好了，直接离线建树，问题转化为：

- 从 $1$ 到 $u$ 查询逆序对数。再把 $1$ 到 $u$ 颜色推平。

这个推平就一脸 ODT 的感觉，但是普通 ODT 是在序列上的，这里需要在树上进行，其实也很容易，套一个重链剖分即可。

具体地，我们对于每一条重链维护一个 set，由于重链上编号连续，很好维护 $[l,r,c]$ 为编号在 $[l,r]$ 之间，点权为 $c$ 的连续段。查询的话暴力跳重链，并且把每一个合法连续段记录下来，做一遍树状树组优化逆序对即可。这里只能对每一段整体做，不然无法保证复杂度。推平是普通的。

## 二
---
重链上维护 ODT 是两只 $\log$，查询总共弄下来的段数最多是 $O(n\log_2n)$ 的（每次询问从 $\log_2n$ 重链上记下来 $O(1)$ 个），再加上树状树组的复杂度，总时间复杂度是 $O(n\log_2^2n)$。空间 $O(n)$。

感觉这题很一般，不如校内一场模拟赛 T1，推平这个提示太强了。

## 三
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#define ll long long
using namespace std;

int n,m,tm;
int t[100005];
int b[100005];
int c[100005];
int uu[100005];
int vv[100005];
int sz[100005];
int fa[100005];
int son[100005];
int dep[100005];
int top[100005];
int dfn[100005];
int ti[100005];
vector <int> g[100005];
struct node{int l,r,c;};
bool operator < (node p,node q){return p.l<q.l;}
set <node> st[100005];
node a[100005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

void dfsfind(int u,int fath){
	fa[u]=fath;
	dep[u]=dep[fath]+1;
	sz[u]=1;
	for(int v:g[u]){
		if(v==fath) continue;
		dfsfind(v,u);
		sz[u]+=sz[v];
		if(sz[son[u]]<sz[v]) son[u]=v;
	}
	return ;
}

void dfstime(int u,int tp){
	top[u]=tp;
	dfn[u]=++tm;
	ti[tm]=u;
	if(son[u]) dfstime(son[u],tp);
	for(int v:g[u]){
		if(v==fa[u]||v==son[u]) continue;
		dfstime(v,v);
	}
	return ;
}

set <node> :: iterator split(int pos,int id){
	set <node> :: iterator it=st[id].lower_bound({pos,0,0});
	if(it!=st[id].end()&&it->l==pos) return it;
	it--;
	if(it->r<pos) return st[id].end();
	int l=it->l;
	int r=it->r;
	int c=it->c;
	st[id].erase(it);
	st[id].insert({l,pos-1,c});
	return st[id].insert({pos,r,c}).first;
}

inline void add(int x,int k){while(x<=m) t[x]+=k,x+=x&-x;return ;}
inline int ask(int x){int s=0;while(x) s+=t[x],x^=x&-x;return s;}

inline void work(int u){
	int m=0;
	while(u){
		auto ed=split(dfn[u]+1,top[u]);
		auto it=st[top[u]].begin();
		while(it!=ed) a[++m]={dep[ti[it->l]],it->r-it->l+1,it->c},it++;
		u=fa[top[u]];
	}
	sort(a+1,a+1+m);
	ll ans=0,cnt=0;
	for(int i=1;i<=m;i++){
		ans+=1ll*a[i].r*(cnt-ask(a[i].c));
		add(a[i].c,a[i].r);
		cnt+=a[i].r;
	}
	for(int i=1;i<=m;i++) add(a[i].c,-a[i].r);
	printf("%lld\n",ans);
	return ;
}

inline int Find(int u){
	auto it=st[top[u]].upper_bound({dfn[u],0,0});
	it--;
	return it->c;
}

inline void cover(int u,int c){
	while(u){
		auto ed=split(dfn[u]+1,top[u]);
		st[top[u]].erase(st[top[u]].begin(),ed);
		st[top[u]].insert({dfn[top[u]],dfn[u],c});
		u=fa[top[u]];
	}
	return ;
}

int main(){
	in(n);
	for(int i=1;i<=n;i++) in(c[i]),b[i]=c[i];
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++) c[i]=lower_bound(b+1,b+1+m,c[i])-b;
	for(int i=1;i<n;i++){
		in(uu[i]),in(vv[i]);
		g[uu[i]].push_back(vv[i]);
		g[vv[i]].push_back(uu[i]);
	}
	dfsfind(1,0);
	dfstime(1,1);
	for(int i=1;i<=n;i++) st[top[i]].insert({dfn[i],dfn[i],c[i]});
	for(int i=1;i<n;i++){
		work(uu[i]);
		cover(uu[i],Find(vv[i]));
	}

	return 0;
}

```

---

## 作者：CQ_Bab (赞：1)

# 思路
看到这种区间覆盖可以优先考虑 ODT 了，因为每次它都覆盖的是一条路径那么考虑每次用 ODT 来修改，因为 ODT 需要时一个连续的区间所以直接套一个重链剖分即可，然后我们将询问离线，然后对于每一次询问按照通过树链剖分去跳链，然后将其加入树状数组中然后再将查询答案累积到答案中即可。

注意，因为树链剖分的每一个小区间是从前往后遍历的，而树剖又是整体从下往上跳的，故去要将其中一个反着遍历，时间复杂度大概是 $O(n\log(n)^3)$，成功成为目前最劣解。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define int long long
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n;
struct node{
	int l,r;
	mutable int val;
	friend bool operator<(const node&a,const node&b) {
		return a.l<b.l;
	}
};
const int N=1e5+10;
vector<int>v[N];
set<node>s;
auto split(int pos) {//ODT
	auto it=s.lower_bound({pos,0,0});
	if(it!=s.end()&&it->l==pos) return it;
	it--;
	if(it->r<pos) return s.end();
	int l=it->l,r=it->r,v=it->val;
	s.erase(it);
	s.insert({l,pos-1,v});
	return s.insert({pos,r,v}).first;
}
void add(int l,int r,int c) {
	auto itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert({l,r,c});
}
int a[N],b[N];
int ans[N];
int dfn[N],son[N],siz[N],f[N],dep[N],top[N];
void dfs(int x,int fa) {
	f[x]=fa;
	dep[x]=dep[fa]+1;
	siz[x]=1;
	for(auto to:v[x]) {
		if(to==fa) continue;
		dfs(to,x);
		siz[x]+=siz[to];
		if(siz[to]>siz[son[x]]) son[x]=to;
	}
}
int idx,mp[N];
void dfs1(int x,int head) {
	top[x]=head;
	dfn[x]=++idx; 
	mp[idx]=x;
	if(!son[x]) return ;
	dfs1(son[x],head);
	for(auto to:v[x]) if(!dfn[to]) dfs1(to,to);
}
int res[N];
int lowbit(int x) {
	return x&-x;
}
int tr[N];
void add(int x,int k) {
	for(;x<=n;x+=lowbit(x)) tr[x]+=k;
}
int Ans(int x) {
	int res=0;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
void modify(int x,int y,int &res) {
	auto itr=split(y+1),itl=split(x);
	itr--;
	itl--;
	auto it=itr;
	for(;itl!=itr;itr--) {
		int cnt=itr->r-itr->l+1;
		res+=cnt*Ans(itr->val-1);
		add(itr->val,cnt);
	}
}
void modify1(int x,int y) {
	auto itr=split(y+1),itl=split(x);
	itr--;
	itl--;
	auto it=itr;
	for(;itl!=itr;itr--) {
		int cnt=itr->r-itr->l+1;
		add(itr->val,-cnt);
	}
}
int Ans(int x,int y) {
	int res=0;
	int xx=x,yy=y;
	while(top[x]!=top[y]) {//树链剖分
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(dfn[top[x]],dfn[x],res);
		x=f[top[x]];
	}
	if(dfn[x]>dfn[y]) swap(x,y);
	modify(dfn[x],dfn[y],res);
	x=xx,y=yy;
	while(top[x]!=top[y]) {//清空
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify1(dfn[top[x]],dfn[x]);
		x=f[top[x]];
	}
	if(dfn[x]>dfn[y]) swap(x,y);
	modify1(dfn[x],dfn[y]);
	return res;
}
void gai(int x,int y,int k) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])  swap(x,y);
		add(dfn[top[x]],dfn[x],k);
		x=f[top[x]];
	}
	if(dfn[x]>dfn[y]) swap(x,y);
	add(dfn[x],dfn[y],k);
}
int tt[N];
void solve() {
	in(n);
	rep(i,1,n) in(a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	int m=unique(b+1,b+1+n)-b-1;
	rep(i,1,n) a[i]=lower_bound(b+1,b+1+m,a[i])-b;//离散化
	rep(i,1,n-1) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
		ans[i]=x;
		tt[i]=y;
	}
	dfs(1,0);
	dfs1(1,1);
	rep(i,1,n) s.insert({i,i,a[mp[i]]});
	rep(i,1,n-1) res[i]=Ans(1,ans[i]),gai(1,ans[i],a[tt[i]]);
	rep(i,1,n-1) printf("%lld\n",res[i]);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}

```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2018A 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_a)

**题目大意**

> 给 $n$ 个点，初始每个点有权值 $w_i$，$n-1$ 次操作连一条边 $u\gets v$，其中 $u$ 与 $1$ 连通，$v$ 与 $1$ 不连通，求 $1\to u$ 路径上权值的逆序对数，然后把路径权值推平为 $v$ 的权值。
>
> 数据范围：$n\le 10^5$。

**思路分析**

考虑 LCT，注意到每次连边后 $access(v)$，那么当前树上每条实链颜色都相同。

因此在 $access$ 过程中对于每棵实链对应的 splay 里的点权值都一样，我们只关心 splay 里有几个点是 $v$ 的祖先，显然把实链底 $x$ 转到根上，那么就有 $siz_{ls(rt)}+1$ 个颜色为 $w_{rt}$ 的点，统计当前有多少个点 $<w_{rt}$，然后插入树状数组对祖先贡献。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+1,W=1e9;
int n,w[MAXN]; ll ans;
struct FenwickTree {
	int tr[MAXN]; ll s;
	vector <int> p;
	inline void add(int x,int v) { for(p.push_back(x);x<=n;x+=x&-x) tr[x]+=v; }
	inline ll qry(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
	inline void clr() { for(int x:p) for(;x<=n;x+=x&-x) tr[x]=0; p.clear(); }
}	T;
namespace LCT {
int fa[MAXN],ch[MAXN][2],col[MAXN],cov[MAXN],siz[MAXN];
inline void psu(int p) { siz[p]=siz[ch[p][0]]+siz[ch[p][1]]+1; }
inline void adt(int x,int c) { if(x) cov[x]=col[x]=c; }
inline void psd(int x) { if(cov[x]) adt(ch[x][0],cov[x]),adt(ch[x][1],cov[x]),cov[x]=0; }
inline bool nrt(int p) { return ch[fa[p]][0]==p||ch[fa[p]][1]==p; }
inline int son(int x) { return ch[fa[x]][1]==x; }
inline void upd(int p) { if(nrt(p)) upd(fa[p]); psd(p); }
inline void rot(int p) {
	int u=fa[p],v=fa[u],k=son(p);
	if(nrt(u)) ch[v][son(u)]=p;
	fa[ch[u][k]=ch[p][k^1]]=u,fa[fa[ch[p][k^1]=u]=p]=v;
	psu(p),psu(u);
}
inline void splay(int p) { for(upd(p);nrt(p);rot(p)) if(nrt(fa[p])) rot(son(p)==son(fa[p])?fa[p]:p); }
inline int access(int p) {
	int u=0;
	for(ans=0,T.clr();p;u=p,p=fa[p]) {
		splay(p);
		int tmp=1+siz[ch[p][0]];
		ans+=1ll*tmp*T.qry(col[p]-1);
		T.add(col[p],tmp);
		ch[p][1]=u,psu(p);
	}
	return u;
}
}
using namespace LCT;
signed main() {
	scanf("%d",&n);
	vector <int> vals;
	for(int i=1;i<=n;++i) scanf("%d",&w[i]),vals.push_back(w[i]);
	sort(vals.begin(),vals.end()),vals.erase(unique(vals.begin(),vals.end()),vals.end());
	for(int i=1;i<=n;++i) w[i]=lower_bound(vals.begin(),vals.end(),w[i])-vals.begin()+1;
	col[1]=w[1],siz[1]=1;
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		adt(access(u),w[v]);
		printf("%lld\n",ans);
		fa[v]=u,col[v]=w[v],siz[v]=1;
	}
	return 0;
}
```



---

## 作者：littlez_meow (赞：0)

珂朵莉树真是太好用辣！

[题目指路](https://www.luogu.com.cn/problem/AT_joisc2018_a)。

## 思路

区间推平，这不明摆着珂朵莉树吗？记维护区间的权值为 $v$。

要求根节点到某个点上的逆序对，又不是很好归并，那就是先离散化再树状数组。

每次修改和查询又是一条路径，这启发我们进行树剖。

以上三个综合起来，得到本题做法：

首先按操作给出的建出树，做一次重链剖分。

然后每次跳重链，对于每条重链从下向上遍历珂朵莉树的节点，每个节点对答案的贡献是该节点区间长度乘权值树状数组上 $v-1$ 的前缀和。

对答案贡献完之后，权值树状数组 $v$ 的值加区间长度。

最后跳重链做区间推平。

考虑时间复杂度，每次只会经过 $O(\log n)$ 条重链，每次加是 $O(\log n)$ 的。

发现每次修改会覆盖掉 $O(\log n)$ 条重链的前缀，也就是说，每条重链的颜色段是均摊 $O(1)$ 的。

综上，时间复杂度 $O(n\log^2 n)$。

如果不知道怎么均摊，有一种感性理解方式。当树高比较浅（$O(\log n)$）时，即使颜色段莫名奇妙卡满了也是 $O(\log n)$ 个区间；当树高比较深（$O(n)$）时，很长一段从根节点的路径都会是同一个值被缩成一段，时间复杂度也是对的。

最后一点细节问题，对树状数组的操作序列要记下来，一次逆序对计算完之后把操作反向做一遍以清空树状数组。如果暴力 `memset` 复杂度会退化成 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define fir first
#define sec second
using namespace std;
const int MAXN=1e5+1;
int n;
struct Segt{
	int l,r;
	mutable int v;
	Segt(const int&x,const int&y,const int&z):l(x),r(y),v(z){}
	inline bool operator<(const Segt&x)const{
		return l<x.l;
	}
};
set<Segt>odt;
inline auto split(int pos){
	auto it=odt.lower_bound((Segt){pos,0,0});
	if(it!=odt.end()&&it->l==pos) return it;
	--it;
	if(it->r<pos) return odt.end();
	int l(it->l),r(it->r),v(it->v);
	odt.erase(it);
	odt.insert({l,pos-1,v});
	return odt.insert({pos,r,v}).fir;
}
inline void assign(int l,int r,int v){
	auto itr=split(r+1);
	auto itl=split(l);
	odt.erase(itl,itr);
	odt.insert((Segt){l,r,v});
	return;
}
int c[MAXN];
pair<int,int>road[MAXN];
vector<int>tree[MAXN];
int fa[MAXN],siz[MAXN],son[MAXN];
int dfn[MAXN],chain[MAXN];
void dfs1(int root,int f){
	fa[root]=f,siz[root]=1;
	for(int i:tree[root]){
		if(i==f) continue;
		dfs1(i,root);
		siz[root]+=siz[i];
		siz[i]>siz[son[root]]&&(son[root]=i);
	}
	return;
}
void dfs2(int root,int top){
	chain[root]=top;
	dfn[root]=++n;
	odt.insert((Segt){n,n,c[root]});
	if(!son[root]) return;
	dfs2(son[root],top);
	for(int i:tree[root]){
		if(i==son[root]||i==fa[root]) continue;
		dfs2(i,i);
	}
	return;
}
map<int,int>lsh;
int cnt;
int bit[MAXN+1];
#define lowbit(x) (x&(-x))
inline void add(int x,int v){
	for(;x<=cnt;x+=lowbit(x)) bit[x]+=v;
	return;
}
inline ll query(int x){
	ll res(0);
	for(;x;x-=lowbit(x)) res+=bit[x];
	return res;
}
pair<int,int>opt[MAXN];
int top;
inline ll calc(int now){
	ll res(0);
	while(now){
		auto itr=prev(split(dfn[now]+1));
		auto itl=prev(split(dfn[chain[now]]));
		while(itr!=itl){
			res+=(itr->r-itr->l+1)*query(itr->v-1);
			add(itr->v,itr->r-itr->l+1);
			opt[++top]={itr->v,itr->r-itr->l+1};
			--itr;
		}
		now=fa[chain[now]];
	}
	while(top) add(opt[top].fir,-opt[top].sec),--top;
	return res;
}
inline void modify(int now){
	int v=c[now];
	while(now){
		assign(dfn[chain[now]],dfn[now],v);
		now=fa[chain[now]];
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	odt.insert({0,0,0});
	F(i,1,n) cin>>c[i],lsh[c[i]]=-1;
	for(auto i:lsh) lsh[i.fir]=++cnt;
	F(i,1,n) c[i]=lsh[c[i]];
	F(i,1,n-1){
		int a,b;
		cin>>a>>b;
		tree[a].push_back(b);
		tree[b].push_back(a);
		road[i]={a,b};
	}
	dfs1(1,0);
	n=0;
	dfs2(1,1);
	F(i,1,n-1){
		cout<<calc(road[i].fir)<<"\n";
		modify(road[i].sec);
	}
	return 0;
}
```

完结撒花，不喜勿喷 ovo~

---

## 作者：Rosaya (赞：0)

### 题意

给定 $n$ 个点，初始时 $i$ 号点的权值为 $c_i$。

接下来进行 $n-1$ 次加边操作，每次连接一条边 $(u,v)$，保证此时 $u$ 与 $1$ 号点连通，$v$ 与 $1$ 号点不连通。

对于每一次加边，求出 $1$ 号点到 $u$ 的简单路径上的逆序对数量，并在操作结束后将 $1$ 号点到 $u$ 的简单路径上的所有点的权值改为 $c_v$。

$1 \le n \le 10^5,1 \le c_i \le 10^9,1 \le u,v \le n$。

### 思路

显然没法直接维护区间逆序对进行合并，而路径覆盖看起来很能均摊，所以我们考虑用一些方式维护这个颜色段。

具体的，我们考虑重链剖分，这样每次查询时都只会涉及到 $O(\log n)$ 条重链。

我们不妨将重链所有的颜色段都拿出来，这个数量可能是 $O(n)$ 的，然后对这个序列做一遍逆序对。

修改时我们发现是对有关的 $O(\log n)$ 条重链做前缀覆盖，这样的话涉及到的 $O(n)$ 个颜色段只会剩 $O(\log n)$ 个，每条重链多一个分界点。

所以颜色段数量均摊分析时 $O(n \log n)$ 的，瓶颈在求逆序对上，总复杂度 $O(n \log^2 n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,c[100005],num[100005];
int f[100005],siz[100005],top[100005],son[100005],dep[100005];
int tr[100005];
ll ans;
vector<int> adj[100005],col[100005];

inline void dfs(int u)
{
    dep[u]=dep[f[u]]+1;
    siz[u]=1;

    for(int i=0;i<adj[u].size();i++)
    {
        int v=adj[u][i];

        dfs(v);

        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])
            son[u]=v;
    }
}

inline void getson(int u)
{
    if(son[u])
    {
        top[son[u]]=top[u];
        getson(son[u]);
    }

    for(int i=0;i<adj[u].size();i++)
    {
        int v=adj[u][i];

        if(v==son[u])
            continue;

        top[v]=v;
        getson(v);
    }

    col[top[u]].push_back(c[u]);
    col[top[u]].push_back(1);
}

inline void getcol(int u,int p)
{
    if(!u)
        return;

    getcol(f[top[u]],p);

    int sz=dep[u]-dep[top[u]]+1;
    int tp=sz;

    while(sz)
    {
        int nm=col[top[u]].back();
        col[top[u]].pop_back();
        int id=col[top[u]].back();
        col[top[u]].pop_back();
        
        col[0].push_back(id);
        col[0].push_back(min(nm,sz));

        if(nm>sz)
        {
            col[top[u]].push_back(id);
            col[top[u]].push_back(nm-sz);
        }

        sz=max(0,sz-nm);
    }

    col[top[u]].push_back(p);
    col[top[u]].push_back(tp);
}

inline int lbt(int k){return k&-k;}

inline void add(int pos,int val)
{
    while(pos<=n)
    {
        tr[pos]+=val;
        pos+=lbt(pos);
    }
}

inline int query(int pos)
{
    int res=0;

    while(pos)
    {
        res+=tr[pos];
        pos-=lbt(pos);
    }

    return res;
}

inline void getans()
{
    ans=0;

    for(int i=0;i<col[0].size();i+=2)
    {
        int id=col[0][i],nm=col[0][i+1];

        ans+=1LL*nm*query(id);
        add(1,nm),add(id,-nm);
    }

    for(int i=0;i<col[0].size();i+=2)
    {
        int id=col[0][i],nm=col[0][i+1];
        add(1,-nm),add(id,nm);
    }

    col[0].clear();

    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
        cin>>c[i],num[i]=c[i];

    sort(num+1,num+n+1);
    for(int i=1;i<=n;i++)
        c[i]=lower_bound(num+1,num+n+1,c[i])-num;

    for(int i=1;i<n;i++)
    {
        int u;
        cin>>u>>num[i];
        f[num[i]]=u;
        adj[u].push_back(num[i]);
    }

    dfs(1);
    top[1]=1;
    getson(1);

    for(int i=1;i<n;i++)
    {
        getcol(f[num[i]],c[num[i]]);
        getans();
    }

    return 0;
}
```

---

