# [JOI Open 2019] 三级跳 / Triple Jump

## 题目描述

**译自 [JOI Open 2019](https://contests.ioi-jp.org/open-2019/index.html) T1 「三段跳び」**

有一条路，包含 $N$ 段，编号 $1\sim N$。第 $i$ 段有一个强度 $A_i$。

JOI 君，有天赋的体育明星，准备来三段跳。一个三段跳包含三次连续的跳跃。令 $a,b,c$ 分别表示 JOI-kun 三次起跳的段编号，他们需要满足以下条件。

- $a<b<c$。含义是每次起跳的编号需要递增。
- $b-a\le c-b$。含义是第一次起跳跨越的距离需要小于等于第二次的。

JOI 君准备进行 $Q$ 次三段跳。在第 $j$ 次（$1\le j\le Q$）中，他需要在区间 $[L_j,R_j]$ 中的编号起跳，也就是要满足 $L_j\le a<b<c\le R_j$。

JOI 君 想要选择恰当的位置起跳。对于每次三段跳，JOI 君想知道他起跳的这些位置的强度和，最大是多少。

写一个程序，给定段数和三段跳的信息。对于每个三段跳，计算他起跳的这些位置的强度和，最大是多少。

## 说明/提示

#### 样例解释：

在第一次跳跃中，JOI 君可以选择 $1,2,4$ 段，从而达到最大加和 $12$。

在第二次跳跃中，JOI 君可以选择 $3,4,5$ 段，从而达到最大加和 $9$。如果选择 $2,4,5$，虽然和是 $10$，但是 $b-a\le c-b$ 没有满足。

在第三次跳跃中，JOI 君可以选择 $1,2,4$ 段，从而达到最大加和 $12$。如果选择 $1,4,5$，虽然和是 $13$，但是 $b-a\le c-b$ 没有满足。

#### 数据范围：

- $3 \le N \le 5 \times 10^5$。
- $1 \le A_i \le 10^8 (1 \le i \le N)$。
- $1 \le Q \le 5 \times 10^5$。
- $1 \le L_j < L_j + 2 \le R_j \le N (1 \le j \le Q)$。

#### 子任务：

1. （5 分）$N\le 100$，$Q\le 100$。
2. （14 分）$N\le 5000$。
3. （27 分）$N\le 2\times 10^5$，$Q=1$，$L_1=1$，$R_1=N$。
4. （54 分）无额外约束。

## 样例 #1

### 输入

```
5
5 2 1 5 3
3
1 4
2 5
1 5```

### 输出

```
12
9
12```

## 样例 #2

### 输入

```
5
5 4 4 5 4
1
1 5```

### 输出

```
14```

## 样例 #3

### 输入

```
15
12 96 100 61 54 66 37 34 58 21 21 1 13 50 81
12
1 15
3 12
11 14
1 13
5 9
4 6
6 14
2 5
4 15
1 7
1 10
8 13```

### 输出

```
277
227
72
262
178
181
174
257
208
262
262
113```

# 题解

## 作者：unicorn1220 (赞：5)

## [JOI Open 2019] Triple Jump

### 题意

给定一个长为 $N$ 的序列 $A$。有 $Q$ 个查询，每次给定 $L,R$，求出满足以下条件的三元组 $(i,j,k)$ 使得 $A_i+A_j+A_k$ 最大。

+ $L \leq i<j<k \leq R$
+ $j-i \leq k-j$

### 题解

暴力枚举情况太多，所以考虑去掉某些无需枚举的情况。

什么时候可以扔掉一个情况 $p_1(i_1,j_1,k_1)$ 呢？当存在一个 $p_2(i_2,j_2,k_2)$ 一定不劣于 $p_1$ 时。

这里的不劣于，需要考虑两个条件。第一，$p_2$ 的贡献一定要比 $p1$ 大。第二，如果 $p1$ 对于一组 $(L,R)$ 合法，那么 $p2$ 也合法，即区间 $[i_2,k_2]$ 被 $[i_1,k_1]$ 包含。

也就是说，满足 $A_{i_1}+A_{j_1}+A_{k_1} \leq A_{i_2}+A_{j_2}+A_{k_2}$，且 $i_1 \leq i_2 < k_2 \leq k_1$。

然而，这种约束情况一不太好找，二过于苛刻，可能会导致去掉的情况不够多。

我们观察 $j-i \leq k-j$ 这个式子，显然当我们钦定 $i,j$ 时，$k$ 的取值范围是一个后缀，准确来说是 $[2j-i,n]$。这样的话，如果我们缩小区间 $[i,j]$，那么 $k$ 的取值范围一定是只会变大的。

我们惊奇的发现，这个缩小后的区间，正好对应了 $p2$。于是我们把约束条件中的 $k$ 去掉，变成 $A_{i_1}+A_{j_1} \leq A_{i_2}+A_{j_2}$，且 $i_1 \leq i_2 < j_2 \leq j_1$。这时，$i,j$ 的贡献保证了不劣，而因为 $p2$ 的区间 $[i_2,j_2]$ 更小，所以 $k_2$ 的取值范围更大，也就保证了不劣。

现在来看还剩下多少有用情况。上面的式子意味着对于 $i,j$，如果他们之间存在 $i'$ 使得 $A_i < A_{i'}$ 或 $A_j < A_{i'}$，那么 $(i,j)$ 就会被 $(i',j)$ 替代，它就没用了。即有用区间可以表示为 $[i,j]$ 使得 $\min(a[i],a[j]) > \max^{j-1}_{k=i+1}(a[k])$。我们令 $L_i$ 为 $i$ 之前最后一个比 $A_i$ 大的 $A_{L_i}$， $R_i$ 为 $i$ 之后第一个比 $A_i$ 大的 $A_{R_i}$。此时，所有的 $(L_i,i]$ 和 $[i,R_i)$ 即可描述所有的有用情况，最多 $2n$ 种。

