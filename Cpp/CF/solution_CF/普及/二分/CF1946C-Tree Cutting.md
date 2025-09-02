# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6```

### 输出

```
2
1
3
1
1
2```

# 题解

## 作者：spfa_ (赞：9)

[CF1946C Tree Cutting](https://www.luogu.com.cn/problem/CF1946C)

### 题目翻译

给一棵 $n$ 个结点的树，在树上删除 $k$ 条边，使得所有连通块大小的最小值最大。

### 题目分析

二分判定答案，单调性显然，因为若当前一个答案满足那么比这个答案小的均满足。假设判定 $x$，我们可以贪心的选择进行删边。若当前节点的子树大小大于等于 $x$（子树内可能已删除了一些边），那么我们可以选择删边，并增加连通块数量。但是要注意判断还未处理的那个连通块的大小是否能够大于等于 $x$。时间复杂度 $O(n\log n)$。

### code

赋注释。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

const int N = 1e5+5;
int n, k, w, tot, sum, sz[N];
vector <int> E[N];

void dfs(int x, int fa) {
	sz[x] = 1;
	for (int y:E[x]) if (y != fa) {
		dfs(y, x);
		if (sz[y] >= w && sum-sz[y] >= w) ++tot, sum -= sz[y];//判断是否能够删除该边 
		else sz[x] += sz[y];
	}
}

bool check(int x) {
	tot = 1, w = x, sum = n; memset(sz, 0, sizeof(sz));//sum为未处理过的联通块大小 
	dfs(1, 0); return tot > k;
}

void solve() {
	for (int i = 1; i <= n; ++i) E[i].clear();//多测要清空 
	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int x = rd(), y = rd();
		E[x].pb(y), E[y].pb(x);
	}
	int l = 1, r = n;
	while (l < r) {//二分 
		int mid = l+r+1>>1;
		if (check(mid)) l = mid;
		else r = mid-1;
	}
	cout << l << '\n';
}

int main() {
	int t = rd();
	while (t--) solve();
	return 0;
}
```

---

## 作者：cute_overmind (赞：4)

考虑二分，单调性显然成立。

定义 $lst_p$ 是对于 $p$ 所在子树取得最大结果后可以返回多少个点。

对于 `check` 函数，我们从根向底搜索，对于一个点 $p$ 的每个子节点 $s$，我们将 $lst_p$ 加上 $lst_s$。

如果此时 $lst_p$ 大于当前 `check` 的值 $x$，那么将 $lst_p$ 设为 $0$ 且将答案加一。

原理是如果此时整个作为一块必然最优，而 $p$ 点已经被使用，所以其他剩余点无法向上继续使用。

最终答案大于 $x$ 则为 `true`。 

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;

struct lsqxx{
	int t, nxt; 
}e[N << 2];
int num[N], cnt;
void addedge(int f, int t){
	e[++ cnt].t = t;
	e[cnt].nxt = num[f];
	num[f] = cnt;
}
void clear(int n){
	cnt = 0;
	for(int i = 1 ; i <= n ; i ++) num[i] = 0;
}

int k;
int ans = 0;
int dfs1(int p, int f, int x){
	int lst = 1;
	for(int i = num[p] ; i ; i = e[i].nxt){
		int t = e[i].t;
		if(t == f) continue;
		lst += dfs1(t, p, x);
	}
	if(lst >= x) ans ++, lst = 0;
	return lst;
}

bool ck(int x){
	ans = 0;
	dfs1(1, 0, x);
	if(ans >= k + 1) return true;
	return false;
}

void solve(){
	int n;
	cin >> n >> k;
	clear(n);
	for(int i = 1 ; i < n ; i ++){
		int f, t;
		cin >> f >> t;
		addedge(f, t);
		addedge(t, f);
	}
	int l = 0, r = n;
	while(l < r){
		int mid = (l + r) >> 1;
		if(ck(mid)) l = mid + 1;
		else r = mid - 1;
	}
	if(! ck(l)) l --;
	cout << l << '\n';
}

signed main(){
	int t;
	cin >> t;
	while(t --)
	solve();

	return 0;
}
```

