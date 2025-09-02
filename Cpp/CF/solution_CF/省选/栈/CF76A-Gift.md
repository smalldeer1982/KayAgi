# Gift

## 题目描述

The kingdom of Olympia consists of $ N $ cities and $ M $ bidirectional roads. Each road connects exactly two cities and two cities can be connected with more than one road. Also it possible that some roads connect city with itself making a loop.

All roads are constantly plundered with bandits. After a while bandits became bored of wasting time in road robberies, so they suggested the king of Olympia to pay off. According to the offer, bandits want to get a gift consisted of gold and silver coins. Offer also contains a list of restrictions: for each road it is known $ g_{i} $ — the smallest amount of gold and $ s_{i} $ — the smallest amount of silver coins that should be in the gift to stop robberies on the road. That is, if the gift contains $ a $ gold and $ b $ silver coins, then bandits will stop robberies on all the roads that $ g_{i}<=a $ and $ s_{i}<=b $ .

Unfortunately kingdom treasury doesn't contain neither gold nor silver coins, but there are Olympian tugriks in it. The cost of one gold coin in tugriks is $ G $ , and the cost of one silver coin in tugriks is $ S $ . King really wants to send bandits such gift that for any two cities there will exist a safe path between them. Your task is to find the minimal cost in Olympian tugriks of the required gift.

## 样例 #1

### 输入

```
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1
```

### 输出

```
30
```

# 题解

## 作者：wheneveright (赞：13)

# CF76A Gift

## 题意
[我认为最好的题意Portal](https://www.luogu.com.cn/discuss/show/300140)感谢 @HTensor 的更好的翻译，否则我看不懂正确的题意。

## 思路

### 壹：初始的暴力思路

按照每条边的 Ag 的需求数量从小到大排序，然后枚举最大 Au 数目的大小 mg（max gold），用 Au 数目小于等于 mg 的边进行 Kruskal 然后求最小值。

时间复杂度 $O(\max(Au) \times M)$， 这里的 Au 代指 Au 的数目。

### 贰：稍微优化了一下

再开一个数组存 Au 的数目，从小到大排序后枚举那个数组的元素大小

时间复杂度 $O(M^2)$。

### 叁：最重要的优化

先来思考这么一个问题。

再 mg 小的时候，满足 Au 的数目的边尚且没被选入生成树中，那么当循环到后面时 mg 变得很大这条边是否会被选入到生成树中去？

显然不会，范围小时尚且不行，范围扩大之后哪里还会有这条边的份呢？

所以，**我们显然可以把那些没用的边在循环之后删了从而得到更好的时间复杂度**。

我选用的是用 STL 中的 [multiset](https://zhuanlan.zhihu.com/p/267056428) 不去重的集合，好处是我可以遍历每条边，还可以以 log 级别的复杂度删除边。

时间复杂度 $O(M + M \times N \times log_2N)$,可以过。


### 肆：一些可以但没必要的优化

- 优化一 ： Kruskal 中判断是否可以提前结束循环的优化。
- 优化二 ： 在核心循环的前面用**二分**定位第一个可以形成生成树的最小的 Au 的数目，之后可以从它开始跑。
- 优化三 ： 可以在排序后把 multiset 改成支持删除的**双向链表**，可以把上面那个复杂度中的 log 去掉（这个我没写）。

## ~~你们最想要的~~代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 205;
const int maxm = 50005;

struct reader {
	template <typename Type>
	reader & operator >> (Type & ret) {
		int f = 1; ret = 0; char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f=-f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret << 1) + (ret << 3) + (ch - '0');
		ret *= f; return *this;
	}
} fin; // 快读，可以像cin一样读整型数据，其他不行

int N, M, G, S;
struct Edge {
	int x, y, g, s;
	bool operator < (Edge X) const {
		return s < X.s;
	}
} P; // 边的结构体
multiset < Edge > E; // 上文提到的集合
int gg[maxm], L, R, mid, res; // 这里的gg数组是上文说的把 Au 单独出来排序
int fa[maxn];
long long ans, now;

int getfa (int id) {return id == fa[id] ? id : fa[id] = getfa (fa[id]);}

bool check (int maxg) {
	int cnt = 1;
	for (int i = 1; i <= N; i++) fa[i] = i;
	for (multiset < Edge > :: iterator it = E.begin (); it != E.end (); it++) {
		P = *it; int fx = getfa (P.x), fy = getfa (P.y);
		if (fx == fy || P.g > maxg) continue; fa[fx] = fy; cnt++;
	}
	// 二分check，multiset看不懂的去上文中的链接
	return cnt == N;
}

int main () {
	fin >> N >> M >> G >> S;
	for (int i = 1; i <= M; i++)
	fin >> P.x >> P.y >> P.g >> P.s, gg[i] = P.g, E.insert (P);
	sort (gg + 1, gg + 1 + M); L = 1; R = M; res = -1;
	while (L <= R) { // 优化二，可以去掉，不过下面的特判要注意
		mid = L + R >> 1;
		check (gg[mid]) ? R = mid - 1, res = mid : L = mid + 1;
	}	ans = 9223372036854775800; // long long 类型上限9223372036854775807
	if (res == -1) {printf ("-1"); return 0;}
	// 如果无论如何都不可以形成生成树，那么输出 -1
	for (int mg = res; mg <= M; mg++) {
		// 刷Kruskal
		int cnt = 1; now = 0;
		for (int i = 1; i <= N; i++) fa[i] = i;
		for (multiset < Edge > :: iterator it = E.begin (); it != E.end (); it++) {
			P = *it; int fx = getfa (P.x), fy = getfa (P.y);
			if (P.g > gg[mg]) continue; if (fx == fy) {
				// 如果满足上文说的优化的条件那就把这个点去掉
				multiset < Edge > :: iterator registit = it;
				registit--; E.erase (it); it = registit; continue;
			}	fa[fx] = fy; now = P.s; cnt++;
			if (cnt == N) break; // 优化一，记录当前有多少个节点在生成树中
		}
		ans = min (ans, now * S + (long long) gg[mg] * G);
	}
	cout << ans << endl;
	return 0;
}
```

## 关于其他的一些解释

### 一：关于删边时的集合迭代器更换

我是先把当前迭代器的前驱记录下来。

```cpp
multiset < Edge > :: iterator registit = it;
registit--;
```

在集合删除迭代器 it 之后，it 应该已经不在集合 E 中了，所以不能直接++，而是类似于链表一样让它变成它的前驱，之后再在循环中自动++。

```cpp
E.erase (it);
it = registit; continue;
```
然后 it 就会正常的向下一位传递。

### 二：如果链接失效等

如果链接失效等或者有什么没理解的私信我，我会进行补充说明

---

## 作者：Elma_ (赞：12)

> 一张图，每条边有两个属性  $(g_i, s_i)$ 。给定  $G, S$，求一棵图的生成树  $T$，使得  $G \times \max(g_i) + S \times \max (s_i)$ 最小  $(i\in T)$。

先对所有边按照 $g_i$ 排序。考虑枚举 $\max(g_i)$，抽出所有 $g_i \leq \max(g_i)$ 的边当做一个新图，然后在新图上维护 $s_i$ 的最小生成树。 枚举 $\max(g_i)$ 的过程相当于不断往这个新图中加边，因此我们需要支持向图中加一条边，然后求最小生成树。

设当前最小生成树的边集为 $T$。显然如果一条边离开了 $T$，就不可能再回到 $T$ 中。因此只有当前 $T$ 中的边和新加入的那条边是有用的，而 $T$ 中的边数始终是 $O(n)$ 的。于是我们暴力地每加一次边，就做一次 $\mathrm{kruskal}$，这样时间复杂度为 $O(nm\log n)$。

然而实际上每次 $\mathrm{kruskal}$ 后 $T$ 都是有序的，于是我们可以在插入一条边的时候直接暴力插入 $T$，这样时间复杂度就是 $O(nm)$。

```cpp
#include <map>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e5 + 5;
const int mod = 998244353;
const int inf = 2e18;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }


