# [ABC252E] Road Reduction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc252/tasks/abc252_e

AtCoder 王国には都市 $ 1,2,\ldots,N $ の $ N $ 個の都市と、道路 $ 1,2,\ldots,M $ の $ M $ 本の道路があります。  
道路 $ i $ は都市 $ A_i $ と $ B_i $ を双方向に結び、距離は $ C_i $ です。  
どの都市間もいくつかの道路を通って行き来することができます。

財政難である王国は、どの都市間もいくつかの道路を通って行き来できるという条件を満たすように $ N-1 $ 本の道路を保守し、それ以外の道路を廃道にすることにしました。

保守する道路のみを通って都市 $ 1 $ から都市 $ i $ へ移動するときの距離を $ d_i $ とするとき、保守する道路の選び方であって、$ d_2+d_3+\ldots+d_N $ を最小化するようなものを $ 1 $ つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ i\neq\ j $ のとき、$ (A_i,B_i)\neq(A_j,B_j) $
- $ 1\leq\ C_i\ \leq\ 10^9 $
- どの都市間もいくつかの道路を通って行き来することができる
- 入力に含まれる値は全て整数である

### Sample Explanation 1

保守する道路の選び方と $ d_i $ の値は次のようになります。 - 道路 $ 1,2 $ を保守するとき、$ d_2=1 $, $ d_3=3 $ - 道路 $ 1,3 $ を保守するとき、$ d_2=1 $, $ d_3=10 $ - 道路 $ 2,3 $ を保守するとき、$ d_2=12 $, $ d_3=10 $ よって、道路 $ 1,2 $ を保守するときに $ d_2+d_3 $ が最小になります。

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 2
1 3 10```

### 输出

```
1 2```

## 样例 #2

### 输入

```
4 6
1 2 1
1 3 1
1 4 1
2 3 1
2 4 1
3 4 1```

### 输出

```
3 1 2```

# 题解

## 作者：zlqwq (赞：2)

请您在先学习图论后再阅读本文。

显然要先跑一遍 dijkstra，考虑一下这个过程中一共 $n$ 个点和 $n-1$ 条边。

这样显然就变成了一棵树。

计算答案直接在松弛的过程中顺便维护一个数组去计算就行。

---

## 作者：xixiyan (赞：2)

# 题目：[ABC252E] Road Reduction
看到这道题没有链式前向星题解，那我必须来写一个了。

注:不会最短路 dijkstra 算法误入。
## 题目大意：
给你一个 $n$ 个节点 $m$ 条边的**无向图**，请你找出从一到其余点的单源**最短路**，并输出所有**边的编号**。
## 分析：
首先根据题意，跑一遍 dijkstra 是必要的，然后我们可以在 dijkstra 过程中进行操作。

不难发现，在跑最短路时正好会有 $n-1$ 条边，正不正是一颗树吗？并且每个点到 $1$ 号节点的距离都是最短的，刚好满足题意。

接下来就是处理处理答案的问题了，其实在最短路中，每条边只会被松弛一次，那我们只需要在松弛的时候顺便更新答案即可。

至于链式前向星，只需要把编号和权值放到一起就好了。

具体的详见代码吧，直接看文字说明不太好理解。

对了：**要开 long long**。
## Code:

```cpp
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define int long long //十年OI一场空 
struct qwq{
	int w;
	int d;
	bool operator < (const qwq& a) const{
		return w>a.w;
	} 
}; 
priority_queue<qwq> o_o;
struct bian{
	int w;
	int num;
}W[400001];//因为一条边只会有一个权值，所以把权值和编号绑定就好了 

int head[200001],Nxt[400001],To[400001],tot;//链式前向星 

const int INF=1e18;//都开long long了肯定要用1e18 

int n,m,dis[200001];//dijkstra
bool vis[200001];

