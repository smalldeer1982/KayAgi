# UNIX插头 A Plug for UNIX

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=694

[PDF](https://uva.onlinejudge.org/external/7/p753.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/bd8d54abcc7626a52e03f403121ef0c4cca175ba.png)

## 样例 #1

### 输入

```
1
4
A
B
C
D
5
laptop B
phone C
pager B
clock B
comb X
3
B X
X A
X D```

### 输出

```
1```

# 题解

## 作者：Stinger (赞：3)

经典网络流题目。

由于插头种类的转换形成一个图，所以我们将这个图先建出来。

为了方便处理，建一个虚拟源点 $s$ 和一个虚拟汇点 $t$，$s$ 向所有设备的插头类型连一条边，所有已有插头类型向 $t$ 连一条边。

但是注意，转换器有无数个，但是从 $s$ 出发或到达 $t$ 的边只能走一次（不可能每个设备/插头有无限个）。于是加入边权，如果这是转换器边权为 $\infty$， 否则边权为 $1$。

那么这个图的实际意义是什么？对于一条 $u\rightarrow v$ ，边权为 $w$ 的边，代表有 $w$ 个 $u$ 类插头可以转换为 $v$ 类。对于这个题的样例，建出来的图是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/lt6yd5p0.png)

注意把重边的边权合并到了一起。

理解了这个图的本质后，可以想到跑一边 $s\rightarrow t$ 的最大流就是最大可以匹配的插头数量了。因为相当于要有尽量多与的 $s$ 直接相连的点和直接与 $t$ 相连的点匹配，在图中就体现为经过边“运送货物”过去。这正是最大流的定义。

然后说一下这道题的细节，首先是网络流，我只会EK所以用了EK（其实EK随机数据貌似吊打Dinic，只是会被卡飞），其次是字符串的问题，由于这题规模小，可以`cin+string+map`处理，如果你没事干可以`scanf+字符数组+手写哈希表`。但我相信以这题的规模选择STL比较合适。

```cpp
#include <iostream>
#include <map>
#include <queue>
#include <cstring>

inline int min(const int x, const int y) {return x < y ? x : y;}
const int INF = 1e9;
std::map<std::string, int> ID;
std::queue<int> Q;
struct Edge {
	int from, to, v, cap, nxt;
} e[1005];
int a[1005], p[1005], head[1005], x[1005], y[1005], tot, id;
inline void AddEdge(const int u, const int v, const int cap) {
	e[++ tot].from = u, e[tot].to = v, e[tot].cap = cap, e[tot].nxt = head[u], head[u] = tot;
	e[++ tot].from = v, e[tot].to = u, e[tot].cap = 0, e[tot].nxt = head[v], head[v] = tot;
}
int Edmonds_Karp(const int s, const int t) {
	int flow(0);
	do {
		while (Q.size()) Q.pop();
		Q.push(s);
		memset(a, 0, sizeof a);
		a[s] = INF;
		while (Q.size() && !a[t]) {
			int u(Q.front());
			Q.pop();
			for (int i(head[u]); i; i = e[i].nxt) {
				int v(e[i].to);
				if (!a[v] && e[i].cap)
					a[v] = min(a[u], e[i].cap), p[v] = i, Q.push(v);
			}
		}
		if (!a[t]) break;
		for (int i(t); i != s; i = e[p[i]].from)
			e[p[i]].cap -= a[t], e[p[i] ^ 1].cap += a[t];
		flow += a[t];
	} while (a[t]);
	return flow;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T --) {
		memset(head, 0, sizeof head);
		id = 0, tot = 1;
		ID.clear();
		int n, m, k;
		std::string name, name2;
		std::cin >> n;
		for (int i(1); i <= n; ++ i) {
			std::cin >> name;
			if (!ID.count(name)) ID[name] = ++ id;
			x[i] = ID[name];
		}
		std::cin >> m;
		for (int i(1); i <= m; ++ i) {
			std::cin >> name;
			std::cin >> name;
			if (!ID.count(name)) ID[name] = ++ id;
			y[i] = ID[name];
		}
		std::cin >> k;
		for (int i(1); i <= k; ++ i) {
			std::cin >> name >> name2;
			if (!ID.count(name)) ID[name] = ++ id;
			if (!ID.count(name2)) ID[name2] = ++ id;
			AddEdge(ID[name], ID[name2], INF);
		}
		for (int i(1); i <= m; ++ i) AddEdge(id + 1, y[i], 1);
		for (int i(1); i <= n; ++ i) AddEdge(x[i], id + 2, 1);
		printf("%d\n", m - Edmonds_Karp(id + 1, id + 2));
		if (T) puts("");
	}
	return 0;
}
```

---

## 作者：yizimi远欣 (赞：1)

### 题目简述

