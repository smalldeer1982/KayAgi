# [CEOI 2002] Royal guards

## 题目描述

从前有一个王国，这个王国的城堡是 $m$ 行 $n$ 列的一个矩形，被分为 $m \times n$ 个方格。一些方格是墙，而另一些是空地。这个王国的国王在城堡里设了一些陷阱，每个陷阱占据一块空地。

一天，国王决定在城堡里布置守卫，他希望安排尽量多的守卫。

守卫们都是经过严格训练的，所以一旦他们发现同行或同列中有人的话，他们立即向那人射击。因此，国王希望能够合理地布置守卫，使他们互相之间不能看见，这样他们就不可能互相射击了。守卫们只能被布置在空地上，不能被布置在陷阱或墙上，且一块空地只能布置一个守卫。如果两个守卫在同一行或同一列，并且他们之间没有墙的话，他们就能互相看见。(守卫就像象棋里的车一样)

你的任务是写一个程序，根据给定的城堡，计算最多可布置多少个守卫，并设计出布置的方案。


## 说明/提示

#### 样例输入输出 1 解释

如图（黑色方格为墙，白色方格为空地，圆圈为陷阱，G表示守卫）

![](https://cdn.luogu.com.cn/upload/image_hosting/zv6sr9xw.png)

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq m, n \leq 200$，$0 \leq a_{i, j} \leq 2$。

## 样例 #1

### 输入

```
3 4
2 0 0 0
2 2 2 1
0 1 0 2
```

### 输出

```
2
1 2
3 3
```

# 题解

## 作者：Rhodoks (赞：20)

&emsp;&emsp;来一篇带注释的题解（手动滑稽）。

&emsp;&emsp;称每一段朝上的墙为横墙，每一段朝左的墙为竖墙。那么每一个侍卫都对应唯一一段横墙和竖墙，而两个侍卫不互相攻击的条件就是这两段墙所对的空地上没有其他侍卫。将每一格空地对应的横墙和竖墙连一条边，问题就转化成了二分图最大匹配问题。

![](https://cdn.luogu.com.cn/upload/pic/45909.png)
 
&emsp;&emsp;图中诸如“横/竖 xy”代表位于空格（x，y）下/右方的横/竖墙。

&emsp;&emsp;建立网络流模型求解二分图最大匹配，超源连所有横墙，横墙通过空格连对应竖墙，竖墙连超汇，权值均为1。

&emsp;&emsp;放张图瞧瞧（图中“点xy“类型的节点在建图中是没有的，这里只是方便理解加上来）。

![](https://cdn.luogu.com.cn/upload/pic/45910.png)

&emsp;&emsp;顺便说一句，https://csacademy.com/app/graph_editor/ 这玩意画图真好用。
 
&emsp;&emsp;建图时，对于二维平面内的墙，我们可以把坐标映射到一维上，由于N,M<=200，所以我们令z=(x-1)*200+y，横墙（x,y）对应结点为p，竖墙（x,y）对应结点为p+40000，令超级源点为0，超级汇点为80001，跑最大流即可。

&emsp;&emsp;上代码咯，~~有注释的代码~~。

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream> 
#include <queue>
#define MAXM 100100
#define MAXN 202
#define MAXN2 202*202
using namespace std;

const int INF=2147483647;

int wall[MAXN][MAXN][2]; //记录空格对应的横墙和竖墙 
int castle[MAXN][MAXN]; //城堡地形图 
int n,m,s,t; //n：x方向长度  m：y方向长度 这里注意，和题目给的是反过来的  s和t为超源超汇 
int maxflow=0;
int idbegin;  //从这个编号开始的边全部是连接竖墙和横墙的边 

struct EDGE
{
	int from,to,weight,next;
}edge[MAXM<<1]; //链式前向星存图 

int head[MAXN2<<1];
int deep[MAXN2<<1];
int cnt=0;

inline void add(int x,int y,int w)
{
	edge[cnt].from=x;
	edge[cnt].to=y;
	edge[cnt].weight=w;
	edge[cnt].next=head[x];
	head[x]=cnt++;
}

inline int convert(int x,int y)  //把二维的坐标映射到一维 
{
	return (x-1)*200+y;
}

void input()
{
	for (int i=0;i<=MAXN2<<1;i++)
		head[i]=-1;
	s=0;
	t=80001;
	cin>>n>>m;
	
	
	for (int i=0;i<=n+1;i++)
	{
		castle[i][0]=2; 
		castle[i][m+1]=2; 
	}
	for (int i=1;i<=m+1;i++)
	{
		castle[0][i]=2; 
		castle[n+1][i]=2; 
	} //这里把城堡用墙先围上一圈 
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&castle[i][j]); //读入 

	int poswall;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (castle[i][j]!=2)
			{
				poswall=convert(i,j);
				if (castle[i+1][j]==2) //如果（i,j)下方有堵墙 
				{
					add(s,poswall,1);
					add(poswall,s,0); //从超源往这堵墙连边 
					for (int k=i;castle[k][j]!=2;k--) //往上走，记录在wall数组里 
						wall[k][j][0]=poswall;
				}
				if (castle[i][j+1]==2) //如果（i,j)右方有堵墙
				{
					add(poswall+40000,t,1); //竖墙是要加上40000的 
					add(t,poswall+40000,0);
					int poswall=convert(i,j);
					for (int k=j;castle[i][k]!=2;k--)
						wall[i][k][1]=poswall;
				}
			}
	idbegin=cnt; //记录此时的cnt，最终寻找有流边的时候从这里开始找就行了 
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (castle[i][j]==0) //如果遇到空地，从对应横墙往对应竖墙连边 
			{
				add(wall[i][j][0],wall[i][j][1]+40000,1);
				add(wall[i][j][1]+40000,wall[i][j][0],0);
			}
}

bool bfs() //dinic算法的bfs部分，求出每个点的deep ，如果到不达汇点说明已经满流 
{
	int cur;
	queue <int> q;
	for (int i=0;i<=80001;i++)
		deep[i]=-1;
	deep[s]=0;
	q.push(s);
	while (!q.empty())
	{
		cur=q.front();
		q.pop();
		for (int i=head[cur];~i;i=edge[i].next)
			if (!~deep[edge[i].to] && edge[i].weight)
			{
				deep[edge[i].to]=deep[cur]+1;
				q.push(edge[i].to);
			}
	}
	if (~deep[t])
		return true;
	else
		return false;
}

int dfs(int cur,int limit) //dinic的dfs部分，寻找可行流
{
	if (!limit || cur==t)
		return limit;
		
	int flow=0;
	int f;
	
	for (int i=head[cur];~i;i=edge[i].next)
	{
		if (deep[edge[i].to]==deep[cur]+1 && (f=dfs(edge[i].to,min(limit,edge[i].weight))))
		{
			flow+=f;
			limit-=f;
			edge[i].weight-=f;
			edge[i^1].weight+=f;
			if (!limit) break;
		}
	}
	if (!flow) deep[cur]=-1;
	return flow;
}

int dinic() //能看到这题应该dinic已经掌握了，不再赘述，如不然请先A了模板题 
{
	while (bfs())
		maxflow+=dfs(s,INF);
	return maxflow;
}

int main()
{
	input();
	dinic();
	cout<<maxflow<<endl;
	for (int i=idbegin;i<cnt;i+=2) //扫描所有正向边 
		if (edge[i].weight==0) //如果有流通过，输出对应竖墙的x坐标和横墙的y坐标 
			cout<<(edge[i].to-40000-1)/200+1<<' '<<(edge[i].from-1)%200+1<<endl; //反过来映射的时候要小心 
	return 0;
}

```

---

## 作者：辰星凌 (赞：15)

# **【题解】宫廷守卫 [P1263]**

[广告](https://www.cnblogs.com/Xing-Ling/p/11631854.html)

**传送门：[宫廷守卫 $[P1263]$](https://www.luogu.org/problem/P1263)**


## **【题目描述】**

给出一个 $n*m$ 的方格图，分别用整数 $0,1,2$ 表示空地、陷阱、墙，空地上可以放置守卫，如果两个守卫在同一行或同一列且他们之间没有墙的阻挡，那么他们就会互相看见。求最多可以放置多少个守卫使得他们互相无法看见对方，并输出其中一种方案。

-------

## **【分析】**

如果没有墙的限制，那就是一个果的二分图套路题（[車的放置](https://www.acwing.com/problem/content/375/)），将每一行看作左点，每一列看作右点，对于没有陷阱的点（空地），将其所在行与其所在列连边，跑一遍二分图最大匹配即可。

墙的存在使得每一行、每一列都分裂成了若干部分，且每一部分都是独立存在、互不干涉的，因此可以把每一部分都视作一个点，例如样例：

**第三列** 被 **墙**$(2,3)$ 分为了上下两个部分，上面是否放守卫与下面能否放守卫没有任何关联，同理下面也如此。

剩余部分与 **車的放置** 相同。

## **【Code】**

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#define Re register int
using namespace std;
const int N=203,M=80003;
struct QAQ{int to,next;}a[M<<1];
int n,m,o,n1,n2,ans,pan[N*N*2],head[N*N*2],match[N*N*2],A[N][N],idh[N][N],idz[N][N];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int dfs(Re x){//匈牙利算法
    for(Re i=head[x],to;i;i=a[i].next)
    	if(!pan[to=a[i].to]){
            pan[to]=1;
            if(!match[to]||dfs(match[to])){
            	match[to]=x;return 1;
            }
    	}
    return 0;
}
int main(){
    // 	freopen("guard.in","r",stdin);
    //	freopen("guard.out","w",stdout);
    in(n),in(m);
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m;++j)
            in(A[i][j]);
    for(Re i=1;i<=n;++i)A[i][0]=2;//预处理边界
    for(Re i=1;i<=m;++i)A[0][i]=2;
    for(Re i=1;i<=n;++i)//处理每一行
    	for(Re j=1;j<=m;++j)
            if(A[i][j]<2)//不是墙，需要建点
            	if(A[i][j-1]>1)idh[i][j]=++n1;//前面是墙，新开一部分
            	else idh[i][j]=idh[i][j-1];//前面不是墙，与其算作一个部分
    for(Re j=1;j<=m;++j)//处理每一列
    	for(Re i=1;i<=n;++i)
            if(A[i][j]<2)//不是墙，需要建点
            	if(A[i-1][j]>1)idz[i][j]=++n2;//前面是墙，新开一部分
            	else idz[i][j]=idz[i-1][j];//前面不是墙，与其算作一个部分
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m;++j)
            if(!A[i][j])add(idh[i][j],idz[i][j]);//没有陷阱就连边
    for(Re i=1;i<=n1;++i){//跑二分图最大匹配
    	for(Re j=1;j<=n2;++j)pan[j]=0;
    	ans+=dfs(i);
    }
    printf("%d\n",ans);
    for(Re i=1;i<=n;++i)//输出答案利用子匈牙利算法的特性
    	for(Re j=1;j<=m;++j)//match数组记录了所有的匹配边
            if(!A[i][j]&&idh[i][j]==match[idz[i][j]])printf("%d %d\n",i,j);
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```



---

## 作者：waaadreamer (赞：8)

这道题乍一看似乎没有下手点，只能用万能算法（爆搜），再仔细想一想，其实最值一般就那几个方法，dp显然不行，贪心似乎也不行（数据量太小），二分呢？不好检查，于是试试网络最大流。

有点类似一道网络流的基本题——同行同列不能出现两个人，这道题不过是多了两个限制——墙和陷阱。其实也很好处理，对于每一行，可以按照墙进行分段，一段对应一个点，对于列也分段处理。

对于每个空地，想它所在的行段和列段连容量为1的边，S向行段连容量为1的边，列段向T连容量为1的边，算出来的最大流就是最多可以放多少个人，最后看看哪些边被使用过就行了。

话说似乎复杂度很悬，结果Dinic算法飞快的AC了，最慢的店才43ms。。。不明白怎么才这么少的人AC。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 40005, maxm = 160005;
struct Edge{int to, cap, next;} edge[maxm];
int mp[205][205], head[maxn], tot, n, m;
inline void addedge(int u, int v, int w){
    edge[tot].to = v;
    edge[tot].cap = w;
    edge[tot].next = head[u];
    head[u] = tot++;
    edge[tot].to = u;
    edge[tot].cap = 0;
    edge[tot].next = head[v];
    head[v] = tot++;
}
int que[maxn], level[maxn], id[maxn];
void bfs(int s){
    int he = 0, ta = 0;
    memset(level, -1, sizeof(level));
    level[que[ta++] = s] = 0;
    while(he < ta){
        int u = que[he++];
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > 0 && level[v] < 0){
                level[v] = level[u] + 1;
                que[ta++] = v;
            }
        }
    }
}
int dfs(int u, int t, int f){
    if(u == t) return f;
    int flow = 0, k;
    for(int &i = id[u]; ~i; i = edge[i].next){
        int v = edge[i].to, c = edge[i].cap;
        if(c > 0 && level[v] > level[u] && 
            (k = dfs(v, t, min(f, c))) > 0){
            f -= k; flow += k;
            edge[i].cap -= k;
            edge[i ^ 1].cap += k;
            if(f == 0) return flow;
        }
    }
    return flow;
}
int max_flow(int s, int t){
    int flow = 0, f;
    while(true){
        bfs(s);
        if(level[t] < 0) return flow;
        memcpy(id, head, sizeof(id));
        while((f = dfs(s, t, 0x7fffffff)) > 0) flow += f;
    }
}
int row[205][205], col[205][205], x[maxm], y[maxm];
int main(){
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) scanf("%d", &mp[i][j]);
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m;){
            int k = j;
            for(; k < m && mp[i][k] != 2; k++);
            for(int l = j; l < k; l++) if(mp[i][l] == 0)
                row[i][l] = cnt;
            if(j < k) cnt++;
            j = k + 1;
        }
    }
    int cnt1 = cnt;
    for(int i = 0, j = 0; i < m; i++){
        for(int j = 0; j < n;){
            int k = j;
            for(; k < n && mp[k][i] != 2; k++);
            for(int l = j; l < k; l++) if(mp[l][i] == 0)
                col[l][i] = cnt;
            if(j < k) cnt++;
            j = k + 1;
        }
    }
    int s = cnt, t = cnt + 1;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
        x[tot] = i + 1; y[tot] = j + 1;
        addedge(row[i][j], col[i][j], 1);
    }
    for(int i = 0; i < cnt1; i++) addedge(s, i, 1);
    for(int i = cnt1; i < cnt; i++) addedge(i, t, 1);
    printf("%d\n", max_flow(s, t));
    for(int i = 0; i < tot; i++) if(edge[i].cap == 0) {
        if(x[i] > 0) printf("%d %d\n", x[i], y[i]);
    }
    return 0;
}
```

---

## 作者：梧桐灯 (赞：4)

这里给出另一种不同于网络流的做法——匈牙利算法，简单好记，对于二分图匹配同样适用。

形象的说，匈牙利算法大致如下：（也可以百度搜索，[这个帮人找妹子的例子不错](https://blog.csdn.net/sunny_hun/article/details/80627351)）

还有适合我的，就把占掉。

适合我的都被占了，就去抢别人的。

别人再重复上述操作。

如果我的被抢了找不到其他适合的，就拒绝你。

我是个文明人（~~确定~~），如果抢被拒绝了再去抢别人的。

抢了一圈没抢到，只好嘤嘤嘤（对答案没有贡献）

说着复杂，其实这只是一个递归的过程。

至于建图，其他dalao都说的很清楚了，这里就只简单提一下：

对于每一个空地，将其下面第一堵墙和右边第一堵墙建边即可（假设图外围为了一圈墙）。

然后化坐标为一维的点就行。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#define MP make_pair
using namespace std;

const int N = 203;
int n, m, a[N][N];
vector <int> c[N * N];
int d[N * N], ans;
bool vis[N * N];
pair <int, int> l[N];

inline int zh (const int x, const int y) {return (x - 1) * (m + 1) + y;} //化二维为一维，这个就随喜好写了
inline void add (const int x, const int y) {c[x].push_back (y); return ;}
inline pair <int, int> work (const int t) {
	int x = (t - 1) / (m + 1) + 1;
	int y = t - (x - 1) * (m + 1);
	return MP (x, y);
} //化一维为二维

bool Find (int x) { //每次Find就是抢别人的操作
	int i, y, k = c[x].size ();
	for (i = 0; i < k; ++i) {
		y = c[x][i];
		if (!vis[y]) {//如果该节点这一轮没有被访问过
			vis[y] = 1;   //标记被访问
			if (!d[y] || Find (d[y])) { //d数组表示该节点被谁占据了，0表示还没有被占据；如果被占据且我把这个抢走，别人还能占到其他的
				d[y] = x; //那这个就是我的了
				return 1;
			}
		}
	}
	return 0;
}

int main () {
	scanf ("%d %d", &n, &m);
	int i, j, x, y; for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) scanf ("%d", &a[i][j]);
	for (i = 0; i <= n + 1; ++i) a[i][0] = a[i][m + 1] = 2;
	for (i = 0; i <= m + 1; ++i) a[0][i] = a[n + 1][i] = 2;
	for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
		if (a[i][j]) continue; //对于每一个空地找墙建图
		y = j + 1; while (a[i][y] != 2) ++y;
		x = i + 1; while (a[x][j] != 2) ++x;
		add (zh (i, y), zh (x, j));
	}
	for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
		if (a[i][j + 1] == 2) {
			memset (vis, 0, sizeof (vis));
			if (Find (zh (i, j + 1))) ++ans; //如果我找到节点占据，ans++
		}
	}
	printf ("%d\n", ans);
	int t;
	for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
		t = zh (i + 1, j);
		if (d[t]) printf ("%d %d\n", work (d[t]).first, j); //该节点被占据，就输出这两个节点对应的坐标
	}
	return 0;
}
```


