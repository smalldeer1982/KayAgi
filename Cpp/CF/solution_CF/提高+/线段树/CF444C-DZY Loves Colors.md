# DZY Loves Colors

## 题目描述

DZY loves colors, and he enjoys painting.

On a colorful day, DZY gets a colorful ribbon, which consists of $ n $ units (they are numbered from $ 1 $ to $ n $ from left to right). The color of the $ i $ -th unit of the ribbon is $ i $ at first. It is colorful enough, but we still consider that the colorfulness of each unit is $ 0 $ at first.

DZY loves painting, we know. He takes up a paintbrush with color $ x $ and uses it to draw a line on the ribbon. In such a case some contiguous units are painted. Imagine that the color of unit $ i $ currently is $ y $ . When it is painted by this paintbrush, the color of the unit becomes $ x $ , and the colorfulness of the unit increases by $ |x-y| $ .

DZY wants to perform $ m $ operations, each operation can be one of the following:

1. Paint all the units with numbers between $ l $ and $ r $ (both inclusive) with color $ x $ .
2. Ask the sum of colorfulness of the units between $ l $ and $ r $ (both inclusive).

Can you help DZY?

## 说明/提示

In the first sample, the color of each unit is initially $ [1,2,3] $ , and the colorfulness is $ [0,0,0] $ .

After the first operation, colors become $ [4,4,3] $ , colorfulness become $ [3,2,0] $ .

After the second operation, colors become $ [4,5,5] $ , colorfulness become $ [3,3,2] $ .

So the answer to the only operation of type $ 2 $ is $ 8 $ .

## 样例 #1

### 输入

```
3 3
1 1 2 4
1 2 3 5
2 1 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 4
1 1 3 4
2 1 1
2 2 2
2 3 3
```

### 输出

```
3
2
1
```

## 样例 #3

### 输入

```
10 6
1 1 5 3
1 2 7 9
1 10 10 11
1 3 8 12
1 1 10 3
2 1 10
```

### 输出

```
129
```

# 题解

## 作者：bsTiat (赞：12)

写一篇较为详细的标准分块题解。

题意翻译写的很详细清楚了，故在此不再重复。


### 算法实现：

首先，对于区间修改操作，零散块直接暴力重构，维护单点颜色情况和单点权值，并对于这一块的整块权值进行修改，保证整块权值是对的，重构之后把整块修改标记去掉。

对于整块的操作，我们分两种情况讨论：

一：整块是同一颜色，即有整块修改标记的块，我们可以直接计算这一整块修改后的权值，然后记录单点权值的修正量，之后更新整块修改标记。

二：整块不是同一颜色，我们把其看成零散块进行暴力重构，然后把整块修改标记更新。

然后，对于区间询问操作：

对于零散块：累加零散块中每个点的单点权值与整块的单点权值修正量之和。

对于整块：直接累加整块权值。

然后就结束了。

### 复杂度分析：

设 $ \sqrt{n} $ 为块长。

每次询问的复杂度显然是  $ O( \sqrt{n} ) $ 。

看上去好像整块修改的操作复杂度不太对？每一块的复杂度会达到 $ O( \sqrt{n} ) $ ，
那么区间修改最坏会达到  $ O(n) $ ？

