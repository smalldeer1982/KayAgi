# Strange Permutation

## 题目描述

Alice had a permutation $ p_1, p_2, \ldots, p_n $ . Unfortunately, the permutation looked very boring, so she decided to change it and choose some non-overlapping subranges of this permutation and reverse them. The cost of reversing a single subrange $ [l, r] $ (elements from position $ l $ to position $ r $ , inclusive) is equal to $ r - l $ , and the cost of the operation is the sum of costs of reversing individual subranges. Alice had an integer $ c $ in mind, so she only considered operations that cost no more than $ c $ .

Then she got really bored, and decided to write down all the permutations that she could possibly obtain by performing exactly one operation on the initial permutation. Of course, Alice is very smart, so she wrote down each obtainable permutation exactly once (no matter in how many ways it can be obtained), and of course the list was sorted lexicographically.

Now Bob would like to ask Alice some questions about her list. Each question is in the following form: what is the $ i $ -th number in the $ j $ -th permutation that Alice wrote down? Since Alice is too bored to answer these questions, she asked you to help her out.

## 说明/提示

In the first test case, Alice wrote down the following permutations: $ [1, 2, 3] $ , $ [1, 3, 2] $ , $ [2, 1, 3] $ .

Note that, for a permutation $ [3, 2, 1] $ Alice would have to reverse the whole array, and it would cost her $ 2 $ , which is greater than the specified value $ c=1 $ . The other two permutations can not be obtained by performing exactly one operation described in the problem statement.

## 样例 #1

### 输入

```
2
3 1 9
1 2 3
1 1
2 1
3 1
1 2
2 2
3 2
1 3
2 3
3 3
6 4 4
6 5 4 3 1 2
1 1
3 14
1 59
2 6```

### 输出

```
1
2
3
1
3
2
2
1
3
1
4
-1
5```

## 样例 #2

### 输入

```
1
12 4 2
1 2 3 4 5 6 7 8 9 10 11 12
2 20
2 21```

### 输出

```
2
2```

# 题解

## 作者：duyi (赞：13)

