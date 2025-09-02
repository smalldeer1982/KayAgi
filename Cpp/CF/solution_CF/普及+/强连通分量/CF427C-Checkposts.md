# Checkposts

## 题目描述

你的城市有 $n$ 个路口。路口之间有一条单程道路。作为城市的市长，你必须确保所有路口的安全。

为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。 如果有一个检查站在 $i$ 路口，保护 $j$ 的条件是：$i==j$ 或者警察巡逻车可以从 $i$ 走到 $j$，并且能回到 $i$。

建造检查站要花一些钱。 由于城市的某些地区比其他地区更昂贵，在某些路口修建检查站可能比其他路口花费更多的钱。

你需要找到使所有路口安全的最低花费，以及花费与最低价格相等的方案数。

如果其中任何一个路口包含其中一个检查点而不包含在另一个路口中，则两种方式是不同的。

方案数模 $10^9+7$。

## 说明/提示

$1 \leq n \leq 10^5,0 \leq m \leq 3 \times 10^5,0 \leq a_{i} \leq 10^9$。

$1<=u_{i},v_{i}<=n,u≠v$。

**最小花费不需要取模，方案数需要取模。**

## 样例 #1

### 输入

```
3
1 2 3
3
1 2
2 3
3 2
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
5
2 8 0 6 0
6
1 4
1 3
2 4
3 4
4 5
5 1
```

### 输出

```
8 2
```

## 样例 #3

### 输入

```
10
1 3 2 2 1 3 1 4 10 10
12
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9
```

### 输出

```
15 6
```

## 样例 #4

### 输入

```
2
7 91
2
1 2
2 1
```

### 输出

```
7 1
```

# 题解

## 作者：KEBrantily (赞：8)

UPD：没写句号打回来了，下次不敢了/kk

## Description
给定一张有向图，有点权无边权，需要在其中的某些点建立保护站。

一个建立在 $i$ 号点的保护站能保护到所有与 $i$ 处于同一个 SCC 中的点，而在一个 SCC 中建立一个保护站的费用可以是其中任意一个点的点权。

求使得所有点都能被保护的最小费用与其方案数。

## Solution
经过如上总结之后，方向已经确定。

先求出强连通分量并缩点，并求出每个强连通分量中最小的点权作为缩点后的点权，然后新的点权之和就是最小费用。

再求出每个强连通分量中点权与最小点权相同的点数，作为缩完后这个点的大小，根据乘法原理，最小花费的方案数就是缩完点后所有点的大小的乘积。

## Code
```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 301000
#define INF 0x3f3f3f3f
#define Mod 1000000007

using namespace std;

bool vis[maxn];
int n,m,tot,top,cnt,t,ans1,ans2=1;
int dfn[maxn],low[maxn],num[maxn],sum[maxn];
int siz[maxn],zhan[maxn],head[maxn],val[maxn];
struct edge{int to,nxt;}e[maxn];

int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*w;
}

void add(int fr,int to){
    e[++tot].to=to;
    e[tot].nxt=head[fr];head[fr]=tot;
}

void tarjan(int x){
    low[x]=dfn[x]=++cnt;
    zhan[++top]=x;vis[x]=1;
    for(int i=head[x];i;i=e[i].nxt){
        int to=e[i].to;
        if(!dfn[to]) tarjan(to),low[x]=min(low[x],low[to]);
        else if(vis[to]) low[x]=min(low[x],dfn[to]);
    }
    if(dfn[x]==low[x]){
        ++t;
        int pre=zhan[top--];
        sum[t]=val[pre];
        vis[pre]=0;num[pre]=t;
        while(pre!=x){
            pre=zhan[top--];
            vis[pre]=0;num[pre]=t;
            sum[t]=min(sum[t],val[pre]);
        }
    }
}

signed main(){
    n=read();
    for(int i=1;i<=n;i++) val[i]=read();
    m=read();
    for(int i=1;i<=m;i++) add(read(),read());
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        if(val[i]==sum[num[i]]) siz[num[i]]++;
    for(int i=1;i<=t;i++) ans1+=sum[i],ans2=(ans2*siz[i])%Mod;
    printf("%d %d\n",ans1,ans2%Mod);
    return 0;
}
```


---

## 作者：Kalium (赞：2)

## 前言：

好久没上 lg 了，这篇题解当做复出吧（因为 whk 不得不退谷1个月）。

## 题意：

求将一张图所检查的最小费用，如果一个点能够从这开始，最后回到这，那么检查的费用为这个点的点权，求最小费用和在此最小费用下的方案数。

## 思路：

求最小花费（easy）：

很明显，看到环就习惯性将原图缩成 DAG。

那么点权要做到最小，因为在环里面，不论从哪个点开始都能回到这个点，所以点权只需要做到这个环里面的最小点权即可。

到这里都是正常的板子题，关键是如何算方案数（difficult）：

对于方案数，我们想想，是不是如果环里面有相同的点权出现，是不是从这两个点开始检查都是一样的花费？

那么对于每个环如此判断一遍，最后用乘法原理搞一下不就可以了。

当然，如果点权更新，相同的个数也得清零，因为得是在最小花费下嘛。

## 细节：

注意要开 long long。

