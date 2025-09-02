# [USACO21OPEN] United Cows of Farmer John P

## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）将要选派一个代表队参加国际牛学奥林匹克（International bOvine olympIad，IOI）。

有 $N$ 头奶牛参加了代表队选拔。她们站成一行，奶牛 $i$ 的品种为 $b_i$。

代表队将会由包含至少三头奶牛的连续区间组成——也就是说，对于满足 $1\le l<r\le N$ 且 $r−l\ge 2$ 的奶牛 
$l\dots r$。选定区间内的三头奶牛将会被指定为领队。出于法律原因，最边上的两头奶牛必须是领队。此外，为了避免种内冲突，每一名领队都必须与代表队的其他成员（包括领队）品种不同。

请帮助 UCFJ 求出（由于纳税原因）他们可以选派参加 IOI 的代表队的方法数。如果两个代表队拥有不同的成员或不同的领队，则被认为是不同的。 

## 说明/提示

#### 样例解释

每一代表队对应以下的一组领队：

$$(1,2,3),(1,2,4),(1,3,4),(1,4,7),(2,3,4),(4,5,6),(4,5,7),(4,6,7),(5,6,7).$$

#### 数据范围与约定

$1\le N\le 2\times 10^5$

## 样例 #1

### 输入

```
7
1 2 3 4 3 2 5```

### 输出

```
9```

# 题解

## 作者：xiaofu15191 (赞：10)

今天模拟赛遇到的题目。第一眼看上去就像数据结构，可是不会打。以为是分块计数然后算之类的（虽然实际上也能用分块维护）。赛后弄了半天才想通。

首先我们设 $pre_i$ 为 $b_i$ 在数组中上一次出现的位置。

接着我们从前往后枚举变量 $r$，即我们要选的区间右端点。这个时候我们需要做到 $O(\log n)$ 来查询对于一个右端点的可行答案。

先考虑此时有哪些左端点可选。发现左端点只可能位于 $[pre_i+1,i-1]$ 中。那么就考虑怎么选中间的领队 $mid$。

回过头来，我们来看看枚举变量 $r$ 时每个元素如何影响答案。

首先，我们找到 $pre_r$，它不可以作为左端点更新答案了；同时，$[pre_{pre_r}+1,pre_r-1]$ 因为在 $r$ 出现了 $b_r$，这段区间中的 $b_i$ 不可以再作为中间点了。

因此，我们可以使用线段树维护答案，对于每个节点维护其区间内可作为左端点的数字个数 $lsum$，可作为中间点的数字个数 $midsum$ 以及对答案的贡献 $sum$。

枚举 $r$ 时，按照上面的步骤处理 $pre_r$，然后更新最终答案 $ans$；接着，$r$ 可作为左端点了，$[pre_i+1,r-1]$ 也可作为中间点了。