[噜啦噜啦咧噜啦噜啦咧的阅读体验！](https://www.cnblogs.com/dysyn1314/p/14261805.html)

# CF1470E Strange Permutation

## 题目大意

[题目链接](https://codeforces.com/contest/1470/problem/E)

给出一个 $1$ 到 $n$ 的排列 $p_{1\dots n}$。你可以选择若干个**互不重叠**的区间，并将它们翻转，称为一组翻转操作。翻转一个区间 $[l,r]$ 的代价是 $r - l$。一组翻转的代价是所选区间的代价之和。你希望花费的代价不超过 $c$。

每组可能的翻转操作，都会得到一个排列。考虑其中本质不同的排列，将这些排列按字典序从小到大排序。

你需要回答 $q$ 次询问。每次询问有两个参数 $i,j$，表示问字典序第 $j$ 小的排列里，第 $i$ 个位置上的数是几。如果不存在 $j$ 个排列，则输出 $-1$。

数据范围：$1\leq n\leq 3\times10^4$，$1\leq c\leq 4$，$1\leq q\leq 3\times 10^5$。

## 本题题解

首先，因为操作互不重叠，且原序列是个排列，所以得到的结果序列一定互不相同。那么一组翻转操作，就唯一对应一个结果序列。问题从找字典序第 $j$ 小结果序列，转化为找排序后第 $j$ 个翻转操作组。

考虑一个长度为 $n$ 的序列，进行总代价不超过 $c$ 的一组翻转操作，能得到多少种结果？枚举总代价 $i$ ($0\leq i\leq c$)。在序列每两个元素之间放一个小球（共 $n - 1$ 个小球）。则一次操作的代价，就是区间里的小球数。所以恰好进行 $i$ 次操作的方案数就是 ${n - 1\choose i}$。总代价不超过 $c$ 的方案数，就是 $\text{ways}(n, c) = \sum_{i = 0}^{c}{n - 1\choose i}$。若询问的 $j$ 大于这个数，则可以直接输出 $-1$。

设 $F(i, c, k)$，表示仅考虑 $[i,n]$ 这段后缀，花费的总代价不超过 $c$ 的，（结果序列的字典序）第 $k$ 小的**翻转操作组**中的，第一个翻转操作（换句话说它返回一组 $(l,r)$ 表示这个操作）。

为了快速实现 $F$ 函数，我们先预处理一个列表 $L(i, c)$。表示 $[i, n]$ 这段后缀，花费的总代价不超过 $c$，按得到的序列的字典序小到大排序的，“第一次操作”的序列。即：序列里每个元素，是一个区间，表示对这个区间进行翻转操作，以这个翻转操作为**第一次操作**的**翻转操作组**。假设翻转操作为 $(l,r)$，则这样的翻转操作组数量就是 $w = \text{ways}(n - r, c - (r - l))$。把这样的 $(w, l, r)$ 作为一个元素存在 $L$ 中。即：$L(i, c) = \{(l_1, r_1, w_1), (l_2,r_2, w_2),\dots,(l_k, r_k, w_k)\}$。那么求 $F(i, c, k)$ 时，我们只需要在 $L(i, c)$ 序列里二分出最小的 $j$，满足 $w_1 + w_2 + \dots + w_j \geq k$，则 $F(i, c, k) = (l_j,r_j)$。

考虑求 $L$。按 $i$ 从大到小递推。

从 $i + 1$ 推到 $i$ 时，只需要插入以 $i$ 为左端点的翻转操作。即 $(i, i + j)$ ($1\leq j\leq \min(c, n - i)$)，这样的操作最多不超过 $c$ 个。暴力枚举这些操作。考虑原来在 $L(i + 1, c)$ 里的操作，它们对应的序列的第一个元素，现在都是 $p_i$。而 $(i, i + j)$ 对应的序列的第一个元素，是 $p_{i + j}$。因为 $p_{i + j}\neq p_i$，所以 $(i, i + j)$ 这个操作，**要么插入到原来所有操作的左边，要么插入到原来所有操作的右边**。

于是我们用一个 $\texttt{deque}$ 来维护，即可推出 $L(1, c)$。在 $L(1, c)$ 上找到一个连续的区间，即可得到 $L(i, c)$。

预处理出 $L$ 后，可以通过二分，在 $\mathcal{O}(\log(nc))$ 的时间内实现 $F$ 函数。通过调用最多不超过 $c$ 次 $F$ 函数，可以回答一个询问。

时间复杂度 $\mathcal{O}(nc^2 +qc\log (nc))$。

## 参考代码


[勇敢向前进 前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/14261805.html)



---

## 作者：Maverik (赞：7)

模拟赛放 T1，*3200 不至于。

$O(nkQ)$ 的做法是显然的，可以用那种线段树二分的思想，预处理 $f(i,j)$ 表示 $[i,n]$ 用不超过 $j$ 的代价能形成的本质不同排列数。

由于操作无交，容易发现操作的二元组集合和形成的排列构成双射，所以预处理很容易，可以 $O(nk)$ 做。

考虑处理完 $[1,i)$ 之后，还剩下 $rk$ 个名次，剩下 $resk$ 的代价。如何让 $i$ 位的字典序更小，发现只关心 $[i,i+resk]$ 区间的数字。

从小到大考虑数字，对于数字 $v$ 在位置 $p$ 上，如果 $rk\le f(p+1,resk-p+i)$，递归到 $p+1$ 的位置就可以了。

否则 $rk\leftarrow rk-f(p+1,resk-p+i)$，接着考虑下一个 $p$。

这样做是 $O(nkQ)$ 的，需要优化。

容易想到从 $k\le 4$ 入手优化，也就是上文 $p\neq i$ 的递归至多有 $k$ 个。

假设现在有一段 $p=i$ 的左端点，右端点显然可以二分，考虑如何 check。

预处理 $g(i,j)=\sum_{a_p<a_i\wedge p-i\le j} f(p+1,j-p+i)$，
并处理前缀和 $s(i,j)=\sum_{k\le i} g(k,j)$，直接 $O(nk^2)$ 预处理就可以了。

对于左端点 $l$，右端点 $r$ 合法当且仅当 $0<rk-s(r-1,resk)+s(l-1,resk)\le f(r,resk)$，分别对应能够转移的上下界。

然后就可以做到 $O(nk^2 +Qk\log n)$ 了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;
const __int128 top=1e25+2;
__int128 f[maxn][6],g[maxn][6],s[maxn][6]; 

int n,K,Q,tage;
int a[maxn];
vector<pii>vec[maxn];
inline int calc(int x,int rk,int resk)
{
    int l=x,r=n+1,div=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        __int128 delta=rk-(s[mid-1][resk]-s[x-1][resk]);
        if(1<=delta && delta<=f[mid][resk]) div=mid,l=mid+1;
        else r=mid-1;
    }
    if(x==div)
    {
        for(auto [v,p]:vec[x]) if(p-x<=resk)
        {
            int nxtresk=resk-(p-x);
            if(rk<=f[p+1][nxtresk])
            {
                if(x<=tage && tage<=p) return a[p-tage+x];
                return calc(p+1,rk,nxtresk);
            }
            rk-=f[p+1][nxtresk];
        }
        return -1;
    }
    else
    {
        if(x<=tage && tage<div) return a[tage];
        rk-=(s[div-1][resk]-s[x-1][resk]);
        return calc(div,rk,resk);
    }
}
inline void solve()
{
    cin>>n>>K>>Q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int x=1;x<=n;x++)
    {
        for(int i=x;i<=min(n,x+K);i++) vec[x].emplace_back(a[i],i);
        sort(vec[x].begin(),vec[x].end());
    }
    for(int k=0;k<=4;k++) f[n+1][k]=1;
    for(int i=n;i>=1;i--) for(int k=0;k<=4;k++)
    {
        if(k>=0) f[i][k]+=f[i+1][k];
        if(k>=1) f[i][k]+=f[i+2][k-1];
        if(k>=2) f[i][k]+=f[i+3][k-2];
        if(k>=3) f[i][k]+=f[i+4][k-3];
        if(k>=4) f[i][k]+=f[i+5][k-4];
    }
    for(int i=1;i<=n;i++) for(int j=0;j<=K;j++)
        for(auto [v,p]:vec[i]) if(v<a[i] && p-i<=j)
            g[i][j]+=f[p+1][j-(p-i)];
    for(int i=1;i<=n;i++) for(int j=0;j<=K;j++)
        s[i][j]=s[i-1][j]+g[i][j];
    for(int i=1,x;i<=Q;i++)
    {
        cin>>tage>>x;
        if(x>f[1][K]){ cout<<"-1\n"; continue; }
        cout<<calc(1,x,K)<<'\n';
    }
    for(int i=1;i<=n;i++) vec[i].clear();
    for(int i=0;i<=n+1;i++) for(int j=0;j<=K;j++) f[i][j]=g[i][j]=s[i][j]=0;
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);
    int T;cin>>T; while(T-- )solve();
}
```

---

## 作者：I_am_Accepted (赞：3)

### Analysis

先考虑总共的合法序列数 $\text{ways}(n,c)$。通过简单的组合计数得出 $\text{ways}(n,c)=\sum\limits_{i=0}^c\binom{n-1}{i}$，可以暴力计算。如果询问超过了这个数，直接 $-1$ 送走。

结论：如果最靠左的 Reverse 相同（$l,r$ 都相同），那么这些序列在字典序中是连续的。

由于 $p_{1\dots n}$ 互不相等，上述结论显然。

而且如果将序列以从左往右数第一个被改动过的下标标号，那么最终字典序的标号依次为：

$$1\times k_1,2\times k_2,3\times k_3,\dots,(n-1)\times k_{n-1},n\times k_n,$$
$$(n-1)\times k_{n+1},(n-2)\times k_{n+2},(n-3)\times k_{n+3},\dots,1\times k_{2n-1}$$

其中 $a\times b$ 表示 $a$ 连续出现 $b$ 次，$k_{\dots}$ 为非负整数。

很容易想到倒序遍历 $p$ 并维护字典序 Deque。

注意 Deque 中是按序列的字典序排的。

具体地，我们对于每一个固定的代价上限 $s\in[1,c]$，维护一个不超过该代价的 Deque。Deque 中每一个元素 $\{l,r,cnt\}$ 表示从左往右第一个翻转在 $[l,r]$，这样的合法序列有 $cnt$ 个（也就是用 $1$ 个来代表 $cnt$ 个），显然 Deque 里的元素不超过 $nc$ 个。

由于从 $i+1$ 遍历到 $i$，首个变动位置为 $i$ 的那些序列只可能插在前后（但是这些内部要排序），$c+1$ 个 Deque 构造的时间是 $O(c(nc)\log (nc))$ 的。

接下来就是对每个问题 $(pos,rk)$ 的求解。我们先求出排名 $rk$ 的排列 Reverse 了哪些区间，这样求出 $pos$ 位置上的数就简单至极了。

先在 $c$ 的 Deque 上二分找到排名 $rk$ 序列的第一个翻转 $[l_1,r_1]$，并将 $rk$ 减去那些因字典序靠前被排除掉的个数，再在 $c-1$ 的 Deque 上且首个变动位置 $>r_1$（Reverse 不交）中找到排名 $rk$，以此类推到 $0$。时间 $O(qc\log(nc))$。

这个过程好比查阅一本很厚的书。这本书的每一章节中间都有连续的一段是上一章的全部内容，而章节里每一个小节中间都有上一小节的全部内容……所以每一层级只要一张目录表，但是当你从第一章节和第三章节进来检索小节时，在小节目录里检索的范围不同而已。

总时间 $O(c(nc)\log (nc)+qc\log(nc))$。

### Code

可能我上面那段话有点难懂，所以我尽力把代码写漂亮了 qwq。

[Link](https://codeforces.com/contest/1470/submission/145640694)

---

## 作者：sunkuangzheng (赞：0)

没有发现太多性质，那就大力 ds。

首先翻转操作不交，一种操作序列唯一对应一个排列。

对字典序影响最大的一定是第一次操作。不可能存在 $i<j<k<l$ 使得：翻转 $(i,j)$ 比翻转 $(i,l)$ 劣但是翻转 $(i,j),(k,l)$ 比翻转 $(i,l)$ 优。

到这里这道题的思路应该很明确了：对于每组询问，依次二分出它的第 $1,2,\ldots,c$ 次操作分别在哪里。

我们先求出翻转每一对 $(i,j)$ 后的 $p'$ 间的大小关系：做一些简单分讨即可。然后需要求出 $g_{i,j}$：有多少翻转方法，使得第一个翻转的区间是 $[i,j]$。这里是一个普及组 DP，设 $dp_{i,j}$ 是长度为 $i$ 的序列，$\sum r - l = j$ 的方案数，转移有 $dp_{i,j} = \sum\limits_{k=0}^j dp_{i-k-1,j-k}$，做一遍前缀和即可得到 $\sum r - l \le j$ 的方案（如果你仔细观察可以发现其实 $dp_{i,j} = \binom{i}{j}$）。

找到第一次操作很容易，这可以直接二分。但是找到第一次操作后，每个询问的 $j$ 和剩余的 $c$ 都不同，导致其第二次操作的决策并不相同。每个询问的决策都需要满足 $i \ge j',r - l \le c'$。

考虑离线所有询问，首先枚举操作轮数 $r \in [1,c]$，然后枚举 $c'$。倒序扫描 $i = n,n-1,\ldots,1$，每次将以 $i$ 为左端点的 $r-l \le c'$ 的决策加入。查询时需要二分，我们用线段树动态维护。

总时间复杂度 $\mathcal O(nc^3 \log n + qc \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 17.10.2024 08:51:28
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif

#include <algorithm>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

#include <cassert>
#include <vector>

namespace atcoder {

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder


using ll = long long;
ll sss(ll x,ll y){return x + y;}
ll eee(){return 0ll;}
const int N = 3e5+5;
using namespace std;
int T,n,c,q,p[N],id[N][5],x,ax[N],na[15],nb[15]; ll g[N][5],y,tg;
vector<pair<ll,int>> qr[N][5],rq[N][5]; vector<pair<int,int>> as[N];
struct rg{
    int l,r; rg(int _l,int _r){l = _l,r = _r;}
    bool operator <(const rg &x)const{
        int al = x.l,ar = x.r,bl = l,br = r,fg = 0;
        if(al < bl) swap(al,bl),swap(ar,br),fg = 1;
        int sz = 0;
        for(int i = bl;i <= br;i ++) na[sz] = p[i],nb[sz ++] = p[i];
        for(int i = max(al,br + 1);i <= ar;i ++) na[sz] = p[i],nb[sz ++] = p[i];
        reverse(na,na + br - bl + 1);
        reverse(nb + min(br + 1 - bl,al - bl),
            nb + min(br + 1 - bl,al - bl) + ar - al + 1);
        for(int i = 0;i < sz;i ++) 
            if(na[i] < nb[i]) return fg ^ 1; 
            else if(na[i] > nb[i]) return fg;
        return 0;
    }
};
bool f(ll x){return x <= tg;}
bool zr(ll x){return x == 0;}
void los(){
    cin >> n >> c >> q;
    for(int i = 1;i <= n;i ++) cin >> p[i],as[i].clear();
    for(int i = 1;i <= n;i ++) for(int j = 0;j <= c;j ++) qr[i][j].clear(),rq[i][j].clear();
    vector<rg> a; a.emplace_back(0,0);
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= c && i + j <= n;j ++) 
        a.emplace_back(i,i + j);
    stable_sort(a.begin(),a.end());
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= c && i + j <= n;j ++)
        id[i][j] = lower_bound(a.begin(),a.end(),rg{i,i + j}) - a.begin() + 1;
    id[0][0] = lower_bound(a.begin(),a.end(),rg{0,0}) - a.begin() + 1; 
    int m = a.size();
    // for(int i = 0;i < m;i ++) cerr << a[i].l << " " << a[i].r << "\n";
    for(int i = 1;i <= q;i ++){
        cin >> x >> y,ax[i] = x;
        if(y > g[n][c]) {ax[i] = -1; continue;}
        rq[1][0].emplace_back(y,i);
    }
    atcoder::segtree<ll,sss,eee> sg(m + 1);
    for(int j = 1;j <= c;j ++){
        for(int i = 1;i <= n;i ++) for(int k = 0;k <= c;k ++) 
            qr[i][k] = rq[i][k],rq[i][k].clear();
        for(int l = 0;l <= c;l ++){
            sg.set(id[0][0],1);
            for(int i = n;i >= 1;i --){
                for(int k = 1;k <= c - l && k + i <= n;k ++)
                    sg.set(id[i][k],g[n - (i + k)][c - (l + k)]);
                
                for(auto [x,id] : qr[i][l]){
                    tg = x - 1;
                    int p = sg.max_right<f>(1);
                    if(p == m + 1) continue;
                    auto [xx,y] = a[p - 1];
                    if(!xx) continue; 
                    ll sm = sg.prod(1,p);
                    as[id].emplace_back(xx,y);
                    if(sm - x) rq[y + 1][l + (y - xx)].emplace_back(x - sm,id);
                }
            }sg.set(id[0][0],0);
            for(int i = n;i >= 1;i --)
                for(int k = 1;k <= c - l && k + i <= n;k ++)
                    sg.set(id[i][k],0);
        }
    }for(int i = 1;i <= q;i ++){
        if(ax[i] == -1) {cout << "-1\n"; continue;} 
        for(auto [x,y] : as[i]) reverse(p+x,p+y+1);
        cout << p[ax[i]] << "\n";
        for(auto [x,y] : as[i]) reverse(p+x,p+y+1);
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    n = 3e4,g[0][0] = 1;
    for(int i = 1;i <= n;i ++) for(int j = 0;j <= 4;j ++) for(int k = 0;i - k - 1 >= 0 && k <= j;k ++)
        g[i][j] += g[i - k - 1][j - k];
    for(int i = 0;i <= n;i ++) for(int j = 1;j <= 4;j ++) g[i][j] += g[i][j - 1];
    // for(int i = 1;i <= 9; i++) for(int j = 0;j <= 4;j ++)
    //     cerr << g[i][j] << " \n"[j == 4];
    for(cin >> T;T --;) los();
}

```

