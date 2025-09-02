# [IOI 2013] robots 机器人

## 题目描述

Marita 的弟弟把玩具扔在客厅地板上，乱七八糟。庆幸的是，Marita 设计了一种特殊的机器人可以收拾玩具。 不过，她需要确定哪个机器人去拣起哪个玩具。

一共有 $T$ 个玩具,整数 $W[i]$ 表示这个玩具的重量，整数 $S[i]$ 表示这个玩具的体积。机器人有两种，分别是：弱机器人和小机器人。

- 有 $A$ 个弱机器人。每个弱机器人有一个重量限制 $X[i] $，它只能拿起重量严格小于 $X[i]$ 的玩具，与玩具的体积大小没关系。
- 有 $B$ 个小机器人。每个小机器人有一个体积限制 $Y[i] $，它只能拿起体积严格小于 $Y[i]$ 的玩具，与玩具的重量大小没有关系。

Marita 的每个机器人用 $1$ 分钟将一个玩具拿走放好。不同的机器人可以同时拿走并放好不同的玩具。

你的任务是确定 Marita 的机器人是否可以将所有的玩具都收拾好，如果是，那么最少用多少时间可以收拾好。


## 说明/提示

对于 $100\%$ 的数据，$1 \le T \le 10^6$，$0 \le A,B \le 5 \times 10^4$ 且 $1 \le A+B$，$1 \le X[i],Y[i],W[i],S[i] \le 2 \times 10^9$。

## 样例 #1

### 输入

```
3 2 10
6 2 9
4 7
4 6
8 5
2 3
7 9
1 8
5 1
3 3
8 7
7 6
10 5

```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1 3
2 5
2
3 1
5 3
2 2
```

### 输出

```
-1```

# 题解

## 作者：s_r_f (赞：9)

首先题意可以转化为$:$每个玩具有两个属性值$x_i,y_i,$弱机器人可以拿掉$x_i<A_i$的玩具$,$小机器人可以拿掉$y_i<B_i$的玩具$.$

不难想到可以二分答案$.$

考虑如何$check$是否能在$mid$分钟的时间内拿走所有的玩具$.$

首先如果只有一维$,$显然可以直接对$x_i$和$A_i$排序然后丢掉多余的机器人$,$直接比大小即可$.$

那么多加了一维就是对$x$先贪心$,$每次尽量拿走$y$更大的数字即可$.$

这个贪心很容易用一个堆来实现$.$

$O(n\log ans \log n).$

代码 $:$

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	x = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
const int N = 500005,M = 100005;
struct st{ int x,y; bool operator < (const st w) const{ return x < w.x; } }p[N];
int A,B,n,a[M],b[M],ca[M],cb[M]; priority_queue<int>H;
inline bool check(int Mid){
	int i;
	for (i = 1; i <= A; ++i) ca[i] = Mid;
	for (i = 1; i <= B; ++i) cb[i] = Mid;
	int now = 1;
	while (!H.empty()) H.pop();
	for (i = 1; i <= A; ++i){
		while (now <= n && p[now].x < a[i]) H.push(p[now].y),++now;
		while (ca[i]-- && !H.empty()) H.pop();
	}
	while (now <= n) H.push(p[now].y),++now;
	for (i = B; i >= 1; --i)
		while (!H.empty() && cb[i]-- && b[i] > H.top()) H.pop();
	return H.empty();
}
int main(){
	int i;
	read(A),read(B),read(n);
	for (i = 1; i <= A; ++i) read(a[i]); sort(a+1,a+A+1);
	for (i = 1; i <= B; ++i) read(b[i]); sort(b+1,b+B+1);
	for (i = 1; i <= n; ++i) read(p[i].x),read(p[i].y); sort(p+1,p+n+1);
	int Ans = -1,L = 1,R = n,Mid;
	while (L <= R){ Mid = L+R>>1; if (check(Mid)) R = Mid-1,Ans = Mid; else L = Mid + 1; }
	cout << Ans << '\n';
	return 0;
}
```

---

