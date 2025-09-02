# Intervals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_w

長さ $ N $ の `0` と `1` からなる文字列を考えます。 この文字列のスコアを次のように計算します。

- 各 $ i $ ($ 1\ \leq\ i\ \leq\ M $) について、$ l_i $ 文字目から $ r_i $ 文字目までに `1` がひとつ以上含まれるならば、スコアに $ a_i $ を加算する。

文字列のスコアの最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 2\ ×\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ ×\ 10^5 $
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ N $
- $ |a_i|\ \leq\ 10^9 $

### Sample Explanation 1

`10001` のスコアは $ a_1\ +\ a_3\ =\ 10\ +\ 10\ =\ 20 $ となります。

### Sample Explanation 2

`100` のスコアは $ a_1\ +\ a_2\ =\ 100\ +\ (-10)\ =\ 90 $ となります。

### Sample Explanation 3

`0` のスコアは $ 0 $ となります。

### Sample Explanation 4

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 5

例えば、`101000` のスコアは $ a_2\ +\ a_3\ +\ a_4\ +\ a_5\ +\ a_7\ =\ 10\ +\ (-8)\ +\ 5\ +\ 9\ +\ (-6)\ =\ 10 $ となります。

## 样例 #1

### 输入

```
5 3
1 3 10
2 4 -10
3 5 10```

### 输出

```
20```

## 样例 #2

### 输入

```
3 4
1 3 100
1 1 -10
2 2 -20
3 3 -30```

### 输出

```
90```

## 样例 #3

### 输入

```
1 1
1 1 -10```

### 输出

```
0```

## 样例 #4

### 输入

```
1 5
1 1 1000000000
1 1 1000000000
1 1 1000000000
1 1 1000000000
1 1 1000000000```

### 输出

```
5000000000```

## 样例 #5

### 输入

```
6 8
5 5 3
1 1 10
1 6 -8
3 6 5
3 4 9
5 5 -2
1 3 -6
4 6 -7```

### 输出

```
10```

# 题解

## 作者：chlchl (赞：30)

看到题解里多多少少都有错误，我来补一篇，顺便纪念 700AC。

## 题意简述
给定 $m$ 个形如 $l_i,r_i,v_i$ 的命令，若一个长度为 $n$ 的 01 串中，第 $l_i\sim r_i$ 个位置至少有一个 $1$，则分数可以增加 $v_i$。问所有 01 串中的最大分数。

$1\leq n,m\leq 2\times 10^5,1\le a_i\leq 10^9$。

## 做法
对于这种区间的命令，一种常见的做法是化区间为点。具体来说，就是按照右端点排序，当访问到某个区间的右边界时才计算其贡献。

显然，分数的计算只跟 $1$ 的位置有关系，所以状态肯定是 $f_{i,j}$ 表示前 $i$ 个位置最后一个 $1$ 在 $j$ 位置的最大分数。

转移时，一开始我想着先枚举倒数第二个出现 $1$ 的位置 $k$，$f_{i,j}=f_{j-1,k}+\sum_{k<l_x\leq i,r_x=j}v_x$。但这样不仅正确性不保证，即使加上主席树优化，快速算出后面的 $\sum$，时间也去到 $O(n^3\log m)$，肯定过不了。

考虑换一种转移。刚刚枚举倒数第二个 $1$ 出现的位置是不必要的。因为我们的 $j\leq i$，所以前 $i-1$ 个位置的最后一个 $1$ 肯定也是 $j$（$j=i$ 时再另说）。

而 $f_{i,j}$ 比 $f_{i-1,j}$ 多的就是右端点在 $i$，左端点包含 $j$ 位置的所有命令的分数。

所以我们得到 $f_{i,j}=f_{i-1,j}+\sum_{l_k\leq j,r_k=i}v_k,j<i$。

当 $j=i$ 时，前 $i-1$ 个位置的最后一个 $1$ 可以是任意位置，所以在 $1\sim i-1$ 中取最大值，即 $f_{i,i}=\max_{j=1}^{i-1}f_{i-1,j}$。

当然，为了防止分数全负，我们还要对 $0$ 取个 $\max$。

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$，肯定过不了。

空间优化比较爽，转移只与上一维有关，直接省去 $i$ 维即可。

时间就比较麻烦了。因为这个转移很难优化其中的 $\sum$ 部分。

所以换种角度思考。注意到方程中的 $l_k\leq j$，证明有很多 $f$ 值的更新都用到了同一个命令。我们能不能枚举结尾（即 $i$），对于每个命令，一次多个 $f$ 值来减少复杂度呢？

答案是肯定的。一个命令影响的的是一个连续的区间。我们把 $f$ 数组扔到线段树上，就可以通过命令的区间更新来快速处理了。

线段树的每个单点就表示 $f$ 数组的值，一段区间就表示 $f$ 数组一段区间的最大值。

对于符合 $r_j=i$ 的所有命令，每次将 $[l_j,r_j]$ 这个区间 $+v_j$，相当于将所有 $f_k(l_j\leq k)$ 全部加上当前命令的分数。

查询时直接输出 $1\sim n$ 的最大值即可。

注意，$f_{i,i}$ 的更新是在 $1\sim i-1$ 中取最大值，所以我们要额外做一次单点更新，每一次将 $i$ 这个位置加上 $\max_{j=1}^{i-1}\{f_j\}$。而因为 $i$ 后面的值还没更新，所以直接调用 $val_1$ 就是 $1\sim i-1$ 最大值。

总时间复杂度 $O(n\log n)$，空间复杂度 $O(4n)$，可以 AC。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int n, m;
struct order{
	int l, r;
	ll v;
	bool operator < (const order &p) const {
		return r < p.r;
	}
} a[N];
ll val[N << 2], tag[N << 2];

#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void pushdown(int o){
	val[ls(o)] += tag[o];
	val[rs(o)] += tag[o];
	tag[ls(o)] += tag[o];
	tag[rs(o)] += tag[o];
	tag[o] = 0;
}

