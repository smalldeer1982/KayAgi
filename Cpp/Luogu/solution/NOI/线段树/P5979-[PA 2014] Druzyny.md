# [PA 2014] Druzyny

## 题目描述

体育课上，$n$ 个小朋友排成一行（从 $1$ 到 $n$ 编号），老师想把他们分成若干组，每一组都包含编号连续的一段小朋友，每个小朋友属于且仅属于一个组。

第 $i$ 个小朋友希望它所在的组的人数不多于 $d_i$，不少于 $c_i$，否则他就会不满意。

在所有小朋友都满意的前提下，求可以分成的组的数目的最大值，以及有多少种分组方案能达到最大值。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le c_i\le d_i\le n$。

## 样例 #1

### 输入

```
9
1 4
2 5
3 4
1 5
1 1
2 5
3 5
1 3
1 1```

### 输出

```
5 2```

## 样例 #2

### 输入

```
2
1 1
2 2```

### 输出

```
NIE```

# 题解

## 作者：ethan_zhou (赞：19)

说一个 $O(n\log^2 n)$ 的 cdq 分治做法，常数不大，不用分类讨论，较为好写。

## 一些符号

- 记 $\operatorname{mxl}(l,r)$ 表示下标在 $l$ 到 $r$ 之间的所有区间的左端点最大值，$\operatorname{mnr}(l,r)$ 意义类似。
- 记 $\operatorname{rng}(l,r)=[\operatorname{mxl}(l,r),\operatorname{mnr}(l,r)]$。

## 暴戾

首先是一个简单的 $O(n^2)$ dp：

$$dp_i=1+\max_{[j<i]\land [(i-j)\in\operatorname{rng}(i+1,j)]}dp_j$$

因为这个转移的条件比较复杂，合法的 $j$ 都是不连续的，考虑用 cdq 分治来做。

## cdq

假设我们目前已经知道 $dp_{[l, mid]}$，考虑这些 dp 值对 $dp_{[mid+1, r]}$ 的贡献。

$dp_i(i\le mid)$ 可以更新 $dp_j(j>mid)$ 当且仅当：

1. $j-i\in\operatorname{rng}(i,mid)$
1. $j-i\in\operatorname{rng}(mid+1,j)$

注意到条件 1 与 $i$ 相关性较大，条件 2 与 $j$ 相关性比较大，考虑分别满足两个条件。

我们可以开一个下标线段树 $T$，然后枚举 $j\in[mid+1,r]$，每次进行三类操作：
1. 对于所有满足 $j=i+\operatorname{mxl}(i,mid)-1$ 的 $i$，$T_i\gets dp_i+1$。
1. 对于所有满足 $j=i+\operatorname{mnr}(i,mid)$ 的 $i$，$T_i\gets-\infty$。
1. $dp_j\gets\min_{j\in[j-\operatorname{mnr}(mid+1,r),j-\operatorname{mxl}(mid+1,r)]}$。

前 2 种操作保证只有满足 **条件 1** 的 $i$ 此时才会在线段树里。
而第 3 个操作则从线段树中筛选出满足 **条件 2** 的 $i$ 用来更新 $dp_j$。

具体实现就比较好搞了，可以先扫一下 $i\in[l,mid]$，然后其对应进行 1，2 操作的 $j$ 处开 `vector` 打个标记即可。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using pi = pair<int, int>;
const char nl = '\n';
const int MXN = 1e6 + 5, INF = 1e9, P = 1e9 + 7;
int n;
pi rng[MXN];
inline void upd(pi &x, const pi &y) {
    x.fi = max(x.fi, y.fi);
    x.se = min(x.se, y.se);
}
namespace segt {
struct node {
    int mx, mxc;
    node(int mx = -INF, int mxc = 0) : mx(mx), mxc(mxc) {}
} t[MXN << 2];
inline int norm(int x) { return x < P ? x : x - P; }
inline node operator+(const node &x, const node &y) {
    if (x.mx == y.mx) return node(x.mx, norm(x.mxc + y.mxc));
    if (x.mx > y.mx) return x;
    return y;
}
#define ls p << 1
#define rs p << 1 | 1
inline void pull(int p) { t[p] = t[ls] + t[rs]; }
void _mdf(int p, int l, int r, int mi, const node &mv) {
    if (l == r) {
        t[p] = mv;
        return;
    }
    int mid = (l + r) >> 1;
    if (mi <= mid)
        _mdf(ls, l, mid, mi, mv);
    else
        _mdf(rs, mid + 1, r, mi, mv);
    pull(p);
}
node _qry(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return node();
    if (ql <= l && r <= qr) return t[p];
    int mid = (l + r) >> 1;
    return _qry(ls, l, mid, ql, qr) + _qry(rs, mid + 1, r, ql, qr);
}
int sz;
void init(int _sz) {
    sz = _sz;
    fill(t + 1, t + 1 + (sz << 2), node());
}
void mdf(int mi, const node &mv) { _mdf(1, 1, sz, mi, mv); }
node qry(int ql, int qr) { return _qry(1, 1, sz, ql, qr); }
} // namespace segt

