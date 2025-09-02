# [USACO08FEB] Hotel G

## 题目描述

The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi ..Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

你需要对每个输入 $1$ 输出对应的答案。

## 样例 #1

### 输入

```
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
```

### 输出

```
1
4
7
0
5
```

# 题解

## 作者：Chemist (赞：155)

区间操作，考虑用线段树维护，需要维护每一段区间的最大连续空房的数量sum，但是只维护这一个值是不够的，因为这时当我们更新节点信息时没法直接让父亲节点的sum等于两个儿子的sum和，比如左儿子在1~4中有三个连续空房1、2、3，右儿子在5~8中有三个连续空房6、7、8，这时父亲的sum显然不等于6而等于3。

因此在新建线段树时需要维护如下信息（懒标记会在下面的区间修改中用到）：
```cpp
struct Segment_Tree{
	int sum;//区间最大连续空房数
	int len;//区间长度 
	int lmax,rmax;//从左开始或从右开始的最大连续空房数
	int lazy;//懒标记 
}t[4*MAXX];
```

然后是建树过程，维护上述信息。
```cpp
void build(int p,int l,int r)
{
	t[p].lazy=0;//懒标记清零
	t[p].sum=t[p].len=t[p].lmax=t[p].rmax=r-l+1;
	//初始均为空房，所以连续空房长度都整个区间长度
	if(l==r)return;
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r); 
}
```
懒标记下放：
```cpp
void spread(int p)
{
	if(t[p].lazy==0)return;
    //没有标记直接返回
	if(t[p].lazy==1){
    //如果要新开房
	    t[p*2].lazy=t[p*2+1].lazy=1;
    //下放懒标记
		t[p*2].sum=t[p*2].lmax=t[p*2].rmax=0;
		t[p*2+1].sum=t[p*2+1].lmax=t[p*2+1].rmax=0;
    //这一段区间没有剩余房间
	}
	if(t[p].lazy==2){
    //如果退房
		t[p*2].lazy=t[p*2+1].lazy=2;
		t[p*2].sum=t[p*2].lmax=t[p*2].rmax=t[p*2].len;
		t[p*2+1].sum=t[p*2+1].lmax=t[p*2+1].rmax=t[p*2+1].len;
    //这一段房间全部是空的
	}
	t[p].lazy=0;//懒标记清零
}
```
更新节点信息：
```cpp
void renew(int p)
{
	if(t[p*2].sum==t[p*2].len)//左区间全为空房 
	 t[p].lmax=t[p*2].len+t[p*2+1].lmax;
    //那么左区间全部可住，在加上右区间从左开始的最长区间
	else t[p].lmax=t[p*2].lmax;
    //否则父节点的lmax等于左区间的lmax
	if(t[p*2+1].sum==t[p*2+1].len)//右区间全为空房，同理
	 t[p].rmax=t[p*2+1].len+t[p*2].rmax; 
	else t[p].rmax=t[p*2+1].rmax;
	t[p].sum=max(max(t[p*2].sum,t[p*2+1].sum),t[p*2].rmax+t[p*2+1].lmax);
    //p节点的sum有三种：全在左边的，全在右边的，跨越左右区间的，取个max就好了
} 
```
现在线段树的基本操作已经完成，再看题，题目要求我们在线段树上支持两种操作：区间修改，查询max(sum)的左端点

区间修改（修改分两种：退房和开房）：
```cpp
void change(int p,int l,int r,int tag,int L,int R)
//tag=1代表没人住，tag=2代表有人住，[L,R]是要修改的区间 
{
	spread(p);//下放懒标记
	if(L<=l&&r<=R){//如果要修改的区间完全覆盖了当前节点所代表的区间 
    	if(tag==1)t[p].sum=t[p].lmax=t[p].rmax=0;
    //如果要开房，这一段房间全部不可用
		else t[p].sum=t[p].lmax=t[p].rmax=t[p].len; 
    //如果要退房，这一段区间全部可用
		t[p].lazy=tag;//更新懒标记
		return;
	}
	int mid=(l+r)/2;
	if(L<=mid)change(p*2,l,mid,tag,L,R);
	if(R>mid)change(p*2+1,mid+1,r,tag,L,R);
    //修改左右儿子
	renew(p);//更新节点信息
}
```
查询：
```cpp
int ask(int p,int l,int r,int length)
{
	spread(p);//下放懒标记
	if(l==r)return l;//如果找到对应区间，返回左端点
	int mid=(l+r)/2;
	if(t[p*2].sum>=length)return ask(p*2,l,mid,length);
    //如果左区间即可找到足够多的房间，就在左区间找
	if(t[p*2].rmax+t[p*2+1].lmax>=length)return mid-t[p*2].rmax+1;
    //如果在中间能找到足够多的房间，答案就是左区间从右开始的最长连续区间的左端点
	else return ask(p*2+1,mid+1,r,length);
    //否则就在右边找
}
```
最后的主函数：
```cpp
int main()
{
	n=read();m=read();
	build(1,1,n);//建树
	for(int i=1;i<=m;i++) 
	{
		int act,x,y;
		act=read();
		if(act==1){
			x=read();
			if(t[1].sum>=x){
        //如果存在这么长的区间才找
				int left=ask(1,1,n,x);
				printf("%d\n",left);
				change(1,1,n,1,left,left+x-1);
                //找到之后记得修改
			}
			else printf("0\n");//否则找不到
		}
		else{
			x=read();y=read();
			change(1,1,n,2,x,x+y-1);//退房	
		}
	}
	return 0;
} 
```

---

## 作者：Owen_codeisking (赞：29)

看到题解都写得很长，是时候发一篇三目运算的题解了

其实第一篇题解讲得很清楚了，我来补充一下，类似最大子段和的做法，利用$sum$要么在左区间，要么在右区间，要么横跨两个区间

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
const int maxn=50000+10;
int n,m;

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
	int opt,l,x;
	while(m--){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d",&x);
			if(sum(1)>=x){
				l=query(x,1,n,1);
				printf("%d\n",l);
				update(l,l+x-1,2,1,n,1);
			}
			else printf("0\n");
		}
		else {
			scanf("%d%d",&l,&x);
			update(l,l+x-1,1,1,n,1);
		}
	}
	return 0;
}
```
没极限压行后$81$行，自认为代码还是比较清爽的

$upd:1.1$

刚学 $ODT$，发现这道题可以用 $ODT$ 水到 $92$，不过 $set$ 版超级慢，下次我手写一个 $list$ 试一试

$92$ 分代码：

```cpp
#include <bits/stdc++.h>
#define IT set<node>::iterator
using namespace std;
const int maxn=100000+10;
int n,m;

struct node{
	int l,r;
	mutable int val;
	node(int l,int r=-1,int val=0):l(l),r(r),val(val){}
};
bool operator < (const node &a,const node &b){
	return a.l<b.l;
}