---

## 作者：xcyyyyyy (赞：0)

考虑算出有多少个不同的排列，考虑 dp，$f_{i,j}$ 表示后缀 $[i,n]$，还有 $j$ 的代价可以使用，转移为 $f_{i,j}=\sum \limits_{k=0}^{\min(n-i,j)}f_{i+k+1,j-k}$。

然后考虑如何算出第 $j$ 个排列的具体值，这个很好计算，考虑从 $1$ 开始，从小到大枚举第一个字符，然后对应翻转即可。

暴力做是 $O(nq)$ 的，由于 $c\leq 4$，我们至多翻转 $c$ 次，其他情况我们都是不变的，我们希望快速处理不反转的情况，直接处理倍增数组即可。时间复杂度 $O(nc^2+qc\log n)$。

比较难写，vp 后两分钟发现有两行写反了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 30005
#define ll long long
#define fr first
#define se second
int t,n,q,c,a[N];
ll f[N][6];
pair<ll,ll> go[N][6][16];//(l,r]
void work(){
	scanf("%d%d%d",&n,&c,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=0;i<=c;i++)f[n+1][i]=1;
	for(int i=n;i;i--){
		for(int j=0;j<=c;j++){
			f[i][j]=0;
			for(int k=0;k<=min(n-i,j);k++)f[i][j]+=f[i+k+1][j-k];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=c;j++){
			go[i][j][0].fr=0;
			for(int k=0;k<=min(n-i,j);k++)if(a[i+k]<a[i])go[i][j][0].fr+=f[i+k+1][j-k];
			go[i][j][0].se=go[i][j][0].fr+f[i+1][j];
		}
	}
	for(int k=1;k<=14;k++){
		for(int i=1;i+(1<<k)-1<=n;i++){
			for(int j=0;j<=c;j++){
				go[i][j][k].fr=go[i][j][k-1].fr+go[i+(1<<k-1)][j][k-1].fr;
				go[i][j][k].se=go[i][j][k-1].fr+go[i+(1<<k-1)][j][k-1].se;
			}
		}
		for(int i=max(n-(1<<k)+2,1);i<=n;i++)for(int j=0;j<=c;j++)go[i][j][k]={0,0};
	}
	while(q--){
		int i,r=c;ll j;
		scanf("%d%lld",&i,&j);
		if(j>f[1][c]){puts("-1");continue;}
		int p=1;
		while(p<=i){
			for(int k=14;k>=0;k--)if(p+(1<<k)<=i&&go[p][r][k].fr<j&&j<=go[p][r][k].se)j-=go[p][r][k].fr,p+=(1<<k);
			if(p==i&&go[p][r][0].fr<j&&j<=go[p][r][0].se){printf("%d\n",a[p]);break;}
			int b[10]={0},m=0,to;
			for(int k=0;k<=min(n-p,r);k++)b[++m]=p+k;
			sort(b+1,b+1+m,[](const int x,const int y){return a[x]<a[y];});
			for(int i=1;i<=m;i++)
				if(j>f[b[i]+1][r-(b[i]-p)])j-=f[b[i]+1][r-(b[i]-p)];
				else{
					to=b[i];
					break;
				}
			if(p<=i&&i<=to){
				printf("%d\n",a[to-(i-p)]);
				break;
			}
			r-=to-p;
			p=to+1;
		}
	}
}
int main(){
	scanf("%d",&t);
	while(t--)work();
}
```

---

## 作者：冷月葬T魂 (赞：0)

简要题意：给定一个长为 $n$ 的排列 $p$ 和一个整数 $c\le 4$，称排列 $p'$ 合法当且仅当 $p'$ 可以通过 $p$ 翻转若干个**不交**的区间 $[l,r]$ 得到，并且这些区间的长度和 $r-l\le c$。$Q$ 次询问所有合法的 $p'$ 中字典序第 $x$ 小的第 $y$ 个位置的值。$n,Q\le 3\times 10^5,c\le 4$。

考虑每个询问的结果 $p'$ 和原排列 $p$ 至多相差 $c$ 个位置，考虑从这里入手。 

将所有询问按 $x$ 排序，考虑这样一个过程：定义 $solve(u,c,rk,L,R)$ 表示当前已经确定了 $p'$ 前 $u$ 项的位置，当前还剩下 $c$ 的交换次数可用，前 $u$ 项已经加的排名量为 $rk$，只需处理 $L,R$ 内的询问。在 $solve$ 中，我们将 $a_u\sim a_{u+c}$ 排序，然后分别从左往右和从右往左拿一个指针扫一遍询问数组，将 $a_u$ 这个位置会改变的询问拎出来递归处理，最后剩下一些 $a_u$ 这个位置不改变的直接递归处理（注意这些询问不用花时间扫一遍）。**在递归处理时，我们首先在序列上二分出询问 $[L,R]$ 中第一个有任意一个询问会改变的位置，将 $u$ 跳到那个位置再开始处理**。至于如何迅速求出一个点 $u$ 往后至多花 $c$ 的长度翻转的方案数，发现这等价于 $u\sim n$ 一共 $n-u$ 个空位中选出至多 $c$ 个空位放横杠的方案数，可以 $O(1)$ 计算。

看一下这样做的时间复杂度为什么是对的。首先关于扫询问那部分的复杂度，由于每扫过一个询问就意味着该询问在该位置上改变了一下，而所有询问的总改变次数是 $O(Qc)$ 的，所以这部分扫的时间复杂度为 $O(Qc)$。**重点在于递归次数的复杂度分析，很有借鉴意义**。考虑所有可能的操作序列形成一个类似 $c$ 叉树的结构（尽管有些节点可能不足 $c$ 个儿子），现在的询问相当于询问第 $x$ 个叶子的信息。**如果前面递归下去时不二分，那么这个过程就相当于将这些叶子形成的“虚树”拎出来，保留“虚树”的每条边上原树的若干节点，得到的“虚树”大小，这显然是 $O(Qn)$ 的。但是，我们的二分操作相当于跳过了所有“虚树”上不分叉的位置，也就是相当于取出了一棵真正的只保留 LCA 的虚树！于是 $solve$ 操作只会调用 $O(Q)$ 次！**

时间复杂度 $O(nc^2+Qc+Q\log n+sort(Q))$。

代码如下：

```cpp
#include "bits/stdc++.h"
#define For(i, a, b) for (int i = a; i <= b; i++)
#define Rev(i, a, b) for (int i = a; i >= b; i--)
#define Fin(file) freopen(file, "r", stdin)
#define Fout(file) freopen(file, "w", stdout)
#define assume(expr) ((!!(expr)) || (exit((fprintf(stderr, "Assumption Failed: %s on Line %d\n", #expr, __LINE__), -1)), false))
using namespace std;
const int N = 3e5 + 5;
typedef long long ll;
struct Query
{
    ll x, y;
    int id;
    bool operator<(const Query &qry) const { return x < qry.x; }
} qry[N];
int n, CC, Q, a[N], ans[N];
ll _Get[N][5];
ll ssum[N][5];
vector<int> nxt[N];
inline ll C(ll x, int y)
{
    if (y < 0 || x < y)
        return 0;
    ll res = 1;
    For(i, 1, y) res = res * (x - i + 1) / i;
    return res;
}
inline ll __Get(int i, int j)
{
    if (i == n + 1)
        return 1;
    ll res = 0;
    For(k, 0, j) res += C(n - i, k);
    return res;
}
inline ll Get(int i, int j) { return _Get[i][j]; }
bool check(int u, int v, int c, ll rk, ll x)
{
    rk += ssum[v][c] - ssum[u - 1][c];
    bool res = rk < x && x <= rk + Get(v + 1, c);
    return res;
}
void solve(int u, int c, ll rk, int L, int R);
void work(int u, int c, ll rk, int L, int R)
{
    if (L > R)
        return;
    int l = u, r = n + 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(u, mid, c, rk, qry[L].x) && check(u, mid, c, rk, qry[R].x))
            l = mid + 1;
        else
            r = mid;
    }
    solve(l, c, rk + ssum[l - 1][c] - ssum[u - 1][c], L, R);
}
void solve(int u, int c, ll rk, int L, int R)
{
    if (L > R)
        return;
    if (u == n + 1 || c == 0)
    {
        For(i, L, R) ans[qry[i].id] = a[qry[i].y];
        return;
    }
    int sz = nxt[u].size(), pp = L;
    ll cur = rk;
    For(ooo, 0, sz - 1)
    {
        int c0 = nxt[u][ooo];
        if (c0 == 0)
            break;
        else if (c0 > c || u + c0 > n)
            continue;
        int lst = pp;
        while (pp <= R && qry[pp].x <= cur + Get(u + c0 + 1, c - c0))
            pp++;
        reverse(a + u, a + u + c0 + 1);
        work(u + c0 + 1, c - c0, cur, lst, pp - 1);
        cur += Get(u + c0 + 1, c - c0);
        reverse(a + u, a + u + c0 + 1);
    }
    int PosL = pp;
    pp = R;
    cur = rk + Get(u, c);
    Rev(ooo, sz - 1, 0)
    {
        int c0 = nxt[u][ooo];
        if (c0 == 0)
            break;
        else if (c0 > c || u + c0 > n)
            continue;
        cur -= Get(u + c0 + 1, c - c0);
        int lst = pp;
        while (pp >= L && qry[pp].x > cur)
            pp--;
        reverse(a + u, a + u + c0 + 1);
        work(u + c0 + 1, c - c0, cur, pp + 1, lst);
        reverse(a + u, a + u + c0 + 1);
    }
    cur -= Get(u + 1, c);
    work(u + 1, c, cur, PosL, pp);
}
void Solve()
{
    cin >> n >> CC >> Q;
    For(i, 1, n) cin >> a[i];
    For(i, 1, n + 1) For(j, 0, CC) _Get[i][j] = __Get(i, j);
    For(i, 1, n)
    {
        nxt[i].clear();
        For(j, 0, min(CC, n - i)) nxt[i].push_back(j);
        sort(nxt[i].begin(), nxt[i].end(), [&](int x, int y)
             { return a[i + x] < a[i + y]; });
        int sz = nxt[i].size();
        For(c, 0, CC)
        {
            ssum[i][c] = ssum[i - 1][c];
            For(ooo, 0, sz - 1)
            {
                int c0 = nxt[i][ooo];
                if (c0 == 0)
                    break;
                else if (c0 > c || i + c0 > n)
                    continue;
                ssum[i][c] += Get(i + c0 + 1, c - c0);
            }
        }
    }
    int qcnt = 0;
    For(i, 1, Q)
    {
        ll x, y;
        cin >> y >> x;
        if (x > Get(1, CC))
            ans[i] = -1;
        else
            qry[++qcnt] = {x, y, i};
    }
    sort(qry + 1, qry + 1 + qcnt);
    solve(1, CC, 0, 1, qcnt);
    For(i, 1, Q)
    {
        if (ans[i] >= 0)
            cout << ans[i] << '\n';
        else
            cout << "-1\n";
    }
    For(i, 1, n + 1) For(j, 0, CC) _Get[i][j] = 0;
}
signed main()
{
    int T;
    cin >> T;
    while (T--)
        Solve();
    cerr << "Time = " << clock() << " ms" << endl;
    return 0;
}

```

---

