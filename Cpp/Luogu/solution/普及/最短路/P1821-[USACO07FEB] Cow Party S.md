# [USACO07FEB] Cow Party S

## 题目描述

寒假到了，$n$ 头牛都要去参加一场在编号为 $x$ 的牛的农场举行的派对，农场之间有 $m$ 条有向路，每条路都有一定的长度。

每头牛参加完派对后都必须回家，无论是去参加派对还是回家，每头牛都会选择最短路径，求这 $n$ 头牛的最短路径（一个来回）中最长的一条路径长度。


## 说明/提示

### 样例 1 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/rl3com2y.png)

### 数据规模与约定

对于全部的测试点，保证 $1 \leq x \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1 \leq u,v \leq n$，$1 \leq w \leq 10^2$，保证从任何一个结点出发都能到达 $x$ 号结点，且从 $x$ 出发可以到达其他所有节点。

## 样例 #1

### 输入

```
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
```

### 输出

```
10```

# 题解

## 作者：My_666 (赞：54)

# 一个巧妙的最短路：


------------

### 题目概括：
求 一个单源最短路 + 一个单终点最短路 的最大值。
### 思路：
- 我们首先想到的是从每个点都求一遍到终点的最短路，这样会加大时间复杂度。
- 所以，我们可以反向建图，直接把单终点最短路转为单源最短路，只需要跑两次最短路算法，显然是稳过的。（可以自己画画图，感受一下）

PS：这里推荐dijkstra算法，不推荐spfa，显然我们可以轻松卡掉spfa，平时练习要养成好的习惯，避免考试时酿成不必要的惨剧。
### 代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll; // 做题的好习惯 

const int maxn = 1005; //点数 
const int maxm = 100005; //边数 

int n, m, s, ans[maxn], sum;

struct Edge{
	int nxt, to, w;
}e[maxm];

int head[maxn], cnt;

void addEdge(int u, int v, int w) {
	e[++cnt].nxt = head[u];
	e[cnt].w = w;
	e[cnt].to = v;
	head[u] = cnt; 
}

int dis[maxn], vis[maxn];

void dijkstra(int s) {
	for (int i = 1; i <= n; i++) dis[i] = 0x3f3f3f3f;  
	priority_queue< pair<int, int> > q;
	q.push(make_pair(0, s));
	dis[s] = 0;
	while (q.size()) {
		int u = q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main() {
	int u[maxm], v[maxm], w[maxm];
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i]; //先存下数据，便于以后反向建边 
		addEdge(u[i], v[i], w[i]); //正向建边 
	}
	dijkstra(s);
	for (int i = 1; i <= n; i++) ans[i] = dis[i]; //回家的最短路径  
	cnt = 0;
	memset(dis, 0, sizeof(dis));
	memset(head, 0, sizeof(head));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= m; i++) addEdge(v[i], u[i], w[i]); //反向建边
	dijkstra(s);
	for (int i = 1; i <= n; i++) {
		ans[i] += dis[i]; //回家的最短路+去派对的最短路=全程的最短路 
		sum = max(sum, ans[i]); //求最大值 
	}
	cout << sum;//输出 
	return 0;
}
```


------------
# 感谢！

---

## 作者：C_Cong (赞：19)

# 【[USACO07FEB]银牛派对Silver Cow Party】

_Tips:博客内食用效果更佳 [传送门](https://dgsyrc.github.io/2019/08/16/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3%20P1821%20%E3%80%90[USACO07FEB]%E9%93%B6%E7%89%9B%E6%B4%BE%E5%AF%B9Silver%20Cow%20Party%E3%80%91/#more)_ 

### 题意：

有$n$头牛，$m$条路，所有牛要前往$X$牛的家开趴（当然$X$牛不用动），求其他牛去开趴来回的最短距离，输出最长的那条。

### 简化版题意：

有$n$个节点，$m$条边，给出终点$X$，求其他节点到终点的来回最短距离，输出最长的距离。

## 注意：该题所给的边为有向边，别瞎*2输出

### 使用的算法：SPFA

### 思路：

题目要找其他点到终点$X$的最短路径和终点$X$到其他点的最短路径。为便于代码实现，要进行反向建图，用SPFA跑正向的图求终点$X$到其他点的最短路径，再用跑反向图求其他点到终点$X$的最短路径。

反向图即将边的起点和终点反过来，边权不变。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
struct edge
{
	int u,v;	
};

vector<edge> G[3][1001];//动态数组存边

queue<int> Q;//队列（STL大法好）

int n,m,f[3][1001],l,ans;
bool vis[1001];

void spfa(int k)//k=1时正向图，k=2时反向图
{
	memset(vis,0,sizeof(vis));//初始化false
	vis[l]=true;
	f[k][l]=0;
	Q.push(l);
	while(!Q.empty())
	{
		int news=Q.front();
		Q.pop();
		vis[news]=false;
		for(int i=0;i<G[k][news].size();i++)
		{
			int v=G[k][news][i].v,u=G[k][news][i].u;
			if(f[k][v]>f[k][news]+u)
			{
				f[k][v]=f[k][news]+u;
				if(!vis[v])
				{
					vis[v]=true;
					Q.push(v);
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&l);
	memset(f,0x3f3f3f,sizeof(f));
	for(int a=1;a<=m;a++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		edge cmp;
		cmp.v=y;
		cmp.u=z;
		G[1][x].push_back(cmp);//正向建图
		cmp.v=x;
		G[2][y].push_back(cmp);//反向建图
	}
	spfa(1);//跑正向图
	spfa(2);//跑反向图
	for(int a=1;a<=n;a++)
	{
		if(a==l)
		{
			continue;
		}
		ans=max(f[1][a]+f[2][a],ans);//找最长的
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：tjztjz (赞：15)

# 这道题一看就是个最短路嘛~
## 可是是用SPFA呢，还是Dijkstra呢？
### 当然啦，本人喜欢写SPFA，~~因为Dijkstra不会写~~
### 咳咳咳，言归正传，这道题该怎么写呢？
其实嘛，这道题就是让你从$X$点开始正着跑一遍SPFA，倒着再跑一遍。
### 注意啦！这道题是有向图！！！不要瞎乘二！
那么SPFA该怎么写呢？（注：会写SPFA的大佬请省略这一部分，直接跳转到最终代码部分！）

首先，我们要存图！存图有好几种方法，不过本蒟蒻还是比较喜欢用邻接表的。

### 一、邻接表存图：
```
struct Tedge           //先开一个用来存边的结构体
		       //to是这条边的终点,len是这条边的长度
{
	int to, len;
};
vector<Tedge> edge[MAXN];    //用vector动态数组存边，更节省空间
void add_edge(int u, int v, int w)
{
	Tedge temp;
	temp.to = v;
	temp.len = w;
	edge[u].push_back(temp);
}
for (int i = 1, a, b, t; i <= m; ++i)
{
	cin >> a >> b >> t;    //分别代表起点、终点、长度
	add_edge(a, b, t);    //这道题是有向图！！
}
//edge[i][j].to代表了起点为i的第j条边，终点为edge[i][j].to
//edge[i][j].len代表了起点为i的第j条边，长度为edge[i][j].len，即i到edge[i][j].to这条边的长度为edge[i][j].len。
```
好了，存图存完了，那么该怎么求最短路呢？
### 二、SPFA
SPFA的本质其实就是在图中做广搜，废话少说，直接贴代码：
```
//dist数组用来存储从起点到i的最短路，inq数组用来存储第i个点是否走过
void spfa1()
{
	for (int i = 1; i <= n; ++i) dist1[i] = 1e9, inq[i] = false;
	dist1[x] = 0;            //这里假设x点为起点
	inq[x] = true;           //首先，作为起点，x点已经被走过
	q.push(x);
	while (! q.empty())
	{
		int cur = q.front();    //cur是当前搜到的点
		inq[cur] = false;
		for (int i = 0; i < edge1[cur].size(); ++i)  //遍历所有cur可以到达的点
		{
			int to = edge1[cur][i].to;
			if (dist1[cur] + edge1[cur][i].len < dist1[to])  //更新其他点的最短路
			{
				dist1[to] = dist1[cur] + edge1[cur][i].len;
				if (! inq[to])
				{
					inq[to] = true;
					q.push(to);
				}
			}
		}
		q.pop();
	}
}
```
以上就是SPFA模版重要片段！
### 三、最后，有关这道题：
这道题的思路：

首先要从点X出发算出每一个点的最短路，然后再以点X为终点，再跑一遍最短路

因此，为了方便，我们存图时需要存两次（一次正着存，一次倒着存）

存图代码：
```
struct Tedge
{
	int to, len;
};
vector<Tedge> edge1[MAXN], edge2[MAXN];
void add_edge(int u, int v, int w)    //存两次图，分别存在edge1和edge2中
{
	Tedge temp1, temp2;
	temp1.to = v;
	temp1.len = w;
	edge1[u].push_back(temp1);
	temp2.to = u;
	temp2.len = w;
	edge2[v].push_back(temp2);
}
for (int i = 1, a, b, t; i <= m; ++i)
{
	cin >> a >> b >> t;
	add_edge(a, b, t);
}
```
然后呢，由于需要做两次SPFA，因此就要写两个SPFA的函数了，不过没啥区别，只需要改一下数组名就好了

### 四、送上终极AC代码：

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 2020 ;
struct Tedge
{
	int to, len;
};
int n, m, x;
int dist1[MAXN], dist2[MAXN];
bool inq[MAXN];
vector<Tedge> edge1[MAXN], edge2[MAXN];
queue<int> q;
void add_edge(int u, int v, int w)    //存边
{
	Tedge temp1, temp2;
	temp1.to = v;
	temp1.len = w;
	edge1[u].push_back(temp1);
	temp2.to = u;
	temp2.len = w;
	edge2[v].push_back(temp2);
}
void spfa1()                  //正着做SPFA
{
	for (int i = 1; i <= n; ++i) dist1[i] = 1e9, inq[i] = false;
	dist1[x] = 0;
	inq[x] = true;
	q.push(x);
	while (! q.empty())
	{
		int cur = q.front();
		inq[cur] = false;
		for (int i = 0; i < edge1[cur].size(); ++i)
		{
			int to = edge1[cur][i].to;
			if (dist1[cur] + edge1[cur][i].len < dist1[to])
			{
				dist1[to] = dist1[cur] + edge1[cur][i].len;
				if (! inq[to])
				{
					inq[to] = true;
					q.push(to);
				}
			}
		}
		q.pop();
	}
}
void spfa2()                  //倒着做SPFA
{
	for (int i = 1; i <= n; ++i) dist2[i] = 1e9, inq[i] = false;
	dist2[x] = 0;
	inq[x] = true;
	q.push(x);
	while (! q.empty())
	{
		int cur = q.front();
		inq[cur] = false;
		for (int i = 0; i < edge2[cur].size(); ++i)
		{
			int to = edge2[cur][i].to;
			if (dist2[cur] + edge2[cur][i].len < dist2[to])
			{
				dist2[to] = dist2[cur] + edge2[cur][i].len;
				if (! inq[to])
				{
					inq[to] = true;
					q.push(to);
				}
			}
		}
		q.pop();
	}
}
int main()
{
	cin >> n >> m >> x;
	for (int i = 1, a, b, t; i <= m; ++i)
	{
		cin >> a >> b >> t;
		add_edge(a, b, t);
	}
	spfa1(); spfa2();        //求两遍SPFA
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, dist1[i] + dist2[i]);   //求最终结果
	cout << ans << endl;
	return 0;
}
```

