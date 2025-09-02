# Timofey and Black-White Tree

## 题目描述

Timofey came to a famous summer school and found a tree on $ n $ vertices. A tree is a connected undirected graph without cycles.

Every vertex of this tree, except $ c_0 $ , is colored white. The vertex $ c_0 $ is colored black.

Timofey wants to color all the vertices of this tree in black. To do this, he performs $ n - 1 $ operations. During the $ i $ -th operation, he selects the vertex $ c_i $ , which is currently white, and paints it black.

Let's call the positivity of tree the minimum distance between all pairs of different black vertices in it. The distance between the vertices $ v $ and $ u $ is the number of edges on the path from $ v $ to $ u $ .

After each operation, Timofey wants to know the positivity of the current tree.

## 说明/提示

In the first testcase, after the second operation, the tree looks like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1790F/a32165e192e2b6f9339d786991ed5f6c93b66d14.png)

The distance between vertices $ 1 $ and $ 6 $ is $ 3 $ , the distance between vertices $ 4 $ and $ 6 $ is $ 3 $ , the distance between vertices $ 1 $ and $ 4 $ is $ 2 $ . The positivity of this tree is equal to the minimum of these distances. It equals $ 2 $ .

In the third testcase, after the fourth operation, the tree looks like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1790F/fd53da75cc7d2ed2c5c7b22e26af36d60231a33d.png)

The positivity of this tree is $ 2 $ .

## 样例 #1

### 输入

```
6
6 6
4 1 3 5 2
2 4
6 5
5 3
3 4
1 3
4 2
4 1 3
3 1
2 3
1 4
10 3
10 7 6 5 2 9 8 1 4
1 2
1 3
4 5
4 3
6 4
8 7
9 8
10 8
1 8
7 3
7 5 1 2 4 6
1 2
3 2
4 5
3 4
6 5
7 6
9 7
9 3 1 4 2 6 8 5
4 1
8 9
4 8
2 6
7 3
2 4
3 5
5 4
10 2
1 8 5 10 6 9 4 3 7
10 7
7 8
3 6
9 7
7 6
4 2
1 6
7 5
9 2```

### 输出

```
3 2 1 1 1 
3 1 1 
3 2 2 2 2 2 1 1 1 
4 2 2 1 1 1 
5 1 1 1 1 1 1 1 
4 3 2 2 1 1 1 1 1```

# 题解

## 作者：World_Creater (赞：17)

顶级诈骗题。

先放一个重要的结论：在将 $x$ 个点染黑后，答案（即两两黑色点对的最小距离）为 $\dfrac{n}{x}$ 级别（实际上界约为 $\dfrac{2n}{x}$）。

考虑一个很显然的暴力乱搞，令一个 $dis$ 数组 $dis_i$ 表示离节点 $i$最近的一个黑色节点。每把一个点染黑，便从这个点开始做一遍搜索更新 $dis$ 数组。若当前节点有更近的黑色节点，或当前节点离新加入的黑色节点的距离大于当前的答案，那么此时继续搜索没有意义，退出。

上述做法正确性显然，同时，这个看上去很假的东西复杂度是对的，为 $\mathcal{O}(n\sqrt{n})$，同时也是官方题解和 jiangly 的做法。

我们来分析一下复杂度：

首先在经过 $\sqrt{n}$ 次操作后，答案不会超过 $\dfrac{n}{\sqrt{n}}=\sqrt{n}$，因此所有**有意义**的 $dis_i$ 的值都不会超过 $\sqrt{n}$，在我们上述的操作过程中，$dis_i$ 显然是单调不增的，因此在这之后，每个 $dis_i$ 显然也只会被更新 $\sqrt{n}$ 次，因此后面的操作总复杂度是 $\mathcal{O}(n\sqrt{n})$ 的。而前 $\sqrt{n}$ 操作中，即使每次操作都满打满算单次复杂度 $\mathcal{O}(n)$，那么 $\sqrt{n}$ 次操作总复杂度也不过是 $\mathcal{O}(n\sqrt{n})$ 的。

因此该算法的复杂度是 $\mathcal{O}(n\sqrt{n})$ 的，可以通过本题，如果你超时了请尝试将搜索边界写的紧一点。

以上算法还能继续优化。

每次操作我们都进行一遍搜索的开销太大，我们考虑只进行**向上更新**，即对于每一个节点，我们一步步跳父亲并更新答案。

这个的正确性看上去不太显然，因为在加入节点时，其子树内的节点是否会被计算到？

答案是会，因为当其子树内部的点存在黑点时，在其向上更新的过程中，也会将这个点计算一遍答案，因此不会出现正确性上的问题。

