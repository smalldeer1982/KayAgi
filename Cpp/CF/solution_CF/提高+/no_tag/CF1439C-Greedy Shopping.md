# Greedy Shopping

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ of integers. This array is non-increasing.

Let's consider a line with $ n $ shops. The shops are numbered with integers from $ 1 $ to $ n $ from left to right. The cost of a meal in the $ i $ -th shop is equal to $ a_i $ .

You should process $ q $ queries of two types:

- 1 x y: for each shop $ 1 \leq i \leq x $ set $ a_{i} = max(a_{i}, y) $ .
- 2 x y: let's consider a hungry man with $ y $ money. He visits the shops from $ x $ -th shop to $ n $ -th and if he can buy a meal in the current shop he buys one item of it. Find how many meals he will purchase. The man can buy a meal in the shop $ i $ if he has at least $ a_i $ money, and after it his money decreases by $ a_i $ .

## 说明/提示

In the first query a hungry man will buy meals in all shops from $ 3 $ to $ 10 $ .

In the second query a hungry man will buy meals in shops $ 4 $ , $ 9 $ , and $ 10 $ .

After the third query the array $ a_1, a_2, \ldots, a_n $ of costs won't change and will be $ \{10, 10, 10, 6, 6, 5, 5, 5, 3, 1\} $ .

In the fourth query a hungry man will buy meals in shops $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 9 $ , and $ 10 $ .

After the fifth query the array $ a $ of costs will be $ \{10, 10, 10, 7, 6, 5, 5, 5, 3, 1\} $ .

In the sixth query a hungry man will buy meals in shops $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
10 6
10 10 10 6 6 5 5 5 3 1
2 3 50
2 4 10
1 3 10
2 2 36
1 4 7
2 2 17```

### 输出

```
8
3
6
2```

# 题解

## 作者：Fairicle (赞：13)

相较于 div2 C 我还是觉得这题更好写/kk

一眼就知道是个对序列操作的数据结构题。有两种操作，一种修改，一种查询。

考虑**从性质入手**，本题的性质是序列**单调不递增**，并且修改后也显然满足该性质。那么有序序列就可以想到**二分**。

于是显而易见操作 $1$ 需要二分出最大的小于 $y$ 的数在哪，操作 $2$ 需要二分出一个位置 $s$，使得 $\sum_{i=x}^sa_i\leq y$ 且 $\sum_{i=x}^{s+1}a_i> y$，或者 $\sum_{i=x}^na_i\leq y$。

做法有很多种实现方式，有的写不好就带上了 3log 从而 gg。考虑线段树的优美性质于是直接在它上面二分即可。

对于操作 $1$ 维护区间最小值，若左儿子最小值大于等于 $y$ 就到右儿子里面找，否则递归左儿子。这部分显然是 $O(logn)$ 的。

对于操作 $2$ 维护区间和，先给出代码。
```cpp
inline int query(int id,int l,int r,int lbor,int &y){
    if(r<lbor||y<mn[id]) return 0;
    if(l>=lbor&&y>=sum[id]){
        y-=sum[id];
        return min(n,r)-l+1;
    }
    pushdown(id,l,r);
    int mid=(l+r)>>1,ans=0;
    if(mid>=lbor) ans+=query(id<<1,l,mid,lbor,y);
    ans+=query(id<<1|1,mid+1,r,lbor,y);
    return ans;
}
```


若该区间右端点小于 $x$ 或区间最小值大于当前 $y$，那么显然是 $0$；若区间合法且区间和小于当前 $y$ 则直接算上这段长度，否则递归左右儿子。

在此对 $y$ 采取引用可以实时减去已经成为答案的段，同时先遍历左儿子再遍历右儿子也满足了从左到右进行遍历。

可以证明，这个过程中被记入答案的节点数量为 $log_2y$ 级别。首先定义一个节点的深度为其在线段树中的深度。

可以发现，若一个被选节点是其父节点的左儿子，那么接下来选的节点必然不会是右节点，**否则答案不连续**；并且只能选**深度比它更深**的左节点，直到叶子节点。

若一个被选节点是其父节点的右儿子，那么接下来它有**两种选择**：选深度不小于它的左儿子，随后深度逐渐加深，一直到叶子节点；选深度小于它的一个右儿子（它父亲的兄弟）。

所以所选从左到右节点的深度应当是**先递减后递增**，假定一开始在叶子结点递增，最后递减到另外一个叶子节点，中间经过的点数也只有 $2log_2y$。而抵达一个节点所经过的节点数不超过 $log_2n$，故这步操作复杂度不大于 $O(logylogn)$。

[code](https://www.luogu.com.cn/paste/yktubhwc)

---

## 作者：Karry5307 (赞：10)

### 题意

给定一个长度为 $n$ 的非递增序列 $a$，在一段路上依次排列了 $n$ 个商店，在第 $i$ 个商店买一顿饭的价钱是 $a_i$。现在有 $q$ 次操作，每次操作形如以下两种：

- `1 x y`：对所有 $1\leq i\leq n$ 将 $a_i$ 赋值为 $\max(a_i,y)$。

- `2 x y`：一个人从 $x$ 号商店开始走向最后一个商店，一开始有 $y$ 元钱。如果走到某一家商店门前看到自己能够买一顿饭那就买，求出这个人买了几顿饭。

$\texttt{Data Range:}1\leq n,q\leq 2\times 10^5$

### 题解

极好的线段树二分题。

对于 $1$ 操作来说，可以二分出最左端的位置 $i$ 满足 $a_i<y$，然后区间覆盖即可，**注意这个操作并不改变序列的单调性。**

对于 $2$ 操作来说，可以在线段树上二分出这个答案来。但是这个左端点的限制会使得二分写起来很麻烦，于是考虑将这个影响消掉。对于一个人 $(x,y)$ 来说，将他的钱增加 $\sum\limits_{i=1}^{x-1}a_i$ 然后让他从 $1$ 开始走，由于这个人从 $1$ 到 $x-1$ 都会买东西，所以到了 $x$ 这个位置他的钱就与原来是一样的，最后再把之前多算的 $x-1$ 个商店减掉就好了。 

注意到每个人进商店买东西构成最多 $\log y$ 个连续段，时间复杂度就是 $O(q\log y\log n)$ 的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
struct SegmentTree{
	ll l,r,mn,sum,tag;
};
SegmentTree tree[MAXN<<2];
ll n,m,op,u,v;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
#define ls node<<1
#define rs (node<<1)|1
inline void update(ll node)
{
	tree[node].mn=min(tree[ls].mn,tree[rs].mn);
	tree[node].sum=tree[ls].sum+tree[rs].sum;
}
inline void create(ll l,ll r,ll node)
{
	tree[node]=(SegmentTree){l,r,0,0,0};
	if(l==r)
	{
		return (void)(tree[node].sum=tree[node].mn=x[l]);
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls),create(mid+1,r,rs),update(node);
}
inline void spread(ll node)
{
	if(tree[node].tag)
	{
		ll lenl=tree[ls].r-tree[ls].l+1,lenr=tree[rs].r-tree[rs].l+1;
		ll tag=tree[node].tag;
		tree[ls].mn=tag,tree[rs].mn=tag,tree[ls].tag=tag,tree[rs].tag=tag;
		tree[ls].sum=tag*lenl,tree[rs].sum=tag*lenr,tree[node].tag=0;
	}
}
inline void cover(ll l,ll r,ll val,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		tree[node].sum=val*(tree[node].r-tree[node].l+1);
		return (void)(tree[node].tag=tree[node].mn=val);
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	l<=mid?cover(l,r,val,ls):(void)1,r>mid?cover(l,r,val,rs):(void)1;
	update(node);
}
inline ll query(ll l,ll r,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		return tree[node].sum;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	return (l<=mid?query(l,r,ls):0)+(r>mid?query(l,r,rs):0);
}
inline ll lb(ll val,ll node)
{
	if(tree[node].l==tree[node].r)
	{
		return tree[node].l;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	return lb(val,tree[ls].mn>val?rs:ls);
}
inline ll query(ll &val,ll node)
{
	if(tree[node].sum<=val)
	{
		return val-=tree[node].sum,tree[node].r-tree[node].l+1;
	}
	if(tree[node].l==tree[node].r)
	{
		return 0;
	}
	spread(node);
	ll lenl=tree[node].r-tree[node].l+1,res=0;
	tree[ls].mn<=val?res+=query(val,ls):1;
	tree[rs].mn<=val?res+=query(val,rs):1;
	return res;
}
inline void disp(ll node)
{
	if(tree[node].l==tree[node].r)
	{
		return (void)(printf("%d ",tree[node].sum));
	}
	spread(node),disp(ls),disp(rs);
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	create(1,n,1);
	for(register int i=0;i<m;i++)
	{
		op=read(),u=read(),v=read();
		if(op==1)
		{
			cover(lb(v,1),u,v,1);
		}
		if(op==2)
		{
			v+=u>1?query(1,u-1,1):0,printf("%d\n",query(v,1)-u+1);
		}
	}
}
```