具体实现可见代码。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
long long n,num[200010],where[200010],pre[200010];
struct node
{
	long long l_num,mid_num,sum,lazy;
}tree[800010];
void pushup(long long now)
{
	tree[now].sum=tree[now<<1].sum+tree[now<<1|1].sum;
	tree[now].l_num=tree[now<<1].l_num+tree[now<<1|1].l_num;
	tree[now].mid_num=tree[now<<1].mid_num+tree[now<<1|1].mid_num;
}
void pushdown(long long now)
{
	tree[now<<1].lazy+=tree[now].lazy;
	tree[now<<1].mid_num+=tree[now].lazy;
	tree[now<<1].sum+=tree[now].lazy*tree[now<<1].l_num;
	tree[now<<1|1].lazy+=tree[now].lazy;
	tree[now<<1|1].mid_num+=tree[now].lazy;
	tree[now<<1|1].sum+=tree[now].lazy*tree[now<<1|1].l_num;
	tree[now].lazy=0;
}
void update_l(long long now,long long l,long long r,long long x,long long k)
{
	if(r<x||l>x) return;
	if(l==r)
	{
		tree[now].l_num+=k;
		tree[now].sum=tree[now].l_num*tree[now].mid_num;
		return;
	}
	pushdown(now);
	long long mid=(l+r)>>1;
	if(x<=mid) update_l(now<<1,l,mid,x,k);
	else update_l(now<<1|1,mid+1,r,x,k);
	pushup(now);
}
void update_mid(long long now,long long l,long long r,long long x,long long y,long long k)
{
	if(r<x||l>y) return;
	if(x<=l&&r<=y)
	{
		tree[now].mid_num+=k;
		tree[now].lazy+=k;
		tree[now].sum+=tree[now].l_num*k;
		return;
	}
	pushdown(now);
	long long mid=(l+r)>>1;
	if(x<=mid) update_mid(now<<1,l,mid,x,y,k);
	if(y>mid) update_mid(now<<1|1,mid+1,r,x,y,k);
	pushup(now);
}
long long query(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return 0;
	if(x<=l&&r<=y) return tree[now].sum;
	pushdown(now);
	long long mid=(l+r)>>1,res=0;
	if(x<=mid) res+=query(now<<1,l,mid,x,y);
	if(y>mid) res+=query(now<<1|1,mid+1,r,x,y);
	return res;
}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&num[i]);
		pre[i]=where[num[i]];
		where[num[i]]=i;
	}
	long long ans=0;
	for(long long i=1;i<=n;i++)
	{
		if(pre[i])
		{
			update_l(1,1,n,pre[i],-1);
			update_mid(1,1,n,pre[pre[i]]+1,pre[i]-1,-1);
		}
		ans+=query(1,1,n,pre[i]+1,i-1);
		update_l(1,1,n,i,1);
		update_mid(1,1,n,pre[i]+1,i-1,1);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：UltiMadow (赞：8)

考虑枚举每个区间的右端点，用线段树维护每个左端点对答案的贡献

设当前枚举到的点为 $i$，值为 $b_i$，上一个出现 $b_i$ 的位置为 $pre_{b_i}$，显然左端点只能在 $(pre_{b_i},i-1)$ 范围内取

考虑新加入一个点 $x$ 对每个左端点的贡献，那么所有在 $(pre_{b_x},x)$ 中的左端点的方案数都可以 +1（这些左端点可以选 $x$ 作为中间点）

还有一个问题就是能作为左端点的点不一定连续，所以可以在线段树中维护一个等于 $0/1$ 的系数，表示这个点是否可以作为左端点

那么这个线段树需要支持的操作就是单点改系数，区间加，区间查询，于是随便打一个标记维护一下即可

时间复杂度 $\mathcal O(n\log n)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 200010
#define int long long
using namespace std;
int n,b[MAXN];
struct segtree{
	int t[MAXN<<2],sz[MAXN<<2];
	//  answer     size
	int val[MAXN<<2],tag[MAXN<<2];
	//  real         lazytag
	void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];sz[p]=sz[p<<1]+sz[p<<1|1];}
	void pushdown(int p){
		if(!tag[p])return;
		val[p<<1]+=tag[p];val[p<<1|1]+=tag[p];
		t[p<<1]+=tag[p]*sz[p<<1];t[p<<1|1]+=tag[p]*sz[p<<1|1];
		tag[p<<1]+=tag[p];tag[p<<1|1]+=tag[p];
		tag[p]=0;
	}
	void update(int p,int l,int r,int pos,int sgn){
		//size modify
		if(l==r){sz[p]+=sgn;t[p]=sz[p]*val[p];return;}
		pushdown(p);int mid=(l+r)>>1;
		if(pos<=mid)update(p<<1,l,mid,pos,sgn);
		else update(p<<1|1,mid+1,r,pos,sgn);
		pushup(p);
	}
	void modify(int p,int l,int r,int L,int R,int sgn){
		//real number modify
		if(L>R)return;
		if(L<=l&&r<=R){
			tag[p]+=sgn;val[p]+=sgn;
			t[p]+=sgn*sz[p];return;
		}pushdown(p);int mid=(l+r)>>1;
		if(L<=mid)modify(p<<1,l,mid,L,R,sgn);
		if(R>mid)modify(p<<1|1,mid+1,r,L,R,sgn);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(L>R)return 0;
		if(L<=l&&r<=R)return t[p];
		pushdown(p);int mid=(l+r)>>1;
		if(R<=mid)return query(p<<1,l,mid,L,R);
		if(L>mid)return query(p<<1|1,mid+1,r,L,R);
		return query(p<<1,l,mid,L,R)+query(p<<1|1,mid+1,r,L,R);
	}
}T;
int pre[MAXN],ppre[MAXN],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++){
		int now=b[i];
		if(pre[now])T.update(1,1,n,pre[now],-1);
		if(pre[now])T.modify(1,1,n,ppre[now]+1,pre[now]-1,-1);
		ans+=T.query(1,1,n,pre[now]+1,i-1);
		T.modify(1,1,n,pre[now]+1,i-1,1);T.update(1,1,n,i,1);
		ppre[now]=pre[now];pre[now]=i;
	}printf("%lld",ans);
	return 0;
}
```

---

## 作者：too_later (赞：6)

[link](https://www.luogu.com.cn/problem/P7530)

### 大致题意：

有 $N$ 头奶牛参加了代表队选拔。她们站成一行，奶牛 $i$ 的品种为 $b_i$。

代表队将会由包含至少三头奶牛的连续区间组成——也就是说，对于满足 $1\le l<r\le N$ 且 $r-l\ge 2$ 的奶牛 $l\dots r$。选定区间内的三头奶牛将会被指定为领队。出于法律原因，最边上的两头奶牛必须是领队。此外，为了避免种内冲突，每一名领队都必须与代表队的其他成员（包括领队）品种不同。

请帮助 UCFJ 求出（由于纳税原因）他们可以选派参加 IOI 的代表队的方法数。如果两个代表队拥有不同的成员或不同的领队，则被认为是不同的。

$1\le n\le 2\times 10^5$。

### Sol.

模拟赛考到这题，然后就懵掉了。

首先肯定是枚举一个右端点 $r$，然后确定 $l$ 和 $mid$。

肯定有如下性质：

- $l,mid$ 在 $r$ 的前驱的后面。

- $l$ 在 $mid$ 的前驱的后面。

- $l,mid$ 的后继在 $r$ 的后面。

第一个条件翻译：$l,mid\in [L_r+1,r-1]$。

第二个条件翻译：$l\in [L_{mid}+1,mid-1]$。

第三个条件翻译：$l,mid$ 是在 $[L_{r}+1,r-1]$ 中最后出现的。

先考虑第二个条件，对于每个 $i$ ，如果他做 $mid$，那么 $l$ 必须在 $[L_i+1,i-1]$ 中选取，在这里打上标记。

再考虑第一个条件：在线段树上只考虑区间 $[L_r+1,r-1]$。

第三个条件：如果 $pre$ 出现过的话那么久把他删掉。

然后就做完了。

时间复杂度 $O(n\log n)$。

### Code:

```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define I inline
#define RI register int
#define rep(i,a,b) for(RI i=a;i<=b;++i)
#define dow(i,a,b) for(RI i=a;i>=b;--i)
using namespace std;
const int N=4e5+5;
struct Segment_Tree{
	struct tree{
		int l,r,sz,val,tag;
		long long sum;
	} tr[N<<1];
	I void build(int l,int r,int p){
		tr[p].l=l,tr[p].r=r;
		if(l==r) return;
		RI mid=l+r>>1;
		build(l,mid,ls),build(mid+1,r,rs);
	}
	I void up(int p){
		tr[p].sz=tr[ls].sz+tr[rs].sz;
		tr[p].sum=tr[ls].sum+tr[rs].sum;
	}
	I void down(int p){
		if(tr[p].tag){
			tr[ls].tag+=tr[p].tag,tr[ls].val+=tr[p].tag,tr[ls].sum+=1ll*tr[ls].sz*tr[p].tag;
			tr[rs].tag+=tr[p].tag,tr[rs].val+=tr[p].tag,tr[rs].sum+=1ll*tr[rs].sz*tr[p].tag;
			tr[p].tag=0;
		}
	}
	I void update_size(int pos,int p,int v){
		if(tr[p].l==tr[p].r)
			return tr[p].sz+=v,tr[p].sum=1ll*tr[p].sz*tr[p].val,void();
		RI mid=tr[p].l+tr[p].r>>1;
		down(p);
		if(pos>mid) update_size(pos,rs,v);
		else update_size(pos,ls,v);
		up(p);
	}
	I void update_Val(int l,int r,int p,int v){
		if(l>r) return;
		if(tr[p].l==l&&tr[p].r==r){
			tr[p].tag+=v;
			tr[p].val+=(tr[p].r-tr[p].l+1)*v;
			tr[p].sum+=tr[p].sz*v;
			return;
		}
		down(p);
		RI mid=tr[p].l+tr[p].r>>1;
		if(l>mid) update_Val(l,r,rs,v);
		else if(r<=mid) update_Val(l,r,ls,v);
		else update_Val(l,mid,ls,v),update_Val(mid+1,r,rs,v);
		up(p);
	}
	I long long query(int l,int r,int p){
		if(l>r) return 0;
		if(tr[p].l==l&&tr[p].r==r)
			return tr[p].sum;
		RI mid=tr[p].l+tr[p].r>>1;
		down(p);
		if(l>mid) return query(l,r,rs);
		else if(r<=mid) return query(l,r,ls);
		else return query(l,mid,ls)+query(mid+1,r,rs);
	}
} T;
int n,a[N],vis[N],pre[N];
long long ans;
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]),pre[i]=vis[a[i]],vis[a[i]]=i;
	T.build(1,n,1);
	rep(i,1,n){
		if(pre[i])
			T.update_size(pre[i],1,-1),T.update_Val(pre[pre[i]]+1,pre[i]-1,1,-1);
		ans+=T.query(pre[i]+1,i-1,1);
		T.update_size(i,1,1),T.update_Val(pre[i]+1,i-1,1,1);
	}
	return printf("%lld\n",ans),0;
}
```

### 总结：

遇到多条件的时候，一定不要慌，一个一个写出来，再逐个破解。不要慌了神，用瞪眼法瞎想。

还有区间乘法的思想真的很妙，按位相乘，扩大范围，用合法的区间来查看。

---

## 作者：hyxgg (赞：3)

[题目](https://www.luogu.com.cn/problem/P7530)

### 前言

老实说我看不大懂其他题解，秉持着自己淋过雨就要想着为别人撑把伞的原则，我决定用大白话写一篇像我一样的蒟蒻也能看懂的题解。

### 题目
题目意思比较好懂，就不再赘述了。

### 思路
设左边的领队，中间的领队，右边的领队的位置分别为 $l,x,r$。

首先枚举 $r$，设 $r$ 之前最后一个值为 $b_r$ 的位置为 $q_{b_r}$。  
则 $l$、$x$ 满足：

$$q_{b_r}<l<x<r$$

此时我们只要知道对于每个 $l$ 有多少个合法的 $x$，就可以通过线段树的区间求和求出右领队为 $r$ 时的个数，再加到答案里。

问题是怎么维护对于每个 $l$ 合法的 $x$ 的个数。

首先，需要声明的是，为了更方便地区间修改、区间查询、和单点修改，我们选择用线段树来维护。

现在考虑如何更新线段树：当我们每处理完一个 $r$，这个 $r$ 就可以作为新的 $r$ 的 $x$ 或 $l$（但只有新的 $x$ 对我们维护的线段树有影响）。

此时我们得到了一个新的 $x$，我们就可以用它更新线段树了。

在确定了 $x$ 的情况下，合法的 $l$ 一定满足：

$$q_{b_x}<l<x$$

而这些合法的 $l$ 一定会多一种方案，所以我们可以写个区间修改把这些值全部加一。

但新的问题出现了，随着 $r$ 的不断增加，会有一些本来合法 $l$ 和 $x$ 变得不合法，我们需要加以处理。

首先对于 $l$ 的不合法状态，当出现 $b_l=b_r$ 时，对于之后 $r$ 这个位置都不能作为左端点，我们也就在 $l=q_{b_r}$ 时进行处理。

为了处理这种情况，我们可以在线段树里多维护一个值，即对于每个区间中合法的 $l$ 的个数，增减的时候都用这个个数值而不是用总数处理。

而当我们处理完了一个 $r$ 时，我们就把 $q_{b_r}$ 的个数变为零。

其次是 $x$ 的不合法情况，当出现 $b_x=b_r$ 时，对于之后的 $r$，这个位置都不能作为中间点，我们也在此时进行处理。

怎么处理呢？我们考虑之前这个位置作为 $x$ 给哪些 $l$ 增加了方案数，结合上文，他给 $q_{b_x}<l<x$ 的所有 $l$ 加了一，那现在我们就把这个区间再减一就好了。（为了方便，可以再开一个数组表示上上个某个 $b$ 值的位置）

最后梳理一遍做法：

遍历 $r$，将答案加上 $q_{b_r}<l<r$ 的所有合法的 $l$ 值，将 $r$ 作为 $x$ 时合法的 $l$ 的值加一，将 $q_{b_r}$ 作为 $l$、$x$ 时的不合法情况处理掉，最后输出答案。

代码如下。
```
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
struct shu
{
    ll z,l,r,gs,bj;
    // 值，节点维护的区间的左右端，区间内合法 l 的个数，懒标记
}yd[800005];
ll n,b[200005];
void js(ll l,ll r,ll bh){ //线段树的初始化
    yd[bh].l=l,yd[bh].r=r,yd[bh].gs=r-l+1;
    if(l==r){
        return ;
    }
    ll mid=(l+r)>>1;
    js(l,mid,bh*2),js(mid+1,r,bh*2+1);
}
void down(ll bh){ //将当前节点的懒标记更新到子节点上
    yd[2*bh].z+=yd[bh*2].gs*yd[bh].bj,yd[2*bh].bj+=yd[bh].bj;
    yd[2*bh+1].z+=yd[bh*2+1].gs*yd[bh].bj,yd[2*bh+1].bj+=yd[bh].bj;
    yd[bh].bj=0;
}
void up(ll bh){//由子节点的值更新当前结点的值
    yd[bh].gs=yd[2*bh].gs+yd[2*bh+1].gs,yd[bh].z=yd[bh*2].z+yd[bh*2+1].z;
}
void gc(ll l,ll r,ll bh,ll z){//区间更改
    if(yd[bh].l>=l&&yd[bh].r<=r){
        yd[bh].z+=yd[bh].gs*z;//用合法个数乘每个点的增量就是这个区间的增量
        yd[bh].bj+=z;
    }
    else{
        down (bh);
        if(l<=yd[2*bh].r)gc(l,r,bh*2,z);
        if(r>=yd[2*bh+1].l)gc(l,r,bh*2+1,z);
        up(bh);
    }
}
void gl(ll d,ll bh){//将不合法的 l 处理掉
    if(yd[bh].r==yd[bh].l)yd[bh].gs=0,yd[bh].z=0;
    else{
        down(bh);
        if(d<=yd[2*bh].r)gl(d,bh*2);
        else gl(d,bh*2+1);
        up(bh);
    }
}
ll cx(ll l,ll r,ll bh){//区间查询
    if(r<l)return 0;
    if(yd[bh].l>=l&&yd[bh].r<=r){
        return yd[bh].z;
    }
    else{
        ll s=0;
        down(bh); 
        if(l<=yd[2*bh].r)s+=cx(l,r,2*bh);
        if(r>=yd[2*bh+1].l)s+=cx(l,r,2*bh+1);
        return s;
    }
}
ll sg[200005],ssg[200005];
//上个 b_r 和 上上个 b_r 的位置
int main(){
    scanf("%lld",&n);
    ll ans=0;
    js(1,n,1);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&b[i]);
        if(i-2>0)ans+=cx(sg[b[i]]+1,i-1,1);
        if(i-1)gc(sg[b[i]]+1,i-1,1,1);
        if(sg[b[i]])gl(sg[b[i]],1);
        if(sg[b[i]]>1)gc(ssg[b[i]]+1,sg[b[i]]-1,1,-1);
        ssg[b[i]]=sg[b[i]],sg[b[i]]=i;
        //处理的时候别忘了判断是否越界
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Kuoy (赞：3)

