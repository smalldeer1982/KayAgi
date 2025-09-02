# [CCC 2021 S4] Daily Commute

## 题目描述

已知有 $N$ 个地铁站，你家在 $1$，学校在 $N$。

有 $W$ 条单向人行道。经过需要一分钟。

此外还有一条环形地铁线路，依次经过 $S_1,S_2,\cdots,S_N$，且保证 $S_1=1$。每天**有且仅有**一辆地铁在 $0$ 时刻从 $S_1$ 出发，并且恰好在第 $i$ 分钟到达 $S_i$。

在接下来 $D$ 天中：

- 交换 $S_{X_i}$ 和 $S_{Y_i}$。注意修改是永久的。
- 查询从 $1$ 到 $N$ 的最短用时。你出发时地铁在 $1$。

## 说明/提示

$$3\leq N\leq 200000,0\leq W\leq 200000,1\leq D\leq 200000$$

译自 [CCC2021 S4](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

请注意常数。

## 样例 #1

### 输入

```
4 3 3
1 2
3 4
4 1
1 4 3 2
3 4
4 2
3 2
```

### 输出

```
1
2
3
```

# 题解

## 作者：_•́へ•́╬_ (赞：12)

## 思路

最优方案一定是只从起点开始坐一段地铁。

因为，如果你坐两段，还会存在等地铁这种事情，一定不会更优。

---------

建反图从终点开始跑一遍 bfs，得到每个点到终点的距离。

每个点到起点的距离就是 $S$ 的逆排列。逆排列就是把下标和数值换一下，我代码里记做 `a`。

两个拼起来，取最小值就是答案。

因为有修改，用数据结构维护一下。

## code

用 `set` 实现，跑的很慢。

```cpp
#include<stdio.h>
#include<deque>
#include<set>
#define N 222222
#define pr pair<int,int> 
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,d,s[N],a[N],h[N],e[N],nxt[N],dis[N];set<pr>qwq;
deque<int>q;
main()
{
	read(n);read(m);read(d);
	for(int i=1,u,v;i<=m;++i)read(u),read(v),--u,--v,
		e[i]=u,nxt[i]=h[v],h[v]=i;
	for(int i=0,x;i<n;read(s[i]),a[--s[i]]=i,dis[i++]=1<<30);
	q.emplace_back(n-1);dis[n-1]=0;
	for(int i;q.size();)
	{
		i=q.front();q.pop_front();
		for(int j=h[i];j;j=nxt[j])if(dis[e[j]]>>30)
			dis[e[j]]=dis[i]+1,q.emplace_back(e[j]);
	}
	for(int i=0;i<n;++i)qwq.emplace(dis[i]+a[i],i);
	for(int u,v;d--;printf("%d\n",qwq.begin()->first))
	{
		read(u);read(v);--u;--v;
		swap(s[u],s[v]);
		u=s[u];v=s[v];
		qwq.erase((pr){dis[u]+a[u],u});qwq.erase((pr){dis[v]+a[v],v});
		swap(a[u],a[v]);
		qwq.emplace(dis[u]+a[u],u);qwq.emplace(dis[v]+a[v],v);
	}
}
```

## code

用堆实现，跑的很快。

```cpp
#include<stdio.h>
#include<queue>
#define N 222222
#define pr pair<int,int> 
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
inline void pc(const char&c)
{
	static char buf[99999],*r=buf;
	(!c||(*r++=c,r==buf+99999))&&(fwrite(buf,1,r-buf,stdout),r=buf);
}
inline void pi(const int&x){if(x>9)pi(x/10);pc(x%10+'0');}
int n,m,d,s[N],a[N],h[N],e[N],nxt[N],dis[N];
priority_queue<pr,vector<pr>,greater<pr> >qwq;deque<int>q;
main()
{
	read(n);read(m);read(d);
	for(int i=1,u,v;i<=m;++i)read(u),read(v),--u,--v,
		e[i]=u,nxt[i]=h[v],h[v]=i;
	for(int i=0,x;i<n;read(s[i]),a[--s[i]]=i,dis[i++]=1<<30);
	q.emplace_back(n-1);dis[n-1]=0;
	for(int i;q.size();)
	{
		i=q.front();q.pop_front();
		for(int j=h[i];j;j=nxt[j])if(dis[e[j]]>>30)
			dis[e[j]]=dis[i]+1,q.emplace_back(e[j]);
	}
	for(int i=0;i<n;++i)qwq.emplace(dis[i]+a[i],i);
	for(int u,v;d--;pi(qwq.top().first),pc('\n'))
	{
		read(u);read(v);--u;--v;
		swap(s[u],s[v]);
		u=s[u];v=s[v];
		swap(a[u],a[v]);
		qwq.emplace(dis[u]+a[u],u);qwq.emplace(dis[v]+a[v],v);
		for(;qwq.top().first^dis[qwq.top().second]+a[qwq.top().second];
			qwq.pop());
	}
	pc(0);
}
```



---

## 作者：RE_Prince (赞：3)

# Daily Commute

[link](https://www.luogu.com.cn/problem/P9026)

## Sol

思维题。

虽然可以等地铁，但这个行为肯定是不被允许的，因为等到地铁来相当于在第 $i$ 分钟的时候从 $S_i$ 出发，和一直坐地铁到 $S_i$ 没有任何区别，因此等地铁我们不考虑。

所以要不是从头做一段地铁，下车然后走到学校，要不是不坐地铁，要不是直接走到学校。

每次跑一遍最短路显然是不现实的，但是我们注意到，交换地铁车站的时候，人行道是不会变的。而坐到第 $i$ 站（注意，是**第** $i$ 站，而不是车站 $i$）并走到学校的时间是 $i+dis_{S_i}$，因此我们建反图，从 $n$ 开始跑，处理到剩下 $n-1$ 个点的最短路来预处理。

因为每个车站的位置是实时变化的，所以需要实时维护最短路。虽然看似每次需要重新跑来求最短，但是我们只需要看交换的两个车站是否改变了最短路即可。因为不交换的车站最短路不会变。

但这会出现一个问题：最短路被交换掉了怎么办？显然，这个方法是会被卡掉的。为了优化时间，我用了优先队列来维护：当车站 $S_i$ 在位置 $j$ 时，最短路是 $dis$。每次交换车站的时候，将新的信息放到队列中。求最短路的时候，就一直取队头，不符合条件的点（也就是交换过的点）就直接弹掉，直至遇到符合条件的点，在那个点下车就是现在的最短路。

总体复杂度是 $O(D\log n)$ 的，可以通过。

代码：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cstring>
#include<string>
#define int long long
using namespace std;
int n, m, i, j, k;
vector<int> G[200009];
bool vis[200009];
int dis[200009];
struct node
{
	int pos, sta, dis;
	bool operator<(node x)const
	{
		return x.dis < dis;
	}
};
priority_queue<node> ans;
int a[200009];
map<int, int> pos;
signed main()
{
	cin >> n >> m >> k;
	for (i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		G[v].push_back(u);
	}
	queue<int> q;
	q.push(n);
	vis[n] = 1;
	memset(dis, 0x3f, sizeof(dis));
	dis[n] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if (!vis[v]) dis[v] = dis[u] + 1, q.push(v), vis[v] = 1;
		}
	}
	for (i = 1; i <= n; i++) cin >> a[i], ans.push({ i,a[i],i + dis[a[i]] - 1}), pos[a[i]] = i;
	int nc = dis[1];
	while (k--)
	{
		int x, y;
		cin >> x >> y;
		int pp = pos[a[x]];
		pos[a[x]] = pos[a[y]];
		pos[a[y]] = pp;
		ans.push({ x,a[y],x + dis[a[y]] - 1 });
		ans.push({ y,a[x],y + dis[a[x]] - 1 });
		swap(a[x], a[y]);
		while (!ans.empty() && pos[ans.top().sta] != ans.top().pos) ans.pop();
		cout << min({ ans.top().dis, nc ,pos[n] - 1 }) << endl;//car->walk, walk, car
	}
	return 0; 
}
```

---

## 作者：jr_zch (赞：3)

# [Daily Commute](https://www.luogu.com.cn/problem/P9026)
## by [jr_zch](https://www.luogu.com.cn/blog/jr-zch-code-garden/) 博客食用更佳喵~
## Part 1：题目大意 
给你一个 $n$ 个点 $w$ 条边的**有向图**，每条边的权值均为 $1$，此外还有一条地铁，通过这条地铁你可以花费 $1$ 分钟以指定顺序通过所有 $n$ 个点 $($ 即 $s$ 数组 $)$，但是当时间为 $t$ 时，你只能在 $s_{t \bmod n}$ 这个点进入地铁。

## Part 2：解题思路
### $O(n^2 \log_2n)$：每一天都跑一遍 `dijkstra` 即可。
### $O(n \log_2n)$：正解如下
把所有普通边建成**反图**，然后从 $n$ 点开始跑一遍 `dijkstra` 得到每个点距 $n$ 的距离 $dis$ 数组。

因为地铁并不是想进就可以进入的，需要等待，那么很显然，最优解**不可能连续坐两段地铁** $($ 明明可以一直在地铁里待着，为何要出来，走一段路，再等地铁，然后到达目的地呢？$)$。

那么只需要枚举地铁坐到哪里，无修改下时间复杂度 $O(n\log_2n)$。

在有修改的情况下也很简单，因为要求最小值，很容易想到用**小根堆**维护一下。

但是优先队列里要存 $3$ 个值：

1. 坐地铁到这个点所需与走到终点所需的总时间。
2. 这个点的编号。
3. 这个点一共交换过几次。

每一次修改就把修改后的入队，然后 `while` 判断，如果堆顶元素的交换次数与这个点当前**总共交换次数**不相等就弹出。

` while(r.top().day!=a[r.top().p]) r.pop(); `
#### tips：
* 最短路的 $dis$ 数组记得初始化成**极大值**。
* 重载运算符时注意细节。

## Part 3：Code
```cpp
#include <bits/stdc++.h>
#define pair pair<int,int>
using namespace std;

