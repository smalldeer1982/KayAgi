# [NOISG 2025 Finals] 洪水

## 题目描述

Pavementland 是一座城市，可以用一个 $h \times w$ 的矩形网格表示。网格的行从北到南编号为 $1$ 到 $h$，列从西到东编号为 $1$ 到 $w$。我们将位于网格第 $r$ 行、第 $c$ 列的单元格称为单元格 $(r, c)$。

在网格中，每个单元格要么是空的，要么包含一座建筑。至少有一个单元格是空的。

由于季风暴潮，Pavementland 发生了突发洪水。最初，一场降雨导致某个空单元格被水淹没。然后，水按照以下规则流动：

- 如果一个空单元格与至少一个被淹没的单元格相邻，它也会被淹没。
- 如果一个包含建筑的单元格与至少两个被淹没的单元格相邻，该建筑会倒塌，该单元格变为被淹没状态。

请注意，如果两个单元格共享一条边，则它们是相邻的。一个单元格最多可以与四个其他单元格相邻。进一步说明，水不会流出网格范围。令 $f((r, c))$ 表示如果单元格 $(r, c)$ 最初被淹没，则最终被淹没的单元格总数。

市政官员希望预测所有可能情况下的洪水蔓延范围。请帮助他们计算所有空单元格 $(r, c)$ 的 $f((r, c))$ 之和。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq h, w \leq 5000$
- 网格中至少有一个空单元格。

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $5$ | $h = 1$ |
| $2$ | $7$ | $h, w \leq 80$ |
| $3$ | $16$ | $h, w \leq 500$ |
| $4$ | $32$ | $h, w \leq 2000$ |
| $5$ | $40$ | 无 |

### 样例 1 解释

此样例适用于子任务 $2$ 至 $5$。

如果单元格 $(1, 1), (1, 2), (1, 3), (2, 1)$ 或 $(3, 1)$ 最初被淹没，则整个网格最终都会被淹没。如果单元格 $(3, 3)$ 最初被淹没，则最终只有 $1$ 个单元格被淹没。因此，输出为 $9 + 9 + 9 + 9 + 9 + 1 = 46$。

### 样例 2 解释

此样例适用于子任务 $2$ 至 $5$。

### 样例 3 解释

此样例适用于所有子任务。


## 样例 #1

### 输入

```
3 3
000
011
010```

### 输出

```
46```

## 样例 #2

### 输入

```
5 5
00101
01011
11010
01101
11000```

### 输出

```
182```

## 样例 #3

### 输入

```
1 10
1101011100```

### 输出

```
6```

# 题解

## 作者：伊地知虹夏 (赞：3)

绝世好题！！！

速报：本题复杂度已达到输入同级 $\mathcal O(hw)$！！！

注意到每个结点能淹没的点一定是一个矩形，不然可以继续扩张。

我们在矩形外面围一层 $1$。

考虑一个作为答案的矩形长什么样，容易发现该矩形的边界一定全是 $1$，且不能存在一行（列） $1$ 将其分开。

一个位置的答案矩形即为最小的包含它的这种矩形的大小。

记第 $i$ 个这种矩形的大小为 $x_i \times y_i$，我们断言 $ \sum{(x_i+y_i)} \le hw$。

考虑证明这个理论：

首先这样的矩形只能包含或相离，否则会有两个矩形互相把对方切开。

我们对矩形的包含关系建一棵树。

考虑每个矩形和它父亲矩形的重叠部分，我们证明其不可能包含一组对边。

若其包含一组对边，则该矩形会把父亲矩形划分成两个部分，不满足合法矩形要求。

那么它至少有一对长和宽是不与父亲重合的，即 $\sum (x_i+y_i) \le hw$。

接下来我们需要求出这些极大矩形。

考虑枚举左边界 $x$。记 $x$ 上的建筑物为 $0,i_1,i_2,\cdots,i_k,m+1$，$f_p$ 为 $i_p$ 向左延伸的最远距离。

那么一个合法的上下边界 $i_p,i_q$ 一定满足 $\min(f_p,f_q) > \max\limits_{i=p+1}^{q-1} f_i$，这个可以单调栈求出。

