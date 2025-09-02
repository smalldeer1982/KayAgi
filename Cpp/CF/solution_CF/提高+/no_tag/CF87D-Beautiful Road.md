# Beautiful Road

## 题目描述

A long time ago in some country in Asia were civil wars.

Each of $ n $ cities wanted to seize power. That's why sometimes one city gathered an army and sent it to campaign against another city.

Road making was difficult, so the country had few roads, exactly $ n-1 $ . Also you could reach any city from any other city going on those roads.

Even during the war the Oriental people remain spiritually rich and appreciate the beauty of nature. And to keep the memory of this great crusade for the centuries to come, they planted one beautiful tree by the road on which the army spent most time. The Oriental people love nature, that's why if there were several such roads, then one tree was planted by each of them.

Recently, when the records of the war were found, it became clear that each city attacked each other one exactly once. There were exactly $ n(n-1) $ attacks in total. Everyone has been wondering what road after those wars became the most beautiful, that is, by which road they planted the largest number of beautiful trees.

## 样例 #1

### 输入

```
2
2 1 5
```

### 输出

```
2 1
1 
```

## 样例 #2

### 输入

```
6
1 2 1
1 3 5
3 4 2
3 5 3
3 6 4
```

### 输出

```
16 1
2 
```

# 题解

## 作者：封禁用户 (赞：4)

先排序，从小到大的加。出现连续的一段权相等就拿出来一起处理。

每新加一条边，这条边肯定要大于之前加过的任何一条边的权。那么这条边的答案显然是其连接的两个连通块之间的大小积。

那么什么数据结构可以维护连通关系和连通大小呢？并查集即可。

会出一点问题。是因为合并的时候没有顺序。同颜色段的边按深度降序排列，由深度大的向深度小的点合并，那么，下一条边的连通块包含了前一条边的连通块，也就不存在互相影响的情况。