void update(int o, int l, int r, int s, int t, ll x){
	if(l >= s && r <= t){
		val[o] += x;
		tag[o] += x;
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if(s <= mid)
		update(ls(o), l, mid, s, t, x);
	if(t > mid)
		update(rs(o), mid + 1, r, s, t, x);
	val[o] = max(val[ls(o)], val[rs(o)]);
}//一课只有更新的线段树

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%lld", &a[i].l, &a[i].r, &a[i].v);
	sort(a + 1, a + 1 + m);//排序，注意不是 n 条命令
	for(int i=1,j=1;i<=n;i++){
		update(1, 1, n, i, i, max(0ll, val[1]));//更新 i 位置
		while(a[j].r == i && j <= m)
            update(1, 1, n, a[j].l, a[j].r, a[j].v), j++;//更新线段
        //运用双指针思想，均摊 O(1)
	}
	printf("%lld\n", max(0ll, val[1]));//与 0 取 max
	return 0;
}
```


---

## 作者：SoyTony (赞：23)

据说是套路题。套路在于在右端点处计算贡献，这样不重不漏。

设 $dp_{i,j}$ 为前 $i$ 个位置中，上一个 $1$ 放置在 $j$ 处的最大答案。
首先有：
$$dp_{i,i}=\max_{j=1}^{i-1}\{dp_{i-1,j}\}$$
同时存在 $i$ 是第一个为 $1$ 的位置，所以要和 $0$ 取 $\max$，排除负贡献的情况。

接下来考虑普通的转移，枚举到右端点 $i$ 时，对于所有的 $k,r_k=i$，若 $l_k\ge j$，就会产生贡献。于是转移方程：
$$dp_{i,j}=dp_{i-1,j}+\sum_{l_k\ge j,r_k=i} a_k$$
当然对于 $dp_{i,i}$，转移应当是从其本身得来的。

复杂度是 $O(n^2)$ 的。

发现后面的部分每条规则只被计算一次，算上区间加应当和枚举状态同级，考虑如何把枚举状态以及区间修改优化。

可以使用线段树，这样便可以对于每一个 $k$，批量修改所有产生贡献的 $dp_{i,j}$。

```cpp
int n,m;
struct node{
    int l,r;
    ll w;
    node()=default;
    node(int l_,int r_,ll w_):l(l_),r(r_),w(w_){}
}a[maxn];
vector<node> gr[maxn];
struct SegmentTree{
    #define mid ((l+r)>>1)
    #define lson rt<<1,l,mid
    #define rson rt<<1|1,mid+1,r
    ll mx[maxn<<2],tag[maxn<<2];
    void build(int rt,int l,int r){
        mx[rt]=0,tag[rt]=0;
        if(l==r) return;
        build(lson),build(rson);
    } 
    void push_down(int rt){
        if(tag[rt]){
            tag[rt<<1]+=tag[rt],tag[rt<<1|1]+=tag[rt];
            mx[rt<<1]+=tag[rt],mx[rt<<1|1]+=tag[rt];
            tag[rt]=0;
        }
    }
    void update(int rt,int l,int r,int pl,int pr,ll k){
        if(pl<=l&&r<=pr){
            mx[rt]+=k,tag[rt]+=k;
            return;
        }
        push_down(rt);
        if(pl<=mid) update(lson,pl,pr,k);
        if(pr>mid) update(rson,pl,pr,k);
        mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
    }
    #undef mid
    #undef lson
    #undef rson
}S;
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int l=read(),r=read(),w=read();
        a[i]=node(l,r,w);
        gr[r].push_back(a[i]);
    }
    S.build(1,1,n);
    for(int r=1;r<=n;++r){
        S.update(1,1,n,r,r,max(S.mx[1],0ll));
        for(int j=0;j<gr[r].size();++j){
            int l=gr[r][j].l;
            ll w=gr[r][j].w;
            S.update(1,1,n,l,r,w);
        }
    }
    printf("%lld\n",max(S.mx[1],0ll));
    return 0;
}
```

---

## 作者：CDFLS_mao_zx (赞：14)

## AT4544

### 题意:

给定 $m$ 个形如 $(l,r,a)$ 的条件，你需要确定一个 $01$ 串 $s$，对于任意一个条件，如果 $s[l,r]$ 中有一个  $1$ ，那么分数加 $a$ ，求最大分数。

$n,m\leq 2 * 10^5,|a|\leq 10^9$

### 思路：

考虑到条件是序列，不易统计贡献，我们先对条件按 $r$ 排序，约定在考虑到 $r$ 时统计这个东西的贡献。

**这是个常见的套路**

于是 $\text{DP}$ 的状态和转移都不难想到：

因为每次统计贡献，关心的仅仅是**最近的 $0$ **的位置。

$dp[i][j]$ 表示考虑到第 $i$ 个位置，上一个 $0$ 在 $j$ 处的最大分数。

$dp[i][i]=\min\limits_{j<i}(dp[i-1][j])$

$dp[i][j]=dp[i][j]+\sum\limits_{r[x]=i,l[x]\leq j}^{}a[x]$

先做上面的那个转移。

显然这样是 $O(n^2)$ 的，认真分析一下发现下面的式子是 $O(n^2)$ 的而不是 $O(n^3)$ 的。

过不了。

状态还可以滚动一下，空间 $O(n)$ ，然后发现好像已经没有办法继续优化状态了，于是考虑优化转移。

先考虑第二个转移，发现它就是一个区间加，第一个转移就是区间查最小值和单点修改，果断线段树。转移 $O(log_2n)$。

收工！

### 具体实现和参考代码：

怎么线段树呢？

对 $\text{DP}$ 值区间加，把 $dp$ 数组扔到线段树上啊，然后直接像模板一样维护就行了，再具体的看代码吧。

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define earse erase
#define LNF 1000000000000000000ll
#define int long long
//不开 long long 见祖宗
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
const int N=2e5+10;
int i,j,k,n,s,t,m;
struct Segment_Tree{
	int a[N<<2],lazy[N<<2];
	Segment_Tree()
	{
		for(int i=0;i<N<<2;i++)
		a[i]=-LNF;
	}
	void push_up(int rt)
	{
		a[rt]=max(a[rt<<1],a[rt<<1|1]);
	}
	void push_down(int rt)
	{
		if(lazy[rt]==0)return;
		a[rt<<1]+=lazy[rt],a[rt<<1|1]+=lazy[rt];
		lazy[rt<<1]+=lazy[rt],lazy[rt<<1|1]+=lazy[rt];
		lazy[rt]=0;
	}
	void updata(int l,int r,int rt,int x,int y,int c,int op)
	{
		if(x<=l&&y>=r)
		{
			if(op==1)
			a[rt]+=c,lazy[rt]+=c;
			else
			a[rt]=c;
			return;
		}
		push_down(rt);
		int mid=(l+r)/2;
		if(x<=mid)
		updata(l,mid,rt<<1,x,y,c,op);
		if(y>mid)
		updata(mid+1,r,rt<<1|1,x,y,c,op);
		push_up(rt);
	}
}T;
struct line{
	int l,r,val;
	friend bool operator <(line aa,line bb)
	{
		return aa.r<bb.r;
	}
}a[N];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	read(n),read(m);
	for(i=1;i<=m;i++)
	read(a[i].l),read(a[i].r),read(a[i].val);

	sort(a+1,a+m+1);
	int now=1;
	for(i=1;i<=n;i++)
	{
		int val=max(T.a[1],0ll);
		T.updata(1,n,1,i,i,val,0);
		while(a[now].r==i)
		T.updata(1,n,1,a[now].l,i,a[now].val,1),now++;
	}
	int ans=0;
	ans=max(ans,T.a[1]);
	cout<<ans;
	return 0;
}
```

