# Evacuation

## 题目描述

研究站被分成 $n\times n$ 个格子，每个格子是反应堆或实验室，其中一个受感染的反应堆还有 $t$ 分钟爆炸，每一个受感染的格子会在下一分钟感染所有相邻的实验室。每个实验室都有一定数量的科学家和一定数量的救援舱，每个救援舱可以救一名科学家。科学家可以在一分钟内移动到相邻的未感染的实验室。

## 样例 #1

### 输入

```
3 3
1YZ
1YY
100

0YZ
0YY
003
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 4
Y110
1Y1Z
1Y0Y
0100

Y001
0Y0Z
0Y0Y
0005
```

### 输出

```
3```

# 题解

## 作者：Chenyichen0420 (赞：0)

## 思路分析

一眼网络流，建模也很简单。

首先向每一个有科学家的地方连一个流量为人数的边，有逃生舱的地方连一个流量为仓数的边。

然后考虑二者之间的连通性。我们处理出泄露堆到每一个位置的距离，然后从每一个有人的实验室出发，如果到一个点时所用的时间比爆炸时间大或者比泄漏到这里的时间大就不继续走了。

否则我们先检查这里有没有逃生舱，有就建边。如果此时正好也泄漏到这里就不继续了。否则继续向周围扩展。

显然用广搜会更快一些。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
int n, m; char c[12][12], g[12][12]; bool vis[12][12];
int rad[12][12], dax, day, s, t;
struct node {
	int x, y, d;
	node(int xi = 0, int yi = 0, int di = 0) :x(xi), y(yi), d(di) {};
}tmp; queue<node>q;
inline void getmind() {
	memset(vis, 0, sizeof vis);
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			if (c[i][j] == 'Z')
				vis[i][j] = 1, q.emplace(i, j, 0);
	while (q.size()) {
		tmp = q.front(), q.pop(); rad[tmp.x][tmp.y] = tmp.d;
		for (int i = 0;i != 4;++i)
			if (!vis[tmp.x + dx[i]][tmp.y + dy[i]])
				if (c[tmp.x + dx[i]][tmp.y + dy[i]] != 'Y')
					vis[tmp.x + dx[i]][tmp.y + dy[i]] = 1,
					q.emplace(tmp.x + dx[i], tmp.y + dy[i], tmp.d + 1);
	}
}
struct dinic {
	struct edge { int p, v; }tmp;
	vector<edge>e; vector<int>h[60005];
	inline void ins(int l, int r, int v) {
		h[l].push_back(e.size());
		tmp.p = r; tmp.v = v;
		e.push_back(tmp);
		h[r].push_back(e.size());
		tmp.p = l; tmp.v = 0;
		e.push_back(tmp);
		cerr << l << " to " << r << ' ' << v << endl;
	}
	int d[60005]; bool vis[60005];
	inline bool bfs() {
		memset(vis, 0, sizeof vis);
		vis[s] = d[s] = 1;
		queue<int>q; q.push(s);
		while (q.size()) {
			int tp = q.front();q.pop();
			for (int i = 0;i != h[tp].size();++i) {
				edge& sp = e[h[tp][i]];
				if (!vis[sp.p] && sp.v)
					d[sp.p] = d[tp] + 1,
					vis[sp.p] = 1, q.push(sp.p);
			}
		}
		return vis[t];
	}
	int cur[60005];
	inline int dfs(int p, int a) {
		if (p == t || a == 0)  return a; int ret = 0, f;
		for (int& i = cur[p]; i != h[p].size(); ++i) {
			edge& sp = e[h[p][i]];
			if (d[sp.p] == d[p] + 1 && (f = dfs(sp.p, min(a, sp.v))) > 0) {
				sp.v -= f; e[h[p][i] ^ 1].v += f;
				ret += f; if ((a -= f) == 0) break;
			}
		}
		return ret;
	}
	inline int maxflow() {
		int ret = 0;
		while (bfs())
			memset(cur, 0, sizeof cur),
			ret += dfs(s, 1000);
		return ret;
	}
	inline void reset(int sz) {
		e.clear(); for (int i = 0;i != sz;++i) h[i].clear();
	}
}din;
inline int id(int x, int y) {
	return (x - 1) * n + y;
}
signed main() {
	ios::sync_with_stdio(0);
	memset(rad, 0x3f, sizeof rad);
	cin >> n >> m;
	memset(c, 'Y', sizeof c);
	memset(g, 'Y', sizeof g);
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			cin >> c[i][j];
	s = n * n * 2 + 1; t = s + 1; getmind();
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			cin >> g[i][j];
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			if (c[i][j] >= '1' && c[i][j] <= '9') {
				memset(vis, 0, sizeof vis);
				q.emplace(i, j, 0); vis[i][j] = 1;
				while (q.size()) {
					tmp = q.front(); q.pop();
					if (tmp.d > m || tmp.d > rad[tmp.x][tmp.y]) continue;
					if (g[tmp.x][tmp.y] >= '1' && g[tmp.x][tmp.y] <= '9')
						din.ins(id(i, j), id(tmp.x, tmp.y) + n * n, 1000);
					if (tmp.d == rad[tmp.x][tmp.y]) continue;
					for (int k = 0;k != 4;++k)
						if (!vis[tmp.x + dx[k]][tmp.y + dy[k]])
							if (c[tmp.x + dx[k]][tmp.y + dy[k]] != 'Y')
								q.emplace(tmp.x + dx[k], tmp.y + dy[k], tmp.d + 1),
								vis[tmp.x + dx[k]][tmp.y + dy[k]] = 1;
				}
			}
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			if (c[i][j] >= '1' && c[i][j] <= '9')
				din.ins(s, id(i, j), c[i][j] ^ 48);
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j)
			if (g[i][j] >= '1' && g[i][j] <= '9')
				din.ins(id(i, j) + n * n, t, g[i][j] ^ 48);
	cout << din.maxflow() << endl;
}
```

---

## 作者：tbdsh (赞：0)

## 题意简述
[更好的阅读体验](/article/p0xiex0u)

[洛谷题目传送门](/problem/cf78e)

[CodeForces 题目传送门](//codeforces.com/contest/78/problem/e)

给定 $n\times n$ 个格子，每个格子是反应堆或实验室，实验室里有科学家和救援舱。

现在**有且仅有一个**反应堆被污染，这个反应堆将在 $t$ 秒后爆炸。

同时，一个被污染的格子将在下一分钟污染与其相邻的所有格子。

所有科学家可以每秒都可以抵达相邻的**未被污染的实验室**并进入救援舱。一个救援舱只能容纳一名科学家，且只有进入救援舱的科学家能够存活。我们假设科学家进入救援舱不消耗时间。

问 $t$ 秒后最多有多少个科学家能够存活。

## 分析
首先观察到数据范围很小，考虑使用网络流。

我们考虑把所有有科学家的格子和所有有救援舱的格子视为图上的一个点。

那么不难想到可以先从源点向所有象征着科学家的点连一条流量为科学家人数的边，将所有象征着救援舱的点向汇点连一条流量为救援舱数量的边。

接下来考虑科学家的点和救援舱的点如何连边。

我们注意到 $n\le10$，所以我们可以暴力预处理出每个点在多久后会被污染。然后从每个象征着科学家的点开始爆搜，向能走到的象征着救援舱的点连一条流量为 $+\infty$ 的点。需要注意的是如果在某一时刻一个点已被污染且科学家刚好到达这个有救援舱的点，这个科学家是能够存活的。

然后直接跑网络流即可。

## Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e4 + 5, MAXM = 1e7 + 5;
int n, t, cnt[15][15], opt, Dis[MAXM], dis[MAXN], lst[MAXM], pre[MAXN], ans;
int st, ed;
bool vis[MAXN];
bool Vis[15][15];
int fx[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};
string a[15], b[15];
struct Node{
  int v, id;
};
void dfs1(int x, int y, int tme){
  if (x < 1 || y < 1 || x > n || y > n || a[x][y] == 'Y' || tme > cnt[x][y]){
    return ;
  }
  cnt[x][y] = tme;
  for (int i = 0; i < 4; i++){
    dfs1(x + fx[0][i], y + fx[1][i], tme + 1);
  }
}
vector<Node> g[MAXN];
void add(int u, int v, int w){
  g[u].push_back({v, ++opt});
  lst[opt] = v;
  Dis[opt] = w;
}
void dfs2(int id, int x, int y, int tme){
  if (x < 1 || y < 1 || x > n || y > n || a[x][y] == 'Y' || a[x][y] == 'Z' || Vis[x][y]){
    return ;
  }else if ('1' <= b[x][y] && b[x][y] <= '9' && tme <= cnt[x][y] && tme <= t){
    add(id, x * n + y + n * n, int(1e9));
    add(x * n + y + n * n, id, 0);
  }
  if (tme >= cnt[x][y] || tme >= t){
    return ;
  }
  Vis[x][y] = 1;
  for (int i = 0; i < 4; i++){
    dfs2(id, x + fx[0][i], y + fx[1][i], tme + 1);
  }
}
bool bfs(){
  for (int i = 0; i <= ed; i++){
    vis[i] = 0;
  }
  vis[0] = 1;
  dis[0] = 1e9;
  queue<int> b;
  b.push(0);
  while (b.size()){
    auto x = b.front();
    b.pop();
    for (auto v : g[x]){
      int w = Dis[v.id];
      if (!w || vis[v.v]){
        continue;
      }
      pre[v.v] = v.id;
      dis[v.v] = min(dis[x], w);
      vis[v.v] = 1;
      b.push(v.v);
      if (v.v == ed){
        return 1;
      }
    }
  }
  return 0;
}
void update(){
  int x = ed;
  while (x){
    int o = pre[x];
    Dis[o] -= dis[ed];
    Dis[o ^ 1] += dis[ed];
    x = lst[o ^ 1];
  }
  ans += dis[ed];
}
bool check(){
  int cnt = 0;
  for (int i = 1; i <= n; i++){
    for (auto v : a[i]){
      cnt += (v == 'Y');
    }
  }
  return !cnt;
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  opt = -1;
  cin >> n >> t;
  ed = 1e4;
  t++;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
    a[i] = ' ' + a[i];
  }
  for (int i = 1; i <= n; i++){
    cin >> b[i];
    b[i] = ' ' + b[i];
    for (int j = 1; j <= n; j++){
      cnt[i][j] = 1e9;
    }
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= n; j++){
      if (a[i][j] == 'Z'){
        dfs1(i, j, 1);
      }
    }
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= n; j++){
      if ('1' <= a[i][j] && a[i][j] <= '9'){
        add(0, i * n + j, a[i][j] - '0');
        add(i * n + j, 0, 0);
        for (int i = 1; i <= n; i++){
          for (int j = 1; j <= n; j++){
            Vis[i][j] = 0;
          }
        }
        dfs2(i * n + j, i, j, 1);
      }
      if ('1' <= b[i][j] && b[i][j] <= '9'){
        add(i * n + j + n * n, ed, b[i][j] - '0');
        add(ed, i * n + j + n * n, 0);
      }
    }
  }
  while (bfs()){
    update();
  }
  cout << ans;
  return 0;
}
```

