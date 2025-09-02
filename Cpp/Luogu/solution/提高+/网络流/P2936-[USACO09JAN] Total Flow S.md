# [USACO09JAN] Total Flow S

## 题目描述

**请注意，题面中并没有说明水管是单向的还是双向的（虽然应该是双向的）。数据保证无论将水管视作单向还是双向得到的结果相同。**

农夫约翰总是希望他的奶牛有足够的水，因此他绘制了一张农场上连接水井和谷仓的 $N（1 \leq N \leq 700$）根水管的地图。他惊讶地发现这些不同尺寸的水管连接得杂乱无章。他想计算水管的流量。

两个串联的水管允许的水流量是两个水管流量值中的最小值。例如，一个流量为 $5$ 的水管连接到一个流量为 $3$ 的水管，可以逻辑上简化为一个流量为 $3$ 的水管：

```plain
+---5---+---3---+    ->    +---3---+
```

类似地，并联的水管允许的水流量是它们流量的总和：

```plain
   +---5---+
---+       +---    ->    +---8---+
   +---3---+
```

最后，一个没有连接到其他任何东西的水管可以被移除，它对最终的总流量没有贡献：

```plain
   +---5---+
---+               ->    +---3---+
   +---3---+--
```

管道网络中的所有水管都可以使用这些方法简化为一个总流量。

给定一张水管的地图，确定从水井 $A$ 到谷仓 $Z$ 的流量。

考虑这个节点名称用字母标记的例子：

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +---3---+---5---+---4---+
                 C       D
```

管道 $BC$ 和 $CD$ 可以合并：

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +-----3-----+-----4-----+
                     D
```

然后 $BD$ 和 $DZ$ 可以合并：

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +-----------3-----------+
```

然后 $BZ$ 的两条路径可以合并：

```plain
         B
