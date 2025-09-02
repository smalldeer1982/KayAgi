# Breaking Good

## 题目描述

Breaking Good is a new video game which a lot of gamers want to have. There is a certain level in the game that is really difficult even for experienced gamers.

Walter William, the main character of the game, wants to join a gang called Los Hermanos (The Brothers). The gang controls the whole country which consists of $ n $ cities with $ m $ bidirectional roads connecting them. There is no road is connecting a city to itself and for any two cities there is at most one road between them. The country is connected, in the other words, it is possible to reach any city from any other city using the given roads.

The roads aren't all working. There are some roads which need some more work to be performed to be completely functioning.

The gang is going to rob a bank! The bank is located in city $ 1 $ . As usual, the hardest part is to escape to their headquarters where the police can't get them. The gang's headquarters is in city $ n $ . To gain the gang's trust, Walter is in charge of this operation, so he came up with a smart plan.

First of all the path which they are going to use on their way back from city $ 1 $ to their headquarters $ n $ must be as short as possible, since it is important to finish operation as fast as possible.

Then, gang has to blow up all other roads in country that don't lay on this path, in order to prevent any police reinforcements. In case of non-working road, they don't have to blow up it as it is already malfunctional.

If the chosen path has some roads that doesn't work they'll have to repair those roads before the operation.

Walter discovered that there was a lot of paths that satisfied the condition of being shortest possible so he decided to choose among them a path that minimizes the total number of affected roads (both roads that have to be blown up and roads to be repaired).

Can you help Walter complete his task and gain the gang's trust?

## 说明/提示

In the first test the only path is $ 1-2 $

In the second test the only shortest path is $ 1-3-4 $

In the third test there are multiple shortest paths but the optimal is $ 1-4-6-8 $

## 样例 #1

### 输入

```
2 1
1 2 0
```

### 输出

```
1
1 2 1
```

## 样例 #2

### 输入

```
4 4
1 2 1
1 3 0
2 3 1
3 4 1
```

### 输出

```
3
1 2 0
1 3 1
2 3 0
```

## 样例 #3

### 输入

```
8 9
1 2 0
8 3 0
2 3 1
1 4 1
8 7 0
1 5 1
4 6 1
5 7 0
6 8 0
```

### 输出

```
3
2 3 0
1 5 0
6 8 1
```

# 题解

## 作者：寻旧 (赞：8)

## SPFA

对于想要进一步学习SPFA的同学有比较好的作用。

题目较长，对提升快速提取题目信息的能力也很有效。

也警示我们：如果毫无思路，不如回头再多看一眼题面，从中找到解决问题的突破口！

## 进入正题：

观察题目：他们将在从城市1返回途中使用的路径总长度必须尽可能短

第一眼看到，就想到SPFA跑最短路，但是呢？题目里还有一句话：

#### 使受影响道路的总数最小化

怎么办呢？

还是倒回题面：

1、炸毁不在最短路上的可通行道路。

2、修复在最短路上的不可通行道路。


------------


如何做到影响道路最小化？

相信多读几遍题目的你已经知道了：

让最短路上不可通行道路尽量的少，

也就是说让可通行道路尽量在最短路上，让他们不要被炸。

让不可通行道路尽量不在最短路上，让他们不要被修复。

（拗口没关系，多读几遍）

------------

### 结合两个条件

这就需要我们在跑最短路的时候

将路径长度作为第一关键字

将不可通行道路数量作为第二关键字

跑最短路的时候：

定义：路径长度数组 $d[i]$ 和不可通行道路数量数组 $num[i]$。

如果 $d[y]>d[x]+z$ 就更新 $y$ 的 $d$ 数组和 $num$ 数组

当然，还要记录在最短路上的边，我们可以用一个 $pre$ 数组。

跑完最短路后，就记录不在最短路上的可通行道路

记录在最短路上的不可通行道路

按照题意输出就行了。

具体还可以参照代码。

上代码~

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
LL read()
{
	LL w=0;bool f=true;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=false;c=getchar();}
	while(c>='0'&&c<='9')w=(w<<1)+(w<<3)+(c^48),c=getchar();
	return f?w:~w+1;
}

const int N=1e5+5;

struct edge
{
	int x,y,nxt,flag;
}e[N*2];int tot=-1,fir[N];//这里邻接表的建立不同（tot=-1），意在方便查找反向边。 
void Add(int x,int y,int flag)
{
	e[++tot]=(edge){x,y,fir[x],flag};fir[x]=tot;
}

int n,m;

int d[N],num[N],b[N];
int pre[N][2];
queue<int>Q;
bool g1[N*2],g2[N*2];

void spfa()
{
	memset(d,0x3f,sizeof(d));
	memset(num,0x3f,sizeof(num));
	d[1]=0;num[1]=0;
	Q.push(1);b[1]=1;
	while(Q.size())
	{
		int x=Q.front();Q.pop();b[x]=0;
		for(int k=fir[x];k>=0;k=e[k].nxt)
		{
			int y=e[k].y,z=e[k].flag^1;      //如果flag为1，则通过时不加num 
			if(d[y]==d[x]+1&&num[y]>num[x]+z)  //在最短路径相同的情况下，保证通过不可通行道路最少 
			{
				num[y]=num[x]+z; 
				pre[y][0]=x;pre[y][1]=k;      //pre[i][0]表示到y的是哪个点,pre[i][0]表示到y的是哪条边 
				if(!b[y]) b[y]=1,Q.push(y);
			}
			else if(d[y]>d[x]+1)      //如果路径更短，不管不可通行道路多少，都要更新
			                          //这就是第一关键字和第二关键字的区别 
			{
				d[y]=d[x]+1;
				num[y]=num[x]+z;
				pre[y][0]=x;pre[y][1]=k;
				if(!b[y]) b[y]=1,Q.push(y);
			}
		}
	}
}