这么少的情况可以直接用线段树维护。对于所有有用情况 $(l_i,r_i)$ ,区间 $[2j-i,n]$ 的所有数都可以获得 $A_{l_i}+A_{r_i}$ 的贡献，取 $\max$ 加上原本的数即为答案。而 $L_i,R_i$ 可以随便用单调栈维护。加上查询总复杂度为 $O((n+q)\log n)$。

最后，在处理询问时，有用区间应该按左端点降序插入线段树，同时边插边把当前左端点的询问做了，因为我们要保证插入线段树的区间也在询问范围内。

代码放个主函数吧。

```cpp
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    build(1,1,n);scanf("%lld",&Q);
    for(int i=1,ai,bi;i<=Q;i++) scanf("%lld%lld",&ai,&bi),ask[ai].push_back(make_pair(bi,i));
    for(int i=1;i<=n;i++)
    {
        while(!q.empty()&&a[i]>a[q.top()]) q.pop();
        if(!q.empty()) qj[q.top()].push_back(i);
        q.push(i);
    }//找Li
    while(!q.empty()) q.pop();
    for(int i=n;i>=1;i--)
    {
         while(!q.empty()&&a[i]>a[q.top()]) q.pop();
        if(!q.empty()) qj[i].push_back(q.top());
        q.push(i);
    }//找Ri
    for(int i=n;i>=1;i--)//倒着插入
    {
        for(int j:qj[i]) update(1,1,n,2*j-i,n,a[j]+a[i]);
        for(auto j:ask[i]) ans[j.second]=query(1,1,n,i,j.first);
    }
    for(int i=1;i<=Q;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：strcmp (赞：5)

联考的原题，被乱搞冲了 $95$，感觉比 CF765F 更适合用来当支配对引入题（如果要问什么乱搞的话，大概就是取出区间内前 $K$ 个数，钦定两个数对在这堆数里面，然后剩下的是一个 RMQ，当然能被卡）。

考虑点对 $l \le x < y < z \le r$，我们的限制是 $y - x \le z - y$。

仔细观察这个式子，如果我们钦定了 $x,\,y$，那么合法的 $z$ 显然是 $[l,\,r]$ 区间的一段后缀。

支配对的思想是这样的：如果点对 $p_1$ 无论如何不可能优秀于 $p_2$，那么任何时刻不再考虑 $p_1$。

对于我们考虑 $p_2$ 一定不劣于 $p_1$ 的条件。

- $p_1$ 如果合法，那么 $p_2$ 必须合法，我们需要的是**一定不劣**，因此如果我们不考虑 $p_2$ 的合法性直接抛弃 $p_1$，那么我们就可能在这个区间内找不到答案（$p_1$ 被抛弃，$p_2$ 不合法）。

- 如果 $p_1$ 和 $p_2$ 都合法，那么 $p_2$ 的权值一定不小于 $p_1$ 的权值（前置条件）。

- 在两个基础上，我们希望这个严格不劣于的条件**越弱越好**，这样我们就可以排除更多更平凡的点对，降低我们的复杂度了。

我们来考虑 $p_1 = (x_1,\,y_1,\,z_1)$ 和 $p_2 = (x_2,\,y_2,\,z_2)$。

首先 $x_1 \le x_2 \wedge z_2 \le z_1$，然后 $a_{x_1} + a_{y_1} + a_{z_1} \le a_{x_2} + a_{y_2} + a_{z_2}$。那么 $p_1$ 被 $p_2$ 偏序了。

但是这个条件太强了，考虑能不能弱化一下它。

你发现固定 $x,\,y$，那么 $z$ 一定是一个后缀。

并且 $y - x$ 越小，那么 $z$ 的限制越少，那么如果 $\max a_x + a_y$ 的值不变的情况下，$y - x$ 越小，答案越可能更大（答案至少不会减小）。

那么我们直接让 $p_1 = (x_1,\,y_1)$ 且 $p_2 = (x_2,\,y_2)$，并且 $x_1 \le x_2 < y_2 \le y_1$。

$p_2$ 偏序 $p_1$ 的条件就是 $a_{x_1} + a_{y_1} \le a_{x_2} + a_{y_2}$。

那不妨考虑 $[x_1,\,y_1]$ 内怎么找偏序它的一个点对，很显然，虽然找一个不小于 $a_{x_1}$ 或者 $a_{y_1}$ 的 $a_k$，然后用 $k$ 替换掉较小的那个端点即可。

于是经过若干次这样的操作，最后我们得到的是 $[l,\,r]$，满足 $a_l,\,a_r$ 都比 $(l,\,r)$ 开区间最大值**严格**大。

这样的区间数一看就知道很少，实际上，求出 $L_i$ 代表 $i$ 之前最后一个比 $a_i$ 大的 $a_{L_i}$，$R_i$ 代表 $i$ 之后第一个比 $a_i$ 大的 $a_{R_i}$。这里使用悬线法可以直接求。

所有区间 $(L_i,\,i],\,[i,\,R_i)$ 显然描述了所有的“满足 $a_l,\,a_r$ 都比 $(l,\,r)$ 开区间最大值严格大的区间”。

这样的区间，显然最多只有 $2n$ 个。

于是现在这些区间就相当于有一个自己的值，并且会贡献到一个区间的后缀上，也就是让一个区间对一个值 $v$ 取 $\max$。就令这些取 $\max$ 的结果为 $b$。

同时每个位置有一个承担 $z$ 的责任，因此还有一个不会变的值 $c_i = a_i$。

扫描线先去掉那个 $l \le x$ 的限制。

然后我们 $[l,\,r]$ 的询问，相当于求 $\max\limits_{l \le i \le r} b_i + c_i$。

考虑线段树进行维护，$c_i$ 不会变，直接维护 $c$ 的最大值，然后再用个额外信息维护答案。这是双半群，是可以维护的。

区间对 $v$ 取 $\max$ 使用 beats？

又没有其它修改操作，标记合并直接让更大的 $v$ 成为标记即可。

时间复杂度 $\Theta((n + Q) \log n)$。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pq = priority_queue<int>;
using vec = vector<int>;
constexpr int maxn = 5e5 + 10, N = maxn, mod = 1e9 + 7, B = 600; constexpr ll inf = 1e18;
inline ll ksm(ll a, int b = mod - 2) { ll ls = 1; while (b) (b & 1) && (ls = ls * a % mod), a = a * a % mod, b >>= 1; return ls; }
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
struct Node { int mx, tg, v; } t[maxn << 2]; int a[maxn], n, Q;
#define mx(x) (t[x].mx)
#define tg(x) (t[x].tg)
#define val(x) (t[x].v)
inline void up(int x) { mx(x) = max(mx(ls(x)), mx(rs(x))); }
inline void ptg(int x, int k) { tg(x) = max(tg(x), k); mx(x) = max(mx(x), tg(x) + val(x)); }
inline void down(int x) { if (!tg(x)) return; ptg(ls(x), tg(x)), ptg(rs(x), tg(x)); }
void bd(int l, int r, int x) { if (l == r) return void(val(x) = mx(x) = a[l]); bd(l, mid, ls(x)), bd(mid + 1, r, rs(x)), up(x); val(x) = max(val(ls(x)), val(rs(x))); }
void mdf(int l, int r, int ml, int mr, int v, int x) {
	if (ml <= l && r <= mr) return ptg(x, v); down(x);
	ml <= mid && (mdf(l, mid, ml, mr, v, ls(x)), 1), mr > mid && (mdf(mid + 1, r, ml, mr, v, rs(x)), 1); up(x);
}
int qry(int l, int r, int ql, int qr, int x) {
	if (ql <= l && r <= qr) return mx(x); down(x); int ans = 0;
	ql <= mid && (ans = qry(l, mid, ql, qr, ls(x))), qr > mid && (ans = max(ans, qry(mid + 1, r, ql, qr, rs(x)))); return ans;
}
int L[maxn], R[maxn], ans[maxn]; vector<pii> q[maxn]; vec d[maxn];
int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]), L[i] = R[i] = i;
	rep(i, 1, n) {
		while (L[i] > 1 && a[i] > a[L[i] - 1]) L[i] = L[L[i] - 1];
		if (L[i] - 1 >= 1) d[L[i] - 1].pb(i);
	}
	per(i, n, 1) {
		while (R[i] < n && a[i] > a[R[i] + 1]) R[i] = R[R[i] + 1];
		if (R[i] + 1 <= n) d[i].pb(R[i] + 1);
	}
	bd(1, n, 1); scanf("%d", &Q);
	for (int i = 1, l, r; i <= Q; i++) scanf("%d%d", &l, &r), q[l].pb({ r, i });
	per(l, n, 1) {
		for (int r : d[l]) if (2 * r - l <= n) mdf(1, n, 2 * r - l, n, a[l] + a[r], 1);
		for (pii x : q[l]) ans[x.Y] = qry(1, n, l, x.X, 1);
	}
	rep(i, 1, Q) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：4)

偶遇联考原题。感觉这个题分析错方向就没救了。

### Solution

考虑一对 $a,b$。如果 $\min(A_a,A_b)\le \max_{i=a+1}^{b-1}A_i$，则将 $a$ 或 $b$ 的其中一个调整为 $\arg\max_{i=a+1}^{b-1}A_i$ 一定不劣。

所以说 $\min(A_a,A_b)>\max_{i=a+1}^{b-1}A_i$，考虑分析这样的 $(a,b)$ 数量。若 $A_a\le A_b$，那么 $b$ 只能为 $(a,n]$ 中第一个 $\ge A_a$ 的数；否则，$a$ 只能为 $[1,b)$ 中最后一个 $>A_b$ 的数。于是这样的 $(a,b)$ 一共只有 $O(n)$ 对。

我们已经把可能有贡献的 $(a,b)$ 找出来了，剩下的条件就是 $2b-a\le c$ 与 $l\le a$。考虑新序列 $B_i=\max\limits_{(a,b),2b-a=i}A_a+A_b$，则答案就是 $\max\limits_{l\le i\le j\le r}B_i+A_j$。对左端点扫描线，动态加入合法的 $(a,b)$，线段树做即可。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=5e5+5;
constexpr ll INF=1e15;
int n,q,a[N];
int st[20][N],lg[N];
void initST(){
	lg[1]=0;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)st[0][i]=a[i];
	for(int i=1;i<=19;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
inline int askmax(int l,int r){
	int lim=lg[r-l+1];
	return max(st[lim][l],st[lim][r-(1<<lim)+1]);
}
struct node{
	int x,v;
	node(){x=v=0;}
	node(int _x,int _v){x=_x,v=_v;}
};
vector<node> mdf[N],qry[N];
struct Tnode{
	ll a,b,ab;
	Tnode(){a=b=ab=0;}
	Tnode(ll _a,ll _b,ll _ab){a=_a,b=_b,ab=_ab;}
	Tnode operator +(const Tnode &_)const{
		return Tnode(max(a,_.a),max(b,_.b),max({ab,_.ab,a+_.b}));
	}
};
int L[N<<2],R[N<<2],M[N<<2];Tnode Max[N<<2];
void build(int l,int r,int p=1){
	L[p]=l,R[p]=r,M[p]=(l+r)>>1;
	if(l==r){
		Max[p]=Tnode(-INF,a[l],-INF);
		return;
	}
	build(L[p],M[p],p<<1);
	build(M[p]+1,R[p],p<<1|1);
	Max[p]=Max[p<<1]+Max[p<<1|1];
}
void modify(int x,int v,int p=1){
	if(L[p]==R[p]){
		Max[p].a=max(Max[p].a,(ll)v);
		Max[p].ab=Max[p].a+Max[p].b;
		return;
	}
	if(x<=M[p])modify(x,v,p<<1);
	else modify(x,v,p<<1|1);
	Max[p]=Max[p<<1]+Max[p<<1|1];
}
Tnode query(int l,int r,int p=1){
	if(l<=L[p]&&R[p]<=r)return Max[p];
	Tnode res(-INF,-INF,-INF);
	if(l<=M[p])res=query(l,r,p<<1)+res;
	if(M[p]<r)res=res+query(l,r,p<<1|1);
	return res;
}
ll ans[N];
bool Med;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cerr<<abs(&Mst-&Med)/1048576.0<<'\n';
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	initST();
	for(int i=1;i<=n;i++){
		if(i>1){
			int l=0,r=i-1,mid;
			while(l<r){
				mid=(l+r+1)>>1;
				if(askmax(mid,i-1)>=a[i])l=mid;
				else r=mid-1;
			}
			if(i*2-l<=n)
				mdf[l].emplace_back(i*2-l,a[l]+a[i]);
		}
		if(i<n){
			int l=i+1,r=n+1,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(askmax(i+1,mid)>=a[i])r=mid;
				else l=mid+1;
			}
			if(r*2-i<=n)
				mdf[i].emplace_back(r*2-i,a[i]+a[r]);
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int l,r;cin>>l>>r;
		qry[l].emplace_back(r,i);
	}
	build(1,n);
	for(int i=n;i>=1;i--){
		for(auto &o:mdf[i])modify(o.x,o.v);
		for(auto &o:qry[i])ans[o.v]=query(i,o.x).ab;
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
	cerr<<1000.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

感觉调整的东西错了啊，倒闭了 /ll

考虑分析最优情况下 $(a,b,c)$ 的结构。如果 $\exists a < i < b$ 使得 $v_i \ge \min\{v_a,v_b\}$，则可以将 $a$ 和 $b$ 中的一个替换为 $i$。

这样得出 $\min\{v_a,v_b\} > \max_{a<i<b} v_i$。这很类似 JOISC2017D，得到只有 $O(n)$ 对可能的 $(a,b)$。

一对 $(a,b)$ 确定后，它可以对 $\ge 2b-a+1$ 的 $c$ 都产生贡献。

随便扫描线，可以将问题转化为：

维护序列 $a$、$b$，有两种操作（$b$ 序列给定，$a$ 初始全是 $0$）

- `1 l r v`，表示 $a_i \leftarrow \max\{a_i,v\}$，对 $l \le i \le r$。
- `2 l r`，询问 $\max_{l \le i \le r} \{a_i+b_i\}$。

这个东西看着就可以随便维护。

$n$ 和 $q$ 同阶时，复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,q,a[MAXN],mx[MAXN<<2],ma[MAXN<<2],tag[MAXN<<2];
void build(int k,int l,int r) {
	if(l==r) return mx[k]=ma[k]=a[l],void();
	build(lson,l,mid),build(rson,mid+1,r);
	return mx[k]=max(mx[lson],mx[rson]),ma[k]=max(ma[lson],ma[rson]),void();	
}
void push_down(int k,int l,int r) {
	ma[lson]=max(ma[lson],mx[lson]+tag[k]),ma[rson]=max(ma[rson],mx[rson]+tag[k]);
	tag[lson]=max(tag[lson],tag[k]),tag[rson]=max(tag[rson],tag[k]);
	return ;	
}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return ma[k]=max(ma[k],mx[k]+v),tag[k]=max(tag[k],v),void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	return ma[k]=max(ma[lson],ma[rson]),void();
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return ma[k];
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return max(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
int ans[MAXN];
vector<pair<int,int>> qr[MAXN];
vector<int> upd[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	build(1,1,n),cin>>q;
	ffor(i,1,q) {int l,r;cin>>l>>r,qr[l].push_back({r,i});}
	stack<int> st;
	ffor(i,1,n) {
		while(!st.empty()&&a[i]>a[st.top()]) st.pop();
		if(!st.empty()) upd[st.top()].push_back(i);
		st.push(i);
	}
	while(!st.empty()) st.pop();
	roff(i,n,1) {
		while(!st.empty()&&a[i]>a[st.top()]) st.pop();
		if(!st.empty()) upd[i].push_back(st.top());
		st.push(i);	
	}
	roff(i,n,1) {
		for(auto id:upd[i]) if(2*id-i<=n) update(1,1,n,2*id-i,n,a[i]+a[id]);
		for(auto pr:qr[i]) ans[pr.second]=max(ans[pr.second],query(1,1,n,i,pr.first));
	}
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：2)

# 题目思路

以下用 $a$ 表示原数组 $A$，$i,j,k$ 对应原文的 $a,b,c$。

模拟赛题，一个一个 sub 想可能简单点？

sub 1 直接暴力枚举所有情况就能过。

sub 2 **如果**是单测 $[1,n]$ 的情况下（话说我做出这题之后都不知道这档分咋做？？），可以发现我们只要枚举 $i,j$。合法的 $k$ 是一段后缀。直接用树状数组或者线段树维护后缀 $\max$ 即可。

考虑 sub 3。发现这个 $i,j$ 如果缩小到 $i\leq i'\leq j'\leq j$，那么 $k$ 的可行范围只会增大。$a_k$ 的选择是不劣的，我们尝试把 $i,j$ 缩小到一个最优的情况。只要中间有比 $\min\{a_i,a_j\}$ 大的数，就一定可以把 $i$ 或 $j$ 挪过去。递归地考虑这个过程，结束情况代表 $a_i,a_j$ 都比 $[i+1,j-1]$ 中间的大。

这个结束状态相当于是，前方第一个比自己大的 $pre_i$ 和自己 $i$，自己 $i$ 和后方第一个比自己大的 $nxt_i$，这两对区间。单调栈不难求出。**这样的区间只有 $\mathcal O(n)$ 个**。

考虑多测的情况。根据 sub 2 的做法，我们先求出每组 $i,j$ 对应的 $k$ 的范围。移项得到 $k\geq 2j-i$。加入的时候要保证 $i,j,k$ 至少都要 $\geq l$，所以倒序枚举 $l$。加入的时候就是对一个后缀 $[2j-i,n]$ 打标记，$tag_k\gets \max\{tag_k,a_i+a_j\}$。之后要求的是 $[l,r]$ 之间最大的 $tag_k+a_k$。通过线段树不难实现。这里线段树实现需要一个附加一个静态区间 $\max$，但是可以发现求的范围一定是线段树的一个节点的范围。在建树的时候多求一个 $mxk_i$ 表示这个节点内最大的 $a_k$ 即可。代码除去快读快写还是很短的。

# 完整代码

[洛谷 record 198020029](https://www.luogu.com.cn/record/198020029)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
#define FIO(s)                    \
    freopen(s ".in", "r", stdin); \
    freopen(s ".out", "w", stdout);
int n, Q;
int a[500020];
int ans[500020];
vector<array<int, 2>> q[500020];
int stk[500020], top;
int pre[500020];
int nxt[500020];
vector<int> vec[500020];
struct SegTree
{
    struct node
    {
        int mx, mxk, lzy;
    } t[500020 << 2];
#define ls id << 1
#define rs id << 1 | 1
    void push_up(int id) { t[id].mx = max(t[ls].mx, t[rs].mx); }
    void push_down(int id, int l, int r)
    {
        chkmx(t[ls].lzy, t[id].lzy);
        chkmx(t[rs].lzy, t[id].lzy);
        t[ls].mx = max(t[ls].mx, t[ls].mxk + t[ls].lzy);
        t[rs].mx = max(t[rs].mx, t[rs].mxk + t[rs].lzy);
    }
    void build(int id = 1, int l = 1, int r = n)
    {
        t[id].lzy = 0;
        if (l == r)
            return t[id].mx = t[id].mxk = a[l], void();
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        push_up(id);
        t[id].mxk = max(t[ls].mxk, t[rs].mxk);
    }
    void modify(int ql, int qr, int k, int id = 1, int l = 1, int r = n)
    {
        if (r < ql || l > qr)
            return;
        if (ql <= l && r <= qr)
            return chkmx(t[id].lzy, k), t[id].mx = max(t[id].mx, t[id].mxk + t[id].lzy), void();
        push_down(id, l, r);
        int mid = l + r >> 1;
        modify(ql, qr, k, ls, l, mid);
        modify(ql, qr, k, rs, mid + 1, r);
        push_up(id);
    }
    int query(int ql, int qr, int id = 1, int l = 1, int r = n)
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return t[id].mx;
        push_down(id, l, r);
        int mid = l + r >> 1;
        return max(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    }
} T;
int main()
{
    // FIO("triple");
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    read(Q);
    for (int i = 1; i <= Q; i++)
    {
        int l, r;
        read(l, r);
        q[l].push_back({r, i});
    }
    a[0] = a[n + 1] = 1e9;
    stk[top = 1] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (top && a[stk[top]] < a[i])
            top--;
        pre[i] = stk[top];
        stk[++top] = i;
    }
    stk[top = 1] = n + 1;
    for (int i = n; i >= 1; i--)
    {
        while (top && a[stk[top]] < a[i])
            top--;
        nxt[i] = stk[top];
        stk[++top] = i;
    }
    // for (int i = 1; i <= n; i++)
    //     cout << pre[i] << ' ';
    // cout << '\n';
    // for (int i = 1; i <= n; i++)
    //     cout << nxt[i] << ' ';
    // cout << '\n';
    for (int i = 1; i <= n; i++)
    {
        if (pre[i] != 0)
            vec[pre[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (nxt[i] != n + 1)
            vec[i].push_back(nxt[i]);
    }
    T.build();
    for (int l = n; l >= 1; l--)
    {
        for (int r : vec[l])
        {
            if (r + r - l <= n)
                T.modify(r + r - l, n, a[l] + a[r]);
        }
        // cout << l << '\n';
        for (auto [r, id] : q[l])
            ans[id] = T.query(l, r);
        // for (int i = 1; i <= n; i++)
        //     cout << T.query(i, i) << ' ';
        // cout << '\n';
    }
    for (int i = 1; i <= Q; i++)
        write(ans[i], '\n');
    return 0;
}
```

