# [国家集训队] happiness

## 题目描述

高一一班的座位表是个 $n\times m$ 的矩阵，经过一个学期的相处，每个同学和前后左右相邻的同学互相成为了好朋友。这学期要分文理科了，每个同学对于选择文科与理科有着自己的喜悦值，而一对好朋友如果能同时选文科或者理科，那么他们又将收获一些喜悦值。

作为计算机竞赛教练的 scp 大老板，想知道如何分配可以使得全班的喜悦值总和最大。

## 说明/提示

### 样例解释

两人都选理，则获得 $100+110+1000$ 的喜悦值。

对于 $100\%$ 的数据，$1\le n,m \le 100$，且所有喜悦值均为小于等于 $5000$ 的非负整数。

## 样例 #1

### 输入

```
1 2
1 1
100 110
1
1000```

### 输出

```
1210
```

# 题解

## 作者：Siyuan (赞：32)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

## Description

> 题目链接：[Luogu 1646](https://www.luogu.org/problemnew/show/P1646)

高一一班的座位表是个 $n\times m$ 的矩阵，经过一个学期的相处，每个同学和前后左右相邻的同学互相成为了好朋友。这学期要分文理科了，每个同学对于选择文科与理科有着自己的喜悦值，而一对好朋友如果能同时选文科或者理科，那么他们又将收获一些喜悦值。

作为计算机竞赛教练的 scp 大老板，想知道如何分配可以使得全班的喜悦值总和最大。

数据范围：$1\le n,m\le 100$，喜悦值均为小于等于 $5000$ 的非负整数。

------

## Solution

考虑用网络流求解，**总量减去最小割**即为答案。

对于每个点 $(i,j)$，从 $s$ 连一条容量为选择文科的边，到 $t$ 连一条容量位选择理科的边。

对于 $(i,j)$ 和 $(i+1,j)$ 两个点的组合情况。假设这两个点同时选文科有 $w$ 的喜悦值，我们新建一个节点 $x$，从 $s$ 向 $x$ 连一条容量为喜悦值 $w$ 的边，再从 $x$ 向 $(i,j)$ 和 $(i+1,j)$ 分别连一条容量为 $\texttt{INF}$ 的边。对于左右前后、文科理科同理！

考虑这样做法的**正确性**：每个点自然只能选择一个科目（文科或理科），当某个点选择了文科 $s$，那么它向理科 $t$ 的边都应该要被断开。考虑哪些边会被断开：首先是它直接连向 $t$ 的边，其次是它和别的点组合连向 $t$ 的边，这样一来，这些边在网络图的**割**中是有贡献的，意味着这些边的容量在答案中没有贡献，正确性证明完毕。

**时间复杂度**：$O((nm)^3)$（$\texttt{Dinic}$）

------

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define FOR(i,a,b) for(int i=a;i<=b;++i)

const int N=1e5+5,M=5e6+5;
const int inf=1<<30;
int n,m,tot=1,lnk[N],ter[M],nxt[M],val[M],dep[N],cnr[N];

int id(int x,int y) {
	return (x-1)*m+y;
}
void add(int u,int v,int w) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void addedge(int u,int v,int w) {
	add(u,v,w),add(v,u,0);
}
int bfs(int s,int t) {
	memset(dep,0,sizeof(dep));
	memcpy(cnr,lnk,sizeof(lnk));
	std::queue<int> q;
	q.push(s),dep[s]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(int i=lnk[u];i;i=nxt[i]) {
			int v=ter[i];
			if(val[i]&&!dep[v]) q.push(v),dep[v]=dep[u]+1;
		}
	}
	return dep[t];
}
int dfs(int u,int t,int flow) {
	if(u==t) return flow;
	int ans=0;
	for(int i=cnr[u];i&&ans<flow;i=nxt[i]) {
		cnr[u]=i;
		int v=ter[i];
		if(val[i]&&dep[v]==dep[u]+1) {
			int x=dfs(v,t,std::min(val[i],flow-ans));
			if(x) val[i]-=x,val[i^1]+=x,ans+=x;
		}
	}
	if(ans<flow) dep[u]=-1;
	return ans;
}
int dinic(int s,int t) {
	int ans=0;
	while(bfs(s,t)) {
		int x;
		while((x=dfs(s,t,inf))) ans+=x;
	}
	return ans;
}
int main() {
	scanf("%d%d",&n,&m);
	int s=0,t=n*m+2*n*(m-1)+2*(n-1)*m+1,cnt=n*m;
	int ans=0;
	FOR(i,1,n) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,id(i,j),x);
	}
	FOR(i,1,n) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(id(i,j),t,x);
	}
	FOR(i,1,n-1) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,++cnt,x);
		addedge(cnt,id(i,j),inf);
		addedge(cnt,id(i+1,j),inf);
	}
	FOR(i,1,n-1) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(++cnt,t,x);
		addedge(id(i,j),cnt,inf);
		addedge(id(i+1,j),cnt,inf);
	}
	FOR(i,1,n) FOR(j,1,m-1) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,++cnt,x);
		addedge(cnt,id(i,j),inf);
		addedge(cnt,id(i,j+1),inf);
	}
	FOR(i,1,n) FOR(j,1,m-1) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(++cnt,t,x);
		addedge(id(i,j),cnt,inf);
		addedge(id(i,j+1),cnt,inf);
	}
	printf("%d\n",ans-dinic(s,t));
	return 0;
}
```



---

## 作者：nofind (赞：30)

### 本篇篇幅过长，可能会出不少错，我已经查过一遍了，如果还有错恳请提出，我马上修改。

------------

## [题意](https://www.luogu.com.cn/problem/P1646)

这题有两种做法：

根据套路，先将所有愉悦值加上，之后减去最小代价。
### 1.

首先套路地，从源点$s$向每个点连选文科的价值，从每个点向汇点$t$连选理科的价值，割那条表示不选哪科，这样可以保证每个人不选文就选理。

接下来考虑如何处理这个限制：  
只要点对$(i,j)$中至少有一个不选文（理科同理），我们就要减去同选文的价值。

我们可以新建一个节点$x$，从$s$向$x$连容量为$i,j$同选文的价值，之后从$x$向$i,j$连容量为$inf$的边。

我们发现这时如果$i,j$两点中有一个点理科边没有割（即不选文），那么此时就存在一条$s-x-i/j-t$这样一条路，我们只能割掉$s-x$这条边，因为如果割掉$i/j-t$这条边，那么我们可以不割$s-i/j$这条边，这与选文科不符，于是我们还是能保证每个人都选且只选了一科。

建出的图如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/9pjdyuqc.png)

code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=110;
const ll inf=1e18;
int n,m,cnt=1,tot=2,S,T;
int head[maxn*maxn*20],cur[maxn*maxn*20],dep[maxn*maxn*20];
ll ans;
struct edge{int to,nxt;ll flow;}e[maxn*maxn*40];
inline int id(int i,int j){return (i-1)*m+j;}
inline void add(int u,int v,ll w)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	e[cnt].flow=w;
}
inline void addflow(int u,int v,ll w){add(u,v,w);add(v,u,0);}
inline bool bfs()
{
    memset(dep,0,sizeof(dep));
    for(int i=0;i<=tot;i++)cur[i]=head[i];
    queue<int>q;
    q.push(S);dep[S]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to;
            if(dep[y]||e[i].flow<=0)continue;
            dep[y]=dep[x]+1;q.push(y);
        }
    }
    return dep[T]>0;
}
ll dfs(int x,int goal,ll lim)
{
    if(x==goal||lim<=0)return lim;
    ll res=lim;
    for(int i=cur[x];i;i=e[i].nxt)
    {
        cur[x]=i;
        int y=e[i].to;
        if(e[i].flow<=0||dep[y]!=dep[x]+1)continue;
        ll tmp=dfs(y,goal,min(res,e[i].flow));
        if(tmp<=0)dep[y]=0;
        res-=tmp;
        e[i].flow-=tmp,e[i^1].flow+=tmp;
        if(res<=0)break;
    }
    return lim-res;
}
inline ll Dinic()
{
    ll res=0;
    while(bfs())res+=dfs(S,T,inf);
    return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=0,T=n*m+1;
	tot=n*m+1;
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=m;j++)
		{
			scanf("%d",&x);ans+=x;
			addflow(S,id(i,j),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=m;j++)
		{	
			scanf("%d",&x);ans+=x;
			addflow(id(i,j),T,x);
		}
	for(int i=1;i<n;i++)
		for(int j=1,x;j<=m;j++)
		{	
			scanf("%d",&x);ans+=x;
			addflow(S,++tot,x);
			addflow(tot,id(i+1,j),inf),addflow(tot,id(i,j),inf);
		}
	for(int i=1;i<n;i++)
		for(int j=1,x;j<=m;j++)
		{	
			scanf("%d",&x);ans+=x;
			addflow(++tot,T,x);
			addflow(id(i+1,j),tot,inf),addflow(id(i,j),tot,inf);
		}
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<m;j++)
		{
			scanf("%d",&x);ans+=x;
			addflow(S,++tot,x);
			addflow(tot,id(i,j+1),inf),addflow(tot,id(i,j),inf);
		}	
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<m;j++)
		{
			scanf("%d",&x);ans+=x;
			addflow(++tot,T,x);
			addflow(id(i,j+1),tot,inf),addflow(id(i,j),tot,inf);
		}		
	printf("%lld",ans-Dinic());
	return 0;
}
```
### 2.