对于一对合法的 $i_p,i_q$，我们可以暴力从 $x$ 出发找右边界，容易证明这个的复杂度是均摊 $\mathcal O(hw)$ 的。

接下来就是做矩形 checkmin，求全局值。这部分由于周长是 $\mathcal O(hw)$ 级别的可以对每行开一个 $\mathcal O(w)$ 并查集，将矩形从小到大排序后对每行做区间覆盖。排序使用计数排序即可做到时间复杂度 $\mathcal O(hw)$。

[qoj 最优解](https://qoj.ac/submission/1098226)。

---

## 作者：Milmon (赞：3)

容易发现一个位置开始最后洪水淹没的位置形状是一个矩形。于是我们可以得到一个 $\Theta(hw(h + w))$ 的做法：枚举初始位置，不断尝试向四个方向扩展矩形。

定义一个矩形是合法的，当且仅当其上下左右都是边界或者建筑物并且不存在一行或者一列全是障碍物。那么每个位置的答案矩形显然合法，所以一个位置的答案矩形即为最小的包含它的合法矩形的大小。

考虑如何求出所有合法矩形。枚举合法矩形的左边界 $x$，设第 $x$ 列建筑物的位置依次为 $0, i_1, i_2, \cdots, i_k, h + 1$。那么对于任意两个建筑物，如果第 $x - 1$ 列这一段都是建筑物，那么可以向右找到最远的扩展位置，从而产生一个合法矩形。最远的扩展位置可以使用二分求得。

注意到，每个合法矩形的上下边界均必须为建筑物或者边界，所以两个建筑物 $i_u, i_v$ 的最大扩展列数至多为第 $i_u, i_v$ 列从第 $x$ 行开始的最长连续建筑物长度的较小值。设有建筑物的 $k$ 行的最长连续建筑物长度分别为 $f_1, f_2, \cdots, f_k$，找到一个 $j$ 满足 $f_{j} \leq \min(f_{j - 1}, f_{j + 1})$，那么能够以第 $i_j$ 行作为边界之一的合法矩形至多只有两个，因为如果一个合法矩形以第 $i_j$ 行作为边界并且跨过第 $i_{j - 1}$ 或者第 $i_{j + 1}$ 行，那么存在一行全是建筑物，不符合条件。于是我们每次找出最小的长度，计算以其为边界的合法矩形之后就可以将其删除。于是我们得到了 $\mathcal{O}(hw)$ 个合法矩形。

最后相当于要处理 $\mathcal{O}(hw)$ 次矩形取最小值，最后查询所有位置的答案。扫描线即可，总时间复杂度 $\mathcal{O}(hw \log hw)$。

---

## 作者：Lucyna_Kushinada (赞：1)

# P12019 [NOISG 2025 Finals] 洪水

## 题意

给定一个 $n\times m$ 的网格，每个格子有数字，第 $i$ 行 $j$ 列的为 $a_{i,j}\in \{0,1\}$，$1$ 表示该格子为建筑格子，$0$ 表示为空格子。

初始时在**空格子** $(x,y)$ 放水，然后会有如下淹没规律：

- 如果一个空格子与至少一个被淹没的格子相邻，它会被淹没。

- 如果一个建筑格子与至少两个被淹没的格子相邻，它会被淹没。

水不会流出边界。

记最终状态时被淹没的格子数为 $f(x,y)$。

求出 $\displaystyle \sum_{i=1}^n \sum_{j=1}^m [a_{i,j}=0]f(i,j)$。

$n,m\le 5000$。

## 题解

知识点：扫描线，线段树，单调栈，堆。

启发：

- 特定情况下使用堆实现延迟删除。

感觉全是基本功啊，可为什么前前后后搞了这么久呢。

一开始没用堆，用的 `multiset` 卡常卡了一天还没卡过去，很难受。

### 思考 0

- 空格子不会被淹没，当且仅当四联通域没有被淹没的。

- 建筑格子不会被淹没，当且仅当四联通域至多有一个被淹没的。

被淹没的格子外围，要么是边界，要么是建筑格子。

### 思考 1

想一想被淹没的格子组成的形状。

当淹没的格子外围有凸出时，凸出左右边包住的不会是边界，因为边界是平的，所以只能是建筑格子，而这也是不可能的，建筑格子显然也会被淹没，所以不存在凸出，同理，也不存在凹进。所以外围是平的。

可以得出重要结论：**被淹没的所有格子组成的图形一定是矩形**。而矩形外围一圈（不包括四个角斜向的）不是建筑格子就是边界。

考虑将边界全变为建筑格子，可以发现他们一定不会被淹没，所以可以等效。

那么矩形的上下左右边界就都是建筑格子。

### 思考 2

那么一个空格子的贡献就是包含它的最小矩形的面积。

考虑处理出所有矩形，在这之前，先思考其数量级，由于矩形内部一定不能存在一整行/列的建筑格子（不然就会变成两个矩形），一个矩形的任意两对边至多同时贡献到一个矩形，这个限制比较强，故其数量级大概是 $O(nm)$ 的。

处理出两个数组 $ha_{i,j},la_{i,j}$，分别表示如果 $(i,j)$ 是建筑格子，其向行/列增加方向最长的连续建筑格子的长度（包括自己）。

处理出所有矩形，可以先 $O(m)$ 枚举列 $y$ 为其左边界，然后在每一列里面枚举上下边界的 $x$ 坐标，判定能否组成矩形，如果能就加入，判定这一步会排除矩形内一整列建筑格子的情况。

当然，这里并不能 $O(n^2)$ 枚举，考虑两个 $i,j(i<j)$，如果 $la_{i,y}\le la_{j,y}$，则 $i$ 肯定无法和后面的搭配形成矩形了，倘若组成矩形，那么第 $j$ 行会其中形成一个一整行的建筑格子，所以肯定不合法。

这个过程可以用单调栈实现，时间复杂度 $O(n)$，这一步会排除矩形内一整行建筑格子的情况。

### 思考 3

根据之前得出的，一个空格子的贡献就是包含它的最小矩形的面积，考虑扫描线，对哪一维扫都可以，动态加入/删除矩形，权值是该矩形的面积。

一下讨论的是对 $y$ 坐标的扫描。

扫描线达到了一个消维的效果，那么问题就转变为了：

- 维护一个长度为 $n$ 的序列 $a$，初始时每个位置都为 $+\infty$，每次给出三元组 $(l,r,s)$，对每个 $i\in [l,r]$ 执行 $a_i\leftarrow \min(a_i,s)$，同时还需要支持随机撤销之前三元组 $(l,r,x)$ 的作用效果，单点询问 $a_i$ 当前的值。

第一眼有一个线段树的做法，每个节点维护一个 `multiset` 的做法。

区间赋值时，递归到完全被操作区间的包含的节点区间时将 $s$ 加入该节点的 `multiset`。

查询时，顺着查询位置走线段树上的节点直到走到叶子，答案就是路径上 `multiset` 里的最小值。

只可惜这个做法常数太大了，卡常卡了一页还没过，于是有一个常数更小更聪明的堆做法。

每个节点开一个 `pair<int,int>` 的 `priority_queue`，加入节点的形式是一个 `pair`，面积 $s$ 为 `first`，该矩形作用时间右端点为 `second`，查询时先不断弹出 `second` 小于当前扫描到的列的队头，然后取此时的队头。

此时优先队列里面可能还有超时的元素，为什么不弹呢？其实这里用到了延迟删除的思想，不弹它并不会影响答案，那就等到队头是他的时候再弹，因为时间是单调的，某个时刻超时了，那么后面所有时刻都是超时状态。

总时间复杂度 $O(nm \log^2 n)$，虽然和 `multiset` 做法的复杂度相同，但是常数小了不少。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 5005
#define ll long long

int n,m,ha[N][N],la[N][N];
int st[N],tp,a[N][N];

struct rec{
    int l,r,s,ed;
};

vector<rec>ad[N];

inline void chk(int l,int r,int j){
    if(r-l-1<=0||ha[l+1][j-1]<r-l-1){
        return;
    }

    int i=j-1,ed=j+min(la[l][j],la[r][j])-1;

    while(ha[l+1][i+1]<r-l-1&&i<=ed){
        i++;
    }

    if(i>ed||i<j){
        return;
    }

    // cout<<"suc\n";

    ad[j].pb({l+1,r-1,(r-l-1)*(i-j+1),i});

    // cout<<l+1<<' '<<r-1<<' '<<j<<' '<<i<<' '<<"\n";
}

struct segt{
    #define mid ((l+r)>>1)

    priority_queue<pr,vector<pr>,greater<pr>>q[N<<2];

    inline void add(int L,int R,int k,int l,int r,int d,int ed){
        if(L<=l&&R>=r){
            q[k].push({d,ed});
            return;
        }

        if(L<=mid){
            add(L,R,k*2,l,mid,d,ed);
        }
        if(R>mid){
            add(L,R,k*2+1,mid+1,r,d,ed);
        }
    }

    inline int ask(int L,int k,int l,int r,int ed){
        int ans=1e9;

        while(1){
            while(sz(q[k])&&q[k].top().se<ed){
                q[k].pop();
            }

            if(sz(q[k])){
                ans=min(ans,q[k].top().fi);
            }

            if(l==r){
                break;
            }

            if(L<=mid){
                r=mid;
                k=k*2;
            }
            else{
                l=mid+1;
                k=k*2+1;
            }
        }
        
        return ans;
    }

    #undef mid
}t;

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(0);
    // cin.tie(0);cout.tie(0);

    cin>>n>>m;

    n+=2,m+=2;
    rep(i,1,n){
        a[i][1]=a[i][m]=1;
    }
    rep(i,1,m){
        a[1][i]=a[n][i]=1;
    }

    #define getchar getchar_unlocked

    char c=0;
    rep(i,2,n-1){
        rep(j,2,m-1){
            c=getchar();
            while(c!='0'&&c!='1'){
                c=getchar();
            }

            a[i][j]=c-'0';
        }
    }

    per(i,1,n){
        per(j,1,m){
            if(a[i][j]){
                ha[i][j]=ha[i+1][j]+1;
                la[i][j]=la[i][j+1]+1;
            }
        }
    }

    per(j,2,m-1){
        tp=0;

        rep(i,1,n){
            while(tp){
                chk(st[tp],i,j);

                if(la[st[tp]][j]>la[i][j]){
                    break;
                }
                tp--;
            }

            st[++tp]=i;
        }
    }

    ll ans=0;

    rep(j,1,m){
        for(rec u:ad[j]){
            t.add(u.l,u.r,1,1,n,u.s,u.ed);
            // cout<<j<<' '<<u.l<<' '<<u.r<<" add\n";
        }

        rep(i,1,n){
            if(a[i][j]){
                continue;
            }
            
            ans+=t.ask(i,1,1,n,j);
        }
    }

    cout<<ans;
    
    return 0;
}
```

---

## 作者：_biLang_ (赞：0)

# 分析
手模一下就能发现最终被淹没的区域一定是个矩形（否则一定有可拓展的点），有矩形就可以想到扫描线做法。首先找出所有可能有贡献的矩形，其边界外一定全为障碍，且内部不会被整行或整列的障碍。先枚举左边界 $$$ x $$$ 从 $$$ w $$$ 到 $$$ 1 $$$，并在转移时顺便维护每个 $$$ (i, x) $$$ 最右连续障碍的长度和每行向下连续障碍的单调栈。对每个横向障碍找出其上下第一个长于自身的障碍，二分上界那行的向下连续障碍的单调栈以找出第一个不短于上下距离的竖直障碍，容易理解这种方法一定能枚举到所有可能矩形，个数是 $$$ \mathcal{O}(h \cdot w) $$$ 的。最后扫描线对每点求出最小覆盖矩形，扫描线易做，总时复 $$$ \mathcal{O}(h \cdot w \cdot (\log h + \log w)) $$$。
# AC code
```cpp
#include <bits/stdc++.h>

