# Problem with Queries

## 题目描述

给定一个整数数组 $a$，长度为 $n$。你的任务是处理 $q$ 个查询，这些查询分为两种类型：

- 类型 1：`1 p x` — 将数组中索引为 $p$ 的元素值更新为 $x$；
- 类型 2：`2 l r` — 计算数组 $a$ 中满足条件的索引对 $(i, j)$ 的数量，其中 $l \le i < j \le r$ 且 $a_i \ne a_j$。

请注意，这些查询是编码过的；每个后续查询必须在解出前一个类型 2 查询的答案后才能解码。

## 样例 #1

### 输入

```
3
1 2 3
5
2 0 2
1 0 2
2 0 2
1 2 0
2 1 0```

### 输出

```
3 2 0```

## 样例 #2

### 输入

```
7
1 3 4 4 7 1 3
3
2 1 6
2 1 0
2 5 6```

### 输出

```
13 18 0```

# 题解

## 作者：Gold14526 (赞：6)

$\rm Problem:$[Problem with Queries](https://www.luogu.com.cn/problem/CF2043G)

$O((n+q)\sqrt{n})$ 做法。

## 前言

这不我们 [[Ynoi2010] Brodal queue](https://www.luogu.com.cn/problem/P6019) 弱化嘛。

## 题意

维护长度为 $n$ 的序列 $a$，要求支持以下操作：

- ```1 p x``` 将 $a_p$ 赋值为 $x$。
- ```2 l r``` 求有多少对 $(i,j)$ 使得 $l\le i<j\le r$ 且 $a_i\neq a_j$。

强制在线。

$1\le n\le10^5,1\le q\le 3\times10^5,1\le a_i,x\le n$。

## 做法

分块，设 $m=\sqrt{n}$ 为块数。

设 $tot_{i,x}$ 表示前 $i$ 个数中 $x$ 的个数，发现只要能够计算出 $\sum_{x=1}^n(tot_{r,x}-tot_{l-1,x})^2$ 即可。

用 $(a-b)^2=a^2+b^2-2ab$ 拆开来计算。

### 计算 $\sum_{x=1}^ntot_{i,x}^2$

这一部分是较为简单的，假设 $i$ 在第 $p$ 个块中，如果我们知道第 $p-1$ 个块右端点的 $R$ 的 $tot_{R,x},\sum_x tot_{R,x}^2$，不难 $O(\sqrt{n})$ 递推到 $i$。

那我们直接存下这两个值，每次修改的时候暴力重新计算它们即可，一共只会修改 $O(\sqrt{n})$ 个值，所以复杂度也是 $O(\sqrt{n})$ 的。

### 计算 $\sum_{x=1}^ntot_{l-1,x}tot_{r,x}$

假设 $l-1,r$ 分别在第 $p,q$ 个块中，如果我们知道第 $p-1$ 个块右端点 $R_{p-1}$，第 $q-1$ 个块右端点 $R_{q-1}$ 的 $tot_{R_{p-1},x},tot_{R_{q-1},x},\sum_xtot_{R_{p-1},x}tot_{R_{q-1},x}$，不难 $O(\sqrt{n})$ 递推到 $l-1,r$。

方便起见，设 $f_{i,j}=\sum_xtot_{i,x}tot_{j,x}$，并将第一维视作行，第二维视作列。

若 $a_k$ 变为了 $x$，则对于所有 $k\le i\le m$ 的 $i$，$tot_{i,x}$ 加上了 $1$，由于加 $1$ 和减 $1$ 处理十分类似，所以只讨论此时加 $1$ 对 $f_{i,j}$ 的影响：

- 若 $1\le i<k,1\le j<k$，那么 $f_{i,j}$ 不会被影响。
- 若 $1\le i<k,k\le j\le m$，那么 $f_{i,j}$ 会加上 $tot_{i,x}(tot_{j,x}+1)-tot_{i,x}tot_{j,x}=tot_{i,x}$，即对于 $1\le i<k$ 的所有 $i$，要给所有 $k\le j\le m$ 的 $f_{i,j}$ 加上 $tot_{i,x}$，这是一个行上的后缀加，不难 $O(\sqrt{n})$ 维护。
- 若 $k\le i\le m,k\le j\le m$，那么 $f_{i,j}$ 会加上 $(tot_{i,x}+1)(tot_{j,x}+1)-tot_{i,x}tot_{j,x}=tot_{i,x}+tot_{j,x}+1$，这是一个行上的后缀加和一个列上的后缀加，同理 $O(\sqrt{n})$ 维护。

于是，我们就在 $O((n+q)\sqrt{n})$ 的时间复杂度内解决了这个问题。

## 提交记录

[submission](https://codeforces.com/contest/2043/submission/298477685)

---

## 作者：spdarkle (赞：4)

先来做一些基本的推导吧。

首先可以发现，如果我们可以分块，那么只需要 $O(B)$ 的移动就可以将区间端点变为块的端点（开临时桶，维护块前缀和）。

于是问题就变为了维护块端点的答案。

那么每个块本质上就变成一个可重集了，每次我们对 $l\sim r$ 的集合进行合并并给出每个元素出现次数的**平方和**（维护 $sum$ 是容易的）。

$$
\begin{aligned}
&\sum_x (cnt_{r,x}-cnt_{l-1,x})^2\\
=&\sum_x cnt^2_{r,x}+cnt^2_{l-1,x}-2cnt_{l-1,x}cnt_{r,x}
\end{aligned}
$$
$\sum_{x}cnt_{r,x}^2$ 也是易于维护的，可以简单 $O(\frac{n}{B})$。

关键在于对于 $\sum_x cnt_{r,x}cnt_{l-1,x}$ 的维护，不妨称这个就是 $l\leftarrow l-1$，并称呼其为 $w(l,r)$。

考虑在集合 $p$ 加入一个元素 $x$ 的影响，删除是类似的：

1. $r< p$ 无影响。
2. $l<p\le r,w'(l,r)=w(l,r)+cnt_{l,x}$
3. $p\le l,w'(l,r)=w(l,r)+cnt_{l,x}+cnt_{r,x}+1$

注意到修改可以描述为：

1. $\forall l$，将 $r\in [p,ed]$ 全部加上 $cnt_{l,x}$。
2. $\forall r\ge p$，将 $l\in [p,r]$ 全部加上 $cnt_{r,x}+1$。

如果我们将 $w(l,r)$ 看作一个矩阵，那么相当于每次对一行/一列做区间修改，然后我们需要求某个位置的值。

在修改的时候可以发现行列独立，那么不妨维护 $wh(l,r),ww(l,r)$ 表示操作 $1$ 或者操作 $2$ 的增量。

注意到我们对于区间的修改是相当多的，会有 $O(q\frac{n}{B})$ 次，但是我们只会查询 $O(q)$ 次。

不妨想办法平衡这个复杂度。

注意到修改可以变为差分，因此我们只需要变成单点修改 $O(q\frac{n}{B})$ 次。

事实上 $w(l,r)$ 是一个 $\frac{n}{B}\times \frac{n}{B}$ 的矩阵，因此可以直接暴力查询对应行/列，计算是单次 $O(\frac{n}{B})$ 的。

然后再算上处理散块的 $O(B)$，总复杂度 $O((n+q)({B+\frac{n}{B}}))$。

取 $B=\sqrt n$，得到 $O((n+q)\sqrt n)$。

[参考实现](https://codeforces.com/contest/2043/submission/298481838)

---

## 作者：Rosabel (赞：3)

分块清新题。

题目大意即单点修改，求区间颜色相同二元组数量，且强制在线。求区间颜色相同二元组数量，即便是静态问题也很难做到 polylog。所以考虑分块。

先思考没有修改的情况要怎么做。分成整块 + 整块，整块 + 散块，散块 + 散块三个部分。对于整块 + 整块，可以预处理出 $ans(l,r)$ 表示 $l$ 和 $r$ 块之间的答案，预处理数组总时间复杂度是 $\Theta(n\sqrt{n})$。对于整块 + 散块，拎出散块中的每一个元素，记录前缀和 $buc(x,i)$ 数组表示值 $x$ 在 $1\sim i$ 块中的出现次数。那么对于一个散块的元素可以利用 $buc$ 数组 $\Theta(1)$ 求出元素在整块内的出现次数。对于散块 + 散块，直接开一个 $cnt$ 数组表示当前统计过的散块元素每个值出现次数，也可以每个元素 $\Theta(1)$ 做。总时间复杂度 $\Theta((n+q)\sqrt{n})$。这个部分的方法比较常见的。

接下来考虑有修改的情况。我的第一反应是要根号重构，发现没有意义，因为不同颜色之间无法通过信息合并优化复杂度，所以还是老老实实地在线处理修改。一个值的改变可能对 $ans$ 数组的 $\Theta(n)$ 个状态发生改变，只能观察更新值对 $ans$ 影响的结构从而找到性质。发现 $ans$ 发生改变的极小区间必然形如 $(p,p)\text{modify}-p$，$(i,p)\text{modify}-p$ 和 $(p,i)\text{modify}-p$。这些状态是 $\Theta(\sqrt{n})$ 级别的。可以猜想是否可以只维护这些信息然后对于非极小区间可以通过前缀和之类的优化而覆盖到。这时再去观察这些极小区间与答案的关系，发现答案区间 $(l,r)$ 可以由 $\forall i\in[l,r),(i,r)\text{modify}-i$，$\forall i\in(l,r],(l,i)\text{modify}-i$ 以及 $\forall i\in[l,r],(i,i)\text{modify}-i$ 相加而成。所以只需要分别维护这三者的贡献就好。修改和查询对于这三类值都是 $\Theta(\sqrt{n})$。记得同时要更改 $buc$ 数组，也是 $\Theta(\sqrt{n})$ 的。

[code](https://codeforces.com/contest/2043/submission/298486647)

---

## 作者：紊莫 (赞：2)

直接的 $O(n\sqrt{n})$ 做法。

---

首先对序列分块，设块长为 $B=\sqrt n$，考虑贡献来源：

1. 块内相等的对数。
2. 整块与散块间相等的对数。
3. 散块与散块间相等的对数。
4. 整块与整块间相等的对数。

前三种利用分块容易在 $O(\sqrt{n})$ 的时间内修改和查询。

对于最后一种，考虑设 $f_{i,j}$ 表示 $i$ 和 $j$ 两个块的相等对数，维护这个 $f$ 数组是简单的，等价于每次 $O(B)$ 个单点加。

查询等价于求解 $f$ 的矩形和，对于一个大小为 $n\times n$ 的矩形，可以在 $O(1)-O(n)$ 的时间内完成单点加和矩形查询。

对于行和列都再次分块，块长为 $K = n^{\frac{1}{4}}$。

这样对于一个矩形查询，有 $O(K)$ 个列整块，每个整块中通过对行分块在 $O(K)$ 的时间内求和。

维护 $f$ 总复杂度是 $O(1)-O(\sqrt{n})$ 的。

于是整个题的复杂度就是 $O(n\sqrt n)$ 的。

[一个粗略的实现。](https://codeforces.com/contest/2043/submission/310501401)

---

## 作者：cike_bilibili (赞：2)

做不同数对计数不如做相同数对计数，所以我们需要解决的问题就是强制在线单点修改和区间相等数对计数。

这东西放在树上的分治结构上是难以维护的，因为是下标和值域的两维限制，考虑分块。

询问转化为散块内部，散块对散块，散块对整块，整块内部和整块对整块的贡献，我们一一考虑。

散块内部和散块对散块的贡献可以开桶暴力统计，散块对整块我们可以维护一个前缀和数组 $pre_{b,i}$ 表示前 $b$ 个块有多少个 $i$，于是散块对整块的贡献就可以枚举散块的元素用中间整块的 $pre$ 快速计算了。

整块内部的贡献我们可以预处理，即直接记录答案，在修改的时候重构就行了。

整块对整块，我们可以去考虑直接预处理两块之间的答案，但不可取，我们是接受枚举整块的，所以我们考虑枚举每个整块计算对其他整块的贡献，尝试记录 $val_{i,j},(j>i)$ 表示第 $i$ 个块对 $j$ 块的贡献，这样我们枚举每一个整块将 $val$ 的前缀和统计起来就行了。

考虑如何去修改，设当前要将 $pos$ 这个位置的值改为 $v$，它所在块的编号是 $id$，$pre$ 数组可以直接枚举 $id$ 之后的块暴力修改，块内答案暴力重构，而 $val$ 数组较为特殊，对于 $val_{id,i}$，我们发现每个 $val_{id,i}$ 的增量都和块内为 $v$ 和 $a_{pos}$ 的数量有关，枚举所有 $i$ 修改，对于 $val_{i,id}$，增量与块 $i$ 中的 $val$ 和 $a_{pos}$ 有关，也可以暴力维护，应为询问时有前缀和查询，可以写一个树状数组。

这里的树状数组是 $O(\log (\sqrt n))$ 的，所以复杂度是 $O(m \sqrt n \log(\sqrt n))$，空间 $O(n\sqrt n)$。

---

## 作者：xiezheyuan (赞：2)

在考场上较为实用的在线带修莫队 $O((n+m)n^{2/3})$ 做法。

## 简要题意

给定一个长度为 $n$ 的序列 $a$，有 $m$ 次操作，支持：

- `1 p v` 令 $a_p\gets v$。
- `2 l r` 计算有多少个数对 $(i,j)$ 满足 $l\leq i\lt j\leq r$ 且 $a_i\neq a_j$。

**强制在线**，$1\leq n\leq 10^5,1\leq m\leq 3\times 10^3,1\leq a_i\leq n$。

时间限制 $8000\mathrm{ms}$，空间限制 $1024\mathrm{MiB}$。

## 思路

### Part 1

对于询问，令 $L=r-l+1$，则共有 $\frac{1}{2}(L^2-L)$ 个数对 $(i,j)$ 满足 $l\leq i\leq j\leq r$。假如计算出每种数的出现次数平方和 $k$，则就有 $\frac{k-L}{2}$ 个不满足题目要求的数对，两式相减，得到 $\frac{1}{2}(L^2-k)$。

$L$ 计算是容易的，所以问题是计算 $k$，也就是区间每种数出现次数的平方和。

- 如果允许离线、没有修改，则为 [P2709 小 B 的询问](https://www.luogu.com.cn/problem/P2709) 一题，可以直接用普通莫队算法解决。
- 如果允许离线，存在修改，则可以将普通莫队改为带修莫队，做法可以参考 [P1903 \[国家集训队\] 数颜色 / 维护队列](https://www.luogu.com.cn/problem/P1903)。

现在本题要求**强制在线**，导致我们难以使用一般的莫队算法解决，这时难道我们需要写正经的分块吗？不，我们考虑[莫队的在线化改造](https://www.luogu.com.cn/article/wdg1s2hw)。

### Part 2

先来思考普通莫队算法的在线化改造。

**将序列分为 $B$ 块**，在询问的时候，从若干个整块组成的区间出发，套用莫队双指针移动到询问区间，从而找到询问区间的答案，这就需要我们预处理以下信息：

- **所有整块区间的答案**。这需要 $O(nB)$ 的时间复杂度与空间复杂度。
- **所有整块区间的莫队中间状态**，在本题中，就是记录每个数出现次数的桶。如果全部记录下来，无论时空复杂度都是 $O(nB^2)$ 难以承受。不过这个出现次数的信息显然是可以差分的，因此可以改为记录**若干个整块组成的前缀的出现次数**，时空复杂度降为 $O(nB)$。

注意在双指针移动时，我们需要用一个桶来维护指针移动时出现次数信息的变化量，这个桶和初始整块区间信息加起来，作为真正的出现次数信息。这个桶的清空显然不能暴力清空，可以**用栈记录修改过的位置**。

于是时间复杂度为 $O(nB+m\cdot \frac{n}{B})$，根据均值不等式，取 $B=\sqrt{m}$ 时时间复杂度最优，为 $O(n\sqrt{m})$，该时间复杂度与普通莫队算法相同。

### Part 3

现在思考带修莫队算法的在线化改造。

这时难点主要在于在每次修改时，会影响到 $O(B^2)$ 个区间的答案，如果继续取 $B=\sqrt{m}$ 是难以承受的，不妨考虑带修莫队的思路，遇到修改先不真的更改，而是记录下来，等到后面在应用 / 撤销修改。

具体地，我们遇到修改时，**先修改莫队中间状态**（出现次数桶），然后**在询问的时候考虑应用修改**。

如何应用修改呢？貌似只能暴力了，那我们不妨真的暴力，**记录一下每个若干个整块构成的区间上次更新的时间戳，然后将这个区间的答案更新到当前时间戳**。

具体实现的话，由于桶已经是最新的了，所以更新答案必须**倒着更新**，用一个辅助桶来表示这次修改前的出现次数桶，然后计算答案。

接下来就是和 Part 2 一样的过程了。

分析一下复杂度，预处理同样是 $O(nB)$，单个询问不好考虑，考虑最多 $m$ 个修改，可以依次作用在 $B^2$ 个块中，故询问部分总时间复杂度为 $O(mB^2)$，修改部分总时间复杂度为 $O(m\cdot \frac{n}{B})$。

故总时间复杂度为 $O(nB+mB^2+m\cdot\frac{n}{B})$，通过平衡阶数法，取 $B=O(n^{1/3})$ 达到最优时间复杂度 $O(n^{4/3}+mn^{2/3})$，和带修莫队算法的时间复杂度相同。

### Part 4

我们需要卡常。

经过实践，取块长 $\frac{n}{B}=2300$ 表现较为平衡。另外，需要加入额外的判断，来让莫队时选取的若干个整块构成的初始区间最优，可以通过分类讨论左右端点来得到，具体可以看代码实现。

其他就没有什么非常厉害的卡常了，正常关闭同步流 + 火车头即可。

根据 [OI Wiki 的线索](https://oi-wiki.org/misc/modifiable-mo-algo/)，我们也许可以做一个伪在线，由于操作编号没有加密，通过求出操作的分布情况来调整超参数 $B$，这一点我没有实现，如果有同学实现了并取得了较好的成效，请私信我。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int N = 1e5 + 5, BK = 55, M = 3e5 + 5, K = 1e7 + 5;
using i64 = long long;
int n, m, a[N], cnt[BK][N], tim[BK][BK];
i64 ans[BK][BK];
int bl[BK], br[BK], bel[N];

struct tracer{
    int a[N];
    int vp[K], tot;
    int operator[](int x){ return a[x]; }
    void set(int pos, int x){ vp[++tot] = pos, a[pos] = x; }
    void add(int pos, int x = 1){ set(pos, a[pos] + x); }
    void roll(){ while(tot) a[vp[tot--]] = 0; }
} bkt;

void init(){
    int blk = max((int)pow(n, 2.0 / 3), 1);
    if(n > 5e4) blk = 2300;
    for(int i=1;i<=n/blk;i++) bl[i] = (i - 1) * blk + 1, br[i] = i * blk;
    br[n / blk] = n;
    for(int i=1;i<=n/blk;i++){
        for(int j=bl[i];j<=br[i];j++) bel[j] = i, bkt.add(a[j]);
        for(int j=1;j<=n;j++) cnt[i][j] = bkt[j];
    }
    for(int i=1;i<=bel[n];i++){
        bkt.roll();
        for(int j=i;j<=bel[n];j++){
            ans[i][j] = ans[i][j - 1];
            for(int k=bl[j];k<=br[j];k++){
                ans[i][j] += bkt[a[k]] << 1 | 1;
                bkt.add(a[k]);
            }
        }
    }
}

struct update_option{
    int pos, lst, val;
} upd[M];
int updt;

void update(int x, int y){
    if(a[x] == y) return;
    upd[++updt] = {x, a[x], y};
    for(int i=bel[x];i<=bel[n];i++) cnt[i][a[x]]--, cnt[i][y]++;
    a[x] = y;
}

int get(int l, int r, int p){ return cnt[r][p] - cnt[l - 1][p]; }

i64 ret;

void add(int p, int L, int R){
    ret += (bkt[p] + get(L, R, p)) << 1 | 1;
    bkt.add(p);
}

void del(int p, int L, int R){
    ret -= ((bkt[p] + get(L, R, p)) << 1) - 1;
    bkt.add(p, -1);
}

i64 query(int l, int r){
    int L = bl[bel[l]], R = br[bel[r]];
    int sl = bel[l], sr = bel[r];
    if(bel[l] != bel[n]){
        if(bl[bel[l] + 1] - l < l - bl[bel[l]]) sl = bel[l] + 1, L = bl[sl];
    }
    if(bel[r] != bel[1]){
        if(r - br[bel[r] - 1] < br[bel[r]] - r){
            if(sl <= (bel[r] - 1)) sr = bel[r] - 1, R = br[sr];
        }
    }
    bkt.roll();
    for(int i=updt;i>tim[sl][sr];i--){
        auto [pos, lst, val] = upd[i];
        if(pos < L || pos > R) continue;
        bkt.add(lst), bkt.add(val, -1);
        ans[sl][sr] -= ((get(sl, sr, lst) + bkt[lst]) << 1) - 1;
        ans[sl][sr] += (get(sl, sr, val) + bkt[val]) << 1 | 1;
    }
    tim[sl][sr] = updt;
    bkt.roll();
    ret = ans[sl][sr];
    while(L > l) add(a[--L], sl, sr);
    while(R < r) add(a[++R], sl, sr);
    while(L < l) del(a[L++], sl, sr);
    while(R > r) del(a[R--], sl, sr);
    return ret;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    init(); i64 lastans = 0;
    cin >> m;
    // cerr << (1.0 * clock() / CLOCKS_PER_SEC) << ' ' << n << ' ' << m << '\n';
    while(m--){
        int op, x, y; cin >> op >> x >> y;
        x = (x + lastans) % n + 1;
        y = (y + lastans) % n + 1;
        if(op == 1) update(x, y);
        else{
            if(x > y) swap(x, y);
            i64 ret = query(x, y);
            cout << (lastans = ((1ll * (y - x + 1) * (y - x + 1) - ret) >> 1));
            cout << ' ';
            assert(lastans >= 0);
        }
        // if(m % 10000 == 0) cerr << m << ' ' << (1.0 * clock() / CLOCKS_PER_SEC) << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：lfxxx (赞：2)

查询只要知道区间每种颜色出现次数平方和就行了。

离线可以直接带修莫队，可惜这里要强制在线。

仿照在线莫队，以 $B$ 为块长将序列分为 $\frac{n}{B}$ 块，对于块构成的 $\frac{n^2}{B^2}$ 个区间预处理出答案，对于块构成的 $\frac{n}{B}$ 个前缀预处理出一个出现次数的桶，查询时假若包含了整块 $[L,R]$，那么先把整块的答案算进去，然后将散块内的数一个个加进去，加入的过程中只需要知道当前每种数的出现次数就可以知道答案的变化量，考虑将加入的散块中的数存在一个桶中，将其与块区间 $[L,R]$ 内数出现次数的信息合并即可（由于出现次数可差分，用两个块构成的前缀信息减就行），这个部分复杂度 $O(q \times B)$，至于修改你发现所有预处理的信息都可以在总共 $O(q \times \frac{n^2}{B^2})$ 的时间内重新计算，于是令 $B = n^{\frac{2}{3}}$ 即可做到 $O(q \times n^{\frac{2}{3}})$。

需要注意若干细节和常数。

[代码](https://codeforces.com/contest/2043/submission/298431414)

---

## 作者：Tx_Lcy (赞：0)

贡献一个简单的做法，代码只有 1.5k 左右。

## 思路

首先我们显然要容斥，变成计算 $a_i=a_j$ 的对数。

同时，这个数据范围和时限显然不是 $\text{polylog}$ 做法，因此考虑分块。

散块与散块，散块与整块的答案是容易处理的，扫一遍即可。主要问题在于处理若干个连续的整块的答案。

我们考虑处理出 $val_{i,j}$ 表示块 $i$ 与块 $i+1 \sim j$ 之间的答案，那么查询块 $l$ 至块 $r$ 的贡献就直接枚举每个块 $i$，把 $val_{i,r}$ 加起来，再加上每个块内部的答案即可。

对于块 $p$ 的修改，我们考虑 $val_{i,j}$ 会怎么变，我们发现对于每个 $i<p$，我们会将 $val_{i,j} \ (j \ge p)$ 加上一个相同的值，也就是说，块 $p$ 对 $val_{i,j} \ (j \ge p)$ 的贡献只与 $i$ 的值有关。

所以我们再记一个 $tag_{i,j}$ 表示块 $i$ 对块 $j \sim i$ 的 $val$ 数组的贡献，同时我们把每个块内部的贡献也记在 $tag$ 数组上。

这样就能快速维护修改并快速查询了，代码极其好写，时间复杂度 $\Theta((n+q)\sqrt n)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for (int i=j;i<=k;++i)
#define per(i,j,k) for (int i=j;i>=k;--i)
int const N=1e5+10,B=320;
int n,a[N],q,bel[N],L[N],R[N],cnt[N],val[B][B],tag[B][B],tong[N][B];
//tong[val][id] -> val 在块 1~id 中的出现次数
//val[i][j] -> 块 i 与块 i+1~j 之间的贡献
//tag[i][j] -> 块 i 的修改对块 j~i 产生的影响
inline void upd(int x,int y,int o){
	a[x]=y;
	rep(i,1,bel[x]) tag[bel[x]][i]+=(tong[y][bel[x]]-tong[y][i-1]-(o==-1))*o;
	rep(i,bel[x]+1,bel[n]) val[bel[x]][i]+=(tong[y][i]-tong[y][bel[x]])*o;
	rep(i,bel[x],bel[n]) tong[y][i]+=o;
}
inline void solve(){
	cin>>n;
	rep(i,1,n) cin>>a[i],bel[i]=(i-1)/B+1;
	rep(i,1,n){
		if (!L[bel[i]]) L[bel[i]]=i;
		R[bel[i]]=i;
	}
	rep(i,1,n) upd(i,a[i],1);
	cin>>q;
	int la=0;
	while (q--){
		int op;cin>>op;
		switch (op){
			case 1:{
				int p,x;cin>>p>>x;
				p=(p+la)%n+1,x=(x+la)%n+1;
				upd(p,a[p],-1),a[p]=x,upd(p,a[p],1);
				break;
			}
			case 2:{
				int l,r;cin>>l>>r;
				l=(l+la)%n+1,r=(r+la)%n+1;
				if (l>r) swap(l,r);
				la=(r-l+1)*(r-l)/2;
				rep(i,bel[l]+1,bel[r]-1)
					la-=tag[i][bel[l]+1]+val[i][bel[r]-1];
				if (bel[l]==bel[r]){
					rep(i,l,r) la-=cnt[a[i]]++;
					rep(i,l,r) cnt[a[i]]=0;
				}else{
					rep(i,l,R[bel[l]]) la-=tong[a[i]][bel[r]-1]-tong[a[i]][bel[l]]+cnt[a[i]]++;
					rep(i,L[bel[r]],r) la-=tong[a[i]][bel[r]-1]-tong[a[i]][bel[l]]+cnt[a[i]]++;
					rep(i,l,R[bel[l]]) cnt[a[i]]=0;
					rep(i,L[bel[r]],r) cnt[a[i]]=0;
				}
				cout<<la<<' ';
				break;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