声明：本题解是搬运并翻译了此题出题人 Benjamin Qi 的解题报告。

注意：本题解内我将奶牛们标号为 $0 \cdots N-1$ 而不是 $1 \cdots N$。

为了在 $O(N^{2})$ 的时间内解决本题，我们可以将右端点 $r$ 固定并从右往左遍历左端点 $l$。设 $unique_{l,r}$ 表示区间 $l \cdots r$ 内品种独特的牛的数量。

当我们将左端点 $l$ 左移一位（减少 $1$）时：

 - 如果 $B_{l}=B_{r}$，证明奶牛 $r$ 不能作为代表队 $(l,r)$ 的领队。那此时结束操作。
 - 如果 $B_{l}$ 在 $l \cdots r$ 中是没出现过，那么将 $unique_{l+1,r-1}$ 统计入答案中，并令 $unique_{l,r-1}=unique_{l+1,r-1+1}$。
 - 如果 $B_{l}$ 在 $l+1 \cdots r$ 中出现过，证明 $B_l$ 在 $l+1 \cdots r$ 中是唯一的而在 $l \cdots r$ 中不是。那令 $unique_{l,r-1}=unique_{l+1,r-1}-1$
 
具体代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
 
int main() {
	int N; cin >> N;
	vector<int> B(N); for (int& b: B) cin >> b;
	int64_t ans = 0;
	for (int r = 0; r < N; ++r) {
		vector<int> occ(N+1);
		int unique = 0;
		for (int l = r-1; l >= 0; --l) {
			if (B[l] == B[r]) break;
			int& o = occ[B[l]]; ++o;
			if (o == 1) {
				ans += unique;
				++unique;
			} else if (o == 2) {
				--unique;
			}
		}
	}
	cout << ans << "\n";
}
```

实际上，我们就是在计算对于每个 $0 \cdots N-1$ 中的 右端点 $r$ 的 $active_{r}[l]$，$unique_{r}[l]$ 和 $val_{r}[l]$。其中对于每一个 $l \le r$ 我们定义：

 - 若 $B_{l}$ 在 $B_{l},B_{l+1} \cdots B_{r}$ 是唯一的，则 $active_{r}[l]=1$ 否则 $active_{r}[l]=0$.
 - $unique_{r}[l]=unique_{l+1,r-1}$
 - $val_{r}[l]=active_{r}[l] \times unique_{l+1,r-1}$

对于每个 $r$，我们将 $val_r$ 的后缀加入答案中。

为了在 $O(N \log N)$ 的时间内解决这个问题，我们必须高效地将 $r$ 从 $r-1$ 处转移来。定义 $prev\_oc[j]$ 表示最大的 $i$ （$i<j$）满足 $B_i=B_j$。除了下列的更改外 $active_r$ 和 $unique_r$ 都分别与 $active_{r-1}$ 和 $unique_{r-1}$ 相同：

 - $active_{r}[r]=1$
 - $active_{r}[prev\_oc[r]]=0$
 - $unique_{r}[prev\_oc[r] \cdots r-1]$ 必须逐个递增 $1$ （每个都必须比前一个大 $1$）
 - $unique_{r}[prev\_oc[prev\_oc[r]] \cdots prev\_oc[r]-1]$ 必须逐个递减 $1$（每个都必须比前一个小 $1$）
 
这些更新以及对于 $val_r$ 的区间和查询，每个都可以通过使用 [带下传懒标记的线段树](https://usaco.guide/plat/RURQ#lazy-segment-tree) 在 $O(N \log N)$ 内被解决。对于在线段树上的区间 $x \cdots y$，我们维护 $\sum_{i=x}^{y}active_{r}[i]$，$\sum_{i=x}^{y}val_r[i]$ 和一个表示区间值变化的懒标记。你可以在题目 [数干草垛](http://www.usaco.org/current/data/sol_haybales_platinum_dec15.html) 的解题报告中找到关于线段树的介绍。

```cpp
#include<bits/stdc++.h>
using namespace std;

using T = uint64_t;
const int SZ = 1<<18;