呼~好了，终于写完题解了，希望能通过

~~另外，觉得题解好就赞一个呗~~~~~

---

## 作者：zengxr (赞：10)

# 套一套spfa的板子就好了。

# 思路：
从每个点做一次spfa，记录下每个点到x点的距离（即奶牛们去的距离），然后再以x点为起点做一次spfa，在记录从x点到每个点的距离（即奶牛们回来的距离）。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int b,e,p,m,n,t;
int tot,now[100010],son[100010],pre[100010],V[100010];
int dis[100010],ans[100010];
bool flag[100010];
int team[100010];
void read(int &x) {
    char ch; bool ok;
    for(ok=0,ch=getchar(); !isdigit(ch); ch=getchar()) if(ch=='-') ok=1;
    for(x=0; isdigit(ch); x=x*10+ch-'0',ch=getchar()); if(ok) x=-x;
}//快读
void put(int x,int y,int z)
{
    pre[++tot]=now[x];
    now[x]=tot;
    son[tot]=y;
    V[tot]=z;
}//邻接表存储
void spfa(int s,int *d)
{
    
    for(int i=1;i<=n;i++)
        d[i]=9999999;
    int head=0,tail=1;
    memset(flag,false,sizeof(flag));
    flag[s]=true;
    d[s]=0;
    team[1]=s;
    do
    {
        head++;
        int u=team[head];
        flag[u]=false;
        for(int i=now[u];i;i=pre[i])
        {
            int v=son[i];
            if(d[v]>d[u]+V[i])
            {
                d[v]=d[u]+V[i];
                if(!flag[v])
                {
                    tail++;
                    team[tail]=v;
                    flag[v]=true;
                }
            }
        }
    } while (head<=tail);
    
}//spfa的板子
int main()
{
    int x,y,z;
    read(n),read(m),read(t);
    for(int i=1;i<=m;i++)
    {
        read(x),read(y),read(z);
        put(x,y,z);
    }
    for(int i=1;i<=n;i++)
    {
      spfa(i,dis);//每个点做一次spfa
      ans[i]=dis[t];//记录
    }
    spfa(t,dis);//从终点做一次
    int maxx=0;//记录最大值
    for(int i=1;i<=n;i++)
    {
      ans[i]+=dis[i];//加上每头牛回家的距离
      maxx=max(ans[i],maxx);//找最大值
    }
    printf("%d",maxx);//输出答案
}
```



---

## 作者：玫葵之蝶 (赞：8)

**很经典的最短路，虽然数据不坑**

思路：这题是一个单源最短路和单终点最短路，前者大家都会，一遍SPFA或Dijkstra就行了（数据也没卡SPFA）；可是后者单终点最短路怎么办呢？可以把边反过来（具体可以在输入时就建两个图，一正一反），因为单源和单终点只是方向改变，所以很容易发现这么做是对的。

具体做法：很简单呢，两遍SPFA，不过要写两个函数。

注意：好像没什么可以注意的。。。

接下来贴代码：

```cpp
#include<bits/stdc++.h>
#define inf 2000000000
using namespace std;
struct edge{
    int to,next,w;
}e[100001],e2[100001];
int n,m,s;
int head[1001],head2[1001];
int in[1001];
int d1[1001];
int d2[1001];

