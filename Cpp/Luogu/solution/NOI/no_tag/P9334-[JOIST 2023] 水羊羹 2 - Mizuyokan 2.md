# [JOIST 2023] 水羊羹 2 / Mizuyokan 2

## 题目描述

水羊羹是一种日本甜点，是用红豆糊和琼脂制成的。它的做法是先将红豆糊与琼脂混合后搅拌均匀，然后倒入长方形模具中，等待它们凝固成型。

现在，JOI 君有了一个制作水羊羹的机器。他可以用该机器制作一块长度为 $d_1+d_2+⋯+d_N$ 的水羊羹。JOI 君可以让这块水羊羹沿着 $N−1$ 条垂直的切割线（不包括两端）分割成 $N$ 段长度为 $d_1,d_2,…,d_N$ 的竖条形状的小片。

JOI 君希望在有 $Q$ 场茶会上送给尽可能多的朋友水羊羹。每场茶会对应 $(X_j,Y_j,A_j,B_j)$，其中：

+ JOI 君会更新机器上第 $X_j$ 条切割线的位置为 $Y_j$，以此生成一个新的水羊羹。

+ JOI 君挑选出原水羊羹中从第 $A_j$ 条切割线到第 $B_j$ 条切割线之间的部分，作为茶会中的水羊羹。剩余部分被他自己吃掉。

+ JOI 君需将所选小片沿着一些切割线分割成若干段让朋友品尝。在这一过程中应当满足如下条件：如果按顺序排列，分割后每个小片长度的大小应当是一个“之”字形，即连续两个片段长度先递增再递减，亦或者先递减再递增。

具体地，令 $(x_1,x_2,…,x_m)$ 是分割后小片长度组成的序列，$(x_1,x_2,…,x_m)$ 是“之”字形当且仅当它满足以下一个或两个条件：

+ 对于所有 $k=1,2,…,m−1$，如果 $k$ 为奇数，则 $x_k<x_{k+1}$，否则 $x_k>x_{k+1}$。

+ 对于所有 $k=1,2,…,m−1$，如果 $k$ 为奇数，则 $x_k>x_{k+1}$，否则 $x_k<x_{k+1}$。

因为 JOI 君希望给尽可能多的朋友品尝到水羊羹，所以他希望供品的小片数量最大化。

请完成一个程序，它会读入水羊羹机器的参数和茶会计划，并对每一场茶会输出可供品尝的小片的最大数量。请注意，在任务的限制下，可以总是找到一种合适的方法将所选小片分割成符合“之”字形条件的若干小片。

## 说明/提示

对于所有输入数据，满足：

- $1\le N \le 2.5\times 10^5$
- $1\le L_i \le 10^9$
- $1\le Q\le5\times10^4$
- $1\le X_j\le N,1\le Y_j\le 10^9$
- $0\le A_j < B_j \le N$

详细子任务附加限制及分值如下表所示。

|子任务编号|附加限制|分值 |
|:---:|:--------:|:-:|
|$1$|$N\le 200,Q\le 10$| $6$|
|$2$|$N\le 2\space000,Q\le 10$| $9$|
|$3$|$Q\le10$|$13$|
|$4$|$Y_j=L_{X_j}$|$32$|
|$5$|$L_i,Y_j\le 1.2\times10^5$|$29$|
|$6$|无附加限制|$11$|

## 样例 #1

### 输入

```
6
5 6 8 7 4 9
1
6 9 0 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
6 2 3 6
3
3 2 1 3
4 5 1 4
1 1 0 4
```

### 输出

```
1
2
3
```

# 题解

## 作者：APJifengc (赞：6)

首先大力 DP 就是 $O(n^3)$，注意到任意一种方案把小段缩到长度为 $1$ 仍然满足条件，于是我们可以只记录每次选的小段的位置，这样就能 $O(n^2)$ 了，且容易优化到 $O(n \log n)$，但是这个做法没有什么拓展空间。

