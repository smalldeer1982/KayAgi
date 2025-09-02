# Periodic RMQ Problem

## 题目描述

给你一个整数序列 $a$，你要执行 $q$ 次操作，分两种：

- `1 l r x`：将 $a_l\sim a_r$ 赋值为 $x$。
- `2 l r`：求 $a_l\sim a_r$ 中的最小值。

我们认为这个问题太简单了，所以不直接给出 $a$，而是给出长度为 $n$ 的序列 $b$，将 $b$ 复制 $k$ 份，拼在一起得到 $a$。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,q\le 10^5$，$1\le k\le 10^4$，$1\le l\le r\le n\times k$，$1\le b_i,x\le 10^9$。

## 样例 #1

### 输入

```
3 1
1 2 3
3
2 1 3
1 1 2 4
2 1 3
```

### 输出

```
1
3
```

## 样例 #2

### 输入

```
3 2
1 2 3
5
2 4 4
1 4 4 5
2 4 4
1 1 6 1
2 6 6
```

### 输出

```
1
5
1
```

# 题解

## 作者：Meatherm (赞：21)

Update On 2020.04.16：修正了 LaTeX 和部分语句问题

## 前言

前置知识：线段树及其动态开点，ST 表

## 思路

### 空间复杂度的优化

区间赋值？区间最小值？立刻想到了朴素线段树。但是 $a$ 的长度可能达到 $10^9$，显然不可行。

这个时候就要使用线段树动态开点了。顾名思义，就是要用当前节点的信息时再建立这个节点。

至于线段树数组要开多大？我算过，但是算挂了。为了保证正确，建议在空间限制允许的范围内尽可能地开大（例如 $2\times10^7$）。

### 时间复杂度的优化

空间复杂度满足了，再来考虑时间复杂度。如果直接用  $O(nk\times \log_2(nk))$ 的复杂度建一棵线段树，那么直接 TLE。

考虑不建树，而使用 ST 表对付查询。如果当前区间已经被覆盖，则返回覆盖的值。否则有 $3$ 种情况（注：$l,r$ 下标从 $0$ 开始，不同于一般 ST 表）：

1. 区间的左端点 $l$ 与区间的右端点 $r$ 之差 $≥n$，即 $r-l+1≥n$，这个时候 $[l,r]$ 包含了一个完整的$b$ 序列，所以 $[l,r]$ 中的数一定只包含 $b$ 中的数，这种情况使用 ST 表查询 $b$ 中 $[0,n-1]$ 的最小值即可。

2. $r-l+1≤n$ 且 $\left\lfloor l/n \right\rfloor = \left \lfloor r/n \right\rfloor$。这种情况下， $[l,r]$ 包含 $b$ 中的一段。使用 ST 表查询 $b$ 中 $[l \mod n,r \mod n]$ 最小值即可。

3. $r-l+1≤n$ 且 $\left\lfloor l/n \right\rfloor ≠ \left \lfloor r/n \right\rfloor$。这种情况下，区间 $[l,r]$ 包含 $b$ 中 $[l \mod n,n-1]$ 和 $[0,r\mod n]$ 两段。这种情况下答案为两段最小值的最小值。

这个时候时间复杂度已经降低到$O(q\times \log_2(nk))$，可以通过本题。

## 代码

这里给出博主的代码。希望能对您有所帮助。

```
# include <bits/stdc++.h>
# define rr register
const int N=100010,MAXN=20000010;
struct Node{
	int l,r,add,Min;
}tree[MAXN];
int ST[N][30];
int n,k,q;
int root,id;//root是根节点编号 id是给线段树节点标号用的
inline int read(void){//快读
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;		
}
inline int RMQ_ask(int l,int r){//小区间ST表查询
	int len=log2(r-l+1);
	return std::min(ST[l][len],ST[r-(1<<len)+1][len]);
}
inline int Ask(int l,int r){//大区间ST表查询
	if(r-l+1>=n){
		return RMQ_ask(0,n-1);
	}
	if(l/n==r/n){
		return RMQ_ask(l%n,r%n);
	}
	return std::min(RMQ_ask(l%n,n-1),RMQ_ask(0,r%n));
}
inline bool make(int &x,int l,int r){//开点
	if(x)
		return false;
	x=++id;
	tree[x].Min=Ask(l,r);//每一个新节点都是没有标记的（除非父节点会传下来） 于是初始值都是[l,r]的最小值
	return true;
}
inline void Add(int k,int v){//区间赋值操作
	tree[k].add=tree[k].Min=v;
	return;
}
inline void pushdown(int k,int l,int r){//标记下传操作
	int mid=(l+r)>>1;
	make(tree[k].l,l,mid);
	make(tree[k].r,mid+1,r);
	if(!tree[k].add)
		return;
	tree[tree[k].l].add=tree[tree[k].l].Min=tree[tree[k].r].add=tree[tree[k].r].Min=tree[k].add;
	tree[k].add=0;
	return;	
}
void change(int &k,int l,int r,int L,int R,int v){
	make(k,l,r);//进来一次make一次 防止出奇怪的bug
	if(L<=l&&r<=R){
		Add(k,v);
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		change(tree[k].l,l,mid,L,R,v);
	if(mid<R)
		change(tree[k].r,mid+1,r,L,R,v);
	tree[k].Min=std::min(tree[tree[k].l].Min,tree[tree[k].r].Min);
	return;		
}
int ask(int &k,int l,int r,int L,int R){//询问 和普通线段树差不多
	make(k,l,r);
	if(L<=l&&r<=R){
		return tree[k].Min;
	}
	pushdown(k,l,r);
	int res=1e9,mid=(l+r)>>1;
	if(L<=mid)
		res=std::min(res,ask(tree[k].l,l,mid,L,R));
	if(mid<R)
		res=std::min(res,ask(tree[k].r,mid+1,r,L,R));
	return res;	
}
int main(void){
	n=read(),k=read();
	for(rr int i=0;i<n;++i)//从零开始的数组下标
		ST[i][0]=read();
	for(rr int j=1;(1<<j)<=n;++j)
		for(rr int i=0;i+(1<<j)-1<n;++i){
			ST[i][j]=std::min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
		}
	q=read();
	make(root,0,n*k-1);//提前建好root节点
	int sign,l,r,x;
	while(q--){
		sign=read(),l=read(),r=read();
		if(sign==1){//修改
			x=read();
			change(root,0,n*k-1,l-1,r-1,x);
		}
		else printf("%d\n",ask(root,0,n*k-1,l-1,r-1));//查询
	}
	return 0;
}
```

---

## 作者：Limit (赞：15)

# 题目大意

给出一个长度为 $n$ 的序列 $b$,序列 $a$ 又序列 $b$ 复制 $k$ 次后得到,需要支持区间覆盖,区间取 $min$.

# 分析

开始没有想到可以用st表,很自闭.