int main()
{
	n=read();m=read();
	memset(fir,-1,sizeof(fir));    //这里邻接表的建立不同，意在方便查找反向边。 
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read(),flag=read();
		Add(x,y,flag);Add(y,x,flag);
	}
	spfa();
	int now=n;
	while(now!=1)
	{
		g1[pre[now][1]]=g1[pre[now][1]^1]=true;    //将在最短路上的边标记好，i^查找第i条边的反向边
		                                           //因为前面从0开始记录边，则0对应1    2对应3 
		                                           //1要转化为0只需要xor1就行了，0也是。 
		if(!e[pre[now][1]].flag) g2[pre[now][1]]=g2[pre[now][1]^1]=true;//将在最短路上的不可通行道路标记好 
		now=pre[now][0];
	}
	int Ans[N][4],nn=0;
	for(int i=0;i<=tot;i+=2)
	{
		if((!g1[i]||!g1[i^1])&&e[i].flag)     //如果他不是最短路上的边，并且可通行，炸毁 
		{
			Ans[++nn][1]=e[i].x;
			Ans[nn][2]=e[i].y;
			Ans[nn][3]=0;
		}
		if(g2[i]||g2[i^1])                    //如果他是最短路上边，并且不可通行，修复 
		{
			Ans[++nn][1]=e[i].x;
			Ans[nn][2]=e[i].y;
			Ans[nn][3]=1;
		}
	}
	printf("%d\n",nn);
	for(int i=1;i<=nn;++i)
	  printf("%d %d %d\n",Ans[i][1],Ans[i][2],Ans[i][3]);
	return 0;
}
```


蒟蒻第二次写题解，如有错误不满欢迎批评指出。

在距离考试还有10天的这时，我忠心地说一句：

# 祝大家CSP RP++！

---

## 作者：Travller (赞：5)

~~闲来无事，写篇题解。~~

写完之后看了看题解，发现写的大多是 SPFA 。

这里奉上一份用 Dijkstra 的写法(其实差不多)。


------------

# 题目大意
给定 $n$ 个点，$m$ 条边（边权都为1）的无向图，初始时每条道路有两种状态（$0$ 代表是坏的，$1$ 代表是好的）。

找一条 $1-n$ 的最短路，将选的路径上的坏的道路修好，将不在选的路径上的其他好边炸掉！使受影响的道路的总量最小，并输出受影响的道路的操作（修好或炸掉）。

# 分析
### 首先：

> 首先，他们将在从城市1返回途中使用的路径总长度必须尽可能短。

题目中这句话是突破口，这句话告诉我们选的路径必须是最短路。


------------

### 其次：

于是我们不管道路的维修情况，先求出从 $1-n$ 的最短路，这里直接 Dijkstra 求最短路就好了。可能有很多条从 $1-n$ 的最短路。然后我们就需要筛选出我们想要的那条最短路。

设 $dis$ 表示从 $1-n$ 的最短路上边的数量，$cnt$ 表示最短路上好的边的数量，$huai$ 表示最短路上坏的边的数量，$tot$ 表示整张图好的边的数量。

我们发现受影响的道路 $ans=tot-cnt+huai$。同时可以发现 $huai=dis-cnt$。

所以 $ans=tot+dis-2\times cnt$，$dis$ 是 $1-n$ 的最短路，是确定的，所以 $ans$ 随着 $cnt$ 的增大而减小，要求 $ans$ 的最小值，我们就让 $cnt$ 尽量大呗。于是我们要去找路径上好边最多的一条最短路。


------------

### 然后：
可以发现，最终求得的所有最短路组成的图是一张拓扑图，因为一个点的最短路从上一个点的最短路过来，所以可以将所有在最短路上的路径新建一张图，设 $cnt_i$ 表示从 $1$ 到 $i$ 的路径上好边的数量，拓扑序一直求出 $cnt_n$。

关于如何将所有在最短路上的路径新建一张图：

枚举所有边，如果 $dis_v+w=dis_u$ 或 $dis_u+w=dis_v$，说明该边是一条最短路，然后就连边。

第一问就求出来了。


------------

### 再其次:
然后还要输出受影响的边的操作，需要维修则输出 `u v 1`；需要炸毁则输出 `u v 0`。这就需要我们进一步的求出具体是哪一条最短路了。

如何求呢？

我们采用上面新建图类似的做法，设 $w$ 为道路的好坏情况，从 $n$ 往回走，如果 $cnt_v+w=cnt_u$，说明 $u$ 是从 $v$ 走过来的，我们就走连向 $v$ 的路径，将路径上的边标记，其实也是一个拓扑序，只不过是从 $n-1$ 的，于是具体哪条路径就求出来了。

### 最后：
枚举每条边，如果这条边被标记了，说明在被选的路径上，同时这条边如果是坏的（需要修好），输出。
如果这条边没有被标记，说明不在被选的路径上，同时这条边是好的（需要炸掉），输出。

这道题就结束了。
### 后记：

其实与 SPFA 写法思路是一样的，只不过 SPFA 在求最短路的时候可以进行多次松弛，所以可以直接求出路径，而 Dij 基于贪心，一个点一旦被确定，就无法再被其他点更新，所以步骤麻烦一些。


# Code
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
inline long long read(){
	long long w=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		w=w*10+ch-'0';
		ch=getchar(); 
	}
	return w*f;
}
int n,m,dis[100005],ind[100005],cnt[100005],tot;
bool vis[100005];
vector<int> g[100005];
vector<pair<int,int> > g1[100005];
vector<pair<int,pair<int,int> > > g2[100005];
bool mark[100005];
struct edge{
	int u;
	int v;
	int w;
}e[100005];
void dij(){
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0,q.push(make_pair(0,1));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push(make_pair(dis[v],v));
			}
		}
	} 
}
void select(){
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v,w=e[i].w;
		if(dis[u]+1==dis[v]){
			g1[u].push_back(make_pair(w,v));
			ind[v]++;
			g2[v].push_back(make_pair(w,make_pair(i,u)));
		}else if(dis[v]+1==dis[u]){
			g1[v].push_back(make_pair(w,u));
			ind[u]++;
			g2[u].push_back(make_pair(w,make_pair(i,v))); 
		}
	}
}
void topo1(){
	queue<int> q;
	q.push(1),cnt[1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<g1[u].size();i++){
			int v=g1[u][i].second;
			int w=g1[u][i].first;
			cnt[v]=max(cnt[v],cnt[u]+w);
			ind[v]--;
			if(!ind[v]) q.push(v);
		}
	}
}
void topo2(){
	queue<int> q;
	q.push(n);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<g2[u].size();i++){
			int v=g2[u][i].second.second;
			int w=g2[u][i].first;
			int id=g2[u][i].second.first;
			if(cnt[u]-w==cnt[v]){
				q.push(v);
				mark[id]=1;
				break; 
			}
		} 
	}
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){
    	int u=read(),v=read(),w=read();
    	if(w) tot++;
    	e[i].u=u,e[i].v=v,e[i].w=w;
    	g[u].push_back(v);
    	g[v].push_back(u);
	}
	dij();
	select();
	topo1();
	topo2();
	cout<<tot+dis[n]-2*cnt[n]<<endl;
	for(int i=1;i<=m;i++){
		if(mark[i]&&!e[i].w) cout<<e[i].u<<" "<<e[i].v<<" "<<1<<endl;
		else if(!mark[i]&&e[i].w) cout<<e[i].u<<" "<<e[i].v<<" "<<0<<endl;
	}
	return 0;
}
```




