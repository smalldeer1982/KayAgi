# [ABC376D] Cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点 $ M $ 辺の単純有向グラフがあります。$ i $ 番目の辺 $ (1\ \leq\ i\ \leq\ M) $ は頂点 $ a_i $ から頂点 $ b_i $ へ伸びる辺です。  
 頂点 $ 1 $ を含む閉路が存在するか判定して、存在する場合はそのような閉路のうち辺数が最小の閉路の辺数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min\ \left(\ \frac{N(N-1)}{2},\ 2\ \times\ 10^5\ \right) $
- $ 1\ \leq\ a_i\ \leq\ N $
- $ 1\ \leq\ b_i\ \leq\ N $
- $ a_i\ \neq\ b_i $
- $ i\ \neq\ j $ ならば $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ かつ $ (a_i,\ b_i)\ \neq\ (b_j,\ a_j) $
- 入力される値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ $ \to $ 頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ 頂点 $ 1 $ は辺数が $ 3 $ の閉路で、これが頂点 $ 1 $ を含む唯一の閉路です。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 9
6 1
1 5
2 6
2 1
3 6
4 2
6 4
3 5
5 4```

### 输出

```
4```

# 题解

## 作者：Heldivis (赞：3)

## [ABC376D] Cycle

直接求环比较难处理。注意到题目是有向边，考虑转化题意为：**从 $1$ 号点出发到 $x$ 号点，再从 $x$ 号点走回 $1$ 号点的最短路**。由于是有向边，这样的两条路径一定构成环。具体实现可以直接从 $1$ 经过一条边可以到达的点跑多远最短路，求出它们到 $1$ 号点的最短路的最小值即可。时间复杂度 $O(N)$。

代码如下：

```cpp
n = read(), m = read();
for (int i = 1; i <= m; ++i)
  int x = read(), y = read(), e[x].push_back(y);
queue<int> q;
memset(d, 0x3f, sizeof d);
for (int y : e[1]) q.push(y), d[y] = 1;
while (q.size()) {
  int x = q.front();
  q.pop();
  for (int y : e[x])
    if (d[y] > d[x] + 1) d[y] = d[x] + 1, q.push(y);
}
if (d[1] >= 1E9) d[1] = -1;
printf("%d\n", d[1]);
```

---

## 作者：yangxikun (赞：2)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/AT_abc376_d) [AT](https://atcoder.jp/contests/abc376/tasks/abc376_d)

### 题目大意

一个有 $N$ 个点的有向简单图，编号为 $1$ 到 $N$。有 $M$ 条边，每条边是一条顶点 $a_i$ 到 $b_i$ 的有向边。判断是否存在包含顶点 $1$ 的循环，如果存在，求这种循环中边的最小数目。

### 解法

一道 BFS。

用邻接表存图，注意是**有向图**。建一个 dis 数组，用来记录到每个点的最短距离，初始每一位都是 $0$。

BFS 结束后，输出 $dis_1$ 即可。如果是 $0$，表示没有最后到 $1$ 的循环，输出 $-1$。

### 代码

[AT 提交记录](https://atcoder.jp/contests/abc376/submissions/58973918)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define MP(a,b) make_pair(a,b)
#define PB(a) push_back(a)
vector<int> g[200005];//邻接表
int dis[200005];
queue<int> q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	memset(dis,0,sizeof(dis));//其实没必要memset
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
	}
	q.push(1);//初始化
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto i:g[u]){
			if(dis[i]!=0)continue;//访问过了，注意最小数目
			q.push(i);
			dis[i]=dis[u]+1;
		}
	}
	cout<<(dis[1]==0?-1:dis[1]);//输出
	return 0;
}
```

---

## 作者：shitingjia (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc376_d)

### 题目大意

判断**有向图中**是否存在包含顶点 $1$ 的环。如果存在，输出包含顶点 $1$ 的最小环的边数。

### 题目思路

跟图好像没有太大的关系，广搜就可以解决。把边权全部设为 $1$。

队列中记录两个值：

- 当前节点编号。
- 当前节点到 $1$ 节点的距离。

若回到了 $1$ 节点，输出时间即可。

否则继续搜索。

注意 $N$ 的范围，不能用邻接矩阵。

### AC Code

