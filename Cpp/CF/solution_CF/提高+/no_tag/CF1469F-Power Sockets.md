# Power Sockets

## 题目描述

// We decided to drop the legend about the power sockets but feel free to come up with your own :^)

Define a chain:

- a chain of length $ 1 $ is a single vertex;
- a chain of length $ x $ is a chain of length $ x-1 $ with a new vertex connected to the end of it with a single edge.

You are given $ n $ chains of lengths $ l_1, l_2, \dots, l_n $ . You plan to build a tree using some of them.

- Each vertex of the tree is either white or black.
- The tree initially only has a white root vertex.
- All chains initially consist only of white vertices.
- You can take one of the chains and connect any of its vertices to any white vertex of the tree with an edge. The chain becomes part of the tree. Both endpoints of this edge become black.
- Each chain can be used no more than once.
- Some chains can be left unused.

The distance between two vertices of the tree is the number of edges on the shortest path between them.

If there is at least $ k $ white vertices in the resulting tree, then the value of the tree is the distance between the root and the $ k $ -th closest white vertex.

What's the minimum value of the tree you can obtain? If there is no way to build a tree with at least $ k $ white vertices, then print -1.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1469F/981e4f2e3fb7129ca908af827dab42c29ac78ae4.png)You are allowed to not use all the chains, so it's optimal to only use chain of length $ 4 $ in the second example.

## 样例 #1

### 输入

```
1 2
3```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
4 3 3```

### 输出

```
3```

## 样例 #3

### 输入

```
3 5
4 3 4```

### 输出

```
4```

## 样例 #4

### 输入

```
2 10
5 7```

### 输出

```
-1```

# 题解

## 作者：zjjws (赞：7)

先考虑这样一个事情：我们如何实现加入一条链的操作。

从 ~~样例分析~~ 严谨的分析中我们可以知道：必然是把一条链的 **重心（中点）** 接过去，这样能保证产生的那些深度都最浅。

假设我们接上去的点（树中的）的深度是 $x$，链的长度为 $l$，那么我们要实现的操作是：

- 将深度为 $x$ 的点减少一个（染黑了）。

- $(x+1,x+\lfloor \frac{l-1}{2}\rfloor\ ]\cap \mathbb Z$ 深度的白点各增加一个。

- $(x+1,x+(l-1-\lfloor \frac{l-1}{2}\rfloor)\ ]\cap \mathbb Z$ 深度的白点各增加一个。

这题时限开了四秒，所以我们自然可以大力线段树，维护每个深度的点出现次数。

当然这里介绍一种十分巧妙的差分做法，是 Rank 1 那位 ~~凑DD~~ @jiangly 的写法。

因为是区间加操作，可以用查分来实现，**只会往后更新** 的性质使得我们可以一边做一边处理前缀和得到当前真正的白点个数。

这样就可以使得总复杂度为线性。


```cpp
for(i=0,j=1;i<N;i++)
    {
        sum+=s[i];
        s[i+1]+=s[i];
        if(sum+s[i+1]>=k){ans=i+1;break;}
        for(;j<=n&&s[i];j++)
        {
            s[i+2]+=2;
            s[i+2+(l[j]-1>>1)]--;
            s[i+2+(l[j]-1-(l[j]-1>>1))]--;
            s[i]--;
            sum--;
        }
    }
