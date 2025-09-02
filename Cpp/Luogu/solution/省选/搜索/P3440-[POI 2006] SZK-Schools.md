# [POI 2006] SZK-Schools

## 题目描述

B 国境内有 $n$ 所学校，每所学校都有一个 $1 \sim n$ 的编号。

由于管理过于宽松，可能存在两个学校同时用一个编号的情况，当然也存在一个编号没有学校用的情况。

现在国王决定重新给所有学校编号，使得任意两个学校的编号不同。

当然，改变编号是一个很繁重的工作，学校不希望自己的编号改变太多。每个学校都有一个可以接受的新编号区间 $[a,b]$，以及改变编号的单位成本 $k$。如果一个学校的旧编号为 $m$，新编号为 $m'$，那么给这个学校改变编号的成本即为 $k \times |m'-m|$。

现在你需要告诉国王完成编号更新的最低成本是多少，或者说明这是不可能的。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a_i \le m_i \le b_i \le n \le 200$，$1\le k_i \le 1000$。

## 样例 #1

### 输入

```
5
1 1 2 3
1 1 5 1
3 2 5 5
4 1 5 10
3 3 3 1```

### 输出

```
9```

# 题解

## 作者：银河AI (赞：2)

~~为什么题解里面都是跑网络流啊喂。~~

下面提供一种二分图完美匹配的思路。

### 解题思路

题目最后提到要求最低成本，那就相当于是要跑二分图最小权完美匹配（说白了就是负权边跑最大权）

加边的时候（用的是邻接矩阵），我们枚举能更新到的编号范围，然后加边。

加完边之后就再跑一个 KM 的板子就好了。

关于什么时候输出 `NIE`：

只需在更新 $del$ 的时候判断 $del$ 是否还是 $\infty$ 就好了。

如果还是 $\infty$ ，那么就输出 `NIE`。

具体看代码理解，这里跑的是 dfs 版的 KM。

### AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e2+1,inf=1e9+1;
int n;
int a[N],b[N];
int last[N],k[N]; 
int goal[N],slack[N];
struct edge{
	int to,ne,dis;
}e[N*N];
int adj[N],l;
inline void add(int x,int y,int z){e[++l].to=y,e[l].ne=adj[x],e[l].dis=z,adj[x]=l;}
int col[N],vis[N],mat[N];
int nn;
int flag=0;
int ans[N],sum;
int dfs(int x){
	vis[x]=1;
	for(register int i=adj[x];i;i=e[i].ne){
		int y=e[i].to,z=e[i].dis;
		if(vis[y]) continue;
		int dist=goal[x]+goal[y]-z;
		if(dist==0){
			vis[y]=1;
			if(!mat[y]||dfs(mat[y])){
				if(mat[y]) sum-=ans[y];
				ans[y]=z;
				sum+=z;
				mat[y]=x;
				return 1;
			} 
		}
		else slack[y]=min(slack[y],dist);
	}
	return 0;
}
inline int KM(){
	for(register int x=1;x<=n;x++){
		for(int i=adj[x];i;i=e[i].ne){
			int y=e[i].to,z=e[i].dis;
			goal[x]=max(goal[x],z);
		}
	}
	for(register int i=1;i<=n;i++){
		memset(slack,inf,sizeof(slack));
		while(1){
			memset(vis,0,sizeof(vis));
			if(dfs(i)) break;
			int del=inf;
			for(register int j=n+1;j<=n+nn;j++) if(!vis[j]) del=min(del,slack[j]);
			if(del==inf) return inf;
			for(register int j=1;j<=n;j++) if(vis[j]) goal[j]-=del;
			for(register int j=n+1;j<=n+nn;j++){
				if(vis[j]) goal[j]+=del;
				else slack[j]-=del;
			} 
		}
	}
	return sum;
}
signed main(){
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&last[i],&a[i],&b[i],&k[i]);
		nn=max(nn,max(a[i],b[i]));
		for(register int j=a[i];j<=b[i];j++) add(i,j+n,-k[i]*abs(last[i]-j));
		goal[i]=-inf;
	}
	int anss=KM();
	if(anss==inf) printf("NIE");
	else printf("%lld",-anss);
}
```


---

## 作者：Priori_Incantatem (赞：2)

其实就是一个带权二分图匹配，建好图后直接跑一边最小费用最大流

最后如果最大流不为$n$，说明不是所有人都能找到合适的编号，输出`NIE`，否则输出最小费用

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=1000,Maxm=100000+20,inf=0x3f3f3f3f;
int nxt[Maxm],flow[Maxm],to[Maxm],cost[Maxm];
int head[Maxn],dis[Maxn],pre[Maxn],cur[Maxn];
int n,s,t,ans,tot,edgecnt=1;
bool vis[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void add(int x,int y,int len,int c)
{
	++edgecnt;
	nxt[edgecnt]=head[x];
	to[edgecnt]=y;
	flow[edgecnt]=len;
	cost[edgecnt]=c;
	head[x]=edgecnt;
}
bool spfa()
{
	memset(dis,inf,sizeof(dis));
	memset(cur,inf,sizeof(cur));
	queue <int> q;
	dis[s]=0,vis[s]=1,q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(!flow[i])continue;
			if(dis[y]>dis[x]+cost[i])
			{
				dis[y]=dis[x]+cost[i];
				pre[y]=i,cur[y]=min(cur[x],flow[i]);
				if(!vis[y])vis[y]=1,q.push(y);
			}
		}
	}
	if(dis[t]==inf)return 0;
	return 1;
}
void upd()
{
	int x=t;
	while(x!=s && x)
	{
		int i=pre[x];
		flow[i]-=cur[t];
		flow[i^1]+=cur[t];
		x=to[i^1];
	}
	ans+=cur[t];
	tot+=cur[t]*dis[t];
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	n=read();
	s=n*2+1,t=s+1;
	for(int i=1;i<=n;++i)
	{
		add(s,i,1,0);
		add(i,s,0,0);
		add(i+n,t,1,0);
		add(t,i+n,0,0);
	}
	for(int i=1;i<=n;++i)
	{
		int id=read(),l=read(),r=read(),k=read();
		for(int j=l;j<=r;++j)
		{
			int c=abs(id-j)*k;
			add(i,j+n,1,c);
			add(j+n,i,0,-c);
		}
	}
	while(spfa())upd();
	if(ans!=n)
	{
		puts("NIE");
		return 0;
	}
	printf("%d\n",tot);
	
	return 0;
}
```

---

## 作者：MeowScore (赞：1)

题意不再描述了。

每个学校有一个初始编号、一个改编后可以接受的编号范围，以及单位编号变化的代价。不难看出其实是一道带权二分图匹配问题，即学校去和编号匹配，直接上最小费用最大流。我们用一个超级源点向所有学校连边，容量是 $1$，费用是 $0$。每个学校向它能接受的所有编号连边，容量是 $1$，费用就是编号变化量乘以单位变化的代价。再把所有编号向超级汇点连边，容量为 $1$，费用为 $0$。学校用点 $1$ 到 $n$ 表示，编号 $i$ 用点 $n+i$ 表示。源点为 $0$，汇点为 $n+n+1$。