---

## 作者：rEdWhitE_uMbrElla (赞：0)

一开始我想到了一个暴力建图+网络流方法，，然后看到了那极小数据范围，，，然后就信心满满的打，，，然后就过了。。我这么弱的人都能这么水过这道题，说明这题真的不难。。。

---

切入正题。

1. 分析数据
	
    我们可以将```一个科学家可以在t分钟之内从(x0,y0)移动到(x1,y1)```作为```(x0,y0)在t时刻联通```。
    
2. 建图

	现在我们有一个网格图了，我们可以再将其转化一下。我们构造有一个源点，一个汇点，中间有两个层，每层$n^2$个节点的图。将每个点在开始时的科学家数量作为源点到这个点在第一层相应节点的边的流量。将每个点开始时的胶囊数量作为这个点在第二层所对应的节点到汇点的边的流量。若(x0,y0)和(x1,y1)在某一时刻是联通的，则将(x0,y0)在第一层所对应的节点和(x1,y1)在第二层所对应的节点连一条流量为正无穷的边。
    
3. 求解

	emmm...在我们构建的新图上跑一遍网络最大流，最大流即为答案。然而，根据相关法律法规，网络流题不允许卡Dinic/ISAP/HLPP，但可以卡EK，所以还是别用EK好。
    
上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 210;

