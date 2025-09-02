# Almost Permutation

## 题目描述

Recently Ivan noticed an array $ a $ while debugging his code. Now Ivan can't remember this array, but the bug he was trying to fix didn't go away, so Ivan thinks that the data from this array might help him to reproduce the bug.

Ivan clearly remembers that there were $ n $ elements in the array, and each element was not less than $ 1 $ and not greater than $ n $ . Also he remembers $ q $ facts about the array. There are two types of facts that Ivan remembers:

- $ 1 $ $ l_{i} $ $ r_{i} $ $ v_{i} $ — for each $ x $ such that $ l_{i}<=x<=r_{i} $ $ a_{x}>=v_{i} $ ;
- $ 2 $ $ l_{i} $ $ r_{i} $ $ v_{i} $ — for each $ x $ such that $ l_{i}<=x<=r_{i} $ $ a_{x}<=v_{i} $ .

Also Ivan thinks that this array was a permutation, but he is not so sure about it. He wants to restore some array that corresponds to the $ q $ facts that he remembers and is very similar to permutation. Formally, Ivan has denoted the $ cost $ of array as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF863F/198b849a40dcf1d15e369281568dd0d51bf7cdcd.png), where $ cnt(i) $ is the number of occurences of $ i $ in the array.

Help Ivan to determine minimum possible $ cost $ of the array that corresponds to the facts!

## 样例 #1

### 输入

```
3 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 1
1 1 3 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 2
1 1 3 2
2 1 3 2
```

### 输出

```
9
```

## 样例 #4

### 输入

```
3 2
1 1 3 2
2 1 3 1
```

### 输出

```
-1
```

# 题解

## 作者：tzc_wk (赞：7)

费用流之差分建图

