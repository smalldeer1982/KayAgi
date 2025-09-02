# [USACO21JAN] Telephone G

## 题目描述

Farmer John 的 N 头奶牛，编号为 $1…N$，站成一行（$1≤N≤5⋅10^4$）。第 $i$ 头奶牛的品种编号为 $b_i$，范围为 $1\dots K$，其中 $1≤K≤50$。奶牛们需要你帮助求出如何最优地从奶牛 $1$ 传输一条信息到奶牛 $N$。

从奶牛 $i$ 传输信息到奶牛 $j$ 花费时间 $|i-j|$。然而，不是所有品种的奶牛都愿意互相交谈，如一个 $K\times K$ 的方阵 $S$ 所表示，其中如果一头品种 $i$ 的奶牛愿意传输一条信息给一头品种 $j$ 的奶牛，那么 $S_{ij}=1$，否则为 $0$。不保证 $S_{ij}=S_{ji}$，并且如果品种 $i$ 的奶牛之间不愿意互相交流时可以有 $S_{ii}=0$。

请求出传输信息所需的最小时间。

## 说明/提示

最优传输序列为 $1\to 4\to 3\to 5$。总时间为 $|1-4|+|4-3|+|3-5|=6$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤1000$。
 - 测试点 6-13 没有额外限制。

供题：Dhruv Rohatgi

## 样例 #1

### 输入

```
5 4
1 4 2 3 4
1010
0001
0110
0100```

### 输出

```
6```

# 题解

## 作者：vegetable_ste (赞：18)

本题解旨在更清晰地讲解**分层图**算法在此题的应用。

![](https://cdn.luogu.com.cn/upload/image_hosting/s5izapzo.png)
图1
```
4 3
1 2 3 2
101
011
110
```

对于这一组数据，如果     $\operatorname{O}(n^2)$  暴力处理，显然会得到这样的图。

如何对其进行优化？
* * *

观察到  $k$  较小，这种点的种类较少的题，分层图可以作为一个思考方向。

所谓分层，层与层之间维持**有限制条件的联系**，而层内部看作一个**整体**。

- 层内部的处理

观察式子  $|i - j|$  ，不难发现它的实质是一条边权为1的“链”上点  $i$  和点 $j$  之间的距离。因此，可以在层内部以  $(i, i + 1)$  的方式连边。这里连**无向边**，因为一层是一个整体，  $(i,j)$  和  $(j, i)$  的连通性、权值相同。

- 层之间的处理

把一层看作一个整体后，通过层与层之间不同点的关系维持题目当中  $S$  的限制条件。

（第  $k$  层的点  $u$  记作    $\operatorname{get}(u, k)$  ）

考虑第  $1$  ~  $k$  层对于第  $0$  层的意义。第  $b[u]$  层的点  $u$  完全“继承”第  $0$  层的点  $u$  。
我们对第$0$层的点  $u$  和  $\operatorname{get}(u, b[u])$  连一条边权为0的有向边，把 $b[u]$  层的所有点“固定”到点 $u$ 上。

然后，对于满足 $S_{k, b[u]} = 1$ 的所有组合，由  $\operatorname{get}(u, k)$ 向第 $0$ 层点 $u$ 连接**有向**边。

如果经过被“固定”到点 $u$ 的若干点又能从点 $\operatorname{get}(v, b[u])$ 回到第 $0$ 层点 $v$  ，那么就等同于建立了**有向**边  $(u, v)$ 。根据层内连边的规则，不难发现在第 $b[u]$ 层经过的边权之和即为 $|u - v|$ 。

这样，我们便巧妙地转化了 $S$ 所给出的限制条件。

可以借助图2理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/a5k6f8iy.png)
图2

* * *
代码实现上 ，仍然将 $n$ 作为终点，所有非第 $0$ 层点都作为中间“过渡”点。

设置 $\operatorname{get}(u, k) = u + n \times k$ 作为由第 $0$  层的  $u$ 跳转到第 $k$ 层对应点的标志。

