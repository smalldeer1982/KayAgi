# [USACO25OPEN] Ski Slope S

## 题目描述

贝茜要和朋友们一起去滑雪。雪山上有 $N$ 个路标（$1 \leq N \leq 10^5$），按海拔从低到高依次标记为 $1, 2, \ldots, N$（路标 $1$ 位于山脚）。

对于每个路标 $i > 1$，有一条从路标 $i$ 出发，终点为路标 $p_i$（$1 \leq p_i < i$）的滑雪道。这条滑道的难度为 $d_i$（$0 \leq d_i \leq 10^9$），乐趣值为 $e_i$（$0 \leq e_i \leq 10^9$）。

贝茜的 $M$ 个朋友（$1 \leq M \leq 10^5$）每人会进行如下操作：选择一个起始路标 $i$，然后沿着滑道向下滑行（依次经过 $p_i,p_{p_i}$，依此类推），直到抵达路标 $1$。

每位朋友获得的乐趣值等于他们经过的所有滑道的乐趣值之和。每个朋友有不同的技能水平 $s_j$（$0 \leq s_j \leq 10^9$）和勇气值 $c_j$（$0 \leq c_j \leq 10$），这限制他们选择的起始路标必须满足：滑行过程中最多有 $c_j$ 条滑道的难度超过 $s_j$。

请为每位朋友计算他们能获得的最大乐趣值。


## 说明/提示

第一位朋友只能选择路标 $1$ 作为起点，因为其他路标都会导致至少经过一条难度超过 $19$ 的滑道。总乐趣值为 $0$。

第二位朋友可以选择路标 $4$，依次滑行至路标 $2$ 和 $1$。总乐趣值为 $100 + 200 = 300$，其中有一条滑道难度超过 $19$。

第三位朋友可以选择路标 $3$，依次滑行至路标 $2$ 和 $1$。总乐趣值为 $300 + 200 = 500$，其中有两条滑道难度超过 $19$。

- 测试点 $2\sim4$：$N, M \leq 1000$。
- 测试点 $5\sim7$：所有 $c_j = 0$。
- 测试点 $8\sim17$：无额外限制。

## 样例 #1

### 输入

```
4
1 20 200
2 30 300
2 10 100
8
19 0
19 1
19 2
20 0
20 1
20 2
29 0
30 0```

### 输出

```
0
300
500
300
500
500
300
500```

# 题解

## 作者：nbhs23a28 (赞：2)

本题是 USACO25OPEN 银组实现难度略大的题，由于这只属于银组知识范围，所以在此我当然不会用什么高级数据结构或算法，仅仅是一个朴素的的预处理即可。

根据题意，本题等效于给定一棵树和 $M$ 个查询，求满足指定条件的到根结点路径的最大边权和。由于本题询问量比较大，我们有两个方向：一个是带 $\log$ 查询，还有一个是预处理。注意到本题 $c_i \le 10$，这透露给我们信息：可以预处理这 $11$ 种勇气值情况，再由二分技能水平找到符合条件的最大乐趣值。

接下来考虑具体代码实现。我们可以由终点倒推，维护到每个出发点的前 $11$ 大的难度值和总乐趣值。接下来，对于每种勇气值，我们分别对这些该勇气值加 $1$ 大的难度值及乐趣值构成的结构体进行排序。（该勇气值加 $1$ 大的难度值为临界情况，依此排序）接下来我们再遍历排序后的结构体数组，维护 $[1,i]$ 上的乐趣最大值。接下来，对于每个查询，我们先对勇气值对号入座，再二分在排序后结构体数组中的定位，输出预处理出来的乐趣最大值即可。