using segt::init;
using segt::mdf;
using segt::qry;
vector<pi> id[MXN];
segt::node dp[MXN];
void solve(int l, int r) {
    if (r - l <= 50) {
        for (int i = l; i <= r; i++) {
            pi tmp = {1, n};
            for (int j = i - 1; j >= l; j--) {
                upd(tmp, rng[j + 1]);
                if (i - j > tmp.se) break;
                if (i - j >= tmp.fi) dp[i] = dp[i] + segt::node(dp[j].mx + 1, dp[j].mxc);
            }
        }
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    pi tmp = {1, n};
    for (int i = mid + 1; i <= r; i++) id[i].clear();
    for (int i = mid; i >= l; i--) {
        if (tmp.se < tmp.fi || i + tmp.se <= mid) break;
        if (i + tmp.fi <= r) {
            id[max(mid + 1, i + tmp.fi)].push_back({i, 1});
            id[min(r + 1, i + tmp.se + 1)].push_back({i, 0});
        }
        upd(tmp, rng[i]);
    }
    init(mid - l + 1);
    tmp = {1, n};
    for (int i = mid + 1; i <= r; i++) {
        for (auto j : id[i]) {
            if (j.se)
                mdf(j.fi - l + 1, dp[j.fi]);
            else
                mdf(j.fi - l + 1, segt::node());
        }
        upd(tmp, rng[i]);
        if (tmp.se < tmp.fi || i - tmp.se > mid) break;
        segt::node res = qry(max(l, i - tmp.se) - l + 1, min(mid, i - tmp.fi) - l + 1);
        ++res.mx;
        dp[i] = dp[i] + res;
    }
    solve(mid + 1, r);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    pi tmp = {1, n};
    for (int i = 1; i <= n; i++) {
        cin >> rng[i].fi >> rng[i].se;
        upd(tmp, rng[i]);
    }
    dp[0] = {0, 1};
    solve(0, n);
    if (dp[n].mx < 0)
        cout << "NIE";
    else
        cout << dp[n].mx << " " << dp[n].mxc;

    return 0;
}
```

---

## 作者：zzy_zzy (赞：8)

### 前言
感谢 @[liu_yi](/user/673867) 跟我细心讲解！
### 思路
先考虑暴力怎么做。

像这种分段的题，很多都是 dp，因此我们考虑 dp。套路的，设 $dp_i$ 表示以 $i$ 为一段的结尾的组数最大，$g_i$ 表示总方案数，则有转移：

$$dp_i=\max_{\max_{k=j+1}^{i}c_k\le i-j\le \min_{k=j+1}^{i}d_k}dp_j+1$$
$$g_i=\sum_{\max_{k=j+1}^{i}c_k\le i-j\le \min_{k=j+1}^{i}d_k}g_j$$

这样的复杂度是 $O(n^2)$ 的，考虑优化。

首先可以确定的是，当 $i$ 固定时，满足条件的 $j$ 并非一段区间，因此不能直接使用线段树等数据结构进行优化。

但是，当 $i$ 固定时，满足 $i-j\le \min_{k=j+1}^{i}d_k$ 的 $j$ 是一段连续的区间（因为当 $j$ 减小时，$i-j$ 在变大，而 $\min_{k=j+1}^{i}d_k$ 却在变小，迟早会有一个位置会使得这个限制不满足）。所以，可以考虑记 $p_i$ 为最早满足这个限制的位置。

这时，我们还剩下一个很烦的限制，我们考虑引入一种分治（不妨设它叫 ly 分治）。具体的，对于每段区间 $[l,r]$，我们找到这段区间最大值的位置（记作 $mid$），先考虑递归计算 $[l,mid]$ 的值，将其插入至某种数据结构中，再考虑用 $[l,mid]$ 的值去更新 $[mid+1,r]$ 的值，最后再递归计算 $[mid+1,r]$ 对 $[mid+1,r]$ 的贡献。

但是，用 $[l,mid]$ 去更新 $[mid+1,r]$ 的过程也因具体情况而定，一般要分 $[l,mid]$ 和 $[mid+1,r]$ 谁的长度更短两种情况来保证复杂度。（因为如果不这样干的话每次最坏可以遍历 $n$ 个位置，而递归树的树高最坏是 $O(n)$ 的，所以总复杂度就退化到 $O(n^2)$ 了。若分情况讨论，复杂度就相当于在笛卡尔树上做启发式合并（不用数据结构维护）的复杂度，是 $O(n\log n)$ 的）

在这道题里。我们分以下两种情况：

- 若 $[l,mid]$ 的长度比 $[mid+1,r]$ 长，那很简单。直接遍历 $[mid+1,r]$ 的所有数，由于 $mid$ 是任意一个跨过 $mid$ 的区间的最大值，所以这时满足条件的 $j$ 是一个区间！只要实现单点修、区间求和。可以用线段树维护！
- 若 $[l,mid]$ 的长度比 $[mid+1,r]$ 短，那也很简单。直接遍历 $[l,mid]$ 的所有数，此时我们会发现 $p$ 是单调的（这个很容易想），因此可以二分出这个位置能更新到的最后一个位置，而由于当 $j$ 固定时，所能更新到的 $i$ 也是一段区间（同上一种情况），所以只需要实现区间加、单点修、单点查，也可以使用线段树！

因此，这道题就做完了！实现上，可以新定义加运算表示两个带有最值和最值个数的结构体的合并，注意一下边界条件。

### AC code：
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
int c[1000010],d[1000010],p[1000010];
const int Mod=1e9+7;
pair<int,int>st[1000010][20];
int Log[1000010];
int getMin(int l,int r){//找d的最小值
    int k=Log[r-l+1];
    if(st[l][k].first<st[r-(1<<k)+1][k].first)return st[l][k].second;
    return st[r-(1<<k)+1][k].second;
}
int getMax(int l,int r){//找c的最大值
    if(!l&&!r)return 0;
    if(!l)l=1;
    int k=Log[r-l+1];
    if(st[l][k].first>st[r-(1<<k)+1][k].first)return st[l][k].second;
    return st[r-(1<<k)+1][k].second;
}
struct NN{
    int Max,ci;//最大值、出现次数
}tree[4000010],tag[4000010];
NN operator+(NN a,NN b){//新定义加
    if(a.Max>b.Max)return a;
    if(a.Max<b.Max)return b;
    return {a.Max,(a.ci+b.ci)%Mod};
}
NN dp[1000010],unit_cell={-1000000000,0};//unit_cell是加操作的单位元
void pushdown(int p){
    if(tag[p].Max==unit_cell.Max&&tag[p].ci==unit_cell.ci)return;
    tree[ls]=tree[ls]+tag[p];
    tree[rs]=tree[rs]+tag[p];
    tag[ls]=tag[ls]+tag[p];
    tag[rs]=tag[rs]+tag[p];
    tag[p]=unit_cell;
}
inline void change(int p,int l,int r,int x,NN Y){//线段树单点修改
    if(l==r&&l==x){
        tree[p]=Y;
        return;
    }
    pushdown(p);
    int mid=(l+r)>>1;
    if(x<=mid)change(ls,l,mid,x,Y);
    else change(rs,mid+1,r,x,Y);
    tree[p]=tree[ls]+tree[rs];
}
inline void Change(int p,int l,int r,int L,int R,NN Y){//线段树区间加
    if(l>R||r<L)return;
    if(l>=L&&r<=R){
        tag[p]=tag[p]+Y;
        tree[p]=tree[p]+Y;
        return;
    }
    pushdown(p);
    int mid=(l+r)>>1;
    Change(ls,l,mid,L,R,Y);
    Change(rs,mid+1,r,L,R,Y);
    tree[p]=tree[ls]+tree[rs];
}
inline NN ask(int p,int l,int r,int L,int R){//线段树区间求和
    if(l>R||r<L)return unit_cell;
    if(l>=L&&r<=R)return tree[p];
    pushdown(p);
    int mid=(l+r)>>1;
    return ask(ls,l,mid,L,R)+ask(rs,mid+1,r,L,R);
}
int n;
inline void ly(int l,int r){//ly分治
    if(l>=r)return;
    int mid=getMax(l,r-1);//细节(如果写成getMax(l,r)会死循环)
    if(mid==l&&r!=l+1)mid=getMax(l+1,r-1);//细节(如果不加会死循环)
    if(r-mid<mid-l+1||r-l==1){//右边更短
        ly(l,mid);
        for(int i=mid+1;i<=r;i++){
            NN ss;
            if(i==r&&c[r]>=c[mid]){
                ss=ask(1,0,n,max(l,p[i]),min(mid-1,i-c[r]));
            }
            else{
                ss=ask(1,0,n,max(l,p[i]),min(mid-1,i-c[mid]));
            }
            ss.Max++;
            dp[i]=ask(1,0,n,i,i);
            dp[i]=dp[i]+ss;
            if(mid>=p[i]&&i-mid>=c[getMax(mid+1,i)]){//细节，考虑每个数对 mid 的贡献
                dp[mid]=ask(1,0,n,mid,mid);
                NN sss=dp[mid];
                sss.Max++;
                dp[i]=dp[i]+sss;
            }
            change(1,0,n,i,dp[i]);
        }
        ly(mid+1,r);
    }
    else{
        ly(l,mid-1);//细节，考虑把 mid 和 mid+1~r 一起算，不然很难用 mid 更新 mid+1~r
        for(int i=l;i<mid;i++){
            int ll=mid,rr=r,ans=mid-1;
            while(ll<=rr){//二分找到右边界
                int Mid=(ll+rr)>>1;
                if(p[Mid]<=i){
                    ans=Mid;
                    ll=Mid+1;
                }
                else rr=Mid-1;
            }
            dp[i]=ask(1,0,n,i,i);
            NN ss=dp[i];
            ss.Max++;
            Change(1,0,n,max(mid,i+c[mid]),min(r-1,ans),ss);
            if(c[r]>=c[mid]){
                if(r-i>=c[r]&&p[r]<=i)dp[r]=dp[r]+ss,Change(1,0,n,r,r,ss);
            }
            else{
                if(r-i>=c[mid]&&p[r]<=i)dp[r]=dp[r]+ss,Change(1,0,n,r,r,ss);
            }
        }
        ly(mid,r);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>d[i];
        st[i][0]={d[i],i};
    }
    Log[0]=-1;
    for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
    for(int i=1;i<=19;i++){
        for(int j=1;j<=n-(1<<i)+1;j++){
            if(st[j][i-1].first<st[j+(1<<(i-1))][i-1].first){
                st[j][i]=st[j][i-1];
            }
            else{
                st[j][i]=st[j+(1<<(i-1))][i-1];
            }
        }
    }
    // 二分找p
    for(int i=1;i<=n;i++){
        int l=0,r=i-1,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if((i-mid)<=d[getMin(mid+1,i)]){
                ans=mid;
                r=mid-1;
            }
            else l=mid+1;
        }
        p[i]=ans;
    }
    for(int i=1;i<=n;i++)st[i][0]={c[i],i};
    for(int i=1;i<=19;i++){
        for(int j=1;j<=n-(1<<i)+1;j++){
            if(st[j][i-1].first>st[j+(1<<(i-1))][i-1].first){
                st[j][i]=st[j][i-1];
            }
            else{
                st[j][i]=st[j+(1<<(i-1))][i-1];
            }
        }
    }
    // 这个不是cdq分治，那我们就叫它ly分治吧QaQ
    dp[0]={0,1};
    change(1,0,n,0,dp[0]);
    for(int i=1;i<=n;i++){
        dp[i]=unit_cell;
        change(1,0,n,i,dp[i]);
    }
    for(int i=1;i<=4*n;i++){
        tag[i]=unit_cell;
    }
    ly(0,n);
    dp[n]=ask(1,0,n,n,n);
    if(!dp[n].ci||!dp[n].Max){
        cout<<"NIE";
        return 0;
    }
    cout<<dp[n].Max<<" "<<dp[n].ci;
    return 0;
}
```

---

## 作者：forest114514 (赞：7)

### P5979 [PA2014] Druzyny

依旧是 feelcle 课上的神仙例题，考虑朴素的 DP，记 $f_i$ 为将 $i$ 划分进以 $i$ 结尾的组的最大划分数量，$g_i$ 为此时的方案数。

则：
$$
f_{i}=\max\limits_{\max\limits_{j+1\sim i} l_k\le i-j\le \min\limits_{j+1\sim i} r_k} f_{j}+1,g_{i}=\sum\limits_{\max\limits_{j+1\sim i} l_k\le i-j\le \min\limits_{j+1\sim i} r_k} [f_{j}+1=f_i] g_j
$$
我们首先计算 $f$，注意到这个 DP 的合法决策点不是单调的甚至有可能不连续，不能每次二分/单调队列之类的优化……

正难则反，既然我们很难直接确定 DP 的所有转移点，所以我们考虑每一个点对后面的点的贡献，直接做也不好做的，所以考虑 cdq 分治，我们可以确定一段区间 $[l,r]$ 中 $j\in[l,mid]$ 对 $i\in[mid+1,r]$ 的贡献，从这里转移出去。

考虑 $j\in[l,mid],i\in[mid+1,r]$，我们可以记录 $j\sim mid$ 的后缀 $\min r_k\to lmn_j/\max l_k\to lmx_j$ 和 $mid+1\sim i$ 的前缀 $\min r_k\to rmn_i/ \max l_k\to rmx_i$，此时 $j\to i$ 需要满足 $\max(lmx_{j+1},rmx_i)\le i-j\le \min(lmn_{j+1},rmn_i)$，**此时一个区间 $\min/\max$ 的限制就成了单点的限制**。

考虑去掉 $\max/\min$，即只需要让 $lmx,lmn$ 和 $rmx,rmn$ 同时满足条件即可。

1.  $lmx_j\le i-j\le lmn_j\to i\in[lmx_j+j,lmn_j+j]$，此时是向一个区间转移 $f_j+1$，直接不好做，可以考虑对 $i$ 扫描线，在移动 $i$ 的同时增加或删除可转移的 $f_j$ 即可。
2. $rmx_i\le i-j\le rmn_i\to j\in[i-rmn_i,i-rmx_i]$，此时查询区间 $\max$ 即可。

综合以上 2 种情况，开一个下标线段树使用线段树+扫描线，我们可以在 $O(N\log N)$ 解决一层的转移。

至于数组 $g$，考虑同时维护即可，转移的同时注意处理相等的情况，线段树 `pushup` 时特判一下相等即可。

时间复杂度为 $O(N\log^2 N)$，空间复杂度为 $O(N)$。


代码还是挺好写的：

```cpp
const int N=1e6+100,mod=1e9+7;
int n,L[N],R[N];
struct DP{
	int f,g;
	DP(int _f=-inf,int _g=0){f=_f,g=_g;}
}dp[N];
DP operator +(const DP X,const DP Y){
	if(X.f==Y.f) return DP(X.f,(X.g+Y.g>=mod)?X.g+Y.g-mod:X.g+Y.g);
	return (X.f>Y.f)?X:Y;
}
template<int SIZE> struct SGT{
	DP tr[SIZE<<2];
	void update(int x,int l,int r,int u,const DP &v){
		if(l==r){tr[x]=v; return;}
		int mid=l+r>>1;
		(mid>=u)?update(ls(x),l,mid,u,v):update(rs(x),mid+1,r,u,v);
		tr[x]=tr[ls(x)]+tr[rs(x)];
	}
	DP query(int x,int l,int r,int L,int R){
		if(l>r||L>R) return DP(-inf,0);
		if(L<=l&&r<=R) return tr[x];
		int mid=l+r>>1;DP res=DP();
		if(mid>=L) res=query(ls(x),l,mid,L,R);
		if(mid<R) res=res+query(rs(x),mid+1,r,L,R);
		return res;
	}
};
SGT<N>TR;
vector<pii> opt[N];
void cdq(int l,int r){
	if(l==r) return;
	int mid=l+r>>1;
	cdq(l,mid);
	int lmx=L[mid+1],lmn=R[mid+1];
	per(i,mid,l){
		if(lmx>lmn) break;
		if(i+lmx<=r&&i+lmn>=mid+1){
			opt[max(i+lmx,mid+1)].pb({i,1});
			opt[min(r,i+lmn)+1].pb({i,-1});
		}
		lmx=max(lmx,L[i]);
		lmn=min(lmn,R[i]);
	}
	int rmx=0,rmn=inf;
	rep(i,mid+1,r){
		for(auto op:opt[i]) TR.update(1,1,n,op.fi,(op.sc==1)?DP(dp[op.fi].f+1,dp[op.fi].g):DP(-inf,0));
		opt[i].clear();
		rmx=max(rmx,L[i]);
		rmn=min(rmn,R[i]);
		if(rmn>=rmx) dp[i]=dp[i]+TR.query(1,1,n,max(i-rmn,l),min(i-rmx,mid));
	}
	for(auto op:opt[r+1]) TR.update(1,1,n,op.fi,DP());
	opt[r+1].clear();
	cdq(mid+1,r);
}
signed main(){
	read(n);
	int minn=inf,maxx=0;
	rep(i,1,n)read(L[i],R[i]);
	rep(i,1,n){
		maxx=max(maxx,L[i]);minn=min(minn,R[i]);
		if(maxx<=i&&i<=minn) dp[i]=DP(1,1);
	}
	cdq(1,n);
	if(dp[n].f<=0) puts("NIE");
	else write(dp[n].f,' '),write(dp[n].g,'\n');
	return 0;
}
```



---

## 作者：KellyFrog (赞：6)

~~模拟赛题，终于学会了 cdq 分治~~

朴素 DP 就是对于 $\max_{j\le k\le i} l_k \le i-j+1\le \min_{j\le k\le i} r_k$，$f_j\rightarrow f_i$

考虑如何优化，一般对 min/max 可以用单调栈或者分治解决，由于单调栈会让左右两边的边界发生变化，所以尝试使用 cdq 分治，问题转化为每次处理左边对右边的贡献

分别令 $a_j,b_j$ 表示前一半的后缀 $\max l$ 和 $\min r$、$c_i,d_i$ 表示后一半的前缀 $\max l$ 和 $\min r$，不难分类讨论 $a_j,c_i$ 和 $b_j,d_i$ 的大小关系，分为四类：

- $c_i>a_j,d_i<b_j$，有 $j\le i+1-c_i,j\ge i+1-d_i$，由于 $a_j,b_j$ 都是单调的，所以是一段区间向一个点转移，用线段树维护
- $c_i\le a_j,d_i<b_j$，有 $a_j+j\le i+1,j\ge i+1-d_i$，是一个形如 $j\in [l,r],a_j+j\le k$ 的转移，用主席树或者离线线段树维护
- $c_i>a_j,d_i\ge b_j$，有 $j\le i+1-c_i,b_j+j\ge i+1$，由于 $b_j+j$ 有单调性，所以和第一种一样，是一段区间向一个点转移
- $c_i\le a_j,d_i\ge b_j$，有 $a_j+j\le i+1,b_j+j\ge i+1$，和第二种一样由于 $b_j+j$ 有单调性，用主席树或离线线段树维护

时间复杂度 $O(n\log^2 n)$，注意初始值要弄成 `-inf`，代码写的比较丑

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e6 + 5;
const int M = N * 22;
const int P = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int n, l[N], r[N];
int a[N], b[N], c[N], d[N], pa[N], vala[N], valb[N];
int posa[N], posb[N], pospa[N], pospb[N];
pair<int, int> f[N];
int rt[N], tt;

inline void upd(pair<int, int>& x, const pair<int, int>& y) {
    if(x.fi == y.fi) x.se = (x.se + y.se) % P;
    else if(x.fi < y.fi) x = y;
}

inline void upd2(pair<int, int>& x, pair<int, int> y) {
    ++y.fi;
    if(x.fi == y.fi) x.se = (x.se + y.se) % P;
    else if(x.fi < y.fi) x = y;
}

pair<int, int> inc(const pair<int, int>& x) { return mp(x.fi + 1, x.se); }

namespace seg1 {
    int ls[M], rs[M];
    pair<int, int> val[M];

    inline int newnode(int o) {
	++tt;
	ls[tt] = ls[o];
	rs[tt] = rs[o];
	val[tt] = val[o];
	return tt;
    }

    inline void insert(int& o1, int& o2, int p, int l, int r) {
        o1 = newnode(o2);
	if(l == r) {
	    assert(val[o1] == val[0]);
	    val[o1] = f[p-1];
	    return;
	}
	int mid = l + r >> 1;
	if(p <= mid) insert(ls[o1], ls[o2], p, l, mid);
	else insert(rs[o1], rs[o2], p, mid + 1, r);

	val[o1] = mp(-inf, 0);
	upd(val[o1], val[ls[o1]]);
	upd(val[o1], val[rs[o1]]);
    }

    inline pair<int, int> query(int o, int ql, int qr, int l, int r) {
	if(ql > qr) return mp(-inf, 0);
	if(!o) return mp(-inf, 0);
	if(ql <= l && r <= qr) {
	    //cerr << "seg1 " << o << " " << l << " " << r << " " <<  val[o].fi << " " << val[o].se << "\n";
	    return val[o];
	}
	int mid = l + r >> 1;
	pair<int, int> res = mp(-inf, 0);
	if(ql <= mid) upd(res, query(ls[o], ql, qr, l, mid));
	if(mid < qr) upd(res, query(rs[o], ql, qr, mid + 1, r));
	return res;
    }
}

namespace seg2 {
    pair<int, int> val[N<<2];
    inline void build(int o, int l, int r) {
	if(l == r) {
	    val[o] = f[l-1];
	    return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	val[o] = mp(-inf, 0);
	upd(val[o], val[o << 1]);
	upd(val[o], val[o << 1 | 1]);
    }

    inline pair<int, int> query(int o, int ql, int qr, int l, int r) {
	if(ql > qr) return mp(-inf, 0);
	if(ql <= l && r <= qr) return val[o];
	int mid = l + r >> 1;
	pair<int, int> res = mp(-inf, 0);
	if(ql <= mid) upd(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) upd(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
    }
}

inline void solve(int l, int r) {
    if(l == r) {
	if(::l[l] <= 1) upd2(f[l], f[l-1]);
	return;
    }
    
    int mid = l + r >> 1;
    solve(l, mid);

    //cerr << "solve = " << l << ", " << mid << " -> " << mid + 1 << ", " << r << "\n";
    per(i, l, mid) {
	a[i] = max(a[i + 1], ::l[i]);
	b[i] = min(b[i + 1], ::r[i]);
    }
    rep(i, mid + 1, r) {
	c[i] = max(c[i - 1], ::l[i]);
	d[i] = min(d[i - 1], ::r[i]);
    }
    
    rep(i, l, mid) vala[i] = a[i] + i;
    rep(i, l, mid) valb[i] = b[i] + i;
    
    rep(i, mid + 1, r) {
	posa[i] = upper_bound(a + l, a + mid + 1, c[i], greater<int>()) - a;
	posb[i] = upper_bound(b + l, b + mid + 1, d[i]) - b;
    }
    
    // c[i] > a[j], d[i] < b[j]

    seg2::build(1, l, mid);
    rep(i, mid + 1, r) {
	int ql = l, qr = mid;
	ql = max<int>(ql, posb[i]);
	ql = max<int>(ql, posa[i]);
	ql = max(ql, i + 1 - d[i]);
	qr = min(qr, i + 1 - c[i]);
	upd2(f[i], seg2::query(1, ql, qr, l, mid));
    }
    
    //c[i] <= a[j], d[i] < b[j]

    auto compa = [&](int i, int j) { return vala[i] < vala[j]; };
    rep(i, l, mid) pa[i] = i;
    sort(pa + l, pa + mid + 1, compa);
    rep(i, l, mid) {
	seg1::insert(rt[i], rt[i-1], pa[i], l, mid);
    }

    rep(i, mid + 1, r) {
	vala[i] = i + 1;
	pospa[i] = upper_bound(pa + l, pa + mid + 1, i, compa) - pa;
	pospb[i] = lower_bound(valb + l, valb + mid + 1, i + 1) - valb;
    }
    
    rep(i, mid + 1, r) {
	int p = pospa[i] - 1;
	int ql = l, qr = mid;
	ql = max<int>(ql, posb[i]);
	ql = max(ql, i + 1 - d[i]);
	qr = min<int>(qr, posa[i] - 1);
	upd2(f[i], seg1::query(rt[p], ql, qr, l, mid));
    }
    //c[i] > a[j], d[i] >= b[j]
    rep(i, mid + 1, r) {
	int ql = l, qr = mid;
	ql = max<int>(ql, posa[i]);
	qr = min<int>(qr, posb[i] - 1);
	qr = min(qr, i + 1 - c[i]);
	ql = max<int>(ql, pospb[i]);
	upd2(f[i], seg2::query(1, ql, qr, l, mid));
    }

    rep(i, mid + 1, r) {
	int ql = l, qr = mid;
	qr = min<int>(qr, posa[i] - 1);
	qr = min<int>(qr, posb[i] - 1);
	ql = max<int>(ql, pospb[i]);
	
	int p = pospa[i] - 1;
	upd2(f[i], seg1::query(rt[p], ql, qr, l, mid));
    }
    
    rep(i, l, r) {
	vala[i] = valb[i] = a[i] = c[i] = 0;
	b[i] = d[i] = inf;
	rt[i] = 0;
    }
    tt = 0;

    solve(mid + 1, r);
}

int main() {
    // freopen("elect.in", "r", stdin);
    // freopen("elect.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 1, n) cin >> l[i] >> r[i];
    rep(i, 1, n) f[i] = mp(-inf, 0);

    memset(b, 0x3f, sizeof b);
    memset(d, 0x3f, sizeof d);
    f[0] = mp(0, 1);
    seg1::val[0] = mp(-inf, 0);

    solve(1, n);
    
    if(f[n].fi <= 0) cout << "NIE" << "\n";
    else cout << f[n].fi << " " << f[n].se << "\n";
    cout.flush();

    return 0;
}
```

---

## 作者：kyEEcccccc (赞：5)

## 更好体验

- [博客园](https://www.cnblogs.com/kyeecccccc/p/17247889.html)

- [洛谷博客](https://ky-ee.blog.luogu.org/solution-p5979)

## 简要题意

> 有 $n$ 个人，把他们划分成尽可能多的区间，其中第 $i$ 个人要求它所在的区间长度大于等于 $c_i$，小于等于 $d_i$，求最多的区间数量以及如此划分的方案数。
>
> 数据范围：$1\le n \le 10^6, 1\le c_i, d_i\le n$。时间限制 7s（优秀解 500-700ms，我的垃圾大常数实现 2s，我都觉得写假了）。

## 题解

方案数是 trivial 的，实现一个 `Data` 类，合并信息的时候同时维护最大值和方案数即可。注意信息失去了幂等性。

首先考虑朴素 DP，设 $f_i$ 表示前 $i$ 个数可以划分成的最大区间数。转移枚举上一段的端点即可。时间复杂度 $\Theta(n^2)$。

下面考虑优化。注意到线性结构，转移彼此独立，考虑分治优化。题解区许多解法似乎是标准 CDQ 分治做法，然而时间复杂度是双 $\log$ 的同时实现也较为复杂。我没有研究。

这题处理的难点在于我要同时维护 $c$ 和 $d$ 两个方向的限制，能转移到 $i$ 的所有 $j$ 分布很诡异，而 CDQ 分治并不能帮助改善这一点。而我们对于 $c, d$ 关注的只有最值。这启示我们使用最值分治的做法，将其中一个的最值对应点放到分治中心，这样所有左区间到右区间的转移都会跨越这个点，它又是最值，相当于这一维限制被固定了。观察题目可以发现，$d$ 作为上界限制，只考虑它限制下能对 $i$ 进行转移的 $j$ 一定是 $[0, i - 1]$ 的一段后缀，设为 $[pre_i, i - 1]$，这个东西很好预处理，并且很优美（注意到 $pre_i$ 不降），所以我们考虑固定 $c$，当前分治区间设为 $[l, r]$，中点设为 $mid$（注意左区间是 $[l, mid)$），那么能转移到右区间 $i$ 的 $j$ 所属区间是 $[l, mid)\cap [pre_i, i - c_{mid}]$。

然而最值分治失去了分治层数 $\log$ 的特性，一般地需要在合并时精细实现来避免退化成平方（我就退化过）。当然，分治区间总个数仍然保证是 $\Theta(n)$ 的。接下来考虑分类转移：

1. $i < l + c_mid$ 或者 $pre_i \ge mid$：很容易排除掉。

1. $pre_i < l, i - c_{mid} < mid$：区间是 $[l, mid)$ 的前缀，随着 $i$ 不断增加，右端点只会每次移动 1，那么第一次在线段树上查一下，后面就直接用 $f_j$ 来 $\Theta(1)$ 更新即可。这一部分的时间复杂度：第一次查线段树 $\Theta(n\log n)$，后面的更新次数只会是左右区间长度的 $\min$，类比启发式合并可以得到时间复杂度是 $\mathrm O(n\log n)$。

1. $pre_i < l, i - c_{mid} \ge mid$：区间是 $[l, mid)$，二分一下右边能被这样更新的 $i$，一定也是个区间，线段树上区间查一下，区间取 $max$ 一下，$\Theta(n\log n)$。

1. $pre_i \in [l, mid), i - c_{mid} \ge mid$：全部暴力 $\Theta(\log n)$，这是因为对于一个 $i$，它所属的所有分治右区间，所对应的分治左区间两两不交（可以画出分治树看一下），所以 $pre_i$ 只属于其中某一个，于是每个 $i$ 只会这样暴力转移一次。

于是这样做完了，总复杂度 $\Theta(n\log n)$。

## 代码

```cpp
// Author: kyEEcccccc

#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using ULL = unsigned long long;

#define F(i, l, r) for (int i = (l); i <= (r); ++i)
#define FF(i, r, l) for (int i = (r); i >= (l); --i)
#define MAX(a, b) ((a) = max(a, b))
#define MIN(a, b) ((a) = min(a, b))
#define SZ(a) ((int)((a).size()) - 1)

const int N = 1000005, MOD = 1000000007;

int n, c[N], d[N];

struct Data { int mx; LL s; };

Data mer(Data x, Data y)
{
	Data r = {max(x.mx, y.mx), 0};
	if (x.mx == r.mx) r.s += x.s;
	if (y.mx == r.mx) (r.s += y.s) %= MOD;
	return r;
}

struct SegTree
{
	Data x[N << 2], tg[N << 2];

	void init(int p, int cl, int cr)
	{
		x[p] = tg[p] = {-n, 0};
		if (cl == cr) return;
		int cm = cl + cr >> 1;
		init(p << 1, cl, cm);
		init(p << 1 | 1, cm + 1, cr);
	}

	void pushdown(int p)
	{
		Data d = tg[p]; tg[p] = {-n, 0};
		x[p << 1] = mer(x[p << 1], d);
		x[p << 1 | 1] = mer(x[p << 1 | 1], d);
		tg[p << 1] = mer(tg[p << 1], d);
		tg[p << 1 | 1] = mer(tg[p << 1 | 1], d);
	}

	Data get_max(int p, int cl, int cr, int l, int r)
	{
		if (l > r) return {-n, 0};
		if (cl >= l && cr <= r) return x[p];
		pushdown(p);
		int cm = cl + cr >> 1;
		if (l <= cm && r > cm)
		{
			return mer(get_max(p << 1, cl, cm, l, r),
				get_max(p << 1 | 1, cm + 1, cr, l, r));
		}
		else if (l <= cm) return get_max(p << 1, cl, cm, l, r);
		else return get_max(p << 1 | 1, cm + 1, cr, l, r);
	}

	void assign_max(int p, int cl, int cr, int l, int r, Data d)
	{
		if (l > r) return;
		if (cl >= l && cr <= r)
		{
			x[p] = mer(x[p], d), tg[p] = mer(tg[p], d);
			return;
		}
		pushdown(p);
		int cm = cl + cr >> 1;
		if (l <= cm) assign_max(p << 1, cl, cm, l, r, d);
		if (r > cm) assign_max(p << 1 | 1, cm + 1, cr, l, r, d);
		x[p] = mer(x[p << 1], x[p << 1 | 1]);
	}
} sgt;

int pre[N];
Data f[N];

struct SegTree2
{
	int x[N << 2];

	void init(int p, int cl, int cr)
	{
		if (cl == cr) return x[p] = cl, void();
		int cm = cl + cr >> 1;
		init(p << 1, cl, cm);
		init(p << 1 | 1, cm + 1, cr);
		if (c[x[p << 1]] > c[x[p << 1 | 1]]) x[p] = x[p << 1];
		else x[p] = x[p << 1 | 1];
	}

	int get_max(int p, int cl, int cr, int l, int r)
	{
		if (cl >= l && cr <= r) return x[p];
		int cm = cl + cr >> 1;
		if (l <= cm && r > cm)
		{
			int a = get_max(p << 1, cl, cm, l, r),
				b = get_max(p << 1 | 1, cm + 1, cr, l, r);
			return c[a] > c[b] ? a : b;
		}
		else if (l <= cm) return get_max(p << 1, cl, cm, l, r);
		else return get_max(p << 1 | 1, cm + 1, cr, l, r);
	}
} sgt2;

void solve(int l, int r)
{
	if (l == r)
	{
		Data t = f[l];
		f[l] = mer(f[l], sgt.get_max(1, 0, n, l, l));
		sgt.assign_max(1, 0, n, l, l, t);
		return;
	}

	int mid = sgt2.get_max(1, 1, n, l + 1, r) - 1, mxc = c[mid + 1];

	solve(l, mid);

	int p = max(mid + 1, l + mxc);
	Data cur_x = {INT_MIN, 0};
	while (p <= r && p - mxc < mid && pre[p] <= l)
	{
		if (cur_x.mx == INT_MIN) cur_x = sgt.get_max(1, 0, n, l, p - mxc);
		else cur_x = mer(cur_x, f[p - mxc]);
		Data x = cur_x; ++x.mx;
		f[p] = mer(f[p], x);
		++p;
	}
	if (p > r) goto SOLVE_R;

	if (pre[p] <= l)
	{
		int cl = p, cr = r, ca = p;
		while (cl <= cr)
		{
			int cm = cl + cr >> 1;
			if (pre[cm] <= l) ca = cm, cl = cm + 1;
			else cr = cm - 1;
		}
		Data x = sgt.get_max(1, 0, n, l, mid); ++x.mx;
		sgt.assign_max(1, 0, n, p, ca, x);
		p = ca + 1;
	}
	if (p > r) goto SOLVE_R;

	while (p <= r && pre[p] <= mid)
	{
		Data x = sgt.get_max(1, 0, n, pre[p], min(mid, p - mxc));
		++x.mx;
		f[p] = mer(f[p], x);
		++p;
	}

	SOLVE_R: solve(mid + 1, r);
}

struct SegTree3
{
	int x[N << 2];

	void init(int p, int cl, int cr)
	{
		if (cl == cr) return x[p] = d[cl], void();
		int cm = cl + cr >> 1;
		init(p << 1, cl, cm);
		init(p << 1 | 1, cm + 1, cr);
		x[p] = min(x[p << 1], x[p << 1 | 1]);
	}

	int get_min(int p, int cl, int cr, int l, int r)
	{
		if (cl >= l && cr <= r) return x[p];
		int cm = cl + cr >> 1;
		if (l <= cm && r > cm)
		{
			return min(get_min(p << 1, cl, cm, l, r),
				get_min(p << 1 | 1, cm + 1, cr, l, r));
		}
		else if (l <= cm) return get_min(p << 1, cl, cm, l, r);
		else return get_min(p << 1 | 1, cm + 1, cr, l, r);
	}
} sgt3;

signed main(void)
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr);

	cin >> n;
	F(i, 1, n) cin >> c[i] >> d[i];

	sgt3.init(1, 1, n);
	pre[1] = 0;
	F(i, 2, n)
	{
		pre[i] = pre[i - 1];
		while (sgt3.get_min(1, 1, n, pre[i] + 1, i) < i - pre[i]) ++pre[i];
		// cout << i << ": " << pre[i] << '\n';
	}

	f[0] = {0, 1};
	F(i, 1, n) f[i] = {-n, 0};
	sgt.init(1, 0, n);

	sgt2.init(1, 1, n);
	solve(0, n);

	// F(i, 0, n) cout << i << ": " << f[i].mx << ' ' << f[i].s << '\n';

	if (f[n].s == 0) cout << "NIE" << endl;
	else cout << f[n].mx << ' '  << f[n].s << endl;
	
	return 0;
}
```

---

## 作者：juicyyou (赞：5)

模拟赛的题，场上没调完，破防了。

先考虑如果没有 $c_i$ 这个限制我们该怎么做，这个问题显然是一个普及组题目，设 $f_i$ 表示到 $i$ 的最大段数，$g_i$ 表示 $f_i$ 的方案，由于只有 $d_i$ ，转移显然是一段区间，直接线段树即可。

但是当我们加入了 $c_i$ 之后，转移就不再是一段区间，所以我们要考虑怎么去掉这个限制。

容易想到分治进行转移，但是普通的 CDQ 分治转移难以处理下界限制，所以我们考虑按照笛卡尔树的结构进行分治，这样的话左边到右边的转移的限制就是当前这棵子树的根的限制。

于是很容易想到类似于 CDQ，枚举右子树里的点。预处理出只考虑 $l_i$ 表示如果 $i$ 作为右端点且不考虑 $c_i$ 的限制，其左端点最远能到哪里，$r_i$ 同理。那么在右子树里每个点的转移都是左子树的一段区间，于是只用一棵线段树即可。

但这样的复杂度是不对的，因为笛卡尔树并不是平衡的。上面的做法当左子树大小小于右子树大小时没有复杂度保证，可能会退化成 $O(n^2 \log n)$。

所以我们考虑类似于启发式合并的方法，在这种情况下枚举左子树转移右子树，容易发现转移依旧是一段区间，于是我们考虑如何维护。

具体的，我们要实现这么一个数据结构：

+ 单点查询

+ 将一个区间内的数和 $x$ 取 max，同时维护其 max 方案数

显然可以使用线段树维护，所以我们只需写两棵线段树即可。

用类似于启发式合并的分析可以得知，复杂度就是 $O(n \log^2 n)$ 的，可以通过。

代码可能写的比较丑。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
int n, L[maxn], R[maxn];
inline int add(int x, int y){
    return x + y >= mod ? x + y - mod : x + y;
}
struct Node{
    int x, y;
    Node(int xx = 0, int yy = 0){
        x = xx; y = yy;
    }
    Node friend operator+(Node n1, Node n2){
        if(n1.y == 0 && n2.y == 0) return Node(-inf, 0);
        if(n1.y == 0) return n2;
        if(n2.y == 0) return n1;
        if(n1.x == n2.x) return Node(n1.x, add(n1.y, n2.y));
        if(n1.x < n2.x) return n2;
        return n1;
    }
};
struct TreeNode{
    Node mx; Node sum;
};
TreeNode t[maxn << 2];
void pushup(int p){
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum; return ;
}
void build(int p, int l, int r){
    t[p].mx = Node(-inf, 0); t[p].sum = Node(-inf, 0);
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
    return ;
}
void upd(int p, int pl, int pr, int l, int r, int x, int v){
    if(pl <= l && r <= pr){
        // cerr << pl << " " << pr << " " << x << " " << v << endl;
        t[p].mx = t[p].mx + Node(x, v); // cerr << t[p].mx.x << endl;
        return ;
    }
    int mid = (l + r) >> 1;
    if(pl <= mid) upd(p << 1, pl, pr, l, mid, x, v);
    if(pr > mid) upd(p << 1 | 1, pl, pr, mid + 1, r, x, v);
    return ;
}
void upd1(int p, int l, int r, int x, Node v){
    if(l == r){
        // cerr << "! " << x << " " << v.x << " " << v.y << endl;
        t[p].sum = v; return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) upd1(p << 1, l, mid, x, v);
    if(x > mid) upd1(p << 1 | 1, mid + 1, r, x, v);
    pushup(p); // cerr << ":: " << l << " " << r << " " << t[p].sum.x << endl;
    return ;
}
Node que1(int p, int pl, int pr, int l, int r){
    if(pl > pr) return Node(-inf, 0);
    if(pl <= l && r <= pr) return t[p].sum;
    int mid = (l + r) >> 1; Node res = Node(-inf, 0);
    if(pl <= mid) res = res + que1(p << 1, pl, pr, l, mid);
    if(pr > mid) res = res + que1(p << 1 | 1, pl, pr, mid + 1, r);
    return res;
}
Node que(int p, int l, int r, int x){
    if(l == r) return t[p].mx;
    int mid = (l + r) >> 1; Node res = t[p].mx;
    if(x <= mid) res = res + que(p << 1, l, mid, x);
    if(x > mid) res = res + que(p << 1 | 1, mid + 1, r, x);
    return res;
}
int st[maxn][21], mlg[maxn];
int rmq(int x, int y){
    int len = mlg[y - x + 1];
    return min(st[x][len], st[y - (1 << len) + 1][len]);
}
int rl[maxn], rr[maxn];
int stk[maxn], top = 0; int rt = 0; int son[maxn][2];
int sum[maxn]; int lp[maxn], rp[maxn];
void init(int now){
    if(now == 0) return ;
    init(son[now][0]); init(son[now][1]);
    lp[now] = son[now][0] ? lp[son[now][0]] : now;
    rp[now] = son[now][1] ? rp[son[now][1]] : now;
    return ;
}
int sz(int now){
    if(now == 0) return 0;
    return rp[now] - lp[now] + 1;
}
void dfs(int now){
    if(now == 0) return ;
    dfs(son[now][0]);
    int szl = sz(son[now][0]); int szr = sz(son[now][1]);
    if(szl > szr){
        for(int i = now;i <= rp[now];i++){
            int lt = max(rl[i], lp[now]);
            int rt = min(now, i - L[now] + 1);
            if(rt < lp[now] || rt < lt) continue;
            Node val = que1(1, lt - 1, rt - 1, 0, n);
            upd(1, i, i, 0, n, val.x + 1, val.y);
            // cerr << lt - 1 << " " << rt - 1 << " -> " << i << " " << val.y << endl;
        }
    }
    if(szl <= szr){
        for(int i = lp[now] - 1;i < now;i++){
            Node val = que(1, 0, n, i);
            int lt = max(now, i + L[now]);
            int rt = min(rr[i + 1], rp[now]);
            // cerr << i << " " << now << " " << lt << " " << rp[now] << endl;
            if(lt > rp[now] || rt < lt) continue;
            upd(1, lt, rt, 0, n, val.x + 1, val.y);
            // cerr << i << " -> " << lt << " " << rt << endl;
        }
    }
    Node nowval = que(1, 0, n, now); upd1(1, 0, n, now, nowval);
    dfs(son[now][1]); return ;
}
int main(){
    // freopen("elect.in", "r", stdin);
    // freopen("tmp.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> L[i] >> R[i]; st[i][0] = R[i];
    }
    for(int j = 1;(1 << j) <= n;j++){
        for(int i = 1;i + (1 << j) - 1 <= n;i++){
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    mlg[1] = 0;
    for(int i = 1;i <= n;i++){
        mlg[i] = mlg[i - 1] + ((1 << (mlg[i - 1] + 1)) == i);
    }
    for(int i = 1;i <= n;i++){
        int pl = i, pr = n, res = i;
        while(pl <= pr){
            int mid = (pl + pr) >> 1;
            if(rmq(i, mid) >= mid - i + 1){
                res = mid; pl = mid + 1;
            } else {
                pr = mid - 1;
            }
        }
        rr[i] = res; pl = 1; pr = i; res = i;
        while(pl <= pr){
            int mid = (pl + pr) >> 1;
            if(rmq(mid, i) >= i - mid + 1){
                res = mid; pr = mid - 1;
            } else {
                pl = mid + 1;
            }
        }
        rl[i] = res;
    }
    // cerr << "ok" << endl;
    for(int i = 1;i <= n;i++){
        int las = 0;
        while(top && L[stk[top]] <= L[i]){
            son[stk[top]][1] = las; las = stk[top]; top--;
        }
        son[i][0] = las; stk[++top] = i;
    }
    while(top > 1){
        son[stk[top - 1]][1] = stk[top]; top--;
    }
    rt = stk[1];
    // for(int i = 1;i <= n;i++) cerr << son[i][0] << " " << son[i][1] << endl;
    build(1, 0, n); upd(1, 0, 0, 0, n, 0, 1);
    upd1(1, 0, n, 0, Node(0, 1));
    init(rt); dfs(rt);
    Node val = que(1, 0, n, n);
    if(val.y == 0) cout << "NIE" << endl;
    else cout << val.x << " " << val.y << endl;
    return 0;
}
```

---

## 作者：lndjy (赞：5)

首先，容易得到一个朴素 dp：设 $f_i$ 为前 $i$ 个人划分的最大组，枚举最后一次划分点，有

$$f_i=\max(f_j+1)(\max(c_{j+1},c_{j+2}...c_i)\le i-j\le \min(d_{j+1},d_{j+2}...d_i))$$

对于计数，设 $g_i$ 为 $f_i$ 取最大值的方案数，把所有能让 $f$ 取最大值的转移的 $g$ 加起来即可。

考虑分治优化。

记当前区间为 $[l,r]$。

首先找到 $[l+1,r]$ 中 $c_k$ 最大的 $k$，先递归处理 $[l,k-1]$，然后考虑 $[l,k-1]$ 对 $[k,r]$ 的贡献，最后递归处理 $[k,r]$。

这样处理有一个性质：$[l,k-1]$ 对 $[k,r]$ 更新时，$c$ 最大的值永远是 $c_k$，这样就压了一个限制。

对于左区间长度更长的情况，枚举右区间的每个点 $i$，则左区间内**能更新这个点** $j$ 的最小值是 $\min(k-1,i-c_k)$，最大值是 $\max(l,lim_i)$。其中 $lim_i$ 为最大的满足 $d$ 限制的 $j$。

对于右区间长度更长的情况，枚举左区间的每个点 $j$，则右区间内**能被这个点更新**的 $i$ 的最小值是 $\max(k,j+c_k)$，最大值是 $\min(r,lim2_j)$。其中 $lim2_j$ 为最大的满足 $d$ 限制的 $i$。

对于 $lim,lim2$ 的处理，可以推出来有单调性，双指针 +multiset 可以在 $O(nlogn)$ 的复杂度预处理。

用线段树维护 $f$ 和 $g$，我们需要支持以下操作：

1. 查询区间 $c$ 最大值和位置。
2. 查询区间 $f$ 最大值。
3. 区间 $f$ 与一个数取 $\max$ 并维护 $g$。

复杂度证明类似启发式分裂，每层用较小区间的复杂度处理。

然后如果你和我一样大常数，可能需要一个剪枝：枚举右区间 $lim_i\ge k$ 时，或者枚举左区间 $i+c_k\ge r$ 时，之后也不会有合法的区间，直接 `break`。

代码比较丑，就不放了。

---

## 作者：Masterwei (赞：4)

CDQ 分治优化 dp。

首先是一个朴素 dp：我们设 $f_i$ 表示到 $i$ 的最大值和方案数组成的二元组，那么我们有如下转移：$f_i=\displaystyle\sum_{j=1}^{i}[\max_{j\le k\le i} c_k\le i-j+1\le \min_{j\le k\le i} d_k]f_{j-1}$。

这个是 $O(n^2)$ 的，且不好直接优化转移，考虑用 CDQ 分治来优化。

我们设 $solve(l,r)$ 表示解决了 $[l,r]$ 内的转移，考虑用 $[l,mid]$ 的 dp 值去转移到 $[mid+1,r]$。

发现最开始转移的区间 $\max$ 和 $\min$ 的条件可以通过 $mid$ 分成两个类似的条件，也就是我们要从 $j$ 转移到 $i$，就要满足：

$\displaystyle\max_{j\le k\le mid} c_k\le i-j+1\le \min_{j\le k\le mid} d_k$

和

$\displaystyle\max_{mid+1\le k\le i} c_k\le i-j+1\le \min_{mid+1\le k\le i} d_k$。

稍微对如上式子进行一下移项，就变成了：

$\displaystyle\max_{j\le k\le mid} c_k+j-1\le i\le \min_{j\le k\le mid} d_k+j-1$

和

$\displaystyle i+1-\min_{mid+1\le k\le i} d_k\le j\le i+1-\max_{mid+1\le k\le i} c_k$。

可以发现我们能分别处理这两个条件。具体地，我们对于所有的 $j\in [l,mid]$，将对应可行的 $i$ 的区间进行差分，然后扫描线，对于所有的 $i\in [mid+1,r]$，直接区间查询对应可行的 $j$ 的区间即可。这样我们就同时满足了这两个条件。

由于要区间询问，且这个二元组的加法运算不支持撤销，所以只能用线段树。

时间复杂度 $O(n\log^2n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e6+5,mod=1e9+7,inf=1e9;
int n;
struct node{
	int c,d;
}a[Maxn];
struct Node{
	int mx,cnt;
	inline Node operator+(const Node&b)const{
		if(b.mx==mx)return (Node){mx,(cnt+b.cnt)%mod};
		if(b.mx>mx)return b;return (Node){mx,cnt};
	}
}f[Maxn],t[Maxn<<2];
void build(int x,int l,int r){
	t[x]=(Node){-inf,0};if(l==r)return;
	int mid=l+r>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}
void change(int x,int l,int r,int d,Node p){
	if(l==r)return void(t[x]=p);
	int mid=l+r>>1;
	if(mid>=d)change(x<<1,l,mid,d,p);
	else change(x<<1|1,mid+1,r,d,p);
	t[x]=t[x<<1]+t[x<<1|1];
}
Node query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x];
	int mid=l+r>>1;
	if(mid>=L&&mid<R)return query(x<<1,l,mid,L,R)+query(x<<1|1,mid+1,r,L,R);
	if(mid>=L)return query(x<<1,l,mid,L,R);
	return query(x<<1|1,mid+1,r,L,R);
}
vector<int>g[Maxn];
int c[Maxn],d[Maxn];
void solve(int l,int r){
	if(l==r){
		if(a[l].c==1){Node tmp=f[l-1];tmp.mx++;f[l]=f[l]+tmp;}
		return;
	}
	int mid=l+r>>1;solve(l,mid);
	for(int i=l;i<=r+1;i++)g[i].clear();
	c[mid+1]=0;d[mid+1]=inf;
	for(int i=mid;i>=l;i--){
		c[i]=max(a[i].c,c[i+1]);d[i]=min(a[i].d,d[i+1]);
		int L=max(mid+1,c[i]+i-1),R=min(d[i]+i-1,r);
		if(L<=R){
			g[L].emplace_back(i);
			g[R+1].emplace_back(-i);
		}
	}
	for(int i=mid+1;i<=r+1;i++){
		for(int j:g[i]){
			if(j<0)change(1,0,n,-j,(Node){-inf,0});
			else change(1,0,n,j,f[j-1]);
		}if(i==r+1)break;
		c[i]=max(a[i].c,c[i-1]);d[i]=min(d[i-1],a[i].d);
		int L=max(l,i-d[i]+1),R=min(i-c[i]+1,mid);
		if(L<=R){Node tmp=query(1,0,n,L,R);tmp.mx++;f[i]=f[i]+tmp;}
	}solve(mid+1,r);
}
int main(){
	n=read();build(1,0,n);change(1,0,n,0,(Node){0,1});f[0]=(Node){0,1};
	for(int i=1;i<=n;i++)f[i]=(Node){-inf,0};
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	solve(1,n);
	if(f[n].mx<=0)puts("NIE");
	else printf("%d %d\n",f[n].mx,f[n].cnt);
	return 0;
}