至于复杂度，由于我们向上跳节点的次数不会超过当前答案（超过了一定不优），因此总复杂度为 $\mathcal{O}(\sum_{i=1}^{n}ans_i)$，其中 $ans_i$ 为加入第 $i$ 个节点时的答案，初始黑点视为第一个节点。而我们知道 $ans_i\leq \dfrac{n}{i}$，因此总复杂度为 $\mathcal{O}(\sum_{i=1}^{n}\dfrac{n}{i})$，这是一个经典的调和级数形式，因此复杂度为 $\mathcal{O}(n\log n)$，本做法也是 tourist 的做法。

还有很多做法，比如~~大冤种~~点分树做法，与 [CF342E](https://www.luogu.com.cn/problem/CF342E) 类似，不多展开，~~也是我赛时被诈骗写的做法~~。

不过个人来看，本题不能完全算与上题重题，因为巧妙利用答案的上界解题思路是这题有而上题没有的。

$\mathcal{O}(n\sqrt{n})$ 实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,ans,nxt[400005],head[200005],go[400005],k,dis[200005],a[200005];
void add(int u,int v)
{
	nxt[++k]=head[u];
	head[u]=k;
	go[k]=v;
}
void bfs(int s)
{
	dis[s]=0;
	queue<int> q;
	q.emplace(s);	
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(dis[x]>=ans) break ;
		for(int i=head[x];i;i=nxt[i])
		{
			int g=go[i];
			if(dis[g]<=dis[x]+1) continue ;
			dis[g]=dis[x]+1;
			q.emplace(g);
		}
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		fill(dis+1,dis+1+n,n+1);
		fill(head+1,head+1+n,0);
		k=0;
		ans=n+1;
		for(int i=1;i<n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		bfs(s);
		for(int i=1;i<n;i++)
		{
			ans=min(ans,dis[a[i]]);
			bfs(a[i]);
			cout<<ans<<" ";
		}
		cout<<"\n";
	}
}
```

$\mathcal{O}(n\log n)$ 实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,ans,nxt[400005],head[200005],go[400005],k,dis[200005],a[200005],f[200005];
void add(int u,int v)
{
	nxt[++k]=head[u];
	head[u]=k;
	go[k]=v;
}
void add(int x)
{
	int d=0,p=x;
	while(p&&d<ans)
	{
		ans=min(ans,dis[p]+d);
		dis[p]=min(dis[p],d);
		p=f[p];
		d++;
	}
}
void dfs(int x,int fa)
{
	f[x]=fa;
	for(int i=head[x];i;i=nxt[i])
	{
		int g=go[i];
		if(g!=fa) dfs(g,x);
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		fill(dis+1,dis+1+n,n+1);
		fill(head+1,head+1+n,0);
		k=0;
		ans=n+1;
		for(int i=1;i<n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		add(s);
		for(int i=1;i<n;i++)
		{
			ans=min(ans,dis[a[i]]);
			add(a[i]);
			cout<<ans<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：Kazeno_Akina (赞：3)

看到这道题是在同学的平衡复杂度分享课件里。

下面将详细叙述我是怎么迅速获 ~~猜~~ 得正解的以及正解的内容。

### $\texttt{part 01}$

首先你考虑暴力应该怎么写。

根据题意你在每次染黑某个点的时候，当前这个点是 $c_{k}$，那么直接找 $res = \min\limits_{i=0}^{k-1} dis(c_{i},c_{k})$ 然后用这个结果更新一下 $ans$ 就好。

考虑这东西复杂度是啥。求 $res$ 的复杂度取决于你求它用的方法。首先由于树的边权都是 $1$ 所以 dij 和 spfa 之类的肯定是劣的，你考虑搜索。

事实上你用深搜和广搜的第一个点的最劣复杂度都是 $O(n)$，但是广搜显然在染了很多个点之后复杂度更优，因此我们考虑广搜。

### $\texttt{part 02}$

考虑这东西怎么优化。

广搜本身你可以加个限制，即搜索时如果距离超过了当前答案就停止。

此时你想起来一个很典的结论：在一棵 $n$ 个点的树上，随便选 $i$ 个点，它们之间的最短距离是 $O(\dfrac{n}{i})$ 级别。于是你觉得你写的已经非常优。

但是很容易就有一个数据可以把你卡掉了。考虑一个单层菊花，$ans$ 一直是 $2$，然后你就寄了。

我们来继续思考怎么优化。

### $\texttt{part 03}$

你发现其实有一些点的搜索没有意义。如果你目前搜到的点距离刚染黑的点的距离大于等于到原来某个黑点的距离，那这一枝的搜索接下去就是没有意义的，原因是你更新不了任何一个点的 dis（也就是到最近的黑点的距离）。

于是你不妨开一个 dis 数组，然后搜索的时候顺便把 dis 改一下即可。复杂度为 $O(n \sqrt{n})$。原因是前面的 $\sqrt{n}$ 个点在搜索时复杂度至多为 $O(n \sqrt{n})$，而后面的点搜索的时候更新 dis 至多更新 $O(n \sqrt{n})$ 次（根据上面那个非常典的结论，有意义的 dis 在后半段过程中至多为 $\sqrt{n}$，每次更新一个 dis 那你的复杂度就对了）。

你获得了正解。

### $\texttt{code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=0x3f3f3f3f;
int t,n,nw,ans,c[N],dis[N];
bitset<N> clr,vis;
vector<int> hvvis,ch[N];//hvvis的作用是记录哪些点被vis过。如果每次都reset你的复杂度就假了。
inline int bfs(int p){
    queue<int> pnt;
    pnt.push(p),dis[p]=0;
    while(!pnt.empty()){
        nw=pnt.front(),pnt.pop();
        vis[nw]=1,hvvis.push_back(nw);
        for(int i=0;i<ch[nw].size();++i){
            if(!vis[ch[nw][i]]){
                if(clr[ch[nw][i]]) return dis[nw]+1;
                if(dis[ch[nw][i]]>dis[nw]+1&&dis[nw]+1<ans) dis[ch[nw][i]]=dis[nw]+1,pnt.push(ch[nw][i]);
                else continue;
            }
        }
    }
    return 0;
}
inline void cln(){
    for(int i=0;i<hvvis.size();++i) vis[hvvis[i]]=0;
    hvvis.clear();
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n,ans=inf;
        clr.reset(),memset(dis,0x3f,sizeof(dis));
        for(int i=1;i<=n;++i) cin >> c[i],ch[i].clear();
        for(int i=1,u,v;i<n;++i) cin >> u >> v,ch[u].push_back(v),ch[v].push_back(u);
        cln(),clr[c[1]]=1,bfs(c[1]);
        for(int i=2;i<=n;++i) ans=min(ans,dis[c[i]]),cout << ans << ' ',cln(),clr[c[i]]=1,bfs(c[i]);
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：Arghariza (赞：2)

为啥都带根号？为啥都带根号？为啥都带根号？

给一个 $O(n\log n)$ 的做法。

考虑如果维护的是最远距离，可以直接用线段树维护直径端点；但现在我们求的是最近距离，于是考虑静态 Top Tree。

我们可以根据 Top Tree 的性质得到一个更加具有可扩展性的做法：

对于每一个簇，维护三个值：簇内部的最短距离及到两个界点的最短距离。信息的合并类似于最大子段和，只需要考虑将两条路径拼接起来即可。

这个做法同样支持动态删点。并且复杂度是 $O(n\log n)$ 的。

```cpp
// Problem: Timofey and Black-White Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1790F
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef vector<int> vi;
bool Mbe;

const int N = 2e5 + 5;
const int inf = 1e9;

int n, rt, tot;
int c[N], sz[N], fa[N], son[N];
vector<int> G[N];

struct P {
	int x, y, d, op, l, r, m;
	P () : l(inf), r(inf), m(inf) { }
	P (int _x, int _y, int _d, int _op, int _l, int _r, int _m) :
		x(_x), y(_y), d(_d), op(_op), l(_l), r(_r), m(_m) { }
};

struct S {
	int lc, rc, fa, sz; P vl;
	S () { }
	S (int _lc, int _rc, int _fa, int _sz, P _vl) :
		lc(_lc), rc(_rc), fa(_fa), sz(_sz), vl(_vl) { }
} t[N << 1];

#define ls(x) t[x].lc
#define rs(x) t[x].rc

P cp(const P &L, const P &R) {
	return P(L.x, R.y, L.d + R.d, 0, 
	min(L.l, L.d + R.l), min(R.r, R.d + L.r), 
	min(min(L.m, R.m), L.r + R.l));
}

P rk(const P &L, const P &R) {
	return P(L.x, L.y, L.d, 1,
	min(L.l, R.l), min(L.r, L.d + R.l), 
	min(min(L.m, R.m), L.l + R.l));
}

int bld(vi::iterator l, vi::iterator r, auto op) {
	if (l == r - 1) return *l;
	int sum = 0, cur = 0; auto mid = l + 1;
	for (auto i = l; i != r; i++) sum += t[*i].sz;
	for (auto i = l; i != r; i++) {
		cur += t[*i].sz;
		if (cur * 2 <= sum) mid = i + 1;
	}
	int L = bld(l, mid, op), R = bld(mid, r, op);
	t[++tot] = S(L, R, 0, t[L].sz + t[R].sz, op(t[L].vl, t[R].vl)), t[L].fa = t[R].fa = tot;
	return tot;
}

void dfs1(int u, int f) {
	fa[u] = f, sz[u] = 1;
	t[u] = S(0, 0, 0, 1, P(f, u, 1, -1, inf, inf, inf));
	for (int v : G[u]) {
		if (v == f) continue;
		dfs1(v, u), sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}

int dfs2(int u) {
	vi p = { u };
	while (son[u]) {
		vi q = { son[u] };
		for (int v : G[u]) 
			if (v != fa[u] && v != son[u]) q.eb(dfs2(v));
		p.eb(bld(q.begin(), q.end(), rk)), u = son[u];
	}
	return bld(p.begin(), p.end(), cp);
}

void solve() {
	cin >> n, tot = n;
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, G[u].eb(v), G[v].eb(u);
	dfs1(1, 0), rt = dfs2(1);
	for (int i = 1; i <= n; i++) {
		int u = c[i]; t[u].vl.l = 1, t[u].vl.r = 0;
		while (u = t[u].fa) t[u].vl = (!t[u].vl.op ? cp : rk)(t[ls(u)].vl, t[rs(u)].vl);
		if (i >= 2) cout << t[rt].vl.m << ' ';
	}
	cout << '\n';
	for (int i = 1; i <= tot; i++) t[i] = S();
	for (int i = 1; i <= n; i++) sz[i] = son[i] = fa[i] = 0, G[i].clear();
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：xxseven (赞：1)

大家好啊，我不会分析暴力复杂度，所以直接硬做并获得了 $O(n \log n)$ 的优秀复杂度。

首先，每添加一个黑点，我们希望知道它与**之前**所有黑点的最小距离，然后取前缀 $\min$ 即为答案。

一边修改一边询问并不好做，考虑 CDQ 分治，问题转化为每次给定树上一些黑点一些白点，求每个白点离最近黑点的距离。

如果只有一个这样的问题，我们可以一遍换根 DP 在 $O(n)$ 复杂度内解决。但现在我们有 $O(n)$ 个总规模为 $O(n \log n)$ 的问题，那么使用虚树处理。

现在直接做可以得到 $O(n \log^2 n)$ 的复杂度，一只 $\log$ 来自分治，一只 $\log $ 来自建立虚树时对点进行排序。

但实际上，我们可以使用更精细的实现消去建立虚树的 $\log$。

将分治过程改为后序遍历，那么当我们要排序 $[L,R]$ 内的点以构建虚树时，我们已经在处理子任务时，将 $[L,mid]$ 和 $[mid+1,R]$ 两个区间内的点分别排序了，直接归并即可。

最后的时间复杂度为 $O(n \log n)$。~~但是我懒得写了，所以~~下面给出 $O(n \log^2 n)$ 的实现。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;
int n,p[N],q[N],ans[N];
vector<int> f[N];

int siz[N],top[N],dfn[N],son[N],fa[N],dep[N],idx;
void dfs(int x,int y){
	siz[x]=1; dep[x]=dep[y]+1; fa[x]=y;
	for(int u:f[x]) {
		if(u==y) continue;
		dfs(u,x); siz[x]+=siz[u];
		if(siz[u]>siz[son[x]]) son[x]=u;
	}
}
void dfs2(int x,int y){
	top[x]=y; dfn[x]=++idx;
	if(son[x]) dfs2(son[x],y);
	for(int u:f[x]) if(!top[u]) dfs2(u,u);
}
int lca(int x,int y){
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int b[N<<1],tp;
vector<pair<int,int> > g[N];
void build(int L,int R){
	tp=0;
	for(int i=L;i<=R;++i) b[++tp]=p[i];
	sort(b+1,b+tp+1,[&](int x,int y){return dfn[x]<dfn[y];});
	int tmp=tp;
	for(int i=2;i<=tmp;++i) b[++tp]=lca(b[i],b[i-1]);
	sort(b+1,b+tp+1,[&](int x,int y){return dfn[x]<dfn[y];});
	tp=unique(b+1,b+tp+1)-b-1;
	for(int l,d,i=2;i<=tp;++i) {
		l=lca(b[i],b[i-1]);
		d=dep[b[i]]-dep[l];
		g[l].push_back({b[i],d});
	}
}
int dp[N],dp2[N];
vector<int> pre[N],suf[N];
void DP(int x,int lim){
	if(q[x]<=lim) dp[x]=0;
	else dp[x]=1e9;
	int m=g[x].size();
	pre[x].resize(m); suf[x].resize(m);
	
	for(int i=0;i<m;++i){
		auto e=g[x][i];
		int u=e.first,w=e.second;
		DP(u,lim);
		dp[x]=min(dp[x],dp[u]+w);
		pre[x][i]=suf[x][i]=dp[u]+w;
	}
	for(int i=1;i<m;++i) pre[x][i]=min(pre[x][i],pre[x][i-1]);
	for(int i=m-2;i>=0;--i) suf[x][i]=min(suf[x][i],suf[x][i+1]);
}
void DP2(int x,int lim) {
	
	int m=g[x].size();
	for(int i=0;i<m;++i){
		auto e=g[x][i];
		int u=e.first,w=e.second;
		dp2[u]=dp2[x]+w;
		if(i!=0) dp2[u]=min(dp2[u],pre[x][i-1]+w);
		if(i!=m-1) dp2[u]=min(dp2[u],suf[x][i+1]+w);
		if(q[x]<=lim) dp2[u]=w;
		DP2(u,lim);
	}
	if(q[x]>lim) ans[q[x]]=min({ans[q[x]],dp[x],dp2[x]});
	g[x].clear(); pre[x].clear(); suf[x].clear(); 
}

void cdq(int L,int R){
	if(L==R) return;
	int mid=L+R>>1;
	build(L,R); 
	dp2[b[1]]=1e9; DP(b[1],mid); DP2(b[1],mid);
	cdq(L,mid); cdq(mid+1,R);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--) {
		cin>>n;
		for(int i=1;i<=n;++i) {
			ans[i]=1e9; f[i].clear();
			siz[i]=son[i]=dfn[i]=top[i]=fa[i]=dep[i]=0;
		}
		
		for(int i=1;i<=n;++i) cin>>p[i],q[p[i]]=i;
		for(int x,y,i=1;i<n;++i) {
			cin>>x>>y;
			f[x].push_back(y);
			f[y].push_back(x);
		}
		idx=0; dfs(1,0); dfs2(1,1);
		cdq(1,n);
		for(int i=2;i<=n;++i) {
			ans[i]=min(ans[i],ans[i-1]);
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：Hisaishi_Kanade (赞：1)

太高明了吧这个题。

对于加入的第 $i$ 个黑点，答案上界 $\dfrac n i$。随便反证一波。假设存在 $i$ 个点，任意两个黑点之间距离都至少为 $1+\dfrac {n} {i}$（这样答案才会大于 $\dfrac n i$）。那么就可以找到一条长度为 $(\dfrac {n} i+1)\times i=n+i>n$ 的链。而这是不可能的。得证。

那么加入一个黑点后可能影响答案的点的距离不超过 $\dfrac n i$。

而且，容易证明对于输出的 $ans_i$，显然，必然有 $ans_i\ge ans_{i+1}$。

所以我们只需要广搜扩展到 $\min(ans_{i-1},\dfrac n i)$ 之内即可，在这个范围内找黑色点然后更新答案。

正确性显然。证明时间复杂度。

+ 在 $i\le \sqrt n$ 时，最坏的显然是几乎全扩展了一遍，复杂度当成 $O(n\sqrt n)$。

+ 当 $i> \sqrt n$ 时，此时扩展的距离最多是 $\sqrt n$。设 $dis_i$ 表示 $i$ 到最近黑色点的距离。那么 $\sum dis$ 显然是 $n\sqrt n$ 量级的。每次用一个新的点覆盖相当于把一些点的 $dis$ 减少一些。最后的覆盖次数也是 $n\sqrt n$ 级别。

所以总复杂度 $O(n\sqrt n)$。

```cpp
// LUOGU_RID: 122400920
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
using namespace std;
int t, n, i, ret, ans, s, u, v, sq;
const int N=2e5+5;
vector<int> e[N]; int c[N], dis[N], q[N];
inline void bfs(int id)
{
	int l, r, lim=i>sq? min(ans, n/i): ans;
	dis[id]=0; q[l=r=1]=id;
	while(l<=r)
	{
		if(dis[q[l]]>lim) break;
		for(auto nxt: e[q[l]])
		{
			if(dis[nxt]>dis[q[l]]+1)
			{
				dis[nxt]=dis[q[l]]+1;
				q[++r]=nxt;
			}
		}
		++l;
	}
}
int main()
{
	scanf("%d", &t); while(t--)
	{
		scanf("%d %d", &n, &s); sq=sqrt(n)+0.9; rep(i, 1, n) e[i].clear(); rep(i, 1, n) dis[i]=2e9; dis[s]=0;
		rep(i, 2, n) scanf("%d", c+i); rep(i, 2, n) {scanf("%d %d", &u, &v); e[u].emplace_back(v); e[v].emplace_back(u);}
		ans=2e9; i=0; bfs(s);
//		int j; rep(j, 1, n) printf("%d ", dis[i]); puts("");
		rep(i, 2, n)
		{
//			printf("%d %d %d\n", ans, dis[c[i]], min(ans, dis[c[i]]));
			ans=min(ans, dis[c[i]]);
			bfs(c[i]);
			printf("%d ", ans);
		} puts("");
	}
}

```

---

## 作者：苏联小渣 (赞：1)

这个题虽然好像有码量很小的做法，但是我们可以用一种更为好想且非常模板的方法，点分治。

我们记录 $p_x$ 表示 $x$ 是第几个变黑的，然后对于每个 $x$，求出一个最小的 $dis(x,y)$ 满足 $p_y<p_x$。然后，取一个前缀 min 就能得到答案。

这种树上路径问题，显然是可以通过点分治解决的。具体来说，每次找到树的重心作为根节点 $rt$。对于 $rt$ 的所有儿子 $u$，先递归 $u$ 的子树，对于 $u$ 子树里面的所有点 $v$，记录 $dis_v$ 表示 $rt$ 到 $v$ 的距离。递归完之后，我们对于这些 $v$，查找 $p_x \in [1,p_v-1]$ 中 $dis_x$ 的最小值，并将 $ans_{p_v} \gets \min(ans_{p_v},dis_x+dis_v)$。这个前缀 min 用一个树状数组就行了。然后对所有儿子的子树，找到其重心再递归即可。然后这道题就做完了。时间复杂度 $O(n \log^2 n)$。

注意一下以下细节：

- 由于根据传统的点分治，我们查找到的 $x$ 一定是比 $v$ 先遍历到的，而后遍历到的也有可能产生答案，所以还要把存边的顺序反过来再跑一次点分治（链式前向星存图相当于把链表倒置，用 vector 存图会更方便一点，变成从尾到头遍历就好了）

- 根节点 $rt$ 也要加入树状数组中，它的 $dis_{rt}=0$。

- 注意对树状数组清空的细节。

~~好像理论复杂度还比官方题解优那么一点。~~

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, p, x, y, tsiz, mn, rt, a[200010], rev[200010], h[200010], siz[200010], dis[200010], vis[200010], ans[200010];
struct node{
	int x, y, next;
}d[400010];
struct BIT{
	int d[200010];
	void clear(int p){
		for (; p<=n; p+=p&-p) d[p] = 1e9 + 7;
	}
	void add(int p, int x){
		for (; p<=n; p+=p&-p) d[p] = min(d[p], x);
	}
	int query(int p){
		int ret = 1e9;
		for (; p; p-=p&-p) ret = min(ret, d[p]);
		return ret;
	}
}S;
vector <int> del, cun;
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
void dfs1(int x, int fa){
	siz[x] = 1;
	int mx = 0;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa || vis[y]) continue;
		dfs1(y, x);
		mx = max(mx, siz[y]);
		siz[x] += siz[y];
	}
	mx = max(mx, tsiz - siz[x]);
	if (mx < mn) mn = mx, rt = x;
}
void dfs2(int x, int fa){
	cun.push_back(x);
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa || vis[y]) continue;
		dis[y] = dis[x] + 1;
		dfs2(y, x);
	}
}
void solve(int x, int fa){
	vis[x] = 1, dis[x] = 0;
	del.clear();
	S.add(rev[x], 0);
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa || vis[y]) continue;
		dis[y] = 1;
		cun.clear();
		dfs2(y, x);
		for (int j=0; j<cun.size(); j++){
			int now = cun[j];
			ans[rev[now]] = min(ans[rev[now]], dis[now] + S.query(rev[now]));
		}
		for (int j=0; j<cun.size(); j++){
			int now = cun[j];
			del.push_back(rev[now]);
			S.add(rev[now], dis[now]);
		}
	}
	ans[rev[rt]] = min(ans[rev[rt]], S.query(rev[rt]-1));
	for (int i=0; i<del.size(); i++){
		S.clear(del[i]);
	}
	S.clear(rev[x]);
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa || vis[y]) continue;
		tsiz = siz[y], mn = 1e9, rt = 0;
		dfs1(y, x);
		dfs1(rt, 0);
		solve(rt, 0);
	}
}
int main(){
	scanf ("%d", &t);
	while (t --){
		p = 0;
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			rev[a[i]] = i;
			h[i] = vis[i] = 0;
			ans[i] = S.d[i] = 1e9 + 7;
		}
		for (int i=1; i<n; i++){
			scanf ("%d%d", &x, &y);
			add(x, y); add(y, x);
		}
		mn = 1e9, rt = 0, tsiz = n;
		dfs1(1, 0);
		dfs1(rt, 0);
		solve(rt, 0);
		for (int i=1; i<=n; i++){
			cun.clear();
			vis[i] = 0, S.d[i] = 1e9 + 7;
			for (int j=h[i]; j; j=d[j].next){
				cun.push_back(d[j].y);
			}
			int tot = cun.size() - 1;
			for (int j=h[i], k=0; j; j=d[j].next, k++){
				d[j].y = cun[tot-k];
			}
		}
		mn = 1e9, rt = 0, tsiz = n;
		dfs1(1, 0);
		dfs1(rt, 0);
		solve(rt, 0);
		for (int i=3; i<=n; i++){
			ans[i] = min(ans[i], ans[i-1]);
		}
		for (int i=2; i<=n; i++){
			printf ("%d ", ans[i]);
		}
		puts ("");
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

还可以的。

就你发现这个答案是不升的，然后你又因为有好多点之间的路径什么的，你肯定会猜答案上界或者根分这样的东西。

呐，显然我们可以把上一次的答案 $x$ 作为上界，然后因为如果要影响答案那么更短的路径一端肯定是新加的点，那我们从这个点搜 $x-1$ 层就好了。

那这个东西你分析平衡一下发现其实就是 $O(n\sqrt n)$，然后就能过了。

---

## 作者：GenesisCrystal (赞：0)

## 思路
令 $dis_i$ 为离 $i$ 最近的黑点距离， $ans$ 是距离最近的一对黑点距离， 我们可以发现， 每次 $i \gets i + 1$ 后 $ans$ 的更新只会与 $dis_{c_i}$ 有关， 因为 $c_i$ 是新的黑点， 然后再从 $c_i$ 来一次 BFS 更新 $dis_i$ 即可。

更详细的在注释。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int KMaxN = 2e5 + 1;

int n, c[KMaxN], t, u, v, dis[KMaxN]/* 离 i 最近的黑点距离 */, ans = 1e9;
vector<int> g[KMaxN]; // 存边

void bfs(int s) { // 从 s 做一次 BFS 更新
  dis[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    if (dis[t] >= ans) { // 优化：当当前点 i 最近黑点的距离大于最小值 ans, 可以直接不用搜了
      break;
    }
    for (int i : g[t]) {
      if (dis[i] <= dis[t] + 1) {
        continue;
      }
      dis[i] = dis[t] + 1; // 更新
      q.push(i);
    }
  }
}

int main() {
  for (cin >> t; t; t-- , ans = 1e9) { // t 次询问
    cin >> n >> c[0];
    fill(dis + 1 , dis + n + 1 , 1e9);
    for (int i = 1; i < n; i++) {
      g[i].clear();
      cin >> c[i];
    }
    g[n].clear();
    for (int i = 1; i < n; i++) {
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    bfs(c[0]); // 先对 c[0] 做一次 BFS
    for (int i = 1; i < n; i++) {
      ans = min(ans, dis[c[i]]); // 只有 dis[c[i]] 对 ans 有影响
      cout << ans << " ";
      bfs(c[i]); // 更新 dis
    }
    cout << "\n";
  }
  return 0;
}

```

---

## 作者：小木虫 (赞：0)

### Preface  
非常妙的一道“根号分治”。
### Problem  
给你一个 $n$ 个节点的树 $T$，每一次染黑一个点，每次操作后问你任选两个黑点之后这两个黑点的最短距离。  
$2\leq n\leq 2\times 10^5$。  
### Solution  
有一个很厉害的结论，即随便在树上撒 $\sqrt{n}$ 个点，这些点之间的最短距离不超过 $\sqrt{n}$。  
正确性是显然的，其在链上是成立的，而树比链要更紧。  
你考虑对于每个点 $u$ 记录离其最近的黑点和它的距离 $f_u$。  

显然，经过 $\sqrt{n}$ 次操作之后，$f$ 只有 $\sqrt{n}$ 以下的取值有意义，如果一个点更新上的值超过这个值我们就可以选择不去更新。  

然后你每次染黑之后暴力进行 dfs，每个点的 $f$ 只会被更新至多 $\sqrt{n}$ 次，然后你考虑一个点被更新之后还要继续 dfs，肯定要枚举其相邻点，所以这么做的复杂度是 $O(\sum_{u\in T}deg_u\times \sqrt{n})=O(n\sqrt{n})$。  

常数较大，实现需要小心。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,u,v,c[N],vis[N],f[N],res;
vector <int> edge[N];
void dfs(int u,int fa){
	if(f[u]>=res)return;
	if(vis[u])res=min(res,f[u]);
	for(auto v:edge[u]){
		if(v==fa)continue;
		if(f[u]+1<f[v])f[v]=f[u]+1,dfs(v,u);
		else res=min(res,f[u]+1+f[v]);
	}
}
void solve(){
	cin>>n>>c[0];res=n;
	for(int i=1;i<=n;i++)vis[i]=0,f[i]=n;
	for(int i=1;i<=n;i++)
		edge[i].clear();
	for(int i=1;i<n;i++)
		cin>>c[i];
	for(int i=1;i<n;i++){
		cin>>u>>v;
		edge[u].emplace_back(v);
		edge[v].emplace_back(u); 
	}f[c[0]]=0;dfs(c[0],0);vis[c[0]]=1;
	for(int i=1;i<n;i++){
		f[c[i]]=0;
		dfs(c[i],0);
		vis[c[i]]=1;
		cout<<res<<" ";
	}cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}



```


---

## 作者：氧少Kevin (赞：0)

# CF1790F - Timofey and Black-White Tree
- https://www.luogu.com.cn/problem/CF1790F
- 根号分块、暴力

## 题意
给出一棵 $n(2\leq n \leq 2\cdot 10^5)$ 个节点的树，最初 $c_0$ 号节点是黑色，其余均为白色。

给定操作序列 $c_1,c_2,\cdots,c_{n-1}$，第 $i$ 次操作表示将 $c_i$ 号节点染黑。每次操作后，输出距离最近的两个黑点间的距离。

**本题时限 4s。**

## 思路

考虑暴力。

最坏的情况是：染黑的前 $\sqrt {n}$ 个点均匀分布，各个点的距离为近似 $\sqrt{n}$，这一步骤复杂度是 $O(n \sqrt n)$。

接下来染黑的点，他到最近的其他点的距离一定 $<\sqrt n$。每次 BFS 时，控制入队的次数不超过上一次的答案（超过一定不会对答案产生更新），因此 BFS 的次数 $<\sqrt n$ 次，这一步骤复杂度也是 $O(n \sqrt n)$。

因此，复杂度是 $O(n \sqrt n)$。

## 实现

需要注意的是：上面所讲的情况是特殊的极端情况。

实际情况可能是：某两个点距离非常近，某两个点距离非常远。每次 BFS 时，控制入队的次数即可。


---

## 作者：Retired_lvmao (赞：0)

### 题意

给定一棵树，每次染黑一个点，在每次操作后，你需要输出最近的一对黑点的距离。

$n\leq 2\times 10^5$

### 题解

**该做法并不是官方题解给出的正解，只是能跑过此题。**

观察到答案在 $\sqrt{n}$ 次操作之后，就会变化到 $\sqrt{n}$ 以下，因此，可以观察到答案的变化次数不会超过 $2\sqrt{n}$ 。也就是说，答案实际上由至多 $2\sqrt{n}$ 个连续段组成。

由于对于任意一次操作后的答案，我们都可以简单的 $O(n)$ DFS 求出，因此，在知道一个连续段的左端点的情况下，我们可以二分连续段的右端点的位置。

但是这样朴素实现是 $O(n\sqrt{n} \log n)$ 的，会直接 TLE on test 6。考虑优化。

观察到对于每个连续段二分的时候，每次的右端点并不需要从 $n$ 开始，可以通过之前询问的结果，将右端点的范围缩小，这样子会跑的快很多。然而，这个做法仍旧不足以通过，会 TLE on test 32，直接 FST。

考虑进一步优化。在上文的做法中，我们会进行非常多次的 DFS 操作。而观察到每次 DFS 的时候，树的形态都是不变的。也就是说，我们可以预处理 DFS 序之后，按照 DFS 序从大到小，用循环来访问每一个节点。由于循环的常数远远小于递归，因此该做法可以通过，甚至只需要跑 $1$s 左右。

### 代码


```
#include<bits/stdc++.h>
using namespace std;
#define min min_
int min(int x,int y)
{
	return x<y?x:y;
}
int n;
int c[200010],cnt=0,ti[200010],tot;
int dp[200010],f[200010],sub[200010],id[200010];
int ans=1e9,lim,rt,dfn[200010],g[200010];
mt19937 rng(time(0)); 
struct node
{
	int nxt,to;
};
node e[400010];
int hd[200010];
void add(int x,int y)
{
	e[++cnt]=(node){hd[x],y};
	hd[x]=cnt;
}
void init(int x,int pre)
{
	dp[x]=dp[pre]+1;dfn[x]=++tot;id[tot]=x;
	sub[x]=ti[x];
	for(int i=hd[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y!=pre)
			init(y,x),sub[x]=min(sub[x],sub[y]);
	}
} 
int vis[200010];
int solve(int key)
{
	if(vis[key]!=-1)
		return vis[key];
	ans=1e9;
	for(int z=n;z>=1;z--)
	{
		int x=id[z];
		int mn=1e9;
		if(ti[x]<=key)
			mn=dp[x];
		for(int i=hd[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(dfn[y]<dfn[x])
				continue;
			int tt=g[y];
			ans=min(ans,mn+tt-2*dp[x]);
			mn=min(mn,tt);
		}
		g[x]=mn;
	}
	return vis[key]=ans;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ans=1e9;cnt=0;
		scanf("%d",&n);rt=1;
		for(int i=1;i<=n;i++)
			scanf("%d",&c[i]),f[i]=-1,ti[c[i]]=i,vis[i]=-1,hd[i]=0;
		for(int i=2;i<=n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		tot=0;
		init(rt,0);
		int lst=solve(2),tagl=3;f[2]=lst;
		int mem=n;
		set<int> s;
		while(1)
		{
			tot++;
			if(lst==1)
				break;
			int l=tagl,r=mem,ans=n;
			while(l<=r)
			{
				int mid=(l+r)/2;
				s.insert(mid);
				if(solve(mid)==lst)
					l=mid+1;
				else
					r=mid-1,ans=mid;
			}
			f[ans]=solve(ans);
			while(s.size()&&solve(*s.begin())>=f[ans])
				s.erase(*s.begin());
			if(s.size())
				mem=(*s.begin());
			else
				mem=n;
			lst=f[ans];tagl=ans+1;
		}
		for(int i=2;i<=n;i++)
			f[i]=(f[i]==-1?f[i-1]:f[i]),printf("%d ",f[i]);
		puts("");
	}
}
```

---