---

## 作者：Alarm5854 (赞：5)

这道题目直接 bfs 即可，不知道为什么要用 SPFA。

存边的时候，需要多存一个有关于该道路状态的信息。然后，边 bfs 边 dp。

记 $f_i$ 为从 $1$ 开始，走到 $i$ 的最短路径长度，$g_i$ 为达到 $f_i$ 所需要修改道路状态的最小次数。若 $f_v>f_u+1$，那么直接更新，否则如果 $f_v=f_u+1$，那么就以修改次数更新答案。

这样为什么是正确的呢？因为正常的道路和异常的道路的数量是一定的，而 $g_n$ 是修改的最小次数，所以需要炸毁的道路也是最少的。

最后，因为要输出方案，所以要记录一个 $pre$ 数组为经过的边。

```cpp
#include<ctime>
#include<queue>
#include<cctype>
#include<cstdio>
const int N = 1e5 + 10;
using namespace std;
inline int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
struct Edge {
	int to, st, nxt; Edge(int to = 0, int st = 0, int nxt = 0): to(to), st(st), nxt(nxt){}
} e[N * 2];
struct node {
	int u, v, w; node(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w){}
} a[N];
int n, m, x, y, z, tot, ans, head[N], f[N], g[N], vis[N], pre[N];
void out(int p, int st) {//st代表这次是否要输出，第一次不输出，因为还不知道最少修改次数
	if (p == 1) return;
	int u = a[pre[p]].u, v = a[pre[p]].v, w = a[pre[p]].w;
	vis[pre[p]] = 1, out(u == p ? v : u, st);
	if (!st) return;
	if (!w) printf("%d %d 1\n", u, v);
}
void add(int u, int v, int w) {
	e[++tot] = Edge(v, w, head[u]);
	head[u] = tot;
}
void bfs() {
	queue<int> q; q.push(1);
	for (int i = 2; i <= n; ++i) f[i] = n;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to, id = (i + 1) / 2, w = e[i].st;
			if (f[v] > f[u] + 1)
				f[v] = f[u] + 1, g[v] = g[u] + (w ^ 1), pre[v] = id, q.push(v);
			else if (f[v] == f[u] + 1 && g[v] > g[u] + (w ^ 1))
				g[v] = g[u] + (w ^ 1), pre[v] = id;
		}
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		x = read(), y = read(), z = read();
		add(x, y, z), add(y, x, z);
		a[i] = node(x, y, z);
	}
	bfs();
	ans = g[n];
	out(n, 0);
	for (int i = 1; i <= m; ++i) if (!vis[i] && a[i].w) ++ans;
	printf("%d\n", ans);
	out(n, 1);
	for (int i = 1; i <= m; ++i) {
		if (!vis[i] && a[i].w)
		printf("%d %d 0\n", a[i].u, a[i].v);
	}
	return 0;
}
```



---

## 作者：453xzz (赞：5)

## 千万要看清题目！
~~由于看错题目而抱灵n次~~

输出的第一行为最少的修改路径，不是从起点到终点的路径！

这里提供一种有些麻烦但是好想也好写的方法QAQ

------------
第一步：用spfa找出所有条最短路

第二步：用dfs找出最短路中需要修改最少的路

第三步：将第二步走的路0改为1，不走的路1改0

