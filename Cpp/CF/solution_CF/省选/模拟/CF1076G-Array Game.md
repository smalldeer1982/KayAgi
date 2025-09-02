# Array Game

## 题目描述

考虑如下的两人游戏：

有一个由正整数组成的数组 $b_1, b_2, \ldots, b_k$。最开始，一个棋子放在数组的第一个格子里，并且 $b_1$ 减 $1$。两位玩家轮流行动。每一回合，当前玩家需要执行以下操作：假设棋子当前在第 $x$ 个格子，那么他需要选择一个 $y \in [x, \min(k, x + m)]$，满足 $b_y > 0$，然后将棋子移动到第 $y$ 个格子，并将 $b_y$ 减 $1$。如果无法进行有效的移动，则当前玩家输掉游戏。

你的任务如下：给定一个由 $n$ 个正整数组成的数组 $a$，以及 $q$ 个对其的操作。操作有两种类型：

- $1\ l\ r\ d$ —— 对于每个 $i \in [l, r]$，将 $a_i$ 增加 $d$；
- $2\ l\ r$ —— 问如果在 $a$ 的第 $l$ 到第 $r$ 个元素组成的子数组上进行上述游戏，假设双方都采取最优策略，谁会获胜。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2 4
1 2 3 4 5
1 3 5 6
2 2 5
1 1 2 3
2 1 5
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
5 1 3
1 1 3 3 4
2 1 5
2 2 5
2 3 5
```

### 输出

```
1
2
1
```

# 题解

## 作者：tzc_wk (赞：9)

[Codeforces 题面传送门](https://codeforces.ml/contest/1076/problem/G) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1076G)

一道 hot tea……听讲解时半懂不懂~~因为不知道题目意思~~，最后终究还是琢磨出来了（

首先注意到对于每个 $a_i$，它具体是什么并不重要，我们只关心它的**奇偶性**，因为每次到达一个点后，如果后手有必胜策略，那么如果先手原地踏步，那么后手完全可以重复先手的操作直到 $a_i\lt 2$ 为止，如果先手有必胜策略则反过来。由于每次走到一个点时候都要令 $a_i$ 减 $1$，因此我们可以直接令 $a_i\leftarrow (a_i-1)\bmod 2$，这样游戏可以转化为，有 $n$ 个 $[0,1]$ 中的整数 $a_1,a_2,\cdots,a_n$，初始有一个棋子在 $a_1$ 处，两个人轮流操作，每次一个人可以将棋子移到 $[i+1,\min(i+m,n)]$ 中的某个位置上，或者如果 $a_i=1$，那么可以将棋子停留在原地并令 $a_i=0$，不可以操作者输，问最终谁 win。

考虑暴力 $dp$，$dp_{i,j}$ 为当前棋子在 $i$，$a_i=j$ 的输赢状态，$0$ 表示先手必输，$1$ 表示先手必胜，那么显然 $dp_{i,j}=1$ 当且仅当 $\exists k\in[i+1,\min(i+m,n)]$ 满足 $dp_{k,a_k}=0$，或者 $j=1$ 且 $dp_{i,0}=0$，否则 $dp_{i,j}=0$。

这样暴力做是 $\mathcal O(nq)$ 的，考虑优化这个暴力，以下简记 $dp_i=dp_{i,a_i}$，手玩一下样例就会发现一个 observation，那就是如果 $a_i=1$，那么必有 $dp_i=1$，因为如果 $[i+1,i+m]$ 中存在必输点那么移到那个必输点即可，否则 $dp_{i,0}=0$，原地踏步即可。也就是说我们只用对于 $a_i=0$ 检验 $[i+1,i+m]$ 中是否存在必输点即可。那么怎么检验呢？注意到这题的 $m$ 令人出乎意料地小，$2^m$ 不过 $32$，并且涉及区间操作，因此可以想到线段树维护个什么东西。我们考虑对序列 $a$ **建一棵线段树，线段树上每个区间 $[l,r]$ 开一个 $2^m$ 的数组 $to$**，其中 $to_S$ 表示如果 $r+1,r+2,\cdots,r+m$ 是否为必胜点的状态为 $S$（$0$：必输点；$1$：必胜点），那么 $l,l+1,\cdots,l+m-1$ 是否为必输点的状态是多少。这样显然可以在 $\mathcal O(2^m)$ 的时间内合并 $[l,mid],[mid+1,r]$ 两个节点上的信息，初始状态：若 $a_i=1$，那么 $to_S=(2S+1)\&(2^m-1)$，其中 $\&$ 为按位与，否则如果 $S=2^m-1$ 那么 $to_S=2^m-2$，否则 $to_S$ 也等于 $(2S+1)\&(2^m-1)$。最终求答案就将查询区间拆分一下、合并一下，如果查询得到的 $to_0$ 的第一位为 $0$，那么答案是 $2$，否则答案是 $1$。至于那个区间加……显然如果 $x$ 是偶数那么我们肯定不用关它，否则相当于翻转一个区间的 $a$（$0\to 1,1\to 0$），我们就记 $b_i=2-a_i$，额外维护一下 $b$ 数组的胜负情况，记作 $to'$，翻转一整个区间时就直接交换它的 $to$ 和 $to'$ 即可，时间复杂度 $2^mn\log n$，已经可以通过此题。

当然还有比正解更优秀的做法，其实只要加一个非常 simple 的 optimization 即可，注意到上面的做法中记录了一个二进制状态，费时费力，而其实我们只关心它第一个 $0$ 的位置，因此我们可以将 $to_i$ 的定义修改为：如果在 $r$ 右边离 $r$ 最近的必输点位置为 $r+i$，那么在 $l-1$ 右边离 $l-1$ 最近的必输点位置为 $l-1+to_i$，如果该位置 $>l-1+m$ 那么 $to_i=m+1$，显然在这种定义下我们可以 $\mathcal O(m)$ 地合并序列信息，因此复杂度就降到了 $mn\log n$。

```cpp
const int MAXN=2e5;
const int MAXM=5;
int n,m,qu;ll a[MAXN+5];
struct data{
	int a[MAXM+3];
	data(){memset(a,0,sizeof(a));}
	friend data operator +(data x,data y){
		data res;
		for(int i=1;i<=m+1;i++) res.a[i]=y.a[x.a[i]];
		return res;
	}
};
struct node{int l,r,rev;data v[2];} s[MAXN*4+5];
void pushup(int k){
	s[k].v[0]=s[k<<1|1].v[0]+s[k<<1].v[0];
	s[k].v[1]=s[k<<1|1].v[1]+s[k<<1].v[1];
}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;
	if(l==r){
		for(int i=1;i<=m;i++){
			s[k].v[a[l]].a[i]=s[k].v[a[l]^1].a[i]=i+1;
		} s[k].v[a[l]].a[m+1]=1;s[k].v[a[l]^1].a[m+1]=m+1;return;
	} int mid=l+r>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