> P.S. 当一个图只含有边权为 $0, 1$ 的两种边的时候，可以用双端队列BFS进一步优化掉Dijkstra的一个  $\operatorname{log}$ （不过不用也没什么关系）

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
#define mp make_pair
const int N = 5e4 + 10, M = 52;
int n, k, b[N];
char s[M][M];
vector<PII> e[N * M];
int dist[N * M];
void Add(int x, int y, int w = 0, int f = 0) { e[x].push_back(mp(y, w)); if(f) e[y].push_back(mp(x, w)); }
#define get_l(x, t) ((x) + (t) * n) // 第t层点x的映射
void build() {
	// 1. 1至n层内部连边
	for(int i = 1; i <= k; i ++ )
		for(int j = 1; j <= n - 1; j ++ )
			Add(get_l(j, i), get_l(j + 1, i), 1, 1);
	// 2. 由第0层向其它层等效加边
	for(int i = 1; i <= n; i ++ ) Add(i, get_l(i, b[i]));
	// 3. 由其它层向第0层等效加边
	for(int i = 1; i <= k; i ++ )
		for(int j = 1; j <= n; j ++ )
			if(s[i][b[j]] == '1') Add(get_l(j, i), j);
}
void work() {
	#ifdef debug
	for(int i = 1; i <= get_l(n, k); i ++ ) {
		for_each(e[i].begin(), e[i].end(), [](PII x) -> void { cout << x.first << " "; });
		cout << endl;
	}
	#endif
	memset(dist, 0x3f, sizeof dist);
	deque<int> Q;
	Q.push_back(1); dist[1] = 0;
	while(!Q.empty()) {
		int t = Q.front(); Q.pop_front();
		for(unsigned i = 0; i < e[t].size(); i ++ ) {
			int u = e[t][i].first, w = e[t][i].second;
			if(dist[u] > dist[t] + w) {
				dist[u] = dist[t] + w;
				if(w) Q.push_back(u);
				else Q.push_front(u);
			}
		}
	}
	printf("%d\n", dist[n] > 1e9 ? -1 : dist[n]);
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++ ) scanf("%d", b + i);
	for(int i = 1; i <= k; i ++ )
		scanf("%s", s[i] + 1); // 下标从1开始
	build();
	work();
	return 0;
}
```

---

## 作者：ETHANK (赞：14)

题意：给$N$个点，第$i$个点带颜色$b_i$。和一个关于颜色的邻接矩阵$S$。若$S_{ij}=1$，则所有颜色$i$的点到颜色$j$的点都有一条边。规定$i$号点到$j$号点若有一条边，则边权为$|i-j|$。问图中从$1$到$N$的最短路。

数据范围：$1\le N\le5\times 10^4,1\le K\le 50$。

思路：首先发现如果暴力建图是$O(N^2)$的，显然不行，考虑优化。

发现$K$很小，而且原图中的边权较有特点，考虑优化建图。$i$号点为起点时，它在原图中的边的终点为所有满足$S_{b_ib_j}=1$的$j$，且该边边权为$|i-j|$。

如何优化呢？如果只有一种颜色:
- $S_{11}=1$时，那么原图等价于一条从$1$到$N$的链，也就是对所有$(i,i+1)$有一条边权为$1$的无向边。
- $S_{11}=0$时，原图中没有边，也可以理解为所有颜色$1$的点没有出边。

多个颜色的情况也是类似的，我们可以做分层图。
- 对于每个颜色$c$，可以在第$c$层作出一条链，也就是对于第$c$层内，所有$(i,i+1)$有一条边权为$1$的无向边。
- 对于原图的$i$号点，作它到$b_i$层$i$号点的一条边权为$0$的有向边。
- 如果$S_{b_ic}=1$，作一条从第$c$层的$i$号点到原图$i$号点的有向边，边权为$0$。

这样的分层图一共只有$N(K+1)$个节点，且连出的边数也是$O(NK)$的，可以通过。
后面跑最短路即可，这里用的是bfs。

时间复杂度：$O(NK)$。

代码：
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int N=51005;
int n,k,b[N],dis[50*N];
bool vis[50*N],S[55][55];
int h,t,q[100*N];
inline void update(int u,int v,int w){
    if(dis[v])return;
    if(w==0){
        q[h--]=v;//put 0 in queue's head
        dis[v]=dis[u];
    }else{
        q[++t]=v;
        dis[v]=dis[u]+1;
    }
}
int main(){
    scanf("%d%d",&n,&k);
    rep(i,1,n)scanf("%d",&b[i]);
    rep(i,1,k)rep(j,1,k){
        char c;
        cin>>c;
        S[i][j]=c-'0';
    }
    dis[1]=1;
    h=50*N,t=50*N+1;
    q[t]=1;
    while(h<t){//
        int x=q[++h];
        if(x<=n)update(x,b[x]*n+x,0);//x->(b[x],x)
        else{
            int nx=(x-1)/n,ny=(x-1)%n+1;//找到第几层以及几号点
            if(ny>1)update(x,x-1,1);//(nx,ny)->(nx,ny-1)
            if(ny<n)update(x,x+1,1);//(nx,ny)->(nx,ny+1)
            if(S[nx][b[ny]])update(x,ny,0);//(nx,ny)->ny
        }
    }
    printf("%d\n",dis[n]-1);
    return 0;
}
```



---

## 作者：乘湘去 (赞：7)

## 提供一种不用分层图的做法。~~非常暴力~~

本题可以看出是个裸的最短路问题，对于前五个点的暴力做法，可以直接对于每个位置暴力连边(复杂度为 $O(n^{2})$ )直接跑裸的 Dij 即可。

那么 AC 本题的局限显然就是无法直接连边，那如何解决这个问题呢？那就是:
~~不连边~~

没错，这道题其实不用对于每个点都连上边再跑最短路, ~~直接广搜不香吗？~~。

我们只用保存品种之间能否到达的矩阵就行了，具体来说，对于 Dij 松弛的每一个点,我们枚举出他能通向的所有品种，枚举这些品种所包含的点，进行松弛操作就行了。

那么问题又来了，一个点可以通向的点可是 $O(n)$ 级别的，直接枚举肯定不行。

解决方法很简单，对于一个松弛过的节点，我们就不需要枚举他来再次进行松弛操作了，在枚举过程中，我们把松弛过的点从数组中删除掉就避免了不必要的枚举。

这样在 $O_2$ 的加持下就能~~轻而易举地~~通过本题。

## Code
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 50005
#define M 2000006
#define LL long long 
using namespace std;

char s[55];
int d[N],rad[55][55];// d统计的是1到i的距离，rad表示品种i到j是否可以到达
int v[55][N],tot[55];// v储存每个品种牛的位置，tot[i]表示品种i有几头牛
int n,k,a[N],vis[N];
priority_queue<pair<int,int> >q;

inline int qr()
{
	char a=0;int w=1,x=0;
	while(a<'0'||a>'9'){if(a=='-')w=-1;a=getchar();}
	while(a<='9'&&a>='0'){x=(x<<3)+(x<<1)+(a^48);a=getchar();}
	return x*w;
}

