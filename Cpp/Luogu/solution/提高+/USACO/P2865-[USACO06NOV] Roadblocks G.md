# [USACO06NOV] Roadblocks G

## 题目描述

Bessie 搬到了一个小农场，有时喜欢回去拜访她的一个好朋友。她不想太快到达她的旧家，因为她喜欢沿途的风景。她决定选择第二短的路径而不是最短的路径。她知道一定存在某条第二短路径。

乡村由 $R(1\le R\le100,000)$ 条双向道路组成，每条道路连接 $N(1\le N\le5000)$ 个交叉路口中的两个，这些交叉路口被方便地编号为 $1$ 到 $N$。Bessie 从交叉路口 $1$ 出发，她的朋友（目的地）在交叉路口 $N$。

第二短路径可以与任何最短路径共享道路，并且可以回溯，即多次使用相同的道路或交叉路口。第二短路径是长度比最短路径长的最短路径（即，如果存在两条或多条最短路径，第二短路径是长度比这些路径长但不比任何其他路径长的路径）。

## 说明/提示

两条路径：$1\to2\to4$（长度 $100+200=300$）和 $1\to2\to3\to4$（长度 $100+250+100=450$）。

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 4
1 2 100
2 4 200
2 3 250
3 4 100```

### 输出

```
450```

# 题解

## 作者：Manjusaka丶梦寒 (赞：123)

看到题解好多dijkstra，作为一名钟爱于spfa的蒟蒻看不下去了。

有些spfa要跑两边，代码量要曾长好多(虽然复制)，而且还慢。

下面开始我的表演：

首先看清楚题意：题目说的是从n点往回走(因为双向边，所以好多人注意到也过了)

接着明确一个数组：
	
    d[i][0]表示到i点的最短路
    
    d[i][1]表示到i点的次短路
    
初始化数组，d[n][0]=0,d[n][1]=INF,其他的也都是INF；

然后将点进入队列开始，进行对其他点的更改。

记当前节点编号为u，目前所连边的编号为v。

我们将判断分为两块

(1)d[u][0]对于v点的影响。

(2)d[u][1]对于v点的影响。

####	(1)

如果$$d[u][0]+dis[u,v]<d[v][0]$$,也就是说足影响v点，那么此时的次短路变成了更新前的最短路，最短路更新。


如果
$$d[v][0]<=d[u][0]+dis[u,v]$$

$$d[v][0]>=d[u][0]+dis[u,v]$$

就是说不足以影响最短路，却可以影响次短路，能更新自然更新。

####	(2)

再开始判断d[u][1]对v点的影响

前边(1)部分先更新的最短路。

如果足矣更新最短路：那么到u点的最短路一定小于到u点的次短路，所以用d[u][0]一定更优。

如果没有更新：那么既然最短路都不能更新了，次短路还有啥用。

总的来说对v点最短路这一块理解就好，木有代码。

对于次短路我们要判断一下是否更新。

注意注意：以上判断都需要注意次短路严格小于最短路。

所以：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue> 
using namespace std;
struct ahah{
	int nxt,to,dis;
}edge[200010];
int n,m;
int head[5010],tot;
void add(int x,int y,int z)
{
	edge[++tot].nxt=head[x],edge[tot].to=y,edge[tot].dis=z,head[x]=tot;
}
int d[5010][2];
bool vis[5010];
queue <int> que;
int read()
{
	int sum=0,fg=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')fg=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return sum*fg;
}
void spfa(int s)
{
	memset(d,0x7f,sizeof(d));
	que.push(s);vis[s]=1;
	d[s][0]=0;
	while(!que.empty())
	{
		int u=que.front();
		vis[u]=0;que.pop() ;
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(d[v][0]>d[u][0]+edge[i].dis)
			{
				d[v][1]=d[v][0];
				d[v][0]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][0]+edge[i].dis&&d[u][0]+edge[i].dis>d[v][0])
			{
				d[v][1]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][1]+edge[i].dis)
			{
				d[v][1]=d[u][1]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
		}
	} 
}
int main()
{
	int x,y,z;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	spfa(n);
	printf("%d",d[1][1]);
}
```

喜欢您就点个赞，谢谢。

