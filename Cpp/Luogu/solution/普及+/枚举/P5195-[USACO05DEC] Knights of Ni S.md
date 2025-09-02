# [USACO05DEC] Knights of Ni S

## 题目描述

贝茜遇到了一件很麻烦的事：她无意中闯入了森林里的一座城堡，如果她想回家，就必须穿过这片由骑士们守护着的森林。为了能安全地离开，贝茜不得不按照骑士们的要求，在森林寻找一种特殊的灌木并带一棵给他们。

当然，贝茜想早点离开这可怕的森林，于是她必须尽快完成骑士们给的任务，贝茜随身带着这片森林的地图，地图上的森林被放入了直角坐标系，并按 $x,y $ 轴上的单位长度划分成了 $ W \times H\  ( 1 \leq W,H \leq 1000 )$ 块，贝茜在地图上查出了她自己以及骑士们所在的位置，当然地图上也标注了她所需要的灌木生长的区域。某些区域是不能通过的（比如说沼泽地，悬崖，以及食人兔的聚居地）。在没有找到灌木之前，贝茜不能通过骑士们所在的那个区域，为了确保她自己不会迷路，贝茜只向正北、正东、正南、正西四个方向移动（注意，她不会走对角线）。她要走整整一天，才能从某块区域走到与它相邻的那块区域。

贝茜希望你能帮她计算一下，她最少需要多少天才可脱离这可怕的地方？输入数据保证贝茜一定能完成骑士的任务。

## 说明/提示

这片森林的长为 $8$，宽为 $4$．贝茜的起始位置在第 $3$ 行，离骑士们不远。

贝茜可以按这样的路线完成骑士的任务：北，西，北，南，东，东，北，东，东，南，南。她在森林的西北角得到一株她需要的灌木，然后绕过障碍把它交给在东南方的骑士。

## 样例 #1

### 输入

```
8 4
4 1 0 0 0 0 1 0
0 0 0 1 0 1 0 0
0 2 1 1 3 0 4 0
0 0 0 4 1 1 1 0
```

### 输出

```
11```

# 题解

## 作者：Wenoide (赞：19)

给出一种只需一次 `BFS` 的做法。

用 $dis(x,y,0)$ 表示 **「到达点 $(x,y)$，但未取得灌木」** 所需的最短时间。

用 $dis(x,y,1)$ 表示 **「到达点 $(x,y)$，且已取得灌木」** 所需的最短时间。

在一般 `BFS` 的基础上增加对 **「是否已取得灌木」** 的判断即可。

参考代码：

```
#include<cstdio>
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
const int MAXN=1000+10;
int map[MAXN][MAXN];
struct Node{
	int x,y;
	bool tag;
	//tag 记录是否已取得灌木。
}que[MAXN*MAXN];
Node make(int x,int y,bool tag){
	Node t;
	t.x=x,t.y=y;
	t.tag=tag;
	return t;
}
int l,r;
int dis[MAXN][MAXN][2];
bool vis[MAXN][MAXN][2];
int ex,ey;
int main(){
	int w,h;
	scanf("%d%d",&w,&h);
	for(int i=1;i<=h;++i){
		for(int j=1;j<=w;++j){
			scanf("%d",&map[i][j]);
			if(map[i][j]==2){
				que[r++]=make(i,j,false);
				vis[i][j][0]=true;
			}
			if(map[i][j]==3){
				ex=i,ey=j;
			}
			//处理起点与终点。
		}
	}
	for(int i=1;i<=h;++i){
		map[i][0]=map[i][w+1]=1;
	}
	for(int j=1;j<=w;++j){
		map[0][j]=map[h+1][j]=1;
	}
	//处理边界。
	while(l!=r){
		Node t=que[l++];
		int x=t.x,y=t.y;
		bool tag=t.tag;
		if(x==ex&&y==ey&&tag){
			break;
		}
		//到达终点且取得灌木才能结束。
		for(int i=0;i<4;++i){
			int u=x+dx[i],v=y+dy[i];
			bool w=tag||(map[u][v]==4);
			//若此前已取得灌木，或当前位置长有灌木，则当前状态下已取得灌木。
			if(!vis[u][v][w]&&map[u][v]!=1){
				dis[u][v][w]=dis[x][y][tag]+1;
				vis[u][v][w]=true;
				que[r++]=make(u,v,w);
			}
		}
	}
	printf("%d",dis[ex][ey][1]);
	return 0;
}
```

---

## 作者：vеctorwyx (赞：12)

## 我被这道题坑了很久（~~现在感觉不难了~~）

仔细康康你会发现这~~其实就是道简单的广搜~~（我不会最短路径算法）

但是我最后发现~~好像并不要专门剪枝~~，只要你别想太多就行；

要注意的点：

1. 搜两边，一遍从贝茜开始（不能经过骑士的位置），另一遍从骑士的位置开始（除了障碍都能走）；

1.  搜索的时候要把所有灌木丛都找到最短路；

1.  搜索到一个灌木丛要标记成路（一开始标记成障碍了 [哭] ），但是在第二次搜索前要恢复（这个我一开始也忘了[哭*2]）；

1. 恢复方法最好是输入时标记好灌木丛的位置，到时候直接枚举每一丛的位置就行

1. 标记灌木丛位置用的结构体（数组）开大一点！！！**你永远不知道出题人在那里放了多少丛灌木**（我RE了）

最后**温馨提示** >▽<：找到灌木丛后别忘了continue( RE警告 )

然后上代码：
```
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
int m,n,sx,sy,ex,ey;
int dx[5]={0,-1,1,0,0};
int dy[5]={0,0,0,-1,1};
int a[1010][1010];
long long ji;
struct lol
{
	int x1,y1;
}guan_mu_cong[10000];
bool b[1010][1010];
long long ji1[1010][1010],ji2[1010][1010];
struct node
{
	int x,y,tim;
}qwq;
long long minn=0x7f7f7f7f;
queue<node>q;
int main()
{
	cin>>m>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]==2)
			{
				sx=i;
				sy=j;
			}
			else if(a[i][j]==3)
			{
				ex=i;
				ey=j;
			}
			else if(a[i][j]==4)
			{
				guan_mu_cong[++ji].x1=i;
				guan_mu_cong[ji].y1=j;
			}
		}
	}
	qwq.x=sx;
	qwq.y=sy;
	qwq.tim=0;
	q.push(qwq);
	while(!q.empty())
	{
		qwq=q.front();
		if(a[qwq.x][qwq.y]==4&&ji1[qwq.x][qwq.y]==0)
		{
			ji1[qwq.x][qwq.y]=qwq.tim;
			a[qwq.x][qwq.y]=0;
			q.pop();
			continue;
		}
		for(int i=1;i<=4;i++)
		{
			qwq=q.front();
			qwq.x+=dx[i];
			qwq.y+=dy[i];
			qwq.tim++;
			if(qwq.x>0&&qwq.x<=n&&qwq.y>0&&qwq.y<=m&&(a[qwq.x][qwq.y]==0||a[qwq.x][qwq.y]==4)&&b[qwq.x][qwq.y]==0)
			{
				q.push(qwq);
				b[qwq.x][qwq.y]=1;
			}
		}
		q.pop();
	}
	while(!q.empty())
	{
		q.pop();
	}
	for(int i=1;i<=ji;i++)
	a[guan_mu_cong[i].x1][guan_mu_cong[i].y1]=4;
	qwq.tim=0;
	qwq.x=ex;
	qwq.y=ey;
	q.push(qwq);
	memset(b,0,sizeof(b));
	while(!q.empty())
	{
		qwq=q.front();
		if(a[qwq.x][qwq.y]==4&&ji2[qwq.x][qwq.y]==0)
		{
			ji2[qwq.x][qwq.y]=qwq.tim;
			a[qwq.x][qwq.y]=0;
			q.pop();
			continue;
		}
		for(int i=1;i<=4;i++)
		{
			qwq=q.front();
			qwq.x+=dx[i];
			qwq.y+=dy[i];
			qwq.tim++;
			if(qwq.x>0&&qwq.x<=n&&qwq.y>0&&qwq.y<=m&&(a[qwq.x][qwq.y]!=1)&&b[qwq.x][qwq.y]==0)
			{
				q.push(qwq);
				b[qwq.x][qwq.y]=1;
			}
		}
		q.pop();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(ji1[i][j]&&ji2[i][j])
			minn=min(minn,ji1[i][j]+ji2[i][j]);
		}	
	}
	cout<<minn;
}
```
~~代码长也就100来行~~

