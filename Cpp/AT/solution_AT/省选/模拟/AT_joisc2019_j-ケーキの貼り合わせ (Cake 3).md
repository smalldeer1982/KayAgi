# ケーキの貼り合わせ (Cake 3)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2019/tasks/joisc2019_j



## 样例 #1

### 输入

```
5 3
2 1
4 2
6 4
8 8
10 16```

### 输出

```
6```

## 样例 #2

### 输入

```
8 4
112103441 501365808
659752417 137957977
86280801 257419447
902409188 565237611
965602301 689654312
104535476 646977261
945132881 114821749
198700181 915994879```

### 输出

```
2323231661```

# 题解

## 作者：_Cheems (赞：4)

硬想是想不出来滴。考虑 $n=m$ 的特殊情况。

式子的前半部分不变，要令后半部分最小，不难得到贪心策略：从小到大放。这样子代价是 $2(\max b-\min b)$，容易证明这是下界。可以尝试改变下位置，你会发现怎么改都不能更优。

注意到后半部分中，我们只关心最大和最小蛋糕，中间的与 $2(\max b-\min b)$ 没有直接关联。

将蛋糕按 $b$ 从小到大排，对每个 $i$ 求出 $f_i=\max\limits_{1\le j<i}(a_i+a_j-2(b_i-b_j)+w(j+1,i-1))$。

其中，$w(l,r)$ 表示 $[l,r]$ 中选取前 $m-2$ 个最大的 $a$ 的价值。离散化后，用可持久化权值线段树即可 $O(\log n)$ 得出。

虽然它不满足四边形不等式，但打表发现 $f$ 具有决策单调性。

证明：若在 $i$ 时决策点 $x<y$ 且 $x$ 更优，证明在 $i+1$ 时 $x$ 还是更优即可。

将相同项去掉，我们有 $a_x+2b_x+w(x+1,i-1)\ge a_y+2b_y+w(y+1,i-1)$。

着重关注 $w$ 部分，注意到一个关键性质：$w(x+1,i)$ 的增长速度一定比 $w(y+1,i)$ 快。这不难感性理解，因为前者元素总体更小，被替换的原元素也更小，差值就更大。

于是有 $w(x+1,i+1)-w(x+1,i) \ge w(y+1,i+1)-w(y+1,i)$。

与原不等式相加，就可得知决策点 $x$ 在 $i+1$ 时仍然更优。证毕。

分治实现即可，复杂度 $O(n\log^2n)$。
#### 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

#define int long long
#define mid (l + r >> 1)
const int N = 2e5 + 5, inf = -1e15;
int n, _n, m, ans, idw[N], f[N];
struct node{int _a, _b;} a[N]; 

inline bool cmp(node A, node B) {return A._b < B._b;}
inline bool cmpp(int A, int B) {return A > B;}
namespace Zx_Tree{
	struct node{int ls, rs, s, siz;} t[N * 30];
	int rot[N], tot;
	