考虑分析大段的性质。首先大段有一个显然的必要条件，就是大段的和一定比段的左右两个数大，即 $\sum_{i=l}^r a_i > \max(a_{l-1}, a_{r+1})$，我们称满足这个条件的段为好段，而最优方案下小段长度为 $1$，于是上述条件就是一个充分条件。但是小段长度不一定等于 $1$，不过我们可以猜测，小段长度不等于 $1$ 时，上述条件仍然是充分条件。

证明很简单，考虑左右两个段 $[l_1, r_1], [l_2, r_2]$，如果有 $a_{r_1 + 1} < a_{l_2 - 1}$，那么将 $l_2$ 拓展到 $r_1 + 2$ 显然仍然满足条件，否则将 $r_1$ 拓展到 $l_2 - 2$ 仍然满足条件。对于最靠左与最靠右的段，我们假设最靠左的段 $[l, r]$，右边同理，那么如果 $a_1 < a_{l - 1}$，那么把 $l$ 拓展到 $2$ 显然符合条件，否则可以在左面新加一段 $[1, l - 1]$，这样也能够符合条件。也就是说，任意一种好段的划分，都可以找到一种合法方案的划分，那么我们只需要考虑找出最大的好段划分即可，这显然是等于答案的。而这个问题有很简单的贪心方式解决，对于右端点从左往右扫，如果左端点大于等于上一个右端点 $+2$ 那么就选这个段。而这个做法就很好拓展了。

那么考虑设 $f(r)$ 为以 $r$ 为右端点的最小的好段的左端点，设 $nxt(r)$ 为最小的 $k$ 满足 $f(k) \ge r + 2$，答案就是从 $[l, r]$ 中某个点开始跳 $nxt$，跳到区间外为止，最多能跳多少个点。需要特殊讨论一下开头结尾是不是长为 $1$ 的小段，这都比较简单。那么静态区间询问就可以做了。

考虑如何修改。每次修改看起来会改变很多的 $f(r)$，并不好修改，但是可以证明 $nxt(r) - r = O(\log V)$，考虑从右边某个点开始向左右拓展，注意到向一边拓展时，如果 $a_{l - 1} < \sum a_i$，那么此时就可以停止拓展，否则有 $a_{l - 1} \ge \sum a_i$，注意到拓展后 $\sum a_i$ 会翻倍，于是每次这样拓展都会使得区间和翻倍，那么显然翻倍 $O(\log V)$ 次后就一定会满足条件了，所以说这样的拓展向左向右都最多进行 $O(\log V)$ 次，于是就可以证明 $nxt(r) - r = O(\log V)$ 了。