但是毕竟写出来了,就来分享一个不用st表的做法,这个做法可能比较复杂,如果想要实现更方便的做法可以看看[$\color{red}\sf{M}\color{black}\sf{eatherm}$](https://www.luogu.com.cn/user/108949)神仙的[题解](https://www.luogu.com.cn/blog/Meatherm/solution-cf803g).

可以发现如果暴力建树的复杂度是 $\mathcal{O}(nk\log_2nk)$ 显然会 $T$,开始的时候每连续 $n$ 个都是相同的,所以考虑建 $k$ 颗树,每颗树就是一个块,开始时都和初始树(用 $b$ 建成的树)相同.

当然这里需要动态开点.

然后是修改操作,考虑将修改部分变成三段,分别为左端点所在的块,右端点所在的块,中间的块,然后对于每一段进行修改.

1.  对于左右的块,直接在左右块对于的线段树上修改就可以了
2.  对于中间的块,显然不可以暴力修改,那么考虑再用一颗线段树维护

然后是查询操作,仍然将它分成三段来查询,和修改的方式差不多.

但是在查询左右块时需要查询左右快是否被覆盖,如果被覆盖那么在维护所有块的线段树中将这个标记去掉,再进行全局覆盖.

时间复杂度 $\mathcal{O}(m(log_2n+log_2k))$.

这就是线段树优化分块吗,i了i了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=1e5+7;
const int INF=1e9;
int n,m,k;
int arr[MAXN];
int root[MAXN];
int min_num=INF;
namespace All//维护块的线段树
{
	struct LazyTag//有覆盖标记
	{
		int if_cover;
		int cover;
		void Clean()
		{
			if_cover=0;
		}
	}for_make;
	LazyTag MakeTag(int cover)
	{
		for_make.if_cover=1;
		for_make.cover=cover;
		return for_make;
	}
	struct SegmentTree
	{
		int min;//需要维护区间min
		int cover;//需要维护这个位置的块是否被覆盖
		LazyTag tag;
	}sgt[MAXN*4];
	#define LSON (now<<1)
	#define RSON (now<<1|1)
	#define MIDDLE ((left+right)>>1)
	#define LEFT LSON,left,MIDDLE
	#define RIGHT RSON,MIDDLE+1,right
	#define NOW now_left,now_right
	void PushUp(int now)//合并区间min
	{
		sgt[now].min=min(sgt[LSON].min,sgt[RSON].min);
	}
	void Build(int now=1,int left=1,int right=k)//建树
	{
		if(left==right)
		{
			sgt[now].min=min_num;//开始都是区间中的最小数
			sgt[now].cover=0;
			return;
		}
		Build(LEFT);
		Build(RIGHT);
		PushUp(now);
	}
	void Down(LazyTag tag,int now)//修改
	{
		if(!tag.if_cover)
		{
			return;
		}
		sgt[now].tag.if_cover=1;//有覆盖表紧
		sgt[now].tag.cover=tag.cover;
		sgt[now].min=sgt[now].cover=tag.cover;//区间min和覆盖都赋值为cover
	}
	void PushDown(int now)//下传标记
	{
		Down(sgt[now].tag,LSON);
		Down(sgt[now].tag,RSON);
		sgt[now].tag.Clean();
	}
	void Cover(int now_left,int now_right,int cover,int now=1,int left=1,int right=k)//区间覆盖
	{
		if(now_right<left||right<now_left)
		{
			return;
		}
		if(now_left<=left&&right<=now_right)
		{
			Down(MakeTag(cover),now);
			return;
		}
		PushDown(now);
		Cover(NOW,cover,LEFT);
		Cover(NOW,cover,RIGHT);
		PushUp(now);
	}
	void UpdataMin(int place,int min,int now=1,int left=1,int right=k)//单点修改最小值,在左右块被修改后最小值也可能会发生改变
	{
		if(place<left||right<place)
		{
			return;
		}
		if(left==right)
		{
			sgt[now].min=min;
			return;
		}
		PushDown(now);
		UpdataMin(place,min,LEFT);
		UpdataMin(place,min,RIGHT);
		PushUp(now);
	}
	int QueryMin(int now_left,int now_right,int now=1,int left=1,int right=k)//查询区间min
	{
		if(now_right<left||right<now_left)
		{
			return INF;
		}
		if(now_left<=left&&right<=now_right)
		{
			return sgt[now].min;
		}
		PushDown(now);
		int result=min(QueryMin(NOW,LEFT),QueryMin(NOW,RIGHT));
		return result;
	}
	int Query(int place,int now=1,int left=1,int right=k)//单点查询这个块是否被覆盖
	{
		if(place<left||right<place)
		{
			return 0;
		}
		if(left==right)
		{
			int result=sgt[now].cover;
			sgt[now].cover=0;//相当于下传,所以需要清空
			return result;
		}
		PushDown(now);
		return Query(place,LEFT)+Query(place,RIGHT);
	}
	#undef LSON
	#undef RSON
	#undef MIDDLE
	#undef LEFT
	#undef RIGHT
	#undef NOW
}
namespace Range//维护区间的线段树
{
	int first_tree=0;//表示编号小于first_tree的节点为初始线段树上的
	struct LazyTag
	{
		int if_cover;
		int cover;
		void Clean()
		{
			if_cover=0;
		}
	}for_make;
	LazyTag MakeTag(int cover)
	{
		for_make.if_cover=1;
		for_make.cover=cover;
		return for_make;
	}
	struct SegmentTree
	{
		int min;
		int lson,rson;
		LazyTag tag;
	}sgt[MAXN*64];
	int sgt_cnt=0;
	#define LSON sgt[now].lson
	#define RSON sgt[now].rson
	#define MIDDLE ((left+right)>>1)
	#define LEFT LSON,left,MIDDLE
	#define RIGHT RSON,MIDDLE+1,right
	#define NOW now_left,now_right
	void PushUp(int now)
	{
		sgt[now].min=min(sgt[LSON].min,sgt[RSON].min);
	}
	void Build(int &now,int left=1,int right=n)//建树
	{
		now=++sgt_cnt;
		if(left==right)
		{
			sgt[now].min=arr[left];
			return;
		}
		Build(LEFT);
		Build(RIGHT);
		PushUp(now);
		if(left==1&&right==n)
		{
			first_tree=sgt_cnt;
		}
	}
	void Down(LazyTag tag,int &now)
	{
		if(!tag.if_cover)
		{
			return;
		}
		if(now<first_tree)//如果当前节点在初始线段树上那么就新建一个节点,需要将左右子节点也赋值过来
		{
			sgt[++sgt_cnt].lson=sgt[now].lson;
			sgt[sgt_cnt].rson=sgt[now].rson;
			now=sgt_cnt;
		}
		sgt[now].min=tag.cover;
		sgt[now].tag.if_cover=1;
		sgt[now].tag.cover=tag.cover;
	}
	void PushDown(int now)
	{
		Down(sgt[now].tag,LSON);
		Down(sgt[now].tag,RSON);
		sgt[now].tag.Clean();
	}
	void Cover(int now_left,int now_right,int cover,int &now,int left=1,int right=n)
	{
		if(now_right<left||right<now_left)
		{
			return;
		}
		if(now<first_tree)//同理建新节点
		{
			sgt[++sgt_cnt].lson=sgt[now].lson;
			sgt[sgt_cnt].rson=sgt[now].rson;
			now=sgt_cnt;
		}
		if(now_left<=left&&right<=now_right)
		{
			Down(MakeTag(cover),now);
			return;
		}
		PushDown(now);
		Cover(NOW,cover,LEFT);
		Cover(NOW,cover,RIGHT);
		PushUp(now);
	}
	int QueryMin(int now_left,int now_right,int now,int left=1,int right=n)//区间取min
	{
		if(now_right<left||right<now_left)
		{
			return INF;
		}
		if(now_left<=left&&right<=now_right)
		{
			return sgt[now].min;
		}
		PushDown(now);
		return min(QueryMin(NOW,LEFT),QueryMin(NOW,RIGHT));
	}
	#undef LSON
	#undef RSON
	#undef MIDDLE
	#undef LEFT
	#undef RIGHT
	#undef NOW
}
int main()
{
	scanf("%d%d",&n,&k);
	REP(i,1,n)
	{
		scanf("%d",&arr[i]);
		min_num=min(min_num,arr[i]);
	}
	Range::Build(root[0]);
	All::Build();
	REP(i,1,k)
	{
		root[i]=root[0];
	}
	scanf("%d",&m);
	int opt,l,r,x;
	int l_,r_;
	int l_c,r_c;
	int answer=0;
	REP(i,1,m)
	{
		scanf("%d%d%d",&opt,&l,&r);
		l_=l/n+(bool)(l%n);//l和r所在块的编号
		r_=r/n+(bool)(r%n);
		if(opt==1)//修改操作
		{
			scanf("%d",&x);
			if(l_+1<=r_-1)//如果中间存在块,那么中间的块赋值为x
			{
				All::Cover(l_+1,r_-1,x);
			}
			l_c=All::Query(l_);//查询左右的块是否被覆盖,如果覆盖那么就直接修改
			if(l_c)
			{
				Range::Cover(1,n,l_c,root[l_]);
			}
			r_c=All::Query(r_);
			if(r_c)
			{
				Range::Cover(1,n,r_c,root[r_]);
			}
			if(l_^r_)//如果左右所在不同
			{
                //可以画个图理解一下
				Range::Cover(l-(l_-1)*n,n,x,root[l_]);
				Range::Cover(1,r-(r_-1)*n,x,root[r_]);
			}
			else//如果在同一个快
			{
				Range::Cover(l-(l_-1)*n,r-(r_-1)*n,x,root[l_]);
			}
            //在左右的块中修改
			All::UpdataMin(l_,Range::QueryMin(1,n,root[l_]));
			All::UpdataMin(r_,Range::QueryMin(1,n,root[r_]));
		}
		if(opt==2)
		{
			answer=INF;
			if(l_+1<=r_-1)//如果中间有快那么查询中间快的min
			{
				answer=All::QueryMin(l_+1,r_-1);
			}
			l_c=All::Query(l_);
			if(l_c)//和修改部分同理
			{
				Range::Cover(1,n,l_c,root[l_]);
			}
			r_c=All::Query(r_);
			if(r_c)
			{
				Range::Cover(1,n,r_c,root[r_]);
			}
			if(l_^r_)//查询也需要分类讨论
			{
				answer=min(answer,min(Range::QueryMin(l-(l_-1)*n,n,root[l_]),Range::QueryMin(1,r-(r_-1)*n,root[r_])));
			}
			else
			{
				answer=min(answer,Range::QueryMin(l-(l_-1)*n,r-(r_-1)*n,root[l_]));
			}
			printf("%d\n",answer);
		}
	}
	return 0;
}
```

---

## 作者：ZCETHAN (赞：10)

[CF803G Periodic RMQ Problem](https://codeforces.com/problemset/problem/803/G)

## 题目大意
给你一个序列 $a$，序列 $b$ 是 $a$ 重复拼接 $k$ 次后的结果。现要你实现区间赋值区间最值。

## Solution
一道氵黑吧，CF 只有 *2300。

首先考虑维护，一个非常简单的线段树，基操了。

但是这道题唯一的困难之处就是无法在拼接后的长度为 $10^9$ 的序列中用线段树。

然后我们发现询问只有 $10^5$ 个，于是我们考虑放弃掉一些无用的数据。

第一个想到的应该是只保留每次询问和修改的两个端点。想做到这样并不难，先离线询问，然后我们对每一对 $l,r$ 离散化一下，那就只有 $2\times Q$ 个点，然后我们对于这 $2\times Q$ 个点来做线段树，仿佛非常可行的鸭子。

但是我们来考虑这样一个情况：
```
5 3
5 6 2 3 6
3
2 1 5
1 2 3 4
2 1 5
```
好我们按照刚才的想法，保留下来的点是 $5\;6\;2\;6$。然后执行第一个询问结果是 $2$ 没错，执行赋值后区间变成了 $5\;4\;4\;6$ 于是我们回答下一个询问的答案是 $4$ 而我们希望的答案是 $3$。

原因就是，我们在保留的时候却丢失了 $3$ 的信息，于是我们联想到，在我们上面保留的点的基础上，相邻两个已经保留的点之间的最小值也是需要的（但不需要整段的信息，因为不会有询问只询问这一段的一半，或者是修改一半，不然这一段就会被分成两段甚至更多），所以在上面的基础之上，我们把相邻两个点之间的最小值也插入进去做线段树就没问题了。

所以空间要开 $4$ 倍以上![](\https://啧.tk/kk)别问问就是 RE 人。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=5e5+10;
struct Tree{
	int l,r;
	ll mn,inc;
}tr[MAXN<<2];
#define ls i<<1
#define rs i<<1|1
ll b[MAXN];
void pushup(int i){
	tr[i].mn=min(tr[ls].mn,tr[rs].mn);
}
void build(int i,int l,int r){
	tr[i].l=l;tr[i].r=r;tr[i].inc=-1;
	if(l==r){tr[i].mn=b[l];return;}
	int mid=l+r>>1;build(ls,l,mid);build(rs,mid+1,r);
	pushup(i);
}
void cov(int i,ll v){
	tr[i].mn=v;tr[i].inc=v;
}
void pushdown(int i){
	if(tr[i].inc==-1) return;
	cov(ls,tr[i].inc);
	cov(rs,tr[i].inc);
	tr[i].inc=-1;
}
void upd(int i,int l,int r,ll v){
	if(tr[i].l>=l&&tr[i].r<=r){
		cov(i,v);return;
	}pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	if(r<=mid) upd(ls,l,r,v);
	else if(l>mid) upd(rs,l,r,v);
	else upd(ls,l,mid,v),upd(rs,mid+1,r,v);
	pushup(i);
}
ll qmin(int i,int l,int r){
	if(tr[i].l>=l&&tr[i].r<=r)
		return tr[i].mn;
	pushdown(i);int mid=tr[i].l+tr[i].r>>1;
	if(r<=mid) return qmin(ls,l,r);
	else if(l>mid) return qmin(rs,l,r);
	else return min(qmin(ls,l,mid),qmin(rs,mid+1,r));
}//区间赋值区间最小线段树
ll lsh[MAXN];int cnt;
struct Query{
	int op;ll l,r,x;
	void input(){
		scanf("%d%lld%lld",&op,&l,&r);
		if(op==1) scanf("%lld",&x);
		lsh[++cnt]=l;lsh[++cnt]=r;
	}
}q[MAXN];//离散询问
ll tmp[MAXN];//暂存不含相邻点区间最小值的数组
int n,k,mp[MAXN];//mp[] 存 lsh 中的第 i 个位置对应到最终数组中的位置是 mp[i]
int MODp(int p){
	p=p%n;if(p==0) p=n;
	return p;
}//求位置 p 在一段循环节中是第几个
ll getmin(ll l,ll r){
	ll ret;
	if(r-l+1>=n) ret=tr[1].mn;
	else{
		l=MODp(l);r=MODp(r);
		if(l<=r) ret=qmin(1,l,r);
		else{
			ret=qmin(1,1,r);
			ret=min(ret,qmin(1,l,n));
		}
	}return ret;
}//求出原位置 [l,r] 的最小值
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&b[i]);
	build(1,1,n);//先对原序列建一下线段树
	int Q;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		q[i].input();
	}sort(lsh+1,lsh+1+cnt);
	cnt=unique(lsh+1,lsh+1+cnt)-lsh-1;
	memset(tmp,0x3f,sizeof(tmp));
	for(int i=1;i<=Q;i++){
		int pl=lower_bound(lsh+1,lsh+1+cnt,q[i].l)-lsh;
		int pr=lower_bound(lsh+1,lsh+1+cnt,q[i].r)-lsh;
		tmp[pl]=b[MODp(q[i].l)];
		tmp[pr]=b[MODp(q[i].r)];
	}
	b[1]=tmp[1];mp[1]=1;
	int len=1;
	for(int i=1;i<cnt;i++){
		if(lsh[i]+1<=lsh[i+1]-1)
		b[++len]=getmin(lsh[i]+1,lsh[i+1]-1);//相邻两点之间的最小值
		b[++len]=tmp[i+1];mp[i+1]=len;//在询问中出现过的值
	}
	build(1,1,len);//对最终的序列建线段树
	for(int i=1;i<=Q;i++){
		int pl=lower_bound(lsh+1,lsh+1+cnt,q[i].l)-lsh;pl=mp[pl];
		int pr=lower_bound(lsh+1,lsh+1+cnt,q[i].r)-lsh;pr=mp[pr];
		//求出询问的两个端点在最终压缩后数组中的位置
		if(q[i].op==1) upd(1,pl,pr,q[i].x);
		else printf("%lld\n",qmin(1,pl,pr));
	}
}
```
## End

---

## 作者：UnyieldingTrilobite (赞：8)

首先，这题要求支持两个操作：区间推平，区间查最小值。不难想到珂朵莉树。

~~但似乎题解区没人用？~~

首先看如果没有推平操作该怎么做，就是在给出的数组里建个 ST 表然后查询的时候简单分类一下就好了。~~像我这样的强迫症还同时去维护了一下全局最小值和前缀/后缀最小值，大概可以减小一点点点常数（雾。~~

既然未推平区间都可以快速求值，**那就可以视为一个连续段**。至多是加个标记区分一下当前段是推平后区间还是推平前区间就可以了。

然后就是个 ODT 板板，奈何常数太大过不去。

~~我一开始的思路是直接把 set 换成平衡树然后维护连续段，这样的话理论复杂度是一个 $\sout{\log}$ 的奈何依旧常数太大过不去，平衡树常数比线段树常数那可不止大了一点。~~

我们需要一点合理优化。

既然我们敢用珂朵莉树，那就是相信了数据随机。既然如此，我们可以大胆猜测前期的诸多查询，答案很有可能直接就是全序列（修改后的）最小值，那也就是只要查询里有一段出了这个值那就直接退出循环，然后就可以过了。

ODT 期望复杂度大概是两只 $\log$，全算法复杂度瓶颈在普通 rmq 预处理。实际上可以用各种套路（比如 sqrt-tree，比如 [这个](https://return20071007.blog.uoj.ac/blog/6554)）把普通 rmq 复杂度也降到这个级别，但由于常数原因瓶颈反而在珂朵莉树上，那就无所谓了。

丢个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,st[20][100009],lg2[100009],suf[100009],pre[100009],mn;
int minret;
int query(int l,int r){
	if(r-l+1>=n)return mn;
	if((l=(l-1)%n+1)>(r=(r-1)%n+1))return min(pre[r],suf[l]);
	int h=lg2[r-l+1];
	return min(st[h][l],st[h][r-(1<<h)+1]);
}
struct node{
	mutable int l,r,v;
	bool tag;
	bool operator<(const node&to)const{return l<to.l;};
};
set<node>odt;
auto split(int x){
	if(x>n*k)return odt.end();
	auto it=--odt.upper_bound({x,0,0,false});
	if(it->l==x)return it;
	int l=it->l,r=it->r,v=it->v;
	bool tag=it->tag;
	odt.erase(it);
	odt.insert({l,x-1,v,tag});
	return odt.insert({x,r,v,tag}).first;
}
void assign(int l,int r,int v){
	auto itr=split(r+1),itl=split(l);
	odt.erase(itl,itr);
	odt.insert({l,r,v,true});
}
int qmin(int l,int r){
	int ret=INT_MAX;
	auto itr=split(r+1),itl=split(l);
	while(itl!=itr){
		ret=min(ret,itl->tag?itl->v:query(itl->l,itl->r));
		if(ret==minret)break;
		++itl;
	}return ret;
}
int main(){
	cin>>n>>k,lg2[0]=-1;
	for(int i=1;i<=n;++i)
		cin>>st[0][i],lg2[i]=lg2[i>>1]+1;
	minret=mn=*min_element(st[0]+1,st[0]+n+1);
	pre[0]=suf[n+1]=INT_MAX;
	for(int i=1;i<=n;++i)pre[i]=min(pre[i-1],st[0][i]);
	for(int i=n;i>=1;--i)suf[i]=min(suf[i+1],st[0][i]);
	for(int h=1;h<20;++h)
		for(int i=1;i+(1<<h)<=n+1;++i)
			st[h][i]=min(st[h-1][i],st[h-1][i+(1<<(h-1))]);
	odt.insert({1,n*k,mn,false});
	cin>>m;
	for(int op,l,r;m;--m){
		cin>>op>>l>>r;
		if(op==1){
			int x;cin>>x;
			minret=min(minret,x);
			assign(l,r,x);
		}else cout<<qmin(l,r)<<'\n';
	}
	return 0;
}
```

---

## 作者：Leap_Frog (赞：6)

### P.S.
高质量好题！！！！！！  
![](https://cdn.luogu.com.cn/upload/image_hosting/48jikhx5.png)  
这题我写了三种不同的方法，第一种写挂了，第二种也写挂了（（（  
于是这篇题解会介绍三种不同的方法，有两种可能是假的。。。  
通过这题让我明白了一个血的教训：能用简单的做法，不管常数有多大，就用。  
AC 代码 99808KB（50 行，WA 的代码 148736 KB （100 行
### Description.
给你一个序列，需要支持区间覆盖，查询区间最小值。  
但是这个序列很长，是 $10^9$ 级别的，但是它有不超过 $10^5$ 的循环节。  
读入方式是读入循环节长度和循环节数量。  

### Solution1.
思路很暴力，类似分块一样。  
对于所有区间维护一个动态开点线段树，再对所有循环节维护另一颗线段树。  
然后每次查询、修改直接对边块暴力修改（指在那颗线段树上修改。  
然后整块直接在循环节线段树上维护区间最小值以及这个循环节应该打的标记  
然后时间复杂度是 $O(n\log n+n\log k)$ 的，空间复杂度对每次询问只会增加 $\log n$ 个节点，所以是 $O(n+Q\log n)$ 的，结果笔者写挂了。  
附**写挂**的代码。  
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x,1:1;
}
const int INF=1e9+5;
int n,Q,k,a[1000005],rt[1000005],tt=0;
struct seg{int mn,lz,tg;}t[4000005];
struct segm{int mn,tg,ls,rs;}T[6000005];
inline void tallc(int x,int c) {if(c) t[x].mn=t[x].lz=t[x].tg=c;}
inline void tdown(int x) {tallc(x<<1,t[x].tg),tallc(x<<1|1,t[x].tg),t[x].tg=0;}
inline void tup(int x) {t[x].mn=min(t[x<<1].mn,t[x<<1|1].mn);}
inline void tbuild(int x,int l,int r,int c)
{
	if(l==r) return(void)(t[x].mn=c,t[x].lz=t[x].tg=0);else t[x].tg=0;
	tbuild(x<<1,l,(l+r)>>1,c),tbuild(x<<1|1,((l+r)>>1)+1,r,c),tup(x);
}
inline void tmotif(int x,int l,int r,int dl,int dr,int dc)
{
	if(dl>r||l>dr||dl>dr) return;else if(dl<=l&&r<=dr) return tallc(x,dc);else tdown(x);
	tmotif(x<<1,l,(l+r)>>1,dl,dr,dc),tmotif(x<<1|1,((l+r)>>1)+1,r,dl,dr,dc),tup(x);
}
inline int tquery(int x,int l,int r,int dl,int dr)
{
	if(dl>r||l>dr||dl>dr) return INF;else if(dl<=l&&r<=dr) return t[x].mn;else tdown(x);
	return min(tquery(x<<1,l,(l+r)>>1,dl,dr),tquery(x<<1|1,((l+r)>>1)+1,r,dl,dr));
}
inline int task(int x,int l,int r,int dw)
{
	if(l==r) return t[x].lz;else tdown(x);
	return dw<=((l+r)>>1)?task(x<<1,l,(l+r)>>1,dw):task(x<<1|1,((l+r)>>1)+1,r,dw);
}
inline void tqklz(int x,int l,int r,int dw,int dc)
{
	if(l==r) return(void)(t[x].lz=0,t[x].mn=dc);else tdown(x);
	if(dw<=((l+r)>>1)) tqklz(x<<1,l,(l+r)>>1,dw,dc),tup(x);
	else tqklz(x<<1|1,((l+r)>>1)+1,r,dw,dc),tup(x);
}
inline void Tallc(int &x,int c) {T[++tt]=T[x],x=tt;if(c) T[x].tg=c,T[x].mn=c;}
inline void Tdown(int x) {Tallc(T[x].ls,T[x].tg),Tallc(T[x].rs,T[x].tg),T[x].tg=0;}
inline void Tup(int x) {T[x].mn=min(T[T[x].ls].mn,T[T[x].rs].mn);}
inline void Tbuild(int &x,int l,int r)
{
	x=++tt;if(l==r) return(void)(T[x]=(segm){a[l],0,0,0});else T[x].tg=0;
	Tbuild(T[x].ls,l,(l+r)>>1),Tbuild(T[x].rs,((l+r)>>1)+1,r),Tup(x);
}
inline void Tmotif(int &x,int l,int r,int dl,int dr,int dc)
{
	if(l>dr||dl>r||!x) return;
	T[++tt]=T[x],x=tt;if(dl<=l&&r<=dr) return Tallc(x,dc);else Tdown(x);
	Tmotif(T[x].ls,l,(l+r)>>1,dl,dr,dc),Tmotif(T[x].rs,((l+r)>>1)+1,r,dl,dr,dc),Tup(x);
}
inline int Tquery(int x,int l,int r,int dl,int dr)
{
	if(!x||dl>r||l>dr) return INF;else if(dl<=l&&r<=dr) return T[x].mn;else Tdown(x);
	return min(Tquery(T[x].ls,l,(l+r)>>1,dl,dr),Tquery(T[x].rs,((l+r)>>1)+1,r,dl,dr));
}
inline void Push_Down(int w) {int val=task(1,1,n,w);if(val) Tmotif(rt[w],1,n,1,n,val),tqklz(1,1,n,w,val);}
inline void Chang(long long l,long long r,int c)
{
	int le=(l-1)/n+1,ri=(r-1)/n+1;Push_Down(le);if(le^ri) Push_Down(ri);
	if(le==ri) return Tmotif(rt[le],1,n,(l-1)%n+1,(r-1)%n+1,c),tqklz(1,1,n,le,T[rt[le]].mn);
	Tmotif(rt[le],1,n,(l-1)%n+1,n,c),tqklz(1,1,n,le,T[rt[le]].mn);
	Tmotif(rt[ri],1,n,1,(r-1)%n+1,c),tqklz(1,1,n,ri,T[rt[ri]].mn);
	tmotif(1,1,n,le+1,ri-1,c);
}
inline void P(int id) {for(int i=1;i<=n;i++) printf("%d%c",Tquery(rt[id],1,n,i,i),i==n?'\n':' ');}
inline int Query(long long l,long long r)
{
	int le=(l-1)/n+1,ri=(r-1)/n+1;Push_Down(le);if(le^ri) Push_Down(ri);
	int res=INF;if(le==ri) return Tquery(rt[le],1,n,(l-1)%n+1,(r-1)%n+1);
	res=min(res,Tquery(rt[le],1,n,(l-1)%n+1,n));
	res=min(res,Tquery(rt[ri],1,n,1,(r-1)%n+1));
	res=min(res,tquery(1,1,n,le+1,ri-1));return res;
}
inline void debug(int x,int l,int r)
{
	if(x) printf("%d : [ %d ~ %d ] : %d ( %d -> %d %d\n",x,l,r,T[x].mn,T[x].tg,T[x].ls,T[x].rs);
	if(l^r) Tdown(x),debug(T[x].ls,l,(l+r)>>1),debug(T[x].rs,((l+r)>>1)+1,r);
}
int main()
{
	read(n),read(k);for(int i=1;i<=n;i++) read(a[i]);
	Tbuild(rt[1],1,n),tbuild(1,1,n,T[rt[1]].mn);for(int i=2;i<=k;i++) rt[i]=rt[1];
	for(read(Q);Q--;)
	{
		//debug(rt[1],1,n),debug(rt[2],1,n);
		int fg,x;long long l,r;read(fg),read(l),read(r);
		if(fg^1) printf("%d\n",Query(l,r));else read(x),Chang(l,r,x);
	}
	return 0;
}
```
### Solution 2.
直接离线，然后直接暴力。  
把一段没有修改的区间直接压成一个点，用 st表 维护区间最值。  
思路很简单，一交直接 WA on 7，代码就不[放](http://codeforces.com/contest/803/submission/99108034)了。  
### Solution 3.
还是用 st表，但是不离散化，直接更加暴力地动态开点。  
和上面 Solution2 的思路差不对，只不过不压点。  
结果直接 A 了。。。~~小编也很惊讶但是事实就是这样子~~  
具体实现看代码注释qwq
### Coding.
```cpp
//愿你和你重要的人能够重逢
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
struct node{int vl,tg,ls,rs;}t[5000005];
int n,k,Q,a[300005],lg[200005],st[200005][25],tt=0,rt=0;
inline int qry(int l,int r) {int g=lg[r-l+1];return min(st[l][g],st[r-(1<<g)+1][g]);}
inline int rqry(int l,int r)
{//像分块一样，如果同一块，直接查
//如果相邻块就是后面一段和前面一段
//否则就肯定至少包括了一个整块，直接全局最小值
	int le=(l-1)/n+1,ri=(r-1)/n+1,L=(l-1)%n+1,R=(r-1)%n+1;if(le==ri) return qry(L,R);
	if(le+1==ri) return min(qry(L,n),qry(1,R));else return qry(1,n);
}
//↓动态开点线段树的动态开点函数↓
inline void New(int &x,int l,int r) {if(!x) t[x=++tt]=(node){rqry(l,r),0,0,0};}
//↓线段树模板↓
inline void allc(int x,int c) {if(c) t[x].vl=t[x].tg=c;}
inline void down(int x,int l,int r) {New(t[x].ls,l,(l+r)>>1),New(t[x].rs,((l+r)>>1)+1,r),allc(t[x].ls,t[x].tg),allc(t[x].rs,t[x].tg),t[x].tg=0;}
inline void motif(int &x,int l,int r,int dl,int dr,int dc)
{
	New(x,l,r);if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x,dc);else down(x,l,r);
	motif(t[x].ls,l,(l+r)>>1,dl,dr,dc),motif(t[x].rs,((l+r)>>1)+1,r,dl,dr,dc),t[x].vl=min(t[t[x].ls].vl,t[t[x].rs].vl);
}
inline int query(int &x,int l,int r,int dl,int dr)
{
	New(x,l,r);if(l>dr||dl>r) return 1e9;else if(dl<=l&&r<=dr) return t[x].vl;else down(x,l,r);
	return min(query(t[x].ls,l,(l+r)>>1,dl,dr),query(t[x].rs,((l+r)>>1)+1,r,dl,dr));
}
//debug函数，不删了
inline void debug(int x,int l,int r)
{
	if(x) printf("%d : [ %d , %d ] & %d\n",x,l,r,t[x].vl);
	if(l^r) down(x,l,r),debug(t[x].ls,l,(l+r)>>1),debug(t[x].rs,((l+r)>>1)+1,r);
}
int main()
{
	lg[0]=-1,read(n),read(k);
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) read(st[i][0]);
	for(int i=1;i<=20;i++) for(int j=1;j+(1<<(i-1))<=n;j++) st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
//	printf("%d , %d , %d , %d , %d , %d\n",rqry(1,1),rqry(1,2),rqry(1,3),rqry(2,2),rqry(2,3),rqry(3,3));
	read(Q),New(rt,1,n*k);for(int fg,l,r,c;Q--;)
	{
		read(fg),read(l),read(r);//debug(rt,1,n);
		if(fg&1) read(c),motif(rt,1,n*k,l,r,c);else printf("%d\n",query(rt,1,n*k,l,r));
	}
	return 0;
}
```

---

## 作者：qwaszx (赞：6)

好题

如果初值都是$0$那么我们直接动态开点线段树就能水过这道题.

有初值怎么办呢?

每次需要新建节点的时候我们直接把它的初值算出来，也就是一个区间$[l,r]$的最小值.

类似分块，这个最小值有三种情况.

1. $r-l+1>=n$，那么它包含一个完整的原序列，又因为新序列是原序列复制得到的，所以最小值就是原序列中的最小值

2. $l,r$在同一个块内，直接查询对应原序列中的最小值.使用$ST$表即可.

3. $l,r$不在同一个块内，那么这个区间的组成相当于原序列的一个前缀和一个后缀，分别预处理然后取个$min$就好了.

其他的都和动态开点线段树没什么区别了.注意修改的时候两边都要新建节点，即使并不需要修改其中一边，因为这样才能保证$pushup$的正确性.


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2e5;
struct Node{int w,ch[2];}a[N<<6];
int f[20][N],pre[N],suc[N],minn,n,nn,q,lg[N],node_cnt,tag[N<<6],rt;
int st_query(int l,int r)
{
	int len=lg[r-l+1];
	return min(f[len][l],f[len][r-(1<<len)+1]);
}
void make()
{
	lg[1]=0;for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	pre[1]=f[0][1];for(int i=2;i<=n;i++)pre[i]=min(pre[i-1],f[0][i]);
	suc[n]=f[0][n];for(int i=n-1;i>=1;i--)suc[i]=min(suc[i+1],f[0][i]);
	minn=pre[n];
}
int query(int l,int r)
{
	if(r-l+1>=n)return minn;
	int bl=(l-1)/n+1,br=(r-1)/n+1;
	if(bl==br){int L=(bl-1)*n;return st_query(l-L,r-L);}
	else{int L=(bl-1)*n,R=(br-1)*n;return min(suc[l-L],pre[r-R]);}
}
void newnode(int &rot,int lt,int rt)
{
	rot=++node_cnt;
	a[rot].w=query(lt,rt);
}
void upd(int rot,int w){a[rot].w=tag[rot]=w;}
void pushdown(int rot)
{
	if(tag[rot])
	{
		int t=tag[rot];tag[rot]=0;
		if(!a[rot].ch[0])a[rot].ch[0]=++node_cnt;
		if(!a[rot].ch[1])a[rot].ch[1]=++node_cnt;
		upd(a[rot].ch[0],t),upd(a[rot].ch[1],t);
	}
}
void update(int &rot,int lt,int rt,int lq,int rq,int w)
{
	if(!rot)newnode(rot,lt,rt);
	if(lt>rq||rt<lq)return;
//	cout<<lt<<" "<<rt<<" "<<a[rot].w<<endl;
	if(lt>=lq&&rt<=rq){upd(rot,w);return;}
	pushdown(rot);int mid=(lt+rt)>>1;
	update(a[rot].ch[0],lt,mid,lq,rq,w),update(a[rot].ch[1],mid+1,rt,lq,rq,w);
	a[rot].w=min(a[a[rot].ch[0]].w,a[a[rot].ch[1]].w);
}
int query(int &rot,int lt,int rt,int lq,int rq)
{
	if(!rot)newnode(rot,lt,rt);
//	cout<<lt<<" "<<rt<<" "<<a[rot].w<<endl;
	if(lt>=lq&&rt<=rq)return a[rot].w;
	int mid=(lt+rt)>>1;pushdown(rot);
	if(rq<=mid)return query(a[rot].ch[0],lt,mid,lq,rq);
	else if(lq>mid)return query(a[rot].ch[1],mid+1,rt,lq,rq);
	else return min(query(a[rot].ch[0],lt,mid,lq,mid),query(a[rot].ch[1],mid+1,rt,mid+1,rq));
}
int getin()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x;
}
int main()
{
	n=getin(),nn=getin()*n;
	for(int i=1;i<=n;i++)f[0][i]=getin();
	make();
	q=getin();a[0].w=2e9;
	for(int i=1;i<=q;i++)
	{
		int opt=getin(),l=getin(),r=getin(),x;
		if(opt==1)x=getin(),update(rt,1,nn,l,r,x);
		else printf("%d\n",query(rt,1,nn,l,r));
	}
}
```

---

## 作者：RedreamMer (赞：3)

[$\Large\texttt{CF803G}$](https://www.luogu.com.cn/problem/CF803G)

标签：线段树、离散化

~~可能就是码量大了一点~~

## 题意

~~这么清楚了就不作赘述了QwQ~~

就是要注意它的 $\texttt{q}$ 大小只有 $1e5$ 。

## 思路

面对这种题目，串的长度很长但是有规律，区间修改为赋值操作，基本上都有一个十分套路的通解，因为对于 $1e5$ 的操作数据访问很少，操作只要记录两个端点，所以有些元素根本不会用到它，把它们忽视掉就好了，可以用离散化优化。

但是这里的串初始化时一段串重复多次形成的，可能有点难离散化，我的方法是把所有操作两个端点离散化下来，对于每两个端点间的区间（不包括这两个端点）也离散化成一个值，这个值就是区间中最小的数。

这个区间的值可以分类得到：

1. 区间的两个端点距离超过一个序列 $a$ 的长度，那么直接将这个区间的值取为序列a的最小值。

2. 区间的两个端点在完整的一个 $a$ 序列内，这里可以把它们相对于a序列的位置求出来，用 $\texttt{ST}$ 表求出区间最小值。

3. 区间的两个端点跨越了一个序列 $a$ ，这可以把两端区间（端点 $r$ 到序列头，端点 $l$ 序列尾）的最小值，同样用 $\texttt{ST}$ 表做到 $O(1)$ 查询。

然后维护好所有的端点后，剩下的操作用朴素的线段树就可以过去。

复杂度 $\texttt{O(玄学+可过)}$

目前的最优解 $3.37ms$

## 代码

```cpp

#include <bits/stdc++.h>
using namespace std;

#define ls n << 1
#define rs n << 1 | 1
const int N = 1e5;
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a, b, c, s[N + 10], p[(N << 1) + 10], top, q[(N << 2) + 10], id, f[N + 10][30];
struct ask
{
    int opt, l, r, x;
} ask[N + 10];
struct Stree
{
    int l, r, mn;
    bool lazy;
} t[(N << 4) + 10];
struct reel_id
{
    int id, val;
} o[(N << 1) + 10];

inline int find(int n)
{
    int l = 1, r = top;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (o[mid].val == n)
            return o[mid].id;
        if (o[mid].val < n)
            l = mid + 1;
        else
            r = mid - 1;
    }
}

inline int query(int l, int r)//ST表O(1)询问
{
    int k = log2(r - l + 1);
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}

inline void up(int n)
{
    t[n].mn = min(t[ls].mn, t[rs].mn);
}

inline void down(int n)
{
    if (!t[n].lazy)
        return;
    t[ls].mn = t[rs].mn = t[n].mn;
    t[ls].lazy = t[rs].lazy = 1;
    t[n].lazy = 0;
}

inline void build(int n, int l, int r)
{
    t[n].l = l;
    t[n].r = r;
    t[n].mn = 1e9;
    if (l == r)
    {
        t[n].mn = q[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    up(n);
}

inline void change(int n, int l, int r, int k)
{
    if (l <= t[n].l && t[n].r <= r)
    {
        t[n].mn = k;
        t[n].lazy = 1;
        return;
    }
    down(n);
    int mid = (t[n].l + t[n].r) >> 1;
    if (l <= mid)
        change(ls, l, r, k);
    if (mid < r)
        change(rs, l, r, k);
    up(n);
}

inline int Query(int n, int l, int r)
{
    if (l <= t[n].l && t[n].r <= r)
        return t[n].mn;
    int mid = (t[n].l + t[n].r) >> 1, sum = 1e9;
    down(n);
    if (l <= mid)
        sum = min(sum, Query(ls, l, r));
    if (mid < r)
        sum = min(sum, Query(rs, l, r));
    return sum;
}

signed main()
{
    a = read();
    b = read();
    int mn = 1e9;
    for (int i = 1; i <= a; i++)
        s[i] = f[i][0] = read(), mn = min(mn, s[i]);
    for (int i = 1; i <= 25; i++)
        for (int j = 1; j + (1 << i) - 1 <= a; j++)
            f[j][i] = min(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
    c = read();
    for (int i = 1; i <= c; i++)
    {
        ask[i].opt = read();
        ask[i].l = read();
        ask[i].r = read();
        if (ask[i].opt == 1)
            ask[i].x = read();
        p[++top] = ask[i].l;
        p[++top] = ask[i].r;
    }
    sort(p + 1, p + top + 1);//离散下询问的所有端点 
    top = unique(p + 1, p + top + 1) - p - 1;
    for (int i = 1; i <= top; i++)
    {
        if (i > 1 && p[i] - p[i - 1] > 1)//离散下区间 
        {
            int l = p[i - 1] + 1, r = p[i] - 1;
            if (r - l + 1 >= a)
                q[++id] = mn;
            else
            {
                l = (l - 1) % a + 1;
                r = (r - 1) % a + 1;
                if (l <= r)
                    q[++id] = query(l, r);
                else
                    q[++id] = min(query(1, r), query(l, a));
            }
        }
        q[++id] = s[(p[i] - 1) % a + 1];
        o[i].val = p[i];
        o[i].id = id;
    }
    for (int i = 1; i <= c; i++)
        ask[i].l = find(ask[i].l), ask[i].r = find(ask[i].r);//修改下操作的两个端点 
    build(1, 1, id);
    for (int i = 1; i <= c; i++)
    {
        if (ask[i].opt == 1)
            change(1, ask[i].l, ask[i].r, ask[i].x);
        if (ask[i].opt == 2)
            printf("%d\n", Query(1, ask[i].l, ask[i].r));
    }
    return 0;
}
```

---

## 作者：Rui_R (赞：2)

题目大意：给一个序列，由一个长为N的序列拼接M次而成。现在要在这个东西上面维护区间赋值操作和区间最小值。

$N<=1e5,M<=1e4$

[原题](https://www.luogu.com.cn/problem/CF803G)

如果只是单纯的区间赋值和区间最小值，这题就是线段树裸题。问题在于这个数列长度有 $1e9$ ，线段树会当场空间爆炸。

于是，我们要想想怎么减少空间消耗。

我们注意到这个序列是由一段长度可以接受的序列，拼接可以接受的次数而形成的。也就是说，它们之间**存在大量相同的部分。** 我们要充分利用这个性质，节省空间。

于是想到一个类似可持久化线段树的东西，也就是对于每一份序列，维护一棵线段树。**同时，它们尽量使用同一份空间。**

为什么想到对于每一份序列建树？因为这样的话，初始时**它们完全相同，甚至可以用同一个根结点。**

而之后面对修改操作，可以动态开点。

但是问题又来了：如果操作区间横跨多份序列，要怎么办？

好办的很，在序列之间再维护一个数据结构，要支持区间赋值，区间最小值，其内部的值由序列内部的线段树维护出来。

咦？这不还是线段树吗？于是我们得到一个存在漏洞的（伪）程序：

对于区间赋值操作：

如果在同一份序列里，更新该序列内部线段树，然后单点更新序列之间线段树。

否则，更新散块内部线段树，整块间以序列之间线段树维护。对于散块，记得单点更新序列之间线段树。

询问同理。

但是仔细一想，有漏洞：我们用序列之间的线段树区间赋值了一些序列，可是在处理序列内部的时候，我们要怎么知道它有没有被区间赋值过啊？

具体来说，我们要怎么知道一份序列，是否被区间赋值过，以及**该“赋值”是否已经生效呢？**

我们可以打标记啊！怎么打标记呢？

现在我们需要一个数据结构，支持区间打标记，查询一个点（即一份序列）有没有被整个赋值过。

等等，区间打标记……也算是区间赋值吧？

唔！这不还是线段树吗？

（其实因为只需要单点查询，可以树状数组，但是实际上我们可以直接套用之前的序列间线段树，会更简单）

于是对于之前的伪代码，在每次访问一棵序列内部线段树的时候，先判断它是否需要被区间赋值，那么就完整了。

三棵线段树完全独立，复杂度应该还是 $O(n \log{n})$。

不过显而易见的惊人常数，险些喜提最劣解。

```
#include <cstdio>
#include <cstdlib>

const int maxn=1e5+5,inf=1e9+7;
#define null 0

int n,m,a[maxn],minn=inf;

template<typename T> inline T min(T a,T b){
	return a<b?a:b;
}

struct sgt_1{//每个序列内部线段树，动态开点
	struct node{
		node *l,*r;int tag,minn;
		node(){l=r=null;tag=0,minn=inf;}
		void push_up(){
			if(!l&&!r) return;
			minn=min(l?l->minn:inf,r?r->minn:inf);
		}
		void push_down(){
			if(!tag||(!l&&!r)) return;
			node *pl=new node;*pl=*l;pl->minn=pl->tag=tag;l=pl;
			node *pr=new node;*pr=*r;pr->minn=pr->tag=tag;r=pr;//别忘了新开结点
			tag=0;
		}
		void init(){*this=node();}
	}*rt[maxn];
	node *&operator[](const int &id){
		return rt[id];
	}
	node *build(int l,int r){
		node *now=new node;if(l==r){now->minn=a[l];return now;}
		int mid=(l+r)>>1;
		now->l=build(l,mid),now->r=build(mid+1,r);
		return now->push_up(),now;//按原始序列建树
	}
	node* modify(int _l,int _r,node* las,int l,int r,int val){
		if(l>_r||r<_l) return las;node *now=new node;*now=*las;//动态开点
		if(_l<=l&&r<=_r){
			now->tag=now->minn=val;
			return now;
		}
		now->push_down();int mid=(l+r)>>1;
		now->l=modify(_l,_r,now->l,l,mid,val),now->r=modify(_l,_r,now->r,mid+1,r,val);
		return now->push_up(),now;//区间赋值
	}
	int wonder(int _l,int _r,node *now,int l,int r){
		if(l>_r||r<_l) return inf;if(_l<=l&&r<=_r) return now->minn;
		now->push_down();int mid=(l+r)>>1;
		return min(wonder(_l,_r,now->l,l,mid),wonder(_l,_r,now->r,mid+1,r));
	}//区间最值
}s_1;

struct sgt_2{//序列上线段树，这个不用动态开点
	struct node{
		node *l,*r;int tag,minn;
		node(){l=r=null;tag=0,minn=inf;}
		void push_up(){
			if(!l&&!r) return;
			minn=min(l?l->minn:inf,r?r->minn:inf);
		}
		void push_down(){
			if(!tag) return;
			l->tag=l->minn=tag,r->tag=r->minn=tag;
			tag=0;
		}
		void init(){*this=node();}
	}*rt;
	node *build(int l,int r){
		node *now=new node;if(l==r){now->minn=minn;return now;}
		int mid=(l+r)>>1;
		now->l=build(l,mid),now->r=build(mid+1,r);
		return now->push_up(),now;
	}
	void modify(int _l,int _r,node *now,int l,int r,int val){
		if(l>_r||r<_l) return;
		if(_l<=l&&r<=_r){
			now->tag=now->minn=val;
			return;
		}
		now->push_down();
		int mid=(l+r)>>1;
		modify(_l,_r,now->l,l,mid,val),modify(_l,_r,now->r,mid+1,r,val);
		return now->push_up();
	}
	int wonder(int _l,int _r,node *now,int l,int r){
		if(l>_r||r<_l) return inf;if(_l<=l&&r<=_r) return now->minn;
		now->push_down();int mid=(l+r)>>1;
		return min(wonder(_l,_r,now->l,l,mid),wonder(_l,_r,now->r,mid+1,r));
	}
}s_2,s_3;//s_2用来管区间最值，s_3用来管标记

inline int where(int key){return (key-1)/n+1;}//判断一个点所在序列

void solve(int id){//类似push_down操作
	int watch=s_3.wonder(id,id,s_3.rt,1,m);
	if(watch){
		s_1[id]=s_1.modify(1,n,s_1[id],1,n,watch);
		s_3.modify(id,id,s_3.rt,1,m,0);
	}//判断一个序列是否被标记过要赋值，并处理赋值
}

int main(){
	scanf("%d%d",&n,&m);for(int i=1;i<=n;i++) scanf("%d",&a[i]),minn=min(minn,a[i]);
	s_1.rt[1]=s_1.build(1,n);s_2.rt=s_2.build(1,m);minn=0;s_3.rt=s_3.build(1,m);
	for(int i=2;i<=m;i++) s_1.rt[i]=s_1.rt[i-1];
	int q;scanf("%d",&q);
	for(int ___=1;___<=q;___++){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			int idl=where(l),idr=where(r);
			l-=(idl-1)*n,r-=(idr-1)*n;
			if(idl==idr){
				solve(idl);s_1[idl]=s_1.modify(l,r,s_1.rt[idl],1,n,x);
				s_2.modify(idl,idl,s_2.rt,1,m,s_1.wonder(1,n,s_1[idl],1,n));
				continue;
			}
			solve(idl);s_1[idl]=s_1.modify(l,n,s_1[idl],1,n,x);s_2.modify(idl,idl,s_2.rt,1,m,s_1.wonder(1,n,s_1[idl],1,n));
			solve(idr);s_1[idr]=s_1.modify(1,r,s_1[idr],1,n,x);s_2.modify(idr,idr,s_2.rt,1,m,s_1.wonder(1,n,s_1[idr],1,n));
			if(idl!=idr) s_2.modify(idl+1,idr-1,s_2.rt,1,m,x),s_3.modify(idl+1,idr-1,s_3.rt,1,m,x);
		}
		else{
			int l,r;scanf("%d%d",&l,&r);int idl=where(l),idr=where(r);
			l-=(idl-1)*n,r-=(idr-1)*n;
			solve(idl);if(idl!=idr) solve(idr);
			if(idl==idr) printf("%d\n",s_1.wonder(l,r,s_1[idl],1,n));
			else{
				int temp=inf;if(idl!=idr) temp=s_2.wonder(idl+1,idr-1,s_2.rt,1,m);
				temp=min(temp,min(s_1.wonder(l,n,s_1[idl],1,n),s_1.wonder(1,r,s_1[idr],1,n)));
				printf("%d\n",temp);
			}
		}//见伪代码
	}
	return 0;
}
```

---

## 作者：CyanSineSin (赞：2)

**题目解释：**

有一个由给定序列不断首尾拼接而成的序列（很长，存不下）。

要求实现两个操作：区间赋值和查询区间最小值。

----

这个序列很长不好操作，所以我们要进行离散化，缩小一下操作的范围。

把每个操作的左端点减一和右端点加入离散化数组$pri$（这里下标从1开始）。

离散化后第i个块的左端点是$pri[i-1]+1$,右端点是$pri[i]$。（离散化还要插入$0$和最后一个位置的下标，不然有些位置没有被覆盖到）

但是离散化之后我们不知道每个离散化出来的块内的最小值，这样就无法初始化。

我们可以利用之前给出用来首尾拼接的序列求出来。

对每个块分类讨论：（设给定用来拼接的序列长为$n$）

1).块长大于等于$n$：

此时这个块已经覆盖了整个给定序列，那它的最小值直接就是给定序列的最小值。

2).块长小于$n$：

又要分两种情况:

$\ \ \ \ $A).左端点投射到序列中的位置在右端点的后面（由于是由同一序列首尾拼接而成，我们可以把它们投射到一个序列上）。

$\ \ \ \ $就是说：这个块覆盖的给定序列的前面的一部分和后面的一部分。

$\ \ \ \ $就像这样：

![](https://s1.ax1x.com/2020/07/28/aAX7GQ.png)

$\ \ \ \ $投射到给定序列上就像这样：

![](https://s1.ax1x.com/2020/07/28/aAXTPg.png)

$\ \ \ \ $那么我们直接查询（涂色的）这两段的最小值再取个$min$就好了。

$\ \ \ \ $其实就是从他们中间的序列尾（就是更上面的那张图L,R中间那条黑线）分开来求两边的最小值再取$min$，就得到了他们之间的最小值。

$\ \ \ \ $B).左端点投射到序列中的位置在右端点的前面。

$\ \ \ \ $仿照上个情况，投射到序列上查询他们之间的最小值即可。

由于是以操作的左右端点做的离散化，所以一个块内要么一起被询问，要么一起被修改。

所以我们用上面的方法处理出这个离散化后的序列每个块的初始值之后，就可以用线段树把它当板题做了！

代码：

```
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> pri;
const int INF=1e9+1;
int n,q,k,a[100010],ori[400010],op[100010],opl[100010],opr[100010],opx[100010],nodes[1000010],tag[2000010],s;
void buildori(int l,int r,int x)//对于给定序列的线段树建树。 
{
	if(l^r)
	{
		int mid=(l+r)>>1;
		buildori(l,mid,x<<1);
		buildori(mid+1,r,x<<1|1);
		ori[x]=min(ori[x<<1],ori[x<<1|1]);
	}
	else	ori[x]=a[l];
}
int findori(int l,int r,int x,int fr,int ba)//查询给定序列里的区间最小值。 
{
	if(l>ba||r<fr)	return INF;
	if(l>=fr&&r<=ba)	return ori[x];
	else
	{
		int mid=(l+r)>>1;
		return min(findori(l,mid,x<<1,fr,ba),findori(mid+1,r,x<<1|1,fr,ba));
	}
}
void build(int l,int r,int x)//对离散化后的序列建树。 
{
	if(l^r)
	{
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		nodes[x]=min(nodes[x<<1],nodes[x<<1|1]);
	}
	else
	{
		if(pri[l]-pri[l-1]>=n)	nodes[x]=ori[1];//情况1). 
		else
		{
			int one=(pri[l-1]+1)%n;
			if(one==0)	one=n;
			int two=pri[l]%n;
			if(two==0)	two=n;
			if(one>two)	nodes[x]=min(findori(1,n,1,one,n),findori(1,n,1,1,two));//情况2).A). 
			else	nodes[x]=findori(1,n,1,one,two);//情况2).B). 
		}
	}
}
//后面的就是模板操作。 
void pushdown(int x)
{
	if(tag[x])
	{
		nodes[x]=tag[x];
		tag[x<<1]=tag[x<<1|1]=tag[x];
		tag[x]=0;
	}
}
void update(int l,int r,int x,int fr,int ba,int val)
{
	if(l>ba||r<fr)	return;
	if(l>=fr&&r<=ba)	tag[x]=val;
	else
	{
		int mid=(l+r)>>1;
		pushdown(x);
		update(l,mid,x<<1,fr,ba,val);
		update(mid+1,r,x<<1|1,fr,ba,val);
		pushdown(x<<1);
		pushdown(x<<1|1);
		nodes[x]=min(nodes[x<<1],nodes[x<<1|1]);
	}
}
int find(int l,int r,int x,int fr,int ba)
{
	if(l>ba||r<fr)	return INF;
	pushdown(x);
	if(l>=fr&&r<=ba)	return nodes[x];
	else
	{
		int mid=(l+r)>>1;
		return min(find(l,mid,x<<1,fr,ba),find(mid+1,r,x<<1|1,fr,ba));
	}
}
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	buildori(1,n,1);
	scanf("%d",&q);
	pri.push_back(0);
	pri.push_back(n*k);//插入0和最后一个位置的下标。 
	for(int i=1;i<=q;++i)
	{
		scanf("%d %d %d",&op[i],&opl[i],&opr[i]);
		if(op[i]==1)	scanf("%d",&opx[i]);
		pri.push_back(opl[i]-1);
		pri.push_back(opr[i]);//把每个操作的左端点减一和右端点加入离散化数组pri。 
	}
	sort(pri.begin(),pri.end());
	pri.erase(unique(pri.begin(),pri.end()),pri.end());
	s=pri.size();
	build(1,s,1);//0下标的位置没有前一个，所以从1开始建树。 
	for(int i=1;i<=q;++i)
	{
		//lower_bound返回大于等于给定值的下标，插入操作时是插入的opl[i]-1和opr[i]，所以查询大于等于opl[i]的下标可以查询到opl[i]所在的块。 
		if(op[i]==1)	update(1,s,1,lower_bound(pri.begin(),pri.end(),opl[i])-pri.begin(),lower_bound(pri.begin(),pri.end(),opr[i])-pri.begin(),opx[i]);
		else	printf("%d\n",find(1,s,1,lower_bound(pri.begin(),pri.end(),opl[i])-pri.begin(),lower_bound(pri.begin(),pri.end(),opr[i])-pri.begin()));
	}
	return 0;
}
```

---

## 作者：Terac (赞：1)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF803G)

## 题意

给定一个长度为 $n$ 的序列 $b_{1\dots n}$，将其首尾相接 $k$ 次得到序列 $a_{1\dots nk}$，在 $a$ 上进行 $q$ 次操作：

+ 区间推平
+ 区间查询最小值


数据范围：$1\le n,q\le 10^5$，$1\le k\le10^4$，$1\le b_i\le10^9$

## 题解

又是一道 DS 妙题。

$a$ 的长度能到 $10^9$，用朴素线段树做时间复杂度 $O(nk\log nk)$，空间也到了 $O(nk)$，显然不能接受。

空间可以动态开点优化至 $O(q\log nk)$，这个结构看上去就很可以用动态开点线段树做。

发现每次新建节点都要求出区间的最小值，考虑如何快速求出。

对于一个新建的节点，该区间是由 $b$ 构成的，考虑将该区间的最小值转化到序列 $b$ 上。

设区间为 $\left[l,r\right]$，便于处理，这里下标从 $0$ 开始，分三类讨论：

1. 当 $r-l+1\ge n$ 时，此时一定包含了整个 $b$ 序列，区间最小值为 $\min\limits_{i=0}^{n-1}b_i$。  

![](https://cdn.luogu.com.cn/upload/image_hosting/pt0sb17w.png?x-oss-process=image/resize,m_lfit,h_2000,w_2000)

2. 当 $r-l+1<n$ 且 $\lfloor\frac{l}{n}\rfloor=\lfloor\frac{r}{n}\rfloor$ 时，$l,r$ 在同一 $b$ 序列中，区间最小值为 $\min\limits_{i=l\bmod n}^{r\bmod n}b_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cysxf2zb.png?x-oss-process=image/resize,m_lfit,h_2000,w_2000)

3. 当 $r-l+1<n$ 且 $\lfloor\frac{l}{n}\rfloor\ne\lfloor\frac{r}{n}\rfloor$ 时，$l,r$ 恰分布在两个 $b$ 序列中的连续段，区间最小值为 $\min(\min\limits_{i=l\bmod n}^{n-1}b_i,\min\limits_{i=0}^{r\bmod n}b_i)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/lmj1n5l2.png?x-oss-process=image/resize,m_lfit,h_2000,w_2000)

于是可以对 $b$ 开一个 ST 表维护区间最小值做到 $O(1)$ 开点，总时间复杂度为 $O(q\log nk)$。  

感觉写下来有种分块的味道，整体还算小清新。

顺便提一嘴数组开的大小，因为下传标记时会开左右儿子的点，所以实际上还有一个常数 $2$，数组大小为 $2\times10^5\times\log(10^9)\approx6\times10^6$。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
	//read and write
} using namespace IO;
const int N = 1e5 + 10, M = 6e6 + 10, L = 20;
int n, k, q;
namespace RMQ {
	int st[L][N];
	void init() {
		for(int i = 1; (1 << i) <= n; i++)
			for(int j = 0; j + (1 << i) - 1 < n; j++)
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	}
	int Min(int l, int r) {
		int len = log2(r - l + 1);
		return min(st[len][l], st[len][r - (1 << len) + 1]);
	}
} using namespace RMQ;
namespace SegmentTree {
	int rt, ls[M], rs[M], mn[M], tag[M], cnt;
	int newnode(int l, int r) {
		++cnt;
		if(r - l + 1 >= n) return mn[cnt] = Min(0, n - 1), cnt;
		if(l / n == r / n) return mn[cnt] = Min(l % n, r % n), cnt;
		return mn[cnt] = min(Min(l % n, n - 1), Min(0, r % n)), cnt;
	}
	void pushup(int x) { mn[x] = min(mn[ls[x]], mn[rs[x]]); }
	void pushdown(int x, int l, int r) {
		int mid = l + r >> 1;
		if(!ls[x]) ls[x] = newnode(l, mid);
		if(!rs[x]) rs[x] = newnode(mid + 1, r);
		if(!tag[x]) return;
		mn[ls[x]] = mn[rs[x]] = tag[ls[x]] = tag[rs[x]] = tag[x];
		tag[x] = 0;
		return;
	}
	void modify(int &x, int l, int r, int L, int R, int v) {
		if(!x) x = newnode(l, r);
		if(L <= l && r <= R) { mn[x] = tag[x] = v; return; };
		pushdown(x, l, r);
		int mid = l + r >> 1;
		if(mid >= L) modify(ls[x], l, mid, L, R, v);
		if(mid < R) modify(rs[x], mid + 1, r, L, R, v);
		pushup(x); 
	}
	int query(int &x, int l, int r, int L, int R) {
		if(!x) x = newnode(l, r);
		if(L <= l && r <= R) return mn[x];
		pushdown(x, l, r);
		int mid = l + r >> 1, res = 2e9;
		if(mid >= L) res = min(res, query(ls[x], l, mid, L, R));
		if(mid < R) res = min(res, query(rs[x], mid + 1, r, L, R));
		return res;
	}
} using namespace SegmentTree;
int main() {
	n = read(), k = read();
	for(int i = 0; i < n; i++) st[0][i] = read();
	init();
	q = read();
	int opt, l, r, x;
	while(q--) {
		opt = read(), l = read() - 1, r = read() - 1;
		if(opt == 1) x = read(), modify(rt, 0, n * k - 1, l, r, x);
		else write(query(rt, 0, n * k - 1, l, r)), putc('\n');
	}
	flush();
	return 0;
}
```

---

## 作者：yzxoi (赞：1)

## [My Blog](https://yzxoi.top/archives/1765)

## Description

> 题目链接：[CF803G](http://codeforces.com/problemset/problem/803/G)

一个序列 $\{a_i\}$ 由 $k$ 个长度为 $n$ 的序列 $\{b_i\}$ 拼接而成，支持 $q$ 个操作：

1. `1 l r x`，区间赋值
2. `2 l r`求区间最小值

$1\leq n\leq 10^5,1\leq k \leq 10^4,1\leq q \leq 10^5,1\leq b_i\leq 10^9$

## Solution

~~乍一看就是线段树模板题~~，然后看一眼数据范围，序列 $\{a_i\}$ 的长度可以高达 $10^9$，所以不能直接开线段树。

考虑这个序列的特殊性质：由 $k$ 个长度为 $n$ 的序列 $\{b_i\}$ 拼接而成。

也就是说其实我们可以把所有操作映射到 $\{b_i\}$ 上做。

然后把所有操作离线下来，离散化，拆成每个点以及两个点间的区间，先用 RMQ 预处理出离散化后每个点的初值，然后再套个线段树动态维护一下最小值即可。

## Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=1e5+10;
int n,k,b[N],q,o[N<<1],cnt,tot,w[N<<2],id[N<<2];
struct Que{int op,l,r,x;}c[N];
class RMQ{
	private:
		int F[N][20],lg[N];
	public:
		I void B(){
			RI i,j;for(lg[0]=-1,i=1;i<=n;i++) F[i][0]=b[i],lg[i]=lg[i/2]+1;
			for(j=1;(1<<j)<=n;j++) for(i=1;i+(1<<j)-1<=n;i++) F[i][j]=min(F[i][j-1],F[i+(1<<j-1)][j-1]);
		}
		I int Q(CI l,CI r){return min(F[l][lg[r-l+1]],F[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);}
}R;
class SegmentTree{
	private:
		struct node{int S,T;}T[N<<3];
		#define mid (l+r>>1)
		#define PT CI x=1,CI l=1,CI r=tot
		#define LT x<<1,l,mid
		#define RT x<<1|1,mid+1,r
		#define PU(x) (T[x].S=min(T[x<<1].S,T[x<<1|1].S))
		#define PD(x) (T[x].T&&(T[x<<1].T=T[x<<1|1].T=T[x<<1].S=T[x<<1|1].S=T[x].T,T[x].T=0))
	public:
		I void B(PT){
			if(l==r) return void(T[x].S=w[l]);
			B(LT),B(RT),PU(x);
		}
		I void U(CI L,CI R,CI v,PT){
			if(L<=l&&r<=R) return void(T[x].T=T[x].S=v);
			PD(x),L<=mid&&(U(L,R,v,LT),0),R>mid&&(U(L,R,v,RT),0),PU(x);
		}
		I int Q(CI L,CI R,PT){
			if(L<=l&&r<=R) return T[x].S;
			RI S=2e9;return PD(x),L<=mid&&(S=min(S,Q(L,R,LT))),R>mid&&(S=min(S,Q(L,R,RT))),S;
		}
}S;
int main(){
	RI i,l,r;for(read(n,k),i=1;i<=n;i++) read(b[i]);
	for(R.B(),read(q),i=1;i<=q;i++) read(c[i].op,c[i].l,c[i].r),c[i].op&1&&(read(c[i].x),0),o[++cnt]=c[i].l,o[++cnt]=c[i].r;
	#define idx(x) ((x)%n?(x)%n:n)
	sort(o+1,o+cnt+1),cnt=unique(o+1,o+cnt+1)-o-1;for(i=1;i<cnt;i++) if(w[++tot]=b[idx(o[i])],id[i]=tot,o[i+1]>o[i]+1){//离散化后分情况讨论
		if(o[i+1]-1-(o[i]+1)>=n) w[++tot]=R.Q(1,n);//如果长度超过 n ，其实就是整个 bi 的最小值
		else if((l=idx(o[i]+1))<=(r=idx(o[i+1]-1))) w[++tot]=R.Q(l,r);//如果在一段区间内
		else w[++tot]=min(R.Q(l,n),R.Q(1,r));//如果跨越了两个区间
	}w[++tot]=b[idx(o[cnt])],id[cnt]=tot;
	#define LW(x) (lower_bound(o+1,o+cnt+1,x)-o)
	for(S.B(),i=1;i<=q;i++) c[i].l=LW(c[i].l),c[i].r=LW(c[i].r),c[i].op&1?S.U(id[c[i].l],id[c[i].r],c[i].x):
	writeln(S.Q(id[c[i].l],id[c[i].r]));return 0;
}
```



---

## 作者：Suzt_ilymtics (赞：1)



## Description

题面：[CF803G Periodic RMQ Problem](https://www.luogu.com.cn/problem/CF803G)

> 给你一个序列 $a$ 让你支持: 区间赋值;询问区间最小值
我们觉得这个问题太水了,所以我们不会给你序列 $a$
而是给你序列一个长度为 $n$ 的序列 $b$ ,把 $b$ 复制粘贴 $k$ 次就可以得到 $a$
$n \le 10^5,k \le 10^4,q \le 10^5,b_i \le 10^9$
$1 \le l \le r \le n \times k$

## Solution

维护的线段树操作不难，麻烦的地方在于对原序列的处理，理解思想后自己完全可以yy出来。

看到 “区间覆盖，区间最小值” ，这不板子？
但是，序列长度可是 $n \times k = 10^9$ 啊。

发现询问涉及到的点只有 $10^5$ 级别，考虑进行离散化处理，只保留对答案有贡献的信息。

注意：对答案有贡献的信息不仅仅是询问涉及到的点，还有相邻的两个涉及到的点的区间也对答案有贡献
（因为这个区间内的最小值可能比两个端点更小）。

蓝色箭头是询问涉及过的点，相邻的两个涉及过的点的区间被压缩成一个点来处理（如果相邻两个涉及过的点之间没有区间就不压缩）。

把这两种点都放进一个新的序列（红色序列），然后在新的序列上进行修改查询操作即可。
注意映射好询问涉及到的点在红色序列中的位置。

![](https://ae02.alicdn.com/kf/U4277bc0b68ba45a5a94e523ea4b9d420j.jpg)

注意将区间压缩成一个点时的处理：

- 如果区间长度超过 $n$，直接加入原来整段区间的最小值（~~但是数据没卡这个地方~~）
- 如果在同一个区间内，加入这个区间内的最小值
- 如果跨越了两个区间，加入区间 $[1, r]$ 和 $[l, n]$ 的最小值

这种做法在复杂度和空间消耗上都比较优秀。

剩下的看代码吧，重要步骤都有注释，如果有不懂的可以在评论区提出。

## Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 2e5+5; // 注意开的数组大小（自己算算应该用多少 
const int INF = 1e9+7;
const int mod = 1e9+7;

struct Ques{
    int opt, l, r, val;
}q[MAXN];

int n, K, m;
int a[MAXN], b[MAXN << 1], Cnt = 0, pre[MAXN << 1];
int date[MAXN], cnt = 0, date_num = 0;

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

struct Big_Seg{ // 采用结构体，码量会更少哦 
    #define lson i << 1
    #define rson i << 1 | 1
    struct Tree{
        int min, lazy;
    }tree[MAXN << 3];
    void Push_up(int i) { tree[i].min = min(tree[lson].min, tree[rson].min); }
    void Push_down(int i) {
        if(tree[i].lazy) {
            tree[lson].lazy = tree[rson].lazy = tree[i].lazy;
            tree[lson].min = tree[rson].min = tree[i].lazy;
            tree[i].lazy = 0;
        }
    }
    void Build(int i, int l, int r) { //两个建树分别给两个线段树用 
        if(l == r) { tree[i].min = b[l]; return ; }
        int mid = (l + r) >> 1;
        Build(lson, l, mid), Build(rson, mid + 1, r);
        Push_up(i);
    }
    void Build0(int i, int l, int r) {
        if(l == r) { tree[i].min = a[l]; return ; }
        int mid = (l + r) >> 1;
        Build0(lson, l, mid), Build0(rson, mid + 1, r);
        Push_up(i);
    }
    void Change(int i, int l, int r, int L, int R, int k) {
        if(L <= l && r <= R) {
            tree[i].min = tree[i].lazy = k;
            return ;
        }
        Push_down(i);
        int mid = (l + r) >> 1;
        if(mid >= L) Change(lson, l, mid, L, R, k);
        if(mid < R) Change(rson, mid + 1, r, L, R, k);
        Push_up(i);
    }
    int Get_min(int i, int l, int r, int L, int R) {
        if(L <= l && r <= R) return tree[i].min;
        Push_down(i);
        int mid = (l + r) >> 1, ans = INF;
        if(mid >= L) ans = min(ans, Get_min(lson, l, mid, L, R));
        if(mid < R) ans = min(ans, Get_min(rson, mid + 1, r, L, R));
        return ans;
    }
}Seg[2];

int main()
{
    n = read(), K = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    Seg[0].Build0(1, 1, n); // 先对给定的小序列建树 
    m = read();
    for(int i = 1; i <= m; ++i) {
        q[i].opt = read(), q[i].l = read(), q[i].r = read();
        date[++ cnt] = q[i].l, date[++ cnt] = q[i].r;
        if(q[i].opt == 1) q[i].val = read();
    }
    sort(date + 1, date + cnt + 1); date[0] = -INF;
    for(int i = 1; i <= cnt; ++i) if(date[i] != date[i - 1]) date[++ date_num] = date[i]; // 离散化 
    
    //一下是构造新序列b过程（即图中的红色序列 
    for(int i = 1; i < date_num; ++i) {
        if(date[i] % n == 0) b[++Cnt] = a[n];
        else b[++Cnt] = a[date[i] % n];
        pre[i] = Cnt; // 进行第二次映射的处理 
        if(date[i + 1] > date[i] + 1){
            if((date[i + 1] - 1) - (date[i] + 1) >= n) { // 压缩区间长度超过 n 时 
                b[++Cnt] = Seg[0].tree[1].min;
                continue;
            }
            int l = (date[i] + 1) % n, r = (date[i + 1] - 1) % n; //映射到复制前的序列中的位置 
            if(l == 0) l = n;
            if(r == 0) r = n;
            if(l <= r) b[++Cnt] = Seg[0].Get_min(1, 1, n, l, r); // 在一个区间内 
            else b[++Cnt] = min(Seg[0].Get_min(1, 1, n, 1, r), Seg[0].Get_min(1, 1, n, l, n)); // 不在一个区间内，用两段区间合并 
        }
    }
    if(date[date_num] % n == 0) b[++Cnt] = a[n];
    else b[++Cnt] = a[date[date_num] % n];
    pre[date_num] = Cnt;
    
    for(int i = 1; i <= m; ++i) { 
        q[i].l = lower_bound(date + 1, date + date_num + 1, q[i].l) - date; // 询问的点向离散化后映射 
        q[i].r = lower_bound(date + 1, date + date_num + 1, q[i].r) - date;
        q[i].l = pre[q[i].l], q[i].r = pre[q[i].r]; // 向b序列中的映射 
    }
    Seg[1].Build(1, 1, Cnt); //对 b序列建树 
    for(int i = 1; i <= m; ++i) { //直接修改+查询即可 
        if(q[i].opt == 1) Seg[1].Change(1, 1, Cnt, q[i].l, q[i].r, q[i].val);
        else printf("%d\n", Seg[1].Get_min(1, 1, Cnt, q[i].l, q[i].r));
    }
    return 0;
}

```

## 总结

对于所维护的区间过大时，考虑离散化只留下有用的信息来达到节约空间的目的。

---

## 作者：Cry_For_theMoon (赞：0)

[传送门](https://codeforces.com/contest/803/problem/G)

##### 前言：

CF 2300*，洛谷黑，我怀疑有一个在骗我。~~我觉得是CF.~~

远古时代的 edu 真毒瘤~~（等等现在好像更毒瘤）~~

##### 题意：

给定 $n,k$ 和 $b=[b_1,b_2,...,b_n]$. $a$ 是正整数序列 $b$ 依次复制 $k$ 遍并拼接在一起得到的。

请支持对 $a$ 的区间赋值（推平），区间 $\min$ 查询。共 $q$ 次操作。

$n,q\le10^5,k\le 10^4,b_i \le 10^9$

##### 分析：

如果没有复制 $k$ 次那么这将是个大水题，可惜没不得。

容易想到中间有很多连续的相同的块，自然地想到类似分块的思想：把每 $n$ 个看成一块。对于一次针对于 $[l,r]$ 的修改/查询，中间那些连续块快速处理，$l$ 所在块和 $r$ 所在块单独处理。

看上去，对于中间块，开一个长度为 $k$ 的线段树，每一个元素代表每一**块**整体的最小值，维护若干连续块的最小值。对于散块，开 $k$ 个长度为 $n$ 的线段树，第 $i$ 个线段树里每个元素代表第 $i$ 块里的一**个**值，维护块内连续段的最小值。然后我们就做完了。

但是很快问题接踵而至：

- 开 $k$ 个大小为 $n$ 的线段树显然 MLE

针对这点，容易想到动态开点。但是这题初始不是全为 $0$. 无法从零开始动态开点。实际上你发现这又有点像主席树里的动态开点，先写一颗初始线段树根为 $root_0$维护 $b_1,...,b_n$，然后对于每一个真正要用到的线段树，$root_i$ 复制 $root_0$ 的信息（即只有最上面的根不同）。然后这里显然不能标记永久化，我们不得已在每次 pushdown 的时候新建两个儿子节点（当然还是复制原来儿子节点的信息）。来写这题的~~除了我~~应该都已经会主席树了，所以理解起来并不难（也不太好解释）。

容易发现这样每次还是会多 $O(\log_2 n)$ 级别的节点只不过常数有点过大。所以最后这里的动态开点线段树部分节点要设到 $10^7$ 级别。

- 散块可能在后面的操作里会被当成中间块覆盖，需要更新动态开点线段树里的信息。

为了解决这个问题，不难想到再开一颗长度为 $k$ 的线段树（普通的就行）。维护每一**块**的标记。标记为 $k$ 则代表一整块被覆盖上了 $k$，标记为 $\infty$ 代表这一块上面有若干次散块修改。每次需要修改/查询散块的时候，我们先看其标记是否不为 $\infty$，如果不为，则在动态开点线段树内将这一块全部修改为 $k$（操作众多也是导致空间常数大的一方面原因），同时重新将其标志置为 $\infty$.

这样就在 $O(m \log n)$ 的时间内解决了问题。

~~我怎么知道常数到底有多大~~

~~4.32kb代码倾情献上~~

 ```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
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
typedef double db;
using namespace std;
const int MAXN=1e5+10,MAXK=1e4+10,MAXM=1e7+10,INF=2e9,SIGN=2e9;

struct DynamicSegmentTree{
	int lc[MAXM],rc[MAXM],val[MAXM],tag[MAXM],tot;
	il int node(){return ++tot;}
	il void copy(int from,int to){lc[to]=lc[from],rc[to]=rc[from],val[to]=val[from],tag[to]=tag[from];}
	void pushup(int x){val[x]=min(val[lc[x]],val[rc[x]]);}
	void pushdown(int x){
		//新建节点 
		int tmp;
		tmp=lc[x];lc[x]=node();copy(tmp,lc[x]);
		tmp=rc[x];rc[x]=node();copy(tmp,rc[x]);
		//传递标记
		if(!tag[x])return;
		val[lc[x]]=val[rc[x]]=tag[x];tag[lc[x]]=tag[rc[x]]=tag[x];tag[x]=0; 
	}
	void update(int x,int l,int r,int ql,int qr,int v){
		if(ql<=l && qr>=r){val[x]=tag[x]=v;return;}
		pushdown(x);
		int mid=(l+r)>>1;
		if(ql<=mid)update(lc[x],l,mid,ql,qr,v);
		if(qr>mid)update(rc[x],mid+1,r,ql,qr,v);
		pushup(x);
	}
	int query(int x,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r){return val[x];}
		pushdown(x);
		int mid=(l+r)>>1,ret=INF;
		if(ql<=mid)ret=min(ret,query(lc[x],l,mid,ql,qr));
		if(qr>mid)ret=min(ret,query(rc[x],mid+1,r,ql,qr));
		return ret;
	}
}small; //对块内的动态开点线段树维护 
struct SegmentTree{
	int lc[MAXK<<2],rc[MAXK<<2],tag[MAXK<<2],val[MAXK<<2];
	void pushup(int x){val[x]=min(val[lc[x]],val[rc[x]]);}
	void pushdown(int x){if(!tag[x])return;
		val[lc[x]]=val[rc[x]]=tag[lc[x]]=tag[rc[x]]=tag[x];
		tag[x]=0;
	}
	void build(int x,int l,int r){
		if(l==r)return;
		int mid=(l+r)>>1;
		lc[x]=x<<1;rc[x]=lc[x]|1;
		build(lc[x],l,mid);build(rc[x],mid+1,r);
	}
	void update(int x,int l,int r,int ql,int qr,int v){
		if(ql<=l && qr>=r){val[x]=tag[x]=v;return;}
		pushdown(x);
		int mid=(l+r)>>1;
		if(ql<=mid)update(lc[x],l,mid,ql,qr,v);
		if(qr>mid)update(rc[x],mid+1,r,ql,qr,v);
		pushup(x);
	}
	int query(int x,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r){return val[x];}
		pushdown(x);
		int mid=(l+r)>>1,ret=INF;
		if(ql<=mid)ret=min(ret,query(lc[x],l,mid,ql,qr));
		if(qr>mid)ret=min(ret,query(rc[x],mid+1,r,ql,qr));
		return ret;
	}
}big,tag; //对块整体的维护和块的标记用普通线段树 
int n,k,b[MAXN],q,op,l,r,x;
int root[MAXK],initval=INF;
void update(int x,int l,int r,int val=-1){
	//check
	int v=tag.query(1,1,k,x,x);
	if(v!=SIGN){
		tag.update(1,1,k,x,x,SIGN);
		big.update(1,1,k,x,x,v);
		small.update(root[x],1,n,1,n,v);
	}
	if(val==-1)return;
	//cover
	small.update(root[x],1,n,l,r,val);
	v=small.query(root[x],1,n,1,n);
	big.update(1,1,k,x,x,v);
}
int main(){
	small.val[0]=INF;
	scanf("%d%d",&n,&k);
	rep(i,1,n){
		scanf("%d",&b[i]);initval=min(initval,b[i]);
	}
	big.build(1,1,k);tag.build(1,1,k);
	tag.update(1,1,k,1,k,SIGN); //开始时都未被覆盖上标记
	big.update(1,1,k,1,k,initval); //每一块的初始最小值 
	root[0]=small.node();
	rep(i,1,n){small.update(root[0],1,n,i,i,b[i]);}
	rep(i,1,k){
		root[i]=small.node();
		small.copy(root[0],root[i]);
	}
	scanf("%d",&q);
	//线段树优化分块(???) 
	rep(i,1,q){
		scanf("%d%d%d",&op,&l,&r);
		int L=(l+n-1)/n,R=(r+n-1)/n,ans=INF; //l,r所在大块
		//两边块暴力修改 
		if(op==1){scanf("%d",&x);
			if(L+1<=R-1){
				big.update(1,1,k,L+1,R-1,x);
				tag.update(1,1,k,L+1,R-1,x);
			}
			if(L==R){ 
				update(L,(l-1)%n+1,(r-1)%n+1,x);
			}else{
				update(L,(l-1)%n+1,n,x); 
				update(R,1,(r-1)%n+1,x);
			}
		}else{
			if(L+1<=R-1){ans=min(ans,big.query(1,1,k,L+1,R-1));}
			if(L==R){
				update(L,(l-1)%n+1,(r-1)%n+1);
				ans=min(ans,small.query(root[L],1,n,(l-1)%n+1,(r-1)%n+1));
			}else{
				update(L,(l-1)%n+1,n);
				ans=min(ans,small.query(root[L],1,n,(l-1)%n+1,n));
				update(R,1,(r-1)%n+1);	
				ans=min(ans,small.query(root[R],1,n,1,(r-1)%n+1));
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
 ```



---

