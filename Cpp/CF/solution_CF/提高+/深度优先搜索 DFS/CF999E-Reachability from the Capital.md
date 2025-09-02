# Reachability from the Capital

## 题目描述

在 Berland 有 $n$ 座城市和 $m$ 条道路，每条道路连接着一对城市。

Berland 的道路都是**单向**的

为了能让首都能够到达所有的城市，最少需要新修建多少新道路？

新道路也是单向的

## 说明/提示

样例 1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/cfa72c5c5f72e8ccb5babda1e509efae921c1e73.png)

例如，您可以添加道路 ( 6, 4 ) , ( 7 , 9 ) , ( 1 , 7 )，以使从 $s = 1$ 可到达所有城市。
样例 2：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/62d78c6df2be4fcc0d6c17ba856e4ad627c47d5f.png)

在此样例中，您可以添加道路（5 , 1），（5 , 2），（5 , 3），（5 , 4）中的任何一条，以使可从 $s = 5$ 到达所有城市。

## 样例 #1

### 输入

```
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4 5
1 2
2 3
3 4
4 1
```

### 输出

```
1
```

# 题解

## 作者：attack (赞：7)

emmmmm。本蒟蒻是真的看不懂楼下的大佬在讲什么，，为什么连set都用上了qwq。。。

这题不应该是很套路的先tarjan一边

那么对于联通块中的点都是互相可达的。

这样我们只要统计一下入度为$0$的点输出就好了。。


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
const int MAXN = 1e6 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, M, S;
struct Edge {
    int u, v, nxt;
}E[MAXN];
int head[MAXN], num = 1;
inline void AddEdge(int x, int y) {
    E[num] = (Edge){x, y, head[x]};
    head[x] = num++;
}
stack<int>s;
int dfn[MAXN], low[MAXN], color[MAXN], colornum = 0, tot = 0, vis[MAXN], siz[MAXN];
void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    s.push(x);
    vis[x] = 1;
    for(int i = head[x]; i != -1; i = E[i].nxt) {
        int to = E[i].v;
        if(!dfn[to]) tarjan(to), low[x] = min(low[x], low[to]);
        else if(vis[to]) low[x] = min(low[x], dfn[to]);
    }
    if(dfn[x] == low[x]) {
        int h;
        colornum++;
        do {
            h = s.top(); s.pop();
            color[h] = colornum;
            vis[h] = 0;
        }while(h != x);
    }
}
bool happen[MAXN];
vector<int> v[MAXN];
int ans = 0;
int inder[MAXN];
int main() {
#ifdef WIN32
    //freopen("a.in", "r", stdin);
#endif    
    memset(head, -1, sizeof(head));
    N = read(); M = read(); S = read();
    for(int i = 1; i <= M; i++) {
        int x = read(), y = read();
        AddEdge(x, y);
    }
    for(int i = 1; i <= N; i++) 
        if(!color[i])
            tarjan(i);
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= N; i++) 
        for(int j = head[i]; j != -1; j = E[j].nxt) 
            if(color[E[j].u] != color[E[j].v])
                inder[color[E[j].v]]++;
    for(int i = 1; i <= colornum; i++)
        if(inder[i] == 0)
            ans++;
    if(inder[color[S]] == 0) ans--;
    printf("%d", ans);
    return 0;
}
```

---

## 作者：MyukiyoMekya (赞：5)

如果一个强连通分量内的一个点能被 $s$ 到达，那么强连通分量里所有点都被 $s$ 到达，所以先缩点

缩完点建完新图，我们看到的基本上就只有这么三种情况的连通块

```
A -> B -> D       E -> F -> G        H -> I -> J
     ^                                    |
     |                                    V
     C                                    K