struct LazySeg {
	T sum[2*SZ], lazy[2*SZ], num_active[2*SZ];
	LazySeg() {
		for (int i = 0; i < SZ; ++i) 
			num_active[SZ+i] = 1;
		for (int i = SZ-1; i > 0; --i) 
			num_active[i] = num_active[2*i]+num_active[2*i+1];
	}
	void push(int ind, int L, int R) {
		sum[ind] += num_active[ind]*lazy[ind];
		if (L != R) for (int i = 0; i < 2; ++i) 
			lazy[2*ind+i] += lazy[ind];
		lazy[ind] = 0;
	}
	void pull(int ind) {
		sum[ind] = sum[2*ind]+sum[2*ind+1];
		num_active[ind] = num_active[2*ind]+num_active[2*ind+1];
	}
	void increment(int lo,int hi, int val, int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = val; push(ind,L,R); return; }
		int M = (L+R)/2; 
		increment(lo,hi,val,2*ind,L,M); 
		increment(lo,hi,val,2*ind+1,M+1,R); 
		pull(ind);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=SZ-1) {
		push(ind,L,R); 
		if (lo > R || L > hi) return 0;
		if (lo <= L && R <= hi) return sum[ind];
		int M = (L+R)/2;
		return query(lo,hi,2*ind,L,M)+query(lo,hi,2*ind+1,M+1,R);
	}
	void deactivate(int pos, int ind=1, int L=0, int R=SZ-1) {
		push(ind,L,R); 
		if (pos > R || L > pos) return;
		if (pos <= L && R <= pos) {
			assert(num_active[ind] == 1);
			sum[ind] = num_active[ind] = 0;
			return;
		}
		int M = (L+R)/2; 
		deactivate(pos,2*ind,L,M);
		deactivate(pos,2*ind+1,M+1,R);
		pull(ind);
	}
} Seg;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	vector<int> B(N); for (int& b: B) cin >> b;
	vector<int> last(N+1,-1), prev_oc(N);
	int64_t ans = 0;
	for (int r = 0; r < N; ++r) {
		int& last_oc = last[B[r]];
		ans += Seg.query(last_oc+1,SZ-1);
		if (last_oc != -1) {
			Seg.deactivate(last_oc);
			Seg.increment(prev_oc[last_oc],last_oc-1,-1);
		}
		Seg.increment(last_oc,r-1,1);
		prev_oc[r] = last_oc; last_oc = r;
	}
	cout << ans << "\n";
}
```

丹尼·米塔尔（Danny Mittal）的代码：

```cpp
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
 
public class TriplesOfCows {
 
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] last2 = new int[n + 1];
        int[] last = new int[n + 1];
        long answer = 0;
        SegmentTree segTree = new SegmentTree(n);
        for (int j = 1; j <= n; j++) {
            int k = Integer.parseInt(tokenizer.nextToken());
            segTree.updateSingle(last[k], -1);
            segTree.updateRange(last2[k] + 1, last[k] - 1, -1);
            answer += segTree.query(last[k] + 1, j - 1);
            segTree.updateRange(last[k] + 1, j - 1, 1);
            segTree.updateSingle(j, 1);
            last2[k] = last[k];
            last[k] = j;
        }
        System.out.println(answer);
    }
 
    static class SegmentTree {
        final int n;
        final long[] value = new long[530000];
        final long[] singles = new long[530000];
        final long[] lazy = new long[530000];
 
        SegmentTree(int n) {
            this.n = n;
        }
 
        void propagate(int node) {
            value[2 * node] += lazy[node] * singles[2 * node];
            value[(2 * node) + 1] += lazy[node] * singles[(2 * node) + 1];
            lazy[2 * node] += lazy[node];
            lazy[(2 * node) + 1] += lazy[node];
            lazy[node] = 0;
        }
 
        void updateSingle(int index, long delta, int node, int segFrom, int segTo) {
            if (segFrom == segTo) {
                value[node] += delta * lazy[node];
                singles[node] += delta;
            } else {
                propagate(node);
                int mid = (segFrom + segTo) / 2;
                if (index <= mid) {
                    updateSingle(index, delta, 2 * node, segFrom, mid);
                } else {
                    updateSingle(index, delta, (2 * node) + 1, mid + 1, segTo);
                }
                value[node] = value[2 * node] + value[(2 * node) + 1];
                singles[node] = singles[2 * node] + singles[(2 * node) + 1];
            }
        }
 
        void updateSingle(int index, long delta) {
            if (index > 0) {
                updateSingle(index, delta, 1, 1, n);
            }
        }
 
        void updateRange(int from, int to, long delta, int node, int segFrom, int segTo) {
            if (segTo < from || to < segFrom) {
 
            } else if (from <= segFrom && segTo <= to) {
                value[node] += delta * singles[node];
                lazy[node] += delta;
            } else {
                propagate(node);
                int mid = (segFrom + segTo) / 2;
                updateRange(from, to, delta, 2 * node, segFrom, mid);
                updateRange(from, to, delta, (2 * node) + 1, mid + 1, segTo);
                value[node] = value[2 * node] + value[(2 * node) + 1];
                singles[node] = singles[2 * node] + singles[(2 * node) + 1];
            }
        }
 
        void updateRange(int from, int to, long delta) {
            updateRange(from, to, delta, 1, 1, n);
        }
 
        long query(int from, int to, int node, int segFrom, int segTo) {
            if (segTo < from || to < segFrom) {
                return 0;
            } else if (from <= segFrom && segTo <= to) {
                return value[node];
            } else {
                propagate(node);
                int mid = (segFrom + segTo) / 2;
                return query(from, to, 2 * node, segFrom, mid) + query(from, to, (2 * node) + 1, mid + 1, segTo);
            }
        }
 
        long query(int from, int to) {
            return query(from, to, 1, 1, n);
        }
    }
}
```

~~译者总结~~

固定右端点 $r$，然后找左端点 $l$ 满足 $[l,r]$ 中没有与 $l$ 相同品种的牛。

之后对于这个 $[l,r]$ 找一下里面有多少个牛的品种是唯一一次出现的。

都是线段树维护。每次结果乘起来加进答案里，没了。

---

## 作者：XL4453 (赞：2)

### 解题思路：

整体思路是依次加入每一个位置，然后用线段树统计出当前位置作为右端点时的贡献。

首先要求作为端点的领队不能和队伍中的任何一个成员的种类相同，这也就是说只能在上一个该种族出现的位置之后的位置中找统计贡献。

同时，一个位置可以作为左端点也就是要求这个位置之后的所有位置上不存在和这个节点相同的种类。也就是每一个种类只有最后一个可以作为左端点为后续的右端点提供贡献。

最后考虑中间的节点，某一个位置可以作为中间的领队也就是要求这个节点在所要的左节点之后，而且在这个左节点到右节点之间只存在一个这样的种类奶牛。换言之，就是说只在最靠右的到第二靠右的节点之间的左节点可以使用这个种类的奶牛作为中间节点产生贡献。

---
实现上可以采用线段树进行维护，记录下一个左节点权值 $val$ 和实际可能作为左节点产生贡献的个数 $size$，以及统计结果的 $ans$。

对于一个新加入的节点，将这个节点前一个节点到再前一个节点直接产生的贡献取消，并取消前一个节点作为左端点的可能性。统计当前节点到上一个相同种类之间节点作为左端点的贡献之和。

然后更新当前节点的贡献，将所有在上一个相同种类的节点到当前节点之间的可能左端点都加上一个可能的中间端点的贡献，然后将当前节点的设置为可能作为左端点等待被更新。

---
特别注意，在 $\text{push down}$ 标记的时候，千万不要和正常的线段树一样直接用 $size\times val$ 进行更新，而是直接将标记加到 $ans$ 上，因为所有的非叶子节点的 $val$ 都是没有意义的空变量。

~~这个错误调了一年。~~

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN=200005;
struct str{
	int sz,val,ans,tag;
}t[MAXN*4];
int n,a[MAXN],last[MAXN],pre_last[MAXN],ans;
void push_up(int p){
	t[p].ans=t[p<<1].ans+t[p<<1|1].ans;
	t[p].sz=t[p<<1].sz+t[p<<1|1].sz;
}
void push_down(int p){
	if(t[p].tag==0)return;
	
	t[p<<1].tag+=t[p].tag;
	t[p<<1].val+=t[p].tag;
	t[p<<1].ans+=t[p].tag*t[p<<1].sz;
	
	t[p<<1|1].tag+=t[p].tag;	
	t[p<<1|1].val+=t[p].tag;
	t[p<<1|1].ans+=t[p].tag*t[p<<1|1].sz;
	
	t[p].tag=0;
}
void modify_size(int p,int l,int r,int x,int val){
	if(l==r){
		t[p].sz+=val;
		t[p].ans=t[p].sz*t[p].val;
		return;
	}
	push_down(p);
	int mid=l+r>>1;
	if(x<=mid)modify_size(p<<1,l,mid,x,val);
	else modify_size(p<<1|1,mid+1,r,x,val);
	push_up(p);
}
void modify_val(int p,int l,int r,int L,int R,int val){
	if(L>R)return;
	if(L<=l&&r<=R){
		t[p].tag+=val;
		t[p].val+=val;
		t[p].ans+=val*t[p].sz;
		return;
	}
	push_down(p);
	int mid=l+r>>1;
	if(L<=mid)modify_val(p<<1,l,mid,L,R,val);
	if(R>mid)modify_val(p<<1|1,mid+1,r,L,R,val);
	push_up(p);
}
int query(int p,int l,int r,int L,int R){
	if(L>R)return 0;
	if(L<=l&&r<=R)return t[p].ans;
	push_down(p);
	int mid=l+r>>1;
	if(R<=mid)return query(p<<1,l,mid,L,R);
	if(L>mid)return query(p<<1|1,mid+1,r,L,R);
	return query(p<<1,l,mid,L,R)+query(p<<1|1,mid+1,r,L,R);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(last[a[i]])modify_size(1,1,n,last[a[i]],-1);
		if(last[a[i]])modify_val(1,1,n,pre_last[a[i]]+1,last[a[i]]-1,-1);
		ans+=query(1,1,n,last[a[i]]+1,i-1);
		modify_val(1,1,n,last[a[i]]+1,i-1,1);
		modify_size(1,1,n,i,1);
		pre_last[a[i]]=last[a[i]];
		last[a[i]]=i;
	}
	printf("%lld\n",ans);
	return 0;
}
/*
15
2 12 4 5 5 8 1 10 10 10 12 1 12 1 9

(2,4,9)
(2,8,9)
(4,8,9)
(5,8,9)
(12,1,9)

*/

```