---

## 作者：VainSylphid (赞：2)

看到要找一个三元组，容易想到的事情是去分析支配对。如果直接分析三元组的性质会很困难，但是如果我们把目光集中在 $a,b$ 上，会得到一个很重要的观察：若存在 $i$ 使得 $a<i<b$ 且 $A_a,A_b\leq A_i$，那么把 $a$ 换成 $i$，和没有变小，能贡献的询问区间却变多了。

因此，我们只需要关注满足 $a,b$ 之间的所有数都小于 $\min(A_a,A_b)$ 的 $a,b$ 对。进一步观察发现实际上只有每个数和它左侧或右侧第一个大于等于它的数满足这样的条件。所以这样的 $a,b$ 对的数量是 $O(N)$ 的，可以用单调栈求出。

找出所有 $a,b$ 对后，考虑能和 $a,b$ 对产生贡献的 $c$ 的形式，应当满足 $c-b\geq b-a$ 也就是 $c\geq 2b-a$。那么容易想到的一个事情是从左到右扫描线，对于每个 $a,b$ 对，在 $2b-a$ 的位置加入它的贡献，同时用线段树维护 $A_c$ 的区间最大值以及 $A_a+A_b+A_c$ 的区间最大值（维护前者是为了在修改时快速维护后者）。为了进行查询，在建立线段树前需要将 $a,b$ 对按照 $A_a$ 从小到大排序（注意排序的顺序和插入线段树的顺序是不同的），这样查询的就是线段树上一段连续区间的 $A_a+A_b+A_c$ 的最大值。