void spfa(){
    queue<int> q;
    q.push(s);
    in[s]=1;
    d1[s]=0;
    while(!q.empty()){
        int t=q.front();
        q.pop();
        in[t]=0;
        for(int i=head[t];i!=0;i=e[i].next){
            if(d1[t]+e[i].w<d1[e[i].to]){
                d1[e[i].to]=d1[t]+e[i].w;
                if(!in[e[i].to]){
                    in[e[i].to]=1;
                    q.push(e[i].to);
                }
            }
        }
    }
}
void spfa2(){
    queue<int> q;
    q.push(s);
    in[s]=1;
    d2[s]=0;
    while(!q.empty()){
        int t=q.front();
        q.pop();
        in[t]=0;
        for(int i=head2[t];i!=0;i=e2[i].next){
            if(d2[t]+e2[i].w<d2[e2[i].to]){
                d2[e2[i].to]=d2[t]+e2[i].w;
                if(!in[e2[i].to]){
                    in[e2[i].to]=1;
                    q.push(e2[i].to);
                }
            }
        }
    }
}
int main(){
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++){
        d1[i]=inf;
        d2[i]=inf;
    }
    for(int i=1;i<=m;i++){
        int a,b,l;
        scanf("%d %d %d",&a,&b,&l);
        e[i].to=b;
        e[i].next=head[a];
        head[a]=i;
        e[i].w=l;
        e2[i].to=a;
        e2[i].next=head2[b];
        e2[i].w=l;
        head2[b]=i;
    }
    spfa();
    memset(in,0,sizeof(in));
    spfa2();
    int mx=0;
    for(int i=1;i<=n;i++){
        mx=max(mx,d1[i]+d2[i]);
    }
    cout<<mx;
    return 0;
}
```

---

## 作者：King丨帝御威 (赞：5)

看遍了所有题解，大家都没有写结构体版堆优化dijkstra的，而恰恰这个算法跑最短路是最实用的(那些线段树优化dijkstra的dalao先别说话。。。(noip也用不到))。spfa复杂度不稳定，可以被出题人轻松卡掉，所以，我来给各位发一遍堆优化dijkstra的题解，具体实现和思路看代码吧。

如果想练习做堆优化模板题联系一下的话：请  [luogu P4779](https://www.luogu.org/problemnew/show/P4779)

下面献上我~~香喷喷~~的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define ll long long
#define maxn 1000+1
#define maxn1 100000+1
using namespace std;
inline ll qread()             //快读(不会的同学也可以用scanf,不推荐用cin,太慢了。。。)
{
	char c=getchar();ll num=0,f=1;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) num=num*10+c-'0';
	return num*f;
}
ll n,m,dis[maxn],head[maxn],ans,num,zdl[maxn],t,s,maxx=-1;                 //dis表示起点到某个点的最短路，zdl为最后统计的最终每个点的最短路，maxx用来更新最大值。
struct Edge
{
	ll v,w,nxt;
}edge[maxn1];
inline void ct(ll u,ll v,ll w)   //链式前向星存图。
{
	edge[++num].v=v;
	edge[num].w=w;
	edge[num].nxt=head[u];
	head[u]=num;
}
struct node
{
	ll x,y;
	bool operator < (const node &a) const   //把大根堆重载成小根堆。
	{
		return y>a.y;
	}
};
inline void dijkstra()        //从某个点到终点。
{
	memset(dis,0x3f,sizeof(dis));  //初始化最短路数组为极大值。
	dis[s]=0;
	priority_queue<node>q;
	q.push((node){s,0});            //加入起点。
	while(!q.empty())
	{
		ll u=q.top().x,d=q.top().y;
		q.pop();
		if(d!=dis[u]) continue;
		for(ll i=head[u];i;i=edge[i].nxt)
		{
			ll v=edge[i].v;
			if(dis[v]>dis[u]+edge[i].w)  //dijkstra基本操作。
			{
				dis[v]=dis[u]+edge[i].w;
				q.push((node){v,dis[v]});
			}
		}
	}
}
inline void dijkstra2()     //从终点到某个点。
{
	memset(dis,0x3f,sizeof(dis));
	dis[t]=0;                     //加入终点。
	priority_queue<node>q;
	q.push((node){t,0});
	while(!q.empty())
	{
		ll u=q.top().x,d=q.top().y;
		q.pop();
		if(d!=dis[u]) continue;
		for(ll i=head[u];i;i=edge[i].nxt)
		{
			ll v=edge[i].v;
			if(dis[v]>dis[u]+edge[i].w)     //套路同上。
			{
				dis[v]=dis[u]+edge[i].w;
				q.push((node){v,dis[v]});
			}
		}
	}
}
int main()
{
	n=qread(),m=qread(),t=qread();
	for(int i=1,u,v,w;i<=m;++i)
	{
		u=qread(),v=qread(),w=qread();
		ct(u,v,w);           
	}
	for(int i=1;i<=n;++i)
	{
		s=i;
		dijkstra();
		zdl[i]=dis[t];           //更新每个点的当前最短路。
	}
	dijkstra2();
	for(int i=1;i<=n;++i)
	{
		zdl[i]+=dis[i];        //还要从终点跑回家。
		maxx=max(maxx,zdl[i]);  //更新最大值。
	}
	cout<<maxx<<'\n';
	return 0;                 //输出，完美落幕！
}
```

大家有什么不懂的地方可以在我的博客留言或私信问我哦！

---

## 作者：封禁用户 (赞：5)

明明可以写一次SPFA（或dij）为什么要写两次呢？

以下代码主要优越在拆点

###思路

把一个点拆成两个，双数为正向，单数为反向

上代码ε=ε=ε=(~￣▽￣)~

**SPFA版**

```cpp
cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=100100;
const int INF=0x3f3f3f3f;
int x,a,b,c,n,m,d[maxn];
inline int read(){
    int k=0;char f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        k=k*10+c-'0';
        c=getchar();
    }
    return k*f;
}
int idx=0,e[maxn],ne[maxn],cost[maxn],h[maxn];
bool in[maxn];
void add(int a,int b,int c){
    e[idx]=b;ne[idx]=h[a];cost[idx]=c;h[a]=idx++;
}
void SPFA(int s){
    memset(in,false,sizeof(in));
    queue<int>que;
    que.push(s);
    in[s]=true;
    d[s]=0;
    while(!que.empty()){
        int u=que.front();que.pop();
        in[u]=false;
        for(int v=h[u];v!=-1;v=ne[v]){
            if(d[e[v]]>d[u]+cost[v]){
                d[e[v]]=d[u]+cost[v];
                if(!in[e[v]]){
                    in[e[v]]=true;
                    que.push(e[v]);
                }
            }
        }
    }
}
int main(){
    memset(h,-1,sizeof(h));
    memset(d,INF,sizeof(d));
    n=read();m=read();x=read();
    for(register int i=1;i<=m;i++){
        a=read();b=read();c=read();
        add(a<<1,b<<1,c);add(b<<1|1,a<<1|1,c);
    }
    SPFA(x<<1|1);SPFA(x<<1);
    int ans=-1;
    for(register int i=1;i<=n;i++){
        if(i==x)continue;
        ans=max(d[i<<1]+d[i<<1|1],ans);
    }
    printf("%d\n",ans);
    return 0;
}
```
**dij版**

