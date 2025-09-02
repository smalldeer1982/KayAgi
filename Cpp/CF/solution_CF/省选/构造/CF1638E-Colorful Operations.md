# Colorful Operations

## 题目描述

You have an array $ a_1,a_2, \dots, a_n $ . Each element initially has value $ 0 $ and color $ 1 $ . You are also given $ q $ queries to perform:

- Color $ l $ $ r $ $ c $ : Change the color of elements $ a_l,a_{l+1},\cdots,a_r $ to $ c $ ( $ 1 \le l \le r \le n $ , $ 1 \le c \le n $ ).
- Add $ c $ $ x $ : Add $ x $ to values of all elements $ a_i $ ( $ 1 \le i \le n $ ) of color $ c $ ( $ 1 \le c \le n $ , $ -10^9 \le x \le 10^9 $ ).
- Query $ i $ : Print $ a_i $ ( $ 1 \le i \le n $ ).

## 说明/提示

The first sample test is explained below. Blue, red and green represent colors $ 1 $ , $ 2 $ and $ 3 $ respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638E/fca750ad681aed552c7980359d7170f22a91379c.png)

## 样例 #1

### 输入

```
5 8
Color 2 4 2
Add 2 2
Query 3
Color 4 5 3
Color 2 2 3
Add 3 3
Query 2
Query 5```

### 输出

```
2
5
3```

## 样例 #2

### 输入

```
2 7
Add 1 7
Query 1
Add 2 4
Query 2
Color 1 1 1
Add 1 1
Query 2```

### 输出

```
7
7
8```

# 题解

## 作者：StudyingFather (赞：26)

