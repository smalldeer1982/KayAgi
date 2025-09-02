# [USACO4.2] 完美的牛栏The Perfect Stall

## 题目描述

农夫约翰上个星期刚刚建好了他的新牛棚，他使用了最新的挤奶技术。

不幸的是，由于工程问题，每个牛栏都不一样。

第一个星期，农夫约翰随便地让奶牛们进入牛栏，但是问题很快地显露出来：每头奶牛都只愿意在她们喜欢的那些牛栏中产奶。

上个星期，农夫约翰刚刚收集到了奶牛们的爱好的信息（每头奶牛喜欢在哪些牛栏产奶）。

一个牛栏只能容纳一头奶牛，当然，一头奶牛只能在一个牛栏中产奶。

给出奶牛们的爱好的信息，计算最大分配方案。

## 说明/提示

$0\le n,m\le 200$，$0\le s_i\le m$。

## 样例 #1

### 输入

```
5 5
2 2 5
3 2 3 4
2 1 5
3 1 2 5
1 2```

### 输出

```
4```

# 题解

## 作者：宁_缺 (赞：22)

两个月前过的二分图模板，没想到两个月后又能在这里邂逅几乎一模一样的题（反正我没看出区别），那就发篇题解纪念吧

二分图压压行真的很短（~~至少比SPFA、BSGS短多了~~）
### 就像这样：
```cpp
#include<bits/stdc++.h>
const int N=201;
int n,m,lk[N],g[N][N],v[N],ans;
bool dfs(int now){
	for(int i=1;i<=n;i++)
		if(!v[i]&&g[now][i]&&(v[i]=1))//其实在&&中修改变量还是挺方便的
			if((!lk[i]||dfs(lk[i]))&&(lk[i]=now))return 1;//与或非优先级懒得算了，于是搞了一堆括号
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,s,x;i<=n;i++){
		scanf("%d",&s);
		while(s--)scanf("%d",&x),g[i][x]=1;
	}
	for(int i=1;i<=n;i++)
		memset(v,0,sizeof(v)),ans+=dfs(i);
	return 0*printf("%d",ans);
}
```
开学后发的第一篇题解（~~看我多懒~~）

---

## 作者：zhaotiensn (赞：18)

（昨天学长上课，讲了一般图的匹配和线性规划，然而我这个连二分图匹配都不会的蒟蒻整节课都在发呆，表示什么也听不懂，所以今天特地找了二分图匹配的题来做。（然而并没什么用，还是看不懂PPT））


这是一道挺水的**二分图匹配**，但对渣渣的我来说已经很难了，理解匈牙利算法是关键，这道题可以算是**匈牙利算法**的模板（听楼下大佬说可以用**网络流**做，但我不会，只能用匈牙利算法）


**二分图：**简单的说就是可以将所有的点分成两个集合，所有的边的端点都在不同的集合，也可以说没有奇数边的环，这题就可以把牛看做一个集合，把牛栏看做另一个集合，一头牛喜欢某个牛栏说明这两点之间有边。


**匈牙利算法：**个人感觉类似**搜索**，所以在代码中就直接用**DFS**实现，其实也可以用**BFS**（稀疏图跑的还是宽搜快，不过稠密图差不多，但DFS实现方便）匈牙利算法核心是寻找**增广路**，在找一个牛的牛栏时，如果遇到一个没有牛的牛栏，说明找到了一条增广路，否则就**取反**，假设这头牛先进这个牛栏，然后本来的牛在进行一次匹配，成功了说明找到增广路，否则这头牛就注定没有牛栏了。