```

那么现在，我们需要知道操作的策略。

考场 yy 出来的结论是从大到小排序（但是没写，因为时间不够了），这里看能不能说清。

考虑当前要加进去的两条链，它们的长度分别为 $l_1,l_2$，且 $l_1<l_2$。

设当前深度最小的点深度为 $x$。

若是先加入 $l_1$，那么此时 $x$ 深度的点会减少一个，假设减少至 $0$，那么之后加入 $l_2$ 的时候，只能选取大于 $x$ 深度的点作为接入口，此时产生的点集明显 **劣于** 两条链顺序交换产生的点集。


比如 $l_1=3,l_2=5$ 的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/spqfcn98.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/md0tuopg.png)

题目中因为有说 **不用全部加入**，所以可以在找到深度最小的 **白点个数大于等于 k** 的地方直接跳出。

要注意一点：因为一条链会往后扩展 $\frac{l-1}{2}$ 左右的深度的点，而链的总数是 $n$ 条，粗略算一下的话最大深度会是 $k\cdot n$，这个 $k$ 大概是 $[1,3]$ 之间的某个实数，具体的我没算，本体也不卡空，我就直接开了四倍。

---

## 作者：momentous (赞：3)

题意就不再讲了。

我们可以发现，把一条链的中间（即重心）接进去是最优的，因为新增的白点的数量和接的位置没有关系，所以白点的深度越小越好。

那么我们就可以用线段树维护了。

注意细节。

吐槽：为什么时限是4s啊，我线段树所有31个点总共就跑了3.67s......

（无脑做法）：

```cpp
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define CT printf("\n-------------------------\n");
using namespace std;
typedef long long ll;
const int inf=1<<30;
const ll Inf=1ll<<60ll;
namespace io{
	#define bufsize (1<<23)
	char buf[bufsize],*p1=buf,*p2=buf,c;int f;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,bufsize,stdin),p1==p2)?EOF:*p1++)
	template<typename T>T read(){
		T x=0;f=0;c=getchar();
		while(!isdigit(c))(c=='-')&&(f=1),c=getchar();
		while(isdigit(c))x=x*10+(c&15),c=getchar();
		return f?-x:x;
	}
	#undef bufsize
}
#define readi io::read<int>
const int N=200005;
#define range 200010
//N*5
struct Node{
	ll s,tg;
}t[N*5];
#define ls (o<<1)
#define rs (o<<1|1)
void build(int o,int l,int r){
	t[o].s=0;t[o].tg=0;
	if(l==r){
		if(l==0)t[o].s=1;
		else t[o].s=0;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[o].s=t[ls].s+t[rs].s;
}
void pushdown(int o,int l,int r){
	if(t[o].tg==0)return;
	int mid=l+r>>1;
	t[ls].s+=(mid-l+1)*t[o].tg;
	t[rs].s+=(r-mid)*t[o].tg;
	t[ls].tg+=t[o].tg;
	t[rs].tg+=t[o].tg;
	t[o].tg=0;
}
void update(int o,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		t[o].s+=r-l+1;
		t[o].tg++;
		return;
	}
	pushdown(o,l,r);
	int mid=l+r>>1;
	if(L<=mid)update(ls,l,mid,L,R);
	if(R>mid)update(rs,mid+1,r,L,R);
	t[o].s=t[ls].s+t[rs].s;
}
void reduce(int o,int l,int r,int p){
	if(l==r){t[o].s--;return;}
	pushdown(o,l,r);
	int mid=l+r>>1;
	if(p<=mid)reduce(ls,l,mid,p);
	else reduce(rs,mid+1,r,p);
	t[o].s=t[ls].s+t[rs].s;
}
int find(int o,int l,int r){
//	printf("** %d %d\n",l,r);
	if(l==r)return l;
	int mid=l+r>>1;
	pushdown(o,l,r);
	if(t[ls].s!=0)return find(ls,l,mid);
	else return find(rs,mid+1,r);
}
int k,a[N];
ll query(int o,int l,int r,int k){
	if(l==r)return l;
	int mid=l+r>>1;
	pushdown(o,l,r);
	if(t[ls].s<k)return query(rs,mid+1,r,k-t[ls].s);
	else return query(ls,l,mid,k);
}

ll debug(int o,int l,int r,int p){
	if(l==r)return t[o].s;
	int mid=l+r>>1;
	pushdown(o,l,r);
	if(p<=mid)return debug(ls,l,mid,p);
	else return debug(rs,mid+1,r,p);
}

int n;
int main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=readi();k=readi();
	for(int i=1;i<=n;++i){
		a[i]=readi();
	}
	sort(a+1,a+n+1,greater<int>());
	build(1,0,range);