```
#include<bits/stdc++.h>
using namespace std;
#define nnn 100300

int get(){             //快读
	int ss=1;
	char c;
	while((c=getchar())<'0'||c>'9'){
		if(c=='-')ss=-1;
	}
	int res=c-'0';
	while((c=getchar())>='0'&&c<='9'){
		res=res*10+c-'0';
	}
	return res*ss;
}

int go[nnn*2],nex[nnn*2],head[nnn*2],jz[nnn*2],tot;
int m,n;
bool vv[nnn];
int lu[nnn];
vector<int>fa[nnn];
vector<int>zhi[nnn];
queue<int>q;

void add(int p,int q,int o){      //前向星存图
	go[++tot]=q;nex[tot]=head[p];head[p]=tot;jz[tot]=o;
}


void spfa(){           //跑第一遍最短路，找所有的可能路径
	memset(lu,0x3f3f3f,sizeof(lu));
	q.push(1);
	vv[1]=true;
	lu[1]=0;
	int tem,tt;
	while(!q.empty()){
		tem=q.front();
		q.pop();
		vv[tem]=false;
		for(int i=head[tem];i;i=nex[i]){
			tt=go[i];
			if(lu[tt]==1+lu[tem]){
				fa[tt].push_back(tem);   //存可能路径
				zhi[tt].push_back(jz[i]);
				if(!vv[tt]){
					vv[tt]=true;
					q.push(tt);
				}
			}
			if(lu[tt]>lu[tem]+1){
				lu[tt]=lu[tem]+1;
				while(!fa[tt].empty()){
					fa[tt].clear();
					zhi[tt].clear();
				}
				fa[tt].push_back(tem);
				zhi[tt].push_back(jz[i]);
				if(!vv[tt]){
					vv[tt]=true;
					q.push(tt);
				}
			}
		}
	}
}

int ans[nnn],lo[nnn],last;

void dfs(int u,int dep){
	if(u==1){
		if(dep>=last){   //拥有最少不用修改的路
			last=dep;
			for(int i=1;i<=n;i++){
				ans[i]=lo[i];
			}
		}
		return ;
	}
	for(int i=0;i<fa[u].size();i++){ 
		lo[fa[u][i]]=u;
		dfs(fa[u][i],dep+zhi[u][i]);
		lo[fa[u][i]]=0;
	}
}

bool zoul[nnn];
int z1[nnn],z2[nnn],z3[nnn],qwq;

void dfs2(int u,int fa){   //找输出路径
	int tem;
	for(int i=head[u];i;i=nex[i]){
		tem=go[i];
		if(zoul[(1+i)/2]==true)continue;
		if(ans[tem]==u||ans[u]==tem){
			if(jz[i]==0){
			    z1[++qwq]=u;
			    z2[qwq]=tem;
			    z3[qwq]=1;
			}
		}else{
			if(jz[i]==1){
			    z1[++qwq]=u;
			    z2[qwq]=tem;
			    z3[qwq]=0;
			}
		}
		zoul[(i+1)/2]=true;
		dfs2(tem,u);
	}
}

int main(){
	n=get(),m=get();
	int x,y,z;
	for(int i=1;i<=m;i++){
		x=get();y=get();z=get();
		add(x,y,z);
		add(y,x,z);
	}
	spfa();               //第一步
	memset(lo,0,sizeof(lo));
	memset(zoul,0,sizeof(zoul));
	last=0;
	dfs(n,0);             //第二步
	dfs2(1,0);            //第三步
	cout<<qwq<<endl;
	for(int i=1;i<=qwq;i++){
		cout<<z1[i]<<" "<<z2[i]<<" "<<z3[i]<<endl;
	}
	return 0;
} 
```

求大佬放过QAQ

CSP RP++

---

## 作者：justin_cao (赞：3)

题解全都是$SPFA$是怎么回事啊。。

首先分析题目发现题目实际上就是要求选的最短路上的不能通行的道路尽量的少，因为最短路是固定的。

然后考虑求最短路，发现边长都是$1$直接跑一个$bfs$即可。

把最短路求出来之后考虑把最短路图给弄出来，然后考虑在上面$dp$，设$f[i]$为从$1$到$i$在最短路图的路上最少的不能通行的道路，拓扑排序转移即可。

这样就做完了，复杂度$O(n)$。

