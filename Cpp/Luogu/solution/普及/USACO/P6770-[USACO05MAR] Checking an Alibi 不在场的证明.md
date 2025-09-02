# [USACO05MAR] Checking an Alibi 不在场的证明

## 题目描述

农场有 $F$ 个点，已知 $P$ 条边以及每条边的起点终点和通过时间，给出 $C$ 个有牛的点，求在规定时间 $M$ 内能从起点到达牛当前位置的牛的数量，并按升序输出牛的编号。

谷仓里发现谷物被盗！FJ 正试图从 $C$ 只奶牛里找出那个偷谷物的罪犯。幸运的是，一个恰好路过的卫星拍下谷物被盗前 $M$ 秒的农场的图片。这样约翰就能通过牛们的位置来判断谁有足够的时间来盗窃谷物。

约翰农场有 $F$ 草地，标号 $1$ 到 $F$，还有 $P$ 条双向路连接着它们。通过这些路需要的时间在 $1$ 到 $70000$ 秒的范围内。田地 $1$ 上建有那个被盗的谷仓。给出农场地图，以及卫星照片里每只牛所在的位置，请判断哪些牛有可能犯罪。

请注意：数据里可能存在重边（起点和终点相同的边）。

## 说明/提示

#### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/ik4552lc.png)

#### 数据约定

对于 $100\%$ 的数据：$1 \le M \le 70000$，$1 \le C \le 100$，$1 \le P \le 1000$，$1 \le F \le 500$。

## 样例 #1

### 输入

```
7 6 5 8
1 4 2
1 2 1
2 3 6
3 5 5
5 4 6
1 7 9
1
4
5
3
7```

### 输出

```
4
1
2
3
4```

# 题解

## 作者：一只书虫仔 (赞：12)

#### Description

> 给定一个 $N$ 点 $M$ 边的图，有 $C$ 个有奶牛的点，如果他们到达点 $1$ 的最短时间在 $\rm limit$ 内，那么就算这只奶牛犯罪。求有哪些奶牛犯罪。

#### Solution

这题其实可以简化为最短路。

因为我们要求的是每只奶牛到达点 $1$ 的 **最短时间**，所以我们每次计算$1$ 到奶牛所在的点的最短路即可。

为了更简便一点，我们可以使用 SPFA，进行一次 SPFA，然后调用 ${\rm dist}_i$ 即可。

在最后统计答案的时候容易错，放一下统计答案的代码。

```cpp
for (int i = 1, x; i <= c; i++) {
	scanf("%d", &x);
	if (dist[x] <= limit)
		ans[++pnt] = i;
}
printf("%d\n", pnt);
sort(ans + 1, ans + pnt + 1);
for (int i = 1; i <= pnt; i++)
	printf("%d\n", ans[i]);
```

By Shuchong     
2020.8.18

---

## 作者：WanderingTrader (赞：5)

没有人发dijkstra的题解啊，那我来发一个。
### 题目分析
样例解释里的地图说明了一切。

![](https://cdn.luogu.com.cn/upload/image_hosting/ik4552lc.png)

其实就是一个最短路问题。把农场看作结点，边看作边（smwy），通过的时间看作权值。然后求有多少个奶牛到1号结点的最短路不超过 $M$。

我们看到，通过的时间在 $[1,7\times10^4]$ 范围内，所以图的边权都是正数，可以采用dijkstra算法。

不过此题的数据范围很小，所以朴素版和堆优化版的都可以。（连某死了的算法都可以）
### 代码
输入整张图后，我们令第 $i$ 个奶牛的编号是 $id[i]$，存储一下。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
const int maxm=1005;
const int inf=5e8;
int h[maxn],id[maxn],d[maxn];
bool ok[maxn];
int tot=0;
struct edge {int v,w,next;} e[maxm<<1];
void dijkstra(int n,int s)
{
	fill(ok,ok+1+n,false);
	fill(d,d+1+n,inf);
	d[s]=0;
	for(int i=1;i<=n;++i)
	{
		int u=0;
		for(int j=1;j<=n;++j) if(!ok[j]&&d[j]<d[u]) u=j;
		ok[u]=true;
		for(int j=h[u];j;j=e[j].next)
		{
			int v=e[j].v;
			d[v]=min(d[u]+e[j].w,d[v]); 
		}
	}
}
inline void add(int u,int v,int w)
{
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].next=h[u];
	h[u]=tot;
}
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	int n=read(),m=read(),c=read(),t=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=c;++i) id[i]=read();
	dijkstra(n,1);
	return 0;
}
```
求出最短路后（这里采用dij朴素版），遍历 $id$ 数组，计个数。
```cpp
	int ans=0;
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) ++ans;
	printf("%d\n",ans);