void bfs()//dij式广搜
{
	memset(d,0x3f,sizeof(d));//初始化距离
	d[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		if(x==n) break;
		vis[x]=1;
		for(register int i=1;i<=k;i++)
			if(rad[a[x]][i])                         //如果x所代表的的品种能到品种i
				for(register int j=1;j<=tot[i];j++)  //枚举品种i的所有位置
				{
					int y=v[i][j];
					while(vis[y]&&tot[i]>1)          //如果这个位置被松弛过，那么这个位置就没啥用了直接把这位置删除掉
					{
						swap(v[i][j],v[i][tot[i]]);  //把这个点和最后的点交换，然后删掉
						tot[i]--;
						y=v[i][j];
						if(tot[i]==1) break;
					}
					if(!vis[y]&&(d[y]>d[x]+(y-x>0?y-x:x-y)))//那个鬼畜三目运算是abs函数  ，如果能被松弛的话更新距离，放入堆中
					{
						d[y]=d[x]+(y-x>0?y-x:x-y);
						q.push(make_pair(-d[y],y));
					}
				}
	}
}

int main()
{
	n=qr();
	k=qr();
	for(register int i=1;i<=n;i++)
	{
		a[i]=qr();
		v[a[i]][++tot[a[i]]]=i;    //统计品种i的点的位置
	}
	for(register int i=1;i<=k;i++)
	{
		scanf("%s",(s+1));
		for(register int j=1;j<=k;j++)
			if(s[j]=='1')
				rad[i][j]=1;       //找到能走的品种
	}
	bfs();
	if(d[n]==0x3f3f3f3f)           //如果到不了输出-1
	{
		printf("-1\n");
		return 0;
	}
	printf("%d\n",d[n]);
	return 0;
}
```




---

## 作者：UltiMadow (赞：6)

优化建图

首先可以有一个 $n^2$ 的建图，就是对于每一个点，$\mathcal O(n)$ 去扫描所有点，如果能传信息就连一条边，然后跑最短路

但是显然图的规模太大了不能接受

发现 $k$ 的范围不大，于是可以考虑把 $n$ 个点复制 $n+1$ 层，记为 $0,1,\dots,n$，第 0 层代表原来的点，第 $i$ 层表示品种为 $i$ 的点为 **起点** 所能传递的路径

对于一个点 $u$，记它的品种为 $b_u$，那么从第 0 层的 $u$ 号点连向第 $b_u$ 层的 $u$ 号点，边权为 0，若一个品种 $b_0$ 能传到 $u$，则从第 $b_0$ 层的 $u$ 号点连向第 0 层的 $u$ 号点，边权为 0

一个层内部 $u$ 连向 $u+1$ 边权为 1 的双向边

那么这个图就被优化到了 $nk$ 的规模

然后再这个图上跑最短路即可

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 50010
#define MAXK 55
#define MAXM 2550010
using namespace std;
int	n,K,a[MAXN];
char c[MAXK];
int b[MAXK][MAXK];
struct Node{int to,nxt,val;}Edge[7550010];
int Head[MAXM],cnt_Edge;
void Add_Edge(int u,int v,int w){
	Edge[++cnt_Edge]=(Node){v,Head[u],w};
	Head[u]=cnt_Edge;
}
int inq[MAXM],dis[MAXM];
queue<int>Q;
void spfa(){//考场上偷懒写了个spfa（
	memset(dis,0x3f,sizeof(dis));
	Q.push(1);dis[1]=0;
	while(!Q.empty()){
		int u=Q.front();Q.pop();inq[u]=false;
		for(int i=Head[u];i;i=Edge[i].nxt){
			int v=Edge[i].to,w=Edge[i].val;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v])inq[v]=true,Q.push(v);
			}
		}
	}
}
int get(int x,int y){return n*(x-1)+y;}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=K;i++){
		scanf("%s",c+1);
		for(int j=1;j<=K;j++)b[i][j]=c[j]-'0';
	}
	for(int i=2;i<=K+1;i++)
		for(int j=2;j<=n;j++)
			Add_Edge(get(i,j-1),get(i,j),1),Add_Edge(get(i,j),get(i,j-1),1);//层内边
	for(int i=1;i<=K;i++)
		for(int j=1;j<=n;j++){
			if(b[i][a[j]])
				Add_Edge(get(i+1,j),j,0);
			if(a[j]==i)
				Add_Edge(j,get(i+1,j),0);
		}
	spfa();
	printf("%d\n",dis[n]==0x3f3f3f3f?-1:dis[n]);
	return 0;
}
```

---

## 作者：dingcx (赞：5)

提供一种做法，不需要分层图，甚至不需要建图，跟部分题解的做法有相似之处。个人感觉好写不难想，重点是**快**（点击最优解可以看到我是断崖式最优解）。

## 思路

暴力边数是 $n^2$，发现 $k$ 很小，所以考虑从牛的品种入手。

先考虑同一品种的牛，题目说同品种的也可能不能传递信息。但仔细思考可以发现，除了从牛 $1$ 进行的第一次传递和到牛 $n$ 的最后一次传递，中间都不会发生同品种牛之间的传递。因为先传给同品种的再传给下一个品种的一定不优于直接传给下一个品种的，这个根据绝对值的性质不难理解。

经过这个**贪心**，同品种之间的牛就没什么关系了，接下来只需要考虑品种间的关系，而品种间的传递只需要用到 $k^2$ 的图。

记从牛 $1$ 传递到牛 $i$ 的最短时间是 $dis[i]$，对于图上的每条边 $u \to v$，考虑如何将所有品种 $u$ 的牛的 $dis$ 转移到品种 $v$。暴力转移仍是 $n^2$，这里需要再用一个**贪心**。