给我的[网络流 blog](https://www.luogu.com.cn/blog/et2006/wang-lao-liu-hao-ti-ti-xie-hui-zong) 打个 call。

首先，我们可以将所有限制都转化为 $a_i$ 在区间 $[l_i,r_i]$ 中。如果 $l_i \geq r_i$，那么说明无解，否则一定有解。

接下来就考虑这个解怎么求。我们将每个点拆成 $2$ 个点，其中两个是入点和出点 $in,out$。由于代价为 $\sum cnt(i)^2$，所以我们考虑差分建图，即 $n^2=1+3+\dots+(2n-1)$，所以我们对于每个数（注意，不要跟下标搞混了）再建 $2$ 个点，称为 $i.a,i.b$。这样建图方式就比较显然了：

1. 对于每个下标 $i$，连一条边 $(S,i.in,1,0)$，表示每个 $a_i$ 只能取 $1$ 个值。同理，连边 $(i.out,T,1,0)$。
2. 对于每个下标 $i$，枚举 $a_i$ 可以取的值 $j \in [l_i,r_i]$，连边 $(i.in,j.a,1,0),(j.b,i.out,1,0)$。
3. 对于每一个值 $val$，在 $i.a$ 与 $i.b$ 之间连 $n$ 条边，容量均为 $1$，费用分别为 $1,3,5,7,\dots,2n-1$，差分处理那个“平方”。

然后跑最小费用最大流就是答案。

```cpp
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int head[100005],ecnt=1;
struct edge{
	int to,nxt,cap,cost;
} e[1000005];
inline void addedge(int u,int v,int f,int c){
	e[++ecnt].to=v;e[ecnt].cap=f;e[ecnt].cost=c;e[ecnt].nxt=head[u];head[u]=ecnt;
}
bool vis[100005];
int dist[100005],flow[100005],pre[100005],pos[100005];
inline bool spfa(int s,int t){
	memset(vis,1,sizeof(vis));
	memset(dist,63,sizeof(dist));
	queue<int> q;
	vis[s]=0;
	dist[s]=0;
	flow[s]=0x3f3f3f3f;
	q.push(s);
	while(!q.empty()){
		int x=q.front();
//		cout<<x<<endl;
		vis[x]=true;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
//			cout<<y<<endl;
			if(e[i].cap>0&&dist[y]>dist[x]+e[i].cost){
				dist[y]=dist[x]+e[i].cost;pos[y]=x;pre[y]=i;
				flow[y]=min(flow[x],e[i].cap);
//				cout<<flow[y]<<endl;
				if(vis[y]){
					q.push(y);
					vis[y]=false;
				}
			}
		}
		q.pop();
	}
//	cout<<flow[t]<<endl;
	return dist[t]<0x3f3f3f3f;
}
inline int Dinic(int s,int t){
	int sum=0;
	while(spfa(s,t)){
		sum+=flow[t]*dist[t];
		for(int i=t;i!=s;i=pos[i]){
			e[pre[i]].cap-=flow[t];
			e[pre[i]^1].cap+=flow[t];
		}
	}
	return sum;
}
int n=read(),m=read();
int mn[55],mx[55]; 
signed main(){
	fz(i,1,n)	mn[i]=1,mx[i]=n; 
	fz(i,1,m){
		int opt=read(),l=read(),r=read(),x=read();
		if(opt==1){
			for(int j=l;j<=r;j++)	mn[j]=max(mn[j],x);
		}
		else{
			for(int j=l;j<=r;j++)	mx[j]=min(mx[j],x);
		}
	}
	fz(i,1,n){
		if(mn[i]>mx[i]){
			puts("-1");
			return 0;
		}
	}
	fz(i,1,n){
		addedge(0,i,1,0);
		addedge(i,0,0,0);
		addedge(n+n+n+i,5000,1,0);
		addedge(5000,n+n+n+i,0,0);//建图方式1
		fz(j,mn[i],mx[i]){
			addedge(i,n+j,1,0);
			addedge(n+j,i,0,0);
			addedge(n+n+j,n+n+n+i,1,0);
			addedge(n+n+n+i,n+n+j,0,0);//建图方式2
		}
	}
	fz(i,1,n){
		fz(j,1,n){
			addedge(n+i,n+n+i,1,2*j-1);
			addedge(n+n+i,n+i,0,-(2*j-1));//建图方式3
		}
	}
	cout<<Dinic(0,5000)<<endl;
	return 0;
}
```

---

## 作者：__vector__ (赞：4)

vp 被卡死在这题了，写个题解记录一下。  
### 题意  
长度为 $n$ 的序列，第 $i$ 个数的值域范围是 $l_i,r_i$。  

求所有可能的序列中，所有数出现次数平方和的最小可能的值。  
### 做法     

注意到每个位置 $i$ 都只能有一个数，并且这个数在 $[l_i,r_i]$ 之间，相当于位置 $i$ 可以为 $[l_i,r_i]$ 中的某个数贡献一次出现次数。  

从这里可以想到网络流，由于最终每个数都要出现一次，考虑将原问题求的总代价作为费用，而最大流量设计为能有效安排的位置个数，这样保证了使用最小费用最大流可以在有解的情况下求出最小代价，当然，此时最大流是 $n$。  

考虑一下发现，上述过程对应的是源点向每个位置 $i$ 连一条容量为 $1$，代价为 $0$ 的边，每个位置 $i$ 向数值 $[l_i,r_i]$ 连一条容量为 $1$，代价为 $0$ 的边。  

由于每种数值 $j$ 的出现次数决定了最终代价，考虑每个数值 $j$ 向汇点连 $n$ 条容量为 $1$，费用分别为 $1^2-0^0,2^2-1^2,3^2-2^2,\cdots,n^2-(n-1)^2$ 的边。  

然后跑最小费用最大流就行，我用的是 Dinic，用时 46ms。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
template<class T>
void wrint(T x){
    if(x<0){
        x=-x;
        pc('-');
    }
    if(x>=10){
        wrint(x/10);
    }
    pc(x%10^48);
}
template<class T>
void wrintln(T x){
    wrint(x);
    pln
}
template<class T>
void read(T& x){
    x=0;
    int f=1;
    char ch=gc;
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=gc;
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=gc;
    }
    x*=f;
}
const int maxn=55;
int n,q;
int mx[maxn],mn[maxn];
struct EDGE{
    int to,nxt;
    int lim,cost;
}edge[maxn*maxn*6];
int head[maxn*2];
int cnt=1;
void _add(int u,int to,int lim,int cost){
    edge[++cnt].to=to;
    edge[cnt].nxt=head[u];
    edge[cnt].lim=lim;
    edge[cnt].cost=cost;
    head[u]=cnt;
}
void add(int u,int to,int lim,int cost){
	//printf("%d -> %d\n",u,to);
    _add(u,to,lim,cost);
    _add(to,u,0,-cost);
}
int source=0,receive;
int dis[maxn*2];
int cur[maxn*2];
bool ins[maxn*2];
bool vis[maxn*2];
bool bfs(){
    queue<int> q;
    memset(dis,0x3f,sizeof dis);
    memcpy(cur,head,sizeof head);
	memset(vis,0,sizeof vis);
    q.push(source);
    dis[source]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ins[u]=0;
        for(int i=head[u];i;i=edge[i].nxt){
            int to=edge[i].to;
            if(edge[i].lim&&dis[to]>dis[u]+edge[i].cost){
                dis[to]=dis[u]+edge[i].cost;
                if(!ins[to]){
                    q.push(to),ins[to]=1;
                }
            }
        }
    }
    return (dis[receive]<=1e8);
}
int dfs(int u,int flow){
    if(!flow||u==receive)return flow;
    int used=0;
	vis[u]=1;
    for(int& i=cur[u];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(dis[to]==dis[u]+edge[i].cost&&!vis[to]&&edge[i].lim>0){
            int use=dfs(to,min(flow-used,edge[i].lim));
            edge[i].lim-=use;
            edge[i^1].lim+=use;
            used+=use;
        }
        
        if(used==flow)return used;
    }
    return used;
}
void Dinic(){
    int mxflow=0,totcost=0;
    while(bfs()){
        int nwflow=dfs(source,1e9);
        mxflow+=nwflow;
        totcost+=nwflow*dis[receive];
    }
    if(mxflow!=n){
        puts("-1");
    }else{
        printf("%d\n",totcost);
    }
}
void solve(int id_of_test){
	read(n);
    read(q);
    FOR(i,1,n){
        mn[i]=1,mx[i]=n;
    }
    receive=2*n+1;
    FOR(i,1,q){
        int t,l,r,v;
        read(t);
        read(l);
        read(r);
        read(v);
        if(t==1){
            FOR(j,l,r){
                ckmx(mn[j],v);
            }
        }else{
            FOR(j,l,r){
                ckmn(mx[j],v);
            }
        }
    }
    FOR(i,1,n){
        add(source,i,1,0);
    }
    FOR(i,1,n){
        FOR(j,mn[i],mx[i]){
            add(i,n+j,1,0);
        }
    }
    FOR(v,1,n){
        FOR(mult,1,n){
            add(v+n,receive,1,mult*mult-(mult-1)*(mult-1));
        }
    }
    Dinic();
}
int main()
{
	int T;
	T=1;
	FOR(_,1,T){
		solve(_);
	}
	return 0;
}
```

---

## 作者：_Clown_ (赞：4)

## 本弱鸡的第一道黑题！
## 发篇题解纪念一下！

这道题目我们可以用最小费用最大流来解决。

首先，你要会打费用流的模板。

不会的可以参考[这里](https://www.cnblogs.com/Xsmyy/p/13458370.html)。

然后我们开始推式子...

设$U_i$表示第$i$个数$\ge U_i$

设$D_i$表示第$i$个数$\ge D_i$

我们先将源点$Start$向第一层流量为$\mathcal{1}$费用为$0$

然后跑一边费用流就好了呀！

不会费用流的去[这里](https://www.cnblogs.com/Xsmyy/p/13458370.html)。

[我的代码跑的还不错，Rank2](https://cdn.luogu.com.cn/upload/image_hosting/o3z0neym.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

```cpp
#include<bits/stdc++.h>
#define MAX 201
using namespace std;
int TotalPoint,TotalEdge;
int Start,End,Sp;
int Ans,AllCost;
bool Visit[MAX];
bool VisitDfs[MAX];
int Dist[MAX];
int U[MAX],D[MAX];
vector<int>Edge[MAX];
vector<int>Stream[MAX];
vector<int>Cost[MAX];
vector<int>Size[MAX];
inline void AddEdge(int From,int To,int NowStream,int NowCost)
{
    Edge[From].push_back(To);
    Edge[To].push_back(From);
    Stream[From].push_back(NowStream);
    Stream[To].push_back(0);
    Cost[From].push_back(NowCost);
    Cost[To].push_back(-NowCost);
    Size[From].push_back(Edge[To].size()-1);
    Size[To].push_back(Edge[From].size()-1);
}
inline bool Spfa(int Start,int End)
{
    register queue<int>Queue;
    register int i;
    for(i=1;i<=Sp;i++)
    {
        VisitDfs[i]=false;
        Visit[i]=false;
        Dist[i]=2147483647;
    }
    Visit[Start]=true;
    Dist[Start]=0;
    Queue.push(Start);
    while(!Queue.empty())
    {
        register int Top;
        Top=Queue.front();
        Queue.pop();
        Visit[Top]=false;
        for(i=0;i<Edge[Top].size();i++)
        {
            register int Next;
            Next=Edge[Top][i];
            if(Dist[Top]+Cost[Top][i]<Dist[Next]&&Stream[Top][i])
            {
                Dist[Next]=Dist[Top]+Cost[Top][i];
                if(!Visit[Next])
                {
                    Visit[Next]=true;
                    Queue.push(Next);
                }
            }
        }
    }
    return Dist[End]!=2147483647;
}
inline int Dfs(int Now,int End,int Min)
{
    if(!Min||Now==End)
    {
        return Min;
    }
    register int Return;
    Return=0;
    VisitDfs[Now]=1;
    register int i;
    for(i=0;i<Edge[Now].size();i++)
    {
        register int Next=Edge[Now][i];
        if(Dist[Now]+Cost[Now][i]==Dist[Next]&&Stream[Now][i]&&!VisitDfs[Next])
        {
            register int MinStream;
            MinStream=Dfs(Next,End,min(Min,Stream[Now][i]));
            Stream[Now][i]-=MinStream;
            Stream[Next][Size[Now][i]]+=MinStream;
            Min-=MinStream;
            Return+=MinStream;
            AllCost+=MinStream*Cost[Now][i];
        }
    }
    return Return;
}
inline void Mcmf()
{
    while(Spfa(Start,End))
    {
        Ans=Ans+Dfs(Start,End,2147483647);
    }
}
int main(void)
{
    register int i,j;
    cin>>TotalPoint>>TotalEdge;
    Start=TotalPoint*2+1;
    End=TotalPoint*2+2;
    Sp=TotalPoint*2+2;
    for(i=1;i<=TotalPoint;i++)
    {
    	U[i]=1;
    	D[i]=TotalPoint;
	}
    for(i=1;i<=TotalEdge;i++)
    {
        register int Left,Right,Opt,Value;
        cin>>Opt>>Left>>Right>>Value;
        for(j=Left;j<=Right;j++)
        {
        	if(Opt==1)
        	{
        		U[j]=max(U[j],Value);
			}
			else
			{
				D[j]=min(D[j],Value);
			}
		}
    }
    for(i=1;i<=TotalPoint;i++)
    {
    	AddEdge(Start,i,1,0);
	}
	for(i=1;i<=TotalPoint;i++)
	{
		for(j=U[i];j<=D[i];j++)
		{
			AddEdge(i,j+TotalPoint,1,0);
		}
	}
	for(i=1;i<=TotalPoint;i++)
	{
		for(j=1;j<=TotalPoint;j++)
		{
			AddEdge(i+TotalPoint,End,1,2*j-1);
		}
	}
    Mcmf();
    if(Ans==TotalPoint)
    {
    	cout<<AllCost<<endl;
	}
	else
	{
		cout<<-1<<endl;
	}
    return 0;
}
```

---

## 作者：RainFestival (赞：3)

这道题用费用流

设$u_i$为第$i$个数字$\ge u_i$

设$d_i$为第$i$个数字$\le d_i$

我们先将源点$s$向第$1$层的点连流量为$1$,费用为$0$边

再将第$1$层每一个点向第$1$层的第$x,x\in[u_i,d_i]$个点连一条流量为$1$，费用为$0$的边

因为费用是$k^2(k$是相同的数数量$)$，且$k^2$单调递增，所以第$2$层每一个点向汇点$t$连$n$条边,每一条边的流量为$1$,费用依次为$1^2-0^2$,$2^2-1^2$,$\cdot\cdot\cdot$,$n^2-(n-1)^2$，第$k$次走这条边时费用从$(k-1)^2$变成$k^2$,增加了$k^2-(k-1)^2$,而这一组边第$k$小的费用正好为$k^2-(k-1)^2$

然后跑一边费用流

如果流量$<n$,说明无解

```cpp
#include<cstdio>
#include<vector>
#include<queue>
std::vector<int> a[105],b[105],c[105],f[105];
int n,m,s,t,sp,flow=0,cost=0,dis[105],vis[105],use[105],u[55],d[55];
std::queue<int> q;
void add(int x,int y,int v,int w)
{
	a[x].push_back(y);a[y].push_back(x);
	b[x].push_back(v);b[y].push_back(0);
	c[x].push_back(w);c[y].push_back(-w);
	f[x].push_back(a[y].size()-1),f[y].push_back(a[x].size()-1); 
}
int spfa(int s,int t)
{
	for (int i=1;i<=sp;i++) dis[i]=1000000000,vis[i]=0,use[i]=0;
	dis[s]=0;vis[s]=1;q.push(s);
	while (!q.empty())
	{
		int v=q.front();q.pop();vis[v]=0;
		for (int i=0;i<a[v].size();i++)
		{
			int u=a[v][i];
			if (dis[v]+c[v][i]<dis[u]&&b[v][i])
			{
				dis[u]=dis[v]+c[v][i];
				if (!vis[u]) q.push(u),vis[u]=1;
			}
		}
	}
	return dis[t]!=1000000000;
}
int dfs(int v,int t,int now)
{
	if (v==t||!now) return now;
	int fl=0;use[v]=1;
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
	    if (dis[v]+c[v][i]==dis[u]&&b[v][i]&&!use[u])
		{
			int k=dfs(u,t,std::min(b[v][i],now));
			b[v][i]=b[v][i]-k;b[u][f[v][i]]=b[u][f[v][i]]+k;
			fl=fl+k;now=now-k;cost=cost+k*c[v][i];
		}
	}
	return fl;
}
void mcmf(){while (spfa(s,t)) flow=flow+dfs(s,t,1000000000);}
int main()
{
	scanf("%d%d",&n,&m);s=n*2+1,t=2*n+2,sp=2*n+2;
	for (int i=1;i<=n;i++) u[i]=1,d[i]=n;
	for (int i=1;i<=m;i++)
	{
		int opt,l,r,v;
		scanf("%d%d%d%d",&opt,&l,&r,&v);
		for (int i=l;i<=r;i++) opt==1?u[i]=std::max(u[i],v):d[i]=std::min(d[i],v);
	}
	for (int i=1;i<=n;i++) add(s,i,1,0);
	for (int i=1;i<=n;i++) for (int j=u[i];j<=d[i];j++) add(i,j+n,1,0);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) add(i+n,t,1,2*j-1);
	mcmf();
	if (flow==n) printf("%d\n",cost);
	else puts("-1");
	return 0;
}
```
然后就$AC$了

$QAQ$

---

## 作者：tder (赞：1)

看不懂现有的任何一篇题解，还是我太弱了。

---

由于 $n\le50$，我们不妨用 $O(q\cdot n)$ 的复杂度预处理出 $a_i\in[l_i,r_i]$，若存在一个 $l_i>r_i$ 则无解。具体的：

> 对于每个约束 $\forall~i\in[x,y], a_x\ge v$，我们不妨枚举 $i$，对 $l_i$ 与 $v$ 取较大值作为 $l_i$。反之同理，对于 $\forall~i\in[x,y], a_x\le v$，同样枚举 $i$，对 $r_i$ 与 $v$ 取较小值作为 $r_i$。

接下来考虑建图。观察到 $a_i\in[1,n]$，我们可以用若干个点表示一种取值。由于最终影响答案的是每种取值出现的次数，因此我们希望将这出现 $1\sim n$ 种情况分别表示出来。这里没有 $0$ 是因为没用贡献。具体的：

> 由于 $\text{cnt}$ 个 $s$ 对答案的贡献是 $\text{cnt}^2$，因此考虑差分。我们知道：
> 
> $$
> \begin{aligned}
> 1^2&=1 \\
> 2^2&=1+3 \\
> 3^2&=1+3+5 \\
> n^2&=1+3+5+\cdots+(2n-1) \\
>   &=\sum_{i=1}^{n}(2i-1)
> \end{aligned}
> $$
> 
> 这是显然的，可以通过 $n^2-(n-1)^2=(n+(n-1))\cdot(n-(n-1))=2n-1$ 轻松证明。
> 
> 那么，对于每一种取值 $s$，我们考虑建两个点 $\text{in}_s$ 和 $\text{out}_s$，两点之间连 $n$ 条边，分别为 $\text{in}_s\xrightarrow[c=2i-1]{w=1}\text{out}_s$，此处 $i$ 的取值范围为 $[1,n]$。
> 
> 由此，流前 $k$ 条边表示在序列中共有 $\text{cnt}=\displaystyle\sum_{i=1}^k(2i-1)=k^2$ 个 $s$。

我们已经连好了对应每种取值的边，接下来是确定每个 $a_i$ 的取值：

> 我们已经预处理出 $a_i\in[l_i,r_i]$，因此不妨对每个 $l_i\le j\le r_i$，连一条 $i\xrightarrow[c=0]{w=1}\text{in}_j$ 和 $\text{out}_j\xrightarrow[c=0]{w=1}i$。 
>
> 但是这样我们无法对「每个 $a_i$ 只能取一个值」进行约束，我们不妨考虑拆点套路，将 $i$ 拆成 $\text{iin}_i$ 和 $\text{oout}_i$。连 $s\xrightarrow[c=0]{w=1}\text{iin}_i$ 和 $\text{oout}_i\xrightarrow[c=0]{w=1}t$ 保证流经 $i$ 的流量最多为 $1$。
> 
> 同理，前面的建图方式也应改为：连 $\text{iin}_i\xrightarrow[c=0]{w=1}\text{in}_j$ 和 $\text{out}_j\xrightarrow[c=0]{w=1}\text{oout}_i$。

举个简单的例子便于理解：

> 对于一个长度为 $4$ 的序列 $\{a_4\}$，给定约束分别为：
>
> - $\forall~i\in[1,3],a_i\ge2$；
> - $\forall~i\in[4,4],a_i\le3$；
> - $\forall~i\in[2,3],a_i\le3$。

> 整理一下可以得到下表：
> 
> | $i$ | $1$ | $2$ | $3$ | $4$ |
> | :----------: | :----------: | :----------: | :----------: | :----------: |
> | $[l_i,r_i]$ | $[2,4]$ | $[2,3]$ | $[2,3]$ | $[1,3]$ |
> 
> 这里给出 $a_1$ 的连边方式，注意应当还有 $s\to\text{iin}_1$ 和 $\text{oout}_1\to t$ ：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/32fg7g5o.png)

跑一遍 MCMF 即可解决。

---

## 作者：small_john (赞：0)

## 思路

首先可以暴力预处理出每个点的最终范围 $l_i\sim r_i$，显然如果 $l_i>r_i$ 无解，否则必然有解。

注意到 $x^2=1+3+\dots+(2x-1)$。将每种权值拆分为两个点 $in_i$ 和 $out_i$，分别连上容量为 $1$，费用为 $1,3,\dots,2n-1$ 的边，如果有 $k$ 个流量流入了 $in_i$，相当于有 $k$ 个数的值为 $i$，跑最小费用最大流最终的费用刚好是 $k^2$，符合题目所求。

最后的建图就十分显然了，建立超级源点 $S$，$S$ 向每个 $i$ 连容量为 $1$，费用为 $0$ 的边，表示每个 $a_i$ 只能选一个数，每个 $i$ 向 $in_{l_i\sim r_i}$ 连容量为 $1$，费用为 $0$ 的边，表示 $a_i$ 可以选这个数。建立超级汇点 $T$，每个 $out_i$ 向 $T$ 连容量为 $\infin$，费用为 $0$ 的边。

然后跑最小费用最大流即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55,M = 1e6+5;
int n,q,s,t,cnt = 1,head[N*3],now[N*3],nxt[M],to[M],fl[M],g[M];
inline void add(int x,int y,int w,int flow)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y,g[cnt] = w,fl[cnt] = flow;
	nxt[++cnt] = head[y];
	head[y] = cnt;
	to[cnt] = x,g[cnt] = -w,fl[cnt] = 0;
}
int dis[N*3],mn[N*3];
bool vis[N*3];
inline bool spfa()
{
	for(int i = s;i<=t;i++)
		dis[i] = 2e9,vis[i] = 0;
	dis[s] = 0,mn[s] = 2e9,vis[s] = 1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();q.pop();
		vis[u] = 0;
		for(int i = head[u];i;i = nxt[i])
		{
			int v = to[i];double w = g[i];
			if(fl[i]&&dis[v]>dis[u]+w)
			{
				now[v] = i,dis[v] = dis[u]+w,mn[v] = min(mn[u],fl[i]);
				if(!vis[v]) vis[v] = 1,q.push(v);
			}
		}
	}
	if(dis[t]<2e9) return 1;
	return 0;
}
int lt[N],rt[N];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i = 1;i<=n;i++) lt[i] = 1,rt[i] = n;
	s = 0,t = 3*n+1;
	while(q--)
	{
		int op,l,r,v;
		cin>>op>>l>>r>>v;
		for(int i = l;i<=r;i++)
			if(op==1) lt[i] = max(lt[i],v);
			else rt[i] = min(rt[i],v);
	}
	for(int i = 1;i<=n;i++)
	{
		if(lt[i]>rt[i]) return cout<<"-1",0;
		add(s,i,0,1);
		for(int j = lt[i];j<=rt[i];j++) add(i,j+n,0,1);
		for(int j = 1;j<=n;j++) add(i+n,i+2*n,2*j-1,1);
		add(i+2*n,t,0,2e9);
	}
	int ans1 = 0,ans2 = 0;
	while(spfa())
	{
		ans1+=mn[t],ans2+=(double)mn[t]*dis[t];
		int x = t;
		while(x!=s)
		{
			fl[now[x]]-=mn[t],fl[now[x]^1]+=mn[t];
			x = to[now[x]^1];
		}
	}
	cout<<ans2;
	return 0;
}
```

