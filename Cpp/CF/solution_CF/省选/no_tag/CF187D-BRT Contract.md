# BRT Contract

## 题目描述

In the last war of PMP, he defeated all his opponents and advanced to the final round. But after the end of semi-final round evil attacked him from behind and killed him! God bless him.

Before his death, PMP signed a contract with the bus rapid transit (BRT) that improves public transportations by optimizing time of travel estimation. You should help PMP finish his last contract.

Each BRT line is straight line that passes $ n $ intersecting on its ways. At each intersection there is traffic light that periodically cycles between green and red. It starts illuminating green at time zero. During the green phase which lasts for $ g $ seconds, traffic is allowed to proceed. After the green phase the light changes to red and remains in this color for $ r $ seconds. During the red phase traffic is prohibited from proceeding. If a vehicle reaches the intersection exactly at a time when the light changes to red, it should stop, but the vehicle is clear to proceed if the light has just changed to green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF187D/62435a41fe7e90193c8a9b88800f99834c7d7ef9.png)All traffic lights have the same timing and are synchronized. In other words the period of red (and green) phase is the same for all of traffic lights and they all start illuminating green at time zero.

The BRT Company has calculated the time that a bus requires to pass each road segment. A road segment is the distance between two consecutive traffic lights or between a traffic light and source (or destination) station. More precisely BRT specialists provide $ n+1 $ positive integers $ l_{i} $ , the time in seconds that a bus needs to traverse $ i $ -th road segment in the path from source to destination. The $ l_{1} $ value denotes the time that a bus needs to pass the distance between source and the first intersection. The $ l_{n+1} $ value denotes the time between the last intersection and destination.

In one day $ q $ buses leave the source station. The $ i $ -th bus starts from source at time $ t_{i} $ (in seconds). Decision makers of BRT Company want to know what time a bus gets to destination?

The bus is considered as point. A bus will always move if it can. The buses do not interfere with each other.

## 说明/提示

In the first sample, buses #1, #2 and #5 will reach the destination without waiting behind the red light. But buses #3 and #4 should wait.

In the second sample, first bus should wait at third, fourth and fifth intersections. Second and third buses should wait only at the fifth intersection.

## 样例 #1

### 输入

```
1 3 2
5 2
5
1
2
3
4
5
```

### 输出

```
8
9
12
12
12
```

## 样例 #2

### 输入

```
5 3 7
10 1 1 8 900000005 1000000000
3
1
10
1000000000
```

### 输出

```
1900000040
1900000040
2900000030
```

# 题解

## 作者：一粒夸克 (赞：14)


## BRT Contract

### solution 1：

**乱搞做法：**


模拟开车的过程，每一次遇到红灯时加上等绿灯所需的时间。

我们会发现我们开车过程中遇到红绿灯的情况，只与当前时间除以 $(g+r)$ 的余数有关。

而假如我们在 $i$ 路口停下了，我们再次出发的时间膜 $(g+r)$ 都等于 $0$ 。

因此只要我们在 $i$ 路口遇到了红灯，那么我们再次启动后走 $i->n$ 这段路径所需的时间是一定的。

因此我们可以试着记忆化一下：



```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,g,r,q;
long long a[100005],ans[100005];
vector<pair<long long,long long> >vec;
int main(){
	scanf("%lld%lld%lld",&n,&g,&r);
	for(int i=0;i<=n;i++)scanf("%lld",&a[i]);
	memset(ans,-1,sizeof(ans));
	scanf("%lld",&q);
	while(q--){
		long long x;
		scanf("%lld",&x);
		x+=a[0];
		for(int i=1;i<=n;i++){
			if(x%(g+r)>=g){
				x+=(g+r-x%(g+r));
				if(~ans[i]){
					x+=ans[i];break;
				}
				vec.push_back(make_pair(i,x));
			}
			x+=a[i];
		}
		for(vector<pair<long long,long long> >::iterator it=vec.begin();it!=vec.end();it++){
			ans[(*it).first]=x-(*it).second;
		}vec.clear();
		printf("%lld\n",x);
	}

	return 0;
}

```



这种做法看起来不是很靠谱，但在随机数据下的运行速度接近线性，碾压正解：

