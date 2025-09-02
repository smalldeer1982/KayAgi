# Airport Express

## 题目描述

在$Iokh$市中，机场快线是市民从市内去机场的首选交通工具。机场快线分为经济线和商业线两种，线路、速度和价钱都不同。你有一张商业线车票，可以坐一站商业线，而其他时候只能乘坐经济线。假设换乘时间忽略不计，你的任务是找一条去机场最快的线路。

## 样例 #1

### 输入

```
4 1 4
4
1 2 2
1 3 3
2 4 4
3 4 5
1
2 4 3```

### 输出

```
1 2 4
2
5```

# 题解

## 作者：览遍千秋 (赞：9)

## 吐槽

一道坑题。

---

## 如何对待商务票

因为商务票只有一张，所以在$k$条边中只有一条边会被选中，很显然，最后这条边会被枚举。

---

## 如何选择使用商务票的边

假设我们正在枚举这条边，现在的边为$(u,v)$，边权为$w$。

那么现在的最小代价肯定为

$$min(dist_{(s,u)_{min}}+dist_{(v,e)_{min}}+w,dist_{(s,v)_{min}}+dist_{(u,e)_{min}}+w)$$

其中$s$代表起点，$e$代表终点，$dist_{(a,b)}$代表$a$到$b$的距离。

从$dist_{(a,b)_{min}}$中，我们可以很清楚地感受到，需要跑最短路。

强烈推荐使用$dijkstra$+堆优化。