---

## 作者：xishanmeigao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P7530)

设 $lst_i,nxt_i$ 分别表示上一个/下一个和 $i$ 相同的位置。

设 $f_{l,r}=\sum\limits_{j=l+1}^r[lst_j<l][nxt_j>r]$。扫右端点 $r$，贡献是 $\sum\limits_{l=lst_i+1}^{r-2}[nxt_l>r]f_{l,r-1}$。

扫描线，假设现在右端点是 $i$，操作流程如下：

定义 $j$「有用」表示 $nxt_j>i-1$（其实就是最后一个出现的 $a_j$）。

先查询 $[lst_i+1,i-2]$ **有用**的 $f$ 和，贡献到答案。

对 $[lst_i+1,i-1]$ 之间**有用**的 $f$ 全部加一。

对 $[lst_{lst_i}+1,lst_i-1]$ 之间**有用**的 $f$ 全部减一。

将 $lst_i$ 处的 $f$ 值置为无用，$i$ 处的 $f$ 值置为有用。

用线段树维护 $f$。维护 $s,cnt$ 分别表示有用的 $f$ 和、个数。时间复杂度 $\mathcal{O}(n\log n)$。 


```cpp
#include<bits/stdc++.h>
#define LL long long
#define db double
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=2e5+10;

int n,a[N];
int idx[N],lst[N];
LL ans;

#define lc(p) p<<1
#define rc(p) p<<1|1
struct SegmentTree
{
	LL s[N<<2],ad[N<<2]; int cnt[N<<2];

	void Add(int p,int v)
	{
		s[p]+=1LL*cnt[p]*v;
		ad[p]+=v;
	}

	void pushup(int p)
	{
		s[p]=s[lc(p)]+s[rc(p)];
		cnt[p]=cnt[lc(p)]+cnt[rc(p)];
	}

	void spread(int p)
	{
		if(ad[p])
		{
			Add(lc(p),ad[p]);
			Add(rc(p),ad[p]);
			ad[p]=0;
		}
	}

	void build(int p,int l,int r)
	{
		s[p]=ad[p]=cnt[p]=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(lc(p),l,mid); build(rc(p),mid+1,r); 
	}

	void modify(int p,int l,int r,int pos,int v)
	{
		if(!pos) return;
		if(l==r)
		{
			if(v>0) cnt[p]=1, s[p]=0;
			else cnt[p]=0, s[p]=0;
			return;
		}
		spread(p);
		int mid=(l+r)>>1;
		if(pos<=mid) modify(lc(p),l,mid,pos,v);
		else modify(rc(p),mid+1,r,pos,v);
		pushup(p);
	}

	void add(int p,int l,int r,int ql,int qr,int v)
	{
		if(ql>qr) return;
		if(ql<=l && qr>=r) return Add(p,v);
		spread(p);
		int mid=(l+r)>>1;
		if(ql<=mid) add(lc(p),l,mid,ql,qr,v);
		if(qr>mid) add(rc(p),mid+1,r,ql,qr,v);
		pushup(p);
	}

	LL ask(int p,int l,int r,int ql,int qr)
	{
		if(ql>qr) return 0;
		if(ql<=l && qr>=r) return s[p];
		spread(p);
		int mid=(l+r)>>1; LL res=0;
		if(ql<=mid) res+=ask(lc(p),l,mid,ql,qr);
		if(qr>mid) res+=ask(rc(p),mid+1,r,ql,qr);
		return res;
	}
}T;

int main()
{
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		lst[i]=idx[a[i]];
		idx[a[i]]=i;
	}

	T.build(1,1,n);

	for(int i=1; i<=n; i++)
	{
		ans+=T.ask(1,1,n,lst[i]+1,i-2);
		T.add(1,1,n,lst[i]+1,i-1,1);
		T.add(1,1,n,lst[lst[i]]+1,lst[i]-1,-1);
		T.modify(1,1,n,lst[i],-1);
		T.modify(1,1,n,i,1);
	}

	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：7KByte (赞：2)

题目大意：金组T1加强版，给定一个序列，求序列中三元组 $(i,j,k),i<j<k$ 的个数满足 $a_i,a_j,a_k$ 在区间 $[i,k]$ 中都恰好出现一次。

延续金组的思路，我们固定 $k$ ，则满足条件的 $i$ 一定在区间 $[pre_k+1,k-1]$ 内。

同时需要满足 $nxt_i>k$ 。

如果只有这两个条件，则是一个二维偏序问题。

我们还有 $j$ 的限制。要求 $a_j$ 在区间中只出现一次。

显然我们可以把 $i,j$ 捆绑到一起计算，然后只用对每个 $k$ 计算对应的 $i$ 的权值。

每个 $j$ 会对 $pre_j<i<j$ 的 $i$ 产生贡献，我们只用在二维偏序的基础上维护在线维护一个区间加即可。

看起来十分不可做？大力分块。。。

我们对每个块块内排序，整块直接打标记，块内查询直接二分。这样可以做到$\rm O(N\sqrt{N\log N})$ 的时间复杂度。空间复杂度是线性。

如果开桶，可以做到$\rm O(N\sqrt{N})$ 的时空复杂度。

一下是分块二分做法。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define pre(i,a,b) for(register int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,c[N],nxt[N],pre[N],u[N],bas,w[N],t[N],s[900][233];
struct node{
	int rl,ps,vl;
	node(int X=0,int Y=0){ps=X;rl=Y;vl=0;}
	bool operator<(const node o)const{return rl<o.rl;}
}a[900][233];
void change(int l,int r,int val){
	if(l>r)return;
	register int L=(l-1)/bas+1,R=(r-1)/bas+1;
	if(L==R){
		rep(i,1,w[L])a[L][i].vl+=t[L]+val*(l<=a[L][i].ps&&a[L][i].ps<=r);
		rep(i,1,w[L])s[L][i]=s[L][i-1]+a[L][i].vl;
		t[L]=0;
	}
	else{
		rep(i,1,w[L])a[L][i].vl+=t[L]+val*(l<=a[L][i].ps&&a[L][i].ps<=r);
		rep(i,1,w[L])s[L][i]=s[L][i-1]+a[L][i].vl;
		t[L]=0;
		rep(i,1,w[R])a[R][i].vl+=t[R]+val*(l<=a[R][i].ps&&a[R][i].ps<=r);
		rep(i,1,w[R])s[R][i]=s[R][i-1]+a[R][i].vl;
		t[R]=0;
		rep(i,L+1,R-1)t[i]+=val;
	}
}
int ask(int l,int r,int lim){
	if(l>r)return 0;
	register int L=(l-1)/bas+1,R=(r-1)/bas+1,sum=0,cur;
	if(L==R){
		rep(i,1,w[L])sum+=(t[L]+a[L][i].vl)*(l<=a[L][i].ps&&a[L][i].ps<=r&&a[L][i].rl>=lim);
		return sum;
	}
	else{
		rep(i,1,w[L])sum+=(t[L]+a[L][i].vl)*(l<=a[L][i].ps&&a[L][i].ps<=r&&a[L][i].rl>=lim);
		rep(i,1,w[R])sum+=(t[R]+a[R][i].vl)*(l<=a[R][i].ps&&a[R][i].ps<=r&&a[R][i].rl>=lim);
		rep(i,L+1,R-1){
			cur=lower_bound(a[i]+1,a[i]+w[i]+1,node(0,lim))-a[i]-1;
			sum+=s[i][w[i]]-s[i][cur]+(w[i]-cur)*t[i];
		}
		return sum;
	}
}
char buf[1<<22],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int main(){
	//freopen("INPUT","r",stdin);
	n=read();bas=230;
	rep(i,1,n)u[i]=read();
	rep(i,1,n){
		if(c[u[i]])pre[i]=c[u[i]],nxt[c[u[i]]]=i;
		c[u[i]]=i;	
	}
	register int cur;
	rep(i,1,n){
		cur=(i-1)/bas+1;
		if(nxt[i])a[cur][++w[cur]]=node(i,nxt[i]-1);
		else a[cur][++w[cur]]=node(i,n+1);
	}
	pre(i,(n-1)/bas+1,1)sort(a[i]+1,a[i]+w[i]+1);
	register long long ans=0;
	rep(i,1,n){
		ans+=ask(pre[i]+1,i-1,i);
		if(pre[i]!=0)change(pre[pre[i]]+1,pre[i]-1,-1);
		change(pre[i]+1,i-1,1);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：wangjiajian (赞：1)

设 $pre_i$ 表示第 $i$ 位牛的上一个相同品种的牛的位置

**考虑对于每一个确定的右领队 $r$：**

其左领队 $l$ 的的范围是 $[pre_i+1, i-2]$（因为左领队品种不能与右领队相同，且区间长度至少为 $3$）。

**考虑每一个新加入的位置 $i$：**

消极影响：
 - $pre_i$ 不能被选为左领队（因为左领队不能与成员品种相同）
 - 能将 $pre_i$ 作为中间领队的左领队（即区间 $[pre_{pre_i}+1, pre_i-1]$ 中的左领队）都不能将 $pre_i$ 作为中间领队了（因为中间领队不能与成员品种相同）

积极影响：
 - 其本身可以作为左领队
 - 其本身可以作为 $[pre_i+1, i-1]$ 中所有左领队的中间领队

**使用线段树维护：**

看到区间查询和区间的修改，考虑线段树。维护变量：
 - $num$ 表示该点/区间内左领队的个数
 - $mid$ 表示该点可选取的中间领队的个数
 - $sum$ 表示该点/区间的总可能数

**注意事项：**

 - 在更新区间的时候要特判防止区间越界到 $0$
 - 把位置 $i$ 加入时，要在统计 $i$ 作为右领队的答案之前把消极影响添加（因为 $i$ 作为右领队和作为中间领队的消极影响都是一样的）
 - 把位置 $i$ 加入时，在统计完 $i$ 作为右领队的答案之后才添加其作为中间领队的积极影响（因为一个牛不可能既是右领队又是中间领队）

**AC 代码**

```cpp
#include <bits/stdc++.h>
#define N (int)(2e5+3)
#define ll long long
using namespace std;

