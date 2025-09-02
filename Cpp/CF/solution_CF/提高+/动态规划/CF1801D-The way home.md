# The way home

## 题目描述

The famous magician Borya Budini traveled through the country $ X $ , which consists of $ n $ cities. However, an accident happened, and he was robbed in the city number $ 1 $ . Now Budini will have a hard way home to the city number $ n $ .He's going to get there by plane. In total, there are $ m $ flights in the country, $ i $ -th flies from city $ a_i $ to city $ b_i $ and costs $ s_i $ coins. Note that the $ i $ -th flight is one-way, so it can't be used to get from city $ b_i $ to city $ a_i $ . To use it, Borya must be in the city $ a_i $ and have at least $ s_i $ coins (which he will spend on the flight).

After the robbery, he has only $ p $ coins left, but he does not despair! Being in the city $ i $ , he can organize performances every day, each performance will bring him $ w_i $ coins.

Help the magician find out if he will be able to get home, and what is the minimum number of performances he will have to organize.

## 说明/提示

In the first example, it is optimal for Borya to make $ 4 $ performances in the first city, having as a result $ 2 + 7 \cdot 4 = 30 $ coins, and then walk along the route $ 1-3-2-4 $ , spending $ 6+8+11=25 $ coins. In the second example, it is optimal for Borya to make $ 15 $ performances in the first city, fly to $ 3 $ city, make $ 9 $ performances there, and then go to $ 4 $ city.

## 样例 #1

### 输入

```
4
4 4 2
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11
4 4 10
1 2 10 1
1 2 20
2 4 30
1 3 25
3 4 89
4 4 7
5 1 6 2
1 2 5
2 3 10
3 4 50
3 4 70
4 1 2
1 1 1 1
1 3 2```

### 输出

```
4
24
10
-1```

# 题解

## 作者：Otue (赞：11)

膜拜 gyh20 开场爆切此题。


## 思路
我们可以确定一个最佳行走方案。

从 $1$ 号点开始，选择一个目标点 $x$，通过最短路路径到达 $x$。如果发现钱不够则在 $1$ 号点反复赚钱，直到够为止。同理，继续从 $x$ 开始，选择一个目标点 $y$，通过最短路径到达 $y$，如果钱不够则在 $x$ 号点反复赚钱。如此反复，直到到达 $n$。

当然，我们的目标点肯定优先考虑赚钱更多的点。故 $w_i$ 从小到大排序。

---

现在考虑一个问题，$u$ 到 $v$ 的路径，到达 $v$ 点后有许多种结局，用二元组 $(f,g)$ 表示。$f$ 代表到达 $v$ 点后演出次数，$g$ 代表到达 $v$ 点后所剩的钱。到底哪种方案更优？演出次数最小的更优？赚的钱越多更优？

考虑 ($f_1,g_1)$ 和 $(f_2,g_2)$ 两种结局，若 $f_1<f_2$ 且 $g_1<g_2$，此时我们怎么判断谁更优？

事实上，$(f_1,g_1)$ 只需要到达 $v$ 后再多演出一次，所剩余的钱就比 $g_2$ 多。

因为，从 $u$ 到 $v$ 的路径，到达 $v$ 点后所有方案所剩的钱不会超过 $w_u$，因为一旦超过，你可以少演出一次。且前面讨论过，一定满足 $w_u<w_v$。

可知 $g_2-g_1<w_u,w_u<w_v$，即 $g_1+w_v>g_2$ 。$(f_1,g_1)$ 的情况多演出一次则变为 $(f_1+1,g_1+w_v)$。肯定优秀于 $(f_2,g_2)$。

综上：演出次数越少，方案越优。如果演出次数相等，则剩的钱越多越优。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN_N = 805, MAXN_M = 3005;

int T, n, m, p, w[MAXN_N], dist[MAXN_N][MAXN_N], f[MAXN_N], g[MAXN_N];
// f,g 数组表示到达该点后演出次数和所剩钱

struct edge {
	int x, id;
}a[MAXN_N];
bool cmp(edge x, edge y) { return x.x < y.x; }

void floyd() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		}
	} 
}

