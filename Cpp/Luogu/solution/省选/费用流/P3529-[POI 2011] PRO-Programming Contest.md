# [POI 2011] PRO-Programming Contest

## 题目描述

**译自 POI 2011 Round 3. Day 2. C「[Programming Contest](https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement)」**

Bartie 和他的朋友们都在打团体程序设计竞赛。每个队有 $n$ 名队员，每个队可以用 $n$ 台电脑。比赛持续 $t$ 分钟，比赛中选手们要解决 $m$ 道程序设计题目。此外，比赛会按如下规则记罚时：比赛开始 $s$ 分钟通过了一道题，则罚时加 $s$ 分。解题数目最多的队伍获胜，如果解题数目相同，罚时最少的队伍获胜。

在一次比赛中，Bartie 迅速浏览了全部题目并且把题目分配给了队友。他十分了解队友，并可以把题目分配给能解决这道题的人。对于每个选手，解决一道题的时间都恰好是 $r$ 分钟。

Bartie 的队伍在今年的比赛中表现不佳。Bartie 确信这是他的问题，是由于他分配问题失误造成的。他想让你写个程序，给出 Bartie 在比赛前知道的信息，请求出 Bartie 的队伍可能的最好成绩和分配题目的方式。

## 说明/提示

对于全部数据，$ 1 \le n, m \le 500 , 1 \le r, t \le 1000000, 1 \le a \le n , 1 \le b \le m $

对于 $30\%$ 的分数，$n,m\le 100$。