```

---

## 作者：CQ_Bab (赞：3)

# 前言
第一道自己做出来的黑题，当然是要记录一下的。
# 思路
首先你能想出一个 $n^2$ 的 dp，我们定义 $f_i,g_i$ 表示以 $i$ 结尾的最多能分的段数以及方案数，然后转移就是 $f_i=\max(f_{j-1}+1)$ 其中 $j-i+1\leq \min(d_i\sim d_j),j-i+1\geq \max(c_i\sim c_j)$，有了这两个式子我们就可以一下想到分治维护 dp 了，这里只需要分类讨论四种情况即可。

下面我们设分治区间为 $l\sim mid\sim r$ 然后 $\min(d_i\sim d_j)=mn,mx=\max(c_i,c_j)$ 以及 $l1,r1$ 表示使得 $\min(d_{l1}\sim d_j)=\min(d_{mid+1}\sim d_j)$ 最小的 $l1$，$r1$ 也同理，还有 $i,j$ 表示转移过来的下标和被转移点的下标。

- 如果 $mx,mn$ 都在 $mid+1\sim r$ 这一段中，我们可以把式子化为 $j+1-mx\geq i,j-mn+1\leq i$ 因为要满足 $mx,mn$ 都在 $mid+1\sim r$ 中所以 $i\geq \max(l1,r1)$，相当于在一段区间中求 $f_{i-1}$ 的最大值以及方案数之和，可以用线段树轻松处理。
- 如果 $mx,mn$ 都在 $l\sim mid$ 中，那么首先需要满足 $i<\min(l1,r1)$ 然后还以化式子 $j+1\leq mn+i,j+1\geq mx+i$ 那么我们发现这是求一个前缀中满足 $j+1\leq nm+i,j+1\geq mx+i$ 的 $f_{i-1}$ 的最大值，那么我们直接把 $j+1$ 挂在 $\min(l1,r1)-1$ 那个位置上查询 $j+1$ 的答案每次修改 $mx+i\sim mn+i$ 这一段区间的最大值即可。
- 然后就是两种分居两边的情况了，其实这两种情况类似讲了一种应该就懂了，我们设 $l1<r1$ 那么我们发现只会出现 $mx$ 在 $l\sim mid$ 中 $mn$ 在 $mid+1\sim r$ 中的情况，那么我们依旧考虑话式子 $j-mn+1\leq i,j+1\geq mx+i$ 考虑一下这个式子的形式 $i\geq \max(j-mn+1,l1),i<r1,j+1\geq mx+i$ 那么对于这个三维偏序考虑离线按 $j+1$ 以及 $mx+i$ 排序对于修改就把 $f_{i-1}$ 修改到 $i$ 上如果是查询就查询 $\max(j-mn+1,l1)\sim r1-1$ 这一段的最大值即可。
- 另一种情况类似也是离线就可以处理了。

这种做法常数比较大，所以略需要卡常，这种处理方案数的线段树切记只能处理区间修改和单点查询或者区间查询单点修改的情况，上述正好是这两种情况所以也是很好处理的。

由于需要卡常所以在区间长度小于 $200$ 的时候还是跑暴力更优。
# 代码
~~石山代码~~。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
constexpr int bufsize = 230005;
char *f1, *f2, buf[bufsize];
char gtchar() {return f1 == f2 && (f1 = buf + fread(f2 = buf, 1, bufsize, stdin)) == buf? EOF: *f2++;}
template<class T> il void in(T &x) {
    x = 0; char ch = gtchar();
    while (ch < '0' || ch > '9') {ch = gtchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = gtchar(); }
}
int T=1;
const int N=1e6+10,mod=1e9+7,inf=1e9;
int f[N];
int g[N];
int c[N],d[N];
int n;
struct nodek{
	int l,r;
	int mx,mn;
}t1[N<<2];
il void up2(int x) {
	t1[x].mx=max(t1[x<<1].mx,t1[x<<1|1].mx);
	t1[x].mn=min(t1[x<<1].mn,t1[x<<1|1].mn);
}
il void build(int u,int l,int r) {
	t1[u]={l,r};
	if(l==r) {
		t1[u].mx=c[l];
		t1[u].mn=d[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	up2(u);
}
il int Ansc(int u,int l,int r) {
	if(t1[u].l>=l&&t1[u].r<=r) {
		return t1[u].mx;
	}
	int mid=t1[u].l+t1[u].r>>1;
	int res=0;
	if(mid>=l) res=Ansc(u<<1,l,r);
	if(mid<r) res=max(res,Ansc(u<<1|1,l,r));
	return res;
}
il int Ansd(int u,int l,int r) {
	if(t1[u].l>=l&&t1[u].r<=r) {
		return t1[u].mn;
	}
	int mid=t1[u].l+t1[u].r>>1;
	int res=inf;
	if(mid>=l) res=Ansd(u<<1,l,r);
	if(mid<r) res=min(res,Ansd(u<<1|1,l,r));
	return res;
}
struct node{
	int mx;
	int cnt;
}tr[N<<2];
il void up(int x) {
	tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);
	tr[x].cnt=0;
	if(tr[x].mx==tr[x<<1].mx) tr[x].cnt=tr[x<<1].cnt;
	if(tr[x].mx==tr[x<<1|1].mx) tr[x].cnt+=tr[x<<1|1].cnt,tr[x].cnt%=mod;
}
il void modify(int u,int l,int r,int x,int f,int g) {
	if(l==r) {
		tr[u].mx=f;
		tr[u].cnt=g;
		return;
	}
	int mid=l+r>>1;
	if(mid>=x) modify(u<<1,l,mid,x,f,g);
	else modify(u<<1|1,mid+1,r,x,f,g);
	up(u);
}
il pair<int,int> Ans(int u,int l,int r,int ql,int qr) {
	if(ql>qr) return {-inf,0};
	if(l>=ql&&r<=qr) {
		return {tr[u].mx,tr[u].cnt};
	}
	int mid=l+r>>1;
	pair<int,int>res={-inf,0};
	if(mid>=ql) res=Ans(u<<1,l,mid,ql,qr);
	if(mid<qr) {
		pair<int,int>res1=Ans(u<<1|1,mid+1,r,ql,qr);
		if(res.first==res1.first) res.second+=res1.second,res.second%=mod;
		else if(res.first<res1.first) res=res1;
	}
	return res;
}
struct nodes{
	int mx;
	int cnt;
}tt[N*4];
il void clr(int u,int l,int r,int l1,int r1) {
	if(l1>r1) return;
	tt[u]={-inf,0};
	if(l>=l1&&r<=r1) return;
	int mid=l+r>>1;
	if(mid>=l1) clr(u<<1,l,mid,l1,r1);
	if(mid<r1) clr(u<<1|1,mid+1,r,l1,r1);
}
#define xwe cute
vector<int>v[N];
il void modify(int u,int l,int r,int ml,int mr,int k,int cnt) {
	if(l>=ml&&r<=mr) {
		if(tt[u].mx==k) tt[u].cnt+=cnt,tt[u].cnt%=mod;
		else if(tt[u].mx<k) {
			tt[u].cnt=cnt;
			tt[u].mx=k;
		}
		return;
	}
	int mid=l+r>>1;
	if(mid>=ml) modify(u<<1,l,mid,ml,mr,k,cnt);
	if(mid<mr) modify(u<<1|1,mid+1,r,ml,mr,k,cnt);
}
il pair<int,int> Ans(int u,int l,int r,int k) {
	pair<int,int>res={tt[u].mx,tt[u].cnt};
	if(l==r) return res;
	int mid=l+r>>1;
	if(mid>=k) {
		pair<int,int>lst=Ans(u<<1,l,mid,k);
		if(lst.first==res.first) res.second=(res.second+lst.second)%mod;
		else if(lst.first>res.first) res=lst;
	}else{
		pair<int,int>lst=Ans(u<<1|1,mid+1,r,k);
		if(lst.first==res.first) res.second=(res.second+lst.second)%mod;
		else if(lst.first>res.first) res=lst;
	}
	return res;
}
struct node1{
	int val,f;
	int l,r,id;
	il friend bool operator<(const node1&a,const node1&b) {
		if(a.val!=b.val) return a.val<b.val;
		return a.f<b.f;
	}
}s[N];
struct node2{
	int val,f;
	int l,r,id;
	il friend bool operator<(const node2&a,const node2&b) {
		if(a.val!=b.val) return a.val>b.val;
		return a.f<b.f;
	}
}s1[N];
int idx,idx1;
il void clr1(int u,int l,int r,int x) {
	tr[u]={-inf,0};
	if(l==r) return;
	int mid=l+r>>1;
	if(mid>=x) clr1(u<<1,l,mid,x);
	else clr1(u<<1|1,mid+1,r,x);
}
int gc[N],gd[N];
il void cdq(int l,int rr) {
	if(l==rr) {
		return;
	}
	int mid=l+rr>>1;
	cdq(l,mid);
	if(c[mid+1]<=1) {
		pair<int,int>gg={f[mid],g[mid]};
		if(gg.first+1>f[mid+1]) f[mid+1]=gg.first+1,g[mid+1]=gg.second;
		else if(gg.first+1==f[mid+1]) g[mid+1]=(g[mid+1]+gg.second)%mod;
	}
	if(rr-l+1<=200) {
		int gmx=0,gmn=inf;
		rep(i,mid+1,rr) {
			gmx=max(gmx,c[i]);
			gmn=min(gmn,d[i]);
			int mx=gmx,mn=gmn;
			rep1(j,mid,l) {
				mx=max(mx,c[j]);
				mn=min(mn,d[j]);
				if(mx>mn) break;
				if(i-j+1>=mx&&i-j+1<=mn) {
					if(f[j-1]+1>f[i]) {
						f[i]=f[j-1]+1;
						g[i]=g[j-1];
					}else if(f[j-1]+1==f[i]) g[i]=(g[i]+g[j-1])%mod;
				}
			}
		}
	}else{
		idx=idx1=false;
		rep(i,l,mid) clr1(1,1,n,i);
		rep(i,l,mid) modify(1,1,n,i,f[i-1],g[i-1]);
		int mx=0,mn=inf;
		rep(i,l,mid) v[i].clear();
		int cres=mid+1,dres=mid+1;
		int mxx=false,mnn=inf;
		rep(i,mid+1,rr) {
			mx=max(mx,c[i]);
			mn=min(mn,d[i]);
			if(mx>mn) break;
			while(max({mxx,mx,c[cres-1]})==mx&&cres>l) {
				mxx=max(mxx,c[cres-1]);
				cres--;
			}
			while(min({mnn,mn,d[dres-1]})==mn&&dres>l) {
				mnn=min(mnn,d[dres-1]);
				dres--;
			}
			int p1=max({dres,cres,i-mn+1});
			pair<int,int>res=Ans(1,1,n,p1,i-mx+1); 
			if(f[i]<res.first+1) f[i]=res.first+1,g[i]=res.second;
			else if(f[i]==res.first+1) g[i]+=res.second,g[i]%=mod;
			int p2=min({dres,cres})-1;
			if(p2>=l&&p2<=mid) v[p2].pb({i});
			if(dres==cres) continue;
			if(dres<cres) {
				int ll1=max(i-mn+1,dres),rr=cres-1;
				if(ll1<=rr) s[++idx]={i+1,1,ll1,rr,i};
			}else {
				int ll1=cres,rr=min(dres-1,i-mx+1);
				if(ll1<=rr) s1[++idx1]={i+1,1,ll1,rr,i};
			}
		}
		rep(i,l,mid) clr1(1,1,n,i);
		rep(i,l,mid) gc[i]=Ansc(1,i,mid),gd[i]=Ansd(1,i,mid),s[++idx]={i+gc[i],0,0,0,i},s1[++idx1]={gd[i]+i,0,0,0,i};
		stable_sort(s+1,s+1+idx);
		stable_sort(s1+1,s1+1+idx1);
		rep(i,1,idx) {
			if(s[i].f==0) {
				modify(1,1,n,s[i].id,f[s[i].id-1],g[s[i].id-1]);
			}else {
				pair<int,int>res=Ans(1,1,n,s[i].l,s[i].r);
				res.first++;
				if(f[s[i].id]<res.first) f[s[i].id]=res.first,g[s[i].id]=res.second;
				else if(f[s[i].id]==res.first) g[s[i].id]=(g[s[i].id]+res.second)%mod;
			}
		}
		rep(i,l,mid) clr1(1,1,n,i);
		rep(i,1,idx1) {
			if(s1[i].f==0) {
				modify(1,1,n,s1[i].id,f[s1[i].id-1],g[s1[i].id-1]);
			}else {
				pair<int,int>res=Ans(1,1,n,s1[i].l,s1[i].r);
				res.first++;
				if(f[s1[i].id]<res.first) f[s1[i].id]=res.first,g[s1[i].id]=res.second;
				else if(f[s1[i].id]==res.first) g[s1[i].id]=(g[s1[i].id]+res.second)%mod;
			}
		}
		rep(i,l,mid) {
			if(gc[i]+i<=min(n+1,gd[i]+i)) modify(1,1,n+1,gc[i]+i,min(n+1,gd[i]+i),f[i-1],g[i-1]);
			for(auto to:v[i]) {
				pair<int,int>res=Ans(1,1,n+1,to+1);
				if(f[to]<res.first+1) f[to]=res.first+1,g[to]=res.second;
				else if(f[to]==res.first+1) g[to]+=res.second,g[to]%=mod;
			}
		}
		rep(i,l,mid) clr(1,1,n+1,gc[i]+i,min(n+1,gd[i]+i));
	}
	cdq(mid+1,rr);
}
il void solve() {
	in(n);
	rep(i,1,n) in(c[i]),in(d[i]);
	memset(f,-0x3f,sizeof f);
	f[0]=0;
	g[0]=1;
	if(c[1]<=1) {
		f[1]=1;
		g[1]=1;
	}
	build(1,1,n);
	rep(i,1,n) clr1(1,1,n,i),clr(1,1,n+1,i,i);
	clr(1,1,n+1,n+1,n+1);
	cdq(1,n);
	if(f[n]<0) puts("NIE");
	else print(f[n]),putchar(' '),print(g[n]);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```
