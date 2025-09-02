# Hopping Around the Array

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/e51ba52831aa2bdc46f5ded7e75759c71a41f8c8.png)William really wants to get a pet. Since his childhood he dreamt about getting a pet grasshopper. William is being very responsible about choosing his pet, so he wants to set up a trial for the grasshopper!

The trial takes place on an array $ a $ of length $ n $ , which defines lengths of hops for each of $ n $ cells. A grasshopper can hop around the sells according to the following rule: from a cell with index $ i $ it can jump to any cell with indices from $ i $ to $ i+a_i $ inclusive.

Let's call the  $ k $ -grasshopper value of some array the smallest number of hops it would take a grasshopper to hop from the first cell to the last, but before starting you can select no more than $ k $ cells and remove them from the array. When a cell is removed all other cells are renumbered but the values of $ a_i $ for each cell remains the same. During this the first and the last cells may not be removed.

It is required to process $ q $ queries of the following format: you are given three numbers $ l $ , $ r $ , $ k $ . You are required to find the $ k $ -grasshopper value for an array, which is a subarray of the array $ a $ with elements from $ l $ to $ r $ inclusive.

## 说明/提示

For the second query the process occurs like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/c1ccc3788dc1fede7feb02bdd9497a50772396e2.png)

For the third query the process occurs like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/0e6c1b078b934e632312b366706afe7addccd69f.png)

## 样例 #1

### 输入

```
9 5
1 1 2 1 3 1 2 1 1
1 1 0
2 5 1
5 9 1
2 8 2
1 9 4```

### 输出

```
0
2
1
2
2```

# 题解

## 作者：Chy12321 (赞：10)

首先考虑 $k = 0$ 的情况。

贪心，最后一步之前每个 $i$ 只会跳到 $j \in [i, i + a_i]$ 且 $j + a_j$ 最大的点 $j$，这个信息或许可以线性处理？但是我没脑子，我用线段树维护，时间复杂度 $\mathcal O(n \log n)$。

然后就可以倍增了，时间复杂度 $\mathcal O(n \log n)$。

加入 $k \ne 0$ 的情况，设 $f(i, j, k)$ 表示从 $i$ 出发跳 $2^j$ 步，删了 $k$ 个点的最远可达位置。

同时又注意到删点其实相当于扩大可达范围，也就是在跳一步的情况下，删 $k$ 个点后可达范围从 $[i, i + a_i]$ 变成了 $[i, i + a_i + k]$。

于是就很好转移了，时间允许枚举每个状态的 $k$ 暴力做转移，时间复杂度 $\mathcal O(nk^2 \log n)$。

倍增的一大特色是统计答案和状态转移特像，也是直接暴力做就好。

- 若 $l = r$，则答案为 $0$。
- 若 $r \in [l, l + a_l + k]$，则答案为 $1$。
- 否则开始倍增，第 $2^j$ 步能跳当且仅当无论如何都不会使最大可达范围覆盖到 $r$，答案即为步数 $+ 2$。

时间复杂度 $\mathcal O(qk^2 \log n)$。

总时间复杂度就是 $\mathcal O[(n + q)k^2 \log n]$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e4 + 10, LN = 16, K = 31;

int n, q, a[N];

struct Node {
    int w, id;

    Node() {}
    Node(int i) : w(a[i] + i), id(i) {}
    Node(int w, int id) : w(min(w, n)), id(id) {}

    Node operator+(const Node &rhs) const {return w < rhs.w ? rhs : *this;}
} f[N][LN][K];

namespace SGT {
    #define lson pos << 1
    #define rson pos << 1 | 1

    Node t[N << 2];

    void build(int pos, int l, int r) {
        if (l == r) {t[pos] = {a[l] + l, l}; return;}
        int mid = (l + r) >> 1;
        build(lson, l, mid), build(rson, mid + 1, r);
        t[pos] = t[lson] + t[rson];
    }