时间复杂度 $O(c⋅N\log N+M\log N)$（$c= 11$，表示 $c_i$ 值域大小）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[100010],k;//一次性
long long e[100010],d[100010],_max[12][100010],ans[12][100010];
struct Node{
 long long e,max_[12];
 bool operator<(const Node& x)
 {return max_[k]<x.max_[k];
 }
}a[100010];
long long max_[12][100010];
int main()
{cin>>n;
 for(int i=2;i<=n;i++)
 {cin>>p[i]>>d[i]>>e[i];
  e[i]+=e[p[i]];
  a[i].e=e[i];
  for(int j=1;j<=11;j++)
  _max[j][i]=_max[j][p[i]];
  for(int j=1;j<=11;j++)
  {if(d[i]>_max[j][i])
   swap(d[i],_max[j][i]);
   a[i].max_[j]=_max[j][i];
  }
 }
 for(k=1;k<=11;k++)
 {sort(a+1,a+1+n);
  for(int i=2;i<=n;i++)
  {ans[k][i]=max(ans[k][i-1],a[i].e);
   max_[k][i]=a[i].max_[k];
  }
 }
 int m;cin>>m;
 while(m--)
 {int s,c;
  cin>>s>>c;
  c++;
  int id=upper_bound(max_[c]+1,max_[c]+n+1,s)-max_[c]-1;
  cout<<ans[c][id]<<'\n';
 }
}
```

---

## 作者：Ybll_ (赞：1)

# 思路：

**前置芝士：** [可持久化线段树](https://www.luogu.com.cn/problem/P3834)。

考虑到 $c_j\le 10$，预处理出每一个点滑到点 $1$ 使用 $k$ 点勇气值所需要的最小能力值，其实就是这一段路上的滑道难度值的第 $k+1$ 大，那我们就可以用可持久化线段树去做第 $k$ 大问题 ~~，其实是我 dp 不好~~，

我们按题目给出的滑道建反边就得到了一棵以节点 $1$ 为根的树，预处理的时候就从节点 $1$ 往下搜，节点 $1$ 的线段树为一棵空树，剩下的每一个节点的线段树就在它的父亲的线段树的基础上添加这一条边的难度值，接着求第 $k$ 大就行，

现在我们记 `f[i][j].sum` 为从点 $j$ 滑到点 $1$ 使用 $i$ 点勇气值所需的最小能力值，`f[i][j].val` 为从点 $j$ 滑到点 $1$ 使用 $i$ 点勇气值可以获得的乐趣值，全部求出来后，我们对于 `f` 中的每一个勇气值，按照 `f[i][j].sum` 进行升序排序，再从前往后扫一遍求出 `f[i][j].val` 的前缀最大值，

然后就发现此时的序列具有单调性，查询时二分即可。

# 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;
const int N=100005;
struct G
{
	int to,val,sum;
};
struct edge
{
	int u,v,val,sum;
}edge[N];
struct query
{
	int val,sum;
}q[N],f[11][N];
struct segment_tree
{
	int ls,rs,sum;
}tree[N<<5];
int n,m,cnt,sum[N],root[N],A[N];
vector<G>g[N];
bool cmp(query i,query j)
{
	return i.sum<j.sum;
}
il void new_node(int &x)
{
	tree[++cnt]=tree[x];
	tree[cnt].sum++;
	x=cnt;
}
il void build(int &id,int l,int r)
{
	id=++cnt;
	if(l==r)return;
	int mid=l+r>>1;
	build(tree[id].ls,l,mid);
	build(tree[id].rs,mid+1,r);
}
il void update(int &id,int p,int l,int r)
{
	if(l>p||r<p)return;
	new_node(id);
	if(l==r)return;
	int mid=l+r>>1;
	update(tree[id].ls,p,l,mid);
	update(tree[id].rs,p,mid+1,r);
}
il int query(int idx,int idy,int x,int l,int r)
{
	if(l>=r)return l;
	int i=tree[tree[idy].ls].sum-tree[tree[idx].ls].sum,mid=l+r>>1;
	if(i>=x)return query(tree[idx].ls,tree[idy].ls,x,l,mid);
	return query(tree[idx].rs,tree[idy].rs,x-i,mid+1,r);
}
void dfs(int u,int dep)
{
	for(int i=0;i<g[u].size();i++)
	{
		sum[g[u][i].to]=g[u][i].sum+sum[u];
		root[g[u][i].to]=root[u];
		update(root[g[u][i].to],g[u][i].val,1,m);//在父亲的版本上进行修改
		for(int j=0;j<min(11ll,dep);j++)
		{
			f[j][g[u][i].to].sum=query(root[1],root[g[u][i].to],dep-j,1,m);
		}
		dfs(g[u][i].to,dep+1);
	}
}
signed main()
{
//	freopen("skiing.in","r",stdin);
//	freopen("skiing.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=2,j,k,l;i<=n;i++)
	{
		cin>>j>>k>>l;
		edge[i-1]={j,i,k,l};//离散化需要先把输入存下来
		A[i-1]=k;
	}
	sort(A+1,A+n);//离散化排序
	m=unique(A+1,A+n)-A-1;//离散化去重
	build(root[1],1,m);//节点一为一棵空树
	for(int i=1;i<n;i++)
	{
		edge[i].val=lower_bound(A+1,A+n,edge[i].val)-A;
		g[edge[i].u].push_back({edge[i].v,edge[i].val,edge[i].sum});//建反边
	}
	dfs(1,1);
	for(int i=0;i<11;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][j].sum=A[f[i][j].sum];
			f[i][j].val=sum[j];
		}
		sort(f[i]+1,f[i]+1+n,cmp);//按所需能力值升序排序
		for(int j=2;j<=n;j++)
		{
			f[i][j].val=max(f[i][j].val,f[i][j-1].val);//前缀最大值，不做这个东西序列没有单调性，无法直接二分
		}
	}
	cin>>m;
	while(m--)
	{
		int a,b,l=1,r=n,mid,res;
		cin>>a>>b;
		while(l<=r)//二分找出小于此人能力值的最大难度值
		{
			mid=l+r>>1;
			if(f[b][mid].sum<=a)
			{
				res=f[b][mid].val;
				l=mid+1;
			}
			else r=mid-1;
		}
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：CommandSR (赞：1)

## 题意简述

我们需要解决一个关于滑雪路径选择的问题：

有 $n$ 个路标构成一棵以 $1$ 为根的树，每个路标 $i$ 有一条指向 $p_i$ 的滑道，具有难度 $d_i$ 和乐趣值 $e_i$。有 $m$ 个朋友，每人有技能 $s_j$ 和勇气 $c_j$。每个朋友要选择一条从某个路标到根节点 $1$ 的路径，路径上最多有 $c_j$ 条滑道的难度超过 $s_j$。

目标是找到满足条件的路径，使得乐趣值总和最大。

## 基本思路

注意到 $0 \leq c_j \leq 10$，我们可以维护出根节点到每个点的路径上前 $11$ 大的数，并维护出根节点到每个点路径上的乐趣值之和。

则对于每一个询问，因为要求路径上最多有 $c_j$ 条滑道的难度超过 $s_j$，则答案在所有第 $c_j+1$ 大的数不超过 $s_j$ 的点中产生。

不难发现，根据第 $c_j+1$ 大的数分组后，乐趣值越大，所需要的“勇气”就越大，具有单调性，可以套一个二分。对于每一个询问二分出 $c_j+1$ 组中小于等于 $s_j$ 的数中最大的数，输出其乐趣值。

语言描述有些许抽象，可以结合代码理解。

## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (ll i = a; i <= b; ++i)
#define _F(i, a, b) for (ll i = a; i >= b; --i)
#define ll long long
#define pb push_back
using namespace std;
ll rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
const ll N = 2e5 + 5;
ll n, m, p[N], e[N], d[N], mxn[13][N], k;
struct node {
	ll mx[13]; // 每个点路径上前 11 大的值
	ll sum; // 总乐趣值
} a[N];
ll ans[13][N], maxn[13][N];
bool cmp2(node u, node v) {
	return u.mx[k] < v.mx[k];
}
int main() {
	n = rd();
	F(i, 2, n) {
		p[i] = rd(), d[i] = rd(), e[i] = rd();
		e[i] += e[p[i]];
		a[i].sum = e[i];
		F(j, 1, 11) mxn[j][i] = mxn[j][p[i]];
		F(j, 1, 11) {
			if (d[i] > mxn[j][i]) swap(d[i], mxn[j][i]);
			a[i].mx[j] = mxn[j][i];
		}
	}
	for (k = 1; k <= 11; k++) {
		sort(a + 1, a + 1 + n, cmp2);
		F(i, 2, n) {
			ans[k][i] = max(ans[k][i-1], a[i].sum);
			maxn[k][i] = a[i].mx[k];
		}
	}
	m = rd();
	while (m--) {
		ll x = rd(), y = rd();
		ll cur = upper_bound(maxn[y+1] + 1, maxn[y+1] + n + 1, x) - maxn[y+1] - 1;
		cout << ans[y+1][cur] << '\n';
	}
	return 0;
}
```