A+---3---+---9---+Z
```

最后，$AB$ 和 $BZ$ 可以合并，得到净流量为 $3$：

```plain
A+---3---+Z
```

编写一个程序读取描述为两个端点的水管集合，然后计算从 $A$ 到 $Z$ 的净流量。测试数据中的所有网络都可以使用这里的规则简化。

管道 i 连接两个不同的节点 $a_i$ 和 $b_i$（节点范围均为 $a-z、A-Z$），流量为 $F_i$（$1 \leq F_i \leq 1,000$）。注意，小写和大写的节点名称应视为不同。

形式化题意：求出 $A$ 到 $Z$ 的最大流。

## 说明/提示

@[langmouren](luogu://user/1470994) 提供翻译

## 样例 #1

### 输入

```
5 
A B 3 
B C 3 
C D 5 
D Z 4 
B Z 6 
```

### 输出

```
3 
```

# 题解

## 作者：OraclePi (赞：4)

## 首先感谢@JK_LOVER大犇相助，解决了我的困惑

	简化题意：求A到Z的最大流；

	本题作为网络流的板题，其实也并不是很板，还是考察了一些细节的：
1. 题目上的****管理员注****，其实注了跟没注一样，这是在我的满篇~~WA~~提交下实践出来的，所以duck直接处理建边：
   
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/ggdzvkgo.png)；
   
   
   2.本题使用卡无优化版本的dinic，会T飞7个点，但是其它题解上好像并未出现此问题~~可能是本人码风问题~~；
   
   
30pts代码：
```cpp
#include<bits/stdc++.h>
#define rg register int 
using namespace std;
int N,cnt=1,head[400040],dep[400040];
struct node{
	int nxt;
	int to;
	int w;
}edge[400040];
void add_edge(int u,int v,int w)
{
	edge[++cnt].nxt=head[u];
	edge[cnt].to=v;
	edge[cnt].w=w;
	head[u]=cnt;
}
bool bfs()
{
	memset(dep,0,sizeof dep);
	queue< int >x;x.push(1);
	dep[1]=1;
	while(!x.empty())
	{
		int u=x.front();
		for(rg i=head[u];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(!dep[v]&&edge[i].w)
			{
				dep[v]=dep[u]+1;
				x.push(v);
			}
			if(v==26) return 1;
		}
		x.pop();
	}
	return 0;
}
int dinic(int u,int flow)
{
	if(u==26) return flow;
	int k;int res=flow;
	for(rg i=head[u];i&&res;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(dep[v]==dep[u]+1&&edge[i].w)
		{
			k=dinic(v,min(edge[i].w,res));
			if(!k) dep[v]=0;
			edge[i].w-=k;
			edge[i^1].w+=k;
			res-=k;
		}
	}
	return flow-res;
}
int ans,flo;
signed main()
{
	scanf("%d",&N);
	while(N--)
	{
		char a,b;int w;
		cin>>a>>b>>w;
//		if(a>=97) a-=96;if(b>=97) b-=96;if(a>=65&&a<=90) a-=64;if(b>=65&&b<=90) b-=64;
		add_edge(int(a)-'A'+1,int(b)-'A'+1,w);
		add_edge(int(b)-'A'+1,int(a)-'A'+1,0);
	}
	while(bfs())
	{
		while(flo=dinic(1,INT_MAX)) ans+=flo;
	}
	printf("%d\n",ans);
	return 0;
}
```
100pts代码：
```cpp
#include<bits/stdc++.h>
#define rg register int 
using namespace std;
int N,cnt=1,head[4101],dep[4100];
int ans,flo;
struct node{
    int nxt;
    int to;
    int w;
}edge[11200];
void add_edge(int u,int v,int w)
{
    edge[++cnt].nxt=head[u];
    edge[cnt].to=v;
    edge[cnt].w=w;
    head[u]=cnt;
}
bool bfs()
{
    memset(dep,0,sizeof dep);
    queue< int >x;x.push(1);
    dep[1]=1;
    while(!x.empty())
    {
        int u=x.front();x.pop();
        for(rg i=head[u];i;i=edge[i].nxt)
        {
            int v=edge[i].to;
            if(!dep[v]&&edge[i].w)
            {
                dep[v]=dep[u]+1;
                if(v==26) return 1;
                x.push(v);
            }
        }
    }
    return 0;
}
int cur[4010];
int dinic(int u,int flow)
{
    if(u==26 || flow == 0) return flow;
    int k;int res=0;
    for(rg i=cur[u];i;i=edge[i].nxt)
    {
        cur[u] = i;
        int v=edge[i].to;
        if(dep[v]==dep[u]+1&&edge[i].w)
        {
            k=dinic(v,min(edge[i].w,flow));
            if(!k) continue;
            edge[i].w-=k;
            edge[i^1].w+=k;
            res+=k;flow -=k;
            if(flow == 0) break;
        }
    }
    return res;
}
signed main()
{
    scanf("%d",&N);
    while(N--)
    {
        char a,b;int w;
        cin>>a>>b>>w;
        add_edge(int(a-'A'+1),int(b-'A'+1),w);
        add_edge(int(b-'A'+1),int(a-'A'+1),0);
    }
    while(bfs())
    {
        memcpy(cur,head,sizeof(cur));
        int maxflow = dinic(1,19260817);
        ans += maxflow;
    }
    printf("%d\n",ans);
    return 0;
}
```

%%%，犇篇完结



---

## 作者：7KByte (赞：2)

题目很复杂，图片很抽象，翻译很简略  
----这道题的真实写照  



------------
## 步入正题  
题目仔细阅读一下是不难的：一张网络，求A点到Z点的最大流量  
以至于什么并联串联就是网络流重边和流量限制  
于是我们按照网络流模板来就好了



------------
## Code: 捧上我丑陋无比的dinic

```
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int to,next,data;
}e[100000];
int h[500],d[500],n,s=1,t=26,pop=1;
void add(int x,int y,int dat){
	pop++;
	e[pop].data=dat;e[pop].to=y;
	e[pop].next=h[x];h[x]=pop;
}
queue<int>q;
bool bfs(){
	memset(d,0,sizeof(d));
	while(!q.empty())q.pop();
	q.push(s);d[s]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=e[i].next){
			if(!d[e[i].to]&&e[i].data){
				d[e[i].to]=d[x]+1;
				q.push(e[i].to);
				if(e[i].to==t)return true;
			}
		}
	}
	return false;
}
int dfs(int p,int flow){
	int rest=flow;
	if(p==t)return flow;
	for(int i=h[p];i&&rest;i=e[i].next){
		if(e[i].data&&d[e[i].to]==d[p]+1)
		  {
		  	int k=dfs(e[i].to,min(rest,e[i].data));
		  	if(!k)d[e[i].to]=-1;
		  	e[i].data-=k;e[i^1].data+=k;rest-=k;
		  }
	}
	return flow-rest;
}
int main()
{
	scanf("%d",&n);
	memset(h,0,sizeof(h));
	string a,b;int x,y,z;
	for(int i=1;i<=n;i++){
		cin>>a>>b>>z;
		x=a[0]-'A'+1;y=b[0]-'A'+1;
		//cout<<x<<" "<<y<<endl;
		add(x,y,z);add(y,x,0);
	}
	int ans=0;
	while(bfs())
	  ans+=dfs(s,(1<<30));
	printf("%d\n",ans);
	return 0;
}
```

-----

有兴趣可以去看看模板[P3376](https://www.luogu.org/problemnew/show/P3376)

---

## 作者：pocafup (赞：1)

网络流模板，好多人因为小写字母崩了，这里思路是直接转化字母到数字后再进行连边。

至于重边的处理，开始还在想很复杂的输入中数组记录后加边再进行操作，后面发现其实重边没有影响，因为重边只不过是复杂度稍微高一点，只要n的大小没有到不可理喻的地步就行。

连边的方式大概是将每个字母当做节点连，之后将 ‘A’ 作为起点， ‘Z’ 作为终点进行一个最大流的查找就能找出答案。

为什么这个解法正确呢？因为合并管子代替送水量等价于两条水管分别送水，而串联取最小值其实就是路径中最小水管的容量。

代码：

```
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;
namespace Dinic{
  int n,m,s,t,a,b,head[MAXN],c,tot=1,dep[MAXN],flow;

  struct Edge{
    int u,v,nxt,val;
  }edge[MAXM<<1];