set<node> s;

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}
void print(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

IT split(int x){
	IT it=s.lower_bound(node(x));
	if(it!=s.end()&&it->l==x) return it;
	it--;
	int l=it->l,r=it->r,val=it->val;
	s.erase(it);
	s.insert(node(l,x-1,val));
	return s.insert(node(x,r,val)).first;
}

void update(int l,int r,int x){
	IT R=split(r+1),L=split(l);
	s.erase(L,R);
	s.insert(node(l,r,x));
}

int query(int x){
	int ans=0,now=0;
	for(IT it=s.begin();it!=s.end();it++){
		if(it->r<=n&&it->val==0){
			if(now==0) ans=it->l;
			now+=it->r-it->l+1;
			if(now>=x) return ans;
		}
		else now=0;
	}
	return 0;
}

int main()
{
	n=read(),m=read();
	s.insert(node(1,n,0));
	s.insert(node(n+1,n+1,-1));
	int op,l,r,x;
	for(int i=1;i<=m;i++){
		op=read();
		if(op==1){
			x=read();
			printf("%d\n",l=query(x));
			if(l) update(l,l+x-1,1);
		}
		else {
			l=read(),r=read();
			update(l,l+r-1,0);
		}
	}
	return 0;
}
```

---

## 作者：amstar (赞：17)

线段树维护三个值，区间内最大的连续空位，从左边最大延伸的长度，从右边最大延伸的长度。


更新时，有人住让这些数组都为0，表示0个空位，没人住，就是区间长度，表示区间内的空位就是长度，都是空位。


其他的详见代码注释。





```cpp
#include<cstdio>
#include<algorithm>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int MAXN = 400010;
int len[MAXN],sum[MAXN],ml[MAXN],mr[MAXN],tag[MAXN];
//分别区间的长度，区间内最大的连续空位，从左边延伸最长的空位，同理从右边，懒标记 
int n,q;
void pushup(int rt)
{
    if (sum[rt<<1]==len[rt<<1])//如果左区间全是空位，大区间的ml就是左区间的全部 加 右区间的ml 
        ml[rt] = sum[rt<<1]+ml[rt<<1|1];
    else//否则就是最区间ml 
        ml[rt] = ml[rt<<1];
    if (sum[rt<<1|1]==len[rt<<1|1])//同理 
        mr[rt] = sum[rt<<1|1]+mr[rt<<1];
    else
        mr[rt] = mr[rt<<1|1];
    sum[rt] = max(max(sum[rt<<1],sum[rt<<1|1]),mr[rt<<1]+ml[rt<<1|1]);//大区间的最大连续长度，从两个子区间和中间的部分区最大的 
    return;
}
void pushdown(int rt)
{
    if (tag[rt]==0) return;
    if (tag[rt]==1)//有人住，所以设为0 
    {
        tag[rt<<1] = tag[rt<<1|1] = 1;
        sum[rt<<1] = ml[rt<<1] = mr[rt<<1] = 0;
        sum[rt<<1|1] = ml[rt<<1|1] = mr[rt<<1|1] = 0;
    }
    if (tag[rt]==2)//没有人住，全是空，就是区间的长度 
    {
        tag[rt<<1] = tag[rt<<1|1] = 2;
        sum[rt<<1] = ml[rt<<1] = mr[rt<<1] = len[rt<<1];
        sum[rt<<1|1] = ml[rt<<1|1] = mr[rt<<1|1] = len[rt<<1|1];
    }
    tag[rt] = 0;
}
void build(int l,int r,int rt)
{
    ml[rt] = mr[rt] = sum[rt] = len[rt] = r-l+1;
    tag[rt] = 0;
    if (l==r) return;
    int m = (l+r)>>1;
    build(lson);
    build(rson);
}
void update(int l,int r,int rt,int L,int R,int c)
{
    pushdown(rt);
    if (L<=l&&r<=R)
    {
        if (c==1) sum[rt] = ml[rt] = mr[rt] = 0;
        else sum[rt] = ml[rt] = mr[rt] = len[rt];
        tag[rt] = c;
        return ;
    }
    int m = (l+r)>>1;
    if (L<=m) update(lson,L,R,c);
    if (R>m)  update(rson,L,R,c);
    pushup(rt);
}
int query(int l,int r,int rt,int x)
{
    pushdown(rt);
    if (l==r) return l;
    int m = (l+r)>>1;
    if (sum[rt<<1]>=x) return query(lson,x);//如果左区间有x个连续空位，在左区间找 
    if (mr[rt<<1]+ml[rt<<1|1]>=x) return m-mr[rt<<1]+1;//如果左区间的右边 和 右区间的左边 加起来有x个连续空位，返回左区间右边最大时的起点 
    else return query(rson,x);//在右区间找，肯定会有的 
}
int main()
{
    scanf("%d%d",&n,&q);
    build(1,n,1);
    while (q--)
    {
        int opt,x,y,p;
        scanf("%d",&opt);
        if (opt==1)
        {
            scanf("%d",&x);
            if (sum[1]<x)//如果总区间没有x个连续的空位，输出0 
            {
                printf("0\n");
                continue;
            }
            p = query(1,n,1,x);
            printf("%d\n",p);
            update(1,n,1,p,p+x-1,1);//区间不是0，所以数组都是0，见数组定义 
        }
        else
        {
            scanf("%d%d",&x,&y);
            update(1,n,1,x,x+y-1,2);//将区间设为0，所以数组都是区间的长度 
        }
    }
    return 0;
}
```

---

## 作者：Bronya18C (赞：10)

# 水过了一道蓝题（美滋滋%%%%%%%）
---
还是先说一下做法：

1、模拟，暴力

2、快读。

3、O2

---
主要是按题意模拟，线性求最左的超过长度的空位，标记为1.
去掉就标记为0.
```
#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int a,k,g,x,y;
bool ok;
bool z[500005];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main()
{
    n=read();
    m=read();
    for(register int i=1;i<=m;i++){
    	a=read();
    	if(a==1){
    	k=read();
    	ok=0;
    	g=0;
    	for(int j=1;j<=n;j++){
    		if(z[j]==0){
    			g++;
    		}
    		else {
    			g=0;
    		}
    		if(g>=k){
    			for(register int l=j-k+1;l<=j;l++)
    				z[l]=1;
    			printf("%d\n",j-k+1);
    			ok=1;
    			break;
    		}
    	}
    	if(!ok)puts("0");
    	}
    	else {
    		x=read();
    		y=read();
    		for(register int j=x;j<=x+y-1;j++)z[j]=0;
    	}
	}
    return 0;
}
```

---

## 作者：chihik (赞：8)

这道题明显是线段树的板题，至于考试时因为懒标记的小问题只有20分，~~我也很无奈~~。

进入正题，既然要修改查询区间内连续的一段元素，~~似曾相识的感觉~~。
我们等价的把空房子看为1，住人的房子看为0。

我们维护三个值: $num$表示这个区间最长的一段连续$'1'$串 ， $lnum$表示这个区间从左端点开始的最长连续$'1'$串 , $rnum$表示这个区间从右端点开始的最长连续$'1'$串。

然后，用f记录区间状态（懒标记），$f=1$表示全为1，$f=0$表示全为0，$f=2$什么都没发生。

然后，就照着线段树的模板写。稍微麻烦一点的是区间修改后的维护与查询操作，下面来讲解一下。

#### 1.区间修改后的维护（$pushup$函数）

在得到两个子区间后，我们需要根据他们得出大区间的信息。（废话）

1.$lnum$，$rnum$

显然，大区间的$lnum$就等于左区间的$lnum$，特殊情况下，当左区间全为1时，大区间的$lnum$等于左区间的长度加上右区间的$lnum$。$rnum$同理。

2.$num$

显然，大区间的$num$可能是两个小区间的$num$的较大值，同时，也可能是由左区间的$rnum$和右区间$lnum$的拼接而成的连续‘1’串。

#### 2.区间查询（$Find$函数）

应该比较好理解，哪个区间足够就查询哪个区间吗，注意输出最小的值，从左到右依次查询。


```cpp
#include <cstdio>
#define ls x << 1
#define rs x << 1 | 1
#define INF 0x3f3f3f3f

const int MAXN = 50000;
int n,m;
struct node{
	int l , r , f;
	int num , lnum , rnum;
}Tree[ 4 * MAXN + 5 ];

int Max( int x , int y ) {
	return x > y ? x : y;
}
int Min( int x , int y ) {
	return x < y ? x : y;
}

void Build( int x , int l , int r ) {
	Tree[ x ].l = l , Tree[ x ].r = r , Tree[ x ].f = 2;
	Tree[ x ].lnum = Tree[ x ].rnum = Tree[ x ].num = Tree[ x ].r - Tree[ x ].l + 1;
	if( l == r ) return;
	
	int Mid = ( l + r ) / 2;
	Build( ls , l , Mid );
	Build( rs , Mid + 1 , r );
}
void pushup( int x ) {
	Tree[ x ].lnum = Tree[ ls ].lnum;
	if( Tree[ ls ].num == Tree[ ls ].r - Tree[ ls ].l + 1 ) Tree[ x ].lnum = Tree[ ls ].num + Tree[ rs ].lnum;
	
	Tree[ x ].rnum = Tree[ rs ].rnum;
	if( Tree[ rs ].num == Tree[ rs ].r - Tree[ rs ].l + 1 ) Tree[ x ].rnum = Tree[ rs ].num + Tree[ ls ].rnum;
	
	Tree[ x ].num = Max( Max( Tree[ ls ].num , Tree[ rs ].num ) , Tree[ ls ].rnum + Tree[ rs ].lnum );
}
void pushdown( int x ) {
	if( Tree[ x ].l == Tree[ x ].r )
		return;
	if( Tree[ x ].f == 0 ) {
		Tree[ ls ].num = 0 , Tree[ ls ].f = 0;
		Tree[ rs ].num = 0 , Tree[ rs ].f = 0;
		Tree[ ls ].lnum = Tree[ ls ].rnum = 0;
		Tree[ rs ].lnum = Tree[ rs ].rnum = 0;
		Tree[ x ].f = 2;
	}
	if( Tree[ x ].f == 1 ) {
		Tree[ ls ].num = Tree[ ls ].r - Tree[ ls ].l + 1 , Tree[ ls ].f = 1;
		Tree[ rs ].num = Tree[ rs ].r - Tree[ rs ].l + 1 , Tree[ rs ].f = 1;
		Tree[ ls ].lnum = Tree[ ls ].rnum = Tree[ ls ].num;
		Tree[ rs ].lnum = Tree[ rs ].rnum = Tree[ rs ].num;
		Tree[ x ].f = 2;
	}
}
void Insert( int x , int l , int r , int k ) {
	if( l > Tree[ x ].r || Tree[ x ].l > r )
		return;
	if( l <= Tree[ x ].l && Tree[ x ].r <= r ) {
		Tree[ x ].f = k;
		Tree[ x ].num = k == 1 ? Tree[ x ].r - Tree[ x ].l + 1 : 0;
		Tree[ x ].lnum = Tree[ x ].rnum = Tree[ x ].num;
		return;
	}
	pushdown( x );
	Insert( ls , l , r , k );
	Insert( rs , l , r , k );
	pushup( x );
}
int Find( int x , int k ) {
	if( Tree[ x ].l == Tree[ x ].r ) return Tree[ x ].l;
	pushdown( x );
	if( Tree[ ls ].num >= k ) return Find( ls , k );
	if( Tree[ ls ].rnum + Tree[ rs ].lnum >= k ) return Tree[ ls ].r - Tree[ ls ].rnum + 1;
	if( Tree[ rs ].num >= k ) return Find( rs , k );
}
int main( ) {
	//freopen("hotel.in","r",stdin);
	//freopen("hotel.out","w",stdout);
	
	scanf("%d %d",&n,&m);
	Build( 1 , 1 , n );
	int op,x,d;
	for( int i = 1 ; i <= m ; i ++ ) {
		scanf("%d",&op);
		if( op == 1 ) {
			scanf("%d",&d);
			if( Tree[ 1 ].num < d ) {
				printf("0\n");
				continue;
			}
			int r = Find( 1 , d );
			Insert( 1 , r , r + d - 1 , 0 );
			printf("%d\n",r);
		}
		else if( op == 2 ) {
			scanf("%d %d",&x,&d);
			Insert( 1 , x , x + d - 1 , 1 );
		}
	}
	return 0;
}
```

---

## 作者：_l_l_ (赞：7)

Links: [Here](https://www.luogu.com.cn/problem/P2894)

这道题是一道线段树的题目。

乍一看，修改还好修改，只是...

...查询是什么鬼？

![](https://cdn.luogu.com.cn/upload/image_hosting/46mbvqdh.png)

题目是要查询长度大于 n 的连续空房区间。

那么我们定义 `val[]` 为区间内的最大空房。

我们可以考虑维护：

1. 区间内从左边开始的最长连续空房区间的长度(`lmax[]`)。
2. 区间内从右边开始的最长连续空房区间的长度(`rmax[]`)。

查询时，我们可以：

1. 只从区间左子树查询(`val[lson]`)，如 `* 0 0 *|* * * *`。
2. 只从区间右子树查询(`val[rson]`)，如 `* * * *|* 0 0 *`。
3. 查询的区间跨越了中线(`rmax[lson] + lmax[rson]`)，如 `* * 0 0|0 * * *`。

答案就是**符合要求时**按顺序查询：

```cpp
if (val[lson] >= want) return search(want, l, mid, lson);
else if (rmax[lson] + lmax[rson] >= want) return mid - rmax[lson] + 1;
else if (val[rson] >= want) return search(want, mid + 1, r, rson);
else return 0;

```

在~~个人的~~代码中，`lazy[o] == 1` 代表清空区间，`lazy[o] == 2`代表填满区间。（`lazy[o] == 0` 不需要说了吧...）

再注意一下 `pushdown` 下推懒标记操作就可以了：

```cpp
void pushdown(int o) {
    if (lazy[o]) {
        lmax[lson] = rmax[lson] = val[lson] = lazy[o] == 1 ? 0 : len[lson];
        lmax[rson] = rmax[rson] = val[rson] = lazy[o] == 1 ? 0 : len[rson];
        lazy[lson] = lazy[rson] = lazy[o];
    }
    lazy[o] = 0;
}
```

完整代码：

```cpp
#include <cstdio>
#include <algorithm>
#define lson o << 1
#define rson (o << 1) | 1
using namespace std;
const int MAXN = 50001;
struct SegmentTree {
    int val[MAXN << 2]， len[MAXN << 2], lmax[MAXN << 2], rmax[MAXN << 2], lazy[MAXN << 2];
    void pushup(int o) {
        lmax[o] = val[lson] == len[lson] ? len[lson] + lmax[rson] : lmax[lson];
        rmax[o] = val[rson] == len[rson] ? len[rson] + rmax[lson] ： rmax[rson];
        val[o] = max(max(val[lson], val[rson]), rmax[lson] + lmax[rson]);
    }
    void pushdown(int o) {
        if (lazy[o]) {
            lmax[lson] = rmax[lson] = val[lson] = lazy[o] == 1 ? 0 : len[lson];
            lmax[rson] = rmax[rson] = val[rson] = lazy[o] == 1 ? 0 : len[rson];
            lazy[lson] = lazy[rson] = lazy[o];
        }
        lazy[o] = 0;
    }
    void build(int l, int r, int o) {
        val[o] = len[o] = lmax[o] = rmax[o] = r - l + 1;
        lazy[o] = 0;
        if (l != r) {
            int mid = (l + r) >> 1;
            build(l, mid, lson);
            build(mid + 1, r, rson);
        }
    }
    int search(int want, int l, int r, int o) {
        pushdown(o);
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (val[lson] >= want) return search(want, l, mid, lson);
        else if (rmax[lson] + lmax[rson] >= want) return mid - rmax[lson] + 1;
        else if (val[rson] >= want) return search(want, mid + 1, r, rson);
        else return 0;
    }
    void change(bool type, int cl, int cr, int l, int r, int o) {
        pushdown(o);
        if (cl <= l and cr >= r) {
            val[o] = lmax[o] = rmax[o] = type ? len[o] : 0;
            lazy[o] = int(type) + 1;
            return;
        }
        if (cr < l or cl > r) return;
        else {
            int mid = (l + r) >> 1;
            change(type, cl, cr, l, mid, lson);
            change(type, cl, cr, mid + 1, r, rson);
            pushup(o);
        }
    }
} seg；
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    seg.build(0, n, 0);
    for (int i = 0; i < m; i++) {
        int k, a;
        scanf("%d %d", &k, &a);
        if (k == 1) {
            if (seg.val[1] >= a) {
                int s = seg.search(a, 0, n, 0);
                printf("%d\n", s);
                seg.change(0, s, s + a - 1, 0, n, 0);
            }
            else {
                printf("0\n");
            }
        }
        else {
            int b;
            scanf("%d", &b);
            seg.change(1, a, a + b - 1, 0, n, 0);
        }
    }
    return 0;
}
```

然而我埋了几个坑

直接提交会发现

![](https://cdn.luogu.com.cn/upload/image_hosting/gpxonk13.png)

即使你改了 CE 也不能过的，乖乖自己写吧（光速逃 + 切勿谔谔）

---

## 作者：lukelin (赞：5)

### 首先安利博客
[更好的阅读体验](https://www.cnblogs.com/linzhengmin/p/11140727.html)  
### 正确的题解
首先我们都知道这题要用线段树做。考虑维护靠左边的answer，靠右边的answer，和整个区间的answer，那么就珂以维护这道题目了。  
这里比较复杂的有下传操作和上传操作。
#### 上传
```cpp
void pushUp(int pos, int l, int r){
    seg[pos].ans = max(seg[pos << 1].rans + seg[pos << 1 | 1].lans, max(seg[pos << 1].ans, seg[pos << 1 | 1].ans));
    int mid = (l + r) >> 1;
    if (seg[pos << 1].ans == mid - l + 1)
        seg[pos].lans = seg[pos << 1 | 1].lans + seg[pos << 1].ans;
    else
        seg[pos].lans = seg[pos << 1].lans;
    if (seg[pos << 1 | 1].ans == r - mid)
        seg[pos].rans = seg[pos << 1].rans + seg[pos << 1 | 1].ans;
    else
        seg[pos].rans = seg[pos << 1 | 1].rans;
}
```
#### 下传
```cpp
void pushDown(int pos, int l, int r){
    if (!seg[pos].lazy){
        seg[pos << 1].lazy = seg[pos << 1 | 1].lazy = 0;
        int mid = (l + r) >> 1;
        seg[pos << 1].ans = seg[pos << 1].lans = seg[pos << 1].rans = mid - l + 1;
        seg[pos << 1 | 1].ans = seg[pos << 1 | 1].lans = seg[pos << 1 | 1].rans = r - mid;
    }
    else if (seg[pos].lazy == 1){
        seg[pos << 1].lazy = seg[pos << 1 | 1].lazy = 1;
        seg[pos << 1].ans = seg[pos << 1].lans = seg[pos << 1].rans = 0;
        seg[pos << 1 | 1].ans = seg[pos << 1 | 1].lans = seg[pos << 1 | 1].rans = 0;
    }
    seg[pos].lazy = -1;
}

