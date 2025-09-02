# Mike and Friends

## 题目描述

What-The-Fatherland is a strange country! All phone numbers there are strings consisting of lowercase English letters. What is double strange that a phone number can be associated with several bears!

In that country there is a rock band called CF consisting of $ n $ bears (including Mike) numbered from $ 1 $ to $ n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547E/795f636f6e5e68bda106d7b6f30ea579c783740e.png)Phone number of $ i $ -th member of CF is $ s_{i} $ . May 17th is a holiday named Phone Calls day. In the last Phone Calls day, everyone called all the numbers that are substrings of his/her number (one may call some number several times). In particular, everyone called himself (that was really strange country).

Denote as $ call(i,j) $ the number of times that $ i $ -th member of CF called the $ j $ -th member of CF.

The geek Mike has $ q $ questions that he wants to ask you. In each question he gives you numbers $ l,r $ and $ k $ and you should tell him the number

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547E/a85d82cd6a7515cf5b34f6817bb4ac822d627734.png)

## 样例 #1

### 输入

```
5 5
a
ab
abab
ababab
b
1 5 1
3 5 1
1 5 2
1 5 3
1 4 5
```

### 输出

```
7
5
6
3
6
```

# 题解

## 作者：zhoukangyang (赞：25)

欢迎来蒟蒻的博客园看蒟蒻的[AC自动机练习笔记 ](https://www.cnblogs.com/zkyJuruo/p/13464007.html)

首先建立$AC$自动机,建立 $fail$ 树。

寻问 $s_k$ 在 $s_l .. s_r$ 中出现几次, 拆分成 $s_k$ 在 $s_1 ...  s_r$ 中出现的次数 减 $s_k$ 在 $s_1 ...  s_r$ 中出现的次数,离线查询。

在建立完 $Fail$ 树之后, 一个一个插入字符串。插入字符串 $s_m$ 时将字符串 $s_m$ 的每一个前缀对应状态的答案增加一。

插入完解决对于任意 $k$, $s_k$ 在 $s_1 ... s_m$ 中出现的次数, 由于在 $s_k$ 的子树中的状态所对于的字符串都包含 $s_k$, 所以只需要查询 $Fail$ 树上的子树答案和就行了。

如何快速得到这一个答案? $dfs$ 序 + 树状数组即可。

时间复杂度 $(|S| + q) log_2|S|$, $|S| = \sum\limits_{i = 1}^{n}|S_i|$

Code:
```cpp
#include<bits/stdc++.h>
#define N 210000
#define M 510000
using namespace std;
int lowbit(int x) {return x & -x;}
int n, Q, ans[N], ch[N][26], fa[N], fail[N], tot, uid[N], siz[N], cnt;
long long szsz[N];
void add(int x, int val) {
	if(x == 0) return;
	while(x <= cnt) szsz[x] += val,x += lowbit(x);
}
int qzh(int x) {
	int Ans = 0;
	for(int i = x; i; i -= lowbit(i)) Ans += szsz[i];
	return Ans;
}
int head[N], last[N];
struct node {
	int to, next;
} e[N];
int edge_id;
void add_edge(int u, int v) {
	++edge_id;
	if(!head[u]) head[u] = edge_id;
	else e[last[u]].next = edge_id;
	e[edge_id].to = v, last[u] = edge_id;
}
void ins(char *f, int len, int id) {
	int now = 0;
	for(int i = 0; i < len; i++) {
		if(!ch[now][f[i] - 'a']) ch[now][f[i] - 'a'] = ++tot, fa[tot] = now;
		now = ch[now][f[i] - 'a'];
	}
	ans[id] = now;
}
void bfs() {
	queue<int> q; 
	for(int i = 0; i < 26; i++) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = 0; i < 26; i++) {
			int v = ch[u][i];
			if(!v) ch[u][i] = ch[fail[u]][i];
			else fail[v] = ch[fail[u]][i], q.push(v);
		}
	}
}
void dfs(int x) {
	uid[x] = ++cnt, siz[x] = 1;
	for(int i = head[x]; i; i = e[i].next) dfs(e[i].to), siz[x] += siz[e[i].to];
} 
void build() {
	for(int i = 1; i <= tot; i++) add_edge(fail[i], i);
	dfs(0);
} 
struct ask {
	int x, cx, id, flag;
	long long ans;
} q[M << 1];
bool cmp(ask aa, ask bb) {
	return aa.x < bb.x;
}
bool pmc(ask aa, ask bb) {
	return aa.id == bb.id ? aa.flag < bb.flag : aa.id < bb.id; 
}
char s[N];
int mian() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		ins(s, strlen(s), i);
	}
	bfs(), build();
	for(int i = 1; i <= Q; i++) {
		scanf("%d", &q[i * 2 - 1].x), q[i * 2 - 1].x--;
		scanf("%d", &q[i * 2].x);
		scanf("%d", &q[i * 2].cx), q[i * 2 - 1].cx = q[i * 2].cx;
		q[i * 2 - 1].id = q[i * 2].id = i;
		q[i * 2 - 1].flag = -1, q[i * 2].flag = 1;
	}
	sort(q + 1, q + 2 * Q + 1, cmp);
	int xyx = 1;
	while(q[xyx].x == 0) ++xyx;
	for(int i = 1; i <= n; ++i) {
		for(int j = ans[i]; j; j = fa[j]) add(uid[j], 1);
		while(q[xyx].x == i) {
			int ques = ans[q[xyx].cx], pid = uid[ques];
			q[xyx].ans = qzh(pid + siz[ques] - 1) - qzh(pid - 1);
			++xyx;
		}
	}
	sort(q + 1, q + 2 * Q + 1, pmc);
	for(int i = 1; i <= Q; i++) printf("%lld\n", q[i * 2].ans - q[i * 2 - 1].ans);
	return 0; //}
```

---

## 作者：xht (赞：17)

> [CF547E Mike and Friends](https://codeforc.es/contest/547/problem/E)

## 题意

- 给定 $n$ 个字符串 $s_{1 \dots n}$。
- $q$ 次询问 $s_k$ 在 $s_{l \dots r}$ 中出现了多少次。
- $n, \sum |s| \le 2 \times 10^5$，$q \le 5 \times 10^5$。

## 题解

首先对 $n$ 个字符串建出 AC 自动机。

将询问离线并差分成两个询问。

将字符串顺着扫一遍，对扫过的字符串在 trie 上的所有节点贡献 $+1$。

假设此时扫到串 $i$，那么在 $i$ 上的询问 $s_k$ 的贡献等于 **$s_k$ 在 trie 上的终点**在 fail 树上的子树贡献和。

按 fail 树的 dfs 序建树状数组维护即可，时间复杂度 $\mathcal O((n + q) \log n)$。

## 代码

```cpp
const int N = 2e5 + 7, M = 26, Q = 5e5 + 7;
int n, m, q, p[N], trie[N][M], fail[N], f[N], t = 1, dfn[N], num, siz[N], c[N], k[Q], ans[Q];
char s[N];
vi e[N];

inline int ins(int n) {
	int p = 1;
	for (int i = 1; i <= n; i++) {
		int c = s[i] - 'a';
		if (!trie[p][c]) f[trie[p][c]=++t] = p;
		p = trie[p][c];
	}
	return p;
}

void dfs(int x) {
	dfn[x] = ++num, siz[x] = 1;
	for (ui i = 0; i < e[x].size(); i++) dfs(e[x][i]), siz[x] += siz[e[x][i]];
}

inline void build() {
	queue< int > q;
	for (int i = 0; i < M; i++)
		if (trie[1][i]) fail[trie[1][i]] = 1, q.push(trie[1][i]);
		else trie[1][i] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < M; i++)
			if (trie[x][i]) fail[trie[x][i]] = trie[fail[x]][i], q.push(trie[x][i]);
			else trie[x][i] = trie[fail[x]][i];
	}
	for (int i = 2; i <= t; i++) e[fail[i]].pb(i);
	dfs(1);
}

inline void add(int x) {
	while (x <= t) ++c[x], x += x & -x;
}

inline int ask(int x) {
	int ret = 0;
	while (x) ret += c[x], x -= x & -x;
	return ret;
}

int main() {
	rd(n), rd(q);
	for (int i = 1; i <= n; i++) rds(s, m), p[i] = ins(m);
	build();
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1, l, r; i <= q; i++) {
		rd(l), rd(r), rd(k[i]);
		if (l > 1) e[l-1].pb(-i);
		e[r].pb(i);
	}
	for (int i = 1; i <= n; i++) {
		int x = p[i];
		while (x ^ 1) add(dfn[x]), x = f[x];
		for (ui j = 0; j < e[i].size(); j++) {
			int o = e[i][j] > 0 ? 1 : -1, t = abs(e[i][j]), x = p[k[t]];
			ans[t] += o * (ask(dfn[x] + siz[x] - 1) - ask(dfn[x] - 1));
		}
	}
	for (int i = 1; i <= q; i++) print(ans[i]);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：15)

## 【SAM，线段树合并】CF547E Mike and Friends

### Description

给定 $n$ 个字符串 $s_1 \dots s_n$。有 $q$ 次询问，每次查询 $s_k$ 在 $s_l \sim s_r$ 中出现了多少次（作为子串）。

$1 \leq n, \sum |s| \leq 2 \times 10^5$，$1 \leq q \leq 5 \times 10^5$。

### Analysis

对 $s$ 建出广义 SAM。

考虑以 $s_k$ 为子串的串是在 fail 树上 $s_k$ 的对应结点的子树中的所有结点对应的字符串。只要那么只需要求出子树中的结点一共表示了多少个 $[l, r]$ 内的字符串即可。

考虑对每个结点维护一个权值线段树，区间 $[i, i]$ 表示它代表了几个编号为 $i$ 的子串，大区间维护区间和。在建 SAM 的时候，把所有串的所有前缀都在对应对应节点的线段树的对应位置上 $+1$，然后在 fail 树上向上线段树合并，就可以求出每个节点的信息。当然，为了不爆时空，线段树需要动态开点。查询时直接找到 $s_k$ 的对应节点，然后查询线段树上 $[l, r]$ 的区间和。

下一个问题是，如果在线段树合并的时候采取“新建一个节点”作为返回值这样不破坏原信息的写法，需要开 $8 \times \sum |s| \times \log n  \approx 3.2 \times 10^7$ 个结点，肉眼可见会爆空间。因此必须将询问离线，把询问全部挂在 $s_k$ 对应的节点上，在将 $s_k$ 子树信息合并完以后，直接求出 $s_k$ 的所有询问的答案。这样只需要开 $\sum |s| \log n$ 个线段树结点，空间上可以承受。

考虑时间复杂度（以下设 $\sum |s| = S$，字符集大小为 $t$）：一开始一共把 $O(S)$ 个前缀在线段树上修改，时间复杂度 $O(S \log n)$，构造 $SAM$ 的复杂度为 $O(S \log t)$，线段树合并的总复杂度为 $O(S \log n)$，查询复杂度为 $O(q \log n)$。因此总复杂度为 $O((S + q) \log n + S \log t)$。

### Code

```cpp
namespace Fusu {

const int maxt = 26;
const int maxh = 19;
const int maxn = 200005;
const int maxq = 500005;

int n, q;
int a[maxq], b[maxq], k[maxq], ans[maxq];

namespace Smt {

struct Node {
  int v;
  Node *ls, *rs;

  void pushup() {
    v = 0;
    if (ls) v += ls->v;
    if (rs) v += rs->v;
  }

  int qry(const int L, const int R, const int l, const int r) {
    if ((L <= l) && (r <= R)) return v;
    int ret = 0, mid = (l + r) >> 1;
    if (mid >= L) {
      ret += ls ? ls->qry(L, R, l, mid) : 0;
    }
    if (mid <= R) {
      ret += rs ? rs->qry(L, R, mid + 1, r) : 0;
    }
    return ret;
  }
};
Node Mem[maxn * maxh], *pool = Mem, rot, *rt = &rot;
inline Node* New() {
  return pool++;
}

inline void upd(Node *const u, const int p, const int v, const int l, const int r) {
  if (l == r) {
    u->v += v;
  } else {
    int mid = (l + r) >> 1;
    if (p <= mid) {
      upd(u->ls ? u->ls : u->ls = New(), p, v, l, mid);
    } else {
      upd(u->rs ? u->rs : u->rs = New(), p, v, mid + 1, r);
    }
    u->pushup();
  }
//  printf("OOOOvOOO%lld %d %d %d %d %d\n", u, l, r, u->v, u->ls ? u->ls->v : -1, u->rs ? u->rs->v : -1);
}

Node *merge(Node *const u, Node *const v) {
  if (u == nullptr) return v;
  if (v == nullptr) return u;
  if ((u->ls == nullptr) && (u->rs == nullptr)) {
    u->v += v->v;
    return u;
  }
  u->ls = merge(u->ls, v->ls);
  u->rs = merge(u->rs, v->rs);
  u->pushup();
  return u;
}

} // namespace Smt

namespace SAM {

struct Node {
  int len;
  Node *fail;
  Smt::Node *t;
  std::vector<int> qid;
  std::vector<Node*> e;
  std::map<char, Node*> trans;

  void dfs() {
    for (auto v : e) {
      v->dfs();
      t = Smt::merge(t, v->t);
    }
    for (auto x : qid) {
      ans[x] = t->qry(a[x], b[x], 1, n);
    }
  }
};
Node Mem[maxn << 1], *pool = Mem, rt , *rot = &rt;
inline Node *New(const int x) {
  pool->len = x;
  return pool++;
}

Node *extend(Node *p, const char x) {
  auto np = New(p->len + 1);
  while (p && (p->trans.count(x) == false)) {
    p->trans[x] = np;
    p = p->fail;
  }
  if (p == nullptr) {
    np->fail = rot;
  } else {
    auto q = p->trans[x];
    if (q->len == (p->len + 1)) {
      np->fail = q;
    } else {
      auto nq = New(p->len + 1);
      nq->trans = q->trans;
      nq->fail = q->fail;
      q->fail = np->fail = nq;
      while (p && (p->trans[x] == q)) {
        p->trans[x] = nq;
        p = p->fail;
      }
    }
  }
  return np;
}

void debug() {
  printf("%lld\n", rot);
  for (auto u = Mem; u != pool; ++u) printf("%lld %lld %d\n", u, u->fail, u->len);
}

} // namespace SAM

namespace Trie {

struct Node {
  Node *ls, *rs;
  SAM::Node *pos;
  std::vector<int> pid;
  std::map<int, Node*> trans;
};
Node rt, *rot = &rt, Mem[maxn], *pool = Mem;

Node* insert(char *const s, const int x, const int id) {
  auto u = rot;
  for (int i = 1, c = s[i] - 'a'; i <= x; c = s[++i] - 'a') {
    u = u->trans[c] ? u->trans[c] : (u->trans[c] = pool++);
    u->pid.push_back(id);
  }
  return u;
}

std::queue<Node*> Q;
void bfs() {
  Q.push(rot);
  rot->pos = SAM::rot;
  for (Node *u, *v; Q.empty() == false; Q.pop()) {
    u = Q.front();
    u->pos->t = Smt::pool++;
    for (auto x : u->pid) {
      Smt::upd(u->pos->t, x, 1, 1, n);
//      printf("OOvvOO%lld %d %d\n", u->pos, x, u->pos->t->v);
    }
    for (auto &vv : u->trans) {
      auto p = SAM::extend(u->pos, vv.first);
      Q.push(v = vv.second);
      v->pos = p;
    }
  }
}

} // namespace Trie
Trie::Node *epos[maxn];

char s[maxn];
void Main() {
  qr(n); qr(q);
  for (int i = 1, x; i <= n; ++i) {
    x = qrs(s + 1);
    epos[i] = Trie::insert(s, x, i);
  }
  Trie::bfs();
//  SAM::debug();
  for (int i = 1; i <= q; ++i) {
    qr(a[i]); qr(b[i]); qr(k[i]);
    epos[k[i]]->pos->qid.push_back(i);
  }
  for (auto u = SAM::Mem; u != SAM::pool; ++u) {
    u->fail->e.push_back(u);
  }
  SAM::rot->dfs();
  qwa(ans + 1, q,  '\n', '\n');
}

} // namespace Fusu
```



---

## 作者：Gypsophila (赞：7)

同步更新在我的 [blog](https://acfunction.github.io/2019/08/23/CF547E/) 。

### Description 

给定 $ n $ 个串  $ s_1, s_2, \cdots, s_n $ 和 $q$ 个询问，每次查询 $ s_i $ 一共在 $ s_l, s_{l+1}, \cdots, s_r $ 出现了多少次。

$ n, q, \sum \limits_{i=1}^{n} |s_i| \leq 2 \times 10^5 $。

### Solution

这里有一个后缀数组的做法。

- 把 $ n $ 个串依次连在一起，相邻两个之间用一个 `#` 隔开。得到一个大串 $ \mathtt{S} $ 。  
- 我们可以简单地求出第 $ i $ 个串 $ s_i $ 的长度 $len_i$，在 $ \mathtt{S} $ 中第一个字母所在的位置 $pos_i$ 以及 $ \mathtt{S} $ 的后缀数组。  
- 对于一个询问，假设询问串是 $s_k$，他在一个位置 $p$ 出现当且仅当从 $p$ 开始的后缀与从 $pos_k$ 开始的后缀的 $\mathtt{LCP} $ 的长度 $\ge len_k $ 。
- 众所周知，两个后缀 $i, j (\mathtt{rk[i]} < \mathtt{rk[j]})$ 的 $ \mathtt{LCP} $ 就是 $\min\limits_{\mathtt{rk[i] + 1} \le x \le \mathtt{rk[j]}} \{\mathtt{height[x]}\}$ ，也就是一段区间的最小值。
- 对于每个 $k$ ，我们可以简单地通过二分来找到最长的一段包含 $\mathtt{rk[k]}$ 的区间 $[L_k, R_k]$ 使得这一段区间中的 $\mathtt{height[i]}$ 最小值 $ \ge len_i$ 。
- 那么如果一个后缀的前缀是 $s_k$ ，那么他的 $ \mathtt{rk} $ 必须要在 $[L_k, R_k]$ 中。
- 而我们想要的是 $s_l, s_{l+1}, \cdots, s_r$ 中出现了多少次 $s_k$ ，所以这个后缀的出现位置 $i$ 要满足 $pos_l \le i \le pos_{r+1}-1$ 。为了方便，我们假设 $pos_{n+1} = |S|+1$ 。
- 做法已经比较显然：如果把后缀 $i$ 对应成平面直角坐标系中的点 $(i, rk_i)$ ，那么对于一个询问 $l, r, k$ ，答案便是左下角为 $(pos_l, L_k)$ ，右上角为 $(pos_{r+1}-1, R_k)$ 的矩形中点的个数。
- 这便是一个经典问题。只需要把一个询问拆成四个，拿出来按照第一关键字排序，按照顺序扫一遍，对于每个新的询问把满足第一维限制的点的第二维坐标加一，询问就查询前缀和即可。可以用一个简单的树状数组维护。
- 时间复杂度 $O(n \log n)$ 。

### Code

```cpp
/**
 * Author: AcFunction
 * Date:   2019-08-20 12:57:11
 * Email:  3486942970@qq.com
**/

#include <bits/stdc++.h>
#define ll long long
#define db double
#define PII pair <int, int> 
#define pb push_back 
#define fi first
#define se second 
#define MP make_pair

using namespace std;

const int N = 1002000; 

int n, qq, m, rk[N], sa[N], cnt[N], c[N]; 
int len[N], pos[N], h[N], st[N][25], lg2[N], ans[N];
char s[N];  
string S; 
char A[N]; 
int Lp[N], Rp[N], tot; 

struct node {
  int x, y, id; 
} a[N], b[N]; 

struct Query {
  int x, y, id, typ; 
  bool operator < (const Query &t) const {
    return x == t.x ? y < t.y : x < t.x; 
  }
} Q[N * 4]; 

int lcp(int l, int r) {
  if(l > r) return -1; int k = lg2[r - l + 1]; 
  return min(st[l][k], st[r - (1 << k) + 1][k]); 
}

int lb(int x) {
  return x & (-x); 
}

int add(int x, int d) {
  for(int i = x; i <= m; i += lb(i)) 
    c[i] += d;
}

int sum(int x) {
  int ret = 0; 
  for(int i = x; i; i -= lb(i))
    ret += c[i]; 
  return ret; 
}

int main() {
  scanf("%d %d", &n, &qq);
  int nowlen = 1;  
  for(int i = 1; i <= n; i++) {
    pos[i] = nowlen; 
    scanf("%s", s + 1); 
    len[i] = strlen(s + 1); 
    for(int j = 1; j <= len[i]; j++) 
      S += s[j]; 
    nowlen += len[i] + 1; 
    S += '#';  
  } 
  m = S.length();   
  pos[n + 1] = m + 1;
  A[0] = '#'; 
  for(int i = 0; i < m; i++) A[i + 1] = S[i]; 
  for(int i = 1; i <= m; i++) cnt[A[i]]++; 
  for(int i = 1; i <= 256; i++) cnt[i] += cnt[i - 1]; 
  for(int i = 1; i <= m; i++) rk[i] = cnt[A[i]]; 
  for(int L = 1; L <= m; L <<= 1) {
    for(int i = 1; i <= m; i++) {
      a[i].x = rk[i], a[i].y = rk[i + L]; a[i].id = i;
    }
    for(int i = 1; i <= m; i++) cnt[i] = 0; 
    for(int i = 1; i <= m; i++) cnt[a[i].y]++; 
    for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1]; 
    for(int i = 1; i <= m; i++) b[cnt[a[i].y]--] = a[i]; 
    for(int i = 1; i <= m; i++) cnt[i] = 0; 
    for(int i = 1; i <= m; i++) cnt[b[i].x]++;
    for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1]; 
    for(int i = m; i >= 1; i--) a[cnt[b[i].x]--] = b[i]; 
    for(int i = 1; i <= m; i++) {
      if(a[i].x == a[i - 1].x && a[i].y == a[i - 1].y)
        rk[a[i].id] = rk[a[i - 1].id]; 
      else rk[a[i].id] = rk[a[i - 1].id] + 1; 
    }
  }
  for(int i = 2; i <= m; i++) lg2[i] = lg2[i >> 1] + 1; 
  for(int i = 1; i <= m; i++) sa[rk[i]] = i; 
  int k = 0; 
  for(int i = 1; i <= m; i++) {
    if(k) k--; int j = sa[rk[i] - 1]; 
    while(i + k <= m && j + k <= m && A[i + k] == A[j + k]) k++;
    h[rk[i]] = k; 
  }
  for(int i = 1; i <= m; i++) st[i][0] = h[i]; 
  for(int j = 1; (1 << j) <= m; j++) 
    for(int i = 1; i + (1 << j) - 1 <= m; i++) 
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); 
  for(int i = 1; i <= n; i++) {
    int pp = pos[i];
    int l = rk[pp] + 1, r = m; 
    Lp[i] = Rp[i] = rk[pp]; 
    while(l <= r) {
      int mid = (l + r) >> 1; 
      if(lcp(rk[pp] + 1, mid) >= len[i]) {
        Rp[i] = mid; l = mid + 1;  
      } else r = mid - 1; 
    }
    l = 1, r = rk[pp]; 
    while(l <= r) {
      int mid = (l + r) >> 1; 
      if(lcp(mid + 1, rk[pp]) >= len[i]) {
        Lp[i] = mid; r = mid - 1; 
      } else l = mid + 1; 
    }  
  }
  for(int i = 1; i <= qq; i++) {
    int l, r, k; 
    scanf("%d %d %d", &l, &r, &k); 
    Q[++tot] = {pos[l] - 1, Lp[k] - 1, i, 1}; 
    Q[++tot] = {pos[r + 1] - 1, Lp[k] - 1, i, -1}; 
    Q[++tot] = {pos[l] - 1, Rp[k], i, -1}; 
    Q[++tot] = {pos[r + 1] - 1, Rp[k], i, 1}; 
  }
  int P = 1; 
  sort(Q + 1, Q + tot + 1);
  for(int i = 1; i <= tot; i++) {
    while(P <= Q[i].x && P <= m) {
      add(rk[P], 1); P++; 
    }
    // cout << Q[i].x << " " << Q[i].y << endl; 
    // cout << P << endl; 
    ans[Q[i].id] += Q[i].typ * sum(Q[i].y); 
  }
  for(int i = 1; i <= qq; i++) printf("%d\n", ans[i]); 
  return 0; 
}
```

---

## 作者：81179332_ (赞：6)

把询问离线下来拆成两个询问

对所有字符串建出 AC 自动机，建 fail 树

依次加入每一个字符串的贡献同时统计答案

对于一个字符串，它在当前所有串中出现次数为：它的终止节点在的子树（fail 树）的贡献和

怎么计算每一个串的贡献？由于 $\sum |s_i|\le n$，所以我们暴力在 trie 树上跳同时在树状数组里单点修改即可，由于维护的是子树信息，所以树状数组采用 dfs 序作为下标

```cpp
//timeuse:40min
const int N = 200010,M = N;
int cnt;
struct AC
{
	struct trie
	{
		int ch[26],fail;
		int& operator [](int x) { return ch[x]; }
	}t[N];
	int end[N],fa[N];
	void insert(char *s,int id)
	{
		int now = 0;
		for(int i = 1;s[i];i++)
		{
			int ch = s[i] - 'a';
			if(!t[now][ch]) fa[t[now][ch] = ++cnt] = now;
			now = t[now][ch];
		}end[id] = now;
	}
	queue<int> q;EE(1);
	int siz[N],dfn[N],idx;
	void dfs(int u)
	{
		dfn[u] = ++idx,siz[u] = 1;
		for(int i = head[u];i;i = e[i].nxt) dfs(e[i].to),siz[u] += siz[e[i].to];
	}
	void build()
	{
		for(int i = 0;i < 26;i++) if(t[0][i]) q.push(t[0][i]);
		while(!q.empty())
		{
			int u = q.front();q.pop();
			for(int i = 0;i < 26;i++)
				if(t[u][i]) t[t[u][i]].fail = t[t[u].fail][i],q.push(t[u][i]);
				else t[u][i] = t[t[u].fail][i];
		}
		for(int i = 1;i <= cnt;i++) add(t[i].fail,i);
		dfs(0);
	}
	struct BIT
	{
		int c[N];
		void add(int x) { for(;x <= cnt + 1;x += x & -x) c[x]++; }
		int query(int x) { int res = 0;for(;x;x -= x & -x) res += c[x];return res; }
	}bit;
	void push(int id)
	{
		int now = end[id];
		while(now) bit.add(dfn[now]),now = fa[now];
	}
	int query(int id)
	{
		int k = end[id];
		return bit.query(dfn[k] + siz[k] - 1) - bit.query(dfn[k] - 1);
	}
}AC;
int n,q;char s[N];
struct query { int k,id,t; };
vector<query> v[N];int ans[N];
int main()
{
	n = read(),q = read();
	for(int i = 1;i <= n;i++) scanf("%s",s + 1),AC.insert(s,i);
	AC.build();
	for(int i = 1;i <= q;i++)
	{
		int l = read(),r = read(),k = read();
		v[r].push_back({k,i,1});
		v[l - 1].push_back({k,i,-1});
	}
	for(int i = 1;i <= n;i++)
	{
		AC.push(i);
		for(auto j:v[i]) ans[j.id] += j.t * AC.query(j.k);
	}
	for(int i = 1;i <= q;i++) fprint(ans[i]);
}
```

---

## 作者：wasa855 (赞：5)

我是用 广义SAM+线段树合并做的，好像大家都没仔细讲，于是我来讲一下。

---

首先先建出 SAM，可以找出 SAM 中每一个点是在第几个字符串中出现的，在一棵动态开点的线段树上记录一下。然后把 SAM dfs 一遍，每一个点在每一个字符串的贡献加上他的 $son$ 的权值。

这里有一个问题：就是 SAM 中可能有些点代表的字符串是一样的，解决方法是把一样的点都交给最上面的处理。

dfs 完之后**理论上**可以得到每一个点每一个字符串的贡献，就可以做了。

---

但是他有很多细节。

首先在建 SAM 的时候就把每一个点的贡献预处理好，代码如下。

```cpp
for(int i=1;i<=n;i++)
{
	scanf("%s",str); int len=strlen(str);
	int las=1;
	for(int j=0;j<len;j++) las=insert(str[j]-'a',las),update(rt[las],1,n,i);;
	pos[i]=las;
}
```

然后因为我~~懒得离线~~（不太会），用了一个在线做法，**线段树合并之后的两个点都是有用的**，所以以下的合并做法会锅，他会在后面更新的时候覆盖掉前面还要用的数据。

```cpp
int merge(int u,int v)
{
	if(!u||!v) return u|v;
	t[u].v+=t[v].v;
	t[u].ls=merge(t[u].ls,t[v].ls);
	t[u].rs=merge(t[u].rs,t[v].rs);
	return u;
}
```

每次合并的时候要新开一个点，然后合并完了把原来的并回去，代码如下。

```cpp
int merge(int u,int v)
{
	if(!u&&!v) return 0;
	if(!v) return u;
	if(!u) {int x=++_cnt; t[x]=t[v]; return x;}
	int x=++_cnt;
	t[x].v=t[u].v+t[v].v;
	t[x].ls=merge(t[u].ls,t[v].ls);
	t[x].rs=merge(t[u].rs,t[v].rs);
	return x;
}
```

因为我很菜，所以这个做法还有点卡空间，我用了 253MB 的空间，距离 MLE 还有 3MB 。

---

于是经过一些不怎么简单的实现，（其实是我太菜了，调了一个晚上），我们得到了一个时间 $O(|s|\log |s|+q)$，空间 $O(|s|\log |s|)$ 的做法。

完整代码如下：（并不怎么好看）

```cpp
#define N 400005
int len[N],fa[N],ch[N][26],rt[N],pos[N],f[N];
char str[N];
int cnt=1,n,Q;
int insert(int c,int las)
{
	int p=las,np=++cnt;
	len[np]=len[p]+1;
	for(;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;
	if(!p) fa[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[p]+1==len[q]) fa[np]=q;
		else
		{
			int nq=++cnt; len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],26*4);
			fa[nq]=fa[q]; fa[q]=fa[np]=nq;
			for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
		}
	}
	return np;
}
struct Node{int ls,rs,v;};
struct Query{int l,r,id;};
int ans[N];
Node t[N*40];
vector<int> G[N];
vector<Query> q[N];
int _cnt;
void update(int &u,int l,int r,int p)
{
	if(!u) u=++_cnt;
	if(l==r) {t[u].v++;  return ;}
	int mid=(l+r)/2;
	if(p<=mid) update(t[u].ls,l,mid,p);
	else update(t[u].rs,mid+1,r,p);
	t[u].v=t[t[u].ls].v+t[t[u].rs].v;
}
int query(int u,int l,int r,int L,int R)
{
	if(!u) return 0;
	if(L<=l&&r<=R) return t[u].v;
	int mid=(l+r)/2,ans=0;
	if(L<=mid) ans+=query(t[u].ls,l,mid,L,R);
	if(R>mid) ans+=query(t[u].rs,mid+1,r,L,R);
	return ans;
}
int merge(int u,int v)
{
	if(!u&&!v) return 0;
	if(!v) return u;
	if(!u)
	{
		int x=++_cnt;
		t[x]=t[v];
		return x;
	}
	int x=++_cnt;
	t[x].v=t[u].v+t[v].v;
	t[x].ls=merge(t[u].ls,t[v].ls);
	t[x].rs=merge(t[u].rs,t[v].rs);
	return x;
}
void dfs(int u)
{
	for(int v:G[u])
	{
		if(len[u]==len[v]) f[v]=f[u];
		else f[v]=v;
		dfs(v); rt[u]=merge(rt[u],rt[v]);
	}
}
signed main()
{
	cin>>n>>Q;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str); int len=strlen(str);
		int las=1;
		for(int j=0;j<len;j++) las=insert(str[j]-'a',las),update(rt[las],1,n,i);;
		pos[i]=las;
	}
	for(int i=2;i<=cnt;i++) G[fa[i]].pb(i);
	f[1]=1;
	dfs(1);
	while(Q--)
	{
		int u=read(),v=read(),w=read();
		printf("%d\n",query(rt[f[pos[w]]],1,n,u,v));
	}
	return 0;
}
```



---

## 作者：Benzenesir (赞：3)

这里没有哈希的题解，所以来水一篇。

不难从题目的数据范围内找到根号的条件，一共只会出现 $\sqrt{n}$ 种不同的权值。

那不妨离线查询，对于每一种长度 $k$ 遍历一遍所有的字符串，分离出长度为 $k$ 的子串，
放进桶里，然后拆询问，在每个右端点处计算答案。

分离子串不难用哈希实现，总复杂度为 $n^{1.5}+q$。

由于这是道 CF 题，所以卡哈希，感谢 [ereoth](https://www.luogu.com.cn/user/329990) 提供的 base ，得以通过此题。


```c++
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <stack>
#include <tuple>
#include <bitset>
#define ll long long
#define ull unsigned long long
#define db double
#define fp(a,b,c) for(int a=b;a<=c;a++)
#define fd(a,b,c) for(int a=b;a>=c;a--)
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define bae 12347
#define mod 1000000007
#define eb emplace_back
#define y1 y114
#define y0 y514
#define x1 x114
#define x0 x514
#define mpr make_pair
#define met(x,t) memset(x,t,sizeof(x))
#define fir first
#define sec second
#include <numeric>
#include <stdlib.h>
#include <assert.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace std;

inline int rd(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch = getchar();
	return x * f;}
const int N=2e5+10;
int n,q;
string s[N];
vector<ll>hsh[N];
vector<int> rlen;
ll powx[N],ans[N*5];
int len[N],id[N];
struct node{
	int p,coe,id,qqq;
	node(int p=0,int coe=0,int id=0,int qqq=0):p(p),coe(coe),id(id),qqq(qqq) {}
};
vector<node> qu[450];
__gnu_pbds::gp_hash_table<ll,int> mp;
//符号 编号 哪个询问
ll split(int l,int r,int id){
	return (hsh[id][r]+mod-powx[r-l+1]*hsh[id][l-1]%mod)%mod;
}
int ppip(char c){
	return c-'a'+1;
}
void build(){
	powx[0]=1;
	fp(i,1,N-10) powx[i]=(powx[i-1]*bae)%mod;
	fp(i,1,n){
		hsh[i].resize(len[i]+2);
		fp(j,1,len[i])
			hsh[i][j]=((hsh[i][j-1]*bae)%mod+ppip(s[i][j]))%mod;
	}
}

auto uni=[](vector<int> &v){
	sort(v.begin(),v.end());
	int len=unique(v.begin(),v.end())-v.begin();
	while(v.size()^len) v.pop_back();
};

void lis(){
	fp(i,1,n)
		rlen.emplace_back(len[i]);
	uni(rlen);
	fp(i,1,n){
		int kkk=lower_bound(rlen.begin(),rlen.end(),len[i])-rlen.begin()+1;
		id[i]=kkk;
	}
}

void work(int wh){
	if(qu[wh].empty()) return ;
	int lenx=rlen[wh-1];
	mp.clear();
	sort(qu[wh].begin(),qu[wh].end(),[&](node x,node y){
		return x.p>y.p;
	});
	fp(i,1,n){
		if(qu[wh].empty()) break;
		fp(j,1,len[i]-lenx+1){
			ll kkk=split(j,j+lenx-1,i);
			mp[kkk]++;
		}
		while(!qu[wh].empty()&&qu[wh].back().p==i){
			auto [p,coe,id,qqq]=qu[wh].back();
			int kkkk=split(1,len[id],id);
			qu[wh].pop_back();
			ans[qqq]+=coe*mp[split(1,len[id],id)];
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	cin >> n >> q;
	fp(i,1,n){
		cin >> s[i];
		len[i]=s[i].length();
		s[i]=" "+s[i];
	}
	build();
	lis();
	fp(i,1,q){
		int l,r,x;
		cin >> l >> r >> x;
		qu[id[x]].emplace_back(r,1,x,i);
		if(l>1) qu[id[x]].emplace_back(l-1,-1,x,i);
	}
	ll zzz=split(1,1,1),zzzz=split(1,len[2],2);
	fp(i,1,rlen.size())
		work(i);
	fp(i,1,q) cout << ans[i] << '\n'; 
	return 0;
}
```


---

## 作者：FZzzz (赞：3)

~~萌新刚学 OI，请问这就是字符串毒瘤题吗，i 了 i 了。~~

写出这种题~~特别是用两种方法写~~真的会特别有成就感的说。

------------
这里给出一个不一样的做法以及一个烂大街的做法。

本着能用朴素 SAM 就绝对不用其他字符串数据结构的想法，我们无脑把所有串加分隔符串在一起然后建 SAM。

找出每个串所对应的节点。这个直接在 SAM 上匹配就行。当然你要是不嫌麻烦你也可以在 parent 树上跑倍增或者树剖，反正这不会成为瓶颈。

然后我们会发现，“在 $l$ 到 $r$ 的串中出现”其实就相当于在拼接串的某一部分出现。于是就线段树合并维护 endpos 集合然后查询区间和即可。

你要是搞个主席树合并我也不拦你，不过这里是可以直接离线处理的。

然后你写出了这样（可能好看一点）的代码：
```cpp
#include<algorithm>
#include<vector>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=2e5+5,maxq=5e5+5,sigma=26+5;
int n,q;
char *s[maxn],res[maxn];
int l[maxn],endl[maxn];
struct node{
	int l,r;
	node* ch[2];
	int v;
	void pushup(){
		v=0;
		if(ch[0]) v+=ch[0]->v;
		if(ch[1]) v+=ch[1]->v;
	}
	node(int l,int r):l(l),r(r),v(0){
		ch[0]=ch[1]=0;
	}
	void modify(int x,int k){
		if(l==r) v+=k;
		else{
			int mid=l+(r-l)/2;
			if(x<=mid){
				if(!ch[0]) ch[0]=new node(l,mid);
				ch[0]->modify(x,k);
			}
			else{
				if(!ch[1]) ch[1]=new node(mid+1,r);
				ch[1]->modify(x,k);
			}
			pushup();
		}
	}
	int query(int ql,int qr){
		if(ql==l&&qr==r) return v;
		else{
			int ans=0;
			if(ch[0]&&ql<=ch[0]->r) ans+=ch[0]->query(ql,min(qr,ch[0]->r));
			if(ch[1]&&qr>=ch[1]->l) ans+=ch[1]->query(max(ql,ch[1]->l),qr);
			return ans;
		}
	}
};
node* merge(node* a,node* b){
	if(!a) return b;
	if(!b) return a;
	a->ch[0]=merge(a->ch[0],b->ch[0]);
	a->ch[1]=merge(a->ch[1],b->ch[1]);
	a->v+=b->v;
	a->pushup();
	delete b;
	return a;
}
int sz,last,link[maxn*4],len[maxn*4],nxt[maxn*4][sigma];
vector<int> ch[maxn*4];
node* rt[maxn*4];
void init(){
	sz=1;
	last=0;
	link[0]=-1;
	len[0]=0;
	memset(nxt[0],-1,sizeof(nxt[0]));
	rt[0]=new node(1,endl[n]);
}
void extend(int c){
	int cur=sz++;
	len[cur]=len[last]+1;
	memset(nxt[cur],-1,sizeof(nxt[cur]));
	rt[cur]=new node(1,endl[n]);
	rt[cur]->modify(len[cur],1);
	int p=last;
	while(p>=0&&nxt[p][c]<0){
		nxt[p][c]=cur;
		p=link[p];
	}
	if(p<0) link[cur]=0;
	else{
		int q=nxt[p][c];
		if(len[p]+1==len[q]) link[cur]=q;
		else{
			int clone=sz++;
			len[clone]=len[p]+1;
			link[clone]=link[q];
			for(int i=0;i<sigma;i++) nxt[clone][i]=nxt[q][i];
			rt[clone]=new node(1,endl[n]);
			while(p>=0&&nxt[p][c]==q){
				nxt[p][c]=clone;
				p=link[p];
			}
			link[cur]=link[q]=clone;
		}
	}
	last=cur;
}
int pos[maxn];
struct query{
	int l,r;
}queries[maxq];
vector<int> q2[maxn*4];
int ans[maxq];
void dfs(int u){
	for(unsigned i=0;i<ch[u].size();i++){
		int v=ch[u][i];
		dfs(v);
		rt[u]=merge(rt[u],rt[v]);
	}
	for(unsigned i=0;i<q2[u].size();i++){
		int q=q2[u][i];
		ans[q]=rt[u]->query(endl[queries[q].l-1]+1,endl[queries[q].r]);
	}
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    q=readint();
    for(int i=1;i<=n;i++){
    	scanf("%s",res);
    	l[i]=strlen(res);
    	s[i]=new char[l[i]+1];
    	strcpy(s[i],res);
	}
	endl[0]=0;
	for(int i=1;i<=n;i++) endl[i]=endl[i-1]+l[i]+1;
	init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<l[i];j++) extend(s[i][j]-'a');
		extend(26);
	}
	for(int i=1;i<sz;i++) ch[link[i]].push_back(i);
	for(int i=1;i<=n;i++){
		pos[i]=0;
		for(int j=0;j<l[i];j++) pos[i]=nxt[pos[i]][s[i][j]-'a'];
	}
	for(int i=0;i<q;i++){
		queries[i].l=readint();
		queries[i].r=readint();
		int k=readint();
		q2[pos[k]].push_back(i);
	}
	dfs(0);
	for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}
```
~~是的这份代码的真正目的是防抄袭。~~

你会发现它 `MLE on test 9`。

这个算法的空间复杂度是 $O(n\log n)$，理论上应该是卡不掉的啊？

但是实际上由于分隔符，在串的长度都很短的情况下拼接串的长度有可能达到 $n$ 的两倍，然后 SAM 的节点又要开两倍……这样下来就是四倍。卡时间我还有点办法，空间我是真不会卡。

所以这个方法废了。

SA 什么的一辈子都不会写的，那这个多串的问题就只能用 ACAM 做了。

然后就还是套路。建 ACAM，然后根据 fail 树的意义，询问就变成问某个节点的子树内的每个节点是几个 $l$ 到 $r$ 的串对应的节点的祖先的和。

~~fz 教你说绕口令。~~

这样我们可以差分询问然后离线依次加入每个点的贡献。具体就是把它对应的节点所有祖先节点的权值加一，然后查询就是问一个子树内的和，显然搞出 dfs 序弄个树状数组就行了。

另外这里把所有祖先的权值都加一的操作我一开始脑抽想用树剖加线段树，但是其实这样还多个 log。事实上暴力也完全不会成为瓶颈因为总共算起来它依然是线性的。

然后就……就做完了。

这次是能过的代码：
```cpp
#include<queue>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=2e5+5,maxq=5e5+5,sigma=26;
int n,q;
char *s[maxn],res[maxn];
int l[maxn];
int sz=1,nxt[maxn][sigma],fail[maxn];
vector<int> ch[maxn];
int insert(char *s,int l){
	int u=0;
	for(int i=0;i<l;i++){
		if(!nxt[u][s[i]-'a']) nxt[u][s[i]-'a']=sz++;
		u=nxt[u][s[i]-'a'];
	}
	return u;
}
void build(){
	queue<int> q;
	fail[0]=-1;
	for(int i=0;i<sigma;i++) if(nxt[0][i]){
		fail[nxt[0][i]]=0;
		q.push(nxt[0][i]);
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<sigma;i++){
			if(nxt[u][i]){
				fail[nxt[u][i]]=nxt[fail[u]][i];
				q.push(nxt[u][i]);
			}
			else nxt[u][i]=nxt[fail[u]][i];
		}
	}
}
typedef unsigned uint;
int cnt=0,size[maxn],dfn[maxn];
void dfs(int u){
	size[u]=1;
	dfn[u]=++cnt;
	for(uint i=0;i<ch[u].size();i++){
		int v=ch[u][i];
		dfs(v);
		size[u]+=size[v];
	}
}
int pos[maxn];
int k[maxq];
vector<int> q2[maxn];
int c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void modify(int x,int k){
	while(x<=sz){
		c[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int s=0;
	while(x>0){
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
int ans[maxq];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    q=readint();
    for(int i=1;i<=n;i++){
    	scanf("%s",res);
    	l[i]=strlen(res);
    	s[i]=new char[l[i]+1];
    	strcpy(s[i],res);
    	pos[i]=insert(s[i],l[i]);
	}
	build();
	for(int i=1;i<=q;i++){
		int l,r;
		l=readint();
		r=readint();
		k[i]=readint();
		if(l>1) q2[l-1].push_back(-i);
		q2[r].push_back(i);
	}
	for(int i=1;i<sz;i++) ch[fail[i]].push_back(i);
	dfs(0);
	for(int i=1;i<=n;i++){
		int u=0;
		for(int j=0;j<l[i];j++){
			u=nxt[u][s[i][j]-'a'];
			modify(dfn[u],1);
		}
		for(uint j=0;j<q2[i].size();j++){
			int qq=q2[i][j];
			if(qq>0) ans[qq]+=query(dfn[pos[k[qq]]]+size[pos[k[qq]]]-1)-query(dfn[pos[k[qq]]]-1);
			else ans[-qq]-=query(dfn[pos[k[-qq]]]+size[pos[k[-qq]]]-1)-query(dfn[pos[k[-qq]]]-1);
		}
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}
```
另外两份代码由于奇奇怪怪的原因码风不一样（都很丑）……凑活看吧。

---

## 作者：GoPoux4 (赞：3)

_推销博客：https://www.cnblogs.com/syc233/p/13771152.html_

---

AC自动机+线段树合并。

---

将所有字符串插入AC自动机中，建出fail树。

若 $s$ 是 $t$ 的子串，令 $u$ 表示 $s$ 的末尾字符在AC自动机上对应的结点。由于AC自动机的性质，那么一定存在一个 $t$ 在AC自动机中的结点，满足在fail树中它在 $u$ 的子树中。

那么问题就转化为：询问 $s_k$ 在AC自动机上的结束结点的子树中，有多少结点属于 $s_{l \cdots r}$ （即插入Trie时经过的结点）。

这个问题可以用线段树合并解决。

每个结点开一个以字符串编号为下标的线段树。插入字符串 $s_{id}$ 时，在经过的所有结点的线段树中的 $id$ 位置加一，代表这个结点属于 $s_{id}$ 。

将询问离线，线段树合并到一个结点时，在线段树上查询区间和即可。

---

代码挺好写的。

$\text{Code}:$ 

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#define Rint register int
#define INF 0x3f3f3f3f
using namespace std;
typedef long long lxl;
const int maxn=2e5+5,maxq=5e5+5;
 
template <typename T>
inline void read(T &x)
{
	x=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	x*=f;
}

struct edge
{
	int u,v,next;
	edge(int u,int v,int next):u(u),v(v),next(next){}
	edge(){}
}e[maxn];

int head[maxn],ecnt;

inline void add(int u,int v)
{
	e[ecnt]=edge(u,v,head[u]);
	head[u]=ecnt++;
}

struct Segment_Tree
{
	int tot;
	int sum[maxn<<5],ch[maxn<<5][2];
	inline void update(int p)
	{
		sum[p]=sum[ch[p][0]]+sum[ch[p][1]];
	}
	void modify(int &p,int l,int r,int ps,int d)
	{
		if(!p) p=++tot;
		sum[p]+=d;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(ps<=mid) modify(ch[p][0],l,mid,ps,d);
		else modify(ch[p][1],mid+1,r,ps,d);
	}
	int query(int p,int l,int r,int L,int R)
	{
		if(!sum[p]||(L<=l&&r<=R)) return sum[p];
		int mid=(l+r)>>1,ans=0;
		if(L<=mid) ans+=query(ch[p][0],l,mid,L,R);
		if(R>mid) ans+=query(ch[p][1],mid+1,r,L,R);
		return ans;
	}
	int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		sum[x]+=sum[y];
		ch[x][0]=merge(ch[x][0],ch[y][0]);
		ch[x][1]=merge(ch[x][1],ch[y][1]);
		return x;
	}
}st;
int rt[maxn];

struct querys
{
	int l,r,id;
	querys(int l,int r,int id):l(l),r(r),id(id){}
	querys(){}
};

int n,q,idx[maxn];
vector<querys> vec[maxn];
int ans[maxq];
int ch[maxn][30],tot;
int fail[maxn];

inline void insert(const char *s,int id)
{
	int len=strlen(s+1),u=0;
	for(int i=1;i<=len;++i)
	{
		int c=s[i]-'a'+1;
		if(!ch[u][c]) ch[u][c]=++tot;
		u=ch[u][c];
		st.modify(rt[u],1,n,id,1);
	}
	idx[id]=u;
}

inline void GetFail()
{
	queue<int> q;
	memset(fail,-1,sizeof(fail));
	for(int i=1;i<=26;++i)
		if(ch[0][i]) q.push(ch[0][i]),fail[ch[0][i]]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=1;i<=26;++i)
			if(ch[u][i])
			{
				fail[ch[u][i]]=ch[fail[u]][i];
				q.push(ch[u][i]);
			}
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=1;i<=tot;++i)
		if(~fail[i]) add(fail[i],i);
}