int n, b[N], pre[N], lst[N];
ll ans, num[N<<2], mid[N<<2], lzy[N<<2], sum[N<<2];

inline void pushup(int u) {
	num[u] = num[u<<1] + num[u<<1|1];
	sum[u] = sum[u<<1] + sum[u<<1|1]; 
}

inline void pushdown(int u) {
	if(lzy[u] == 0)
		return;
	lzy[u<<1] += lzy[u];
	mid[u<<1] += lzy[u];
	sum[u<<1] += lzy[u]*num[u<<1]; 
	lzy[u<<1|1] += lzy[u];
	mid[u<<1|1] += lzy[u];
	sum[u<<1|1] += lzy[u]*num[u<<1|1];
	lzy[u] = 0;
}

void update_num(int u, int l, int r, int pos, int x) {
	if(l == r) {
		num[u] = num[u] + x;
		sum[u] = sum[u] + x * mid[u];
		return;
	}
	pushdown(u);
	int m = (l+r)>>1;
	if(pos <= m)
		update_num(u<<1, l, m, pos, x);
	else
		update_num(u<<1|1, m+1, r, pos, x);
	pushup(u);
}

void update_mid(int u, int l, int r, int s, int t, int x) {
	if(s<=l && r<=t) {
		mid[u] = mid[u] + x;
		sum[u] = sum[u] + num[u] * x;
		lzy[u] = lzy[u] + x;
		return;
	}
	pushdown(u);
	int m = (l+r)>>1;
	if(s <= m)
		update_mid(u<<1, l, m, s, t, x);
	if(t >= m+1)
		update_mid(u<<1|1, m+1, r, s, t, x);
	pushup(u);
}

ll getsum(int u, int l, int r, int s, int t) {
	if(s<=l && r<=t)
		return sum[u];
	pushdown(u);
	ll ret = 0;
	int m = (l+r)>>1;
	if(s <= m)
		ret += getsum(u<<1, l, m, s, t);
	if(t >= m+1)
		ret += getsum(u<<1|1, m+1, r, s, t);
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", b+i);
		pre[i] = lst[b[i]];
		lst[b[i]] = i;
	}
	for(int i=1; i<=n; i++) {
		if(pre[i] > 0)
			update_num(1, 1, n, pre[i], -1);
		if(pre[i]-1 > 0)
			update_mid(1, 1, n, pre[pre[i]]+1, pre[i]-1, -1);
		if(i-2 > 0)
			ans += getsum(1, 1, n, pre[i]+1, i-2);
		update_num(1, 1, n, i, 1);
		if(i-1 > 0)
			update_mid(1, 1, n, pre[i]+1, i-1, 1);
	}
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：Anonymely (赞：0)

清新数据结构。

对于三个特殊点的区间问题，扫描线左端点，数据结构维护左端点答案。

首先对于每个数求出 $pre_i$ 表示上一个 $a_i$ 相等的位置，没有设为 $0$。

对于确定的右端点，左端点得在 $[pre_r+1,r-2]$ 取。

同时 $l$ 需要满足区间内没有与他相同的数，即 $r \to r + 1$ 时 $pre_r$ 就不能成为左端点，$r$ 可以成为。

第三个点也要满足数不同，$r \to r + 1$ 时给左端点在 $[pre_r+1,r-1]$ 中的数答案加 $1$。

也就是需要支持激活/关闭一个点，区间加，区间求和，线段树即可做到。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 2e5 + 5;
int n, a[N], pos[N], pre[N];