![](https://cdn.luogu.com.cn/upload/image_hosting/4oaenk11.png)

考虑可能转移到 $v$ 牛（蓝点）的两个 $u$ 牛（红点），用哪个转移呢？发现应该用靠近 $v$ 牛的 $u$ 牛转移（即左边的红点），因为不管转移到 $u$ 牛的上一个牛（绿点）在什么位置，用靠近蓝点的红点转移都不远于靠远的（可以看 绿$\to$红$\to$蓝 的路径长度）。若红点在蓝点左边，结论也相同。

于是转移到 $v$ 牛的点只可能是其左右最靠近它的两个 $u$ 牛，写个**双指针**，可将转移的复杂度降为 $O(n)$，具体怎么写自己想或看后面代码。

跑图我直接用 **bfs** 跑了，毕竟点只有 $50$。

总时间复杂度理论上是 $O(nk^2)$，但看时间又感觉是 $O(nk)$，总之不带 $\log$ 而且很快。空间也只有 $O(n+k^2)$。

## 实现细节

首先是刚刚遗留的如何处理 $1$ 和 $n$ 号牛在同品种间传递的问题。我的做法是先特判它们是同一个品种并且能交流，此时直接输出 $n-1$；否则把它们单开一个品种，连的边和原品种相同。

然后是 bfs 防止死循环，加一个只有当存在一个 $v$ 牛的 $dis$ 改变才把 $v$ 加进队列里即可。

## 代码

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
const int MAXN=5e4+10;
int n,m,a[MAXN],G[55][55],dis[MAXN];
vector<int> b[55]; //每个品种的牛的编号
int read(){
	int num=0,sign=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	return num*sign;
}
queue<int> q;
void bfs(){
	for(int i=2;i<=n;i++) dis[i]=1e9;
	q.push(m+1);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v=1;v<=m+2;v++){
			if(!G[u][v]) continue;
			bool fl=0; //判是否有dis改变
			for(int i=0,j=0;i<b[u].size()&&j<b[v].size();){ //双指针转移
				if(dis[b[u][i]]+abs(b[u][i]-b[v][j])<dis[b[v][j]])
					dis[b[v][j]]=dis[b[u][i]]+abs(b[u][i]-b[v][j]),fl=1;
				if(i==b[u].size()-1||b[u][i]>b[v][j]) j++;
				else i++;
			}
			if(fl) q.push(v);
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<n;i++) b[a[i]].push_back(i);
	b[m+1].push_back(1),b[m+2].push_back(n);
	for(int i=1;i<=m;i++) for(int j=1;j<=m;j++) scanf("%1d",&G[i][j]);
	if(a[1]==a[n]&&G[a[1]][a[n]]){printf("%d\n",n-1);return 0;} //特判
	for(int i=1;i<=m;i++) if(G[a[1]][i]) G[m+1][i]=1; //边与原品种相同
	for(int i=1;i<=m;i++) if(G[i][a[n]]) G[i][m+2]=1;
	a[1]=m+1,a[2]=m+2;
	bfs();
	printf("%d\n",dis[n]==1e9?-1:dis[n]);
	return 0; //华丽结束
}
```

---

## 作者：MolotovM (赞：5)


**题意：**
给定n个点，每个点被分配k种颜色其中一种，任意两点$i,j$距离定义为$|i-j|$，每种颜色的点向某些特定颜色的点连边（给定k*k个关系），求1到n的路径最小距离

颜色数量不多于20，n不多于5e4

**题解：**
这题应该是整场最easy的

看k的数据范围和求最短路就知道要建立**分层图**

还是比较明显的

我们按照以下步骤建图：

1.将每个点拆成k+1个点，k个点对应k个颜色，1个是本身

2.将k*n个点中每相同颜色的n个点相连，共连k层，双向边，边权为1

3.将每个点连接当前点颜色可到达的颜色对应的当前点拆出来的点，也将可到达当前点颜色的颜色对应的当前点拆出来的点连接当前点，边权均为0，单向边

最后跑从1到n的最短路即可
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int Read(){
  	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 60 * (5e4 + 50);
int n,k;
int a[MAXN],s[55][55];
int d[MAXN];
bool vis[MAXN];
priority_queue<pair<int,int> >Q;
int head[MAXN],to[MAXN << 1],nxt[MAXN << 1],val[MAXN << 1],tot;
void add(int x,int y,int v){
	to[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
	val[tot] = v;
}
int id(int i,int j){
	return i * n + j;
}
void Dijkstra(int s){
	memset(d,127,sizeof(d));
	Q.push(make_pair(0,s));
	d[s] = 0;
	while(!Q.empty()){
		int u = Q.top().second;
		Q.pop();	
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u] ; i ; i = nxt[i]){
			int v = to[i];
			if(d[v] > d[u] + val[i]){
				d[v] = d[u] + val[i];
				Q.push(make_pair(-d[v],v));
			}
		}
 	}
}
int main(){
	n = Read() , k = Read();
	for(int i = 1 ; i <= n ; i ++) a[i] = Read();
	for(int i = 1 ; i <= k ; i ++){
		for(int j = 1 ;  j <= k ; j ++){
			char ch = getchar();
			while(ch != '0' && ch != '1') ch = getchar();
			s[i][j] = ch - '0';
		}
	}
	for(int i = 1 ; i <= k ; i ++){
		for(int j = 1 ; j + 1 <= n ; j ++){
			add(id(i,j),id(i,j + 1),1);
			add(id(i,j + 1),id(i,j),1);
		}
	}
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= k ; j ++){
			if(s[a[i]][j]) add(i,id(j,i),0);
		}
		add(id(a[i],i),i,0);
	}
	Dijkstra(1);
	if(d[n] < 0x7f7f7f7f) printf("%d\n",d[n]);
	else printf("-1\n");
	return 0;
}
```