```cpp
cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=100100;
const int INF=0x3f3f3f3f;
int x,a,b,c,n,m,d[maxn];
inline int read(){
    int k=0;
    char f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
    }        
    while(c<='9'&&c>='0'){
        k=k*10+c-'0';
        c=getchar();
    }
    return k*f;
}
int idx=0,e[maxn],ne[maxn],cost[maxn],h[maxn];
void add(int a,int b,int c){
    e[idx]=b;ne[idx]=h[a];cost[idx]=c;h[a]=idx++;
}
struct node{
    int pnt,dis;
};
struct cmp{
    bool operator () (const node &A,const node &B){
        return A.dis<B.dis;
    }
};
void dij(int s){
    d[s]=0;
    priority_queue<node,vector<node>,cmp>que;
    que.push((node){s,0});
    while(!que.empty()){
        node q=que.top();que.pop();
        int u=q.pnt,len=q.dis;
        if(len>d[u])continue;
        for(int v=h[u];v!=-1;v=ne[v]){
            if(d[e[v]]>d[u]+cost[v]){
                d[e[v]]=d[u]+cost[v];
                que.push((node){e[v],d[e[v]]});
            }
        }
    }
    return;
}
int main(){
    memset(h,-1,sizeof(h));
    memset(d,INF,sizeof(d));
    n=read();m=read();x=read();
    for(register int i=1;i<=m;i++){
        a=read();b=read();c=read();
        add(a<<1,b<<1,c);add(b<<1|1,a<<1|1,c);
    }
    dij(x<<1|1);dij(x<<1);
    int ans=-1;
    for(register int i=1;i<=n;i++){
        if(i==x)continue;
        ans=max(d[i<<1]+d[i<<1|1],ans);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：ShineEternal (赞：4)

# 题目描述：
寒假到了，N头牛都要去参加一场在编号为X（1≤X≤N）的牛的农场举行的派对（1≤N≤1000），农场之间有M（1≤M≤100000）条有向路，每条路长Ti（1≤Ti≤100）。

每头牛参加完派对后都必须回家，无论是去参加派对还是回家，每头牛都会选择最短路径，求这N头牛的最短路径（一个来回）中最长的一条路径长度。

# 分析：
其实这道题的考点就是单元最短路径和单终点最短路径。

单终点最短路径其实就可以把所有的边反过来，直接就转换为单源最短路径了。

于是此题的核心就是跑两遍dijkstra或spfa了（本人偏好dijkstra）。

**还有就是注意变量不要重复**

# [代码](https://blog.csdn.net/kkkksc03/article/details/83050450)

---

## 作者：标准非洲人 (赞：4)

很暴力很暴力的完全两遍spfa正跑反跑。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=100000+5;
struct node1 {
    int v,next,c;
} a1[MAXN];
struct node2 {
    int v,next,c;
} a2[MAXN];
queue<int>q;
int n,m,x,u,v,c,e1,e2,fa1,fa2,son1,son2,c1,c2;
int head1[MAXN],head2[MAXN],dist1[MAXN],dist2[MAXN],fx1[MAXN],fx2[MAXN],ans[MAXN];
bool pd1[MAXN],pd2[MAXN];
void addnode(int u,int v,int c) {
    e1++;
    a1[e1].v=v;
    a1[e1].c=c;
    a1[e1].next=head1[u];
    head1[u]=e1;
}
void addnodef(int u,int v,int c) {
    e2++;
    a2[e2].v=v;
    a2[e2].c=c;
    a2[e2].next=head2[u];
    head2[u]=e2;
}
int spfa_1(int s,int t) {
    memset(dist1,0x7f,sizeof(dist1));
    memset(pd1,0,sizeof(pd1));
    while(!q.empty()) q.pop();
    q.push(s);
    pd1[s]=true;
    dist1[s]=0;
    while(!q.empty()) {
        int fa1=q.front();
        q.pop();
        pd1[fa1]=false;
        for(int i=head1[fa1]; i; i=a1[i].next) {
            int son1=a1[i].v;
            int c1=a1[i].c;
            if(dist1[fa1]+c1<dist1[son1]) {
                dist1[son1]=dist1[fa1]+c1;
                if(!pd1[son1]) {
                    pd1[son1]=true;
                    q.push(son1);
                }
            }
        }
    }
    return dist1[t];
}
int spfa_2(int s,int t) {
    memset(dist2,0x7f,sizeof(dist2));
    memset(pd2,0,sizeof(pd2));
    while(!q.empty()) q.pop();
    q.push(s);
    pd2[s]=true;
    dist2[s]=0;
    while(!q.empty()) {
        int fa2=q.front();
        q.pop();
        pd2[fa2]=false;
        for(int i=head2[fa2]; i; i=a2[i].next) {
            int son2=a2[i].v;
            int c2=a2[i].c;
            if(dist2[fa2]+c2<dist2[son2]) {
                dist2[son2]=dist2[fa2]+c2;
                if(!pd2[son2]) {
                    pd2[son2]=true;
                    q.push(son2);
                }
            }
        }
    }
    return dist2[t];
}
int main() {
    cin>>n>>m>>x;
    for(int i=1; i<=m; i++) {
        cin>>u>>v>>c;
        addnode(u,v,c);
        addnodef(v,u,c);
    }
    for(int i=1; i<=n; i++)
        fx1[i]=spfa_1(i,x);
    while(!q.empty()) q.pop();
    for(int i=1; i<=n; i++)
        fx2[i]=spfa_2(i,x);
    for(int i=1; i<=n; i++) ans[i]=fx1[i]+fx2[i];
    cout<<*max_element(ans+1,ans+n+1)<<endl;
    return 0;
}
```

---

## 作者：地表最萌猫 (赞：3)

~~这一题就是基础的最短路模板吧~~

附上最短路模板传送门

[最短路](https://www.luogu.org/problem/P3371)

那么这一题，我们可以先理解一下题意，很明显要我们反向建图，因为本蒟蒻用的是dijkstra，只需要第一次正着跑一边所有点到x点的距离，反着循环1~n来求出x点到i点的距离,用两个数组来记录一下权值，类似++tot的方法记录一下下标，最后相加求最大应该就行了。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=50010;
int ver[N<<1],head[N<<1],next[N<<1],edge[N<<1],d[N<<1],v[N];
int tot,x,n,m,tot1,tot2,maxx;
int a[N],b[N];
priority_queue< pair<int,int > > q;
void add(int x,int y,int z)
{
	ver[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}
void dijkstra(int S)
{
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	d[S]=0;
	q.push(make_pair(0,S));
	while(q.size())
	{
		int x=q.top().second; q.pop();
		if(v[x]) continue;
		v[x]=1;
		for(int i=head[x];i;i=next[i])
		{
			int y=ver[i],z=edge[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));	
			}	
		}	
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&x);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		add(x,y,z);
	}
	dijkstra(x);
	for(int i=1;i<=n;i++)
	{
		a[++tot1]=d[i];
	}
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	for(int i=1;i<=n;i++)
	{
		dijkstra(i);
		b[++tot2]=d[x];
	}
	for(int i=1;i<=tot1;i++)
	{
		maxx=max(maxx,a[i]+b[i]);
	}
	printf("%d",maxx);
	return 0;
}
```
如有不对的地方，请各位巨佬斧正qwq

~~好像数据不怎么毒瘤呢~~

---

## 作者：hater (赞：3)

这个题目实际上已经有许多好的题解了

~~我再发一篇也只是锦上添葱咕~~~~~

大多数人使用SPFA的 但是蒟蒻天天听：SPFA死了

于是用的是Dijkstra + 堆优化 和 vector建图 

~~这个的好处是开o2可以快很多~~

有的人需要写两个函数来跑

蒟蒻用的是带一个参数（之前题解也有了）

这个参数表示的是跑正向建图或是反向建图

说起来很拗口 但是参考代码理解就很简单了

至于为什么要反向建图 蒟蒻看见有人在问

许多题解也没给出很好的解释

想一下：从所有点到x 跟 x到所有点的最短距离 为什么会不一样

显然因为是图是有向的 （无向的就是一样的 因为可以原路返回）

那么 想求所有点到x的距离的话

把所有图反着建一遍 从x跑 

就相当于从x原路返回到所有点

最后贴个代码

太丑勿喷

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> d[2][1005];
vector <int> e[2][1005];
int dis[2][1005];
bool vis[1005];
int n,m,s;
priority_queue<pair<int,int> > q;
void dj(int Q)
{
    int temp,y,z;
    memset(vis,0,sizeof(vis));
    dis[Q][s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        temp=q.top().second;
        q.pop();
        if(vis[temp]) continue;
        vis[temp]=1;
        for(int i=0;i<d[Q][temp].size();i++)
        {
            y=d[Q][temp][i]; z=e[Q][temp][i];
            if(dis[Q][y]>dis[Q][temp]+z)
            {
                dis[Q][y]=dis[Q][temp]+z;
                q.push(make_pair(-dis[Q][y],y));
            }
        } 
    }
}
int main() {
    int x,y,z,ans=0;
    cin>>n>>m>>s;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y>>z;
        d[0][x].push_back(y);
        e[0][x].push_back(z);
        d[1][y].push_back(x);
        e[1][y].push_back(z);
    }
    dj(0); dj(1);
    for(int i=1;i<=n;i++)
    ans=max(dis[0][i]+dis[1][i],ans);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：kfhkx (赞：2)

### 这是一道练习最短路的题目

给p党一个模板吧~

在这里提供两种思路


------------

## 1. 最容易想到的就是暴力跑n遍最短路来模拟选择哪个牧场，然后再统计答案
- 这样做的话很暴力，一般不可取，因为普通的dijkstra或spfa肯定会超时，所以要用堆优化的dijkstra或者spfa，~~听说优化后的最短路比Floyd快。。。~~

我这里用的是链式前向星存图+堆优化的dijkstra

### p1821.pas
------------
```pascal	
var
        n,m,s,i,j,tot,v,head,bns,x,y,z:longint;
        he,ne,t,w,cj,num,heap,bis,dis,ans:array[0..400010] of longint;
        pd:array[0..1010,0..1010] of longint;
function max(x,y:longint):longint;
begin
        if x>y then exit(x) else exit(y);
end;
procedure swap(var x,y:longint);
var
        t:longint;
begin
        t:=x;
        x:=y;
        y:=t;
end;
procedure link(x,y,z:longint);
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=z;
end;
procedure insert(a,x:longint);
var
        i:longint;