char a[maxn][maxn],ss[maxn][maxn],can[maxn][maxn][2];
int och[200][2],was[maxn][maxn],n,q[maxn][maxn];

void bfs(int x, int y, int t) {
    int b,e;
    b=e=1;
    och[b][0] = x;
    och[b][1] = y;
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    int tx,ty,i,j;
    for (i=0;i<n;++i)
        for( j=0;j<n;++j)
            was[i][j] = -1;
    was[x][y]=0;
    while (b<=e) {
        x= och[b][0];
        y= och[b][1];
        if (was[x][y]==t) {
            ++b;
            continue;
        }
        for (i=0;i<4;++i) {
            tx = x + dx[i];
            ty = y + dy[i];
            if (tx <0 || tx >=n || ty <0 || ty >= n || a[tx][ty]=='Y')
                continue;
            if (was[tx][ty]==-1) {
                was[tx][ty] = was[x][y] + 1;
                och[++e][0] = tx;
                och[e][1] = ty;
            }
        }
        ++b;
    }
}

struct edge{
    int to;
    int cap;
};

vector <edge> e;
vector <int> v[maxn];
int flag[maxn]={0},pos[maxn]={0};

void addE(int from, int to, int d){
    edge ee;
    ee.to=to;
    ee.cap=d;
    e.push_back(ee);
    v[from].push_back(e.size()-1);
    ee.to=from;
    ee.cap=0;
    e.push_back(ee);
    v[to].push_back(e.size()-1);
}

