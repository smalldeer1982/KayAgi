# [ABC361E] Tree and Hamilton Path 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_e

AtCoder国には $ 1 $ から $ N $ の番号がついた $ N $ 個の街と $ 1 $ から $ N-1 $ の番号がついた $ N-1 $ 本の道路があります。

道路 $ i $ は街 $ A_i $ と街 $ B_i $ を双方向に結び、長さは $ C_i $ です。どの街同士も、いくつかの道路を通って互いに行き来することができます。

いずれかの街を出発し、道路による移動で全ての街を $ 1 $ 度以上訪れるための移動距離の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 入力は全て整数である
- どの街同士も、いくつかの道路を通って互いに行き来できる
 
### Sample Explanation 1

$ 4\ \to\ 1\ \to\ 2\ \to\ 1\ \to\ 3 $ と移動すると移動距離の合計は $ 11 $ となり、これが最小値です。 最初の街に戻ってくる必要はないことに注意してください。

### Sample Explanation 2

オーバーフローに注意してください。

## 样例 #1

### 输入

```
4
1 2 2
1 3 3
1 4 4```

### 输出

```
11```

## 样例 #2

### 输入

```
10
10 9 1000000000
9 8 1000000000
8 7 1000000000
7 6 1000000000
6 5 1000000000
5 4 1000000000
4 3 1000000000
3 2 1000000000
2 1 1000000000```

### 输出

```
9000000000```

# 题解

## 作者：chenzhaoxu2027 (赞：7)

# 题目大意

给你一棵带权树，寻找能够把所有点都遍历至少一遍的最短路径（可以回头）。

# 分析

如果我们需要一条回路，那么长度显然就是树上所有边权和的两倍。

但是题目不要求是回路，假设起点、终点分别是 $u$、$v$，所以说答案就是 $2 \times \sum_{e \in E}e_c-\operatorname{dis}(u,v)$。

要使答案最小化，就要使 $\operatorname{dis}(u,v)$ 最大。所以说求出树的直径就可以了。

