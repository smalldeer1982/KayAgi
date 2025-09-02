# Monsters

## 题目描述

There is an undirected graph with $ n $ vertices and $ m $ edges. Initially, for each vertex $ i $ , there is a monster with danger $ a_{i} $ on that vertex. For a monster with danger $ a_{i} $ , you can defeat it if and only if you have defeated at least $ a_{i} $ other monsters before.

Now you want to defeat all the monsters. First, you choose some vertex $ s $ and defeat the monster on that vertex (since you haven't defeated any monsters before, $ a_{s} $ has to be $ 0 $ ). Then, you can move through the edges. If you want to move from vertex $ u $ to vertex $ v $ , then the following must hold: either the monster on vertex $ v $ has been defeated before, or you can defeat it now. For the second case, you defeat the monster on vertex $ v $ and reach vertex $ v $ .

You can pass the vertices and the edges any number of times. Determine whether you can defeat all the monsters or not.

## 说明/提示

In the first test case, you can start at vertex $ 3 $ and defeat the monster on it, before you go to vertices $ 2 $ , $ 1 $ in this order, defeating the monsters on them as well. Then you return to vertex $ 3 $ , and go to vertex $ 4 $ , defeating the monster on it.

In the third test case, there is no path to vertex $ 4 $ if you start at vertex $ 1 $ . Also, there is no path to vertices $ 1 $ , $ 2 $ , and $ 3 $ if you start at vertex $ 4 $ .

## 样例 #1

### 输入

```
5
4 3
2 1 0 3
1 2
2 3
3 4
6 6
0 1 2 3 0 1
1 2
2 3
3 4
4 5
4 6
5 6
4 3
0 1 2 0
1 2
2 3
1 3
4 6
1 1 1 0
1 2
3 2
4 3
2 4
4 1
1 3
5 5
0 1 3 2 0
1 2
2 3
3 4
4 5
3 5```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：Graygoo (赞：8)

我怀疑 T 宝就是一直在想你们这些均摊做法才没做出来的。实际上有一个没啥思维量的做法，就是首先考虑点权转边权，边权是两个点权最大值，然后条件改成打过的怪数量必须大于等于边权才能走这条边。然后就是老生常谈地建立 kruskal 重构树，在重构树上一条边能走条件就是子树大小大于等于这条边原边权，然后按照这个条件搜下去，能遍历到权值为 $0$ 的点就说明可行，否则显然不可行。

这玩意又好想好写复杂度还是一个 log 的，比官解优秀。

---

## 作者：__Aaaaaaaa (赞：8)

题面翻译：给定一张 $n$ 个点 $m$ 条边的无向图，对于每个点 $i$ 上都有一个怪兽，其危险性为 $a_i$，玩家可以选择任意一个点作为出生点，然后开始跑图打怪，每个点和边都可以重复经过，在走到点 $i$ 上的时候，必须保证已经打了 $a_i$ 个怪了，也就是说出生点的怪物的危险性必须是 $0$，判定玩家能否找到一种方案打败所有怪兽。

Solution：  
个人认为这道题的难度至少是蓝(比赛时没做出来)。  
不难想到暴力的解法：对于每一个危险度为 $0$ 的怪物，都从它开始跑一边图（可以用类似 Djkstra 的算法进行优化，每次选的新怪兽一定是所有可以一步到达的怪物的危险度最小的，详见代码中的 work 函数），然后判定是否存在一个出生点点满足打完所有怪的标准。  
此暴力算法和正解竟然十分接近：只需要增加一个步骤那就是判定所选出生点是否被走到过（即之前就存在一个出生点可以走到这个出生点但是不能打败所有的怪兽）。  

浅证一下：  
令一个集合 $D(u)$ 表示以 $u$ 为出生点，可以走到的所有的点集（若 $a_i \neq 0$ 则 $D(i) = \varnothing $ )，可以找到一个读者可以自证~~不难~~的结论：若 $y\in D(u)$，则 $D(y) \in D(u)$  
那么对于一个可以作为起始点的点 $x$，若它之前已经被访问过，即存在一个点 $y$，$y$ 作为出生点可以到达 $x$ 但不能到达所有点，那么 $ D(x)\in D(y) \notni {1,2,3...n} $，则没有必要考虑重新从 $x$ 开始搜索。  
下面证明一下时间复杂度：  
如果同一个点被加入了两个 $D$，设这两个出生点为 $x$ 和 $y$，$A=|D(x)|$，$B=|D(y)|$，且不妨 $A\leq B$，那么说明 $y$ 可以走到 $x$ 但 $x$ 不能走到 $y$，也就是说 $D(x)$ 中的点可以一步到达一些点，这些点的 $a$ 值大于 $A$，但是 $y$ 却攻破了这层防线，说明 $2 \times A\leq B$，也就是说，对于每一个点，这个点最多会被添加进入 $\log_2 n$ 个 $D$ 中，时间复杂度最坏就是 $O(n\log_2 n)$。


### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10;
int n,m,a[N],vis[N];
vector<int>E[N];
priority_queue<PII,vector<PII>,greater<PII> >u;
bool work(int p){
	while(!u.empty())
		u.pop();
	u.push(PII(a[p],p));
	int cnt=0;//当前已经战胜了多少怪物
	while(!u.empty()){
		int x=u.top().se;//选择当前危险度最低且可以到达的点
		u.pop();
		if(vis[x]==p)continue;
		vis[x]=p;
		if(a[x]>cnt)return 0;//如果当前点是可以一步到达的危险度最小的怪物并且依旧无法战胜，则说明从p开始打怪是一定无解的
		cnt++;
		for(int i=0;i<E[x].size();i++){
			int j=E[x][i];
			if(vis[j]<p){
				u.push(PII(a[j],j));//这个点还没有被搜过，存入堆中
			}
		}
	}
	return cnt==n;//判定能够到达的点是否和总点数相等
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i),vis[i]=0,E[i].clear();
		for(int i=1,x,y;i<=m;i++){
			scanf("%d%d",&x,&y);
			E[x].push_back(y);
			E[y].push_back(x);
		}
		for(int i=1;i<=n;i++){
			if(a[i]==0&&vis[i]==0){//这个点还没有被到达过且这个点可以作为出生点
				if(work(i)){
					puts("YES");
					break;
				}
			}
			if(i==n)
				puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：tyr_04 (赞：7)

[传送门](https://www.luogu.com.cn/problem/CF1810E)

非常好的图论题，使 04 的大脑旋转，场上 all in 这道题，码了一个并查集 + set + 启发式合并的做法，发现 TLE 了（思路可能都伪了），场下才发现原来正解那么巧妙。

### 题意

给定一张无向图（不一定连通），每个点有点权。任选一个点权为 $0$ 的点做起点，能去往下一个未经过且有边相连的点当且仅当目前经过的点数大于等于要去往的点的点权（可以在经过的点中相互穿梭），问能否遍历完整张图？

### 思路

考虑暴力，从每个点权为 $0$ 的点开始按 kruskal 的方法跑一遍，能到达所有点则有解，时间复杂度 $O(n^2 \log n)$。

考虑优化，如果以一个点为起点时在遍历的过程中经过另一个点权为 $0$ 的点，打上标记，并不再以经过的点为起点遍历整张图。

思考正确性，如果从某个点开始遍历不能遍历完整张图，遍历过程中经过的起点可到达的点集一定被包含。通俗一点，可以理解为以经过的点为起点时，遍历前已经走过了一些点，但仍无法遍历完整张图，而从 $0$ 开始能到达的点一定更少，因此也无解。

分析复杂度，若从 $x$ 为起点时可以到达起点 $y$，以 $y$ 为起点时不能到达起点 $x$，则 $x$ 能到达 $y$ 能到达的所有点。又因为从 $x$ 走过某条边去往 $y$ 点集中的某个点前经过的点数大于 $y$（不然走不了这条边）。所以以 $x$ 为起点经过的点集大小大于以 $y$ 为起点经过的点集大小的两倍，那么每个点最多遍历 $\log n$ 次，再乘上 kruskal 的复杂度，时间复杂度 $O(n \log^2 n)$。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],ans=0;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
bool z[200005],jl[200005];
vector<int> v[200005];
bool check(int x)
{
	while(!q.empty())
	{
		q.pop();
	}
	for(int i=1;i<=n;i++)
	{
		z[i]=0;
	}
	int sum=0;
	q.push({a[x],x});
	z[x]=1;
	while(!q.empty())
	{
		pair<int,int> u=q.top();
		q.pop();
		if(u.first==0)
		{
			jl[u.second]=1;
		}
		if(sum<u.first)
		{
			break;
		}
		sum++;
		for(int i=0;i<v[u.second].size();i++)
		{
			int y=v[u.second][i];
			if(z[y]==0)
			{
				q.push({a[y],y});
				z[y]=1;
			}
		}
	}
	if(sum==n)
	{
		return 1;
	}
	return 0;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			jl[i]=0;
			v[i].clear();
		}
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i]==0&&jl[i]==0)
			{
				if(check(i)==1)
				{
					ans=1;
					break;
				}
			}
		}
		if(ans==1)
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：4)