  inline void add(int f, int t, int d){
    edge[++tot].u = f;
    edge[tot].v = t;
    edge[tot].nxt = head[f];
    edge[tot].val = d;
    head[f] = tot;
  }
  inline void addedge(int f,int t, int d){
    add(f,t,d);add(t,f,0);
  }//双向加，反向边初始为0
  inline bool Dinic(){
    queue<int> q;
    q.push(s);
    memset(dep,0,sizeof(dep));
    dep[s] = 1;
    while(!q.empty()){
      int qf = q.front();q.pop();
      for (int i=head[qf];i;i=edge[i].nxt){
        int v= edge[i].v;
        if (!dep[v] && edge[i].val){
          dep[v] = dep[qf]+1;
          q.push(v);
        }
      }
    }
    return dep[t];
  }//dinic算法的基础，查看终点是否能够访问。
  inline int dfs(int u, int lim){
    if(!lim || u==t) return lim;
    int tflow = 0;
    for (int i=head[u];i;i=edge[i].nxt){
      int v = edge[i].v;
      if (dep[v] ==dep[u]+1 && edge[i].val){
        int now = dfs(v,min(lim,edge[i].val));
        edge[i].val-=now;
        edge[i^1].val+=now;
        tflow+=now;
        lim-=now;
      }
    }
    if (!tflow) dep[u] = 0;
    return tflow;
  }
  inline void solve();
}

inline int id(char x){
  return (int) x-64;
}//将字母转化为点，'A'的ASCII码为65，减去64后为1。
char c1,c2;
inline void Dinic::solve(){
  s = id('A'), t = id('Z');
  cin >> n;
  for (int i=1;i<=n;i++){
    cin >> c1 >> c2 >> c;
    addedge(id(c1),id(c2),c);
  }//加个边
  while(Dinic()) flow+= dfs(s,1e9);//不断找增广路就好了。
  cout << flow;
}

signed main(){
  Dinic::solve();
}

```

---

## 作者：_lcy_ (赞：1)

[题目](https://www.luogu.org/problem/P2936)
---
标准的网络流裸题  
只需要跑一遍网络流的模板就好了

---
不知道网络流是什么的请看[这道题](https://www.luogu.org/problem/P3376)  
附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=10010,MAXM=100010;
int N,M,S,T;
int to[MAXM<<1],edge[MAXM<<1],nxt[MAXM<<1],head[MAXN],tot=1;
void addedge(int u,int v,int c){
  to[++tot]=v;
  edge[tot]=c;
  nxt[tot]=head[u];
  head[u]=tot;
}
int d[MAXN];
map<string,int> m;\\将字母变成数字
int tot2;
queue<int> q;
bool bfs(){
  memset(d,0,sizeof(d));
  while(!q.empty()) q.pop();
  q.push(S);
  d[S]=1;
  while(!q.empty()){
    int t=q.front();
    q.pop();
    for(int i=head[t];i;i=nxt[i]){
      int v=to[i];
      if(edge[i] && !d[v]) {
        d[v]=d[t]+1;
        q.push(v);
        if(v==T) return true;
      }
    }
  }
  return false;
}

int dinic(int now,int flow){
  if(now==T) return flow;
  int rest=flow;
  for(int i=head[now];i;i=nxt[i]){
    int v=to[i];
    if(edge[i] && d[v]==d[now]+1) {
      int k=dinic(v,min(rest,edge[i]));
      rest-=k;
      edge[i]-=k;
      edge[i^1]+=k;
      if(k==0) d[v]=0;
    }
  }
  return flow-rest;
}

int main(){
  scanf("%d%d",&N,&M);
  string t1,t2;
  int t3;
  while(cin>>t1>>t2>>t3){
    // scanf("%d%d%d",&t1,&t2,&t3);
    if(m.count(t1)==0) m[t1]=++tot2;
    if(m.count(t2)==0) m[t2]=++tot2;
    addedge(m[t1],m[t2],t3);
    addedge(m[t2],m[t1],t3);
  }
  if(m.count("A")==0 || m.count("Z")==0){
      printf("%d\n",0);
      system("pause");
      return 0;
  }
  S=m["A"],T=m["Z"];
  int maxflow=0;
  while(bfs()){
    int flow;
    while(flow=dinic(S,0x3f3f3f3f)) maxflow+=flow;
  }
  printf("%d\n",maxflow);
//  system("pause");
  return 0;
}
```

---

## 作者：VenusM1nT (赞：1)

这题搞得我想哭QAQ

A了之后看了一下别人的代码，裸的Dinic只要20~200ms不等，我这个还加了弧优化的怎么跑了600ms？！

（难道是因为我用了$cin$吗）

做法很简单，按题目中给出的路径连边，然后设源点$S=ASCII('A')$，汇点$T=ASCII('Z')$跑一遍$Dinic/EK$求最大流即可

代码如下