	inline void psup(int u) {t[u].s = t[t[u].ls].s + t[t[u].rs].s, t[u].siz = t[t[u].ls].siz + t[t[u].rs].siz;}
	inline int S(int x, int y) {return t[y].s - t[x].s;}
	inline int Siz(int x, int y) {return t[y].siz - t[x].siz;}
	inline void upd(int ua, int &ub, int l, int r, int k, int p){
		t[ub = ++tot] = t[ua];
		if(l == r) {t[ub].s += p, ++t[ub].siz; return ;}
		if(k <= mid) upd(t[ua].ls, t[ub].ls, l, mid, k, p);
		else upd(t[ua].rs, t[ub].rs, mid + 1, r, k, p);
		psup(ub);
	} 
	inline int qry(int ua, int ub, int l, int r, int p){
		if(Siz(ua, ub) <= p) return S(ua, ub);
		if(l == r) return p * idw[l];
		if(Siz(t[ua].rs, t[ub].rs) >= p) return qry(t[ua].rs, t[ub].rs, mid + 1, r, p);
		else return S(t[ua].rs, t[ub].rs) + qry(t[ua].ls, t[ub].ls, l, mid, p - Siz(t[ua].rs, t[ub].rs)); 
	}
}using namespace Zx_Tree;
inline int w(int x, int y) {return qry(rot[x - 1], rot[y], 1, n, m - 2);}
inline void calc(int l, int r, int kl, int kr){
	if(l > r || kl > kr) return ;
	int k = kl;
	for(int p = kl; p <= min(mid - m + 1, kr); ++p){
		int W = idw[a[mid]._a] + idw[a[p]._a] + w(p + 1, mid - 1) - (a[mid]._b - a[p]._b);
		if(W >= f[mid]) f[mid] = W, k = p;
	}
	calc(l, mid - 1, kl, k), calc(mid + 1, r, k, kr);
}
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) scanf("%lld%lld", &a[i]._a, &a[i]._b), a[i]._b <<= 1;
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) idw[i] = a[i]._a, f[i] = inf;
	sort(idw + 1, idw + 1 + n), _n = unique(idw + 1, idw + 1 + n) - idw - 1;
	for(int i = 1; i <= n; ++i) a[i]._a = lower_bound(idw + 1, idw + 1 + _n, a[i]._a) - idw;
	for(int i = 1; i <= n; ++i) upd(rot[i - 1], rot[i], 1, n, a[i]._a, idw[a[i]._a]);
	calc(1, n, 1, n); 
	ans = inf; for(int i = 1; i <= n; ++i) ans = max(ans, f[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

先考虑这个式子：

$$\sum_{j=1}^{M} |C_{k_{j}} - C_{k_{j+1}}|$$

一定是在 $C$ 有序时取到，具体证明很简单各位读者自己证明。

那么现在式子变成：

$$\sum{V} + 2 \times({C_{\max} - C_{\min}})$$

这个时候一个常见的技巧是将 $C$ 排序。

这个时候就可以定义状态：

$$dp_{i,j} = \sum{V} + 2 \times (C_{j} - C_{i})$$

然后从贪心的思想出发，$V$ 一定是选取区间 $[i,j]$ 中最大的 $M$ 个。

令 $f(i,j)$ 表示区间 $[i,j]$ 中前 $M$ 大之和，有：

$$dp_{i,j} = f(i,j) + 2 \times (C_{j} - C_{i})$$

考虑去掉一维状态：

$$dp_{i} = \max{(f(i,j) + 2 \times C_{j})} - 2 \times C_i$$

因为 $f(i,j) + 2 \times C_{j}$ 满足四边形不等式，所以 $dp_{i}$ 满足决策单调性，考虑分治优化，$f(i,j)$ 可以直接用主席树求解。

那么我们就 $O(n \log^2 n)$ 地做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//dp[l][r] 表示区间 [l,r] 内前 M 大
//求 max(dp[l][r])
//max_{r>l}(dp[l][r])
//设计状态 dp[i] 表示区间 [i,j] 前 M 大之和减去 2*(c[j]-c[i]) 
//dp[i]=max{f(i,j)-2*c[j]}+2*c[i]
const int maxn = 2e5+114;
const int top = 1e9+114;
const int inf = 2e18+114514;
int dp[maxn];
int n,m;
struct Node{
    int sum,ls,rs;
	int val;
}tr[maxn*35];
struct hhx{
	int c,v;
}a[maxn];
int root[maxn],tot;
inline int kth(int lt,int rt,int L,int R,int k){
    if(lt==rt){
    	return k*lt;
	}
    int mid=(lt+rt)>>1;
    if((tr[tr[R].rs].sum-tr[tr[L].rs].sum)>=k){
        return kth(mid+1,rt,tr[L].rs,tr[R].rs,k);
    }
    else{
        return (tr[tr[R].rs].val-tr[tr[L].rs].val)+kth(lt,mid,tr[L].ls,tr[R].ls,k-(tr[tr[R].rs].sum-tr[tr[L].rs].sum));
    }
}
inline void add(int cur,int lst,int lt,int rt,int pos){
    tr[cur].sum=tr[lst].sum+1;
    tr[cur].val=tr[lst].val+pos;
    if(lt==rt){
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid){
        tr[cur].rs=tr[lst].rs;
        tr[cur].ls=++tot;
        add(tr[cur].ls,tr[lst].ls,lt,mid,pos);
    }
    else{
        tr[cur].ls=tr[lst].ls;
        tr[cur].rs=++tot;
        add(tr[cur].rs,tr[lst].rs,mid+1,rt,pos);
    }
}
//前 k 大之和 
void solve(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	int mx=-inf,p=0;
	for(int i=max(mid+m-1,L);i<=R;i++){
		if(kth(1,top,root[mid-1],root[i],m)-2*a[i].c>mx){
			mx=kth(1,top,root[mid-1],root[i],m)-2*a[i].c;
			p=i;
		}
	}
	dp[mid]=mx+2*a[mid].c;
	solve(l,mid-1,L,p);
	solve(mid+1,r,p,R);
}
bool cmp(hhx A,hhx B){
	return A.c<B.c;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) dp[i]=-inf;
	for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].c;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		root[i]=++tot;
		add(root[i],root[i-1],1,top,a[i].v);
	}
	solve(1,n-m+1,1,n);
	int ans=-inf;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans;
}
```


---

## 作者：To_our_starry_sea (赞：1)

### Solution

首先，注意到这个 $\sum_{i = 1}^m |c_{k_i} - c_{k_{i + 1}}|$ 比较不好处理。考虑已知 $k_i$ 的情况，不难发现当 $c_{k_i}$ 单调不减排序时其的值最小，因此我们将答案转化成以下的形式：

$$
\max(\sum_{i = 1}^m v_{k_i} - 2 \times (\max_{i = 1}^m c_{k_i} - \min_{i = 1}^m c_{k_i}))
$$

这就启发我们按照 $c_i$ 从小到大将蛋糕排序。设 $dp_i$ 表示所取的蛋糕的编号最大为 $i$ 时的答案。则我们可以得到如下的式子：

$$
dp_i = \max_{j = 1}^{i - 1}(v_i + v_j - 2 \times (c_i - c_j) + val(j + 1, i - 1))
$$

其中 $val(i + 1, j - 1)$ 中选择前 $m - 2$ 大的 $v_i$ 的值，容易用可持久化线段树 $O(\log n)$ 解决。这样一来，根据上面的式子，我们就可以暴力的用 $O(n^2 \log n)$ 的时间复杂度解决问题。

接下来我们思考如何优化。注意到 $val(i, j)$ 实际上有着比较好的决策单调性，因此我们从这个角度入手。

设当前为 $i$，$x > y$ 且 $dp_i$ 从 $x$ 转移较从 $y$ 转移更优。即 $v_x + 2 \times c_x  + val(x + 1, i - 1) \ge v_y + 2 \times c_y + val(y + 1, i - 1)$。设 $S_x$ 与 $S_y$ 分别表示 $x$ 和 $y$ 时在 $[x + 1, i - 1]$ 与 $[y + 1, i - 1]$ 中选择蛋糕的集合。考虑当 $i \gets i + 1$ 时，若 $c_{i + 1}$ 不对 $val$ 产生贡献，则显然 $x$ 比 $y$ 仍然更优。否则，我们必然会用 $c_{i + 1}$ 替换掉 $S_x$ 与 $S_y$ 中 $c_k$ 最小的值。注意到我们有 $\min\limits_{k \in S_x} c_k \le \min\limits_{k \in S_y} c_k$，因为若上式不成立，则 $S_y$ 不优。所以对 $val(x, i)$ 的贡献更大。故我们可以得到 $val(x + 1, i) - val(x + 1, i - 1) \ge val(y + 1, i) - val(y + 1, i - 1)$。结合上述不等式可知，选择 $x$ 较选择 $y$ 转移更优。因此我们可以套路的用决策单调性分治来解决问题，时间复杂度为 $O(n \log^2 n)$。

### Code


```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 200005;
const ll INF = 1e18;
int n, m, cnt = 0, tot = 0, rt[MAXN];
ll ans = -INF, b[MAXN];
struct Segment_Tree {
	int ls, rs, sum;
	ll w;
} tr[MAXN << 5];
struct node {
	ll A, B;
	inline bool operator < (const node &b) {
		if (B != b.B) return B < b.B;
		else return A < b.A;
	}
} a[MAXN];
inline void change(int &rt, int x, int l, int r, int w) {
    rt = ++tot;
    tr[rt] = tr[x];
    if (w < l || w > r) return;
    tr[rt].sum++, tr[rt].w += b[w];
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (w <= mid) change(tr[rt].ls, tr[x].ls, l, mid, w);
    else change(tr[rt].rs, tr[x].rs, mid + 1, r, w) ;
}
inline ll query(int nl, int nr, int l, int r, ll k) {
	if (l > r || !k) return 0;
	if (tr[nr].sum - tr[nl].sum <= k) return tr[nr].w - tr[nl].w;
	if (l == r) return 1ll * k * b[l];
	int mid = (l + r) >> 1, res = tr[tr[nr].rs].sum - tr[tr[nl].rs].sum;
	if (res >= k) return query(tr[nl].rs, tr[nr].rs, mid + 1, r, k);
	else return tr[tr[nr].rs].w - tr[tr[nl].rs].w + query(tr[nl].ls, tr[nr].ls, l, mid, k - res);
}
inline void solve(int l, int r, int L, int R) {
	if (L > R || l > r) return;
	ll now = -INF;
	int mid = (L + R) >> 1, way = l;
	for (int i = l; i <= r; i++) {
		if (mid - i + 1 < m) break;
		ll res = b[a[i].A] + b[a[mid].A] - 2 * (a[mid].B - a[i].B);
		res += query(rt[i], rt[mid - 1], 1, cnt, m - 2);
		if (res > now) {
			now = res;
			way = i;
		}
	}
	ans = max(ans, now);
	solve(l, way, L, mid - 1);
	solve(way, r, mid + 1, R);
}
inline ll read() {
	ll x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) a[i].A = read(), a[i].B = read(), b[++cnt] = a[i].A;
	sort(a + 1, a + n + 1);
	sort(b + 1, b + cnt + 1);
	cnt = unique(b + 1, b + cnt + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		int way = lower_bound(b + 1, b + cnt + 1, a[i].A) - b;
		a[i].A = way;
		change(rt[i], rt[i - 1], 1, cnt, a[i].A);
	}
	solve(1, n, 1, n);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# JOISC2019J 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_j)

