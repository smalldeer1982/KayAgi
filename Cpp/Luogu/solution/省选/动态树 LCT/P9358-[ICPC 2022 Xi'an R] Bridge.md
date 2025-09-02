# [ICPC 2022 Xi'an R] Bridge

## 题目描述

Erathia 大陆上有 $n$ 个国家，从 $1$ 到 $n$ 编号。每个国家可以看成由 $m + 1$ 个结点组成的链，结点从 $1$ 到 $m + 1$ 编号。结点 $(a, b)$ 和 $(a, b + 1)$ 由一条街道连接，其中 $(a, b)$ 表示国家 $a$ 的第 $b$ 个结点。一开始，国家之间没有桥。

你需要处理 $q$ 个操作：

- $1\ a\ b$（$1\leq a < n$，$1\leq b\leq m$）：在 $(a, b)$ 和 $(a + 1, b)$ 之间建造一座桥。**保证每个结点最多和一座桥相连**。
- $2\ a$（$1\leq a\leq n$）：一名英雄走过 Erathia 大陆。他从 $(a, 1)$ 出发。如果这名英雄当前在结点 $(x, y)$ 且有一座未被访问过的桥与之连接，那么他会走过这个桥到达桥的另一端，否则他会走到 $(x, y + 1)$。一旦他到达某个国家的第 $m + 1$ 个结点，他就会停下来。注意两个询问之间的 “未被访问过的桥” 是独立的。

你的任务是对每个操作 $2$ 求出英雄最终所在的国家。

$1\leq n, m, q\leq 10 ^ 5$。

## 样例 #1

### 输入

```
3 4 13
2 2
1 1 3
2 1
2 2
2 3
1 2 4
2 1
2 2
2 3
1 2 1
2 1
2 2
2 3
```

### 输出

```
2
2
1
3
3
1
2
3
2
1
```

# 题解

## 作者：一扶苏一 (赞：6)

# 【splay】【P9358】 Bridge

## Analysis

以下是赛时的思考过程。

我们把从某个城市的 $1$ 号结点出发按照规则最终到达某个城市的 $(m + 1)$ 号结点所经过的**结点**集合称为一条路径。

一个观察是，起点和终点总是一一对应的。换句话说，一个起点对应唯一一个终点，而一个终点也唯一对应一个起点。进一步画图可以发现，添加一座桥其实相当于交换两个路径的起点对应的的终点。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gbfxc5s8.png)

图中标有相同字母的两个结点对应一组配对的起终点。

不妨假定这个结论是对的，我们将在下面给出维护方法后自然地发现这个结论的正确性。这个观察直接启示我们尝试把每条路径都维护出来。显然每条路径都是一条由结点构成的链，添加一座桥“大致”就相当于交换两条路径的后半部分。这个东西大致可以用 splay 做。之所以是“大致”，是因为添加一座桥以后，桥连接的两个结点将同时存在于两条路径上。这个结构不是很能方便地用 splay 维护出来，我们更希望每个点唯一地对应一条路径。

观察添加一座桥连接 $x$ 和 $y$ 会发生什么：假设 $x$ 的前驱结点是 $u$，$y$ 的前驱节点是 $v$。那么加了桥后，$u$ 将沿 $x$ 走到 $y$；$v$ 将沿 $y$ 走到 $u$。也就是说，一座桥的本质是交换 $x$ 和 $y$ 的前驱所连接的结点。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/x20zz7co.png)
不考虑结点个数，我们可以很轻松地按用 splay 维护上右图中的每条链：给每条链开一个 splay，其中序遍历对应从起点到终点的路径。对于一个连接 $x,y$ 的桥，我们把 $x$ 和 $y$ 分别 splay 到对应的树根，然后交换两棵 splay 的右子树即可。

对于一次从 $(a,1)$ 出发的查询，只需要找到这个结点所属的 splay，然后找到这棵 splay 最后一个点，查询它所属的国家即可。