顺便打一波广告，([逃](https://www.cnblogs.com/rmy020718/p/9492307.html)。

---

## 作者：汪从文 (赞：35)

直接跑两次spfa，一个从起点跑，一个从终点跑，然后找次短路。先开始自己都从起点跑，然后写了一个判断，结果只有30分，先看看着30分的代码：

```cpp
inline void spfa(int s)
{
    memset(vis,false,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    deque<int>q;
    q.push_back(s);
    dis[s]=0;
    vis[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis[u]=false;
        for(int i=head[u];i;i=a[i].net)
        {
            int v=a[i].to;
            if(dis[v]>dis[u]+a[i].w)
            {
                vis[v]=true;
                dis[v]=dis[u]+a[i].w;
                if(q.empty()||dis[v]>dis[q.front()])
                {
                    q.push_back(v);
                }
                else
                {
                    q.push_front(v);
                }
            }
        }
    }
}
inline void spfa2(int s)
{
    int js=1;
    memset(vis2,false,sizeof(vis2));
    memset(dis2,0x7f,sizeof(dis2));
    deque<int>q;
    q.push_back(s);
    dis2[s]=0;
    vis2[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis2[u]=false;
        for(int i=head2[u];i;i=a2[i].net)
        {
            int v=a2[i].to;
            if(dis2[v]>dis2[u]+a2[i].w&&dis2[u]+a2[i].w>dis[js])//判断在这里
            {            
                js++;
                dis2[v]=dis2[u]+a2[i].w;
                vis2[v]=true;
                if(q.empty()||dis2[v]>dis2[q.front()])
                {
                    q.push_back(v);
                }
                else
                {
                    q.push_front(v);
                }
            }
        }
    }
}
```
然后，意识到这种判断很明显的有问题，然后改了很久，然后直接把跑的路程枚举，比较，因为第二短路的长度必须严格大于最短路的长度，但它的长度必须不大于所有除最短路外的路径的长度。然后又改了一下就A了。
AC代码：



```cpp
#include<bits/stdc++.h>
using namespace std;
const int gg=500010;
struct node{
    int w;
    int to;
    int net;
}a[gg];
struct node2{
    int w;
    int to;
    int net;
}a2[gg];
int head[gg],head2[gg];
int dis[gg],dis2[gg];
bool vis[gg],vis2[gg];
int r,n;
int cnt,cnt2;
int ans=1e9;
inline void add(int i,int j,int w)
{
    a[++cnt].to=j;
    a[cnt].net=head[i];
    a[cnt].w=w;
    head[i]=cnt;
}
inline void add2(int i,int j,int w)
{
    a2[++cnt2].to=j;
    a2[cnt2].net=head2[i];
    a2[cnt2].w=w;
    head2[i]=cnt2;
}
inline void spfa(int s)
{
    memset(vis,false,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    deque<int>q;
    q.push_back(s);
    dis[s]=0;
    vis[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis[u]=false;
        for(int i=head[u];i;i=a[i].net)
        {
            int v=a[i].to;
            if(dis[v]>dis[u]+a[i].w)
            {
                vis[v]=true;
                dis[v]=dis[u]+a[i].w;
                if(q.empty()||dis[v]>dis[q.front()])
                {
                    q.push_back(v);
                }
                else
                {
                    q.push_front(v);
                }
            }
        }
    }
}
inline void spfa2(int s)
{
    memset(vis2,false,sizeof(vis2));
    memset(dis2,0x7f,sizeof(dis2));
    deque<int>q;
    q.push_back(s);
    dis2[s]=0;
    vis2[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis2[u]=false;
        for(int i=head2[u];i;i=a2[i].net)
        {
            int v=a2[i].to;
            if(dis2[v]>dis2[u]+a2[i].w)
            {            
                dis2[v]=dis2[u]+a2[i].w;
                vis2[v]=true;
                if(q.empty()||dis2[v]>dis2[q.front()])
                {
                    q.push_back(v);
                }
                else
                {
                    q.push_front(v);
                }
            }
        }
    }
}
int main()
{
    cin>>n>>r;
    for(register int i=1;i<=r;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
        add(b,a,c);
        add2(a,b,c);
        add2(b,a,c);
    }
    spfa(1);
//    cout<<dis[n]<<endl;
    spfa2(n);
    int minn=dis[n];
    for(register int i=1;i<=n;i++)
    {
        for(register int j=head[i],k=head2[i];j,k;j=a[j].net,k=a2[k].net)
        {
            int v=a[j].to;
            int v2=a2[k].to;
            int w=a[j].w;
            int w2=a2[k].w;
            if(dis[i]+dis2[v2]+w>minn&&dis[i]+dis2[v2]+w<ans)
                ans=dis[i]+dis2[v]+w;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：四糸乃 (赞：23)

updata：被Dalao叉了嘤嘤嘤QAQ......
正如Dalao所说，嘤该在修改最短路的时候把最短路的长度赋值给次短路QAQ
加了一句话QAQ
(Ps:现在看自己码风好怪QAQ凑合着看吧QAQ)
 
次短路应该会和最短路有关系，想到dijkstra，SPFA...(关于SPFA......)对于新加入的一条边，无非几种情况：
  
  (1).更新了最短路
  
  (2).无法更新最短路，有可能更新次短路
  
  (3).无法更新次短路和最短路
  
注意的地方：

更新最短路后要把原最短路赋值给最短路(免得被叉QAQ)

情况2只有满足加入当前边后严格长于最短，才去更新次短路

次短路当然更新不了最短路啦Baka！QAQ

如果求稳还是dij吧QAQ


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define maxn 101000
#include<queue>
using namespace std;
int tot=0,head[4*maxn],dist1[maxn],dist2[maxn];
int m,ed;
struct node
{
    int v,val,next;
}edge[200000];
void add(int x,int y,int val)
{
     tot++;
     edge[tot].v=y;
     edge[tot].val=val;
     edge[tot].next=head[x];
     head[x]=tot;
     tot++;
     edge[tot].v=x;
     edge[tot].val=val;
     edge[tot].next=head[y];
     head[y]=tot;
}
void dijkstra()
{
    //memset(vis,0,sizeof(vis));
    memset(dist1,0x3F,sizeof(dist1));
    memset(dist2,0x3F,sizeof(dist2)); 
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,1));
    dist1[1]=0;
    while(!q.empty())
    {
        int temp=q.top().second,dis=q.top().first;
        q.pop(); 
        if(dis>dist2[temp]) continue;
        for(int i=head[temp];i;i=edge[i].next)
        {
            int cnt=edge[i].v;
             if(dist1[cnt]>dis+edge[i].val)
            {   
			    dist2[cnt]=dist1[cnt];
                dist1[cnt]=dis+edge[i].val;
                q.push(make_pair(dist1[cnt],cnt));
            } 
             if(dist2[cnt]>dis+edge[i].val&&dis+edge[i].val>dist1[cnt])/**/
             {
                dist2[cnt]=dis+edge[i].val; 
                q.push(make_pair(dist2[cnt],cnt));
             }    
        }
    }

}
int main()
{
    cin>>ed>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,val;
        cin>>x>>y>>val;
        add(x,y,val);
    }
    dijkstra();
    cout<<dist2[ed]<<endl;
    return 0;
 } 
```

---

## 作者：javalyc (赞：17)

## [博客传送门](https://www.cnblogs.com/LLTYYC/p/9615256.html)
## 算法
### Dijkstra
要求次短路

那么在不考虑重复走一条边的情况下

肯定是把最短路中的一段改成另一段

 #### _至少_ 要换另一条边到路径里
 
所以可以枚举所有不属于最短路的每条边（a,b）

那么dis（1,a）+（a,b）+ dis(b,n)就是一种可能的答案（记为S）

#### 显然如果另一条不属于S的边更新S后会使S更长，就不可能为次短路了

那么只要对起点1和终点n分别跑Dijkstra就可以求出每个dis(1,a)和dis(b,n)

至于判断一条边是否在最短路上也很容易：

显然，如果dis(1,a)+(a,b)=dis(1,b)，那么边(a,b)就在最短路径上

然后考虑重复走一条边情况（显然也只要考虑重复走**一条边**的情况）

也很简单，用贪心的思想

找到最短路径上最短的边(a,b)，如果重复走一条边的情况为次短路，那么肯定是dis(1,n)+(a,b)*2 （走过去又走回来）
#### 如果（c,d）不是最短的边，那么dis(1,n)+(c,d)*2肯定大于dis(1,n)+(a,b)*2，就不可能是次短路
然后就可以了，实现时要注意一下细节
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
inline int read()
{
    int res=0;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res;
}
struct node//存Dijkstra的优先队列中的数据
{
    int u,v;//v为点的编号，u表示从起点到v的距离
    bool operator < (const node &b) const{
        return u>b.u;
    }
};
priority_queue <node> q;//为Dijkstra开的优先队列
struct edge
{
    int from,to,z;
}e[1000007];
int fir[50007],cnt;//链式前向星存图
inline void add(int a,int b,int c)
{
    e[++cnt].from=fir[a];
    fir[a]=cnt;
    e[cnt].to=b;
    e[cnt].z=c;
}//加边
int n,m,ans=199999999;
int dis[50007][2];
//dis[][0]为起点到各个点的距离，dis[][1]为终点到各个点的距离
inline void dijk(int sta,int k)
//sta为开始点，k为dis的第二维
{
    dis[sta][k]=0;
    node p;
    p.u=0; p.v=sta;
    q.push(p);
    while(q.empty()==0)
    {
        int u=q.top().u,v=q.top().v;
        q.pop();
        if(u!=dis[v][k]) continue; //优化
        for(int i=fir[v];i;i=e[i].from)
        {
            int to=e[i].to;
            if(dis[to][k]>dis[v][k]+e[i].z)
            {
                dis[to][k]=dis[v][k]+e[i].z;
                p.u=dis[to][k]; p.v=to;
                q.push(p);
            }
        }
    }
}//Dijkstra的模板
struct data
{
    int x,y,z;
}d[1000007];//存读入的数据
int main()
{
    memset(dis,0x7f,sizeof(dis));
    int a,b,c,mi=199999999;//mi表示最短路径上最短的边长
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        a=read(); b=read(); c=read();
        d[i].x=a; d[i].y=b; d[i].z=c;
        add(a,b,c); add(b,a,c);
    }//读入
    dijk(1,0); dijk(n,1);//跑最短路
    int mx=dis[n][0];
    for(int i=1;i<=m;i++)
    //考虑不重复走一条边的情况
    {
        int x=d[i].x,y=d[i].y;
        if(dis[x][0]+dis[y][1]>dis[y][0]+dis[x][1]) swap(x,y);
        //重要的细节,1到x的路径不能和y到n的路径重复
        int s=dis[x][0]+dis[y][1];
        if(s+d[i].z==mx) continue;//判断边(x,y)是否在最短路径上,如果在就不能选
        ans=min(ans,s+d[i].z);//否则就尝试更新答案
    }
    for(int i=1;i<=m;i++)
    //考虑重复走一条边的情况，显然只要考虑在最短路径上的边
    {
        int x=d[i].x,y=d[i].y;
        if(dis[x][0]+dis[y][1]>dis[y][0]+dis[x][1]) swap(x,y);
        //同样，1到x的路径不能和y到n的路径重复
        if(dis[x][0]+dis[y][1]+d[i].z!=mx) continue;//如果边(x,y)不在最短路径上就不能考虑
        mi=min(mi,d[i].z);//尝试更新mi
    }
    ans=min(ans,mx+mi*2);//答案取较小值
    cout<<ans;
    return 0;
}
```


---

## 作者：清远学会 (赞：9)

# 一句话 深搜（DFS）
##### ~~由于数据水才容本蒟蒻说此话~~
### 既然是求次短路，那么先捣鼓出最短路做标准，再深搜求解；
#### 设最短路长为s1,与结点n相连的最短边的长度为c，设s2=s1+2*c,则s2就是次短路长度的上界。接下来我们只要进行DFS深搜即可，在搜索过程中利用上界s2进行剪枝，并不断更新s2，就可以在题目规定的时间内得到结果。
话不多说，上代码；

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

int n,m;
int x,y,z,T;
int ans[1000000];
int head[200500],cnt;
int dis[200500];
bool done[200500];
struct node {
    int nxt,to,dis;
}e[200500];

inline void cdp(int from,int to,int dis) {
    cnt ++;
    e[cnt].to = to;
    e[cnt].dis = dis;
    e[cnt].nxt = head[from];
    head[from] = cnt;
}

int numm;
void dfs(int x,int nt) {
    if(x == n) {
        if(nt != dis[n]) T = min(T,nt);
        return ;
    }
    if(nt > T) return ;
    
    for(int i = head[x]; i ;i = e[i].nxt) {
        if(done[e[i].to]) continue ;
        else {
            done[e[i].to] = true;
            dfs(e[i].to,nt + e[i].dis);
            done[e[i].to] = false;
        }
    }
}

queue< int > q;
inline void spfa() {
    for(int i = 1;i <= n;i ++) dis[i] = 999999999,done[i] = 0;
    dis[1] = 0;
    done[1] = 1;
    q.push(1); 
    while(!q.empty()) {
        int u = q.front();q.pop();
        done[u] = 0;
        for(int i = head[u]; i ;i = e[i].nxt) {
            if(dis[e[i].to] > dis[u] + e[i].dis) {
                dis[e[i].to] = dis[u] + e[i].dis;
                if(!done[e[i].to]) {
                    q.push(e[i].to);
                    done[e[i].to] = 1; 
                }
            }
        }
    }
}

int main() {
    // freopen("maze.in","r",stdin);
    //freopen("maze.out","w",stdout);
    
    int maxx = 999999999;
    
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i ++) {
        scanf("%d%d%d",&x,&y,&z);
        cdp(x,y,z);cdp(y,x,z);
        if(x == n || y == n) {
            maxx = min(z,maxx);
        }
    }
    
    spfa();
    T = dis[n] + 2 * maxx;
    
    dfs(1,0);
    printf("%d",T);
    
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
/*
4 4
1 2 2
2 4 4
2 3 3
3 4 4
*/

---

## 作者：钱逸凡 (赞：9)

看到题解里好多dijkstra的，我就来一篇spfa的吧

好像有很多题解说spfa要跑两遍？

但是我只用了一遍就A了啊

## 思路：

dist数组开二维，分别装最小距离和次小距离。

先像往常一样打一个spfa，然后往里面塞一些if就好了。

更新最小距离的条件不用说了，

### 更新次小距离的条件有三种：

1.更新了最小距离，要把上次的最小距离先拿给次小距离（刚开始没想到这个条件，调了好久），因为上次的最小距离就是比当前距离大且最小的距离（即为次短距离）。

2.虽然可能当前路径无法更新最小距离，但可能更新次小距离，要加判断

3.从上一个点的次短距离更新这一个点的次短距离

### 注意：

想转移次短距离，必须保证该距离小于最短距离。

### 完整代码：

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
inline int Read(){
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
int n,m;
int dist[10101][2];//dist[i][0]装最短路,dist[i][1]次短路
struct Node{
	int v;
	int next;
	int val;
}node[202020];
int head[5050],top;
inline void addedge(int u,int v,int val){
	node[++top].v=v;
	node[top].val=val;
	node[top].next=head[u];
	head[u]=top;
}
inline void add(int u,int v,int val){
	addedge(u,v,val);
	addedge(v,u,val);
}
int inque[5050];
void spfa(){
	int s=1;
	memset(dist,0x3f,sizeof(dist));
	queue<int>q;
	q.push(s);
	dist[s][0]=0;
	dist[s][1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inque[u]=0;
		for(int i=head[u];i;i=node[i].next){
			int d=node[i].v;
			if(dist[d][0]>dist[u][0]+node[i].val){
				dist[d][1]=dist[d][0];//条件1 
				dist[d][0]=dist[u][0]+node[i].val;
				if(inque[d]==0){
					q.push(d);
					inque[d]=1;
				}
			}
			if(
			(dist[d][1]>dist[u][0]+node[i].val&&dist[u][0]+node[i].val>dist[d][0])
			||(dist[d][1]==dist[d][0])){//从最短路转移（条件2） 
				dist[d][1]=dist[u][0]+node[i].val;
				if(inque[d]==0){
					q.push(d);
					inque[d]=1;
				}
			}
			if(dist[d][1]>dist[u][1]+node[i].val&&dist[u][1]+node[i].val>dist[d][0]){//从次短路转移（条件3） 
				dist[d][1]=dist[u][1]+node[i].val;
				if(inque[d]==0){
					q.push(d);
					inque[d]=1;
				}
			}
		}
	}
}
int main(){
	register int i;
	int u,v,val;
	n=Read(),m=Read();
	for(i=1;i<=m;i++){
	u=Read(),v=Read(),val=Read();
	add(u,v,val);
	}
	spfa();
	printf("%d",dist[n][1]);
	return 0;
}
```

---

## 作者：mxr已死 (赞：8)

  在做本题前，一定理解最短路算法的核心思想。
当然，并不需要对所有的最短路算法有深刻了解。
所以今天我就给大家带来优先队列优化的dijsktra。~~（SPFA我不会）~~
  
   那么问题来了，经典的dijkstra只能维护最短路，怎么去维护次短路呢？其实很简单，只要同时维护两个数组就行了。
   
   那怎么更新呢？我们设dis1数组存最短路，dis2数组存最长路，当找到一条路，比dis1和dis2都短时，就先把目前次短路赋为目前最短路，也就是让dis2=dis1，再把目前最短路赋为找到的更短路。剩下的就是dijkstra的板子了。
   
   当我们存边时，还是推荐大家用邻接表存边，只用写一个函数，跑的好像还比vector快，下面就为大家带来一个不怎么好看的dijkstra板：
   ```c
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<stack>
#include<vector>
#include<cstdio>
#define ll long long
#define inf 1e9+10
using namespace std;
const int maxn=1e5+10;
struct mxr
{
    int to,next,val;
}e[2*maxn];
int n,cnt,m,vis[maxn],head[maxn],s;
int dis[maxn];
priority_queue<pair<ll,int> >q;
inline int read()
{
	int s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();
    if(ch=='-')f=-1;}
	while(ch>='0'&&ch<='9')
    s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*f;
}
inline void add(int u,int v,int w)
{
    e[cnt].to=v;
    e[cnt].val=w;
    e[cnt].next=head[u];
    head[u]=cnt++;
    return ;
}
inline void dij()
{
	q.push(make_pair(0,s));
    dis[s]=0;
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(int i=head[now];i!=-1;i=e[i].next)
        {
            int v=e[i].to;
            if(dis[v]>dis[now]+e[i].val)
            {
                dis[v]=dis[now]+e[i].val;
                q.push(make_pair(-dis[v],v));
            }
        }
    }
    return ;
}
int main()
{
    memset(head,-1,sizeof(head));
    cnt=0;
    n=read(),m=read(),s=read();
    for(int i=1;i<=n;i++) dis[i]=inf;
    for(int i=1;i<=m;i++)
    {
        int a,b,w;
        a=read(),b=read(),w=read();
        add(a,b,w);
    }
    dij();
    for(int i=1;i<=n;i++) printf("%d ",dis[i]);
    return 0;
}

```
下面是本题代码：
```c
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<stack>
#include<vector>
#include<cstdio>
#define ll long long
#define inf 1e9+10
using namespace std;
const int maxn=1e5+10;
struct mxr
{
    int to,next,val;
}e[2*maxn];
int n,cnt,m,head[maxn];
int dis1[maxn],dis2[maxn];
priority_queue<pair<ll,int> >q;
inline char nc()//fread，跑的快 
{
	static char buf[100000],*L=buf,*R=buf;
	return L==R&&(R=(L=buf)+fread(buf,1,100000,stdin),L==R)?EOF:*L++;
}
inline int read()
{
	int ret=0,f=1;char ch=nc();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=nc();}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=nc();
	return ret*f;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return ;
}
inline void add(int u,int v,int w)//邻接表存边，貌似比vector快 
{
    e[cnt].to=v;
    e[cnt].val=w;
    e[cnt].next=head[u];
    head[u]=cnt++;
    return ;
}
inline void dij()//优先队列优化dijkstra 
{
	for(register int i=1;i<=n;++i) dis1[i]=inf,dis2[i]=inf;
	dis1[1]=0;
	q.push(make_pair(0,1));
    while(!q.empty())
    {
        int now=q.top().second,dis=-q.top().first;
        q.pop();
        for(register int i=head[now];i!=-1;i=e[i].next)
        {
            int v=e[i].to;
            if(dis1[v]>dis+e[i].val)
                dis2[v]=dis1[v],dis1[v]=dis+e[i].val,q.push(make_pair(-dis1[v],v));//找到更优，更新dis1与dis2 
            if(dis2[v]>dis+e[i].val&&dis1[v]<dis+e[i].val)
            	dis2[v]=dis+e[i].val,q.push(make_pair(-dis2[v],v));//找到比dis2优，比dis1劣，更新dis2 
        }
    }
    return ;
}
int main()
{
    memset(head,-1,sizeof(head));
    cnt=0;
    n=read(),m=read();
    for(register int i=1;i<=m;++i)
    {
        int a,b,w;
        a=read(),b=read(),w=read();
        add(a,b,w),add(b,a,w);
    }
    dij();
    write(dis2[n]),puts(" ");
    return 0;
}

```
本蒟蒻第一篇luogu博客，望大家喜欢！

---

## 作者：dreamtouch (赞：7)

发现我的方法和大部分人不太一样额……

看了下大部分维护了两个值，即次短路和最短路，但是作为蒟蒻的我很容易就被绕晕了（~~其实是没有仔细看~~）。我来讲讲我自己yy的方法吧：

## 不需要什么理解能力的方法：

1. 首先从n出发跑一次最短路求出n至所有能去的节点的最短路，随便什么方法都行，不会的请前往[单源最短路径（标准版）](https://www.luogu.org/problem/P4779)

2. 选取和1节点相邻的最短边$W$，将1至n的最短路长度加上$2W$，作为次短路的初始值。

3. 然后从1节点出发，跑DFS（是的就是这么暴力）但是如果当前已经走过的距离加上从当前节点去n的最短路（刚刚已经求出了去n的最短路），那么就跳出搜索。如果走到了n节点，查看走过距离是否比当前的次短路短并且比最短路大，如果是则更新。

不知道这叫什么算法呢，如果有知道的可以在评论区告诉笔者。

由于此题数据较水，不吸氧最慢数据点也才222ms，完全可以接受。

代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1000011;
const long long inf=100000000000;
long long dis[maxn];
int vis[maxn];
int head[maxn];
int cnt=0,n,m;
struct edge{
	int to,next,val;
}star[maxn];
long long cd;
void add(int from,int to,int val){
	star[++cnt].to=to;
	star[cnt].val=val;
	star[cnt].next=head[from];
	head[from]=cnt;
}
struct node{
	long long d,dis;
	bool operator < (const node &x)const{
		return dis>x.dis;
	}
};
void dij(){
	priority_queue <node> q1;
	q1.push((node){n,0});
	for(int i=1;i<=n;i++){
		dis[i] = 1100000000;
	}
	dis[n]=0;
	while(!q1.empty()){
		node tmp = q1.top();
		q1.pop();
		int u = tmp.d,d=tmp.dis;
		if(vis[u])continue;
		vis[u]=1;
		dis[u]=d;
		for(int i = head[u];i>0;i=star[i].next){
			if(dis[u]+star[i].val < dis[star[i].to]){
				dis[star[i].to]=dis[u] + star[i].val;
			}
			q1.push((node){star[i].to , star[i].val + d});
		}
	}
}
void dfs(int now,long long len){//直接暴力深搜
	if(len+dis[now]>cd)return;//但是如果此节点去n点的距离加上已经走过的距离大于次短路就退出
	if(now==n){
		if(len>dis[1]&&len<cd)cd=len;
		return;
	}
	for(int i=head[now];i;i=star[i].next){
		int v=star[i].to;
		dfs(v,len+star[i].val);
	}
}
void read(int &a){
	a=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){
		a=(a<<3)+(a<<1)+(c^48);
		c=getchar();
	}
}
int a,b,c;
int main(){
	//freopen("block.in","r",stdin);
	//freopen("block.out","w",stdout);
	read(n);read(m);
	int mink=999999999;
	for(int i=1;i<=m;i++){
		read(a);read(b);read(c);
		add(a,b,c);add(b,a,c);
		if(a==1||b==1)mink=min(mink,c);
	}
	dij();
	cd=dis[1]+2*mink;//可能是次短路
	dfs(1,0);
	printf("%lld\n",cd);
}
```


---

## 作者：奔波儿霸 (赞：6)

#### 解题思路
次短路满足一个很显然的条件，那就是比最短路径要长，比出最短路径外的其他路径要短。那么就可以枚举每一条边，新生成的路径就是这条边的长度加上从$1$到这个点的$u$的最短距离和从$n$到$v$的最短距离，如果这条路径比最短路径要长，那就更新答案，记录一个最小值。

至于从$1$到各个点和从$n$到各个点的距离，用两遍$SPFA$预处理一下就OK了

#### 附上代码
临走前放上我弱弱的代码
```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
const int maxnode = 5e3+3, maxedge = 2e5+3;
const int INF = 2147483647;
int n, m, u[maxedge], v[maxedge], w[maxedge], cnt, Ans = INF;
int fir[maxnode], nxt[maxedge], dis1[maxnode], dis2[maxnode];
bool vis[maxnode];
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while (c <= '9' && c >= '0') {x = x*10+c-'0'; c = getchar();}
	return x * f;
}
inline void addedge(int x, int y, int z) {
	nxt[++cnt] = fir[x];
	fir[x] = cnt;
	u[cnt] = x, v[cnt] = y, w[cnt] = z;
}
inline void SPFA(int s, int *dist) {
	std::queue<int> Q;
	std::memset(vis, 0, sizeof(vis));
	std::fill(dist+1, dist+1+n, INF);
	Q.push(s);
	dist[s] = 0, vis[s] = 1;
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		int k = fir[x];
		while (k != -1) {
			if(dist[u[k]] + w[k] < dist[v[k]]) {
				dist[v[k]] = dist[u[k]] + w[k];
				if(!vis[v[k]])
					vis[v[k]] = 1, Q.push(v[k]);
			}
			k = nxt[k];
		}
		vis[x] = 0;
	}
}
int main() {
	n = read(), m = read();
	std::memset(fir, -1, sizeof(fir));
	int x, y, z;
	for(int i=1; i<=m; i++) {
		x = read(), y = read(), z = read();
		addedge(x, y, z);
		addedge(y, x, z);
	}
	SPFA(1, dis1);
	SPFA(n, dis2);
	for(int i=1; i<=cnt; i++) {
		if(dis1[u[i]] + dis2[v[i]] + w[i] > dis1[n])
			Ans = std::min(Ans, dis1[u[i]] + dis2[v[i]] + w[i]);
	}
	printf("%d", Ans);
}
```

---

## 作者：EternalAlexander (赞：5)

A*

 从终点跑一遍最短路算法，预处理出dis[i]，即i号点距离终点的最短路距离。  
然后从起点开始跑A*，用dis作为估价函数，直到搜到大于最短路的路径为止。

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define maxn 5005
#define maxm 100005

struct edge {
    int v, w, next;
}edges[maxm<<1];
int tail=0, head[maxn]={0}, dis[maxn], vis[maxn]={0}, n, m;
struct node {
    int u, w;
};
bool operator < (node a, node b) {
    return dis[a.u]+a.w>dis[b.u]+b.w;
}

std::priority_queue <node> heap;
inline void add_edge(int u, int v, int w) {
    edges[++tail].v=v;
    edges[tail].w=w;
    edges[tail].next=head[u];
    head[u]=tail;
}
node newnode(int u, int w) {
    node v; v.u=u; v.w=w;
    return v;
}

void Astar() {
    heap.push(newnode(1, 0));
    while (true) {
        node v=heap.top(); heap.pop();
    //	printf("%d %d %d\n", v.u, v.w, dis[v.u]);char a=getchar();
        if (v.u==n&&v.w>dis[1]) {
            printf("%d", v.w);
            return ;
        }
        for (int i=head[v.u];i;i=edges[i].next) {
            heap.push(newnode(edges[i].v, v.w+edges[i].w));
        }
    }
}
        

inline void spfa() {
    std::queue <int> q;
    std::memset(dis, 127, sizeof(dis));
    q.push(n); dis[n]=0; vis[n]=1;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=head[u];i;i=edges[i].next) {
            if (dis[u]+edges[i].w<dis[edges[i].v]) {
                dis[edges[i].v]=dis[u]+edges[i].w;
                if (!vis[edges[i].v]) {
                    vis[edges[i].v]=1;
                    q.push(edges[i].v);
                }
            }
        }vis[u]=0;
    }
}

int main() {
//	freopen("maze.in", "r", stdin);
//	freopen("maze.out", "w", stdout);
    int u, v, w;
    scanf("%d %d", &n, &m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w); add_edge(v, u, w);
    }spfa();
    //printf("%d", dis[1]);
    Astar();
    return 0;
}


```