---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF863F)

看到数据范围直接考虑费用流。

首先直接预处理出每个数的上界和下界，若上界 $<$ 下界直接特判 $-1$。然后考虑构建二分图，左部点为 $n$ 个点代表这 $n$ 个数，即第 $i$ 的点代表第 $i$ 个数；右部点为 $n$ 个点代表值域，即第 $i+n$ 个点代表 $i$ 值。

将源点向每个左部点连容量 $1$ 费用 $0$ 的边，将每个左部点向其上下界范围内的右部点连容量 $0$ 费用 $1$ 的边。

最后要将右部点向汇点连边，但是观察到每条（右部点向汇点连的）边的费用和其流量有关系，所以我们考虑拆边，将每个右部点向汇点练的边拆为 $n$ 条边，每条边容量为 $1$，费用为 $x^2-(x-1)^2=2x-1$。

---

## 作者：UperFicial (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF863F)

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16149816.html)。

### $\texttt{Description}$

$n$ 个数，每个数都在 $1$ 至 $n$ 间。$m$ 个形如 $[l,r]$ 中的数不小于或不大于 $v$ 的限制。设 $cnt(i)$ 表示 $i$ 的出现次数，求 $\sum cnt_i^2$ 的最小值。

$1\le n\le 50$，$1\le m\le 100$。