这题我其实是暴力优化水过的（（（

首先先来考虑只有一个点为 $0$ 的情况，我们创建一个优先队列，存的是能到的点，按照怪兽等级升序。

第一次把那个为 $0$ 的点放到优先队列里，每轮取出队首，如果能到就去，自己的等级也加一，不能到就结束了。

现在有很多个权值为 $0$ 的点，如果我们都那样干就会超时，这时有一个神奇优化：

我们还是一个个枚举权值为 $0$ 的点，但是如果这个点被之前的权值 $0$ 的点遍历到了，我们就没有必要再去遍历它了，剪枝显然正确。 

感觉时间复杂度是 $n\sqrt{n}$ 但是证明好像简单，我却不会。

代码（第一次没加剪枝就交了，白送 $50$ pts，不过排名损失并不大。）：

```cpp
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
int t, n, m;
int x, y, cnt;
int a[200005];
bool vis[200005], ans, c[200005];
priority_queue <pair<int, int>, vector <pair<int, int> >, greater <pair<int, int> > > q;
vector <int> v[200005];
void init () {
	for (int i = 1; i <= n; i ++) vis[i] = false;
	while (!q.empty () ) q.pop();
}
int main () {
	cin >> t;
	while (t --) {
		ans = false;
		cin >> n >> m;
		for (int i = 1; i <= n; i ++) v[i].clear();
		for (int i = 1; i <= n; i ++) c[i] = false;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i <= m; i ++) {
			cin >> x >> y;
			v[x].push_back (y);
			v[y].push_back (x);
		}
		for (int i = 1; i <= n; i ++) {
			if (a[i] != 0 || c[i]) continue;
			c[i] = true;
			init ();
			cnt = 0;
			q.push (make_pair (0, i) );
			while (!q.empty () ) {
				x = q.top ().first;
				y = q.top ().second;
				if (x == 0) c[y] = true;
				q.pop ();
				if (x > cnt || vis[y]) continue;
				++ cnt;
				swap (x, y);
				vis[x] = true;
				for (int i = 0; i < v[x].size (); i ++) {
					if (!vis[v[x][i] ]) q.push (make_pair (a[v[x][i] ], v[x][i]) );
				}
			}
			bool f = false;
			for (int i = 1; i <= n; i ++) {
				if (!vis[i]) {
					f = true;
					break;
				}
			}
			if (!f) ans = true;
		}
		if (ans) cout << "Yes" << "\n";
		else cout << "No" << "\n";
	}
	return 0;
}
```


---

## 作者：小木虫 (赞：3)

### Preface  
比较有意思的图论问题，如果您还没思考超过 15 min 不建议阅读题解，否则您可能会失去这道题的精华所在。  
### Problem  
给你一个 $n$ 个点的无向图 $E$，每个点有点权 $a_i$，你可以任意选一个点权为 0 的点为开始子图 $G$，然后每次操作，你可以选择任意一个与该子图相邻的节点 $u$，若 $a_u \leq |G|$，则该点可以被击败，你可以将该点加入子图。  

现在问你你是否有一种方案可以通过若干次如上操作将 $G$ 变为 $E$。  

$n,m \leq2\times 10^5 \space ,0\leq a_i\leq n$。  