begin
        if cj[x]<>0 then begin
                heap[cj[x]]:=a;
                i:=cj[x];
        end else begin
                inc(heap[0]);
                heap[heap[0]]:=a;
                num[heap[0]]:=x;
                i:=heap[0];
                cj[x]:=heap[0];
        end;
        while (i>>1>0) and (heap[i]<heap[i>>1]) do begin
                swap(cj[num[i]],cj[num[i>>1]]);
                swap(heap[i],heap[i>>1]);
                swap(num[i],num[i>>1]);
                i:=i>>1;
        end;
end;
procedure del;
var
        mid,i:longint;
begin
        cj[num[1]]:=0;
        heap[1]:=heap[heap[0]];
        num[1]:=num[heap[0]];
        dec(heap[0]);
        i:=1;
        if (heap[i<<1]<heap[i<<1+1]) or (i=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        while (mid<=heap[0]) and (heap[mid]<heap[i]) do begin
                swap(cj[num[i]],cj[num[mid]]);
                swap(heap[i],heap[mid]);
                swap(num[i],num[mid]);
                i:=mid;
                if (heap[i<<1]<heap[i<<1+1]) or (i<<1=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        end;
end;
procedure dij(x:longint);
var
        i:longint;
begin
        for i:=1 to n do dis[i]:=maxlongint;
        dis[x]:=0;
        head:=x;
        heap[0]:=1;
        heap[1]:=0;
        num[1]:=x;
        while heap[0]<>0 do begin
                v:=he[head];
                while v<>0 do begin
                        if dis[t[v]]>dis[head]+w[v] then begin
                                dis[t[v]]:=dis[head]+w[v];
                                insert(dis[t[v]],t[v]);
                        end;
                        v:=ne[v];
                end;
                del;
                head:=num[1];
        end;
        if x=s then for j:=1 to n do bis[j]:=dis[j] else ans[x]:=dis[s];
end;
begin
        readln(n,m,s);
        for i:=1 to m do begin
                read(x,y,z);
                if (x=y) or (pd[x,y]=1) then continue;
                pd[x,y]:=1;
                link(x,y,z);
        end;
        for i:=1 to n do dij(i);
        for i:=1 to n do bns:=max(bns,bis[i]+ans[i]);
        writeln(bns);
end.

```
总共跑了277ms，~~数据有点。。。~~


------------
2. 第二种思路就是正反向各跑一次最短路，然后统计答案就行了

一样用的是链式前向星存图+堆优化的dijkstra

### p1821(1).pas


------------
```pascal
var
        n,m,s,i,j,tot,tot1,v,head,bns,x,y,z,ans:longint;
        he,ne,t,w,cj,num,heap,bis,dis,he1,ne1,t1,w1,dis1:array[0..400010] of longint;
        pd:array[0..1010,0..1010] of longint;
function max(x,y:longint):longint;
begin
        if x>y then exit(x) else exit(y);
end;
procedure swap(var x,y:longint);
var
        t:longint;
begin
        t:=x;
        x:=y;
        y:=t;
end;
procedure link1(x,y,z:longint);
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=z;
end;
procedure link2(x,y,z:longint);
begin
        inc(tot1);
        ne1[tot1]:=he1[x];
        he1[x]:=tot;
        t1[tot1]:=y;
        w1[tot1]:=z;
end;
procedure insert(a,x:longint);
var
        i:longint;
begin
        if cj[x]<>0 then begin
                heap[cj[x]]:=a;
                i:=cj[x];
        end else begin
                inc(heap[0]);
                heap[heap[0]]:=a;
                num[heap[0]]:=x;
                i:=heap[0];
                cj[x]:=heap[0];
        end;
        while (i>>1>0) and (heap[i]<heap[i>>1]) do begin
                swap(cj[num[i]],cj[num[i>>1]]);
                swap(heap[i],heap[i>>1]);
                swap(num[i],num[i>>1]);
                i:=i>>1;
        end;
end;
procedure del;
var
        mid,i:longint;
begin
        cj[num[1]]:=0;
        heap[1]:=heap[heap[0]];
        num[1]:=num[heap[0]];
        dec(heap[0]);
        i:=1;
        if (heap[i<<1]<heap[i<<1+1]) or (i=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        while (mid<=heap[0]) and (heap[mid]<heap[i]) do begin
                swap(cj[num[i]],cj[num[mid]]);
                swap(heap[i],heap[mid]);
                swap(num[i],num[mid]);
                i:=mid;
                if (heap[i<<1]<heap[i<<1+1]) or (i<<1=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        end;
end;
procedure dij(x:longint);
var
        i:longint;
begin
        for i:=1 to n do dis[i]:=maxlongint;
        dis[x]:=0;
        head:=x;
        heap[0]:=1;
        heap[1]:=0;
        num[1]:=x;
        while heap[0]<>0 do begin
                v:=he[head];
                while v<>0 do begin
                        if dis[t[v]]>dis[head]+w[v] then begin
                                dis[t[v]]:=dis[head]+w[v];
                                insert(dis[t[v]],t[v]);
                        end;
                        v:=ne[v];
                end;
                del;
                head:=num[1];
        end;
end;
procedure dij1(x:longint);
var
        i:longint;
begin
        for i:=1 to n do dis1[i]:=maxlongint;
        dis1[x]:=0;
        head:=x;
        heap[0]:=1;
        heap[1]:=0;
        num[1]:=x;
        while heap[0]<>0 do begin
                v:=he1[head];
                while v<>0 do begin
                        if dis1[t1[v]]>dis1[head]+w1[v] then begin
                                dis1[t1[v]]:=dis1[head]+w1[v];
                                insert(dis1[t1[v]],t1[v]);
                        end;
                        v:=ne1[v];
                end;
                del;
                head:=num[1];
        end;
end;
begin
        readln(n,m,s);
        for i:=1 to m do begin
                read(x,y,z);
                if (x=y) or (pd[x,y]=1) then continue;
                pd[x,y]:=1;
                link1(x,y,z);
                link2(y,x,z);
        end;
        dij(s);
        dij1(s);
        for i:=1 to n do ans:=max(ans,dis[i]+dis1[i]);
        writeln(ans);
end.
```
60ms


---

## 作者：x_faraway_x (赞：2)

不知道为什么在家写不对在学校就写对了233

这道题算法明显是单源最短路问题。对于单终点最短路，只需要将每条边翻转就可以转换成单源最短路径问题

我用的是SPFA算法，给大家参考

···cpp

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1005, M = 100005;
int Head[N][2],Next[M][2],Adj[M][2],Weight[M],d[N][2],n,m,x,ans=-1;
bool vis[N];
queue<int> Q;
void addedge(int u, int v, int w, int i) { //加一条正边和一条反转的边
    Next[i][0] = Head[u][0];
    Head[u][0]    = i;
    Adj[i][0] = v;
    Weight[i] = w;
    Next[i][1] = Head[v][1];
    Head[v][1] = i;
    Adj[i][1] = u;
}
void SPFA(int t) {
    d[x][t] = 0;
    vis[x] = 1;
    Q.push(x);
    while(!Q.empty()) {
        int f = Q.front();
        Q.pop(); vis[f] = 0;
        for(int e = Head[f][t]; e; e = Next[e][t]) {
            int j = Adj[e][t];
            if(d[j][t] > d[f][t] + Weight[e]) {
                d[j][t] = d[f][t] + Weight[e];
                if(!vis[j]) {
                    vis[j] = 1;
                    Q.push(j);
                }
            }
        }
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &x);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w, i);
    }
    memset(d, 127/3, sizeof(d)); //初始化为1<<30
    SPFA(0); //单源最短路
    memset(vis, 0, sizeof(vis));
    SPFA(1); //单终点最短路
    for(int i = 1; i <= n; i++)
        if(ans < d[i][0] + d[i][1])
            ans = d[i][0] + d[i][1];
    printf("%d", ans);
    return 0;
}
```
···
//大概就是这样吧


---

## 作者：羽儇 (赞：2)

我的思路是：跑两遍最短路，第一遍是按照原本方向的路线，第二遍是反过来的路线。

其实就是敲个Dijkstra+堆优的板子，加上点细节：记录跑第一遍路线的每头牛的最短路线为ans[]，然后清空数组edge，与head（因为我们只需要反转一下边的方向，只需要把原来的边都删去，重新加下边，然后重新跑Dijkstra，求反过来方向后从st到各点的最短路。
最后把ans[]（反转方向之前求得的最短路）与dis[](反转方向的最短路）枚举相加取max即可
```cpp
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
const int maxn = 100010;
const int inf = 0x7fffffff;
struct node 
{
	int next,to,val;
}edge[maxn];
using namespace std;
int uu[maxn],head[1010],vv[maxn],ww[maxn],tot,n,m,st,ans[1010],dis[1010];
bool vis[1010];
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > >q;
void add_edge(int u,int v,int w)
{
    edge[++tot].next=head[u];
    edge[tot].to=v;
    edge[tot].val=w;
    head[u]=tot;
}
void Dijkstra()
{
	for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=false;
	q.push(make_pair(0,st));
	dis[st]=0;
	while(q.size())
	{
		int u = q.top().second;q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=head[u];i;i=edge[i].next)
		{
			int v = edge[i].to;
			if(!vis[v]&&dis[v]>dis[u]+edge[i].val)
			{
				dis[v]=dis[u]+edge[i].val;
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&st);
	for(int i=1;i<=m;i++)
	scanf("%d%d%d",&uu[i],&vv[i],&ww[i]),add_edge(uu[i],vv[i],ww[i]);	
	Dijkstra();
	for(int i=1;i<=n;i++)ans[i]=dis[i];
	tot=0;
	memset(head,0,sizeof(head));
	memset(edge,0,sizeof(edge));
	for(int i=1;i<=m;i++)add_edge(vv[i],uu[i],ww[i]);
	Dijkstra();
	int maxs=0;
	for(int i=1;i<=n;i++)maxs=max(dis[i]+ans[i],maxs);
	printf("%d",maxs);
	return 0;
 } 
```
如有不懂，请私我

---

## 作者：Dog_Two (赞：2)

Bellman代码简短，效率也不算特别差，妥妥的新人福音啊~

楼上有位老哥的想法很棒**反向存边，把单终点问题转化成单源问题**

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10,maxm=1e5+10;
int n,m,X;
int dis_tow[maxn],dis_bac[maxn];
int tow_u[maxm],tow_v[maxm],tow_w[maxm];
int bac_u[maxm],bac_v[maxm],bac_w[maxm];
//toward表示去，back表示返回
void Bell_F(int *dis,int *u,int *v,int *w,int St){
    //数组指针做参数，不必写两份函数 
    fill(dis+1,dis+n+1,0x3f3f3f3f);
    dis[St]=0;
    int k=n-1;
    while(k--){
        bool if_los=false;
        for(int i=1;i<=m;i++){
            int from=u[i],to=v[i],cost=w[i];
            if(dis[to]>dis[from]+cost){
                dis[to]=dis[from]+cost;
                if_los=true;
            }
        }
        if(!if_los) break;
        //没有进行松弛，则退出循环 
    }
}
int main(){
    cin>>n>>m>>X;
    for(int i=1;i<=m;i++){
        register int U,V,W;
        scanf("%d%d%d",&U,&V,&W);
        tow_u[i]=bac_v[i]=U;
        tow_v[i]=bac_u[i]=V;
        //反向存边，把单终点转化为单起点 
        tow_w[i]=bac_w[i]=W;
    }
    Bell_F(dis_tow,tow_u,tow_v,tow_w,X);
    Bell_F(dis_bac,bac_u,bac_v,bac_w,X);
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,dis_tow[i]+dis_bac[i]);
    cout<<ans;
    return 0;
}

```

---

## 作者：Widerg (赞：1)

**哦，最短路，大家最喜欢写了，早就明白要想成功就得写熟经典算法。**

对于每个点i(i!=X)，其往返距离为(i,x)的最短路+(x,i)的最短路，所以可以求任意两点间的最短路径。 但由于N=1000，使用O(N^3)的Floyd会超时。仔细分析发现floyd会求出很多无用的信息，其实只要分别求出x到其他所有点沿正向边和反向边的最短路就可以了，使用两次Dijkstra或者SPFA，能通过所有测试点。（当然聪明的你肯定能考虑到其实一次dj内也可以求出两个最短路）。

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("sparty.in", "r"), *out = fopen("sparty.out", "w");
int n,m,p;
int d[1000][1000];

void store(int a, int b, int c) {
    a--;b--;
    if (d[a][b]==-1 || c<d[a][b]) d[a][b]=c;
}

bool visited[1000];
int best1[1000];
int best2[1000];
void dijk1(void) {
    int i,t,bt;
    for (i=0;i<n;i++) {visited[i]=false; best1[i]=-1;}
    best1[p]=0;
    bool done;
    while(true) {
        done=true; bt=-1;
        for (i=0;i<n;i++) {
            if (!visited[i]&&best1[i]!=-1) {
                if (bt==-1 || best1[i]<bt) {t=i;bt=best1[i];}
                done=false;
            }
        }
        if (done) break;
        for (i=0;i<n;i++) {
            if (d[t][i]!=-1)
                if (best1[i]==-1 || best1[t]+d[t][i]<best1[i])
                    best1[i]=best1[t]+d[t][i];
        }
        visited[t]=true;
    }
}
void dijk2(void) {
    int i,t,bt;
    for (i=0;i<n;i++) {visited[i]=false; best2[i]=-1;}
    best2[p]=0;
    bool done;
    while(true) {
        done=true; bt=-1;
        for (i=0;i<n;i++) {
            if (!visited[i]&&best2[i]!=-1) {
                if (bt==-1 || best2[i]<bt) {t=i;bt=best2[i];}
                done=false;
            }
        }
        if (done) break;
        for (i=0;i<n;i++) {
            if (d[i][t]!=-1)
                if (best2[i]==-1 || best2[t]+d[i][t]<best2[i])
                    best2[i]=best2[t]+d[i][t];
        }
        visited[t]=true;
    }
}

int main(void) {
    int i,j,a,b,c;
    fscanf(in,"%i %i %i",&n,&m,&p); p--;
    for (i=0;i<n;i++) for (j=0;j<n;j++) d[i][j]=-1;
    for (i=0;i<m;i++) {
        fscanf(in,"%i %i %i",&a,&b,&c);
        store(a,b,c);
    }
    dijk1();
    dijk2();
    int r=0;
    for (i=0;i<n;i++)
    {
        if (best1[i]+best2[i]>r)
            r=best1[i]+best2[i];
    }
    fprintf(out,"%i\n",r);
    fclose(in); fclose(out); return 0;
}
```
###重在理解题意！！


---

## 作者：Anakin (赞：1)

思路楼下都说的很清楚了,在这里就不多说了,一个单源最短路,一个单重点最短路,正反图各跑一遍.看到楼下都是写两个函数的，,或者拆边，对于本蒟蒻来说这样写容易搞错变量名,所以在这里提供一个减小代码量并且不容易搞混变量名的写法:把图做成结构体，封装一下，这样写一遍就够了，建完图直接调用，贼方便
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3f3f3f3f
#define MAXN 1000+10
#define MAXM 100000+10
using namespace std;
int read(){
	int out=0;
	char c=getchar();
	while(c<48||c>57) c=getchar();
	while(c<=57&&c>=48){
		out=(out<<1)+(out<<3)+c-48;
		c=getchar();
	}
	return out;
}
void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int n,m,x;
struct Edge{int v,w,next;};
struct Node{
	int id,d;
	bool operator<(const Node a)const{
		return d>a.d;
	}
};
struct G{//图的结构体
	Edge edge[MAXM];
	int cnt;
	int dis[MAXN],head[MAXN];//不用担心变量名冲突
	void init(){//链式前向星的准备
		cnt=0;
		memset(head,-1,sizeof(head));
	}
	inline void addedge(int u,int v,int w){//加边
		edge[++cnt].v=v;
		edge[cnt].w=w;
		edge[cnt].next=head[u];
		head[u]=cnt;
	}
	void dij(){//最短路
		memset(dis,INF,sizeof(dis));
		priority_queue<Node>q;
		q.push(Node{x,0});
		dis[x]=0;
		while(!q.empty()){
			Node temp=q.top();
			q.pop();
			int u=temp.id;
			int d=temp.d;
			if(d!=dis[u]) continue;
			for(int i=head[u];i!=-1;i=edge[i].next){
				int v=edge[i].v,w=edge[i].w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					q.push(Node{v,dis[v]});
				}
			}
		}
	}
}g1,g2;//建两个图,一个正向边一个反向
void init(){
	n=read();
	m=read();
	x=read();
	g1.init();
	g2.init();
	for(int i=1;i<=m;++i){
		int u=read();
		int v=read();
		int w=read();
		g1.addedge(u,v,w);//g1是正向图
		g2.addedge(v,u,w);//g2是反向图
	}
}
int d[MAXN];
int main(){
	init();
	g1.dij();
	g2.dij();
	int ans=0;
	for(int i=1;i<=n;++i){
		d[i]=g1.dis[i]+g2.dis[i];//直接累加就ok
		ans=max(d[i],ans);
	}
	write(ans);
	return 0;
}
```

---

## 作者：原子分子奶子 (赞：1)

前段时间学校考试写的这道题的代码找不到了QwQ,我当时还因为把freopen里的party打成patry少得了100分......

好了不扯犊子了。各个点牛们要去到某一个点再回到自己家（有向图），回来很显然就是一个裸的单源最短路，dijkstra不优化都可以；但是去的话有些麻烦。仔细想一下之后发现只要把所有的边全部反过来，再从开party的地点走一遍dijkstra不就是牛们去开party的总路径和了吗。

前后两个最短路径和相加即为答案，代码抽空写下再贴上来吧，


---

## 作者：EarthGiao (赞：0)

SPFA     
## 【注意注意】
这是单向路单向路单向路！！！   
重要的事情说三遍！！！    
（题目中没点出这点但是我的全WA经历让我深刻的认识到了这一点）    
## 【思路】
去和来这是两个完全相反的东西    
SPFA跑一个方向是很轻松的    
然后另一个方向就很难办了    
该怎么办呢？    
n遍SPFA？    
不太可能这就是一道黄题    
对了！可以反向建图！    
将方向反过来建出来的图就是完全相反的    
某个点到x的距离恰好就是回家的最短距离    
这样和正向建图一结合    
就能求出去和回的最短路径了    
然后比较最大的和    
输出就好了     
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int Max = 100005;
struct node
{
	int y;
	int ne;
	int z;
}a1[Max << 1],a2[Max << 1];
int n,m,x;
const int M = 1002;
int head1[M],head2[M];
int sum = 0;
void add1(int x,int y,int z)
{
	a1[++ sum].y = y;
	a1[sum].z = z;
	a1[sum].ne = head1[x];
	head1[x] = sum;
}
void add2(int x,int y,int z)
{
	a2[++ sum].y = y;
	a2[sum].z = z;
	a2[sum].ne = head2[x];
	head2[x] = sum;
}

int d1[M],d2[M];
bool use[M];
void SPFA1()
{
	memset(use,false,sizeof(use));
	queue<int>q;
	for(register int i = 1;i <= n;++ i)
		d1[i] = 999999;
	d1[x] = 0;
	q.push(x);
	while(!q.empty())
	{
		int qwq = q.front();
		q.pop();use[qwq] = false;
		for(register int i = head1[qwq];i != 0;i = a1[i].ne)
		{
			int awa = a1[i].y;
			if(d1[awa] > d1[qwq] + a1[i].z)
			{
				d1[awa] = d1[qwq] + a1[i].z;
				if(use[awa] == false)
				{
					use[awa] = true;
					q.push(awa);
				}
			}
		}
	}
}
void SPFA2()
{
	memset(use,false,sizeof(use));
	queue<int>q;
	for(register int i = 1;i <= n;++ i)
		d2[i] = 999999;
	d2[x] = 0;
	q.push(x);
	while(!q.empty())
	{
		int qwq = q.front();
		q.pop();use[qwq] = false;
		for(register int i = head2[qwq];i != 0;i = a2[i].ne)
		{
			int awa = a2[i].y;
			if(d2[awa] > d2[qwq] + a2[i].z)
			{
				d2[awa] = d2[qwq] + a2[i].z;
				if(use[awa] == false)
				{
					use[awa] = true;
					q.push(awa);
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&x);
	int xx,yy,zz;
	for(register int i = 1;i <= m;++ i)
	{
		scanf("%d%d%d",&xx,&yy,&zz);
		add1(xx,yy,zz);
		add2(yy,xx,zz);
	}
	SPFA1();
	SPFA2();
	int MM = 0;
	for(register int i = 1;i <= n;++ i)
		MM = max(MM,d1[i] + d2[i]);
	cout << MM << endl;
	return 0;
}
```

---

## 作者：Zekrom (赞：0)

主要思路:对于有向图，只要反向建边跑最短路就行  
~~既然要跑两次，为什么不一次dijk，一次spfa呢（练手）~~  
上代码  
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1010
#define M 100010 
using namespace std;
int n,m,head[N],rhead[N],tot,rtot,d1[N],d2[N],ans,s;
bool vis[N];
struct Edge{
	int v,next,val;
}edge[M],redge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return  x*f;
}
inline void add1(int x,int y,int z){edge[++tot].v=y;edge[tot].val=z;edge[tot].next=head[x];head[x]=tot;}
inline void add2(int x,int y,int z){redge[++rtot].v=y;redge[rtot].val=z;redge[rtot].next=rhead[x];rhead[x]=rtot;}
void dijk(int x){
	priority_queue<pair<int,int> >q;
	memset(d1,0x3f,sizeof(d1));
	q.push(make_pair(0,x));d1[x]=0;
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d1[v]>d1[u]+z){
				d1[v]=d1[u]+z;
				q.push(make_pair(-d1[v],v));
			}
		}
	}
}
void spfa(int x){
	queue<int>q;
	memset(d2,0x3f,sizeof(d2));
	memset(vis,0,sizeof(vis));
	q.push(x);vis[x]=1;d2[x]=0;
	while(q.size()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=rhead[u];i;i=redge[i].next){
			int v=redge[i].v,z=redge[i].val;
			if(d2[v]>d2[u]+z){
				d2[v]=d2[u]+z;
				if(!vis[v])q.push(v),vis[v]=1; 
			} 
		}
	}
	
}
int main()
{
	n=read(),m=read(),s=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add1(x,y,z);add2(y,x,z); 
	} 
	dijk(s);
	spfa(s);
	for(int i=1;i<=n;i++)
		ans=max(ans,d1[i]+d2[i]);
	printf("%d\n",ans); 
	return 0;
}