struct node {
    int u, v, g, s;
} edge[maxn], a[maxn];
int n, m, S, G, tot, ans = inf;

inline bool cmp(const node &x, const node &y) {
    return x.g < y.g;
}

struct DSU {
    int fa[maxn];
    inline void init() {
        for (int i = 1;i <= n;i++) fa[i] = i;
    }
    inline int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    inline void uni(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) fa[fx] = fy;
    }
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
} s;

signed main(void) { 
    n = read(), m = read(), S = read(), G = read();
    for (int i = 1;i <= m;i++) edge[i].u = read(), edge[i].v = read(), edge[i].s = read(), edge[i].g = read();
    sort(edge + 1, edge + m + 1, cmp);
    for (int i = 1;i <= m;i++) {
        int pos = ++tot;
        while (pos >= 2 && a[pos - 1].s > edge[i].s) {
            a[pos] = a[pos - 1]; pos--;
        }
        a[pos] = edge[i], s.init();
        int cnt = 0, maxS = 0;
        for (int i = 1;i <= tot;i++) {
            int u = a[i].u, v = a[i].v;
            if (!s.same(u, v)) {
                s.uni(u, v), a[++cnt] = a[i];
                maxS = max(maxS, a[i].s);
            }
        }
        if (cnt == n - 1) ans = min(ans, maxS * S + edge[i].g * G);
        tot = cnt;
    }
    printf("%lld\n", (ans == inf) ? -1 : ans);
    return 0; 
}
```


---

## 作者：ghr_226 (赞：9)

# 思路：

提供一种题解区没有的 ~~麻烦的要死~~ 的 **LCT** 做法。

转换题意，求所有生成树 $P$ 的

$$
Min(Max_{i\in P}\ g_i\times G+Max_{i\in P}\ s_i\times S)
$$

发现和 [魔法森林](https://www.luogu.com.cn/problem/P2387) 很像。

考虑类似的维护方式。

化边为点，先将边按 $g_i$ 排序，然后逐条加入边，维护 $s_i$ 的最小生成树，并在图连通后每次更新答案。

考虑如何维护 $s_i$ 的最小生成树：

加入一条边：
- 如果边的两端点不连通，直接加入。
- 如果边的两端点连通，加入这条边后势必成环，找到环上 $s_i$ 最大的边，删除即可。

于是 **LCT** 维护链的 $Max\ s_i$ 即可。

考虑如何更新答案：

即要维护根节点的整棵子树的 $Max\ g_i$ 和 $Max\ s_i$。

用 **LCT** 维护子树最值的常规手段，在每个节点开一个 **multiset** 维护虚子树的最值，在 **access** 和 **link** 时更新即可。

时间复杂度：$O(mlog^2(n+m))$ ~~（常数极大）~~。

~~于是可以加强到~~ $n,m\leq 10^5$ 。

注意最大的答案可能到 $2\times 10^{18}$，于是 **INF** 要开大。

update:
经过奆佬 @[FSYolanda](https://www.luogu.com.cn/user/73811) 的提醒，更新答案只用维护边的集合，于是用一个 **set** 维护可以做到 $O(mlogn)$ ~~(跑得挺快)~~。

~~于是可以加强到~~ $n,m\leq 10^6$ 了。


# code：

$O(mlog^2(n+m))$


```cpp
#include <bits/stdc++.h>
using namespace std;

