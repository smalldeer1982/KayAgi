# [ABC373D] Hidden Weights

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc373/tasks/abc373_d

$ N $ 頂点 $ M $ 辺の有向グラフが与えられます。$ j $ 番目の有向辺は頂点 $ u_j $ から頂点 $ v_j $ に向かっており、重み $ w_j $ を持っています。

各頂点に $ -10^{18} $ 以上 $ 10^{18} $ 以下の整数を書き込む方法であって、次の条件を満たすものを $ 1 $ つ見つけてください。

- 頂点 $ i $ に書き込まれている値を $ x_i $ とする。すべての辺 $ j=1,2,\dots,M $ について、$ x_{v_j}\ -\ x_{u_j}\ =\ w_j $ が成り立つ。

与えられる入力について、条件を満たす書き込み方が少なくとも $ 1 $ つ存在することが保証されます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min\{2\ \times\ 10^5,N(N-1)/2\} $
- $ 1\ \leq\ u_j,\ v_j\ \leq\ N $
- $ u_j\ \neq\ v_j $
- $ i\ \neq\ j $ なら $ (u_i,v_i)\ \neq\ (u_j,v_j) $ かつ $ (u_i,v_i)\ \neq\ (v_j,u_j) $
- $ |w_j|\ \leq\ 10^9 $
- 入力はすべて整数
- 条件を満たす書き込み方が少なくとも $ 1 $ つ存在する

### Sample Explanation 1

$ x=(3,5,2) $ とすることで、$ x_2-x_1=w_1=2,x_2-x_3=w_2=3,x_3-x_1=w_3=-1 $ となり、条件を満たします。 他にも、たとえば $ x=(-1,1,-2) $ としても正解となります。

### Sample Explanation 2

他にも、たとえば $ x=(0,-5,4,1) $ や $ x=(5,0,4,1) $ としても正解となります。

## 样例 #1

### 输入

```
3 3
1 2 2
3 2 3
1 3 -1```

### 输出

```
3 5 2```

## 样例 #2

### 输入

```
4 2
2 1 5
3 4 -3```

### 输出

```
5 0 6 3```

## 样例 #3

### 输入

```
5 7
2 1 18169343
3 1 307110901
4 1 130955934
2 3 -288941558
2 5 96267410
5 3 -385208968
4 3 -176154967```

### 输出

```
200401298 182231955 -106709603 69445364 278499365```

# 题解

## 作者：ikunTLE (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_d)

### 思路

如果确定了一个顶点的值，相邻顶点的值确定。由于该图的连通性，只要任意一点上的值确定，所有的值都会根据该点得知而确定。