---

## 作者：Shadow_T (赞：3)

### 前言

赛时一遍过，开心！

### 题目分析

很明显连通块含有节点数的最小值越大，越不容易删掉 $k$ 条边。所以满足单调性，可以二分。

对于二分的 $\operatorname{check}(x)$ 函数可以贪心，dfs 遍历整棵树，统计子节点数量。当答案从下往上倒着传上来时，如果发现叶节点数大于等于 $x$，我们就直接切，把传上去的子节点变成 $0$，增加计数器。

最终如果发现剩余的点不足 $x$，那么就在少切一条边，减少计数器。最终如果计数器大于等于 $k$，即返回 $1$；否则返回 $0$。

时间复杂度 $\mathcal {O}(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
vector<int> g[maxn];
bool vis[maxn];
int tot,n,k;
int dfs(int d,int x)
{
//	cout<<d<<" ";
	int ans=1;
	for(int i=0;i<g[d].size();i++)
	if(!vis[g[d][i]])
	{
		vis[g[d][i]]=true;
		ans+=dfs(g[d][i],x);
	}
	if(ans>=x) 
	{
		ans=0,tot++;
//		cout<<"tot++,"<<d<<" ";
	}
	return ans;
}
bool check(int x)
{
//	cout<<"x="<<x<<"\n";
	tot=0;
	for(int i=1;i<=n;i++)
	vis[i]=false;
	vis[1]=true;
	int z=dfs(1,x);
	if(z<x) tot--;
//	cout<<"\ntot="<<tot<<"\n";
	if(tot<k) return false;
	return true;
}
void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	g[i].clear();
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout<<l<<"\n"; 
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve(); 
}
```

---

## 作者：T_TLucas_Yin (赞：2)

这题好难，居然能放到 C。

首先对于答案的判定是通过二分查找实现的（显然，如果能构造出最小子树为 $x$ 的方案，那么肯定可以有最小子树为 $x-1$ 的方案，只需要在别的地方去掉一刀，用来分割这棵最小子树即可）。但这一点似乎不是很好想。

接下来就要考虑如何模拟删边的过程。注意到在树上删去一条边，其实相当于删掉了某个节点的一棵子树。对于给定的子树最小限制 $m$，如果删掉的这棵子树和删掉后整棵树剩余部分的大小均大于等于 $m$，则可以进行切割。

为了最优化答案，每次删掉的树要尽可能小。所以我们要从子树最小的节点开始枚举，即从深度最深的节点开始。首先存储下以每个节点为根的子树的大小。在深搜的时候，对于一个节点，先分割它的子树，再判断此时删掉它与它的这棵子树之间的边是否可行。如果可行，则进行删除操作，在该节点的大小中直接去掉该子树的大小，并更新删除的边数。此时它的父节点也需要更新，所以还要通过懒标记上传。整棵树遍历完后判断切掉的边数是否达到了 $k$ 条，达到即合法。

注意一组数据要进行多次搜索判断，所以需要单独开一个存储子树大小的数组用于搜索，搜索前把这个数组恢复到初始状态。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,b,f[200005],flag[200005];
int ver[200005],ne[200005],head[200005],tot;
void add(int x,int y){
	ver[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
int build(int root,int fa){//计算子树大小，逻辑很简单，可以自行理解
	f[root]=1;
	for(int i=head[root];~i;i=ne[i]){
		if(ver[i]==fa) continue;
		f[root]+=build(ver[i],root);
	}
	return f[root];
}
int x,cnt,ff[200005];//cnt表示当前树中的节点数
void dfs(int root,int fa,int k){//模拟删除边操作的深搜
	for(int i=head[root];~i;i=ne[i]){
		if(ver[i]==fa) continue;
		dfs(ver[i],root,k);//一定要先切子树
		if(ff[ver[i]]>=k&&cnt-ff[ver[i]]>=k){//如果可以切割
			x++;
			ff[root]-=ff[ver[i]],cnt-=ff[ver[i]],flag[root]+=ff[ver[i]];//更新子树大小和懒标记
		}
		if(flag[ver[i]])//上传子树的懒标记
			ff[root]-=flag[ver[i]],flag[root]+=flag[ver[i]],flag[ver[i]]=0;
	}
}
bool check(int k){
	x=0,cnt=n;
	for(int i=1;i<=n;i++) ff[i]=f[i],flag[i]=0;//以上为初始化
	dfs(1,0,k);
	return x>=m;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++) head[i]=-1;
		for(int i=1;i<n;i++){
			scanf("%d %d",&a,&b);
			add(a,b),add(b,a);
		}//以上为输入和建树
		f[1]=build(1,0);//存储下所有子树大小
		int l=1,r=n,mid,k=1;
		while(l<=r){//开始二分
			mid=(l+r)>>1;
			if(check(mid)) l=mid+1,k=mid;
			else r=mid-1;
		}
		printf("%d\n",k);
	}
	return 0;
}
```