祝各位dalao轻松AC这道~~水题~~

---

## 作者：那一条变阻器 (赞：10)

分层图题解很少啊，来个分层图哒

------------

这道题一开始看，我是想的跑两次最短路，一次从起点跑，一次从终点跑，然后枚举每一个灌木,但是因为起点的时候不能走骑士，所以会$WA$，只有$60$分。正解分层图最短路，在找到灌木的时候，向骑士那一层连一条边即可，从起点跑一遍最短路即可。

这里用的$SPFA$ ~~SPFA没有SPFA！！！~~:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n , m , s , tot , p;
int a[1010][1010]  , dis[2000010] , vis[2000010];
vector<int> e[2000010];
int id(int x , int y){	//二维压一维 
	return (x - 1) * m + y;
}
void add(int x , int y){
	e[x].push_back(y);
}
void spfa(int k){
	memset(dis , 127 , sizeof(dis));
	memset(vis , 0 , sizeof(vis));
	queue<int> q;
	vis[k] = 1;
	dis[k] = 0;
	q.push(k);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		vis[x] = 1;
		for(int i = 0; i < e[x].size(); i++){
			int nx = e[x][i];
			if(dis[nx] > dis[x] + 1){
				dis[nx] = dis[x] + 1;
				if(!vis[nx]){
					vis[nx] = 1;
					q.push(nx);
				}
			}
		}
	}
}
int main(){
	cin >> m >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1) continue;
			if(a[i][j] == 2) s = id(i , j);
			if(a[i][j] == 3) p = id(i , j);
			if(a[i][j] == 4) add(id(i , j) , id(i , j) + n * m);
			if((a[i - 1][j] == 0 || a[i - 1][j] == 2 || a[i - 1][j] == 4) && i != 1) add(id(i , j) , id(i - 1 , j));
			if((a[i + 1][j] == 0 || a[i + 1][j] == 2 || a[i + 1][j] == 4) && i != n) add(id(i , j) , id(i + 1 , j));
			if((a[i][j - 1] == 0 || a[i][j - 1] == 2 || a[i][j - 1] == 4) && j != 1) add(id(i , j) , id(i , j - 1));
			if((a[i][j + 1] == 0 || a[i][j + 1] == 2 || a[i][j + 1] == 4) && j != m) add(id(i , j) , id(i , j + 1));
			if((a[i - 1][j] == 0 || a[i - 1][j] == 2 || a[i - 1][j] == 4 || a[i - 1][j] == 3) && i != 1) add(id(i , j) + n * m , id(i - 1 , j) + n * m);	//向上一层连边 
			if((a[i + 1][j] == 0 || a[i + 1][j] == 2 || a[i + 1][j] == 4 || a[i + 1][j] == 3) && i != n) add(id(i , j) + n * m , id(i + 1 , j) + n * m);
			if((a[i][j - 1] == 0 || a[i][j - 1] == 2 || a[i][j - 1] == 4 || a[i][j - 1] == 3) && j != 1) add(id(i , j) + n * m , id(i , j - 1) + n * m);
			if((a[i][j + 1] == 0 || a[i][j + 1] == 2 || a[i][j + 1] == 4 || a[i][j + 1] == 3) && j != m) add(id(i , j) + n * m , id(i , j + 1) + n * m);
		}
	spfa(s);
	cout << dis[p + n * m] - 1;	//走向上一层的时候，花费了一天，减去 
	return 0;
}
```


---

## 作者：linaonao (赞：7)

---
## 思路
这是一道蓝色的题（=水题）

题目要求在图中一点$ST$到某些点$IS[i]$再到一点$ED$的最短距离，显然是双向搜索，这里我采用的是双向bfs。我们用双向bfs预处理出从$ST$出发和从$ED$出发到各点的最短距离$d1[x][y]$和$d2[x][y]$，最后循环求$min(d1[is[i].x][is[]i].y+d2[is[i].x][is[]i].y)$即可。

这里还有一个注意点，即bfs的过程中可以通过$d[u.x][u.y]+1>=d[xx][yy]$判断是否多次经过进行剪支。

## 代码
~~~cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f
using namespace std;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int n,m;
int ma[1005][1005],vis1[1005][1005],vis2[1005][1005];
int d1[1005][1005],d2[1005][1005];
int cnt;
struct node{
	int x,y;
}sta,to,is[1000005];
void bfs(){
	queue<node>q1,q2;
	q1.push(sta),q2.push(to);
	memset(d1,INF,sizeof(d1)); memset(d2,INF,sizeof(d2));
	d1[sta.x][sta.y]=0; vis1[sta.x][sta.y]=1;
	d2[to.x][to.y]=0; vis2[to.x][to.y]=1;
	while(!q1.empty()){
		node u=q1.front();q1.pop();
		for(int i=0;i<4;++i){
			int xx=u.x+dx[i],yy=u.y+dy[i];
			if(vis1[xx][yy]||xx<1||yy<1||xx>n||yy>m||ma[xx][yy]==1) continue;
			if(d1[u.x][u.y]+1>=d1[xx][yy])continue;
			vis1[xx][yy]=1;
			d1[xx][yy]=d1[u.x][u.y]+1;
			q1.push((node){xx,yy});
		}
	}
	while(!q2.empty()){
		node u=q2.front();q2.pop();
		for(int i=0;i<4;++i){
			int xx=u.x+dx[i],yy=u.y+dy[i];
			if(vis2[xx][yy]||xx<1||yy<1||xx>n||yy>m||ma[xx][yy]==1) continue;
			if(d2[u.x][u.y]+1>=d2[xx][yy])continue;
			vis2[xx][yy]=1;
			d2[xx][yy]=d2[u.x][u.y]+1;
			q2.push((node){xx,yy});
		}
	}
}
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&ma[i][j]);
			if(ma[i][j]==2)sta.x=i,sta.y=j;
			if(ma[i][j]==3)to.x=i,to.y=j;
			if(ma[i][j]==4)is[++cnt].x=i,is[cnt].y=j;
		}
	}
	bfs();
	int ans=INF;
	for(int i=1;i<=cnt;++i){
		ans=min(ans,d1[is[i].x][is[i].y]+d2[is[i].x][is[i].y]);
	}
	cout<<ans;
	return 0;
}
~~~
## 附
如果还想深入了解双端搜索可以去做做[P4799世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799)和[P3067Balanced Cow Subsets G](https://www.luogu.com.cn/problem/P3067)（因为这道题有点easy了）



---

## 作者：Diaоsi (赞：7)

## 题目链接：[传送门](https://www.luogu.org/problem/P5195)
【口胡】~~这种在矩阵里求最短路的模型很显然就是BFS~~
## 思路：
题目要求Bessie要在地图中找到一种特殊的灌木并且把他带给骑士，灌木可能有多个，但是起点和终点都只有一个

我们可以在读图的时候记录下起点和终点，以及每对灌木的坐标，
然后分别从起点和终点进行BFS，求出起点与终点到每从灌木的最短路径

将起点与终点到当前灌木丛的最短路径加起来就是起点经过该灌木到终点的最短路

然后再枚举先前记录下来的灌木丛的坐标，记录他们之中最短的一条就是答案
## 关于搜索：
### Tips1:最优性剪枝
我们可以在搜索的时候判断当前的路径答案是否小于原有的答案，如果当前是更优解就进行更新，否则就停止搜索，这样就可以剪去很多的搜索状态

$Code:$
```cpp
if(dist1[q[l].x][q[l].y]+1>=dist1[tx][ty])continue;
```
### Tips2:手写队列
~~众所周知stl的常数都很大~~

我们可以用一个结构体数组去实现一个队列，然后用两个变量分别表示队首和队尾，队首变量++就相当于pop，队尾边量++就相当于push，这样可以有效防止爆队列，而且重设一下队首和队尾变量就相当于清空了整个队列

$Code:$
```cpp
struct node1{int x,y;}q[M];
```
## 代 码 放 送：

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=10000010,INF=0x3f3f3f3f;
const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};
int g[N][N],dist1[N][N],dist2[N][N],l,r,cntk;
int n,m,sx,sy,ex,ey,kx[M],ky[M],minans=INF;
bool vis1[N][N],vis2[N][N];
struct node1{int x,y;}q[M];
void bfs1(){//搜索1 
	while(l<=r){
		for(int i=0;i<4;i++){
			int tx=q[l].x+dx[i];
			int ty=q[l].y+dy[i];
			if(tx<1||ty<1||tx>n||ty>m||vis1[tx][ty]||g[tx][ty]==1)continue;
			if(dist1[q[l].x][q[l].y]+1>=dist1[tx][ty])continue;//最优性剪枝
			q[++r].x=tx;q[r].y=ty;vis1[tx][ty]=1;
			dist1[tx][ty]=dist1[q[l].x][q[l].y]+1;
		}
		l++;
	}
}
void bfs2(){//搜索2 
	while(l<=r){
		for(int i=0;i<4;i++){
			int tx=q[l].x+dx[i];
			int ty=q[l].y+dy[i];
			if(tx<1||ty<1||tx>n||ty>m||vis2[tx][ty]||g[tx][ty]==1)continue;
			if(dist2[q[l].x][q[l].y]+1>=dist2[tx][ty])continue;//最优性剪枝 
			q[++r].x=tx;q[r].y=ty;vis1[tx][ty]=1;
			dist2[tx][ty]=dist2[q[l].x][q[l].y]+1;
		}
		l++;
	}
}
int main(){
	scanf("%d%d",&m,&n);
	memset(dist1,0x3f,sizeof(dist1));
	memset(dist2,0x3f,sizeof(dist2));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&g[i][j]);
			if(g[i][j]==2)sx=i,sy=j;//记录起点 
			if(g[i][j]==3)ex=i,ey=j;//记录终点 
			if(g[i][j]==4){kx[++cntk]=i;ky[cntk]=j;}//记录下每对灌木丛的编号 
		}
	l=r=1;
	q[l].x=sx;
	q[l].y=sy;
	dist1[sx][sy]=0;
	vis1[sx][sy]=1;
	bfs1();
	l=r=1;
	q[l].x=ex;
	q[l].y=ey;
	dist2[ex][ey]=0;
	vis1[ex][ey]=1;
	bfs2();
	for(int i=1;i<=cntk;i++)
		minans=min(minans,dist1[kx[i]][ky[i]]+dist2[kx[i]][ky[i]]);//找最小值 
	printf("%d\n",minans);
	return 0;
}
```


