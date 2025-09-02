# Babysitting

## 题目描述

Theofanis wants to play video games, however he should also take care of his sister. Since Theofanis is a CS major, he found a way to do both. He will install some cameras in his house in order to make sure his sister is okay.

His house is an undirected graph with $ n $ nodes and $ m $ edges. His sister likes to play at the edges of the graph, so he has to install a camera to at least one endpoint of every edge of the graph. Theofanis wants to find a [vertex cover](https://en.wikipedia.org/wiki/Vertex_cover) that maximizes the minimum difference between indices of the chosen nodes.

More formally, let $ a_1, a_2, \ldots, a_k $ be a vertex cover of the graph. Let the minimum difference between indices of the chosen nodes be the minimum $ \lvert a_i - a_j \rvert $ (where $ i \neq j $ ) out of the nodes that you chose. If $ k = 1 $ then we assume that the minimum difference between indices of the chosen nodes is $ n $ .

Can you find the maximum possible minimum difference between indices of the chosen nodes over all vertex covers?

## 说明/提示

In the first test case, we can install cameras at nodes $ 1 $ , $ 3 $ , and $ 7 $ , so the answer is $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1903F/d75ed844401c37d1caa07fbd47253f2f681dd7c5.png)In the second test case, we can install only one camera at node $ 1 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
3
7 6
1 2
1 3
1 4
1 6
2 3
5 7
3 3
1 2
1 3
1 1
2 4
1 2
1 2
2 1
1 1```

### 输出

```
2
3
2```

# 题解

## 作者：sunkuangzheng (赞：8)

考虑 $k$ 固定的时候怎么做。

题目中的限制可以转化为两条：

- 对于一条边 $(u,v)$，$u$ 不选 $\to$ $v$ 一定要选。

- 对于点 $u$，$u$ 选了 $\to $ 所有满足 $|u-v| < k$ 的点 $v(v \ne u)$ 都不能选。

你发现这个问题很 2-sat，但是边数是 $\mathcal O(nk)$ 级别的。又发现每次连边是单点连边，或者点向区间连边，线段树优化建图即可。

$k$ 不是固定的怎么办？直接二分。时间复杂度 $\mathcal O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 6e5+5;vector<pair<int,int>> gr;
int t,n,m,u,v,dfn[N],low[N],vis[N],st[N],be[N],tp,ti,tot;vector<int> g[N];
int id(int u,int x){return u + 4 * n + n * x;}
void add(int u,int v){return g[u].push_back(v);}
void build(int s,int l,int r){
    if(l == r) return add(s,id(l,0));int mid = (l + r) / 2;
    build(s*2,l,mid),build(s*2+1,mid+1,r),
    g[s].push_back(s*2),g[s].push_back(s*2+1);
}void upd(int s,int l,int r,int ql,int qr,int k){
    if(qr < ql || ql <= 0 || qr > n) return ;
    if(ql <= l && r <= qr) return add(id(k,1),s);
    int mid = (l + r) / 2;
    if(ql <= mid) upd(s*2,l,mid,ql,qr,k); if(qr > mid) upd(s*2+1,mid+1,r,ql,qr,k);
}void tarjan(int u){
    low[u] = dfn[u] = ++ti,st[++tp] = u,vis[u] = 1;
    for(int v : g[u]) if(!dfn[v]) tarjan(v),low[u] = min(low[u],low[v]); else if(vis[v]) low[u] = min(low[u],dfn[v]);
    if(low[u] == dfn[u]) for(++tot;;) if(be[st[tp]] = u,vis[st[tp]] = 0,st[tp --] == u) break;
}bool ck(int mid){
    for(int i = 1;i <= 6*n;i ++) g[i].clear(),dfn[i] = low[i] = vis[i] = 0;ti = tot = tp = 0;
    build(1,1,n);
    for(auto [u,v] : gr) add(id(u,0),id(v,1)),add(id(v,0),id(u,1));
    for(int i = 1;i <= n;i ++){
        int l = i - mid + 1,r = i + mid - 1;
        upd(1,1,n,max(l,1),i-1,i),upd(1,1,n,i+1,min(r,n),i);
    }for(int i = 1;i <= 6 * n;i ++) if(!dfn[i]) tarjan(i);
    for(int i = 1;i <= n;i ++) if(be[id(i,0)] == be[id(i,1)]) return 0;
    return 1;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n >> m,gr.clear();
        for(int i = 1;i <= m;i ++) cin >> u >> v,gr.emplace_back(u,v);
        int l = 1,r = n;
        while(l <= r){
            int mid = (l + r) / 2;
            if(ck(mid)) l = mid + 1; else r = mid - 1;
        }cout << l - 1 << "\n";
    }
}
```