    Node query(int pos, int l, int r, int x, int y) {
        if (x <= l && r <= y) {return t[pos];}
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, l, mid, x, y);
        if (x > mid) return query(rson, mid + 1, r, x, y);
        return query(lson, l, mid, x, y) + query(rson, mid + 1, r, x, y);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q; for (int i = 1; i <= n; i++) cin >> a[i];
    SGT::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        f[i][0][0] = SGT::query(1, 1, n, i, i + a[i]);
        for (int k = 1; k <= 30; k++) f[i][0][k] = Node(f[i][0][k - 1].w + 1, f[i][0][k - 1].id) + Node(min(a[i] + i + k, n));
    }
    for (int j = 1; j < LN; j++) {
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k <= 30; k++) {
                for (int k1 = 0; k1 <= k; k1++) {
                    f[i][j][k] = f[i][j][k] + f[f[i][j - 1][k1].id][j - 1][k - k1];
                }
            }
        }
    }
    int l, r, lim, cur[K];
    while (q--) {
        cin >> l >> r >> lim;
        if (l == r) {cout << "0\n"; continue;}
        if (l + a[l] + lim >= r) {cout << "1\n"; continue;}
        fill(cur, cur + lim + 1, l); int ans = 2;
        for (int j = LN - 1; j >= 0; j--) {
            bool trans = 1;
            for (int k = 0; k <= lim; k++) if (f[cur[k]][j][lim - k].w >= r) {trans = 0; break;}
            if (!trans) continue;
            ans += (1 << j);
            for (int k = lim; k >= 0; k--) {
                Node mx = {0, 0};
                for (int k1 = 0; k1 <= k; k1++) mx = mx + f[cur[k1]][j][k - k1];
                cur[k] = mx.id;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```



---

## 作者：Suiseiseki (赞：5)

首先考虑没有删除点应当怎么做，显然我们从第 $i$ 个点出发，我们可以到达的点是 $[i,i+a_i]$，那么我们假设我们下一步走到的点为 $j(j\in [i,i+a_i])$，那么 $j$ 一定满足 $\forall i\leq k\leq i+a_i,j+a_j\geq k+a_k$。

如果我们删点，那么假设在第 $i$ 个点，删除了 $x$ 个点，那么显然会走到 $i+a_i+x$，否则的话就没有必要删这么多。

那么我们就很容易设计一个状态，设 $f_{i,k,j}$ 表示从 $j$ 出发，走 $2^i$ 步，可以删除不超过 $k$ 个点可以走到的最远点。

然后转移的时候我们直接暴力枚举 $k_i,k_2$ 将 $\max_{l=j}^{f_{i,k_1,j}} f_{i,k_2,l}$ 的答案贡献到 $f_{i+1,k_1+k_2,j}$ 上，这部分可以通过数据结构来优化。

接下来把所有的询问离线一起处理，设 $ans_{t,i,j}$ 表示第 $i$ 个询问，删除 $j$ 个点，在考虑 $\geq 2^t$ 步的所有的情况下所能够到达的最靠右的不超过 $r_i$ 的点是什么（由我们在题解开头给出的结论，容易得到这样贪心是正确的），初始的时候是 $\forall 0\leq j\leq k_i, ans_{\log n,i,j}=l_i$。

然后这一部分中间的转移我们同样可以通过数据结构优化。

时间复杂度为：$O(nk\log^2 n + nk^2\log n)$

代码可以去我的博客查看：[Codeforces 1523H. Hopping Around the Array  题解](https://www.cnblogs.com/withhope/p/14835749.html)

---

## 作者：11400F (赞：3)

## CF1523H Hopping Around the Array 题解

对于在某个点跳的某一步，如果你跳到的这个点他能到达的范围最大，那么跳到这个点上肯定是最优的。

---

那么对于 $k=0$，你想从 $l$ 跳到 $r$，那么就可以贪心跳：假设当前这个点为 $x$，我们要找到 $x$ 点能跳的区间 $[x+a_x]$ 中的某一个点 $v$，使 $v+a_v$ 最大。范围更大那么就肯定更优，因为你的选择变多了，也可以跳的更远了。

于是可以处理一个倍增数组：假设 $f_{i,j}$ 为从 $i$ 点起跳，先跳到 $[i,i+a_i]$ 区间内，跳 $2^j$ 步之后再跳一步能到达的最远的点的编号。

首先预处理：我们要维护每一个点的一步能到达的最大位置，还要区间查询，于是我们就可以使用线段树这个数据结构。具体地说，我们把每一个点的坐标 $x$ 和一步能到达的位置 $val_x = x+a_x$ 插进一个线段树节点里。区间查询的时候我们就查询某个区间里最大的 $val$ 对应的 $x$ 即可。然后 $f_{i,0}$ 就等于在 $[i,i+a_i]$ 里面值最大的 $val$ 对应的 $x$。

接着转移：$f_{i,j} = f_{(f_{i,j-1}),j-1}$。

然后特判：如果 $l=r$，那么答案为 $0$，如果 $r$ 在 $[l,l+a_l]$ 里面，那么答案为 $1$。

最后倍增跳：如果你想从 $l$ 跳到 $r$，就倍增处理。记录当前点 $p$，从大到小枚举 $2$ 的指数 $j$，如果此时的 $f_{p,j} \ge r$，那么就不跳。否则就跳，并且答案加上 $2^j$，还要更新 $p$。最后答案再 $+2$。因为你要先跳到起始区间，再从最终区间再跳一步到终点。

---

现在 $k \neq 0$ 了，也就是说可以删点了。于是我们就让 $f$ 数组多一维，变为 $f_{i,j,k}$。它的定义就是，从 $i$ 点起跳，先跳到他所在的区间内，跳 $2^j$ 步之后再跳一步能到达的最远的点的编号，并且中途删除了 $k$ 个点。

于是我们预处理：还是线段树维护每一个点的一步能到达的最大位置，并且中途不删点。于是做法和之前一样，把答案记录到 $f_{i,0,0}$ 里。

然后初始转移：$f_{i,0,j}$ 为 $f_{i,0,j-1} + 1$ 和区间查询 $[i,i+a_i+j]$ 的值最大的 $val$ 对应的 $x$。

接着转移：$f_{i,j,k} = \displaystyle\max_{0\le l\le k}(f_{(f_{i,j-1,l}),j-1,k-l})$。这就相当于是把删除 $k$ 次分成了两段：$l$ 次和 $k-l$ 次，然后结合在一起，最后对所有的 $l$ 的情况取 $\max$。

之后特判：如果 $l=r$，那么答案为 $0$，如果 $r$ 在 $[l,l+a_l+k]$ 里面，那么答案为 $1$。

最后倍增跳：记录当前数组 $p$，$p_i$ 表示在当前点，删除了 $i$ 个点再跳一步能到达的最远距离所对应的当前点。然后就从大到小枚举 $2$ 的指数 $j$，如果存在一个 $i$ 使 $f_{p_i, j, k-i} \ge r$，那么就不能跳。否则就跳，并且答案加上 $2^j$，还要更新 $p$ 数组。最后答案再 $+2$。理由同上。

因为这道题的 $k$ 值范围非常的小，只有 $30$，于是我们就可以在转移和判断时枚举 $l$。则总复杂度为 $O((n+q)k^2\log n)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e4+6;
const int LG = 15;
const int K = 31;
struct node{
    int pos, val;
};
bool operator < (const node &a, const node &b){ return a.val < b.val; }
bool operator > (const node &a, const node &b){ return a.val > b.val; }
int n, a[N], q;
namespace Seg_Tr{
    struct segtr_node{
        node val;
        int l, r;
    }tr[N<<2];
    void pushup(int x){
        tr[x].val = max(tr[x<<1].val, tr[x<<1|1].val);
    }
    void build(int x, int l, int r){
        tr[x].l = l, tr[x].r = r;
        if(l==r){
            tr[x].val = {l, min(l+a[l], n)};
            return ;
        }
        int mid = l+r>>1;
        build(x<<1, l, mid);
        build(x<<1|1, mid+1, r);
        pushup(x);
    }
    node query(int x, int ql, int qr){
        int l = tr[x].l, r = tr[x].r;
        if(ql<=l&&r<=qr) return tr[x].val;
        int mid = l+r>>1;
        node ans = {0,0};
        if(ql<=mid) ans = max(ans, query(x<<1, ql, qr));
        if(qr>mid) ans = max(ans, query(x<<1|1, ql, qr));
        return ans;
    }
}
using namespace Seg_Tr;
node f[N][LG+2][K+2];
int lim;
int cur[N];// 目前的，删除了 k 个点之后能跳到的最远的点
int tmp[N];
void solve(){
    int ql, qr, k;
    cin>>ql>>qr>>k;
    if(ql==qr) return cout<<"0\n", void();
    else if(ql+k+a[ql]>=qr) return cout<<"1\n", void();
    for(int i=0;i<=k;i++) cur[i] = ql;
    int ans = 0;
    for(int j=lim;j>=0;j--){
        bool flag = 0;
        for(int l=0;l<=k;l++){
            if(f[cur[l]][j][k-l].val >= qr){
                flag = 1; break;
            }
        }
        if(flag) continue;
        ans += (1<<j);
        for(int l=0;l<=k;l++){
            node farthest = {0, 0};
            for(int now=0;now<=l;now++){
                farthest = max(farthest, f[cur[now]][j][l-now]);
            }
            tmp[l] = farthest.pos;
        }
        for(int l=0;l<=k;l++){
            cur[l] = tmp[l];
        }
    }
    cout<<ans+2<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1, 1, n);
    lim = __lg(n);
    for(int i=1;i<=n;i++){
        f[i][0][0] = query(1, i, i+a[i]);
        for(int j=1;j<=K;j++){
            f[i][0][j] = max((node){f[i][0][j-1].pos, min(f[i][0][j-1].val+1, n)},
                              query(1, i, min(i+a[i]+j, n)));
        }
    }
    for(int j=1;j<=lim;j++){
        for(int i=1;i<=n;i++){
            for(int k=0;k<=K;k++){
                for(int l=0;l<=k;l++){
                    f[i][j][k] = max(f[i][j][k], f[f[i][j-1][l].pos][j-1][k-l]);
                }
                
            }
        }
    }
    while(q--){
        solve();
    }
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

**CF1523H**

套路缝合题。

暴力 $\text{dp}$ 就是设 $\text{dp}_{\text i,\text j}$ 表示从 $\text l$ 走到 $\text i$ 并且删除了 $\text j$ 个节点时的最小步数花费，刷表和填表都可以采用数据结构维护。 

发现单次转移的 $\text{maxgap}$ 是 $\log \text n$ 级别的，并且我们发现从 $\text l \sim \text r$ 既可以从左往右 $\text {dp}$，也可以从右往左 $\text {dp}$，所以直接放弃思考，猫树分治维护左右端点到整个区间节点的 $\text {dp}$ 值，就能很轻松做到 $\text O(\text n \text k^2 \log ^ 2 \text n)$ 空间 $\text O(\text n\text k \log \text n)$ 的复杂度，但这并不是最简单且最优秀的做法。

容易想到静态区间信息问题的另一个做法：$\text {st}$ 表倍增解决问题。并且我们发现这个 $\text{dp}$ 已经没有继续优化的空间了！果断变化一下维度，设 $\text{dp}_{\text i,\text j,\text k}$ 表示从 $\text i$ 开始跳跃 $\text j$ 步并删除至多 $\text k$ 个节点后最远可以走到哪个节点。

我们想做类似树上倍增求 $\text K$ 级祖先一样的过程。令 $\text{dp}_{\text i,\text j,\text k}$ 表示从 $\text i$ 开始跳跃 $\text 2^{\text j}$ 步并删除至多 $\text k$ 个节点后最远走到哪个节点。

关于该数组的处理可以从小到大枚举 $\text j$，建立每层关于 $\text {dp}_{\text i,\text j,\text k}$ 的 $\text{st}$ 表 $\text f_{\text l,\text i,\text k}$ 表示 $\max_{\text o = \text i} ^ {\text i + \text 2 ^ {\text l} - \text 1} \{\text{dp}_{\text o,\text j,\text k}\}$，即滚动数组 $\text j$ 维，然后枚举前 $\text 2 ^ {\text j - \text 1}$ 步和后 $\text 2 ^ {\text j - \text 1}$ 步至多删除的节点数 $\text{k1,k2}$ 即可实现转移。

~~然后有人没想到这个查询怎么做怎么回事呢~~

查询时对于每个查询 $\text i$，计算最大的 $\text{as}_{\text i}$ 满足无论如何进行了 $\text {as}_{\text i}$ 步跳跃之后依然处于 $<  \text r$ 的位置。

我们从大到小枚举 $\text 2 ^ {\text k}$ 的步长，设 $\text p_{\text i,\text j}$ 表示第 $\text i$ 个询问在当前删除 $\text j$ 个节点后，考虑了 $\geq \text 2 ^ {\text k}$ 的所有步长后能跳到的最远位置。

每次判断当前该步长需要被加入答案 $\text{as}_{\text i}$ 的充要条件是尝试进行更新后的状态里没有方案能跳到目标位置 $\text r_{\text i}$ 以后否则不更新 $\text {as}_{\text i,\text j}$。

至此就做到了时间复杂度 $\text O(\text n(\text k^\text 2 + \log \text n) \log \text n)$ 空间 $\text O(\text n \text k\log \text n)$ 的时间复杂度。 

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e4 + 5 , N = 17 , K = 30;
int mxf[N + 5][K + 5][Len],f[N + 5][K + 5][Len],a[Len],lg[Len],n,q;
//mxf 滚动数组
int d;
int as[Len][K + 5],Pt[Len];
struct Q
{
	int l,r,x;
	Q(){l = r = x = 0;}
	Q(int L,int R,int X){l = L , r = R , x = X;}
}mp[Len];
int mxk,mxl,mxr;
inline int Q(int k,int l,int r)
{
	d = lg[r - l + 1];
	return max(mxf[d][k][l] , mxf[d][k][r - (1 << d) + 1]);
} 
int main()
{
	scanf("%d %d",&n,&q);for(int i = 2 ; i <= n ; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	for(int i = 0 ; i <= K ; i ++)
		for(int j = 1 ; j <= n ; j ++) f[0][i][j] = min(n , j + a[j] + i);
	for(int i = 1 ; i <= lg[n] ; i ++)
	{
		for(int j = 0 ; j <= K ; j ++)
			for(int l = 1 ; l <= n ; l ++) mxf[0][j][l] = f[i - 1][j][l];
		for(int d = 1 ; d <= lg[n] ; d ++)
			for(int j = 0 ; j <= K ; j ++)
				for(int l = 1 ; l + (1 << d) - 1 <= n ; l ++) mxf[d][j][l] = max(mxf[d - 1][j][l] , mxf[d - 1][j][l + (1 << (d - 1))]);
		for(int k1 = 0 ; k1 <= K ; k1 ++)
			for(int k2 = 0 ; k2 <= K - k1 ; k2 ++)
				for(int l = 1 ; l <= n ; l ++) 
					f[i][k1 + k2][l] = max(f[i][k1 + k2][l] , Q(k2 , l , f[i - 1][k1][l]));
	}
	//printf("!!!%d %d %d\n",mxk,mxl,mxr);
	for(int i = 1 ; i <= q ; i ++)
	{
		scanf("%d %d %d",&mp[i].l,&mp[i].r,&mp[i].x);
		for(int j = 0 ; j <= mp[i].x ; j ++) as[i][j] = mp[i].l;
		if(mp[i].l == mp[i].r) Pt[i] = -1;
	}
	int R[K + 5];
	for(int i = lg[n] ; i >= 0 ; i --) 
	{
		for(int j = 0 ; j <= K ; j ++)
			for(int l = 1 ; l <= n ; l ++) mxf[0][j][l] = f[i][j][l];
		for(int d = 1 ; d <= lg[n] ; d ++)
			for(int j = 0 ; j <= K ; j ++)
				for(int l = 1 ; l + (1 << d) - 1 <= n ; l ++) mxf[d][j][l] = max(mxf[d - 1][j][l] , mxf[d - 1][j][l + (1 << (d - 1))]);
		for(int o = 1 ; o <= q ; o ++)
		{
			for(int j = 0 ; j <= mp[o].x ; j ++) R[j] = 0;
			for(int k1 = 0 ; k1 <= mp[o].x ; k1 ++)
				for(int k2 = 0 ; k2 <= mp[o].x - k1 ; k2 ++)
					R[k1 + k2] = max(R[k1 + k2] , Q(k2 , mp[o].l , as[o][k1]));
			if(R[mp[o].x] < mp[o].r)
			{
				Pt[o] += (1 << i);
				for(int j = 0 ; j <= mp[o].x ; j ++) as[o][j] = R[j];
			}
		}
	}
	for(int i = 1 ; i <= q ; i ++) printf("%d\n",Pt[i] + 1);
	return 0;
}
```

---

## 作者：丛雨 (赞：2)

# CF1523H Hopping Around the Array

> 题意:存在一个长度为$n$的序列$a_i$.每次询问时给你一个$l,r,k$,每次操作你可以花费代价$1$将$l$变为$[l+1,a_l+l]$中的一个数，或进行不超过$k$次的代价为$0$的$l+1$,问将$l$变成$r$的最少花费
>
> $1\leq n,q\leq 20000$

考虑设计状态$dp_{i,j,k}$表示$i$花费$j$进行$k$次操作2能到达的$x+a_x$最大的$x$

为什么如此设计呢？

原因在于如果我们只是让$x$最大，则可能存在$y<x$而$y+a_y>x+a_x$,这时如果我们要继续往下走就会选择先到$y$再到$x$,这时下一步能到达的位置更多，且代价相同

我们发现此时总状态数$O(n^2k)$无法通过

这时就运用了倍增的思想，对于状态$dp_{i,j,k}$表示$i$花费$2^j$进行$k$次操作2能到达的$x+a_x$最大的$x$
由于任何代价$x$均可以表示为$\sum2^{y_i}$,所以不会漏掉可能的转移方式

预处理时就用类似于$\tt ST$表的方式，转移则使用类似求$\tt LCA$时的倍增(即求出使得只需再一次操作1便可以到达终点的最小代价)

时间复杂度$O((n+q)k^2\log n)$,能过就离谱

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define log2 LOG2
int s,m,a[20005],f[15][31][20005],st[15][200005],A[31];
int Max_(int x,int y){return x+a[x]>y+a[y]?x:y;}
int main(){
	s=read,m=read;
	auto log2=[=](double x)->int{return x==1?0:((*(unsigned ll*)&x>>52)&1023)+1;};
	auto query=[=](int l,int r){
		int x=log2(r-l+1);
		return Max_(st[x][l],st[x][r-(1<<x)+1]);
	};
	for(int i=1;i<=s;++i)a[i]=read,st[0][i]=i,a[i]+i>s&&(a[i]=s-i+1);
	st[0][s+1]=s+1;a[s+1]=1;
	for(int i=0;(1<<i+1)<=s+1;++i)
		for(int j=1;j+(1<<i+1)-1<=s+1;++j)
			st[i+1][j]=Max_(st[i][j],st[i][j+(1<<i)]);
	for(int i=0;(1<<i)<=s;++i)
		for(int j=0;j<=30;++j)
			f[i][j][s+1]=s+1;
	for(int i=1;i<=s;++i){
		f[0][0][i]=query(i+1,i+a[i]);
		for(int j=1;j<=30;++j)
			f[0][j][i]=min(i+j+a[i],s+1);
	}
	for(int i=1;(1<<i)<=s;++i){
		auto g=f[i],h=f[i-1];
		for(int j=0;j<=30;++j)
			for(int k=0;k+j<=30;++k)
				for(int l=1;l<=s;++l)
					g[j+k][l]=Max_(g[j+k][l],h[j][h[k][l]]);
	}while(m--){
		int l=read,r=read,k=read,ans=2;
		if(l==r){puts("0");continue;}
		if(l+a[l]+k>=r){puts("1");continue;}
		fill(A,A+k+1,l);
		int x=log2(r-l+1)+1;
		while(x--){
			auto g=f[x];bool vis=1;
			for(int i=0;i<=k&&vis;++i)
				for(int j=0;i+j<=k;++j){
					int p=g[i][A[j]];
					if(p+a[p]+k-i-j>=r){vis=0;break;}
				}
			if(!vis)continue;
			ans+=1<<x;
			for(int i=k;~i;--i)
				for(int j=k-i;~j;--j)
					A[i+j]=Max_(A[i+j],g[j][A[i]]);
		}printf("%d\n",ans);
	}
	return 0;
}
```





---

## 作者：StayAlone (赞：1)

很纯粹的倍增题目，但是较难想清楚。

先假设 $k=0$，考虑跳跃的策略。除了最后一步，就是每次跳到 $[i, i+a_i]$ 中，$j+a_j$ 最大的 $j$，这样下一步的范围最广。若在此次跳跃中考虑删除，其实就是将 $i$ 的范围扩展为 $[i, i+k+a_i]$。

由于跳跃的方式固定，可以用倍增优化。设 $f_{i, j, k}$ 表示从 $i$ 开始，跳跃 $2^j$ 次，删除了 $k$ 个位置时，**再跳一步**最远的位置。可以通过简单地枚举两部分删除的个数合并。

考虑查询。先特判掉 $ans\leq 1$ 的情况。

其他情况下，由于 $f$ 数组是保证跳到的位置的下一步最远，而不是跳到的位置最远，因此倍增的条件是跳到的位置的下一步无法到 $r$ 时跳跃。这样跳完之后，还要耗费 $1$ 步跳到一个能到 $r$ 的位置，再耗费 $1$ 步跳到 $r$。

时间复杂度 $\mathcal O((n+q)k^2\log n)$。

[AC record](https://codeforces.com/problemset/submission/1523/318835518)

```cpp
int n, q; pii a[MAXN], f[MAXN][16][35];
 
struct setr {
    pii maa[MAXN << 2];
 
    il void pushup(int x) {
        maa[x] = max(maa[ls(x)], maa[rs(x)]);
    }
 
    il void build(int x, int l, int r) {
        if (l == r) return maa[x] = a[l], void();
        int mid = l + r >> 1;
        build(ls(x), l, mid); build(rs(x), mid + 1, r);
        pushup(x);
    }
 
    il pii query(int x, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return {0, 0};
        if (l >= ql && r <= qr) return maa[x];
        int mid = l + r >> 1;
        return max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
    }
} T;
 
il void solve() {
    int l, r, k; read(l, r, k);
    if (l == r) return puts("0"), void();
    if (a[l].fst + k >= r) return puts("1"), void();
    int ans = 2, g[35]; fill(g, g + k + 1, l);
    rep2(j, 15, 0) {
        bool flg = 0;
        rep1(i, 0, k) if (f[g[i]][j][k - i].fst >= r) flg = 1;
        if (flg) continue;
        ans += 1 << j;
        rep2(i, k, 0) {
            pii p = {0, 0};
            rep1(k1, 0, i) gmax(p, f[g[k1]][j][i - k1]);
            g[i] = p.snd;
        }
    } printf("%d\n", ans);
}
 
int main() {
    read(n, q);
    rep1(i, 1, n) a[i] = {min(n, i + read()), i};
    T.build(1, 1, n);
    rep1(i, 1, n) {
        f[i][0][0] = T.query(1, 1, n, i, a[i].fst);
        rep1(k, 1, 30) f[i][0][k] = max(a[min(a[i].fst + k, n)], {min(f[i][0][k - 1].fst + 1, n), f[i][0][k - 1].snd});
    }
    rep1(j, 1, 15) {
        rep1(i, 1, n) rep1(k, 0, 30) rep1(k1, 0, k) {
            gmax(f[i][j][k], f[f[i][j - 1][k1].snd][j - 1][k - k1]);
        }
    } while (q--) solve();
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

最水 3500。。。

考虑一个性质：如果我们存在一种删数方案，使得 $i$ 经过 $j$ 步能到达 $r$，则 $\forall i \le l \le r$，$i$ 都能经过不超过 $j$ 步到达 $l$。因此我们设 $f_{i,j,k}$ 为：$i$ 最多删 $k$ 个点，走 $2^j$ 步最远能到哪。

在倍增的过程中，你需要计算一段区间中更低的 $j$ 对应的 $f$ 的最大值，用 ST 表可以去掉 max。

统计答案的时候递增即可。

显然，同时建立这么多 ST 表肯定会爆空间，**最好的解决方案是同时离线，对于每一个二的幂次分别建立 ST 表！！**

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e4+10;
int n,q,a[MAXN],dp[MAXN][15][31],lg2[MAXN];
int st[MAXN][15][31];
#define max(a,b) ((a>b)?a:b)
void build_st(int dep) {
	ffor(i,1,n) ffor(j,0,30) st[i][0][j]=dp[i][dep][j];
	ffor(k,1,14) for(int l=1,r=(1<<k);r<=n;l++,r++) ffor(j,0,30) st[l][k][j]=max(st[l][k-1][j],st[l+(1<<k-1)][k-1][j]);
	return ;
}
int query(int lim,int l,int r) {
	return max(st[l][lg2[r-l+1]][lim],st[r-(1<<lg2[r-l+1])+1][lg2[r-l+1]][lim]);
}
int pos[MAXN][31],npos[MAXN][31],ans[MAXN],s[MAXN],t[MAXN],k[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) lg2[i]=log2(i);
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) ffor(j,0,30) dp[i][0][j]=min(n,i+a[i]+j);
	ffor(d,1,14) {
		build_st(d-1);
		ffor(i,1,n) ffor(j,0,30) ffor(k,0,30-j) dp[i][d][j+k]=max(dp[i][d][j+k],query(k,i,dp[i][d-1][j]));
	}
	ffor(i,1,q) {
		cin>>s[i]>>t[i]>>k[i];
		ffor(j,0,k[i]) pos[i][j]=s[i];
	}
	roff(d,14,0) {
		build_st(d);
		ffor(id,1,q) {
			ffor(j,0,k[id]) npos[id][j]=0;
			ffor(j,0,k[id]) ffor(K,0,k[id]-j) npos[id][j+K]=max(npos[id][j+K],query(K,s[id],pos[id][j]));
			if(npos[id][k[id]]<t[id]) {
				ans[id]+=(1<<d);
				ffor(j,0,k[id]) pos[id][j]=npos[id][j];
			}
		}
	}
	ffor(i,1,q) {
		if(s[i]==t[i]) cout<<0<<'\n';
		else cout<<ans[i]+1<<'\n';	
	}
	return 0;
}
```

---

## 作者：zzxLLL (赞：0)

整体倍增(?)

---

显然地，如果从 $x$ 开始走 $k$ 步能到达最远的点为 $y$，那么 $k$ 步内 $[x,y]$ 内的所有点都可以到达。

考虑 dp。设 $f_{x,i,j}$ 表示从 $x$ 开始，走了 $i$ 步，其中删掉 $j$ 个点，能够到达的最远点。对于每个询问，都二分找到最小的 $k$。状态数 $O(n^2k)$ 过大，考虑优化。

因为 $k$ 步能走到的是连续一段，考虑倍增：设 $f_{x,i,j}$ 表示从 $x$ 开始，走 $2^i$ 步，其中删去了 $j$ 个点能够到达的最远点。转移：

$$f_{x,i,j}=\max\limits_{p+q=j}(\max\limits_{y=x}^{f_{x,i-1,p}}f_{y,i-1,q})$$

边界是 $f_{x,0,j}=\min(x+a_x+j,n)$。

然后每一层建 $k$ 个 ST 表来维护里面那个 $\max$ 即可。时间复杂度 $O(nk^2\log n)$。

对于每个询问 $(l,r)$，考虑从 $l$ 开始倍增，从大到小枚举 $2^i$，找到**最远走不到 $r$ 的**最大步数。这个也可以 dp 维护，转移与上面类似。但是这样每次都要建 $k\log n$ 个 ST 表，非常不好。发现每次建的 ST 表是一样的，于是将询问离线，从大到小枚举 $i$，建出 $f_{x,i,* }$ 的 ST 表，然后 $q$ 个询问一起转移即可。

```cpp
#include <bits/stdc++.h>
const int M = 2e4 + 10;

inline int read() {
    char ch = getchar();
    int x = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

int n, q, a[M], _lg2[M], cur[31][M];
int f[18][31][M];

struct Query { int l, r, k, ans; } w[M];

struct Sparse_Table {
    int st[18][M];
    inline void Build(int* f, int len) {
        for (int i = 1; i <= len; i++) st[0][i] = f[i];
        for (int k = 1; (1 << k) <= len; k++)
            for (int i = 1; i + (1 << k) - 1 <= len; i++)
                st[k][i] = std::max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
    inline int Ask(int l, int r) {
        int k = _lg2[r - l + 1];
        return std::max(st[k][l], st[k][r - (1 << k) + 1]);
    }
} rmq[31];

int main() {
    _lg2[0] = -1;
    for (int i = 1; i < M; i++) _lg2[i] = _lg2[i >> 1] + 1;

    n = read(), q = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 30; j++) f[0][j][i] = std::min(n, a[i] + i + j);
    
    for (int k = 1; k <= 17; k++) {
        for (int i = 0; i <= 30; i++) rmq[i].Build(f[k - 1][i], n);
        for (int i = 1; i <= n; i++)
            for (int x = 0; x <= 30; x++)
                for (int y = 0; x + y <= 30; y++)
                    f[k][x + y][i] = std::max(f[k][x + y][i], rmq[y].Ask(i, f[k - 1][x][i]));
    }

    for (int i = 1; i <= q; i++) {
        w[i].l = read(), w[i].r = read(), w[i].k = read();
        w[i].ans = (w[i].l != w[i].r);
        for (int j = 0; j <= w[i].k; j++) cur[j][i] = w[i].l;
    }

    for (int k = 17; k >= 0; k--) {
        for (int i = 0; i <= 30; i++) rmq[i].Build(f[k][i], n);
        for (int i = 1; i <= q; i++) {
            static int nxt[31];
            for (int j = 0; j <= w[i].k; j++) nxt[j] = cur[j][i];
            for (int x = 0; x <= w[i].k; x++)
                for (int y = 0; x + y <= w[i].k; y++)
                    nxt[x + y] = std::max(nxt[x + y], rmq[y].Ask(w[i].l, cur[x][i]));
            
            bool flag = true;
            for (int j = 0; j <= w[i].k; j++)
                if (nxt[j] >= w[i].r) { flag = false; break; }
            if (!flag) continue;

            for (int j = 0; j <= w[i].k; j++) cur[j][i] = nxt[j];
            w[i].ans += (1 << k);
        }
    }
    
    for (int i = 1; i <= q; i++) printf("%d\n", w[i].ans);
    return 0;
}
```

---