inline void dfs(int u)
{
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		dfs(v);
		rt[u]=st.merge(rt[u],rt[v]);
	}
	for(auto v:vec[u])
		ans[v.id]=st.query(rt[u],1,n,v.l,v.r);
}

char s[maxn];

int main()
{
	// freopen("CF547E.in","r",stdin);
	read(n),read(q);
	for(int i=1;i<=n;++i)
	{
		scanf(" %s",s+1);
		insert(s,i);
	}
	memset(head,-1,sizeof(head));
	GetFail();
	for(int i=1,l,r,k;i<=q;++i)
	{
		read(l),read(r),read(k);
		vec[idx[k]].push_back(querys(l,r,i));
	}
	dfs(0);
	for(int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}

```


---

## 作者：tzc_wk (赞：2)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/547/problem/E)

好久每做过 AC 自动机的题了……做几个题回忆一下罢

AC 自动机能够解决多串**匹配问题**，注意是匹配，碰到前后缀的问题那多半不在 AC 自动机能解决的范围内。

在初学 AC 自动机的时候相信大家都做过一道题叫做 P2414 [NOI2011] 阿狸的打字机。在这道题中我们用到了两棵树，一棵就是所有串的字典树，称为 trie 树，令一棵是求出每个点的 $fail_i$ 后，对于所有不是根节点的 $i$ 连边 $(fail_i,i)$ 后形成的树，称为 fail 树。

在那道题中我们学到了一个很重要的结论，那就是一个字符串 $s$ 在另一个字符串 $t$ 中出现的次数，等于 $t$ 的结尾位置在 **trie** 树上的祖先中，有多少个在 $s$ 的结尾位置在 **fail** 树的子树中。可以简单记为“**模式串 fail 树向下，文本串 trie 树向上**”。这个结论是解不少 AC 自动机与数据结构结合的题的基础。

那么我们就用这个结论来解这道题。首先建出 AC 自动机。我们考虑可以用差分的思想把一个询问拆成 $(l-1,k)$ 和 $(r,k)$ 两部分，二者相减得到答案。于是现在问题转化为处理形如“$s_y$ 在前 $x$ 个字符串中出现了多少次”，我们把这样的询问都挂到 $x$ 上并动态地添加字符串。当我们加入一个字符串 $s_i$ 的时候，假设 $s_i$ 的结尾位置为 $x$，由于 $s_i$ 是文本串要在 trie 树上向上跳，我们就枚举 $x$ 的所有祖先 $y$ 并在 $y$ 位置上加 $1$，表示 $y$ 节点的访问次数多了 $1$1。查询的时候就求出 $s_k$ 的结尾位置在 fail 树中的子树中有多少个 $1$，这个显然可以树状数组+DFS 序搞定。算下时间复杂度，显然对于一个字符串 $i$，它在 trie 树上的祖先个数就是 $|s_i|$，故我们最多在树状数组上加 $\sum|s_i|$ 次，复杂度线对。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e5;
const int MAXQ=5e5;
const int ALPHA=26;
int n,qu;string s[MAXN+5];
int ch[MAXN+5][ALPHA+2],fail[MAXN+5],ncnt=0,ed[MAXN+5],ans[MAXQ+5];
void insert(string s,int id){
	int cur=0;
	for(int i=0;i<s.size();i++){
		if(!ch[cur][s[i]-'a']) ch[cur][s[i]-'a']=++ncnt;
		cur=ch[cur][s[i]-'a'];
	} ed[id]=cur;
}
void getfail(){
	queue<int> q;
	for(int i=0;i<ALPHA;i++) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<ALPHA;i++){
			if(ch[x][i]){fail[ch[x][i]]=ch[fail[x]][i];q.push(ch[x][i]);}
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}
int hd[MAXN+5],to[MAXN+5],nxt[MAXN+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int tim=0,bgt[MAXN+5],edt[MAXN+5];
void dfs(int x){bgt[x]=++tim;for(int e=hd[x];e;e=nxt[e]) dfs(to[e]);edt[x]=tim;}
int t[MAXN+5];
void add(int x,int v){for(int i=x;i<=(ncnt+1);i+=(i&(-i))) t[i]+=v;}
int query(int x){int ret=0;for(int i=x;i;i&=(i-1)) ret+=t[i];return ret;}
vector<pair<pii,int> > qv[MAXN+5];
int main(){
	scanf("%d%d",&n,&qu);for(int i=1;i<=n;i++) cin>>s[i],insert(s[i],i);
	getfail();for(int i=1;i<=ncnt;i++) adde(fail[i],i);dfs(0);
	for(int i=1;i<=qu;i++){
		int l,r,k;scanf("%d%d%d",&l,&r,&k);
		qv[r].pb(mp(mp(i,1),k));qv[l-1].pb(mp(mp(i,-1),k));
	}
	for(int i=1;i<=n;i++){
		int cur=0;
		for(int j=0;j<s[i].size();j++){
			cur=ch[cur][s[i][j]-'a'];add(bgt[cur],1);
		}
		ffe(it,qv[i]){
			int x=it->se,id=it->fi.fi,mul=it->fi.se;
			ans[id]+=mul*(query(edt[ed[x]])-query(bgt[ed[x]]-1));
		}
	}
	for(int i=1;i<=qu;i++) printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Boxxxxxx (赞：2)

[博客](https://blog.csdn.net/qq_43804974/article/details/106563051)

这提供一个sa+主席树的做法，这个用做法就你顺势可以在敲掉基本一样的洛谷[P4084](https://www.luogu.com.cn/problem/P4094)

题意询问的是k串在[L,R]的串里面出现了多少次，不同位置算多次。

对于一个串在SA里的位置以及和他最像的位置必然是连续的（字典序的原因）,然后对于每一个串就都可以二分出一个区间，这个区间内的串都有和当前串相同的前缀。

那么我们知道这个区间后，怎么知道询问要求的区间有多少个是落在能够使用的区间呢？

以下rk指sa的rank数组

这就是可以利用主席树。我们让rk为权值去建立主席树，然后按字符串长度的顺序去插入，然后询问的时候我们就可以直接询问主席树上某个区间里面出现了多少个rk在二分出来的区间的数量，（二分出来的区间也就是一个rk的区间范围）


RE警告之一：由于字符串可以有很多个，如果每一组都是用新的字符去连接的话，字符会不够用，这就会RE，我们需要用int去存储字符串，这样就不会有RE的问题了。

RE警告之二：二分的时候要注意有没有写错，如果你想用之前写过的某道题的二分写法，最好不用这道[P2336 ](https://www.luogu.com.cn/problem/P2336)那道题的二分你写错了也能A，你debug可能要好久。

RE警告之三：主席树空间要开足，我一开始主席树开小了出RE但是没红感叹号提醒又debug好久

[代码时间](https://www.luogu.com.cn/paste/90kcs5vv)

---

## 作者：Durant_Lee (赞：2)

[欢迎来我的blog逛逛~](https://blog.csdn.net/Dream_Lolita/article/details/86657057)

这种东西显然$\text{SAM}$线段树合并就可以做了吧。建出$\text{SAM}$，那么询问就是子树中编号为某段区间$endpos$的数量。我们以所在串编号建立线段树，线段树合并$right$集合即可。

~~然而我又忘记SAM是节点数是两倍了~~

什么？不会$\text{SAM}$？没有关系。

其实做这题的初衷就是练$\text{AC}$自动机的，原理一样，~~但显然不够优秀~~。

我们建出$\text{AC}$自动机以后，再用每个串跑一次，对于当前串$s$前缀$s_i$，在其对应$fail$树的位置贡献$+1$，那么这个前缀的所有后缀都会被贡献一次，即它$fail$树子树中所有节点对于$s$这个串的计数都会$+1$。

现在问题就是统计子树内代表串编号在$[l,r]$的所有节点权值和。
观察到询问编号在$[l,r]$这个东西是可以差分的，那么我们线段树的下标显然就不是编号了。一种显然的方式是，我们对$fail$树求出它的$dfs$序，然后以此为下标建立线段树，可持久化一下就行了。

我们也可以使用离线$BIT$的方式解决这个问题，可以获得更优秀的空间复杂度。

两种做法时间复杂度是一样的，都是$O((n+q)\log n)$。

以下给出两种实现方式的参考代码

【SAM+线段树合并】
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=4e5+10,M=N*40;
int n,Q;
char s[N];

namespace IO
{
	int read()
	{
		int ret=0;char c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
		return ret;
	}
	void write(int x){if(x>9)write(x/10);putchar(x%10^48);}
	void writeln(int x){write(x);putchar('\n');}
}
using namespace IO;

namespace Tree
{
	int rt[N];
	struct Segment
	{
		int sz,ls[M],rs[M],sum[M];
		void update(int &x,int l,int r,int p)
		{
			if(!x) x=++sz; ++sum[x];
			if(l==r) return;
			int mid=(l+r)>>1;
			if(p<=mid) update(ls[x],l,mid,p);
			else update(rs[x],mid+1,r,p);
		}
		int query(int x,int l,int r,int L,int R)
		{
			if(!x) return 0;
			if(L<=l && r<=R) return sum[x];
			int mid=(l+r)>>1,res=0;
			if(L<=mid) res+=query(ls[x],l,mid,L,R);
			if(R>mid) res+=query(rs[x],mid+1,r,L,R);
			return res;
		}
		int merge(int x,int y)
		{
			if(!x || !y) return x+y;
			int z=++sz;
			ls[z]=merge(ls[x],ls[y]);
			rs[z]=merge(rs[x],rs[y]);
			sum[z]=sum[x]+sum[y];
			return z;
		}
	}tr;
}
using namespace Tree;

namespace SAM
{
	int p[N],b[N],c[N],id[N];
	struct SAM
	{
		int sz,las,fa[N],mx[N],ch[N][26];
		void extend(int x)
		{
			int p,q,np,nq;
			if(ch[las][x])
			{
				p=las;q=ch[p][x];
				if(mx[q]==mx[p]+1) {las=q;return;}
				nq=++sz;mx[nq]=mx[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];fa[q]=nq;
				for(;p && ch[p][x]==q;p=fa[p]) ch[p][x]=nq;
				las=nq;return;
			}
			p=las;np=las=++sz;mx[np]=mx[p]+1;
			for(;p && !ch[p][x];p=fa[p]) ch[p][x]=np;
			if(!p) fa[np]=1;
			else
			{
				q=ch[p][x];
				if(mx[q]==mx[p]+1) fa[np]=q;
				else 
				{
					nq=++sz;mx[nq]=mx[p]+1;
					memcpy(ch[nq],ch[q],sizeof(ch[q]));
					fa[nq]=fa[q];fa[np]=fa[q]=nq;
					for(;ch[p][x]==q;p=fa[p]) ch[p][x]=nq;
				}
			}
		}
		void merge()
		{
			for(int i=1;i<=sz;++i) b[mx[i]]++;
			for(int i=1;i<=sz;++i) b[i]+=b[i-1];
			for(int i=sz;i;--i) c[b[mx[i]]--]=i;
			for(int i=sz,x;i>1;--i) x=c[i],rt[fa[x]]=tr.merge(rt[x],rt[fa[x]]); 
		}
	}S;
}
using namespace SAM;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF547E.in","r",stdin);
	freopen("CF547E.out","w",stdout);
#endif
	n=read();Q=read();S.sz=S.las=1;
	for(int i=1,l;i<=n;++i) 
	{
		scanf("%s",s+1);l=strlen(s+1);S.las=1;
		for(int j=1;j<=l;++j) S.extend(s[j]-'a'),tr.update(rt[S.las],1,n,i);
		p[i]=S.las;
	}
	S.merge();
	while(Q--)
	{
		int l=read(),r=read(),id=read();
		writeln(tr.query(rt[p[id]],1,n,l,r));
	}
	return 0;
}
```
【AC自动机+主席树】
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int N=2e5+10,M=N*40;
int n,Q;

namespace IO
{
	int read()
	{
		int ret=0;char c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
		return ret;
	}
	void write(int x){if(x>9)write(x/10);putchar(x%10^48);}
	void writeln(int x){write(x);putchar('\n');}
}
using namespace IO;

namespace Tree
{
	vector<int>e[N];
	int ind,rt[N],st[N],en[N];
	struct Segment
	{
		int sz,ls[M],rs[M],sum[M];
		void copy(int x,int y){ls[x]=ls[y];rs[x]=rs[y];sum[x]=sum[y];}
		void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
		void update(int y,int &x,int l,int r,int p)
		{
			//printf("%d %d %d %d %d\n",y,x,l,r,p);
			x=++sz;copy(x,y);
			if(l==r){sum[x]++;return;}
			int mid=(l+r)>>1;
			if(p<=mid) update(ls[y],ls[x],l,mid,p);
			else update(rs[y],rs[x],mid+1,r,p);
			pushup(x);
			//printf("%d %d %d\n",l,r,sum[x]);
		}
		int query(int y,int x,int l,int r,int L,int R)
		{
			if(L<=l && r<=R) return sum[x]-sum[y];
			int mid=(l+r)>>1,res=0;
			if(L<=mid) res+=query(ls[y],ls[x],l,mid,L,R);
			if(R>mid) res+=query(rs[y],rs[x],mid+1,r,L,R);
			return res;
		}
	}tr;
	void dfs(int x)
	{
		st[x]=++ind;
		for(int i=0;i<(int)e[x].size();++i) dfs(e[x][i]);
		en[x]=ind;
	}
}
using namespace Tree;

namespace ACM
{
	int ed[N],len[N];
	char s[N];
	vector<int>ts[N];
	queue<int>q;
	struct ACM
	{
		int sz,rt,fail[N],ch[N][26];
		void init(){rt=sz=1;}
		void in(int id)
		{
			scanf("%s",s+1);len[id]=strlen(s+1);int now=rt;
			//printf("%d %d\n",id,len[id]);
			for(int i=1;i<=len[id];++i)
			{
				ts[id].pb(s[i]-'a');
				int x=s[i]-'a';
				if(!ch[now][x]) ch[now][x]=++sz;
				now=ch[now][x];
			}
			ed[id]=now;
		}
		void getfail()
		{
			q.push(rt);
			while(!q.empty())
			{
				int x=q.front();q.pop();
				for(int i=0;i<26;++i)
				{
					if(!ch[x][i]) continue;
					int t=fail[x],t1=ch[x][i];
					while(t && !ch[t][i]) t=fail[t];
					fail[t1]=t?ch[t][i]:rt;
					q.push(t1);
				}
			}
			for(int i=1;i<=sz;++i) e[fail[i]].pb(i);
		}
	}S;
}
using namespace ACM;

void build(int y,int &x,int id)
{
	int now=S.rt,las=y;
	//printf("%d %d %d %d\n",id,len[id],st[ed[id]],en[ed[id]]);
	for(int i=0;i<len[id];++i)
	{
		now=S.ch[now][ts[id][i]];
		tr.update(las,x,1,ind,st[now]);las=x;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF547E.in","r",stdin);
	freopen("CF547E.out","w",stdout);
#endif
	n=read();Q=read();S.init();
	for(int i=1;i<=n;++i) S.in(i);
	S.getfail();dfs(S.rt);
	for(int i=1;i<=n;++i) build(rt[i-1],rt[i],i);
	while(Q--)
	{
		int l=read(),r=read(),id=read();
		printf("%d\n",tr.query(rt[l-1],rt[r],1,ind,st[ed[id]],en[ed[id]]));
	}
	return 0;
}
```




---

## 作者：Purple_wzy (赞：0)

[题面](https://www.luogu.com.cn/problem/CF547E)

[英文题面](https://codeforces.com/problemset/problem/547/E)

题解：

由于要统计字符串在某一串中的出现情况，不难想到用线段树合并。

对所有串建立广义SAM，然后拓扑排序，沿着link边向上合并即可。

每次查询，只需保存每个串终止位置的节点编号，在线段树上查询。

注意建立广义SAM时不能简单地把last设为1，还要注意不能每次都新加节点，

具体可以看我的代码。

时间复杂度：$O(nlogn)$

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
namespace Tree{
	int root[404000],tot,lc[9090000],rc[9090000],w[9090000];
	#define lt lc[k],l,mid
	#define rt rc[k],mid+1,r
	I modi(int &k,int l,int r,int x){
		if(!k)k=++tot;w[k]++;
		if(l==r)return;
		re mid=(l+r)>>1;
		if(x<=mid)modi(lt,x);
		else modi(rt,x);
	}
	IN ques(int k,int l,int r,int x,int y){
		if(x>r||y<l||!k)return 0;
		if(x<=l&&r<=y)return w[k];
		re mid=(l+r)>>1;
		return ques(lt,x,y)+ques(rt,x,y);
	}
	IN merge(int x,int y){
		if(!x||!y)return x+y;
		re now=++tot;
		w[now]=w[x]+w[y];lc[now]=merge(lc[x],lc[y]);rc[now]=merge(rc[x],rc[y]);
		return now;
	}
};
namespace SAM{
	int ch[404000][27],len[404000],link[404000],tot,las,p,q,cur,cle;
	int buc[404000],sa[404000],id[202000];
	I init(){
		las=1;tot=1;
	}
	I add(int x){
		if(ch[las][x]){
			p=las;q=ch[p][x];
			if(len[p]+1==len[q]){las=q;return;}
			cle=++tot;len[cle]=len[p]+1,link[cle]=link[q];
			memcpy(ch[cle],ch[q],sizeof(ch[q]));
			while(p&&ch[p][x]==q)ch[p][x]=cle,p=link[p];
			las=cle;link[q]=cle;return;
		}
		len[cur=++tot]=len[las]+1;p=las;las=cur;
		while(p&&!ch[p][x])ch[p][x]=cur,p=link[p];
		if(!p){link[cur]=1;return;}
		q=ch[p][x];
		if(len[p]+1==len[q]){link[cur]=q;return;}
		cle=++tot;len[cle]=len[p]+1,link[cle]=link[q];
		memcpy(ch[cle],ch[q],sizeof(ch[q]));
		while(p&&ch[p][x]==q)ch[p][x]=cle,p=link[p];
		link[cur]=link[q]=cle;
	}
	I sort(){
		F(i,1,tot)buc[len[i]]++;
		F(i,1,tot)buc[i]+=buc[i-1];
		FOR(i,tot,1)sa[buc[len[i]]--]=i;
		FOR(i,tot,1){
			if(sa[i]==1)continue;Tree::root[link[sa[i]]]=Tree::merge(Tree::root[link[sa[i]]],Tree::root[sa[i]]);
		}
	}
};
char c[202000];
int n,m,X,Y,W;
int main(){
	read(n);read(m);
	SAM::init();
	F(i,1,n){
		scanf("%s",c+1);SAM::las=1;re len=strlen(c+1);
		F(j,1,len)SAM::add(c[j]-'a'+1),Tree::modi(Tree::root[SAM::las],1,n,i);
		SAM::id[i]=SAM::las;
	}
	SAM::sort();
	while(m--){
		read(X);read(Y);read(W);
		printf("%d\n",Tree::ques(Tree::root[SAM::id[W]],1,n,X,Y));
	}
	return 0;
}
```

---