#define re register
#define LL long long
typedef unsigned int uint;
typedef unsigned long long ull;
#define fir first
#define sec second
#define pb push_back
#define mp make_pair

#define int long long

namespace IO {
char buf_[1 << 21], *p1_ = buf_, *p2_ = buf_;
#define ch()                                                                 \
  (p1_ == p2_ &&                                                             \
           (p2_ = (p1_ = buf_) + fread(buf_, 1, 1 << 21, stdin), p1_ == p2_) \
       ? EOF                                                                 \
       : *p1_++)
inline int in() {
  int s = 0, f = 1;
  char x = ch();
  for (; x < '0' || x > '9'; x = ch())
    if (x == '-') f = -1;
  for (; x >= '0' && x <= '9'; x = ch()) s = (s * 10) + (x & 15);
  return f == 1 ? s : -s;
}
char _buf[1 << 21];
int _pos = -1;
inline void flush() { fwrite(_buf, 1, _pos + 1, stdout), _pos = -1; }
inline void pc(char x) {
  if (_pos == (1 << 21) - 1) flush();
  _buf[++_pos] = x;
}
inline void out(int x) {
  char k[30];
  int pos = 0;
  if (!x) return pc('0');
  if (x < 0) pc('-'), x = -x;
  while (x) k[++pos] = (x % 10) | 48, x /= 10;
  for (re int i = pos; i; i--) pc(k[i]);
}
inline void out(string x) {
  int len = x.size();
  for (re int i = 0; i < len; ++i) pc(x[i]);
}
}  // namespace IO
using namespace IO;

const int A = 5e5 + 5;
const int INF = 3e18;
int n, m;
int G, S;
int ans = INF;

struct Road {
  int x, y, g, s;
  inline friend bool operator<(Road u, Road v) { return u.g < v.g; }
} p[A];

struct LCT {
  int ch[A][2], f[A], rev[A], mxg[A], mxs[A], xg[A], xs[A];
  struct MG {
    int x;
    MG(int _x = 0) { x = _x; }
    inline friend bool operator<(MG u, MG v) { return p[u.x].g > p[v.x].g; }
  };
  struct MS {
    int x;
    MS(int _x = 0) { x = _x; }
    inline friend bool operator<(MS u, MS v) { return p[u.x].s > p[v.x].s; }
  };
  multiset<MG> mg[A];
  multiset<MS> ms[A];

  inline int isroot(int x) { return ch[f[x]][0] != x && ch[f[x]][1] != x; }

  inline int Maxg(int x, int y) { return p[x].g > p[y].g ? x : y; }
  inline int Maxs(int x, int y) { return p[x].s > p[y].s ? x : y; }

  inline void pushup(int x) {
    mxg[x] =
        Maxg(Maxg(x, (*mg[x].begin()).x), Maxg(mxg[ch[x][0]], mxg[ch[x][1]]));
    mxs[x] =
        Maxs(Maxs(x, (*ms[x].begin()).x), Maxs(mxs[ch[x][0]], mxs[ch[x][1]]));
    xg[x] = Maxg(x, Maxg(xg[ch[x][0]], xg[ch[x][1]]));
    xs[x] = Maxs(x, Maxs(xs[ch[x][0]], xs[ch[x][1]]));
  }

  inline void reverse(int x) {
    if (x) swap(ch[x][0], ch[x][1]), rev[x] ^= 1;
  }

  inline void pushdown(int x) {
    if (rev[x]) reverse(ch[x][0]), reverse(ch[x][1]), rev[x] ^= 1;
  }

  inline void rotate(int x) {
    int y = f[x], z = f[y];
    int k = (ch[y][1] == x);
    if (!isroot(y)) ch[z][(ch[z][1] == y)] = x;
    f[x] = z, ch[y][k] = ch[x][k ^ 1];
    if (ch[x][k ^ 1]) f[ch[x][k ^ 1]] = y;
    ch[x][k ^ 1] = y, f[y] = x;
    pushup(y);
    return;
  }

  int st[A], top;
  inline void pushpath(int x) {
    top = 0;
    st[++top] = x;
    for (int i = x; !isroot(i); i = f[i]) st[++top] = f[i];
    for (int i = top; i; i--) pushdown(st[i]);
    return;
  }

  inline void splay(int x) {
    pushpath(x);
    while (!isroot(x)) {
      int y = f[x], z = f[y];
      if (!isroot(y)) {
        if ((ch[y][1] == x) == (ch[z][1] == y))
          rotate(y);
        else
          rotate(x);
      }
      rotate(x);
    }
    pushup(x);
    return;
  }

  inline void access(int x) {
    for (int y = 0; x; y = x, x = f[x]) {
      splay(x);
      if (y) {
        mg[x].erase(mg[x].find(MG(mxg[y])));
        ms[x].erase(ms[x].find(MS(mxs[y])));
      }
      if (ch[x][1]) {
        mg[x].insert(MG(mxg[ch[x][1]]));
        ms[x].insert(MS(mxs[ch[x][1]]));
      }
      ch[x][1] = y;
      pushup(x);
    }
  }

  inline void makeroot(int x) { access(x), splay(x), reverse(x); }

  inline int findroot(int x) {
    access(x), splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    return x;
  }

