# The Tag Game

## 题目描述

Alice got tired of playing the tag game by the usual rules so she offered Bob a little modification to it. Now the game should be played on an undirected rooted tree of $ n $ vertices. Vertex 1 is the root of the tree.

Alice starts at vertex 1 and Bob starts at vertex $ x $ ( $ x≠1 $ ). The moves are made in turns, Bob goes first. In one move one can either stay at the current vertex or travel to the neighbouring one.

The game ends when Alice goes to the same vertex where Bob is standing. Alice wants to minimize the total number of moves and Bob wants to maximize it.

You should write a program which will determine how many moves will the game last.

## 说明/提示

In the first example the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/b7ec0a99b40c82b622ba7707f0f0b2d0e630852a.png)The red vertex is Alice's starting position, the blue one is Bob's. Bob will make the game run the longest by standing at the vertex 3 during all the game. So here are the moves:

B: stay at vertex 3

A: go to vertex 2

B: stay at vertex 3

A: go to vertex 3

In the second example the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/67357a90193bb980ddc9f6e8d8aabc3f3d4836ca.png)The moves in the optimal strategy are:

B: go to vertex 3

A: go to vertex 2

B: go to vertex 4

A: go to vertex 3

B: stay at vertex 4

A: go to vertex 4

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 2
1 2
2 3
3 4
2 5
```

### 输出

```
6
```

# 题解

## 作者：Dzhao (赞：4)

## [$\color{#66ccff}{\texttt{My\ Blog}}$](https://www.cnblogs.com/qshjydzh/p/12399179.html)
先翻译下本题，个人认为翻译不大准确：

A在根节点1上，B在节点t上，现在B开始走，他要尽可能地躲避A通过走到与其相邻节点上。而A要抓B，故他要尽可能去追B。请问，最多几轮后两人会相遇。

分析这道题，可以发现，B的路径只有两种，分别为：1.一直往上走，直到与A相撞。2.往上走，然后到某一个点拐弯，往下走到底。

## $\texttt{Part\ one}$
我们的小B一直往上走，那么小A也一直往下走，他们会在他们两个点组成的链上相遇，至于在哪个点相遇，我们不管他。理性分析发现这条链上除起始点与终点外的点，除了相遇点外，都走了一遍，相遇点走了两边。那么这之间走的步数就是起始点与重点的**深度差**。
## $\texttt{Part\ two}$
我们的小B经历了一次拐弯，那么我们首先得判断，小B在转弯前，有没有和小A碰到，碰到就不用做了，我们现在考虑未碰到的情况。小B肯定比小A先到底，所以走的步数就是小A到底的距离差的2倍、

讨论结束，我们整理一下我们需要求的东西：

$dep[u]\ u$点的深度 和 $down[u]\ u$点往下走，最远能走到哪。

这两个数组，我们都可以用一遍 DFS 遍历求出来。

$dep[u]=dep[fa]+1,down[u]=\max(down[u],down[v]+1)$

存图就用一个邻接表存就行了，这就不多说了、

$View\ Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() //快读 
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f; 
}
inline int max(int x,int y) {return x>y?x:y;} //手写max，比较快 
const int N=200005;
struct Edge
{
	int ed,nxt;
}a[N<<1]; //邻接表存图 
int tot,h[N],t,n,down[N],dep[N],f[N],ans;
inline void add(int x,int y) //加边 
{
	a[++tot].ed=y;
	a[tot].nxt=h[x];
	h[x]=tot;
} 
void dfs(int u,int fa)
{
	f[u]=fa; //处理出没个点的父亲，方便遍历一条链用 
	dep[u]=dep[fa]+1;
	for(int i=h[u];i;i=a[i].nxt)
	{
		int v=a[i].ed;
		if(v==fa) continue;
		dfs(v,u);
		down[u]=max(down[u],down[v]+1); // 处理该点最多能往下走多少 
	}
}
void solve(int u)
{
	if(!u) return; //到头结束 
	if(dep[t]-dep[u]>=dep[u]-dep[1]) return; //如果在转弯前碰到，结束 
	ans=max(ans,(dep[u]-dep[1]+down[u])*2); //算出在u转弯的值 
	solve(f[u]); //往上遍历 
}

int main()
{
	n=read(),t=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);
	ans=dep[t]-dep[1]; //小B与小A横冲直撞未拐弯情况 
	solve(t);
	printf("%d\n",ans);
	return 0;
}
```
$Thanks\ for\ watching$

