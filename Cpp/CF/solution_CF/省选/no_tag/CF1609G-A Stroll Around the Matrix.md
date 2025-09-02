# A Stroll Around the Matrix

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609G/ceef08d1b03037a22565155ac40e7e9a427625a1.png)William has two arrays of numbers $ a_1, a_2, \dots, a_n $ and $ b_1, b_2, \dots, b_m $ . The arrays satisfy the conditions of being convex. Formally an array $ c $ of length $ k $ is considered convex if $ c_i - c_{i - 1} < c_{i + 1} - c_i $ for all $ i $ from $ 2 $ to $ k - 1 $ and $ c_1 < c_2 $ .

Throughout William's life he observed $ q $ changes of two types happening to the arrays:

1. Add the arithmetic progression $ d, d \cdot 2, d \cdot 3, \dots, d \cdot k $ to the suffix of the array $ a $ of length $ k $ . The array after the change looks like this: $ [a_1, a_2, \dots, a_{n - k}, a_{n - k + 1} + d, a_{n - k + 2} + d \cdot 2, \dots, a_n + d \cdot k] $ .
2. The same operation, but for array $ b $ .

After each change a matrix $ d $ is created from arrays $ a $ and $ b $ , of size $ n \times m $ , where $ d_{i, j}=a_i + b_j $ . William wants to get from cell ( $ 1, 1 $ ) to cell ( $ n, m $ ) of this matrix. From cell ( $ x, y $ ) he can only move to cells ( $ x + 1, y $ ) and ( $ x, y + 1 $ ). The length of a path is calculated as the sum of numbers in cells visited by William, including the first and the last cells.

After each change William wants you to help find out the minimal length of the path he could take.

## 样例 #1

### 输入

```
5 3 4
1 2 4 7 11
5 7 10
1 3 2
2 2 5
1 5 4
2 1 7```

### 输出

```
98
128
219
229```

## 样例 #2

### 输入

```
5 6 7
4 9 22 118 226
7 94 238 395 565 738
2 1 95
1 4 54
1 2 5
1 2 87
2 6 62
2 1 143
1 1 77```

### 输出

```
3639
5122
5162
5617
7663
7806
7960```

# 题解

## 作者：Cry_For_theMoon (赞：6)