  inline void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
  }

  inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x)
      f[x] = y, mg[y].insert(MG(mxg[x])), ms[y].insert(MS(mxs[x]));
    pushup(y);
  }

  inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && f[x] == y && ch[y][0] == x) f[x] = 0, ch[y][0] = 0;
    pushup(y);
  }

  struct DSU {
    int f[A], num[A];
    inline int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
    inline void merge(int x, int y) {
      if (find(x) != find(y))
        num[find(y)] += num[find(x)], f[find(x)] = find(y);
    }
  } D;

  inline void work(int now) {
    if (D.find(p[now].x) != D.find(p[now].y)) {
      link(p[now].x + m, now);
      link(p[now].y + m, now);
      D.merge(p[now].x, p[now].y);
    } else {
      split(p[now].x + m, p[now].y + m);
      if (p[xs[p[now].y + m]].s > p[now].s) {
        int t = xs[p[now].y + m];
        cut(p[t].x + m, t), cut(p[t].y + m, t);
        link(p[now].x + m, now), link(p[now].y + m, now);
      }
    }
    if (D.num[D.find(1)] == n) {
      makeroot(m + 1);
      ans = min(ans, p[mxg[m + 1]].g * G + p[mxs[m + 1]].s * S);
    }
    return;
  }

} T;

signed main() {
  n = in(), m = in(), G = in(), S = in();
  for (int i = 1; i <= m; i++)
    p[i].x = in(), p[i].y = in(), p[i].g = in(), p[i].s = in();
  sort(p + 1, p + 1 + m);
  for (int i = 1; i <= n; i++) T.D.f[i] = i, T.D.num[i] = 1;
  for (int i = 1; i <= m; i++) T.mxg[i] = T.mxs[i] = i;
  for (int i = 1; i <= m; i++) T.work(i);
  out(ans == INF ? -1 : ans), pc('\n');
  flush();
  return 0;
}
```

# code:

$O(mlogn)$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define re register
#define LL long long
typedef unsigned int uint;
typedef unsigned long long ull;
#define fir first
#define sec second
#define pb push_back
#define mp make_pair

#define int long long

namespace IO {
char buf_[1 << 21], *p1_ = buf_, *p2_ = buf_;
#define ch()                                                                 \
  (p1_ == p2_ &&                                                             \
           (p2_ = (p1_ = buf_) + fread(buf_, 1, 1 << 21, stdin), p1_ == p2_) \
       ? EOF                                                                 \
       : *p1_++)
inline int in() {
  int s = 0, f = 1;
  char x = ch();
  for (; x < '0' || x > '9'; x = ch())
    if (x == '-') f = -1;
  for (; x >= '0' && x <= '9'; x = ch()) s = (s * 10) + (x & 15);
  return f == 1 ? s : -s;
}
char _buf[1 << 21];
int _pos = -1;
inline void flush() { fwrite(_buf, 1, _pos + 1, stdout), _pos = -1; }
inline void pc(char x) {
  if (_pos == (1 << 21) - 1) flush();
  _buf[++_pos] = x;
}
inline void out(int x) {
  char k[30];
  int pos = 0;
  if (!x) return pc('0');
  if (x < 0) pc('-'), x = -x;
  while (x) k[++pos] = (x % 10) | 48, x /= 10;
  for (re int i = pos; i; i--) pc(k[i]);
}
inline void out(string x) {
  int len = x.size();
  for (re int i = 0; i < len; ++i) pc(x[i]);
}
}  // namespace IO
using namespace IO;

const int A = 5e5 + 5;
const int INF = 3e18;
int n, m;
int G, S;
int ans = INF;

struct Road {
  int x, y, g, s;
  inline friend bool operator<(Road u, Road v) { return u.g < v.g; }
} p[A];

struct LCT {
  int ch[A][2], f[A], rev[A], xg[A], xs[A];
  struct MG {
    int x;
    MG(int _x = 0) { x = _x; }
    inline friend bool operator<(MG u, MG v) { return p[u.x].g > p[v.x].g; }
  };
  struct MS {
    int x;
    MS(int _x = 0) { x = _x; }
    inline friend bool operator<(MS u, MS v) { return p[u.x].s > p[v.x].s; }
  };
  multiset<MG> mg;
  multiset<MS> ms;

  inline int isroot(int x) { return ch[f[x]][0] != x && ch[f[x]][1] != x; }

  inline int Maxg(int x, int y) { return p[x].g > p[y].g ? x : y; }
  inline int Maxs(int x, int y) { return p[x].s > p[y].s ? x : y; }

  inline void pushup(int x) {
    xg[x] = Maxg(x, Maxg(xg[ch[x][0]], xg[ch[x][1]]));
    xs[x] = Maxs(x, Maxs(xs[ch[x][0]], xs[ch[x][1]]));
  }

  inline void reverse(int x) {
    if (x) swap(ch[x][0], ch[x][1]), rev[x] ^= 1;
  }

  inline void pushdown(int x) {
    if (rev[x]) reverse(ch[x][0]), reverse(ch[x][1]), rev[x] ^= 1;
  }

  inline void rotate(int x) {
    int y = f[x], z = f[y];
    int k = (ch[y][1] == x);
    if (!isroot(y)) ch[z][(ch[z][1] == y)] = x;
    f[x] = z, ch[y][k] = ch[x][k ^ 1];
    if (ch[x][k ^ 1]) f[ch[x][k ^ 1]] = y;
    ch[x][k ^ 1] = y, f[y] = x;
    pushup(y);
    return;
  }

  int st[A], top;
  inline void pushpath(int x) {
    top = 0;
    st[++top] = x;
    for (int i = x; !isroot(i); i = f[i]) st[++top] = f[i];
    for (int i = top; i; i--) pushdown(st[i]);
    return;
  }

  inline void splay(int x) {
    pushpath(x);
    while (!isroot(x)) {
      int y = f[x], z = f[y];
      if (!isroot(y)) {
        if ((ch[y][1] == x) == (ch[z][1] == y))
          rotate(y);
        else
          rotate(x);
      }
      rotate(x);
    }
    pushup(x);
    return;
  }

  inline void access(int x) {
    for (int y = 0; x; y = x, x = f[x]) splay(x), ch[x][1] = y, pushup(x);
  }

  inline void makeroot(int x) { access(x), splay(x), reverse(x); }

  inline int findroot(int x) {
    access(x), splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    return x;
  }

  inline void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
  }

  inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) f[x] = y;
  }

  inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && f[x] == y && ch[y][0] == x) f[x] = 0, ch[y][0] = 0;
    pushup(y);
  }

  struct DSU {
    int f[A], num[A];
    inline int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
    inline void merge(int x, int y) {
      if (find(x) != find(y))
        num[find(y)] += num[find(x)], f[find(x)] = find(y);
    }
  } D;

  inline void work(int now) {
    if (D.find(p[now].x) != D.find(p[now].y)) {
      link(p[now].x + m, now);
      link(p[now].y + m, now);
      mg.insert(MG(now)), ms.insert(MS(now));
      D.merge(p[now].x, p[now].y);
    } else {
      split(p[now].x + m, p[now].y + m);
      if (p[xs[p[now].y + m]].s > p[now].s) {
        int t = xs[p[now].y + m];
        cut(p[t].x + m, t), cut(p[t].y + m, t);
        mg.erase(mg.find(t)), ms.erase(ms.find(t));
        link(p[now].x + m, now), link(p[now].y + m, now);
        mg.insert(MG(now)), ms.insert(MS(now));
      }
    }
    if (D.num[D.find(1)] == n)
      ans = min(ans, p[(*mg.begin()).x].g * G + p[(*ms.begin()).x].s * S);
    return;
  }

} T;

signed main() {
  n = in(), m = in(), G = in(), S = in();
  for (int i = 1; i <= m; i++)
    p[i].x = in(), p[i].y = in(), p[i].g = in(), p[i].s = in();
  sort(p + 1, p + 1 + m);
  for (int i = 1; i <= n; i++) T.D.f[i] = i, T.D.num[i] = 1;
  for (int i = 1; i <= m; i++) T.work(i);
  out(ans == INF ? -1 : ans), pc('\n');
  flush();
  return 0;
}
```