---

## 作者：The_Elation_Aha (赞：2)

想 BC 都比想 A 快，服了。

--------

很容易想到二分答案。

我们可以贪心地去选择要删除哪些边。如果一个点的某个儿子的子树大小大于等于我们二分到的 $x$，并且次数已经删去的边数 $tot<k$，那么就可以把当前点和这个儿子的边删了，这个点的子树大小就不加上儿子的子树大小。

但是你直接这么写会发现过不了样例的第五个测试，原因是那个样例中这样贪心之后会剩一个 $1$ 号点组成单独一个连通块，小于等于二分到的答案 $2$，但是我们并没有判断。所以考虑在 dfs 过程中维护一个并查集，dfs 后如果 $tot=k$ 并且每个连通块大小都 $\ge x$ 那么就合法了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
const ll N=3*114514,M=1919810,inf=1e18,mod=1e9+7;
struct xx{
	ll next,to;
}e[2*N];
ll head[2*N],cnt;
void add(ll x,ll y){
	e[++cnt].next=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
ll T;
ll n,k,tot,siz[N],f[N];
void dfs(ll u,ll fa,ll x){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,x);
		if(siz[v]>=x&&tot<k) ++tot;
		else siz[u]+=siz[v],f[v]=u;
	}
}
ll find(ll x){return x==f[x]?x:f[x]=find(f[x]);}
bool check(ll x){
	for(int i=1;i<=n;++i) f[i]=i;
	tot=0,dfs(1,0,x);
	bool fl=1;
	for(int i=1;i<=n;++i)
		if(siz[find(i)]<x) fl=0; 
	return tot>=k&&fl;
}
void solve(){
	cin>>n>>k;
	cnt=0;
	for(int i=1;i<n;++i){
		ll a,b;
		cin>>a>>b;
		add(a,b),add(b,a);
	}
	ll l=1,r=n/(k+1),ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans<<'\n';
	for(int i=0;i<=cnt;++i) head[i]=0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}//我服了爸爸 