其实我们修改完一整块之后，会打上标记，之后就是  $ O(1) $ 的了，而让标记被去除的块只有在区间修改零散块时才会产生，所以至多只有 $ O(m) $ 个，因此最终复杂度为 $ O(m\sqrt{n}) $ 。

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
# define int long long
const int N = 1e5+7;
inline int rd(){
	char c=getchar();int sum=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
int n,m,len;
int L[N],R[N],id[N],sum[N],col[N],tag[N],val[N],b[N];
//sum；整块权值和
//tag：整块颜色
//val：单点权值
//b:   整块权值修正  
void build(int l,int r,int x){		//暴力重构整块 
	int sid=id[l];
	if(tag[sid])
		for(int i=L[sid];i<=R[sid];++i)
			if(i>=l&&i<=r)
				sum[sid]+=abs(tag[sid]-x),
				val[i]+=abs(tag[sid]-x),col[i]=x;
			else col[i]=tag[sid];
	else
		for(int i=l;i<=r;++i)	
			sum[sid]+=abs(col[i]-x),
			val[i]+=abs(col[i]-x),col[i]=x;
	tag[sid]=0;return;
}
void change(int l,int r,int x){		
	int sid=id[l],eid=id[r];
	if(sid==eid){
		build(l,r,x);
		return;
	}
	build(l,R[sid],x);build(L[eid],r,x);
	for(int i=sid+1;i<eid;++i)
		if(tag[i])
			b[i]+=abs(tag[i]-x),
			sum[i]+=abs(tag[i]-x)*(R[i]-L[i]+1),tag[i]=x;
		else {
			build(L[i],R[i],x);
			tag[i]=x;
		}
	return;
}
int query(int l,int r){
	int sid=id[l],eid=id[r],ans=0;
	if(sid==eid){
		for(int i=l;i<=r;++i)
			ans+=val[i]+b[sid];
		return ans;
	}
	for(int i=l;i<=R[sid];++i)ans+=val[i]+b[sid];
	for(int i=L[eid];i<=r;++i)ans+=val[i]+b[eid];
	for(int i=sid+1;i<eid;++i)ans+=sum[i];
	return ans;
}
signed main(){
	int op,l,r,x;
	n=rd();m=rd();
	len=pow(n,0.5);
	for(int i=1;i<=n;++i){
		col[i]=i;
		id[i]=(i-1)/len+1;
	}
	for(int i=1;i<=id[n];++i)
		L[i]=(i-1)*len+1,R[i]=i*len;
	R[id[n]]=n;
	while(m--){
		op=rd();l=rd();r=rd();
		if(op==1){
			x=rd();
			change(l,r,x);
		}else{
			printf("%lld\n",query(l,r));
		}
	} 
	return 0;
}
```



---

## 作者：Dreamweaver (赞：10)

# Preface

颜色段均摊水题。

# Description

有一个长为 $n$ 的序列，每个元素有颜色 $c_i$ 和权值 $w_i$。$c_i$ 初始为 $i$，$w_i$ 初始为 $0$。

$m$ 次操作：

1. 区间染色为 $x$，同时区间中每个位置的权值增加新颜色与旧颜色差的绝对值。

1. 查询区间和。

$1\le n,m\le 10^5$，$1\le x\le 10^8$。
 
# Solution

## How？

看到有区间染色的操作，想到珂朵莉树、分块、势能线段树，这里我写了自己最熟悉的势能线段树。

线段树的每个节点维护区间是否为同色块（包括区间的颜色），区间权值和，区间染色的标记，区间加的标记。

对于 1 操作，如果线段树上某个节点的整个区间内颜色相同，则转化为了区间颜色修改及区间权值加，直接打标记即可；否则继续递归左右儿子，知道找到符合条件的区间。

对于 2 操作，直接查区间权值和即可。

## Why？

颜色段均摊的复杂度分析：

对于一个区间颜色连续段，每次线段树上递归修改的复杂度是 $O(\log n)$,每次区间染色操作，最多增加 $O(1)$ 个区间颜色连续段，所以单次 1 操作均摊复杂度是 $O(\log n)$。


# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define inf 0x3f3f3f3f
#define re register
#define maxn 200010
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define int long long
#define Orz cout<<"stO %王队% Orz"<<'\n';
int n,m;
struct node
{
	int l,r,col,sum,add,cc;
	bool tag;
	node()
	{
		l=r=col=sum=add=0;
		cc=-1;
		tag=false;
	}
	#define l(x) z[x].l
	#define r(x) z[x].r
	#define c(x) z[x].col
	#define a(x) z[x].add
	#define s(x) z[x].sum
	#define t(x) z[x].tag
	#define cc(x) z[x].cc
}z[maxn<<2];
void update(int root)
{
	if(l(root)==r(root)) return ;
	s(root)=s(ls(root))+s(rs(root));
	if(t(ls(root))&&t(rs(root))&&c(ls(root))==c(rs(root)))	t(root)=true,c(root)=c(ls(root));
	else	t(root)=false,c(root)=-1;
}
void f(int root,int x)
{
	s(root)+=(r(root)-l(root)+1)*x;
	a(root)+=x;
}
void ff(int root,int y)
{
	t(root)=true;
	c(root)=y;
	cc(root)=y;
} 
void pushdown(int root)
{
	f(ls(root),a(root));
	f(rs(root),a(root));
	a(root)=0;
	if(~cc(root))
	{
		ff(ls(root),cc(root));
		ff(rs(root),cc(root));
		cc(root)=-1;
	}	 
}
void build(int l,int r,int root)
{
	l(root)=l,r(root)=r;
	if(l==r)
	{
		t(root)=true;
		s(root)=0;
		cc(root)=-1;
		c(root)=l;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,ls(root));
	build(mid+1,r,rs(root));
	update(root);
}
void modify(int root,int l,int r,int x)
{
	if(l<=l(root)&&r>=r(root))
	{
		if(t(root))
		{
			f(root,abs(x-c(root)));
			ff(root,x);	
			return ;
		}
		pushdown(root);
		modify(ls(root),l,r,x);
		modify(rs(root),l,r,x);
		update(root);
		return ;
	}
	pushdown(root);
	int mid=l(root)+r(root)>>1;
	if(l<=mid)	modify(ls(root),l,r,x);
	if(r>mid)	modify(rs(root),l,r,x);
	update(root);
}
int query(int root,int l,int r)
{
	if(l<=l(root)&&r>=r(root))	return s(root);
	pushdown(root);
	int ans=0;
	int mid=l(root)+r(root)>>1;
	if(l<=mid)	ans+=query(ls(root),l,r);
	if(r>mid)	ans+=query(rs(root),l,r);
	update(root);
	return ans;
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
inline void wn(int x){if (x<0) {putchar('-');wn(-x);return;}if(x>=10)wn(x/10);putchar(x%10+'0');}
inline void wr(int x){wn(x);putchar('\n');}
signed main()
{
	cin>>n>>m;
	build(1,n,1);
	for(re int i=1;i<=m;++i)
	{
		int op=read(),l=read(),r=read();
		if(op==2)
			wr(query(1,l,r));
		else
		{
			int x=read();
			modify(1,l,r,x);
		} 
	}
	return 0;
}
```


---

## 作者：RedLycoris (赞：7)

这题线段树、珂朵莉树的题解都有了，我来个分块吧/cy

分块维护每一个块内的状况，如果遇到整块涂色则打上标记，可以将时间复杂度保持在$O(n\sqrt{n})$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
const int mxn=1e5+5;
ll n,m,sn,a[mxn],b[mxn],ta[444],sb[444],tb[444],ans,th,tl,tr;
int main(){
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,sn=sqrt(n);
	for(int i=0;i<n;++i)a[i]=i+1;   //初始状况
	for(;m--;){
		int tmp,l,r;cin>>tmp>>l>>r,--l,--r;
		if(tmp==1){
			int x;cin>>x;
			for(int i=l;i<=r;){   //分块处理
				th=i/sn,tl=th*sn,tr=min(tl+sn,n);
				if(i==tl and r>=tr-1){
					if(ta[th])tb[th]+=abs(ta[th]-x),sb[th]+=abs(ta[th]-x)*(tr-tl);    //可以整体覆盖
					else for(int i2=tl;i2<tr;++i2)b[i2]+=abs(a[i2]-x),sb[th]+=abs(a[i2]-x);  //一个一个来
					ta[th]=x,i=tr;
				}else{
					if(ta[th]){
						for(int i2=tl;i2<tr;++i2)a[i2]=ta[th];
						ta[th]=0;
					}
					b[i]+=abs(a[i]-x),sb[th]+=abs(a[i]-x),a[i]=x,++i;
				}
			}
		}else{
			ans=0;
			for(int i=l;i<=r;){  //分块求和
				tl=i/sn*sn,tr=min(tl+sn,n),th=i/sn;
				if(i==tl and r>=tr-1)ans+=sb[th],i=tr;
				else ans+=tb[th]+b[i],++i;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：CmsMartin (赞：4)

## 题目描述

[题目传送门](https://codeforces.com/problemset/problem/444/C)

## 分析

看到区间推平操作，可以写珂朵莉树。

使用珂朵莉树维护区间的颜色，使用树状数组维护区间和。

这道题的难点在于加上的数字是 $|y - x|$ ，所以我们要在推平操作里稍加改动。

不使用 `std::set` 的区间 `erase` 操作，而是和其他的操作一样暴力推平，对相同的颜色做区间加操作即可。

还是挺好写的，~~但是珂朵莉不知道为什么不理你了~~。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int C1[MAXN] , C2[MAXN] , N , M;

int LowBit(int x) {
	return x & -x;
}

void Add(int x , int d) {
	int k = x;
	while(x <= N) {
		C1[x] += d;
		C2[x] += d * k;
		x += LowBit(x);
	}
}

int GetSum(int x) {
	int res = 0;
	int d = x;
	while(x) {
		res += C1[x] * (d + 1) - C2[x];
		x -= LowBit(x);
	}
	return res;
}

struct Node {
	int l , r;
	mutable int Val;
	Node(const int &il , const int &ir , const int &iv) : l(il) , r(ir) , Val(iv) { }
	const bool operator < (const Node &o) const { 
        return l < o.l; 
    }
};

set<Node> ODT;

typedef set<Node>::iterator sit;

sit Split(int Pos) {
	sit it = ODT.lower_bound(Node(Pos , 0 , 0));
	if(it != ODT.end() && it -> l == Pos) return it;
	it--;
	int l = it -> l;
	int r = it -> r;
	int v = it -> Val;
	ODT.erase(it);
	ODT.insert(Node(l , Pos - 1 , v));
	return ODT.insert(Node(Pos , r , v)).first;
}

void Assign(int l , int r , int v) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    sit itll = itl; 
    while(itl != itr) {
    	Add(itl -> l, abs(itl -> Val - v));
        Add(itl -> r + 1, -abs(itl -> Val - v));
		itl = ODT.erase(itl);
	}
    ODT.insert(Node(l , r , v));
}


signed main() {
	scanf("%lld%lld" ,&N ,&M);
	for(int i = 1; i <= N; i++) ODT.insert(Node(i , i , i));
	while(M--) {
		int op , l , r , v;
		scanf("%lld%lld%lld" ,&op ,&l ,&r);
		if(op == 1) {
			scanf("%lld" ,&v);
			Assign(l , r , v);
		}
		else {
			printf("%lld\n" ,GetSum(r) - GetSum(l - 1));
		}
	}
	return 0;
}
```

---

## 作者：eee_hoho (赞：4)

我们用线段树维护这一段的答案和这段颜色是否一样，如果一样是什么颜色

每次我们修改时候对相同的颜色段修改，不相同的颜色段递归暴力修改

对于一次区间覆盖，只会产生两个新的端点，所以只会暴力$O(n+2m)$次

复杂度$O(mlogn)$

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 100000
#define zrt k << 1
#define yrt k << 1 | 1
using namespace std;
int n,m;
struct node
{
    int tag,c;
    long long su,at;
    node ()
    {
        at = su = c = tag = 0;
    }
};
int myabs(int x)
{
    if (x > 0)
        return x;
    return -x;
}
struct Seg
{
    node s[N * 4 + 5];
    node upd(node x,node y)
    {
        node k;
        if (x.c == y.c)
            k.c = x.c;
        k.su = x.su + y.su;
        return k;
    }
    void build(int k,int l,int r)
    {
        if (l == r)
        {
            s[k].c = l;
            s[k].su = 0LL;
            return;
        }
        int mid = l + r >> 1;
        build(zrt,l,mid);
        build(yrt,mid + 1,r);
        s[k] = upd(s[zrt],s[yrt]);
    }
    void pushdown(int k,int l,int r,int mid)
    {
        if (!s[k].tag && !s[k].at)
            return;
        if (s[k].tag)
        {
            s[zrt].c = s[k].tag;
            s[yrt].c = s[k].tag;
            s[zrt].tag = s[k].tag;
            s[yrt].tag = s[k].tag;
        }
        if (s[k].at)
        {
            s[zrt].su += (long long)(mid - l + 1) * s[k].at;
            s[yrt].su += (long long)(r - mid) * s[k].at;
            s[zrt].su += s[k].at;
            s[yrt].su += s[k].at;
        }
        s[k].tag = s[k].at = 0;
    }
    void change(int k,int l,int r,int x,int y,int z)
    {
        if (l >= x && r <= y && s[k].c)
        {
            s[k].su += (long long)myabs(z - s[k].c) * (long long)(r - l + 1);
            s[k].c = z;
            s[k].tag = z;
            s[k].at += (long long)myabs(z - s[k].c);
            return;
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x > mid)
            change(yrt,mid + 1,r,x,y,z);
        else
            if (y <= mid)
                change(zrt,l,mid,x,y,z);
            else
                change(zrt,l,mid,x,y,z),change(yrt,mid + 1,r,x,y,z);
        s[k] = upd(s[zrt],s[yrt]);
    }
    node query(int k,int l,int r,int x,int y)
    {
        if (l >= x && r <= y)
            return s[k];
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x > mid)
            return query(yrt,mid + 1,r,x,y);
        else
            if (y <= mid)
                return query(zrt,l,mid,x,y);
            else
                return upd(query(zrt,l,mid,x,y),query(yrt,mid + 1,r,x,y));
    }
}tree;
int main()
{
    scanf("%d%d",&n,&m);
    tree.build(1,1,n);
    int opt,l,r,z;
    for (int i = 1;i <= m;i++)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if (opt == 1)
        {
            scanf("%d",&z);
            tree.change(1,1,n,l,r,z);
        }
        else
            printf("%lld\n",tree.query(1,1,n,l,r).su);
    }
    return 0;
}
```

---

## 作者：hovny (赞：3)

## 思路：

这是一个**区间覆盖**的题，~~不经过思考~~就想到了$Old\ Driver\ Tree$，然后配合着**线段树**，就用数据结构过去了qaq

#### 时间复杂度分析

~~O(玄学)~~ 最坏的查询是$log$级的，显然不是影响时间复杂度关键，假设所有都是修改操作，修改绝大多数的时候都是使原本$n$个点变少的，最坏的情况应该是把同一个区间分裂成三个不同的区间，也就是每次把三个连在一起，再把一个区间分开三个，似乎复杂度也不会很高，最多三倍，加上$lower\_bound$的$log$和线段树的$log$，时间复杂度$O(能过)$，~~结束，cheer~~

Code：

```cpp
#include<bits/stdc++.h>
#define It set<node>::iterator 
#define N 100010
#define ll long long
using namespace std;
struct node{//用于ODT
	int l,r;
	mutable int val;
	node(int a,int b=-1,int c=0):l(a),r(b),val(c){	}
	node(){	}
	bool operator< (const node x) const{
		return l<x.l;
	}
};
int n,T,L,R,val,y;
ll f[N<<2],tag[N<<2],ans;//线段树，别忘了开ll
set<node>s;
It Itl,Itr,it;//迭代器
inline int read(){
	register int s=0;
	register char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
It Split(int pos)//分离
{
	it=s.lower_bound(node(pos));
	if(it!=s.end() && it->l ==pos) return it;
	--it;
	int l=it->l,r=it->r,val=it->val;
	s.erase(it);
	s.insert(node(l,pos-1,val));
	return s.insert(node(pos,r,val)).first;//返回的是pair类型，第一段关键字是插入位置的迭代器
}
void push(int k,int l,int r)
{
	f[k]+=tag[k]*(r-l+1);
	if(l!=r)
	{
		int cur=k<<1;
		tag[cur]+=tag[k];
		tag[cur|1]+=tag[k];
	}
	tag[k]=0;
}
void Modify(int k,int l,int r)
{
	if(tag[k]) push(k,l,r);
	if(r<L||R<l) return;
	if(L<=l&&r<=R)
	{
		tag[k]=y;
		push(k,l,r);
		return;
	}
	int mid=(l+r)>>1,cur=k<<1;
	Modify(cur,l,mid);
	Modify(cur|1,mid+1,r);
	f[k]=f[cur]+f[cur|1];
}
void Cov(int l,int r)
{
	Itr=Split(r+1);it=Itl=Split(l);
	for(;it!=Itr;++it)
	{
		L=it->l;R=it->r;y=abs(val- it->val);
		Modify(1,1,n);
	}
	s.erase(Itl,Itr);
	s.insert(node(l,r,val));//记得这里要重新插入过
}
void Query(int k,int l,int r)
{
	if(tag[k]) push(k,l,r);
	if(r<L||R<l) return;
	if(L<=l&&r<=R){ans+=f[k];return;}
	int mid=(l+r)>>1,cur=k<<1;
	Query(cur,l,mid);
	Query(cur|1,mid+1,r);
}
int main()
{
	int i;
	n=read();T=read();
	for(i=1;i<=n;i++)
		s.insert(node(i,i,i));
	while(T--)
	{
		if(read()==1)
		{
			L=read(),R=read(),val=read();
			Cov(L,R);
		}
		else
			ans=0,L=read(),R=read(),Query(1,1,n),printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：Buried_Dream (赞：2)

## Solution 

发现有区间推平，区间求和。

区间推平很容易想到珂朵莉树。

考虑用珂朵莉树来维护颜色，线段树来维护权值。

因为在每个珂朵莉树节点维护的区间里，加的权值与区间的颜色有关。

所以要对每个 set 中的节点去用线段树操作。

就是在珂朵莉树的覆盖操作中对于每个节点加完再清除节点。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.7.21
**/
#include<set>
#include<cmath>
#include<queue>
#include<cstdio>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar 
using namespace std;
typedef long long ll;
#define int long long
const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll inf = 0x3f3f3f3f3f3f3f3f;
inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline int ksm(int a, int b) {int base = a % mod, res = 1; while(b){if(b & 1) res = (res * base) % mod; base = (base * base) % mod, b >>= 1;}return res % mod;}
inline int mul(int a, int b) {int base = a % mod, res = 0; while(b){if(b & 1) res = (res + base) % mod; base = (base + base) % mod, b >>= 1;}return res % mod;}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

namespace Seg {
	#define lson rt << 1 
	#define rson rt << 1 | 1
	struct node {int l, r, sum, lazy; } tree[N << 1];
	void build(int rt, int l, int r) {
		tree[rt].l = l, tree[rt].r = r;
		if(l == r) return; int mid = (l + r) >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
	}
	void pushdown(int rt) {
		tree[lson].lazy += tree[rt].lazy, tree[rson].lazy += tree[rt].lazy;
		tree[lson].sum += tree[rt].lazy * (tree[lson].r - tree[lson].l + 1);
		tree[rson].sum += tree[rt].lazy * (tree[rson].r - tree[rson].l + 1);
		tree[rt].lazy = 0;
	}
	void change(int rt, int l, int r, int k) {
		if(tree[rt].l > r || tree[rt].r < l) return;
		if(tree[rt].l >= l && tree[rt].r <= r) {
			tree[rt].lazy += k, tree[rt].sum += k * (tree[rt].r - tree[rt].l + 1);
			return;
		} pushdown(rt), change(lson, l, r, k), change(rson, l, r, k);
		tree[rt].sum = tree[lson].sum + tree[rson].sum;
	}
	int Query(int rt, int l, int r) {
		if(tree[rt].l > r || tree[rt].r < l ) return 0;
		if(tree[rt].l >= l && tree[rt].r <= r) return tree[rt].sum;
		pushdown(rt); return Query(lson, l, r) + Query(rson, l, r); 
	}
}
using namespace Seg;

namespace Chollthy_Tree {
	#define It set<Node>::iterator
	struct Node {
		int l, r; mutable int v;
		Node(int L, int R = -1, int V = 0) : l(L), r(R), v(V) {}
		bool operator < (const Node &x) const {return l < x.l; }
	};
	set<Node> s;
	It Split(int pos) {
		It it = s.lower_bound(Node(pos));
		if(it != s.end() && it -> l == pos) return it;
		--it;
		int L = it -> l , R = it -> r, V = it -> v;
		s.erase(it);
		s.insert(Node(L, pos - 1, V));
		return s.insert(Node(pos, R, V)).first;
	}
	void Cover(int l, int r, int val) {
		It itr = Split(r + 1), itl = Split(l);
		for(; itl != itr; ) {
			change(1, itl -> l, itl -> r, abs(itl -> v - val));
			itl = s.erase(itl);
		}
		s.insert(Node (l, r, val));	
	}
}

using namespace Chollthy_Tree;

signed main() 
{
	int n = read(), Q = read();
	for(int i = 1; i <= n; i++) s.insert(Node (i, i, i));
	build(1, 1, n);
	for(int i = 1; i <= Q; i++) {
		int opt = read(), x = read(), y = read();
		if(opt & 1) {
			int val = read();
			Cover(x, y, val);
		}
		else printf("%lld\n", Query(1, x, y));
 	}
}
```

---

## 作者：Lily_White (赞：1)

一句话题解：珂朵莉树+线段树

（实际上这场的 Editorial 里面有珂朵莉树的思想`std::set`维护相同值区间了，来源要早于lxl正式提出）

注意到这个题目的要求里面有区间推平：

> Paint all the units with numbers between $l$ and $r$ (both inclusive) with color $x$.

这个操作用珂朵莉树是很容易维护的，但是这个题的询问问的是操作造成的影响值，需要单独维护。

影响值上面带了绝对值有点烦，但是对于珂朵莉树上的同值区间这是很好维护的——既然相同的值被改成了另外一个相同的值，那就直接在线段树上面加就好了。

如果操作破坏了已有的区间，就`split`来保证性质。

然后就是两个板子了。

```cpp

// Problem : C. DZY Loves Colors
// Contest : Codeforces Round #254 (Div. 1)
// URL : https://codeforces.com/contest/444/problem/C
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define y1 y114514
#define y2 y1919810
typedef pair <int, int> PII;
#define int long long
#define all(x) (x.begin(),  x.end())
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define range(i, s, t)  for (int i = s; i <= (int)t; i++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
long long qread() {
	char c = getchar();
	int neg = 1;
	long long val = 0;
	while (c != '-' && !isdigit(c)) c = getchar();
	if (c == '-') c = getchar(), neg = -1;
	while (isdigit(c)) val = (val << 3) + (val << 1) + c - '0', c = getchar();
	return neg * val;
}
const int N = 800010;
int n, m;
int ans;
//线段树开始
int lazy[N], sum[N];
inline void pushdown(int p, int l, int r) {
	sum[p] += lazy[p] * (r - l + 1);
	if (l != r) {
		lazy[p << 1] += lazy[p];
		lazy[p << 1 | 1] += lazy[p];
	}
	lazy[p] = 0;
}
inline void pushup(int p) {
	sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
void modify(int p, int l, int r, int ql, int qr, int v) {
	if (lazy[p]) pushdown(p, l, r);
	if (r < ql || qr < l) return;
	if (ql <= l && r <= qr) {
		lazy[p] = v;
		pushdown(p, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	modify(p << 1, l, mid, ql, qr, v);
	modify(p << 1 | 1, mid + 1, r, ql, qr, v);
	pushup(p);
}
void ask(int p, int l, int r, int ql, int qr) {
	if (lazy[p]) pushdown(p, l, r);
	if (r < ql || qr < l) return;
	if (ql <= l && r <= qr) {ans += sum[p]; return;}
	int mid = (l + r) >> 1;
	ask(p << 1, l, mid, ql, qr);
	ask(p << 1 | 1, mid + 1, r, ql, qr);
}
//珂朵莉树开始
struct node {
	int l, r;
	mutable int v;
	node(int l, int r = -1, int v = 0) : l(l), r(r), v(v) {}
	inline bool operator < (const node& b)const {return l < b.l;}
};
set <node> chtholly;
set <node> :: iterator split(int x) {
	//if (x > n) return chtholly.end();
	auto it = chtholly.lower_bound(node(x));
	if (it != chtholly.end() && it -> l == x) return it;
	--it;
	int l = it -> l, r = it -> r, v = it -> v;
	chtholly.erase(it);
	chtholly.insert(node(l, x - 1, v));
	return chtholly.insert(node(x, r, v)).first;
}
void assign(int l, int r, int v) {
	auto itr = split(r + 1), itl = split(l);
	auto it = itl;
	for (; it != itr; ++it) {
		int lV = it -> l, rV = it -> r, vV = abs(v - it -> v);
		modify(1, 1, n, lV, rV, vV);
	}
	chtholly.erase(itl, itr);
	chtholly.insert(node(l, r, v));
}

signed main() {
	n = qread(); m = qread(); repn(i, n) chtholly.insert(node(i, i, i));
	rep(i, m) {
		int op = qread();
		if (op == 1) {
			int l = qread(), r = qread(), v = qread();
			assign(l, r, v);
		}
		else {
			ans = 0;
			int l = qread(), r = qread();
			ask(1, 1, n, l, r);
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

