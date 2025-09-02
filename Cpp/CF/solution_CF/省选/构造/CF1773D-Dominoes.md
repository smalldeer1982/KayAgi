# Dominoes

## 题目描述

Dora喜欢玩多米诺骨牌。玩法是在一个 $n×m$ 的表格中标记一些格子，然后用 $2×1$ 的多米诺骨牌填满其他空格子。注意，多米诺骨牌不能放在标记过的格子上。

Dora的弟弟Dani喜欢搞恶作剧，趁Dora不在时，他会在表格中又标记两个格子。请告诉他有多少种标记的方案，使多米诺骨牌无法填充到所有空格子里。

但是Dani只能数到 $10^6$。如果方案数超过 $10^6$，请输出 $10^6$。

## 样例 #1

### 输入

```
3 6
...#..
......
#...##```

### 输出

```
52```

## 样例 #2

### 输入

```
2 2
..
..```

### 输出

```
2```

## 样例 #3

### 输入

```
2 2
#.
#.```

### 输出

```
0```

# 题解

## 作者：SkyRainWind (赞：8)

[my blog](https://www.cnblogs.com/SkyRainWind/p/17176667.html)
## Solution

首先将棋盘黑白染色，是一个二分图。

由于题目保证初始状态一定能密铺，因此这个二分图一定有完美匹配。

现在要铺 2 个地方，显然分两种情况：

- 黑白颜色相同。

显然此时并不能产生完美匹配，因此这些情况都是答案，即 $2 \times \binom{cnt}{2}$。

- 颜色不同。

枚举黑色点删哪个，考察哪些白色点删了之后二分图就不存在完美匹配了，即求新图最大匹配的必经点。

[这篇](https://www.cnblogs.com/SkyRainWind/p/17176631.html)写的是必经边，这里换成了必经点，处理有所不同。

首先，如果流量不是白色点$-1$，就说明无论选什么白色点，都无法达到完美匹配，答案加上白色点个数。

否则，考虑从汇点 $T$ 反向走，每次走满流的点，如果当前点是白色点，就标记。最后统计没标记的点就是必经点。

为什么是对的呢？

首先，考虑 $T$ 到某个白色点的反向边，反向边由于容量为 $0$，满流则说明其对应的正向边的流量也为 $0$，也就是这个白色点没有参加匹配。

从这个白色点开始，走反向边到黑色点，意味着这个黑点到这个白点没有匹配，可以作为备选。

然后从黑色点开始走，**满流**走到下一个白色点，意味着这个黑点和下一个白色点匹配上了，这时，我们发现可以将这个黑点和上一个白点匹配，也就是下一个白点不是必选点。这样递归下去我们就得到了所有非必选点，反过来就是必经点了。

代码：

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 3005;

int n,m,a[1005][1005];
struct ed{
	LL from,to,cap,flow,rev;
	ed(){}
	ed(LL from,LL to,LL cap,LL flow,LL rev):from(from),to(to),cap(cap),flow(flow),rev(rev){}
};
vector<ed>g[maxn];

const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
inline int in(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;} 
inline int ind(int x,int y){return (x-1)*m+y;}

struct netflow{
	int cur[maxn]; 
	int d[maxn], q[maxn], hd, tl;
	int s, t;	// 源 汇 
	
	netflow(){s=t=-1;}
	
	void init(int s0,int t0){
		s = s0, t = t0;
	}

	void add(int x,int y,LL v){
		g[x].push_back(ed(x,y,v,0,g[y].size()));
		g[y].push_back(ed(y,x,0,0,g[x].size() - 1));
	}
	
	int bfs(){
		memset(d,0, sizeof d);
		hd = tl = 0;
		q[tl ++] = s;
		d[s] = 1;
		while(hd != tl){
			int now = q[hd ++];
			for(int i = 0;i<g[now].size();i++){
				ed &e = g[now][i];
				if(!d[e.to] && e.cap > e.flow)d[e.to] = d[now] + 1, q[tl ++] = e.to;
			}
		}
		return d[t];
	}
	
	LL dfs(int now,LL rem){	// rem 当前流量 
		if(now == t || !rem)return rem;
		LL flow = 0;
		for(int &i = cur[now]; i < g[now].size();i ++){
			ed &e = g[now][i];
				// 分层图 & 残量不为0 
			if(d[e.to] == d[now] + 1 && e.cap > e.flow){
				LL f = dfs(e.to, min(rem, e.cap - e.flow));
				rem -= f, flow += f, e.flow += f, g[e.to][e.rev].flow -= f;
			}
			if(!rem)break;
		}
		if(rem)d[now] = -1;
		return flow;
	}
	
	LL dinic(){
		assert(s!=-1);
		LL flow = 0;
		while(bfs()){
			memset(cur, 0, sizeof cur);
			flow += dfs(s, 1ll << 62);
		}
		return flow;
	}
}nf;
vector<pii>ed;
vector<int>lft,rgt; 
int vis[maxn];

void dfs(int x){
	vis[x] = 1;
	for(int i=0;i<g[x].size();i++){
		struct ed e = g[x][i];
		if(!vis[e.to] && e.flow == e.cap)dfs(e.to);
	}
}

map<int,int>mp;
int cc;

signed main(){
//	freopen("CF1773D.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		char s[1005];
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			if(s[j] == '#')a[i][j] = 0;
			else a[i][j] = 1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)if(a[i][j] == 1)mp[ind(i, j)] = ++cc;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)if(a[i][j]){
			if((i%2 + j) & 1){
				for(int k=0;k<4;k++){
					int fi = i+dx[k], fj = j+dy[k];
					if(!in(fi, fj) || !a[fi][fj])continue;
					ed.pb(mpr(mp[ind(i, j)], mp[ind(fi, fj)]));
				}
			}
		}
	
	int cnt0=0, cnt1=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)if(a[i][j]){
			if((i%2 + j) & 1)++ cnt0, lft.pb(mp[ind(i, j)]);
			else ++cnt1, rgt.pb(mp[ind(i, j)]);
		}
	
	ll ans = 1ll*cnt0*(cnt0-1)/2 + 1ll*cnt1*(cnt1-1)/2;
	if(ans >= (ll)1e6)return printf("%d\n",(int)1e6), 0;
	
	int s = 2*cnt0+1, t = s+1;
	nf.init(s, t);
	for(int u : lft){
		for(int i : lft)g[i].clear(), vis[i] = 0;
		for(int i : rgt)g[i].clear(), vis[i] = 0;
		g[s].clear(), g[t].clear();
		vis[s] = vis[t] = 0;
		
		for(pii e : ed){
			if(e.first ^ u){
				nf.add(e.first, e.second, 1);
			}
		}
		for(int v : lft)if(u^v)nf.add(s, v, 1);
		for(int v : rgt)nf.add(v, t, 1);
		
		ll res = nf.dinic(), r=0;
		if(res != cnt0-1){
			ans += cnt1;
			continue;
		}
		dfs(t);
		for(int v : rgt)if(!vis[v])++ r;
		ans += r;
	}
	cout << min(ans, (ll)1e6) << '\n';

	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