常规方法解方程。

还是经典老图：
![](https://cdn.luogu.com.cn/upload/image_hosting/pwzh0xcx.png)

这张图上面是$i$，下面是$j$，左边是文科，右边是理科，这里割哪条边表示不选哪科。

我们开始解方程：

先设$a_i$表示$i$选文科的价值，$b_i$表示$i$选理科的价值，$c_{i,j}$表示$i,j$同选文科的价值，$d_{i,j}$表示$i,j$同选理科的价值。

对于点对$(i,j)$可以列出方程（以下方程按照“同文”，“同理”，“$i$文$j$理”，“$i$理$j$文”排序）：

$\begin{cases}c+d=b_i+b_j+d_{i,j}<1>\\ a+b=a_i+a_j+c_{i,j}<2>\\ b+c+e=b_i+a_j+c_{i,j}+d_{i,j}<3>\\a+d+f=a_i+b_j+c_{i,j}+d_{i,j}<4>\end{cases}$

我们通过$<3>+<4>-<1>-<2>$可以得到：$e+f=c_{i,j}+d_{i,j}$  
令$e=f$，可得：$e=f=\frac{c_{i,j}+d_{i,j}}{2}$

我们令$a=a_i+\frac{c_{i,j}}{2}$，即可解得其他变量的值：  
$b=a_j+\frac{c_{i,j}}{2}$  
$c=b_i+\frac{d_{i,j}}{2}$  
$d=b_j+\frac{d_{i,j}}{2}$

于是我们就可以建图了，但是由于$a,b,c,d,e,f$不一定是整数，我们先整体乘2，最后除回去即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
const int inf=1e9;
int n,m,cnt=1,S,T,ans;
int head[maxn*maxn*20],cur[maxn*maxn*20],dep[maxn*maxn*20];
struct edge{int to,nxt,flow;}e[maxn*maxn*40];
inline int read()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
	return res*f;
}
inline int id(int i,int j){return (i-1)*m+j;}
inline void add(int u,int v,int w)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	e[cnt].flow=w;
}
inline void addflow(int u,int v,int w){add(u,v,w),add(v,u,0);}
inline bool bfs()
{
    memset(dep,0,sizeof(dep));
    for(int i=S;i<=T;i++)cur[i]=head[i];
    queue<int>q;
    q.push(S);dep[S]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to;
            if(dep[y]||e[i].flow<=0)continue;
            dep[y]=dep[x]+1;q.push(y);
        }
    }
    return dep[T]>0;
}
int dfs(int x,int goal,int lim)
{
    if(x==goal||lim<=0)return lim;
    int res=lim;
    for(int i=cur[x];i;i=e[i].nxt)
    {
        cur[x]=i;
        int y=e[i].to;
        if(e[i].flow<=0||dep[y]!=dep[x]+1)continue;
        int tmp=dfs(y,goal,min(res,e[i].flow));
        if(tmp<=0)dep[y]=0;
        res-=tmp;
        e[i].flow-=tmp,e[i^1].flow+=tmp;
        if(res<=0)break;
    }
    return lim-res;
}
inline int Dinic()
{
    int res=0;
    while(bfs())res+=dfs(S,T,inf);
    return res;
}
int main()
{
	n=read(),m=read();
	S=0,T=n*m+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=read();ans+=x;
			addflow(S,id(i,j),x<<1);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=read();ans+=x;
			addflow(id(i,j),T,x<<1);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=read();ans+=x;
			addflow(id(i,j),id(i+1,j),x);addflow(id(i+1,j),id(i,j),x);
			addflow(S,id(i,j),x),addflow(S,id(i+1,j),x);//之前少加。 
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=read();ans+=x;
			addflow(id(i,j),id(i+1,j),x);addflow(id(i+1,j),id(i,j),x);
			addflow(id(i,j),T,x),addflow(id(i+1,j),T,x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			int x=read();ans+=x;
			addflow(id(i,j),id(i,j+1),x);addflow(id(i,j+1),id(i,j),x);
			addflow(S,id(i,j),x),addflow(S,id(i,j+1),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			int x=read();ans+=x;
			addflow(id(i,j),id(i,j+1),x);addflow(id(i,j+1),id(i,j),x);
			addflow(id(i,j),T,x),addflow(id(i,j+1),T,x);
		}
	printf("%d",ans-(Dinic()>>1));
	return 0;
}
```


---

## 作者：bztMinamoto (赞：9)

打个广告->[这里](https://www.cnblogs.com/bztMinamoto/p/9568462.html)

　额，这题最重要的是一个模型转换的思想。因为最小割可以代表选择或不选择，那么我们就让每一个最小割的状态分别代表题目所示的每一个状态

　　先考虑建图，假设$A$和$B$是有关联的两点，那么建如下的图

 ![](https://i.loli.net/2018/09/01/5b8a22633625a.png)

　　其中$S$表示源点，代表文科，$T$表示汇点，代表理科，$A,B$是互相关联的两点。这张图的意思是，如果某个点与$S$相连，代表它选择文科，如果与$T$相连，代表它选择理科

　　那么我们考虑一下，要怎么样才能使全文，全理，一文一理三种情况都能出现呢？

　　我们考虑图中边的流量，a=A文+AB文/2，c=B文+AB文/2，b=A理+AB理/2，d=B理+AB理/2，e=f=AB文/2+AB理/2

　　因为最小割的割可以代表选择，所以我们可以通过枚举割来枚举选择。那么上图中是不是每一个割都代表了一种选择呢？

　　我们设sum=A文+B文+A理+B理+AB文+AB理

　　当两人都选文时，我们割去b，d，那么割的大小为A理+B理+AB理，用sum减去割剩下的就是全选文的高兴值

　　如果两人都选理，那么我们割去a，c，和上面一个一样，就不多说

　　如果两人一文一理怎么办呢？我们假设A文B理，割去a，f，d，那么sum减去割的大小就是A选文和B选理的高兴值

　　综上所述，不难发现上图的每一个割都代表了一种选择的状态。那么我们要令高兴值最大，那么割必须最小，只要求出一个最小割就行了

　　代码参考~~（抄）~~了hzwer的
```
// luogu-judger-enable-o2
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=10005,M=500005;
int head[N],Next[M],ver[M],edge[M],tot=1;
int dep[N],cur[N],n,m,s,t,mxflow;
int a[105][105],b[105][105],id[105][105],ans;
queue<int> q;
inline void add_edge(int u,int v,int e){
    ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
}
inline void ins(int u,int v,int e){
    add_edge(u,v,e),add_edge(v,u,e);
}
inline void insert(int u,int v,int e){
    add_edge(u,v,e),add_edge(v,u,0);
}
bool bfs(){
    memset(dep,-1,sizeof(dep));
    while(!q.empty()) q.pop();
    for(int i=s;i<=t;++i) cur[i]=head[i];
    q.push(s),dep[s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=Next[i]){
            int v=ver[i];
            if(dep[v]<0&&edge[i]){
                dep[v]=dep[u]+1,q.push(v);
                if(v==t) return true;
            }
        }
    }
    return false;
}
int dfs(int u,int limit){
    if(u==t||!limit) return limit;
    int flow=0,f;
    for(int i=cur[u];i;i=Next[i]){
        int v=ver[i];cur[u]=i;
        if(dep[v]==dep[u]+1&&(f=dfs(v,min(limit,edge[i])))){
            flow+=f,limit-=f;
            edge[i]-=f,edge[i^1]+=f;
            if(!limit) break;
        }
    }
    if(!flow) dep[u]=-1;
    return flow;
}
void dinic(){
    while(bfs()) mxflow+=dfs(s,inf);
}
void build(){
    int x;s=0,t=n*m+1;
    for(int i=1;i<n;++i)
    for(int j=1;j<=m;++j){
        x=read(),ans+=x;
        a[i][j]+=x,a[i+1][j]+=x;
        ins(id[i][j],id[i+1][j],x);
    }
    for(int i=1;i<n;++i)
    for(int j=1;j<=m;++j){
        x=read(),ans+=x;
        b[i][j]+=x,b[i+1][j]+=x;
        ins(id[i][j],id[i+1][j],x);
    }
    for(int i=1;i<=n;++i)
    for(int j=1;j<m;++j){
        x=read(),ans+=x;
        a[i][j]+=x,a[i][j+1]+=x;
        ins(id[i][j],id[i][j+1],x);
    }
    for(int i=1;i<=n;++i)
    for(int j=1;j<m;++j){
        x=read(),ans+=x;
        b[i][j]+=x,b[i][j+1]+=x;
        ins(id[i][j],id[i][j+1],x);
    }
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j){
        insert(s,id[i][j],a[i][j]);
        insert(id[i][j],t,b[i][j]);
    }
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    a[i][j]=read(),ans+=a[i][j],a[i][j]<<=1;
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    b[i][j]=read(),ans+=b[i][j],b[i][j]<<=1;
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    id[i][j]=(i-1)*m+j;
    build(),dinic();
    printf("%d\n",ans-(mxflow>>1));
    return 0;
}
```

---

## 作者：Dispwnl (赞：6)

> 11.29 换了图

考虑记录总量再求最小割

对于每个点，$S$（源点）与ta连一条容量为选文的边，$T$（汇点）与ta连一条容量为选理的边

建立新节点，$S$与新节点连一条容量为前后桌同时选文的边

新节点再分别与前后桌连一条容量为$inf$的边（为了不影响答案）

再建一个新节点，新节点与t连一条容量为前后桌同时选理的边

前后桌再与新节点连一条容量为$inf$的边

左右桌同理

这时跑最小割（也就是最大流），得到的是最小得不到的快乐值

所以所有快乐值-最小割就是答案

样例的图：

 ![](https://a-failure.github.io/img/study/happiness.png) 

图中红点为第一个新建的点，橙点为第二个新建的点，蓝点为原来的点，跑最小割为$3$

### 代码
```
# include<iostream>
# include<cstdio>
# include<cstring>
# include<cstdlib>
# include<queue>
# define pu(x,y) (x-1)*m+y
using namespace std;
const int MAX=2e5+1,inf=1e8,t=2e5;
struct p{
    int x,y,dis;
}c[MAX<<1];
int n,m,num,SUM;
int h[MAX],d[MAX];
void add(int x,int y,int dis)
{
    c[num].x=h[y],c[num].y=x,c[num].dis=0,h[y]=num++;
    c[num].x=h[x],c[num].y=y,c[num].dis=dis,h[x]=num++;
}
bool bfs()
{
    memset(d,0,sizeof(d));
    queue<int> qu;
    qu.push(0);
    d[0]=1;
    while(!qu.empty())
    {
        int tt=qu.front();
        qu.pop();
        for(int i=h[tt];i;i=c[i].x)
          if(!d[c[i].y]&&c[i].dis)
          {
              d[c[i].y]=d[tt]+1;
              qu.push(c[i].y);
          }
    }
    return d[t];
}
int dfs(int x,int dix)
{
    if(!dix||x==t) return dix;
    int sum=0;
    for(int i=h[x];i;i=c[i].x)
      if(c[i].dis&&d[c[i].y]==d[x]+1)
      {
          int dis=dfs(c[i].y,min(dix,c[i].dis));
          if(dis)
          {
              dix-=dis;
              sum+=dis;
              c[i].dis-=dis;
              c[i^1].dis+=dis;
              if(!dix) break;
        }
      }
    if(!sum) d[x]=-1;
    return sum;
}
int dinic()
{
    int tot=0;
    while(bfs()) tot+=dfs(0,inf);
    return tot;
}
int main()
{
    scanf("%d%d",&n,&m);
    int ss=pu(n,m);
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        {
            int dis,tt=pu(i,j);
            scanf("%d",&dis);
            SUM+=dis;
            add(0,tt,dis);
        }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        {
            int dis,tt=pu(i,j);
            scanf("%d",&dis);
            SUM+=dis;
            add(tt,t,dis);
        }
    for(int i=1;i<n;i++)
      for(int j=1;j<=m;j++)
        {
            int dis,tt=pu(i,j)+ss,t1=pu(i,j),t2=pu(i+1,j);
            scanf("%d",&dis);
            SUM+=dis;
            add(0,tt,dis);
            add(tt,t1,inf);
            add(tt,t2,inf);
        }
    for(int i=1;i<n;i++)
      for(int j=1;j<=m;j++)
        {
            int dis,tt=pu(i,j)+2*ss,t1=pu(i,j),t2=pu(i+1,j);
            scanf("%d",&dis);
            SUM+=dis;
            add(tt,t,dis);
            add(t1,tt,inf);
            add(t2,tt,inf);
        }
    for(int i=1;i<=n;i++)
      for(int j=1;j<m;j++)
        {
            int dis,tt=pu(i,j)+3*ss,t1=pu(i,j),t2=pu(i,j+1);
            scanf("%d",&dis);
            SUM+=dis;
            add(0,tt,dis);
            add(tt,t1,inf);
            add(tt,t2,inf);
        }
    for(int i=1;i<=n;i++)
      for(int j=1;j<m;j++)
        {
            int dis,tt=pu(i,j)+4*ss,t1=pu(i,j),t2=pu(i,j+1);
            scanf("%d",&dis);
            SUM+=dis;
            add(tt,t,dis);
            add(t1,tt,inf);
            add(t2,tt,inf);
        }
    printf("%d",SUM-dinic());
    return 0;
}
```


---

## 作者：Infiltrator (赞：5)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P1646)

------------

# Solution

一种列方程的套路。

我们先单独找出两个点的关系来考虑。

假设有$x$和$y$两个同学，向$S$连边代表选理科，向$T$连边代表选文科。设$S$向$x$连的有向边为$a$，$S$向$y$连的有向边为$b$，$x$向$T$连的有向边为$c$，$y$向$T$连的有向边为$d$，$x$和$y$之间连了一条双向边$e$，割掉一条边的流量代表损失了这么多的愉悦值。

设都选理科的愉悦值是$v_1$，都选文科的愉悦值是$v_2$，按照题意可列方程组如下：

$$a + b = v_1$$

这是对应的两个同学都选理科。

$$c + d = v_2$$

这是对应的两个同学都选文科。

$$a + e + d = v_1 + v_2$$

这是对应的$x$选理科，$y$选文科。

$$b + e + c = v_1 + v_2$$

这是对应的$x$选文科，$y$选理科。

解得

$$a = b = \frac{v_1}{2}, c = d = \frac{v_2}{2}, e = \frac{v_1 + v_2}{2}$$

那么我们只需要从$S$向每个点连一条容量为该同学选理科的愉悦值和他所有相邻的同学选理科的之和的有向边，从每个同学向$T$连一条容量为该同学选文科和他所有相邻的同学都选文科的愉悦值之和的有向边。

每个同学向它相邻的同学连一条容量为他们同时都选理科或者文科的愉悦值的平均值的双向边。

那么答案就是所有愉悦值的和减去最小割。

注意因为要算平均值，所以可能出现小数，这样在一开始连边的时候乘二，最后再除以二就行了。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue> 
using namespace std;

const int N = 1000050;
const int M = 2000050;
const int INF = 999999999;

int head[N], num = 1, n, m, s, t, tu[500][500][2], tmp[500][500], sum, d[N], x;

struct Node
{
	int next, to, flow;
} edge[M * 2];

void Addedge(int u, int v, int w)
{
	edge[++num] = (Node){head[u], v, w};
	head[u] = num;
	return;
}

void Add(int u, int v, int w)
{
	Addedge(u, v, w);
	Addedge(v, u, 0);
	return;
}

int Id(int a, int b)
{
	return (a - 1) * m + b;
} 

template <class T>
void Read(T &x)
{
	x = 0; int p = 0; char st = getchar();
	while (st < '0' || st > '9') p = (st == '-'), st = getchar();
	while (st >= '0' && st <= '9') x = (x << 1) + (x << 3) +st - '0', st = getchar();	
	x = p ? -x : x;
	return;
} 

template <class T>
void Put(T x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) Put(x / 10);
	putchar(x % 10 + '0');
	return; 
}

bool Bfs()
{
    queue<int> q;
    for (int i = 0; i <= t; i++) d[i] = 0;
    d[s] = 1; q.push(s);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = edge[i].next)
            if (!d[edge[i].to] && edge[i].flow)
            {
                d[edge[i].to] = d[u] + 1;
                q.push(edge[i].to);
                if (edge[i].to == t) return 1;
            }
    }
    return 0;
}

int Dinic(int x, int flow)
{
    if (x == t || !flow) return flow;
    int rest = flow;
    for (int i = head[x]; i && rest; i = edge[i].next)
        if (edge[i].flow && d[edge[i].to] == d[x] + 1)
        {
            int v = edge[i].to;
            int tmp = Dinic(v, min(rest, edge[i].flow));
            rest -= tmp;
            edge[i].flow -= tmp;
            edge[i ^ 1].flow += tmp;
            if (!tmp) d[v] = 0;
        }
    return flow - rest;
}

int Maxflow()
{
	int maxflow = 0, tmp;
	while (Bfs())
	{
		tmp = Dinic(s, INF);
		if (tmp) maxflow += tmp;
	}
	return maxflow;
}

int main()
{
	Read(n); Read(m); t = n * m + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			Read(x);
			sum += x;
			tu[i][j][1] += x * 2;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			Read(x);
			sum += x;
			tu[i][j][0] += x * 2;
		}
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= m; j++)
		{
			Read(x);
			sum += x;
			tmp[i][j] += x;
			tu[i][j][1] += x;
			tu[i + 1][j][1] += x;
		}
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= m; j++)
		{
			Read(x);
			sum += x;
			tmp[i][j] += x;
			Add(Id(i, j), Id(i + 1, j), tmp[i][j]);
			Add(Id(i + 1, j), Id(i, j), tmp[i][j]);
			tu[i][j][0] += x;
			tu[i + 1][j][0] += x;
			tmp[i][j] = 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m - 1; j++)
		{
			Read(x);
			sum += x;
			tmp[i][j] += x;
			tu[i][j][1] += x;
			tu[i][j + 1][1] += x; 
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m - 1; j++)
		{
			Read(x);
			sum += x;
			tmp[i][j] += x;
			Add(Id(i, j), Id(i, j + 1), tmp[i][j]);
			Add(Id(i, j + 1), Id(i, j), tmp[i][j]);
			tu[i][j][0] += x;
			tu[i][j + 1][0] += x;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			Add(s, Id(i, j), tu[i][j][0]);
			Add(Id(i, j), t, tu[i][j][1]);
		}
	Put(sum - Maxflow() / 2); 
	return 0;
}
```