```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N=2e5+10;
int n,m;
bool vis[N];
vector<int>e[N];
bool bfs(){
	queue<pair<int,int> >q;
	q.push({1,0});
	while(q.size()){
		int u=q.front().first,time=q.front().second;
		q.pop();
		for(auto v:e[u]){
			if(v==1){
				cout<<time+1;//还要再走一步才到达1节点
				return 1;
			}
			if(!vis[v]){//之前还没有走到过v节点
				vis[v]=1;
				q.push({v,time+1});
			}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
	}
	bool ans=bfs();
	if(!ans)	cout<<-1;//没有答案
	return 0;
}
```

---

## 作者：__FL__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc376_d)

## 题意

给定一个简单有向图，求其中包含顶点 $1$ 的环的最小边数。如果不存在就输出 $-1$。

## 思路

考虑最小边数，即边权为 $1$，满足 bfs 的条件。考虑从顶点 $1$ 开始向外 bfs，队列中同时记录顶点编号和走的边数，用 vis 数组标记一个点是否被走过，当第一次走到顶点 $1$ 时，就直接输出答案并 return。如果到最后也没有输出答案，就输出 $-1$。

## Code

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
int n,m,a,b;
bool vis[200005],f;
vector<int>vec[200005];
queue<PII>q;
void bfs()
{
	while (!q.empty())
	{
		PII now = q.front();
		q.pop();
		for (int i: vec[now.first])
		{
			if (i == 1)
			{
				cout << now.second+1;
				f = 1;
				return;
			}
			if (!vis[i])
			{
				q.push({i,now.second+1});
				vis[i] = 1;
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		vec[a].push_back(b);
	}
	q.push({1,0});
	bfs();
	if (!f) cout << -1;
    return 0;
}
```

---

## 作者：zjj2024 (赞：1)

### 思路
考虑广搜。

分析广搜的过程。

如果一个点没有被扩展过则扩展，并打上标记。

在有向图如果之前被扩展过则为有环。

由于广搜出的是最短路径，则 1 号点第一次被另一个点扩展时则为最小环，环的长度为中间经过的步数。

所以跟[这题](https://www.luogu.com.cn/problem/P2661)是非常相近的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
vector<int>v[N];
int a[N],vis[N],q[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);//存边
	}
	int l=1,r=0;
	q[++r]=1;
	vis[1]=1;//遍历时间
	while(r>=l)
	{
		int x=q[l];
		l++;
		for(int i=0;i<v[x].size();i++)
		{
			int y=v[x][i];
			if(y==1)
			{
				cout<<vis[x]<<'\n';//vis[x]-vis[1]+1=vis[x]
				return 0;
			}
			if(vis[y])continue;
			q[++r]=y;//加入队列
			vis[y]=vis[x]+1;
		}
	}
	cout<<"-1\n";
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
题意为求包含结点 $1$ 的最小环。

从结点 $1$ 开始广度优先搜索，当第二次遇到 $1$ 的时候就说明找到了最小环。可以在搜索过程中给结点打上标记防止进入死循环，保证每个点只走一次。

时间复杂度 $O(N+M)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,ans = -1;
bool arr[200001];
vector<int>e[200001];
queue<pair<int,int> >q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i ++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	q.push(make_pair(0,1));
	while(q.size() && ans == -1){
		int w = q.front().first,u = q.front().second;
		q.pop();
		for(int i = 0;i < e[u].size();i ++){
			int v = e[u][i];
			if(v == 1){//检测该边终点而不是检测起点，防止第一轮就检测到 1 从而错误地退出
				ans = w + 1;
				break;
			}
			if(arr[v]){//有标记不重复走
				continue;
			}
			arr[v] = true;
			q.push(make_pair(w + 1,v));
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Anins (赞：1)

## [[ABC376D] Cycle](https://www.luogu.com.cn/problem/AT_abc376_d)

### 题意：

有 $n$ 个点，$m$ 条边权为 $1$ 的单向边，问经过 $1$ 号点的最小环长度。

### 思路：

从 $1$ 号点开始 bfs，枚举队首点出边所至点，若未遍历过就更新距离且压入队列，若遍历过且点的编号为 $1$，说明可以构成一个环，用当前点距 $1$ 号点距离更新最小环的长度。

因为数据不大，所以不需要优化也能过。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, ans=0x3f3f3f;
vector <ll> e[200005];
void bfs() {
	ll dis[200005];
	memset(dis, -1, sizeof(dis));
	queue <ll> q;
	dis[1]=0;
	q.push(1);
	while(!q.empty()) {
		ll u=q.front();
		q.pop();
		for(auto v:e[u]) {
			if(dis[v]==-1) { //未遍历过，扩展
				dis[v]=dis[u]+1;
				q.push(v); 
			} else if(v==1) {
				ans=min(ans, dis[u]+1); //一个环，更新答案
			}
		}
	} 
}
int main() {
	scanf("%lld%lld", &n, &m);
	ll u, v;
	for(int i=1; i<=m; i++) {
		scanf("%lld%lld", &u, &v);
		e[u].push_back(v);
	}
	bfs();
	if(ans==0x3f3f3f) printf("-1");
	else printf("%lld", ans); 
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[at原题面](https://atcoder.jp/contests/abc376/tasks/abc376_d)
## 题目分析：
题意挺直接的，就是给定一张图，找有没有包含节点 $1$ 的环，并输出最短环的长度，直接跑 bfs 即可。
## Code:
```cpp
#include<bits/stdc++.h>
#define starrail main
#define lowbit(x)  (x&(-x))
#define re registe
#define il inline
#define fi first
#define se second
using namespace std;
typedef long long ll;
il int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int N=2e5+10;
int n,m;
vector<int>e[N];
bool vis[N];
il void bfs(){
    queue<pair<int,int>>q;
    q.push({1,0});
    while(!q.empty()){
        int now=q.front().fi,nxt=q.front().se;
        q.pop();
        if(now==1&&nxt!=0){
            printf("%d\n",nxt);
            exit(0);
        }
        for(auto i:e[now]){
            if(!vis[i]){
                vis[i]=true;
                q.push({i,nxt+1});
            }
        }
    }
}
signed starrail(){
	n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[u].push_back(v);
    }
    bfs();
    printf("-1");
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

题目可以转化为从点 $1$ 必须经过其他点再回到点 $1$ 的最短路。

为了防止跑最短路时将点 $1$ 到点 $1$ 的路程初始化为 $0$，我们将点 $1$ 拆成两个点 $1$ 和 $n+1$，其中点 $1$ 连着所有的入边，点 $n+1$ 连着所有的出边。

答案就是从点 $n+1$ 到点 $1$ 的最短路。

---

## 作者：Special_Tony (赞：0)

# 思路
这不是 bfs 板子吗？最普通的 bfs，并且只需要在最开始不把 $vis_1$ 标记掉，这样就可以在第一次回到 $1$ 号点的时候输出路径长度。

[代码](https://atcoder.jp/contests/abc376/submissions/58953831)。

---

## 作者：__O_v_O__ (赞：0)

容易发现，一个包含点 $1$ 的环相当于一个起点为 $1$，终点为 $1$ 的路径。

于是，我们创建一个虚点，把连向 $1$ 的边改为连向虚点，最后跑从 $1$ 到虚点的最短路即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{int to,nx;}e[500001];
int n,m,vi[500001],h[500001],nu;
int di[500001],en,s,g[500001];
priority_queue<pair<int,int> >q;
void ae(int fr,int to){
	e[++en].nx=h[fr],e[en].to=to,h[fr]=en;
}
void d(int s){
	memset(di,0x3f,sizeof di);
	di[s]=0;
	q.push(make_pair(0,s));
	while(q.size()){
		int ma=q.top().second;
		q.pop();
		if(vi[ma])continue;
		vi[ma]=1;
		for(int i=h[ma];i;i=e[i].nx){
			int v=e[i].to;
			if(di[v]>di[ma]+1)di[v]=di[ma]+1
				,q.push(make_pair(-di[v],v));
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		if(v==1)ae(u,n+1);
		else ae(u,v);
	}
	d(1);
	if(di[n+1]==0x3f3f3f3f)cout<<-1;
	else cout<<di[n+1];
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定一个有向图，求包括 $1$ 的最小环的边数，不存在则输出 `-1`。

**解题思路**

一个包括 $1$ 的环一定是由 $1\to i\to 1$ 构成的，其中 $(i,1)$ 为一条有向边。

以 $1$ 为根节点跑最短路，那么最终答案为

$$
\min_{1\le i\le n\operatorname{and} 1\in g(i)}\{d_i+1\}
$$

其中 $g(i)$ 为 $i$ 一次能到的点。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
const int N = 2e5 + 5;
using namespace std;
int n, m, dis[N];
vector<int> e[N];
struct node {
  int x, y;
  inline bool operator<(const node z)const {
    return y > z.y;
  }
};
priority_queue<node> q;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  int x, y;
  for(int i = 1; i <= m; i++) {
    cin >> x >> y;
    e[x].push_back(y);
  }
  memset(dis, 0x3f, sizeof dis);
  dis[1] = 1;
  q.push({1, 1});
  while(!q.empty()) {
    x = q.top().x, y = q.top().y;
    q.pop();
    if(y != dis[x]) { continue; }
    for(int i : e[x]) {
      if(dis[x] + 1 < dis[i]) {
        dis[i] = dis[x] + 1;
        q.push({i, dis[i]});
      }
    }
  }
  int ans = 1e9;
  for(int i = 1; i <= n; i++) {
    for(auto j : e[i]) if(j == 1) {
      ans = min(ans, dis[i]);
    }
  }
  cout << (ans == 1e9 ? -1 : ans);
  return 0;
}
```

---

## 作者：CuteForces (赞：0)

## 思路：

看题本，发现就是找包含 $1$ 的最短环。先看数据范围，$N,M\le 2\times 10^5$，显然暴力是过不去的。

所以可以使用 $O(n\log{n})$ 的方法，一下想到 Dijkstra。

比较好想的是，因为是有向图，所以当通过 $d_x+1$ 更新 $d_1$ 时，一定存在一个长度为 $d_x+1-d_1$ 的环。

所以直接套用即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
int n,m,ans=0x3f3f3f3f,h[N],e[N],nxt[N],d[N],tot;
bool vis[N];
void add(int x,int y){
	e[++tot]=y;
	nxt[tot]=h[x];
	h[x]=tot;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
	}
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	priority_queue<pair<int,int> > q;
	q.push({0,1});
	while(!q.empty()){
		int u=q.top().second,now=q.top().first;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=h[u];i;i=nxt[i]){
			int j=e[i];
			if(d[j]>d[u]+1){
				d[j]=d[u]+1;
				q.push({-d[j],j});
			}else if(j==1) ans=min(ans,d[u]+1);
		}
	}
	if(ans==0x3f3f3f3f) ans=-1;
	cout<<ans;
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

本题等价于求从 $1$ 到 $1$ 的非严格次短路。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int tot = 0, head[N];
struct Edge {
	int next, to;
} edge[N << 1];
inline void add_edge(int u, int v) {
	edge[++tot].next = head[u], edge[tot].to = v, head[u] = tot;
}

int n, m, u, v;

namespace Dijkstra {
	int dis1[N], dis2[N];
	
	struct node {
		int to, dis;
		
		node(int v, int w) : to(v), dis(w) {}
		
		bool operator< (const node& other) const {
			return dis > other.dis;
		}
	};
	priority_queue<node> q;
	
	inline int dijkstra(int s, int t) {
		memset(dis1, 0x3f, sizeof(dis1));
		memset(dis2, 0x3f, sizeof(dis2));
		dis1[s] = 0;
		q.push(node(s, 0));
		while (!q.empty()) {
			int u = q.top().to, d = q.top().dis;
			q.pop();
			if (d > dis2[u]) continue;
			for (int j = head[u]; j != 0; j = edge[j].next) {
				int v = edge[j].to, w = d + 1;
				if (dis1[v] > w) {
					dis2[v] = dis1[v], dis1[v] = w;
					q.push(node(v, dis1[v]));
				} 
				if (dis2[v] > w && dis1[v] < w) {
					dis2[v] = w;
					q.push(node(v, dis2[v]));
				}
			}
		}
		return dis2[t];
	}
}

void _main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, add_edge(u, v);
	int res = Dijkstra::dijkstra(1, 1);
	if (res >= 0x3f3f3f3f) cout << -1;
	else cout << res;
} 
```

---

## 作者：T_TLucas_Yin (赞：0)

这题放 D 简直太水了。

既然让找环，我们就从 $1$ 号点开始搜索，找到第一个能连接到 $1$ 号点的节点，即为找到了一个环。既然让找最小的环，那我们就用广搜，搜到的节点肯定是按步数从小到大排列的，里面第一个能连接到 $1$ 号节点的点就是最小包含 $1$ 的环的终点，输出遍历到它经历的步数 $+1$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b;
int head[1000005],ver[1000005],ne[1000005],tot;
void add(int x,int y){
	ver[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
struct node{
	int k,x;
};
queue<node> q;
bool flag[1000005];
int main(){
	cin>>n>>m;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		add(a,b);
	}
	q.push({1,0}),flag[1]=1;
	while(!q.empty()){
		node t=q.front();
		q.pop();
		for(int i=head[t.k];~i;i=ne[i]){
			if(ver[i]==1){
				cout<<t.x+1;
				return 0;
			}
			q.push({ver[i],t.x+1}),flag[ver[i]]=1;
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 题目大意

给定一个有向图，从 $1$ 出发的最小环。

### 思路

很明显，我们可以枚举一个点，然后求出从 $1$ 到这个点的距离和这个点到 $1$ 的距离，把两个之加起来，在求出最小的和即可。

至于如何求反过来走到 $1$，直接建一个反图，然后对于反图正图都跑一遍最短路就可以了。

时间复杂度：$\Theta(m\log m)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400010,M = 2000010;
typedef pair<int,int> PII;
int h[N], e[M], ne[M], idx,w[M];
int q[M];
int dist[M];
bool st[N];
void add(int a, int b, int c){
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
int hs[N], es[M], nes[M], idxs,wss[M];
int dists[N];
bool sts[N];
void adds(int a, int b, int c){
	es[idxs] = b, wss[idxs] = c, nes[idxs] = hs[a], hs[a] = idxs ++ ;
}
int l[N];
void dijkstra(int s){
	memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	heap.push({0, s});
	while (heap.size()){
		auto t = heap.top();
		heap.pop();
		int v = t.second;
		if (st[v]){
			continue;
		}
		st[v] = true;
		for (int i = h[v]; ~i; i = ne[i]){
			int j = e[i];
			if (dist[j] > dist[v] + w[i]){
				dist[j] = dist[v] + w[i];
				l[j] = v;
				heap.push({dist[j], j});
			}
		}
	}
}
void dijkstras(int s){
	memset(dists, 0x3f, sizeof dists);
	dists[s] = 0;
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	heap.push({0, s});
	while (heap.size()){
		auto t = heap.top();
		heap.pop();
		int v = t.second;
		if (sts[v]){
			continue;
		}
		sts[v] = true;
		for (int i = hs[v]; ~i; i = nes[i]){
			int j = es[i];
			if (dists[j] > dists[v] + wss[i]){
				dists[j] = dists[v] + wss[i];
				heap.push({dist[j], j});
			}
		}
	}
}
int main(){
	memset(hs,-1,sizeof hs);
	memset(h, -1, sizeof h);
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= m; i ++ ){
		int a,b,c;
		scanf("%d%d",&a,&b);
		add(a,b,1);
		adds(b,a,1);
	}
	dijkstra(1);
	dijkstras(1);
	int res = 1e9;
	for (int i = 2; i <= n; i ++ ){
		res = min(res,dist[i] + dists[i]);
	}
	if (res == 1e9){
		cout << -1;
		return 0;
	}
	cout << res;
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc376_d)
## 思路
一道 bfs 板子题。从 $1$ 开始广搜，遍历每一个点，第一次回到 $1$ 就为最小环的长度。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m;
int vis[N];
vector<int> tr[N];

void bfs()
{
	queue<pair<int, int> > q;
	q.push(make_pair(1, 0));
	while (q.size())
	{
		pair<int, int> u = q.front();
		q.pop();
		if (u.first == 1 && vis[u.first])
		{
			printf("%d\n", u.second);
			exit(0);
		}
		else if (vis[u.first]) continue;
		vis[u.first]++;
		for (auto v : tr[u.first])
		{
			q.push(make_pair(v, u.second + 1));
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		tr[u].push_back(v);
	}
	bfs();
	printf("-1\n");
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

简单图论题。

这道题要我们找包含 $1$ 的最小环。不难发现我们从所有与 $1$ 相连的点开始做多源最短路，如果最后还能回到 $1$ 号节点，那么答案就是此时的距离加一。

那好像就没了。

[提交记录](https://atcoder.jp/contests/abc376/submissions/58960864)

---

## 作者：WuMin4 (赞：0)

## [[ABC376D] Cycle](https://atcoder.jp/contests/abc376/tasks/abc376_d)

## 题意

对一个边权为 $1$ 的简单有向图找一个经过点 $1$ 的环的最小长度。

## 思路

因为边权为 $1$，所以可以直接从点 $1$ 跑 bfs，找出到每个点的最短路径，最短环即为连向点 $1$ 的最短路径点 $v$ 的路径长度 $+1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[200005];
struct node{
	int x,d;
};
vector<int> t[200005];
int bfs(){
	queue<node> q;
	q.push({1,0});//从点1开始，路径长度为0
	while(!q.empty()){
		node u=q.front();q.pop();
		vis[u.x]=true;
		for(int v:t[u.x]){
			if(v==1)
				return u.d+1;//该点连向点1
			if(vis[v])
				continue;
			q.push({v,u.d+1});
		}
	}
	return -1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>n>>m;
	for(int x,y,i=1;i<=m;i++){
		cin>>x>>y;
		t[x].push_back(y);
	}
	cout<<bfs();
	return 0;
}
```

---

## 作者：light_searcher (赞：0)

问题实质上就是以 $1$ 为起点，求沿着有向边又走回 $1$ 的最小步数，那这个明显可以广搜吧。

由于边权都是 $1$，所以直接写普通广搜，每搜到一个点就把这个点标记一下，不能走标记过的点，记录步数，如果发现下一个点是 $1$ 了，直接输出答案，如果所有的点全搜完了，还没有找到 $1$ 的话那就无解。复杂度 $\mathcal O(n)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,vis[N];
vector<int>edge[N];
queue<pair<int,int> >q;
void bfs(int x){
	q.push({x,0});
	vis[x]=1;
	while(!q.empty()){
		int u=q.front().first,d=q.front().second;
		q.pop();
		for(int v:edge[u]){
			if(v==1){
				printf("%d",d+1);
				exit(0);
			}
			if(!vis[v]){
				vis[v]=1;
				q.push({v,d+1});
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
	}
	bfs(1);
	puts("-1");
	return 0;
}

---

## 作者：Binah_cyc (赞：0)

一个板子题。

一句话题意：在有向图中找包含 $1$ 号点的最小环。

环就是一个点走出去，转一圈之后再走回来走过的路径。因此，包含 $1$ 号点的最小环就可以理解为 $1$ 号节点到自己的最短路。

因此改改 Dijkstra 的板子就过了。单位权图最短路也可以用 BFS，这样能少一个 log。我赛时写的 Dijkstra。

代码：
```
// Problem: D - Cycle
// Contest: AtCoder - AtCoder Beginner Contest 376
// URL: https://atcoder.jp/contests/abc376/tasks/abc376_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5;
//#define int long long
int n,m;

int head[N],tot;
struct Node{int nxt,to;}edge[N<<1];
void add(int u,int v){edge[++tot]=Node{head[u],v},head[u]=tot;}

int dis[N],cnt;
bool vis[N];
struct node{int place,val;};
bool operator<(node a,node b){return a.val>b.val;}
priority_queue<node> q;
void dij(int start)
{
	memset(dis,0x3f,sizeof(dis));
	q.push(node{start,0});
	while(q.size())
	{
		auto now=q.top();
		q.pop();
		if(vis[now.place]) continue;
		if(now.place==1) cnt++;
		if(cnt==2) return ;
		if(now.place!=1) vis[now.place]=1;
		for(int i=head[now.place];i;i=edge[i].nxt)
		{
			if(!vis[edge[i].to]&&dis[edge[i].to]>now.val+1)
			{
				dis[edge[i].to]=now.val+1;
				q.push(node{edge[i].to,dis[edge[i].to]});
			}
		}
	}
}

signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++) cin>>x>>y,add(x,y);
	dij(1);
	if(dis[1]<=n) cout<<dis[1];
	else cout<<-1;//判无解
	return 0;
}
```

---

