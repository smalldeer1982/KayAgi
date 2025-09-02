# [NERC 2022] Dominoes

## 题目描述

Dora 喜欢玩多米诺骨牌。她拿来一个 $n \times m$ 的棋盘，将一些单元格标记为已占据，然后尝试用 $2 \times 1$ 的多米诺骨牌填满所有未被占据的单元格。

![](https://cdn.luogu.com.cn/upload/image_hosting/izci2rsk.png)

她的弟弟 Dani 喜欢对他姐姐搞恶作剧。所以当她不在的时候，他又将两个未被占据的单元格标记为已占据。他想通过这种方式，使得无法再用多米诺骨牌填满所有未被占据的单元格。

请帮助 Dani 计算他有多少种选择这两个单元格的方法。由于 Dani 最多数到一百万，如果方法数是 $x$，请输出 $\min(x, 10^6)$。

## 说明/提示

翻译由 gemini2.5pro 完成

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

## 作者：ケロシ (赞：3)

好题啊

首先对网格图进行黑白染色，这样的话选两个黑或两个白去掉一定不合法，因为答案要对 $10^6$ 取 $\min$，所以当白点数加黑点数大于 $2\times 10^3$ 的时候就顶到 $10^6$ 了，所以只需要考虑格子数小于 $2 \times 10^3$ 的情况。

先考虑暴力怎么做，就是暴力枚举去掉的白点和黑点，然后跑二分图匹配，这样肯定行不通。

再进行一些观察，不难发现因为原图合法，所以考虑先对原图找出一组合法的二分图匹配。接下来如果要去掉一对点，那么要求去掉后的匹配数只减掉 $1$。不难发现这个的充要条件是这两个点之间存在一条增广路。因为存在的话直接退掉这个增广路，不存在的话匹配数要减 $2$。

每次从一个起点遍历增广路即可，设点数为 $n \le 2 \times 10^3$，复杂度就是 $O(n^2)$。


```cpp
const int N = 2e3 + 5;
const int M = 1e5 + 5;
const int V = 1e6;
const int INF = 0x3f3f3f3f;
int n, m;
string s[N];
int a[N][N], cnt;
int dx[] = {0, 0, 1, - 1};
int dy[] = {1, - 1, 0, 0};
struct Edge { int ne, to, ew; } e[M];
int fi[N], c[N], ecnt;
int S, T, d[N];
int vis[N];
void init() {
	ecnt = 1;
	memset(fi, 0, sizeof fi);
}
void add(int u, int v, int w) {
	e[++ ecnt] = {fi[u], v, w};
	fi[u] = ecnt;
	e[++ ecnt] = {fi[v], u, 0};
	fi[v] = ecnt;
}
bool bfs() {
	memset(d, 0x3f, sizeof d);
	queue<int> q; 
	d[S] = 0; q.push(S);
	while(! q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = fi[u]; i; i = e[i].ne) if(e[i].ew) {
			int v = e[i].to;
			if(d[v] == INF) {
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	return d[T] != INF;
}
int dfs(int u, int w) {
	if(u == T || ! w) return w;
	int res = 0;
	for(int & i = c[u]; i; i = e[i].ne) if(e[i].ew) {
		int v = e[i].to;
		if(d[v] != d[u] + 1) continue;
		int val = dfs(v, min(w, e[i].ew));
		if(! val) continue;
		e[i].ew -= val;
		e[i ^ 1].ew += val;
		w -= val;
		res += val;
		if(! w) return res;
	}
	return res;
}
int dinic(int _S, int _T) {
	S = _S, T = _T;
	int res = 0;
	while(bfs()) {
		memcpy(c, fi, sizeof c);
		res += dfs(S, INF);
	}
	return res;
}
void solve() {
	cin >> n >> m;
	FOR(i, 1, n) {
		cin >> s[i];
		s[i] = ' ' + s[i];
	}
	FOR(i, 1, n) FOR(j, 1, m) if(s[i][j] == '.') if((i + j) & 1)
		a[i][j] = ++ cnt;
	FOR(i, 1, n) FOR(j, 1, m) if(s[i][j] == '.') if(! ((i + j) & 1))
		a[i][j] = ++ cnt;
	cnt /= 2;
	if(1ll * cnt * (cnt - 1) >= V) {
		cout << V << endl;
		return;
	}
	int S = 0, T = cnt * 2 + 1;
	init();
	FOR(i, 1, cnt) add(S, i, 1);
	FOR(i, 1, cnt) add(i + cnt, T, 1);
	FOR(i, 1, n) FOR(j, 1, m) if(s[i][j] == '.') if((i + j) & 1) REP(d, 4) {
		int x = i + dx[d], y = j + dy[d];
		if(x < 1 || x > n || y < 1 || y > m) continue;
		if(s[x][y] == '#') continue;
		add(a[i][j], a[x][y], 1);
	}
	dinic(S, T);
	int ans = cnt * (cnt - 1);
	FOR(i, 1, cnt) {
		FOR(j, 1, cnt * 2) vis[j] = 0;
		queue<int> q;
		q.push(i); vis[i] = 1;
		while(! q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = fi[u]; i; i = e[i].ne) if(e[i ^ 1].ew) {
				int v = e[i].to;
				if(v == S || v == T) continue;
				if(! vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
		FOR(j, cnt + 1, cnt * 2) ans += ! vis[j];
	}
	chmin(ans, V);
	cout << ans << endl;
}
```

---