namespace io
{
  char buf[1 << 20], *p1(buf), *p2(buf), c;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
  
  template <typename _Tp> inline void read(_Tp& x)
  { x = 0; while (!isdigit(c = gc())); while (x = (x << 1) + (x << 3) + (c ^ 48), isdigit(c = gc())); }
  
  template <typename _Tp, typename... Args> inline void read(_Tp& x, Args&... args) { read(x), read(args...); }
  
  inline bool get(void) { while (!isdigit(c = gc())); return c ^ 48; }
  
  char pbuf[1 << 20], *pp(pbuf), sta[30], *top(sta);
#define flush() (fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf)
#define pc(c) (pp - pbuf == 1 << 20 ? flush() : 0, *pp++ = (c))
  
  template <typename _Tp> inline void write(_Tp x)
  { while (*top++ = x % 10 ^ 48, x /= 10); while (pc(*--top), top != sta); }
  
  struct flusher { inline ~flusher(void) { flush(); } } ioflush;
} // namespace io

using io::read;
using io::get;
using io::write;

using u32 = int;

constexpr u32 N(5002);

u32 h, w, s[N][N], r[N], d[N], q[N][N], p[N][N], top[N], Q[N], tp; long long ans; std::bitset<N> mp[N];

struct rect
{
  u32 L, R, U, D, sz;
  inline rect(const u32& l, const u32& r, const u32& u, const u32& d)
  : L(l), R(r), U(u), D(d) { sz = (R - L + 1) * (D - U + 1); }
  friend inline bool operator < (const rect& a, const rect& b) { return a.sz > b.sz; }
}; std::vector<rect> in[N];