const int maxn=2e5+7;
int n,m,d,u,v;
int s[maxn],dis[maxn],a[maxn];
bool vis[maxn];
struct node{
	int len,p,day;
	const bool operator>(const node& x) const{
    	return len>x.len;
  	}
};
vector<int> e[maxn];
priority_queue<pair,vector<pair >,greater<pair > > q;
priority_queue<node,vector<node>,greater<node> > r;

void dijkstra(int st){
	memset(dis,0x3f,sizeof(dis));
	dis[st]=0,q.push(make_pair(0,st));
	while(q.size()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push(make_pair(dis[v],v));
			}
		}
	}
	return ;
}

int main(){
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		e[v].push_back(u);
	}
	dijkstra(n);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=1;i<=n;i++) r.push({i+dis[s[i]]-1,s[i],0});
	for(int i=1;i<=d;i++){
		scanf("%d%d",&u,&v);
		r.push({v+dis[s[u]]-1,s[u],++a[s[u]]});
		r.push({u+dis[s[v]]-1,s[v],++a[s[v]]});
		while(r.top().day!=a[r.top().p]) r.pop();
		printf("%d\n",r.top().len);
		swap(s[u],s[v]);
	}
	return 0;
}
```
## Thanks for your reading

---

## 作者：tkm2013 (赞：2)

## P9026 [CCC2021 S4] Daily Commute 题解

### [传送门](https://www.luogu.com.cn/problem/P9026)

在这道题中，比普通的最短路题还要多了一个地铁，所以我们重点来考虑这个地铁。

如题，地铁只有一趟，所以我们可以选择坐或者不坐，也可以是中途下车，而不会中途上车。如果你比地铁先一步到达地铁站，还是要等待地铁，所以和一开始就上地铁的时间是一样的，所以坐地铁就只会有三种情况。

然后我们还需要求出每个点到终点的距离，不要每一次都重新求，那样时间复杂度会有点高，边权都为1，我们可以使用广搜求最短路，由于我们不好以每个点为起点，然后往 $n$ 走，我们可以以 $n$ 为起点，建立反边跑广搜。然后再交换后枚举在哪一个时刻下车，再加上 $dis_{s_i} - 1$。这样我们就可以得到 $90$ 分了，毕竟也是道绿题，不可能这么简单就得到满分的，我先把这份暴力代码放一下。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int dis[200005];
vector<int>g[200005];
int s[200005]; 
void bfs(){//跑遍最短路
	for(int i=1;i<n;i++){//初始化
		dis[i]=2e9;
	}
	queue<int>q;
	q.push(n);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(auto v:g[u]){
			if(dis[v]==2e9){
				q.push(v);
				dis[v]=dis[u]+1; 
			}
		} 
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	bfs();
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		swap(s[x],s[y]);
		int minn=2e9;
		for(int j=1;j<=n;j++){//枚举下车时刻
			minn=min(minn,dis[s[j]]+j-1);
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```

