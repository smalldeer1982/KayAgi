# [USACO18DEC] Fine Dining G

## 题目描述

漫长的一天结束了，饥困交加的奶牛们准备返回牛棚。

农场由 $N$ 片牧场组成（$2\le N\le 5\times 10^4$），方便起见编号为 $1\dots N$。所有奶牛都要前往位于牧场 $N$ 的牛棚。其他 $N-1$ 片牧场中每片有一头奶牛。奶牛们可以通过 $M$ 条无向的小路在牧场之间移动（$1\le M\le 10^5$）。第i条小路连接牧场 $a_i$ 和 $b_i$，通过需要时间 $t_i$。每头奶牛都可以经过一些小路回到牛棚。

由于饥饿，奶牛们很乐于在他们回家的路上停留一段时间觅食。农场里有 $K$ 个有美味的干草捆（$1 \le K \le N$），第 $i$ 个干草捆的美味值为 $y_i$。每头奶牛都想要在她回牛棚的路上在某一个干草捆处停留，但是她这样做仅当经过这个干草捆使她回牛棚的时间增加不超过这个干草捆的美味值。注意一头奶牛仅仅“正式地”在一个干草捆处因进食而停留，即使她的路径上经过其他放有干草捆的牧场；她会简单地无视其他的干草捆。

## 说明/提示

在这个例子中，牧场 $3$ 里的奶牛可以停留进食，因为她回去的时间仅会增加 $6$（从 $2$ 增加到 $8$），而这个增加量并没有超过干草捆的美味值 $7$。牧场 $2$ 里的奶牛显然可以吃掉牧场 $2$ 里的干草，因为这并不会导致她的最佳路径发生变化。对于牧场 $1$ 里的奶牛是一个有趣的情况，因为看起来她的最佳路径（$10$）可能会因为前去进食而有过大的增加量。然而，确实存在一条路径使得她可以前去干草捆处停留：先到牧场 $4$，然后去牧场 $2$（吃草），然后回到牧场 $4$。

## 样例 #1

### 输入

```
4 5 1
1 4 10
2 1 20
4 2 3
2 3 5
4 3 2
2 7```

### 输出

```
1
1
1```

# 题解

## 作者：Lips (赞：28)

### 康到楼下全用的~~某已死算法~~$SPFA$，窝就来用一个$dijkstra!$

