# BZOJ4355 Play with sequence

## 题目描述

维护一个长度为 $n$ 的整数序列 $a$，支持三种操作：

- `1 u v c`，对于 $\forall i \in [u,v]$，将 $a_i$ 更改为 $c$；
- `2 u v c`，对于 $\forall i \in [u,v]$，将 $a_i$ 更改为 $\max(a_i+c,0)$；
- `3 u v`，输出 $\sum \limits_{i=u}^v [a_i=0]$ 的值。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n,m\leq 3\times 10^5$，$0\leq a_i\leq 10^9$。

- 对于操作 $1$，保证 $0\leq c\leq 10^9$。
- 对于操作 $2$，保证 $|c| \leq 10^9$。

且对于所有操作，保证 $1\leq u\leq v\leq n$。

## 样例 #1

### 输入

```
5 3
6 4 6 6 4 
2 1 5 -5
1 3 4 4
3 1 5```

### 输出

```
2```

# 题解

## 作者：wangtairan114 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P10638)

## 题意
维护一个数据结构，支持区间赋值，区间加法和区间取最值。

## 思路
原题中，区间修改为 $\max(a_i+c,0)$ 感觉很假，考虑拆成区间加 $c$ 后与 $0$ 取 $\max$。

区间操作显然用线段树维护，维护区间最值需要用到吉司机线段树。吉司机的详细时间复杂度证明见[吉老师的集训队论文](https://yutong.site/wp-content/uploads/2018/09/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)，这里只给出感性理解和实现方法。

在吉司机线段树中，对于区间取 $\max$ 我们维护区间最小值和严格次小值。递归过程中，当修改值位于最小值和次小值之间时，我们对当前区间进行修改，否则继续递归。

第一眼感觉这种做法是 $O(n)$ 的，因为每次暴力修改最劣可能改变 $n$ 个位置。但是我们发现，每一次取 $\max$ 操作都会减少不同最小值的数量，减少的最小值数量与我们暴力修改次数相关。同时，我们发现通过其他操作增加最小值数量需要花费一定的次数。因此，均摊后我们时间复杂度显然小于 $O(nq)$。

具体地，通过吉司机线段树我们可以做到 $O(q\log^2 n)$ 的时间复杂度，具体参考论文~~因为我不会势能分析。~~
## 代码
```
#include <bits/stdc++.h>
//by wangtairan114
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3fll
#define IINF 0x3f3f3f3f
#define DINF 10000000
#define ll long long
#define sc scanf
#define pr printf
#define v1 first
#define v2 second
#define lowbit(x) ((x)&(-x))
const int N=300005;
#define lson k*2,l,mid
#define rson k*2+1,mid+1,r
#define mid ((l+r)>>1)
struct node{
    ll mn;//最小值
    ll smn;//次小值
    ll cntmn;//最小值个数
}p[N<<2];
ll a[N];
ll tgst[N<<2],tgad[N<<2],tgmx[N<<2];
node merge(node x,node y){
    node ans;
    if(x.mn>y.mn)swap(x,y);//比较最小值
    ans.mn=x.mn;
    ans.cntmn=x.cntmn;
    if(x.mn==y.mn){
        ans.cntmn+=y.cntmn;//如果最小值相同将个数累加
        ans.smn=min(x.smn,y.smn);//更新次小值
    }
    else ans.smn=min(x.smn,y.mn);
    return ans;
}
void push_up(int k){p[k]=merge(p[k*2],p[k*2+1]);}
void push_st(int k,int l,int r,ll va){
    p[k].mn=va;
    p[k].smn=INF;
    p[k].cntmn=r-l+1;
    tgst[k]=va;
    tgad[k]=0;
    tgmx[k]=-INF;
}
void push_ad(int k,int l,int r,ll va){
    p[k].mn+=va;
    if(p[k].smn!=INF)p[k].smn+=va;
    tgad[k]+=va;
    if(tgmx[k]!=-INF)tgmx[k]+=va;
}
void push_mx(int k,int l,int r,ll va){
    if(p[k].mn>=va)return;
    p[k].mn=va;
    tgmx[k]=va;
}
void push_down(int k,int l,int r){//下传懒标记
    if(tgst[k]!=-INF){push_st(lson,tgst[k]);push_st(rson,tgst[k]);}//先赋值
    if(tgad[k]){push_ad(lson,tgad[k]);push_ad(rson,tgad[k]);}//下传加法标记
    if(tgmx[k]!=-INF){push_mx(lson,tgmx[k]);push_mx(rson,tgmx[k]);}//下传max标记
    tgst[k]=-INF;
    tgad[k]=0;
    tgmx[k]=-INF;
}
void build(int k,int l,int r){
    tgmx[k]=-INF;
    tgst[k]=-INF;
    tgad[k]=0;
    if(l==r){
        p[k].mn=a[l];
        p[k].smn=INF;//不存在次小值时赋值为inf
        p[k].cntmn=1;
        return;
    }
    build(lson);
    build(rson);
    push_up(k);
}
void modify_st(int k,int l,int r,const int lbor,const int rbor,ll va){//区间赋值
    if(lbor<=l&&r<=rbor){push_st(k,l,r,va);return;}
    push_down(k,l,r);
    if(mid>=lbor)modify_st(lson,lbor,rbor,va);
    if(mid<rbor)modify_st(rson,lbor,rbor,va);
    push_up(k);
}
void modify_ad(int k,int l,int r,const int lbor,const int rbor,ll va){//区间加
    if(lbor<=l&&r<=rbor){push_ad(k,l,r,va);return;}
    push_down(k,l,r);
    if(mid>=lbor)modify_ad(lson,lbor,rbor,va);
    if(mid<rbor)modify_ad(rson,lbor,rbor,va);
    push_up(k);
}
void modify_mx(int k,int l,int r,const int lbor,const int rbor,ll va){//区间取max
    if(p[k].mn>=va)return;//如果当前区间最小值大于修改的值，直接返回
    if(lbor<=l&&r<=rbor&&p[k].smn>va){push_mx(k,l,r,va);return;}//如果区间合法且小于次小值，进行修改
    push_down(k,l,r);//否则继续下传
    if(mid>=lbor)modify_mx(lson,lbor,rbor,va);
    if(mid<rbor)modify_mx(rson,lbor,rbor,va);
    push_up(k);
}
ll query(int k,int l,int r,const int lbor,const int rbor){
    if(lbor<=l&&r<=rbor){
        if(p[k].mn==0)return p[k].cntmn;
        return 0;
    }
    push_down(k,l,r);
    ll ans=0;
    if(mid>=lbor)ans+=query(lson,lbor,rbor);
    if(mid<rbor)ans+=query(rson,lbor,rbor);
    return ans;
}
int n,q;

int main(){
    sc("%d%d",&n,&q);
    for(int i=1; i <= n; i++)
        sc("%lld",&a[i]);
    build(1,1,n);
    while(q--){
        int op;
        sc("%d",&op);
        if(op==1){
            int l,r;
            ll va;
            sc("%d%d%lld",&l,&r,&va);
            modify_st(1,1,n,l,r,va);
        }
        else if(op==2){
            int l,r;
            ll va;
            sc("%d%d%lld",&l,&r,&va);
            modify_ad(1,1,n,l,r,va);
            modify_mx(1,1,n,l,r,0);
        }
        else {
            int l,r;
            sc("%d%d",&l,&r);
            pr("%lld\n",query(1,1,n,l,r));
        }
    }
    return 0;
}
```

代码实现过程中，注意标记下传过程中要先下传加再下传最值，因为求完最值后的加法操作要基于原先的最值标记进行修改。

---

## 作者：zhlzt (赞：5)

### 题解

写这题之前建议把 [P10639 BZOJ4695 最佳女选手](https://www.luogu.com.cn/problem/P10639) 敲完。

关于吉司机线段树的介绍和应用，以及最佳女选手的分析和代码可以参见 [OI-Wiki](https://oi-wiki.org/ds/seg-beats/)。

然后这题可以直接在最佳女选手的板子上改：

- 操作 $1$ 对区间赋 $c$，相当于对区间取一遍最小值和一遍最大值，单次时间复杂度 $O(\log^2n)$。

- 操作 $2$ 对区间加 $c$ 并对 $0$ 取较大值，直接二次调用函数即可，单次时间复杂度 $O(\log^2n)$。

- 操作 $3$ 注意到始终有 $a_i\ge 0$，需要重写一下 query，单次时间复杂度 $O(\log n)$。

这里给出操作 $3$ 的代码（利用了 $a_i$ 始终非负的条件）：

```cpp
typedef int t;
int query(t l,t r,t p,t pl,t pr){
	if(tree[p].mn>0ll) return 0;
	if(l<=pl and pr<=r) return tree[p].mnc;
	int mid=(pl+pr)>>1; int ans=0; 
	pushdown(p,pl,pr);
	if(l<=mid) ans+=query(l,r,p<<1,pl,mid);
	if(r>mid) ans+=query(l,r,p<<1|1,mid+1,pr);
	return ans;
}
```

其中 $mn$ 表示最小值，$mnc$ 表示最小值出现次数。

### 代码实现

代码 4.01KB 只好放云剪贴板里了，[Link](/paste/oi8kv0i7)。

---

## 作者：MrPython (赞：4)

你说的对，但是我会分块。

对于每个区块，我们维护以下信息：
- 原始数组 `dat`；
- 一个指针数组 `sorted`，指向原始数组里的每一个元素，按照指向的值升序排序；
- 当前区块的偏移量 `delta`（进行区间加时使用）；
- 一个指向 `sorted` 中元素的指针 `ptr`，表示第一个大于 `minx` 的元素（相当于存下有多少个元素等于最小值）；
- 当前区块的最小值 `minx`；
- 一个标记 `flag`，表示全区块内的值是否不相等。若不存在标记，则全区块的值均为 `minx`。

对于操作 1：
- 散块直接拍扁重构然后暴力。
- 整块则设置 `flag` 为 false，表示全区块内的元素都相等。此后的维护中，不维护 `sorted`、`delta`、`ptr` 的信息（已知全部元素相等，显然不需要这些信息）。

对于操作 2:
- 散块拍扁重构后暴力。
- 若标记 `flag` 为 false，则直接修改 `minx`。否则，修改 `minx`、`delta`，再二分出新的 `ptr`。注意新的 `ptr` 只可能向右移动，因此二分的区间为 [`ptr`,`sorted.end()`)。

对于操作 3:
- 散块拍扁重构后暴力。
- 对于整块，倘若 minx 不为 0 直接返回 0。若 `flag` 为 false，则整个块内都是 0，返回块的大小，否则返回 `ptr - sorted.begin()`。

以上的“拍扁重构”，指以下过程：
1. 若 `flag` 为 false，则全区块的值都是 `minx`，将 minx 填充至 dat，重置 `delta` 为 0，将 `ptr` 指向 `sorted.begin()` 或 `sorted.end()`（取决于 `minx` 是否为 0）。  
  否则，将 `delta` 内的值全部加回原数组中，然后重置 `delta` 为 0。
2. 进行暴力操作；
3. 重新对 sorted 排序，并重新二分 `ptr` 的位置。

完整代码如下：
```cpp
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
struct Block {
  using It = vector<li>::iterator;
  struct colorful {
    vector<li> dat;
    vector<It> sorted;
    li delta;
    decltype(sorted)::iterator ptr;
  };
  colorful dat;
  bool flag;
  li minx;
  Block(vector<li> const& a)
      : dat(colorful{a, vector<decltype(dat.dat)::iterator>(a.size()), 0, {}}),
        flag(true),
        minx(0) {
    iota(dat.sorted.begin(), dat.sorted.end(), dat.dat.begin());
    dat.ptr = dat.sorted.begin();
    reinit();
  }
  void reinit(void) {
    ranges::sort(dat.sorted, [](It x, It y) { return *x < *y; });
    dat.ptr =
        ranges::upper_bound(dat.sorted, 0, less<>(), [](It x) { return *x; });
    minx = *dat.sorted[0];
  }
  void reset(void) {
    if (!flag) {
      flag = true;
      ranges::fill(dat.dat, minx);
      dat.delta = 0;
      dat.ptr = minx == 0 ? dat.sorted.end() : dat.sorted.begin();
    } else {
      for (auto it : ranges::views::iota(dat.sorted.begin(), dat.ptr))
        **it = minx;
      for (auto it : ranges::views::iota(dat.ptr, dat.sorted.end()))
        **it += dat.delta;
      dat.delta = 0;
    }
  }
  void fill(size_t l, size_t r, int x) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      for (size_t i = l; i < r; ++i) dat.dat[i] = x;
      reinit();
      return;
    }
    flag = false;
    minx = x;
  }
  void add(size_t l, size_t r, int x) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      for (size_t i = l; i < r; ++i) dat.dat[i] = max(dat.dat[i] + x, 0ll);
      reinit();
      return;
    }
    minx = max(minx + x, 0ll);
    if (!flag) return;
    dat.delta += x;
    dat.ptr = ranges::upper_bound(dat.ptr, dat.sorted.end(), 0, less<>(),
                                  [&](It v) { return *v + dat.delta; });
  }
  size_t count(size_t l, size_t r) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      return ranges::count(dat.dat.begin() + l, dat.dat.begin() + r, 0);
    }
    if (minx > 0) return 0;
    if (!flag) return dat.sorted.size();
    return dat.ptr - dat.sorted.begin();
  }
};
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n, m;
  fin >> n >> m;
  size_t len = 450;
  vector<Block> blks;
  for (size_t i = 0; i < n; i += len) {
    size_t j = min(i + len, n);
    vector<li> a(j - i);
    for (li& x : a) fin >> x;
    blks.emplace_back(a);
  }
  while (m--) {
    char op;
    size_t l, r;
    fin >> op >> l >> r;
    --l;
    size_t bl = l / len, br = (r + len - 1) / len;
    if (op == '1') {
      int c;
      fin >> c;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        blks[i].fill(cl, cr, c);
      }
    }
    if (op == '2') {
      int c;
      fin >> c;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        blks[i].add(cl, cr, c);
      }
    }
    if (op == '3') {
      size_t ans = 0;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        ans += blks[i].count(cl, cr);
      }
      fout << ans << '\n';
    }
  }
  return 0;
}
```
这份代码可以取得 63 分的好成绩。还需要优化。

首先，进行散块操作后，观察 `sorted` 数组，可以发现：将被修改过的数和未被修改过的数分成两个数组，则这两个数组都是升序排列的。我们可以直接使用 $O(n)$ 的序列合并操作取代 $O(n \log n)$ 的排序操作。

其次，在区间加操作的二分步骤前检查 `minx`，倘若 `minx > 0`，则说明全部元素都只进行可普通的加法，没有与 0 取 $\max$，则等于 minx 的元素数量不变，无需重新二分 ptr。此优化可以将不少次 $O(\log n)$ 的二分操作优化成 $O(1)$。

使用以上两种优化即可通过全部测试数据。最终代码如下所示。

```cpp
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using It = vector<li>::iterator;
constexpr auto UF = [](It x) { return *x; };
struct Block {
  struct colorful {
    vector<li> dat;
    vector<It> sorted;
    li delta;
    decltype(sorted)::iterator ptr;
  };
  colorful dat;
  bool flag;
  li minx;
  Block(vector<li> const& a)
      : dat(colorful{a, vector<decltype(dat.dat)::iterator>(a.size()), 0, {}}),
        flag(true),
        minx(0) {
    iota(dat.sorted.begin(), dat.sorted.end(), dat.dat.begin());
    dat.ptr = dat.sorted.begin();
    reinit();
  }
  void reinit(void) {
    ranges::sort(dat.sorted, [](It x, It y) { return *x < *y; });
    dat.ptr =
        ranges::upper_bound(dat.sorted, 0, less<>(), [](It x) { return *x; });
    minx = *dat.sorted[0];
  }
  void reset(void) {
    if (!flag) {
      flag = true;
      ranges::fill(dat.dat, minx);
      dat.delta = 0;
      dat.ptr = minx == 0 ? dat.sorted.end() : dat.sorted.begin();
    } else {
      for (auto it : ranges::views::iota(dat.sorted.begin(), dat.ptr))
        **it = minx;
      for (auto it : ranges::views::iota(dat.ptr, dat.sorted.end()))
        **it += dat.delta;
      dat.delta = 0;
    }
  }
  void remerge(size_t l, size_t r) {
    vector<It> a, b;
    for (auto it : dat.sorted)
      (l <= it - dat.dat.begin() && it - dat.dat.begin() < r ? b : a)
          .emplace_back(it);
    ranges::merge(a, b, dat.sorted.begin(), less<>(), UF, UF);
    dat.ptr = ranges::upper_bound(dat.sorted, 0, less<>(), UF);
    minx = *dat.sorted.front();
  }
  void fill(size_t l, size_t r, int x) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      for (size_t i = l; i < r; ++i) dat.dat[i] = x;
      remerge(l, r);
      return;
    }
    flag = false;
    minx = x;
  }
  void add(size_t l, size_t r, int x) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      for (size_t i = l; i < r; ++i) dat.dat[i] = max(dat.dat[i] + x, 0ll);
      remerge(l, r);
      return;
    }
    minx = max(minx + x, 0ll);
    if (!flag) return;
    dat.delta += x;
    if (minx > 0) return;
    dat.ptr = ranges::upper_bound(dat.ptr, dat.sorted.end(), 0, less<>(),
                                  [&](It v) { return *v + dat.delta; });
  }
  size_t count(size_t l, size_t r) {
    if (l != 0 || r != dat.dat.size()) {
      reset();
      return ranges::count(dat.dat.begin() + l, dat.dat.begin() + r, 0);
    }
    if (minx > 0) return 0;
    if (!flag) return dat.sorted.size();
    return dat.ptr - dat.sorted.begin();
  }
};
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n, m;
  fin >> n >> m;
  size_t len = 450;
  vector<Block> blks;
  for (size_t i = 0; i < n; i += len) {
    size_t j = min(i + len, n);
    vector<li> a(j - i);
    for (li& x : a) fin >> x;
    blks.emplace_back(a);
  }
  while (m--) {
    char op;
    size_t l, r;
    fin >> op >> l >> r;
    --l;
    size_t bl = l / len, br = (r + len - 1) / len;
    if (op == '1') {
      int c;
      fin >> c;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        blks[i].fill(cl, cr, c);
      }
    }
    if (op == '2') {
      int c;
      fin >> c;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        blks[i].add(cl, cr, c);
      }
    }
    if (op == '3') {
      size_t ans = 0;
      for (size_t i = bl; i < br; ++i) {
        size_t cl = max(l, i * len) - i * len,
               cr = min(r, (i + 1) * len) - i * len;
        ans += blks[i].count(cl, cr);
      }
      fout << ans << '\n';
    }
  }
  return 0;
}
```

---

## 作者：light_searcher (赞：3)

大家应该都会 segment tree beats 了吧，支持的基本操作是取 $\min$ 或 取 $\max$，区间加。

操作 $1$ 由于 $c$ 为非负数，所以可以先对区间内的数和 $-1$ 取 $\min$，再和 $c$ 取 $\max$。

操作 $2$ 可以看出来就是先区间加，然后再和 $0$ 取 $\min$。

操作 $3$ 由于所有数都是非负数，所以如果区间内的最小值为 $0$，直接加上最小值的数量即可。

然后做完了，操作 $1$ 和 $2$ 均摊 $\mathcal O(m \log^2 n)$，操作 $3$ 每次严格 $\mathcal O(\log n)$。

Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=1e18;
int n,q,a[N],mx[4*N],mx2[4*N],mn[4*N],mn2[4*N],sum[4*N],cmx[4*N],cmn[4*N],tmx[4*N],tmn[4*N],add[4*N];
void push_up(int x){
	sum[x]=sum[2*x]+sum[2*x+1];
	if(mx[2*x]==mx[2*x+1]){
		mx[x]=mx[2*x]; 
		cmx[x]=cmx[2*x]+cmx[2*x+1];
		mx2[x]=max(mx2[2*x],mx2[2*x+1]);
	} 
	else if(mx[2*x]>mx[2*x+1]){
		mx[x]=mx[2*x];
		cmx[x]=cmx[2*x];
		mx2[x]=max(mx2[2*x],mx[2*x+1]);
	}
	else{
		mx[x]=mx[2*x+1];
		cmx[x]=cmx[2*x+1];
		mx2[x]=max(mx[2*x],mx2[2*x+1]);
	}
	if(mn[2*x]==mn[2*x+1]){
		mn[x]=mn[2*x]; 
		cmn[x]=cmn[2*x]+cmn[2*x+1];
		mn2[x]=min(mn2[2*x],mn2[2*x+1]);
	} 
	else if(mn[2*x]<mn[2*x+1]){
		mn[x]=mn[2*x];
		cmn[x]=cmn[2*x];
		mn2[x]=min(mn2[2*x],mn[2*x+1]);
	}
	else{
		mn[x]=mn[2*x+1];
		cmn[x]=cmn[2*x+1];
		mn2[x]=min(mn[2*x],mn2[2*x+1]);
	}	
}
void build(int x,int l,int r){
	tmx[x]=-inf;
	tmn[x]=inf;
	if(l==r){
		sum[x]=mx[x]=mn[x]=a[l];
		mx2[x]=-inf;
		mn2[x]=inf;
		cmx[x]=cmn[x]=1;
		return; 
	}
	int mid=(l+r)/2;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	push_up(x);
}
void push_add(int x,int l,int r,int v){
	sum[x]+=(r-l+1)*v;
	mx[x]+=v;
	mn[x]+=v;
	if(mx2[x]!=-inf) mx2[x]+=v;
	if(mn2[x]!=inf) mn2[x]+=v;
	if(tmx[x]!=-inf) tmx[x]+=v;
	if(tmn[x]!=inf) tmn[x]+=v;
	add[x]+=v;
}
void push_mx(int x,int v){
	if(mn[x]>=v) return;
	sum[x]+=(v-mn[x])*cmn[x];
	if(mx2[x]==mn[x]) mx2[x]=v;
	if(mx[x]==mn[x]) mx[x]=v;
	if(tmn[x]<v) tmn[x]=v;
	mn[x]=v;
	tmx[x]=v;
}
void push_mn(int x,int v){
	if(mx[x]<=v) return;
	sum[x]-=(mx[x]-v)*cmx[x];
	if(mn2[x]==mx[x]) mn2[x]=v;
	if(mn[x]==mx[x]) mn[x]=v;
	if(tmx[x]>v) tmx[x]=v;
	mx[x]=v;
	tmn[x]=v;
}
void push_down(int x,int l,int r){
	if(add[x]){
		int mid=(l+r)/2;
		push_add(2*x,l,mid,add[x]);
		push_add(2*x+1,mid+1,r,add[x]);
		add[x]=0;
	}
	if(tmn[x]!=inf){
		push_mn(2*x,tmn[x]);
		push_mn(2*x+1,tmn[x]);
		tmn[x]=inf;
	}
	if(tmx[x]!=-inf){
		push_mx(2*x,tmx[x]);
		push_mx(2*x+1,tmx[x]);
		tmx[x]=-inf;
	}
}
void modify(int x,int l,int r,int L,int R,int v){
	if(l>=L&&r<=R) return push_add(x,l,r,v);
	push_down(x,l,r);
	int mid=(l+r)/2;
	if(L<=mid) modify(2*x,l,mid,L,R,v);
	if(R>mid) modify(2*x+1,mid+1,r,L,R,v);
	push_up(x);
}
void chkmx(int x,int l,int r,int L,int R,int v){
	if(l>=L&&r<=R&&mn2[x]>v) return push_mx(x,v);
	push_down(x,l,r);
	int mid=(l+r)/2;
	if(L<=mid) chkmx(2*x,l,mid,L,R,v);
	if(R>mid) chkmx(2*x+1,mid+1,r,L,R,v);
	push_up(x);
}
void chkmn(int x,int l,int r,int L,int R,int v){
	if(l>=L&&r<=R&&mx2[x]<v) return push_mn(x,v);
	push_down(x,l,r);
	int mid=(l+r)/2;
	if(L<=mid) chkmn(2*x,l,mid,L,R,v);
	if(R>mid) chkmn(2*x+1,mid+1,r,L,R,v);
	push_up(x);
}
int query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R) return mn[x]?0:cmn[x];
	push_down(x,l,r);
	int mid=(l+r)/2,ret=0;
	if(L<=mid) ret+=query(2*x,l,mid,L,R);
	if(R>mid) ret+=query(2*x+1,mid+1,r,L,R);
	return ret;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	for(int opt,l,r,v;q;q--){
		scanf("%lld%lld%lld",&opt,&l,&r);
		if(opt==1){
			scanf("%lld",&v);
			chkmn(1,1,n,l,r,-1);
			chkmx(1,1,n,l,r,v);
		}
		else if(opt==2){
			scanf("%lld",&v);
			modify(1,1,n,l,r,v);
			chkmx(1,1,n,l,r,0);
		}
		else printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}

---

## 作者：Purslane (赞：3)

# Solution

相信大家都会 $\rm Segment \ tree \ beats$ 了。

如何把代码写的简洁一点（尽管常数略大）？

事实上，我们只有两种修改操作：区间加，区间取 $\max$。

对于区间覆盖操作（操作 $2$），等价于区间加 $- \infty$，区间对 $c$ 取 $\rm max$；

对于操作 $3$，等价于区间加 $c$，区间对 $0$ 取 $\max$。

值得注意的是，注意你的 $\rm INF$ 的实现。比如，如果区间没有次小值，你又偏要设为 $\rm INF$，那么在区间减 $\rm INF$ 不能修改他。

代码只有 $96$ 行，$\rm 2.9 \ Kb$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,q,a[MAXN];
struct INFO {
	int len,sum;
	int mn,smn,mncnt;
}t[MAXN<<2];
struct TAG {
	int midad,mnad;
}tag[MAXN<<2];
INFO operator +(INFO A,TAG B) {
	A.sum+=1ll*A.mncnt*B.mnad+1ll*(A.len-A.mncnt)*B.midad;
	if(A.mncnt!=A.len) A.smn+=B.midad;
	A.mn+=B.mnad;
	return A;
}
TAG operator +(TAG A,TAG B) {
	return {A.midad+B.midad,A.mnad+B.mnad};
}
int calc_smn(int a,int b,int c,int d) {
	int mn=min(min(a,b),min(c,d)),ans=INF;
	if(a!=mn) ans=min(ans,a);
	if(b!=mn) ans=min(ans,b);
	if(c!=mn) ans=min(ans,c);
	if(d!=mn) ans=min(ans,d);
	return ans;	
}
INFO operator +(INFO A,INFO B) {
	return {A.len+B.len,A.sum+B.sum,min(A.mn,B.mn),calc_smn(A.mn,B.mn,A.smn,B.smn),(A.mn<=B.mn?A.mncnt:0)+(A.mn>=B.mn?B.mncnt:0)};	
}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {
	int mn=min(t[lson].mn,t[rson].mn);
	TAG lad,rad;
	if(t[lson].mn==mn) lad=tag[k];
	else lad={tag[k].midad,tag[k].midad};
	t[lson]=t[lson]+lad,tag[lson]=tag[lson]+lad;
	if(t[rson].mn==mn) rad=tag[k];
	else rad={tag[k].midad,tag[k].midad};
	t[rson]=t[rson]+rad,tag[rson]=tag[rson]+rad;
	return tag[k]={0,0},void();
}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return t[k]=t[k]+TAG{v,v},tag[k]=tag[k]+TAG{v,v},void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	return t[k]=t[lson]+t[rson],void();	
}
void get_max(int k,int l,int r,int x,int y,int v) {
	if(t[k].mn>=v) return ;
	if(x<=l&&r<=y) {
		int val=v-t[k].mn;
		if(t[k].mncnt==r-l+1||t[k].smn>v) return t[k]=t[k]+TAG{0,val},tag[k]=tag[k]+TAG{0,val},void();
		push_down(k,l,r);
		return get_max(lson,l,mid,x,y,v),get_max(rson,mid+1,r,x,y,v),t[k]=t[lson]+t[rson],void();
	}
	push_down(k,l,r);
	if(x<=mid) get_max(lson,l,mid,x,y,v);
	if(y>mid) get_max(rson,mid+1,r,x,y,v);
	return t[k]=t[lson]+t[rson],void();
}
INFO query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return query(lson,l,mid,x,y)+query(rson,mid+1,r,x,y);	
}
void build(int k,int l,int r) {
	if(l==r) return t[k]={1,a[l],a[l],INF,1},void();
	return build(lson,l,mid),build(rson,mid+1,r),t[k]=t[lson]+t[rson],void();
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	build(1,1,n);
	ffor(i,1,q) {
		int op,l,r,c;
		cin>>op>>l>>r;
		if(op==1) cin>>c,update(1,1,n,l,r,-INF),get_max(1,1,n,l,r,c);	
		else if(op==2) cin>>c,update(1,1,n,l,r,c),get_max(1,1,n,l,r,0);
		else {
			auto info=query(1,1,n,l,r);
			if(info.mn==0) cout<<info.mncnt<<'\n';
			else cout<<0<<'\n';	
		}
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：2)

下面介绍的是吉司机线段树（Segment Tree Beats）。

吉司机线段树是一种支持区间加和区间 chkmax / chkmin 的数据结构，他本质是一棵线段树维护的几个信息，以 chkmax 为例，重要的有 $min,sec,sum$。

我们现在有一个区间 $[l,r]$ 要进行 chkmax $v$ 操作，那么具体流程如下：

- 当 $min\leq v$，那么显然不会产生任何操作，直接返回。
- 当 $min<v\leq sec$，我们把所有的 $min$ 改为 $v$，并打上一个修改的 tag，下次操作到这记得 pushdown。
- 当 $sec>v$，我们递归下去，直到出现上述两种情况之一。

这么做复杂度均摊是 $O(n \log^2 n)$ 的，我们来分析一下。

重点是 $min<v\leq sec$ 的操作，由于数的种类算上操作总数一共只有 $O(n)$ 种，那么我们把 $min$ 改成 $v$ 相当于删掉一种，那么这个操作只会执行 $O(n)$ 次。

但是由于我们有区间加操作，会使得某些被消除掉的数字又变得突出，不过由于线段树上分为 $\log n$ 个线段处理，所以一次只会有 $\log n$ 个节点，故数的总类别数其实是 $O(n \log n)$ 的。结合每次递归下去 $\log n$，总复杂度 $O(n \log ^2 n)$。

```cpp
const int N = 3e5 + 19, inf = 1e18;
int n, q, a[N];
struct SegTree {
	int t[N << 2], mn[N << 2], sec[N << 2], tag[N << 2], lzy[N << 2];
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	#define mid ((l + r) >> 1)
	void pushup(int k) {
		if (mn[ls] == mn[rs]) {
			mn[k] = mn[ls]; sec[k] = min(sec[ls], sec[rs]); t[k] = t[ls] + t[rs];
		} else if (mn[ls] < mn[rs]) {
			mn[k] = mn[ls]; sec[k] = min(sec[ls], mn[rs]); t[k] = t[ls];
		} else {
			mn[k] = mn[rs]; sec[k] = min(sec[rs], mn[ls]); t[k] = t[rs];
		}
	}
	void build(int k, int l, int r) {
		lzy[k] = -1;
		if (l == r) return t[k] = 1, mn[k] = a[l], sec[k] = inf, void();
		build(ls, l, mid); build(rs, mid+1, r);
		pushup(k);
	}
	void mktag(int k, int w) {
		if (mn[k] > -inf) mn[k] += w;
		if (sec[k] < inf && sec[k] > -inf) sec[k] += w;
		if (tag[k] > -inf) tag[k] += w;
		if (lzy[k] > -inf) lzy[k] += w;
	}
	void pushdown(int k) {
		if (tag[k]) {
			mktag(ls, tag[k]); mktag(rs, tag[k]);
			tag[k] = 0;
		}
		if (~lzy[k]) {
			if (mn[ls] < lzy[k]) mn[ls] = lzy[ls] = lzy[k];
			if (mn[rs] < lzy[k]) mn[rs] = lzy[rs] = lzy[k];
			lzy[k] = -1;
		}
	}
	void add(int k, int l, int r, int L, int R, int w) {
		if (L <= l && r <= R) return mktag(k, w), void();
		pushdown(k);
		if (L <= mid) add(ls, l, mid, L, R, w);
		if (R > mid) add(rs, mid+1, r, L, R, w);
		pushup(k); 
	}
	void chkmax(int k, int l, int r, int L, int R, int w) {
		if (mn[k] >= w) return ;
		if (L <= l && r <= R) {
			if (sec[k] > w) {
				if (l < r) pushdown(k);
				mn[k] = lzy[k] = w;
				return ;
			}
		}
		pushdown(k);
		if (L <= mid) chkmax(ls, l, mid, L, R, w);
		if (R > mid) chkmax(rs, mid+1, r, L, R, w);
		pushup(k);
	}
	int query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mn[k] ? 0 : t[k];
		pushdown(k);
		int ans = 0;
		if (L <= mid) ans += query(ls, l, mid, L, R);
		if (R > mid) ans += query(rs, mid+1, r, L, R);
		return ans;
	}
} seg;
signed main() {
	read(n, q); for (int i=1;i<=n;++i) read(a[i]);
	seg.build(1, 1, n);
	while (q--) {
		int op, x, y, c;
		read(op, x, y);
		if (op == 3) write(seg.query(1, 1, n, x, y));
		else {
			read(c);
			if (op == 1) seg.add(1, 1, n, x, y, -inf), seg.chkmax(1, 1, n, x, y, c);
			else seg.add(1, 1, n, x, y, c), seg.chkmax(1, 1, n, x, y, 0);
		}
	}
	return 0;
}
```

---

## 作者：Starrykiller (赞：2)

> 选自 数据结构做题记录 **LIX**。


第二个操作可以看成是区间加与区间 chmax 的复合。于是只需要维护区间覆盖、区间加、区间 chmax 这三个操作就好了。

对于区间 chmax，我们用 segbeats 的套路，具体地说：

维护区间次小值 $\mathrm{sec}$ 和区间最小值 $\mathrm{mn}$，设 chmax 的值是 $v$。当当前区间完全包含询问区间时：
- $v\le \mathrm{mn}$：无事可做，直接返回；
- $\mathrm{mn}\lt v\lt \mathrm{sec}$：直接修改 $\mathrm{mn}$ 即可；
- $\mathrm{sec} \le v$：递归处理。

吉如一老师证明了这么做的时间复杂度是 $\Theta(m\log^2 n)$ 的。

区间加和区间 chmax 是平凡的。只需要再维护一个区间最小值的数量 $\mathrm{cnt}$，查询的时候就是查询 $\sum \mathrm{cnt}\cdot [\mathrm{mn}=0]$。

需要注意 tag 下传的顺序：先下传区间覆盖，再下传区间加，最后区间 chmax。区间覆盖之后要把区间加的 tag 清除掉。

似乎还有一种做法就是设 tag $(a,b)$ 为 $x\gets \max(x+a,b)$，然后注意到这个东西是满足结合律的。

[代码](https://www.luogu.com.cn/paste/65vpxyhs)。

---

## 作者：_zuoqingyuan (赞：1)

# 思路分析

将操作二 $a_i\gets \max(a_i+c,0)$ 拆开成 $a_i\gets a_i+c$ 和 $a_i\gets \max(a_i,0)$，则题目被转化为维护支持区间加法，区间赋值，区间取 $\max$，查询区间 $0$ 的个数的数据结构。

看到区间 $\max$ 和区间加不难想到 Segment Tree Beats。问题在于我们如何同时维护加法，赋值，取 $\max$ 三个标记。

仔细思考后容易发现，若我们打上赋值标记，可以直接将另外两个标记清空，而加法和取 $\max$ 也可以直接合并到赋值标记上，所以标记的处理我们先对赋值标记进行讨论。若不存在赋值标记，则用维护数域的方法，先下传加法，再下传 $\max$。

- 打赋值标记：

直接将其他标记清空，修改最小值为所赋的值，次小值为正无穷，修改最小值个数为区间长度，同时打上赋值标记。

- 打加法标记：

若存在赋值标记，则直接将赋值标记加上加法标记的值，同时修改最小值。

若不存在，则打上加法标记，同时修改最小值，次小值和取 $\max$ 标记，注意判断后面两个量不存在的情况。

- 打 $\max$ 标记：

若存在赋值标记，则直接令赋值标记取 $\max$，同时修改最小值。

若不存在，则打上 $\max$ 标记，同时修改最小值。

-------------------------------

注意到序列中的数无论何时都非负，所以查询时只要满足当前区间最小值为 $0$，直接返回同时维护的区间最小值个数即可。

其余部分就是 Segment Tree Beats 的基础操作了，时间复杂度为 $O(n\log^2 n)$，运行效率较快，可以通过，注意写的过程中一些初值的赋值。


# Code


```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
inline void read(int &a){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-48,ch=getchar();
	a=x*f;return;
}
const int N=3e5+10;
const int inf=1e15+7;
int a[N],n,m;
struct node{
	int ad[N<<2],tc[N<<2],len[N<<2],tmx[N<<2];
	int mn[N<<2],mns[N<<2],cn[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	void push_up(int p){
		if(mn[ls]==mn[rs]){
			mn[p]=mn[ls],cn[p]=cn[ls]+cn[rs];
			mns[p]=min(mns[ls],mns[rs]); 
		}else if(mn[ls]<mn[rs]){
			mn[p]=mn[ls],cn[p]=cn[ls];
			mns[p]=min(mns[ls],mn[rs]);
		}else if(mn[ls]>mn[rs]){
			mn[p]=mn[rs],cn[p]=cn[rs];
			mns[p]=min(mn[ls],mns[rs]);
		}
		return;
	}
	void build(int p,int l,int r){
		tc[p]=tmx[p]=-inf,len[p]=r-l+1;
		if(l==r){
			mn[p]=a[l],mns[p]=inf,cn[p]=1;
			return;
		}else{
			int mid=(l+r)>>1;
			build(ls,l,mid),build(rs,mid+1,r);
			push_up(p);
		}
	}
	void pushadd(int p,int v){
		if(tc[p]!=-inf)tc[p]+=v,mn[p]+=v;
		else{
			ad[p]+=v,mn[p]+=v;
			if(tmx[p]!=-inf)tmx[p]+=v;
			if(mns[p]!=inf)mns[p]+=v;
		}
	}
	void pushcover(int p,int v){
		ad[p]=0;tc[p]=mn[p]=v;tmx[p]=-inf;cn[p]=len[p];mns[p]=inf;
	}
	void pushmax(int p,int v){
		if(tc[p]!=-inf){
			tc[p]=max(tc[p],v);
			mn[p]=max(mn[p],v);
		}else{
			if(mn[p]>=v)return;
			mn[p]=v,tmx[p]=v;
		}
	}
	void push_down(int p){
		if(tc[p]!=-inf){
			pushcover(ls,tc[p]);
			pushcover(rs,tc[p]);
		}else{
			if(ad[p]){
				pushadd(ls,ad[p]);
				pushadd(rs,ad[p]);
			}
			if(tmx[p]!=-inf){
				pushmax(ls,tmx[p]);
				pushmax(rs,tmx[p]);
			}
		}
		tc[p]=tmx[p]=-inf,ad[p]=0;
		return;
	}
	void cover(int p,int l,int r,int L,int R,int c){
		if(L<=l&&r<=R){
			pushcover(p,c);
			return;
		}else{
			int mid=(l+r)>>1;push_down(p);
			if(L<=mid)cover(ls,l,mid,L,R,c);
			if(R>mid)cover(rs,mid+1,r,L,R,c);
			push_up(p);return;
		}
	}
	void add(int p,int l,int r,int L,int R,int v){
		if(L<=l&&r<=R){
			pushadd(p,v);
			return;
		}else{
			int mid=(l+r)>>1;push_down(p);
			if(L<=mid)add(ls,l,mid,L,R,v);
			if(R>mid)add(rs,mid+1,r,L,R,v);
			push_up(p);return;
		}
	}
	void updmax(int p,int l,int r,int L,int R,int v){
		if(mn[p]>=v)return;
		if(L<=l&&r<=R&&v<mns[p]){
			pushmax(p,v);
			return;
		}else{
			int mid=(l+r)>>1;push_down(p);
			if(L<=mid)updmax(ls,l,mid,L,R,v);
			if(R>mid)updmax(rs,mid+1,r,L,R,v);
			push_up(p);return;
		}
	}
	int ask(int p,int l,int r,int L,int R){
		if(mn[p]>0)return 0;
		if(L<=l&&r<=R)return cn[p];
		int mid=(l+r)>>1,cnt=0;push_down(p);
		if(L<=mid)cnt+=ask(ls,l,mid,L,R);
		if(R>mid)cnt+=ask(rs,mid+1,r,L,R);
		return cnt;
	}
	
}tr;
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	tr.build(1,1,n);
	while(m--){
		int o,l,r,x;
		read(o),read(l),read(r);
		if(o==1)read(x),tr.cover(1,1,n,l,r,x);
		if(o==2)read(x),tr.add(1,1,n,l,r,x),tr.updmax(1,1,n,l,r,0);
		if(o==3)printf("%lld\n",tr.ask(1,1,n,l,r));  
	}
	return 0;
} 
```

如有错误，请指出。

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10638)

# 前置知识

[区间最值操作 & 区间历史最值](https://oi-wiki.org/ds/seg-beats/)

# 解法

将操作 $1$ 也化成操作 $2$ 的形式，有 $a_{i} \gets \max(a_{i}-\infty,c)$。

现在就转化成了区间加和区间最值，考虑使用吉司机线段树，由势能分析可知时间复杂度为 $O(m \log^{2} n)$。标记下传时注意遵循一定的顺序，这里的代码中规定加法标记优先级高于覆盖标记。

因保证操作过程中 $a_{i} \ge 0$，所以只需要记录最小值出现次数即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll inf=0x3f3f3f3f3f;
ll a[300010];
struct SMT
{
	struct SegmentTree
	{
		ll mn,se,cnt,cov,add;
	}tree[1200010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void pushup(ll rt)
	{
		tree[rt].mn=min(tree[lson(rt)].mn,tree[rson(rt)].mn);
		if(tree[lson(rt)].mn<tree[rson(rt)].mn)
		{
			tree[rt].se=min(tree[lson(rt)].se,tree[rson(rt)].mn);
			tree[rt].cnt=tree[lson(rt)].cnt;
		}
		if(tree[lson(rt)].mn==tree[rson(rt)].mn)
		{
			tree[rt].se=min(tree[lson(rt)].se,tree[rson(rt)].se);
			tree[rt].cnt=tree[lson(rt)].cnt+tree[rson(rt)].cnt;
		}
		if(tree[lson(rt)].mn>tree[rson(rt)].mn)
		{
			tree[rt].se=min(tree[lson(rt)].mn,tree[rson(rt)].se);
			tree[rt].cnt=tree[rson(rt)].cnt;
		}
	}
	void build(ll rt,ll l,ll r)
	{
		tree[rt].cov=-1;
		if(l==r)
		{
			tree[rt].mn=a[l];  tree[rt].se=inf;
			tree[rt].cnt=1;
			return;
		}
		ll mid=(l+r)/2;
		build(lson(rt),l,mid);  build(rson(rt),mid+1,r);
		pushup(rt);
	}
	void pushlazy(ll rt,ll add,ll cov)
	{
		tree[rt].mn+=add;
		if(tree[rt].se!=inf)  tree[rt].se+=add;
		tree[rt].add+=add;
		if(tree[rt].cov!=-1)  tree[rt].cov+=add;
		if(cov==-1||tree[rt].mn>=cov)  return;
		tree[rt].mn=tree[rt].cov=cov;
	}
	void pushdown(ll rt)
	{	
		pushlazy(lson(rt),tree[rt].add,tree[rt].cov);
		pushlazy(rson(rt),tree[rt].add,tree[rt].cov);
		tree[rt].add=0;  tree[rt].cov=-1;
	}
	void update1(ll rt,ll l,ll r,ll x,ll y,ll val)
	{
		if(x<=l&&r<=y)
		{
			pushlazy(rt,val,-1);
			return;
		}
		pushdown(rt);
		ll mid=(l+r)/2;
		if(x<=mid)  update1(lson(rt),l,mid,x,y,val);
		if(y>mid)  update1(rson(rt),mid+1,r,x,y,val);
		pushup(rt);
	}
	void update2(ll rt,ll l,ll r,ll x,ll y,ll val)
	{
		if(tree[rt].mn>=val)  return;
		if(x<=l&&r<=y&&tree[rt].se>val)
		{
			pushlazy(rt,0,val);
			return;
		}
		pushdown(rt);
		ll mid=(l+r)/2;
		if(x<=mid)  update2(lson(rt),l,mid,x,y,val);
		if(y>mid)  update2(rson(rt),mid+1,r,x,y,val);
		pushup(rt);
	}
	ll query(ll rt,ll l,ll r,ll x,ll y)
	{
		if(x<=l&&r<=y)  return (tree[rt].mn==0)*tree[rt].cnt;
		pushdown(rt);
		ll mid=(l+r)/2,ans=0;
		if(x<=mid)  ans+=query(lson(rt),l,mid,x,y);
		if(y>mid)  ans+=query(rson(rt),mid+1,r,x,y);
		return ans;
	}
}T;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif	
	ll n,m,pd,l,r,x,i;
	cin>>n>>m;
	for(i=1;i<=n;i++)  cin>>a[i];
	T.build(1,1,n);
	for(i=1;i<=m;i++)
	{
		cin>>pd>>l>>r;
		if(pd==1)
		{
			cin>>x;
			T.update1(1,1,n,l,r,-inf);
			T.update2(1,1,n,l,r,x);
		}
		if(pd==2)
		{	
			cin>>x;
			T.update1(1,1,n,l,r,x);
			T.update2(1,1,n,l,r,0);
		}
		if(pd==3)  cout<<T.query(1,1,n,l,r)<<endl;
	}
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

$2$ 操作相当于先区间加 $c$，在区间和 $0$ 取 $\max$，直接上吉司机，$1$ 操作其实也可以转化成区间加 $-inf$，在和 $c$ 取 $\max$，因为 $a_i$ 非负，$3$ 操作只需维护最小值和最小值出现次数即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int inf=1e18;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[300010];
struct Info{int mi,cnt;Info(){mi=cnt=0;}Info operator+(Info x){Info res;res.mi=min(mi,x.mi);res.cnt=cnt*(res.mi==mi)+x.cnt*(res.mi==x.mi);return res;}};
struct seg{int l,r,_mi,add,tag;Info x;}t[1200010];
#define lson now<<1
#define rson now<<1|1
void pushup(int now){t[now].x=t[lson].x+t[rson].x;if(t[lson].x.mi<t[rson].x.mi) t[now]._mi=min(t[lson]._mi,t[rson].x.mi);else if(t[lson].x.mi==t[rson].x.mi) t[now]._mi=min(t[lson]._mi,t[rson]._mi);else t[now]._mi=min(t[lson].x.mi,t[rson]._mi);}
void build(int now,int l,int r){
	t[now]={l,r};t[now].tag=-inf;if(l==r){t[now].x.mi=a[l];t[now].x.cnt=1;t[now]._mi=inf;return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);pushup(now);
}
void putadd(int now,int v){t[now].x.mi+=v;t[now].add+=v;if(t[now]._mi^inf) t[now]._mi+=v;if(t[now].tag^-inf)t[now].tag+=v;}
void puttag(int now,int v){if(t[now].x.mi>=v) return ;t[now].x.mi=t[now].tag=v;}
void pushdown(int now){
	if(t[now].add){putadd(lson,t[now].add);putadd(rson,t[now].add);t[now].add=0;}
	if(t[now].tag^-inf){puttag(lson,t[now].tag);puttag(rson,t[now].tag);t[now].tag=-inf;}
}
void modify(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){putadd(now,v);return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) modify(lson,l,r,v);if(mid<r) modify(rson,l,r,v);pushup(now);
}
void chkmax(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){if(t[now].x.mi>=v) return ;if(t[now]._mi>v){puttag(now,v);return ;}}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) chkmax(lson,l,r,v);if(mid<r) chkmax(rson,l,r,v);pushup(now);
}
Info query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].x;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(r<=mid) return query(lson,l,r);if(mid<l) return query(rson,l,r);return query(lson,l,r)+query(rson,l,r);
}
signed main(){
	n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();build(1,1,n);
	while(m--){int opt=read(),l=read(),r=read();if(!(opt^1)){int v=read();modify(1,l,r,-1e14);chkmax(1,l,r,v);}else if(!(opt^2)){int v=read();modify(1,l,r,v);chkmax(1,l,r,0);}else{auto res=query(1,l,r);cout<<(res.mi==0)*res.cnt<<'\n';}}
	return 0;
}
```

---

## 作者：xuanfeng101 (赞：0)

## 前言
吉司机线段树简单应用。
## 题解
首先，我们发现操作 $2$ 的取 $\max$ 操作是吉司机线段树的经典操作，但是这里套了一层加法，所以可以转换为**先后**两个操作，即为将 $i \in [l, r], a_i \leftarrow a_i + c$ 再 $a_i \leftarrow \max(a_i, 0)$，这样就成功把变为我们熟悉的模式，然后这题就变为一道考察**懒标记更新逻辑**的题目了。

  我们发现，我们需要维护区间加，区间赋值，区间取最大值，所以就需要有三个懒标记 $add, cover, mx$。

对于 $add$ 和 $cover$ 之间的懒标记逻辑就很经典了，也就是对于一个区间两个标记只会**同时存在一个**，当 $cover$ 标记存在时，遇到 $add$ 操作，直接加到 $cover$ 上即可；当 $add$ 存在时，遇到 $cover$ 操作，直接清空即可。

同理，多一个 $mx$ 标记时，我们可以在 $add$ 非空时直接加上 $c$，并且在 $cover$ 非空时直接**赋值** $cover$ 即可。

然后就是比较模板化的吉司机线段树，每次维护最小值 $mn$，次小值 $se$，对于取最大值操作，若 $mn \ge v$ 则直接返回，若 $se < v$ 则进行操作并返回，否则 $se \ge v$，当前区间信息无法维护，需要继续递归。

这样的做法看似暴力更新，而吉老师用势能分析法证明其复杂度上界为 $O(n\log^2n)$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, INF = 2e18;
int n, m, a[N];
struct Node
{
    int l, r, mn, se, cnt, add, tag, cover;
}tr[N * 4];

void pushup(Node &rt, Node &l, Node &r)
{
    if (l.mn < r.mn)
    {
        rt.mn = l.mn;
        rt.cnt = l.cnt;
        rt.se = min(l.se, r.mn);
    }
    else if (r.mn < l.mn)
    {
        rt.mn = r.mn;
        rt.cnt = r.cnt;
        rt.se = min(r.se, l.mn);
    }
    else 
    {
        rt.mn = r.mn;
        rt.cnt = r.cnt + l.cnt;
        rt.se = min(l.se, r.se);
    }
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void pushcover(Node &rt, int v)
{
    rt.add = 0;
    rt.mn = rt.cover = v;
    rt.cnt = rt.r - rt.l + 1;
    rt.se = INF, rt.tag = -INF;
}

void pushmx(Node &rt, int v)
{
    if (rt.mn >= v) return;
    if (rt.cover != INF) rt.cover = v;
    else rt.tag = v;
    rt.mn = v;
}

void pushadd(Node &rt, int v)
{
    if (rt.cover != INF) rt.cover += v;
    else 
    {
        rt.add += v;  
        if (rt.tag != -INF) rt.tag += v;
    }
    if (rt.se != INF) rt.se += v;
    rt.mn += v;
}

void pushdown(int u)
{
    auto &rt = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
    if (rt.add)
    {
        pushadd(l, rt.add), pushadd(r, rt.add);
        rt.add = 0;
    }
    if (rt.cover != INF)
    {
        pushcover(l, rt.cover), pushcover(r, rt.cover);
        rt.cover = INF;
    }
    if (rt.tag != -INF)
    {
        pushmx(l, rt.tag), pushmx(r, rt.tag);
        rt.tag = -INF;
    }
}

void build(int u, int l, int r)
{
    tr[u] = {l, r, INF, INF, 0, 0, -INF, INF};
    if (l == r)
    {
        tr[u].cnt = 1;
        tr[u].mn = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update_add(int u, int l, int r, int v)
{
    if (tr[u].l >= l && tr[u].r <= r) 
    {
        pushadd(tr[u], v);
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) update_add(u << 1, l, r, v);
    if (r > mid) update_add(u << 1 | 1, l, r, v);
    pushup(u);
}

void update_cover(int u, int l, int r, int v)
{
    if (tr[u].l >= l && tr[u].r <= r)
    {
        pushcover(tr[u], v);
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) update_cover(u << 1, l, r, v);
    if (r > mid) update_cover(u << 1 | 1, l, r, v);
    pushup(u);
}

void update_mx(int u, int l, int r)
{
    if (tr[u].mn >= 0) return;
    if (tr[u].l >= l && tr[u].r <= r && tr[u].se > 0)
    {
        pushmx(tr[u], 0);
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) update_mx(u << 1, l, r);
    if (r > mid) update_mx(u << 1 | 1, l, r);
    pushup(u);
}

int query(int u, int l, int r)
{
    if (tr[u].mn > 0) return 0;
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].cnt;
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    int res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res; 
}

signed main()
{
    freopen("1.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;    
    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    while (m -- )
    {
        int op, l, r, v;
        cin >> op >> l >> r;
        if (op == 3) cout << query(1, l, r) << endl;
        else 
        {
            cin >> v;
            if (op == 1) update_cover(1, l, r, v);
            else 
            {
                update_add(1, l, r, v);
                update_mx(1, l, r);
            }
        }
    }
    return 0;
}
```

---