```

---

## 作者：huangrenheluogu (赞：1)

直接求解略有困难，不难想到转为判定行问题。

考虑二分答案，判定答案 $mid$ 是否可行。

之后，可以树形 dp，$f_{x}$ 表示 $x$ 的子树内最多可以划分成多少个连通块，并且顺便记录一下划分成这么多个连通块还剩下多少个节点可以贡献。

如果此时 $f_x\ge mid$，那么仍然可行，计入贡献。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define mid (l + r >> 1)
using namespace std;
const int N = 1e5 + 5;
int T, n, fir[N], nxt[N << 1], son[N << 1], tot, u, v, k, l, r, ans, sz[N], f[N];
inline void init(){
	for(int i = 1; i <= n; i++){
		fir[i] = 0;
	}
	for(int i = 1; i <= tot; i++){
		nxt[i] = 0;
	}
	tot = 0;
}
inline void dfs(int x, int ff = 0){
	f[x] = 0, sz[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] ^ ff){
			dfs(son[i], x);
			sz[x] += sz[son[i]];
			f[x] += f[son[i]];
		}
	}
	if(sz[x] >= mid) sz[x] = 0, f[x]++;
}
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
int main(){
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d%d", &n, &k);
		for(int i = 1; i < n; i++){
			scanf("%d%d", &u, &v);
			add(u, v), add(v, u);
		}
		l = 1, r = n;
		while(l <= r){
			dfs(1);
			if(f[1] >= k + 1) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Rubedo_N (赞：1)

# CF1946C Tree Cutting 题解
## 思路
二分题。  

可以二分最小连通块的节点数。  

二分中的 `check()` 函数中是贪心和 dfs。从叶子节点开始 dfs，统计 dfs 到的节点数量。  
当统计到的数量等于二分到的 $mid$ 时，说明可以删一条边。故统计节点数变量归零，统计删边数变量 $+1$。  
dfs 结束后，若剩下节点数 $< mid$，说明多删了一边。
删除边数 $-1$。  
以上操作均进行后，判断最终删除边数是否 $\ge k$，成立则返回 $1$，否则返回 $0$。

若`check()` 函数返回 $1$，移动左指针，否则移动右指针。

最后输出左右指针均可。
## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,x,y;
int ans,cnt;
int l,r,mid;
vector<int> a[500010];//记录节点连通情况
bool vis[500010];//标记数组
int dfs(int d,int now){
	int ans=1;
	int l=a[d].size();//时间复杂度比每次判断长度的方式快
	for(int i=0;i<l;i++){
		if(!vis[a[d][i]]){//未来过
			vis[a[d][i]]=1;//标记
			ans+=dfs(a[d][i],now);//dfs 目的点
		}
	}
	if(ans>=now){//节点数大于 mid
		ans=0;//节点数归零
		cnt++;//多切一边
	}
	return ans;
}
bool check(int now){
	cnt=0;//初始化计边数变量
	for(int i=1;i<=n;i++)vis[i]=0;//初始化标记数组
	vis[1]=1;//标记起点
	if(dfs(1,now)<now)cnt--;//开始dfs。结果若少于 mid，则少切一条边
	return cnt>=k;
}
signed main(){
	cin>>t;
	while(t--){//多组测试数据
		cin>>n>>k;
		for(int i=1;i<=n;i++)a[i].clear();//初始化 
		for(int i=1;i<n;i++){
			cin>>x>>y;
			a[x].push_back(y);
			a[y].push_back(x);//类似于无向图
		}
        //二分
		l=1,r=n;
		while(l<r){
			mid=(l+r+1)/2;
			if(check(mid))l=mid;//条件满足移动左指针
			else r=mid-1;//不满足移动右指针
		}
		cout<<l<<endl; 		
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
求最小的最大，显然是二分题。然后判断函数只需要从根节点递归，如果当前节点数 $\ge mid$ 了，那就删掉它与父亲节点的边，并累加一下计数器。如果删边数量已经够多了，那么只要看剩下的整棵树的节点数是否也 $\ge mid$ 就行啦。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, l, r, mid, best, k, x, y, tot;
vector <int> v[100005];
int dfs (int x, int f) {
	int s = 1;
	for (int& i : v[x])
		if (i != f)
			s += dfs (i, x);
	if (tot < k && s >= mid) {
		++ tot;
		return 0;
	}
	return s;
}
bool check () {
	tot = 0;
	return dfs (1, 0) >= mid && tot >= k;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++ i)
			v[i].clear ();
		for (int i = 1; i < n; ++ i)
			cin >> x >> y, v[x].emplace_back (y), v[y].emplace_back (x);
		l = 1, r = n;
		while (l <= r) {
			mid = l + r >> 1;
			if (check ())
				l = mid + 1, best = mid;
			else
				r = mid - 1;
		}
		cout << best << '\n';
	}
	return 0;
}
```

