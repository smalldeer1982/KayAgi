# [COCI 2015/2016 #7] Prokletnik

## 题目描述

定义魔法序列为满足所有元素的大小均在第一个元素和最后一个元素之间的序列。

现有一个元素个数为 $N$ 的数组 $a$。给出 $Q$ 次询问 $L,R$，求 $a$ 中下标在 $[L,R]$ 之间的最长的子魔法区间。

## 说明/提示

**【数据规模与约定】**

- 对于 $50\%$ 的数据，$N,Q \le 3 \times 10^4$。
- 对于 $100\%$ 的数据，$1 \le N,Q \le 5 \times 10^5$，$1 \le a_i \le 10^9$，$1 \le L \le R \le N$。

**【提示与说明】**

**题目译自 [COCI 2015-2016](https://hsin.hr/coci/archive/2015_2016/) [#7](https://hsin.hr/coci/archive/2015_2016/contest7_tasks.pdf) _Task 6 Prokletnik_。**

**本题分值按 COCI 原题设置，满分 $160$。**

## 样例 #1

### 输入

```
5
5 4 3 3 2
3
1 2
1 1
2 4```

### 输出

```
2
1
3```

## 样例 #2

### 输入

```
6
6 6 5 1 6 2
3
4 5
4 6
1 4```

### 输出

```
2
2
4```

# 题解

## 作者：DaiRuiChen007 (赞：15)

# 洛谷 P8037 题解

[$\text{Link}$](https://www.luogu.com.cn/problem/P8037)

## 思路分析

好题，考虑对询问离线并按右端点排序

我们先考虑右端点是最大值的情况，反过来的只需要对每个数取反再做一次

记录每个点为区间左端点能够达到最远的右端点

考虑加入新的一个点 $a_r$，那么我们需要更新某一段区间 $[l,r]$ 中的数的右端点为 $r$，其中 $l$ 为满足 $l\le r$ 且 $a_{l-1}>a_r$ 的最大整数

为了快速求出 $l$，我们可以维护一个递减的单调栈

接下来考虑 $[l,r]$ 区间内有哪些点的右端点可以被更新为 $r$，假设某个点 $a_x$ 的右端点可以被更新为 $r$，当且仅当：
$$
\forall k\in[x,r],a_k\ge a_x
$$
那么如果加入 $a_r$，每一个满足 $a_x> a_r$ 的点以后就一直不能被更新了，所以我们再维护一个递增的单调栈，每次弹栈弹掉的这些元素就不能再更新右端点

考虑对以上操作用线段树维护以下信息：

- 维护当前区间可以使 $r$ 作为右端点并形成合法区间的第一个点，如果没有则设为 $0$
- 每个点作为左端点能获得的最大区间长度的最大值
- 区间更新右端点的 LazyTag

注意那些不能更新右端点的点依然可能对答案做出贡献

时间复杂度 $\Theta(n\log n)$

> 总结：
>
> 离线按右端点排序是处理区间问题的一个常用 trick（就是不知道本题强制在线怎么做。。。）
>
> 把所有数取反再跑一遍的 trick 看起来好像也还挺高妙的
>
> 有些区间问题可以固定右端点然后考虑左端点的贡献，这个做法好像我还没见过

一些实现的细节请看代码

### 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+1;
int n,m;
class SegmentTree {
	private:
		struct node {
			int pos,len,tag;
			/*
			 * pos: 当前最左合法左端点 
			 * len: 当前区间最大长度
			 * tag: 区间更新右端点的懒标记 
			 */
		}	tree[MAXN<<2];
		inline int left(int x) {
			return x<<1;
		}
		inline int right(int x) {
			return x<<1|1;
		}
		inline void pushup(int pos) {
			tree[pos].len=max(tree[left(pos)].len,tree[right(pos)].len);
			tree[pos].pos=(!tree[left(pos)].pos)?tree[right(pos)].pos:tree[left(pos)].pos;
		}
		inline void pushdown(int pos) {
			//用pos作为右端点更新两个区间的最大长度 
			if(!tree[pos].tag) return ;
			tree[left(pos)].tag=max(tree[left(pos)].tag,tree[pos].tag);
			tree[right(pos)].tag=max(tree[right(pos)].tag,tree[pos].tag);
			if(tree[left(pos)].pos) {
				tree[left(pos)].len=max(tree[left(pos)].len,tree[pos].tag-tree[left(pos)].pos+1);
			}
			if(tree[right(pos)].pos) {
				tree[right(pos)].len=max(tree[right(pos)].len,tree[pos].tag-tree[right(pos)].pos+1);
			}
			tree[pos].tag=0;
		}
	public:
		inline void Build(int l=1,int r=n,int pos=1) {
			if(l==r) {
				tree[pos].pos=tree[pos].len=tree[pos].tag=0;
				return ;
			}
			int mid=(l+r)>>1;
			Build(l,mid,left(pos));
			Build(mid+1,r,right(pos));
			pushup(pos);
		}	
		inline void ModifyL(int u,int k,int l=1,int r=n,int pos=1) {
			//修改左端点是否合法 
			if(l==r) {
				tree[pos].pos=k;
				return ;
			}
			pushdown(pos);
			int mid=(l+r)>>1;
			if(u<=mid) ModifyL(u,k,l,mid,left(pos));
			else ModifyL(u,k,mid+1,r,right(pos));
			pushup(pos);
		}
		inline void ModifyR(int ul,int ur,int k,int l=1,int r=n,int pos=1) {
			//区间修改右端点 
			if(ul<=l&&r<=ur) {
				if(tree[pos].pos) tree[pos].len=max(tree[pos].len,k-tree[pos].pos+1);
				tree[pos].tag=max(tree[pos].tag,k);
				return ;
			}
			pushdown(pos);
			int mid=(l+r)>>1;
			if(ul<=mid) ModifyR(ul,ur,k,l,mid,left(pos));
			if(mid<ur) ModifyR(ul,ur,k,mid+1,r,right(pos));
			pushup(pos);
		}
		inline int Query(int ql,int qr,int l=1,int r=n,int pos=1) {
			if(ql<=l&&r<=qr) return tree[pos].len;
			pushdown(pos);
			int mid=(l+r)>>1,res=0;
			if(ql<=mid) res=max(res,Query(ql,qr,l,mid,left(pos)));
			if(mid<qr) res=max(res,Query(ql,qr,mid+1,r,right(pos)));
			return res;
		}
}	S;
struct query {
	int l,id;
};
vector <query> q[MAXN];
int st1[MAXN],st2[MAXN],a[MAXN],ans[MAXN];
inline void solve() {
	st1[0]=st2[0]=0; //单调栈栈顶 
	S.Build();
	for(int i=1;i<=n;++i) {
		while(st1[0]&&a[st1[st1[0]]]<=a[i]) --st1[0];
		int l=st1[st1[0]]+1;
		st1[++st1[0]]=i;
		while(st2[0]&&a[st2[st2[0]]]>a[i]) {
			S.ModifyL(st2[st2[0]],0);
			//这个点以后都不能更新新的右端点了 
			--st2[0];
		}
		st2[++st2[0]]=i;
		S.ModifyL(i,i);
		S.ModifyR(l,i,i);
		for(auto qry:q[i]) {
			ans[qry.id]=max(ans[qry.id],S.Query(qry.l,i));
		}
	}
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;++i) {
		int l,r;
		scanf("%d%d",&l,&r);
		q[r].push_back((query){l,i});
	}
	solve();
	for(int i=1;i<=n;++i) a[i]*=-1;
	solve();
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：fight_for_humanity (赞：8)

**提供一种树状数组的解法**。

[题目链接](https://www.luogu.com.cn/problem/P8037)。

[Better experience](https://www.cnblogs.com/fight-for-humanity/p/18381413)。

#### 题意简述
一个好区间定义为：这个区间的两个端点值为整个区间的最大值和最小值。
有一段长为 $n(1 \le n \le 500000)$ 的序列，现在提出 $Q(Q \le 500000)$ 个询问，每次有 $L,R(1 \le L \le R \le N)$ 表示询问的区间。
求出 $[L,R]$ 中最长的子区间，是好区间。

#### 题目分析

套路地，我们可以离线，按照右端点排序。那么类似增量法，每次加入一个 $r$，维护答案并查询。

我一开始的想法：单调栈预处理出向左、向右第一个大于、小于的位置，然后二维偏序，对于当前的 $r$ 每个 $i$ 维护的是 $[i,r]$ 这个区间的答案。但不知道怎么继续，难点在于每一个偏序找到的点都要大范围地更新答案。

首先令右端点的值为最大值，相反的将每个 $a_i$ 取反再跑一遍即可。我们维护一个单调递减的栈，表示这些可以被 $i$ 以及后续更新到的位置。和其他题解中的方式基本相同，但我们先思考线段树到底是怎么维护的。是不是对于栈中的点的存在与否进行 $pos$ 标记（即修改），再以打 $tag$ 标记的方式去将答案放到线段树的节点上。既然是以栈中元素作为中心，为什么不直接开一个树状数组去维护栈中元素？

具体实现如下：
1. 维护一个树状数组 $R$，表示对应的栈中的元素作为左端点时的最大右端点，维护前缀最大值。
1. 维护一个树状数组 $ans$，表示 $i$ 节点为左端点的最大答案，维护后缀最大值。
1. 每一次要加入当前的 $a_i$，将栈中不再会被更新的元素弹掉，并将其答案 `R.query(top)-st[top]+1` 加入到 $ans$ 中。
1. 然后将 $i$ 入栈，二分找到栈中的第一个合法位置，并修改 $R$ 和 $ans$。由于 $R$ 维护的是前缀最值，修改是改其后面的部分，故栈中所有要被更新的左端点都被更新了。
1. 处理询问时，令栈中第一个大于等于当前询问的位置为 $it$。由于我们先前更新时对于 $R$ 的更新时没有全部都更新到 $ans$ 上去，那么更新答案要对 $ans$ 的最值和 $it$ 的答案 `R.query(it) - st[it] + 1` 取一个最大值，类似于一个延迟更新。

时间复杂度 $\Theta ((n+q)\cdot \log n)$，细节见代码。

#### CODE

```cpp
#include<bits/stdc++.h>
#define debug() cerr<<"Line:"<<__LINE__<<endl
using namespace std;
typedef pair<int,int> pii;
const int N = 500010;
int n,a[N],res[N],q;
vector<pii> e[N];
int st[N],top;
int l[N];

template <int op = 1>
struct Bit{
	int c[N];
	#define lowbit(a) (a&(-a))
	void init(){
		memset(c,0,sizeof c);
	}
	void add(int x,int v){
		for(int i = x;0 < i && i <= n;i += op * lowbit(i))c[i] = max(c[i],v);
	}
	int query(int x){
		int res = 0;
		for(int i = x;0 < i && i <= n;i -= op * lowbit(i))res = max(c[i],res);
		return res;
	}
};
Bit<1> R;
Bit<-1> ans;

void solve(){
	R.init(),ans.init();
	top = 0;
	for(int i = 1;i<=n;++i){
		while(top && a[st[top]] <= a[i])--top;
		l[i] = st[top]+1;
		st[++top] = i;
	}
	top = 0;
	for(int i = 1;i<=n;++i){
		while(top && a[st[top]] > a[i]){
			int res = R.query(top) - st[top] + 1;
			ans.add(st[top],res);
			--top;
		}
		st[++top] = i;
		int it = lower_bound(st+1,st+top+1,l[i])-st;
		R.add(it,i), ans.add(st[it],i-st[it]+1);
		for(pii p : e[i]){
			int it = lower_bound(st+1,st+top+1,p.first)-st;
			int fi = ans.query(p.first), se = R.query(it) - st[it] + 1;
			res[p.second] = max(res[p.second],max(fi,se));	
		}
	}
}
//#define printf printf(">>>> "),printf
int main(){
	scanf("%d",&n); for(int i = 1;i<=n;++i)scanf("%d",&a[i]);
	scanf("%d",&q); for(int i = 1,l,r;i<=q;++i){
		scanf("%d%d",&l,&r);
		e[r].push_back({l,i});
	}
	solve();
	for(int i = 1;i<=n;++i)a[i] = -a[i];
	solve();
	for(int i = 1;i<=q;++i)printf("%d\n",res[i]);
	return 0;
}
```

#### 反思 & 总结

**trick：**

1. 离线按右端点排序是处理区间问题。
1. 对于两个性质相反的东西进行统计可以把所有数取反再跑一遍。
1. 用树状数组维护栈。

---

## 作者：zsq147258369 (赞：7)

因为魔法序列的左右端点大小不定，我这里是左端点较小。但可以将询问和序列一起翻转，或用 $mx$ 减一下原序列，再跑一遍即可。

假设我们可以求出对于每个点作为左端点，向右最大可以的右端点，且限定右端点最大为 $i$，就可以求出答案。

那么对于询问 $(l_i,r_i)$，查询对于 $j\in[l_i,r_i]$，限定 $j$ 为左端点，右端点最大为 $r_i$ 的最大长度。

限定右端点可以从小到大限定。当前限定 $i$ 为最长的右端点，求出小于 $i$ 的点作为左端点的最长长度。离线查询即可。

考虑求出每个点作为左端点的最大右端点。搞一个不下降的单调栈，对于加入 $i$，有一下两种情况。

* $a_i\ge a_{k_{top}}$


$i$ 直接加入栈中，然后对于栈中元素位置大于 $to_i$（比 $a_i$ 大且位置比 $i$ 小的最后一个元素位置），把他们的的右端点置为 $i$，可以用一棵与栈中位置一一对应的线段树维护他们的魔法序列长度最大值。

* $a_i<a_{k_{top}}$


$k_{top}$ 的右端点不会再更新，把他踢到另一棵与原序列位置一一对应的线段树，然后要在第一棵树中把 $top$ 位置清空。一直踢到 $a_i\ge a_{k_{top}}$ 再加入 $i$。

求 $to_i$ 跑一次单调栈即可。

设当前处理到 $i$，对于询问 $(l,i)$，分别在两颗线段树中查询 $(l,i)$ 区间的最大值，注意第一棵线段树查询时用 `lower_bound` 求出节点在栈中的位置。

# $code$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+50;

struct ask
{
	int l,r,id;
	
	friend bool operator<(ask a,ask b)
	{
		return a.r<b.r;
	}
}p[N];

int n,a[N],mx,q,k[N],ans[N],top,to[N],A[N<<2],B[N<<2],la[N<<2],qu[N],tail;

void cc()
{
	memset(k,0,sizeof k);top=tail=0;
	memset(to,0,sizeof to);
	memset(A,0,sizeof A);
	memset(B,0,sizeof B);
	memset(la,0,sizeof la);
	memset(qu,0,sizeof qu);
}

#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)

void down(int x,int l,int r)
{
	if(la[x])
	{
		la[ls]=la[rs]=la[x];
		A[ls]=la[x]-qu[l]+1;
		A[rs]=la[x]-qu[mid+1]+1;
		la[x]=0;
		return;
	}
}

void up(int x,int f)
{
	if(!f)A[x]=max(A[ls],A[rs]);
	else B[x]=max(B[ls],B[rs]);
}

void clear(int x,int l,int r,int d)
{
	if(l==r)
	{
		A[x]=0;
		return;
	}
	down(x,l,r);
	if(d<=mid)clear(ls,l,mid,d);
	else clear(rs,mid+1,r,d);
	up(x,0);
}

int find(int x,int l,int r,int L,int R)
{
	if(L<=l&&R>=r)return A[x];
	int ans=0;down(x,l,r);
	if(L<=mid)ans=max(ans,find(ls,l,mid,L,R));
	if(R>mid)ans=max(ans,find(rs,mid+1,r,L,R));
	return ans;
}

void add(int x,int l,int r,int d,int y)
{
	if(l==r)
	{
		B[x]=y;
		return;
	}
	if(d<=mid)add(ls,l,mid,d,y);
	else add(rs,mid+1,r,d,y);
	up(x,1);
}

void insert(int x,int l,int r,int L,int R,int d)
{
	if(L<=l&&R>=r)
	{
		A[x]=d-qu[l]+1;
		la[x]=d;
		return;
	}
	down(x,l,r);
	if(L<=mid)insert(ls,l,mid,L,R,d);
	if(R>mid)insert(rs,mid+1,r,L,R,d);
	up(x,0);
}

int get(int x,int l,int r,int L,int R)
{
	if(L<=l&&R>=r)return B[x];
	int ans=0;down(x,l,r);
	if(L<=mid)ans=max(ans,get(ls,l,mid,L,R));
	if(R>mid)ans=max(ans,get(rs,mid+1,r,L,R));
	return ans;
}

void sol()
{
	for(int i=n;i>=1;i--)
	{
		while(top&&a[i]>a[k[top]])to[k[top--]]=i;
		k[++top]=i;
	}
	for(int i=1,j=1;i<=n;i++)
	{
		while(tail&&a[qu[tail]]>a[i])
		{
			add(1,1,n,qu[tail],find(1,1,n,tail,tail));
			clear(1,1,n,tail);
			tail--;
		}
		qu[++tail]=i;
		int t=upper_bound(qu+1,qu+1+tail,to[i])-qu;t=max(t,1);
		insert(1,1,n,t,tail,i);
		while(j<=q&&p[j].r==i)
		{
			ans[p[j].id]=max(ans[p[j].id],get(1,1,n,p[j].l,p[j].r));
			int t=lower_bound(qu+1,qu+1+tail,p[j].l)-qu;
			ans[p[j].id]=max(ans[p[j].id],find(1,1,n,t,tail));
			j++;
		}
	}
}

main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mx=max(a[i],mx);
	cin>>q;
	for(int i=1;i<=q;i++)cin>>p[i].l>>p[i].r,p[i].id=i;
	sort(p+1,p+1+q);
	sol();
	for(int i=1;i<=n;i++)a[i]=mx-a[i]+1;
	cc();sol();
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}
```

---

## 作者：Feyn (赞：6)

[link](https://www.luogu.com.cn/problem/P8037)

一道很好的线段树题目。

题外话：今天上午，全宇宙内最弱的辣鸡 Feyn 再一次和正解擦肩而过，下午这个蒟蒻看题解甚至没有看懂题解的写法（[参考题解链接](https://www.cnblogs.com/nightsky05/p/15162746.html)，我实在没看出来它的两棵线段树咋维护的，为啥觉得它只写了一棵呢，果然我还是太弱了），于是这个连题解都看不懂的菜鸡花了一下午时间研究了一种低效但比较清晰的写法，希望可以提供一些帮助（虽然觉得应该不会有人需要这篇题解，因为大家看完那篇题解应该就都会了）。

本人在考场上想出了一个 $O(N^2)$ 的做法，对于每一个区间，枚举哪个点作为答案区间的右端点，然后考虑如何选择左端点使这个区间尽量的长。分两种情况，假如希望右端点是区间的最小值，那么显然选中的左端点应该在上一个比这个右端点小的位置的后面。同时由于规定了左端点是区间的最大值，那么这个区间内不应该出现比左点更大的值，所以左端点不应该比当前询问区间的最大值的位置还靠左。两个限制需要同时满足，所以取较大值，和枚举的这个右端点一起去更新答案即可。左大右小也是一样。由于呢写得太丑了考场上只混到了 20 分，就很悲惨。

正解其实和上面的方法有共通之处。还是先考虑左小右大（另一种情况把每个数取反再跑一次即可），由于在线维护似乎比较麻烦，所以可以把所有询问离线下来然后按右端点排序，每次加入一个右端点。按照惯常的思路应该有一个数据结构，数据结构上每个点的值代表这个点作为左端点时最大的区间长度，然后查询这个询问区间的答案就只需要查询数据结构中询问区间的最大值就可以啦。这样显然是正确的，因为所有右端点大于当前询问的右端点的区间都还没有被加入，而所有左端点小于询问的左端点的区间无法被访问，所以这个思路是正确的。

但问题来了，如何维护这个东西呢。

显然有些位置的答案是不会变化的，因为变化的位置需要满足一个条件，即这个位置和当前枚举到的右端点可以形成一个合法的区间（为了叙述方便，一个魔法序列称为一个合法的区间）。这需要满足什么条件呢，区间内不能有比当前右端点大的，也不能有比左端点小的。假如当前的右端点是 $x$ ，那么一个合法的 $y$ 需要满足 $\forall y\le i\le x,a_y\le a_i\le a_x $。有人说这不废话吗，那么我们可以换一种表示方式。假如 $px$ 是 $x$ 之前第一个比它大的数的位置，$py$ 是 $y$ 之后第一个比它小的位置，那么有 $y\ge px+1,x\le py-1$。这就是单调栈的节奏了。对于后面的那个限制 $x\le py-1$，可以用单调栈来维护，用简单的方式使得栈内所有元素都符合这个条件，这样一来可能被更新的位置就是那些在栈内的、而且满足 $y\ge px+1$ 的那些元素。由于栈是上大下小的结构，根据前面的条件，可能被更新的元素实际上就是栈内某个位置（二分即可）到栈顶的所有元素，用线段树更新即可。

那那些不会被更新的位置咋办呢？可以发现如果之前存在一个 $x'\ge py$，那么随着 $x$ 的增大，上面那个不等式会一直成立下去，所以这个位置就再也不会被更新了。于是就可以把那些位置的数丢出来装在另一棵线段树内查询即可。那如何找出这些位置呢？上面说了维护单调栈的时候不是要弹出元素吗，弹出的每一个元素都是不会被更新的啊。

再补充说明一点上面那个维护栈内答案的线段树。由于元素间的实际下标可能并不连续，我在这棵树里用的是栈的下标。而这棵线段树支持的修改操作比较离谱，它要求支持的操作是这样的：由于树上的每片叶子都对应的原序列中的一个位置，而每次修改的时候都会给出另一个位置（也就是当前枚举的右端点），希望每个叶子的答案修改成所谓“另一个位置”减去叶子对应位置再加一（也就是叶子对应位置和右端点形成的序列长度）。lazy 标记好说，那如何更新答案呢？思考上面的那个柿子，所谓“另一个位置”是不变的，所以要求区间内的最大值，实际上就是要求某个区间内所有叶子对应位置的最小值，在结点内更新即可（写法为，每个节点直接继承左儿子的那个答案）。

我是把两棵线段树完全分开写的，感觉会更清晰一点，代码有注释。话说为啥我题解又写了一个小时。。。

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=500010;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline int max(int s1,int s2){
	return s1<s2?s2:s1;
}
inline int min(int s1,int s2){
	return s1<s2?s1:s2;
}

#define lc (wh<<1)
#define rc (wh<<1|1)
#define mid (t[wh].l+t[wh].r>>1) 
//x tree是废弃结点对应的线段树 
namespace x{
	struct node{
		int l,r,data;
	}t[N<<2];
	inline void pushup(int wh){
		t[wh].data=max(t[lc].data,t[rc].data);
	}
	inline void build(int wh,int l,int r){
		t[wh].l=l,t[wh].r=r,t[wh].data=0;
		if(l==r)return;
		build(lc,l,mid);
		build(rc,mid+1,r);
	}
	inline void update(int wh,int pl,int val){
		if(t[wh].l==t[wh].r){
			t[wh].data=val;return;
		}
		update(pl<=mid?lc:rc,pl,val); 
		pushup(wh);
	}
	inline int work(int wh,int wl,int wr){
		if(wl<=t[wh].l&&t[wh].r<=wr)return t[wh].data;
		int an=0;
		if(wl<=mid)an=max(an,work(lc,wl,wr));
		if(wr>mid)an=max(an,work(rc,wl,wr));
		return an;
	}
}
//y是栈内元素对应的线段树 
namespace y{
	struct node{
		int l,r;
		int lazy,data,pl_min;
		//data是区间内权值最大的左端点的权值
		//pl_min是区间内在原序列中对应位置最靠左的位置 
	}t[N<<2];
	inline void pushup(int wh){
		t[wh].pl_min=t[lc].pl_min;//直接继承左儿子 
		t[wh].data=max(t[lc].data,t[rc].data);
	}
	inline void pushnow(int wh,int val){
		if(val<=t[wh].lazy)return;
		t[wh].lazy=val;
		t[wh].data=max(t[wh].data,val-t[wh].pl_min+1);//更新答案 
	}
	inline void pushdown(int wh){
		if(t[wh].lazy){
			pushnow(lc,t[wh].lazy);
			pushnow(rc,t[wh].lazy);
			t[wh].lazy=0;
		}
	}
	inline void build(int wh,int l,int r){
		t[wh].l=l,t[wh].r=r,t[wh].data=t[wh].pl_min=t[wh].lazy=0;
		if(l==r)return;
		build(lc,l,mid);
		build(rc,mid+1,r);
	}
	inline void update(int wh,int pl,int val){
		if(t[wh].l==t[wh].r){
			t[wh].data=1;t[wh].lazy=0;t[wh].pl_min=val;return;
		}
		pushdown(wh);
		update(pl<=mid?lc:rc,pl,val);
		pushup(wh);
	}
	inline void change(int wh,int wl,int wr,int val){
		if(wl<=t[wh].l&&t[wh].r<=wr){
			pushnow(wh,val);return;
		}
		pushdown(wh);
		if(wl<=mid)change(lc,wl,wr,val);
		if(wr>mid)change(rc,wl,wr,val);
		pushup(wh);
	}
	inline int work(int wh,int wl,int wr){
		if(wl<=t[wh].l&&t[wh].r<=wr){
			return t[wh].data;
		}
		int an=0;pushdown(wh);
		if(wl<=mid)an=max(an,work(lc,wl,wr));
		if(wr>mid)an=max(an,work(rc,wl,wr));
		pushup(wh);return an;
	}
}
#undef lc
#undef rc
#undef mid


struct node{
	int l,r,id;
}c[N];
inline bool cmp(node s1,node s2){
	return s1.r<s2.r;
}
int m,n,a[N],an[N];

int st[N],top;
stack<int>st_max;
void solve(){
	a[0]=1e9+10;
	while(!st_max.empty())st_max.pop();
	st_max.push(top=0);
	x::build(1,1,m);y::build(1,1,m);
	for(int i=1,j=1;i<=m;i++){
		while(a[st_max.top()]<=a[i])st_max.pop();
		int pl=st_max.top();st_max.push(i);
		//find first one bigger than a[i]
		while(top&&a[st[top]]>a[i]){
			int now_pl=st[top--];
			int now_data=y::work(1,top+1,top+1);
			x::update(1,now_pl,now_data);
		}
		st[++top]=i;y::update(1,top,i);
		int fir=lower_bound(st+1,st+top+1,pl)-st;
		y::change(1,fir,top,i);
		//find ones smaller than a[i]
		while(j<=n&&c[j].r==i){
			int now_pl=lower_bound(st+1,st+top+1,c[j].l)-st;
			an[c[j].id]=max(an[c[j].id],y::work(1,now_pl,top));
			an[c[j].id]=max(an[c[j].id],x::work(1,c[j].l,c[j].r));
			j++;
		}
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)read(a[i]);
	read(n);
	for(int i=1;i<=n;i++){
		read(c[i].l);read(c[i].r);
		c[i].id=i;
	}
	sort(c+1,c+n+1,cmp);
	solve();
	for(int i=1;i<=m;i++)a[i]=-a[i];
	solve();
	for(int i=1;i<=n;i++)printf("%d\n",an[i]);
	
	return 0;
}
```

---

## 作者：luogubot (赞：5)

假设左端点是最小值，右端点是最大值，然后反转再做一遍。

直观上感觉不能在线段树上维护答案，所以尝试把询问离线扫描线。朴素地，令指针 $u$ 从左往右扫，同时对于每个 $i\leq u$ 维护 $f_i$ 表示以 $i$ 为左端点，右端点不超过 $u$ 的最大长度，则 $u=R$ 时回答询问 $[L,R]$ 的答案为 $\max_{i=L}^R\{f_i\}$。考虑 $u$ 向右移动一格时对 $f$ 的影响，预处理出 $l_i$ 表示 $i$ 左边第一个比 $a_i$ 大的位置，$r_i$ 表示 $i$ 右边第一个比 $a_i$ 小的位置，则 $u$ 能影响到 $f_i$ 当且仅当 $l_u\leq i$ 且 $r_i\ge u$。如果当前的 $u>r_i$，则之后的 $u$ 一定不能更新 $f_i$，相当于维护了一个单调栈，只有在栈中的元素 $i$ 的 $f_i$ 才可能更新，被弹出之后就不可能再更新了。对于 $u$ 的加入，找到栈顶的若干元素满足其大于 $l_u$，则这些 $f_i$ 都应该被更新为以 $u$ 为右端点的，不妨分析一下，栈中元素当前对应的右端点是分段的，且每个 $u$ 会添加至多一段，则暴力向前一段一段更新的次数均摊也是 $O(n)$。

于是思路就清晰了：预处理出 $l_i$。扫描线过程中维护一个不减的单调栈 $s_1$，其中的元素 $i$ 表示 $[i,u]$ 还没有出现 $<a_i$ 的，$f_i$ 还有可能更新，用一棵线段树 $T_1$ 来维护这些 $i$ 的 dp 值。$u$ 移动时更新栈顶所有 $>l_u$ 的 $i$ 的 dp 值，同段的更新是区间加相同的数。当一个 $i$ 从 $s_1$ 被弹出时，其 $f_i$ 不应该接受之后的更新，在 $T_1$ 上将 $f_i$ 设为 $-\inf$，并将其挪到另一棵线段树 $T_2$ 上。对于一个询问 $[L,R]$，在 $u=R$ 时查询 $T_1,T_2$ 上 $[L,R]$ 内的最大值。对段的维护另开一个栈 $s_2$ 即可。

复杂度 $O(n\log n)$，常数略大。

---

## 作者：hrgd (赞：3)

不妨设左小右大，然后反着扫一遍。

扫描线。对于每个右端点，它的每一个合法左端点都应该是后缀最小值，这形成一个单调栈。而单调栈中只有一个后缀能成为合法左端点，因为还要求右端点是区间最大值。

注意到一个点如果被弹出栈了，我们只需把它作为左端点的最长区间放入线段树即可，因为它再也不可能称为合法左端点了。对于栈中的元素我们则要维护其最远右端点，而由于每次更新一个后缀，于是也可以线段树维护。

查询分为两部分，对于不在栈中的只需线段树查询，对于在栈中的也是后缀查询，只是我们需要在线段树中多维护一个区间长度最大值即可。

时间复杂度线性对数。代码没什么细节，不放了（没写）。

---

## 作者：鱼跃于渊 (赞：2)

一道 ds 好题。  

## 解法

对于这种多组区间询问的问题，有一个技巧：  
我们离线所有询问，使用扫描线，枚举所有的 $r$，在此过程中使用某种数据结构维护 $f_l$（$1 \le l\le r,f_l$ 是以 $l$ 为左端点的最大答案）。  
而对于这种两端分别需要满足一个条件的问题，也有一个技巧：  
我们钦定右端点满足其中一个条件，求出此时所有问题的答案；再钦定右端点满足另一个条件，求出此时所有问题的答案，两者取最优。  

在这题中，我们钦定右端点为最大值，考虑加入一个数 $a_r$ 会产生什么影响。  
设 $f_l$ 为 $l$ 最远可以到达的右端点，没有则为 $0$。  
首先区间 $[l+1,r]$ 的 $f_i$ 可能更新为 $r$，其中 $l$ 为满足 $l<r$ 且 $a_l>a_r$ 的最大整数。  
我们可以维护一个递减的单调栈来快速求出这个 $l$。  
考虑有哪些 $f_i$ 不能更新为 $r$，显然对于一个点 $l$ 来说，它不能更新当且仅当 $\exist k\in[l,r],a_l>a_k$。  
我们可以维护一个递增的单调栈来快速求出这个 $l$，注意这些不能更新的点仍然可能对答案产生贡献。  

对于每个操作，我们开一颗线段树维护以下信息：  

- 当前区间能以 $r$ 为右端点且合法的第一个点，没有则为 $0$。  
- 每个点作为左端点的最大合法区间长度。  
- 更新右端点的懒标记。  
  
接下来考虑钦定右端点为最小值，其实我们只需要将所有数取反在跑一遍上述算法即可。  
时间复杂度 $O(n\log n)$，可以通过此题。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define all(x,l,r) &(x)[l],&(x)[r]+1
#define epb emplace_back
#define ls(i) (i<<1)
#define rs(i) (i<<1|1)
#define mid (((l)+(r))>>1)
const int N=5e5+5;
struct ques{
    int l,id;
    ques(int _l=0,int _id=0){
        l=_l;id=_id;
    }
};
struct tree{
    int p,len,tag;
}t[N<<2];
int n,m,a[N],ans[N];
int topl,topr,stl[N],str[N];
vector <ques> q[N];
void push_up(int i){
    t[i].len=max(t[ls(i)].len,t[rs(i)].len);
    t[i].p=(t[ls(i)].p?t[ls(i)].p:t[rs(i)].p);
}
void modify(int i,int tag){
    t[i].tag=max(t[i].tag,tag);
    if(t[i].p) t[i].len=max(t[i].len,t[i].tag-t[i].p+1);
}
void push_down(int i){
    if(!t[i].tag) return;
    modify(ls(i),t[i].tag);
    modify(rs(i),t[i].tag);
    t[i].tag=0;
}
void build(int i,int l,int r){
    t[i]={0,0,0};
    if(l==r) return;
    build(ls(i),l,mid);
    build(rs(i),mid+1,r);
    push_up(i);
}
void updatel(int nx,int l,int r,int i,int k){
    if(l==r){
        t[i].p=k;
        return;
    }
    push_down(i);
    if(nx<=mid) updatel(nx,l,mid,ls(i),k);
    else updatel(nx,mid+1,r,rs(i),k);
    push_up(i);
}
void updater(int nl,int nr,int l,int r,int i,int k){
    if(nl<=l&&r<=nr) return modify(i,k);
    push_down(i);
    if(nl<=mid) updater(nl,nr,l,mid,ls(i),k);
    if(mid<nr) updater(nl,nr,mid+1,r,rs(i),k);
    push_up(i);
}
int query(int nl,int nr,int l,int r,int i){
    if(nl<=l&&r<=nr) return t[i].len;
    push_down(i);
    int res=0;
    if(nl<=mid) res=max(res,query(nl,nr,l,mid,ls(i)));
    if(mid<nr) res=max(res,query(nl,nr,mid+1,r,rs(i)));
    return res;
}
void solve(){
    topl=topr=0;
    build(1,1,n);
    per(i,1,n){
        while(topl&&a[stl[topl]]<=a[i]) topl--;
        stl[++topl]=i;
        while(topr&&a[str[topr]]>a[i]){
            updatel(str[topr],1,n,1,0);
            topr--;
        }
        str[++topr]=i;
        updatel(i,1,n,1,i);
        updater(stl[topl-1]+1,i,1,n,1,i);
        for(auto x:q[i]) ans[x.id]=max(ans[x.id],query(x.l,i,1,n,1));
    }
}
void main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n;
    per(i,1,n) cin>>a[i];
    cin>>m;
    for(int i=1,l,r;i<=m;i++){
        cin>>l>>r;
        q[r].epb(l,i);
    }
    solve();
    per(i,1,n) a[i]*=-1;
    solve();
    per(i,1,m) cout<<ans[i]<<'\n';
}}
signed main(){
    fisher::main();
    return 0;
}
```

---

## 作者：NATO (赞：2)

【数据删除】 sol。

### 思路浅析：

我们钦定左端点是合法区间的最小值，右端点是最大值，下面默认只讨论我们钦定的情况，相反情况把值翻转后再跑一遍即可。

考虑离线扫描线，将询问挂到 $r$，维护左端点的贡献。

当我们扫描到位置 $i$，考虑以它为右端点的合法左端点。

我们发现对于一个位置 $j$ 合法当且仅当 $\max\limits_{k=j}^ia_k=a_i$ 和 $\min\limits_{k=j}^ia_k=a_j$ 均成立。

维护后缀 $\min,\max$，容易想到单调栈维护之。

具体地，对于位置 $i$，先用单调栈扫出最小的满足 $\max\limits_{k=j}^ia_k=a_i$ 的 $j$。

然后用单调栈维护后缀 $\min$。

考虑 $l$ 的限制，建立线段树，每个位置表示以该位置为左端点，合法的最大长度。 

考虑已经出栈的部分最大合法右端点已经固定了，出栈时丢入线段树即可。

而当前这个位置显然只会更新单调栈上的一段后缀，用单调栈二分出即可。考虑开一颗线段树维护单调栈内长度最大值，当前位置的更新即是后缀覆盖。

注意到一个区间被覆盖时必然是最左边那个位置对应的长度最长，直接将最大长度赋为 $i-st_l+1$ ，在线段树上直接打标记即可。

查询即取维护出栈的线段树和维护栈内答案的线段树中对应区间的最大值即可。

时间复杂度 $O((n+q)\log n)$。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
#define un unsigned
using namespace std;
ll n,q;
ll a[500005],b[500005];
ll ans[500005];
struct px
{
	ll l,uid;
};
vector<px>ask[500005];
stack<ll>s;
ll st[500005];
ll tr[2000005];
#define ls(id) id*2
#define rs(id) id*2+1
void update(ll id,ll l,ll r,ll ml,ll val)
{
	if(l==r)
	{
		tr[id]=max(tr[id],val);return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)update(ls(id),l,mid,ml,val);
	else update(rs(id),1+mid,r,ml,val);
	tr[id]=max(tr[ls(id)],tr[rs(id)]);
}
ll query(ll id,ll l,ll r,ll ml,ll mr)
{
	if(ml<=l&&r<=mr)return tr[id];
	ll mid=l+r>>1,res=0;
	if(ml<=mid)res=max(res,query(ls(id),l,mid,ml,mr));
	if(mr>mid)res=max(res,query(rs(id),1+mid,r,ml,mr));
	return res;
}
struct SGT
{
	struct tree
	{
		ll maxr_tag,maxn;
	}tr[2000005];
	void pushup(ll id)
	{
		tr[id].maxn=max(tr[ls(id)].maxn,tr[rs(id)].maxn);
	}
	void add_tag(ll id,ll l,ll r,ll val)
	{
		tr[id].maxr_tag=val;tr[id].maxn=val-st[l]+1;
	}
	void pushdown(ll id,ll l,ll r)
	{
		if(!tr[id].maxr_tag)return;
		ll mid=l+r>>1;
		add_tag(ls(id),l,mid,tr[id].maxr_tag);
		add_tag(rs(id),1+mid,r,tr[id].maxr_tag);
		tr[id].maxr_tag=0;
	}
	void update(ll id,ll l,ll r,ll ml,ll mr,ll val)
	{
		if(ml<=l&&r<=mr)
		{
			add_tag(id,l,r,val);return;
		}
		ll mid=l+r>>1;
		pushdown(id,l,r);
		if(ml<=mid)update(ls(id),l,mid,ml,mr,val);
		if(mr>mid)update(rs(id),1+mid,r,ml,mr,val);
		pushup(id);
	}
	ll query(ll id,ll l,ll r,ll ml,ll mr)
	{
		if(ml<=l&&r<=mr)return tr[id].maxn;
		pushdown(id,l,r);
		ll mid=l+r>>1,res=0;
		if(ml<=mid)res=max(res,query(ls(id),l,mid,ml,mr));
		if(mr>mid)res=max(res,query(rs(id),1+mid,r,ml,mr));
		pushup(id);
		return res;
	}
}sgt;
ll l[500005];
void solve()
{
	while(!s.empty())s.pop();
	for(ll i=1;i<=4*n;++i)tr[i]=0,sgt.tr[i].maxn=sgt.tr[i].maxr_tag=0;
	for(ll i=1;i<=n;++i)
	{
		l[i]=0;
		while(!s.empty()&&a[s.top()]<=a[i])s.pop();
		if(!s.empty())l[i]=s.top();
		s.push(i);
	}
	while(!s.empty())s.pop();
	for(ll i=1;i<=n;++i)
	{
		while(!s.empty()&&a[s.top()]>a[i])
		{
			ll val=sgt.query(1,1,n,s.size(),s.size());
			update(1,1,n,s.top(),val);
			s.pop();
		}
		s.push(i);st[s.size()]=i;
		ll where=upper_bound(st+1,st+1+s.size(),l[i])-st;
		sgt.update(1,1,n,where,s.size(),i);
		for(auto it:ask[i])
		{
			ll where=lower_bound(st+1,st+1+s.size(),it.l)-st;
			ans[it.uid]=max(ans[it.uid],max(query(1,1,n,it.l,i),sgt.query(1,1,n,where,s.size())));
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	ll cot=unique(b+1,b+1+n)-b-1;
	for(ll i=1;i<=n;++i)a[i]=lower_bound(b+1,b+1+cot,a[i])-b;
	cin>>q;
	ll l,r;
	for(ll i=1;i<=q;++i)
	{
		cin>>l>>r;ask[r].push_back((px){l,i});
	}
	solve();
	for(ll i=1;i<=n;++i)a[i]=cot-a[i]+1;
	solve();
	for(ll i=1;i<=q;++i)
	cout<<ans[i]<<'\n';
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
首先钦定左端点为最小值，右端点为最大值，另一种情况反转再跑一遍就行了。看到没有修改，感觉就很像扫描线，考虑右端点向右移的变化。首先右端点要合法，一定是最大值，容易想到用单调栈维护，设上一个严格大于它的位置为 $l$，加入的点为 $r$，$(l,r]$ 都是可以更新的。再考虑以 $(l,r]$ 的点作为左端点，如果一个点后面加入了比它权值小的点，这个点就不能被更新了，也可以用一个单调栈维护，设上一个小于等于 $a_r$ 的点为 $x$，那么 $(x,r]$ 中的所有点以后都不能再更新。考虑维护答案，容易想到用线段树，一个区间记录最小且可以更新的左端点和最大长度，每次加入一个点就去做一个区间覆盖，更新每一个小区间能取到的最大长度。过程中有的点会变成不能更新，如果这个东西也打标记做区间覆盖，那么标记下传难以实现，发现每个点只会被改一次，打一个类似势能的东西，单点改就好了。实现部分有点抽象，建议看下代码。
# Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
struct node
{
	int l,r,id;
	bool operator<(const node &a)const{return r<a.r;}
}q[1000005];
int n,m;
int a[1000005];
namespace Nene
{
	struct segt
	{
		int l,r,val;
		int tag;
		int flag;
	}t[1000005<<2];
	#define ls (root<<1)
	#define rs (root<<1|1)
	#define mid (l+r>>1)
	inline void pushr(int x,int y)
	{
		t[x].r=max(t[x].r,y);
		t[x].tag=max(t[x].tag,y);
		t[x].val=max(t[x].val,t[x].r-t[x].l+1);
	}
	inline void down(int root){if(t[root].tag) pushr(ls,t[root].tag),pushr(rs,t[root].tag),t[root].tag=0;}
	inline void update(int root)
	{
		t[root].l=min(t[ls].l,t[rs].l);
		t[root].val=max({t[root].val,t[ls].val,t[rs].val});
		t[root].flag=t[ls].flag&t[rs].flag;
	}
	void init(int root=1,int l=1,int r=n)
	{
		t[root].l=l;
		t[root].r=t[root].tag=t[root].val=t[root].flag=0;
		if(l==r) return;
		init(ls,l,mid);init(rs,mid+1,r);
		update(root);
	}
	void cov(int x,int y,int v,int root=1,int l=1,int r=n)
	{
		if(l>=x&&r<=y)
		{
			pushr(root,v);
			return;
		}
		down(root);
		if(x<=mid) cov(x,y,v,ls,l,mid);
		if(y>mid) cov(x,y,v,rs,mid+1,r);
		update(root);
	}
	void del(int x,int y,int root=1,int l=1,int r=n)
	{
		if(t[root].flag==1) return;
		if(l==r)
		{
			t[root].l=1e9,t[root].flag=1;
			return;
		}
		down(root);
		if(x<=mid) del(x,y,ls,l,mid);
		if(y>mid) del(x,y,rs,mid+1,r);
		update(root);
	}
	int query(int x,int y,int root=1,int l=1,int r=n)
	{
		if(l>=x&&r<=y) return t[root].val;
		down(root);
		int res=0;
		if(x<=mid) res=max(res,query(x,y,ls,l,mid));
		if(y>mid) res=max(res,query(x,y,rs,mid+1,r));
		return res;
	}
}
using namespace Nene;
int ans[1000005];
int stkl[1000005],topl,stkh[1000005],toph;
inline void work()
{
	memset(stkl,0,sizeof stkl);memset(stkh,0,sizeof stkh);topl=toph=0;
	init();
	sort(q+1,q+m+1);
	int cur=1;
	for(int i=1;i<=n;i++)
	{
		while(topl&&a[stkl[topl]]<=a[i]) --topl;
		while(toph&&a[stkh[toph]]>a[i]) --toph;
		if(stkh[toph]+1<=i-1) del(stkh[toph]+1,i-1);
		cov(stkl[topl]+1,i,i);
		stkl[++topl]=i;stkh[++toph]=i;
		while(cur<=m&&q[cur].r==i)
		{
			ans[q[cur].id]=max(ans[q[cur].id],query(q[cur].l,q[cur].r));
			++cur;
		}
	}
}
int main()
{
//	freopen("eat5.in","r",stdin);
//	freopen("eat.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	read(m);
	for(int i=1;i<=m;i++) read(q[i].l,q[i].r),q[i].id=i;
	work();
	reverse(a+1,a+n+1);
	for(int i=1;i<=m;i++)
	{
		int l=n-q[i].r+1,r=n-q[i].l+1;
		q[i].l=l,q[i].r=r;
	}
	work();
	for(int i=1;i<=m;i++) write(ans[i]),putch('\n');
	flush();
}
```

---

## 作者：MnZnOIer (赞：2)

作为模拟赛的 T3，考场上就打了个没分的暴力。

### 题意简述
求一个区间内，最大值为左或右端点，最小值为右或坐端点的区间最大长度是多少。

### 解题思路
我们可以先认为左端点就是最小值，右端点就是最大值，对于左端点是最大值，右端点是最小值的情况，按照左小右大的方法把数组倒过来再跑一边就可以了。

我们先把边离线下来，把询问挂到 $r$ 上，维护最小的左端点。当遇到一个 $l(l\le r)$ 时，它能作为一个合法的左端点，当且仅当 $\min _ {i=l} ^ {r}=a_l$ 和 $\max _ {i=l} ^ {r}a_i=a_r$ 都成立。

那么我们可以想到用单调栈来维护对于右端点 $r$ 的最小的左端点。具体地，我们可以用单调栈扫出最小的满足 $\max ^ {r} _ {i=l}a_i=a_r$ 的值，然后用单调栈维护后缀 $\min$。若数据随机，单调栈的大小期望 $\log n$，这时我们可以暴力取出所有值。又因为有 $l$ 的限制，所以我们可以建一个树状数组来维护以该点为左端点的合法的最大长度，对于从单调栈中取出的值就可以直接在树状数组上更新。最后再按照右端点统计答案即可。

这个做法在本题中没有被卡得太难看，同时证明了数据的随机性。

那么时间复杂度为 $\Theta(n\log^2 n)$。

### 代码部分

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
int n, q, a[N], s[N], top, l[N], ans[N];
struct Question{int lef, id;};//离线询问。
vector <Question> v[N];
int lowbit (int x){return x & -x;}
struct Bit_Tree//树状数组模板。
{
	int tree[N], f;
	void Clear (){memset (tree, 0, sizeof (tree));}
	void update (int to, int d){for (; to && to <= n; to += f * lowbit (to))tree[to] = max (tree[to], d);}
	int query (int to){int s = 0;for (; to && to <= n; to -= f * lowbit (to))s = max (s, tree[to]);return s;}
}que, con;
void solve ()
{
	top = 0;
	for (int i = 1; i <= n; ++ i)
	{
		while (top && a[s[top]] <= a[i])-- top;
		l[i] = s[top] + 1;//维护最小的左端点。
		s[++ top] = i;
	}
	top = 0;
	for (int i = 1; i <= n; ++ i)
	{
		while (top && a[s[top]] > a[i])
		{
			que.update (s[top], con.query(top) - s[top] + 1);//取出单调栈中的值在树状数组中更新。
			-- top;
		}
		s[++ top] = i;
		int p = lower_bound (s + 1, s + top + 1, l[i]) - s;//找到第一个大于等于右端点的值。
		con.update (p, i); //更新。
		que.update (s[p], i - s[p] + 1);
		for (int j = 0; j < v[i].size (); ++ j)
		{
			Question t = v[i][j];
			int pp = lower_bound (s + 1, s + top + 1, t.lef) - s;
			ans[t.id] = max ({ans[t.id], que.query (t.lef), con.query (pp) - s[pp] + 1});//更新答案。
		}
	}
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i)cin >> a[i];
	for (int i = 1, x, y; i <= q; ++ i)
	{
		cin >> x >> y;
		v[y].push_back (Question{x, i});//离线询问。
	}
	que.f = -1, con.f = 1;
	solve ();
	for (int i = 1; i <= n; ++ i)a[i] *= -1;//反转数组，其实只需要反转大小关系。
	que.Clear ();
	con.Clear ();
	solve ();
	for (int i = 1; i <= q; ++ i)cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：PNNNN (赞：1)

介绍一种历史最值线段树的解法。

考虑最大值在右端点，最小值在左端点的情况。

对于一个点 $i$，我们可以求出以 $i$ 为右端点的魔法区间左端点最远可以到哪里，设其为 $pos_i$，则 $\max \limits_{j=pos_i}^{i} \{a_j\} \leq a_i$。可以由单调栈求出。

那对于一个右端点 $i$，又有哪些点可以作为左端点？可知，一个点 $j$ 要为一个合法的左端点，则需满足 $\min \limits_{k=j}^{i} \{a_k\} \geq a_j$。

这个东西也可以用单调栈维护，每次把栈中 $a$ 大于 $a_i$ 的点弹出，因为这些点都是不合法的。已知随着 $i$ 的增加，$\min \limits_{k=j}^{i} \{a_k\}$ 是单调不降的，所以当一个点从栈中被弹出时，它之后都不可能成为一个合法的左端点。随后再 $i$ 加入栈中，因为 $[i,i]$ 也是一个魔法区间。

在弹完元素之后，栈中的点便都满足 $\min \limits_{k=j}^{i} \{a_k\} \geq a_j$。此时以点 $i$ 为右端点的魔法区间的左端点就是编号大于等于 $pos_i$ 且在栈中的点。

考虑如何快速求以 $i$ 为右端点的最长的魔法区间的长度。考虑一个序列 $t[1\dots n]$，初始时 $t_i=1-i$。对于那些弹出栈的不合法的点 $j$ ，我们可以在弹栈时将 $t_j$ 修改为 $-\infty$。这样的话，我们要求的最长的魔法区间的长度相当于再对 $t[pos_i,i]$ 加上 $i$ 后的 $\max\limits_{j=pos_i}^{i}\{t_j\}$。若是询问要求左端点要大于等于 $l$，则答案是 $\max\limits_{j=\max(pos_i,l)}^{i}\{t_j\}$。序列 $t$ 可以用线段树维护。

再考虑对于一个区间 $[l,r]$ 怎么求出它最长的子魔法区间的长度。根据上面的做法，容易想到对询问以 $r$ 为关键字排序，接着对右端点 $i$ 进行扫描线，用历史最值线段树维护 $t$ 序列即可。具体的，每次区间加之后线段树会取得最值，再区间减消除贡献即可。当扫描到 $r$ 时，答案即为区间 $[l,r]$ 在线段树上的历史最值。

对于最大值在左端点，最小值在右端点的情况，将 $a_i$ 取反再用上面的做法做一遍就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
#define fr first
#define sc second
using namespace std;

const int inf=1e9;

int n,q,a[1000005],ans[1000005];

struct tree{
	int val,tag,_tag,_val;
}t[1000005<<2];

inline void pushup(int k){
	t[k].val=max(t[ls].val,t[rs].val),t[k]._val=max(t[ls]._val,t[rs]._val);return;
}

inline void pushdown(int k){
	if(t[k].tag!=0||t[k]._tag!=0){
		t[ls]._tag=max(t[ls]._tag,t[ls].tag+t[k]._tag),t[ls].tag+=t[k].tag;
		t[ls]._val=max(t[ls]._val,t[ls].val+t[k]._tag),t[ls].val+=t[k].tag;
		
		t[rs]._tag=max(t[rs]._tag,t[rs].tag+t[k]._tag),t[rs].tag+=t[k].tag;
		t[rs]._val=max(t[rs]._val,t[rs].val+t[k]._tag),t[rs].val+=t[k].tag;
		
		t[k].tag=0,t[k]._tag=0;
	}return;
}

inline void build(int k=1,int l=1,int r=n){
	t[k].tag=t[k]._tag=0;
	if(l==r){
		t[k].val=t[k]._val=-l+1;
	}else{
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(k);
	}return;
}

inline void updata(int L,int R,int val,int k=1,int l=1,int r=n){
	if(L>R)return;
	if(L<=l&&r<=R){
		t[k].tag+=val,t[k]._tag=max(t[k]._tag,t[k].tag);
		t[k].val+=val,t[k]._val=max(t[k].val,t[k]._val);
	}else{
		pushdown(k);
		int mid=l+r>>1;
		if(L<=mid)updata(L,R,val,ls,l,mid);
		if(R>mid)updata(L,R,val,rs,mid+1,r);
		pushup(k);
	}return;
}

inline int _query(int L,int R,int k=1,int l=1,int r=n){
	if(L<=l&&r<=R){
		return t[k]._val;
	}else{
		pushdown(k);
		int mid=l+r>>1,res=-inf;
		if(L<=mid)res=max(res,_query(L,R,ls,l,mid));
		if(R>mid)res=max(res,_query(L,R,rs,mid+1,r));
		return res;
	}
}

inline int query(int L,int R,int k=1,int l=1,int r=n){
	if(L<=l&&r<=R){
		return t[k].val;
	}else{
		pushdown(k);
		int mid=l+r>>1,res=-inf;
		if(L<=mid)res=max(res,query(L,R,ls,l,mid));
		if(R>mid)res=max(res,query(L,R,rs,mid+1,r));
		return res;
	}
}

struct ask{
	int l,r,id;
}vec[1000005];

inline bool cmp(ask A,ask B){return A.r<B.r;}

int st[1000005],top,pos[1000005],it;

inline int read(){
	register int x(0),t(0);
	static char ch=getchar();
	while(!isdigit(ch)){t|=(ch=='-'),ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
	return t?-x:x;
}

signed main(){
	
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=q;i++){
		vec[i]={read(),read(),i};
	}
	sort(vec+1,vec+1+q,cmp);
	
	top=0,it=0,build();
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<=a[i])top--;
		pos[i]=st[top]+1,st[++top]=i;
	}
	top=0;
	for(int i=1;i<=q;i++){
		while(it+1<=vec[i].r){
			it++;
			while(top&&a[st[top]]>a[it]){
				updata(st[top],st[top],-inf),top--;
			}
			st[++top]=it;
			updata(pos[it],it,it);
			updata(pos[it],it,-it);
		}
		ans[vec[i].id]=max(ans[vec[i].id],_query(vec[i].l,vec[i].r));
	}
	
	for(int i=1;i<=n;i++){
		a[i]=1000000000-a[i]+1;
	}
	
	top=0,it=0,build();
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<=a[i])top--;
		pos[i]=st[top]+1,st[++top]=i;
	}
	top=0;
	for(int i=1;i<=q;i++){
		while(it+1<=vec[i].r){
			it++;
			while(top&&a[st[top]]>a[it]){
				updata(st[top],st[top],-inf),top--;
			}
			st[++top]=it;
			updata(pos[it],it,it);
			updata(pos[it],it,-it);
		}
		ans[vec[i].id]=max(ans[vec[i].id],_query(vec[i].l,vec[i].r));
	}
	
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<'\n';
	}
	
	return 0;
}
```
时间复杂度 $ O((n+q)\times \log n)$。

---

## 作者：苏联小渣 (赞：1)

子区间问题考虑扫描线。把询问按照右端点排序，扫到每个点作为右端点时，如果我们能把所有合法的左端点更新答案，就能做到区间查询答案了。

转化题意，区间合法的条件是左右端点都是最值。不妨假设右端点是最大值，左端点是最小值，另一种情况用同样方法处理就行了。

考虑枚举右端点 $r$。我们要使得 $a_r$ 为右端点，那么找到左边第一个比它大的数，记作 $lef_r$，那么左端点 $l$ 需要满足 $l \in [lef_r+1,r]$。

除此之外，$l$ 还需要满足 $a_l$ 是区间 $[l,r]$ 的最小值。考虑 $r$ 固定时区间 $[l,r]$ 的最小值，一定是从 $r$ 开始，不断跳左边第一个小于等于它的数能跳到的点，换句话说，就是维护一个权值单调递减（非严格）的单调栈，在 $r$ 处时这个单调栈里面所有的点。

如果只有第一个限制，我们直接区间赋值就可以了。具体来说，在线段树的每个结点维护子树里面所有点作为左端点时，长度的最大值。设这个结点代表的区间是 $[l,r]$，当前更新的右端点是 $R$，那么直接把这个结点的答案更新为 $R-l+1$（因为要求长度最大，所以选左端点肯定更优），并且把 $R$ 放到区间赋值的 tag 里面就好了。pushup 和 pushdown 都是类似的操作。

加上第二个限制，那么合法的点就不是连续的了。对于一个点，在它变为合法和变成不合法的时候，我们都在线段树上打一个标记，表示这个点能否作为合法的左端点。在进行区间覆盖的时候，我们就不能把当前结点的答案更新为 $R-l+1$ 了，而要改成 $R-L_k+1$，其中 $L_k$ 表示这个子树里面最左端合法的点，这个是容易维护的。

然后查询的时候，直接查询区间 $[l,r]$ 的最大值就好了。时间复杂度 $O(n \log n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, q, l, r, a[500010], ans[500010];
struct Query{
	int l, id;
};
vector <Query> ask[500010];
stack <int> st1, st2;
struct segment{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	int d[2000010], lef[2000010], tag[2000010];
	void clear(){
		for (int i=1; i<=n*4; i++){
			d[i] = lef[i] = tag[i] = 0;
		}
	}
	void pushup(int k){
		d[k] = max(d[lc(k)], d[rc(k)]);
		lef[k] = min(lef[lc(k)], lef[rc(k)]);
	}
	void pushdown(int k){
		if (tag[k]){
			tag[lc(k)] = tag[rc(k)] = tag[k];
			d[lc(k)] = max(d[lc(k)], tag[k] - lef[lc(k)] + 1);
			d[rc(k)] = max(d[rc(k)], tag[k] - lef[rc(k)] + 1);
			tag[k] = 0;
		}
	}
	void modify(int k, int l, int r, int x, int y){
		if (l == r){
			lef[k] = y;
			return ;
		}
		pushdown(k);
		int mid = l + r >> 1;
		if (x <= mid) modify(lc(k), l, mid, x, y);
		else modify(rc(k), mid+1, r, x, y);
		pushup(k);
	}
	void modifyadd(int k, int l, int r, int x, int y, int val){
		if (x <= l && r <= y){
			d[k] = max(d[k], val - lef[k] + 1), tag[k] = val;
			return ;
		}
		pushdown(k);
		int mid = l + r >> 1;
		if (x <= mid) modifyadd(lc(k), l, mid, x, y, val);
		if (y > mid) modifyadd(rc(k), mid+1, r, x, y, val);
		pushup(k);
	}
	int query(int k, int l, int r, int x, int y){
		if (x <= l && r <= y) return d[k];
		pushdown(k);
		int mid = l + r >> 1, ret = 0;
		if (x <= mid) ret = max(ret, query(lc(k), l, mid, x, y));
		if (y > mid) ret = max(ret, query(rc(k), mid+1, r, x, y));
		return ret;
	}
}S;
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
	}
	scanf ("%d", &q);
	for (int i=1; i<=q; i++){
		scanf ("%d%d", &l, &r);
		ask[r].push_back((Query){l, i});
	}
	for (int i=1; i<=n; i++){
		while (!st1.empty() && a[st1.top()] <= a[i]) st1.pop();
		while (!st2.empty() && a[st2.top()] > a[i]){
			S.modify(1, 1, n, st2.top(), 1e9);
			st2.pop();
		}
		S.modify(1, 1, n, i, i);
		int lef;
		if (st1.empty()) lef = 0;
		else lef = st1.top();
		S.modifyadd(1, 1, n, lef+1, i, i);
		for (int j=0; j<ask[i].size(); j++){
			int l = ask[i][j].l, id = ask[i][j].id;
			ans[id] = max(ans[id], S.query(1, 1, n, l, i));
		}
		st1.push(i); st2.push(i);
	}
	S.clear();
	while (!st1.empty()) st1.pop();
	while (!st2.empty()) st2.pop();
	for (int i=1; i<=n; i++){
		while (!st1.empty() && a[st1.top()] >= a[i]) st1.pop();
		while (!st2.empty() && a[st2.top()] < a[i]){
			S.modify(1, 1, n, st2.top(), 1e9);
			st2.pop();
		}
		S.modify(1, 1, n, i, i);
		int lef;
		if (st1.empty()) lef = 0;
		else lef = st1.top();
		S.modifyadd(1, 1, n, lef+1, i, i);
		for (int j=0; j<ask[i].size(); j++){
			int l = ask[i][j].l, id = ask[i][j].id;
			ans[id] = max(ans[id], S.query(1, 1, n, l, i));
		}
		st1.push(i); st2.push(i);
	}
	for (int i=1; i<=q; i++){
		printf ("%d\n", ans[i]);
	}
	return 0;
}

```