![](https://cdn.luogu.com.cn/upload/pic/25108.png)

如果你不确定你的最短路模板是否正确，请[移步](https://www.luogu.org/problemnew/show/P4779)

---

## 两次最短路

经过分析，我们知道要跑最短路，但是由于有两个点分别到$s$和$e$的最短距离，那么就需要以$s$和$e$分别为源，跑单源最短路径。

最短路中需要记录前驱。

---

## 总思路

先读入，注意多组测试数据。

再跑两遍最短路。

枚举$k$条边，对于每一条边$(u,v)$，用上面的公式和当前最优的$ans$比较并记录。

最后输出。（如果挂了先调这个）

---

## 细节

 - 每组测试数据的输出之间需要一个空行
 
 - 最后一组测试数据后不能有空行
 
 - 行末不能有多余的空格
 
---

## 彩蛋

[点这里](https://www.udebug.com/UVa/11374)

可能有点卡

---

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

#define maxn 500
#define maxm 1000
struct node{
    int dis,x;
    bool operator <(const node &a)const
    {
        return dis>a.dis;
    }
};
int h_j[maxn+7],n_j[maxm*2+7],h_s[maxn+7],n_s[maxm*2+7],u_j[maxm*2+7],v_j[maxm*2+7],w_j[maxm*2+7],tot_j,u_s[maxm*2+7],v_s[maxm*2+7],w_s[maxm*2+7],tot_s;
int s,e,n,m,k,x,y,z,p[maxn+7],dis1[maxn+7],dis2[maxn+7],qi1[maxn+7],qi2[maxn+7],ans=0x7fffffff,ansi,ansj;
bool used1[maxn+7],used2[maxn+7];
int u[maxm+7],v[maxm+7],w[maxm+7],stac[maxn+7],cas,xx,top;
void add_j()
{
    u_j[++tot_j]=x,v_j[tot_j]=y,w_j[tot_j]=z;
    n_j[tot_j]=h_j[x],h_j[x]=tot_j;
    u_j[++tot_j]=y,v_j[tot_j]=x,w_j[tot_j]=z;
    n_j[tot_j]=h_j[y],h_j[y]=tot_j;
}
void clear()
{
    memset(h_j,0,sizeof(h_j));
    memset(n_j,0,sizeof(n_j));
    memset(used1,0,sizeof(used1));
    memset(used2,0,sizeof(used2));
    tot_j=0;
    memset(qi1,0,sizeof(qi1));
    memset(qi2,0,sizeof(qi2));
    ans=0x7fffffff;
}
int mian()
{
    while((~scanf("%d%d%d",&n,&s,&e))&&n&&s&&e)
    {
        if(cas++) printf(" ");
//        clear();
        scanf("%d",&m);
        for(register int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            add_j();
        }
        scanf("%d",&k);
        for(register int i=1;i<=k;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            u[i]=x,v[i]=y,w[i]=z;
        }
        for(register int i=1;i<=n;i++) dis1[i]=dis2[i]=0x3f3f3f3f;
        priority_queue<node>q1;
        dis1[s]=0;
        q1.push((node){0,s});
        while(!q1.empty())
        {
            int u=q1.top().x;
            q1.pop();
            if(used1[u]) continue;
            used1[u]=1;
            for(int i=h_j[u];i;i=n_j[i])
            {
                int aa=v_j[i],co=w_j[i];
                if(dis1[aa]>dis1[u]+co)
                {
                    dis1[aa]=dis1[u]+co;qi1[aa]=u;
                    q1.push((node){dis1[aa],aa}); 
                }
            }
        }
        priority_queue<node>q2;
        dis2[e]=0;
        q2.push((node){0,e});
        while(!q2.empty())
        {
            int u=q2.top().x;
            q2.pop();
            if(used2[u]) continue;
            used2[u]=1;
            for(int i=h_j[u];i;i=n_j[i])
            {
                int aa=v_j[i],co=w_j[i];
                if(dis2[aa]>dis2[u]+co)
                {
                    dis2[aa]=dis2[u]+co;qi2[aa]=u;
                    q2.push((node){dis2[aa],aa}); 
                }
            }
        }
        for(register int i=1;i<=k;i++)
        {
            if(dis1[u[i]]+dis2[v[i]]+w[i]<=ans)
            {
                ans=dis1[u[i]]+dis2[v[i]]+w[i];
                ansi=u[i];
                ansj=v[i];
            }
            if(dis1[v[i]]+dis2[u[i]]+w[i]<=ans)
            {
                ans=dis1[v[i]]+dis2[u[i]]+w[i];
                ansi=v[i];
                ansj=u[i];
            }
        }
        xx=ansi;
        top=0;
        if(s==e)
        {
            printf("%d\nTicket Not Used\n0\n",s);
            continue;
        }
        if(ans<=dis1[e])
        {
            while(xx!=s&&xx)
            {
                stac[++top]=xx;
                xx=qi1[xx];
            }
            printf("%d ",s);
            while(top)
            {
                printf("%d ",stac[top--]);
            }
            xx=ansj;
            while(xx!=e&&xx)
            {
                stac[++top]=xx;
                xx=qi2[xx];
            }
            int fuck=1;
            while(fuck<=top)
            {
                printf("%d ",stac[fuck++]);
            }
            printf("%d\n",e);
            printf("%d\n%d\n",ansi,ans);
        }
        else
        {
            int xx=qi1[e];
            while(xx!=s&&xx)
            {
                stac[++top]=xx;
                xx=qi1[xx];
            }
            printf("%d ",s);
            while(top)
            {
                printf("%d ",stac[top--]);
            }
            printf("%d\nTicke Not Used\n%d\n",e,dis1[e]);
        }
    }
}
```

抱歉挖坑了，认真看的话很明显

---

## 作者：Kevin_Wa (赞：7)

恐怖，此题刷新了我的历史观。

$SPFA$居然卡不过$Dij$

是不是此题与$SPFA$有仇。所以卡的他哇哇叫。

商务票只有一张。所以最容易想到的自然是跑$n$遍最短路。

但是$TLE$等着你。

所以要优化。头跑一遍，尾跑一遍。所以只要跑两边最短路。

虽然$SPFA$半死不活。我们还是得救。应为不会打$dij$

上代码：

## Code

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
 
#define maxn 550
#define INF 0x3f3f3f3f
 
struct Edge {
    int from, to, dist;
};
 
struct HeapNode {
    int d, u;
    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};
 
int n, S, E;
vector<Edge> edges;
vector<int> G[maxn];
bool vis[maxn];
int d[maxn], p[maxn], p1[maxn], p2[maxn];
 
void Init(int n) {
    for(int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
}
 
void addEdge(int from, int to, int dist) { // 无向图，每条边需要调用两次addEdge
    edges.push_back((Edge){from, to, dist});
    int x = edges.size();
    G[from].push_back(x-1);
}
void Dijkstra(int s) {
    priority_queue<HeapNode> q;
    for(int i = 1; i <= n; i++) d[i] = INF;
    d[s] = 0;
    memset(vis, false, sizeof(vis));
    q.push((HeapNode){0, s});
    while(!q.empty()) {
        HeapNode x = q.top(); q.pop();
        int u = x.u;
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if(d[e.to] > d[u]+e.dist) {
                d[e.to] = d[u]+e.dist;
                p[e.to] = G[u][i];
                q.push((HeapNode){d[e.to], e.to});
            }
        }
    }
}
 
void printA(int k)
{
    if(k == S) {
        printf("%d", k);
        return ;
    }
    int t = p1[k];
    Edge& e = edges[t];
    printA(e.from);
    printf(" %d", k);
}
void printB(int k)
{
    if(k == E)
    {
        printf(" %d", k);
        return;
    }
    printf(" %d", k);
    int t = p2[k];
    Edge& e = edges[t];
    printB(e.from);
}
int main() {
    int count = 0;
    int N, M, K, X, Y, Z, f[maxn], g[maxn];
    while(~scanf("%d%d%d", &N, &S, &E)) {
        if(count++) printf("\n");
        n = N;
        scanf("%d", &M);
        Init(N);
        while(M--) {
            scanf("%d%d%d", &X, &Y, &Z);
            addEdge(X, Y, Z);
            addEdge(Y, X, Z);
        }
        Dijkstra(S);
        memcpy(f, d, sizeof(d));
        memcpy(p1, p, sizeof(p));
        Dijkstra(E);
        memcpy(g, d, sizeof(d));
        memcpy(p2, p, sizeof(p));
        scanf("%d", &K);
        int ans = f[E];
        int st = -1, ed = -1;
        while(K--) {
            scanf("%d%d%d", &X, &Y, &Z);
            if(ans > Z+f[X]+g[Y]) {
                ans = Z+f[X]+g[Y];
                st = X;
                ed = Y;
            }
            if(ans > Z+f[Y]+g[X]) {
                ans = Z+f[Y]+g[X];
                st = Y;
                ed = X;
            }
        }
        if(st == -1) {
            printA(E);
            printf("\nTicket Not Used\n");
        } else {
            printA(st);
            printB(ed);
            printf("\n%d\n", st);
        }
        printf("%d\n", ans);
    }
    return 0;
}

```


---

## 作者：Chase_s (赞：5)

这道题写的真的...一言难尽（保持微笑）；

注意有坑，可能输出多组数据，每一组之间要空格；图是无向；

这题思路很明确，枚举+最短路；

枚举商务票，从起点到商务票起点跑一遍最短路，反向从终点向商务票终点跑一遍最短路；

注意输出格式；

嗯，，这题不卡spfa，虽然交了十多次都是TLE...最后改着改着就过了。

代码如下：

```
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=1<<29;                           
const int maxn=1100;
const int maxm=maxn*maxn;
int e,head[maxn],pnt[maxm],nxt[maxm],cost[maxm],dist[maxn],pre[maxn],dist1[maxn],pre1[maxn];
int n,m,a,b;
queue<int> q;                                
bool vis[maxn];
void AddEdge(int u,int v,int c)
{
    pnt[e]=v;
    nxt[e]=head[u];
    cost[e]=c;
    head[u]=e++;
}
void Spfa(int st)             //起点到每条商务线的起点的时间
{
    memset(dist,0x3f3f3f,sizeof(dist));          
    dist[st]=0;
    q.push(st);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u]; i!=-1; i=nxt[i])
            if(dist[pnt[i]]>dist[u]+cost[i])
            {
                pre[pnt[i]]=u;
                dist[pnt[i]]=dist[u]+cost[i];
                if(!vis[pnt[i]])
                {
                    q.push(pnt[i]);
                    vis[pnt[i]]=1;
                }
            }
    }
}
void Spfa1(int st)           //每条商务线的终点到终点的时间
{
    memset(dist1,0x3f3f3f,sizeof(dist1));
    dist1[st]=0;
    q.push(st);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u]; i!=-1; i=nxt[i])
            if(dist1[pnt[i]]>dist1[u]+cost[i])
            {
                pre1[pnt[i]]=u;
                dist1[pnt[i]]=dist1[u]+cost[i];
                if(!vis[pnt[i]])
                {
                    q.push(pnt[i]);
                    vis[pnt[i]]=1;
                }
            }
    }
}
void dfs(int u)              //起点到商务线的起点路径
{
    if(u==a)
    {
        printf("%d",u);
        return;
    }
    dfs(pre[u]);
    printf(" %d",u);
}
void dfs1(int u)            //商务线的终点到终点的路径
{
    printf(" %d",u);
    if(u==b)
        return;
    dfs1(pre1[u]);
}

int main()
{
    int x,c1=0;
    while(scanf("%d%d%d",&n,&a,&b)!=EOF)
    {
        if(c1)printf("\n");                         
        scanf("%d",&m);
        memset(head,-1,sizeof(head));
        memset(pre,-1,sizeof(pre));                  
        for(int i=0; i<m; i++)
        {
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            AddEdge(u,v,c);
            AddEdge(v,u,c);
        }
        Spfa(a);
        int num=dist[b];
        memset(pre1,-1,sizeof(pre1));                
        Spfa1(b);
        scanf("%d",&x);
        int k=0,l=0;                                  
        for(int i=0; i<x; i++)
        {
            int w,y,z;
            scanf("%d%d%d",&w,&y,&z);
            if(num>dist[w]+dist1[y]+z)
            {
                num=dist[w]+dist1[y]+z;
                k=w;
                l=y;
            }
            if(num>dist[y]+dist1[w]+z)                   
            {
                num=dist[y]+dist1[w]+z;
                k=y;
                l=w;
            }
        }
        if(k==0)
        {
            dfs(b);
            printf("\nTicket Not Used\n%d\n",num);
        }
        else
        {
            dfs(k);
            dfs1(l);
            printf("\n%d\n%d\n",k,num);
        }
        c1=1;                                                  
    }
}
```



---

## 作者：一扶苏一 (赞：3)

# 最短路问题。

由于贵的路线只能选择一条，我们不妨枚举选择的路线。显然如果一个路线是最短的那么一定被选择的路线两侧是都是最短路。所以我们以s和e为起点和终点各跑一遍最短路，枚举被选择的边即可。

# Code：
```
#include<queue>
#include<cstdio>
#include<cstring>
#ifdef ONLINE_JUDGE
#define putchar(o) \
puts("I am a cheater!")
#endif
#define maxn 5010
#define maxm 20010

inline void qr(int &x) {
	char ch=getchar(),lst=NULL;
	while(ch>'9'||ch<'0') lst=ch,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst=='-') x=-x;
}

template <typename T>
inline T mmax(const T &a,const T &b) {if(a>b) return a;return b;}
template <typename T>
inline T mmin(const T &a,const T &b) {if(a<b) return a;return b;}
template <typename T>
inline T mabs(const T &a) {if(a>=0) return a;return -a;}

——————————————以上是头文件——————

template <typename T>
inline void spaw(T &a,T &b) {T temp=a;a=b;b=temp;}

int n,s,t,m,a,b,cnt,c;
int stack[maxn],top;
int frog[maxn],gorf[maxn],forward[maxn],nxt[maxn];

struct Edge {
	int to,nxt,v;
};
Edge edge[maxm];int hd[maxn],ecnt;
inline void cont(int from,int to,int v) {
	Edge &e=edge[++ecnt];
	e.to=to;
	e.nxt=hd[from];
	e.v=v;
	hd[from]=ecnt;
}

struct M {
	int from,to,v;
};
M MU[maxm];int mcnt;
inline void ade(int from,int to,int v) {
	M &now=MU[++mcnt];
	now.to=to;now.from=from;now.v=v;
}

struct Zay {
	int h,v;
	Zay(int a=0,int b=0) {h=a;v=b;}
	inline bool operator <(const Zay &a) const {
		return this->v>a.v;
	}
};
std::priority_queue<Zay>Q;
bool inlft[maxn];

void clear();
void dij(int,int*,int*);

int main() {
	while(~scanf("%d",&n)) {
		clear();
		qr(s);qr(t);qr(m);
		while(m--) {a=b=c=0;qr(a);qr(b);qr(c);cont(a,b,c);cont(b,a,c);}
		m=0;qr(m);
		for(int i=1;i<=m;++i) {
			a=b=c=0;qr(a);qr(b);qr(c);
			ade(a,b,c);ade(b,a,c);
		}
		dij(s,frog,forward);
		memset(inlft,0,sizeof inlft);
		while(!Q.empty()) Q.pop();
		dij(t,gorf,nxt);
		int used=0,nowd=frog[t];
		while(mcnt) {
			int u=MU[mcnt].from,v=MU[mcnt].to;
			if(frog[u]+gorf[v]+MU[mcnt].v<nowd) nowd=frog[u]+gorf[v]+MU[mcnt].v,used=mcnt;
			--mcnt;
		}
		if(cnt++) putchar('\n');
		if(used){
			int u=MU[used].from;
			while(u) {
				stack[++top]=u;
				u=forward[u];
			}
			while(top) printf("%d ",stack[top--]);
			u=MU[used].to;
			while(u!=t) {
				printf("%d ",u);
				u=nxt[u];
			}
			printf("%d\n%d\n%d\n",t,MU[used].from,nowd);
		}
		else {
			int u=s;  
			while(u!=t) {
				printf("%d ",u);u=nxt[u];
			}
			printf("%d\nTicket Not Used\n%d\n",t,nowd);
		}
	}
	return 0;
}

void clear() {
	memset(hd,0,sizeof hd);
	memset(MU,0,sizeof MU);
	memset(nxt,0,sizeof nxt);
	memset(edge,0,sizeof edge);
	memset(inlft,0,sizeof inlft);
	memset(stack,0,sizeof stack);
	memset(frog,0x3f,sizeof frog);
	memset(gorf,0x3f,sizeof gorf);
	memset(forward,0,sizeof forward);
	s=t=m=ecnt=mcnt=top=0;
	while(!Q.empty()) Q.pop();
}

void dij(int k,int *f,int *l) {
	f[k]=0;
	for(int i=1;i<=n;++i) Q.push(Zay(i,f[i]));
	for(int i=1;i<=n;++i) {
		while(inlft[Q.top().h]) Q.pop();
		int nowh=Q.top().h,nowd=Q.top().v;
		inlft[nowh]=true;
		for(int j=hd[nowh];j;j=edge[j].nxt) {
			int &to=edge[j].to;
			if(f[to]>nowd+edge[j].v) {
				f[to]=edge[j].v+nowd;
				Q.push(Zay(to,f[to]));
				l[to]=nowh;
			}
		}
	}
}
```

---

## 作者：_gcl (赞：2)


###### 闲聊吐槽篇：
非常有意思的一个题， 整体思路比较巧妙， 思考难度不是很高， 但是考察的点很细很细（尤其是输出部分的点，锅太多了）， 此题评分紫应该就是在细节上叭。。。 （那么至此闲聊吐槽结束


题面链接：[题面](https://www.luogu.com.cn/problem/UVA11374)



## **分析算法：**

分析一个问题的算法，这也是算法竞赛中所应做的第一步。

大体题意： 我们要前往飞机场， 这其中有若干个车站， 两车站间有经济线或者是商业线。 商业线和经济线都有一定的时间通往下一个点， 商业线是更省时间的。 我们只能走**一次**商业线， 求此时从起点到终点的**最短时间间隔**。

## 如何算出最短时间

直接想从最短路中进行修改，判断走不走商业线的话，是不太好入手的。但我们要是从商业线入手，便有了突破点。**商业线只能走一次，所以可以枚举到底走哪个商业线，然后对于每个商业线，我们O（1）算出对应的时间花费，最后选取一个最优的即可。**


首先假设此时有一个商业线是 （A,B） （从A点连接到B点），如果想算出此时的答案的话，该怎么办呢？


很显然， 此时的答案Cur_ans=(** _**从起点到A点的时间+从B点到终点的时间+两点所需要花费的时间**_ **） 


我们姑且把它表示成  **Cur_ans=(dis1[A]+dis2[B]+W)**


显然，此时的dis1[ ]数组便存储的是起点到各个点的最短路径，dis2[ ]数组存的便是终点到各个点的最短路径，而W便是这个“商业线”的花费


我们拿Cur_ans和我们的ans比较（ans初值为由起点跑到终点的最短路径），如果小于当前ans，我们记录一下便可。

```cpp
	int ans=dis[e][0];
		for(int i=1;i<=k;i++)
		{
			int u,v,w;
			u=read(),v=read(),w=read();	
			if(ans>dis[u][0]+dis[v][1]+w)
			{
				ans=dis[u][0]+dis[v][1]+w;
				minu=u;//记录商业站起点
				minv=v;//记录商业站终点
			}
			if(ans>dis[v][0]+dis[u][1]+w)//注意，由于是双向边，记得比较两次，要不然会WA
			{
				ans=dis[v][0]+dis[u][1]+w;
				minu=v;//记录商业站起点
				minv=u;//记录商业站终点
			}
		}
```




## 如何统计路径

### 1.记录

我们在进行dijkstra的时候，**每次由 第 i个点推向第j个点时，那么低j个点的上一个路径点便是i**。所以，我们只需要在进行松弛操作更新下一个点的时候，记录一下即可。

非常朴素的dijkstra板子

```cpp
void dijkstra1(int s)
{
	memset(vis,0,sizeof vis);
    priority_queue<node>q;
    dis[s]=0;
    q.push((node){s,0});
    while(!q.empty())
    {
    	node m=q.top();
    	q.pop();
    	if(vis[m.id])continue;
    	vis[m.id]=1;
    	for(int i=head[m.id];i;i=e[i].next)
    	{
    		if(dis[e[i].to]>dis[m.id]+e[i].dis)
    		{
    			dis[e[i].to]=dis[m.id]+e[i].dis;
    			pre[e[i].to]=m.id;//记录节点
    			q.push((node){e[i].to,dis[e[i].to]});
			}
		}
	}
}
```

（dijkstra记得跑两次，一个是起点，一个是终点）

### 2.输出

输出的时候可以用递归。只要前驱节点不是0，那么一直递归下去即可。需要注意的就是这里的输出需要考虑第一个点不要输出空格的问题（卡了我好久）


```cpp
void print1(int x)
{
	if(x==0)return;
	print1(pre[x][0]);
	if(x==s)printf("%d",x);
	else printf(" %d",x);//输出由起点到商业线起点站的路线
}
```

```
void print2(int x)
{
	if(x==0)return;
	printf(" %d",x);
	print2(pre[x][1]);//输出商业线终点站到终点的路线，注意这里的输出格式。
}
```
# 复杂度分析：

##### 预处理：O（mlogn）
##### 枚举商业线：O（k）
##### 总复杂度：O（mlogn+k）



## **~~提醒：记得注意格式问题~~**





---

## 作者：梧桐灯 (赞：2)

此题难度顶多蓝，但是坑的输出让它变成紫……

设：

d[x][0]表示到了点x没有用商业票

d[x][1]表示到了点x已经用过了商业票

然后接下来我们就可以愉快的用dij了……

一下是代码（附有注释）：

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iostream>
#define MP make_pair
using namespace std;

inline void read (int& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	return ;
}

const int N = 503, M = 1003;
int n, sx, zx, m, h[N], tot;
struct stu {
	int v, next;
	int w, tag;
}s[M << 2];

inline void add (const int x, const int y, const int z, const int f) {
	++tot;
	s[tot].v = y;
	s[tot].next = h[x];
	s[tot].w = z;
	s[tot].tag = f;
	h[x] = tot;
	return ;
}

int d[N][2], ans[N], v, vis[N][2];
pair <int, int> pre[N][2], t;

struct QAQ {
	int pos, al, val;
	inline bool operator < (const QAQ& p) const {return val > p.val;}
}p;
priority_queue <QAQ> q;

int main () {
	int QwQ = 0;
	while (~scanf ("%d %d %d", &n, &sx, &zx)) {
		if (QwQ++) putchar ('\n');
		int i, x, y, z;
		memset (h, 0, sizeof (h));
		memset (pre, 0, sizeof (pre));
		tot = v = 0;
		read (m); while (m--) {
			read (x), read (y), read (z);
			add (x, y, z, 0);
			add (y, x, z, 0);
		}//tag为0表示非商业票
		read (m); while (m--) {
			read (x), read (y), read (z);
			add (x, y, z, 1);
			add (y, x, z, 1);
		}
		memset (d, 0x3f, sizeof (d));
		memset (vis, 0, sizeof (vis));
		d[sx][0] = 0;
		q.push ((QAQ) {sx, 0, 0});
		while (!q.empty ()){ 
			p = q.top ();
			q.pop ();
			x = p.pos;
			if (vis[x][p.al]) continue;
			vis[x][p.al] = 1;
			for (i = h[x]; i; i = s[i].next) {
				y = s[i].v;
				if (s[i].tag && p.al) continue; //已经用过就不能再用了
				z = d[x][p.al] + s[i].w;
				int t = p.al + s[i].tag; //已经用过或这次用后，都表示用过了
				if (d[y][t] > z) {
					d[y][t] = z;
					q.push ((QAQ) {y, t, d[y][t]});
					pre[y][t] = MP (x, p.al);
				}
			}
		}
		if (d[zx][0] < d[zx][1]) {
			x = zx, z = 0;
			while (x) {
				ans[++v] = x;
				t = pre[x][z];
				x = t.first, y = t.second;
			}
			printf ("%d", ans[v]);
			for (i = v - 1; i; --i) printf (" %d", ans[i]);
			puts ("\nTicket Not Used");
			printf ("%d\n", d[zx][0]);
		}
		else {
			x = zx, z = 1, y = 0;
			while (x) {
				ans[++v] = x;
				t = pre[x][z];
				x = t.first, z = t.second;
				if (!z && !y) y = x;
			}
			printf ("%d", ans[v]);
			for (i = v - 1; i; --i) printf (" %d", ans[i]);
			printf ("\n%d\n", y);
			printf ("%d\n", d[zx][1]);
		}
	}
	return 0;
}

```

哦对了忘了说输出：


```
XXX
XXX
XXX
一个空格
XXX
XXX
XXX
一个空格
……
XXX
XXX
XXX
一个空格
```

空格不能多不能少……

---

## 作者：Andrew82 (赞：2)

analysis

第一眼看到这个题就知道是分层图最短路了

因为

- 每个点可以做决策
- 决策次数比较少



嗯，这是分层图最短路的特征啊，那就用分层图做吧

这个题的状态呢只有两个，其一就是没有使用商业车票，另一个就是使用了商业车票

两个状态之间的连边也很简单了，设用过商业车票的那一层的点的标号为原来的点的标号+n，于是对于一条u到v的普通路线，连u到v和u+n和v+n（双向边要连两次！），对于一条u到v的商业路线，连u到v+n和v和u+n

然后愉快的跑一个dijkstra就可以AC啦


code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define loop(i,start,end) for(register int i=start;i<=end;++i)
#define anti_loop(i,start,end) for(register int i=start;i>=end;--i)
#define clean(arry,num) memset(arry,num,sizeof(arry))
#define ll long long
template<typename T>void read(T &x){
	x=0;char r=getchar();T neg=1;
	while(r>'9'||r<'0'){if(r=='-')neg=-1;r=getchar();}
	while(r>='0'&&r<='9'){x=(x<<1)+(x<<3)+r-'0';r=getchar();}
	x*=neg;
}
int n,S,E;
const int maxn=500+10;
int m,k;
const int maxm=1000+10;
const int maxk=1000+10;
struct node{
	int e;
	ll w;
	int nxt;
}edge[maxm*10];
int cnt=0;
int head[maxn<<1]; 
inline void addl(int u,int v,ll w){
	edge[cnt].e=v;
	edge[cnt].w=w;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
struct point{
	int pos;
	ll w;
	point():pos(0),w(0){}
	point(int pos,ll w):pos(pos),w(w){}
	friend bool operator<(point a,point b){
		return a.w>b.w;
	}
};
priority_queue<point>q;
ll dis[maxn<<1];
int path[maxn<<1];
int sta[maxn<<1];
int top=0;
void dijkstra(){
	clean(dis,0x3f);
	clean(path,0);
	dis[S]=dis[S+n]=0; 
	q.push(point(S,0));
	q.push(point(S+n,0));
	while(q.empty()==false){
		int f=q.top().pos;
		q.pop();
		for(int i=head[f];i!=-1;i=edge[i].nxt){
			int v=edge[i].e;
			if(dis[v]>dis[f]+edge[i].w){
				dis[v]=dis[f]+edge[i].w;
				path[v]=f;
				q.push(point(v,dis[v]));
			}
		}
	}
	clean(sta,0);
	top=0;
	sta[++top]=dis[E]>dis[E+n]?E+n:E;
	int kkk=(dis[E]>dis[E+n])?E+n:E;
	while(kkk!=S&&path[kkk]!=S){
		//printf("%d\n",kkk);
		kkk=path[kkk];
		sta[++top]=kkk;
	}
	if(S!=E)
		sta[++top]=S;
	int uppos=0;
	while(top){
		if(sta[top-1]>n&&uppos==0)
			uppos=sta[top];
		printf("%d",sta[top]>n?sta[top]-n:sta[top]);
		--top;
		if(top)
			printf(" ");
	}
	printf("\n");
	if(!uppos) printf("Ticket Not Used\n");
	else printf("%d\n",uppos);
	printf("%lld\n",min(dis[E],dis[E+n]));
}
int main(){
	int nfG=0;
	while(scanf("%d%d%d",&n,&S,&E)!=EOF){
		if(nfG)
			printf("\n");
		++nfG;
		clean(head,-1);
		cnt=0;
		read(m);
		loop(i,1,m){
			int xi,yi,zi;
			read(xi);
			read(yi);
			read(zi);
			addl(xi,yi,(ll)zi);
			addl(yi,xi,(ll)zi);
			addl(xi+n,yi+n,(ll)zi);
			addl(yi+n,xi+n,(ll)zi);
		}
		read(k);
		loop(i,1,k){
			int xi,yi,zi;
			read(xi);
			read(yi);
			read(zi);
			addl(xi,yi+n,(ll)zi);
			addl(yi,xi+n,(ll)zi);
		}
		dijkstra();
	}
	return 0;
}
```


关于分层图最短路，蒟蒻做过一个[整理](https://www.cnblogs.com/andrew82/protected/p/11377712.html#%E7%89%B9%E5%BE%81)，各位大佬有兴趣的话可以看一眼

~~（8倍经验警告）~~


---

## 作者：andyli (赞：1)

因为商业线只能坐一站，所以可以枚举坐的是哪一站，比较所有可能性下的最优解。如果可以在$O(1)$的时间内计算出每种方案对应的最优方案，整个问题就可以在$O(K)$的时间内得到解决。  
假设我们用商业线车票从车站$a$坐到车站$b$，则从起点到$a$、从$a$到终点这两部分路线对于“经济线网络”来说都应该是最短路。换句话说，我们只需要从起点开始、到终点结束坐两次单源最短路，记录下从起点到每一个点$x$的最短时间$f(x)$和从每个点$x$到终点的最短时间$g(x)$，则总时间为$f(a)+T(a,b)+g(b)$，其中$T(a,b)$为从$a$坐一站商业线到达$b$的时间。  
算上预处理时间$O(m\log n)$，本算法的总时间复杂度为$O(m\log n+k)$。  
代码如下：
```cpp
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;
const int INF = 0x3f3f3f3f, maxn = 1000005;

struct Edge
{
    int next, to, dist;
    Edge() {}
    Edge(int u, int v, int d) : next(u), to(v), dist(d) {}
};

class Dijkstra
{
  public:
    struct HeapNode
    {
        int d, u;
        bool operator<(const HeapNode &rhs) const
        {
            return d > rhs.d;
        }
    };
    int n, m;
    vector<Edge> edges;
    bool done[maxn];
    int d[maxn], head[maxn];
    int p[maxn];
    void init(int n)
    {
        this->n = n;
        edges.clear();
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to, int dist)
    {
        edges.emplace_back(head[from], to, dist);
        head[from] = edges.size() - 1;
    }
    void dijkstra(int s)
    {
        priority_queue<HeapNode> Q;
        for (int i = 1; i <= n; i++)
            d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        memset(p, 0, sizeof(p));
        Q.push((HeapNode){0, s});
        while (!Q.empty())
        {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u])
                continue;
            done[u] = true;
            for (int v = head[u]; ~v; v = edges[v].next)
            {
                if (d[edges[v].to] > d[u] + edges[v].dist)
                {
                    d[edges[v].to] = d[u] + edges[v].dist;
                    p[edges[v].to] = u;
                    Q.push((HeapNode){d[edges[v].to], edges[v].to});
                }
            }
        }
    }
};

int diss[maxn], ps[maxn], cnt;
Edge edges[maxn << 2];

int main()
{
    int N, S, E, M, kase = 0;
    while (scanf("%d%d%d", &N, &S, &E) == 3)
    {
        if (kase++)
            printf("\n");
        Dijkstra dij;
        dij.init(N);
        scanf("%d", &M);
        while (M--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dij.AddEdge(u, v, w);
            dij.AddEdge(v, u, w);
        }
        scanf("%d", &M);
        cnt = 0;
        for (int i = 1; i <= M; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            edges[++cnt] = Edge(u, v, w);
            edges[++cnt] = Edge(v, u, w);
        }
        dij.dijkstra(S);
        memcpy(diss, dij.d, sizeof(dij.d));
        memcpy(ps, dij.p, sizeof(dij.p));
        dij.dijkstra(E);
        int maxt = diss[E], used = 0;
        for (int i = 1; i <= cnt; i++)
            if (maxt > diss[edges[i].next] + edges[i].dist + dij.d[edges[i].to])
                maxt = diss[edges[i].next] + edges[i].dist + dij.d[edges[i].to], used = i;
        if (used)
        {
            stack<int> st;
            int u = edges[used].next;
            while (u)
            {
                st.push(u);
                u = ps[u];
            }
            while (!st.empty())
                printf("%d ", st.top()), st.pop();
            u = edges[used].to;
            while (u != E)
            {
                printf("%d ", u);
                u = dij.p[u];
            }
            printf("%d\n%d\n%d\n", E, edges[used].next, maxt);
        }
        else
        {
            int u = S;
            while (u != E)
            {
                printf("%d ", u);
                u = dij.p[u];
            }
            printf("%d\nTicket Not Used\n%d\n", E, maxt);
        }
    }
    return 0;
}
```

---

## 作者：何大佰 (赞：0)

商业线只能坐一站，因此考虑枚举坐哪一趟商业线；

假设枚举的商业线从a→b；

则我们还需要知道从S→a和从b→E的最短路；

S到a的最短路很容易，直接从S跑一次dijkstra即可求出从S到任意点的最短路；

从b到E的最短路，可以从b跑一次dijkstra，但b可能是图中的任意点，会T

因为地图是无向图，则从b到E的最短路与从E到b的最短路是一样的，因此直接从E跑一次最短路即可

本题需要打印具体路径，因此在松弛的时候记下前驱节点即可，最后递归打印

不同测试数据间用一个空行隔开。注意：UVA中不得有多的空格和空行

```
#include<bits/stdc++.h>
using namespace std;
const int M=1005,N=505;
int n,e,s,m,pre[N][2],dis[N][2],ans,ticket[2],t;
//pre记录father,dis记录到根节点距离，二维中1--从起点开始，2--从终点开始；
//ans记录最终时间
//ticket记录商业线起终点，若为0则没坐商业线，t为数据组数(为了输出格式)

int to[M<<1],nex[M<<1],fir[N],cnt,val[M<<1];     //经济线 
int to1[M<<1],nex1[M<<1],fir1[N],cnt1,val1[M<<1];//商业线 
bool vis[N];                                  //记录是否在dijk中被确定 
void init()                                      //初始化 
{
  ans=0,cnt=0,cnt1=0,ticket[0]=0,ticket[1]=0;
  memset(pre,0,sizeof(pre));memset(fir,0,sizeof(fir));
  memset(nex,0,sizeof(nex));memset(to,0,sizeof(to));
  memset(val,0,sizeof(val));memset(fir1,0,sizeof(fir1));
  memset(nex1,0,sizeof(nex1));memset(to1,0,sizeof(to1));
  memset(val1,0,sizeof(val1));
}
int Read()
{
  int x=0;
  char c=getchar();
  while(!isdigit(c))
    c=getchar();
  while(isdigit(c))
  {
  	x=(x<<3)+(x<<1)+c-'0';
  	c=getchar();
  }
  return x;
}
void addtree(int From,int To,int w)//经济线 
{
  to[++cnt]=To;
  nex[cnt]=fir[From];
  fir[From]=cnt;
  val[cnt]=w;
}
void addtree1(int From,int To,int w)//商业线 
{
  to1[++cnt1]=To;
  nex1[cnt1]=fir1[From];
  fir1[From]=cnt1;
  val1[cnt1]=w;
}
priority_queue<pair<int,int> >que;//优先队列优化dijk算法
//pair的first记录dis的相反数(从而实现从小到大排列)，second记录该点的编号 

void dijk(int x,int loop)  //loop为0--起点开始，1--终点开始 
{
  memset(vis,0,sizeof(vis));
  dis[x][loop]=0;
  que.push(make_pair(0,x));//传入第一个点的数据 
  while(que.size())
  {
    int u=que.top().second;que.pop();
    if(vis[u]==1) 
      continue;           //被确定了就continue 
    vis[u]=1;            //否则就确定该点 
    for(int i=fir[u];i;i=nex[i])
    {
      int v=to[i];
      if(dis[v][loop]>dis[u][loop]+val[i])//松弛 
      {
      	dis[v][loop]=dis[u][loop]+val[i];
      	pre[v][loop]=u;
      	que.push(make_pair(-dis[v][loop],v));
	  }
	}
  }
}
void print(int u)       //输出起点到商业线前端点或直接到终点 
{
  if(u==0)
    return;
  print(pre[u][0]);
  if(u==s)
    cout<<u;
  else
    cout<<' '<<u;
}
void print1(int v)      //输出商业线之后到终点 
{
  if(v==0)
    return;
  cout<<' '<<v;
  print1(pre[v][1]);
}
int main()
{
  while(scanf("%d%d%d",&n,&s,&e)==3)//多组数据 
  {
  	if(t++) cout<<endl;     //每组数据间的空行,但最后一组不能有空行 
    init();m=Read();
	for(int i=1;i<=m;i++)
	{
	  int a=Read(),b=Read(),c=Read();
	  addtree(a,b,c);addtree(b,a,c);
	}
	int k=Read();
	for(int i=1;i<=k;i++)
	{
	  int a=Read(),b=Read(),c=Read();
	  addtree1(a,b,c);addtree1(b,a,c);
	}
	memset(dis,0x3f,sizeof(dis));
	dijk(s,0);dijk(e,1);
	ans=dis[e][0];          //ans初始为全走经济线 
	for(int u=1;u<=n;u++)   //枚举商业线 
	{
	  for(int j=fir1[u];j;j=nex1[j])
	  {
	    int v=to1[j];
	    if(dis[u][0]+dis[v][1]+val1[j]<ans)
	    {
	  	  ans=dis[u][0]+dis[v][1]+val1[j];
	  	  ticket[0]=u,ticket[1]=v;
	    }
	  }
	}
	if(ticket[0]==0)       //没坐商业线 
	{
	  print(e);
	  cout<<endl<<"Ticket Not Used"<<endl<<ans<<endl;
	}
	else                   //坐了 
	{
	  print(ticket[0]);print1(ticket[1]);
	  cout<<endl<<ticket[0]<<endl<<ans<<endl;
	}
  }
  return 0;
}
```


---

## 作者：鹭天 (赞：0)

#### [题目传送门](https://www.luogu.org/problemnew/show/UVA11374)
### [博客](https://blog.csdn.net/huang_ke_hai/article/details/86971575)
### 题目描述：
##### |中文|
在IokhIokhIokh市中，机场快线是市民从市内去机场的首选交通工具。机场快线分为经济线和商业线两种，线路、速度和价钱都不同。你有一张商业线车票，可以坐一站商业线，而其他时候只能乘坐经济线。假设换乘时间忽略不计，你的任务是找一条去机场最快的线路。
输入格式：
输入包含多组数据。每组数据第一行为333个整数N,SN, SN,S和E(2≤N≤500,1≤S,E≤100)E(2 \leq N \leq 500, 1 \leq S, E \leq 100)E(2≤N≤500,1≤S,E≤100)，即机场快线中的车站总数，起点和终点（即机场所在站）编号。下一行包含一个整数M(1≤M≤1000)M(1 \leq M \leq 1000)M(1≤M≤1000)，即经济线的路段条数。以下MMM行每行3个整数X,Y,Z(1≤X,Y≤N,1≤Z≤100)X, Y, Z(1 \leq X, Y \leq N, 1 \leq Z \leq 100)X,Y,Z(1≤X,Y≤N,1≤Z≤100)，表示可以乘坐经济线在车站XXX和车站YYY之间往返，其中单程需要ZZZ分钟。下一行为商业线的路段条数K(1≤K≤1000)K(1 \leq K \leq 1000)K(1≤K≤1000)，以下KKK行是这些路段的描述，格式同经济线。所有路段都是双向的，但有可能必须使用商业车票才能到达机场。保证最优解唯一。
输出格式：
对于每组数据，输出333行。第一行按访问顺序给出经过的各个车站（包括起点和终点），第二行是换乘商业线的车站编号（如果没有商业线车票，输出Ticket Not Used），第三行是总时间。
##### |英文|
In a small city called Iokh, a train service, Airport-Express,takes residents to the airport more quickly than other transports. There are two types of trains in Airport-Express,the Economy-Xpress and the Commercial-Xpress. They travel at diﬀerent speeds, take diﬀerent routes and have different costs.Jason is going to the airport to meet his friend. He wants to take the Commercial-Xpress which is supposed to be faster,but he doesn't have enough money. Luckily he has a ticket for the Commercial-Xpress which can take him one station forward. If he used the ticket wisely, he might end up saving a lot of time. However, choosing the best time to use the ticket is not easy for him.Jason now seeks your help. The routes of the two types of trains are given. Please write a program to nd the best
route to the destination. The program should also tell when the ticket should be used.
***
**分析：跑两遍dj，预处理出起点和终点到每个端点的距离，处理的时候处理一下点的前驱和后继。然后枚举每一个商业线，将加入商业线之后的长度与ans比较，然后记录商业线的编号。输出时按照商业线的编号再按照它的前驱和后继输出即可（输出后继时需要倒得输出）。**

预处理完dj后，就可以O(1)判断出加入商业线之后的时间：
$$min(dis1[u[i]]+dis2[v[i]]+uv[i],dis1[v[i]]+dis2[u[i]]+uv[i])$$
*备注：其中dis1是当前点到端点的最短路，dis2是当前点到终点的最短路,u[i]和v[i]分别是商业线的两端，uv[i]是乘坐商业线的长度*

那么具体代码如下：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <queue>               
#include <stdio.h>
#include <string.h>
using namespace std;
typedef pair<int , int > pii;
int linkk1[10001],linkk2[10001];
int n,s,e;
bool f;
struct node{
    int y,Next,v;
}e1[10001],e2[10001];
int m1;
int last[10001],Next[10001];
int dis1[10001],dis2[10001];
int len1,len2;
bool vis[1001];
int u[1001],v[1001],uv[1101];
int k;
int m[1001];
void insert1(int x,int y,int z){
    e1[++len1].Next=linkk1[x];
    linkk1[x]=len1;
    e1[len1].y=y;
    e1[len1].v=z;
}
void insert2(int x,int y,int z){
    e2[++len2].Next=linkk2[x];
    linkk2[x]=len2;
    e2[len2].y=y;
    e2[len2].v=z;
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
    while ((~scanf("%d %d %d",&n,&s,&e))&&n&&s&&e){
    	if (f) printf("\n");
    	f=1;
    	len1=len2=0;
    	memset(linkk1,0,sizeof(linkk1));
    	memset(linkk2,0,sizeof(linkk2));
    	memset(e1,0,sizeof(e1));
    	memset(e2,0,sizeof(e2));
        scanf("%d",&m1);
        for (int i=1,x,y,z;i<=m1;i++) scanf("%d %d %d",&x,&y,&z),insert1(x,y,z),insert1(y,x,z),insert2(y,x,z),insert2(x,y,z);
        scanf("%d",&k);
    	for (int i=1;i<=k;i++) scanf("%d %d %d",&u[i],&v[i],&uv[i]);
    	priority_queue < pii , vector < pii > , greater < pii > > q;
   		memset(dis1,20,sizeof(dis1));
   		memset(vis,0,sizeof(vis));
		dis1[s]=0;
		last[s]=0;
    	q.push(make_pair(0,s));
    	while (!q.empty()){
	    	pii t=q.top();q.pop();
	    	int x=t.second,vv=t.first;
//	    	printf("x:%d v:%d\n",x,vv);
	    	if (vis[x]) continue;
	    	vis[x]=1;
	    	for (int i=linkk1[x];i;i=e1[i].Next)
	      	if (dis1[e1[i].y]>vv+e1[i].v)
	          last[e1[i].y]=x,dis1[e1[i].y]=vv+e1[i].v,q.push(make_pair(dis1[e1[i].y],e1[i].y));
		}
//		for (int i=1;i<=n;i++) cout<<dis1[i]<<' '<<last[i]<<endl;
		memset(vis,0,sizeof(vis));
		memset(dis2,20,sizeof(dis2));
		Next[e]=0;
		dis2[e]=0;
		q.push(make_pair(0,e));
		while (!q.empty()){
	    	pii t=q.top();q.pop();
	    	int x=t.second,vv=t.first;
//	    	printf("x:%d v:%d\n",x,vv);
	    	if (vis[x]) continue;
	   	 	vis[x]=1;
	   		for (int i=linkk2[x];i;i=e2[i].Next)
	      	  if (dis2[e2[i].y]>vv+e2[i].v)
	          Next[e2[i].y]=x,dis2[e2[i].y]=vv+e2[i].v,q.push(make_pair(dis2[e2[i].y],e2[i].y));
		}
		int ans=dis1[e];
		int w=0;
		int f1=0,f2=0;
		for (int i=1;i<=k;i++){
		    if (ans>dis1[u[i]]+dis2[v[i]]+uv[i])
		      ans=dis1[u[i]]+dis2[v[i]]+uv[i],f1=u[i],f2=v[i];
		    if (ans>dis2[u[i]]+dis1[v[i]]+uv[i])
		      ans=dis2[u[i]]+dis1[v[i]]+uv[i],f1=v[i],f2=u[i];
		}
		int num=0;
		if (!f1){for (int i=e;i;i=last[i]) m[++num]=i;printf("%d",m[num]);for (int i=num-1;i;i--) printf(" %d",m[i]);printf("\nTicket Not Used\n");}
		else{
	    	for (int i=f1;i;i=last[i]) m[++num]=i;
	    	printf("%d",m[num]);
			for (int i=num-1;i;i--) printf(" %d",m[i]);
			num=0;
			for (int i=f2;i;i=Next[i]) printf(" %d",i);
			printf("\n%d\n",f1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

