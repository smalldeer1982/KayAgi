# Tree Pruning

## 题目描述

[t+pazolite, ginkiha, Hommarju - Paved Garden](https://soundcloud.com/fractalex-gd/ginkiha-paved-garden-little)

⠀



You are given a tree with $ n $ nodes, rooted at node $ 1 $ . In this problem, a leaf is a non-root node with degree $ 1 $ .

In one operation, you can remove a leaf and the edge adjacent to it (possibly, new leaves appear). What is the minimum number of operations that you have to perform to get a tree, also rooted at node $ 1 $ , where all the leaves are at the same distance from the root?

## 说明/提示

In the first two examples, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2018C/46789adad3b93ca642b297f7ca0ca574c7f98f60.png)In the first example, by removing edges $ (1, 3) $ and $ (2, 5) $ , the resulting tree has all leaves (nodes $ 6 $ and $ 7 $ ) at the same distance from the root (node $ 1 $ ), which is $ 3 $ . The answer is $ 2 $ , as it is the minimum number of edges that need to be removed to achieve the goal.

In the second example, removing edges $ (1, 4) $ and $ (5, 7) $ results in a tree where all leaves (nodes $ 4 $ and $ 5 $ ) are at the same distance from the root (node $ 1 $ ), which is $ 2 $ .

## 样例 #1

### 输入

```
3
7
1 2
1 3
2 4
2 5
4 6
4 7
7
1 2
1 3
1 4
2 5
3 6
5 7
15
12 9
1 6
6 14
9 11
8 7
3 5
13 5
6 10
13 15
13 6
14 12
7 2
8 1
1 4```

### 输出

```
2
2
5```

# 题解

## 作者：_xm_ (赞：7)

代码附有详细的注释，建议题解和代码相互对应着看。

默认根节点 $1$ 深度为 $0$，假设**当前**维护的树满足叶子的深度都为 $dep$，不难发现从深度 $dep$ 转移到深度 $dep+1$ 是一个 bfs 的过程。