#### *D. Dominoes

判定多米诺骨牌是否可以密铺整个网格：黑白染色，一个多米诺骨牌代表一条边，可密铺的充要条件为二分图存在完美匹配。

对于一个连通块，若黑白格数量相差超过 $2$ 或为奇数，删去任意两格均无解。否则若相差 $2$，则必须删去两个较多颜色的格子。否则相等，必须删去两个不同颜色的格子。因此，删去两格有解的方案数不超过 $\frac {n ^ 2} 4$。

因为答案只要和 $10 ^ 6$ 取较小值，所以若空地数量 $N > 2000$ 则答案一定为 $10 ^ 6$。

若 $N$ 为奇数，无论怎么删都无解。否则，枚举删去的格子之一，求出二分图匹配，若匹配大小小于 $\frac N 2 - 1$，无论怎么删都无解。否则，若删去后有解，不妨设左部图较大，则另一个格子为匹配的非必经左部点。

求匹配必经点是经典问题：从每个左部非匹配点出发，遍历它的所有右部匹配点邻居对应的左部匹配点，则所有被遍历到的左部匹配点均为非必经点，因为从它们开始存在交错路径使得终点为非匹配点，将匹配边换成路径下一条边即可。

时间复杂度 $\mathcal{O}(N ^ {2.5})$。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int L = 1e3 + 5;
constexpr int N = 2e3 + 5;
constexpr int M = 2e4 + 5;
constexpr int inf = 1000000;
constexpr int dx[4] = {-1, 0, 0, 1};
constexpr int dy[4] = {0, -1, 1, 0};

int n, m, cnt, type[N], label[L][L];
int ban, node, ans;
vector<int> e[N];

struct flow {
  int cnt = 1, hd[N], nxt[M << 1], to[M << 1], limit[M << 1];
  void clear() {
    memset(hd, 0, sizeof(hd));
    cnt = 1;
  }
  void add(int u, int v, int w) {
    nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w;
    nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0;
  }
  int T, cur[N], dis[N];
  int dfs(int id, int res) {
    if(id == T) return res;
    int flow = 0;
    for(int i = cur[id]; i && res; i = nxt[i]) {
      cur[id] = i;
      int c = min(limit[i], res), it = to[i];
      if(dis[id] + 1 == dis[it] && c) {
        int k = dfs(it, c);
        flow += k, res -= k, limit[i] -= k, limit[i ^ 1] += k;
      }
    }
    if(!flow) dis[id] = -1;
    return flow;
  }
  int maxflow(int s, int t) {
    T = t;
    int flow = 0;
    while(1) {
      queue<int> q;
      memset(dis, -1, sizeof(dis));
      memcpy(cur, hd, sizeof(cur));
      q.push(s), dis[s] = 0;
      while(!q.empty()) {
        int t = q.front();
        q.pop();
        for(int i = hd[t]; i; i = nxt[i])
          if(dis[to[i]] == -1 && limit[i])
            dis[to[i]] = dis[t] + 1, q.push(to[i]);
      }
      if(dis[t] == -1) return flow;
      flow += dfs(s, N);
    }
  }
} g;

