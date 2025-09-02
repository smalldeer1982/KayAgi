# [USACO07OPEN] Dining G

## 题目描述

奶牛是如此挑剔的食客。每头奶牛都有自己偏好的食物和饮料，她们不会吃其他的东西。

农夫约翰为他的奶牛们准备了丰盛的饭菜，但他忘记检查菜单是否符合她们的偏好。虽然他可能无法满足所有奶牛，但他希望尽可能多地为奶牛提供一份完整的食物和饮料。

农夫约翰准备了 $F$ 种食物（$1 \le F \le 100$）和 $D$ 种饮料（$1 \le D \le 100$）。他的 $N$ 头奶牛（$1 \le N \le 100$）已经决定她们愿意吃某种食物或喝某种饮料。农夫约翰必须为每头奶牛分配一种食物类型和一种饮料类型，以最大化同时获得食物和饮料的奶牛数量。

每种食物或饮料只能被一头奶牛消费（即，一旦食物类型 2 被分配给一头奶牛，其他奶牛就不能再被分配食物类型 2）。


## 说明/提示

一种满足三头奶牛的方法是：


奶牛 1：没有餐食


奶牛 2：食物 #2，饮料 #2


奶牛 3：食物 #1，饮料 #1


奶牛 4：食物 #3，饮料 #3


鸽巢原理告诉我们，由于只有三种食物或饮料，我们不能做得更好。当然，其他测试数据集更具挑战性。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 3 3
2 2 1 2 3 1
2 2 2 3 1 2
2 2 1 3 1 2
2 1 1 3 3```

### 输出

```
3```

# 题解

## 作者：ez_lcw (赞：23)

# 最大流例题——[USACO07OPEN]吃饭Dining

这是一道比较经典的**网络流**的入门题。

相信和我一样的蒟蒻们看到这题的第一个想法都是**超源连每种食品，食品连喜欢吃它的奶牛，奶牛连他喜欢吃的饮料，每种饮料连超汇，**然后就无脑的套一波模板，闭着眼睛关上脑子抱着人有多大胆地有多大产的心态直接连样例都不过就交上去幻想着0msAC对不对！

### 作为经典例题哪有那么简（dou）单（bi）？
#### ~~虽然我也是这么想的~~

但仔细想想就会发现——脑子怎么可能**关上**呢？对不对？

好吧，不开玩笑了，这题怎么可能那么简单就能过，因为文中有一个要求***“每种食物或饮料只能供一头牛享用，且每头牛只享用一种食物和一种饮料”***，怎么解决这个问题呢？这就需要一个网络流中的常用方法：拆点。

**什么是拆点呢？其实就是把一个点拆成两个点（入点和出点），所有指向这个点的边都连向入点，而从这个点连出去的所有边的起点都在这个点的出点。就像下图一样：**

![](https://cdn.luogu.com.cn/upload/pic/27555.png)

拆点之后：

![](https://cdn.luogu.com.cn/upload/pic/27554.png)

**然后通过入点和出点间的容量（如图，为1）来限制经过这个点的流量，那么就只能有一种食物和一种饮料被这头牛吃。**

这时，*“每头牛只享用一种食物和一种饮料”*的问题已解决，那么*“每种食物或饮料只能供一头牛享用”*怎么解决呢？

**其实这个很简单，只要把超源连每种食物的每条边和每种饮料连超汇的每条边的容量设为1就行，这就保证了每种食物、饮料只能找到一个主人。**

最后的图片如下（没把每个点都画出来，因为画不下那么大~~其实是因为我懒~~）：

![](https://cdn.luogu.com.cn/upload/pic/27550.png)

最后直接跑最大流即可：

dinic算法：

```cpp
#include<cstdio>
#include<queue>
 
#define N 500
#define M 200000
#define INF 0x7fffffff
 
using namespace std;
 
int n,f,d,head[N],to[M],c[M],nxt[M],num[N],minn,s,t,cnt,minflow,maxflow,tot;
 //用邻接表存边
queue<int>q;
 
void adde(int u,int v,int a){//建边
    cnt++;
    to[cnt]=v;
    c[cnt]=a;
    nxt[cnt]=head[u];
    head[u]=cnt;
     
    cnt++;
    to[cnt]=u;
    c[cnt]=0;
    nxt[cnt]=head[v];
    head[v]=cnt;
}
 
bool add_num() {//给每个点标号
    while(!q.empty()) {
        q.pop();
    }
    for(int i=s;i<=t+n;i++) {
        num[i]=-1;
    }
    num[s]=1;
    q.push(s);
    while(!q.empty()) {
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=nxt[i]) {
            if(c[i]&&num[to[i]]==-1) {
                num[to[i]]=num[now]+1;
                q.push(to[i]);
            }
        }
    }
    if(num[t]==-1) {//如果num[t]==-1，那么就说明到不了汇点，不能给汇点标号。
        return false;
    } else {
        return true;
    }
}
 
int dfs(int u,int s){
    if(u==t){
        return s;
    }
    for(int i=head[u];i;i=nxt[i]){
        if(c[i]&&num[u]+1==num[to[i]]&&(minflow=dfs(to[i],min(s,c[i])))){
            c[i]-=minflow;
            c[i^1]+=minflow;
            return minflow;
        }
    }
    return 0;
}
 
void dinic(){//dinic模板
    while(add_num()){
        while((minn=dfs(1,INF))){
            maxflow+=minn;
        }
    }
}
 