---

## 作者：toolong114514 (赞：1)

# CF1946C Tree cutting 题解
## 题面翻译
给定一个包含 $n$ 个结点的树。

在树上删除 $k(1\leq k<n \leq10^5)$ 条边，使删除后的的图中，所有连通块含有节点数的最小值最大。

输出这个最大值。

本题单个测试点含有多组测试数据。对于每个测试点，所有 $n$ 的和不超过 $10^5$。
## 解题思路
答案存在单调性。

如果一棵树在删除 $k$ 条边后，能构造出一种所有连通块含有节点数的最小值为 $x$ 的解，那么一定能构造出所有连通块含有节点数的最小值为 $x-1$ 的解。

根据答案存在单调性，使用二分答案。

接下来考虑如对二分的 $x$ 进行 check。

不知道大家是否见过这道题：[CF1039D You Are Given a Tree](https://www.luogu.com.cn/problem/CF1039D)。

我们可以用和这道题相类似的贪心思路：

在树上跑一个 DFS。

如果子树的和大于等于 $x$，那么合法连通块数量加 1，这棵子树的大小置为 0。

这样逐层往上统计，如果最终合法连通块数量大于等于 $k$，那么当前 $x$ 的情况有解，否则无解。

此方法的正确性较为显然，因为贪心时得到的所有子树的根都是尽可能深的。
## 参考代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e6+10;
struct node{
	int to,nxt;
}edge[2*N];
int head[N];
int cnt;
void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}
int f[N],lt[N];
int lcnt;
void dfs(int x,int last,int mnsiz){
	f[x]=1;
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to==last) continue;
		dfs(edge[i].to,x,mnsiz);
		f[x]+=f[edge[i].to];
	}
	if(f[x]>=mnsiz){
		lt[++lcnt]=f[x];
		f[x]=0;
	}
}
int n,t,k;
bool check(int xx){
	lcnt=0;
	dfs(1,0,xx);
	if(lcnt-1>=k) return true;
	else return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			head[i]=-1;
		}
		cnt=0;
		for(int i=1;i<n;i++){
			int uu,vv;
			cin>>uu>>vv;
			add(uu,vv);
			add(vv,uu);
		}
		int ans=1;
		int l=1,r=n;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/152620182)