[传送门](https://codeforces.com/contest/1609/problem/G)

这周生病了，状态很差，所以有段时间没写题。今天写掉了这场比赛的 FG 两道 DS 清醒清醒。然后发现这两道都是 naive 题......

#### 分析：

看到就大概有个感觉，就是这是个二合一题。

发现告诉你了两个序列递增且差分递增，修改完后也满足。看上去，这东西对修改没帮助，那么只可能和查询有关。

事实上查询部分是很简单的（~~我初一的时候就出了这道题）~~：

结论：每次贪心地往两种走法里，数小的走，一定是最优解。

证明：

此时差分单调发挥用处了。上述结论的本质就是选差分小的那个数。那么反证一下就完事了。

这样你可以在 $O(n+m)$ 的时间内解决一个询问。

我们现在要做的是把这个策略转成一个式子，或者可以 DS 维护的东西。

已经提到了，这个策略的本质是每次选择差分小的走。把最终最优策略里，每次新选择的差分写出来，那么它是单调的。或者说，你会发现这个写出来的过程，就是在对差分排序。而第 $i$ 个位置的差分，会贡献 $(n+m-i-1)$ 次。

换言之如果把 $a$ 和 $b$ 的差分写出来，共有 $n+m-2$ 个，把这个数组记作 $d$ 并排序，则结果为

$$\sum _{i=1}^{n+m-2}(n-m-i-1)d_i$$

这个式子看上去比较亲切了。而且你观察到，对于 $a$ 的修改我们暴力，对于 $b$ 的修改，在差分数组 $db$ 上体现就是后缀加法。修改部分不是很难。

然后发现 $n=100$ 还没用。注意到一个事情，就是两个序列的差分各自有序。那你完全可以对 $b$ 序列差分 $db$ 保持不变，把 $a$ 序列的 $n-1$ 个差分，即数组 $da$，一个一个插入 $db$。这样只会插入 $100$ 次，是完全可以接受的。

刚才已经提过 $b$ 需要支持后缀加法了，这里又有一个查找前驱后继，第一反应是平衡树，但我不会。有没有替代品？那你可以二分+线段树，但是实测会 TLE，那就改成线段树上二分即可。

细节还是略多的，建议写之前大概捋一遍自己要维护哪些东西。捋清楚以后代码也就 100L 出头。可能比 F 还少点。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
using namespace std;
const int MAXN=1e5+10;
ll n,m,q;
ll a[MAXN],b[MAXN],type,k,d;
ll da[MAXN],db[MAXN];
ll s;
void Read(ll& num){
	char ch;
	while((ch=getchar()) && !isdigit(ch));
	num=ch-'0';
	while((ch=getchar()) && isdigit(ch))num=num*10+ch-'0';
}
struct SegmentTree{
	ll sum[MAXN<<2],tag[MAXN<<2],rv[MAXN<<2];
	void pushup(int x){sum[x]=sum[lc(x)]+sum[rc(x)];rv[x]=rv[rc(x)];}
	void pushdown(int x,int l,int r){
		if(!tag[x])return;
		int mid=(l+r)>>1;sum[lc(x)]+=tag[x]*(mid-l+1);sum[rc(x)]+=tag[x]*(r-mid);
		rv[lc(x)]+=tag[x];rv[rc(x)]+=tag[x];
		tag[lc(x)]+=tag[x];tag[rc(x)]+=tag[x];tag[x]=0;
	} 
	void upd(int x,int l,int r,int ql,int qr,ll val){
		if(ql<=l && qr>=r){
			sum[x]+=val*(r-l+1);tag[x]+=val;rv[x]+=val; 
			return;
		}
		pushdown(x,l,r);int mid=(l+r)>>1;
		if(ql<=mid)upd(lc(x),l,mid,ql,qr,val);
		if(qr>mid)upd(rc(x),mid+1,r,ql,qr,val);
		pushup(x);
	}
	void build(int x,int l,int r){
		if(l==r){
			sum[x]=rv[x]=db[l];
			return;
		}
		int mid=(l+r)>>1;build(lc(x),l,mid);build(rc(x),mid+1,r);pushup(x);
	}
	ll qry(int x,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r)return sum[x];
		pushdown(x,l,r);
		int mid=(l+r)>>1;ll ret=0;
		if(ql<=mid)ret+=qry(lc(x),l,mid,ql,qr);
		if(qr>mid)ret+=qry(rc(x),mid+1,r,ql,qr);
		pushup(x);return ret;
	}
	int search(int x,int l,int r,ll val){
		if(l==r)return l;
		int mid=(l+r)>>1;
		pushdown(x,l,r);
		int ret=0;	
		if(rv[lc(x)]>=val)ret=search(lc(x),l,mid,val);
		else ret=search(rc(x),mid+1,r,val);
		pushup(x);return ret; 
	}
}t; 
ll S(ll n){return n*(n+1)/2;}
int main(){
	Read(n);Read(m);Read(q);
	
	rep(i,1,n)Read(a[i]);
	rep(i,1,m)Read(b[i]);
	rep(i,2,n)da[i]=a[i]-a[i-1];
	rep(i,2,m)db[i]=b[i]-b[i-1];
	rep(i,2,m)s+=db[i]*(m-i+1);
	t.build(1,2,m);
	rep(i,1,q){
		Read(type);Read(k);Read(d);
		if(type==1){
			if(k==n){a[1]+=d;k--;}
			rep(i,n-k+1,n)da[i]+=d;
		}else{
			if(k==m){b[1]+=d;k--;}
			s+=d*S(k);
			t.upd(1,2,m,m-k+1,m,d);
		}
		ll ans=s+(n+m-1)*(a[1]+b[1]);
		ll sm=t.qry(1,2,m,2,m);
		rep(i,2,n){
			//find ai's positionS
			if(t.qry(1,2,m,m,m)<da[i]){ans+=sm;continue;}
			int pos=t.search(1,2,m,da[i]);
			if(pos!=2)ans+=t.qry(1,2,m,2,pos-1);
			ans+=da[i]*(m-pos+1);	
		}
		rep(i,2,n)ans+=da[i]*(n-i+1);
		printf("%lld\n",ans);
	}

	return 0;
}