void change(int x, int nf, int ng) { // 按照演出次数越少越优的优先级更新 dp 数组
	if (nf < f[x]) f[x] = nf, g[x] = ng;
	else if (nf == f[x] && ng > g[x]) f[x] = nf, g[x] = ng;
}

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> m >> p;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) dist[i][j] = 0;
				else dist[i][j] = 1e18;
			}
		}
		for (int i = 1; i <= n; i++) cin >> w[i], a[i].x = w[i], a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			dist[a][b] = min(dist[a][b], c);
		}
		floyd();
		for (int i = 1; i <= n; i++) f[i] = 1e18, g[i] = 0;
		f[1] = 0, g[1] = p;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int x = a[i].id, y = a[j].id;
				if (dist[x][y] != 1e18 && i != j) {
					int tmpf = f[x], tmpg = g[x];
					if (tmpg >= dist[x][y]) change(y, tmpf, tmpg - dist[x][y]); // 如果你现在钱都够了，不需要赚，走就行
					else {
						int dlt = dist[x][y] - tmpg;
						int sum = (dlt + w[x] - 1) / w[x];
						tmpf += sum; tmpg += sum * w[x];
						change(y, tmpf, tmpg - dist[x][y]);
					}
				}
			} 
		}
		if (f[n] <= 3e12) cout << f[n] << endl;
		else puts("-1"); 
	}
}
```

---

## 作者：AkeRi (赞：11)

orz gyh20 orz

# Description

略。

# Solution

考虑贪心地更新每个点。

对于每一个点排序（防止转移出环），
处理出每个点的最短路，对于每一个点 $i$ 的状态，可以看做一个二元组 $(f_i,g_i)$，其中 $f_i$ 表示到达点 $i$ 的的最小表演次数，$g_i$ 表示到这个点的最大剩余钱数。

考虑转移，对于点 $u$ 到点 $v$，若 $f_v$ 更优，则直接更新 $(f_v,g_v)$，若 $f_v$ 不优 $g_v$ 更优，则只更新 $g_v$ 即可。

证明：我们已经预处理最短路，对于新到的点，必然有 $g_v\lt g_u$。对于到达一个点的两种方案 $(f_{p1},g_{p1})$、$(f_{p2},g_{p2})$ 如果在某一时刻到达某点，其 $f_p$ 更优，则可在这个点提前加上其部分贡献，使得 $g_{p1}\ge g_{p2}$，此时更新其 $f_p\leftarrow f_{p1}$，$g_p\leftarrow g_{p1}$ 即可。否则比较 $g$ 的大小进行转移。

初始化：$f_1=0,g_1=w$，其中 $w$ 是初始拥有的钱数。

复杂度 $\Theta(n^3+n^2+n\log n)$
# Code
```cpp
/*

by L1rs1ngzN1sLyr

*/
#include<bits/stdc++.h>
#define int long long
const int AI=1e3+9;
const int KI=1e6+2;
const int CI=1e7+3;
int read(){int x=0,w=1;char ch=0;while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}return x*w;}
int f[KI],g[KI];//f：time,g:cost;
int dis[AI][AI],a[KI],p[KI];
bool mys(int x,int b){return a[x]<a[b];}
int T=read(); 

signed main()
{
	while(T--)
	{
		int n=read(),m=read(),c=read();
		
		memset(dis,0x3f,sizeof dis);
		for(int i=1;i<=n;i++) a[i]=read(),p[i]=i;
		for(int i=1;i<=n;i++) dis[i][i]=0,f[i]=0x3f3f3f3f3f3f3f3f,g[i]=0;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			dis[u][v]=std::min(dis[u][v],w);
		} 
		std::sort(p+1,p+n+1,mys);
		for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
		g[1]=c,f[1]=0;
		
		for(int i=1;i<=n;i++) 
		{
			int x=p[i];
			for(int j=1;j<=n;j++) if(dis[p[i]][p[j]]<=CI*CI && i!=j)
			{
				int sf=f[x],sg=g[x];
				if(sg>=dis[p[i]][p[j]])
				{
					if(sf<f[p[j]]) f[p[j]]=sf,g[p[j]]=sg-dis[p[i]][p[j]];
					else if(sf==f[p[j]] && sg-dis[p[i]][p[j]]>g[p[j]]) g[p[j]]=sg-dis[p[i]][p[j]];			
				}
				else
				{
					int delta=dis[p[i]][p[j]]-sg;
					delta=(delta+a[x]-1)/a[x];
					sg+=delta*a[x],sf+=delta;
					if(sf<f[p[j]]) f[p[j]]=sf,g[p[j]]=sg-dis[p[i]][p[j]];
					else if(sf==f[p[j]] && sg-dis[p[i]][p[j]]>g[p[j]]) g[p[j]]=sg-dis[p[i]][p[j]];			
				}
			}
		}
		std::cout<<(f[n]<=1e15?f[n]:-1)<<'\n';
	}
}