---

## 作者：Fheiwn (赞：5)

一道果的次短路问题；

我是用的dijkstra;


最短路的思想都会。


次短路 dis2<s,t> 有两种情况


  (1) : 从s->u的最短路+dis<u,t>;

  (2) : 从s->u的次短路+dis<u,t>;

所以 只要在跑最短路时 记录次短路(dis2) 并更新。







```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<bitset>
#include<sstream>
#include<cstdlib>
#define QAQ int
#define TAT long long
#define ORZ double
#define OwO bool
#define SHO short
#define F(i,j,n) for(QAQ i=j;i<=n;++i)
#define E(i,j,n) for(QAQ i=j;i>=n;--i)
#define MES(i,j) memset(i,j,sizeof(i))
#define MEC(i,j) memcpy(i,j,sizeof(j))
using namespace std;
const QAQ N=5005,M=200005;
typedef pair<QAQ,QAQ> PA;
QAQ n,m;
struct data{
    QAQ to,last,val;
}a[M];
QAQ head[N],js;
QAQ dis1[N],dis2[N];
priority_queue<PA,vector<PA>,greater<PA> > q;
void dijkstra(QAQ s){
    MES(dis1,100);MES(dis2,100);
    dis1[s]=0;
    q.push(make_pair(dis1[s],s));
    while(q.size()){
        PA p=q.top();q.pop();
        QAQ x=p.second,dis=p.first;
        if(dis>dis2[x]) continue;
        for(QAQ i=head[x];i;i=a[i].last){
            QAQ d2=dis+a[i].val;
            if(dis1[a[i].to]>d2){
                swap(dis1[a[i].to],d2);
                q.push(make_pair(dis1[a[i].to],a[i].to));
            }
            if(dis2[a[i].to]>d2&&dis1[a[i].to]<d2){
                dis2[a[i].to]=d2;
                q.push(make_pair(dis2[a[i].to],a[i].to));
            }
        }
    }
}
void add(QAQ x,QAQ y,QAQ z){
    a[++js].to=y;a[js].val=z;
    a[js].last=head[x];head[x]=js;
}
QAQ main(){
    scanf("%d%d",&n,&m);
    F(i,1,m) {
        QAQ u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dijkstra(1);
    printf("%d\n",dis2[n]);
    return 0;
}

```