code：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<stack>
#include<bitset>
#define eps 1e-15
#define maxn 100010
#define maxm 410
#define inf 1000000007
#define mod 1000000007
#define mp(x,y) make_pair(x,y)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef pair<int,int> pii;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m;
struct P{
    int u,v,w;
}e[maxn];
int head[maxn],nxt[maxn*2],to[maxn*2],c[maxn*2],id[maxn*2],tot;
void add(int u,int v,int x,int y)
{
    tot++;
    nxt[tot]=head[u];
    head[u]=tot;
    to[tot]=v;
    c[tot]=x;
    id[tot]=y;
}
int dis[maxn];
queue<int>q;
void get_dis()
{
    for(int i=2;i<=n;i++)  dis[i]=-1;
    q.push(1);
    while(q.size())
    {
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=nxt[i])
        {
            if(dis[to[i]]<0)
            {
                dis[to[i]]=dis[now]+1;
                q.push(to[i]);
            }
        }
    }
}
int f[maxn],las[maxn],las_id[maxn],deg[maxn];
void DP()
{
    for(int i=1;i<=n;i++)  f[i]=inf;f[1]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j;j=nxt[j])
        {
            if(dis[to[j]]==dis[i]+1)  deg[to[j]]++;
        }
    }
    q.push(1);
    while(q.size())
    {
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=nxt[i])
        {
            if(dis[to[i]]==dis[now]+1)
            {
                deg[to[i]]--;
                if(f[to[i]]>f[now]+(c[i]^1))
                {
                    f[to[i]]=f[now]+(c[i]^1);
                    las[to[i]]=now;
                    las_id[to[i]]=id[i];
                }
                if(!deg[to[i]])  q.push(to[i]);    
            }
        }
    }
}
int ans[maxn],res;
int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        e[i].u=read();e[i].v=read();e[i].w=read();
        add(e[i].u,e[i].v,e[i].w,i);
        add(e[i].v,e[i].u,e[i].w,i);
    }
    get_dis();
    DP();
    for(int i=n;i!=1;i=las[i])  ans[las_id[i]]=1;
    for(int i=1;i<=m;i++)
      if(e[i].w^ans[i])  res++;
    printf("%d\n",res);
    for(int i=1;i<=m;i++)
    {
        if(e[i].w^ans[i])  printf("%d %d %d\n",e[i].u,e[i].v,ans[i]);
    }
    return 0;
}
```

---

## 作者：hzoi_liuchang (赞：2)

### 分析
首先，我们要选择一条最短的路径

在路径最短的基础上，我们要尽量使受影响的道路数更少

因此我们要在跑$Dij$的结构体里存储三个东西

即当前节点的编号，当前节点距离起点的最短路径，当前路径下更改的道路条数

在进行松弛操作时，如果$dis[u]>dis[now]+b[i].val$

那么我们像之前那样更新$dis$值即可

如果$dis[u]=dis[now]+b[i].val$但是新的路径更改的道路条数更少

此时我们也需要更新
### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int head[maxn],tot=1;
struct asd{
    int from,to,next,val,jud;
}b[maxn];
void ad(int aa,int bb,int cc,int dd){
    b[tot].from=aa;
    b[tot].to=bb;
    b[tot].next=head[aa];
    b[tot].val=cc;
    b[tot].jud=dd;
    head[aa]=tot++;
}
struct jie{
    int num,jl,hf;
    jie(int aa,int bb,int cc){
        num=aa,jl=bb,hf=cc;
    }
    bool operator < (const jie& A) const{
        if(jl==A.jl) return hf>A.hf;
        return jl>A.jl;
    }
};
priority_queue<jie> q;
bool viss[maxn];
int dis[maxn],jl[maxn],hf[maxn];
void dij(){
    memset(dis,0x3f,sizeof(dis));
    memset(hf,0x3f,sizeof(hf));
    dis[1]=0;
    hf[1]=0;
    q.push(jie(1,0,0));
    while(!q.empty()){
        int now=q.top().num;
        int nhf=q.top().hf;
        q.pop();
        if(viss[now]) continue;
        viss[now]=1;
        for(int i=head[now];i!=-1;i=b[i].next){
            int u=b[i].to;
            if(dis[u]>dis[now]+b[i].val){
                dis[u]=dis[now]+b[i].val;
                jl[u]=i;
                hf[u]=nhf+b[i].jud;
                q.push(jie(u,dis[u],hf[u]));
            } else if(dis[u]==dis[now]+b[i].val){
                if(hf[u]>nhf+b[i].jud){
                    jl[u]=i;
                    hf[u]=nhf+b[i].jud;
                    q.push(jie(u,dis[u],hf[u]));
                }
            }
        }
    }
}
vector<int> g;
bool vis[maxn];
int main(){
    memset(head,-1,sizeof(head));
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int aa,bb,cc;
        scanf("%d%d%d",&aa,&bb,&cc);
        ad(aa,bb,1,cc^1);
        ad(bb,aa,1,cc^1);
    }
    dij();
    int ans=0;
    int now=n;
    while(jl[now]){
        if(jl[now]%2==0) g.push_back(jl[now]-1);
        else g.push_back(jl[now]);
        now=b[jl[now]].from;
    }
    for(int i=0;i<g.size();i++){
        vis[g[i]]=1;
    }
    for(int i=1;i<tot;i+=2){
        if(vis[i]){
            if(b[i].jud==1){
                ans++;
            }
        } else {
            if(b[i].jud==0){
                ans++;
            }
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<tot;i+=2){
        if(vis[i]){
            if(b[i].jud==1){
                printf("%d %d %d\n",b[i].from,b[i].to,1);
            } 
        } else {
            if(b[i].jud==0){
                ans++;
                printf("%d %d %d\n",b[i].from,b[i].to,0);
            }
        }
    }
    return 0;
}
```


---

## 作者：ifyml (赞：2)

## SPFA


------------
### 这道题大意
在一个有n个城市m条道路的国家，有一个犯罪团伙要去抢劫银行，银行在城市1，犯罪团伙在城市n，
walter的任务是在城市1和城市n之间选择一个最短路径，当有多个最短路径的时候选择影响值最小的 ，
为0的道路是指未工作的，为1的道路是指修好的，walter在选择好最短路径后，要修复好最短路径上
未工作的路，破坏其他路径上工作的路径。