---

## 作者：yuruilin2026 (赞：3)

$upd:2025/2/3$：因内容有误而更正，并修改了可能产生歧义的表述。\
声明：本题解改自本人的另一篇题解：\
[题解：AT_abc274_g [ABC274G] Security Camera 3](https://www.luogu.com.cn/article/0tmkvxrr)。\
~~欢迎各位大佬切掉这道双倍经验题~~。

---

本题解默认已经熟练掌握了匈牙利算法。\
若没有熟练掌握，请移步 [P3386](https://www.luogu.com.cn/problem/P3386)。
1. 题意：\
   在地图内放守卫，只能在空地上放。\
   除非有墙的阻隔，否则不能再同一行列中放守卫。\
   求最多的守卫数量。
2. 思路：\
   放了一个守卫之后，他所在的那一行和那一列都不能再次被使用。\
   可以理解为一行和一列对应匹配。\
   将行列匹配，若交点可以放置守卫，则在行列之间建边。\
   匹配的话，用行列分别作为二分图的左部点和右部点，跑一遍匈牙利求最大匹配就行了。
3. 图论建模：\
   建边的时候怎么办呢？
   
   如果没有障碍，那么只需将行看作是二分图的一边，列看作另一边，然后可以放置守卫的地方的行向列连边即可。

   本来一行只能放一个守卫，但障碍的出现导致一行被隔开，所以在有障碍的情况下，可以把一行看成多行。
   
   列同理，在有障碍的情况下，把一列看成多列连边。

4. 输出方案：\
   二分图匹配时，用了 $match_i$ 来存储 $i$ 的匹配对象，现在就是它发挥作用的时候了。

   具体实现见代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char ch[1145][1145];
bool vis[1145][1145];
string str;
int g[114514],match[114514],re[114514],n,m,sum,next1[114514],head[114514],cnt;
int tot1,tot2;
struct ppp{
	int d,x,y;
}a1[114514],a2[114514];
void add(int u,int p){ //链式前向星 
	++cnt;
	next1[cnt] = head[u],g[cnt] = p,head[u] = cnt;
}
bool dfs(int x){
	for(register int i = head[x];i;i = next1[i]){//枚举右部点
		if(re[g[i]] == 0){//有边并且没被匹配 
			re[g[i]] = 1;//匹配上 
			if(match[g[i]] == 0){//match[i]存储的是匹配的人 
				match[g[i]] = x;
				return 1;
			}
			else if(dfs(match[g[i]])){
				match[g[i]] = x;
				return 1;
			}
		}
	}
	return 0;
}
inline void init(){//初始化
	for(register int i = 0;i <= m*n+2;++i) re[i] = 0;
}
void init2(){//初始化*2
	memset(vis,0,sizeof(vis));
	memset(g,0,sizeof(g));
	memset(match,0,sizeof(match));
	memset(re,0,sizeof(re));
	memset(next1,0,sizeof(next1));
	memset(head,0,sizeof(head));
	cnt = 0,tot1 = 0,tot2 = 0,sum = 0,n = 0,m = 0;
	for(register int i = 0;i <= 1513;++i){
		a1[i] = ppp{0,0,0};
		a2[i] = ppp{0,0,0};
	}
	for(register int i = 0;i <= 164;++i){
		for(register int j = 0;j <= 164;++j){
			ch[i][j] = ' ';
		}
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	init2();
	cin >> n >> m;
	for(register int i = 1;i <= n;i++){
		for(register int j = 1;j <= m;j++){
			cin >> ch[i][j];
		}
	}
	for(register int i = 1;i <= n;i++){
		for(register int j = 1;j <= m;j++){
			if(vis[i][j]) continue;
			if(ch[i][j] != '0') continue;
			int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
			while(xx11 > 1 && ch[xx11-1][j] != '2'){
				xx11--;//区间上端点 
			}
			while(xx22 < n && ch[xx22+1][j] != '2'){
				xx22++;//区间下端点 
			}
			for(register int k = xx11;k <= xx22;k++){
				vis[k][j] = 1;
			}
			a1[++tot1] = ppp{j,xx11,xx22};
		}
	}
	memset(vis,0,sizeof(vis));
	for(register int i = 1;i <= n;i++){
		for(register int j = 1;j <= m;j++){
			if(vis[i][j]) continue;
			if(ch[i][j] != '0') continue;
			int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
			while(yy11 > 1 && ch[i][yy11-1] != '2'){
				yy11--;//区间左端点 
			}
			while(yy22 < m && ch[i][yy22+1] != '2'){
				yy22++;//区间右端点 
			}
			for(register int k = yy11;k <= yy22;k++){
				vis[i][k] = 1;
			}
			a2[++tot2] = ppp{i,yy11,yy22};
		}
	}
	for(register int i = 1;i <= tot1;i++){
		for(register int j = 1;j <= tot2;j++){
			if(a1[i].x <= a2[j].d && a1[i].y >= a2[j].d){
				if(a2[j].x <= a1[i].d && a2[j].y >= a1[i].d){
					if(ch[a2[j].d][a1[i].d] == '1') continue;//交点是陷阱不能建边
					add(i,j);
				}
			}
		}
	}
	for(register int i = 1;i <= tot1;i++){
		init();
		if(dfs(i)) sum++;
	}
	cout << sum << endl;
	for(register int i = 1;i <= tot2;i++){
		if(match[i] == 0) continue;
		//a2[i].d 存储的是分割后的行在之前的行数
		//a1[i].d 存储的是分割后的列在之前的列数
		//match[i]存储的是分割后的第i行匹配的列 
		cout << a2[i].d << " " << a1[match[i]].d << endl;
	}
	
	return 0;
}
```

---

## 作者：Dispwnl (赞：3)

[博客](https://a-failure.github.io/2018/04/14/%E5%AE%AB%E5%BB%B7%E5%AE%88%E5%8D%AB/)

跟[这道题](https://www.luogu.org/problemnew/show/P2825)思路一样

把每行、每列连续的一段缩成一个点并编号

然后可以选的位置行和列的编号相连，跑个最大流就行了

至于输出方案，把编号和行列对应一下就行了

代码：
```
# include<iostream>
# include<cstdio>
# include<cstring>
# include<queue>
using namespace std;
const int MAX=401,inf=1e8,MAXX=(MAX*MAX<<1)+1,t=MAX*MAX<<1;
struct p{
    int x,y,dis;
}c[MAXX<<1];
int n,m,tot,num,TOT;
int h[MAXX],d[MAXX],id[MAXX],id2[MAXX];
int colr[MAX][MAX],colc[MAX][MAX],a[MAX][MAX];
bool use[MAXX];
void add(int x,int y,int dis)
{
    c[num]=(p){h[y],x,0};
    h[y]=num++;
    c[num]=(p){h[x],y,dis};
    h[x]=num++;
}
bool bfs()
{
    queue<int> qu;
    qu.push(0);
    memset(d,0,sizeof(d));
    d[0]=1;
    while(!qu.empty())
    {
        int tt=qu.front();
        qu.pop();
        for(int i=h[tt];i;i=c[i].x)
          if(!d[c[i].y]&&c[i].dis)
          {
          	d[c[i].y]=d[tt]+1;
          	qu.push(c[i].y);
          }
    }
    return d[t];
}
int dfs(int x,int dix)
{
    if(!dix||x==t) return dix;
    int sum=0;
    for(int i=h[x];i;i=c[i].x)
      if(d[c[i].y]==d[x]+1&&c[i].dis)
      {
      	int dis=dfs(c[i].y,min(dix,c[i].dis));
      	if(dis)
      	{
      		dix-=dis;
      		sum+=dis;
      		c[i].dis-=dis;
      		c[i^1].dis+=dis;
      		if(!dix) break;
        }
      }
    if(!sum) d[x]=-1;
    return sum;
}
int dinic()
{
    int tot=0;
    while(bfs()) tot+=dfs(0,inf);
    return tot;
}
int read()
{
	int x=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);x=x*10+ch-48,ch=getchar());
	return x;
}
void work()
{
	for(int i=1;i<=tot;++i)
	  for(int j=h[i];j;j=c[j].x)
	    if(c[j^1].dis&&c[j].y)
	    printf("%d %d\n",id[i],id2[c[j].y-tot]);
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        a[i][j]=read();
    for(int i=1;i<=n;i++)
      {
      	id[++tot]=i;
      	for(int j=1;j<=m;j++)
      	  {
      	  	if(a[i][j]==2) ++tot;
      	  	else colr[i][j]=tot;
      	  	id[tot]=i;
		  }
      }
    for(int i=1;i<=m;i++)
      {
      	id2[++TOT]=i;
      	for(int j=1;j<=n;j++)
      	  {
      	  	if(a[j][i]==2) ++TOT;
      	  	else colc[j][i]=TOT+tot;
      	  	id2[TOT]=i;
		  }
      }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        if(!a[i][j])
        {
        	if(!use[colr[i][j]])
        	{
        		add(0,colr[i][j],1);
        		use[colr[i][j]]=1;
            }
            if(!use[colc[i][j]])
            {
                add(colc[i][j],t,1);
                use[colc[i][j]]=1;
            }
        	add(colr[i][j],colc[i][j],1);
        }
    printf("%d\n",dinic());
    work();
    return 0;
}
```


---

## 作者：Victorique (赞：3)

楼下代码貌似不是十分美观。

其实说实话，这道题难道不是一看就是网络流么。。这么经典的模型。同行同列只能有一个人，并且有墙的限制。。。然而如果没有墙的限制貌似O（1）出解。。而如果有墙又几乎搜不出来。。

把每一横纵以“2”拆成很多个串，然后把每个串当成一个点，然后使用二分图匹配抑或是网络流来实现他们之间的异或关系。连边什么的楼下已经说过了，那么说一下网络流问题里一直恶心的输出方案，这个题还比较好，由于我们从每一行的点只有连向列的和源点的，所以我们把边打上标记，表示它是从x，y点连出来的，然后暴力枚举所有行的点即可。

不是一道难题。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define inf 5000001
#define re register
#define ll long long 
using namespace std;
struct po{
	int to,nxt,w,x,y;
};
po edge[500001];
int head[20001],dep[20001],cur[20001],a[1001],b[50001],id,num=-1,nm,s,t,n,m;
int line[201][201],row[201][201],map[201][201];
struct print{
	int x,y;
};
print out[20001];
inline int read()
{
    int x=0,c=1;
    char ch=' ';
    while((ch>'9'||ch<'0')&&ch!='-')ch=getchar();
    while(ch=='-')c*=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
    return x*c;
}
inline void add_edge(int from,int to,int w,int x,int y)
{
	edge[++num].nxt=head[from];
	edge[num].to=to;
	edge[num].w=w;
	edge[num].x=x;
	edge[num].y=y;
	head[from]=num;
}
inline void add(int from,int to,int w,int x,int y)
{
	add_edge(from,to,w,x,y);
	add_edge(to,from,0,x,y);
}
inline bool bfs()
{
	memset(dep,0,sizeof(dep));
	queue<int> q;
	while(!q.empty())
	q.pop();
	dep[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(re int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].w>0&&!dep[v]){
				dep[v]=dep[u]+1;
				if(v==t) return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
inline int dfs(int u,int low)
{
	if(u==t) return low;
	int diss=0;
	for(re int& i=cur[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(edge[i].w&&dep[v]==dep[u]+1){
			int check=dfs(v,min(low,edge[i].w));
			if(check){
				low-=check;
				diss+=check;
				edge[i].w-=check;
				edge[i^1].w+=check;
				if(low==0) break;
			}
		}
	}
	return diss;
}
inline int dinic()
{
	int ans=0;
	while(bfs()){
		for(re int i=s;i<=t;i++)
		cur[i]=head[i];
		while(int d=dfs(s,inf))
		ans+=d;
	}
	return ans;
}
inline bool cmp(print p,print q){
	if(p.x<q.x) return 1;
	else if(p.x==q.x&&p.y<q.y) return 1;
	return 0;
}
int main()
{
	memset(head,-1,sizeof(head));
	n=read();m=read();
	for(re int i=1;i<=n;i++)
	 for(re int j=1;j<=m;j++)
	 map[i][j]=read();
	for(re int i=1;i<=n;i++)
	 for(re int j=1;j<=m;j++){
	 	if(map[i][j]==2) continue;
	 	if(j==1||map[i][j-1]==2) id++;
	 	line[i][j]=id;
	 }
	 int tt=id;
	for(re int i=1;i<=m;i++)
	 for(re int j=1;j<=n;j++){
	 	if(map[j][i]==2) continue;
	 	if(j==1||map[j-1][i]==2) id++;
	 	row[j][i]=id; 
	}
	for(re int i=1;i<=n;i++)
	 for(re int j=1;j<=m;j++)
	 if(map[i][j]==0)
	 add(line[i][j],row[i][j],1,i,j);
	s=0;t=id+1;
	for(re int i=1;i<=tt;i++)
	add(s,i,1,0,0);
	for(re int i=tt+1;i<=id;i++)
	add(i,t,1,0,0);
	cout<<dinic()<<endl;
	for(re int i=1;i<=n;i++)
	 for(re int j=1;j<=m;j++){
	 	int u=line[i][j];
	 	if(u&&!b[u]){
	 		for(re int i=head[u];i!=-1;i=edge[i].nxt){
	 			if(edge[i^1].w!=0&&edge[i].to!=s)
	 			out[++nm].x=edge[i].x,out[nm].y=edge[i].y;
			 }
			 b[u]=1;
		 }
	 }
	sort(out+1,out+1+nm,cmp);
	for(re int i=1;i<=nm;i++)
	cout<<out[i].x<<" "<<out[i].y<<endl;
}
```

---

## 作者：rq_kyz (赞：2)

# 【题解】宫廷守卫

## 传送门
[P1263 [CEOI2002] Royal guards](https://www.luogu.com.cn/problem/P1263)

## 题意

现在有一个 $m \times n$ 大小的方格图，上面分别有 $0$、$1$、$2$ 三种数字，现在要在上面选一些格子放守卫，每个格子放一个守卫，$0$ 可以选，$1$ 和 $2$ 不能选，并且每两个守卫之间不能是同一行或同一列，除非中间有数字 $2$ 把它们隔开，不然他们就会互相攻击。现在问你最多可以放多少个守卫，并把守卫的坐标打印出来。

## 分析

我们把题目精简一下（虽然上面的题目是作者已经经过精简的），一个方格图上有 $0$、$1$、$2$ 三种数字，$0$ 可以选，不能阻挡；$1$ 不能选和阻挡；$2$ 不能选，可阻挡。问最多可选多少个格子。

既然同一行或同一列中没有 $2$ 阻挡的两个格子不能同时选，我们只需要通过行和 $2$ 将这些格子分为不同个部分，再通过列和 $2$ 将这些格子分为不同个部分，每个部分就是一个节点，格子有重叠的两个节点之间连边，这样建完之后就是一个二分图，再在上面跑[二分图最大匹配（增广路算法）](https://oi-wiki.org/graph/graph-matching/bigraph-match/)，整道题就解决了。

我们再把思路理一下，首先我们从行的方向将方格图分隔，具体如下（白色为空地，绿色为陷阱，黑色为墙）：

![行](https://x.imgs.ovh/x/2023/09/08/64fb2374a126a.bmp)

然后，我们再按列将它分隔：

![列](https://x.imgs.ovh/x/2023/09/08/64fb23bd94c16.bmp)

分隔完成之后，我们把每一个可以选的格子将它按行所在的结点和按列所在的结点连接起来，构成一张二分图（两个行和两个列之间不可能建边）。

![二分图](https://x.imgs.ovh/x/2023/09/08/64fb24ba2b24b.bmp)

这样构建的二分图它的每一个结点代表从行或列上分隔的一部分，而每条边表示一个可以选择的格子，换句话说有几个为 $0$ 的格子就有几条边。

最后的最后，我们只需要通过这个图跑一遍最大匹配就行了。

## 本蒟蒻的 AC 代码（蒟蒻有点懒，注释不是很多）

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll last[40001];
struct s{
	ll t,to,x,y;
}nxet[40001];
ll cd=0;
void lj(ll x,ll y,ll i,ll j){
	nxet[++cd].t=last[x];
	nxet[cd].to=y;
	nxet[cd].x=i;//连边的时候也要记录这条边所指的那个格子的坐标，因为最后要输出
	nxet[cd].y=j;
	last[x]=cd;
}
bool vis[40001];
ll dis[40001];
ll zb[40001][2];
bool dfs(ll u){
	for(ll j=last[u];j;j=nxet[j].t){
		ll v=nxet[j].to;
		if(vis[v])
			continue;
		vis[v]=1;
		if(!dis[v] || dfs(dis[v])){
			dis[v]=u;
			zb[v][0]=nxet[j].x;//记录坐标
			zb[v][1]=nxet[j].y;
			return 1;
		}
	}
	return 0;
}
ll a[201][201];
ll t[201][201][2];
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);//这里是作者的习惯，将m和n的含义调换了
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	ll cd0=0;
	for(ll i=1;i<=n;i++){//行向建点
		ll j=1;
		while(1){
			while(j<=m && a[i][j]==2)
				j++;
			if(j>m)
				break;
			cd0++;
			while(j<=m && a[i][j]<2)
				t[i][j++][0]=cd0;
		}
	}
	ll cd1=cd0;
	for(ll j=1;j<=m;j++){//列向建点
		ll i=1;
		while(1){
			while(i<=n && a[i][j]==2)
				i++;
			if(i>n)
				break;
			cd1++;
			while(i<=n && a[i][j]<2)
				t[i++][j][1]=cd1;
		}
	}
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			if(!a[i][j])//遍历可以放的格子，并连边
				lj(t[i][j][0],t[i][j][1],i,j);
	ll sum=0;
	for(ll i=1;i<=cd0;i++){//跑最大匹配
		memset(vis,0,sizeof(vis));
		if(dfs(i))
			sum++;
	}
	printf("%lld",sum);
	for(ll i=cd0+1;i<=cd1;i++)
		if(dis[i])
			printf("\n%lld %lld",zb[i][0],zb[i][1]);
    return 0;
}
```

---

## 作者：C_Pos_Princess (赞：1)

# 题解：P1263 [CEOI2002] Royal guards

（码风最好的题解，没有之一）

难在建图，最后储存。



**最小点覆盖的板子**



每个连通的一行/列 ， 用一个数字表示 ， 把数字连起来，则每条边上的两个点只能选一个。



即： 从一个图中选出最多的点，使得选出的点之间没有边。

注意代码储存每个 $cnt$ 表示的 行 和 列 的位置。



**代码奉上**

```
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
int n, m;
int mp1[N][N], mp2[N][N];
int cnt1, cnt2;
int ch[N][N];
int e[N * N], ne[N * N], h[N * N], cnt;
void add(int a, int b) {
	e[++cnt] = b;
	ne[cnt] = h[a];
	h[a] = cnt;
}

int match[N * N];
int st[N * N];
int lie[N * N], hang[N * N];

bool mat(int u) {
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (!st[j]) {
			st[j] = 1;
			if (!match[j] || mat(match[j])) {
				match[j] = u;
				return true;
			}
		}
	}
	return false;
}


int main() {
	scanf("%d%d", &n, &m);

	memset(h, -1, sizeof h);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &ch[i][j]);


	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (ch[i][j] == 2) continue;
			if ((j == 1) || (ch[i][j - 1] == 2)) cnt1++;
			mp1[i][j] = cnt1;
			hang[cnt1] = i;
		}

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			if (ch[j][i] == 2) continue;
			if ( (j == 1) || (ch[j - 1][i] == 2)) cnt2++;
			mp2[j][i] = cnt2;
			if (ch[j][i] == 0) add(mp1[j][i], mp2[j][i]);
			lie[cnt2] = i;
		}

	int ans = 0;
	for (int i = 1; i <= cnt1; i++) {
		memset(st, 0, sizeof st);
		if (mat(i))  ans ++;
	}
	printf("%d\n", ans);
	for (int i = 1; i <= cnt2; i++)
		if (match[i])
			printf("%d %d\n", hang[match[i]], lie[i]);


	return 0;
}
```

**三倍经验**

P1263

P6062

P2825

---

## 作者：toolong114514 (赞：1)

# P1263 [CEOI2002] Royal guards 题解
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/P1263)
## 解题思路
一道二分图最大匹配的经典题。

记中间没有墙分隔，而且连续的一个同行极长段为**连续行**。

记中间没有墙分隔，而且连续的一个同列极长段为**连续列**。

可以在 $O(nm)$ 的时间复杂度内预处理上述信息。


我们将所有连续行和连续列抽象成若干个点，考虑每一个空地，将其所在的连续行向连序列连边。

容易发现，这是一个二分图，左部为连续行的点，右部为连续列的点。

我们还发现，两个守卫如果能互相看见，他们一定身处同行或同列，之间无墙阻挡，即**同处于一个连续行或连序列**。

在建出的图上，这表现为左部有两个点连向了右部一个相同的点。

又因为这种情况是不合法的，所以合法的情况就是它的否命题，即**二分图上每个左部的点连向的右部点（如果存在）互不相同**。这是典型的**二分图匹配**。

我们要求如上的合法方案中，匹配数最多的方案，输出匹配数和方案（有 SPJ，所以输出任意的就行）。

那么问题就转化为了**二分图最大匹配**。

不会的可以先学[模板题](https://www.luogu.com.cn/problem/P3386)。

写个匈牙利或网络流，并输出保存的匹配情况即可。

时间复杂度约为 $O(n^2m^2)$，如果写优化的 dinic 算法，时间复杂度约为 $O(\sqrt{nm}\cdot nm)$，可以通过本题。
## 参考代码
写的是匈牙利算法。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct node{
	int to,nxt;
}edge[80005];
int head[80005];
int cnt;
void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}
int tr1[80005],tr2[80005];
int cst[205][205],blo1[205][205],blo2[205][205];
int n,m,ans;
bool vst[80005];
int match[80005];
bool dfs(int x){
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(!vst[edge[i].to]){
			vst[edge[i].to]=true;
			if(!match[edge[i].to]||dfs(match[edge[i].to])){
				match[edge[i].to]=x;
				return true;
			}
		}
	}
	return false;
}
int hf(int x,int y){
	return (x-1)*n+y;
}
int t1,t2;
int main(){
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>cst[i][j];
		}
	}
	t2=n*m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(cst[i][j]==2){
				continue;
			}
			if(!blo1[i][j]){
				t1++;
				tr1[t1]=j;
				int tmp=i;
				while(tmp>0){
					if(cst[tmp][j]==2) break;
					blo1[tmp][j]=t1;
					tmp--;
				}
				tmp=i;
				while(tmp<=m){
					if(cst[tmp][j]==2) break;
					blo1[tmp][j]=t1;
					tmp++;
				}
			}
			if(!blo2[i][j]){
				t2++;
				tr2[t2]=i;
				int tmp=j;
				while(tmp>0){
					if(cst[i][tmp]==2) break;
					blo2[i][tmp]=t2;
					tmp--;
				}
				tmp=j;
				while(tmp<=n){
					if(cst[i][tmp]==2) break;
					blo2[i][tmp]=t2;
					tmp++;
				}
			}
			if(cst[i][j]!=0) continue;
			add(blo1[i][j],blo2[i][j]);
		}
	}
	for(int i=1;i<=t1;i++){
		memset(vst,false,sizeof(vst));
		if(dfs(i)) ans++;
	}
	cout<<ans<<'\n';
	for(int i=n*m+1;i<=t2;i++){
		if(match[i]){
			cout<<tr2[i]<<" "<<tr1[match[i]]<<'\n';
		}
	}
	return 0;
}
```
[本代码可以通过洛谷的评测。](https://www.luogu.com.cn/record/162426350)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/6/17.

---

## 作者：wangruibo20 (赞：1)

先搭一个传送门：[[CEOI2002] Royal guards](https://www.luogu.com.cn/problem/P1263)

如果去掉墙和陷阱的限制，这就是一道最基础的二分图的题目（每一行与每一列连边，求最大匹配）。但这道题有陷阱和墙，陷阱很好处理，方法就是它所在行和列不连边，而墙将行和列都隔开了，这意味着被墙隔开的**区域**与**区域**之间不会互相影响。

于是我们将行和列分成这种**区域**：

![](https://cdn.luogu.com.cn/upload/image_hosting/a9yrgjde.png)

这样，若某**横区域**与某**竖区域**有相交的空格子，就将它们连边，然后跑匈牙利就能完美通过了。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
bitset<6000005>vis;
ll l[6000005],n,m,ans,cnt,cnt1,cnt2,a[80005],aa[80005],mp[6005][6005],mp2[6005][6005],head[6000005],nxt[6000005],v[6000005];
char k;
bool dfs(ll u){
	for(ll i=head[u];i;i=nxt[i]){
		if(!vis[v[i]]){
			vis[v[i]]=1;
			if(!l[v[i]]||dfs(l[v[i]])){
				l[v[i]]=u;
				return 1;
			}
		}
	}return 0;
}void add(ll u,ll vv){
	nxt[++cnt]=head[u];
	head[u]=cnt;
	v[cnt]=vv;
}int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			scanf("%lld",&k);
			if(k==2)continue;
			if(!mp[i][j-1])mp[i][j]=++cnt1;
			else mp[i][j]=mp[i][j-1];
			if(!mp2[i-1][j])mp2[i][j]=++cnt2;
			else mp2[i][j]=mp2[i-1][j];
			a[mp[i][j]]=i;
			aa[mp2[i][j]]=j;
			if(!k)add(mp[i][j],mp2[i][j]);
		}
	}cnt=0;
	for(ll i=1;i<=cnt1;i++){
		vis=0;
		if(dfs(i))ans++;
	}printf("%lld",ans);
	for(ll i=1;i<=cnt2;i++)if(l[i])printf("\n%lld %lld",a[l[i]],aa[i]);
}
```



---

## 作者：xh39 (赞：1)

前置算法:二分图最大匹配。请先学习此算法或跳过此题解,若不学,很难看懂此篇题解。

首先,我们考虑一个问题,如果没有墙,那么这道题怎么做。

显然,每一行都只能选择一个,每一列都只能选择一个(否则他们会攻击)

所以,我们可以直接将**不是陷阱的格子**行列建边。然后跑一遍二分图最大匹配。

比如,对于这个图:
```cpp
00
01
```
1行1列,1行2列,2行1列均是空地。

那么我们这样建边,最大匹配就是1->1,2->2
```cpp
1==1
 \
  \