然后我们就需要对这份代码进行优化了，枚举的时间复杂度是 $O(qn)$ 所以我们需要优化。

最优，看到这两个字，就让人想到了优先队列，我们可以先把没有任何交换过的答案放进优先队列，每次交换后把在 $s_x$ 与 $s_y$ 的位置下车重新放进队列，这时我们发现无法删除，但是我们没必要把对答案没有影响的答案排出去，所以我们从头开始判断。我们的优先队列记录两个值第几站，是到达那个点，然后我们判断优先队列的头如果和我们先在的 $s$ 数组对不上号，就把它踢掉，由于会有多个，此过程使用 $while$ 循环。

### 正确代码


```cpp
#include<bits/stdc++.h>
#include<vector>
using namespace std;
int n,m,f;
int dis[200005];
vector<int>g[200005];
int s[200005];
void bfs(){
	for(int i=1;i<n;i++){
		dis[i]=2e9;
	}
	queue<int>q;
	q.push(n);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(auto v:g[u]){
			if(dis[v]==2e9){
				q.push(v);
				dis[v]=dis[u]+1; 
			}
		} 
	}
	return;
}
struct no{
	int pos,id;
	bool operator<(const no&x)const
	{
		return pos-1+dis[id]>x.pos-1+dis[x.id];
	}
};
priority_queue<no>q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>f;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	bfs();
	for(int i=1;i<=n;i++){
		q.push({i,s[i]});
	}
	for(int i=1;i<=f;i++){
		int x,y;
		cin>>x>>y;
		swap(s[x],s[y]);
		q.push({x,s[x]});
		q.push({y,s[y]});
		while(s[q.top().pos]!=q.top().id){//将对不上号的给踢出去
			q.pop();
		}
		cout<<q.top().pos-1+dis[q.top().id]<<"\n";
	}
	return 0;
}
```