![](https://cdn.luogu.com.cn/upload/image_hosting/qv9fflmj.png)


可以看到，快了将近一倍。


### solution 2：

**正解：**

乱搞终归是乱搞，总是可以被特殊数据卡到 $O(qn)$ 的（比如本题的第 $34$ 个测试点）

之所以上面的算法会被卡，是因为它找到后面第一个红灯的路口仍然是在暴力找。

考虑优化这个过程。

对 $d$ 求一遍前缀和，在不考虑中途的红灯的情况下，如果在 $a$ 时刻出发，到达 $i$ 点的时间 $b$ ，那么 $b-d[i]≡a(mod$ $(g+r))$。

那么我们只要从后往前维护起始时间膜 $(g+r)$ 的每个余数对应的第一次遇到红灯的位置即可。

由于 $g$、$r$ 的范围很大，我们可以使用 ODT 或动态开点线段树维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,g,s,q;
map<int,int>mp;
inline void update(int l,int r,int i){
	if(l==r)return ;
	map<int,int>::iterator j=mp.lower_bound(l),k=mp.upper_bound(r);
	int tmp=(--k)->second;mp.erase(j,++k);mp[l]=i;mp[r]=tmp;
}
long long a[100005],t[100005];
int main(){
	scanf("%d%d%d",&n,&g,&s);
	s+=g;mp[0]=n+1;
	for(int i=1;i<=n+1;i++){
		scanf("%lld",&a[i]);a[i]+=a[i-1];
	}
	for(int i=n;i;i--){
		int l=(g-a[i]%s+s)%s,r=(s-a[i]%s);
		map<int,int>::iterator it=mp.upper_bound(r);
		int j=(--it)->second;
		t[i]=(j==n+1?a[n+1]-a[i]:(a[j]-a[i]+s-1)/s*s+t[j]);
		if(l<r)update(l,r,i);
		else update(0,r,i),update(l,s,i);
	}
	scanf("%d",&q);
	while(q--){
		int x;scanf("%d",&x);
		map<int,int>::iterator it=mp.upper_bound(x%s);
		int j=(--it)->second;
		printf("%lld\n",j==n+1?x+a[n+1]:(x+a[j]+s-1)/s*s+t[j]);
	}

	return 0;
}
```







---

## 作者：Zimse (赞：8)

不同时刻从家出发一旦在一个位置等了红灯之后花费的时间就固定不变了 , $f_i$ 表示从 $i$ 位置开始等完红灯 (可以理解为时刻为 $0$ ) 走到终点花费的时间 , 然后倒着计算。

如何找到第一个需要等红灯的位置呢 , 如果从开始到第 $i$ 个位置的距离模 $(g+r)$ 余数为 $p$ , 出发时间为 $t$ , 如果满足 $g \le (t+p) \% (g+r)$ 就代表需要等这个红灯 , 可以发现 $t$ 的区间有两种情况。

$p\le g : t\in[g-p,r+g-1-p]$

$g \lt p : t\in[0,r+g-1-p]\cup[m-p+g,m-1]$

维护一个线段树 , 支持区间set单点查询。

如何计算每一个 $f_i$ 呢 , 如果倒着往前考虑到 $i$ 时假定之前的没有经过红灯顺利过来的 , 在家等 $x$ 秒 , 使从家到第 $i$ 个位置刚好亮起绿灯 , 这样等价于时刻 $0$ ,最后花费时间减去从家到 $i$ 的时间和等的 $x$ 秒就是从 $i$ 位置开始走到终点花费的时间。

对于每一个询问 , 找出第一个遇到的红灯 $i$ , 从家到 $i$ 的时间加等红灯的时间加 $f_i$ 就是最终的答案。

因为值域比较大 , 要写动态开点线段树 , 注意数组开大一些。



------------


Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

#define int long long
#define Lid (ch[id][0])
#define Rid (ch[id][1])

using namespace std;

int read(){int qrx=0,qry=1;char qrc=getchar();
while(qrc<'0'||qrc>'9'){if(qrc=='-'){qry=-1,qrc=getchar();}else qrc=getchar();}
while(qrc>='0'&&qrc<='9')qrx=qrx*10+qrc-48,qrc=getchar();return qrx*qry;}

const int N=2e6+7,Mod=998244353,INF=1e12+7;
int n,m,G,R,d[N],X[N],f[N],Q,rt=1;
signed ch[N*8][2],tot=1,val[N*8];

void pushdown(int id,int len){
	if(val[id]&&len>1){
		if(!Lid)Lid=++tot;
		if(!Rid)Rid=++tot;
		val[Lid]=val[Rid]=val[id],val[id]=0;
	}
	return;
}

void update(int L,int R,int id,int l,int r,int x){
	pushdown(id,R-L+1);
	if(l<=L&&r>=R)val[id]=x,pushdown(id,R-L+1);
	else{
		int M=(L+R)>>1;
		if(l<=M)update(L,M,Lid,l,r,x);
		if(r>M)update(M+1,R,Rid,l,r,x);
	}
	return;
}

int query(int L,int R,int id,int x){
	pushdown(id,R-L+1);
	if(L==R)return val[id];
	int M=(L+R)>>1;
	if(x<=M)return query(L,M,Lid,x);
	else return query(M+1,R,Rid,x);
}

int Query(int t){
	int p=query(0,m-1,rt,t%m);
	int ans=t+X[p]+f[p];
	if(p<=n)ans+=m-(X[p]+t)%m;
	return ans;
}

signed main(){
	n=read(),G=read(),R=read(),m=G+R;
	for(int i=1;i<=n+1;i++)d[i]=read(),X[i]=X[i-1]+d[i];
	update(0,m-1,rt,0,m-1,n+1);
	for(int i=n,p=0;i>=1;i--){
		p=m-X[i]%m,f[i]=Query(p)-X[i]-p,p=X[i]%m;
		if(p<=G)update(0,m-1,rt,G-p,m-1-p,i);
		else update(0,m-1,rt,0,m-1-p,i),update(0,m-1,rt,m-p+G,m-1,i);
	}
	Q=read();
	for(int i=1;i<=Q;i++)printf("%lld\n",Query(read()));
	return 0;
}
```


---

## 作者：louhao088 (赞：6)

一道比较好的线段树题。

首先我们可以发现几个性质。

1. 你走的时间肯定有关于 $g+r$ 的周期，所以在模周期意义下相同的两个出发时间走完这一程的时间是相同的。

2. 如果你在一个红绿灯停住，那么你之后所走的到终点的时间是确定的。因为你从这个点出发时间在模周期下是相同的。

通过以上两个性质，我们很容易想到找到第一个停住的红灯，这个很明显可以用线段树查询，我们把所有红灯在模意义下的下标变为他的编号，每个人第一个停住的红灯就是在红灯这段时间内所走路程中模意义下的最小值，即他能碰到模意义下的红灯区间中最小的红灯。

因为是第一个碰到的红灯，所以之前一定是一直在走，这样我们只要拿这个红灯之前所用时间加上这个红灯后的时间即可。

每个红灯后所用时间是可以预处理的，具体的我们倒着往线段树里插数，对于每个红灯判断他之后第一个碰到的红灯，重复上述操作。

但是我么发现 $g+r$ 这个周期很大，我们可以离散化，然后再进行操作。就是注意不要拿离散后的数组进行询问操作。 ~~小蒟蒻就是因此在模拟赛上挂掉，还不知道。~~

时间复杂度 $O (n \log n)$。



------------
代码如下


```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define int long long
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
const int maxn=4e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn],T,b[maxn],tot=0,Min[maxn*4],s[maxn],d[maxn],f[maxn],t2,t1,l[maxn],q,x,ans;
void pushup(int rt){Min[rt]=min(Min[ls],Min[rs]);}
void build(int rt,int l,int r)
{
	if(l==r){Min[rt]=1e9;return;}
	build(ls,l,mid),build(rs,mid+1,r);pushup(rt);
}
void change(int rt,int l,int r,int x,int num)
{
	if(l>x||r<x)return;
	if(l==r){Min[rt]=num;return;}
	change(ls,l,mid,x,num),change(rs,mid+1,r,x,num),pushup(rt);
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 1e9;
	if(l>=L&&r<=R)return Min[rt];
	return min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));	
}
int get(int l,int r)
{
	int x=lower_bound(b+1,b+n+1,l)-b;
	int y=lower_bound(b+1,b+n+1,r)-b;
	if(b[y]>r)y--;if(y==n+1)y--;
	if(x>y)return 1e9;
	return query(1,1,n,x,y); 
}
int find(int s)
{
	int res=1e9,l,r;if(s==0)s=T;
	if(s<=t1)
		l=t1-s,r=T-s-1,res=min(res,get(l,r));
	else
	{
		l=0,r=T-s-1;res=min(res,get(l,r));
		l=t1-s+T,r=T-1;res=min(res,get(l,r));
	}
	if(res>n)return -1;
	return res;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),t1=read(),t2=read();T=t1+t2;
	for(int i=1;i<=n;i++)
	{
		l[i]=read(),s[i]=s[i-1]+l[i];b[i]=(s[i])%T;
	}l[n+1]=read();s[n+1]=s[n]+l[n+1];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		int u=lower_bound(b+1,b+n+1,s[i]%T)-b;
		d[i]=u;
	}
	build(1,1,n);f[n]=l[n+1];change(1,1,n,d[n],n);
	for(int i=n-1;i>=1;i--)
	{
		int x=find(T-b[d[i]]);
		if(x==-1)
			f[i]=s[n+1]-s[i];
		else
		{
			int k=(s[x]-s[i]-1)/T+1;
			f[i]=f[x]+k*T;
		}
		change(1,1,n,d[i],i);
	}
	q=read();
	for(int i=1;i<=q;i++)
	{
		x=read();
		int y=find(x%T);
		if(y==-1)
			ans=x+s[n+1];
		else
		{
			ans=f[y];int k=s[y]+x;k=(k-1)/T+1;
			ans=ans+k*T;
		}
		printf("%lld\n",ans);
	}
 	return 0;
}

```

如果有错请帮忙指出谢谢。


---

## 作者：lfxxx (赞：5)

模拟考最后一题是这道题，要是数组开大就场切了，最后不小心挂了 $15$ 分。

以下是考场思路：

考虑这样一个问题，所有时间对 $r+g$ 取余是可以的。毕竟红绿灯是一个循环。

再考虑这样一个东西，等过一次红灯后的所有情况是相似的，从循环的角度出发都是时刻 $0$。

因此考虑处理出出发之后第一次遇到红绿灯的点，然后问题就变成从一个路口到终点，可以使用一次 $n^2$ 的 dp 完成。

接下来先考虑如何处理第一次遇到红绿灯的点。

假若需要从之前的路口走到这个路口需要花费时间 $x$ 那么满足以下条件的出发时间 **可能** 会在这个点第一次遇到红绿灯。

$$t + x < g (\bmod (r+g))$$

第一次遇到红绿灯的点就是最小的 $x$。

实际上满足条件的 $t$ 根据与 $g$ 的大小关系构成至多两段区间，考虑动态开点权值线段树维护区间取最小值和单点查询。

接下来考虑如何优化上面那个 $n^2$ 的 dp 我们可以发现等完红绿灯出发与从起点出发的情况实际上是类似的，倒着扫描一遍且与上面那种情况类似的用线段树维护即可。

注意空间不要开小了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
const int inf = 1e9+114;
int tr[maxn*70+1],tag[maxn*70+1],ls[maxn*70+1],rs[maxn*70+1],tot; 
long long l[maxn],pre[maxn],dp[maxn];
long long cost[maxn];
long long G,R,n,q;
void pushdown(long long cur){
	if(ls[cur]==0) ls[cur]=++tot;
	if(rs[cur]==0) rs[cur]=++tot;
	tr[ls[cur]]=min(tr[ls[cur]],tag[cur]);
	tr[rs[cur]]=min(tr[rs[cur]],tag[cur]);
	tag[ls[cur]]=min(tag[ls[cur]],tag[cur]);
	tag[rs[cur]]=min(tag[rs[cur]],tag[cur]);
	tag[cur]=inf;
}
void pushup(long long cur){
	tr[cur]=min(tr[ls[cur]],tr[rs[cur]]);
}
void update(int &cur,long long lt,long long rt,long long l,long long r,int v){
	if(lt>rt) return ;
	if(l>rt||r<lt) return;
	if(cur==0) cur=++tot;
	if(l<=lt&&rt<=r){
		tr[cur]=min(tr[cur],v);
		tag[cur]=min(tag[cur],v);
		return ;
	}
	long long mid=(lt+rt-1)>>1;
	pushdown(cur);
	update(ls[cur],lt,mid,l,r,v);
	update(rs[cur],mid+1,rt,l,r,v);
	pushup(cur);
}
long long query(long long cur,long long lt,long long rt,long long l,long long r){
	if(l>rt||r<lt||cur==0) return inf;
	if(l<=lt&&rt<=r) return tr[cur];
	long long mid=(lt+rt-1)>>1;
	pushdown(cur);
	return min(query(ls[cur],lt,mid,l,r),query(rs[cur],mid+1,rt,l,r));
}
int rt;
void init(){
	for(long long i=1;i<=n;i++) pre[i]=(pre[i-1]+l[i])%(G+R),cost[i]=cost[i-1]+l[i];
	for(long long i=0;i<maxn*70;i++) tr[i]=tag[i]=inf;
	dp[n+1]=0;
	for(int i=n;i>=1;i--){
		long long x=(G+R-pre[i])%(G+R);
		long long y=query(rt,0,G+R-1,(x)%(G+R),(x)%(G+R));
		if(y<inf) dp[i]=dp[y]+(cost[y]-cost[i]+((G+R)-((cost[y]-cost[i])%(G+R))));
		else dp[i]=cost[n]-cost[i]+l[n+1];
		if(pre[i]<=G){
			update(rt,0,G+R-1,G-pre[i],R+G-1-pre[i],i);
		}
		else{
			update(rt,0,G+R-1,0,R+G-1-pre[i],i);
			update(rt,0,R+G-1,G+R-pre[i]+G,R+G-1,i);
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>G>>R;
	for(long long i=1;i<=n+1;i++) cin>>l[i];
	init();
	cin>>q;
	while(q--){
		long long x;
		cin>>x;
		long long st=query(rt,0,G+R-1,x%(G+R),x%(G+R));
		if(st==inf){
			cout<<x+cost[n]+l[n+1]<<'\n';
		}
		else{
			long long res=cost[st]+x+((G+R)-((cost[st]+x)%(G+R)));
			res+=dp[st];
			cout<<res<<'\n';
		}
	}
	return 0;
}
/*
4 5 1
12 18 4 6 7
5
4
11
5
3
2
*/
```


---

## 作者：Miko35 (赞：3)

题意：给定路（看做数轴）上 $n$ 个红绿灯的位置，从 0 时刻开始，红绿灯先绿 $g$ 秒，然后红 $r$ 秒。绿灯时，车可以通过红绿灯，红灯时只能在红绿灯的位置等待至绿灯。有 $q$ 组询问，每次询问一辆车从 0 位置、在 $t$ 时刻出发，到达终点的时间。

---

$\textrm{Solution}$：

简单题。

首先想到，可以维护 $f_i$ 表示 $0$ 时刻从 $i$ 点开始走到终点所需的时间。$f_i$ 的转移可以倒着扫一遍，则需求出 $0$ 时刻从 $i$ 点走到的第一个红灯位置 $j$，有 $f_i = f_j + \operatorname{calc}(i,j)$，其中 $\operatorname{calc}(i,j)$ 表示从 $i$ 走到 $j$ 且等到绿灯所花的时间。

而对于询问，我们可以看做是把起点到 $1$ 号灯之间的边加长了 $t$，用上述方法求 $f_0$ 即为答案。

问题就是，如何求在 $0$ 时刻从点 $i$ 开始走到的第一个红灯？

在走到红灯之前肯定是一路绿灯走过去的，所以走到的第一个红灯 $j$ 一定满足 $\operatorname{dis}(i,j) \bmod (g+r) \in [g,g+r-1]$，其中 $\operatorname{dis}(i,j)$ 表示 $i,j$ 两点在数轴上的距离。我们将 $l$ 数组做前缀和后，$\operatorname{dis}$ 可以差分，转化为 $(l_j - l_i) \bmod (g+r) \in [g,g+r-1]$。

此时可以把 $l_i$ 移动到右边，那么我们需要找到的是，$i$ 右边的第一个 $j$ 满足 $l_j \bmod (g+r)$ 在一个（两个）区间中。

由于是倒着扫的，所以可以将其放到线段树中，下标为 $l_i \bmod (g+r)$，权值为 $i$，查询即区间最小值。值域 $10^9$，需要动态开点。

```cpp
#include<bits/stdc++.h>
#define rgi register int
#define FOR(i,a,b) for(rgi i=a,i##i=b;i<=i##i;++i)
#define ROF(i,a,b) for(rgi i=a,i##i=b;i>=i##i;--i)
typedef long long ll;
using namespace std;
const int N=100010;
int n,q,G,R,P,mi[N<<6],ls[N<<6],rs[N<<6],C,rt,nx;
ll d[N],f[N];
#define mid ((l+r)>>1)
void upd(int x,int v,int& k=rt,int l=0,int r=P-1){
	if(l>x||r<x)return;
	mi[k?k:k=++C]=v;
	if(l!=r)upd(x,v,ls[k],l,mid),upd(x,v,rs[k],mid+1,r);
}
int qry(int x,int y,int k=rt,int l=0,int r=P-1){
	if(l>y||r<x||!k)return n+1;
	if(l>=x&&r<=y)return mi[k];
	return min(qry(x,y,ls[k],l,mid),qry(x,y,rs[k],mid+1,r));
}
int find(ll x){return min(qry(x-R,x-1),qry(x+G,x+P-1));}
ll calc(ll x,int w){return w>n?x:ceil(x*1.0/P)*P;}
signed main(){
	scanf("%d%d%d",&n,&G,&R),P=G+R,mi[0]=n+1;
	FOR(i,1,n+1)scanf("%lld",d+i),d[i]+=d[i-1];
	ROF(i,n,1){
		nx=find(d[i]%P);
		f[i]=f[nx]+calc(d[nx]-d[i],nx);
		upd(d[i]%P,i);
	}
	for(scanf("%d",&q);q--;){
		scanf("%lld",d),nx=find((P-d[0]%P)%P);
		printf("%lld\n",f[nx]+calc(d[nx]+d[0],nx));
	}
	return 0;
}

```



---

## 作者：shenxinge (赞：2)

给出一种不需要 ODT 和线段树的空间复杂度 $O(n)$，时间复杂度 $O(n \log{n} +q)$ 的做法。

对于 $d_i$ 做前缀和为 $h_i$，考虑到如果从 $a$ 时刻出发，不考虑中间的红灯的情况下，到达第 $i$ 个点的时刻为 $b$，则有 $a \equiv b-h_i \pmod{(r+g)} $，这样通过 $h_i$ 可以限制 $b$ 时刻为红灯的范围为 $[g-h_i,g-h_i+r)$。

考虑到一些询问是可以合并的，在同一个红灯内停下的询问可以变成一个新的从 $g-b+r$ 开始的询问，同时将他们的答案加上需要等待的时间，删除这些询问，然后在后面放进去这个新的询问就行了。

容易发现这些询问构成一个多叉树形式，一个询问的答案是从这个点到根的路径的和。

直接在树上求和即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std; constexpr int maxn(2e5+10);
int n,g,r,q,d[maxn],h[maxn],v[maxn],t[maxn],fa[maxn],cnt,rnd; set<pair<int,int> > s; bool vis[maxn];
inline int val(int u){if(vis[u]) return v[u]; else return vis[u]=true,v[u]+=val(fa[u]);}
inline void solve(int L,int R,int G){ vector<int> vec;
	for(auto it=s.lower_bound({L,0});it!=s.end()&&it->first<=R;s.erase(it),it=s.lower_bound({L,0})) vec.push_back(it->second),v[it->second]+=G-it->first;
	if((int)vec.size()>0){ s.insert({G%rnd,++cnt}); for(int x:vec) fa[x]=cnt;}
}
inline void calc(int L){ 
	L=(rnd-L+g)%rnd; int R=L+r-1,G=R+1; //printf("L: %d R: %d G: %d\n",L,R,G);
	solve(L,min(R,rnd-1),G); if(R>=rnd) solve(0,R-rnd,G-rnd);
}
signed main(){ //freopen("traffic.in","r",stdin);freopen("traffic.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr),cin >> n >> g >> r;
	rnd=(g+r); for(int i=0;i<=n;i++) cin >> d[i],h[i]=(i>0?h[i-1]:0)+d[i]; //puts("finish_read_d");
	cin >> q; cnt=q; for(int i=1;i<=q;i++) cin >> t[i],s.insert({t[i]%rnd,i}),v[i]=t[i];
	for(int i=0;i<n;i++) calc(h[i]%rnd); for(int i=1;i<=q;i++) cout << h[n]+val(i) << '\n';
	return 0;
}
```


---

## 作者：FjswYuzu (赞：1)

不妨将等待这个动作看成在 $0$ 时刻上了一条长度为 $t_i$ 的路，然后询问答案。这样每个询问变成了一开始是绿灯的情况。

然后相当于每次我们改变第一条路的权值，后面的路的信息不变。我们考虑预处理后面的信息，然后解决当前的问题。

注意到，如果求某个位置出发刚好为绿灯刚亮的时刻到达终点的时间就可以了，那么我们需要找到第一个撞红灯的位置，停下等到绿灯，发现又是一个子问题。这样后面的信息可以处理，询问也可以通过找到第一个撞红灯的位置算。（Motivation: 子问题转化）

那么现在要找到每个位置第一次撞红灯的位置。相当于一段后缀减去一段后缀对 $g+r$ 取模是否存在在某个红灯表示的区间，并且取最小值。这个问题可以用权值线段树解决。

因为值域很大，要用动态开点。

```cpp
void modify(LL l,LL r,LL &now,LL p,LL v)
{
	if(!now)	now=++cnt,minn[now]=n+1;
	minn[now]=min(minn[now],v);
	if(l==r)	return ;
	Mm;
	if(p<=mid)	modify(l,mid,lc[now],p,v);
	else	modify(mid+1,r,rc[now],p,v);
}
LL query(LL l,LL r,LL now,LL x,LL y)
{
	if(x>y)	return n+1;
	if(!now)	return n+1;
	if(x<=l && r<=y)	return minn[now];
	Mm,ret=n+1;
	if(x<=mid)	ret=min(ret,query(l,mid,lc[now],x,y));
	if(mid<y)	ret=min(ret,query(mid+1,r,rc[now],x,y));
	return ret;
}
LL g,r,d[100005],p;
int main(){
	n=read(),g=read(),r=read(),p=g+r;
	for(LL i=0;i<=n;++i)	d[i]=read();
	for(LL i=n;i;--i)
	{
		suf[i]=suf[i+1]+d[i];
		LL t=suf[i]%p;
		// [t+1, t+r]
		LL pos=query(0,p-1,rt,t+1,min(p-1,t+r));
		if(t+r>p-1)
		{
			LL dt=t+r-p;
			pos=min(pos,query(0,p-1,rt,0,dt));
		}
		if(pos==n+1)	dis[i]=suf[i];
		else
		{
			LL w=suf[i]-suf[pos];
			w%=p;
			w+=p;
			w%=p;
			w=p-w;
			dis[i]=(suf[i]-suf[pos]+dis[pos]+w);
		}
		modify(0,p-1,rt,t,i);
	}
	LL q=read();
	for(LL i=1;i<=q;++i)
	{
		LL T=read();
		LL d0=d[0]+T;
		T=T/p*p;
		suf[0]=suf[1]+d0;
		LL t=suf[0]%p;
		LL pos=query(0,p-1,rt,t+1,min(p-1,t+r));
		if(t+r>p-1)
		{
			LL dt=t+r-p;
			pos=min(pos,query(0,p-1,rt,0,dt));
		}
		if(pos==n+1)	write(suf[0]);
		else
		{
			LL w=suf[0]-suf[pos];
			w%=p;
			w+=p;
			w%=p;
			w=p-w;
			write(suf[0]-suf[pos]+dis[pos]+w);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Durancer (赞：1)

### 前言 

一个 $\text{Map}$ 跑过 主主树的题目。

### 前置知识

- $\text{Map}$ 的迭代器和一些内嵌函数的应用 

- 主主树

### Map

该部分感谢 @天梦 的讲解让我彻底悟了这个题目。

思维量最集中的部分就是预处理的部分了。

我们考虑这么一种情况，我们能否求出一个数组 $\text{Time}_i$ 表示在第 $i$ 个红绿灯的地方走到最后需要花费的时间为多少。

大概重要的预处理函数有一下几个：

```cpp
void Insert(int l ,int r,int id)
int Find(int x)
int calc(int x,int y)
```
我们考虑如何预处理出 $\text{Time}$ 数组：

首先对长度 $\text{len}_i$ 都做一个前缀和，设到达某一个红绿灯 $i$ 的时间为 $a$，那么考虑求出，到达这个红绿灯时，需要等待的到达时间的范围：

我们设出方程，求出到达的时间在一个红灯绿灯的周期中的位置。

$$a+len_i \equiv b\ (\bmod\  p)$$

把 $b = g , g + r$ 带入方程，求出两个范围 $a_1,a_2$。

在这里讨论两种情况，因为是在模意义下，所以：

- $[a_1,a_2)$

- $[0,a_2) , [a_1,g+r)$

这两种情况所代表的区间可能是会在第 $i$ 个红绿灯停下的时间。

然后我们考虑怎么覆盖这个区间。

因为长度的范围是 $10^9$ ，因此考虑用 $\text{map}$ 离散化。

$\text{map}$ 类型数组 $vis_i = k$ 表示在 $i$ 这个时间到达会最早在第 $k$ 个红绿灯被截住。

考虑第一个操作 $\text{Insert}$。

我们考虑如何可以找到从一个红绿灯 $i$ 开始走，被最早截住的红绿灯 $j$。

可以从后向前依次覆盖：

```cpp
void Insert(int l ,int r,int id)
{
	if(l == r) return;//因为得到的是一个左闭右开的区间，所以相等就是没有
	auto L = vis.lower_bound(l);
	auto R = vis.upper_bound(r);
	int lst = prev(R , 1) -> second;
	//保证找到的两个迭代器都是在 l，r 区间之内的覆盖 
	vis.erase(L,R);
	vis[l] = id;
	vis[r] = lst;
	//因为是从后向前，所以是直接覆盖当前的这个区间是最优的，因为最后要找到第一个被截住的  
}
```
**注：** $\text{prev}(it,len)$ 代表是返回迭代器 $\text{it}$ 前的第 $len$ 个迭代器。


画一个图图：

```cpp
x-----------x-----------x-----------x
       l-------------------r
       
```
这种情况下，$L$ 指向这第 $2$ 个 $x$ ， $R$ 指向这第 $4$ 个 $x$。

$\text{But}$ ，我们要覆盖的是 $[2,3]$ 这之间的 $x$ 。

而且这个区间一定是左闭右开的，所以更新时 $\text{vis}_r$ 里面应该是指向的下一个位置，也就是原本第 $3$ 个 $x$ 。

然后就可以实现覆盖了。

然后，我们考虑 $\text{Find}$ 函数的作用，找到从 $x$ 时间出发的最早的被拦截的红绿灯的编号。

这里同样体现出了从后向前更新的优点，因为枚举到红绿灯 $i$ 的时候，$vis$ 所存储的一定是往后的并且是最近的，因为更远的并且具有相同区间的一定会被覆盖掉，所以保证了最优性。

考虑如何用 $vis$ 数组进行查找，继续画图看;

```cpp
x--------x--------|--x-------x
                 pos
```

要找的是这个位置，那么肯定是 $\text{lower\_bound}$ 一下 $l$ ，然后返回前面一个即可。

```cpp
int Find(int x)
{
	x = x % mod;
	auto it = vis.upper_bound(x);
	int ret = prev(it , 1) -> second;
	return ret; 
}
```

最后最重要的是计算 $\text{Time}$ 值：

我们考虑预处理的时候怎么做？

再次声明 $\text{Time}$ 的意义：在红绿灯 $i$ **等到绿灯开始**，到达重点所花费的时间。

假设我们我们已经走了 $x$ 的距离，并且会在 $y$ 这个红绿灯处被截停，考虑计算一下其中的时间花费，首先声明的是，我们这个走了 $x$ 的距离，是必须保证走了这 $x$ 的距离之后正好处于完整的一个周期的初始位置（末尾位置一样）。

然后就考虑，如果 $y=n+1$ ，那么这一段花费的时间一定是 $len_y - x$。

反之，那么他走到这个地方停止之后，肯定会等到红灯结束之后也就是开启一个新的周期的时候，才会继续走，那么在这期间一定会是若干个完整的周期，所以我们就可以考虑到，计算这个周期的数量，并且一定会是向上取整的。

这里有一个小 $\text{trick}$：如果我们要对一个 $A$ 为一组，对 $a$ 求一共有多少个 $A$ 的数量向上取整的话，可以这么搞：

$$ans =\dfrac{a+A-1}{A}\times A$$

根据这个 $\text{trick}$ 同样可以得到这个计算周期的数量：

$$ans = \dfrac{len_y-x+mod-1}{mod}\times mod$$

但是我们的 $\text{calc}$ 函数计算的是，走了 $x$ 的距离，最近被截断的位置是 $y$ 红绿灯的情况的到达最后重点的时间，因为是从后向前枚举预处理，所以说靠后的 $\text{Times}$ 已经处理好了。

```cpp
int calc(int x,int y)//当前已经走了 x 的时间， 第一个被截住的路灯是 y  
{
	if(y == n + 1) return len[y] - x;
	else return ((len[y] - x + mod - 1) / mod ) * mod + Time[y];
	//其实就是 (len[y] - x) / A 向上取整 * A ;
	// + A - 1 是直接向上取整了。 
} 

```
最后询问的部分需要注意一个小地方，因为当前计算时候的 $x$ 都是在一个周期的开始，但是询问的时候初始的时间不一定会在一个周期的开始，那么考虑如何把他给转化一下，假如是这种情况：

```cpp
0---|----g-------r
    x
```

这种情况可以转化为：

```cpp
|--0---g---r
x
```

然后就可以保证都是整的区间了。(最后的地方多少有些理解上的问题，如有建议请私信指出）。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#define int long long
using namespace std;
const int N = 2e5 + 9;
const int M = 2e5 + 9;
int a[N],len[N]; 
int n,m,T;
int ans,val;
int g,r,mod;
int Time[N]; 
map<int,int> vis;//记录一下在 i 时刻 - > 下一个有元素的时刻，会被哪一个拦截住 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void Insert(int l ,int r,int id)
{
	if(l == r) return;//因为得到的是一个左闭右开的区间，所以相等就是没有
	auto L = vis.lower_bound(l);
	auto R = vis.upper_bound(r);
	int lst = prev(R , 1) -> second;
	//保证找到的两个迭代器都是在 l，r 区间之内的覆盖 
	vis.erase(L,R);
	vis[l] = id;
	vis[r] = lst;
	//因为是从后向前，所以是直接覆盖当前的这个区间是最优的，因为最后要找到第一个被截住的  
}
int calc(int x,int y)//当前已经走了 x 的时间， 第一个被截住的路灯是 y  
{
	if(y == n + 1) return len[y] - x;
	else return ((len[y] - x + mod - 1) / mod ) * mod + Time[y];
	//其实就是 (len[y] - x) / A 向上取整 * A ;
	// + A - 1 是直接向上取整了。 
} 
int Find(int x)
{
	x = x % mod;
	auto it = vis.upper_bound(x);
	int ret = prev(it , 1) -> second;
	return ret; 
}
void Prepare()
{
	for(int i = n ; i >= 1 ; i --)
	{
		// a + len[i] = b (mod mod ) , 
		// 带入之后，得到的 [a1,a2) 的时间内会在 i 这个红灯这个地方被截住 
		int l = (g - len[i] % mod + mod) % mod;
		int r = mod - len[i] % mod;
		//判断一下会被包含过的区间。
		int pos = Find(r);
		Time[i] = calc(len[i] , pos);
		
		if(l < r) Insert(l,r,i);
		else Insert(0,r,i) , Insert(l,mod,i); 
	}
}
void Query()
{
	int lst = 0;
	int x = 0;
	T = read();
	while(T --)
	{
		x = read();
		//x = (x ^ lst);
		int pos = Find(x);
		lst = calc(-x , pos);
		//因为这是已经经过的时间了。 
		printf("%lld\n",lst);
		lst = lst % 2147483647;
	}
}
signed main()
{
	n = read();
	g = read(); r = read();
	mod = g + r; 
	vis[0] = n + 1;//表示直接走到头即可 
	for(int i = 1; i <= n + 1; i ++)
		a[i] = read();
	for(int i = 1; i <= n + 1; i ++)
		len[i] = len[i - 1] + a[i];
	Prepare();
	Query();
	return 0;
}
```


最后奉上一份被干掉的~~主主树~~的做法，思路是一摸一样的

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define int long long 
using namespace std;
const int N=100010;
int tag[N*60];
int ls[N*60],rs[N*60];
int delta,l[N],n,g,r;
int tot,q,root;
int get(int p,int l,int r,int x)
{
    if(!p)
        return 0;
    if(tag[p] != -1)
        return tag[p] - (x-l);
    int mid = (l+r) >> 1;
    if(x <= mid)
        return get( ls[p] , l , mid , x);
    else 
        return get( rs[p] , mid+1 , r , x );
}
int get(int x) // 查找以 x 时间开始,需要的停留时间 , 当然要加上所有的长度的停留的时间 
{
    x = (x + delta) % (g+r);
    return get(root , 0 , g+r-1 , x);
}
int newnode()
{
    tot++;
    tag[tot] = -1;
    return tot;
}
void cov(int&p , int x)
{
    if(!p)
        p = newnode();
    tag[p] = x;
}
void cov(int&p,int l,int r,int L,int R,int x)
{
    if(!p)
        p = newnode();
    if(L <= l and r <= R)
    {
        cov(p,x);
        return;
    }
    int mid = (l+r)>>1;
    if(tag[p] != -1)
    {
        cov(ls[p] , tag[p]);
        cov(rs[p] , tag[p]-(mid-l+1));
        tag[p] = -1;
    }
    if(L <= mid)
        cov(ls[p] , l , mid , L , R , x);
    if(R>mid)
        cov(rs[p] , mid + 1 , r , L , R , x-max( 0ll , (mid + 1 - max( l , L))));   
}
void cov(int L,int R,int x)
{
    L = (L + delta) % (g + r);
    R = (R + delta) % (g + r);
    if(L <= R)
        cov(root , 0 , g + r - 1 , L , R , x);
    else 
        cov(root , 0 , g + r - 1 , L , g + r - 1 , x ), cov(root , 0 , g + r - 1 , 0 , R , x - ( g + r - L ));
} 
signed main()
{
    scanf("%lld%lld%lld",&n,&g,&r);
    for(int i = 1; i <= n + 1; i ++)
        scanf("%lld",&l[i]);
    for(int i = n + 1 ; i > 1 ; i --)
    {
        int tmp = get(l[i]);
        delta = (delta + l[i]) % (g+r);
        cov( g , g + r  - 1 , tmp + r );
    }
    delta = (delta + l[1] ) % (g + r);
    int sum = 0;
    for(int i = 1 ; i <= n + 1; i++)
        sum += l[i];
    scanf("%lld",&q);
    int ans = 0;
    while(q--)
    {
        int t;
        scanf("%lld",&t);
        t ^= ans % 2147483647;
        printf("%lld\n",ans = get( t %(g+r)) + sum + t);
    	ans = 0;
	}
    return 0;
}

```

---