```

---

## 作者：_HMZ_ (赞：8)

[在博客食用更佳](https://www.luogu.com.cn/blog/DUCKPEAR/solution-cf1801d)

场上切了，但是 1B 寄掉了/oh

## 大致题意：

波奇酱初始在 $1$ 号节点，手里有 $p$ 块钱。

她想去 $n$ 号点，而每通过一条边就必须交 $s_i$ 块钱，如果钱不够则无法通过。

当然，钱有可能不够，所以，波奇酱可以在第 $i$ 个点进行演出，而每演出一次可以获得 $w_i$ 块钱，在一个城市可以演出无限次。

但，波奇酱很社恐，所以，她想知道 $1$ 走到 $n$ 最少需要演出多少次？

## 大致思路：

~~我对题意进行了一点点的魔改~~

先惰性的演出，也就是说，当钱不够时再演出。

而贪心一下，如果要演出必然在演出路上经过的能得到最多钱的点演出。

于是我们就能列出一个 dp 方程，具体而言，$dp_{i,j,k}$ 代表现在在第 $i$ 个节点，路上经过的 $w_i$ 最大的点是 $j$，手里有 $k$ 块钱，最少需要买多少次。

当然，这个东西复杂度肯定崩了，我们发现 $k$ 这个东西太大了，考虑优化。

因为演出是惰性的，所以我们可以把 $k$ 作为第二关键字塞进 dp 里头。

那这样为什么是对的呢？

感性理解一下，如果演出次数少了一次，那么我们再在 $j$ 这个位置上买一次，演出次数就相等，而手里的钱必然会更多。

然后直接用最短路优化 dp 就行。

## 代码：

```cpp
//This code is written by hmz,and hmz is cute!!!
//这里忽略了部分缺省源
TY T,n,m,p,val[MAXN];pair<TY,TY> dp[MAXN][MAXN];bool vis[MAXN][MAXN];
vector<pair<TY,TY> > e[MAXN];
struct road{
	TY now,K,fir,sec;
	bool operator<(const road&A) const{
		if(fir!=A.fir)return fir>A.fir;
		else return sec<A.sec;
	}
};priority_queue<road> q;
inline void minroad(){
	For(i,1,n)For(j,1,n)dp[i][j]={1e18,0},vis[i][j]=0;
	dp[1][1]={0,p};
	TY ans=1e18;q.push({1,1,0,p});
	while(!q.empty()){
		TY now=q.top().now,k=q.top().K,a=q.top().fir,b=q.top().sec;
		if(now==n)ans=min(ans,a);
		q.pop();
		if(vis[now][k])continue;vis[now][k]=1;
		FOR(i,0,e[now].size()){
			TY y=e[now][i].first,ta=a,tb=b,nxt=(val[y]>val[k]?y:k);
			tb-=e[now][i].second;
			if(tb<0)ta+=Ceil(abs(tb),val[k]),tb%=val[k],tb=(tb==0?0:tb+val[k]);
			if(ta<dp[y][nxt].first||(ta==dp[y][nxt].first&&tb>dp[y][nxt].second)){
				dp[y][nxt]={ta,tb};
				q.push({y,nxt,ta,tb});
			}
		}
	}qw(ans==1e18?-1:ans,'\n');
}
int main(){
	T=qr();while(T--){
		n=qr();m=qr();p=qr();
		For(i,1,n)e[i].clear();
		For(i,1,n)val[i]=qr();
		For(i,1,m){
			TY u=qr(),v=qr(),w=qr();
			e[u].push_back({v,w});
		}minroad();
	}
	return 0;
}


