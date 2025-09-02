# Interesting Sections

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609F/37581220fa7958c8fff17f022427b5b4d5e4d291.png)William has an array of non-negative numbers $ a_1, a_2, \dots, a_n $ . He wants you to find out how many segments $ l \le r $ pass the check. The check is performed in the following manner:

1. The minimum and maximum numbers are found on the segment of the array starting at $ l $ and ending at $ r $ .
2. The check is considered to be passed if the binary representation of the minimum and maximum numbers have the same number of bits equal to 1.

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
9```

## 样例 #2

### 输入

```
10
0 5 7 3 9 10 1 6 13 7```

### 输出

```
18```

# 题解

## 作者：Alan_Zhao (赞：11)

**[&#x1f605;](https://www.cnblogs.com/alan-zhao-2007/p/cf1609f-sol.html)**

## 题解

考虑分治。设当前要对区间 $[l,r]$ 进行计算，令 $m=\lfloor \frac{l+r}{2}\rfloor$，我们只需要计算左端点 $\in [l,m]$，右端点 $\in [m+1,r]$ 的合法区间个数，然后递归到 $[l,m],[m+1,r]$ 计算即可。

我们从大到小枚举一个左端点 $i\in [l,m]$，对于一个固定的 $i$，在 $[m+1,r]$ 之间一定会存在两个分界点 $p_1,p_2$ 使得：

- 若右端点 $\in [m+1,p_1]$，则区间的 $\max$ 和 $\min$ 都在 $[i,m]$ 间取到；
- 若右端点 $\in [p_1+1,p_2]$，则区间的 $\max$ **或** $\min$ 在 $[i,m]$ 间取到；
- 若右端点 $\in [p_2+1,r]$，则区间的 $\max$ 和 $\min$ 都在 $[m+1,\text{右端点}]$ 间取到；

并且，随着 $i$ 逐渐减小，$p_1,p_2$ 都递增。于是我们可以双指针维护 $p_1,p_2$，并分别考虑三种情况的贡献。第一种和第三种的贡献是显然的，对于第二种，只需要在 $p_1,p_2$ 移动过程中，对于每个 $k$ 维护 $\operatorname{popcount}=k$ 的个数有多少。

这样总复杂度是 $\mathcal{O}(n(\log n+\log V))$ 的，$V$ 是 $\max_i\{a_i\}$。

## 代码

因为我用了 `memset`，所以代码实际上是 $\mathcal{O}(n\log n\log V)$ 的，但 `memset` 的常数比较小，所以跑得挺快。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define popc __builtin_popcountll
#define Clear(a) memset(a,0,sizeof(a))
typedef long long ll;
const int N=1e6+5,LogV=65;
const ll Inf=0x3f3f3f3f3f3f3f3f;
int n,cnt1[LogV],cnt2[LogV],cnt3[LogV],cnt4[LogV],eq[N];ll a[N],ans;
void Solve(int l,int r){
	if(l>r) return;
	if(l==r){++ans;return;}
	int mid=(l+r)/2;
	Clear(cnt1),Clear(cnt2),Clear(cnt3),Clear(cnt4);
	eq[mid]=0;
	for(ll i=mid+1,mn=a[mid+1],mx=a[mid+1];i<=r;++i,mn=min(mn,a[i]),mx=max(mx,a[i]))
		eq[i]=eq[i-1]+(popc(mn)==popc(mx));
	ll mn=Inf,mx=-Inf,mn1=Inf,mx1=-Inf,mn2=Inf,mx2=-Inf;
	for(int i=mid,p1=mid,p2=mid;i>=l;--i){
		mn=min(mn,a[i]),mx=max(mx,a[i]);
		while(p1<r&&mn<=min(mn1,a[p1+1])&&mx>=max(mx1,a[p1+1]))
			++p1,mn1=min(mn1,a[p1]),mx1=max(mx1,a[p1]),++cnt1[popc(mn1)],++cnt2[popc(mx1)];
		while(p2<r&&(mn<=min(mn2,a[p2+1])||mx>=max(mx2,a[p2+1])))
			++p2,mn2=min(mn2,a[p2]),mx2=max(mx2,a[p2]),++cnt3[popc(mn2)],++cnt4[popc(mx2)];
		ans+=(popc(mn)==popc(mx))*(p1-mid)+eq[r]-eq[p2];
		if(mn<=mn2) ans+=cnt4[popc(mn)]-cnt2[popc(mn)];
		else ans+=cnt3[popc(mx)]-cnt1[popc(mx)];
	}
	Solve(l,mid),Solve(mid+1,r);
}
int main(){
	#ifndef zyz
	ios::sync_with_stdio(false),cin.tie(nullptr);
	#endif
	cin>>n;
	For(i,1,n) cin>>a[i];
	Solve(1,n);
	cout<<ans;
	return 0;
}
```

---

## 作者：GSH_gsh (赞：8)

### 题意

给你一个长为 $n$ 的非负整数序列 $a$，求有多少区间 $[l,r]$ 满足 $\text{popcount}(\max\limits_{i=l}^r a_i)=\text{popcount}(\min\limits_{i=l}^r a_i)$。

$1\le n\le 10^6,0\le a_i\le 10^{18}$。

### 题解

因为 $\text{popcount}$ 和 $\max/\min$ 没有多大关系，所以可以把 $\text{popcount}(a_i)$ 看成 $i$ 的颜色 $b_i,0\le b_i\le 59$。

对每个位置求出 $a_i$ 作为 $\max$ 时向左右最多可以控制到哪个位置，记为 $l_{1_i},r_{1_i}$，表示任意区间 $[x,y]$ 满足 $l_{1_i}\le x\le i,i\le y\le r_{1_i}$，都有 $\max\limits_{j=x}^y a_j=a_i$。对于相同的 $a_i$ 可以用下标比较，总之不能重复。

