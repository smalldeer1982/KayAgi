# Permutation Separation

## 题目描述

You are given a permutation $ p_1, p_2, \dots , p_n $ (an array where each integer from $ 1 $ to $ n $ appears exactly once). The weight of the $ i $ -th element of this permutation is $ a_i $ .

At first, you separate your permutation into two non-empty sets — prefix and suffix. More formally, the first set contains elements $ p_1, p_2, \dots , p_k $ , the second — $ p_{k+1}, p_{k+2}, \dots , p_n $ , where $ 1 \le k < n $ .

After that, you may move elements between sets. The operation you are allowed to do is to choose some element of the first set and move it to the second set, or vice versa (move from the second set to the first). You have to pay $ a_i $ dollars to move the element $ p_i $ .

Your goal is to make it so that each element of the first set is less than each element of the second set. Note that if one of the sets is empty, this condition is met.

For example, if $ p = [3, 1, 2] $ and $ a = [7, 1, 4] $ , then the optimal strategy is: separate $ p $ into two parts $ [3, 1] $ and $ [2] $ and then move the $ 2 $ -element into first set (it costs $ 4 $ ). And if $ p = [3, 5, 1, 6, 2, 4] $ , $ a = [9, 1, 9, 9, 1, 9] $ , then the optimal strategy is: separate $ p $ into two parts $ [3, 5, 1] $ and $ [6, 2, 4] $ , and then move the $ 2 $ -element into first set (it costs $ 1 $ ), and $ 5 $ -element into second set (it also costs $ 1 $ ).

Calculate the minimum number of dollars you have to spend.

## 样例 #1

### 输入

```
3
3 1 2
7 1 4```

### 输出

```
4```

## 样例 #2

### 输入

```
4
2 4 1 3
5 9 8 3```

### 输出

```
3```

## 样例 #3

### 输入

```
6
3 5 1 6 2 4
9 1 9 9 1 9```

### 输出

```
2```

# 题解

## 作者：YLWang (赞：14)

非常简单的一个题。但容易想歪。这种题相对C和D来说就可以算有点意思了。

做数据结构题，乃至做所有题，都有一个技巧。先把暴力敲出来，看看能不能优化暴力。

我们考虑怎么暴力做这题。

首先，枚举一开始的分割位置 $t$。（$a[t]$属于左边）

其次我们发现不大好确定怎么移动。这时候就要发掘发掘性质。

我们发现，移动完的数组一定是形如在某个数 $s$ 左边（包括$s$）的$p$为$1, 2, ..., s$， 剩下的为$s+1, s+2, ..., n$。这个非常好理解。

那么我们只要枚举 $s$ ，统计出 $t$ 左边（包括$t$）原来大于$s$的$p_i$的$a_i$的和，右边（不包括$t$）原来小于$s$的$p_i$的$a_i$的和，两边一加就是答案。

回头一看复杂度，妥妥的$n^3$。

接下来考虑优化。我们发现统计和那一步可以用权值线段树，优化到$n^2lgn$

但是这样子没什么用。枚举的复杂度是省不了的。

怎么办？