---

## 作者：NDFS (赞：3)

提供一种不用分层图的做法。

首先模拟可以发现，这题难度在于如何优化建边。直接把所有可能传递的边都建出来跑最短路边的数量会特别多，很显然这其中会有许多无用边。

通过观察可以发现：对于每个点，每个奶牛种类只要连到左边离这个点最近的这种奶牛，右边离这个点最近的这种奶牛，这些就是有用的边；以及判断能否传递到最后一个奶牛，不然可能连不到最后。这样建出来的边最多是 $2NK$ 条。

具体来说，可以设 $pre_{i,j}$ 表示左边离第 $i$ 个点最近的第 $j$ 种奶牛，设 $nxt_{i,j}$ 表示右边离第 $i$ 个点最近的第 $j$ 种奶牛，可以在 $O(NK)$ 的时间内预处理出 $pre$ 和 $nxt$，再特判一下 $N$ 能不能传递，跑单源最短路径即可，我写了 SPFA。

总的时间复杂度 $O(k(2NK)+NK)$。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,k,a[50005],v[50005],d[50005];
char b[55][55];
int h[50005],ne[5000005],to[5000005],w[5000005],tot=0;
int pre[50005][55],nxt[50005][55];
queue<int>q;
int abs(int x)
{
	if(x<0)return -x;
	return x;
}
void add(int a,int b)
{
	to[++tot]=b;
	w[tot]=abs(a-b);
	ne[tot]=h[a];
	h[a]=tot;
}
void spfa(int s)
{
	for(int i=1;i<=n;i++)v[i]=0,d[i]=1e9;
	v[s]=1,d[s]=0;
	int x,y;
	q.push(s);
	while(!q.empty())
	{
		x=q.front(),q.pop();
		v[x]=0;
		for(int i=h[x];i;i=ne[i])
		{
			y=to[i];
			if(d[x]+w[i]<d[y])
			{
				d[y]=d[x]+w[i];
				if(!v[y])v[y]=1,q.push(y);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=k;i++)scanf("%s",b[i]+1);
	//预处理
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)pre[i][j]=pre[i-1][j];
		pre[i][a[i-1]]=i-1;
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=k;j++)nxt[i][j]=nxt[i+1][j];
		nxt[i][a[i+1]]=i+1;
	}
	//建边
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(b[a[i]][j]-'0'&&pre[i][j])add(i,pre[i][j]);
			if(b[a[i]][j]-'0'&&nxt[i][j])add(i,nxt[i][j]);
			if(b[a[i]][a[n]]-'0')add(i,n);
		}
	}
	//最短路
	spfa(1);
	if(d[n]!=1e9)printf("%d",d[n]);
	else printf("-1");
	return 0;
}
```

---

## 作者：2021sunzishan (赞：2)

一道很难，也很好的分层图最短路题。
## 题目大意：
给定 $n$ 个点，每个点都有自己的颜色。每个颜色之间可能愿意传输信息，也可能不愿意传输信息。相同颜色 之间也有可能不愿意传输信息。若点 $i$ 愿意传输信息给j，则传输的代价为 $\left|i-j\right|$。问从 $1$ 号点到 $n$ 点店传输信息的最小代价。

## 思路：

如果暴力加边，那么就是 $n^2$ 的时间复杂度，肯定超时，考虑分层图。

本题用分层图需要构建 $k+1$ 层图。

何为 $k+1$ 层呢？就是每个颜色都建一层，再加上一层转折层。

每一层上都是 $n$ 个点，一层上的点相邻的连一条边权为 $1$ 的边（转折层除外），这样就处理好了代价为 $\left|i-j\right|$ 这个问题。

那么问题来了，转折层是干什么的的呢？

因为有些颜色之间可以传输信息，如果将这 $k$ 层之间能交流的点都连上边，时间复杂度怕是承受不住了。

那么我们就巧妙地运用转折层。转折层上也有 $n$ 个点，如果一个点 $i$ 可以与颜色 $j$ 连边，那么就将此点与转折层上所有颜色为 $i$ 的点连一条边权为 $0$ 的边，然后将转折层上的所有点向其他 $k$ 层上的对应点都连一条权值为 $0$ 的边。这样，从一个颜色到另一个颜色，只要经过转折层问题就解决了！

最后，跑一遍最短路就好啦！

如果还是不懂，那就看代码吧！

**切勿抄袭！！！**

## 代码 ：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int n,k,a[10000005];
char c[10000005];
int s[505][505];
struct node {//链式前向星
	int to,next,w;
} edge[10000005];
int head[10000005],cnt;
void addedge(int u,int v,int w) {
	edge[++cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
	edge[cnt].w=w;
}
int vis[10000005],dis[10000005];
queue<int>q;//SPFA模板
void bfs() {
	memset(dis,0x3f,sizeof(dis));
	q.push(1);
	dis[1]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u]; i; i=edge[i].next) {
			int v=edge[i].to；
			if(dis[v]>dis[u]+edge[i].w) {
				dis[v]=dis[u]+edge[i].w;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int ls(int x,int y) {//求点的编号，x为在第几层，y为在第x层的第y个
	return (x-1)*n+y;
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),k=read();//读入
	for(int i=1; i<=n; i++)a[i]=read();
	for(int i=1; i<=k; i++)
		for(int j=1; j<=k; j++) {
			char c;
			cin>>c;
			s[i][j]=c-'0';
		}
	for(int i=2; i<=k+1; i++)//从2到k+1，第一层为转折层
		for(int j=2; j<=n; j++) {
			addedge(ls(i,j-1),ls(i,j),1);//层内之间连边，边权为1
			addedge(ls(i,j),ls(i,j-1),1);//注意是双向边
		}
	for(int i=1; i<=k; i++)
		for(int j=1; j<=n; j++) {
			if(s[i][a[j]])//如果可以到达
				addedge(ls(i+1,j),ls(1,j),0);//和转折层连边
			if(a[j]==i)//把第i层的对应点连上
				addedge(ls(1,j),ls(i+1,j),0);
		}
	bfs();
	if(dis[n]==0x3f3f3f3f)//最后输出，大功告成
		printf("-1");
	else
		printf("%d",dis[n]);
	return 0;
}
```