把每个区间看成二维平面上的点，$\forall i\in[1,n]$，$a_i$ 控制的矩形是 $[l_{1_i},i]\times [i,r_{1_i}]$，把这个矩形染成 $b_i$ 的颜色。容易发现一个区间对应唯一的最小值，所以这个二维平面的上三角矩形恰好每个位置被染了一次色。

对于 $\min$ 同样处理求出 $l_{2_i},r_{2_i}$，再染一次色。

问题转化成 $2n$ 个矩形染色操作，保证上三角矩阵恰好染两次色，求有多少个位置染色相同。

对每种颜色分别进行扫描线，矩形加 $1$，求出有多少个位置权值为 $2$。答案就是所有颜色加起来。

求所有的 $l_{1_i},r_{1_i},l_{2_i},r_{2_i}$ 可以用单调栈做到线性时间，扫描线复杂度 $O(n\log n)$。

总时间复杂度 $O(n\log n)$。本题略微卡常，请合理使用 `fread`。

[code](https://codeforces.com/contest/1609/submission/137319742)

---

## 作者：tzc_wk (赞：5)

> 摘自我的[贪心/构造/DP 杂题选做Ⅳ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp4.html)中的第 $86$ 题

讲个笑话，vp 的时候想交这道题的时候 CF 崩掉了，卡了 1h 直到 vp 结束后 3min 才好，好在最后我的第一发提交因为常数太大 T 了，否则就亏大了……

考虑枚举最大值和最小值的 popcount，那么问题等价于，给定一个序列 $a_i$，其中有一些位置是关键位置，要求有多少个区间，满足其最大值和最小值都是关键位置。

碰到数区间问题无非两个套路：枚举右（左）端点或分治，这次咱们采取前者，我们扫描线式枚举右端点 $r$，扫描到 $r$ 时，我们记 $f_l$ 表示 $[l,r]$ 中最大值是否关键位置 $+$ $[l,r]$ 中最小值是否是关键位置，那么显然 $f_l$ 的变化可以通过单调栈求出，那么对于一个右端点 $r$ 和一个 `popcount` $v$，其对答案的贡献就是 $f_l=2$ 的 $l$ 的个数。注意到 $f_l$ 的上界就是 $2$，因此这个可以通过区间最大值及其出现次数的线段树维护。

算下复杂度，乍一看这个做法复杂度是 2log 的，但实则不是。因为我们单调栈时修改次数均摊下来是 $\mathcal O(n)$ 的，而查询我们只用用到根节点存储的值，因此虽然查询次数可以达到 $n\log v$，单次查询是 $\mathcal O(1)$ 的这一事实导致复杂度也不算太高，这样总复杂度就是 $n(\log v+\log n)$，可以通过。

注意常数问题！！！！！1111

```cpp
using namespace fastio;
const int MAXN = 1e6;
const int LOG_V = 62;
int n, c[MAXN + 5], cnt[LOG_V + 2]; ll a[MAXN + 5];
struct node {int l, r, mx, mxc, lz;} s[MAXN * 4 + 5];
void pushup(int k) {
	s[k].mx = max(s[k << 1].mx, s[k << 1 | 1].mx); s[k].mxc = 0;
	if (s[k].mx == s[k << 1].mx) s[k].mxc += s[k << 1].mxc;
	if (s[k].mx == s[k << 1 | 1].mx) s[k].mxc += s[k << 1 | 1].mxc;
}
void build(int k, int l, int r) {
	s[k].l = l; s[k].r = r; s[k].mx = s[k].lz = 0; s[k].mxc = r - l + 1;
	if (l == r) return; int mid = l + r >> 1;
	build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r);
}
void tag(int k, int v) {s[k].mx += v; s[k].lz += v;}
void pushdown(int k) {
	if (s[k].lz) tag(k << 1, s[k].lz), tag(k << 1 | 1, s[k].lz), s[k].lz = 0;
}
void modify(int k, int l, int r, int v) {
	if (l <= s[k].l && s[k].r <= r) return tag(k, v), void();
	pushdown(k); int mid = s[k].l + s[k].r >> 1;
	if (r <= mid) modify(k << 1, l, r, v);
	else if (l > mid) modify(k << 1 | 1, l, r, v);
	else modify(k << 1, l, mid, v), modify(k << 1 | 1, mid + 1, r, v);
	pushup(k);
}
struct opt {int p, l, r, v;};
vector<opt> qv[LOG_V + 2];
int main() {
	read(n); ll res = 0;
	for (int i = 1; i <= n; i++) {
		read(a[i]), c[i] = __builtin_popcountll(a[i]);
		cnt[c[i]]++;
	}
	static int stk_mn[MAXN + 5], stk_mx[MAXN + 5];
	int mn_tp = 1, mx_tp = 1;
	for (int j = 1; j <= n; j++) {
		while (mn_tp > 1 && a[stk_mn[mn_tp]] > a[j]) {
			int p = stk_mn[mn_tp--];
			qv[c[p]].pb({j, stk_mn[mn_tp] + 1, p, -1});
		}
		qv[c[j]].pb({j, stk_mn[mn_tp] + 1, j, 1});
		while (mx_tp > 1 && a[stk_mx[mx_tp]] <= a[j]) {
			int p = stk_mx[mx_tp--];
			qv[c[p]].pb({j, stk_mx[mx_tp] + 1, p, -1});
		}
		qv[c[j]].pb({j, stk_mx[mx_tp] + 1, j, 1});
		stk_mx[++mx_tp] = j; stk_mn[++mn_tp] = j;
	}
	for (int i = 0; i <= LOG_V; i++) {
		if (!cnt[i]) continue; build(1, 1, n);
		for (int j = 1, cur = 0; j <= n; j++) {
			while (cur < qv[i].size() && qv[i][cur].p <= j) {
				modify(1, qv[i][cur].l, qv[i][cur].r, qv[i][cur].v);
				cur++;
			}
			if (s[1].mx == 2) res += s[1].mxc;
		}
	}
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：Miko35 (赞：3)

考场降智不会做蠢蠢题...

---

题意：给你一个长度为 $n$ 的序列 $\{a_i\}$，问区间 $\max$ 和区间 $\min$ 拥有相同 $\operatorname{popcount}$ 的区间有多少个。

$n \leq 10^6,a_i \leq 10^{18}$

$\textrm{Solution}$：考虑枚举这个 $\operatorname{popcount}$ 是多少来统计，假设当前枚举的 $\operatorname{popcount}$ 是 $w$。

朴素的做法是，从左到右枚举右端点 $r$，同时用单调栈维护左端点为 $l$ 的区间最大/小值的 $\operatorname{popcount}$ 是否为 $w$，那么就需要一个数据结构支持两个序列 $A,B$ 的如下操作：

1. 对一个序列区间覆盖为 0/1，保证覆盖前这个区间所有数相等。
2. 查询 $\sum A_iB_i$

树状数组维护即可，时间复杂度 $O(n \log a\log n)$。

观察可知，在整个过程中 $1$ 覆盖只有 $O(n)$ 个，瓶颈在于有太多无用的 $0$ 覆盖。

根据单调栈的性质可以发现，扫到 $i$ 时覆盖的区间的左端点是 $i$ 前面第一个比 $a_i$ 大/小的元素，显然这玩意成一个树形结构。所以对于某一次操作将某一段覆盖为 $1$，那么这段区间在之后的操作中一定是被整个覆盖为 $0$，不会在中间被拆开，在单调栈的时候记录这个时间戳即可。时间复杂度 $O(n (\log a + \log n))$，轻微卡常。

```cpp
int n,c[N],qx[N],qm[N],cx,cm,px[N],pm[N],t1,t2,V[N];
struct BIT{
	...
}t[2];
ll a[N],ans,sum;
vector<pii>ex[62],em[62];
void mdf(int w,int l,int r,int v){sum+=v*t[!w].qry(l,r),t[w].upd(l,r,v);}
signed main(){
	FOR(i,1,n=read()){
		V[c[i]=__builtin_popcountll(a[i]=read())]=1;
		while(cx&&a[i]>a[qx[cx]])ex[c[qx[cx]]].pbk({i,qx[cx--]});
		px[i]=qx[cx]+1,qx[++cx]=i;
		while(cm&&a[i]<a[qm[cm]])em[c[qm[cm]]].pbk({i,qm[cm--]});
		pm[i]=qm[cm]+1,qm[++cm]=i;
	}
	FOR(w,0,60)if(V[w]){
		sot(ex[w]),sot(em[w]);
		t[t1=t2=sum=0].clear(),t[1].clear();
		rgi S1=ex[w].size(),S2=em[w].size();
		FOR(i,1,n){
			if(c[i]==w)mdf(0,px[i],i,1),mdf(1,pm[i],i,1);
			while(t1<S1&&ex[w][t1].fi==i){
				rgi k=ex[w][t1++].se;
				mdf(0,px[k],k,-1);
			}
			while(t2<S2&&em[w][t2].fi==i){
				rgi k=em[w][t2++].se;
				mdf(1,pm[k],k,-1);
			}
			ans+=sum;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：EuphoricStar (赞：2)

看到 $\max, \min$ 考虑单调栈。枚举右端点，计算有多少个符合条件的左端点。

单调栈维护的是对于每个右端点，以每个点为左端点的后缀 $\max, \min$ 形成的极长的段。先枚举 $\text{popcount} = k$，然后如果一个段的 $\max$ 的 $\text{popcount} = k$ 就在线段树上把这段区间 $+1$。$\min$ 同理。那么查询就是查 $[1, n]$ 的 $2$ 的个数。可以维护区间最大值个数解决。

时间复杂度 $O(n (\log n + \log V))$。但是因为 $\log n$ 是线段树的 $\log$ 所以要卡常才能通过。

[code](https://codeforces.com/problemset/submission/1609/242772389)

---

## 作者：5k_sync_closer (赞：2)

分治，设当前区间为 $[l,r]$，考虑跨过分治中点 $m=\left\lfloor\dfrac{l+r}2\right\rfloor$ 的满足条件的区间个数。

枚举区间左端点 $i\in[l,m]$，设右端点为 $j$，则对每个 $i$，总有 $p1,p2$ 满足：

- $\forall j\in(m,p1]$，$[i,j]$ 的 $\max,\min$ 均落在 $[i,m]$ 中，

则若此时 $\text{popcount}(\max\limits_{k=i}^ma_k)=\text{popcount}(\min\limits_{k=i}^ma_k)$，则所有 $j\in(m,p1]$ 的 $[i,j]$ 均符合要求，否则均不负责要求。

- $\forall j\in(p1,p2]$，$[i,j]$ 的 $\max,\min$ 一个落在 $[i,m]$ 中，一个落在 $(m,j]$ 中，

以 $\min$ 落在 $[i,m]$ 中，$\max$ 落在 $(m,j]$ 中为例，

问题变为统计 $(p1,p2]$ 中有多少 $j$ 满足 $\text{popcount}(\max\limits_{k=m+1}^ja_k)=\text{popcount}(\min\limits_{k=i}^ma_k)$，

直接开桶维护 $c_x$ 表示当前 $(p1,p2]$ 中有多少 $j$ 满足 $\text{popcount}(\max\limits_{k=m+1}^ja_k)=x$，更新 $p1,p2$ 时更新这个桶即可。

- $\forall j\in(p2,r]$，$[i,j]$ 的 $\max,\min$ 均落在 $(m,j]$ 中，

问题变为统计 $(p2,r]$ 中有多少 $j$ 满足 $\text{popcount}(\max\limits_{k=m+1}^ja_k)=\text{popcount}(\min\limits_{k=m+1}^ja_k)$，

发现与 $i$ 无关，提前预处理 $e_x$ 表示 $(m,x]$ 中满足该条件的 $j$ 的个数。

然后倒序枚举 $i$，发现 $p1,p2$ 单调后移，双指针即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, q, a[1000050], e[1000050], c1[70], c2[70];
void F(int l, int r)
{
    if (l == r)
        return void(++q);
    int m = l + r >> 1;
    memset(c1, 0, sizeof c1);
    memset(c2, 0, sizeof c2);
    e[m] = 0;
    long long u = 1e18, v = -1e18, u1 = 1e18, v1 = -1e18, u2 = 1e18, v2 = -1e18;
    for (int i = m + 1; i <= r; ++i)
        e[i] = e[i - 1] + (__builtin_popcountll(u = min(u, a[i])) == __builtin_popcountll(v = max(v, a[i])));
    u = 1e18;
    v = -1e18;
    for (int i = m, p1 = m, p2 = m; i >= l; --i)
    {
        u = min(u, a[i]);
        v = max(v, a[i]);
        while (p1 < r && u <= min(u1, a[p1 + 1]) && v >= max(v1, a[p1 + 1]))
            u1 = min(u1, a[++p1]), v1 = max(v1, a[p1]), --c1[__builtin_popcountll(u1)], --c2[__builtin_popcountll(v1)];
        while (p2 < r && (u <= min(u2, a[p2 + 1]) || v >= max(v2, a[p2 + 1])))
            u2 = min(u2, a[++p2]), v2 = max(v2, a[p2]), ++c1[__builtin_popcountll(u2)], ++c2[__builtin_popcountll(v2)];
        if (__builtin_popcountll(u) == __builtin_popcountll(v))
            q += p1 - m;
        q += e[r] - e[p2];
        if (u <= u2)
            q += c2[__builtin_popcountll(u)];
        else
            q += c1[__builtin_popcountll(v)];
    }
    F(l, m);
    F(m + 1, r);
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    F(1, n);
    printf("%lld", q);
    return 0;
}
```


---

## 作者：kiritokazuto (赞：2)

# Interesting Sections

> ~~既然是数据结构，不用线段树怎么行呢？有了线段树，不用扫描线怎么行呢？有了扫描线，那不就扫两下就过了吗？~~

> 然后，在机房各个巨佬的带领下，这玩意卡卡常，过了，加个 `fread` 什么的就行，做出突出贡献的有 [``Kamisato_Ayaka_`` 带佬](https://www.luogu.com.cn/user/654518)。

- 首先我们可以想到线段树，线段树上的每一个节点，代表以当前 $l,r$ 中的每一个点为左端点，到我现在扫到的 $i$，中我现在的 $\operatorname{popcount}$ 的贡献。

- 显然我们最初的思路是暴力硬扫，总共最多只有 $60$ 种 $\operatorname{popcount}$，那我们就硬扫就完了，但是显然之中的显然，他会超时，而且还会超时很多(虽然现在也超)，所以我们应该去优化一下。

- 我们考虑一个数的管辖区间，可以通过单调栈来解决。

  - 对于最大值，我们维护一个单调递减的栈，如果当前栈顶比我小，那么就出栈，那么对于我当前 $a_{i}$ 的管辖区间删完之后的栈顶到我的 $i$，也就是他们的最大值都是我。
  
  - 对于最小值，只需要相反地维护一个单调递增的栈即可。
  
- 我们再考虑如何寻找答案。

  - 对于最大值相同的区间，我的答案就是这段区间里 $\operatorname{popcount}$ 和我相同的 $Min$ 的个数，所以如果最大值相同，我们就将他的区间都设置成 $1$，然后直接统计相同区间里 $Min$ 的一的个数即可，具体可见代码，我的文字拙劣，可能说不清。
  
  - 对于最小值相同的区间，完全相反即可。
  
- 之后我们考虑一个数会怎样进行贡献。

  - 一个数其实最多只会进行 $4$ 次贡献:
  
    - 进栈时对于最大值和最小值的更新两次。

    - 出栈时对于最大值和最小值的更新两次。

  - 那么我们就可以开始均摊复杂度了。
    - 对于一个相同的 $\operatorname{popcount}$ 显然只有其他和我现在 $\operatorname{popcount}$ 相同的点会进行贡献，所以我的单调栈里只维护和我 $\operatorname{popcount}$ 相同的点并计算贡献。
    - 但是注意，对于 $\operatorname{popcount}$ 和我不相同的点，它会使我出栈，这是无法避免的事实，所以我可以出栈，但是不让他进栈，我的栈里时刻维护和我 $\operatorname{popcount}$ 相同的点。
  - 因为我一个数不可能既不 $\ge a_{i}$ 又不 $\le a_{i}$，所以每次一个新数都会影响我的栈，所以能考虑到所有情况，正确性是可以保证的。
- 最后均摊完时间复杂度大概是 $O(n\log n)$，对于那个可能存在的 $60$ 的常数，嗯。~~可以忽略~~。

```cpp

#include<cstdio>
#define LL long long
#define fuc(x, y) inline x y
#define fr(x, y, z)for(int x = y; x <= z; x ++)
#define fp(x, y, z)for(int x = y; x >= z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define lsp(rt) (rt << 1)
#define rsp(rt) (rt << 1 | 1)
#define mid ((l + r) >> 1)
#define WMX aiaiaiai~~
using namespace std;
const int Mxdt=100000;
inline char gc(){
    static char buf[Mxdt],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline LL read(){
    LL t=0,f=0;char v=gc();
    while(v<'0')f|=(v=='-'),v=gc();
    while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
    return f?-t:t;
}
const int maxn = 1e6 + 10, maxm = 4e6 + 10;
fuc(int, popcnt)(LL x){
    int res = 0 ;
    while(x){
        if(x)res++;
        x ^= x & (-x);
    }
    return res;
}


int n;
bool is[62];
int lz1[maxn << 2], lz2[maxn << 2];
int lMax[maxn << 2], lMin[maxn << 2];
int pop[maxn];
LL a[maxn];
LL ans[maxn << 2];
LL sum1[maxn << 2], sum2[maxn << 2];
LL anss;
fuc(void, pushup)(int rt){
    ans[rt] = ans[lsp(rt)] + ans[rsp(rt)];
    sum1[rt] = sum1[lsp(rt)] + sum1[rsp(rt)];
    sum2[rt] = sum2[lsp(rt)] + sum2[rsp(rt)];
}

fuc(void, changeMax)(int rt, int l, int r, int type){
    if(type == 1){//覆成1
        sum1[rt] = r - l  + 1;
        ans[rt] = sum2[rt];//我Max相同时只需要找Min的popcnt相同就是答案
        lz1[rt] = 1;
    }else {
        sum1[rt] = 0;
        ans[rt] = 0;
        lz1[rt] = -1;
    }
}
fuc(void, changeMin)(int rt, int l, int r, int type){
    if(type == 1){//覆成1
        sum2[rt] = r - l  + 1;
        ans[rt] = sum1[rt];
        lz2[rt] = 1;
    }else {
        sum2[rt] = 0;
        ans[rt] = 0;
        lz2[rt] = -1;
    }
}
fuc(void ,pushdownMax)(int rt, int l, int r){
    changeMax(lsp(rt), l, mid, lz1[rt]);
    changeMax(rsp(rt), mid + 1, r, lz1[rt]);
    lz1[rt] = 0;
}
fuc(void, pushdownMin)(int rt, int l, int r){
    changeMin(lsp(rt), l, mid, lz2[rt]);
    changeMin(rsp(rt), mid + 1, r, lz2[rt]);
    lz2[rt] = 0;
}
fuc(void, updataMax)(int rt, int l, int r, int L , int R, int type) {
    if(L <= l && r <= R) return changeMax(rt, l, r, type), void();
    if(lz1[rt])pushdownMax(rt, l, r);
    if(lz2[rt])pushdownMin(rt, l, r);
    if(L <= mid)updataMax(lsp(rt), l , mid, L, R, type);
    if(R > mid)updataMax(rsp(rt), mid + 1, r, L, R, type);
    pushup(rt);
}
fuc(void, updataMin)(int rt, int l, int r, int L , int R, int type) {
    if(L <= l && r <= R) return changeMin(rt, l, r, type), void();
    if(lz1[rt])pushdownMax(rt, l, r);
    if(lz2[rt])pushdownMin(rt, l, r);
    if(L <= mid)updataMin(lsp(rt), l , mid, L, R, type);
    if(R > mid)updataMin(rsp(rt), mid + 1, r, L, R, type);
    pushup(rt);
}
int topMax, stkMax[maxn];
int topMin, stkMin[maxn];
fuc(void, init_but_not_work)(){
    fr(i, 1, n) {
        while(topMax && a[stkMax[topMax]] <= a[i])topMax--;
        lMax[i] = stkMax[topMax] + 1;
        stkMax[++topMax] = i;
        while(topMin && a[stkMin[topMin]] >= a[i])topMin--;
        lMin[i] = stkMin[topMin] + 1;
        stkMin[++topMin] = i;

    }
}
fuc(void, FBI_open_the_door)(int now){
    changeMax(1, 1, n, -1);
    changeMin(1, 1, n, -1);//初始化
    topMax = topMin = 0;
    fr(i, 1, n) {
        while(topMax && a[stkMax[topMax]] <= a[i]){
            updataMax(1, 1, n, stkMax[topMax - 1] + 1, stkMax[topMax], 0);
            //我次栈顶到栈顶以及到i的Max现在都是ai,我假定它和我现在的popcnt不同,所以我先删除,最后再补回来
            topMax--;
        }
        while(topMin && a[stkMin[topMin]] >= a[i]) {
            updataMin(1, 1, n, stkMin[topMin - 1] + 1, stkMin[topMin], 0);
            topMin--;
        }
        if(pop[i] == now){
            stkMax[++topMax] = i;
            updataMax(1, 1, n, lMax[i], i, 1);
            stkMin[++topMin] = i;
            updataMin(1, 1, n, lMin[i], i, 1);
        }
        anss += ans[1];

    }
}

signed main() {
    n = read();
    fr(i, 1, n){
        a[i] = read();
        pop[i] = popcnt(a[i]);
        is[pop[i]] = 1;
    }
    init_but_not_work();
    fr(i, 0, 60) {
        if(is[i])FBI_open_the_door(i);
    }
    printf("%lld",anss);
}
 
 
 
 
```

---

## 作者：gyh20 (赞：2)

一般做这种题有一个常见的套路：从前往后扫 $i$，用单调栈+数据结构维护 $[x,i]$ 的最大值以及最小值，具体的，单调栈的每一次入栈和出栈可以看成一个区间赋值，使用线段树即可。

分开对于每一种 popcount 考虑，在线段树上维护 $\min[x,i]$ 的 popcount 是否为当前枚举的值，$\max$ 同理，最后只用查询两个条件都满足的 $x$ 的个数，相当于维护两个数组 $a,b$ 支持区间 $a/b$ 赋值为 $0/1$，区间查询 $\sum a_ib_i$，很容易维护，直接做就是 $O(n\log a_i\log n)$ 的。

我们发现，区间修改为 $1$ 的总操作个数为 $O(n)$ 个，且每一个区间赋 $0$ 一定不包含/完全包含一个区间赋 $1$ 操作，可以看作将这个操作撤回，对这个区间进行区间赋 $0$，于是现在把线段树的操作也减少到了 $O(n)$ 次，时间复杂度 $O(n(\log a_i+\log n))$，略卡常。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
using namespace std;
const int Mxdt=1000000;
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline ll read(){
	re ll t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int n,m,mx,T1[2100002],T2[2100002],X,Y,Z,num[2100002],tg1[2100002],tg2[2100002],len[2100002],stk1[1000002],stk2[1000002],C[1000002],stk3[1000002],stk4[1000002],nn,L1[1000002],L2[1000002];
ll a[1000002],ans;
inline void Cov1(re int p,re int x){
	num[p]=x*T2[p];
	T1[p]=x*len[p];
	tg1[p]=x;
}
inline void Cov2(re int p,re int x){
	num[p]=x*T1[p];
	T2[p]=x*len[p];
	tg2[p]=x;
}
inline void pd(re int p){
	if(~tg1[p])Cov1(p<<1,tg1[p]),Cov1(p<<1|1,tg1[p]),tg1[p]=-1;
	if(~tg2[p])Cov2(p<<1,tg2[p]),Cov2(p<<1|1,tg2[p]),tg2[p]=-1;
}
inline void Cov1(re int p,re int l,re int r){
	if(l>=X&&r<=Y){
		Cov1(p,Z);
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(X<=mid)Cov1(p<<1,l,mid);
	if(Y>mid)Cov1(p<<1|1,mid+1,r);
	T1[p]=T1[p<<1]+T1[p<<1|1],num[p]=num[p<<1]+num[p<<1|1];
}
inline void Cov2(re int p,re int l,re int r){
	if(l>=X&&r<=Y){
		Cov2(p,Z);
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(X<=mid)Cov2(p<<1,l,mid);
	if(Y>mid)Cov2(p<<1|1,mid+1,r);
	T2[p]=T2[p<<1]+T2[p<<1|1],num[p]=num[p<<1]+num[p<<1|1];
}
inline void build(re int p,re int l,re int r){
	tg1[p]=tg2[p]=-1,len[p]=r-l+1,T1[p]=T2[p]=num[p]=0;
	if(l==r)return;
	re int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	mx=max(mx,p);
}
int main(){
	n=read();
	for(re int i=1;i<=n;++i){
		a[i]=read();
		for(re int j=0;j<=59;++j)if(a[i]&(1ll<<j))++C[i];
	}
	build(1,1,n);
	re int tp3=0,tp4=0;
	for(re int j=1;j<=n;++j){
		while(tp3&&a[stk3[tp3]]<=a[j])--tp3;
		while(tp4&&a[stk4[tp4]]>=a[j])--tp4;
		L1[j]=stk3[tp3],L2[j]=stk4[tp4];
		stk3[++tp3]=j,stk4[++tp4]=j;
	}
	for(re int i=0;i<=59;++i){
		memset(tg1,-1,sizeof(tg1)),memset(tg2,-1,sizeof(tg2)),memset(T1,0,sizeof(T1)),memset(T2,0,sizeof(T2)),memset(num,0,sizeof(num));
		int tp1=0,tp2=0;
		for(re int j=1;j<=n;++j){
			while(tp1&&a[stk1[tp1]]<=a[j]){
				X=stk1[tp1-1]+1,Y=stk1[tp1],Z=0,Cov1(1,1,n),++nn;
				--tp1;
			}
			while(tp2&&a[stk2[tp2]]>=a[j]){
				X=stk2[tp2-1]+1,Y=stk2[tp2],Z=0,Cov2(1,1,n),++nn;
				--tp2;
			}
			if(C[j]==i){
				X=L1[j]+1,Y=j,Z=(C[j]==i),Cov1(1,1,n),++nn;
				X=L2[j]+1,Y=j,Z=(C[j]==i),Cov2(1,1,n),++nn;
			}
			ans+=num[1];
			if(C[j]==i)stk1[++tp1]=j,stk2[++tp2]=j;
		}
	}
	printf("%lld",ans);
}
```


---

## 作者：蒟蒻君HJT (赞：1)

这个做法复杂度与 $\text{popcount}$ 的值域**无关**。

这题。第一眼看上去很不可做的样子。然后发现就是个 trivial 的分类讨论，不太好写。

首先 $\text{popcount}$ 和数值大小并没有关系，所以可以不用去思考它的性质，当成有 $\log a$ 种颜色就可以了。

记号：$lma_i,rma_i$ 表示当左端点落在 $[lma_i,i]$，右端点落在 $[i,rma_i]$ 时最大值在 $a_i$ 处取到。$lmi_i,rmi_i$ 同理表示最小值。同时可以钦定数值相同的左边大。

第一个思路，枚举最大值所在位置。不太好做，因为若是要保证复杂度的话必须启发式分裂，即每次枚举短的一边，但另一边还可能会有一车能产生贡献的最小值位置，所以不太可行。

第二个思路，暴力取中点分治。注意这里的分治指的是最大值最小值分居中点两边，而不是区间跨过中点。这是可以做的。我们考虑计算出所有 $\max$ 在 $\min$ 右边的情况，反过来做法相同，再加上所有长度为 $1$ 的区间，就得到了答案。

不妨假设当前分治区间为 $[l,r]$ 中点为 $mid$。先递归。

然后计算跨过中点的贡献。考虑从 $mid+1$ 向右枚举最大值的可能位置。

发现一些显然但有用的性质：

- 一定从 $mid+1$ 开始的前缀 $\max$ 才可能作为这个最大值。

- 假设这些前缀 $\max$ 的下标从小到大分别为 $i_1,i_2,\cdots i_k$ 则必有 $lma_{i_s}$ 递减，$rma_{i_s}+1=i_{s+1}$。

假设右边最大值的下标为 $m$，考虑左边的最小值的下标为 $m'$，则必须满足 $lma_m \leq m'  \ \text{and} \ rmi_{m'}\geq m$ 这对数才可能有贡献。并且贡献为 $(\min(rma_{m},rmi_{m'})-m+1)(m'-\max(lmi_{m'},lma_{m})+1)$。

这个式子太复杂了，考虑用性质化简。

所有 $[m,rma_m]$ 的无交并产生 $[mid+1,m]$，因此左边的 $\min$ 中，对于每一个 $m'$ 只有唯一一个 $m$ 会使得这个 $\min$ 取到 $rmi_{m'}$，将 $m'$ 按照 $rmi_{m'}$ 升序排序即可枚举。