### 总结：

有一说一，这种直接把 $\text{DP}$ 值扔在数据结构上的题比较少见，不过见过了就非常 $\text{Trival} $ 了，这道题的难点还是在于想到 $\text{DP}$ 的状态吧。

如果有疑问私信吧。。。

---

## 作者：_Vix_ (赞：12)

[原题链接](https://www.luogu.com.cn/problem/AT_dp_w)

---

第一次写线段树优化 DP，来记录一下套路。

## 分析

首先看到区间，根据经典套路，我们记录下来所有的右端点，每次在右端点处更新答案，这样可以做到不重不漏。

然后是 DP 的状态设计。可以想到用 $f_{i,j}$ 表示考虑完前 $i$ 个位置并且上一个 $1$ 在位置 $j$ 的最大答案。我们可以根据 $j$ 的位置进行转移：

如果在当前 $i$ 放一个 $1$，就一定有：

$$f_{i,i} = \max_{1 \le j < i} f_{i-1,j}+ \sum_{k,l_k \le i,r_k=i}val_k$$

若当前位置不放 $(1 \le j < i)$：

$$f_{i,j}= f_{i-1,j} + \sum_{k,\ l_k \le j, \ r_k=i} val_k$$

最后都要记得加上在 $i$ 结束的区间带来的贡献

朴素做时间复杂度是 $O(n^2)$，空间可以滚一下到 $O(n)$。

## 优化

怎么优化呢？我们分析一下 DP 在做什么事情。

每到一个新位置 $i$：

对于 $j = i$，我们找到了 $j$ 位置之前的最小值。

对于 $1 \le j \le i$，随着 $j$ 的遍历，我们将所有右端点在 $i$ 的区间的 $val$ 累加到这段区间的 DP 值里面。

发现什么没有？对，这就是一颗线段树可以解决的问题。将 DP 值扔到线段树上维护，可以 $O(n \log n)$ 解决这个问题。

## 注意
 1. 每次找的最大值应该与 $0$ 取 $\max$。
 2. 注意 long long
 
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 2e5 + 10;

struct seg {
	int L[N << 2], R[N << 2];
	ll mx[N << 2], add[N << 2];
	#define lson u << 1
	#define rson u << 1 | 1
	#define mid (L[u] + R[u] >> 1)
	void pushup(int u) {
		mx[u] = max(mx[lson], mx[rson]);
	}
	void apply(int u, ll v) {
		mx[u] += v;
		add[u] += v;
	}
	void pushdown(int u) {
		if (!add[u]) return;
		apply(lson, add[u]), apply(rson, add[u]);
		add[u] = 0;
	}
	void build(int u, int l, int r) {
		L[u] = l, R[u] = r;
		if (l == r) return;
		build(lson, l, mid);
		build(rson, mid + 1, r);
	}
	void modify(int u, int l, int r, ll v) {
		if (l <= L[u] && R[u] <= r) {
			apply(u, v);
			return;
		}
		pushdown(u);
		if (l <= mid) modify(lson, l, r, v);
		if (r > mid) modify(rson, l, r, v);
		pushup(u);
	}
	ll query() {
		return max(0ll, mx[1]);
	}
} T;
int n, m, l, r, v;
vector<PII> vec[N];

int main() {
	scanf("%d%d", &n, &m);
	T.build(1, 1, n);
	while (m--) {
		scanf("%d%d%d", &l, &r, &v);
		vec[r].push_back({l, v});
	}
	for (int i = 1; i <= n; i++) {
		T.modify(1, i, i, T.query());
		for (auto t : vec[i]) T.modify(1, t.fi, i, t.se);
	}
	printf("%lld", T.query());
	return 0;
}
```


---

## 作者：Pengzt (赞：11)

**[cnblogs](https://www.cnblogs.com/Pengzt/p/17845406.html)**

**[洛谷](https://www.luogu.com.cn/problem/AT_dp_w) [AT](https://atcoder.jp/contests/dp/tasks/dp_w)**

先不看数据范围，考虑 dp。

令 $f_i$ 表示前 $i$ 个字符且强制第 $i$ 个字符为 $1$ 的最大分数。

则 $f_i = \max(f_{j - 1} +\sum\limits_{r_k\ge i\ge l_k\ge j}a_k)$。

这个是一份 $\mathcal{O}(n^2m)$ 暴力 dp 的代码片段：
```cpp
ll ans = 0;
for(int i = 1; i <= n; ++i) {
	f[i] = -inf;
	for(int j = 1; j <= i; ++j) {
		ll val = 0;
		for(int k = 1; k <= m; ++k) if(a[k] >= j && a[k] <= i && b[k] >= i) val += c[k];
		f[i] = max(f[i], f[j - 1] + val);
	}
	ans = max(ans, f[i]);
}
```

考虑怎么去优化这个 dp。

发现这个 dp 式子每个位置 $j$ 的贡献都是有一个 $f_{j - 1}$ 的，然后后面带有 $\sum$ 的式子在每次 $i$ 变化后的变动次数是很小的，总次数就是区间总数 $m$。考虑将 $f+\sum$ 插入线段树中，则每次只需要区间加和全局取 $\max$，最后就只需要查询根节点的值了。

具体地，将所有区间按右端点排序，然后用一个指针在上面扫，每次对 $r_j = i$ 的区间进行更新即可。时间复杂度 $\mathcal{O}((n + m)\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define eb emplace_back
#define pii pair<int, ll>
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
bool Mbe;
mt19937_64 rng(35);
constexpr int N = 2e5 + 10;
constexpr ll inf = 1e18;
struct node {
	int l, r, v;
};
int n, m;
ll f[N];
node a[N];
struct segt {
	ll val[N << 2], laz[N << 2];
	void tag(int u, ll v) {
		laz[u] += v;
		val[u] += v;
	}
	void down(int u) {
		if(laz[u]) {
			tag(u << 1, laz[u]);
			tag(u << 1 | 1, laz[u]);
			laz[u] = 0;
		}
	}
	void modify(int u, int L, int R, int l, int r, ll v) {
		if(l <= L && R <= r) return tag(u, v);
		down(u);
		int m = (L + R) >> 1;
		if(l <= m) modify(u << 1, L, m, l, r, v);
		if(r > m) modify(u << 1 | 1, m + 1, R, l, r, v);
		val[u] = max(val[u << 1], val[u << 1 | 1]);
	}
} t;
bool Med;
int main() {
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) cin >> a[i].l >> a[i].r >> a[i].v;
	sort(a + 1, a + m + 1, [](node a, node b){
		return a.r < b.r;
	});
	for(int i = 1, j = 1; i <= n; ++i) {
		t.modify(1, 1, n, i, i, max(t.val[1], 0ll));
		for(; j <= m && a[j].r == i; ++j)
			t.modify(1, 1, n, a[j].l, a[j].r, a[j].v);
	}
	cout << max(0ll, t.val[1]) << "\n";
	cerr << TIME << "ms\n";
	return 0;
}
```

---

## 作者：MortisM (赞：4)

题目大意：你要构造一个长度为 $n$ 的 `01` 串，它的价值由 $m$ 条规则组成，每条规则如下：
+ 若在区间 $[l_i,r_i]$ 中有 `1`，则会获得 $a_i$ 的价值（注意：$a_i$ 可能为负数）。

求可能的最大价值。

数据范围：$n\leq 10^5$。

按 $r_i$ 排序，对于每个 $r_i$ 分别计算到 $l_i$ 的贡献。

这道题的思路是 **先设计出 $O(N^2)$ 的状态再优化**，优化就比较套路了。

具体来说，可以设 $f(i,j)$ 表示到第 $i$ 个字符并且上一个选的字符是 $j$（$j=i$ 表示选了第 $i$ 个字符）的最大价值。

转移如下：

$$
\begin{cases}
f(i,i)=\max_{j<i}f(i-1,j)\\
f(i,j)=f(i-1,j)+\sum_{r_k=i,l_k\leq j}a_k
\end{cases}
$$

这个东西用线段树搞一下就行了。

**[代码](https://atcoder.jp/contests/dp/submissions/33892793)**

---

## 作者：OtterZ (赞：4)

这道题那叫非常的简单呀！  
管你会不会，看就完了。
# 题意
给定 $M$ 个区间 $[l_i,r_i]$，对于 $1 \le i \le M,[l_i,r_i] \subset [1,N]$，你可以构造一个集合 $A \subset [1,N]$，若 $A \cap [l_i,r_i] \neq \emptyset$，你将有 $a_i$ 的分数，问分值最大为多少？
# 你要是懂动规的
我们可以发现，当 $dp_i$ 为集合 $A$ 中最大的元素个数时的最大分值时，答案显然是 $\max{dp_i}$，且有一个显然的推导方式，对于次大值 $j$，加入 $i$ 后会额外相交的区间不含 $j$，且含 $i$，因为区间有连续性，故而有相应条件 $j < l_k \le i$ 且 $r_k \ge i$，即 $dp_i = \max{dp_j + \sum _{j < l_k \le i\land r_k \ge i}a_k}$。

# 如何优化
我们如果直接转移，会得到 $\operatorname{O}(n^2m)$ 的算法，显然会 `T`，但是我们可以发现如下性质：

1. 我们要求的 $dp_i$ 是 $dp_j, j \in [1,i - 1]$ 转移而来的最优解，求的是区间上的最大值。
2. $l_i$ 更小的区间更早出现在转移公式内，$r_i$ 更小的区间更早不被转移公式计算到。
3. 区间 $[l_k,r_k]$ 只会影响 $[1,l_k - 1]$ 到 $i$ 的转移，且使之加上 $a_i$。

故而我们可以得到如下结论:

1. 我们可以用**线段树**维护 $dp_j$ 转移到 $dp_i$ 的值，通过区间查询得到 $dp_i$。
2. 对于区间，我们可以用**双指针的**方式维护要加入或删除的区间。

这么做可以将代码优化至 $\operatorname{O}(n\log n + m \log n)$ 的复杂度，这样就可以稳稳地过了。

# 注意事项
1. 线段树的值、懒惰标记，动规转移数组需要开 `long long`，$a_i$ 理论上可以不开，但实际上会因此 `WA`。
2. 区间加入、删除分别处理，易证一个区间不会因此先被删除后被加入。
3. 你需要考虑集合被加入 $i$ 之前为空的情况，实现时可以放在 $0$ 号位置，无需特判。
4. 线段树中和转移中值可以为负数，但保证答案是非负数。

# 代码

```
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
struct line{
	int l,r;
	long long a;
}l1[200005],l2[200005];//分别维护加入区间和删掉区间的先后顺序
int o1 = 1,o2 = 1;
bool cmp1(line x,line y){//易于知道且确定的加入区间的先后顺序
	return x.l < y.l;
}
bool cmp2(line x,line y){//易于知道且确定的删除区间的先后顺序
	return x.r < y.r;
}

long long tr[(1 << 21)],tg[(1 << 21)];//线段树维护区间加和，区间最大值 
void add(int k,int l,int r,int lq,int rq,long long ad){
	if(l > rq || r < lq)
		return;
	if(l >= lq && r <= rq){
		tg[k] += ad;
		tr[k] += ad; 
		return; 
	}
	tr[(k << 1)] += tg[k];
	tg[(k << 1)] += tg[k];
	tr[(k << 1) | 1] += tg[k];
	tg[(k << 1) | 1] += tg[k];
	tg[k] = 0;
	int m = (l + r) >> 1;
	add((k << 1),l,m,lq,rq,ad);
	add((k << 1) | 1,m + 1,r,lq,rq,ad);
	tr[k] = max(tr[(k << 1)],tr[(k << 1) | 1]);
}
long long query(int k,int l,int r,int lq,int rq){
	if(l > rq || r < lq)
		return -9000000000000000000ll;//维护的值可以为负数，不应忽略。
	if(l >= lq && r <= rq){
		return tr[k]; 
	}
	tr[(k << 1)] += tg[k];
	tg[(k << 1)] += tg[k];
	tr[(k << 1) | 1] += tg[k];
	tg[(k << 1) | 1] += tg[k];
	tg[k] = 0;
	int m = (l + r) >> 1;
	long long ret = max(query((k << 1),l,m,lq,rq),query((k << 1) | 1,m + 1,r,lq,rq));
	tr[k] = max(tr[(k << 1)],tr[(k << 1) | 1]);
	return ret;
}

long long dp[200009],ans;//答案最小为0，是全局变量统一的初值
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= m; i ++){
		scanf("%d %d %lld",&l1[i].l,&l1[i].r,&l1[i].a);
		l2[i].l = l1[i].l,l2[i].r = l1[i].r,l2[i].a = l1[i].a;
		//printf("%d %d %d\n %d %d %d\n",l1[i].l,l1[i].r,l1[i].a,l2[i].l,l2[i].r,l2[i].a);
	}
	sort(l1 + 1,l1 + m + 1,cmp1);
	sort(l2 + 1,l2 + m + 1,cmp2);
    
	for(int i = 1; i <= n; i ++){
    	//双指针维护要加入或去掉的区间。
		while(o1 <= m && l1[o1].l <= i){//加入区间。
			//printf("%d %d %d\n",l1[i].l,l1[i].r,l1[i].a);
			add(1,0,n,0,l1[o1].l - 1,l1[o1].a);
			o1++;
		}
		while(o2 <= m && l2[o2].r < i){//去掉区间。
			//printf("%d %d %d\n",l2[i].l,l2[i].r,l2[i].a);
			add(1,0,n,0,l2[o2].l - 1,-l2[o2].a);
			o2++;
		}
		dp[i] = query(1,0,n,0,i - 1);//转移，公式如上，对应值用线段树维护。
		ans = max(ans,dp[i]);
		add(1,0,n,i,i,dp[i]);
		//printf("%lld\n",dp[i]);
	}
    
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：AlicX (赞：2)

## Solution 

发现此题用数据结构或贪心直接做做不了，考虑 dp。  

先考虑一个方法让其不算重，不难想到是将每段区间用 `vector` 存右端点，届时一起更新。  

然后定义 $f_{i,j}$ 表示当前在第 $i$ 个点，最近的 $1$ 在 $j$ 位置时的最大分数。不难推出状态转移：$f_{i,j}=\max_{k=1}^{j}f_{i-1,k}+\sum_{l_p\ge k,r_p=i}a_p$。 

考虑如下优化：$f_{i,j}$ 一定通过 $f_{i-1,j}$ 转移而来，因为要保证 $i$ 答案最优，所以 $1$ 的位置应该尽量靠后，然后就需要单独考虑 $i=j$ 的情况。于是状态转移变为：  

1. $f_{i,i}=\max_{j=0}^{j=i-1} f_{i-1,j}$。
2. $f_{i,j}=f_{i-1,j}+\sum_{l_p\ge k,r_p=i}a_p$。

发现对于每一个 $p$，其影响的区间为 $l_p\sim r_p$，是连续的，于是考虑用线段树维护。时间复杂度为 $O(m\log n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10; 
int n,m; 
vector<pii> q[N]; 
struct Node{
	int l,r; 
	ll w,add; 
}tr[N<<2]; 
void pushup(int u){
	tr[u].w=max(tr[u<<1].w,tr[u<<1|1].w); 
} 
void pushdown(int u){
	if(!tr[u].add) return ; 
	tr[u<<1].w+=tr[u].add,tr[u<<1|1].w+=tr[u].add; 
	tr[u<<1].add+=tr[u].add,tr[u<<1|1].add+=tr[u].add,tr[u].add=0; 
}
void build(int u,int l,int r){
	tr[u]={l,r}; 
	if(l==r) return ; 
	int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
} 
void modify(int u,int l,int r,ll w){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].w+=w,tr[u].add+=w; 
		return ; 
	} pushdown(u); int mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) modify(u<<1,l,r,w); 
	if(r>mid) modify(u<<1|1,l,r,w); 
	pushup(u); 
} 
signed main(){ 
	scanf("%d%d",&n,&m); 
	for(int i=1;i<=m;i++){ 
		int l,r,w; 
		scanf("%d%d%d",&l,&r,&w); 
		q[r].push_back({l,w}); 
	} build(1,1,n); 
	for(int i=1;i<=n;i++){ 
		modify(1,i,i,max(tr[1].w,0ll));  
		for(int j=0;j<q[i].size();j++) modify(1,q[i][j].x,i,q[i][j].y); 
	} printf("%lld\n",max(tr[1].w,0ll)); return 0; 
} 
```


---

## 作者：Meteor_ (赞：2)

# AT_dp_w Intervals 题解

## 题目大意

给定 $m$ 个形如 $l_i, r_i, a_i$ 的指令，当且仅当字符串 $[l_i, r_i]$ 中有至少一个 $1$ 时，该字符串的分数会加上 $a_i$。现在需要你构造一个 $01$ 字符串，使其分数最大。你只需要求出最大分数。

$1 \le n, m \le 2 \times 10^5, |a| \le 10^9$

## 题解

先考虑一下暴力怎么打。

设 $f_i$ 表示最后一个 $1$ 在位置 $i$ 的最大分数

转移比较平凡，枚举一个 $\displaystyle f_i = \max_{j = 1}^{i - 1} \{val_i + f_j - \Delta_{i, j}\}$，$val_i$ 包含位置 $i$ 的所有指令的分数和，$\Delta_{i, j}$ 表示同时包含 $i, j$ 两个位置的所有指令的分数和。

直接转移复杂度炸裂，考虑优化。

比较套路。化区间为点是好想的，所以考虑离线，按照左端点排序，开扫。假设现在扫到一个位置 $i$，我们要来计算 $f_i$。

考虑转移需要的那些东西怎么维护。

$val_i$ 比较好维护。维护一个 $sum$，表示包含当前的所有指令的分数和，那么如果 $i$ 是一个区间的左端点，那么就让 $sum$ 加上这个指令的 $a_i$，如果是右端点，就减去。$val_i$ 就是扫到 $i$ 时 $sum$ 的值。

然后就是考虑怎么维护 $f_j + \Delta_{i, j}$ 的最大值。

维护最值，不难想到线段树。

既然 $\Delta_{i, j}$ 是动态的，考虑每次怎么变化。如果当前点 $i$ 是区间 $k$ 的左端点，那么对于所有的 $j \in [l_k, r_k]$，$\Delta_{i, j}$ 都需要加上 $a_k$。如果当前点 $i$ 是区间 $k$ 的右端点，那么对于所有的 $j \in [l_k, r_k]$，$\Delta_{i, j}$ 都需要减去 $a_k$。

于是就变成了线段树，支持区间加和区间查询最大值。时间复杂度 $O(n \log n)$。

## 代码

```
#include <bits/stdc++.h>
#define int long long
#define P pair<int, int>
#define MP make_pair
using namespace std;

const int M = 200005;
int n, m, maxn[M << 2], lazy[M << 2], ans, f[M], pos = 1, sum;

struct Q {
    int l;
    int r;
    int a;
}q[M];

inline bool cmp(Q a, Q b) {
    if(a.l != b.l)
        return a.l < b.l;
    return a.r < b.r;
}

void push_down(int rt) {
    if(lazy[rt]) {
        int ls = rt << 1, rs = ls | 1;
        maxn[ls] += lazy[rt];
        maxn[rs] += lazy[rt];
        lazy[ls] += lazy[rt];
        lazy[rs] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    maxn[rt] = 0;
    if(l == r)
        return;
    int mid = (l + r) >> 1, ls = rt >> 1, rs = ls | 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    maxn[rt] = max(maxn[ls], maxn[rs]);
}

void add(int rt, int l, int r, int zuo, int you, int addend) {
    if(zuo <= l && r <= you) {
        maxn[rt] += addend;
        lazy[rt] += addend;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1;
    if(zuo <= mid)
        add(ls, l, mid, zuo, you, addend);
    if(you > mid)
        add(rs, mid + 1, r, zuo, you, addend);
    maxn[rt] = max(maxn[ls], maxn[rs]);
}

int ask(int rt, int l, int r, int zuo, int you) {
    if(you < zuo)
        return 0;
    if(zuo <= l && r <= you)
        return maxn[rt];
    push_down(rt);
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1, res = 0;
    if(zuo <= mid)
        res = ask(ls, l, mid, zuo, you);
    if(you > mid)
        res = max(res, ask(rs, mid + 1, r, zuo, you));
    maxn[rt] = max(maxn[ls], maxn[rs]);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++ i)
        cin >> q[i].l >> q[i].r >> q[i].a;
    stable_sort(q + 1, q + 1 + m, cmp);
    priority_queue<P, vector<P>, greater<P>> que;
    build(1, 1, n);
    for(int i = 1; i <= n; ++ i) {
        while(q[pos].l == i) {
            add(1, 1, n, q[pos].l, q[pos].r, -q[pos].a);
            sum += q[pos].a;
            que.push(MP(q[pos].r, pos));
            ++ pos;
        }
        f[i] = sum + max(ask(1, 1, n, 1, i - 1), 0ll);
        add(1, 1, n, i, i, f[i]);
        while(!que.empty() && que.top().first == i) {
            int id = que.top().second;
            sum -= q[id].a;
            add(1, 1, n, q[id].l, q[id].r, q[id].a);
            que.pop();
        }
        ans = max(ans, f[i]);
    }
    cout << ans;
}
```

---

## 作者：rlc202204 (赞：2)

这道题我们可以用 dp 来做，并且只用一维来表示。

设 $dp_i$ 表示前 $i$ 个字符，第 $i$ 个字符为 $1$ 时，可能获得的最大价值。

考虑转移，朴素的转移是 $O(n^2)$ 的，思路是枚举上一个 $1$ 的位置，同时对于每一个区间的贡献，只计算最开始的那个 $1$，状态转移方程如下：

$$
dp_i = \displaystyle\max_{0 \le j < i}{\{dp_j + \sum_{k \in S_{i,j}}a_k\}}
$$

其中 $S_{i,j}$ 是一个集合，表示所有满足 $j < l_k \le i \le r_k$ 的 $k$。

这样就避免了重复计算每个区间的贡献。

但复杂度是 $O(n^2)$ 的，考虑优化。

对于一个区间 $[l_k, r_k]$，若 $k \in S_{i,j}$，则有 $i \in [l_k, r_k]$，$j \in [0,l_k-1]$。

所以我们可以用类似扫描线的思想来做这道题。我们先处理完 $dp_0 \sim dp_{l_k-1}$，此时 $[l_k,r_k]$ 还没有任何贡献。然后在处理 $dp_{l_k} \sim dp_{r_k}$ 时，给所有的 $0 \sim l_k-1$ 上的数加上 $a_i$，相当于把贡献记录下来。然后当我们处理到 $dp_{r_k}$ 的时候，再把 $0 \sim l_k-1$ 减去 $a_i$ 即可。

这样相当于我们动态维护了 $S_{i,j}$ 这个集合，从单个区间的角度去思考。

区间加区间最小值可以用线段树维护，所以最终复杂度 $O(m \log n)$。

**代码：**

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
struct SegTree {//线段树
	int sz;
	vector<long long> val;
	vector<long long> tag;
	#define ls (x << 1)
	#define rs (x << 1 | 1)
	#define mid ((lx + rx) >> 1)
	void pushup(int x) {
		val[x] = max(val[ls], val[rs]);
	}
	void pushdown(int x) {
		if (tag[x] == 0)
			return;
		val[ls] += tag[x], val[rs] += tag[x];
		tag[ls] += tag[x], tag[rs] += tag[x];
		tag[x] = 0;
	}
	void upd(int x, int lx, int rx, int l, int r, long long v) {//区间加
		if (rx <= l || r <= lx)
			return;
		if (l <= lx && rx <= r) {
			val[x] += v;
			tag[x] += v;
			return;
		}
		pushdown(x);
		upd(ls, lx, mid, l, r, v), upd(rs, mid, rx, l, r, v);
		pushup(x);
	}
	long long qry(int x, int lx, int rx, int l, int r) {//区间最小值
		if (rx <= l || r <= lx)
			return -9e18;//注意此处不能为 0，因为状态定义是第 i 位必须为 1
		if (l <= lx && rx <= r)
			return val[x];
		pushdown(x);
		return max(qry(ls, lx, mid, l, r), qry(rs, mid, rx, l, r)); 
	}
	SegTree () {}
	SegTree (int n) {
		sz = 1;
		while (sz < n)
			sz *= 2;
		val.assign(sz * 2, 0ll);
		tag.assign(sz * 2, 0ll);
	}
	#undef ls
	#undef rs
	#undef mid
} st; 
const int MAXN = 2e5 + 5;
int n, m;
struct Node {
	int l, r;
	long long a;
	Node (int L = 0, int R = 0, long long A = 0) :
		l(L), r(R), a(A) {}
};
vector<Node> tmp[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	st = SegTree(n + 1);
	for (int i = 1; i <= m; i++) {
		int l, r;
		long long a;
		scanf("%d%d%lld", &l, &r, &a);
		l++, r++;//由于要考虑第 0 个，所以给所有下标 + 1
		tmp[l].push_back(Node(1, l - 1, a));
		if (r + 1 <= n + 1)
			tmp[r + 1].push_back(Node(1, l - 1, -1ll * a));
	}
	long long ans = 0;
	for (int i = 2; i <= n + 1; i++) {
		for (auto j: tmp[i])
			st.upd(1, 1, st.sz + 1, j.l, j.r + 1, j.a);
		long long sum = st.qry(1, 1, st.sz + 1, 1, i);
 		ans = max(ans, sum);
		st.upd(1, 1, st.sz + 1, i, i + 1, sum);
	}
	printf("%lld\n", ans);
	return 0; 
} 
```



---

## 作者：zerc (赞：1)

一个非常套路的做法是在右端点处计算贡献，以做到不重不漏。

设 $f_{i, j}$ 表示到第 $i$ 个字符，上一个选 $1$ 的位置是 $j$ 的最大价值，易得：

$$
f_{i, j} =
\begin{cases}
 \max_{k < i}\{f_{i - 1, k}\} &j = i\\
 f_{i - 1, j} + \sum_{r_k = i, l_k \le j} a_k & j < i
\end{cases}
$$

再压掉一维，空间 $O(n)$，时间 $O(n ^ 2)$。

考虑优化转移：

- 对于 $j = i$，区间取 max；

- 对于 $\sum a_k$，相当于对 $l_k \sim r_k$ 区间加 $w_k$；

用线段树维护即可，时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

const int maxn = 2e5+5;

struct rules {
    int l, r, w;
    
    bool friend operator < (rules a, rules b) {
        return a.r < b.r;
    }
} rl[maxn];

struct tre {
    tre *ls, *rs;
    int l, r; llt val, tag;
    
    tre(int tl, int tr) {
        ls = rs = nullptr;
        l = tl, r = tr;
        val = tag = 0;
    }
} *rt;

void push_up(tre *t) {
    t -> val = max(t -> ls -> val, t -> rs -> val);
}

void push_down(tre *t) {
    if (t -> l == t -> r) return;
    t -> ls -> val += t -> tag;
    t -> rs -> val += t -> tag;
    t -> ls -> tag += t -> tag;
    t -> rs -> tag += t -> tag;
    t -> tag = 0;
}

void build(int l, int r, tre *&t) {
    t = new tre(l, r);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l,  mid, t -> ls);
    build(mid+1,r, t -> rs);
}

void modity(int l, int r, llt k, tre *t) {
    if (l <= t -> l && t -> r <= r) {
        t -> val += k;
        t -> tag += k;
        return;
    }
    push_down(t);
    if (l <= t -> ls -> r) modity(l, r, k, t -> ls);
    if (r >= t -> rs -> l) modity(l, r, k, t -> rs);
    push_up(t);
}

llt query() {
    return max(rt -> val, 0ll);
}

int main() {
    int n, m; cin >> n >> m, build(1, n, rt);
    for (int i = 1; i <= m; i++) {
        cin >> rl[i].l >> rl[i].r >> rl[i].w;
    }
    sort(rl + 1, rl + m + 1);
    for (int i = 1, k = 1; i <= n; i++) {
        modity(i, i, query(), rt);
        while (rl[k].r == i) {
            modity(rl[k].l, rl[k].r, rl[k].w, rt), k++;
        }
    }
    cout << query() << '\n';
}
```

注意 `long long`。

---

## 作者：WaterSun (赞：0)

# 思路

首先考虑较为普通的 DP。

定义 $dp_{i,j}$ 表示在前 $i$ 个位置中，最后一个 `1` 在 $j$ 的最大分数，显然有：

$$
dp_{i,j} = \left\{\begin{matrix}
\max_{k = 1}^{i - 1}\{dp_{i - 1,k}\} + \sum_{l_k \leq j \wedge r_k = i}{a_k} & (i = j)\\
dp_{i - 1,j} + \sum_{l_k \leq j \wedge r_k = i}{a_k} & (i \neq j)
\end{matrix}\right.
$$

发现这个状态是 $\Theta(n^2)$ 的，但是可以滚掉一维，空间复杂度 $\Theta(n)$，时间复杂度 $\Theta(n^2)$。

不难发现，对于每一个 $(l,r,a)$ 的三元组，会在 $i = r$ 时，在 $dp_{l \sim i}$ 中做出贡献，于是转变为了区间加。

然后对于第一个式子中的 $\max$ 也就是区间查询最值。于是用线段树维护 $dp$ 数组即可。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int n,m;
vector<pii> v[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Max,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].Max += k;
        tr[u].tag += k;
    }

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag);
            calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid);
        build(rs(u),mid + 1,r);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r){
            calc(u,k);
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    #undef ls
    #undef rs
}T;

