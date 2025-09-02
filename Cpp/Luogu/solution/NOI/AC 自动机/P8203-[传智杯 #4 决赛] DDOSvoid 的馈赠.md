# [传智杯 #4 决赛] DDOSvoid 的馈赠

## 题目描述

小智马上就要 AK（All killed，指使本场比赛的全部题目 AC）本场“传智杯”全国大学生 IT 技能大赛（决赛）然后离场了。临走前，DDOSvoid 打算给小智 $n$ 个字符串 $s_1, s_2, \dots, s_n$ 作为纪念。在本题中，我们将这 $n$ 个字符串称作「模板串」。

小智本身有 $m$ 个字符串 $t_1, t_2, \dots t_m$。在本题中，我们将这 $m$ 个字符串称为「查询串」。

DDOSvoid 的礼物不是无条件的，他有 $q$ 个问题，每个问题给定两个参数 $x, y$，要求小智回答他：一共有多少个模板串 $s_i$，满足 $s_i$ 既是 $t_x$ 的子串，也是 $t_y$ 的子串？

只有回答对这 $q$ 个问题，小智才能得到 DDOSvoid 馈赠的礼物。请你帮帮小智，回他 DDOSvoid 的问题。

我们称一个字符串 $t$ 是 $s$ 的子串，当且仅当将 $s$ 的开头若干个（可以为 0 个）连续字符和结尾若干个（可以为 0 个）连续字符删去后，剩下的字符串和 $t$ 相同。例如，我们称 `ab` 是 `abc` 的子串，但 `ac` 不是 `abc` 的子串。

## 说明/提示

### 数据规模与约定

对于全部测试点，保证 $1\leq n,m,q,|s_i|,|t_i| \leq 10^5$，且模板串的长度之和、查询串的长度之和均不超过 $10^5$，即 $\sum\limits_{i = 1}^n |s_i|,\sum\limits_{i = 1}^m|t_i| \leq 10^5$，其中 $|x|$ 表示字符串 $x$ 的长度。保证输入的字符串只含有小写字母，$1 \leq x\neq y \leq m$。

### 提示

**请注意常数因子对程序效率造成的影响**。

## 样例 #1

### 输入

```
3 2 1
a
b
c
ab
bac
1 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 3
aaba
baba
aba
ababa
aabab
babaa
1 2
1 3
2 3
```

### 输出

```
1
2
1```

# 题解

## 作者：xhgua (赞：5)

写一个复杂度较劣但是跑的挺快的做法。

首先建出 $s$ 的 AC 自动机，相当于求 $t_x$ 对应节点构成的虚树和 $t_y$ 对应节点构成的虚树的交集大小。

交集不好求，考虑用容斥原理转成求 $|T_x| + |T_y| - |T_x\cup T_y|$，即求虚树并。

首先我们考虑若知道 $t$ 在 AC 自动机上对应的节点 $u_1, u_2, \cdots u_k$，如何快速求出虚树的大小（即每个点到根对应链的并大小），沿用 [P5840 Divljak](https://www.luogu.com.cn/problem/P5840) 的做法，我们只需按 dfs 序排序后减去相邻两点 LCA 的贡献即可。不妨设 $|t_x| \leq |t_y|$，同样的，对于两个虚树的并，我们考虑将小串的节点插入大串中，具体地，我们对于小串的每个节点，二分找到它应该插在大串节点 dfn 序列的哪个位置，发现最多只会有 $\mathcal{O}(|t_x|)$ 个连续段，我们可以预处理这些连续段内部减去的贡献，并且加上插入时破坏的那部分大串的贡献即可，具体实现可以看代码。

这样子单次询问的时间复杂度即为 $\mathcal{O}(|t_x|\log |t_y|)$，如果对相同的询问记忆化，分析后可得总复杂度是 $\mathcal{O}(T\sqrt{q}\log T)$ 的，其中 $T$ 为 $\sum |t_i|$，已经可以通过本题。

不过我当时做题的时候并没有分析出这个复杂度，发现在 $|t_x|$ 和 $|t_y|$ 都很大时候这个做法较劣，考虑对 $t_x$ 的长度进行阈值分治。

令阈值为 $B$，当 $|t_x|\leq B$ 的时候我们跑上面那个做法，复杂度为 $\mathcal{O}(qB\log T)$，当 $|t_x| \gt B$ 时，这样的 $t$ 最多只有 $\mathcal{O}(\dfrac{T}{B})$ 个，我们考虑用 bitset 维护这些串是否包含 $s_i$，复杂度为 $\mathcal{O}(\dfrac{nT}{B})$，询问时直接把两个 bitset 与起来即可。

取 $B = \sqrt{\dfrac{nT}{q\log T}}$ 可得一个复杂度为 $\mathcal{O}(\sqrt{nqT\log T})$ 的做法，最慢点跑了 300ms。[Code](https://www.luogu.com.cn/paste/spwjle5c)。

---

## 作者：Saliеri (赞：4)

根号好题。前半部分思路来自我，后半部分来自 @abruce（adj.）。

___

建出 AC 自动机过后，问题变成了**虚树交**。

- 这一步如果不懂不建议你做这个题。

但是这个东西不是很好预处理与维护，于是我们考虑这样一个臭活：

设总串长（虚树大小和）是 $S$，询问次数是 $q$，两个虚树的大小是 $x,y$，如果我们可以在 $O(\bold{min}(x,y))$ 内回答一个询问，并将**询问记忆化**，那么总时间复杂度是 $S\sqrt q$。

- 证明：考虑能怎么卡你。取出前 $q$ 大的 pair 来询问，假设将虚树按大小从大到小排序依次为 $\{T_i\}$，那么至多给你卡到 $\sum_{i=1}^{O(\sqrt q)}i|T_i| \le O(S\sqrt q)$（考虑阶梯状求和即证）。

那么问题变成了设计算法以支持在 $O(\bold{min}(x,y))$ 的时间内回答询问。

一个暴力至极的思路是这样的：

- 观察到：任意到根链上关于 “子树内是否包含大虚树点” 有**单调性**。

- 因此，考虑枚举小虚树的叶子，找到其到根链上**最深的包含大虚树点的点**。
	
    - 这里需要使用**倍增**处理，于是带上了 $\log$。 

- 将所有这些点抽出来再做一次**树链并**（虚树权值和）就是答案。

	- 树链并中的 LCA 采用欧拉序 $O(1)$ 实现。 

复杂度 $O(S\sqrt q \log S)$，由于时间充裕，不排除可以过的可能性。

考虑如何去 $\log$。

将倍增那一步反过来看：如果我们**枚举大虚树**，预处理每一个点的到根链上最深的大虚树上点，就可以 $O(1)$ 了。

但是每枚举一个大虚树，我们都需要 $O(S)$ 的时间遍历整个 Trie 树，复杂度就爆了。

考虑**平衡**。我们真的有必要枚举所有大虚树吗？

如果一个虚树的 siz 大于我们设置的一个阈值 $B$，那么我们对它进行一次上述预处理。复杂度 $O(S\sqrt S)$。

- 为了减少常数，类似于 CF1039D，我们可以**使用 dfn 序上扫代替 dfs**。

这样如果询问中大虚树 siz $\ge B$，就可以不带 log。

否则两个虚树 siz 都 $\le B$，直接暴力在虚树上做复杂度也不超过 $O(B)$。

- 具体地，你可以归并合并点集过后暴力求交；

- 更好的实现是，对于每一个小虚树中的点，在大虚树中双指针找到其**前驱后继**，其对应的 “最深包含大虚树的祖先” 一定是其与前驱后继的 LCA 中深度较大的那个。

于是就做完了。复杂度 $O(S\sqrt S+S\sqrt q)$。

---

## 作者：DDOSvoid (赞：4)

对于模式串匹配问题，我们最容易想到的就是 AC 自动机，所以我们从 AC 自动机出发。

我们对于模板串建立 AC 自动机，然后考虑如何朴素的处理一次询问，下文为了方便我们定义 AC 自动机上一个点的树链为这个点到根的路径，这里的树是 AC 自动机的 fail 树

我们首先将在 AC 自动机上做匹配求出查询串 $x$ 和查询串 $y$ 的所有前缀的匹配节点，那么容易得到我们需要统计串 $x$ 的所有匹配节点的树链的并和串 $y$ 的所有匹配节点的树链的并，然后对这两者求交，求交所得到的节点的贡献的和就是我们一次询问的答案

现在我们考虑如何处理所有询问，首先考虑将询问离线，同时我们能够发现询问的一些可以利用的性质，下文为了方便我们令一次询问 $(x,y)$ 中长度较小的串为 $x$，同时称其为小串，长度较大的串为 $y$，同时称其为大串

我们考虑一个看似是暴力的东西，我们固定大串，并预处理一些信息，同时对于这个大串的所有询问，我们暴力枚举小串，即时间复杂度为小串的长度，我们现在证明这个东西的复杂度是可以接受的

对于一个长度为 $B$ 的小串，我们考虑枚举它的复杂度，下面默认将所有询问去重

如果 $B>\sqrt n$，那么 $B$ 最多只会被枚举 $O(\frac{n}{B})$ 次，那么这样一个 $B$ 的对于时间复杂度的贡献最多就是 $O(n\times \frac{n}{B}=n)$， 同时 $B$  只有 $O(\frac{n}{B}=\sqrt n)$ 个，所以这一部分的时间复杂度就是 $O(n\sqrt n)$

如果 $B<\sqrt n$，注意到询问只有 $O(n)$ 个，所以这一部分的时间复杂度也是 $O(n\sqrt n)$

那么现在我们需要考虑对于大串，我们需要预处理什么信息，同时又如何在枚举小串的时间复杂度内回答一次询问

我们继续考虑最初的暴力，我们需要求两个集合的并的交，考虑换一下顺序，我们预处理一个集合的并，然后对于另个一个集合中的每个点与之前求好的并求交，然后再并起来

顺着这个思路，我们不妨假设已经预处理好了大串，那么对于小串的每个点，它与大串的并显然是该点与大串所有节点中 $dfs$ 序相邻的两个点的 $lca$ 中深度较大的那个，下面这个图可能比较形象一点

[![b4FY6J.png](https://s1.ax1x.com/2022/03/10/b4FY6J.png)](https://imgtu.com/i/b4FY6J)

$A,C,D$ 表示大串的点，$B$ 是小串中的一个点，容易得到 $B$ 的树链与 $A,C,D$ 的树链的并，显然是 $F$（ $B$ 与 $A$ 的 $lca$），而不是 $E$ （$B$ 与 $C$ 的 $lca$）

那么求一个点 $dfs$ 序相邻的两个点，我们最先想到的是直接将小串和大串的点都按照 dfs 序排序之后做一个双指针，但这样的时间复杂度是大串的长度，是有可能被卡掉的（如果常数不是很差应该都能过）

于是我们再一次考虑根号分治，我们按照大串的长度来进行分治

如果大串的长度小于 $\sqrt n$，那么我们直接将排序后双指针即可

如果大串的长度大于 $\sqrt n$，我们考虑 $O(n)$ 预处理每个位置的左右第一个点，因为长度大于 $\sqrt n$ 的大串只有 $O(\sqrt n)$ 个，所以这样做的时间复杂度依然是 $O(n\sqrt n)$

所以到这里该问题就在 $O(n\sqrt n)$ 内顺利解决了，但是还有几点需要注意：

1. 注意到我们的做法显然依赖于每个点的 dfs 序，尽管以任何方式做 dfs 复杂度都是正确的，但是不同的方法可能会造成不同的常数
2. 求 lca 是否需要做到 $O(1)$？理论上确实需要，但是我们使用树剖并不会使程序跑得更慢（甚至更快），原因大概是因为树剖求 lca 本身就很快，同时树剖求出来的 dfs 序在普遍意义上更快

---

## 作者：yzy1 (赞：4)

暴力过了！

注：下文复杂度分析默认 $n,m,q$ 同阶。

考虑对 $s$ 建 AC 自动机，然后把每个 $t$ 往上面跑，预处理 $m$ 个 `bitset`，代表每个 $t$ 匹配了哪些 $s$。但是这样空间炸了，不过没关系，可以对 $s$ 分块。询问离线，一块一块做，这样每个 `bitset` 就只有 $O(\dfrac n B)$ 个 bit。空间复杂度下降为 $O(\dfrac{n^2}{wB})$。

查询的时候直接把俩 `bitset` 按位与起来，然后每块的 `.count()` 加一块即为答案。

时间复杂度 $O(\dfrac{n^2}w)$，但是它能过！

注意代码细节较多，实现有些麻烦。

```cpp
struct G {
  int h[N], tot;
  struct E {
    int t, n;
  } e[N];
  inline void Add(int f, int t) { e[++tot] = {t, h[f]}, h[f] = tot; }
  inline void Reset() { tot = 0, memset(h, 0, sizeof h); }
};
typedef bitset<400> BS;

struct Trie {
  int e[N][26], tot = 1, scnt, fil[N], dfn[N], tim, sz[N], son[N], tp[N], dep[N], fa[N], ed[N],
                vp[N];
  vector<int> p;
  G g, vg;
  bool vis[N];

  inline void Ins(const char *s, int n) {
    int u = 1;
    re (i, n) {
      int c = s[i] - 'a';
      if (!e[u][c]) e[u][c] = ++tot;
      u = e[u][c];
    }
    if (!vis[u]) p.push_back(u), vis[u] = 1;
    ed[++scnt] = u;
  }

  inline void AC() {
    rep (i, 0, 25)
      e[0][i] = 1;
    queue<int> q;
    q.push(1);
    while (q.size()) {
      int u = q.front();
      q.pop();
      rep (i, 0, 25)
        if (e[u][i])
          fil[e[u][i]] = e[fil[u]][i], q.push(e[u][i]);
        else
          e[u][i] = e[fil[u]][i];
    }
    rep (i, 2, tot)
      g.Add(fil[i], i);
    Dfs1(1), tp[1] = 1, Dfs2(1);
    sort(p.begin(), p.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
    vector<int> sta;
    sta.push_back(1);
    each (x, p) {
      if (x == 1) continue;
      int l = Lca(x, sta.back());
      if (l != sta.back()) {
        while (dfn[l] < dfn[sta[sta.size() - 2]])
          vg.Add(sta[sta.size() - 2], sta.back()), sta.pop_back();
        if (dfn[l] != dfn[sta[sta.size() - 2]])
          vg.Add(l, sta.back()), sta.back() = l;
        else
          vg.Add(l, sta.back()), sta.pop_back();
      }
      sta.push_back(x);
    }
    rep (i, 0, sta.size() - 2)
      vg.Add(sta[i], sta[i + 1]);
    Dfs4(1);
    memset(vis, 0, sizeof vis);
  }

  inline BS Ask(const char *s, int n) {
    int u = 1;
    re (i, n) {
      int c = s[i] - 'a';
      u = e[u][c];
      vis[vp[u]] = 1;
    }
    Dfs3(1, 0);
    BS res;
    re (i, scnt)
      if (vis[ed[i]]) res.set(i);
    Dfs3(1, 1);
    return res;
  }

  void Dfs1(int f) {
    dep[f] = dep[fa[f]] + 1;
    sz[f] = 1;
    nxt (i, f, g) {
      int t = g.e[i].t;
      fa[t] = f, Dfs1(t), sz[f] += sz[t];
      if (sz[t] > sz[son[f]]) son[f] = t;
    }
  }

  void Dfs2(int f) {
    dfn[f] = ++tim;
    if (!son[f]) return;
    tp[son[f]] = tp[f], Dfs2(son[f]);
    nxt (i, f, g) {
      int t = g.e[i].t;
      if (t == son[f]) continue;
      tp[t] = t, Dfs2(t);
    }
  }

  inline int Lca(int u, int v) {
    while (tp[u] != tp[v]) dep[tp[u]] > dep[tp[v]] ? u = fa[tp[u]] : v = fa[tp[v]];
    return dep[u] > dep[v] ? v : u;
  }

  void Dfs3(int f, bool b) {
    if (b) vis[f] = 0;
    nxt (i, f, vg) {
      int t = vg.e[i].t;
      Dfs3(t, b);
      if (!b) vis[f] |= vis[t];
    }
  }

  void Dfs4(int f) {
    if (vis[f]) vp[f] = f;
    nxt (i, f, g) {
      int t = g.e[i].t;
      vp[t] = vp[f], Dfs4(t);
    }
  }

  inline void Reset() {
    g.Reset(), vg.Reset();
    memset(e, 0, sizeof e), tot = 1, scnt = 0;
    memset(fil, 0, sizeof fil);
    memset(dfn, 0, sizeof dfn), tim = 0;
    memset(sz, 0, sizeof sz);
    memset(son, 0, sizeof son);
    memset(tp, 0, sizeof tp);
    memset(dep, 0, sizeof dep);
    memset(fa, 0, sizeof fa);
    memset(vis, 0, sizeof vis);
    p.clear(), p.push_back(1);
  }
} tr;

int n, m, qc, sz, bl[N], lbl[N], rbl[N], Ans[N];
string s[N], t[N];
pair<int, int> q[N];
BS ans[N];

void Init() {
  sz = sqrt(n);
  re (i, n) {
    bl[i] = (i - 1) / sz + 1;
    lbl[i] = (bl[i] - 1) * sz + 1;
    rbl[i] = min(bl[i] * sz, n);
  }
}

void Work(int x) {
  unordered_map<string, int> mp;
  tr.Reset();
  rep (i, lbl[x], rbl[x])
    tr.Ins(s[i].data() - 1, s[i].size());
  tr.AC();
  re (i, m) {
    if (mp[t[i]])
      ans[i] = ans[mp[t[i]]];
    else
      mp[t[i]] = i, ans[i] = t[i] != t[i - 1] ? tr.Ask(t[i].data() - 1, t[i].size()) : ans[i - 1];
  }
  re (i, qc)
    Ans[i] += (ans[q[i].first] & ans[q[i].second]).count();
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> qc;
  re (i, n)
    cin >> s[i];
  re (i, m)
    cin >> t[i];
  re (i, qc)
    cin >> q[i].first >> q[i].second;
  Init();
  ste (x, 1, n, sz)
    Work(x);
  re (i, qc)
    cout << Ans[i] << '\n';
  return 0;
}
```

---

## 作者：Prean (赞：2)

首先我们对所有的 $s$ 建出 ACAM，然后把所有 $s$ 的信息丢到上去。问题就变为了每个串 $t$ 对应一个大小为 $|t|$ 的点集，求两个点集的虚树的交的点权和。

虚树交这种东西看上去比较奇怪，考虑根号分治。

首先我们先使用 $O(n\log n)-O(1)$ 的 LCA。

考虑三种情况：大对大，小对大，小对小。

小对大很容易啊。直接把大的专门建一颗树，然后把所有 $s$ 的信息插上去。

对于每次查询一个小的串，直接在这颗树上面跑虚树就完了。

接下来考虑小对小。

可以建出虚树的并，然后标记每个节点是否包含第一个和第二个串，然后大力统计。

或者，也可以按照 dfn 序排序后大力归并。

大概就是说，对于一个节点 $u$，如果在这个点集的虚树上最深的被标记的祖先是 $z$ 的话，相当于要在这条路径上找一个最深的节点能被另外一个点集的虚树所包含。

可以发现归并的时候随随便便求一下就完了（

大对大。。。用两种方法预处理都可以。

根号分治的长度为 $\sqrt{\sum|S|}$，复杂度 $O(\sum|S|\log\sum|S|+(m+\sum|S|)\sqrt{\sum|S|})$。

不过我们需要求的是虚树的点权和而不是虚树本身，所以连虚树都可以不用写（（（
```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
typedef unsigned ui;
const ui M=1e5+5;
ui n,m,Q,B,lg[M<<1];char S[M],T[M],*s[M],*t[M];ui lens[M],lent[M];ui sums,sumt;
ui tot(1),fail[M],trans[M][26];ui dfc,d[M],dfn[M],lca[19][M<<1];
ui cnt,h[M];std::vector<ui>point[M];ui v[M];
ui LEN,id[M],ans[318][318];ui L,R,q[M];
struct Edge{
	ui v,nx;
}e[M];
inline void Add(const ui&u,const ui&v){
	e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
}
inline bool cmp(const ui&u,const ui&v){
	return dfn[u]<dfn[v];
}
inline void Insert(char*s,const ui&n){
	ui u(1);
	for(ui i=0;i<n;++i){
		const ui&c=s[i]-97;
		if(!trans[u][c])trans[u][c]=++tot;u=trans[u][c];
	}
}
inline ui Match(char*s,const ui&n){
	ui u(1);for(ui i=0;i<n;++i)u=trans[u][s[i]-97];return u;
}
inline void Find(char*s,const ui&n,std::vector<ui>&point){
	ui u(1);for(ui i=0;i<n;++i)point.push_back(u=trans[u][s[i]-97]);std::sort(point.begin(),point.end(),cmp);
}
inline void DFS(const ui&u){
	lca[0][dfn[u]=++dfc]=u;d[u]=d[fail[u]]+1;for(ui E=h[u];E;E=e[E].nx)DFS(e[E].v),lca[0][++dfc]=u;
}
inline ui Merge(const ui&u,const ui&v){
	return d[u]>d[v]?v:u;
}
inline ui merge(const ui&u,const ui&v){
	return d[u]>d[v]?u:v;
}
inline ui LCA(ui u,ui v){
	if((u=dfn[u])>(v=dfn[v]))u^=v^=u^=v;
	const ui&k=lg[v-u+1];return Merge(lca[k][u],lca[k][v-(1<<k)+1]);
}
inline void Build(){
	L=1;
	for(ui c=0;c<26;++c){
		if(trans[1][c])q[++R]=trans[1][c],fail[trans[1][c]]=1;
		else trans[1][c]=1;
	}
	while(L<=R){
		const ui&u=q[L++];
		for(ui c=0;c<26;++c){
			if(trans[u][c])q[++R]=trans[u][c],fail[trans[u][c]]=trans[fail[u]][c];
			else trans[u][c]=trans[fail[u]][c];
		}
	}
	for(ui u=1;u<=tot;++u)Add(fail[u],u);DFS(1);
	lg[0]=-1;for(ui i=1;i<=dfc;++i)lg[i]=lg[i>>1]+1;
	for(ui i=1;(1<<i)<=dfc;++i)for(ui j=1;j+(1<<i)-1<=dfc;++j){
		lca[i][j]=Merge(lca[i-1][j],lca[i-1][j+(1<<i-1)]);
	}
}
inline std::vector<ui>Merge(std::vector<ui>S,std::vector<ui>T){
	static std::vector<ui>ans;ui v,id(0);std::vector<ui>().swap(ans);
	for(ui i=0;i<S.size()-1;++i){
		v=1;
		for(ui j=id;j<T.size()&&dfn[T[j]]<dfn[S[i+1]];++j)v=merge(v,LCA(S[i],T[j]));
		if(v!=1)ans.push_back(v);while(id<T.size()&&dfn[T[id]]<dfn[S[i]])++id;
	}
	for(v=1;id!=T.size();++id)v=merge(v,LCA(S[S.size()-1],T[id]));if(v!=1)ans.push_back(v);
	return ans;
}
struct Tree{
	ui sum[M];bool vis[M];
	inline void DFS(const ui&u){
		sum[u]+=sum[fail[u]];for(ui E=h[u];E;E=e[E].nx)DFS(e[E].v);
	}
	inline void init(std::vector<ui>S){
		for(ui&u:S)vis[u]=true;
		for(ui i=R;i>=1;--i)vis[fail[q[i]]]|=vis[q[i]];
		for(ui i=1;i<=tot;++i)if(!vis[i])sum[i]=0;
		for(ui i=1;i<=R;++i)sum[q[i]]+=sum[fail[q[i]]];
	}
	inline ui Qry(std::vector<ui>S){
		ui ans=sum[1],v=1;for(ui&u:S)ans+=sum[u]-sum[LCA(v,u)],v=u;return ans;
	}
}tree[317];
signed main(){
	scanf("%u%u%u",&n,&m,&Q);s[0]=S;t[0]=T;
	for(ui i=1;i<=n;++i)scanf("%s",s[i]=s[i-1]+lens[i-1]),lens[i]=strlen(s[i]),sums+=lens[i];
	for(ui i=1;i<=m;++i)scanf("%s",t[i]=t[i-1]+lent[i-1]),lent[i]=strlen(t[i]),sumt+=lent[i];
	for(ui i=1;i<=n;++i)Insert(s[i],lens[i]);Build();B=ceil(sqrt(sumt));
	for(ui i=1;i<=m;++i)if(lent[i]>=B)id[v[i]=++LEN]=i;
	for(ui i=1;i<=m;++i)Find(t[i],lent[i],point[i]);
	for(ui u=1;u<=tot;++u)point[0].push_back(u);
	for(ui i=1;i<=n;++i){
		const ui&u=Match(s[i],lens[i]);
		for(ui k=0;k<=LEN;++k)++tree[k].sum[u];
	}
	for(ui i=0;i<=LEN;++i)tree[i].init(point[id[i]]);
	for(ui i=1;i<=LEN;++i)for(ui j=i+1;j<=LEN;++j){
		if(lent[id[i]]>lent[id[j]])ans[i][j]=ans[j][i]=tree[i].Qry(point[id[j]]);
		else ans[i][j]=ans[j][i]=tree[j].Qry(point[id[i]]);
	}
	while(Q--){
		ui x,y;scanf("%u%u",&x,&y);if(lent[x]>lent[y])x^=y^=x^=y;
		if(v[x]&&v[y])printf("%u\n",ans[v[x]][v[y]]);
		else if(!v[x]&&v[y])printf("%u\n",tree[v[y]].Qry(point[x]));
		else printf("%u\n",tree[0].Qry(Merge(point[y],point[x])));
	}
}
```

---

## 作者：lzyqwq (赞：2)

二模复活赛打赢了限时回归。但是人傻常熟大，正解没 `bitset`  暴力快.jpg。

给出一种 SA 做法。默认字符串总长、$n,m,q$ 同阶。

考虑将所有串用分隔符拼一起后缀排序，然后对于每个排名为 $i$ 的后缀，记录 $c_i$ 表示它来自哪个字符串。对于一个模板串 $s_i$，二分 + ST 表求出包含它的后缀排名区间 $[l_i,r_i]$。那么对于 $(x,y)$ 这个询问，就是求有多少个 $i$，满足 $c$ 数组 $[l_i,r_i]$ 这个区间内出现了 $x,y$ 这两种权值。

其实来自分隔符和查询串的后缀是没用的，因此可以在 $c$ 数组中删去这些位置。记新数组为 $C$。在新数组上，记 $[L_i,R_i]$ 表示 $C$ 中排名在 $[l_i,r_i]$ 内的后缀的区间。那么就是对于 $C$，求有多少个 $[L_i,R_i]$ 内出现了 $x,y$ 两种权值。因为 $C[L_i,R_i]$ 就是 $c[l_i,r_i]$ 删去一些不可能为 $x,y$ 的位置，因此在 $C[L_i,R_i]$ 中一定也出现了 $x,y$。

将 $c$ 转化成 $C$ 纯粹是为了卡常。

考虑转化后的问题，记 $\text{cnt}_x$ 表示 $x$ 在 $C$ 中的出现次数。不妨令 $\text{cnt}_x\le \text{cnt}_y$，不符则交换两者即可。接下来考虑钦定 $[L_i,R_i]$ 最左边的 $x$ 是哪一个，将每种情况的数量相加。

遍历 $C$ 中 $x$ 的位置 $j$，记它左边最后一个 $x$ 的位置为 $p_1$，左边最后一个 $y$ 的位置为 $p_2$，右边第一个 $y$ 的位置为 $p_3$。

首先需要满足 $L_i\le j\le R_i$。由于 $j$ 是最左边的 $x$，因此应满足 $L_i>p_1$。接下来考虑 $[L_i,R_i]$ 内是否存在一个比 $j$ 位置更左的 $y$，然后将两种情况的个数相加。

若存在，则应满足 $L_i\le p_2$；否则应满足 $p_2<L_i$，$R_i\ge p_3$。容易证明如果满足上述条件区间内一定存在 $x,y$。否则，因为 $(p_2,p_3)$ 内不存在 $y$，$[L_i,R_i]$ 就不满足该情况下的条件。

那么上面讨论的这些情况的答案全部都是二维数点，容易解决。

问题是暴力遍历 $x$ 的所有位置真的能接受吗？

考虑将 $\mathcal{O}(n)$ 个询问去重。若 $\text{cnt}_x\le \sqrt{n}$，则最多带来 $\mathcal{O}(n\sqrt{n})$ 个询问。否则，考虑那些 $\text{cnt}_x>\sqrt{n}$ 的询问的 $y$，此时只有 $\mathcal{O}(\sqrt{n})$ 个本质不同的 $y$。对于这些 $y$，和它构成询问的每个 $x$ 会带来 $\mathcal{O}(\text{cnt}_x)$ 个询问。而因为去过重，因此这些 $x$ 都是不同的。因此 $\text{cnt}_x$ 的和不超过 $\mathcal{O}(n)$，所以询问数量还是 $\mathcal{O}(n\sqrt{n})$ 个。

那么变成 $\mathcal{O}(n)$ 个点 $\mathcal{O}(n\sqrt{n})$ 个询问的二维数点，且都是 3-side 矩形，扫描 1-side 那一侧，剩下一维维护前缀和，使用 $\mathcal{O}(\sqrt{n})$ 区间加，$\mathcal{O}(1)$ 单点查的分块即可做到 $\mathcal{O}(n\sqrt{n})$。

还有一个问题，怎么快速求出 $p_2,p_3$？考虑离线，对于每一种 $y$ 单独求解。维护此时每个位置对应的 $p_2,p_3$，那么对于一个 $y$ 的位置 $j$，它可以对它后面位置的 $p_2$ 和它前面位置的 $p_3$ 产生贡献。分别使用 $\mathcal{O}(\sqrt{n})$ 区间取 $\min/\max$，$\mathcal{O}(1)$ 单点查的分块维护，由于每个 $y$ 做一次，因此 $C$ 中每个位置至多带来一次区间修改，而单点查询数和上面询问数同阶，因此这部分仍是 $\mathcal{O}(n\sqrt{n})$。

那么我们得到了一个时空都是 $\mathcal{O}(n\sqrt{n})$ 的做法，空间爆炸。原因是存不下那么多询问。可以考虑设置一个阈值 $B$，每产生 $B$ 个询问就数一次点并清空。这样修改部分常数会变大因为每数一次点就要修改一次。但是空间的问题解决了，那部分常数也可以忽略不计。

事实上 $B$ 取 $10^7$ 左右可以通过本题。

[AC Link](https://www.luogu.com.cn/record/161217411)

[Code](https://www.luogu.com.cn/paste/uck4twyf)

---

## 作者：Tachibana_Kimika (赞：1)

### 题目解析

每次询问给定 $i,j$，询问有多少模式串 $s_k$ 满足既是匹配串 $t_i$ 又是匹配串 $t_j$ 的子串。

这种多模式串问题，我们首先建出 $s$ 的 AC 自动机，然后变成了求 $t_i$ 和 $t_j$ 的交。我们发现如果复杂度基于 $t$ 的长度非常不好处理，再加上题目给定 $\sum t$ 的范围，所以我们考虑根号分治。我们设 $t_i$ 长度大于 $t_j$。

先考虑 $t_i$ 长度小于 $\sqrt n$ 的情况。显然的，我们可以将 $t_i$ 和 $t_j$ 的每个在 AC 自动机上的点按照 dfn 序排序，然后双指针扫一遍，每次统计他们的 lca，再容斥一手就行了。因为长度是 $\sqrt n$，所以每次询问复杂度是 $\sqrt n$。

如果 $t_i$ 长度大于 $\sqrt n$ 呢？这么扫就是错的了，因为每次询问不同的 $t_j$ 的时候都要扫一遍这个很长的 $t_i$，所以均摊就是每次 $O(n)$，显然不行啊。既然瓶颈是 $t_i$ 每次都要扫，而且都是一样的，我们考虑离线。我们创新地把一个 dfn 值对应的左右的 $t_i$ 点全部预处理了，这个是 $O(n)$ 的，然后每次扫 $t_j$ 的点就可以了，算 lca 的时候就跟左右并一下即可。因为 $\sum t_j$ 是 $O(n)$ 的，再加上最多只有 $\sqrt n$ 个 $t_i$，所以复杂度是 $n\sqrt n$，完全没问题。

根本不需要什么 $O(1)$ lca 的科技，跑的还没树剖快。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int maxn=2e5+10;

int tr[N][26];
int fail[N],val[N],cnt=1;
int rt=1;

inline void insert(string s){
	int u=rt;
	for(int i=0;i<s.size();i++){
		int v=s[i]-'a';
		if(tr[u][v]==1) tr[u][v]=++cnt;
		u=tr[u][v];
	}
	val[u]++;
}

inline void build(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(tr[rt][i]!=1){
			q.push(tr[rt][i]);
			fail[tr[rt][i]]=rt;
		}
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<26;i++){
			if(tr[u][i]!=1) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i]=tr[fail[u]][i];
		}
	}
}//以上都是 ac 自动机

vector<int>G[N];
int dis[N],dfn[N];
int cnt1;

int siz[N],dep[N],son[N],fa[N];
int top[N];

void dfs1(int u,int f){
	siz[u]=1;
	dis[u]+=val[u];
	for(auto v:G[u]){
		if(v==f) continue;
		dep[v]=dep[u]+1; fa[v]=u; dis[v]+=dis[u]; dfs1(v,u); siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}

void dfs2(int u,int tp){
	top[u]=tp; dfn[u]=++cnt1;
	if(!son[u]) return;
	dfs2(son[u],tp);
	for(auto v:G[u]){
		if(v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}

inline int LCA(int u,int v){
	if(!u||!v) return 0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}//树剖lca

char t[N];
int pos[N];
vector<int>a[N],D[N];
map<pair<int,int>,int>mp;
int ans[N],Q[N];

int vis[N],L[N],R[N];

inline void fake_main(){
	int n,m,q; cin>>n>>m>>q;
	for(int i=1;i<=1e5;i++){
		for(int j=0;j<26;j++){
			tr[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++){
		string s; cin>>s;
		insert(s);
	}
	build();
	for(int i=1;i<=cnt;i++) G[fail[i]].push_back(i);//建fail树
	dfs1(1,0); dfs2(1,1);
	
	for(int i=1;i<=m;i++){
		cin>>t+pos[i];
		pos[i+1]=pos[i]+strlen(t+pos[i]);
	}
	int len=pos[m+1];
	int B=sqrt(len),tot=0;
	
	for(int i=1;i<=q;i++){
		int x,y; cin>>x>>y;
		if(pos[x+1]-pos[x]>pos[y+1]-pos[y]||(pos[x+1]-pos[x]==pos[y+1]-pos[y]&&x>y)){//把短的离线到长的ti下面
			swap(x,y);
		}
		if(mp.find({x,y})==mp.end()) mp[{x,y}]=++tot;
		Q[i]=mp[{x,y}]; a[y].push_back(x);
	}
	for(int i=1;i<=m;i++){//预处理每个t上每个点的dfn序
		int u=rt; 
		for(int j=pos[i];j<pos[i+1];j++){
			u=tr[u][t[j]-'a'];
			D[i].push_back(u);
		}
		sort(D[i].begin(),D[i].end(),[](int a,int b){
			return dfn[a]<dfn[b];
		});
		D[i].erase(unique(D[i].begin(),D[i].end()),D[i].end());//求得是整个 t 的并，和顺序没关系，直接排序去重了先。
	}
	int sqrtsum=0; 
	for(int u=1;u<=m;u++){
		if(!a[u].size()) continue;
		if(pos[u+1]-pos[u]<=B){//小于根号n，直接双指针跑
			for(auto v:a[u]){
				int p=0; vector<int>tmp;
				for(auto t:D[v]){
					while(p<D[u].size()&&dfn[D[u][p]]<=dfn[t]) ++p;
					int x,y;
					if(p>0) x=LCA(t,D[u][p-1]); else x=0;
					if(p<D[u].size()) y=LCA(t,D[u][p]); else y=0;
					tmp.push_back(dis[x]>dis[y]?x:y);
				}
				int k=dis[tmp[0]];
				for(int i=1;i<tmp.size();++i){
					k+=dis[tmp[i]]-dis[LCA(tmp[i-1],tmp[i])];
				}
				ans[mp[{v,u}]]=k;
			}
		}else{
			memset(vis,0,sizeof vis);
			for(auto t:D[u]){
				vis[dfn[t]]=t;//预处理t上每个点的dfn所在位置
			}
			int tv=0;
			for(int i=1;i<=cnt;++i){//预处理每个dfn的左右最近的t上的点
				if(vis[i]) tv=vis[i];
				L[i]=tv;
			}
			tv=0;
			for(int i=cnt;i;--i){
				if(vis[i]) tv=vis[i];
				R[i]=tv;
			}
			for(auto v:a[u]){
				vector<int>tmp;
				for(auto t:D[v]){
					int x=LCA(t,L[dfn[t]]),y=LCA(t,R[dfn[t]]);//直接调用刚才跑好的lr数组，不用双指针扫ti了。
					tmp.push_back(dis[x]>dis[y]?x:y);
				}
				int k=dis[tmp[0]];
				for(int i=1;i<tmp.size();i++){
					k+=dis[tmp[i]]-dis[LCA(tmp[i-1],tmp[i])];
				}
				ans[mp[{v,u}]]=k;
			}
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[Q[i]]<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：zhouyuhang (赞：1)

显然无论如何需要先建出关于 $s$ 的 AC 自动机。不难发现答案即为 fail 树上的虚树交中所有点权之和（点权即为在此结束的 $s$ 数量）。

考虑将长度较小的 $y$ 挂到长度较大 $x$ 上离线，不难发现如果能够在 $O(y\text{ polylog})$ 的复杂度内解决一次询问，则经典结论是记忆化后总复杂度是 $O(n\sqrt n\text{ polylog})$。

而 $\rm polylog$ 的做法是容易的。考虑对于 $y$ 中的每个点，找出其所有祖先中最深的在 $x$ 虚树上的点，并对这些新点再建虚树。剖一遍后维护所有重链上最深的在 $x$ 虚树上的点是什么即可，一只 $\log$。

考虑怎么不带 $\log$。再次使用根分（上一次是记忆化所有带来的自然根分），如果 $x$ 的长度大于阈值 $B$，那么考虑 dfs 整颗树处理出所有点的答案；否则抽出 $x,y$ 所有点的 dfn 序，双指针维护 $y$ 的每个 dfn 序在 $x$ dfn 中的前驱后继，则其所有祖先中最深的在 $x$ 虚树上的点即为与这两点 lca 中深度较大者。使用 $O(1)$ LCA 容易做到 $O(n\sqrt n)$。

---

## 作者：TernaryTree (赞：0)

题目大意：给定 $n$ 个串 $s_{1\sim n}$ 和 $m$ 个串 $t_{1\sim m}$。$q$ 次询问，每次给定 $x,y$，求有多少 $s_i$ 在 $t_x$ 和 $t_y$ 中都有出现过。$n,m,q,\sum|s_i|,\sum|t_i|\le 10^5$。

---

典题？

首先对 $s_{1\sim n}$ 建出 ACAM。定义 $e_i$ 表示 $s_i$ 在 ACAM 上的最终结点，$ed_i$ 表示有多少字符串结束于结点 $i$。

一个经典的结论是：$s_i$ 在 $t$ 中出现过，当且仅当在这个 ACAM 上，$t$ 依次在 AC 图（即 ACAM 的 `ch` 数组）上转移，经过的所有结点中，存在一点 $u$ 位于 $e_i$ 在 fail 树上的子树中。

定义 $T_i$ 表示 $t_i$ 沿 AC 图依次转移经过的结点的不可重集合。

根据这个结论，我们可以将一次询问转化为：对 fail 树上一类点的 $ed_i$ 求和，要求满足其子树内同时存在两点 $u,v$ 满足 $u\in T_x$ 且 $v\in T_y$（$u,v$ 可以重合）。

考虑根号分治，不妨设定一个阈值 $B$，由 $x,y$ 的对称性可令 $|T_x|\ge|T_y|$。接下来分类讨论两种情况：

- $|T_y|\le |T_x|\le B$

  考虑询问的时候直接暴力做，对 $T_x\cup T_y$ 建出虚树，每条边的边权是原树上两端点的上开下闭（即不包括最顶端结点）的链的 $ed_i$ 之和，然后直接在虚树上 dfs，若一个点子树内同时存在 $T_x$ 和 $T_y$ 的点，就将这个点上面的边的边权累计进答案。
  
  这部分在线回答询问，复杂度为 $\Theta(B\log(\sum |s_i|))$。
  
- $|T_x|\gt B$

  考虑所有询问之前全部把这类的答案预处理出来。利用个数少的性质，这样的 $x$ 最多只有 $\dfrac{\sum|t_i|}{B}$ 个。对于这 $\dfrac{\sum|t_i|}{B}$ 个 $x$，首先处理出 fail 树上哪些点子树内存在 $T_x$ 的点打上标记。再对于每个 $x$ 分别去枚举 $1\le y\le m$，建 $T_y$ 的虚树，虚树边权为原树上两端点的上开下闭链中被标记的点的 $ed_i$ 之和，此时 $ans_{x,y}$ 即为虚树上的边权和。
  
  优化 $1$：注意到我们不必每次枚举 $x$ 再枚举 $y$ 时都去建 $T_y$ 的虚树，只要在此之前处理出每个 $T_y$ 的虚树即可。
  
  优化 $2$：我们不必真的把虚树建出来，我们所要的只是边权和，所以用一个数组去记录 $T_y$ 的虚树所有边的两个端点即可，这样实现起来更加方便，同时节省空间。
  
  这部分复杂度为 $\Theta(\sum{|t_i|\log |t_i|}+\dfrac{(\sum{|t_i|})^2}{B})$。
  
总复杂度为 $\Theta(qB\log(\sum |s_i|)+\sum{|t_i|\log |t_i|}+\dfrac{(\sum{|t_i|})^2}{B})$。由均值不等式，当 $B$ 取 $\sqrt{\dfrac{(\sum{|t_i|})^2}{q\log(\sum |s_i|)})}=\dfrac{\sum{|t_i|}}{\sqrt{q\log(\sum |s_i|)}}$ 时最优，此时总复杂度是 $\Theta({\sqrt{q\log(\sum |s_i|)}}{\sum{|t_i|}}+\sum{|t_i|\log |t_i|}$。由于 $n,m,q,\sum|s_i|,\sum|t_i|$ 同阶可简记为 $n\sqrt{n\log n}$。代码里的 LCA 使用 dfs 序 $\Theta(n\log n)-\Theta(1)$ LCA，详见 [Alex_Wei 的博客：冷门科技 —— DFS 序求 LCA](https://www.luogu.com.cn/blog/AlexWei/leng-men-ke-ji-dfs-xu-qiu-lca)。因为给了 4s 时限所以能过，~~理论上卡常可以卡进 1s~~。

[Code](https://www.luogu.com.cn/paste/thjk2q8x)。

---