```
### 正解代码
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Node{
    int ans, lans, rans;
    int lazy; 
} seg[200000];

void pushUp(int pos, int l, int r){
    seg[pos].ans = max(seg[pos << 1].rans + seg[pos << 1 | 1].lans, max(seg[pos << 1].ans, seg[pos << 1 | 1].ans));
    int mid = (l + r) >> 1;
    if (seg[pos << 1].ans == mid - l + 1)
        seg[pos].lans = seg[pos << 1 | 1].lans + seg[pos << 1].ans;
    else
        seg[pos].lans = seg[pos << 1].lans;
    if (seg[pos << 1 | 1].ans == r - mid)
        seg[pos].rans = seg[pos << 1].rans + seg[pos << 1 | 1].ans;
    else
        seg[pos].rans = seg[pos << 1 | 1].rans;
}

void pushDown(int pos, int l, int r){
    if (!seg[pos].lazy){
        seg[pos << 1].lazy = seg[pos << 1 | 1].lazy = 0;
        int mid = (l + r) >> 1;
        seg[pos << 1].ans = seg[pos << 1].lans = seg[pos << 1].rans = mid - l + 1;
        seg[pos << 1 | 1].ans = seg[pos << 1 | 1].lans = seg[pos << 1 | 1].rans = r - mid;
    }
    else if (seg[pos].lazy == 1){
        seg[pos << 1].lazy = seg[pos << 1 | 1].lazy = 1;
        seg[pos << 1].ans = seg[pos << 1].lans = seg[pos << 1].rans = 0;
        seg[pos << 1 | 1].ans = seg[pos << 1 | 1].lans = seg[pos << 1 | 1].rans = 0;
    }
    seg[pos].lazy = -1;
}

void build(int pos, int l, int r){
    if (l == r){
        seg[pos].ans = seg[pos].lans = seg[pos].rans = 1;
        seg[pos].lazy = -1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(pos << 1, l, mid), build(pos << 1 | 1, mid + 1, r);
    pushUp(pos, l, r);
}

void modify(int pos, int l, int r, int x, int y, int val){
    if (x <= l && r <= y){
        if (val) seg[pos].ans = seg[pos].lans = seg[pos].rans = 0;
        else seg[pos].ans = seg[pos].lans = seg[pos].rans = r - l + 1;
        seg[pos].lazy = val;
        return ;
    }
    pushDown(pos, l, r); int mid = (l + r) >> 1;
    if (x <= mid) modify(pos << 1, l, mid, x, y, val);
    if (y > mid) modify(pos << 1 | 1, mid + 1, r, x, y, val);
    pushUp(pos, l, r);
}

int query(int pos, int l, int r, int k){
    pushDown(pos, l, r); if (l == r) return l;
    int mid = (l + r) >> 1;
    if (seg[pos << 1].ans >= k) return query(pos << 1, l, mid, k);
    if (seg[pos << 1].rans + seg[pos << 1 | 1].lans >= k) return (mid - seg[pos << 1].rans + 1);
    else return query(pos << 1 | 1, mid + 1, r, k);
}

int main(){
    int n = read(), m = read();
    build(1, 1, n);
    for (int i = 1; i <= m; ++i){
        int op = read(), x, y;
        if (op == 1){
            x = read();
            if(seg[1].ans >= x){
                int l = query(1, 1, n, x);
                printf("%d\n", l);
                modify(1, 1, n, l, l + x - 1, 1);
            }
            else
                puts("0");
        }
        else{
            x = read(), y = read();
            modify(1, 1, n, x, x + y - 1, 0);
        }
    }
    return 0;
}
```
### 提供一种新的得高分思路
这是我发这篇题解的目的，我们看到这熟悉的区间推平操作，很容易就想到了珂朵莉树，也就是我一开始的打法，但是由于数据的原因珂树T了，伤心.jpg。  
我们考虑珂朵莉树的查询，显然我们只需要更改一下查询即可
```cpp
int query(int k){
    int l = 1, cnt = 0;
    for (set<Node>::iterator it = st.begin(); it != st.end(); ++it){
        if (it->val == 1){
            l = it->r + 1;
            cnt = 0;
        }
        else{
            cnt += it->r - it->l + 1;
            if (cnt >= k) return l;
        }
    }
    return -1;
}
```
我们考虑把连在一起的块的值为零的区间的长度加起来，取第一个满足条件的端点，然后就珂以做出来啦。
### 可怜的92分代码
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

//build
struct Node{
    int l, r;
    mutable bool val;
    Node(int a = -1, int b = -1, int c = 0){
        l = a, r = b, val = c;
    }
    bool operator < (const Node &a) const{
        return l < a.l;
    }
};

set<Node> st;

//modify
set<Node>::iterator split(int pos){
    set<Node>::iterator it = st.lower_bound(Node(pos));
    if (it != st.end() && it->l == pos) return it;
    --it; Node tmp = *it; st.erase(it);
    st.insert(Node(tmp.l, pos - 1, tmp.val));
    return st.insert(Node(pos, tmp.r, tmp.val)).first; //first return iterator
}

void assign(int l, int r, bool val){
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    st.erase(itl, itr);
    st.insert((Node){l, r, val});
}

//query
int query(int k){
    int l = 1, cnt = 0;
    for (set<Node>::iterator it = st.begin(); it != st.end(); ++it){
        if (it->val == 1){
            l = it->r + 1;
            cnt = 0;
        }
        else{
            cnt += it->r - it->l + 1;
            if (cnt >= k) return l;
        }
    }
    return -1;
}