最小费用是在最大流量的前提下的。本题如果最大流计算出来等于 $n$，那说明所有学校都匹配到了编号，此时的最小费用便是答案。如果最大流不是 $n$，那么判定为无解。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,s,t;
int p[250],a[250],b[250],k[250];
const int N=200010,INF=500000000;
int head[N],to[N*2],nex[N*2],e[N*2],cnt,f[N*2];
void addE(int x,int y,int z,int w){
	cnt++;
	e[cnt]=z;
	f[cnt]=w;
	to[cnt]=y;
	nex[cnt]=head[x];
	head[x]=cnt;
}
void add(int x,int y,int z,int w){
	addE(x,y,z,w);
	addE(y,x,0,-w);
}
int d[N],pre[N],r[N];
bool v[N];
bool spfa(){
	queue<int> q;
	q.push(s);
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	v[s]=1;
	d[s]=0;
	r[s]=INF;
	while(q.size()){
		int x=q.front();
		q.pop();
		v[x]=0;
		for(int i=head[x];i;i=nex[i]){
			int y=to[i];
			if(e[i]&&d[y]>d[x]+f[i]){
				d[y]=d[x]+f[i];
				pre[y]=i;
				r[y]=min(r[x],e[i]);
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
	}
	if(d[t]!=d[t+1])
		return 1;
	return 0;
}
int ans,maxflow;
void update(){
	int x=t;
	while(x!=s){
		e[pre[x]]-=r[t];
		e[pre[x]^1]+=r[t];
		x=to[pre[x]^1];
	}
	ans+=r[t]*d[t];
	maxflow+=r[t];
}
void EK(){
	while(spfa())
		update();
}
int main(){
	cnt=1;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i]>>a[i]>>b[i]>>k[i];
	s=0;
	t=n+n+1;
	for(int i=1;i<=n;i++){
		add(s,i,1,0);
		for(int j=a[i];j<=b[i];j++)
			add(i,n+j,1,k[i]*abs(p[i]-j));
	}
	for(int i=1;i<=n;i++)
		add(i+n,t,1,0);
	EK();
	if(maxflow!=n)
		cout<<"NIE";
	else
		cout<<ans;
	return 0;
}
```

---

## 作者：Su_Zipei (赞：1)

第一眼看上去好像并不是很可做但是看了数据范围后就不难发现这是一个网络流问题。

要判断是否合法和费用最小，那么可以使用最小费用最大流，并不知道为什么有最小割的标签。

对于每个**学校**，注意是**学校**而不是编号，向它能够转移的编号连边，流量大小为1，费用为代价，然后原点向学校连边，流量大小为1，费用为0,每个编号向汇点连边，流量大小为1,费用为0,然后就是模板了。

把学校转化成编号，这样做不合法理由是有可能会让某个学校用了别的学校的费用，比如
```
3
1 1 3 1
1 1 3 2
1 1 3 3
```
这组数据。

所以应该是用学校作为一个点。

```
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=410;
struct Edge{
	int to,nxt,val,cost;
}e[N*N];
int h[N],idx=1;
void Ins(int a,int b,int c,int d){
	e[++idx].to=b;e[idx].nxt=h[a];
	h[a]=idx;e[idx].val=c;e[idx].cost=d;
}
int st,ed,cnt,mp[N],dis[N],pre[N];
bool inq[N];
deque<int> q;
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[st]=0;q.push_back(st);
	while(!q.empty()){
		int u=q.front();q.pop_front();inq[u]=0;
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].cost&&e[i].val){
				dis[v]=dis[u]+e[i].cost;
				pre[v]=i;
				if(!inq[v]){
					if(q.empty()||dis[v]<=dis[q.front()])q.push_front(v);
					else q.push_back(v);
					inq[v]=1;
				}
			}
		}
	}
	return dis[ed]!=0x3f3f3f3f;
}
int main(){
	int n;
	scanf("%d",&n);
	st=++cnt;ed=++cnt;
	for(int i=1;i<=n;i++){
		mp[i]=++cnt;
		Ins(cnt,ed,1,0);Ins(ed,cnt,0,0);
	}
	for(int i=1;i<=n;i++){
		int lst,a,b,k;
		scanf("%d%d%d%d",&lst,&a,&b,&k);
		++cnt;
		Ins(st,cnt,1,0);Ins(cnt,st,0,0);
		for(int j=a;j<=b;j++){
			int w=abs(j-lst)*k;
			Ins(cnt,mp[j],1,w);
			Ins(mp[j],cnt,0,-w);
		}
	}
	int res1=0,res2=0;
	while(spfa()){
		int Min=1e9;
		for(int now=ed;now!=st;now=e[pre[now]^1].to)
			Min=min(Min,e[pre[now]].val);
		for(int now=ed;now!=st;now=e[pre[now]^1].to){
			e[pre[now]].val-=Min;
			e[pre[now]^1].val+=Min;
		}
		res1+=Min;
		res2+=Min*dis[ed];
	}
	if(res1!=n)puts("NIE");
	else printf("%d\n",res2);
	return 0;
}