//	CT
//	for(int i=0;i<=10;++i)
//		printf("%lld ",debug(1,0,range,i));
//	CT
	ll ans=Inf;
	ll tot=1;
	
	for(int i=1;i<=n;++i){
//		printf("de:%lld\n",debug(1,0,range,2));
		int pos=find(1,0,range);
		reduce(1,0,range,pos);
		tot--;
		int len=a[i];
		if(len&1){
			update(1,0,range,pos+2,pos+1+len/2);
			update(1,0,range,pos+2,pos+1+len/2);
			tot+=(len/2)*2;
		}else{
			update(1,0,range,pos+2,pos+1+len/2);
			tot+=(len/2);
			update(1,0,range,pos+2,pos+1+(len-1)/2);
			tot+=((len-1)/2);
		}
		if(tot>=k) ans=min(ans,query(1,0,range,k));
	}
	if(ans==Inf)puts("-1");
	else printf("%lld\n",ans);

//	fclose(stdin);fclose(stdout);
	return 0;
}
/*
10 20
9 8 6 6 6 5 4 4 4 3
*/
```

---

## 作者：tai_chi (赞：2)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18564798) 中阅读。

#### 题意

有一些已知长度的链，一棵只有一个白色根节点的树。定义一次操作为：

- 选择用一条未操作的链，连接链上中的某个点 $u$ 与树上某个白点 $v$；
- 点 $u$ 和 $v$ 都会变成黑色。

每条链最多操作一次，也可以不操作。最小化根节点到第 $k$ 近的白点的距离。

#### 分析

题意等价于最小化第 $k$ 深白点的深度。

贪心地，我们在挂上一条链的时候会选择这条链的中点位置，而且会选择树上深度最浅的点，这显然会使深度最浅。

依然贪心地，我们先会选择较长的链。感性理解：后连的链会基于一个比较深的位置向下延伸，我们希望更深的延伸发生在较早的时间点。

我们需要动态维护树上深度最小的点，而且还要支持加入一条链的每个深度，考虑到链上的点深度连续，这个操作实际上可以表述为区间加，线段树可以实现这一操作。而寻找深度最小的点则可以通过线段树上二分来实现。

为啥线段树的节点不会爆空间？考虑最坏情况：$2 \times 10^5$ 条链的长度都顶满 $2 \times 10^5$。我们先加入一条链，即使后面的链全都挂在初始的这条链上，最大深度也只有 $4 \times 10^5$，况且这并不是最优方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int N=2e6+5,inf=0x3f3f3f3f;
int n,k;
int l[N];
struct node
{
	int l,r,mx,tag;
	ll sum;
} t[N*4];
void pushup(int u)
{
	t[u].mx=max(t[u*2].mx,t[u*2+1].mx);
	t[u].sum=t[u*2].sum+t[u*2+1].sum;
}
void build(int u,int l,int r)
{
	t[u].l=l; t[u].r=r;
	if(l==r)
	{
		if(l==0) t[u].mx=t[u].sum=1;
		else t[u].mx=t[u].sum=0;
		return;
	}
	int mid=(l+r)>>1;
	build(u*2,l,mid); build(u*2+1,mid+1,r);
	pushup(u);
}
void maketag(int u,int x)
{
	if(!x) return;
	t[u].mx+=x;
	t[u].tag+=x;
	t[u].sum+=x*(t[u].r-t[u].l+1);
}
void pushdown(int u)
{
	maketag(u*2,t[u].tag); maketag(u*2+1,t[u].tag);
	t[u].tag=0;
}
void add(int u,int L,int R,int x)
{
	if(L<=t[u].l&&t[u].r<=R) {maketag(u,x); return;}
	if(t[u].r<L||R<t[u].l) return;
	pushdown(u);
	add(u*2,L,R,x); add(u*2+1,L,R,x);
	pushup(u);
}
int ask(int u)
{
	if(t[u].mx==0) return 0;
	if(t[u].l==t[u].r)
	{
		t[u].mx--;
		t[u].sum--;
		return t[u].l;
	}
	pushdown(u);
	int ret=ask(u*2);
	if(!ret) ret=ask(u*2+1);
	pushup(u);
	return ret;
}
int query(int u,int x)
{
	if(t[u].l==t[u].r) return t[u].l;
	pushdown(u);
	if(t[u*2].sum>=x) return query(u*2,x);
	else return query(u*2+1,x-t[u*2].sum);
	pushup(u);
}

signed main()
{
	IOS;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>l[i];
	sort(l+1,l+n+1,greater<int>());
	build(1,0,2e6);
	int ans=inf;
	for(int i=1;i<=n;i++)
	{
		int pl=ask(1);
		int l1=(l[i]-1)/2,l2=l[i]/2;
		add(1,1+pl+1,1+pl+1+l1-1,1); add(1,1+pl+1,1+pl+1+l2-1,1);
		if(t[1].sum>=k) ans=min(ans,query(1,k));
	}
	if(ans==inf) cout<<-1<<"\n";
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### P.S.
这里提供一个两 $\log $ 做法。  
~~其实可以被优化成单 $\log$~~

### Solution.
首先看到第 $K$ 近想到二分答案。  
然后相当于存在一个分界线它下面的节点全部消失，让他上面白点尽量多。  

首先有一个显然的结论，就是每个链肯定会用中点挂上去。  
证明的话考虑调整法，如果不用中点，选中点挂上去会使深度不增，答案不减。  

还有另一个显然的结论，就是会贪心地从大到小挂。  
证明考虑如果长链没超出范围，长链挂越浅肯定更优。  
如果长链超出范围短链没有，那交换后节点少了。  
如果都超出范围了，不管怎么挂答案都不变。  

还有第三个显然地结论，从大到小挂，每个链会贪心地挂在最浅地节点上。  
证明的话考虑如果空节点肯定不优，否则就是第二个结论。  

所以原题转化成了有一棵树，每次取出最浅的白点挂上一条链  
这个东西怎么维护，我们考虑暴力用 `set` 维护。  
`set` 中某个元素定义为出现了若干次的一个链的深度区间。  
按照最浅的点深度排序，然后每次找出 `set` 的头，挂上一个链就行了。  

复杂度俩 $\log$，不可以过。  
但是考虑答案范围，每条链只可能选择最浅的挂，而每条链的长度不超过 $2\times 10^5$。  
所以最深深度不可能超过 $n+2\times 10^5$，所以二分上界不用设成 $O(nv)$ 直接 $O(n+v)$ 即可。  
这样就可以通过此题了。  

然后就是一个嘴巴的单 $\log$，注意到其实那个 `set` 很鸡肋。  
我们发现值域的性质之后，就可以直接指针 + 差分维护它。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=200005;int n,K,a[N];
struct ${ll l,r;int cnt;inline char operator<($ b) const {return l<b.l;}};
inline char check(ll v)
{
	multiset<$>s;s.insert(($){1ll,1ll,1});ll cn=1,mx=1;
	for(int i=1;i<=n;i++)
	{
		if(s.empty()) return mx>=K;
		$ x=*s.begin();s.erase(s.begin());ll l=x.l,r=x.r;int c=x.cnt;
		l^r?s.insert(($){l+1,r,1}),0:0;if(c==2) s.insert(($){l,r,1});
		if(l+1==v) return mx>=K;
		ll r1=min(v,(a[i]-1)/2+l+1),r2=min(v,a[i]/2+l+1);cn+=r1-l+r2-l-3,mx=max(mx,cn);
		(r1^r2?s.insert(($){r2,r2,1}),0:0);if(r1>l+1) s.insert(($){l+2,r1,2});
	}return mx>=K;
}
int main()
{
	read(n,K);for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+n+1,greater<int>());ll rs=0;
	//return printf("%d\n",check(3)),0;
	for(ll L=0,R=400002,md=(L+R)>>1;L<=R;md=(L+R)>>1)
		if(check(md)) rs=md,R=md-1;else L=md+1;
	return printf("%lld\n",rs-1),0;
}
```

---