---

## 作者：杨铠远 (赞：5)

#### 好像都是两遍bfs或者dfs
#### 其实跑一遍分层图就可以了

在骑士处连接分层图，具体看代码
```cpp
//Code by : Y-k-y
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#define ll long long
const int N=10000010;
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
int n,m,sx,sy,tot;
int a[1005][1005];
struct pp{
	int v,nxt;
}edge[N];
int head[N],d[N],id[1004][1005];
bool ans[N];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool vis[N];
inline void add(int u,int v){
	edge[++tot].nxt=head[u],head[u]=tot;
	edge[tot].v=v;
}
inline int chk(int x,int y){
	return x>0&&x<=n&&y>0&&y<=m&&a[x][y]!=1;
}
inline int num(int x,int y){
	return (x-1)*m+y;
}
inline void spfa(){
	queue<int>q;
	q.push(id[sx][sy]);vis[id[sx][sy]]=1;
	memset(d,0x3f,sizeof(d));
	d[id[sx][sy]]=0;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}
int main(){
	cin>>m>>n;//n m的顺序。。。 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		a[i][j]=rnd(),id[i][j]=num(i,j);//类似hash吧 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1)continue;
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(chk(x,y)){
					add(id[i][j],id[x][y]);
					add(id[i][j]+n*m,id[x][y]+n*m);//两个图上都要连边 
				}
			}
			if(a[i][j]==4){
				add(id[i][j],id[i][j]+n*m);//骑士，连接两个图 
			}
			if(a[i][j]==3){
				ans[id[i][j]]=1;
			}
			if(a[i][j]==2){
				sx=i,sy=j;
			}
		}
	}
	spfa();
	int sum=1<<30;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ans[id[i][j]]){
				sum=min(sum,d[id[i][j]+n*m]);
			}
		}
	}
	wr(sum-1);//因为在跳图的时候，也算了一个距离，所以减一 
	return 0;
}
```


---

## 作者：Ofnoname (赞：3)

路径一定是“起点(2) → 宝藏点(4) → 终点(3)”。

