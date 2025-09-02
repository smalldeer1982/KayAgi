# Destroying Roads

## 题目描述

在这个国家有$n$ 个城市，城市间由$m$ 条双向公路连接。城市被编号为$1$ 到$n$ 。如果城市$a$ 和$b$ 被公路连接，那么你可以双向通行。你可以在这个公路网上通过公路从一个城市移动到另一个城市。走过每条公路均耗时$1$ 小时。

你想要破坏最多的公路，但是破坏后必须满足从指定城市$s_1$ 到$t_1$ 最短不超过$l_1$ 小时，且从指定城市$s_2$ 到$t_2$ 最短不超过$l_2$ 小时。

计算在符合条件的情况下能破坏的最多公路数量。如果无论如何都无法满足条件，输出$-1$ 。

## 样例 #1

### 输入

```
5 4
1 2
2 3
3 4
4 5
1 3 2
3 5 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
4 5
1 3 2
2 4 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 4
1 2
2 3
3 4
4 5
1 3 2
3 5 1
```

### 输出

```
-1
```

# 题解

## 作者：ShineEternal (赞：5)

> https://www.cnblogs.com/ShineEternal/p/11222368.html


看到没有题解就贡献一波呗 

题解通过率：114/164


# 分析：

这题其实就是想让我们求一个图中两条最短路的最短（好把更多的边删掉）。

我们先考虑一条最短路，~~别问我我怎么会的~~显然，就是s和t跑个最短路再用n-就行。

然后就是两条喽！~~这不就是做两次吗，我太巨了！~~

这当然是可以的

## ——不过只是一种情况

考虑到我们的两条路径可能会有重合，我们只好**枚举重合最短路的左右端点**，将路径分为5段（6段？）来处理。

然后问题基本就解决了，最开始把两两点之间预处理出最短路，这里要注意bfs即可~~别告诉我你要用Floyd~~

最后的答案如果比m大就-1了。

l1,l2的限制条件不要忘了判断鸭!

# 代码：

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int d[3005][3005];
int vis[3005];
vector<int>e[3005];
void bfs(int s)
{
	memset(vis,0,sizeof(vis));
	queue<int>q;
	q.push(s);
	//vis[s]=1;
	d[s][s]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=0;i<e[x].size();i++)
		{
			int y=e[x][i];
			if(d[s][y]==-1)
			{
				d[s][y]=d[s][x]+1;
				//printf("%d\n",d[s][y]);
				q.push(y);
			}
		} 
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	memset(d,-1,sizeof(d));
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	int s1,t1,l1,s2,t2,l2;
	scanf("%d%d%d",&s1,&t1,&l1);
	scanf("%d%d%d",&s2,&t2,&l2);
	for(int i=1;i<=n;i++)
	{
	//	printf("qaq\n");
		bfs(i);
	}
	/*for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			printf("%d ",d[i][j]);
		}
		printf("\n");
	}*/
	int ans=999999999;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(d[s1][i]+d[i][j]+d[j][t1]>l1)continue;
			if(d[s2][i]+d[i][j]+d[j][t2]>l2)continue;
			ans=min(ans,d[s1][i]+d[i][j]+d[j][t1]+d[s2][i]+d[i][j]+d[j][t2]-d[i][j]);
		} 
	}
	if(d[s1][t1]<=l1&&d[s2][t2]<=l2)
	{
		ans=min(ans,d[s1][t1]+d[s2][t2]);
	}
	swap(s2,t2);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(d[s1][i]+d[i][j]+d[j][t1]>l1)continue;
			if(d[s2][i]+d[i][j]+d[j][t2]>l2)continue;
			ans=min(ans,d[s1][i]+d[i][j]+d[j][t1]+d[s2][i]+d[i][j]+d[j][t2]-d[i][j]);
		} 
	}
	if(d[s1][t1]<=l1&&d[s2][t2]<=l2)
	{
		ans=min(ans,d[s1][t1]+d[s2][t2]);
	}
	if(ans>m)printf("-1\n");
	else
	printf("%d\n",m-ans);
	return 0;
} 

