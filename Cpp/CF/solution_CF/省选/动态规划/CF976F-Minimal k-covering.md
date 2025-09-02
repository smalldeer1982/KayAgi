# Minimal k-covering

## 题目描述

##### 题目大意

给你一张二分图  $G = (U, V, E)$ ， $U$  是图的  $X$  部， $V$  是图的  $Y$  部， $E$  是边集，可能有重边。

我们称  $E$  的某个子集  $\overline E$  是 *k-覆盖*  的，当且仅当图  $\overline G = (U, V, \overline E)$  的每个顶点至少连接了  $k$  条边；若  $\overline E$  是 k-覆盖 的且不存在元素个数比它更小的边集也是 k-覆盖 的，则称  $\overline E$  是一个 *最小k-覆盖* 。

你的任务是对于所有  $k \in [0, minDegree]$ ，求出 最小k-覆盖，其中  $minDegree$  是图  $G$  的所有点度数的最小值。

## 样例 #1

### 输入

```
3 3 7
1 2
2 3
1 3
3 2
3 3
2 1
2 1
```

### 输出

```
0 
3 3 7 4 
6 1 3 6 7 4 5 
```

## 样例 #2

### 输入

```
1 1 5
1 1
1 1
1 1
1 1
1 1
```

### 输出

```
0 
1 5 
2 4 5 
3 3 4 5 
4 2 3 4 5 
5 1 2 3 4 5 
```

# 题解

## 作者：Twig_K (赞：4)

### 题意

给定一张二分图，对于每个 $k\in [0,minDegree]$，求一个边数最小的边集，满足对于左右每个点都有至少 $k$ 条邻边被选出。

### 思路

所有边全选上一定是符合条件的，但不是最小的。题目转化为：每个点减去的邻边数量有上限，减去最多数量的边不选，使得仍然满足条件。

与二分图匹配有一些相似，只不过每个点可以匹配上多条边（也就是下文 $v_i$），我们用最大流来解决。

### 朴素做法

先考虑对于某个特定的 $k$ 怎么做。

设左部点编号为 $[1,n1]$，右部点编号为 $[n1+1,n1+n2]$，设 $v_i \leftarrow deg_i-k, i\in [1,n1+n2]$，即减掉边的上限。连边方案为：

- $(S,i,v_i),i \in [1,n1]$，第一类边。
- $(u_i,v_i+n1,1)$，题目中读入的边，第二类边。
- $(i,T,v_i),i \in [n1+1,n1+n2]$，第三类边。

求出最大流是 $w$，那么这个 $k$ 的答案就是 $m-w$。输出方案时考虑第二类边，如果第二类边满流，这条边就是被我们删去的。输出那些没有被删去的边。

对每种 $k$ 都用上述算法跑一遍。时间复杂度 $O(超时)$。我们每次都需要重新建图，太慢了。