那么也就是说只有 $O(\log V)$ 个 $nxt(r)$ 会发生改变，于是我们只需要每次更新这几个 $nxt(r)$ 即可。然后维护跳链的信息可以使用 LCT 做到 $O(n \log n \log V)$，不过这比较蠢，由于 $nxt(r) - r = O(\log V)$，也就是说每次只会跳 $O(\log V)$，于是我们可以直接用线段树维护一个区间内从前 $O(\log V)$ 个为止开始跳，跳到区间外的第一个点是啥，然后这个东西是容易合并的，单次 pushup 是 $O(\log V)$ 的，而我们修改连续的 $O(\log V)$ 个值，所以只会更新 $O(\log n + \log V)$ 个点，于是线段树维护的复杂度就是 $O(n \log V (\log n + \log V))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 250005, LOG = 65;
int n, q, a[MAXN];
int nxt[MAXN];
struct SegmentTree {
    struct Node {
        int l, r;
        pair<int, int> a[LOG + 1];
        pair<int, int> jmp(pair<int, int> q) {
            auto [i, v] = q;
            auto p = i <= min(r - l + 1, LOG) ? a[i] : make_pair(i - (r - l + 1), 0);
            p.second += v;
            return p;
        }
        Node operator+(Node b) {
            Node c; c.l = l, c.r = b.r;
            for (int i = 1; i <= min(c.r - c.l + 1, LOG); i++) c.a[i] = b.jmp(jmp(make_pair(i, 0)));
            return c;
        }
    } t[MAXN << 2];
#define lc (i << 1)
#define rc (i << 1 | 1)
    void update(int a, int b, int i = 1, int l = 0, int r = n) {
        if (l == r) {
            t[i].l = t[i].r = l;
            t[i].a[1] = { nxt[l] - l, 1 };
            return;
        }
        int mid = (l + r) >> 1;
        if (a <= mid) update(a, b, lc, l, mid);
        if (b > mid) update(a, b, rc, mid + 1, r);
        t[i] = t[lc] + t[rc];
    }
    Node query(int a, int b, int i = 1, int l = 0, int r = n) {
        if (a <= l && r <= b) return t[i];
        int mid = (l + r) >> 1;
        if (b <= mid) return query(a, b, lc, l, mid);
        if (a > mid) return query(a, b, rc, mid + 1, r);
        return query(a, b, lc, l, mid) + query(a, b, rc, mid + 1, r);
    }
} st;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    a[0] = a[n + 1] = -1;
    nxt[n + 1] = n + 1;
    int cc = 0;
    auto solve = [&](int l, int r) {
        for (int i = r; i >= l; i--) {
            nxt[i] = nxt[i + 1];
            long long sum = 0;
            for (int j = i + 2; j <= min(n, i + LOG); j++) {
                sum += a[j];
                cc++;
                if (sum > a[i + 1] && sum > a[j + 1]) {
                    nxt[i] = min(nxt[i], j);
                    break;
                }
            }
        }
        st.update(l, r);
    };
    solve(0, n);
    scanf("%d", &q);
    while (q--) {
        {
            int x, y; scanf("%d%d", &x, &y);
            a[x] = y;
            solve(max(0, x - LOG), x);
        }
        {
            int l, r; scanf("%d%d", &l, &r); l++;
            int ans = 1;
            int pre = r, suf = l;
            long long sum = 0;
            for (int i = l; i < r; i++) {
                sum += a[i];
                if (a[i + 1] < sum) {
                    pre = i;
                    break;
                }
            }
            sum = 0;
            for (int i = r; i > l; i--) {
                sum += a[i];
                if (a[i - 1] < sum) {
                    suf = i;
                    break;
                }
            }
            auto query = [&](int l, int r) {
                if (l > r && nxt[l - 1] >= r) return INT_MIN;                
                return 2 * (st.query(l - 1, r - 1).a[1].second - 1) + 1;
            };
            ans = max(ans, query(l, r));
            ans = max(ans, query(pre + 1, r) + 1);
            ans = max(ans, query(l, suf - 1) + 1);
            ans = max(ans, query(pre + 1, suf - 1) + 2);
            printf("%d\n", ans);
        }
    }
    return 0;
}
```


---

## 作者：Wonder_Fish (赞：4)

提供另一种维护方式：使用分块，时间复杂度 $O(n\sqrt n)$，但是常数小。

---

### 题意

给定一个序列，每次询问单点修改，再求把区间 $[l,r]$ 划分为若干段使每段的和构成的序列是交替的。

---

### 性质分析

这部分另外的题解已经讲得很详细了，但为了形成一篇完整的题解，就在这略提几句。

首先发现在最优方案下，一定是划分成一些大段和一些长度为 1 的小段，因为如果小段长度 $>1$，把剩下的分到大段一定不劣。

在最优方案下，合法大段的充要条件是 $\sum_{i=l}^r a_i > a_{l-1}$ 且 $>a_{r+1}$。注意到在不保证最优条件下，这样划分也可以得到正确段数。考虑如下证明：假设一个长度 $>1$ 的小段 $[l,r]$，左侧有大段 $[l_1,r_1]$，右侧大段 $[l_2,r_2]$，若 $a_l<a_r$，那么把右侧变为 $[l+1,r_2]$ 依然合法，反之同理拓展左边；若 $[l,r]$ 在最左侧，若 $a_1<a_{l_2-1}$，那么把 $l_2$ 移动到 $2$，否则新增一段 $[1,l_2-2]$，在最右边同理对称一下。

成满足上述条件的段为好段，发现找好段划分满足最优条件下充要条件，一定可以找出不劣于最优解的答案，且已经证明这样求出的答案不会出现使答案偏大的不合法情况，于是只要计算好段划分即可。

现在的问题变为了，有一些区间 $[l,r]$，要选出一些区间使它们无交，最多选出多少个区间。可以贪心，按照右端点从小到大，尽量选择右端点小的。设 $nxt_i$ 表示若上一个好段结尾为 $i$，那下一个可以接在它后面的好段的最小右端点。于是我们会 $O(n^2)$ 了，暴力修改 $nxt$，然后询问时候暴力计算跳了多少次 $nxt$。需要稍微讨论一下开头结尾是否存在小段，这也是简单的，因为若不存在小段，根据贪心思想第一个大段也被确定了。

感觉每次只修改一位，把整个 $nxt$ 重算一遍过于浪费。发现有重要性质：$nxt_i - i$ 为 $O(\log V)$ 级别。考虑从下个好段中任意一点向左右拓展，每拓展一次需满足当前和 $<$ 拓展的位置，也就是说和至少翻倍，因此 $O(\log V)$ 次拓展后和大于任意一个相邻的数。有这个性质之后，每次修改只会影响 $O(\log V)$ 个位置的 $nxt$。

~~好像不是略提几句了~~

---

### 快速跳 $nxt$

可以 LCT，但那太蠢了，~~而且我不会~~。也可以线段树，是 $\log n \log V$ 的，但是常数不小而且不是很好写。

注意到这部分和 [P3203](https://www.luogu.com.cn/problem/P3203) 非常像。借鉴那题的分块，维护 $t_i$ 和 $c_i$ 表示从当前块内一点第一次跳到块外的位置和跳跃次数。

修改的时候，假设 $nxt_i$ 发生变动的区间为 $[l,r]$，首先修改 $[l,r]$ 内的 $t$ 和 $c$，然后修改剩下的和 $l$ 在一个块内的位置的 $t$ 和 $c$，修改可以递推，单个位置 $O(1)$，这部分最多修改 $\log V + \sqrt n$ 和点。

询问时候先跳 $t$，再跳 $nxt$，两段跳跃次数都不超过 $\sqrt n$。

因此最后的复杂度是 $O(n \log^2 V + n\sqrt n)$，稍劣于线段树，但是常数小啊，一发交上去是目前的最优解。

---

### Code

代码不长，但是有一些细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define mod 998244353
#define N 250010
#define int long long
#define szi sizeof(int)
#define il inline
int n,q,sq,a[N],x,y,l,ll,r,rr,nxt[N],p[N],t[N],c[N],ans;
il void cmax(int &x,int y){x=(x>y)?x:y;return ;}
il void cmin(int &x,int y){x=(x<y)?x:y;return ;}
il void upd(int l,int r){
    for(int i=r;i>=l;--i){
        nxt[i]=nxt[i+1];
        for(int j=i+2,s=a[i+2];j<=n&&j-i<=65;s+=a[++j])
            if(s>a[i+1]&&s>a[j+1]){cmin(nxt[i],j);break;}
        if(p[nxt[i]]==p[i]) t[i]=t[nxt[i]],c[i]=c[nxt[i]]+2;
        else t[i]=nxt[i],c[i]=2;
    }
    for(int i=l-1;i>=0&&p[i]==p[l];--i){
        if(p[nxt[i]]==p[i]) t[i]=t[nxt[i]],c[i]=c[nxt[i]]+2;
        else t[i]=nxt[i],c[i]=2;
    }
    return ;
}
il int calc(int l,int r){
    int res=0; --l; if(l>=r) return -inf;
    while(t[l]<r) res+=c[l],l=t[l]; while(nxt[l]<r) res+=2,l=nxt[l];
    return res;
}
signed main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    scanf("%lld",&n),sq=sqrt(n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=0;i<=n;++i) p[i]=i/sq+1; p[n+1]=p[n]+1;
    nxt[n+1]=n+1,upd(0,n),scanf("%lld",&q);
    while(q--){
        scanf("%lld%lld%lld%lld",&x,&y,&l,&r),++l,a[x]=y;
        upd(max(0ll,x-65),x-1),ans=1,ll=r+1,rr=l-1;
        for(int i=l,s=a[l];i<r;s+=a[++i]) if(s>a[i+1]){ll=i+1;break;}
        for(int i=r,s=a[r];i>l;s+=a[--i]) if(s>a[i-1]){rr=i-1;break;}
        cmax(ans,calc(l,r)+1),cmax(ans,calc(ll,r)+2);
        cmax(ans,calc(l,rr)+2),cmax(ans,calc(ll,rr)+3);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Iniaugoty (赞：4)

注意到最优策略中，“谷”一定是单个数字构成的，否则把多余的分到“峰”里一定不劣。DP 可以期望得分 $6/15/28$，不多赘述。~~然后不会了。~~

发现 $[l, r]$ 构成“峰”需要满足一个条件，$\sum _ {i = l} ^ {r} a _ i > \max(a _ {l - 1}, a _ {r + 1})$。必要性是显然的。但是他可能不是充分的。但是考虑可以把它当成充分的，总能从不合法方案中调整出合法方案~~我没懂~~。

设 $f _ i$ 为以 $i$ 为右端点的满足条件的“峰”的最大左端点（当然这个可能不存在），设 $g _ i$ 为最小的 $j$ 使得 $f _ {j} \ge i + 2$。不难发现，若当前取了 $i$ 作为某个“峰”的右端点，下一步一定是以 $i + 1$ 为一个“谷”，再以 $[i + 2, j]$ 为下一个“峰”最优。

那么问题就变成了一个不断跳 $g$，要从区间左端点跳到右端点的问题。~~然后有一车边界~~。我会分块！考虑[弹飞绵羊](https://www.luogu.com.cn/problem/P3203)。对于每一个点，维护跳一步到的位置、第一次跳出块到的位置及其跳的次数。

考虑修改 $x$。注意到只有 $[x - 2 \log V, x]$ 的 $g$ 会有变化，因为“峰”向外拓展的过程中一直在翻倍，单个 $g _ {i} - i$ 不超过 $2 \log V$。先暴力地把有变化的 $g$ 求出来。然后将这些位置所在的 $O(1)$ 个块暴力重构，只需要取一个 $> 2 \log V$ 的块长就最多只用重构两个块了（你发现 $\sqrt n$ 就满足这个条件）。

考虑查询 $[l, r]$。先使用“第一次跳出块到的位置及其跳的次数”跳到 $r$ 所在块，然后使用“跳一步到的位置”跳过 $r$。需要讨论一下 $[l, r]$ 边界上是否为“谷”的问题。

取 $\sqrt n$ 为块长，则时间复杂度为 $O(q (\sqrt n + \log ^ 2 V))$，常数很小，跑得飞快。实际上块长略长一些更快，因为修改的常数比查询要小。使用 $1000$ 作为块长，获得了（截至本文发表前的）[洛谷](/record/207033028)和 [LOJ](https://loj.ac/s/2278918) 上的最优解。使用 $500, 400, 250, 200$ 作为块长，分别获得了洛谷上的[次优解](/record/207031560)和三四五优解。

代码比较短，不到 2K，但是细节很多（？）。~~我是和 OJ 交互了半小时随机改出来的，我也搞不懂这些细节。~~

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define dF(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> pii;
const int N = 2.5e5 + 5;
const int k = 1e3, K = N / k + 5;
const int lg = 70;

int n, q, a[N];

int st[K], ed[K], id[N], nxt[N], to[N], cnt[N];
void Init(int l, int r) {
  dF(i, r, l) {
    nxt[i] = nxt[i + 1]; LL now = 0;
    F(j, i + 2, min(n, i + lg)) {
      now += a[j];
      if (now > a[i + 1] && now > a[j + 1])
        { nxt[i] = min(nxt[i], j); break; }
    }
  }
}
void Update(int l, int r) {
  dF(i, r, l)
    if (nxt[i] > ed[id[i]]) to[i] = nxt[i], cnt[i] = 1;
    else to[i] = to[nxt[i]], cnt[i] = cnt[nxt[i]] + 1;
}
int Get(int x, int y) {
  int res = 0;
  while (id[x] < id[y]) res += cnt[x], x = to[x];
  while (x < y) ++res, x = nxt[x];
  return res;
}
int Query(int l, int r) {
  if (l > r && nxt[l - 1] >= r) return -N;
  return 2 * Get(l - 1, r) - 1;
}

int main() {
  // freopen("zyq.in", "r", stdin);
  // freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n, a[0] = -N;
  F(i, 1, n) cin >> a[i];
  F(i, 1, n) id[i] = (i - 1) / k + 1;
  F(i, 1, id[n]) st[i] = ed[i - 1] + 1, ed[i] = ed[i - 1] + k;
  ed[id[n]] = n;
  nxt[n + 1] = n + 1, Init(0, n), Update(0, n);
  cin >> q;
  while (q--) {
    int x, y, l, r; cin >> x >> y >> l >> r, a[x] = y, ++l;
    Init(max(x - lg, 1), x);
    Update(st[id[max(x - lg, 0)]], ed[id[x]]);
    int p = -1, q = -1, ans = Query(l, r); LL sum = 0;
    F(i, l, r - 1) { sum += a[i]; if (sum > a[i + 1]) { p = i; break; } }
    if (p > 0) ans = max(ans, Query(p + 1, r) + 1); sum = 0;
    dF(i, r, l + 1) { sum += a[i]; if (sum > a[i - 1]) { q = i; break; } }
    if (q > 0) ans = max(ans, Query(l, q - 1) + 1);
    if (p > 0 && q > 0) ans = max(ans, Query(p + 1, q - 1) + 2);
    cout << ans << "\n";
  }
  return 0;
}
```