```

---

## 作者：Konnyaku_LXZ (赞：3)

这题和 [P5683 [CSPJX2019]道路拆除](https://www.luogu.com.cn/problem/P5683) 非常像，那题是这题的弱化版。

首先我们第一反应肯定是找最短路，即 $dis[s1][t1]$ 和 $dis[s2][t2]$。但是由于有两条路径，所以它们有可能有重合部分。

我们枚举重合部分的两个端点 $i,j$ ，将两条路径分成五个部分，这五个部分中每个部分一定都是要走最短路的，因为如果你不走最短路，那么路径会变长，可拆除的道路会变少，并且无法满足时间限制的概率会变大。

然后计算每个部分的最短路，相加即可。

当然路径可能有两种情况：

① $s1-->i-->j-->t1$ 

$s2-->i-->j-->t2$

②$s1-->i-->j-->t1$

$s2-->j-->i-->t2$

分别计算两种情况的答案即可。

具体见代码。

Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN=3050,INF=0x3f3f3f3f;

struct edge{
	int next;
	int to;
};

int N,M,head[MAXN],Cnte=0,Ans=-1;
int s1,t1,l1,s2,t2,l2;
int dis[MAXN][MAXN];
edge e[MAXN*MAXN];//注意边数要开到点数的平方 

void adde(int u,int v){
	++Cnte;
	e[Cnte].to=v;
	e[Cnte].next=head[u];
	head[u]=Cnte;
}

void bfs(int start){//求最短路 
	queue<int> q;
	while(!q.empty()) q.pop();
	q.push(start);
	dis[start][start]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[start][v]!=INF) continue;
            dis[start][v]=dis[start][u]+1;
            q.push(v);
		}
	}
}

bool check1(int x,int y){return dis[s1][x]+dis[x][y]+dis[y][t1]<=l1&&dis[s2][x]+dis[x][y]+dis[y][t2]<=l2;}
bool check2(int x,int y){return dis[s1][x]+dis[x][y]+dis[y][t1]<=l1&&dis[t2][x]+dis[x][y]+dis[y][s2]<=l2;}

void Init(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);//链式前向星建图 
	}
	scanf("%d%d%d%d%d%d",&s1,&t1,&l1,&s2,&t2,&l2);
}

void Solve(){
	for(int i=1;i<=N;++i) for(int j=1;j<=N;++j) dis[i][j]=INF;
	for(int i=1;i<=N;++i) bfs(i);//bfs求两点间最短路 
	for(int i=1;i<=N;++i)
		for(int j=1;j<=N;++j){//两种情况 
			if(check1(i,j)) Ans=max(Ans,M-dis[s1][i]-dis[s2][i]-dis[i][j]-dis[j][t1]-dis[j][t2]);
			if(check2(i,j)) Ans=max(Ans,M-dis[s1][i]-dis[t2][i]-dis[i][j]-dis[j][t1]-dis[j][s2]);
		}//也有可能两条路径没有重合，此时分别跑最短路即可 
	if(dis[s1][t1]<=l1&&dis[s2][t2]<=l2) Ans=max(Ans,M-dis[s1][t1]-dis[s2][t2]);
}

void Print(){
	printf("%d\n",Ans);
}

int main()
{
	Init();
	Solve();
	Print();
	return 0;
}
```

---

## 作者：liyichun001 (赞：3)

