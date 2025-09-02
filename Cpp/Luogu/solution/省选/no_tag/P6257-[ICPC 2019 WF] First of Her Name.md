# [ICPC 2019 WF] First of Her Name

## 题目描述

众所周知，皇室家族的名字非常有讲究。而作为研究皇室的历史学家的你，最近接到了一个艰巨的任务——分析王国历史中所有皇室夫人的名字。

王国历史上有 $n$ 位皇室夫人，方便起见，我们将其从 $1$ 至 $n$ 编号。除了 $1$ 号夫人外，其余夫人的名字均为一个大写字母连接着她母亲的名字。而 $1$ 号夫人作为王国的首任王后，她的名字只有一个大写字母。

例如，由于 `AENERYS` 由 `A` 与 `ENERYS` 组成，因此 `ENERYS` 是 `AENERYS` 的母亲。相似地，`AENERYS` 是 `DAENERYS` 与 `YAENERYS` 的母亲。

你知道王国历史上所有皇室夫人的姓名与关系，而你需要完成的任务是，对于其他历史学家感兴趣的名字串 $s$，总共有多少位夫人的名字是以 $s$ 起始的。

例如在样例的皇室族谱中，`S` 至 `AENERYS` 的这一支（包含 `YS`、`RYS`、`ERYS`、`NERYS` 与 `ENERYS` 这几位夫人）均只有一位女儿。接下来 `AENERYS` 有两位女儿，分别是 `DAENERYS`，以及女儿是 `RYAENERYS` 的 `YAENERYS`。

在这个皇室家族内，有两位夫人的名字以 `RY` 起始，她们是 `RYS` 与 `RYAENERYS`。而 `ERYS` 与 `ENERYS` 均以 `E` 起始。名字以 `N` 起始的仅有一位夫人 `NERYS`。同样地，以 `S` 起始的仅有首位王后 `S`。而没有任何一位夫人的名字以 `AY` 起始。

## 说明/提示

$1\leq n\leq 10^6$，$1\leq k\leq 10^6$，$p_1=0$，特别地，对于 $1\lt i\leq n$，保证有 $1\leq p_i\lt i$。感兴趣的名字串总长不超过 $10^6$。

## 样例 #1

### 输入

```
10 5
S 0
Y 1
R 2
E 3
N 4
E 5
A 6
D 7
Y 7
R 9
RY
E
N
S
AY```

### 输出

```
2
2
1
1
0```

# 题解

## 作者：CYJian (赞：7)

## 题目大意

给定一棵 $n$ 个节点的 `Trie` 树，进行 $k$ 次询问，每次询问一个串 $str$ 与 `Trie` 树上从任意一个节点开始走到根路径上形成的串中，有多少个串满足 $str$ 是其前缀。

$1 \leq n,k,\sum|str| \leq 10^6$

## 题目解法

考虑 `Trie` 树上每一个串对所有询问串的贡献。不难发现，如果我们对询问串的反串建 `AC` 自动机（此时要求的条件是询问串是 `Trie` 树上的串的后缀），那么对于一个串 $S$，它在 `AC` 自动机中出现过的所有后缀，一定是 `fail` 树上的一条到根节点的链。我们只需要用 $S$ 在 `AC` 自动机上暴力匹配，就能找到最长的那一个后缀。打一个前缀和标记最后进行一遍 `DFS` 即可。

现在我们需要对 `Trie` 树上所有点代表的字符串跑一遍匹配。由于 `Trie` 树上的子节点所代表的串在 `AC` 自动机上跑到的匹配是可以直接用其父节点匹配的位置跳一步转移就可以到达的。利用 `Trie` 图的小 `trick` 就能做到 $O(n + k + |str|)$。

`Code`：