inline void Solve(const u32& L, const u32& U, const u32& D)
{
  static u32 ll, rr, m; if (D - U == 1) return; ll = 1, rr = top[U + 1];
  while (ll < rr) m = ll + rr + 1 >> 1, (q[U + 1][m] < D - U - 1) ? (rr = m - 1) : (ll = m);
  if (p[U + 1][ll] <= L + r[U] + 1 && p[U + 1][ll] <= L + r[D] + 1 && p[U + 1][ll] > L + 1)
    in[L + 1].emplace_back(L + 1, p[U + 1][ll] - 1, U + 1, D - 1);
}

struct segment_tree
{
  struct nd { u32 L, R; std::priority_queue<rect> rc; } tr[N << 2]; u32 cur, ql, qr; rect* qx;
  
#define Ls (i << 1)
#define Rs (Ls | 1)
  
  void build(const u32& i, const u32& l, const u32& r)
  { tr[i].L = l, tr[i].R = r; if (l != r) build(Ls, l, l + r >> 1), build(Rs, (l + r >> 1) + 1, r); }
  
  void modify(const u32& i)
  {
    if (ql <= tr[i].L && tr[i].R <= qr) { tr[i].rc.emplace(*qx); return; }
    if (ql <= tr[Ls].R) modify(Ls); if (tr[Rs].L <= qr) modify(Rs);
  }
  