# 题解CF543B
食用博客效果更佳:　<https://www.luogu.org/blog/123-day/zui-duan-lu>
### 一道很裸（shui）的$\color{blue}\text{SPFA求任意两点最短路}$
思路：由于要求从 **s1/s2 到 t1/t2 的距离不超过 d1/d2，**　且要破坏最多的道路，因此求 s1/s2 到 t1/t2 的最短路，然后**判断能否在 d1/d2 范围内到达，**　如果能在范围内到达则将 s1-t1、s2-t2 两条路的**边数相加**，然后枚举找这两条路重叠的边数，最后的结果等于总的边数减去两条路的边数再加上重叠的边数
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 5001
using namespace std;
int n,m;
vector<int> G[N];
int dis[N][N];
bool vis[N];
void SPFA(){
    for(int i=1;i<=n;i++){
        memset(vis,false,sizeof(vis));
        vis[i]=true;
        queue<int> Q;
        Q.push(i);
        while(!Q.empty()){
            int x=Q.front();
            Q.pop();
            for(int j=0;j<G[x].size();j++){
                int y=G[x][j];
                if(vis[y])
                    continue;
 
                vis[y]=true;
                dis[i][y]=dis[i][x]+1;
                Q.push(y);
            }
        }
    }
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=m;i++)
            G[i].clear();
 
        for(int i=1;i<=m;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
 
        int s1,t1,d1,s2,t2,d2;
        scanf("%d%d%d%d%d%d",&s1,&t1,&d1,&s2,&t2,&d2);
        SPFA();
        if(dis[s1][t1]>d1||dis[s2][t2]>d2)
            printf("-1\n");
        else{
            int res=dis[s1][t1]+dis[s2][t2];
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dis[s1][i]+dis[i][j]+dis[j][t1]<=d1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=d2)
                        res=min(res,dis[s1][i]+dis[i][j]+dis[j][t1]+dis[s2][i]+dis[j][t2]);
                    if(dis[s1][i]+dis[i][j]+dis[j][t1]<=d1&&dis[t2][i]+dis[i][j]+dis[j][s2]<=d2)
                        res=min(res,dis[s1][i]+dis[i][j]+dis[j][t1]+dis[t2][i]+dis[j][s2]);
                }
            }
            printf("%d\n",m-res);
        }
    }
    return 0;
}
```

---

## 作者：Peter0701 (赞：3)

背景：$Codeforces$ $Round$ $\#302$ $(Div. 1)$ $B$ 题， $Codeforces543B$ 

给定一张边权全为 $1$ 的图。在保证点 $s_1$ 到点 $t_1$ 的距离不超过 $l_1$ 且点 $s_2$ 到点 $t_2$ 的距离不超过 $l_2$ 的条件下，求最多能删去的边数。如果没有合法方案，输出 $-1$ 。

这题最关键的就是转化模型。一开始我死都没想到正解就是因为忽略了边权全为 $1$ 。

设点 $i$ 到点 $j$ 的最短长度为 $dis[i][j]$ 。这时原条件就可以转化成求点 $s_1$ 到点 $t_1$ 的最短路上和点 $s_2$ 到点 $t_2$ 的最短路上经过的路径边数之和。

当然，这其中有 $3$ 种情况：

第一种是点 $s_1$ 到点 $t_1$ 的最短路和点 $s_2$ 到点 $t_2$ 的最短路没有重叠部分。这个时候两个最短路值直接相加就行。

第二种是点 $s_1$ 到点 $t_1$ 的最短路和点 $s_2$ 到点 $t_2$ 的最短路在点 $i$ 和点 $j$ 之间重叠。这个时候可以 $O(n^2)$ 枚举重叠点 $i$ 和 $j$ ，在保证路长限制的情况下更新答案就行，答案是 $dis[s_1][i]+dis[s_2][i]+dis[i][j]+dis[j][t_1]+dis[j][t_2]$ 。

第三种也是点 $s_1$ 到点 $t_1$ 的最短路和点 $s_2$ 到点 $t_2$ 的最短路在点 $i$ 和点 $j$ 之间重叠，但是点 $s_2$ 到点 $t_2$ 的最短路从点 $i$ 走向点 $j$ ，而点 $s_1$ 到点 $t_1$ 的最短路从点 $j$ 走向点 $i$ 。 这个时候做法同上，答案是 $dis[s_1][j]+dis[s_2][i]+dis[i][j]+dis[i][t_1]+dis[j][t_2]$ 。

至于求任意两点的最短路嘛，做 $n$ 遍 $bfs$ 就行。

整个过程就是这样，如果还有什么不明白的，评论区见！感谢您的耐心阅读！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int n,m,x,y,s1,s2,t1,t2,l1,l2,ans;
int num,head[6005],dis[3005][3005],vis[3005];
struct edge
{
	int ver,nxt;
}e[6005];
queue<int> q;
inline void adde(int u,int v)
{
	e[++num].ver=v;
	e[num].nxt=head[u];
	head[u]=num;
}
inline void bfs(int s)
{
	memset(vis,0,sizeof(vis));
	q.push(s);
	vis[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(register int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].ver;
			if(vis[y])
				continue;
			vis[y]=1;
			dis[s][y]=dis[s][x]+1;
			q.push(y);
		}
	}
}
int main()
{
	n=read();
	m=read();
	for(register int i=1;i<=m;i++)
	{
		x=read();
		y=read();
		adde(x,y);
		adde(y,x);
	}
	for(register int i=1;i<=n;i++)
		bfs(i);
	s1=read();
	t1=read();
	l1=read();
	s2=read();
	t2=read();
	l2=read();
	if(dis[s1][t1]>l1||dis[s2][t2]>l2)
	{
		printf("-1\n");
		return 0;
	}
	ans=dis[s1][t1]+dis[s2][t2];
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2)
				ans=min(ans,dis[s1][i]+dis[i][j]+dis[j][t1]+dis[s2][i]+dis[j][t2]);
			if(dis[s1][j]+dis[i][j]+dis[i][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2)
				ans=min(ans,dis[s1][j]+dis[i][j]+dis[i][t1]+dis[s2][i]+dis[j][t2]);
		}
	}
	printf("%d\n",m-ans);
	return 0;
}
```