[评测记录：TLE on 15](https://codeforces.com/problemset/submission/976/295336316)

### 优化

倒序枚举 $k$ 的值，我们发现对于每个 $k$，图的形态是不变的，且当 $k$ 的值减少 $1$ 时，上述第二类边的流量不变，每条第一类和第三类的边流量增加 $1$。

所以我们只需要在上一个 $k$ 的残量网络上，将第一类边和第三类边的正向边流量加 $1$，看看有没有新的增广路，把流量加到上一次的答案中。输出方案的判断还是一样的。

### 代码

[完整代码链接](https://codeforces.com/problemset/submission/976/295335849)

```cpp
void addedge(int x,int y,int z){ add(x,y,z),add(y,x,0); }

bool bfs();
int dfs(int u,int mxf);
int Dinic(int N);

int ans,res[maxn];//ans 存最大流的值，res 是每轮答案
vector<int> ret[maxn];
void getres(int x){
    ans+=Dinic(T),res[x]=m-ans;
    For(i,1,m) if(e[eid[i]].w) ret[x].push_back(i);
}
signed main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n1,&n2,&m);
    S=(n1+n2)+1,T=(n1+n2)+2;

    int u,v,mind=m;
    For(i,1,m) scanf("%d%d",&u,&v),v+=n1,++d[u],++d[v],addedge(u,v,1),eid[i]=cnt-2;//eid[i] 和 id[i] 存编号，方便之后对流量的修改以及判断是否满流
    For(i,1,n1+n2) mind=min(mind,d[i]);
    For(i,1,n1) addedge(S,i,d[i]-mind),id[i]=cnt-2;
    For(i,n1+1,n1+n2) addedge(i,T,d[i]-mind),id[i]=cnt-2;

    getres(mind);
    Forr(x,mind-1,0){
        For(i,1,n1+n2) e[id[i]].w++;//修改流量
        getres(x);
    }
    For(i,0,mind){
        printf("%d",res[i]);
        for(auto v:ret[i]) printf(" %d",v);
        printf("\n");
    }
}
```

---

## 作者：tzc_wk (赞：3)

一道网络流的好题

安利个人 [blog](https://www.luogu.com.cn/blog/et2006/wang-lao-liu-hao-ti-ti-xie-hui-zong)。

我太弱了，被这个“最小”带偏了，看到“最小”我就想到最小割，看了CF官方题解才知道是一个最大流。

由于普通网络流中，限制一般是每条边流量最大为多少（除了有上下界网络流，可惜我不会），因此我们可以把题目中的“每个点最少覆盖 $k$ 次改为每个点最多覆盖 $d_i-k$ 次，其中 $d$ 数组为每个节点的度数。这样一来建图就出来了，对于二分图的左半部分，连边 $(S,i,d_i-k)$，对于二分图的右半部分，连边 $(i,T,d_i-k)$。中间部分连题目给出的边，容量为 $1$，然后跑最大流，用 $m-$ 最大流就是答案。输出方案只需找中间流量为 $0$ 的边输出就好了。

但是你发现你 TLE 了。原因是：你对于每个 $k$ 都建了一次图，跑了一次最大流，这样相当于跑了 $n$ 次网络流，很明显 CF 数据不可能这么弱让你跑过去的。那么我们可不可以只建一次图，然后在残余网络上跑最大流呢？

答案是肯定的。我们可以倒着从 $minDegree$ 开始，每一次在上一次的残余网络上跑最大流，不难发现 $k$ 从 $i$ 变为 $i-1$ 的时候与 $S$ 和 $T$ 相连的边的容量都扩大 $1$，这样我们只需建一次图，跑 $n$ 次网络流的时间复杂度均摊下来是 $O(n)$ 的，就可以过了。

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
int n1=read(),n2=read(),m=read();
int u[2005],v[2005];
int head[5005];
struct edge{
	int to,nxt,cap;
} e[3000005];
int ecnt=1;
inline void addedge(int u,int v,int f){
	e[++ecnt].to=v;e[ecnt].cap=f;e[ecnt].nxt=head[u];head[u]=ecnt;
}
int dep[5005];
inline bool bfs(int s,int t){
	queue<int> q;
	memset(dep,-1,sizeof(dep));
	q.push(s);dep[s]=0;
	while(!q.empty()){
		int cur=q.front();q.pop();
		for(int i=head[cur];i;i=e[i].nxt){
			int to=e[i].to;
			if(dep[to]==-1&&e[i].cap){
				dep[to]=dep[cur]+1;
				q.push(to);
			}
		}
	}
	if(dep[t]!=-1)	return 1;
	return 0;
}
inline int dfs(int x,int t,int f){
	if(x==t)	return f;
	int ret=0;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(dep[y]==dep[x]+1&&e[i].cap){
			int w=dfs(y,t,min(f-ret,e[i].cap));
			e[i].cap-=w;
			e[i^1].cap+=w;
			ret+=w;
			if(ret==f)	return f;
		}
	}
	if(ret==0)	dep[x]=-1;
	return ret;
}
inline int Dinic(int s,int t){
	int tot=0;
	while(bfs(s,t))	tot+=dfs(s,t,0x3f3f3f3f);
	return tot;
}
int id[2005],deg[4005];
vector<int> ans[2005];
signed main(){
	fz(i,1,m){
		u[i]=read();v[i]=read();v[i]+=n1;
		deg[u[i]]++;deg[v[i]]++;
	}
	int k=0x3f3f3f3f;
	fz(i,1,n1+n2)	k=min(k,deg[i]);
	fz(j,1,n1){
		addedge(0,j,deg[j]-k);
		addedge(j,0,0);
	}
	fz(j,n1+1,n1+n2){
		addedge(j,5000,deg[j]-k);
		addedge(5000,j,0);
	}
	fz(j,1,m){
		addedge(u[j],v[j],1);
		addedge(v[j],u[j],0);
		id[j]=ecnt;
	}
	fd(i,k,0){
		Dinic(0,5000);
		fz(j,1,m){
			if(e[id[j]].cap==0){
				ans[i].push_back(j);
			}
		}
		for(int i=head[0];i;i=e[i].nxt)	e[i].cap++;
		for(int i=head[5000];i;i=e[i].nxt)	e[i^1].cap++;
	}
	fz(i,0,k){
		cout<<ans[i].size()<<" ";
		foreach(it,ans[i])	cout<<*it<<" ";
		puts("");
	}
	return 0;
}
```

---

## 作者：Valhalla_Is_Calling (赞：1)

大 好 题

### 题意概述
为了让所有点都有至少 k 的度数，至少要选择多少边。

### 题解
对于这种多重约束问题，应该首先想到网络流。我们想一下，至少 k 的度数意味着至少有 k 条边连向这个点，也就是说最多有 $deg_i-k$ 条边不连这个点。所以我们可以考虑建图，因为题目是一个二分图，分为 U 和 V 两个大集合，所以我们可以把每个 U 集合中的点连向我们的虚拟源点 s ，V 集合中的每个点连向我们的虚拟汇点 t，边权都是 $deg_i-k$。为什么是这个呢？想一下，因为我们需要最少的边，所以我们希望选取的边尽量少，这同时意味着不选的边要尽量多，而 $deg_i-k$ 就是最多不选多少边，所以在这样的一张图上跑的最大流就是最多不选多少边。还有就是题目给的每条边都连上，权值为 1，因为一条边不能“不选 2 次”。

上面的做法非常简洁易懂，但问题是每次的 k 都是不一样的，如果对于每个 k 都重新建图，那么复杂度肯定超标，因为一次 Dinic 算法的复杂度是 $\Theta(VE)$，建图最坏情况下算是 $\Theta(E)$，就变成了 $\Theta(VE^2)$，显然过不去。

我们接着想，如果说，我们只建一次图，但是把 k 从大到小枚举 $k\in[mindeg,0]$，这意味着每次边权为 $deg_i-k$ 的边的边权都要加一，这样每次就不需要重新建图了，只需要增加边权即可。

### 做法证明
这意味着我们每次都是在上一次求解答案时的残余网络上面增广，为什么这一定是最优的呢？

经过与学长的激烈讨论，我得出了如下理解&证明方法。

因为每次边权加一，所以显然，这总共 mindeg+1 次 Dinic 的运行总时间跟直接把所有边权都按照最小的 k 即最大的 $deg_i-k$ 给的运行总时间是一样的，因为在最高边权一定的情况下，他们增广的次数是一定的，所以均摊下来总共时间复杂度还是 $\Theta(VE)$，这是关于时间复杂度的证明。

那最优性呢？每次我们都在上一次的残余网络上面 Dinic，根据 Dinic 的运行方式，如果这一次有比上一次更优的解决方案，那么我们会通过反向边把流量加回去，不会影响结果。

到这里，这道题就做完啦（

### AC代码
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define INF 0x3f3f3f3f
using namespace std;
const int N=2e5+5;
int n1,n2,m,v[N],w[N],nxt[N],head[N],id[N],cnt=1,de[N],S,T;
int mindegree=0x3f3f3f3f,X[N],Y[N],dep[N],vis[N],cur[N];
vector<int>ans[N];
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
void add(int a,int b,int c,int d)
{
    v[++cnt]=b;
    w[cnt]=c;
    id[cnt]=d;
    nxt[cnt]=head[a];
    head[a]=cnt;
}
int bfs()
{
    memset(dep,0x3f,sizeof(dep));
    for(int i=S;i<=T;i++)cur[i]=head[i];
    queue<int>q;q.push(S);dep[S]=0;
    while(!q.empty())
    {
        int c=q.front();q.pop();vis[c]=0;
        for(int i=head[c];i;i=nxt[i])
        {
            if(dep[v[i]]>dep[c]+1&&w[i])
            {
                dep[v[i]]=dep[c]+1;
                if(!vis[v[i]])
                {
                    q.push(v[i]);
                    vis[v[i]]=1;
                }
            }
        }
    }
    if(dep[T]==INF)return 0;
    return 1;
}
int dfs(int x,int limit)
{
    if(x==T || !limit) return limit;
    int flow=0,rlow;
    for(int i=cur[x];i;i=nxt[i])
    {
        cur[x]=i;
        if(dep[v[i]]==dep[x]+1 && w[i])
        {
            if(rlow=dfs(v[i],min(w[i],limit)))
            {
                flow+=rlow;
                limit-=rlow;
                w[i]-=rlow;
                w[i^1]+=rlow;
                if(!limit)break;
            }
        }
    }
    return flow;
}
void Dinic()
{
    int maxflow=0;
    while(bfs()) maxflow+=dfs(S,INF);
}
int main()
{
    n1=read(),n2=read(),m=read();
    for(int i=1;i<=m;i++) X[i]=read(),Y[i]=read(),de[X[i]]++,de[Y[i]+n1]++;
    S=0;T=n1+n2+1;
    for(int i=1;i<=n1+n2;i++) mindegree=min(mindegree,de[i]);
    for(int i=1;i<=m;i++) add(X[i],Y[i]+n1,1,i),add(Y[i]+n1,X[i],0,i);
    for(int i=1;i<=n1;i++) add(S,i,de[i]-mindegree,0),add(i,S,0,0);
    for(int i=1;i<=n2;i++) add(i+n1,T,de[i+n1]-mindegree,0),add(T,i+n1,0,0);
    for(int i=mindegree;i>=0;i--)
    {
        Dinic();
        for(int j=1;j<=n1;j++)for(int k=head[j];k;k=nxt[k]) if(w[k]&&id[k]) ans[i].pb(id[k]);
        for(int j=head[S];j;j=nxt[j]) w[j]++;
        for(int j=head[T];j;j=nxt[j]) w[j^1]++;
    }
    for(int i=0;i<=mindegree;i++)
    {
        int siz=ans[i].size();
        printf("%d ",siz);
        for(int j=0;j<siz;j++) printf("%d ",ans[i][j]);
        puts("");
    }
    return 0;
}
```


---