行稳致远。

---

## 作者：Lucyna_Kushinada (赞：2)

# P5979 [PA 2014] Druzyny

## 题意

有 $n$ 个人排成一行（从 $1$ 到 $n$ 编号），把他们分成若干组，每一组都是编号连续的一段，每个人属于且仅属于一个组。

第 $i$ 个人期望它所在的组的人数 $\in [c_i,d_i]$，否则这个分组方案就是不合法的。

求可以分成的组的数目的最大值，以及有多少种分组方案能达到最大值。

## 题解

知识点：动态规划，扫描线，线段树，cdq 分治。

远古疑难杂症，年初的时候写了发暴力就跑路了，今天来解决它。

设 $f_i$ 表示考虑了前 $i$ 个，最多能分多少组。

设 $g_i$ 表示考虑了前 $i$ 个，在最优分组数的前提下的有多少种方案。

假设 $j-1$ 能转移到 $i$（即将 $j\sim i$ 分为一组），则应该满足以下条件：

$$\max_{k=j}^i c_k \le i-j+1 \le \max_{k=j}^i d_k$$

非常棘手的条件，每一项都有 $i,j$，直接做根本优化不了，我们想要的的条件应该是每一项只有 $i$ 或者 $j$。

这时候就可以考虑 cdq 分治了，设当前局面为区间 $[l,r]$，设定一个 $mid$，使 $j\in [l,mid]$，$i\in [mid+1,r]$。