因此，可以给初始的顶点赋值为 $0$，BFS 确定其连通的值。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
struct node{
	int v,w;
};vector<node>vc[N];
bool vis[N];
int ans[N];
signed main(){
	int n=read(),m=read();
	while(m--){
		int u=read(),v=read(),w=read();
		vc[u].push_back({v,w});
		vc[v].push_back({u,-w});
	}
	for(int i=1;i<=n;++i){
		if(vis[i])
			continue;
		queue<int>q;
		q.push(i),vis[i]=true;
		while(!q.empty()){
			int u=q.front();
			for(auto i:vc[u])
				if(!vis[i.v]){
					vis[i.v]=true;
					ans[i.v]=ans[u]+i.w;
					q.push(i.v);
				}
			q.pop();
		}
	}
	for(int i=1;i<=n;++i)
		printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：zlqwq (赞：4)

我们可以直接对每个点进行一次 dfs。

对于每个点，我们枚举所有与其相连的点，看看这些点有没有没搜过。

如果没被搜过，就去搜一下，并更新 $x$ 数组。

一定要双向建边！


```cpp
#include<iostream>
#include<vector>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18
using namespace std;
const int N = 2e5 + 5;
vector<pair<int,int>> ed[N];
bool vis[N];
int x[N];
int n,m;
void dfs(int p,int now) {
	for(auto g : ed[p]) {
		int u = g.first;
		int w = g.second;
		if(!vis[u]) {
			vis[u] = 1;
			x[u] = now + w;
			dfs(u,now+w);
		}
	}
}
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= m;++i) {
		int u,v,w;
		cin >> u >> v >> w;
		ed[v].push_back({u,-w});
		ed[u].push_back({v,w});
	}
	for(int i = 1;i <= n;++i) {
		if(!vis[i]) {
			vis[i] = 1;
			x[i] = 0;
			dfs(i,0);
		}
	}
	for(int i = 1;i <= n;++i) {
		cout << x[i] << " ";
	}
	return 0;
}


```

---

## 作者：liuziqin (赞：3)

## 思路

由于 $X_{v_i}=X_{u_i}+w_i$ ，可以推出 $X_{u_i}=X_{v_i}-w_i$ 。

依据这个性质，每次在加边时建一条权值为 $w_i$ 的正边和一条权值为 $-w_i$ 的反边，最后跑一遍 bfs 即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
struct edge{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt;
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	e[cnt].w=w;
	head[u]=cnt;
}
int val[N];
bool used[N];
void bfs(int rt){
	val[rt]=0;
	queue<int>q;
	q.push(rt);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		used[u]=1;
		int now=val[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(used[v])continue;
			val[v]=val[u]+e[i].w;
			q.push(v);
		}
	}
}//bfs
signed main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,-w);//反边
	}
	for(int i=1;i<=n;i++)if(!used[i])bfs(i);
	for(int i=1;i<=n;i++)cout<<val[i]<<" ";//输出
	cout<<"\n";
	return 0;
}

```

---

## 作者：SkyWave (赞：1)

# [D](https://atcoder.jp/contests/abc373/tasks/abc373_d)

## 思路
说是有向图，实际上可以看作是无向图。因为如果有 $x_{v_j} - x_{u_j} = w_j$，那么就一定有 $x_{u_j} - x_{v_j} = -w_j$。

因为题目保证给出的数量关系没有冲突，所以如果我们知道了一个结点 $a$ 的值，那么所有与它有数量关系的结点 $b$ 的值都能被推出。从而如果一个连通块内有一个结点已经有值，那么整个连通块内的所有结点的值都能被推出。

我们可以对每个连通块任取一个结点，将它的值设为 $0$，然后将它作为起点用任意方式遍历一遍这个连通块即可。

## 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 200000 + 1;

vector<pair<int, int>> graph[N];
bitset<N> vis;
int que[N];
ll x[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].emplace_back(v, w);
		graph[v].emplace_back(u, -w);
	}
	
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		int front = 1, rear = 0; 
		vis[que[++rear] = i] = true;
		while (front <= rear) {
			int u = que[front++];
			for (auto [v, w] : graph[u]) if (!vis[v]) {
				x[v] = x[u] + w;
				vis[que[++rear] = v] = true;
			}
		}
	}
  
	for (int i = 1; i <= n; ++i) {
		cout << x[i] << " \n"[i == n];
	}
	return 0;
}
```

---

## 作者：cly312 (赞：1)

可以发现一个性质：**对于图的每个连通分量，一旦在其中任何顶点上的值固定，则所有写入的值都是确定的。**