~~十年洛谷一场空，复制题解名变棕~~。

---

## 作者：CSP_Sept (赞：2)

<https://www.luogu.com.cn/problem/P9026>

## 题解

结论：我们一定不会坐 2 次及以上地铁。**不同于其他题解，给出严谨证明：**

- 若在某点 $x\ne 1$ 恰赶上地铁，无论是否是第一班地铁，均不会优于从点 $1$ 开始坐地铁；
- 若还需要等地铁，则若从点 $1$ 开始坐地铁，可以花更少的时间到达 $x$ 点。

证毕。

于是对于每个点，预处理出其到 $n$ 的人行道距离 $d_i$（建反图后使用 Dijkstra 跑一遍即可）。我们接下来的所有交换操作不会改变 $d$ 序列。

再考虑坐地铁到达各点的时间 $t_i$。可以读入的时候预处理出来。

接下来令 $a_i=d_i+t_i$。每次操作等价于交换 $t_{S_i},t_{S_j}$，直接单点维护即可。

我们每次要求 $\min\limits_{i=1}^n\{a_i\}$，注意到 $n\le 2\times 10^5$，直接拉一个线段树过来维护单点修改与全局最小值。

时间复杂度 $O(n\log n)$，常数允许通过。

## 代码

```cpp
int ver[N], edg[N], nxt[N], hed[N];
int tot = 0;
void add(int x, int y, int z){
	tot++;
	ver[tot] = y, edg[tot] = z;
	nxt[tot] = hed[x], hed[x] = tot;
}
ll d[N]; int v[N];
priority_queue <pair <int, int> > q;
void dij(int s){
	for(int i = 1 ; i <= n ; i++) d[i] = (1 << 31) - 1;
	d[s] = 0;
	q.push(make_pair(0, s));
	while(!q.empty()){
		int x = q.top().second;
		q.pop();
		if(v[x]) continue;
		v[x] = 1;
		for(int i = hed[x] ; i ; i = nxt[i]){
			int y = ver[i], z = edg[i];
			if(d[y] > d[x] + z){
				d[y] = d[x] + z;
				q.push(make_pair(-d[y], y));
			}
		}
	}
}

struct segtree{
	ll v[N], a[N], lazy[N];
	void onepush(int l, int r, int k, int d){
		v[k] += d;
		lazy[k] += d;
	}
	void pushdown(int l, int r, int k){
		int m = (l + r) >> 1, d = lazy[k];
		onepush(l, m, k << 1, d);
		onepush(m + 1, r, k << 1 | 1, d);
		lazy[k] = 0;
	}
	void update(int k){
		v[k] = min(v[k << 1], v[k << 1 | 1]);
	}
	void build(int l, int r, int k){
		if(l == r){
			v[k] = a[l];
			return;
		}
		int m = (l + r) >> 1;
		build(l, m, k << 1);
		build(m + 1, r, k << 1 | 1);
		update(k);
	}
	void modify(int ql, int qr, int l, int r, int k, int d){
		if(l == ql && r == qr){
			v[k] += d;
			lazy[k] += d;
			return;
		}
		pushdown(l, r, k);
		int m = (l + r) >> 1;
		if(ql <= m)
			modify(ql, min(qr, m), l, m, k << 1, d);
		if(qr > m)
			modify(max(ql, m + 1), qr, m + 1, r, k << 1 | 1, d);
		update(k);
	}
	ll query(int ql, int qr, int l, int r, int k){
		if(l == ql && r == qr)
			return v[k];
		pushdown(l, r, k);
		int m = (l + r) >> 1;
		ll ans = (1 << 31) - 1;
		if(ql <= m)
			ans = min(ans, query(ql, min(qr, m), l, m, k << 1));
		if(qr > m)
			ans = min(ans, query(max(ql, m + 1), qr, m + 1, r, k << 1 | 1));
		return ans;
	}
};

int t[N], s[N];

segtree tr;

int main(){
	n = rd(), m = rd(), r = rd();
	for(int i = 1 ; i <= m ; i++){
		int x, y, z;
		x = rd(), y = rd(), z = 1;
		add(y, x, z);
	}
	dij(n);
	for(int i = 1 ; i <= n ; i++){
		s[i] = rd();
		t[s[i]] = i - 1;
		tr.a[s[i]] = d[s[i]] + t[s[i]];
	}
	tr.build(1, n, 1);
	while(r--){
		int x = rd(), y = rd();
		int c = t[s[y]] - t[s[x]];
		tr.modify(s[x], s[x], 1, n, 1, c);
		tr.modify(s[y], s[y], 1, n, 1, -c);
		swap(t[s[x]], t[s[y]]); swap(s[x], s[y]);
		printf("%lld\n", tr.query(1, n, 1, n, 1));
	}
	return 0;
}

```