Written by [toolong114514](https://www.luogu.com.cn/user/477821) on 2024/3/26.

---

## 作者：DFs_YYDS (赞：0)

# 题目大意
给你一棵树，需要你删掉 $k$ 条边，使剩下来的点中每个联通块的大小的最小值最大，输出这个最大值。

没有 `CF` 账号交不了，但是在学校的 `OJ` 上过了，应该没啥问题。
# 具体思路
明显有单调性，考虑二分。`check` 使用 `dfs`（这里图方便直接在循环中比较，就不写 `check` 函数了）。`check` 的时候先搜索每个结点的子结点，并返回没被切掉的结点数量，然后看看加上自己是否到 $mid$，如果有的话，直接把这个结点和它的父亲切掉，否则就不切。

当然了，最后切的次数要减一。因为最后一个结点跟它的父亲切，那么它的父亲肯定就不到 $mid$ 了。因此必须减掉一个，来使每个连通块的大小都大于 $mid$。

感觉有点抽象，看了代码就不抽象了（）。
# 完整代码
首先不要 `ctrl+cv`，其次不要 `ctrl+cv`，最后还是不要 `ctrl+cv`。

我一般不喜欢写函数，除非是递归。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a[100005];//每个结点的子结点。 
bool vis[100005];//vis数组。 
int n,k,ans=0;
int dfs(int x,int mid){
	int s=1;//自己也算一个结点。 
	vis[x]=1;
	for(int i=0;i<a[x].size();i++)if(!vis[a[x][i]])s+=dfs(a[x][i],mid);
	//计算孩子结点还有多少个和自己相连。 
	if(s>=mid)ans++,s=0;
	//如果大于mid，就切断，ans++。 
	return s;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));//多测不清空，爆0两行泪。 
		cin>>n>>k;
		for(int i=1;i<n;i++){
			int x,y;
			cin>>x>>y;
			a[x].push_back(y);
			a[y].push_back(x);
			//没有说明第一个是第二个的父亲，所以建双向边。 
		}
		int l=0,r=n;
		while(l+1<r){
			memset(vis,0,sizeof(vis));//清空vis数组。 
			ans=0;//ans设为0。 
			int mid=(l+r)>>1,x=dfs(1,mid);
			ans--;//ans减一，有点抽象，但是尽量理解吧。 
			if(ans>=k)l=mid;//如果切割次数>=k，说明mid可以再增加，l=mid。 
			if(ans<k)r=mid;//mid需要减少，r=mid。 
		}
		cout<<l<<"\n";//最后输出l。 
	}
	return 0;
}
```

---

## 作者：wangxinyi2010 (赞：0)

### Solution
本题难度：CF：1600，洛谷上对应绿题。此题的标签包括二分、贪心、树结构等。

看到题干中“最小值最大”的字眼，并且满足单调性，就可以知道这题需要二分答案。根据狄利克雷原则（抽屉原理），这个最小值不可能超过 $\lfloor\dfrac{n}{k+1}\rfloor$。

我们用 DFS 遍历这棵树，由叶至根统计以各个节点为根的子树的节点数 $sum$，根据贪心算法，我们可以在当某一结点（包括根节点）的 $sum$ 大于等于当前枚举的答案时，将以此节点为根的子树整个切除，即把 $sum$ 赋值为 $0$，同时连通块的数量 $cnt$ 加 $1$。

得到 $cnt$ 后分类讨论：

1. 若 $cnt=k+1$，显然满足要求，答案大于等于 $cnt$。
2. 若 $cnt<k+1$，显然不能满足要求，答案小于 $cnt$。
3. 若 $cnt>k+1$，将某些连通块进行合并，同样可以满足要求，答案大于等于 $cnt$。

注意存储树的数据结构（这里使用邻接表）与二分答案代码的写法，别忘了在解决完一组测试数据后清空树。

### AC Code
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#define maxn 100005
using namespace std;
int t1,n,k,cnt;
vector<int> t[maxn];
bool vis[maxn];
int f(int r,int x){
	vis[r]=true;
	int sum=1;
	for(int i=0;i<t[r].size();i++){
		if(!vis[t[r][i]]) sum+=f(t[r][i],x);
	}
	if(sum>=x){
		cnt++;
		sum=0;
	}
	return sum;
}
int main(){
	cin>>t1;
	for(int i=1;i<=t1;i++){
		cin>>n>>k;
		for(int j=1;j<=n;j++) t[j].clear();
		for(int j=1;j<n;j++){
			int u,v;
			cin>>u>>v;
			t[u].push_back(v);
			t[v].push_back(u);//插入两次
		} 
		int l=1,r=(n/(k+1))+1,mid;
		while(l<r-1){
			mid=(l+r)>>1;
			memset(vis,0,sizeof(vis));
			cnt=0;
			f(1,mid);
			if(cnt>=k+1) l=mid;
			else r=mid;
		}
		cout<<l<<endl;
	}
	return 0;
}
```

---

## 作者：w9095 (赞：0)