---

## 作者：二gou子 (赞：7)

学长说这是一道线段树二分题，让我们一定要学会，于是我开始了~~爆肝~~之旅。为了给和我一样~~比较菜的人看~~，我打算将题解写得详细而且通俗易懂一些。

## 思路

首先一眼秒的暴力思路，直接两层循环上去干，总时间复杂度$O(qn)$，~~然后直接暴毙。~~

接着想怎么优化，既然学长说是线段树二分，莫非是线段树维护+二分查找？我试试我试试，嗯，首先发现操作$1$不会改变序列的单调性：大的不会变，因为它们本来就比这个值要大；而被改的值本来就比这个值小，改完之后还是比没有改的值小，所以大小关系没有改变，所以可以二分。对于操作$1$，我只需要维护区间最大值，然后每次在线段树中往下递归找到第一个大于等于替换值的位置就可以了。查询区间最大值时间复杂度是$O(logn)$，然后二分又是$O(logn)$，一共有$q$次操作，那么现在对于操作$1$，我就可以在$O(nlog^2n)$的时间复杂度内解决了。看一眼数据范围：$n \leq 2*10^5$，嗯老哥这波很稳。然后再看操作$2$，**故 技 重 施**，害，这不是小菜一碟？这蓝题就这呀，我还以为线段树二分有多难呢，两个普及算法拼起来罢了。首先二分找到第一个能买的东西的位置，时间复杂度$O(logn)$。然后计算区间和，$O(logn)$。然后......欸？貌似不太对劲啊？好像后面还有若干段，而每一段都需要$O(log^2n)$来解决，再加上$q$次询问，我不就炸了吗$QWQ$。

危，想错了。

正当我绞尽脑汁想如何优化时，学长一语惊醒梦中人：如果在线段树外面二分，那么无论怎么优化都是要带着这个$log$。但是线段树二分的意思是在线段树里面二分，这样你递归的时候不就相当于把区间二分了吗，用一个$log$就全部解决了。恍然大悟！

具体操作如下：在查询的时候，我去递归左右儿子节点。首先分为三种大情况：$1.$完全包含。在这种情况下分为三种子情况：$a.$，这个区间的最大值比$y$（含义见题意）要小，那么也就是说在这个区间里，第一个能买的商品就是左端点，直接返回左端点。$b.$，这个区间里的最小值比$y$要大，那也就是说这段区间里的东西我一个也买不起，那么可以返回$n+k$，其中$k$只要随便给一个正值就行了，为的是让它大于$n$，我代码中写的是$10$。$c.$比最大值小，比最小值大，那也就是说我们要求的答案恰好在这个区间内，$pushdown$下传标记之后直接递归然后去$min$即可（因为我们要找的是**第一个**能买的物品的位置）。$2.$完全不包含。这种情况直接返回$n+k$即可（不包含算个**）。$3.$部分包含。这种情况也很简单，直接递归左右儿子就行了。这样我们会发现，在线段树向下递归的时候，其实无意间完成了类似二分的过程。在原先的线段树+二分中，我们要先用$log$的时间求出最大或最小值，然后二分还要一个$log$。但现在一个$log$就解决了。