```


---

## 作者：AugustineYang (赞：0)

SLF优化的SPFA可过。

建立反图求牛去程时（代码中为下标为1的数组）的最短路径

建立正图求牛返程时（代码中为下标为2的数组）的最短路径

opt为相应的操作符号，等于1时求去程，等于2时求返程

```cpp
//1为反图求去时，2为正图求回时 
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAXN 1005
#define MAXM 500005
using namespace std;
int n, m, X, num_edge[3], maxx = -2147483647; //1为反图，2为正图
int head[3][MAXN], dis[5][MAXN];
bool in_queue[MAXN];
struct add
{
	int to, len ,next;
}edge[3][MAXM];
inline int read()
{
	int sum = 0, flag = 1;
	char c = getchar();
	while(!isdigit(c))
	{
		if(c == '-') flag = -1;
		c = getchar();
	}
	while(isdigit(c))
	{
		sum = (sum<<3)+(sum<<1)+(c&15);
		c = getchar();	
	}
	return sum*flag;
}
inline void add_edge(int from, int to, int len, int opt)
{
	edge[opt][++num_edge[opt]].to = to;
	edge[opt][num_edge[opt]].len = len;
	edge[opt][num_edge[opt]].next = head[opt][from];
	head[opt][from] = num_edge[opt];
}
inline void spfa(int s, int opt)
{
	memset(in_queue, 0, sizeof in_queue);
	dis[opt][s] = 0;
	deque<int> q;
	q.push_back(s);
	in_queue[s] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop_front();
		in_queue[u] = 0;
		for(int i=head[opt][u]; i; i=edge[opt][i].next)
		{
			int v = edge[opt][i].to;
			if(dis[opt][v] > dis[opt][u]+edge[opt][i].len)
			{
				dis[opt][v] = dis[opt][u]+edge[opt][i].len;
				if(!in_queue[v])
				{
					if(!q.empty() && dis[opt][v] < dis[opt][q.front()])
						q.push_front(v);
					else q.push_back(v);
					in_queue[v] = 1;
				}
			}
		}
	}
}
int main()
{
	n = read(), m = read(), X = read();
	for(int i=1; i<=m; ++i)
	{
		int x = read(), y = read(), z = read();
		add_edge(y, x, z, 1);
		add_edge(x, y, z, 2);
	}
	memset(dis, 0x3f, sizeof dis);
	spfa(X, 1);
	spfa(X, 2);
	for(int i=1; i<=n; ++i)
	{
		dis[3][i] = dis[1][i]+dis[2][i];
		maxx = max(maxx, dis[3][i]);
	} //dis3存往返全程最短路径
	printf("%d\n", maxx);
	return 0;	
}
```

---

## 作者：江海寄余生 (赞：0)

floyd算法 O（n3）真假的能过呀

n次heapdijkstra O(n m log n）也不见得floyd快

以上两种算法能过多半因为是数据水

其实我们注意到回家的最短路很好找，关键就是去派对的路径，若是一个个点dij，或是floyd，那不是大材小用吗

其实我们只要将所有路径反过来，然后再跑一次以派对点为源节点的最短路，就能轻松算出正常情况下所有点去派对的最短路

时间复杂度O（n2），自测能跑出几十倍于开头算法的速度






```cpp
//adj list
type
  adj=record
    too,last,wei:longint;
  end;