```

---

## 作者：tzc_wk (赞：4)

> 摘自我的[杂题选做Ⅳ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp4.html)中的第 $96$ 题。

首先考虑什么样的路径是最优路径。我们先不妨假设我们先一直向右走，再一直向下走，即 $(1,1)\to(1,2)\to\cdots\to(1,m)\to(2,m)\to\cdots\to(n,m)$，但是这样显然不一定是最优解，因此考虑调整。调整的第一步显然是将 $(1,m-1)\to(1,m)\to(2,m)$ 调整为 $(1,m-1)\to(2,m-1)\to(2,m)$，显然后者代价比前者更优，当且仅当 $a_2+b_{m-1}<a_1+b_m$。再者就是将 $(1,m-2)\to(1,m-1)\to(2,m-1)$ 调整为 $(1,m-2)\to(2,m-2)\to(2,m-1)$，以及 $(2,m-1)\to(2,m)\to(3,m)$ 调整为 $(2,m-1)\to(3,m-1)\to(3,m)$，以此类推。按照这样的方式继续手玩下去可以发现，在最终的状态中，假设我们在点 $(i,j)$，那么我们会往下走，当且仅当 $j=m$，或者 $i\ne n$ 且 $a_{i+1}-a_i<b_{j+1}-b_j$。

我们考虑设 $pos_i$ 表示我们处于第 $i$ 行时，会在哪个位置首次向下走，由于 $n$ 很小并且题目中 $a,b$ 序列都是下凸的，因此对于同一行 $i$，必然存在一个断点 $j$，使得对于 $j$ 左边所有位置，当我们位于 $(i,j)$ 时都会向右走，而对于 $j$ 右边所有位置，当我们位于 $(i,j)$ 时都会向下走。且 $pos$ 数组也是单调不降的。这样一来问题就好办了，由于 $n$ 很小，因此对于每次修改，改完之后都可以直接线段树二分修改 $pos$ 数组，而答案即为 $\sum\limits_{i=1}^n(a_i·(pos_i-pos_{i-1}+1)+\sum\limits_{j=pos_{i-1}}^{pos_i}b_j)$，这个也可以每次 $\mathcal O(n\log m)$ 地求。比较麻烦的是要实现单点加求三阶前缀和，用树状数组维护平方项、一次项和常数项能够获得常数较小的实现。

时间复杂度 $\Theta(nm\log m)$。

```cpp
const int MAXN = 100;
const int MAXM = 1e5;
int n, m, qu; u64 a[MAXN + 5], b[MAXM + 5];
struct node {int l, r; u64 lz, sum, rit;} s[MAXM * 4 + 5];
void pushup(int k) {
	s[k].sum = s[k << 1].sum + s[k << 1 | 1].sum;
	s[k].rit = s[k << 1 | 1].rit;
}
void build(int k, int l, int r) {
	s[k].l = l; s[k].r = r; if (l == r) return s[k].sum = s[k].rit = b[l + 1] - b[l], void();
	int mid = l + r >> 1; build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
void tag(int k, u64 v) {
	s[k].rit += v; s[k].lz += v;
	s[k].sum += 1ull * (s[k].r - s[k].l + 1) * v;
}
void pushdown(int k) {if (s[k].lz) tag(k << 1, s[k].lz), tag(k << 1 | 1, s[k].lz), s[k].lz = 0;}
int walk(int k, u64 v) {
	if (s[k].rit <= v) return m;
	if (s[k].l == s[k].r) return s[k].l; pushdown(k);
	if (s[k << 1].rit <= v) return walk(k << 1 | 1, v);
	else return walk(k << 1, v);
}
void modify(int k, int l, int r, u64 v) {
	if (l <= s[k].l && s[k].r <= r) return tag(k, v), void();
	pushdown(k); int mid = s[k].l + s[k].r >> 1;
	if (r <= mid) modify(k << 1, l, r, v);
	else if (l > mid) modify(k << 1 | 1, l, r, v);
	else modify(k << 1, l, mid, v), modify(k << 1 | 1, mid + 1, r, v);
	pushup(k);
}
int pt[MAXN + 5];
void calc() {
	pt[0] = 1;
	for (int i = 1; i < n; i++) pt[i] = walk(1, a[i + 1] - a[i]);
	pt[n] = m;
}
struct fenwick {
	u64 t[MAXM + 5];
	void add(int x, u64 v) {for (int i = x; i <= m; i += (i & (-i))) t[i] += v;}
	u64 query(int x) {u64 ret = 0; for (int i = x; i; i &= (i - 1)) ret += t[i]; return ret;}
} t0, t1, t2;
void mdf(int l, u64 a, u64 b) {
	t2.add(l, b);
	t1.add(l, 2 * a + b);
	t0.add(l, 2 * a * (1 - l) + b * l * (1 - l));
}
u64 query(int x) {
	return (1ull * x * x * t2.query(x) + 1ull * x * t1.query(x) + t0.query(x)) / 2;
}
u64 query(int l, int r) {return query(r) - query(l - 1);}
u64 calcans() {
	u64 res = 0;
	for (int i = 1; i <= n; i++)
		res += 1ull * a[i] * (pt[i] - pt[i - 1] + 1) + query(pt[i - 1], pt[i]);
	return res;
}
int main() {
	scanf("%d%d%d", &n, &m, &qu);
	for (int i = 1; i <= n; i++) scanf("%llu", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%llu", &b[i]), t0.add(i, 2 * b[i]);
	build(1, 1, m - 1);
	while (qu--) {
		int typ, d, v; scanf("%d%d%d", &typ, &d, &v);
		if (typ == 1) {
			for (int i = 1; i <= d; i++)
				a[n - d + i] += 1ull * i * v;
		} else {
			mdf(m - d + 1, -1ull * (m - d) * v, v);
			modify(1, m - d, m - 1, v);
		}
		calc();
		printf("%llu\n", calcans());
	}
	return 0;
}
```

---

## 作者：Eon_Sky (赞：1)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Eon/solution-cf1609g)

### 主体思路：贪心+线段树

### 复杂度：$O(nq\log m)$

### 完整思路

最重要的性质是两个严格上升。

先不考虑修改，考虑一次统计答案，$(1, 1)$ 的贡献无法避免，我们先排除它们。

设初始值为 $0$，将每个格点的代价取消，将从 $(x, y)$ 走到 $(x + 1, y)$ 的代价设为 $a_{x + 1} - a_x$，走到 $(x, y + 1)$ 的代价设为 $b_{y + 1} - b_y$。

这样从 $(1, 1)$ 走到 $(x, y)$ 的代价之和即 $a_x +b_y - a_1 - b_1$，所以每一个代价	会在后面的每一步造成一次贡献，假设第 $i$ 次走代价为 $w$，则它会产生 $(n - i + 1)w$ 的贡献。

贪心地想，我们希望大的代价尽量贡献少的次数，而且我们每次走的差分代价也是递增的，所以方案是唯一的，每次走较小的代价即可。

![ ](https://cdn.luogu.com.cn/upload/image_hosting/gkxldeh8.png)

如果不懂看上面这张图自行模拟即可，图来自官方题解。

设 $da_i = a_{i + 1} - a_i,db_i = b_{i + 1} - b_i$，整个过程等价于将两个数组归并为一个 $d$ 数组，令 $n' = n - 1, m' = m - 1$，有 $d$ 数组长度为 $n' + m'$。

刚才的贪心过程相当于求一个 $\sum \limits_{i = 1}^{n' + m'} d_i \times (n' + m' - i + 1)$。

然后 $(1, 1)$ 的值，即 $a_1 + b_1$ 在每个格子中都出现了，所以总共贡献 $n + m - 1 = n' + m' + 1$ 次。

考虑修改的影响，对于 $da$ 可以暴力修改，特判 $a_1$，操作本质相当于在 $db$ 数组上区间加，可以用线段树维护，也要特判 $b_1$。

考虑如何统计答案，暴力归并我们并不能接受，但 $n$ 是小的，我们可以把 $n'$ 个 $da_i$ 插入 $db$ 中。

先维护一个 $\sum \limits_{i = 1}^{m'} db_i \times (m' - i + 1)$，每次倒序向其中插入一个 $da_i$ 相当于把不大于它的所有 $db_i$ 都后移一位，相当于多造成一次贡献，于是答案加上一个前缀的和即可，$da_i$ 贡献了 $n' - i + m' - tem + 1$ 次，这个相当于比它大的元素个数加一。

用线段树维护区间最小值，区间和，然后区间加、区间查询和、找前驱（线段树上二分）即可。

### 代码实现需要注意的地方：

- 需要开 **long long**。

### 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 100 + 5, M = 1e5 + 5, NM= 100100 + 5;

int n, m, q;
LL a[N], b[M];

LL temp, da[N], db[M];
//--------------------//
// Segment-Tree

#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

const int TM = 4e5 + 5;

struct Seg_Tree  {
    struct Seg_Tree_Node {
        LL mnv, sum, lazy;
    } t[TM];

    void tag(int rt, int L, int R, LL val) {
        t[rt].mnv += val, t[rt].sum += 1LL * (R - L + 1) * val, t[rt].lazy += val;
    }

    void push_up(int rt) {
        t[rt].mnv = min(t[ls(rt)].mnv, t[rs(rt)].mnv), t[rt].sum = t[ls(rt)].sum + t[rs(rt)].sum;
    }

    void push_down(int rt, int L, int R) {
        if (!t[rt].lazy)
            return;
        int mid = L + R >> 1;
        tag(ls(rt), L, mid, t[rt].lazy), tag(rs(rt), mid + 1, R, t[rt].lazy), t[rt].lazy = 0;
    }

    void build(int rt, int L, int R) {
        if (L == R)
            return t[rt] = {db[L], db[L], db[L]}, void();
        int mid = L + R >> 1;
        build(ls(rt), L, mid), build(rs(rt), mid + 1, R), push_up(rt);
    }

    void change(int rt, int L, int R, int l, int r, LL val) { // 区间加
        if (l > r)
            return;
        if (L >= l && R <= r)
            return tag(rt, L, R, val), void();
        push_down(rt, L, R);
        int mid = L + R >> 1;
        if (l <= mid)
            change(ls(rt), L, mid, l, r, val);
        if (r > mid)
            change(rs(rt), mid + 1, R, l, r, val);
        push_up(rt);
    }

    int query_rk(int rt, int L, int R, int val) { // 查找前驱
        if (t[rt].mnv > val)
            return 0;
        if (L == R)
            return L;
        push_down(rt, L, R);
        int mid = L + R >> 1;
        if (t[rs(rt)].mnv <= val)
            return query_rk(rs(rt), mid + 1, R, val);
        return query_rk(ls(rt), L, mid, val);
    }

    LL query_sum(int rt, int L, int R, int l, int r) { // 区间求和
        if (l > r)
            return 0;
        if (L >= l && R <= r)
            return t[rt].sum;
        push_down(rt, L, R);
        int mid = L + R >> 1;
        if (r <= mid)
            return query_sum(ls(rt), L, mid, l, r);
        if (l > mid)
            return query_sum(rs(rt), mid + 1, R, l, r);
        return query_sum(ls(rt), L, mid, l, r) + query_sum(rs(rt), mid + 1, R, l, r);
    }
} T;
//--------------------//
void changea(int k, LL val) { // 修改 a
    if (k > n)
        a[1] += val, k = n; // 特判
    for (int i = n - k + 1; i <= n; i++)
        da[i] += val; // 暴力改
}

void changeb(int k, LL val) { // 修改 b
    if (k > m)
        b[1] += val, k = m;
    temp += 1LL * k * (k + 1) / 2 * val; // 维护题解中说的那个和
    T.change(1, 1, m, m - k + 1, m, val); // 后缀加
}

LL query() {
    LL res = temp + (a[1] + b[1]) * (n + m + 1); // 初始答案
    for (int tem, i = n; i >= 1; i--) {
        tem = T.query_rk(1, 1, m, da[i]); // 找前驱
        res += 1LL * (m - tem + n - i + 1) * da[i] + T.query_sum(1, 1, m, 1, tem); // 统计当前 da 贡献以及更新比它小的 db 贡献
    }
    return res;
}
//--------------------//
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &b[i]);
    n--, m--; // 差分元素少一个
    for (int i = 1; i <= n; i++)
        da[i] = a[i + 1] - a[i];
    for (int i = 1; i <= m; i++)
        db[i] = b[i + 1] - b[i], temp += db[i] * (m - i + 1); // 初始化
    T.build(1, 1, m);
    // printf("%lld\n", query());
    for (int op, k, d, i = 1; i <= q; i++) {
        scanf("%d%d%d", &op, &k, &d);
        if (op == 1)
            changea(k, d);
        else
            changeb(k, d);
        printf("%lld\n", query());
    }
    return 0;
}

```

---

## 作者：EuphoricStar (赞：0)

我独立做出一道 *3000？

考虑对于单次询问，除了 $O(nm)$ 的 dp，有没有什么方法能快速算出答案。发现若 $a_{i + 1} - a_i < b_{j + 1} - b_j$ 则 $i \gets i + 1$，否则 $j \gets j + 1$ 是最优的。这个贪心的证明不难，考虑当前新走到某一行或某一列的贡献是差分数组乘上剩下的格子个数，显然选较小的乘上去最优。

那么现在单次询问我们能做到 $O(n + m)$ 了。观察到 $n \le 100$，考虑从这里入手。可以枚举每一行，二分出在这一行能走到的最右的列（也就是最大的 $j$ 使得 $b_{j + 1} - b_j < a_{i + 1} - a_i$）。用一棵树状数组维护 $b$ 的二阶差分即可树状数组上二分找到这个位置。

$a$ 对答案的贡献每次枚举 $i$ 直接计算即可，$b$ 对答案的贡献不难发现是 $[1, m]$ 的和加上一些单点的形式（单点的贡献是向下走产生的）。查 $b$ 的单点的值，考虑转化成 $b$ 的一阶差分的前缀和，也可以用树状数组维护。

总时间复杂度为 $O((nm + q) \log m + nq)$。

[code](https://codeforces.com/problemset/submission/1609/242788357)

---

## 作者：Otomachi_Una_ (赞：0)

**[E. A Stroll Around the Matrix](https://www.luogu.com.cn/problem/CF1609G)（7）**

这种问题首先要考虑一个容易被 ds 维护的东西或者解法。一般这个解法应当是简单的，重点应当在怎么上 ds。

首先考虑不修改的情况。手膜不难发现每次走权值比较小边的贪心就是对的。但是这玩意 ds 显然不太好维护，因为每一次加入的是一个等差数列。转到差分就是差分的后缀加，我们可以考虑维护差分。

题目说了两个序列的差分都是单调增的，上面走路径相当于每次选一个差分小的一边走过去，这个差分会给后面的所有步增加。也就是我们考虑给 $a,b$ 的差分数组 $da,db$ 进行二路归并得到 $d$，最后差分造成的贡献就是 $\sum(n+m-1-i)\times d_i$。

观察 $n$ 非常小，应当考虑 $\mathcal O(nm\log)$ 的做法。我们把上面的式子拆开，分成 $\sum d$ 和 $\sum i\times d_i$。$\sum d$ 是好求的，$\sum i\times d_i$ 有一定难度，因为我们需要对 $da,db$ 进行二路归并。考虑到 $a$ 的长度比较小，我们可以用 ds 维护 $db$，同时暴力插入 $da$ 查询贡献。

一个基本的想法是用 splay 解决。每次插入 $da$，查询完之后删除 $da$。遗憾的是虽然复杂度正确，但是 splay 常数太大，不太能做。

我们考虑到我们的 $db$ 已经有序，我们只需要每次查询 $da$ 在 $db$ 当中的排名即可。用线段树维护常数小很多。

[submission](https://codeforces.com/contest/1609/submission/228382097)。

---

## 作者：Miraik (赞：0)

先不考虑修改，考虑查询的实质。

题目里给了一个差分数组单调上升的条件，我们自然地去将问题放到差分数组上考虑。记 $c,d$ 为 $a,b$ 的差分数组，然后你会发现我在 $(i,j)$ 位置往下走/往右走一步相当于将 $c_{i+1}$ / $d_{j+1}$ 加入后面所有步的贡献。

进一步的，由差分数组单调上升，我们容易得到每次选取 $c_{i+1}$ 和 $d_{j+1}$ 中更小的那个必然不劣。

若我们将 $c$ 和 $d$ 归并得到数组 $x$，那么答案可以表示为：

$(n+m-1) \times (a_1+b_1) + \sum\limits_{i=1}^{n+m-2} (n+m-1-i) \times x_i$

而修改操作对差分数组就是后缀加。

但是每次查询都进行归并的话显然是吃不消的。我们注意到 $n \le 100$ 看上去很有用，我们可以这么做：

对于 $c$ 数组的修改直接暴力，而 $d$ 数组在线段树上维护。

对于查询的贡献我们分成三部分：$c$ 数组自身的贡献；$d$ 数组自身的贡献；将 $c$ 和 $d$ 归并起来时，额外造成的贡献。

$c$ 自身的贡献即为 $\sum\limits_{i=1}^{n-1} c_i \times (n-i)$，$d$ 同理。这个是好维护的。

每次归并的时候只需要考虑将 $c_i$ 插入 $d$ 数组时的贡献。$d$ 数组中所有比 $c_i$ 小的数会多一步贡献，而其他数会给 $c_i$ 造成一步贡献。容易用线段树二分实现。

总时间复杂度 $O(nq \log m)$，我 CF 上跑了 5500ms，鉴定为人傻常数大。

[code](https://codeforces.com/contest/1609/submission/203618558)

---