---

## 作者：Luckies (赞：1)

如果你做过 [GSS2](https://www.luogu.com.cn/problem/SP1557)，那么你会发现它们很像，都是询问最优子段的问题。

这里有一个 trick，对于这一类询问最优子段的问题，首先考虑将询问离线，然后扫描线。若当前扫描到 $i$，设 $f_j$ 表示以 $j$ 为左端点，$i$ 为右端点的子段信息，可以维护 $f_j$ 的历史最值求解。

如何理解这个历史最值。由于是扫描线依次添加每一个位置，那么 $f_j$ 的历史最值即为以 $j$ 为左端点，且右端点在 $[j, i]$ 的最优子段。可以用线段树维护区间历史最值。

那么问题在于如何维护 $f_j$。不妨设左小右大，那么左大右小将序列取倒数即可。

不难发现，若 $i$ 能够成为最大值，则 $\max\limits_{k\in[j,i]}{a_k} \le a_i$。可以用单调栈维护 $L_i$ 表示 $i$ 左边第一个小于 $a_i$ 的数的位置，则 $j \in (L_i, i]$。

考虑哪些 $j$ 是合法的。在扫描线的同时维护一个单调栈，单调不减。那么在栈中的位置一定是合法的 $j$，弹出位置一定不合法。将不合法的位置标记，则 $(L_i, i]$ 中未被标记的位置即为所有合法的 $j$。用线段树区间修改即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, Q, a[N], L[N], ans[N];
struct node
{
    int l, r, id;
};
vector<node> q;
struct Tree
{
    int maxi, tag, hismaxi, histag;
}tree[N << 2];
#define ls (cur << 1)
#define rs (cur << 1 | 1)
#define mid (lt + rt >> 1)
void pushup(int cur)
{
    tree[cur].maxi = max(tree[ls].maxi, tree[rs].maxi);
    tree[cur].hismaxi = max(tree[ls].hismaxi, tree[rs].hismaxi);
    return;
}
void build(int cur, int lt, int rt)
{
    tree[cur] = {0, 0, 0, 0};
    if(lt == rt)
    {
        tree[cur] = {-lt + 1, 0, 0, 0};
        return;
    }
    build(ls, lt, mid), build(rs, mid + 1, rt);
    return pushup(cur);
}
void addtag(int cur, int tag, int histag)
{
    tree[cur].hismaxi = max(tree[cur].hismaxi, tree[cur].maxi + histag), tree[cur].maxi += tag;
    tree[cur].histag = max(tree[cur].histag, tree[cur].tag + histag), tree[cur].tag += tag;
    return;
}
void pushdown(int cur)
{
    if(!tree[cur].tag && !tree[cur].histag)
        return;
    addtag(ls, tree[cur].tag, tree[cur].histag);
    addtag(rs, tree[cur].tag, tree[cur].histag);
    tree[cur].tag = 0, tree[cur].histag = 0;
    return;
}
void update(int cur, int lt, int rt, int l, int r, int val)
{
    if(r < lt || rt < l)
        return;
    if(l <= lt && rt <= r)
    {
        tree[cur].tag += val, tree[cur].histag = max(tree[cur].histag, tree[cur].tag);
        tree[cur].maxi += val, tree[cur].hismaxi = max(tree[cur].hismaxi, tree[cur].maxi);
        return;
    }
    pushdown(cur);
    update(ls, lt, mid, l, r, val), update(rs, mid + 1, rt, l, r, val);
    return pushup(cur);
}
int query(int cur, int lt, int rt, int l, int r)
{
    if(r < lt || rt < l)
        return 0;
    if(l <= lt && rt <= r)
        return tree[cur].hismaxi;
    pushdown(cur);
    return max(query(ls, lt, mid, l, r), query(rs, mid + 1, rt, l, r));
}
void solve()
{
    stack<int> stk;
    for(int i = n; i; i--)
    {
        while(!stk.empty() && a[stk.top()] < a[i])
            L[stk.top()] = i + 1, stk.pop();
        stk.push(i);
    }
    while(!stk.empty())
        L[stk.top()] = 1, stk.pop();
    build(1, 1, n);
    int i = 0;
    for(auto [l, r, id] : q)
    {
        while(i < r)
        {
            i++;
            while(!stk.empty() && a[stk.top()] > a[i])
                update(1, 1, n, stk.top(), stk.top(), INT_MIN), stk.pop();
            stk.push(i);
            update(1, 1, n, L[i], i, i);
            update(1, 1, n, L[i], i, -i);
        }
        ans[id] = max(ans[id], query(1, 1, n, l, r));
    }
    return;
}
signed main()
{
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> Q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= Q; i++)
    {
        int l, r;
        cin >> l >> r;
        q.push_back({l, r, i});
    }
    sort(q.begin(), q.end(), [](auto x, auto y)
    {
        return x.r < y.r;
    });
    solve();
    for(int i = 1; i <= n; i++)
        a[i] = -a[i];
    solve();
    for(int i = 1; i <= Q; i++)
        cout << ans[i] << "\n";
    return 0;
}
```

---

## 作者：qnqfff (赞：0)

### 思路

离线扫描线，钦定右端点为最大值，另一种情况把每个值变成最大值减它自己在做一边就行了。

考虑扫到 $r$，那么维护一个单调递减的单调栈 $st$ 则 $l\in(st_{top},i]$，但还要保证左端点是最小值，也可以维护一个单调递增的单调栈即可。

考虑线段树维护每个左端点的答案，因为答案形如 $r-l+1$，$r$ 是你扫的，于是只要维护 $l$ 的最小值即可。

### 代码

```cpp
#include<bits/stdc++.h>
const int inf=1e9;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[1000010],s1[1000010],t1,s2[1000010],t2,ans[1000010];struct Q{int l,r,id;}q[1000010];struct seg{int l,r,mi,mx,tag;}t[4000010];
#define lson now<<1
#define rson now<<1|1
void pushup(int now){t[now].mi=min(t[lson].mi,t[rson].mi);t[now].mx=max(t[lson].mx,t[rson].mx);}
void build(int now,int l,int r){
	t[now].l=l;t[now].r=r;t[now].mi=t[now].mx=t[now].tag=0;if(l==r) return ;
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);
}
void puttag(int now,int v){t[now].tag=v;t[now].mx=max(t[now].mx,v-t[now].mi+1);}
void pushdown(int now){if(!t[now].tag) return ;puttag(lson,t[now].tag);puttag(rson,t[now].tag);t[now].tag=0;}
void modify(int now,int x,int v){
	if(t[now].l==t[now].r){t[now].mi=v;return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(x<=mid) modify(lson,x,v);else modify(rson,x,v);pushup(now);
}
void cover(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){puttag(now,v);return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) cover(lson,l,r,v);if(mid<r) cover(rson,l,r,v);pushup(now);
}
int query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].mx;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1,res=1;if(l<=mid) res=max(res,query(lson,l,r));if(mid<r) res=max(res,query(rson,l,r));return res;
}
void upd(){
	build(1,1,n);t1=t2=0;for(int i=1,j=1;i<=n;i++){
		while(t1&&a[s1[t1]]<=a[i]) t1--;while(t2&&a[s2[t2]]>a[i]){modify(1,s2[t2],1e9);t2--;}
		modify(1,i,i);cover(1,s1[t1]+1,i,i);s1[++t1]=s2[++t2]=i;for(;j<=m&&q[j].r==i;j++) ans[q[j].id]=max(ans[q[j].id],query(1,q[j].l,i));
	}
}
int main(){
	n=read();int mx=0;for(int i=1;i<=n;i++) a[i]=read(),mx=max(mx,a[i]);m=read();for(int i=1;i<=m;i++) q[i]={read(),read(),i};sort(q+1,q+1+m,[&](Q x,Q y){return x.r<y.r;});
	upd();for(int i=1;i<=n;i++) a[i]=mx-a[i]+1;upd();for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18355760)