int main(){
    scanf("%d%d%d",&n,&f,&d);
    cnt=1;
    s=1;
    t=1+f+n+d+1;
    for(int i=1;i<=f;i++){//超源连每种食品
        adde(s,1+i,1);
    }
    for(int i=1;i<=d;i++){//每种饮料连超汇
        adde(1+f+n+i,t,1);
    }
    for(int i=1;i<=n;i++){//入点连出点
        adde(1+f+i,1+f+n+d+1+i,1);
    }
    for(int i=1;i<=n;i++){
        int dn,fn;
        scanf("%d%d",&fn,&dn);
        for(int q=1;q<=fn;q++){//食品连喜欢吃它的奶牛
            int fi;
            scanf("%d",&fi);
            adde(1+fi,1+f+i,1);
        }
        for(int q=1;q<=dn;q++){//奶牛连他喜欢吃的饮料
            int di;
            scanf("%d",&di);
            adde(1+f+n+d+1+i,1+f+n+di,1);
        }
    }
    dinic();
    printf("%d\n",maxflow);//输出
    return 0;
}
```
注：EK朴素算法也可以过得去。
如果是入门最大流也可以用邻接矩阵存边。

---

## 作者：雅儿贝德 (赞：8)

作为网络流入门题还是非常不错的一道题

网络流中，建图是第一重要的

看题，很自然会想到把牛，食物，饮料连在一起，有因为食物和饮料没有直接可以相连的关系，所以，非常机智想到了把牛放在中间，食物和饮料放两边，然后就是一个裸的网络流，然后瞎写写就能AC了是不是！非常激动是不是！

Too young too simple

不难发现从原点到牛的流量可能不是1，从牛到汇点也可能不是1

这代表什么？

题目中要求每种食物或饮料只能供一头牛享用，且每头牛只享用一种食物和一种饮料

这代表一头牛可能食用了所有它喜欢吃的和喜欢喝的

那怎么办？

把一头牛分开，分成牛A和牛B

在牛A与牛B之间连一条容量为1的边

这样就能保证在流的过程中，到达牛B的流量最多为1，也意味着只享用了1种食物，而接下来从牛B开始也只有1的流量，因为我们在把牛，食物，饮料连在一起时，边容量为1，所以也保证从牛B接下来只会享用1种饮料

完美！

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int v,w,next,other;
}edge[100010];

int from[100010],h[100010],q[100010];
int n,m,num,f,d,st,ed;

void addedge(int x,int y,int c)
{
	int k1,k2;
	num++;
	k1=num;
	edge[num].v=y;
	edge[num].w=c;
	edge[num].next=from[x];
	from[x]=num;
	
	num++;
	k2=num;
	edge[num].v=x;
	edge[num].w=0;
	edge[num].next=from[y];
	from[y]=num;
	
	edge[k1].other=k2;
	edge[k2].other=k1;
}

int head,tail; 

bool bfs()
{
	memset(h,0,sizeof(h));
	h[st]=1;
	q[1]=st;
	head=1;tail=2;
	while(head!=tail)
	{
		int x=q[head];
		for(int k=from[x];k;k=edge[k].next)
		{
			int y=edge[k].v;
			if((edge[k].w>0)&&(h[y]==0))
			{
				h[y]=h[x]+1;
				q[tail]=y;
				tail++;
			}
		}
		head++;
	}
	if(h[ed]>0) return true;else return false;
}

int dfs(int x,int f)
{
	if(x==ed) return f;
	int s=0,t;
	for (int k=from[x];k;k=edge[k].next)
	{
		int y=edge[k].v;
		if((h[y]==(h[x]+1))&&(edge[k].w>0)&&(s<f))
		{
			t=dfs(y,min(f-s,edge[k].w));
			s+=t;
			edge[k].w-=t;
			edge[edge[k].other].w+=t;
		}
	}
	if (s==0) h[x]=0;
	return s;
}

int main()
{
	cin>>n>>f>>d;
	st=0;
	ed=n*2+f+d+1;
	for(int i=1;i<=f;i++) addedge(st,i,1);
	for(int i=1;i<=n;i++) addedge(i+f,i+f+n,1);
	for(int i=1;i<=d;i++) addedge(i+2*n+f,ed,1);
	for(int i=1;i<=n;i++)
	{
		int f1,d1;
		cin>>f1>>d1;
		for(int j=1;j<=f1;j++)
		{
			int x;
			cin>>x;
			addedge(x,i+f,1);
		}
		for(int j=1;j<=d1;j++)
		{
			int x;
			cin>>x;
			addedge(n+i+f,n+n+f+x,1);
		}
	}
	int ans;
	while(bfs())
	{
		ans+=dfs(st,19270817);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lukelin (赞：3)

### 前言
如果有人不会网络流，那么安利一下我[网络最大流Dinic的博客](https://www.cnblogs.com/linzhengmin/p/9313216.html)  
关于网络流，我多久没有碰这个算法了...  
这是一道网络流好题。  
### 题解
这道题目难点主要是构图。  
这道题的构图一开始很容易想到建一个超级源点连食物，食物连牛，牛连饮料，饮料连一个新建的超级汇点。  
最后跑一遍最大流求出答案。  
但是实际上这个算法是错误的  
比如下面这组数据  
```
1 3 3
3 3 1 2 3 1 2 3
```
答案应该是1，但当前的算法输出是3，算法的错误是中间的牛被重复利用了。  
于是我们想到了一个技巧，**拆点**。  
把一个牛**拆成两个点**，中间连接一条流量为1的边，这样保证了一头牛最多只会被利用一次。  
于是重新构图：  
建一个超级源点连房间，食物连牛1，牛1连牛2，牛2连饮料，饮料连一个新建的超级汇点。  
注:其中牛1和牛2实际上是指同一头牛。  
然后接着跑一遍网络流求出答案即可。  
### 代码
```cpp
#include <cstdio> 
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const long long MAX = (1ll << 62);

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Edge{
    int to, next;
    long long dis;
} edges[210000];