  void query(const u32& i)
  {
    while (!tr[i].rc.empty() && tr[i].rc.top().R < cur) tr[i].rc.pop();
    if (!tr[i].rc.empty() && tr[i].rc.top().sz < qr) qr = tr[i].rc.top().sz;
	if (tr[i].L != tr[i].R) query((ql <= tr[Ls].R) ? Ls : Rs);
  }
} tr;

signed main(void)
{
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout);
#endif
  
  u32 i, j, k, U, D;
  
  read(h, w); for (i = 1; i <= h; i++) for (j = 1; j <= w; j++) mp[i][j] = get();
  mp[0].set(), mp[h + 1].set(); for (i = 1; i <= h; i++) mp[i].set(0), mp[i].set(w + 1);
  
  for (i = w; ~i; i--)
  {
    for (j = 0; j <= h + 1; j++) mp[j][i + 1] ? (r[j]++) : (r[j] = 0);
    for (j = h; j; j--)
    {
      if (!mp[j][i + 1]) { d[j] = 0; continue; } d[j] = d[j + 1] + 1;
      while (top[j] && q[j][top[j]] <= d[j]) top[j]--;
      top[j]++, q[j][top[j]] = d[j], p[j][top[j]] = i + 1;
	}
	for (j = 1; j <= h; j++) if (mp[j][i])
	{
	  U = D = j; while (D < h && mp[D + 1][i]) D++;
	  for (k = U - 1, tp = 0; k <= D + 1; k++) if (r[k])
	  { while (tp && r[Q[tp]] < r[k]) tp--; if (tp) Solve(i, Q[tp], k); Q[++tp] = k; }
	  for (k = D + 1, tp = 0; k >= U - 1; k--) if (r[k])
	  { while (tp && r[Q[tp]] < r[k]) tp--; if (tp && r[Q[tp]] > r[k]) Solve(i, k, Q[tp]); Q[++tp] = k; }
	  j = D;
	}
  }
  
  for (i = 1, tr.build(1, 1, h); i <= w; i++)
  {
    for (rect& rc : in[i]) tr.ql = rc.U, tr.qr = rc.D, tr.qx = &rc, tr.modify(1);
    for (j = 1, tr.cur = i; j <= h; j++) if (!mp[j][i]) tr.ql = j, tr.qr = 3e7, tr.query(1), ans += tr.qr;
  }
  
  write(ans);
  
  return 0;
}