**影响值= 修复+破坏的道路**   
**修复的道路=最短路径数-最短路径上工作的路径**  
**破坏的道路=工作的总道路-最短路径上工作的道路** 
#### ~~所以要使影响值最小应该使得~~
### **最短路径上面工作的道路最多**

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define NN 100001
#define inf 0x7fffffff
using namespace std;
int N,M,sum,ok,x;
struct ss{
    int to,c,fl;
    bool operator < (const ss &r)const{return r.c<c;}
};
int dis[NN],used[NN],s[NN],val[NN],A[NN],B[NN],C[NN];
vector<ss>q[NN],ans[NN];
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&A[i],&B[i],&C[i]);
        //C表示路径的状况，是工作还是未工作 
        q[A[i]].push_back((ss){B[i],0,C[i]});
        q[B[i]].push_back((ss){A[i],0,C[i]});
        sum+=C[i];//记录整个图的工作的路径的个数
    }
    for(int i=2;i<=N;i++)dis[i]=inf;
    priority_queue<ss>que;
    que.push((ss){1,0});
    while(!que.empty())
    {
        ss t=que.top();que.pop();
        int u=t.to;
        used[u]=0;
        for(int i=0;i<q[u].size();i++)
        {
            int v=q[u][i].to;
            int fl=q[u][i].fl;
            if(dis[v]>dis[u]+1||((dis[v]==dis[u]+1)&&(val[v]<val[u]+fl)))
            {
                dis[v]=dis[u]+1;
                val[v]=val[u]+fl;
                s[v]=u;//记录前驱结点
                if(!used[v])
                {
                    que.push((ss){v,dis[v]});
                    used[v]=1;
                }
            }
        }
    }
    memset(used,0,sizeof(used));used[1]=1;
    ok=dis[N]-val[N]*2+sum;
    //影响值=最短路径中的未工作的路径+其他路径中工作的路径   
    x=N;
    while(x!=1)
    {
        used[x]=1;
        x=s[x];
    }
    printf("%d\n",ok);
    for(int i=1;i<=M;i++)
    {
        if(used[A[i]]&&used[B[i]]&&C[i]==0)
         printf("%d %d 1\n",A[i],B[i]);//最短路径输出未工作的路径
        if((!used[A[i]]||!used[B[i]])&&C[i]==1)
         printf("%d %d 0\n",A[i],B[i]);//其他路径输出工作的路径
    }
    return 0;
}
```

---

## 作者：Eazin_star (赞：1)

### 思路
题目大意这里就不说了，相信大家都理解了。

那题目绕来绕去是让我们求什么呢？简单来讲就是最短路并且道路影响最小，也就是最短路上的不可通行道路尽可能少，不在最短路上的可通行道路尽可能多。

那我们只需要在跑最短路的时候多开个数组记录下这条路上不可通行道路的数量最后输出就行了，整体思路还是比较好想的，就是实现稍微有点复杂。~~（可能是本蒟蒻码力太弱了）~~

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

struct JZ {
	int fr, to, nxt, flag;
}edge[200005];
struct Eazin {
	int x, y, z;
}ans[100005]; //记录答案
queue <int> q;
int n, m, cnt = 1;
int head[100005], dis[100005], vis[100005], num[100005], pre[100005][2]; //num记录一条路上的不可通行道路数量，pre记录在最短路上的边
bool ind[200005], indw[200005]; //ind记录是否在目标最短路上，indw记录在目标最短路上且不可通行的边
void add(int u, int v, int w) {
	edge[++cnt] = {u, v, head[u], w};
	head[u] = cnt;
}
void spfa() {
	memset(dis, 0x3f, sizeof dis);
	memset(num, 0x3f, sizeof num);
	dis[1] = 0, num[1] = 0, q.push(1), vis[1] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = 0;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to, f = edge[i].flag^1;
			if (dis[v] == dis[u]+1 && num[v] > num[u]+f) { //如果都是最短路，用不可通行道路的数量来松弛
				num[v] = num[u]+f; //更新
				pre[v][0] = u, pre[v][1] = i; //记录在最短路上的边
				if (!vis[v]) q.push(v), vis[v] = 1;
			} 
			else if (dis[v] > dis[u]+1) { //松弛最短路
				dis[v] = dis[u]+1, num[v] = num[u]+f; //更新
				pre[v][0] = u, pre[v][1] = i; //记录最短路上的边
				if (!vis[v]) q.push(v), vis[v] = 1;
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	}
	spfa(); //跑最短路
	int now = n;
	while (now != 1) {
		ind[pre[now][1]] = ind[pre[now][1]^1] = 1; //记录是否在最短路上
		if (!edge[pre[now][1]].flag) indw[pre[now][1]] = indw[pre[now][1]^1] = 1; //记录在最短路上不可通行的道路
		now = pre[now][0];
	}
	int cur = 0;
	for (int i = 2; i <= cnt; i += 2) {
		if (!ind[i] && edge[i].flag) ans[++cur] = {edge[i].fr, edge[i].to, 0}; //如果不是最短路上的边并且可通行，炸毁道路
		if (indw[i]) ans[++cur] = {edge[i].fr, edge[i].to, 1}; //如果是最短路上的边并且不可通行，修复道路
	}
	printf("%d\n", cur);
	for (int i = 1; i <= cur; i++) printf("%d %d %d\n", ans[i].x, ans[i].y, ans[i].z);  //输出答案
	return 0;
}
```

---

## 作者：modfisher (赞：1)

# 思路
简单来说就是在从节点 $1$ 到节点 $n$ 的最短路径中，选出一条不可通行道路最少的最短路。因为不可通行道路总数不变，所以当路径上的不可通行道路最少时，路径外的不可通行道路最多，则需要操作的次数一定最少。

别的先不说，先考虑最短路：无向无权图，用 Bfs 即可。

思考 Bfs 的过程：对于每一个节点，用它的最短路径去更新它所能到达的所有节点的最短路径，因为该图无向无权，所以一定最优。换言之，记节点 $1$ 到节点 $x$ 的最短路径长度为 $dis[x]$，只要节点 $u$ 与节点 $v$相连，且 $dis[u]+1\geq dis[v]$，则节点 $v$ 的其中一条最短路径的前驱一定是节点 $u$。

那么，我们可以记录从节点 $1$ 到节点 $x$ 的最短路径中可通行道路最多的数量，则在每次转移时，都比较一次，若发现了可通行道路更多的方案，就更新。

那最短路径如何记录呢？定义前驱数组 $pre$ ，记从节点 $1$到节点 $x$ 最短路径中可通行道路最多的最短路径中，$x$ 的前驱为 $pre[x]$，就可以解决了。

# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int head[maxn], nxt[maxn << 1], to[maxn << 1], ww[maxn << 1], cnt = 0, dis[maxn], dis2[maxn], vis[maxn], pre[maxn];
int uu[maxn], vv[maxn], www[maxn], tag[maxn];
queue<int> q;