```

我们假设这三种情况都不能被 $s$ 到达

第一种多个入度为0的点，必须要从 $s$ 往 $A$ 和 $C$ 各连一条边才行

第二种一条链，$s$ 往 $E$ 连边就行

第三种只有一个入度为 0 的点，那么 $s$ 往 $H$ 连边就行

那么这里就发现了规律了，对于一个不能被 $s$ 所到达的连通块，**其所要新加边的数量为其中入度为 0 点的数量**

那么就在新图中先从 $s$ 所在新图中的点开始 dfs 一遍标记掉能到达的点

然后答案就是新图中没被标记过并且入度为 0 的点数

```cpp
// This code writed by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=5050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2],nE[MaxN<<2];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],nhd[MaxN],en,nen,n,m;
int dfn[MaxN],low[MaxN],dep;
int col[MaxN],scc;
int sta[MaxN],top;
bool instack[MaxN];
bool vis[MaxN];
int deg[MaxN];
inline void adde(int u,int v)
{
	++en;
	E[en]=(Edge){hd[u],v};
	hd[u]=en;
	return;
}
inline void nadde(int u,int v)
{
	++nen;
	nE[nen]=(Edge){nhd[u],v};
	nhd[u]=nen;
	return;
}
inline void tarjan(int u)
{
	dfn[u]=low[u]=++dep;
	sta[top++]=u;
	instack[u]=true;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		++scc;
		do
		{
			--top;
			instack[sta[top]]=false;
			col[sta[top]]=scc;
		}while(sta[top]!=u);
	}
	return;
}
inline void dfs(int u,int fa)
{
	vis[u]=true;
	for(int i=nhd[u];~i;i=nE[i].nxt)
	{
		reg int v=nE[i].to;
		if(v==fa||vis[v])
			continue;
		dfs(v,u);
	}
	return;
}
signed main(void)
{
	memset(hd,-1,sizeof hd);
	memset(nhd,-1,sizeof nhd);
	int s;
	reg int u,v;
	cin>>n>>m>>s;
	for(int i=1;i<=m;++i)
	{
		read(u);read(v);
		adde(u,v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(int u=1;u<=n;++u)
		for(int i=hd[u];~i;i=E[i].nxt)
		{
			reg int v=E[i].to;
			if(col[u]==col[v])
				continue;
			nadde(col[u],col[v]);
			++deg[col[v]];
		}
	dfs(col[s],0);
	reg int ans=0;
	for(int i=1;i<=scc;++i)
		if(!vis[i]&&!deg[i])
			++ans;
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：LSG_waterlyf (赞：4)

### 我的方法$:$ $dfs+$贪心。

首先我们先对于起点$dfs$一次，把所有直接与起点联通的点做个标记，将这些点删去后，变成了若干个联通块(不是严格意义上的，感性理解下)。也就是说从每个点出发，有一个可以到达的点集$s_i$.我们找出每个点$i$的$s_i$.按从大到小排序，依次选取，并把集合$s_i$中的每个点做个标记.

为什么是对的？

因为设$|s_i|>|s_j|$，则$j$有可能是$i$的后继节点，因而先选$i$不会更亏。

贴上代码(比大多数$tarjan$写法方便许多)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 5010
int n,m,cnt,h[N],rt,vis[N],ans,num[N],in[N];
struct edge{int v,nxt;}e[N*2];
void add(int u,int v){e[++cnt]=(edge){v,h[u]};h[u]=cnt;}
void dfs1(int u)
{
	if(vis[u]) return;vis[u]=1;
	for(int i=h[u];i;i=e[i].nxt) dfs1(e[i].v);
}
int dfs2(int u)
{
	if(vis[u]||in[u]) return 0;num[u]=in[u]=1;
	for(int i=h[u];i;i=e[i].nxt)num[u]+=dfs2(e[i].v);
	return num[u];
}
struct nod
{
	int id,w;
	bool operator<(const nod&b)const{return w>b.w;}
}p[N];
int main()
{
	cin>>n>>m>>rt;
	for(int i=1,u,v;i<=m;i++)
	  scanf("%d%d",&u,&v),add(u,v);
	dfs1(rt);
	for(int i=1;i<=n;i++)
	{
		memset(in,0,sizeof(in));
		dfs2(i);
	}
	for(int i=1;i<=n;i++)p[i]=(nod){i,num[i]};
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	  if(!vis[p[i].id]) dfs1(p[i].id),ans++;
	cout<<ans;
	return 0;
}
```


---

## 作者：让风忽悠你 (赞：2)

## CF999E Reachability from the Capital

[原题](https://www.luogu.com.cn/problem/CF999E)

## 题意
- 给出一个 n 个点 m 条边的 有向图，求加多少边才能使 s 点能到达图上的任意一点。

## 做法
- 先求出图上的强连通分量，因为强连通分量中的每个点都可以互相到达。
- 统计每个强连通分量的入度，入度为 0 时说明没有点能到达这个强连通分量，这时就需要加一条边。
- 当 s 点所在的强连通分量入度为 0 时答案需要减 1，因为要求的是 s 点能到达所有点，并不需要其他点能到达 s 点。

## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 5005
#define M 1000005

using namespace std;

int n,m,s,idx,tot,top,bcnt,ans;
int head[N],dfn[N],low[N],sta[N],belong[N],into[N];
int u[N],v[N];
bool vis[N];
struct node{
	int next,to;
}e[M];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

inline void add(int u,int v){
	e[++tot].to=v;
	e[tot].next=head[u];
	head[u]=tot;
}

void tarjan(int u){
	dfn[u]=low[u]=++idx;
	vis[u]=1;
	sta[++top]=u;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		bcnt++;
		int v=-1;
		while(u!=v){
			v=sta[top--];
			vis[v]=0;
			belong[v]=bcnt;
		}
	}
}

int main(){
	n=read(); m=read(); s=read();
	for(int i=1;i<=m;i++){
		u[i]=read(); v[i]=read();
		add(u[i],v[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);//求强连通分量 
	for(int i=1;i<=m;i++)
		if(belong[u[i]]!=belong[v[i]])
			into[belong[v[i]]]++;//统计入度 
	for(int i=1;i<=bcnt;i++) if(!into[i]) ans++;
	if(!into[belong[s]]) ans--;//s 点所在的强连通分量入度为 0 
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Farkas_W (赞：2)

$\quad$前置芝士：Tarjan缩点，建议做做模板题([P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387))

$$\text{关于题意}$$

$\quad$给定一个有向图，求要使一个点 $t$ 能够到达其他所有点还需加多少边？

$\quad$因为在一个强连通分量中，每个点都可以到达其他所有点，所以考虑缩点，将一个强连通分量中所有点看做一个点，再做其他操作。

$\quad$缩点之后图就变成了[$DAG$(有向无环图)](https://baike.baidu.com/item/%E6%9C%89%E5%90%91%E6%97%A0%E7%8E%AF%E5%9B%BE/10972513?fr=aladdin)，然后考虑每一个点的入度情况(缩点后)，因为点 $t$ 要能到达其他每一个点，所以除了点 $t$ 所在的强连通分量之外，其他所有点的入度必须大于$0$，通过找规律就可以发现答案就是缩点后入度为 $0$ 且不是点 $t$ 所在的强连通分量的点的数量。(因为即使t所在的强连通分量入度为0，也不需要连边)

$\quad$如果还不能理解就看代码吧，注释都在代码里。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#define int long long
#define re register int
#define il inline
#define next ne
using namespace std;
il int read()					     //快速读入
{
	int x=0,f=1;char ch=getchar();
	while(isdigit(ch)==0&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch-'0'),ch=getchar();
	return x*f;
}
const int N=5e3+5;
int n,m,dfn[N],low[N],c[N],f[N*2],s[N],l[N]
int next[N*2],go[N*2],head[N],tot,cnt,ans,t;
il void Add(int x,int y)  			     //链式前向星存图，记录每条边的端点u，v，之后要计算每个点的入度
{
	next[++tot]=head[x];
	head[x]=tot;
	f[tot]=x;
	go[tot]=y;
}
stack<int>q;					     //个人喜欢用stack栈，不用数组模拟栈
il void Tarjan(int x)				     //Tarjan缩点板子
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
		s[c[0]]=1;
		while(q.top()!=x)
		{
			c[q.top()]=c[0];
			s[c[0]]++;
			q.pop();
		}
		q.pop();
	}
}
signed main()
{
	n=read();m=read();t=read();
	tot=cnt=0;
	for(re i=1;i<=m;i++)
	{
		int x=read(),y=read();
		Add(x,y);
	}
	for(re i=1;i<=n;i++)
	if(!dfn[i])Tarjan(i);
	if(c[0]==1){printf("0\n");return 0;}	//如果只有一个强连通分量，不需要加边
	for(re i=1;i<=m;i++)
	{
		int x=c[f[i]],y=c[go[i]];
		if(x!=y)l[y]++; 		//记录每个点的入度（缩点后）
	}
	for(re i=1;i<=c[0];i++)			//条件1：入度为0   条件2：不是t所在的强连通分量
	if(!l[i]&&i!=c[t])ans++;		//统计答案
	printf("%lld\n",ans);
	return 0;
}
```

$\quad$如果觉得我写得好的，不妨点个赞呗

---

## 作者：___new2zy___ (赞：2)

## 题解 CF999E 【Reachability from the Capital】

题目传送门:

https://www.luogu.org/problemnew/show/CF999E

真是奇怪，我竟然是最优解（不敢相信）

还是大概来说一下做法吧= =

==========================================

题目大意:(其实楼下也有，我是自己总结的)

	有n个节点m条边，边都是单向的，请你添加最少的边使得起点s到其他与其他每一个点之间都能互相到达

emmm...这题一看就是一个缩点啊= =

（别问我怎么看出来的）（逃

其实对于原有的m条边相连的一些点，如果之前他们已经形成了强连通分量(scc)，那么它们之前就可以相互到达(不用修路),对于这些点我们可以把它们“缩”成一个“点”，这其实就是Tarjian缩点的思想，至于实现吗。。。缩点模板题链接:

[缩点模板题](https://www.luogu.org/problemnew/show/P3387)

其实luogu里还有很多缩点的模板题,自己去找找吧，都不难的

那么如果你会了缩点，这个题只要缩完点之后统计一下入度就行了(让强连通分量之间连边)

直接粘板子~~~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=1e9+7;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
const int maxn=5007;
const int maxm=5007;
struct Edge
{
    int next,from,to;
}p[maxm];
struct point
{
    int low,dnf,vis,fa,in;
}A[maxn];
int n,m,cnt,sum_scc,tot,S;
int Stack[maxn],top,ans,head[maxm];
inline void add_edge(int x,int y)//加边
{
    cnt++;
    p[cnt].from=head[x];
    head[x]=cnt;
    p[cnt].next=x;
    p[cnt].to=y;
}
inline void Tarjian(int x)//Tarjian缩点
{
    A[x].dnf=A[x].low=++tot;
    A[x].vis=1,Stack[++top]=x;
    for(int i=head[x];i;i=p[i].from)
        {
            int y=p[i].to;
            if(!A[y].dnf)
                Tarjian(y),A[x].low=min(A[x].low,A[y].low);
            else if(A[y].vis)
                    A[x].low=min(A[x].low,A[y].dnf);
        }
    if(A[x].dnf==A[x].low)
        {
            int y;
            sum_scc++;
            while(y=Stack[top--])
                {
                    A[y].vis=0;
                    A[y].fa=sum_scc;
                    if(x==y)break;
                }
        }
}
int main()
{
    n=read(),m=read(),S=read();
    for(int i=1;i<=m;i++)
        {
            int x=read(),y=read();
            add_edge(x,y);
        }
    for(int i=1;i<=n;i++)
        if(!A[i].dnf)Tarjian(i);
    for(int i=1;i<=m;i++)//统计入度
        {
            int x=A[p[i].next].fa,y=A[p[i].to].fa;
            if(x!=y)A[y].in++;
        }
    for(int i=1;i<=sum_scc;i++)
    	//没有入度的scc个数++
        if(!A[i].in)ans++;
    if(!A[A[S].fa].in)ans--;
    //特判,起点所在的scc如果没有入度那么答案-1
    printf("%d\n",ans);
    return 0;
}
```

好了，这个题大概就这样了（不要怪我讲得少）

最后推广一下我的blog:

https://www.luogu.org/blog/new2zy/

感谢阅读，拜拜~~~


---

## 作者：Schwarzkopf_Henkal (赞：1)

这是一道比较难看出来的 Tarjan 题，如果是有向图而且还不是求最短路的，那往 Tarjan 这方面想总是比较好的。

题目的要求是要求让所有点都从起点可达的最小加边数量。首先我们考虑这样一种情况，如果一个点没有入度，并且还不是起点的话，容易证明至少要连一条向着这个点的边，这个边自然是从起点或是哪个从起点可达的点连起都可以。

这样并不能概括完全，例如要是有环，环内所有点都有入度，但是要是没有向环内连的边，一样是不行的。然后想到缩点，把所有情况都化成第一种情况，可以证明这样是完备的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N,m,s,low[5005],dfn[5005],tot,u[5005];
int v[5005],mk[5005],f[5005],in[5005],ans;
basic_string<int>to[5005];
stack<int>sta;
void dfs(int p){
    dfn[p]=low[p]=++tot;
    mk[p]=1;
    sta.push(p);
    for(int i=0;i<to[p].size();i++){
        if(!dfn[to[p][i]]){
            dfs(to[p][i]);
            low[p]=min(low[p],low[to[p][i]]);
        }else if(mk[to[p][i]])
            low[p]=min(low[p],dfn[to[p][i]]);
    }
    if(dfn[p]==low[p]){
        int lst=1e9;
        N++;
        while(lst!=p){
            mk[sta.top()]=0;
            f[sta.top()]=N;
            lst=sta.top();
            sta.pop();
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u[i],&v[i]);
        to[u[i]]+=v[i];
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
    for(int i=1;i<=m;i++)
        if(f[u[i]]!=f[v[i]])
            in[f[v[i]]]++;
    for(int i=1;i<=N;i++)
        if(in[i]==0&&i!=f[s])
            ans++;
    printf("%d",ans);
}
```

---

## 作者：lx_zjk (赞：1)

这道题是道$tarjan$模板题

如果这个图联通 每个点的入度都不为一

要是这个图联通 那么就必须使入度为0的点加边

那么这道题目就是统计入度为0的点数 然后要减去$in[ssc_num[s]] == 0$ 

然后输出答案就行了

代码实现比较简单

# code

```cpp
//
//  CF999E Reachability from the Capital
//  Tarjan
//
//  Created by 周俊康 on 2019/10/2.
//  Copyright © 2019 周俊康. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

typedef unsigned long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << ' = ' << x << std::endl

inline int read() {
    int f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_M = 5000 + 5;

struct EDGE {
    int to, next;
} edge[MAX_M];

int head[MAX_M], cnt;

void addedge (int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

int dfn[MAX_M], low[MAX_M], vis[MAX_M], s[MAX_M], top, f[MAX_M];

int n, m, st, scc_num[MAX_M], in[MAX_M], out[MAX_M], scc_cnt;

void tarjan (int u) {
    dfn[u] = low[u] = ++cnt;
    vis[u] = 1; s[++top] = u;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++ scc_cnt;
        while (s[top + 1] != u) {
            scc_num[s[top]] = scc_cnt;
            vis[s[top -- ]] = 0;
        }
    }
}

int main () {
    n = read(); m = read(); st = read();
    for (int i = 1; i <= m; i ++ ) {
        int u = read(), v = read();
        addedge (u, v);
    }
    cnt = 0;
    for (int i = 1; i <= n; i ++ ) {
        if (!dfn[i]) tarjan(i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++ ) {
        cout << i << " " << scc_num[i] << endl;
    }
    for (int u = 1; u <= n; u ++ ) {
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;
            if (scc_num[u] != scc_num[v]) in[scc_num[v]] ++ ;
        }
    }
    for (int i = 1; i <= scc_cnt; i ++ ) {
        ans += (in[i] == 0);
    }
    cout << (ans - (in[scc_num[st]] == 0)) << endl;
}

```

---

## 作者：GIFBMP (赞：0)

很经典的 tarjan 题。

首先，对于每个强连通分量中的点，它们之间一定能两两互达，于是我们考虑缩点。

缩完点后很显然只要计算有多少个入度为 $0$ 的点即可。

细节：如果 $col_s$ 的入度为 $0$，就要去除它的贡献。

Code:

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std ;
const int MAXN = 5e3 + 10 ;
int min (int a , int b) {
	return a < b ? a : b ;
}
int n , m , s , dfn[MAXN] , low[MAXN] , stack[MAXN] , top , cnt , col[MAXN] , d[MAXN] , cntc , ans ;
bool inq[MAXN] ;
vector <int> G[MAXN] ;
void tarjan (int x) {
	dfn[x] = low[x] = ++cnt ;
	stack[++top] = x ;
	inq[x] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (!dfn[v]) tarjan (v) , low[x] = min (low[x] , low[v]);
		else if (inq[v]) low[x] = min (low[x] , dfn[v]) ;
	}
	if (dfn[x] == low[x]) {
		cntc++ ;
		while (stack[top + 1] != x) {
			col[stack[top]] = cntc ;
			inq[stack[top--]] = 0 ;
		}
	}
}
int main () {
	scanf ("%d %d %d" , &n , &m , &s) ;
	for (int i = 1 ; i <= m ; i++) {
		int u , v ;
		scanf ("%d %d" , &u , &v) ;
		G[u].push_back (v) ; 
	}
	for (int i = 1 ; i <= n ; i++)	
		if (!dfn[i]) tarjan (i) ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 0 ; j < G[i].size () ; j++) {
			int v = G[i][j] ;
			if (col[i] == col[v]) continue ;
			d[col[v]] ++ ; 
		}
	for (int i = 1 ; i <= cntc ; i++)
		if (!d[i]) ans++ ;
	if (!d[col[s]]) ans-- ;
	printf ("%d" , ans) ;
	return 0 ;
}
```

---

## 作者：chihik (赞：0)


显然，在一个强联通分量中，只要有一个城市与$s$联通，那么整个分量就与$s$联通。

于是我们可以缩点，统计它的入度。如果入度为$0$，我们就从$s$向这个缩点连一条边，如果入度不为0，说明其他城市可以到达它，我们就不需要单独连边。

最后，注意特判与$s$在同一强联通分量的点。

```cpp
#include <cstdio>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

const int MAXN = 5000;
int n , m , s , u , v;
vector< int > Graph[ MAXN + 5 ];

int dfn[ MAXN + 5 ] , low[ MAXN + 5 ] , depth , cnt;
int bel[ MAXN + 5 ] , In[ MAXN + 5 ];
bool is[ MAXN + 5 ];
stack< int > S;
void Tarjan( int u ) {
	dfn[ u ] = low[ u ] = ++ depth;
	S.push( u ) , is[ u ] = 1;
	
	int v;
	for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
		v = Graph[ u ][ i ];
		if( !dfn[ v ] ) {
			Tarjan( v );
			low[ u ] = min( low[ u ] , low[ v ] );
		}
		else if( is[ v ] )
			low[ u ] = min( low[ u ] , dfn[ v ] );
	}
	if( dfn[ u ] == low[ u ] ) {
		++ cnt;
		do{
			v = S.top( );
			S.pop( ); is[ v ] = 0;
			bel[ v ] = cnt;
		}while( u != v );
	}
}

int main( ) {
	scanf("%d %d %d",&n,&m,&s);
	for( int i = 1 ; i <= m ; i ++ ) {
		scanf("%d %d",&u,&v);
		Graph[ u ].push_back( v );
	}
	for( int i = 1 ; i <= n ; i ++ )
		if( !dfn[ i ] ) Tarjan( i );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j < Graph[ i ].size( ) ; j ++ ) {
			int u = bel[ i ] , v = bel[ Graph[ i ][ j ] ];
			if( u != v ) In[ v ] ++;
		}
	int Ans = 0;
	for( int i = 1 ; i <= cnt ; i ++ )
		if( !In[ i ] && i != bel[ s ] ) Ans ++;
	printf("%d\n",Ans);
	return 0;
}
```


---