> tips：不会求树直径的可以去[这里](https://oiwiki.com/graph/tree-diameter/)

这里我采用了两次 DFS 的方法，求出来以后带入公式就结束力。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,c,d[200005];
vector<int> g[200005];
vector<int> h[200005];
int sum;
void dfs(int u,int fa){
    for(int i=0;i<g[u].size();i++){
  	    int v=g[u][i],w=h[u][i];
        if(v==fa){
            continue;
        }
        d[v]=d[u]+w;
        if(d[v]>d[c]){
            c=v;
        }
        dfs(v,u);
    }
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back(v);
    	g[v].push_back(u);
	    h[u].push_back(w);
	    h[v].push_back(w);
    	sum+=w;
    }
    dfs(1,0);
    d[c]=0;
    dfs(c,0);
    cout<<sum*2-d[c];
    return 0;
}
```

---

## 作者：zrl123456 (赞：2)

[[ABC361E] Tree and Hamilton Path 2](https://www.luogu.com.cn/problem/AT_abc361_e)    
考察：树的直径，dfs，dp。   
题目简述：   
给定一棵有 $n$ 个点的树，从任意一个点开始，经过所有点后所走过的最短路径。  
一个点可以经过多次，最后不一定要回到原点。  
数据范围：
- $n\le 2\times 10^5$
------------
考虑下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ygahfk5w.png)  
其满足限制的最短路径是 $9\Rightarrow6\Rightarrow1\Rightarrow2\Rightarrow7\Rightarrow2\Rightarrow4\Rightarrow5\Rightarrow8\Rightarrow5\Rightarrow3$，长度为 $4+3+2+5+5+3+5+1+1+4=33$。  
我们将其标在树上，就成了下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/hb4jx8ok.png)
我们发现有向图比原树少了 $3$ 到 $9$ 的这一条路径，而这条路径就是树的直径。  
那么我们得出答案就是（设直径为 $len$）：
$$\sum_{(u_i,v_i,w_i)\in E}w_i-len$$
直径采用 dp 就可得到。  

代码：
```cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define int long long
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(reg int i=x;i<=(y);++i) 
#define per(i,x,y) for(reg int i=x;i>=(y);--i)
#define rpr(i,x,y,z) for(reg int i=x;i<=(y);i+=z)
#define epe(i,x,y,z) for(reg int i=x;i>=(y);i-=z)
#define endl '\n'
#define INF 1e16
#define pb push_back
#define fi first
#define se second
#define lcm(x,y) x/__gcd(x,y)*y
#define ull unsigned long long
#define prr make_pair
#define pii pair<int,int> 
#define gt(s) getline(cin,s)
#define at(x,y) for(reg auto x:y)
#define ff fflush(stdout)
#define mt(x,y) memset(x,y,sizeof(x))
#define idg isdigit
#define fp(s) string ssss=s;freopen((ssss+".in").c_str(),"r",stdin);freopen((ssss+".out").c_str(),"w",stdout);
#define sstr stringstream 
#define all(x) x.begin(),x.end()
#define mcy(a,b) memcpy(a,b,sizeof(b))
using namespace std;
const int N=2e5+5;
vector<pii >g[N];
int mx[N],mx2[N];
bool vis[N];
inl void dfs(int u,int &num){
	vis[u]=1;
	at(v,g[u])
		if(!vis[v.fi]){
			dfs(v.fi,num);
			if(mx[u]<mx[v.fi]+v.se){
				mx2[u]=mx[u];
				mx[u]=mx[v.fi]+v.se;
			}else mx2[u]=max(mx2[u],mx[v.fi]+v.se);
		}
	num=max(num,mx[u]+mx2[u]);
}
signed main(){
	fst;
	reg int n,num=0,ans=0;
	cin>>n;
	rep(i,2,n){
		reg int u,v,w;
		cin>>u>>v>>w;
		g[u].pb(prr(v,w));
		g[v].pb(prr(u,w));
		ans+=w<<1;
	}
	dfs(1,num);
	cout<<ans-num;
	return 0;
} 
```

---

## 作者：SpringFullGarden (赞：1)

## 题意

有一棵树，求从一个节点出发，遍历所有节点的最小路程。


## 思路

可以发现，如果遍历整棵树且需要返回开始的节点的路程为边权和的两倍，但是这道题不用返回，所以有一条路径不用走。

贪心地考虑，为了使路程最小，就要让不走的那一条路径最长。在一棵树上，最长路径就是直径。

所以答案为边权和的两倍减去直径的长度。

## 代码

```cpp
vector <pair <int, int> > e[200005];
ll dis[200005], lst;

void dfs(ll x, ll fa) {
	for(auto it : e[x]) {
		ll v = it.first, w = it.second;
		if(v == fa) continue;
		dis[v] = dis[x] + w;
		if(dis[v] > dis[lst]) lst = v;
		dfs(v, x);
	}
}
signed main() {
	ll n = rd(), sum = 0;
	for(ll i = 1; i < n; i++) {
		ll u = rd(), v = rd(), w = rd();
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
		sum += w;
	}
	dfs(1, 0);
	dis[lst] = 0;
	dfs(lst, 0);
	cout << sum * 2 - dis[lst];
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：1)

首先，你会发现这个图是一棵树。

所以，如果我们要求结束后要返回，那么每条边都要遍历 $2$ 次。那么如果不用返回呢？假设我们从 $x$ 点出发，那么结束肯定是在距离 $x$ 点最远的地方，也就是说我们要减去这棵树的直径。然后两遍 bfs 或 dfs 即可。

代码如下。

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

long long n, vis[200005], dis[200005], maxk;
long long sum;

vector <pair <long long, long long> > edge[200005];
queue <long long> q;

long long bfs(long long s) {
	q.push(s);
	vis[s] = 1;
	while(!q.empty()) {
		long long nx = q.front();
		q.pop();
		for(long long i = 0; i < edge[nx].size(); i++) {
			long long y = edge[nx][i].first, z = edge[nx][i].second;
			if(!vis[y]) {
				vis[y] = 1;
				dis[y] = dis[nx] + z;
				q.push(y);
			}
		}
	}
	for(long long i = 1; i <= n; i++) {
		if(dis[i] > dis[maxk]) maxk = i;
	}
	return maxk;
}