首先考虑离线。

设 $Min-nxt_i$ 表示下一个小于 $a_i$ 处的位置，$Max-nxt_i$ 表示下一个大于 $a_i$ 处的位置。

那么 $[l,r]$ 是魔法区间当且仅当：

- $r$ 是 $[l,r]$ 的最大值，且 $r < Min - nxt_l$。

- $r$ 是 $[l,r]$ 的最小值，且 $r < Max - nxt_l$。 

再令 $Min-pre_i$ 表示上一个小于 $a_i$ 处的位置，$Max-pre_i$ 表示上一个大于 $a_i$ 处的位置。

那么我们可以对于每个 $r$，求出对应的 $l$ 的氛围：

- 若 $r$ 是 $[l,r]$ 的最大值，则 $l \in [Max-pre_r+1,r]$。

- 若 $r$ 是 $[l,r]$ 的最小值，则 $l \in [Min-pre_r+1,r]$。

则可以在扫描线扫到 $r$ 时，对上述两个区间更新答案；注意到对于 $l$ 的答案是 $r-l+1$，那么对于区间 $[a,b]$，其的右端点若都是 $r$，要使得贡献最大，应该选择 $[a,r]$ 区间，但是有些点是无法对 $r$ 造成贡献的（对于这类点的处理见下文），于是我们需要找到 $[a,b]$ 内最小的能对 $r$ 造成贡献的点，维护一个 `set` 二分即可，需要支持删除。