```cpp
const int MAXN = 1000010;

int tr[MAXN][26];
int res[MAXN];
int pos[MAXN];

char str[MAXN];
vector<int>to[MAXN];

struct ACAM {
	int tr[MAXN][26];
	int fail[MAXN];
	int cnt[MAXN];
	int ct;

	inline int Insert(int n) {
		int x = 0;
		for(int i = n; i >= 1; i--) {
			int c = str[i] - 'A';
			if(!tr[x][c])
				tr[x][c] = ++ct;
			x = tr[x][c];
		} return x;
	}

	inline void build() {
		queue<int>q;
		for(int i = 0; i < 26; i++)
			if(tr[0][i]) q.push(tr[0][i]);
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(int c = 0; c < 26; c++)
				if(tr[x][c]) fail[tr[x][c]] = tr[fail[x]][c], q.push(tr[x][c]);
				else tr[x][c] = tr[fail[x]][c];
		}
		for(int i = 1; i <= ct; i++)
			to[fail[i]].push_back(i);
	}

	inline void dfs(int x) {
		int sz = to[x].size();
		for(int i = 0; i < sz; i++)
			dfs(to[x][i]), cnt[x] += cnt[to[x][i]];
	}
}ac;

inline void dfs(int x, int y) {
	ac.cnt[y]++;
	for(int c = 0; c < 26; c++)
		if(tr[x][c]) dfs(tr[x][c], ac.tr[y][c]);
}

int main() {
	int n = ri, k = ri;
	for(int i = 1; i <= n; i++) {
		char ch = ge;
		while(!isalpha(ch)) ch = ge;
		tr[ri][ch - 'A'] = i;
	}
	for(int i = 1; i <= k; i++) {
		char ch = ge; int len = 0;
		while(!isalpha(ch)) ch = ge;
		while(isalpha(ch)) str[++len] = ch, ch = ge;
		pos[i] = ac.Insert(len);
	} ac.build(), dfs(0, 0), ac.dfs(0);
	for(int i = 1; i <= k; i++) printf("%d\n", ac.cnt[pos[i]]);
	return 0;
}
```

---

## 作者：251Sec (赞：2)

首先把所有串翻转过来，那么题目直接给的就是一棵字典树，这明示了我们建一个广义 SAM，然后我们得到了一个 Parent Tree。考虑一个人的名字对答案的贡献，容易发现它会将 Parent Tree 上对应节点的所有祖先的答案加 $1$，于是直接树上差分最后一遍 DFS 统计。