注意在求方案的时候要取模。

## 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define inf 0x3f3f3f3f
#define ll long long

const int N = 1e5 + 7;
const int M = 3e5 + 7;
const int mod = 1e9 + 7;

using namespace std;

int dfn[N], low[N];

int n, m;

ll v[N], newv[N];
 
ll num[N];

int ti, sc;

int stk[N], instk; 

bool flag[N];

struct Edge {
	int to, next;
} edge[M];

int head[N], cnt;

inline void addedge(int u, int v) {
	edge[++ cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++ ti;
	stk[++ instk] = u;
	flag[u] = 1;
	
	for (int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		
		if (! dfn[v]) {
			tarjan(v);
			low[u] = mina(low[u], low[v]);
		} else if (flag[v])
			low[u] = mina(dfn[v], low[u]);
	}
	
	int cur;
	
	if (dfn[u] == low[u]) {
		sc ++;
		newv[sc] = inf; 
		
		do {
			cur = stk[instk --];
			flag[cur] = 0;
			
			if (v[cur] < newv[sc]) {
				newv[sc] = v[cur];
				num[sc] = 0;
			}
			
			if (newv[sc] == v[cur]) num[sc] ++;
		} while (cur != u);
	}
}

int main() {
	memset(head, -1, sizeof(head));
	
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i ++)
		scanf("%d ", &v[i]);
	
	scanf("%d", &m);
	
	for (int i = 1, u, v; i <= m; i ++) {
		scanf("%d %d", &u, &v);
		
		addedge(u, v); 
	}
	
	for (int i = 1; i <= n; i ++) {
		if (! dfn[i])
			tarjan(i);
	}
	
	ll ans1 = 0;
	ll ans2 = 1;
	
	for (int i = 1; i <= sc; i ++) {
		ans1 += newv[i];
		ans2 *= num[i], ans2 %= mod;
	}
	
	printf("%lld %lld\n", ans1, ans2);
	
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：2)

题目大意：

给一个有向图，每个点一个权值，

对每个强连通分量选一个点，

求最小权值和和在权值和最小的情况下可选择的方案数

题目分析：

上面的题目大意其实已经将原题意转换成图论问题，

强连通分量直接tarjan搞，

对每个取权值最小的然后判断有没有权值一样的，

然后乘法计数原理

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack> 
#define MAX 0x3f3f3f3f
#define MIN -0x3f3f3f3f
const int moder = 1e9 +7 ; 
using namespace std ;
const int N= 1e5 + 10  ;
long long cost[N] ;
int dfn[N],low[N] ;
int belong[N] ;
vector <int> G[N] ;
stack <int> S ; 
bool vis[N] ;
int dfn_max ;
vector <int> link[N] ;
int sum ; 
int n, m ; 
void tarjan(int now) //tarjan模板
{
	dfn[now]=low[now]=++dfn_max ;
	vis[now]=true,S.push(now) ;
	for (int i=0;i<G[now].size();i++)
	{
		int to=G[now][i] ;
		if (!dfn[to])
		{
			tarjan(to) ;
			low[now]=min(low[now],low[to]) ;
		} 
		if (dfn[to] && vis[to]) low[now]=min(low[now],low[to]) ;
	} 
	if (dfn[now]==low[now])
	{ 
		belong[now]=++sum ; 
		vis[now]=false ;
		while (S.top()!=now)
		{
			belong[S.top()]=sum ; 
			vis[S.top()]=false ;
			S.pop() ;
		}
		S.pop();
	}
}
int main()
{
	scanf("%d",&n) ;
	for (int i=1;i<=n;i++) scanf("%d",&cost[i]) ;
	scanf("%d",&m) ;
	for (int i=1;i<=m;i++)
	{
		int u,v ;
		scanf("%d%d",&u,&v) ;
		G[u].push_back(v) ;
	}
	memset(dfn,0,sizeof(dfn)) ;
	memset(low,0,sizeof(low)) ;
	memset(vis,false,sizeof(vis)) ;
	for (int i=1;i<=n;i++)
	if (!dfn[i]) tarjan(i) ;  
	for (int i=1;i<=n;i++)
	link[belong[i]].push_back(i) ; //建图
	long long ans=0,rlt=1 ;
	for (int i=1;i<=sum;i++)
	{
		long long  min=MAX,t=1 ; 
		for (int j=0;j<link[i].size();j++)
		{
			int x=link[i][j] ;
			if (cost[x]<min)
			{
				t=1;
				min=cost[x] ;
			}
			else if (cost[x]==min)
			{
				t++ ;
			}
		}
		ans+=min;rlt=(rlt*t)%moder ;
	}
	printf("%lld %lld",ans,rlt) ;
}

