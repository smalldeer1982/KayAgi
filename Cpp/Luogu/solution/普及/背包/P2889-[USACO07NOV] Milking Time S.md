# [USACO07NOV] Milking Time S

## 题目描述

Bessie 可以在接下来 $N$ 个小时内产奶，为了方便，我们把这 $N$ 个小时 $1\dots N$ 编号。

FJ 在这 $N$ 个小时内有 $M$ 段时间可以来给 Bessie 挤奶，第 $i$ 段时间从 $Start_i$ 开始到 $End_i$ 结束，可以得到 $Eff_i$ 加仑牛奶。

每次 FJ 给 Bessie 挤奶之后，Bessie 都要休息 $R$ 个小时，FJ 才能开始下一次挤奶。

现在，FJ 需要您计算出 Bessie 在这 $N$ 个小时内最多产多少奶。

## 说明/提示

#### 数据规模与约定
对于全部的测试点，保证 $1\le N\le 10^6$，$1\le M\le 10^3$，$1\le Start_i<end_i\le N$，$1\le Eff_i\le 10^6$。

## 样例 #1

### 输入

```
12 4 2
1 2 8
10 12 19
3 6 24
7 10 31```

### 输出

```
43```

# 题解

## 作者：kkxhh (赞：35)

定义**状态 d[i] 为以第i个区间为最后一个被选择区间时的最大值** ，于是对于每一个 **d[i]** 我们都可以从所有在它前面的不与它重叠的区间转移过来，也就是直接**在前面找到一个最大值，然后加上这个区间本身的权值**就行了。

排序时按照区间左端还是右端排序其实都没有区别，只需要保证前后两个区间不相交就行了

## 代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef struct interval{int l,r,w;}itv;

itv v[1010];
int n,m,r,d[1010]={0},ans=0;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

bool cmp(itv a,itv b) {return a.l<b.l;}//这个地方写 a.r<b.r 也可以

