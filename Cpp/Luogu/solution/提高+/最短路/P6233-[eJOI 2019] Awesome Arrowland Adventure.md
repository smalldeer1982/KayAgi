# [eJOI 2019] Awesome Arrowland Adventure

## 题目描述

你现在在一个大小为 $m$ 行（行编号从 $0$ 开始，从上往下一直到 $m-1$） $n$ （列编号从 $0$ 开始，从左往右一直到 $n-1$）列的矩阵中。你的初始位置为 $(0,0)$。（$(r,c)$ 表示矩阵中第 $r$ 行，第 $c$ 列的位置）

你需要走到位置 $(m-1,n-1)$ 处。这个矩阵非常神奇——在矩阵的某些格子上有一个箭头。 箭头只可能有四种方向：北（向上），东（向右），南（向下），西（向左）。箭头分布在整个矩阵之上，形成了箭头矩阵。

当你在某一个位置时，假如这个位置不在矩形（左上角 $(0,0)$，右下角 $(m-1,n-1)$）范围内或这个位置没有箭头，那么你会一直停留于此，永远无法到达终点。如果此处有箭头，那么你将会向这个箭头的方向走一格。

但显然，你不一定能够在初始的箭头矩阵上找到一条从 $(0,0)$ 到 $(m-1,n-1)$ 的路径。为了找到这样一条路径，你可以一次将箭头矩阵中某一个箭头 ***顺时针*** 旋转 $90$ 度。通过几次的旋转，你可能会找到一条路径。

请你判断是否可以通过旋转来得到一条从 $(0,0)$ 到 $(m-1,n-1)$ 的路径，如果有，求出最小需要的旋转次数。

## 说明/提示

#### 样例解释

【样例 1 解释】
- 一个可行的解是，将位置 $(1,2)$ 的 ```W``` 旋转 $3$ 次变成 ```S```。

【样例 2 解释】
- 不需要任何旋转就可以。

【样例 3 解释】
- 在 $(0,0)$ 处旋转 $1$ 次，在 $(1,0)$ 处旋转 $2$ 次，在 $(2,1)$ 处旋转 $1$ 次。

---
#### 数据规模与约定

**本题采用多测试点捆绑测试，共有 $5$ 个子任务**。

- Subtask 1（10 points）：$m=1$，且输入的字符矩阵只包含 ```E``` 或 ```X```。
- Subtask 2（12 points）：$m=1$。
- Subtask 3（12 points）：$n=m=3$。
- Subtask 4（16 points）：$m=2$。
- Subtask 5（50 points）：无特殊限制。

对于 全部的测试点，保证 $1\le m,n\le 500$。

---

#### 说明