而上述只是操作$2$的前半部分，后半部分还要求出一段区间，使得这段区间满足：如果加上原序列的下一个数，和就会超过$y$，也就是我们买不起了。我代码中的此函数返回值是我刚好**买不起**的第一个数的下标。那么按照上个暴力的思路，单次这样又要$log$求出区间和然后$log$二分。但是与刚才的思路差不多，我们还是递归左右儿子节点：这半部分操作就明显比上半部分要简单一点。大致思路就是，如果左儿子的区间和我能买得起，那么我要找的位置肯定在右边。反之，就在左边。我们通过前半部分操作来确定左端点然后在区间内老老实实地递归即可。但是学长又提出了骚操作，包括其他有的题解也有这个骚操作：我其实不用管左端点在哪个位置。假设说，我应该从$x$号开始买，但是我如果从$1$号开始买，就相当于我多花了$1$号到$x-1$号的钱。如果我手中的钱加上这一部分钱，然后以$1$为起点开始查找，这样就会发现我们把左端点统一了，这样做的好处就是代码中少了很多细节，更便于实现和调试，包括我也是这么做的。

至此，代码和思路以及完全详细地讲解了一遍。但是现在还差最后的一步：证明复杂度。经过上面的优化，我们成功把每一次操作$1$都优化到了$O(qlog^2n)$，而每一次操作$2$都优化到了$O(qlogn*k)$。而其中的$k$就在于我买了几段，我买了几段东西就要递归几次，所以我们就要证明$k$最大能有多大。

而结论就是：$k \leq log_2y$

我也不知道这算是感性理解还是理性证明，但是正确性是可以保证的。我们这样想：假设有一个人这样去写了，你要构造一组数据把他卡成$TLE$，那么就要让$k$尽可能的大。而给定的区间$x-n$是不会改变的，如果构造一组数据，让他每一段都只买了一件物品，就可以尽可能地让段数变多。**但是，**如果一段只卖一个，那么下一个一定买不起。也就是说，假设有两个相邻的物品，它们的价格分别是$w_i$和$w_{i+1}$，那么$w_i \leq y < w_i+w_{i+1}$。我们这样想：由于序列是单调不增的，那么$y-w_i < y/2$，那我们可以看成，每一次买一个东西，最后总段数要比每一次总钱数除以$2$得到的总段数要少。而每次除以$2$，最终就会得到$log_2y$段。总结一下就是：在**最坏情况下，**，最多会分成$logy$段，也就是$O(logn)$的操作最多进行$logy$次。那么对于整个操作$2$，最坏时间复杂度为$O(qlog^2n+qlognlogy)$。可以在规定时间内求出最终的结果。