int main(){
    int n = read(), m = read(); st.insert((Node){1, n, 0});
    while (m--){
        int op = read();
        if (op == 1){
            int x = read(), pos = query(x);
            if (pos == -1) puts("0");
            else{
                printf("%d\n", pos);
                assign(pos, pos + x - 1, 1);
            }
        }
        else if (op == 2){
            int x = read(), y = read();
            assign(x, x + y - 1, 0);
        }
    }
    return 0;
}
```

---

## 作者：Unaccepted (赞：2)

Blog地址:[蒟蒻的Blog](https://www.luogu.org/blog/zgj-bloom)

前几天在同学的协助下开通了洛谷博客，但一直没有想好第一篇写什么

在上午~~**用实力**~~AK（**手动滑稽**）之后，下午遇到了一道让我崩溃的题

由于我显示对它耽误了我一下午时间而产生的的痛恨——就它了！

在经过上面的感慨之后，以下才是正文


这道题以前做过一道类似的，所以了解一些线段树区间处理的~~**套路**~~方法

这道题可以维护区间最长连续0的个数，~~**而根据套路**~~，这样做需要维护三个值

分别是

1. $lans$:一个区间从左端开始最长连续0的个数

2. $rans$:一个区间从右端开始最长连续0的个数

3. $ans$:一个区间内最长连续0的个数

然后就可以进行区间合并了

但查找时，我们找的并不是最长连续0，而是长度为x的区间

那么如果 最长连续0个数$> x$ 那么这个区间就是合法的

我们想一想，如果我们枚举合法区间的话，一定是从 合法区间左端点是大区间的左端点  --->  合法区间在大区间里面  --->  合法区间右端点是大区间的右端点  这样枚举

那么因为我们已经维护了最长连续0，那么就可以把每一步的最优值直接取出

那么将这三个枚举步骤直接按顺序执行就行了

查询具体可以这样

① 如果区间最长连续0都没有$x$长，那么这个区间一定不可以，返回0

② 如果左区间最长连续0的个数$> x$，那么直接选取左区间的那个区间即可

③ 因为左区间的$rans$和右区间的$lans$也是连续的（画个区间图就能明白），所以如果它们两个相加 $rans[lson]+lans[rson]> x$ 的话，就相当于合法区间在在左区间和右区间里面了，也是合法的

④实在没有办法，就只能看从右区间的最长连续0是否合法了

看不懂的 ---> 看代码

```cpp
// 码风被很多人说奇怪，凑活看吧 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson (k*2)
#define rson (k*2+1) 
#define mid ((l+r)/2)
#define N 50010
using namespace std;
int n,m;
int ans[N*8],lans[N*8],rans[N*8],tag[N*8];
void build(int k,int l,int r)
{
	ans[k]=lans[k]=rans[k]=r-l+1;// 开始时区间全是0，有r-l+1个 
	tag[k]=-1;
	if(l==r) return;
	build(lson,l,mid);
	build(rson,mid+1,r);
	return;
}
void pushup(int k,int l,int r)
{
	ans[k]=max(rans[lson]+lans[rson],max(ans[lson],ans[rson]));
	if(lans[lson]==mid-l+1) lans[k]=lans[lson]+lans[rson];//这里WA过一次 
	else lans[k]=lans[lson];
	if(rans[rson]==r-mid) rans[k]=rans[rson]+rans[lson];
	else rans[k]=rans[rson];
	return;
}
void pushdown(int k,int l,int r)
{
	if(tag[k]==-1) return;
	ans[lson]=(mid-l+1)*tag[k];
	lans[lson]=(mid-l+1)*tag[k];
	rans[lson]=(mid-l+1)*tag[k];
	tag[lson]=tag[k];
	ans[rson]=(r-mid)*tag[k];
	lans[rson]=(r-mid)*tag[k];
	rans[rson]=(r-mid)*tag[k];
	tag[rson]=tag[k];
	tag[k]=-1;// 下传后把大区间延迟标记清掉 
	return;
}
int getans(int k,int l,int r,int x)
{
	pushdown(k,l,r);
	if(ans[k]<x) return 0;
	if(r-l+1==x) return l; 
	if(ans[lson]>=x) return getans(lson,l,mid,x);//合法区间在左区间里    
	if(rans[lson]+lans[rson]>=x) return mid-rans[lson]+1;//合法区间被分成两半 
	return getans(rson,mid+1,r,x);//合法区间在右区间里 
}
void change(int k,int l,int r,int lx,int rx,int x)
{
	pushdown(k,l,r);
	if(lx<=l && r<=rx)
	{
		ans[k]=(r-l+1)*x;
		lans[k]=(r-l+1)*x;
		rans[k]=(r-l+1)*x;
		tag[k]=x;
		return;
	}
	if(lx<=mid) change(lson,l,mid,lx,rx,x);
	if(rx>mid) change(rson,mid+1,r,lx,rx,x);
	pushup(k,l,r);
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);//建树 
	for(int i=1;i<=m;i++)
	{
		int cmd;
		scanf("%d",&cmd);
		if(cmd==1)
		{
			int l,len;
			scanf("%d",&len);
			if(len>ans[1])
			{
				printf("0\n");
				continue;
			}
			l=getans(1,1,n,len);//题目询问最往左的合法区间左端点值 
			printf("%d\n",l);
			change(1,1,n,l,l+len-1,0);//订房后把那些房间占上 
		}
		else
		{
			int l,len;
			scanf("%d%d",&l,&len);
			change(1,1,n,l,l+len-1,1);//退房后把那些房间让出来 
			
		}
	}
	return 0;
}
```

蒟蒻的第一篇题解，不太熟悉洛谷的编辑器，不喜勿喷，希望能对大家的OI之路有所帮助。

---

## 作者：McGrady (赞：2)

没有pascal代码啊，来一发。

这道题是经典的线段树问题，用线段树维护区间最长连续0的长度，同时记录区间左起最长连续0长度和右起最长连续0长度就可以实现区间信息的合并。

```cpp
program rrr(input,output);
type
  treetype=record
     l,r,lmax,rmax,max,c:longint;    //l是区间左端点编号，r是区间右端点编号，lmax是区间左起最长连续0长度，rmax是区间右起最长连续0长度，max是区间最长连续0长度
  end;
var
  a:array[0..200020]of treetype;
  n,m,i,opt,x,y:longint;
function max(a,b:longint):longint;
begin
   if a>b then exit(a) else exit(b);
end;
procedure build(k,l,r:longint);
var
  mid,t:longint;
begin
   t:=r-l+1;
   a[k].l:=l;a[k].r:=r;a[k].max:=t;a[k].lmax:=t;a[k].rmax:=t;a[k].c:=-1;
   if l=r then exit;
   mid:=(l+r)>>1;
   build(k+k,l,mid);
   build(k+k+1,mid+1,r);
end;
procedure pushdown(k:longint);
var
  i,t:longint;
begin
   if a[k].c=-1 then exit;
   if a[k].l=a[k].r then begin a[k].c:=-1;exit; end;
   i:=k+k;
   if a[k].c=0 then
      begin
         t:=a[i].r-a[i].l+1;
         a[i].lmax:=t;a[i].rmax:=t;a[i].max:=t;a[i].c:=0;
         t:=a[i+1].r-a[i+1].l+1;
         a[i+1].lmax:=t;a[i+1].rmax:=t;a[i+1].max:=t;a[i+1].c:=0;
       end
   else
      begin
         a[i].lmax:=0;a[i].rmax:=0;a[i].max:=0;a[i].c:=1;
         a[i+1].lmax:=0;a[i+1].rmax:=0;a[i+1].max:=0;a[i+1].c:=1;
      end;
   a[k].c:=-1;
end;
function ask(k:longint):longint;
var
  i:longint;
begin
   pushdown(k);
   i:=k+k;
   if a[i].max>=x then exit(ask(i))
   else if a[i].rmax+a[i+1].lmax>=x then exit(a[i].r-a[i].rmax+1)
   else exit(ask(i+1));
end;
procedure change1(k,x,y:longint);
var
  mid,i:longint;
begin
   pushdown(k);
   if (x<=a[k].l) and (a[k].r<=y) then
      begin a[k].lmax:=0;a[k].rmax:=0;a[k].max:=0;a[k].c:=1;exit; end;
   mid:=(a[k].l+a[k].r)>>1;i:=k+k;
   if x<=mid then change1(i,x,y);
   if mid<y then change1(i+1,x,y);
   if a[i].lmax=a[i].r-a[i].l+1 then a[k].lmax:=a[i].lmax+a[i+1].lmax else a[k].lmax:=a[i].lmax;   //这里要注意，刚开始容易直接写a[k].lmax:=a[i].lmax
   if a[i+1].rmax=a[i+1].r-a[i+1].l+1 then a[k].rmax:=a[i].rmax+a[i+1].rmax else a[k].rmax:=a[i+1].rmax;   //这里也一样
   a[k].max:=max(max(a[i].max,a[i+1].max),a[i].rmax+a[i+1].lmax);
end;
procedure change0(k,x,y:longint);
var
  mid,t,i:longint;
begin
   pushdown(k);
   if (x<=a[k].l) and (a[k].r<=y) then
      begin t:=a[k].r-a[k].l+1;a[k].lmax:=t;a[k].rmax:=t;a[k].max:=t;a[k].c:=0;exit; end;
   mid:=(a[k].l+a[k].r)>>1;i:=k+k;
   if x<=mid then change0(i,x,y);
   if mid<y then change0(i+1,x,y);
   if a[i].lmax=a[i].r-a[i].l+1 then a[k].lmax:=a[i].lmax+a[i+1].lmax else a[k].lmax:=a[i].lmax;   //还有这儿
   if a[i+1].rmax=a[i+1].r-a[i+1].l+1 then a[k].rmax:=a[i].rmax+a[i+1].rmax else a[k].rmax:=a[i+1].rmax;   //和这儿
   a[k].max:=max(max(a[i].max,a[i+1].max),a[i].rmax+a[i+1].lmax);
end;
begin
   //assign(input,'r.in');assign(output,'r.out');reset(input);rewrite(output);
   readln(n,m);
   build(1,1,n);
   for i:=1 to m do
      begin
         read(opt);
         if opt=1 then
            begin
               readln(x);
               if a[1].max<x then writeln(0)
               else begin y:=ask(1);writeln(y);change1(1,y,y+x-1); end;
            end
         else begin readln(x,y);change0(1,x,x+y-1); end;
      end;
   //close(input);close(output);
end.
```

---

## 作者：Rainybunny (赞：1)

( 本文也作$8.16$考试题解, 附[题目链接](https://www.luogu.org/problem/P2894). )  
咱们考试终于送点水分了$x$.

------------
首先, 可以轻易看出本题的算法——线段树.  
我们维护三个数值: 以区间左端点开始的空房长度; 以区间右端点开始的空房长度; 整个区间最长的空房长度.  
对于区间合并, 为了维护大区间的最长的空房长度, 我们可以对其分类讨论:  
1. 最长空房区间在左儿子.  

2. 最长空房区间在右儿子.  

3. 最长空房区间跨越左右儿子.  

以上三种情况, 取最大值即可.  
特别注意, 在区间合并时, 如果出现某个儿子全是空房, 以区间端点开始的空房长度也会贯穿个儿子.  
如何查询? 我们分为三步:  
1. 查询是否存在答案.  
很轻松, 访问根节点即可.  

2. 找到最靠左的答案位置.  
递归查找. 在进入递归时检查该结点区间内是否存在答案, 在以上文1.2.3.的顺序分别检查最长空房长度的三种情况. 一旦找到解, 立即结束查询.  

3. 标记入住.  
( 不会去做板题吧. )  

上代码, $class$注意避雷, 风骚码风注意避雷.
```cpp
#include <cstdio>
#include <iostream>

#define Int register int

using namespace std;

inline int rint () {
	Int x = 0, f = 1; register char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () ) f = s == '-' ? -f : f;
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x * f;
}

const int MAXN = 50000;
int n, m, Ans;