翻译来自于 [LibreOJ](https://loj.ac/p/2171)。

## 样例 #1

### 输入

```
2 4 3 15 4
1 1
2 3
1 4
1 3```

### 输出

```
3 12
1 4 0
2 3 0
1 1 3```

# 题解

## 作者：C_S_X_ (赞：7)

**最大流**

（罚时：每道题被完成的 **时间点** 之和）

先不看罚时最小的要求，只考虑做题数量最多，可以像这样建图：

1 每个人连向自己会做的题，由于一个人只会做一道题一次，所以容量为1

2 每道题连向汇点，由于一道题只需要被做一次，所以容量为1

3 源点连向每个人，由于每个人最多的做题数为t/r，所以容量填t/r

最大流就是最大做题数

**再考虑罚时最小**，就是要求从比赛开始，要尽可能更多人在做题，上面这种建图的缺陷在于可能一个人包揽了很多题，导致罚时很大（~~明明他可以让别人做一些~~）导致这种为题就在于源点向人连的边容量过大，一开始允许他做很多题。

所以可以动态加边，每次加一组源点到人的容量为1的边，慢慢开放他们做题的权限，防止一个人疯狂做题，直到某一次即使加边他们也做不出更多的题目，目前的流量图就是一个合法的方案。

输出方案：对于每条人到题目正向边，如果被流满则这个人做了这道题。

```cpp
#include<bits/stdc++.h>
#define N 500000
#define inf 1000000007
using namespace std;
int n,m,r,t,k,first[N],nxt[N],tot=1,S,T;
int in1[N],in2[N],depth[N],maxflow=0,flow,max_num,last=0,ans=0;
int ans1[N],ans2[N],ans3[N],tpp=0,p[N]={0};
queue <int> q;
struct Edge
{
    int u,v,flow;
}edge[N];
void Add(int u,int v,int flow)
{
    tot++;
    nxt[tot]=first[u];
    first[u]=tot;
    edge[tot]=(Edge){u,v,flow};
    return;
}
void Addedge(int u,int v,int flow)
{
    Add(u,v,flow);
    Add(v,u,0);
    return;
}
int bfs()
{
    memset(depth,0,sizeof(depth));
    while (q.size()) q.pop();
    depth[S]=1;
    q.push(S);
    while (q.size())
    {
        int tmp=q.front();
        q.pop();
        for (int j=first[tmp];j!=-1;j=nxt[j])
            if (edge[j].flow&&!depth[edge[j].v])
            {
            	int to=edge[j].v;
            	depth[to]=depth[tmp]+1;
            	q.push(to);
            }
    }
    if (depth[T]) return 1;
    else return 0;
}
int Dinic(int p,int f)
{
    if (p==T) return f;
    int k,rest=f;
    for (int j=first[p];j!=-1&&rest;j=nxt[j])
         if (edge[j].flow&&depth[edge[j].v]==depth[p]+1)
         {
         	int to=edge[j].v;
         	k=Dinic(to,min(rest,edge[j].flow));
         	if (!k) 
         	{
         		depth[to]=0;
         		continue;
         	}
         	edge[j].flow-=k;
         	edge[j^1].flow+=k;
         	rest-=k;
         }
    return f-rest;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
    memset(first,-1,sizeof(first));
    scanf("%d%d%d%d%d",&n,&m,&r,&t,&k);
    S=n+m+1;
    T=n+m+2;
    for (int i=1;i<=k;i++) scanf("%d%d",&in1[i],&in2[i]);
    for (int i=1;i<=k;i++) Addedge(in1[i],in2[i]+n,1);
    for (int i=n+1;i<=n+m;i++) Addedge(i,T,1);
    max_num=t/r;
    for (int i=1;i<=max_num;i++)
    {
        for (int i=1;i<=n;i++) Addedge(S,i,1);
        while (bfs())
            while ((flow=Dinic(S,inf))) maxflow+=flow;
        if (maxflow==last) break;
        last=maxflow;
    }
    for (int i=2;i<=tot;i+=2)
    {
        int p1=edge[i].u,p2=edge[i].v;
        if (edge[i].flow==0&&p1!=S&&p2!=T&&i%2==0)
        {
        	tpp++;
        	ans1[tpp]=p1;
        	ans2[tpp]=p2-n;
        	ans3[tpp]=p[p1]*r;
        	p[p1]++;
        	ans+=ans3[tpp]+r;
        }
    }
    printf("%d %d\n",maxflow,ans);
    for (int i=1;i<=tpp;i++) printf("%d %d %d\n",ans1[i],ans2[i],ans3[i]);
//	for (int i=2;i<=tot;i+=2) printf("%d %d %d\n",edge[i].u,edge[i].v,edge[i].flow);
    return 0;
}
```

---

## 作者：Needna (赞：4)

**P3529 [POI 2011] PRO-Programming Contest解题报告**

### 题目分析：
有 $n$ 个人 $m$ 个任务，每个人完成一道题用 $r$ 时，比赛时间为  $t$ ，有 $k$ 对完成人物的关系。要在规定时间 $t$ 内，在解题最多的情况下，罚时最少。

为了使罚时最少，我们会让题目尽量在前面跑，而且一个人跑的次数小于等于  $\left \lfloor \frac{t}{r}  \right \rfloor $  ,所以可以用二分图匹配完成。

### 具体做法：
跑 $\left \lfloor \frac{t}{r}  \right \rfloor $  次二分图最大匹配，保证一个人最多做 $\left \lfloor \frac{t}{r}  \right \rfloor $  道题，并且由于二分图匹配每个人都进行了多次，使得一个人不会做太多道题。不仅如此，二分图最大匹配还保证了解题数最多，所以叫为完美的解决了这道题目。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m,vis[N],ma[N],ans=0,r,t,k,ans1,ans2,ti[N];
vector<int> ve[N];
int dfs(int x){//二分图最大匹配模板 不解释 
	for(int v:ve[x]){
		if(vis[v]) continue;
		vis[v]=1;
		if(!ma[v]||dfs(ma[v])){
			ma[v]=x;
			return 1;
		}
	}
	return 0;
}
int main(){
    cin>>n>>m>>r>>t>>k;//直接抄不会过 
    for(int i=1,x,y;i<=k;i++){
    	cin>>x>>y;ve[x].emplace_back(y);//人连题 
	}
	for(int i=1,flg=0;i*r<=t;i++){//跑t/r遍最大匹配 
		for(int j=1;j<=n;j++){
		    memset(vis,0,sizeof(vis));
		    	if (dfs(j)){
                ans1++; 
                ans2+=i*r;
                flg=1;
			}
	    }if(!flg||ans1>=m) break;//剪枝 
	}
	cout<<ans1<<" "<<ans2<<'\n';
	for(int i=1;i<=m;i++){
		if(ma[i])cout<<ma[i]<<" "<<i<<" "<<(ti[ma[i]]++)*r<<'\n';//时间分配 
	}
	return 0;
}
```

---

## 作者：bssmessi (赞：2)

对于这个题,我们首先想到的是:

将源点向选手连边,容量为 $\left \lfloor \frac{t}{r}  \right \rfloor $ ,表示所给时间内能做的最多题.

选手再向会做的题目连边,容量为 $1$ ,表示一个题就做一遍.

题目最后向汇点连边,容量为 $1$ ,表示一个题最多只会被做一遍.

建边后我们跑一遍最大流求出答案.

但是我们发现这种做法并没有考虑到罚时的问题,并不能保证罚时最短,会出现一个人做很多道题导致罚时过多的情况.

所以我们可以考虑逐渐增加源点向选手连边的容量大小,保证一个选手先做一个题,再逐渐增加,这样子罚时肯定最少.若增加选手可做的题数最大流却没有增加就停止.

对于如何输出后面的答案,我们只需要把所有选手和题目的连边跑一遍,如果流量被用完,那就是这个题目被这个选手做了.
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=7e5+10;
struct node{
	int u,v,w,nxt;
}g[N];
int head[N],cur[N],dis[N],a1[N],a2[N],a3[N],num[N];//a1,a2,a3记录3个答案值,num表示每个人做的题数 
int n,m,s=0,t=1e4,r,ti,k,idx=1;//idx初始化为1,从2开始(使得i^1刚好能与i配对) 
void add(int u,int v,int w){
	g[++idx]={u,v,w,head[u]};head[u]=idx;
	g[++idx]={v,u,0,head[v]};head[v]=idx;//反向建边 
}
bool bfs(){//寻找增广路 
	memset(dis,0,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop(); 
		for(int i=head[u];i;i=g[i].nxt){
			int v=g[i].v;
			if(dis[v]==0&&g[i].w){
				dis[v]=dis[u]+1;
				q.push(v);
				if(v==t) return 1;
			}
		}
	} 
	return 0;
}
int dfs(int u,int mf){//多路增广 
	if(u==t) return mf;
	int sum=0;
	for(int &i=cur[u];i;i=g[i].nxt){//当前弧优化 
		int v=g[i].v;
		if(dis[v]==dis[u]+1&&g[i].w){
			int f=dfs(v,min(mf,g[i].w));
			g[i].w-=f;
			g[i^1].w+=f;
			sum+=f;//累加流出流量 
			mf-=f;//减少流量剩余 
			if(mf==0) break;//如果没流量了就停止 
		}
	}
	if(sum==0) dis[u]=0;//残枝优化，删点 
	return sum;
}
int dinic(){//将可行流累加 
	int ans=0;
	while(bfs()){
		memcpy(cur,head,sizeof(head));
		ans+=dfs(s,1e9);//初始可行流流量为无穷大 
	}
	return ans;
}
signed main(){
	cin>>n>>m>>r>>ti>>k;
	for(int i=1;i<=m;i++){
		add(1000+i,t,1);
	}
	for(int i=1;i<=k;i++){
		int a,b;cin>>a>>b;
		add(a,1000+b,1);
	}
	int last=0,now=0;
	for(int i=1;i<=ti/r;i++){
		for(int j=1;j<=n;j++) add(s,j,1);
		now+=dinic();//将流累加 
		if(now==last) break;
		last=now;
	}
	int tot=0,ans=0;
	for(int i=2;i<=idx;i+=2){//寻找流量用完的边，表示这个题他做了 
		int u=g[i].u,v=g[i].v;
		if(u!=s&&v!=t&&g[i].w==0){//排除不是选手和题目之间的连边
			a1[++tot]=u;a2[tot]=v-1000;a3[tot]=num[u]++*r;;ans+=a3[tot]+r;
		}
	}
	cout<<now<<" "<<ans<<"\n";
	for(int i=1;i<=tot;i++){
		cout<<a1[i]<<" "<<a2[i]<<" "<<a3[i]<<"\n";
	}
    return 0;
}

```

---

## 作者：mqmhaaaa1 (赞：1)

感觉是比较考对网络流理解的水紫。

读题后，我们发现几个关键信息：

1. 一个选手最多可以做 $t/r$ 道题。

2. 贪心的想，一个选手所产生的每一个罚时都会是 $r$ 的整数倍，因为他做完一道题后会尽可能快的写下一道题。

所以很快会有一个想法，我们可以先求出最多做题数，再求答案。

# 求最多做题数

求最多做题数很简单，建图方法如下：

由源点 $S$ 向每个选手连容量为 $t/r$ 的边，因为一个选手最多做 $t/r$ 道题。

再由每个选手向 ta 会做的题连 $1$ 容量的边。

最后由每到题向汇点 $T$ 连容量为 $1$ 的边，因为每道题只能做一次。

# 求最少罚时

我们可以把比赛时间看作总共 $t/r$ 个时间点，每个时间点所有的选手就都可以做题，每两个时间点间隔为 $r$。

我们先把 $S$ 向选手的边都断掉。

我们可以从第一个时间点开始，枚举 $i$，每个时间点由 $S$ 向每个选手连一条容量为 $1$ 费用为 $r \times i$，表示这个时候选手由一道题的做题机会且做完题后罚时为 $r \times i$。

每次枚举跑一边最小费用最大流，当最大流等于最大做题数时，说明此时已经做完了可以做的最多的题，且时间最少。

# 输出方案

我的方法很好理解。

我们先检查每一条选手向题目的连边，如果这条边满流，就说明该选手做了这道题。对每个选手开个 vector，把 ta 们做的题先存起来。

之后枚举 $S$ 连向选手的每条边。如果一条边满流，说明这个选手在该边添加的时间点开始做一道题，我们从该选手的 vector 里弹出来一个 ta 做过的题，做这道题的时间点为 **该边费用 $-r$**（因为添加费用为 $r\times i$ 边的时间点对应时间为 $r\times (i-1)$）。

最后输出就行，看代码。


```cpp
#include<bits/stdc++.h>
#define ll long long
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
using namespace std;
const ll N=1e4+10,M=2e6+10,inf=0x7f7f7f7f;
ll to[M<<1],nxt[M<<1],w[M<<1],c[M<<1],bh[N],tot=1;
ll head[N],dis[N];
bool vis[N];
inline void add(ll u,ll v,ll flow,ll cost){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=flow;
	c[tot]=cost;
	bh[u]=tot;
//	cout<<u<<' '<<v<<' '<<flow<<'\n';
	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	c[tot]=-cost;
	bh[v]=tot;
}
ll s,t;
inline bool spaf(){
	for(ll i=0;i<=t;i++){
		vis[i]=0;head[i]=bh[i];
		dis[i]=inf;
	}
	queue<ll>q;
	vis[s]=1;dis[s]=0;
	q.push(s);
	while(q.size()){
		ll u=q.front();q.pop();
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&dis[u]+c[i]<dis[v]){
				dis[v]=dis[u]+c[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[t]!=inf;
}
ll ans,mxf;
ll dic(ll u,ll flow){
	vis[u]=1;
	if(u==t){
		mxf+=flow;
		return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&(!vis[v]||v==t)&&dis[v]==dis[u]+c[i]){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb;w[i^1]+=jb;
			zy+=jb;flow-=jb;
			ans+=jb*c[i];
			if(!flow)break;
		}
	}
	vis[u]=0;
	return zy;
}
ll n,m,r,tim,k;
struct edge{
	ll u,v;
}e[M];
//题目 i+n 
ll mxl;
void getmxf(){//求做题数 
	s=0;t=n+m+1;
	for(ll i=1;i<=k;i++){
		e[i].u=read(),e[i].v=read()+n;
		add(e[i].u,e[i].v,1,0);
	}
	for(ll i=1;i<=n;i++)add(s,i,tim/r,0);
	for(ll i=1;i<=m;i++)add(i+n,t,1,0);
	//因为是为了求最大流，直接把费用设为0跑就行 
	while(spaf()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inf);
		}
	}
	mxl=mxf;
	memset(bh,0,sizeof bh);
	tot=1;
	mxf=ans=0;
	//记得清空 
}
vector<ll>cz[N];
void getans(){//求最小罚时 
	s=0;t=n+m+1;
	ll now=0;
	for(ll i=1;i<=k;i++){
		add(e[i].u,e[i].v,1,0);
	}
	for(ll i=1;i<=m;i++)add(i+n,t,1,0);
	while(now<=tim&&mxf!=mxl){//枚举 
		now+=r;
		for(ll i=1;i<=n;i++){//直接加边就行，不用清空 
			add(s,i,1,now);
		}
		while(spaf()){
			vis[t]=1;
			while(vis[t]){
				memset(vis,0,sizeof vis);
				dic(s,inf);
			}
		}
	}
}

int main(){
	n=read();m=read();r=read();tim=read();k=read();
	getmxf(); 
	getans();
	cout<<mxl<<' '<<ans<<'\n';
	for(ll i=1;i<=n;i++){//枚举选手 
		ll u=i;
		for(ll j=bh[u];j;j=nxt[j]){
			ll v=to[j];
			if(v==s)continue;
			if(!w[j])cz[u].push_back(v-n);//做的题 
		} 
	}
	for(ll i=bh[s];i;i=nxt[i]){
		ll v=to[i];
		if(!w[i]){
			cout<<v<<' '<<cz[v].back()<<' '<<c[i]-r<<'\n';
			cz[v].pop_back();//记得弹出去 
		}
	}
	return 0;
}

```

---

## 作者：Soulist (赞：1)


首先可以建立费用流的模型，每个人拆边即可，$S\to i$ 依次为流量为 $1$，费用为 $r,2r,3r...$ 的边即可。边数为 $\frac{t}{r}\times n+nm$，无法通过。

注意到我们必然是先流 $r$ 的边再流 $2r,3r$ 的边，不妨从小到大枚举 $kr$，发现本质上是动态增流的二分图匹配问题，如果一个点之前没有流流量，那么本次他也不会流了，所以直接 匈牙利/dinic 可以做到优秀的 $\mathcal O(nm^2)/\mathcal O(nm\sqrt{n})$，如果连边的时候暴力就大概是 $\mathcal O(nm)$，但是不是复杂度瓶颈所以也没啥关系。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2000 + 5 ; 
const int M = 1e6 + 5 ; 
const int inf = 1e15 + 7 ; 
struct E {
	int next, to, w ; 
} e[M] ; 
int n, m, r, t, K, S, T, cnt, head[N] ;
int cur[N], dep[N], sum, Ans ;  
void add( int x, int y, int z ) {
	e[++ cnt] = (E){ head[x], y, z }, head[x] = cnt,
	e[++ cnt] = (E){ head[y], x, 0 }, head[y] = cnt ; 
}
queue<int> q ; 
bool bfs() {
	rep( i, S, T ) dep[i] = 0 ; q.push(S), dep[S] = 1 ;
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ; 
		Next( i, u ) {
			int v = e[i].to ; 
			if( e[i].w && !dep[v] ) 
			dep[v] = dep[u] + 1, q.push(v) ; 
		}
	} return dep[T] != 0 ; 
}
int dfs( int x, int dist ) {
	if( x == T || !dist ) return dist ; int flow = 0 ;
	for( re int &i = cur[x]; i; i = e[i].next ) {
		int v = e[i].to ; 
		if( e[i].w && dep[v] == dep[x] + 1 ) {
			int di = dfs( v, min(dist, e[i].w) ) ; 
			e[i].w -= di, e[i ^ 1].w += di, flow += di, dist -= di ; 
		}
	} return flow ; 
}
int dinic() {
	int ans = 0, di ;
	while( bfs() ) {
		rep( i, S, T ) cur[i] = head[i] ; 
		while(di = dfs(S, inf)) ans += di ; 
	} return ans ; 
}
signed main()
{
	n = gi(), m = gi(), r = gi(), t = gi(), K = gi(), cnt = 1 ; 
	int x, y, maxn = t / r ; S = 0, T = n + m + 1 ; 
	rep( i, 1, K ) x = gi(), y = gi(), add(x, y + n, 1) ; 
	rep( i, 1, m ) add( i + n, T, 1 ) ;
	int sum = 0, de = 0 ; 
	while( de < maxn ) {
		++ de ; 
		rep( i, 1, n ) add( S, i, 1 ) ;
		int f = dinic() ; if( f == 0 ) break ; 
		Ans += f * de, sum += f ; 
	}
	printf("%lld %lld\n", sum, Ans * r ) ;
	rep( x, 1, n ) {
		int de = 0 ; 
		Next( i, x ) {
			int v = e[i].to ; 
			if( !e[i].w && v != S ) printf("%lld %lld %lld\n", x, v - n, de * r ), ++ de ; 
		}
	}
	return 0 ;
}
```

---

## 作者：mulberror (赞：1)

$$\href{http://blog.chhokmah.top/index.php/archives/45/}{\Large\texttt{My blog}}$$

---

> 题目链接：[洛谷3529](https://www.luogu.org/problemnew/solution/P3529)

## 题目描述
现在有$n$个人，每一个人有一个电脑，然后一大堆题目，现在给出每一个人能够解出题目的对应关系，每一个人解出一道题目的时间是固定的$r$，现在有$t$总时间，并且我们按照$ACM$的计分方式来计算分数。

请你给出能够最大化题目的情况下，最小化罚时，并给出方案。
## Data Range
$n,m\leq 500,r,t\leq 1000000$
<!--more-->
## Solution
考虑二分图匹配，很显然的是我们要把题目往前面堆越好，这样可以保证罚时最少。

然后我们就首先枚举时间$nowt$表示当前的时间段，那么解出需要$r$的时间。

那么基于当前的时间我们就尽可能的满足二分图匹配，这个匹配是题目匹配人。**因为一个人可以做出多个题目，但是一个题目做掉就没有办法再做一次了。**

所以我们就用贪心的思路，按照最少的时间来贪心匹配即可。

时间复杂度为二分图匹配的复杂度。
## Code
```cpp
// ==================
// author : chhokmah
// website : http://blog.chhokmah.top/
// create time : 13/08/19 22:38
// ==================
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