---

## 作者：BDFCL (赞：7)

**Solution**

首先考虑只有银币怎么做，显然此时的答案为最小生成树中最大边的权值

现在我们又加入了金币的限制，所以我们考虑枚举金币的数量$max\_g$，然后每次将符合条件（即$g_i\leq max\_g$）的边加入新图，然后对这个新图按银币为权值做最小生成树

这么做复杂度大概是$O(M^2)$的

考虑优化复杂度，为了使之前加入的边在新的图中都有用，我们将边按照$g_i$从小到大排序，依次作为$max\_g$。这样建图的复杂度变成了$O(M)$的

现在复杂度主要是在每次都要求一边最小生成树的问题

我们可以发现一个性质——如果这条边之前不是最小生成树中的边，那么之后都不可能成为最小生成树中的边，证明十分显然：如果之前都不在里面了，那么之后如果要用它，为什么不用原先更小的那个呢

这样我们求最小生成树的考虑边数就变成了$O(N)$的了，但是由于每次都要将边排序所以我们的复杂度是$O(MN\log N)$的，大约在$7\times10^7$左右，考虑到CF的机子很快，可能可以过

但是又考虑到这是远古场，所以可能并不是让我们$7\times10^7$暴力过的，所以我们再考虑进一步优化

由于我们每次将一条新边加入的时候之前的边都是排好序的，我们便想到了归并排序。而由于我们每次只加进去一条边，所以直接将比这条边差的暴力后移一位再直接将其插入到对应位置即可，类似于冒泡排序

这么做复杂度就变成了$O(MN)$的了

**Code**

```c++
#include <bits/stdc++.h>

#define N (int) 1e5
#define ll long long
#define INF (ll) 2e18

using namespace std;

int input () {
    int x = 0, f = 0;
    char c = getchar ();
    while (c < '0' || c > '9') f = c == '-', c = getchar ();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar ();
    return f ? - x : x;
}

int n, m;
int S, G;
struct Edge {
    int u, v, g, s;
} edge[N];

bool cmp (const Edge & x, const Edge & y) {
    return x.g < y.g;
}

struct Oniset {
    int fth[N], size[N];
    inline int findf (int x) {
        return x == fth[x] ? x : fth[x] = findf (fth[x]);
    }
    void onion (int x, int y) {
        int fx = findf (x), fy = findf (y);
        if (fx == fy) return ;
        if (size[fx] < size[fy]) fth[fx] = fy;
        else fth[fy] = fx, size[fx] += size[fx] == size[fy];
    }
    int same (int x, int y) {
        return findf (x) == findf (y);
    }
    void init (int n) {
        for (int i = 1; i <= n; i ++) fth[i] = i, size[i] = 1;
    }
} oniset;

Edge a[N];
int tot;

int main () {
    n = input (), m = input ();
    S = input (), G = input ();
    for (int i = 1; i <= m; i ++) edge[i].u = input (), edge[i].v = input (), edge[i].s = input (), edge[i].g = input ();

    sort (edge+1, edge+m+1, cmp);

    ll ans = INF;
    for (int i = 1; i <= m; i ++) {
        int pos = ++ tot;
        while (pos >= 2 && a[pos-1].s > edge[i].s) {
            a[pos]= a[pos-1];
            pos --;
        }
        a[pos] = edge[i];

        oniset.init (n);
        int tmp = 0, max_s = 0;
        for (int i = 1; i <= tot; i ++) {
            int u = a[i].u, v = a[i].v;
            if (! oniset.same (u, v)) {
                oniset.onion (u, v);
                a[++ tmp] = a[i];
                max_s = max (max_s, a[i].s);
            }
        }

        if (tmp == n-1) ans = min (ans, 1ll * (1ll * max_s * S + 1ll * edge[i].g * G));
        tot = tmp;
    }

    cout << (ans == INF ? -1 : ans) << endl;

    return 0;
}
```