注意到本题的的操作 1 是连续段染色，与 [ODT](https://oi-wiki.org/ds/odt/) 的 `assign` 操作类似，因此考虑 ODT 维护颜色段。

操作 2 是对所有同色元素加一个值，考虑对于颜色 $i$ 维护一个 $tag_i$，表示颜色 $i$ 加的值是多少，每次执行操作 2 时，只需要修改 $tag_i$ 即可。

单点查询时，元素 $p$ 的值显然是 $a_p + tag_{col_p}$。

现在考虑 $tag$ 的存在对操作 1 的影响（设某元素原来的颜色为 $c$，新颜色为 $c^\prime$）：

- 首先，由于颜色的更新，$tag_c$ 值应该累加到该元素上，以落实操作 2 的延迟修改。
- 在颜色更新到 $c^\prime$ 后，为了抵消 $tag_{c^\prime}$ 的影响，该元素的值还要减去 $tag_{c^\prime}$，从而确保单点查询时能得到正确的结果。

操作 1 涉及到元素的区间加，用树状数组维护即可。

显然操作 2 时间复杂度 $O(1)$，操作 3 是树状数组单点查询，时间复杂度 $O(\log n)$。

问题来了，本题数据并不保证随机，操作 1 使用 ODT 的时间复杂度还有保障吗？

设一次 `assign` 操作需要合并 $k$ 个区间。在 `assign` 操作后，区间数会减少 $k-1$，同时由于 `assign` 前需要 `split` 端点，又会产生至多 2 个区间。

整个过程中，区间数的增量为 $O(q)$，因为区间数恒为正，`assign` 操作减少的区间数（即我们要合并的区间数）至多也为 $O(q)$。

在执行 `assign` 操作时，每处理一个区间，就要执行一次树状数组的区间修改。因此，该做法的时间复杂度为 $O(q \log n)$。

```cpp
// Problem: E. Colorful Operations
// Contest: Codeforces - Codeforces Round #771 (Div. 2)
// URL: https://codeforces.com/contest/1638/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
struct node {
  int l, r;
  mutable int c;
  node(int l, int r = -1, int c = 0) {
    this->l = l;
    this->r = r;
    this->c = c;
  }
  bool operator<(const node& a) const { return l < a.l; }
};
set<node> odt;
int n, q;
long long tag[1000005];
struct BIT {
  long long a[1000005];
  int n;
  void init(int n) { this->n = n; }
  int lowbit(int x) { return x & (-x); }
  void add(int p, long long x) {
    while (p <= n) {
      a[p] += x;
      p += lowbit(p);
    }
  }
  long long query(int p) {
    long long ans = 0;
    while (p) {
      ans += a[p];
      p -= lowbit(p);
    }
    return ans;
  }
} tr;
auto split(int pos) {
  auto it = odt.lower_bound(node(pos));
  if (it != odt.end() && it->l == pos) return it;
  it--;
  int l = it->l, r = it->r, c = it->c;
  odt.erase(it);
  odt.insert(node(l, pos - 1, c));
  return odt.insert(node(pos, r, c)).first;
}
void assign(int l, int r, int c) {
  auto itr = split(r + 1), itl = split(l);
  for (auto it = itl; it != itr; it++) {
    tr.add(it->l, tag[it->c]);
    tr.add(it->r + 1, -tag[it->c]);
  }
  odt.erase(itl, itr);
  odt.insert(node(l, r, c));
  tr.add(l, -tag[c]), tr.add(r + 1, tag[c]);
}
long long get_tag(int p) {
  auto it = odt.lower_bound(node(p));
  if (it != odt.end() && it->l == p) return tag[it->c];
  return tag[(--it)->c];
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> q;
  odt.insert(node(1, n, 1));
  tr.init(n);
  while (q--) {
    string type;
    cin >> type;
    if (type == "Color") {
      int l, r, c;
      cin >> l >> r >> c;
      assign(l, r, c);
    } else if (type == "Add") {
      int c, x;
      cin >> c >> x;
      tag[c] += x;
    } else {
      int x;
      cin >> x;
      cout << tr.query(x) + get_tag(x) << endl;
    }
  }
  return 0;
}
```

---

## 作者：Doubeecat (赞：16)

> [CF1638E Colorful Operations](https://codeforces.ml/contest/1638/problem/E)
>
> 给定一个长度为 $n$ 的序列，初始时所有元素的值为 $0$ ，颜色为 $1$。你需要实现以下三种操作：
>
> - `Color l r c` ：把 $[l,r]$ 这段的元素颜色改为 $c$
> - `Add c x`：把所有颜色为 $c$ 的元素值都加上 $x$
> - `Query i`：输出元素 $i$ 的值
>
> $n,q \leq 10^6$ 

<!-- more -->

## 思路：

这个题有两种思路，一种是树状数组/线段树套珂朵莉树，一种是带 `lazytag` 的线段树，本文在此讲解第二种思路。

首先我们考虑这个把所有颜色为 $c$ 的元素值都加上 $x$ 的操作显然是不好直接处理的，所以我们把这个操作转化为一个全局打标记的操作。具体来说，我们维护一个 $tag_c$ 表示颜色 $c$ 累计加上的值。

接下来考虑单点查询的操作，这个很简单，我们直接线段树上查询元素 $i$ 的值之后加上 $tag_{color_x}$ 即可。

最后考虑区间修改的操作。我们首先考虑 $[l,r]$ 颜色相同的情况，那么只需要把 $[l,r]$ 这段加上原本颜色的 $tag$，消除掉之前的影响，然后再减去新颜色的 $tag$。这里减去新颜色的 $tag$ 是在于我们最后输出时会加上这个 $tag$，并且我们更新的时候实际上也会加上这个 $tag$，所以很巧妙的处理了颜色对于元素的影响。

但是我们发现，如果 $[l,r]$ 颜色不完全相同的时候会不会挂掉？其实是不会的，我们使用颜色段均摊的知识进行证明。

> 对于一个区间颜色连续段，每次线段树上递归修改的复杂度是 $\Theta (\log n)$
>
> 每次区间染色操作，最多增加 $O(1)$ 个区间颜色连续段，所以单次操作均摊复杂度是 $\Theta(\log n)$。

所以我们的代码就能达到  $\Theta(n + q\log n)$ 的复杂度。而对于一个区间连续段是否颜色相同的维护，我们可以直接在 `pushup` 的过程中暴力维护，可以参考以下代码。



## 代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
#define ll long long
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define pii pair<int,int>
#define mp make_pair
#define int long long

//char buf[1 << 20], *p1, *p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
template <typename T> inline void read(T &t) {
	int v = getchar();T f = 1;t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	t *= f;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args) {
	read(t);read(args...);
}

const int N = 1e6 + 10;

ll a[N],tag[N],n,q;

struct node {
    int l,r;
    ll tag1,tag2,col,sam;
}tree[N<<2];

void pushup(int p) {
    tree[p].col = tree[p << 1].col;
    tree[p].sam = ((tree[p << 1].sam && tree[p << 1 | 1].sam )&& (tree[p << 1].col == tree[p << 1 | 1].col));
}

void build(int p,int l,int r) {
    tree[p].l = l,tree[p].r = r;
    if (l == r) {
        tree[p].col = 1;
        tree[p].sam = 1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(p << 1,l,mid);
    build(p << 1 | 1,mid + 1,r);
    pushup(p);
}

void pushdown(int p) {
    if (tree[p].tag1) {
        tree[p << 1].tag1 += tree[p].tag1;
        tree[p << 1 | 1].tag1 += tree[p].tag1;
        tree[p].tag1 = 0;
    }
    if (tree[p].tag2) {
        tree[p << 1].col = tree[p << 1 | 1].col = tree[p].tag2;
        tree[p << 1].tag2 = tree[p << 1 | 1].tag2 = tree[p].tag2;
        tree[p << 1].sam = tree[p << 1 | 1].sam = 1;
        tree[p].tag2 = 0;
    }
}

void change(int p,int l,int r,int k) {
    if (tree[p].l >= l && tree[p].r <= r && tree[p].sam) {
        tree[p].tag1 += tag[tree[p].col];
        tree[p].col = k;
        tree[p].tag2 = k;
        tree[p].sam = 1;
        tree[p].tag1 -= tag[k];
        return ;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    pushdown(p);
    if (l <= mid) change(p << 1,l,r,k);
    if (r > mid) change(p << 1 | 1,l,r,k);
    pushup(p);
}

ll query(int p,int x) {
    //printf("%lld %lld %lld %lld %lld\n",p,tree[p].l,tree[p].r,tree[p].tag2,tree[p].col);
    if (tree[p].l == tree[p].r) {
        return tree[p].tag1 + tag[tree[p].col];
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    pushdown(p);
    if (x <= mid) return query(p << 1,x);
    else return query(p << 1 | 1,x);
}

signed main() {
    read(n,q);
    build(1,1,n);
    for (int i = 1;i <= q;++i) {
        char opt[10];scanf("%s ",opt);
        if (opt[0] == 'C') {
            int x,y,w;read(x,y,w);
            change(1,x,y,w);
        }
        if (opt[0] == 'A') {
            int x,k;read(x,k);
            tag[x] += k;
        }
        if (opt[0] == 'Q') {
            int x;read(x);
            printf("%lld\n",query(1,x));
        }
    }
	return 0;
}
```



---

## 作者：Cry_For_theMoon (赞：5)

# CF1638E Colorful Operations

开题的时候看到是数据结构很开心，感觉可以秒了。结果最后虽然想到了正解，但是写挂到最后都没调出来...

## 题意：

给定一个初始全 $0$ 的序列 $a_1,a_2,...,a_n$，每个元素的颜色都为 $1$。接下来执行 $q$ 次操作：

- ```Color l r c``` 把区间 $[a_l,a_r]$ 的元素颜色都置为 $c$。
- ```Add c x``` 把当前所有颜色为 $c$ 的元素增加 $x$。（$x$ 可负）
- ```Query x``` 询问当前 $a_x$ 的值。

$n,q\le 10^6$。

## 分析：

### Part 1.

本题操作有三个，有点复杂。我们来把这个问题弱化一下：如果没有操作 $1$，每个元素的初始颜色可以不同。然后保留操作 $2$ 和 $3$，如何快速实现。

那么我们发现我们可以对颜色打 $lazy$：一次 ```Add``` 操作就令 $lazy_c\leftarrow lazy_c+x$。然后一次询问，设第 $x$ 个元素的颜色是 $c$，输出当前的 $lazy_c$ 即可。

这样，是 $O(n+q)$ 的。

### Part 2.

让我们回到原问题。

因为 $2$ 操作不可能找到所有位置去修改，所以依然是以打 $lazy$ 的形式实现下来。

那么我们肯定得支持区间推平，单点查询的数据结构，来查询每次询问时第 $x$ 个元素的颜色。一般的思路是线段树，本题也可以用 ```std::set``` 来暴力维护。这是简单的。

由于询问是单点的，我们可以考虑它在时刻 $1\sim t$ 的变化（$t$ 是一次询问该位置的值的时刻）：

设该点 $x$，在时刻 $[i,j]$ 上是颜色 $c$ 的，那么在 $i-1$ 时刻，我们让他减去 $lazy_{c}$，在 $j$ 时刻，我们让他加上 $lazy_j$。

另外，这等价于在 $i$ 时刻减掉 $lazy_i$ 而不是在 $i-1$ 时刻去减，因为 $i$ 时刻肯定是一次覆盖操作。（除非 $i=1$，但是这个时候减去的是 $0$）。

或者说，考虑这样的过程：

对于一次覆盖操作，对于被覆盖到的每个点，如果它以前颜色为 $c'$，那么该点的值加上 $lazy_{c'}$；如果覆盖后颜色为 $c$，那么该点的值加上 $lazy_{c}$。

对于一次询问操作，先询问出该点当前的值 $val$ 和颜色 $c$。$val+lazy_c$ 就是答案。

我们需要快速支持这个问题。

### Part 3.

减去 $lazy_c$ 是好做的，$[l,r]$ 进行区间减法即可。

 考虑这样的想法：维护所有的颜色连续段，称一个颜色为 $c$ 的极大连续段为一条颜色为 $c$ 的线段。显然每个状态下两两线段交集为空，且所有线段的并集为 $[1,n]$。

每次加入一条操作 $[l,r]$，暴力找出所有和 $[l,r]$ 有交的线段，由于一条线段上的所有点颜色相同，那么上文提到的加上 $lazy_{c'}$ 这个操作就好维护了。

这样的复杂度是正确的：一条线段只会被删除一次，而一次操作会增加常数 ($\le 5$ ) 条线段。所以可以用 ```std::set``` 来维护。

笔者赛时的想法是考虑类似 Segment beats 的做法：用 $c_x$ 表示节点 $x$ 的所表示区间内，所有元素的颜色是否全为某个统一的值 $val$（如果是，则为 $val$；否则为 $0$）。

那么一次修改的时候，如果询问区间 $[q_l,q_r]$ 不完全包含当前节点 $x$ 的表示区间 $[l,r]$，就还是正常递归下去。否则，常规线段树是直接进行修改了，但本题中可能这个区间的颜色不全相同（$c_x=0$），此时我们要继续递归下去，直到 $c_x$ 非 $0$ 为止才修改。

修改是加法。我们假设它是 $O(1)$ 的，那么我们首先可以得到一个结论：复杂度是 $O(q\log n)$ 的，因为还是有 $O(q)$ 条线段，然后每条线段会在线段树上被拆分为 $\log $ 条（或者也可以势能分析）。

然后一个 naive 的想法可能是，还要维护一个 bit 执行区间加法，每次的“修改”放在 bit，这样就是 $O(q\log^2 n)$ 的，但是没有必要。我们直接在线段树的每个节点维护一个加法 tag，修改放在 tag 上就好了。

注意到这样，就有区间颜色覆盖的 tag，和加法的 tag，这两个 tag 互相没啥联系（不像乘法 tag 和加法 tag），所以可以放心 pushdown。如果不放心，可以直接把加法 tag 标记永久化，也是好实现的。

两种做法的时间复杂度都是 $O(q\log n)$​。

## 两种实现的代码：

### 1. set 实现

```cpp
const int MAXN=1e6+10,INF=1e9;
int n,q;
ll lazy[MAXN];
struct BIT{
    ll t[MAXN];
    void upd(int x,ll val){for(;x<=n;x+=lowbit(x))t[x]+=val;}
    void upd(int l,int r,ll val){upd(l,val);upd(r+1,-val);}
    ll qry(int x){ll ret=0;for(;x;x-=lowbit(x))ret+=t[x];return ret;}
}bit;
set<array<int,3> >s;
int upd(int l1,int r1,int l2,int r2,int prec,int t){
    if(r1<l2||l1>r2)return 0;
    if(l1<=l2&&r1>=r2){
        bit.upd(l2,r2,lazy[prec]);
        if(l1!=l2)s.insert({l1,l2-1,prec});
        if(r1!=r2)s.insert({r2+1,r1,prec});
    }else if(l1>=l2&&r1<=r2){
        bit.upd(l1,r1,lazy[prec]);
    }else if(l1<=l2){
        bit.upd(l2,r1,lazy[prec]);
        if(l1!=l2)s.insert({l1,l2-1,prec});
    }else{
        bit.upd(l1,r2,lazy[prec]);
        if(r1!=r2)s.insert({r2+1,r1,prec});
    }
    s.erase({l1,r1,prec});
    return 1;
}
void Add(int t,int l,int r,int c){
    bit.upd(l,r,-lazy[c]);
    auto it=s.upper_bound({l,r,INF});
    it--;
    array<int,3>tmp=*it;
    upd(tmp[0],tmp[1],l,r,tmp[2],t);
    int pre=tmp[1];
    while(1){
        it=s.upper_bound({pre,INF,INF});
        if(it==s.end())break;
        tmp=*it;
        if(tmp[0]>r)break;
        upd(tmp[0],tmp[1],l,r,tmp[2],t);
        pre=tmp[1];
    }
    s.insert({l,r,c});
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    s.insert({1,n,1});
    s.insert({n+1,n+1,n+1});
    rep(i,1,q){
        string op;
        cin>>op;
        if(op=="Color"){
            int l,r,c;cin>>l>>r>>c;
            Add(i,l,r,c);
        }else if(op=="Add"){
            int c,x;cin>>c>>x;
            lazy[c]+=x;
        }else{
            int x;cin>>x;
            auto it=s.upper_bound({x,INF,INF});
            it--;
            int c=(*it)[2];
            ll ans=bit.qry(x);
            ans+=lazy[c];
            cout<<ans<<endl;
        }
    }
 
    return 0;
}
```

### 2. 线段树实现（推荐）

```cpp
const int MAXN=1e6+10;
int n,q;
ll lazy[MAXN];
string op;
struct Seg{
    int c[MAXN<<2],ctag[MAXN<<2];
    ll tag[MAXN<<2],s[MAXN<<2];
    void pushup(int x){c[x]=(c[lc(x)]==c[rc(x)])?c[lc(x)]:0;}
    void add(int x,ll val){s[x]+=val;tag[x]+=val;}
    void pushdown(int x){if(ctag[x])c[lc(x)]=c[rc(x)]=ctag[lc(x)]=ctag[rc(x)]=ctag[x],ctag[x]=0;}
    void build(int x,int l,int r){
        c[x]=1;if(l==r)return;
        int mid=(l+r)>>1;build(lc(x),l,mid);build(rc(x),mid+1,r);
    }
    void upd(int x,int l,int r,int ql,int qr,int col){
        if(ql<=l&&qr>=r){
            if(c[x]){
                add(x,lazy[c[x]]);add(x,-lazy[col]);
                c[x]=ctag[x]=col;
                return;
            }
            int mid=(l+r)>>1;pushdown(x);
            upd(lc(x),l,mid,ql,qr,col);
            upd(rc(x),mid+1,r,ql,qr,col);
            pushup(x);
            return;
        }
        int mid=(l+r)>>1;pushdown(x);
        if(ql<=mid)upd(lc(x),l,mid,ql,qr,col);
        if(qr>mid)upd(rc(x),mid+1,r,ql,qr,col);
        pushup(x);
    }
    ll qry(int x,int l,int r,int pos){
        if(l==r)return s[x]+lazy[c[x]];
        int mid=(l+r)>>1;pushdown(x);
        ll ret=tag[x];if(pos<=mid)ret+=qry(lc(x),l,mid,pos);else ret+=qry(rc(x),mid+1,r,pos);
        pushup(x);return ret;
    }
}t;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    t.build(1,1,n);
    rep(i,1,q){
        cin>>op;
        if(op=="Color"){
            int l,r,c;cin>>l>>r>>c;
            t.upd(1,1,n,l,r,c);
        }else if(op=="Add"){
            int c,x;cin>>c>>x;
            lazy[c]+=x;
        }else{
            int x;cin>>x;
            cout<<t.qry(1,1,n,x)<<endl;
        }
    }
    return 0;
}
```



---

## 作者：GaryH (赞：5)

## CF1638E 题解

给一个自认为很无脑很好想的做法，

用到了区间加单点查询，以及区间赋值单点查询两种线段树，

缺点是常数巨大，需要加 `fread` 快读才能卡过。

**题意**：

你需要维护一个长为 $n$ 的序列，其中每个位置上有权值和颜色。

最开始时序列所有位置的权值都为 $0$，颜色都为 $1$。

维护过程中可能会有三种要求共 $q$ 次，具体如下：

1. 将区间 $[l,r]$ 内所有位置的颜色改成 $c$；
2. 将所有颜色是 $c$ 的位置的权值加 $x$；
3. 查询位置 $i$ 的权值。

> $n,q\le10^6$。

**做法**：

首先看到的是改变权值的唯一途径是对某种特定颜色的全局加，

故对每种颜色维护全局加的标记是好想的，即记 $tag_c$ 代表所有颜色为 $c$ 的位置被一起加的和，

则我们只需要维护数组 $col$ 代表每个位置的颜色，同时维护数组 $b$ 代表每个位置上已经更新过的权值，

即 $b_i=a_i-tag_{col_i}$，那么查询操作就是简单的，我们直接输出 $a_i=b_i+tag_{col_i}$ 即可。

那现在唯一需要解决的问题就是，在一个位置 $i$ 的颜色从 $c$ 变成 $c'$ 时，为确保答案的正确性，

我们需要更新这个位置的权值，即将 $b_i$ 改成 $b_i+tag_{c}-tag_{c'}$，代表：

我们加上这个位置应该受到的权值的改变，即因为该位置颜色是 $c$ 而导致的位置权值的变化量；

并扣除其不应该受到的值的改变，即其刚从颜色 $c$ 变成 $c'$，所有 $c'$ 颜色以前对应的变化都不应有影响。

显然，这时候我们不能枚举区间中的每个位置并一个个维护，这样的复杂度还不如暴力，

但是我们发现，对于区间中的一个颜色同为 $c$ 的连续段，这些位置的权值加的数是一样的，

即都是 $tag_{c'}-tag_{c}$，那么如果我们能快速找出这些连续段，并对每个连续段内所有数同时维护，

则复杂度就是所有遇到的连续段个数之和的级别，再带个用线段树维护 $b,col$ 数组的 $\log$。

看上去这个复杂度还是不对？这里就要用到本题解中唯一的观察，即：

遇到的颜色段数之和是 $O(q)$ 级别的。以下给出证明：

我们发现，我们每次区间赋颜色时，除了区间中最左和最右的连续段，

其他所有区间中的连续段都会完全被覆盖，最后一起变成一个大的颜色连续段，

故一个连续段只会被遇到一次，因为在遇到之后我们就会将其删掉，

只有在每次操作结束后，我们会在序列中增加不超过三个连续段，即 $O(1)$ 个连续段，

所以所有操作中增加的连续段数之和是 $O(q)$ 级别的，我们遇到的连续段数也就是 $O(q)$ 级别的。

于是，我们只要支持快速找颜色连续段即可，而支持这个操作，我们可以再维护两个数组 $L,R$，

其中 $L_i,R_i$ 分别代表位置 $i$ 所在连续段的左右端点，那当需要找区间 $[l,r]$ 中的连续段时，

我们只需要从 $l$ 开始跳，每次跳到当前位置所在连续段的右端点的右边，直到跳到 $r$ 右边结束。

维护 $L,R$ 数组是简单的，我们每次会将区间 $[l,r]$ 内所有位置的 $L,R$ 值分别改成 $l$ 和 $r$，

以及 $l$ 左边某些位置的 $R$ 值改成 $l-1$，和 $r$ 右边某些位置的 $L$ 值改成 $r+1$，

故我们用区间加单点查询的线段树维护 $b$，用区间赋值单点查询的线段树维护 $col,L,R$ 即可。

时间复杂度是 $O(q\log n)$ 的，但因为常数大，所以需要 `fread` 快读快输才能卡过。

[**code**](https://codeforces.com/contest/1638/submission/146472244) 见链接。

---

## 作者：Aryper (赞：4)

Colorful Operations

[Github Blog](https://onlypath.github.io/2022/03/12/CF1638E/)。

神奇均摊科技。

颜色加可以直接做一个颜色标记累加在上面。

修改区间的时候直接暴力找到每个该区间内线段树上颜色相同的子区间并打上懒标记，最后查询的时候直接在线段树上单点查即可（比较 Trivial 的 lazytag 下传）。

然后就没了。

为什么这个复杂度是对的？

我们知道，每次染色操作，至多会增加 $O(1)$ 个颜色相同的子区间。我们假设第 $i$ 次操作的区间中有 $O(\Delta x_i)$ 个颜色相同的子区间（不是线段树上的）需要暴力修改，则必然在之前需要 $O(\Delta x_i)$ 次染色操作，从而有 $O(\sum \Delta x_i)\le O(q)$，因此需要操作的颜色相同的子区间数量为 $O(q)$ 个。

但是我们是在线段树上操作的，意味着每个这样颜色相同的子区间我们都需要把它拆分成 $\log$ 个线段树上的区间，从而我们的染色操作的总复杂度是 $O(q\log n)$ 的。

这样，我们最终的复杂度就是 $O((n+q)\log n)$ 的。

代码：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1e6;

ll n,q;
ll tag_val[N+5];
char s[10];

struct Sgt{
  ll tag_same,tag_laz;
  #define tag_same(x) tree[x].tag_same
  #define tag_laz(x) tree[x].tag_laz
}tree[N*4+5];

inline void Build(ll p,ll l,ll r) {
  tag_same(p)=1;
  if(l==r) return;ll mid=(l+r)>>1;
  if(l<=mid) Build(p<<1,l,mid);
  if(r>mid) Build(p<<1|1,mid+1,r);
}

inline void Pushup(ll p) {
  if(tag_same(p<<1)==tag_same(p<<1|1)) tag_same(p)=tag_same(p<<1);
  else tag_same(p)=0;
}

inline void Pushdown(ll p) {
  tag_laz(p<<1)+=tag_laz(p);tag_laz(p<<1|1)+=tag_laz(p);
  if(tag_same(p)) {
    tag_same(p<<1)=tag_same(p<<1|1)=tag_same(p);
  }
  tag_laz(p)=0;
}

inline void Modify(ll p,ll lp,ll rp,ll l,ll r,ll col) {
  if(lp>=l&&rp<=r) {
    if(tag_same(p)) {
      tag_laz(p)+=tag_val[tag_same(p)];
      tag_laz(p)-=tag_val[col];
      tag_same(p)=col;
      return;
    }
    ll mid=(lp+rp)>>1;
    Modify(p<<1,lp,mid,l,r,col);Modify(p<<1|1,mid+1,rp,l,r,col);
    Pushup(p);
    return;
  }
  ll mid=(lp+rp)>>1;Pushdown(p);
  if(l<=mid) Modify(p<<1,lp,mid,l,r,col);
  if(r>mid) Modify(p<<1|1,mid+1,rp,l,r,col);
  Pushup(p);
}

inline ll Ask(ll p,ll lp,ll rp,ll x) {
  if(lp==rp) return tag_laz(p)+tag_val[tag_same(p)];
  ll mid=(lp+rp)>>1;Pushdown(p);
  if(x<=mid) return Ask(p<<1,lp,mid,x);
  else return Ask(p<<1|1,mid+1,rp,x);
}

inline ll read() {
  ll ret=0,f=1;char ch=getchar();
  while(ch<48||ch>57) {if(ch==45) f=-f;ch=getchar();}
  while(ch>=48&&ch<=57) {ret=(ret<<3)+(ret<<1)+ch-48;ch=getchar();}
  return ret*f;
}

inline void write(ll x) {
  static char buf[22];static ll len=-1;
  if(x>=0) {do{buf[++len]=x%10+48;x/=10;}while(x);}
  else {putchar(45);do{buf[++len]=-(x%10)+48;x/=10;}while(x);}
  while(len>=0) putchar(buf[len--]);
}

inline void writeln(ll x) {write(x);putchar(10);}

int main() {

  n=read();q=read();
  Build(1,1,n);

  while(q--) {
    scanf("%s",s);
    if(s[0]=='C') {
      ll l,r,c;
      l=read();r=read();c=read();
      Modify(1,1,n,l,r,c);
    }
    if(s[0]=='A') {
      ll c,x;
      c=read();x=read();tag_val[c]+=x;
    }
    if(s[0]=='Q') {
      ll x=read();
      writeln(Ask(1,1,n,x));
    }
  }

  return 0;
}
```

---

## 作者：intel_core (赞：3)

因为这题有推平操作，并且也没有其它颜色的区间操作，所以考虑 $\text{ODT}$ 维护颜色序列。

2 操作是对一个颜色的点整体 $+x$ ，但显然不能遍历一遍 $\text{ODT}$ 暴力地做；所以我们考虑维护每个颜色的整体 $\text{tag}$ ，操作 2 直接修改一个颜色的 $\text{tag}$ 就可以了。然后我们维护一个树状数组，存储 $a_i-tag_{color_i}$

接着考虑 1 操作，在 $\text{ODT}$ 上取出 $[l,r]$ 内的颜色块后，考虑将一个颜色块的颜色从 $x'$ 换成 $x$ 之后，块内的数会发生怎样的变化。

因为我们只是改变了颜色块的颜色，所以我们需要让内部的点值保持不变；不难发现，只需将颜色块对应区间都加上两种颜色对应的 $\text{tag}$ 的差即可，即 $tag_x-tag_{x'}$。

接着我们考虑这个东西的时间复杂度，很明显，2 操作的复杂度是 $O(1)$ ，3操作单次复杂度为 $O(\log n)$

考虑 1 操作的时间复杂度，很显然，每次 1 操作最多给 $\text{ODT}$ 加上 $2$ 个颜色块；如果一个颜色块在一次 1 操作中被遍历了，很显然在这次 1 操作后就会被删除。所以每个颜色块只会被遍历 1 次。

因为我们最多只会新建 $O(n)$ 个颜色块，而每个颜色块最多被遍历 $1$ 次，所以 1 操作的总复杂度为 $O(n\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e6+10;
#define ll long long
#define fi first
#define se second
int n,q;ll c[NR];

struct node{
	int l,r,color;
	bool operator <(const node &T)const{
		return l<T.l;
	}
}; 
set<node>s;
#define IT set<node>::iterator

ll a[NR];
int lowbit(int x){
	return x&(-x);
}
void add(int x,ll y){
	for(int i=x;i<=n;i+=lowbit(i))
		a[i]+=y;
}
ll sum(int x){
	ll res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=a[i];
	return res;
}
void modify(int l,int r,ll x){
	add(l,x);add(r+1,-x);
}

IT split(int pos){
	IT it=s.lower_bound((node){pos,0,0});
	if(it!=s.end()&&(*it).l==pos)return it;
	it--;
	int l=(*it).l,r=(*it).r,co=(*it).color;
	s.erase(it);
	s.insert((node){l,pos-1,co});
	return s.insert((node){pos,r,co}).fi;
}
void assign(int l,int r,int x){
	IT it1=split(r+1),it2,it3=split(l);it2=it3;
	while(it1!=it2){
		modify((*it2).l,(*it2).r,c[(*it2).color]-c[x]);
		it2++;
	}
	s.erase(it3,it1);
	s.insert((node){l,r,x});
}
int query(int x){
	IT it=s.lower_bound((node){x,0,0});
	if(it!=s.end()&&(*it).l==x)return (*it).color;
	it--;
	return (*it).color;
}

int main(){
	cin>>n>>q;
	s.insert((node){1,n,1});
	while(q--){
		int x,y,z;char opt[10];
		scanf(" %s %d",opt,&x);
		if(opt[0]=='C'){
			scanf(" %d%d",&y,&z);
			assign(x,y,z);
		}
		if(opt[0]=='A'){
			scanf(" %d",&y);
			c[x]+=y;
		}
		if(opt[0]=='Q')printf("%lld\n",sum(x)+c[query(x)]);
	}	
	return 0;
}
```

---

## 作者：洛谷小灵 (赞：3)

## 前言

- 语言：Java
- 参考资料：https://zhuanlan.zhihu.com/p/467535379
   > 若可以看懂上面这篇文章，那么此篇题解可以不看，此题解作为上面的补充。

## 解析

个人认为本题的难点应该是如何维护这个颜色，我一开始是想用一个结点内部维护一个 `color` 和 `val` 属性，表示每个结点的颜色和值，用的是线段树，后面我发现如果一个区间内的颜色不同，那么 color 到底应该填什么呢...，val 又表示啥呢？

**当然，我这是普通的线段树模板而已，才学不久，看来还是我太菜了...** 

**回到主题：**

我们先考虑单点操作，三种操作如下：

- `Color x c`：将元素 $i$ 的颜色修改为 $c$。
- `Add c x`：将所有颜色为 $c$ 的元素增加 $x$。
- `Query i`：打印第 $i$ 个元素。

首先我们需要一个 $Lazy[color]$ 来保存每个颜色的总和，因为我们总不可能遍历每一个颜色为 $c$ 的元素都增加 $x$ 吧？这样效率很低，可以考虑先操作，等该数的颜色发生变化时，再去更新元素的值，这就是一个延迟操作的效果。

还需要一个 $color[i]$ 保持元素 $i$ 的颜色。

对于操作 2 来说：

```java
Lazy[c] += x
```

对于操作 3 来说：

```java
A[x] + Lazy[color[x]] // 输出需要加上 Lazy ，这就是延迟
```

对于操作 1 来说：

```java
A[x] += Lazy[color[x]] // 颜色准备发生改变，更新当前元素`=>`触发延迟操作
color[x] = c // 更新颜色
A[x] -= Lazy[c] // 因为我们输出时，我们要保证 A[x] + Lazy[color[x]]，因此需要减去 Lazy[c]
```

**手动模拟一下：**


```txt
【1】Add 1 7
【2】Query 1 7
【3】Add 2 4
【4】Query 2
【5】Color 1 2
【6】Query 1

====================
Lazy:  0 0 0
Color: 1 1 1
A:     0 0 0
====================
【1】Lazy[1] += 7
====================
Lazy:  7 0 0
Color: 1 1 1
A:     0 0 0
====================
【2】A[1] + Lazy[color[1]] // print 7
【3】Lazy[2] += 4
====================
Lazy:  7 4 0
Color: 1 1 1
A:     0 0 0
====================
【4】A[2] + Lazy[color[2]] // print 7
【5】A[1] += Lazy[color[1]]
     color[1] = 2
     A[1] -= Lazy[2]
====================
Lazy:  7 4 0
Color: 1 1 1
A:     7 0 0
--------------------
Lazy:  7 4 0
Color: 2 1 1
A:     7 0 0
--------------------
Lazy:  7 4 0
Color: 2 1 1
A:     3 0 0
====================
【6】A[1] + Lazy[color[1]] // print 7
```

**明白了单点操作，回来看看区间操作：**

采用线段树和LazyTag的方式来进行实现。

`colorVal[color]`：同上面的 Lazy

需要一个结点，里面维护如下元素：

- `same`：该区间的所有元素是否相同
- `color`：该结点的颜色，当 `same` 为 true 时，表示该区间内所有的颜色
- `lazy`：懒标记，同时也作为该元素的值

对于操作 2 和 操作 3 来说，其实和单点的是一样。对于操作 1 来说也差不多。

对于操作 1：只修改同一种颜色的区间，否则就一定往下找，最后一个点一定为 true。

## AC Code


```java
public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StreamTokenizer st = new StreamTokenizer(br);
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    static final int MAX = 1000005;
    static long[] colorVal = new long[MAX];
    static Node[] T = new Node[MAX << 2];
    static int n, m;

    public static void main(String[] args) throws Exception {
        n = nextInt(); m = nextInt();
        build(1, 1, n);
        while(m-- != 0) {
            String opt = nextStr();
            if(opt.equals("Color")) update(1, nextInt(), nextInt(), nextInt());
            else if(opt.equals("Add")) colorVal[nextInt()] += nextInt();
            else if(opt.equals("Query")) {
                int v = nextInt();
                out.println(query(1, v, v));
            }
        }
        out.flush();
    }

    public static void build(int p, int start, int end) {
        T[p] = new Node(start, end);
        if(start == end) {
            T[p].color = 1;
            T[p].same = true;
            return;
        }
        int mid = (start + end) / 2;
        build(L(p), start, mid);
        build(R(p), mid + 1, end);
        pushUp(p);
    }

    public static void update(int p, int start, int end, int k) {
        // 只修改同一种颜色的区间，否则就一直往下找，最后一个点一定为 true
        if(start <= T[p].left && end >= T[p].right && T[p].same) {
            T[p].lazy += colorVal[T[p].color];
            T[p].color = k;
            T[p].lazy -= colorVal[T[p].color];
            return;
        }
        pushDown(p);
        int mid = (T[p].left + T[p].right) / 2;
        if(start <= mid) update(L(p), start, end, k);
        if(end > mid) update(R(p), start, end, k);
        pushUp(p);
    }

    public static long query(int p, int start, int end) {
        long res = 0;
        if(start <= T[p].left && end >= T[p].right)
            return T[p].lazy + colorVal[T[p].color];
        pushDown(p);
        int mid = (T[p].left + T[p].right) / 2;
        if(start <= mid) res += query(L(p), start, end);
        if(end > mid) res += query(R(p), start, end);
        return res;
    }

    public static void pushDown(int p) {
        // 因为我们修改的是同一种颜色的区间，因此也对同一种颜色的区间下传
        if(T[p].same) {
            T[L(p)].lazy += T[p].lazy;
            T[R(p)].lazy += T[p].lazy;
            T[L(p)].color = T[p].color;
            T[R(p)].color = T[p].color;
            T[p].lazy = 0;
        }
    }

    public static void pushUp(int p) {
        // 只更新同一种颜色的区间
        if(T[L(p)].same && T[R(p)].same && T[L(p)].color == T[R(p)].color) {
            T[p].same = true;
            T[p].color = T[R(p)].color;
        } else {
            T[p].same = false;
        }
    }

    public static int L(int p) { return p<<1; };
    public static int R(int p) { return p<<1|1; };

    public static int nextInt() throws Exception {
        st.nextToken();
        return (int) st.nval;
    }

    public static String nextStr() throws Exception {
        st.nextToken();
        return st.sval;
    }
}

class Node {
    int left, right;
    int color; // 该区间颜色
    long lazy; // lazyTag
    boolean same; // 该区间内的颜色是否完全相同
    public Node(int left, int right) {
        this.left = left;
        this.right = right;
    }
}
```





---

## 作者：do_while_true (赞：3)

每次区间染色，会删除若干个颜色段，添加 $\mathcal{O}(1)$ 个颜色段。因此颜色段总数是 $\mathcal{O}(n+q)$．

采用平衡树（用 set 即可）维护极长连续颜色段，维护每个颜色增加值大小的 $tag$，并用树状数组维护每个点的答案减去对应颜色的 $tag$ 值。

`Add`：直接给对应颜色的 $tag$ 进行修改。

`Color`：当删除一个颜色段时，就将其区间加上原先颜色的 $tag$ 值；当添加一个颜色段时，就将其区间减去新颜色的 $tag$ 值（因为新颜色原先的 $tag$ 并没有加在这一段上，需要减去）。

`Query`：输出答案即可，即树状数组维护的值加上对应颜色的 $tag$ 值。

不难发现树状数组操作次数和颜色段次数呈线性，时间复杂度 $\mathcal{O}((n+q)\log n)$．

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int>pii;
typedef std::pair<ll,int>pli;
typedef std::pair<ll,ll>pll;
typedef std::vector<int>vi;
typedef std::vector<ll>vll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=1000010;
inline int lowbit(int x){return x&(-x);}
int n,q;
ll tree[N],tag[N];
void modify(int x,ll v){
	for(;x<=n;x+=lowbit(x))tree[x]+=v;
}
void change(int x,int y,ll v){
	modify(x,v);
	if(y<n)modify(y+1,-v);
}
ll query(int x){
	ll s=0;
	for(;x;x-=lowbit(x))s+=tree[x];
	return s;
}
struct Node{
	int l,r,c;
	Node(int x=0,int y=0,int z=0){
		l=x;r=y;c=z;
	}
	bool operator < (const Node &x)const{
		return l<x.l;
	}
};
set<Node>st;
#define IT set<Node>::iterator
IT split(int pos){
	auto it=st.lower_bound(Node(pos,pos,0));
	if(it!=st.end()&&(*it).l==pos)return it;
	--it;
	int L=(*it).l,R=(*it).r,C=(*it).c;
	st.erase(it);
	st.insert(Node(L,pos-1,C));
	return st.insert(Node(pos,R,C)).first;
}
void assign(int l,int r,int c){
	auto itr=split(r+1),itl=split(l);
	auto it=split(l);
	for(;it!=itr;++it)
		change((*it).l,(*it).r,tag[(*it).c]);
	st.erase(itl,itr);
	st.insert(Node(l,r,c));
	change(l,r,-tag[c]);
}
int Col(int l,int r){
	auto it=st.lower_bound(Node(l,r,0));
	while(it==st.end()||(!(l>=(*it).l && r<=(*it).r)))--it;
	return (*it).c;
}
signed main(){
	#ifdef do_while_true
	freopen("data.in","r",stdin);
	#endif 
	read(n,q);
	st.insert(Node(1,n,1));
	while(q--){
		char ch=getchar();while(ch!='C'&&ch!='A'&&ch!='Q')ch=getchar();
		if(ch=='A'){
			int c,x;read(c,x);
			tag[c]+=x;
		}
		else if(ch=='Q'){
			int x;read(x);
			cout << query(x)+tag[Col(x,x)] << '\n';
		}
		else{
			int l,r,c;read(l,r,c);
			assign(l,r,c);
		}
	}
	return 0;
}
```

---

## 作者：Qiaoqia (赞：3)

第一次在赛场上想出只有那么点人过的 E 留念。~~可是在 C 上卡了好久没时间调了。~~

如果只能改成一种颜色，那么只需要记录一个颜色加标记，把一段修改成这个颜色前先把这一段都减去该颜色现在已有的标记，最后查询位置上的值再加上加标记就可以了（好像某场 ABC 出过？），但是如果进行多次颜色更改，那这样就会丢失原来的标记。

一种朴素的弥补想法是在进行一次修改之前，先把一个位置先前颜色的标记加到那个位置上，再进行修改颜色。因为只有最多 $2q$ 个颜色间的分界点，而一个分界点被覆盖之后就会消失，所以若每次对整块颜色进行这样的操作，最多 $O(q)$ 次覆盖，复杂度就是对的。

用一个树状数组维护每个位置的值，一个树状数组维护颜色，一个树状数组维护断点就可以了。找到一块可以通过二分来实现，即找到第一个断点前缀和多了的位置，直接二分是两只 $\log$ 的，树状数组上二分应该可以做到一只 $\log$ 但比赛的时候为了求稳赶时间我直接二分了。需要注意的是，维护断点的树状数组是单点修改查前缀和的，其它两个是区间修改查单点的。~~最后 4min 写完一遍过样例，因为这个搞错却喜提 RE。~~

```cpp
constexpr int N = 100'0006;
long long n, q, cnt[N];
struct bit {
    long long t[N];
    void upd(int x, int v) {
        for ( ; x <= n + 1; x += x & -x) t[x] += v;
    }
    long long qry(int x) {
        long long an = 0;
        for ( ; x; x -= x & -x) an += t[x];
        return an;
    }
    void add(int l, int r, int v) {
        upd(l, v), upd(r + 1, -v);
    }
} bre, col, sum;
void cover(int L, int R, int c) {
    int oL = L;
    while ("Powered By CP Editor"[0]) {
        int l = L, r = R, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (bre.qry(mid) == bre.qry(L)) l = mid + 1;
            else ans = mid, r = mid - 1;
        }
        bool flag = 0;
        if (ans == -1) {
            ans = R + 1;
            flag = 1;
        }
        int oc = col.qry(L);
        sum.add(L, ans-1, cnt[oc]);
        col.add(L, ans-1, -oc), col.add(L, ans-1, c);
        if (bre.qry(ans) != bre.qry(ans-1)) bre.upd(ans, -1);
        L = ans;
        if (flag == 1) break;
    }
    if (bre.qry(R + 1) == bre.qry(R)) bre.upd(R + 1, 1);
    if (bre.qry(oL) == bre.qry(oL-1)) bre.upd(oL, 1);
}
void main() {
    std::cin >> n >> q;
    col.add(1, n, 1);
    bre.upd(1, 1);
    while (q--) {
        std::string opt;
        std::cin >> opt;
        if (opt == "Color") {
            int a, b, c;
            std::cin >> a >> b >> c;
            cover(a, b, c);
            sum.add(a, b, -cnt[c]);
        }
        else if (opt == "Add") {
            int a, b;
            std::cin >> a >> b;
            cnt[a] += b;
        }
        else {
            int a;
            std::cin >> a;
            std::cout << sum.qry(a) + cnt[col.qry(a)] << '\n';
        }
    }
}
```

---

## 作者：Buried_Dream (赞：1)

## Solution

有很明显的区间覆盖操作，我们考虑用 ODT。

操作二直接暴力的话显然不可以，我们可以给每个颜色维护一个 $tag_{col_i}$，表示 $col_i$ 这个颜色需要加的数，每次操作二的时候直接给这个颜色的 $tag$ 加上即可。

操作一中，当颜色修改的时候，要把当前颜色之前没有加上的 $tag$ 加上，

所以需要一个数据结构来高效维护区间加，单点查，线段树，树状数组都可以。

最后加完之后要在覆盖后的区间减去一个 $tag$，因为当覆盖完之后，当前的颜色之前加的数他并不需要加，所以提前减去就可以避免这个问题了。

操作三就是树状数组单点查。

注意需要开 long long。
```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.9.6
 **/
#include<set>
#include<cmath>
#include<queue>
#include<cstdio>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar
#define int long long
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
#define debug cout << "i ak ioi" << "\n"
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}


int n, q, tag[N];

namespace Bit {
	int c[N];
	#define lowbit(x) (x & -x)
	void add(int x, int k) {for(; x <= n; x += lowbit(x)) c[x] += k; }
	int Query(int x) {int res = 0; for(; x; x -= lowbit(x)) res += c[x]; return res;}
}
using namespace Bit;

namespace Chtholly_tree {
	#define It set <Node>::iterator
	struct Node {
		int l, r; mutable int v;
		Node (int L, int R = 0, int V = 0) : l(L), r(R), v(V) {}
		bool operator < (const Node &x) const {return l < x.l; }
	}; set <Node> s;
	It Split(int pos) {
		It it = s.lower_bound(Node(pos));
		if(it != s.end() && it -> l == pos) return it;
		--it; int L = it -> l, R = it -> r, V = it -> v;
		s.erase(it); s.insert(Node(L, pos - 1, V));
		return s.insert(Node(pos, R, V)).first;
	}
	void Cover(int l, int r, int val) {
		It itr = Split(r + 1), itl = Split(l);
		for(It it = itl; it != itr; ++it) 
			add(it -> l, tag[it -> v]), add(it -> r + 1, -tag[it -> v]);
		s.erase(itl, itr), s.insert(Node(l, r, val));
		add(l, -tag[val]),  add(r + 1, tag[val]);
	}
	int getans(int pos) {
		It it = s.lower_bound(Node(pos, 0, 0));
		if(it != s.end() && it -> l == pos) return Query(pos) + tag[it -> v];
		else return Query(pos) + tag[(--it) -> v];
	}
}
using namespace Chtholly_tree;

signed main() 	
{
	n = read(), q = read();
	s.insert(Node(1, n + 5, 1));
	for(int i = 1; i <= q; i++) {
		string s; cin >> s;
		if(s == "Color") {
			int l = read(), r = read(), c = read();
			Cover(l, r, c);
		}
		else if(s == "Add") {
			int c = read(), x = read();
			tag[c] += x;
		}
		else {
			int pos = read();
			printf("%lld\n", getans(pos));
		}
	}
	return (0 - 0);
}

```

---

## 作者：wosile (赞：0)

和人 duel 到这道题，一眼像是 ODT，但是不想写 ODT，所以想了这个和题解区其他题解都不一样的做法。

我们可以把所有操作离线下来，然后调换时间轴和位置轴。也就是我们按位置轴进行操作，按时间轴进行计算和询问。

可以用一个有序集 $s$ 来记录当前位置所有的 `Color` 操作。

对于 `Color` 操作，我们在左端点 $l$ 处把这个操作加入 $s$，在 $r$ 处删掉。这样到每个位置 $i$，$s$ 中记录的操作就把时间轴分成了若干段，每一段是一个颜色。

在时间轴上开一个树状数组，在每一段结尾的位置维护这一段内这个颜色所有 `Add` 操作的和。

对于每种颜色，我们可以记录下这种颜色所有的 `Add` 操作和前缀和，求区间和二分差分即可。

`Query` 时，我们可以先在树状数组上查询在查询位置 $i$ 之前的所有整块的和，再加上 $i$ 所在块代表颜色的一小段区间和。

时间复杂度 $O(n+q\log q)$。

做法比较抽象，请结合代码理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Q;
struct query{
	char op;
	int l,r,c,v,t;
}q[1000005]; // 操作们 
vector<int>vq[1000005],vadd[1000005],vdel[1000005];
// vadd 和 vdel 是 Color 操作的起止。
// vq 是 Query 操作。 
set<int>sc;
typedef long long ll;
vector<int>mod[1000005];
vector<ll>pre[1000005];
// mod[c] 记录对颜色 c 的 Add 操作，pre[c] 记录这些操作 x 的前缀和 
ll ans[1000005],sum[1000005];
ll c[1000005],ac[1000005];
// c 是树状数组，剩下的只是一些辅助数组。 
void add(int x,ll v){
	ac[x]+=v;
	for(;x<=Q;x+=(x&-x))c[x]+=v;
}
ll query(int x){
	ll ans=0;
	for(;x;x-=(x&-x))ans+=c[x];
	return ans;
}
// 树状数组操作 
ll cquery(int c,int x){
	int it=lower_bound(mod[c].begin(),mod[c].end(),x)-mod[c].begin();
	if(it==0)return 0;
	return pre[c][it-1];
}
// 指定颜色前缀和，O(logQ)。 
void sadd(int x){
	int inxt=*sc.lower_bound(x);
	int ipre=*--sc.lower_bound(x);
	ll t1=cquery(q[ipre].c,x)-cquery(q[ipre].c,ipre);
	ll t2=cquery(q[x].c,inxt)-cquery(q[x].c,x);
	add(x,t1);
	add(inxt,t2-ac[inxt]);
	sc.insert(x);
}
void sdel(int x){
	int inxt=*sc.upper_bound(x);
	int ipre=*--sc.lower_bound(x);
	ll t2=cquery(q[ipre].c,inxt)-cquery(q[ipre].c,ipre);
	add(x,-ac[x]);
	add(inxt,t2-ac[inxt]);
	sc.erase(x);
}
// 在时间轴上增删 Color 操作，O(logQ)。 
int main(){
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=Q;i++){
		char tmp[10];
		scanf("%s",tmp);
		q[i].t=i;
		q[i].op=tmp[0];
		if(tmp[0]=='C')scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].c);
		if(tmp[0]=='A')scanf("%d%d",&q[i].c,&q[i].v);
		if(tmp[0]=='Q')scanf("%d",&q[i].l);
		if(tmp[0]=='C')vadd[q[i].l].push_back(i);
		if(tmp[0]=='C')vdel[q[i].r].push_back(i);
		if(tmp[0]=='Q')vq[q[i].l].push_back(i);
		if(tmp[0]=='A')mod[q[i].c].push_back(i);
		if(tmp[0]=='A')sum[q[i].c]+=q[i].v;
		if(tmp[0]=='A')pre[q[i].c].push_back(sum[q[i].c]);
	}
	sc.insert(0);
	sc.insert(Q+1);
	q[0].c=1;
	for(int i=1;i<=n;i++){
		for(int x:vadd[i])sadd(x);
		for(int x:vq[i]){
			int prec=*(--sc.lower_bound(x));
			ans[x]=query(x)+cquery(q[prec].c,x)-cquery(q[prec].c,prec);
		}
		for(int x:vdel[i])sdel(x);
	}
	for(int i=1;i<=Q;i++)if(q[i].op=='Q')printf("%lld\n",ans[i]);
	return 0;
	// quod erat demonstrandum
}
```

---