完结~

---

## 作者：Aleph_Drawer (赞：2)

这里提供一种**不用建图**的方法。

### 基本思路

我们可以考虑设 $\large f_{i}$ 表示从 $1$ 到 $i$ 传话的最小代价，则很容易我们得知如下方程
$$
f_{i} = \min (f_j + |i - j|)
$$
其中 $1 \leq j \leq n$ 且满足 $\large s_{b_i,j} = 1$。

这个DP是会有后效性的，但是我们可以考虑用**队列**，每一次记录要转移的 $i$ 和对应的 $f_i$，由于 $|i - j| \geq 0$，所以我们可以将多余的、重复的、不会更优的状态减掉。

这样做，复杂度是 $O (n^2)$ 的，空间时间随便一个都炸了。

----------------

### 优化！

我们考虑减掉一些多余的状态，首先我们假设 $u$ 在 $b$ 序列中如图下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/w9tkbygy.png)

我们假设有两个点 $n1, n2$ 可以从 $u$ 转移过来，这里我们设 $n1 < n2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/28xgi4gl.png)

倘若我们假设一个目标点 $p$ 是我们接下来要从 $n1, n2$ 转移来的点（均可转移）：

![](https://cdn.luogu.com.cn/upload/image_hosting/beke05g4.png)

如果 $p \geq n2$，那么转移代价就会是一样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/9z74nmof.png)

如果 $p \leq n2$，那么从 $n1$ 转移到 $p$ 代价会比从 $n2$ 更优：