则上面的条件可以拆为两个：

$$\max_{k=j}^{mid} c_k \le i-j+1 \le \max_{k=j}^{mid} d_k$$

$$\max_{k=mid+1}^i c_k \le i-j+1 \le \max_{k=mid+1}^i d_k$$

然后进行移项得到：

$$\max_{k=j}^{mid} c_k +j-1 \le i \le \max_{k=j}^{mid} d_k +j-1$$

$$-\max_{k=mid+1}^i d_k+i+1\le j \le -\max_{k=mid+1}^i c_k +i+1$$

可以发现这两个条件都是每一项只有 $i$ 或者 $j$，这意味着我们可以分开处理。

对于 $j$，通过处理第一个条件可以划定满足条件的 $i$，计算出区间，用扫描线简单维护。

对于 $i$，通过处理第二个条件可以选定满足条件的 $j$，直接计算出区间，去扫描线维护的线段树上询问即可。

时间复杂度 $O(n \log^2 n)$。

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

#define N 1002506
#define int long long

const int mod=1e9+7;
int n,c[N],d[N];
pr dp[N];
vector<int>ad[N],dl[N];

inline pr mg(pr x,pr y){
    if(x.fi==y.fi){
        return {x.fi,(x.se+y.se)%mod};
    }

    if(x.fi>y.fi){
        return x;
    }

    return y;
}