int main(){
    n=read(); m=read(); r=read();
    for(int i=1;i<=m;i++) v[i].l=read(),v[i].r=read()+r,v[i].w=read();
    //直接在区间右端加上r，方便后面处理
    sort(v+1,v+1+m,cmp);
    for(int i=1;i<=m;i++){
        for(int j=i-1;j>=1;j--)
            if(v[j].r<=v[i].l) //保证两个区间不相交
                d[i]=max(d[i],d[j]);
        d[i]+=v[i].w; ans=max(ans,d[i]);
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：TheGod (赞：31)

dp[i]表示时刻i能得到的最大值

不挤奶：dp[i]=dp[i-1]

挤奶：dp[i]=max(dp[t-r]+p)   （存在从t到i的可以挤奶的时段，能得到p的价值）

容易想到可以用邻接表存储，类似于建i->t的权值为p的边……


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000010;
struct time{
    int st,ed,p,next;}a[N];
int dp[N],head[N];
int main(){
    int n,m,r,i,j,k;
    scanf("%d%d%d",&n,&m,&r);
    for(i=1;i<=m;i++){
        scanf("%d%d%d",&a[i].st,&a[i].ed,&a[i].p);
        a[i].next=head[a[i].ed];
        head[a[i].ed]=i;//前向星}
    memset(dp,0,sizeof(dp));
    for(j=1;j<=n;j++){
        dp[j]=dp[j-1];
        for(i=head[j];i;i=a[i].next)
            dp[j]=max(dp[j],dp[max(0,a[i].st-r)]+a[i].p);//第一次挤奶不需要等待r}
    cout<<dp[n]<<endl;
return 0;}
```

---

## 作者：ibilllee (赞：18)

思路：

如果选择在l-r时间段内挤奶，则对答案产生v的贡献，而且需要往后消耗R的时间

可以这样建模：连一条l->r+R的边，权值为v，用SPFA跑一遍最长路，注意起点是0不是1，终点是n+R而不是n

```cpp
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define RG register int
#define ll long long
#define inf (1<<30)
#define eps (1e-15)
#define maxn 1000005
#define maxm 1005
#define rep(i,a,b) for(RG i=a;i<=b;i++)
#define per(i,a,b) for(RG i=a;i>=b;i--)
using namespace std;
int n,m,p,cnt;
int head[maxn<<1],dis[maxn];
bool vis[maxn],fg[maxn];
struct E{
    int v,next,val;
}e[(maxn<<1)+maxm];

inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}

inline void add(int u,int v,int val)
{
    e[++cnt].v=v,e[cnt].val=val,e[cnt].next=head[u],head[u]=cnt;
}

void SPFA()
{
    RG u,v;
    queue<int> que;
    que.push(0);
    while(!que.empty())
    {
        u=que.front(),que.pop();vis[u]=0;
        for(RG i=head[u];i;i=e[i].next)
        {
            v=e[i].v;
            if(dis[v]<=dis[u]+e[i].val)
            {
                dis[v]=dis[u]+e[i].val;
                if(!vis[v])    que.push(v),vis[v]=1;
            }
        }
    }
    printf("%d",dis[n+p]);
}

int main()
{
    RG hd=1,tl=0;
    n=read(),m=read(),p=read();
    int lim=n+p;
    RG u,v,val;rep(i,1,m)    u=read(),v=read(),val=read(),add(u,v+p,val),fg[u]=1,fg[v+p]=1;
    while(1)
    {
        while(!fg[hd]&&hd<lim)    hd++;
        add(tl,hd,0);
        if(hd>=lim)    break;
        tl=hd,hd++;
    }
    SPFA();
    return 0;
}
```

---

## 作者：Cxs3 (赞：13)

题目链接：https://www.luogu.org/problem/P2889

## 题目分析
观察题目发现，$n$的范围是$1 ≤ n ≤ 1000000$，而$m$的范围是$1 ≤ m ≤ 1000$，比$n$小多了，所以我们可以考虑从$m$入手，将一个可以挤奶的时间段看做一个单位。  
也就是说，用一个结构体数组$a$来记录这$m$个时间段，其中$a[i].l$和$a[i].r$分别记录$i$这个时间段的左端点和右端点，$a[i].e$记录能挤到的牛奶量。

所以很容易想到用$f[i](1≤i≤m)$表示在前$i$个时间段中能挤到的最大的牛奶量，且在时间段$i$里一定会挤奶。  
接下来如何转移呢？  
如果$i$前面的某个$j$的右端点小于等于`a[i].l-R`，即`a[j].r<=a[i].l-R`，那么就可以在$j$挤完之后再挤$i$，所以此时答案为$f[j]+a[i].e$。  
故转移方程为$f[i]=max(f[i],f[j]+a[i].e)$。  
由于都要加上$a[i].e$，所以可以先求出最大的$f[j]$，最后再加上$a[i].e$。

需要注意的是，输入的时间段不一定排过序，要先按时间段的左端点（或右端点）从小到大排序后，才可进行动态转移。  
求出所有的$f[i]$后，枚举$1$到$m$，用$ans$求最大的$f[i]$。因为$f[n]$不一定是最优解，可能不挤$n$会更优。  
或者一边转移一边求$ans$也可，这样就少了一个循环。最后输出就完成了。

## 代码实现
```cpp
#include<bits/stdc++.h>
const int M=1000+10;
using namespace std;

struct node
{
	int l,r,e;
}a[M];
int n,m,r,f[M],ans;

bool cmp(node x,node y){return x.l<y.l;}

int main()
{
	int i,j;
	cin>>n>>m>>r;
	for(i=1;i<=m;i++) cin>>a[i].l>>a[i].r>>a[i].e;
	sort(a+1,a+m+1,cmp);//排序 
	for(i=1;i<=m;i++)
	{
	  for(j=1;j<i;j++)
	  	if(a[j].r<=a[i].l-r) f[i]=max(f[i],f[j]);//如果符合条件就更新f[i]
	  f[i]+=a[i].e;//加上当前可得的牛奶量 
	}
	for(i=1;i<=m;i++) ans=max(ans,f[i]);//求出答案 
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hfyzw (赞：6)

这题明明是普及题嘛~

大佬把我吓得瑟瑟发抖

蒟蒻我来贴个题解

我们让奶牛休息时间加到挤奶时间内

就变成了在n个带权区间内

选取不重叠的一些

得到的最大权值是多少

不就是裸的DP吗？

（而且这个DP好像还可以优化听说是dandiaoduilie）

```pascal
var f,x,y,z:array[0..1000]of longint;
    n,m,k,i,j,ans:longint;
begin
  read(m,n,k);
  for i:=1 to n do begin
    read(x[i],y[i],z[i]);
    y[i]:=y[i]+k;
  end;
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if x[i]>x[j] then begin
        k:=x[i]; x[i]:=x[j]; x[j]:=k;
        k:=y[i]; y[i]:=y[j]; y[j]:=k;
        k:=z[i]; z[i]:=z[j]; z[j]:=k;
      end;
  for i:=1 to n do begin
    for j:=1 to i-1 do
      if (y[j]<=x[i])and(f[j]>f[i]) then f[i]:=f[j];
    f[i]:=f[i]+z[i];
    if f[i]>ans then ans:=f[i];
  end;
  writeln(ans);
end.
```
这么简单的程序就不写注释了（现在P也不多了，写了也是白费）

------------
所以大家来评价一下题目难度吧（刷到入门）（滑稽）

---

## 作者：Priori_Incantatem (赞：5)

这题似乎根本不用排序，好像也不是背包 QwQ

对于 $0\sim m$ 的每一个时间点 $i$（注意**不是时间段**），开一个名为 $bin$ 的vector记录所有以时间点 $i$ 结尾的挤奶的时间段  
设状态 $f[i]$ 表示到第 $i$ 小时时，可以获得的最大产奶量  
显然，在以当前时间点 $i$ 结尾的所有挤奶时间段中，只能选出一个时间段（因为选出的时间段中需要有间隔），由此推出转移方程：  
如果当前时间点刚刚挤完奶 $f[i]=max(f[a[p].l-R]+a[p].value)$ $p \in bin[i]$  
如果不挤奶 $f[i]=f[i-1]$

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int Maxn=1010,Maxm=1000020,inf=0x3f3f3f3f;
struct interval{
	int l,r,v;
}a[Maxn];
int f[Maxm];
vector <int> bin[Maxm];
int n,m,k;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}

int main()
{
	//freopen("in.txt","r",stdin);
	m=read(),n=read(),k=read();  //这里m为时间点的个数，n为挤奶时间段的个数
	for(int i=1;i<=n;++i)
	{
		a[i].l=read(),a[i].r=read(),a[i].v=read();
		bin[a[i].r].push_back(i);
	}
	for(int i=1;i<=m;++i)
	{
		f[i]=f[i-1];
		for(int j=0;j<bin[i].size();++j)
		{
			int p=bin[i][j];
			f[i]=max(f[i],f[a[p].l-k]+a[p].v);
		}
	}
	printf("%d\n",f[m]);
	return 0;
}
```

---

## 作者：Michael_Li (赞：5)

觉得这题并不是很难，但是一看题解，都好奇怪啊。。。

还有用树状数组的。。

我的思路和最顶楼的题解有点类似，不过不需要spfa，把每个时间段按左端点排序，然后dp就行了。

转移的时候只要前面选的时间段的右端点和我的左端点差小于等于R就行了

可能大佬都不屑于做这么简单的题吧。。。
```
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<iostream>
#define LL long long
#define N (1001)
using namespace std;
int n,m,r;
LL f[N],maxans;
template <typename T> void read(T&t) {
	t=0;
	bool fl=true;
	char p=getchar();
	while (!isdigit(p)) {
		if (p=='-') fl=false;
		p=getchar();
	}
	do {
		(t*=10)+=p-48;p=getchar();
	}while (isdigit(p));
	if (!fl) t=-t;
}
struct edge{
	int l,r;
	LL data;
}a[N];
inline bool cmp(edge a,edge b){
	return a.l==b.l?a.r<b.r:a.l<b.l;
}
int main(){
	freopen("testdata.in","r",stdin); 
	read(n),read(m),read(r);
	for (int i=1;i<=m;i++){
		read(a[i].l),read(a[i].r),read(a[i].data);
	}
	sort(a+1,a+m+1,cmp);
	a[0].r=-1000000;
	for (int i=1;i<=m;i++){
		for (int j=0;j<i;j++){
			if (a[i].l-a[j].r>=r) f[i]=max(f[i],f[j]);
		}
		f[i]+=a[i].data;
		maxans=max(f[i],maxans);
	}
	printf("%lld",maxans);
	return 0;
}
```

---

## 作者：zwjdd (赞：3)

既然都有大佬用spfa跑最长链了，那么怎么少得了拓扑排序呢

~~主要感觉和P1137旅行计划没啥区别~~

对于任务A，如果它的结束时间（包括休息）end+R >= 任务B的 begin

那么说明可以形成继承关系，连一条从A到B的有向边，顺便计算B入度++

记dp[i]表示以i为终点的最长链，以上面的AB举例
dp[B]=max(dp[B],dp[A]+w[B]);  取max因为B的前驱点可能不止一个

坑点大概就是连边条件>=不是>吧，，似乎>只有80.....，因为结束时间不挤奶，所以有效时间只是 [ l , r-1 ] ，可得最终休息结束时间在r+R-1；

其他没啥细节，看代码吧
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 1024;// m范围 
typedef long long ll;

struct RNG
{
    int be,en,w;
}task[maxn];

struct EDG// 我喜欢结构体 
{
    int to,next;
}edge[maxn*maxn];
 
int n,m,r;// 基础变量 
int dp[maxn],rd[maxn],ans=-1;// 拓扑+dp变量 
int cnt,head[maxn];// 前向星变量 

bool cmp(RNG a,RNG b)// 排序方便连边 
{
    return a.be<b.be;
}

void add(ll from,ll to)// 加边 
{
    edge[++cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt;
}

void toopsort()// 朴实无华的拓扑排序 
{
    queue<int>q;
    for(int i=1;i<=m;i++)
        if(!rd[i])// 将每一个可以作为起点的点扔进队列，并初始化dp值 
        {
            q.push(i);
            dp[i]=task[i].w;
        }
    while(!q.empty())
    {
        int f1=q.front();
        q.pop();
        for(int i=head[f1];i!=-1;i=edge[i].next)
        {
            int to=edge[i].to;
            dp[to]=max(dp[to],dp[f1]+task[to].w);// dp 
            ans=max(ans,dp[to]); 
            if(--rd[to]==0)	q.push(to);
        }
    }
}
 
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        task[i].be=x; task[i].en=y+r; task[i].w=z;
    }
    
    sort(task+1,task+1+m,cmp);// 排序方便连边 
    
    for(int i=1;i<=m;i++)// 连边 
        for(int j=i+1;j<=m;j++)
            if(task[j].be>=task[i].en)
            {
                add(i,j);
                rd[j]++;
            }
    
    toopsort();// 拓扑排序 
    printf("%d",ans);// 输出，结束 
    return 0;
}
```


---

## 作者：qwaszx (赞：3)

这题其实就是个线段覆盖嘛.....

对于R那一段，直接加到右端点上，显然对答案没有影响

然后就是给定n段区间，选取不相交的若干个区间使权值和最大

然后写dp方程$f[i]=max\{f[j]\ |\ r[j]\leq l[i]\}+w[i]$

按右端点排序，然后应该非常容易写

考虑对$f$做一个前缀$max$，然后贪心地选取最靠右的满足条件的区间

贪心正确性的证法...归纳吧~~oi不需要证明~~

然后因为右端点单调不降，可以二分找

然后就在$mlogm$的时间内切掉了

所以这其实是个pj题....$m^2$都能过

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct lr{int l,r,w;}a[500000];
int f[500000],g[500000],n,m,R;
int cmp(const lr &a,const lr &b)
{
	return a.r<b.r;
}
int main()
{
	scanf("%d%d%d",&n,&m,&R);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w),a[i].r+=R;
	sort(a+1,a+m+1,cmp);
	a[0].r=-1;
	for(int i=1;i<=m;i++)
	{
		int l=0,r=i-1,mid;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(a[mid].r<=a[i].l)l=mid;
			else r=mid-1;
		}
		if(a[r].r<=a[i].l)f[i]=g[r]+a[i].w;
		else f[i]=a[i].w;
		g[i]=max(g[i-1],f[i]);
	}
	cout<<g[m]<<endl;
}
```

---

## 作者：租酥雨 (赞：2)

为什么我的想法总是那么奇怪...

设**dp[i]表示前i时间内挤奶，且i时间刚好完成了一次挤奶**的最大受益

我们易知对于一次挤奶(区间[l,r],收益为w)，显然是可以转移到dp[r]的，但问题是从哪里转移过来呢?

应该是**dp[0]~dp[max(0,l-R)]**中的最大值吧 (因为不能保证dp[max(0,l-R)]时刚好完成了一次挤奶，也不能保证从dp[max(0,l-R)]转移一定是最优解)

先按所有区间的右端点排序，显然是为了确定转移顺序，右端点越靠右的越后转移。

观察上面那个式子就是一个前缀最大值，我们用**！树状数组！**维护，然后依次转移。

最后的答案不是dp[n],而是**dp[0]~dp[n]的前缀最大值**。

然后这道题就做完了，复杂度**O(mlogm+mlogn)**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int _ = 1000005;
struct interval
{
    int l,r,w;
    bool operator < (const interval &zsy) const {return r<zsy.r;}
}a[_];
int n,m,R,c[_];
int gi()
{
    int x=0,w=1;char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') w=-1,ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*w;
}
void Modify(int pos,int val){for(int k=pos;k<=n;k+=k&-k)c[k]=max(c[k],val);}//树状数组修改操作
int Query(int pos){int res=0;for(int k=pos;k;k-=k&-k)res=max(res,c[k]);return res;}//树状数组查询操作
int main()
{
    n=gi();m=gi();R=gi();
    for (int i=1;i<=m;i++)
        a[i]=(interval){gi(),gi(),gi()};
    sort(a+1,a+m+1);
    for (int i=1;i<=m;i++)
        Modify(a[i].r,Query(max(0,a[i].l-R))+a[i].w);//查询前缀最大值转移并修改当前的dp值
    printf("%d\n",Query(n));
    return 0;
}

```

---

## 作者：DennyQi (赞：0)

### 提供一个不需要排序的做法

将休息时间合并到挤奶时间里去，然后对于每一个结束时刻记录其对应的开始时刻。注意一个结束时刻有可能对应多个开始时刻，因此用一个$vector$来维护。然后从头开始扫描，转移即可

注意答案是$dp[n+R]$，而不是$dp[n]$。还需要注意休息时间的最后一秒是可以开始挤牛奶的！也就是说，要从$dp[pre]$转移而来，而不是$dp[pre-1]$

```cpp
/*By DennyQi 2018*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1010;
const int MAXM = 1000010;
const int INF = 1061109567;
inline int Max(const int a, const int b){ return (a > b) ? a : b; }
inline int Min(const int a, const int b){ return (a < b) ? a : b; }
inline int read(){
    int x = 0; int w = 1; register char c = getchar();
    for(; c ^ '-' && (c < '0' || c > '9'); c = getchar());
    if(c == '-') w = -1, c = getchar();
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x<<3) + (x<<1) + c - '0'; return x * w;
}
struct Cow{
	int t,c;
};
int N,M,R,mx;
int s[MAXN],e[MAXN],w[MAXN];
vector <Cow> pre[MAXM];
int dp[MAXM];
int main(){
//	freopen(".in","r",stdin);
	N = read(), M = read(), R = read();
	for(int i = 1; i <= M; ++i){
		s[i] = read(), e[i] = read()+R, w[i] = read();
		pre[e[i]].push_back((Cow){s[i], w[i]});
	}
	dp[0] = 0;
	for(int i = 1; i <= N+R; ++i){
		dp[i] = dp[i-1];
		for(int sz = pre[i].size(), j = 0; j < sz; ++j){
			dp[i] = Max(dp[i], dp[pre[i][j].t] + pre[i][j].c);
		}
	}
	printf("%d", dp[N+R]);
	return 0;
}
```

---

## 作者：redegg (赞：0)

感觉被一道水题侮辱了智商。~~无法解释为何没有一次性AC~~

感觉根本不用写什么单调队列来存储，直接暴力地存到一个maxn里面，保证后面的区间从maxn转移是合法的就行了，于是sort两下子，跑个m，顺便把last（就是上一个可以合法转移的区间）往后移动，maxn更新一下就好了。

复杂度，，，就是sort的吧，好像sort要大一点点。

~~所以这是一道排序题（雾）。~~

代码如下，dp为主：
```
#include <bits/stdc++.h>
using namespace std;

int n,m,x;

struct ha
{
    int l,r;
    long long e;
}a[1000006];

ha b[1000006];

long long dp[1000005];

int last=1;
long long maxn;
long long ans=0;

bool cmp1(const ha &aa,const ha &bb)
{
    if(aa.l==bb.l)return aa.r<bb.r;
    return aa.l<bb.l;
}

bool cmp2(const ha &aa,const ha &bb)
{
    if(aa.r==bb.r)return aa.l<bb.l;
    return aa.r<bb.r;
}

int main()
{
    scanf("%d%d%d",&n,&m,&x);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&a[i].l,&a[i].r,&a[i].e);
        b[i].l=a[i].l;
        b[i].r=a[i].r;
        b[i].e=a[i].e;
    }

    sort(a+1,a+1+m,cmp1);
    sort(b+1,b+1+m,cmp2);
    for(int i=1;i<=m;i++)
    {
        while(1)
        {
            if(b[last].r>a[i].l-x)break;
            maxn=max(dp[b[last].r],maxn);
            last++;
        }
        dp[a[i].r]=max(maxn+a[i].e,dp[a[i].r]);
        ans=max(dp[a[i].r],ans);
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：lianliangyu (赞：0)

#### 第一道不看题解通过的蓝题DP

这道题题意大致就是，选取若干个区间，每个区间都有一个值，且两个区间之间隔不小于R，求能选取的区间中数值总和的最大值。

所以可以选用建图跑最短路或背包的思想。我选用的是背包。

建一个数组$f$,$f[i]$表示在时间$i$内能选取的区间的值总和的最大值，那么状态转移方程就是：

$f[j]=max(f[j],f[a[i].l-r]+a[i].e),$ $j∈[1,n],i∈[1,m]$

$a[i].l$表示区间的左端点，$r$表示区间间隔。选取到该区间后，接下来只能再往前搜，往前距$j$最近的就是$a[i].l-r$。

另外值得注意的是，$j$要从后往前搜，由于这题类似$01$背包的思想（我的思路就是这么来的），所以与$01$背包的代码类似，要从后往前搜。同时对于区间还要以右端点为关键字从小到大排序。
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int l,r,e;
	inline bool operator<(const node &k)const
	{return r==k.r?l<k.l:r<k.r;}
}a[1005];
int n,m,r,f[1000005];
template<class type>inline void read(type &k)
{
	k=0;type t=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {k=k*10+ch-'0';ch=getchar();}
	k*=t;
}
inline int max(int x,int y) {return x>y?x:y;}
int main()
{
	int i,j;
	read(n);read(m);read(r);
	for(i=1;i<=m;i++)
	read(a[i].l),read(a[i].r),read(a[i].e);
	sort(a+1,a+m+1);
//	for(i=1;i<=m;i++)
//	cout<<a[i].l<<" "<<a[i].r<<endl;
	for(i=1;i<=m;i++)
	for(j=n;j;j--)
	if(a[i].r<=j)
	f[j]=max(f[j],f[a[i].l-r]+a[i].e);
	printf("%d\n",f[n]);
	return 0;
}
```
本来这道题是个二重循环，理论上很难过掉，但实际上只卡了一个点，$WA$了一个点，开个$O2$就很神奇的把两个点 [卡掉了](https://www.luogu.org/record/26368313)。

---

## 作者：circlegg (赞：0)

看完题想的是如果当前时间可以挤奶就从开始挤奶时间转移到挤奶结束时间，不能挤奶就直接转移给后面一个时间点

然后发现如果有休息 r 时间这个限制还是挺麻烦的，但是发现从挤奶开始一直到休息完是一个整体，都不能进行转移

所以直接将挤奶时间变成 time+r 进行转移就可以了

转移方程 f[i+time[i]+r]=max(f[i+time[i]+r],f[i]+w[i])

time[i] 为这次挤奶的持续时间, w[i] 是这次挤奶的收益, r 在读入时计入 time 数组中即可

复杂度 O(n)

上代码：

···
```cpp
//?2017 circlegg
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int read(){
    int x=0,mns=1; char c=getchar();
    while(c!='-'&&(c<'0'&&c>'9')) c=getchar();
    if(c=='-') mns=-1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*mns;
}
int n,m,r,f[2000005],y;
bool vis[2000005];
struct data{
    int st,tim,w;
}a[1005];
bool cmp(data a,data b){
    return a.st<b.st;
}
int main(){
    n=read();
    m=read();
    r=read();
    n=n+r+5;//+5容错 
    for(int i=1;i<=m;i++){
        a[i].st=read();
        vis[a[i].st]=1;
        y=read();
        a[i].w=read();
        a[i].tim=y-a[i].st+r;
    }
    sort(a+1,a+1+m,cmp);
    int j=1;
    for(int i=0;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
        if(vis[i]){
            for(;a[j].st==i;j++){
                f[i+a[j].tim]=max(f[i+a[j].tim],f[i]+a[j].w);
            }
        }
    }
    printf("%d\n",f[n]);
    return 0;
} 
···
```

---

## 作者：梦想国度 (赞：0)

  
      
                  
```cpp
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
const int MAXN=1000000+10;  
int dp[MAXN]; //dp[i]表示从头开始取到第i段能获得的最大值   
struct data  
{  
    int st,et,val;    
    bool operator <(const data &x)const{  
        return st<x.st;  
    }  
}a[1024];  
int main()  
{  
    int n,m,r;  
    while(~scanf("%d%d%d",&n,&m,&r))  
    {  
        for(int i=0;i<m;i++)  
            scanf("%d%d%d",&a[i].st,&a[i].et,&a[i].val);  
        sort(a,a+m);  
        int ans=0;        
        for(int i=0;i<m;i++)  
        {  
            dp[i]=a[i].val;  
            for(int j=0;j<i;j++)           
                if(a[i].st>=a[j].et+r)                 
                    dp[i]=max(dp[i],dp[j]+a[i].val);  
            ans=max(ans,dp[i]);  
        }  
        printf("%d\n",ans);  
    }  
    return 0;  
}
```

---

