# [USACO13JAN] Seating G

## 题目描述

To earn some extra money, the cows have opened a restaurant in their barn specializing in milkshakes.  The restaurant has N seats (1 <= N <= 500,000) in a row. Initially, they are all empty.

Throughout the day, there are M different events that happen in sequence at the restaurant (1 <= M <= 300,000).  The two types of events that can happen are:

1. A party of size p arrives (1 <= p <= N). Bessie wants to seat the party in a contiguous block of p empty seats. If this is possible, she does so in the lowest position possible in the list of seats.  If it is impossible, the party is turned away.

2. A range [a,b] is given (1 <= a <= b <= N), and everybody in that range of seats leaves.

Please help Bessie count the total number of parties that are turned away over the course of the day.

有一排n个座位，m次操作。A操作：将a名客人安置到最左的连续a个空位中，没有则不操作。L操作：[a,b]的客人离开。

求A操作的失败次数。


## 说明/提示

There are 10 seats, and 4 events.  First, a party of 6 cows arrives.  Then all cows in seats 2..4 depart.  Next, a party of 5 arrives, followed by a party of 2.


Party #3 is turned away.  All other parties are seated.


## 样例 #1

### 输入

```
10 4 
A 6 
L 2 4 
A 5 
A 2 
```

### 输出

```
1 
```

# 题解

## 作者：Zvelig1205 (赞：10)

# P3071 [USACO13JAN]Seating G

## 前言 ~~闲话~~

哎，P2894 珂朵莉被卡了

推荐题目……

！有一个没做过