struct Tree {
	ll sum, len, tag;
} t[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void up(int p) {t[p].len = t[ls].len + t[rs].len, t[p].sum = t[ls].sum + t[rs].sum;}
void push(int p, ll w) {t[p].sum += w * t[p].len, t[p].tag += w;}
void down(int p) {if (t[p].tag) push(ls, t[p].tag), push(rs, t[p].tag), t[p].tag = 0;}
void ins(int p, int l, int r, int x, int o) {
	if (l == r) {
		// return t[p].len = o, void();
		if (!o) t[p].sum = 0, t[p].len = 0;
		else t[p].len = 1;
		return ;
	}
	down(p); int mid = (l + r) / 2;
	x <= mid ? ins(ls, l, mid, x, o) : ins(rs, mid + 1, r, x, o);
	up(p);
}
void add(int p, int l, int r, int L, int R, int x) {
	if (L > R) return ;
	if (L <= l && r <= R) return push(p, x);
	down(p); int mid = (l + r) / 2;
	if (L <= mid) add(ls, l, mid, L, R, x);
	if (mid < R) add(rs, mid + 1, r, L, R, x);
	up(p);
}
ll query(int p, int l, int r, int L, int R) {
	if (L > R) return 0;
	if (L <= l && r <= R) return t[p].sum;
	down(p); int mid = (l + r) / 2; ll sum = 0;
	if (L <= mid) sum += query(ls, l, mid, L, R);
	if (mid < R) sum += query(rs, mid + 1, r, L, R);
	return sum;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) pre[i] = pos[a[i]], pos[a[i]] = i;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ins(1, 1, n, i, 1);
		if (pre[i]) ins(1, 1, n, pre[i], 0);
		if (pre[i]) add(1, 1, n, pre[pre[i]] + 1, pre[i] - 1, -1);
		ans += query(1, 1, n, pre[i] + 1, i - 2);
		add(1, 1, n, pre[i] + 1, i - 1, 1);
		// cerr << ans << ' ';
	}
	cout << ans << '\n';
	QwQ01AwA;
}
```

---

## 作者：Egg_laying_master (赞：0)

## Description

给定一个长度为 $n$ 的数组 $a$，求其中数对 $(l,r,x)$ 的个数，满足 $1\leq l<x<r\leq n$ 且 $[l,r]$ 中 $a_l,a_r,a_x$ 均只出现了一次。

$1\leq n\leq 2\times 10^5$。

[link](https://www.luogu.com.cn/problem/P7530)

## Solution

考虑枚举 $r$，用线段树维护每个 $l$ 所对应的答案。

设 $L_i$ 表示上一个 $a_i$ 出现的位置 $+1$，$R_i$ 表示下一个 $a_i$ 出现的位置 $-1$。

容易发现 $L_x\leq l\leq x-1$ 且 $r\leq R	_l$。

用线段树维护对于每个 $l$，满足条件的 $x$ 的个数，显然这个东西跟 $r$ 无关，只要满足 $L_x\leq l\leq x-1$ 即可，所以每次只要在 $[L_x,x-1]$ 这个区间里加 $1$ 即可。

然而光求这个是不行的，因为还要满足 $L_r\leq l\leq r-2$ 和 $r\leq R_l$。前面那个很好求，只要求区间的和即可。

由于 $r$ 是从小到大枚举的，所以一个 $l$ 在当前不满足 $r\leq R_l$ 时，之后的每个 $r$ 都不会满足，所以可以把它删掉。于是用一个 vector 维护 $R_l=r$ 的所有 $l$ 即可，询问完删除。

然而线段树中是不支持删除操作的，所以可以维护一个带系数 $0/1$ 的线段树，初始时每个点的系数为 $1$，每次单点删除 $k$ 的操作就把 $k$ 对应的节点系数置为 $0$，然后删除 $k$ 作为 $x$ 对答案的贡献即可。

具体实现细节见代码。

时间复杂度：$O(n\log n)$。

## Code

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

// #define int int64_t

using i64 = int64_t;

const int kMaxN = 2e5 + 5;

int n;
int b[kMaxN], L[kMaxN], R[kMaxN], lst[kMaxN];
i64 sum[kMaxN << 2], val[kMaxN << 2], w[kMaxN << 2], tag[kMaxN << 2];
std::vector<int> v[kMaxN];

void pushup(int x) {
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  val[x] = val[x << 1] + val[x << 1 | 1];
  w[x] = w[x << 1] + w[x << 1 | 1];
}

void addtag(int x, int l, int r, int v) {
  tag[x] += v, val[x] += 1ll * w[x] * v, sum[x] += 1ll * (r - l + 1) * v;
}

void pushdown(int x, int l, int r) {
  if (!tag[x]) return;
  int mid = (l + r) >> 1;
  addtag(x << 1, l, mid, tag[x]), addtag(x << 1 | 1, mid + 1, r, tag[x]);
  tag[x] = 0;
}

void update1(int x, int l, int r, int ql, int qr, int v) {
  if (l > qr || r < ql) {
    return;
  } else if (l >= ql && r <= qr) {
    return addtag(x, l, r, v);
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  update1(x << 1, l, mid, ql, qr, v), update1(x << 1 | 1, mid + 1, r, ql, qr, v);
  pushup(x);
}

void update2(int x, int l, int r, int ql, int v) {
  if (l == r) {
    w[x] = v, val[x] = sum[x] * v;
    return;
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  if (ql <= mid) update2(x << 1, l, mid, ql, v);
  else update2(x << 1 | 1, mid + 1, r, ql, v);
  pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) {
    return 0;
  } else if (l >= ql && r <= qr) {
    return val[x];
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  return query(x << 1, l, mid, ql, qr) + query(x << 1 | 1, mid + 1, r, ql, qr);
}

void dickdreamer() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> b[i];
    L[i] = lst[b[i]] + 1;
    lst[b[i]] = i;
  }
  std::fill_n(lst + 1, n, n + 1);
  for (int i = n; i; --i) {
    R[i] = lst[b[i]] - 1;
    lst[b[i]] = i;
    v[R[i]].emplace_back(i);
  }
  for (int i = 1; i <= n; ++i)
    update2(1, 1, n, i, 1);
  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += query(1, 1, n, L[i], i - 2);
    update1(1, 1, n, L[i], i - 1, 1);
    for (auto x : v[i]) {
      update1(1, 1, n, L[x], x - 1, -1);
      update2(1, 1, n, x, 0);
    }
  }
  std::cout << ans << '\n';
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  // std::cin >> T;
  while (T--) dickdreamer();
  // std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
  return 0;
}
```

---

## 作者：moring (赞：0)