思路：建完图，以 $N$ 为起点跑一边 $dijkstra$，记录 $N$ 到各个点的最短路，再对于每一次的`干草堆操作`，将 $N+1$ 与 $pos$ 之间建一条长度为 $N$ 到这个个点的距离减 $x$ 的边。再以 $N+1$ 为起点跑一边 $dijkstra$ 后，从 $1$ 到 $N-1$ 枚举，如果 $N$ 到 $i$ 的最短路小于 $N+1$ 到 $i$ 的最短路，那么就输出 $1$，否则输出 $0$。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN=50010;
typedef long long ll;
int n,m,k;
ll d[MAXN],a[MAXN],ans[MAXN];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
inline ll read_ll()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
struct edge
{
	int to;
	ll cost;
	edge(int to,ll cost):to(to),cost(cost){}
};
vector<edge>G[MAXN];
typedef pair<ll,int>P;
void dijkstra(int s)
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d[i]=0x3f3f3f3f;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(d[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				q.push(make_pair(d[e.to],e.to));
			}
		}
	}
}
int main()
{
	n=read(),m=read(),k=read();
	while(m--)
	{
		int u=read(),v=read();
		ll w=read_ll(); 
		G[u].push_back(edge(v,w));
		G[v].push_back(edge(u,w));
	}
	dijkstra(n);
	for(register int i=1;i<=n;i++) ans[i]=d[i];
	for(register int i=1;i<=k;i++)
	{
		int pos=read();
		ll x=read_ll();
		G[n+1].push_back(edge(pos,d[pos]-x));
	}
	dijkstra(n+1);
	for(register int i=1;i<n;i++)
		if(d[i]<=ans[i]) printf("%d\n",1);
		else printf("%d\n",0);
	return 0;
}
```
第一篇紫题题解，珂以点个赞在走么？Orz

---

## 作者：Sol1 (赞：24)

来个我自己胡出来的分层图解法~

首先，我们发现一个点上如果有多个草堆，那么显然只有美味值最大的那一捆有意义，所以就转化成了一个点上只有一堆草的问题。

然后我们发现一只牛只能经过一个草堆，所以考虑分两层，第一层表示没有经过草堆，第二层表示已经经过了一个草堆。

现在这道题的做法就很明显了：

对于原图的每一条边 $<u\leftrightarrow v,w>$，连边 $<u\leftrightarrow v,w>$ 和 $<u+n\leftrightarrow v+n,w>$；对于每一个草堆 $(i,y_i)$，连边 $<i+n\rightarrow i,-y_i>$。

然后以 $n$ 为源点跑一遍 SPFA，设结果为 $d_1$；再以 $2n$ 为源点跑一遍 SPFA，设结果为 $d_2$。

最后对于每一个 $i<n$，判断如果 $d_{1,i} \geq d_{2,i}$，则输出 $1$；否则输出 $0$。

问题解决~

最后的复杂度就是 $O(\text{SPFA})$，最坏是 $O(NM)$，但是能过。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

#define int long long

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

struct Edge {
	int to, len, nxt;
	Edge() {
		nxt = -1;
	}
};
int hd[100005], pnt, n, m, k, val[100005], dist[2][100005], inq[100005];
Edge e[500005];

inline void AddEdge(int u, int v, int w) {
	e[++pnt].to = v;
	e[pnt].len = w;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread(); m = qread(); k = qread();
	for (register int i = 1;i <= m;i++) {
		register int u = qread(), v = qread(), w = qread();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
		AddEdge(u + n, v + n, w);
		AddEdge(v + n, u + n, w);
	}
	for (register int i = 1;i <= k;i++) {
		register int x = qread(), y = qread();
		val[x] = Max(val[x], y);
	}
}

inline void SPFA(int s, int k) {
	queue <int> que;
	memset(inq, 0, sizeof(inq));
	memset(dist[k], 0x3f, sizeof(dist[k]));
	dist[k][s] = 0;
	que.push(s);
	inq[s] = 1;
	while (!que.empty()) {
		register int u = que.front();
		que.pop();
		inq[u] = 0;
		for (register int i = hd[u];~i;i = e[i].nxt) {
			if (dist[k][e[i].to] > dist[k][u] + e[i].len) {
				dist[k][e[i].to] = dist[k][u] + e[i].len;
				if (!inq[e[i].to]) {
					inq[e[i].to] = 1;
					que.push(e[i].to);
				}
			}
		}
	}
}

inline void Solve() {
	for (register int i = 1;i <= n;i++) {
		if (val[i]) AddEdge(i + n, i, -val[i]);
	}
	SPFA(n << 1, 1);
	for (register int i = 1;i < n;i++) {
		//printf("%lld %lld\n", dist[0][i], dist[1][i]);
		if (dist[0][i] >= dist[1][i]) puts("1");
		else puts("0");
	}
	//printf("%lld %lld\n", dist[0][n], dist[1][n]);
}

signed main() {
	memset(hd, -1, sizeof(hd));
	Read();
	SPFA(n, 0);
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：super蒟蒻 (赞：12)

   看到此题我首先想到的就是先求每个点去到终点的最短时间，只要把终点作为起点跑一遍$SPFA$或$Dijkstra$就可以了
   
   但是题目要求的是每头牛能否经过某个干草垛在回到终点，且时间与最短的相比不能超过其美味值(不妨记做$v[i]$)，这里的美味值相当于是用来抵消时间的，那么怎么做呢？
   
   定义$f[i]$记做从第$i$个点开始到$n$的最短时间
   
   * 第一种思路就是枚举每个点$i$，每个都跑$1$遍最短路，$f2[j]$就表示从第$i$个点出发，到达点$j$的最短时间，然后再枚举干草垛$k_i(1≤_i≤k)$，对于每个$k_i$，如果使得
   
   $f2[k_i]+f[k_i]-v[k_i]≤f[i]$
   
   那么第$i$头奶牛就符合题意，输出$1$
   
很显然这太暴力，光是枚举就的复杂度就是$O(nk)$，更别提跑最短路的复杂度了，肯定会超时。

那如果把思路转换一下，求**从每个干草垛去到每头奶牛的最短时间**呢？

这时候就产生了一种巧妙的做法：
   * 新建一个点$n+1$，把它与每个干草垛建一条有向边，然后以$n+1$为起点，保证一定会经过草垛，$so$跑一遍$SPFA$就可以求出上面的问题了。虽然现在已求出某个点去到某个草垛的最短时间，但是并不知去的是哪个草垛。所以，就要把新加的有向边的权值设为$f[i]-v[i]$($i$表示第$i$个草垛)，这样一来问题就迎刃而解。
   
至于为什么要这样做，因为$f[i]-v[i]$是用美味值**先去抵消**总的时间，这样就不需要了解去的是哪个草垛了，这里总的时间是指 $f[i]+$某个点到草垛$i$的最短时间 ，跑完第二遍$SPFA$后，把结果放在一个数组里（假设是$D[i]$吧）。最后输出时判断一下$D[i]≤f[i]$，是就输出$1$，否则输出$0$。

顺便贴上代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
//链式前向星存边
struct node{
    int v;
    long long tim;
    node *nxt;
    node(int v=0,int tim=0,node *nxt=NULL):v(v),tim(tim),nxt(nxt){}
}*head[50000];

bool vis[50000];

long long f[50000];//到终点的最短时间

long long f2[50000];//经过草垛的时间

void add(int u,int v,long long c){
    node *A=new node(v,c,head[u]);
    head[u]=A;
}
//spfa模板
void spfa(int s){
    for(int i=1;i<=n;i++)
        f[i]=100000000000000;
    f[s]=0;
    queue<int>q;
    q.push(s);
    memset(vis,0,sizeof(vis));
    vis[s]=true;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        vis[cur]=false;
        for(node *i=head[cur];i!=NULL;i=i->nxt){
            if( f[cur]+i->tim < f[i->v] ){
                f[i->v]=f[cur]+i->tim;
                if(!vis[i->v]){
                    q.push(i->v);
                    vis[i->v]=true;
                }
            }
        }
    }
    return;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int x,y;
        long long z;
        scanf("%d%d%lld",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);//建双向边
    }
    spfa(n);//先求到终点的最短时间
    for(int i=1;i<=n;i++)
        f2[i]=f[i];
    for(int i=1;i<=k;i++){
        int x;
        long long d;
        scanf("%d%lld",&x,&d);
        add(n+1,x,f[x]-d);//新建有向边，并用美味值先抵消总时间
    }
    spfa(n+1);//求出经草垛到终点的时间
    for(int i=1;i<n;i++){
        if(f[i]<=f2[i]) puts("1");
        else puts("0");
    }
    
    return 0;
}
```