![](https://cdn.luogu.com.cn/upload/image_hosting/7rcv9tc3.png)

如果 $n1, n2 \leq u$ 也是同理的。

所以我们发现，**如果存在两个相同的可转移的点位于 $u$ 的一侧，那么离  $u$ 更远的一定不会更优**。

所以我们现在只需要记录当前这个点的每一种颜色的**与这种颜色相同且最近的左右两个点**的位置和距离，然后转移一下就好了。设这两个点为 $pre, nxt$，则：

$$
f_{i} = \min (f_{pre} + |i - pre|, f_{nxt} + |i - nxt|)
$$

注意每种品种都需要一次转移，按照上面的队列转移即可，时间复杂度 $O (nk)$。

### 特别判断

看下面这个样例，假设 $1$ 可以转移到 $2$ 而 $2$ 不可以转移到其他任何东西。

对于 `1 2 2` 这个样例，按照上面的方法，我们会发现只会从 $1$ 转移到第一个 $2$，所以我们需要特判：如果当前这个点 $i$ 可以一步到达终点，那么我们就直接考虑 $f_n = \min (f_n, f_i + |n - i|)$ 特判一下即可。

### 参考code （没有注释，谨慎观看）

```cpp
/* Author : Luogu @Alpha_Drawer */
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

ll head = 1, tail = 0, q [500101], val [500101];
ll next [50101][51], dist [50101][51];
ll pre [50101][51], pr_dist [50101][51];
ll least [501001];
ll n, k;
ll b [501001];
ll s [511][511];

int main () {
	scanf ("%lld%lld", &n, &k);
	for (ll i = 1; i <= n; i++)
		scanf ("%lld", &b [i]), least [i] = 1e18;
	for (ll i = 1; i <= k; i++) {
		ll j = 1;
		char str = getchar ();
		while (str < 32 || str > 126) str = getchar ();
		while (str >= 32 && str <= 126) {
			s [i][j ++] = str - '0';
			str = getchar ();
		}
	}
	
	for (ll i = n - 1; i >= 1; i--)
		for (ll j = 1; j <= k; j++) {
			if (b [i + 1] == j) next [i][j] = i + 1, dist [i][j] = 1;
			else next [i][j] = next [i + 1][j], dist [i][j] = dist [i + 1][j] + 1; 
		} 
	
	for (ll i = 2; i <= n; i++)
		for (ll j = 1; j <= k; j++) {
			if (b [i - 1] == j) pre [i][j] = i - 1, pr_dist [i][j] = 1;
			else pre [i][j] = pre [i - 1][j], pr_dist [i][j] = pr_dist [i - 1][j] + 1;
		}
	
	q [++ tail] = 1;
	val [tail] = 0;
	least [1] = 0;
	while (head <= tail) {
		ll u = q [head], value = val [head ++];
		if (s [b [u]][b [n]]) least [n] = min (least [n], value + n - u);
		for (ll i = 1; i <= k; i++) {
			if ((!s [b [u]][i]) || (!next [u][i])) continue;
			if (value + dist [u][i] >= least [next [u][i]]) continue;
			q [++ tail] = next [u][i];
			val [tail] = value + dist [u][i];
			least [next [u][i]] = min (val [tail], least [next [u][i]]);
		}
		for (ll i = 1; i <= k; i++) {
			if ((!s [b [u]][i]) || (!pre [u][i])) continue;
			if (value + pr_dist [u][i] >= least [pre [u][i]]) continue;
			q [++ tail] = pre [u][i];
			val [tail] = value + pr_dist [u][i];
			least [pre [u][i]] = min (val [tail], least [pre [u][i]]);
		}
	}
	if (least [n] == 1e18) {
		printf ("-1");
		return 0;
	}
	printf ("%lld", least [n]);
	return 0;
}
```


---

## 作者：约瑟夫用脑玩 (赞：2)

提供一种不用分层图的**正确**做法并给出了证明。（虽然我已经会分层图的做法了）

开始并没有看懂分层图，直到看到了一篇做法清晰明了又好懂，就是没有证明。（主要是估计他也不会/不想证。。。）

众所周知，暴力建边要 $O(n^2)$，于是直接想办法建 $O(nK)$ 的边。

先给出结论，对于每个点只用对于每种颜色连前驱和后继，再补上每个点直接到 $n$ 的边。

显然只有 $O(nK)$ 条边，至于找点随便用个指针带着走也不至于有 $\log$。

------------

证明：

考虑由一个点 $i$ 颜色为 $c_i$ 走到另一种颜色为 $c_j$ 的点 $j$ 上，不妨设 $i<j$。

如果有最近的一个点 $k$ 满足 $c_k=c_j$ 在他中间，即 $i<k<j$，在当前建图下显然就走不到 $j$ 而只能到 $k$ 了。

但是如果我们接下来希望从 $j$ 走到另一个点 $x$，那么一定有 $S_{c_j,c_x}=S_{c_k,c_x}=1$。

首先一定有 $x>j$，因为显然当 $x\le j$ 时走 $j$ 一定没有 $k$ 优。

继续考虑 $x$ 与 $k$ 中间最近的点 $y,c_y=c_x,k<y<x$ 也是如此，这样走就必须一直向右走直到某个颜色。

直到你不找下一个点了，那么就得直接跳到 $n$。

这样只走后继显然也是能一直往右找到那个颜色的，这里的长度均为 $n-i$。

或者你不走其他点 $j$ 而直接走最近的后继 $k$ 的情况在图中已经表示出来了，跑最短路肯定就能跑到。

那么 $j<k<i$ 的情况也类似，我们肯定往左走到某个点 $p$ 直接转移到 $n$，但我们在新图上走，同理分析一定能找到同样颜色的点 $q\ge p$，那么 $|p-i|+|n-p|\ge |q-i|+|n-q|$，一定不劣。

否则就是直接走最近的前驱也加边表示出来了。

故可以代替原图来找最短路。

------------

对一个边数 $O(nK)$ 点数却只有 $O(n)$ 的图跑最短路，可以随手用个最简单的基数堆优化到 $O(nK+n\log)$ 的复杂度，时间复杂度并不劣。

---

## 作者：pocafup (赞：2)

似乎跟目前所有题解的思路都不太一样（？）没有用到分层图

这是个憨憨题目啊，为啥我赛时就是搞不出来啊/kk，搞出来就过了啊

首先朴素的 $O(n^2)$ 建图不讲，这里讲讲优化。

发现这题有个核心难点，就是同样品种的牛可能不相通，于是考虑去掉这个条件怎么做

发现如果同样品种牛保证相通，那么我们只需要将每个点跟其他颜色的最近的两个点找出来，然后在同色之间同样以最近的节点建图跑dij即可。

正确性证明：如果同色的点相通，那么假设当前节点更新了较近的 A 色点，那么我们可以使用这个 A 色点去更新较远的 A 色点，然后用后面的节点更新再远一点的A色点。

![](https://cdn.luogu.com.cn/upload/image_hosting/qxf1qiwq.png)

现在考虑去掉这个特殊条件，发现会出现这样一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/md96jkfb.png)

即同色不互通，但 B 色点仍然能更新所有 A 色点。

观察到如果一个点更新的方向不变，那么他可以被用来更新同色点。

因此，我们可以考虑在转移时记录方向。如果上一个被更新 A 色点的节点在其左边，那么 A 色点可以被用于更新他右边的节点，否则他可以被用来更新他左边的节点。

于是，我们建图时异色点只对最近的两个节点建边，同色点建立双向边。建边同时需要保留方向。

至此，本题的更新可以被总结为三个部分：

- 更新异色点：直接更新即可
- 更新同色点且同色相通：更新节点，且将两种方向都加入队列
- 更新同色点但同色不相通：如果当前方向跟来的方向一致，那么更新节点

时间复杂度 $O(nklog(nk))$

代码：（截取重要部分，需要完整代码私信）

```cpp
const int MAXN = 5e4+5;
const int MAXM = 1e6+5;
const int MAXK = 55;
const int mod = 1e9+7;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int n,m,t,l,k,a,b,c,pos[MAXN],al[MAXK][MAXK],dist[MAXN],ans;
vector<int> adj[MAXN];
namespace AdjEdge{
  //var
  int head[MAXN],tot;
  struct Edge{
    int u,v,d,nxt,tp;
  }edge[MAXM<<1];
  inline void add(int u, int v, int d,int tp){
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].d = d;
    edge[tot].nxt = head[u];
    edge[tot].tp = tp;
    head[u] = tot;
  }
}
using namespace AdjEdge;
inline int bsl(int u, int v){
  int l = 0, r = adj[v].size()-1;
  while(l!=r){
    int mid = (l+r+1)>>1;
    if (adj[v][mid]<=u) l = mid;
    else r = mid-1;
  }
  return adj[v][l]<=u ? adj[v][l] : -1;
}//查找左边最近的节点
inline int bsr(int u, int v){
  int l = 0, r = adj[v].size()-1;
  while(l!=r){
    int mid = (l+r)>>1;
    if (adj[v][mid]>=u) r = mid;
    else l = mid+1;
  }
  return adj[v][l]>=u ? adj[v][l] : -1;
}//查找右边最近的节点
struct Node{
  int u,tp,d;
  bool operator < (const Node &oth) const{
    return d>oth.d;
  }
};
inline void dij(int src){
  mem(dist,0x3f3f);
  dist[src] = 0;
  pq<Node> q; q.push((Node){src,2,0});
  while(!q.empty()){
    int u = q.top().u, t = q.top().tp;q.pop();
    trav(i,u){
      int v = edge[i].v, d = edge[i].d,tp = edge[i].tp;
      //type 1 : different breed
      if (pos[u]!=pos[v]){
        if (dist[v]>dist[u]+d){
          dist[v] = dist[u]+d;
          q.push((Node){v,tp,dist[v]});
        }
      }
      //type 2 : same breed, can go
      if (pos[u]==pos[v] && al[pos[u]][pos[v]]){
        if (dist[v]>dist[u]+d){
          dist[v] = dist[u]+d;
          q.push((Node){v,0,dist[v]});
          q.push((Node){v,1,dist[v]});
        }
      }
      //type 3: same breed, cannot go
      if (pos[u]==pos[v] && !al[pos[u]][pos[v]]){
        if (t==tp && dist[v]>dist[u]+d){
          dist[v] = dist[u]+d;
          q.push((Node){v,tp,dist[v]});
        }
      }
    }
  }
  writeln(dist[n] > 1e9 ? -1 : dist[n]);
}
signed main(){
  n = read(); k = read();
  For(i,1,n) pos[i] = read(),adj[pos[i]].pb(i);
  For(i,1,k) For(j,1,k) al[i][j] = get()-'0';
  For(i,1,n){
    For(j,1,k){
      if (!adj[j].size() || pos[i]==j || !al[pos[i]][j]) continue;
      int l = bsl(i,j), r = bsr(i,j);
      if (l!=-1) add(i,l,i-l,0);//如果左边有节点,就建边
      if (r!=-1) add(i,r,r-i,1);//如果右边有节点,就建边
    }
  }
  For(i,1,k){
    if (adj[i].size()<=1) continue;
    For(j,0,adj[i].size()-2){
      add(adj[i][j],adj[i][j+1],adj[i][j+1]-adj[i][j],1);
      add(adj[i][j+1],adj[i][j],adj[i][j+1]-adj[i][j],0);
      //同色左右各自相连即可
    }
  }
  dij(1);
}
```

---

## 作者：kradcigam (赞：1)

一种新的方法，做法类似于 w33z 的毒瘤题[团](https://www.luogu.com.cn/problem/P7100)，大家可以类比着看一下。

[团](https://www.luogu.com.cn/problem/P7100)这道题启示我们什么？对于 $n$ 个点向 $m$ 个点分别连边，我们可以引入中介来讲 $nm$ 条边变成 $n+m$ 条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/yie1aenl.png)

相似的道理，首先考虑如果 $S_{i,i}$ 保证为 $1$ 怎么做？我们可以将同一个种类的所有相邻两头奶牛的连边。每一个奶牛对于一种颜色，就只需要跟左边最近的和右边最近的连边就可以了（当然如果左边或右边没有这个种类的奶牛就自然不用了）。

我们回过来再考虑$S_{i,i}$ 可能为 $0$，也就是说不能再同种类的相邻的两头奶牛建边了。我们给每个点建一个虚点，虚点向这个点连边，我们就可以在同一个种类的所有相邻两头奶牛的虚点连边，每一个奶牛对于一种颜色，就只需要跟左边最近的和右边最近的虚点连边就可以了（当然如果左边或右边没有这个种类的奶牛就自然不用了）。

相比于分层图的解法，代码有些难写：

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define eb emplace_back
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=1e5+10;
int b[N],cnt,lst[55][N],f[N];
bool h[55][55];
vector<pair<int,int> >v[N];
queue<int>q;
int main(){
	int n=read(),k=read();
	F(i,1,n){
		b[i]=read();
		v[i+n].eb(i,0);
		if(lst[b[i]][0]){
			v[i+n].eb(lst[b[i]][lst[b[i]][0]]+n,i-lst[b[i]][lst[b[i]][0]]);
			v[lst[b[i]][lst[b[i]][0]]+n].eb(i+n,i-lst[b[i]][lst[b[i]][0]]);
		}lst[b[i]][++lst[b[i]][0]]=i;
	}
	F(i,1,k)
		F(j,1,k){
			char ch=getchar();
			for(;ch!='0'&&ch!='1';ch=getchar());
			h[i][j]=(ch=='1');
		}
	F(i,1,n)
		F(j,1,k)
			if(h[b[i]][j]){
				if(!lst[j][0])continue;
				if(lst[j][1]<=i){
					int x=upper_bound(lst[j]+1,lst[j]+lst[j][0]+1,i)-lst[j]-1;
					v[i].eb(lst[j][x]+n,i-lst[j][x]);
				}
				if(lst[j][lst[j][0]]>i){
					int x=upper_bound(lst[j]+1,lst[j]+lst[j][0]+1,i)-lst[j];
					v[i].eb(lst[j][x]+n,lst[j][x]-i);
				}
			}
	ms(f,0x3f);f[1]=0;
	q.push(1);
	while(q.size()){
		int x=q.front();q.pop();
		for(auto[fi,se]:v[x]){
			if(f[x]+se<f[fi]){
				f[fi]=f[x]+se;
				q.push(fi);
			}
		}
	}
	if(f[n]==f[0])puts("-1");
	else cout<<f[n];
	return 0;
}
```





---