## 作者：piantouqu (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P5894)

思路
---
我们发现，如果在第 $i$ 分钟可以收拾好，那么在第 $i+1$ 分钟必然可以收拾好，所以考虑二分答案。

然后我们想如何才能更快的收拾好：对机器人的限制大小从小到大排序后，让弱机器人去拿它能拿起的最大玩具，再让小机器人拿剩余的玩具。如果最后还有剩余，则说明无法收拾好。

code
---
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dep(i,r,l) for(int i=(r);i>=(l);i--)
using namespace std;

int A,B,T;
int x[50005],y[50005];
struct toy{
	int x,y;
	bool operator < (const toy z) const{return x<z.x;} 
}a[1000005];
priority_queue<int> p;

bool check(int mid){
	while(!p.empty()) p.pop();
	int tot=1;
	rep(i,1,A){
		while(tot<=T&&a[tot].x<x[i]) p.push(a[tot].y),tot++;
		rep(j,1,mid){
			if(p.empty()) break;
			p.pop();
		}
	}
	while(tot<=T) p.push(a[tot].y),tot++;
	dep(i,B,1){
		if(p.empty()) break;
		rep(j,1,mid){
			if(p.empty()||p.top()>=y[i]) break;
			p.pop();
		}
	}
	return p.empty();
}

signed main(){
	scanf("%d%d%d",&A,&B,&T);
	rep(i,1,A) scanf("%d",x+i);
	rep(i,1,B) scanf("%d",y+i);
	rep(i,1,T) scanf("%d",&a[i].x),scanf("%d",&a[i].y);
	sort(a+1,a+1+T);sort(x+1,x+1+A);sort(y+1,y+1+B);
	int ans=-1,l=1,r=T;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：redegg (赞：4)

~~嗯，别人说了我才会做的。~~

这题贪心不难：

假设我们知道了最大的次数为w。

代码中n个a组，m个b组，k个树。

两种工人a组，b组。

分别从小到大排序a，b组。

树的果实x，高度y，以果实（高度也可以，那么后面反过来）从小到大排序。

对于a[ i ]，把比a[ i ]小的x[ j ]全部找出来，这些树都可以被a[ i ]，a[ i+1 ]，a[ i+2 ]......a[ n ]工人给收集。

那么对于a[ i ]工人，我们就尽量收集到w次（w为已经知道的最大次数），而这w次，尽量以从高到低来收集，这样就可以保证高的树能被收集。

贪心过程如上，没做到ai，就找到所有的xj<ai,然后把yj丢到堆里维护，然后每次从堆里丢出最大的yj，一共丢w次，如果到最后能丢完，w成立。

w这么求呢？二分答案即可。

代码如下：（还有坑，自己想吧）

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,k;

int a[100000];
int b[100000];

struct ha
{
    int x,y;
    bool operator <(const ha &aa)const
    {
        return x<aa.x;
    }
}c[100000];
priority_queue<int> p;

bool run(int mi)
{
    while(!p.empty())
        p.pop();
    int d=1;
    for(int i=1;i<=n;i++)
    {
        while(d<=k&&c[d].x<a[i])
        {
            p.push(c[d].y);
            d++;
        }
        for(int j=1;j<=mi;j++)
        {
            if(p.empty())break;
            p.pop();
        }
    }
    while(d<=k)
    {
        p.push(c[d].y);
        d++;
    }
    for(int i=m;i>=1;i--)
    {
        int kk=0;
        if(p.empty())break;
        while(!p.empty()&&p.top()<b[i]&&kk<mi)
        {
            kk++;
            p.pop();
        }
    }
    if(!p.empty())return false;
    else return true;
}

void erfen(int l,int r)
{
    if(l==r&&run(l))
    {
        printf("%d\n",l);
        exit(0);
    }
    if(l==r&&run(l)!=true)
    {
        return ;
    }
    int mid=(l+r)/2;
    if(run(mid))erfen(l,mid);
    else erfen(mid+1,r);
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    sort(b+1,b+1+m);

    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&c[i].x,&c[i].y);
    }
    sort(c+1,c+1+k);
    erfen(1,k);

    printf("Impossible\n");
    return 0;
}