int mx[N], my[N], vis[N];
void fill(int id) {
  if(vis[id]) return;
  vis[id] = 1;
  for(int it : e[id]) if(my[it]) fill(my[it]);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      char s;
      cin >> s;
      if(s == '.') {
        label[i][j] = ++cnt, type[cnt] = i + j & 1;
        if(cnt > 2000) cout << inf << "\n", exit(0);
      }
    }
  }
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      if(!label[i][j]) continue;
      int id = label[i][j];
      for(int d = 0; d < 4; d++) {
        int x = i + dx[d], y = j + dy[d];
        if(label[x][y]) e[id].push_back(label[x][y]);
      }
    }
  for(int _ = 1; _ <= cnt; _++) {
    g.clear();
    memset(vis, 0, sizeof(vis));
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    int B = 0, W = 0;
    for(int i = 1; i <= cnt; i++) if(i != _) type[i] ? B++ : W++;
    if(abs(B - W) != 1) continue;
    vector<int> L;
    int S = 0, T = cnt + 1;
    for(int i = 1; i <= cnt; i++) {
      if(i == _) continue;
      if(type[i] == (B > W)) {
        g.add(S, i, 1), L.push_back(i);
        for(int it : e[i]) if(it != _) g.add(i, it, 1);
      }
      else g.add(i, T, 1);
    }
    int res = g.maxflow(S, T);
    if(res != (cnt - 1 >> 1)) continue;
    for(int i : L)
      for(int j = g.hd[i]; j; j = g.nxt[j]) {
        int it = g.to[j];
        if(it && !g.limit[j]) mx[i] = it, my[it] = i;
      }
    for(int i : L) if(!mx[i]) fill(i);
    for(int i : L) ans += vis[i];
  }
  ans = cnt * (cnt - 1) / 2 - (ans >> 1);
  cout << min(ans, inf) << "\n";
  return 0;
}
```

对原图跑一遍最大匹配。若最大匹配为 $\frac N 2$，那么求出删去每个点之后大小为 $\frac N 2 - 1$ 的匹配是平凡的。若最大匹配为 $\frac N 2 - 1$，那么求出删去某左部点之后大小为 $\frac N 2 - 1$ 的匹配，若该点为非匹配点则平凡，否则只需从该点找到一条以左部非匹配点结尾的交错路。这样可避免每次重新跑最大匹配。时间复杂度 $\mathcal{O}(N ^ 2)$。

---

## 作者：Cxny (赞：5)

题意：$n\times m$ 的网格，有些位置是障碍。问有多少种将两个空格变成障碍的方式，使得无法使用 $1\times2$ 的骨牌将网格填满。保证初始状态能被填满。输出方案数向 $10^6$ 取 $\min$ 的结果。$n,m\le1000$。

典中典。

经典结论：黑白网格数相同是可以被填充的必要条件。因此，同时填充两个黑格或白格之后一定无解。

此时若方案数仍 $<10^6$，则有空格数 $<2000$。

再考虑经典做法。对相邻的黑格和白格连边，有完美匹配是有解的充要条件。

下面设二分图左部和右部各有 $k$ 个结点。由于初始状态有解，该二分图有完美匹配。

考虑去掉左部的每一个点。此时的最大匹配一定是 $k-1$。若右部的某一个点**必定在最大匹配上**，那么删去这个点后不存在完美匹配。

之后的做法就和二分图博弈差不多了。网络流，从汇点沿 $0$ 边跑 dfs，搜到的点一定在最大匹配上。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define ll long long
const int maxn = 2010;
bool vis[maxn * maxn];
namespace MF {
    const int N = 1010;
    const int lim = 1000000;
    const int NN = 2010;
    const int MM = 10010;
    int n, s, t, head[NN], to[MM << 1], nxt[MM << 1], flow[MM << 1];
    int cur[NN], d[NN], tot = 1, vis[NN];
    void init() {
        memset(head, 0, sizeof(head));
        tot = 1;
    }
    void addedge(int u, int v, int w) {
        to[++tot] = v, flow[tot] = w, nxt[tot] = head[u], head[u] = tot;
    }
    void add(int u, int v, int w) {
        addedge(u, v, w);
        addedge(v, u, 0);
    }
    bool bfs() {
        queue<int> q;
        memset(d, 0, sizeof(d));
        d[s] = 1, q.push(s);
        while (!q.empty()) {
        int u = q.front();
        q.pop(), cur[u] = head[u];
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = flow[i];
            if (w > 0 && !d[v])
            d[v] = d[u] + 1, q.push(v);
        }
        }
        return d[t];
    }
    int dfs(int u, int now) {
        if (u == t || !now) return now;
        int rest = now;
        for (int i = cur[u]; i && rest > 0; i = nxt[i]) {
        cur[u] = i;
        int v = to[i], w = flow[i];
        if (d[v] == d[u] + 1 && w > 0) {
            int cap = dfs(v, min(rest, w));
            if (cap) flow[i] -= cap, flow[i ^ 1] += cap, rest -= cap;
        }
        }
        return now - rest;
    }
    int Dinic() {
        int res = 0, cap;
        while (bfs()) while (cap = dfs(s, 1e9)) res += cap;
        return res;
    }
    void rest_dfs(int u) {
        vis[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = flow[i];
        if (w == 0 && !vis[v]) rest_dfs(v);
        }
    }
    int solve(int l, int r) {
        for(int i = 1; i <= n; i++) vis[i] = 0;
        rest_dfs(t);
        int cnt = 0;
        for(int i = l; i <= r; i++) if (!vis[i]) cnt++;
        return cnt;
    }
}
#define ind(x, y) (((x) - 1) * m + (y))
const int lim = 1e6;
int n, m, cnt[2], ind[maxn][maxn];
char s[maxn][maxn];
ll ans;
vector<pair<int, int>> pos[2];
vector<int> edge[maxn * maxn];
signed main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%s", s[i] + 1);
        for(int j = 1; j <= m; j++) if(s[i][j] == '.') ind[i][j] = ++cnt[(i + j) & 1], pos[(i + j) & 1].eb(i, j);
    }
    ans = 1ll * cnt[0] * (cnt[0] - 1) / 2 + 1ll * cnt[1] * (cnt[1] - 1) / 2;
    if(ans > lim) return printf("%d\n", lim), 0;
    for(auto [x, y] : pos[0]) for(auto [i, j] : pos[1]) if(abs(x - i) + abs(y - j) == 1) edge[ind[x][y]].pb(ind[i][j] + cnt[0]);
    MF::s = 2 * cnt[0] + 1, MF::n = MF::t = 2 * cnt[0] + 2;
    for(auto [x, y] : pos[0]){
        MF::init();
        for(auto [i, j] : pos[0]) if(i != x || y != j){
            MF::add(MF::s, ind[i][j], 1);
            for(int v : edge[ind[i][j]]) MF::add(ind[i][j], v, 1);
        }
        for(auto [i, j] : pos[1]) MF::add(ind[i][j] + cnt[0], MF::t, 1);
        int res = MF::Dinic();
        if(res != cnt[0] - 1) ans += cnt[0];
        else ans += MF::solve(cnt[0] + 1, cnt[0] * 2);
    }
    printf("%lld\n", min(ans, 1ll * lim));
    return 0;
}
```