我们可以逐个 DFS 每个连通分量，按照题目的要求给每个点赋值，初始搜索的点值设成 $0$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
vector<pair<int,int>> g[200010];
bool vi[200010];
int ans[200010];
void sear(int o){
	vi[o]=1;
	for(auto &[v,w]:g[o]){
		if(!vi[v]){
			vi[v]=1;
			ans[v]=ans[o]+w;
			sear(v);
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		g[u].push_back({v,w});
		g[v].push_back({u,-w});
	}
	for(int i=1;i<=n;i++){
		if(vi[i]) continue;
		sear(i);
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<' ';
	}
}
```

---

## 作者：dg114514 (赞：1)

## [ABC373D] Hidden Weights 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_d)
### 题意
给你一个 $n$ 元一次方程，一共有 $m$ 个表达式，
设 $1\le i \le m$ ,第 $i$ 个表达式格式如下：
> $u_i\ v_i\ w_i$

意为 $x_{u_i} = x_{v_i} - w_i$。   
求方程解（ 输出 $x_1,x_2,\dots,x_n$ ）。

### 思路
我们发现，解中的所有数同时加一或减一同样是正确的。  
所以我们读入时每次往 $u_i$ 和 $v_i$ 建一条权值为 $w_i$ 的边，同时往 $v_i$ 和 $u_i$ 建一条权值为 $-w_i$ 的边（肥肠重要！因为 $x_{u_i} = x_{v_i} - w_i$ 与 $x_{v_i} = x_{u_i} - (-w_i)$ 等价），然后跑几遍 BFS 即可。

具体实现在代码里~
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define sint static int
#define itn int
using namespace std;
const int N=1919810,inf=1e18;
int vis[N],ans[N];
struct abc373{
	int to,val;
};
vector<abc373>e[N];
void bfs(int start){
	queue<int> q;
	q.push(start);
	while(q.size()){
		auto t=q.front();
		q.pop();
		for(auto &x:e[t])
			if(!vis[x.to]){
				vis[x.to]=1;
				q.push(x.to);
				ans[x.to]=ans[t]+x.val;
			}
	}
}
signed main(){
	fill(ans+1,ans+N+1,0xabc373d);
	itn n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int fr,to,val;
		cin>>fr>>to>>val;
		e[fr].push_back({to,val});
		e[to].push_back({fr,-val});
	}
	for(int i=1;i<=n;i++)//防止非连通图的情况
		if(!vis[i])
			bfs(i);
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
}
```

---

## 作者：sherry_lover (赞：0)

# AT_abc373_d [ABC372D] Hidden Weights 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_d)

## 思路

题目说了一定有解，所以我们直接对每个没有填上值的点赋一个初始值，然后跑 dfs 即可。

注意要单开一个数组存每个点是否被访问过，否则算出来的点权容易和初始值冲撞。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long num[200005];
vector<pair<int,int> > b[200005];
bool vis[200005];
void dfs(int x)
{
	for(auto i:b[x])
	{
		if(!vis[i.first])
		{	
			num[i.first] = num[x] + i.second;
			vis[i.first] = 1;
			dfs(i.first);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1,u,v,w;i <= m;i++)
	{
		cin >> u >> v >> w;
		b[u].push_back({v,w});
		b[v].push_back({u,-w});
	}
	for(int i = 1;i <= n;i++)
	{
		if(!vis[i])
		{
			vis[i] = 1;
			dfs(i);
		}
	}
	for(int i = 1;i <= n;i++) cout << num[i] << " ";
	return 0;
}
```

---

## 作者：JOKER_chu (赞：0)

## 题意

给出一个 $n$ 个点，$m$ 条边的有向带权图，请求出一个点权序列 $a$，满足对于 $1 \leq i \leq m \land a_{u_i} = a_{v_i} - w_i$。

## 解法

很具有迷惑性的一题，很容易想到一个假解：先拓扑排序一遍，然后按拓扑序做递推，我赛时就是这么 `WA` 的，你会发现数据可能有环，然后拓扑就炸了。

如果要连一条从 $u \rightarrow v$ 边权为 $w$ 的边，我们容易看出来，可以将一条 $v \rightarrow u$ 边权为 $-w$ 的边建上去，那么从 $u \rightarrow v$ 和 $v \rightarrow u$ 的代价就是一样的了。

那么就可以这样建边，然后跑图的遍历，将初始点的点权建成 $0$，然后每次走到其他点时递推即可。

## 代码

```cpp
#include <iostream>

#include <algorithm>

#include <vector>

#define endl '\n'

#define int long long

using namespace std;

const int N = 2e5 + 5, Max = 2e14;

struct Edge{
	int x, w;
};

int n, m, ans[N];
bool v[N];

vector<int>topo;
vector<Edge>g[N];

void s(int x, int sum){
	if(v[x] == 1) return ;
	v[x] = 1, ans[x] = sum;
	for(auto to : g[x]) {
		s(to.x, sum + to.w); // 从这个点推到其他点
	}
}

signed main(){
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 1, x, y, w; i <= m; ++i){
		cin >> x >> y >> w;
		g[y].push_back({x, -w}), g[x].push_back({y, w}); // 建边
	}
	for(int i = 1; i <= n; ++i) s(i, 0);
	for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
	return 0;
}

```

---

## 作者：lilong (赞：0)

### 题意

给定 $n$ 个点，$m$ 条有向边，每条有向边从 $u_i$ 指向 $v_i$，边权为 $w_i$。构造一个长度为 $n$ 的整数序列 $x$，满足：

- $-10^{18} \le x_i \le 10^{18},1 \le i \le n$。

- $x_{v_j} - x_{u_j} = w_j,1 \le j \le m$。

**数据保证有解**。

### 解法

注意到数据保证有解，因此一定有多组的解（在某组解上同时加或减一个数，差显然不变），构造起来也比较容易。直接遍历全图，对于当前的第 $j$ 条边，若 $v_j$ 未遍历，则令 $ x_{v_j} \leftarrow x_{u_j} + w_j$ 即可，并遍历 $v_j$。这样做保证了时间复杂度为 $O(n+m)$。

但是题目给的是有向图，如果随意选择某个点进入则不一定能把整个连通块遍历完。考虑对等式两遍同乘 $-1$，则有 $x_{u_j} - x_{v_j} = -w_j$，那么我们再建一条从 $v_j$ 到 $u_j$，边权为 $-w_j$ 的边，即可确保遍历到同一连通块的每个点。

实现时要判断每个点是否被遍历（题目没有保证给定的是连通图）。


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

struct E
{
	int v,w,nxt;
}e[1000001];

int n,m,vis[1000001],hd[1000001],ans[1000001],tot;

void dfs( int u )
{
	vis[u] = 1;
	int v;
	for( int i = hd[u] ; i ; i = e[i].nxt )
	{
		v = e[i].v;
		if( vis[v] ) continue;
		ans[v] = ans[u] + e[i].w;
		dfs( v );
	}
	return;
}

void add( int u , int v , int w )
{
	tot ++;
	e[tot].v = v;
	e[tot].w = w;
	e[tot].nxt = hd[u];
	hd[u] = tot;
	return;
}

signed main()
{
	int u,v,w;
	cin >> n >> m;
	for( int i = 1 ; i <= m ; i ++ )
	{
		cin >> u >> v >> w;
		add( u , v , w );
		add( v , u , -w );
	}
	for( int i = 1 ; i <= n ; i ++ )
		if( !vis[i] )
			dfs( i );
	for( int i = 1 ; i <= n ; i ++ )
		cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
题意：给定 $m$ 条边的有向图，求一个点权序列 $a$，对于每条边，需要保证 $a_{v_i} - a_{u_i} = w_i$。

因为保证有解，所以可以考虑对每个连通块 bfs，以求解点权，但是因为是有向边，所以可能出现一个连通块无法完全遍历的情况。

于是考虑到 $a_{v_i} - a_{u_i} = w_i$ 等价于 $a_{u_i} - a_{v_i} = -w_i$。这样，就把一条边变为 $(u_i,v_i,w_i)$ 与 $(v_i,u_i,-w_i)$ 两条边，就解决了问题。

# 代码实现
```cpp
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N = 2e5 + 5;
int n, m;
int u, v, w;
long long x[N];  // 开 long long
bool vis[N];
struct Node { int v, w; };
vector<Node> ed[N];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        ed[u].push_back({v, w});
        ed[v].push_back({u, -w}); // 拆成两条边
    }
    for(int i = 1; i <= n; ++i) {
        if(vis[i]) continue;
        vis[i] = true;
        queue<int> q;
        q.push(i);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto p : ed[u])
                if(!vis[p.v]) {
                    vis[p.v] = 1;
                    x[p.v] = x[u] + p.w; // 赋点权
                    q.push(p.v);
                }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%lld ", x[i]);
}
```

---

## 作者：_WRYYY_ (赞：0)

[ABC373 题解合订版（A~F）。](https://www.cnblogs.com/wryyy-233/p/18439686)

原式子可化为：$x_{u_j}+w_j=x_{v_j}$。

无环的情况直接从无入度点搜一遍就行，考虑对于任意一个环我们如何求解。

假设该环有 $k$ 条边，令边 $i(1\le i\le k)$ 连接着 $i$ 和 $i+1$ 号节点，特别的第 $k$ 条边为 $(k,1)$。

由环上任意一点绕一圈回来可以得到 $x_i+\sum_{j=1}^kw_j=x_i$。

而题目保证有解。

所以最后答案与在环上哪个点起始和取值多少无关，只要一直搜的去满足式子就行。

最后注意图可能不连通，还有从任意一点搜如果该点有入度，那么入度后的全部用反图搜。

## Code


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 200010
using namespace std;
using namespace __gnu_pbds;
vector<pair<int, ll>> a[N], ra[N];
ll val[N];
bitset<N> vis;
void dfs1(int x)
{
	vis[x] = 1;
	for (auto [y, w] : a[x])
	{
		if (vis[y])
			continue;
		val[y] = val[x] + w;
		dfs1(y);
	}
	return;
}
void dfs2(int x)
{
	vis[x] = 1;
	for (auto [y, w] : ra[x])
	{
		if (vis[y])
			continue;
		val[y] = val[x] + w;
		dfs2(y);
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, m, x, y, w;
	cin >> n >> m;
	vector<tuple<ll, ll, ll>> vec;
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y >> w;
		vec.push_back(m_t(x, y, w));
		a[x].push_back(m_p(y, w));
		a[y].push_back(m_p(x, -w));
	}
	for (int i = 1; i <= n; i++)
	{
		if (vis[i])
			continue;
		dfs1(i);
		dfs2(i);
	}
	for (int i = 1; i <= n; i++)
		cout << val[i] << " ";
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：0)

一个朴素的想法是依次满足各个条件，很显然过不了，例如：
```
3 2
1 2 1
3 2 2
```
原因很显然，一个点确定后再进行操作会导致前面的不合法，因为保证有解，易得它是有向无环图，所以可以拓扑排序（存疑），但这只蒟蒻写挂了，所以这篇题解主要介绍 DFS 解法。

这个比较简单，我画个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/ybry3qmv.png)
为了方便 DFS，我们建上反边，注意取负边权：
![](https://cdn.luogu.com.cn/upload/image_hosting/rrwsy3dc.png)
然后对于每个点用朴素 DFS 并附上点权就行了（也就是用 DFS 确定先后顺序）。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, a[200005], vis[200005], cnt;
vector<pair<long long, long long> > g[200005];
void dfs(long long u){
	vis[u] = 1;
	for(long long i = 0; i < g[u].size(); i ++){
		a[g[u][i].first] = a[u] + g[u][i].second;
		if(!vis[g[u][i].first]) dfs(g[u][i].first);//警示后人，别写成 i 了
	}
}
int main(){
	cin >> n >> m;
	for(long long i = 1; i <= m; i ++){
		long long u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, -w});
	}
	for(long long i = 1; i <= n; i ++){
		if(!vis[i]) dfs(i);
	}
	for(long long i = 1; i <= n; i ++) cout << a[i] << " ";
	return 0;
}
```
[愉快 AC](https://atcoder.jp/contests/abc373/submissions/58238734)，~~我不会告诉你我是最后几分钟才找出错的~~。

---

## 作者：hjyowl (赞：0)

### 题目大意

给定你 $n$ 个不等式，每个等式要求：$v_i-u_i=w_i$，请你输出任意一种构造方案。

### 思路

对于等式，首先想到差分约束系统，具体建边系统如下：

```cpp
		swap(a,b);//顺序反的，到换一下
		add(b,a,c);
		add(a,b,-c);
```

然后就很好做了，对于这个系统，使用 spfa 做就可以了（不能用 dijkstra 是因为有负权边）。

### 细节：

spfa 里不能用栈而要用队列（因此挂了 $9$ 次）。

双向边数组开两倍。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 200010,M = 800010;
long long h[N], e[M], w[M], ne[M], idx;
long long dist[N],cnt[N];
bool st[N];
long long n,m;
void add(long long a, long long b, long long c){
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
double start;
bool spfa(){
	long long hh = 0,tt = 1;
	memset(dist,-0x3f,sizeof dist);
	dist[0] = 0;
	queue<long long>q;
	q.push(0);
	st[0] = 1;
	while (!q.empty()){
		long long t = q.front();
		q.pop();
		st[t] = 0;
		for (long long i = h[t]; ~i; i = ne[i]){
			long long j = e[i];
			if (dist[t] + w[i] > dist[j]){
				dist[j] = dist[t] + w[i];
				if (!st[j]){
					q.push(j);
					st[j] = 1;
				}
			}
		}
	}
	return 1;
}
int main(){ 
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	start = clock();
	cin >> n >> m;
	memset(h, -1, sizeof h);
	while (m -- ){
		long long a,b,c;
		cin >> a >> b >> c;
		swap(a,b);
		add(b,a,c);
		add(a,b,-c);
	}
	for (long long i = n; i > 0; i -- ){
		add(0,i,0);
	}
	if (spfa()){
		for (int i = 1; i <= n; i ++ ){
			cout << dist[i] << " ";
		}
	}
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 题意
给出 $n$ 个点，$m$ 条无向边。第 $i$ 条边从 $a_i$ 到 $b_i$，边权为 $c_i$。你要构造 $x$ 数组，使得 $x_{b_i}-x_{a_i}=c_i$。
# 题解
注意到 $x$ 的范围是 $-10^{18}\le x_i \le 10^{18}$，而边权之和才 $2 \times 10^{14}$，也就是说 $x_i$ 取值范围等于说无穷大。

我们对于每个连通块，任选一点为 $0$，接着遍历连通块就行了。因为题目说了保证有解，所以每个点只要遍历一次。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,e[400010],ne[400010],h[200010],q[400010],st[400010],idx;
long long ans[400010];
void add(int a,int b,int c){e[idx]=b,q[idx]=c,ne[idx]=h[a],h[a]=idx++;}
void dfs(int i){
	st[i]=1;
	for(int w=h[i];~w;w=ne[w])if(!st[e[w]])ans[e[w]]=ans[i]+q[w],dfs(e[w]);
}
int main(){
    scanf("%d%d",&n,&m),memset(h,-1,sizeof(h));
    for(int w=1;w<=m;w++)scanf("%d%d%d",&a,&b,&c),add(a,b,c),add(b,a,-c);
    for(int w=1;w<=n;w++)if(!st[w])dfs(w);
    for(int w=1;w<=n;w++)printf("%lld ",ans[w]);
    return 0;
}
```

---

## 作者：Imerance1018 (赞：0)

E 题没场切，不开心。

### Description

[传送门](https://atcoder.jp/contests/abc373/tasks/abc373_d)

### Solution

首先我们需要一个并查集维护连通块，以防万一，我们建图的时候要建双向边。（赛时大脑宕机建双向边居然写复杂了）

建双向边的原因：如果不是双向边，那么对于任意节点 $i$，它所在树的根节点与 $i$ 之间不一定连通。

对于每个连通块做一个 dfs，将任意节点赋为 0，然后按照连边的关系给每个节点依次赋值即可。

因为题目保证有解，所以答案总是正确的。

### Description
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m,ans[N];
int fa[N];
int find(int x)
{
	if(fa[x]==x)return fa[x];
	return fa[x]=find(fa[x]);
}
bool vis[N];
vector<pair<int,pair<int,int> > >G[N];
void dfs(int x)
{
	vis[x]=1;
	for(int i=0;i<G[x].size();i++)
 	{
 	
		int y=G[x][i].first;
		if(vis[y])continue;
		if(G[x][i].second.first==1)ans[y]=ans[x]+G[x][i].second.second;
		else ans[y]=ans[x]-G[x][i].second.second;
		dfs(y);
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		G[u].emplace_back(make_pair(v,make_pair(1,w)));//好奇怪，不要学我
		G[v].emplace_back(make_pair(u,make_pair(0,w)));
		if(find(v)==find(u))continue;
		fa[find(v)]=find(u);
	}
	for(int i=1;i<=n;i++)
	{
		if(find(i)==i)dfs(i);
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
``````

---

## 作者：Your_Name (赞：0)

## 题意
给一个 $n$ 个点 $m$ 条边的有向图，要求构造一个 $x$，使得对第 $j$ 条边都有 $x_v-x_u=w_j$。
## 题意
注：下文联通块是指底图中的。

发现直接从每个联通块的任意一点出发 bfs，把整个联通块处理完到起点的距离就是答案，因为输入保证有解。

但是，从任意一点出发可能并没有办法走遍整个联通块，因此每次加边的时候再加一条权值是原来相反数的边即可。

建议评黄。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 4e5 + 10;
LL e[N],ne[N],w[N],h[N],n,m,idx;
bool vis[N];
void add(LL a,LL b,LL c){
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
LL ans[N];
void bfs(int s){
    queue<LL> q;
    q.push(s);
    vis[s] = 1;
    while(!q.empty()){
        LL i = q.front();
        q.pop();
        for(LL j = h[i]; ~j; j = ne[j]){
            LL k = e[j];
            if(vis[k])continue;
            ans[k] = ans[i] + w[j];
            vis[k] = 1;
            q.push(k);
        }
    }
}//直接bfs
int main(){
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for(LL i = 1; i <= m; i ++){
        LL u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, -w);//加反边
    }
    for(LL i = 1; i <= n; i ++)if(!vis[i])bfs(i);
    for(LL i = 1; i <= n; i ++){
        cout << ans[i] << ' ';
    }
    return 0;
}
```

---

## 作者：TainityAnle (赞：0)

#### 题意简述

给定一个有向图，要求你往每个节点上写一个 $-10^{18}$ 和 $10^{18}$ 之间的数，使得有边相连的两个节点的数字之差等于这条边的边权。

---

虽然题目给出了一张有向图，但是要求两点数字之差（即 $|x_i-x_j|$）等于边权。

因为如果从点 $i$ 到点 $j$ 差为 $w$，那么从点 $j$ 到点 $i$ 差也为 $w$，所以可以不考虑图的方向，给每一条边建一个反边。

这样，每条边有两种情况，即到下一个点加上权值或减去权值。比赛时，我没有一下想到正解，于是先写了一个简单的暴力，每条边选择走正或负，跑完 $O(m)$ 判断是否满足条件，但这 $O(2^m\times m)$ 的时间复杂度只能跑到 $m\leq20$。

然后，尝试记录成功时的 $\operatorname{dfs}$ 序以及走的是正权值还是负权值，发现样例 $1$ 和样例 $2$ 都有一种情况，所有的反边都跑的是负权。所以在建图时将反边赋负权即可。

---

#### 总结做法

1. 建双向边，反边赋负权值。
2. 样例二告诉我们，图有可能不联通，所以枚举每个点，若它没有被访问过，就从它开始搜。
3. 要开 long long！

---

#### AC code

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int head[N],maxi,maxx,sum,tot,n,m,a[N];
bool vis[N];
struct Edge {
	int nxt,to,from,w;
} e[N<<1];
void add(int from,int to,int w) {
	e[++tot].nxt=head[from];
	e[tot].from=from;
	e[tot].to=to;
	e[tot].w=w;
	head[from]=tot;
}
void dfs(int x,int id) {
	vis[x]=1;
	a[x]=id;
	for(int i=head[x]; i; i=e[i].nxt)
		if(!vis[e[i].to]) dfs(e[i].to,id+e[i].w);
}
signed main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,-w);
	}
	for(int i=1; i<=n; i++) {
		if(!vis[i]) {
			dfs(i,0);
		}
	}
	for(int i=1; i<=n; i++) cout<<a[i]<<" ";
	return 0;
}
```

---