void pushdown(int k){
	if(s[k].rev){
		swap(s[k<<1].v[0],s[k<<1].v[1]);s[k<<1].rev^=1;
		swap(s[k<<1|1].v[0],s[k<<1|1].v[1]);s[k<<1|1].rev^=1;
		s[k].rev=0;
	}
}
void flip(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return swap(s[k].v[0],s[k].v[1]),s[k].rev^=1,void();
	int mid=(pushdown(k),s[k].l+s[k].r>>1);
	if(r<=mid) flip(k<<1,l,r);else if(l>mid) flip(k<<1|1,l,r);
	else flip(k<<1,l,mid),flip(k<<1|1,mid+1,r);pushup(k);
}
data query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].v[0];
	int mid=(pushdown(k),s[k].l+s[k].r>>1);
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1|1,mid+1,r)+query(k<<1,l,mid);
}
int main(){
	scanf("%d%d%d",&n,&m,&qu);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]=(~a[i])&1;
	build(1,1,n);
	while(qu--){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int l,r;ll x;scanf("%d%d%lld",&l,&r,&x);
			if(x&1) flip(1,l,r);
		} else {
			int l,r;scanf("%d%d",&l,&r);data t=query(1,l,r);
			printf("%d\n",1+(t.a[m+1]==1));
		}
	}
	return 0;
}
```



---

## 作者：Marsrayd (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1076G)

先思考如果我们只查询 $[1,n]$ 怎么做？

容易想到 $dp_i$ 表示跳到第 $i$ 个格子，是先手必胜还是先手必败的。

显然可以倒过来 ```dp```：
- 当 $a_i\equiv1\pmod 2$ 时，$dp_i=1$

因为如果跳到后面 $m$ 个格子都是先手必胜的话，那么谁跳出去谁输，先手可以选择在 $i$ 这个格子一直跳，最终后手一定要跳出去
  
如果有一个先手必败，那直接跳过去即可。

- 当 $a_i\equiv0\pmod 2$ 时，$dp_i$ 取决于之后的 $m$ 个格子中有没有先手必败态，有 $=1$，没有 $=2$。

于是，我们就有了一个时间复杂度为 $\mathcal{O}(n\times m\times q)$ 的优秀做法，而且我们发现，$dp_i$ 至于 $a_i$ 的奇偶性有关。

考虑优化，由于本题带区间修改，不难想到线段树，发现本题的 $m$ 非常小，考虑在这上面下功夫。

由于 $dp_i$ 的值只可能是 $1$ 或 $0$，$m$ 又很小，考虑把对区间有用的 $dp$ 值状态压缩下来。

对于线段树上的每个区间，记录如果 $[r+1,r+m]$ 的 $dp$ 值状态为 $S$，那么我们这个区间的 $[l,l+m-1]$ 的 $dp$ 值的状态应该是什么。

这是很好合并的，具体见之后的代码。

然后考虑区间修改操作，区间加偶数肯定是没有用的，不改变 $a_i$ 的奇偶性，然而加奇数就有用了，等价于区间翻转奇偶性，于是我们再以相同的方式处理如果区间奇偶性翻转了的上述内容。

继续思考，发现许多的 $S$ 是没有用的，我们只需要知道 $S$ 中的第一个 $0$ 在哪即可（最优肯定跳到他），最终的时间复杂度 $\mathcal{O}(qm\log n)$。

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
const int N=200010;
inline int read()
{
	int x=0,y=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*y;
}
int TMPS[N],CNT;
inline int write(int x)
{
	CNT=0;
	if(x<0) x=-x,putchar('-');
	while(x) TMPS[++CNT]=x%10+'0',x/=10;
	for(int i=CNT;i>=1;i--) putchar(TMPS[i]);
}
int n,m,q,a[N];
struct node{
	int f[10];//记录[r+1,r+m]第一个0在i时，[l,l+m-1]第一个0在哪。 
	node operator +(const node &b)const{
		node res;
		for(int i=1;i<=m+1;i++) res.f[i]=f[b.f[i]];
		return res;
	}
};
struct Segment{
	int tag;//区间翻转tag 
	node dp[2];//两个版本，dp[0]为翻转后版本，dp[1]为要查询的版本
}tr[N<<2];
inline void pushup(int o)
{
	tr[o].dp[1]=tr[o<<1].dp[1]+tr[o<<1|1].dp[1];
	tr[o].dp[0]=tr[o<<1].dp[0]+tr[o<<1|1].dp[0];
}
inline void pushdown(int o)
{
	if(tr[o].tag)
	{
		std::swap(tr[o<<1].dp[1],tr[o<<1].dp[0]);
		std::swap(tr[o<<1|1].dp[1],tr[o<<1|1].dp[0]);
		tr[o<<1].tag^=1,tr[o<<1|1].tag^=1;
		tr[o].tag=0;
	}
}
void build(int o,int l,int r)
{
	if(l==r)
	{
		for(int i=1;i<=m;i++) tr[o].dp[1].f[i]=tr[o].dp[0].f[i]=i+1;
		//[r+1,r+m]没有必败态，如果a[i]-1为奇数必胜，否则必败。 
		if(a[l]==1) tr[o].dp[1].f[m+1]=m+1,tr[o].dp[0].f[m+1]=1; 
		else tr[o].dp[1].f[m+1]=1,tr[o].dp[0].f[m+1]=m+1;
		return;
	}
	int mid=l+r>>1;
	build(o<<1,l,mid),build(o<<1|1,mid+1,r),pushup(o); 
}
int L,R;
void update(int o,int l,int r)
{
	if(L<=l&&r<=R) {tr[o].tag^=1,std::swap(tr[o].dp[0],tr[o].dp[1]);return;}
	int mid=l+r>>1;pushdown(o);
	if(mid>=L) update(o<<1,l,mid);
	if(mid<R) update(o<<1|1,mid+1,r);
	pushup(o); 
}
node query(int o,int l,int r)
{
	if(L<=l&&r<=R) return tr[o].dp[1];
	int mid=l+r>>1;pushdown(o);
	if(mid<L) return query(o<<1|1,mid+1,r);
	else if(mid>=R) return query(o<<1,l,mid);
	else return query(o<<1,l,mid)+query(o<<1|1,mid+1,r);
}
signed main()
{
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(),a[i]=(a[i]&1)^1;//a[i]即为[i,i]的胜负
	build(1,1,n);
	for(int op,k;q--;)
	{
		op=read(),L=read(),R=read();
		if(op==1)
		{
			k=read();
			if(k&1) update(1,1,n);
		}
		else
		{
			node tmp=query(1,1,n);
			printf("%d\n",1+(tmp.f[m+1]==1));
		}
	}
	return 0;
}
```


---

## 作者：ywy_c_asm (赞：5)

~~降智好题……~~

首先要注意到这个游戏的关键是它可以原地跳，但是一旦跳出去之后就不能再回来，所以，我们只需要知道第一次跳到某个格子的时候先手必败还是必胜即可。这个倒着$dp$，如果$[i+1,i+m]$里面有的位置是先手必败的话那么在这个位置先手的人可以直接跳到那个位置让后手败掉，否则需要在当前位置消耗步数，但是如果对方还能走的话对方也必须在这里消耗步数，所以我们发现这个只与这个位置的奇偶性有关。如果这个位置当前是奇的，那么先手的在这个位置耗到只剩一步的情况，再耗一步后手就必败了。

于是我们就知道了，（注意一开始的时候会把第一个位置-1所以要把奇偶性反过来）如果第一个位置是偶数的话那么先手必胜，否则除非后面$m$步内有先手必败那么必胜，否则必败。

考虑这个东西怎么维护，这显然得$O(2^m)$记录后面$m$步的输赢状态，我开始的时候sb了还以为是要维护一个$2^m*2^m$的矩阵来$ddp$，其实这不是矩阵……这是一个变换，就是每个位置相当于一个变换$f(S)$表示当$[i+1,i+m]$的状态是$S$的时候$[i,i-1+m]$的状态，这东西显然有结合律，运算是$O(2^m)$的，那就在线段树上维护区间的变换即可。区间加的时候偶数没用，奇数相当于区间反转奇偶性，在线段树上维护一个反的变换然后修改的时候交换一下即可。