---

## 作者：Sevendays_Coder (赞：3)

## 前言
题解区好像全都是网络流的做法，本着杀鸡焉用牛刀的思想~~其实就是不会~~，这里提供一个不用网络流的做法，复杂度也是 $O(n^2)$。


---

网格图很容易想到黑白染色后形成二分图，用矩形覆盖即形成了一个匹配，问题就变成了在二分图中删两个点使之没有完美匹配的方案数，完美匹配即匹配数等于点数的一半。

容易发现，选择两个**同色**点是必定合法的，因为左右点数不平衡了。

那么选择两个同色的方案数即为 $2\times{{|S_1|}\choose{2}}$。

注意题面指出：方案数与 $10^6$ 取 $\min$，意味着只要总空格数大于 $2000$ 才需要往后考虑，所以这条限制帮我们将点数限制在了 $O(n)$，一个点最多只接出四条边，边数也限制了 $O(n)$。

于是我们开始考虑选**异色**点。

先求出一组完美匹配，考虑选怎样的两个点会破坏完美匹配。

好像不是很好求，那考虑怎样选不会破坏。

首先若两点已经匹配，那么同时删去不会影响其他点，考虑本来不匹配的点。

若同时删除两点，这两点原来匹配的点还能找到新的匹配点，那么这两个点删除不会破坏平衡。

我们发现这类似于匈牙利算法中的**增广**过程，我们枚举一个左边的点，对它跑 _dfs_，模拟增广的过程，能遍历到的点就可以与它形成合法的点对，然后总点对数减去合法点对数就是我们要求的方案。