**题目大意**

> 在 $n$ 个元素中选 $m$ 个并进行排列得到 $s_1\sim s_m$，最大化 $\sum_{i=1}^m v_i-|c_{i+1}-c_i|$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

显然 $c$ 的和最小为 $2|c_{\max}-c_{\min}|$，按 $c$ 小到大排序，区间 $[l,r]$ 的答案就是 $S_k[l,r]-2\times(c_r-c_l)$，其中 $S_k[l,r]$ 表示 $[l,r]$ 内的前 $k$ 大 $v_i$ 值之和。

这是经典的决策单调性模型，分治优化，主席树维护权值即可。

时间复杂度 $\mathcal O(n\log n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,inf=1e9;
const ll infll=1e18;
struct SegmentTree {
	int ls[MAXN<<5],rs[MAXN<<5],cnt[MAXN<<5],tot;
	ll sum[MAXN<<5];
	inline void ins(int u,int l,int r,int q,int &p) {
		p=++tot,cnt[p]=cnt[q]+1,sum[p]=sum[q]+u;
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(u<=mid) ins(u,l,mid,ls[q],ls[p]),rs[p]=rs[q];
		else ins(u,mid+1,r,rs[q],rs[p]),ls[p]=ls[q];
	}
	inline ll qry(int k,int l,int r,int q,int p) {
		if(l==r) return min(k,cnt[p])*l;
		int mid=(l+r)>>1,rc=cnt[rs[p]]-cnt[rs[q]];
		if(k<=rc) return qry(k,mid+1,r,rs[q],rs[p]);
		return sum[rs[p]]-sum[rs[q]]+qry(k-rc,l,mid,ls[q],ls[p]);
	}
}	T;
struct node { int h,v; } a[MAXN];
int n,m,rt[MAXN];
ll dp[MAXN];
inline void solve(int l,int r,int L,int R) {
	if(l>r) return ;
	int mid=(l+r)>>1,M=0;
	for(int i=L;i<=R&&i<=mid-m+1;++i) {
		ll val=T.qry(m,1,inf,rt[i-1],rt[mid])-2*(a[mid].h-a[i].h);
		if(val>dp[mid]) dp[mid]=val,M=i;
	}
	solve(l,mid-1,L,M),solve(mid+1,r,M,R);
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].v,&a[i].h);
	sort(a+1,a+n+1,[&](auto x,auto y){ return x.h<y.h; });
	for(int i=1;i<=n;++i) T.ins(a[i].v,1,inf,rt[i-1],rt[i]);
	memset(dp,-0x3f,sizeof(dp));
	solve(m,n,1,n);
	ll ans=-infll;
	for(int i=m;i<=n;++i) ans=max(ans,dp[i]);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Fracture_Dream (赞：0)