那么我们以2作为起点，进行一次广搜，求出2到每个点的最短距离`f0[]`。再以3作为起点，求出3到每个点的最短距离`f1[]`。那么对于每一个值为4的点(x, y)，答案就是`f0[x][y] + f1[x][y]`取最小值即可。

需要注意，第一次搜索是不能经过3的，而第二次搜索可以经过2。而也并不是每个“4”点都能到达，所以可以将广搜答案数组初始化为`inf`。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define MAX (1000 + 7)
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int N, M, Stx, Sty, Edx, Edy, ans = 1e9, a[MAX][MAX], f0[MAX][MAX], f1[MAX][MAX];

void BFS(int f[MAX][MAX], int x0, int y0)
{
	queue <int> Qx, Qy;
	Qx.push(x0), Qy.push(y0), f[x0][y0] = 0;
	while (Qx.size())
	{
		int x = Qx.front(); Qx.pop();
		int y = Qy.front(); Qy.pop();
		for (int i = 0; i < 4; i++)
		{
			int ix = x + dx[i], iy = y + dy[i];
			if (ix && iy && ix<=N && iy<=M && f[ix][iy]==inf && !(a[ix][iy]&1))
			{//a[ix][iy]为奇数，就是可以通行的情况（0，2，4）
				f[ix][iy] = f[x][y] + 1;
				Qx.push(ix), Qy.push(iy);
			}
		}
	}
}

int main()
{
	scanf("%d%d", &M, &N);
	memset(f0, 0x3f, sizeof f0);
	memset(f1, 0x3f, sizeof f1);//初始化为inf
	for (int x = 1; x <= N; x++)
	for (int y = 1; y <= M; y++)
	{
		scanf("%d", &a[x][y]);
		if (a[x][y] == 2) Stx = x, Sty = y;
		if (a[x][y] == 3) Edx = x, Edy = y;
	}
	a[Stx][Sty] = 0, BFS(f0, Stx, Sty);//第一次广搜不能经过(Edx, Edy)
	a[Edx][Edy] = 0, BFS(f1, Edx, Edy);//第二次广搜可以经过(Stx, Sty)，先将(Edx, Edy)赋为0
	for (int x = 1; x <= N; x++)
	for (int y = 1; y <= M; y++)
		if (a[x][y] == 4) ans = min(ans, f0[x][y] + f1[x][y]);
	printf("%d\n", ans);
}
```

---

## 作者：Na2PtCl6 (赞：2)

~~为什么你们的代码又短跑得又快啊~~

---

## 分析题目
据题意 ， bessie 的行走路线应该是: 起点 $\rightarrow$ 灌木丛 $\rightarrow$ 骑士

所以这就变成了一个求**两段路程之和最小值**的问题了

## 代码

### 第一段路程(起点 $\rightarrow$ 灌木丛)
我们用 bfs 枚举出 bessie 到每个灌木的最短路径，并用数组递推优化，避免走重复的路。

剪枝：如果已经到过了所有的灌木就结束。

```
void bfs1(int str,int stc){
	int cnt=0;  //记录到过的灌木数量 
	queue < point > q;
	q.push((point){str,stc});
	vis[str][stc]=1;
	while(!q.empty()){
		point fr=q.front();
		q.pop();
		if(fo[fr.h][fr.l]==4){
			++cnt;
			if(cnt==bush.size())  //如果到过的灌木数量等于灌木的总数就退出 
				return ;
		}
		for(int i=0;i<4;i++){
			const int nr=fr.h+d1[i],nc=fr.l+d2[i];
			if(nr>0&&nr<=w&&nc>0&&nc<=h&&!vis[nr][nc]){
				vis[nr][nc]=1;
				q.push((point){nr,nc});
				//bessie到现在所在的点的路程为到上一步的路程加一 
				len1[nr][nc]=len1[fr.h][fr.l]+1;   
			}
		}
	}
}

```
时间复杂度 $\leq O(wh)$ , 完全可以接受。

### 第二段路程（灌木丛 $\rightarrow$ 骑士）
类似地，我们用 bfs 枚举出每个灌木丛到每个骑士的最短路径，并用数组递推优化，避免走重复的路。

剪枝：如果已经到过了所有的骑士就结束。

```
void bfs2(int str,int stc,int ori){ 
	int cnt=0;  //记录到过的其实个数 
	queue < point > q;
	q.push((point){str,stc});
	//记录搜过的点,搜完要删掉在这些点上做的改动 
	vector < point > mem;   
	mem.push_back((point){str,stc});
	vis[str][stc]=1;len2[str][stc]=ori;
	while(!q.empty()){
		point fr=q.front();
		q.pop();
		if(fo[fr.h][fr.l]==3){
			++cnt;
			int comp=len2[fr.h][fr.l];
			res=res<comp?res:comp;
			if(cnt==kn){  //如果到过的骑士数量等于骑士的总数就退出 
				//搜完之后删除标记这次搜索的结果,否则会影响下一次搜索 
				for(int i=0;i<mem.size();i++){
					point now=mem[i];
					vis[now.h][now.l]=0;
					len2[now.h][now.l]=0;
				}
				return ;
			}
		}
		for(int i=0;i<4;i++){
			const int nr=fr.h+d1[i],nc=fr.l+d2[i];
			if(nr>0&&nr<=w&&nc>0&&nc<=h&&!vis[nr][nc]){
				vis[nr][nc]=1;
				mem.push_back((point){nr,nc});
				q.push((point){nr,nc});
				//和bfs1函数一样的数组递推 
				len2[nr][nc]=len2[fr.h][fr.l]+1;
			}
		}
	}
}
```

设灌木丛的数量为 $s$ , 因为要枚举出每一个树丛到每一个骑士的距离,即进行 $s$ 次这样的 bfs ，所以时间复杂度 $\leq O(swh)$ ， 如果数据比较强是会 GG 的。

### 完整代码
```
#include<bits/stdc++.h>
using namespace std;
const char d1[]={0,0,-1,1},d2[]={-1,1,0,0};
const int maxn=1004,inf=0x7fffffff;
char fo[maxn][maxn],vis[maxn][maxn];
int h,w,kn,res=inf,len1[maxn][maxn],len2[maxn][maxn];
struct point{ int h,l;}bessie;
vector < point > bush;

char read(){  //快读 
	char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	return (c^48);
}

void bfs1(int str,int stc){
	int cnt=0;  //记录到过的灌木数量 
	queue < point > q;
	q.push((point){str,stc});
	vis[str][stc]=1;
	while(!q.empty()){
		point fr=q.front();
		q.pop();
		if(fo[fr.h][fr.l]==4){
			++cnt;
			if(cnt==bush.size())  //如果到过的灌木数量等于灌木的总数就退出 
				return ;
		}
		for(int i=0;i<4;i++){
			const int nr=fr.h+d1[i],nc=fr.l+d2[i];
			if(nr>0&&nr<=w&&nc>0&&nc<=h&&!vis[nr][nc]){
				vis[nr][nc]=1;
				q.push((point){nr,nc});
				//bessie到现在所在的点的路程为到上一步的路程加一 
				len1[nr][nc]=len1[fr.h][fr.l]+1;   
			}
		}
	}
}