int cur[10010], head[10010], edge_num = -1;

void addEdge2(int from, int to, long long dis){
    edges[++edge_num].to = to;
    edges[edge_num].dis = dis;
    edges[edge_num].next = head[from];
    head[from] = edge_num;
}

void addEdge(int from, int to, long long dis){
    addEdge2(from, to, dis), addEdge2(to, from, 0);
}

int d[10010];
int s, t;

long long DFS(int u, long long flow){
    if (u == t) return flow;
    long long _flow = 0, __flow;
    for (int& c_e = cur[u]; c_e != -1; c_e = edges[c_e].next){
        int v = edges[c_e].to;
        if (d[v] == d[u] + 1 && edges[c_e].dis > 0){
            __flow = DFS(v, min(flow, edges[c_e].dis));
            flow -= __flow;
            edges[c_e].dis -= __flow;
            _flow += __flow;
            edges[c_e ^ 1].dis += __flow;
            if (!flow)
                break;
        }
    }
    if (!_flow) d[u] = -1;
    return _flow;
}

bool BFS(){
    memset(d, -1, sizeof(d));
    queue<int> que; que.push(s);
    d[s] = 0; int u, _new;
    while (!que.empty()){
        u = que.front(), que.pop();
        for (int c_e = head[u]; c_e != -1; c_e = edges[c_e].next){
            _new = edges[c_e].to;
            if (d[_new] == -1 && edges[c_e].dis > 0){
                d[_new] = d[u] + 1;
                que.push(_new);
            }
        }
    }
    return (d[t] != -1);
}

int n;

void dinic(){
    long long max_flow = 0;
    while (BFS()){
        for (int i = 0; i <= n; ++i) cur[i] = head[i];
        max_flow += DFS(s, MAX);
    }
    printf("%lld", max_flow);
}

