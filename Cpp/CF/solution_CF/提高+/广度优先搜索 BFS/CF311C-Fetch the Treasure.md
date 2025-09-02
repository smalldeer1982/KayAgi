# Fetch the Treasure

## 题目描述

Rainbow built $ h $ cells in a row that are numbered from 1 to $ h $ from left to right. There are $ n $ cells with treasure. We call each of these $ n $ cells "Treasure Cell". The $ i $ -th "Treasure Cell" is the $ a_{i} $ -th cell and the value of treasure in it is $ c_{i} $ dollars.

Then, Freda went in the first cell. For now, she can go just $ k $ cells forward, or return to the first cell. That means Freda was able to reach the 1st, ( $ k+1 $ )-th, ( $ 2·k+1 $ )-th, ( $ 3·k+1 $ )-th cells and so on.

Then Rainbow gave Freda $ m $ operations. Each operation is one of the following three types:

1. Add another method $ x $ : she can also go just $ x $ cells forward at any moment. For example, initially she has only one method $ k $ . If at some moment she has methods $ a_{1},a_{2},...,a_{r} $ then she can reach all the cells with number in form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF311C/098e382b3b8846367b54760ca19a29ffa8e34102.png), where $ v_{i} $ — some non-negative integer.
2. Reduce the value of the treasure in the $ x $ -th "Treasure Cell" by $ y $ dollars. In other words, to apply assignment $ c_{x}=c_{x}-y $ .
3. Ask the value of the most valuable treasure among the cells Freda can reach. If Freda cannot reach any cell with the treasure then consider the value of the most valuable treasure equal to 0, and do nothing. Otherwise take the most valuable treasure away. If several "Treasure Cells" have the most valuable treasure, take the "Treasure Cell" with the minimum number (not necessarily with the minimum number of cell). After that the total number of cells with a treasure is decreased by one.

As a programmer, you are asked by Freda to write a program to answer each query.

## 说明/提示

In the sample, there are 10 cells and 3 "Treasure Cells". The first "Treasure Cell" is cell 5, having 50 dollars tresure in it. The second "Treasure Cell" is cell 7, having 60 dollars tresure in it. The third "Treasure Cell" is cell 8, having 100 dollars tresure in it.

At first, Freda can only reach cell 1, 3, 5, 7 and 9. In the first operation, we reduce the value in the second "Treasure Cell" from 60 to 55. Then the most valuable treasure among the "Treasure Cells" she can reach is max(50, 55) = 55. After the third operation, she can also go 3 cells forward each step, being able to reach cell 1, 3, 4, 5, 6, 7, 8, 9, 10. So the most valuable tresure is 100.

Noticed that she took the 55 dollars and 100 dollars treasure away, so the last answer is 50.

## 样例 #1

### 输入

```
10 3 5 2
5 50
7 60
8 100
2 2 5
3
1 3
3
3
```

### 输出

```
55
100
50
```

# 题解

## 作者：LTb_ (赞：5)

注意到 $k \le 10^4$。考虑把所有位置按模 $k$ 的值分成 $k$ 类，并按除 $k$ 的商分成若干段。显然，如果在第 $i$ 段可以到达一个属于第 $j$ 类的位置，那么所有在第 $i$ 段以后且属于第 $j$ 类的位置都是可以到达的。于是，只需要维护 $d_i$ 表示属于第 $i$ 类的位置在哪一段第一次出现，就可以 $\mathcal O(1)$ 地判定某个位置是否可以到达。

考虑第一种操作。考虑「向前走 $x$ 步」这个操作**在模 $k$ 下意义**的本质：它使得 $i$ 可以到达 $(i + x) \bmod k$，但是中间要跨过 $\left\lfloor\dfrac{i+x}{k}\right\rfloor$ 个额外的段。于是建个图：设一个源点 $S$，并对于所有 $0 \le i <k$ 连权值为 $d_i$ 的有向边 $S \to i$，点之间按上面说的「本质」连边，从源点跑 Dijkstra，跑完之后更新 $d$ 即可。单次操作的时间复杂度为 $\mathcal O(k \log k + n)$。

答案可以用 `multiset` 维护，操作二和三也直接在 `multiset` 里面操作。