有 n 个插座，m 个设备和 k (n, m, k ≤ 100) 种转换器，每种转换器有无限多。已知每个插座的类型，每个设备的插头类型，以及每种转换器的插座类型和插头类型。插头和插座类型都用不超过 2424 个字母表示，插座只能插到类型名称相同的插座中。

例如，有 4 个插座，类型分别为 A，B，C，D；有 5 个设备，插头类型分别为 B，C，B，B，X；还有三种转换器，分别是 B->X，X->A 和 X->D。这里用 B -> X 表示插座类型为 B，插头类型为 X，因此一个插座类型为 B 的设备插上这种转换器之后就 “变成” 了一个插头类型为 X 的设备。转换器可以级联使用，例如插头类型为 A 的设备依次接上 A->B, B->C, C->D 这 3 个转换器之后会 “变成” 插头类型为 D 的设备。

要求插的设备尽量多。问最少剩几个不匹配的设备。

### 主要思路 ：最大流 （此处采用Dinic算法）

Dinic的模板就不仔细讲了，有需要的的同学去[网络最大流题解](https://www.luogu.org/problemnew/solution/P3376)中去看，我这里的Dinic是从第一篇题解中学来的，代码有些相似。

这道题最重要的是建图（似乎网络流的题都是这样吧）。

我们建立一个 s = 0 作为源点，既然我们要从抽象的从设备到插座连边，也就是说从设备流入图中，既然我们每个设备只能算 1 ，我们就讲 s 向每一个设备连一条容量为 1 的边。相似的，我们要流到每个插座，最终插座流向汇点 t = n + m + k + 1（n + m + k是题目中所给的可能最大的节点数，为了不重复，我们定的大一些），便于统计答案。

然后处理插座，设备与转换器的关系。

首先是设备，设备可以直接连到插座上，也可以连到转换器上，我们就把接口名字相同的连接起来。然后处理转换器，转换器还可以连转换器，也可以直接连到插座上，也是把名字相同的连接起来，切记，不要把同一个转换器首尾连接（好像可能性不大）。

然后跑个最大流，源点 s 汇点 t。

最后，UVa的毒瘤输出，，，注意代码最后的main函数，，，

### code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define go(i, j, n, k) for(int i = j; i <= n; i += k)
#define rep(i, x) for(int i = h[x]; i != -1; i = e[i].nxt)
#define curep(i, x) for(int i = cur[x]; i != -1; i = e[i].nxt)
#define mn 100010
#define inf 1 << 30
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -f; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

int n, m, K;
struct edge {
	int v, nxt, w;
} e[mn << 1];
int h[mn], p = -1;
inline void add(int a, int b, int c) {
	e[++p].nxt = h[a], h[a] = p;
	e[p].v = b, e[p].w = c; 
	e[++p].nxt = h[b], h[b] = p;
	e[p].v = a, e[p].w = 0;  
}
int dep[mn], cur[mn]; 
string na[mn], naa[mn], name1[mn], name2[mn];

inline bool bfs(int s, int t) {
	go(i, 0, n + m + K + 1, 1) dep[i] = inf;
	go(i, 0, n + m + K + 1, 1) cur[i] = h[i];
	queue<int> q;
	dep[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		rep(i, x) {
			int v = e[i].v, w = e[i].w;
			if(dep[v] >= inf && w) {
				dep[v] = dep[x] + 1;
				q.push(v);
			}
		}
	}
	if(dep[t] < inf) return true;
	return false;
}

int dfs(int x, int t, int lim) { 
	if(!lim || x == t) return lim;
	int flow = 0, f = 0;
	curep(i, x) {
		int v = e[i].v, w = e[i].w;
		cur[x] = i;
		if(dep[v] == dep[x] + 1 && (f = dfs(v, t, min(lim, w)))) {
			flow += f;
			lim -= f;
			e[i].w -= f;
			e[i ^ 1].w += f;
			if(!lim) break;
		}
	} 
	return flow;
}

inline int Dinic(int s, int t) {
	int maxflow = 0;
	while(bfs(s, t)) 
		maxflow += dfs(s, t, inf); 
	return maxflow;
}

inline void solve() {
	n = read();
	go(i, 1, n, 1) {
		cin >> na[i];
	}
	m = read();
	go(i, 1, m, 1) {
		string tmp; cin >> tmp;
		cin >> naa[i];
	}
	K = read();
	go(i, 1, K, 1) {
		cin >> name1[i] >> name2[i];
	}
	int s = 0, t = n + m + K + 1;
	go(i, 1, n, 1) {
		add(i, t, 1);
	} 
	go(i, 1, m, 1) {
		add(s, i + n, 1);
		go(j, 1, n, 1) {
			if(naa[i] == na[j])
				add(i + n, j, 1);
		}
		go(j, 1, K, 1) {
			if(naa[i] == name1[j])
				add(i + n, j + n + m, 1e9);
		}
	}
	go(i, 1, K, 1) {
		go(j, 1, n, 1) {
			if(name2[i] == na[j])
				add(i + n + m, j, 1e9);
		} 
		go(j, 1, K, 1) {
			if(name2[i] == name1[j] && i != j) {
				add(i + n + m, j + n + m, 1e9);
			}
		}
	}
	int ans = Dinic(s, t);
	cout << m - ans << "\n";
}
inline void init() {
	memset(h, -1, sizeof h);
	p = -1;
}
int main(){
	int T = read();
	while(T--) {
		init();
		solve();
		if(T) puts("");
	}
	return 0;
}
```

---

## 作者：_liet (赞：1)

这是一道最大流问题，我们可以以如下方式建图：

1. 首先我们先用容量为 1 的边把设备和插头连起来；
2. 然后再用容量为无穷大的边把转换器两头连起来；
3. 接着再添加一个源点 s 与所有设备相连，边容量为 1；
4. 最后再添加一个汇点 t 与墙上的插头相连，边容量为 1。

建完图之后我们用设备数减去从 s 到 t 的最大流就是答案啦。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define MAXVERTEX 810
#define INF 999999999
typedef long long ll;
using namespace std;

struct Edge {
    int from, to, cap, flow;
    Edge(int u = 0, int v = 0, int c = 0, int f = 0):
    from(u), to(v), cap(c), flow(f) {}
};

unordered_map<string, int> idxMapper;
int a[MAXVERTEX], p[MAXVERTEX], plugOfDevice[MAXVERTEX];
int id, plugs, plugsOfAdapter, devices, adapters, edges;
vector<int> g[MAXVERTEX];
vector<Edge> edge;

void init() {
    id = 1;
    plugsOfAdapter = 0;
    for (int i = 0; i < MAXVERTEX; i++) {
        g[i].clear();
    }
    edge.clear();
    idxMapper.clear();
}

/* 以下为求最大流常规操作 */

void add(int from, int to, int cap) {
    edge.push_back(Edge(from, to, cap, 0));
    edge.push_back(Edge(to, from, 0, 0));
    edges = edge.size();
    g[from].push_back(edges - 2);
    g[to].push_back(edges - 1);
}

int maxflow(int s, int t) {
    int flow = 0;
    while (true) {
        memset(a, 0, sizeof(a));
        queue<int> q;
        q.push(s);
        a[s] = INF;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < g[x].size(); i++) {
                Edge& e = edge[g[x][i]];
                if (!a[e.to] && e.cap > e.flow) {
                    p[e.to] = g[x][i];
                    a[e.to] = min(a[x], e.cap - e.flow);
                    q.push(e.to);
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        for (int u = t; u != s; u = edge[p[u]].from) {
            edge[p[u]].flow += a[t];
            edge[p[u]^1].flow -= a[t];
        }
        flow += a[t];
    }
    return flow;
}

/* 以上为求最大流常规操作 */

// 把插座映射到数字上
void setIndexOf(string str) {
    if (idxMapper[str] == 0) {
        idxMapper[str] = id++;
    }
}

// 获取插座对应的数字
int getIndexOf(string str) {
    if (idxMapper[str] == 0) {
        int idx = id++;
        idxMapper[str] = idx;
        plugs++;
        plugsOfAdapter++;
        return idx;
    } else {
        return idxMapper[str];
    }
}

// 输入数据
void input() {
    string plug, device, from, to;

    cin >> plugs;
    for (int i = 0; i < plugs; i++) {
        cin >> plug;
        setIndexOf(plug);
    }

    cin >> devices;
    for (int i = 0; i < devices; i++) {
        cin >> device >> plug;
        plugOfDevice[i] = getIndexOf(plug);
    }

    cin >> adapters;
    for (int i = 0; i < adapters; i++) {
        cin >> from >> to;
        add(getIndexOf(from) - 1, getIndexOf(to) - 1, INF);
    }
}

// 连边
// 这里的 s 是 plugs + devices，t 是 plugs + devices + 1
void link() {
    for (int i = 0; i < devices; i++) {
        add(plugs + devices, i + plugs, 1);
        add(i + plugs, plugOfDevice[i] - 1, 1);
    }
    // 适配器上的插口不应被连到 t 上，所以这里需要让 plugs - plugsOfAdapter
    for (int i = 0; i < plugs - plugsOfAdapter; i++) {
        add(i, plugs + devices + 1, 1);
    }
}

int main() {
    int t;

    ios::sync_with_stdio(false);
    cin >> t;
    for (int i = 0; i < t; i++) {
        // 不要忘了输出 cases 之间的空行
        if (i != 0) cout << endl;
        
        init();
        input();
        link();

        int ans = maxflow(plugs + devices, plugs + devices + 1);
        cout << devices - ans << endl;
    }

    return 0;
}

```

---

## 作者：EuphoricStar (赞：1)

## 思路

最大流。

首先求出设备 $i$ 是否可以通过接上 $0$ 个或多个转换器之后插到第 $j$ 个插座上。这部分可以使用 Floyd 算法，结点表示插图类型，边表示转换器，计算出任意一种插头类型是否能转化为另一种插头类型。

接下来建立源点 $s$ 和汇点 $t$。$s$ 到所有设备对应的插头类型连一条容量为 $1$ 的弧，所有插座对应的插头类型到 $t$ 连一条容量为 $1$ 的弧。对于所有设备 $i$ 和插座 $j$，如果设备 $i$ 对应的插头类型能转化为插头 $j$ 对应的插头类型，则在它们的插头类型之间连一条容量为 $\infty$ 的边，代表允许任意多个设备转换。

最后的答案就是设备数量减去最大流。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 410, maxm = 1000000;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

ll tc, n, s, t, p, m, kk, cnt, head[maxn], len;
string a[maxn], b[maxn];
bool can[maxn][maxn];
map<string, ll> mp;

ll ID(string &s) {
    if (mp.count(s)) {
        return mp[s];
    } else {
        return mp[s] = ++cnt;
    }
}

struct edge {
    ll from, to, next, cap, flow;
} edges[maxm];

void add_edge(ll u, ll v, ll c, ll f) {
    edges[++len].from = u;
    edges[len].to = v;
    edges[len].next = head[u];
    edges[len].cap = c;
    edges[len].flow = f;
    head[u] = len;
}

struct Dinic {
    bool vis[maxn];
    ll d[maxn], cur[maxn];

    void add(ll u, ll v, ll c) {
        add_edge(u, v, c, 0);
        add_edge(v, u, 0, 0);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<ll> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (q.size()) {
            ll u = q.front();
            q.pop();
            for (int i = head[u]; i; i = edges[i].next) {
                edge e = edges[i];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    ll dfs(ll u, ll a) {
        if (u == t || !a) {
            return a;
        }
        ll flow = 0, f;
        for (ll &i = cur[u]; i; i = edges[i].next) {
            edge &e = edges[i];
            if (d[u] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[i ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (!a) {
                    break;
                }
            }
        }
        return flow;
    }

    ll solve() {
        ll flow = 0;
        while (bfs()) {
            for (int i = 1; i <= n; ++i) {
                cur[i] = head[i];
            }
            flow += dfs(s, inf);
        }
        return flow;
    }
} solver;

int main() {
    scanf("%lld", &tc);
    while (tc--) {
        memset(can, 0, sizeof(can));
        memset(head, 0, sizeof(head));
        cnt = 0;
        len = 1;
        mp.clear();
        scanf("%lld", &p);
        for (int i = 1; i <= p; ++i) {
            string tmp;
            cin >> tmp;
            ID(tmp);
            a[i] = tmp;
        }
        scanf("%lld", &m);
        for (int i = 1; i <= m; ++i) {
            string a, tmp;
            cin >> a >> tmp;
            ID(tmp);
            b[i] = tmp;
        }
        n = cnt + 2;
        s = cnt + 1;
        t = n;
        scanf("%lld", &kk);
        while (kk--) {
            string s, t;
            cin >> s >> t;
            can[ID(s)][ID(t)] = 1;
        }
        for (int k = 1; k <= cnt; ++k) {
            for (int i = 1; i <= cnt; ++i) {
                for (int j = 1; j <= cnt; ++j) {
                    can[i][j] |= (can[i][k] & can[k][j]);
                }
            }
        }
        for (int i = 1; i <= m; ++i) {
            solver.add(s, ID(b[i]), 1);
        }
        for (int i = 1; i <= p; ++i) {
            solver.add(ID(a[i]), t, 1);
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= p; ++j) {
                int u = ID(b[i]), v = ID(a[j]);
                if (can[u][v]) {
                    solver.add(u, v, inf);
                }
            }
        }
        printf("%lld\n", m - solver.solve());
        if (tc) {
            putchar('\n');
        }
    }
    return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

很明显的网络流转化。我们可以令插座为源点，设备为汇点，各自连向超级源汇点。然后设备与插座同类直连，限制 $1$。设备、插座、不同的转接口与转接口同类相连，不限量。注意区分一下哪里进哪里出。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node { int p, v, nt; }e[40005]; int h[2005], cne;
inline void ins(int l, int r, int v) {
	e[++cne].nt = h[l]; e[cne].p = r; e[cne].v = v; h[l] = cne;
	e[++cne].nt = h[r]; e[cne].p = l; e[cne].v = 0; h[r] = cne;
}
int qp, n, m, k, s, t, d[2005], tp, th[2005], ans; queue<int>q;
string a[105], b[105], cl[105], cr[105];
inline bool bfs() {
	memset(d, 0, sizeof d);
	d[s] = 1; q.emplace(s);
	while (q.size()) {
		tp = q.front(); q.pop();
		for (int i = h[tp], sp; i; i = e[i].nt)
			if (!d[sp = e[i].p] && e[i].v)
				d[sp] = d[tp] + 1, q.emplace(sp);
	}
	return d[t];
}
inline int dfs(int p, int fs) {
	if (p == t || !fs) return fs; int ret = 0;
	for (int& i = th[p], sp, v; i; i = e[i].nt)
		if (d[sp = e[i].p] == d[p] + 1 && (v = dfs(sp, min(fs - ret, e[i].v)))) {
			ret += v; e[i].v -= v; e[i ^ 1].v += v;
			if (ret == fs) return ret;
		}
	return ret;
}
signed main() {
	ios::sync_with_stdio(0); cin >> qp;
	for (int i = 1; i <= qp; ++i) {
		memset(h, 0, sizeof h); cne = 1;
		cin >> n; ans = 0;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		cin >> m;
		for (int i = 1; i <= m; ++i) cin >> b[i] >> b[i];
		cin >> k;
		for (int i = 1; i <= k; ++i) cin >> cl[i] >> cr[i];
		s = n + m + k + 1, t = s + 1;
		for (int i = 1; i <= n; i++) ins(i, t, 1);//设接汇
		for (int i = 1; i <= m; i++) {
			ins(s, i + n, 1);//源接插
			for (int j = 1; j <= n; j++)
				if (b[i] == a[j]) ins(i + n, j, 1);//插接设
			for (int j = 1; j <= k; j++)
				if (b[i] == cl[j]) ins(i + n, j + n + m, 1e9);//转接设
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= n; j++)
				if (cr[i] == a[j]) ins(i + n + m, j, 1e9);//插接转
			for (int j = 1; j <= k; j++)
				if (cr[i] == cl[j] && i != j)
					ins(i + n + m, j + n + m, 1e9);//转接转
		}
		while (bfs())
			memcpy(th, h, sizeof h),
			ans += dfs(s, 1e9);
		cout << m - ans << endl;
		if (i != qp) cout << endl;
	}
}
```

---

## 作者：LG1038 (赞：0)

## UNIX插头 A Plug for UNIX 题解
这是一道最大流的题，题中说要求最少有几个不匹配的设备，只要求出匹配的设备数量，然后再用总设备数量减去它即可。求出匹配的设备数量可以用最大流（这里用 Dinic 算法）大致思路如下：

首先对输入的字符串进行操作，将其转换为数字（写哈希比较麻烦，所以用 map），注意一定要从 $2$ 开始，因为 $1$ 是源点。
然后将远点与每个插座都连一条边权为 $1$ 的边，因为一个插座只能用一次。然后再将每台设备与汇点连 $1$ 条边权为 $1$ 的边，（注意汇点应为 $2000$，保证不会有点与汇点重合）然后按照 $k$ 个关系将相应设备与插头之间连边权为无穷大的边，因为转换器可以使用无限次。然后跑一个最大流，就行了。

### code
```cpp
#include<bits/stdc++.h>
#define N 2003
using namespace std;
const int inf = 0x7ffffff;
map<string , int>qp;
int n, m, _cot = 1, s = 1, t = 2000;
string na;
int cnt = 1;
int dis[N];
int now[N];
int head[N];
struct node
{
	int to, nxt;
	int v;
	node(int a=0, int b=0, int c=0)
	{
		to=a, nxt=b, v=c;
	}
}ls[N<<2];
inline void add(int u, int v, int w)
{
	ls[++ _cot] = node(v, head[u], w);
	head[u] = _cot; 
}
inline long long dfs(int x, int sum)
{
	if(x == t) return sum;
	long long k, res = 0;
	for(int i = now[x]; i&&sum; i = ls[i].nxt)
	{
		now[x] = i;
		int tmp = ls[i].to;
		if(ls[i].v > 0 && dis[tmp] == dis[x] + 1)
		{
			k = dfs(tmp, min(sum, ls[i].v));
			if(k == 0) dis[tmp] = inf;
			ls[i].v -= k;
			ls[i ^ 1].v += k;
			res += k;
			sum -= k;
		}
	}
	return res;
}

inline bool bfs(void)
{
	for(int i = 1; i <= t; i++)
	{
		dis[i] = inf;
	}
	queue<int>q;
	q.push(s);
	dis[s] = 0;
	now[s] = head[s];
	
	while(!q.empty())
	{
		int last = q.front(); q.pop();
		for(int i = head[last]; i; i = ls[i].nxt)
		{
			int tmp = ls[i].to;
			if(ls[i].v > 0 && dis[tmp] == inf)
			{
				q.push(tmp);
				now[tmp] = head[tmp];
				dis[tmp] = dis[last] + 1;
				if(tmp == t) return true;
			}
		}
	}
	return false;
}
inline int dinic(void)
{
	int ans = 0;
	while(bfs()) ans += dfs(s,inf);
	return ans;
}//最大流
int main(void)
{
	cin >> n;
	for(int i = 1; i <= n; ++ i)
	{
		string f; 
		cin >> f;
		if(!qp[f]) qp[f] = ++ cnt;
		add(qp[f], t, 1);
		add(t, qp[f], 0);
	}
	cin >> m;
	for(int i = 1; i <= m; ++ i)
	{
		cin >> na >> na;
		if(!qp[na]) qp[na] = ++ cnt;
		add(s,qp[na],1);
		add(qp[na], s, 0);
	}
	int k;
	cin >> k;
	for(int i = 1; i <= k; ++ i)
	{
		string u,v;
		cin >> u >> v;
		if(!qp[u])qp[u]= ++cnt;
		if(!qp[v])qp[v]= ++cnt;
		add(qp[u],qp[v],inf);
		add(qp[v], qp[u], 0);
	}
	cout << m - dinic() << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路

可以联想到图。

最开始的建图思路是建两列插口，转换头，根据数据连接。然后就会发现，这样就不能实现“级联使用”，所以我们换一种思路，只要一列插口，转换头。将可以转换的插头连在一起。这样就实现了“级联使用”。

再将其与源点与汇点连接起来，跑一遍网络流就行了。汇点与其的边权为其有多少个相同的插口。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 405, maxm = (405 * (405 - 1)) >> 1, inf = 0x7fffffff;   

int n, m, s, t, k;

map<string, int> m1, m2, m3;

struct Edge
{
    int to, next, weight;
}edges[maxm]; 

int _count = 1, head[maxn], cur[maxn];

void add(int x, int y, int w)
{
    edges[++ _count].next = head[x];
    edges[_count].to = y;
    edges[_count].weight = w;
    head[x] = _count;
}

int level[maxn];

bool bfs()
{
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(head));
    queue<int> q;
    q.push(s);
    level[s] = 1;
    while (! q.empty())
	{
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != 0; i = edges[i].next)
		{
            int v = edges[i].to;
			int flow = edges[i].weight;
            if (flow > 0 && level[v] == 0)
			{
                level[v] = level[u] + 1;
                q.push(v);
            }
        }   
    }
    return (level[t] != 0);
}

int dfs(int p = s, int cur_flow = inf)
{
    if (p == t)
    {
    	return cur_flow;
	}
    int ret = 0;
    for (int i = cur[p]; i != 0; i = edges[i].next)
	{
        cur[p] = i;
        int v = edges[i].to, vol = edges[i].weight;
        if (level[v] == level[p] + 1 && vol > 0)
		{
            int f = dfs(v, min(cur_flow - ret, vol));
            edges[i].weight -= f;
            edges[i ^ 1].weight += f;
            ret += f;
            if (ret == cur_flow) 
				return ret;
        }
    }
    return ret;
}

int dinic()
{
    int max_flow = 0;
    while (bfs())
	{
        max_flow += dfs();
    }
    return max_flow;
}

signed main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t --) {
      cin >> n;
      s = 1, t = 805;
      for (int i = 1;i <= n; ++ i)
      {
          string str;
          cin >> str;
          ++ m2[str];	
          m3[str] = 1;
      }
      cin >> m;
      for (int i = 1;i <= m; ++ i)
      {
          string str1, str2;
          cin >> str1 >> str2;
          ++ m1[str2];
          m3[str2] = 1;
      }
      int cur = 1;
      for (auto i : m1)
      {
          add(s, ++ cur, i.second);
          add(cur, s, 0);
          m3[i.first] = cur;
          if (m2[i.first] > 0)
          {
              add(cur, t, m2[i.first]);
              add(t, cur, 0);
              m2.erase(i.first);
          }
      }
      for (auto i : m2)
      {
          add(++ cur, t, i.second);
          add(t, cur, 0);	
          m3[i.first] = cur;
      }
      cin >> k;
      for (int i = 1;i <= k; ++ i)
      {
          string str1, str2;
          cin >> str1 >> str2;
          auto it1 = m3.find(str1), it2 = m3.find(str2);
          add(it1->second, it2->second, inf);
          add(it2->second, it1->second, 0);
      }
      cout << m - dinic() << endl;
    }
    return 0;
}
```

---

## 作者：Arthur_Douglas (赞：0)

## 思路

一道网络流经典题。首先我们知道 $m$ 个字符串是记者所用的品牌。所以可以将这些字符串连向源点。这些的含义是从源点 $s$ 出发可以从此到达这些字符串。

而 $n$ 个插座则连向汇点。使得插座最后可以连到汇点 $t$。

**注意**，上述建图流量都为 $1$。

而中间的转接关系则是连向汇点的字符串与连向源点的字符串的建图关系，由于店员给的是无限个插座，所以流量是一个**极大值**。

**这相当于求可以插上插座的人的个数**。

所以这就可以很轻松的得到答案。相当于是所有的人数 $m$ 减去跑出来的最大流。

完
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int s , t;
map<string , bool> qp;
int rs = 1;
map<string , int> L;
struct line
{
	int to;
	int v; 
};
struct node
{
	line l;
	int next;
}ll[8001];
int dist[2001] , Now[2001] , head[2001] , _count = 1;
void add_edge(int a , int b , int c)
{
	ll[++ _count].l.to = b;
	ll[_count].l.v = c;
	ll[_count].next = head[a];
	head[a] = _count ++;
	ll[_count].l.to = a;
	ll[_count].l.v = 0;
	ll[_count].next = head[b];
	head[b] = _count;
}
bool bfs()//dinic 跑网络流
{
	for(int i = 2;i <= 2000;++ i)
	dist[i] = 0x7fffff;//大了会爆（同下）
	queue < int > q;
	q.push(s);
	Now[s] = head[s];
	while(!q.empty())
	{
		int tmp = q.front();
		q.pop();
		int tp = head[tmp];
		while(tp)
		{
			if(ll[tp].l.v && dist[ll[tp].l.to] == 0x7fffff)
			{
				q.push(ll[tp].l.to);
				Now[ll[tp].l.to] = head[ll[tp].l.to];
				dist[ll[tp].l.to] = dist[tmp] + 1;
				if(ll[tp].l.to == t)
				return true;
			}
			tp = ll[tp].next;
		}
	}
	return false;
}
int dfs(int start , int cnt)
{
	if(start == t)
	return cnt;
	int k , res = 0;
	int tp = Now[start];
	while(tp && cnt)
	{
		Now[start] = tp;
		if(ll[tp].l.v && dist[ll[tp].l.to] == dist[start] + 1)
		{
			k = dfs(ll[tp].l.to , min(cnt , ll[tp].l.v));
			if(! k)
			dist[ll[tp].l.to] = 0x7fffff;
			ll[tp].l.v -= k;
			ll[tp ^ 1].l.v += k;
			res += k;
			cnt -= k;
		}
		tp = ll[tp].next;
	}
	return res;
}
int main()
{
	int n , m , k;
	s = 1 , t = 2000;
	cin >> n;
	qp.clear();
	for(int i = 1;i <= n;++ i)
	{
		string kb;
		cin >> kb;
		if(!qp[kb])
		{
			qp[kb] = true;
			L[kb] = ++ rs;
		}
		add_edge(L[kb] , t , 1);//map 哈希之后转化数字点后建图（同下）
	}
	cin >> m;
	for(int i = 1;i <= m;++ i)
	{
		string sr , h;
		cin >> sr >> h;
		if(!qp[h])
		{
			qp[h] = true;
			L[h] = ++ rs;
		}
		add_edge(s , L[h] , 1);
	}
	cin >> k;
	for(int i = 1;i <= k;++ i)
	{
		string ab , bb;
		cin >> ab >> bb;
		if(!qp[ab])
		{
			qp[ab] = true;
			L[ab] = ++ rs;
		}
		if(!qp[bb])
		{
			qp[bb] = true;
			L[bb] = ++ rs;
		}
		add_edge(L[ab] , L[bb] , 0x7fffff);
	}
	int ans = 0;
	while(bfs())
	{
		ans += dfs(s , 0x7fffff);
	}
	cout << m - ans;
	return 0;
}
```
~~（hhhh）~~

---

## 作者：Luckin_Coffee (赞：0)

这是一篇极为好懂的题解，适合新手观看。

这道题因为我uva上不去，是在POJ提交的,所以读入是用cin检测而不是组数

前置知识是dinic或者Edmond-Karp算法求最大流，这一点相信点进来的小伙伴们肯定都会，不再详述。

网络流算法只是第一步，最重要的部分是建模，那么我们来分析一下这道题的模型吧。

这道题问有n个适配不同型号插头的插座，m个只能适配特定型号插头的设备，k种将特定型号转为另一种特定型号的转换插头，数量无限，问充分利用手头条件，最少有几个设备分不到插座？

题中的要素有，设备，插头，转换插头，所以我们将图分为两层。第一层是设备和插头的关系，每一个设备对应一个型号的插头，我们将设备和插头之间连上一条容量为1的边。编号方式为i(设备编号)--->设备数量m + j(插头编号)

第二层是插头和插座的关系，因为每种型号的插座只有一个，而且只能插进去对应的插头，所以我们将对等的型号插头和插座之间连上容量为1的边。编号方式为: 设备数量m + j(插头编号)---> m + 插头种类总数 tot + 插座编号k

那现在只剩下转换插头了，这个自然很好想，将转换器转换的插头A和B之间连上一条边，因为A和B都是插头，所以他们在同一层，题面又说转换插头的数量是无限的，所以边的容量为INF。

这样一来我们的模型就建好了，为了方便统计，我们再把所有的设备连上超级源点，所有的插座连上超级汇点，跑一遍Dinic就能求出最多有多少个设备可以插进插座里了。这里注意题目问的是最少有多少个设备插不进插座，所以用设备的总数减去最多能插进去的就是所要求的答案了。

因为输入的是字符串，我们可以用两个map分别将插座和设备的字符串映射到一个int变量上，在读入设备的时候可能会遇到没有插座情况，这样的时候就创建新的编号就行了，最后处理一下源和汇的关系就好了

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define limit (100000 + 5)//防止溢出
#define INF 0x3f3f3f3f
#define inf 0x3f3f3f3f3f
#define lowbit(i) i&(-i)//一步两步
#define EPS 1e-6
#define FASTIO  ios::sync_with_stdio(false);cin.tie(0);
#define ff(a) printf("%d\n",a );
#define pi(a,b) pair<a,b>
#define rep(i, a, b) for(ll i = a; i <= b ; ++i)
#define per(i, a, b) for(ll i = b ; i >= a ; --i)
#define MOD 998244353
#define traverse(u) for(int i = head[u]; ~i ; i = edge[i].next)
#define FOPEN freopen("C:\\Users\\tiany\\CLionProjects\\bbb\\data.txt", "rt", stdin)
#define FOUT freopen("C:\\Users\\tiany\\CLionProjects\\bbb\\dabiao.txt", "wt", stdout)
typedef long long ll;
typedef unsigned long long ull;
ll read(){
    ll sign = 1, x = 0;char s = getchar();
    while(s > '9' || s < '0' ){if(s == '-')sign = -1;s = getchar();}
    while(s >= '0' && s <= '9'){x = (x << 3) + (x << 1) + s - '0';s = getchar();}
    return x * sign;
}//快读
void write(ll x){
    if(x < 0) putchar('-'),x = -x;
    if(x / 10) write(x / 10);
    putchar(x % 10 + '0');
}
int n,m,vs,ve,k;
int layer[limit],head[limit], cnt;
struct node{
    int to ,next;
    ll flow;
}edge[limit];
ll max_flow;
void add_one(int u , int v, ll flow){
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].flow = flow;
    head[u] = cnt++;
}
inline void add(int u, int v, ll flow){
    add_one(u,v,flow);
    add_one(v, u,0);
}
inline void init(bool flag = true){
    if(flag){
        memset(head, -1, sizeof(head));
        max_flow = cnt = 0;
    }else{
        memset(layer, -1, sizeof(layer));
    }
}
inline bool bfs(){
    init(false);
    queue<int>q;
    layer[vs] = 0;//从第0层开始
    q.push(vs);
    while (q.size()){
        int u = q.front();
        q.pop();
        traverse(u){
            int v = edge[i].to,flow = edge[i].flow;
            if(layer[v] == -1 && flow > 0){
                layer[v] = layer[u] + 1;//迭代加深
                q.push(v);
            }
        }
    }
    return ~layer[ve];
}
ll dfs(int u, ll flow){
    if(u == ve)return flow;
    ll rev_flow = 0,min_flow;
    traverse(u){
        int v =edge[i].to;
        ll t_flow = edge[i].flow;
        if(layer[v] == layer[u] + 1 && t_flow > 0){
            min_flow = dfs(v, min(flow, t_flow));
            flow -= min_flow;
            edge[i].flow -= min_flow;
            rev_flow += min_flow;
            edge[i^1].flow += min_flow;
            if(!flow)break;
        }
    }
    if(!rev_flow)layer[u] = -1;
    return rev_flow;
}
void dinic(){
    while (bfs()){
        max_flow += dfs(vs,inf);
    }
}
map<string,int>device,plug;//插头和插座
int main() {
#ifdef LOCAL
    FOPEN;
#endif
    FASTIO
    while (cin>>n){
        device.clear();//初始化
        plug.clear();
        init();//初始化
        int tot = 0, num = 0;//分别记录插头的数目和设备的数目
        vs = 80001, ve = vs + 1;
        rep(i ,1,n){
            string str;
            cin>>str;
            plug[str] = ++tot;//编号
        }
        cin>>m;
        rep(i ,1,m){
            string item, match;
            cin>>item>>match;
            device[item] = ++num;//编号
            if(plug.find(match) == plug.end())plug[match] = ++tot;
            add(device[item], m + plug[match],1);
            add(vs, device[item], 1);//添加便
        }
        cin>>k;
        rep(i ,1, n){
            add(m + i , m + tot + i, 1);
            add(m + tot + i , ve, 1);
        }
        rep(i ,1, k){
            string fst, scd;
            cin>>fst>>scd;
            add(plug[fst] + m , plug[scd] + m ,INF);
        }
        dinic();
        cout<<(m - max_flow)<<endl;
    }
    return 0;
}

```


---