但是我们需要满足 $r < Min-nxt_l$ 或 $r<Max-nxt_l$，那么可以在 $Min-nxt_l$ 和 $Max-nxt_l$ 处将 $l$ 此处赋值为无穷小即可。

注意到就算 $l$ 处被赋值为无穷小，即无法对 $r$ 与 $r$ 后面的数造成贡献，但是其本身也有贡献，需要用另外一个线段树维护无法造成新贡献的点的区间最大贡献。

时间复杂度为 $O((N+Q) \log^2 N)$。

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
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef int ll;
bool Begin;
const ll N=5e5+10;
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
ll n,q,l,r,top;
ll a[N],ans[N],stk[N],Mi_pre[N],Ma_pre[N],Mi_nxt[N],Ma_nxt[N];
vector<ll> F[N],G[N];
vector<pi> Q[N];
class St{
public:
    ll X[N<<2];
    void pushup(ll k){
        X[k]=max(X[k<<1],X[k<<1|1]);
    }
    void build(ll k,ll l,ll r){
        X[k]=0;
        if(l==r)
          return ;
        ll mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
    }
    void add(ll k,ll l,ll r,ll i,ll v){
        if(l==i&&i==r){
            X[k]=v;
            return ;
        }
        ll mid=(l+r)>>1;
        if(i<=mid)
          add(k<<1,l,mid,i,v);
        else
          add(k<<1|1,mid+1,r,i,v);
        pushup(k);
    }
    ll query(ll k,ll L,ll R,ll l,ll r){
        if(L==l&&r==R)
          return X[k];
        ll mid=(L+R)>>1;
        if(r<=mid)
          return query(k<<1,L,mid,l,r);
        else if(l>mid)
          return query(k<<1|1,mid+1,R,l,r);
        else
          return max(query(k<<1,L,mid,l,mid),query(k<<1|1,mid+1,R,mid+1,r));
    }    
}TT;
class Tree{
public:
    set<ll> S;
    struct Node{
        ll l,r;
        ll Max;
        ll tag;
    }X[N<<2];
    ll get(ll x){
        return (*S.lower_bound(x));
    }
    void add(ll k,ll v){
        ll t=get(X[k].l);
        if(t>X[k].r)
          X[k].Max=-1e9;
        else
          X[k].Max=v-t+1;
        X[k].tag=v;
    }
    void push_down(ll k){
        if(X[k].tag){
            add(k<<1,X[k].tag);
            add(k<<1|1,X[k].tag);
            X[k].tag=0;
        }
    }
    void pushup(ll k){
        X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
    }
    void build(ll k,ll l,ll r){
        X[k].l=l,X[k].r=r;
        X[k].tag=X[k].Max=0;
        if(l==r){
            S.insert(l);
            return ;
        }
        ll mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
    }
    void add(ll k,ll i,ll v){
        if(X[k].l==i&&i==X[k].r){
            TT.add(1,1,n,i,X[k].Max);
            S.erase(i);
            X[k].Max=v;
            return ;
        }
        push_down(k);
        ll mid=(X[k].l+X[k].r)>>1;
        if(i<=mid)
          add(k<<1,i,v);
        else
          add(k<<1|1,i,v);
        pushup(k);
    }
    void update(ll k,ll l,ll r,ll v){
        if(X[k].l==l&&r==X[k].r){
            //cerr<<"1:"<<l<<' '<<r<<' '<<v<<'\n';
            add(k,v);
            //cerr<<"2:"<<l<<' '<<r<<' '<<X[k].Max<<'\n';
            return ;
        }
        push_down(k);
        ll mid=(X[k].l+X[k].r)>>1;
        if(r<=mid)
          update(k<<1,l,r,v);
        else if(l>mid)
          update(k<<1|1,l,r,v);
        else{
            update(k<<1,l,mid,v);
            update(k<<1|1,mid+1,r,v);
        }
        pushup(k);
        //cerr<<"3:"<<X[k].l<<' '<<X[k].r<<' '<<X[k].Max<<'\n';
    }
    ll query(ll k,ll l,ll r){
        //cerr<<"4:"<<X[k].l<<' '<<X[k].r<<' '<<X[k].Max<<'\n';
        if(X[k].l==l&&r==X[k].r)
          return X[k].Max;
        push_down(k);
        ll mid=(X[k].l+X[k].r)>>1;
        if(r<=mid)
          return query(k<<1,l,r);
        else if(l>mid)
          return query(k<<1|1,l,r);
        else
          return max(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
    }
}T;
bool End;
int main(){
    n=read();
    for(int i=1;i<=n;i++)
      a[i]=read();
    q=read();
    for(int i=1;i<=q;i++){
        l=read(),r=read();
        Q[r].push_back({l,i});
    }
    for(int i=1;i<=n;i++){
        while(top&&a[stk[top]]>a[i]){
            Mi_nxt[stk[top]]=i;
            top--;
        }
        stk[++top]=i;    
    }
    top=0;
    for(int i=1;i<=n;i++){
        while(top&&a[stk[top]]<a[i]){
            Ma_nxt[stk[top]]=i;
            top--;
        }
        stk[++top]=i;
    }
    top=0;
    for(int i=n;i>=1;i--){
        while(top&&a[stk[top]]>a[i]){
            Mi_pre[stk[top]]=i;
            top--;
        }
        stk[++top]=i;  
    }
    top=0;
    for(int i=n;i>=1;i--){
        while(top&&a[stk[top]]<a[i]){
            Ma_pre[stk[top]]=i;
            top--;
        }
        stk[++top]=i;       
    }
    for(int i=1;i<=n;i++){
        F[Mi_nxt[i]].push_back(i);
        G[Ma_nxt[i]].push_back(i);
    }
    T.build(1,1,n);
    TT.build(1,1,n);
    for(int i=1;i<=n;i++){
        for(auto v:F[i])
          T.add(1,v,-1e9);
        T.update(1,Ma_pre[i]+1,i,i);
        for(auto t:Q[i])
          ans[t.se]=max({ans[t.se],T.query(1,t.fi,i),TT.query(1,1,n,t.fi,i)});
    }
    T.build(1,1,n);
    TT.build(1,1,n);
    for(int i=1;i<=n;i++){
        for(auto v:G[i])
          T.add(1,v,-1e9);
        T.update(1,Mi_pre[i]+1,i,i);
        for(auto t:Q[i])
          ans[t.se]=max({ans[t.se],T.query(1,t.fi,i),TT.query(1,1,n,t.fi,i)});
    }
    for(int i=1;i<=q;i++){
        write(ans[i]);
        putchar('\n');
    }
	return 0;
}
```

---