---

## 作者：牛蛙丶丶 (赞：1)

删掉更多的边则意味着保留的边肯定要尽量的少一点，那么我们可以把问题转化为求一个图中两条最短路中的最小值。

要先预处理出所有的点之间的最短路，并且将答案初始为 $s_1$ 到 $t_1$ 和 $s_2$ 到 $t_2$ 的距离之和，此时不要忘了判断。

显然，我们所求的两条最短路中可能会有重合的部分，此时我们可以 $n^2$ 枚举点对，来将路径分为5段进行处理，我们令中间的划分点为 i,j ,此时得到了5段路径，这时我们可以发现有两种情况：

- $s_1 \rightarrow i$，$i \rightarrow j$，$j \rightarrow t_1$，$s_2 \rightarrow i$，$j \rightarrow t_2$

- $s_1 \rightarrow j$，$j \rightarrow i$，$i \rightarrow t_1$，$s_2 \rightarrow i$，$j \rightarrow t_2$

求保留的边的最小值即可。

#### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<cstring>
#define F1(i,l,r) for(int i=l;i<=r;++i)
#define F2(i,r,l) for(int i=r;i>=l;--i)
#define sf(i) scanf("%d",&i)
#define pf(i) printf("%d\n",i)
#define v e[i].to
#define inf 0x3f3f3f3f
#define N 3070
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

struct Edge{
	int to,nxt,w;
}e[N*N];
int n,m,s1,t1,l1,s2,t2,l2,cnt;
int d[N][N],head[N];
bool vis[N][N];

void add(int from,int to,int val){
	e[++cnt].to=to;
	e[cnt].w=val;
	e[cnt].nxt=head[from];
	head[from]=cnt;
}

void Spfa(int s){
	for(int i=1;i<=n;++i) vis[s][i]=0;
	d[s][s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt)
			if(v!=s&&d[s][v]>d[s][u]+e[i].w){
				d[s][v]=d[s][u]+e[i].w;
				if(!vis[s][v]){
					vis[s][v]=1;
					q.push(v);
				}
			}
	}
}