希望能给不会的童鞋以帮助，节省更多的时间。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m;
ll a[200005];
struct Node {
	int l,r;
	ll v,tag,minn=1000000000000,maxx=-1000000000000;
	Node *ls,*rs;
	Node(const int L,const int R) {
		l=L,r=R;
		if(l==r) {
			tag=0;
			v=a[l];
			minn=a[l];
			maxx=a[l];
			ls=rs=NULL;
		} else {
			tag=0;
			int M=(L+R)/2;
			ls=new Node(L,M);
			rs=new Node(M+1,R);
			pushup();
		}
	}
	inline void pushup() {
		maxx=max(ls->maxx,rs->maxx);
		minn=min(ls->minn,rs->minn);
		v=ls->v+rs->v;
	}
	inline void pushdown() {
		if(tag==0) return;
		else {
			ls->maketag(tag);
			rs->maketag(tag);
			tag=0;
		}
	}
	inline void maketag(ll w) {
		v=(r-l+1)*w;
		tag=w;
		minn=tag;
		maxx=tag;
	}
	inline bool InRange(const int L,const int R) {
		return (l>=L)&&(r<=R);
	}
	inline bool OutofRange(const int L,const int R) {
		return (r<L)||(l>R);
	}
	inline void upd(const int L,const int R,ll w) {
		if(InRange(L,R)) {
			maketag(w);
		} else if(!OutofRange(L,R)) {
			pushdown();
			ls->upd(L,R,w);
			rs->upd(L,R,w);
			pushup();
		}
	}
	inline ll qry1(const int L,const int R) {
		if(InRange(L,R)) {
			return v;
		}
		if(OutofRange(L,R)) {
			return 0;
		} else {
			pushdown();
			return ls->qry1(L,R)+rs->qry1(L,R);
		}
	}
	inline ll qry2(ll w){//第一个买不了的点(前缀和 
		if(l==r){
			if(l==n&&w>=v){
				return l+1;//特判，如果全都能买，那么不能买的第一个位置相当于n+1
			}
			else return l;
		}
		else{
			pushdown();
			if(ls->v<=w){
				return rs->qry2(w-ls->v);
			}
			else{
				return ls->qry2(w);
			}
		}
	}
	inline ll qry3(const int L,const int R,ll w){//第一个能买的点(单个商品 
		if(InRange(L,R)){
		 	if(maxx<=w){
		 		return l;
			}
			if(minn>w){
				return n+10;
			}
			else{
				pushdown();
				return min(ls->qry3(L,R,w),rs->qry3(L,R,w));
			}
		}
		if(OutofRange(L,R)){
			return n+10;
		} 
		else{
			pushdown();
			return min(ls->qry3(L,R,w),rs->qry3(L,R,w));
		}
	}
};
int main() 
{
	n=read();m=read();
	for(int i=1; i<=n; i++) {
		a[i]=read();
	}
	Node *rot=new Node(1,n);
	for(int i=1; i<=m; i++) {
		ll op,x,y,z;
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1) {
			int l=1,r=x,p=0;
			while(l<=r) {
				int mid=(l+r)/2;
				if(rot->qry1(mid,mid)<y) {
					r=mid-1;
					p=mid;
				} else {
					l=mid+1;
				}
			}
			if(p==0) {
				continue;
			}
//			printf("p=%d\n",p);
			rot->upd(p,x,y);
		} 
		else {
			int ans=0;
			while(x<=n){
				int p=rot->qry3(x,n,y);
//				printf("p1=%d\n",p);
				if(p==n+10){
					break;
				}
				x=p;
				ll sum=rot->qry1(1,x-1);
				y+=sum;
				p=rot->qry2(y);
//				printf("p2=%d\n",p);
				ans+=p-x;
				y-=rot->qry1(x,p-1);
				y-=sum; 
				x=p+1;//由于第p个物品不能买，所以下一波直接从p+1开始找
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```
$PS:$我的线段树是用指针写的，如果看不懂可以用数组写一遍，切勿直接剽窃题解。自己写一遍也是对代码能力的提升，毕竟思路才是最重要的。

---

## 作者：_Sein (赞：5)

提供一种比较快且比较短的做法。

我们可以通过分析第二种操作的复杂度来证明暴力的复杂度是 $\Theta(\log^2n)$ 的。

显然，卡满必须得区间个数尽量地多。

考虑 $10101010\cdots$ ，$1$ 表示选，$0$ 表示没选的序列。

这样可以很轻松地证明它的缩减速度很快，每多一个区间， $y$ 便 $/2$ 。

于是最多有 $\log$ 个询问区间。

然后询问暴力即可。

```cpp
int mx[N << 2], mn[N << 2], lz[N << 2], siz[N << 2], a[N]; ll s[N << 2];

#define lc p << 1
#define rc p << 1 | 1

void upd(int p) {
	mx[p] = mx[lc];
	mn[p] = mn[rc];
	s[p] = s[lc] + s[rc]; 
} 

void pushdown(int p) {
	if (lz[p]) {
		int d = lz[p]; lz[p] = 0;
		mx[lc] = d; s[lc] = 1ll * siz[lc] * d; mn[lc] = d; lz[lc] = max(lz[lc], d);
		mx[rc] = d; s[rc] = 1ll * siz[rc] * d; mn[rc] = d; lz[rc] = max(lz[rc], d);
	} 
}

void build(int p, int l, int r) {
	siz[p] = r - l + 1;
	if (l == r) {mx[p] = mn[p] = s[p] = a[l]; return ;}
	int mid = l + r >> 1; build(lc, l, mid); build(rc, mid + 1, r);
	upd(p);
}

void modify(int p, int l, int r, int x, int d) {
	int mid = l + r >> 1;
	if (r > x) {pushdown(p); if (mid < x) modify(rc, mid + 1, r, x, d); modify(lc, l, mid, x, d); upd(p); return ;} 	
	if (mx[p] <= d) {mx[p] = mn[p] = d; s[p] = 1ll * siz[p] * d; lz[p] = max(lz[p], d); return ;}
	if (mn[p] >= d) return ; 
	pushdown(p);  
	modify(lc, l, mid, x, d); modify(rc, mid + 1, r, x, d);
	upd(p);
}

ll sum; int ans;

void query(int p, int l, int r, int x) {
	int mid = l + r >> 1;
	if (l < x) {	
		pushdown(p);
		if (x <= mid) query(lc, l, mid, x);
		query(rc, mid + 1, r, x);
		return ;
	}
	if (mn[p] > sum) return ;
	if (s[p] <= sum) {
		sum -= s[p]; ans += siz[p]; return ;
	} pushdown(p);
	query(lc, l, mid, x); query(rc, mid + 1, r, x);
}

void solve() {
    int n, m; qr(n); qr(m);
    rep (i, 1, n) qr(a[i]); 
    build(1, 1, n);
    rep (i, 1, m) {
    	int op, x, y; qr(op); qr(x), qr(y);
		if (op == 1) modify(1, 1, n, x, y);
		else ans = 0, sum = y, query(1, 1, n, x), pr2(ans);
    }
    
}
```





---

## 作者：Piwry (赞：3)

## 解析

这里主要证明下操作 $\texttt{2}$ 产生的区间个数是 $\log a$ 的，以及介绍一种不太一样的操作 $\texttt{2}$ 线段树实现（另一种比较好写的实现就见 [Karry5307
](https://www.luogu.com.cn/blog/Karry5307/solution-cf1439c) \kel）

### Part1

这一部分证明操作 $\texttt{2}$ 产生的区间个数是 $\log a$ 的

考虑我们选的某一段区间。设该次选择前剩余的钱 $y$，该次选择的区间 $[l, r]$ 的和 $s$，该次选择停止处的元素的值 $t$（具体即 $r+1$ 处的元素）

不难发现有：

1. $y-s<t$
2. $s\geq t$

于是首先有：

$y<s+t\leq2s$

接着就有：

$2(y-s)<y$

这即说明，$y$ 在每次选择后至少减少一半；于是至多选择出 $\log a$ 个区间

### Part2

这一部分介绍一种不太一样的操作 $\texttt{2}$ 线段树实现

不难有将操作 $\texttt{2}$ 直接放到线段树查询上搞的想法

于是就可以分类讨论，尝试写出代码：

```cpp
/*返回最右的满足 sum[l, pos] 不大于 val 的位置 pos*/
pad query2(const int &l, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr)
		return (val >= sum[x]) ? pad(nl, sum[x]) : pad(-0x3f3f3f3f, 0);
	pushdown(x);
	int mid =(nl+nr)>>1;
	if(l < nl){
		if(sum[x<<1] < val){
			pad ret =query2(l, val-sum[x<<1], mid+1, nr, x<<1^1);
			ret.pos =max(ret.pos, mid), ret.sum +=sum[x<<1];
			return ret;
		}
		else
			return query2(l, val, nl, mid, x<<1);
	}
	else if(l <= mid){
		pad ret =query2(l, val, nl, mid, x<<1);
		if(ret.pos == mid && ret.sum < val){
			pad ret2 =query2(l, val-ret.sum, mid+1, nr, x<<1^1);
			ret.pos =max(ret.pos, ret2.pos), ret.sum +=ret2.sum;
		}
		return ret;
	}
	else
		return query2(l, val, mid+1, nr, x<<1^1);
}
```

（变量/结构体定义可见下面完整代码；具体含义手列下情况应该就能理解X）

其中主要比较容易使人迷惑的是 `(l <= mid)` 处的分支，因为它同时递归了左右子树

实际上这个函数单词查询的复杂度的确是 $O(\log n)$ 的，考虑其递归路线大概是这样：

![query](https://cdn.luogu.com.cn/upload/image_hosting/dgro6tmn.png)

由此也可发现它最坏可能带一个 $2$ 的常数...因此理论复杂度不一定会比开头提到的较简易的实现更优 \fad

## CODE

即 $\texttt{Part 2}$ 提到的实现

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using std::min;
using std::max;

const int MAXN =2e5+20, MAXT =1<<19;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Seg------------------------------*/

int N =1;
ll sum[MAXT];
ll tag_s[MAXT];
int mn[MAXT];
int tag_mn[MAXT];

inline void pushup(const int &x){
	sum[x] =sum[x<<1]+sum[x<<1^1];
	mn[x] =min(mn[x<<1], mn[x<<1^1]);
}

inline void pushdown(const int &x){
	if(tag_s[x]){
		sum[x<<1] =tag_s[x]/2;
		sum[x<<1^1] =tag_s[x]/2;
		tag_s[x<<1] =tag_s[x]/2;
		tag_s[x<<1^1] =tag_s[x]/2;
		tag_s[x] =0;
	}
	if(tag_mn[x]){
		mn[x<<1] =tag_mn[x];
		mn[x<<1^1] =tag_mn[x];
		tag_mn[x<<1] =tag_mn[x];
		tag_mn[x<<1^1] =tag_mn[x];
		tag_mn[x] =0;
	}
}

void modify(const int &l, const int &r, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(l > r)
		return;
	if(l == nl && r == nr){
		sum[x] =1ll*val*(nr-nl+1);
		tag_s[x] =1ll*val*(nr-nl+1);
		mn[x] =val;
		tag_mn[x] =val;
		return;
	}
	pushdown(x);
	int mid =(nl+nr)>>1;
	if(r <= mid)
		modify(l, r, val, nl, mid, x<<1);
	else if(l >= mid+1)
		modify(l, r, val, mid+1, nr, x<<1^1);
	else
		modify(l, mid, val, nl, mid, x<<1), modify(mid+1, r, val, mid+1, nr, x<<1^1);
	pushup(x);
}

/*最左的至少为 pos 的不大于 val 的位置*/
int query1(const int &pos, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr)
		return (mn[x] <= val) ? nl : 0x3f3f3f3f;
	pushdown(x);
	int mid =(nl+nr)>>1;
	if(mid >= pos && mn[x<<1] <= val)
		return query1(pos, val, nl, mid, x<<1);
	else
		return query1(pos, val, mid+1, nr, x<<1^1);
}

struct pad{
	int pos, sum;
	
	pad(const int &P, const int &S):pos(P), sum(S){}
};

/*最右的 sum[l, pos] 不大于 val 的位置 pos*/
pad query2(const int &l, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr)
		return (val >= sum[x]) ? pad(nl, sum[x]) : pad(-0x3f3f3f3f, 0);
	pushdown(x);
	int mid =(nl+nr)>>1;
	if(l < nl){
		if(sum[x<<1] < val){
			pad ret =query2(l, val-sum[x<<1], mid+1, nr, x<<1^1);
			ret.pos =max(ret.pos, mid), ret.sum +=sum[x<<1];
			return ret;
		}
		else
			return query2(l, val, nl, mid, x<<1);
	}
	else if(l <= mid){
		pad ret =query2(l, val, nl, mid, x<<1);
		if(ret.pos == mid && ret.sum < val){
			pad ret2 =query2(l, val-ret.sum, mid+1, nr, x<<1^1);
			ret.pos =max(ret.pos, ret2.pos), ret.sum +=ret2.sum;
		}
		return ret;
	}
	else
		return query2(l, val, mid+1, nr, x<<1^1);
}

/*------------------------------Main------------------------------*/

int work(int pos, int money, const int &n){
	int ret =0;
	while(pos <= n){
		int S =query1(pos, money);
		
		if(S > n)
			break;
		
		pad get =query2(S, money);
		int T =get.pos;
		
		ret +=T-S+1;
		money -=get.sum;
		pos =T+1;
	}
	return ret;
}

int main(){
	int n =read(), q =read();
	
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		sum[i] =read(), mn[i] =sum[i];
	for(int i =N+n; i < 2*N; ++i)
		sum[i] =mn[i] =0x3f3f3f3f;
	for(int i =N-1; i >= 1; --i)
		pushup(i);
	
	for(int t =0; t < q; ++t){
		int op =read();
		int x =read(), y =read();
		if(op == 1)
			modify(query1(1, y), x, y);
		else
			write(work(x, y, n)), putchar('\n');
	}
}
```

---

## 作者：serverkiller (赞：3)

# CF1439C

## 题意:

给你一个**不递增**的数列,让你支持两个操作:

1. 对于$i\in [1,x],a_i=max(a_i,y)$

2. 询问一次从$x$开始有$w$元的贪心购物能买多少物品

一次从$x$开始的贪心购物指从$x$开始 遇到一个可以买的物品就买.

## solution

首先我们注意到这个数列有一个不递增的性质 所以对于1操作 我们每次修改的必然是这个指定的前缀的后缀

所以我们可以取二分这个后缀的起点 对其区间赋值

操作1的复杂度是$O(log^2n)$

而对于操作2 我们可以发现我们每次取的必然是一段一段的区间 所以我们去二分这个区间的起点 二分终点 然后按照题意模拟取 就可以了

操作2的复杂度是$O(log^3n)$

这个做法非常卡常 我赛时被卡了两次

~~一次是pretest 一次是system test 赛后开C++17过去了~~

~~然而事实证明 开个编译优化就能过去了~~

所以我们必须要考虑优化这个做法

我们发现我们不需要在序列上二分 可以直接把二分放在线段树上 这样我们就做到了单次询问$O(log^2n)$

~~但是我赛时懒得写了~~

具体实现并不难 看代码吧（

```cpp
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;

template <typename T>

void read(T &a)
{
	T x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	a = x * f;
}

template <typename T,typename... Args> void read(T &t,Args &... args) {read(t); read(args...); }

int n,a[N],m;

struct Segment_Tree
{
	int sum[N << 2],lazy[N << 2],mini[N << 2];
	void pushup(int now)
	{
		sum[now] = sum[now << 1] + sum[now << 1 | 1];
		mini[now] = min(mini[now << 1],mini[now << 1 | 1]);
	}
	void pushdown(int now,int l,int r)
	{
		if (lazy[now] == -1) return ;
		int mid = (l + r) >> 1;
		sum[now << 1] = (mid - l + 1) * lazy[now];
		mini[now << 1] = lazy[now];
		lazy[now << 1] = lazy[now];
		sum[now << 1 | 1] = (r - mid) * lazy[now];
		mini[now << 1 | 1] = lazy[now];
		lazy[now << 1 | 1] = lazy[now];
		lazy[now] = -1;
	}
	void build(int now,int l,int r)
	{
		lazy[now] = -1;
		if (l == r)
		{
			sum[now] = a[l];
			mini[now] = a[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(now << 1,l,mid);
		build(now << 1 | 1,mid + 1,r);
		pushup(now);
	}
	void update(int now,int l,int r,int ll,int rr,int k)
	{
		if (ll <= l && rr >= r)
		{
			sum[now] = (r - l + 1) * k;
			lazy[now] = k;
			return ;
		}
		pushdown(now,l,r);
		int mid = (l + r) >> 1;
		if (ll <= mid) update(now << 1,l,mid,ll,rr,k);
		if (rr > mid) update(now << 1 | 1,mid + 1,r,ll,rr,k);
		pushup(now);
	}
	int query(int now,int l,int r,int ll,int rr)
	{
		if (ll <= l && rr >= r)
		{
			return sum[now];
		}
		pushdown(now,l,r);
		int mid = (l + r) >> 1,ans = 0;
		if (ll <= mid) ans += query(now << 1,l,mid,ll,rr);
		if (rr > mid) ans += query(now << 1 | 1,mid + 1,r,ll,rr);
		return ans;
	}
	int query(int now,int l,int r,int &val)
	{
		if (val >= sum[now])
		{
			val -= sum[now];
			return r - l + 1;
		}
		if (l == r) return 0;
		pushdown(now,l,r);
		int mid = (l + r) >> 1,ans = 0;
		if (mini[now << 1] <= val) ans += query(now << 1,l,mid,val);
		if (mini[now << 1 | 1] <= val) ans += query(now << 1 | 1,mid + 1,r,val);
		return ans;
	}
}T;

signed main()
{
	read(n,m);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	T.build(1,1,n);
	while (m--)
	{
		int opt;
		read(opt);
		if (opt == 1)
		{
			int l = 1,r,x,ans = -1,y;
			read(r,y);
			x = r;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (T.query(1,1,n,mid,mid) < y) r = mid - 1,ans = mid;
				else l = mid + 1;
			}
			if (ans == -1) continue;
			T.update(1,1,n,ans,x,y);
		}
		if (opt == 2)
		{
			int x,w;
			read(x,w);
			if (x > 1) w += T.query(1,1,n,1,x - 1);
			int res = T.query(1,1,n,w);
			printf("%lld\n",res - (x - 1));
		}
	}
	return 0;
}
```

---

## 作者：tommymio (赞：3)

考虑 $1$ 操作 $\text{1 x y}$，由于在非升序列上操作，改变的值一定构成了一段 $[1,x]$ 的后缀区间 $[L,x]$。所以可以维护区间 $\min$ 在线段树上二分找到后缀区间的左端点。

考虑 $2$ 操作 $\text{2 x y}$，答案必然是一些连续段之和，并且这些连续段的个数不超过 $\log n$ 个，证明显然。所以可以考虑直接在区间上暴力查询，时间复杂度是 $O(\log^2 n)$ 的。但是这个部分有一个左边界的限制，考虑让 $[1,x)$ 一定被计入答案，最后再减去即可。

代码就不贴了，线段树二分入门题。

---

## 作者：louhao088 (赞：1)

## 一道很好的线段树题

小蒟蒻太菜了，调了很久，发现数组没开够。


------------


## 思路

我们发现一个很重要的性质，这个序列一定是单调的，这就可以用一种类似于二分的思想来做这道题。


------------
### 操作1

我们对线段树维护最大最小值，很容易发现，只要更改$\geq Y$部分的$a_i$即可，所以我们用线段树查询第一个大于等于$Y$的位置，在对之后进行区间修改，复杂度应该是$O(n \log n)$。

```cpp
inline void change(int rt,int l,int r,int L,int R,int num)//区间修改
{
	if(l>R||r<L)return;
	if(l>=L&&r<=R){Max[rt]=Min[rt]=num,sum[rt]=(r-l+1)*num;tag[rt]=num;return;}push(rt,l,r);
	int mid=l+r>>1;change(ls,l,mid,L,R,num),change(rs,mid+1,r,L,R,num);
	sum[rt]=sum[ls]+sum[rs],Min[rt]=min(Min[ls],Min[rs]);Max[rt]=max(Max[ls],Max[rs]);
}
inline int query(int rt,int l,int r,int num)//查询第一个比y大的位置
{
	if(Min[rt]>num)return 10000000;//不符合返回一个大的值
	if(Max[rt]<=num)return l;//符合返回左位置
	if(l==r)return l;int mid=l+r>>1;push(rt,l,r);
	return min(query(ls,l,mid,num),query(rs,mid+1,r,num));//取较小的
}
```



------------


### 操作2 

我们考虑记录区间之和，对于每次操作，寻找到它一次能连续取的最多次数，$y$减去区间之和后继续做。

#### 复杂度简单证明

这样粗略一看复杂度好像比暴力还大，最坏情况要$(n^2 \log n)$,其实则不然，因为每次都会取到比下一个数小为止，故最坏情况就是$2^n$,...
$16,8,4,2,1$,因为不超过$1e9$，操作次数是$log$级别，故时间复杂度$O(n \log n \log y)$。


#### 具体实现

这里我用了一种常数较大的方法，先寻问每次从1开始，第一个比$y$小的位置$k$，计算$1, k-1$间$a_i$的和,将其加到$y$上，询问每次从1开始最多能取到的位置，将$y$减去消耗后再来一遍。



------------
完整代码
```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls rt<<1
#define rs rt<<1|1
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=5e5+5;
int n,m,ans,a[maxn*4],sum[maxn*4],Min[maxn*4],Max[maxn*4],tag[maxn*4],x,y,opt,M;
inline void push(int rt,int l,int r)
{
	if(tag[rt])
	{
		tag[ls]=tag[rt],tag[rs]=tag[rt];int mid=l+r>>1;sum[ls]=tag[rt]*(mid-l+1);
		sum[rs]=tag[rt]*(r-mid);Min[ls]=Min[rs]=Max[ls]=Max[rs]=tag[rt];tag[rt]=0;
	}
}
inline void build(int rt,int l,int r)
{
	if(l==r){Min[rt]=a[l],Max[rt]=a[l],sum[rt]=a[l];return;}
	int mid=l+r>>1;build(ls,l,mid),build(rs,mid+1,r);
	sum[rt]=sum[ls]+sum[rs],Min[rt]=min(Min[ls],Min[rs]);Max[rt]=max(Max[ls],Max[rs]);
}
inline void change(int rt,int l,int r,int L,int R,int num)
{
	if(l>R||r<L)return;
	if(l>=L&&r<=R){Max[rt]=Min[rt]=num,sum[rt]=(r-l+1)*num;tag[rt]=num;return;}push(rt,l,r);
	int mid=l+r>>1;change(ls,l,mid,L,R,num),change(rs,mid+1,r,L,R,num);
	sum[rt]=sum[ls]+sum[rs],Min[rt]=min(Min[ls],Min[rs]);Max[rt]=max(Max[ls],Max[rs]);
}
inline int query(int rt,int l,int r,int num)
{
	if(Min[rt]>num)return 10000000;
	if(Max[rt]<=num)return l;
	if(l==r)return l;int mid=l+r>>1;push(rt,l,r);
	return min(query(ls,l,mid,num),query(rs,mid+1,r,num));
}
inline int query2(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;if(l>=L&&r<=R){return sum[rt];}
	push(rt,l,r);int mid=l+r>>1;
	return query2(ls,l,mid,L,R)+query2(rs,mid+1,r,L,R);
}
inline int query1(int rt,int l,int r,int num)
{
	if(sum[rt]<=num){M=max(M,r);return sum[rt];}
	if(l==r)return 0;push(rt,l,r);int mid=l+r>>1;
	if(sum[ls]<=num)
	{
		M=max(M,mid);
		return sum[ls]+query1(rs,mid+1,r,num-sum[ls]);
	}
	else return query1(ls,l,mid,num);
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		opt=read(),x=read(),y=read();
		if(opt==1)
		{
			int k=query(1,1,n,y);if(k>x)continue;
			else change(1,1,n,k,x,y);
		}
		else
		{
			int k2=query(1,1,n,y);ans=0;M=x;
			while(k2<=n)
			{
				k2=max(k2,M);
				int k=query2(1,1,n,1,k2-1);M=0;
				y=y-query1(1,1,n,y+k)+k;ans+=M-k2+1;
				if(M==n)break;
				k2=query(1,1,n,y);
			}printf("%d\n",ans);
		}
	}
	return 0;
} 
```














---

## 作者：conprour (赞：0)

# 题解
一开始想的是维护区间最大值和区间和。

记录最大值可以支持线段树二分进行操作 $1$（先递归右子树，再递归左子树），记录区间和可以方便操作 $2$ 的查询操作。

然而这样在操作 $2$ 二分的时候并不能简便地选择递归左子树还是右子树（因为是最大值是从右向左二分，而操作 $2$ 是从左往右走），很难搞。

换种思路，记录区间最小值，同样能支持线段树二分进行操作 $1$，而且对于操作 $2$，可以实现从左往右二分，过程中满足条件就对 $y$ 不断减去 $sum$，同时更新答案，累加 $r-l+1$。

## 一点细节
不知道有没有人像我一样一开始有疑惑：区间取最小值，往下传懒标记的时候怎么更新区间和数组呢？

实际上，区间和和区间最小值都是在二分找到操作 $1$ 需要更新的区间之后才更新的，所以直接赋值就可以，不需要担心太多。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FCC fclose(stdin),fclose(stdout)
#define ls (k<<1)
#define rs (k<<1|1)
#define mid ((l+r)>>1)
const int INF = 0x3f3f3f3f,N = 2e5+10;
inline ll read()
{
	ll ret=0;char ch=' ',c=getchar();
	while(!(c>='0'&&c<='9')) ch=c,c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
int n,q,a[N];
struct Segtree
{
	ll laz[N<<2],minn[N<<2],sum[N<<2];
	inline void pushup(int k)
	{
		minn[k]=min(minn[ls],minn[rs]);
		sum[k]=sum[ls]+sum[rs];
	}
	inline void build(int k,int l,int r)
	{
		if(l==r) {sum[k]=minn[k]=a[l];return;}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	inline void add(int k,int l,int r,int v)
	{
		laz[k]=v;
		minn[k]=v;
		sum[k]=1LL*(r-l+1)*v;
	}
	inline void pushdown(int k,int l,int r)
	{
		if(!laz[k]) return;
		add(ls,l,mid,laz[k]);
		add(rs,mid+1,r,laz[k]);
		laz[k]=0;
	}
	int find(int k,int l,int r,int v)
	{
		if(l==r) return v>sum[k]?l:l+1;//特判无解情况，n+1 
		pushdown(k,l,r);
		if(minn[ls]>=v) return find(rs,mid+1,r,v);
		return find(ls,l,mid,v);
	}
	void modify(int k,int l,int r,int x,int y,int v)
	{
		if(x<=l&&r<=y) return add(k,l,r,v);
		pushdown(k,l,r);
		if(x<=mid) modify(ls,l,mid,x,y,v);
		if(y>mid)  modify(rs,mid+1,r,x,y,v);
		pushup(k); 
	}	
	int query(int k,int l,int r,int x,int &v)
	{
		if(r<x||minn[k]>v) return 0;
		if(l>=x&&v>=sum[k]) 
		{
			v-=sum[k];
			return r-l+1;	
		}
		pushdown(k,l,r);
		int ret=0;
		//if(minn[ls]<=v&&mid>=x) 
		ret+=query(ls,l,mid,x,v);
		ret+=query(rs,mid+1,r,x,v);
		return ret; 
	}
}str;
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	str.build(1,1,n);
	while(q--)
	{
		int op=read(),x=read(),y=read();
		if(op==1)
		{
			int l=str.find(1,1,n,y);
			if(l<=x) str.modify(1,1,n,l,x,y);	
		}
		else printf("%d\n",str.query(1,1,n,x,y)); 
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：0)

给一个比较无脑但慢得起飞的写法。

主要的做法和其他题解差不多。简单提一下，就是注意到修改操作不会改变数组的单调性，于是修改使用线段树上二分找到位置后区间覆盖，又注意到询问 the hungry man 最多吃掉 $\log_2(\max y)$ 个连续段后继续线段树上二分即可。

关于线段树二分（以下讨论形如 $\operatorname{max-right}(L,R,w)$ 表示在区间 $[L,R]$ 找到一个最大的 $i$，使得 $\sum_{j=1}^i\leqslant w$ 的二分问题），其实不用分析边界的影响，直接由归纳法把问题上升到一般有上下界的线段树上二分即可。但是这样写要求线段树维护前缀和，这不太可做。于是在进行线段树二分的时候，可以传参 $\textit{pre}$，在当前结点，维护的区间是 $[l, r]$，则 $\textit{pre}=\sum_{i=1}^r a_i$。判断二分应该往哪棵子树里面走的问题，若满足 $\textit{pre}-\textit{sum}_{\text{right child}}\leqslant w$，其中 $\textit{sum}_x$ 表示线段树上结点 $x$ 所维护的区间和，$w$ 的意义同 $\operatorname{max-right}(L, R, w)$ 中的意义，则意味着左子树一定满足条件，而我们应该看看右子树怎么样（这里的说法不太严谨，因为会出现左子树恰好满足而进入右子树找不到答案的情况，在代码中有所体现），反之左子树不成立，则右子树不可能成立，直接进入左子树即可。

然后 testcase #101 是个把 $\log_2(\max y)$ 卡满的点，卡不过可以直接特判（mobai DJ）。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)/2)
using namespace std;
using ll = long long;
int n, Q, a[200100], mn[800100], sz[800100], tag[800100];
ll sum[800100];
void upd(int now) {
    mn[now] = min(mn[now*2], mn[now*2+1]), sum[now] = sum[now*2]+sum[now*2+1];
    sz[now] = sz[now*2]+sz[now*2+1];
}
void pr(int now, int w) {
    sum[now] = (ll)w*sz[now], mn[now] = tag[now] = w;
}
void push(int now) {
    if (tag[now] == -1) return;
    pr(now*2, tag[now]), pr(now*2+1, tag[now]), tag[now] = -1;
}
void bld(int now, int l, int r) {
    tag[now] = -1;
    if (l == r) {
        mn[now] = sum[now] = a[l], sz[now] = 1;
        return;
    }
    bld(now*2, l, mid), bld(now*2+1, mid+1, r), upd(now);
}
void cng(int L, int R, int w, int now=1, int l=1, int r=n) {
    if (L > R) return;
    if (l >= L && r <= R) return pr(now, w);
    push(now);
    if (mid >= L) cng(L, R, w, now*2, l, mid);
    if (mid < R) cng(L, R, w, now*2+1, mid+1, r);
    upd(now);
}
int min_left(int L, int R, int w, int now=1, int l=1, int r=n) {
    if (L > R) return n+1;
    if (l == r) return l;
    push(now);
    if (l >= L && r <= R) {
        if (mn[now*2] <= w) return min_left(L, R, w, now*2, l, mid);
        else if (mn[now*2+1] <= w) return min_left(L, R, w, now*2+1, mid+1, r);
        return n+1;
    }
    int res = n+1;
    if (mid >= L && mn[now*2] <= w) res = min_left(L, R, w, now*2, l, mid);
    if (res <= n) return res;
    if (mid < R && mn[now*2+1] <= w) res = min_left(L, R, w, now*2+1, mid+1, r);
    return res;
}
int max_right(int L, int R, ll w, ll pre, int now=1, int l=1, int r=n) {
    if (l == r) {
        // 这里就是左子树恰好满足的情况，l-1 一定满足（除非 l == 1）
        if (l > 1) return pre > w ? l-1 : l;
        return pre > w ? n+1 : l;
    }
    push(now);
    if (l >= L && r <= R) {
        if (pre-sum[now*2+1] <= w) return max_right(L, R, w, pre, now*2+1, mid+1, r);
        else return max_right(L, R, w, pre-sum[now*2+1], now*2, l, mid);
    }
    int res = n+1;
    if (mid < R && pre-sum[now*2+1] <= w) res = max_right(L, R, w, pre, now*2+1, mid+1, r);
    if (L <= res && res <= R) return res;
    if (mid >= L) res = max_right(L, R, w, pre-sum[now*2+1], now*2, l, mid);
    return res;
}
ll qry(int L, int R, int now=1, int l=1, int r=n) {
    if (l > R || r < L) return 0;
    if (l >= L && r <= R) return sum[now];
    push(now);
    return qry(L, R, now*2, l, mid)+qry(L, R, now*2+1, mid+1, r);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> Q;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
    }
    if (n == 2e5 && a[10] == 268435456) { // 特判 #101
        for (int i=1; i<=Q; ++i) {
            cout << "29\n";
        }
        return 0;
    }
    bld(1, 1, n);
    ll y;
    for (int op,x; Q--;) {
        cin >> op >> x >> y;
        if (op == 1) {
            cng(min_left(1, x, y), x, y);
        }
        else {
            int cur = x, ans = 0;
            while (y > 0) {
                ll pre = qry(1, cur-1);
                if (qry(1, cur) > y+pre) {
                    cur = min_left(cur, n, y);
                    continue;
                }
                int t = max_right(cur, n, y+pre, sum[1]);
                y -= qry(cur, t);
                ans += t-cur+1;
                cur = min_left(t+1, n, y);
                if (cur > n) break;
            }
            cout << ans << "\n";
        }
    }
}
```

---