void bfs2(int str,int stc,int ori){ 
	int cnt=0;  //记录到过的其实个数 
	queue < point > q;
	q.push((point){str,stc});
	//记录搜过的点,搜完要删掉在这些点上做的改动 
	vector < point > mem;   
	mem.push_back((point){str,stc});
	vis[str][stc]=1;len2[str][stc]=ori;
	while(!q.empty()){
		point fr=q.front();
		q.pop();
		if(fo[fr.h][fr.l]==3){
			++cnt;
			int comp=len2[fr.h][fr.l];
			res=res<comp?res:comp;
			if(cnt==kn){  //如果到过的骑士数量等于骑士的总数就退出 
				//搜完之后删除标记这次搜索的结果,否则会影响下一次搜索 
				for(int i=0;i<mem.size();i++){
					point now=mem[i];
					vis[now.h][now.l]=0;
					len2[now.h][now.l]=0;
				}
				return ;
			}
		}
		for(int i=0;i<4;i++){
			const int nr=fr.h+d1[i],nc=fr.l+d2[i];
			if(nr>0&&nr<=w&&nc>0&&nc<=h&&!vis[nr][nc]){
				vis[nr][nc]=1;
				mem.push_back((point){nr,nc});
				q.push((point){nr,nc});
				//和bfs1函数一样的数组递推 
				len2[nr][nc]=len2[fr.h][fr.l]+1;
			}
		}
	}
}

int main(){
	scanf("%d %d",&h,&w);  //颠倒顺序，方便后面的操作 
	for(int i=1;i<=w;i++)
		for(int j=1;j<=h;j++){
			fo[i][j]=read();
			if(fo[i][j]==2)  //记录起始位置 
				bessie.h=i,bessie.l=j;
			if(fo[i][j]==3)  //骑士数量 
				++kn;
			if(fo[i][j]==4)  //灌木丛 
				bush.push_back((point){i,j});
		}
	for(int i=1;i<=w;i++)
		for(int j=1;j<=h;j++)
			vis[i][j]=(fo[i][j]==1)?1:0;
	bfs1(bessie.h,bessie.l);
	//下面4行的作用是重新整理vis数组,避免影响之后的搜索 
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=w;i++)
		for(int j=1;j<=h;j++)
			vis[i][j]=(fo[i][j]==1)?1:0;
	//枚举每个灌木到骑士的距离 
	for(int i=0;i<bush.size();i++){
		point now=bush[i];
		if(len1[now.h][now.l])
			bfs2(now.h,now.l,len1[now.h][now.l]);
	}
	printf("%d",res);
	return 0;
}
```
~~代码不长，刚过百行(指不加注释前)~~

---

## 作者：06ray (赞：2)

$BFS$水题

先用$BFS$求出起点与终点到其他点的最短距离，然后在枚举每个沼泽，把每个沼泽到终点与起点的最短距离相加，最后打个擂台求最小的就是答案。

话不多说，上代码：

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
struct map{
	int x,y;
};
int dis1[1010][1010],dis2[1010][1010];//dis1表示从起点到其它点的最短路，dis2表示从终点到其它点的最短路
int a[1010][1010];//森林地图
int n,m,x1,y1,x2,y2;
const int way[4][2]={{0,-1},{-1,0},{1,0},{0,1}};
void bfs(int x,int y)
{
	memset(dis1,50,sizeof(dis1));//初始化
	queue<map>q;
	q.push((map){x,y});
	dis1[x][y]=0;
	while(!q.empty())
	{
		map v=q.front();
		q.pop();
		for(int i=0; i<4; i++)
		{
			int nx=v.x+way[i][0],ny=v.y+way[i][1];//枚举下一个点
			if(nx<1||nx>n||ny<1||ny>m) continue;//防止越界
			if(a[nx][ny]==1) continue;//这个点一定要是可走的点
			if(dis1[v.x][v.y]+1<dis1[nx][ny])
			{
				dis1[nx][ny]=dis1[v.x][v.y]+1;
				q.push((map){nx,ny});
			}
		}
	}
}
void bfs2(int x,int y)//同上
{
	memset(dis2,50,sizeof(dis2));
	queue<map>q;
	q.push((map){x,y});
	dis2[x][y]=0;
	while(!q.empty())
	{
		map v=q.front();
		q.pop();
		for(int i=0; i<4; i++)
		{
			int nx=v.x+way[i][0],ny=v.y+way[i][1];
			if(nx<1||nx>n||ny<1||ny>m) continue;
			if(a[nx][ny]==1) continue;
			if(dis2[v.x][v.y]+1<dis2[nx][ny])
			{
				dis2[nx][ny]=dis2[v.x][v.y]+1;
				q.push((map){nx,ny});
			}
		}
	}
}
int main()
{
	cin>>m>>n;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			cin>>a[i][j];
			if(a[i][j]==2)
			{
				x1=i,y1=j;//起点
			}
			if(a[i][j]==3)
			{
				x2=i,y2=j;//终点
			}
		}
	}
	bfs(x1,y1);
	bfs2(x2,y2);
	int ans=2000000000;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(a[i][j]==4)
			{
				ans=min(ans,dis1[i][j]+dis2[i][j]);//打擂台
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：chichichichi (赞：1)

链接：[P5195](https://www.luogu.com.cn/problem/P5195)

题目大意：求A - > B 经过 C 的最短路径

最短路当然要用最短路来求！

**此类有中间点的最短路可以用正反两遍最短路，最后枚举中间点求和来解决，在有向图中需要建反图，这道题中可以直接跑反向**

要不说这是道蓝 ~~（水）~~ 题呢
 

- 读入
	
    邻接表存图信息
    
	记录 **A **点和 **B** 点信息
    
    因为灌木丛并不唯一，使用一个数组记录所有**C**点的信息
    
    

- 最短路求得

   **F [ i ]**：A点到 i 点的最短路径长度
   
   **D [ i ]**：B点到 i 点的最短路径长度

- 因为灌木丛并不唯一，读入时使用一个数组记录所有**C**点的信息最后的答案只需枚举**C**点的集合中每一个点

	ans = max { F[ i ]+D[ i ] } 
    
   

 
 
 存图的时候有一个小技巧 ~~（大家都会的吧）~~
 
 在邻接表中，点的序号可以用  _(x-1)*m+y_  来表示
 
 这样每个点的序号都是唯一的
 
 下面是（奇丑无比的）代码
 ```cpp
 #include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e3+200;