```


---

## 作者：oscar (赞：1)

【POI补全计划#24 POI2006 SZK】

没什么可说的，又是标准的费用流（看数据范围都知道）

建图分三部分：

1.源点S->学校i，容量1，费用0

2.学校i->可接受编号j，容量1，费用 $ | m_i - j | \times t_i $，其中 $ a_i \leq j \leq b_i $ 
3.编号i->汇点T

然后再这个图上跑最小费用最大流即可

贴代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=510,S=501,T=502,SHIFT=250;
struct edge
{
    int v,f,len;
    edge *next,*rev;
}*h[MAXN],pool[MAXN*MAXN*2];
int top;
inline void addedge(int u,int v,int c,int w)
{
    edge *tmp=&pool[++top];tmp->v=v;tmp->f=c;tmp->len=w;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[++top];pmt->v=u;pmt->f=0;pmt->len=-w;pmt->next=h[v];h[v]=pmt;
    tmp->rev=pmt;pmt->rev=tmp;
}
int totf,totc;
queue<int> q;
int inq[MAXN],dis[MAXN],last[MAXN];
edge *laste[MAXN];
inline int spfa()
{
    while(!q.empty())q.pop();
    memset(dis,0x3f,sizeof(dis));
    memset(last,0,sizeof(last));
    memset(laste,0,sizeof(laste));
    dis[S]=0;inq[S]=1;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=0;
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(tmp->f&&dis[tmp->v]>dis[u]+tmp->len)
            {
                dis[tmp->v]=dis[u]+tmp->len;
                last[tmp->v]=u;
                laste[tmp->v]=tmp;
                if(!inq[tmp->v])
                {
                    inq[tmp->v]=1;
                    q.push(tmp->v);
                }
            }
        }
    }
    if(dis[T]==0x3f3f3f3f)return -1;
    int cur=T;
    while(cur!=S)
    {
        laste[cur]->f--;laste[cur]->rev->f++;
        cur=last[cur];
    }
    return dis[T];
}
int main()
{
    int n;
    scanf("%d",&n);
    int m,l,r,t;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&m,&l,&r,&t);
        addedge(S,i,1,0);
        for(int j=l;j<=r;j++)
        {
            addedge(i,j+SHIFT,1,abs(m-j)*t);
        }
        addedge(i+SHIFT,T,1,0);
    }
    int tmp;
    while((tmp=spfa())!=-1)
    {
        totf++;
        totc+=tmp;
    }
    if(totf==n)printf("%d\n",totc);
    else printf("NIE\n");
    return 0;
}
```

---

## 作者：miaokehao (赞：1)

直接建边，以0为超级源，以1+2*n为超级汇
直接跑最小费用最大流即可
提醒一下：下方题解不能直接抄
```
#include <bits/stdc++.h>
#define res register int
#define inf 0x3f3f3f3f
#define N 20001
#define M 8000000
using namespace std;
int d[N],pre[N],dis[N],flow[N],per[N],n,m,a,b,cc,tot=1,ans,maxflow,vis[N];
struct papa{
    int w,c,next,to;
}e[M];
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void add(int x,int y,int we,int cost){
    e[++tot].next=d[x];
    d[x]=tot;
    e[tot].w=we;
    e[tot].c=cost;
    e[tot].to=y;
}
inline bool spfa(int s,int t){
    memset(dis,inf,sizeof(dis));
    memset(vis,0,sizeof(vis));
    queue<int> l;
    dis[s]=0;
    vis[s]=1;
    flow[s]=inf;
    l.push(s);
    while(!l.empty()){
        int now=l.front();
        vis[now]=0;
        l.pop();
        for(res i=d[now];i;i=e[i].next)
          if(e[i].w&&dis[e[i].to]>dis[now]+e[i].c){
          	dis[e[i].to]=dis[now]+e[i].c;
          	flow[e[i].to]=min(flow[now],e[i].w);
          	pre[e[i].to]=i;
          	if(!vis[e[i].to]){
          		l.push(e[i].to);
          		vis[e[i].to]=1;
              }
          }
    }
    return dis[t]!=inf;
}
inline void updata(int s,int t){
    int x=t;
    while(x!=s){
        int i=pre[x];
        e[i].w-=flow[t];
        e[i^1].w+=flow[t];
        x=e[i^1].to;
    }
    maxflow+=flow[t];
    ans+=dis[t]*flow[t];
}
inline void EK(int s,int t){
    while(spfa(s,t))
      updata(s,t);
}
int main(){
    //n=read();
    for(res i=1;i<=n;i++){
        add(0,i,1,0);
        add(i,0,0,0);
    }
    for(res i=1;i<=n;i++){
        m=read(),a=read(),b=read(),cc=read();
        for(res j=a;j<=b;j++)
          add(i,n+j,1,abs(j-m)*cc),add(n+j,i,0,-abs(j-m)*cc);
    }
    for(res i=1;i<=n;i++)
      add(i+n,1+(n<<1),1,0),add(1+(n<<1),i+n,0,0);
    EK(0,1+(n<<1));
    if(maxflow==n)
      printf("%d\n",ans);
    else
      printf("NIE\n");
}
```