```


---

## 作者：Zimo_666 (赞：7)

## [CF1801D] The way home

### Description

一个人在一张有向图的 $1$ 号结点，他要去到 $n$ 结点。每条边 $(a_i,b_i)$ 有边权 $s_i$，表示走过这条边需要花 $s_i$ 元。这个人一开始有 $p$ 元，到了一个点 $u$，他可以进行若干次演出，每次演出收获 $w_u$ 元。问到达 $n$ 的最小演出次数，若无解输出 ```-1```。

### Solution

首先我们先考虑该题这个人的表演策略，即如果回家的路径确定了，那么我们直接考虑表演的策略。显然有他在某一个点 $x$ 表演够恰好回到 $n$ 结点数，而后直接走最小花费的路径回到 $n$ 结点。接着我们考虑他是如何来到 $x$ 的，必然有在另一点 $x'$ 表演够恰好来到 $x$。所以我们如果如果已经确定走的路径，那么他的表演策略是确定的。

于是我们考虑先对 $n$ 个点求出最短路，再用类似贪心的方式求出下次表演的地点。我们考虑在这部分求算中，有两个变量影响，一个是 $cost_i$ 即到达 $i$ 点需要表演的次数，和 $res_i$ 即此时剩余的钱数。显然我们在表演次数取到最小时，使得剩余钱数最多，所以我们考虑使用优先队列维护这样形如堆优化迪杰斯特拉的算法。每次我们取出当前点 $u$ 时，我们枚举下一个停靠点 $i$。则我们可以计算出演唱次数 $times$。而后我们比较两种方法优劣性并更新答案，所有答案即为 $cost_n$。

考虑用类似堆优化迪杰斯特拉实现。注意取整需要考虑被除数为负数的情况，建议手写。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int n,m,p;
const int N=800+7;
vector<pair<int,int>> G[N];
bool vis[N],_vis[N];
int cost[N],res[N];
int dis[N],b[N];

struct node{
	int dis,id;
	friend bool operator < (node a,node b){
		return a.dis>b.dis;
	}
};

struct node2{
	int x,cost,res;
	friend bool operator < (node2 a,node2 b){
		if(a.cost!=b.cost) return a.cost>b.cost;
		return a.res<b.res; 
	}
};

void Dj(int s){
	memset(_vis,0,sizeof _vis);
	priority_queue<node> q;
	memset(dis,80,sizeof dis);
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(_vis[u]) continue;
		_vis[u]=1;
		for(auto i:G[u]){
			int k=i.first,w=i.second;
			if(dis[k]>dis[u]+w){
				dis[k]=dis[u]+w;
				q.push({dis[k],k});
			}
		}
	} 
}

//int _ceil(int x,int y){
//	if(x<0)return 0;
//	if(x%y==0)return x/y;
//	return x/y+1;
//}

int _ceil(int x,int y){if(x<0) return 0;return (x+y-1)/y;}
 
void Get_ans(){
	memset(vis,0,sizeof vis);
	priority_queue<node2> q;
	cost[1]=0,res[1]=p;
	q.push((node2){1,cost[1],res[1]});
	while(!q.empty()){
		int u=q.top().x;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		Dj(u);
		for(int i=1;i<=n;i++){
			if(!vis[i]){
//				int times=(int)ceil((dis[i]-res[u])*1.0/b[u]);
					int times=_ceil(dis[i]-res[u],b[u]);
//				printf("times:%lld\n",times);
				node2 tmp={i,cost[u]+times,res[u]+times*b[u]-dis[i]};
				node2 bf={i,cost[i],res[i]};
				if(bf<tmp){
					q.push(tmp);
					cost[i]=tmp.cost;
					res[i]=tmp.res;
				}
			}
		}
	}
}

void solve(){
	scanf("%lld%lld%lld",&n,&m,&p);
	for(int i=1;i<=n;i++){
		G[i].clear();
		scanf("%lld",&b[i]);
		vis[i]=0;cost[i]=0x3f3f3f3f3f3f3f3f;res[i]=0;
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		G[u].push_back(make_pair(v,w));
	}
	Dj(1);
//	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
	if(dis[n]==dis[0]) return printf("-1\n"),void();
	Get_ans();
	printf("%lld\n",cost[n]);
}

signed main(){
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：LiveZoom (赞：4)

## Description

[link](https://www.luogu.com.cn/problem/CF1801D)

## Solution

首先这个演出是不好一次演出完然后搞，更为好做的是延迟表演，即记录当前经过的最大演出收获是 $w_j$，然后需要钱的时候再演出。

所以可以设 $f_{i,j,k}$ 表示从 $1$ 走到 $i$，经过的点中最大演出收获是 $w_j$，还剩 $k$ 块钱的最小操作次数。这个用最短路做即可。

但是这样做一看就会 T 飞，考虑优化。

因为每次演出是演出到刚好把钱赚够，所以如果次数大于等于 $1$ 的话，当前的钱数 $k$ 一定小于 $w_j$。

考虑把 $k$ 加到 dp 状态里，即 $f_{i,j}=\{\text{表演次数},\text{剩的钱数}\}$。

如果状态 $s_1$ 的表演次数大于状态 $s_2$ 的表演次数，由于 $s_1$ 剩的钱数一定小于 $w_j$，所以让 $s_2$ 表演到 $s_1$ 的表演次数时，$s_2$ 的钱数一定会优于 $s_1$。那么 $s_1$ 就可以删掉了。

另外一种情况是两种状态的表演次数相同，就比剩下的钱数。

所以跑一个关于 pair 的最短路即可。

时间复杂度：$O\big((n^2+nm)\log n\big)$。

~~话说别的题解好像都没讲为什么搞成 pair 是可以做的。~~

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;
using pii = pair<int, int>;

const int kMaxN = 805, kInf = 1e18;

bool cmp(const pii &p1, const pii &p2) {
  if (p1.first != p2.first) return p1.first < p2.first;
  return p1.second > p2.second;
}

struct Node {
  int id, now;
  pii fk;

  Node() {}
  Node(int _id, int _now, pii _fk) : id(_id), now(_now), fk(_fk) {}

  friend bool operator <(const Node &n1, const Node &n2) {
    return cmp(n2.fk, n1.fk);
  }
};

int n, m, p;
int w[kMaxN];
pii f[kMaxN][kMaxN];
bool vis[kMaxN][kMaxN];
vector<pii> G[kMaxN];

void dijkstra() {
  priority_queue<Node> q;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      f[i][j] = {kInf, -kInf};
      vis[i][j] = 0;
    }
  f[1][1] = {0, p};
  q.emplace(1, 1, make_pair(0, p));
  while (!q.empty()) {
    auto [u, now, p] = q.top();
    auto [x, y] = p;
    q.pop();
    if (vis[u][now]) continue;
    vis[u][now] = 1;
    for (auto [v, ww] : G[u]) {
      int nnow = (w[v] > w[now] ? v : now), nx = x, ny = y - ww;
      if (ny < 0) nx += (-ny + w[now] - 1) / w[now], ny += (-ny + w[now] - 1) / w[now] * w[now];
      if (cmp(make_pair(nx, ny), f[v][nnow])) {
        f[v][nnow] = make_pair(nx, ny);
        q.emplace(v, nnow, f[v][nnow]);
      }
    }
  }
  int ans = kInf;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, f[n][i].first);
  cout << (ans == kInf ? -1 : ans) << '\n';
}

void dickdreamer() {
  cin >> n >> m >> p;
  for (int i = 1; i <= n; ++i) {
    G[i].clear();
    cin >> w[i];
  }
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    // G[v].emplace_back(u, w);
  }
  dijkstra();
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) dickdreamer();
  // cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's';
  return 0;
}
```