int ans[200001]; //答案数组 
void add(int x,int y,int w){
	W[++tot].w=w;
	To[tot]=y;
	Nxt[tot]=head[x];
	head[x]=tot;
}//存边 

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		dis[i]=INF;
	}//初始化 
	for(int i=1;i<=m;i++){
		int x,y,w;
		scanf("%d %d %d",&x,&y,&w);
		add(x,y,w);
		W[tot].num=i;
		add(y,x,w);
		W[tot].num=i;//注意，正边和反边的编号是一样的！！！ 
	}
	
	dis[1]=0;
	o_o.push((qwq){0,1});
	
	while(!o_o.empty())
	{
		int d=o_o.top().d;
		o_o.pop();
		if(vis[d]) continue;
		vis[d]=1;
		for(int i=head[d],y;i;i=Nxt[i])
		{
			y=To[i];			
			if(dis[y]>dis[d]+W[i].w)
			{
				dis[y]=dis[d]+W[i].w;
				o_o.push((qwq){dis[y],y});
				ans[y]=W[i].num;//松弛时顺便更新答案，相当于和dis[i]同时更改 
			}		
		}
	}
	for(int i=2;i<=n;i++) printf("%lld ",ans[i]);//不要输出1号节点 
	return 0;
}
```

---

## 作者：FL_sleake (赞：2)

## 题意简述

给定 $ n $ 个点 $ m $ 条边的无向连通简单图，每条边为 $ a_i $ 到 $ b_i $，权值为 $ c_i $。你需要构造一棵生成树，最小化点 $ 1 $ 在生成树上到其它所有点的距离和，输出生成树的所有边的序号。如果有多个方案随便输出一个即可。

## 解题思路

我们令 $dis_i$ 表示 $1$ 到 $i$ 的最短路的长度，$D_i$ 表示在某种选择的方案下 $1$ 到 $i$ 的长度。不难发现一定会有 $D_i \geq dis_i$。所以，在选择某一条边后，如果有 $D_i=dis_i$，那么选择这条边就是最优的。选边的过程可以在跑 dijkstra 的过程中顺便完成掉。具体细节见代码及注释。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int v,w,id;//id表示边的编号
	bool operator<(const node &b)const{
		return w>b.w;//方便priority_queue从小到大排序
	}
};
vector<node> G[200010];
int n,m,ans[200010],dis[200010];
priority_queue<node> q;
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	q.push({1,0,0});
    //其实q中不需要记录边的编号，这里偷了个懒，沿用了前面的结构体
	dis[1]=0;
    //初始化
	while(!q.empty()){
		int u=q.top().v,D=q.top().w;
		q.pop();
		if(dis[u]<D) continue;
        //没有这个判断将会在after_contest的数据上TLE。我也不知道为什么会TLE，但是加上绝对是正确的。（如有大佬知道可以告诉我qwq）
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].v,w=G[u][i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				ans[v]=G[u][i].id;//记录答案
				q.push({v,dis[v],0});
			}
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w,i});
		G[v].push_back({u,w,i});
	}
	Dijkstra();
	for(int i=2;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：FFTotoro (赞：2)

Upd：题解通道重新开放，重新递交审核。

可以由从起点为 $1$ 开始使用 Dijkstra 算法求最短路，就可以算出 $d_i$。

根据 Dijkstra 的更新情况，每个点都会被至少松弛一次，最后被松弛的那次对应一条边，而 $1$ 是起点，不会被其他边松弛，这样 $n-1$ 个点正好对应 $n-1$ 条边。问题就得到了解决。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  vector<vector<pii> > g(n);
  vector<int> w(m),p(n),d(n,1e18);
  for(int i=0;i<m;i++){
    int a,b; cin>>a>>b>>w[i];
    g[a-1].emplace_back(b-1,i);
    g[b-1].emplace_back(a-1,i);
  }
  priority_queue<pii,vector<pii>,greater<> >q;
  q.emplace(d[0]=0,0);
  while(!q.empty()){
    auto [f,e]=q.top(); q.pop();
    if(f>d[e])continue;
    if(e)cout<<p[e]+1<<' ';
    for(auto [v,i]:g[e]){
      if(d[e]+w[i]>=d[v])continue;
      p[v]=i; q.emplace(d[v]=d[e]+w[i],v);
    }
  } // Dijkstra
  return 0;
}
```

---

## 作者：Ascnbeta (赞：1)

##  [ABC252E] Road Reduction
最短路模板题，考察的是对 dijkstra 真正的理解。

## 思路分析
因为要求从结点 $1$ 到其他结点的路径最短，因此我们肯定要跑一遍 dijkstra，然后你就会发现，所有松弛成功的边就是可以选出的边。

