# Michael and Hotel

## 题目描述

Michael and Brian are stuck in a hotel with $ n $ rooms, numbered from $ 1 $ to $ n $ , and need to find each other. But this hotel's doors are all locked and the only way of getting around is by using the teleporters in each room. Room $ i $ has a teleporter that will take you to room $ a_i $ (it might be that $ a_i = i $ ). But they don't know the values of $ a_1,a_2, \dots, a_n $ .

Instead, they can call up the front desk to ask queries. In one query, they give a room $ u $ , a positive integer $ k $ , and a set of rooms $ S $ . The hotel concierge answers whether a person starting in room $ u $ , and using the teleporters $ k $ times, ends up in a room in $ S $ .

Brian is in room $ 1 $ . Michael wants to know the set $ A $ of rooms so that if he starts in one of those rooms they can use the teleporters to meet up. He can ask at most $ 2000 $ queries.

The values $ a_1, a_2, \dots, a_n $ are fixed before the start of the interaction and do not depend on your queries. In other words, the interactor is not adaptive.

## 说明/提示

In the sample test, there are $ n=5 $ rooms and the (hidden) array describing the behavior of the teleporters is $ [1, 2, 1, 3, 2] $ .

- The first query asks whether starting from room number $ a=3 $ , and using the teleporters $ 5 $ times, one ends up in one of the two rooms $ S=\{2, 3\} $ . This action results in ending up in the room $ 1 $ , so the answer is $ 0 $ .
- The second query asks whether starting from room number $ a=2 $ , and using the teleporters $ 5 $ times, one ends up in one of the two rooms $ S=\{2, 3\} $ . This action results in ending up in the room $ 2 $ , so the answer is $ 1 $ .

## 样例 #1

### 输入

```
5

0

1```

### 输出

```
? 3 5 2 2 3

? 2 5 2 2 3

! 3 1 3 4```

# 题解

## 作者：蒟蒻君HJT (赞：5)

这道题目是好题，但是官方题解写的很不清楚，并且洛谷题解区里也没有对此的详细解释，所以我来补充一下题解。如果没有看懂的话请一定要私信问我！

首先我们可以通过二分求出任意一个 $a_i$。但是总的次数只有 $4n$，不够。此外我们可以用二分求出 $1$ 号点跳某个非常多步后到达的点 $x$，这个点 $x$ 一定是在 $1$ 号点所在连通块的环上的。可以想到，如果我们能知道这个环上的所有点构成的集合 $S$，那么我们观察其他点跳非常多步后是否能到 $S$ 即可求出每个点的答案。

但是我们没法暴力地求出 $S$。退而求其次，假设我们已经求出了在环上的**连续**的 $k$ 个点，那么我们有没有办法使 $k$ 扩增到 $2k$？我们求出所有未知是否在环上的点跳 $k$ 步后是否能达到这 $k$ 个点中的某一个。

$\text{Lemma 1.}$ 若本次新求出的点的数量少于 $k$，则本次结束后，所有在 $1$ 号点所在连通块的环上的点均已被找出。