class Segment_Tree {
private:
	struct Node {
		int l, r, Lmax, Rmax, Secmax, Lazy;
	} *Tree;
public:
	inline int CompSecmax () { return Tree[1].Secmax; }
	inline void Build ( const int i, const int l, const int r, const int SizeofTree = 0 ) {
		if ( i == 1 ) Tree = new Node[SizeofTree] ();
		Tree[i] = { l, r, r - l + 1, r - l + 1, r - l + 1 };
		if ( l == r ) return ;
		int mid = l + r >> 1;
		this -> Build ( i << 1, l, mid );
		this -> Build ( i << 1 | 1, mid + 1, r );
	}
	inline void Spread ( const int i ) {
		if ( ! Tree[i].Lazy ) return ;
		if ( ~ Tree[i].Lazy ) {
			Tree[i << 1].Lmax = Tree[i << 1].Rmax = Tree[i << 1].Secmax = Tree[i << 1].r - Tree[i << 1].l + 1;
			Tree[i << 1 | 1].Lmax = Tree[i << 1 | 1].Rmax = Tree[i << 1 | 1].Secmax = Tree[i << 1 | 1].r - Tree[i << 1 | 1].l + 1;
		} else {
			Tree[i << 1].Lmax = Tree[i << 1].Rmax = Tree[i << 1].Secmax = 0;
			Tree[i << 1 | 1].Lmax = Tree[i << 1 | 1].Rmax = Tree[i << 1 | 1].Secmax = 0;
		}
		Tree[i << 1].Lazy = Tree[i << 1 | 1].Lazy = Tree[i].Lazy;
		Tree[i].Lazy = 0;
	}
	inline void Push_up ( const int i ) {
		Tree[i].Lmax = Tree[i << 1].Lmax, Tree[i].Rmax = Tree[i << 1 | 1].Rmax;
		Tree[i].Secmax = max ( Tree[i << 1].Secmax, Tree[i << 1 | 1].Secmax ); // 不跨界
		Tree[i].Secmax = max ( Tree[i].Secmax, Tree[i << 1].Rmax + Tree[i << 1 | 1].Lmax ); // 跨界
		if ( Tree[i << 1].Lmax == Tree[i << 1].r - Tree[i << 1].l + 1 ) { // 贯通 
			Tree[i].Lmax += Tree[i << 1 | 1].Lmax;
		}
		if ( Tree[i << 1 | 1].Rmax == Tree[i << 1 | 1].r - Tree[i << 1 | 1].l + 1 ) {
			Tree[i].Rmax += Tree[i << 1].Rmax;
		}
	}
	inline void Check_out ( const int i, const int l, const int r ) {
		if ( r < Tree[i].l || Tree[i].r < l ) return ;
		if ( l <= Tree[i].l && Tree[i].r <= r ) {
			Tree[i].Lmax = Tree[i].Rmax = Tree[i].Secmax = Tree[i].r - Tree[i].l + 1;
			Tree[i].Lazy = 1;
			return ;
		}
		this -> Spread ( i );
		this -> Check_out ( i << 1, l, r );
		this -> Check_out ( i << 1 | 1, l, r );
		this -> Push_up ( i );
	}
	inline int Check_in ( const int i, const int d ) {
		if ( Tree[i].Secmax < d ) return 0;
		if ( Tree[i].l == Tree[i].r ) {
			return Tree[i].l;
		}
		this -> Spread ( i );
		int lret = Check_in ( i << 1, d );
		if ( lret ) return lret;
		if ( Tree[i << 1].Rmax + Tree[i << 1 | 1].Lmax >= d ) return Tree[i << 1].r - Tree[i << 1].Rmax + 1;
		return Check_in ( i << 1 | 1, d );
	}
	inline void Cover ( const int i, const int l, const int r ) {
		if ( r < Tree[i].l || Tree[i].r < l ) return ;
		if ( l <= Tree[i].l && Tree[i].r <= r ) {
			Tree[i].Lmax = Tree[i].Rmax = Tree[i].Secmax = 0;
			Tree[i].Lazy = -1;
			return ;
		}
		this -> Spread ( i );
		this -> Cover ( i << 1, l, r );
		this -> Cover ( i << 1 | 1, l, r );
		this -> Push_up ( i );
	}
} SegTree;

inline void Work () {
	n = rint (), m = rint ();
	SegTree.Build ( 1, 1, n, n << 2 );
	while ( m -- ) {
		static int Opr, x, d;
		scanf ( "%d", &Opr );
		if ( Opr == 1 ) {
			scanf ( "%d", &d );
			if ( SegTree.CompSecmax () < d ) {
				puts ( "0" );
			} else {
				int l = SegTree.Check_in ( 1, d );
				printf ( "%d\n", l );
				SegTree.Cover ( 1, l, l + d - 1 );
			}
		} else {
			scanf ( "%d %d", &x, &d );
			SegTree.Check_out ( 1, x, x + d - 1 );
		}
	}
}

int main () {
//	freopen ( "hotel.in", "r", stdin );
//	freopen ( "hotel.out", "w", stdout );
	Work ();
	return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2894)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;线段树入门题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;线段树的区间里面维护三个东西——从左端点开始的最长的一段空房间的长度；从右端点开始的最长的一段空房间的长度；该区间内最长的一段空房间的长度。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;修改就不说了；前两个信息可以用来合并出第三个信息；有了第三个信息就可以用来查询了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;查询就是......暴力遍历这棵树。记得用第三个信息来剪枝。  
# 代码
```cpp
#include <cstdio>
#define len( a ) ( segTree[a].r - segTree[a].l + 1 )
//#define __DEBUG

const int MAXN = 50005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct segmentTreeNode
{
	int l, r;
	int lEmp, rEmp, emp;
	int tag;
}segTree[MAXN << 2];

int N, M;

void upt( const int now )
{
	if( segTree[now].l == segTree[now].r ) return;
	segTree[now].lEmp = segTree[now << 1].lEmp == len( now << 1 ) ? segTree[now << 1 | 1].lEmp + len( now << 1 ) : segTree[now << 1].lEmp;
	segTree[now].rEmp = segTree[now << 1 | 1].rEmp == len( now << 1 | 1 ) ? segTree[now << 1].rEmp + len( now << 1 | 1 ) : segTree[now << 1 | 1].rEmp;
	segTree[now].emp = MAX( MAX( segTree[now << 1].emp, segTree[now << 1 | 1].emp ), segTree[now << 1].rEmp + segTree[now << 1 | 1].lEmp );
}

void normalize( const int now )
{
	if( segTree[now].l == segTree[now].r ) return;
	if( segTree[now].tag )
	{
		if( segTree[now].tag > 0 )
		{
			segTree[now << 1].lEmp = segTree[now << 1].rEmp = segTree[now << 1].emp = 0;
			segTree[now << 1 | 1].lEmp = segTree[now << 1 | 1].rEmp = segTree[now << 1 | 1].emp = 0;
		}
		else
		{
			segTree[now << 1].lEmp = segTree[now << 1].rEmp = segTree[now << 1].emp = len( now << 1 );
			segTree[now << 1 | 1].lEmp = segTree[now << 1 | 1].rEmp = segTree[now << 1 | 1].emp = len( now << 1 | 1 );
		}
		segTree[now << 1].tag = segTree[now << 1 | 1].tag = segTree[now].tag;
		segTree[now].tag = 0;
	}
}

void build( const int now, const int left, const int right )
{
	segTree[now].l = left, segTree[now].r = right;
	if( left == right )
	{
		segTree[now].lEmp = segTree[now].rEmp = segTree[now].emp = 1;
		return;
	}
	build( now << 1, left, ( left + right ) >> 1 );
	build( now << 1 | 1, ( ( left + right ) >> 1 ) + 1, right );
	upt( now );
}

void update( const int now, const int segL, const int segR )
{
	#ifdef __DEBUG
	segmentTreeNode &node1 = segTree[now];
	#endif
	if( segR < segTree[now].l || segTree[now].r < segL ) return;
	if( segL <= segTree[now].l && segTree[now].r <= segR )
	{
		segTree[now].lEmp = segTree[now].rEmp = segTree[now].emp = 0;
		segTree[now].tag = 1;
		return;
	}
	if( segTree[now].l == segTree[now].r ) return;
	normalize( now );
	update( now << 1, segL, segR );
	update( now << 1 | 1, segL, segR );
	upt( now );
}

void clean( const int now, const int segL, const int segR )
{
	#ifdef __DEBUG
	segmentTreeNode &node2 = segTree[now];
	#endif
	if( segR < segTree[now].l || segTree[now].r < segL ) return;
	if( segL <= segTree[now].l && segTree[now].r <= segR )
	{
		segTree[now].lEmp = segTree[now].rEmp = segTree[now].emp = len( now );
		segTree[now].tag = -1;
		return;
	}
	if( segTree[now].l == segTree[now].r ) return;
	normalize( now );
	clean( now << 1, segL, segR );
	clean( now << 1 | 1, segL, segR );
	upt( now );
}

int query( const int now, const int length )
{
	#ifdef __DEBUG
	segmentTreeNode &node3 = segTree[now];
	#endif
	if( segTree[now].emp < length ) return 0;
	if( segTree[now].l == segTree[now].r ) return segTree[now].l;
	int val = 0;
	normalize( now );
	val = query( now << 1, length );
	if( val ) return val;
	if( segTree[now << 1].rEmp + segTree[now << 1 | 1].lEmp >= length )
		return segTree[now << 1].r - segTree[now << 1].rEmp + 1;
	return query( now << 1 | 1, length );
}

int main()
{
//	freopen( "hotel.in", "r", stdin );
//	freopen( "hotel.out", "w", stdout );
	int op, x, d, res;
	read( N ), read( M );
	build( 1, 1, N );
	while( M -- )
	{
		read( op );
		if( op & 1 )
		{
			read( d );
			res = query( 1, d );
			write( res ), putchar( '\n' );
			if( res ) update( 1, res, res + d - 1 );
		}
		else
		{
			read( x ), read( d );
			clean( 1, x, x + d - 1 );
		}
	}
	return 0;
}
```

---

## 作者：jacky567 (赞：1)

首先，我们先将题目简化一下，这道题需要我们实现$2$个操作：

1、订房:相当于查询是否有连续$D$个位置是空的，如果有输出最左端点

2、退房:相当于将$X$到$X+D-1$这段位置置为空

因此，我们很容易看出，这是一道支持区间查询和区间修改的线段树题。

要解决这个问题，每个节点都需要维护$4$个变量：

1、$lm$从左数最多有多少个连续的$0$

2、$rm$从右数最多有多少个连续的$0$

3、$m$整个区间最多有多少个连续的$0$

4、$sum$区间的长度

（读者：什么！？不用延迟标记（俗称$lazy$标志）吗？）

（我：...延迟标记还要写在这里吗？区间修改不是肯定需要吗?）

一开始，因为整个区间都是空的，所以我们将这些的值都赋为区间的长度。

当遇到一个查询的时候，就从根节点开始查询，为了保证最后得到的答案一定是靠左的，所以我们都先判断左边的连续$0$的个数是否大于我们需要的$D$，如果是就直接返回左端点，然后，用同样的方法判断判断中间和右边的部分。

当遇到修改的时候，就正常修改，只是在最后上传标志的时候会稍微复杂一点点，有几种情况需要判断。