对于其余的情况，左边的括号中是 $(rma_m-m+1)$ 是一个对于 $m$ 确定的值。这很好。而 $lma_m$ 是递减的，因此右边的 $\max$ 取值对每个 $m'$ 来说只会变化一次，而且变化的时间结点同样可以用双指针求出。

对于取到 $lmi_{m'}$ 的情况，只要对每个颜色开一个桶记录 $\displaystyle \sum (m'-lmi_{m'}+1)$；否则，需要用桶记录的是 $\displaystyle \sum m'$ 和 $\displaystyle \sum [m' \ \text{is valid}]$。

每个 $m'$ 的状态只会产生三次变化：

1. $m'$ 大于等于 $lma_{m}$ 了，产生贡献，用指针根据 $m'$ 从大到小遍历；

2. $lmi_{m'}$ 大于等于 $lma_{m}$ 了，贡献方式变化，用指针根据 $lmi_{m'}$ 从大到小遍历；

3. $rmi_{m'}$ 小于等于 $rma_m$ 了，消去贡献，用指针根据 $rmi_{m'}$ 从小到大遍历。

实现时排序从下往上归并，记录当前每个 $m'$ 的贡献状态，就能做到时间 $\Theta(n\log n)$。我用了 memset 清空桶，复杂度是 $\Theta(n\log n + n\log a)$ 也跑得很快。不用 memset 而是根据用到的颜色来清空的话可以做到 $\Theta(n\log n)$。

[for reference only.](https://codeforces.com/contest/1609/submission/227979634)

---

## 作者：orz_z (赞：1)



枚举最大值和最小值的 `popcount`，扫描线枚举右端点 $r$，记 $f_l$ 表示 $[l,r]$ 中最大值是否等于枚举的 `popcount` $+$ $[l,r]$ 中最小值是否为枚举的 `popcount`，单调栈维护 $f_l$ 的变化，那么答案即为 $f_l=2$ 的 $l$ 的个数，线段树维护即可。时间复杂度均摊 $\mathcal O(n(\log n + \log V))$。

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace Fread
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S, *T;
	inline char getchar()
	{
		if (S == T)
		{
			T = (S = buf) + fread(buf, 1, SIZE, stdin);
			if (S == T)
				return '\n';
		}
		return *S++;
	}
}
namespace Fwrite
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush()
	{
		fwrite(buf, 1, S - buf, stdout);
		S = buf;
	}
	inline void putchar(char c)
	{
		*S++ = c;
		if (S == T)
			flush();
	}
	struct NTR
	{
		~NTR()
		{
			flush();
		}
	} ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

typedef long long ll;

inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10ll + c - '0', c = getchar();
	return x * f;
}

const int _ = 1e6 + 5, M = 62;

int n, t1 = 1, t2 = 1, stk1[_], stk2[_], c[_], cnt[M + 5];

struct abc
{
	int p, l, r, v;
};

vector<abc> k[_ + 5];

ll a[_], ans;

struct node
{
	int l, r, mx, mxc, lz;
} t[_ << 2];

void pushup(int o)
{
	t[o].mx = max(t[o << 1].mx, t[o << 1 | 1].mx);
	t[o].mxc = 0;
	if(t[o].mx == t[o << 1].mx) t[o].mxc += t[o << 1].mxc;
	if(t[o].mx == t[o << 1 | 1].mx) t[o].mxc += t[o << 1 | 1].mxc;
}

void build(int o, int l, int r)
{
	t[o].l = l, t[o].r = r, t[o].mx = t[o].lz = 0, t[o].mxc = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
}

void tag(int o, int v)
{
	t[o].mx += v, t[o].lz += v;
}

void pushdown(int o)
{
	if(t[o].lz)
	{
		tag(o << 1, t[o].lz), tag(o << 1 | 1, t[o].lz), t[o].lz = 0;
	}
}

void update(int o, int l, int r, int v)
{
	if(l <= t[o].l && t[o].r <= r) return tag(o, v), void();
	pushdown(o);
	int mid = (t[o].l + t[o].r) >> 1;
//	if(r <= mid) update(o << 1, l, r, v);
//	else if(l > mid) update(o << 1 | 1, l, r, v);
//	else update(o << 1, l, mid, v), update(o << 1 | 1, mid + 1, r, v);
	if(l <= mid) update(o << 1, l, r, v);
	if(r > mid) update(o << 1 | 1, l, r, v);
	pushup(o);
}

signed main()
{
	n = read();
	for(int i = 1; i <= n; ++i)
	{
		a[i] = read(), c[i] = __builtin_popcountll(a[i]);
		cnt[c[i]]++;
	}
	for(int i = 1, p; i <= n; ++i)
	{
		while(t1 > 1 && a[stk1[t1]] > a[i])
		{
			p = stk1[t1--];
			k[c[p]].push_back({i, stk1[t1] + 1, p, -1});
		}
		k[c[i]].push_back({i, stk1[t1] + 1, i, 1});
		while(t2 > 1 && a[stk2[t2]] <= a[i])
		{
			p = stk2[t2--];
			k[c[p]].push_back({i, stk2[t2] + 1, p, -1});
		}
		k[c[i]].push_back({i, stk2[t2] + 1, i, 1});
		stk1[++t1] = i, stk2[++t2] = i;
	}
	for(int i = 0; i <= M; ++i)
	{
		if(!cnt[i]) continue;
		build(1, 1, n);
		for(int j = 1, cur = 0; j <= n; ++j)
		{
			while(cur < k[i].size() && k[i][cur].p <= j)
			{
				update(1, k[i][cur].l, k[i][cur].r, k[i][cur].v);
				cur++;
			}
			if(t[1].mx == 2) ans += t[1].mxc;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

对于对区间的计数问题，我们可以考虑钦定 $r$ 得到 $l$ 的方案数，$l$ 可行的记作 $1$，否则记作 $0$。

注意到单调栈会把原序列分成若干个段，假设令 $0$ 永远在栈里，那么就会分成左开右闭的段，并且每次都以右端点作为最值。

考虑枚举 `popcount`，这样我们就能算出每段是否符合条件，并且只有弹出栈顶的时候才会更新信息，并且只有区间 $0$ 和 $1$ 之间的变化，所以可以用线段树维护。

我们把递增栈和递减栈都维护到同一个线段树上，这样我们只有点值为 $2$ 的时候才有贡献，而点值最多为 $2$，所以就是一个最大值计数。

如果直接这样做的话，时间复杂度看似是 $O(n\log V\log n)$ 的。但是如果记 $c_i$ 为 $\operatorname{popcount}(a_i)$，用 $x$ 弹出 $y$ 的时候，只有 $c_x\ne c_y$ 的时候修改值非 $0$，而这种情况就只有枚举的 `popcount` 为 $\operatorname{popcount}(a_x)$ 或 $\operatorname{popcount}(a_y)$ 的时候。

因为每个位置都只会删一次，所以只有 $O(n)$ 次修改，查询是 $O(1)$ 的，所以时间复杂度是 $O(n\log n)$ 的。

---

## 作者：qnqfff (赞：0)

### 思路

---

考虑分治。

设当前分治到 $[l,r]$。

枚举右端点 $i \in [mid+1,r]$ 钦定最大值在 $[mid+1,i]$ 中。

那么左端点 $j$ 只要考虑 $\max \limits_{k=j}^{mid}a_k \le \max\limits_{k=mid+1}^{i}a_k$ 的 $j$ 即可。

你知道最大值在 $[mid+1,i]$ 中，但你不知道最小值在哪，因此设一个指针 $p$ 使得 $\min\limits_{k=p}^{mid}a_k \ge \min\limits_{k=mid+1}^{i} a_k$ 且 $\min\limits_{k=j}^{p-1}a_k < \min\limits_{k=mid+1}^{i} a_k$。

分类讨论。

1. 最小值在 $[mid+1,i]$ 中。

答案为 $(mid+1-p) \cdot [\text{popcount}(\max\limits_{k=mid+1}^{i}a_k)=\text{popcount}(\min\limits_{k=mid+1}^{i}a_k)]$。

2. 最小值在 $[j,mid]$ 中。

用一个桶 $t_i$ 表示 $\text{popcount}(\min\limits_{k=j}^{mid}a_k)$ 等于 $i$ 的左端点 $j$ 的数量。

则答案为 $t_{\text{popcount}(\max\limits_{k=mid+1}^{i}a_k)}$。

最大值在 $[l,mid]$ 中的答案也可以通过枚举左端点 $j$ 计算，和上文是类似的。

时间复杂度 $O(n(\log n\ + \log V ))$ 。

### 代码

---

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf,ubuf[1<<23],*u=ubuf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,a[1000010],t[65],pre[1000010];
int solve(int l,int r){
	if(l==r) return 1;int mid=(l+r)>>1,res=0;
	memset(t,0,sizeof(t));pre[mid+1]=1e18;for(int i=mid;i>=l;i--) pre[i]=min(pre[i+1],a[i]);
	for(int i=mid+1,j=mid+1,k=mid+1,mx=0,mi=1e18;i<=r;i++){//枚举右端点
		mx=max(mx,a[i]);mi=min(mi,a[i]);while(j-1>=l&&a[j-1]<=mx) j--,t[__builtin_popcountll(pre[j])]++;while(k-1>=j&&mi<=pre[k-1]) k--,t[__builtin_popcountll(pre[k])]--;
		res+=(mid+1-k)*(__builtin_popcountll(mx)==__builtin_popcountll(mi));res+=t[__builtin_popcountll(mx)];
	}memset(t,0,sizeof(t));pre[mid]=1e18;for(int i=mid+1;i<=r;i++) pre[i]=min(pre[i-1],a[i]);
	for(int i=mid,j=mid,k=mid,mx=0,mi=1e18;i>=l;i--){//枚举左端点
		mx=max(mx,a[i]);mi=min(mi,a[i]);while(j+1<=r&&a[j+1]<mx) j++,t[__builtin_popcountll(pre[j])]++;while(k+1<=j&&mi<=pre[k+1]) k++,t[__builtin_popcountll(pre[k])]--;
		res+=(k-mid)*(__builtin_popcountll(mx)==__builtin_popcountll(mi));res+=t[__builtin_popcountll(mx)];
	}return res+solve(l,mid)+solve(mid+1,r);
}
signed main(){
	n=read();for(int i=1;i<=n;i++) a[i]=read();
	cout<<solve(1,n);
	return 0;
}
```

---

## 作者：Celtic (赞：0)

考虑扫描线。扫右端点，维护左端点的信息。因为有最大值和最小值所以考虑用单调栈来维护。每次加入一个点时考虑和他相反的单调栈，他会影响的是所有 $\operatorname{popcount}$ 和他相同的且在他和栈顶这段区间内的另一个单调栈内的点。

于是考虑开 $64$ 个树状数组，维护每种 $\operatorname{popcount}$ 的答案。存一下单调栈每个位置到上一个位置的距离，树状数组求一下区间和，因为区间内第一个和最后一个位置会多算，所以还需要两次 `lower_bound` 来减去多的答案。这样空间是 $64n$ 的，会 MLE。

考虑离线算每种 $\operatorname{popcount}$ 的答案，只在 $\operatorname{popcount}=k$ 的位置算答案。于是时间是 $O(n \log n)$，空间 $O(n)$，略微卡常可以通过。

<https://codeforces.com/contest/1609/submission/181080451>

---