2==2
```

但现在加入了墙,那怎么办呢?每行每列就不是只能选一个了。

那么,我们要构造出只能选1个的。我们发现,在同行同列并且中间没有墙的一些方格就只能选1个。

所以我们把那些可以射击的方格表示为相同的数字,不可以射击表示为不同的数字。然后建边。

比如对于样例(x表示墙)。
```cpp
3 4      行可以相互射击的:   列直接可以相互射击的:
2 0 0 0  x 1 1 1             x 1 2 3
2 2 2 1  x x x 2             x x x 3
0 1 0 2  3 3 3 x             4 5 6 x
```
然后建边1->1,1->2,1->3,3->4,3->6。

具体思路就看代码吧,看了代码你就懂了。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[1005][1005],x[1005][1005],y[1005][1005];
int kkksc03[1000005];
bool mark[1000005];
struct xyq{
	int v,next;
}_[1000005];
int head[1000005],tot=1;
void add(int u,int v){
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	++tot;
}
bool dfs(int iakioi){
	int i;
	for(i=head[iakioi];i;i=_[i].next){
		if(mark[_[i].v]){ 
			continue;
		}
		mark[_[i].v]=1;
		if(!kkksc03[_[i].v]||dfs(kkksc03[_[i].v])){
			kkksc03[_[i].v]=iakioi;
			return true;
		}
	}
	return false;
}
int fx[1000005],fy[1000005],n,m;
void Find(int xx,int yy,int &ra,int &rb){ //查找行列的函数。
	ra=-1;
	rb=-1;
	int i,j;
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			if(x[i][j]==xx&&y[i][j]==yy){
				ra=i;
				rb=j;
				return;
			}
		}
	}
}
int main(){
	int i,j,sum=0,sumx=1,sumy=1,aa,bb;
	cin>>n>>m;
	for(i=0;i<=n;i++){
		for(j=0;j<=m;j++){
			a[i][j]=2; //一开始全是墙,否则会出现边界不是墙而产生的问题。
		}
	}
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]!=2){
				if(a[i-1][j]==2){ //如果与前面一个可以射击就与前面一样,否则新建一个分组。
					x[i][j]=sumx; 
					fx[sumy]=i;
					fx[sumy]=j;
					sumx++;
				}else{
					x[i][j]=x[i-1][j];
				}
				if(a[i][j-1]==2){
					y[i][j]=sumy;
					fy[sumy]=i;
					fy[sumy]=j;
					sumy++;
				}else{
					y[i][j]=y[i][j-1];
				}
				if(!a[i][j]){ //只有在空地才建边。
					add(x[i][j],y[i][j]);
				}
			}
		}
	}
	for(i=1;i<sumx;++i){
		memset(mark,0,sizeof(mark));
		sum+=dfs(i);
	}
	cout<<sum<<endl;
	for(i=1;i<=sumy;++i){
		if(kkksc03[i]){
			Find(kkksc03[i],i,aa,bb); //由于要输出方案,要设一个查找函数,根据分组查找出行列。
			cout<<aa<<" "<<bb<<endl;
		}
	}
	return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

[cnblog 版](https://www.cnblogs.com/xlpg-0713/articles/17798542.html)

三倍经验紫题，你真的不来做吗？
[1263](https://www.luogu.com.cn/problem/P1263) [2825](https://www.luogu.com.cn/problem/P2825) [6062](https://www.luogu.com.cn/problem/P6062)

题意差不多都是这样的：一个网格图，有的地方是墙；有的地方是空地，可以放哨兵（或其他的）；有的地方是陷阱，不可以放哨兵。一个哨兵可以看到他所在的行和列（看不穿墙）。要求哨兵之间不可相互看到，求最多放多少个哨兵？

首先显然地，所有空地一定被看到，因为如果有空地没被看到就可以再放一个哨兵，这也是为什么这道题的结论到 P6062 也是正确的。

考虑连续的一横段或一竖段最多只有一个人，这是经典的二分图匹配模型。陷阱不放人，空地对应的行向列连一条边，然后跑二分图匹配。

现在考虑墙的限制。一道横的墙会把上面的一段和下面的一段隔开，上面的列和下面的列就互不影响了。怎么办呢，以这道墙的边的编号为新的列，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yvtzmjuf.png)

连边时，连新的编号就行了，这样可以处理墙的限制，列也是同理的

代码实现上，如果有一道墙，他的上面应当被作为列的编号，对应的是墙上面所有可达的空地。右面省略。另外，为处理不被墙限制的点，在地图的外围围一堵墙。由于 $n$ 只有区区 $200$，可以让点 $(i,j)$ 的下方和右方的线标号为 $(i-1)\times200+j$ 和 $(i-1)\times200+j+40000$ 这样可以不重叠，然后跑一遍二分图，最后最大流就是结果。

另外要构造出一组可行解，由行连向列的正向边如果有流通过，对应的点是答案。

我在代码里用了 dinic，由于有 $n^2$ 个点，复杂度是 $n^2\times \sqrt {n^2}=O(n^3)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std; int wl[202][202][2], now[80002];
int n, m, s, t, mp[202][202], dep[80002], res; const int inf = 1e9;
struct edge{int u, v, w, nxt;}e[1000010]; int cnt = 1, head[80002];
inline void add(int u, int v){
    e[++cnt] = (edge){u, v, 1, head[u]}; head[u] = cnt;
    e[++cnt] = (edge){v, u, 0, head[v]}; head[v] = cnt;
} // 加边
inline bool bfs(){
    memset(dep, -1, sizeof dep);
    queue<int>q;
    q.emplace(s); dep[s] = 0;
    while(q.size()){ int x = q.front(); q.pop();
        for(int i = head[x]; i; i = e[i].nxt){ auto o = e[i]; int v = o.v;
            if(o.w && dep[v] == -1) dep[v] = dep[x] + 1, q.emplace(v);}
    } for(int i = 0; i <= 80001; i++) now[i] = head[i]; return dep[t] != -1;
}
inline int dfs(int x, int lim){
    if(x == t) return lim; int used = 0;
    for(int &i = now[x]; i; i = e[i].nxt){ 
        auto o = e[i]; int v = o.v;
        if(dep[v] == dep[x] + 1 && o.w){
            int t = dfs(v, min(lim, o.w));
            used += t; e[i].w -= t; e[i^1].w += t;
            if (t == lim){now[x] = i; break;}
        }
    }
    if (!used){dep[x] = -1;}
    return used;
}//网络流部分
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    cin >> n >> m; s = 0, t = 80001;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> mp[i][j];
    for(int i = 0; i <= n + 1; i++) mp[i][0] = 2, mp[i][m + 1] = 2; 
	for(int i = 1; i <= m + 1; i++) mp[0][i] = 2, mp[n + 1][i] = 2; //先围一堵墙
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(mp[i][j] != 2){
			int ps = (i - 1) * 200 + j;
			if(mp[i + 1][j] == 2){
                add(s, ps); for(int k = i; mp[k][j] != 2; k--) wl[k][j][0] = ps;
			}if(mp[i][j + 1] == 2){ ps += 40000;
                add(ps, t); for(int k = j; mp[i][k] != 2; k--) wl[i][k][1] = ps;
			} //这部分是求出每个点对应的行和列（新的）
		} int ct = cnt + 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(!mp[i][j]) add(wl[i][j][0], wl[i][j][1]); //二分图的连边
    while(bfs()) res += dfs(s, inf); //跑最大流
    cout << res << '\n';
    for(int i = ct; i <= cnt; i++) if(!e[i].w && (e[i].v >= 40001))
        cout << (e[i].v - 40001) / 200 + 1 << ' ' << (e[i].u - 1) % 200 + 1 << '\n'; //构造方案。
    return 0;
}
```