int s,t,mn;

bool dfs(int w){
    int i,reb,u,tmp;
    flag[w]=1;
    if (w==t)
        return true;
    for (i=pos[w];i<v[w].size();i++){
        reb=v[w][i];
        u=e[reb].to;
        tmp=mn;
        if (e[reb].cap>0 && e[reb].cap<mn)
            mn=e[reb].cap;
        if (e[reb].cap>0 && (flag[u]==0 && dfs(u))){
            e[reb].cap-=mn;
            e[reb^1].cap+=mn;
            pos[w]=i+1;
            return true;
        }
        mn=tmp;
    }
    for (i=0;i<pos[w];i++){
        reb=v[w][i];
        u=e[reb].to;
        if (e[reb].cap>0 && (flag[u]==0 && dfs(u))){
            e[reb].cap-=mn;
            e[reb^1].cap+=mn;
            pos[w]=i+1;
            return true;
        }
    }
    return false;
}

const int inf = 0x3f3f3f3f;

int flow(){
    int i,fl=1,res=0;
    while (fl){
        fl=0;
        for (i=0;i<=t;i++){
            flag[i]=0;
            pos[i]=0;
        }
        while (1){
            mn=inf;
            if (!dfs(s))
                break;
            fl=1;
            flag[s]=flag[t]=0;
            res+=mn;
        }
    }
    return res;
}

void bfs2(int x, int y, int t) {
    int fx,fy;
    fx = x;
    fy = y;
    int cap = a[x][y] - '0';
    int b,e;
    b=e=1;
    och[b][0] = x;
    och[b][1] = y;
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    int tx,ty,i,j;
    for (i=0;i<n;++i)
        for( j=0;j<n;++j)
            q[i][j] = -1;
    q[x][y]=0;
    addE(fx*n+fy,fx*n+fy+n*n,cap);
    while (b<=e) {
        x= och[b][0];
        y= och[b][1];
        if (q[x][y]==t || q[x][y]==was[x][y]) {
            ++b;
            continue;
        }
        for (i=0;i<4;++i) {
            tx = x + dx[i];
            ty = y + dy[i];
            if (tx <0 || tx >=n || ty <0 || ty >= n || a[tx][ty]=='Z' || a[tx][ty]=='Y')
                continue;
            if (q[tx][ty]==-1 && (q[x][y]+1 <= was[tx][ty] || was[tx][ty]==-1)) {
                q[tx][ty] = q[x][y] + 1;
                addE(fx*n+fy,tx*n+ty+n*n,cap);
                och[++e][0] = tx;
                och[e][1] = ty;
            }
        }
        ++b;
    }
}

int main(){
    int T,i,j,x,y;
    cin >> n >> T;
    for (i=0;i<n;++i) {
        for (j=0;j<n;++j) {
            cin >> a[i][j];
            if (a[i][j]=='Z') {
                x = i;
                y = j;
            }
        }
    }
    for (i=0;i<n;++i) {
        for (j=0;j<n;++j)
            cin >> ss[i][j];
    }
    bfs(x,y,T);
    for (i=0;i<n;++i){
        for (j=0;j<n;++j){
            if (a[i][j] >='0' && a[i][j] <='9') {
                bfs2(i,j,T);
            }
        }
    }
    s = n * n * 2 + 1;
    t = n * n * 2 + 2;
    for (i=0;i<n;++i) {
        for (j=0;j<n;++j) {
            if (a[i][j]>='0' && a[i][j] <='9')
                addE(s,i*n+j,a[i][j]-'0');
            if (ss[i][j] >='1' && ss[i][j] <='9')
                addE(i*n+j+n*n,t,ss[i][j]-'0');
        }
    }
    int res = flow();
    cout << res;
    return 0;
}
```

这么水的题就不要抄题解了吧 QAQ

---