---

## 作者：_zuoqingyuan (赞：1)

今天模拟赛挂了 $200$ 分，这题贡献了 $100$。

# 思路分析

首先有一个结论：“我”的行为一定是**从 $1$ 号点坐一段地铁，然后在某个点下车，步行走到学校**。

这个结论很好证明。

首先，不坐地铁纯步行可以看做从 $1$ 号点上地铁，然后 $1$ 号点下地铁，步行去学校。

然后证明坐地铁一定是从 $1$ 号点开始坐：假设我们步行到点 $u$，在 $t_u$ 这个时刻坐上地铁（一定是恰好卡点坐上地铁，不然一定不是最优方案）。因为恰好在 $t_u$ 这个时刻地铁到达点 $u$，所以“我”其实可以直接从 $1$ 号点坐到 $u$ 号点，用时是一样的，一定不会更劣。

再然后证明下了一次地铁后一定不会再上地铁：假设坐地铁到 $u$ 点下车，步行到 $v$ 点上车，最后坐到 $w$ 点下车。其实不如直接从点 $u$ 坐到点 $w$，用时是一样的。

证明了最开始的结论，我们想办法表示出 $1$ 到 $n$ 的最短路。

设 $d_x$ 表示从 $x$ 出发到 $n$ 的最短距离，$p_x$ 表示 $x$ 在地铁线中的位置，那么从 $1$ 到 $n$ 在 $x$ 下车的最短路可以表示为 $d_x+p_x-1$。
$d_x,p_x$ 均可以预处理得出（$d_x$ 可以通过建反图 BFS 得来）。

考虑修改操作：首先可以明确的是，修改操作只会修改 $p_x$ 的值，$d_x+1$ 值是不变的。可以任意选择一个支持单点修改，全局最大的数据结构来维护信息。

这里给出一种优先队列（priority_queue）的写法。

预处理出所有 $d_x+p_x-1$，将三元组 $(d_x+p_x-1,x,p_x)$ 插入到优先队列 $q$ 中。

对于每一次修改操作 $x,y$，我们首先交换 $p_x,p_y$ 的值，然后将更新后的值插入 $q$ 中。随后取出队头 $(d_u+p_u'-1,u,p_u')$，如果满足 $p_{u}'=p_{u}$（即这个状态自入队以来，没有被交换过），输出三元组的第一项，否则不断弹出队头，直到队头合法为止。

BFS 时间复杂度 $O(n)$，优先队列时间复杂度 $O(n\log n)$。可以通过本题。