---

## 作者：qW__Wp (赞：1)

很有意思的题。处理方式类似于[这题](https://www.luogu.com.cn/article/00tw3rn9)，可以去看看。

显然建图，将 $p_i$ 向 $i$ 连边，第 $i$ 个点的点权为其乐趣值 $e_i$。这样我们得到一颗根为 $1$ 的树。则问题等价于：

> 每个人选择初始路标，然后滑到根节点，途中经过的滑雪道的难度超过他们的技能 $s$ 的次数不能超过 $c$ 次。求最大的乐趣值总和。

对于某个人，我们称难度大于这个人技能的边为坏边。**则对于某一条边，它相对于所有技能小于边的难度的人是一条坏边**。

因此可以考虑**将人和边并为一个数组，按照人的技能或边的难度升序排序**，则对于排序后编号为 $i$ 的某条边，它相对于它之后编号大于 $i$ 的人是一条坏边。（实际上，在数组中，我们将边转移到它所连的两个点之中靠近叶子的那个点 $u$，即读入的点。）则在树上，$u$ 及其子树上的点到根节点的路径都需要多经过一条坏边，即记点 $i$ 到根节点的路径上的坏边数量为 $f_i$，使这些点的 $f$ 值加一。

注意到 $0 \le c_i \le 10$，也就是说我们只关心那些 $f_i \le 10$ 的点。对于每个可能的 $f$ 的值 $x$（$0 \sim 10$），**维护所有 $f_u = x$ 的点中 $sum_u$ 的最大值 $t_x$**。对于某个人 $i$，答案即为 $\max\limits_{j = 0}^{c_i} t_j$。

至于 $t$ 的维护，使用 `set` 即可。同时更新时没必要遍历整颗子树，当更新到某个点 $f_u > 10$ 就不用再往下更新了。详见代码。

由于每个点最多被更新 $10$ 次，`set` 更新的时间复杂度为 $O(N \log N)$。

```C++
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 5;

int p[N], d[N], v[N], sum[N], t[N];
int s[N], c[N], ans[N];
int hd[N], cnt, tot;
int n, m;

struct Edge {
	int to, nx;
} e[N];

struct Node {
	int x, id, f;
} a[N];

struct SetCmp {
	bool operator()(int a, int b) const {
		return sum[a] > sum[b];
		// 自定义set排序方式
	}
};

set<int, SetCmp> st[12];

void add(int u, int v) {
	e[ ++ cnt] = {v, hd[u]}, hd[u] = cnt;
}

bool cmp(Node a, Node b) {
	if (a.x != b.x) return a.x > b.x;
	return a.f > b.f; // 相同则小朋友排前面
}

void dfs(int u, int fa) { // 统计sum
	sum[u] = sum[fa] + v[u];
	for (int i = hd[u]; i; i = e[i].nx) {
		int v = e[i].to;
		dfs(v, u);
	}
}

void update(int u) {
	if (t[u] > 10) return;
	st[t[u]].erase(u);
	t[u] ++;
	if (t[u] <= 10) st[t[u]].insert(u);
	for (int i = hd[u]; i; i = e[i].nx) {
		int v = e[i].to;
		update(v);
	}
}

signed main() {
	cin >> n;
	for (int i = 2; i <= n; i ++) {
		cin >> p[i] >> d[i] >> v[i];
		add(p[i], i);
		a[ ++ tot] = {d[i], i, 0};
	}
	cin >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> s[i] >> c[i];
		a[ ++ tot] = {s[i], i, 1};
	}
	sort(a + 1, a + tot + 1, cmp);
	dfs(1, 0);
	for (int i = 1; i <= n; i ++) st[0].insert(i);
	for (int i = 1; i <= tot; i ++) {
		if (a[i].f == 0) { // 雪道，更新f
			update(a[i].id);
		} else { // 人，记录答案
			for (int j = 0; j <= c[a[i].id]; j ++) {
				for (auto x : st[j]) { // 获取set的第一位
					ans[a[i].id] = max(ans[a[i].id], sum[x]);
					break;
				}
			}
		}
	}
	for (int i = 1; i <= m; i ++) {
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：hoko (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P12027)

注意到 $c\le10$，所以我们想到可以用 $g_{i,j}$ 表示从 $i$ 出发滑到 $1$ 的路径上，难度为第 $j$ 大的值为多少,同时用 $val_i$ 记录从 $i$ 到 $1$ 的路径的快乐值之和。

考虑怎么计算这个 $g_{i,j}$，我们可以先把路径按 $p_i$ 从小到大排，这样就可以从小到大处理。怎么维护前 $11$ 大呢，可以直接暴力，每次排序后，判断一下最小值有没有比新加入的路径的难度值小，如果要小的话，就把最小值赋值为新的难度值。


```cpp
for(int i=1;i<=n;i++){
	ll now=s[i].id;
	g[now].val+=s[i].e+g[s[i].p].val;
	for(int j=1;j<=11;j++)g[now].dis[j]=g[s[i].p].dis[j];
	sort(g[now].dis+1,g[now].dis+11+1,cmp1);
	if(g[now].dis[11]<s[i].d)g[now].dis[11]=s[i].d;
	sort(g[now].dis+1,g[now].dis+11+1,cmp1);
}
```

那么，处理好这个有什么用呢。我们先考虑暴力该怎么做，因为每个朋友有一个技能水平 $s_j$ 和勇气值 $c_j$，也就是说这个朋友最多可以经过有 $c_j$ 个难度值大于 $s_j$ 的路径。也就是 $g_{i,c_j+1}\le s_j$。

现在考虑如何优化，容易发现每次比对都只会比对第 $c_j+1$ 大的难度值，所以我们可以把从 $1$ 到 $n$ 的前 $11$ 大的难度值提出来，成为一个二维数组，$d_{i,j}$ 就表示在难度第 $i$ 大的数组里的第 $j$ 条路径的值。我们再对这些数组进行降序排序，并且求出后缀 $\max$，那么最后的答案就是在 $d_{c_j+1}$ 中二分找到第一个大于等于 $s_j$ 的位置 $k$，那么答案就是 $sum_{c_j+1,k}$。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=101010;
ll n,a,b,m,ans,sum[15][N];
struct tt{
	ll p,d,e,id;
}s[N];
struct gg{
	ll val,dis[15];
}g[N];
struct cc{
	ll num,id;
}c[15][N];
bool cmp(tt a,tt b){return a.p<b.p;}
bool cmp1(ll a,ll b){return a>b;}
bool cmpc(cc a,cc b){return a.num<b.num;} 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)cin>>s[i].p>>s[i].d>>s[i].e,s[i].id=i,s[i].p--;
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		ll now=s[i].id;
		g[now].val+=s[i].e+g[s[i].p].val;
		for(int j=1;j<=11;j++)g[now].dis[j]=g[s[i].p].dis[j];
		sort(g[now].dis+1,g[now].dis+11+1,cmp1);
		if(g[now].dis[11]<s[i].d)g[now].dis[11]=s[i].d;
		sort(g[now].dis+1,g[now].dis+11+1,cmp1);
	}
	for(int i=1;i<=11;i++){
		for(int j=1;j<=n;j++)c[i][j].num=g[j].dis[i],c[i][j].id=j;
		sort(c[i]+1,c[i]+n+1,cmpc);
		for(int j=1;j<=n;j++)sum[i][j]=max(sum[i][j-1],g[c[i][j].id].val);
	}
	cin>>m;
	while(m--){
		ans=0;
		cin>>a>>b;
		ll l=1,r=n,ans=0;
		while(l<=r){
			ll mid=l+r>>1;
			if(a>=c[b+1][mid].num)ans=max(ans,sum[b+1][mid]),l=mid+1;
			else r=mid-1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
完结撒花

---

## 作者：LittleAcbg (赞：0)

对限制条件进行转化，最多有 $c_j$ 条超过 $s_j$，就相当于第 $c_j+1$ 名不超过 $s_j$。由于 $c_j$ 范围只有 $10$，所以我们只需要维护每个节点到 $1$ 号节点路径上的边中前 $\bold{11}$（注意不是 $10$）名的难度值。

然后，用 BIT 维护第 $t$ 名不超过 $x$ 的最大乐趣值。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+9;
int n,p,d,e,m,s,c,x[N],nUnq,fd[N][11];
// fd[u][t] 表示根到 u 的路径上的边，第 t+1 大的 d 是多少；没有 t+1 条的默认为 0
ll f[N],bit[11][N];
// f[u] 表示根到 u 路径 e 和
// bit[x][t] 是 BIT 维护 fd[u][t]<=x 的 max f[u]
struct Edge {int v,d,e;};
vector<Edge> to[N];
void dfs(int u)
{
	for (int i = 0; i < to[u].size(); ++i)
	{
		int v = to[u][i].v,d = to[u][i].d,e = to[u][i].e;
		f[v] = f[u] + e;
		for (int j = 0; j <= 10; ++j) fd[v][j] = fd[u][j]; // 复制一遍
		for (int j = 0; j <= 10; ++j)
			if (d >= fd[v][j]) // 更新前 11 名
			{
				for (int k = 10; k > j; --k) fd[v][k] = fd[v][k - 1];
				fd[v][j] = d;
				break;
			}
		dfs(v);
	}
}
// BIT，实现单点增加和前缀最大值查询
int LSB(int x) {return x & -x;}
void add(int t, int x, ll z)
{
	while (x <= nUnq)
	{
		bit[t][x] = max(bit[t][x], z);
		x += LSB(x);
	}
}
ll pmq(int t, int x)
{
	ll ret = 0;
	while (x)
	{
		ret = max(ret, bit[t][x]);
		x -= LSB(x);
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	for (int u = 2; u <= n; ++u)
	{
		scanf("%d%d%d", &p, &d, &e);
		to[p].push_back((Edge){u, d, e}); // 父亲到儿子连边
		x[u] = d;
	}
	sort(x + 1, x + n + 1); // 离散化
	nUnq = unique(x + 1, x + n + 1) - x - 1;
	for (int u = 1; u <= n; ++u) for (int i = 0; i < to[u].size(); ++i)
		to[u][i].d = lower_bound(x + 1, x + nUnq + 1, to[u][i].d) - x;
	for (int j = 0; j <= 10; ++j) fd[1][j] = 1; // fd 默认为 0，离散化后值为 1（x[1]=0）
	dfs(1); // DFS 预处理 fd 和 f
	for (c = 0; c <= 10; ++c) for (int u = 1; u <= n; ++u)
		add(c, fd[u][c], f[u]); // 预处理 BIT
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d%d", &s, &c);
		s = upper_bound(x + 1, x + nUnq + 1, s) - x - 1; // s 变为离散化后的值
		printf("%lld\n", pmq(c, s)); // 输出前缀最大值
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

疑似本题最劣解。

发现有 $n-1$ 条路径，因此这座山是一棵树，因此每个点到 $1$ 有唯一的简单路径，因此按每个点来考虑。

考虑离线，把奶牛的能力值从大到小排序，假设我们按能力值从大到小处理到了 $now$。

这样每次就相当于从每个点开始到 $1$ 的路径上超过 $now$ 的数量一直增加。假设节点 $k$ 到根路径上难度值大于 $now$ 的边的数量为 $val_k$。对于每条边，如果他的难度值大于 $now$，那么深度较深的端点的子树内的点的 $val$ 都会增加 $1$，子树加的问题预处理一下 dfs 序就变为序列上的问题了。预处理出子树到根路径上乐趣值之和 $sum_k$，就变成了给定 $x$，查询 $val_k=x$ 的点的 $sum_k$ 最大值。

但是接下来我们需要维护 $val_k=x$ 这个东西，凭借线段树无法胜任。但是观察到 $c_j\le 10$，因此 $val_k>10$ 的部分就没用了。所以可以使用势能线段树，维护区间 $val_k$ 最小值，暴力修改每个节点，若区间 $val_k$ 最小值 $>10$，就不用修改了。开 $10$ 个可删堆维护 $10$ 个 $val_k$ 的 $sum_k$，同时支持查询最大值。

赛时代码写得有点屎山。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int n,q,cnt,pos,dfn[N],rdfn[N],sz[N],sum[N],res[N];
struct Edge
{
	int fr,to,x,y;
	bool operator<(const Edge &w)const{return x>w.x;}
}E[N];//边
struct Query
{
	int x,y,num;
	bool operator<(const Query &w)const{return x>w.x;}
}Q[N];
struct Deleteable_Heap//可删堆
{
	priority_queue<int>q1,q2;
	void insert(int x) {q1.push(x);return;}
	void erase(int x) {q2.push(x);return;}
	int size() {return q1.size()-q2.size();}
	int top()
	{
    while(!q2.empty()&&!q1.empty()&&q2.top()==q1.top()) q1.pop(),q2.pop();
    return q1.top();
	}
}s[12];
struct SGT
{
	int minn[N*4];
	void build(int k,int l,int r)//建树
	{
		if(l==r) {minn[k]=0;return;}
		int mid=l+r>>1;
		build(k*2,l,mid);
		build(k*2+1,mid+1,r);
		minn[k]=min(minn[k*2],minn[k*2+1]);
		return;
	}
	void update(int k,int l,int r,int ql,int qr)//区间 +1
	{
		if(minn[k]>10) return;//势能线段树
		if(l==r)
		{
			s[minn[k]].erase(sum[rdfn[l]]);
			minn[k]++;
			s[minn[k]].insert(sum[rdfn[l]]);
			return;
		}
		int mid=l+r>>1;
		if(ql<=mid) update(k*2,l,mid,ql,qr);
		if(qr>mid) update(k*2+1,mid+1,r,ql,qr);
		minn[k]=min(minn[k*2],minn[k*2+1]);
		return;
	}
}t;
vector<Edge>v[N];
void dfs(int k,int fa)
{
	sz[k]=1;
	dfn[k]=++cnt;
	rdfn[cnt]=k;
	for(auto now:v[k])
	{
		if(now.to==fa) continue;
		sum[now.to]=sum[k]+now.y;
		dfs(now.to,k);
		sz[k]+=sz[now.to];
	}
	return;
}
void debug()
{
	for(int i=1;i<=n;i++) cout<<sz[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++) cout<<dfn[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++) cout<<rdfn[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++) cout<<sum[i]<<" ";
	cout<<endl<<endl;
	for(int i=2;i<=n;i++) cout<<E[i].fr<<" "<<E[i].to<<" "<<E[i].x<<" "<<E[i].y<<endl;
	cout<<endl;
	for(int i=1;i<=q;i++) cout<<Q[i].num<<" "<<Q[i].x<<" "<<Q[i].y<<endl;
	cout<<endl;
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		E[i].fr=i;
		cin>>E[i].to>>E[i].x>>E[i].y;
		v[i].push_back(Edge{i,E[i].to,E[i].x,E[i].y});
		v[E[i].to].push_back(Edge{E[i].to,i,E[i].x,E[i].y});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) s[0].insert(sum[rdfn[i]]);
	cin>>q;
	for(int i=1;i<=q;i++) cin>>Q[i].x>>Q[i].y,Q[i].num=i;
	sort(Q+1,Q+q+1);
	sort(E+2,E+n+1);
	pos=2;
	//debug();
	t.build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		while(pos<=n&&E[pos].x>Q[i].x)
		{
			t.update(1,1,n,dfn[E[pos].fr],dfn[E[pos].fr]+sz[E[pos].fr]-1);
			pos++;
		}
		for(int j=0;j<=Q[i].y;j++) if(s[j].size()>0) res[Q[i].num]=max(res[Q[i].num],s[j].top());
	}
	for(int i=1;i<=q;i++) cout<<res[i]<<"\n";
	return 0;
}
/*
按 s[i] 从大到小排序，离线处理。

预处理 sum[i] 表示 i 到根节点的乐趣值之和

维护每个节点到根节点路径上难度 >= s[i] 的数量

由于 c[i]<=10，因此按 c[i] 的大小开 10 个 set 维护加入/删除一个数，查询 sum[i] 最大值，势能线段树维护 10 个 set
*/
```

---