int main(){
	sf(n),sf(m);
	memset(d,0x3f,sizeof(d));
	F1(i,1,m){int a,b;a=read(),b=read();add(a,b,1),add(b,a,1);}
	F1(i,1,n) Spfa(i);
	sf(s1),sf(t1),sf(l1),sf(s2),sf(t2),sf(l2);
	if(d[s1][t1]>l1||d[s2][t2]>l2){pf(-1);return 0;}
	int ans=d[s1][t1]+d[s2][t2];
	F1(i,1,n)
		F1(j,1,n){
			if(d[s1][i]+d[i][j]+d[j][t1]<=l1&&d[s2][i]+d[i][j]+d[j][t2]<=l2)
				ans=min(ans,d[s1][i]+d[i][j]+d[j][t1]+d[s2][i]+d[j][t2]);
			if(d[s1][j]+d[i][j]+d[i][t1]<=l1&&d[s2][i]+d[i][j]+d[j][t2]<=l2)
				ans=min(ans,d[s1][j]+d[i][j]+d[i][t1]+d[s2][i]+d[j][t2]);			
	}
	pf(m-ans);
}
```

呃呃，码风恶臭

---

## 作者：初雪_matt (赞：0)

既然求能被破坏的最多公路数量且边权均为 $1$，那么就是使走的公路尽可能少。

题目还对路径权值和有要求，要使得路径不超过某数值，其实就是判无解的情况，因为你要使走的公路尽可能少，必定是走最短路而不会考虑路径和的封顶要求。

所以可以求出两条最短路，$s_1\rightarrow t_1$ 与 $s_2\rightarrow t_2$，发现难点在于如果有重边答案会更优，所以需要枚举重边的起点与终点位置。

需要任意两点之间的距离，由于边权为 $1$，可以考虑对每个点进行 bfs 求解。

时间复杂度 $O(n^2+nm)$。

---

## 作者：Sad_Rex (赞：0)

**一：题意转述：**

题目中只说每个起点到终点的路径不超过 $l_1$ 和 $l_2$，但可以转化一下：对于每个起点到终点，若它们的最短路径都超过了 $l_1$ 和 $l_2$，那么一定无解。又因为每条边的边权都为 $1$，所以**我们只要考虑最短路径即可**。

**其次**，我们可以将能破坏的最多公路数量的数量转化为使得**最短路径上的边的数量尽可能少**。

**二：解题：**

对于，以上的分析，我们可以容易的得到**若** $s_1$ **到** $t_1$ **的最短路径和** $s_2$ **到** $t_2$ **的最短路径不重边**，则有**答案 $m - len1-len2$** （其中 $m$ 为总边数，$len_1$ 和 $len_2$ 分别为 $s_1$ 到 $t_1$ 的最短路径，$s_2$ 到 $t_2$ 的最短路径）。

那如果有重边呢。

我们可以**枚举重边的起点和终点**，最后答案总减去对应的最短路即可。

对于最短路径由于我们要多次询问，所以我们可以预处理一遍。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int  long long
#define kg putchar(' ')
#define endl puts("")
inline int read(){
    int vis=1,ans=0;
    char x=getchar();
    while(x<'0'||x>'9'){
        if(x=='-')vis=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9'){
        ans=ans*10+x-'0';
        x=getchar();
    }
    return vis*ans;
}
inline void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
const int N=4090;
int n=read(),m=read();
int s1,t1,l1,s2,t2,l2;
struct node{
	int nxt,to;
}e[2*N];
int head[N],cnt;
void add(int x,int y){
	++cnt;
	e[cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
bool vis[N];
int dis[N][N];
queue<int>q;
inline void dijkstra(int s){
	for(int i=1;i<=n;i++)dis[s][i]=1e18,vis[i]=0;
	dis[s][s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int id=q.front();
		q.pop();
		vis[id]=0;
		for(int i=head[id];i;i=e[i].nxt){
			int y=e[i].to;
			if(dis[s][y]>dis[s][id]+1){
				dis[s][y]=dis[s][id]+1;
				if(vis[y])continue;
				q.push(y);
				vis[y]=1;
			}
		}
	}//模板 
}
signed main(){
	for(int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		add(u,v);
		add(v,u);//建图 
	}
	s1=read(),t1=read(),l1=read(),s2=read(),t2=read(),l2=read();
	for(int i=1;i<=n;i++)dijkstra(i);//预处理跑dijkstra
	int len1=dis[s1][t1],len2=dis[s2][t2];
	if(s1>t1)swap(s1,t1);
	if(s2>t2)swap(s2,t2);
	if(len1<0||len1>l1||len2<0||len2>l2){
		print(-1);
		return 0;
	}//如果无论如何都不能在规定时间内跑到输出-1 
	int ans=len1+len2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2){
				ans=min(ans,dis[s1][i]+dis[i][j]+dis[j][t1]+dis[s2][i]+dis[j][t2]);//统计最短路的最小值 
			}
			if(dis[s1][j]+dis[i][j]+dis[i][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2){
				ans=min(ans,dis[s1][j]+dis[i][j]+dis[i][t1]+dis[s2][i]+dis[j][t2]);
			}
		}
	}
	print(m-ans);
    return 0;
}
```