预处理完之后每个询问直接在 SAM 上找到对应节点输出答案即可。记得翻转字符串。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node {
    int ch[26], prt, len;
    Node &operator=(const Node &o) {
        for (int i = 0; i < 26; i++) ch[i] = o.ch[i];
        prt = o.prt; len = o.len;
        return *this;
    }
} f[2000020];
int cnt = 1;
int Ins(int c, int las) {
    int s = ++cnt, p = las;
    f[s].len = f[las].len + 1;
    for (; p && !f[p].ch[c]; p = f[p].prt) f[p].ch[c] = s;
    if (!p) {
        f[s].prt = 1;
        return s;
    }
    int q = f[p].ch[c];
    if (f[q].len == f[p].len + 1) {
        f[s].prt = q;
        return s;
    }
    int r = ++cnt;
    f[r] = f[q]; f[r].len = f[p].len + 1;
    int t = p;
    while (t && f[t].ch[c] == q) {
        f[t].ch[c] = r;
        t = f[t].prt;
    }
    f[q].prt = f[s].prt = r;
    return s;
}
int w[2000020];
int id[1000005];
struct Edge {
    int to, next;
    Edge() {}
    Edge(int to, int next) : to(to), next(next) {}
} e[2000020];
int head[2000020], len;
void InsE(int u, int v) {
    e[++len] = Edge(v, head[u]);
    head[u] = len;
}
int n, k;
void DFS(int u) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        DFS(v);
        w[u] += w[v];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    id[0] = 1;
    for (int i = 1; i <= n; i++) {
        char c; int p;
        cin >> c >> p;
        id[i] = Ins(c - 'A', id[p]);
        w[id[i]]++;
    }
    for (int i = 2; i <= cnt; i++) InsE(f[i].prt, i);
    DFS(1);
    while (k--) {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        int p = 1;
        for (char c : s) p = f[p].ch[c - 'A'];
        cout << w[p] << '\n';
    }
	return 0;
}
```

---

## 作者：biyi_mouse (赞：1)

### [P6257](https://www.luogu.com.cn/problem/P6257)

考虑题目给出的名字都是前面加一个字母，这非常不友好，所以我们考虑每次在后面加一个字母，然后将所有的询问串都翻转。这样题目就转化成了查找有多少个人名字后缀包含某个询问串。

这就比较好做了，我们可以对于所有翻转的查询串建立 AC 自动机，然后对于所有的名字建 Trie。显然根据题目给出的名字结构是非常好建 Trie 的。

接着我们考虑一个名字在 AC 自动机中出现的后缀肯定是一条 fail 链，所以我们不妨建出 fail 树。直接跳显然不对，但我们只要在最长的后缀的位置标记，最后用拓扑排序或者 dfs 计算答案即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
#define fro(i, a, b) for (int i = (a); i >= b; i --)
#define INF 0x3f3f3f3f
#define eps 1e-6
#define lowbit(x) (x & (-x))
#define initrand srand((unsigned)time(0))
#define random(x) ((LL)rand() * rand() % (x))
#define eb emplace_back
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, int> PDI;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}

const int N = 1000010;
int n, m;
int tr[N][26], ed[N];
char s[N];

struct AC {
    int tr[N][26], tot, fail[N], cnt[N];
    int h[N], e[N], ne[N], idx;
    
    void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    }

    int insert(string s) {
        int p = 0;
        for (int i = s.size() - 1; i >= 0; i --) {
            int c = s[i] - 'A';
            if (!tr[p][c]) tr[p][c] = ++ tot;
            p = tr[p][c];
        }
        return p;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i ++)
            if (tr[0][i]) q.push(tr[0][i]);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 26; i ++) {
                int p = tr[u][i];
                if (!p) tr[u][i] = tr[fail[u]][i];
                else {
                    fail[p] = tr[fail[u]][i];
                    q.push(p);
                }
            }
        }
    }

    void build_graph() {
        memset(h, -1, sizeof h);
        for (int i = 1; i <= tot; i ++) add(fail[i], i);
    }

    void dfs(int u) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            dfs(j);
            cnt[u] += cnt[j];   
        }
    }
} ac;

void dfs(int x, int y) {
    ac.cnt[y] ++;
    for (int i = 0; i < 26; i ++)
        if (tr[x][i])
            dfs(tr[x][i], ac.tr[y][i]); 
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i ++) {
        scanf("%s", s);
        int c = *s - 'A', p = read();
        tr[p][c] = i;
    }

    for (int i = 1; i <= m; i ++) {
        string s; cin >> s;
        ed[i] = ac.insert(s);
    }

    ac.build(); dfs(0, 0); 
    ac.build_graph(); ac.dfs(0);

    for (int i = 1; i <= m; i ++) printf("%d\n", ac.cnt[ed[i]]);
    return 0;
}
```

---

## 作者：SDqwq (赞：1)

## 思路

多串查询，考虑 $\texttt{AC}$ 自动机。

如果以题目所描述的顺序难以插入，考虑每次在其母亲的名字后面加字母，再把询问的前缀倒过来，变成询问后缀，这样问题简化了很多。

首先把每位夫人的名字插入，虽然总长度很长，但是由于每次只在已有的串后面加一个字符，所以每次 $\texttt{trie}$ 的大小只会 $+1$。

接下来考虑如何查询。如果直接这样去查询很难以处理，因为需要找到 $\texttt{trie}$ 图中每一条包含这个查询串的链。

一个很巧妙的处理是把查询串也插入 $\texttt{AC}$ 自动机中，这样可以保证其在 $\texttt{fail}$ 树中对应的结点的子树一定包含了所有以它为后缀的串。