```cpp
#include<bits/stdc++.h>
#define inf 2147400000
using namespace std;
queue <int> q;
int cnt=1,fst[505],nxt[200005],to[200005],w[200005],cur[505];
int n,S,T,dep[505];
void AddEdge(int u,int v,int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
bool Bfs()
{
	memset(dep,0,sizeof(dep));
	q.push(S);
	dep[S]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=to[i];
			if(!dep[v] && w[i])
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[T];
}
int Dfs(int u,int flow)
{
	if(u==T || !flow) return flow;
	int used=0;
	for(int i=cur[u];i;i=nxt[i])
	{
		int v=to[i];
		if(dep[v]==dep[u]+1 && w[i])
		{
			int fl=Dfs(v,min(flow,w[i]));
			if(fl)
			{
				used+=fl;
				flow-=fl;
				w[i]-=fl;
				w[i^1]+=fl;
				if(!flow) break;
			}
		}
	}
	return used;
}
int Dinic()
{
	int sum=0;
	while(Bfs())
	{
		memcpy(cur,fst,sizeof(fst));
		sum+=Dfs(S,inf);
	}
	return sum;
}
int main()
{
	scanf("%d",&n);
	S=65;
	T=90;
	for(int i=1;i<=n;i++)
	{
		char x,y;
		int z;
		cin >> x >> y >> z;
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	int ans=Dinic();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：I_AM_HelloWord (赞：1)

不知道楼下的ISAP出现什么问题使得bfs的距离d数组爆了，反正我是找着模板打的，最后过了就是了。


嗯，说说这题吧，题目就是说给出一堆字母标号的水管，要求A到Z的最大流量，水管的字母标号也有可能是小写的哟。


然后直接将读到的字母的ASCII码值减去64，建个图，跑个最大流就行了。


我原本也是Dinic党，但认真学了ISAP后，觉得也不是很复杂，但比Dinic快了不少，建议大家都能学学，万一考试的时候卡了那个常数呢？


ISAP的具体原理一句两句也不好说，大家看看程序的注释吧，应该说不是很难理解。


参考代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int M=888;
const int INF=0x3f3f3f3f;
int n,EdgeCnt=0,S,T;
struct Edge{
    int to,cap,next;
}e[M*2];
int a[M],d[M],num[M],cur[M],fa[M];
queue<int> Q;
void addedge(int u,int v,int w){
    int &p=EdgeCnt;
    e[p].to=v;e[p].cap=w;e[p].next=a[u];
    a[u]=p++;
}
void BFS(){
    for (int i=1;i<=80;i++)d[i]=52;//一共就52个点，所以最大距离不会超过52
    Q.push(T);d[T]=0;
    while (!Q.empty()){
        int u=Q.front();Q.pop();
        for (int p=a[u];p!=-1;p=e[p].next){
            int v=e[p].to;
            if (e[p^1].cap && d[v]>d[u]+1){//注意，这里是从汇点开始倒着bfs的，所以当前的边是反向弧，必须要p^1切换到正向边
                d[v]=d[u]+1;
                Q.push(v);
            }
        }
    }
}
int Augment(){
    int u=T,f=INF;
    while (u!=S){
        u=fa[u];
        f=min(f,e[cur[u]].cap);
    }
    u=T;
    while (u!=S){
        u=fa[u];
        e[cur[u]].cap-=f;
        e[cur[u]^1].cap+=f;
    }
    return f;
```
}//增广，就不用解释了吧？
```cpp
int MaxFlow(){
    memset(num,0,sizeof(num));
    BFS();//预处理第一次的距离标号
    for (int i=1;i<=80;i++)num[d[i]]++,cur[i]=a[i];
    int u=S,flow=0;
    while (d[S]<52){//既然都为了时间快，写ISAP了，干脆写成非递归的
        if (u==T){
            flow+=Augment();u=S;//走到汇点了，增广，在回到源点
        }
        bool done=false;//是否前进的标志
        for (int p=cur[u];p!=-1;p=e[p].next){
            int v=e[p].to;
            if (e[p].cap && d[u]==d[v]+1){
                fa[v]=u;cur[u]=p;//cur与fa类似递归时的栈保存当前选择了那条边，回溯时就不会走重复的路
                u=v;done=true;//前进
                break;
            }
        }
        if (!done){
            int m=51;
            for (int p=a[u];p!=-1;p=e[p].next){
                int v=e[p].to;
                if (e[p].cap)m=min(m,d[v]);
```
}//取消Dinic的一次性bfs修改d数组，而是回溯时直接从所有他的后继状态直接转移一个最短路过来
if (--num[d[u]]==0)break;//gap优化，很好理解，就是中间一个距离状态为空了，所以源点与汇点一定不连通

```cpp
            num[d[u]=m+1]++;
            cur[u]=a[u];
            if (u!=S)u=fa[u];//回溯
        }
    }
    return flow;
}
int main(){
    scanf("%d",&n);
    S=1;T=26;
    memset(a,0xff,sizeof(a));
    for (int i=1;i<=n;i++){
        char tu,tv;int u,v,w;
        scanf("\n%c %c %d",&tu,&tv,&w);
        u=tu-64;v=tv-64; 
        addedge(u,v,w);
        addedge(v,u,0);//正反向建图
    }
    printf("%d",MaxFlow());
    return 0;
}
```

---

## 作者：Mychael (赞：1)

这道题其实就是网络流最大流模板

题目很友善，甚至水管给的都是有向的

————————————————————————————————

Ford\_Fulkerson算法（增广路）：

每次作出原图的残量网络，然后沿着一条可以到达汇点的路径，将路径上所有的点的流值加上这条路径上的最小允许流量

知道找不到这样一条增广路为止，算法结束。

下面是代码：




```cpp
#include<iostream>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=60,maxe=1500,INF=2000000000,S=0,T=25;
bool vis[maxn];
int read()                                         //读入优化
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
inline int code(char c)                                      //字符转化整型
{
    return c>='a' ? c-'a'+26:c-'A';
}
int head[maxn],nedge=0;
class EDGE                                          //链式前向星构图
{
```
public:




