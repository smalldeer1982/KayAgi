# Angels & Demons

## 题目背景

教皇内侍已经感觉到了身体上的疼痛。疼痛迅速传遍了全身，让他想抓想挠。

>不要忘记耶稣所遭受的痛苦。

他感觉喉咙中有种火烧火燎般的疼痛，就连吗啡都无法将之化解。

>我在这里的事情已经做完了。

他激起了人们的敬畏之心，人们又有了希望。

在帕利恩凹室里的时候，教皇内侍遵从上帝的教诲，举行了涂油仪式。他的身体上，发须上，面颊上，麻布长袍上，全身都涂满了灯油。他这会儿像是浸泡在神圣的绿色灯油中一样，气味芬芳，如母亲的体香，可却易燃烧。他将会幸运地升天。那是个充满奇迹而又迅速的过程。他留给世人的不再是丑闻……而是一股新的力量和奇迹。

他的手滑入长袍的口袋，摸出从帕利恩凹室里拿来的小小的金色打火机。

他低声说出了上帝在最后审判时说过的一句话。

>熊熊烈焰直冲云霄，上帝的天使也会在火焰中升天。

他的大拇指按在了打火机上。

人们还在圣彼得广场上唱着颂歌……

## 题目描述

给定 $n$ 个由小写字母组成的模板串 $S_{1...n}$，$q$ 组询问，询问分为以下两种类型：

1. `1 T`：给定一个由小写字母组成的询问串 $T$。
2. `2 p l r`：设 $num(p,l,r)$ 表示 $S_p$ 的 $[l,r]$ 子串是多少个询问串的子串，求 $\max\limits_{i=1}^{l}(num(p,i,r))$。

## 说明/提示

对于 $100\%$ 数据：$1\le n,q\le 10^5$，$\sum\limits_{i=1}^{n}|S_i|\le5\times10^5$，$\sum|T|\le5\times10^5$，$1\le p\le n$，$w_0\in\{0,1\}$，$1\le A,B<C\le10^9$。

|测试点|分值|$n\le$|$\sum\limits_{i=1}^{n}\|S_i\|\le$|$q\leq $|$\sum \| T\| \leq $|$w_0=$|其他限制|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$3$|$20$|$200$|$200$|$5000$|$0$|无|
|$2$|$3$|$200$|$2000$|$200$|$5000$|$0$|无|
|$3$|$3$|$200$|$2000$|$200$|$5000$|$0$|无|
|$4$|$3$|$200$|$2000$|$200$|$5\times10^5$|$0$|无|
|$5$|$3$|$200$|$2000$|$200$|$5\times10^5$|$0$|无|
|$6$|$3$|$1$|$5\times10^5$|$2$|$5\times10^5$|$0$|无|
|$7$|$3$|$1$|$5\times10^5$|$2$|$5\times10^5$|$0$|无|
|$8$|$4$|$10^5$|$10^5$|$10^5$|$10^5$|$0$|无|
|$9$|$3$|$10^5$|$10^5$|$10^5$|$10^5$|$0$|字符串随机|
|$10$|$4$|$10^5$|$2 \times 10^5$|$10^5$|$2 \times 10^5$|$0$|无|
|$11$|$3$|$10^5$|$2 \times 10^5$|$10^5$|$2 \times 10^5$|$0$|字符串随机|
|$12$|$4$|$10^5$|$3 \times 10^5$|$10^5$|$3 \times 10^5$|$0$|无|
|$13$|$3$|$10^5$|$3 \times 10^5$|$10^5$|$3 \times 10^5$|$0$|字符串随机|
|$14$|$4$|$10^5$|$4 \times 10^5$|$10^5$|$4 \times 10^5$|$0$|无|
|$15$|$3$|$10^5$|$4 \times 10^5$|$10^5$|$4 \times 10^5$|$0$|字符串随机|
|$16$|$4$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|无|
|$17$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|字符串随机|
|$18$|$3$|$10^5$|$2 \times 10^5$|$10^5$|$5\times10^5$|$0$|无|
|$19$|$3$|$10^5$|$3 \times 10^5$|$10^5$|$5\times10^5$|$0$|无|
|$20$|$3$|$10^5$|$4 \times 10^5$|$10^5$|$5\times10^5$|$0$|无|
|$21$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|字符串随机|
|$22$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|无|
|$23$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|无|
|$24$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|无|
|$25$|$3$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$0$|无|
|$26$|$4$|$10^5$|$3\times10^5$|$10^5$|$5\times10^5$|$1$|无|
|$27$|$4$|$10^5$|$4\times10^5$|$10^5$|$5\times10^5$|$1$|无|
|$28$|$4$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$1$|无|
|$29$|$4$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$1$|无|
|$30$|$4$|$10^5$|$5\times10^5$|$10^5$|$5\times10^5$|$1$|无|

**测试点 $8\sim 17$ 保证对于所有询问 $2$，$l=1$。**

## 样例 #1

### 输入

```
5 11 0
abb
aab
baab
bbaa
aabbb
1 ab
2 1 1 3
2 2 2 3
1 ba
2 3 1 2
2 4 1 2
2 4 2 3
1 abb
2 5 2 4
2 1 1 3
2 1 1 2
```

### 输出

```
0
1
1
0
1
1
1
2
```

## 样例 #2

### 输入

```
5 11 1
114 514 1919810
abb
aab
baab
bbaa
aabbb
1 ab
2 1 1 3
2 2 2 3
1 ba
2 3 1 2
2 4 1 2
2 4 2 3
1 abb
2 5 2 4
2 1 1 3
2 1 1 2
```

### 输出

```
0
0
1
0
0
1
1
0
```

# 题解

## 作者：Alex_Wei (赞：12)