原题来自：[eJOI2019](https://www.ejoi2019.si) Problem F [Awesome Arrowland Adventure](https://www.ejoi2019.si/static/media/uploads/tasks/adventure-isc(1).pdf)

题面翻译：@[```_Wallace_```](https://www.luogu.com.cn/user/61430)（如果觉得这个翻译令人谔谔，欢迎提供新翻译）

## 样例 #1

### 输入

```
3 3
EES
SSW
ESX```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
EES
SSW
EEX```

### 输出

```
0```

## 样例 #3

### 输入

```
3 4
EXES
WSNS
XNNX```

### 输出

```
4```

# 题解

## 作者：Lice (赞：12)

### Description

~~它 spfa 了~~

### Solution

显然直接胡乱转是行不通的。

然而正解是图论中的最短路。

那样例1来说：

```plain
EES
SSW
ESX
```

假如你现在要从 $(0,1)$ 走到 $(1,1)$，的话，如果不绕圈子，那么我们需要将位置 $(0,1)$ 的箭头旋转一次，然后就可以走过去了。这可以抽象成： **从顶点** $(0,1)$ **有一条到** $(1,1)$ **的边，边权为1**。其他的位置同理，**以位置之间移动的所需旋转次数为边权** 。如果是 ```X``` 的话，就把它的所有出边边权设成 ```inf``` 。

那么对这个箭头矩阵进行这样的转化之后，我们得到了一张这样的图：

![e.g.](https://s1.ax1x.com/2020/03/22/85MLdI.png)

然后？直接跑最短路就好啦！

下面用了 Dijkstra 算法，spfa 应该可以（这个坑留个下一个题解）。

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int dx[4]={0,0,-1,1};
const int dy[4]={-1,1,0,0};
const char dir[]="WENS";

int val[256];
const int N=502;
char s[N][N];
int dist[N][N];
bool book[N][N];
int n,m;

int cost(char a,char b)//计算字符（箭头）转化的花费
{
	int sub=val[(int)b]-val[(int)a];
	if(sub<0) sub+=4;
	return sub;
}

struct HeapNode
{
	int x,y,dis;
	HeapNode(int _x,int _y,int _d):x(_x),y(_y),dis(_d){}
	bool operator <(const HeapNode &t)const{return dis>t.dis;}
};

bool out_of_range(int x,int y)
{
	return (x<1||y<1||x>n||y>m);
}

void SSSP()//建不建图其实无所谓，可以直接在原矩阵上跑。但是建图的话就可以直接套板子了，少了一些判断。
{//堆优化 Dijkstra 板子
	priority_queue<HeapNode> Q;
	Q.push(HeapNode(1,1,dist[1][1]=0));
	while(!Q.empty())
	{
		int x=Q.top().x,y=Q.top().y;
		Q.pop();
		if(book[x][y]) continue;
		book[x][y]=true;
		if(s[x][y]=='X') continue;
		for(register int i=0;i<4;i++)
		{
			HeapNode nxt(x+dx[i],y+dy[i],dist[x][y]+cost(s[x][y],dir[i]));
			if(out_of_range(nxt.x,nxt.y)) continue;
			if(dist[nxt.x][nxt.y]<=nxt.dis) continue;
			dist[nxt.x][nxt.y]=nxt.dis;
			Q.push(HeapNode(nxt));
		}
	}
}

signed main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	
	memset(dist,0x3f,sizeof dist);
	memset(book,false,sizeof book);
	val['W']=0,val['N']=1;
	val['E']=2,val['S']=3;
	
	SSSP();
	printf("%d\n",dist[n][m]==0x3f3f3f3f?-1:dist[n][m]);
	return 0;
}
```

应该是第一篇题解，如果帮到了你不妨点个赞啊 awa

---

## 作者：xtx1092515503 (赞：3)

为什么题解都用的是Dijkstra或是SPFA呀……你就没有考虑到毒瘤出题人如果把数据加强到$5000\times5000$该怎么过吗……

这里介绍一种可以通过上述数据范围的方法：**双端队列bfs**或者叫**01bfs**，[经典例题](https://www.luogu.com.cn/problem/P4667)。

这个方法适用于当一张图中所有的边的边权都是$0$或$1$的图上的最短路。具体而言，我们用**双端队列**替代常规图（即边权均为$1$的图）中的**普通队列**，当遇到$0$边时，从队首入队；当遇到$1$边时，从队尾入队。这样就保证了队列中的距离始终是**单调**的，因而也可以看作是用双端队列替代了Dijkstra中的**优先队列**。显然，因为使用了双端队列，复杂度是$O(n+m)$而非Dijkstra的$O(n+m\log m)$，其中$n$为图中点数，$m$为图中边数。

对于这题而言，我们可以将一个方格拆成$4$个点，分别表示当该方格上的箭头指向$4$个方向时的值，则所有的边权都为$0$或$1$，其中$1$边当且仅当箭头旋转时存在。直接套用上文所述01bfs，即可在$O(nm)$时间内通过本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dx[4]={-1,0,1,0},dy[4]={0,1,0,-1},lim;
struct node{
	int x,y,z,dir;
	node(int a,int b,int c,int d){x=a,y=b,z=c,dir=d;}
};
char g[510][510];
int dir(char x){
	if(x=='N')return 0;
	if(x=='E')return 1;
	if(x=='S')return 2;
	if(x=='W')return 3;
	return 4;
}
bool vis[510][510][5];
bool che(node i){
	return i.x<=n&&i.x>=1&&i.y<=m&&i.y>=1&&(g[i.x][i.y]!='X'||(i.x==n&&i.y==m))&&!vis[i.x][i.y][i.dir];
}
int bfs(){
	deque<node>q;
	q.push_back(node(1,1,0,dir(g[1][1])));
	while(!q.empty()){
		node x=q.front();q.pop_front();
		if(!che(x))continue;vis[x.x][x.y][x.dir]=true;
		if(x.x==n&&x.y==m)return x.z;
		q.push_front(node(x.x+dx[x.dir],x.y+dy[x.dir],x.z,dir(g[x.x+dx[x.dir]][x.y+dy[x.dir]])));
		q.push_back(node(x.x,x.y,x.z+1,(x.dir+1)%4));
	}
	return -1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",g[i]+1);
	if(g[1][1]=='X'&&(n>1||m>1)){puts("-1");return 0;}
	printf("%d\n",bfs());
	return 0;
}
```


---

## 作者：Nephren_Sakura (赞：2)

首先，看到这道题，第一反应是 bfs。

那么目前的难点在于：相邻两个点之间转移的权值：

1. 若当前的点为 X，无法转移

1. 若当前的点不为 X，使用一个 help 函数求出从当前的点到下一个点需要的价值

在将权值求出之后就是 bfs 板子了


虽然使用 bfs 已经能够通过本题，但是时间复杂度十分高，于是考虑用类似 spfa 的方法优化，$vis_{nx,ny}$ 表示此时横坐标为 $nx$，纵坐标为 $ny$ 的点是否在队列中，不在则入队，若在则跳过。

下附代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void put(int x){
	if(x<0){
		putchar('-');
		put(-x);
		return;
	}
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
struct node{
	int x,y;
};
int help(char c,int y){//可以写少一点，本人懒了 
	if(c=='N'&&y==0)
		return 0;
	else if(c=='N'&&y==1)
		return 1;
	else if(c=='N'&&y==2)
		return 2;
	else if(c=='N'&&y==3)
		return 3;
	else if(c=='E'&&y==0)
		return 3;
	else if(c=='E'&&y==1)
		return 0;
	else if(c=='E'&&y==2)
		return 1;
	else if(c=='E'&&y==3)
		return 2;
	else if(c=='S'&&y==0)
		return 2;
	else if(c=='S'&&y==1)
		return 3;
	else if(c=='S'&&y==2)
		return 0;
	else if(c=='S')
		return 1;
	else if(y==0)
		return 1;
	else if(y==1)
		return 2;
	else if(y==2)
		return 3;
	else
		return 0;
}
int n=read(),m=read(),dis[1005][1005];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
bool vis[1005][1005];
int val[100005];
char c[1005][1005];
void spfa(int x,int y){
	queue<node> q;
	q.push(node{x,y});//将初始点入队 
	dis[x][y]=0;
	vis[x][y]=true;//初始点在队列中 
	while(q.empty()==false){
		node cur=q.front();
		q.pop();
		vis[cur.x][cur.y]=false;//vis清空 
		if(c[cur.x][cur.y]=='X')
			continue;
		for(int i=0; i<4; i++){
			int nx=cur.x+dx[i],ny=cur.y+dy[i];
			int w=help(c[cur.x][cur.y],i);
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&dis[cur.x][cur.y]+w<dis[nx][ny]){//判断是否在地图中，能否更快到达nx,ny 
				dis[nx][ny]=dis[cur.x][cur.y]+w;
				if(vis[nx][ny]==false){//不在队列中，入队 ，标记vis 
					vis[nx][ny]=true;
					q.push(node{nx,ny});
				}
			}
		}
	}
	return;
}
signed main(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>c[i][j],dis[i][j]=1e18;
	spfa(1,1);
	if(dis[n][m]==1e18)//特判走不到 
		put(-1);
	else
		put(dis[n][m]);
	return 0;
 }
 
 ```


---

## 作者：朝夕 (赞：2)

## 解题思路
相比于上面的题解，我是先建图再跑的最短路。

**关于建图：**

对于矩阵内的每个位置，都可以视为图中的一个节点。

若该位置没有箭头，则代表该节点出度为0，没有出去的边。

否则只要有箭头，该节点都有4条边，通往上下左右四个节点，边的权值则是去往哪个节点箭头需要旋转的次数。

则题目转化为求从（1,1）这个节点前往（m,n）这个节点的最短路权值和。

**关于节点的编号：**

最简单的方法就是从1号编到n$\times$m号，则题目转化为从1号节点到n$\times$m号节点的最短路。

```cpp
int cnt=0;
for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++) id[i][j]=++cnt;
```
**关于建边：**

给四个方向分别标号，比如我的代码中是这样的：上0右1南2西3。

则用当前要去的方向标号减去原本的方向标号，就是要旋转的次数，如果这个差是负数，那再+4就可以了。

举例来说：现在的箭头方向是右1，要去的方向是上0，差是0-1=-1.是负数所以再+4=3.所以要旋转的次数就是3次。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int id[505][505];
int dx[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//向四个方向走后位置的变化
struct node{int to;int val;};
vector<node>edge[250005];
ll dis[250005];
bool vis[250005];
typedef pair<ll,int> pa;
void dijkstra(int start)//dijkstra模板。关于SPFA，它死了
{
    priority_queue<pa,vector<pa>,greater<pa> >q;
    memset(vis,0,sizeof(vis));
    dis[start]=0;
    q.push(pa(0,start));
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(int i=0;i<edge[now].size();i++)
        {
            int to=edge[now][i].to;
            int val=edge[now][i].val;
            if(dis[to]>dis[now]+val)
            {
                dis[to]=dis[now]+val;
                if(!vis[to]) q.push(pa(dis[to],to));
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int m,n;
    cin>>m>>n;
    int cnt=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) id[i][j]=++cnt;//给节点编号
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char in;
            cin>>in;
            int now;
            if(in=='X') continue;
            if(in=='N') now=0;
            if(in=='E') now=1;
            if(in=='S') now=2;
            if(in=='W') now=3;//确定当前方向
            for(int k=0;k<4;k++)
            {
                node x;
                x.to=id[i+dx[k][0]][j+dx[k][1]];//要去的节点
                int cost=k-now;
                if(cost<0) cost+=4;//处理权值
                x.val=cost;
                edge[id[i][j]].push_back(x);
            }
        }
    }
    for(int i=2;i<=n*m;i++) dis[i]=1e18;//初始化
    dijkstra(1);
    if(dis[n*m]>1e17) cout<<-1<<endl;//无解
    else cout<<dis[n*m]<<endl;
    return 0;
}

```


---

## 作者：DegChuZm (赞：1)

~~好水啊，这题真的是蓝题吗~~

题目简述，给你一个 $n,m$ 的矩阵，每个坐标上可能会有一个指向上下左右的箭头，可以**顺时针**旋转 $90$ 度让箭头指向不同的方向。问最少旋转几次可以从 $1,1$ 沿着箭头走到 $n,m$。

考虑使用最短路算法来求解这道题，我们可以在坐标 $x,y$ 依据需要旋转几次来建边。

我们用下面的图来打个比方。

```cpp
(1,1) (1,2) (1,3)
(2,1)  (E)  (2,3)
(3,1) (3,2) (3,3)
```

很明显，我们的箭头朝东指，所以我们到 $2,3$ 的边权就为 $0$。

而如果我们要到 $3,2$ 呢？

我们就可以旋转一次，于是边权就为 $1$。

如果一个点没有箭头，那么指向其他点的边权就是 $\inf$，这样就可以处理完一张图了。

以此类推，我们把一整张图都这样建好，就可以跑最短路了。

于是给出代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[100001],dis[2500001],jj,ans,n,m,o,x,y,z,head[1000001],cnt,xxx,yyy,flag;
bool vis[100001];
struct node{
	int val,to,nex;
}a[1000001];
struct dcz{
	int u,d;
	bool operator<(const dcz& jntm)const{
		return d>jntm.d;
	}
};
inline void add(int x,int y,int z){
	a[++cnt].val=z;
	a[cnt].to=y;
	a[cnt].nex=head[x];
	head[x]=cnt;
}
inline void dij(int o){
	memset(dis,0x3f,sizeof dis);
	dis[o]=0;
	priority_queue<dcz> q;
	q.push((dcz){o,0});
	while(!q.empty()){
		dcz xx=q.top();
		q.pop();
		int u=xx.u;
		int d=xx.d;
		if(d!=dis[u])
			continue;
		for(int i=head[u];i;i=a[i].nex){
			int v=a[i].to;
			int w=a[i].val;;
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push((dcz){v,dis[v]});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char mp;
			cin>>mp;// 建边乱搞
			if(mp=='E'){
				if(j+1<=m) add((i-1)*m+j,(i-1)*m+j+1,0);
				if(i+1<=n) add((i-1)*m+j,(i-1)*m+j+m,1);
				if(j-1>=1) add((i-1)*m+j,(i-1)*m+j-1,2);
				if(i-1>=1) add((i-1)*m+j,(i-1)*m+j-m,3);
			}
			if(mp=='W'){
				if(j+1<=m) add((i-1)*m+j,(i-1)*m+j+1,2);
				if(i+1<=n) add((i-1)*m+j,(i-1)*m+j+m,3);
				if(j-1>=1) add((i-1)*m+j,(i-1)*m+j-1,0);
				if(i-1>=1) add((i-1)*m+j,(i-1)*m+j-m,1);
			}
			if(mp=='N'){
				if(j+1<=m) add((i-1)*m+j,(i-1)*m+j+1,1);
				if(i+1<=n) add((i-1)*m+j,(i-1)*m+j+m,2);
				if(j-1>=1) add((i-1)*m+j,(i-1)*m+j-1,3);
				if(i-1>=1) add((i-1)*m+j,(i-1)*m+j-m,0);
			}
			if(mp=='S'){
				if(j+1<=m) add((i-1)*m+j,(i-1)*m+j+1,3);
				if(i+1<=n) add((i-1)*m+j,(i-1)*m+j+m,0);
				if(j-1>=1) add((i-1)*m+j,(i-1)*m+j-1,1);
				if(i-1>=1) add((i-1)*m+j,(i-1)*m+j-m,2);
			}
			if(mp=='X'){
				if(j+1<=m) add((i-1)*m+j,(i-1)*m+j+1,1061109567);
				if(i+1<=n) add((i-1)*m+j,(i-1)*m+j+m,1061109567);
				if(j-1>=1) add((i-1)*m+j,(i-1)*m+j-1,1061109567);
				if(i-1>=1) add((i-1)*m+j,(i-1)*m+j-m,1061109567);
			}
		}
	}
	dij(1);
	if(dis[n*m]==1061109567){
		cout<<-1;
		return 0;
	}
	printf("%d",dis[n*m]);
}
```


---

## 作者：happybob (赞：1)

比较容易的最短路。

主要考虑如何建图，可以发现每个点只要不是 `X`，那么它可以和与它四联通的每个点建边，那么边权是多少呢？

设目前点为 $(x_1, y_1)$，目标点为 $(x_2, y_2)$，$(x_2, y_2)$ 是与 $(x_1, y_1)$ 四联通的一个点，那么可得边权应该是目前点到目标点需要旋转的次数。

那么如果一个点为 `X` 怎么办？有两种做法，一种是仍然建边，不过边权是 $\infty $，另一种是不建边，这两种都可行，但第二种更优一些。

建完图后，可以发现，边权并不完全相同，考虑最短路或者 01-BFS，实测 01-BFS 快一些。

另外，网格图最短路建议选择 Dijkstra，SPFA 复杂度会很高。

Dijkstra 代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

constexpr int N(505), M(1e6 + 5);

int n, m;
char c[N][N];

int dx[] = { -1, 1, 0, 0 }; // 上下左右
int dy[] = { 0, 0, -1, 1 };

#define get(x) (x == 'W' ? 2 : (x == 'E' ? 3 : (x == 'N' ? 0 : 1)))

#define change(x) (x == 'W' ? 'N' : (x == 'E' ? 'S' : (x == 'N' ? 'E' : 'W')))

#define cg(x, y) ((x - 1) * m + y)

struct Edge
{
	int to, cost;
	Edge(int _to, int _cost): to(_to), cost(_cost){}
};

vector<Edge> G[M];
int dis[M];
bool f[M];

struct Node
{
	int place, dist;
	Node(int _p, int _d): place(_p), dist(_d){}
	bool operator<(const Node& g) const
	{
		return dist > g.dist;
	}
};

inline void dijkstra()
{
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	priority_queue<Node> q;
	q.push(Node(1, 0));
	while (q.size())
	{
		int l = q.top().place;
		q.pop();
		if (f[l]) continue;
		f[l] = true;
		for (register int i(0), j(G[l].size()); i < j; ++i)
		{
			register int nx(G[l][i].to);
			if (dis[nx] > dis[l] + G[l][i].cost)
			{
				dis[nx] = dis[l] + G[l][i].cost;
				if (!f[nx]) q.push(Node(nx, dis[nx]));
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (register int i(1); i <= n; ++i)
	{
		for (register int j(1); j <= m; ++j)
		{
			scanf(" %c", &c[i][j]);
			if (c[i][j] != 'X')
			{
				int p(get(c[i][j])), k(cg(i, j)), nx(i + dx[p]), ny(j + dy[p]);
				char h(c[i][j]);
				if (nx >= 1 and nx <= n and ny >= 1 and ny <= m)
				{
					G[k].push_back(Edge(cg(nx, ny), 0)); // 原始方向
				}
				for (register int bn(1); bn <= 3; ++bn)
				{
					h = change(h);
					p = get(h);
					nx = i + dx[p], ny = j + dy[p];
					if (nx >= 1 and nx <= n and ny >= 1 and ny <= m) G[k].push_back(Edge(cg(nx, ny), bn));
				}
			}
		}
	}
	dijkstra();
	printf("%d\n", dis[cg(n, m)] == dis[0] ? -1 : dis[cg(n, m)]);
	return 0;
}
```

01-BFS 代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

constexpr int N(505), M(1e6 + 5);

int n, m;
char c[N][N];

int dx[] = { -1, 1, 0, 0 }; // 上下左右
int dy[] = { 0, 0, -1, 1 };

#define get(x) (x == 'W' ? 2 : (x == 'E' ? 3 : (x == 'N' ? 0 : 1)))

#define change(x) (x == 'W' ? 'N' : (x == 'E' ? 'S' : (x == 'N' ? 'E' : 'W')))

#define cg(x, y) ((x - 1) * m + y)

struct Edge
{
	int to, cost;
	Edge(int _to, int _cost): to(_to), cost(_cost){}
};

vector<Edge> G[M];
int dis[M];

inline void bfs()
{
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	deque<int> q;
	q.push_back(1);
	while (q.size())
	{
		int l = q.front();
		q.pop_front();
		for (register int i(0), j(G[l].size()); i < j; ++i)
		{
			register int nx(G[l][i].to);
			if (dis[nx] > dis[l] + G[l][i].cost)
			{
				dis[nx] = dis[l] + G[l][i].cost;
				if (G[l][i].cost == 0) q.push_front(nx);
				else q.push_back(nx);
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (register int i(1); i <= n; ++i)
	{
		for (register int j(1); j <= m; ++j)
		{
			scanf(" %c", &c[i][j]);
			if (c[i][j] != 'X')
			{
				int p(get(c[i][j])), k(cg(i, j)), nx(i + dx[p]), ny(j + dy[p]);
				char h(c[i][j]);
				if (nx >= 1 and nx <= n and ny >= 1 and ny <= m)
				{
					G[k].push_back(Edge(cg(nx, ny), 0)); // 原始方向
				}
				for (register int bn(1); bn <= 3; ++bn)
				{
					h = change(h);
					p = get(h);
					nx = i + dx[p], ny = j + dy[p];
					if (nx >= 1 and nx <= n and ny >= 1 and ny <= m) G[k].push_back(Edge(cg(nx, ny), bn));
				}
			}
		}
	}
	bfs();
	printf("%d\n", dis[cg(n, m)] == dis[0] ? -1 : dis[cg(n, m)]);
	return 0;
}
```

最后说一个技巧，大家看代码可以发现，我的代码有一个 `#define cg(x, y) ((x - 1) * m + y)`，这是什么意思呢？不知道大家发现没有，这道题是一个二维的平面，我们最短路上的 `dis` 数组应该是二维，但是我的为什么是一维的呢？我们有一个办法，可以将坐标 $(x, y)$ 转化为一个唯一的值，其实就是以这个点为右下角，以 $(1, 1)$ 为左上角的矩形包括的点的个数，显然这个值是唯一的。


---

## 作者：Marginal_world (赞：1)

解题思路:先建图再跑最短路。

对于矩阵内的每个位置，都可以视为图中的一个节点。

若该位置没有箭头，则代表该节点出度为零，没有出去的边。

否则只要有箭头，该节点都有四条边，通往上下左右四个节点，边的权值则是去往哪个节点箭头需要旋转的次数。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int id[505][505];
int dx[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//向四个方向走后位置的变化
struct node{int to;int val;};
vector<node>edge[250005];
ll dis[250005];
bool vis[250005];
typedef pair<ll,int> pa;
void dijkstra(int start)//模板
{
    priority_queue<pa,vector<pa>,greater<pa> >q;
    memset(vis,0,sizeof(vis));
    dis[start]=0;
    q.push(pa(0,start));
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(int i=0;i<edge[now].size();i++)
        {
            int to=edge[now][i].to;
            int val=edge[now][i].val;
            if(dis[to]>dis[now]+val)
            {
                dis[to]=dis[now]+val;
                if(!vis[to]) q.push(pa(dis[to],to));
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int m,n;
    cin>>m>>n;
    int cnt=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) id[i][j]=++cnt;//给节点编号
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char in;
            cin>>in;
            int now;
            if(in=='X') continue;
            if(in=='N') now=0;
            if(in=='E') now=1;
            if(in=='S') now=2;
            if(in=='W') now=3;//确定当前方向
            for(int k=0;k<4;k++)
            {
                node x;
                x.to=id[i+dx[k][0]][j+dx[k][1]];//要去的节点
                int cost=k-now;
                if(cost<0) cost+=4;//处理权值
                x.val=cost;
                edge[id[i][j]].push_back(x);
            }
        }
    }
    for(int i=2;i<=n*m;i++) dis[i]=1e18;//初始化
    dijkstra(1);
    if(dis[n*m]>1e17) cout<<-1<<endl;//无解
    else cout<<dis[n*m]<<endl;
    return 0;
}
```

希望能对大家有所帮助。

---

## 作者：编程客 (赞：1)

### 题意翻译
- 给一个字符矩阵矩阵，矩阵中的每个字符表示上下左右，如果按字符方向行走就不需要花费代价，否则就需要花费字符方向顺时针方向旋转到 此方向÷90 的代价。
- 结果求的是从 $(1,1)$ 到 $(n,m)$ 所需要的最小代价。
- 本人的数组是从 $(1,1)$ 开始计算的，用从 $(0,0)$ 开始的也行。

### 解题思路
- 正解自然是最短路。
- 刚开始存图，可以直接用字符存，也可以像我一样用 `int` 存图。
- 建边，可以用 `vector` 刚开始预处理好所有边，也可以在最短路途中直接计算。边权，就是当前点输入的方向顺时针旋转到所需要的方向所需要的角度。（有点难懂，仔细思考。
- 这里附上一些代码
 ```cpp
int rx[4]={0,0,-1,1},ry[4]={-1,1,0,0};// 左右上下移动；
```

 ```cpp
数组名 [4][4]={
{0,2,1,3},
{2,0,3,1},
{3,1,0,2},
{1,3,2,0}};// 坐标权值；f[i][j]表示方向 i 到 方向 j 所需要旋转的角度；
```

### 注意事项
- 他这个样例直接复制会出现一些奇怪的符号……这里附上样例
 ```cpp
3 3
EES
SSW
ESX
```

 ```cpp
3 3
EES
SSW
EEX
```

 ```cpp
3 4
EXES
WSNS
XNNX
```
- 不要忘记有 `-1` 的情况
- 如果用 `getchar()` 要注意换行时也要读入一个换行符，否则会出错
### 关于最短路
- 先分析一下时间复杂度

`dij` $n log n$ , 但不能处理负权

`spfa` 能处理负权边权，但时间复杂度可能会被卡到 $O(n^2)$ 
- 我用的是 spfa , 但 TLE 了一个数据点，开 O2 就过了（切勿直接复制代码！！！）
 ## Code
 
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct node
{
	int x,y;
};
int n,m,a[505][505];
int f[505][505]; 
int rx[4]={0,0,-1,1},ry[4]={-1,1,0,0};
int rr[4][4]={
{0,2,1,3},
{2,0,3,1},
{3,1,0,2},
{1,3,2,0}};
int in_queue[505][505];
void spfa(int sx,int sy)
{
	queue<node> q;
	memset(f,63,sizeof(f));
	f[sx][sy]=0;
	in_queue[sx][sy]=1;
	q.push((node){sx,sy}); 
	while(!q.empty())
	{
		int nx=q.front().x,ny=q.front().y;
		q.pop();
		if(a[nx][ny]==4) continue;				// 如果为'X' 
		for(int i=0;i<4;i++)
		{
			int tx=nx+rx[i],ty=ny+ry[i];
			if(tx<1||tx>n||ty<1||ty>m) continue;
			int w=rr[a[nx][ny]][i];
			if(f[tx][ty]>f[nx][ny]+w)
			{
				f[tx][ty]=f[nx][ny]+w;
				if(in_queue[tx][ty]==0) q.push((node){tx,ty}); 
				in_queue[tx][ty]=1;
			}
		}
		in_queue[nx][ny]=0;
	}
}
int main()
{
	scanf("%d%d\n",&n,&m);
	char c;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			c=getchar();
			switch(c)						// 存点 
			{
				case 'W':a[i][j]=0;break;
				case 'E':a[i][j]=1;break;
				case 'N':a[i][j]=2;break;
				case 'S':a[i][j]=3;break;
				case 'X':a[i][j]=4;break;
			}
		}
		c=getchar();
	}
	spfa(1,1);
	if(f[n][m]==f[0][0]) printf("-1");		// 不能到达的情况 
	else printf("%d",f[n][m]);
	return 0;
}
```



---

## 作者：Night_sea_64 (赞：0)

非常水的一道题。

对于两个相邻格子，如果可以直接到达，连一条边权为 $0$ 的边；如果转一次就可以直接到达，连一条边权为 $1$ 的边；以此类推。

剩下的就是 SPFA 了，它没死。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
int n,m,a[510][510],d[510][510];
int dx[]={0,-1,0,1,0};
int dy[]={0,0,1,0,-1};
struct node{int x,y;};
void spfa()
{
    memset(d,999999,sizeof(d));
    if(!a[1][1]&&(n!=1||m!=1))return;
    d[1][1]=0;
    queue<node>q;
    q.push({1,1});
    while(!q.empty())
    {
        int x=q.front().x,y=q.front().y;
        q.pop();
        for(int i=1;i<=4;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<1||nx>n||ny<1||ny>m)continue;
            if(!a[nx][ny]&&(nx!=n||ny!=m))continue;
            int w=(i+4-a[x][y])%4;
            if(d[x][y]+w<d[nx][ny])
            {
                d[nx][ny]=d[x][y]+w;
                q.push({nx,ny});
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            char c;
            cin>>c;
            if(c=='N')a[i][j]=1;
            if(c=='E')a[i][j]=2;
            if(c=='S')a[i][j]=3;
            if(c=='W')a[i][j]=4;
        }
    spfa();
    if(d[n][m]<1e9)cout<<d[n][m]<<endl;
    else cout<<-1<<endl;
    return 0;
}
```

与此题非常类似的另一道题是 [P4667](https://www.luogu.com.cn/problem/P4667)，请自行练习。

---

## 作者：__DDDDDD__ (赞：0)

# 题面简述

给定一个 $m \times n$ 大小的、部分格子带箭头的矩阵。只能朝格子上箭头所指方向移动，求如何通过旋转最少数量的箭头从矩阵的左上角 $(0,0)$ 移动到右下角 $(m-1,n-1)$。

# 题目分析

采用 dijkstra 最短路算法，将旋转次数转化为边权。

将每个格子 $(i,j)$ 当作一个节点并标号为 $(i\times n +j)$，对于带有箭头的格子，向上下左右四个方向的格子连边，边权大小为相应的旋转次数。以样例 1 为例：

| **E** | **E** | **S** |
| -----------: | -----------: | -----------: |
| **S** | **S** | **W** |
| **E** | **S** | **X** |

对于 $(2,2)$ 的 “S”：
- 向 $(3,2)$ 的 “S” 连边，边权为 0；
- 向 $(2,1)$ 的 “S” 连边，边权为 1；
- 向 $(1,2)$ 的 “E” 连边，边权为 2；
- 向 $(2,3)$ 的 “W” 连边，边权为 3。

以此类推，注意边缘特判。详细细节见代码：


# 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int n,m;
int head[maxn],Next[maxn],ver[maxn],edge[maxn],tot=1;
inline void add(int x,int y,int z){
	ver[++tot]=y;edge[tot]=z;
	Next[tot]=head[x];head[x]=tot;
}

inline int calpos(int x,int y){ 	// 计算坐标（x，y）对应点的编号 
	return x*n+y; 
}

struct node{				// dijkstra 求最短路 
	int pos,dist;
	inline bool operator <(const node &a)const{return dist>a.dist;}
};
priority_queue<node>q;
int dist[maxn];
bool vis[maxn];
inline void dijkstra(int s){
	memset(dist,0x7f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	dist[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		node tmp=q.top();q.pop();
		int x=tmp.pos;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i],z=edge[i];
			if(dist[y]>dist[x]+z){
				dist[y]=dist[x]+z;
				if(!vis[y])q.push((node){y,dist[y]});
			}
		}
	}
}

char ch;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>ch;
			if(ch=='N'){		// 判断方向，向四周连边 
				if(i>1)add(calpos(i,j),calpos(i-1,j),0);
				if(j<n)add(calpos(i,j),calpos(i,j+1),1);
				if(i<n)add(calpos(i,j),calpos(i+1,j),2);
				if(j>1)add(calpos(i,j),calpos(i,j-1),3);
			}else if(ch=='E'){
				if(i>1)add(calpos(i,j),calpos(i-1,j),3);
				if(j<n)add(calpos(i,j),calpos(i,j+1),0);
				if(i<n)add(calpos(i,j),calpos(i+1,j),1);
				if(j>1)add(calpos(i,j),calpos(i,j-1),2);
			}else if(ch=='S'){
				if(i>1)add(calpos(i,j),calpos(i-1,j),2);
				if(j<n)add(calpos(i,j),calpos(i,j+1),3);
				if(i<n)add(calpos(i,j),calpos(i+1,j),0);
				if(j>1)add(calpos(i,j),calpos(i,j-1),1);
			}else if(ch=='W'){
				if(i>1)add(calpos(i,j),calpos(i-1,j),1);
				if(j<n)add(calpos(i,j),calpos(i,j+1),2);
				if(i<n)add(calpos(i,j),calpos(i+1,j),3);
				if(j>1)add(calpos(i,j),calpos(i,j-1),0);
			}
		}
	}
	dijkstra(calpos(1,1));
	cout<<(dist[calpos(m,n)]==0x7f7f7f7f7f7f7f7f?-1:dist[calpos(m,n)])<<endl;
						// 注意无解特判 
	return 0;
}
```





---

## 作者：chenxia25 (赞：0)

>[洛谷题目页面传送门](https://www.luogu.com.cn/problem/P6233)

>题意见洛谷。

看到这种网格题，就想DP，结果发现有环，果断最短路。

考虑对于每两个相邻网格有序对$((a,b),(c,d))$，若$(a,b)$处有箭头，那么从$(a,b)$到$(c,d)$连一条有向边，边权为从$(a,b)$的初始箭头方向到$(a,b)\to(c,d)$应该的方向需要转的次数。然后堆优化Dijkstra即可。$\mathrm O(nm\log nm)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define y0 sdfjaewjfwa
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int inf=0x3f3f3f3f;
const int N=500,M=500,ASCII=150;
int n,m;
char a[N+1][M+5];
int id[ASCII];const int ds[][4]={{0,1,2,3},{3,0,1,2},{2,3,0,1},{1,2,3,0}}/*方向与方向之间的距离*/,dx[]={-1,0,1,0},dy[]={0,1,0,-1};
bool vld(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
vector<pair<int,int> > nei[N*M+1];//邻接矩阵 
int dis[N*M+1];
void dijkstra(){//Dijkstra
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	memset(dis,0x3f,sizeof(dis));
	q.push(mp(dis[1]=0,1));
	while(q.size()){
		int x=q.top().Y;
		q.pop();
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X,len=nei[x][i].Y;
			if(dis[x]+len<dis[y])q.push(mp(dis[y]=dis[x]+len,y));
		}
	}
//	for(int i=1;i<=n*m;i++)cout<<dis[i]<<" ";puts("");
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	id['N']=0;id['E']=1;id['S']=2;id['W']=3;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='X')//连边 
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(vld(x,y))nei[(i-1)*m+j].pb(mp((x-1)*m+y,ds[id[a[i][j]]][k]));
		}
	dijkstra();//求最短路 
	cout<<(dis[n*m]<inf?dis[n*m]:-1);
	return 0;
}
```

然后看到神仙ymx的[题解](https://www.luogu.com.cn/blog/Troverld/solution-p6233)，发现有$\mathrm O(nm)$的做法（orzymxtqlddw）。这里需要用到一个小trick。对于一个边权只有$0,1$两种图求最短路时，我们可以把Dijkstra里的堆换成双端队列，松弛成功时若连接边为$0$则从队首加入，否则从队尾加入，正确性显然。就去掉了$\log$。至于这题，可以将每个格子拆成$4$个点，每个点代表一个方向，方向到方向之间连$1$边，相邻格子之间连$0$边，然后跑上述trick即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define y0 sdfjaewjfwa
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define pf push_front
#define ppf pop_front
const int inf=0x3f3f3f3f;
const int N=500,M=500,ASCII=150;
int n,m;
char a[N+1][M+5];
int id[ASCII];const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
bool vld(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
vector<pair<int,bool> > nei[4*N*M+1];//邻接矩阵 
int dis[4*N*M+1];
void dijkstra(){//Dijkstra 
	deque<int> q;//双端队列 
	memset(dis,0x3f,sizeof(dis));
	dis[4-id[a[1][1]]]=0;q.pb(4-id[a[1][1]]);
	while(q.size()){
		int x=q[0];
		q.ppf();
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X;bool len=nei[x][i].Y;
			if(dis[x]+len<dis[y]){
				dis[y]=dis[x]+len;
				if(len)q.pb(y);//队尾加 
				else q.pf(y);//队首加 
			}
		}
	}
//	for(int i=1;i<=4*n*m;i++)cout<<dis[i]<<" ";puts("");
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	id['N']=0;id['E']=1;id['S']=2;id['W']=3;id['X']=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='X')//连边 
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			nei[4*((i-1)*m+j)-k].pb(mp(4*((i-1)*m+j)-(k+1)%4,1));
			if(vld(x,y))nei[4*((i-1)*m+j)-k].pb(mp(4*((x-1)*m+y)-id[a[x][y]],0));
		}
	dijkstra();//求最短路 
	cout<<(dis[4*n*m-id[a[n][m]]]<inf?dis[4*n*m-id[a[n][m]]]:-1);
	return 0;
}
```

---

