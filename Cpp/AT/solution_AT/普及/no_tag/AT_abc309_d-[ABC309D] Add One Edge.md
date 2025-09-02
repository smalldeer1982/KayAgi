# [ABC309D] Add One Edge

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc309/tasks/abc309_d

$ N_1+N_2 $ 頂点 $ M $ 辺の無向グラフがあります。$ i=1,2,\ldots,M $ に対し、$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結びます。  
 また、以下を満たすことが保障されます。

- $ 1\ \leq\ u,v\ \leq\ N_1 $ を満たす整数 $ u,v $ に対し、頂点 $ u $ と頂点 $ v $ は連結
- $ N_1+1\ \leq\ u,v\ \leq\ N_1+N_2 $ を満たす整数 $ u,v $ に対し、頂点 $ u $ と頂点 $ v $ は連結
- 頂点 $ 1 $ と頂点 $ N_1+N_2 $ は非連結
 
次の操作をちょうど $ 1 $ 回行います。

- $ 1\ \leq\ u\ \leq\ N_1 $ を満たす整数 $ u $ と $ N_1+1\ \leq\ v\ \leq\ N_1+N_2 $ を満たす整数 $ v $ を選び、頂点 $ u $ と頂点 $ v $ を結ぶ辺を追加する
 
操作後のグラフにおいて、頂点 $ 1 $ と頂点 $ N_1+N_2 $ は必ず連結であることが示せます。そこで、頂点 $ 1 $ と頂点 $ N_1+N_2 $ を結ぶ経路の長さ(辺の本数)の最小値を $ d $ とします。

操作で追加する辺を適切に選んだ時にありえる $ d $ の最大値を求めてください。

  連結とは？ 無向グラフの頂点 $ u,v $ が連結であるとは、頂点 $ u $ と頂点 $ v $ を結ぶ経路が存在することをいいます。

## 说明/提示

### 制約

- $ 1\ \leq\ N_1,N_2\ \leq\ 1.5\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ b_i\ \leq\ N_1+N_2 $
- $ i\ \neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- $ 1\ \leq\ u,v\ \leq\ N_1 $ を満たす整数 $ u,v $ に対し、頂点 $ u $ と頂点 $ v $ は連結
- $ N_1+1\ \leq\ u,v\ \leq\ N_1+N_2 $ を満たす整数 $ u,v $ に対し、頂点 $ u $ と頂点 $ v $ は連結
- 頂点 $ 1 $ と頂点 $ N_1+N_2 $ は非連結
- 入力はすべて整数
 
### Sample Explanation 1