---

## 作者：eastcloud (赞：3)

一句话题意：给定一个序列，单点修改，区间询问把这个区间划分成若干区间和交替的子段的最大划分段数。

先考虑不带修改且询问一整个区间怎么做，我们称划分中比旁边大的段叫大段，否则叫小段，朴素 dp 是 $O(n^3)$ 的。太蠢了，这个题性质很好，尝试找点性质。

一个非常容易想到的性质是一定存在一组最优解小段长度为 1，否则你可以直接拆出来一个数归到左边或者右边。这样显然不劣。而对于一个大段似乎也存在类似的性质，因为如果大段太长你会发现你很有可能找到一个位置断开这整个段。

尝试更精确地分析一下这种情况什么时候会发生，对于大段里的点 $i$，我们能从这个位置分裂当且仅当它小于对应前缀和和后缀和，任意一个条件不满足都不行，但是你注意到如果不满足这个条件，前缀和必然至少翻倍，换言之，对于前缀来说最多只会有 $O(\log V)$ 个这样的节点。

对于后缀来说也是这样的，于是两部分拼起来也只有 $O(\log V)$ 个节点不能断，于是你会发现最优解里大段长度就是 $O(\log V)$ 的。

加上这俩性质就可以快速 dp 了。由于 dp 的本质是每次拼上一段，考虑这个过程能不能用一些手法加速。由于这个拼接的性质很好，考虑贪心，每次尝试拼上一个小段和一个大段，我们贪心地选右端点尽量左的合法大段，但是你注意到此时可能评上的小段不是目前的右端点，不过这也没关系，因为我们总能把目前的大段拉过去或者后面的大段拉过来，简单分讨一下大小关系即可证明。