```

---

## 作者：Purple_wzy (赞：3)

题面：https://www.luogu.com.cn/problem/P4835

题解：我们先将规划性问题转化为判定性问题：二分答案。

现在的问题是：如何check?
设当前二分的答案为$T$,也就是说每个工人最多采摘$T$次。

考虑如何规划才能采完所有果子。

对于对数目$w$有限制的工人，若将他们按$a[i]$(限定数目)

排序，可以发现：$a[i]$越小，能摘的东西就越少。~~废话~~

而我们又想“人尽其用”，于是我们发现一种可行的贪心策略：

对于$a[i]$小的工人，让他们在能力范围内尽量摘$h[i]$大的果子。

想想这么做为什么是正确的：对于$h[i]$越大的果子，能摘它的
b类工人越少，因此a类工人摘这些果子总是最优的。

整个过程可以用一个大根堆来实现。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
typedef pair<int,int>pii;
struct P{
	int h,w,id;
}p[101000];
priority_queue<pii>q;
pii nd;
int n,m,A,B,a[50500],f[50500],b[50500],g[50500],vis[101000];
inline bool bb2(P x,P y){return x.h^y.h?x.h<y.h:x.w<y.w;}
inline bool bb1(P x,P y){return x.w^y.w?x.w<y.w:x.h<y.h;}
IN ck(int x){
	memset(vis,0,sizeof(vis));
	while(!q.empty())q.pop();m=0;
	F(i,1,A){
		while(m<n&&p[m+1].w<a[i])m++,q.emplace(make_pair(p[m].h,m));
		for(re j=1;j<=x&&!q.empty();j++){
			nd=q.top();q.pop();
			vis[nd.second]=1;
		}
	}
	F(i,m+1,n)q.emplace(make_pair(p[i].h,i));
	if(q.empty())return 1;
	FOR(i,B,1){
		for(re j=1;j<=x&&!q.empty();j++){
			nd=q.top();q.pop();
			if(b[i]<=nd.first)return 0;
		}
		if(q.empty())return 1;
	}
	if(q.empty())return 1;
	return 0;
}
IN divided(int x,int y){
	//cout<<x<<" "<<y<<endl;
	if(x==y)return x;
	re mid=(x+y)>>1;
	if(ck(mid))y=mid;
	else x=mid+1;
	return divided(x,y);
}
int main(){
	read(A);read(B);read(n);
	F(i,1,A)read(a[i]);sort(a+1,a+1+A);
	F(i,1,B)read(b[i]);sort(b+1,b+1+B);
	F(i,1,n)read(p[i].w),read(p[i].h);
	sort(p+1,p+1+n,bb1);
	FOR(i,n,1){
		if(a[A]<=p[i].w&&b[B]<=p[i].h){
			cout<<"Impossible";
			return 0;
		}
	}
	m=A+B;
	if(n%m==0)m=n/m;
	else m=(n/m)+1;
	//system("pause");
	printf("%d",divided(m,n));
	return 0;
}
```
推荐一下我的博客：https://www.cnblogs.com/Purple-wzy/

---

## 作者：Querainy (赞：3)

二分+贪心+并查集，同时是模拟最大流(也许可以这么叫?)的简单练手题。

(学了一点模拟费用流之后就什么贪心都想模拟费用流解释了)

首先看到最小化最大时间，先二分一下，问题变成$d$分钟能不能拿完所有玩具。

考虑最大流。显然可以这么建图 : $s$向每个玩具连$1$，表示每个玩具被拿一次；每个机器人向$t$连$d$，表示每个机器人能拿的玩具数；每个玩具向最菜的能拿它的机器人连$1$，每个弱鸡(弱 鸡 气 人)向第一个比它强的弱鸡连$\infty$，每个小鸡向第一个比它大的小鸡连$\infty$，表示这个拿不了的话，可以推给比它巨的。如果跑出来最大流是$n$(玩具个数)，那么说明可以拿完。