struct segt{
    #define mid ((l+r)>>1)

    pr tr[N<<2];
    
    inline void build(int k,int l,int r){
        tr[k]={-1e18,0};

        if(l==r){
            return;
        }

        build(k*2,l,mid);
        build(k*2+1,mid+1,r);
    }

    inline void upd(int L,int k,int l,int r,pr d){
        if(l==r){
            tr[k]=d;
            return;
        }

        if(L<=mid){
            upd(L,k*2,l,mid,d);
        }
        else{
            upd(L,k*2+1,mid+1,r,d);
        }

        tr[k]=mg(tr[k*2],tr[k*2+1]);
    }

    inline pr ask(int L,int R,int k,int l,int r){
        if(L<=l&&R>=r){
            return tr[k];
        }

        pr ans={-1e18,0};

        if(L<=mid){
            ans=mg(ans,ask(L,R,k*2,l,mid));
        }
        if(R>mid){
            ans=mg(ans,ask(L,R,k*2+1,mid+1,r));
        }

        return ans;
    }

    #undef mid
}t;

inline void cdq(int l,int r){
    if(l==r){
        if(c[l]>1){
            return;
        }

        pr pre=dp[l-1];
        pre.fi++;

        dp[l]=mg(dp[l],pre);

        return;
    }

    int mid=(l+r)>>1;

    cdq(l,mid);

    int C=0,D=1e9;
    per(i,l,mid){
        C=max(c[i],C);
        D=min(d[i],D);

        int L=max(mid+1,C+i-1),R=min(r,D+i-1);

        if(L<=R){
            ad[L].pb(i);
            dl[R+1].pb(i);
        }
    }

    C=0,D=1e9;

    rep(i,mid+1,r+1){
        for(int x:ad[i]){
            t.upd(x,1,0,n,dp[x-1]);
        }
        for(int x:dl[i]){
            t.upd(x,1,0,n,{(int)-1e18,0});
        }

        C=max(c[i],C);
        D=min(d[i],D);

        int L=max(l,i+1-D),R=min(mid,i+1-C);

        if(L<=R){
            pr res=t.ask(L,R,1,0,n);
            res.fi++;

            dp[i]=mg(dp[i],res);
        }

        ad[i].clear();
        dl[i].clear();
    }

    cdq(mid+1,r);
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n;

    dp[0]={0,1};
    t.build(1,0,n);

    rep(i,1,n){
        dp[i]={-1e18,0};
        cin>>c[i]>>d[i];
    }

    cdq(1,n);

    // rep(i,1,n){
    //     cout<<dp[i].fi<<' '<<dp[i].se<<"\n";
    // }

    if(!dp[n].se){
        cout<<"NIE";
    }
    else{
        cout<<dp[n].fi<<' '<<dp[n].se;
    }

    return 0;
}
```

---

## 作者：Eterna (赞：2)

令 $f_i$ 为 $[1,i]$ 中的最大分组。容易推出方程：

$$f_i=\max_{\max _{k \in [j,i]}c_k \le i-j+1 \le \min _{k\in [j,i]}d_k} f_j+1$$

方案数同理。直接模拟 $\mathcal{O}(n^2)$ 是不行的。

考虑分治优化 dp。换言之，我们考虑  $j \in [l,\mathrm{mid}]$ 对 $i \in (\mathrm{mid},r]$ 的贡献。

令 $x_k,y_k$ 为 $k$ 到分治中点的最大的 $c$ 或最小的 $d$。

即条件变为 $\max \{x_i,x_j\} \le i-j+1 \le \min\{y_i,y_j\}$。

可以将条件拆成两个：

1. $x_i \le i-j+1 \le y_i$
2. $x_j \le i-j+1 \le y_j$

移项后可以得到：

1. $i+1-y_i \le j \le i+1-x_i$
2. $x_j+j-1 \le i \le y_j +j -1$

不难发现，这两个条件一个只影响 $i$，一个只影响 $j$。

枚举 $j$，将所有影响 $i$ 的区间预处理出来。算答案时，枚举 $i$，用线段树维护序列维，加入可以影响它的 $j$，删除不能影响它的 $j$。

时间复杂度是 $\mathcal{O}(n \log^2  n)$。

---

## 作者：yhy2024 (赞：1)

$f_i$ 为前 $i$ 个，且以 $i$ 断开的最优解，则有方程：

设 $mxl_{i,j}$ 为 $i$ 到 $j$ 的左端点最大值，$mnr$ 同理。

$$f_i=\max_{j}^{i-1} [i-j+1 \le mnr_{i,j}][i-j+1 \ge mxl_{i,j}] f_j+1$$

初始时，当 $mxl_{1,i}\le i$ 且 $mnr_{1,i}\ge i$ 时 $f_i=1$。

数量同理。

分治优化 dp。

在做 $[l,r]$。

设 $mxl_i$ 为 $i$ 到中点的左端点最大值，$mnr$ 同理。

现在做到 $i$，对于 $j \le mid$ 能对 $i$ 产生贡献当：

$$\max(mxl_i,mxl_j)<i-j+1<\min(mnr_i,mnr_j)$$。

可拆成：

$$mxl_i \le i-j+1 \le mnr_i$$

且

$$mxl_j \le i-j+1 \le mnr_j$$

移向后变成：

$$i+1-mxr_i \le j \le i+1-mnl_i$$

和

$$mxl_j+j-1 \le i \le mnr_j+j-1$$

变成两个只与 $i,j$ 有关的条件，在做 $[l,mid]$是找左边可行的区间记下，做 $[mid+1,r]$ 时，在 $j$ 在区间时把加入线段树，不合法时移除，解决条件 $2$，条件 $1$ 直接将 $i$ 带入，其实是求那段区间最大值。类似扫描线。

---

## 作者：Purslane (赞：1)

# Solution

设 $dp_i$ 表示前 $i$ 个数最多划分成多少段，以及方案数。（重载运算）很容易先出线性 DP：

$$
dp_i = \sum_{j < i,(j+1,i) \text{ is legal}} (dp_j+1)
$$

这里的 $+1$ 表示把划分段数加一，外层求和表示重载运算符。

使用 CDQ 分治优化转移。

也就是 $j \le p$，$i>p$，其中 $p$ 是分治中心。

只考虑  $(i,p]$ 和 $(p,j]$ 中的限制。$i$ 对 $j$ 的限制和 $j$ 对 $i$ 的限制都是一段区间。

使用线段树扫描一遍即可（枚举 $j$ 的时候，将 $i$ 加入或删除线段树，查询的时候做区间询问）。

复杂度 $O(n \log^2 n)$，足已通过本题。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=1e9+7;
int n,c[MAXN],d[MAXN];
struct Node {
	int mx,cnt;
}dp[MAXN];
Node operator +(Node A,Node B) {
	if(A.mx>B.mx) return A;
	if(A.mx<B.mx) return B;
	return {A.mx,(A.cnt+B.cnt)%MOD};	
}
namespace DS {
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	Node t[MAXN<<2];
	void build(int k,int l,int r) {
		t[k]={-0x3f3f3f3f,0};
		if(l!=r) build(lson,l,mid),build(rson,mid+1,r);
		return ;	
	}
	void update(int k,int l,int r,int pos,Node nd) {
		if(l==r) return t[k]=nd,void();
		if(pos<=mid) update(lson,l,mid,pos,nd);
		else update(rson,mid+1,r,pos,nd);
		return t[k]=t[lson]+t[rson],void();	
	}
	Node query(int k,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return t[k];
		if(y<=mid) return query(lson,l,mid,x,y);
		if(x>mid) return query(rson,mid+1,r,x,y);
		return query(lson,l,mid,x,y)+query(rson,mid+1,r,x,y);	
	}
	#undef mid
};
vector<int> ins[MAXN],del[MAXN];
void cdq(int l,int r) {
	if(l==r) return ;
	int mid=(l+r>>1);
	cdq(l,mid);
	int cmx=0,dmn=n+1;
	ffor(i,mid+1,r) ins[i].clear(),del[i].clear();
	roff(i,mid,l) {
		//(i+cmx,i+dmn)
		int ll=max(i+cmx,mid+1),rr=min(i+dmn,r);
		if(ll<=rr) ins[ll].push_back(i),del[rr+1].push_back(i);
		cmx=max(cmx,c[i]),dmn=min(dmn,d[i]);
	}
	cmx=0,dmn=n+1;
	ffor(i,mid+1,r) {
		for(auto id:ins[i]) DS::update(1,0,n,id,{dp[id].mx+1,dp[id].cnt});
		for(auto id:del[i]) DS::update(1,0,n,id,{-0x3f3f3f3f,0});	
		cmx=max(cmx,c[i]),dmn=min(dmn,d[i]);
		int ll=max(l,i-dmn),rr=min(mid+1,i-cmx);
		if(ll<=rr) dp[i]=dp[i]+DS::query(1,0,n,ll,rr);
	}
	ffor(i,mid+1,r) for(auto id:ins[i]) DS::update(1,0,n,id,{-0x3f3f3f3f,0});
	cdq(mid+1,r);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>c[i]>>d[i];
	ffor(i,1,n) dp[i]={-0x3f3f3f3f,0};
	dp[0]={0,1};
	DS::build(1,0,n);
	cdq(0,n);
	if(dp[n].mx>=0) cout<<dp[n].mx<<' '<<dp[n].cnt;
	else cout<<"NIE";
	return 0;
}
```