---

## 作者：hwx12233 (赞：3)

~~众所周知cf等级是乱划的~~

题意：在限制条件下，到比自己深的点，需要走几步。

限制条件就是从这个点向上到转折点的步数小于这个点的深度。

哇！明显的lca啊

将点按深度排序

然后比较一下目标点
$p$ $dep[p]$与$dep[x]-dep[p]$的大小就好了

特殊情况如果目标点在$x$下面

那就跳过判断

这以后易得操作步数等于最深点$*2$

若搜到比x点浅的点了

那么说明x最优是待在原地

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
typedef long long ll;
#define INF 1e19
#define inf 0x7fffffff

inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}

const int N=500010;
struct E{
	int to,next;
}edge[N<<1];
struct node{
	int dep,id;
}a[N];
int head[N],n,m,s,d[N],fa[N][30],cnt;
inline void add(int u,int v){edge[++cnt].to=v;edge[cnt].next=head[u];head[u]=cnt;}
inline bool cmp(node x,node y){
	return x.dep>y.dep;
}
inline void build(int u,int pre){
	d[u]=d[pre]+1;fa[u][0]=pre;
	a[u].dep=d[u];a[u].id=u;
	for(int i=0;fa[u][i];i++)fa[u][i+1]=fa[fa[u][i]][i];
	for(int i=head[u];i;i=edge[i].next){
		int e=edge[i].to;
		if(e!=pre)build(e,u);
	}
}
inline int LCA(int u,int v){
	if(d[u]>d[v])swap(u,v);
	for(int i=20;i>=0;i--)if(d[u]<=d[v]-(1<<i))v=fa[v][i];
	if(u==v)return u;
	for(int i=20;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v);add(v,u);
	}
	build(1,0);
	sort(a+1,a+1+n,cmp);
	int ans=0;
	for(int i=1;i<=n;i++){
		if(d[a[i].id]<d[m]){cout<<(d[m]-1)*2;break;}
		int p=LCA(a[i].id,m);
		if(p==m){//判断是否在其下 
			cout<<d[a[i].id]*2-2;
			break;
		}
		else {
			if(d[p]-1>d[m]-d[p]){
				cout<<d[a[i].id]*2-2;break;
			}
		}
	}
}
```


---

## 作者：有毒的粽子 (赞：3)

B的行动模式一定是走到一个位置后停下来，A则不断接近B。

问题转换成求一个A比B晚到的最长路。

用dijkstra跑两遍。从1开始和从x开始的。最后遍历判断一下B比A先到。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
const int maxm=2e6+5;
const int inf=0x7fffffff;
int h[maxn],vis[maxn],dis[maxn],dis1[maxn];
int tot,n,x;
struct edge
{
    int u;
    int v;
    int w;
}e[maxm];
struct node
{
    int now;
    int dis;
    bool operator<(const node&a)const
    {
        return dis>a.dis;
    }
};
inline void add(int u,int v,int w)
{
    tot++;
    e[tot].v=v;
    e[tot].w=w;
    e[tot].u=h[u];
    h[u]=tot;
}
inline void dijkstra(int s,int dis[])//dijkstra板子
{
    for(int i=1;i<=n;++i)
    {
        dis[i]=inf;
        vis[i]=0;
    }
    dis[s]=0;
    priority_queue<node> que;
    que.push((node){s,0});
    while(!que.empty())
    {
        node x=que.top();
        que.pop();
        int u=x.now;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=h[u];i;i=e[i].u)
        {
            int v=e[i].v;
            if(dis[v]>dis[u]+e[i].w)
            {
                dis[v]=dis[u]+e[i].w;
                que.push((node){v,dis[v]});
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&x);
    for(int i=1;i<n;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b,1);
        add(b,a,1);//无向图存边
    }
    dijkstra(1,dis);
    dijkstra(x,dis1);//
    int ans=0;
    for(int i=2;i<=n;++i)//注意B不能到根节点
    {
        if(dis[i]>dis1[i])//B的最短路比A的小，满足B先到
        {
            ans=max(ans,dis[i]*2);//结果*2。
        }
    }
    printf("%d\n",ans);
    return 0;
}

```


---

## 作者：FwbAway (赞：2)

感觉这题没有绿啊，黄差不多。

一道典型的树上运动问题，并不需要用到任何树上算法，但也不一定一下就可以想到正解，所以算一道树上运动的中档题。

闲言少叙，CF 继续。

## 题意