然后就做完了，时间复杂度 $O((N+Q)\log N)$。不过这真的是蓝题么？


```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
struct sgt{
	int v[4000005],w[4000005],d[4000005];
	void pushdown(int p)
	{
		if(!w[p])
			return;
		d[p << 1] = max(d[p << 1],v[p << 1] + w[p]);
		w[p << 1] = max(w[p << 1],w[p]);
		d[p << 1 | 1] = max(d[p << 1 | 1],v[p << 1 | 1] + w[p]);
		w[p << 1 | 1] = max(w[p << 1 | 1],w[p]);
		w[p] = 0;
	}
	void pushup(int p)
	{
		v[p] = max(v[p << 1],v[p << 1 | 1]);
		d[p] = max(d[p << 1],d[p << 1 | 1]);
	}
	void build(int p,int l,int r)
	{
		if(l == r)
		{
			v[p] = -inf,w[p] = 0,d[p] = -inf;
			return;
		}
		int mid = l + r >> 1;
		build(p << 1,l,mid);
		build(p << 1 | 1,mid + 1,r);
		pushup(p);
	}
	void insert(int p,int l,int r,int x,int k)
	{
		if(l == r)
		{
			v[p] = k;
			w[p] = 0;
			d[p] = k + w[p];
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if(x <= mid)
			insert(p << 1,l,mid,x,k);
		else
			insert(p << 1 | 1,mid + 1,r,x,k);
		pushup(p);
	}
	void modify(int p,int l,int r,int x,int y,int k)
	{
		if(x <= l && r <= y)
		{
			w[p] = max(w[p],k);
			d[p] = max(d[p],v[p] + k);
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if(x <= mid)
			modify(p << 1,l,mid,x,y,k);
		if(y > mid)
			modify(p << 1 | 1,mid + 1,r,x,y,k);
		pushup(p);
	}
	int query(int p,int l,int r,int x,int y)
	{
		if(x <= l && r <= y)
			return d[p];
		pushdown(p);
		int mid = l + r >> 1;
		if(x <= mid && y > mid)
			return max(query(p << 1,l,mid,x,y),query(p << 1 | 1,mid + 1,r,x,y));
		else if(x <= mid)
			return query(p << 1,l,mid,x,y);
		return query(p << 1 | 1,mid + 1,r,x,y);
	}
}tr;
int n,m,a[500005],stk[500005],tp,pre[500005],nxt[500005];
struct node{
	int pa,pb,s;
}t[1000005];
int pos;
vector<int> v[500005];
bool cmp(node A,node B)
{
	return A.pa < B.pa;
}
int ql[500005],qr[500005],ans[500005];
vector<int> q[500005];
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i <= n;i++)
	{
		pre[i] = 0;
		while(tp && a[stk[tp]] < a[i])
			tp--;
		if(tp)
			pre[i] = stk[tp];
		stk[++tp] = i;
	}
	tp = 0;
	for(int i = n;i;i--)
	{
		nxt[i] = n + 1;
		while(tp && a[stk[tp]] < a[i])
			tp--;
		if(tp)
			nxt[i] = stk[tp];
		stk[++tp] = i;
	}
	for(int i = 1;i <= n;i++)
	{
		if(pre[i] > 0)
			t[++pos] = {pre[i],i,a[pre[i]] + a[i]};
		if(nxt[i] <= n)
			t[++pos] = {i,nxt[i],a[i] + a[nxt[i]]};
	}
	sort(t + 1,t + 1 + pos,cmp);
	for(int i = 1;i <= pos;i++)
		if(2 * t[i].pb - t[i].pa <= n)
			v[2 * t[i].pb - t[i].pa].push_back(i);
	scanf("%d",&m);
	for(int i = 1;i <= m;i++)
		scanf("%d%d",&ql[i],&qr[i]),q[qr[i]].push_back(i);
	tr.build(1,1,pos);
	for(int i = 1;i <= n;i++)
	{
		for(auto j : v[i])
			tr.insert(1,1,pos,j,t[j].s);
		tr.modify(1,1,pos,1,pos,a[i]);
		for(auto j : q[i])
		{
			int pl = 1,pr = pos;
			while(pl <= pr)
			{
				int mid = pl + pr >> 1;
				if(t[mid].pa < ql[j])
					pl = mid + 1;
				else
					pr = mid - 1;
			}
			ans[j] = tr.query(1,1,pos,pl,pos);
		}
	}
	for(int i = 1;i <= m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

支配对好题。

对于第一次跳跃的 $(i,j)$ 进行考虑，根据题目的跳跃约束条件 $j-i\le k-j$，我们其实是希望其间距尽可能小。同时题目要求最大化 $a_i+a_j+a_k$，我们肯定是希望 $a_i+a_j$ 尽可能大。在这两个条件之下，我们可以发现对于 $(l,r)$，如果存在 $l\le i < j\le r$，满足 $a_i+a_j\ge a_l+a_r$，这个时候 $(l,r)$ 是没有用的，因为任何时候都可以将 $(l,r,k)$ 替换为 $(i,j,k)$ 这个调整是不劣的，因为 $(i,j)$ 在区间间距和权值两个维度都比 $(l,r)$ 优秀。

所以我们其实是要找出所有点对 $(l,r)$ 满足，$\max\limits_{l<i<r} a_i< \min(a_l,a_r)$。这个条件等价于建立小根笛卡尔树之后，某个点管辖的区间为 $[l+1,r-1]$。由笛卡尔树的节点数可知，这样子的有效点对是 $O(n)$ 对的。具体来说，可以正反做两遍单调栈来找到所有支配对。

确定前两个点的最优二元组之后，第三个点 $k$ 需要满足 $k\ge 2\times j-i$。

对于区间询问转化为扫描线，用线段树下标为 $k$ 的线段树维护区间 $\max a_i+b_i$，同时支持对于 $a_i$ 进行 chkmax。

时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
vector<int> ad[maxn];
vector<pair<int,int> > q[maxn];
int c[maxn],st[maxn],ans[maxn],n,Q,top;
struct SegmentTree{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid (l+r>>1)
	int b[maxn<<2],val[maxn<<2],tag[maxn<<2];
	void pushup(int p){
		b[p]=max(b[ls],b[rs]);
		val[p]=max(val[ls],val[rs]);
	}
	void upd(int p,int v){
		val[p]=max(val[p],v+b[p]); 
		tag[p]=max(tag[p],v);
	}
	void pushdown(int p){
		if(!tag[p]) return ;
		upd(ls,tag[p]); upd(rs,tag[p]); tag[p]=0;
	}
	void build(int p,int l,int r){
		val[p]=tag[p]=b[p]=0;
		if(l==r){ b[p]=c[l]; return ; }
		build(ls,l,mid); build(rs,mid+1,r);
		pushup(p); 
	}
	void modify(int p,int l,int r,int ql,int qr,int v){
		if(ql<=l&&r<=qr){ upd(p,v); return ; }
		pushdown(p);
		if(ql<=mid) modify(ls,l,mid,ql,qr,v);
		if(qr>mid) modify(rs,mid+1,r,ql,qr,v);
		pushup(p); 
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return val[p];
		pushdown(p);
		if(qr<=mid) return query(ls,l,mid,ql,qr);
		else if(ql>mid) return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}seg;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];
	cin>>Q;
	for(int i=1;i<=Q;i++){
		int l,r; cin>>l>>r;
		q[l].pb(r,i);
	}
	for(int i=1;i<=n;i++){
		while(top&&c[st[top]]<c[i]) top--;
		if(top) ad[st[top]].pb(i); st[++top]=i; 
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&c[st[top]]<c[i]) top--;
		if(top) ad[i].pb(st[top]); st[++top]=i;
	}
	seg.build(1,1,n);
	for(int i=n;i>=1;i--){
		for(auto j:ad[i])
			if(2*j-i<=n) seg.modify(1,1,n,2*j-i,n,c[i]+c[j]);
		for(auto z:q[i]) ans[z.se]=seg.query(1,1,n,i,z.fi); 
	}
	for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

容易发现对于一组 $(a,b,c)$，若存在 $a<d<b$ 且 $\min(A_a,A_b)\leq A_d$ 则把小的那个换成 $d$ 一定不劣，所以只需要考虑不存在 $d$ 的 $(a,b)$，这样的 $(a,b)$ 只有 $O(N)$ 组，直接单调栈求出来就行了。

把询问离线挂左端点，那么对于一组 $(a,b)$ 可以贡献到的区间是 $[2b-a,n]$，线段树维护对于一个 $c$ 最大的 $A_a+A_b$，和区间最大的 $A$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[500010],R[500010],st[500010],top,ans[500010],qr[500010];vector<int>M[500010],Q[500010];struct seg{int l,r,A,mx,tag;}t[2000010];
#define lson now<<1
#define rson now<<1|1
void build(int now,int l,int r){
	t[now]={l,r};if(l==r){t[now].mx=t[now].A=a[l];return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);t[now].mx=max(t[lson].mx,t[rson].mx);t[now].A=max(t[lson].A,t[rson].A); 
} 
void puttag(int now,int v){t[now].mx=max(t[now].mx,v+t[now].A);t[now].tag=max(t[now].tag,v);}
void pushdown(int now){if(!t[now].tag) return ;puttag(lson,t[now].tag);puttag(rson,t[now].tag);t[now].tag=0;}
void modify(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){puttag(now,v);return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) modify(lson,l,r,v);if(mid<r) modify(rson,l,r,v);t[now].mx=max(t[lson].mx,t[rson].mx); 
}
int query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].mx;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1,res=0;if(l<=mid) res=max(res,query(lson,l,r));if(mid<r) res=max(res,query(rson,l,r));return res;
}
signed main(){
	n=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i]) M[st[top]].push_back(i),top--;
		if(top) M[st[top]].push_back(i);st[++top]=i;	
	}m=read();for(int i=1;i<=m;i++){int l=read();qr[i]=read();Q[l].push_back(i);}
	build(1,1,n);for(int i=n;i;i--){
		for(auto j:M[i]) if((j<<1)-i<=n) modify(1,(j<<1)-i,n,a[i]+a[j]);
		for(auto j:Q[i]) ans[j]=max(ans[j],query(1,i,qr[j]));
	}for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