---

## 作者：吾王美如画 (赞：2)

# 唔姆
~~一道令人偷♂税的网络流~~

---
我们把问题分开了讨论

- 首先，如果只是每个人文理科可以得相应的愉♂悦值，那这题就是标准的最小割了（~~其实直接选最大的就可以了，但为了节目效果，大家配合一下~~）把源点向每个人连条容量为文科愉悦值的边，再把每个人向汇点连条容量为理科愉悦值的边。然后用总愉悦值-最小割就OK了（这不用说吧）
- 接着，问题来了。辣个一起学习所获得的额外的愉悦值肿么办呢？其实可以看做把这俩人和成一个点，但是要注意的是，为了限制每个人只能选一个学科，我们要为文科和一个点，为理科和一个点，然后源连文，理连汇（就是把先开始说的转换一下啦），然后各自连上他们所对应的两个点，以保证没人只能选一门学科。
- 最后，还是和第一条说的那样，总愉悦值-最小割就OK啦（有个大佬的题解里那图画的超好的，有助于理解，大家可以去看看）

~~贴代码总是令人偷♂税~~

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define MAXN 100050
#define MAXM 150005
using namespace std;
int head[MAXN],next[MAXM*2],to[MAXM*2],w[MAXM*2];
int n,m,S,T;
int cnt=-1;
int deep[MAXN];
void link(int a,int b,int c){
     cnt++;
     w[cnt]=c;
     next[cnt]=head[a];
     to[cnt]=b;
     head[a]=cnt;
     cnt++;
     w[cnt]=0;
     next[cnt]=head[b];
     to[cnt]=a;
     head[b]=cnt;
}
bool bfs(){
     memset(deep,0,sizeof(deep));
     queue<int> q;
     while(!q.empty())q.pop();
     q.push(S);
     deep[S]=1;
     while(!q.empty()){
                       int now=q.front();
                       q.pop();
                       for(int i=head[now];i!=-1;i=next[i]){
                               if (w[i]&&!deep[to[i]]){
                                                       deep[to[i]]=deep[now]+1;
                                                       q.push(to[i]);
                               }
                       }
     }
     if (deep[T])return 1;else return 0;
}
int dinic(int now,int last){
    if (now==T||!last)return last;
    int ret=0;
    for(int i=head[now];i!=-1;i=next[i]){
            if(deep[to[i]]-1==deep[now]&&w[i]){
                                               int zgl=dinic(to[i],min(w[i],last-ret));
                                               if (zgl){
                                                        w[i]-=zgl;
                                                        w[i^1]+=zgl;     
                                                        ret+=zgl;
                                               }
            }
    }
    if (!ret)deep[now]=-1;
    return ret;
}
int num(int a,int b){
    return m*(a-1)+b;
}
int main(){
    cin>>n>>m;
    S=0;T=MAXN-1;
    int a;
    memset(head,-1,sizeof(head));
    long long sum=0;
    for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                    scanf("%d",&a);
                    link(S,num(i,j),a);
                    sum+=a;
            }
    }
    for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                    scanf("%d",&a);
                    link(num(i,j),T,a);
                    sum+=a;
            }
    }
    for(int i=1;i<n;i++){
            for(int j=1;j<=m;j++){
                    scanf("%d",&a);
                    link(S,num(i,j)+10100,a);
                    link(num(i,j)+10100,num(i,j),a);
                    link(num(i,j)+10100,num(i+1,j),a);
                    sum+=a;
            }
    }
    for(int i=1;i<n;i++){
            for(int j=1;j<=m;j++){
                    scanf("%d",&a);
                    link(num(i,j)+20100,T,a);
                    link(num(i,j),num(i,j)+20100,a);
                    link(num(i+1,j),num(i,j)+20100,a);
                    sum+=a;
            }
    }
    for(int i=1;i<=n;i++){
            for(int j=1;j<m;j++){
                    scanf("%d",&a);
                    link(S,num(i,j)+10100,a);
                    link(num(i,j)+10100,num(i,j),a);
                    link(num(i,j)+10100,num(i,j+1),a);
                    sum+=a;
            }
    }
    for(int i=1;i<=n;i++){
            for(int j=1;j<m;j++){
                    scanf("%d",&a);
                    link(num(i,j)+20100,T,a);
                    link(num(i,j),num(i,j)+20100,a);
                    link(num(i,j+1),num(i,j)+20100,a);
                    sum+=a;
            }
    }
    long long ans=0;
    while(bfs())
                 ans+=dinic(S,9999999);
    cout<<sum-ans;
    return 0;
}