最后一个问题是，一共有 $O(nm)$ 个结点，把它们一开始都建出来是不可接受的。但是注意到大部分连续的节点本质相同且自始至终不会被操作到，可以把一段连续相同的区间缩成 splay 上一个点。每次用到区间内一个点时，把这个区间拆成两个区间（两个点）就可以了。具体来说，一开始每棵 splay 都只有一个点 $[1,m+1]$，第 $a$ 棵树的这个点对应 $(a,1)$ 到 $(a,m + 1)$ 共 $m + 1$ 个结点。当某次需要用到 $(a,b)$ 这个结点时，找到 $(a,b)$ 所在的区间 $[l,r]$，然后把区间分成 $[l, b - 1]$ 和 $[b, r]$ 两个点，再插入 splay 即可。此时只需要把 $[l,b - 1]$ 转到根再访问其右子树，就是我们需要交换的部分。

初始时，splay 只有 $O(n)$ 个结点。每次操作至多增加两个结点，一共增加 $O(q)$ 个结点，所以 splay 结点总数是 $O(n + q)$。

最后是经典结论，多个总节点数为 $O(n)$ 的 splay 互相修改结构（把某棵 splay 的一部分插入到另一棵 splay 上），其 splay 操作的均摊复杂度依然是 $O(\log n)$。证明思路上可以考虑一次交换子树的操作只会影响两棵树根节点的势能，然后得到总势能的改变量一定是个常数。因为比较繁琐且不是做法的核心，在此略去。

## Code

```cpp
#include <map>
#include <iostream>

const int maxn = 100005;

struct Node {
  Node *fa, *ch[2];
  int bel;

  Node():fa(nullptr), bel(0) {
    ch[0] = ch[1] = nullptr;
  }

  inline int getRela(Node *u) {
    return fa->ch[1] == u;
  }

  void rotate(int x) {
    auto nt = ch[x];
    ch[x] = nt->ch[x ^ 1];
    nt->ch[x ^ 1] = this;
    if (fa) fa->ch[getRela(this)] = nt;
    nt->fa = fa;
    fa = nt;
    if (ch[x]) ch[x]->fa = this;
  }

  void splay() {
    while (fa != nullptr) {
      auto pa = fa->fa;
      if (pa == nullptr) {
        fa->rotate(getRela(this));
      } else {
        int x1 = getRela(this), x2 = fa->getRela(fa);
        if (x1 == x2) {
          pa->rotate(x1);
          fa->rotate(x2);
        } else {
          fa->rotate(x1);
        }
      }
    }
  }
};

int n, m, q;
std::map<int, Node*> node[maxn];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    auto p = new Node();
    p->bel = i;
    node[i][m + 1] = p;
  }
  for (int op, a, b; q; --q) {
    std::cin >> op >> a;
    if (op == 1) {
      std::cin >> b;
      auto p1 = node[a].lower_bound(b), p2 = node[a + 1].lower_bound(b);
      auto A = p1->second, B = p2->second;
      A->splay(); B->splay();
      auto p3 = new Node, p4 = new Node;
      p3->bel = A->bel;
      p4->bel = B->bel;
      if ((p3->ch[1] = A->ch[1])) {
        p3->ch[1]->fa = p3;
      }
      if ((p4->ch[1] = B->ch[1])) {
        p4->ch[1]->fa = p4;
      }
      A->ch[1] = p4;
      B->ch[1] = p3;
      p3->fa = B; p4->fa = A;
      node[a][p1->first] = p3;
      node[a + 1][p2->first] = p4;
      node[a][b] = A;
      node[a + 1][b] = B;
    } else {
      auto u = node[a].begin()->second;
      u->splay();
      while (u->ch[1]) u = u->ch[1];
      std::cout << u->bel << '\n';
      u->splay();
    }
  }
}
```

---

## 作者：xyzfrozen (赞：3)

Fhq 做法

本题的关键在于每个点只会有一个桥。

## idea