---

## 作者：pipiispig (赞：9)

##
和其他人的思路不大一样，这个题并不用2次spfa来做，完全可以用分层图最短路来实现，代码难度偏低，只要能建好图就是个单纯的最短路问题了；
```
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

const int N=5*100005;
const int M=11*10005; 

long long cnt=0,ver[N],head[M],edge[N],nexts[N];//分层图的数组一定要开大，根据层数和点数来确定，如果实在不确定就劲量开大点；

long long vis[M],dis[M];

void add(int x,int y,int z)
{
	ver[++cnt]=y,edge[cnt]=z,nexts[cnt]=head[x],head[x]=cnt;
}

int n,m,k;

void spfa()
{
	queue<int>q;
	memset(dis,0x7f,sizeof(dis));
	q.push(n);
	vis[n]=1;
	dis[n]=0;
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		vis[w]=0;
		for(int i=head[w];i;i=nexts[i])
		{
			int v=ver[i];
			if(dis[v]>dis[w]+edge[i])
			{
				dis[v]=dis[w]+edge[i];
				if(!vis[v])
				{
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}//求最短路的方式都是一样的QwQ,简单吧;

int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
		add(x+n,y+n,z);
		add(y+n,x+n,z);//分层图最短路的难点就在于建图，我们这个题可以建2个图一个代表没有经过甘草的，一个代表经过甘草的，显然x+n是代表吃过草后的路径，而x就是未吃草的路径；
	}
	for(int i=1;i<=k;i++)
	{
		int x;
		long long y;
		cin>>x>>y;
		add(x,x+n,-y);//将有甘草的连边，就是x与x+n相连，边权就是负的美味度;
	}
	spfa();
	for(int i=1;i<n;i++)
	{
		if(dis[i]>=dis[n+i])cout<<1<<endl;//如果吃过草的比没吃草的远就代表不行，因为我们在求最短路的时候已经减去美味度了；
		else cout<<0<<endl; 
	}
} 
```