var
  edge,unedge:array[1..100000] of adj;
  unhead,head,a,min,sum:array[1..1000] of longint;
  nedge,v,e,i,j,x,y,z,point,num,minw,minv,max:longint;
procedure add(a,b,w:longint);
begin
  inc(nedge);
  edge[nedge].last:=head[a];
  edge[nedge].too:=b;
  edge[nedge].wei:=w;
  head[a]:=nedge;
end;
procedure unadd(a,b,w:longint);
begin
  unedge[nedge].last:=unhead[a];
  unedge[nedge].too:=b;
  unedge[nedge].wei:=w;
  unhead[a]:=nedge;
end;
procedure readin;
begin
  read(v,e,point);
  nedge:=0;
  fillchar(head,sizeof(head),0);
  for i:=1 to e do
  begin
    read(x,y,z);
    add(x,y,z);
    unadd(y,x,z);
  end;
end;
begin
  readin;
  fillchar(a,sizeof(a),0);
  for i:=1 to v do
  min[i]:=maxlongint;
  a[point]:=1;
  num:=1;
  min[point]:=0;
  x:=head[point];
  while (x>0) do
  begin
    min[edge[x].too]:=edge[x].wei;
    x:=edge[x].last;
  end;
  while num<v do
  begin
    minw:=maxlongint;
    for i:=1 to v do
    if (a[i]=0) and (min[i]<minw) then
    begin
      minv:=i;
      minw:=min[i];
    end;
    x:=head[minv];
    while (x>0) do
    begin
      if min[edge[x].too]>edge[x].wei+min[minv] then
      min[edge[x].too]:=edge[x].wei+min[minv];
      x:=edge[x].last;
    end;
    inc(num);
    a[minv]:=1;
  end;
  for i:=1 to v do
  sum[i]:=min[i];
  fillchar(a,sizeof(a),0);
  for i:=1 to v do
  min[i]:=maxlongint;
  a[point]:=1;
  num:=1;
  min[point]:=0;
  x:=unhead[point];
  while (x>0) do
  begin
    min[unedge[x].too]:=unedge[x].wei;
    x:=unedge[x].last;
  end;
  while num<v do
  begin
    minw:=maxlongint;
    for i:=1 to v do
    if (a[i]=0) and (min[i]<minw) then
    begin
      minv:=i;
      minw:=min[i];
    end;
    x:=unhead[minv];
    while (x>0) do
    begin
      if min[unedge[x].too]>unedge[x].wei+min[minv] then
      min[unedge[x].too]:=unedge[x].wei+min[minv];
      x:=unedge[x].last;
    end;
    inc(num);
    a[minv]:=1;
  end;
  for i:=1 to v do
  sum[i]:=sum[i]+min[i];
  max:=0;
  for i:=1 to v do
  if sum[i]>max then
  max:=sum[i];
  write(max);