int main() {
	cin >> n;
	for(long long i = 1; i < n; i++) {
		long long u, v, w;
		cin >> u >> v >> w;
		edge[u].push_back(make_pair(v, w));
		edge[v].push_back(make_pair(u, w));
		sum += 2 * w;
	}
	long long t = bfs(1), tt = maxk;
	memset(dis, 0, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	maxk = 0;
	cout << sum - dis[bfs(tt)];
}
```

---

## 作者：Dws_t7760 (赞：1)

## Statement

给定一颗有 $N$ 个节点的带边权的无根树，求经过每一个节点至少一次的最短路径长度。

## Solution

任取一点为根节点，从根节点出发，若以 dfs 序遍历这棵树，易知路径长度为所有边权之和的两倍，且最后回到根节点。但可以发现遍历到最后一个节点时已经满足题意了，不需要返回，所以答案要减去最后一个节点到根节点的距离，考虑到路径最短，应减去最远的叶子节点的距离。

综上，由于是无根树，答案为 $2 \sum c - \left( \max _{i\in \left[ 1,n\right] ,j\in \left[ 1,n\right] }dis\left( i,j\right) \right)$，可以用二次扫描与换根解决，任取一根节点，跑出以每个节点为根的子树中到此节点距离的最大值，次大值以及最大值所属的子树。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define len 214514
struct nod { int id, s; };
int n, a, b, c, s[len], siz[len], ans, v[len], ts;
int zd[len], cd[len], zdf[len];
vector <nod> vec[len];
int mx(int a, int b) { return a > b ? a : b; }
void chg(int id, int f, int s) {
	if (s >= zd[id]) cd[id] = zd[id], zd[id] = s, zdf[id] = f;
	else if (s > cd[id]) cd[id] = s;
	return;
}
int get(int id, int f) { return f == zdf[id] ? cd[id] : zd[id]; }
void dfs(int x, int ss) {
	v[x] = 1;
	for (int i = 0; i < s[x]; i++) {
		int a = vec[x][i].id, b = vec[x][i].s;
		if (!v[a]) dfs(a, ss + b), siz[x] = mx(siz[x], siz[a] + b), chg(x, a, siz[a] + b);
	}
	v[x] = 0;
	return;
}
void dfs2(int x,int f) {
	int tmp = mx(f, siz[x]);
	ans = mx(tmp, ans), v[x] = 1;
	for (int i = 0; i < s[x]; i++) {
		int a = vec[x][i].id, b = vec[x][i].s;
		if (!v[a]) dfs2(a, mx(f, get(x, a)) + b);
	}
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) cin >> a >> b >> c, ts += c, s[a]++, vec[a].push_back({ b,c }), s[b]++, vec[b].push_back({ a,c });
	dfs(1, 0), ans = siz[1], dfs2(1, 0);
	cout << 0ll + 2ll * ts - ans;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC361E] Tree and Hamilton Path 2](https://www.luogu.com.cn/problem/AT_abc361_e)

板子。如果从根节点出发经过每一个点最后回到根节点，路径长度为 $\sum{c_i}\times 2$。那么最后停留在某一个点而不回到根节点，少的便是该点到根节点的距离，设该距离为 $dis$。则答案为 $\sum{c_i}\times 2-dis$。

$\sum{c_i}\times 2$ 是一定的，所以要让答案最小，就需要使 $dis$ 最大。$dis$ 是树上两点间距离，所以 $dis$ 最大为树的直径。所以答案就是 $\sum{c_i}\times 2$ 减去树的直径。对于树的直径，可以通过两遍 DFS 或树形 DP 求出。

---

## 作者：Dtw_ (赞：0)

# 思路
可以先考虑从某个节点走经过所有的点之后回到他的最短路径，那显然就是每条边都要走两遍。而现在，可以不用回来，那肯定是选一条最长的路只走一遍，其余的还是走两遍，而这又是一棵树，最长的路就是树的直径。

求一下树的直径就行了。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n;

int c, f[N];

vector<pair<int, int>> G[N];

void dfs(int u, int fa)
{
	for(auto e : G[u])
	{
		int v = e.fi, w = e.se;
		if(v == fa) continue;
		f[v] = f[u] + w;
		if(f[v] > f[c]) c = v;
		dfs(v, u);
	}
}

signed main()
{
	cin >> n;
	int res = 0;
	for(int i=1; i<n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back({v, w}), G[v].push_back({u, w});
		res += w * 2;
	}
	dfs(1, 0);
	f[c] = 0;
	dfs(c, 0);
//	cout << f[c] << endl;
	res -= f[c];
	cout << res;
	return 0;
}




```

---

## 作者：Ivan422 (赞：0)

题目大意：给出有边长的一颗无根树，求一条走完所有节点的路径，要求最短。

思路：为了防止走两遍一条边，可以从直径开始搜索，直径就只需要走一次了。接着，再散发出去走即可。用一句话概括就是：线段总长设为 $a$，直径长度设为 $b$，则答案是 $2\times a-b$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
struct l{int t,v;};
vector<l>e[N];
int n,u,v,w,mxl,dep[N],fa[N],f1,f2,fl,fr,ans,su;
bool blk[N];
void dfs(int v,int f){
	fa[v]=f;
	if(dep[mxl]<dep[v])mxl=v;
	for(auto li:e[v]){
		if(li.t==f||blk[li.t])continue;
		dep[li.t]=dep[v]+li.v;
		dfs(li.t,v);
	}
	return;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;ans+=w;
		e[u].push_back(l{v,w});
		e[v].push_back(l{u,w});
	}
    ans*=2;
	dep[1]=1; dfs(1,0); f1=mxl;
	dep[f1]=0;dfs(f1,0);f2=mxl;
    cout<<ans-dep[f2];
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们发现在访问每个节点至少一次之前，我们需要返回到祖先才能访问新的节点。而当全部节点访问完后，就不需要再访问新节点，也就不需要返回。所以我们需要找到树上的一条最长路径，只走他一次，就能使距离最短。

树上最长路径也就是树的直径，访问节点的过程中，我们需要走到一个节点，再返回到他的祖先，也就是每条边会被走两次。而直径有一次不需要走，所以答案就是树上所有边权之和乘 $2$ 减去树的直径长度。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n,num,tmp,sum;
int dep[N];
vector<pair<int,int> >v[N];
void dfs1(int k,int fa)
{
  for(auto now:v[k])
  {
    if(now.first==fa) continue;
		dep[now.first]=dep[k]+now.second;
    dfs1(now.first,k);
  }
  return;
}
void dfs2(int k,int fa)
{
  for(auto now:v[k])
  {
    if(now.first==fa) continue;
		dep[now.first]=dep[k]+now.second;
    dfs2(now.first,k);
  }
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<n;i++)
  {
    int x,y,z;
    cin>>x>>y>>z;
    v[x].push_back({y,z});
    v[y].push_back({x,z});
		sum+=z;
  }
  dfs1(1,0);
  for(int i=1;i<=n;i++) if(dep[i]>dep[num]) num=i;
	tmp=num;
	dep[num]=0;
  dfs1(num,0);
  for(int i=1;i<=n;i++) if(dep[i]>dep[num]) num=i;
  cout<<sum*2-dep[num];
  return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到如果最后要回到原点的话，每条边至少要经过 $2$ 次，出去一次，回来一次。

现在不需要回到原点，且要使得距离最小，我们可以找到树上最长的一条链，即树的直径，然后减去其长度即可。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,s,t;
ll dis[N];
vector<pair<ll,ll>> E[N];
void add(ll u,ll v,ll w){
	E[u].push_back({v,w});
	E[v].push_back({u,w});
}
void dfs(ll u,ll fa){
	for(auto t:E[u]){
		ll v=t.first,w=t.second;
		if(v==fa)
		  continue;
		dis[v]=dis[u]+w;
		dfs(v,u);
	}
}
pair<ll,ll> solve(ll u,ll fa){
	ll sum=0,Max=0;
	for(auto t:E[u]){
		ll v=t.first,w=t.second;
		if(v==fa)
		  continue;
		auto h=solve(v,u);
		sum+=h.first+2*w;
		Max=max(Max,w+h.second);
	}
	return {sum,Max};
}
int main(){
	n=read();
	for(int u,v,w,i=1;i<n;i++){
		u=read(),v=read(),w=read();
		add(u,v,w);
	}
	dfs(1,1);
	for(int i=1;i<=n;i++)
	  if(dis[i]>dis[s])
	    s=i;
	dis[s]=0;
	dfs(s,s);
	for(int i=1;i<=n;i++)
	  if(dis[i]>dis[t])
	    t=i;
	auto h=solve(s,s);
	write(h.first-h.second);
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

由于路只有 $N-1$ 条，可以看作一棵树。

先考虑完成旅行后需要回起点的情况，设一条边从 $u$ 到 $v$，则从 $u\to v$、$v\to u$ 都至少会经过 $2$ 次（一次用来旅行，一次回去）。

但是，旅行后不需要回起点。我发现，从最后一个被访问的点到起点的路径只会经过 $1$ 次。因此，为了使答案最小，经过 $1$ 次的路径要最长。

路径最长……就是树的直径！直径上的边只经过一次，就可以使答案最小。

答案为 $2\times\sum_{i=1}^{n-1}c_i-\operatorname{diam}(T)$，$\operatorname{diam}$ 指直径，$T$ 指树。

---

## 作者：1234567890sjx (赞：0)

### E

根据某一次 NOIP 集训 T1 的思路，容易发现一定是有一条路径上的边只经过了一次，其他的边都经过了两次。为了让经过的边的边权和最小，只需要让这一条路径为树的直径即可。时间复杂度为 $O(n\log n)$，这是因为要求两点之间距离需要倍增 LCA 求（其实又是降智行为）。

```cpp
bool begmem;
#include <bits/stdc++.h>
#define int long long
using namespace std;
class FastIO {
public:
    int read() {
        int o = 1, x; char ch;
        while (!isdigit(ch = getchar())) {
            if (ch == '-') {
                o = -1;
            }
        }
        x = ch ^ 48;
        while (isdigit(ch = getchar())) {
            x = (x << 3) + (x << 1) + (ch ^ 48);
        }
        return o * x;
    }
} ; FastIO io;

void calcqwq();
const int N = 500100, inf = 1e18;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }
int f[N][20], id, vis[N], dis[N], n, sum;
vector<pair<int, int>> z[N];
void bfs(int st) {
    memset(dis, 0x3f, sizeof dis);
    queue<int> q; q.push(st); vis[st] = 1, dis[st] = 0;
    while (q.size()) {
        int f = q.front(); q.pop(); vis[f] = 0;
        for (auto &[g, w] : z[f]) if (dis[g] > dis[f] + w) {
            dis[g] = dis[f] + w;
            if (!vis[g]) {
                vis[g] = 1;
                q.push(g);
            }
        }
    }
    id = -233;
    for (int i = 1; i <= n; ++i)
        if (id == -233 || dis[i] > dis[id]) id = i;
}
int dep[N], yhb[N];
void dfs(int u, int fa) {
    f[u][0] = fa, yhb[u] = yhb[fa] + 1;
    for (auto &[v, _] : z[u]) if (v != fa) dep[v] = dep[u] + _, dfs(v, u);
}
int lca(int u, int v) {
    if (yhb[u] < yhb[v]) swap(u, v);
    int delta = yhb[u] - yhb[v];
    for (int i = 0; i < 20; ++i) if (delta >> i & 1) u = f[u][i];
    // cout << "qvq " << u << '\n';
    if (u == v) return u; for (int i = 19; ~i; --i)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int qwq(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}
signed main() {
    atexit(calcqwq);
    n = io.read(), sum = 0;
    for (int i = 1; i < n; ++i) {
        int u = io.read(), v = io.read(), w = io.read();
        z[u].emplace_back(v, w);
        z[v].emplace_back(u, w);
        sum += w;
    }
    bfs(1);
    int st = id;
    bfs(st);
    int st2 = id;
    dfs(1, 0);
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j <= n; ++j)
            f[j][i] = f[f[j][i - 1]][i - 1];
    // cout << st << ' ' << st2 << ' ' << lca(st, st2) << ' ' << qwq(st, st2) << '\n';
    cout << sum * 2 - qwq(st, st2) << '\n';
}
bool endmem;
void calcqwq() {
    fprintf(stderr, "Memory = %.5lf\n", (&begmem - &endmem) / 1048576.);
}
```

---

## 作者：DrAlfred (赞：0)

摘要：树的直径，树状 dp，贪心

[传送门：https://www.luogu.com.cn/problem/AT_abc361_e](https://www.luogu.com.cn/problem/AT_abc361_e)

## 题意

给定一颗 $n$ 个节点的带边权的树。求从某个点出发，遍历所有点的最小花费（注意不需要回到开始起点，只需要遍历完所有点即可）。

## 分析思路

如果我们从某个点出发，到达所有点并且返回到起点，很明显对于最优的情况，所有的边都恰好经过了两次，即答案为 $2 \sum C_i$。

然而，这题要求我们不需要返回起始点。这个条件等价于让我们选择某个起点 $u$ 和终点 $v$，将原先 $2 \sum C_i$ 的答案减去 $\mathrm{dis}(u, v)$。显然取 $\mathrm{dis}(u, v)$ 等于树的直径答案最小。

于是，我们使用树 dp 求出树的直径，将二倍边权和减去直径即为答案。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
using i64 = long long;
struct Edge {
    i64 to, w;
};
vector<Edge> G[N];
i64 n, u, v, w, mx, ans, dp[N][2];
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
inline void dfs(int x, int fa) {
    for (auto edge : G[x]) {
        if (edge.to == fa) continue;
        dfs(edge.to, x), v = dp[edge.to][0] + edge.w;
        if (v > dp[x][0]) {
            dp[x][1] = dp[x][0], dp[x][0] = v;
        } else if (v > dp[x][1]) {
            dp[x][1] = v;
        }
    }
    mx = max(mx, dp[x][0] + dp[x][1]);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w, ans += 2 * w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    // find diameter of tree.
    dfs(1, 0), cout << ans - mx << endl;
    return 0;
}

```

---

## 作者：zhlzt (赞：0)

### 题解
原题 POJ 1849，题目略有不同，但代码一模一样，本质相同。

给定一棵带边权无根树，你可以从任意一点出发遍历这棵树，求最小代价。

先假定任意一点为根，那么正常情况下有搜索加回溯，即每条边经过两次，但是显然遍历完最后一点后不必再回溯，即这条回溯的路径中每边只在搜索时经过一次。

考虑到回溯的路径可以是树的直径，那么令树的直径的一端为根，从此开始遍历，且可以满足遍历到的最后一点是树的直径的另一端，即树的直径上每边只需在搜索时经过一次。

答案即为树的边权之和的两倍减去树的直径的长度。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
long long dp[maxn],dpans[maxn];
vector<pair<int,long long> >edge[maxn];
void dfs(int u,int fath){
	vector<long long>sta;
	for(int i=0;i<edge[u].size();i++){
		pair<int,int> cur=edge[u][i];
		int v=cur.first;
		long long w=cur.second;
		if(v==fath) continue; dfs(v,u);
		sta.push_back(w+dp[v]);
	}
	int cnt=sta.size();
	sort(sta.begin(),sta.end());
	if(cnt>0) dp[u]=dpans[u]=sta[cnt-1]; 
	if(cnt>1){
		dpans[u]=sta[cnt-2]+sta[cnt-1];
	}
}
int main(){
	int n;scanf("%d",&n);
	long long sum=0;
	for(int i=1;i<n;i++){
		int u,v;long long w;scanf("%d%d%lld",&u,&v,&w);
		edge[u].push_back(make_pair(v,w));
		edge[v].push_back(make_pair(u,w));
		sum+=w<<1;
	}
	dfs(1,0); long long ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dpans[i]);
	printf("%lld\n",sum-ans); return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc361_e)

## 思路

贪心。

不难发现这个图是个树，而树的直径联通所有点。由于要想到达每个点，大部分边都至少被走两次。所以我们想到把最远的两个点作为起点和终点，使连接这两个点的边只被走一次。用**所有边权和的二倍减去树的直径**，所得值即为路径长度和最小值。

先从 $1$ 号根节点找最远的点 $A$，再从这个点找最远的点 $B$，$A$ 与 $B$ 的距离即为树的直径。用两个 ``dfs`` 记录路径长度，同时更新距离最远的点即可。**记得 ``dfs`` 函数内先后顺序和树链剖分不同。**

- 记得开 ``long long``。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pli pair<ll,int>
#define fi first
#define se second
using namespace std;
ll read(){//快读。
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=2e5+10;
int n,A,B,fa[N];
ll dis[N],sum;
vector<pli>g[N];
void dfs(int x,int f){
	for(auto i:g[x]){
		if(i.se==f)continue;//不能回去。
		dis[i.se]=i.fi+dis[x];
		if(dis[i.se]>dis[A])A=i.se;//有比当前更远的，更新。
		dfs(i.se,x);
	}
	return ;
}
void dfs2(int x,int f){
	for(auto i:g[x]){
		if(i.se==f)continue;
		dis[i.se]=i.fi+dis[x];
		if(dis[i.se]>dis[B])B=i.se;
		dfs2(i.se,x);
	}
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		ll w=read();
		g[u].pb({w,v});
		g[v].pb({w,u});
		sum+=w;
	}
	dfs(1,0);//第一遍搜索找 A。
	memset(dis,0,sizeof dis);
	dfs2(A,0);//第二遍搜索找 B。
	cout<<sum*2ll-dis[B];。
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc361/submissions/55285676)

---

## 作者：Heldivis (赞：0)

考虑如果要求树上从一个点经过每一个点，再回到这个点的路径长度，则为答案两倍边权，即按照 DFS 序走一遍。可以证明没有比这样更短的走法。

现在不要求回到原点，相当于减去从终点到起点的路径长度。为了让答案最小，要让这条路径长度最大，树上最大的一条路径是直径。所以答案为两倍边权减去直径。

对于求直径，可以看 [[SDOI2013] 直径](https://www.luogu.com.cn/problem/P3304) 这道题的第一问，概括来说是先以任一点为根，找出最深的点，再以这个点为根，找出最深的点，此时这两个点的距离就是根的长度。

为了验证，考虑如何构造合法方案。可以发现，从直径的一段走向另一端，在路径上只要遇到不在直径上的边，就走出去，进行 DFS，按照 DFS 序走，之后在回来。这样走了一条合法方案。

---

## 作者：FFTotoro (赞：0)

第一次 $3$ 分钟内做掉 E。

先假定根结点为 $1$，即从结点 $1$ 开始遍历整棵树。如果最后要回到根结点，考虑深搜的过程，显然每条边要经过恰好 $2$ 次（根向叶子下行 / 叶子向根上行）；因为最后不需要回到根结点，所以可以留下一条根结点到叶子的路径不返回，即答案可以减去 $1$ 到某个结点的路径长度，为了让答案最小，只需要找出最长的那条路径即可。

如果根结点不为 $1$，显然考虑选择一个根结点和一个叶子结点作为那条路径。显然此时只需选取树的直径即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,c=0; cin>>n;
  vector<vector<pii> > g(n);
  for(int i=1;i<n;i++){
    int u,v,w; cin>>u>>v>>w,c+=w<<1;
    g[--u].emplace_back(--v,w);
    g[v].emplace_back(u,w);
  }
  vector<int> d(n);
  function<void(int,int)> dfs=[&](int u,int f){
    for(auto [i,w]:g[u])
      if(i!=f)d[i]=d[u]+w,dfs(i,u);
  }; // 两遍 dfs 求直径
  dfs(0,0);
  int rt=max_element(d.begin(),d.end())-d.begin();
  fill(d.begin(),d.end(),0);
  dfs(rt,rt);
  cout<<c-*max_element(d.begin(),d.end())<<endl;
  return 0;
}
```

---

## 作者：Starrykiller (赞：0)

简单题。

首先考虑对于定根的情况怎么做。最后停留在深度最深的节点一定最优，那么找到深度最深的节点的深度即可。

但是这题不定根，那么怎么选取根呢？选取树的直径的端点即可。

顺便讲一下树的直径的 dp 求法。考虑设 $d(u)$ 为以 $u$ 为一端的最长链的长度。遍历完 $u$ 的儿子 $v$（设 $\mathrm{val}(u,v)=w$）后，先用 $d(u)+d(v)+w$ 来更新直径长度，再 $d(u)\gets \max(d(u),d(v)+w)$ 即可，正确性显然。

[代码](https://atcoder.jp/contests/abc361/submissions/55276977)。

---

## 作者：云裳 (赞：0)

**思路**

联通的图有 $n$ 个点，$n-1$ 条边，就构成了一棵树。设树的直径为 $k$，那答案就是 $2\sum C_i-k$。

感性理解一下。首先从任意一个点出发，在回到这个点所经过的路程至少为 $2\sum C_i$，因为每一条边你过去要经过一次，回来也要经过一次。而按照 DFS 的顺序就刚好可以达到这个下界。然后这样子是多走了 $dis(s,v)$，其中 $s$ 是起点，$v$ 是 DFS 序的中点，$dis(s,v)$ 为这两个点的距离。那既然 $s$ 和 $v$ 是任意两点，为了使答案最小，就要是 $dis(s,v)$ 最大，最大也就是直径 $k$。

因此答案是 $2\sum C_i-k$。

直径可以用两次 DFS 求出，具体看 [PT07Z](https://www.luogu.com.cn/problem/SP1437)。

**代码**

```cpp
#include<bits/stdc++.h>
#define up(i,l,r) for(int i=l,END##i=r;i<=END##i;i++)
#define dn(i,l,r) for(int i=l,END##i=r;i>=END##i;i--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int INF=0x3f3f3f3f,N=2e5+7;
struct e {
	ll to,nxt,w;
} a[N<<1];
ll head[N],tot;
void add(ll x,ll y,ll z) {
	a[++tot].to=y,a[tot].w=z,a[tot].nxt=head[x],head[x]=tot;
}
ll ans,dis[N],nn,n;
namespace sol {
	ll read() {
		ll f=0,x=0;
		char c=getchar();
		while(c<'0'||c>'9') f|=c=='-',c=getchar();
		while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
		return f?-x:x;
	}
	void write(ll x) {
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	void dfs(ll now,ll fa) {//求直径
		for(int i=head[now]; i; i=a[i].nxt) {
			ll to=a[i].to;
			if(to!=fa) {
				dis[to]=dis[now]+a[i].w;
				if(dis[nn]<dis[to]) nn=to;
				dfs(to,now);
			}
		}
	}
	void solve() {
		n=read();
		up(i,2,n) {
			ll x=read(),y=read(),z=read();
			add(x,y,z),add(y,x,z);
			ans+=z;
		}
		dfs(1,0);
		memset(dis,0,sizeof dis);
		dfs(nn,0);
		write(2*ans-dis[nn]);
	}
}
using namespace sol;
signed main() {
	solve();
	return 0;
}

```

---

## 作者：Redamancy_Lydic (赞：0)

## 背景

好板啊，机房大佬直接三分钟过掉。

## 题意

给你一棵树，问从任意一个节点出发，经过所有节点至少一次的最短经过长度。

## 分析

稍微分析以后可以发现想要达成目标，那么树上只有一条路径需要走一次，其余一定要经过两次。那么按照贪心的思想，这条路径一定需要是树的直径。

考虑具体实现，先跑出来树的直径长度，然后统计所有边权和的二倍，再减去直径长度就是最终答案。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
using namespace std;
using namespace  __gnu_pbds;
//gp_hash_table<string,int>mp2;
//__gnu_pbds::priority_queue<int,less<int>,pairing_heap_tag> q;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n;
struct no
{
	int y,v;
};
vector<no> G[maxn];
int d[maxn];
void dfs(int x,int fa)
{
	for(auto i : G[x])
	{
		int y=i.y,v=i.v;
		if(y==fa)continue;
		d[y]=d[x]+v;
		dfs(y,x);
	}
}
int ans;
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read(),v=read();
		G[x].push_back({y,v});
		G[y].push_back({x,v});
		ans+=v*2;
	}
	dfs(1,0);int st=1;
	for(int i=2;i<=n;i++)
	{
		if(d[i]>d[st])st=i;
	}
	int en=1;
//	for(int i=2;i<=n;i++)
//	{
//		if(siz[i]==1&&d[i]>d[en]&&i!=st)en=i;
//	}
//	cout<<ans-G[st][0].v-G[en][0].v;
	memset(d,0,sizeof d);
	dfs(st,0);
	for(int i=2;i<=n;i++)
	{
		if(d[i]>d[en])en=i;
	}
	cout<<ans-d[en];
	return 0;
}
```

---

