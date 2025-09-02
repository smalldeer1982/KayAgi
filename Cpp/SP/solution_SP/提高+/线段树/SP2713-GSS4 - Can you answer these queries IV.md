# GSS4 - Can you answer these queries IV

## 题目描述

You are given a sequence A of N(N <= 100,000) positive integers. There sum will be less than 10 $ ^{18} $ . On this sequence you have to apply M (M <= 100,000) operations:

(A) For given x,y, for each elements between the x-th and the y-th ones (inclusively, counting from 1), modify it to its positive square root (rounded down to the nearest integer).

(B) For given x,y, query the sum of all the elements between the x-th and the y-th ones (inclusively, counting from 1) in the sequence.

## 样例 #1

### 输入

```
5
1 2 3 4 5
5
1 2 4
0 2 4
1 2 4
0 4 5
1 1 5
4
10 10 10 10
3
1 1 4
0 2 3
1 1 4```

### 输出

```
Case #1:
9
4
6

Case #2:
40
26```

# 题解

## 作者：BFqwq (赞：17)

# 题解GSS4
（管理大大能不能给过啊，前面的题解一篇都没过。。。）
## 思考
数据范围：1e5

一眼望去，这个题似乎是个数据结构题

再一看求和

于是，我们就想到了线段树

（我超级喜欢线段树嘻嘻）

（我相信各位巨佬应该都会线段树吧，这儿我就不再赘述了）