```cpp
        int to,f,next;
}edge[maxe];
void build(int a,int b,int w)
{
    edge[nedge]=(EDGE){b,w,head[a]};
    head[a]=nedge++;
    edge[nedge]=(EDGE){a,0,head[b]};
    head[b]=nedge++;
}
int dfs(int u,int minf)                                                 //深搜找增广路
{
    if(u==T)
        return minf;
    vis[u]=true;
    int d;
    for(int k=head[u];k!=-1;k=edge[k].next)
    {
        if(!vis[edge[k].to]&&edge[k].f)
        {
            d=dfs(edge[k].to,min(minf,edge[k].f));
            if(d>0)
            {
                edge[k].f-=d;
                edge[k^1].f+=d;                                                       //反图
                return d;
            }
        }
    }
    return 0;
}
int flow_max()                                                      //最大流算法
{
    int ans=0,f=INF;
    while(f)
    {
        fill(vis,vis+maxn,false);
        f=INF;
        f=dfs(S,f);
        ans+=f;
    }
    return ans;
}
int main()
{
    fill(head,head+maxn,-1);
    int N=read(),x;
    char a,b;
    while(N--)
    {
        a=getchar();
        while(!isalpha(a)) a=getchar();
        b=getchar();
        while(!isalpha(b)) b=getchar();
        x=read();
        build(code(a),code(b),x);
    }
    cout<<flow_max()<<endl;
    return 0;
}

```

---

## 作者：king_xbz (赞：0)

看到这道~~经典的网络流裸题~~，我毫不犹豫的使用**EK算法**A掉了它，题解区的12篇题解貌似还没有用EK做的，那么我就来写一篇题解帮助像我一样刚学网络流的小白来了解**最大流问题的EK做法**吧！

- 先来简单了解一下这个算法的由来吧！

EK算法全称 _Edmonds-Karp_ 算法，该算法最初由 _Yefim Dinitz_ 于1970年出版，并由 _Jack Edmonds_ 和 _Richard Kar_ p于1972年独立出版。在计算机科学中 _Edmonds-Karp_ 算法是用于**计算流网络中的最大流量**的 _Ford-Fulkerson_ 方法的实现。 这个算法的时间复杂度是**O(VE²)**.

- 算法实现

这个算法的实质其实就是**不停的进行BFS**，找增广路，并更新，直到找不到路径，流量无法再增加时就结束了。我们都知道，一次BFS找到的路径并不一定是最优决策，所以我们应该给自己留有**反悔**的余地，这时候就需要我们双向存图，在第一次找到增广路之后，在**把路上每一段的容量减少flow的同时，也把每一段上的反方向的容量增加flow。**