```

---

## 作者：nullqtr_pwp (赞：0)

首先观察到一个 $0$ 的极大四联通连通块是等价的起点，对于一个连通块手玩一下发现可以至少可以拓展到包含它的最小矩形。那么我们将问题转化成了若干矩形不断拓展，合并的过程。然而直接将每个连通块看成一个矩形是错误的，具体来说一个矩形的四联通相邻位置都是 $1$ 或者边界是就无法拓展，不能用简单的相交来刻画，我们称这样的矩形是好的。我们尝试找出所有极大的好矩形，猜测这些矩形的数量并不多，为了进一步缩小可行数量，我们要求这些矩形内部不存在某行或者某列全是 $1$，这样我们声称好矩形的个数是 $\mathcal O(nm)$ 的（构造就是将所有 $2\mid (x+y)$ 的 $(x,y)$ 染为 $1$）。不难发现，对于一个连通块构成的矩形而言，其答案的上界就是最小包含它的好矩形。进一步的，你发现答案事实上就是这个好矩形。于是做法分为两步，找到这些好矩形，以及对每个连通块的矩形找到最小包含它的好矩形。

对于第一步，固定这个好矩形的左上角 $(x,y)$，显然这个 $(x,y)$ 贡献最多一个矩形（你考虑逐渐 bfs 的过程，显然只会有一个矩形完全包住它），因此总数量正确。现在考虑如何快速找它。处理 $(x-1,y),(x,y-1)$ 分别向右以及向下延的极长 $1$ 连续段长度。外层按 $x$ 枚举，从右往左扫 $y$ 在 $(x-1,*)$ 的每个连续段，维护 $down_i$ 表示 $(x-1,i)$ 开始向下延的 $1$ 连续段长度，显然我们只关心 $down$ 的严格前缀 $\max$。然后在横轴 $[x,n]$ 维护一个线段树，每个元素的值就是 $to_i$ 表示第 $i$ 行在这个单调栈 ``lowerbound`` 出来的那个列的右端点开始延到的 $1$ 连续段的左端点（也就是，对于单调栈的前缀 $\max$，考虑每个列比上一个列多出来的那些部分的行，这些在对应横轴的 $i$ 维护赋值了 $to_i$）。显然我们只需要线段树二分第一个 $to_i\leq y$。进一步你甚至不需要单调栈，每次做一个区间覆盖 $to$，具体来说预处理 $m$ 个线段树，然后做区间 copy。这样我们以 $\mathcal O(nm\log nm)$ 的复杂度查找出了所有好矩形。

对于第二步，不难发现矩形之间只有严格包含和严格相离。我们只需要对左和对上两个方向做两次扫描线，找到这个方向上，上一个在区间上严格包含查询区间的矩形，手玩一下发现目标矩形只在这两个中找到。以从左向右扫描线为例，此时是一维问题，我们需要求出上一个 $[ql,qr]\subseteq[l,r]$ 的 $[l,r]$ 的信息。维护一个长度为 $n$ 的序列 $a$，插入一个矩形的左边界时，记录当前横轴位置为 $x$，将 $a[l:r]$ 赋值为 $(x,id)$，其中 $id$ 为这个矩形。那么查询就是 $a[ql:qr]$ 中 $x$ 最小的位置对应的 $id$，容易上数据结构维护做到 $\mathcal O(nm\log nm)$。

由于需要动态开点以支持区间复制，这个常数可能比较大，所以做法仅供参考。

不过我是口胡选手，没有写代码，如果有锅请指出。

---