# 简述题意

你要从 $n$ 个蛋糕中选择 $m$ 个，每个蛋糕有 $v,c$ 两个属性，令你选择的蛋糕编号为 $k_1$ 到 $k_m$，请最大化：

$$\sum_{i=1}^{m} v_{k_i} - \sum_{i=1}^{m} | c_{k_i} - c_{k_{i+1}} |$$

注意 $k_{m+1}=k_1$。

# 思路
从贪心的角度思考，为了使 $\sum_{i=1}^{m} | c_{k_i} - c_{k_{i+1}} |$ 尽可能地小，那么就一定有 $c_{k_i} \le c_{k_{i+1}}$，证明显然，考虑此时交换 $k$ 中的某对元素，那么一定不优。
所以，不妨将蛋糕按 $c$ 从小到大排序，那么就等价于求 $\sum_{i=1}^{m} v_{k_i} - 2 \times (c_{k_m}-c_1)$ 的最大值。

不妨令 $cost(i,j)$ 表示 $i,j$ **必选**，从 $[i,j]$ 中选出 $m$ 个蛋糕的最大答案，那么显然有：

$$cost(i,j)=v_i+v_j-2\times(c_j-c_i)+midval$$

其中 $midval$ 表示 $[i+1,j-1]$ 中前 $k-2$ 大的 $v$ 的总和。特定区间前 $k$ 大总和，很容易想到用主席树维护。
那么最终答案为 $cost(i,j),i ,j\in [1,n]$，然而时间复杂度 $O(n^2)$ 显然不优。