这样一来，我们只需要让每一个名字串的结尾权值为 $1$，然后统计每个结点在 $\texttt{fail}$ 树上的子树权值和。直接查询该询问的串对应的子树权值和即可。

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 2e6 + 5, S = 26;

int pos[N];
string s;

int cnt, elst[N];
struct edge {
	int to, nxt;
} e[N << 1];
void add(int u, int v) {
	e[++cnt].to = v;
	e[cnt].nxt = elst[u];
	elst[u] = cnt;
}

int idx, go[N][S], fa[N], siz[N];
void ins(string s, int id) {
	int u = 0;
	for (auto i : s) {
		int c = i - 'A';
		if (!go[u][c]) go[u][c] = ++idx;
		u = go[u][c];
	}
	pos[id] = u;
}
void build() {
	queue<int> q;
	for (int i = 0; i < S; i++)
		if (go[0][i]) q.push(go[0][i]);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		add(fa[u], u);
		for (int i = 0; i < S; i++) {
			if (go[u][i]) fa[go[u][i]] = go[fa[u]][i], q.push(go[u][i]);
			else go[u][i] = go[fa[u]][i];
		}
	}
}
void dfs(int u) {
	for (int i = elst[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		dfs(v);
		siz[u] += siz[v];
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		char c;
		int p, u;
		scanf("\n%c %d", &c, &p);
		u = pos[p];
		if (!go[u][c - 'A']) go[u][c - 'A'] = ++idx;
		u = go[u][c - 'A'];
		pos[i] = u;
		siz[u]++;
	}
	for (int i = 1; i <= m; i++) {
		cin >> s;
		reverse(s.begin(), s.end());
		ins(s, i + n);
	}
	build();
	dfs(0);
	for (int i = 1; i <= m; i++) printf("%d\n", siz[pos[i + n]]);
	return 0;
}
```

---

## 作者：Aleph1022 (赞：1)

此文同步于我的博客：<https://www.alpha1022.me/articles/loj-6583>

依然是一个广义 SAM 屑题（  
于是 ACAM 照样能做（

为了符合各种字符串数据结构的习惯，考虑将所有串反过来。  
发现将输入看做 Trie 上的连边就可以了。  
于是直接 BFS 建广义 SAM，询问则将询问串反过来放在广义 SAM 上跑，达到的状态的 Parent Tree 上子树内所有状态都是以它为一个后缀的字符串。  
又因为每个状态一定都是一个名字，所以直接对所有串维护 $|{\rm endpos}|$ 即可。

代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e6;
int n,m,k;
char s[N + 5];
struct node
{
    int ch[26];
    int ed;
} tr[N + 5];
namespace SAM
{
    struct node
    {
        int ch[26];
        int fa,len;
    } sam[(N << 1) + 5];
    int tot = 1,las = 1,sz[(N << 1) + 5];
    inline void insert(int x)
    {
        int cur = las,p = las = ++tot,nxt;
        sam[p].len = sam[cur].len + 1,sz[p] = 1;
        for(;cur && !sam[cur].ch[x];cur = sam[cur].fa)
            sam[cur].ch[x] = p;
        if(!cur)
            sam[p].fa = 1;
        else
        {
            int q = sam[cur].ch[x];
            if(sam[cur].len + 1 == sam[q].len)
                sam[p].fa = q;
            else
            {
                nxt = ++tot;
                sam[nxt] = sam[q],sam[nxt].len = sam[cur].len + 1,sam[p].fa = sam[q].fa = nxt;
                for(;cur && sam[cur].ch[x] == q;cur = sam[cur].fa)
                    sam[cur].ch[x] = nxt;
            }
        }
    }
    int c[N + 5],a[(N << 1) + 5];
    inline void init()
    {
        for(register int i = 1;i <= tot;++i)
            ++c[sam[i].len];
        for(register int i = 1;i <= N;++i)
            c[i] += c[i - 1];
        for(register int i = tot;i > 1;--i)
            a[c[sam[i].len]--] = i;
        for(register int i = tot;i > 1;--i)
            sz[sam[a[i]].fa] += sz[a[i]];
    }
}
int q[N + 5],head,tail;
int main()
{
    scanf("%d%d",&n,&k);
    char ch;
    int fa;
    for(register int i = 1;i <= n;++i)
        scanf(" %c%d",&ch,&fa),tr[++fa].ch[ch - 'A'] = i + 1;
    q[tail = 1] = 1,tr[1].ed = 1;
    for(register int p;head < tail;)
    {
        p = q[++head];
        for(register int i = 0;i < 26;++i)
            if(tr[p].ch[i])
                SAM::las = tr[p].ed,SAM::insert(i),tr[tr[p].ch[i]].ed = SAM::las,q[++tail] = tr[p].ch[i];
    }
    SAM::init();
    for(;k;--k)
    {
        scanf("%s",s + 1),m = strlen(s + 1);
        int p = 1,flag = 0;
        for(register int i = m;i;--i)
        {
            if(!SAM::sam[p].ch[s[i] - 'A'])
            {
                puts("0"),flag = 1;
                break;
            }
            p = SAM::sam[p].ch[s[i] - 'A'];
        }
        if(!flag)
            printf("%d\n",SAM::sz[p]);
    }
}
```

---

## 作者：win114514 (赞：0)

优越 AC 自动机永不败北。

### 思路

考虑给出的姓名的反串是一颗 Trie。

我们可以考虑将询问串也进行翻转。

这道题最有用的一点是什么呢。

可以发现 Trie 上任意一个到根的路径都是一个名字。

也就是只要我们的询问串在 Trie 中出现，出现的位置都可以对应到一个名字的后缀（翻转后）。

那么可以对询问串减出 AC 自动机。

然后把 Trie 放到 AC 自动机上跑即可。

时间复杂度：$O(26(n+k))$。

### Code

```cpp
/*
  ! 以渺小启程，以伟大结束。
  ! Created: 2024/06/30 16:00:54
*/
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1e6 + 10;

int n, m, rt, ct;
int ch1[N][26], cr[N], dx[N];
int ch2[N][26], fa[N], sz[N], id[N];
vector<int> to[N];

inline void build() {
  queue<int> q;
  fro(i, 0, 25) if (ch2[0][i]) q.push(ch2[0][i]);
  while (q.empty() == 0) {
    int x = q.front(); q.pop();
    fro(i, 0, 25)
      if (ch2[x][i]) fa[ch2[x][i]] = ch2[fa[x]][i], q.push(ch2[x][i]);
      else ch2[x][i] = ch2[fa[x]][i];
  }
  fro(i, 1, ct) to[fa[i]].push_back(i);
}
inline void solve() {
  queue<int> q; q.push(0);
  while (q.empty() == 0) {
    int x = q.front();
    q.pop(), sz[cr[x]] += dx[x];
    fro(i, 0, 25) if (ch1[x][i])
      cr[ch1[x][i]] = ch2[cr[x]][i], q.push(ch1[x][i]);
  }
}
inline void dfs(int cr) {
  for (auto i : to[cr]) {
    dfs(i), sz[cr] += sz[i];
  }
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  fro(i, 1, n) {
    char x; int y;
    cin >> x >> y;
    if (!ch1[y][x - 'A']) ch1[y][x - 'A'] = i;
    dx[ch1[y][x - 'A']]++;
  }
  fro(i, 1, m) {
    string s;
    cin >> s, rt = 0;
    reverse(s.begin(), s.end());
    for (auto j : s) {
      if (!ch2[rt][j - 'A']) ch2[rt][j - 'A'] = ++ct;
      rt = ch2[rt][j - 'A'];
    }
    id[i] = rt;
  }
  build();
  solve(), dfs(0);
  fro(i, 1, m) cout << sz[id[i]] << "\n";
  return 0;
}
```

---