---

## 作者：IMIDAZOLE (赞：4)

# [CF1801D The way home](https://www.luogu.com.cn/problem/CF1801D)
## **Solution:**

与最短路结合的 DP。

令 $dp_{i,j}$ 表示当前走到第 $i$ 号节点，在 $i$ 之前经过的节点中 $w$ 最大的节点编号为 $j$，此时的最小表演数和最大剩余钱数。

转移方式：优先考虑表演数小的，当表演数相同时，再考虑剩余钱数大的。

结合 dijkstra 算法进行求解即可。

证明：

假设 $dp_{i,j}$ 从两个不同的节点转移过来：

令第一个节点的最小表演数为 $a_1$，最大剩余钱数为 $b_1$；

令第二个节点的最小表演数为 $a_2$，最大剩余钱数为 $b_2$；

其中 $a_1 < a_2$ 且 $b_1 < b_2$，此时从第一个节点转移一定比第二个优。

首先，这两个点既然都可以转移到 $dp_{i,j}$，说明这两个点代表的不同路径曾经相交于 $j$ 节点，二者的差异仅和 $j$ 节点之后的路径有关。

因为路径上 $w_j$ 为最大且我们补表演是补到能做飞机就停，因此 $b_2 < w_j$ 是一定的。

所以如果我们为第一个节点补上 $a_2-a_1$ 次表演，那么剩余钱数一定大于第二个节点，因此更优。