不会的同学们可以移步[这边](https://www.luogu.org/problem/P3372)

## 维护
那么，我们该怎么维护呢

由于考虑到sqrt是个常数挺大的运算，且又不能叠加

那不就变成O（n）了吗。。。

（绝对不行！！！）
## 亮点
那么接下来，就是这题的重点了

（敲黑板）


我们想到，一个点如果是1或者0，那么这个点的开根是没有意义的

而即使是一个1e9，在经过不到10次开根后也会变成1！！！

（有了这一点我们就可以开心的写题啦）

## 正解

在维护sum的同时，我们再维护一个tag

要是这个点是1或者0，那么tag就等于1

在维护的时候，只要左右子节点的tag都等于1时，这个点的tag就等于1

于是我们就通过这道紫题啦！！！

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=100005;
struct _{
	int sum;
	bool tag;
}t[maxn<<2];
int a[maxn],n,m;
void pushup(int o){
	t[o].sum=t[o<<1].sum+t[o<<1|1].sum;
	if(t[o<<1].tag && t[o<<1|1].tag) t[o].tag=1;
	else t[o].tag=0;
}
void build(int o,int l,int r){
	if(l==r){
		t[o].sum=a[l];
		if(a[l]==0 || a[l]==1) t[o].tag=1;
		else t[o].tag=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pushup(o);
}
void change(int o,int l,int r,int ql,int qr){
	if(l==r){
		t[o].sum=sqrt(t[o].sum);
		if(t[o].sum==0 || t[o].sum==1) t[o].tag=1;
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid && !t[o<<1].tag) change(o<<1,l,mid,ql,qr);
	if(qr>mid && !t[o<<1|1].tag) change(o<<1|1,mid+1,r,ql,qr);
	pushup(o);
}
int query(int o,int l,int r,int ql,int qr){
	if(ql<=l && qr>=r) return t[o].sum;
	int mid=(l+r)>>1;
	int res=0;
	if(ql<=mid) res+=query(o<<1,l,mid,ql,qr);
	if(qr>mid) res+=query(o<<1|1,mid+1,r,ql,qr);
	return res;
}
signed main(){
	int _case=0;
	while(~scanf("%d",&n)){
		printf("Case #%d:\n",++_case);
		memset(a,0,sizeof(a));
		memset(t,0,sizeof(t));
		for(int i=1;i<=n;i++) a[i]=read();
		build(1,1,n);
		m=read();
		while(m--){
			int opt=read(),l=read(),r=read();
			if(l>r) swap(l,r);
			if(opt==0) change(1,1,n,l,r);
			else printf("%lld\n",query(1,1,n,l,r));
		}
		puts("");
	}
	return 0;
} 
```

























---

## 作者：VenusM1nT (赞：12)

线段树。~~一开始以为分块可以过，因为 `Hzwer 之数列分块入门 5` 的操作就是区间开方和区间和，不过显然，放到这道题会 $\text{T}$ 上天，不信邪的笔者在各种卡常无果后还是放弃了分块。~~

~~分块代码如下。~~

UPD on 2.22

在 @codesonic julao 的提醒下发现，没有考虑 $x>y$ 的情况……但修改后依然不能在 C++ 环境下通过，但使用 C++11 （或卡卡常）可以 AC。

分块还是要比线段树慢上一些的。

（代码已修改）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200005
using namespace std;
int n,m,unt,pos[MAXN];
ll sum[MAXN],val[MAXN];
bool fg[MAXN];
template <typename T> void Read(T &x)
{
    int fu=1;
    x=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
    x*=fu;
}
void ModifyBlock(int x)
{
	if(fg[x]) return;
	fg[x]=1;
	sum[x]=0;
	for(int i=(x-1)*unt+1;i<=x*unt;i++)
	{
		val[i]=sqrt(val[i]);
		sum[x]+=val[i];
		if(val[i]>1) fg[x]=0;
	}
}
void Modify(int l,int r)
{
	for(int i=l;i<=min(pos[l]*unt,r);i++)
	{
		sum[pos[l]]-=val[i];
		val[i]=sqrt(val[i]);
		sum[pos[l]]+=val[i];
	}
	if(pos[l]!=pos[r])
	{
		for(int i=(pos[r]-1)*unt+1;i<=r;i++)
		{
			sum[pos[r]]-=val[i];
			val[i]=sqrt(val[i]);
			sum[pos[r]]+=val[i];
		}
	}
	for(int i=pos[l]+1;i<=pos[r]-1;i++) ModifyBlock(i);
}
ll Query(int l,int r)
{
	ll res=0;
	for(int i=l;i<=min(pos[l]*unt,r);i++) res+=val[i];
	if(pos[l]!=pos[r]) for(int i=(pos[r]-1)*unt+1;i<=r;i++) res+=val[i];
	for(int i=pos[l]+1;i<=pos[r]-1;i++) res+=sum[i];
	return res;
}
int main()
{
	int Case=0;
	while(~scanf("%d",&n))
	{
		printf("Case #%d:\n",++Case);
		memset(sum,0,sizeof(sum));
		memset(fg,0,sizeof(fg));
		unt=sqrt(n);
		for(int i=1;i<=n;i++) Read(val[i]);
		for(int i=1;i<=n;i++)
		{
			pos[i]=(i-1)/unt+1;
			sum[pos[i]]+=val[i];
		}
		Read(m);
		while(m--)
		{
			int opt,x,y;
			Read(opt);
			Read(x);
			Read(y);
            if(x>y) swap(x,y);
			if(!opt) Modify(x,y);
			else printf("%lld\n",Query(x,y));
		}
		puts("");
	}
	return 0;
}
```

~~既然分块不行，那就只能用线段树了。~~

区间和首先不管，来考虑最难搞的区间开方，容易想到的是对 $sum$ 进行开方，但是仔细一想就知道，**开方和** 和 **和开方** 的结果绝对是不一样的，似乎只有暴力这一条路可走了。

此时拿出计算器算算，$1e18$ 在开方仅仅 $6$ 次下取整后就已经变成了 $1$，这意味着一个区间最多只会被开方 $6$ 次，极限复杂度不过 $\text{O}(6e5)$，似乎非常可做。因为一个区间被开方多次之后一定会全部变成 $1$，所以我们记录一下区间最大值，如果区间最大值小于等于 $1$ 的话，意味着这个区间已经开方完成了，没有必要再开了（因为全是 $1$，$\sqrt{1}=1$），于是就不用往里搜了，这样可以省去大量的时间复杂度。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 100005
using namespace std;
int n,m;
ll a[MAXN],t[MAXN<<2],maxn[MAXN<<2];
void PushUp(int rt)
{
	t[rt]=t[rt<<1]+t[rt<<1|1];
	maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
}
void BuildSegmentTree(int rt,int l,int r)
{
	if(l==r)
	{
		t[rt]=maxn[rt]=a[l];
		return;
	}
	int mid=l+r>>1;
	BuildSegmentTree(rt<<1,l,mid);
	BuildSegmentTree(rt<<1|1,mid+1,r);
	PushUp(rt);
}
void Modify(int rt,int l,int r,int tl,int tr)
{
	if(l==r)
	{
		t[rt]=sqrt(t[rt]);
		maxn[rt]=t[rt];
		return;
	}
	int mid=l+r>>1;
	if(tl<=mid && maxn[rt<<1]>1) Modify(rt<<1,l,mid,tl,tr);
	if(tr>mid && maxn[rt<<1|1]>1) Modify(rt<<1|1,mid+1,r,tl,tr);
	PushUp(rt);
}
ll Query(int rt,int l,int r,int tl,int tr)
{
	if(tl<=l && r<=tr) return t[rt];
	int mid=l+r>>1;
	ll res=0;
	if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
	if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
	return res;
}
int main()
{
	int Case=0;
	while(~scanf("%d",&n))
	{
		printf("Case #%d:\n",++Case);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		BuildSegmentTree(1,1,n);
		scanf("%d",&m);
		while(m--)
		{
			int opt,x,y;
			scanf("%d %d %d",&opt,&x,&y);
			if(x>y) swap(x,y);
			if(!opt) Modify(1,1,n,x,y);
			else printf("%lld\n",Query(1,1,n,x,y));
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Diamiko (赞：6)

区间问题最喜欢用线段树了，
线段树做此题非常方便。

首先考虑怎么应对区间开平方。本题的数据范围最大`1e18`，我们自己~~用计算器~~算一下就能算出来，`1e18`一直开平方（下取整），开到 1 也只需要6次，而 1 的算术平方根是 1  ， 0 的算术平方根是 0 ，那么我们就可以大胆考虑了。

对每次修改直接暴力进行单点修改就OK了啊？

每次判断，如果这个区间全是 1 或 0 ，那就不用管了， 反正再怎么改也是这样。

怎么判断是否全是 1 或 0 呢？只要判断一下区间和是否小于等于区间长度即可。

详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
ll sum[N<<2],n,m,k,l,r;
inline ll read()
{
	char c;ll res=0,flag=1;
	for(;!isdigit(c);c=getchar())if(c=='-')flag=-1;
	for(;isdigit(c);c=getchar())res=res*10+c-'0';
	return res*flag;
}
void build(int i,int l,int r)
{
	if(l==r)
	{
		sum[i]=read();
		return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	sum[i]=sum[i<<1]+sum[i<<1|1];
}

void modify(int i,int l,int r,int x,int y)
{
	if(sum[i]<=r-l+1)
		return;
	if(l==r)
	{
		sum[i]=sqrt(sum[i]);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) modify(i<<1,l,mid,x,y);
	if(y>mid)  modify(i<<1|1,mid+1,r,x,y);
	sum[i]=sum[i<<1]+sum[i<<1|1];
}

ll query(int i,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)return sum[i];
	int mid=l+r>>1;
	ll ans=0;
	if(x<=mid) ans+=query(i<<1,l,mid,x,y);
	if(y>mid)  ans+=query(i<<1|1,mid+1,r,x,y);
	return ans;
}
int cnt;
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		printf("Case #%d:\n",++cnt);
		build(1,1,n);
		m=read();
		while(m--)
		{
			k=read();
			l=read(),r=read();
			if(l>r)l^=r^=l^=r;
			if(!k) modify(1,1,n,l,r);
			else printf("%lld\n",query(1,1,n,l,r));
		}
		putchar('\n');
		memset(sum,0,sizeof sum);
	}
	return 0;
}
```

另外，[双倍经验](https://www.luogu.com.cn/problem/P4145)

---

## 作者：云浅知处 (赞：5)

这题其实和 [P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145) 那题差不多，都是区间 $\text{sqrt}$ 区间求和。

区间和不必多说。这里重点讲一下区间 $\text{sqrt}$ 的维护方法。

首先区间修改肯定第一反应懒标记+ `pushdown` 。

但是你会发现把区间内每个数开根号并不等价于把区间和开根号，也就是说懒标记基本不可维护。

那难道只能暴力修改了？

其实可以优化。

注意到 $\text{sqrt}$ 这个操作其实会把被开方的数减小一大截。就算是 $10^{18}$ 这种大数，顶多开六次根号并下取整就会变成 $1$。

而显然 $\left\lfloor\sqrt{1}\right\rfloor=1,\left\lfloor\sqrt{0}\right\rfloor=0$，也就是说，如果一个子区间内的数全都是 $1$ 或 $0$，那么对此区间的修改就会变得没有意义了，可以直接跳过。

当然你也可以维护一下每个数的被修改次数，然后如果次数 $\ge6$ 就不再修改。不过这样相对比较难写（？

至于怎么知道子区间内的数是否都是 $1$ 或 $0$，其实只需要在每个节点上维护一个 $\text{tag}$，在 $\texttt{pushup}$ 的时候把两个子节点的 $\text{tag}$ 取一个逻辑与运算即可。

------------

下面是代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<cstring>

#define MAXN 100005
#define lson(o) (o<<1)
#define rson(o) (o<<1|1)
#define LL long long

using namespace std;

LL a[MAXN],n,m;

struct Node{

	LL sum;
	bool f;//f 表示这个节点对应的区间内的数是否都是 0 或 1。 
	Node(LL _s,bool _f)
		:sum(_s),f(_f){}
	Node(){}
};

struct SMT{

	Node d[MAXN<<2];

	inline void pushup(LL o){
		d[o]=Node(d[lson(o)].sum+d[rson(o)].sum,d[lson(o)].f&d[rson(o)].f);
	}

	inline void build(LL l,LL r,LL o){
		if(l==r){
			d[o].sum=a[l];
			d[o].f=a[l]==0||a[l]==1;
			return ;
		}
		LL mid=(l+r)>>1;
		build(l,mid,lson(o));
		build(mid+1,r,rson(o));
		pushup(o);
	}

	inline void modify(LL l,LL r,LL ql,LL qr,LL o){
		if(d[o].f)return ;
		if(ql==qr){
			d[o].sum=floor(sqrt(d[o].sum));
			d[o].f=d[o].sum==1||d[o].sum==0;//判断区间内是否全是 1 或 0。 
			return ;
		}
		LL mid=(ql+qr)>>1;
		if(l<=mid)modify(l,r,ql,mid,lson(o));
		if(r>mid)modify(l,r,mid+1,qr,rson(o));
		pushup(o);
	}

	inline LL query(LL l,LL r,LL ql,LL qr,LL o){
		if(l<=ql&&qr<=r){
			return d[o].sum;
		}
		LL mid=(ql+qr)>>1;
		LL ans=0;
		if(l<=mid)ans+=query(l,r,ql,mid,lson(o));
		if(r>mid)ans+=query(l,r,mid+1,qr,rson(o));
		return ans;
	}
};

SMT tree;

int main(void){

	LL cnt=1;

	while(~scanf("%lld",&n)){
		memset(a,0,sizeof(a));
		memset(tree.d,0,sizeof(tree.d));
		printf("Case #%lld:\n",cnt++);
		for(LL i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}

		tree.build(1,n,1);

		scanf("%lld",&m);

		while(m--){
			LL opt,l,r;
			scanf("%lld%lld%lld",&opt,&l,&r);
			if(l>r)swap(l,r);//这一步记得加上qwq 
			if(opt==0){
				tree.modify(l,r,1,n,1);
			}
			else{
				printf("%lld\n",tree.query(l,r,1,n,1));
			}
		}

		puts("");
	}

	return 0;
}
```

---

## 作者：顾z (赞：4)

**题目大意**
  
  给定一个区间 支持**开方**和**查询区间值**操作
  **(多组数据**

**分析**

如果一个区间的最大值小于1,那就没有开方的必要了~~(具体不会证明,听大佬讲的~~

一个数经过多次开方就会变成1~~(可以用计算器试一下~~

因此我们维护一下区间最大值,维护一下区间和,对于一个区间的话,最大值开方后依旧为最大值,所以**对最大值以及区间和开方**即可。

由于是多组数据 所以需要每次**初始化**

可能分析与代码略有不同,思路是相同的

代码看不懂的来私信我吧~

[欢迎来玩](https://www.luogu.org/blog/RPdreamer/#)

------------------代码-------------------
```cpp
#include<bits/stdc++.h>
#define IL inline 
#define RI register int
#define ll long long
using namespace std;
ll n,m,t[400010],tg[400010];
ll cnt;
IL void up(ll o)
{
    t[o]=t[2*o]+t[2*o+1];
    tg[o]=max(tg[2*o],tg[2*o+1]);
    return;
}//维护区间最值的线段树 向上传递
IL void build(ll o,ll l, ll r)
{
    if(l==r)
    {
        scanf("%lld",&t[o]);
        tg[o]=t[o];
        return;
    }
    ll mid=l+r>>1;
    build(2*o,l,mid);
    build(2*o+1,mid+1,r);
    up(o);
    return;
}
IL void change(ll o,ll l,ll r,ll x,ll y)
{
    if(tg[o]<=1)return;//最大值小于等于1的不做处理
    if(l==r&&x<=l&&y>=r)
    {
        t[o]=sqrt(t[o]*1.0);
        tg[o]=t[o];
        return ;
    }
    ll mid=l+r>>1;
    if(x<=mid)change(2*o,l,mid,x,y);
    if(y>mid)change(2*o+1,mid+1,r,x,y);
    up(o);
    return;
}
IL ll query(ll o,ll l,ll r,ll x,ll y)
{
    if(x<=l&&y>=r)return t[o];
    ll mid=l+r>>1;
    ll re=0;
    if(x<=mid)re+=query(2*o,l,mid,x,y);
    if(y>mid)re+=query(2*o+1,mid+1,r,x,y);
    return re;
}
//操作和普通线段树差不多哦
int main()
{
    while(scanf("%lld",&n)!=EOF)
    {
    	printf("Case #%d:\n",++cnt);
    	memset(t,0,sizeof t);
		memset(tg,0,sizeof tg); 
	    build(1,1,n);
	    scanf("%lld",&m);
	    while(m--)
	    {
	        int k;
	        ll l,r;
	        scanf("%d%lld%lld",&k,&l,&r);
	        if(l>r)swap(l,r);
	        if(k==0)change(1,1,n,l,r);
	        else printf("%lld\n",query(1,1,n,l,r));
	    }
	}
}
```

---

## 作者：xcxc82 (赞：3)

# SP2713 GSS4  题解


## [间隙](https://www.luogu.com.cn/problem/SP2713)


## [双倍经验](https://www.luogu.com.cn/problem/P4145)

## 前置知识:线段树

如果您还不会线段树的话,推荐去看一下[**这篇文章**](https://www.cnblogs.com/jason2003/p/9676729.html),我一开始也是在那里学的

## 大致题意

给一堆数,有以下两个操作:

- 给出一个区间$[L,R]$,把该区间内的每个数都开平方

- 给出一个区间$[L,R]$,查询这个区间的每个数的和

## 分析
首先看一下这个数据范围,$1e18$,直接暴力的话肯定会T飞

求和操作很简单,相信学过线段树的人应该都会

难点在于这个开方操作,我们没法像线段树模板那样打个懒标记来进行下传操作

![](https://cdn.luogu.com.cn/upload/image_hosting/72ur96tc.png)

通过观察$\sqrt x$函数图像缓慢的增长率或者其他性质不难发现,很多开方操作是不必要的,考虑减枝优化:

- 不难发现,**当一个区间内的所有数都是$1$时,再对该区间进行开方操作对该区间内的总值造成不了任何改变**($\sqrt{1} = 1$)

因此代码实现方面只要在区间内总值均为1的情况下加一个小剪枝即可


------------


## 代码实现

思路理解了代码实现难度就不高了,但还是有几个坑点...具体的注释里有写

```cpp
#include<bits/stdc++.h>
#define lson (node<<1)//左儿子
#define rson (node<<1|1)//右儿子
#define ll long long 
#define int long long //记得开long long
using namespace std;
const int MAXN = 100005;
struct st{
	int l,r;//左右端点
	ll sum;
}tree[MAXN<<2];

ll a[MAXN];
int n,m;
void pushup(int node){
	tree[node].sum = tree[lson].sum + tree[rson].sum;//合并操作
}
void build(int node,int l,int r){//建树
	tree[node].l = l;
	tree[node].r = r;
	if(l==r){
		tree[node].sum = a[l];
		return;
	}
	int mid = (l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(node);
}
void change(int node,int l,int r){
	int L = tree[node].l,R = tree[node].r;
	if(tree[node].sum==R-L+1) return;//如果总和为区间长度,也就是所有值均为1时,直接剪枝掉
	if(L==R){
		tree[node].sum = sqrt(tree[node].sum);
		return;
	}
	int mid = (L+R)>>1;
	if(l<=mid){
			change(lson,l,r);
	}
	if(r>mid){
			change(rson,l,r);
	}
	pushup(node);
}
ll query(int node,int l,int r){//查询
	int L = tree[node].l,R = tree[node].r;
	if(l<=L&&r>=R){//包含在查询区间内,直接返回sum值
		return tree[node].sum;
	}
	int mid = (L+R)>>1;
	ll ans = 0;
	if(l<=mid){
		ans+=query(lson,l,r);
	}
	if(r>mid){
		ans+=query(rson,l,r);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);//不加貌似会TLE?
    cin.tie(0);
    cout.tie(0);
	int Case=0;
	while(cin>>n){
	printf("Case #%d:\n",++Case);//注意,样例里那个case是要输出的,一开始被这里卡了好久...
	memset(a,0,sizeof(a));//记得要先memset
	memset(tree,0,sizeof(tree));
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	cin>>m;
	while(m--){
		int mode,left,right;
		cin>>mode>>left>>right;
		if(left > right){
			swap(left,right);
		}
		if(mode==0){
			change(1,left,right);
		}
		else{
			printf("%lld\n",query(1,left,right));
		}
	 }
	 puts("");//记得换行
	}
	
}
```















---

## 作者：lhm_ (赞：3)

用计算器算一算，就可以发现$10^{18}$的数，被开方$6$次后就变为了$1$。

所以我们可以直接暴力的进行区间修改，若这个数已经到达$1$，则以后就不再修改（因为$1$开方后还是$1$），用并查集和树状数组进行维护。

这个方法用了[P2391 白雪皑皑](https://www.luogu.org/problem/P2391)的思想处理，用并查集标记该点已经不再用替换。

和我这题[CF920F【SUM和REPLACE】](https://www.luogu.org/blog/lhm126/solution-cf920f)的方法相同。


$code$:
```cpp
#include<bits/stdc++.h>
#define maxn 500010
#define lowbit(x) (x&(-x))
typedef long long ll;
using namespace std;
ll n,m;
ll fa[maxn],k,l,r;
ll a[maxn],tree[maxn];
int cnt;
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void add(int x,ll d)
{
	while(x<=n)
	{
		tree[x]+=d;
		x+=lowbit(x);
	}
}
ll query(int x)
{
	ll sum=0;
	while(x)
	{
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}
int main()
{
	while(scanf("%lld",&n)!=EOF)
	{
		cnt++;
		printf("Case #%d:\n",cnt);
		for(int i=1;i<=n*4;++i)
		tree[i]=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%lld",&a[i]);
			add(i,a[i]);
			fa[i]=i;
		}
		fa[n+1]=n+1;
		scanf("%lld",&m);
		while(m--)
		{
			scanf("%lld%lld%lld",&k,&l,&r);
			if(l>r)
			swap(l,r);
			if(k==0)
			{
				for(int i=l;i<=r;)
				{
					add(i,(ll)sqrt(a[i])-a[i]);//手动暴力开方
					a[i]=(ll)sqrt(a[i]);
					if(a[i]<=1)
					fa[i]=i+1;//若这个数已经为1，则将其指向它下一个数	
					if(i==find(i))
					i++;
					else
					i=fa[i];//进行跳转，忽略不再需要开方的数
				}
			}
			else
			printf("%lld\n",query(r)-query(l-1));
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：ADay (赞：3)

[更好的阅读体验](https://aday526.github.io/%E9%A2%98%E8%A7%A3%20SP2713%20%E3%80%90GSS4%20-%20Can%20you%20answer%20these%20queries%20IV%E3%80%91/)

这里详细讲一下需要`C++11`才能过的分块做法​  


## $\mathcal{S}olution$

对于每个块，我们要维护两个东西：`sum,flag​`  

`sum`就是每个块的和，`flag`是块中每个数是否都为$0/1$    

维护`flag`的意义在于：**是否还要继续暴力开方**  

那么就涉及到操作了：在**[**$l,r$**]**之间的区间操作  

### 区间求和

在靠近$l$和$r$的两边，如果有不完整的块，我们直接暴力求和，而中间完整的块，直接加上`sum[块的编号]`即可  

先说一下变量的作用，以便更好理解以下代码:

- $n:$元素个数 
- $m:$操作数
- $num:$块的个数，即$\sqrt n$ 
- $a_i:$原数组
- $bl_i:$第$i$个元素属于第$bl_i$个块，$bl$是$belong$的缩写
- $sum_i:$第$i$块的和
- $flag_i:$第$i$块中每个数是否都为$0/1$ 

这部分的代码如下：  

```cpp
inline ll question(int x,int y)
{
    rg ll res=0;
    for(rg int i=x;i<=bl[x]*num&&i<=y;i++)
        res+=a[i];//左边不完整的块
    if(bl[x]!=bl[y])
        for(rg int i=(bl[y]-1)*num+1;i<=y;i++)
            res+=a[i];//右边不完整的块
    for(rg int i=bl[x]+1;i<bl[y];i++)
        res+=sum[i];//中间完整的块
    return res;
}
```



### 区间开方

对于不完整的块，还是暴力，即$a_i$变成$\sqrt{a_i}$，也要更新$sum_{bl_i}$,变成$sum_{bl_i}-a_i+\sqrt{a_i}$.  

而对于完整的块，如果此块的$flag$为$true$了，就不再进行操作，不然还是暴力解决  

完整的块最多暴力开方$7$次，因为数据范围是$10^{18}$，而$(10^{18})^{(\dfrac{1}{2})^7}\approx1$，那么就可以放心暴力啦~  

代码如下:

```cpp
inline void _sqrt(int x)//处理完整的块
{
    if(flag[x])return;
    flag[x]=1;
    sum[x]=0;//注意更新sum
    for(rg int i=(x-1)*num+1;i<=x*num;i++)
    {//暴力
        sum[x]+=a[i]=sqrt(a[i]);
        if(a[i]>1)flag[x]=0;
    }
}

inline void upd(int x,int y)
{
    //左边不完整的块
    for(rg int i=x;i<=bl[x]*num&&i<=y;i++)
        sum[bl[i]]-=a[i],a[i]=sqrt(a[i]),sum[bl[i]]+=a[i];
    //右边不完整的块
    if(bl[x]!=bl[y])
        for(rg int i=(bl[y]-1)*num+1;i<=y;i++)
            sum[bl[i]]-=a[i],a[i]=sqrt(a[i]),sum[bl[i]]+=a[i];
    //中间完整的块
    for(rg int i=bl[x]+1;i<bl[y];i++)
        _sqrt(i);
}
```

这样看来复杂度貌似是$\mathcal O(T\times m\sqrt n)$，但在`C++11`的~~玄学~~帮助下轻松过掉

---

## 作者：Na2PtCl6 (赞：2)

## 分析题目
此题是区间开方的模板题。

### 错误解法

第一眼看，一般人会尝试用懒标记开方，但很快就会发现这是错的，为什么呢？

我们维护的是区间的和，而对这个和进行开方没有任何意义，所以就只能另辟蹊径了。

### 正确解法

那就用暴力罢，但裸暴力肯定过不去，需要优化。

我们通过读题可以发现：$a_i \le10^{18}$，而且是下取整，所以对 $a_i$ 进行开方若干次后， $a_i$ 就会变为 $1$ ，这个次数是非常有限的，可以作为常数忽略不计。

当 $a_i$ 等于 $1$ 时，再对它进行开方得到的结果还是 $1$，就等于是浪费了，所以我们要避免再次开方发生。

单点判断是否需要开方肯定是不行的。我们想到多次开方后，可能会出现大片的连续的 $1$，所以我们维护一个区间最大值，如果这个区间的最大数值是 $1$ 的话，就不用管了，剩下的暴力开方。

### 时间复杂度评估

时间复杂度为 $O((m-k)(logn)+(k+1)(nlogn))$ （$k$ 为一常数，大概是把 $10^{18}$ 变成 $1$ 经过的开方次数），忽略常数就是 $O(mlogn+nlogn)$

建树函数是 $O(nlogn)$ 的。

暴力修改的部分总共用时 $O(knlogn)$ 。也就是说一次修改中可能只有暴力修改，也可能有略过连续的 $1$，这里只讨论暴力的部分。线段树暴力修改是 $O(llogn)$ （$l$ 指的是暴力修改的区间的长度）的，零散的暴力修改拼凑在一起的区间长度共有大概 $kn$ ，故时间复杂度为 $O(knlogn)$。

略过连续的 $1$ 或查询区间和总共用时 $O((m-k)logn)$ 。因为略过连续的 $1$ 是通过检查区间实现的，检查的区间递归深度不会超过 $log_2n$ 层，查询区间和也差不多。查询以及略过的时间复杂度为 $O(logn)$，共进行了大概 $m-k$ 次，故时间复杂度为 $O((m-k)logn)$。

## 注意事项
相信大家都会开 `long long` 的，但是务必注意要考虑到所有可能会爆 `int` 的地方，比如 `max` 函数、询问函数等。

## 代码实现

建树
```cpp
void build(int l,int r,int node){
	if(l==r){
		tree[node]=maxi[node]=a[l];
		return ;
	}
	int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
	build(l,mid,lnode),build(mid+1,r,rnode);
	tree[node]=tree[lnode]+tree[rnode];
	maxi[node]=_max(maxi[lnode],maxi[rnode]);
}
```

修改
```cpp
void update(int l,int r,int node,int start,int end){
	if(l==r){
		maxi[node]=tree[node]=(LL)sqrt(tree[node]);
		return ;
	}
	int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
	if(start<=mid&&maxi[lnode]>1)
		update(l,mid,lnode,start,end);
	if(end>mid&&maxi[rnode]>1)
		update(mid+1,r,rnode,start,end);
	tree[node]=tree[lnode]+tree[rnode]; 
	maxi[node]=_max(maxi[lnode],maxi[rnode]);
}
```

询问
```cpp
LL query(int l,int r,int node,int start,int end){
	if(start<=l&&r<=end)
		return tree[node];
	int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
	LL sum=0;
	if(start<=mid)
		sum+=query(l,mid,lnode,start,end);
	if(end>mid)
		sum+=query(mid+1,r,rnode,start,end);
	return sum;
}
```

我看见很多大佬在右端点小于左端点时用了 `swap`，其实不用这样的

```cpp
read(op),read(L),read(R);
if(!op)
	update(1,n,1,L<R?L:R,L>R?L:R);
else{
	write(query(1,n,1,L<R?L:R,L>R?L:R));
	putchar('\n');
}
```

---

## 作者：Sunqi666 (赞：2)

### 易知 $1<\sqrt[2^{7}]{10^{18}}<2$（计算器算的）
### 且 $\sqrt{1}=1$
意思是一个数最多操作7次就可以变成$1$，且之后再进行操作的话数值也不会变。

所以我们再开一个线段树，记录下每个节点的两个孩子的最大值，如果都是$1$就不必要再进行修改了

并且每个数顶多修改7次，所以不用担心超时哦

下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,t[400001],ma[400001],k;
void build(ll o,ll l,ll r){
    if(l==r){scanf("%lld",&t[o]);ma[o]=t[o];return;}
    ll mid=l+r>>1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    t[o]=t[o<<1]+t[o<<1|1];
    ma[o]=max(ma[o<<1],ma[o<<1|1]);
}
void update(ll o,ll l,ll r,ll x,ll y){
    if(l==r){t[o]=sqrt(t[o]);ma[o]=t[o];return;}
    ll mid=l+r>>1;
    if(x<=mid&&ma[o<<1]>1)update(o<<1,l,mid,x,y);
    if(mid<y&&ma[o<<1|1]>1)update(o<<1|1,mid+1,r,x,y);
    t[o]=t[o<<1]+t[o<<1|1];
    ma[o]=max(ma[o<<1],ma[o<<1|1]);
}
ll query(ll o,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y)return t[o];
    ll mid=l+r>>1,ans=0;
    if(x<=mid)ans=query(o<<1,l,mid,x,y);
    return mid<y?ans+query(o<<1|1,mid+1,r,x,y):ans;
}
int main(){
    ll tot=1;
    while(scanf("%lld",&n)!=EOF){
        printf("Case #%lld:\n",tot++);
        build(1,1,n);
       	scanf("%lld",&m);
       	while(m--){
       		ll x,y;
    	   	scanf("%lld%lld%lld",&k,&x,&y);
       		if(k)printf("%lld\n",query(1,1,n,min(x,y),max(x,y)));//输入有坑
       		else update(1,1,n,min(x,y),max(x,y));
    	}
    	printf("\n");//看输出样例，这里要换行
    }
}
```

---

## 作者：___new2zy___ (赞：2)

## 题解 SP2713 【GSS4 - Can you answer these queries IV】

题目传送门:

https://www.luogu.org/problemnew/show/SP2713

=========================================

~~（先瞎扯两句= =）~~

1.原本以为这题很水的，其实不然，还是比较脑洞的

2.我说这题是个**重题**你信么= =

**双倍经验**：

https://www.luogu.org/problemnew/show/P4145

p4145 上帝造题的七分钟2/花神游历各国

（虽然说这题的数据比较强，不算重题吧= =）

==========================================

对于这个题，我看见题目之后就去搜了一下= =

发现GSS4-Can you answer these queries竟然是一套完整的数据结构~~（毒瘤）~~题，考虑一下先从这题开始做起，以后可能会陆续做完其他的题吧

好了不扯了，开始讲解：

既然是个数据结构题，那么一定要向数据结构上想

首先可以想到一个很容易懂的东西：

	对于一个数（这里指1e9以内的数），经过连续开方6次就会变成1

（不信的小伙伴可以自己手动试一下）


以后无论怎么操作都是1 !!!

那么有了这个认识，我们不妨这样考虑：

**如果一个区间的最大值都为1，那么是不是对于整个区间都不用操作呢**

**正确性显然，因为如果整个区间最大值是1，那么整个区间显然都是1，那么1怎么开方都是1**

有了这个想法，再加上不怕WA~~死~~的精神，我们不妨把它推广到本题上来

（不就是数据变成了1e18么，不是太大吧）（逃

做法如下：

建立一颗**线段树**，维护**区间最大值**和**区间和**，

在进行**区间开方**操作时，**只需要判断一下区间最大值是否为1**，**如果为1那么不用操作，否则给区间和及区间最大值开方即可**

时间复杂度很正确，即使是数据大了一些

下面奉上代码code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define l_son p<<1
#define r_son p<<1|1
#define maxn 100003
using namespace std;
typedef long long ll;
const int inf=1e9+7;
inline ll read()
{
    ll p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return 1ll*f*p;}
struct Line_Segment_Tree  //定义线段树
{
    ll mx,value_;
}T[maxn<<2];
int n,m,L[maxn<<2],R[maxn<<2];
ll A[maxn];
inline ll max(ll a,ll b)
{
	return a>b?a:b;
}
inline void maintain(int p)//维护线段树信息 
{
	T[p].value_=T[l_son].value_+T[r_son].value_;
	T[p].mx=max(T[l_son].mx,T[r_son].mx);
}
inline void Build_(int p,int l,int r)//建树 
{
    L[p]=l,R[p]=r;
    if(l==r)
       {
       		T[p].value_=T[p].mx=A[l];
       		return ;
       }
    int mid=(l+r)>>1;
    Build_(l_son,l,mid),Build_(r_son,mid+1,r);
    maintain(p);
}
inline void change_(int p,int l,int r)//区间开方 
{
    if(L[p]==R[p])
    	{
    		T[p].mx=(ll)sqrt(T[p].mx);
    		T[p].value_=(ll)sqrt(T[p].value_);
			return ;
		}
    int mid=(L[p]+R[p])>>1;
    if(l<=mid&&T[l_son].mx>1)change_(l_son,l,r);
    if(r>mid&&T[r_son].mx>1)change_(r_son,l,r);
    maintain(p);
}
inline ll ask_(int p,int l,int r)//询问区间和 
{
    if(l<=L[p]&&r>=R[p])return T[p].value_;
    int mid=(L[p]+R[p])>>1;
	ll ans=0;
    if(l<=mid)ans+=ask_(l_son,l,r);
    if(r>mid)ans+=ask_(r_son,l,r);
    return 1ll*ans;
}
inline void Clean()//多组数据注意清空 
{
	memset(T,0,sizeof(T));
	memset(A,0,sizeof(A));
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
}
int main()
{
	int cas=0;
	while(scanf("%d",&n)!=EOF)
		{
			printf("Case #%d:\n",++cas);
			for(int i=1;i<=n;i++)A[i]=read();
    		Build_(1,1,n);//建树
			m=read();
    		while(m--)
        		{
        			int key_=read(),x=read(),y=read();
          		  if(x>y)swap(x,y);//题目要求 
					if(!key_)change_(1,x,y);//区间开方 
            		else if(key_==1)//询问区间和 
               			printf("%lld\n",ask_(1,x,y));
            	}
            printf("\n");//注意输出格式坑点,数据之间有回车 
			Clean();
		}
    return 0;
}
```
好了，到这里这题就结束了

小总结：线段树可以维护一些神奇的量，能使得一些看似困难的操作变得很简单，的确需要十分熟练地使用

最后推广一下我的blog:

https://www.luogu.org/blog/new2zy/

感谢阅读，拜拜~~~


---

## 作者：酒三两、 (赞：2)

看到水题却没有人发题解！我来水一下下

评分的时候好不走心啊

一看ctsc秒怂

原来就是一个裸的线段树加个小优化就解决啦

首先看题目 
emm 10的18次方 long long上限 大概在18到19次方之间 更接近19次方 

其实有一秒是想用double写的最后想了想是我没带脑叽
还听说大神用什么树套树 平衡树什么的 小萌新表示不会  
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;

const int MAXN=100005;
long long a[MAXN];
long long f[MAXN<<2];

long long read(long long &x)//因为第一次交超时了emm，特意加上快读最后发现bug好像出在维护上
{
    long long f=1;char ch=getchar();
    
    x=0;
    
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    
    }
    return x*f;
}

int readline(int &x)//没有任何亮点的读入优化
{
    int f=1;char ch=getchar();
    
    x=0;
    
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    
    return x*f;
}

void build(int root,int left,int right)//线段树常规操作
{
    if(left==right)
    {
        f[root]=a[left];//可以在这里读入！但是我懒得要死当然不会改了
        return;
    }
    
    int mid=(left+right)/2;
    
    build(2*root,left,mid);
    
    build(2*root+1,mid+1,right);
    
    f[root]=f[2*root]+f[2*root+1];
}

void update(int root,int left,int right,int qleft,int qright)
{
    int mid,ans,i;
    
    if(right-left+1==f[root])//！！！！！！！就是这里！这两行就是简短而又鸡汁的小优化
        return;
    
    if(left==right)
    {
    	f[root]=sqrt(f[root]);//作为小萌新只会加减的区间维护，然鹅前面的优化已经够卡入时限啦！200ms解决
		return;
	}
	
	mid=(left+right)/2;
    
    if(qleft<=mid)
    {
        update(2*root,left,mid,qleft,qright);
    }
    
    if(mid<qright)
    {
        update(2*root+1,mid+1,right,qleft,qright);
    }
    
    f[root]=f[root*2]+f[root*2+1];
}
long long query(int root,int left,int right,int qleft,int qright)//第二wa在这里写的int
{
    long long ans=0;
    
    if(qleft<=left&&right<=qright)
    {
        return f[root];
    }
    
    int mid=(left+right)/2;
    
    if(qleft<=mid)
    {
        ans=query(2*root,left,mid,qleft,qright);
    }
    
    if(mid<qright)
    {
        ans+=query(2*root+1,mid+1,right,qleft,qright);
    }
    
    return ans;
}
int main()
{
    int n,i,x,y,j,way,k=0,m;
    
    while(scanf("%d",&n)!=EOF)//各大OJ的常规操作 不多说
    {
    
        k++;
    
        printf("Case #%d:\n",k);
    
        for(i=1;i<=n;i++)
        {
            read(a[i]);//这里可以放在建树的时候读入
        }
    
        build(1,1,n);
    
        readline(m);
    
        for(i=1;i<=m;i++)
        {
    
            readline(way);readline(x);readline(y);
    
            if(y<x)//多看几眼题目
            {
                int b=x;
                x=y;
                y=b;
            }
    
            if(way==1)
            {
                //cout<<"afs"<<endl;
                printf("%lld\n",query(1,1,n,x,y));
            }
            else if(way==0)
            {
                update(1,1,n,x,y);
            }
        }
        
        printf("\n");//这输出格式绝了
    }
}

```

---

## 作者：StupidSeven (赞：1)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/SP2713)

## Analysis
板子题，维护一棵线段树，支持区间开方

## Solution
注意到数据$1e18$最多开方$6$次就会变成1，考虑维护一个区间最大值，如果小于等于$1$，就不修改此区间，毕竟没必要
```cpp
void Change(int index,int lson,int rson){
	if(tree[index].lson==tree[index].rson){
		tree[index].x=(int)sqrt(tree[index].x);
		tree[index].Max=(int)sqrt(tree[index].Max);
		return;
	}
	int mid=(tree[index].lson+tree[index].rson)>>1;
	if(lson<=mid&&tree[index<<1].Max>1) Change(index<<1,lson,rson);
	if(rson>mid&&tree[index<<1|1].Max>1) Change(index<<1|1,lson,rson);
	UpDate(index);
	return;
}
```
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define M 500010
#define int long long
inline int read(){
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=s*10+c-48;c=getchar();}
	return s*f;
}
struct SegTree{
	int lson,rson,x,Max;
}tree[M<<2];
int n,m,opt,u,v,tot,value[M];
void UpDate(int index){
	tree[index].x=tree[index<<1].x+tree[index<<1|1].x;
	tree[index].Max=max(tree[index<<1].Max,tree[index<<1|1].Max);
	return;
}
void BuildTree(int index,int lson,int rson){
	tree[index]=(SegTree){lson,rson};
	if(lson==rson){
		tree[index].x=tree[index].Max=value[lson];
		return;
	}
	int mid=(lson+rson)>>1;
	BuildTree(index<<1,lson,mid);
	BuildTree(index<<1|1,mid+1,rson);
	UpDate(index);
	return;
}
void Change(int index,int lson,int rson){
	if(tree[index].lson==tree[index].rson){
		tree[index].x=(int)sqrt(tree[index].x);
		tree[index].Max=(int)sqrt(tree[index].Max);
		return;
	}
	int mid=(tree[index].lson+tree[index].rson)>>1;
	if(lson<=mid&&tree[index<<1].Max>1) Change(index<<1,lson,rson);
	if(rson>mid&&tree[index<<1|1].Max>1) Change(index<<1|1,lson,rson);
	UpDate(index);
	return;
}
int Query(int index,int lson,int rson){
	if(lson<=tree[index].lson&&tree[index].rson<=rson)
		return tree[index].x;
	int mid=(tree[index].lson+tree[index].rson)>>1,ans=0;
	if(lson<=mid) ans+=Query(index<<1,lson,rson);
	if(rson>mid) ans+=Query(index<<1|1,lson,rson);
	return ans;
}
signed main(void){
	while(cin>>n){
		tot++;
		printf("Case #%lld:\n",tot);
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=n;i++) value[i]=read();
		BuildTree(1,1,n);
		m=read();
		while(m--){
			opt=read();u=read();v=read();
			if(u>v) swap(u,v);
			if(opt==0) Change(1,u,v);
			else printf("%lld\n",Query(1,u,v));
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Azazеl (赞：1)

>题目传送门: [$SP2713$](https://www.luogu.com.cn/problem/SP2713)  

第一眼我们还是会去想能不能像加法的线段树一样，打$lazy\ tag$,但很快我们就会否决掉，原因很简单:  
$$\sqrt{a+b}≠\sqrt{a}+\sqrt{b}$$  
那我们能不能把区间拆成单点修改呢?可能不能···吧?  

再从数据范围下手:   
>保证$\sum a \le 10^{18}$ 

好的，我们掏出计算器来看一看(均向下取整):
$$\sqrt{10^{18}}=10^9\ \ \sqrt{10^9}=31622\ \ \ \sqrt{31622}=177\ \ \ \sqrt{177}=13\ \ \ \sqrt{13}=3 \ \ \ \sqrt{3}=1···$$  
只需要$6$次，我们的$10^{18}$就可以被开到$1$,换句话说对每一个数的开方次数不会超过$6$次.  

现在，我们再拿这颗线段树顺便维护一下区间最大值，若区间最大值大于$1$,那么我们就不用修改了.  

(最大)时间复杂度:$O(6*(n+m)logn)$  

[$\mathcal{CODE}$](https://www.luogu.com.cn/paste/fc4kt7um)

---

## 作者：Karry5307 (赞：1)

### 题意

给一段正整数构成的区间，支持区间开平方以及询问区间和。

### 题解

考虑线段树，显然区间开平方是不能用$lazy\ tag$的，所以我们选择暴力修改。

先证明一个引理，区间最大值为$1$的区间进行修改是没有意义的。（这个证明算是补了一个坑）

证明：由于区间内所有数是正整数，所以区间最大值为$1$的区间内所有数均为$1$，而$\sqrt{1}=1$，故修改区间内的值没有意义，证毕。

于是我们考虑在修改区间时判断一下当前区间最大值是不是$1$，如果是，就没有修改的必要。如果这个节点的左右端点重合，直接修改即可，这样可以少修改许多修改了也没用的区间，至于查询还是一样的。

提醒大家有多组数据，**记得初始化**

[安利一下我的博客](https://karry5307.github.io/)

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=1e5+51;
struct SegmentTree{
    ll l,r,sum,maxn;
};
SegmentTree tree[MAXN<<2];
ll cnt,qcnt,op,l,r,ccnt;
ll num[MAXN];
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
inline void update(ll node)
{
    tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
    tree[node].maxn=max(tree[node<<1].maxn,tree[(node<<1)|1].maxn);
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r;
    if(l==r)
    {
        tree[node].sum=tree[node].maxn=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline void change(ll l,ll r,ll node)
{
    if(tree[node].maxn<=1)
    {
        return;
    }
    if(tree[node].l==tree[node].r)
    {
        tree[node].sum=tree[node].maxn=sqrt(tree[node].sum);
        return;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        change(l,r,node<<1);
    }
    if(r>mid)
    {
        change(l,r,(node<<1)|1);
    }
    update(node);
}
inline ll querySum(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node].sum;
    }
    ll mid=(tree[node].l+tree[node].r)>>1,res=0;
    if(l<=mid)
    {
        res+=querySum(l,r,node<<1);
    }
    if(r>mid)
    {
        res+=querySum(l,r,(node<<1)|1);
    }
    return res;
}
inline ll queryMax(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node].maxn;
    }
    ll mid=(tree[node].l+tree[node].r)>>1,res=0;
    if(l<=mid)
    {
        res=max(res,queryMax(l,r,node<<1));
    }
    if(r>mid)
    {
        res=max(res,queryMax(l,r,(node<<1)|1));
    }
    return res;
}
int main()
{
    while(scanf("%lld",&cnt)!=EOF)
    {
        printf("Case #%lld:\n",++ccnt);
        for(register int i=1;i<=cnt;i++)
        {
            num[i]=read();
        }
        create(1,cnt,1);
        qcnt=read();
        for(register int i=0;i<qcnt;i++)
        {
            op=read(),l=read(),r=read();
            if(l>r)
            {
                swap(l,r);
            }
            if(op)
            {
                printf("%lld\n",querySum(l,r,1));
            }
            else
            {
                if(queryMax(l,r,1)>1)
                {
                    change(l,r,1);
                }
            }
        }
        memset(num,0,sizeof(num));
        memset(tree,0,sizeof(tree));
        puts("");
    }
}
```

---

## 作者：pengyule (赞：0)

这是我自己的线段树入门博客，自认为写得很详细：[link](https://pengyule.github.io/post/xian-duan-shu-ru-men/)，不会线段树的同学可以参观一下:)。

这道题跟 loj 数列分块入门 5 是差不多的题目，但是线段树的效率会高一些，至少是在常数上减小了不少。

主要思路有下：

首先，我们应该意识到，一个正整数，被开方并下取整若干次后他会变成 $1$，而 $1$ 继续开方只会浪费我们的时间，因此到此就可以截止了。对于 $10^{18}$ 的数据范围，试一试可以发现，经过开方并下取整 $6$ 次后变成 $1$，那么可见在此基础上使用暴力是可以通过的。

那么线段树又有什么用？用来告诉我们这个区间是不是全部为 $1$ 了，即是不是可以不用操作这个区间了。

用 $book_k$ 表示编号 $k$ 的区间是（$1$）否（$0$）全部为 $1$。那么显然有，当 $book_{2k}=book_{2k+1}=1$ 时，$book_k$ 才为 $1$。每一次修改先传到每一个叶子结点，将其开方并考虑修改其 $book$，然后一步步 $pushup$ 上来，决定有哪些区间是不用修改的，把需要修改的区间分裂、修改叶子结点、整合，最终修改完毕。

关于 $book$ 的初始值，我们在建树的时候就把那些值为 $1$ 的叶子结点的 $book$ 设为 $1$，对于非叶子节点，那么根据儿子节点是不是都为 $1$ 来决定它的 $book$。

下面是完整代码。除以上思路外，有一点需要注意，就是你的函数名要小心不要撞关键字或者什么其他的稀奇古怪的问题，因为我如果把所有函数名前的“_”去掉有时就会出现 TLE 的状况:(。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
ll a[N],t[N],book[N];
int _case=0;
void _pushup(int k){
    t[k]=t[k<<1]+t[k<<1|1];
    book[k]=book[k<<1]&&book[k<<1|1];
}
void build(int l,int r,int k){
    if(l==r){
        t[k]=a[l];
        book[k]=(a[l]==1);
    }
    else {
        int mid=l+r>>1;
        build(l,mid,k<<1);
        build(mid+1,r,k<<1|1);
        _pushup(k);
    }
}
void _updata(int L,int R,int l,int r,int k){
    if(l==r){
        t[k]=sqrt(t[k]);
        book[k]=(t[k]==1);
    }
    else {
        int mid=l+r>>1;
        if(L<=mid && !book[k<<1]) _updata(L,R,l,mid,k<<1);
        if(R>mid && !book[k<<1|1]) _updata(L,R,mid+1,r,k<<1|1);
        _pushup(k);
    }
}
ll _query(int L,int R,int l,int r,int k){
    if(L<=l && r<=R) return t[k];
    else {
        int mid=l+r>>1;
        ll res=0;
        if(L<=mid) res+=_query(L,R,l,mid,k<<1);
        if(R>mid) res+=_query(L,R,mid+1,r,k<<1|1);
        return res;
    }
}
void _work(int n){
    printf("Case #%d:\n",++_case);
    int m,opt,l,r;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    build(1,n,1);
    scanf("%d",&m);
    while(m--){
        scanf("%d %d %d",&opt,&l,&r);
        if(l>r) swap(l,r);
        if(opt==0) _updata(l,r,1,n,1);
        else printf("%lld\n",_query(l,r,1,n,1));
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n)){
        _work(n);
        puts("");
    }
    return 0;
}
```

---

## 作者：_998344353_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP2713)

双倍经验：花神游历各国（P4145）

### 题目大意：

给你n个数，要求维护区间开方和区间求和。

看到这题（以及它的双倍经验）还没有树状数组**不加**并查集的做法，于是来写一波

一个数至多开7次方就会变成1，各位大佬已经说过，在此不再赘述。

原理：一段数如果全为1，由于sqrt(1)=1,所以不用修改，否则暴力修改，最多修改7n次

所以问题来了，怎样判断一段数是否全为1呢？

很显然，如果l~r这个区间的和小于r - l **+1**,则我们就不用暴力修改。

暴力修改：同时修改**原数组**和**树状数组**，这样就可以了。

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,i,j,a[1000001],b[1000001],qaq=0,t=0;//a:树状数组 b:原数组
inline ll lowbit(ll k)//lowbit操作
{
	return k&(-k);
}
inline void change(ll x,ll y)//单点修改
{
	while(x<=n)
	{
		a[x]+=y;
		x+=lowbit(x);
	}
	return;
}
inline ll qzh(ll x) //前缀和(区间查询)
{
	ll sum=0;
	while(x>0)
	{
		sum+=a[x];
		x-=lowbit(x);
	}
	return sum;
}
int main()
{
	while(scanf("%lld",&n)!=EOF)
	{
		printf("Case #%lld:\n",++t);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(i=1;i<=n;i++)
		{
			scanf("%lld",&b[i]);
			change(i,b[i]);
		}
		cin>>m;
		for(i=1;i<=m;i++)
		{
			ll pd,x,y;
			scanf("%lld%lld%lld",&pd,&x,&y);
			if(x>y)
			{
				swap(x,y);
			}
			if(pd==1)
			{
				printf("%lld\n",qzh(y)-qzh(x-1));
			}
			else
			{
				if(qzh(y)-qzh(x-1)<=y-x+1) //判断是否需要暴力修改
				{
					continue;
				}
					for(j=x;j<=y;j++)
					{
						if(b[j]>1)
						{
							change(j,((ll)sqrt(b[j]))-b[j]);//修改树状数组
							b[j]=sqrt(b[j]); //修改原数组
						}
					}
					qaq++;
			}
		}
	}
	return 0;
} 
```
**另外，一定记得判断是否需要交换l和r!**

---

## 作者：炳源 (赞：0)

# 看到各种dalao用线段树维护最大值以及区间和  
### 蒟蒻有点想法  
其实判断最大值是1并不需要这么困难，  
## 题目也说了，该题的数据是正整数！  
所以我们只需要判断区间和是否等于这个区间的长度就OK了  
对于开方来说，为什么我们这题不能使用lazytag维护是因为开方操作不满足交换律，所以lazytag就失去作用。  
比如
```
sqrt(2) != sqrt(1) + sqrt(1)
```
然后还有最后一点，一个数多次开方后就会变成1  
比如  
![](https://cdn.luogu.com.cn/upload/image_hosting/05rbzz0v.png))  
而sqrt（1）又等于1  
所以就可以愉快的切掉这题了  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define il inline 
#define R register 
using namespace std;
typedef long long int ll;
const ll maxsize = 100100;
ll n,m;
inline ll Read()
{
	ll data = 0;
	char ch = getchar();
	while(!isdigit(ch))
		ch = getchar();
	while(isdigit(ch))
		data = (data << 3) + (data << 1) + ch - '0',ch = getchar();
	return data;
}
class Line_Tree
{
	private :
		struct Line_Tree_Node
		{
    		ll l;
    		ll r;
    		ll lazy_tag_add;
    		ll lazy_tag_mul;
    		ll val;
		}G[maxsize<<2];
	public :
		inline ll lc(R ll pos)
		{
    		return pos<<1;
		}
		inline ll rc(R ll pos)
		{
    		return pos<<1|1;
		}
		inline void Clear()
		{
			memset(G,0,sizeof(G));
		}
		il void Build(R ll pos,R ll l,R ll r)
		{
    		G[pos].l = l;
    		G[pos].r = r;
    		G[pos].lazy_tag_mul = 1;
    		if(l == r)
    		{
    		    scanf("%lld",&G[pos].val);
    		    return ;
    		}   
    		ll mid = (l + r) >> 1;
    		Build(lc(pos),l,mid);
    		Build(rc(pos),mid + 1,r);
    		G[pos].val = G[lc(pos)].val + G[rc(pos)].val; 
		}
		il void Prescription_Data(R ll pos,R ll goal_l,R ll goal_r)
		{
			if(G[pos].val == G[pos].r - G[pos].l + 1)
				return ;
			if((G[pos].l == G[pos].r) && (G[pos].l >= goal_l) && (G[pos].r <= goal_r))
			{
				G[pos].val = sqrt(G[pos].val);
				return ;
			}
			ll mid = (G[pos].l + G[pos].r) >> 1;
			if(goal_l <= mid)
				Prescription_Data(lc(pos),goal_l,goal_r);
			if(goal_r > mid)
				Prescription_Data(rc(pos),goal_l,goal_r);
			G[pos].val = G[lc(pos)].val + G[rc(pos)].val;
		}
		il ll Query(R ll pos,R ll goal_l,R ll goal_r)
		{   
    		if (goal_l <= G[pos].l && G[pos].r <= goal_r)
       			return G[pos].val;
    		ll temp_val = 0;
    		ll mid = (G[pos].l + G[pos].r) >> 1;
    		if (goal_l <= mid)
        		temp_val += Query(lc(pos),goal_l,goal_r);
    		if (mid < goal_r)
       			temp_val += Query(rc(pos),goal_l,goal_r);
    		return temp_val;
		}
}line_tree;
int Index = 0;
int main()
{
	while(scanf("%lld",&n) != EOF)
	{
		line_tree.Clear();
    	line_tree.Build(1,1,n);
		scanf("%lld",&m);
		printf("Case #%d:\n",++Index);
		for (register int i = 1;i <= m;i++)
    	{
        	int opt = Read();
			int l = Read(),r = Read();
			if(l > r)
				swap(l,r);
			if(opt == 0)
				line_tree.Prescription_Data(1,l,r);
			else
				printf("%lld\n",line_tree.Query(1,l,r));
    	}
	}
    return 0;
}
```
还有一点，[双倍经验](https://www.luogu.org/problem/P4145)

---

## 作者：Provicy (赞：0)

一道线段树偏板子的题

这题的操作显而易见，是**区间开方**和求区间和。

首先不要看错，**开方和**和**和开方**是不一样的，这是第一点，故我们不能用什么奇淫技巧。

同时我们观察此题，发现对于开方运算次数并不会很多。故我们可以用一个数组记录区间最大值，如果这个最大值比$1$要小，那就说明这个区间已经开方完成了，那就不用继续处理这个区间了，这样我们就大大减少了修改区间的时间复杂度。

同时不要忘记，这是多组数据，不要忘了初始化

最后代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=410000;
int n,m,a[N],leaf1[N],leaf2[N],now;
inline int read()
{
	int s=0,w=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar(); return s*w;
}
inline int LeftChild(int x) {return x<<1;}
inline int RightChild(int x) {return x<<1|1;}
inline void Push_Up(int x)
{
	leaf2[x]=max(leaf2[LeftChild(x)],leaf2[RightChild(x)]);
	leaf1[x]=leaf1[LeftChild(x)]+leaf1[RightChild(x)];
}
void Build_Tree(int x,int l,int r)
{
	if(l==r) {leaf1[x]=leaf2[x]=a[l]; return;}
	Build_Tree(LeftChild(x),l,(l+r)>>1);
	Build_Tree(RightChild(x),((l+r)>>1)+1,r);
	Push_Up(x);
}
void UpDate(int u,int v,int l,int r,int x)
{
	if(l==r) {leaf1[x]=sqrt(leaf1[x]); leaf2[x]=sqrt(leaf2[x]); return;}
	if(leaf2[x]<=1) return;
	if(u<=(l+r)>>1) UpDate(u,v,l,(l+r)>>1,LeftChild(x));
	if(v>(l+r)>>1) UpDate(u,v,((l+r)>>1)+1,r,RightChild(x));
	Push_Up(x);
}
int Ask(int u,int v,int l,int r,int x)
{
	if(l>=u&&r<=v) return leaf1[x];
	int ans=0;
	if(u<=(l+r)>>1) ans+=Ask(u,v,l,(l+r)>>1,LeftChild(x));
	if(v>(l+r)>>1) ans+=Ask(u,v,((l+r)>>1)+1,r,RightChild(x));
	return ans;
}
void Clear()
{
	memset(a,0,sizeof(a));
	memset(leaf1,0,sizeof(leaf1));memset(leaf2,0,sizeof(leaf2));
}
signed main()
{
	while(scanf("%lld",&n)!=EOF)
	{
		now++;
		printf("Case #%lld:\n",now);
		for(int i=1;i<=n;i++) a[i]=read();
		Build_Tree(1,1,n);m=read();
		for(int i=1,op,l,r;i<=m;i++)
		{
			op=read();l=read();r=read();
			if(l>r) swap(l,r);
			if(!op) UpDate(l,r,1,n,1);
			else if(op) printf("%lld\n",Ask(l,r,1,n,1));
		}
		printf("\n");
		Clear();
	}
	return 0;
}
```


---

## 作者：xsI666 (赞：0)


$SPOJ$的$GSS$系列第四题。

乍一看和[这题](https://loj.ac/problem/6281)一模一样，于是准备直接拿一样的代码提交。

猛然发现：数据范围差了那么远！

[这题](https://loj.ac/problem/6281)中$0 \leq n \leq 50000$,$-2^{31} \leq others$、$ans \leq 2^{31} - 1$。

而本题中$n \leq 100000$，$\sum~a_i~\leq~10^{18}$直接提交一样的代码肯定会$TLE$。

于是尝试线段树。

普通操作与线段树大同小异，只是需要注意一个点：**一个数已经小于或等于1就不要再开方了！**

为什么呢？因为大于$1$的数开方会越来越接近$1$，而小于$1$的数开方也会越来越接近$1$，又因为$\sqrt{1} = 1$，因此任何数经过开方操作都可以到$1$。

不难得出$AC$代码。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

inline int gi()//快速读入
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

const int maxn = 100000 + 5;
int n, m, Case;
long long tr[maxn << 2], a[maxn], sq[maxn << 2];//tr为区间和,a为数字序列,sq为区间最大值

inline void pushup(int p)//上传节点
{
	tr[p] = tr[p << 1] + tr[(p << 1) | 1];//增加区间和
	sq[p] = max(sq[p << 1], sq[(p << 1) | 1]);//计算最大值
}

void build(int s, int t, int p)//建树
{
	if (s == t)//已经是叶子节点
	{
		tr[p] = sq[p] = a[s];//初始化节点信息
		return;//直接返回
	}
	int mid = (s + t) >> 1;//计算中点
	build(s, mid, p << 1);//递归左子树
	build(mid + 1, t, (p << 1) | 1);//递归右子树
	pushup(p);//上传当前节点
}

void modify(int l, int r, int s, int t, int p)//进行区间开方操作
{
	if (s == t)//已经到了叶子节点
	{
		tr[p] = sqrt(tr[p]);//进行开方
		sq[p] = tr[p];//区间最大值就是当前数
		return;//返回
	}
	int mid = (s + t) >> 1;//计算中间值
	if (l <= mid && sq[p << 1] > 1) //如果目标节点在左区间且左区间最大值大于1
		modify(l, r, s, mid, p << 1);//就递归左子树寻找目标节点
	if (r > mid && sq[(p << 1) | 1] > 1) //目标节点在右区间且右区间最大值大于1
		modify(l, r, mid + 1, t, (p << 1) | 1);//递归右子树寻找目标节点
	pushup(p);//上传当前节点
}

long long getans(int l, int r, int s, int t, int p)//寻找答案
{
	if (l <= s && r >= t)//当前区间包含于目标区间
	{
		return tr[p];//直接返回当前区间信息
	}
	long long sum = 0;//要返回的和
	int mid = (s + t) >> 1;//计算中间值
	if (l <= mid)//如果左端点在中点左侧
	{
		sum = sum + getans(l, r, s, mid, p << 1);//加上左区间的答案
	}
	if (r > mid)//如果右端点在中点右侧
	{
		sum = sum + getans(l, r, mid + 1, t, (p << 1) | 1);//加上右区间的答案
	}
	return sum;//返回答案
}

int main()
{
	while (~scanf("%d", &n))//多组数据
	{
		printf("Case #%d:\n", ++Case);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		memset(tr, 0, sizeof(tr));
		memset(sq, 0, sizeof(sq));//多组数据要初始化
		build(1, n, 1);//建树
		m = gi();//输入询问个数
		for (int i = 1; i <= m; i++)
		{
			int x = gi(), y = gi(), z = gi();
			if (y > z) swap(y, z);//如果左端点大于右端点,就交换它们
			if (x == 1)//是询问区间和
			{
				printf("%lld\n", getans(y, z, 1, n, 1));//输出答案
			}
			else 
			{
				modify(y, z, 1, n, 1);//否则就进行区间开方
			}
		}
		puts("");//一定记得数据之间要空行
	}
	return 0;//结束
}
```

---

## 作者：Jμdge (赞：0)

没开 long long   wa*1

没换 l r   wa*2

裸题 wa 3下直接哭出来

很套路的一道题，我们发现 1e18 的数开不超过五次就变成 1 了

所以我们是不是可以考虑维护一个线段树处理区间和？然后打打标记？

然后每次修改都是找到叶子，开方？

然后如果一个节点的子树内（包括自己）都是 1 就打个标记然后下次 update 的时候直接 return ？

复杂度 $O(n \log n)$ 常数大概就是每个数开方次数，也就是 5 吧（远远达不到的，你加了代码就会发现跑的贼快）

然后我的代码还是这么短....

```
//by Judge
#include<cmath>
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
const int M=1e5+3;
int n,m,cnt; ll a[M],t[M<<2],tag[M<<2];
#define ls k<<1
#define rs k<<1|1
#define mid (l+r>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
void build(int k,int l,int r){ tag[k]=0;
	if(l==r) return t[k]=a[l],void();
	build(lson),build(rson),t[k]=t[ls]+t[rs];
}
void update(int k,int l,int r,int L,int R){ if(tag[k]||l>R||L>r) return ;
	if(l==r) return t[k]=sqrt(t[k]),tag[k]=t[k]==1,void();
	update(lson,L,R),update(rson,L,R),t[k]=t[ls]+t[rs],tag[k]=tag[ls]&tag[rs];
}
ll query(int k,int l,int r,int L,int R){
	if(L>r||l>R) return 0; if(L<=l&&r<=R) return t[k];
	return query(lson,L,R)+query(rson,L,R);
}
int main(){
	for(;~scanf("%d",&n);){
		if(cnt) puts("");
		printf("Case #%d:\n",++cnt);
		for(int i=1;i<=n;++i) scanf("%lld",a+i);
		build(1,1,n),scanf("%d",&m);
		for(int op,l,r;m;--m){ scanf("%d%d%d",&op,&l,&r);
			if(l>r) l^=r^=l^=r;
			if(op) printf("%lld\n",query(1,1,n,l,r));
			else update(1,1,n,l,r);
		}
	} return 0;
}
```

---

## 作者：King丨帝御威 (赞：0)

第一眼，一点头绪都没有，因为涉及到区间修改和查询，像线段树，但又一副不可做的样子，因为如果区间修改不加任何优化的话，常数就会大的一批，应该会超时，那么，我们就来考虑关于开方的有关性质，首先$sqrt(1)=1$，震惊！！没错，这就是修改终点，如果一个位置的数为1，再开方是没有意义的，那么我们就可以维护一个区间最大值，如果这个区间最大值是$1$，也就是这个区间的数都是$1$，那么就没必要进行修改了，区间求和的话就跟普通线段树没什么区别了。还有，为什么区间修改时终点是$l==r$呢？难道不是$L<=l$&&$r<=R$么？因为这里的区间修改是采用了一种暴力的思想，也就是一个一个改，相当于单点修改。

如果不知道怎么写的话，可以参考以下代码：
``` cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>
#define maxn 100007
#define ll long long
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
int n,m,tim;
ll maxx[maxn<<2],sum[maxn<<2];
inline ll qread() {
  char c=getchar();ll num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
inline void pushup(int rt) {
  sum[rt]=sum[ls]+sum[rs];
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
void build(int rt, int l, int r) {
  if(l==r) {
    sum[rt]=maxx[rt]=qread();
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
void modify(int rt, int l, int r, int L, int R) {
  if(l==r) {
    sum[rt]=sqrt(sum[rt]);
    maxx[rt]=sqrt(maxx[rt]);
    return;
  }
  int mid=(l+r)>>1;
  if(L<=mid&&maxx[ls]>1) modify(ls,l,mid,L,R);
  if(R>mid&&maxx[rs]>1) modify(rs,mid+1,r,L,R);
  pushup(rt);
}
ll csum(int rt, int l, int r, int L, int R) {
  if(L>r||R<l) return 0;
  if(L<=l&&r<=R) return sum[rt];
  int mid=(l+r)>>1;
  return csum(ls,l,mid,L,R)+csum(rs,mid+1,r,L,R);
}
int main() {
  while(scanf("%d",&n)==1) {
    printf("Case #%d:\n",++tim);
    build(1,1,n);
    m=qread();
    for(int i=1,k,x,y;i<=m;++i) {
      k=qread(),x=qread(),y=qread();
      if(x>y) swap(x,y);
      if(!k) modify(1,1,n,x,y);
      else printf("%lld\n",csum(1,1,n,x,y));  
    }
  }
  return 0;
}
```

希望这篇题解对大家理解线段树能有所帮助。

---

## 作者：piuke (赞：0)

# 题目描述
[~同样的小网址~](https://www.luogu.org/problemnew/show/SP2713)
# 预备知识
不会树状数组请左转我的[这篇博客](https://blog.csdn.net/qq_43906740/article/details/84763539)

看到别人都在打线段树，作为一个只会 __B.I.T.__ 的小蒟蒻真的好虚啊

不过，不要想多了，这道题真的可以用树状数组来做

# 分析
首先,打好一个树状数组的模板,如下(这个时候树状数组比线段树好的地方就看出来了)
```cpp
long long C[MAXN];
#define lowbit(x) (x & -x)
inline void update(int x,long long val) {
    for(reg int i=x;i<=n;i+=lowbit(i)) C[i]+=val;
}
inline long long query(int x) {
    long long s=0;
    for(reg int i=x;i;i-=lowbit(i)) s+=C[i];
    return s;
}
```
看到区间修改，首先的思路应该是这样的
```cpp
long long a[MAXN];
inline void change(int l,int r) {
    for(reg int i=l;i<=r;i++)
        a[i]=sqrt(a[i]);
    memset(C,0,sizeof C);
    for(reg int i=1;i<=n;i++)
        update(i,a[i]);
}
```
~~无论你再怎么吸氧也无能为力~~

## 第一次优化尝试

突然发现,我们可以有一个小优化,因为$\sqrt 1\ =\ 1$,所以可以用一个数组来记录一下最近的1,优化一下常数,如下
```cpp
int one[MAXN];
inline void init() {
    for(reg int i=1;i<=n;i++) one[i]=i+1;
}
inline void change(int l,int r) {
    int pre=0;
    for(reg int i=l;i<=r;i=one[i]) {
        a[i]=sqrt(a[i]);
        if(a[i]==1) one[pre]=i+1;
        pre=i;
    }
    memset(C,0,sizeof C);
    for(reg int i=1;i<=n;i++) update(i,a[i]);
}
```
~~仍然吸氧难救~~

## 第二次优化尝试
如果有完全的优化的话,应该是直接指向最前方的非1元素,也就是指向前面的前面的前面的……的非1元素  
等一下?前面的……?父亲的父亲的父亲的……?~~震惊!~~路径压缩?并查集?  
正解思路:B.I.T.+并查集

如下
```cpp
inline void change(int l,int r) {
    for(reg int i=l;i<=r;i=findSet(i+1)) {
        int t=LL(sqrt(a[i]));
        update(i,t-a[i]);
        a[i]=t;
        if(a[i]<=1)
            fa[i]=findSet(i+1);
    }
}
```

# 完整代码
(不要问我搞这么多模板干什么)
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#define reg register
template <typename T>
inline T read() {
    T a=0; char c=getchar(),f=1;
    while(c<'0'||c>'9') {
        if(c=='-') f=-f;
        if(c==-1) return c;
        c=getchar();
    }
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+(c^48),c=getchar();
    return a*f;
}
template <class T>
inline int write(T x) {
    if(x<0) x=(~x)+1, putchar('-');
    if(x/10) write(x/10);
    return putchar(x%10|48);
}
template <class T>
inline int write(T x,char c) {
    return write(x)&&putchar(c);
}
template <class T>
inline T Max(T a,T b) { return a>b?a:b; }
template <class T>
inline T Min(T a,T b) { return a<b?a:b; }
template <class T>
inline T Abs(T a) { return a<0?-a:a; }
inline void swap(int&a,int&b) {
    a^=b;
    b^=a;
    a^=b;
}
const int MAXN=100001;
typedef long long LL;
int n=read<int>();
LL C[MAXN];
LL a[MAXN];
#define lowbit(x) (x & -x)
inline void update(int x,LL val) {
    for(reg int i=x;i<=n;i+=lowbit(i)) C[i]+=val;
}
inline LL query(int x) {
    LL s=0;
    for(reg int i=x;i;i-=lowbit(i)) s+=C[i];
    return s;
}
int fa[MAXN];
inline void init() { for(reg int i=1;i<=n+1;i++) fa[i]=i; }
inline int findSet(int x) { while(x!=fa[x]) x=fa[x]=fa[fa[x]]; return x; }
inline void change(int l,int r) {
    for(reg int i=l;i<=r;i=findSet(i+1)) {
        int t=LL(sqrt(a[i]));
        update(i,t-a[i]);
        a[i]=t;
        if(a[i]<=1)
            fa[i]=findSet(i+1);
    }
}
int main() {
    init();
    for(reg int i=1;i<=n;i++) {
        a[i]=read<LL>();
        update(i,a[i]);
    }
    int Q=read<int>();
    for(reg int i=1;i<=Q;i++) {
        int k=read<int>();
        if(k) {
            int l=read<int>(),r=read<int>();
            if(l>r) swap(l,r);
            LL sum=query(r)-query(l-1);
            write(sum,'\n');
        }
        else {
            int l=read<int>(),r=read<int>();
            if(l>r) swap(l,r);
            change(l,r);
        }
    }
}

```

---

## 作者：JustinRochester (赞：0)

本蒟蒻比较喜欢指针打线段树，就来一波指针的吧

这里本蒟蒻先说明一下，因为本蒟蒻实在比较菜，有的东西的原理可能说得不清楚或不专业。如果这方面有了解的大佬可以在评论区帮本蒟蒻“拨乱反正”一下

本蒟蒻先再此谢过众位大佬

---
**【分析】**
--

已知这种区间的操作就是线段树啊、分块啊之类的做法

那本蒟蒻是用了线段树的做法，这边我就只讲这种做法吧

首先，对于两个区间操作，查询是常规操作，这里就不过多讲解了

主要讲一下开方操作：

我们用计算器可以很快知道：

$\sqrt{10^{18}}=10^9$

$\sqrt{10^9}=31622$

$\sqrt{31622}=177$

$\sqrt{177}=13$

$\sqrt{13}=3$

$\sqrt{3}=1$

也就是说，在题目给定的数值范围内，任意数只要开方 $6$ 次及以内就会变为 $1$ 了 ( $0$ 除外)

而一旦变为 $1$ ，它变无论开方多少次，都是 $1$

因此，我们可以给每个数字判定一下，如果是 $1$ ，我们开方操作时直接跳过这个数就可以了

接下来，我们考虑一下连续一个区间的 $1$ 

如果一个连续区间都是 $1$ 或 $0$ ，那么，每次开方操作对于这个区间都相当于无效的

因此，我们可以再加一个标记维护这个连续区间是不是如上所示

如果是，就直接跳过；如果不是，就暴力修改两边（每个数字最多修改 $6$ 次，所以大体上来说，修改是不大的）

好，那我们的标记要怎么处理呢？

这里本蒟蒻用的是维护最大值，如果最大值为 $1$，就直接跳过。(当然，本蒟蒻觉得用一个 $bool$ 变量应该也行)

那对于多组数据怎么处理呢？

如果每次指针都重新申请空间，有很大可能会爆炸

那我们就干脆每次执行完就释放所有申请的空间

我们可以用一个深搜解决，遍历整棵树，访问到叶节点就删去，否则先删除子树

**但是**，本蒟蒻这里推荐析构函数，它的执行时间是当这个节点要被删除的时候，执行完以后再删除

你问我为什么复杂度差不多，却要用析构函数不用深搜？

当然是因为我懒啊  ~~2333333~~

具体的一些细节就看本蒟蒻的代码了

---

**【代码】**
--

那本蒟蒻就放 ~~码风极其丑陋的~~ 代码了

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
#define f(a,b,c) for(register int a=b;a<=c;a++)
#define g(a,b,c) for(register int a=b;a>=c;a--)
#define Max(a,b) ((a>b)?a:b)
#define Min(a,b) ((a<b)?a:b)
typedef long long int ll;
typedef unsigned long long int ull;
inline ll read(){
	register ll ans=0;register char c=getchar();register bool neg=0;
	while((c<'0')|(c>'9')) neg^=!(c^'-'),c=getchar();
	while((c>='0')&(c<='9')) ans=(ans<<3)+(ans<<1)+(c^'0'),c=getchar();
	return neg?-ans:ans;
}//条件反射的结果
struct Node{
	int L,R;
	ll Sum,Maxa;
	Node *Lc,*Rc;
	Node(int Head,int Tail):L(Head),R(Tail) {
		if(L==R){
			Sum=Maxa=read();
			Lc=Rc=0;
			return ;
		}
		Lc=new Node(L,(L+R)>>1);
		Rc=new Node(Lc->R+1,R);
		Sum=Lc->Sum+Rc->Sum;
		Maxa=Max(Lc->Maxa,Rc->Maxa);
	}//构造函数，建树
	~Node() { delete(Lc); delete(Rc); }
    //析构函数，“砍树”
	ll  Qry(int Head,int Tail){
		if( (Head==L)&(Tail==R) ) return Sum;
		if(Tail<=Lc->R) return Lc->Qry(Head,Tail);
		else if(Head>=Rc->L) return Rc->Qry(Head,Tail);
		else return Lc->Qry(Head,Lc->R)+Rc->Qry(Rc->L,Tail);
	}//查询，常规操作
	void Sqr(int Head,int Tail){
		if(Maxa==1) return ;
		if(L==R){
			Sum=sqrt(Sum);
			Maxa=Sum;
			return ;
		}
		if(Tail<=Lc->R) Lc->Sqr(Head,Tail);
		else if(Head>=Rc->L) Rc->Sqr(Head,Tail);
		else Lc->Sqr(Head,Lc->R),Rc->Sqr(Rc->L,Tail);
		Sum=Lc->Qry(Lc->L,Lc->R)+Rc->Qry(Rc->L,Rc->R);
        //维护总和
		Maxa=Max(Lc->Maxa,Rc->Maxa);//维护最大值
	}//开方
}*Root;
void ope(int x){
	int Head=read(),Tail=read();
	if(Head>Tail) Head^=Tail^=Head^=Tail;
	if(x==1) printf("%lld\n",Root->Qry(Head,Tail));
	else if(x==0) Root->Sqr(Head,Tail);
}//操作识别
int main(){
	int N,Cnt=1;
	while( scanf("%d",&N)!=EOF ){
		printf("Case #%d:\n",Cnt++);
		Root=new Node(1,N);
		int M=read();
		while(M--) ope(read());
		delete(Root);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：ChenZ01 (赞：0)

## 题解

又是一道假的紫题

又是一道系列毒瘤题

### 分析

显然开方操作不能打lazy-tag，对于每个修改我们只能直接单点或区间修改

既然只能这么做，我们必须考虑开方操作的优化

由于开方后再开方相当于四次根号，那么开了$n$次方的数所得结果就是$2^n$次根号，这个数一定不会大到哪里去

事实上，$\lfloor^{64}\sqrt{10^{18}}\rfloor=1$，因此超过$6$次开方的区间所有的数一定为$1$

根据这个性质，我们有如下思想：
对于将修改的区间$[L,R]$，若每个数都等于$1$（亦即区间和$=R-L+1$），这个区间无需操作，否则修改到点

由于一个点最多被修改$6$次，复杂度可以接受

### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
long long s[500010];
long long n, q, tmp, op, ans;
int x, y, cnt;
void init()
{
    memset(s, 0, sizeof s);
}
void pushup(int root)
{
    s[root] = s[root << 1] + s[root << 1 | 1];
}
void build(int l, int r, int root)
{
    if (l == r)
        cin >> tmp, s[root] = tmp;
    else
    {
        int mid = l + r >> 1;
        build(l, mid, root << 1);
        build(mid + 1, r, root << 1 | 1);
        pushup(root);
    }
}
void update(int l, int r, int root)
{
    if (s[root] <= r - l + 1)
        return;
    if (l == r)
        s[root] = (long long)floor(sqrt(s[root]));
    else
    {
        int mid = l + r >> 1;
        if (x <= mid)
            update(l, mid, root << 1);
        if (y > mid)
            update(mid + 1, r, root << 1 | 1);
        pushup(root);
    }
}
void query(int l, int r, int root)
{
    if (l >= x && r <= y)
        ans += s[root];
    else
    {
        int mid = l + r >> 1;
        if (x <= mid)
            query(l, mid, root << 1);
        if (y > mid)
            query(mid + 1, r, root << 1 | 1);
    }
}
int main(int argc, char ** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n)
    {
        cout << "Case #" << ++cnt << ":" << endl;
        init();
        build(1, n, 1);
        cin >> q;
        while (q--)
        {
            cin >> op >> x >> y;
            if (x > y)
                swap(x, y);
            if (op)
            {
                ans = 0;
                query(1, n, 1);
                cout << ans << endl;
            }
            else
            {
                update(1, n, 1);
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