为什么呢？考虑 dijkstra 的执行过程。发现我们每次是从堆中取出了一个未被确定最短路的结点中路径最短的结点，然后它就再也不会被其他结点更新。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ka4wa6kz.png)

结点 $3$ 的最短路一旦被 $2$ 或 $4$ 更新过后，一定不会再被另一个点更新，因此选出的一定是 $n-1$ 条边，既一棵生成树。

## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+10;
int n,m;
struct edge{
	int to,nxt,w,num;
}e[maxn<<1];
int head[maxn],tot;
inline void add(int u,int v,int w,int num) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	e[tot].w = w;
	e[tot].num = num;
	head[u] = tot;
}
bool f[maxn];
int dis[maxn],ans[maxn];
struct node{
	int p,w;
	bool operator < (const node &x) const{
		return w > x.w;
	}
};
priority_queue<node> q;
inline void dij(int s) {
	q.push(node{s,0});
	memset(dis,0x3f,sizeof(dis));
	dis[s] = 0;
	while (!q.empty()) {
		node t = q.top();
		q.pop();
    if (f[t.p]) continue;
		f[t.p] = true;
		for (int i = head[t.p]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[t.p] + e[i].w) {
				dis[v] = dis[t.p] + e[i].w;
				q.push(node{v,dis[v]});
				ans[v] = e[i].num;
			}
		}
	}
}
signed main () {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x,y,z;
		cin >> x >> y >> z;
		add(x,y,z,i);
		add(y,x,z,i);
	}
	dij(1);
	for (int i = 2; i <= n; i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}
```

---

## 作者：imsbNR (赞：1)

# 题解：AT_abc252_e [ABC252E] Road Reduction

## 思路

跑一边 dijkstra 即可，因为 dijkstra 算法对于连通图会在原来的答案上添加一条边，明显的，跑一遍 dijkstra 经过的遍刚好 $n-1$ 条并且联通，即为一颗生成树，且除 $1$ 以外的所有节点到 $1$ 的距离最小。

## code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
map <ll, map <ll, ll>> l;
struct node {
	ll to, val, i;
	friend bool operator < (node a, node b) {
		return a.val > b.val;
	}
};
priority_queue <node> q;
vector <node> G[maxn];
ll n, m, u, v, w, d[maxn], f[maxn], vis[maxn];
void add_edge(ll a, ll b, ll c, ll dd) {
	G[a].push_back({b, c, dd});
	return;
}
void dijkstra() {
	memset(d, 0x3f, sizeof d);
	q.push({1, 0, 0});
	d[1] = 0;
	while (!q.empty()) {
		ll u = q.top().to, dd=q.top().val;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (auto g : G[u]) {
			ll v = g.to, w = g.val;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				f[v] = g.i;
				q.push({v, d[v], 0});
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		l[u][v] = l[v][u] = i;
		add_edge(u, v, w, i);
		add_edge(v, u, w, i);
	}
	dijkstra();
	for (int i = 2; i <= n; i++)
		cout << f[i] << ' ';
	return 0;
}
```

~~珍爱生命，原理链式前向星。~~

AC 记录： [link](https://atcoder.jp/contests/abc252/submissions/58527559) 。

---

## 作者：ChuYilin2011 (赞：1)

首先，显然一个结点到点 $1$ 的最短距离小于等于该结点和点 $1$ 之间其他路径的距离。那么根据同向不等式的可叠加性，所有结点到点 $1$ 的最短距离和小于等于其他方案的距离和。所以，那个最小的距离和就是每个结点到点 $1$ 的最短距离和。

那么，写一个 Dijkstra，然后答案应该就是在每个结点的最短路径上的所有边了。但是这样得到的图为什么一定是原图的一个生成树呢？

显然，该图是连通的。然后因为 Dijkstra 的原理是用得到最短路的点更新其他点，所以当一个除 $1$ 外的结点得到最短路时，一定只在原先答案的基础上增加一条边。总共 $n-1$ 个结点，就有 $n-1$ 条边，并且连通，这一定是原图的一个生成树。这叫“最短路径树”，有兴趣的可以去查查。

所以这就是本题思路：跑一遍 Dijkstra，顺便把最短路径经过的边记录下来就是答案。

提醒 dis 数组要开 long long。

~~都讲到这里了还不能自己写代码啊~~

---