---

## 作者：yizhiming (赞：0)

三倍经验题捏。

[三](https://www.luogu.com.cn/problem/P1263)
[道](https://www.luogu.com.cn/problem/P6062)
[题](https://www.luogu.com.cn/problem/P2825)

## 题面大意

给定一个 $n\times m$ 的网格图，有墙，空地和陷阱三种东西，你可以在空地放置守卫，守卫能够射击它所在的行和列，但是无法穿透墙，陷阱可以被穿透，但不能放置守卫，问最多放置多少个守卫，并给出一种合法方案。

$1\leq n,m \leq 200$。

## 题目分析

能做到这道题的人都是擅长网络流的人，建模还需要我讲吗(

我们仔细考虑如何放置守卫，如果当前位置能够放置，则放置，并且其所在的行和列便无法再放置，所以原题可以抽象为每个点，要么被它所在列覆盖，要么被它所在的行覆盖（如果都没覆盖，显然能够再放置一个守卫）。

所以问题转化为了对于每个点，能够被所在行或者所在列覆盖的前提下，能够覆盖多少次，这东西就是网络流基本建模了，我们考虑对于每个点，由所在行连向所在列，然后跑二分图最大匹配即可。

这道题我们发现行和列不好维护，所以我们考虑将概念改一下，我们对于每一个墙，都给它一个编号 $x$，然后我们维护每个墙向下的空地和向右的空地，则说这些空地所在的列/行为当前墙的编号，然后直接网络流即可。

输出方案直接维护每一个连接行和列的线段是连了哪一行哪一列，然后直接在残余网络上找边权为 $0$ 的正边即可。

## Code

因为要维护每个墙下面和右面的点，所以顶着上面和左面的空地会找不到编号，所以我们人为地增加一行以及一列墙，方便修改。

读入的取模不要在意，那是其它经验的题的读入，我懒得改了。。。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 205;
const int V = N*N*4;
char ch[N];
int mp[N][N],S,T;
struct aa{
	int nxt,to,val;
}edge[V*2];
int tot=1,head[V];
void add(int u,int v,int w){
	edge[++tot].nxt = head[u];edge[tot].to = v;head[u] = tot;edge[tot].val = w;
	edge[++tot].nxt = head[v];edge[tot].to = u;head[v] = tot;edge[tot].val = 0;
}
int num1[N][N];
int num2[N][N];
int dep[V];
queue<int>q;
bool bfs(){
	memset(dep,0,sizeof(dep));
	dep[S] = 1;
	q.push(S);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(!dep[now]&&edge[i].val){
				dep[now] = dep[u]+1;
				q.push(now);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int f){
	if(u==T){
		return f;
	}
	int used = 0;
	for(int i=head[u];i&&f;i=edge[i].nxt){
		int now = edge[i].to;
		if(dep[now]==dep[u]+1&&edge[i].val){
			int w = dfs(now,min(f,edge[i].val));
			edge[i].val-=w;edge[i^1].val+=w;
			used+=w;f-=w;
		}
	}
	if(!used){
		dep[u] = 0;
	}
	return used;
}
int ans,inf = 1e9;
void dinic(){
	while(bfs()){
		ans+=dfs(S,inf);
	}
}
int val1[V],val2[V];
int main(){
	int n,m;
	n = read();m = read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mp[i][j] = (read()+1)%3;
		}
	}
	S = 0;T = (n+1)*(m+1)*2+1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(mp[i][j]){
				continue;
			}
			bool flg = 1;
			for(int k=i+1;k<=n;k++){
				if(mp[k][j]==0){
					break;
				}
				flg = 0;
				num1[k][j] = i*(m+1)+j; 
			}
			if(!flg){
				add(S,i*(m+1)+j,1);
			}
			flg = 1;
			for(int k=j+1;k<=m;k++){
				if(mp[i][k]==0){
					break;
				}
				flg = 0;
				num2[i][k] = i*(m+1)+j+(n+1)*(m+1);
			}
			if(!flg){
				add(i*(m+1)+j+(n+1)*(m+1),T,1);
			}
		}
	}
	int tots = tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]==1){
				val1[tot+1] = i;val2[tot+1] = j;
				add(num1[i][j],num2[i][j],1);
			}
		}
	}
	dinic();