---

## 作者：Glacier_elk (赞：3)

因为不久前刚刚看过了[最短路计数](https://www.luogu.org/problem/P1144)这道题目，所以就想在求最短路的时候，用dis数组记录最短路和次短路，然后就愉快的打完了代码，过了样例，但是只有50分。
然后，我重新想了想我在求最短路的时候的判断，发现50这个样子写，最小值可能会覆盖次小值，因为我只判断了一遍的范围，没有限制次小值严格小于最小值。而且题目要求**一条路可以重复走多次**，所以我增加了每个点可以经过的次数。
判断部分就改成了下面这样

```cpp
for (int i = head[id]; i; i = e[i].nxt)
{
	if (dis[e[i].v][0] > di + e[i].w)
	{
		dis[e[i].v][1] = dis[e[i].v][0], dis[e[i].v][0] = di + e[i].w;
		if (dis[e[i].v][1] > dis[id][1] + e[i].w && dis[e[i].v][0] < dis[id][1] + e[i].w)
		dis[e[i].v][1] = dis[id][1] + e[i].w;
		if (vis[e[i].v] < 2) q.push(make_pair(dis[e[i].v][0], e[i].v));
	}
	else
		if (dis[e[i].v][1] > di + e[i].w && dis[e[i].v][0] < di + e[i].w)
		{
			dis[e[i].v][1] = di + e[i].w;
			q.push(make_pair(dis[e[i].v][0], e[i].v));
		}
	else
		if (dis[e[i].v][1] > dis[id][1] + e[i].w && dis[e[i].v][0] < dis[id][1] + e[i].w)
			dis[e[i].v][1] = dis[id][1] + e[i].w;
}
```


这样就过了90分！
然后下载了错误数据，发现还是错在了一条边可以走多次的问题上。因为走多次的话，第一个点的次短路就不一定是0了，所以我把初始化只改成了初始化1号点的最短路。这样就过了这个题。
下面是AC代码
```cpp
#include <bits/stdc++.h>
#define id tmp.second
#define di tmp.first
using namespace std;
typedef pair<int, int> PI;
const int M = 300500;
int n, r, head[M], tot, dis[M][2], vis[M];
struct EDGE{
	int v, w, nxt;
}e[M];
priority_queue<PI, vector<PI>, greater<PI> > q;
PI tmp;

void add(int x, int y, int z)
{
	e[++tot].v = y, e[tot].nxt = head[x], e[tot].w = z, head[x] = tot;
}

void Dijkstra()
{
	memset(dis, 0x4f, sizeof(dis));
	dis[1][0] = 0;
	q.push(make_pair(0, 1));
	while (!q.empty())
	{
		tmp = q.top(), q.pop();
		if (vis[id] == 2) continue;
		++vis[id];
		for (int i = head[id]; i; i = e[i].nxt)
		{
			if (dis[e[i].v][0] > di + e[i].w)
			{
				dis[e[i].v][1] = dis[e[i].v][0], dis[e[i].v][0] = di + e[i].w;
				if (dis[e[i].v][1] > dis[id][1] + e[i].w && dis[e[i].v][0] < dis[id][1] + e[i].w)
					dis[e[i].v][1] = dis[id][1] + e[i].w;
				if (vis[e[i].v] < 2) q.push(make_pair(dis[e[i].v][0], e[i].v));
			}
			else
				if (dis[e[i].v][1] > di + e[i].w && dis[e[i].v][0] < di + e[i].w)
				{
					dis[e[i].v][1] = di + e[i].w;
					if (vis[e[i].v] < 2) q.push(make_pair(dis[e[i].v][0], e[i].v));
				}
			else
				if (dis[e[i].v][1] > dis[id][1] + e[i].w && dis[e[i].v][0] < dis[id][1] + e[i].w)
					dis[e[i].v][1] = dis[id][1] + e[i].w;
		}
	}
}

int main()
{
	int x, y, z;
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> r;
	for (int i = 1; i <= r; ++i) cin >> x >> y >> z, add(x, y, z), add(y, x, z);
	Dijkstra();
	printf("%d", dis[n][1]);
	return 0;
}
```


---

## 作者：小手冰凉 (赞：3)

大暴力做法


算两边SPFA（从1~n和从n~1各走一遍），然后计算次短路是枚举每条边，算出每条边1->该边的出发点+该边长度+该边结束点->n的值


（由于数组开小，贡献了N发WA）


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int M=400005;
int head[M],nxt[M],from[M],tail[M],e[M];
queue<int>q;
int dis[M],inq[M],dis2[M];
int t,n,m,ans,anst;
void addto(int x,int y,int z)
{
    nxt[++t]=head[x];
    from[t]=x;
    head[x]=t;
    tail[t]=y;
    e[t]=z;
}
void spfa(int s,int t,int *dis)
{
    memset(inq,0,sizeof(inq));
    q.push(s);
    dis[s]=0;
    inq[s]=1;
    while(!q.empty()){
        int k=q.front();
        q.pop();
        inq[k]=0;
        for(int i=head[k];i;i=nxt[i]){
            int x=tail[i];
            if(dis[x]>dis[k]+e[i]){
                dis[x]=dis[k]+e[i];
                if(!inq[x]){
                    q.push(x);
                    inq[x]=1;
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        addto(x,y,z);
        addto(y,x,z);
    }
    memset(dis,127/3,sizeof(dis));
    spfa(1,n,dis);
    anst=dis[n];
    ans=1e9;
    memset(dis2,127/3,sizeof(dis));
    spfa(n,1,dis2);
    for(int i=1;i<=t;i++)
        if(dis[from[i]]+dis2[tail[i]]+e[i]>anst)
            ans=min(dis[from[i]]+dis2[tail[i]]+e[i],ans);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：lajioj (赞：2)

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
#define E 0x3f3f3f3f
#define MAXN 5010  
#define MAXM 100100 
using namespace std;
int n,m;

struct node{
	int u,v,next,w;
}e[MAXM*2];
int head[MAXN];
int cnt;
bool r[MAXN];
int dis[MAXN];
int dis2[MAXN];
void add(int u,int v,int w){
	cnt++;
	e[cnt].u = u;
	e[cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}

void SPFA(int orz,int d[]){//裸的SPFA 
	memset(r,0,sizeof r);
	queue<int>q;
	d[orz] = 0;
	q.push(orz);
	r[orz] = true;
	while(!q.empty()){
		int h=q.front();
		q.pop();
		r[h] = 0;
		for(int i=head[h];i!=0;i=e[i].next){
			if(e[i].w+d[e[i].u]<d[e[i].v]){
				d[e[i].v]=e[i].w+d[e[i].u];
				if(r[e[i].v]==0){
					q.push(e[i].v);
					r[e[i].v]=1;
				}
			}
		}
	}
}

int main(){
	while(~(scanf("%d%d",&n,&m))){
	cnt = 0;
	memset(dis,E,sizeof dis);
	memset(dis2,E,sizeof dis2);
	memset(head,0,sizeof head);
		for(int i=1;i<=m;++i){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			add(a,b,c);
			add(b,a,c);
		}
		SPFA(1,dis);//求出1到所有点的最短距离
		SPFA(n,dis2);//求出n到所有点的最短距离 
		int minn = dis[n];//次短路当然大于最短路啦
		int ans = E;//先把答案置为最大值，以便于更新
		for(int i=1;i<=n;++i){//枚举每一个点 
			for(int j=head[i];j;j=e[j].next){//每个点的连点
				int v=e[j].v;//终点 
				int w=e[j].w;//权值 
				if(dis[i] + dis2[v] + w >minn && dis[i] + dis2[v] + w < ans){
					ans = dis[i]+dis2[v]+w;
				}/*如果说1到i这个点的距离加上其的终边到n的距离并加上其终边的权值大于了最短路，并且他小于当前的次短路，那么更新答案*/ 
			}
		}//其实就是一个暴力更新 
		printf("%d\n",ans);//输出走人
	}
	return 0;
}
```

---