我们设区间内的三个点分别为 $i$ , $j$ , $k$ ，根据题意，我们可以列出如下不等式：
$$
\begin{aligned}
\left\{
\begin{array}{ll}
i<j<k  \\
r_i>k  \\
l_k<i  \\
r_j>k  \\
l_j<i  \\
\end{array}
\right.
\end{aligned}
$$
其中 $l_i$ 表示与 $i$ 同颜色的前驱， $r_i$ 表示后继。

我们枚举 $k$ ，联系上面的式子于是我们就可以得到 $l_k<i<j<k$ 。

再观察上面的式子，发现 $r_i>k$ 且 $r_j>k$ ，所以对于可行的 $i$ 和 $j$ ，都必须保证上述条件。

那么如何判断 $r_x$ 是否大于 $k$ 呢？我们从前往后枚举 $k$ ，设 $k'=l_k$ ，如果 $k'>0$ ，就说明 $r_{k'}=k$ ，所以对于 $x<k$ ， $r_{k'}>x$ 。

然后我们考虑如何求答案，我们把所有符合条件的位置都放进线段树里。因为这些位置既可以作为 $i$ ，也可以作为 $j$ ，所以我们要存两次：当位置作为 $i$ 时，我们将这个位置+1；当作为 $j$ 时，能放 $i$ 的位置就是 $[l_x+1,x-1]$ （跟 $k$ 是一样的），然后就把这段区间+1。当出现超出 $k$ 时，就删掉前驱的所有贡献。对于每个 $k$ ，答案就是线段树上 $i$ 的个数 $\times$ $j$ 的个数。

我的代码添加了一个 $ll$ 数组，表示前驱的前驱的位置，方便删除。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define ls now<<1
#define rs now<<1|1
using namespace std;
int n;
long long lazy[N*5];
int a[N],l[N],ll[N],id[N];
struct Node{
	long long v,num,ans;
}tree[N*5];
void update(int now,int l,int r)
{
	tree[now].ans=tree[l].ans+tree[r].ans;
	tree[now].num=tree[l].num+tree[r].num;
}
void pushdown(int now,int l,int r)
{
	if(lazy[now])
	{
		lazy[l]+=lazy[now],lazy[r]+=lazy[now];
		tree[l].v+=lazy[now],tree[r].v+=lazy[now];
		tree[l].ans+=lazy[now]*tree[l].num,tree[r].ans+=lazy[now]*tree[r].num;
		lazy[now]=0;
	}
}
void change1(int now,int l,int r,int x,int y)
{
	if(l==r)
	{
		tree[now].num+=y;
		tree[now].ans=tree[now].num*tree[now].v;
		return;
	}
	pushdown(now,ls,rs);
	int mid=(l+r)>>1;
	if(mid>=x)  change1(ls,l,mid,x,y);
	else  change1(rs,mid+1,r,x,y);
	update(now,ls,rs); 
}
void change2(int now,int l,int r,int x,int y,int z) 
{
	if(x>y)  return;
	if(l==x && r==y)
	{
		lazy[now]+=z;
		tree[now].v+=z;
		tree[now].ans+=z*tree[now].num;
		return;
	}
	pushdown(now,ls,rs);
	int mid=(l+r)>>1;
	if(mid>=y)  change2(ls,l,mid,x,y,z);
	else
	{
		if(mid<x)  change2(rs,mid+1,r,x,y,z);
		else  change2(ls,l,mid,x,mid,z),change2(rs,mid+1,r,mid+1,y,z);
	}
	update(now,ls,rs); 
}
long long query(int now,int l,int r,int x,int y)
{
	if(x>y)  return 0;
	if(l==x && r==y)
		return tree[now].ans;
	pushdown(now,ls,rs);
	int mid=(l+r)>>1;
	if(mid>=y)  return query(ls,l,mid,x,y);
	else
	{
		if(mid<x)  return query(rs,mid+1,r,x,y);
		else  return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		l[i]=id[a[i]];
		ll[i]=l[l[i]];
		if(l[i])
		{
			change1(1,1,n,l[i],-1);
			change2(1,1,n,ll[i]+1,l[i]-1,-1);	
		}	
		ans+=query(1,1,n,l[i]+1,i-1);
		change1(1,1,n,i,1);
		change2(1,1,n,l[i]+1,i-1,1);
		id[a[i]]=i;
	} 
	printf("%lld\n",ans);
}
```


---

## 作者：Nasaepa (赞：0)

学校 vp [USACO21OPEN] P 组一道题没切，赛后找同学对拍才过。

---

显然如果一个点在某个区间里没有出现过第二次，它就可以成为领队，因此可以预处理出每个点上一个同样的点出现的位置的后一位 $p$ 和下一个同样的点出现的位置的前一位 $f$ 。

首先讲个 $O(n^2)$ 思路，我想到了两种做法，一个是枚举左领队和中领队，一个是枚举左领队和右领队。第一个不好优化，第二个可以优化，因此这里讲第二种思路。

考虑枚举到左领队 $i$ 有且仅有 $[i+2,f_i]$ 内的点可以成为右领队。维护 $cnt$ 数组， $cnt_j$ 为 $j$ 为右领队时的方案数。显然中领队一定在左领队和右领队的中间，当 $j$ 变为中领队时，显然 $[j+1,f_j]$ 内的所所有右领队都可以选择 $j$ 作为中领队，因此方案数增加 $1$ 区间增加可以使用差分前缀和实现。代码：

```cpp
// 枚举左右节点
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define N 200010
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
int n,a[N];
int last[N],p[N],f[N];
int cnt[N];
ll ans;
// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;++i)cin >> a[i],p[i] = last[a[i]]+1,last[a[i]] = i;
    for(int i = 1;i <= n;++i)last[i] = n + 1;
    for(int i = n;i >= 1;--i)f[i] = last[a[i]]-1,last[a[i]] = i;
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= n;++j)cnt[j] = 0;
        for(int j = i + 1;j <= f[i];++j){
            cnt[j] += cnt[j-1];
            if(p[j] > i)continue;
            ans += cnt[j];
            ++cnt[j+1],--cnt[f[j]+1];
        }
    }
    cout << ans;
    return 0;
}
```

接下来是 $O(n \log n)$ 的正解思路，考虑用线段树进行优化。倒叙枚举左领队，考虑中领队 $i$ ， $[i+1,f_i]$ 的右领队都可以选择 $i$ 作为中领队， $[p_i,i-1]$ 的左领队都可以选择 $i$ 作为左领队，但是当右领队 $j$ 的 $p_j > i$ 时， $i$ 不再可以作为 $j$ 的中领队，此时应该将 $j$ 锁定，因为此时 $j$ 不再可以作为右领队了。维护 $c_i$ 为 $i$ 为右领队的方案数，对于 $i$ 左领队，此时 $f_i+1$ 不可再作为右领队，应该锁定，其方案数的贡献为 $\sum^{f_i}_{q = i+1}c_q$ 。此时 $i$ 变为中领队，会对 $[i+1,f_i]$ 内的点产生贡献，而对于 $p_j > i$ 的中领队 $j$ 应该清除贡献。这些可以用线段树实现。

```cpp
// 枚举左右节点
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define N 200010
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
int n,a[N];
int last[N],p[N],f[N];
int cnt[N];
ll ans;
int c[N];
inline bool cmp(const int &n1,const int &n2){return p[n1] < p[n2];}
namespace segment_tree{
    struct node{
        int lq,rq,lson,rson,cff;
        ll val = 0,lazy = 0;
    }pn[N<<2];int np =1, rt = 1;
    inline void push_down(const int &x){
        node &now = pn[x],&lson = pn[now.lson],&rson = pn[now.rson];
        lson.val += lson.cff * now.lazy;
        rson.val += rson.cff * now.lazy;
        lson.lazy += now.lazy,rson.lazy += now.lazy;
        now.lazy = 0;
    }
    void build(const int &x,const int &lq,const int &rq){
        node &now = pn[x];now.lq = lq,now.rq = rq,now.cff = (rq - lq + 1);
        if(lq == rq)return ;
        int mid = lq + (rq - lq >> 1);
        now.lson = ++np,build(now.lson,lq,mid);
        now.rson = ++np,build(now.rson,mid+1,rq);
    }
    void lock(const int &x,const int &pos){
        node &now = pn[x];
        if(pos > now.rq || pos < now.lq)return ;
        if(now.lq == now.rq){now.val = now.cff = 0;return ;}
        push_down(x);
        node &lson = pn[now.lson];
        if(lson.rq >= pos)lock(now.lson,pos);
        else lock(now.rson,pos);
        now.val = (pn[now.lson].val + pn[now.rson].val);
        now.cff = (pn[now.lson].cff + pn[now.rson].cff);
    }
    void update(const int &x,const int &lq,const int &rq,const ll &val){
        if(lq > rq)return ;
        node &now = pn[x];
        if(lq <= now.lq && now.rq <= rq){
            now.val += now.cff * val;
            now.lazy += val;
            return;
        }else if(now.lq > rq || now.rq < lq)return ;
        push_down(x);
        update(now.lson,lq,rq,val),update(now.rson,lq,rq,val);
        now.val = (pn[now.lson].val + pn[now.rson].val);
    }
    ll query(const int &x,const int &lq,const int &rq){
        if(lq > rq)return 0;
        node &now = pn[x];
        if(lq <= now.lq && now.rq <= rq){
            return now.val;
        }else if(now.lq > rq || now.rq < lq)return 0;
        push_down(x);
        return query(now.lson,lq,rq) + query(now.rson,lq,rq);
    }
}
using namespace segment_tree;
// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;++i)cin >> a[i],p[i] = last[a[i]]+1,last[a[i]] = i;
    for(int i = 1;i <= n;++i)last[i] = n + 1;
    for(int i = n;i >= 1;--i)f[i] = last[a[i]]-1,last[a[i]] = i,c[i] = i;
    sort(c+1,c+n+1,cmp);
    int pos = n;
    build(rt,1,n);
    for(int i = n;i >= 1;--i){
        while(pos >= 1 && p[c[pos]] > i)update(rt,c[pos]+1,f[c[pos]],-1),--pos;
        lock(rt,f[i]+1);
        ans += query(rt,i+1,f[i]);
        update(rt,i+1,f[i],1);
    }
    cout << ans;
    return 0;
}
```

---