### Solution  
首先，若我们已经选定了一个初始点 $s$，那么按照如下类似于 Prim 算法的策略来构造 $G$ 肯定是最优的：  

不断选择与 $G$ 相邻的点中点权最小的点加入 $G$，直到不能加入。  

这个过程显然是可以进行堆优化的，我们可以枚举每一个起始点来进行运算，复杂度 $O(n^2 \log n)$，不够优秀。  

但是你如果考虑，这个类似于 Prim 算法的贪心策略所建出的生成树，这样可能会便于您之后的阅读和思考。

如果我们有能力通过另外一个起始点建出的子图 $G'$ 来到达 $G$ 中的一个节点 $u$，那么这意味着 $G'$ 的大小已经达到了 $G$ 加入 $u$ 之前的规模，那么我们就有能力将 $G$ 中的点全部收入囊中，读者可以意会一下，$G$ 加入 $u$ 之前的版本的规模严格小于 $G'$，我们就可以从 $u$ 开始层层递进将这一部分的点加入，而剩下的点我们可以通过与建 $G$ 时一样的策略来加入。  

简而言之，如果说我们进行多路增广的贪心策略，而且两个起始点建出的子图在某个点相遇了，那么这两个子图就可以进行合并。  

于是我们一个一个枚举起始点，遇到了之前建出的子图就合并记录信息的堆和并查集，最后观察是否所有子图合并为一个且包括所有点。  

你要是朴素地合并的话就只能做到 $O(n^2 \log n)$。  
启发式合并可以做到 $O(n \log^2 n)$。  
而你要是把堆换成线段树进行线段树合并则可以做到更优秀的 $O(n \log n)$。  

启发式合并算法 code：  
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define endl "\n"
using namespace std;
const int N=2e5+10;
int T,n,m,val[N],u,v,fa[N],sz[N];
vector <int> edge[N];
priority_queue < pair<int,int> > Q[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void init(){
	for(int i=1;i<=n;i++)
		while(Q[i].size())Q[i].pop();
	for(int i=1;i<=n;i++)
		edge[i].clear();
}
void merge(int x,int y){
	y=find(y);fa[y]=x;sz[x]+=sz[y];
	if(Q[x].size()<Q[y].size())
		swap(Q[x],Q[y]);
	while(Q[y].size())
		Q[x].push(Q[y].top()),Q[y].pop();
}
void sim_prim(int s){
	while(Q[s].size()){
		int u=Q[s].top().sec;
		//cout<<u<<endl;
		int w=-Q[s].top().fir;
		if(w>sz[s])break;Q[s].pop();
		if(find(u)==s)continue;merge(s,u);
		for(auto v:edge[u]){
			if(find(v)==s)continue;
			Q[s].push(mp(-val[v],v));
		}//cout<<Q[s].size()<<endl;
	}
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		edge[u].pb(v);
		edge[v].pb(u);
		Q[u].push(mp(-val[v],v));
		Q[v].push(mp(-val[u],u));
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==i&&val[i]==0)
			sim_prim(i);
	}int MAX=0;
	for(int i=1;i<=n;i++)
		MAX=max(MAX,sz[i]);
	//cout<<"YES"<<endl;
	//cout<<MAX<<endl;
	if(MAX==n)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：Register_int (赞：3)

我一看这不是 [Fighter Takashi](/problem/AT_abc319_f) 的第二步吗？于是我就跑来写题解了。

首先发现我们打出来的一定是一个连通块，所以每次拓展都是选与这个连通块相邻的点。在广搜的同时贪心，有限拓展 $a_i$ 较小的点，无法拓展直接返回即可。

不过这题有多个点可以作为出发点。有一个显然的结论：如果一个起始点 $u$ 能拓展到的点集 $S_u$ 包含了另一个起始点 $v$，则必有 $S_v\subseteq S_u$。感性理解一下就是你到达 $v$ 时怪物比 $0$ 多一定不劣。如果一个点能被两个起始点的点集包含到，并且 $v\notin S_u$，则说明 $u$ 在拓展进 $S_v$ 前已经有了 $|S_u|>|S_v|$，所以 $|S_u|>2|S_v|$。可以发现，由于有这个限制，一个点最多被加进 $\log n$ 个点集中。所以暴力的复杂度是对的！时间复杂度 $O((n+m)\log^2 n)$，可以通过。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct node {
	int u, d;
	bool operator < (const node &rhs) const { return d > rhs.d; }
}; priority_queue<node> q;