signed main(){
    n = read();
    m = read();
    for (re int i = 1;i <= m;i++){
        int l,r,w;
        l = read();
        r = read();
        w = read();
        v[r].push_back({l,w});
    }
    T.build(1,1,n);
    for (re int i = 1;i <= n;i++){
        T.modify(1,i,i,max(0ll,T.tr[1].Max));
        for (auto p:v[i]) T.modify(1,p.fst,i,p.snd);
    }
    printf("%lld",max(0ll,T.tr[1].Max));
    return 0;
}
```

---

## 作者：TKXZ133 (赞：0)

[Intervals](https://www.luogu.com.cn/problem/AT_dp_w)

### 题目大意

给定 $m$ 条形如 $(l_i,r_i,a_i)$ 的规则，你需要求出一个长为 $n$ 的分数最大的 01 串的分数，其中一个 01 串 $A$ 的分数被定义为

$$\sum_{i=1}^ma_i[\sum_{j=l_i}^{r_i}A_j\ge 1]$$

### 思路分析

考虑 DP。

设 $f_{i,j}$ 表示考虑 01 串的前 $i$ 个数，最后一个 $1$ 放在 $j$ 时的最大分数，首先有一个特殊的转移：

$$f_{i,i}=\max_{j<i}(f_{i-1,j})$$

也就是枚举前 $i-1$ 个数中上一个 $1$ 放在哪个位置，对所有可能的情况取 $\max$。

考虑一般情况：

从 $i-1$ 转移到 $i$，新的贡献只从所有右端点为 $i$ 的区间产生，考虑到产生贡献的条件是至少包含一个 $1$，而最后的 $1$ 位于 $j$，故只有这个区间包含 $j$ 的时候才会产生贡献，故有状态转移方程：

$$f_{i,j}=f_{i-1,j}+\sum_{k=1}^m[l_k\le j][r_k=i]a_k$$

直接转移的时间复杂度是 $O(n^3)$ 的，不过可以通过将区间排序加双指针做到均摊 $O(n^2)$，但依然无法通过，考虑优化。

首先发现转移只与上一维有关，可以直接优化掉 $i$，使空间复杂度降为 $O(n)$。

考虑哪些区间对 $f$ 产生贡献，不难发现，只要区间包含 $f$ 的端点，它就对 $f$ 有贡献，那么我们就可以把 $f$ 丢到线段树上，对于每一个区间进行一次线段树上的区间加操作，维护区间的最大值即可。

注意 01 串全为 $0$ 时其分数为 $0$，故不可能产生负分数，所有的分数需要和 $0$ 取 $\max$。

### 代码

```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;
const int N=200200;
#define int long long
#define mid ((l+r)>>1)

int n,m,in1,in2,in3;

struct Node{
    int l,r,a;
}a[N];
vector<Node> v[N];

struct ST{
    int maxn[N<<2],tag[N<<2];
    void change_t(int p,int k){
        maxn[p]+=k;tag[p]+=k;
    }
    void push_down(int p){
        if(!tag[p]) return ;
        change_t(p<<1,tag[p]);
        change_t(p<<1|1,tag[p]);
        tag[p]=0;
    }
    void change(int p,int l,int r,int x,int y,int k){
        if(x<=l&&r<=y){change_t(p,k);return ;}
        push_down(p);
        if(x<=mid) change(p<<1,l,mid,x,y,k);
        if(y>mid) change(p<<1|1,mid+1,r,x,y,k);
        maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
    }
}tree;

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&in1,&in2,&in3);
        a[i]=Node{in1,in2,in3};
        v[in2].push_back(a[i]);
    }
    for(int i=1;i<=n;i++){
        tree.change(1,1,n,i,i,max(tree.maxn[1],0ll));
        for(auto it:v[i])
            tree.change(1,1,n,it.l,i,it.a);
    }
    cout<<max(tree.maxn[1],0ll)<<'\n';
    return 0;
}
```

---