```cpp
#include<bits/stdc++.h>

using namespace std;
inline int Read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c))
	{
	    if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
const int N=1000;
const int M=1e6;
char s[N+5][N+5];
int p[N+5][N+5];
int n,m,cnt;
int id(int x,int y)
{
	if(!p[x][y])
		p[x][y]=++cnt;
	return p[x][y];
}
vector<int>c[2];
int u[4]={1,-1,0,0},v[4]={0,0,1,-1};
bool vis[N<<2];
int match[M];
int Head[N<<2],To[M<<1],Nxt[M<<1],Etot;
void Addedge(int x,int y)
{
	To[++Etot]=y;
	Nxt[Etot]=Head[x];
	Head[x]=Etot;
}
int dfs(int x)
{
	for(int i=Head[x];i;i=Nxt[i])
	{
		int y=To[i];
		if(vis[y])
			continue;
		vis[y]=true;
		if(!match[y]||dfs(match[y]))
		{
			match[y]=x;
			match[x]=y;
			return true;
		}
	}
	return false;
}
int an[N<<2];
void dfss(int x,int Top)
{
	for(int i=Head[x];i;i=Nxt[i])
	{
		int y=To[i];
		if(vis[y])
			continue;
		vis[y]=true;
		an[Top]++;
		dfss(match[y],Top);
	}	
}
int main()
{
	n=Read(),m=Read();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='.')
			{
				c[(i+j)&1].push_back(id(i,j));
				if(c[0].size()*(c[0].size()-1)>=M)
				{
					cout<<M<<endl;
					return 0;
				}
				for(int k=0;k<4;k++)
				{
					int x=i+u[k],y=j+v[k];
					if(x&&y&&x<=n&&y<=m&&s[x][y]=='.')
						Addedge(id(x,y),id(i,j));
				}
			}
	int cnt=0,ans=c[0].size()*(c[0].size()-1);
	for(int i=0;i<c[0].size();i++)
	{
		memset(vis,0,sizeof(vis));
		cnt+=dfs(c[0][i]);
	}
	for(int i=0;i<c[0].size();i++)
	{
		memset(vis,0,sizeof(vis));
		dfss(c[0][i],c[0][i]);
		ans+=cnt-an[c[0][i]].size();
	}
	printf("%d\n",min(ans,M));
 	return 0;
}

```


---

## 作者：enucai (赞：1)

## Description

你有一个 $n\times m$ 的矩形网格图，你要用一些 $1\times 2$ 的多米诺骨牌去填充这些网格，现在规定一些网格位置被 ban 掉了（不能填多米诺骨牌），问有多少对未被填充的点 $((x_1,y_1),(x_2,y_2))$，使得 ban 掉这两个点后能填满所有未被 ban 掉的点。输出答案对 $10^6$ 取 $\min$ 的结果。题目保证初始形态一定有解。

## Analysis

我们将矩形网格黑白染色，显然如果 ban 掉两个位置后剩下网格的黑点与白点个数不同，显然无解。

由于初始黑白点数相同，我们只要 ban 掉两个黑点或两个白点，那么一定无解。所以先算出未被 ban 的黑白点的数量，如果单种颜色点数 $>10^3$，那么答案一定 $\ge 10^6$，直接输出 $10^6$ 即可。

