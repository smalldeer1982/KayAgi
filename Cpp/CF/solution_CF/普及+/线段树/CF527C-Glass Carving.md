# Glass Carving

## 题目描述

Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular $ w $ mm $ × $ $ h $ mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.

In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.

After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.

Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?

## 说明/提示

Picture for the first sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/6468d2fd0321178fa316ccb774411f002769e9ee.png) Picture for the second sample test:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/40ba2772b27431a21bc874ab308dc348ec8365fd.png)

## 样例 #1

### 输入

```
4 3 4
H 2
V 2
V 3
V 1
```

### 输出

```
8
4
4
2
```

## 样例 #2

### 输入

```
7 6 5
H 4
V 3
V 5
H 2
V 1
```

### 输出

```
28
16
12
6
4
```

# 题解

## 作者：Liu_zj (赞：18)

先来分析题目，要求找到切割后最大的矩形面积，根据说明里的图片分析得知，问题可以转换为求横纵两边最长的一段。

看到这里，想到了一道经典的题目：[hotel酒店（旅馆）](https://www.luogu.org/problemnew/show/P2894)

维护横纵两边最长的未被切割的一段，可以用线段树。横纵两边各建一棵线段树。

用0表示没被切割，用1表示被切割。

## 求区间最长的连续0：

首先想到，维护当前区间最长连续0，大区间的最长连续0等于左右区间最长连续0的max。

然而，对这一个左右区间：11000011000  00011000001，合并后大区间的最长连续0明显是6（中间的一段），而不是5（max(4,5)）。

这种情况如何处理呢？

分析发现，中间的这一段是由左边区间的右边连续零，和右边区间的左边连续零。

所以我们维护区间左右连续零就可以了。

将左右区间的 中间最大连续零和 左区间的右边和右区间的左边的和 进行比较求最大值，就是 除左右区间之外的最长连续零

关于左右区间连续零，

大区间的左右连续零等于左\右区间连续左\右零

吗？

对于下面这个数据：000000 001001,合并区间后左边最长连续零应该是8（6+2）而不是6（左区间的左连续零）。

那么我们还需要维护一个bool，标记是否当前区间全是零。

如果全是零，那么 大区间的左边连续零 等于 左边区间的所有零 加上 右边区间的左边连续零

大区间的左右连续零
**000000 00**1001

等于

左边区间的所有零**000000** 001001

加上

右边区间的左边连续零000000 **00**1001

如果不全是零，那么大区间的左边连续零等于左区间的左边连续零。（右边同理



## 修改和查询：

修改就是将当前点所有维护的信息变成0 。

建树时将当前点所有维护的信息变成1 。

由于查询整个区间的最大值，所以直接查询根节点即可，不必打区间查询板子（手痒除外）。

## 小细节

输入的是距离，所以在建树查询时要-1，在输出时要+1 。

横切影响的是纵，纵切影响的是横。

左右区间全是零，当前区间全是零，**否则不全是零**。

开longlong好习惯。

## 代码（码风清奇
```
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000010
#define int long long
int sum_z[MAXN][5];//左区间最大值
int sum_y[MAXN][5];//右区间最大值
int sum_m[MAXN][5];//整个最大值
bool ifallzero[MAXN][5];//是否全是零
void update(int now,int horz)
{
	if(ifallzero[now<<1][horz]==1)//左儿子全零
		sum_z[now][horz]=sum_z[now<<1][horz]+sum_z[now<<1|1][horz];//当前左边等于左边的全部+右边的左边
	else
		sum_z[now][horz]=sum_z[now<<1][horz];//否则当前左边等于左儿子左边
		
	if(ifallzero[now<<1|1][horz]==1)//右儿子全零
		sum_y[now][horz]=sum_y[now<<1|1][horz]+sum_y[now<<1][horz];//同上 
	else
		sum_y[now][horz]=sum_y[now<<1|1][horz];//同上 

	sum_m[now][horz]=max((sum_y[now<<1][horz]+sum_z[now<<1|1][horz]),max(sum_m[now<<1][horz],sum_m[now<<1|1][horz]));//中间等于左边的右边+右边的左边与左右两边最大值的最大值 

	if(ifallzero[now<<1][horz]==1&&ifallzero[now<<1|1][horz]==1)
	ifallzero[now][horz]=true;//左右全零和全零
	else
	ifallzero[now][horz]=false;
}
void build(int now,int l,int r,int horz)//建树
{
	if(l==r)
	{
		sum_z[now][horz]=1;
		sum_y[now][horz]=1;
		sum_m[now][horz]=1;
		ifallzero[now][horz]=true;//全是1
		return ;
	}
	int mid=(l+r)>>1;
	build(now<<1,l,mid,horz);
	build(now<<1|1,mid+1,r,horz);
	update(now,horz);
}
void change(int now,int l,int r,int go,int horz)//修改
{
	if(l==r)
	{
		ifallzero[now][horz]=false;//全是0
		sum_z[now][horz]=0;
		sum_y[now][horz]=0;
		sum_m[now][horz]=0;
		return ;
	}
	int mid=(l+r)>>1;
	if(go<=mid)
	change(now<<1,l,mid,go,horz);
	else
	change(now<<1|1,mid+1,r,go,horz);
	update(now,horz);
}
signed main()
{
	int w,h,n,x;
	char o;
	cin>>w>>h>>n;
	build(1,1,w-1,1);//横 
	build(1,1,h-1,2);//纵 
	for(int i=1;i<=n;i++)
	{
		cin>>o>>x;
		if(o=='H')
			change(1,1,h-1,x,2);//横切影响纵 
		if(o=='V')
			change(1,1,w-1,x,1);//纵切影响横 
		cout<<(sum_m[1][1]+1)*(sum_m[1][2]+1)<<endl;
	}
    //return 0 好习惯
}
```

这里顺便整理了线段树比较简单的“板子”题

线段树题目：

[统计和：简化版的模板1](https://www.luogu.org/problemnew/show/P2068)

[忠诚：模板1难度经典题](https://www.luogu.org/problemnew/show/P1816)

[XOR的艺术：模板1的变种](https://www.luogu.org/problemnew/show/P2574)

[最大数：模板1的变种](https://www.luogu.org/problemnew/show/P1198)

[光开关：XOR艺术的双倍经验](https://www.luogu.org/problemnew/show/P2846)

[开关：XOR艺术的三倍经验](https://www.luogu.org/problemnew/show/P3870)

[维护序列：模板2的双倍经验](https://www.luogu.org/problemnew/show/P2023)

[方差：线段树+数学，模板1变种](https://www.luogu.org/problemnew/show/P1471)

[数学计算：模板1简化](https://www.luogu.org/problemnew/show/P4588)

[Glass Carving：模板1困难](https://www.luogu.org/problemnew/show/CF527C)

[酒店hotel：Glass的困难版](https://www.luogu.org/problemnew/show/P2894)

---

## 作者：KNO3 (赞：16)

lang:C++

思路：用set&multiset储存切割后的碎块边长最大值及切割位置

每次切割后维护一下,输出最大碎块边长的积就可以了

STL大法好

使用STL中的set&multiset（set中元素不可重复,multiset可以）

直接省去了排序的过程

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
int w,h,n,t;
set<long long>lx,ly;
multiset<long long>x,y;
multiset<long long>::iterator it;
char c;
int main()
{
	scanf("%d%d%d",&w,&h,&n);
	x.insert(w);
	y.insert(h);
     //x,y储存碎块边长
	lx.insert(0);lx.insert(w);
	ly.insert(0);ly.insert(h);
     //lx,ly储存切割位置
	for(int i=1;i<=n;++i)
	{
		cin>>c>>t;
		if(c=='H')
		{
			ly.insert(t);//加入新的切割位置
			it=ly.find(t);
            //无须排序
			--it;
			long long l=*it;//前一条切割位置
			++it;++it;
			long long r=*it;//后一条切割位置
			it=y.find(r-l);
            //找到原来的“碎块边长”
			y.erase(it);
            //已被破坏
			y.insert(r-t);
			y.insert(t-l);
            //新加了两条“碎块边长”
		}
		else
		{
        	//同理
			lx.insert(t);
			it=lx.find(t);
			--it;
			int l=*it;
			++it;++it;
			int r=*it;
			it=x.find(r-l);
			x.erase(it);
			x.insert(r-t);
			x.insert(t-l);
		}
		it=x.end();it--;
		long long l=*it;
		it=y.end();it--;
		long long r=*it;
        //寻找最大值
		cout<<(long long)(l*r)<<endl;
	}
	return 0;
}
```

---

## 作者：KRMS (赞：10)

似乎各位dalao都是用线段树或set做的这道题，那么本蒟蒻来一发**链表离线做法**。

对于此题而言，显然最后的切割状态一定是正确的，那么我们不妨按照时间倒序来求出每一次切割后的最大面积。

首先，将所有切割完成后的横坐标和纵坐标分别排序，然后分别求出横轴和纵轴中的最大长度，同时用链表维护每一个点的前驱和后继（比它坐标小的第一个点和比它坐标大的第一个点），根据人类的智慧，横轴最大值*纵轴最大值即为最后一个答案。

其次，按照时间倒序求出第n-1~1次切割后的答案。显然，每次切割后新产生的点只会影响它的前驱和后继，那么我们把每个点按照时间倒序删掉，同时更新被删除点的前驱后继，再用被删除点的后继坐标-前驱坐标更新该坐标轴上的最大长度即可。总时间复杂度粗略估算O(n)，有可能被卡出来log，不过2e5还是妥妥的（溜
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int maxn=200020;

int n,m,q,cnt,tot,maxx,maxy;
int stra[maxn],strb[maxn],fx[maxn],fy[maxn],sum[maxn];

struct haha{int len,nxt,pre,flag;}a[maxn],b[maxn];

struct hahaha{char opt[10];int len,flag;}num[maxn];

void read()
{
	cin>>n>>m>>q;
	for(int i=1,k;i<=q;i++)
	{
		char str[5]; scanf("%s",str+1); scanf("%lld",&k);
		if(str[1]=='V' && (((k==0)||(k==n)) || fx[k]) 
		|| str[1]=='H' && (((k==0)||(k==m)) || fy[k]))
		{num[i].flag=1;continue;} 
		num[i].opt[1]=str[1]; 
		num[i].len=k; 
		num[i].flag=0;
		if(num[i].opt[1]=='H')
		{
			strb[++tot]=num[i].len;
			fy[num[i].len]=1;
		} 
		else 
		{
			stra[++cnt]=num[i].len;
			fx[num[i].len]=1;
		}
	}
}

void deal_first()
{
	sort(stra+1,stra+cnt+1);
	sort(strb+1,strb+tot+1);
	if(strb[tot]!=m)strb[++tot]=m;
	if(stra[cnt]!=n)stra[++cnt]=n;
	for(int i=1,pre=0;i<=cnt+1;i++)
	{
		if(stra[i]==pre) continue;
		a[pre].nxt=stra[i];
		a[stra[i]].pre=pre;
		a[stra[i]].flag=1;
		a[stra[i]].len=stra[i]-pre;
		maxx=max(maxx,(stra[i]-pre));
		pre=stra[i];
	}
	for(int i=1,pre=0;i<=tot;i++)
	{
		if(strb[i]==pre) continue;
		b[pre].nxt=strb[i];
		b[strb[i]].pre=pre;
		b[strb[i]].flag=1;
		b[strb[i]].len=strb[i]-pre;
		maxy=max(maxy,(strb[i]-pre));
		pre=strb[i];
	}
	sum[q]=maxx*maxy;
}

void do_it()
{
	for(int i=q;i>=2;i--)
	{
		if(num[i].flag){sum[i-1]=sum[i];continue;}
		int len=num[i].len;
		if(num[i].opt[1]=='H')
		{
			if(!b[len].flag) continue;
			b[len].flag=0;
			b[b[len].nxt].len+=b[len].len;
			maxy=max(maxy,b[b[len].nxt].len);
			b[b[len].pre].nxt=b[len].nxt;
			b[b[len].nxt].pre=b[len].pre;
			sum[i-1]=maxx*maxy;
		}
		else
		{
			if(!a[len].flag) continue;
			a[len].flag=0;
			a[a[len].nxt].len+=a[len].len;
			maxx=max(maxx,a[a[len].nxt].len);
			a[a[len].pre].nxt=a[len].nxt;
			a[a[len].nxt].pre=a[len].pre;
			sum[i-1]=maxx*maxy;
		}
	}
	for(register int i=1;i<=q;i++) printf("%lld\n",sum[i]);
}

signed main()
{
	read();
	deal_first();
	do_it();
	return 0;
}
```


---

## 作者：生而为人 (赞：6)

## 来一发60行（不压行）的清新线段树。
**此题让你求每次切割之后的 最大值， 你可以把它 没有切得部分赋为0被切割得部分赋为一 转化为求 最长的 连续 0的串的长度。 由于w，h过于大，我们可以开两颗线段树分别维护再 求乘  但由于是距离 所以减一加一要注意 下面附AC代码：**
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
const int N=200005;
struct node
{
	int lma;
	int rma;
	int ma;
};
node tr[N<<2][3];
void up(int id,int k,int l,int r)
{
	int mid=(l+r)>>1;
	tr[k][id].lma=tr[k<<1][id].lma==(mid-l+1)?tr[k<<1][id].lma+tr[k<<1|1][id].lma:tr[k<<1][id].lma;
	tr[k][id].rma=tr[k<<1|1][id].rma==(r-mid)?tr[k<<1|1][id].rma+tr[k<<1][id].rma:tr[k<<1|1][id].rma;
	tr[k][id].ma=max(tr[k<<1][id].ma,tr[k<<1|1][id].ma);
	tr[k][id].ma=max(tr[k][id].ma,tr[k<<1][id].rma+tr[k<<1|1][id].lma);
}
void build(int id,int k,int l,int r)
{
	if(l==r) return (void) (tr[k][id].lma=tr[k][id].rma=tr[k][id].ma=1);
	int mid=(l+r)>>1;
	build(id,k<<1,l,mid);
	build(id,k<<1|1,mid+1,r);
	up(id,k,l,r);
}
void add(int id,int k,int l,int r,int pos)
{
	if(l==r) return(void)(tr[k][id].lma=tr[k][id].rma=tr[k][id].ma=0);
	int mid=(l+r)>>1;
	if(pos<=mid)
	add(id,k<<1,l,mid,pos);
	else
	add(id,k<<1|1,mid+1,r,pos);
	up(id,k,l,r);
}
int query(int id,int k,int l,int r,int ql,int qr)
{
	if(ql==l&&qr==r) return max(tr[k][id].ma,max(tr[k][id].lma,tr[k][id].rma));
	int mid=(l+r)>>1;
	if(qr<=mid)
	return query(id,k<<1,l,mid,ql,qr);
	else
	if(ql>mid)
	return query(id,k<<1|1,mid+1,r,ql,qr);
	else
	return max(query(id,k<<1,l,mid,ql,mid),query(id,k<<1|1,mid+1,r,mid+1,qr));
}
int w,h,q;
signed main()
{
	scanf("%lld%lld%lld",&w,&h,&q);
	build(1,1,1,w-1),build(2,1,1,h-1);
	for(int i=1;i<=q;i++)
	{
		char x;
		int y;
		cin>>x>>y;
		if(x=='H')add(2,1,1,h-1,y);
		else add(1,1,1,w-1,y);
		cout<<(query(1,1,1,w,1,w)+1)*(1+query(2,1,1,h,1,h))<<endl;
	}
}
```


---

## 作者：luckydrawbox (赞：4)

## 题意

有一块 $w\times h$ 的玻璃，每次横着切一刀 $(H)$ 或者竖着切一刀 $(V)$ ，没有两次相同的切割，求最大的矩形碎片面积。 

## 分析

显然，最大矩形碎片面积 $=$ 最大的长 $\times$ 最大的宽。因为长宽互不干扰，所以我们分开处理。

我们把求长和宽看作查询，把切看成修改，显然我们需要两个支持单点修改+区间查询的线段树。

接下来以 $w$（横着）为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/rzovi7bp.png)

我们线段树中定义的点是一段长度，但题目要把一段长度分开，怎么办呢？

**加几个点**呗！

没错，由于切割都是整数，所以我们在相邻两个单位长度之间加一个点，原来 $w$ 个点变成了 $2\times w-1$ 个点，第 $x$ 个单位长度与第 $x+1$ 个单位长度之间的间隙相当于第 $2\times x$ 个节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/tmil6q8a.png)

建树时，我们令全局为 $1$。

切断时，我们只要把第 $2\times x$ 个节点改成 $0$，维护最长的连续 $1$ 的个数就行了。

计算答案时，最大矩形碎片面积 $=$（第一个线段树最长的连续 $1$ 的个数 $+1$）$\div2\times$ （第二个线段树最长的连续 $1$ 的个数 $+1$）$\div2$。

**友情提示**：注意开 ``long long``。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pl p<<1
#define pr p<<1|1
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int N=4e5+10;
int w,h,n,x;
char op;
struct Tree{
	int l,r;
	int lmx,rmx,mx;
}s[2][4*N];
void pushup(int k,int p){
	s[k][p].lmx=s[k][pl].lmx;
	if(s[k][pl].lmx==s[k][pl].r-s[k][pl].l+1)
		s[k][p].lmx=max(s[k][p].lmx,s[k][pl].lmx+s[k][pr].lmx);
	s[k][p].rmx=s[k][pr].rmx;
	if(s[k][pr].rmx==s[k][pr].r-s[k][pr].l+1)
		s[k][p].rmx=max(s[k][p].rmx,s[k][pr].rmx+s[k][pl].rmx);
	s[k][p].mx=max(max(s[k][pl].mx,s[k][pr].mx),max(s[k][p].lmx,s[k][p].rmx));
	s[k][p].mx=max(s[k][p].mx,s[k][pl].rmx+s[k][pr].lmx);
}
void build(int k,int p,int l,int r){
	s[k][p].l=l;s[k][p].r=r;
	if(l==r){
		s[k][p].mx=s[k][p].lmx=s[k][p].rmx=1;
		return;
	}
	int mid=(l+r)>>1;
	build(k,pl,l,mid);
	build(k,pr,mid+1,r);
	pushup(k,p);
}
void change(int k,int p,int x){
	if(s[k][p].l==s[k][p].r){
		s[k][p].mx=s[k][p].lmx=s[k][p].rmx=0;
		return;
	}
	int mid=(s[k][p].l+s[k][p].r)>>1;
	if(x<=mid)
		change(k,pl,x);
	else
		change(k,pr,x);
	pushup(k,p);
}
ll ask(){
	return (ll)(s[0][1].mx+1)/2*(s[1][1].mx+1)/2;
}
int main()
{
    w=read();h=read();n=read();
	build(0,1,1,2*w-1);
	build(1,1,1,2*h-1);
	for(int i=1;i<=n;i++){
		cin>>op;
      x=read();
		if(op=='H')
			change(1,1,2*x);
		else
			change(0,1,2*x);
		cout<<ask()<<endl;
	}
	return 0;
}
```


---

## 作者：SUNCHAOYI (赞：3)

对于每一次切割后，求出最大的碎片面积，也就是求出完整的玻璃的最大长度与最大宽度之积。

由题意可知，一条长度为 $k$ 的边，最多可以被切 $k - 1$ 次，因为在此之后均为长度为 $1$ 的边无法在切割。于是我们就可以用 $0$ 或 $1$ 来表示该边的某个点是否被切割，总共表示 $k - 1$ 个点。初始的时候每个点均为 $0$，表示所有的点均未被切割，每输入一次后将相应的切割点标记为 $1$。于是乎，不难将问题转化成求每次切割后每条边的最长 $0$ 的个数。

考虑用线段树来维护，一棵线段树共有以下参数：`len`、`l`、`r` 与 `mx`，分别表示区间的长度、从左端点最长 $0$ 的个数、从右端点最长 $0$ 的个数以及该区间最长 $0$ 的个数。

下面我将分别讲述 `build` 、 `modify` 与 `pushup` 函数。

在 `build` 函数中，因初始时均为 $0$，所以每段区间的 `l`、`r` 与 `mx` 的值均为 `len`，即 $r - l + 1$，有以下代码：

```cpp
void build (T tree[],int cur,int l,int r)
{
	tree[cur].l = tree[cur].r = tree[cur].mx = tree[cur].len = r - l + 1;
	if (l == r) return ;
	int mid = (l + r) >> 1;                                    
	build (tree,cur << 1,l,mid);
	build (tree,cur << 1 | 1,mid + 1,r); 
	pushup (tree,cur);//这个在接下去讲
}
```

在 `modify` 函数中，由题可知是一个单点的修改，因此我们只需要在 $l = r$ 之时把该点的值改为 $1$，表示已被切割就可以了。同时，该区间的 `l`、`r` 与 `mx` 因数值的变化均会变为 $0$。代码如下：

```cpp
void modify (T tree[],int cur,int l,int r,int x)
{
	if (l == r && x == l)
	{
		tree[cur].l = tree[cur].r = tree[cur].mx = 0;//已被切割，此点变为 1，故该点的 0 个数均更新为 0
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify (tree,cur << 1,l,mid,x);
	else modify (tree,cur << 1 | 1,mid + 1,r,x);
	pushup (tree,cur);
}
```

最后来讲 `pushup` 函数，每个区间在更新后除长度不会改变外其余均有变动。首先是 `l` 的值，分两种情况，若从左端点最长 $0$ 的个数与区间长度相等，则说明正一段区间均为 $0$，因此可以更新至右区间的左端 $0$ 所能达到的最远之处，相加即可；否则就是左端点的 `l` 的值。`r` 的值同理分两种情况，不再赘述。同时，需要更新区间 `mx`，易得有三种情况，分别为左端点开始最长的 $0$ 的个数，右端点开始最长的 $0$ 的个数以及序列中间最长的 $0$ 的个数，三者取最值就能更新答案了。代码如下：

```cpp
void pushup (T tree[],int cur)
{
	if (tree[cur << 1].l == tree[cur << 1].len) tree[cur].l = tree[cur << 1].len + tree[cur << 1 | 1].l;
	else tree[cur].l = tree[cur << 1].l;	
	if (tree[cur << 1 | 1].r == tree[cur << 1 | 1].len) tree[cur].r = tree[cur << 1 | 1].len + tree[cur << 1].r;
	else tree[cur].r = tree[cur << 1 | 1].r;
	tree[cur].mx = max (tree[cur << 1].mx,max (tree[cur << 1 | 1].mx,tree[cur << 1].r + tree[cur << 1 | 1].l));//三段取最值
}
```

最后给出主函数，查询即为下标为 $1$ 的线段树的数组的 `mx` 值，但返回的答案记得 $+1$，画一下图就能悟了哦！

```cpp
int main ()
{
	m = read ();n = read ();q = read ();
	build (tree_l,1,1,n - 1);build (tree_h,1,1,m - 1);
	while (q--)
	{
		char x;int num;
		scanf ("%c",&x);num = read ();
		if (x == 'H') modify (tree_l,1,1,n - 1,n - num);//距离底部
		else modify (tree_h,1,1,m - 1,num);//距离左端
		ll da = tree_h[1].mx + 1,db = tree_l[1].mx + 1;//别忘了
		printf ("%lld\n",da * db);
	}
	return 0;
}
```

---

## 作者：zplqwq (赞：3)

用 multiset 和 set 做的。

因为切割位置可以重复，因此考虑用 multiset 存储。而 set 可以存储切割后的碎块边长的最值。

最后每次切割之后维护一下最大积输出即可。

因为 set 和 multiset 都是默认从小到大排序的，因而不用排序。

具体看代码理解。

```cpp

#include<bits/stdc++.h>
//by :zplqwq
using namespace std;

int w,h,n;
multiset<int> sx;
multiset<int> sy;
set<int> x;
set<int> y;
char c;
int p;
int main()
{
	
	scanf("%d%d%d",&w,&h,&n);
	x.insert(0);
	x.insert(h);
	y.insert(w);
	y.insert(0);
   // 边长
	sx.insert(h);
	sy.insert(w);
   //位置
	for(int i=1;i<=n;i++)
	{
		char c;
		int p;
		scanf("%s%d",&c,&p);
		//scanf("%d",&p);
		//cout<<endl;
      //这里我考虑了会有两个一样的切的情况，其实按照题意是可以不考虑的。
		if(c=='V')
		{
			multiset<int>::iterator it,itt,ittt;
			it=y.lower_bound(p);
			itt=it;
			if(it!=y.begin())	--it;
			y.insert(p);
			ittt=sy.lower_bound(*itt-*it);
        //删除已被破坏的
			sy.erase(ittt);
        //新增边长
			sy.insert(*itt-p);
			sy.insert(p-*it);
			//sy.insert(rs); 
			/*
			else
			{
				sy.insert(ls);
				sy.insert(rs);
			}
			*/
		}
		else
		{
        //与上面几乎同理
			multiset<int>::iterator it,itt,ittt;
			it=x.lower_bound(p);
			itt=it;
			if(it!=x.begin())	--it;
			x.insert(p);
			ittt=sx.lower_bound(*itt-*it);
			sx.erase(ittt);
			sx.insert(*itt-p);
			sx.insert(p-*it);
		//	sx.insert(rs);
			/*
			else
			{
				sy.insert(ls);
				sy.insert(rs);
			}
			*/
			
		}
		int a,b;
		a=*(--sx.end());
		b=*(--sy.end());
     //取最大乘积
		//cout<<a<<" "<<b<<endl;
		printf("%lld\n",(1LL)*a*b);
	}
	
	return 0;
}
```

---

## 作者：如我西沉 (赞：2)

这题，长宽都是 10^5，所以，用 01 序列表示每个点是否被切割，然后，

最长的长就是长的最长连续 0 的数量+1

最长的宽就是宽的最长连续 0 的数量+1

于是用线段树维护最长连续零

问题转换成：

目标信息：区间最长连续零的个数

点信息：0 或 1 由于目标信息不符合区间加法，所以要扩充目标信息。
转换后的线段树结构：

区间信息：从左，右开始的最长连续零，本区间是否全零，本区间最长连续零。

点信息：0 或 1

然后还是那 2 个问题：

1.区间加法：

这里，一个区间的最长连续零，需要考虑 3 部分：

（1）：左子区间最长连续零

（2）：右子区间最长连续零

（3）：左右子区间拼起来，而在中间生成的连续零（可能长于两个子区间的最长连续零）而中间拼起来的部分长度，其实是左区间从右开始的最长连续零+右区间从左开始的最长连续零。

所以每个节点需要多两个量，来存从左右开始的最长连续零。

然而，左开始的最长连续零分两种情况，

（1）：左区间不是全零，那么等于左区间的左最长连续零

（2）：左区间全零，那么等于左区间 0 的个数加上右区间的左最长连续零

于是，需要知道左区间是否全零，于是再多加一个变量。

最终，通过维护 4 个值，达到了维护区间最长连续零的效果。

2.点信息->区间信息 ：

如果是 0，那么 最长连续零=左最长连续零=右最长连续零=1 ，全零=true。

如果是 1，那么 最长连续零=左最长连续零=右最长连续零=0， 全零=false。

至于修改和查询，有了区间加法之后，机械地写一下就好了。

由于这里其实只有对整个区间的查询，所以查询函数是不用写的，直接找根的统计信息就行了。

代码如下：
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define lson id<<1
#define rson id<<1|1
const long long maxn=200001;
long long x,w,h,n,a[maxn],b[maxn];
char c;
long long lt[maxn<<2][2];
long long rt[maxn<<2][2];
long long l[maxn<<2][2];
long long r[maxn<<2][2];
long long ma[maxn<<2][2];
bool pure[maxn<<2][2];
void pushup(long long id,long long k){
 	pure[id][k]=pure[lson][k]&&pure[rson][k];
 	ma[id][k]=max(r[lson][k]+l[rson][k],max(ma[lson][k],ma[rson][k]));
 	l[id][k]=pure[lson][k]?l[lson][k]+l[rson][k]:l[lson][k];
 	r[id][k]=pure[rson][k]?r[rson][k]+r[lson][k]:r[rson][k];
}
inline void build(long long id,long long ll,long long rr,long long k)
{
	lt[id][k]=ll;
	rt[id][k]=rr;
	if (ll==rr)
	{
		pure[id][k]=true;
		ma[id][k]=1;
		l[id][k]=1;
		r[id][k]=1;
		return;
	}
	long long mid=(ll+rr)>>1;
	build(lson,ll,mid,k);
	build(rson,mid+1,rr,k);
	pushup(id,k);
}
inline void update(long long id,long long x,long long k)
{
	if (lt[id][k]==x && rt[id][k]==x)
	{
		pure[id][k]=false;
		ma[id][k]=0;
		l[id][k]=0;
		r[id][k]=0;
		return;
	}
	long long mid=(lt[id][k]+rt[id][k])>>1;
	if (x<=mid) update(lson,x,k);
	  else update(rson,x,k);
	pushup(id,k);
}
int main()
{
	scanf("%lld%lld%lld",&w,&h,&n);
	build(1,1,w-1,1);
	build(1,1,h-1,0);
	for (long long i=1;i<=n;i++)
	{	
		c=getchar();
		while (c!='H' && c!='V') c=getchar();
		if (c=='V') 
		{
			scanf("%lld",&x);
			update(1,x,1);
		}
		else
		{
			scanf("%lld",&x);
			update(1,x,0);
		}
		printf("%lld\n",(ma[1][1]+1)*(ma[1][0]+1));
	}
	return 0;
}
```

---

## 作者：zymooll (赞：1)

### 题目大意

给定一个矩形，大小为 $w \times h$，再给定 $n$ 次操作，每次操作将会以一条平行与水平或竖直方向上过某点的的直线分割矩形。

### 主要思路

建立两个数轴分别存储横轴和竖轴，对于每次操作，即相当于分割数轴。

对于每次查询，即相当于查询横轴和竖轴上最长的数轴长度。

附抽象图一张：

![](https://cdn.luogu.com.cn/upload/image_hosting/dmb3lfk3.png?x-oss-process=image/resize,m_lfit,h_420/rotate,270)

### 实现方式

这也就是本题解相较于其他题解的不同之处。

鄙人所想的方案是先建立两个数组，分别存储横轴和竖轴的区间内最长数轴长度，初始值易得为全区间为 $w$ 或 $h$。

定义下文所指位置 $x$ 为在 $x$ 到 $x+1$ 间砍了一刀。

初始时，相当于要在矩形最左侧 $0$ 位置和最右侧 $n$ 位置砍了一刀。

对于每次修改，令修改位置为 $x$，查询出其前驱 $pre$，和后继 $nxt$，再将 $[pre+1,x]$ 修改为 $x-pre$，将 $[x+1,nxt]$ 修改为 $nxt-x$。

对于查询前驱后继，易想到平衡树；而对于区间修改，宜采用线段树。

相较于其他题解，本方法优势在于都是板子，好写好想，缺点就是码量较大（鄙人写了 3K）。

附抽象图一张：

![](https://cdn.luogu.com.cn/upload/image_hosting/4mx30lum.png?x-oss-process=image/resize,m_lfit,h_420/rotate,270)

### 代码参考

线段树实现为动态开点线段树，平衡树实现为 01trie。

为保证观感，略去了快读快写及头文件，请读者自行补全。

```cpp
// Author:zymooll
#define int long long
using namespace std;
char getchar_s(){
    char ch=getchar();
    while(ch=='\n'||ch=='\r')ch=getchar();
    return ch;
}
const int NMax=2e5;
const int W=18;
int w,h,n;
struct DataStruct{
    int size;
    struct SegmentTree{
        //work on dynamic open point segment tree O(nlogn)
        struct Node{
            int n,l,r;
        }t[2*NMax+10];
        int ncnt=1;
        int modify(int p,int L,int R,int l,int r,int x){
            if(!p)p=++ncnt;
            if(l<=L&&R<=r){
                t[p].n=x;
                return p;
            }
            int mid=(L+R)/2;
            if(l<=mid)t[p].l=modify(t[p].l,L,mid,l,r,x);
            if(r>mid)t[p].r=modify(t[p].r,mid+1,R,l,r,x);
            t[p].n=max(t[t[p].l].n,t[t[p].r].n);
            return p;
        }
        int ask(){
            return t[1].n;
        }
    }st;
    struct BalancedTree{
        //work on 01trie O(nlogw)
        int size;
        struct Node{
            int n,son[2];
        }t[NMax*W+10];
        int ncnt=1;
        void add(int x){
            int u=1;
            for(int i=W;i>=0;i--){
                int c=(x>>i)&1;
                if(!t[u].son[c])t[u].son[c]=++ncnt;
                u=t[u].son[c];
                t[u].n++;
            }
            return;
        }
        int rnk(int x){
            int u=1,ans=0;
            for(int i=W;i>=0;i--){
                if(x<=t[t[u].son[0]].n)u=t[u].son[0];
                else{
                    x-=t[t[u].son[0]].n;
                    ans^=(1<<i);
                    u=t[u].son[1];
                }
            }
            return ans;
        }
        int kth(int x){
            int u=1,ans=1;
            for(int i=W;i>=0;i--){
                int c=(x>>i)&1;
                if(c)ans+=t[t[u].son[0]].n;
                u=t[u].son[c];
            }
            return ans;
        }
        int pre(int x){
            return rnk(kth(x)-1);
        }
        int nxt(int x){
            return rnk(kth(x+1));
        }
    }bt;
    void modify(int x,int size){
        int pre=bt.pre(x),nxt=bt.nxt(x);
        st.modify(1,1,size,pre+1,x,x-pre);
        st.modify(1,1,size,x+1,nxt,nxt-x);
        bt.add(x);
    }
    int ask(){
        return st.ask();
    }
};
signed main(){
	w=read(),h=read(),n=read();
    DataStruct sw,sh;
    sw.st.t[1].n=w;
    sh.st.t[1].n=h;
    sw.bt.add(0);
    sh.bt.add(0);
    sw.bt.add(w);
    sh.bt.add(h);
    while(n--){
        char ch=getchar_s();
        int x=read();
        if(ch=='H')sh.modify(x,h);
        else sw.modify(x,w);
        print(sh.ask()*sw.ask());
        putchar('\n');
    }
	return 0;
}

```

### 后记

注意这代码在我本地机子上跑不过（RE），在线是能过的。（因为这个调了快 2h）

参考时间复杂度 $O(n \log n)$，实际大概在 500 ms 左右。

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
本题使用 `multiset<>`，注意：因为 $2 \leq w,h \leq 200000$，并且 $200000 \times 200000 > 2^{31}$，有些还要开 `long long`，不然会炸掉的。为了记录每一次切割，我们就要定义这些：

```cpp
multiset<long long> x, V;  //前者 x 用于记录所有长的分段，后者 V 用于记录场上所有切割点。
multiset<long long> y, H;  //前者 y 用于记录所有长的分段，后者 H 用于记录场上所有切割点。
```

然后再每次切割时：

+ 找到切割点 $mid$ 靠近两旁的两个点 $l$ 和 $r$。因为一刀下去，玻璃绝对有一段变成两份了，所以现在要擦除 $r-l$ 的一段，换成 $r - mid$ 和 $mid - l$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long w, h, n;
char ch;
long long mid;
multiset<long long> x, V;  //前者 x 用于记录所有长的分段，后者 V 用于记录场上所有切割点。
multiset<long long> y, H;  //前者 y 用于记录所有长的分段，后者 H 用于记录场上所有切割点。
int main() {
  cin >> w >> h >> n;  //长 高 次数

  // 记录有哪几段（长度）：
  x.insert(w);
  y.insert(h);

  // 记录收尾点（也算上切割）：
  V.insert(0);
  V.insert(w);
  H.insert(0);
  H.insert(h);

  // 接受切割：
  while (n--) {
    long long l, r;
    cin >> ch >> mid;
    if (ch == 'H') {
      H.insert(mid);
      auto it = H.lower_bound(mid);  //获取该在高上的切割点位置。
      it--;                          //该点的上一点。
      l = *it;                       //记录上一点位置。
      it++;                          //返回该点。
      it++;                          //该点的下一点。
      r = *it;                       //记录下一点位置。

      // 用位置差得出主要切割点会改变的长度：
      it = y.lower_bound(r - l);

      //擦除并且更新长度，因为一刀下去，玻璃绝对有一段变成两份了：
      y.erase(it);
      y.insert(r - mid);
      y.insert(mid - l);
    } else {
      // 意思与高的方法差不多：
      V.insert(mid);
      auto it = V.lower_bound(mid);
      it--;
      l = *it;
      it++;
      it++;
      r = *it;
      it = x.lower_bound(r - l);
      x.erase(it);
      x.insert(r - mid);
      x.insert(mid - l);
    }

    // 因为 multiset 是排了序的，所以分别只要找最后面的两个最大长度就能算出最大面积：
    long long VV, HH;
    auto it = x.end();
    it--;
    VV = *it;
    it = y.end();
    it--;
    HH = *it;
    cout << VV * HH << "\n";
  }
  return 0;
}
```

---

## 作者：kdy20100729 (赞：0)

### 题意简述  
切割一块 $W \times H$ 的玻璃，```H``` 表示横着切，```V``` 表示竖着切。问每次切割后最大的那块玻璃有多大。  
### 思路  
```cpp
multiset<long long> x,y;
```  
用 $x$ 存所有碎片的宽，$y$ 存所有碎片的高。  
```cpp
multiset<long long> lx,ly;
```  
用 $lx$ 存竖着（```V```）切的位置，$ly$ 存横着（```H```）切的位置。

每次循环时：  
>+ 如果输入的是 $V$，$pos$。  
>假如我们竖着切 $pos$ 这个位置。 那么我们直接 ```lx.insert(pos)```。然后找到 $pos$ 小和比 $pos$ 大的两个位置 $l$,$r$，显然我们是切割 $x$ 中边界 $l$,$r$ 的玻璃，它们的宽为 $r-l$。  
>+ 如果输入的是 $H$，$pos$。  
>同理。每次切割一次，都会删除一个 $x$ 或者 $y$ 中的一个宽度或者高度，然后产生两个新的宽度或者高度。  

### 奉上蒟蒻的 $AC$ 代码:  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int w,h,n;
multiset<int> x,y,lx,ly;//存储所有碎片的边长、切割的位置 
multiset<int>::iterator it;
signed main()
{
	cin >> w >> h >> n;//最开始是一整块玻璃
	x.insert(w);
	y.insert(h);
	lx.insert(0);
	lx.insert(w);
	ly.insert(0);
	ly.insert(h);
	while(n--)
	{
		char ch;
		int pos;
		cin >> ch >> pos;
		if (ch=='H')
		{
			int l,r;
			ly.insert(pos);
			it=ly.find(pos);
			it--;//找到pos前一个切割位置
			l=*it;
			it++;
			it++;//找到pos后一个切割位置
			r=*it;//删除一个高度r-l，增加两个新高度
			it=y.find(r-l);
			y.erase(it);
			y.insert(r-pos);
			y.insert(pos-l);
		}
		else
		{
			int l,r;
			lx.insert(pos);
			it=lx.find(pos);
			it--;//找到pos前一个切割位置
			l=*it;
			it++;
			it++;//找到pos后一个切割位置
			r=*it;//删除一个宽度r-l，增加两个新宽度
			it=x.find(r-l);
			x.erase(it);
			x.insert(r-pos);
			x.insert(pos-l);
		}
		int r,c;
		it=x.end();
		it--;
		r=*it;
		it=y.end();
		it--;
		c=*it;
		cout << r*c << "\n";
	}
	return 0;
}
```

---

## 作者：jins3599 (赞：0)

敲+调试了一个小时...码力还是不行啊..

首先做法是很明确的，分别在$x$轴和$y$轴上维护一颗线段树，线段树中$1$代表切断，于是问题转化成了最长的一串$0$.

对于线段树中的结点，我们维护下面几个信息：

- 左边最长的连续零序列
- 右边最长的连续零序列
- 中间最长的连续零序列

然后我们的难点在于设计`pushup`

我们每次`pushup`的时候，先继承左儿子的左最长，然后再看左儿子的左最长是否是整个序列，若是的话再加上右儿子的左最长。

右最长和中间最长同理。

于是这道题就变成了码农题，

~~我才不会告诉你们我因为忘了开`long long`调了十多分钟~~

(于是就暴躁的`#define int long long`)

$Code:$

```cpp
#include <bits/stdc++.h>
#define ls(x) x << 1
#define rs(x) x << 1 | 1 
#define int long long

using namespace std;

const int N = 200000 + 5;
int w , h , m;

struct Seg {
	int l , r , len;
	int lft , rgt , mid;
	int ld , rd;
}t[2][N << 2];

void pushup_0(int x) {
	t[0][x].ld = t[0][ls(x)].ld; t[0][x].rd = t[0][rs(x)].rd;
	t[0][x].lft = t[0][ls(x)].lft;
	if(t[0][ls(x)].lft == t[0][ls(x)].len && t[0][ls(x)].rd == t[0][rs(x)].ld)
		t[0][x].lft += t[0][rs(x)].lft;
	t[0][x].rgt = t[0][rs(x)].rgt;
	if(t[0][rs(x)].rgt == t[0][rs(x)].len && t[0][rs(x)].ld == t[0][ls(x)].rd)
		t[0][x].rgt += t[0][ls(x)].rgt;
	t[0][x].mid = max(t[0][ls(x)].mid , t[0][rs(x)].mid);
	if(t[0][ls(x)].rd == t[0][rs(x)].ld && t[0][ls(x)].rd == 0) 
		t[0][x].mid = max(t[0][x].mid , t[0][ls(x)].rgt + t[0][rs(x)].lft);
}
void pushup_1(int x) {
	t[1][x].ld = t[1][ls(x)].ld; t[1][x].rd = t[1][rs(x)].rd;
	t[1][x].lft = t[1][ls(x)].lft;
	if(t[1][ls(x)].lft == t[1][ls(x)].len && t[1][ls(x)].rd == t[1][rs(x)].ld)
	t[1][x].lft += t[1][rs(x)].lft;
	t[1][x].rgt = t[1][rs(x)].rgt;
	if(t[1][rs(x)].rgt == t[1][rs(x)].len && t[1][rs(x)].ld == t[1][ls(x)].rd)
	t[1][x].rgt += t[1][ls(x)].rgt;
	t[1][x].mid = max(t[1][ls(x)].mid , t[1][rs(x)].mid);
	if(t[1][ls(x)].rd == t[1][rs(x)].ld && t[1][ls(x)].rd == 0) 
	t[1][x].mid = max(t[1][x].mid , t[1][ls(x)].rgt + t[1][rs(x)].lft);
}
void built_0 (int x ,int l , int r){
	t[0][x].l = l , t[0][x].r = r;
	t[0][x].len = r - l + 1;
	if(l == r) {
		t[0][x].ld = t[0][x].rd = 0;
		t[0][x].lft = t[0][x].rgt = t[0][x].mid = 1;
		return;
	}
	int mid = l + r >> 1;
	built_0(ls(x) , l , mid);
	built_0(rs(x) , mid + 1 , r);
	pushup_0(x);
}

void built_1 (int x ,int l , int r){
	t[1][x].l = l , t[1][x].r = r;
	t[1][x].len = r - l + 1;
	if(l == r) {
		t[1][x].ld = t[1][x].rd = 0;
		t[1][x].lft = t[1][x].rgt = t[1][x].mid = 1;
		return;
	}
	int mid = l + r >> 1;
	built_1(ls(x) , l , mid);
	built_1(rs(x) , mid + 1 , r);
	pushup_1(x);
}

void updata_0(int x , int p) {
	if(t[0][x].l == t[0][x].r) {
		t[0][x].ld = t[0][x].rd = 1;
		t[0][x].lft = t[0][x].rgt = t[0][x].mid = 0;
		return;
	}
	int mid = (t[0][x].l + t[0][x].r ) >> 1;
	if(p <= mid) updata_0(ls(x) , p);
	else updata_0(rs(x) , p);
	pushup_0(x);
}

void updata_1(int x , int p) {
	if(t[1][x].l == t[1][x].r) {
		t[1][x].ld = t[1][x].rd = 1;
		t[1][x].lft = t[1][x].rgt = t[1][x].mid = 0;
		return;
	}
	int mid = (t[1][x].l + t[1][x].r ) >> 1;
	if(p <= mid) updata_1(ls(x) , p);
	else updata_1(rs(x) , p);
	pushup_1(x);
}

int query() {
	int ans1 = 0 , ans2 = 0;
	ans1 = max(t[0][1].mid , max(t[0][1].lft , t[0][1].rgt)) + 1;
	ans2 = max(t[1][1].mid , max(t[1][1].lft , t[1][1].rgt)) + 1;
	return ans1 * ans2;
}

signed main () {
	ios::sync_with_stdio(false);
	cin >> w >> h >> m;
	built_0(1 , 1 , w - 1);
	built_1(1 , 1 , h - 1);

	while(m -- ) {
		char opt; int aim;
		cin >> opt >> aim;
		if(opt == 'V') {
			updata_0(1 , aim);
			cout << query() << endl;
		} else {
			updata_1(1 , aim);
			cout << query() << endl;
		}
	}
	return 0;
}
```

---

## 作者：lvjiyuan (赞：0)

新手来一发线段树的题解，才四十行。玻璃是矩形的，即矩形面积=长边最大边 * 短边最大边；那么我们可不可以只考虑它的上边和左边？假设上边长于左边（反之同理）。那么把矩形从上到下拍平了，让矩形面积最大的最长边是不是就是上边的最长边？从右往左拍扁了，矩形面积最大的最短边不就是左边的最长边吗？所以，我们只要用两棵线段树维护左边与上边的最大值即可。
```c
#include<bits/stdc++.h>//横是0，纵是1； 
#define lk (fat<<1)
#define rk (fat<<1|1)
#define ll long long
using namespace std;
const ll N=200005;
ll L[N<<2][2],R[N<<2][2],E[N<<2][2],M[2],w,h,n;
bool P[N<<2][2];
void push(ll l,ll r,ll fat,ll k)
{
    P[fat][k]=P[lk][k]&&P[rk][k];
    E[fat][k]=max(R[lk][k]+L[rk][k],max(E[lk][k],E[rk][k]));
    L[fat][k]=P[lk][k]==1?L[lk][k]+L[rk][k]:L[lk][k];
    R[fat][k]=P[rk][k]==1?R[rk][k]+R[lk][k]:R[rk][k];
}
void build(ll l,ll r,ll fat,ll k)
{
    if(l==r){L[fat][k]=R[fat][k]=E[fat][k]=1;P[fat][k]=true; return;}
    ll m=(l+r)>>1;
    build(l,m,lk,k); build(m+1,r,rk,k);
    push(l,r,fat,k);
}
void update(ll l,ll r,ll fat,ll k,ll num)
{
    if(l==r){	L[fat][k]=R[fat][k]=E[fat][k]=0;P[fat][k]=false;return ;}
    ll m=(l+r)>>1;
    if(num<=m)update(l,m,lk,k,num); else update(m+1,r,rk,k,num);
    push(l,r,fat,k);
    //cout<<num<<" "<<E[fat][k]<<"  L:"<<l<<" R:"<<r<<endl;
}
int main()
{
    cin>>w>>h>>n;
    build(1,w-1,1,0);build(1,h-1,1,1);
    for(ll i=1;i<=n;i++)
    {
        char sg;ll num;
        cin>>sg>>num;
        if(sg=='H')update(1,h-1,1,1,num);//横切影响纵行;
        if(sg=='V')update(1,w-1,1,0,num);//纵切影响横行;
        cout<<(E[1][0]+1)*(E[1][1]+1)<<endl;//<<"  w:"<<E[1][0]+1<<"  h:"<<E[1][1]+1
    }
    return 0;
}
```

---

## 作者：Kendrick_Z (赞：0)

弱鸡来写一波题解

大多数julao用的都是STL 然而我为了练习我的线段树采用了线段树的的写法

考虑一下我们每次横向或者是竖向切 对于另一个方向是没有影响的

（自己画图模拟下即可）

所以我们可以对行和列分别维护

我们对行和列分别维护一个01序列 然后我们找到以1为根节点的最大值就可以了

最后要加1因为我们的线段树维护的是距离

还有就是要注意的是我们横着切其实是对竖着的产生影响

竖着切会对横着产生影响

维护的时候不要维护反了

关于pushdown?

因为我们要维护的是一个连续01序列中连续0 考虑下以下几种情况？

1.在左边
2.在右边
3.左右可以连接上

那么我们就要在结构体维护一个从左边开始的最大 和从右边开始的最大

同时也要注意判断整部分区间是否满足 然后拼接

还是看代码比较好理解：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,q;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}   
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
} 
struct node{
	int lsum,rsum,sum,l,r;
}tree1[N<<1],tree2[N<<1];
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
inline void upd1(int p){
	int mid=(tree1[p].l+tree1[p].r)>>1;
	tree1[p].sum=max(tree1[ls(p)].sum,tree1[rs(p)].sum);
	tree1[p].sum=max(tree1[p].sum,tree1[ls(p)].rsum+tree1[rs(p)].lsum);
	tree1[p].lsum=tree1[ls(p)].lsum;
	if(tree1[ls(p)].lsum==mid-tree1[p].l+1){
	   tree1[p].lsum+=tree1[rs(p)].lsum;	//如果左儿子区间全都是 那么可以和右区间连接上							  
	}
	tree1[p].rsum=tree1[rs(p)].rsum;
	if(tree1[rs(p)].rsum==tree1[p].r-mid){
	   tree1[p].rsum+=tree1[ls(p)].rsum;	//如果右儿子区间全都是 那么可以和左区间连接上							  
	}
}
inline void upd2(int p){
    int mid=(tree2[p].l+tree2[p].r)>>1;
	tree2[p].sum=max(tree2[ls(p)].sum,tree2[rs(p)].sum);
	tree2[p].sum=max(tree2[p].sum,tree2[ls(p)].rsum+tree2[rs(p)].lsum);
	tree2[p].lsum=tree2[ls(p)].lsum;
	if(tree2[ls(p)].lsum==mid-tree2[p].l+1){
	   tree2[p].lsum+=tree2[rs(p)].lsum;	//如果左儿子区间全都是 那么可以和右区间连接上							  
	}
	tree2[p].rsum=tree2[rs(p)].rsum;
	if(tree2[rs(p)].rsum==tree2[p].r-mid){
	   tree2[p].rsum+=tree2[ls(p)].rsum;	//如果右儿子区间全都是 那么可以和左区间连接上							  
	}   
}
inline void build1(int l,int r,int p){
	tree1[p].lsum=tree1[p].sum=tree1[p].rsum=r-l+1;
	tree1[p].l=l,tree1[p].r=r;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build1(l,mid,ls(p));
	build1(mid+1,r,rs(p));
	upd1(p);
}
inline void build2(int l,int r,int p){
    tree2[p].lsum=tree2[p].sum=tree2[p].rsum=r-l+1;
   	tree2[p].l=l,tree2[p].r=r;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build2(l,mid,ls(p));
	build2(mid+1,r,rs(p));
	upd2(p);
}
inline void change1(int l,int r,int p,int x){
	if(l==r){
		tree1[p].lsum=tree1[p].rsum=tree1[p].sum=0;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		change1(l,mid,ls(p),x);
	}
	else change1(mid+1,r,rs(p),x);
	upd1(p);
} 
inline void change2(int l,int r,int p,int x){
    if(l==r){
        tree2[p].lsum=tree2[p].rsum=tree2[p].sum=0;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		change2(l,mid,ls(p),x);
	}
	else change2(mid+1,r,rs(p),x);
	upd2(p);
}
signed  main(){
	n=read(),m=read(),q=read();
	build1(1,n-1,1);
	build2(1,m-1,1);
	while(q--){
		char ch[3];
		int k;
		scanf("%s",ch);
		k=read();
		if(ch[0]=='H'){
			change2(1,m-1,1,k);
		}
		else change1(1,n-1,1,k);
		printf("%lld\n",(tree1[1].sum+1)*(tree2[1].sum+1)); 
	}
	return 0;
}
```


虽然代码特别长100+行，但是其实就是复制一份 实际也就是几十行的代码量



---