# Code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define mp make_pair
using namespace std;
const int N=2e5+10,M=2e6+10;
int n,m,d,ver[N],to[M],nxt[M],idx,dis[N],mk[N],ans,s[N];
queue<int>q;
void add(int x,int y){
	to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx;
}
priority_queue<pair<int,pair<int,int>>>Q;
int main(){
	scanf("%d %d %d",&n,&m,&d);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d %d",&u,&v);
		add(v,u);
	}
	memset(dis,0x3f,sizeof(dis));
	memset(mk,0,sizeof(mk));
	q.push(n);dis[n]=0;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=ver[x];i;i=nxt[i]){
			int y=to[i];
			if(mk[y])continue;
			mk[y]=1;
			dis[y]=dis[x]+1;
			q.push(y); 
		}
	} 
	for(int i=1;i<=n;i++){
		scanf("%d",s+i);
		Q.push(mp(-(dis[s[i]]+i-1),mp(s[i],i))); 
	}
	for(int i=1,u,v;i<=d;i++){
		scanf("%d %d",&u,&v);
		swap(s[u],s[v]);
		Q.push(mp(-(u+dis[s[u]]-1),mp(s[u],u)));
		Q.push(mp(-(v+dis[s[v]]-1),mp(s[v],v))); 
		while(Q.size()&&s[Q.top().second.second]!=Q.top().second.first)Q.pop();
		ans=-Q.top().first;
		printf("%d\n",ans);
	}
	return 0;
}
```

如有错误，请指出。

---

## 作者：double_wings (赞：1)

# P9026题解
## 题目大意 
 题目中已很清楚，无非交换（永久）加查询最小值。
 题解中为最短路等数据结构，经机房巨佬想法，查询，修改，最小值，来一发**线段树**。
##  构图
![](https://cdn.luogu.com.cn/upload/image_hosting/vyc3zue6.png)
为了鲜明，路径不在同一条直线上。

根据题意这是一个**单向图**，图中蓝线代表人行道，橙线代表列车运行轨道。（根据样例）。
## 想法及做法
根据题意可判断，人可以先坐车后走路，也可以直接坐车做到底，通过线段树将坐车的时间与走路的时间拼在一起进行区间求最小值。
首先需**宽搜**将所有路径进行处理，在交换之后再进行线段树的**区间查询**，如果全程每交换一次就进行一次宽搜会加大复杂度。

对于交换的 $x$ 和 $y$，我们知道坐车时到第 $n$ 个点的时间为 $n-1$，所以根据线段树的单点修改（也就是下面代码里的 $change$ 函数
）来维护，交换后，上一次加上的 $x-1$ 此时就需要先减了在往上加一个 $y-1$。
最后通过区间查询找最小值即可。
## 代码
```cpp


#include<bits/stdc++.h>
using namespace std;
const int M = 10000010;
const int N = 10000010;
const long long mod = 1e9+7;
int read() {
    int s=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return s*f;
}
int n,m,q,head[1000010];
struct edge{int nex,to;}e[M];
void add(int u,int v) {
    static int tot = 0;
    e[++ tot].to = v;
    
    e[tot].nex = head[u];
    head[u] = tot;
}
int dis[500100],vis[500100];
void bfs(){
    for(int i = 1;i <=n; i++)dis[i] = 1e9+7;
    dis[n] = 0;
    queue<int>q;q.push(n);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int i = head[u];i;i = e[i].nex){
            int v = e[i].to;
            if(dis[v] == 1e9+7){
                dis[v] = dis[u]+1;
                q.push(v);
            }
        }
    }
}
struct tree{
    int l,r;
    long long mi;
}t[2000100];
void build(int p,int L,int R){
    t[p].l = L;t[p].r = R;
    if(L == R){
        t[p].mi = dis[L];
        return ;
    }
    int mid = (L+R)>>1;
    build(p*2,L,mid);build(p*2+1,mid+1,R);
    t[p].mi = min(t[p*2].mi,t[p*2+1].mi);
}
void change(int p,int x,int k){//单点修改
    if(t[p].l == t[p].r){
        t[p].mi+=k;
        return ;
    }  
    int mid=(t[p].l+t[p].r)>>1;
    if(x<=mid) change(p*2,x,k);
    if(mid+1<=x) change(p*2+1,x,k);
    t[p].mi = min(t[p*2].mi,t[p*2+1].mi);
}
int a[500010],rnk[1000010];
int main(){
    n =read();m = read();q = read();
    for(int i=1;i<=m;i++){
        int x,y;
        x = read();y = read();
        add(y,x);
    }
    bfs();
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        a[i] = read();
        change(1,a[i],i-1);
        rnk[a[i]] = i;
    }
    for(int i=1;i<=q;i++){
        int x,y;
        x= read();y = read();
        change(1,a[x],-(x-1));change(1,a[y],-(y-1));
        change(1,a[x],y-1);change(1,a[y],x-1);
        swap(a[x],a[y]);
        cout<<t[1].mi<<endl;
    }
}
```


---

## 作者：凤年 (赞：1)

把整个路程分成两段，一段是坐车走的，一段时候下车以后走的。为啥分两段呢？如果先坐车再走最后还坐车，当第二次可以上车的时候说明车和人是同时到达该点，那为什么不直接简化成一直坐车呢？

我们直接倒着求出 $i$ 到 $n$ 的距离，把它和 $1$ 到 $i$ 坐公交车的时间拼起来即为当前图的最短路。

假如交换之前是这样的（这里用 $x$ 和 $y$ 代替了 $s_x$ 和 $s_y$）：
![](https://s3.bmp.ovh/imgs/2023/06/04/7b45d54f3a002fbe.png)

交换之后是这样：
![](https://s3.bmp.ovh/imgs/2023/06/04/91ed66ca29ca642a.png)

$x$ 和 $y$ 点交换之后不影响它们到终点的时间，只会影响从起点到它们的时间。

原来的两个点被交换以后从起点经过它们到终点的路就被拆了，同时新建了两条新的路径。

因此我们需要数据结构，它能维护关于所有路径的删除操作，且需要查询最短的路径，这不是一颗平衡树吗？但是只需要删除和查询，那就用堆和字典搞一个低配，用字典标记，堆查询最小！

```cpp
#include <bits/stdc++.h>
#define N 200001
#define M 200001
#define pos first
#define tim second
using namespace std;