---

## 作者：_ChongYun_ (赞：0)

# 题意

给你一个图，在满足 $s_1$ 至 $t_1$ 的最短路不超过 $l_1$，$s_2$ 至 $t_2$ 的最短路不超过 $l_2$ 的情况下尽可能删除更多的边，问最多可以删多少。

# 解析

我们先将每一个点到所以点的最短路预处理出来。

由于两条路径可能会重合，我们直接枚举重合的左右端点 $i$ 和 $j$，每次如果满足条件，就更新答案，如果没重合，直接求出答案。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,ans=-1;
int s1,t1,l1,s2,t2,l2;
struct node{
	int to,nxt,val;
}w[114514<<1];
int h[114514<<1];
int cnt=0;
void Link(int x,int y,int val){
	++cnt;
	w[cnt].to=y;
	w[cnt].nxt=h[x];
	w[cnt].val=val;
	h[x]=cnt;
}
int dis[1145<<2][1145<<2];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q; 
void dijkstra(int st){
	dis[st][st]=0;
	q.push(make_pair(0,st));
	while(!q.empty()){
		int xx=q.top().first;
		int x=q.top().second;
		q.pop();
		if(xx!=dis[st][x]) continue;
		for(int i=h[x];i!=0;i=w[i].nxt){
			int y=w[i].to;
			if(dis[st][y]>dis[st][x]+w[i].val){
				dis[st][y]=dis[st][x]+w[i].val;
				q.push(make_pair(dis[st][y],y));
			}
		}
	}
	return ;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		Link(u,v,1);
		Link(v,u,1);
	}
	cin>>s1>>t1>>l1>>s2>>t2>>l2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=INT_MAX;
		}
	}
	for(int i=1;i<=n;i++){
		dijkstra(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2) ans=max(ans,m-(dis[i][j]+dis[s1][i]+dis[j][t1]+dis[s2][i]+dis[j][t2]));
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[t2][i]+dis[i][j]+dis[j][s2]<=l2) ans=max(ans,m-(dis[i][j]+dis[s1][i]+dis[j][t1]+dis[t2][i]+dis[j][s2]));
		}
	}
	if(dis[s1][t1]<=l1&&dis[s2][t1]) ans=max(ans,m-(dis[s1][t1]+dis[s2][t2]));
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：LCGUO (赞：0)

这题是一个简单的最短路。

题意等价于求最少保留几条边，答案就是用 $m$ 减去最少保留边的个数。

因为题目只关心 $s_1$，$t_1$，$s_2$，$t_2$，所以我们只用保留 $s_1 \to t_1$ 和 $s_2 \to t_2$ 这两条路径就好了。

我们设 $dis_{i,j}$ 表示点 $i$ 到点 $j$ 的最短路径。

不存在的情况是当两条最短路的长度均大于要求长度。

当这两条路径不相交时，最少保留的边数就是 $dis_{s_1,t_1}+dis_{s_2,t_2}$

当两条路有相交的时候，假设相交的部分是 $x_1 \to x_2$，路径就是：