---

## 作者：lupengheyyds (赞：1)

> CDQ 优化 DP
> 
> 使用场景：DP 转移不连续，考虑贡献。
> 
> 过程：利用分治，考虑 $[j,mid]\to [mid+1,r]$，即整体贡献。
> 
> 过程：$[l,mid],[l,mid]\to [mid+1,r],[mid+1,r]$ 重点在中间。

不难得到一个朴素的 DP 方程：$dp_i$ 表示以 $i$ 作为结尾划分的最大值为多少，有 $dp_i=1+\sum\limits_{j\le i\land i-j\in[mx_{j+1,i},mn_{j+1,i}]}dp_j$。其中$mn_{l,r}=\min_{i=l}^rd_i,mx_{l,r}=\max_{i=l}^rc_i$。DP 最值的方案数是套路的，这里的问题是， $j$ 的转移并**不连续**，无法通过往常的方法优化。

---

考虑每个 $j$ 对 $i$ 的贡献，记为 $j\to i$，那么可以使用 CDQ 将变为整体之间的贡献，加速计算。

考虑如何求出 $[l,mid]\to[mid+1,r]$。我们将 $mn_{j+1,i}$ 拆分为两块，即 $mn_{j+1,mid+1},mn_{mid+1,i},mx$ 同理，这样就变为了一个一元变量。那么条件变为：

- $mx_{j+1,mid+1}\le i-j\le mn_{j+1,mid+1}\implies i\in[mx_{j+1,mid+1}+j,mn_{j+1,mid+1}+j]$
- $mx_{mid+1,i}\le i-j\le mn_{mid+1,i}\implies j\in[i-mn_{mid+1,i},i-mx_{mid+1,i}]$

需要同时满足。

第二个条件直接线段树维护，第一个条件可以使用类似扫描线的方法解决，即动态加入删除。