否则套路地，我们考虑建立二分图，将相邻的黑白点之间连边。我们枚举 ban 掉的白点是哪个，然后跑二分图最大匹配，若最大流量不是总空白点数 $\div 2$，必然无解，否则删除黑点中的最大匹配必经点就无解。我们只要算出黑点中的必经点即可，算法见 [link](https://www.cnblogs.com/Vexoben/p/11761040.html)。

最后统计答案是平凡的，最坏情况下复杂度 $k\sqrt k$，其中 $k=2000$。

具体细节见代码。

## Code

```cpp
const int N = 1010;
const int lim = 1000000;
const int NN = 2010;
const int MM = 10010;

struct MF {
  int n, s, t, head[NN], to[MM << 1], nxt[MM << 1], flow[MM << 1];
  int cur[NN], d[NN], tot = 1, vis[NN];
  void init() {
    memset(head, 0, sizeof(head));
    tot = 1;
  }
  void addedge(int u, int v, int w) {
    to[++tot] = v, flow[tot] = w, nxt[tot] = head[u], head[u] = tot;
  }
  void add(int u, int v, int w) {
    addedge(u, v, w);
    addedge(v, u, 0);
  }
  bool bfs() {
    queue<int> q;
    memset(d, 0, sizeof(d));
    d[s] = 1, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), cur[u] = head[u];
      for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = flow[i];
        if (w > 0 && !d[v])
          d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t];
  }
  int dfs(int u, int now) {
    if (u == t || !now) return now;
    int rest = now;
    for (int i = cur[u]; i && rest > 0; i = nxt[i]) {
      cur[u] = i;
      int v = to[i], w = flow[i];
      if (d[v] == d[u] + 1 && w > 0) {
        int cap = dfs(v, min(rest, w));
        if (cap) flow[i] -= cap, flow[i ^ 1] += cap, rest -= cap;
      }
    }
    return now - rest;
  }
  int mf() {
    int res = 0, cap;
    while (bfs()) while (cap = dfs(s, 1e9)) res += cap;
    return res;
  }
  void rest_dfs(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i], w = flow[i];
      if (w == 0 && !vis[v]) rest_dfs(v);
    }
  }
  int solve(int l, int r) {
    rep (i, 1, n) vis[i] = 0;
    rest_dfs(t);
    int cnt = 0;
    rep (i, l, r) if (!vis[i]) cnt++;
    return cnt;
  }
}g;

int n, m;
char s[N][N];
vector<pii> pos[2];
vector<int> eg[N];

int main() {
  n = read(), m = read();
  rep (i, 1, n) scanf("%s", s[i] + 1);
  int cnt[2]; memset(cnt, 0, sizeof(cnt));
  rep (i, 1, n) rep (j, 1, m) {
    if (s[i][j] == '.') cnt[(i + j) & 1]++;
  }
  assert(cnt[0] == cnt[1]);
  if (1ll * cnt[0] * (cnt[0] - 1) >= lim) return write(lim), 0;
  ll ans = 1ll * cnt[0] * (cnt[0] - 1);
  rep (i, 1, n) rep (j, 1, m) {
    if (s[i][j] == '.') pos[(i + j) & 1].emplace_back(i, j);
  }
  rep (i, 0, cnt[0] - 1) rep (j, 0, cnt[1] - 1){
    if(abs(pos[0][i].fi - pos[1][j].fi) + abs(pos[0][i].se - pos[1][j].se) == 1) {
      eg[i + 1].emplace_back(j + 1);
    }
  }
  g.n = 2 * cnt[0] + 2;
  rep (id, 1, cnt[0]){
    g.init(), g.s = 2 * cnt[0] + 1, g.t = g.s + 1;
    int S = g.s, T = g.t;
    rep (i, 1, cnt[0]) if (i != id) {
      g.add(S, i, 1);
      for (int j:eg[i]) g.add(i, cnt[0] + j, 1);
    }
    rep (i, 1, cnt[0]) g.add(cnt[0] + i, T, 1);
    if (g.mf() != cnt[0] - 1) ans += cnt[0];
    else ans += g.solve(cnt[0] + 1, 2 * cnt[0]);
  }
  write(min(ans, 1ll * lim));
}
```

---

## 作者：huangrenheluogu (赞：0)

发现一个比较特殊的条件：答案和 $10^6$ 取 $\min$。

仔细想一下发现是诈骗题，哪里有 $n\times m$ 个点，明明只有 $2000$ 个。

原因在于黑白染色之后删去同一种颜色的方案是 $C_n^2$（现在写作 $\dbinom{n}{2}$，表示 $n$ 个数里选 $2$ 个数的方案总数）。

而 $C_n^2\le10^6$ 可以发现 $n\le2000$。

所以其实只有 $2000$ 个数。

假设有 $cnt$ 组点，$cnt\le1000$（注意折半）。

我们可以先算删除同色点的个数，方案数是 $C_n^2$。

然后不同颜色的点，因为 $cnt\le1000$，所以暴力删点，跑一个 Tarjan，判断另一种颜色的点是不是必须的即可，用网络流解决。

复杂度 $\mathcal{O}(cnt^2\sqrt{cnt})$。

介绍一个我的 trick，按 $col$ 排序可以将不同颜色的点分开。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005, NN = 2005, inf = 1e9;
int n, m, cnt, col[N][N], Map[N][N], nx, ny, ans, has[N][N];
bool vis[NN];
int fir[NN], nxt[N * N], son[N * N], tot, dfn[NN], low[NN], to[NN], s[NN], t, edge[N * N], S, T, now[NN], d[NN], x, tem, idx, q[NN], h, cntnum, aaa[NN];
char ch;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
struct node{
	int x, y, col;
}a[N * N];
inline void dfs(int x, int y){
	for(int k = 0; k < 4; k++){
		nx = x + dx[k];
		ny = y + dy[k];
		if(nx < 1 || ny < 1 || nx > n || ny > m) continue ;
		if(~col[nx][ny]) continue ;
		col[nx][ny] = col[x][y] ^ 1;
		dfs(nx, ny);
	}
}
inline bool cmp(node x, node y){
	return x.col < y.col;
}
inline void mem(){
	for(int i = S; i <= T; i++) fir[i] = 0, dfn[i] = 0;
	for(int i = 2; i <= tot; i++) nxt[i] = 0;
	tot = 1;
	cntnum = idx = 0;
}
inline void add(int x, int y, int flow){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
	edge[tot] = flow;
	if(y == S || y == T) aaa[x] = tot;
}
inline void Add(int x, int y, int flow = 1){
	add(x, y, flow);
	add(y, x, 0);
}
inline bool bfs(){
	for(int i = S; i <= T; i++) now[i] = fir[i], d[i] = 0;
	d[S] = 1, q[t = 1] = S, h = 0;
	while(h < t){
		h++;
		x = q[h];
		for(int i = fir[x]; i ; i = nxt[i]){
			if(!d[son[i]] && edge[i]){
				d[son[i]] = d[x] + 1;
				q[++t] = son[i];
				if(son[i] == T) return 1;
			}
		}
	}
	return 0;
}
inline int dinic(int x = S, int flow = inf){
	if(x == T) return flow;
	int res = flow;
	for(int i = now[x]; i && res; i = nxt[i]){
		now[x] = i;
		if(edge[i] && d[son[i]] == d[x] + 1){
			tem = dinic(son[i], min(edge[i], res));
			edge[i] -= tem;
			edge[i ^ 1] += tem;
			res -= tem;
		}
	}
	return flow - res;
}
inline void tarjan(int x){
	vis[x] = 1;
	q[++t] = x;
	dfn[x] = low[x] = ++idx;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(!edge[i]) continue ;
		if(!dfn[son[i]]){
			tarjan(son[i]);
			low[x] = min(low[x], low[son[i]]);
		}
		else if(vis[son[i]]) low[x] = min(low[x], dfn[son[i]]);
	}
	if(low[x] == dfn[x]){
		cntnum++;
		while(vis[x]){
			to[q[t]] = cntnum;
			vis[q[t--]] = 0;
		}
	}
}
int main(){
	memset(col, -1, sizeof(col));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ch = getchar();
			while(ch != '.' && ch != '#') ch = getchar();
			Map[i][j] = (ch == '.') ? 0 : 1;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(Map[i][j]) continue ;
			if(!(~col[i][j])) col[i][j] = 0, dfs(i, j);
			cnt++;
			a[cnt] = (node){i, j, col[i][j]};
			has[i][j] = cnt;
		}
	}
	if(cnt > 2000){
		printf("1000000\n");
		return 0;
	}
	if(cnt == 2){
		printf("0\n");
		return 0;
	}
	sort(a + 1, a + cnt + 1, cmp);
	cnt >>= 1;
	ans += cnt * (cnt - 1);
	S = 0, T = cnt * 2 + 1;
	for(int i = 1; i <= cnt << 1; i++) has[a[i].x][a[i].y] = i;
	for(int del = 1; del <= cnt; del++){
		mem();
		for(int i = 1; i <= cnt; i++){
			if(i == del) continue ;
			for(int j = 0; j < 4; j++){
				nx = a[i].x + dx[j];
				ny = a[i].y + dy[j];
				if(!has[nx][ny]) continue ;
				Add(i, has[nx][ny]);
			}
		}
		for(int i = 1; i <= cnt; i++){
			Add(S, i);
			Add(cnt + i, T);
		}
		while(bfs()){
			if(dinic()) ;
			else break;
		}
		t = 0;
		for(int i = S; i <= T; i++){
			if(!dfn[i]) tarjan(i);
		}
		for(int i = cnt + 1; i <= cnt + cnt; i++){
			if(to[i] != to[T] && edge[aaa[i]] == 0) ans++/*, printf("%d %d\n", del, i)*/;
		}
//		printf("%lld\n", ans);
	}
	ans = min(ans, 1000000);
	printf("%d\n", ans);
	return 0;
}
/*
2 3
.#.
.#.
*/
```

---

## 作者：happybob (赞：0)

首先我们知道可以密铺的充要条件是黑白染色之后建二分图，四联通的点连边，图有完美匹配。然而 $nm \leq 10^6$，在 $10^6$ 个点的二分图上做匹配有关的事情肯定会超时。

注意到题目要求答案对 $10^6$ 取 $\min$。这可能意味着二分图的真正点数不会很多，否则答案就超过了 $10^6$。

具体来说，考虑黑白染色后，每个连通块的黑白个数分别为 $x,y$。能密铺的必要条件是 $x=y$。若 $x$ 与 $y$ 的差为奇数或大于 $2$，那么任意删掉连通块两个点都不可能密铺，贡献为 $\dbinom{x+y}{2}$。考虑 $x = y+2$ 或者 $y=x+2$，此时可以把更少的颜色删掉两个，贡献至少为形如 $\dbinom{x}{2}$ 或者 $\dbinom{y}{2}$。$x=y$ 时，删掉两个任意一种颜色都是合法的，贡献至少是 $\dbinom{x}{2} + \dbinom{y}{2}$。

设总共空地数为 $N$，我们发现 $N >2000$ 时答案必然大于等于 $10^6$。于是二分图点数 $\leq 2000$。

考虑枚举删掉的其中一个点，然后就等价于求删掉这个点的二分图的最大匹配，以及最大匹配必经点。这里使用网络流或者 HK 算法都可以做到 $O(N^{2.5})$，大概已经可以过了。但是其实有 $O(N^2)$ 的做法。

先考虑怎么删掉一个点之后求最大匹配。直接求出原二分图最大匹配，然后考虑删掉一个点之后，在之前的匹配中重新找一次增广路即可。

对于求必经点，我们不妨假设我们要求左侧必经点。事实上非必经点就是所有左侧非匹配点开始的交错路在左侧的终点集合。这些点都可以通过在交错路上对匹配异或从而不属于最大匹配。

这样我们得到了 $O(N^2)$ 的复杂度做法，注意一些特判和细节。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

const int M = 1005, N = 4005;

using ll = long long;

int n, m;
char c[M][M];
int id[M][M], idx;
int lft;
vector<int> G[N];
ll ans = 0ll;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

int match[N], pre[N];
bool vis[N];

bool bfs()
{
	for (int i = 1; i <= idx; i++) pre[i] = vis[i] = 0;
	queue<int> q;
	for (int i = 1; i <= lft; i++) if (!match[i]) q.push(i);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& j : G[u])
		{
			if (vis[j]) continue;
			vis[j] = 1;
			pre[j] = u;
			if (!match[j])
			{
				int k = j;
				while (true)
				{
					int x = pre[k], g = match[x];
					match[x] = k, match[k] = x;
					if (!g) return 1;
					k = g;
				}
			}
			else if (!vis[match[j]]) q.push(match[j]);
		}
	}
	return 0;
}

void bfsrt(int uu)
{
	int rm = match[uu];
	match[uu] = match[rm] = 0;
	for (int i = 1; i <= idx; i++) pre[i] = vis[i] = 0;
	queue<int> q;
	for (int i = lft + 1; i <= idx; i++) if (!match[i] && i != uu) q.push(i);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& j : G[u])
		{
			if (vis[j] || j == uu) continue;
			vis[j] = 1;
			pre[j] = u;
			if (!vis[match[j]] && match[j] != uu) q.push(match[j]);
		}
	}
	match[uu] = rm, match[rm] = uu;
}

void bfslft(int uu)
{
	int rm = match[uu];
	match[uu] = match[rm] = 0;
	for (int i = 1; i <= idx; i++) pre[i] = vis[i] = 0;
	queue<int> q;
	for (int i = 1; i <= lft; i++) if (!match[i] && i != uu) q.push(i);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& j : G[u])
		{
			if (vis[j] || j == uu) continue;
			vis[j] = 1;
			pre[j] = u;
			if (!vis[match[j]] && match[j] != uu) q.push(match[j]);
		}
	}
	match[uu] = rm, match[rm] = uu;
}

bool tag[N];

void get_tag_right(int u)
{
	for (int i = 1; i <= idx; i++) tag[i] = 0;
	bfsrt(u);
	for (int i = lft + 1; i <= idx; i++)
	{
		if (vis[i]) tag[i] = 1;
	}
}

void get_tag_left(int u)
{
	for (int i = 1; i <= idx; i++) tag[i] = 0;
	bfslft(u);
	for (int i = 1; i <= lft; i++)
	{
		if (vis[i]) tag[i] = 1;
	}
}

bool bfsn(int uu)
{
	int rm = match[uu];
	match[uu] = match[rm] = 0;
	for (int i = 1; i <= idx; i++) pre[i] = vis[i] = 0;
	queue<int> q;
	for (int i = 1; i <= lft; i++) if (!match[i] && uu != i) q.push(i);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& j : G[u])
		{
			if (vis[j] || j == uu) continue;
			vis[j] = 1;
			pre[j] = u;
			if (!match[j])
			{
				match[u] = rm, match[rm] = uu;
				return 1;
			}
			else if (!vis[match[j]] && match[j] != uu) q.push(match[j]);
		}
	}
	return 0;
}

int mm;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> c[i][j];
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i + j) & 1)
			{
				if (c[i][j] == '.') id[i][j] = ++idx, c1++;
			}
		}
	}
	lft = idx;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i + j) % 2 == 0)
			{
				if (c[i][j] == '.') id[i][j] = ++idx, c2++;
			}
		}
	}
	if (idx > 2000)
	{
		cout << "1000000\n";
		return 0;
	}
	if (idx & 1)
	{
		cout << min((ll)1e6, 1ll * idx * (idx - 1) / 2ll) << "\n";
		return 0;
	}
	// build up edge
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i + j) & 1)
			{
				if (c[i][j] != '.') continue;
				int x = id[i][j];
				for (int k = 0; k < 4; k++)
				{
					int ni = i + dx[k], nj = j + dy[k];
					if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && c[ni][nj] == '.')
					{
						G[x].emplace_back(id[ni][nj]);
						G[id[ni][nj]].emplace_back(x);
					}
				}
			}
		}
	}
	while (bfs()) mm++;
	// 选一黑一白
	if (c1 != c2)
	{
		ans += 1ll * c1 * c2;
	}
	else
	{
		for (int i = 1; i <= lft; i++)
		{
			int rm = mm;
			if (rm < lft - 1)
			{
				ans += c2;
			}
			else
			{
				if (rm == lft - 1 && match[i] && !bfsn(i))
				{
					ans += c2;
				}
				else
				{
					get_tag_right(i);
					for (int j = lft + 1; j <= idx; j++) ans += !tag[j];
				}
			}
		}
	}
	// 选两个黑
	if (c1 != c2 + 2)
	{
		ans += 1ll * c1 * (c1 - 1) / 2ll;
	}
	else
	{
		for (int i = 1; i <= lft; i++)
		{
			int rm = mm;
			if (rm < c2)
			{
				ans += c1 - 1;
			}
			else
			{
				if (match[i] && !bfsn(i))
				{
					ans += c1 - 1;
				}
				else
				{
					get_tag_left(i);
					for (int j = 1; j <= lft; j++) ans += !tag[j];
				}
			}
		}
	}
	// 选两个白
	if (c2 != c1 + 2)
	{
		ans += 1ll * c2 * (c2 - 1ll) / 2;
	}
	else
	{
		for (int i = lft + 1; i <= idx; i++)
		{
			int rm = mm;
			if (mm < c1)
			{
				ans += c2 - 1;
			}
			else
			{
				if (match[i] && !bfsn(i)) ans += c2 - 1;
				else
				{
					get_tag_right(i);
					for (int j = lft + 1; j <= idx; j++) ans += !tag[j];
				}
			}
		}
	}
	cout << min(ans, (ll)1e6) << "\n";
	return 0;
}
```

---