跑的贼快。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
const int maxn = 1e5 + 5;
int n;
int res[maxn];
int tot;
vector<int> G[maxn];
struct edge {
	int u, v, w;
	int dep;
	int id;
} e[maxn << 1];
int Ans, ans;
int dep[maxn];
int t[maxn];
void init(int x, int fa)
{
	for (int v : G[x]) {
		if (v == fa) {
			continue;
		}
		dep[v] = dep[x] + 1;
		init(v, x);
	}
}
bool cmp(edge x, edge y)
{
	if (x.w == y.w) {
		return x.dep > y.dep;
	}
	return x.w < y.w;
}
int f[maxn], s[maxn];
int fnd(int x)
{
	if (f[x] == x) {
		return x;
	} else {
		return f[x] = fnd(f[x]);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		s[i] = 1;
	}
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back(v);
		G[v].push_back(u);
		e[i] = (edge) {
			u, v, w
		};
		e[i].id = i;
	}
	init(1, 0);
	for (int i = 1; i < n; i++) {
		e[i].dep = min(dep[e[i].u], dep[e[i].v]);
	}
	sort(e + 1, e + 1 + n - 1, cmp);
	int i, j;
	for (i = 1; i < n; i = j) {
		for (j = i; j < n && e[i].w == e[j].w; j++) {
			int u = e[j].u;
			int v = e[j].v;
			if (dep[u] > dep[v]) {
				swap(u, v);
			}
			t[j] = s[v];
			f[v] = fnd(u);
			s[fnd(u)] += s[v];
		}
		for (j = i; j < n && e[i].w == e[j].w; j++) {
			int u = e[j].u;
			int sum = s[fnd(u)];
			ans = 2 * t[j] * (sum - t[j]);
			if (ans > Ans) {
				Ans = ans;
				tot = 1;
				res[tot] = e[j].id;
			} else if (ans == Ans) {
				res[++tot] = e[j].id;
			}
		}
	}
	cout << Ans << ' ' << tot << '\n';
	sort(res + 1, res + 1  + tot);
	for (int i = 1; i <= tot; i++) {
		cout << res[i] << ' ';
	}
	cout << '\n';
	return 0;
}
```

---

## 作者：LOLchn0 (赞：2)

# 题意：
给定一棵树，枚举每条路径，给路径上边权最大的边的边权加一。若有多个边权最大的边，则每一条的边权都加一。求最后边权最大的边的边权，有多少边权同样最大，输出这些边的编号。

# 思路：
考虑两种情况：

第一种情况：若所有的边权值都相等：对于每条边，假设它的两边连接的点数分别为 $x$ 和 $y$，则该边的魅力值为 $2xy$。只需要建立一棵树，遍历一遍统计已任意结点为根的子树结点数，便可计算所有边的魅力值，从而得出答案。举例：若以 $rt1$ 为根的子树大小为 $m$，则连接 $rt1$ 和它的父结点的边的魅力值为 $m(n-m)$。

第二种情况：若所有边权值都不等：考虑按照权值从小到大地向图中加入边，用并查集维护联通性，当加入第 $i$ 条边时，将加入它之前两个顶点所在地并查集大小相乘，再乘上 $2$ 便可得到该边魅力值。将所有边加入后，也就得到了答案。

但是在本题中，对边的权值没有限制，也就是说既有不同的也有相同的。所以如果直接应用上述第二种情况中的方法是不对的。应该按照权值从小到大，但是一次不是只加入一条边，而是应该加入权值相等的所有边，然后统计这些边的答案，再进行下一轮加边。

以任意点为根建一棵树，将相等的边按照由深到浅的顺序加入，这样边连接的更深的点所连的结点数是不会改变的，在加入边之前记录这个值，等所有同等权值的边加入后，就可以利用前面记录的值和边所在的并查集总大小得到答案了。

# 代码：
```c
#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int N = 1e5 + 5; 
int n, fa[N], Size[N], dep[N], tmp[N];
vector<int>to[N];
ll val[N];
struct edge {
	int u,v,id,dep;
	ll w;
}e[N];
bool cmp(edge x,edge y){
	if (x.w == y.w)
		return x.dep > y.dep;
	return x.w < y.w;
}
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void join(int i, int u, int v) {
	int fu = find(u), fv = find(v);
	tmp[i] = Size[fv];
	fa[fu] = fv;
	Size[fv] += Size[fu];
}
void dfs(int u, int fa, int depp) {
	dep[u] = depp;
	for (int i = 0;i < to[u].size();++i) {
		int v = to[u][i];
		if (v == fa) continue;
		dfs(v, u, depp + 1);
	}
}
int main() {
	cin >> n;
	for (int i = 1;i < n;++i) {
		cin >> e[i].u >> e[i].v >> e[i].w;
		e[i].id = i;
		to[e[i].u].push_back(e[i].v);
		to[e[i].v].push_back(e[i].u); 
	}

	for (int i = 1;i <= n;++i)
		fa[i] = i, Size[i] = 1;

	dfs(1, 0, 0);
	
	for (int i = 1;i < n;++i) {
		if (dep[e[i].u] > dep[e[i].v])
			swap(e[i].u, e[i].v);  
		e[i].dep = dep[e[i].v];
	}
	sort(e + 1, e + n, cmp);
	int num = 0;
	for (int i = 1;i < n;++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		join(i, u, v), ++num;
		if (i == n - 1 || w != e[i + 1].w) {
			for (int j = i - num + 1;j <= i;++j)
				val[e[j].id] = 1ll * tmp[j] * (Size[find(e[j].u)] - tmp[j]) * 2;
			num = 0;
		}
	}
	num = 0;
	ll maxval = 0;  //写ll！！！
	for (int i = 1;i < n;++i)
		if (maxval < val[i])
			maxval = val[i], num = 1;
		else if (maxval == val[i])
			++num;
	cout << maxval << " " << num << endl;
	for (int i = 1;i < n;++i)
		if (maxval == val[i])
			cout << i << " ";
	return 0;
}

```


---

## 作者：truly_handsome (赞：1)

题意：给定一颗 $n$ 个节点的树，每条边有一个美丽值。枚举所有的路径，一共 $n\times(n-1)$ 条，每次选取所有美丽值最大的边，将这些边权 $+1$。问最后边权最大的边的边权和这些边的标号。

很明显不能暴力枚举每条边，那我们可以尝试计算那些路径会对边做出贡献。为了方便，我们可以把边的美丽值从小到大排序，出现相等的美丽值就拿出来一起处理。

如果美丽值都不一样，那这条边的边权就是它连接的两个连通块的积。

如果不一样，我们可以先记录以深度大的节点为根的子树大小 $sz_v$，然后将深度大的节点并到深度小的，那最后这条边的边权就是 $sz_v\times( \text{连通块大小} - sz_v)$。 

``` cpp
# include <bits/stdc++.h>
# define pb push_back
# define int long long
using namespace std;

int n, cnt = 0, fa[200005], sz[200005], dep[200005], vis[200005], tmp[200005], ans[200005];

vector <int> g[200005];

struct E{
	int u, v, w, dep, id;
} edge[200005];

void add(int u, int v, int w, int id){
	edge[++cnt] = (E){u, v, w, 0, id};
}