### $\texttt{Solution}$

发现数据范围这么小，那么我们可以暴力预处理出，序列中每一个 $a_i$ 可能取到的范围，设为 $[down_i,up_i]$。

然后考虑一个二分图模型。

左边是 $1$ 至 $n$，代表每一个位置，右边是 $1$ 至 $n$，代表序列中每一个位置上可能的值。

每一个位置上只能有一个数，所以我们连 $s\to i$，容量为 $0$，费用为 $1$。

然后对于每一个位置连向它能取到的区间即 $[down_i,up_i]$，流量为 $1$，费用为 $0$。

这些都是非常显然的。

但问题在于，如果我们右边的每一个数，向 $t$ 连一条容量为 $\infty$ 费用为 $1$ 的边（表示一个数可能被多个位置匹配，然后每一个位置都要有 $1$ 的贡献），最终需要求得是 $\sum cnt_i^2$，无法解决。

考虑右边一个数，最多被匹配的上限是 $n$，那么将这个点向 $t$ 连 $n$ 条边，第 $i$ 条边，容量为 $1$，费用为 $i^2-(i-1)^2$。

这是什么意思呢？

考虑它的匹配，容量都一样，那么我们 $\texttt{spfa}$ 在找增光路的时候肯定会找费用最小的几条。

当从第 $i$ 小的边，加入了第 $i+1$ 小的边时，$i^2$ 的那一项恰好被削掉，$(i-1)^2$ 的那一项又被前面的消掉，所以求和起来就是 $(i+1)^2$。

个人感觉像是构造的思想，十分巧妙。也许是一种 $\texttt{trick}$ 但我并不知道。

代码：

```cpp
int main()
{
	n=read(),m=read();
	s=0,t=n<<1|1;
	for(register int i=1;i<=n;i++) down[i]=1,up[i]=n;
	for(register int i=1;i<=m;i++)
	{
		int opt=read(),l=read(),r=read(),v=read();
		if(opt==1) for(register int j=l;j<=r;j++) down[j]=Max(down[j],v);
		else for(register int j=l;j<=r;j++) up[j]=Min(up[j],v);
	} 
	for(register int i=1;i<=n;i++) if(down[i]>up[i])
	{
		puts("-1");
		return 0;
	}
	for(register int i=1;i<=n;i++)
		for(register int j=down[i];j<=up[i];j++)
			add_edge(i,j+n,1,0);
	for(register int i=1;i<=n;i++) add_edge(s,i,1,0);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			add_edge(i+n,t,1,(j<<1)-1);
	MCMF();
	return 0;
}
```

注意数组不要开小了。

$$\texttt{The End.by UF}$$

---