![](https://s21.ax1x.com/2024/09/28/pA1prr9.jpg)

考虑维护 bfs 每一层的点，转移时遇到没有儿子的点（如图右从点 $4$ 转移到下一层）就删去，且递归地考虑父亲是否该删除（如图左从点 $5$ 转移到下一层，只删去点 $5$ 而不删去还有另外儿子的点 $2$，假如 $2, 5$ 中间还有若干点也将一并删除）。

遍历所有的深度，得到合法树的最大点数即可求出最小删点次数。

```cpp
// by xm
// 2024.9.27
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ll N = 5e5 + 5, Inf = 1e18;

ll T = 1, n, fa[N], de[N]; // fa:父亲, de:度数(无向图)
vector<ll> G[N];

void solution() {
	cin >> n;
	for(int i = 1; i <= n; i++) de[i] = fa[i] = 0, G[i].clear();
	for(int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
		de[u]++, de[v]++;
	}
	vector<ll> lst = {1}; // bfs的上一层, 初始 {1}
	ll ans = 0, tot = 1; // ans:最大点数, tot:当前树点数
	for(ll dep = 1; dep <= n; dep++) {
		vector<ll> q; // bfs当前层
		for(auto u : lst) {
			for(auto v : G[u]) { // bfs出lst的下一层
				if(v == fa[u]) continue;
				fa[v] = u;
				q.push_back(v);
				tot++; // 点数+1
			}
			while(u != 1 && de[u] - 1 == 0) { // 非根节点的儿子个数等于度数-1
				de[fa[u]]--, de[u]--; // u没有儿子, 删掉(u, fa[u])
				tot--; // 点数-1
				u = fa[u]; // 递归处理fa[u], 要求删掉一条连续的链
			}
		}
		ans = max(ans, tot); // 最大点数
		lst = q; // 记录上一层
	}
	cout << n - ans << "\n"; // 最小删点次数
}

double ST, ED;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	ST = clock(); cin >> T; while(T--) solution(); ED = clock();
	cerr << 1000 * (ED - ST) / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
```

---

## 作者：TianTianChaoFang (赞：5)

# 分析

好像官方题解是反向求解的，这里提供一个正向求解的思路，即直接求出最后所有叶节点到根的距离相同为 $x$ 时需要删除的结点数 $ans_x$ 。

如果我们最后到根的相同距离为 $x$，那么答案有两个组成部分。

第一个部分，若到根距离为 $x$ 的结点是一个中间结点，也就是说这个结点还有子节点，那么直接把比这个点更深的子树都删掉即可。

第二个部分，对于每一个分枝，若这个分支的最深深度小于 $x$ ，那么这一整个分支都得删掉。因为这个分枝只要有剩余，它的叶节点到根的距离一定小于 $x$ 。只有被完全剪掉，才会不剩余叶节点，才会没有到根距离小于 $x$ 的叶节点。

因此，我们只需要处理出所有剪完后叶节点到根的距离的删减数，再所有答案取最小就行了，而这个过程，也只需要一次 **DFS** 就能完成。

对于第一个部分，只需要在 DFS 的过程维护一下**下方子树的大小**，在每一层加上所有下方子树大小即可。

对于第二个部分，对于每一个点，我们记录一下这个点所代表的子树的**最深深度**，那么想一下，是不是只要最后要保留的叶节点到根的距离大于这个结点的深度，这个结点就得被删掉。

所以，我们可以用 **差分数组** 来维护这一件事。
记 $mx_i$ 为结点 $i$ 的子树的最深深度，$z$ 数组是第二部分的答案数组的差分数组，因此每一个点对第二部分的答案数组贡献就是对 $z_{mx_i + 1} + 1$ 。

最后，把两部分的答案加一下就行了，然后对所有情况的答案取最小即可。

上代码！

# AC CODE

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf INT64_MAX
#define ull unsigned long long

using namespace std;

const int N = 6e5 + 9;
int d[N], k[N], sz[N], z[N];
//d：当前结点深度  k：保留的距离要减掉的结点数  sz：当前结点代表的子树大小  z：第二部分答案的差分数组
int mx[N];//当前结点最深深度
int dmx;

vector<int> g[N];

void dfs(int st, int pre)//st：当前结点  pre：父节点
{
	if(st != 1)d[st] = d[pre] + 1;
	dmx = max(dmx, d[st]);//求出整棵树的最深深度
	
	sz[st] = 1;
	
	if(g[st].size() == 1 && st != 1)
	{
		mx[st] = d[st];
	}
	 
	for(auto &i : g[st])
	{
		if(i == pre)continue;
		
		dfs(i, st);
		k[d[st]] += sz[i];//第一部分答案
		sz[st] += sz[i];
		mx[st] = max(mx[st], mx[i]);
	}
	
	if(st != 1)z[mx[st] + 1] ++;//给第二部分答案做贡献
}

void init(int n)
{
	for(int i = 1;i <= n + 10;i ++)
	{
		g[i].clear();
		k[i] = 0;
		sz[i] = 0;
		z[i] = 0;
		mx[i] = 0;
	}
	dmx = 0;
}

void solve()
{
	int n;cin >> n;
	
	init(n);
	
	for(int i = 1;i < n;i ++)
	{
		int u, v;cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	d[1] = 0;
	dfs(1, -1);
	
	for(int i = 1;i <= dmx;i ++)z[i] += z[i - 1];//差分数组前缀和求出第二部分的答案
	for(int i = 1;i <= dmx;i ++)k[i] += z[i];//两部分答案求和
	
	int ans = inf;
	
	for(int i = 1;i <= dmx;i ++)ans = min(ans, k[i]);
	
	cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int t = 1;cin >> t;
    while(t --)solve();

    return 0;
}

```

---

## 作者：Crazyouth (赞：4)

## 分析

~~为什么要写树剖啊。~~

首先枚举最终所有叶子所在的层数 $h$，显然对于所有大于 $h$ 层的节点需要全部删除，并且如果有某一个不到 $h$ 层的子树，该子树需要全部删除。记录一下每层的节点数，每个节点子树内的最大深度，以及它们分别的前缀和即可。

~~赛时本题唯一难点在于发现它不难。~~

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int dep[N],depcnt[N],mxdep[N],mxcnt[N],summx[N],h,sumdep[N];
vector<int> G[N];
void dfs(int u,int fa)
{
	depcnt[dep[u]]++;
	mxdep[u]=dep[u];
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		mxdep[u]=max(mxdep[u],mxdep[v]); 
	}
	mxcnt[mxdep[u]]++;
}
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) G[i].clear(),G[i].shrink_to_fit();
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++) dep[i]=mxdep[i]=depcnt[i]=mxcnt[i]=summx[i]=sumdep[i]=0;
	sumdep[n+1]=0;
	dfs(1,0);
	h=mxdep[1];
	for(int i=1;i<=h;i++) summx[i]=summx[i-1]+mxcnt[i];
	for(int i=h;i;i--) sumdep[i]=sumdep[i+1]+depcnt[i];
	int ans=1e9;
	for(int i=1;i<=h;i++) ans=min(ans,sumdep[i+1]+summx[i-1]);
	cout<<ans<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：Larryyu (赞：3)

## _Description_

给定一棵有 $n$ 个点的以 $1$ 为根的树，在此问题中，叶子节点被定义为非根的度数为一的点。

每次操作可以删去一个叶子节点及其相连的边，你需要求出最小的操作次数，使得操作后所有叶子节点到根节点的距离相同。

## _Solution_

考虑一条边什么情况下不会被删去。

对于 $(x,y)$ 这条边，设 $y$ 为深度较大的那个点，$z$ 为 $y$ 子树内深度最大的点，那么只要操作完后的叶子深度在 $[dep_y,dep_z]$ 范围内，那么这条边就不会被删去，对区间 $[dep_y,dep_z]$ 加 $1$ 即可。

最后叶子深度则为所有可能深度中被加次数最大的那个深度，答案为边数减去其被加的次数。

发现这是区间加，单点查询，你可以用你喜欢的数据结构维护，如线段树、树状数组、分块等。

代码用线段树实现，复杂度 $O(n\log n)$。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls x<<1
#define rs x<<1|1
int t;
int n,tot;
int head[1000010],dep[1000010];
struct edge{
	int to,next;
}e[1000010];
void add(int x,int y){
	e[++tot]=edge{y,head[x]};
	head[x]=tot;
}
struct tree{
	int sum;
}tr[2000020];
void build(int x,int l,int r){
	tr[x].sum=0;
	if(l==r) return ;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void update(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		tr[x].sum++;
		return ;
	}
	int mid=l+r>>1;
	if(L<=mid) update(ls,l,mid,L,R);
	if(R>=mid+1) update(rs,mid+1,r,L,R);
}
int query(int x,int l,int r,int k){
	if(l==r) return tr[x].sum;
	int mid=l+r>>1,ans=tr[x].sum;
	if(k<=mid) return ans+query(ls,l,mid,k);
	else return ans+query(rs,mid+1,r,k);
}
int dfs(int x,int fax){
	dep[x]=dep[fax]+1;
	int maxn=dep[x];
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y==fax) continue;
		int z=dfs(y,x);
		update(1,1,n,dep[x]+1,z);
		maxn=max(maxn,z);
	}
	return maxn;
}
void init(){
	tot=0;
	for(int i=1;i<=n;i++){
		head[i]=0;
	}
	build(1,1,n);
}
void solve(){
	cin>>n;
	init();
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	dfs(1,0);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,query(1,1,n,i));
	}
	cout<<n-1-ans<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Diaоsi (赞：2)

[Tree Pruning](https://codeforces.com/contest/2018/problem/C)

~~怎么没人写长剖呢~~

首先有一个显然的 DP，设 $f_{x,i}$ 表示使 $x$ 子树内的叶子节点深度都为 $i$ 所需要的最少操作次数。

发现第二维状态跟深度有关，可以用长链剖分优化转移。沿用重链剖分的定义，设儿子中子树深度最大的儿子为重儿子，否则为轻儿子。重儿子构成的链则称为长链。

不难发现对于任意一个节点 $x$ ，其所有轻儿子对应的长链深度都不会比 $x$ 所在长链的深度更大。记 $x$ 的重儿子为 $s_x$，将轻重儿子分开合并，合并重儿子时直接继承：

$$
\begin{aligned}
f_{x,i}\ &\leftarrow\ f_{s_x,i-1}\,,\quad i>1\\
f_{x,1}\ &\leftarrow\ \big|\mathrm{sub}(x)\big|-1
\end{aligned}
$$

其中 $\big|\mathrm{sub}(x)\big|$ 表示 $x$ 子树的大小。

合并轻儿子时将对应的深度相加，记儿子 $y$ 所在的长链深度为 $l$：

$$
\begin{aligned}
f_{x,i}\ &\leftarrow\ f_{x,i}+f_{y,i-1},\quad 1<i\leq l\\
f_{x,i}\ &\leftarrow\ f_{x,i}+|\mathrm{sub}(y)|,\quad l<i
\end{aligned}
$$

分析一下转移的时间复杂度，$s_x$ 的继承可以做到 $\mathcal{O}(1)$。$y$ 的转移分为两部分，第一部分的暴力转移的操作次数为 $y$ 子树的深度，同时对应着 $y$ 长链的深度。$y$ 所在的长链不会比 $s_x$ 延伸下去的长链更长，所以可以认为每条长链只会在链顶被合并一次。单次时间复杂度为 $\mathcal{O}(l)$，总时间复杂度为 $\mathcal{O}\big(\sum l\big)=\mathcal{O}(n)$。

第二部分的转移需要支持区间加，这部分可以用线段树维护，但是我们并不关心区间信息，所以直接在长链上打 tag 就可以了。由于每条长链上的节点在 DFS 序上都是连续的，直接对 DFS 做 DP 即可。

时间复杂度 $\mathcal{O}(n)$，代码非常好写，基本没有细节。


```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
int T,n,num,ans,d[N],f[N],ff[N],id[N],mx[N],sz[N],ed[N],son[N],tag[N];
vector<int> h[N];
void add(int x,int y){
	h[x].pb(y);
}
void dfs1(int x,int fa){
	d[x]=d[fa]+1;
	ff[x]=fa;
	mx[x]=d[x];
	sz[x]=1;
	for(int y:h[x]){
		if(y==fa)continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(mx[y]>mx[son[x]])mx[x]=mx[y],son[x]=y;
	}
}
void dfs2(int x,int fa){
	id[x]=++num;
	if(son[x])dfs2(son[x],fa),ed[x]=ed[son[x]];
	else ed[x]=x;
	for(int y:h[x]){
		if(y==ff[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
void dfs(int x,int fa){
	if(son[x]){
		dfs(son[x],x);
		f[id[x]]=sz[x]-1;
	}
	for(int y:h[x]){
		if(y==fa||y==son[x])continue;
		dfs(y,x);
		for(int j=0,t=0;j<=id[ed[y]]-id[y];j++){
			int u=id[x]+j+1,v=id[y]+j;
			t+=tag[v],f[u]+=f[v]+t;
		}
		tag[id[x]+id[ed[y]]-id[y]+1+1]+=sz[y];
	}
}
void solve(){
	cin>>n;
	ans=n;num=0;
	for(int i=1;i<=n;i++){
		h[i].clear();
		f[i]=tag[i]=0;
		ff[i]=ed[i]=son[i]=0;
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	dfs(1,0);
	for(int i=id[1],t=0;i<=id[ed[1]];i++)
		t+=tag[i],ans=min(ans,f[i]+t);
	cout<<ans<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

题意：一棵树，每次可以删除一个叶子，问最少几次可使所有叶子到 $1$ 的距离相等。

若最后每个叶子到 $1$ 的距离为 $d$，那么需要删除的节点要不然自身深度 $>d$，要不然子树内最大深度 $<d$。从大到小枚举 $d$ 以做到快速更新当前答案。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[500005];
int g[500005],w[500005];
int dep[500005];
int val[500005];
void dfs(int p,int dad){
	dep[p]=dep[dad]+1;
	++w[dep[p]];
	val[p]=dep[p];
	for(const int&i:v[p])
		if(i!=dad)dfs(i,p),val[p]=std::max(val[p],val[i]);
	++g[val[p]];
}
int T,n,ans,pre,suf;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			v[i].clear(),g[i]=w[i]=0;
		for(int i=1,x,y;i<n;++i)
			scanf("%d%d",&x,&y),
			v[x].push_back(y),v[y].push_back(x);
		v[1].push_back(0);
		pre=n;suf=0;
		dfs(1,0);
		ans=n-1;
		for(int i=n;i!=1;--i){
			pre-=g[i];
			ans=std::min(ans,pre+suf);
			suf+=w[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：strcmp (赞：1)

看到题很快就会了。

显然的枚举最后叶子的深度都为 $d$，将所有深度恰好为 $d$ 的结点拉出来钦定它们是叶子。除了它们到根的链并之外其它结点都必须删完。

于是答案就是枚举深度，计算相同深度的结点到根的链并的最大值，然后用 $n$ 减去它即可。

计算链并最傻瓜的做法就是按 dfs 序排序然后用深度和减去相邻结点 lca 的深度。（ZJOI 语言的结论）

因为笔者完全不想思考于是直接倍增套了这个结论做了，当然实际上是可以 bfs 序线性维护好它的 lca 的。

时间复杂度 $\Theta(Tn\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 5e5 + 10, mod = 1e9 + 7;
int T, n, q[maxn], hd, tl, d[maxn], dfn[maxn], tot = 0, fa[maxn][21]; vector<int> g[maxn], b[maxn];
void dfs(int u, int f) {
	fa[u][0] = f; dfn[u] = ++tot; d[u] = d[f] + 1;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : g[u]) if (v != f) dfs(v, u);
}
inline int lca(int x, int y) {
	if (x == y) return x;
	per(i, 20, 0) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), g[x].pb(y), g[y].pb(x);
		dfs(1, 0); int ans = n;
		rep(i, 1, n) b[d[i]].pb(i);
		rep(i, 1, n) {
			if (!b[i].empty()) {
				sort(b[i].begin(), b[i].end(), [&](int i, int j) { return dfn[i] < dfn[j]; }); 
				int sum = 0; for (int v : b[i]) sum += d[v];
				rep(j, 0, (int)b[i].size() - 2) sum -= d[lca(b[i][j], b[i][j + 1])]; ans = min(ans, n - sum);
			}
		}
		printf("%d\n", ans);
		for (int i = 1; i <= n; i++) g[i].clear(), b[i].clear(); tot = 0;
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：1)

这 Div2 E 比 C 还简单，虽然我都场切了。

考虑枚举最终结果里叶子深度 $dep$，我们考虑枚举的时候，把原来超过深度 $dep$ 的点全部剪掉，不足 $dep$ 深度的叶子一块剪掉。

首先考虑把超过部分剪掉，这个很简单，只需要处理每个点的深度并计算 $\leq dep$ 的节点个数即可。

然后不足的部分，假设上次枚举 $dep-1$ 保留了某个叶子 $u$，其深度为 $dep-1$，那么可以考虑让 $u$ 不断跳父亲节点 $fa$，并不断删掉 $fa$ 的子树，直到跳到了某个节点 $v$，且 $v$ 的子树存在节点的深度为 $dep$，此时保留 $v$ 以及其祖先节点。

这个过程可以使用广搜轻松实现，时间复杂度均摊 $\Theta(n)$。

```cpp
while (1){
	while (!q.empty()){
		int x=q.front().fr,fa=q.front().sc,t=0;
		q.pop();
		for (auto y:e[x])
			if (y!=fa){
				c[x]++;
				ffa[y]=x;
				q2.push({y,x});
				t=1;
			}
		if (!t) q3.push({x,fa});
	}
	if (q2.empty()) break;
	s+=q2.size();
	while (!q2.empty()){
		q.push(q2.front());
		q2.pop();
	}
	while (!q3.empty()){
		int x=q3.front().fr,fa=q3.front().sc;
		q3.pop();
		if (c[x]||vis[x]) continue;
		vis[x]=1;
		s--,c[fa]--,q3.push({fa,ffa[fa]});
	}
	ans=min(ans,n-s);
}
```

---

## 作者：迟暮天复明 (赞：1)

从小到大枚举深度 $D$，那么深度小于 $D$ 的叶子再也没有用了，全部直接摘掉，这部分可以优先队列维护。深度大于 $D$ 的所有结点全部留不住，直接 DFS 预处理深度后缀和即可。答案就是两个部分相加求最小值。

---

## 作者：Wuming_Shi (赞：1)

# CF2018C 题解
## 题意
给定一个 $n$ 个结点的树，根为 $1$，每次操作可以删除一个叶子结点及其连到父亲的边，问至少多少次能使每个叶子结点到根的距离都相同。
## 思路
先说一下大体的思路。

枚举最终的深度 $d$，则所有深度小于 $d$ 的叶子结点必须删掉，以及所有深度大于 $d$ 的结点（无论是否是叶子）也都要删掉。注意第一种情况可能会产生新的叶子节点，这种结点也要删掉。求出对于每个 $d$ 答案取最小值即可。

### 实现细节

首先需要一个 `sum1` 变量（作用下文说明），一个 `cnt` 数组用来统计每个结点的子结点个数。

考虑从小到大枚举 $d$，用一个 `vector` 存储深度为 $d$ 的所有结点。初始时 `vector` 内只有根。在增加 $d$ 时，要做这两件事：
1. 枚举 `vector` 内的结点，如果它是叶子节点，就删掉，并跳到它的父亲，将父亲的 `cnt` 减一。如果这时父亲的 `cnt` 变成零，即变为叶子结点，就把它删掉，接着往上跳。每删掉一个数就把 `sum1` 加一，这是上文第一种情况的贡献。
2. 将 `vector` 内所有结点的所有儿子都放进来，把原来的结点都清掉。用变量 `sum2` 统计新加入的结点的子树大小（不包括它自己），这是上文第二种情况的贡献。

那么深度为 $d$ 时的答案即为 `sum1+sum2`。注意 `sum1` 在每次循环中不需要清零，而 `sum2` 需要。

## 代码
~~~cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 10;
int t, n;
struct Edge {
    int to, nxt;
}edge[MAXN << 1]; int tot, head[MAXN];
int sz[MAXN], fa[MAXN];
vector<int> pnt, tmp;
int cnt[MAXN];

void addedge(int u, int v) {
    edge[++tot] = {v, head[u]};
    head[u] = tot;
}

void dfs(int pos, int f) {
    fa[pos] = f;
    for (int i = head[pos]; i; i = edge[i].nxt) {
        int to = edge[i].to;
        if (to == f) continue;
        dfs(to, pos);
        sz[pos] += sz[to] + 1;
        ++cnt[pos];
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        addedge(u, v); addedge(v, u);
    }
    dfs(1, 0);
    pnt.push_back(1);
    int ans = sz[1], sum1 = 0;
    while (pnt.size()) {
        int sum2 = 0;
        for (int i : pnt) {
            bool bb = 0;
            for (int j = head[i]; j; j = edge[j].nxt) {
                int to = edge[j].to;
                if (to == fa[i]) continue;
                bb = 1;
                tmp.push_back(to);
                sum2 += sz[to];
            }
            if (!bb) {
                int p = i;
                while (p) {
                    if (cnt[p]) break;
                    cnt[fa[p]]--;
                    p = fa[p];
                    ++sum1;
                }
            }
        }
        pnt = tmp; tmp.clear();
        ans = min(ans, sum1 + sum2);
    }

    cout << ans << endl;
}

void init() {
    pnt.clear(); tmp.clear();
    for (int i = 1; i <= n; i++) {
        sz[i] = fa[i] = 0;
        head[i] = 0;
    }
    tot = 0;
}   

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> t;
    while (t--) {
        solve();
        init();
    }

    return 0;
}
~~~

---

## 作者：Richard_Whr (赞：0)

无脑做法：

直接枚举深度 $d$，然后留下的最大结点数量就是所有深度 $=d$ 的结点和根构成的虚树大小。

做完了。

复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
vector<int> e[N];
vector<int> D[N];
int n;
int dfn[N],sz[N],seq[N],top[N],fa[N],son[N],ts;
int dep[N];
int T;

void dfs(int u,int p)
{
	dep[u]=dep[p]+1,sz[u]=1,fa[u]=p;
	for(auto v:e[u])
	{
		if(v==p) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}

void Dfs(int u,int t)
{
	dfn[u]=++ts,top[u]=t,seq[ts]=u;
	if(son[u]) Dfs(son[u],t);
	for(auto v:e[u])
	{
		if(v==fa[u] || v==son[u]) continue;
		Dfs(v,v);
	}
}

int lca(int a,int b)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]<dep[top[b]]) swap(a,b);
		a=fa[top[a]];
	}
	if(dep[a]<dep[b]) swap(a,b);
	return b;
}

bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}

int build(vector<int> &vec)
{
	vec.push_back(1);
	int sz=vec.size();
	sort(vec.begin(),vec.end(),cmp);
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	
	vector<int> Vc=vec;
	for(int i=1;i<sz;i++)
	{
		int u=vec[i-1],v=vec[i];
		Vc.push_back(lca(u,v));
	}
	
	sort(Vc.begin(),Vc.end(),cmp);
	Vc.erase(unique(Vc.begin(),Vc.end()),Vc.end());
	
	int res=Vc.size();
	for(int i=1;i<Vc.size();i++)
	{
		int u=Vc[i-1],v=Vc[i];
		int p=lca(u,v);
		res+=dep[v]-dep[p]-1;
	}
	return res;
}

void solve()
{
	cin>>n;
	for(int i=1,a,b;i<n;i++)
	{
		cin>>a>>b;
		e[a].push_back(b),e[b].push_back(a);
	}
	
	dfs(1,0);
	Dfs(1,1);
	
	int mx=0;
	for(int i=1;i<=n;i++) D[dep[i]].push_back(i),mx=max(mx,dep[i]);
	
	int res=0;
	for(int i=1;i<=mx;i++)
	{
		res=max(res,build(D[i]));
	}
	
	cout<<n-res<<"\n";
	
	for(int i=1;i<=n;i++) e[i].clear(),D[i].clear();
	ts=0;
	for(int i=1;i<=n;i++) son[i]=0;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>T;
	while(T--) solve();
	
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

来个无脑虚树做法。

设要把所有叶子深度变为 $d$。删边过程肯定是先把深度为 $d$ 节点下面的子树删掉。对于一条边 $(u,v)$（$u$ 是 $v$ 的父亲），若 $v$ 子树没有深度等于 $d$ 的节点，则整个 $v$ 子树包括 $(u,v)$ 这条边都要被剪掉，如果有就留着。

即求所有深度为 $d$ 的点，它们与根节点路径的并集就是删完的树。这是一个虚树经典问题，建出虚树把所有边长度加起来即可。

---

## 作者：liugh_ (赞：0)

## [Tree Pruning](https://www.luogu.com.cn/problem/CF2018C)

若钦定最后的深度 $dep=x$，显然需要将 $dep\ne x$ 的所有叶子删去。分成两部分考虑：$dep>x$，$dep<x$。第一部分是好做的，显然为 $dep>x$ 的点数；而第二部分不容易的地方在于删去叶子后可能会有新的叶子出现，那么类似 topo 的方法，当一个点所有儿子删完后这个点也应该被删，用队列维护即可，于是我们得到一个 $O(n^2)$ 的做法。

考虑优化，注意到对于每个 $x$，$dep\in[1,x)$ 的点都需要进行这样的一次操作，于是考虑从小到大记录删去每个 $dep$ 的次数，前缀和即可。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

#define int long long
#define pii pair<int,int>
#define fi first
#define se second

signed main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int cse;for(cin>>cse;cse--;){
		int n;
		cin>>n;
		vector<vector<int>> G(n+5); 
		for(int i=2;i<=n;i++){
			int u,v;
			cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		vector<int> dep(n+5),son(n+5),fa(n+5);
		function<void(int,int)> dfs=[&](int u,int lst){
			dep[u]=dep[lst]+1;
			fa[u]=lst;
			for(auto v:G[u])if(v!=lst){
				dfs(v,u);
				son[u]++;
			}
		};
		dfs(1,0);
		vector<vector<int>> a(n+5);
		vector<int> cnt(n+5);
		for(int i=2;i<=n;i++){
			cnt[dep[i]]++;
			if(son[i]==0){
				a[dep[i]].push_back(i);
			}
		}
		vector<int> res(n+5);
		for(int i=1;i<=n;i++){
			queue<int> q;
			for(auto x:a[i])q.push(x);
			while(q.size()){
				int x=q.front();
				q.pop();
				res[i]++;
				son[fa[x]]--;
				if(son[fa[x]]==0)q.push(fa[x]);
			}
		}
		for(int i=1;i<=n;i++)res[i]+=res[i-1];
		for(int i=n;i>=1;i--)cnt[i]+=cnt[i+1];
		int ans=1e9;
		for(int i=1;i<=n;i++){
			ans=min(ans,res[i-1]+cnt[i+1]);
		}
		cout<<ans<<'\n';
	}
	exit(0);
}
```

---

## 作者：Wei_Han (赞：0)

会 E 不会 D，唐的。

我们发现这个删点不好维护，不如考虑保留某些点，假设我们现在枚举了当前保留的叶子节点深度 $k$，那么每个深度为 $k$ 的点到根路径上的点都不能删掉，反之，没有被任何一个节点保留的点就是一定需要删除的，现在就转化成区间覆盖，区间查询的问题了，无脑树剖，枚举深度时提前开 ```vector``` 把所有深度的点扔到一块，然后一个一个深度做，复杂度是 $O(n\log^2 n)$。

[submission](https://codeforces.com/contest/2019/submission/283232645)

---

## 作者：qnqfff (赞：0)

### 思路

考虑从大到小枚举最后树的高度 $h$，显然深度大于 $h$ 的点都要删，考虑剩下哪些点要删，将深度等于 $h$ 的点的到根链标记，则剩下的没标记的点都要删，答案取每个 $h$ 对应要删的点个数的 $\min$ 即可，因为每个点只会被标记一次，所以时间复杂度是 $O(n)$ 的。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf,ubuf[1<<23],*u=ubuf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9') {if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9') {p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,dep[500010],f[500010],flg[500010];vector<int>e[500010],d[500010];
void dfs(int u,int fa){dep[u]=dep[fa]+1;f[u]=fa;d[dep[u]].push_back(u);for(auto v:e[u]) if(v^fa) dfs(v,u);}
void solve(){
	n=read();for(int i=1;i<=n;i++) e[i].clear(),d[i].clear(),flg[i]=0;for(int i=1;i<n;i++){int u=read(),v=read();e[u].push_back(v);e[v].push_back(u);}dfs(1,0);flg[1]=1;
	int ans=n-1,res=1;for(int i=n,sum=0;i>=1;i--){for(auto u:d[i]){while(!flg[u]) {flg[u]=1;res++;u=f[u];}}ans=min(ans,n-res+sum);sum+=d[i].size();}cout<<ans<<'\n';
}
signed main(){
	T=read();while(T--) solve();
	return 0;
}
```

---