---

## 作者：Algha_Porthos (赞：8)

这道题的方法之一是**SPFA+超级汇**，
然后比较一个点到终点与到超级汇的距离，得出答案。

举一个例子：(紫色代表美味值)

![PIC1](https://cdn.luogu.com.cn/upload/pic/52459.png)

 
那么我们先SPFA一波，得出每一个数的dis值(橙色)。

![PIC2](https://cdn.luogu.com.cn/upload/pic/52460.png)

然后就是玄学操作：建立一个超级汇(红色)，把美味值为di的节点ai汇集到一个点，并且连上一条长度为（dis2[ai]-di）的边。

![PIC3](https://cdn.luogu.com.cn/upload/pic/52461.png)

为什么？

我们思考一个问题：如果一头牛要去吃唯一的一垛干草，那么这头牛什么条件下会去吃？

在 **多走的路<=美味值** 的时候。

考虑边界情况，自带美味值的节点，当美味值=0，其多走的路=0，那么路径长度应当不改变。如果自带美味值的节点，其美味值>0，那么路径长度会减小美味值。因为一旦到达了任意一个有干草的节点，就不会尝试去访问下一个有干草的节点，那么加上有干草节点的dis值，再减去获得的美味值加成。

是不是**就是另外一个SPFA**？

有一点玄学，可以感性理解一下。

接下来到了坑点时间，对于我做这道题被坑的地方稍作赏析。

1.  注意，和超级汇相连的边**需要为单向边**。因为题目不保证(dis2[ai]-di)的值为正，那么可能出现负环。虽然理论上SPFA可以解决负环，但是这个会被卡住。

2.  **等于的情况也是可以的**！也要输出1！我被这个卡了半个下午！

**不建议您抄袭代码，自认为写得比较详细。如果有问题，请私信我。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[300005],dis2[300005],n,m,s,head[300005],cnt=0,a1,a2,a3,k;
bool vis[300005];
struct Node{
    int nxt,to,w;
}edge[300005];
void addedge(int x,int y,int w){
    edge[++cnt].nxt=head[x];
    edge[cnt].w=w;
    edge[cnt].to=y;
    head[x]=cnt;
}
void spfa(int s){
    queue <int> q;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=edge[i].nxt){
            int v=edge[i].to;
            if(dis[v]>dis[x]+edge[i].w){
                dis[v]=dis[x]+edge[i].w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
int main(){//道路千万条，安全第一条。代码不规范，提交两行泪。 
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i)
        scanf("%d %d %d",&a1,&a2,&a3),addedge(a1,a2,a3),addedge(a2,a1,a3);
    spfa(n);
    for(int i=1;i<=n;++i)
        dis2[i]=dis[i];
    for(int i=1;i<=k;++i)
        scanf("%d %d",&a1,&a2),addedge(n+1,a1,dis2[a1]-a2);
    spfa(n+1);
    for(int i=1;i<=n-1;++i){
        if(dis[i]<=dis2[i])
            printf("1\n");
        else
            printf("0\n");
    }
}
```


---

## 作者：ustze (赞：7)

（考场上把终点看错了调了了2个小时才调出来  
对于此题我能想到的有两种做法  
第一种就是设一个$dis[N][2]$，其中$dis[i][0]=$到i点的最短路,$dis[i][1]=$经过一个草垛后到i点的路径长度减去经过的草垛的美味值的最小值，然后做一遍dij，依照定义更新，最后如果$dis[i][0]<dis[i][1]$就不行,否则可以  

第二种是加点，设$dis[i]$为到i点的最短路  
考虑设置点n+1，然后$addedge(n+1,c,dis[c]-a[c])$
其中c为有干草垛的点，a[c]为其美味值  
样例图及如下，从n+1跑一遍最短路即为所求
![](https://cdn.luogu.com.cn/upload/pic/47087.png)  
代码？还是发一下吧  
第一种
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005,M=200005;
const int inf=0x3f3f3f3f;
int n,m,k;
int dis[N][2],vis[N][2];
int b[M<<1],w[M<<1],nt[M<<1],p[N];
int num;
int c[N];
inline void add(int u,int v,int c){
    num++;
    b[num]=v,w[num]=c,nt[num]=p[u];p[u]=num;
}
struct node{
    int u,pp,dis;
    node(int _u,int _p,int _dis){u=_u,pp=_p,dis=_dis;}
    bool operator<(const node& t)const{
        return dis>t.dis;
    }
};
inline void spfa(int s){
    priority_queue<node> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s][0]=0;
    q.push(node(s,0,0));
    while(!q.empty()){
        int u=q.top().u,pp=q.top().pp;q.pop();
        if(vis[u][pp]) continue;
        vis[u][pp]=1;
        for(int h=p[u];h;h=nt[h]){
            int v=b[h];
            if(pp==0){
                if(dis[v][0]>dis[u][0]+w[h]){
                    dis[v][0]=dis[u][0]+w[h];
                    q.push(node(v,0,dis[v][0]));
                }
                if(c[v]){
                	if(dis[v][1]>dis[u][0]+w[h]-c[v]){
                		dis[v][1]=dis[u][0]+w[h]-c[v];
                		q.push(node(v,1,dis[v][1]));
                    }
                }
            }else {
                if(dis[v][1]>dis[u][1]+w[h]){
                		dis[v][1]=dis[u][1]+w[h];
                		q.push(node(v,1,dis[v][1]));
                }
            }
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    int a,b,t;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&t);
        add(a,b,t);
        add(b,a,t);
    }
    for(int i=1;i<=k;i++){
        scanf("%d%d",&a,&b);
        c[a]=max(c[a],b);
    }
    spfa(n);
    
    for(int i=1;i<n;i++)
        if(dis[i][0]>=dis[i][1]) puts("1");
        else puts("0");
    return 0;
}
```
第二种 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005,M=100005;
const int inf=0x3f3f3f3f;
int n,m,k;
int dis[N],flag[N];
int b[M<<1],w[M<<1],nt[M<<1],p[N];
int num;

inline void add(int u,int v,int c){
    num++;
    b[num]=v,w[num]=c,nt[num]=p[u];p[u]=num;
}
inline void spfa(int s){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    memset(flag,0,sizeof(flag));
    dis[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        flag[u]=0;
        for(int h=p[u];h;h=nt[h]){
            int v=b[h];
            if(dis[v]>dis[u]+w[h]){
                dis[v]=dis[u]+w[h];
                if(!flag[v]) q.push(v),flag[v]=1;
            }
        }
    }
}
int dis0[N];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    int a,b,t;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&t);
        add(a,b,t);
        add(b,a,t);
    }
    spfa(n);
    
    for(int i=1;i<=n;i++) dis0[i]=dis[i];
    for(int i=1;i<=k;i++){
        scanf("%d%d",&a,&b);
        add(n+1,a,dis0[a]-b);
    }
    spfa(n+1);
    
    for(int i=1;i<n;i++)
        if(dis0[i]>=dis[i]) puts("1");
        else puts("0");
    return 0;
}

```

---

## 作者：Schwarzkopf_Henkal (赞：3)

给一个时间复杂度稳定 $O(n\log n)$ 的做法，显然这题肯定是可以用 Dij 的，用了 SPFA 的那些题解也没解释为啥非要用 SPFA 不可。还有什么分层图超级汇什么的根本不知道啥东西啊（

首先分析题意，题目只要我们求每一头牛能不能在某个干草捆停留去吃，条件是增加的时间小于等于干草捆的美味值。那么，这个增加的时间是相对于不吃任何一个干草捆的到达第 $N$ 个农场的最短时间来说的。那么，第一个想法是以 $N$ 为起点跑一遍 Dij 求出各个点到第 $N$ 个农场的最短时间。

那么朴素的想法是对于每一个点，枚举每一个干草捆，能吃掉这个干草捆的条件是：（此处 $i$ 表示点，$j$ 表示干草捆编号）

$$dis_{pos_j,n}+dis_{i,pos_j}-dis_{i,n}\leq deli_{j}$$

实际上这个等价于：

$$dis_{pos_j,n}+dis_{i,pos_j}-deli_{j}\leq dis_{i,n}$$

实际上，这个美味值就相当于从干草捆出发，经过的路程还有干草捆本身到 $N$ 的路程和的减免值，此时某个干草捆可不可行已经和当前是什么点已经“没有”关系了。我们换个思路，从每个干草捆出发，跑一遍最短路，要是满足上面的不等式，那么这个点是能够吃这个干草捆的。

显然对于每一个干草捆都跑一遍最短路效率肯定不够高，题目没有给出 $K$ 的范围感觉还是比较不好。那么我们可以跑一遍“多源最短路”，实质其实就是优先队列 BFS。也就是，相比单源 Dij，这种最短路在最开始的时候加入多个起始点。注意不要在加入堆的时候就将点标记，这样会导致某个点可能不是最优状态。

最后是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t,dis[50005],vis[50005];
vector<pair<int,int> >to[50005];
multiset<pair<int,int> >mts;
struct node{
    int val,cur;
    friend bool operator<(node a,node b){
        return a.val>b.val;
    }
};
priority_queue<node>que;
signed main(){
    scanf("%lld%lld%lld",&n,&m,&t);
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        to[u].push_back(make_pair(v,w));
        to[v].push_back(make_pair(u,w));
    }
    memset(dis,6,sizeof(dis));
    dis[n]=0;
    mts.insert(make_pair(0,n));
    while(1){
        int cur;
        while(!mts.empty()&&vis[mts.begin()->second])
            mts.erase(mts.begin());
        if(mts.empty())
            break;
        cur=mts.begin()->second;
        vis[cur]=1;
        for(int i=0;i<to[cur].size();i++)
            if(!vis[to[cur][i].first]&&dis[to[cur][i].first]>dis[cur]+to[cur][i].second){
                dis[to[cur][i].first]=dis[cur]+to[cur][i].second;
                mts.insert(make_pair(dis[to[cur][i].first],to[cur][i].first));
            }
    }
    memset(vis,0,sizeof(vis));
    for(int i=1,u,v;i<=t;i++){
        scanf("%lld%lld",&u,&v);
        que.push({dis[u]-v,u});
    }
    while(1){
        while(!que.empty()&&vis[que.top().cur])
            que.pop();
        if(que.empty())
            break;
        int cur=que.top().cur,val=que.top().val;
        que.pop();
        vis[cur]=1;
        for(int i=0;i<to[cur].size();i++)
            if(!vis[to[cur][i].first]&&dis[to[cur][i].first]>=val+to[cur][i].second){
                que.push({val+to[cur][i].second,to[cur][i].first});
            }
    }
    for(int i=1;i<n;i++)
        printf("%lld\n",vis[i]);
}
```

---

## 作者：hyfhaha (赞：3)

思路：最短路+dp

1、先跑一遍最短路，计算出没有干草垛最少要多少时间

2、dp求出有干草垛至少需要多少时间，由于dp有后效性，所以用SPFA辅助转移，dp方程和求最短路一模一样，只是先将有干草垛的拉入队列转移，仅此而已。

代码非常简单，可以说是两遍一模一样的SPFA：
```cpp
#include<bits/stdc++.h>
#define maxn 1000001
#define INF 1926081700
using namespace std;
long long cnt,cost[maxn],from[maxn],to[maxn],Next[maxn],head[maxn];
long long dis[maxn],dp[maxn],point[maxn],vis[maxn];
long long n,m,k;
queue<long long>q;
void add(long long x,long long y,long long z){
    cnt++;cost[cnt]=z;
    from[cnt]=x;to[cnt]=y;
    Next[cnt]=head[x];head[x]=cnt;
}
void SPFA(long long S){         //SPFA板子
    for(int i=1;i<=n;i++)dis[i]=INF,vis[i]=0;
    q.push(S);vis[S]=1;dis[S]=0;
    while(!q.empty()){
        long long u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];i!=-1;i=Next[i]){
            long long v=to[i];
            if(dis[v]>dis[u]+cost[i]){
                dis[v]=dis[u]+cost[i];
                if(vis[v]==0){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
void BFS(int S){                //dp
    for(int i=1;i<=n;i++)dp[i]=INF,vis[i]=0;
    //**************************dp唯一与SPFA不同的地方**************************
    for(int i=1;i<=n;i++)
    if(point[i]>0){
        dp[i]=dis[i]-point[i];
        q.push(i);vis[i]=1;
    }
    //**************************dp唯一与SPFA不同的地方**************************
    while(!q.empty()){
        long long u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];i!=-1;i=Next[i]){
            long long v=to[i];
            if(dp[v]>dp[u]+cost[i]){
                dp[v]=dp[u]+cost[i];
                if(vis[v]==0){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)point[i]=0;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=m;i++){
        long long x,y,z;
        scanf("%lld%lld%lld",&x,&y,&z);
        add(x,y,z);add(y,x,z);              //建边
    }
    SPFA(n);
    for(int i=1;i<=k;i++){
        long long x,y;
        scanf("%lld%lld",&x,&y);
        point[x]=max(point[x],y);           //加入干草垛
    }
    BFS(n);
    for(int i=1;i<=n-1;i++){
        if(dp[i]<=dis[i])                   //判断，输出
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}
```

---

## 作者：Parabola (赞：2)

### Part0.题外话

~~奶牛真是社保~~

### Part1.思路

干草捆可以理解为你走到那的最短路减去它的美味值

于是你可以连一条$n -> k$，权为$-y[k]$的边（k是有干草捆的点）

但是这样一定有负环，因为这样子连代表每个干草捆能吃无数遍

所以权值为$-y[k]$的边只能走一次

所以现在的问题就成了这样，给你一张正权无向图和一个起点$st$，再给你$k$条负权有向边，保证这些负权有向边的起点都是$st$，但是负权边只能走一次，求最短路。

然后就有了两个思路

第一个是直接费用流，负权的流量标1，正权流量标inf。

但事实上这个东西不仅慢而且代码长。

你要注意到一个性质

> 负权有向边的起点都是$st$

于是这就成了一个超级源套路题

所以第二个思路就是只用建一个新点让它去连每一个负权边能去到的点，边权为负权边+初始点到它的最短路。

这样就是两个spfa的问题了

### Part3.Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int N = 50000 + 5;

struct spfa{
	int dis[N];
	int tot , head[N] , ver[N << 2] , nxt[N << 2] , val[N << 2];
	bool inq[N];
	spfa () {
		memset(dis , 0x3f , sizeof dis);
		memset(head , 0 , sizeof head);
		tot = 0;
	}
	
	inline void add(int u , int v , int w) {
		ver[++tot] = v; val[tot] = w; nxt[tot] = head[u];
		head[u] = tot;
	}
	
	queue <int> q;
	void main(int st) {
		dis[st] = 0; q.push(st); inq[st] = 1;
		while(q.size()) {
			int u = q.front(); q.pop(); inq[u] = 0;
			for(int i = head[u] ; i ; i = nxt[i]) {
				int v = ver[i];
				if(dis[v] > dis[u] + val[i]) {
					dis[v] = dis[u] + val[i];
					if(!inq[v]) {
						inq[v] = 1;
						q.push(v);
					}
				}
			}
		}
	}
}sol1 , sol2;

int n , m , k;

int main() {
	scanf("%d %d %d" , &n , &m , &k);
	for(int i = 1 , u , v , w ; i <= m ; ++i) {
		scanf("%d %d %d" , &u , &v , &w);
		sol1.add(u , v , w); sol1.add(v , u , w);
		sol2.add(u , v , w); sol2.add(v , u , w);
	}
	sol1.main(n);
	for(int i = 1 , u , x ; i <= k ; ++i) {
		scanf("%d %d" , &u , &x);
		sol2.add(n + 1 , u , sol1.dis[u] - x);
	}
	sol2.main(n + 1);
	for(int i = 1 ; i < n ; ++i)
		printf("%d\n" , sol1.dis[i] >= sol2.dis[i]);
	return 0;
}
```


---

## 作者：Xeqwq (赞：2)

~~这是我第一篇紫题题解+第一篇分层图题解~~  
前置知识：单源最短路径  

---

很容易想出来这道题要从节点 $n$ 向其它所有节点跑最短路径，我们使用SPFA算法，然后我们可以计算出不吃干草的话每头牛到牧场 $n$ 的牛棚要用多久。
接下来解决若是经过干草堆的话每头牛到牧场 $n$ 的牛棚要用多久。

我们先搭建分层图。原图建立在节点 $1$ 至 $n$ 的位置，然后我们再将第二层建立在节点 $n + 1$ 至 $2 \times n$ 的位置。  
第二层记录的是从 $n$ 出来后未经过干草堆的最短路径，所以一旦到了美味值为 $f$ 的干草堆的位置 $i$ ，我们就从第二层图跳到第一层，即建立从 $i + n$ 到 $i$ 的边权为 $-f$ 的边。为了最后的两种走法的比较，我们在这里将这条边的边权设定为 $-f$，这样在后面不用寻找吃的是哪堆干草~~其实我也不会写~~。  
上代码：  
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
int n,m,k;
const int Maxn=100005;
struct Node
{
	int v,w;
	Node(int v,int w):v(v),w(w){};
};
vector<Node> adj[Maxn];
int d[2][Maxn];
bool inq[Maxn];
void spfa(int s,int c)
{
	memset(d[c],0x3f,sizeof(d[c]));
	memset(inq,0,sizeof(inq));
	d[c][s]=0;
	inq[s]=1;
	queue<int> q;
	q.push(s);
	int u,v,w;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		inq[u]=false;
		for(int i=0;i<adj[u].size();i++)
		{
			v=adj[u][i].v;
			w=adj[u][i].w;
			if(d[c][u]+w<d[c][v])
			{
				d[c][v]=d[c][u]+w;
				if(!inq[v])
				{
					q.push(v);
					inq[v]=1;
				}
			}
		}
	} 
}
int f[Maxn];
int main()
{
	cin>>n>>m>>k;
	int u,v,w;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
        //分层图连边，两层不能靠原图的边来连到一起
		adj[u].push_back(Node(v,w));
		adj[v].push_back(Node(u,w));
		adj[u+n].push_back(Node(v+n,w));
		adj[v+n].push_back(Node(u+n,w));
	}
	int num,fl;
	for(int i=1;i<=k;i++)
	{
		cin>>num>>fl;
		f[num]=max(f[num],fl);//每个位置可能有多堆干草，只有最美味的一堆有意义
	}
	for(int i=1;i<=n;i++)
		if(f[i]) adj[i+n].push_back(Node(i,-f[i]));
	spfa(n,0);//不过干草堆的最短路径
	spfa(2*n,1);//过干草堆的最短路径（这两个最短路径只有d[1]至d[n-1]有意义，不过这样写更简便）
	for(int i=1;i<n;i++)
	{
		if(d[0][i]>=d[1][i]) cout<<1<<endl;
		else cout<<0<<endl;
	}
}
```

---

## 作者：万弘 (赞：0)


记 $ dis(i,j) $ 表示 $ i $ 到 $ j $ 的最短距离。

考虑奶牛 $ x $ 经过草堆 $ cur $ 的条件：
$$
dis(x,cur)+dis(cur,n)\le dis(x,n)+v_{cur}
$$
也就是
$$
minv(x)=dis(x,cur)+dis(cur,n)-v_{cur}\le dis(x,n)
$$
 $ dis(x,n) $ 是定值，也就是说要最小化 $ minv(x) $ 。首先可以 $ O(nk) $ 枚举，但是可以直接把 $ dis(cur,n)-v_{cur} $ 做为 $ cur $ 一开始的距离，然后跑一遍多源最短路。注意这里不能用Dij，因为点 $ cur $ 的 $ minv $ 可能被别的点更新，所以只能用 spfa 。复杂度就是 spfa 的复杂度。

```cpp
 
#define MAXN 200011
struct edge{int v,w,nxt;}e[MAXN<<1|1];
int cnt=0,last[MAXN];
void adde(int u,int v,int w){e[++cnt].v=v,e[cnt].w=w,e[cnt].nxt=last[u],last[u]=cnt;}
 
std::queue<int>q;
int disn[MAXN],minv[MAXN],val[MAXN];
bool vis[MAXN],inq[MAXN];
void spfa(int* dis)
{
    while(q.size())
    {
        int u=q.front();q.pop();
        inq[u]=0;
        for(int i=last[u];i;i=e[i].nxt)
        {
            int v=e[i].v;
            if(umin(dis[v],dis[u]+e[i].w))
                if(!inq[v])inq[v]=1,q.push(v);
        }
    }
}
 
int main()
{
    int n=read(),m=read(),k=read();
    while(m--)
    {
        int u=read(),v=read(),w=read();
        adde(u,v,w),adde(v,u,w);
    }
    while(k--){int x=read();umax(val[x],read());}
    memset(disn,0x3f,sizeof disn);
    disn[n]=0,q.push(n),inq[n]=1;
    spfa(disn);
    memset(minv,0x3f,sizeof minv);
    for(int i=1;i<=n;++i)
        if(val[i]>0)minv[i]=disn[i]-val[i],q.push(i),inq[i]=1;
    spfa(minv);
    for(int i=1;i<n;++i)puts(minv[i]<=disn[i]?"1":"0");
    return 0;
}
```



---