```
然后再遍历一次，输出
```cpp
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) 
		printf("%d\n",i);
```
毕竟 $C\le100$，多跑一次循环也无妨。

所以全部代码就是这样：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
const int maxm=1005;
const int inf=5e8;
int h[maxn],id[maxn],d[maxn];
bool ok[maxn];
int tot=0;
struct edge {int v,w,next;} e[maxm<<1];
void dijkstra(int n,int s)
{
	fill(ok,ok+1+n,false);
	fill(d,d+1+n,inf);
	d[s]=0;
	for(int i=1;i<=n;++i)
	{
		int u=0;
		for(int j=1;j<=n;++j) if(!ok[j]&&d[j]<d[u]) u=j;
		ok[u]=true;
		for(int j=h[u];j;j=e[j].next)
		{
			int v=e[j].v;
			d[v]=min(d[u]+e[j].w,d[v]); 
		}
	}
}
inline void add(int u,int v,int w)
{
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].next=h[u];
	h[u]=tot;
}
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	int n=read(),m=read(),c=read(),t=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=c;++i) id[i]=read();
	dijkstra(n,1);
	int ans=0;
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) ++ans;
	printf("%d\n",ans);
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) 
		printf("%d\n",i);
	return 0;
}
```
堆优化的dij也同理，这里就不解释了。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
const int maxm=1005;
const int inf=5e8;
int h[maxn],id[maxn],d[maxn];
bool ok[maxn];
int tot=0;
struct edge {int v,w,next;} e[maxm<<1];
struct node
{
	int u,dis;
	bool operator < (const node& x) const
	{
		return dis>x.dis;
	}
};
void dijkstra(int n,int s)
{
	fill(ok,ok+1+n,false);
	fill(d,d+1+n,inf);
	d[s]=0;
	priority_queue <node> Q;
	Q.push((node){s,0});
	while(!Q.empty())
	{
		int u=Q.top().u;Q.pop();
		if(ok[u]) continue;
		ok[u]=true;
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(d[v]>d[u]+e[i].w)
			{
				d[v]=d[u]+e[i].w;
				Q.push((node){v,d[v]});
			}
		}
	}
}
inline void add(int u,int v,int w)
{
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].next=h[u];
	h[u]=tot;
}
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	int n=read(),m=read(),c=read(),t=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=c;++i) id[i]=read();
	dijkstra(n,1);
	int ans=0;
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) ++ans;
	printf("%d\n",ans);
	for(int i=1;i<=c;++i) if(d[id[i]]<=t) 
		printf("%d\n",i);
	return 0;
}
```
$$\texttt{The End.}$$

---

## 作者：封禁用户 (赞：3)

### 最短路模板题

题目大意:

 给出$P$条边,$C$个点,询问这$C$个点中,有几个点到第一个点的最短路 $\le$ $M$,输出点数和满足条件的点的编号。
 
直接在单源最短路模板代码上增加一点点东西就可以了,注意存双向边。

```
#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int v,w,next;
}
e[200005];
int head[200005],k,m,c,p,f;
int dis[100005],vis[100005],sum,ans[100005];
void adde(int u,int v,int w)
{
	e[++k].v=v;
	e[k].w=w;
	e[k].next=head[u];
	head[u]=k;
}
//链式前向星 
void dij()
{
	typedef pair<int,int>pii;
	priority_queue<pii,vector<pii>,greater<pii> >q;
	dis[1]=0;
	q.push(make_pair(dis[1],1));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w)
			{
				dis[v]=dis[u]+e[i].w;
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
//迪杰斯特拉
int main()
{
	cin>>f>>p>>c>>m;
	for(int i=1;i<=100000;i++)
		dis[i]=1e9;
	for(int i=1;i<=p;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		adde(x,y,z);
		adde(y,x,z);//双向边 
	}
	dij();
	for(int i=1;i<=c;i++)
	{
		int a;
		cin>>a;//输入点 
		if(dis[a]<=m)//如果满足条件 
		{
			sum++;//点数加一 
			ans[sum]=i;//存储点的编号 
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
		cout<<ans[i]<<endl;
	return 0;
}

```


---

## 作者：JK_LOVER (赞：3)

## 题意
$n$ 个点 $m$ 条边，求问有几个点的最短路径长度小于等于 $M$ 。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6770)
## 分析
看懂题就可以做。这个就是让你求单源最短路。而且不卡 $SPFA$ 。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101010;
int n,m,k,T,head[N],cnt = 0,vis[N],dis[N];
struct Edge{int to,w,nxt;}e[N<<1];
void add(int x,int y,int w){
	e[++cnt].nxt = head[x];e[cnt].to = y;e[cnt].w = w;head[x] = cnt;
	e[++cnt].nxt = head[y];e[cnt].to = x;e[cnt].w = w;head[y] = cnt;
}
vector<int> To;
queue<int> Q;
int main()
{
	cin >> n >> m >> k >> T;
	for(int i = 1;i <= m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1] = 0;Q.push(1);vis[1]=1;
	while(!Q.empty()){
		int x = Q.front();Q.pop();
		vis[x] = 0;
		for(int i = head[x];i;i = e[i].nxt){
			int y = e[i].to;
			if(dis[y] > dis[x] + e[i].w){
				dis[y] = dis[x]+e[i].w;
				if(vis[y])continue;
				Q.push(y);vis[y] = 1;
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= k;i++){
		int a;cin>>a;
		if(dis[a]<=T) ans++,To.push_back(i);
	}
	cout<<ans<<endl;
	for(int i = 0;i < To.size();i++)
	cout<<To.at(i)<<endl;
	return 0;
}
```


---

## 作者：Tomwsc (赞：2)

看了一下，怎么都是最短路啊？这题 bfs 可以轻松水过，蒟蒻就来发一篇 bfs 的题解吧。

## 题意：

给你一张无向图，让你求从 1 号节点在规定时间内可以到达的有牛的节点的数量以及牛的编号。

## 思路：

可以直接从一号节点进行 bfs，每次从队首弹出一个节点后便判断有没有牛在这个节点上，有就用一个 ans 数组存储起来，然后遍历与它相邻的节点，加入队列。最后 sort 排序一下再输出就好了。

注意：一个节点上可能有多只牛，所以每次出队时必须 $O(n)$ 遍历牛所在的位置。

## 代码：

因为 $1≤F≤500$ 所以可以使用邻接矩阵存图。同时注意一下重边就好了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 510;
int n , m , c , t;
int mapp[MAXN][MAXN];
int area[MAXN];
int ans[MAXN];
int cnt;
bool flag[MAXN];

inline void bfs() {
	queue<pair<int , int>>q;
	q.push(make_pair(1 , 0));
	while(!q.empty()) {
		int u = q.front().first;
		int time = q.front().second;
//		cout << u << " ";
		q.pop();
		if(flag[u])
			continue;
		if(time > t)
			continue;
		flag[u] = true;
		for(int i = 1;i <= c;i ++)
			if(area[i] == u)
				ans[++ cnt] = i;		//存答案
		for(int i = 1;i <= n;i ++)
			if(i != u && mapp[u][i] != INT_MAX)		//是否连通
				q.push(make_pair(i , time + mapp[u][i]));
	}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> c >> t;
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
			if(i != j)
				mapp[i][j] = INT_MAX;
	for(int i = 1;i <= m;i ++) {
		int u , v , w;
		cin >> u >> v >> w;
		mapp[u][v] = min(mapp[u][v] , w);
		mapp[v][u] = min(mapp[v][u] , w);
	}
	for(int i = 1;i <= c;i ++)
		cin >> area[i];
	bfs();
	sort(ans + 1 , ans + 1 + cnt);
	cout << cnt << '\n';
	for(int i = 1;i <= cnt;i ++)
		cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：FutureThx (赞：1)

感觉 $USACO$ 里的题不是奶牛就是农夫 $John$ ,反正肯定有一个跑不了……
## 题意
给定一个无向图，共有 $F$ 个点和 $P$ 条边，再给一个常数 $T$ 和 $C$ 个点，求出有多少个点对于 $1$ 最短路权值小于 $T$.
$ $

题目：[传送门](https://www.luogu.com.cn/problem/P6770)

## 思路
**直接求 $1$ 到所有其他节点的最短路，一个个和 $T$ 比较一下就行了**
$ $

怎么求最短路呢？
$ $

这里我本来想偷懒用 $Floyd$ 做的算了一波复杂度发现根本不可行，那就给大家介绍一下 $Dijkstra$ .
$ $

0. 读入数据

1. 采用邻接矩阵， $e[i][j]$ 记为 $i$ 到 $j$ 的权值，若无法直接到达记为 无穷大。

2. 初始化 $dis$ 数组， $dis$ 数组表示所有边到 $1$ 的最短路径：$dis[i] = e[1][i]$ 

3. 初始化 $f$ 数组($true$ 表示未访问,$false$ 表示已访问)，表示一个点是否被访问，到后面的核心算法有用

4. 初始化 $f[1] = false$，因为 $1$ 本身就是起点

5. 敲黑板，划重点了！
```
5.0  按照最坏情况，需要中转 n 次，进行循环:

    5.1  首先需要求出图中距离 1 点最近并且未被访问过的节点，记作点 u

    5.2  接着将点 f[u] = false ,表示点 u 已被访问

    5.3  比较所有未访问的节点中的路径是否最优，可以两个选择 
       1.dis[i] : 直接按照原来的路走，不变化
       2.dis[u] + e[i][u] : 以 u 为中转点,换条路 
```

6. 遍历 $dis$ 如果 $dis[i] \le T$ ,记录，输出

7. 就完工了，华丽结束

## 代码

注释在代码里，希望各位**借鉴思路而不是借鉴代码**，否则后果自负
```cpp
#include <iostream>
using namespace std;
const int inf = 0x3f3f3f3f;//inf最好别用0x7fffffff，特容易爆
int e[502][502],n,m,t,c,f[502],dis[502]; //声明数组
int main(){
    cin >> n >> m >> t >> c;//输入
    for(int i = 1;i <= n;i++)//初始化 e 数组
       for(int j = 1;j <=  n;j++)
          e[i][j] = i == j ? 0 : inf;
    for(int i = 1;i <= m;i++){
        int t1,t2,t3;
        cin >> t1 >> t2 >> t3;//读入边
        e[t1][t2] = min(t3,e[t1][t2]);//因为是无向图，就相当于建两条有向边
        e[t2][t1] = min(t3,e[t2][t1]);
    }
    for(int i = 1;i <= n;i++)
       dis[i] = e[i][1];//初始化 dis 数组
    f[1] = 1;//将起点 f[1] 标记 
    for(int i = 1;i <= n;i++){
        int minn = inf,u;
        for(int j = 1;j <= n;j++)//找距离 1 最小且未被访问的点 u
            if(f[j] == 0 && dis[j] < minn)
               minn = dis[j],u = j;
        if(minn == inf)break;//松弛次数可能不足 n -1，如果 u 未更新，数组就可能越界，需要退出
        f[u] = 1;
        for(int j = 1;j <= n;j++)//找最短路
           if(f[j] == 0)
              dis[j] = min(dis[j],dis[u] + e[j][u]);
    }
    //剩下的就是简单的处理了
    int a[501],t2 = 0;
    for(int i = 1;i <= t;i++){
        int x;
        cin >> x;
        if(dis[x] <= c)
           t2++,a[t2] = i;
    }
    cout << t2 << endl;
    for(int i = 1;i <= t2;i++)
        cout << a[i] << endl;
    return 0;
}
```
这里特别感谢一下 @wsyhb 帮助我解决了一些错误，才写下了这篇题解

## 后记
$Updata \ 2020.9.7 \ :$ 完成题解，求管理员给通过

---

## 作者：爱晚亭哦 (赞：1)

### 裸的$SPFA$，不卡时方便食用老少皆宜

求1到每只牛的最短路，小于等于$M$就有犯罪嫌疑。

$Code:$

```
#include<cstdio>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
int f,p,c,m;
const int F=1001;
const int P=20001;
const int MAXN=2147483647;
int nx[P],head[P],to[P],w[P];
int dis[F],vis[F],sum[101];
int summ;
void add(int x,int y,int z)
{
	nx[++summ]=head[x];
	to[summ]=y;
	w[summ]=z;
	head[x]=summ;
}//邻接表存图
void spfa()//求最短路
{
	for(int i=1;i<=F;i++)
	{
		dis[i]=MAXN;
		vis[i]=0;
	}
	queue <int> t;
	t.push(1);
	dis[1]=0;
	vis[1]=1;
	while(!t.empty())
	{
		int u=t.front();
		t.pop();
		vis[u]=0;
		for(int i=head[u];i;i=nx[i])
		{
			int v=to[i];
			if(dis[v]>dis[u]+w[i])
			{
				dis[v]=dis[u]+w[i];
				if(!vis[v])
				{
					vis[v]=1;
					t.push(v);
				}
			}
		}
	}
}
int main()
{
	int x,y,z,ans=0;
	scanf("%d %d %d %d",&f,&p,&c,&m);
	for(int i=1;i<=p;i++)
	{
		scanf("%d %d %d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	spfa();
	for(int i=1;i<=c;i++)
	{
		scanf("%d",&x);
		if(dis[x]<=m)//有犯罪嫌疑就计入答案
			sum[++ans]=i;
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%d\n",sum[i]);
}
```
不卡$SPFA$的出题人都是好人$qwq$

---

## 作者：CCF_zkskyer (赞：1)

# 题解！！！
## Checking an Alibi 不在场的证明

一、看题

   这道题蛮单纯的，就是让我们先求每一个点到点1的最短时间，然后再判断最短时间是否不超过$M$，然后先输出有嫌疑的牛的总数，再挨个输出编号。仅此而已。
   
#### 注意，如果有不会最短路径的朋友，可以先转至本蒟蒻写的最短路径之$dijkstra$——[纯属手写](https://blog.csdn.net/Kimi_Kai/article/details/106725753)

二、代码


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a,b;
	friend bool operator < (const node &x,const node &y)
	{
		return x.a>y.a;
	}
}; //重载 

priority_queue<node> q;
int head[500005],to[500005],val[500005],ne[500005],n,m,c,t,cnt;
long long dis[100005];
bool flag[100005];
int farm[100005];

void edge(int a,int b,int c)
{
	to[++cnt]=b;
	val[cnt]=c;
	ne[cnt]=head[a];
	head[a]=cnt;
} //添边 

int main()
{
	cin>>n>>m>>c>>t; //由于个人懒的缘故，不想写scanf 
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		edge(u,v,w); 
		edge(v,u,w);
	}  //切记双向存边 
	for (register int i=1;i<=c;++i)
	{
		cin>>farm[i];
	} //每头牛所在的农场 
	
	for (int i=1;i<=n;i++)
	{
		dis[i]=0x7f7f7f7f;
	} //初始化 
	
	dis[1]=0;
	q.push((node){0,1}); //终点先入队 
	
	while(q.size()!=0)
	{
		int x=q.top().b;
		q.pop();
		if(flag[x]==1) continue;
		flag[x]=1;
		for(int i=head[x]; i; i=ne[i])
		{
			if(dis[to[i]]>dis[x]+val[i])
			{
				dis[to[i]]=dis[x]+val[i];
				q.push((node){dis[to[i]],to[i]}); 
			} //松弛操作 
		}
	} //求最短时间 
	
	int num=0; //存有嫌疑的数量 
	
	for (register int i=1;i<=c;++i)
	{
		if (dis[farm[i]]<=t) num++;
	} //先求数量 
	cout<<num<<endl;
	
	for (register int i=1;i<=c;++i)
	{
		if (dis[farm[i]]<=t) cout<<i<<endl;
	} //在挨个输出 
	
	return 0;
}
```


------------

# 谢谢观看！！！

---

## 作者：novax (赞：0)

#### 题意
题意很简单，就是给你一个无向图，并按顺序给你 $C$ 个图中的点，求这些点中距离起点小于等于 $M$ 的点的数量，并按从小到大的顺序输出刚才读入这些点时的编号。

注意，要输出的是后来读入时的编号而不是点本身的编号。

#### 思路
既然要求的最短路的起点不同而终点相同，那么不妨反过来，将 $1$ 号点作为起点，分别求出到达每个点的最短路，并用数组存下来每个有牛的点，分别判断从 $1$ 到每个有牛的点的最短路是否大于 $M$ 并按顺序输出它们的编号就可以了。

#### 代码
本题的主体就是求最短路，因为数据范围很小，用Bellman-Ford、SPFA、无优化Dijkstra和用堆优化的Dijkstra都可以。

我用的是链式前向星+手写队列SPFA，代码如下（个人码风原因代码可能略长请见谅）

```cpp
#include <cstdio>
//SPFA 
//邻接表 链式前向星
struct edge
{
	int to,value,nex;//边的指向 边的权值 下一条边 
};
edge a[20010];//边数组 
int head[510];//链首
int d[510];//到第i个点的最短路 
bool p[510];//第i个点是否在队列里 0为不在 
int ci[510];//这个点是否有牛 
int que[1010];//队列 
const int quaa=1000;
int L,R;//队首 队尾 左闭右开
int cnt;//当前边数 
int N,M,C,T;
void add(int u,int v,int w)
{
	a[++cnt].to=v;
	a[cnt].value=w;
	a[cnt].nex=head[u];
	head[u]=cnt;
} 
void push(int x)//将x插入队列 
{
	que[R%quaa]=x;
	R++;
} 
int pop()
{
	L++;
	return que[(L-1)%quaa];
} 
int main()
{
	L=0;R=1;
	scanf("%d%d%d%d",&N,&M,&C,&T);
	int i,j,x,y,z,ans;
	for(i=1;i<=M;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(i=0;i<=505;i++)
	{
		d[i]=2147483647;
		p[i]=0;
	}
	d[1]=0;
	push(1);
	p[1]=1;
	while(L<R)//SFPA主体
	{
		x=pop();
		p[x]=0;
		for(i=head[x];i!=0;i=a[i].nex)
		{
			y=a[i].to;
			if(d[y]>d[x]+a[i].value)
			{
				d[y]=d[x]+a[i].value;
				if(p[y]==0)
				{
					push(y);
					p[y]=1;
				}
			}
		}
	} 
	ans=0;
	for(i=1;i<=C;i++)
	{
		scanf("%d",&x);
		ci[i]=x;
		if(d[x]<=T)
		{
			ans++;
		}
	}
	
	printf("%d\n",ans);
	for(j=1;ci[j]!=0;j++)
	{
		if(d[ci[j]]<=T)
		printf("%d\n",j);
	}
}
```


---

## 作者：_Fontainebleau_ (赞：0)

这是一道 **单源最短路** 模板题。

根据题意，我们直接以 $1$ 点为起点跑最短路（ SPFA 或 Dij 都行），然后判断当前奶牛所在的位置距离 $1$ 点最短路径是否 $≤ m$ ，小于等于的话说明有犯罪嫌疑，就用 vector 记录下来，最后统一输出。

下面是 SPFA 的代码 ~~手写队列真的快~~ 。

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int x,p,c,m,cnt,s,f,e,q[1001001];
int h[502],t[2001],val[2001],nxt[2001],dis[502];
bool inq[502];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*f;
}
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
int main()
{
	memset(dis,-1,sizeof(dis));
	x=read(),p=read(),c=read(),m=read(),s=1;
	for(int i=1;i<=p;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	f=e=1,inq[s]=true,q[1]=s,dis[s]=0;
	while(f<=e)
	{
		int u=q[f++];
		for(int P=h[u];P;P=nxt[P])
		{
			int v=t[P],C=val[P];
			if(dis[v]==-1||dis[v]>dis[u]+C)
			{
				dis[v]=dis[u]+C;
				if(!inq[v])	inq[v]=true,q[++e]=v;
			}
		}
		inq[u]=false;
	}
	int ans=0;
	vector<int> v;
	for(int i=1;i<=c;i++)
	{
		int u=read();
		if(dis[u]<=m&&dis[u]!=-1)	ans++,v.push_back(i);
	}
	printf("%d\n",ans);
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
		printf("%d\n",*it);	
	return 0;
}

```


---