时间复杂度：$O((n+m)\log m)$。

## **Code:**

```cpp
#include<bits/stdc++.h>
#define IL inline
#define int long long
#define pr pair <int,int>
#define ft first
#define sd second
#define pb push_back
#define mpr make_pair
using namespace std;
const int N = 8e2 + 10,inf = 1e18 + 10;
bool _u;
struct node {
	int ans,rst,a,b;
	node() {}
	node(int _x,int _y,int _z,int _w) : ans(_x),rst(_y),a(_z),b(_w) {}
	bool operator < (const node &x) const {
		return ans == x.ans ? rst < x.rst : ans > x.ans;
	}
}dp[N][N]; // dp[i][j] 表示当前走到第 i号节点，在 i 之前经过的节点中 w 最大的节点编号为 j，此时的最小表演数和最大剩余钱数	
priority_queue <node> Q;
vector <pr> e[N];
int T,n,m,p,ans,w[N];
bool _v;
IL int read() {
	int x = 0,f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
signed main() {
	clock_t st = clock();
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	cerr << abs(&_u - &_v) / 1048576.0 << " MB" << endl;
	T = read();
	while(T --) {
		memset(dp,0x3f,sizeof(dp));
		n = read(),m = read(),p = read(),ans = inf;
		for(int i = 1;i <= n;i ++)	w[i] = read(),e[i].clear();
		for(int i = 1,u,v,s;i <= m;i ++)	u = read(),v = read(),s = read(),e[u].pb(mpr(v,s));
		dp[1][0] = node(0,p,1,0),Q.push(dp[1][0]);
		while(!Q.empty()) {
			node p = Q.top();Q.pop();
			int val = p.ans,my = p.rst,i = p.a,j = p.b;
			if(val > dp[i][j].ans || my < dp[i][j].rst)	continue;
			if(w[i] > w[j])	j = i;
			for(auto v : e[i]) {
				int to = v.ft,ct = v.sd,tm = max(1ll * 0,(int)ceil(1.0 * (ct - my) / w[j])),rt = tm * w[j] + my - ct;
				if(dp[to][j].ans > val + tm || (dp[to][j].ans == val + tm && dp[to][j].rst < rt)) {
					dp[to][j] = node(val + tm,rt,to,j);
					Q.push(dp[to][j]);
				}
			}
		}
		for(int i = 1;i <= n;i ++)	ans = min(ans,dp[n][i].ans);
		printf("%lld\n",ans == inf ? -1 : ans);
	}
//	cerr << (clock() - st) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}
```

---

## 作者：Feyn (赞：3)