int main(){
    memset(head, -1, sizeof(head));
    int N = read(), f = read(), d = read();
    s = 0;
    for (int j = 1; j <= f; ++j)
        addEdge(s, j, 1);
    for (int i = 1; i <= N; ++i){
        int fi = read(), di = read();
        for (int j = 1; j <= fi; ++j){
            int ff = read();
            addEdge(ff, f + d + i, 1);
        }
        addEdge(f + d + i, f + d + N + i, 1);
        for (int j = 1; j <= di; ++j){
            int dd = read();
            addEdge(f + d + N + i, f + dd, 1);
        }
    }
    n = t = f + d + N * 2 + 1;
    for (int j = 1; j <= d; ++j)
        addEdge(f + j, t, 1);
    dinic();
    return 0;
}
```

---

## 作者：Prean (赞：2)

# 题目大意
有$ n $只奶牛，$ q $种食物和$ p $种饮料，每只奶牛喜欢一些饮料和食物，但只能那一种，求最小配对数量。

首先来看一下这道题的简化版：没有饮料，该怎么做呢？

我会！裸的二分图最大匹配！

但加了饮料，就有了两种限制条件，我们自然地想到直接饮料、食物和奶牛都连边，用Dinic跑网络最大流。

于是你WA了。

问题处在哪儿呢？

让我们来看一组数据：
```
1 2 2
2 2 1 2 1 2
```
用Dinic跑网络最大流，答案是2，但正确答案是1。

问题在于：同一只奶牛选了两次。

所以我们运用拆点的思想，将一只奶牛拆成两个点：出点和入点，食物连入点，出点连饮料。

然后你再交上去就A了qwq

给一下代码吧：
```cpp
#include<cstring>
#include<cstdio>
#include<queue>
const int M=405;
struct Edge{
    int to,nx,flow;
}e[M*200];
int n,q,p,s,t,cnt=1,d[M],h[M],cur[M];
inline int min(const int a,const int b){
    return a>b?b:a;
}
inline void Add(int x,int y){
    e[++cnt]=(Edge){y,h[x],1};h[x]=cnt;
    e[++cnt]=(Edge){x,h[y],0};h[y]=cnt;
}
inline bool BFS(){
    register int E,u,v;
    std::queue<int>q;
    memset(d,0,sizeof d);
    q.push(s);d[s]=1;
    while(!q.empty()){
        u=q.front();q.pop();
        for(E=cur[u]=h[u];E;E=e[E].nx)if(e[E].flow){
            v=e[E].to;
            if(!d[v]){
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    return d[t];
}
int DFS(register int u,register int flow){
    if(u==t)return flow;
    int used=flow;
    for(register int&E=cur[u];E;E=e[E].nx)if(e[E].flow){
        int v=e[E].to;
        if(d[v]==d[u]+1){
            int f=DFS(v,min(used,e[E].flow));
            e[E].flow-=f;e[E^1].flow+=f;used-=f;
            if(!f)d[v]=0;
            if(!used)return flow;
        }
    }
    return cur[u]=h[u],flow-used;
}
inline int Dinic(){
    int ans=0;
    while(BFS())while(int d=DFS(s,2e9))ans+=d;
    return ans;
}
signed main(){
    int i,j,u,x,y;
    scanf("%d%d%d",&n,&q,&p);
    s=0;t=q+n+n+p+1;
    for(i=1;i<=q;++i)Add(s,i);
    for(i=1;i<=n;++i)Add(q+i,q+n+i);
    for(i=1;i<=p;++i)Add(q+n+n+i,t);
    for(i=1;i<=n;++i){
        scanf("%d%d",&x,&y);
        for(j=1;j<=x;++j){
            scanf("%d",&u);
            Add(u,q+i);
        }
        for(j=1;j<=y;++j){
            scanf("%d",&u);
            Add(q+n+i,q+n+n+u);
        }
    }
    printf("%d",Dinic());
}
```
P.S.：这种题能少一点儿吗qwq，这已经是我遇到的第三道“酒店之王”了 qwq

---

## 作者：破忆 (赞：1)

### 【题目大意】
每只奶牛都有喜欢的食物和饮料，每种食物和饮料都只能被一头奶牛享用
求最多能满足多少头奶牛
### 【分析】
最大匹配，n≤100

基本就能确定可以用网络流解

网络流一般流程

* 读数据
* 建边
* 跑板子

关键在于建边


![大概模型](https://cdn.luogu.com.cn/upload/image_hosting/rrkzly3x.png)

1. 建立超级源点S，超级汇点T
2. S向食物连流量为1的边
3. 食物向奶牛的入点连流量为1的边，可以保证食物最多被选一次
4. 奶牛的入点连向对应奶牛的出点，流量为1，可以保证奶牛至多选1种食物，1种饮料
5. 奶牛的出点向饮料连流量为1的边

6. 饮料向T连边，可以保证饮料最多被选一次

根据以上建边方式，就能保证奶牛、食物与饮料一一匹配，且最后汇点接受的流量即为答案
### 【算法】
最大流
### 【代码】
```cpp
#include<bits/stdc++.h>
#define RE register
#define IN inline
using namespace std;
const int maxn=105,maxt=maxn*10,maxe=10*maxn*maxn,INF=1<<30;
int n,p,q,S,T;
int tot=1,lnk[maxt];
int cur[maxt],dep[maxt],que[maxt];
int ans;
struct edge{
	int to,nxt,f;
}e[maxe];
IN int read(){
	RE int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
IN void add_e(RE int x,RE int y,RE int f){
	e[++tot]=(edge){y,lnk[x],f};
	lnk[x]=tot;
}
IN void ADD(RE int x,RE int y,RE int f){
	add_e(x,y,f),add_e(y,x,0);
}
IN bool BFS(RE int s,RE int t){
	for(RE int i=1;i<=T;i++) cur[i]=lnk[i],dep[i]=INF;
	RE int hed=0,til=1;
	que[1]=s,dep[s]=0;
	while(hed!=til){
		RE int x=que[++hed];
		for(RE int j=lnk[x];j;j=e[j].nxt){
			RE int y=e[j].to;
			if(dep[y]>dep[x]+1&&e[j].f){
				dep[y]=dep[x]+1;
				que[++til]=y;
			}
		}
	}
	return dep[T]<INF;
}
int DFS(RE int x,RE int limit){
	if(!limit||x==T) return limit;
	RE int flow=0,f;
	for(RE int j=cur[x];j;j=e[j].nxt){
		cur[x]=j;
		RE int y=e[j].to;
		if(dep[y]==dep[x]+1&&(f=DFS(y,min(limit,e[j].f)))){
			flow+=f;
			limit-=f;
			e[j].f-=f;
			e[j^1].f+=f;
			if(!limit) break;
		}
	}
	return flow;
}
IN void Dinic(RE int s,RE int t){
	while(BFS(s,t)){
		ans+=DFS(s,INF);
	}
}
void make_e(){
	S=n*2+p+q+1,T=S+1;
    //步骤1
	for(RE int i=1;i<=p;i++) ADD(S,i,1);
    //2类边
	for(RE int i=1;i<=q;i++) ADD(p+2*n+i,T,1);
    //6类边
	for(RE int i=1;i<=n;i++) ADD(p+i,p+i+n,1);
    //4类边
	for(RE int i=1;i<=n;i++){
		RE int f=read(),d=read();
		for(RE int j=1;j<=f;j++){
			int x=read();
			ADD(x,p+i,1);
            //3类边
		}
		for(RE int j=1;j<=d;j++){
			RE int x=read();
			ADD(p+n+i,p+2*n+x,1);
            //5类边
		}
	}
}
int main(){
//  	freopen("P2891.in","r",stdin);
//  	freopen("P2891.out","w",stdout);
 	n=read(),p=read(),q=read();
 	make_e();//建边
	Dinic(S,T);//跑板子
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：TangLongbin (赞：1)

这个题目可以用网络流做，当然也可以用二分图最大匹配去做；	
我用的就是二分图匹配~~（可能是我太笨，写不来网络流）~~	
首先根据题意，建立如下的一张三分图（没错，就是三分，不过其实就是两张二分图拼接在一起），左边表示食物，中间表示牛，右边表示饮料；	
按照题目要求，我们对于每一只牛，同时向左右两边增广，增广成功则ans++；
![](https://cdn.luogu.com.cn/upload/pic/49016.png )				但只去增广并不能AC，我们还需要对增广的牛的编号进行排序，即让连接边最多的牛先去赠广，这样可以避免发生一些不必要的冲突，例如A食物可以同时给牛a和牛b,但是牛a可以匹配更多食物，我们肯定会将食物给牛a，这样再后续的匹配中，答案更优(但还不是最优！！)；	
为什么说不是最优，因为我们是同时增广两条边，如果其中一条没有匹配上，但是另外一边却匹配了，那么当前的食物或饮料就浪费了，因为现在的这头牛并没有满足条件；因此我们还需要在有且一边匹配成功的时候，对这条边进行“回溯”，即把以前的匹配情况保留下来，具体看代码：	
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define Max 105
using namespace std;
int n,f,d,ans;
bool vis[3][Max*Max],bol[Max*Max],changed[Max*Max];
int match[3][Max*Max],du[3][Max*Max],num[Max*Max],pre[3][Max*Max];
int fir[3][Max*Max],next[3][Max*Max],to[3][Max*Max],tot[3];

void Add(int u,int v,int type){next[type][++tot[type]]=fir[type][u];fir[type][u]=tot[type];to[type][tot[type]]=v;}

bool cmp(int x,int y){return du[1][x]==du[1][y]?du[2][x]>du[2][y]:du[1][x]>du[1][y];}

bool dfs(int now,int type){
    for(register int i = fir[type][now] ; i ; i = next[type][i]){
        int y = to[type][i];
        if(!vis[type][y]){
            vis[type][y]=1;
            if(!match[type][y]||dfs(match[type][y],type)){
                pre[type][y]=match[type][y];
                changed[y]=1;
                match[type][y]=now;
                return 1;
            }
        }
    }
    return 0;
}//匹配边；

void back(){for(register int i = 1 ; i  <= f ; ++i){if(changed[i])match[1][i]=pre[1][i];}}//“回溯”；

int main(){
    scanf("%d%d%d",&n,&f,&d);
    for(register int i = 1,fi,di ; i <= n ; ++i){
        scanf("%d%d",&fi,&di);num[i]=i;
        for(register int j = 1,x ; j <= fi ; ++j){
            scanf("%d",&x);Add(i,x,1);du[1][i]++;
        }//建立第一张二分图；
        for(register int j = 1,x ; j <= di ; ++j){
            scanf("%d",&x);Add(i,x,2);du[2][i]++;
        }//第二张二分图；
        if(!fi||!di)bol[i]=1;//派出一定不会满足的牛；
    }
    sort(num+1,num+1+n,cmp);//排个序；
    for(register int i = 1 ; i <= n ; ++i){
        if(!bol[num[i]]){
            memset(vis,0,sizeof(vis));memset(changed,0,sizeof(changed));
            if(dfs(num[i],1)){
                if(dfs(num[i],2))ans++;
                else back();//这里对第一张图进行“回溯”；
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：3269224138刘 (赞：1)

求最大流(源点(s):0,汇点(t):n+f+dd+n+1,食品编号:1--f,饮料编号:f+1--f+dd,奶牛编号:f+dd+1--f+dd+n,奶牛‘编号:f+dd+n+1--f+dd+n+n。

s向所有食品连边，权为1

所有饮料向t连边，权为1

拆点，把奶牛i拆成i和i+n，i向i+1连边，权为1

奶牛i对应的食品向i连边，权为1，奶牛’i+n向对应的饮料连边，权为1

最后做一边最大流






```cpp
var
  s,t,tot,i,x,k,m,n,j,ans,f,dd,aa,bb,a1:longint;
  deep,d,pre,now,son,h,opp:array[0..100000] of longint;
procedure insert(a,b,c,p:longint);
begin
  inc(tot);
  pre[tot]:=now[a]; now[a]:=tot; son[tot]:=b;
  d[tot]:=c; opp[tot]:=p;
end;
procedure doit(a,b,c:longint);
begin
  insert(a,b,c,tot+2);
  insert(b,a,0,tot);
end;
function bfs:boolean;
var
  head,tail,p:longint;
begin
  fillchar(deep,sizeof(deep),$ff);
  deep[s]:=0;
  head:=1; tail:=1;
  h[1]:=s;
  repeat
    p:=now[h[head]];
    while p>0 do
    begin
      if (d[p]>0) and (deep[son[p]]=-1) then
      begin
        deep[son[p]]:=deep[h[head]]+1;
        if son[p]=t then exit(true);
        inc(tail);
        h[tail]:=son[p];
      end;
      p:=pre[p];
    end;
    inc(head);
  until head>tail;
  exit(false);
end;
function find(x,tmpflow:longint):longint;
var
  temp,sum,p:longint;
begin
  if x=t then exit(tmpflow);
  sum:=0;
  p:=now[x];
  while p>0 do
  begin
    if (d[p]>0) and (deep[x]+1=deep[son[p]]) then
    begin
      if tmpflow<d[p] then temp:=find(son[p],tmpflow)
      else temp:=find(son[p],d[p]);
      dec(d[p],temp);
      inc(d[opp[p]],temp);
      inc(sum,temp);
      dec(tmpflow,temp);
      if tmpflow=0 then break;
    end;
    p:=pre[p];
  end;
  deep[x]:=-1;
  exit(sum);
end;
begin
  readln(n,f,dd);
  s:=0;
  t:=n+f+dd+n+1;
  for i:=1 to f do
    doit(s,i,1);
  for i:=f+1 to f+dd do
    doit(i,t,1);
  for i:=f+dd+n+1 to f+dd+n+n do
    doit(i-n,i,1);
  for i:=f+dd+1 to f+dd+n do
  begin
    read(aa,bb);
    for j:=1 to aa do
    begin
      read(a1);
      doit(a1,i,1);
    end;
    for j:=1 to bb do
    begin
      read(a1);
      doit(i+n,a1+f,1);
    end;
  end;
  ans:=0;
  while bfs do
    inc(ans,find(s,maxlongint));
  writeln(ans);
end.
```

---

## 作者：Social_Zhao (赞：1)

~~看了一下题解，里面的大佬之气极为强烈……于是我决定从一个萌新的角度来解释这道题~~

我是刚学会用网络最大瘤来解决二分图匹配后就来做这题了。

网络最大瘤解决二分图匹配的连边思路：

$s \rightarrow left \rightarrow right \rightarrow t$

这道题貌似是个“三分图”最大“匹配”（注意这里加了引号）。

可以将食物、牛、饮料分别定义为：左部点，中部点，右部点。

但是这里的“匹配”就不是原来的匹配了。

匹配本来的意思是：任意**两边**不共**端点**。

而在这里，“匹配”的意思任意两条从左部到右部的**路径**没有公共**点**。

但是建图的方式还是可以仿照二分图最大匹配的——

$s \rightarrow left \rightarrow mid \rightarrow right \rightarrow t$

但是这样一来，如果您真正理解了网络最大瘤做二分图最大匹配的原理时，你就会发现：

本来经过所有**点**的流量都应该小于等于1，但是在这里经过mid点的流量可能会大于1！这样一来，就会出现一个问题：有两条路径共mid点，与我们之前谈到的“三分图”最大“匹配”的定义不符。

这说明我们需要对mid点进行**“限流”**~~（没错，一开始我就是把这个东西称为“限流”，后面才知道叫拆点）~~

限流的方法很简单：在《挑战程序设计竞赛——第二版》的第3章第5节，214页第二点有提到：

将一个点拆做**入点**和**出点**，连一条权值为限制流量的边。

所以就可以这样建图：

$s \rightarrow left \rightarrow mid \rightarrow mid' \rightarrow right \rightarrow t$

下面我们要给这些点分配空间：

我是这样定义的（方便）

```cpp
#define s 1 //源
#define food(x) (x + 1) //食物
#define cow1(x) (f + x + 1) //入点
#define cow2(x) (f + n + x + 1) //出点
#define drnk(x) (f + n + n + x + 1) //饮料
#define t (f + n + n + dr + 2) //汇
```

然后跑Dinic即可（虽说看起来EK可过）

代码如下：

```cpp
#include<bits/stdc++.h>
#define s 1
#define food(x) (x + 1)
#define cow1(x) (f + x + 1)
#define cow2(x) (f + n + x + 1)
#define drnk(x) (f + n + n + x + 1)
#define t (f + n + n + dr + 2)
#define inf (0x7fffffff)
using namespace std;

int get()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 1005, E = 20005;
int n, f, dr;
struct Edge {
	int nxt, v, w;
} edge[E];
int head[N], cnt = 1;
int d[N];
int max_flow;

void addedge(int u, int v, int w)
{
	edge[++cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

void insedge(int u, int v, int w)
{
	addedge(u, v, w);
	addedge(v, u, 0);
}

bool bfs() 
{
	memset(d, 0, sizeof(d));
	queue<int>q;
	q.push(s);
	d[s] = 1;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].v, w = edge[i].w;
			if(d[v] || !w) continue;
			q.push(v);
			d[v] = d[u] + 1;
			if(v == t) return 1;
		}
	}
	return 0;
}

int dfs(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, tot = 0;
    for(int i = head[u]; i; i = edge[i].nxt){
        int v = edge[i].v, w = edge[i].w;
        if((!w) || d[u] + 1 != d[v]) continue;
        int k = dfs(v, min(w, rest)); 
		rest -= k; 
		tot += k;
        edge[i].w -= k;
		edge[i^1].w += k;
    }
    return tot;
}

void dinic() //Dinic板子
{
	while(bfs())
		max_flow += dfs(s, inf);
}

int main()
{
	n = get(), f = get(), dr = get(); 
	for(int i = 1; i <= n; i++) {
		int fi = get(), di = get();
		for(int j = 1; j <= fi; j++) { 
			int k = get();
			insedge(food(k), cow1(i), 1); //食物连入点
		}
		for(int j = 1; j <= di; j++) {
			int k = get();
			insedge(cow2(i), drnk(k), 1); //出点连饮料
		}
		insedge(cow1(i), cow2(i), 1); //入点连出点
	}
	for(int i = 1; i <= f; i++) insedge(s, food(i), 1); //源连食物
	for(int i = 1; i <= dr; i++) insedge(drnk(i), t, 1); //饮料连汇
	dinic();
	printf("%d", max_flow);
	return 0;
}

```

~~自古2P没人看？~~

对这类问题的总结：

既然已经出现了二分图匹配、三分图“匹配”，那么会不会有“四分图匹配”乃至“N分图匹配”的出现呢？

就算来了也不怕了。

我们都可以采取以下的方式连边：

$s \rightarrow a_1 \rightarrow a_2 \rightarrow a_2' \rightarrow ... \rightarrow a_{n-1} \rightarrow a_{n-1}' \rightarrow a_n \rightarrow t$

然后跑最大流就行了。

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2891)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有没有想过直接源点连饮料，饮料连牛，牛连食物，食物连汇点，然后暴力跑匹配？  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;交上去你不$WA$，~~我当场就把这个电脑屏幕吃下去~~才怪了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先这个问题有很明显的限制——每头牛只能享用最多一种饮料和一种食物。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;也就是说，中间的“牛”节点是有流量上限的！  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很好处理，把一个点拆成两个点，在之间连一条容量为$1$的边就可以了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后再跑普通的网络流就可以了。$EK$或者$Dinic$都可以。
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
//#define PAGING

const int INF = 0x3f3f3f3f;
const int MAXSIZ = 505, MAXM = 25005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct edge
{
	int to, nxt, w;
}Graph[MAXM];

struct pre
{
	int v, e;
}p[MAXSIZ];

queue<int> q;

int head[MAXSIZ];
int N, F, D, siz, cnt = 1;
bool visited[MAXSIZ];

void addEdge( const int from, const int to, const int W )
{
	cnt ++;
	Graph[cnt].w = W;
	Graph[cnt].to = to;
	Graph[cnt].nxt = head[from];
	head[from] = cnt;
	#ifdef PAGING
	if( ! W ) return;
	if( W ^ INF ) printf( "    %d -> %d[color = red];\n", from, to );
	else printf( "    %d -> %d[color = blue];\n", from, to );
	#endif
}

void aE( const int from, const int to, const int W )
{
	addEdge( from, to, W );
	addEdge( to, from, 0 );
}

bool BFS( const int S, const int T )
{
	while( ! q.empty() ) q.pop();
	memset( visited, false, sizeof( visited ) );
	memset( p, -1, sizeof( p ) );
	visited[S] = true;
	q.push( S );
	int u, v;
	while( ! q.empty() )
	{
		u = q.front();
		q.pop();
		for( int i = head[u] ; i ; i = Graph[i].nxt )
		{
			v = Graph[i].to;
			if( ! visited[v] && Graph[i].w )
			{
   				visited[v] = true;
				p[v].v = u, p[v].e = i;
				if( v == T ) return true;
				q.push( v );
			}
		}
	}
	return false;
}

int EK( const int S, const int T )
{
	int minVal, res = 0;
	while( BFS( S, T ) )
	{
		minVal = INF;
		for( int u = T ; u ^ S ; u = p[u].v ) minVal = MIN( minVal, Graph[p[u].e].w );
		for( int u = T ; u ^ S ; u = p[u].v ) Graph[p[u].e].w -= minVal, Graph[p[u].e ^ 1].w += minVal;
		res += minVal;
	}
	return res;
}

int main()
{
	#ifdef PAGING
	freopen( "PAG.dot", "w", stdout );
	puts( "digraph PAG{\n" );
	puts( "    rankdir = LR" );
	puts( "    node[shape = circle]" );
	#endif
	int S = 0;
	read( N ), read( F ), read( D );
	S = 2 * N + F + D + 1;
	int f, d, to;
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( f ), read( d );
		for( int j = 1 ; j <= f ; j ++ )
		{
			read( to );
			aE( to, F + i, INF );
		}
		for( int j = 1 ; j <= d ; j ++ )
		{
			read( to );
			aE( N + F + i, 2 * N + F + to, INF );
		}
		aE( F + i, F + N + i, 1 );
	}
	for( int i = 1 ; i <= F ; i ++ )
		aE( 0, i, 1 );
	for( int i = 1 ; i <= D ; i ++ )
		aE( 2 * N + F + i, S, 1 );
	#ifdef PAGING
	puts( "}" );
	#else
	write( EK( 0, S ) ), putchar( '\n' );
	#endif
	return 0;
    //以上奇怪的预编译指令都是用来给样例画图的
}
```

---

## 作者：ViXpop (赞：0)

弱弱的蒟蒻来发自己的第二篇题解了（虽说和第一篇的题目类型其实是差不多，不过蒟蒻大概也就只会这一种题目了）

其实这题也还是~~很水~~的

这题其实也是一个基本的最大流，dinic方法就不多赘述

当然身为一道蓝题，肯定不只是最基本的网络最大流了

由于每种饮料和食物只可能给一头牛吃，当多头牛都想吃这个食物或者喝这个饮料的时候，如果只用普通的最大流，那么这个点一定会被使用多次（就变成了很多牛吃一样食物或者饮料），所以这里需要拆点，即把牛拆成一个实点和一个虚点，中间的流量为1即可，以确保一样食品不会被多次食用。

大概的图就是 源点--食物--牛（实点）--牛（虚点）--饮料--汇点

每条边的流量都是1

# 下面是代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define FOR(i,l,r) for(register int i=l;i<=r;i++)
#define INF 1<<30

using namespace std;

const int N=6000001;
const int M=1001;
int to[N],nxt[N],head[N],cnt=1,w[N],s,t,d[N],q[N],cur[N],orz; 
int n,f,ans;
void qxx(int x,int y,int dis)
{
    to[++cnt]=y;
    w[cnt]=dis;
    nxt[cnt]=head[x];
    head[x]=cnt;
}
void add(int x,int y,int z)
{
	qxx(x,y,z);
	qxx(y,x,0);
}
int bfs()
{
    memset(d,-1,sizeof(d));
    int fr,tail;
    fr=1,tail=0;
    d[s]=0;
    q[1]=s;
    while(tail<fr)
    {
        int k=q[++tail];
        for(register int i=head[k];i;i=nxt[i])
        {
            int kk=to[i];
            if(d[kk]==-1&&w[i])
            {
                d[kk]=d[k]+1;
                q[++fr]=kk;
            }
        }
    }
    if(d[t]==-1)
        return 0;
    else 
        return 1;
}
int dfs(int x,int minflow)
{
    int a=0;
    if(x==t||!minflow)
        return minflow;
    for(register int i=cur[x];i;i=nxt[i])
    {
        int k=to[i];cur[x]=i;
        if(d[k]==d[x]+1&&(a=dfs(k,min(w[i],minflow))))
        {
            w[i]-=a;
            w[i^1]+=a;
            return a;
        }
    }
    return 0;
} //最大流 
int dinic()
{
    ans=0;
    int STO;
    while(bfs())
    {
        STO=0;
        memcpy(cur,head,sizeof(head));
        while(STO=dfs(s,INF))
        {
            ans+=STO;
        }
    }
    return ans;
}//dinic 不多说 
int main()
{
	int k;
	scanf("%d%d%d",&n,&f,&k);// n  牛的头数   f   食物种类数   k  饮料种类数 
	orz=2*n+f+k;//拆点后点的数量 
	s=0,t=orz+1;//源点和汇点 
	FOR(i,1,f)
	{
		add(s,i,1);
	} //连源点 
	FOR(i,1,k)
	{
 		add(2*n+f+i,t,1);
	} //连汇点 
	FOR(i,1,n)
	{
		add(f+i,n+f+i,1);
	} //拆点 
	FOR(i,1,n)
	{ 
		int l,r;
		scanf("%d%d",&l,&r);
		FOR(j,1,l)
		{
			int a;
			scanf("%d",&a);
			add(a,f+i,1);
		}
		FOR(j,1,r)
		{
			int a;
			scanf("%d",&a);
			add(f+n+i,a+f+2*n,1);
		}
	}//如果喜欢就建边 
	printf("%d",dinic());
    return 0;//结束 
}
```


### 这题也有[三倍经验](https://www.luogu.org/discuss/show?postid=69873)的 


 #### 最后，作为一个蒟蒻，当然是膜一下[最强最强的大佬了](https://www.luogu.org/space/show?uid=122988)了



---

## 作者：zyh2015 (赞：0)

网络流重在建图。

其中每一头牛对应一种饮料与食物。

将饮料与食物放在两边，牛放在中间，对应连接边，cap（容量）设为1。

其中要注意，一头牛只能对应一种饮料与一种食物，可能有多种食物指向一头牛，所以要把牛的结点分裂成两个，用边连接，cap为1。

节点分配弄清楚。

（邻接表加边一定要写函数不然代码辣目0。0）

‘’‘

```cpp
#include <cstdio>
#include <cstring>
#define INF 105
using namespace std;
int n,m,p,S,T,u,cnt,l,r;
struct Edge{
    int to,nex,cap;
}e[50000];
int fir[500],cur[500],q[500],d[500];
inline int Min(int x,int y){return x<y?x:y;}
bool bfs() {
    memset(d,-1,sizeof d);
    l=r=0; q[r++]=S; d[S]=0;
    while(l<r){
        int x=q[l++];
        for(int i=fir[x];i!=-1;i=e[i].nex) {
            if(e[i].cap<=0 || d[e[i].to]!=-1) continue;
            q[r++]=e[i].to;
            d[e[i].to]=d[x]+1;
            if(e[i].to==T) return true;
        }
    }
    return false;
}
int dfs(int x,int now) {
    if(!now || x==T) return now;
    int flow=0,f;
    for(int& i=cur[x];i!=-1;i=e[i].nex) {
        if(d[e[i].to]!=d[x]+1) continue;
        f=dfs(e[i].to,Min(now,e[i].cap));
        if(f<1) continue;
        flow+=f; now-=f;
        e[i].cap-=f; e[i^1].cap+=f;
        if(!now) break;
    }
    return flow;
}
int Dinic() {
    int ans=0;
    while(bfs()){
        for(int i=0;i<=T;i++) cur[i]=fir[i];
        ans+=dfs(S,INF);
    }
    return ans;
}
void Add_Edge(int x,int y){
    u++; e[u].to=y; e[u].cap=1; e[u].nex=fir[x]; fir[x]=u;
    u^=1; e[u].to=x; e[u].cap=0; e[u].nex=fir[y]; fir[y]=u;
    return ;
}
int main(){
    memset(fir,-1,sizeof fir);
    scanf("%d%d%d",&n,&m,&p);
    u=-1; T=n*2+m+p+2;
    for(int i=1;i<=m;i++) Add_Edge(S,++cnt);
    for(int i=1;i<=p;i++) Add_Edge(++cnt,T);
    for(int i=1;i<=n;i++){
        ++cnt;
        int mi,pi,x;
        scanf("%d%d",&mi,&pi);
        while(mi--) scanf("%d",&x) , Add_Edge(x,cnt);
        ++cnt; Add_Edge(cnt-1,cnt);
        while(pi--) scanf("%d",&x) , Add_Edge(cnt,x+m);
    }
    printf("%d\n",Dinic());
    return 0;
}
’‘’
```

---