考虑决策单调性，~~其实不需要严格证明，把模板写出来套进去，~~大样例过了一般就是对的~~。~~ 

但还是简单提一下，注意到式子中 $cost(i,j)+2 \times c_j$ 满足四边形不等式，令 $dp_i$ 为钦定 $i$ 为结尾的最大值，有：

$$dp_i=cost(i,j)+2\times(c_j-c_i)，j \in [1,i-k+1]$$

分治处理一下就好了。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n , k , dp[MAXN] , lsh[MAXN] , len;
struct node{
	int v , c;
	friend bool operator<(node x , node y) {return x.c < y.c;}
}a[MAXN];
namespace Segement{
	static int tot , rt[MAXN];
	struct tree{
		int l , r , ls , rs , cnt , sum;
	}tree[MAXN << 5];
	int newnode(int p) {
		tree[++ tot] = tree[p];
		return tot;
	}
	int build(int p , int l , int r) {
		p = ++ tot;
		tree[p].l = l , tree[p].r = r;
		if (l == r) return p;
		int mid = l + r >> 1;
		tree[p].ls = build(p , l , mid) , tree[p].rs = build(p , mid + 1 , r);
		return p;
	}
	int update(int p , int x) {
		int now = newnode(p);
		tree[now].cnt ++ , tree[now].sum += lsh[x];
		if (tree[now].l == tree[now].r) return now;
		int mid = tree[p].l + tree[p].r >> 1;
		if (x <= mid) tree[now].ls = update(tree[now].ls , x);
		else tree[now].rs = update(tree[now].rs , x);
		return now;
	}
	int query(int p , int p2 , int kth) {
		if (tree[p].l == tree[p].r) {
			return kth * lsh[tree[p].l];
		}
		int cnt = tree[tree[p2].rs].cnt - tree[tree[p].rs].cnt;
		if (cnt < kth) return tree[tree[p2].rs].sum - tree[tree[p].rs].sum + query(tree[p].ls , tree[p2].ls , kth - cnt);
		return query(tree[p].rs , tree[p2].rs , kth);
	}
} 
using namespace Segement;
int cost(int l , int r) {
	if (k == 2) return 0;
	return query(rt[l - 1] , rt[r] , k - 2);
}
void DP(int l , int r , int ql , int qr) {
	if (l > r) return;
	int mid = l + r >> 1 , qmid = ql;
	for (int i = ql ; i <= min(qr , mid) ; i ++) {
		if (mid - i + 1 < k) continue;
		int lst = cost(i + 1 , mid - 1) + lsh[a[i].v] + lsh[a[mid].v] - 2 * (a[mid].c - a[i].c);
		if (lst > dp[mid]) dp[mid] = lst , qmid = i;
	}
	DP(l , mid - 1 , ql , qmid);
	DP(mid + 1 , r , qmid , qr);
}
signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
	for (int i = 1 ; i <= n ; i ++) cin >> a[i].v >> a[i].c;
	sort(a + 1 , a + n + 1);
	if (k == 1) {
		int Max = -1e18;
		for (int i = 1 ; i <= n ; i ++) Max = max(Max , a[i].v);
		cout << Max;
	} else {
		for (int i = 1 ; i <= n ; i ++) lsh[++ len] = a[i].v;
		sort(lsh + 1 , lsh + len + 1);
		len = unique(lsh + 1 , lsh + len + 1) - lsh - 1;
		rt[0] = build(1 , 1 , len);
		for (int i = 1 ; i <= n ; i ++) {
			a[i].v = lower_bound(lsh + 1 , lsh + len + 1 , a[i].v) - lsh;
			rt[i] = update(rt[i - 1] , a[i].v);
		}
		memset(dp , -0x3f , sizeof(dp));
		DP(1 , n , 1 , n);
		int Max = -1e18;
		for (int i = 1 ; i <= n ; i ++) Max = max(Max , dp[i]);
		cout << Max;
	}
	return 0;
}

