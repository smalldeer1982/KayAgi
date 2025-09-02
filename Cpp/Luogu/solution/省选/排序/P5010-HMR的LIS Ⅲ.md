# HMR的LIS Ⅲ

## 题目背景

[HMR的LIS Ⅰ](https://www.luogu.org/problemnew/show/T51390)

[HMR的LIS Ⅱ](https://www.luogu.org/problemnew/show/T51391)

在你帮助HMR切掉AKIOI的神仙LSK的两道题后，LSK很不满，决定好好刁难一下你（而不是HMR）

## 题目描述

LSK又给出了一个长度为n的序列，要求你求出它的IBvl序列

IBvl序列满足以下要求：

1.一个IBvl序列满足$ \forall ~ i \in (1,len] , L < a_i - a_{i-1} < R $，其中$len$为IBvl序列的长度

2.IBvl序列中的元素相对顺序应满足在原序列中的相对顺序

3.在所有满足条件的序列中长度最长

我们视位置不同的元素为不同元素，有任一组成元素不同的IBvl序列为不同IBvl序列

现在要求你输出原序列的IBvl序列的长度，并输出字典序第k小（以元素在原序列中的位置为关键字排序）的序列的每个元素在原序列中的位置

## 说明/提示

#### 样例解释：

对于给出的数据，一共有$5$种IBvl序列，分别是:$\{6\},\{8\},\{0\},\{2\},\{7\}$。

他们在原序列中位置的编号序列分别是$\{1\},\{2\},\{3\},\{4\},\{5\}$

IBvl序列的长度为1。

要求输出字典序第$3$小的编号序列，于是输出$3$。

#### 数据范围与约定：

对于20%的数据，$ n \le 18$

对于50%的数据，$ n \le 1000 , | l | , | r | \leq 10^9 , r-l>1 , 0 \le a[i] \le 10^9 $

对于另外10%的数据，$ l=0 , r=10^9+1 , k=1 $

对于另外20%的数据，$ l=0 , r=10^9+1 , k \le 3 $

对于100%的数据，$ n \le 5*10^5 , | l | , | r | \le 10^9 , r-l>1 , k \le 10^{13} , 0 \le a[i] \le 10^9 $

对于所有数据，保证合法且有解。

对于前50%的数据，时限为1s，后50%的数据，时限为2s（~~凉~~良心不卡常）

## 样例 #1

### 输入

```
5 3 2 4
6 8 0 2 7```

### 输出

```
1
3```

# 题解

## 作者：DDOSvoid (赞：4)

## Solution

### subtask 1

直接 $2^n$ 枚举子集，然后判断即可，注意要把合法的最长的 IBvl 序列存下来，最后排个序即可 

### subtask 3

求字典序最小的最长上升子序列

考虑求最长上升子序列的 $O(nlog)$ 的做法

实际上是开了一个数组，$d[i]$ 表示长度为 i 子序列最后一位最小可以是多少，我们在记录 d 数组的同时将所有长度为 i 的子序列的最后一位所在的位置都存下来。

最后贪心选即可

注意要倒着求

### subtask 4

求字典序最小/次小/第三小的最长上升子序列

这个我除了正解不会别的做法

~~乱搞AC~~

### subtask 2

其实如果知道了 $O(n^2)$ 的做法就离正解不远了

令 $f[i]$ 表示 i 向后的 IBvl 的最长长度，$g[i]$ 表示方案数

显然可以 $O(n^2)$ 求这两个数组

那么我们有了这两个数组之后，就可以求第 k 小了

肯定是要逐位确定

首先枚举 $f[i]==mx$ 的 i

按照原下标排序，如果 $g[i]<k$，则说明这一位不能选 $i$，并且将 k - g[i]。重复知道 $g[i]\ge k$，说明这一位一定是 i。

那么就可以逐步确定，具体的做法是先按照 $f[i]$ 从大到小排序，对于 $f[i]$ 相同的，按照原下标排序

### subtask 5

我们发现 subtask 2 的瓶颈在于求 f 和 g 数组。

对于 f 的转移 $f[i]=max_{j=i+1}^n(f[j]+1)(a[j]+L< a[i]<a[j]+R)$

发现可以转移的是一段区间，所以那线段树维护就好了

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
#define gc getchar
#define maxn 500010
#define cs const seg
//#define ll __int128
#define ll long long
#define INF 1000000000
#define pc putchar
using namespace std;

ll read(){
    ll x = 0; bool f = 0; char c = gc();
    while(!isdigit(c)){if(c == '-') f = 1; c = gc();}
    while(isdigit(c)){x = x * 10 + c - '0'; c = gc();}
    return f ? -x : x;
}

int st[maxn], top;
void write(ll x){
    if(!x) pc('0'); top = 0;
    while(x){st[++top] = x % 10; x /= 10;}
    while(top) putchar(st[top--] + '0'); puts("");
}

int n, L, R; ll K;

int a[maxn], b[maxn * 3], c1, cnt;
void init_hash(){ c1 = n; a[0] = INF;
    for(int i = 1; i <= n; ++i) b[i] = a[i] = read();
    for(int i = 1; i <= n; ++i) b[++c1] = a[i] + L, b[++c1] = a[i] + R;
    sort(b + 1, b + c1 + 1); cnt = unique(b + 1, b + c1 + 1) - b - 1;
}

inline int get_pos(int v){return lower_bound(b + 1, b + cnt + 1, v) - b;}

inline bool check(int x, int y){
    if(x == INF) return 1;
    return y - x > L && y - x < R;
}

#define lc i << 1
#define rc i << 1 | 1
struct seg{
    int v, id; ll s;
    seg(int _v = 0, ll _s = 0){v = _v; s = _s;}
}T[maxn * 12], A[maxn];
inline void maintain(seg &o, seg ls, seg rs){
    o.v = max(ls.v, rs.v); o.s = 0;
    if(ls.v >= rs.v && ls.v) o.s += ls.s;
    if(ls.v <= rs.v && rs.v) o.s += rs.s;
    o.s = max((ll)1, o.s); o.s = min(o.s, K + 1);
}

void update(int i, int l, int r, int k, cs &o){
    if(l == r){
        if(o.v > T[i].v) T[i] = o;
        else if(o.v == T[i].v) T[i].s += o.s;
        T[i].s = min(T[i].s, K + 1);
        return ;
    } int m = l + r >> 1;
    if(k <= m) update(lc, l, m, k, o);
    else update(rc, m + 1, r, k, o);
    maintain(T[i], T[lc], T[rc]);
}

seg query(int i, int l, int r, int L, int R){
    if(l > R || r < L) return seg(0, 0);
    if(L <= l && r <= R) return T[i];
    int m = l + r >> 1;
    seg t, t1 = query(lc, l, m, L, R), t2 = query(rc, m + 1, r, L, R);
    maintain(t, t1, t2); return t;
}

inline bool cmp(cs &u, cs &v){
    if(u.v == v.v) return u.id < v.id;
    return u.v > v.v;
}
int ans[maxn], c2;
int main(){
    n = read(); K = read(); L = read(); R = read();
    init_hash();
    for(int i = n; i; --i){
        A[i] = query(1, 1, cnt, get_pos(a[i] + L) + 1, get_pos(a[i] + R) - 1); 
        A[i].id = i; ++A[i].v;
        update(1, 1, cnt, get_pos(a[i]), A[i]);
    }
    //    for(int i = 1; i <= n; ++i) cerr << A[i].v << " " << A[i].s << endl;
    sort(A + 1, A + n + 1, cmp); int p = 0, la = 0;
    ll tot = 0;
    for(int i = 1; i <= n; ++i) if(A[i].v == A[1].v) tot += A[i].s;
    //write(tot);
    for(int i = 1; i <= n; i = p){
        p = i;
        while(A[p].v == A[i].v) ++p;
        for(int j = i; j < p; ++j){
            if(A[j].id < la || !check(a[la], a[A[j].id])) continue;
            if(A[j].s >= K){
                ans[++c2] = A[j].id; la = A[j].id;
                break;
            }
            K -= A[j].s;
        }
    }
    cout << A[1].v << endl;
    for(int i = 1; i <= c2; ++i) printf("%d ", ans[i]);
    return 0;
}
```

rqy 的代码

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int S = 10000000;
struct Read {
  inline char gc() { static char buf[S], *p = buf, *end = buf; return p == end ? feof(stdin) ? (char)EOF : (end = buf + fread(p = buf, 1, S, stdin), *(p++)) : *(p++); }
  template<typename T> Read &operator[](T &ans) { ans = 0; int c, f = 1; while (!isdigit(c = gc())) if (c == '-') f = -1; do ans = ans * 10 + c - '0'; while (isdigit(c = gc())); ans *= f; return *this; }
} read;
struct Write {
  char obuf[S], *op, *oend; Write() { op = obuf; oend = obuf + S; }
  inline void flush() { fwrite(obuf, 1, op - obuf, stdout); op = obuf; } inline void putChar(char c) { if (op == obuf) flush(); *(op++) = c; }
  template <typename T> Write &operator[](T ans) { static int c[20]; int p = 0; while (ans) c[p++] = ans % 10, ans /= 10; while (p--) putChar(c[p] + '0'); return *this; }
  Write &operator[](char c) { putChar(c); return *this; }
  ~Write() { flush(); }
} write;
const int N = 500050;
int n, m, L, R, A[N], NL[N], NR[N], B[N], f[N], hd[N], nxt[N], len; LL K, num[N];
void Discretize() { for (int i = 0; i < n; ++i) B[i] = A[i];
  std::sort(B, B + n); m = std::unique(B, B + n) - B;
  for (int i = 0; i < n; ++i) A[i] = std::lower_bound(B, B + m, A[i]) - B;
  for (int i = 0, j = 0; i < m; NL[i] = j, ++i) while (j < m && B[j] <= B[i] + L) ++j;
  for (int i = 0, j = 0; i < m; NR[i] = j, ++i) while (j + 1 < m && B[j + 1] < B[i] + R) ++j; }
struct Msg { int maxv; LL numv; Msg(int x = 0, LL v = 0) : maxv(x), numv(v) {}
  inline void operator+=(const Msg &rhs) { if (maxv < rhs.maxv) maxv = rhs.maxv, numv = rhs.numv; else if (maxv == rhs.maxv) numv = std::min(K, numv + rhs.numv); }
} msgv[1200000];
void Modify(int x, int f, LL v) { Msg adv = Msg(f, v); for (x += len + 1; x; x >>= 1) msgv[x] += adv; }
Msg Query(int l, int r) { Msg ans = Msg(0, 1); if (l > r) return ans;
  for (l += len, r += len + 2; l + 1 != r; l >>= 1, r >>= 1) { if (~l & 1) ans += msgv[l | 1]; if (r & 1) ans += msgv[r & ~1]; } return ans; }
int main() { read[n][K][L][R]; for (int i = 0; i < n; ++i) read[A[i]];
  Discretize(); len = 1; while (len < m + 2) len <<= 1;
  memset(hd, -1, sizeof hd);
  for (int i = n - 1; i >= 0; --i) { Msg ans = Query(NL[A[i]], NR[A[i]]); Modify(A[i], f[i] = ans.maxv + 1, num[i] = ans.numv); nxt[i] = hd[f[i]]; hd[f[i]] = i; }
  int ans1 = 0; while (~hd[ans1 + 1]) ++ans1; write[ans1]['\n'];
  for (int i = ans1, last = -1, l = 0, r = m - 1; i; --i) for (int j = hd[i]; ~j; j = nxt[j]) if (j > last && A[j] >= l && A[j] <= r)
    if (num[j] >= K) { write[(last = j) + 1][' ']; l = NL[A[j]]; r = NR[A[j]]; break; } else K -= num[j];
}
```



---