那么话不多说，我们看一下注释代码
-
```cpp
int cnt=1;//重中之重，不然你会什么也得不到
signed main()
{
	n=read(),m=read(),s=read(),t=read();//n为点数，m为边数，s，t为起点终点
	int x,y,z;
	for(fint i=1;i<=m;i++)
	x=read(),y=read(),z=read(),adds(x,y,z);
	while(EK(s,t))
	addup(t);//不停的进行bfs
	printf("%lld",ans);
	return 0;
}

inline void adds(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].val=w;
	e[cnt].next=head[u];
	head[u]=cnt;
	e[++cnt].to=u;
	e[cnt].val=0;//注意反向图流量初始为0
	e[cnt].next=head[v];
	head[v]=cnt;
	return ;
}//链式前向星双向存图大法

inline int EK(int s,int t)
{
	queue <int>q;
	memset(vis,0,sizeof(vis));
	vis[s]=1,dis[s]=inf;//vis标记访问，dis为边上的流量
	q.push(s);
	while(!q.empty())
	{
		int hea=q.front();
		q.pop();
		for(fint i=head[hea];i;i=e[i].next)//BFS
			if(e[i].val)//有流量时才可搜哦
			{
				if(!vis[e[i].to])
				dis[e[i].to]=min(dis[hea],e[i].val),pre[e[i].to]=i,vis[e[i].to]=1,q.push(e[i].to);//这里记得更新前驱节点pre数组，一会有用
				if(e[i].to==t)
				return 1;若搜到了汇点，bfs成功，可以更新了
			}
	}
	return 0;//bfs失败，即已经没有可更新的流量
}

inline void addup(int x)
{
	while(x!=s)//反向操作
	{
		e[pre[x]].val-=dis[t];
		e[pre[x]^1].val+=dis[t];//正减反加
		x=e[pre[x]^1].to;
	}
	ans+=dis[t];//累加最大流
	return ;
}
```
后排提示，此代码**并非**这道题的AC代码，而是[这道](https://www.luogu.com.cn/problem/P3376)不要脑子一热抄上去了。

那么对于这道题，我们需要在~~将知识迁移运用~~时注意：
```
2019.2.21 管理员注：输入数据中可能含有小写字母。
```
所以，我们需要将A-Z,a-z转化为数字（其实不转换也不是不行，只是麻烦点罢了）

根据我们熟悉的ASCII码的知识，我们就有了这段代码：
```cpp
for(fint i=1;i<=n;i++)
	cin>>a>>b,c=read(),aa=a-64,bb=b-64,adds(aa,bb,c);
```
那么这道题便结束了，同时P3376的~~双倍经验也拿了~~，谢谢大家的浏览！

---

## 作者：a2920353120 (赞：0)

> 网络最大流的模板题
>
> 跑一遍最大流的模板就好的
>
> 具体看代码
>
> 注释有讲解

```cpp

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

const int N = 1000 + 10;
int s, t, n, m, tot, maxflow;//s:源点,t汇点, maxflow最大流量
int head[N], pre[N], d[N];//head数组邻接表存边,pre记录分层图的点,d拿来分层
struct node {
	int from, to, dis;//from记录从起点,to记录终点,dis记录容量
	int nxt, op;//nxt下一个,op反向边
}e[N];

void add(int x, int y, int z) {//邻接表加边
	//正向加边
	tot++;
	e[tot].from = x;
	e[tot].to = y;
	e[tot].dis = z;
	e[tot].nxt = head[x];
	head[x] = tot;
	e[tot].op = tot + 1;
    //反向存边
	tot++;
	e[tot].from = y;
	e[tot].to = x;
	e[tot].dis = 0;//注意容量为0
	e[tot].nxt = head[y];
	head[y] = tot;
	e[tot].op = tot - 1;
}

bool found() {//寻找可增广路
	memset(d, 0x77, sizeof(d));//相当于给d数组置INF
	d[s] = 0;
	queue<int > q;
	q.push(s);//从起点开始
	while(!q.empty()) {
		int lin = q.front();
		int now = head[lin];
		while(now != -1) {//还有边
			if(e[now].dis > 0 && d[e[now].from] + 1 < d[e[now].to]) {
				d[e[now].to] = d[e[now].from] + 1;//分层
				pre[e[now].to] = now;//记录经过的点
				q.push(e[now].to);
				if(e[now].to == t) return true;//还存在可增广路
			}
			now = e[now].nxt;
		}
		q.pop();
	}
	return false;
}
	
void augment() {
	int p;//求每一条增广路的流量
	p = t;
	int flow = 100000000;
	while(p != s) {
		flow = min(e[pre[p]].dis, flow);//增广路的流量由最小容量决定
		p = e[pre[p]].from;
	}
	maxflow += flow;//最大流加上本次流量
	p = t;
	while(p != s) {
		e[pre[p]].dis -= flow;//路径减去容量
		e[e[pre[p]].op].dis = flow;
		p = e[pre[p]].from;
	}
}

int main() {
	int i, j, k;
	cin >> m;
	s = int('A');//从A出发
	t = int('Z');//到Z结束
	memset(head, -1, sizeof(head));//head数组置-1
	for(i = 1; i <= m; i++) {
		char x, y;
		int z;
		cin >> x >> y >> z;
		add(int(x), int(y), z);//点用它的ASCII码表示，注意强制转换
	}
	while(found()) augment();//还有可增广路
	cout << maxflow << endl;
	return 0;
}
```


---

## 作者：不争不闹 (赞：0)

并没有发现有哪一篇题解方便食用


其实这是一个最大流模板题目


带有三个优化的Dinic

1、当前弧优化，访问这个点的出边时，从上一次访问的下一条边开始

2、当增广到某个点时，增广过程中，已出去的流量==进来的，停止增广；增广完毕时，出去的流量<进来的流量，标记这个点，以后不再访问此点

3、分层时，找到汇点后即刻return，不要等到队列为空

Dinic有此三个优化，足以不学其他算法（By XXY）

xxy dalao 博客


> #include <iostream>
```cpp
http://www.cnblogs.com/TheRoadToTheGold/p/6502767.html
#include <cstdio>
#include <queue>
#define inf 0x3fffffff
#define min(x,y) (x<y)?(x):(y)
#define N 701
#define M 101
int n,head[M],cnt[M],lev[M];
int src,decc,tot=1;
struct Edge{
    int v,w,nxt;
}edge[N<<1];
inline int read()
{
    int n=0,w=1;register char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c<='9'&&c>='0')n=n*10+c-'0',c=getchar();
    return n*w;
}
inline void add(int u,int v,int w)
{
    edge[++tot].v=v;
    edge[tot].w=w;
    edge[tot].nxt=head[u];
    head[u]=tot;
    return ;
}
inline void add_(int u,int v)
{
    edge[++tot].v=u;
    edge[tot].w=0;
    edge[tot].nxt=head[v];
    head[v]=tot;
    return ;
}
std::queue<int> que;
inline bool bfs()
{
    for(int i=0;i<=100;++i)
```
{//当前弧优化
```cpp
        cnt[i]=head[i];
        lev[i]=-1;
    }
    while(!que.empty())que.pop();
    que.push(src);lev[src]=0;
    while(!que.empty())
    {
        int now=que.front();que.pop();
        for(int i=head[now];i;i=edge[i].nxt)
        {
            int t=edge[i].v;
            if(lev[t]==-1&&edge[i].w>0)
            {
                que.push(t);
                lev[t]=lev[now]+1;
                if(t==decc)return true;
```
}//优化3
```cpp
        }
    }
    return false;
}
int dinic(int now,int flow)
{
    int delta,rest=0;
    if(now==decc)return flow;
    for(int &i=cnt[now];i;i=edge[i].nxt)
    {
        int t=edge[i].v;
        if(lev[t]==lev[now]+1&&edge[i].w>0)
        {
            delta=dinic(t,min(edge[i].w,flow-rest));
            if(delta)
            {
                edge[i].w-=delta;
                edge[i^1].w+=delta;
                rest+=delta;
                if(rest==flow)break;
```
}//优化2
```cpp
        }
    }
    if(rest!=flow)lev[now]=-1;
    return rest;
}
int main()
{
    n=read();
    src=1,decc=26;
    char c;
    for(int x,y,z,i=0;i<n;++i)
    {
         c=0;
        while((c<'A'||c>'Z')&&(c<'a'||c>'z'))c=getchar();
        x=c-'A'+1;
        c=0;
        while((c<'A'||c>'Z')&&(c<'a'||c>'z'))c=getchar();
        y=c-'A'+1;
        z=read();
        add(x,y,z);add_(x,y);
    }
    int ans=0;
    while(bfs())
        ans+=dinic(src,inf);
    printf("%d",ans);
    return 0;
}
```
另：可能有人发现我的代码开头没有using namespace std;
算是小技巧……考场上面不加这一句话一定不会出现变量重名导致的CE