//	for(int i=head[T];i;i=edge[i].nxt){
//		int now = edge[i].to;
//		cout<<"Node:"<<now<<" "<<edge[i].val<<"\n";
//	}
	cout<<ans<<"\n";
	for(int i=tots+1;i<tot;i+=2){
		if(!edge[i].val){
			cout<<val1[i]<<" "<<val2[i]<<"\n"; 
		}
	}
	return 0;
} 
```


---

## 作者：AIskeleton (赞：0)

### 题意

给出一个 $m \times n$ 的矩阵，有空地、墙、陷阱三种情况。

只有空地可以放置守卫，若两个守卫在同一行或同一列且其之间没有墙的阻挡则这两个守卫可以互相看见。

求最多可以放置的守卫数，并输出一种放置方案。

### 题解

其实这题和 P2825 几乎一致，墙的存在让行、列分段，各段之间互不干扰。

所以可以把每个部分看成一个点，即把连续的一段缩成一个点并编号。

然后把可以放置的点的位置的行、列坐标连边，跑二分图最大匹配即可。

题目要求输出方案，就利用匈牙利算法的特性，把编号与行列对应即可。

### 代码

```
#include <bits/stdc++.h>
#define V e[i].v
using namespace std;const int N=2e3,M=1e6;int n,m,a[N][N],in[N][N],out[N][N],t,c,ans,F[M],f[N],p[M];
struct E{int v,nt;}e[M];void I(int u,int v){e[++c].v=v;e[c].nt=F[u];F[u]=c;}
int D(int x){for(int i=F[x];i;i=e[i].nt)if(!f[V]){f[V]=1;if(!p[V]||D(p[V])){p[V]=x;return 1;}}return 0;}
int main(){
    cin>>n>>m;for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!=2){if(j==1||a[i][j-1]==2)t++;in[i][j]=t;}
    for(int j=1;j<=m;j++)for(int i=1;i<=n;i++)if(a[i][j]!=2){if(i==1||a[i-1][j]==2)t++;out[i][j]=t;}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!a[i][j])I(in[i][j],out[i][j]);
    for(int i=1;i<=t;i++)memset(f,0,sizeof(f)),ans+=D(i);cout<<ans<<endl;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(p[out[i][j]]==in[i][j]&&!a[i][j])cout<<i<<" "<<j<<endl;
    return 0;
}
```

---