const int maxm=1e6+200;
const int dx[]={0,0,1,-1};
const int dy[]={-1,1,0,0};
int n,m,cnt,ans;
int a[maxn][maxn],f[maxm],vis[maxm],d[maxm];
struct node{
	int x,y;
}p,t,mi[maxm];
priority_queue<pair<int,int> > q,e;
void dij1(int x,int y)
{
	memset(f,0x3f,sizeof(f));
	int s=(x-1)*m+y;
	f[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int w=q.top().second;
		q.pop();
		if(vis[w]==1)
		continue;
		vis[w]=1;
		int y=w%m;
		if(y==0)
		y=m;
		int x=(w-y)/m+1;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx>0&&xx<=n&&yy>0&&yy<=m)//判边界
				if(a[xx][yy]!=1)
				{
					int ww=(xx-1)*m+yy;
					if(f[ww]>f[w]+1)
					{
					f[ww]=f[w]+1;
					q.push(make_pair(-f[ww],ww));
					}
				}
		}
	}
}
void dij2(int x,int y)
{
	swap(e,q);
	memset(d,0x3f,sizeof(d));
	memset(vis,0,sizeof(vis));
	int s=(x-1)*m+y;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int w=q.top().second;
		q.pop();
		if(vis[w]==1)
		continue;
		vis[w]=1;
		int y=w%m;
		if(y==0)
		y=m;
		int x=(w-y)/m+1;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx>0&&xx<=n&&yy>0&&yy<=m)
			{
				if(a[xx][yy]!=1)
				{
					int ww=(xx-1)*m+yy;
					if(d[ww]>d[w]+1)
					{
						d[ww]=d[w]+1;
						q.push(make_pair(-d[ww],ww));
					}
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
		scanf("%d",&a[i][j]);//读入
		if(a[i][j]==2)
		 	p.x=i,p.y=j;
		if(a[i][j]==3)
			t.x=i,t.y=j;
		if(a[i][j]==4)
			mi[++cnt].x=i,mi[cnt].y=j;
	}
	dij1(p.x,p.y);
	dij2(t.x,t.y);
	ans=0x3f3f3f3f;
	for(int i=1;i<=cnt;i++)
		{
			int s=(mi[i].x-1)*m+mi[i].y;
			ans=min(ans,d[s]+f[s]);
	}
	printf("%d",ans);
	return 0;
}
```




---

## 作者：2017gdgzoi999 (赞：1)

普通的BFS

跑两次，分别是奶牛到灌木，骑士到灌木(其实是灌木到骑士)。

最后枚举灌木，取距离之和的最小值输出。

以下细节：

- 镶边：防止BFS时数组越界，把边界外的visited都设为true。

- 初始化：不是起点的最短距离都设为INF

不然后果很严重：

```
0 0 0 1 4
0 4 0 1 0
0 0 0 1 0
1 1 1 1 0
3 2 0 0 0
```

如上图，奶牛找不到的灌木的dis都为0，导致错误的输出。

- 注意题面！

小细节：

> 在没有找到灌木之前，贝茜不能通过骑士们所在的那个区域

所以对于奶牛到灌木而言，骑士位置的visited要变成true!

最后几乎没难度了，裸的BFS

样例:

```cpp
8 4
4 1 0 0 0 0 1 0
0 0 0 1 0 1 0 0
0 2 1 1 3 0 4 0
0 0 0 4 1 1 1 0
```

可以看出输入的第一个数是列数,而不是行数.


```cpp
#include <iostream>
#include <cstdio>
#include <queue>

#define SIZE 1010
#define INF 1e+09

using namespace std;

struct node
{
    int x, y;
};

queue<node> q, q2; // 队列,BFS用
int dis[SIZE][SIZE], dis2[SIZE][SIZE], a[SIZE][SIZE]; // 距离和原数组
bool visited[SIZE][SIZE], visited2[SIZE][SIZE]; // 是否访问过
int dx[4] = {0, 0, 1, -1}; // 四个方向
int dy[4] = {1, -1, 0, 0};

int main(void)
{
    int n, m, i, j, x, y, r, c, res = INF;
    
    scanf("%d%d", &m, &n); // 注意是反的!
    for (i = 1; i <= n; ++i)
    {
        visited[i][0] = visited[i][m+1] = visited2[i][0] = visited2[i][m+1] = true; // 镶边
        for (j = 1; j <= m; ++j)
        {
            dis[i][j] = dis2[i][j] = INF; // 一开始我们认为它和起点不连通,即距离为INF
            visited[0][j] = visited[n+1][j] = visited2[0][j] = visited2[n+1][j] = true; // 镶边
            scanf("%d", &a[i][j]);
            if (a[i][j] == 1) // 障碍物
            {
                visited[i][j] = visited2[i][j] = true;
            }
            else if (a[i][j] == 2) // 奶牛的起点
            {
                visited[i][j] = true; // 标记奶牛走过
                dis[i][j] = 0;
                q.push({i, j});
            }
            else if (a[i][j] == 3) // 骑士的起点
            {
                dis2[i][j] = 0;
                visited[i][j] = visited2[i][j] = true; // 骑士走过,奶牛到灌木的路程中也不能走
                q2.push({i, j});
            }
        }
    }
    
    while (!q.empty()) // 奶牛到灌木跑BFS
    {
        x = q.front().x;
        y = q.front().y;
        q.pop();
        for (i = 0; i < 4; ++i) // 枚举四个方向
        {
            r = x + dx[i]; // 目标点
            c = y + dy[i];
            if (!visited[r][c]) // 如果没有被走过或走到这个点合法
            {
                dis[r][c] = dis[x][y] + 1; // 计算距离
                visited[r][c] = true; // 标记为走过
                q.push({r, c});
            }
        }
    }
    while (!q2.empty()) // 骑士到灌木跑BFS,注释同上
    {
        x = q2.front().x;
        y = q2.front().y;
        q2.pop();
        for (i = 0; i < 4; ++i)
        {
            r = x + dx[i];
            c = y + dy[i];
            if (!visited2[r][c])
            {
                dis2[r][c] = dis2[x][y] + 1;
                visited2[r][c] = true;
                q2.push({r, c});
            }
        }
    }
    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= m; ++j)
        {
            if (a[i][j] == 4) // 枚举所有的灌木
            {
                res = min(res, dis[i][j] + dis2[i][j]); // 计算从奶牛到灌木和灌木到骑士的距离之和的最小值
            }
        }
    }
    
    printf("%d", res);
    
    return 0;
}
```

---

## 作者：whale142857 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5195)

这种网格图上走的题一般是用bfs的，这道题直接裸的bfs跑满整张图复杂度为$1000 \times 1000 \times 2 = 2e6$，貌似可以过，不过这里讲一下双向bfs，可以降低搜索树的规模~~就是让你跑得更快~~

题目需要你从起点去拿到图中的好东西给另一个地方的骑士们，~~显然~~在你跑图的时候骑士也可以来找你，如果你和骑士相遇了，并且你和骑士任意一人拿到了好东西，那就可以结束搜索了，如果没有，则继续走。

在bfs的时候分别记录从你和骑士开始跑图扩展的状态的个数，每次选择小的扩展，这是为了平衡两棵搜索树的大小，即平衡你的时间复杂度。

还要记录每个点的状态，分别是，从起点走到那里，没有好东西；从起点走到那里，有好东西；从终点走到那里，没有好东西；从终点走到那里，有好东西。对于当前状态走过的地方就不要再去走了，因为那个点已经被扩展过了，说明之前先走过那个点，并且步数比这次走到的要少。

当然，遇到障碍不能走

对于结束的判断，只要走到了对方走过的路径，并且至少一方拿到了好东西时结束


详见代码：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>


using namespace std;


const int maxN = 1010;


struct Poi{		// 从对应起点走到x行 y列的步数为step，have为1时拿到了好东西
	int x,y,step;
	bool have;
};
int N,M,data[maxN][maxN],qx,qy,zx,zy,spe,sps;		//spe为从终点开始走扩展的状态数，sps为从起点开始走扩展的状态数
int b[maxN][maxN][4];		//判重
int mx[4] = {-1,0,1,0},my[4] = {0,1,0,-1};


void bfs() {
	queue<Poi> queues,queuee;
	queues.push((Poi){qx,qy,0,0});
	queuee.push((Poi){zx,zy,0,0});
	int x,y,step;
	bool have;
	memset(b,-1,sizeof(b));
	b[qx][qy][0] = 0;
	b[zx][zy][2] = 0;
	while(!queues.empty() or !queuee.empty()) {
		if(spe > sps and queues.size()) {		//从起点扩展
			x = queues.front().x;
			y = queues.front().y;
			step = queues.front().step;
			have = queues.front().have;
			queues.pop();
            
			if(b[x][y][2] != -1 and have) {
				printf("%d",b[x][y][2] + step);
				return;
			}
			if(b[x][y][3] != -1) {
				printf("%d",b[x][y][3] + step);
				return;				
			}//相遇了，结束搜索
            
			for(int i = 0;i < 4;i += 1) {
				int h = have;
				int X = x + mx[i],Y = y + my[i];
				if(X > N or X < 1 or Y > M or Y < 1) continue;
				if(data[X][Y] == 1) continue;
				if(!have and data[X][Y] == 3) continue;
				if(data[X][Y] == 4) h = 1;
				if(b[X][Y][0 + h] != -1) continue;
				b[X][Y][0 + h] = step + 1;
				queues.push((Poi){X,Y,step + 1,h});
				sps += 1;
			}
		}
		else {		//从终点扩展
			x = queuee.front().x;
			y = queuee.front().y;
			step = queuee.front().step;
			have = queuee.front().have;
			queuee.pop();
            
			if(b[x][y][0] != -1 and have) {
				printf("%d",b[x][y][0] + step);
				return;
			}
			if(b[x][y][1] != -1) {
				printf("%d",b[x][y][1] + step);
				return;				
			}相遇了，结束搜索
            
			for(int i = 0;i < 4;i += 1) {
				int h = have;
				int X = x + mx[i],Y = y + my[i];
				if(X > N or X < 1 or Y > M or Y < 1) continue;
				if(data[X][Y] == 1) continue;
				if(!have and data[X][Y] == 3) continue;
				if(data[X][Y] == 4) h = 1;
				if(b[X][Y][2 + h] != -1) continue;
				b[X][Y][2 + h] = step + 1;
				queuee.push((Poi){X,Y,step + 1,h});
				spe += 1;
			}
		}
	}
}


int main() {
	scanf("%d %d",&M,&N);
	for(int i = 1;i <= N;i += 1) {
		for(int q = 1;q <= M;q += 1) {
			scanf("%d",&data[i][q]);
			if(data[i][q] == 2) qx = i,qy = q;
			if(data[i][q] == 3) zx = i,zy = q;
		}
	}
	bfs();
	return 0;
}
```