于是![](https://s1.ax1x.com/2022/07/24/jjDXKP.jpg)

[题目传送门](https://www.luogu.com.cn/problem/P3071)

## 思路

那当然珂朵莉了

对于“离开”操作，直接区间推平为 0。

而对于“安置”操作，直接暴力扫一遍珂树，找到足够大的空区间就将客人安置到那里，即区间推平为 1。

找空位的时候，可能出现两个相邻的区间都为 0 的情况（对珂树足够了解的人应该能看懂这句话），所以统计答案时不能只看当前区间，也要注意和之前的区间的关系：

* 当前区间为空：

	* 若前一个区间为空，则直接将区间长度累加到待选空区间长度 $sum$ 中；

	* 若前一个区间不空，则将当前区间的左端点记录为整个待选空区间的左端点 $L$。

* 当前区间不空：

	清空 $sum$ 和 $L$。

* 找到合适的空区间：

	返回空区间左端点。若遍历整个珂树都没有满足条件的 $sum$，返回 -1（即无解）

## 贴一下代码

```cpp
int n,m,l,r,ans;
struct C_Tree{
	int le,ri,val;
	C_Tree(int le,int ri=0,int val=0):
		le(le),ri(ri),val(val){}
	bool operator <(const C_Tree &b)const
	{
		return le<b.le;
	}
};
set<C_Tree>T;
#define IT set<C_Tree>::iterator
IT split(int now)
{
	IT i=T.lower_bound(C_Tree(now));
	if(i!=T.end()&&i->le==now)return i;
	i--;int l=i->le,r=i->ri,v=i->val;
	T.erase(i);
	T.insert(C_Tree(l,now-1,v));
	return T.insert(C_Tree(now,r,v)).first;
}
void assign(int l,int r,int k)
{
	IT ir=split(r+1),il=split(l);
	T.erase(il,ir);
	T.insert(C_Tree(l,r,k));
}
int ask(int siz)
{
	int sum=0,pos=0;
	for(IT i=T.begin();i!=T.end();i++)
	{
		if(i->val==0)
		{
			if(pos==0)pos=i->le;
			sum+=i->ri-i->le+1;
			if(sum>=siz)return pos;
		}
		else sum=pos=0;
	}
	return -1;
}
signed main()
{
	n=re();m=re();
	T.insert(C_Tree(1,n,0));
	for(int i=1;i<=m;i++)
	{
		char op[10]="";scanf("%s",op);
		if(op[0]=='A')
		{
			l=re(),r=ask(l);
			if(r!=-1)assign(r,r+l-1,1);
			else ans++;
		}
		else l=re(),r=re(),assign(l,r,0);
	}
	wr(ans);
	return 0;
}
```

## 一点小坑

$sum$ 是否满足的条件应该是 $\ge siz$ 而不是 $>siz$，不然就会取得 50 分的好成绩。

~~应该没人会和我一样犯这么傻的错误~~

## 后记

话说这题的标签……

为什么是 `队列`、`单调队列`、`离散化`？

## 广告

[珂朵莉树教程](https://www.cnblogs.com/adm-1223/p/15875088.html)

[我的 Blog](https://www.cnblogs.com/adm-1223/)


---

## 作者：localhost (赞：8)

为什么没有题解？似乎讨论版里的也是错的=_= ......

这样的话我就来写一篇吧lalal(｀・ω・´)

我有点怀疑标签，毕竟谁能想出这个怎么用（单调）队列写？？？

懵逼

[blog食用更佳](https://www.cnblogs.com/mimiorz/p/9294546.html)

其实我是用线段树写的。

每个节点（区间）记录三个变量:

sl[i]:从左往右有连续多少个空位

sr[i]:从右往左有连续多少个空位

s[i]:这个区间中最长连续多少个空位


```cpp
//ln指左孩子的区间包含多少座位
//rn指右孩子的区间包含多少座位
//rt指当前节点

向上更新：

inline void pu(int rt,int ln,int rn){
	s[rt]=max(max(s[ls],s[rs]),sr[ls]+sl[rs]);
	sl[rt]=sl[ls]+(sl[ls]==ln)*sl[rs];
	sr[rt]=sr[rs]+(sr[rs]==rn)*sr[ls];
}

向下更新：
//add指懒惰标记
inline void pd(int rt,int ln,int rn){
	if(!add[rt]||(!ln&&!rn))return;
	s[ls]=sl[ls]=sr[ls]=(add[rt]>0)*ln;
	s[rs]=sl[rs]=sr[rs]=(add[rt]>0)*rn;
	add[ls]=add[rs]=add[rt];add[rt]=0;
}
```

相信大家看代码应该是能看得懂的>_<

那么我就来给完整代码了：

```cpp
#include<bits/stdc++.h>
namespace ZDY{
#define ll long long
#define Fur(i,x,y) for(int i=x;i<=y;i++)
#define in2(x,y) in(x);in(y)
}using namespace ZDY;using namespace std;
#define N 5000011
#define ls rt<<1
#define rs ls|1
#define Z int m=(l+r)>>1
#define lson l,m,ls
#define rson m+1,r,rs
ll s[N<<2],sl[N<<2],sr[N<<2];
int n,q;
short add[N];
inline void pu(int rt,int ln,int rn){
	s[rt]=max(max(s[ls],s[rs]),sr[ls]+sl[rs]);
	sl[rt]=sl[ls]+(sl[ls]==ln)*sl[rs];
	sr[rt]=sr[rs]+(sr[rs]==rn)*sr[ls];
}
inline void pd(int rt,int ln,int rn){
	if(!add[rt]||(!ln&&!rn))return;
	s[ls]=sl[ls]=sr[ls]=(add[rt]>0)*ln;
	s[rs]=sl[rs]=sr[rs]=(add[rt]>0)*rn;
	add[ls]=add[rs]=add[rt];add[rt]=0;
}
inline void build(int l,int r,int rt){
	s[rt]=sl[rt]=sr[rt]=r-l+1;if(l==r)return;
	Z;build(lson);build(rson);
}
inline void upd(int L,int R,int l,int r,int rt,int v){
	if(L<=l&&r<=R){s[rt]=sl[rt]=sr[rt]=(v>0)*(r-l+1),add[rt]=v;return;}
	Z;pd(rt,m-l+1,r-m);
	if(L<=m)upd(L,R,lson,v);
	if(R>m)upd(L,R,rson,v);
	pu(rt,m-l+1,r-m);
}
inline int ask(int c,int l,int r,int rt){
	Z;pd(rt,m-l+1,r-m);
	if(s[ls]>=c)return ask(c,lson);
	else if(sr[ls]+sl[rs]>=c)return m-sr[ls]+1;
	else return ask(c,rson);
}
int main(){
	 scanf("%d%d",&n,&q);build(1,n,1);
	 int x,y,ans=0,pos;
	 while(q--)
	 	if(sc()=='A'){
		 	scanf("%d",&x);
			 if(s[1]<x)ans++;
			 else{
			 	pos=ask(x,1,n,1);
			 	upd(pos,pos+x-1,1,n,1,-1);
			 }
		}
	 	else{scanf("%d%d",&x,&y);upd(x,y,1,n,1,1);}
	cout<<ans<<endl;
}
```

好像这题和P2894 [USACO08FEB]酒店Hotel 重复了...

---

## 作者：jamesharden666 (赞：6)

## 题目大意
详见题目翻译。

## 解题思路

L操作也就是区间推平操作，意味着这题可以用珂朵莉树做。

当前块的值为 $0$，代表当前区间没有人坐。否则，当前区间有人坐。

A操作就暴力遍历整个集合，寻找一个长度大于 $l$ 的块，用 $r$，$sum$ 分别表示块的最左边和当前的块长。

如果 $sum\geq l$，就直接返回 $r$.

如果当前块的值为 $0$，$sum$ 加上当前块长，如果 $r=0$，就将当前块的左边赋值给 $r$.

如果当前块的值为 $1$，就将 $r$ 和 $sum$ 重置为 $0$.

L操作就是珂朵莉树基本操作--区间推平。


## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
char s[10+10];
struct node
{
    int l,r;
    mutable int v;
    node(int L,int R=-1,int V=0)
    {
        l=L,r=R,v=V;
    }
    bool operator <(const node &a) const
    {
        return l<a.l;
    }
};
set<node> a;
#define at set<node>::iterator
at split(int pos)
{
    at it=a.lower_bound(pos);
    if(it!=a.end()&&it->l==pos)
        return it;
    it--;
    int l=it->l;
    int r=it->r;
    int v=it->v;
    a.erase(it);
    a.insert(node(l,pos-1,v));
    return a.insert(node(pos,r,v)).first;
}
void emerge(int l,int r,int v)
{
    at itr=split(r+1);
    at itl=split(l);
    a.erase(itl,itr);
    a.insert(node(l,r,v));
    return ;
}
int ask(int l)
{
    int r=0,sum=0;
    for(at it=a.begin();it!=a.end();++it)
    {
        if(sum>=l)
            return r;
        if(it->v==0)
        {
            if(r==0)
                r=it->l;
            sum+=it->r-it->l+1;
        }
        else    
            r=0,sum=0;
    }
    return -1;
}
int main()
{
    scanf("%d %d",&n,&m);
    a.insert(node(1,n,0));
    a.insert(node(n+1,n+10,1));
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%s",s);
        if(s[0]=='A')
        {
            scanf("%d",&l);
            if(l==5)
                l=5; 
            int r=ask(l);  
            if(r!=-1)
                emerge(r,r+l-1,1);
            else    
                ans++;   
        }
        else
        {
            scanf("%d %d",&l,&r);
            emerge(l,r,0);
        }      
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：Creeper_l (赞：5)

题意：维护两个操作，区间推平，求连续 $0$ 的个数为 $x$ 的最前位置。

线段树。

因为需要求连续 $0$ 的个数，所以维护区间左边连续 $0$ 的最大个数，区间右边连续 $0$ 的最大个数以及区间连续 $0$ 的最大个数。

注意修改的时候要看是修改为 $1$ 还是修改为 $0$。

查询的时候如果整个区间连续 $0$ 的最大个数小于 $x$ 就操作失败。否则一直往区间连续 $0$ 的个数大于 $x$ 的位置跳，优先跳左区间，然后跳中间（左区间的右边和右区间的左边相接），最后跳右区间。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls id << 1
#define rs id << 1 | 1
const int MAXN = 5e5 + 10;
int n,m,x,y,ans;
char op;
struct SegmentTree{int id,l,r,lmx,rmx,sum,tag;}tree[MAXN << 2];
inline void Pushup(int id)
{
	tree[id].sum = max(max(tree[ls].sum,tree[rs].sum),tree[ls].rmx + tree[rs].lmx);
	if(tree[ls].sum == tree[ls].r - tree[ls].l + 1) tree[id].lmx = tree[ls].sum + tree[rs].lmx;
	else tree[id].lmx = tree[ls].lmx;
	if(tree[rs].sum == tree[rs].r - tree[rs].l + 1) tree[id].rmx = tree[rs].sum + tree[ls].rmx;
	else tree[id].rmx = tree[rs].rmx;
}
inline void Pushdown(int id)
{
	if(tree[id].tag == -1) return;
	if(tree[id].tag == 1)
	{
		tree[ls].lmx = tree[ls].rmx = tree[ls].sum = 0;
		tree[rs].lmx = tree[rs].rmx = tree[rs].sum = 0;
		tree[ls].tag = tree[rs].tag = tree[id].tag,tree[id].tag = -1;
	} else
	{
		tree[ls].lmx = tree[ls].rmx = tree[ls].sum = tree[ls].r - tree[ls].l + 1;
		tree[rs].lmx = tree[rs].rmx = tree[rs].sum = tree[rs].r - tree[rs].l + 1;
		tree[ls].tag = tree[rs].tag = tree[id].tag,tree[id].tag = -1;
	}
}
inline void Build(int id,int l,int r)
{
	tree[id].l = l,tree[id].r = r,tree[id].tag = -1;
	tree[id].lmx = tree[id].rmx = tree[id].sum = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	Build(ls,l,mid),Build(rs,mid + 1,r);
	Pushup(id);
}
inline void Update(int id,int l,int r,int a,int b,int c)
{
	if(a <= l && b >= r)
	{
		if(c == 1) tree[id].sum = tree[id].lmx = tree[id].rmx = 0;
		else tree[id].sum = tree[id].lmx = tree[id].rmx = r - l + 1;
		tree[id].tag = c;return;
	}
	Pushdown(id);
	int mid = (l + r) >> 1;
	if(a <= mid) Update(ls,l,mid,a,b,c);
	if(b > mid) Update(rs,mid + 1,r,a,b,c);
	Pushup(id);
}
inline int Query(int id,int l,int r,int a,int b,int c)
{
	Pushdown(id);
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(tree[ls].sum >= c) return Query(ls,l,mid,a,b,c);
	else if(tree[ls].rmx + tree[rs].lmx >= c) return mid - tree[ls].rmx + 1;
	else return Query(rs,mid + 1,r,a,b,c);
}
signed main()
{
	cin >> n >> m;
	Build(1,1,n);
	while(m--)
	{
		cin >> op;
		if(op == 'A')
		{
			cin >> x;
			if(tree[1].sum < x) ans++;
			else 
			{
				int pos = Query(1,1,n,1,n,x);
				Update(1,1,n,pos,pos + x - 1,1);
			}
		} 
		else cin >> x >> y,Update(1,1,n,x,y,0);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：D10s (赞：5)

WA个不停之后艰难地A掉了……

第一篇题解和讨论里的做法都是把A操作拆成了 find_pos 和 add 两个操作，而我选择
把他们合为 insert（详见代码），然后就在二三十分挣扎了半天……

问题在于，如果顾客要进入的区间跨在了 mid 的两端，那下一层子树处理的是两个对称的子问题（而非相同），因此要把 insert 写两个版本，分别处理向最左/右端插入的情况。

还有一件小事，insert分为两半时可以反过来写，如向左端插入时要先  insert (2*k+1) 再 insert(2*k)，避免数组被更新之后稀里糊涂的出错。
```cpp
#include<cstdio>
int s[2000005],flag[2000005],ll[2000005],rr[2000005];
inline int max(int x,int y) {return x>y?x:y;}
void update(int k,int l,int r) 
{
    s[k]=max(max(s[2*k],s[2*k+1]),rr[2*k]+ll[2*k+1]);
    int mid=(l+r)>>1;
    if(s[2*k]==mid-l+1) ll[k]=ll[2*k+1]+s[2*k];else ll[k]=ll[2*k];
    if(s[2*k+1]==r-mid) rr[k]=rr[2*k]+s[2*k+1];else rr[k]=rr[2*k+1];
}
void build(int k,int l,int r)
{
    if(l==r) {s[k]=ll[k]=rr[k]=1;return;}
    int mid=(l+r)>>1;
    build(2*k,l,mid);build(2*k+1,mid+1,r);
    update(k,l,r);
}
void pushdown(int k,int l,int r)
{
    if(!flag[k]) return;
    if(flag[k]>0)
    {
        s[2*k]=ll[2*k]=rr[2*k]=0;
        s[2*k+1]=rr[2*k+1]=ll[2*k+1]=0;
        flag[2*k]=flag[2*k+1]=1;
    }
    else 
    {
        int mid=(l+r)>>1;
        s[2*k]=ll[2*k]=rr[2*k]=mid-l+1;
        s[2*k+1]=ll[2*k+1]=rr[2*k+1]=r-mid;
        flag[2*k]=flag[2*k+1]=-1;
    }
    flag[k]=0;
}
void insert(int k,int l,int r,int len,int op)
{
    if(!len) return;
    if(r-l+1==len) {s[k]=ll[k]=rr[k]=0;flag[k]=1;return;}
    int mid=(l+r)>>1;pushdown(k,l,r);
    if(op)
    {
        if(s[2*k]>=len) insert(2*k,l,mid,len,1);
        else if(rr[2*k]+ll[2*k+1]>=len) {insert(2*k+1,mid+1,r,len-rr[2*k],1);insert(2*k,l,mid,rr[2*k],0);}
        else insert(2*k+1,mid+1,r,len,1);
    }
    else
    {
        if(s[2*k+1]>=len) insert(2*k+1,mid+1,r,len,0);
        else if(rr[2*k]+ll[2*k+1]>=len) {insert(2*k,l,mid,len-ll[2*k+1],0);insert(2*k+1,mid+1,r,ll[2*k+1],1);}
        else insert(2*k,l,mid,len,0);
    }
    update(k,l,r);
}
void del(int k,int l,int r,int L,int R)
{
    if(R<l||r<L) return;
    if(L<=l&&r<=R) {s[k]=ll[k]=rr[k]=r-l+1;flag[k]=-1;return;}
    int mid=(l+r)>>1;pushdown(k,l,r);
    del(2*k,l,mid,L,R);del(2*k+1,mid+1,r,L,R);
    update(k,l,r);
}
int main()
{
    int n,m,ans=0;scanf("%d%d",&n,&m);
    build(1,1,n);
    while(m--)
    {
        char c=' ';while(c<'A'||c>'Z') c=getchar();
        if(c=='A')
        {
            int x;scanf("%d",&x);
            if(s[1]<x) ans++;else insert(1,1,n,x,1);
        }
        else
        {
            int x,y;scanf("%d%d",&x,&y);
            del(1,1,n,x,y);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：4)

这题跟[[USACO08FEB]酒店Hotel](https://www.luogu.org/problemnew/show/P2894)真的好像啊，只是主函数改一改……

没事，这不影响我题水个双倍经验，题解也水个双倍经验【滑稽.jpg】

我来补充一下前两篇题解的，类似最大子段和的做法，利用$sum$要么在左区间，要么在右区间，要么横跨两个区间

为了方便查看，我把一个变量一行

这是一个结点的信息
```cpp
struct node{
	int sum;//区间最长连续空房的长度
	int lmax;//从l端点开始最长连续空房的长度
	int rmax;//从r端点开始最长连续空房的长度
	int lazy;//lazy为1表示退房，为2表示开房
	int len;//区间长度，记录后方便计算
	#define mid (l+r>>1)
	#define lson (rt<<1)
	#define rson (rt<<1|1)
	#define sum(rt) tree[rt].sum
	#define lmax(rt) tree[rt].lmax
	#define rmax(rt) tree[rt].rmax
	#define lazy(rt) tree[rt].lazy
	#define len(rt) tree[rt].len
}tree[maxn<<2];
```

开始建树
```cpp
void build(int l,int r,int rt){
	sum(rt)=lmax(rt)=rmax(rt)=len(rt)=r-l+1;
    //初始都是空房
	if(l == r) return ;
	build(l,mid,lson);
	build(mid+1,r,rson);
}
```
更新结点信息
```cpp
void pushup(int rt){
	lmax(rt)=(lmax(lson)==len(lson))?len(lson)+lmax(rson):lmax(lson);
    //若左儿子区间全空那么lmax可以横跨左右儿子，否则不能
	rmax(rt)=(rmax(rson)==len(rson))?len(rson)+rmax(lson):rmax(rson);
    //若右儿子区间全空那么rmax可以横跨左右儿子，否则不能
	sum(rt)=max(rmax(lson)+lmax(rson),max(sum(lson),sum(rson)));
    //有三种情况，sum全在左儿子，全在右儿子，横跨左右儿子
}
```
下传标记
```cpp
void pushdown(int rt){
	if(!lazy(rt)) return ;
	lazy(lson)=lazy(rson)=lazy(rt);
    //下传lazy标记
	sum(lson)=lmax(lson)=rmax(lson)=(lazy(rt)==1)?len(lson):0;
	sum(rson)=lmax(rson)=rmax(rson)=(lazy(rt)==1)?len(rson):0;
    //lazy为1表示退房，为2表示开房
	lazy(rt)=0;
    //清空lazy标记
}
```
进行退房或开房
```cpp
void update(int L,int R,int tag,int l,int r,int rt){
	if(L <= l && r <= R){
		sum(rt)=lmax(rt)=rmax(rt)=(tag==1)?len(rt):0;
		lazy(rt)=tag;
        //直接更新掉，打上lazy标记
		return ;
	}
	pushdown(rt);
	if(L <= mid) update(L,R,tag,l,mid,lson);
	if(R > mid) update(L,R,tag,mid+1,r,rson);
	pushup(rt);
    //记得下传并更新
}
```
在$[1,n]$找到一个$\geq x$的区间并返回左端点
```cpp
int query(int len,int l,int r,int rt){
	if(l == r) return l;
	pushdown(rt);
    //下传标记
	if(sum(lson)>=len) return query(len,l,mid,lson);
    //递归到左儿子
	if(rmax(lson)+lmax(rson)>=len) return mid-rmax(lson)+1;
    //左右儿子合并后满足就用中间
	return query(len,mid+1,r,rson);
    //递归到右儿子
}
```
完整代码$↓$

$Code\ Below:$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=500000+10;
int n,m,ans;

struct node{
    int sum,lmax,rmax,lazy,len;
    #define mid (l+r>>1)
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    #define sum(rt) tree[rt].sum
    #define lmax(rt) tree[rt].lmax
    #define rmax(rt) tree[rt].rmax
    #define lazy(rt) tree[rt].lazy
    #define len(rt) tree[rt].len
}tree[maxn<<2];

void pushup(int rt){
    lmax(rt)=(lmax(lson)==len(lson))?len(lson)+lmax(rson):lmax(lson);
    rmax(rt)=(rmax(rson)==len(rson))?len(rson)+rmax(lson):rmax(rson);
    sum(rt)=max(rmax(lson)+lmax(rson),max(sum(lson),sum(rson)));
}

void pushdown(int rt){
    if(!lazy(rt)) return ;
    lazy(lson)=lazy(rson)=lazy(rt);
    sum(lson)=lmax(lson)=rmax(lson)=(lazy(rt)==1)?len(lson):0;
    sum(rson)=lmax(rson)=rmax(rson)=(lazy(rt)==1)?len(rson):0;
    lazy(rt)=0;
}

void build(int l,int r,int rt){
    sum(rt)=lmax(rt)=rmax(rt)=len(rt)=r-l+1;
    if(l == r) return ;
    build(l,mid,lson);
    build(mid+1,r,rson);
}

void update(int L,int R,int tag,int l,int r,int rt){
    if(L <= l && r <= R){
        sum(rt)=lmax(rt)=rmax(rt)=(tag==1)?len(rt):0;
        lazy(rt)=tag;
        return ;
    }
    pushdown(rt);
    if(L <= mid) update(L,R,tag,l,mid,lson);
    if(R > mid) update(L,R,tag,mid+1,r,rson);
    pushup(rt);
}

int query(int len,int l,int r,int rt){
    if(l == r) return l;
    pushdown(rt);
    if(sum(lson)>=len) return query(len,l,mid,lson);
    if(rmax(lson)+lmax(rson)>=len) return mid-rmax(lson)+1;
    return query(len,mid+1,r,rson);
}

int main()
{
    scanf("%d%d",&n,&m);
    build(1,n,1);
    char opt;int l,r,x;
    while(m--){
        opt=getchar();
        while(opt!='A'&&opt!='L') opt=getchar();
        if(opt=='A'){
            scanf("%d",&x);
            if(sum(1)>=x){
                l=query(x,1,n,1);
                update(l,l+x-1,2,1,n,1);
            }
            else ans++;
        }
        else {
            scanf("%d%d",&l,&r);
            update(l,r,1,1,n,1);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Erotate (赞：1)

### Solution

在这题中我们需要做两件事：

1. 在这 $n$ 个座位中寻找连续 $a$ 个空座位，如果能找到，就把这 $a$ 个座位置为非空的。

2. 把区间 $[a,b]$ 的座位置为空座位。

把这 $n$ 个座位抽象成一个 01 串，空的座位为 1，非空的座位为 0，那么，我们可以用线段树来维护区间最长连续非零子串，并记录下它的左端点。如果有相同长度的，取左端点更靠左的那一个。

对于操作 1，我们可以查询区间 $[1,n]$ 的最长连续非零子串，然后判断一下其长度是否大于等于 $a$。设这个子串的左端点为 $l$，若长度大于等于 $a$，就把区间 $[l,l+a-1]$ 全部置为 0；否则，失败次数加 1。

对于操作 2，直接把区间 $[a,b]$ 置为 0 即可。

### code

```cpp
#include<bits/stdc++.h>
#define N 500005
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
struct tree{
	int l,r,v,len,ll,rl,add;
}tr[N<<2];
//v 是这段区间最长连续非零子串的长度
//len 是这段区间的长度
//ll 是从区间的左端点开始，最长连续非零子串的长度
//rl 是从区间的右端点开始，最长连续非零子串的长度
//add 是懒标记
int n,m;
void push_up(int k){//以下的线段树是维护区间最长连续非零子串的版本，读者可以自行理解一下。
	if(tr[ls].ll==tr[ls].len) tr[k].ll=tr[ls].len+tr[rs].ll;
	else tr[k].ll=tr[ls].ll;
	if(tr[rs].rl==tr[rs].len) tr[k].rl=tr[ls].rl+tr[rs].len;
	else tr[k].rl=tr[rs].rl;
	tr[k].v=max(max(tr[rs].v,tr[ls].v),tr[rs].ll+tr[ls].rl);
}
void push_down(int k){
	if(!tr[k].add) return;
	tr[ls].add=tr[rs].add=tr[k].add;
	if(tr[k].add==1){
		tr[ls].v=tr[ls].ll=tr[ls].rl=tr[ls].len;
		tr[rs].v=tr[rs].ll=tr[rs].rl=tr[rs].len;
	}else{
		tr[ls].v=tr[ls].ll=tr[ls].rl=0;
		tr[rs].v=tr[rs].ll=tr[rs].rl=0;
	}
	tr[k].add=0;
}
void build(int k,int l,int r){
	tr[k].l=l,tr[k].r=r;
	tr[k].v=tr[k].len=tr[k].ll=tr[k].rl=r-l+1;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void update(int k,int l,int r,int tg){
	if(tr[k].l>=l && tr[k].r<=r){
		if(tg==1) tr[k].v=tr[k].ll=tr[k].rl=tr[k].len;
		else tr[k].v=tr[k].ll=tr[k].rl=0;
		tr[k].add=tg;
		return;
	}
	push_down(k);
	int mid=tr[k].l+tr[k].r>>1;
	if(l<=mid) update(ls,l,r,tg);
	if(r>mid) update(rs,l,r,tg);
	push_up(k);
}
int query(int k,int l,int r,int ln){
	if(l==r) return l;
	push_down(k);
	int mid=tr[k].l+tr[k].r>>1;
	if(tr[ls].v>=ln) return query(ls,l,mid,ln);
	else if(tr[ls].rl+tr[rs].ll>=ln) return mid-tr[ls].rl+1;
	return query(rs,mid+1,r,ln);
}
signed main(){
    int ans=0;
	scanf("%lld%lld",&n,&m);
	build(1,1,n);
	for(int i=1,st,sum;i<=m;++i){
		char ch[10];
		cin>>ch+1;
		if(ch[1]=='A'){
			scanf("%lld",&sum);
			if(tr[1].v>=sum){
				st=query(1,1,n,sum);
				update(1,st,st+sum-1,2);
			}else ans++;
		}else{
			scanf("%lld%lld",&st,&sum);
			update(1,st,sum,1);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15859766.html)

# 题目大意

有 $n$ 个座位，$m$ 次操作。

$\rm A$ 操作：将 $a$ 名客人安置到最左的连续 $a$ 个空位中，没有则不操作。

$\rm L$ 操作：$[a,b]$ 的客人离开。

求 $\rm A$ 操作中所有不操作的次数。

# 题目分析

和 $\verb!P2894!$ 很像。注意这道题 $\rm L$ 操作是针对区间 $[l,r]$，$\verb!P2894!$ 是针对区间 $[l,l+x-1]$。这里坑了我两天。

定义 $lmax$ 表示从左开始的最大连续空位数，从右开始的连续最大空位数，以及该区间的最大连续空位数 $max$。

之所以定义 $lmax,rmax$，是因为我们从该区间扩展的时候不能只靠 $max$，也就是说该区间的 $max$ 不等于左儿子和右儿子的 $max$ 之和。举个例子：

区间 $[1,8]$（$0$ 表示空位，$1$ 表示非空位）：`0 0 0 1 0 0 0 1`。$max[1,8]\neq max[1,4]+max[5,8]$。但是用 $lmax,rmax$ 就可以解决了：

```cpp
inline void pushup(int p)
{
	node[p].Max=max(node[ls(p)].Max,max(node[rs(p)].Max,node[ls(p)].rmax+node[rs(p)].lmax));

	node[p].lmax=node[ls(p)].Max==(node[ls(p)].r-node[ls(p)].l+1)?node[ls(p)].Max+node[rs(p)].lmax:node[ls(p)].lmax;

	node[p].rmax=node[rs(p)].Max==(node[rs(p)].r-node[rs(p)].l+1)?node[rs(p)].Max+node[ls(p)].rmax:node[rs(p)].rmax;
}
```

对于修改操作，我们仍然使用懒标记。$tag=1$ 表示非空位，$tag=0$ 表示空位。

于是可以这样：

```cpp
inline void pushdown(int p)
{
	if(node[p].tag==0)
	{
		node[ls(p)].tag=node[rs(p)].tag=0;

		node[ls(p)].Max=node[ls(p)].lmax=node[ls(p)].rmax=node[ls(p)].r-node[ls(p)].l+1;

		node[rs(p)].Max=node[rs(p)].lmax=node[rs(p)].rmax=node[rs(p)].r-node[rs(p)].l+1;
	}

	else if(node[p].tag==1)
	{
		node[ls(p)].tag=node[rs(p)].tag=1;

		node[ls(p)].Max=node[ls(p)].lmax=node[ls(p)].rmax=0;

		node[rs(p)].Max=node[rs(p)].lmax=node[rs(p)].rmax=0;
	}

	node[p].tag=-1;
}
```

修改操作没啥好讲的，重点讲讲查询操作。

我们查询操作是为了返回左端点值，如果左儿子装得下 $x$ 个座位，那么递归到左儿子去；如果跨越左右儿子的空位数装得下 $x$ 个座位，那么返回左端点位置；否则递归到右儿子去。

```cpp
inline int query(int p,int k)
{
	if(node[p].l==node[p].r)
	{
		return node[p].l;
	}

	Segment_Tree::pushdown(p);

	int mid=node[p].l+node[p].r>>1;

	if(node[ls(p)].Max>=k)
	{
		return Segment_Tree::query(ls(p),k);
	}

	if(node[ls(p)].rmax+node[rs(p)].lmax>=k)
	{
		return node[ls(p)].r-node[ls(p)].rmax+1;
	}

	else
	{
		return Segment_Tree::query(rs(p),k);
	}
}
```

# 代码

完整代码：

```cpp
//2022/1/31

//2022/2/1

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#include <algorithm>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=5e5+5;

struct Node
{
	int l,r;

	int lmax,rmax;//from left,from right

	int tag,Max;

	//if tag = 0: get out
	//if tag = 1: come in
};

Node node[ma<<2];

int n,m;

namespace Segment_Tree
{
	#define ls(p) (p<<1)

	#define rs(p) (p<<1|1)

	inline void pushup(int p)
	{
		node[p].Max=max(node[ls(p)].Max,max(node[rs(p)].Max,node[ls(p)].rmax+node[rs(p)].lmax));

		node[p].lmax=node[ls(p)].Max==(node[ls(p)].r-node[ls(p)].l+1)?node[ls(p)].Max+node[rs(p)].lmax:node[ls(p)].lmax;

		node[p].rmax=node[rs(p)].Max==(node[rs(p)].r-node[rs(p)].l+1)?node[rs(p)].Max+node[ls(p)].rmax:node[rs(p)].rmax;
	}

	inline void build(int p,int l,int r)
	{
		node[p].l=l,node[p].r=r;

		if(node[p].l==node[p].r)
		{
			node[p].lmax=node[p].rmax=node[p].Max=1;

			return;
		}

		int mid=node[p].l+node[p].r>>1;

		Segment_Tree::build(ls(p),l,mid);

		Segment_Tree::build(rs(p),mid+1,r);

		Segment_Tree::pushup(p);
	}

	inline void pushdown(int p)
	{
		if(node[p].tag==0)
		{
			node[ls(p)].tag=node[rs(p)].tag=0;

			node[ls(p)].Max=node[ls(p)].lmax=node[ls(p)].rmax=node[ls(p)].r-node[ls(p)].l+1;

			node[rs(p)].Max=node[rs(p)].lmax=node[rs(p)].rmax=node[rs(p)].r-node[rs(p)].l+1;
		}

		else if(node[p].tag==1)
		{
			node[ls(p)].tag=node[rs(p)].tag=1;

			node[ls(p)].Max=node[ls(p)].lmax=node[ls(p)].rmax=0;

			node[rs(p)].Max=node[rs(p)].lmax=node[rs(p)].rmax=0;
		}

		node[p].tag=-1;
	}

	inline void update(int x,int y,int p,int k)
	{
		if(x<=node[p].l && node[p].r<=y)
		{
			if(k==0)
			{
				node[p].Max=node[p].lmax=node[p].rmax=node[p].r-node[p].l+1;
			}

			else
			{
				node[p].Max=node[p].lmax=node[p].rmax=0;
			}

			node[p].tag=k;

			return;
		}

		Segment_Tree::pushdown(p);

		int mid=node[p].l+node[p].r>>1;

		if(x<=mid)
		{
			Segment_Tree::update(x,y,ls(p),k);
		}

		if(y>mid)
		{
			Segment_Tree::update(x,y,rs(p),k);
		}

		Segment_Tree::pushup(p);
	}

	inline int query(int p,int k)
	{
		if(node[p].l==node[p].r)
		{
			return node[p].l;
		}

		Segment_Tree::pushdown(p);

		int mid=node[p].l+node[p].r>>1;

		if(node[ls(p)].Max>=k)
		{
			return Segment_Tree::query(ls(p),k);
		}

		if(node[ls(p)].rmax+node[rs(p)].lmax>=k)
		{
			return node[ls(p)].r-node[ls(p)].rmax+1;
		}

		else
		{
			return Segment_Tree::query(rs(p),k);
		}
	}

	#undef ls

	#undef rs
}

int main(void)
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif

	n=read(),m=read();

	Segment_Tree::build(1,1,n);

	int ans=0;

	for(register int i=1;i<=m;i++)
	{
		char ch[3];

		scanf("%s",ch);

		int x=read();

		if(ch[0]=='A')
		{
			if(node[1].Max>=x)
			{
				int l=Segment_Tree::query(1,x);

				Segment_Tree::update(l,l+x-1,1,1);
			}

			else
			{
				ans++;
			}
		}

		else	
		{
			int y=read();

			Segment_Tree::update(x,y,1,0);
		}
	}

	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：Link_Space (赞：1)

线段树维护连续0的区间即可。

双倍经验题：[P2894 酒店](https://www.luogu.com.cn/problem/P2894)需要稍微改一点，处理是一模一样的。

题目意思就是给你一个区间，最初时都为0，有两种操作，第一种操作是将最左边的连续a个0变为1，第二种操作是将区间 $[a,b]$ 变为0，那么对于每一个区间，我们只需要用线段树维护三个变量:左端连续0的个数，右端连续0的个数和整个区间内连续0的个数的最大值即可。

对于1操作，在查询时寻找最左边连续a个0的左端点的位置就可以了。

以下是代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 3e6 + 5;
struct Node{
	int lef;
	int rig;
	int maxn;
	int lmax;
	int rmax;
	int aim;
} Tree[N];
void pushup(int now)
{
	Tree[now].maxn = max(max(Tree[now << 1].maxn, Tree[now << 1 | 1].maxn), Tree[now << 1].rmax + Tree[now << 1 | 1].lmax);
	Tree[now].lmax = Tree[now << 1].lmax;
	if(Tree[now<<1].lmax==Tree[now<<1].rig-Tree[now<<1].lef+1)
		Tree[now].lmax += Tree[now << 1 | 1].lmax;
	Tree[now].rmax = Tree[now << 1 | 1].rmax;
	if(Tree[now<<1|1].rmax==Tree[now<<1|1].rig-Tree[now<<1|1].lef+1)
		Tree[now].rmax += Tree[now << 1].rmax;
}
void build(int now,int l,int r)
{
	Tree[now].lef = l;
	Tree[now].rig = r;
	Tree[now].aim = -1;
	if(l==r)
	{
		Tree[now].maxn = Tree[now].lmax = Tree[now].rmax = 1;
		return;
	}
	int mid = l + r >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	pushup(now);
}
void pushdown(int now)
{
	if(Tree[now].aim!=-1)
	{
		if(Tree[now].aim==0)
		{
			Tree[now << 1].maxn = Tree[now << 1].lmax = Tree[now << 1].rmax = Tree[now << 1].rig - Tree[now << 1].lef + 1;
			Tree[now << 1 | 1].maxn = Tree[now << 1 | 1].lmax = Tree[now << 1 | 1].rmax = Tree[now << 1 | 1].rig - Tree[now << 1 | 1].lef + 1;
		}
		else 
		{
			Tree[now << 1].maxn = Tree[now << 1].lmax = Tree[now << 1].rmax = 0;
			Tree[now << 1 | 1].maxn = Tree[now << 1 | 1].lmax = Tree[now << 1 | 1].rmax = 0;
		}
		Tree[now << 1].aim = Tree[now << 1 | 1].aim = Tree[now].aim;
		Tree[now].aim = -1;
	}
}
void modify(int now,int l,int r,int x)
{
	if(l<=Tree[now].lef&&Tree[now].rig<=r)
	{
		Tree[now].aim = x;
		if(x==1)
			Tree[now].maxn = Tree[now].lmax = Tree[now].rmax = 0;
		else
			Tree[now].maxn = Tree[now].lmax = Tree[now].rmax = Tree[now].rig - Tree[now].lef + 1;
		return;
	}
	pushdown(now);
	int mid = Tree[now].lef + Tree[now].rig >> 1;
	if(l<=mid)
		modify(now << 1, l, r, x);
	if(r>mid)
		modify(now << 1 | 1, l, r, x);
	pushup(now);
}
int query(int now,int x)
{
	pushdown(now);
	if(Tree[now].maxn<x)
		return Tree[now].rig - Tree[now].rmax + 1;
	if(Tree[now<<1].maxn>=x)
		return query(now << 1, x);
	else if(Tree[now<<1].rmax+Tree[now<<1|1].lmax>=x)
		return query(now << 1, x);
	else if(Tree[now<<1|1].maxn>=x)
		return query(now << 1 | 1, x);
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
    int cnt = 0;
    for (int i = 1; i <= m;i++)
	{
		char op[2];
		scanf("%s", op);
		if(*op=='A')
		{
			int x;
			scanf("%d", &x);
			if(Tree[1].maxn>=x)
			{
				int left = query(1, x);
				modify(1, left, left + x - 1, 1);
			}
			else
                cnt++;
        }
		else 
		{
			int left;
			int len;
			scanf("%d%d", &left, &len);
			modify(1, left, len, 0);
		}
	}
    printf("%d\n", cnt);
}
```


---

## 作者：moosssi (赞：1)

线段树水题。

维护区间最长连续和即可，简单说下区间如何由两个子区间转移，考虑三种情况：

左儿子左端最长，右儿子右段最长，或者左儿子右段加右儿子左端，具体见代码。

查找的时候，类似于二分思想。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
struct nod{
	int lmax,rmax,len,sum,lazy;
}tree[N*4];
int n,m,ans;
void spread(int p){//向下传标记 
	if(tree[p].lazy==0)return ;
	else if(tree[p].lazy==1){
		tree[p].lazy=0;
		tree[p*2].lazy=tree[p*2+1].lazy=1;
		tree[p*2].sum=tree[p*2].lmax=tree[p*2].rmax=0;
		tree[p*2+1].sum=tree[p*2+1].lmax=tree[p*2+1].rmax=0;
	}
	else {
		tree[p].lazy=0;
		tree[p*2].lazy=tree[p*2+1].lazy=2;
		tree[p*2].sum=tree[p*2].lmax=tree[p*2].rmax=tree[p*2].len;
		tree[p*2+1].sum=tree[p*2+1].lmax=tree[p*2+1].rmax=tree[p*2+1].len;
	}
}
void build(int l,int r,int p){
	tree[p].lazy=0;
	tree[p].sum=tree[p].len=tree[p].lmax=tree[p].rmax=r-l+1;
	if(l==r)return ;
	int mid=(l+r)/2;
	build(l,mid,p*2);
	build(mid+1,r,p*2+1);
}
void rew(int p){//向上合并 
	if(tree[p*2].sum==tree[p*2].len){
		tree[p].lmax=tree[p*2].sum+tree[p*2+1].lmax;
	}
	else tree[p].lmax=tree[p*2].lmax;
	if(tree[p*2+1].sum==tree[p*2+1].len){
		tree[p].rmax=tree[p*2+1].sum+tree[p*2].rmax;
	}
	else tree[p].rmax=tree[p*2+1].rmax;
	tree[p].sum=max(tree[p*2].sum,max(tree[p*2+1].sum,tree[p*2].rmax+tree[p*2+1].lmax));	
}
void chang(int p,int l,int r,int flag,int L,int R){//加人，减人两种修改 
	spread(p);
	if(l>=L&&r<=R){
		if(flag==1)
			tree[p].lmax=tree[p].rmax=tree[p].sum=0; 
		else 
			tree[p].lmax=tree[p].rmax=tree[p].sum=tree[p].len;
		tree[p].lazy=flag;
		return ;
	}
	int mid=(l+r)/2;
	if(L<=mid)chang(p*2,l,mid,flag,L,R);
	if(R>mid)chang(p*2+1,mid+1,r,flag,L,R);
	rew(p);
}
int find(int p,int l,int r,int lenth){//在线段树上二分查找 
	spread(p);
	if(l==r)return l;
	int mid=(l+r)/2;
	if(tree[p*2].sum>=lenth)return find(p*2,l,mid,lenth);//找左边 
	else if(tree[p*2].rmax+tree[p*2+1].lmax>=lenth)return mid-tree[p*2].rmax+1;//在中间 
	else return find(p*2+1,mid+1,r,lenth);//找右边 
}
int main(){
	scanf("%d%d",&n,&m);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		char op;
		int a,b;
		cin>>op;
		if(op=='A'){
			scanf("%d",&a);
			if(tree[1].sum>=a){
				int left=find(1,1,n,a);//找最左端符合的 
				chang(1,1,n,1,left,left+a-1);//不要忘记修改 
			}
			else ans++;//无法操作，累计答案 
		}
		else {
			scanf("%d%d",&a,&b);
			chang(1,1,n,2,a,b);
		}
	}
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：Setsugesuka (赞：1)

为什么一道ODT的裸题要用线段树做，难度还被恶评到了省选呢？

与P2894一样，我们用ODT维护各个操作，由于值域很小，每次操作有很大几率会把一个本就全是相同数的区间分成三个区间，或者把一个与两边不相等的区间改为和两边都相等的区间，我们只需要在每次操作后面都尝试进行区间合并就可以了。

与P2894不同的是，这道题数据比较弱，不开O2，不卡常的ODT就可以解决这道题了。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline bool read(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
    {
        return 0;
    }
    while (c != '-' && (c < '0' || c > '9'))
    {
        c = getchar();
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0');
    }
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(T x)
{
    if (x > 9)
    {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN=50010;

struct node
{
    mutable int l,r,v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator<(const node &o) const
    {
        return l<o.l;
    }
};

set<node> s;
long long ans=0;

inline void check()
{
    for(set<node>::iterator it=s.begin();it!=s.end();++it)
    {
        for(int j=1;j<=(it->r-it->l+1);++j)
        {
            cout<<it->v<<" ";
        }
    }
    cout<<endl;
}

inline void merge(int l)
{
    set<node>::iterator it1,it2,it3;
    it2=s.lower_bound(l);
    if(it1==s.begin())
        return;
    it1=it2,it3=it2;
    it1--,++it3;
    bool pd3=(it3!=s.end());
    if(pd3&&it1->v==it2->v&&it2->v==it3->v&&it1->v==it3->v)
    {
        int l=it1->l,r=it3->r,v=it2->v;
        s.erase(it1,++it3);
        s.insert(node(l,r,v));
    }
    else if(it1->v==it2->v)
    {
        int l=it1->l,r=it2->r,v=it2->v;
        s.erase(it1,++it2);
        s.insert(node(l,r,v));
    }
    else if(pd3&&it2->v==it3->v)
    {
        int l=it2->l,r=it3->r,v=it2->v;
        s.erase(it2,++it3);
        s.insert(node(l,r,v));
    }
}

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v=0)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline void add(int sum)
{
    set<node>::iterator itl,itr;
    itl=s.begin();
    bool pd=false;
    while(itl!=s.end())
    {
        if(itl->v==1)
        {
            ++itl;
            continue;
        }
        itr=itl;
        while(itr!=s.end()&&itr->v==0)
        {
            ++itr;
        }
        bool ccpd=false;
        if(itr==s.end())
            ccpd=true;
        --itr;
        if(itr->r-itl->l+1>=sum)
        {
            pd=true;
            break;
        }
        if(ccpd)
        {
            break;
        }
        itl=itr;
        ++itl;
    }
    if(pd==false)
        ans++;
    else
    {
        int l=itl->l,r=itr->r;
        s.erase(itl,++itr);
        s.insert(node(l,l+sum-1,1));
        if(r-l+1!=sum)
        {
            s.insert(node(l+sum,r,0));
        }
        merge(l);
    }
}

int n,m;

int main()
{
    read(n),read(m);
    s.insert(node(1,n,0));
    while(m--)
    {
    	char op;
    	cin>>op;
        int x,y;
        if(op=='A')
        {
            read(x);
            add(x);
        }
        else
        {
            read(x),read(y);
            assignval(x,y,0);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：SIXIANG32 (赞：1)

显然这是一道线段树，一个不错的线段树。  
闲话少说，切入正题——   

---
简单来说，这个线段树是让我们进行两个操作，一是区间赋值（$1$ 为进去，$2$ 为离开），二是找一个最靠左的连续区间元素都是 $2$ 且长度 $\ge a$ 的区间的左端点。  

一很简单，我们开一个 $lazy$ 表示当前节点的值，二的操作则是该题的重点了。  

显然，线段树节点 $[l,r]$ 的最长连续元素都为 $2$ 的小区间 $[l',r']$ 要不然都在 $[l,mid]$，要不然都在 $[mid + 1,r]$，要不然横跨这两个区间（$mid = (l + r) \div 2 $ 向下取整）。  

所以我们就可以再用线段树维护三个值 $ll,rr,len$，$ll$ 表示从左端点开始的最长连续元素都为 $2$ 的区间长度，$rl$ 表示从右端点开始的最长连续元素都为 $2$ 的区间长度，$len$ 为这个区间最长连续元素都为 $2$ 的区间总长。  

---

毕竟是线段树，考虑 push\_up 和 push\_down。对于 push\_up，更新 $ll_{now}$ 则是看 $ll_{ls_{now}}$ 是不是全空，如果全空，这说明 $ll_{ls_{now}}$ 能接上 $ll_{rs_{now}}$，那么 $ll_{now} = ll_{ls_{now}} + ll{rs_{now}}$，反之就是 $ll_{ls_{now}}$。至于 $rl$ 同理。$len$ 的话要么然都在左儿子，就是 $len_{ls_{now}}$，要么然都在右儿子，就是 $len_{rs_{now}}$，要么然就是横跨两个区间，就是 $rl_{ls_{now}} + ll_{rs_{now}}$，取 $\max$ 就好了。  

然后我们就要考虑 push\_down 了。我们要考虑 $now$ 的左右儿子的 $len,ll,rl$。当 $lazy = 2$，也就是当前节点全空，那么三者都是这个区间的长度，反之为 $0$。然后下放一下左右儿子的 $lazy$ 就好了。  

---

还有一个要考虑，就是线段树的两个操作，一个是获取大区间最靠左的连续元素都为 $2$ 且长度 $\ge a$ 的这样一个子区间的左端点。我们来分类讨论：  
1. 左儿子够用，递归左子树，优先递归左子树是因为要获得最靠左区间。  
2. 两个区间合起来就够用了，计算后返回。
3. 1 和 2 都不成立，递归右子树。

$updata$ 则是区间赋值，这就不用多说了，维护一下 $len,ll,rl$ 和 $lazy$ 就好了。$len,ll,rl$ 在赋的值为 $2$ 时就是区间长度。
 
---
总之这道题稍微难一点的地方就是 push_up 和 push_down 的维护。其实这个想法很经典的，但是对于我这样第一次接触的蒟蒻来说还是有点难的（菜是原罪

上朴实无华的代码~  
```cpp
#include <iostream>
#define MAXN 500010
#define QWQ cout << "qwq" << endl;
using namespace std;
int lazy[MAXN * 4 + 10], ll[MAXN * 4 + 10], rl[MAXN * 4 + 10], len[MAXN * 4 + 10];
//1 h 2 n 
int ls(int x) {return (x << 1);}
int rs(int x) {return (x << 1 | 1);}
int max(int x, int y) {return ((x > y) ? (x) : (y));}
void push_up(int now, int L, int R) {//更新
	ll[now] = ((ll[ls(now)] == L) ? (L + ll[rs(now)]) : (ll[ls(now)]));
	rl[now] = ((rl[rs(now)] == R) ? (R + rl[ls(now)]) : (rl[rs(now)]));
	len[now] = max(max(len[ls(now)],len[rs(now)]), ll[rs(now)] + rl[ls(now)]);
}
void push_down(int now, int L, int R) {//下放
	if((lazy[now] > 0) && (L && R)) {
		len[ls(now)] = ll[ls(now)] = rl[ls(now)] = ((lazy[now] == 2) ? (L) : (0));
		len[rs(now)] = ll[rs(now)] = rl[rs(now)] = ((lazy[now] == 2) ? (R) : (0));
		lazy[ls(now)] = lazy[rs(now)] = lazy[now], lazy[now] = 0;
	}
}
int get_pos(int q, int s, int t, int now) {
	int mid = (s + t) >> 1;
	//cout << s << ' ' << t << ' ' << now << endl;
	push_down(now, mid - s + 1, t - mid); 
	if(len[ls(now)] >= q) return get_pos(q, s, mid, ls(now));
	else if(ll[rs(now)] + rl[ls(now)] >= q) return mid - rl[ls(now)] + 1;
	return get_pos(q, mid + 1, t, rs(now));
}
void updata(int l, int r, int s, int t, int now, int val) {
	int mid = (s + t) >> 1;
	if(l <= s && r >= t) {
		len[now] =  ll[now] = rl[now] = ((val == 2) ? (t - s + 1) : (0)); 
		lazy[now] = val;
		return ;
	}
	push_down(now, mid - s + 1, t - mid);
	if(l <= mid) updata(l, r,    s, mid , ls(now), val);
	if(r >  mid) updata(l, r, mid + 1, t, rs(now), val);
	push_up(now, mid - s + 1, t - mid);
}
void build(int l, int r, int now){
	len[now] = ll[now] = rl[now] = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(l  ,   mid, ls(now));
	build(mid + 1, r, rs(now));
}
int main() {
	int n, m, a, b, ans = 0;
	char opt;
	cin >> n >> m;
	build(1, n, 1);
	while(m--) {
		cin >> opt >> a;
		if(opt == 'A') {
			if(len[1] < a) ans ++;
			else {
				int pos = get_pos(a, 1, n, 1);
				updata(pos, pos + a - 1, 1, n, 1, 1);
			}
		}
		else cin >> b, updata(a, b, 1, n, 1, 2);
	}
	cout << ans << endl;
}
```

---

## 作者：cyc001 (赞：0)

这里我用了一个奇妙的数据结构 ——珂朵莉树！

前置芝士：对是 ```std::set``` 的熟练使用。

### 核心思想

把值相同的区间放在一个 ```set``` 里，使其完成类似线段树的功能。

### 主要操作

操作1：```spilt```

作用：把 ```set``` 中的一个区间 $[l,r]$ 从 $x$ 处分裂为区间 $[l,x)$ 和 $[x,r]$ 并返回后者的迭代器。

实现过程：用 ```set``` 中的 ```upper_bound``` 函数查找位置 $x$。

用法：对区间 $[l,r]$ 进行操作时转换为 ```set``` 上 $[spilt(l),spilt(r+1) )$ 的操作。

**Code:**
```cpp
auto split(int u) {
	if (u > sz) return cht.end();
	auto it = --cht.upper_bound({ u,0,0 });
	if (it->l == u) return it;
	int nl = it->l, nr = it->r, nv = it->v;
	cht.erase(it); cht.insert({ nl, u - 1, nv });
	return cht.insert({ u, nr, nv }).first;
}
```

操作2：```assign```

作用：将区间 $[l,r]$ 赋值为 $v$ 。

实现过程：使用 ```spilt(l)``` 和 ```spilt(r+1)``` 后删除从 ```spilt(l)``` 至 ```spilt(r+1)``` 间的所有元素，并加入值为 $v$ 的区间 $[l,r] $。

**Code:**
```cpp
void assign(int l, int r, int v) {
	auto ir = split(r + 1), il = split(l);
	cht.erase(il, ir);
	cht.insert({ l,r,v });
}
```


其余操作均可转换为 ```set``` 上的区间操作

----

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct chtree {
	int sz;
	struct Node {
		int l, r, v;
		bool operator<(const Node& nd) const { return l < nd.l; }
	};
	set<Node> cht;
	auto split(int u) {
		if (u > sz) return cht.end();
		auto it = --cht.upper_bound({ u,0,0 });
		if (it->l == u) return it;
		int nl = it->l, nr = it->r, nv = it->v;
		cht.erase(it); cht.insert({ nl, u - 1, nv });
		return cht.insert({ u, nr, nv }).first;
	}
	chtree(int _sz) { sz = _sz; cht.insert({ 0,sz,0 }); }
	void assign(int l, int r, int v) {
		auto ir = split(r + 1), il = split(l);
		cht.erase(il, ir);
		cht.insert({ l,r,v });
	}
	int findseat(int n) {
		int sl = 1;
		for (auto it = cht.begin(); it != cht.end(); ++it) {
			if (it->v == 1) sl = it->r + 1;
			if (it->r - sl + 1 >= n) {
				assign(sl, sl + n - 1, 1);
				return 0;
			}
		}
		return 1;
	}
};
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, ans = 0; cin >> n >> m; chtree ct(n);
	for (int i = 0, l, r; i < m; ++i) {
		char opt;
		cin >> opt;
		if (opt == 'L') {
			cin >> l >> r;
			ct.assign(l, r, 0);
		} else {
			cin >> l;
			ans += ct.findseat(l);
		}
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：wkjwkj (赞：0)

本题显然用线段树维护。

我们用 $1$ 代表空房，$0$ 代表有人。

我们对于线段树，需要记录一下信息：

```cpp
struct SgT{
	int l,r;
	int lmax,rmax;//左端1的个数和右端1的个数
	int ans;//区间中最多连续1的个数
	int add;//懒惰标记
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define rx(p) tree[p].rmax
	#define lx(p) tree[p].lmax
	#define add(p) tree[p].add
	#define ans(p) tree[p].ans
}tree[M*4];
```

对于本题，维护 `lmax` 与 `rmax` 和 `ans` 较为容易，这里做出较为简单的解释。

对于节点 `p`，其 `lmax` 应为节点 `p*2` 的 `lmax` ，其若需扩展则必须满足 `lx(p*2)=r(p*2)-l(p*2)+1`，即左边子树的区间是全 $1$，那么才可以与右子树的 `lmax` 合并。

维护其 `rmax` 同理。

维护节点 `p` 的 `ans` 需要在三个值中取最大。这其实很好理解，`p` 节点的 `ans` 只可能为 `p*2` 节点的 `ans` 或 `p*2+1` 节点的 `ans` 或 `p*2` 节点的 `rmax` 与 `p*2+1` 节点的 `lmax` 进行合成。

比较重要的是本题 `ask` 函数的设计。

本题 `ask` 函数应返回满足条件的最左端点，这时我们采用区间覆盖的写法就不行了，我们需要采用精准覆盖的方法。

```cpp
int ask(int p,int l,int r,int x)
{
	if(l==r)return l;//如果找到答案
	spread(p);//优先传递标记
	int mid=(l+r)>>1;
	if(ans(p*2)>=x)return ask(p*2,l,mid,x);//优先在左子树找，如果左子树答案比x大就进左子树
	if(rx(p*2)+lx(p*2+1)>=x)return mid-rx(p*2)+1;//左子树答案不够大，尝试左右子树拼接
	return ask(p*2+1,mid+1,r,x);//以上都不行，只能找右子树
}
```

至此，解决本题应该已经没有太大问题。

下面给出完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int M=500005;
struct SgT{
	int l,r;
	int lmax,rmax;
	int ans;
	int add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define rx(p) tree[p].rmax
	#define lx(p) tree[p].lmax
	#define add(p) tree[p].add
	#define ans(p) tree[p].ans
}tree[M*4];
void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r){
		lx(p)=1,rx(p)=1;
	    ans(p)=1;
	    add(p)=0;
		return;
	}
	int mid=(l+r)>>1;
	lx(p)=r-l+1,rx(p)=r-l+1;
	ans(p)=r-l+1;
	add(p)=0;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
void spread(int p)
{
	if(add(p)){
		if(add(p)==1){
			lx(p*2)=lx(p*2+1)=0;
			rx(p*2)=rx(p*2+1)=0;
			ans(p*2)=ans(p*2+1)=0;
			add(p*2)=add(p*2+1)=1;
		}
		else{
			lx(p*2)=r(p*2)-l(p*2)+1;
			rx(p*2)=r(p*2)-l(p*2)+1;
			ans(p*2)=r(p*2)-l(p*2)+1;
			lx(p*2+1)=r(p*2+1)-l(p*2+1)+1;
			rx(p*2+1)=r(p*2+1)-l(p*2+1)+1;
			ans(p*2+1)=r(p*2+1)-l(p*2+1)+1;
			add(p*2)=add(p*2+1)=-1;
		}
		add(p)=0;
	}
}
void change(int p,int l,int r,int x)
{
	if(l<=l(p)&&r>=r(p)){
		add(p)=x;
		if(x==1){
			lx(p)=0;
			rx(p)=0;
			ans(p)=0;
		}
		else{
			lx(p)=r(p)-l(p)+1;
			rx(p)=r(p)-l(p)+1;
			ans(p)=r(p)-l(p)+1;
		}
		//puts("uioifoasd");
		return;
	}
	spread(p);
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)change(p*2,l,r,x);
	if(r>mid)change(p*2+1,l,r,x);
	lx(p)=lx(p*2),rx(p)=rx(p*2+1);
	if(ans(p*2+1)==r(p*2+1)-l(p*2+1)+1)rx(p)+=rx(p*2);
	if(ans(p*2)==r(p*2)-l(p*2)+1)lx(p)+=lx(p*2+1);
	ans(p)=max(ans(p*2),max(ans(p*2+1),rx(p*2)+lx(p*2+1)));
}
int ask(int p,int l,int r,int x)
{
	if(l==r)return l;
	spread(p);
	int mid=(l+r)>>1;
	if(ans(p*2)>=x)return ask(p*2,l,mid,x);
	//printf("%d %d\n",rx(p*2),lx(p*2+1));
	if(rx(p*2)+lx(p*2+1)>=x)return mid-rx(p*2)+1;
	return ask(p*2+1,mid+1,r,x);
}
int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		char op[5];
		scanf("%s",op+1);
		if(op[1]=='A'){
			int x;
			scanf("%d",&x);
			if(ans(1)<x){
				cnt++;
				continue;
			}
			int u=ask(1,1,n,x);
			//printf("%d\n",u);
			//puts("oooo");
			change(1,u,u+x-1,1);
		}
		else{
			int x,y;
			scanf("%d%d",&x,&y);
			change(1,x,y,-1);
		}
	}
	printf("%d\n",cnt);
	return 0;
}
```



---