bool cmp(E a, E b){
	if (a.w != b.w) return a.w < b.w;
	return a.dep > b.dep;
}

void dfs(int u, int fa){
	dep[u] = dep[fa] + 1;
	for (int v : g[u]) if (v != fa) dfs(v, u);
}

int fnd(int x){
	return x == fa[x] ? x : fa[x] = fnd(fa[x]);
}

signed main(){
	scanf("%lld", &n);
	for (int i = 1;i <= n;i++) fa[i] = i, sz[i] = 1;
	for (int i = 1;i < n;i++){
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		add(u, v, w, i);
		g[u].pb(v); g[v].pb(u);
	}
	dfs(1, 0);
	for (int i = 1;i <= cnt;i++) edge[i].dep = min(dep[edge[i].u], dep[edge[i].v]);
	sort (edge+1, edge+cnt+1, cmp);
	for (int i = 1;i <= cnt;i++){
		for (int j = i;j <= cnt;j++){
			if (edge[i].w != edge[j].w) break;
			int u = edge[j].u, v = edge[j].v;
			if (dep[u] > dep[v]) swap(u, v);
			tmp[j] = sz[v];
			sz[fnd(u)] += sz[v];
			fa[v] = fnd(u);
		}
		for (int j = i;j <= cnt;j++){
			if (edge[i].w != edge[j].w) break; i = j;
			int u = edge[j].u;
			ans[edge[j].id] = tmp[j] * (sz[fnd(u)] - tmp[j]);
	}
	int maxn = 0;
	for (int i = 1;i <= cnt;i++) maxn = max(maxn, ans[i]);
	vector <int> v;
	for (int i = 1;i <= cnt;i++) if (ans[i] == maxn) v.pb(i);
	printf("%lld %lld\n", maxn*2, (int)v.size());
	for (int i : v) printf("%lld ", i);
	return 0;
}

/*
10
10 6 4
4 2  1
1 2  3
5 3  6
8 7  4
7 1  1
5 8  1
9 3  5
6 4  2

32 1
4
*/
```

---

## 作者：Katz (赞：1)

我们在建图的时候可以先从小到大排序，这样确保可以在每一次加边的时候这条边都是当前最大的。这条边的答案即为所联通的并查集大小相乘。然后再以深度为关键字由大到小排序，将深度小的合并到大的里面。这样的话，边连接的更深的点所连接的点数不变。最后统计答案即可。

可能讲的不太清楚，具体可见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,z,fa[100010],siz[100010],tdep[100010],cnt,faa,fab,t[100010],v[100010],ans,anscnt;
vector<int>nxt[100010];
struct node
{
	int a,b;
	int id;
	int dep;
	int val;
}edge[100010];
void dfs(int x,int fa,int tcnt)
{
	tdep[x]=tcnt;
	for(int i=0,to;i<nxt[x].size();i++)
	{
		to=nxt[x][i];
		if(to!=fa) dfs(to,x,tcnt+1);
	}
}
int find(int x)
{
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}
bool cmp(node a,node b)
{
	if(a.val!=b.val) return a.val<b.val;
	return a.dep>b.dep;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;//初始化 
	for(int i=1;i<n;i++)
	{
		edge[i].id=i;
		cin>>edge[i].a>>edge[i].b>>edge[i].val;
		nxt[edge[i].a].push_back(edge[i].b);
		nxt[edge[i].b].push_back(edge[i].a);//无向边 
	}
	dfs(1,0,0);//求出深度 
	for(int i=1;i<n;i++)
	{
		if(tdep[edge[i].a]>tdep[edge[i].b]) swap(edge[i].a,edge[i].b);//使b更深 
		edge[i].dep=tdep[edge[i].b];
	}
	sort(edge+1,edge+n,cmp);// 
	for(int i=1;i<n;i++)
	{
		faa=find(edge[i].a),fab=find(edge[i].b);
		t[i]=siz[fab];
		fa[faa]=fab;
		siz[fab]+=siz[faa];//合并 
		cnt++;
		if(i==n-1||edge[i].val!=edge[i+1].val)
		{
			for(int j=i-cnt+1;j<=i;j++) v[edge[j].id]=2*t[j]*(siz[find(edge[j].a)]-t[j]); 
			cnt=0;
		}
	}
	for(int i=1;i<n;i++)
	{
		if(ans==v[i]) anscnt++;
		if(v[i]>ans) ans=v[i],anscnt=1;//求出答案 
	}
	cout<<ans<<" "<<anscnt<<endl;
	for(int i=1;i<n;i++) if(v[i]==ans) cout<<i<<endl;
	return 0;
}
```

---