我们首先有一个显然的想法，就是连一个桥相当于修改一些国家为 $a$ 的点的最终目的地。我们进一步思考，我们可以将这个修改一些数 $\to$ 修改一个数的后继，即交换 $(a,b),(a+1,b)$ 的后继**边**，这里看看扶苏的图会更加清晰。

但是每个国家建 $m+1$ 个点显然是不切实际的，继续考察这个后继边的影响，实际上是对于**一段连续区间** $[l,b]$ 进行修改，在 $l-1$ 处某个国家连了一条边到 $(a,l)$ 来。我们发现这样的区间段至多只有 $O(n+q)$ 种，于是想到维护这个段的信息，想到 [P3960 [NOIP2017 提高组] 列队](https://www.luogu.com.cn/problem/P3960)，考虑用裂点 `Fhq` 实现。

## 操作

首先我们每个国家建一个段 $[1,m+1]$。

1. 连桥

我们找到 $(a,b)$ 所在的 $[l,r]$ 区间，满足 $l \leq b \leq r$，然后找到这个段所属的平衡树，分裂出 $[b+1,m+1]$，然后同理操作 $(a+1,b)$，交换这两个后继。

如何实现找区间？

想到 [P3285 [SCOI2014] 方伯伯的OJ](https://www.luogu.com.cn/problem/P3285) 我们用 `map` 实现，对每个国家维护每个段的左端点，查询时类似 `ODT` 的找即可。

写的时候一定要注意修改的是后继边，所以是不含 $b$ 本身的！

2. 跑路（误）

对于每棵树我们在进行操作 1 的时候维护一下它的段头颜色（国家），然后找的时候直接访问这可树的根，向右儿子跳即可，最右节点的颜色即为答案。


```cpp
#include<bits/stdc++.h>
#define pt putchar(' ')
#define nl puts("")
#define pi pair<int,int>
#define fi first
#define se second
#define pb push_back
#define go(it) for(auto &it:as[x])
using namespace std;

const int N=8e5+10;
int n,m,q,idx,a,b,u,v;
int rt[N],col[N];
mt19937 Rnd(time(0)^99994919);
struct node{
    int ls,rs;
    int heap;
    int ql,qr,c,s,fa;
    node(){}
    node(int ls,int rs,int heap,int ql,int qr,int c,int s,int fa):
        ls(ls),rs(rs),heap(heap),ql(ql),qr(qr),c(c),s(s),fa(fa){}
}tr[N];
map<int,int> id[N];

int fr(){
    int x=0,flag=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        x=x*10+(ch-'0');
        ch=getchar();
    }
    return x*flag;
}
void fw(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) fw(x/10);
    putchar(x%10+'0');
}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}

#define Ls(p) tr[tr[p].ls]
#define Rs(p) tr[tr[p].rs]
#define Fa(p) tr[p].fa
#define L(p) tr[p].ql
#define R(p) tr[p].qr

int add(int ql,int qr,int col)
{
    idx++,tr[idx]=node(0,0,Rnd(),ql,qr,col,1,idx);
    return id[col][ql]=idx;
}
void chf(int now)
{
    tr[now].s=Ls(now).s+Rs(now).s+R(now)-L(now)+1;
    Ls(now).fa=Rs(now).fa=Fa(now)=now;
}

int merge(int l,int r)
{
    if(!l || !r) return l|r;
    if(tr[l].heap>tr[r].heap) return tr[l].rs=merge(tr[l].rs,r),chf(l),l;
    else return tr[r].ls=merge(l,tr[r].ls),chf(r),r;
}

void split_node(int now,int sz)
{
    if(sz>=R(now)-L(now)+1) return;
    int r=R(now);
    R(now)=L(now)+sz-1;
    tr[now].rs=merge(add(L(now)+sz,r,tr[now].c),tr[now].rs);
    chf(now);
}

void split(int now,int size,int &l,int &r)
{
    if(!now) return void(l=r=0);
    if(size<=Ls(now).s) r=now,split(tr[now].ls,size,l,tr[now].ls);
    else
    {
        split_node(now,size-Ls(now).s);
        l=now,split(tr[now].rs,size-Ls(now).s-(R(now)-L(now)+1),tr[now].rs,r);
    }
    chf(now);
}

int l,mid,r;
void make_tr(int x,int y,int &t,int &T,int &pos)
{
    auto res=id[x].lower_bound(y);
    if(res==id[x].end() || res->first>y) res--;
    int now=res->second;
    while(Fa(now)!=now) now=Fa(now);
    pos=col[now];
    split(now,y,l,r);
    T=l,t=r;
}

void modify(int x,int y)
{
    int t1,t2,Tx,Ty,bx,by;
    make_tr(x,y,t1,Tx,bx),make_tr(x+1,y,t2,Ty,by);
    col[rt[bx]=merge(Tx,t2)]=bx;
    col[rt[by]=merge(Ty,t1)]=by;
}

int query(int nat)
{
    int now=col[nat];
    while(Fa(now)!=now) now=Fa(now);
    while(tr[now].rs) now=tr[now].rs;
    return tr[now].c;
}

int main()
{
    n=fr(),m=fr(),q=fr();
    for(int i=1;i<=n;i++) col[rt[i]=add(1,m+1,i)]=i;
    while(q--)
    {
        if(fr()&1) a=fr(),b=fr(),modify(a,b);
        else fw(query(fr())),nl;
    }
    return 0;
}
```

---

## 作者：jinhaoxian (赞：3)

以下认为该地图是一个 $n$ 行 $m+1$ 列的网格，由于每个点最多连接一座桥，可以发现每一列中不同的桥不会互相影响（即不会有某条路径经过同一列的多座桥）但处理难度较大。因此考虑离线之后将有多座桥的列拆成多列（使得每列仅有一座桥）并离散化。

考虑分块，设总共有 $k$ 座桥，即离散化后有 $k$ 列，则以 $k^{\frac{1}{2}}$ 列为一块，容易发现每一块涉及的行只有 $O(k^{\frac{1}{2}})$ 级别。未涉及的行不与任何桥连接，因此不会改变路径所在行，可以特殊处理。在每次新增一座桥时重新计算从每一行进入块内，对应走到的终点。查询则只需要每一块依次查表模拟这一过程。时间复杂度 $O((n+m+k) \times k^{\frac{1}{2}})$。

具体实现上，由于本题能接受 $k^{\frac{3}{2}}$ 空间，可以对每一块，记录涉及到的行即其在块内离散化后的编号，重构与询问的过程均可以直接查表求解（以下代码中 bs 用于存涉及的行编号，使用 bitset 仅为省空间）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,op[105000],a[105000],b[105000],cnt[105000];
int B,Bl[405],Br[405],Bcnt,Binv[405][805],Bid[405][105000],Bres[405][805],val[105000][2];//{pos,time}
bitset<105000> bs[405];
void remake(int x,int t) {
    for (int i=1;i<=Binv[x][0];i++) Bres[x][i]=i;
    for (int i=Bl[x];i<=Br[x];i++) {
        if (val[i][1]>t) continue;
        swap(Bres[x][Bid[x][val[i][0]]],Bres[x][Bid[x][val[i][0]]+1]);
    }
    for (int i=1;i<=Binv[x][0];i++) Bres[0][Bres[x][i]]=i;
    for (int i=1;i<=Binv[x][0];i++) Bres[x][i]=Bres[0][i];
}
int main() {
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=q;i++) {
        scanf("%d",&op[i]);
        if (op[i]==1) {
            scanf("%d%d",&a[i],&b[i]);
            cnt[b[i]]++;
        } else scanf("%d",&a[i]);
    }
    for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    m=cnt[m];
    for (int i=q;i>=1;i--) {
        if (op[i]==1) {
            b[i]=cnt[b[i]]--;
            val[b[i]][0]=a[i];val[b[i]][1]=i;
        }
    }
    B=sqrt(m);
    for (int i=1;i<=m;i+=B) {
        Bl[(i+B-1)/B]=i;Br[(i+B-1)/B]=min(i+B-1,m);Bcnt=(i+B-1)/B;
    }
    for (int i=1;i<=Bcnt;i++) {
        for (int j=Bl[i];j<=Br[i];j++) {
            bs[i][val[j][0]]=bs[i][val[j][0]+1]=1;
        }
        for (int j=1;j<=n;j++) {
            if (bs[i][j]) {
                Binv[i][++Binv[i][0]]=j;
                Bid[i][j]=Binv[i][0];
                Bres[i][Binv[i][0]]=Binv[i][0];
            }
        }
    }
    for (int i=1;i<=q;i++) {
        if (op[i]==1) {
            remake((b[i]+B-1)/B,i);
            int id=(b[i]+B-1)/B;
        } else {
            int x=a[i];
            for (int j=1;j<=Bcnt;j++) if (Bid[j][x]) x=Binv[j][Bres[j][Bid[j][x]]];
            printf("%d\n",x);
        }
    }
    return 0;
}

```


---

## 作者：Alex_Wei (赞：2)

### [P9358 [ICPC 2022 Xi'an R] Bridge](https://www.luogu.com.cn/problem/P9358)

因为没走过的桥是必须走，所以从每个位置出发的路径是唯一的。初始路径是 $n$ 条 $(x, 1)\to (x, 2) \to \cdots \to (x, m + 1)$ 的链，一次操作相当于交换 $(a, b)$ 和 $(a + 1, b)$ 指向的点，所以任何时候的路径都是 $n$ 条链。

考虑最简单的做法，就是显式的维护每个点指向的点，修改 $\mathcal{O}(1)$，查询 $\mathcal{O}(m)$。

首先的问题是存不下，因为一共有 $\mathcal{O}(nm)$ 个点。但注意到链上大部分是没有桥连接的点，可以把一段极长的这样的点缩起来，也就是只保留和桥相连的关键点。这样空间就可以接受了。

对于这种修改和查询不平衡的问题，最直接的就是分块。本题无论是对 $n$，$m$ 还是时间轴分块都是可以的。官方解法是对时间轴分块，实现起来较复杂。我们考虑对 $m$ 分块，只保留所有国家的编号在 $[l, r)$ 的点，每次修改后 $\mathcal{O}(B)$ 更新被修改的两条链是从哪个国家到哪个国家，做到 $\mathcal{O}(1)$ 查询。一共有 $q\frac {m} B$ 次查询，取 $B = \sqrt m$ 得到时间复杂度 $\mathcal{O}((n + q)\sqrt m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 3e5 + 5;
constexpr int B = 333;
int n, m, q, op[N], x[N], y[N];
int anc[N], pre[N], nxt[N], to[N];
vector<pair<int, int>> buc[N];
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> q;
  for(int i = 1; i <= q; i++) {
    cin >> op[i] >> x[i];
    if(op[i] == 1) cin >> y[i];
  }
  for(int l = 1; l < m + 1; ) {
    int r = min(m + 1, l + B);
    for(int i = 1; i <= q; i++) {
      if(op[i] == 1) {
        if(y[i] >= l && y[i] < r) {
          buc[x[i]].push_back({y[i], n + i});
          buc[x[i] + 1].push_back({y[i], n + q + i});
        }
      }
    }
    for(int i = 1; i <= n; i++) {
      to[i] = i;
      if(buc[i].empty()) continue;
      sort(buc[i].begin(), buc[i].end());
      int cur = i;
      for(auto _ : buc[i]) {
        int id = _.second;
        nxt[cur] = id, pre[id] = cur;
        anc[cur = id] = i;
      }
      nxt[cur] = -i;
      buc[i].clear();
    }
    auto update = [&](int p) {
      int ini = p;
      while(p >= 0) anc[p] = ini, p = nxt[p];
      to[ini] = -p;
    };
    for(int i = 1; i <= q; i++) {
      if(op[i] == 1 && y[i] >= l && y[i] < r) {
        int id1 = n + i, id2 = n + q + i, tmp = anc[id2];
        swap(nxt[pre[id1]], nxt[pre[id2]]);
        swap(pre[id1], pre[id2]);
        update(anc[id1]), update(tmp);
      }
      if(op[i] == 2) x[i] = to[x[i]];
    }
    l = r;
  }
  for(int i = 1; i <= q; i++) {
    if(op[i] == 2) cout << x[i] << "\n";
  }
  return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：2)

不难发现，最开始有 $n$ 条链，并且由于每个点最多有一个桥，所以我们的交换操作实际上等价于将相邻的两条链断开，然后将它们后半部分交换。并且每个点在路径中的相对位置不变。

于是考虑维护这些链。

有一个很直观的思路就是维护点对 $(i,j)$ 表示最开始第 $i$ 条链的第 $j$ 个点在哪条链中，我们需要快速改变它以及它后面点的引索，所以考虑把在一条链中的点对放到一棵以 $j$ 为键值的 FHQtreap 上并维护每个点所属的 treap 然后操作就变成了分裂之后交换子树以及查询最大值，这个很好维护，可问题是点数是 $O(nm)$ 级别的。

所以考虑维护三元组表示最开始第 $i$ 条链上第 $l$ 到第 $r$ 个点当前所在的链，不难发现最开始有 $n$ 个三元组且一次操作最多使一个三元组分裂为 $(x,l,t)$ 与 $(x,t+1,r)$ 故三元组数量为 $O(n + m)$ 级别。

为了快速检索每个点在那个三元组中，把 $x$ 相同的三元组放在一个可以支持快速插入删除寻找前驱后继的平衡树中，在平衡树中储存三元组所在的节点的编号即可。

如此我们便在 $O(n \log n)$ 的时间内解决了问题。

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
const int maxn = 5e5+114;
__gnu_pbds::tree< pair<int, int>, __gnu_pbds::null_type, less< pair<int, int> >,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update > Index[maxn];
//(r,tot)
struct Node{
	int l,r,p;
	int fa;
	int ls,rs;
	int val;
}tr[maxn];
int root[maxn];
map<int,int> found;
int tot;
int clone(int l,int r,int p){
	tr[++tot].l=l,tr[tot].r=r,tr[tot].p=p,tr[tot].val=rand();
	return tot;
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(tr[x].val>tr[y].val){
		tr[x].rs=merge(tr[x].rs,y);
		tr[tr[x].rs].fa=x;
		return x;
	}
	else{
		tr[y].ls=merge(x,tr[y].ls);
		tr[tr[y].ls].fa=y;
		return y;
	}
}
void split(int cur,int x,int &l,int &r){
	if(cur==0){
		l=r=0;
		return ;
	}
	if(tr[cur].l>x){
		r=cur;
		split(tr[cur].ls,x,l,tr[cur].ls);
		tr[tr[cur].ls].fa=cur;
	}
	else{
		l=cur;
		split(tr[cur].rs,x,tr[cur].rs,r);
		tr[tr[cur].rs].fa=cur;
	}
}
int find_root(int x){//寻找点 x 所在的根 
	while(tr[x].fa!=0){
		x=tr[x].fa;
	}
	return x;
}
int Ord_split(int x,int pos){//将 (x,pos) 所在的有序段分裂为 [l,x] 与 [x+1,r] 
	int y = (*Index[pos].lower_bound(make_pair(x,x))).second;
	int lt=tr[y].l,rt=tr[y].r,p=tr[y].p;
	y=find_root(y);
	if(x==rt) return y;
	int pos_rt=found[y];
	int tr1=0,tr2=0,tr3=0;
	split(y,lt-1,tr1,tr2);
	split(tr2,lt,tr2,tr3);
	int New1=clone(lt,x,p),New2=clone(x+1,rt,p);
	found[y]=0;
	y=merge(tr1,merge(New1,merge(New2,tr3)));
	tr[y].fa=0,found[y]=pos_rt,root[pos_rt]=y;
	Index[pos].erase(Index[pos].lower_bound(make_pair(x,x)));
	Index[pos].insert(make_pair(x,New1));
	Index[pos].insert(make_pair(rt,New2));	
	return y;
} 
int n,m,q;
void build(){
	for(int i=1;i<=n;i++){
		int y=clone(1,m+1,i);
		tr[y].fa=0,found[y]=i,root[i]=y;
		Index[i].insert(make_pair(m+1,y));
	}
}
int End(int x){
	if(tr[x].rs==0) return tr[x].p;
	else return End(tr[x].rs);
}
int query(int x){//查询从点 x 开始最后会到那个点 
	return End(root[x]);
}
void opt(int a,int b){
	int x=Ord_split(b,a);
	int y=Ord_split(b,a+1);
	x=find_root(x);
	y=find_root(y);
	int x_pos = found[x];
	int y_pos = found[y];
	int tr1=0,tr2=0,tr3=0,tr4=0;
	split(x,b,tr1,tr2);
	split(y,b,tr3,tr4);
	found[x]=0;
	found[y]=0;
	x=merge(tr1,tr4);
	y=merge(tr3,tr2);
	tr[x].fa=0,found[x]=x_pos,root[x_pos]=x;
	tr[y].fa=0,found[y]=y_pos,root[y_pos]=y;
}
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>n>>m>>q;
build();
for(int i=1;i<=q;i++){
	int op;
	cin>>op;
	if(op==1){
		int a,b;
		cin>>a>>b;
		opt(a,b);
	}
	else{
		int a;
		cin>>a;
		cout<<query(a)<<'\n';
	}
}
return 0;
}
```


---

## 作者：yzy1 (赞：1)

## 声明

博客编辑页和管理员题解审核页使用的 $\KaTeX$ 版本较低．根据目前使用发现，该版本暂不支持以下语法：

- `\def` 指令．
- 结合使用 `\textt` 指令和 `\textit` 指令实现等宽斜体．

此原因可能会导致本题解中的部分公式渲染异常．而在题目对应的题解展示页面和个人博客渲染页面使用的 $\KaTeX$ 为高版本，则无此问题．


## 题目大意

给出一个 $n$ 横行 $m+1$ 竖列的格点图，第 $i$ 横行第 $j$ 竖列的点可以用二元组 $(i,j)$ 表示．初始时，对于所有 $1 \le i \le n$，$1 \le j \le m$，存在 $(i,j)$ 到 $(i,j+1)$ 且权值为 $1$ 的单向边．

维护 $q$（$1 \le q \le 10^5$）次操作：

- $\texttt{1 \textit a \textit b}$（$1 \le a < n$，$1 \le b\le m$）：在 $(a, b)$ 和 $(a + 1, b)$ 之间添加一条权值为 $2$ 的双向边．**保证每个结点最多和一条双向边相连**．
- $\texttt{2 \textit a}$（$1 \le a \le n$）：假设从 $(a, 1)$ 开始，每次会从当前沿着一条未走过的且权值最大的边走向下一个结点，直到以所在结点出发不存在未走过的边为止．求出结束时所在点对应的二元组的首项．

## 简要做法

考虑在 $(a,b)$ 和 $(a+1,b)$ 之间新建一条双向边相当于断开 $(a,b) \to (a,b+1)$ 和 $(a+1,b) \to (a+1,b+1)$，并添加 $(a,b) \to (a+1,b+1)$ 和 $(a+1,b) \to (a,b+1)$ 两条新边．经过这个转换，我们发现在进行若干次操作后，图依旧是 $n$ 个长度为 $m+1$ 的链．

我们将初始时位于第 $i$ 条链上的结点的颜色定义为 $i$，维护每条链上点的颜色．则 $1$ 操作转换为首先找到两个指定颜色的结点对应的链，然后交换两个链的指定长度的后缀．$2$ 操作转换为制定一条链，求它的最后一个结点的颜色．

这个问题可以通过平衡树解决，但是存在更为简便的方法．观察到每条链的形态自始至终均相同，我们可以直接用动态开点线段树代替平衡树，我们让 $n$ 棵动态开点线段树公用一个内存池，就可以实现结点的交换．而对于「给定颜色找对应的链」，我们发现交换是不会改变颜色与结点编号的关系的，则可以通过一个全局的 map 记录每种颜色结点对应的编号．然后通过给每个结点记录一个 father，这样不断跳 father 就可以找到链对应线段树的根结点了．

该做法时间复杂度为 $O(n \log n)$，可以通过本题．

## 代码参考

见 [原始 OJ 提交](https://qoj.ac/submission/108513)．


---

## 作者：tanghg (赞：0)

考虑对 $m$ 分块，每次维护一个 $f_{i,j}$ 表示第 $i$ 个国家经过第 $i$ 个块后能到达哪个国家，那么使用 `std::map` 来记录桥。对于每一次修改先通过从 $a,a+1$ 开始，从 $b$ 开始一直反向推到 $b$ 所属的块首，表示推出最开始能到达的国家，为 $s,t$。那么就可以互换 $f_{s,k}$ 与 $f_{t,k}$ 表示这两个位置可以互相交换到达了。$k$ 即为 $b$ 所在的块编号。那么对于查询就可以直接一直迭代 $f_{a,i}$ 即可。初始化 $f_{i,j}=i$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long ll;
const ll MAXN=1e5+5;
const ll MAXK=320;
ll n,m,Q;
ll f[MAXN][MAXK];
map<ll,ll>bg[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>m>>Q;
    ll lb=sqrt(m);
    rep(i,1,n){
        rep(j,0,m/lb){
            f[i][j]=i;
        }
    }
    while(Q--){
        ll op,a,b;
        cin>>op>>a;
        if(op==2){
            rep(i,0,m/lb){
                a=f[a][i];
            }
            cout<<a<<"\n";
            continue;
        }
        cin>>b;
        ll id=b/lb;
        ll s=a,t=a+1;
        for(int i=b;i>=id*lb;--i){
            if(bg[s].count(i)){
                s=bg[s][i];
            }
            if(bg[t].count(i)){
                t=bg[t][i];
            }
        }
        swap(f[s][id],f[t][id]);
        bg[a][b]=a+1;
        bg[a+1][b]=a;
    }
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

感觉很妙啊，应该不止蓝吧？

首先一个转化是每次建桥操作就相当于交换两条链的后半部分，可以看看扶苏那篇题解的图。

我们将每个点表示为形如 $(x, y)$ 的二元组表示它初始在第 $x$ 行第 $y$ 列，按 $y$ 为键值排序，那么一次询问就是查询一条链的最大值。

这些操作可以用 FHQ Treap 完成，就是每次修改 $(a, b)$ 就把两棵 Treap 分别按 $\le b$ split 成四棵，交换后再 merge。查询直接暴力跳右儿子就行。

但是显然不能存 $nm$ 个点。考虑我维护连续段而不是维护一个个单点，每个连续段形如 $(x, l, r)$ 表示初始在第 $x$ 行第 $l$ 列到第 $r$ 列的点，意义是它们在同一条链上并且连边 $l \to l + 1 \to \cdots \to r$。

那么每次修改操作会多产生 $4$ 个段，所以段的个数就是 $O(n + q)$ 的，可以接受。

实现时比较繁琐，每一行要额外开个 set 维护原来在这一行的段方便对于每次修改找到 $b$ 所在的段，还要开个 map 维护每个三元组 $(x, l, r)$ 对应到 Treap 上的哪个点。为了找对应结点的根还要维护每个点的父亲。

总时间复杂度是 $O((n + q) \log n)$。

[code](https://qoj.ac/submission/288175)

---