---

## 作者：edr_saverr (赞：0)


[题目链接](https://www.luogu.com.cn/problem/P5195)

### 可以采用BFS求最短路径的方式
~~这样大部分 luogu 的朋友们都能理解~~（这不是重点），而且在数据范围之内，能用搜素尽量使用搜素。

#### WARNING
为了防止抄题解，只放部分代码，并且x,y反写 ~~(滑稽)~~。
**如果你是为了** ~~抄题解~~ **请看其他dalao的题解q**。

## 思路
思路大致分为

### 第一步 输入
采用**矩阵** $vis$ 的方式存图，并用 $dis1$ , $dis2$ 存路径(下面会 ~~详细~~ 叙述)。如果为了节省空间完全可以用 **char** 数据类型来存储每一个单元格内的情况。~~不过完全没有这个必要q~~。~~<----废话真多！~~

接着定义两个数组 dx[] , dy[]。 

安利一手快读板子(qwq)
```cpp
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;}
```

下面就是输入和存储的部分：(手写队列yyds)
```cpp
int vis[maxn][maxn];
int dis1[maxn][maxn];
int dis2[maxn][maxn];
bool gone[maxn][maxn];
int w,h;
int ox,oy,kx,ky;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,1,-1};
struct str{
	int x,y,step;
}q[maxm];
int head, tail;
int main(){
	w = read(),h = read();
	for(ri i=1;i<=h;i++){
		for(ri j=1;j<=w;j++){
			scanf("%d"，&vis[i][j]);
			if(vis[i][j]==2) {ox=j,oy=i；}
			if(vis[i][j]==3) {kx=j,ky=i；}
		}
	}
	memset(dis1,-1,sizeof(dis1))；
	memset(dis2,-1,sizeof(dis2))；//CE
```
### 第二步 BFS环节
采用两次BFS从骑士和贝茜的位置分别搜索，过程中每走过的路都把走过的路标记为 $5$ ，走过的灌木标记为 $6$ 方便在第二次 $bfs$ 的时候还原。**注意！BFS的时候是不能通过骑士的位置的！因为题目说过：**

	"在没有找到灌木之前，贝茜不能通过骑士们所在的那个区域。"
    
**所以骑士的位置也要被排除掉。**

不能通过的标记有 $1$ , $2$ , $3$ , $5$ , $6$ 。

并且刚开始的位置全都设置为"-1"以便后面查询这个地方有没有被标记过。

求最优解的bfs递推式是这样的:
```cpp
if(nx<=0 || ny<=0 || nx>w || ny>h || (vis[ny][nx]!=0 && vis[ny][nx]!=4) || gone[ny][nx] )continue;
			if(dis1[ny][nx] <= q[head].step+1 && dis1[ny][nx]!=-1)
				continue;
			dis1[ny][nx]=q[head].step+1;
```
(因为调试的时候 ~~死活~~ 过不去，所以写了 $step$ ， $gone$ ， 之类的东西，实则都可以不用写)

然后可以写出这样的代码。
```cpp
void bfs1 (){
	q[tail].x = ox, q[tail].y = oy, q[tail++].step = 0;
	while(tail > head){
		for(ri i=0;i<4;++i){
			int nx=q[head].x+dx[i],
				ny=q[head].y+dy[i];
			if(nx<=0 || ny<=0 || nx>w || ny>h || (vis[nx][ny]!=0 && vis[nx][ny]!=4) || gone[nx][ny] )continue;
			if(dis1[nx][ny] <= q[head].step+1 && dis1[nx][ny]!=-1)
				continue;
			dis1[nx][ny]=q[head].step+1;
			q[tail].x=nx;
			q[tail].y=ny;
			q[tail].step=q[head].step+1;
			tail++;
			gone[nx][ny]=1；//CE
		}
		head++;
	}
	return;
   //x,y是反的qwq
}
```
### 第三步 还原
bfs1()之后
还原部分就是把 $q$ , $gone$ 等数组还原。 **别忘了把head,tail指针还原**。
代码
```cpp
memset(q,0,sizeof(q));
	head=0,tail=0;
	memset(gone,0,sizeof(gone));
```
接着bfs2()就好了， bfs2() 的样式几乎和 bfs1() 完全一致这里就不放出来了。
### 第四步 输出
只需要找出所有的灌木的位置，并把灌木位置的 $dis1$ , $dis2$相加，取出最小的就可以了。
```cpp
int minn=INF;
	for(ri i=1;i<=h;i++)
		for(ri j=1;j<=w;j++)
			if(vis[i][j]==4 && dis1[i][j]!=-1 && dis2[i][j]!=-1){
				minn=min(minn,dis1[i][j]+dis2[i][j]);
			}
```
## 最后就可以AC啦！
祝愿大家各种ak!

---

## 作者：封禁用户 (赞：0)

这道题目。。。明显的搜索题啊。。。

先算出到灌木丛的距离，再加上到骑士的距离或者是先到灌木丛，然后直接去骑士地方。

就是这么简单。。。

$\rm C++$代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1001
struct target
{
	int x,y;
} t[N*N];
struct queue
{
	int x,y;
} q[N*N];
int dicx[4]={0,1,0,-1},dicy[4]={1,0,-1,0};
int n,m,cnt,x1,y1,x2,y2,head,tail,ans=100000000;
int a[N][N],dis1[N][N],dis2[N][N];
bool f[N][N];
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void bfs1(int x,int y)
{
	head=0;
	tail=1;
	f[x][y]=1;
	q[1].x=x;
	q[1].y=y;
	while (head<tail)
	{
		head++;
		int nx=q[head].x,ny=q[head].y;
		for (int i=0; i<4; i++)
		{
			int xx=nx+dicx[i],yy=ny+dicy[i];
			if (xx<1||xx>n||yy<1||yy>m)continue;
			if (f[xx][yy]||a[xx][yy]==1) continue;
			dis1[xx][yy]=dis1[nx][ny]+1;
			q[++tail].x=xx;
			q[tail].y=yy;
			f[xx][yy]=1;
		}
	}
}
void bfs2(int x,int y)
{
	memset(q,0,sizeof(q));
	memset(f,0,sizeof(f));
	head=0;
	tail=1;
	f[x][y]=1;
	q[1].x=x;
	q[1].y=y;
	while (head<tail)
	{
		head++;
		int nx=q[head].x,ny=q[head].y;
		for (int i=0; i<4; i++)
		{
			int xx=nx+dicx[i],yy=ny+dicy[i];
			if (xx<1||xx>n||yy<1||yy>m)continue;
			if (f[xx][yy]||a[xx][yy]==1) continue;
			dis2[xx][yy]=dis2[nx][ny]+1;
			q[++tail].x=xx;
			q[tail].y=yy;
			f[xx][yy]=1;
		}
	}
}
int main()
{
	m=read();
	n=read();
	for (int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			a[i][j]=read();
			if (a[i][j]==4)
			{
				t[++cnt].x=i;
				t[cnt].y=j;
			}
			else if (a[i][j]==2)
			{
				x1=i;
				y1=j;
				a[i][j]=0;
			}
			else if (a[i][j]==3)
			{
				x2=i;
				y2=j;
				a[i][j]=0;
			}
		}
	bfs1(x1,y1);
	bfs2(x2,y2);
	for (int i=1; i<=cnt; i++)
	{
		int nx=t[i].x,ny=t[i].y;
		if (!(dis1[nx][ny]+dis2[nx][ny])) continue;
		ans=min(ans,dis1[nx][ny]+dis2[nx][ny]);
	}
	printf("%d\n",ans);
}
```

$\rm Pascal$代码：
```pas
const dx:array[1..4]of longint=(-1,1,0,0);
      dy:array[1..4]of longint=(0,0,-1,1);
var n,m,x1,y1,x2,y2,t,i,j,min:longint;
    a,c,d:array[1..1000,1..1000]of longint;
    b,e:array[1..1000000,1..2]of longint;
    f:array[1..1000,1..1000]of boolean;
procedure bfs1(x,y:longint);
var nx,ny,k,head,tail:longint;
begin
  head:=0;
  tail:=1;
  f[x,y]:=true;
  e[1,1]:=x;
  e[1,2]:=y;
  while head<tail do
    begin
      head:=head+1;
      for k:=1 to 4 do
        begin
          nx:=e[head,1]+dx[k];
          ny:=e[head,2]+dy[k];
          if (nx>0)and(nx<=n)and(ny>0)and(ny<=m) then
            if a[nx,ny]<>1 then
              if not f[nx,ny] then
                begin
                  tail:=tail+1;
                  e[tail,1]:=nx;
                  e[tail,2]:=ny;
                  f[nx,ny]:=true;
                  c[nx,ny]:=c[e[head,1],e[head,2]]+1;
                end;
        end;
    end;
end;
procedure bfs2(x,y:longint);
var nx,ny,k,head,tail:longint;
begin
  head:=0;
  tail:=1;
  f[x,y]:=true;
  e[1,1]:=x;
  e[1,2]:=y;
  while head<tail do
    begin
      head:=head+1;
      for k:=1 to 4 do
        begin
          nx:=e[head,1]+dx[k];
          ny:=e[head,2]+dy[k];
          if (nx>0)and(nx<=n)and(ny>0)and(ny<=m) then
            if a[nx,ny]<>1 then
              if not f[nx,ny] then
                begin
                  tail:=tail+1;
                  e[tail,1]:=nx;
                  e[tail,2]:=ny;
                  f[nx,ny]:=true;
                  d[nx,ny]:=d[e[head,1],e[head,2]]+1;
                end;
        end;
    end;
end;
begin
  readln(m,n);
  for i:=1 to n do
    begin
      for j:=1 to m do 
        begin
          read(a[i,j]);
          if a[i,j]=2 then
            begin
              x1:=i;
              y1:=j;
              a[i,j]:=1;
            end;
          if a[i,j]=3 then
            begin
              x2:=i;
              y2:=j;
              a[i,j]:=1;
            end;
          if a[i,j]=4 then
            begin
              t:=t+1;
              b[t,1]:=i;
              b[t,2]:=j;
            end;
        end;
      readln;
    end;
  bfs1(x1,y1);
  fillchar(f,sizeof(f),false);
  fillchar(e,sizeof(f),false);
  bfs2(x2,y2);
  min:=maxlongint;
  for i:=1 to t do
    if (c[b[i,1],b[i,2]]<>0)and(d[b[i,1],b[i,2]]<>0) then
      if c[b[i,1],b[i,2]]+d[b[i,1],b[i,2]]<min then
        min:=c[b[i,1],b[i,2]]+d[b[i,1],b[i,2]];
  writeln(min);
end.
```

---