```c++
// 2021.08.06 - 11:32
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define debug printf("Passing Line %d in function [%s].\n",__LINE__,__FUNCTION__)
#define fi first
#define se second
inline int read(){
    int x=0,f=1;
    char ch='.';
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
inline void chmax(int &x,int y){x=max(x,y);}
inline void chmin(int &x,int y){x=min(x,y);}

const int MOD = 998244353;
inline int add(int x,int y){return(x+y>=MOD)?(x+y-MOD):((x+y<0)?(x+y+MOD):(x+y));}

const int MAXN = 100005, MAXM = 10005;
const int INF = 1e18 + 20;
int stO_yzhang_txdy_ddjxd_Orz, n, m, k;
int a[MAXN], c[MAXN];
int d[MAXM];
multiset<int> s;
bool in[MAXN];

inline bool ok(int x) {
	return d[x % k] <= x / k;
}

struct Node {
	int x, w;
	bool operator < (const Node& b) const {
		return w > b.w;
	}
};
int dis[MAXN];
bool vis[MAXN];
vector<Node> G[MAXN];

void dijkstra(int S) {
	memset(vis, false, sizeof(vis));
	priority_queue<Node> q;

	dis[S] = 0;
	q.push((Node) { S, 0 });
	while (!q.empty()) {
		auto p = q.top();
		q.pop();
		if (vis[p.x]) continue;
		vis[p.x] = true;

		for (auto i : G[p.x]) {
			if (vis[i.x]) continue;
			if (dis[i.x] > p.w + i.w) {
				dis[i.x] = p.w + i.w;
				q.push((Node) { i.x, dis[i.x] });
			}
		}
	}
}

inline void upd(int x) {
	for (int i = 0; i < k; i++)
		G[i].clear(), dis[i] = INF;

	for (int i = 0; i < k; i++) {
		G[i].push_back((Node){(i + x) % k, (i + x) / k});
		G[k].push_back((Node){i, d[i]});
	}

	dijkstra(k);
	for (int i = 0; i < k; i++) {
		chmin(d[i], dis[i]);
	}

	for (int i = 1; i <= n; i++) {
		if (ok(a[i]) && !in[i]) {
			in[i] = true;
			s.insert(c[i]);
		}
	}
}

signed main()

{
	stO_yzhang_txdy_ddjxd_Orz = read(), n = read(), m = read(), k = read();

	for (int i = 0; i < k; i++)
		d[i] = INF;
	d[1 % k] = 0;

	for (int i = 1; i <= n; i++) {
		a[i] = read(), c[i] = read();
		if (ok(a[i])) s.insert(c[i]), in[i] = true;
	}

	while (m--) {
		int opt = read();
		if (opt == 1) {
			int x = read();
			upd(x);
		} else if (opt == 2) {
			int x = read(), y = read();
			if (in[x]) s.erase(s.find(c[x]));
			c[x] -= y;
			if (in[x]) s.insert(c[x]);
		} else {
			if (s.empty()) cout << 0 << endl;
			else {
				cout << *prev(s.end()) << endl;
				s.erase(prev(s.end()));
			}
		}
	}
	return 0;
}
```



---

## 作者：bluewindde (赞：0)

发现集合 $S$ 中存在一个不超过 $10^4$ 的数，考虑同余最短路，对于每次向集合 $S$ 中添加数暴力重新处理。于是集合 $Q$ 容易确定，线段树维护后两个操作即可。

时间复杂度 $O(Tk \log k + m \log n)$，其中 $T$ 是操作 $1$ 的个数，可以通过。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define int long long

using namespace std;

const int inf = 2e18;

int h, n, q;
struct {
    int x, y;
} a[100005];
bool b[100005];
bool disabled[100005];
int S[25], cnt;

struct node {
    int val, id;
    friend inline node operator+(const node &x, const node &y) {
        if (x.val > y.val)
            return {x.val, x.id};
        else if (x.val < y.val)
            return {y.val, y.id};
        return {x.val, min(x.id, y.id)};
    }
} d[400005];
static inline void build(int s, int t, int p) {
    if (s == t) {
        if (b[s])
            d[p] = {a[s].y, s};
        else
            d[p] = {0, -1};
        return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, p << 1);
    build(mid + 1, t, p << 1 | 1);
    d[p] = d[p << 1] + d[p << 1 | 1];
}
static inline void update(int x, int s, int t, int p) {
    if (s == t) {
        if (b[s])
            d[p] = {a[s].y, s};
        else
            d[p] = {0, -1};
        return;
    }
    int mid = (s + t) >> 1;
    if (x <= mid)
        update(x, s, mid, p << 1);
    else
        update(x, mid + 1, t, p << 1 | 1);
    d[p] = d[p << 1] + d[p << 1 | 1];
}

int dis[10005];
vector<pair<int, int>> vec[10005];
static inline void build() {
    sort(S + 1, S + cnt + 1);
    for (int i = 0; i < S[1]; ++i) {
        vec[i].clear();
        dis[i] = inf;
    }
    for (int j = 0; j < S[1]; ++j)
        for (int i = 2; i <= cnt; ++i)
            vec[j].push_back({(j + S[i]) % S[1], S[i]});
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 0});
    dis[0] = 0;
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dis[u])
            continue;
        for (auto [v, w] : vec[u]) {
            int dd = d + w;
            if (dd < dis[v]) {
                dis[v] = dd;
                q.push({dd, v});
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        b[i] = !disabled[i] && dis[a[i].x % S[1]] <= a[i].x;
    build(1, n, 1);
}

static inline void solve() {
    cin >> h >> n >> q >> S[++cnt];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y;
        --a[i].x;
    }
    build();
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> S[++cnt];
            build();
        } else if (op == 2) {
            int x, w;
            cin >> x >> w;
            a[x].y -= w;
            update(x, 1, n, 1);
        } else {
            if (d[1].id == -1) {
                cout << "0\n";
                continue;
            }
            cout << d[1].val << '\n';
            b[d[1].id] = false;
            disabled[d[1].id] = true;
            update(d[1].id, 1, n, 1);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