```


---

## 作者：MloVtry (赞：2)

最小割，割去最小的不可得喜悦值。

一种滋滋同选文和同选理额外喜悦值不同的建边方法，新建附加节点。

新建一些附加节点node表示a与b同选择文，那么s-额外值->node,node-inf->a,b;同选理a,b-inf->node,node-额外值->t。

累计所有值，然后减去最小割。


```cpp
#include<iostream>
#define inf 1<<30
#include<cstring>
#include<cstdio>
#define M 1000000
#define N 100000
#include<queue>
using namespace std;
int n,m,s,t,ans,it;
int head[N],Next[M],to[M],cup[M],e=1;
void buid(int u,int v,int c)
{
    Next[++e]=head[u],head[u]=e;
    to[e]=v,cup[e]=c;
}
int id(int x,int y)
{
    return (x-1)*m+y;
}
int use[N],itc[N];
queue<int> q;
bool bfs()
{
    memset(itc,0,sizeof(itc));
    itc[s]=1;q.push(s);
    while(!q.empty())
    {
        int now=q.front();q.pop();
        for(int i=head[now];i;i=Next[i])
        {
            if(!cup[i]) continue;
            int j=to[i];
            if(!itc[j]) itc[j]=itc[now]+1,q.push(j);
        }
    }
    return itc[t];
}
int doit(int now,int want)
{
    if(now==t||!want) return want;
    int get=0;
    for(int i=use[now];i;i=Next[i])
    {
        use[now]=i;
        int j=to[i];
        if(itc[j]==itc[now]+1)
        {
            int f=doit(j,min(want,cup[i]));
            get+=f;want-=f;
            cup[i]-=f;cup[i^1]+=f;
            if(!want) return get;
        }
    }
    return get;
}
void max_flow()
{
    while(bfs())
    {
        for(int i=s;i<=t;++i) use[i]=head[i];
        ans-=doit(s,inf);
    }
}
int main()
{
    scanf("%d%d",&n,&m);t=n*m*5+1;
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    scanf("%d",&it),ans+=it,buid(s,id(i,j),it),buid(id(i,j),s,0);
     
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    scanf("%d",&it),ans+=it,buid(id(i,j),t,it),buid(t,id(i,j),0);
     
    for(int i=1;i<n;++i)
    for(int j=1;j<=m;++j)
    {
        scanf("%d",&it),ans+=it;
        int iam=n*m+id(i,j);
        buid(s,iam,it);
        buid(iam,s,0);
         
        buid(iam,id(i,j),inf);
        buid(id(i,j),iam,0);
         
        buid(iam,id(i+1,j),inf);
        buid(id(i+1,j),iam,0);
    }
     
    for(int i=1;i<n;++i)
    for(int j=1;j<=m;++j)
    {
        scanf("%d",&it),ans+=it;
        int iam=2*n*m+id(i,j);
        buid(iam,t,it);
        buid(t,iam,0);
         
        buid(iam,id(i,j),0);
        buid(id(i,j),iam,inf);
         
        buid(iam,id(i+1,j),0);
        buid(id(i+1,j),iam,inf);        
    }
     
    for(int i=1;i<=n;++i)
    for(int j=1;j<m;++j)
    {
        scanf("%d",&it),ans+=it;
        int iam=3*n*m+id(i,j);
        buid(s,iam,it);
        buid(iam,s,0);
         
        buid(iam,id(i,j),inf);
        buid(id(i,j),iam,0);
         
        buid(iam,id(i,j+1),inf);
        buid(id(i,j+1),iam,0);
    }
     
    for(int i=1;i<=n;++i)
    for(int j=1;j<m;++j)
    {
        scanf("%d",&it),ans+=it;
        int iam=4*n*m+id(i,j);
        buid(iam,t,it);
        buid(t,iam,0);
         
        buid(iam,id(i,j),0);
        buid(id(i,j),iam,inf);
         
        buid(iam,id(i,j+1),0);
        buid(id(i,j+1),iam,inf);        
    }
    max_flow();
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：ysy20021208 (赞：0)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**分析与题解：**这就是例题二的限制条件进行一下小更改，对于每一个同学，不是要和相邻同学都选择一个才能有额外收益，而是只有一个一样就能有额外收益。

```c++
// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 110
#define inf 1000000001
int n,m,s,t,ans,idx=1;
int head[N*N],cur[N*N],to[(N*N)<<3],val[(N*N)<<3],nxt[(N*N)<<3];
int math[N][N],chin[N][N];int dis[N*N];
int ea_ma_x[N][N],ea_ch_x[N][N];
int ea_ma_y[N][N],ea_ch_y[N][N];
int find_id(int a,int b) {return (a-1)*m+b;}
void add(int a,int b,int c)
{nxt[++idx]=head[a],to[idx]=b,val[idx]=c,head[a]=idx;}
bool bfs()
{
    memset(dis,-1,sizeof(dis));
    queue <int> q; q.push(s),dis[s]=0;
    while(!q.empty())
    {
        int p=q.front();q.pop();
        if(p==t) return true;
        for(int i=head[p];i;i=nxt[i])
            if(val[i]>0&&dis[to[i]]==-1)
                dis[to[i]]=dis[p]+1,q.push(to[i]);
    } return false;
}
int dfs(int p,int flow)
{
    int now,temp=flow;
    if(p==t) return flow;
    for(int i=cur[p];i;i=nxt[i])
        if(dis[to[i]]==dis[p]+1&&val[i]>0)
        {
            now=dfs(to[i],min(val[i],temp));
            if(!now) dis[to[i]]=-1;
            temp-=now,val[i]-=now,val[i^1]+=now;
            if(val[i]) cur[p]=i;
            if(!temp) break;
        } return flow-temp;
}
void dinic() {while(bfs()) memcpy(cur,head,sizeof(head)),ans-=dfs(s,inf);}
int main()
{
    scanf("%d%d",&n,&m),s=n*m+1,t=n*m+2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&math[i][j]),ans+=2*math[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&chin[i][j]),ans+=2*chin[i][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++) 
            scanf("%d",&ea_ma_x[i][j]),ans+=2*ea_ma_x[i][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++) 
            scanf("%d",&ea_ch_x[i][j]),ans+=2*ea_ch_x[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++) 
            scanf("%d",&ea_ma_y[i][j]),ans+=2*ea_ma_y[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++) 
            scanf("%d",&ea_ch_y[i][j]),ans+=2*ea_ch_y[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        add(s,find_id(i,j),math[i][j]*2+ea_ma_x[i-1][j]
            +ea_ma_x[i][j]+ea_ma_y[i][j-1]+ea_ma_y[i][j]);
        add(find_id(i,j),s,0);
        add(find_id(i,j),t,chin[i][j]*2+ea_ch_x[i-1][j]
            +ea_ch_x[i][j]+ea_ch_y[i][j-1]+ea_ch_y[i][j]);
        add(t,find_id(i,j),0);
        if(i!=n) add(find_id(i,j),find_id(i+1,j),ea_ch_x[i][j]+ea_ma_x[i][j]),
            add(find_id(i+1,j),find_id(i,j),ea_ch_x[i][j]+ea_ma_x[i][j]);
        if(j!=m) add(find_id(i,j),find_id(i,j+1),ea_ch_y[i][j]+ea_ma_y[i][j]),
            add(find_id(i,j+1),find_id(i,j),ea_ch_y[i][j]+ea_ma_y[i][j]);
    } dinic();
    printf("%d\n",ans/2);
}
```

---