采用OI的常用套路，逆向思维。(譬如枚举每条边的贡献，枚举字符集就是这个的常见应用）

我统计不了每个状态下你分开的贡献，我还不能把你所有的贡献一起处理了？这样统一处理，就可以方便地使用一些东西维护。

我们考虑还是枚举$t$。维护一个数组$S$，$S[i]$表示$s$为$i$时候的答案。

对于一个$p_i$，如果它在$t$左边（包括$t$），那么它会对$s_0, s_1, ..., s_{p_i-1}$产生$a_i$的贡献。

对于一个$p_i$，如果它在$t$右边（包括$t$），那么它会对$s_{p_i}, s_{p_i+1}, ..., s_{n}$产生$a_i$的贡献。

这个时候我们直接上一棵线段树维护就可以了。

一开始全部在左边。后来一个一个往右加。最后全部在右边。每次加入后查询全局最小值。这就是一个非常完美的解法。

---

## 作者：万弘 (赞：13)

考虑最后的状态一定满足左部都不大于一个整数$k$,右部都大于$k$.

枚举初始的划分点$i$(将原序列分成$[1,i],[i+1,n]$两部分，$1\le i<n$,因为初始时两边均非空).不妨设$f(i,k)$表示以$i$为初始划分点，最终左部都不大于$k$,右部都大于$k$的花费.

考虑$j$对$f(i,j)$的贡献：
- 若$j\le i$:若$p_j\le k$,即$j$本来在左部，最终也在左部，不需移动。若$p_j>k$,即$j$本来在左部，最终应在右部，需要花费$a_i$的代价移动。
- 若$j>i$:若$p_j\le k$,即$j$本来在右部，最终在左部，需要花费$a_i$的代价移动。若$p_j>k$,即$j$本来在右部，最终也在右部，不需移动。

暴力枚举$i,k,j$,时间复杂度$\Theta(n^3)$  
考虑从划分点$i-1$到$i$的变化：
- 对于$k\ge p_i$,不需要再花费$a_i$的代价移动。
- 对于$k<p_i$,需要花费$a_i$的代价移动。  

因此只枚举$i,k$即可。时间复杂度$\Theta(n^2)$

考虑上面变化的第一条，即对$k\in[p_i,n],f(i,k)=f(i-1,k)-a_i$,对$k\in[0,p_i-1],f(i,k)=f(i-1,k)+a_i$

那这就是一个区间修改，查询全局min的线段树。时间复杂度$\Theta(nlogn)$

```cpp
/**********/省略快读
#define MAXN 200011
ll n;
struct Segment_Tree//线段树
{
	struct node
	{
		ll minv,tag;
	}t[MAXN<<2|1];
	#define rt t[num]
	#define tl t[num<<1]
	#define tr t[num<<1|1]
	void pushup(un num)
	{
		rt.minv=min(tl.minv,tr.minv);
	}
	void pushdown(un l,un r,un num)//下放标记
	{
		if(!rt.tag)return;
		tl.minv+=rt.tag,tl.tag+=rt.tag;
		tr.minv+=rt.tag,tr.tag+=rt.tag;
		rt.tag=0;
	}
	void modify(ll ql,ll qr,ll k,un l=0,un r=n,un num=1)//区间修改
	{
		if(ql<=l&&r<=qr)
		{
			rt.minv+=k;
			rt.tag+=k;
			return;
		}
		pushdown(l,r,num);
		un mid=(l+r)>>1;
		if(ql<=mid)modify(ql,qr,k,l,mid,num<<1);
		if(qr>mid)modify(ql,qr,k,mid+1,r,num<<1|1);
		pushup(num);
	}
	ll Qmin()//查询全局min
	{
		return t[1].minv;
	}
}sgt;
ll p[MAXN],a[MAXN];
int main()
{
	n=read();
	for(ll i=1;i<=n;++i)p[i]=read();
	for(ll i=1;i<=n;++i)a[i]=read();
	for(ll i=1;i<=n;++i)
		sgt.modify(p[i],n,a[i]);
	ll ans=INF;
	for(ll i=1;i<n;++i)//[1,i],[i+1,n]
	{
		sgt.modify(p[i],n,-a[i]);
		sgt.modify(0,p[i]-1,a[i]);
		umin(ans,sgt.Qmin());
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ix35 (赞：5)

这是一道比较水的 div2 E 题。

记 $ans(i,j)$ 表示最终 $1,\cdots,i$ 在左边，$i+1,\cdots,n$ 在右边，且初始将排列切分成 $[1,j]$，$[j+1,n]$ 两段时的最小代价。

按照升序枚举 $i$，一开始 $i=0$，则有 $ans(0,j)=\sum\limits_{k=1}^j a_i$，因为要将 $1,\cdots,j$ 位置上所有数移到右边去。

考虑如何从 $ans(i,j)$ 转移到 $ans(i+1,j)$，设 $p$ 为排列中 $i+1$ 所在的位置，则：

1. 对于 $j<p$，那么 $ans(i+1,j)=ans(i,j)+a_p$，因为原来不需要动 $i+1$，现在需要移动到左边。

2. 对于 $j\ge p$，那么 $ans(i+1,j)=ans(i,j)-a_p$，因为原来要移动到右边来，现在不需要动。

所有 $ans(i,j)$ 只需要从 $ans(i-1,j)$ 转移过来，所以可以简记为 $ans(j)$，其中 $i$ 就是当前枚举到的 $i$。转移过程中，$p$ 左边的 $ans(j)$ 要加上一个 $a_p$，$p$ 右边的 $ans(j)$ 要减去一个 $a_p$，可以用线段树优化区间加法，最后为了取得答案，询问全局最小值即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=200010;
ll n,x,sum,ans,pos[MAXN],a[MAXN],mn[MAXN*4],mk[MAXN*4];
void pd (int p) {
	if (mk[p]) {
		mn[p<<1]+=mk[p],mn[(p<<1)|1]+=mk[p];
		mk[p<<1]+=mk[p],mk[(p<<1)|1]+=mk[p];
		mk[p]=0;
	}
	return;
}
void modify (int p,int l,int r,int xl,int xr,ll v) {
	if (xr<l||r<xl) {return;}
	if (xl<=l&&r<=xr) {
		mn[p]+=v,mk[p]+=v;
		return;
	}
	pd(p);
	int mid=(l+r)>>1;
	modify(p<<1,l,mid,xl,xr,v),modify((p<<1)|1,mid+1,r,xl,xr,v);
	mn[p]=min(mn[p<<1],mn[(p<<1)|1]);
	return;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		pos[x]=i;
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		sum+=a[i];
		if (i<n) {modify(1,1,n-1,i,i,sum);}
	}
	ans=mn[1];
	for (int i=1;i<=n;i++) {
		if (pos[i]==1) {modify(1,1,n-1,1,n-1,-a[pos[i]]);}
		else if (pos[i]==n) {modify(1,1,n-1,1,n-1,a[pos[i]]);}
		else {
			modify(1,1,n-1,1,pos[i]-1,a[pos[i]]);
			modify(1,1,n-1,pos[i],n-1,-a[pos[i]]);
		}
		ans=min(ans,mn[1]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：skydogli (赞：2)

比较朴素的想法是枚举左边最大的数$\text P$是多少，再枚举左右的分界线$x$，花费为$\sum\limits_{i\leq x,p_i>P}a_i+\sum\limits_{i>x,p_i\leq P}a_i$。暴力枚举复杂度是$O(n^2)$的。

所以我们可以反过来考虑每次$\text P+1$时，各个分界线的代价的变化。我们发现，对于$\text{P+1}$所在位置的右边为分界线，代价变小了，因为不需要把这个$\text{P+1}$挪到右边。同理，对于$\text{P+1}$所在位置的左边作为分界线的代价变大了，因为要把它从右边挪过来。

那么每次让$\text P+1$时，我们会进行区间修改和取min操作，线段树维护即可。

注意，因为题目要求一开始分组不能让一组非空，所以我们$x
$的值域是$(1,n-1)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MN 200005
#define LL long long
#define Ls (x<<1)
#define Rs (x<<1|1)
#define mid ((l+r)>>1)
LL Min[MN<<3],sum[MN],tag[MN<<3];
int n,p[MN],a[MN],loc[MN];
void build(int x,int l,int r){
	if(l==r){Min[x]=sum[l];return;}
	build(Ls,l,mid);
	build(Rs,mid+1,r);
	Min[x]=min(Min[Ls],Min[Rs]);
}
void pushdown(int x){
	if(tag[x]){
		Min[Ls]+=tag[x];
		Min[Rs]+=tag[x];
		tag[Ls]+=tag[x];
		tag[Rs]+=tag[x];
		tag[x]=0;
	}
}
void change(int x,int l,int r,int b,int e,int v){
	if(l>e||r<b)return;
	if(b<=l&&r<=e){Min[x]+=v;tag[x]+=v;return;}
	pushdown(x);
	change(Ls,l,mid,b,e,v);change(Rs,mid+1,r,b,e,v);
	Min[x]=min(Min[Ls],Min[Rs]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){scanf("%d",&p[i]);loc[p[i]]=i;}
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	LL ans=min(a[1],a[n]);
	build(1,1,n-1);
   //建树，一开始使P为0，则分界点为x的代价显然是a_1...a_x
	for(int i=1;i<n;++i){
		change(1,1,n-1,loc[i],n-1,-a[loc[i]]);
		if(loc[i]!=1)change(1,1,n-1,1,loc[i]-1,a[loc[i]]);
		ans=min(ans,Min[1]);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Lyccrius (赞：1)

2200 的 CF DS 题我居然没胡出来。

$ans(i, j)$ 表示值为 $[1, i]$ 的在左边，$[i + 1, n]$ 在右边，并且将初始序列划分为 $[1, j]$ 和 $[j + 1, n]$ 的代价。

对于 $i = 0$，最后左边没有任何元素，那就要将原序列下标为 $[1, j]$ 的都转移一遍，故 $ans(0, j) = \sum_{k = 1}^j a_k$。

考虑从 $ans(i - 1)$ 转移到 $ans(i)$，设 $p$ 为 $i$ 在原序列中的位置。

* 对于 $p \gt j$，本来 $i$ 被划分到了右边，即 $[j + 1, n]$，现在要将 $i$ 移动到左边，故 $ans(i, j) = ans(i - 1, j) + a_p$
* 对于 $p \le j$，本来 $i$ 被划分到了左边，即 $[1, j]$，在计算 $i - 1$ 时 $i$ 被移动到右边，现在要将 $i$ 移回来，故 $ans(i, j) = ans(i - 1, j) - a_p$

于是对于每一个 $i$，$ans(i, j)$ 都可以从 $ans(i - 1, j)$ 转移过来，而转移的形式又是区间加减，可以使用线段树优化转移。

---

## 作者：caidzh (赞：1)

首先有一个比较显然的暴力做法，我们设定一个边界值$x$，然后枚举两个集合的分界点，在第一个集合中查询数值在$[x+1,n]$之间的权值和，在第二个集合中查询$[1,x]$的和，加起来取$\min$

但这显然是不能过的，我们考虑逐渐增大边界值$x$，同时用一种数据结构来维护第$i$个位置为分界点时的花费，接下来我们发现增大边界值可以看成在区间加，维护花费是区间$\min$，可以使用线段树来维护，复杂度$O(nlogn)$

---

## 作者：QwQ蒟蒻wjr (赞：1)

[我的blog](https://www.cnblogs.com/wangjunrui/p/12244238.html)
> > 题目链接：[CF1295E Permutation Separation](https://www.luogu.com.cn/problem/CF1295E)

$$preface$$
~~开一波E题闷声发大财~~

感谢@Karry5307 在考后提供思路

$$description$$

给定一个序列$p$(为1~n的排列)，和这个序列每一个数所对应的花费a以及序列的长度n。

取一数$1\leq k<n$，将$p$序列分成两个序列，分别是$p_1,p_2,...,p_k$和$p_{k+1},p_{k+2},...,p_n$

将两个序列的某些数移到另一个序列使得第一个序列的所有数小于第二个序列的所有数，注意如果其中一组为空，则满足此条件，移动$p_i$的花费是$a_i$

求最小花费
$$solution$$
一道裸的线段树

考虑维护$a_i$的前缀和$sum_i=\sum_{j=1}^{i}a_i$，因为$1\leq k<n$，所以前缀和$sum$最多只要维护到$a_{n-1}$即可

假设第一个序列的所有数都移到了第二个序列值最小~~虽然不大可能~~则
答案是$sum$中的最小值

因为$p$序列是1~n的排列，所以记$pos_i$为$i$在序列$p$中出现的位置

枚举i从1~n

假设将$p[pos_i]$最终在第一序列，那么$p[pos_1],p[pos_2],...,,p[pos_{i-1}]一定在最终在第一序列$，考虑当前对前缀和的修改。

当$k>=pos_i$时，$p[pos_i]$在第一序列，那么不需要费用

当$k<pos_i$时，$p[pos_i]$在第二序列，需要$a[pos_i]$的费用移动到第一序列

则将$sum_1$~$sum_{pos_i-1}$的值分别加上$a[pos_i]$

$sum_{pos_i}$~$sum_{n-1}$的值分别减去$a[pos_i]$

当前策略最小值即当前$sum$的最小值。

答案即是对所有策略的最小值取最小值

$$code$$
```cpp
#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define lc (root<<1)
#define rc (root<<1|1)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
const int N=2e5+5;
struct Tree
{
	ll minn,lazy;
} tree[N<<2];
ll sum[N];
inline void build(int root,int l,int r)
{
	if(l==r)
	{
		tree[root].minn=sum[l];
		tree[root].lazy=0;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);
	return;
}
inline void pushdown(int root)
{
	if(!tree[root].lazy)
		return;
	tree[lc].minn+=tree[root].lazy;
	tree[rc].minn+=tree[root].lazy;
	tree[lc].lazy+=tree[root].lazy;
	tree[rc].lazy+=tree[root].lazy;
	tree[root].lazy=0;
	return;
}
inline void change(int root,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[root].minn+=val;
		tree[root].lazy+=val;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(root);
	change(lc,l,mid,x,y,val);
	change(rc,mid+1,r,x,y,val);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);
	return;
}
int n,p[N],a[N],pos[N];
ll ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(p[i]);
		pos[p[i]]=i;
	}
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	build(1,1,n-1);
	ans=tree[1].minn;
	for(re int i=1; i<=n; ++i)
	{
		change(1,1,n-1,1,pos[i]-1,a[pos[i]]);
		change(1,1,n-1,pos[i],n-1,-a[pos[i]]);
//		printf("%d\n",ans);
		ans=min(ans,tree[1].minn);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

首先显然的 $O(n^2)$ 暴力，一维枚举切割的位置，假设为 $[1,k-1]$ 与 $[k,n]$，一维枚举左右两边的最终元素，假设为 $[1,s-1]$ 与 $[s,n]$。

然后我们发现，从 $k$ 转移到 $k+1$ 时，每个 $s$ 对应情况的变化其实很小。具体是这样的：

- 对于 $1 < s \le p_k$，这些情况本来要把 $p_k$ 拿到左边来，现在 $p_k$ 已经到左边了，因此权值 $-a_k$；
-  对于 $p_k < s \le n$，这些情况本来留在右边的 $p_k$ 跑到了左边去，现在要把 $p_k$ 拿回到右边来，因此权值 $+a_k$。

然后拿一个能支持区间加和查询区间最小值的东西维护即可。考虑使用线段树，时间复杂度 $O(n\log n)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll (k<<1)
#define rr (k<<1|1)
int n, p[500005], a[500005], ans = 0x3f3f3f3f3f3f3f3f;
struct tree {
	int l, r, num, lazy;
} t[3000005];
void build(int k, int l, int r) {
	t[k].l = l, t[k].r = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(ll, l, mid);
	build(rr, mid + 1, r);
	return ;
}
inline void pushup(int k) {
	t[k].num = min(t[ll].num, t[rr].num);
	return ;
}
inline void pushdown(int k) {
	if (t[k].lazy) {
		t[ll].num += t[k].lazy;
		t[rr].num += t[k].lazy;
		t[ll].lazy += t[k].lazy;
		t[rr].lazy += t[k].lazy;
		t[k].lazy = 0;
	}
	return ;
}
void update(int k, int l, int r, int c) {
	if (t[k].l > r || t[k].r < l) return ;
	if (t[k].l >= l && t[k].r <= r) {
		t[k].num += c;
		t[k].lazy += c;
		return ;
	}
	pushdown(k);
	update(ll, l, r, c);
	update(rr, l, r, c);
	pushup(k);
	return ;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	build(1, 1, n - 1);
	for (int i = 1; i <= n; i++) cin >> p[i];
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		update(1, p[i], n - 1, a[i]);
	}
	for (int i = 1; i < n; i++) {
		update(1, 1, p[i] - 1, a[i]);
		update(1, p[i], n - 1, -a[i]);
		ans = min(ans, t[1].num);
	}
	cout << min({ans, a[1], a[n]});
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

对于 $ 1 \sim n $ 的排列 $ p $ 每个位置带有权值，请找到一个将序列分为两非空段的分割点，使得通过以权值的代价分别移动一些数进入另一段后第一段所有数严格小于第二段的总代价最小。

## 分析

* 考虑枚举第一段截止点 $ k $，枚举第一段最大值 $ s $，我们发现这个时间复杂度是 $ O(n^3) $ 的。
* 考虑刻画确定首段截止点 $ k $ 时的每个数值作为 $ s $ 带来的总代价：
  * 对于位置 $ i $ 且 $ i \le k $，当且仅当 $ s<p_i $ 会导致这个位置带来 $ a_i $ 的移动代价；
  * 对于位置 $ i $ 且 $ i>k $，当且仅当 $ s \ge p_i $ 会导致这个位置带来 $ a_i $ 的代价。
  * 考虑枚举首段截止点 $ k $，然后对 $ s $ 的不同取值开值域线段树，用区间加更新代价值，最后取区间最小值，时间复杂度是 $ O(n^2 \log n) $ 的。
* 考虑扫描线首段截止点 $ k $，然后发现当 $ k $ 被增加 $ 1 $ 后，只有当前的位置 $ k $ 带来 $ a_k $ 的代价的范围会产生变化，然后区间加只需要整个程序做 $ O(n) $ 次即可，时间复杂度为 $ O(n \log n) $。
* 程序实现时，需要一棵支持区间加，区间取最小值的懒标记，参见本网站模板线段树 2。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
namespace BoatDevil {
    const int N = 2e5 + 5;
    int n;
    int p[N], a[N];
    ll d[N * 4], c[N * 4], presum[N];
    void update(int l, int r, int v, int s, int t, int p) {
        //if(s == 1 && t == n) cout << "+ " << l << " " << r << " " << v << endl;
        if(l <= s && t <= r) {
            d[p] += v, c[p] += v;
            return;
        }
        d[p * 2] += c[p], d[p * 2 + 1] += c[p], c[p * 2] += c[p], c[p * 2 + 1] += c[p];
        c[p] = 0;
        int mid = (s + t) >> 1;
        if(l <= mid) update(l, r, v, s, mid, p * 2);
        if(mid < r) update(l, r, v, mid + 1, t, p * 2 + 1);
        d[p] = min(d[p * 2], d[p * 2 + 1]);
    }
    ll query(int l, int r, int s, int t, int p) {
        if(l <= s && t <= r) return d[p];
        d[p * 2] += c[p], d[p * 2 + 1] += c[p], c[p * 2] += c[p], c[p * 2 + 1] += c[p];
        c[p] = 0;
        ll ret = (ll)1e18 + 5;
        int mid = (s + t) >> 1;
        if(l <= mid) ret = min(ret, query(l, r, s, mid, p * 2));
        if(mid < r) ret = min(ret, query(l, r, mid + 1, t, p * 2 + 1));
        return ret;
    }
    void resolve() {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]), presum[i] = presum[i - 1] + a[i];
        for(int i = 1; i <= n; i++) update(p[i], n, a[i], 1, n, 1);
        ll ans = (ll)1e18 + 5;
        for(int i = 1; i < n; i++) {
            //A<=i,B>i
            //A<=x,B>x
            //A:[1,i)+=a[i]
            //B:[i,n]+=a[i]
            if(p[i] > 1) update(1, p[i] - 1, a[i], 1, n, 1);
            update(p[i], n, -a[i], 1, n, 1);
            //cout << "Get" << endl;
            ans = min(ans, query(1, n, 1, n, 1));
            ans = min(ans, presum[i]);
            //cout << ans << endl;
        }
        printf("%lld\n", ans);
    }
};
int main() {
    BoatDevil::resolve();
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

题意看上去很简单。我们要对于区间 $[1,n]$，求 $\sum a_i  $ 满足 $1≤i≤k$ 且 $p_i>\min(p_{[k+1,n]})$。

我们考虑维护一个数组 $t_i$，记录 $\sum a_j$ 满足 $p_j<p_i$。假设我们现在把序列 $p$ 分成 $[1,k][k+1,n]$ 两个区间，那么我们求出区间 $[k+1,n]$ 的最小值 $m$，那么我们就知道了区间 $[1,k]$ 中小于 $m$ 的 $p_i$ 对应的 $a_i$ 之和。然后我们维护一个前缀和 $q_i=\sum\limits_{j=1}^i a_j$，那么我们只需要 $q_i-t_m$ 即可求出区间 $[1,k]$ 中大于 $m$ 的 $p_i$ 对应的 $a_i$ 之和。

但是我们发现，我们并没有考虑从右边移到左边的情况。但是我们知道线段树这个方法是一个好方法，所以后面我们还会用到它。

既然 $k$ 未知，那么想必我们需要枚举 $k$。我们还需要枚举最终状态的分界 $i$，因为这个序列是一个 $1\sim n$ 的排列，所以我们知道最终左边的值一定 $≤i$，右边的一定 $>i$。

我们设 $k,i$，那么考察 $a_i,k$ 的关系然后暴力计算，复杂度为 $O(n^2)$。

但是我们发现，我们枚举 $k$ 每次只有一个值被划分到了别的区间。当 $k$ 从 $k-1$ 变成 $k$ 时，我们把 $p_k$ 从右区间划分到了左区间。假设最终的区间划分为 $[1,i][i+1,n]$，那么也只有 $p_k$ 可能需要做出改变（比如可能 $p_k$ 应该在右边且初始状态下就在右边，但 $k$ 改变为 $k'$ 后导致 $p_k$ 初始状态下从右边到了左边，但是它需要去右边，这样就会多出 $a_k$ 的花费）。假设 $p_k≤k$，那么 $p$ 不需要花费 $a_k$ 来移动。反之需要。所以我们可以从答案变化的角度来看，**正难则反**。

我们记 $ans_{i,j}$ 为取 $k=j$ 时让序列划分为 $[1,i][i+1,n]$ 两个区间的花费。

那么我们可以考虑 $ans_{i,j}$ 是怎么样从 $ans_{i-1,j}$ 转移过来的。

- 如果 $j<i$，那么说明原来 $i$ 在右边，但现在要到左边，所以需要移动。$ans_{i,j}=ans{i-1,j}+a_i$。

- 如果 $j≥i$，那么说明原来 $i$ 需要从左边移动到右边，但现在不用了。所以 $ans_{i,j}=ans{i-1,j}-a_i$。

我们考虑到 $i$ 就是我们枚举的 $k$，那么我们可以维护一个一维数组 $ans_j$，当我们的 $k$ 从 $i-1$ 变成 $i$ 时，就直接维护 $ans_j$ 的值，然后全局最小值更新我们的答案。

因为在 $k$ 转移中，有上面的两种情况，所以我们需要维护一个支持区间加减的数据结构。那么就是线段树了。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*

//*/

//
using namespace std;
//
const int N=2e5+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,a[N],b,q,s[N],op,sum,p[N],ans,res,tmp,cnt[N],id[N];
int tag[N<<2];
int tot,tr[N<<2];

void pushup(int x){
	tr[x]=min(tr[x<<1],tr[x<<1|1]);
}
void pushdown(int x){
	tag[x<<1]+=tag[x];
	tag[x<<1|1]+=tag[x];
	tr[x<<1]+=tag[x];
	tr[x<<1|1]+=tag[x];
	tag[x]=0;
}


void change(int x,int l,int r,int pl,int pr,int v){
	//线段树上维护当前k下不同j取值的答案的最小值
	if(l>=pl&&r<=pr){
		tag[x]+=v;
		tr[x]+=v;
		return ;
	}
	pushdown(x);
	int mid=l+r>>1;
	if(pl<=mid)change(x<<1,l,mid,pl,pr,v);
	if(pr>mid)change(x<<1|1,mid+1,r,pl,pr,v);
	pushup(x);
	return ;
}

int query(int x,int l,int r,int pl,int pr){
	return tr[1];//返回全局最小值即可
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>n;
	for(int i=1;i<=n;i++){
		int v;
		cin>>v;
		p[v]=i;//记录数字v的位置
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		if(i!=n)change(1,1,n-1,i,i,sum);
	}
	ans=a[1];
	
//	cerr<<"OK\n";
	
	for(int k=1;k<=n;k++){
		if(p[k]==1)change(1,1,n-1,1,n-1,-a[p[k]]);
		else if(p[k]==n)change(1,1,n-1,1,n-1,a[p[k]]);
		else{
			change(1,1,n-1,1,p[k]-1,a[p[k]]);
			change(1,1,n-1,p[k],n-1,-a[p[k]]);
	 		
		} 
		ans=min(ans,query(1,1,n-1,1,n-1));
	}
	
	cout<<ans<<endl;
	return 0;
}

//check your long long and the size of memery!!!

```




---

## 作者：E1_de5truct0r (赞：0)

## 思路

第一思路就是暴力，毕竟用到数据结构的题肯定先打暴力再优化。

最暴力的算法显然是 $O(n)$ 枚举断点，再 $O(n^2)$ 算一下这样的贡献。这样显然是过不了的，而且最多把后面算贡献变成 $O(n \log n)$，总的复杂度还是 $O(n^2 \log n)$ 级别的。那么怎么办呢？

我们可以联想到一些题目，总体求贡献是困难的，但是如果我们对于每个个体算出它对答案的总贡献，是不是更容易呢？因此，我们可以先考虑枚举每一个断点 $i$，进而求出每一个 $p_i$ 对答案的贡献。

首先，令 $f_{i,j}$ 表示从 $i$ 切分，最后是分成 $[1,j]$ 和 $[j+1,n]$ 的方案数。每次转移的时候我们不从枚举 $j$ 入手，而是对于每一个 $p_i$，算出它对于 $j$ 取值的贡献。显然对于 $j \leq p_i$，是需要移动的，否则不需要。所以我们每次枚举断点，然后用线段树维护这 $n$ 个值，每次查询全局最小值即可。

最后呢，显然的，$f_{0,j} = \sum\limits_{k=1}^{j} a_k$，因为要把这些都移到右边。

```cpp
#include <bits/stdc++.h>
#define ll __int128
using namespace std;
ll read()
{
	ll w=0;bool f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=0;
	for(;isdigit(ch);ch=getchar())w=(w<<1)+(w<<3)+(ch^48);
	return f?w:-w;
}
void write(ll x)
{
	if(x>9) write(x/10);
	putchar(x%10+48);
}
const ll MAXN=200005;
ll p[MAXN],a[MAXN];
ll tr[MAXN<<4],tag[MAXN<<4];
void push_down(ll p,ll l,ll r)
{
	tr[p<<1]+=tag[p];
	tr[p<<1|1]+=tag[p];
	tag[p<<1]+=tag[p];
	tag[p<<1|1]+=tag[p];
	tag[p]=0;
}
void upd(ll p,ll l,ll r,ll st,ll en,ll k)
{
	if(r<st || l>en) return;
	if(st<=l && r<=en)
	{
		tr[p]+=k;
		tag[p]+=k;
		return;
	}
	push_down(p,l,r);
	ll mid=(l+r)>>1;
	upd(p<<1,l,mid,st,en,k);
	upd(p<<1|1,mid+1,r,st,en,k);
	tr[p]=min(tr[p<<1],tr[p<<1|1]);
}
signed main()
{
	ll n; n=read();
	for(ll i=1;i<=n;i++) p[i]=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=1;i<=n;i++) upd(1,0,n,p[i],n,a[i]);
	ll ans=1e25;
	for(ll i=1;i<n;i++)
	{
		upd(1,0,n,p[i],n,-a[i]);
		upd(1,0,n,0,p[i]-1,a[i]);
		ans=min(ans,tr[1]);
	}
	write(ans);
	return 0;
}
```

---