void add(int u, int v, int w){
	nxt[++ cnt] = head[u];
	to[cnt] = v;
	ww[cnt] = w;
	head[u] = cnt;
}
void bfs(int st){
	memset(dis, 0x3f, sizeof(dis));
	q.push(st);
	vis[st] = 1;
	dis[st] = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; i; i = nxt[i]){
			int j = to[i];
			if(dis[x] + 1 <= dis[j]){
				dis[j] = dis[x] + 1;
				if(dis2[x] + ww[i] >= dis2[j]){
					dis2[j] = dis2[x] + ww[i];
					pre[j] = i + 1 >> 1;
				}
			}
			if(!vis[j]){
				q.push(j);
				vis[j] = 1;
			}
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i ++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		uu[i] = u;
		vv[i] = v;
		www[i] = w;
		add(u, v, w);
		add(v, u, w);
	}
	bfs(1);
	int x = n;
	while(x != 0){
		int i = pre[x], j = uu[i] == x ? vv[i] : uu[i];
		tag[i] = 1;
		x = j;
	}
	int ans = 0;
	for(int i = 1; i <= m; i ++){
		if((tag[i] && !www[i]) || (!tag[i] && www[i])){
			ans ++;
		}
	}
	printf("%d\n", ans);
	for(int i = 1; i <= m; i ++){
		if(tag[i] && !www[i]){
			printf("%d %d 1\n", uu[i], vv[i]);
		}else if(!tag[i] && www[i]){
			printf("%d %d 0\n", uu[i], vv[i]);
		}
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：1)

## 思路
为啥要用 $\verb!SPFA!$，明明就是个 $\verb!dij!$ 的模板。只不过我们在记录最短路的时候还要记录一个变量为当前路途上可以通行的路的条数。显然这个条数越多越好，我们可以少修几条。