end.
```

---

## 作者：sfd158 (赞：0)

使用n次Heap优化的Dijkstra算法即可，这样效率比floyd要高。

```cpp

#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 1005
using namespace std;
typedef pair<int,int> pii;
struct Edge{
    int from,to,dist;
};
vector<Edge> G[maxn];//利用vector数组来储存每一条边
int d[maxn],dx[maxn],ans[maxn];
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > q;//有限队列
int main()
{
    int n,m,x,i,j,u,v,w,X=0;
    scanf("%d%d%d",&n,&m,&x);
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back((Edge){u,v,w});
    }
    for(i=1;i<=n;i++)
    {
        memset(d,0x3f,sizeof(d));
        memset(vis,0,sizeof(vis));
        d[i]=0;
        q.push(make_pair(0,i));
        while(!q.empty())
        {
            u=q.top().second;
            q.pop();
            if(vis[u])continue;
            vis[u]=1;//访问标记
            for(j=0;j<G[u].size();j++)
            {
                Edge &e=G[u][j];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    q.push(make_pair(d[e.to],e.to));
                }
            }
        }
        if(i==x)
            memcpy(dx,d,sizeof(d));
        ans[i]=d[x];
    }
    for(i=1;i<=n;i++)
        X=max(ans[i]+dx[i],X);//比较答案
    printf("%d",X);
    return 0;
}

```

---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/12/11/%E3%80%8CLuogu%201821%E3%80%8D[USACO07FEB]%E9%93%B6%E7%89%9B%E6%B4%BE%E5%AF%B9Silver%20Cow%20Party/)

### Solution

题目让我们一些奶牛走到一个点，再从那个点走回来的最短路之和的最大值。那么我们直接用`dijkstra`计算两次最短路（走过去，走回来）就可以了，最后判断一下，那头奶牛需要走的路是最长的，然后问题就解决了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 200005;
struct EDGE {
    int nxt, to, val;
} edge[MAXN];
int n, m, S, cnt, U[MAXN], V[MAXN], VAL[MAXN], dis[MAXN], dist[MAXN], head[MAXN];
bool vis[MAXN];
inline void addedge(int u, int v, int val) {//邻接表存图
    edge[++cnt].to = v; edge[cnt].val = val; edge[cnt].nxt = head[u]; head[u] = cnt;
}
inline void dijkstra(int S) {//dijkstra最短路
    memset(dis, INF, sizeof(dis));
    priority_queue< pair<int, int> > Q;
    Q.push(make_pair(0, S));
    dis[S] = 0;
    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].val) {
                dis[v] = dis[u] + edge[i].val;
                Q.push(make_pair(-dis[v], v));
            }
        }
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &S);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &U[i], &V[i], &VAL[i]);
        addedge(U[i], V[i], VAL[i]);//正向建图
    }
    dijkstra(S);
    for (int i = 1; i <= n; i++)
        dist[i] = dis[i];//记录走到目标点的路程
    cnt = 0;
    memset(edge, 0, sizeof(edge));
    memset(vis, 0, sizeof(vis));
    memset(head, -1, sizeof(head));//注意清空数组
    for (int i = 1; i <= m; i++)
        addedge(V[i], U[i], VAL[i]);//反向建图
    dijkstra(S);
    int Max = -INF;
    for (int i = 1; i <= n; i++)
        Max = max(Max, dis[i] + dist[i]);//判断那个奶牛是走得最多的
    printf("%d\n", Max);
    return 0;
}
```

---