用STL的时候在前面加上std::就好了，也不是很麻烦


---

## 作者：卡车cckk (赞：0)

嗯，其实就是最多26\*2个水管组成的网络，原点A，汇点Z，然后跑一遍dinic  without任何优化

#注意

- 大小写英文字母

- 水管连接可能有重复，比如（测试点2输出第某行）  A B 121  A B 112 所以最终A与B之间的容量是233。所以连边的时候注意要相加


蒟蒻代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<string.h>
#define MA 5200
int edge[256][256],m,dl[333],dis[333];
using namespace std;
int minn(int a,int b){return a>b?b:a;}
int BFS()
{
    int g=0,r=1;memset(dis,0xff,sizeof(dis));
    dl[g]='A';dis['A']=0;
    while(g!=r)
    {
        for(int i='A';i<='z';i++)
        {
            if(edge[dl[g]][i]>0&&dis[i]<0)
            {
                dis[i]=dis[dl[g]]+1;
                dl[r++]=i;
            }
        }
        g++;
    }
    return dis['Z']>0;
}
int DFS(int now,int mins)
{
    int a=0;
    if(now=='Z')return mins;
    for(int i='A';i<='z';i++)
    if(edge[now][i]>0&&dis[now]+1==dis[i])
    if(a=DFS(i,minn(mins,edge[now][i])))
    {
        edge[now][i]-=a;
        edge[i][now]+=a;
        return a;
    }
    return 0;
}
int main()
{
    scanf("%d",&m);
    char a,b;
    int k=0;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b>>k;
        edge[a][b]+=k;
        edge[b][a]+=k;
    }
    int ans=0,jl=0;
    while(BFS())
        while(jl=DFS('A',23333333)){ans+=jl;}
    printf("%d",ans);
    return 0;
}
```
贪图简洁的代码，哈哈。


##题外话：最后推广下我们的Dodou

[Dodou](http://dodou.hicasper.com)


---

## 作者：芬特 (赞：0)

最大流模板题，显而易见，dinic的确没有问题，但是为什么大家都这么抗拒isap呢，isap大法好。

这道题的第七个点意外地爆了isap的反向搜索预处理距离数组，但是isap这种高度模(bao)块(li)化的算法怎么不能灵活运用呢，既然针对最短路增广，我们就把d数组去掉，对于每一条可行流强行增广，这样复杂度就退化成了O( f⋅∣E∣) ，结果这个题的最大流f特别小，就直接秒了。

一些细节还需要看代码，加边什么的……唉

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=10001;
const int inf=0x3f3f3f3f;
int read()
{
    int x=0;char c=getchar();
    while(c<48||c>57)c=getchar();
    while(c>47&&c<58)x*=10,x+=c-48,c=getchar();
    return x;
}
struct edge{int from,to,cap,flow;};
struct isap
{
    int n,s,t,p[maxn],d[maxn],cur[maxn],num[maxn];
    bool vis[maxn];
    vector<int>g[maxn];
    vector<edge>edges;
    void init(int n,int s,int t)
    {
        this->n=n;
        this->s=s;
        this->t=t;
        for(int i=1;i<=n;i++) g[i].clear();
        edges.clear();
    }
    void addegde(int from,int to,int cap)
    {
        edges.push_back((edge){from,to,cap,0});
        edges.push_back((edge){to,from,0,0});
        int m=edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }
    
    int augment()
    {
        int x=t,a=inf;
        while(x!=s)
        {
            a=min(a,edges[p[x]].cap-edges[p[x]].flow);
            x=edges[p[x]].from;
        }
        x=t;
        while(x!=s)
        {
            edges[p[x]].flow+=a;
            edges[p[x]^1].flow =-a;
            x=edges[p[x]].from;
        }
        return a;
    }
    int maxflow()
    {
        int flow=0;
        memset(num,0,sizeof(num));
        memset(cur,0,sizeof(cur));
        for(int i=1;i<=n;i++) num[d[i]]++;
        int x=s;
        while(d[s]<n)
        {
            if(x==t)
            {
            flow+=augment();
            x=s;    
            }
            bool ok=0;
            for(int i=cur[x];i<g[x].size();i++)
            {
                edge &e=edges[g[x][i]];
                if(d[x]==d[e.to]+1&&e.cap>e.flow)
                {
                    p[e.to]=g[x][i];
                    cur[x]=i;x=e.to;
                    ok=1;
                    break;
                }
            }
            if(!ok)
            {
                int m=n-1;
                for(int i=0;i<g[x].size();i++)
                {
                    edge &e=edges[g[x][i]];
                    if(e.cap>e.flow) m=min(m,d[e.to]);
                }
                num[d[x]]--;
                if(!num[d[x]]) break;
                d[x]=m+1;
                num[d[x]]++;
                cur[x]=0;
                if(x!=s) x=edges[p[x]].from;    
            }
        }
        return flow;
    }
}ISAP;
inline int get_in()
{
    char c;
    cin>>c;
    return (c<='Z'&&c>='A')?c-'A'+1:c-'a'+27; 
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m,s,t,u,v,w;
    n=1000;
    s=1,t=26;
    cin>>m;
    ISAP.init(n,s,t);
    for(int i=1;i<=m;i++)
    {
        char c1,c2;
        int c;
        c1=get_in();
        c2=get_in();
        cin>>c;
        ISAP.addegde(c1,c2,c);
    }
    cout<<ISAP.maxflow();
    return 0;
}
```