> [P8947 Angels & Demons](https://www.luogu.com.cn/problem/P8947)

因为查询和所有询问串相关，所以在加入询问串时，它对每个模板串的贡献都要考虑到。因此只能对所有模板串统一建出结构。

因为查询和模板串子串相关，所以这个结构需要描述所有模板串的所有子串。我们考虑广义 SAM。

加入询问串 $T$，考虑它的贡献。我们将 $T$ 输入 SAM，得到它的每个前缀的最长的等于某个模板串子串的后缀长度 $L$，以及对应状态 $p$。根据 SAM 的 link 树的性质，可知 $T$ 对某子串产生贡献的充要条件是：

- 存在 $p$ 在该子串对应状态的子树内（不包括自身）。
- 存在 $p$ 等于该子串的对应状态，且子串长度不大于对应的 $L$。

相同的 $p$ 只保留 $L$ 最大的一个，然后删去所有子树内还有其它 $p$ 的 $(p, L)$。接下来，将所有 $p$ 的父亲到根的链并上所有节点的答案加 $1$，表示对应状态的所有子串答案均加 $1$，链加单点查转成单点加子树查。最后将所有 $p$ 的所有长度不大于 $L$ 的子串答案加 $1$，动态开点线段树维护即可。

说白了，就是把 Divljak 放在广义 SAM 上。

时空复杂度线性对数加线性字符集。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

constexpr int N = 1e6 + 5;
constexpr int M = N << 4;
constexpr int K = 20;
constexpr int S = 26;

namespace GSAM {
  int node, cnt = 1;
  int son[N][S], len[N], fa[N], anc[K][N];
  int ins(int p, int it) {
    int to = son[p][it];
    if(to && len[p] + 1 == len[to]) return to;
    int cur = ++cnt;
    len[cur] = len[p] + 1;
    while(!son[p][it]) son[p][it] = cur, p = fa[p];
    if(!p) return fa[cur] = 1, cur;
    int q = son[p][it];
    if(len[p] + 1 == len[q]) return fa[cur] = q, cur;
    int cl = ++cnt;
    len[cl] = len[p] + 1;
    memcpy(son[cl], son[q], S << 2);
    fa[cl] = fa[q], fa[q] = fa[cur] = cl;
    while(son[p][it] == q) son[p][it] = cl, p = fa[p];
    return to ? cl : cur;
  }
  void build() {
    for(int i = 0; i < K; i++)
      for(int j = 1; j <= cnt; j++) {
        if(i) anc[i][j] = anc[i - 1][anc[i - 1][j]];
        else anc[i][j] = fa[j];
      }
  }
  int locate(int pos, int L) {
    for(int i = K - 1; ~i; i--) {
      int q = anc[i][pos];
      if(len[q] >= L) pos = q;
    }
    return pos;
  }
  void path(char *s, int m, auto P) {
    int L = 0, p = 1;
    for(int i = 1; i <= m; i++) {
      int it = s[i] - 'a';
      while(p > 1 && !son[p][it]) L = len[p = fa[p]];
      if(son[p][it]) L++, p = son[p][it];
      P[i - 1] = {p, L};
    }
  }
}

namespace BIT {
  int c[N];
  void add(int x, int v) {
    while(x < N) c[x] += v, x += x & -x;
  }
  int query(int x) {
    int s = 0;
    while(x) s += c[x], x -= x & -x;
    return s;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
}

namespace SEG {
  int node, R[N], ls[M], rs[M], val[M];
  void modify(int l, int r, int p, int &x) {
    if(!x) x = ++node;
    val[x]++;
    if(l == r) return;
    int m = l + r >> 1;
    if(p <= m) modify(l, m, p, ls[x]);
    else modify(m + 1, r, p, rs[x]);
  }
  int query(int l, int r, int ql, int qr, int x) {
    if(ql <= l && r <= qr || !x) return val[x];
    int m = l + r >> 1, ans = 0;
    if(ql <= m) ans = query(l, m, ql, qr, ls[x]);
    if(m < qr) ans += query(m + 1, r, ql, qr, rs[x]);
    return ans;
  }
}

using GSAM::fa;
using GSAM::len;
using GSAM::cnt;

int n, q, lg[N], w0, A, B, C = 1;
string str[N];
vector<int> pos[N], e[N];

int dn, dfn[N], dep[N], sz[N], mi[K][N];
void dfs(int id) {
  dfn[id] = ++dn, sz[id] = 1;
  mi[0][dn] = fa[id], dep[id] = dep[fa[id]] + 1;
  for(int it : e[id]) dfs(it), sz[id] += sz[it];
}
bool isa(int u, int v) {
  return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];
}
int get(int x, int y) {
  return dep[x] < dep[y] ? x : y;
}
int lca(int u, int v) {
  if(u == v) return u;
  if((u = dfn[u]) > (v = dfn[v])) swap(u, v);
  int d = lg[v - u++];
  return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}


int main() {
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> q >> w0;
  if(w0) cin >> A >> B >> C;
  for(int i = 1, lst = 1; i <= n; i++, lst = 1) {
    cin >> str[i], pos[i].resize(str[i].size());
    for(int j = 0; j < str[i].size(); j++) {
      lst = pos[i][j] = GSAM::ins(lst, str[i][j] - 'a');
    }
  }
  GSAM::build();
  for(int i = 2; i <= cnt; i++) e[fa[i]].push_back(i);
  for(int i = 2; i <= cnt; i++) lg[i] = lg[i >> 1] + 1;
  dfs(1), assert(cnt == dn);
  for(int i = 1; i <= lg[cnt]; i++) {
    for(int j = 1; j + (1 << i) - 1 <= cnt; j++) {
      mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
    }
  }

  for(int _ = 1, lst = 0; _ <= q; _++) {
    int op, x = (1ll * A * lst + B) % C;
    cin >> op;
    if(op == 1) {
      static char s[N];
      cin >> s + 1;
      int m = strlen(s + 1);
      if(w0) {
        for(int i = 1; i <= m; i++) {
          swap(s[i], s[x % m + 1]);
          x = (1ll * A * x + B) % C;
        }
      }
      static pair<int, int> P[N], Q[N];
      GSAM::path(s, m, P);
      sort(P, P + m, [&](auto a, auto b) {
        return a.fi != b.fi ? dfn[a.fi] < dfn[b.fi] : a.se < b.se;
      });
      int c = 0;
      for(int i = 0; i < m; i++) {
        while(c && isa(Q[c - 1].fi, P[i].fi)) c--;
        Q[c++] = P[i];
      }
      if(c == 1 && Q[0].fi == 1) continue;
      for(int i = 0; i < c; i++) {
        int id = Q[i].fi;
        BIT::add(dfn[fa[id]], 1);
        if(i) BIT::add(dfn[lca(fa[id], Q[i - 1].fi)], -1);
        SEG::modify(len[fa[id]] + 1, len[id], Q[i].se, SEG::R[id]);
      }
    }
    else {
      int p, l, r;
      cin >> p >> l >> r;
      if(w0) {
        p = (p + x) % n + 1;
        x = (1ll * A * x + B) % C;
        l = (l + x) % str[p].size() + 1;
        x = (1ll * A * x + B) % C;
        r = (r + x) % str[p].size() + 1;
        x = (1ll * A * x + B) % C;
        if(l > r) swap(l, r);
      }
      int L = r - l + 1;
      p = GSAM::locate(pos[p][r - 1], L);
      int ans = BIT::query(dfn[p], dfn[p] + sz[p] - 1);
      ans += SEG::query(len[fa[p]] + 1, len[p], L, len[p], SEG::R[p]);
      cout << (lst = ans) << "\n";
    }
  }

  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}

```

---

## 作者：Polaris_Australis_ (赞：11)

首先容易发现：$\max\limits_{i=1}^{l}(num(p,i,r))=num(p,l,r)$~~，所以这句话完全是唬人的~~。

## 做法一：hash

乱搞做法，不做讲解，分数不定。

## 做法二：AC 自动机（$l=1$）

考虑 $l=1$ 该怎么做，直接对所有模板串建出 AC 自动机和 fail 树，对于询问 $1$，直接在 AC 自动机上跑匹配，并把经过的所有节点存起来，并把这些节点到根的链的并打上 $+1$ 标记，这样询问 $2$ 的答案就是这个前缀串所代表的节点的标记和。

## 做法三：离线 SAM

现在变成了子串问题，容易想到广义后缀自动机，但是要把模板串和询问串一起建，原因会在下文解释。询问 $1$ 的处理方法和原来一样。询问 $2$ 先需要找到这个子串对应的节点，经典套路，在建广义 SAM 的时候记录 $ed[i][j]$ 表示 $S_i$ 的 $[1,j]$ 子串所对应的节点，然后倍增跳到 $dep[x]$ 最小的满足 $len[x]\ge(r-l+1)$ 的节点即可，然后查询节点标记和。

为什么要把模板串和询问串一起建？我们考虑只建模板串的情况，下面举一组例子：

### input

```
2 2
suffixtree
fixtree
1 tree
2 1 4 10
```

### output

```
0
```

这组样例的 `fixtree` 和 `tree` 这两个串如果不建询问串的话，所在节点完全相同，这样在跑匹配的时候，明明匹配的是 `tree`，但会把整个节点打上标记，导致查询 `fixtree` 的时候会查到 `tree` 的标记。

考虑模板串和询问串一起建广义 SAM 的正确性：对于某一组询问串，对于每一个 $r$，如果 $T_{l...r}$ 是它和模板串能匹配到的最长子串，所在节点为 $now$，设这一段是 $S_i$ 的 $[l',r']$ 子串，则 $S_i$ 的 $[l'-1,r']$ 一定由 $son[now]$ 表示，而不是和 $now$ 同属于一个节点。

## 做法四：在线 SAM

我们考虑一个数据结构，它是一棵树，它的每一个节点都只代表模板串的一种子串，一个节点所代表的子串是它的父亲节点所代表的子串前加一个字符形成的，我们容易发现，广义 SAM 的 parent tree 的每一个节点即是这个数据结构中的一条链。延续离线做法，我们把模板串建广义 SAM（拼在一起建 SAM 也可以），这时我们认为 SAM 的每一个节点所代表的都是上述数据结构中的一条链，之后我们希望给上述数据结构中的每个点一个 dfs 序，其实只需要遍历 SAM 即可，并定义 SAM 上一个点的“dfs 序”为它所代表的链的深度最大的点在数据结构上的 dfs 序。

对于询问 $1$，一样在 SAM 上跑匹配并记录匹配长度（具体的，如果没有当前要找的儿子则跳到父亲，并将当前长度更新为父亲的 $len$，跳到儿子的时候当前长度 $+1$），根据所记录的长度和所在节点的 $len$ 值及其“dfs 序”值，很容易求出其在上述数据结构中的 dfs 序值，按照实际的 dfs 序值做“树链的并”操作即可。由于这里 dfs 序是 $n^2$ 级别，所以需要使用动态开点线段树进行单点修改操作。

对于询问 $2$，也是倍增找到 SAM 上对应节点，再根据长度算出在数据结构中的 dfs 序，然后区间查询即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion{
typedef long long ll;
void main();
}
int main(){
	Wilson_Inversion::main();
	return 0;
}
namespace Wilson_Inversion{
const int N(1000010),M(100010);
int n,q,tot1(1),tot2(1),tot4(1);
ll tot3;
struct trienode{
	int son[26],p;
	vector<pair<int,int> >pos;
}trie[N>>1];
int son[N][26],fa[N][20],len[N],dep[N],rt(1),tr[30000010],ls[30000010],rs[30000010],w0,le[M];
ll st[N],edn[N];
int sta1[N],top,id[N];
ll sta2[N];
char s[N>>1];
vector<int>ed[M],e[N];
void ins(int x){
	int len(strlen(s+1)), now(1);
	ed[x].resize(len + 1, 0);
	for (int i(1); i <= len; ++i) {
		int op(s[i] - 'a');
		if (!trie[now].son[op]) trie[now].son[op] = ++tot1;
		now = trie[now].son[op];
		trie[now].pos.push_back(make_pair(x, i));
	}
}
void insert(int x, int y, int& z) {
	int p(y);
	int np(z = ++tot2);
	len[np]=len[p]+1;
	while (p && (!son[p][x])) {
		son[p][x] = np;
		p = fa[p][0];
	}
	if (!p)
		fa[np][0]=1;
	else {
		int q(son[p][x]);
		if (len[q] == len[p] + 1)
			fa[np][0] = q;
		else {
			int nq(++tot2);
			memcpy(son[nq], son[q], sizeof(son[q]));
			fa[nq][0]=fa[q][0];
			len[nq]=len[p]+1;
			fa[q][0]=fa[np][0]=nq;
			while (p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p][0];
			}
		}
	}
}
void bfs() {
	queue<int> q;
	q.push(1);
	trie[1].p = 1;
	while (!q.empty()) {
		int u(q.front());
		q.pop();
		for (auto i : trie[u].pos) {
			ed[i.first][i.second] = trie[u].p;
		}
		for (int i(0); i < 26; ++i) {
			if (trie[u].son[i]) {
				insert(i, trie[u].p, trie[trie[u].son[i]].p);
				q.push(trie[u].son[i]);
			}
		}
	}
}
void dfs(int x) {
	tot3+=(len[x]-len[fa[x][0]]);
	st[x] = tot3;
	for (int i(1); i <= 19; ++i) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i : e[x]) {
		dep[i] = dep[x] + 1;
		dfs(i);
	}
	edn[x] = tot3;
}
void pp(){
	int now(1),nowlen(0),l(strlen(s+1));
	for(int i(1);i<=l;++i){
		int op(s[i]-'a');
		while(!son[now][op]){
			now=fa[now][0];
			nowlen=len[now];
		}
		now=son[now][op];
		++nowlen;
		if(now==1)continue;
		sta1[++top]=now;
		sta2[top]=st[now]-(len[now]-nowlen);
		id[top]=top;
	}
}
int lcadfs(int x,int xdfs,int y,int ydfs){
	if(x==y)return min(xdfs,ydfs);
	if(dep[x]<dep[y])swap(x,y),swap(xdfs,ydfs);
	for(int i(19);~i;--i){
		if(dep[fa[x][i]]<dep[y])continue;
		x=fa[x][i];
	}
	if(x==y)return ydfs;
	for(int i(19);~i;--i){
		if(fa[x][i]==fa[y][i])continue;
		x=fa[x][i],y=fa[y][i];
	}
	return st[fa[x][0]];
}
pair<ll,ll> find(int p,int l,int r){
	int now(ed[p][r]),tlen(r-l+1);
	for(int i(19);~i;--i){
		if(len[fa[now][i]]>=tlen)now=fa[now][i];
	}
	return make_pair(st[now]-(len[now]-tlen),edn[now]);
}
void modify(int &x,ll l,ll r,ll pos,int num){
	if(l==1ll&&r==tot3){
		++l,--l;
	}
	if(!x)x=++tot4;
	tr[x]+=num;
	if(l==r)return;
	ll mid((l+r)>>1);
	if(pos<=mid)modify(ls[x],l,mid,pos,num);
	else modify(rs[x],mid+1,r,pos,num);
}
int query(int x,ll l,ll r,ll L,ll R){
	if(L<=l&&r<=R)return tr[x];
	if(!x)return 0;
	ll mid((l+r)>>1);
	int res(0);
	if(L<=mid)res+=query(ls[x],l,mid,L,R);
	if(R>mid)res+=query(rs[x],mid+1,r,L,R);
	return res;
}
bool cmp(int x,int y){
	return sta2[x]<sta2[y];
}
void main(){
	scanf("%d%d%d",&n,&q,&w0);
	int A,B,C;
	if(w0){
		scanf("%d%d%d",&A,&B,&C);
	}
	for(int i(1);i<=n;++i){
		scanf("%s",s+1);
		le[i]=strlen(s+1);
		ins(i);
	}
	bfs();
	dep[1]=1;
	for(int i(2);i<=tot2;++i)e[fa[i][0]].push_back(i);
	for(int i(0);i<26;++i)son[0][i]=1;
	len[0]=-1;
	dfs(1);
	int lst(0);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			scanf("%s",s+1);
			if(w0==1){
				int x((1ll*A*lst+B)%C),l(strlen(s+1));
				for(int i(1);i<=l;++i){
					swap(s[i],s[x%l+1]);
					x=(1ll*A*x+B)%C;
				}
			}
			top=0;
			pp();
			sort(id+1,id+1+top,cmp);
			modify(rt,1ll,tot3,sta2[id[1]],1);
			for(int i(2);i<=top;++i){
				modify(rt,1ll,tot3,sta2[id[i]],1);
				modify(rt,1ll,tot3,lcadfs(sta1[id[i-1]],sta2[id[i-1]],sta1[id[i]],sta2[id[i]]),-1);
			}
		}else{
			int p,l,r;
			scanf("%d%d%d",&p,&l,&r);
			if(w0==1){
				int x((1ll*A*lst+B)%C);
				p=(p+x)%n+1;
				x=(1ll*A*x+B)%C;
				l=(l+x)%le[p]+1;
				x=(1ll*A*x+B)%C;
				r=(r+x)%le[p]+1;
				if(l>r)swap(l,r);
			}
			pair<ll,ll>t(find(p,l,r));
			printf("%d\n",lst=query(1,1ll,tot3,t.first,t.second));
		}
	}
}
}
```


---

## 作者：EnofTaiPeople (赞：6)

### Part1 前言

认识到自己才疏学浅，开始学习算法并认真记录。

我之前的 SAM 相关文章大多只写到了后缀接受理论和 parent 树 LCA 的相关技巧，但本题需要考虑到 parent 树边的实际含义，也可以通过反串后缀树来进一步理解，相比与之前要复杂很多。

虽然对大多数人看来是板子，但我之前确实不会。

### Part2 问题引入

[题目链接](https://www.luogu.com.cn/problem/P8947)

给定字符串序列 $s_i$，字符串集合 $T$（初始为空），**在线**进行 $q$ 组询问。

询问 $1$ 向集合 $T$ 加入新的字符串 $t_i$；

询问 $2$ 给定 $p,l,r$，设 $f(p,l,r)$ 表示 $s_p$ 的子串区间 $[l,r]$ 在集合 $T$ 的多少个字符串中**出现过**，求 $\max\limits_{i=1}^lf(p,i,r)$。

容易发现 $\forall i < j\le r,f(p,i,r)\le f(p,j,r)$，所以相当于求 $f(p,l,r)$。

### Part3 对模式串的处理

对 $s_i$ 建广义后缀自动机，也可以拼接之后建后缀自动机，我们尝试去表示一个字符串区间。

对于一个字符串区间 $s_{x,[l,r]}$，我们可以先找到 $s_{x,[1,r]}$ 所对应的自动机节点 $y$。

设 $f_x$ 表示 $x$ 在 parent 树上的父亲，$len_x$ 表示 $x$ 所对应 endpos 等价类的最长串长度。

我们发现如果有 $len_{f_y}\ge r-l+1$，就可以让 $y$ 跳到它的父亲，这样我们就能够找到该串所对应的 endpos 等价类。

这时可以尝试使用一个二元组 $(x,k)$ 表示节点 $x$ 等价类中长度为 $k$ 的字符串来表示询问的模式串。

### Part4 对文本串的处理

考虑表示出来 $t_i$ 在后缀自动机上能接受的所有子串。

找到 $t_i$ 的每一个前缀在后缀自动机上的位置，注意这里不一定能够保留完整的前缀，而且我们依旧需要记录二元组 $(x,k)$ 来表示这些前缀。

这里可以看作将一条 parent 树上的边 $(x,f_x)$ 分成了 $len_x-len_{f_x}$ 段，每个二元组都能通过边上的点得到表示。

我们可以认为一个节点所对应的字符串是该串的子串当且仅当该节点子树内包含该串某一个前缀所代表的节点。

于是我们变成了对于一些点集到根链的节点并加一，这类问题可以使用一类容斥差分办法，即先全部到根链加，然后 dfn 相邻的节点 LCA 到根链减即可。

到根链加单点查可以直接转换为单点加子树查，即单点加区间查，于是可以做到 $O(n\log n)$。

### Part5 对深搜序的处理

注意到上面将一条边分成若干段导致了点数是 $O(n^2)$ 的，在深搜时用 $dfn_x=cnt+len_x-len_{f_x}$ 可以计算出 $dfn$，这样只需要使用动态开点的线段树就能做出这道题，因为子树所包含的区间依旧可以轻松求出来。

不过实际实现时为了避免 `long long` 的计算和减少常数可以在整点上用树状数组维护，虚点的统计只会贡献到自己这条边上，这样对于每一条边都开一棵动态开点线段树即可，这里为了减少细节可以先将存在包含关系的祖先使用单调栈弹掉，这样实点的 LCA 就等于虚点的 LCA 了。

无论使用什么做法，时间复杂度总是 $O((\sum|s_i|+\sum|t_i|+q)\log\sum|s_i|+\sum|s_i||\Sigma|)$ 的，空间 $O(\sum|s_i|(\log\sum|s_i|+|\Sigma|))$。

### Part6 与后缀树的关系

我们发现一条边中间能够裂开许多虚点对一个自动机来说很不自然。

首先从自动机的角度来看就是一个 endpos 等价类有多大这条边就有多长。

但这实质上是反串的后缀树，也就是将反串的所有后缀插到 Trie 上压缩之后的结果。

然后我们发现 SAM 上的跳 parent 的效果是保留后缀，删除前缀，恰好对应反串的后缀树上的删除后缀。

于是这样我们能够更加容易地表示出一个字符串与 SAM 所对应的字符串之间的关系。

给出本题代码以及注释：

```cpp
#include<icecream>
int T,n,m,K,tp,A,B,C,t[N][26],cnt=1,lst=1,ln[N],f[N],ans;
int dt,dfn[N]实点深搜序,low[N],dlt,de[N],g[N],ct[N],b[N];
vt lk[N],h[100005];parent 树边、模式串前缀所对应节点。
void ins(int p){建立广义 SAM，也可以使用顺序拼接的 SAM。
    int tg=0;
    if(t[lst][p]){
        if(ln[t[lst][p]]==ln[lst]+1){
            lst=t[lst][p];return;
        }else tg=1;
    }int x=++cnt,y,z,r;ln[x]=ln[lst]+1;
    for(y=lst;y&&!t[y][p];y=f[y])t[y][p]=x;
    if(!y)f[x]=1;
    else if(ln[z=t[y][p]]==ln[y]+1)f[x]=z;
    else{
        ln[r=++cnt]=ln[y]+1;
        memcpy(t[r],t[z],sizeof(t[r])),f[r]=f[z];
        while(y&&t[y][p]==z)t[y][p]=r,y=f[y];
        f[x]=f[z]=r;
    }lst=tg?r:x;
}
string s[N];
struct dat{
    int x,k;
    bool operator<(const dat &z)const{
        return x==z.x?k>z.k:dfn[x]>dfn[z.x];
    }
}d[N];
void dfs(int x){
    if(de[g[f[x]]]<<1==de[f[x]]+de[g[g[f[x]]]])g[x]=g[g[f[x]]];
    else g[x]=f[x];
    dfn[x]=++dlt;
    for(int y:lk[x])de[y]=de[x]+1,dfs(y);
    low[x]=dlt;
}
int lca(int x,int y){
    if(de[x]<de[y])swap(x,y);
    while(de[x]>de[y])
        x=de[g[x]]<de[y]?f[x]:g[x];
    while(x!=y){
        if(g[x]==g[y])x=f[x],y=f[y];
        else x=g[x],y=g[y];
    }
    return x;
}
void upd(int x,int k){树状数组维护实点贡献。for(x=dfn[x];x<=cnt;x+=x&-x)ct[x]+=k;}
namespace ZYFDNSGT{（动态开点线段树，区间为 [ln[f[x]]+1,ln[x]])）
    int t[T][2],sm[T],cnt;
#define ls t[x][0]
#define rs t[x][1]
    void cg(int &x,int l,int r,int p){
        if(!x)x=++cnt;++sm[x];
        if(l<r){
            int md=l+r>>1;
            if(p>md)cg(rs,md+1,r,p);
            else cg(ls,l,md,p);
        }
    }
    void ask(int x,int l,int r,int L,int R){
        if(!x)return;
        if(l>=L&&r<=R){ans+=sm[x];return;}
        int md=l+r>>1;
        if(L<=md)ask(ls,l,md,L,R);
        if(md<R)ask(rs,md+1,r,L,R);
    }
}
int in(int x,int y){是否在子树内。return dfn[x]>=dfn[y]&&dfn[x]<=low[y];}
int main(){
    int i,j,k,l,r,x,y,z;
    cin>>n>>T>>tp;
    for(i=1;i<=n;++i){
        cin>>s[i],lst=1;
        for(char c:s[i])ins(c-'a');
    }
    for(x=2;x<=cnt;++x)lk[f[x]].push_back(x);
    for(i=1;i<=n;++i){
        h[i]={x=1};
        for(char c:s[i])
            h[i].push_back(x=t[x][c-'a']);
    }
    de[1]=1,dfs(1);
    while(T--){
        cin>>k;
        if(k==1){
            string s;cin>>s,k=s.size();
            x=1,r=dt=0;
            for(i=0;i<k;++i){
                l=s[i]-'a';找到每个前缀所对应的二元组。
                while(x&&!t[x][l])r=ln[x=f[x]];
                if(!x){x=1;continue;}
                d[++dt]={x=t[x][l],++r};
            }
            if(!dt)continue;
            sort(d+1,d+dt+1);
            for(i=1,r=dt,dt=0;i<=r;++i)弹掉包含的祖先。
                if(!(dt&&in(d[dt].x,d[i].x)))d[++dt]=d[i];
            for(i=1;i<=dt;++i){
                upd(f[x=d[i].x],1);
                ZYFDNSGT::cg(b[x],ln[f[x]]+1,ln[x],d[i].k);
            }
            for(i=1;i<dt;++i){容斥掉相邻的 LCA。
                x=lca(d[i].x,d[i%dt+1].x);
                upd(x,-1);
            }
        }else{
            cin>>x>>l>>r;
            x=h[x][r],r=r-l+1;
            while(ln[f[x]]>=r)倍增跳到所在节点。
                if(ln[f[g[x]]]>r)x=g[x];
                else x=f[x];
            ans=0;
            for(i=low[x];i;i-=i&-i)ans+=ct[i];实点贡献。
            for(i=dfn[x]-1;i;i-=i&-i)ans-=ct[i];
            ZYFDNSGT::ask(b[x],ln[f[x]]+1,ln[x],r,ln[x]);虚边贡献查询。
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：Mirasycle (赞：1)

基本思路不难，但是代码量巨大。

由于 $T$ 是动态加入的且要求在线，所以不能离线从 $T$ 角度考虑对于 $S$ 的贡献，也就无法使用 AC 自动机了。对于考虑直接从 $S$ 的子串角度计算答案，因为需要建立广义 SAM。

本题需要知道的就是一个串在其 link 树上的子树内的所有 endpos 集合内出现。

对于 $S$ 串建立广义 SAM 之后，动态加入 $T$ 的时候，就让 $T$ 在 GSAM 上顺着转移边行走，如果失配就跳 fail，并且维护匹配长度。

一个 $S$ 中的串在当前这个 $T$ 中出现，需要满足 $T$ 的某个状态存在于 $S$ 的子树内（不包含本身节点），或者经过了本身节点且匹配长度大于当前串长。

第一个贡献形式是子树数点，第二种贡献形式就是对于每个点开一个动态开点线段树维护其每种长度被贡献次数。但是注意一个 $T$ 只能贡献一次，所以需要去重。考虑提取出 $T$ 在 GSAM 上行走经过点构成的虚树，只保留虚树的叶子节点（否则子孙关系会重复贡献），对于叶子节点可能被 $T$ 多次经过，保留最长的匹配长度在线段树上进行贡献。注意到两个叶子会产生重复贡献，也就是他们 $\rm LCA$ 以及 $\rm LCA$ 祖先这一段。于是我们按照 $\rm DFS$ 序排序之后对于相邻点在其 $\rm LCA$ 处差分一下就行了。

时间复杂度单 $\log$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=1e6+10;
const int maxlog=20;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
char s[maxn]; int rt[maxn],le[maxn],n,m,w0;
int dfn[maxn],sz[maxn],vis[maxn],tim;
vector<int> G[maxn],to[maxn],node;
vector<pii> vec[maxn],h;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct BIT{
	int c[maxn],up;
	int lowbit(int x){ return x&-x; }
	void modify(int x,int v){ for(;x<=up;x+=lowbit(x)) c[x]+=v; }
	int query(int x){ int res=0; for(;x;x-=lowbit(x)) res+=c[x]; return res; }
	int sum(int l,int r){ return query(r)-query(l-1); }
}t;
struct SegmentTree{
	#define mid ((l+r)>>1)
	int val[maxn<<5],ls[maxn<<5],rs[maxn<<5],tot;
	void pushup(int p){ val[p]=val[ls[p]]+val[rs[p]]; }
	void modify(int &p,int l,int r,int x,int v){
		if(!p) p=++tot;
		if(l==r){ val[p]+=v; return ; }
		if(x<=mid) modify(ls[p],l,mid,x,v);
		else modify(rs[p],mid+1,r,x,v);
		pushup(p);
	}
	int query(int p,int l,int r,int ql,int qr){
		if(!p) return 0; 
		if(ql<=l&&r<=qr) return val[p];
		if(qr<=mid) return query(ls[p],l,mid,ql,qr);
		if(ql>mid) return query(rs[p],mid+1,r,ql,qr);
		else return query(ls[p],l,mid,ql,qr)+query(rs[p],mid+1,r,ql,qr);
	}
}seg;
struct Trie{
	int ch[maxn][27],c[maxn],fa[maxn],tot=1;
	void ins(char s[],int id){
		int u=1; int n=strlen(s+1);
		for(int i=1;i<=n;i++){
			int x=s[i]-'a';
			if(!ch[u][x]){ ch[u][x]=++tot; fa[tot]=u; c[tot]=x; }
			u=ch[u][x]; vec[u].pb(id,i);
		}
	}
}trie;
struct SAM{
	int ch[maxn][27],dep[maxn],len[maxn],fa[maxn],mat[maxn];
	int pos[maxn],pa[maxlog][maxn],PA[maxlog][maxn],lg[maxn],D,tot; 
	int add(int c,int last,vector<pii> &ID){
		int p=last; int np=++tot; len[np]=len[p]+1;
		for(auto z:ID) to[z.fi][z.se]=tot;
		for(;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;
		if(!p) fa[np]=1;
		else{
			int q=ch[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else{
				int nq=++tot; memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q]; len[nq]=len[p]+1; fa[q]=fa[np]=nq;
				for(;p&&ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
			}
		}
		return np;
	}
	void dfs(int u,int father){
		PA[0][dfn[u]=++tim]=father; sz[u]=1;
		for(auto v:G[u]){
			dep[v]=dep[u]+1;
			dfs(v,u); sz[u]+=sz[v];
		}
	}
	int cmp(int x,int y){ return dfn[x]<dfn[y]?x:y; }
	int lca(int u,int v){
		if(u==v) return u;
		u=dfn[u]; v=dfn[v];
		if(u>v) swap(u,v);
		u++; int k=lg[v-u+1];
		return cmp(PA[k][u],PA[k][v-(1<<k)+1]);
	}
	void init(){
		dfs(1,0);
		for(int k=1;(1<<k)<=tot;k++)
			for(int i=1;i+(1<<k)-1<=tot;i++)
				PA[k][i]=cmp(PA[k-1][i],PA[k-1][i+(1<<k-1)]);
	}
	void walk(char t[]){
		int n=strlen(t+1),u=1,L=0; h.clear();
		for(int i=1;i<=n;i++){
			int c=t[i]-'a';
			if(ch[u][c]) u=ch[u][c],++L;
			else{
				while(u&&!ch[u][c]) u=fa[u];
				if(u) L=len[u]+1,u=ch[u][c];
				else L=0,u=1;
			}
			if(u!=1) h.pb(u,L);
		}
	}
	void build(){
		queue<int> q; tot=1; pos[1]=1;
		for(int i=0;i<26;i++)
			if(trie.ch[1][i]) q.push(trie.ch[1][i]);
		while(!q.empty()){
			int x=q.front(); q.pop();
			pos[x]=add(trie.c[x],pos[trie.fa[x]],vec[x]);
			for(int i=0;i<26;i++)
				if(trie.ch[x][i]) q.push(trie.ch[x][i]);
		}
		for(int i=2;i<=tot;i++) G[fa[i]].pb(i);
		dep[1]=1; init(); lg[1]=0; t.up=tot;
		for(int i=2;i<=tot;i++) lg[i]=lg[i>>1]+1;
		for(int i=2;i<=tot;i++) pa[0][i]=fa[i];
		for(int k=1;(1<<k)<=tot;k++)
			for(int i=1;i<=tot;i++)
				pa[k][i]=pa[k-1][pa[k-1][i]];
	}
	int solve(int id,int l,int r){
		int L=r-l+1,u=to[id][r];
		if(u==1) return 0;
		for(int k=lg[dep[u]];k>=0;k--){
			int v=pa[k][u];
			if(v<=1) continue;
			if(L<=len[v]) u=v;
		}
		return seg.query(rt[u],1,len[u],L,len[u])+t.sum(dfn[u],dfn[u]+sz[u]-1);
	}
}sam; int A,B,C,lst,q;
bool cmp(pii x,pii y){ return dfn[x.fi]>dfn[y.fi]||(x.fi==y.fi&&x.se>y.se); }
int main(){
	cin>>n>>q>>w0; if(w0) cin>>A>>B>>C;
	for(int i=1;i<=n;i++){
		cin>>(s+1); trie.ins(s,i); 
		le[i]=strlen(s+1); 
		to[i].resize(le[i]+1);
	}
	sam.build();
	while (q--){
		int op; op=read();
		if(op==1){
			scanf("%s",s+1);
			if(w0){
				int x((1ll * A * lst + B) % C), l(strlen(s + 1));
				for (int i(1); i <= l; ++i) {
					swap(s[i], s[x % l + 1]);
					x = (1ll * A * x + B) % C;
				}
			}
			sam.walk(s); int lst=sam.tot+1;
			sort(h.begin(),h.end(),cmp); node.clear();
			for(auto z:h){
				int u=z.fi; 
				if(lst<=dfn[u]+sz[u]-1||vis[u]) continue;
				seg.modify(rt[u],1,sam.len[u],z.se,1);
				lst=dfn[u]; vis[u]=1; node.pb(u);
			} lst=0;
			for(auto u:node){
				if(lst) t.modify(dfn[sam.lca(lst,sam.fa[u])],-1); 
				t.modify(dfn[sam.fa[u]],1); lst=u;
			}
			for(auto z:h) vis[z.fi]=0;
		}else{
			int p,l,r; p=read(); l=read(); r=read();
			if(w0){
				int x((1ll * A * lst + B) % C);
				p = (p + x) % n + 1;
				x = (1ll * A * x + B) % C;
				l = (l + x) % le[p] + 1;
				x = (1ll * A * x + B) % C;
				r = (r + x) % le[p] + 1;
				if (l > r) swap(l, r);
			}
			lst=sam.solve(p,l,r);
			printf("%d\n",lst);
		}
	}
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

套路题。

题面里非常搞笑的一点是 $\max\limits_{1\le i\le l}(num(p,i,r))=num(p,l,r)$，所以我们只需要求 $num(p,l,r)$ 就行了。

发现强制在线而大多数字符串结构难以做到动态维护比较复杂的信息，于是猜测做法必然是考察询问串对模板串的贡献。

因为要定位模板串的一个子串来计算答案，所以合理猜测需要使用后缀结构，这里采用 GSAM。

将所有模板串丢进 trie 里建出 GSAM，那么每个模板串的每一个子串都对应着 GSAM 上的一个节点。如果你不会定位一个子串对应的节点，我后面再讲。

我们考虑在之上刻画询问串 $T$ 对一个节点造成贡献的充要条件。

我们拿出 $T$ 在 GSAM 上面遍历，使用类似 SP1812 的遍历方式，称一个节点 $x$ 为关键点当且仅当 $x$ 被遍历过，同时记录 $x$ 被经过时 $T$ 的匹配长度，请注意**如果一个节点被经过多次你应该保留最长的一次的长度**。

那么 $T$ 会对一个子串 $S$ 造成贡献当且仅当满足一下两个条件之一（下称 $S$ 在 GSAM 对应的节点为 $p$）：
+ $p$ 在 parent tree 上的子树（不包括 $p$）里有关键点。
+ $p$ 是关键点且 $|S|$ 小于等于匹配长度。

第一个条件可以用树状数组解决，具体来讲相当于每一个关键点到根的路径取并之后将在路径并里的点权值加一，可以用虚树刻画，不过你并没有必要真的建出来。

第二个条件可以对每一个点单独开一棵动态开点线段树。

并不卡常且代码较为好写。

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)

using namespace std;
bool st;

const int N=1e6+10,K=20;
int n,q,w0,dep[N],top[N],siz[N],son[N],father[N],id[N],idx,f[N][K+1],TOT,cnt,lenth[N],A,B,C,res[N],flag[N];
vector < int > v[N],rev[N];string in;

struct TreeArray{
	int tr[N];inline int lowbit(const int &x){return x&(-x);}
	inline void add(int i,int x){for(;i<=TOT;i+=lowbit(i)) tr[i]+=x;}
	inline int ask(int i){int res=0;for(;i;i-=lowbit(i)) res+=tr[i];return res;}
	inline int ask(int l,int r){return ask(r)-ask(l-1);}
}t,chk;
struct Node{//内存池 
	int l,r,sum;
	#define ls(k) tr[k].l
	#define rs(k) tr[k].r
	#define sum(k) tr[k].sum
}tr[N*22];
struct segment{
	int rt[N],n;
	void ins(int &now,int l,int r,int to){
		if(!now) now=++cnt;
		--sum(now);if(l==r) return ;
		(mid>=to)?ins(ls(now),l,mid,to):ins(rs(now),mid+1,r,to);
	}
	int query(int now,int l,int r,int x,int y){
		if(!now||x>y||x>r||y<l) return 0;
		if(x<=l&&r<=y) return sum(now);
		return query(ls(now),l,mid,x,y)+query(rs(now),mid+1,r,x,y);
	}
	inline void ins(int x,int v){ins(rt[x],1,n,v);}
	inline int ask(int x,int l){return query(rt[x],1,n,1,l-1);}
}s;

void dfs1(int x,int y){
	siz[x]=1;dep[x]=dep[f[x][0]=father[x]=y]+1;for(int i=1;i<=K;++i) f[x][i]=f[f[x][i-1]][i-1];
	for(int i:v[x]){dfs1(i,x);siz[x]+=siz[i];(siz[son[x]]<siz[i])&&(son[x]=i);}
}
void dfs2(int x,int topf){
	top[x]=topf;id[x]=++idx;if(son[x]) dfs2(son[x],topf);
	for(int i:v[x]) if(i!=son[x]) dfs2(i,i);
}
inline int LCA(int x,int y){
	while(top[x]!=top[y]) dep[top[x]]>dep[top[y]]?x=father[top[x]]:y=father[top[y]];
	return dep[x]<dep[y]?x:y; 
}
inline int ask(int x,int len){return t.ask(id[x],id[x]+siz[x]-1)+s.ask(x,len);}
inline void add(int x,int y){t.add(id[x],1);t.add(id[y],1);int z=LCA(x,y);t.add(id[z],-2);}

struct GSAM{
	struct node{
		int ch[26],len,fa;
		#define ch(k,i) tr[k].ch[i]
		#define len(k) tr[k].len
		#define fa(k) tr[k].fa 
	}tr[N];
	int now=1,tot=1,son[N][26],pos[N],T;
	queue < int > Q;
	inline void insert(string &s,int id){
		int now=0;rev[id].emplace_back(0);
		for(char x:s){
			int to=x-'a';
			if(!son[now][to]) son[now][to]=++T;
			now=son[now][to];rev[id].emplace_back(now);
		}
	}
	inline int ins(int x,int p){
		len(now=++tot)=len(p)+1;
		for(;p&&!ch(p,x);p=fa(p)) ch(p,x)=now;
		if(!p) fa(now)=1;
		else {
			int to=ch(p,x);
			if(len(to)==len(p)+1) fa(now)=to;
			else {
				tr[++tot]=tr[to];
				len(tot)=len(p)+1;
				fa(now)=fa(to)=tot;
				for(;p&&ch(p,x)==to;p=fa(p)) ch(p,x)=tot;
			}
		}
		return now;
	}
	inline void BFS(){
		pos[0]=1;Q.push(0);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
	 		for(int i=0;i<26;++i) if(son[x][i]){pos[son[x][i]]=ins(i,pos[x]);Q.push(son[x][i]);}
		}
		TOT=tot;s.n=5e5;
		for(int i=2;i<=tot;++i) v[fa(i)].emplace_back(i);
		dfs1(1,0);dfs2(1,1);
	}
}g;

inline int Jump(int id,int l,int r){//查询 
	int len=r-l+1,x=g.pos[rev[id][r]];
//	cout<<x<<' ';
	for(int i=K;~i;--i) if(g.len(f[x][i])>=len) x=f[x][i];
//	cout<<x<<' '<<g.len(x)<<' '<<len<<'\n';
	return ask(x,len);
}
inline void upd(vector<int> &d){
	for(auto x:d) if(flag[x]){chk.add(id[x],1);flag[x]=0;}
	for(auto x:d){
		if(res[x]&&chk.ask(id[x],id[x]+siz[x]-1)==1) s.ins(x,res[x]);
		res[x]=0;
	}
	for(auto x:d) if(!flag[x]){chk.add(id[x],-1);flag[x]=1;}
	d.emplace_back(1);sort(d.begin(),d.end(),[](const int x,const int y){return id[x]<id[y];});
	d.erase(unique(d.begin(),d.end()),d.end());int len=d.size();
	for(int i=1;i<len;++i) d.emplace_back(LCA(d[i],d[i-1]));
	sort(d.begin(),d.end(),[](const int x,const int y){return id[x]<id[y];});
	d.erase(unique(d.begin(),d.end()),d.end());len=d.size();t.add(id[d[0]],1);
	for(int i=1;i<len;++i){t.add(id[LCA(d[i],d[i-1])],-1);t.add(id[d[i]],1);} 
}
inline void Change(string &S){
	vector<int> d;
	int n=S.size(),now=1,len=0;
	for(int i=0;i<n;++i){
		int to=S[i]-'a';
		if(g.ch(now,to)){
			now=g.ch(now,to);
			++len;
		}else {
			while(now&&!g.ch(now,to)) now=g.fa(now);
			if(!now){now=1,len=0;continue;}
			else {len=g.len(now)+1;now=g.ch(now,to);}
		}
		d.emplace_back(now);res[now]=max(res[now],len);
		flag[now]=1;
	}
	upd(d);
}
bool ed;

inline void Solve0(){
//	cout << "----\n"
	while(q--){
		int op;cin>>op;
		if(op==1){cin>>in;Change(in);}
		else {int p,l,r;cin>>p>>l>>r;cout<<Jump(p,l,r)<<'\n';}
	}
}
inline void Solve1(){
	int lst=0;
	while (q--) {
		int op;cin>>op;
		int x=(1ll*A*lst+B)%C;
		if (op == 1) {
			cin>>in;int l=in.size();
			for(int i=1;i<=l;++i){swap(in[i-1],in[x%l]);x=(1ll*A*x+B)%C;}
			Change(in);
//			int x((1ll * A * lst + B) % C), l(strlen(s + 1));
//			for (int i(1); i <= l; ++i) {
//				swap(s[i], s[x % l + 1]);
//				x = (1ll * A * x + B) % C;
//			}
		} else {
			int p,l,r;cin>>p>>l>>r;
			p=(p+x)%n+1;
			x=(1ll*A*x+B)%C;
			l=(l+x)%lenth[p]+1;
			x=(1ll*A*x+B)%C;
			r=(r+x)%lenth[p]+1;
			if(l>r) swap(l,r);
			// 此处更新 lst
			cout<<(lst=Jump(p,l,r))<<'\n';
		}
	}
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q>>w0;if(w0) cin>>A>>B>>C;
	for(int i=1;i<=n;++i){cin>>in;g.insert(in,i);lenth[i]=in.size();}g.BFS();
	w0?Solve1():Solve0();
	cerr<<(&st-&ed)/1048576.0<<" MB\n";
	  	return 0;
}
```

---

