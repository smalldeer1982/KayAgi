# 「Cfz Round 5」Zhòng shù

## 题目背景

> 我想要种一棵香蕉树 上面挂满我的所有祝福

## 题目描述

小 C 喜欢种树。

它种了一棵香蕉树，但是这棵树似乎需要人工维护才能生长。

因此，它经常会在树上的某一个位置挂上一些「祝福」。所谓「祝福」，其实就是一条链。

而有的时候树的一部分长得太好了，会导致整棵树长歪，所以它又不得不砍掉一部分。

小 C 还喜欢众数，所以它会经常问你所有树上结点的深度中同一个深度最多的出现次数。

具体来说，有一棵有根树，最初只有根结点 $1$，另外有一个变量 $n=1$。

有如下三种操作：

1. `x l k`：增加编号为 $n+1\sim n+lk$ 的结点以及边
$(x,n+1),(n+1,n+2),\dots,(n+l-1,n+l)$；$(x,n+l+1),(n+l+1,n+l+2),\dots,(n+2l-1,n+2l)$；$\dots$；$(x+n+(k-1)l+1),(n+(k-1)l+1,n+(k-1)l+2),\dots,(n+kl-1,n+kl)$。即在 $x$ 号结点下面挂了 $k$ 条长度为 $l$ 的链。这个操作执行之后 $n\gets n+kl$。
2. `x`：删除 $x$ 号结点及其子树。
3. （无参数）查询所有结点的深度中，出现最多的那个深度的出现次数。

## 说明/提示

#### 「样例解释 #1」

下面的图中，点的颜色代表被加入的时间。