---

## 作者：阿廖 (赞：0)

此题就是网络流模板，很裸，dinic随便过（并不需要什么优化，缩边这类的鬼玩意，尽管题目有说）

```cpp
#include<bits/stdc++.h>
using namespace std;
class bigpig
{
    public:
        void work()
        {
            while(bfs())
                while(tot=dfs(start,1e9))ans+=tot;
        }
        void add(int x,int y,int v)
        {
            a[++tot].end=y,a[tot].val=v,a[tot].next=head[x],head[x]=tot;
            a[++tot].end=x,a[tot].val=0,a[tot].next=head[y],head[y]=tot;
        }
        void updata(int s,int e)
        {
            start=s,end=e;
        }
        int extract(int k)
        {
            if(k==1)return start;
            if(k==2)return end;
            if(k==3)return ans;
        }
    private:
        int bfs()
        {
            memset(dis,-1,sizeof(dis));
            dis[start]=0;
            while(!q.empty())q.pop();
            q.push(start);
            while(!q.empty())
            {
                int now=q.front();
                q.pop();
                for(int i=head[now];i;i=a[i].next)
                    if(a[i].val>0 && dis[a[i].end]<0)
                        dis[a[i].end]=dis[now]+1,q.push(a[i].end);
            }
            if(dis[end]>0)return 1;
            else return 0;
        }
        int dfs(int now,int val)
        {
            if(now==end)return val;
            for(int i=head[now],k;i;i=a[i].next)
                if(a[i].val>0 && dis[a[i].end]==dis[now]+1 && (k=dfs(a[i].end,min(a[i].val,val))))
                    {a[i].val-=k,a[i+1].val+=k;return k;}
            dis[now]=-1;
            return 0;
        }
        int start,end,tot,ans,dis[1005],head[1005];
        queue<int>q;
        struct smallpig
        {
            int end,next,val;
        }a[2005];
};
bigpig flow;
int n,start_,end_;
char a,b;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n,start_=1,end_=26;
    for(int i=1,x,y,z;i<=n;i++)
        cin>>a>>b>>z,x=a-'A'+1,y=b-'A'+1,flow.add(x,y,z);
    flow.updata(start_,end_);
    flow.work();
    cout<<flow.extract(3)<<endl;
    return 0;
}
```
好吧，就这样。


---

## 作者：Infinity_shl (赞：0)

本人今天刚刚学会最大流，此题感觉完全没有提高+的难度，仅仅是一个模板[最大流](https://www.luogu.org/problemnew/show/P3376)，我用了Dinic算法，而且本题数据很小，邻接矩阵存图即可。

## 注意：本题大小写字母均包括在内！！


~~被卡了一次10分~~

Dinic模板的代码   (AC本题）

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int INF=99999999;
queue<int>q;
int n,w[257][257],d[257];
inline bool bfs()
{
	memset(d,0,sizeof(d));
	d['A']=1;
	q.push('A');
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i='A';i<='z';i++)   //一定要到小写z
			if(w[now][i]>0&&d[i]==0)
			{
				d[i]=d[now]+1;
				q.push(i);
			}
	}
	return d['Z']!=0;
}
int dfs(int now,int dist)
{
	if(now=='Z') return dist;
	for(int i='A';i<='z';i++)  //同上
		if(d[i]==d[now]+1&&w[now][i]>0)
		{
			int x=dfs(i,min(dist,w[now][i]));
			if(x>0)
			{
				w[now][i]-=x;
				w[i][now]+=x;
				return x;
			}
		}
	return 0;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char x,y;
		int z;
		cin>>x>>y>>z;
		w[x][y]+=z;
	}
	int ans=0;
	while(bfs())
	{
		while(int di=dfs('A',INF))
			ans+=di;
	}
	cout<<ans;
	return 0;
}
```

---