[CF1946C Tree Cutting](https://www.luogu.com.cn/problem/CF1946C)

容易发现，如果连通块含有节点数的最小值为 $x$，并且使用的刀数多于或等于 $k$，那么 $x$ 一定可以成为最后的结果。原因是我们可以通过减少一部分刀数，保留一个最小值的连通块，减少其他的刀数。由于 $k\ge1$，所以一定可以保留一个最小值的连通块。

基于这一点，我们发现，连通块含有节点数的最小值为 $x$ 具有单调性。因此，我们对 $x$ 使用二分算法。

对于每一个 $x$，我们考虑一种刀法。显然，我们需要使用最优的刀法。我们考虑如何最小化刀数。

我们通过深度优先搜索，在回溯的过程中，每当我们发现一个子树的节点数超过 $x$，就直接割断它。可以发现这样做是最优的，因为一个子树的节点数超过 $x$，已经构成了一个点数超过 $x$ 的连通块，没有必要再往里面增加节点。

注意需要特判根节点的连通块点数小于 $x$ 的情况，直接返回不可能。原因是在最优化的情况下都无法解决，其余情况更不能解决。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt;
}e[400000];
long long t,n,k,u,v,h[400000],cnt=0,tol=0,ans=0;
void add_edge(long long u,long long v)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
}

long long dfs(long long x,long long f,long long c)
{
	long long siz=1;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=f)siz+=dfs(e[i].v,x,c);
	if(siz>=c&&x!=1)
	   {
	   	tol++;
	   	return 0;
	   }
	if(x==1&&siz<c&&tol==k)tol=0;
	return siz;
}

int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld",&n,&k);
	   	ans=0,cnt=0;
	   	for(int i=1;i<=n;i++)h[i]=0;
	   	for(int i=1;i<=n-1;i++)
	   	    {
	   	    scanf("%lld%lld",&u,&v);
	   	    add_edge(u,v),add_edge(v,u);
			}
		long long l=1,r=n;
		while(l<=r)
		   {
		   	long long mid=(l+r)>>1;
		   	tol=0,dfs(1,0,mid);
		   	if(tol>=k)ans=mid,l=mid+1;
		   	else r=mid-1;
		   }
		printf("%lld\n",ans);
	   }
	return 0;
}
```

---

## 作者：Engulf (赞：0)

注意到答案具有单调性，考虑二分答案转为可行性问题。

二分 $x$，贪心地去切边，假设当前子树 $u$ 的大小 $siz_u$ $\ge x$ 并且 $S - siz_u \ge x$（保证另一个连通分量也 $\ge x$），就直接切掉 $u$ 和它父亲的边。同时直接令 $siz_u = 0$，因为已经切掉了。$S$ 是当前剩余节点数。
```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> g(n);
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            u--, v--;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        int l = 0, r = n - 1, res = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if ([=]() {
                int cnt = 0;
                int tot = n;
                vector<int> siz(n);
                function<void(int, int)> dfs = [&](int u, int fa) {
                    siz[u] = 1;
                    for (auto v: g[u]) {
                        if (v == fa) continue;
                        dfs(v, u);
                        siz[u] += siz[v];
                    }
                    if (fa != -1 && siz[u] >= mid && tot - siz[u] >= mid) {
                        cnt++;
                        tot -= siz[u];
                        siz[u] = 0;
                    }
                };
                dfs(0, -1);
                return cnt >= k;
            }()) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        assert(res != -1);
        cout << res << "\n";
    }
    return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定一棵有 $n$ 个点的树，问删掉 $k$ 条边后最小连通块节点数 $x$ 的最大值是多少。
# 思路
一眼二分答案，我们二分枚举 $x$，然后每次检验是否可以做到。

关于检验的部分是比较重要的。

因为需要删 $k$ 边，根据树的定义可以知道每删掉一条边就会多一个连通块，最后共有 $k+1$ 个连通块。

同时，因为删掉的边必然是一个父节点到一个子节点的，所以每个连通块都是原树的子树。

所以我们遍历一遍这棵树，同时计满足节点数大于等于枚举的 $x$ 值的子树个数。对每个子树统计节点数，若大于等于当前枚举的 $x$ 值便将此子树删去并且计数赠一。最后若计数值大于等于 $k+1$ 便满足题意了。