```

---

## 作者：Felix72 (赞：0)

发现决策单调性之后这题简直就是整体二分和主席树的板子题，这里说说一个简单严谨的证明。

假设已经按照颜色排好序。

定义区间 $[l, r]$ 的**决策**是在这中间选出 $m$ 个 $v$ 值最大的元素的过程，而 $f(l, r)$ 表示 $[l, r]$ 决策的值。**最优决策**则为左端点固定时，$f$ 值减去颜色差值最大的选法。

考虑两个决策：$[l_1, r_1]$ 和 $[l_2, r_2]$。不妨假设 $l_1 < l_2$ 且 $[l_1, r_1]$ 是以 $l_1$ 为左端点的最优决策。如果 $r_2 < r_1$，我们要证明 $[l_2, r_2]$ 必然不是最优决策。

首先证明一个引理：考虑一个分割点 $lim$，则对于两个相交的**最优**决策 $[l_1, r_1]$ 和 $[l_2, r_2]$，若有 $l_1 \leq l_2 \leq lim$，则前者决策在 $lim$ 前选的元素个数不小于后者决策，$lim$ 后则相反。

道理也不难理解，考虑用堆动态维护前 $m$ 大的过程即可。既然前者在 $lim$ 之前有更多选择，那么之后加入新元素的过程中，若 $lim$ 前元素被替换，则后者决策一定也有元素被替换了。

回到正题，用引理考虑 $[l_1, r_1]$ 和 $[l_2, r_2]$，如果后者也是最优决策，设 $lim = r1$，则根据引理，$(lim, r_1]$ 中选的个数不大于 $(lim, r_2]$ 中选的个数。

但我们发现 $lim = r_2$，也就是说 $(lim, r_2]$ 中选了 $0$ 个元素。那么 $(lim, r_1]$ 这一段也选了 $0$ 个元素，根本没有存在的必要，删去这一段颜色差还可能变小，有矛盾了。

因此这个问题存在决策单调性，直接整体二分即可。

---