另外我们求的目标应该是$f(11111111\cdots)$，因为它不能跳出这个区间，而只有当后面有0的时候才能跳出去，所以把区间外的部分都设为1就行了。~~我还被这个坑了……~~

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
using namespace std;
namespace ywy {
	inline ll get() {
	    ll n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int m;
	typedef struct _n {
	    int f[33];
	    _n() { memset(f, 0, sizeof(f)); }
	    friend _n operator*(const _n &a, const _n &b) {
	        _n c;
	        for (register int i = 0; i < (1 << m); i++) c.f[i] = b.f[a.f[i]];
	        return (c);
	    }
	} node;
	node data[1000001], fan[1000001];
	ll ints[200001];
	unsigned char bj[1000001];
	node dk0, dk1;
	inline void up(int tree) {
	    data[tree] = data[rs(tree)] * data[ls(tree)];
	    fan[tree] = fan[rs(tree)] * fan[ls(tree)];
	}
	inline void down(int tree) {
	    if (!bj[tree])
	        return;
	    bj[tree] = 0;
	    bj[ls(tree)] ^= 1;
	    bj[rs(tree)] ^= 1;
	    swap(data[ls(tree)], fan[ls(tree)]);
	    swap(data[rs(tree)], fan[rs(tree)]);
	}
	void build(int l, int r, int tree) {
	    if (l == r) {
	        if (ints[l] & 1)
	            data[tree] = dk1, fan[tree] = dk0;
	        else
	            data[tree] = dk0, fan[tree] = dk1;
	        return;
	    }
	    int mid = (l + r) >> 1;
	    build(l, mid, ls(tree));
	    build(mid + 1, r, rs(tree));
	    up(tree);
	}
	void fz(int rl, int rr, int l, int r, int tree) {
	    if (rl == l && rr == r) {
	        swap(fan[tree], data[tree]);
	        bj[tree] ^= 1;
	        return;
	    }
	    int mid = (l + r) >> 1;
	    down(tree);
	    if (rl > mid)
	        fz(rl, rr, mid + 1, r, rs(tree));
	    else {
	        if (rr <= mid)
	            fz(rl, rr, l, mid, ls(tree));
	        else {
	            fz(rl, mid, l, mid, ls(tree));
	            fz(mid + 1, rr, mid + 1, r, rs(tree));
	        }
	    }
	    up(tree);
	}
	node query(int rl, int rr, int l, int r, int tree) {
	    if (rl == l && rr == r)
	        return (data[tree]);
	    int mid = (l + r) >> 1;
	    down(tree);
	    if (rl > mid)
	        return (query(rl, rr, mid + 1, r, rs(tree)));
	    if (rr <= mid)
	        return (query(rl, rr, l, mid, ls(tree)));
	    return (query(mid + 1, rr, mid + 1, r, rs(tree)) * query(rl, mid, l, mid, ls(tree)));
	}
	void ywymain() {
	    int n = get();
	    m = get();
	    int q = get();
	    for (register int i = 0; i < (1 << m); i++) {
	        dk0.f[i] = (i >> 1) | (1 << (m - 1));
	        if (i == (1 << m) - 1)
	            dk1.f[i] = i >> 1;
	        else
	            dk1.f[i] = (i >> 1) | (1 << (m - 1));
	    }
	    for (register int i = 1; i <= n; i++) ints[i] = get();
	    build(1, n, 1);
	    while (q) {
	        q--;
	        int op = get();
	        if (op == 1) {
	            int l = get(), r = get();
	            ll d = get();
	            if (!(d & 1))
	                continue;
	            fz(l, r, 1, n, 1);
	        }
	        if (op == 2) {
	            int l = get(), r = get();
	            node cjr = query(l, r, 1, n, 1);
	            if (cjr.f[(1 << m) - 1] & (1 << (m - 1)))
	                printf("1\n");
	            else
	                printf("2\n");
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：_determination_ (赞：5)

在场上什么都想到了，就是没有想到线段树节点同时维护反转后的状态。

本文默认读者有一部分博弈论基础。

首先考虑怎么把这玩意做出来。你应该发现了我们不关心 $a$ 的具体数值，只关心他的奇偶性。同时每次到达一个格子会将该格子的数值减一，所以我们可以提前减一。之后我们所说的 $a_i$ 均指减一后的 $a_i$。

我们定义 $f_x$ 为走到了这个格子之后的先手的胜负。显然当 $a_x=1$ 时 $f_x=1$。因为如果在正常博弈论 dp 的情况下是输的先手就可以拖一步，而后手如果要再拖也会是先手把 $a_x$ 减到 0 从而让后手输。而如果正常情况下是赢得就直接赢了。而 $a_x=0$ 的情况就正常做即可。

好的如你所见，我们得到了一个 $O(nmq)$ 的做法。考虑优化。

继续考虑不带修的情况。我们发现 $f$ 数组在 dp 完之后呈现一种一堆 1 中间夹一小部分 0 的状态。又注意到我们在 $a_x=0$ 的转移中只关心后面出现的第一个 0 的位置。

考虑建一个线段树，节点中维护 $f_x$ 表示当右边部分最左边的 0 是 $x$（$x=0$ 代表在前 $m$ 格内没有 0）的情况下 dp 完毕后整个 dp 序列最左边的 0 是第几个数（如果前 $m$ 个格子没有 0 那么返回 0）。

合并节点的时候直接根据定义暴力转即可。合并的复杂度是 $O(qm\log n)$。这个复杂度显然是对的，但是我们不支持修改。

对于修改操作，显然当 $d$ 是偶数的时候不用管，否则相当于翻转一段区间的奇偶性。考虑同时记一个 $g$ 表示翻转后的 $f$ 数组，在翻转的时候直接交换 $f$ 和 $g$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
int a[200010];
int n,m,q;
struct node{
	int l,r,tag;
	int f[30],g[30];
}t[800010];
node merge(node l,node r)
{
	node ans;
	ans.l=l.l,ans.r=r.r,ans.tag=0;
	for ( int i = 0 ; i <= m ; i++ )
	{
		ans.f[i]=l.f[r.f[i]];
		ans.g[i]=l.g[r.g[i]];
	}
	return ans;
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		t[x].f[0]=1-a[l];
		t[x].g[0]=a[l];
		for ( int i = 1 ; i < m ; i++ )t[x].f[i]=t[x].g[i]=i+1;
		t[x].f[m]=t[x].g[m]=0;
		t[x].l=l;
		t[x].r=r;
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	t[x]=merge(t[x<<1],t[x<<1|1]);
}
void mktag(int x){for ( int i = 0 ; i <= m ; i++ )swap(t[x].f[i],t[x].g[i]);}
void pd(int x)
{
	if(!t[x].tag)return;
	t[x].tag=0;
	t[x<<1].tag^=1;
	t[x<<1|1].tag^=1;
	mktag(x<<1),mktag(x<<1|1);
}
void upd(int x,int l,int r)
{
	int lf=t[x].l,rt=t[x].r;
	if(l<=lf&&rt<=r)return mktag(x),t[x].tag^=1,void();
	if(rt<l||r<lf)return;
	pd(x);
	upd(x<<1,l,r),upd(x<<1|1,l,r);
	t[x]=merge(t[x<<1],t[x<<1|1]);
}
node calc(int x,int l,int r)
{
	int lf=t[x].l,rt=t[x].r;
	if(l<=lf&&rt<=r)return t[x];
	int mid=(lf+rt)/2;
	pd(x);
	if(mid<l)return calc(x<<1|1,l,r);
	if(r<=mid)return calc(x<<1,l,r);
	return merge(calc(x<<1,l,r),calc(x<<1|1,l,r));
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >>n >>m >>q;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> a[i];
		a[i]=(a[i]-1)%2;
	}
	build(1,1,n);
	while(q--)
	{
		int op,l,r,d;
		cin >> op >> l >>r ;
		if(op==1)
		{
			cin >> d;
			if(d&1)upd(1,l,r);
//			for ( int i = l ; i <= r ; i++ )a[i]=(a[i]+d)&1;
		}else{
			cout << 1+(calc(1,l,r).f[0]==1) << endl;
//			for ( int i = r ; i >= l ; i-- )
//			{
//				if(a[i]==1)f[i]=1;
//				else{
//					f[i]=1;
//					for ( int j = i+1 ; j <= min(r,i+m) ; j++ )f[i]=min(f[i],f[j]);
//					f[i]^=1;
//				}
//			}
//			cout << 2-f[l] << endl;
		}
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：4)

虽然是个 *3000 的题，但感觉也不是很 nb 的亚子嗷（

首先发现这字里行间都写着 ICG 三个大字，感觉很舒服。

可能的状态只有可能是这样的：某个后缀原封不动，然后这个后缀的上一个位置 $i$ 的值随便（$j\in[0,a_i)$），设其 SG 值为 $s_{i,j}$。这个题不涉及 ICG 的和，只需要考虑非零性。考虑转移，显然 $s_{i,j}=\bigvee\limits_{k=i+1}^{i+m}\lnot s_{k,a_k-1}\lor\lnot s_{i,j-1}$，后面一项如果满足 $j>0$ 的话。容易发现一个事实：把 $i$ 作阶段的话，每个阶段过后只可能关心 $s_{i,a_i-1}$。考虑只算这个东西。容易发现针对某个阶段，若那个 bigvee 里面有 1 的话肯定是 1 了；否则 $j=0\sim a_i-1$ 是 0 1 0 1 这样有周期性的，$s_{i,a_i-1}=1$ 当且仅当 $a_i$ 是偶数。那么 $a_i$ 只关心奇偶性~~，好家伙这幌子打得漂亮~~。

那考虑暴力算法：就从右往左对 $t_i=s_{i,a_i-1}$ 递推就行了。

很自然的想到，维护一个最近 $m$ 个位置的 $t$ 值的向量，如果这个递推关系可以写成一个有结合律的变换那就可以线段树维护区间复合了。首先想到的是线性变换，那考虑能不能实现逻辑或的表达？这玩意 $\bmod 2$ 意义下，只能表示异或，那么或能不能用异或表达出来？很遗憾，不能。一个简短的证明是，异或满足交换律结合律消去律，再怎么组合都只能是一堆人的异或再选择性地取反。

再想想就发现 wsbl。这个状态数这么少，只有 $2^m$，可以暴力存啊，这是最原始的变换——数组映射啊。。。。。那复合就可以 trivial 地 $\mathrm O(2^m)$。然后区间查询可以的，区间修改就打懒标记的话怎么迅速区间取反呢，实时维护一个反的复合做备用然后取反的时候 swap 即可。复杂度 $\mathrm O(q2^m\log n)$，有点危。再稍微想一下发现合法状态的向量里面最多有一个 $0$，那只有 $m+1$ 种，复杂度 $\mathrm O(qm\log n)$~~（早就预料到是这个复杂度）~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int n,m,qu;
bool a[N];
struct trans{
	int to[6];
	int &operator[](int x){return to[x];}
	trans(){for(int i=0;i<6;i++)to[i]=i;}
	friend trans operator*(trans x,trans y){
		trans z;
		for(int i=0;i<6;i++)z[i]=x[y[i]];
		return z;
	}
};
struct segtree{
	struct node{trans t,t0;bool lz;}nd[N<<2];
	#define t(p) nd[p].t
	#define t0(p) nd[p].t0
	#define lz(p) nd[p].lz
	void sprup(int p){
		t(p)=t(p<<1)*t(p<<1|1);
		t0(p)=t0(p<<1)*t0(p<<1|1);
	}
	void bld(int l=1,int r=n,int p=1){
		lz(p)=0;
		if(l==r){
			trans &t=t(p),&t0=t0(p);
			for(int i=1;i<m;i++)t[i]=t0[i]=i+1;t[m]=t0[m]=0;
			t[0]=0,t0[0]=1;
			if(a[l])swap(t,t0);
			return;
		}
		int mid=l+r>>1;
		bld(l,mid,p<<1),bld(mid+1,r,p<<1|1);
		sprup(p);
	}
	void init(){
		bld();
	}
	void sprdwn(int p){
		if(lz(p)){
			swap(t(p<<1),t0(p<<1)),lz(p<<1)^=1;
			swap(t(p<<1|1),t0(p<<1|1)),lz(p<<1|1)^=1;
			lz(p)=0;
		}
	}
	void flip(int l,int r,int p=1,int tl=1,int tr=n){
		if(l<=tl&&r>=tr)return swap(t(p),t0(p)),lz(p)^=1,void();
		sprdwn(p);
		int mid=tl+tr>>1;
		if(l<=mid)flip(l,r,p<<1,tl,mid);
		if(r>mid)flip(l,r,p<<1|1,mid+1,tr);
		sprup(p);
	}
	trans ask(int l,int r,int p=1,int tl=1,int tr=n){
		if(l<=tl&&r>=tr)return t(p);
		sprdwn(p);
		int mid=tl+tr>>1;trans res;
		if(l<=mid)res=res*ask(l,r,p<<1,tl,mid);
		if(r>mid)res=res*ask(l,r,p<<1|1,mid+1,tr);
		return res;
	}
}segt;
int main(){
	cin>>n>>m>>qu;
	for(int i=1;i<=n;i++){
		long long x;
		scanf("%lld",&x);
		a[i]=x&1;
	}
	segt.init();
	while(qu--){
		int tp,l,r;
		scanf("%d%d%d",&tp,&l,&r);
		if(tp==1){
			long long x;
			scanf("%lld",&x);
			if(!(x&1))continue;
			segt.flip(l,r);
		}
		else printf("%d\n",segt.ask(l,r)[0]==1?2:1);
	}
	return 0;
}
```

# 

---

## 作者：Purslane (赞：3)

# Solution

这能有 `*3000`？

-----

如果 $q=1$ 怎么做？设 $dp_i$ 表示当前棋子在 $i$，是否先手必胜。

假设 $dp_{i+1 \dots i+m}$ 里存在一个 $0$（先手必败），那么 $dp_i=1$；否则，如果 $a_i \ge 2$，先手只能选择在原地不动——很容易发现，此时 $dp_i = (a_i-1) \bmod 2$。

因此我们只需要关注 $a_i$ 的奇偶性。

-----

考虑类似 DP 套 DP 的手段，在动态 DP 的过程中把 $dp_{i+1 \dots i+m}$ 状态压缩。设序列 $\mathcal T_i$ 表示如果 $dp_{i+1 \dots i+m}$ 的状态为 $s$，那么 $dp_{i \dots i+m-1}$ 的状态为 $\mathcal T_{i,s}$。

显然 $\mathcal T_i$ 只与 $a_i \bmod 2$ 有关。

很容易定义 $\mathcal T$ 的复合运算 $\mathcal T_1 \circ \mathcal T_2$，那么我们只需要维护 $\mathcal T_r \circ \mathcal T_{r-1} \circ \cdots \mathcal T_l$。

-----

区间和的信息容易使用线段树维护。

那么怎么处理区间修改呢？

这个比较典，维护原序列的复合结果，以及**原序列所有数都奇偶翻转**的复合结果即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,q,a[MAXN],flp[MAXN<<2];
struct G {int to[32];}mul[2],t[MAXN<<2][2];
G operator +(G A,G B) {
	G C;
	ffor(i,0,(1<<m)-1) C.to[i]=B.to[A.to[i]];
	return C;	
}
G gain(int op) {
	G ans;
	ffor(i,0,(1<<m)-1) {
		if(__builtin_popcount(i)!=m||!op) ans.to[i]=((i<<1)&((1<<m)-1))|1;
		else ans.to[i]=((i<<1)&((1<<m)-1));
	}
	return ans;
}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void flip(int k,int l,int r) {return swap(t[k][0],t[k][1]),flp[k]^=1,void();}
void update(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return flip(k,l,r),void();
	if(flp[k]) flp[k]=0,flip(lson,l,mid),flip(rson,mid+1,r);
	if(x<=mid) update(lson,l,mid,x,y);
	if(y>mid) update(rson,mid+1,r,x,y);
	return t[k][0]=t[rson][0]+t[lson][0],t[k][1]=t[rson][1]+t[lson][1],void();
}
void build(int k,int l,int r) {
	if(l==r) return t[k][0]=mul[a[l]&1],t[k][1]=mul[(a[l]&1)^1],void();
	build(lson,l,mid),build(rson,mid+1,r);
	return t[k][0]=t[rson][0]+t[lson][0],t[k][1]=t[rson][1]+t[lson][1],void();
}
G query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k][0];
	if(flp[k]) flp[k]=0,flip(lson,l,mid),flip(rson,mid+1,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return query(rson,mid+1,r,x,y)+query(lson,l,mid,x,y);
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	mul[0]=gain(0),mul[1]=gain(1);
	ffor(i,1,n) cin>>a[i];
	build(1,1,n);
	ffor(i,1,q) {
		int op,l,r,d;
		cin>>op>>l>>r;
		if(op==1) {
			cin>>d;
			if(d&1) update(1,1,n,l,r);	
		}
		else {
			G pr=query(1,1,n,l,r);
			int ans=pr.to[(1<<m)-1]&1;
			cout<<2-ans<<'\n';	
		}
	}
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

大家写的都是线段树，但是我个人觉得它没有分块好写（

> Observation 1.一个格子唯一有用的信息就是其奇偶性。

这很显然，因为无论哪个格子，都可以通过双方来回下棋来不断 $-2$。

> Definition 1.
>
> 我们定义一个格子“必胜”，意味着在对手将棋子移到该格子后，现在下棋的人有必胜策略。
>
> 同理可以定义”必败“。
>
> 我们定义一个格子为”偶格“，意味着在将棋子移到该格子前，该格子里面的数是偶数。
>
> 同理可以定义”奇格“。

> Observation 2.
>
> 偶格都为必胜格，奇格必胜当且仅当其之后 $m$ 格中存在必败格。

偶格必胜，因为如果接下来 $m$ 格有必败态显然可以直接移过去，而如果接下来 $m$ 格全为必胜态则可以留在原地不动（显然，这总是合法的，因为这格是偶格），让对手把棋移到必胜态去。

奇格必胜当且仅当可移到必败，因为显然留着原地不动不是合适的选择（对手完全可以继续不动），而如果往后移的话不移到必败态是赢不了的。

于是我们发现我们只关心该格之后首个必败格的位置，而这个值只有 $m+1$ 种不同取值。

现在我们考虑用数据结构维护。比如说就用分块，则我们可以记录，如果在块的右端点处首个必败格的距离确定的话，走到左端点处时首个必败格的距离是什么。

对于每个块，我们只需要对于 $m+1$ 种不同值全部处理一遍即可。

现在考虑区间加。显然如果加偶数不会改变奇偶性，加奇数则是区间反转。

那么就对每个块处理出其反转与否时的答案即可。

块长取 $\sqrt{\dfrac{N}{4M}}=100$ 取得最优复杂度。

跑得飞快，2s不到就过了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int BBB=100;
int n,m,q,BLK[200100],lp[2010];
int a[200100];
int f[2][2010][12];//1-m+1:the first block that fails is i;
bool rev[2010];
int tmp[200100];
void rebuild(int ip){
	for(int i=1;i<=m+1;i++){
		f[0][ip][i]=i;
		for(int j=lp[ip+1]-1;j>=lp[ip];j--){
			if(!a[j]||f[0][ip][i]<=m)f[0][ip][i]++;
			else f[0][ip][i]=1;
		}
		f[0][ip][i]=min(f[0][ip][i],m+1);
		f[1][ip][i]=i;
		for(int j=lp[ip+1]-1;j>=lp[ip];j--){
			if(a[j]||f[1][ip][i]<=m)f[1][ip][i]++;
			else f[1][ip][i]=1;
		}
		f[1][ip][i]=min(f[1][ip][i],m+1);
	}
}
void read(int&x){
	x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
int main(){
	read(n),read(m),read(q);
	for(int i=0;i<n;i++)read(a[i]),a[i]&=1,BLK[i]=i/BBB;
	lp[BLK[n]=BLK[n-1]+1]=n;
	for(int i=0;i<BLK[n];i++)lp[i]=i*BBB;
	for(int i=0;i<BLK[n];i++)rebuild(i); 
	for(int i=1,tp,l,r,x;i<=q;i++){
		read(tp),read(l),read(r),l--,r--;
		if(tp==1){
			read(x),x&=1;
			if(!x)continue;
//			printf("TURN[%d,%d]\n",l,r);
			if(BLK[l]==BLK[r]){for(int j=l;j<=r;j++)a[j]^=1;rebuild(BLK[l]);continue;}
			for(int j=BLK[l]+1;j<=BLK[r]-1;j++)rev[j]^=1;
			for(int j=l;j<lp[BLK[l]+1];j++)a[j]^=1;rebuild(BLK[l]);
			for(int j=lp[BLK[r]];j<=r;j++)a[j]^=1;rebuild(BLK[r]);
		}else{
//			printf("ASK[%d,%d]\n",l,r);
			int fail=m+1;
			if(BLK[l]==BLK[r]){
				for(int j=r;j>=l;j--){
					if(!(a[j]^rev[BLK[r]])||fail<=m)fail++;
					else fail=1;
				}
				putchar(fail==1?'2':'1'),putchar('\n');
				continue;
			}
//			puts("IN");
			for(int j=r;j>=lp[BLK[r]];j--){
				if(!(a[j]^rev[BLK[r]])||fail<=m)fail++;
				else fail=1;
			}
			fail=min(fail,m+1);
			for(int j=BLK[r]-1;j>=BLK[l]+1;j--)fail=f[rev[j]][j][fail];
			for(int j=lp[BLK[l]+1]-1;j>=l;j--){
				if(!(a[j]^rev[BLK[l]])||fail<=m)fail++;
				else fail=1;
			}
			fail=min(fail,m+1);
			putchar(fail==1?'2':'1'),putchar('\n');
		}
	}
	return 0;
}
/*
5 2 4
1 2 3 4 5
1 3 5 6
2 2 5
1 1 2 3
2 1 5
*/
```



---

## 作者：Genius_Star (赞：2)

### 思路：

定义一个位置为**必胜态**当且仅当棋子到达该位置后先手有必胜策略，**必败态**同理。

如果 $i$ 后面的 $m$ 个格子有**必败态**时，则操作方一定会移过去；

否则当后面的 $m$ 个格子全都是**必胜态**时，两者肯定不想移过去，于是就会在 $i$ 处**消耗**着，每一轮 $a_i$ 都要 $-2$，于是最后就只跟 $a_i$ 的奇偶性有关。

则考虑从后往前 $dp$，定义 $dp_i$ 表示 $i$ 处是否是**必胜态**，若 $dp_{i+1,\cdots,i+m}$ 存在一个 $0$，则 $dp_i=1$；否则 $dp_i = (a_i -1) \bmod 2$。

现在我们已经可以做到 $O(nq)$ 的复杂度，考虑继续优化。

先令 $a_i \gets (a_i-1) \bmod 2$，注意到是对区间加同一个数，则当 $d$ 是偶数时，是不会改变 $a_i$ 的奇偶性的；否则相当于区间取反。

考虑令 $f_i = \{dp_i,dp_{i+1},dp_{i+m-1}\}$（可以直接状压为二进制数），然后使用线段树维护每一个区间 $[l,r]$ 的 $F_{l,r,S}$ 表示当 $f_{r+1} = S$ 时 $f_l = F_{l,r,S}$。

发现很好维护，设我们要合并 $[l_1,r_1],[l_2,r_2]$ 这两个区间，则：

$$F_{l_1,r_2,S} = F_{l_1,r_1,F_{l_2,r_2,S}}$$

可以做到单次合并 $O(2^m)$，但是因为区间还可能会取反，所以我们还需要维护当区间取反时的 $F'_{l,r,S}$。

这样我们就做到了 $O(2^mn \log n)$，本题已经可以通过，但是还可以优化。

注意到，我们只需要关心这 $m$ 个数中第一个为 $0$ 的位置，则令 $f_i$ 表示 $[i+1,i+m]$ 中第一个为 $dp_j=0$ 的位置，$F_{l,r,id}$ 表示当第 $f_{r+1} = id$ 时 $f_l = F_{l,r,id}$（$id=0$ 代表全为 $1$）。

还是一样，设我们要合并 $[l_1,r_1],[l_2,r_2]$ 这两个区间，则：

$$F_{l_1,r_2,id} = F_{l_1,r_1,F_{l_2,r_2,id}}$$

则若询问的 $F_{l,r,0}$ 不为 $1$ 的话就是先手必胜；此时单次合并是 $O(m)$ 的，总时间复杂度为 $O(mn \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(register int i=l;i<=r;i++)
#define _For(i,l,r) for(register int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
int n,m,q,op,l,r,x;
bool a[N];
namespace Sub1{
	int S;
	const int M=1ll<<5;
	struct St{
		int F[M];
		St(){
			memset(F,0,sizeof(F));
		}
		inline int &operator[](const int i)noexcept{
	        return F[i];
	    }
		friend St operator+(St a,St b){
			St ans;
			For(i,0,S)
			  ans[i]=a[b[i]];
			return ans;
		}
	};
	struct Node{
		int l,r;
		St data[2];
		bool f;
		bool tag;
	}X[N<<2];
	void pushup(int k){
		X[k].data[X[k].f]=X[k<<1].data[X[k<<1].f]+X[k<<1|1].data[X[k<<1|1].f];
		X[k].data[X[k].f^1]=X[k<<1].data[X[k<<1].f^1]+X[k<<1|1].data[X[k<<1|1].f^1];
	}
	void rev(int k){
		X[k].f^=1;
		X[k].tag^=1;
	}
	void push_down(int k){
		if(X[k].tag){
			rev(k<<1);
			rev(k<<1|1);
			X[k].tag=0;
		}
	}
	void build(int k,int l,int r){
		X[k].l=l,X[k].r=r;
		if(l==r){
			For(i,0,S)
			  X[k].data[0][i]=X[k].data[1][i]=((i<<1ll)+1)&S;
			X[k].data[a[l]][S]--;
			return ;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void update(int k,int l,int r){
		if(X[k].l==l&&r==X[k].r){
			rev(k);
			return ;
		}
		push_down(k);
		int mid=(X[k].l+X[k].r)>>1;
		if(r<=mid)
		  update(k<<1,l,r);
		else if(l>mid)
		  update(k<<1|1,l,r);
		else{
			update(k<<1,l,mid);
			update(k<<1|1,mid+1,r);
		}
		pushup(k);
	}
	St query(int k,int l,int r){
		if(X[k].l==l&&r==X[k].r)
		  return X[k].data[X[k].f];
		push_down(k);
		int mid=(X[k].l+X[k].r)>>1;
		if(r<=mid)
		  return query(k<<1,l,r);
		else if(l>mid)
		  return query(k<<1|1,l,r);
		else
		  return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
	}
	void work(){
		S=(1ll<<m)-1;
		build(1,1,n);
		while(q--){
			op=read(),l=read(),r=read();
			if(op==1){
				x=read();
				if(x&1ll)
				  update(1,l,r);
			}
			else{
				write(2-(query(1,l,r)[S]&1));
				putchar('\n');
			}
		}
	}
};
namespace Sub2{
	const int M=25;
	struct St{
		int F[M];
		St(){
			memset(F,0,sizeof(F));
		}
		inline int &operator[](const int i)noexcept{
	        return F[i];
	    }
		friend St operator+(St a,St b){
			St ans;
			For(i,1,m+1)
			  ans[i]=a[b[i]];
			return ans;
		}
	};
	struct Node{
		int l,r;
		St data[2];
		bool f;
		bool tag;
	}X[N<<2];
	void pushup(int k){
		X[k].data[X[k].f]=X[k<<1].data[X[k<<1].f]+X[k<<1|1].data[X[k<<1|1].f];
		X[k].data[X[k].f^1]=X[k<<1].data[X[k<<1].f^1]+X[k<<1|1].data[X[k<<1|1].f^1];
	}
	void rev(int k){
		X[k].f^=1;
		X[k].tag^=1;
	}
	void push_down(int k){
		if(X[k].tag){
			rev(k<<1);
			rev(k<<1|1);
			X[k].tag=0;
		}
	}
	void build(int k,int l,int r){
		X[k].l=l,X[k].r=r;
		if(l==r){
			For(i,1,m)
			  X[k].data[0][i]=X[k].data[1][i]=i+1;
			X[k].data[a[l]][m+1]=1;
			X[k].data[a[l]^1][m+1]=m+1;
			return ;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void update(int k,int l,int r){
		if(X[k].l==l&&r==X[k].r){
			rev(k);
			return ;
		}
		push_down(k);
		int mid=(X[k].l+X[k].r)>>1;
		if(r<=mid)
		  update(k<<1,l,r);
		else if(l>mid)
		  update(k<<1|1,l,r);
		else{
			update(k<<1,l,mid);
			update(k<<1|1,mid+1,r);
		}
		pushup(k);
	}
	St query(int k,int l,int r){
		if(X[k].l==l&&r==X[k].r)
		  return X[k].data[X[k].f];
		push_down(k);
		int mid=(X[k].l+X[k].r)>>1;
		if(r<=mid)
		  return query(k<<1,l,r);
		else if(l>mid)
		  return query(k<<1|1,l,r);
		else
		  return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
	}
	void work(){
		build(1,1,n);
		while(q--){
			op=read(),l=read(),r=read();
			if(op==1){
				x=read();
				if(x&1ll)
				  update(1,l,r);
			}
			else{
				write(2-(query(1,l,r)[m+1]!=1));
				putchar('\n');
			}
		}		
	}
};
bool End;
int main(){
//	open("game.in","game.out");
	n=read(),m=read(),q=read();
	For(i,1,n)
	  a[i]=(read()-1)&1ll;
	if(m<=5)
	  Sub1::work();
	else
	  Sub2::work();
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Yajnun (赞：2)

观察到当前所处的位置棋子数为奇数时先手必胜，因为如果当前位置为先手必败时，先手可以原地不动迫使后手跳出。所以答案只与$[l,r]$区间中数的奇偶性有关。$1$操作可以看成区间翻转。

$ans[s]$表示$[r+1,r+m]$区间胜负态为$s$时，$[l,l+m-1]$区间的胜负态。用线段树分别维护当前的$ans$数组和整段区间翻转后的$ans$数组。观察到可能的状态$s$最多有$m+1$种（长度为$m$的区间里最多有一个先手必败态）。用线段树维护即可。
代码：
```
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstring>
#define ll long long
#define maxn 300005
#define p 1000000007
#define re(i,a,b) for(int i=a;i<=b;i++)
#define for_edge(x) for(int i=head[x];i;i=e[i].nxt)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
//______________________________________________________________________________________
int n,m,q,N;
inline int get_pre(int s1,int t)
{
	re(w1,0,m-1)
		if( (s1&(1<<w1)) && ( w1+1>t  )  )
					return w1+1;
	return 0;
}
struct ANS
{
	int ans[6];
	int operator[](int x){return ans[x];}
	inline ANS merge(ANS x)
	{
		ANS a;
		re(i,0,m)
			a.ans [i] =ans[x[i]];
		return a;
	}
}e;
ANS to[32];
int s[maxn],ch[maxn];
inline int get_type(int x)
{
	int ans = 0;
	for(;x;x-=x&-x)
		ans ^= s[x];
	return ans;
}
inline void flip_type(int x)
{
	for(;x<=n;x+=x&-x)
		s[x]^= 1;
}
inline int get_s(int l,int r,int L,int R)
{
	int x = 0;
	re(i,l,r)
		x |= ( i>=L && i<=R && get_type(i)  )<< r-i;
	//printf("%d %d %d\n",L,R,x);
	return x;
}
struct node
{
	int son[2],flip;ANS ans[2];
}a[maxn*2];
inline void rever(int x)
{
	if(x)
	{
		a[x].flip ^=1;
		swap(a[x].ans [0],a[x].ans [1]);
	}
}
inline void pushdown(int x)
{
	if(a[x].flip )
	{
		rever(a[x].son [0]);
		rever(a[x].son [1]);
		a[x].flip = 0;
	}
}
inline void pushup(int x)
{
	a[x].ans [0] = a[ a[x].son [0] ].ans[0].merge( a[ a[x].son [1] ].ans[0]  );
	a[x].ans [1] = a[ a[x].son [0] ].ans[1].merge( a[ a[x].son [1] ].ans[1]  );
}
#define MID(l,r) ( (l-1)/m+1+r/m ) /2 *m
int tot;
void build(int&x,int l,int r)
{
	x = ++tot;
	//printf("%d %d\n",l,r);
	if(r-l+1==m)
	{
		int s = get_s(l,r,l,r);
		a[x].ans[0] = to[s];
		a[x].ans[1] = to[N^s];
		return;
	}
	int mid = MID(l,r)  ;
	build(a[x].son [0],l,mid);
	build(a[x].son [1],mid+1,r);
	pushup(x);
}
ANS query(int x,int l,int r,int L,int R)
{
	if(l>R||L>r) return e;
	if(l>=L&&r<=R) 
		return a[x].ans [0];
	if(r-l+1==m)
		return to[ get_s(l,r,L,R) ];
	int mid = MID(l,r)  ;
	pushdown(x);
	ANS ans = query(a[x].son [0],l,mid,L,R).merge( query(a[x].son [1],mid+1,r,L,R)  );
	pushup(x);
	return ans;
}
void flip(int x,int l,int r,int L,int R)
{
	if(l>R||L>r)
		return ;
	if(l>=L&&r<=R)
	{
		rever(x);
		return ;
	} 
	if(r-l+1==m)
	{
		int s = get_s(l,r,l,r);
		a[x].ans[0] = to[s];
		a[x].ans[1] = to[N^s];
		return;
	}
	int mid = MID(l,r)  ;
	pushdown(x);
	flip(a[x].son [0],l,mid,L,R);
	flip(a[x].son [1],mid+1,r,L,R);
	pushup(x);
}
inline void debug()
{
//	re(i,1,n)printf("%d ",get_type(i));printf("\n");
	/*re(i,0,N)
		re(j,0,m)
		printf("%d %d %d\n",i,j,to[i][j])	;*/
}
int main()
{
//	freopen("0.in","r",stdin);
    n=read();m = read();q = read();N = (1<<m)-1;
    re(i,1,n)
    	ch[i] = read() &1;
    n += m - n%m;
    for(int i=n;i;i--)
    	ch[i]^=ch[i-1];
    	
    re(i,1,n)
    {
    	if(ch[i])
    		flip_type(i);
    }
    re(i,0,N)
    	re(j,0,m)
    		to[i].ans [j] = get_pre(i,j);
    re(i,0,m)
    	e.ans [i] = i;
    a[0].ans [0] = a[0].ans [1] = e;
    int root ;
    build(root,1,n);
	while(q--)
	{
		int opt = read(), l = read() , r = read();
		if(opt==1 )
		{
			if(read()&1)
			{
				flip_type(l);flip_type(r+1);
				flip(root,1,n,l,r);
			}
		}
		else
		 printf("%d\n", 1+ (query(root,1,n,l,r)[0] -1 == (n-l)%m)   );
	}
//	debug();
    return 0;
}

```


---

## 作者：BotYoung (赞：1)

前置知识：**博弈论**、**线段树**

我重点讲解了一下博弈过程，并做了张图片方便理解（说人话就是对像我一样的蒟蒻比较友好），然后埋了个小彩蛋……
## 题意：
对于一个区间 $[l,r]$，两人博弈的内容如下：

- 定义一个指针 $p$，初始指向 $a_l$，并将 $a_l$ 减一；
- 两人轮流选择一个位置 $p'\in [p,\min(p+m,r)],a_{p'}>0$，将 $a_{p'}$ 减一，随后 $p\leftarrow p'$；
- 不能操作者负。

给定一个长度为 $n$ 的序列 $a$ 和一个正整数 $m$，进行 $q$ 次区间修改或区间博弈操作。输出每次博弈的胜者。
## 思路：
博弈论+数据结构缝合怪好题 ~~（因为本蒟蒻第一眼没看出来所以好题）~~。

首先我们一定要想清楚博弈的过程，两个人的最优策略是什么。

### Q1:博弈的最优策略？
基础的博弈模型，了解的大佬们可以略过此部分。

~~（好像有原题但是来源忘了）~~

设当前的位置为 $p$，考虑先手处于 $p$ 位置时是否存在最优策略。

若先手必须修改当前指针的位置，这就是一个有向图博弈，只要 $\exists p'\in[p+1,\min(p+m,r)]$，$p'$ 位置的先手不存在必胜策略，先手在 $p$ 位置时就存在必胜策略。

如果停留在当前位置呢？

不难发现，若 $a_p=1$，那么先手选择是否在 $p$ 停留一步，就可以**决定两人的先后顺序**。根据游戏的最终状态，显然这是一个公平组合游戏，也即不存在平局的情况。所以我们得到一个重要的结论——**若先手能够决定自己的先后顺序，先手必胜**。

扩展一下，若 $a_p>1$，后手为了阻止先手满足上述结论，也就是阻止先手拿到必胜状态，后手肯定会停留在 $p$ 位置，两人开始激烈的争夺。所以另一个结论是--**若先手停留在 $p$ 位置，那么 $p$ 位置上的数一定会被取完**。

那么答案就很显然了，令 $f_p$ 表示先手在 $p$ 位置时是否存在必胜策略，有：

- 若 $a_p$ 是奇数，先手一定可以取走最后一个，此时先后手交换；也可以不停留在 $p$，仍然作为先手进行游戏。先手可以决定两人的先后顺序，故此时先手必胜，$f_p$ 为真；

- 反之，先手若想通过取走 $a_p$ 中元素达到“交换先后顺序”的效果，后手一定能够接着取一个阻止先手。那么先手一定无法取走最后一个元素，先后顺序无法被改变，$f_p$ 取决于后面的决策 $f_{p'}$。

那么我们需要做的就是**动态维护每一个区间的第一个位置上，先手必胜策略的存在性**。每次直接力暴重构+查询的总复杂度是 $O(qn)$ 的，显然不可过，考虑使用数据结构优化。

### Q2：如何维护 $f_{[l,r],p}$？
我们需要用到决策的一个重要性质：对于一个区间 $[l,r]$，若已知先手位于 $[r+1,r+m]$ 的胜负情况，由于每个 $f_{p\in [l,r]}$ 都可以由 $p$ 以后 的 $m$ 个状态以及它本身转移而来，所以易证所有 $p\in[l,r]$ 的状态都是唯一确定的。

有了这个性质我们该干什么？

- **状压！**

观察到 $m\leq5$，所以我们可以对于每一个区间 $[l,r]$，状压记录 $f_{p\in[r+1,r+m]}$，对于所有 $2^m$ 种情况，处理对应情况下出 $f_{p\in[l,l+m)}$ 的状态。

接下来就可以使用线段树维护了。

![CF1076G.jpg](https://cdn.luogu.com.cn/upload/image_hosting/9uo8aerm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，对于线段树节点 $[l,r]$，其左子树为 $[l,mid]$，右子树为 $[mid+1,r]$。我们枚举 $f_{[r+1,r+m]}$（上图右边的一段）的状态，那么我们通过右子树的信息可以得知对应状态下 $f_{[mid+1,mid+m]}$（上图中间的一段）。而我们通过左子树的信息，在已知中间部分的情况下，又可以转移到 $f_{[l,l+m)}$。

那么我们经过连续两次转移，就可以合并出区间 $[l,r]$ 上的信息了。（据说这是一种 ddp 的思想，蒟蒻不懂还请路过的大佬求证一下）

该做法时间复杂度为 $O(q\times 2^m\log n)$，$6$ 秒时限稳过。

### Q3:还能更优化吗？
都说到这了那当然能啊！

考虑决策的过程，我们只需要知道**最近的满足 $f_{p'}=0$ 的 $p'$ 的位置**，就可以转移了啊！

想想看，若存在这样的位置，那么 $f_p$ 一定为真，这个位置相对于整个区间不会发生变化；如果不存在这个合法的位置，$f_p$ 为假，那么这个位置就变成了 $p$。

最后只需要判断这个位置是不是 $l$ 就行了，复杂度变为 $O(qm\log n)$，可以说是大大优化了。

喜闻乐见的代码：
```cpp
#include <bits/stdc++.h>
#define reg register
#define rep(i, l, r) for (reg int i = l; i <= r; i++)
#define per(i, r, l) for (reg int i = r; i >= l; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
namespace io {
inline ll read(){
    reg ll s = 0, f = 1;
    reg char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { s = (s << 1) + (s << 3) + (ch ^ '0'); ch = getchar(); }
    return s * f;
}
inline void write(reg ll x){
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10); putchar(x % 10 ^ '0');
}
inline void write(reg ll x, reg char c){
    write(x), putchar(c);
}
}//namespace io
using namespace io;
const int N = 2e5 + 5;
int n, m, q, a[N];
struct node{
    int f[10];
    node operator +(const node &y) const{
        node z;
        rep(i, 1, m + 1) z.f[i] = f[y.f[i]];
        return z;
    }
};
struct SegmentTree{
    node val[2];
    bool tag;
}t[N << 2];
inline void pushup(int p){
    t[p].val[0] = t[p << 1].val[0] + t[p << 1 | 1].val[0];
    t[p].val[1] = t[p << 1].val[1] + t[p << 1 | 1].val[1]; 
}
inline void pushdown(int p){
    if (t[p].tag){
        swap(t[p << 1].val[0], t[p << 1].val[1]);
        swap(t[p << 1 | 1].val[0], t[p << 1 | 1].val[1]);
        t[p << 1].tag ^= 1, t[p << 1 | 1].tag ^= 1;
        t[p].tag = 0;
    }
}
inline void build(int p, int l, int r){
    if (l == r) {
        rep(i, 1, m) t[p].val[0].f[i] = t[p].val[1].f[i] = i + 1;
        t[p].val[0].f[m + 1] = a[l] ? m + 1 : 1;
        t[p].val[1].f[m + 1] = a[l] ? 1 : m + 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
inline void update(int p, int l, int r, int x, int y){
    if (x <= l && r <= y) {
        swap(t[p].val[0], t[p].val[1]);
        return t[p].tag ^= 1, void(0); 
    }
    pushdown(p); int mid = l + r >> 1;
    if (x <= mid) update(p << 1, l, mid, x, y);
    if (y > mid) update(p << 1 | 1, mid + 1, r, x, y);
    pushup(p);
}
inline node query(int p, int l, int r, int x, int y){
    if (x <= l && r <= y) return t[p].val[0];
    pushdown(p); int mid = l + r >> 1; node res;
    if (x > mid) res = query(p << 1 | 1, mid + 1, r, x, y);
    else if (y <= mid) res = query(p << 1, l, mid, x, y);
    else res = query(p << 1, l, mid, x, y) + query(p << 1 | 1, mid + 1, r, x, y);
    return pushup(p), res;
}
int main(){
    n = read(), m = read(), q = read();
    rep(i, 1, n) a[i] = read() & 1 ^ 1;
    build(1, 1, n);
    while (q--){
        int op = read();
        if (op == 1) {
            int x = read(), y = read(), k = read();
            if (k & 1) update(1, 1, n, x, y);
        } else {
            int x = read(), y = read();
            node ans = query(1, 1, n, x, y);
            if (ans.f[m + 1] == 1) puts("2");
            else puts("1");
        }
    }
    return 0;
}
```
## 后记
E_firework: $6$ 秒时限根号稳过。

唯一能听懂的人话就是，使用根号暴力重构的 trick。

本蒟蒻实在是太弱了听不懂神仙说话，但愿有路过的神犇能够听懂并复现……

---

## 作者：SunsetSamsara (赞：1)

## 分析

注意到只需要关注奇偶性。又因为每到一个点都会减去 $1$，所以把 $a_i$ 变成 $(a_i - 1) \mod 2$

令 $f_{i, j}$ 表示当前棋子在 $i$，$a_i = j$ 时的先手必胜策略的存在状态

显然 $f_{i, j} = 1$ 当且仅当存在一个在 $i + 1$ 到 $\min(i + m, n)$ 的 $k$ 满足 $f_{k, a_k} = 0$ 或 $j = 1$ 且 $f_{i, 0} = 0$

这个暴力是 $O(nq)$ 的，考虑优化。

我们记 $f_i = f_{i, a_i}$。不难发现，如果 $a_i = 1$，则 $f_i = 1$。

而当 $a_i = 0$ 时，线段树维护以后 $m$ 个位置的必胜状态，每个节点维护一个整数

第 $i$ 位表示以后 $m$ 位状态为 $i$ 的时候的必胜状态。

至于修改，除了维护当前状态之外再维护一个相反状态的必胜状态，如果一修改就直接交换即可

## 代码

```cpp

#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lld long long
using namespace std;
const int N = 200010;
const int M = 8;
int n, m, q;
lld a[N];
struct _node {
    int a[M];
    _node() { memset(a, 0, sizeof(a)); }
};
_node operator + (const _node &x, const _node &y) {
    _node ret;
    for (int i = 1; i <= m + 1; ++ i)
        ret.a[i] = y.a[x.a[i]];
    return ret;
}
struct node {
    int l, r;
    int rev;
    _node v[2];
} tr[N << 2];
inline void pushup(int k) {
    tr[k].v[0] = tr[k << 1 | 1].v[0] + tr[k << 1].v[0];
    tr[k].v[1] = tr[k << 1 | 1].v[1] + tr[k << 1].v[1];
}
inline void build(int k, int l, int r) {
    tr[k].l = l, tr[k].r = r;
    if (l == r) {
        for (int i = 1; i <= m; ++ i)
            tr[k].v[a[l]].a[i] = tr[k].v[a[l] ^ 1].a[i] = i + 1;
        tr[k].v[a[l]].a[m + 1] = 1;
        tr[k].v[a[l] ^ 1].a[m + 1] = m + 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    pushup(k);
}
void pushdown(int k){
    if (tr[k].rev) {
        swap(tr[k << 1].v[0], tr[k << 1].v[1]);
        tr[k << 1].rev ^= 1;
        swap(tr[k << 1 | 1].v[0], tr[k << 1 | 1].v[1]);
        tr[k << 1 | 1].rev ^= 1;
        tr[k].rev = 0;
    }
}
void modify(int k, int l, int r) {
//  printf("%d(%d %d) %d %d\n", k, tr[k].l, tr[k].r, l, r);
    if (l <= tr[k].l && tr[k].r <= r) {
        swap(tr[k].v[0], tr[k].v[1]);
        tr[k].rev ^= 1;
        return;
    }
    pushdown(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (l <= mid) modify(k << 1, l, r);
    if (mid < r) modify(k << 1 | 1, l, r);
    pushup(k);
}
_node query(int k, int l, int r) {
//  printf("%d(%d %d) %d %d\n", k, tr[k].l, tr[k].r, l, r);
    if (l <= tr[k].l && tr[k].r <= r) return tr[k].v[0];
    pushdown(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (r <= mid) return query(k << 1, l, r);
    if (l > mid) return query(k << 1 | 1, l, r);
    return query(k << 1 | 1, mid + 1, r) + query(k << 1, l, mid);
}
int main() {
//  freopen("C_test.in", "r", stdin);
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++ i) scanf("%d", a + i), a[i] = ((a[i] - 1) & 1);
    build(1, 1, n);
    int op, l, r;
    lld x;
    for (; q --; ) {
        scanf("%d%d%d", &op, &l, &r);
//      printf("%d %d %d\n", op, l, r);
        if (op == 1) {
            scanf("%lld", &x);
            if (x & 1) modify(1, l, r);
        } else printf("%d\n", query(1, l, r).a[m + 1] == 1 ? 2 : 1);
    }
}
```


---

## 作者：orz_z (赞：1)

### CF1076G Array Game

手推出大半，不会实现。

记必胜点表示走到此点时，下一手必胜；必败点同理。

每人都想要对方走到必胜点自己走到必败点。

有一种想法。

记 $pre_i$ 表示 $[1,i]$ 后缀第一个奇数的位置。

容易发现，对于询问 $[l,r]$，$pre_r$ 为必败点，$[pre_r+1,r]$ 为必胜点。

由于最多可前进 $m$ 格，那么 $[pre_r-1,pre_r-m]$ 为必胜点。

那么转化为谁先让 $a_{pre_r-m-1}$ 为 $0$ 谁赢，即如果 $pre_r-m-1$ 为偶格，为必胜点，否则为必败点。

就是操作 $[l, pre_r-m-1]$ 谁必胜。

但是这样极其难修改，考虑根据上述启发必胜态到必败态或者反过来的转移。

偶格必为必胜点，因为如果后面 $m$ 格有必败点可直接过去，否则全为必胜点就在原地不动，让对手到将棋移到必胜点。

奇格必胜，当且仅当可移到必败，显然此时不动不是最优的选择，因为奇偶性变了。

只需要知道每个点可移到的第一个必败点的位置，只有 $m+1$ 种不同取值。

然后考虑分块，记录在块的右端点的首个必败点距离确定时，走到块的左端点的首个必败点的距离。

预处理，对于每个值，处理 $m+1$ 种不同取值即可。

考虑修改，加偶数不改变奇偶性，加奇数则为区间翻转。

顺便记录一下区间翻转后的答案覆盖即可。

时间复杂度大致是 $\mathcal O(n\sqrt n)$，带个 $m$ 的小常数。

```cpp
#include <cstdio>

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

#define js(l, r, fail, tg, fl) for (int j = r; j >= l; --j) if ((fl ^ (!(a[j] ^ tg))) || fail <= m) fail++; else fail = 1;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

const int _ = 2e5 + 10, BL = 50, S = _ / BL + 10;;

int n, m, q, a[_], bel[_], L[S], R[S], f[2][S][7];

bool rev[S];

void build(int id) {
	for (int i = 1; i <= m + 1; ++i) {
		f[0][id][i] = f[1][id][i] = i;
		js(L[id], R[id], f[0][id][i], 0, 0);
		js(L[id], R[id], f[1][id][i], 0, 1);
		f[0][id][i] = min(f[0][id][i], m + 1), f[1][id][i] = min(f[1][id][i], m + 1);
	}
}

signed main() {
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; ++i) a[i] = read() & 1ll, bel[i] = (i - 1) / BL + 1;
	for (int i = 1; i <= bel[n]; ++i) L[i] = R[i - 1] + 1, R[i] = i * BL;
	R[bel[n]] = n;
	for (int i = 1; i <= bel[n]; ++i) build(i);
	int opt, l, r, c;
	while (q--) {
		opt = read(), l = read(), r = read();
		if (opt == 1) {
			c = read() & 1ll;
			if (!c) continue;
			if (bel[l] == bel[r]) {
				for (int i = l; i <= r; ++i) a[i] ^= 1;
				build(bel[l]);
				continue;
			}
			for (int i = l; i <= R[bel[l]]; ++i) a[i] ^= 1;
			build(bel[l]);
			for (int i = bel[l] + 1; i <= bel[r] - 1; ++i) rev[i] ^= 1;
			for (int i = L[bel[r]]; i <= r; ++i) a[i] ^= 1;
			build(bel[r]);
		} else {
			int fail = m + 1;
			if (bel[l] == bel[r]) {
				js(l, r, fail, rev[bel[l]], 0);
				putchar(fail == 1 ? '2' : '1'), he;
				continue;
			}
			js(L[bel[r]], r, fail, rev[bel[r]], 0);
			fail = min(fail, m + 1);
			for (int i = bel[r] - 1; i >= bel[l] + 1; --i)
				fail = f[rev[i]][i][fail];
			js(l, R[bel[l]], fail, rev[bel[l]], 0);
			fail = min(fail, m + 1);
			putchar(fail == 1 ? '2' : '1'), he;
		}
	}
	return 0;
}
```



---

## 作者：scp020 (赞：0)

# CF1076G Array Game 题解

感觉最难想的就是前期的博弈了。后面 ddp 就很套路。

## 解法

这种问题首先要先忽略修改操作。如果没有修改操作，那我们设状态 $f_i$ 表示在第 $i$ 格是否先手必胜。如果后面 $m$ 格存在先手必败状态，则在第 $i$ 格一定是先手必胜的。

如果后面 $m$ 格都是先手必胜的，那显然双方都不想主动走到后面 $m$ 格中，双方会轮流在当前格子中消耗，知道当前格子的数为 $0$。所以状态只与 $a_i$ 的奇偶性有关。

其实这是一种从 $[f_{i+1}\ f_{i+2}\ \dots\ f_{i+m}]$ 到 $[f_i\ f_{i+1}\ \dots\ f_{i+m-1}]$ 的变换，我们可以将这个行向量状压，值域不超过 $2^5$。变换的更形式如图所示。

![变换](https://cdn.luogu.com.cn/upload/image_hosting/jy4ju4hl.png)

通过图我们不难发现这种变换是有结合律的，所以可以使用线段树维护区间变换的结果，设线段树节点表示区间为 $[l,r]$，区间的变换即为 $f_{r+1}$ 进行了这一区间中一些列的变换 $f_l$ 的值会是多少。然后我们就很自然的支持了单点修改 $a_i$ 的操作。

现在考虑如何支持区间修改。

注意到转移只与 $a_i$ 的奇偶性有关，而且区间加一个数会同步改变这个区间所有数的奇偶性，而且变换只有两种，而且还有括号修复那题的 trick，我们考虑把每个节点的两种变换都存下来，如果区间修改不改变奇偶性的话我们就忽略操作，否则即为交换两种变换。

然后就做完了。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * useless things
     */
};
using namespace fast_IO;
int n,m,q,a[200010];
struct transform
{
    int a[32];
    inline transform()
    {
        memset(a,0,sizeof(a));
    }
    inline int &operator[](const int ind) noexcept
    {
        return a[ind];
    }
};
struct node
{
    transform *now,*opp;
    int lazy;
    node *lc,*rc;
    node()
    {
        now=new transform(),opp=new transform(),lazy=0,lc=rc=nullptr;
    }
    inline void pushup()
    {
        for(int i=0;i<=(1<<m)-1;i++)
            now->a[i]=lc->now->a[rc->now->a[i]],
            opp->a[i]=lc->opp->a[rc->opp->a[i]];
    }
    inline void pushdown()
    {
        if(lazy)
        {
            std::swap(lc->now,lc->opp),std::swap(rc->now,rc->opp),lc->lazy^=1,rc->lazy^=1,lazy=0;
        }
    }
};
class seg_tree
{
    #define ls l,mid
    #define rs mid+1,r
private:
    node *root;
    inline node *build(int l,int r)
    {
        node *rt=new node();
        if(l==r)
        {
            for(int i=0;i<(1<<m)-1;i++) rt->now->a[i]=rt->opp->a[i]=(i*2+1)%(1<<m);
            rt->now->a[(1<<m)-1]=((1<<m)-1)^a[l],rt->opp->a[(1<<m)-1]=rt->now->a[(1<<m)-1]^1;
        }else
        {
            int mid=(l+r)/2;
            rt->lc=build(ls),rt->rc=build(rs),rt->pushup();
        }
        return rt;
    }
    inline void fix(node *rt,const int L,const int R,int l,int r)
    {
        if(L<=l && r<=R)
        {
            std::swap(rt->now,rt->opp),rt->lazy^=1;
            return;
        }
        int mid=(l+r)/2;
        rt->pushdown();
        if(L<=mid) fix(rt->lc,L,R,ls);
        if(R>mid) fix(rt->rc,L,R,rs);
        rt->pushup();
    }
    inline transform ask(node *rt,const int L,const int R,int l,int r)
    {
        if(L<=l && r<=R) return *(rt->now);
        int mid=(l+r)/2;
        rt->pushdown();
        if(L>mid) return ask(rt->rc,L,R,rs);
        if(R<=mid) return ask(rt->lc,L,R,ls);
        transform ll=ask(rt->lc,L,R,ls),rr=ask(rt->rc,L,R,rs),ret;
        for(int i=0;i<=(1<<m)-1;i++) ret[i]=ll[rr[i]];
        return ret;
    }
public:
    inline void build()
    {
        root=build(1,n);
    }
    inline void fix(const int L,const int R,const long long val)
    {
        if(val&1) fix(root,L,R,1,n);
    }
    inline int ask(const int L,const int R)
    {
        return 2-(ask(root,L,R,1,n)[(1<<m)-1]&1);
    }
};
seg_tree tree;
long long tmp;
signed main()
{
    in>>n>>m>>q;
    for(int i=1;i<=n;i++) in>>tmp,a[i]=tmp&1;
    tree.build();
    for(int i=1,op,x,y;i<=q;i++)
    {
        in>>op>>x>>y;
        if(op==1) in>>tmp,tree.fix(x,y,tmp);
        else out<<tree.ask(x,y)<<'\n';
    }
    fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](http://codeforces.com/problemset/problem/1076/G)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1076G)

## 分析

考虑从后往前推。如果一个位置后面能走到的位置中有一个必败态，则一定会走过去，则当前位为必胜态。否则两人必然在当前位反复磨，直到一方不得不离开为止。不得不离开的那位就输了。因此当前位是否必胜只与当前位的奇偶性与后 $m$ 位的状态有关。由于 $m$ 很小，考虑直接压成一个数，对每一位记录后面 $m$ 位的状态，转移相当于根据这些状态推出当前状态，然后把当前状态也扔到状态里，然后转移到（序列的）前一位。注意到这实际上是一个只与奇偶性有关的状态的映射，而且定义域很小。我们直接拿数组记下这个映射，放到线段树上维护。区间加法考虑若加的是偶数，则相当于没变。否则相当于把区间中所有数奇偶性取反。由于每个叶子的映射只有两种，而且一旦取反就是对整个区间取反，所以我们对每个点都记两种映射，要取反就把两个映射交换。最后合并的时候注意映射合并的方向。

## 代码

```cpp
#include <iostream>
#define int long long
using namespace std;
int n, m, q;
int a[200005];
struct f {
    short a[33];
    short& operator[](int x) { return a[x]; }
} T[800005][2];
f A[2];
f operator*(f a, f b) {
    f c;
    for (int i = 0; i < (1 << m); i++) c[i] = b[a[i]];
    return c;
}
struct Segment_Tree {
    bool tg[1000005];
    void tag(int o) {
        tg[o] ^= 1;
        swap(T[o][0], T[o][1]);
    }
    void pushdown(int o) {
        if (!tg[o]) 
            return;
        tag(o << 1);
        tag(o << 1 | 1);
        tg[o] = 0;
    }
    void Build(int o, int l, int r) {
        if (l == r) {
            T[o][0] = A[a[l] & 1];
            T[o][1] = A[!(a[r] & 1)];
            return;
        }
        int mid = (l + r) >> 1;
        Build(o << 1, l, mid);
        Build(o << 1 | 1, mid + 1, r);
        T[o][0] = T[o << 1 | 1][0] * T[o << 1][0];
        T[o][1] = T[o << 1 | 1][1] * T[o << 1][1];
    }
    void Change(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            tag(o);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (L <= mid) 
            Change(o << 1, l, mid, L, R);
        if (R > mid) 
            Change(o << 1 | 1, mid + 1, r, L, R);
        T[o][0] = T[o << 1 | 1][0] * T[o << 1][0];
        T[o][1] = T[o << 1 | 1][1] * T[o << 1][1];
    }
    f Query(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) 
            return T[o][0];
        pushdown(o);
        int mid = (l + r) >> 1;
        if (R <= mid) 
            return Query(o << 1, l, mid, L, R);
        if (L > mid) 
            return Query(o << 1 | 1, mid + 1, r, L, R);
        return Query(o << 1 | 1, mid + 1, r, L, R) * Query(o << 1, l, mid, L, R);
    }
} seg;
signed main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (short i = 0; i < (1 << m); i++) {
        if (i != (1 << m) - 1) 
            A[0][i] = A[1][i] = (i << 1 | 1);
        else {
            A[0][i] = (i << 1 | 1);
            A[1][i] = (i << 1);
        }
        if (i & (1 << (m - 1)))  
            A[0][i] ^= (1 << m), A[1][i] ^= (1 << m);
    }
    seg.Build(1, 1, n);
    while (q--) {
        int op, l, r, d;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> d;
            if (d & 1)
                seg.Change(1, 1, n, l, r);
        } else {
            cin >> l >> r;
            f tmp = seg.Query(1, 1, n, l, r);
            cout << 2 - (tmp[(1 << m) - 1] & 1) << "\n";
        }
    }
    return 0;
}

---

## 作者：huazai676 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1076G)

由于 $a_i>0$，所以只关心 $a_i$ 的奇偶性：考虑当前的决策，如果把骰子往后仍对自己有利，则往后仍；如果不利，则对双方都不利，则双方都会原地踏步直到减到零后被迫往后仍。至此可以得到 $O(nmq)$ 的倒推[解法](https://codeforces.com/contest/1076/submission/246638849)。

设 $f_i$ 表示先手取一个 $a_i$ 后能否取胜。观察倒推的过程可以表示成：从后往前枚举 $i$，若 $a_i$ 为奇数且 $f_i$ 还未被赋值则 $f_i \gets 1$，然后 $\forall j \in [i-m,i-1]$， $f_j \gets 0$。考虑用线段树维护这些信息，发现只需要在每个节点维护 $F_x$ 表示假设强制把区间右边的 $x$ 个 $f_i$ 赋值为 0，区间 $f$ 最左边的 1 在哪个位置。则 $F_{u,i}=F_{ls,m-F_{rs,i}+1}$（但是由于区间长度可能小于 $m$，实现时有诸多细节）。由于每个 1 只会影响 $m$ 个数，$F$ 开 $m$ 的长度即可。

对于修改再记录个取反后的 $G$，每次 swap 一下即可。时间复杂度 $O((n+q)m\log n)$。

[代码](https://codeforces.com/contest/1076/submission/246681472)

---