---

## 作者：蒟蒻君HJT (赞：4)

很套路的题目，不知道为什么过的人这么少。盲猜被 D2 卡了？

考虑二分答案 $v$，转化为判断性问题。

容易发现新的问题非常像 2-SAT。具体来说，对每个原图中的结点 $x$ 建两个新结点 $x_1,x_2$ 分别表示 $x$ 被覆盖/不被覆盖。对于原图中的边 $(x,y)$，连边 $(x_2,y_1),(y_2,x_1)$ 表示若 $x,y$ 中一个不覆盖的话，另一个必须覆盖。

此外，对于 $|a_i-a_j|\geq v$ 的限制，再对每个结点 $x$ 建边 $(x_1,y_2),y\in[x-v+1,x+v-1] \backslash \{x\}$ 即可。

当然暴力建边太多了建不出来。考虑形如一个点像两个区间连边，线段树优化建图即可。不会的同学可以看一下 [这道题](https://www.luogu.com.cn/problem/CF786B)。

最后像普通的 2-SAT 一样 tarjan 缩出强连通分量，判断 $\forall x, x_1$ 和 $x_2$ 是否在一个强连通分量就可以了。

[for reference only.](https://codeforces.com/contest/1903/submission/235105725)


---

## 作者：CQ_Bab (赞：1)

# 思路
首先考虑转化问题，我们发现对于一条边 $a\to b$ 那么如果 $a$ 不选那么 $b$ 必须选，如果 $b$ 不选则 $a$ 必须选，然后又因为这道题中的**最大化最小值**所以直接二分，我们可以二分答案，但是这里还需要建边，就是对于那些 $|a-b|<mid$ 的如果 $a$ 选了，那么 $b$ 不选，后同理。

但是连下面那一条边不能暴力搞，所以直接线段树优化建边即可，不会的可可看一下[模板](https://www.luogu.com.cn/problem/CF786B)。

这就可以发现满足 2-SAT 的特性了所以直接二分加 2-SAT 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T;
int n,m;
const int N=1e5+10;
vector<int>v[N];
vector<int>ve[N*6];
/*
1~n 选
n+1~2*n 不选 
*/
struct node{
	int l,r;
}tr[N<<2];
void build(int u,int l,int r) {
	tr[u]={l,r};
	if(l==r) {
		ve[u+2*n].push_back(l+n);
		return ;
	}
	int mid=l+r>>1;
	ve[u+2*n].push_back((u<<1)+2*n);
	ve[u+2*n].push_back((u<<1|1)+2*n);
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void modify(int u,int l,int r,int id) {
	if(tr[u].l>=l&&tr[u].r<=r) {
		ve[id].push_back(u+2*n);
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) modify(u<<1,l,r,id);
	if(mid<r) modify(u<<1|1,l,r,id);
}
int get(int x) {
	return x+n;
}
int val[N*6],tot,idx;
int dfn[N*6],low[N*6],is[N*6];
stack<int>s;
void tarjan(int x) {
	dfn[x]=low[x]=++idx;
	is[x]=1;
	s.push(x);
	for(auto to:ve[x]) {
		if(!dfn[to]) tarjan(to),low[x]=min(low[x],low[to]);
		else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(dfn[x]==low[x]) {
		int p;
		tot++;
		do{
			p=s.top();
			s.pop();
			val[p]=tot;
			is[p]=false;
		}while(p!=x);
	}
}
bool check(int x) {
	rep(i,1,2*n) ve[i].clear();
	rep(i,1,6*n) dfn[i]=low[i]=is[i]=val[i]=false;
	rep(i,1,n) {
		for(auto to:v[i]) {
			ve[get(i)].push_back(to);
			ve[get(to)].push_back(i);
		}
	}
	rep(i,1,n) {
		int l=max(1ll,i-x+1),r=min(n,i+x-1);
		modify(1,l,i-1,i);
		modify(1,i+1,r,i);
	}
	tot=idx=false;
	rep(i,1,6*n) if(!dfn[i]) tarjan(i);
	rep(i,1,n) if(val[i]==val[get(i)]) return false;
	return 1;
}
void solve() {
	in(n),in(m);
	rep(i,1,n) v[i].clear();
	rep(i,1,6*n) ve[i].clear();
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	build(1,1,n);
	int l=0,r=n,res=false;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res<<endl;
	return;
}
fire main() {
	in(T);
	while(T--) {
		solve();
	}
	return false;
}

```

---

## 作者：Unnamed114514 (赞：1)

[link](https://codeforces.com/contest/1903/problem/F)

\*2500，一道简单的题目，不过感觉 tag 很有提示意义，不过因为 OJ bug 所以好像评测时间久了就测不出来。

虽然简单无脑，但是还是学到了一个 trick：**点覆盖问题可以通过强制一个点不取另外一个点取转 2-SAT**。

于是我们把点覆盖转换成 2-SAT。

最小最大，所以二分。

那么绝对值的限制就相当与是 $i$ 取的话，$\forall j\ne i,|j-i|<mid$ 的都不能取（不过因为 $j\ne i$ 耽搁了很长时间），那么这个问题就可以转成 2-SAT 了。

但是注意到第二类边一次最多 $O(n)$ 条，所以如果直接连要 T，但是因为是对一个区间连的，所以可以考虑 DS。

时间 $O(n\log^2n)$，空间 $O(n)$。


[code](https://codeforces.com/contest/1903/submission/238680843)

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给定一个无向图，求出权值最大的点覆盖，一个点覆盖的权值为被选出的点中不同点之间编号之差的绝对值的最小值。

## 题目分析

最大化最小值，考虑二分答案 $k$。

判断最小点覆盖的存在性，可以考虑 2-sat。因为边的限制和 2-sat 中的限制一模一样。

考虑加入 $k$ 的限制，即 $x$ 选了之后 $|y-x|\le k$ 的 $y$ 都不能选，这是两个区间，线段树优化建边即可。

复杂度 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L (x<<1)
#define R (L|1)
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =6e5+5,M=6e6+5;
int n,m;
struct edge{
	int x,y;
}a[N];
int h[N],to[M],nxt[M],cnt;
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int dfn[N],s[N],tp,low[N],Time,K,bel[N];
bool instac[N];
inline void tarjan(int x){
	low[x]=dfn[x]=++Time,s[++tp]=x,instac[x]=1;
	e(x)if(!dfn[y])tarjan(y),low[x]=min(low[x],low[y]);
	else if(instac[y])low[x]=min(low[x],dfn[y]);
	if(low[x]==dfn[x]){
		K++;
		for(int y=s[tp--];;y=s[tp--]){
			instac[y]=0,bel[y]=K;
			if(y==x)return;
		}
	}
}
inline void build(int x,int l,int r){
	if(l==r)return add_(x+n*2,l),void();
	add_(x+n*2,L+n*2),add_(x+n*2,R+n*2),build(lc),build(rc);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int fr){
	if(Ll>Rr)return;
	if(OK)return add_(fr,x+n*2),void();
	if(Ll<=mid)modify(lc,Ll,Rr,fr);
	if(Rr>mid)modify(rc,Ll,Rr,fr);
}
inline bool check(int x){
	rep(i,1,n*6)dfn[i]=h[i]=0;Time=K=cnt=0;
	build(Root);//x:不选 
	repm(i)add_(a[i].x,a[i].y+n),add_(a[i].y,a[i].x+n);
	repn(i)modify(Root,max(i-x+1,1LL),i-1,i+n),modify(Root,i+1,min(i+x-1,n),i+n);
	rep(i,1,n*6)if(!dfn[i])tarjan(i);
	repn(i)if(bel[i]==bel[i+n])return 0;
	return 1;
}
inline void Main(){
	n=read(),m=read();
	repm(i)a[i].x=read(),a[i].y=read();
	int l=1,r=n,ans=1;
	while(l<=r)if(check(mid))ans=mid,l=mid+1;
	else r=mid-1;
	cout <<ans<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```


---

## 作者：huangrenheluogu (赞：1)

直接求解这个最小差值不好做，发现 $n$ 是在 $10^5$ 的级别，考虑可以套多个 $\log$。所以可以用一个二分答案来转化为判定问题。

考虑二分答案出一个 $mid$，下面进行判定。

首先，是两条边至少选一条。

其次，是对于一个点 $i$，如果选择了 $i$，那么 $\max\{1,i-mid+1\}\sim i-1$ 和 $i+1\sim \min\{i+1,i+mid-1\}$ 就不能被选择。

如果这样暴力建边，边数可以达到 $\mathcal{O}(n^2)$，无法通过本题。

考虑线段树优化建边。

主要做法就是将线段树上一个点和其代表的所有点连边，然后点对区间建边就是对代表区间的点建边即可。

比如一颗线段树，我们用节点 $x$ 代表了 $[l,r]$ 的区间不可选，那么如果要求 $[l,r]$ 不可选，只需和 $x$ 连边即可；而在预处理的时候，$x$ 和 $[l,r]$ 中代表不可选的那一面连边，然后跑 2-SAT。

合并和线段树上差不多，比如 $x_1,x_2,x_3$ 分别代表 $[a_1,a_2],[a_2+1,a_3],[a_3+1,a_4]$ 代表的区间，那么，如果一个点 $p$ 需要和 $[a_1,a_4]$ 连边，只需 $p$ 和 $x_1,x_2,x_3$ 分别连边即可。

这个连边过程可以在线段树上实现。

```cpp
inline void modify(int p, int l, int r ,int x, int y, int s){
	if(x <= l && r <= y){
		ver[s].pb(p + 2 * n);
		return ;
	}
	int mid = l + r >> 1;
	if(mid >= x) modify(ls, l, mid, x, y, s);
	if(mid < y) modify(rs, mid + 1, r, x, y, s);
}
```

上面的代码就代表了 $s$ 向 $[x,y]$ 连边。

建完边之后跑一遍 2-SAT 即可。

```cpp
#include<bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int T, n, m, dfn[N * 6], low[N * 6], to[N * 6], u, v, l, r, mid, idx, q[N * 6], t, ans, cnt;
bool vis[N * 6];
vector<int>ver[N * 6];
inline void init(){
	for(int i = 1; i <= n * 6; i++){
		dfn[i] = low[i] = to[i] = vis[i] = 0;
	}
	cnt = t = idx = 0;
}
inline void build(int p, int l, int r){
	for(int i = l; i <= r; i++) ver[p + n * 2].pb(i + n);
	if(l == r) return ;
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
}
inline void modify(int p, int l, int r ,int x, int y, int s){
	if(x <= l && r <= y){
		ver[s].pb(p + 2 * n);
		return ;
	}
	int mid = l + r >> 1;
	if(mid >= x) modify(ls, l, mid, x, y, s);
	if(mid < y) modify(rs, mid + 1, r, x, y, s);
}
inline void tarjan(int x){
	dfn[x] = low[x] = ++idx;
	vis[x] = 1;
	q[++t] = x;
	for(auto v : ver[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}
		else if(vis[v]) low[x] = min(low[x], dfn[v]);
	}
	if(low[x] == dfn[x]){
		cnt++;
		while(vis[x]){
			to[q[t]] = cnt;
			vis[q[t--]] = 0;
		}
	}
}
inline bool check(int mid){
	for(int i = 1; i <= n; i++) ver[i].clear();
	int L, R;
	for(int i = 1; i <= n; i++){
		L = max(1, i - mid + 1);
		R = i - 1;
		if(L <= R) modify(1, 1, n, L, R, i);
		L = i + 1;
		R = min(n, i + mid - 1);
		if(L <= R) modify(1, 1, n, L, R, i);
	}
	init();
	for(int i = 1; i <= n * 6; i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i = 1; i <= n; i++) if(to[i] == to[i + n]) return 0;
	return 1;
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n * 6; i++) ver[i].clear();
		for(int i = 1; i <= m; i++){
			scanf("%d%d", &u, &v);
			ver[u + n].pb(v);
			ver[v + n].pb(u);
		}
		build(1, 1, n);
		ans = 0;
		l = 1, r = n;
		while(l <= r){
			mid = l + r >> 1;
			if(check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

注意在每次 $check$ 的时候只有 $1\sim n$ 会改变，所以初始化可以少一点。

---

## 作者：xujindong_ (赞：0)

类似 AT_arc069_d，二分答案后 2-SAT。有两类边：原图中 $(u,v)$ 连边 $\neg u\to v,\neg v\to u$，距离 $<mid$ 的两点 $u,v$ 连边 $u\to\neg v,v\to\neg u$。

考虑启动 Kosaraju，我们只需要快速遍历这个图。第一类边正常遍历，第二类边的遍历要用序列并查集维护，支持快速找到下一个未访问的点。$O(n\log^2n)$。

序列并查集可以做到线性。按 $w=64$ 分块，块间用并查集指向下一个没有全部访问的块，块内压进一个整数直接查。在 word-RAM model 中，`ctz`，`clz` 都是 $O(1)$ 的，事实上也确实很快。另外我们也默认 $w=\Omega(\log n)$，并查集的 $\log$ 就被除掉了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf1[2097152],*ip1=buf1,*ip2=buf1;
inline int getc(){
  return ip1==ip2&&(ip2=(ip1=buf1)+fread(buf1,1,2097152,stdin),ip1==ip2)?EOF:*ip1++;
}
template<typename T>void in(T&a){
  T ans=0;
  char c=getc();
  for(;c<'0'||c>'9';c=getc());
  for(;c>='0'&&c<='9';c=getc())ans=ans*10+c-'0';
  a=ans;
}
template<typename T,typename ...Args>void in(T&a,Args&...args){
  in(a),in(args...);
}
int t,n,m,f[3130],num[200005],st[200005],top,cc;
unsigned long long v[3130];
bool vis[200005];
vector<int>e[100005];
int find(int x){
  return ~f[x]?f[x]=find(f[x]):x;
}
int getnxt(int x){
  if(v[x>>6]>>(x&63))return x+__builtin_ctzll(v[x>>6]>>(x&63));
  else return x=find((x>>6)+1),x<<6|__builtin_ctzll(v[x]);
}
void del(int x){
  v[x>>6]-=1ull<<(x&63);
  if(!v[x>>6])f[find(x>>6)]=find((x>>6)+1);
}
bool merge(int u,int v){
  return u=find(u),v=find(v),u==v?0:(f[v]=u,1);
}
void dfs1(int pos,int mid){
  vis[pos]=1,del(pos);
  if(pos<=n){
    for(int i=getnxt(n+max(pos-mid+1,1));i<=n+min(pos+mid-1,n);i=getnxt(i+1))if(i!=n+pos)dfs1(i,mid);
  }
  else{
    for(int i=0;i<e[pos-n].size();i++)if(!vis[e[pos-n][i]])dfs1(e[pos-n][i],mid);
  }
  st[++top]=pos;
}
void dfs2(int pos,int mid){
  vis[pos]=1,del(pos),num[pos]=cc;
  if(pos>n){
    for(int i=getnxt(max(pos-n-mid+1,1));i<=min(pos-n+mid-1,n);i=getnxt(i+1))if(i!=pos-n)dfs2(i,mid);
  }
  else{
    for(int i=0;i<e[pos].size();i++)if(!vis[n+e[pos][i]])dfs2(n+e[pos][i],mid);
  }
}
bool check(int mid){
  top=cc=0;
  for(int i=0;i<=n>>5;i++)v[i]=f[i]=-1;
  for(int i=1;i<=2*n;i++)vis[i]=0;
  for(int i=1;i<=2*n;i++)if(!vis[i])dfs1(i,mid);
  for(int i=0;i<=n>>5;i++)v[i]=f[i]=-1;
  for(int i=1;i<=2*n;i++)vis[i]=0;
  for(int i=top;i>=1;i--)if(!vis[st[i]])cc++,dfs2(st[i],mid);
  for(int i=1;i<=n;i++)if(num[i]==num[n+i])return 0;
  return 1;
}
int main(){
  in(t);
  while(t--){
    in(n,m);
    for(int i=1,u,v;i<=m;i++)in(u,v),e[u].push_back(v),e[v].push_back(u);
    int l=1,r=n;
    while(l<r){
      int mid=(l+r+1)>>1;
      if(check(mid))l=mid;
      else r=mid-1;
    }
    cout<<l<<'\n';
    for(int i=1;i<=n;i++)e[i].clear();
  }
  return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
“最小”的“最大”，再结合题中条件所提示的单调性，可以二分最小编号差，记作 $p$。

得到 $p$ 后，结合其定义知，$\forall1\leqslant i\leqslant n$，若取 $i$，则 $[i-p+1,i+p-1]$ 的点均不可取；又由点覆盖的定义，$\forall(u,v)\in E$，若 $u$ 不取，则 $v$ 必取，同理，$v$ 不取则 $u$ 必取。

上述两则可认为是 $\texttt{2-SAT}$ 问题中的逻辑关系。于是建图、跑强连通分量，即可判断可行性。**但是**，其中的区间连边需要用线段树优化建图，而且只需要入树。

### 代码
```cpp
//......
struct segment_tree {
	struct node {int ls, rs;}s[maxn * 4 + 5];
	int rt, size;
	int newnode() {return s[++size] = {0,0}, size;}
	#define l(k) s[k].ls
	#define r(k) s[k].rs
	void link(int &k, int f, int sl, int sr, int ql, int qr, int dot, int mode)//1:向区间连 0:向点连
	{
		if(!k)
		{
			k = newnode();
			if(f) add(f + n, k + n);
		}
		if(ql <= sl && sr <= qr) return mode? add(dot, k + n): add(k + n, dot);
		int mid = sl + sr >> 1;
		if(ql <= mid) link(l(k), k, sl, mid, ql, qr, dot, mode);
		if(qr > mid) link(r(k), k, mid + 1, sr, ql, qr, dot, mode);
	}
	int query(int k, int sl, int sr, int q)
	{
		if(!k) return 0;
		if(sl == sr) return id[k + n];
		int mid = sl + sr >> 1;
		return q <= mid? query(l(k), sl, mid, q): query(r(k), mid + 1, sr, q);
	}
	#undef l
	#undef r
}tree;//入树
void init(int mid)//重新建图
{
	for(int i = 1; i <= n + tree.size; i++) g[i].clear(), dfn[i] = low[i] = instack[i] = 0;
	tree.size = tree.rt = scc = 0;
	for(int i = 1; i <= m; i++)
		tree.link(tree.rt, 0, 1, n, u[i], u[i], v[i], 0),
		tree.link(tree.rt, 0, 1, n, v[i], v[i], u[i], 0);
	for(int i = 1; i <= n; i++)
	{
		if(i > 1) tree.link(tree.rt, 0, 1, n, max(1, i - mid + 1), i - 1, i, 1);
		if(i < n) tree.link(tree.rt, 0, 1, n, i + 1, min(i + mid - 1, n), i, 1);
	}
}
void tarjan(int k)
{
	dfn[k] = low[k] = ++cnt;
	instack[k] = true;
	s.push(k);
	for(int i : g[k])
	{
		if(!dfn[i]) tarjan(i), low[k] = min(low[k], low[i]);
		else if(instack[i]) low[k] = min(low[k], dfn[i]);
	}
	if(dfn[k] == low[k])
	{
		id[k] = ++scc;
		while(s.top() != k)
		{
			id[s.top()] = scc;
			instack[s.top()] = false;
			s.pop();
		}
		instack[k] = false;
		s.pop();
	}
}
bool check(int mid)
{
	init(mid);
	for(int i = 1; i <= n + tree.size; i++) id[i] = 0;
	for(int i = 1; i <= n + tree.size; i++) if(!dfn[i]) cnt = 0, tarjan(i);
	for(int i = 1; i <= n; i++)
		if(id[i] == tree.query(tree.rt, 1, n, i))
			return false;
	return true;
}
int main()
{
	T = read();
	while(T--)
	{
		n = read(), m = read();
		for(int i = 1; i <= m; i++) u[i] = read(), v[i] = read();
		int l = 0, r = n, res = false;
		while(l < r)
		{
			int mid = l + r + 1 >> 1;
			if(check(mid)) l = mid;
			else r = mid - 1;
		}
		write(l), IO::ptchar('\n');
	}
	IO::flush();
	return 0;
}
```

---