比如这是样例的图(a是弱鸡，b是小鸡) : 

![](https://cdn.luogu.com.cn/upload/image_hosting/v4ktg1vp.png)

呃好像中间有点挤，不管了。

然后最大流有一个棒到不行的性质 : (加反向边后)不管以何种方式寻找增广路，只要找到最后没再有增广路，那么找到的一定是最大流。

所以我们考虑扫一遍玩具，尝试把所有玩具都给弱鸡来搬，如果弱鸡搬不动了再让一个玩具反悔给小鸡搬。

然后因为越巨的机器人能搬的肯定越多，我们希望每次都让能搬当前玩具的最菜的机器人来搬。

那么反悔哪一玩具呢?贪心地，我们希望反悔(反悔之后可以给当前玩具腾出空来的)体积最小的那个，这样它才更有可能被小鸡来搬。如果最小的那个也没有小鸡可以搬它，那么显然有玩具搬不完了。

于是我们得到了一个算法 : 二分答案，扫一遍玩具，用线段树+堆维护弱鸡的反悔，用并查集分别维护两种机器人中的空位。

这个线段树+堆好像有点麻烦并且过不了1e6，发现我们每次要反悔的时候总是尝试反悔体积最小的，那么直接按体积从大到小对玩具排序，这样当前物品就总是体积最小的了。

时间复杂度$O(n\log^2 n)$，或$O(n\log n\alpha (n))$。然而不按秩合并也能过（

题面里的数据范围错了?$A,B$范围应该是是$10^6$?

代码 : 

```cpp
#include<iostream>
#include<string.h>
#include<algorithm>
using std::cin;
using std::cout;
using std::sort;
using std::upper_bound;

inline int max(int x,int y)
{
	return x>y?x:y;
}

struct UnionFindSets
{
	int f[1000002];
	
	inline void init(int n)
	{
		for(int i=1;i<=n;i++)
			f[i]=i;
	}
	
	int find(int x)
	{
		if(f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	
	inline void join(int x,int y)
	{
		f[find(x)]=find(y);
	}
}f1,f2;

int a,b,n,x[1000002],y[1000002];

struct Toy
{
	int w,s;
}t[1000002];

inline bool cmp(Toy x,Toy y)
{
	return x.s>y.s;
}

int c1[1000002],c2[1000002],p1[1000002],p2[1000002];

inline bool check(int d)
{
	f1.init(a+1),f2.init(b+1);
	memset(c1,0,sizeof(c1));
	memset(c2,0,sizeof(c2));
	for(int i=1;i<=n;i++)
	{
		int u=f1.find(p1[i]);
		if(u!=a+1)
		{
			c1[u]++;
			if(c1[u]==d) f1.join(u,u+1);
		}
		else
		{
			int v=f2.find(p2[i]);
			if(v!=b+1)
			{
				c2[v]++;
				if(c2[v]==d) f2.join(v,v+1);
			}
			else return false;
		}
	}
	return true;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>a>>b>>n;
	int mxx=0,mxy=0;
	for(int i=1;i<=a;i++)
		cin>>x[i],mxx=max(mxx,x[i]);
	for(int i=1;i<=b;i++)
		cin>>y[i],mxy=max(mxy,y[i]);
	sort(x+1,x+a+1),sort(y+1,y+b+1);
	for(int i=1;i<=n;i++)
	{
		cin>>t[i].w>>t[i].s;
		if(t[i].w>=mxx&&t[i].s>=mxy)
		{
			cout<<-1;
			return 0;
		}
	}
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=n;i++)
		p1[i]=upper_bound(x+1,x+a+1,t[i].w)-x;
	for(int i=1;i<=n;i++)
		p2[i]=upper_bound(y+1,y+b+1,t[i].s)-y;
	int l=1,r=n,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：Episode9 (赞：3)

过于amazine……这道题目我和题解打法都不一样……

我的思路是先将玩具按照体积排序，机器人都按照搬运能力(体积重量)升序排序。然后二分答案，用upper_bound查找并且让第一个能拿重量大于当前玩具重量的弱机器人拿(因为这样能先把体积大的取走)，若当前弱机器人拿了会导致时间超标就给下一个（下一个超标就给下下一个，用并查集或者线段树维护未超标的位置，不用的话暴力while只有，会TLE）。然后剩下的全给小机器人拿，不过upper_bound查询的是能拿体积大于当前未被弱机器人拿走玩具体积的小机器人，然后和弱机器人一样操作，用并查集或者线段树维护位置。最后看看能不能把所有玩具全部拿走，二分出结果即可。
[不要脸宣传](https://voidstruct.solstice23.top/2020/05/20/bzoj3248-ioi2013robots/)
```cpp
#include<bits/stdc++.h>
#define Maxn 2000005
using namespace std;
inline void read(int &x)
{
	int f=1;x=0;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
struct robot{int w,v;bool vis;}p[Maxn];
int A,B,T,X[Maxn],Y[Maxn],l=1,r=1000000,ans,robot_time[Maxn],fa[Maxn];
inline int getfa(int x){if (x==fa[x]) return x;return fa[x]=getfa(fa[x]);}
bool cmp(robot a,robot b){return a.v>b.v;}
inline bool check(int Tim)
{
	int cnt=0;
	for (int i=1;i<=T;i++) p[i].vis=0;
	for (int i=1;i<=A;i++) fa[i]=i; 
	memset(robot_time,0,sizeof(robot_time));
	for (int i=1;i<=T;i++)
	{
		int x=upper_bound(X+1,X+A+1,p[i].w)-X;if (x>A) continue;
		if (robot_time[getfa(x)]<Tim) robot_time[getfa(x)]++,cnt++,p[i].vis=1;
		if (robot_time[getfa(x)]==Tim&&getfa(x)!=A) fa[getfa(x)]=getfa(getfa(x)+1);
	}
	memset(robot_time,0,sizeof(robot_time));
	for (int i=1;i<=B;i++) fa[i]=i; 
	for (int i=1;i<=T;i++)
	{
		if (p[i].vis==1) continue;
		int x=upper_bound(Y+1,Y+B+1,p[i].v)-Y;if (x>B) continue;
		if (robot_time[getfa(x)]<Tim) robot_time[getfa(x)]++,cnt++;
		if (robot_time[getfa(x)]==Tim&&getfa(x)!=B) fa[getfa(x)]=getfa(getfa(x)+1);
	}
	return cnt==T;
}
int main()
{
	read(A),read(B),read(T);
	for (int i=1;i<=A;i++) read(X[i]);
	for (int i=1;i<=B;i++) read(Y[i]);
	for (int i=1;i<=T;i++) read(p[i].w),read(p[i].v);
	sort(p+1,p+T+1,cmp);
	sort(X+1,X+A+1);
	sort(Y+1,Y+B+1);
	while (l<=r)
	{
		int mid=l+r>>1;
		if (check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if (ans==0) puts("-1");else cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：ChickyHas (赞：1)

模拟赛考了这道题，似乎并不太难？

许多人往模拟费用流方面去想的，但是我想的就是硬贪。

看到这种题，先想到二分答案判断可行性。

对于一个机器人使用的次数是固定的，那么我们如何最大化他的价值呢？

可以将数对按第一维排序，弱机器人升序排序，用弱机器人去扫，**每次应该解决能力范围内第二维尽量大的**，这样可以减轻小机器人的负担，通过一个大根堆进行维护。

那么我们最后再把剩下的数对用小机器人从大到小，因此小机器人从大到小排序，不断取堆顶就可以了。

复杂度是 $O(T\operatorname{log^2}T)$ 的。

---

## 作者：dyc2022 (赞：1)

这是一道 IOI 原题。
***
显然答案是满足单调性的，因为如果你能在 $x$ 的时间内完成，那就一定能在 $x+1$ 的时间内完成。我们抓住这个性质，就可以使用二分答案。

那么假设我们已经二分出了当前答案 $m$，那么我们可以使用一个贪心的方法：因为 weak 机器人没有体积限制，因此我们要让每一个 weak 机器人都拿起自己能够拿起的玩具中体积最大的，这一步我们可以用一个堆来将体积小的放到堆顶。然后我们就可以再让 small 机器人来取堆中剩余的玩具，如果最后堆不为空，则说明有的玩具是不能被取完的。

细节不多，详见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 1000006
#define M 50006
using namespace std;
namespace IO
{
	int read()
	{
		int ret=0,bas=1;char ch=getchar();
		while(!isdigit(ch)&&ch!='-')ch=getchar();
		if(ch=='-')bas=-1,ch=getchar();
		while(isdigit(ch))ret=(ret<<3)+(ret<<1)+(ch^48),ch=getchar();
		return bas*ret;
	}
	void write(int k)
	{
		if(!k)return;
		write(k/10);
		putchar(k%10^48);
	}
	void print(int k)
	{
		if(k==0)putchar('0');
		else if(k<0)putchar('-'),write(-k);
		else write(k);
	}
}
using namespace IO;
int n,m,k;
int a[N],b[N];
struct Node{int w,s;}c[N];
bool cmp(int x,int y){return x>y;}
bool cmp2(Node x,Node y){return x.w<y.w;}
bool operator <(Node x,Node y){return x.s<y.s;}
priority_queue<Node> q;
bool check(int mid)
{
	while(!q.empty())q.pop();
	int last=1;
	for(int i=1;i<=n;i++)
	{
		for(;last<=k&&c[last].w<a[i];last++)q.push(c[last]);
		for(int j=1;j<=mid&&!q.empty();j++)q.pop();
	}
	for(;last<=k;last++)q.push(c[last]);
	for(int i=1;i<=m;i++)
	{
		if(!q.empty()&&q.top().s>=b[i])return 0;
		for(int j=1;j<=mid&&!q.empty();j++)q.pop();
	}
	return q.empty();
}
main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+1+n),sort(b+1,b+1+m,cmp);
	for(int i=1;i<=k;i++)c[i]={read(),read()};
	sort(c+1,c+1+k,cmp2);
	int l=0,r=2e6,ans=2e6;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	print((ans==2e6)?-1:ans);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16799733.html)

[题目传送门](https://www.luogu.com.cn/problem/P5894)
## 思路
简单题，设函数 $f_i$ 表示当时间为 $i$ 时是否能够收拾好所有玩具，则 $f_i$ 显然是单调的。

所以我们可以考虑二分。

设我们当前二分到 $x$，我们先把 $x$ 数组按从小到大排序，$y$ 数组按从大到小排序。

我们先扫 $x$ 数组，假设我们当前扫到了 $x_i$，$1$ 至 $j$ 的玩具可以被 $i$ 安放，则，贪心的想，这些玩具对于 $x$ 数组的意义是相同的，但是这些玩具的 $s$ 值是不同的，为了尽可能存在答案，我们需要尽量给遍历 $y$ 数组时留下尽可能小的 $s$ 值，所以我们选取最大的 $x$ 个 $s$ 值删掉。

接下来扫 $y$ 数组，每次都尽可能删去值，若最后被删空，则成立，否则不成立。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e6+10;
int x[N],y[N],w[N],s[N],n,m,t;
struct node{int w,s;}a[N];
inline bool cmp(node x,node y){return x.w<y.w;}
inline bool check(int lim){
    priority_queue<int>q;
    int r=0;
    for (int i=1;i<=n;++i){
        while (a[r+1].w<=x[i] && r+1<=t) q.push(a[++r].s);
        int xx=lim;
        while (!q.empty() && xx--) q.pop();
    }
    while (r<t) q.push(a[++r].s);
    for (int i=1;i<=m;++i){
        if (q.empty()) break;
        if (q.top()>y[i]) return 0;
        int xx=lim;
        while (!q.empty() && xx--) q.pop();
    }
    if (!q.empty()) return 0;
    return 1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>t;
    for (int i=1;i<=n;++i) cin>>x[i],--x[i];sort(x+1,x+n+1);
    for (int i=1;i<=m;++i) cin>>y[i],--y[i];sort(y+1,y+m+1);reverse(y+1,y+m+1);
    for (int i=1;i<=t;++i) cin>>a[i].w>>a[i].s;sort(a+1,a+t+1,cmp);
    int l=0,r=1e9;
    while (l<r){
        int mid=(l+r)>>1;
        if (check(mid)) r=mid;
        else l=mid+1;
    }
    if (l==1e9) l=-1;
    cout<<l<<'\n';
    return 0;
}
```


---

## 作者：xuantianhao (赞：0)

# [P5894 robots 题解](https://www.luogu.com.cn/problem/P5894)

## 题意：

应该就不用我多说了，~~但凡自己推过样例就都应该知道这道题是个什么意思了...~~

那么这道题目显而易见，应该用二分！

别问我是怎么想到二分的...~~问就是**玄学**！~~

我们可以写一个 $check$ 函数，$check(x)$ 中 $x$ 为当前二分的答案，意思也就是每个机器人最多收集 $x$ 次。

首先对于第一种弱机器人，需要考虑的是玩具的重量，所以我们可以对弱机器人从小到大排序，输入的值越小的机器人能搬动的玩具也就越小。（~~感觉像一堆废话~~）

这个时候就可以采用贪心的思想，让那些最弱的弱机器人在他们的能力范围内去收集体积最大的玩具，显然这样子的方法是最优的，因此我们就只需要有一个大根堆来维护就可以了。

然后就可以先写出这样一个程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=1e6+100;
struct node{
	LL w,s;
}toy[N];
LL A,B,T;
LL x[N],y[N];
priority_queue<LL> q;
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
bool cmp(node a,node b){return a.w<b.w;}
bool check(LL u){
	？？？？？
}
void work(LL l,LL r){
	LL ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	printf("%lld",ans);
}
int main() {
	A=read();B=read();T=read();
	for(int i=1;i<=A;i++) x[i]=read();
	for(int i=1;i<=B;i++) y[i]=read();
	for(int i=1;i<=T;i++) toy[i].w=read(),toy[i].s=read();
	sort(x+1,x+A+1);
	sort(y+1,y+B+1);
	sort(toy+1,toy+T+1,cmp);
	work(0,T);
	return 0;
}
```

现在就只差这个 $check$ 函数了。

那么该怎么写呢？

然后这个代码我调了好久好久，最后二分的时候要多次调用 $check$ 函数，所以在每次调用 $check$ 函数之前都应该把这个大根堆清空，并且在后面倒推的时候也是需要清空的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=1e6+100;
struct node{
	LL w,s;
}toy[N];
LL A,B,T;
LL x[N],y[N];
priority_queue<LL> q;
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
bool cmp(node a,node b){return a.w<b.w;}
bool check(LL u){
	while(!q.empty()) q.pop();
	LL now=1;
	for(int i=1;i<=A;i++){
		while(now<=T&&toy[now].w<x[i]){
			q.push(toy[now].s);
			now++;
		}
		for(LL j=1;j<=u;j++){
            if(q.empty()) break;
            q.pop();
        }
	}
	while(now<=T){
        q.push(toy[now].s);
        now++;
    }
	for(int i=B;i>=1;i--){
		LL op=0;
        if(q.empty()) break;
        while(!q.empty()&&q.top()<y[i]&&op<u){
            op++;
            q.pop();
        }
	}
	return q.empty();
}
void work(LL l,LL r){
	LL ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	printf("%lld",ans);
}
int main() {
	A=read();B=read();T=read();
	for(int i=1;i<=A;i++) x[i]=read();
	for(int i=1;i<=B;i++) y[i]=read();
	for(int i=1;i<=T;i++) toy[i].w=read(),toy[i].s=read();
	sort(x+1,x+A+1);
	sort(y+1,y+B+1);
	sort(toy+1,toy+T+1,cmp);
	work(0,T);
	return 0;
}
```

---