vector<int> g[MAXN]; int a[MAXN], vis[MAXN];

int bfs(int s) {
	int ans = 0;
	for (; !q.empty(); q.pop()); vis[s] = s, q.push({ s, 0 });
	for (int u; !q.empty();) {
		u = q.top().u, q.pop();
		if (a[u] > ans) break; ans++;
		for (int v : g[u]) if (vis[v] != s) vis[v] = s, q.push({ v, a[v] });
	}
	return ans;
}

int t, n, m, ans;

int main() {
    for (scanf("%d", &t); t--;) {
    	scanf("%d%d", &n, &m), ans = 0;
    	for (int i = 1; i <= n; i++) g[i].clear(), vis[i] = 0;
    	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), g[u].push_back(v), g[v].push_back(u);
    	for (int i = 1; i <= n; i++) if (!vis[i]) ans = max(ans, bfs(i));
    	puts(ans == n ? "Yes" : "No");
	}
}
```

---

## 作者：masonpop (赞：2)

非常妙的图论题。

首先考虑确定了起始点怎么做。显然，我们可以枚举当前已经扩展到的点能一步到达的节点，再贪心的击杀 $a_i$ 最小的点，若无法操作则无解。运用堆优化可以做到 $O(n\log n)$。

但是从所有 $a_i=0$ 的点出发搜一遍复杂度高达 $O(n^2\log n)$，需要优化。我们可以想到一个小优化：**如果两个点 $x,y$ 满足 $a_x=a_y=0$，且从 $x$ 出发能到 $y$，那么 $y$ 能到达的点 $x$ 均能到达**。正确性是显然的，因为你从 $x$ 到 $y$ 的时候已经击杀了一定数量的怪，再从 $y$ 出发杀怪一定会比直接从 $y$ 出发更优。因此，如果一个起点被其它起点到达过，就可以不搜这个起点。

这看似是个小优化，但是，**复杂度是对的**。下对复杂度进行感性证明。

对于所有起点，设 $S(x)$ 表示从 $x$ 出发能到达的点的集合。如果同一个点同时包含在 $S(x),S(y)$ 中，不妨设 $y$ 是我们后遍历的起点。那么说明，**$x$ 不能到达 $y$ 而 $y$ 可以到达 $x$。** 根据这一点，我们可以推断：$|S(y)|\ge 2|S(x)|$。文字不好解释，看图就十分清晰了：

![](https://cdn.luogu.com.cn/upload/image_hosting/9zn887vr.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

这样，一个点最多被加入 $O(\log n)$ 次，总复杂度就是 $O(n\log^2n)$。注意不能每次广搜时都 memset 一边，用个时间戳标记一下就行了。[代码](https://codeforces.com/contest/1810/submission/220487852)。

---

## 作者：Hisaishi_Kanade (赞：2)

解决 $a_i=0$ 的点有且仅有一个的问题是简单的，我们可以从这个点 $u$ 向周围的边扩展，显然，可以做到让扩展的点 $a_i$ 单调不降，如果最终不能扩展到 $n$ 个则无解。

对于一个 $0$ 点 $u$，设 $F(u)$ 表示以 $u$ 为起始点向周围扩展得到的最多点集合。然后直接开始搜搜搜。我们会发现存在一些点 $x$ 满足 $x\in F(u)$ 的同时也有 $x\in F(v)$。经过思考不难发现，必然会有 $F(u)\in F(v)$ 或者 $F(v)\in F(u)$。我们钦定 $u$ 是当前枚举到的 $0$ 点，则必然有 $F(v)\in F(u)$，如何证明？

我们先去掉 $F(u)$ 中与 $F(v)$ 有关的结点，此时扩展到最大我们称之为 $F^\prime (u)$。这时候，存在一些 $x$ 使得 $F^\prime (u)$ 可以向外扩展。而和 $x$ 相邻的、不属于 $F(v)$ 而属于 $F(u)$ 的 $y$，则其 $a_y> |F(v)|$，如果 $a_y<|F(v)|$，则 $F(v)$ 可以吞掉 $y$ 不符合“最大”的定义。

又因为，目前的 $F^\prime(u)$ 已经可以吞下 $y$，则 $|F^\prime (u)|\ge a_y>|F(v)|$，则 $F^\prime (u)$ 可以吞下整个 $F(v)$。

又因为 $|F(u)|= |F^\prime (u)|+|F(v)|$，可以得到 $|F(u)|>2|F(v)|$。

此时的解法已经呼之欲出了。如果有解，对于一个节点，会有 $x\in F(u_1)\in F(u_2)\cdots\in F(u_k)$，其中，由于上面关于大小的结论，$k\le \log_2 n$。那么直接开始爆搜，使用优先队列维护目前能接触的最小节点，直接就可以通过这道题，复杂度为 $O(n\log n)\times O(\log n)=O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=200005;
int vis[N], a[N];
vector<int> e[N];
int n, m, i, j, t, u, v, w;
class pii
{
public:
    int w, id;
    pii(int x=0, int y=0):w(x), id(y) {};
    inline const bool operator< (const pii &other) const
    {
        return w>other.w;
    }
};
inline const bool finished(int u)
{
	priority_queue<pii> q;
    int v, cnt=0; q.push(pii(0, u));
    while(!q.empty( ))
    {
        v=q.top().id; q.pop();
        if(vis[v]==u) continue;
        vis[v]=u;
        if(a[v]>cnt) return false;
        ++cnt;
//      printf("%d\n", v);
        for(auto nxt : e[v]) if (vis[nxt]!=u) q.push(pii(a[nxt], nxt));
    }
//  printf("%d\n", cnt);
    return cnt==n;
}
int main()
{
    scanf("%d", &t);
    nxtturn:
    while(t--)
    {
        scanf("%d %d", &n, &m);
        rep(i, 1, n) vis[i]=false;
        rep(i, 1, n) vector<int>( ).swap(e[i]);
        rep(i, 1, n) scanf("%d", a+i);
        rep(i, 1, m)
        {
            scanf("%d %d", &u, &v);
            e[u].emplace_back(v);
            e[v].emplace_back(u);
        }
        rep(i, 1, n) if(a[i]==0 && !vis[i]) if(finished(i)) {puts("YES"); goto nxtturn;}
//      rep(i, 1, n) printf("%d\n", vis[i]);
        puts("NO");
    }
}
```