```

---

## 作者：Farkas_W (赞：2)

$$\text{关于题意}$$

$\quad$因为点i能保护j的条件是i可以到达j且j可以返回i，这不就是强连通分量的定义吗？所以考虑缩点，将每个强连通分量缩成一个点，缩点后每个强连通分量中只需取一个点，所以记录每个强连通分量中最小点权及其数量，最后最低成本就是每个强连通分量最小点权之和，方案数是最小点权数量之积。

$\quad$别忘了开long long，最后方案数要对1e9+7取模。

$\quad$如果还有什么不懂的地方就看看代码吧

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
#include<vector>
#define re register int
#define int long long
#define il inline
#define next ne
using namespace std;
il int read()				//快速读入
{
	int x=0,minus=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')minus=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*minus;
}
const int N=1e5+5,MOD=1e9+7;
int n,m,a[N],next[N*3],go[N*3],head[N];
int low[N],dfn[N],c[N],s[N],p[N],l[N],tot,cnt,ans,ans1=1;
il void Add(int x,int y)		//链式前向星存图
{
	next[++tot]=head[x];
	head[x]=tot;
	go[tot]=y;
}
stack<int>q;
il void Tarjan(int x)		 	//Tarjan缩点
{
	dfn[x]=low[x]=++cnt;
	q.push(x);
	for(re i=head[x];i;i=next[i])
	{
		int y=go[i];
		if(!dfn[y])Tarjan(y),low[x]=min(low[x],low[y]);
		else if(!c[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])
	{
		c[x]=++c[0];
		s[c[0]]=a[x];p[c[0]]=1;  			//记录每个强连通分量中点权最小的，数量初始化为1
		while(q.top()!=x)
		{
			c[q.top()]=c[0];
			if(s[c[0]]==a[q.top()])p[c[0]]++;		  	 //如果有一样小的点权，数量+1
			else if(s[c[0]]>a[q.top()])s[c[0]]=a[q.top()],p[c[0]]=1; //如果有更小的点权就更新，数量变为1
			q.pop();
		}
		q.pop();
	}
}
signed main()
{
	n=read();
	for(re i=1;i<=n;i++)a[i]=read();
	m=read();
	for(re i=1;i<=m;i++)
	{
		int x=read(),y=read();
		Add(x,y);
	}
	for(re i=1;i<=n;i++)
	if(!dfn[i])Tarjan(i);
	for(re i=1;i<=c[0];i++)
	{
		ans+=s[i];		//最小点权之和
		ans1*=p[i]%MOD;		//数量之积
	}
	printf("%lld %lld",ans,ans1%MOD);
	return 0;
}
```
$$\text{后话}$$