于是做到了复杂度 $\mathcal O(n\log^2n)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pa;
const int NN=1e6+5,INF=1e9,MOD=1e9+7;
int n,L[NN],R[NN];
struct DP{
	int f,g;
	DP(int _f=-INF,int _g=0){f=_f,g=_g;}
	DP operator+(DP b){
		if(f!=b.f)return (f>b.f)?*this:b;
		return DP(f,(g+b.g)%MOD);
	}
}dp[NN];
vector<pa> op[NN];
struct SegTr{
	DP sgt[NN<<2];
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	#define val(x) sgt[x]
	void Up(int p){
		val(p)=val(ls(p))+val(rs(p));
		return;
	}
	void Prune(int p,int pos,DP v,int L=1,int R=n){
		if(L==R){val(p)=v;return;}
		int mid=L+R>>1;
		if(pos<=mid)Prune(ls(p),pos,v,L,mid);
		else		Prune(rs(p),pos,v,mid+1,R);
		return Up(p);
	}
	DP Pick(int p,int l,int r,int L=1,int R=n){
		if(l>R||L>r||l>r)return DP();
		if(l<=L&&R<=r)return val(p);
		int mid=L+R>>1;
		return Pick(ls(p),l,r,L,mid)+Pick(rs(p),l,r,mid+1,R);
	}
}sgt;
void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	CDQ(l,mid);
	for(int i=mid,mx=L[mid+1],mn=R[mid+1];i>=l&&mx<=mn;i--){
		if(i+mx<=r&&i+mn>=mid+1){
			op[max(i+mx,mid+1)].push_back({i,1});
			op[min(i+mn,r)+1].push_back({i,-1});
		}
		mn=min(mn,R[i]);
		mx=max(mx,L[i]);
	}
	for(int i=mid+1,mx=0,mn=INF;i<=r;i++){//不能在mx>mn的时候break，因为还有余下的op操作，没有清空 
		for(pa opt:op[i]){
			int id=opt.first,si=opt.second;
			sgt.Prune(1,id,si==1?DP(dp[id].f+1,dp[id].g):DP());
		}
		op[i].clear();
		mx=max(mx,L[i]);
		mn=min(mn,R[i]);
		if(mx<=mn)dp[i]=dp[i]+sgt.Pick(1,max(i-mn,l),min(i-mx,mid));
	}
	for(pa opt:op[r+1])sgt.Prune(1,opt.first,DP());
	op[r+1].clear();
	CDQ(mid+1,r);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>L[i]>>R[i];
	for(int i=1,mn=INF,mx=0;i<=n;i++){
		mx=max(mx,L[i]),mn=min(mn,R[i]);
		if(mx<=i&&i<=mn)dp[i]=DP(1,1);
	}
	CDQ(1,n);
	dp[n].f<=0?cout<<"NIE":cout<<dp[n].f<<" "<<dp[n].g<<"\n";
	return 0;
} 
```

---

## 作者：zifanwang (赞：1)

对于一个固定的右端点 $r$，左端点 $l$ 合法当且仅当 $\max(d_l,d_{l+1},\dots d_r)\le r-l+1 \le\min(c_l,c_{l+1},\dots,c_r)$。

容易得到一个很朴素的 dp：记 $f_i$ 表示前 $i$ 个位置可以分成的组的数目的最大值，$g_i$ 表示有多少种分组方案能达到最大值，直接枚举左端点转移，时间复杂度 $\mathcal O(n^2)$。转移点不是连续的，不好直接优化。

考虑对这个 dp 进行一个分治，对于每个分治的区间 $[l,r]$ 处理 $f_{[l,\text{mid}]},g_{[l,\text{mid}]}$ 对 $f_{[\text{mid}+1,r]},g_{[\text{mid}+1,r]}$ 的贡献。发现 $c$ 对每个右端点的限制是只能取某个后缀的左端点，可以直接二分出这个后缀，接下来只要考虑 $d$ 的限制。

很容易想到倒着枚举 $[l,\text{mid}]$ 中的每个位置，维护 $d$ 的最大值，可以得到一个右端点的位置 $\ge \max(d_{[l,\text{mid}]})+l-1$ 的限制。考虑对 $[\text{mid}+1,r]$ 每个位置建一个桶，在这个限制的对应位置处插入这个左端点。接下来正着枚举 $[\text{mid}+1,r]$ 中的每个位置，把桶内的位置插入线段树。对于每个右端点也可以得到一个类似的限制，在线段树上查询即可，最后更新一下就做完了。

时间复杂度 $\mathcal O(n\log^2n)$，参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 1000003
#define md 1000000007
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
struct node{
	ll a,c;
}f[mxn],t[mxn<<2];
int n,lg[mxn],ps[mxn],a[mxn],b[20][mxn];
vector<int>s[mxn];
const int INF=1e9;
node operator+(node x,node y){
	return {max(x.a,y.a),((x.a>=y.a?x.c:0)+(y.a>=x.a?y.c:0))%md};
}
int ask2(int l,int r){
	int k=lg[r-l+1];
	return min(b[k][l],b[k][r-(1<<k)+1]);
}
void change(int p,int x,node y,int l,int r){
	if(l==r){t[p]=y;return;}
	int mid=(l+r)>>1;
	if(x<=mid)change(p<<1,x,y,l,mid);
	else change(p<<1|1,x,y,mid+1,r);
	t[p]=t[p<<1]+t[p<<1|1];
}
node ask(int p,int l,int r,int L,int R){
	if(l<=L&&R<=r)return t[p];
	int mid=(L+R)>>1;
	if(l<=mid&&r>mid)return ask(p<<1,l,r,L,mid)+ask(p<<1|1,l,r,mid+1,R);
	if(l<=mid)return ask(p<<1,l,r,L,mid);
	return ask(p<<1|1,l,r,mid+1,R);
}
void build(int p,int l,int r){
	t[p]={-INF,0};
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
}
void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid);
	rep(i,mid+1,r)s[i].clear();
	int mx=0;
	drep(i,mid,l){
		if(mx+i<=r)s[max(mx+i,mid+1)].pb(i);
		mx=max(mx,a[i]);
	}
	mx=0;
	rep(i,mid+1,r){
		mx=max(mx,a[i]);
		for(int j:s[i])change(1,j,{f[j].a+1,f[j].c},0,n);
		int L=max(ps[i]-1,l),R=min(i-mx,mid);
		if(L<=R)f[i]=f[i]+ask(1,L,R,0,n);
	}
	rep(i,l,mid)change(1,i,{-INF,0},0,n);
	solve(mid+1,r);
}
signed main(){
	scanf("%d",&n);
	rep(i,2,n)lg[i]=lg[i>>1]+1;
	rep(i,1,n)scanf("%d%d",&a[i],&b[0][i]);
	rept(k,1,20){
		rep(i,1,n-(1<<k)+1){
			b[k][i]=min(b[k-1][i],b[k-1][i+(1<<(k-1))]);
		}
	}
	rep(i,1,n){
		int l=1,r=i;
		while(l<r){
			int mid=(l+r)>>1;
			if(ask2(mid,i)>=i-mid+1)r=mid;
			else l=mid+1;
		}
		ps[i]=l;
	}
	f[0].c=1;
	rep(i,1,n)f[i].a=-INF;
	build(1,0,n);
	solve(0,n);
	if(f[n].a<=0)puts("NIE");
	else cout<<f[n].a<<" "<<f[n].c;
	return 0;
}
```

---

## 作者：123456xwd (赞：0)

ZJ 上课讲的题目，是题解区都没有的解法，记录一下。

首先，考虑最基础的 dp，设 $f_i$ 表示将 $[1,i]$ 最多划分为多少段以及对应的方案数，考虑一个转移 $f_{i-1}\to f_j$，则要满足：
$$
\max_{x=i}^j\{c_x\}\le j-i+1\le \min_{x=i}^j\{d_x\}
$$
考虑固定一个 $j$，随着 $i$ 的变小，$j-i+1$ 变大，而 $\min_{x=i}^j\{d_x\}$ 变小，也就是我们可以预处理一个 $p_j$，表示最小的符合要求的 $i$，且 $p$ 显然是单调不降的，双指针和 `multiset` 维护一下即可。

那么，我们的限制变为：
$$
\max_{x=i}^j\{c_x\}\le j-i+1\\
p_{j}\le i< j
$$
考虑那一坨取 $\max$，由此建立一个笛卡尔树。

在上面做分治，假设当前在节点 $u$，对应的区间为 $[L_u,R_u]$，先递归左子树，再从左区间到右区间转移，最后递归右子树，考虑如何转移。

此时继续改写限制，此时那一坨 $\max$ 就变为了 $c_u$，则要满足：
$$
\max(L_u,p_j)\le i\le \min(u,j-c_u+1)
$$
开始分讨，去掉 $\max,\min$：

1. $L_u>p_j,u\ge j-c_u+1$：

   此时对于 $j$ 的限制为：$u\le j\le \min(k-1,u+c_u-1)$。

   其中 $k$ 表示最小的满足 $j\in[u,R_u],p_j\ge L_u$，二分找到他，时间为 $\mathcal{O}(n\log n)$。

   而 $i$ 的限制在于 $L_u\le i\le j-c_u+1$。

   发现，随着 $j$ 的变大，$i$ 的取值范围也是对应不断变大的，对于最初的 $j$，用线段树找到对应有贡献的 $i$，随后每次 $\mathcal{O}(1)$ 的增加即可，若 $i$ 达到了 $u$，在线段树上区间修改即可。 

   注意，若一开始没有符合限制的 $i$，我们可以 $\mathcal{O}(1)$ 求得使得其符合限制的 $j$。

   每次的时间复杂度上界为 $\mathcal{O}(\min(u-L_u,R_u-u))+\mathcal{O}(\log n)$，前者的复杂度分析类似启发式合并，算上线段树，时间复杂度为 $\mathcal{O}(n\log^2 n)$。

2. $L_u>p_j,u<j-c_u+1$：

   此时对于 $j$ 的限制为 $u+c_u-1<j<k$。

   此时对于 $i$ 的限制为 $i\in[L_u,u]$。

   线段树区间查询和区间修改即可，时间复杂度为 $\mathcal{O}(n\log n)$。

3. $L_u\le p_j$：

   此时对于 $j$ 的限制为 $k\le j\le R_u$。

   而 $i$ 的限制为 $p_j\le i\le \min(u,j-c_u+1)$，看似又要进行烦人的分讨，但由于你的 $i\le u$，那么有一个隐含条件就是 $p_j\le u$。

   那么，总体来看，就是要求 $L_u\le p_j\le u\le j\le R_u$。

   则对于一个 $(p_j,j)$，顶多只会在一个 $u$ 内计算到贡献，而 $p_j$ 单调不降，可以二分出来一个合法的区间，然后暴力遍历+线段树区间查询即可，时间复杂度为 $\mathcal{O}(n\log n)$。

综上，我们总算是做完了这道题目，总时间复杂度为 $\mathcal{O}(n\log^2 n)$，不过应该跑不满。

细节较多，请注意一些边界条件。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define f first
#define g second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd;
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1e6+5,INF=0x3f3f3f3f,mod=1e9+7;
int add(int x,int y){
    return x+y<mod?x+y:x+y-mod;
}
pii operator+ (const pii &x,const pii &y){
    if(!x.g&&!y.g) return m_p(-INF,0);
    if(!x.g||!y.g) return x.g?x:y;
    if(x.f==y.f) return m_p(x.f,add(x.g,y.g));
    return x.f>y.f?x:y;
}
struct seg{
    pii a[N<<2],tag[N<<2];
    bool flag[N<<2];
    void calc(int k,pii w){flag[k]=1,a[k]=a[k]+w,tag[k]=tag[k]+w;}
    void push_down(int k){if(flag[k])calc(ls,tag[k]),calc(rs,tag[k]),flag[k]=0,tag[k]=m_p(-INF,0);}
    void push_up(int k){a[k]=a[ls]+a[rs];}
    void build(int k,int l,int r){
        a[k]=tag[k]=m_p(-INF,0);
        if(l==r)return;
        build(ls,l,mid);build(rs,mid+1,r);
    }
    void change(int k,int l,int r,int x,int y,pii w){
        if(x>y)return;
        if(x<=l&&r<=y){calc(k,w);return;}
        push_down(k);
        if(x<=mid)change(ls,l,mid,x,y,w);
        if(y>mid)change(rs,mid+1,r,x,y,w);
        push_up(k);
    }
    pii ask(int k,int l,int r,int x,int y){
        if(x>y) return m_p(-INF,0);
        if(x<=l&&r<=y) return a[k];
        push_down(k);
        if(y<=mid)return ask(ls,l,mid,x,y);
        if(x>mid)return ask(rs,mid+1,r,x,y);
        return ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y);
    }
}T;
int n,d[N],c[N],p[N];
int sta[N],top,_l[N],_r[N];
multiset<int> s;
void dfs(int u,int L,int R){
    if(!u)return;
    dfs(_l[u],L,u-1);
    pii res,tmp;
    int k=lower_bound(p+u,p+R+1,L)-p,lj=u,rj=min(k-1,u+c[u]-1),li=L,ri=u-c[u]+1;
    if(li>ri)lj+=li-ri,ri=li;
    if(lj<=rj){//第一类转移
        res=T.ask(1,0,n,li-1,ri-1),tmp;res.f++;
        T.change(1,0,n,lj,lj,res);
        for(int j=lj+1;j<=rj;j++){
            if(ri==u){
                T.change(1,0,n,j,rj,res);
                break;
            }
            ri++;
            if(ri>=L)tmp=T.ask(1,0,n,ri-1,ri-1);tmp.f++;res=res+tmp;
            T.change(1,0,n,j,j,res);
        }
    }
    //第二类转移
    res=T.ask(1,0,n,L-1,u-1);res.f++;
    T.change(1,0,n,u+c[u],k-1,res);
    //第三类转移：  
    int ul=lower_bound(p+u,p+R+1,L)-p,ur=upper_bound(p+u,p+R+1,u)-p-1;
    for(int j=ul;j<=ur;j++){
        res=T.ask(1,0,n,p[j]-1,min(u,j-c[u]+1)-1);res.f++;
        T.change(1,0,n,j,j,res);
    }
    dfs(_r[u],u+1,R);
}
int main(){
    n=rd();for(int i=1;i<=n;i++) c[i]=rd(),d[i]=rd();
    p[1]=1;s.insert(d[1]);
    for(int i=2;i<=n;i++){
        p[i]=p[i-1];s.insert(d[i]);
        while(i-p[i]+1>(*s.begin())) s.erase(s.find(d[p[i]])),p[i]++;
    }
    T.build(1,0,n);
    T.change(1,0,n,0,0,m_p(0,1));
    for(int i=1;i<=n;i++){
        int tmp=top;
        while(top&&c[sta[top]]<c[i]) top--;
        if(top) _r[sta[top]]=i;
        if(tmp!=top)_l[i]=sta[top+1];
        sta[++top]=i;
    }
    dfs(sta[1],1,n);
    auto [f,g]=T.ask(1,0,n,n,n);
    if(!g)puts("NIE");
    else printf("%d %d\n",f,g);
    return 0;
}
```

---