二分枚举答案时，左边界不难知道为 $1$，因为总点数为 $n$，分成 $k+1$ 份，所以有边界就是 $\lfloor\frac{n}{k+1}\rfloor$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

int t,n,m,k,num,siz[N];

vector<int> e[N];

inline void dfs(int u,int fa){

    siz[u]=1;

    for(auto v:e[u])
        if(v!=fa){

            dfs(v,u);

            siz[u]+=siz[v];
        }

    if(siz[u]>=m)
        num++,siz[u]=0;

    return;
}

main(){

    // freopen("c.out","w",stdout);

    scanf("%d",&t);

    while(t--){

        scanf("%d%d",&n,&k);

        for(int i=2,u,v;i<=n;i++){
            
            scanf("%d%d",&u,&v);

            e[u].emplace_back(v);
            e[v].emplace_back(u);
        }

        int l=1,r=n/k;

        while(l<r){
            
            m=l+r+1>>1;
            num=0;
            dfs(1,0);

            if(num>=k+1)l=m;
            else r=m-1;
        }

        for(int i=1;i<=n;i++)
            e[i].clear();

        printf("%d\n",l);
    }
}
```

---

## 作者：I_will_AKIOI (赞：0)

赛时被降智了，最后 $5$ 分钟才写出，还寄了两发。

#### 题目大意

给你 $n$ 个点的树，你需要删去 $k$ 条边，请你最大化删去 $k$ 条边后这棵树节点的连通块最小值。

看到最大值最小，很容易想到二分。我们二分这个最小值，然后看看最多能删去几条边。若删去边数大于等于 $k$，则令 $l=mid$，否则答案不合法，令 $r=mid-1$。

接着写二分的 check 函数。这里我们可以使用贪心算法。先计算出一个节点的子树大小，接着按节点的深度从大到小枚举，如果子树大小大于等于 $mid$，并且删去之后剩余节点的大小也大于等于 $mid$，则说明可以删去这条边。

但是同时我们发现，我们还需要把该点到根节点上的路径的子树个数全部减去该点的子树大小。这里暴力枚举肯定是不行的。我们用 $f$ 记录减去的子树大小，等到遍历到该点时再减去子树大小，类似于线段树的懒标记。

个人认为这题比较难，绿。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,sum,val,cnt[200005],cnt1[200005],f[200005];
vector<int>v[200005];
void dfs(int k,int fa)//计算深度
{
  cnt[k]=1;
  for(int i=0;i<v[k].size();i++)
  {
    int now=v[k][i];
    if(now==fa) continue;
    dfs(now,k);
    cnt[k]+=cnt[now];
  }
  return;
}
void dfs1(int k,int fa)//计算要删去几条边
{
  for(int i=0;i<v[k].size();i++)
  {
    int now=v[k][i];
    if(now==fa) continue;
    dfs1(now,k);
    if(cnt1[now]>=x&&val-cnt1[now]>=x)//可以删去当前节点
    {
      cnt1[k]-=cnt1[now];
      f[k]+=cnt1[now];
      sum++;
      val-=cnt1[now];
    }
    if(f[k]) cnt1[fa]-=f[k],f[fa]+=f[k],f[k]=0;//将f数组上传
  }
  return;
}
void solve()
{
  cin>>n>>m;
  for(int i=1;i<n;i++)
  {
    int x,y;
    cin>>x>>y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  dfs(1,0);
  int l=1,r=n,ans=1,mid;
  while(l<r)
  {
    mid=l+r+1>>1;
    x=mid;
    sum=0;
    val=n;
    for(int i=1;i<=n;i++) cnt1[i]=cnt[i],f[i]=0;
    //初始化
    dfs1(1,0);
    if(sum>=m) l=ans=mid;
    else r=mid-1;
  }
  cout<<ans<<"\n";
  for(int i=1;i<=n;i++) v[i].clear(),cnt[i]=0;
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