#define REP(i, s, t) for (int i = (s); i <= (t); i ++) 
#define DOW(i, s, t) for (int i = (s); i >= (t); i --)

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define unordered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using unordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;

const int P = 1e9 + 7; // 998244353
const db pi = acos(-1);

template <typename T> void pls(T &x, T y) { x = x + y >= P ? x + y - P : x + y; }
template <typename T> T add(T x, T y) { return x + y >= P ? x + y - P : x + y; }
template <typename T> void dec(T &x, T y) { }
template <typename T> void module(T x) { return (x % P + P) % P; }
template <typename T> T mul(T x, T y) { return (ll) x * y - (ll) x * y / P * P; }

#define mp make_pair
#define pb push_back
#define fi first
#define se second 
#define pi acos(-1)

template <typename T> void chkmax(T &x, T y) { x = x > y ? x : y; }
template <typename T> void chkmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> T qpow(T x, T y) {
  T res = 1; 
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) res = mul(res, x);
  }
  return res;
}
ll inc(ll x, ll y) {
  ll res = 0;
  for (; y; y >>= 1, x = add(x, x)) {
    if (y & 1) pls(res, x);
  }
  return res;
}

namespace input {
  template <typename T> void read(T &x) {
    x = 0; T flg = 0; char ch = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') flg = 1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    if (flg) x *= -1;
  }
  template <typename T, typename... Tx> void read(T &x, Tx &...tx) {
    read(x); read(tx...); 
  }
}