于是你可以预处理每个点下次跳到的是哪个点并用数据结构加速这个过程，注意一些边界的细节，可能比较繁琐，单点修改也是好做的，因为段长是 $O(\log V)$ 的，因此你可以暴力更新前后 $O(\log V)$ 个点，线段树简单维护一下即可，时间复杂度 $O(n \log V \log n)$。


```cpp

#include<bits/stdc++.h>

#define ll long long
#define pi pair<int,int>
#define vi vector<ll>
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mset(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ary array
#define eb emplace_back
#define IL inline
#define For(i,j,k) for(ll i=(j);i<=(k);i++)
#define Fol(i,k,j) for(ll i=(k);i>=(j);i--)

using namespace std;

#define B 67
#define N 300005

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,putchar('-'); 
    if(x/10)write(x/10);
    putchar(x%10+'0');
}

void debug(auto &&...x){
    ((cerr<<x<<' '),...);
    cerr<<'\n';
}

ll nex[N],a[N],n;

void refresh(ll i){
    ll sum=0;
    For(j,i+2,n){
        sum+=a[j];
        if(sum>a[i+1] && sum>a[j+1]){nex[i]=j;break;}
    }
}

struct info{
    int l,r;
    pi f[B+2];
    info(ll lef=0,ll ri=0){l=lef;r=ri;f[1]=mp(lef,0);}
};
info merge(info x,info y){
    ll l=x.l,r=y.r;
    For(i,1,min(x.r-x.l+1,B)){
        ll pos=x.f[i].fi;
        if(nex[pos]<=r){
            pos=nex[pos];x.f[i].se+=2;
            x.f[i].fi=y.f[pos-y.l+1].fi;x.f[i].se+=y.f[pos-y.l+1].se;
        }
    }
    For(i,y.l,y.r){
        if(i-x.l+1>B)break;
        swap(x.f[i-x.l+1],y.f[i-y.l+1]);
    }
    x.r=y.r;
    return x;
}

struct seg{
    info v[N<<2];
    #define ls (x<<1)
    #define rs ((x<<1)|1)
    #define mid ((l+r)>>1)
    void upd(ll x,ll L,ll R,ll l=0,ll r=n){
        if(l==r)return v[x].l=l,v[x].r=r,v[x].f[1]=mp(l,0),void();
        if(L<=mid)upd(ls,L,R,l,mid);
        if(R>mid)upd(rs,L,R,mid+1,r);v[x]=merge(v[ls],v[rs]);
    }
    info ask(ll x,ll L,ll R,ll l=0,ll r=n){
        if(l>=L && r<=R)return v[x];
        if(L<=mid && R>mid)return merge(ask(ls,L,R,l,mid),ask(rs,L,R,mid+1,r));
        else if(L<=mid)return ask(ls,L,R,l,mid);
        return ask(rs,L,R,mid+1,r);
    }
}T;

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif

    n=read();
    For(i,1,n)a[i]=read();a[n+1]=-1;
    For(i,0,n)nex[i]=n+1;nex[n+1]=n+1;
    For(i,0,n-2)refresh(i);
    Fol(i,n,0)nex[i]=min(nex[i],nex[i+1]);
    ll q=read();T.upd(1,0,n);
    For(i,1,q){
        ll x=read(),val=read(),l=read(),r=read();a[x]=val;l++;
        Fol(j,min(x,n-2),max(0ll,x-B))nex[j]=n+1,refresh(j),nex[j]=min(nex[j],nex[j+1]);
        T.upd(1,max(0ll,x-B),x);
        int ans=1;
        ll sum=0,beg=0,ed=0;
        For(j,l,r-1){
            sum+=a[j];
            if(sum>a[j+1]){beg=j;break;}
        }
        sum=0;
        Fol(j,r,l+1){
            sum+=a[j];
            if(sum>a[j-1]){ed=j-2;break;}
        }
        ans=max(ans,T.ask(1,l-1,r-1).f[1].se+1);
        if(beg && beg<=r-1)ans=max(ans,T.ask(1,beg,r-1).f[1].se+2);
        if(ed && l-1<=ed)ans=max(ans,T.ask(1,l-1,ed).f[1].se+2);
        if(beg && ed && beg<=ed)ans=max(ans,T.ask(1,beg,ed).f[1].se+3);
        write(ans);putchar('\n');
    }

    return 0;
}

```

---