![](https://cdn.luogu.com.cn/upload/image_hosting/9h9jt400.png)

$\text{Proof 1.}$ 这个跳 $k$ 步非常精巧。我们只关注那个环，如图所示，从目前已知的连续的 $k$ 个点往后倒退 $k$ 步，得到的依旧是环上**连续**的 $k$ 个点，若两者没有重合，则本次新求出的点的数量至少是 $k$，并且这 $2k$ 个环上的点**连续**；否则，整个环都会被这两段覆盖，也就是说我们找到了所有想找的点。

这里还需要注意一件事：我们每次新得到的点的个数很有可能大于 $k$，因为环上的点下面挂着的树上的点跳 $k$ 步后也可能会到达 $k$ 个点之一，而且我们暂时不可区分找到的哪些点是环上的，哪些不是环上的。但没关系，**我们额外维护一个 $p$ 表示当前已经找到的环上的点的个数，$p$ 在找全环上点之前必然是倍增的。** 这样就可以将新增点的个数与 $p$ 进行比较来决定是否退出了。另外，把这些点也放到 $S$ 中，并不影响正确性，因为我们只需要保证能找到所有在环上的点就可以了。

总结一下，初始时我们用 $\log_2 n$ 次操作得到了 $1$ 号点跳某个非常多步后到达的点 $x$（见前文），利用 $x$ 找到环上连续的 $k$ 个点（共 $k\log_2 n$ 次操作），然后倍增直到找全 $1$ 号点所在连通块的环上的所有点，最后令剩余点走非常多步，观察能否到达这个环。根据官方题解，取 $k=63$ 可以通过。



---

## 作者：i_am_not_feyn (赞：4)

若询问中的 $k$ 十分大，那么最后的点会直接跳到环上去。当环上的点确定时，可以对每个点询问一次求出答案。

于是考虑可以二分出与 1 在同一连通块的环上的一点，而后再二分出环上所有的点，最后再对剩下的点询问一次。令环上有 $l$ 个点，则最劣有 $l\log n+n-l$ 次询问，显然过不掉。

但是若环上有一半的点已经求出来，则每个点可用最多 2 次询问便可求出它是否在块上，即 $k,k+\dfrac{l}{2}$。

则可以先在环上求出 250 个点，然后再对每个点询问，这样最劣有 $250\log n+500$ 次，还是过不掉。

考虑如何更加快速地求出环上的点。

有一个做法是先二分求出 125 个点，然后对于余下的 375 个点询问，其中询问的 $k=125$。这样做的最劣询问次数是 $125\log n+375+2\times 250=2000$。~~刚好卡满。~~

然而当 $l<250$ 时，不在环上的点就不止 250 了。但是注意到这样的话环上的点都求出来了，直接询问即可。

[代码](https://codeforces.com/contest/1854/submission/221506418)

---

## 作者：Alex_Wei (赞：4)

### *[CF1854D Michael and Hotel](https://www.luogu.com.cn/problem/CF1854D)

来个图一乐的做法。

通过二分在 $9$ 次询问内求出点 $u$ 走 $k$ 步到达的点，记作 $s(u, k)$。

首先求出环上任意一点 $p = s(1, k \geq n)$。

考虑先求出环长 $L$。自然的想法是从小到大枚举，但这样代价太大了。注意到若询问 $f(p, k, \{p\}) = 0$ 说明 $L\nmid k$。考虑乱搞：初始令 $k = 1$，不断找到未被标记的 $e$ 使得 $\mathrm{lcm}(k, e)$ 最小且不大于 $10 ^ 9$。若 $e$ 不存在则退出，否则标记 $e$ 并继续。询问 $k$，若 $f(p, k, \{p\}) = 0$ 则将 $k$ 的所有因数全部 ban 掉，否则从小到大枚举 $k$ 的所有未被 ban 掉的因数并检查。发现在限制了每次取 $\mathrm{lcm}$ 的 $e$ 的数量不超过 $30$ 的前提下，可以用不超过 $45$ 次操作求出 $L$。

一个基本想法是查询 $f(x, k, \{x\}) = 1$ 检查 $x$ 是否在环上，但当 $x$ 所在的环长为 $L$ 的因数时，可能导致误判。我的解决方法如下：

- 对于 $L\leq 250$，注意到环长较小，考虑从 $p$ 开始，每次令 $p\gets s(p, B)$，进行 $\frac L B$ 次操作，得到点集 $S$。这样，对于没有被遍历到的点 $x$，若存在 $n\leq k\leq n + B - 1$ 使得 $f(x, k, S) = 1$，则它和环弱连通。按随机顺序枚举 $n\sim n + B - 1$，这部分期望次数为 $\frac {9L} B + (n - L) B + (L - \frac L B) \frac {B + 1} 2$。取 $B = 2$ 或 $3$ 均可以接受。
- 对于 $L > 250$，$x$ 所在环长 $L_x$ 必然是 $L$ 的真因数。因此，对不属于答案集合但所在环长为 $L$ 的因数的点 $x$，存在 $L$ 的质因子 $d$ 使得 $L_x\mid \frac L d$。这样操作次数为 $n(\omega(L) + 1)$，当 $\omega(L)\geq 3$ 时无法接受。两个优化：
  - 对于 $L\leq 419$，按随机顺序枚举 $L$ 的质因子，期望次数为 $L(\omega(L) + 1) + (n - L) \frac {\omega(L) + 1} 2$，可以接受。
  - 对于 $L\geq 420$，注意到若 $L_x\nmid \frac L d$，则 $L_x$ 一定是 $d ^ {\nu_d(L)}$ 的倍数，其中 $\nu_d(L)$ 表示 $L$ 含有的质因子 $d$ 个数。再注意到 $n - L$ 较小，考虑将质因子按 $d ^ {\nu_d(L)}$ 从大到小排序，每次检验后，检查 $d ^ {\nu_d(L)}$ 的积是否已经大于 $n - L$。若是，则 $x$ 一定在从 $1$ 出发的环上，不用继续检查。当 $L = 3\times 4\times 5\times 7$ 时，每个数只需检验至多 $3 + 1 = 4$ 次（对于 $n - L$ 的部分有 $\frac 1 2$ 常数），相当于 $\omega(L)$ 减少了 $1$，可以接受。对于更大的 $L$ 如 $480, 495$ 等也可以接受。

经检验，对于 CF 的所有测试数据，操作次数不超过 $1900$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int debug = 0;
constexpr int N = 500 + 5;

int qu;
int n, a[N];
int query(int u, int k, vector<int> S) {
  assert(++qu < 1900);
  if(debug) {
    cerr << "qid = " << qu << "\n";
    if(qu == 2001) exit(0);
  }
  cout << "? " << u << " " << k << " " << S.size() << " ";
  for(int it : S) cout << it << " ";
  cout << endl;
  if(debug) {
    while(k--) u = a[u];
    for(int it : S) if(u == it) return 1;
    return 0;
  }
  cin >> u;
  return u;
}
int suc(int u, int k) {
  int l = 1, r = n;
  while(l < r) {
    int m = l + r >> 1;
    vector<int> S;
    for(int p = l; p <= m; p++) S.push_back(p);
    if(query(u, k, S)) r = m;
    else l = m + 1;
  }
  return l;
}

void mian() {
  cin >> n;
  if(debug) {
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1, j = 1; i <= n; i++) cout << (j = a[j]) << " ";
    cout << "\n";
  }
  int p = suc(1, 1064), len = 1;
  vector<int> vis(n + 2), ban(n + 2);
  while(1) {
    int cur = 1, cnt = 0;
    while(1) {
      int pk = -1, nxt = 1e9;
      for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        ll v = 1ll * cur * i / __gcd(cur, i);
        if(v <= nxt) pk = i, nxt = v;
      }
      if(pk == -1 || cnt == 30) break;
      cur = nxt, vis[pk] = 1, cnt++;
    }
    if(!query(p, cur, {p})) {
      for(int i = 1; i <= n; i++) {
        if(cur % i == 0) ban[i] = 1;
      }
      continue;
    }
    for(int i = 1; i <= n; i++) {
      if(cur % i == 0 && !ban[i] && query(p, i, {p})) {
        len = i;
        break;
      }
    }
    break;
  }
  for(int &it : vis) it = 0;
  
  cerr << "------------------- len = " << len << "\n";
  vector<int> ans;
  if(len > 250) {
    vector<pii> pf;
    for(int i = 2, tmp = len; i <= tmp; i++) {
      if(tmp % i) continue;
      int tot = 1;
      while(tmp % i == 0) tmp /= i, tot *= i;
      pf.push_back({tot, i});
    }
    sort(pf.begin(), pf.end());
    reverse(pf.begin(), pf.end());
    for(int i = 1; i <= n; i++) {
      if(!query(i, len, {i})) continue;
      vis[i] = 1;
      int ok = 1, cur = 1;
      if(len < 420) shuffle(pf.begin(), pf.end(), rnd);
      for(pii it : pf) {
        if(query(i, len / it.second, {i})) ok = 0;
        if(!ok || (cur *= it.first) > n - len) break;
      }
      if(ok) ans.push_back(i);
    }
    for(int i = 1; i <= n; i++) {
      if(vis[i]) continue;
      if(query(i, 1064, ans)) ans.push_back(i);
    }
  }
  else {
    ans.push_back(p), vis[p] = 1;
    for(int i = 1; i <= len / 3 + 1; i++) {
      p = suc(p, 3);
      if(!vis[p]) ans.push_back(p), vis[p] = 1;
    }
    for(int i = 1; i <= n; i++) {
      if(vis[i]) continue;
      vector<int> K = {1064, 1065, 1066};
      shuffle(K.begin(), K.end(), rnd);
      for(int k : K) {
        if(query(i, k, ans)) {
          ans.push_back(i);
          vis[i] = 1;
          break;
        }
      }
    }
  }
  cout << "! " << ans.size() << " ";
  for(int it : ans) cout << it << " ";
  cout << endl;
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  int T = 1;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

正解就是求出环上一段可以接受的长度的点，然后倍增。有点像这场的 A2。[代码](https://codeforces.com/contest/1854/submission/216437720)。

---

## 作者：namelessgugugu (赞：3)

来点更图一乐的做法。

### 题意

这是一道交互题。

有 $n$ 个点，第 $i$ 个点有且仅有一条出边。

每个点的出边都被隐藏了，但是可以选定点 $u$，正整数 $k$ 和点集 $S$，询问从 $u$ 开始沿其出边走 $k$ 步，到达的点是否在 $S$ 中。

需要通过不超过 $2000$ 次询问求出有哪些点 $x$，使得存在一个点 $y$，它既可以从 $x$ 出发沿出边走若干步到达，也可以从 $1$ 出发沿出边走若干步到达。

$1 \leq n \leq 500$。

### 题解

显然图构成一颗内向基环树森林，所求即为点 $1$ 所在连通块的点集。

容易可以通过二分求出点 $u$ 走 $k$ 步后到达的点，需要 $9$ 次询问。由于 $9n$ 也只有 $4500$，并没有比 $2000$ 大特别多，所以可以猜测稍微卡卡常就行。

注意到如果已知该连通块上的环的点集 $C$，则可以对于剩下的每个点 $x$ 询问一次 $(x, n + 1, C)$ 求出答案。因此考虑先求出环上的点。

先求出 $1$ 走 $n + 1$ 步之后到达的点 $s$，这一定是个在环上的点。假设已知环长为 $l$，可以这样求出环：

* 进行 $\lceil \frac l 4 \rceil$ 次二分，第 $i$ 次求 $s$ 走 $4i$ 步后到达的点，令这些点为初始的 $C$；
* 对所有不在 $C$ 里的点 $x$ 询问其走 $2$ 步是否在 $C$ 中，是则加入 $C$；
* 基本同上一步，只是改成询问 $x$ 走 $1$ 步是否在 $C$ 中。

上述过程的大体思路就是为了减少二分次数，多跑几轮 $n$ 次询问的操作。可以发现这样求出来的 $C$ 一定包含所有环上点，还有一些连通块内的其他点，不会影响答案。

分析询问次数，只考虑环上的点的话，第一步需要 $2.25l$ 次询问，后两步分别需要 $0.75l$ 和 $0.5l$ 次询问，而环以外的点会在后两步以及最后计算答案时进行询问，需要 $3(n - l)$ 次操作，则总计需要 $3n + 0.5l$ 次询问，最坏也只需要 $3.5n$ 次，还有 $250$ 次询问的空余。

但是直接把环长当成 $n$ 会在 $l$ 较小时去世，所以需要用剩下 $250$ 次询问求解环长。注意到我们并不需要得知环长的具体值，只需要大致的估算。利用 BSGS 的思想，用 $7$ 次二分求出环上 $s$ 开始的 $8$ 个点，然后第 $i$ 次询问 $s$ 走 $8i$ 能不能走到这 $8$ 个点，能的话把 $8i$ 视作环长的近似值，这样需要不到 $150$ 次操作，因此实现多 $O(1)$ 次二分也是没问题的。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define FILEIO(filename) (freopen(filename ".in", "r", stdin), freopen(filename ".out", "w", stdout))
typedef long long ll;
typedef unsigned long long ull;
const int N = 505;
int n;
inline int query(int u, int k, std::vector<int> s)
{
    printf("? %d %d %d ", u, k, (int)s.size());
    for(int x : s)
        printf("%d ", x);
    putchar('\n'), fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}
inline int bs(int u, int k)
{
    int l = 1, r = n;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        std::vector<int> tmp;
        for (int i = l; i <= mid;++i)
            tmp.push_back(i);
        if(query(u, k, tmp))
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
inline int getlen(int u)
{
    std::vector<int> pre;
    int now = u;
    for (int i = 1; i <= 8;++i)
    {
        pre.push_back(now);
        now = bs(now, 1);
        if(now == u)
            return i;
    }
    for (int i = 1; i <= 70;++i)
        if(query(u, i * 8, pre))
            return i * 8;
    return -1;
}
bool vis[N];
int main(void)
{
    scanf("%d", &n);
    int st = bs(1, n + 1), len = getlen(st);
    int cnt = (len + 3) / 4;
    vis[1] = vis[st] = 1;
    for (int i = 0, now = st; i < cnt;++i, now = bs(now, 4))
        vis[now] = 1;
    std::vector<int> res;
    for (int i = 1; i <= n;++i)
        if(vis[i])
            res.push_back(i);
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && query(i, 2, res))
            vis[i] = 1, res.push_back(i);
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && query(i, 1, res))
            vis[i] = 1, res.push_back(i);
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && query(i, n + 1, res))
            vis[i] = 1, res.push_back(i);
    std::sort(res.begin(), res.end());
    printf("! %d ", (int)res.size());
    for(int x : res)
        printf("%d ", x);
    putchar('\n'), fflush(stdout);
    return 0;
}
```

---

## 作者：gdf_yhm (赞：2)

[CF1854D](https://www.luogu.com.cn/problem/CF1854D)

### 思路

题目等价于求 $1$ 的联通块大小。

可以 $\log n=9$ 次二分出一个点走 $k$ 步到哪里。有两种用法：走 $n+1$ 步得到环上的某个点和走 $1$ 步得到该点下一个点。

如果找到知道 $1$ 联通块的环是哪些点，就可以对每个不知道的点询问 $n+1$ 得知答案。先从 $1$ 二分 $n+1$ 找到一个环上点，再一直走知道走完一个环。步数与环长 $len$ 有关，$9\times len+500-len\le 4500$。

先找出一个点在 $1$ 联通块的环上，在环上二分 $124$ 次 $1$ 步找到环上连续的 $125$ 个点。对剩下 $375$ 个点找出 $125$ 步能到这 $125$ 个点之一的点。这时至少已知环上连续的 $250$ 个点，有一半的环已知，其他的点走 $n+1$ 步或 $n+1+250$ 步如果在联通块内则一定能到这一半的环。总步数 $9\times 125+375+2\times 250=2000$。如果环长不到 $250$，就直接 $500-len$ 步做完。

这么做的关键是环上连续点长度可以倍增，$500-len$ 步就可以把 $len$ 长的环倍增到 $len\times 2$。如果一开始二分少一些连续长度可以步数更小。

### code

```cpp
int n;
int id[maxn],tot;bool vis[maxn];
vector<int> a,b;
bool ask(int u,int len){
	printf("? %lld %lld %lld ",u,len,tot);
	for(int i=1;i<=tot;i++)printf("%lld ",id[i]);
	printf("\n");fflush(stdout);
	return read();
}
bool get(int u,int len,vector<int> a){
	printf("? %lld %lld %lld ",u,len,(int)a.size());
	for(int i:a)printf("%lld ",i);
	printf("\n");fflush(stdout);
	return read();
}
int find(int u,int len){
	a.clear();
	for(int i=1;i<=n;i++)if(!vis[i]||i==id[1])a.push_back(i);
	while(a.size()>1){
		int num=a.size()>>1;b.clear();
		while(num--)b.push_back(a.back()),a.pop_back();
		if(!get(u,len,a))swap(a,b);
	}
	return a.front();
}
void prinf(){
	sort(id+1,id+tot+1);
	printf("! %lld ",tot);
	for(int i=1;i<=tot;i++)printf("%lld ",id[i]);
	printf("\n");fflush(stdout);
}
void work(){
	n=read();
	a.clear(),b.clear();
	id[++tot]=find(1,n+1);vis[id[tot]]=1;
	for(int t=2;t<=125;t++){
		int p=find(id[tot],1);
		if(p==id[1])break;
		id[++tot]=p,vis[id[tot]]=1;
	}
	if(tot<125){
		for(int i=1;i<=n;i++)if(!vis[i]){
			if(ask(i,n+1)){
				id[++tot]=i;vis[i]=1;
			}
		}
		prinf();return ;
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(ask(i,125)){
			id[++tot]=i;vis[i]=1;
		}
	}
	if(tot<250){
		for(int i=1;i<=n;i++)if(!vis[i]){
			if(ask(i,n+1)){
				id[++tot]=i;vis[i]=1;
			}
		}
		prinf();return ;
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(ask(i,n+1)||ask(i,n+1+250)){
			id[++tot]=i;vis[i]=1;
		}
	}
	prinf();
}
```

---

## 作者：zzzYheng (赞：1)

#### 题意：

现在有一个隐藏的内向基环树森林，你可以进行如下交互：

- 给出 $x,k$ 和集合 $s$，交互库会告诉你 $x$ 跳 $k$ 步后到达的点是否在 $s$ 内。

你要用不超过 $2000$ 次交互得到 $1$ 号节点所在内向基环树的所有点。

数据范围：$n\le 500$。

#### 思路：

题目挺有意思，但不懂为什么要卡常。

首先注意到操作为询问 $x$ 跳 $k$ 步后是否在 $S$ 中，那么利用 $S$ 进行一个二分就可以做到 $\Theta(\log n)$ 次操作确定 $x$ 的跳 $k$ 步后到达的具体位置。将 $x$ 跳 $n$ 步就可以到达 $x$ 所在基环树的环上，然后一步一步地跳就可以使用 $\Theta(n\log n)$ 次操作确定整个基环了。那么再对每个点查询其跳 $n$ 步后是否在这个基环内即可。这样就能做到 $\Theta(n\log n)$ 次询问。

另一种 $\Theta(n\log n)$ 次的算法是通过倍增确定 $x$ 所在的连通块。首先将 $x$ 跳 $n$ 步跳到基环上，假设该点为 $rt$，然后进行倍增，第 $i$ 次将跳 $2^{i-1}$ 步会到达基环树上已知点的所有点加入基环树。显然 $i$ 轮后至少会将所有距离 $rt$ 小于 $2^{i}$ 的所有点加入基环树中，因此这个算法询问次数也是 $\Theta(n\log n)$。

考虑结合这两个算法，先使用算法一在基环上跳出一条长度为 $\frac{n}{B}$ 的链，然后使用算法二倍增至多 $\log{B}$ 轮就可以确定整个基环，再对每个点跳 $n$ 步看是否在已经确定的点集内可得到答案。询问次数为 $\Theta(\frac{n}{B}\log n+n\log B)$，取 $B=\log n$，得操作次数有界 $\Theta(n\log\log n)$。

但是直接实现这个算法大概需要 $2500$ 次操作，一个卡常方法是考虑上一轮倍增中已经确定了在基环树上的点这一轮就都不用再询问了，在基环还未完全确定时第 $i$ 轮倍增会新确定至少 $B2^{i-1}$ 个点，少于这个值就说明基环已经完全确定了，可以退出。这样取 $B=\frac{n}{4}$ 就可以卡到不超过 $2000$ 次了。

---