$s_1 \to x_1 \to x_2 \to t_1$ 或 $t_1 \to x_1 \to x_2 \to s_1$ 和 $s_2 \to x_1 \to x_2 \to t_2$ 或 $t_2 \to x_1 \to x_2 \to s_2$。

然后，我们可以先求出每个点到另外所有点的距离，然后 $n^2$ 枚举相交部分的端点 $x_1$，$x_2$ 就好了。

（其实我最开始用堆优化 dj 跑最短路，复杂度多个 log，后来才发现 bfs 就好了）

---

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
    return f?s:-s;
}
int n,m,tot,nxt[6010],ver[6010],head[3010];
int dis[3010][3010],vis[3010];
int s1,t1,l1,s2,t2,l2;
void add(int x,int y){
    nxt[++tot]=head[x]; ver[tot]=y;
    head[x]=tot;
}
queue<int>q;
void bfs(int s){
    memset(vis,0,sizeof vis);
    while(q.size()) q.pop();
    q.push(s); dis[s][s]=0; vis[s]=1;
    while(q.size()){
        int x=q.front(); q.pop();
        for(rint i=head[x];i;i=nxt[i]){
            int y=ver[i];
            if(vis[y]) continue;
            dis[s][y]=dis[s][x]+1;
            q.push(y); vis[y]=1;
        }
    }
}
int main(){
    n=read(); m=read();
    for(rint i=1;i<=m;++i){
        int x=read(),y=read();
        add(x,y); add(y,x);
    }
    s1=read(); t1=read(); l1=read();
    s2=read(); t2=read(); l2=read();
    memset(dis,0x3f,sizeof dis);
    for(rint i=1;i<=n;++i) bfs(i);
    if(dis[s1][t1]>l1||dis[s2][t2]>l2){
        printf("-1");
        return 0;
    }
    int ans=dis[s1][t1]+dis[s2][t2];
    for(rint i=1;i<=n;++i)
        for(rint j=1;j<=n;++j){
            if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2)
                ans=min(ans,dis[s1][i]+dis[j][t1]+dis[s2][i]+dis[i][j]+dis[j][t2]);
            if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1&&dis[t2][i]+dis[i][j]+dis[j][s2]<=l2)
                ans=min(ans,dis[s1][i]+dis[j][t1]+dis[t2][i]+dis[i][j]+dis[j][s2]);
            if(dis[t1][i]+dis[i][j]+dis[j][s1]<=l1&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2)
                ans=min(ans,dis[t1][i]+dis[j][s1]+dis[s2][i]+dis[i][j]+dis[j][t2]);
            if(dis[t1][i]+dis[i][j]+dis[j][s1]<=l1&&dis[t2][i]+dis[i][j]+dis[j][s2]<=l2)
                ans=min(ans,dis[t1][i]+dis[j][s1]+dis[t2][i]+dis[i][j]+dis[j][s2]);
        }
    printf("%d",m-ans);
    return 0;
}
```

码风很丑，将就着看吧/kk

---

## 作者：wfc284 (赞：0)

考虑先从简单情况，即只有一个 $s,t,l$ 的限制入手。  
我们求出 $s$ 到 $t$ 的最短路，这条路径无论从限制角度还是从最大删边的角度都是最优的。

现在考虑两个限制。  
这时，两条路径可能会有重复部分。我们用 BFS 预处理出全最短路径，然后枚举重复部分的起始点 $u$，终止点 $v$，检查是否满足限制，并求最大值。注意可能一条路径经过了 $u \to v$，而另一条路径经过了 $v \to u$；当然也可能没有重复部分。

这个做法的正确性有没有保障呢？有的。  
还是刚才的思路，最短路无论从什么角度思考，都是最优的。即最优情况不可能有多段不连续的重复，要不然就不符合一开始“考虑**最短路**的重合部分”的思路了。  
也就是，我们不考虑一定坏的情况。

时间复杂度 $O(n^2)$。  
[submission.](https://codeforces.com/contest/543/submission/305743419)

---