[在网上找到，写的挺好的，讲匈牙利和二分图匹配](http://blog.csdn.net/thundermrbird/article/details/52231639)

代码：







```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,ans,cow[1000];//cow[i]代表第i个牛栏的牛
bool vis[1000],k[1000][1000];//vis记录是否搜过
inline int read(){//快读，挺好用的模板
    int k=0,f=1;char ch=getchar();//字符读入，比较快，大数据会很有用
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){k=k*10+ch-'0';ch=getchar();}
    return k*f;
}
inline void write(int x){//快输,同样是模板
    if(x<0)x=-x,putchar('-');//输出负号
    if(x>9)write(x/10);putchar(x%10+'0');//递归输出
}
inline void writeln(int x){
    write(x);puts("");//学过Pascal的应该都知道这是什么（换行输出）
}
bool dfs(int x){//匈牙利算法主体
    for(int i=1;i<=m;i++){
        if(!vis[i]&&k[x][i]){//如果这个牛栏没有搜过并且牛喜欢这个栏
            vis[i]=true;//先假设这头牛住进了这个牛栏
            if(cow[i]==0||dfs(cow[i])){//如果cow[i]=0说明本来没有牛
                cow[i]=x;//否则把原来的牛赶出去，重新进行匹配
                return true;//有牛栏可以住进，返回真
            }
        }
    }
    return false;//没有牛栏可以住进，返回假
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        int l=read();
        while(l--){
            k[i][read()]=true;//这里用快读就会显得简洁一点
        }
    }
    for(int i=1;i<=n;i++){
        memset(vis,false,sizeof vis);//一开始所有牛栏都没有搜过
        if(dfs(i))ans++;//如果可以住进牛栏答案加一
    }
    writeln(ans);//输出答案
    return 0;
}
```

---

## 作者：Wind_yu (赞：8)

比较水的一道二分图匹配

核心算法是匈牙利算法
（[初学者请看](https://blog.csdn.net/sunny_hun/article/details/80627351)）

简单地说就是把牛和牛栏分成两个集合
每只牛可以匹配至少一个牛栏。
先遍历牛，把第一只牛匹配上第一个牛栏，然后再对第二只牛进行匹配。
如果第二只牛可以匹配到第一个牛栏，而这时第一只牛又有另一种匹配选择，那么第二只牛就匹配上第一个牛栏，第一只牛去找另一个牛栏来匹配，以此类推。

代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;

int n,m,t,ans=0,x_[10001],y_[10001];
bool flag[1001][1001],vis[10001];
//flag记录每只牛可以匹配的牛栏

inline bool find(int x)
{
	int i;
	for(i=1;i<=m;i++)
	{
		if(flag[x][i]&&!vis[i])
		{//如果这只牛能匹配上这个牛栏并且这个牛栏没有被其他牛占据
			vis[i]=true;
			if(y_[i]==-1||find(y_[i]))
            //如果这个牛栏没有被占据或者这个牛栏可以腾出来，即原来占据的牛可以找到另一个牛栏
            //这里使用递归实现匹配
			{
				x_[i]=i;
				y_[i]=x;
				return true;
			}
		}
	}
	return false;
}

inline void match()
{
	int i;
	memset(x_,-1,sizeof(x_));
	memset(y_,-1,sizeof(y_));
	
	for(i=1;i<=n;i++)
	{
		memset(vis,false,sizeof(vis));
		ans+=find(i);
  	  //如果匹配成功，find(i)的值为真，即为1
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int i,j;
	cin>>n>>m;
	
	for(i=1;i<=n;i++)
	{
		cin>>t;
		for(j=1;j<=t;j++)
		{
			int x;
			cin>>x;
			flag[i][x]=true;
  			//第i只牛可以匹配第x个牛栏
		}
	}
	
	match();
	
	cout<<ans;
  
	return 0;
}

```


---

## 作者：ytm2004 (赞：2)

这道题的确可以用二分图匹配来做，但是做完[P2740](https://www.luogu.org/problemnew/show/P2740)网络流裸题之后，懒得再写太多代码，于是就在这基础上改了改。

如果不知道网络流怎么写，可以参考其他人二分图匹配法的题解~~或者随便搜一篇网络流模板题的题解~~。

在原图基础上多建一个起点$1$号点和终点$n+m+2$号点，于是原图点的个数从$n+m$增加到了$n+m+2$。

然后从$1$号点向$2$ ~ $n+1$号点各连一条边，再从$n+2$ ~ $n+m+1$号点向$n+m+2$号点各连一条边，跑网络流就可以啦。

由于本人太懒，只写了EK，没加优化，但并不影响使用效果。

直接贴代码：（已做防抄袭处理）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[maxn][maxn], pre[maxn], flow[maxn];

int bfs(){
	queue<int> q;
	while(!q.empty()) q.pop();
	q.push(1);
	pre[1] = 0;
	for(int i = 2; i <= m; i++) pre[i] = -1;
	flow[1] = inf;
	while(!q.empty()){
		int h = q.front();
		q.pop();
		for(int i = 1; i <= m; i++){
			if(i == h) continue;
			if(pre[i] + 1) continue;
			if(a[h][i] == 0) continue;
			flow[i] = min(flow[h], a[h][i]);
			pre[i] = h;
			q.push(i);
			if(i == m) return flow[i];
		}
	}
	return -1;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		a[1][i + 1] = 1;//从1号点向2 ~ n+1号点连边
		int s, x;
		scanf("%d", &s);
		for(int j = 1; j <= s; j++){
			scanf("%d", &x);
			a[i + 1][x + n + 1] = 1;//正常连边
		}
	}
	for(int i = n + 2; i <= n + m + 1; i++)
		a[i][n + m + 2] = 1;//从n+2 ~ n+m+1号点向n+m+2号点连边
	m += n + 2;//此处是我本来就默认m为点的个数，但这道题我一共创建了n+m+2个点，所以要在m的基础上再加上n+2
	int ans = 0, inc = 0;
    //网络流核心代码
	while((inc = bfs()) + 1){//注意括号顺序
		int x = m;
		while(x != 1){//从后往前找，并连反向边
			a[pre[x]][x] -= inc;
			a[x][pre[x]] += inc;
			x = pre[x];
		}
		ans += inc;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Ireliaღ (赞：2)

## 一个带当前弧优化的$ISAP$题解

### 题目大意

有$n$个牛，$m$个牛棚，每头牛有多个可选择的牛棚，求出让尽可能多的牛住进牛棚

### 前置知识：ISAP算法

可以看~~pica~~学长的[博客](https://www.cnblogs.com/ubospica/p/9974285.html)

### 思路

二分图匹配，可以用最大流，我选择用$ISAP$跑最大流，速度快

### 建图

(1) 把$0$当做超级源点，向从$1$到$n$所有点建立容量为$1$的边，把$n + m + 1$当做超级汇点，从$n + 1$到$n + m$向它建立容量为$1$的边

(2) 对于牛$i$的所有选择$x_1$到$x_s$，从$i$到$n + x_j$建立容量为$1$的边

### 输出

跑$ISAP$，直接输出最大流

### 代码（有当前弧优化）

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using std::queue;

const int MAXN = 205;
const int MAXM = 205;
const int INF = 0x3f3f3f3f;

int n, m;

struct Edge{
    int to, val;
    Edge *next, *opps;
    Edge(int to, int val, Edge* next):to(to), val(val), next(next){}
};

Edge *head[MAXN + MAXM];

void AddEdge(int from, int to, int val) {
    head[from] = new Edge(to, val, head[from]);
    head[to] = new Edge(from, 0, head[to]);
    head[to]->opps = head[from]; head[from]->opps = head[to];
}

namespace ISAP{
    Edge *cur[MAXN + MAXM];
    int dep[MAXN + MAXM], gap[MAXN + MAXM];
    int s, t, maxflow = 0;

    void Bfs() {
        memset(dep, -1, sizeof(dep));
        memset(gap, 0, sizeof(gap));
        dep[t] = 0; gap[dep[t]]++;
        queue<int> q;
        q.push(t);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (Edge *e = head[u]; e; e = e->next) {
                int v = e->to;
                if (dep[v] != -1) continue;
                dep[v] = dep[u] + 1;
                gap[dep[v]]++;
                q.push(v);
            }
        }
    }

    int Dfs(int u, int flow) {
        if (u == t) {
            maxflow += flow;
            return flow;
        }
        int used = 0;
        for (Edge *&e = cur[u]; e; e = e->next) {//当前弧优化，需要取址修改当前弧
            int v = e->to;
            if (dep[v] == dep[u] - 1 && e->val) {
                int mi = Dfs(v, std::min(flow - used, e->val));
                if (mi) {
                    used += mi;
                    e->val -= mi;
                    e->opps->val += mi;
                    if (used == flow) return flow;
                }
            }
        }
        gap[dep[u]]--;
        if (gap[dep[u]] == 0) dep[s] = n + 1;
        dep[u]++;
        gap[dep[u]]++;
        cur[u] = head[u];//复原当前弧
        return used;
    }

    void Work() {
        for (int i = 0; i <= n + m + 1; i++) cur[i] = head[i];
        maxflow = 0;
        Bfs();
        while (dep[s] < n) Dfs(s, INF);
    }
}

int main() {
    memset(head, 0, sizeof(head));
    scanf("%d %d", &n, &m);
    ISAP::s = 0; ISAP::t = n + m + 1;
    for (int i = 1; i <= n; i++) AddEdge(0, i, 1);
    for (int i = 1; i <= m; i++) AddEdge(n + i, n + m + 1, 1);
    for (int i = 1, p; i <= n; i++) {
        scanf("%d", &p);
        for (int j = 1, x; j <= p; j++) {
            scanf("%d", &x);
            AddEdge(i, n + x, 1);
        }
    }
    ISAP::Work();
    printf("%d\n", ISAP::maxflow);
    return 0;
}
/*
5 5
2 2 5
3 2 3 4
2 1 5
3 1 2 5
1 2
*/
```

由于我是个懒人，不愿意算最多有多少条边，所以使用了极其拖慢时间的$new$函数动态开空间建边。但是即使这样，也只跑了$26ms$，说明$ISAP$的效率很高

---

## 作者：vinvor (赞：2)

二分图最大匹配的模型。可以用网络流，但是推荐用匈牙利算法，代码很短，而且效率很高。二分匹配用网络流做就没必要用Dijkstra 了，难写又超时。最简单的搜出一条路就行了，裸的匈牙利不加优化即可，时间足够优。下附C++代码。当然一些NOIP选手该用Djikstra就用吧...。

```cpp
#include<bits/stdc++.h>
using namespace std;
int p,i,j,k,m,n,ans=0;
bool a[205][205];
int cow[205],look[205];
int efpp(int x){
    int j;
    for(j=1;j<=m;j++)
       if(a[x][j]&&!look[j]){
          look[j]=1;
          if(cow[j]==0||efpp(cow[j]))
             { cow[j]=x; return 1; }
       }
    return 0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%d",&k);
        for(j=1;j<=k;j++){ 
            scanf("%d",&p);
            a[i][p]=1;
        }                  
    }
    for(i=1;i<=n;i++){
       memset(look,0,sizeof(look));
       efpp(i);
    }
    for(i=1;i<=m;i++)
       if(cow[i]>0)
          ans++;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：笙歌 (赞：1)

	# 第一眼看是匈牙利算法没错
    
    ## 不加优化的匈牙利能秒A，但还是想用网络流

	**网络流其实也很简单，超级源点与每头牛连一条容量为1的边，每头牛与其喜欢的牛栏连容量为1的边，每个牛栏再与超级汇点连一条容量为1的边。这样图就建好了。**

	然后我是用dinic跑了一遍最大流。
    
    下面上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=1000005;
int n,m,s,t,cnt,x,y,z,head[maxn],dis[maxn],q[maxn];
struct node{
    int next;
    int to;
    int w;
}edge[maxn];
void add(int x,int y,int z){
    cnt++;
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    edge[cnt].w=z;
    head[x]=cnt;
}//链式前向星

int dfs(int d,int ll){
    if (d==t) return ll;
    for (int i=head[d];i!=-1;i=edge[i].next){
        if (dis[edge[i].to]==dis[d]+1 && edge[i].w!=0){
            int ans=dfs(edge[i].to,min(ll,edge[i].w));
            if (ans>0){
                edge[i].w-=ans;
                edge[i^1].w+=ans;
                return ans;
            }
        }
    }
    return 0;
}
int bfs(){
    memset(dis,0,sizeof(dis));
    queue<int> q;
    while (!q.empty()) q.pop();
    dis[s]=1;
    q.push(s);
    while (!q.empty()) {
    int p=q.front();
    q.pop();
    for (int i=head[p];i!=-1;i=edge[i].next){
        if (edge[i].w>0 && dis[edge[i].to]==0){
            dis[edge[i].to]=dis[p]+1;
            q.push(edge[i].to);
        }
    }
    }
    if (dis[t]!=0) return 1;
    else return 0;
}
int dinic(){
    int anss=0;
    while (bfs()){
        int f=-1;
        while (f!=0) {
            f=dfs(s,maxn);
            anss+=f;
            
        } 
    }
    return anss;
}
int main(){
    scanf("%d%d",&n,&m);
    s=0;
    t=n+m+1;
    cnt=0;
    memset(head,-1,sizeof(head));
    for (int i=1;i<=n;++i) {
        add(s,i,1);
        add(i,s,0);
    }
    for (int i=1;i<=m;++i){
        scanf("%d",&x);
        for (int j=1;j<=x;++j){
            scanf("%d",&y);
            add(i,y+n,1);
            add(y+n,i,1);
        }
    }
    for (int i=1;i<=m;++i){
        add(n+i,t,1);
        add(t,n+i,1);
    }//建边
    printf("%d\n",dinic());//dinic跑最大流
    return 0;
}
```

---

## 作者：LlLlCc (赞：0)

典型的**不带权二分图匹配**（~~套模板就好~~）

对于二分图匹配问题，有两种常见的做法，**网络流**和**匈牙利**（网络流要快的多且能解决的问题更多，更灵活，但匈牙利更方便好写，有点类似于线段树和树状数组。）

### 匈牙利 (略)：

简单来说就是一个寻找匹配和谦让的过程，效率不高,个人认为可以跳过直接学网络流。

具体的看着吧：[二分图匹配---匈牙利算法](https://blog.csdn.net/sunny_hun/article/details/80627351)

详见代码（私以为码风还行）：

```
#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
int n,m,x,y,e,Ans,Now[maxn],tot,k;
bool vis[maxn],a[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline bool Dfs(int x){
	for (int i=1;i<=m;i++)
	  if (!vis[i]&&a[x][i]){
	     vis[i]=1;
	     if (!Now[i]||Dfs(Now[i])){Now[i]=x;return 1;}
          }
	return 0;
}
int main(){
   n=read(),m=read();
   for (int i=1;i<=n;i++){
	k=read();
	for (int j=1;j<=k;j++) x=read(),a[i][x]=1;
   }
   for (int i=1;i<=n;i++) Ans+=Dfs(i),memset(vis,0,sizeof vis);
   printf("%d",Ans);
   return 0;
}
```

## 网络流：

网络流是一个很重要的算法，能解决很多复杂的问题。

个人比较喜欢Dinic，时间复杂度n * k * k（EK是n * n * k，稀疏图差不多，但稠密图Dinic要快的多，而且代码量也差不多）

Dinic的算法过程可以直接套模板，我们要掌握的就是图论最重要的一环 **如何建边**

因为有多个源点和多个汇点，通常这种情况下，都是建一个**虚拟的超级源点**和一个**虚拟的超级汇点**，超级源点向所有牛建一条**边长为1**的边，所有牛栏向超级汇点的一条**边长为1**的边，再刷一趟超级源点到超级汇点的Dinic就好了

不会Dinic的看这里：[Dinic](https://baijiahao.baidu.com/s?id=1612179096991409044&wfr=spider&for=pc)

代码（仅供参考）：

```
#include<bits/stdc++.h>
#define maxn 5005
using namespace std;
int n,m,Q[maxn],e,lnk[maxn],nxt[maxn*maxn],S,k,T,son[maxn*maxn],w[maxn*maxn],tot=1,x,y,Dep[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y,int z){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;w[tot]=z;}
inline bool Bfs(){
	int hed=0,til=1;
	memset(Dep,0,sizeof Dep);
	Q[1]=S;Dep[S]=1;
	while (hed!=til){
		hed++;
		for (int i=lnk[Q[hed]];i;i=nxt[i])
		  if (!Dep[son[i]]&&w[i]>0){
		  	Dep[son[i]]=Dep[Q[hed]]+1;
		  	Q[++til]=son[i];
		  }
	}
	return Dep[T];
}
inline int Dfs(int x,int flow){
	if (x==T) return flow;
	int sum=0;
	for (int i=lnk[x];i&&sum<flow;i=nxt[i])
	  if (Dep[son[i]]==Dep[x]+1&&w[i]){
	  	int Now=Dfs(son[i],min(w[i],flow-sum));
	  	w[i]-=Now,w[i^1]+=Now;
	  	sum+=Now;
	  }
	  return sum;
}
inline int Dinic(){
	int Ans=0;
	while (Bfs()) Ans+=Dfs(S,1<<30);
    return Ans;
}
int main(){
	n=read(),m=read();S=1,T=n+m+2;
	for (int i=1;i<=n;i++){
    	k=read();
    	for (int j=1;j<=k;j++) x=read()+n+1,add(i+1,x,1),add(x,i+1,0);
    }
	for (int i=1;i<=n;i++) add(S,i+1,1),add(i+1,S,0);
	for (int i=1;i<=m;i++) add(i+n+1,T,1),add(T,i+n+1,0);
	printf("%d",Dinic());
	return 0;
}
```


---

## 作者：wohohohoho (赞：0)

# 小蒟蒻第一次发题解有点紧张... ...
--------------------------分割线--------------------------

这道题嘛...很明显一道比较水的
## 二分图匹配模版题~~

于是就能十分愉快的用匈牙利算法跑了 ~~可惜不会网络流~~

上代码

```cpp
#include<cstring>
#include<iostream>
using namespace std;
int y[210]={0},n,m,ans=0;
bool used[210]={0},line[210][210]={false};

bool find(int x)//dfs本体
{
	for(int i=1;i<=m;i++)
		if(line[x][i]&&!used[i])
		{
			used[i]=true;
			if(y[i]==0||find(y[i]))
			{
				y[i]=x;
				return true;
			}
		}
	return false;
}

void solve()//匈牙利算法模版
{
	for(int i=1;i<=n;i++)
	{
		memset(used,0,sizeof(used));
		if(find(i))ans++;
	}
}

void input()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int n,x;
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			line[i][x]=true;
		} 
	}
}

int main()
{
	input();
	solve();
	cout<<ans;
	return 0;
}
```
蒟蒻第一篇题解谢谢兹瓷~

膜拜大佬们orz

---

## 作者：贞白周逸民 (赞：0)

## 引导：

首先我们看到这道题，我们必须要明白一个东西叫做匈牙利算法！

在这里我就不多说了。。。

神奇的传送门

[打开二分图的世界（基本算法）](https://blog.csdn.net/Dark_Scope/article/details/8880547)

[打开二分图的世界（基本概念）](https://blog.csdn.net/qq_36345036/article/details/76977294)

------------

## 思路：

那么理解匈牙利算法后，我们就可以很明白的这道题无非就是求**最大匹配集**。这时重点来了：我们要明白如何放置两个集合，使其方便我们求**最大匹配集**。根据题意，那么我们可以把奶牛放在一个集合里，牛棚放在一个集合里。然后就是用匈牙利算法跑出**最大匹配集**。



------------

### **个人建议**：跟着代码走一遍，自己在草稿纸上画画。

详解见代码：

```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
int n, m, e;
vector<int> v[2009];
bool bi[2009];  // 标记一次 dfs 过程中，Y 集合中的顶点是否已访问
int ans[2009]; // 标记 Y 集合中的顶点匹配的 X 集合中的顶点编号

bool dfs(int x)
{
	for (int i = 0; i < v[x].size(); i++){
		int mmp = v[x][i];      // 不要太在意变量名，这是只是来控诉一下我以前在长沙学这个的绝望。 
		if (!bi[mmp]){ // 如果 Y 集合中的 x 还没有被访问
			bi[mmp] = 1;
			if (ans[mmp] == -1 || dfs(ans[mmp])){  // 如果 mmp 没有匹配点，或 mmp 的匹配点能找到一条到一个未匹配点的增广路，则将 mmp 的匹配点设为 x 
				ans[mmp] = x;
				return 1;
			}
		}
	}
	return 0; // 如果没有找到增广路 
 } 

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		int a; scanf("%d", &a);
		for (int j = 1; j <= a; j++){
			int b; scanf("%d", &b);
			v[i].push_back(b);
		}
	}
	
	int ansx = 0;
	memset(ans, -1, sizeof(ans)); // 初始将所有 Y 集合中顶点的匹配编号设为 -1
	
	for (int i = 1; i <= n; i++){
		memset(bi, 0, sizeof(bi));// 进行 dfs 前，将 bi 清空
		if (dfs(i))	ansx++; // 如果找到增广路，则将 ansx累加 1
	}
	
	printf("%d", ansx); // ansx就是 最大匹配数 
	return 0;
    //功德圆满
}
```

---

## 作者：Chicago_01 (赞：0)

## 题面

农夫约翰上个星期刚刚建好了他的新牛棚，他使用了最新的挤奶技术。不幸的是，由于工程问题，每个牛栏都不一样。第一个星期，农夫约翰随便地让奶牛们进入牛栏，但是问题很快地显露出来：每头奶牛都只愿意在她们喜欢的那些牛栏中产奶。上个星期，农夫约翰刚刚收集到了奶牛们的爱好的信息（每头奶牛喜欢在哪些牛栏产奶）。一个牛栏只能容纳一头奶牛，当然，一头奶牛只能在一个牛栏中产奶。

给出奶牛们的爱好的信息，计算最大分配方案。

## 题意

如题面。

## 题解

1. 每只奶牛只喜欢在自己喜欢的牛棚里面产奶。（匹配）

2. 一个牛棚只能容纳一头奶牛。

3. 最大的分配方案。

匈牙利算法(匹配算法)，个人感觉实质上就是一个DFS的匹配算法。

伪代码：
```
bool dfs(int x)
{
	while(找到Xi的关联顶点Yj){
          if(顶点Yj不在增广路径上){
                将Yj加入增广路
               if(Yj是未覆盖点或者Yj的原匹配点Xk能找到增广路径){ //扩充集合M
                      将Yj的匹配点改为Xi;
                      返回true;
           }
      }
               返回false;
}
```

根据题意可以知道这是一道匈牙利算法的模板题。于是开始根据伪代码来造代码。

## 代码

### 代码1(my code)

```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 10010;
const int maxm = 10010;
int n,m,tong[maxm],ans;
bool vis[maxn],love[maxn][maxm];

inline int read(){
    int k=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){k=k*10+ch-'0';ch=getchar();}
    return k*f;
}

inline void init()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int l=read();
        while(l--){
            love[i][read()]=true;
        }
    }
}

bool dfs(int x)
{
    for(int i = 1;i <= m;++i)
    {
        if(!vis[i] && love[x][i])
        {
            vis[i] = true;
            if(tong[i]==0 || dfs(tong[i]))
            {
                tong[i] = x;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char const *argv[])
{
    init();
    
    for(int i = 1;i <= n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }

    cout << ans;

    return 0;
}
```

### 代码2(rank 1)

```
#include <cstdio>
#include <cstring>
using namespace std;
#define M(x) memset(x, false, sizeof(x))
const int maxn = 205;
int N, M, ans, link[maxn];
bool vis[maxn], A[maxn][maxn];
bool dfs(int x){
    for(int i = 1; i <= N; i++)
        if(A[x][i] && !vis[i]){
            vis[i] = true;
            if(!link[i] || dfs(link[i])){
                link[i] = x;
                return true;
            }
        }
    return false;
}
inline int GetInt(){
    char x;
    int ret;
    while((x = getchar()) < '0' || x > '9');
    ret = x - '0';
    while((x = getchar()) >= '0' && x <= '9') ret = ret * 10 + x - '0';
    return ret;
}
int main(){
    N = GetInt(), M = GetInt();
    for(int i = 1; i <= N; i++){
        int sum;
        sum = GetInt();
        for(int j = 1, OP; j <= sum; j++){
            OP = GetInt();
            A[i][OP] = true;
        } 
    }
    for(int i = 1; i <= N; i++){
        M(vis);
        if(dfs(i)) ans++;
    } 
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一道题采用匈牙利算法来做

匈牙利算法解释在http://caioj.cn/problem.php?id=1122

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y,next;//记录边 
}a[41000];int len,last[210];
inline void ins(int x,int y)//建边 
{
	len++;
	a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int match[210];//牛栏i的牛 
bool v[210];//第i个牛栏是否被查找过 
bool find_niulang(int x)//核心部分 
{
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		if(v[y]==true)//如果没有被找过 
		{
			v[y]=false;//设置为找过 
			//两种情况：如果这个牛栏没有牛 
			//或者让牛栏里面的牛重新找牛栏并且能找到牛栏 
			if(match[y]==0 || find_niulang(match[y])==true) 
			{
				match[y]=x;//匹配成功
				return true;
			}
		}
	}
	return false;
}
int main()
{
	int n,m,x,y,t,i,ans;
	scanf("%d%d",&n,&m);
	for(x=1;x<=n;x++)
	{
		scanf("%d",&t);//建立边 
		while(t--)
		{
			scanf("%d",&y);
			ins(x,y);
		}
	}
	ans=0;
	for(i=1;i<=n;i++)//枚举牛 
	{
		if(ans==m) break;//如果找到了m个牛栏，就不用管了 
		memset(v,true,sizeof(v));//把牛栏全部设置为没有找过 
		if(find_niulang(i)==true) ans++;//如果能成功匹配
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zhangjianweivv (赞：0)

~~其实写这个题解是怕自己以后忘记网络流怎么打了，然后就可以随时回来看一看~~

好的切入正题。

我网络流是看视频学的dinic算法~~（请允许我来一波广告，[就是在这个网站上学的](http://caioj.cn/)）~~，OK，因为有地址了，就不多逼逼了。

但是这题和网络流模板有一丝不同，这题的原点和汇点处理起来比较麻烦。所以可以去做一做[这道题](http://caioj.cn/problem.php?id=1116)，做完就会用别样的收获~~（貌似广告打太多了。。。）~~

好，那就上代码吧。。。
```
/*
ID:zhangji78
LANG:C++
TASK:stall4
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=99999999;
struct node
{
	int x,y,c,next,other;
}a[21000];int len,last[21000];
int st,ed,n,m;
void ins(int x,int y,int c)
{
	int k1,k2;
	len++;k1=len;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;k2=len;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[k1].other=k2;
	a[k2].other=k1;
}
int list[2100],head,tail,h[2100];
bool bfs()
{
	memset(h,0,sizeof(h));h[st]=1;
	list[1]=st;head=1;tail=2;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k;k=a[k].next)
		{
			int y=a[k].y;
			if(h[y]==0&&a[k].c>0)
			{
				h[y]=h[x]+1;
				list[tail]=y;
				tail++;
			}
		}
		head++;
	}
	if(h[ed]==0)return false;
	else return true;
}
int findflow(int x,int f)
{
	if(x==ed)return f;
	int s=0;
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		if(h[y]==(h[x]+1)&&a[k].c>0&&s<f)
		{
			int t=findflow(y,min(f-s,a[k].c));
			s+=t;a[k].c-=t;a[a[k].other].c+=t;
		}
	}
	if(s==0)h[x]=0;
	return s;
}
int main()
{
	//freopen("stall4.in","r",stdin);
	//freopen("stall4.out","w",stdout);
	scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	st=0;ed=n+m+1;
	for(int i=1;i<=n;i++)ins(st,i,1);
	for(int i=1;i<=n;i++)
	{
		int ss;scanf("%d",&ss);
		for(int j=1;j<=ss;j++)
		{
			int y;scanf("%d",&y);
			ins(i,n+y,1);
		}
	}
	for(int i=1;i<=m;i++)ins(n+i,ed,1);
	int ans=0;
	while(bfs()==true)ans+=findflow(st,inf);
	printf("%d\n",ans);
	return 0;
}
```
~~我不会告诉你我是一遍AC的~~

作为小蒟蒻表示非常开心

~~（虽然没什么大不了的）~~

---

## 作者：依依 (赞：0)

发现一道网络流水题（模板）。

设源点S=0，汇点T=n+m+1。

从S向每头牛建一条流量为1的边。

从每头牛向它们喜欢的牛栏建一条流量为1的边。

从牛栏向T建一条流量为1的边。

然后跑最大流就可以了。

(*^▽^*)
[允许我刷一波访问量](http://www.cnblogs.com/adelalove/p/8525545.html)

---

## 作者：codesonic (赞：0)

~~昨天刚会写的二分图匹配~~

二分图匹配入门题

因为牛喜欢在某些牛栏内挤奶，所以可以用边来表示

很显然牛和牛之间或牛栏和牛栏之间不可能连边

而一个牛栏只能容纳一头牛

很容易就能想到二分图匹配

这里我用了匈牙利算法求最大匹配数

匈牙利算法通过不断找增广路来找到最大匹配（增广路定理：不断寻找增广路就可以找到最大匹配）

需要这方面详细介绍的可以出门左转去模版题题解区：

https://www.luogu.org/problemnew/solution/P3386

以下是C++代码（前向星存图）

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N=10005;
const int M=500005;
int tot,head[N];
int num_nodes;
int num_left;
int num_right;
int num_edges;
int matching_Left[N],matching_Right[N];
bool check[M];

struct Edge{
    int u,v,next;
}G[M];

inline void addedge(int u,int v){
    G[++tot].u=u;
    G[tot].v=v;
    G[tot].next=head[u];
    head[u]=tot;
}//前向星存图

bool dfs(int u){
    for(int i=head[u];i;i=G[i].next){
        int v=G[i].v;
        if(!check[v]){
            check[v]=true;
            if(matching_Left[v]==-1||dfs(matching_Left[v]))//是未盖点
              {
                matching_Left[v]=u;
                matching_Right[u]=v;//交换路径
                return 1;//返回成功
            }
        }
    }
    return 0;//没有增广路，返回失败
}

int hungarian(){
    int ans=0;
    memset(matching_Left,-1,sizeof(matching_Left));
    memset(matching_Right,-1,sizeof(matching_Right));
    for(int u=1;u<=num_left;++u){//从左边的点（牛）一个一个寻找
        memset(check,0,sizeof(check));
        if(dfs(u))
            ans++;
    }
    return ans;
}

int main()
{
    scanf("%d%d",&num_left,&num_right);
    num_nodes=num_left+num_right;
    for(int i=1;i<=num_left;i++){
        int x;
        scanf("%d",&x);
        for(int j=1;j<=x;j++){
            int y;
            scanf("%d",&y);
            addedge(i,y);
        }
    }
    printf("%d",hungarian());
    return 0; 
}
```

---

## 作者：Alcohol_C (赞：0)

第一这个题显然是一个二分图匹配问题

所以可以直接跑匈牙利或网络流。

第二网络流更快

**所以我选择网络流。(很棒的理由)**

建图：S连每头牛，权值为1；每头牛连对应牛栏，权值为1；每个栏连T，权值为1；

此时最大流即为答案，直接输出即可。

具体详见代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,s=0,t,num_e=1,m,l,ss;
const int maxn=10005;
const int inf=2147483647;
int head[maxn],dis[maxn];
struct edge{
    int to,rest,next;
}e[maxn];
inline void add_edge(int x,int y,int z){
    e[++num_e].to=y;e[num_e].rest=z;e[num_e].next=head[x];head[x]=num_e;
    e[++num_e].to=x;e[num_e].rest=0;e[num_e].next=head[y];head[y]=num_e;
}
bool bfs(){
    memset(dis,0,sizeof(dis));
    queue<int> q;
    while(!q.empty()) q.pop();
    q.push(s);
    dis[s]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].next){
            if(e[i].rest&&!dis[e[i].to]){
                dis[e[i].to]=dis[x]+1;
                q.push(e[i].to);
            }
        }
    }
    if(dis[t]) return true;
    return false;
}
int dfs(int x,int minn){
    if(x==t) return minn;
    int sum=0,qq=0;
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to;
        if(e[i].rest&&dis[y]==dis[x]+1){
            qq=dfs(y,min(e[i].rest,minn-sum));
            e[i].rest-=qq;
            e[i^1].rest+=qq;
            sum+=qq;
            if(sum==minn) return sum;
        }
    }
    if(!sum) dis[x]=0;
    return sum;
}
int dinic(){
    int anss=0;
    while(bfs()) anss+=dfs(s,inf);
    return anss;
}
int main(){
    scanf("%d%d",&n,&m);
    t=m+n+1;
    for(int i=1;i<=n;i++) add_edge(s,i,1);
    for(int i=1;i<=m;i++) add_edge(n+i,t,1);
    for(int i=1;i<=n;i++){
        scanf("%d",&ss);
        for(int k=1;k<=ss;k++){
            scanf("%d",&l);
            add_edge(i,l+n,1);
        }
    }
    cout<<dinic();


}

```

---

## 作者：Cet6_427 (赞：0)

匈牙利算法求增广路：初始时，设M为空集，然后反复在二分图中找一条关于M的增广路P，然后进行异或以增加一个匹配，直到二分图中不再存在二分图的增广路。

二分图匹配的匈牙利算法适用于边较多的稠密图，因为边多所以查找增广路的时候速度很快，时间复杂度为O(N^3)







```cpp
#include <cstdio>
#include <cstring>
using namespace std;
#define M(x) memset(x, false, sizeof(x))
const int maxn = 205;
int N, M, ans, link[maxn];
bool vis[maxn], A[maxn][maxn];
bool dfs(int x){
    for(int i = 1; i <= N; i++)
        if(A[x][i] && !vis[i]){
            vis[i] = true;
            if(!link[i] || dfs(link[i])){
                link[i] = x;
                return true;
            }
        }
    return false;
}
inline int GetInt(){
    char x;
    int ret;
    while((x = getchar()) < '0' || x > '9');
    ret = x - '0';
    while((x = getchar()) >= '0' && x <= '9') ret = ret * 10 + x - '0';
    return ret;
}
int main(){
    N = GetInt(), M = GetInt();
    for(int i = 1; i <= N; i++){
        int sum;
        sum = GetInt();
        for(int j = 1, OP; j <= sum; j++){
            OP = GetInt();
            A[i][OP] = true;
        } 
    }
    for(int i = 1; i <= N; i++){
        M(vis);
        if(dfs(i)) ans++;
    } 
    printf("%d", ans);
    return 0;
}

```

---

## 作者：cheeseYang (赞：0)

今天老师刚讲了网络流的做法，手打竟然过了，于是来一发题解

建图是一个问题，首先要建立一个源点和汇点，正如楼下所说，然后把源点的前驱赋值为-1，具体看代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n,m,x,y,c[405][405],f[405][405],num,vis[405],pre[405],ans;
bool YYY=1;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>num;
        c[0][i]=1;
        for(int j=1;j<=num;++j){
            cin>>x;
            c[i][n+x]=1;//n+x是为了不让第二维与第一维产生相等的情况。    
        }
    }
    for(int i=n+1;i<=n+m+1;++i)
        c[i][n+m+1]=1;//我们把源点设为c[0],汇点设为c[n+m+1]，这样就可以建好图了
    while(YYY){
        YYY=0;
        memset(vis,0,sizeof(vis));
        queue<int> q;
        q.push(0);
        vis[0]=1;
        pre[0]=-1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=1;i<=n+m+1;++i)
                if(!vis[i] && c[u][i]>f[u][i]){
                    q.push(i);
                    vis[i]=1;
                    pre[i]=u;
                    if(i==n+m+1){
                        YYY=1;    
                        break;
                    }
                }
            if(YYY)break;
        }
        int k=n+m+1,pj=1000000000;
        while(pre[k]!=-1){
            int u=pre[k],v=k;
            pj=min(pj,c[u][v]-f[u][v]);
            k=u;
        }
        k=n+m+1;
        while(pre[k]!=-1){
            int u=pre[k],v=k;
            f[u][v]+=pj;
            c[v][u]+=pj;//反向弧是为了给我们有撤回的余地，即寻找增广路
            k=u;
        }
    }
    for(int i=1;i<=n+m+1;++i)ans+=f[0][i];//输出，要输出所有从0出去的流的总和
    cout<<ans;
    return 0;
}
```

---

## 作者：Great_Influence (赞：0)

我们老师说了，所有二分匹配的题都可以用网络流做。

并且，这题是在网络流题目中间的。

# 所以，这题怎么能不用网络流做呢？

只要创造一个源点并连接所有的牛，在创造一个汇点并连接所有牛栏，这道题便转化为求源点到汇点的最大流问题。

我的做法是Dinic。



代码：

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<iostream>
#include<map>
#include<queue>
#include<algorithm>
#include<stack>
#define For(i,a,b) for((i)=(a);(i)<=(b);++(i))
#define Forward(i,a,b) for((i)=(a);(i)>=(b);--(i))
using namespace std;
inline void read(int &x)
{
    int s=0,f=1;
    char k=getchar();
    while(!isdigit(k)&&k!='-')k=getchar();
    if(k=='-')
    {
        f=-1;
        k=getchar();
    }
    while(isdigit(k))
    {
        s=(s<<3)+(s<<1)+(k^'0');
        k=getchar();
    }
    x=s*f;
}
struct edge
{
    int v,w,nex;
}p[200*200+100];
int n,m,level[500],he[500],e=1;
void add(int u,int v,int w)
{
    p[++e].v=v;
    p[e].w=w;
    p[e].nex=he[u];
    he[u]=e;
}
queue<int>G;
bool bfs()
{
    memset(level,0,sizeof(level));
    level[1]=1;
    G.push(1);
    while(!G.empty())
    {
        int u=G.front(),v=he[u];
        G.pop();
        while(v)
        {
            if(p[v].w&&!level[p[v].v])
            {
                level[p[v].v]=level[u]+1;
                G.push(p[v].v);
            }
            v=p[v].nex;
        }
    }
    return level[n+m+2];
}
int dfs(int x,int flow)
{
    if(x==m+n+2||!flow)return flow;
    int v=he[x],sum=0;
    while(v)
    {
        if(p[v].w&&level[p[v].v]==level[x]+1)
        {
            int f=dfs(p[v].v,min(p[v].w,flow));
            p[v].w-=f;
            p[v^1].w+=f;
            sum+=f;
            flow-=f;
        }
        v=p[v].nex;
    }
    return sum;
}
int Dinic(void)
{
    int ans=0;
    while(bfs())ans+=dfs(1,1);
    return ans;
}
int main(void)
{
    int s,v,w,i,j;
    read(n);
    read(m);
    For(i,1,n)
    {
        read(s);
        For(j,1,s)
        {
            read(v);
            add(i+1,v+n+1,1);
            add(v+n+1,i+1,0);
        }
    }
    For(i,1,n)
    {
        add(1,i+1,1);
        add(i+1,1,0);
    }
    For(i,1,m)
    {
        add(i+n+1,n+m+2,1);
        add(n+m+2,i+n+1,0);
    }
    printf("%d\n",Dinic());
    return 0;
}
```

---

## 作者：songyuchen (赞：0)

这是一道二分图最大匹配的模板题。这里使用匈牙利算法解决。


对于一只牛和其喜欢的牛棚，我们连一条有向边。我们定义对于牛棚u，Match[u]为其匹配的牛的编号。


我们依次枚举每一只牛u来修改匹配。当找到一个可以匹配的空牛棚时，我们就直接将该空牛棚的Match值置为该牛u。若该牛棚已经被匹配，那么我们向下dfs该牛棚之前对应的那只牛v，看看能否让其更改匹配，对于牛v的操作与牛u类似，但要注意不要dfs重复的牛。重复上述过程直到为牛u腾出位置，则把该牛棚的Match置为牛u，或不存在解则返回0。


通俗点来说，这个算法就是看前面的牛能否通过调整匹配的牛棚来“**让**”出现在需要空出去的牛棚使得新的牛可以匹配。（有点绕口，多读几遍尽量理解，这是这个算法的精髓所在）

更多细节请参看代码。（注释很详细的啦）

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=300;
const int inf=2147483647;

int n,m;
vector<int> E[maxN];//存边
bool vis[maxN];//牛棚是否已经访问过，避免重复
int Match[maxN];//存下牛棚匹配的牛的编号，-1表示还未匹配

bool dfs(int u);

int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    {
        int S;
        cin>>S;
        for (int j=1;j<=S;j++)
        {
            int x;
            cin>>x;
            E[i].push_back(x);//连边
        }
    }

    memset(Match,-1,sizeof(Match));
    int cnt=0;
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));//每一次进行匹配之前都要清空
        if (dfs(i))//若成功匹配，则最大匹配数+1，因为多有一个点能够匹配
            cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}

bool dfs(int u)//1表示匹配成功，0表示不成功
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1) || dfs(Match[v]))//若当前牛棚可以匹配，或是dfs返回1（说明在dfs中成功匹配了），则此时要将新的值更新进去，同时向上一级dfs传值1
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
```
更多内容可以参考我的博客：http://blog.csdn.net/songyuchen0001/article/details/74339575


---