**Conclusion**

* 最小生成树
* 优化掉一些不可能被考虑进来的东西，即扔掉无用状态
* 归并排序



---

## 作者：荣一鸣 (赞：4)

既然这道题给出了几个城市和城市之间联通的边及信息，让你求最小的联通值，~~看起来就是最小生成树~~就是最小生成树。[最小生成树](https://blog.csdn.net/qq_35644234/article/details/59106779)(看完记得回来，这题没这么简单)

但是呢，这棵树有两个量，需要同时考虑，又不能加起来算（因为要选取金币数最大再转换成图腾数，再加上银币数最大再转换成图腾数，不能先加起来再算最小生成树）所以我们要做一个类似于[次小生成树](http://www.cnblogs.com/Ash-ly/p/5494975.html)的操作。

我们先对金币数量排序，然后做建边的操作，当然**先把金币数小的**先放进去，然后得到一个ans，之后不断地往里塞边（**放进去后按银币冒泡**），得到一个关于金币的次小生成树，并使银币从生成树向最小生成树过度，得到一个对于银币和金币加起来最小的树。

神仙代码kruskal，没错就是这么短

```
for(ll i=1,t=0,s;i<=m;i++){
		q[++t]=a[i];
		s=0;
		for(ll j=t-1;j&&q[j+1].b<q[j].b;j--) swap(q[j],q[j+1]);//按银币将最后一个冒泡到前面
		for(ll j=1;j<=n;j++) fa[j]=j;
		for(ll j=1,x,y;s<n-1&&j<=t;j++)
			if((x=find(q[j].x))!=(y=find(q[j].y))) fa[x]=y,q[++s]=q[j];//kruskal，q[++s]=q[j]的解释见下
		if(s==n-1) ans=min(ans,1ll*A*a[i].a+1ll*B*q[s].b);//判断这棵树的大小
		t=s;//已经塞了多少边（有些边被丢掉了）
	}
```
q[++s]=q[j]这句就是将对于已经放进去的边中对于银币来说最优的边建树，剩下的就丢掉，这相当于用贪心做树的转换。

下面是总代码

```
#include<bits/stdc++.h>
#define ll long long//记得用long long
using namespace std;
struct think{
	ll x,y,a,b;
	bool operator<(const think A)const{
		return a<A.a;
	}
}a[50005],q[205];
ll n,m,A,B,fa[205];
ll find(ll x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	freopen("gift.in","r",stdin);
	freopen("gift.out","w",stdout);
	cin>>n>>m>>A>>B;
	for(ll i=1;i<=m;i++){
		cin>>a[i].x>>a[i].y>>a[i].a>>a[i].b;
	}
	sort(a+1,a+m+1);
	ll ans=0x7fffffffffffffff;
	for(ll i=1,t=0,s;i<=m;i++){
		q[++t]=a[i];
		s=0;
		for(ll j=t-1;j&&q[j+1].b<q[j].b;j--) swap(q[j],q[j+1]);
		for(ll j=1;j<=n;j++) fa[j]=j;
		for(ll j=1,x,y;s<n-1&&j<=t;j++)
			if((x=find(q[j].x))!=(y=find(q[j].y))) fa[x]=y,q[++s]=q[j];
		if(s==n-1) ans=min(ans,1ll*A*a[i].a+1ll*B*q[s].b);
		t=s;
	}
	cout<<(ans==0x7fffffffffffffff ? -1:ans);
	return 0;
}
```

---

## 作者：帅到报警 (赞：2)

### 【题目大意】

奥林匹亚王国由N个城市和M个双向道路组成。每条路连接两个城市，两个城市可以连接一条以上的道路。可能有些道路是环城的。所有的道路都不断地被强盗掠夺。后来，强盗们厌倦了在道路抢劫中浪费时间，所以他们要求奥林匹亚国王还清债务。根据提议，强盗想要得到一个由金币和银币组成的礼物。提议还包含一个表单：对于每一条道路，它都是已知的Gi——最小的金币数量和Si——最小的银币数量，应当是阻止强盗在路上抢劫的礼物。也就是说，如果礼物包含A枚金币和B枚银币(Gi<=A且Si<=B)，那么盗贼就可以在每个道路上都停止抢劫。不幸的是，财政部既无金币也无银币，但里面有奥林匹亚图格里克。一个金币在图格里克的成本是G，而一个银币在图格里克的成本是S。国王很想送上盗贼这样的礼物，使任何两个城市之间有一条安全的道路。你的任务是在图格里克找到最小的礼物金额。

### 【分析】
从题中可以看出我们要建立几条边找出最小的价值总和，所以要用最短路来实现。但是题目中有**两个变量**——金币数和银币数，所以简单的一维的Kruscal算法并不能解决。然后第一遍想的时候脑子一抽，直接将两个变量合在了一起当一维做。但是每次加进去一条边后，取的值应为金币最大量与银币最大量，所以**不一定是同一条边上的值**。那么如何才能在二维状况下用Kruscal求最短路呢？

我们可以考虑以金币为第一关键次从小到大排序，然后以银币为变量做最小生成树。所以我们先将银币数排序，但是这样的时间复杂度较高。然后我们思考Kruscal的本质，就是： 

_先构造一个只含 n 个顶点，而边集为空的子图，若将该子图中各个顶点看成是各棵树上的根结点，则它是一个含有 n 棵树的一个森林。之后，从网的边集 E 中选取一条权值最小的边，若该条边的两个顶点分属不同的树，则将其加入子图，也就是说，将这两个顶点分别所在的两棵树合成一棵树；反之，若该条边的两个顶点已落在同一棵树上，则不可取，而应该取下一条权值最小的边再试之。依次类推，直至森林中只有一棵树，也即子图中含有 n-1条边为止。_ 

所以如果这一步的最小生成树满足金币数最少，**那么这条边必定已经枚举过**。所以我们维护一个栈记录上一次最小生成树的边，然后后面几次的找边操作就在这个栈中完成。

####  tip : 注意数据范围，要使用long long；另外定义ans时赋一个最大的long long值（想想CF的数据吧）
 
 
### 【核心代码】
1、每次循环在栈中加进这条边，然后扫一遍栈来完成排序。
```cpp
tmp[++top] = node[i];
for(int j = top; j >= 2; j--)
	if(tmp[j].w2 < tmp[j - 1].w2)
		swap(tmp[j], tmp[j - 1]);
```
2、每次初始化并查集
```cpp
void set()
{
	for(long long a = 1; a <= n; a++)
		fa[a] = a;
}
```

### 【正解】
```cpp
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100100
using namespace std;

long long n, m, G, S, top;
long long ans = 0x7fffffffffffffffll;
long long fa[210];

void set()
{
	for(long long a = 1; a <= n; a++)
		fa[a] = a;
}

long long find(long long x)
{
	if(fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}

struct Node{
	long long from, to, w1, w2;
	friend istream& operator >> (istream&_, Node &a)
	{
		scanf("%d %d %d %d", &a.from, &a.to, & a.w1, &a.w2);
		return _;
	}//玄妙而又方便的读入操作
}node[51000], tmp[210];

bool cmp(Node a, Node b)
{
    if(a.w1 == b.w1)
		return a.w2 < b.w2;
    return a.w1 < b.w1;
    //以金币为第一关键词，银币为第二关键词排序
}

int main()
{
	freopen("gift.in", "r", stdin);
 	freopen("gift.out", "w", stdout);
	cin >> n >> m >> G >> S;
	for(int i = 1; i <= m; i++)
		cin >> node[i];
	sort(node + 1, node + m + 1, cmp);
	for(int i = 1; i <= m; i++)
	{
		set();
		tmp[++top] = node[i];
		for(int j = top; j >= 2; j--)
			if(tmp[j].w2 < tmp[j - 1].w2)
				swap(tmp[j], tmp[j - 1]);
		long long cnt = 0;
		for(int j = 1; j <= top; j++)
        {
            int u = find(tmp[j].from), v = find(tmp[j].to);
            if(u != v)
            {
                fa[u] = v;
                tmp[++cnt] = tmp[j];
                if(cnt == n - 1)
					break;
            }//Kruscal核心
        }
        if(cnt == n - 1)//找到第n - 1条边停止
            ans = min(ans, (long long)G * node[i].w1 + (long long)S * tmp[cnt].w2);
        top = cnt;
    }
    if(ans == 0x7fffffffffffffffll)
		cout << -1;
    else
    	cout << ans;
}
```

---

## 作者：chenxia25 (赞：1)

**[Portal]( https://www.luogu.com.cn/problem/CF76A )**

这是一道挺有意思的题，只是不知道为啥 CF 上 diff 只有 2200？可能因为是远古场吧。

首先考虑一个暴力：从小到大枚举金子数，然后显然最优银子数是递减的，这样一来便是一个 two-pointers，所有可能的最优情况一共有 $\mathrm O(m)$ 个。然后一路 two-pointers 下来，每次都暴力并查集或 DFS 判连通性，这样复杂度是 $\mathrm O\!\left(m^2\alpha\right)$（并查集的删边并不是撤销，无法优化）。但是正解似乎和这个暴力一点关系都没有（

换个角度想：之前是想先确定金银数，然后看构出来的图；而我们可以从图中抽一些边，然后看要的最小金银数。显然，对于抽出来的一些边，要的金银数便分别是这些边的最大金银数（那么边的金银数可以看作边权）。要抽出来的边使得图连通的话，显然考虑取生成树。于是我们的任务就变成了求使得 $Gg+Ss$ 最小的这样一个广义 MST。

广义 MST 怎么求呢？我们考虑 Kruskal 的本质，也就是正确性证明。它基于生成树的一个非常重要的性质：将一条非树边连入该生成树，将形成的环中异与加入边的一条边去掉，得到另一棵生成树；而任意两个生成树都可以通过上述操作互相转化。而一棵生成树是 MST 当且仅当任意一条非树边加入后，它是所在环中边权最大的（也就是无法通过上述操作使权值和变小），这个必要性显然，充分性随便反证。Kruskal 就是利用了这一点，搞出一个推论：任意一棵 MST 都包含图中最小边，亦即图中任意一条最小边都一定在至少一颗 MST 里，随便反证。那么我们 dark 选出任意一条最小边，然后考虑将这条边两端合并成一个点，问题归约为规模为 $n-1$ 的问题，至此 Kruskal 正确性得证。

可见广义 MST 可以用 Kruskal 求需要满足任意时刻都存在一条边，若它是非树边那么以它作为对象做上述操作一定能减小生成树的总权值。而这题中要求的权值是个二维的，很显然不一定存在这样一条边。于是我们考虑消掉一维。

考虑枚举第一维，也就是金子数。那么剩下来的任务就是求一个一维权值的广义 MST，很显然可以 Kruskal，就按照普通 Kruskal 选边策略显然可证正确性。但是这样还是 $\mathrm O\!\left(m^2\alpha\right)$，又回到了暴力（？

但是这个暴力是可优化的。注意到 MST 是一棵树，边数是 $\mathrm O(n)$ instead of $\mathrm O(m)$。一条边今朝不包含在 MST 里，以后永远也别想翻身（这也太显然了吧）。于是我们可以在 $g$ 的从小到大枚举过程中，实时维护 MST 的边们，然后将新加的边暴力放进去跑 Kruskal，这样总边数显然是，$\mathrm O(m)$ 次每次基础边 $\mathrm O(n)$，添加的边的总量是 $\mathrm O(m)$，还要排序，所以总复杂度是 $\mathrm O(nm\log)$。然后这个 $\log$ 可以归并掉，但还要并查集，所以是 $\mathrm O(nm\alpha)$。

至此应该可以过了，但是 yyq 说「有更优秀的方法为什么不用呢」。考虑不一次增加 $g_i=g$ 的那么多边，而一条边一条边加，这样显然会变更简单一些。考虑不再拘泥于 Kruskal，去掉并查集操作：注意到上面说的生成树的那个性质，看新加入的边加入后形成的环，能不能把原边弹劾掉。于是我们需要维护当前 MST 的邻接表，DFS、删边这一切都是 $\mathrm O(n)$ 的，所以总复杂度 $\mathrm O(nm)$。

**_[code]( https://www.luogu.com.cn/paste/915h3kk9 )_**

---

## 作者：安静学习 (赞：1)

需要注意的几点

1数据很大，爆int。

2求一个最小生成树，求这个树上面的每条边的最大的金币数和最大的银币数目，可能最大金币和银币不在一个边上

3把边按开销升序排序

4每一次新加一个边生成的最小生成树，是和前面生成的最小生成树有一定关系的，这是个减小开销的操作，只在一定数目的边内取最小生成树.想一下，m条边，每一次取那么多条边，会TLE。

5每次加入一条边，把银币小的放前面

时间复杂度为mlgm + (m * n)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e2 + 10;
const int maxm = 5e4 + 10;
//test;
int father[maxn] = {0}, T[maxn] = {0};

struct Edge{
    int from, to, gold, silver;
}edges[maxm];

bool com(Edge &a, Edge &b);

void init();

int Get(int u);

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    long long g, s;
    cin >> g >> s;
    for(int i = 0; i < m; i++){
        scanf("%d%d%d%d", &edges[i].from, &edges[i].to, &edges[i].gold, &edges[i].silver);
    }
    sort(edges, edges + m, com);
    long long anw = -1;
    int top = 0;
    for(int i = 0; i < m; i++){
        init();
        T[top++] = i;
        for(int j = top - 1; j >= 1; j--){
            if(edges[T[j]].silver < edges[T[j - 1]].silver){
                swap(T[j], T[j - 1]);
            }//silver first
        }
        int cnt = 0;
        int gold = 0, silver = 0;
        for(int j = 0; j < top; j++){
            int u = edges[T[j]].from, v = edges[T[j]].to;
            int fu = Get(u), fv = Get(v);
            if(fu != fv){
                father[fu] = fv;
                T[cnt++] = T[j];
                gold = max(gold, edges[T[j]].gold);
                silver = max(silver, edges[T[j]].silver);
                if(cnt == n - 1){break;}
            }
        }
        if(cnt == n - 1){
            if(anw == -1){ anw = g * gold + s * silver;}
            else{ anw = min(anw, g * gold + s * silver);}
        }
        top = cnt;
    }
    cout << anw;
    return 0;
}

bool com(Edge &a, Edge &b){
    return ( (a.gold < b.gold) || (a.gold == b.gold && a.silver < b.silver) );
}

void init(){
    for(int i = 0; i < maxn; i++){father[i] = i;}
}

int Get(int u){
    if(father[u] == u){return u;}
    return father[u] = Get(father[u]);
}

```


---

## 作者：UperFicial (赞：0)

**前言**

这题被老师考试放到 $\texttt{T2}$，写了个 $14$ 种贪心乱搞，结果最后一种贪心排序写挂把我人整不会了。

赛后听了讲评知道是一个生成树科技。

**题意简述**

给定 $n$ 个点，$m$ 条边的无向图，每条边有两种属性 $g$ 和 $s$，请你求出此图的一个生成树，使得 $G\times \max\{g_i\}+S\times \{s_i\}$ 尽量小。

$1\le n\le 200,1\le m\le 5\times 10^4$。

**题目解析**

这个比普通生成树多了一个限制，如果光有 $g$ 或 $s$ 的话就是一个最小生成树板子。

考虑我们把其中一个量固定下来，如 $g$，那么我们把 $g$ 升序排序，再考虑 $s$。

对于枚举的一个 $g_i$，考虑将 $[1,i-1]$ 这些边中选取一些边与第 $i$ 条边构成一棵新最小生成树，然后再算这个生成树的贡献，取个最小值即可。

问题是选哪些边构成目前看来最优的生成树。显然，我们要让 $s$ 尽可能小，而 $s_i$ 是一定要选的，所以在 $[1,i-1]$ 这些边中 $s_j>s_i$ 的边都不能选。

这样构建出一个新图，然后 $\texttt{kruskal}$ 跑一遍最小生成树，这题就没了。



---