至于方案，我们在跑 $\verb!dij!$ 的时候记录 $\verb!pre!$，代表它是从哪里转移过来的。最后输出方案的过程略显繁琐，我使用了一个 $\verb!set!$ 记录不需要变动的边，每次扫到一个边判断一下是否已经不需变动即可。
## 冗长的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
#define F first
#define S second
#define mp make_pair
int const N=1e5+10;
int f[N],f1[N],pre[N];
vector<int>a[N],b[N];
set< pair<int,int> >finish;
vector< pair<int,int> >xiu,ans;
priority_queue< pair<int,int>,deque< pair<int,int> >,greater< pair<int,int> > >q;
inline void dijkstra(int st){
	memset(f,0x3f,sizeof(f));
	memset(f1,0x3f,sizeof(f1));
	f[st]=f1[st]=0;
	q.push(mp(0,st));
	while (!q.empty()){
		int now=q.top().second,dis=q.top().first;
	    q.pop();
		for (rint j=0;j<a[now].size();++j){
	    	int to=a[now][j],cost=1-b[now][j];
	        if (f[now]+1<f[to]) f[to]=f[now]+1,f1[to]=f1[now]+cost,pre[to]=now,q.push(mp(f[to],to));
		    if (f[now]+1==f[to] && f1[now]+cost<f1[to]) f1[to]=f1[now]+cost,pre[to]=now,q.push(mp(f[to],to));//这是需要修改的路的数量
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;
	for (rint i=1;i<=m;++i){
		int x,y,z;cin>>x>>y>>z;
		a[x].push_back(y);
		a[y].push_back(x);
		b[x].push_back(z);
		b[y].push_back(z);
	}
	dijkstra(1);
	int now=n;
	while (now!=1){
		int to=pre[now],x=now;
		for (rint i=0;i<a[x].size();++i)
		    if (a[x][i]==to){
				if (b[x][i]==0) xiu.push_back(mp(x,a[x][i]));
				finish.insert(mp(x,a[x][i]));
				break;
			}
		now=pre[now];
	}
	for (rint i=1;i<=n;++i)
		for (rint j=0;j<a[i].size();++j){
			int to=a[i][j];
		    if (finish.find(mp(i,to))!=finish.end() || finish.find(mp(to,i))!=finish.end()) continue;//查询是否已经删过了
	        finish.insert(mp(i,to));
	        if (b[i][j]==1) ans.push_back(mp(i,to));
		}
	cout<<xiu.size()+ans.size()<<'\n';
	for (auto j:xiu) cout<<j.F<<' '<<j.S<<" 1\n";
	for (auto j:ans) cout<<j.F<<' '<<j.S<<" 0\n";
	return 0;
}
```


---

## 作者：RC·阿柒 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF507E)

---

### 题意分析：

这题最重要的是要看懂题目意思：

- 给出 n 个城市和 m 条边，其中 z 表示此边是否能通行。
- 求一条从城市 $ 1 $ 到 n 尽可能短且对道路的影响（即炸毁或修复）尽可能小的路。

**那么如何使选出的路对道路的影响小呢？**

多读几遍题可知：

1. 对于在所选路径上的路，所要修复（即不可通行）的路要尽可能少。
2. 对于非所选路径上的路，所要炸毁（即可通行）的路要尽可能少。

## 解：

这题用最短路做（~~关于 SPFA ，它死了。~~），于是我用 Dijkstra 做。

---

根据刚才的分析，

我们用 $ dis_{ i } $ 表示从城市 $ 1 $ 到 i 的最短路长度，

$ path_{ i } $ 表示所选最短路中从城市 1 到 i 的不可通行路的数量，

更新时考虑找路径最短，且路径中不可通行路数量少：

```cpp
//it.nxt表示下一个城市，now表示现在的城市，
//it.w表示这条路能否通行（因为 0 表示不可通行，所以加 !it.w，即加 1）。
if((dis[it.nxt]==dis[now]+1&&path[it.nxt]>path[now]+!it.w)||dis[it.nxt]>dis[now]+1)
{
    更新...
}
```

---

#### 输出：

这题的输出也是有点麻烦。

我们先用 $ pre_{ v } = u $ 表示前驱，即路径中城市 v 的上一个是城市 u，

跑完 Dijkstra 后从 n 点递归标记选出的最短路：

```cpp
void Print(int x)
{
    vis[x]=1;
    if(pre[x])
        Print(pre[x]);
}
int main()
{
    ...
    memset(vis,0,sizeof(vis));
    Print(n);
    ...
}
```

然后对于所有边按题意模拟一遍输出即可。（具体见代码）

---

### Code：

**注：**

本代码中有关 **auto** 的用法最好用 C++17 提交，

不过其实这个在 C++14 就能用（只是会警告，我平时都用 C++14 交的），

但这题用 C++14 在 CF 上交会 CE。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int nxt;bool w;
};
int n,m;
vector<Node>a[100001];//本人较懒，就用vector存边了

int dis[100001],vis[100001],path[100001],pre[100001];
typedef pair<int,int> Pii;
priority_queue<Pii,vector<Pii>,greater<Pii> >q;//小根堆

void Dijkstra(int s)//堆优化 Dijkstra
{
    memset(dis,0x3f,sizeof(dis));//初始化
    memset(path,0x3f,sizeof(path));//别忘记初始化 path 
    dis[s]=0;path[s]=0;q.emplace(0,s);
    while(!q.empty())
    {
        auto [w,now]=q.top();q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(auto it:a[now])//遍历与城市 now 相连的城市，用 auto 可以省很多码。
        {
            if((dis[it.nxt]==dis[now]+1&&path[it.nxt]>path[now]+!it.w)||dis[it.nxt]>dis[now]+1)
            {
                //更新
                dis[it.nxt]=dis[now]+1;
                path[it.nxt]=path[now]+!it.w;
                pre[it.nxt]=now;
                q.emplace(dis[it.nxt],it.nxt);
            }
        }
    }
}
void Print(int x)//递归标记选出的路径
{
    vis[x]=1;
    if(pre[x])
        Print(pre[x]);
}
int ans[100001][3],sum;//用来存答案
signed main()
{
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++)//无向图存边
        cin>>u>>v>>w,a[u].emplace_back((Node){v,w}),a[v].emplace_back((Node){u,w});
    Dijkstra(1);
    memset(vis,0,sizeof(vis));
    Print(n);
    for(int i=1;i<=n;i++)
    {
        for(auto it:a[i])
        {
            if((vis[i]&&vis[it.nxt]&&it.w==1)||(!(vis[i]&&vis[it.nxt])&&it.w==0))continue;//按题意模拟
            else if(i<it.nxt)//无向图防止重复输出
            {
                sum++;
                ans[++ans[0][0]][0]=i,ans[ans[0][0]][1]=it.nxt,ans[ans[0][0]][2]=!it.w;//记录答案，修复和炸毁和原先反一下，所以存 !it.w
            }
        }
    }
    cout<<sum<<'\n';//输出
    for(int i=1;i<=ans[0][0];i++)
        cout<<ans[i][0]<<' '<<ans[i][1]<<' '<<ans[i][2]<<'\n';
	return 0;
}

```

---

## 作者：QQH08 (赞：1)

其实这题直接模拟题意即可。

- 先把所有的最短路求出来（我用了dijkstra），顺便记录最短路上每个点的父亲（后面遍历要用）。

- 然后从 $n$ 号点开始dfs，遍历每一条最短路，记录这条最短路上的坏掉的路（sum）。当走到 $1$ 号点时，把答案和这条最短路要修改路径的条数取 $min$ 即可，顺便记录路径。

- 枚举每一条边，如果它不在答案的最短路上且它是好的，就要把它炸掉。如果它在答案的最短路上且它是坏的，就要把它修好。

然后就是代码实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,edgenum,tot,ans,ans2=2e9,head[N],Next[N*2],vet[N*2],d[N],p[N],ans3[N],X[N],Y[N],Z[N];
bool vis[N];
priority_queue<pair<int,int> >q;
vector<int> fa[N];
map<int,int> mp[N],flag[N];
void add(int u,int v){
	edgenum++;
	Next[edgenum]=head[u];
	vet[edgenum]=v;
	head[u]=edgenum;
}
void dij(int s){
    for(int i=1;i<=n;i++)d[i]=2e9;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
        if(vis[u])continue;
		vis[u]=1;
		for(int e=head[u];e;e=Next[e]){
			int v=vet[e];
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				fa[v].clear();
				fa[v].push_back(u);
				if(!vis[v])q.push(make_pair(-d[v],v));
			}
			else if(d[v]==d[u]+1)fa[v].push_back(u);
		}
	}
}
void dfs(int u,int sum,int l){
	if(u==1){
		if(sum+tot-(ans-sum)<ans2){
			for(int i=1;i<=ans+1;i++)ans3[i]=p[i];
			ans2=sum+tot-(ans-sum);
		}
		return;
	}
	for(int i=0;i<fa[u].size();i++){
		int v=fa[u][i];
		if(vis[v])continue;
		p[l]=v;
		int sum2=sum;
		if(mp[u][v]==0)sum2++;
		vis[v]=1;
		dfs(v,sum2,l+1);
		vis[v]=0;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v);
		add(v,u);
		if(w==1)tot++;
		X[i]=u,Y[i]=v,Z[i]=w;
		mp[u][v]=mp[v][u]=w;
	}
	dij(1);
	ans=d[n];
	p[1]=n;
	memset(vis,0,sizeof(vis));
	dfs(n,0,2);
	for(int i=1;i<=ans;i++){
		flag[ans3[i]][ans3[i+1]]=flag[ans3[i+1]][ans3[i]]=1;
		// cout<<ans3[i]<<"O";
	}
	puts("");
	printf("%d\n",ans2);
	for(int i=1;i<=m;i++){
		if(Z[i]==0){
			if(flag[X[i]][Y[i]]==1)printf("%d %d %d\n",X[i],Y[i],1);
		}
		else{
			if(flag[X[i]][Y[i]]==0)printf("%d %d %d\n",X[i],Y[i],0);
		}
	}
	return 0;
}
```


---