此题有双倍经验哦，[P2194 HXY烧情侣](https://www.luogu.com.cn/problem/P2194)

临近CSP复赛，祝大家RP++。

写题解不易，帮忙点个赞吧。

---

## 作者：SUNCHAOYI (赞：1)

由题可以知道，每一条边都是有向边。一个检查站只能保护一个环上的路口，即检查站的个数也是环的个数。

题目的第一问求最小花费，也就是就每个环上建一个检查站的最小花费之和。因此用 `tarjan` 求出每一个强联通分量以及该分量内的最小花费，最后求一个和。

```cpp
void tarjan (int u)//模板即可
{
	low[u] = dfn[u] = ++times;
	s.push (u);
	for (int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if (!dfn[v])
		{
			tarjan (v);
			low[u] = min (low[u],low[v]);
		}
		else if (!scc[v])
			low[u] = min (low[u],dfn[v]);
	}
	if (low[u] == dfn[u])
	{
		++scc_cnt; 
		while (true)
		{
			int x = s.top ();
			s.pop ();
			scc[x] = scc_cnt;
			mn[scc_cnt] = min (mn[scc_cnt],cost[x]);//求最小值
			if (x == u) break;
		}
	} 
}
```

最后相加时注意最小花费是**不用取模**的，所以答案为 $\sum^{n}_{i = 1} mn[i]$。

再来看第二问，求方案数。由于肯定要做到每一个强连通分量中选的检查站花费一定最优，所以只要求每一个分量中花费为 $mn[i]$ 的个数，然后根据乘法原理将它乘起来即可。注意这是**需要取模**的，答案为 $\prod^{n}_{i = 1} num[i]$。

```cpp
for (int i = 1;i <= n;++i)
	if (cost[i] == mn[scc[i]]) ++num[scc[i]];//计数
for (int i = 1;i <= scc_cnt;++i) 
	ans_cnt = (ll)ans_cnt * num[i] % MOD;//乘法原理
```

---

## 作者：VenusM1nT (赞：1)

这波啊，这波是绿题上紫。  
观察到是单向图，直接大力缩点，每个点的贡献就是点内权值最小的那个，加起来就得到了第一问的答案。记录一下每个点里有多少个贡献最小的，乘法原理乘起来一搞就出来了。
```cpp
#include<bits/stdc++.h>
#define N 100000
#define reg register
#define inl inline
using namespace std;
const int Mod=1e9+7;
int n,m,a[N+5],dfn[N+5],low[N+5],idx,bel[N+5],tot,siz[N+5],minx[N+5];
bool ins[N+5];
vector <int> g[N+5];
stack <int> s;
void Tarjan(reg int u)
{
	dfn[u]=low[u]=++idx;
	s.push(u);
	ins[u]=1;
	for(auto v : g[u])
	{
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		reg int v=0;
		tot++;
		while(u!=v)
		{
			v=s.top();
			s.pop();
			bel[v]=tot;
			ins[v]=0;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(reg int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(reg int i=1;i<=m;i++)
	{
		reg int x,y;
		scanf("%d %d",&x,&y);
		g[x].push_back(y);
	}
	for(reg int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	memset(minx,60,sizeof(minx));
	for(reg int i=1;i<=n;i++) minx[bel[i]]=min(minx[bel[i]],a[i]);
	reg long long ans=0,Ans=1;
	for(reg int i=1;i<=n;i++) if(minx[bel[i]]==a[i]) siz[bel[i]]++;
	for(reg int i=1;i<=tot;i++) ans=ans+minx[i],Ans=Ans*1ll*siz[i]%Mod;
	printf("%lld\n%lld\n",ans,Ans);
	return 0;
}

```

---

## 作者：LevenKoko (赞：1)

### ~~省选前颓几道水题？~~

[双倍经验？](https://www.luogu.org/problemnew/show/P2194)

言归正传：
	显然这是一道TARJAN，~~题面已经想方设法在提醒你了~~
    
    
   只要记录每个强联通分量中的最小元素值和最小元素值对应的数量即可
   
   看到很多题解都是全部处理完之后在最后统计最小元素值和最小元素对应数量并统计两个答案的，其实对于减小常数来说这样是没必要的,因为每个强连通分量只会在tarjan的途中被搜索到一次（可以叫做无后效性？）所以只要一边tarjan一边统计答案即可
   
   注意开long long 
   
   注意开long long 
   
   注意开long long 
   
   
```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#define writep(x) write(x),putchar(' ')
#define writeln(x) write(x),puts("") 
#define ha 1000000007//珍惜生命，暴力取膜不可取，所以，我们取ha
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M=3e5+5;
int n,m,a[M],head[M],ver[M],nxt[M],tot,dfn[M],low[M],ins[M],sta[M],top,t,mn[M],col,color[M],cnt[M],mc[M],ans1,ans2=1;
/*
col 强连通分量数量
color[]强连通分量的编号
cnt[]强连通分量重元素个数（这里貌似没用）
mn[]强连通分量中值最小值
mc[]强连通分量中最小值个数
*/
inline void add(int x,int y){ver[++tot]=y;nxt[tot]=head[x];head[x]=tot;}
inline void cmin(int &a,int b){if(a>b) a=b;}
void Tarjan(int x){
    dfn[x]=low[x]=++t;ins[x]=1,sta[top++]=x;
    for(register int i=head[x];i;i=nxt[i])
        if(ins[ver[i]]==0) Tarjan(ver[i]),cmin(low[x],low[ver[i]]);
        else if(ins[ver[i]]==1) cmin(low[x],dfn[ver[i]]);
    if(dfn[x]==low[x]) ++col,mn[col]=0x7fffffff;
    if(dfn[x]==low[x]){
        do{
            --top,++cnt[col],color[sta[top]]=col;ins[sta[top]]=-1;
            if(mn[col]>a[sta[top]])	 mn[col]=a[sta[top]],mc[col]=0;
            if(mn[col]==a[sta[top]]) ++mc[col];//关键部分
        }while(sta[top]!=x);
        ans1+=mn[col];ans2=ans2*mc[col]%ha;//记录答案
	}
    
}
int main(){
    n=read();for(register int i=1;i<=n;++i) a[i]=read();
    m=read();for(register int i=1,x,y;i<=m;++i){x=read(),y=read(),add(x,y);}
    for(register int i=1;i<=n;++i) if(!dfn[i]) Tarjan(i);//基本操作
    writep(ans1),writeln(ans2);//输出
    return 0;
}

```

---

## 作者：yangwenbin (赞：1)

# 题解 CF427C 【Checkposts】

我是从[P2194](https://www.luogu.com.cn/problem/P2194)的双倍经验里点进来的

说实话没啥区别 ~~（其实根本没区别）~~

言回正传 ： 没认真看过题目的同学请走这里（[传送门](https://www.luogu.com.cn/problem/CF427C)）

看到是一道紫题说实话慌得一批，以为有什么变化

其实啥区别也没有，基本一样。

但是我们还是以第三题为例，分析一下

```
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9
```

权值暂时不作考虑，可构出如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/csk0qdg6.png)

图形上十个点


都可以相互到达

所以他们是强连通分量

进行缩点

设

```
{9 , 10} = a
{8} = b
{1 ，2 ，3 ，4 ，5 ，6 ，7} = c
```

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/mwhxc2xc.png)

三个分量，按照题目描述

```
为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。
如果有一个检查站在i路口，保护j的条件是：
i==j或者警察巡逻车可以从i走到j，并且能回到i。
```

理解这句话，即一个强连通分量只需要设一个警察检查站；

所以在 a , b , c 中各取一个点建警察检查站

为了使花费最少所以贪个心，去每个强连通分量中权值最少的点，并记录一个分量有几个这样的点

最小花费就是每个强连通分量的最小花费之和，数量就是个数的乘积（简单，易理解就不细讲了）

## trajan

重点讲一下缩点的处理

这里有的是tarjan算法

tarjan算法是常见的强连通分量算法之一，也是比较快的，时间复杂度只有O（N+E）

在处理中我比较喜欢递归实践

在过程中要用到栈（stc）。

存图可以用链式前向星或vector数组存图

我使用的是vector数组

dfn数组记录第几个被搜到，low记录它所在的强连通分量的点最早别搜到的第几个被搜到

instack记录该点是否在栈中

belong数组记录第i个强连通分量内的元素

edge数组存储路径

```
	dfn[u] = low[u] = ++tot;
	stc.push(u);
	instack[u] = true;
	ll s = edge[u].size();
	for (ll i = 0; i < s; ++i){
		ll v = edge[u][i];
		if (!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}else if(instack[v]){
			low[u] = min(low[u],low[v]);
		}
	}
	if (dfn[u] == low[u]){
		ll node;
		++cnt;
		do{
			node = stc.top();
			stc.pop();
			belong[cnt].push_back(node);
			instack[node] = false;
		} while (node != u);
	}
```
还有跑每一个点，循环每一个点没搜过就搜一遍

```
for (ll i = 1; i <= n; ++i){
	if (!dfn[i]){
		tarjan(i);
	}
}
```
## 贪心查找

然后遍历belong数组，寻找最小点，及其个数

```
for (ll i = 1; i <= cnt; ++i){
	ll s = belong[i].size();
	ll tmp = 1000000007;
	ll t;
	for (ll j = 0; j < s; ++j){
		if (input[belong[i][j]] < tmp){
			tmp = input[belong[i][j]];
			t = 1;
		}else if(input[belong[i][j]] == tmp){
			t++;
		}
	}
	ans = ans + tmp;
	times = (times * t) % mod;
}
```

## 记得开long long

不开long long 的我在P2194卡了一个下午

# code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1000000007;
ll n,m,ans,tot,cnt;
ll input[100050],dfn[100050],low[100050];
bool instack[100050];
std::vector< ll > edge[100050];
std::vector< ll > belong[100050];
std::stack < ll > stc;
void tarjan(ll u){
	dfn[u] = low[u] = ++tot;
	stc.push(u);
	instack[u] = true;
	ll s = edge[u].size();
	for (ll i = 0; i < s; ++i){
		ll v = edge[u][i];
		if (!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}else if(instack[v]){
			low[u] = min(low[u],low[v]);
		}
	}
	if (dfn[u] == low[u]){
		ll node;
		++cnt;
		do{
			node = stc.top();
			stc.pop();
			belong[cnt].push_back(node);
			instack[node] = false;
		} while (node != u);
	}
}
int main(){
	scanf("%lld",&n);
	for (ll i = 1; i <= n; ++i){
		scanf("%lld",&input[i]);
	}
	scanf("%lld",&m);
	for (ll i = 0; i < m; ++i){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		edge[x].push_back(y);
	}
	for (ll i = 1; i <= n; ++i){
		if (!dfn[i]){
			tarjan(i);
		}
	}
	ll ans = 0;
	ll times = 1;
	for (ll i = 1; i <= cnt; ++i){
		ll s = belong[i].size();
		ll tmp = 1000000007;
		ll t;
		for (ll j = 0; j < s; ++j){
			if (input[belong[i][j]] < tmp){
				tmp = input[belong[i][j]];
				t = 1;
			}else if(input[belong[i][j]] == tmp){
				t++;
			}
		}
		ans = ans + tmp;
		times = (times * t) % mod;
	}
	printf("%lld %lld\n",ans,times);
}
```

最后推荐一个网站，可以用来见图

已上图都是用它（[传送门](https://csacademy.com/app/graph_editor/)）做的


---

## 作者：alvis (赞：0)

## 题意
有一个 $n$ 个点，$m$ 条边的有向图，每个点有一个权值，试求**每个环中的最小权值之和**以及**选择最小权值点的方案数**。
## 解决
一道 tarjan 求强联通分量的入门题。

首先，求每个环中的最小权值。

这显然非常好维护。

只需要对于每一个环，我们都记录下**该环中点的最小权值**是多少即可。

其次，求选择可以获得最小权值的点的方案数。

这个我们考虑在什么情况下会出现不同方案呢？

是不是只有 $k$ 个相同权值的点在同一环中才会出现？

为什么？

假设现在在第 $i$ 个环中的最小数为 $a$，在第 $j$ 个环中的最小数为 $b$。

则 $i,j$ 两个环中的最小权值和一定为 $a+b$。

设第 $i$ 个环中的一个不为 $a$ 的数为 $x$，在第 $j$ 个环中的一个不为 $b$ 的数为 $y$，且 $x+y = a+b$。

因为 $x \ge a$，所以 $y\le b$。

又因为 $y \ge b$ ，所以 $y =b $。

所以 $x =a$。

证毕。

所以我们只要维护对于每个环来说，**有几个与其最小权值相同的数**即可。

最后，利用乘法原理求解即可。

**tips**: 最后的结果中，最小值之和不需要取模，而方案数需要取模（被坑了好几次/fad

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 

const int N = 1e5+101, P = 1e9+7, MAXN = LONG_MAX;
int n, m, idx, times, top, cnt;
int val[N], h[N], dfn[N], low[N], stk[N], id[N], minn[N], res[N];
bool can[N];

struct node {
    int e, ne;
}g[N << 2];

void add(int a, int b) {
    g[idx].e = b;
    g[idx].ne = h[a];
    h[a] = idx ++;
}
//tarjan求强连通分量
void tarjan(int u){
    dfn[u] = low[u] = ++ times;
    stk[++ top] = u, can[u] = true;
    
    for(int i = h[u];i != -1;i = g[i].ne) {
        int j = g[i].e;
        if(!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if(can[j]) low[u] = min(low[u], dfn[j]); 
    }
    
    if(dfn[u] == low[u]) {
        cnt ++;
        while(stk[top + 1] != u) {
            int k = stk[top];
            id[k] = cnt;
            can[k] = false;
            //记录每个环中的最小权值
            minn[cnt] = min(minn[cnt], val[k]);
            top --;
        }
    }
}

signed main(){
    memset(h, -1, sizeof h);
    cin >> n;
    for(int i = 1;i <= N;i ++) minn[i] = MAXN;
    for(int i = 1; i <= n;i ++) {
        cin >> val[i];
    }
    cin >> m;
    for(int i = 1, a, b;i <= m;i ++) {
        cin >> a >> b;
        add(a, b);
    }
    //图可能不连通
    for(int i = 1;i <= n;i ++) {
        if(!dfn[i]) tarjan(i);
    }
    int ans = 0, count = 1;
    //统计每个环中有多少个数与最小值相等
    for(int i = 1;i <= n;i ++) {
    	if(val[i] == minn[id[i]]) res[id[i]] ++, res[id[i]] %= P;
	}
    //处理最终结果
    for(int i = 1;i <= cnt;i ++) {
        ans = ans + minn[i], count = (count * res[i]) % P;
    }
    cout << ans << " " << count % P;
    return 0;
}
```


---

## 作者：迟暮天复明 (赞：0)

[可能更佳的阅读体验](https://www.cnblogs.com/1358id/p/Sol-CF427C.html)
# Description
有一张带点权有向图，你要在其中修建若干个检查站，使得对于每一个点 $p$ ，都有 $\geq 1$ 个检查站，满足：
1.  存在一条从这个检查站出发到点 $p$ 的路径；
1.  存在一条从点 $p$ 出发到这个检查站的路径。
求出修建检查站的点权和的最小值，以及当点权和有最小值时的修建方案数。
# Solution
对于每个强连通分量，只需要修建 $1$ 个检查站。
所以可以考虑缩点，这样最小点权和就是每个强连通分量中最小点权之和。
至于修建方案数，可以考虑乘法原理。总方案数等于每个强连通分量中方案数的乘积。
而每个强连通分量的方案数就是强连通分量中点权等于最小点权的点的个数。
然后这道题目就愉快地做完了。

```cpp
using std::vector;
struct Edge {
  ll to, nex;
} e[1000010];
ll dfn[1000010], low[1000010], dfncnt;
ll s[1000010], in_stack[1000010], tp;
ll belong[1000010], sc, sz[1000010];
ll head[1000010], cnt;
ll ans = 1, ans2;
ll val[1000010];
vector<ll> scc[1000010];
void add(ll u, ll v) {
  e[++cnt].to = v;
  e[cnt].nex = head[u];
  head[u] = cnt;
}
void tarjan(ll u) {
  low[u] = dfn[u] = ++dfncnt;
  s[++tp] = u, in_stack[u] = 1;
  for(ll i = head[u]; i; i = e[i].nex) {
    ll v = e[i].to;
    if(!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if(in_stack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(dfn[u] == low[u]) {
    ll it = 0;
    ++sc;
    while(s[tp] != u) {
      belong[s[tp]] = sc;
      sz[sc]++;
      in_stack[s[tp]] = 0;
      scc[sc].push_back(val[s[tp]]);
      --tp;
    }
    belong[s[tp]] = sc;
    sz[sc]++;
    in_stack[s[tp]] = 0;
    scc[sc].push_back(val[s[tp]]);
    --tp;
    std::sort(scc[sc].begin(), scc[sc].end());
    rep(i, 0, sz[sc] - 1) if(scc[sc][i] == scc[sc][0]) ++it;
    ans = ans * it % 1000000007ll;
    ans2 += scc[sc][0];
  }
}
int main() {
  ll n, m;
  read(n);
  rep(i, 1, n) read(val[i]);
  read(m);
  rep(i, 1, m) {
    ll x, y;
    read(x), read(y);
    add(x, y);
  }
  rep(i, 1, n) if(!dfn[i]) tarjan(i);
  print(ans2), putchar(' '), print(ans);
  return 0;
}
```

---

## 作者：Ame__ (赞：0)

### 简化题面
~~这我真不知道怎么简化了~~

### 解题思路
这题我觉得不$pay$当一个紫题说实话

很显然的，对于一个强联通分量里的点，我们直接统计这一个强联通分量里面的点的最小代价以及最小代价的点数是多少

我们就有了最后的代价的答案为

总代价$ans_1=\sum_{i=1}^{tot}V[i]$

那么根据乘法原理，我们有我们的方案数为

方案数$ans_2=\prod_{i=1}^{tot}size[i]$

其中$tot$为强联通分量的总数，$V[i]$为强联通分量内点的最小代价，$size[i]$为点的个数

求强联通分量直接$tarjan$即可，时间复杂度$O(n)$

具体实现看代码即可，注意只对方案取模不对价值取模

### $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
    
#define LL long long
    
#define qwq double
    
#define _ 0
    
#define AME__DEBUG
    
#define TOWA(FMT...) fprintf(stdout , FMT)
    
#define LOG(FMT...) fprintf(stderr , FMT)
    
using namespace std;
    
/*Grievous Lady*/
    
const int BUF_SIZE = 1 << 12;
    
char buf[BUF_SIZE] , *buf_s = buf , *buf_t = buf + 1;
    
#define PTR_NEXT() \
{ \
    buf_s ++; \
    if(buf_s == buf_t) \
    { \
        buf_s = buf; \
        buf_t = buf + fread(buf , 1 , BUF_SIZE , stdin); \
    } \
}
    
#define mians(_s_) \
{ \
    while(!isgraph(*buf_s)) \
        PTR_NEXT(); \
    char register *_ptr_ = (_s_); \
    while(isgraph(*buf_s) || *buf_s == '-') \
    { \
        *(_ptr_ ++) = *buf_s; \
        PTR_NEXT(); \
    } \
    (*_ptr_) = '\0'; \
}
    
template <typename _n_> void mian(_n_ & _x_){
    char buf_s; while(buf_s != '-' && !isdigit(buf_s)) buf_s = getchar();
    bool register _nega_ = false; if(buf_s == '-'){ _nega_ = true; buf_s = getchar(); }
    _x_ = 0; while(isdigit(buf_s)){  _x_ = _x_ * 10 + buf_s - '0'; buf_s = getchar(); } if(_nega_) _x_ = -_x_;
}
    
#define INF 0x3f3f3f3f

#define mod 1000000007

const int kato = 3e5 + 10;

template <typename _n_> bool cmax(_n_ &a , const _n_ &b){ return a < b ? a = b , 1 : 0; }
    
template <typename _n_> bool cmin(_n_ &a , const _n_ &b){ return a > b ? a = b , 1 : 0; }
    
struct Edge{
    int to;
    Edge *nxt;
};

struct Graph{
    Edge yuni[kato << 1] , *head[kato] , *tail;

    void clear(){ memset(head , 0 , sizeof head); tail = yuni; }

    Graph(){ clear(); }

    Edge *operator[](int x){ return head[x]; }

    void add(int x , int y){ *tail = (Edge){y , head[x]}; head[x] = tail ++; }
}Ire;

LL n , m , cnt , top , tot , x , y , ans2 , ans1 = 1;

int dfn[kato] , low[kato] , sta[kato] , c[kato] , w[kato] , v[kato] , size[kato];

bool vis[kato];

void tarjan(int x){
    dfn[x] = low[x] = ++ cnt , vis[x] = 1;
    sta[++ top] = x;
    for(Edge *i = Ire[x] ; i ; i = i -> nxt){
        int v = i -> to;
        if(!dfn[v]){
            tarjan(v);
            low[x] = min(low[x] , low[v]);
        }else if(vis[v]) low[x] = min(low[x] , dfn[v]);
    }
    if(dfn[x] == low[x]){
        int y; tot ++; v[tot] = INF;
        do{
            y = sta[top --] , vis[y] = 0;
            c[y] = tot; 
            if(w[y] < v[tot]) v[tot] = w[y] , size[tot] = 1;
            else if(w[y] == v[tot]) size[tot] ++;
        }while(x != y);
    }
}

inline int Ame_(){
#ifdef AME__
    freopen(".in" , "r" , stdin); freopen(".out" , "w" , stdout); int nol_cl = clock();
#endif
    mian(n);
    for(int i = 1;i <= n;i ++) mian(w[i]);
    mian(m);
    for(int i = 1;i <= m;i ++){
        mian(x) , mian(y);
        Ire.add(x , y);
    }
    for(int i = 1;i <= n;i ++) if(!dfn[i]) tarjan(i);
    for(int i = 1;i <= tot;i ++){ 
        ans1 = 1LL * ans1 * size[i] % mod;
        ans2 = ans2 + v[i];
    }
    TOWA("%lld %lld\n" , ans2 , ans1);
#ifdef AME__TIME
    LOG("Time: %dms\n", int((clock() - nol_cl) / (qwq)CLOCKS_PER_SEC * 1000));
#endif
    return ~~(0^_^0); /*さようならプログラム*/
}
    
int Ame__ = Ame_();
    
int main(){;}
```


---

## 作者：封禁用户 (赞：0)

这题就是[P2194](https://www.luogu.com.cn/problem/P2194),一道[强联通分量](https://baike.baidu.com/item/强连通分量/7448759?fr=aladdin)的~~水~~题,我用[$tarjan$](https://blog.csdn.net/weixin_43843835/article/details/88381828)做的。(以下强联通分量默认最大)

第一问的最小花费其实就是求每个强连通分量里的最小点权值,然后再把它们相加。

具体实现:

```cpp
for(int i=1;i<=cnt;i++) ans1=ans1+minn[i];
```

$cnt$为有多少个强联通分量,$minn_i$是每个强连通分量里的最小点权值。

第二问其实也不难,可以用乘法原理做,在跑$tarjan$的时候加一个判断就行了:如果一个强连通分量中有两个最小点权值相等,那么$sum_i$(记录每个强连通分量里面有多少个最小点权值)就加$1$。这里有一点要注意:如果最小点权值更新了,那么$sum_i$也要随之更新。

具体实现:

```cpp
ans2=1;
for(int i=1;i<=cnt;i++) ans2=(ans2*sum[i])%1000000007;
```

完整代码:

```cpp
#include<bits/stdc++.h>
//#define chenkeqi return
//#define AK 0
//#define PJz ;
using namespace std;
struct edge
{
	long long v,next;
}
e[600005];
long long a[100005],head[600005];
long long low[300005],ins[300005];
long long belong[300005],dfn[300005];
long long cnt,k,tot,n,m,ans1,ans2;
long long minn[300005],sum[300005];
stack<int>s;
void adde(long long u,long long v)
{
	e[++k].v=v;
	e[k].next=head[u];
	head[u]=k;
}
//前向星存图
void tarjan(int u)
{
	dfn[u]=low[u]=++tot;
	s.push(u);
	ins[u]=1;
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int kl;
		cnt++;
		do
		{
			kl=s.top();
			s.pop();
			belong[kl]=cnt;
			ins[kl]=0;
			if(minn[cnt]==a[kl])//如果最小值有相同
				sum[cnt]++;//此强连通分量中多一种方案
			if(a[kl]<minn[cnt])//如果有更小值
			{
				minn[cnt]=a[kl];//更新最小值
				sum[cnt]=1;//此强连通分量中方案归1
			}
		}while(u!=kl);
	}
}
//tarjan模板代码
int main()
{
	memset(head,-1,sizeof(head));
	memset(minn,127,sizeof(minn));//注意minn和head的初始化
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		adde(a,b);//加边
	}
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
			tarjan(i);
	}
	for(int i=1;i<=cnt;i++)
		ans1=ans1+minn[i];
	ans2=1;
	for(int i=1;i<=cnt;i++)
		ans2=(ans2*sum[i])%1000000007;
    //对两个问的操作,前面已经讲过
	cout<<ans1<<" "<<ans2;
	//chenkeqi AK PJz
	return 0;
}
```

十年$OI$一场空,不开$long$ $long$见祖宗~~~

---

## 作者：PrincessYR✨～ (赞：0)

这道题难度并不大，只要会强连通分量基本上都能AC。

强连通分量讲解[看这里](https://183473.blog.luogu.org/tarjan-qiang-lian-tong-fen-liang)

我们分步来看：

首先，他让我们找最小值，我们可以在求强连通分量是给每一个强连通分量先付一个最大值，然后在和属于这个强连通分量的点一一比较，取最小值即可。

```
cost_last[numb]=min(cost_last[numb],cost[q]);
```

cost_last[numb]为第numb个强连通分量的最小值，cost[q]为属于第numb个强连通分量的点q的花费。

其次题目让我们求有几种花费相同的情况，我们可以去找每个强连通分量是否有花费一样的点，如果有就累乘，一直乘道最后，别忘了mod1000000007。

温馨提示：

# long long

请记住不开long long见zz，多开long long见zz。

最后贴上代码：

```
#include<bits/stdc++.h>
#define MAX 0x3f3f3f3f
using namespace std;
const int M= 1e5 + 10;
const int mod=1000000007; 
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
vector<int> m[M];
vector<int> fe[M];
stack<int> st;
bool inst[M];
int n,q,low[M],dfn[M],num;
int a,b,numb;
long long cost_last[M],cost[M],last_sum,latlat;
int nums[M],tot;
void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	inst[x]=true;
	st.push(x);
	for(int i=0;i<m[x].size();i++)
	{
		int next=m[x][i];
		if(dfn[next]==0)
		{
			tarjan(next);
			low[x]=min(low[x],low[next]);
		}
		else if(inst[next]==1)
		{
			low[x]=min(low[x],dfn[next]);
		}
	}
	if(dfn[x]==low[x])
	{
		numb++;
		int q;
		do
		{
			q=st.top();
			st.pop();
			inst[q]=false;
			//bl[q]=numb;
			cost_last[numb]=min(cost_last[numb],cost[q]);
			fe[numb].push_back(q);
		}while(q!=x);
	}
}
int main() 
{
	latlat=1;
	tot=0;
	memset(cost_last,21474836,sizeof(cost_last)) ;
	n=read();
	for(int i=1;i<=n;i++)
	cost[i]=read();
	q=read();
	for(int i=1;i<=q;i++)
	{
		a=read();b=read();
		m[a].push_back(b);
	}
	for(int i=1;i<=n;i++)
		if(dfn[i]==0)
		tarjan(i);
	for(int i=1;i<=numb;i++)
	{
		last_sum+=cost_last[i];
	}
	cout<<last_sum<<" ";
	for(int i=1;i<=numb;i++)
	{
		for(int j=0;j<fe[i].size();j++)
		{
			if(cost[fe[i][j]]==cost_last[i])
			tot++;
		}
		latlat=(latlat*tot)%mod;
		tot=0;
	}
	cout<<latlat;
	return 0;
}
```


---