[My Blog](https://www.cnblogs.com/feyn)

考虑一种比较好考虑的情况，即在初始点表演可以获得非常多的金钱，以至于在这里表演可以比在任何其它点表演赚钱效率都高，那么我们的策略一定是先确定一条从起点到终点的最短路，然后计算差的钱数，在起点表演这么多次之后一口气到达终点。

推广开来，贪心地我们肯定会选择在效率最高的一个点进行表演，并且刚好表演到可以到终点的地步。但事实上我们很有可能会选择多个点进行表演，这是因为我们初始的钱数不支持我们到达效率最高的点。但是这里有一个结论是说，假设存在两个表演点 $a,b$，并且我们会先到达 $a$，那么我们在 $a$ 表演的次数一定是使我们能够到达 $b$ 的前提下的最少次数，理由很简单，我们在 $b$ 也表演一定意味着在后者表演效率更高，既然如此我们肯定会尽量在第二个点进行表演。

还有一个显而易见的结论是最优路径不会存在环，毕竟环上一定是会消耗金钱的。于是跑一个单源最短路即可，只是更新出边的时候是枚举所有下一个点，边权就是上面说的最少表演次数，正常更新即可。有些细节但不多。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=810;
const int inf=1e18;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,n;
struct node{int a,b,wh;};
inline bool cmp(node s1,node s2){
	if(s1.a^s2.a)return s1.a<s2.a;
	else return s1.b>s2.b;
}
inline bool operator <(node s1,node s2){
	return cmp(s2,s1);
}

int dis[N][N],fir,C[N];
node f[N];
bool vis[N];
priority_queue<node>q;

void solve(){
	read(m);read(n);read(fir);int s1,s2,s3;
	for(int i=1;i<=m;i++)read(C[i]);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			dis[i][j]=inf;
		}
	}
	for(int i=1;i<=n;i++){
		read(s1);read(s2);read(s3);
		dis[s1][s2]=min(dis[s1][s2],s3);
	}
	for(int t=1;t<=m;t++){
		for(int x=1;x<=m;x++){
			for(int y=1;y<=m;y++){
				if(dis[x][t]+dis[t][y]>=dis[x][y])continue;
				dis[x][y]=dis[x][t]+dis[t][y];
			}
		}
	}
	for(int i=1;i<=m;i++){
		f[i]=(node){inf,inf};
		vis[i]=false;
	}
	
	f[1]=(node){0,fir,1};
	q.push((node){0,fir,1});
	while(!q.empty()){
		node now=q.top();q.pop();
		if(vis[now.wh])continue;vis[now.wh]=true;
		int wh=now.wh,a=now.a,b=now.b;
		for(int th=1;th<=m;th++){
			if(vis[th])continue;
			if(dis[wh][th]==inf)continue;
			node nxt=(node){a,b,th};
			if(dis[wh][th]<=b){
				nxt.b-=dis[wh][th];
			}
			else{
				int need=(dis[wh][th]-b)/C[wh];
				if(need*C[wh]+b<dis[wh][th])++need;
				nxt.a+=need;nxt.b=need*C[wh]+b-dis[wh][th];
			}
			if(cmp(nxt,f[th])==false)continue;
			f[th]=nxt;q.push(nxt);
		}
	}
	if(f[m].a>(1e17))return puts("-1"),void();
	printf("%lld\n",f[m].a);
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	int test=1;
	read(test);
	while(test--){
		solve();
	}
	
	return 0;
}
```

---

## 作者：zac2010 (赞：2)

小清新短代码图论题，看着像是不可做题，但实际上只要用到性质分析、一点点贪心以及迪杰斯特拉算法的加维应用。

我们首先有结论：对于一条路径，假设扩展边的时候费用不够，肯定是从这条路径上 $w_i$ 最大的城市进行演出。

由于是能不演出就不演出，故而我们认为路径上 $w_i$ 最大值相等的两种方案演出次数少者胜，其次再按剩余钱数来比较。

注意我们是有条件的：路径上 $w_i$ 最大值相等的两种方案进行比较。故而我们不妨在原本基础的迪杰斯特拉最短路算法上多加一个维度：路径上 $w_i$ 最大值。这样就方便求解方便转移了。

时间复杂度 $O(n^2 \log m + nm \log m)$ 级别。

[代码](https://codeforces.com/contest/1802/submission/197000917)

---

## 作者：eastcloud (赞：0)

首先，由于题目中既有花费又有最小表演次数的要求，对于每一个可行的方案起所带来的权都是一个二元组，这让我们不太好贪心地进行最短路，于是我们先考虑一些关于这二者的性质，看看能不能简化状态或者找到一种排序方式。

考虑最优解可能的行进路线，我们发现在这条路径上，除了起始点和终止点，有表演过其他点都按照了表演收益升序排序，这是因为如果我们在一个点表演过但是其收益不如前面的点，那么我们选择在前面表演一定更优。

这个性质让我们可以预处理出最短路，将点按照表演收益进行排序转移，每个点要么直接到达终点，要么赚够刚好到达一个表演收益比它高的点的费用并前往。

虽然最短路的雏形已经出来了，但我们还没有确定二元组的排序方式，不过其实由于在上述过程中我们按照表演收益的升序进行转移，其保证了 $p_v<w_u<w_v$，$p_v$ 表示从 $u$ 到 $v$ 剩余的钱数，$w_v$ 表示 $v$ 的表演收益，那么表演次数较少的二元组一定更优，剩余钱数其次，不然我们可以在当前节点多表演二者之差次，这带来的收益显然更优，于是我们就解决了此题，时间复杂度 $O(n^2+mn\log m)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
#include<cmath>
#define N 805
#define M 3005
#define inf 0x3f3f3f3f3f3f3f3f
#define ll long long
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='-' && ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x/10)write(x/10);
	putchar(x%10+'0');
}
ll e,nex[M<<1],head[N],to[M<<1],edg[M<<1];
ll dis[N][N],vis[N],id[N],val[N],P[N],W[N];
void add(ll u,ll v,ll w){
	to[++e]=v;nex[e]=head[u];head[u]=e;edg[e]=w;
}
struct Node{
	ll val,v;
	Node(ll val,ll v):val(val),v(v){}
};
bool operator <(Node x,Node y){
	return x.val>y.val;
}
priority_queue<Node> q;
ll n;
void dij(ll S){
	memset(dis[S],0x3f,sizeof(dis[S]));dis[S][S]=0;
	while(q.size())q.pop();
	for(ll i=1;i<=n;i++)vis[i]=0;
	q.push(Node(0,S));
	while(!q.empty()){
		ll u=q.top().v;q.pop();
		if(vis[u])continue;
		vis[u]++;
		for(ll i=head[u];i;i=nex[i]){
			ll v=to[i],w=edg[i];
			if(dis[S][v]>dis[S][u]+w){
				dis[S][v]=dis[S][u]+w;
				q.push(Node(dis[S][v],v));
			}
		}
	}
}
bool cmp(ll x,ll y){
	return val[x]<val[y];
}
void solve(){
	n=read();ll m=read(),p=read(),flag=0;
	for(ll i=1;i<=n;i++)val[i]=read();
	for(ll i=1;i<=m;i++){
		ll u=read(),v=read(),w=read();
		add(v,u,w);
	}
	for(ll i=1;i<=n;i++)dij(i);
	if(dis[n][1]>=inf)flag=1;
	for(ll i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,cmp);P[1]=p;id[n+1]=n;
	for(ll i=2;i<=n;i++)W[i]=inf;
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n+1;j++){
			ll x=id[i],y=id[j];
			if(dis[y][x]>=inf)continue;
			ll exti=max(ceil((dis[y][x]-P[x])*1.0/val[x]),0.0);
			ll cos=exti+W[x],res=exti*val[x]+P[x]-dis[y][x];
			if(cos<W[y] || (cos==W[y] && res>P[y])){
				W[y]=cos;P[y]=res;
			}
		}
	}
	if(!flag)write(W[n]);
	else putchar('-'),putchar('1');
	putchar('\n');
	for(ll i=1;i<=e;i++)edg[i]=nex[i]=to[i]=0;
	for(ll i=1;i<=n;i++)P[i]=W[i]=head[i]=0;
}
int main(){
	ll T=read();while(T--)solve();
}
```


---