最后，因为我们涉及了区间修改，所以每做一步操作都要下放标志
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#define l(i) t[i].l
#define r(i) t[i].r
#define m(i) t[i].m
#define lm(i) t[i].lm
#define rm(i) t[i].rm
#define sum(i) t[i].sum
#define add(i) t[i].add
using namespace std;
struct ppap 
{
	int l,r,m,lm,rm,sum,add;
}t[200010];
int n,m;
int pushup(int p)//上传标志
{
  if(sum(2*p)==m(2*p)) lm(p)=sum(2*p)+lm(2*p+1);
  else lm(p)=lm(2*p);
  if(sum(2*p+1)==m(2*p+1)) rm(p)=sum(2*p+1)+rm(2*p);
  else rm(p)=rm(2*p+1);
  m(p)=max(m(2*p),m(2*p+1));
  m(p)=max(m(p),rm(2*p)+lm(2*p+1));
}
int pushdown(int p)//下放标志
{
  int add=add(p);
	add(p)=0;
  if(l(p)==r(p)) return 0;
  if(add==1){
    lm(2*p)=rm(2*p)=m(2*p)=sum(2*p);
    lm(2*p+1)=rm(2*p+1)=m(2*p+1)=sum(2*p+1);
    add(2*p)=add(2*p+1)=1;
  }
  else if(add==2){
    lm(2*p)=rm(2*p)=m(2*p)=0;
    lm(2*p+1)=rm(2*p+1)=m(2*p+1)=0;
    add(2*p)=add(2*p+1)=2;
  }
}
int build(int p,int l,int r)//建树 
{
  l(p)=l;
	r(p)=r;
  lm(p)=rm(p)=m(p)=sum(p)=r-l+1;
  if(l==r) return 0;
  int mid=(l+r)>>1;
  build(2*p,l,mid);
	build(2*p+1,mid+1,r);
}
int change(int p,int x,int y,int f)//区间修改 
{
  pushdown(p);
  int l=l(p),r=r(p);
  if(l==x&&y==r){
    if(f==1) lm(p)=rm(p)=m(p)=sum(p);
    else lm(p)=rm(p)=m(p)=0;
    add(p)=f;
    return 0;
  }
  int mid=(l+r)>>1;
  if(mid>=y) change(2*p,x,y,f);
  else if(mid<x) change(2*p+1,x,y,f);
  else{
    change(2*p,x,mid,f);
    change(2*p+1,mid+1,y,f);
  }
  pushup(p);
}
int ask(int p,int x)//区间查询 
{
  pushdown(p);
  int l=l(p),r=r(p),mid=(l+r)>>1;
  if(l==r) return l;
  if(m(2*p)>=x) return ask(2*p,x);
  if(rm(2*p)+lm(2*p+1)>=x) return mid-rm(2*p)+1;
  return ask(2*p+1,x);
} 
int main()
{
  scanf("%d%d",&n,&m);
  build(1,1,n);
  for(int i=1;i<=m;i++){
    int f,x,y;
    scanf("%d",&f);
    if(f==1){
      scanf("%d",&x);
      if(t[1].m<x) cout<<0<<endl;
      else{
				int p=ask(1,x);
				cout<<p<<endl;
				change(1,p,p+x-1,2);
			}
    }
    else{
			scanf("%d%d",&x,&y);
			change(1,x,x+y-1,1);
		}
  }
}
```

---

## 作者：AC_Automation (赞：1)

#### 这道题是道线段树的好题，值得一做

为什么说是道线段树好题呢，因为它不拘于线段树的模板，在查询部分非常~~毒瘤~~有趣。

回到正题，看到区间操作，容易想到线段树维护。

和维护区间最大子段和相似，存储最大连续空房，最大前缀空房和最大后缀空房。

还有一点：$tag$有三种值，代表区间退房（$2$），区间入住（$1$），没有$tag$（$0$）

值得注意的是$pushup$操作和$pushdown$操作（其他和普通线段树一样）

$code:$（$pushup$操作和$pushdown$操作）
```
void up(int root){
	a[root].lm=a[ls].lm;
	a[root].rm=a[rs].rm;
	a[root].sum=max(max(a[ls].sum,a[rs].sum),a[ls].rm+a[rs].lm);//sum只有三种可能：只包含左孩子，横跨左右孩子，只包含右孩子
	if(a[ls].sum==a[ls].len)
		a[root].lm=a[ls].sum+a[rs].lm;
	if(a[rs].sum==a[rs].len)
		a[root].rm=a[rs].sum+a[ls].rm;//最大前缀空房和最大后缀空房
	return;
}
void pd(int root){
	if(!a[root].tag)return;
	if(a[root].tag==1){
		a[ls].sum=0;a[ls].lm=0;a[ls].rm=0;a[ls].tag=1;
		a[rs].sum=0;a[rs].lm=0;a[rs].rm=0;a[rs].tag=1;//区间入住，全置0
	}
	else{
		a[ls].sum=a[ls].len;a[ls].lm=a[ls].len;
		a[ls].rm=a[ls].len;a[ls].tag=2;
		a[rs].sum=a[rs].len;a[rs].lm=a[rs].len;
		a[rs].rm=a[rs].len;a[rs].tag=2;//区间退房，全置len
	}
	a[root].tag=0;
}
```
还有一个重点（也是个人认为的本体最难点）：$query$怎么写？

其实这里的$query$已经不太像线段树的$query$了

对于每次查询到的节点，如果左孩子有足够空房就递归到左孩子，否则横跨两个孩子，然后再递归右孩子。

$code:$
```
int query(int root,int l,int r,int k){
	pd(root);
	if(a[root].sum<k)return 0;
	if(a[ls].sum>=k)return query(ls,l,mid,k);//左孩子
	if(a[ls].rm+a[rs].lm>=k)return mid-a[ls].rm+1;//横跨
	if(a[rs].sum>=k)return query(rs,mid+1,r,k);//右孩子
}
```
所有的难点都攻克了，除此以外，还要注意：
+ 别直接用$cin$
+ 记得$pushdown$和$pushup$
+ ~~别把$ls$和$rs$弄混~~

最后就是完整代码了~
```
#include<iostream>
using namespace std;
#define ls (root<<1)
#define rs (root<<1|1)
#define mid ((l+r)>>1)
struct point{
	int sum,lm,rm,len,tag;
} a[400005];
void up(int root){
	a[root].lm=a[ls].lm;
	a[root].rm=a[rs].rm;
	a[root].sum=max(max(a[ls].sum,a[rs].sum),a[ls].rm+a[rs].lm);//sum只有三种可能：只包含左孩子，横跨左右孩子，只包含右孩子
	if(a[ls].sum==a[ls].len)
		a[root].lm=a[ls].sum+a[rs].lm;
	if(a[rs].sum==a[rs].len)
		a[root].rm=a[rs].sum+a[ls].rm;//最大前缀空房和最大后缀空房
	return;
}
void pd(int root){
	if(!a[root].tag)return;
	if(a[root].tag==1){
		a[ls].sum=0;a[ls].lm=0;a[ls].rm=0;a[ls].tag=1;
		a[rs].sum=0;a[rs].lm=0;a[rs].rm=0;a[rs].tag=1;//区间入住，全置0
	}
	else{
		a[ls].sum=a[ls].len;a[ls].lm=a[ls].len;
		a[ls].rm=a[ls].len;a[ls].tag=2;
		a[rs].sum=a[rs].len;a[rs].lm=a[rs].len;
		a[rs].rm=a[rs].len;a[rs].tag=2;//区间退房，全置len
	}
	a[root].tag=0;
}
void build(int root,int l,int r){
	a[root].len=r-l+1;a[root].sum=a[root].len;
	a[root].lm=a[root].len;a[root].rm=a[root].len;//简单初始化
	a[root].tag=0;
	if(l==r)return;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void change1(int root,int l,int r,int ql,int qr){//入住 
	pd(root);
	if(ql<=l&&qr>=r){//打tag
		a[root].tag=1;
		a[root].sum=0;a[root].lm=0;a[root].rm=0;
		return;
	}
	if(ql<=mid)change1(ls,l,mid,ql,qr);//递归左孩子
	if(qr>mid)change1(rs,mid+1,r,ql,qr);//递归右孩子
	up(root);
	return;
}
void change2(int root,int l,int r,int ql,int qr){//退房 
	pd(root);
	if(ql<=l&&qr>=r){//打tag
		a[root].sum=a[root].len;a[root].lm=a[root].len;
		a[root].rm=a[root].len;a[root].tag=2;
		return;
	}
	if(ql<=mid)change2(ls,l,mid,ql,qr);//递归左孩子
	if(qr>mid)change2(rs,mid+1,r,ql,qr);//递归右孩子
	up(root);
	return;
}
int query(int root,int l,int r,int k){
	pd(root);
	if(a[root].sum<k)return 0;
	if(a[ls].sum>=k)return query(ls,l,mid,k);//左孩子
	if(a[ls].rm+a[rs].lm>=k)return mid-a[ls].rm+1;//横跨
	if(a[rs].sum>=k)return query(rs,mid+1,r,k);//右孩子
}
int mian()
{
	ios::sync_with_stdio(false);cin.tie(0);
	int n,m,opt,x,y,t;
	cin>>n>>m;
	build(1,1,n);
	for(int i=0;i<m;i++){
		cin>>opt;
		if(opt==1){
			cin>>x;
			t=query(1,1,n,x);
			cout<<t<<endl;
			if(t)change1(1,1,n,t,t+x-1);
		}
		else{
			cin>>x>>y;
			change2(1,1,n,x,x+y-1);
		}
	}
	return 0;
}

```
千万别$ctrl C+V$，后果自负

---

## 作者：aiyougege (赞：1)

### bzoj 1593: [Usaco2008 Feb]Hotel 旅馆
#### Soluion
　　sb线段树题.写起来极其麻烦.整整调了一上午, 下午10分钟就找到错误了.原来是**标记没有清空**, 怪不得我手码了一棵没标记的就行了, 我果然还是太弱了.~~每次写线段树都会被按在地上摩擦的感觉真是不爽.~~

　　具体做法就是普通的线段树维护**区间最长空闲连续区间**, 因为一段区间可以由两个区间合并而来, 所以两个**连续的线段树节点**合并不仅需要维护各自的最长连续长度, 还需要维护区间的左侧开始最长长度, 右侧开始最长长度, 一个大区间$[l,r]$的两个子区间$[l,mid],[mid+1,r]$其左侧开始最长长度, 右侧开始最长长度合并起来可能会得到$[l,r]$的最长长度.

　　哦, 对了, 我线段树写**指针**.因此可能是题解中唯一一个指针.下面具体介绍一下各个部分的作用.我稍微压压行, 不压行太长了.

- 线段树节点的结构体:
```c++
struct Node{
    bool vis;//1表示房间全部可用
    int tag;//标记, 1表示房间全部被占用,2表示房间全部被释放, 0表示什么都没有发生.
    int L,R;//区间左端点, 右端点
    int l,r,m,p;//左,右端点开始的长度, 最长长度的开始点.
    Node *ls,*rs;//左右儿子节点.
    void Merge(){//从两个字节点合并而来
        vis=(ls->vis&rs->vis);l=ls->l;r=rs->r;
        if(ls->vis)l+=rs->l;if(rs->vis)r+=ls->r;
        if(ls->m>rs->m)m=ls->m,p=ls->p;else m=rs->m,p=rs->p;
        if(ls->r+rs->l>m)m=ls->r+rs->l,p=ls->R-ls->r+1;
    }
    void clear(){vis=l=r=m=p=false;}//设为全部被占用
    void all(){vis=true,p=L,l=r=m=R-L+1;}//设为全部被释放
    void TurnUp(){if(tag==1)clear();if(tag==2)all();}//根据tag改变状态
    void print(){printf("%d %d %d %d\n",l,r,m,p);}//打印状态
    void PushDown(){if(!tag)return ;ls->tag=tag,rs->tag=tag;ls->TurnUp(),rs->TurnUp();tag=0;}
}c[N<<2];//提前开好内存, 动态分配贼慢
```
- 分配节点内存
```c++
Node *new_Node(){
static int cnt=0;
return &c[++cnt];
}//static 为c++语法, 从ddd那里学的.函数返回的是指针
```
- 线段树
```c++
namespace SegmentTree{
    Node *root;int n;//根节点和n
    void build(Node *&now,int l,int r){
        now->L=l,now->R=r;if(l==r){now->all();return ;}//设为全部不被占用
        int mid=(l+r)>>1;now->ls=new_Node(),now->rs=new_Node();//需要给子节点分配内存
        build(now->ls,l,mid);build(now->rs,mid+1,r);now->Merge();//合并两个子节点
    }
    void init(){root=new_Node();build(root,1,n);}//初始化, 需要分配根节点内存
    void Modify(Node *&now,int l,int r,int L,int R,int G){//修改, G为标记,1占用,2释放
        if(l>=L&&r<=R){now->tag=G;now->TurnUp();return;}//和普通线段树一毛一样
        now->PushDown();
        int mid=(l+r)>>1;
        if(L<=mid)Modify(now->ls,l,mid,L,R,G);
        if(R>mid)Modify(now->rs,mid+1,r,L,R,G);
        now->Merge();
    }
    int Query(Node *&now,int l,int r,int L){//查询区间大于L的可用房间
        if(l==r)return l;
        now->PushDown();
        if(now->m<L)return 0;
        int mid=(l+r)>>1;
        if(now->ls->m>=L)return Query(now->ls,l,mid,L);//首先考虑左侧区间
        else if(now->ls->r+now->rs->l>=L)
	        return now->ls->R-now->ls->r+1;//考虑部分在左侧部分在右侧的区间
        else return Query(now->rs,mid+1,r,L);//最后考虑完全在右侧的区间
    }
};using namespace SegmentTree;
```
- 主函数
```c++
int main(){
    int m;
    scanf("%d%d",&n,&m);
    init();int a,b,c;
    while(m--){
        scanf("%d%d",&a,&b);
        if(a==1){
            int p=Query(root,1,n,b);
            printf("%d\n",p);
            if(p)Modify(root,1,n,p,p+b-1,1);//记得需要修改啊
        }
        if(a==2){scanf("%d",&c);Modify(root,1,n,b,b+c-1,2);}
    }
    return 0;
}
```

#### Code
100分.
```c++
#include<iostream>
#include<cstdio>
#define N 1000005
using namespace std;

struct Node{
    bool vis;
    int tag;
    int L,R;//区间
    int l,r,m,p;//左,右端点开始的长度, 最长长度的开始点.
    Node *ls,*rs;//左右儿子节点.
    void Merge(){
        vis=(ls->vis&rs->vis);l=ls->l;r=rs->r;
        if(ls->vis)l+=rs->l;if(rs->vis)r+=ls->r;
        if(ls->m>rs->m)m=ls->m,p=ls->p;else m=rs->m,p=rs->p;
        if(ls->r+rs->l>m)m=ls->r+rs->l,p=ls->R-ls->r+1;
    }
    void clear(){vis=l=r=m=p=false;}
    void all(){vis=true,p=L,l=r=m=R-L+1;}
    void TurnUp(){if(tag==1)clear();if(tag==2)all();}
    void print(){printf("%d %d %d %d\n",l,r,m,p);}
    void PushDown(){if(!tag)return ;ls->tag=tag,rs->tag=tag;ls->TurnUp(),rs->TurnUp();tag=0;}
}c[N<<2];
Node *new_Node(){static int cnt=0;return &c[++cnt];}
namespace SegmentTree{
    Node *root;int n;
    void build(Node *&now,int l,int r){
        now->L=l,now->R=r;if(l==r){now->all();return ;}
        int mid=(l+r)>>1;now->ls=new_Node(),now->rs=new_Node();
        build(now->ls,l,mid);build(now->rs,mid+1,r);now->Merge();
    }
    void init(){root=new_Node();build(root,1,n);}
    void Modify(Node *&now,int l,int r,int L,int R,int G){
        if(l>=L&&r<=R){now->tag=G;now->TurnUp();return;}
        now->PushDown();
        int mid=(l+r)>>1;
        if(L<=mid)Modify(now->ls,l,mid,L,R,G);
        if(R>mid)Modify(now->rs,mid+1,r,L,R,G);
        now->Merge();
    }
    int Query(Node *&now,int l,int r,int L){
        if(l==r)return l;
        now->PushDown();
        if(now->m<L)return 0;
        int mid=(l+r)>>1;
        if(now->ls->m>=L)return Query(now->ls,l,mid,L);
        else if(now->ls->r+now->rs->l>=L)return now->ls->R-now->ls->r+1;
        else return Query(now->rs,mid+1,r,L);
    }
};using namespace SegmentTree;

int main(){
    int m;
    scanf("%d%d",&n,&m);
    init();int a,b,c;
    while(m--){
        scanf("%d%d",&a,&b);
        if(a==1){
            int p=Query(root,1,n,b);
            printf("%d\n",p);
            if(p)Modify(root,1,n,p,p+b-1,1);
        }
        if(a==2){scanf("%d",&c);Modify(root,1,n,b,b+c-1,2);}
    }
    return 0;
}
```
没有标记的66分. TLE
````c++
#include<iostream>
#include<cstdio>
#define N 1000005
using namespace std;

struct Node{
    bool vis,flag;
    int L,R;//区间
    int l,r,m,p;//左,右端点开始的长度, 最长长度的开始点.
    Node *ls,*rs;//左右儿子节点.
    void Merge(){
        L=ls->L,R=rs->R;
        vis=(ls->vis&rs->vis);
        l=ls->l;r=rs->r;
        if(ls->vis)l+=rs->l;
        if(rs->vis)r+=ls->r;
        if(ls->m>rs->m)m=ls->m,p=ls->p;
        else m=rs->m,p=rs->p;
        if(ls->r+rs->l>m)m=ls->r+rs->l,p=ls->R-ls->r+1;
    //	print();
    }
    void print(){
        printf("flag:%d l:%d r:%d L:%d R:%d Max:%d Position:%d Vis:%d\n",flag,L,R,l,r,m,p,vis);
    }
    void clear(){
        vis=l=r=m=p=false;
    }
    void all(){
        vis=true,p=L,l=r=m=R-L+1;
    }
    void TurnUp(int G){
        if(G)clear();else all();
    }
}c[N<<2];

Node *new_Node(){
    static int cnt=0;
    return &c[++cnt];
}

namespace SegmentTree{
    Node *root;
    int n;
    void build(Node *now,int l,int r){
        now->L=l,now->R=r;
        if(l==r){now->all();return ;}
        int mid=(l+r)>>1;
        now->ls=new_Node(),now->rs=new_Node();
        build(now->ls,l,mid);build(now->rs,mid+1,r);
        now->Merge();
    }
    void init(){
        root=new_Node();
        build(root,1,n);
    }
    void Modify(Node *now,int l,int r,int L,int R,bool G){
        if(l==r){now->TurnUp(G);return;}
        int mid=(l+r)>>1;
        if(L<=mid)Modify(now->ls,l,mid,L,R,G);
        if(R>mid)Modify(now->rs,mid+1,r,L,R,G);
        now->Merge();
    }
    int Query(Node *now,int l,int r,int L){
        if(l==r)return now->p;
        if(now->m<L)return 0;
        int mid=(l+r)>>1,ans=0;
        if(now->ls->m>=L)ans=Query(now->ls,l,mid,L);
        else if(now->ls->r+now->rs->l>=L)ans=now->ls->R-now->ls->r+1;
        else ans=Query(now->rs,mid+1,r,L);
        return ans;
    }
};using namespace SegmentTree;

int main(){
    int m;
    scanf("%d%d",&n,&m);
    init();int a,b,c;
    while(m--){
        scanf("%d%d",&a,&b);
        if(a==1){
            int p=Query(root,1,n,b);
            printf("%d\n",p);
            if(p)Modify(root,1,n,p,p+b-1,1);
        }
        if(a==2){scanf("%d",&c);Modify(root,1,n,b,b+c-1,0);}
    }
    return 0;
}
```

---

## 作者：巨型方块 (赞：1)

首先感谢一下楼下的题解，这道题我有细节写错了，一直8分，心灰意冷，来看了楼下大神的题解；

哇！！这么繁琐的程序都能AC？？，我的也一定可以！！！

然后我重拾信心，努力检查，就AC了；

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define Ll long long
using namespace std;
struct tree{
    int xx,yy,l,r,m,p;//xx，yy是这个区间的范围，l,r代表这段区间的左右最长连续空位，m就是整段区间的连续空位，p是lazy标记 
}T[500000*8+1];
int n,m,x,y,z,ans;
void clean(int num){//这个显然就是lazy的下传 
    if(T[num].xx==T[num].yy)return;
    if(!T[num].p)return;
    int k=num+num;
    if(T[num].p==1){
        T[k].l=T[k].m=T[k].r=T[k+1].l=T[k+1].m=T[k+1].r=0;
        T[k].p=T[k+1].p=1;
    }else{
        T[k].l=T[k].m=T[k].r=T[k].yy-T[k].xx+1;
        T[k+1].l=T[k+1].m=T[k+1].r=T[k+1].yy-T[k+1].xx+1;
        T[k].p=T[k+1].p=2;
    }
    T[num].p=0;
}
void maketree(int x,int y,int num){
    T[num].xx=x;T[num].yy=y;
    T[num].l=T[num].r=T[num].m=y-x+1;//一开始全空房 
    if(x==y)return;
    int mid=(x+y)>>1;num=num<<1;
    maketree(x,mid  ,num  );
    maketree(mid+1,y,num+1);
}
int find(int x,int num){//找一个长度位x的区间，现搜索到第num个区间 
    clean(num);clean(num*2);clean(num*2+1); 
    if(T[num].l>=x)return T[num].xx;//如果这个区间的左连续区间足够，那么直接住在最左边吧 
    if(T[num*2].m>=x)return find(x,num*2);//如果左半段区间的最大值满足x，说明可以住在左子儿子的区间 
    if(T[num*2].r+T[num*2+1].l>=x)return T[num*2].yy-T[num*2].r+1;//这时判断中间的一块区域 
    return find(x,num*2+1);    //因为一定可以找到区间，但前面都找不到，那只可能在右半段的区间里了 
}
void gaoji(int num){//ohly~ohlyohlyohly~~ wearethegay~~~wearethegay~~~~~~~~随便取的函数命 
    int k=num<<1;
    clean(k);clean(k+1);
    T[num].l=T[k  ].l;//显然大区间的l是左小区间的l，但是如果左小区间全空，显然大区间的l要加上右小区间的l 
    if(T[k  ].l==T[k  ].yy-T[k  ].xx+1)T[num].l+=T[k+1].l;
    T[num].r=T[k+1].r;//同理 
    if(T[k+1].r==T[k+1].yy-T[k+1].xx+1)T[num].r+=T[k  ].r;
    T[num].m=max(T[k].m,T[k+1].m);//这个很显然啊 
    T[num].m=max(T[num].m,T[k].r+T[k+1].l);
}
void dec(int x,int y,int num){//这些和基本线段树差不多 
    clean(num);
    if(x<=T[num].xx&&T[num].yy<=y){T[num].l=T[num].r=T[num].m=0;T[num].p=1;return;}
    num=num<<1;
    if(x<=T[num  ].yy)dec(x,y,num  );
    if(y>=T[num+1].xx)dec(x,y,num+1);
    gaoji(num/2);
}
void pluss(int x,int y,int num){
    clean(num);
    if(x<=T[num].xx&&T[num].yy<=y){T[num].l=T[num].r=T[num].m=T[num].yy-T[num].xx+1;T[num].p=2;return;}
    num=num<<1;
    if(x<=T[num  ].yy)pluss(x,y,num  );
    if(y>=T[num+1].xx)pluss(x,y,num+1);
    gaoji(num/2);
}
int main()
{
    scanf("%d%d",&n,&m);
    maketree(1,n,1);
    while(m--){
        scanf("%d",&x);
        if(x==1){
            scanf("%d",&x);
            if(T[1].m<x){printf("0\n");continue;}//T[1].m是整个区间中的最大连续空位，这个判断显然成立 
            ans=find(x,1);//通过了上面一个判断，一定可以找出答案 
            printf("%d\n",ans);
            dec(ans,ans+x-1,1);//把新住进来的房间重置 
        }else{
            scanf("%d%d",&x,&y);
            pluss(x,x+y-1,1);//把新走出去的房间重置 
        }
    }
}
```

---

## 作者：木木！ (赞：0)

这题可以使用线段树做，每个节点维护三个信息：前缀、后缀和中间的最大值。但是，线段树的题怎么能用线段树做呢，所以我写了一个`fhq treap`的代码（成功把蓝题变成紫题）

平衡树可以维护数列信息。具体做法是将平衡树的节点以下标为关键字组织，即节点在平衡树内的`rank`即为其在数列里的位置。这样，每个子树都代表一个区间。

为了输出位置，每个节点还要格外记录横跨其的段的左端点相对于其代表的区间的左端点的偏移量（即`crossl`数组）。在查询的时候，`delta`记录该区间的左端点的位置。

要注意`pushup`和`pushdown`不能乱。

附AC代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int lt[50005];
int rt[50005];
int ri[50005];
int siz[50005];
int tag[50005];
int amz[50005]; //整个区间内的最大连续0
int lmz[50005];
int rmz[50005];
int rmzl[50005]; //用于维护crossl
int cross[50005];
int crossl[50005];
int top;

int buildarr(int x) //建树
{
	if(x)
	{
		++top;
		int t = top;
		siz[t] = x;
		amz[t] = lmz[t] = rmz[t] = cross[t] = x;
		lt[t] = buildarr((x-1)>>1);
		rt[t] = buildarr(x-1-((x-1)>>1));
		return t;
	}
	return 0;
}

void pushup(int x)
{
	if(!x)
	{
		return;
	}
	
	siz[x] = siz[lt[x]]+siz[rt[x]]+1;
	
	if(tag[x])
	{
		if(tag[x]==1)
		{
			lmz[x] = rmz[x] = amz[x] = cross[x] = siz[x];
			rmzl[x] = crossl[x] = 0;
		}
		else
		{
			lmz[x] = rmz[x] = amz[x] = cross[x] = crossl[x] = 0;
			rmzl[x] = siz[x];
		}
		return;
	}
	
	if(lmz[lt[x]]==siz[lt[x]] && !ri[x])
	{
		lmz[x] = siz[lt[x]]+1+lmz[rt[x]];
	}
	else
	{
		lmz[x] = lmz[lt[x]];
	}
	
	if(rmz[rt[x]]==siz[rt[x]] && !ri[x])
	{
		rmz[x] = rmz[rt[x]]+1+rmz[lt[x]];
		rmzl[x] = rmzl[lt[x]];
	}
	else
	{
		rmz[x] = rmz[rt[x]];
		rmzl[x] = rmzl[rt[x]]+siz[lt[x]]+1;
	}
	
	cross[x] = crossl[x] = 0;
	if(!ri[x])
	{
		cross[x] = rmz[lt[x]]+1+lmz[rt[x]];
		crossl[x] = rmzl[lt[x]];
	}
	
	amz[x] = max({amz[lt[x]],amz[rt[x]],cross[x]});
}

void pushdown(int x)
{
	if(tag[x])
	{
		pushup(x);
		if(tag[x]==1)
		{
			ri[x] = 0;
			tag[lt[x]] = tag[rt[x]] = 1;
		}
		else
		{
			ri[x] = 1;
			tag[lt[x]] = tag[rt[x]] = 2;
		}
		pushup(lt[x]);
		pushup(rt[x]);
		tag[x] = 0;
	}
}

void split(int t,int s,int& l,int& r)
{
	if(!t)
	{
		l = r = 0;
		return;
	}
	
	pushdown(t);
	if(siz[lt[t]]<s)
	{
		l = t;
		split(rt[t],s-siz[lt[t]]-1,rt[t],r);
		pushup(l);
	}
	else
	{
		r = t;
		split(lt[t],s,l,lt[t]);
		pushup(r);
	}
}

int merge(int l,int r)
{
	if(!l || !r)
	{
		return l+r;
	}
	
	pushdown(l);
	pushdown(r);
	
	if(rand()%(siz[l]+siz[r])<=siz[l])
	{
		rt[l] = merge(rt[l],r);
		pushup(l);
		return l;
	}
	else
	{
		lt[r] = merge(l,lt[r]);
		pushup(r);
		return r;
	}
}

int query(int t,int s,int delta)
{
	if(!t)
	{
		return -1;
	}
	pushdown(t);
	if(amz[lt[t]]>=s) //贪心地往左边移动
	{
		return query(lt[t],s,delta);
	}
	if(cross[t]>=s)
	{
		return crossl[t]+delta;
	}
	return query(rt[t],s,delta+siz[lt[t]]+1);//可以去掉delta参数写成query(rt[t],s)+siz[lt[t]]+1，不过尾递归形式可以让编译器优化成迭代
}

int main()
{
	srand(20040703);
	
	int n,m;
	scanf("%d%d",&n,&m);
	int fhq = buildarr(n);
	
	for(int i=1; i<=m; ++i)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int x;
			scanf("%d",&x);
			int ans = query(fhq,x,0);
			if(ans==-1)
			{
				printf("0\n");
			}
			else
			{
				int ll,rr,tt;
				split(fhq,ans,ll,rr);
				split(rr,x,tt,rr);
				tag[tt] = 2;
				fhq = merge(ll,merge(tt,rr));
				printf("%d\n",ans+1);
			}
		}
		if(opt==2)
		{
			int l,len;
			scanf("%d%d",&l,&len);
			int ll,rr,tt;
			split(fhq,l-1,ll,rr);
			split(rr,len,tt,rr);
			tag[tt] = 1;
			fhq = merge(ll,merge(tt,rr));
		}
	}
}
```

---

## 作者：PPL_ (赞：0)

[题目传送门](https://www.luogu.org/problem/P2894)

区间修改+区间查询

这不就是**线段树**吗

那么我们需要维护哪些元素呢？

线段状态f，最长的连续空房间数k

最重要的就是最长的连续空房间数，但是怎么维护呢？又怎么找第一个空房间呢呢？我们还要维护两个元素：

从左端点开始的连续空房间数lk，从右端点开始的连续空房间数rk

#### 查询操作

先判断当前线段是否存在连续的空房间数大于等于需要的房间数

不是就直接return

如果是，因为要使房间号尽可能小

1.则先看左儿子的lk是否满足，满足则进入

2.再看中间是否满足,中间即为左儿子的rk + 右儿子的lk

满足就可以直接return答案了，即为 左儿子的r-左儿子被占用的rk+1

 //此处可以暂停脑补步骤2

3.最后看右儿子的rk是否满足，满足则进入

```cpp
int query(int x,int d)
{
	if(d > t[x].k)
		return 0;
	if(t[x].l == t[x].r)
		return t[x].l;
	update(x);
	if(t[x<<1].k >= d)//优先考虑前面
		return query(x << 1,d);
	else if(t[x<<1].rk + t[x<<1|1].lk >= d)//其次是中间
		return t[x<<1].r - t[x<<1].rk + 1;
	else if(t[x<<1|1].k >= d)//最后是后面
		return query(x << 1 | 1,d);
	return 0;
}

```

#### 入住操作 and 退房操作

就像平时的线段树区间修改一样，只是维护的时候有些不同

首先往下找的时候要把父节点的状态更新给子节点(懒标记)

到了之后要更新当前点状态，最后向上更新

我定义的状态为

0：当前线段一个人都没有

1：当前线段住满人

-1：既有入住的，又有没人的

```cpp
void check(int x,int l,int r,int f)
{
	if(t[x].r < l || t[x].l > r)
		return;
	if(t[x].r <= r && t[x].l >= l)
	{
		t[x].f = f;
		if(f == 1)
			t[x].lk = t[x].rk = t[x].k = 0;
		else
			t[x].lk = t[x].rk = t[x].k = t[x].r - t[x].l + 1;
		return;
	}
	update(x);//往下更新
	check(x<<1,l,r,f);
	check(x<<1|1,l,r,f);
	update1(x);//向上更新
}
```

如果你听懂了，update可以自己琢磨写，实在不行就看看吧

代码：

```cpp
//12252024832524
#include <cstdio>
#include <algorithm>
#define Min(x,y) (x<y?x:y)
#define Max(x,y) (x>y?x:y)
using namespace std;

typedef long long LL;
const int MAXN = 50005;
int n;
struct node
{
	int l,r,f;
	int lk,rk,k;
}t[MAXN << 1];

int Read()
{
	int x1 = 0,f1 = 1;char c1 = getchar();
	while(c1 > '9' || c1 < '0'){if(c1 == '-')f1 = -1;c1 = getchar();}
	while(c1 >= '0' && c1 <= '9'){x1 = (x1*10) + (c1^48);c1 = getchar();}
	return x1 * f1;
}
void Put(int x)
{
	if(x > 9)
		Put(x/10);
	putchar(x%10^48);
}
void update(int x)//向下传递
{
	if(t[x].f < 0)
		return ;
	int f = t[x].f;
	t[x].f = -1;
	//左
	x <<= 1;
	if(f == 1)
		t[x].lk = t[x].rk = t[x].k = 0;
	else
		t[x].lk = t[x].rk = t[x].k = t[x].r - t[x].l + 1;
	t[x].f = f;
	//右
	x |= 1;
	if(f == 1)
		t[x].lk = t[x].rk = t[x].k = 0;
	else
		t[x].lk = t[x].rk = t[x].k = t[x].r - t[x].l + 1;
	t[x].f = f;
}
void update1(int x)//向上更新
{
	t[x].lk = t[x<<1].lk;
	t[x].rk = t[x<<1|1].rk;
	if(t[x].lk == t[x<<1].r - t[x<<1].l + 1)//左边全没占
		t[x].lk += t[x<<1|1].lk;//加上右儿子的左边
	if(t[x].rk == t[x<<1|1].r - t[x<<1|1].l + 1)//右边全没占
		t[x].rk += t[x<<1].rk;//加上左儿子的右边
	t[x].k = Max(t[x<<1].k,t[x<<1|1].k);//更新k，左或右
	t[x].k = Max(t[x].k,t[x<<1].rk + t[x<<1|1].lk);//或中间 
}
void Build(int x,int l,int r)
{
	t[x].l = l;
	t[x].r = r;
	t[x].k = t[x].rk = t[x].lk = r - l + 1;
	if(l == r)
		return ;
	int mid = (l+r) >> 1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
}
void check(int x,int l,int r,int f)//check in and check out
{
	if(t[x].r < l || t[x].l > r)
		return;
	if(t[x].r <= r && t[x].l >= l)
	{
		t[x].f = f;
		if(f == 1)
			t[x].lk = t[x].rk = t[x].k = 0;
		else
			t[x].lk = t[x].rk = t[x].k = t[x].r - t[x].l + 1;
		return;
	}
	update(x);//往下更新
	check(x<<1,l,r,f);
	check(x<<1|1,l,r,f);
	update1(x);//向上更新
}
int query(int x,int d)
{
	if(d > t[x].k)
		return 0;
	if(t[x].l == t[x].r)
		return t[x].l;
	update(x);
	if(t[x<<1].k >= d)//优先考虑前面
		return query(x << 1,d);
	else if(t[x<<1].rk + t[x<<1|1].lk >= d)//其次是中间
		return t[x<<1].r - t[x<<1].rk + 1;
	else if(t[x<<1|1].k >= d)//最后是后面
		return query(x << 1 | 1,d);
	return 0;
}

int main()
{
	freopen("hotel.in","r",stdin);
	freopen("hotel.out","w",stdout);
	n = Read();
	Build(1,1,n);
	for(int m = Read();m;-- m)//据说比while快
	{
		int pd = Read(),x = Read();
		if(pd == 1)
		{
			pd = query(1,x);
			Put(pd);
			putchar('\n');
			if(pd)
				check(1,pd,pd+x-1,1);
		}
		else
			check(1,x,x+Read()-1,0);
	}
	return 0;
}
```


---