---

## 作者：Foreverxxx (赞：0)

### 前言

前面的题解只有一篇是用 KM 算法的，本人在此提供另一种做法。

### 思路

首先明确本题是求一个二分图最大权完美匹配，于是考虑使用 KM 算法求解（最小费用最大流也可以完成）。如果还不会 KM 算法，请右转 [P6577 【模板】二分图最大权完美匹配](https://www.luogu.com.cn/problem/P6577) 进行学习。

首先明确题意，是求二分图最大匹配中最小权匹配，我们可以考虑将原问题其变为，将所有的边权变为它的相反数后，原图的最大权完美匹配。

对于有解的情况，直接跑一次 KM 算法的模板就可以了，但是我们应该如何判定无解？

第一种思路是借鉴的 @[银河AI](https://www.luogu.com.cn/user/209808) 的思路，在 DFS 后判断 $delta$ 值是否还是无限，如果是则说明节点 $i$ 找不到可行的增广路，直接返回无解即可。具体代码请见 [题解 P3440 POI2006 SZK-Schools](https://www.luogu.com.cn/blog/AIAKIOI/solution-p3440)（这比求最小费用最大流快得多，不过把 KM 算法用 BFS 写可能会更快）。

现在说一说我的思路。对于无解的情况，一定是会有一个点找不到增广路的，那么我们可以在进行 KM 算法求解之前先进行一次匈牙利算法（如果用的是 ``Dinic`` 算法就不需要考虑了），看能否给每个点找到增广路，如果可以则进行 KM 算法，如果不行则输出 ``NIE``。

不过现在涉及到一个问题，题目中总的边数最大可以达到 $n^2$ 条，进行匈牙利算法时，会枚举每个点，在寻找每个点的增广路时，时间复杂度的上界可以达到 $O(nm)$，在本题中即为 $O(n^3)$，则总的时间复杂度就会达到 $O(n^4)$，难道不会超时吗？

答案是不会，因为我们必须构造出来可能把所有边都枚举一次才能找到增广路的图，按照题目中的建图方式是无法构造出来的，匈牙利算法的时间在此只能达到 $O(n^3)$ 左右，不需要担心超时的问题。

（PS：哪位大佬构造出数据卡掉了匈牙利算法麻烦评论或者私信指出，谢谢！当然这种情况直接把匈牙利算法换成 HK 算法或者 Dinic 算法就好了。）

AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sss=0,www=1;
	char chh=getchar();
	while(chh<'0'||chh>'9'){
		if(chh=='-') www=-1;
		chh=getchar();
	}
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss*www;
}
int n;
long long delta;
long long edge[205][205];
int matched[405];
bool vis[405],visx[205],visy[205];
long long lx[205],ly[205];
int head[40005],to[40005],nxt[40005],tot=0;
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
bool find(int now){
	for(register int i=head[now];i;i=nxt[i]){
		int u=to[i];
		if(!vis[u]){
			vis[u]=true;
			if(!matched[u]||find(matched[u])){
				matched[u]=now;
				return true;
			}
		}
	}
	return false;
}
bool check(){
	for(register int i=1;i<=n;i++){
		memset(vis,false,sizeof vis);
		if(!find(i)) return false;//找不到增广路返回无解
	}
	return true;
}
bool dfs(int now){
	visx[now]=true;
	for(register int i=1;i<=n;i++){
        if(!visy[i]){
            if(lx[now]+ly[i]==edge[now][i]){
                visy[i]=true;
                if(!matched[i]||dfs(matched[i])){
                    matched[i]=now;
                    return true;
                }
            }
            else delta=min(delta,lx[now]+ly[i]-edge[now][i]);
        }
    }
    return false;
}
long long KM(){
	memset(lx,0x3f,sizeof lx);
	for(register int i=1;i<=n;i++){
		while(true){
			memset(visx,false,sizeof visx);
			memset(visy,false,sizeof visy);
			delta=1e18;
			if(dfs(i)) break;
			for(register int j=1;j<=n;j++){
				if(visy[j]) ly[j]+=delta;
				if(visx[j]) lx[j]-=delta;
			}
		}
	}
	long long ans=0;
	for(register int i=1;i<=n;i++)
		ans-=edge[matched[i]][i];
	return ans;
}
int main(){
	n=read();
	int m,a,b,k;
	memset(edge,-0x3f,sizeof edge);
	for(register int i=1;i<=n;i++){
		m=read(),a=read(),b=read(),k=read();
		for(register int j=a;j<=b;j++){
			add(i,j+n);
			edge[i][j]=-k*abs(m-j);
		}
	}
	if(!check()){
		puts("NIE");
		return 0;
	}
	memset(matched,0,sizeof matched);
	printf("%lld\n",KM());
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

对于这样的匹配类问题，往往要想到建立网络流的模型来解决。

我们将学校放到左边，每个新编号放到右边，将学校与其所有接受的新编号之间连一条流量为 $1$ 的边，费用为改编号的开销。

从超级源点向左边所有点连一条流量为 $1$，费用为 $0$ 的边；从超级汇点向右边所有点连一条流量为 $1$，费用为 $0$ 的边（要确保每个编号恰好被选一次），跑最小费用最大流即可。

如果最大流不到 $n$ 则无解，否则求出的最小费用即为答案。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct graph
{
 #define INF 0x3f3f3f3f
 struct edge
 {
  int v,w,c,next;
 }e[100005];
 struct node
 {
  int v,e;
 }p[10005];
 int head[505],dist[505],vis[505],s,t,cnt;
 void addedge(int u,int v,int w,int c)
 {
  e[++cnt].v=v;
  e[cnt].w=w;
  e[cnt].c=c;
  e[cnt].next=head[u];
  head[u]=cnt;
 }
 void init(int S,int T,int n)
 {
  s=S,t=T;
  cnt=1;
  for(int i=1;i<=n;i++)
  {
   addedge(s,i,1,0);
   addedge(i,s,0,0);
   addedge(i+n,t,1,0);
   addedge(t,i+n,0,0);
  }
 }
 bool spfa()
 {
  queue<int> q;
  memset(dist,INF,sizeof(dist));
  q.push(s);
  dist[s]=0;
  vis[s]=1;
  while(!q.empty())
  {
   int cur=q.front();
   q.pop();
   vis[cur]=0;
   for(int i=head[cur];i;i=e[i].next)
    if(e[i].w&&dist[cur]+e[i].c<dist[e[i].v])
    {
     dist[e[i].v]=dist[cur]+e[i].c;
     p[e[i].v].v=cur;
     p[e[i].v].e=i;
     if(!vis[e[i].v])
     {
      vis[e[i].v]=1;
      q.push(e[i].v);
     }
    }
  }
  return dist[t]!=INF;
 }
 pair<int,int> mcmf()
 {
  int maxw=0,minf=0;
  while(spfa())
  {
   int minw=INF;
   for(int i=t;i!=s;i=p[i].v)
    minw=min(minw,e[p[i].e].w);
   for(int i=t;i!=s;i=p[i].v)
   {
    e[p[i].e].w-=minw;
    e[p[i].e^1].w+=minw;
   }
   maxw+=minw;
   minf+=minw*dist[t];
  }
  return make_pair(maxw,minf);
 }
}g;
int main()
{
 int n;
 scanf("%d",&n);
 g.init(2*n+1,2*n+2,n);
 for(int i=1;i<=n;i++)
 {
  int m,a,b,k;
  scanf("%d%d%d%d",&m,&a,&b,&k);
  for(int j=a;j<=b;j++)
  {
   int c=abs(m-j)*k;
   g.addedge(i,j+n,1,c);
   g.addedge(j+n,i,0,-c);
  }
 }
 auto ans=g.mcmf();
 if(ans.first!=n)puts("NIE");
 else printf("%d\n",ans.second);
 return 0;
}
```


---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[题目链接](https://www.luogu.org/problem/P3440).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一道有趣的最小费用流问题. 我们尝试把原问题抽象为图:  
![P3340_1.png](https://cdn.luogu.com.cn/upload/pic/74941.png).  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于从超级源点出发的边, 花费为$0$, 容量为$1$; 对于学校和编号之间的边$<u,v>$, 花费为$k_u|m_u-v|$, 容量为$1$; 对于连向超级汇点的边, 花费为$0$, 容量为$1$, 跑一边最小费用流. 若到达汇点的流量不足$n$, 证明无解, 否则输出最小费用.
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <utility>

#define Int register int

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 200, MAXNODE = 2 * MAXN + 2;
int n, Cnte = 1, Head[MAXNODE + 5] = {}, Dist[MAXNODE + 5] = {}, S, T;
bool Vis[MAXNODE + 5] = {};
pii Path[MAXNODE + 5] = {};
queue<int> Q;

struct Edge {
	int To, Cost, Flow, _nxt;
} Graph[2 * ( MAXN * MAXN + 2 * MAXN ) + 5] = {};

inline int Abs ( const int x ) {
	return x < 0 ? -x : x;
}

inline void Link ( const int From, const int To, const int Cost, const int Flow ) {
	Graph[++ Cnte] = { To, Cost, Flow, Head[From] };
	Head[From] = Cnte;
}

inline bool SPFA () {
	memset ( Vis, false, sizeof Vis );
	memset ( Path, 0, sizeof Path );
	memset ( Dist, 0x3f, sizeof Dist );
	Vis[S] = true, Q.push ( S ), Dist[S] = 0;
	while ( ! Q.empty () ) {
		int u = Q.front (); Q.pop ();
		Vis[u] = false;
		for ( Int i = Head[u], v, w; i; i = Graph[i]._nxt ) {
			w = Graph[i].Cost;
			if ( Graph[i].Flow > 0 && Dist[v = Graph[i].To] > Dist[u] + w ) {
				Dist[v] = Dist[u] + w, Path[v] = { u, i };
				if ( ! Vis[v] ) {
					Q.push ( v );
					Vis[v] = true;
				}
			}
		}
	}
	return Dist[T] ^ 0x3f3f3f3f;
}

inline pii EK () {
	pii ret ( 0, 0 );
	for ( ; SPFA (); ) {
		int MinFlow = 0x7fffffff;
		for ( Int i = T; i ^ S; i = Path[i].first ) {
			MinFlow = min ( MinFlow, Graph[Path[i].second].Flow );
		}
		for ( Int i = T; i ^ S; i = Path[i].first ) {
			Graph[Path[i].second].Flow -= MinFlow;
			Graph[Path[i].second ^ 1].Flow += MinFlow;
		}
		ret.first += MinFlow, ret.second += MinFlow * Dist[T];
	}
	return ret;
}

inline void Work () {
	scanf ( "%d", &n );
	S = 1, T = 2 * n + 2;
	// 1: SuperSource   2~n+1: School   n+2~2*n+1: Index    2*n+2: SuperSink
	for ( Int i = 1, m, a, b, k; i <= n; ++ i ) {
		scanf ( "%d %d %d %d", &m, &a, &b, &k );
		Link ( S, i + 1, 0, 1 ), Link ( i + 1, S, 0, 0 );
		for ( Int j = a; j <= b; ++ j ) {
			Link ( i + 1, 1 + n + j, Abs ( j - m ) * k, 1 );
			Link ( 1 + n + j, i + 1, -Abs ( j - m ) * k, 0 );
		}
	}
	for ( Int i = 1; i <= n; ++ i ) {
		Link ( 1 + n + i, T, 0, 1 );
		Link ( T, 1 + n + i, 0, 0 );
	}
	pii Ans = EK ();
	if ( Ans.first < n ) {
		puts ( "NIE" );
	} else {
		printf ( "%d\n", Ans.second );
	}
}

int main () {
	Work ();
	return 0;
}
```

---