---

## 作者：huangrenheluogu (赞：0)

题解做法太用脑子了，根本想不到。感觉这个方法更加好想。

思路应该是维护多个并查集，然后看是否可以用并查集里所有点推掉一个点。

于是，对于每一个联通块，需要维护外围有多少没有被推掉的，以及没有被推掉的大小，分别的位置，存到一个并查集的根节点里。

这个东西看起来就很像可并堆，于是维护一下即可。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int N = 2e5 + 5;
int T, n, m, fir[N], nxt[N << 1], son[N << 1], tot, a[N], u, v, fa[N], sz[N];
int rt[N], hh, tt, qq[N << 1], idx, tp;
vector<int> vec[N];
bool vis[N];
struct Node{
    int ls, rs, dist, x, w;
}t[N << 2], tem;
inline void add(int x, int y){
    nxt[++tot] = fir[x];
    fir[x] = tot;
    son[tot] = y;
}
inline void init(){
    for(int i = 1; i <= n; i++) fir[i] = 0;
    for(int i = 1; i <= tot; i++) nxt[i] = 0;
    for(int i = 1; i <= n; i++) vec[i].clear();
    tot = 0;
    hh = tt = 0;
    for(int i = 1; i <= n; i++) rt[i] = 0;
    idx = 0;
}
inline int getfa(int x){
    return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
inline int merge(int p, int q){
    if(!p || !q){
        return p + q;
    }
    if(t[p].w > t[q].w) swap(p, q);
    t[p].rs = merge(t[p].rs, q);
    if(t[t[p].rs].dist > t[t[p].ls].dist){
        swap(t[p].ls, t[p].rs);
    }
    t[p].dist = t[t[p].rs].dist + 1;
    return p;
}
inline void Merge(int x, int y){
    x = getfa(x), y = getfa(y);
    if(x == y) return ;
    fa[x] = y;
    sz[y] += sz[x];
    qq[++tt] = y;
    rt[y] = merge(rt[x], rt[y]);
}
inline bool cmp(int x, int y){
    return a[x] < a[y];
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1; i <= m; i++){
            scanf("%d%d", &u, &v);
            add(u, v), add(v, u);
        }
        for(int i = 1; i <= n; i++){
            fa[i] = i;
            sz[i] = 1;
            vis[i] = 0;
            if(a[i] == 0) vis[i] = 1;
        }
        for(int x = 1; x <= n; x++){
            if(a[x] == 0) qq[++tt] = x;
            for(int i = fir[x]; i ; i = nxt[i]){
                idx++;
                t[idx] = (Node){0, 0, 1, son[i], a[son[i]]};
                rt[x] = merge(rt[x], idx);
            }
        }
        #define X getfa(qq[hh])
        while(hh < tt){
            hh++;
            tp = rt[X];
            while(tp && t[tp].w <= sz[getfa(X)]){
                rt[X] = merge(t[rt[X]].ls, t[rt[X]].rs);
                Merge(t[tp].x, X);
                tp = rt[X];
            }
        }
        #undef X
        puts(sz[getfa(1)] == n ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1810E)

## 思路

- 首先不难想出本题是一道**广搜**题，但是不同的是这题需要我们在搜索的时候，将怪兽的等级从小到大进行搜索，这个时候如果我们每次进行排序的话会十分浪费时间了，所以我们可以用**优先队列**来处理。

- 确定了算法，接下来我们就可以开始想写法了。起初，队列中只有起点 $S$ 和它对应的 $v$ 的值 $0$ （**起点必须从 $a_u$ 为 $0$ 的点开始搜索**），通过我们不断**取出 $v$ 值最小的二元组**，最后判断是否走过所有的点就解决了。核心代码如下：

```cpp
bool bfs(int x){
	priority_queue<pii, vector<pii>, greater<pii> > q;
	vis[x] = x;
	q.push({0, x});
	int w = 0;
	while(!q.empty()){
		pii now = q.top();
		q.pop();
		if(w >= now.first){//可以走
			w++;
			for(auto i : g[now.second]){//遍历寻找最小的怪物等级所对应的点
				if(vis[i] == x)continue;//走过
				q.push({a[i], i});
				vis[i] = x;//标点
			}
		}else {
			while(!q.empty()){q.pop();}
			break;
		}
	}
	if(w == n)return true;//遍历成功
	else return false;
}
```

其中值得注意的是本题的标点方法，可以有效减少搜索的次数。如果这个点被算过了，那么 $vis_i$ 就是不等于 $x$ 的，否则等于。

## 代码

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

const int N = 2e5 + 10;

int n, m;

int a[N], vis[N];

vector<int> g[N];

bool bfs(int x){
	priority_queue<pii, vector<pii>, greater<pii> > q;
	vis[x] = x;
	q.push({0, x});
	int w = 0;
	while(!q.empty()){
		pii now = q.top();
		q.pop();
		if(w >= now.first){//可以走
			w++;
			for(auto i : g[now.second]){//遍历寻找最小的怪物等级所对应的点
				if(vis[i] == x)continue;//走过
				q.push({a[i], i});
				vis[i] = x;//标点
			}
		}else {
			while(!q.empty()){q.pop();}
			break;
		}
	}
	if(w == n)return true;//遍历成功
	else return false;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n >> m;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			vis[i] = 0;
			g[i].clear();
		}
		while(m--){
			int x, y;
			cin >> x >> y;
        //双向建边
			g[x].push_back(y);
			g[y].push_back(x);
		}
		bool flag = 0;
		for(int i = 1; i <= n; i++){
			if(a[i] == 0 && !vis[i]){//没走过
				if(bfs(i)){
					printf("YES\n");
					flag = 1;
					break;
				}
			}
		}
		if(!flag)printf("NO\n");
	}
}
```

---