$ u=2,v=5 $ として操作することで $ d=5 $ と出来ます。これが最大値です。 !\[\](https://img.atcoder.jp/abc309/a64d8034b08cfa7d1f655767cc164653.png)

## 样例 #1

### 输入

```
3 4 6
1 2
2 3
4 5
4 6
1 3
6 7```

### 输出

```
5```

## 样例 #2

### 输入

```
7 5 20
10 11
4 5
10 12
1 2
1 5
5 6
2 4
3 5
9 10
2 5
1 4
11 12
9 12
8 9
5 7
3 7
3 6
3 4
8 12
9 11```

### 输出

```
4```

# 题解

## 作者：wangchai2009 (赞：3)

### 题目大意

给定两个点集，分别包含 $N_1$ 和 $N_2$ 个点。点集中的点共用 $M$ 条无向边相连。对于一个点集中的任意两点，满足两点连通；对于点 1 和点 $(N_1 + N_2)$，保证不连通。

现让你在两个点集之间添加一条边，最大化点 1 到点 $(N_1 + N_2)$ 的最短距离。

在本题中，两点间的距离用两点间路径所包含的边数表示。

### 思路

~~赛时の奇妙解题思路~~

+ 看到 “最短距离最大化”，想到二分答案。

+ 很显然，在两个点集中添加一条边后，点 1 和点 $(N_1 + N_2)$ 一定连通。

重点在二分答案的 check 函数上。对于我们每次二分出来的 $d$, 显然代表的是点 1 到点 $(N_1 + N_2)$ 之间的最短距离，如何判断 $d$ 是否合法？

我们可以将点 1 到点 $(N_1 + N_2)$ 之间的最短路径分为 3 段：

1. 第一段：点 1 到 点 1 所在点集中 $i$ 点的最短距离 $dis1_i$.
2. 第二段：两点集之间的连线，长度为 1.
3. 第三段：点 $(N_1 + N_2)$ 到 点 $(N_1 + N_2)$ 所在点集中 $j$ 点的最短距离 $dis2_j$.

很显然有
$$d = dis1_i + 1 + dis2_j$$

对式子进行变形，有
$$d - 1 - dis1_i = dis2_j$$

其中 $dis1_i$ 和 $dis2_j$ 可以用最短路预处理，用一个 map 数组映射 $dis2$ 中的值来判断二分出来的 $d$ 是否存在（如果不理解可移步代码）。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
const int N = 3e5 + 5, M = 6e5 + 5;
int n1, n2, m, u, v;
int h[N], e[M], ne[M], idx;
int l, r, mid;
map <int, int> mp;
 
void add(int u, int v)
{
	e[++idx] = v;
	ne[idx] = h[u];
	h[u] = idx;
}
class distance
{
	public:
		void spfa(int s)
		{
			queue <int> q;	q.push(s);
			memset(dis, INF, sizeof dis);
			vis[s] = true;	dis[s] = 0;
			while(!q.empty())
			{
				int u = q.front();
				q.pop();
				vis[u] = false;
				for (int i = h[u]; i; i = ne[i])
				{
					int v = e[i];
					if(dis[v] > dis[u] + 1)
					{
						dis[v] = dis[u] + 1;
						if(!vis[v])
						{
							vis[v] = true;
							q.push(v);
						}
					}
				}
			}
		}
		int Getdis(int pos)	{return dis[pos];}
	private:
		int dis[N];
		bool vis[N];
} a1, a2;
bool check(int x)
{
	x -= 1;
	for (int i = n1 + 1; i <= n1 + n2; i++)
		if(x - a2.Getdis(i) >= 0 && mp [x - a2.Getdis(i)])
			return true;
	return false;
}
int main()
{
	scanf("%d%d%d", &n1, &n2, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	a1.spfa(1); a2.spfa(n1 + n2);
	for (int i = 1; i <= n1; i++)	mp[a1.Getdis(i)] = 1;
	l = 1, r = 3e5+5;
	while(l < r)
	{
		mid = (l + r + 1) >>1;
		if(check(mid))	l = mid;
		else	r = mid - 1;
	}
	printf("%d",l);
}
```
完结撒花 ヾ(≧▽≦*)o .

---

## 作者：hellolin (赞：3)

## AtCoder Beginner Contest 309 - D - Add One Edge

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc309_d) | [AtCoder 题面](https://atcoder.jp/contests/abc309/tasks/abc309_d) | [前往 blog.hellolin.cf 获取更好的阅读体验](https://blog.hellolin.cf/articles/c9c216c5.html)

在第一部分（点 $1$ 到点 $N_1$）和第二部分（点 $N_1+1$ 到 $N_1+N_2$）各跑一遍 dijkstra，找到离 $1$ 最远的点和离 $N_1+N_2$ 最远的点，两个点一连，这样构成的 $1$ 到 $N_1+N_2$ 的路径是最长的。

``` cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;

constexpr static ll N = 3e5+114, INF = 1145141919;

ll n1, n2, m, a, b;

vector<ll> g1[N], g2[N];
__gnu_pbds::priority_queue<pair<ll,ll>, greater<pair<ll,ll>>, pairing_heap_tag> q;
ll dis[N];
bool vis[N];

ll ans1, ans2;

void dij(ll l, ll s) {
    dis[s]=0;
    q.push(make_pair(0,s));
    while(q.size()) {
        ll p = q.top().second;
        q.pop();
        if(vis[p]) continue;
        vis[p] = 1;

        if(l==1) {
            for(auto i:g1[p]) {
                ll v=i, w=1;
                if(dis[v]>dis[p]+w) {
                    dis[v]=dis[p]+w;
                    q.push(make_pair(dis[v], v));
                }
            }
        } else {
            for(auto i:g2[p]) {
                ll v=i, w=1;
                if(dis[v]>dis[p]+w) {
                    dis[v]=dis[p]+w;
                    q.push(make_pair(dis[v], v));
                }
            }
        }
    }
}

void solve() {
    cin >> n1 >> n2 >> m;
    for(ll i=1; i<=m; i++) {
        cin >> a >> b;
        if(a>n1||b>n1) { // 在第二部分
            g2[a].push_back(b);
            g2[b].push_back(a);
        } else { // 在第一部分
            g1[a].push_back(b);
            g1[b].push_back(a);
        }
    }

    fill(dis+1, dis+n1+n2+1, INF);
    dij(1, 1), dij(2, n1+n2);

    for(ll i=1; i<=n1; i++) {
        ans1 = max(ans1, dis[i]);
    }
    for(ll i=n1+1; i<=n1+n2; i++) {
        ans2 = max(ans2, dis[i]);
    }
    cout << ans1 + ans2 + 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc309_d)


#### 思路

读题可知，有两个图，用一条边连接两个图使 $1$ 到 $n1 + n2$ 的最短距离最长，不难想到求最短路，求出第一张图每个点到 $1$ 的最短路，第二张图每个点到 $n1 + n2$ 的最短路，找出两边最长的，加起来再加一就是这道题的答案了。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,n2,m,x,y,bj[800010],d[1000010],jj,ma1,ma2,v[1000010];
vector<int>a[800010];
queue<int>q;
void bfs(int x,int oo)//求最短路
{
	while(!q.empty())
	{
		jj = q.front();
		d[jj] = 0;
		for(int i = 0;i < a[jj].size();i++)
		{
			if(bj[a[jj][i]] == 1e8 || bj[a[jj][i]] > bj[jj] + 1) 
			{
				bj[a[jj][i]] = bj[jj] + 1; 
				if(!d[a[jj][i]])
				{
					v[a[jj][i]] = oo;
					d[a[jj][i]] = 1;
					q.push(a[jj][i]);
				}
			}	
		}
		q.pop();
	}
	return;
}
int main()
{
	scanf("%d%d%d",&n1,&n2,&m);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for(int j = 1;j <= n1 + n2;j++) bj[j] = 1e8;
	bj[1] = 0;
	q.push(1);
	bfs(1,1);//每个点到 1 的最短路
	//
	bj[n1 + n2] = 0;
	q.push(n1 + n2);每个点到 n1 + n2 的最短路
	bfs(n1 + n2,2);
	for(int j = 1;j <= n1 + n2;j++) if(v[j] == 1) ma1 = max(ma1,bj[j]);//求离 1 最远的
	for(int j = 1;j <= n1 + n2;j++) if(v[j] == 2)ma2 = max(ma2,bj[j]);//求离 n1 + n2 最远的
	cout << ma1 + ma2 + 1;
    return 0;
}


```


---

## 作者：2huk (赞：1)

[AtCoder ABC309 D - Add One Edge](https://atcoder.jp/contests/abc309/tasks/abc309_d)

## 题目描述

有一张 $(N_1 + N_2)$ 个点 $M$ 条边的无向图，且保证：

- 对于所有 $u, v \in [1, N_1]$，$u$ 点和 $v$ 点连通；
- 对于所有 $u, v \in [N_1 + 1, N_1+N_2]$，$u$ 点和 $v$ 点连通；
- $1$ 点和 $(N_1 + N_2)$ 点不连通。

现在你需要选择一个点 $u \in [1, N_1]$ 和一个点 $v \in [N_1 + 1, N_1+N_2]$，连接这两个点。

问连接后从 $1$ 点走到 $(N_1 + N_2)$ 点的最短路径（路径上的边数）最大是多少。

$1 \le N_1, N_2 \le 1.5 \times 10^5$，$0 \le M \le 3 \times 10^5$。

## 分析

题目中给的 $3$ 个输入的保证其实就是说明读入的实际上是两个连通图，其中第一个图有 $N_1$ 条边，第二个图有 $N_2$ 条边。

现在要从两个完全独立的图中选择两点连接，使得从 $1$ 点走到 $(N_1 + N_2)$ 点的最短路径最大。

我们可以分别求每一张图的最大答案，然后相加，这样就能得到最大的最终答案。

具体地，如果要让总路程最大，那么也就是要在图一中找到一个距离 $1$ 点最远的点，再从图 $2$ 中找到一个距离 $(N_1 + N_2)$ 最远的点，然后连接这两个点即可。当然，这里的距离指最短距离。

因为两图相互独立，所以两边同时取最大是不会出现问题的。

假如图一中距离 $1$ 点最远距离为 $k_1$，图二中距离 $(N_1 + N_2)$ 点最远距离为  $k_2$，那么答案为 $(k_1 + k_2 + 1)$。

找最短路最大的距离，可以先求出 $1$ 点和图一中每个点之间的距离，再求出 $(N_1 + N_2)$ 点和图二中每个点之间的距离，然后分别取 $\max$，计算答案输出即可。

由于是无权图，求最短路可以直接 `BFS`。总时间复杂度为 $\Theta(n)$。

一些细节在[代码](https://atcoder.jp/contests/abc309/submissions/43395661)中有所体现。



---

## 作者：DengDuck (赞：0)

这道题非常简单啊！

我们考虑以下一条最短路的构成，一定是 $1$ 所在的连通块的一条 $1$ 到 $x$ 的路径，一条 $x$ 到 $y$ 的边（即我们添加的那条边），一条 $n_1+n_2$ 所在的连通块的 $y$ 到 $n_1+n_2$ 的路径。

显然三个区域并不关联，我们贪心地让三个最大。

也就是说吗，我们找一条 $1$ 所在的连通块的最长路，再找一条 $n_1+n_2$ 所在的连通块的最长路，答案即为两者之和加一。

由于需要跑 BFS 最短路，时间复杂度为 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e6+5;
LL n1,n2,m,x,y,dis[N],mn,mn2;
vector<LL>v[N];
queue<LL>q;
void bfs(LL x)
{
	while(!q.empty())q.pop();
	q.push(x);
	while(!q.empty())
	{
		LL t=q.front();
		q.pop();
		for(LL i:v[t])
		{
			if(dis[i]>dis[t]+1)
			{
				dis[i]=dis[t]+1;
				q.push(i);
			}
		}
	}
}
int main()
{
	scanf("%lld%lld%lld",&n1,&n2,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	memset(dis,127,sizeof(dis));
	dis[1]=0,dis[n1+n2]=0;
	bfs(1),bfs(n1+n2);
	for(int i=2;i<=n1;i++)mn=max(mn,dis[i]);
	for(int i=n1+1;i<n1+n2;i++)mn2=max(mn2,dis[i]);
	printf("%lld",mn+mn2+1);
}
```

---

## 作者：Loser_Syx (赞：0)

注意此题其中 $1 \sim n1$ 和 $n1+1 \sim n1+n2$ 是两个分别的连通块，然后我们要在这两个连通块连一条边，使得 $1$ 和 $n1+n2$ 的距离最长，那么此时我们就可以对于 $1$ 和 $n1+n2$ 跑两次最短路，最后我们对于每个答案的最大值和，在这两个结束的位置连边，答案就是最大值和 $+1$。

[代码](https://atcoder.jp/contests/abc309/submissions/43374046)

---

## 作者：small_john (赞：0)

## 思路

没见过如此简单的 D 题。

用单源最短路求出第 $1$ 个点到第 $1\sim n1$ 个点和第 $n1+n2$ 个点到第 $n1+1\sim n1+n2$ 个点的距离。记为 $d$ 数组。

从 $d_1\sim d_{n1}$ 和 $d_{n1+1}\sim d_{n1+n2}$ 找出最大值，记为 $mx1,mx2$，最后输出 $mx1+mx2+1$ 即可（要花 $1$ 条边连接两个点）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n1,n2,m,d[N],nxt[2*N],head[2*N],to[2*N],cnt;
priority_queue<pair<int,int> > q;
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	nxt[++cnt] = head[y];
	head[y] = cnt;
	to[cnt] = x;
}
void dijkstra()
{
	d[1] = d[n1+n2] = 0;
	q.push(make_pair(0,1)),q.push(make_pair(0,n1+n2));
	while(!q.empty())
	{
		int x = q.top().second;
		q.pop();
		for(int j = head[x];j;j = nxt[j])
			if(d[x]+1<d[to[j]])
				d[to[j]] = d[x]+1,q.push(make_pair(-d[to[j]],to[j]));
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n1>>n2>>m;
	memset(d,0x3f,sizeof(d));
	for(int i = 1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
	}
	dijkstra();
	int mx1 = 0,mx2 = 0;
	for(int i = 1;i<=n1;i++)
		mx1 = max(mx1,d[i]);
	for(int i = n1+1;i<=n1+n2;i++)
		mx2 = max(mx2,d[i]);
	cout<<mx1+mx2+1;
 	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

两张无向图，节点编号分别为 $[1,n_1]$ 和 $[n_1+1,n_1+n_2]$。两张图各选一个节点，并在这两个点间连一条边，求连完边后点 $1$ 和 $n_1+n_2$ 间的最短路径长度的最大值。

## 思路

假设我们选了 $u(1\le u\le n_1)$ 和 $v(n_1+1\le v\le n_1+n_2)$ 两个点，那么点 $1$ 和 $n_1+n_2$ 间的最短路径即点 $1$ 到 $u$ 的最短路径和点 $n_1+n_2$ 到 $v$ 的最短路径之和再加 $1$。

那么结论就很明显了，我们 ``bfs`` 分别找出离点 $1$ 和 $n_1+n_2$ 最远的点则距离最长。求出距离和后千万别忘加 $1$。

## 代码

```cpp
ll n1,n2,m,ans,sum,vis[300005],dis[300005],maxi,maxx;
vector<int>e[300005];
void bfs(int x){
    queue<int>q;
    q.push(x);
    vis[x]=1;
    while(!q.empty()){
	int a=q.front();
	q.pop();
	for(auto i:e[a]){
	    if(!vis[i]){
		vis[i]=1;
		dis[i]=dis[a]+1;
		q.push(i);
	    }
	}	
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n1>>n2>>m;
    for(int i=1;i<=m;i++){
	int u,v;
	cin>>u>>v;
	e[u].pb(v);
	e[v].pb(u);
    }
    bfs(1);
    for(int i=1;i<=n1;i++)maxi=max(maxi,dis[i]);
    bfs(n1+n2);
    for(int i=n1+1;i<=n1+n2;i++)maxx=max(maxx,dis[i]);
    cout<<maxi+maxx+1<<endl;
    return 0;
}
```


---

## 作者：zhangjiting (赞：0)

## 思路

在点 $1$ 到 $N_1$ 之间和点 $N_1+1$ 到点 $N_1+N_2$ 之间各跑一次最短路，找到两部分各自找到与点 $1$ 距离最远的和与点 $N_1+N_2$ 最远的点，加起来就是答案了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[300005],head[300005],nxt[600005],to[600005],tot,x,y,ans1,ans2;
queue<int> q;
void bfs(int at){
	q.push(at);
	dis[at]=0;
	while(q.size()){
		x=q.front();
		q.pop();
		for(int i=head[x];i!=0;i=nxt[i]){
			y=to[i];
			if(dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
}
int main(){
	int n1,n2,m;
	cin>>n1>>n2>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		to[++tot]=y;
		nxt[tot]=head[x];
		head[x]=tot;
		to[++tot]=x;
		nxt[tot]=head[y];
		head[y]=tot;
	}
	memset(dis,-1,sizeof(dis));
	bfs(1);for(int i=1;i<=n1;i++) ans1=max(ans1,dis[i]);
	bfs(n1+n2);for(int i=n1+1;i<=n1+n2;i++) ans2=max(ans2,dis[i]);
	cout<<ans1+ans2+1;
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 分析

一道 rz 题目。

我们分开求，因为要使建边之后的 $1$ 到 $n1+n2$ 的最短路最大，建的这条边长度是固定的，所以要使两边最短路最大。跑两遍 dijsktra，得到节点 $1$ 开始，能到达点的所有最短路与节点 $n1+n2$ 开始，能到达所有点最短路。最后找到两边的最大值相加再加上 $1$ 即可。

一句话概括，就是：可变化值最大和加上定值等于最大化价值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=2e6+10;
int n1,n2,m;
int e[N],h[N],ne[N],idx;
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
int dis[N],vis[N];
void dj(int x){
	priority_queue<PII,vector<PII>,greater<PII> > qu;
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	while(!qu.empty()){
		qu.pop();
	}
	qu.push({0,x});
	dis[x]=0;
	while(!qu.empty()){
		PII now=qu.top();qu.pop();
		if(vis[now.y]) continue;
		vis[now.y]=1;
		for(int i=h[now.y];~i;i=ne[i]){
			int j=e[i];
			if(dis[j]>now.x+1&&!vis[j]){
				dis[j]=now.x+1;
				if(!vis[j]){
					qu.push({dis[j],j});
				}
			}
		}
	}
}
int maxx1,maxx2;
signed main(){
	cin>>n1>>n2>>m;
	memset(h,-1,sizeof(h));
	for(int i=1;i<=m;i++){
		int a,b;cin>>a>>b;
		add(a,b),add(b,a);
	}
	dj(1);
	for(int i=1;i<=n1;i++){
		if(maxx1<dis[i]){
			maxx1=dis[i];
		}
	}
	dj(n1+n2);
	for(int i=n1+1;i<=n1+n2;i++){
		if(maxx2<dis[i]){
			maxx2=dis[i];
		}
	}
	return cout<<maxx1+1+maxx2,0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc309_d)   
一道很水的图论。   
## 题意
给你两张无向图，这两张图的点编号分别是 $[1,n_1]$ 和 $[n_1+1,n_1+n_2]$。      
我们现在要把这两张图的任意两个结点连边，问连起来之后，点 $1$ 到点 $n_1+n_2$ 的最短路径最长是多少。    
## 题解
我们设我们连接了 $u$ 和 $v$ 两个结点，那么最短路径实际上可以表示为（接下来用 $\operatorname{dis}(a,b)$ 表示 $a$ 和 $b$ 两个结点之间的最短距离）：$\operatorname{dis}(1,n_1+n_2)=\operatorname{dis}(1,u)+\operatorname{dis}(v,n_1+n_2)+1$。        
这里因为 $u$ 和 $v$ 直接连了边，所以我们不需要考虑其他走法。     
我们先以 $1$ 和 $n_1+n_2$ 以源点跑两次最短路，之后找出 $\operatorname{dis}(1,u)$ 和 $\operatorname{dis}(v,n_1+n_2)$ 的最大值，再加上一即可。     
时间复杂度为 $O(m\log m)$，可以通过。   
[CODE](https://www.luogu.com.cn/paste/q3a3yynr)

---

## 作者：Mu_leaf (赞：0)

## [题意]
给出两个不联通的图求将 2 个图任意连接 1 条边后点 1 到点 $n1+n2$ 的最短路径最长是多少。

## [思路]

好水的广搜题。

以下的点 $1$ 和 $n1+n2$ 统称为源点。

首先可以发现，题目要求只允许连接 1 条边且所有变边权为 1，我们就可以将问题变成，找到两个图中距离源点最短路径最长。

也就是说我们需要找到两个图中最短路径分别距离 $1$ 和 $n1+n2$ 最远的点。然后再将两个点连接起来，由于边权我们知道为 1。则连接起来后的答案便是两个图中与源点构成最长的最短路径的距离 $+1$ 就可以了。

首先用 bfs 从点 1 出发求出在第一个图中路径最长的路径即为 $mx1$。

同理从 $n1+n2$ 出发求出 $mx2$。

于是答案便是 $mx1+mx2+1$。

然后就结束力。

## [Code](https://atcoder.jp/contests/abc309/submissions/43375042)



---