int n, m, d;

unordered_map<int,int>mp;
priority_queue<int, vector<int>, greater<int>>pq;

bool vis[N];
int head[N << 1], pre[N], last[N], s[N], dis[N << 1];
struct edge{int nex,to,val;}e[M << 1];
void add(int u,int v, int w) {
	static int tot = 0;
	e[++tot].to = v;
	e[tot].nex = head[u];
	e[tot].val = w;
	head[u] = tot;
}

int read() {
	int s=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return s*f;
}

void bfs() {
	queue<int>q;
	memset(dis, 0x3f, sizeof(dis));
	q.push(n);
	dis[n] = 0;
    vis[n] = 1;
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i = head[now]; i; i = e[i].nex) {
			int to = e[i].to;
			if(vis[to]) continue;
			if(dis[to] > dis[now] + e[i].val) {
				dis[to] = dis[now] + e[i].val;
				q.push(to);
			}
		}
	}
	return;
}

int main() {
	n = read(), m = read(), d = read();
	for(int i = 1, u, v;i <= m; ++i) {
		u = read(), v = read();
		add(v, u, 1);
	}

	for(int i = 1;i <= n; ++i) s[i] = read();

    bfs();//跑i到n的最短路

    for(int i = 1;i <= n; ++i)
        pq.push(dis[s[i]] + i - 1);//i - 1表示第i个点到原点的距离
	for(int i = 1, x, y;i <= d; ++i) {
		x = read(), y = read();
        ++mp[dis[s[x]] + x - 1];
        ++mp[dis[s[y]] + y - 1];//标记拆掉的两条路

		swap(s[x], s[y]);

        pq.push(dis[s[x]] + x - 1);
        pq.push(dis[s[y]] + y - 1);//把两条新路加入

        while(mp.find(pq.top()) != mp.end()) {//如果最短路径被删了就不要
            int now = pq.top();
            pq.pop();
            --mp[now];
            if(!mp[now]) mp.erase(now);
        }
        printf("%d\n", pq.top());
	}
	return 0;
}
```


---

## 作者：jinfanhao (赞：1)

这道题的思路特别难想。\
首先，考虑路径方案。

1. 先走路又坐地铁。这样会等地铁，对不对，就会导致时间拖延。
2. 先做地铁又走路。这样可以一开始就坐地铁，不会有任何拖延。

接下来因为地铁会有改动，走路不会改动，所以走路可以预处理好，记得建反图。\
后面地铁的用个优先队列维护，记住这个地点和编号，到后面看看还是不是，如果是，那么中转点就是他。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,m,k,op[N],dist[N];
bool ok[N];
queue<int> q;
struct ANS{
	int pos,id;
	bool operator<(const ANS &x) const{
		return pos-1+dist[id]>x.pos-1+dist[x.id];
	}
};
priority_queue<ANS> pq;
vector<int> g[N];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1; i<=m; ++i){
		int u,v;
		scanf("%lld%lld",&u,&v);
		g[v].push_back(u);
	}
	for(int i=1; i<=n; ++i){
		dist[i]=1e9;
		ok[i]=false;
	}
	q.push(n);
	ok[n]=true;
	dist[n]=0;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0; i<g[u].size(); ++i){
			if(dist[u]+1<dist[g[u][i]]){
				dist[g[u][i]]=dist[u]+1;
				ok[g[u][i]]=true;
				q.push(g[u][i]);
			}
		}
	}
	for(int i=1; i<=n; ++i){
		scanf("%lld",&op[i]);
		pq.push({i,op[i]});
	}
	while(k--){
		int u,v;
		scanf("%lld%lld",&u,&v);
		swap(op[u],op[v]);
		pq.push({u,op[u]});
		pq.push({v,op[v]});
		while(op[pq.top().pos]!=pq.top().id)pq.pop();
		ANS x=pq.top();
		printf("%lld\n",x.pos-1+dist[x.id]);
	}
	return 0;
} 
```

---

## 作者：sieve (赞：0)

# 题解：[P9026 [CCC2021 S4] Daily Commute](https://www.luogu.com.cn/problem/P9026)

## 思路

我们可以想到 $O(ND)$ 的暴力，这个并不难想，但是数据加强了，过不了，所以这里先不讲这个。

我们在求出最短路后，难点在于无法去除 $O(D)$ 的最小值询问。那么，在动态修改的时候求最小值，我们自然就想到了优先队列。