using namespace input;

namespace output {
  void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
  void write(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
  void write(char ch) { putchar(ch); }
  void write(string s) { cout << s; }
  void write(ull x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
  void write(db x) { printf("%.9lf\n", x); }
  template <typename T, typename... Tx> void write(T x, Tx ...tx) {
    write(x); write(tx...); 
  }
  template <typename T, typename... Tx> void writeln(T x, Tx ...tx) {
    write(x); write(tx...); puts("");
  }
  template <typename T> void _dbg(T *a, int l, int r, string s_a = "") {
    if (s_a != "") cout << "array name : " << s_a << " -> "; printf("range [%d, %d] : ", l, r);
    for (int i = l; i <= r; i ++) cout << a[i] << " \n"[i == r];
  }
}

using namespace output;

const int N = 3005;
vector<int> g[N];
bool vis[N];
int match[N], now_time[N];
int n, m, r, t, k;
int dfs(int u) {
  for (auto v : g[u]) {
    if (vis[v]) continue;
    vis[v] = 1;
    if (match[v] == -1 || dfs(match[v])) {
      match[v] = u;
      return 1;
    }
  }
  return 0;
}
int main() {
  memset(match, -1, sizeof(match));
  read(n, m, r, t, k);
  for (int i = 1; i <= k; i ++) {
    int u, v; 
    read(u, v);
    g[u].emplace_back(v);
  }
  int ans1 = 0, ans2 = 0;
  for (int i = 1; i * r <= t; i ++) {
    bool flg = 0;
    for (int j = 1; j <= n; j ++) {
      memset(vis, 0, sizeof(vis));
      if (dfs(j)) {
        ans1 ++; 
        ans2 += i * r;
        flg = 1;
      }
    }
    if (!flg) break;
  }
  writeln(ans1, ' ', ans2);
  memset(now_time, 0, sizeof(now_time));
  for (int i = 1; i <= m; i ++) {
    if (match[i] == -1) continue;
    int u = match[i];
    writeln(u, ' ', i, ' ', now_time[u]);
    now_time[u] += r; 
  }
  return 0;
}
```

---