在一棵有根树上，A 去抓 B，A 在节点 $1$ 开始运动，B 在节点 $x$ 开始运动。每一回合 A 或 B 均可以选择动或不动，求 A 抓住 B 的最少回合数量。

## 思路

考虑 A 和 B 二人的路程。

假设当前有一节点 $a$（$a\neq1$），A 和 B 均已经过这个节点，那么一定有 $stepA_a>stepB_a$。换句话说，如果 A 和 B 都可以经过一个点，则 A 到这个点的步数一定要比 B 到这个点的步数多。

则有以下代码：

```c++
for (int i = 1; i <= n; i++) if (da[i] > db[i]) ans = max(ans, da[i] * 2);
```

由于 B 到达目标点位一定会静止不动，但仍然计算一个回合，所以直接让 $ans\times2$ 即可。

超短代码：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, x, u, v, da[210000], db[210000], ans;
vector<int> e[210000];
void dfs(int u, int fa, int step, int *d) {
	d[u] = step;
	for (int v : e[u]) if (v != fa) dfs(v, u, step + 1, d);
}
int main() {
	scanf("%d%d", &n, &x);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	dfs(1, -1, 0, da), dfs(x, -1, 0, db);
	for (int i = 1; i <= n; i++) if (da[i] > db[i]) ans = max(ans, da[i] * 2);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Frank08 (赞：2)

## 思路

~~我做法比较无脑，也比较简单~~

用 $f_i$ 表示 $x$ 号点到 $i$ 号点的距离，用 $d_i$ 表示 $1$ 号点到 $i$ 号点的距离。

对于每个 $i(1 \le i \le n)$ 如果 $d_i > f_i$，说明 `B` 可以在不碰到 `A` 的情况下到达点 $i$，若 `B` 一直停留在点 $i$，则此时的答案为 $d_i * 2$。所以只需对每个满足条件的所有点的答案取最大值就可以了。

## 完整代码

```cpp
#include <stdio.h>
#include <vector>
using namespace std;

int n,f[200002],d[200002];
vector <int> edge[200002];

void dfs(int x,int from){
	d[x] = d[from] + 1;
	for(auto y : edge[x])
		if(y != from)
			dfs(y,x);
}

int main(){
	int x; scanf("%d%d",&n,&x);
	for(int i = 1;i < n;i++){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}d[0] = -1;
	dfs(x,0);
	for(int i = 1;i <= n;i++)
		f[i] = d[i];
	dfs(1,0);
	int ans = 0;
	for(int i = 1;i <= n;i++)
		if(f[i] < d[i])
			ans = max(d[i] * 2,ans);
	printf("%d",ans);
} 
```

---

## 作者：DennyQi (赞：2)

其实这道题目没有必要规定根。不规定根答案也是一样的。我们假定其中一个起点是根即可。

考虑x要么直接往下逃，要么往上走一段距离然后往下逃。并且一定不可能走到根。

一旦开始往下逃并且没被抓，就会逃到底。

因此只需要维护每个点的高度和深度，枚举转折点（一定在到根的链上）更新答案即可。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0'||c>'9')) c = getchar();
    if(c == '-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3) + (x<<1) + c - '0', c = getchar();
    return x*w;
}
int n,p,x,y,cur,ans,las,dep[200010],fa[200010],h[200010];
int head[200010],nxt[400010],to[400010],cnt;
inline void add(int u, int v){
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void dfs(int u, int Fa){
	fa[u] = Fa;
	h[u] = 1;
	for(int i = head[u]; i; i = nxt[i]){
		if(to[i] == Fa) continue;
		dep[to[i]] = dep[u] + 1;
		dfs(to[i],u);
		h[u] = max(h[u],h[to[i]]+1);
	}
//	printf("u=%d fa=%d h=%d dep=%d\n",u,fa[u],h[u],dep[u]);
}
int main(){
//	freopen(".in","r",stdin);
	n = read(), p = read();
	for(int i = 1; i < n; ++i){
		x = read(), y = read();
		add(x,y);
		add(y,x);
	}
	dep[1] = 1;
	dfs(1,-1);
	cur = p;
	ans = (dep[p]-1)*2;
	while(cur != -1){
		if(dep[p]-dep[cur] >= dep[cur]-1) break;
//		printf("cur = %d\n",cur);
		for(int i = head[cur]; i; i = nxt[i]){
			if(to[i] == fa[cur]) continue;
			if(to[i] == las) continue;
			ans = max(ans,2*(h[to[i]]+dep[cur]-1));
//			printf(" -> %d    %d\n",to[i],2*(h[to[i]]+dep[cur]-1));
		}
		las = cur;
		cur = fa[cur];
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：极寒神冰 (赞：1)

题意：给你一棵树，n个点, 以1为根

Alice站在1号点，Bob站在x号点，他们依次移动，Bob先移动，每一次移动他们可以选择呆在原地或者移动到相邻的位置上

当他们移动到同一个点的时候游戏结束，Alice想要游戏快点结束，Bob则相反。

直接暴力跑两遍dfs，求出1号点到每个点的距离和x号点到每个点的距离。之后暴力i号点和x号点到某个点的距离。因为alice跑的一定需要比bob远（如果bob跑得远说明在这之前已经被抓到了），所以答案为alice跑的距离*2（在alice没抓到bob前bob可以随便跑。

```
#include<bits/stdc++.h>
using namespace std;
const int N=400020;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,x,ans;
int dep1[N],depx[N];
int cnt,head[N];
struct node
{
	int to,nxt;
}e[N];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline int dfs1(int u,int f)
{
	dep1[u]=dep1[f]+1;//求1号点到每个点距离
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,u);
	}
}
inline int dfs2(int u,int f)
{
	depx[u]=depx[f]+1;//求x号点到每个点距离
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs2(v,u);
	}
}
int main()
{
	init();
	n=read(),x=read();
	for(int i=2;i<=n;i++)
	{
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(x,0);
	for(int i=2;i<=n;i++)
	{
		if(dep1[i]>depx[i])//如果bob跑的比alice说明已经被抓到了
		{
			ans=max((dep1[i]-1)*2,ans);
		}
	}
	cout<<ans;
}
```


---

## 作者：aRenBigFather (赞：1)

这道题目标就是要找到Bob能去到的地图中最深的地方，同时又不和Alice相遇

问题是如何判断不和Alice相遇

因为这里Alice想要回合尽量少，那么她肯定去某一个点是直接去，即Alice到一个点的步数等于那个点的深度

所以只要Bob从X点走到某个极深点的距离小于那个点的深度，那么就可以认为Bob肯定会比Alice先到，只用在那里等Alice来就行了

所以通过LCA(DFS时间复杂度也应该允许)可以求出X点到树上任意一点的距离，然后取符合条件的最深点，观察规律可知，游戏可以进行的次数就是 **最深点的深度*2** 因为Alice想要走到那个点至少要 **最深点的深度*2** 回合。

代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2*100010;
struct edge{
	int v,nxt;
}E[maxn*2];
int p[maxn],eid;
int d[maxn], parent[maxn][30];
void init(){
	memset(p,-1,sizeof p);
	memset(d,-1,sizeof d);
	eid = 0;
}
inline void insert(int u,int v){
	E[eid].v = v;
	E[eid].nxt = p[u];
	p[u] = eid++;
}
inline void insert2(int u,int v){
	insert(u,v);
	insert(v,u);
}
void dfs(int u){
  	for(int i = p[u];i != -1;i = E[i].nxt){
    	if(d[E[i].v] == -1){
    	  d[E[i].v] = d[u] + 1;
    	  parent[E[i].v][0] = u;
    	  dfs(E[i].v);
    	}
  	}
}
int lca(int x,int y){
  int i,j;
  if(d[x] < d[y]){
    swap(x,y);
  }
  for(i = 0;(1 << i) <= d[x];i++);
  i--;
  for(j = i;j >= 0;j--){
    if(d[x]-(1 << j) >= d[y]){
      x = parent[x][j];
    }
  }
  if(x == y){
    return x;
  }
  for(j = i;j >= 0;j--){
    if(parent[x][j] != parent[y][j]){
      x = parent[x][j];
      y = parent[y][j];
    }
  }
  return parent[x][0];
}
int main(){
	int n,x;
	scanf("%d%d",&n,&x);
	init();
	for(int i=1;i<=n-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		insert2(u,v);
	}
	d[1] = 0;
	dfs(1);
  	for(int level = 1;(1 << level) <= n;level++){
  	  	for(int i = 1;i <= n;i++){
  	    	parent[i][level] = parent[parent[i][level-1]][level-1];
  	  	}
  	}
  	int deepP = x,maxd = d[x];
	for(int i=1;i<=n;i++){
		if(d[i] > maxd){
			int lcca = lca(i,x);
			int distx;
			if(lcca == i){
				distx = d[x] - d[i];
			}else if(lcca == x){
				distx = d[i] - d[x];
			}else{
				distx = d[i] - d[lcca] + d[x] - d[lcca];
			}
			//cout << "i:" << i << " distx:" << distx << " d[i] - 1:" << d[i] - 1 <<endl;
			if(distx < d[i]){
				maxd = d[i];
				deepP = i;
			}
		}
	}
	printf("%d",maxd*2);
	//cout << "deepP:" << deepP << "maxd:" << maxd;
	return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

duel 秒掉的简单博弈题。  
令 $h_x$ 为节点 $x$ 子树的最大深度，显然祖先 $h_{fa}>h_{now}$，所以我们考虑最多能跳到哪个祖先。  
令 $dep_x$ 为 $x$ 的深度：  
- 若 $dep_x$ 为奇数，应该跳到 $\frac{dep_x+1}{2}+1$，因为再往上跳刚好会被下一步碰上。
- 若 $dep_x$ 为偶数，应该跳到 $\frac{dep_x}{2}+1$，因为再往上就是 Alice 了。

往上跳的过程可以倍增实现，然后再往子树最深的节点跳就可以了。  
**注意：奇数还有两步，因为 Alice 要去碰到 Bob！**  
代码很简单，缺省源写的比较长：  

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define pb push_back
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int n,m,ans,dep[maxn],h[maxn],f[maxn][21];
vector<int>e[maxn];
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1,f[u][0]=fa;
	for(int i=1;i<=20;i++)f[u][i]=f[f[u][i-1]][i-1];//倍增
	for(int v:e[u])
	{
		if(v==fa)continue;
		dfs(v,u),h[u]=max(h[u],h[v]+1);
	}
	h[u]=max(h[u],1ll);//注意叶节点
}
signed main()
{
	int x,y,t,M;
	n=read(),M=m=read();
	for(int i=1;i<n;i++)x=read(),y=read(),e[x].pb(y),e[y].pb(x);
	dfs(1,0),t=(dep[m]+1)/2+1;//最多跳到的高度
	for(int i=20;i>=0;i--)
		if(dep[f[m][i]]>=t)m=f[m][i];
	write((dep[M]-dep[m]+h[m]+(dep[M]&1))*2);//注意奇数
	return 0;
}
```

---

## 作者：ZSYZSYZSYZSY (赞：0)

# CF813C The Tag Game
[提交记录(CF)：277125867](https://codeforces.com/contest/813/submission/277125867)

## Main Idea
我来翻译一下题面。

给定一棵树，$n$ 个点，编号从 $1$ 到 $n$ ，以 $1$ 号点为根。

Alice 站在 $1$ 号点，Bob 站在 $x$ 号点，他们依次移动，Bob 先移动，每一次移动他们可以选择呆在原地或者移动到相邻的位置上。

当他们移动到同一个点的时候游戏结束，Alice 想要游戏快点结束，Bob 则相反。

写一个程序算出游戏最终会进行几次。

## Solution
我来讲一种比较简单的做法。

先预处理好 $disA_i$ 和 $disB_i$ 分别表示 Alice 从 $1$ 号点到 $i$ 号点的距离和 Bob 从 $x$ 号点到 $i$ 号点的距离。

由于 Alice 想要游戏快点结束，Bob 想要游戏慢点结束，所以对于 $i \in [1, n]$ 满足 $disA_i > disB_i$ ，说明 Bob 可以在不碰到 Alice 的情况下到达点 $i$ ，答案即为 $2 \times disA_i$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e17
inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

ll p, head[500005], nxt[500005], to[500005];
inline void add(ll u, ll v)
{
	nxt[++p] = head[u];
	head[u] = p;
	to[p] = v;
}

ll dis_A[200005];//Alice从1号点到i号点的距离

void dfs(ll u, ll fa)
{
	for(ll i = head[u]; i; i = nxt[i])
	{
		ll v = to[i];
		if(v == fa)
		{
			continue;
		}
		dis_A[v] = dis_A[u] + 1;
		dfs(v, u);
	}
}

ll dis_B[200005];//Bob从x号点到i号点的距离

void dfs1(ll u, ll fa)
{
	for(ll i = head[u]; i; i = nxt[i])
	{
		ll v = to[i];
		if(v == fa)
		{
			continue;
		}
		dis_B[v] = dis_B[u] + 1;
		dfs1(v, u);
	}
}

int main()
{
	ll n = read(), x = read();
	for (ll i = 1; i < n; i++)
	{
		ll u = read(), v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	dfs1(x, 0);
	ll ans = 0LL;
	for(ll i = 1; i <= n; i++)
	{
		if(dis_A[i] >= dis_B[i])
		{
			ans = max(ans, dis_A[i] * 2);
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：ChenZQ (赞：0)

首先有一个很重要的信息，那就是整个图的结构是一颗树。

树的特性不多说了，而这道题我们可以先让 $B$ 往上走直到它再走就会被 $A$ 碰到为止，然后从这个点往下走一条能走的最长路径，疯狂地往下走直到走到底。

下面考虑正确性。

首先，每个点可以有很多个儿子，但是只有一个父亲，如果我们不尽量往上走，可能就会出现并不为最优解的情况，而尽量往上走可以使可选择的路径变多，让答案更有可能更优，即使不会出现更优策略，也不会影响答案，因为直接原路返回就好了。

模拟上述过程，我们就可以得到答案，注意轮数要乘二，因为一个人走一步就算一轮了，所以要乘二。

```
#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
int h[N],e[N],ne[N],idx;
int dst[N],dep[N];
int fath[200010];
int n,x;
void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs(int u,int f)
{
	dep[u]=dep[f]+1;dst[u]=dep[u];
	fath[u]=f;
	for(int i=h[u];i!=-1;i=ne[i])
	{
		if(e[i]!=f) dfs(e[i],u),dst[u]=max(dst[u],dst[e[i]]);
	}
}
int main()
{
	scanf("%d%d",&n,&x);
	memset(h,-1,sizeof h);
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	dfs(1,1);
	int g=1;
	int ans=0;
	while(1)
	{
		if(dep[x]-1>g+1) x=fath[x],g++,ans++;
		else break;
	}
	ans+=dep[x]-g;
	printf("%d",(dst[x]-dep[x]+ans)*2);
}
```

---

## 作者：OtterZ (赞：0)

~~首先说一下，把这道题评紫的人是懂算法的。~~
# 题意
有一棵 $n$ 个点的树，$1$ 号点的老虎 `A` 想吃掉 $x$ 号点的猪 `B`，猪会先动一次，老虎后动一次，每次移动会到相邻的另一个点，问老虎采取最优策略时最晚什么时候吃到猪。
# 首要的结论
老虎 `A` 只用走存在 `B` 的子树即可，因为此时猪没办法跨过子树，且这么走既不走回头路，又能限制猪的走向。
# 其次的结论
猪不停的往上走，直到再往上走就要被吃时再跑到子树中深度最大的点时，其深度显然大于或等于在其他时刻掉头逃跑。猛冲属于作死，因为其比呆在源节点还差。
# 如何得出答案
我们可以先预处理每个点的最大深度，再让猪一步一步往上跳，最后得到的答案是跳到可行的最大值时能到的叶子的最大深度的两倍。  
这里不用用倍增，因为一步一步跳是 $\operatorname{O}(n)$ 的，倍增需要 $\operatorname{O}(n \log n)$ 的预处理，得不偿失。
# 时间复杂度
预处理需要遍历每个点，是 $\operatorname{O}(n)$ 的，一步一步跳最坏情况遍历 $[\frac{n}{2}]$ 个点，也是 $\operatorname{O}(n)$ 的。
# 上代码

```cpp
//先上到不被抓住的最浅祖先，在下到长度最长的叶子节点 
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n,m, dep[200005],mxdep[200005],x;
vector<int>e[200005];
int fa[200005];
void srh(int nk){
	//printf("%d\n",nk);
	mxdep[nk] = dep[nk];
	for(int i = 0; i < e[nk].size(); i ++){
		if(e[nk][i] == fa[nk])
			continue;
		fa[e[nk][i]] = nk;
		dep[e[nk][i]] = dep[nk] + 1;
		srh(e[nk][i]);
		mxdep[nk] = max(mxdep[nk],mxdep[e[nk][i]]);
	}
}
int main(){
	scanf("%d %d",&n,&x);
	for(int i = 1; i < n; i ++){
		int u,v;
		scanf("%d %d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	srh(1);
	int u = 0;
	while(dep[x] - 1 > u + 1){
		//printf("%d\n",x);
		u ++;
		x = fa[x];
	}
	printf("%d\n",mxdep[x] << 1);
	return 0;
}
```


---

