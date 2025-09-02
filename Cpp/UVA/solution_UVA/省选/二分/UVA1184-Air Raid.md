# Air Raid

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3625

[PDF](https://uva.onlinejudge.org/external/11/p1184.pdf)

## 样例 #1

### 输入

```
2
4
3
3 4
1 3
2 3
3
3
1 3
1 2
2 3
```

### 输出

```
2
1
```

# 题解

## 作者：阔睡王子 (赞：8)

### 考察如何提炼题目中的模型为二分图

题意：给定一张有向无环图，求最少选择几条链能覆盖所有点,且一个点只被覆盖一次。

明确，在链上，对于每个点，至多都只能影响到一个另外的点。

![](https://ftp.bmp.ovh/imgs/2020/10/e5bf792ad540934b.png)

比如选择链（4，0，1），（2），（3）， $4$ 影响到 $0$ , $0$ 影响到 $1,2$ 不能影响到已经被选择的 $0,3$ 和 $1$ 不能影响任何节点。

发现不能影响到任何节点的点就是链的末端。

那么考虑让每一个点都尽可能影响一个点，通过减少不能影响到其他点的点个数，满足让链的末端最少。

综上：

- 因一个点能影响到的点有多个，但是只能选一个。
- 要让能影响到其他点的点个数尽可能多。

想到可以用二分图解决这个问题。

于是把所有节点放在左边，增开一个虚拟集对照左边的节点。

![](https://ftp.bmp.ovh/imgs/2020/10/799ca8301ba513eb.png)

每连一条边，就让左边的点连上右边对应的点。

最后跑一个最大匹配，匹配答案为```ans```，表示最多有多少个点能影响到其他的点。

```n-=ans```代表不能影响到其他点的个数，表示链的末端个数，就是答案。

```
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e3+10;
int n,m,T,ans,cnt,tot;
int vis[maxn],link[maxn],head[maxn];
struct node
{int to,next;}e[maxn*maxn];
void build(int x,int y)
{e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;}
bool dfs(int now)
{
	for(int i=head[now];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]==tot)continue ;
		vis[v]=tot;
		if(!link[v]||dfs(link[v]))
		{
			link[v]=now;
			return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d",&T);
	for(int grp=1;grp<=T;grp++)
	{
		memset(link,0,sizeof(link));
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		cnt=ans=tot=0;
		scanf("%d%d",&n,&m);
		for(int i=1,x,y;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			build(x,y);
		}
		for(int i=1;i<=n;i++)
		{
			tot++;
			if(dfs(i))ans++;
		}
		printf("%d\n",n-ans);
	}
}
```


---

## 作者：xixike (赞：6)

我们分析题目可以发现题目给的是一个DAG（有向无环图）。我们不难发现，题目就是要求找出最少的点，去覆盖这个图中所有的点，实际上就是求这个图的最小路径覆盖。

**二分图最小路径覆盖 = 点数 $-$ 二分图最大匹配**。

我这里用的是二分图的方法，也就是匈牙利算法求二分图最大匹配。

**附代码**
```cpp
#include<iostream>
#include<cstring>
#define N 10010

using namespace std;

struct node{                      //前向星建二分图
	int v,next;
} edge[N<<1];
int head[N];

int match[N],vis[N];
int tim,tot;

void add(int x,int y){             //建图
	tot++;
	edge[tot].v=y;
	edge[tot].next=head[x];
	head[x]=tot;
}

int dfs(int x){                     //二分图最大匹配模板
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].v;
		
		if(vis[y]==tim) continue;
		vis[y]=tim;
		
		if(!match[y]||dfs(match[y])){
			match[y]=x;
			return 1;
		}
	}
	return 0;
}

int main(){
	int t,n,m,a,b;

	cin>>t;
	while(t--){
		memset(edge,0,sizeof(edge));     //多组数据，各种初始化
		memset(head,0,sizeof(head));
		memset(match,0,sizeof(match));
		memset(vis,0,sizeof(vis));
		tot=0;
		
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>a>>b;
			add(a,b+n);
			add(b+n,a);
		}
		
		int ans=0;
		for(int i=1;i<=n;i++){
			tim=i;                       //小技巧，每次只改变tim，就不用一遍又一遍地memset，能节省一点时间
			ans+=dfs(i);
		}
		
		cout<<n-ans<<endl;
	}
	return 0;
}
```


---

## 作者：小又又 (赞：5)

# problem

给了一个有向无环图，求最少路径去覆盖图中所有的点

# Solution

如果把一个路口分成出口和入口，那么从一个交叉路口出发走到另一个交叉路口就可以看做是从一个交叉口的出口，走到另一个交叉口的入口。

**思考：** 怎么从上面的问题推到二分图最少边覆盖呢？？？


**证明：** 因为路径不能重复，且伞兵一直沿着一条路走~~到尽头~~，所以每条路径的出口和入口都只能走一次，一个出口对应一个入口，这样出口看做左部点，入口看做右部点求最小路径覆盖就好了

**一些其他的东西**：

二分图的几种模型：
1. 二分图匹配（基础又重要）：每个左部点最多与一个右部点相连，每个右部点最多与一个左部点相连

1. 最小点覆盖：选取最少的点，使得所有边都至少与一个被选取点相连

    
1. 最大独立集：选取最多的点，使得其中任意两点互不相达

1. 最小边覆盖：选取最少的边使得所有的点被至少一条边覆盖

其中**最小点覆盖=最大匹配**，**最大独立集=最小边覆盖=总点数-最大匹配**

# Code
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int read(){
  int x = 1,a = 0;char ch = getchar();
  while (ch < '0'||ch > '9'){if (ch == '-') x = -1;ch = getchar();}
  while (ch >= '0'&&ch <= '9'){a = a*10+ch-'0';ch = getchar();}
  return x*a;
}
const int maxn = 1e5+10;
int t;
int n,m;
struct node{
  int to,next;
}ed[maxn];
int head[maxn],tot,matc[maxn];
bool vis[maxn];
void add(int u,int to){
  ed[++tot].to = to;
  ed[tot].next = head[u];
  head[u] = tot;
}
bool dfs(int x){
  for (int i = head[x];i;i = ed[i].next){
    int to = ed[i].to;
    if (vis[to]) continue;vis[to] = 1;
    if (!matc[to]||dfs(matc[to])){
      matc[to]=x;
      return true;
    }
  }
  return false;
}
void init(){
    memset(head,0,sizeof(head));
    memset(ed,0,sizeof(ed));
    memset(matc,0,sizeof(matc));
    tot = 0;
}
int main(){
  t = read();
  while (t--){
    init();
    n = read(),m = read();
    for (int i = 1;i <= m;i++){
      int u,v;
      u = read(),v = read();
      add(u,v + n);add(v + n,u);
    }
    int ans = 0;
  //  cout<<1<<endl;
    for (int i = 1;i <= n;i++){
      memset(vis,0,sizeof(vis));
      if (dfs(i)) ans++;
    }
    printf("%d\n",n-ans);
  }
  return 0;
}
```

---

## 作者：Rachel_in (赞：4)

本题是二分图最大匹配。因为题目要求每两条路径不能相交且没有环所以每个点的出度和入度都应该为1，也就相当于是一条链，$A_1$连向$A_2$,$A_2$连向$A_3$,$A_3$连向......与二分图匹配相当。

用Dinic来解决。我们把每个点都分为一个入点一个出点，超级源点向每个入点连一条权值为$1$的边,每个出点向超级汇点连一条权值为$1$的边。对于一条有向图$u$到$v$,将入点$u$向出点$v$连一条权值为$1$的边。每次$u$只能流过$1$的流量，满足每个点的出度和入度都为1这一条件。

我们得到的最大流的意义表示有多少个点对匹配成功，我们发现我们每匹配成功一对，我们就可以少放一个伞兵，所以最终答案为$n-$最大流

**代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
const int N=300;
const int M=50000;
const int inf=1e7;
int n,m,H,S,T,cnt,fir[N],cur[N],dep[N],nxt[M],go[M],val[M],maxflow;
queue<int> Q;
inline void Add(int u,int v,int w){
	nxt[++cnt]=fir[u];
	fir[u]=cnt;
	go[cnt]=v;
	val[cnt]=w;
}
inline bool bfs(){
	for(int i=S;i<=T;i++) dep[i]=-1;
	dep[S]=0;
	Q.push(S);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int e=fir[u];e;e=nxt[e]){
			int v=go[e];	
			if(dep[v]==-1&&val[e]>0){
				dep[v]=dep[u]+1;
				Q.push(v);
			}			
		}		
	}
	if(dep[T]==-1) return 0;
	else return 1;
}
int dfs(int u,int flow){
	if(u==T) return flow;
	for(int &e=cur[u];e;e=nxt[e]){//当前弧优化
		int v=go[e];
		if(dep[v]==dep[u]+1&&val[e]>0){
			int f=dfs(v,min(flow,val[e]));
			if(f>0){
				val[e]-=f;val[e^1]+=f;	
				return f;
			}			
		}		
	}	
	return 0;
}
void Dinic(){
	while(bfs()){
		for(int i=S;i<=T;i++) cur[i]=fir[i];
		while(int d=dfs(S,inf)){
			maxflow+=d;
		}			
	}	
}
int main(){
	H=read();
	while(H--){
		cnt=1;maxflow=0;
		memset(fir,0,sizeof(fir));//初始化
		n=read();m=read();	
		S=0;T=n+n+1;
		for(int i=1;i<=n;i++)
			Add(S,i,1),Add(i,S,0);
		for(int i=1;i<=n;i++)
			Add(i+n,T,1),Add(T,i+n,0);	//i+n表示出点
		for(int i=1;i<=m;i++){
			int u=read(),v=read();	
			Add(u,v+n,1);Add(v+n,u,0);
		}
		Dinic();
		printf("%d\n",n-maxflow);//注意答案是n-最大流
	}	
	return 0;
}
```

---

## 作者：天上一颗蛋 (赞：3)

**有向无环图（DAG）的最小路径覆盖**的模板题。

定义：在一个有向图中，找出最少的路径，使得这些路径经过了所有的点。

由题意可得这是一个有向图，而路径不能相交，于是我们知道这是无向图的不相交最小路径覆盖问题

我们把所有的点拆成两个，当两点之间有路径时，我们在u与v'之间建一条容量为1的边，利用二分图的思想，最大流数即为减去的路径数。

**求法：最小路径条数 = 点数 - 分裂图最大流数**

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;
int RD(){
    int out = 0,flag = 1;char c = getchar();
    while(c < '0' || c >'9'){if(c == '-')flag = -1;c = getchar();}
    while(c >= '0' && c <= '9'){out = out * 10 + c - '0';c = getchar();}
    return flag * out;
    }
const int maxn = 10019,INF = 1e9;
int T,num,nr;
int head[maxn],nume = 1;
struct Node{
    int v,dis,nxt;
    }E[maxn << 3];
void add(int u,int v,int dis){
    E[++nume].nxt = head[u];
    E[nume].v = v;
    E[nume].dis = dis;
    head[u] = nume;
    }
int maxflow,s,t;
int d[maxn];
bool bfs(){
	queue<int>Q;
	memset(d,0,sizeof(d));
	d[s] = 1;
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front();Q.pop();
		for(int i = head[u];i;i = E[i].nxt){
			int v = E[i].v;
			if(!d[v] && E[i].dis){
				d[v] = d[u] + 1;
				Q.push(v);
				if(v == t)return 1;
				}
			}
		}
	return 0;
	}
int Dinic(int u,int flow){
	if(u == t)return flow;
	int rest = flow,k;
	for(int i = head[u];i;i = E[i].nxt){
		int v = E[i].v;
		if(d[v] == d[u] + 1 && E[i].dis){
			k = Dinic(v,min(rest,E[i].dis));
			if(!k)d[v] = 0;
			E[i].dis -= k;
			E[i ^ 1].dis += k;
			rest -= k;
			}
		if(!rest)break;
		}
	return flow - rest;
	}
void init(){
	memset(head,0,sizeof(head));
	nume = 1;
	s = 1026,t = s + 1;
	maxflow = 0;
	for(int i = 1;i <= num;i++){
		add(s,i << 1,1);
		add(i << 1,s,0);
		add(i << 1 | 1,t,1);
		add(t,i << 1 | 1,0);
		}
	}
int main(){
	T = RD();
	while(T--){
		num = RD();nr = RD();
		init();
		int u,v;
		for(int i = 1;i <= nr;i++){
			u = RD();v = RD();
			add(u << 1,v << 1 | 1,1);add(v << 1 | 1,u << 1,0);
			}
		int flow = 0;
		while(bfs())while(flow = Dinic(s,INF))maxflow += flow;
		printf("%d\n",num - maxflow);
		}
	return 0;
	}
```

---

## 作者：xixiup (赞：2)

## 思路分享

我们可以考虑对于每个交叉口 $i$，我们将其拆成两个点 $i_1$ 与 $i_2$，我们连接一条边 $u \rightarrow v$ 就相当于连接边 $u_1-v_2$，这样我们就可以建一个二分图。

为什么要建二分图呢？考虑二分图的最大匹配。

对于点 $i_1$，这个点只能连接一条边，我们考虑这个含义：设这条边指向 $j_2$，表示有一个伞兵在点 $i$ 只能去一个其他节点，且目前我们选择让他去 $j$ 节点。

对于点 $i_2$，这个点也只能连一条边，我们考虑这个含义：设这条边由 $j_1$ 过来，表示只有一个伞兵能来点 $i$，且目前我们让伞兵从点 $j$ 过来。

故考虑最大匹配，我们设最大匹配为 $x$，则我们最后的答案就是 $n-x$，为什么呢？

因为我们设初始状态就是每一个点放一个伞兵，则答案为 $n$，那么对于每一条边的匹配，我们就可以看作是有一个伞兵移动了 $1$ 个街区的距离，取代了一个伞兵的位置，由于上文提到的性质，我们的答案肯定是合法的。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,maxm=100005;
int n,m,vis[maxn],pd[maxn];
int cnt,bg[maxn],ne[maxm],to[maxm];
void add(int x,int y){
	cnt++;
	ne[cnt]=bg[x];
	to[cnt]=y;
	bg[x]=cnt;
}
bool dfs(int x){//二分图匹配
	for(int i=bg[x];i;i=ne[i]){
		int y=to[i];
		if(vis[y]==0){
			vis[y]=1;
			if(pd[y]==0||dfs(pd[y])){
				pd[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		memset(bg,0,sizeof(bg));//记得清空
		memset(pd,0,sizeof(pd));
		cnt=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);//加边
		}
		int ans=n;
		for(int i=1;i<=n;i++){//匹配
			memset(vis,0,sizeof(vis));
			ans-=dfs(i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：SforyeverQ (赞：1)

### 本题一道二分图求最大匹配问题（~~就是一道模板题~~）。
---
## 分析数据可以用编集数组


```
#include <cstdio>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int f[1000][1000],n,m;
bool dis[1000];
int match[1000];

int dfs(int x)
{
	for(int i=1;i<=n;i++)
	{
		if(dis[i]&&f[x][i])
		{
			dis[i]=false;
			if(match[i]==0||dfs(match[i]))
			{
				match[i]=x;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		memset(f,0,sizeof(f));
		memset(match,0,sizeof(match));
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			f[x][y]=1;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			memset(dis,true,sizeof(dis));
			ans+=dfs(i);
		}
		cout<<n-ans<<endl;
	}
}


```


---

## 作者：Plus_Ultra (赞：0)

### 题解：

这道题看着很难，实际是一道大水题，蒟蒻我一遍就A了.

不扯了，说解法：

1. 稍微思考一下，就可以得出这道题要求什么：有向无环图的最小路径点覆盖.

2. 有向无环图的最小路径点覆盖：

   - 给定一张DAG(有向无环图)，要求用最少的简单路径（互不相交），覆盖DAG上的所有顶点（每个顶点恰好被覆盖一次），这个问题被称为有向无环图的最小路径点覆盖.
  

3. 引出定理：DAG的最小路径点覆盖包含的路径条数 = n - 拆点二分图的最大匹配数.（别问我为啥蒟蒻也不知道QwQ).

4. 拆点二分图：

   - 把每个点拆成编号为 i 和 i + n 的两个点.建立一张新的二分图， 1 ~ n 是左部子集， n + 1 ~ 2n 是右部子集.对原图的每条有向边 (u,v) ，在二分图的左部子集 u 与 右部子集 v + n 之间连边.这样得到的二分图成为原图的拆点二分图.

5. 于是我们可以用匈牙利算法来求解这个问题.

6. [不懂匈牙利算法的盆友看这里！！！](https://www.luogu.org/blog/OnePunchManGO/solution-p3386)

下面上代码（我知道各位大佬也不需要代码）：

```
#include<iostream>
#include<cstring>

#define N 250
#define M 15000

using namespace std;

int T,n,m,x,y,mat[N],vis[N],ans;
int edge[M],nxt[M],head[M],tot;//数组要开够啊qwq 

void add(int x,int y)//邻接表 
{
	edge[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

int match(int x)//找匹配 
{
	for(int i=head[x];i;i=nxt[i])//遍历相连边 
	{
		int y=edge[i];
		if(!vis[y])//没有访问过 
		{
			vis[y]=1;
			if(!mat[y]||match(mat[y]))//还没有匹配或者能找到替换路 
			{
				mat[y]=x;//匹配 
				return 1;//找到 
			}
		}
	}
	return 0;
}

int main()
{
	cin>>T;
	
	while(T--)
	{
		memset(mat,0,sizeof(mat));tot=0;
		memset(head,0,sizeof(head));//初始化 
		cin>>n>>m; ans=0;
		for(int i=1;i<=m;i++)
		{
			cin>>x>>y;
			add(x,y+n);//这里是拆点操作 
		}
		for(int i=1;i<=n;i++)
		memset(vis,0,sizeof(vis)),ans+=match(i);//记得初始化哟 
		cout<<n-ans<<endl;//定理 
	}
	
	return 0;
} 
```

### [Plus Ultra!!!](https://www.luogu.org/blog/OnePunchManGO/)

---

## 作者：览遍千秋 (赞：0)

二分图最小点覆盖板子题。

---

## 定理

定理：拆点二分图最小点覆盖=拆点前图的点数$n$-拆点二分图最大匹配数。

至于证明，请右转百度。

---

## 拆套路点

将每一个点拆分为入点和出点，一条从$x$到$y$的边，等价于从$x$的出点联向$y$的入点。

显然，出点和出点之间没有边，入点和入点之间没有边，故符合二分图的性质。

样例的$\mathrm {Test Case1}$原图如下：

![]( https://cdn.luogu.com.cn/upload/pic/70729.png)

样例的拆点二分图如下：

![]( https://cdn.luogu.com.cn/upload/pic/70732.png)

显然，在左侧加入一个超级源点$S$，右侧加入一个超级汇点$T$即可。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 503
#define maxm 100003
int qwq,n,m,x,y,t,S,T;
int d[maxn],Head[maxn],Next[maxm],w[maxm],v[maxm],tot,ans;

template<typename Tp>
void read(Tp &x){
	x=0;int fh;char ch=1;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

void add(int x,int y,int z){
	v[++tot]=y,Next[tot]=Head[x],Head[x]=tot,w[tot]=z;
}

void Reset(){
	tot=1;ans=0;
	memset(Head,0,sizeof(Head));
	memset(Next,0,sizeof(Next));
}

void Init(){
	read(n);read(m);S=n+n+1,T=n+n+2;
	for(register int i=1;i<=n;i++){
		add(S,i,1);add(i,S,0);add(i+n,T,1);add(T,i+n,0);
	}
	for(register int i=1;i<=m;i++){
		read(x);read(y);
		add(x,y+n,1);add(y+n,x,0);
	}
}

bool bfs(){
	memset(d,0,sizeof(d));
	queue<int>q;q.push(S);d[S]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=Head[x];i;i=Next[i]){
			if(d[v[i]]||!w[i]) continue;
			q.push(v[i]);d[v[i]]=d[x]+1;
			if(v[i]==T) return true;
		}
	}
	return false;
}

int dfs(int x,int flow){
	if(x==T) return flow;
	int rest=flow;
	for(int i=Head[x];i&&rest;i=Next[i]){
		if(d[v[i]]!=d[x]+1||!w[i]) continue;
		int k=dfs(v[i],min(rest,w[i]));
		if(!k) d[v[i]]=0;
		else{
			w[i]-=k,w[i xor 1]+=k;
			rest-=k;
		}
	}
	return flow-rest;
}

void Solve(){
	while(bfs()){
		while((t=dfs(S,0x3f3f3f3f))) ans+=t;
	}
	printf("%d\n",n-ans);
}

int mian(){
	read(qwq);
	while(qwq--){
		Reset();
		Init();
		Solve();
	}
	return 0;
}
```

---

强烈推荐一篇关于网络流的博客:[传送门](https://www.xht37.com/%e4%ba%8c%e5%88%86%e5%9b%be%e4%b8%8e%e7%bd%91%e7%bb%9c%e6%b5%81-%e5%ad%a6%e4%b9%a0%e7%ac%94%e8%ae%b0/)

---

## 作者：Mr_浓氨 (赞：0)

对于刚学完二分图最大匹配的juruo来说,这道题就可以来练练手,我就用匈牙利算法来做一下,这道题只要仔细思考一下就知道这道题的最少路径覆盖就等于相当于建一个二分图左右两边的的点数相等,两个点之间建一条边最后求最大匹配,用点数减去就行了

下面贴代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<stack>
#define ll long long
using namespace std;
vector<int>a[10001];
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int check[10001];
bool b[10001];
inline bool dfs(int u)
{
	for(int i=0;i<a[u].size();i++)
	{
		if(!b[a[u][i]])
		{
			b[a[u][i]]=true;
			if(check[a[u][i]]==0||dfs(check[a[u][i]]))
			{
				check[a[u][i]]=u;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	int T=read();
	while(T--)
	{
		memset(a,0,sizeof(a));
		memset(check,0,sizeof(check));
		int n=read(),e=read();
		for(int i=1;i<=e;i++)
		{
			int x=read(),y=read();
			a[x].push_back(y);
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			memset(b,false,sizeof(b));
			if(dfs(i))
			{
				sum++;
			}
		}
		printf("%d\n",n-sum);
	}
	return 0;
}

```

QAQ,我是不是太菜了,从不压行的我

---