![](https://s21.ax1x.com/2024/12/09/pAHk3Hf.png)

上图为经过三次 $1$ 操作（`1 1 2 3`，`1 6 2 2` 和 `1 7 1 4`）后的树。

![](https://s21.ax1x.com/2024/12/09/pAHklut.png)

上图为在刚才的基础上经过两次 `2` 操作（`2 12` 和 `2 13`）的树。

![](https://s21.ax1x.com/2024/12/09/pAHk1DP.png)

上图为刚才的基础上再经过一次 $1$ 操作（`1 3 1 2`）的树。

![](https://s21.ax1x.com/2024/12/09/pAHkGE8.png)

上图为刚才的基础上再经过两次 $2$ 操作（`2 7` 和 `2 3`）的树。

![](https://s21.ax1x.com/2024/12/09/pAHkMjI.png)

上图为刚才的基础上再经过一次 $1$ 操作（`1 5 2 3`）的树。

![](https://s21.ax1x.com/2024/12/09/pAHkJUS.png)

上图为经过所有操作后的树。

#### 「数据范围」

对于所有测试数据，保证：

- $1\le m\le 10^5$；
- $1$ 操作中的 $x$ 满足 $1\le x\le n$ 且 $x$ 号结点在树上依然存在，保证 $1 \le l,k \le 10^{18}$；
- $2$ 操作中的 $x$ 满足 $1<x\le n$ 且 $x$ 号结点在树上依然存在；
- 任意时刻的 $n$ 满足 $n\le 10^{18}$。

**本题采用捆绑测试。**

设操作过程中 $n$ 的最大值为 $k$。

- Subtask 0（10 points）：$k \le 5000$。
- Subtask 1（20 points）：$k \le 5 \times 10^5$。
- Subtask 2（20 points）：不存在 $2$ 操作。
- Subtask 3（20 points）：$1$ 操作中 $l$ 的值为 $1$。
- Subtask 4（30 points）：无特殊限制。

## 样例 #1

### 输入

```
23
3
1 1 2 3
3
1 6 2 2
3
1 7 1 4
3
2 12
3
2 13
3
1 3 1 2
3
2 7
3
2 3
3
1 5 2 3
3
2 6
3
2 5
3```

### 输出

```
1
3
5
6
5
5
6
4
3
5
3
2```

## 样例 #2

### 输入

```
16
1 1 4 3
3
1 2 3 3
3
1 10 1000000000 2
3
1 1000000021 1 10
3
2 1000000027
3
2 23
3
1 12 1 1
3
1 2000000033 100000 1000000000
3```

### 输出

```
3
6
8
12
11
7
8
1000000001```

## 样例 #3

### 输入

```
18
1 1 85 483
1 32607 44 379
2 45784
1 46178 133 40
3
1 13506 152 357
2 62124
3
1 70877 209 33
3
1 37299 429 158
3
1 31487 258 363
2 159051
3
2 227162
2 279608
3```

### 输出

```
902
1257
1257
1415
1778
1778```

## 样例 #4

### 输入

```
19
1 1 189019619 113958
2 800361853
1 422490453 494478 254349561
3
2 1152812283
2 1650380207
3
1 4033287043 23425848 3533684
2 2666277906
1 709388173 159264263 191915
3
2 3453785850
2 8487830948768
2 39677822722745
2 167837684014594
1 1534084935 1205975 21949299
1 151207136 41249553 693236
1 1121564684 68403 1385595730
3```

### 输出

```
254463518
254463517
254463516
1386594833```

# 题解

## 作者：int_R (赞：10)

我这写的也太详细了。

首先大概还是要维护一下树的结构的，不过显然不能全部维护，所以每次 $1$ 操作时直接把那 $k$ 个长度为 $l$ 的链用一个节点表示。

更具体的，我们应当对一个节点记录 $pos,l,k,dep$，表示这个节点代表的一众原树节点为 $k$ 个长度为 $l$ 的链，这些点的编号为 $[pos,pos+kl-1]$，每个链的深度在 $[dep,dep+l-1]$ 之间。

现在一个节点代表着若干条链，如果我们要对其中一个链的其中一个点做一些事情，那么这些链就并不完全一样了。我们只需要把这条将要操作的链从中 split 出来，它就只代表它自己了。

更具体的，设这个点表示了 $k$ 条链，将要进行操作的是第 $p$ 条链中的点，我们将这个点分成三个点分别代表第 $[1,p-1],[p,p],[p+1,k]$ 条链的信息。

还有一个问题是我们如何找到原树的第 $x$ 个点现在被哪个点表示，只需要全局维护一个 set 来找到所有点的 $pos$ 中小于等于 $x$ 中最大的即可。

那么 $1$ 操作就比较简单了，直接做。$2$ 操作的话我们可以暴力递归子树删掉。实际上要递归的是所有 $dep$ 大于等于 $x$ 点深度的儿子的子树，所以存儿子也要开一个 set。当然最后也要对本身修改一下。

然后我们好像还有一个查询操作，所有修改在深度上都是区间加的形式，动态开点线段树即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#define ll long long
using namespace std;
typedef pair<ll,int> P;
const int MAXN=3e5+10;
const int MAXT=1.3e7;
const ll INF=1e18;
int m,tot=1,fa[MAXN];ll n=1;
struct node{ll pos,l,k,d;}t[MAXN];
set <P> s,v[MAXN];
namespace T
{
    struct node{ll num,add;int ls,rs;}t[MAXT];int tot=1;
    inline void upd(int p,ll z)
        {t[p].num+=z,t[p].add+=z;}
    inline void push_down(int p)
    {
        upd(t[p].ls,t[p].add),upd(t[p].rs,t[p].add);
        t[p].add=0;return ;
    }
    inline void push_up(int p)
        {t[p].num=max(t[t[p].ls].num,t[t[p].rs].num);}
    void add(ll l,ll r,int p,ll x,ll y,ll z)
    {
        if(x<=l&&y>=r){upd(p,z);return ;}
        if(!t[p].ls) t[p].ls=++tot,t[p].rs=++tot;
        ll mid=(l+r)>>1;push_down(p);
        if(x<=mid) add(l,mid,t[p].ls,x,y,z);
        if(y>mid) add(mid+1,r,t[p].rs,x,y,z);
        push_up(p);return ;
    }
    inline void A(ll l,ll r,ll x){add(1,INF,1,l,r,x);}
}

inline int find(ll x)//找到对应节点
{
    auto it=s.lower_bound({x,MAXN});
    return prev(it)->second;
}

inline void create(int p,ll pos,ll l,ll k,ll d)//创建一个新节点
{
    t[++tot]={pos,l,k,d},s.insert({pos,tot});
    v[fa[tot]=p].insert({-d,tot});return ;
}

inline void split(int p,ll num)//分裂出来一条链
{
    ll pos=t[p].pos,l=t[p].l,k=t[p].k,d=t[p].d;
    if(num>1)
    {
        s.erase({pos,p}),create(fa[p],pos,l,num-1,d);
        s.insert({t[p].pos=pos+(num-1)*l,p});
    }
    if(num<k) create(fa[p],pos+num*l,l,k-num,d);
    t[p].k=1;return ;
}

void dfs(int p)//递归子树删除
{
    if(t[p].l) T::A(t[p].d,t[p].d+t[p].l-1,-t[p].k);
    s.erase({t[p].pos,p});for(P y:v[p]) dfs(y.second);
}

inline void insert(ll x,ll l,ll k)// 1 操作
{
    int p=find(x);ll num=(x-t[p].pos)/t[p].l+1;
    split(p,num),num=(x-t[p].pos)%t[p].l;
    create(p,n+1,l,k,t[p].d+num+1);
    T::A(t[p].d+num+1,t[p].d+num+l,k),n+=l*k;return ;
}

inline void erase(ll x)// 2 操作
{
    int p=find(x);ll num=(x-t[p].pos)/t[p].l+1;
    split(p,num),num=(x-t[p].pos)%t[p].l;
    auto it=v[p].begin();
    for(P now:v[p])
    {
        if(-now.first<=t[p].d+num) break;
        dfs(now.second),++it;
    }
    v[p].erase(v[p].begin(),it);
    T::A(t[p].d+num,t[p].d+t[p].l-1,-1);
    t[p].l=num;return ;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    t[1]={1,1,1,1},s.insert({1,1}),T::A(1,1,1);
    cin>>m;for(int op;m;--m)
    {
        cin>>op;ll x,l,k;
        if(op==1) cin>>x>>l>>k,insert(x,l,k);
        if(op==2) cin>>x,erase(x);
        if(op==3) cout<<T::t[1].num<<'\n';
    }
    return 0;
}
```

---

## 作者：Iniaugoty (赞：5)

### [P11488 「Cfz Round 5」Zhòng shù](/problem/P11488)

T4 怒码 3.22KB AK 月赛 Div.2。

我在这道题上感受到了厚重的历**史**的沧桑感。

注意到，有用的结点（操作中出现的 $x$），和本质不同的深度（添加的链很长，连续的深度，会有很大一部分，结点数量都相同），数量都只有 $O(m)$ 级别。显然离散化处理一下。

离线下来。先将操作中出现的所有 $x$ 离散化。

```cpp
// op[i], x[i], l[i], k[i] 是操作参数同题面
// vec 是一个 vector，存的 {n, i} 指第 i 次操作，添加最大结点为 n
// id[i] 和 q 是节点的离散化数组及长度
F(i, 1, m) {
  cin >> op[i];
  if (op[i] <= 2) cin >> x[i], id[++q] = x[i];
  if (op[i] == 1)
    cin >> l[i] >> k[i],
    vec.push_back({n += l[i] * k[i], i});
}
sort(id + 1, id + q + 1), q = unique(id + 1, id + q + 1) - id - 1;
```

然后对每个结点，取原树上最近的祖先为父亲，建树。过程中可以维护这些点在原树上的深度 $dep$。

```cpp
// b[i] 和 w 是深度的离散化数组及长度
// dep[i] 是 i 的深度，nl[i] 和 nr[i] 是添加 i 时的链头和链尾的深度，top[i] 是链头
F(i, 2, q) {
  auto [s, t] = *lower_bound(vec.begin(), vec.end(), (pii) {id[i], 0});
// vec 的元素显然递增，二分出 i 在哪次操作添加，和那次操作后的最大结点
  int f = lower_bound(id + 1, id + q + 1, x[t]) - id;
  top[i] = x[t] + (k[t] - (s - id[i]) / l[t] - 1) * l[t] + 1;
  if (top[i - 1] == top[i]) e[i - 1].push_back(i);
  else e[f].push_back(i);
// 如果前面有结点和 i 同一个链头，那它一定更小更浅，i 的最近祖先是 i - 1
// 否则，i 的最近祖先只能是那个添加链时的 x
  dep[i] = dep[f] + l[t] - (s - id[i]) % l[t];
  nl[i] = dep[f] + 1, nr[i] = dep[f] + l[t];
  b[++w] = dep[i];
}
```

有用的深度，只有每个有用结点的 $dep$，和每次操作 $1$ 的 $dep _ {x _ i} + 1, dep _ {x _ i} + l _ i$，深度也离散化掉。

```cpp
// ql[i] 和 qr[i] 指第 i 次操作添加的链的链头和链尾的深度
F(i, 1, m) if (op[i] <= 2) x[i] = lower_bound(id + 1, id + q + 1, x[i]) - id;
F(i, 1, m) if (op[i] == 1)
  b[++w] = dep[x[i]] + 1, b[++w] = dep[x[i]] + l[i];
sort(b + 1, b + w + 1), w = unique(b + 1, b + w + 1) - b - 1;
F(i, 1, m) if (op[i] == 1)
  ql[i] = lower_bound(b + 1, b + w + 1, dep[x[i]] + 1) - b,
  qr[i] = lower_bound(b + 1, b + w + 1, dep[x[i]] + l[i]) - b;
F(i, 2, q)
  dep[i] = lower_bound(b + 1, b + w + 1, dep[i]) - b,
  nl[i] = lower_bound(b + 1, b + w + 1, nl[i]) - b,
  nr[i] = lower_bound(b + 1, b + w + 1, nr[i]) - b;
```

查询有 $O(m)$ 次，肯定期待 $O(1)$ 或者 $O(\log m)$ 的复杂度。同时注意到添加 $k$ 条长为 $l$ 的链这种操作，就非常像，对 $dep$ 上长为 $l$ 的区间进行区间加 $k$。于是尝试用线段树去维护每个 $dep$ 的结点数量，现在至少需要区间加和求全局最值两个操作，并且由于离散化所以并不需要动态开点。

```cpp
// mx[i] 是区间 max，tag[i] 是加法懒标记
LL mx[N << 2], tag[N << 2];
void Pushup(int u) { mx[u] = max(mx[u << 1], mx[u << 1 | 1]); }
void Maketag(int u, LL k) { mx[u] += k, tag[u] += k; }
void Pushdown(int u) {
  if (tag[u])
    Maketag(u << 1, tag[u]),
    Maketag(u << 1 | 1, tag[u]),
    tag[u] = 0;
}
void Update(int ql, int qr, LL k, int l, int r, int u) {
  if (ql <= l && r <= qr) return Maketag(u, k);
  Pushdown(u); int mid = l + r >> 1;
  if (ql <= mid) Update(ql, qr, k, l, mid, u << 1);
  if (qr > mid) Update(ql, qr, k, mid + 1, r, u << 1 | 1);
  Pushup(u);
}
```

接下来考虑如何维护两种操作。

操作 $1$ 显然是对 $[ql _ i, qr _ i]$ 区间加 $k$ 就行了，并且记录一下在 $x _ i$ 进行的所有操作（因为接下来删点可能要把这些贡献减掉）。

操作 $2$ 首先有一个 naive 的想法，先把 $x _ i$ 所在的那个链上，它后面的点减掉，然后从 $x _ i$ dfs 下去，一个一个删过去，就是把操作 $1$ 的贡献减掉。

```cpp
// qu[u] 存的是在 u 上进行的操作 1 的 ql, qr 和 k
// vis[u] = 1 表示 u 已被删掉
void Dfs(int u) {
  for (auto [l, r, k] : qu[u]) Update(l, r, -k, 1, w, 1);
  vis[u] = 1, qu[u].clear();
  for (auto v : e[u]) if (!vis[v]) Dfs(v);
}

F(i, 1, m) {
  if (op[i] == 1)
    qu[x[i]].push_back({ql[i], qr[i], k[i]}),
    Update(ql[i], qr[i], k[i], 1, w, 1);
  else if (op[i] == 2)
    Update(dep[x[i]], nr[x[i]], -1, 1, w, 1), Dfs(x[i]);
  else cout << mx[1] << "\n";
}
```

但这样是错的，考虑两种情况，都有前提 $v$ 是 $u$ 的子结点，$v$ 已经被删掉，这次要删 $u$：

- $u, v$ 在同一条链上加进来。如果直接减 $u$ 链上后面的点，$v$ 后面这一部分显然会多减一遍，需要把它再加回来。

- 或者，$v$ 是在 $u$ 底下的链添加进来。如果直接减 $u$ 的操作 $1$ 贡献，也会把 $v$ 下面这一部分多减一遍，需要加回来。

然后在 dfs 里面加一行特判就可以了，主函数那一部分不用改。

有一种容斥的感觉（？）。

```cpp
void Dfs(int u) {
  for (auto [l, r, k] : qu[u]) Update(l, r, -k, 1, w, 1);
  vis[u] = 1, qu[u].clear();
  for (auto v : e[u])
    if (!vis[v]) Dfs(v);
    else Update(dep[v], nr[v], 1, 1, w, 1);
}
```

这很暴力是吗。但是每个点最多被访问两次，一次是删自己，一次是删父亲，是 $O(m)$ 级别的。然后每个点上的操作 $1$ 个数加起来也是 $O(m)$ 级别的。所以复杂度均摊下来是 $O(m \log m)$。

完整的代码就不放了~~太长了贴在最后太丑~~。

---

## 作者：shenxindi (赞：1)

发现并不需要用到所有的点，只需要用到修改操作中出现的点即可，其他点可以使用数据结构维护，称这些点为有用点，再称一个有用点 $u$ 为一个点 $v$ 的基准点，当且仅当 $v$ 被加入的时候被挂在了 $u$ 上。



设一个有用点的父亲为：原树上离它最近、且是它祖先的有用点。如果我们从每个有用点向它的父亲连一条边，我们就可以得到一棵点数不超过 $10^5$ 的新树。则我们可以把所有修改挂到树上的节点上。



发现一个点出现的时间是一段区间，考虑如何求出这段区间。首先由一个点的基准点可知区间的左端点，然后从这个基准点到新树的根的路径上所有有用点被删除的最小时间（如果有）就是区间右端点。



发现可以不对每个点求出时间区间再统计答案，而是用有用点挂着的修改操作的信息来一起统计答案。



设一个二维平面上的点 $(t,d)$ 的权值为 $t$ 时刻 $d$ 深度的原树上的点的个数，三元组 $(t,l,k)$ 为一个插入操作的时间和题面中的 $l,k$，一个有用点的 $et$ 为这个点被删除的时间（如果有）、$dep$ 为在原树上的深度。我们对新树dfs，然后维护区间左右端点 $b$ 和 $e$（区间为 $[b,e)$）。在根节点时 $b=1,e=m+1$。每到达一个节点 $u$，首先，如果 $u$ 有 $et$，就找到加入这个点的三元组和这个点的基准点 $v$，并将二维平面上左下角为 $(et_u,dep_u)$、右下角为 $(e,dep_v+l)$ 的矩形权值减 $1$（这个操作相当于一个插入操作的一条链的一部分被删除了，所以要部分减 $1$），然后 $e\gets et_u$。然后，我们遍历这个点挂着的插入操作，将二维平面上左下角为  $(t,dep_u+1)$、右下角为 $(e,dep_u+l)$ 的矩形权值加 $k$。从 $u$ 走到儿子 $v$ 前，要找到 $v$ 的基准点，更新 $b$。



~~发现 $b$ 好像没有什么用。~~



找到一个点的基准点是容易的，对所有插入操作进行二分即可。



考虑如何求出有用点的父亲。首先令每个有用点的父亲为它的基准点。然后对于所有有用点，找到原树上编号小于它且最大的有用点，然后判断一下是否是它的原树上的祖先即可。根据插入的链的编号规律，如果这个点是它的祖先，那么这个点一定是它新树上的父亲。



矩形加减直接离线下来扫描线即可。



[代码](https://www.luogu.com.cn/paste/v4ropf8b)太丑了，所以不直接放出来了。

---