但是我们使用优先队列时，无法做到删除指定元素，~~手写堆当我没说~~，如果可以做到，时间将会来到 $O(N \log D)$。

我们先求出 $n$ 到所有点的最短路，然后，我们定义一个结构体，里面存的是优先队列答案。其中的 $pos$ 表示几号站点（地铁），其中的 $id$ 表示 $s_{pos}$。那么，时间就是等待的时间（$dis_{pos} - 1$），加上坐车的时间（$dis_{id}$）。那么，我们可以先把所有的站点放进去，然后每次交换的时候，把交换完的放回去，然后判断是否合法（$s_{pos} = id$），因为这是我们定义的东西。只要最顶端的不满足，就丢出去。最后输出的自然就是上面的答案了。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,w,d;
int s[N],dis[N];
bool vis[N];
vector<int> g[N];
struct no{
    int id,w;
    bool operator <(const no& b) const
    {
        return w>b.w;
    }
};
struct ANS{
    int pos,id;
    bool operator <(const ANS& b) const
    {
        return pos-1+dis[id]>b.pos-1+dis[b.id];
    }
};
priority_queue<ANS> ans;
void dijkstra(int s)
{
    for(int i=1;i<=n;++i)
    {
        dis[i]=inf;
        vis[i]=0;
    }
    priority_queue<no> q;
    q.push({s,0});
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.top().id;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto v:g[u])
        {
            if(!vis[v]&&dis[v]>dis[u]+1)
            {
                dis[v]=dis[u]+1;
                q.push({v,dis[v]});
            }
        }
    }
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>w>>d;
    for(int i=1;i<=w;++i)
    {
        int x,y;
        cin>>x>>y;
        g[y].push_back(x);
    }
    dijkstra(n);
    for(int i=1;i<=n;++i) cin>>s[i],ans.push({i,s[i]});
    for(int i=1;i<=d;++i)
    {
        int x,y;
        cin>>x>>y;
        swap(s[x],s[y]);
        ans.push({x,s[x]});
        ans.push({y,s[y]});
        while(s[ans.top().pos]!=ans.top().id) ans.pop();
        cout<<ans.top().pos-1+dis[ans.top().id]<<'\n';
    }
    return 0;
}
```

---

## 作者：syLph (赞：0)

一道小小清新题。

首先我们要发现一件非常重要的事：最多坐一次地铁。仔细想想可以发现如果坐超过一次地铁，那么我们在换乘时，可能需要在某个地铁站等待地铁到达该站，所以此时我们可以选择一直乘坐地铁，这样就省去了等待的时间。这种方案一定更优。（形象、生动）

然后我们建反图，预处理出终点到每个点之间的距离 $dist_i$。因为每条路径就是在原图上的一条路径的长度和乘坐地铁长度之和，使用小根堆维护答案（线段树也行）。

时间复杂度 $O(n\log{n})$。

Code:

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<memory.h>
using namespace std;
const int maxn = 200100;
inline int read(){
    char c = getchar(); int x = 0,f = 1;
    while('0' > c || c > '9'){if(c == '-')f = -1;c = getchar();}
    while('0' <= c && c <= '9'){x = x * 10 + c - '0',c = getchar();}
    return x * f;
}
struct aa{int len,p,day;const bool operator>(const aa& x) const{return len>x.len;}};
priority_queue<aa,vector<aa>,greater<aa> > qq;
int n,w,d,nxt[maxn],head[maxn],ver[maxn],tot = 1,dist[maxn],s[maxn],a[maxn];
void add(int x,int y){ver[++tot] = y,nxt[tot] = head[x],head[x] = tot;}
int main(){
    //freopen("testdata.in","r",stdin);
    n = read(),w = read(),d = read();
    for(int i = 0 ; i < w ; i ++){int u = read(),v = read();add(v,u); }
    queue<int> q; q.push(n); memset(dist,0x3f,sizeof dist); dist[n] = 0;
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(int i = head[x] ; i ; i = nxt[i])
            if(dist[ver[i]] == 0x3f3f3f3f)
                dist[ver[i]] = dist[x] + 1,q.push(ver[i]);
    }
    for(int i = 1 ; i <= n ; i ++) s[i] = read();
    for(int i = 1 ; i <= n ; i++) qq.push({i+dist[s[i]]-1,s[i],0});
	for(int i = 1,u,v ; i <= d ; i ++){
		u = read(),v = read(); 
		qq.push({v+dist[s[u]]-1,s[u],++a[s[u]]});
		qq.push({u+dist[s[v]]-1,s[v],++a[s[v]]});
		swap(s[u],s[v]);
		while(qq.top().day!=a[qq.top().p]) qq.pop();
		printf("%d\n",qq.top().len);
	}
    return 0;
}
```

---

