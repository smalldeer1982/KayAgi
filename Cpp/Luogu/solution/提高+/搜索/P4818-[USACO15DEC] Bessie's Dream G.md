# [USACO15DEC] Bessie's Dream G

## 题目描述

Bessie 在 Farmer John 的厨房暴食水果后，开始做奇怪的梦！在最近的梦境中，她被困在一个 $N \times M$ 的网格迷宫（$1 \leq N,M \leq 1,000$）中。她需要从左上角的格子移动到右下角的格子。当站在某个格子时，她可以向四个基本方向移动至相邻格子。

但请注意！每个格子有不同的颜色和特殊属性：

- **红色（0）**：不可通行  
- **粉色（1）**：可正常通行  
- **橙色（2）**：可正常通行，且会使 Bessie 带有橙子气味  
- **蓝色（3）**：仅当 Bessie 带有橙子气味时方可通行  
- **紫色（4）**：Bessie 将沿该方向滑动到下一个格子（除非无法通过）。若下一个格子仍是紫色，则继续滑动直至遇到非紫色格子或不可通行格子。**每次滑动均计为一步移动**，且**紫色格子会消除 Bessie 的气味**

（若对紫色格子机制有疑问，样例将帮助理解）

请帮助 Bessie 找到从左上角到右下角的最短路径步数。

## 说明/提示

样例中，Bessie 的移动路径为：向下 1 步，向右 2 步（滑动再向右 1 步），向上 1 步，向左 1 步，向下 1 步（滑动再向下 2 步），最后向右 1 步。总计 10 步（路径表示为 DRRRULDDDR）。

题目提供者：Nathan Pinsker，灵感来自游戏《Undertale》

## 样例 #1

### 输入

```
4 4
1 0 2 1
1 1 4 1
1 0 4 0
1 3 1 1```

### 输出

```
10```

# 题解

## 作者：zylll (赞：5)

大搜索。因为允许多次在可行的情况下走过一个点，所以在这里我们记录状态，若当前状态未出现过则继续搜索。

本题使用STL queue，因为枚举次数不宜确定，数组大小不确定。手写导致我wa了许多次。队列结构体维护坐标，方向，橙子味，距离。

当a[x][y]==4时，不同的方向会造成不同的结果，所以要记录方向。剩下就不再赘述了。

搜索过程中不用使用判重数组的原因是边界外的点的值是0，与红色格子的值相同。

代码：
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <queue>
static const int MAXN=1050;
static const int dirx[]={1,-1,0,0};
static const int diry[]={0,0,1,-1};
using namespace std;
struct node{
    int x,y,d,ora,dis;
};
queue<node> q;
int n,m,head,tail,a[MAXN][MAXN];
bool vis[MAXN][MAXN][2][5];
inline int read(){
    int x=0;bool sign=false;
    char alpha=0;
    while(!isdigit(alpha)) sign|=alpha=='-',alpha=getchar();
    while(isdigit(alpha)) x=(x<<1)+(x<<3)+(alpha^48),alpha=getchar();
    return sign?-x:x;
}
inline bool check(int x,int y){
    return (x<1||y<1||x>n||y>m)?true:false;
}
inline int bfs(){
    q.push((node){1,1,0,0,0});
    while(!q.empty()){
        node now=q.front();q.pop();
        int x=now.x,y=now.y,d=now.d,ora=now.ora,dis=now.dis;
        bool flag=0;
        if(vis[x][y][ora][d]) continue;
        vis[x][y][ora][d]=1;
        if(x==n&&y==m) return dis;
        if(a[x][y]==4){
            int dx=x+dirx[d],dy=y+diry[d];
            if(!a[dx][dy]||a[dx][dy]==3);
            else if(a[dx][dy]==1||a[dx][dy]==4) q.push((node){dx,dy,d,0,dis+1}),flag=1;
            else q.push((node){dx,dy,d,1,dis+1}),flag=1;
        }
        if(a[x][y]==4&&flag) continue;
        for(int i=0;i<4;i++){
            int dx=x+dirx[i],dy=y+diry[i];
            if(!a[dx][dy]||(a[dx][dy]==3&&!ora)) continue;
            else if((a[dx][dy]==3&&ora)||a[dx][dy]==1||a[dx][dy]==4) q.push((node){dx,dy,i,ora,dis+1});
            else if(a[dx][dy]==2) q.push((node){dx,dy,i,1,dis+1});
        }
    }
    return -1;
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
        }
    }
    printf("%d\n",bfs());
    return 0;
}
```

---

## 作者：俺是小程 (赞：4)

注意到每次转移的代价都为一，于是爆搜即可。   
这个题的难点在于状态的判重（大概）。  
$1000 * 1000$ 的数据规模的话map有点勉强，更何况出题人专门出了卡map的数据（第11个点），所以map是无法通过此题的。  
我们从状态入手。首先仔细读题，确定出如下状态:
```cpp
struct state
{
	int x, y;
	int ld; bool smell;
};
```
考虑到每个状态只有4维，分别是
 - 横坐标
 - 纵坐标
 - 气味
 - 滑行方向   
 
所以我们可以把气味放在十进制下第六位，0-5位放横纵坐标，二进制下的第0位放气味，那么就可以用一个1e7的数组放下所以状态了。

```cpp
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e3 + 20;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
inline int read()
{
	int x = 0; char ch = getchar(); bool f = false;
	while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}

int N, M;
int a[MAXN][MAXN];
int dis[10000000];
struct state
{
	int x, y;
	int ld; bool smell;
	int idx;
	state(int x, int y, int ld, bool s) :
	x(x), y(y), ld(ld), smell(s) {}
	
	inline void Hash(){
		idx = ((x * 1000 + y + (ld + 1) * 1000000) << 1) | smell;
	}
};

inline bool out(int x, int y){
	return !(1 <= x && x <= N && 1 <= y && y <= M);
}

queue<state> q;
int bfs(){
	state s = state(1, 1, -1, false);
	s.Hash(); q.push(s); dis[s.idx] = 0; 
	while(!q.empty()){
		state u = q.front(); q.pop();
		if(u.x == N && u.y == M) return dis[u.idx];

		if(u.ld != -1){
			state v = u; v.smell = false;
			v.x += dx[u.ld], v.y += dy[u.ld];
			int col = a[v.x][v.y];
			if(!(out(v.x, v.y) || col == 0 || col == 3)){
				if(col != 4) v.ld = -1;
				if(col == 2) v.smell = true;
				v.Hash(); 
				if(dis[v.idx] == -1){
					q.push(v); dis[v.idx] = dis[u.idx] + 1;
				}
				continue;
			}
			u.ld = -1;
		}

		for(int i = 0; i < 4; i++){
			state v = u; 
			v.x += dx[i], v.y += dy[i];
			int col = a[v.x][v.y];
			if(out(v.x, v.y) || col == 0) continue;
			if(col == 3 && !v.smell) continue;
			if(col == 2) v.smell = true;
			if(col == 4) v.ld = i, v.smell = false;
			v.Hash();
			if(dis[v.idx] == -1){
				q.push(v); dis[v.idx] = dis[u.idx] + 1;
			}
		}
	}
	return -1;
}

int main()
{
	//freopen("p4818.in", "r", stdin);
	memset(dis, 0xff, sizeof(dis));//初值赋为-1
	cin>>N>>M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++) a[i][j] = read();
	cout<<bfs()<<endl;
	return 0;
}

```

---

## 作者：破忆 (赞：2)

## 【题意】
给定网格图，有一些限制条件，求起点到终点的最短路
## 【分析】
首先步长都是1，刷BFS就行了

绿色格子的通过条件涉及到气味，需要加一维气味状态

紫色格子的通过条件涉及到方向，需要加一维方向状态

再加上坐标，一共需要开四维状态

------------

然后就写了个3k的代码

不出所料，青草池塘处处WA

调试起来及其困难

**所以简化代码真的很重要！**

------------

代码比较简单，讲讲写代码的思路吧

主要是状态转移的过程需要思考，细节也比较多

先对格子进行分类

紫色格子是唯一涉及方向的格子，需要单独挑出来处理

当前若是紫色格子

如果前方无法通过，则把紫色格子看成其他颜色的处理

否则判断下一个状态的气味，再根据路程选择是否把下一状态加入队列

如果当前不是紫色格子（包括紫色格子无法前进的情况）

先把无法通过的判掉，再判断气味，最后根据路程选择是否把下一状态加入队列，基本同上

## 【算法】
BFS
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5,maxq=8e6+5,p[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m;
int mp[maxn][maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int d[maxn][maxn][4][2];
struct Q{
	int x,y,w;
	bool k;
}que[maxq];
void BFS(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) memset(d[i][j],63,sizeof d[i][j]);
	d[1][1][0][0]=0;
	int hed=0,til=1;
	que[1]=(Q){1,1,0,0};
	while(hed!=til){
		int x=que[++hed].x,y=que[hed].y,w=que[hed].w,k=que[hed].k,dis=d[x][y][w][k];
		if(x==n&&y==m){
			printf("%d\n",dis);
			exit(0);
		}
		if(mp[x][y]==4){
			int tx=x+p[w][0],ty=y+p[w][1];
			if(mp[tx][ty]==0||mp[tx][ty]==3);
			else{
				int tk=(mp[tx][ty]==1||mp[tx][ty]==4)?0:1;
				if(d[tx][ty][w][tk]<=dis+1) continue;
				d[tx][ty][w][tk]=dis+1;
				que[++til]=(Q){tx,ty,w,tk};
				continue;
			}
		}
		for(int i=0;i<4;i++){
			int tx=x+p[i][0],ty=y+p[i][1];
			if((mp[tx][ty]==3&&!k)||mp[tx][ty]==0) continue;
			int tk=(mp[tx][ty]==1)?k:((mp[tx][ty]==3||mp[tx][ty]==2)?1:0);
			if(d[tx][ty][i][tk]<=dis+1) continue;
			d[tx][ty][i][tk]=dis+1;
			que[++til]=(Q){tx,ty,i,tk};
		}
	}
}
int main(){
	freopen("P4818.in","r",stdin);
	freopen("P4818.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) mp[i][j]=read();
	BFS();
	printf("-1\n");
	return 0;
}
```


---

## 作者：dyc2022 (赞：1)

说实话，我不知道这题和进制有什么关系。
***
使用 dij 算法。

这种做法比起朴素广搜的优势就是不用多存一个方向的状态。我们可以在走到一个紫色格子后直接扩展出这条路径。显然这个时候权值不一定为 $1$，因此需要使用 dijkstra 来处理 $>1$ 的权值。

没什么细节，参见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 1003
using namespace std;
namespace IO
{
	int read()
	{
		int ret=0,bas=1;char ch=getchar();
		while(!isdigit(ch)&&ch!='-')ch=getchar();
		if(ch=='-')bas=-1,ch=getchar();
		while(isdigit(ch))ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
		return bas*ret;
	}
	void write(int k)
	{
		if(!k)return;
		write(k/10);
		putchar((char)(k%10+'0'));
	}
	void print(int k)
	{
		if(k==0)putchar('0');
		else if(k<0)putchar('-'),write(-k);
		else write(k);
	}
}
using namespace IO;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int n,m,a[N][N];
struct Node{int x,y,sm,cnt;};
int vis[N][N][2];
priority_queue<Node,vector<Node>,greater<Node> > q;
bool operator >(Node x,Node y){return x.cnt>y.cnt;}
bool judge(int x,int y){return x>0&&y>0&&x<=n&&y<=m&&a[x][y];}
int dij()
{
	memset(vis,0x3f,sizeof(vis));
	q.push({1,1,0,0});
	vis[1][1][0]=0;
	while(!q.empty())
	{
		Node now=q.top();q.pop();
		int nowx=now.x,nowy=now.y,nowsm=now.sm,nowcnt=now.cnt;
		for(int i=0;i<4;i++)
		{
			int tx=nowx+dx[i],ty=nowy+dy[i];
			if(a[tx][ty]==3&&!nowsm)continue;
			if(!judge(tx,ty))continue;
			int tsm=nowsm;
			if(a[tx][ty]==2)tsm=1;
			if(a[tx][ty]==4)tsm=0;
			int add=1;
			while(a[tx][ty]==4&&judge(tx+dx[i],ty+dy[i])&&a[tx+dx[i]][ty+dy[i]]!=3)tx+=dx[i],ty+=dy[i],add++;
			if(nowcnt+add<vis[tx][ty][tsm])vis[tx][ty][tsm]=nowcnt+add,q.push({tx,ty,tsm,nowcnt+add});
		}
	}
	if(min(vis[n][m][0],vis[n][m][1])>1e9)return -1;
	return min(vis[n][m][0],vis[n][m][1]);
}
main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();
	return print(dij()),0;
}
```

---

## 作者：Clover_BY (赞：1)

# [P4818 Bessie's Dream G](https://www.luogu.com.cn/problem/P4818)
## 题意简述
题目灵感来自 Undertale 里的趣味颜色游戏。当前翻译把 blue 翻成了绿，不过无伤大雅（但还是建议修正）。  
本题是一道经典的搜索题，要求求出在满足所有条件下进行行走，到达地图右下角的最小步数。  
限制条件包括：  

1. 红色格子不能通过。
2. 橙色格子会使 Bessie 沾上橘子气味，而有橘子气味时才能通过蓝色格子。
3. 如果踏上了紫色格子则只能沿着走上去的方向继续移动，但无法移动时可以考率转向。同时，紫色格子会消除橘子气味。

## 如何实现
大力广搜。  
通过上方的描述，我们不难发现一种状态只需要记录五条信息：横、纵坐标，现在向哪个方向行走，是否沾上了橘子气味，以及当前行走的步数。若队列清空后仍未到达，输出 `-1` 即可。  

### 去重
这些不同的条件会使去重变得比较困难。考虑下面一组数据（同时可以作为另一组样例进行调试）：
```cpp
//输入
6 4
1 0 0 0
1 1 1 1
3 0 0 1
1 0 2 1
1 0 0 0
4 4 4 1

//输出
20
```
在这组数据中，Bessie 需要先到地图右侧沾上橘子气味才能通过左侧的蓝色格子进而继续向右下角移动。如果只记录当前点是否遍历过，显然不能通过本组样例。因而，去重数组的设置状态应与状态相同，开四维，分别记录横纵坐标，从哪个方向进入，以及此时是否沾上了橘子气味。

### 针对不同方格的处理
紫色方格处理起来最麻烦，因此先考虑紫色。  
如果当前在紫色方格上，先考虑按照之前进入的方向是否还能继续行走。若否，按照普通方格处理。  
如果要踏上的是紫色方格，去掉气味标记，记录朝向后入队。  
对于红色方格及处于地图外的方格，直接忽略。  
对于橙色方格，记录气味。  
对于蓝色方格，检查是否有气味标记再入队。

### 缩小空间常数
首先应该明确，这道题的大部分 TLE 和 MLE 都不应是常数问题。若程序正确，很快就能跑出结果。这里只是提供缩小常数的技巧。  
$n, m \leq 1000$，开成 `short` 即可；  
朝向数 `0/1/2/3/4` （含不记录），气味标记 `0/1`，开 `char` 即可；  
用于去重的布尔型数组也换成 `char` ，减少不必要的空间浪费。  
结构体中的变量仿照上述处理。用了一个初学结构体时用到的技巧——将占用空间小的变量放在前面更优。

## Code Time
```cpp
#include <cstdio>
#include <cctype>
#include <queue>
using namespace std;

inline int min(int a, int b){return a < b ? a : b;}
inline short read()
{
	short x = 0; char c;
	while(!isdigit(c = getchar()));
	do{
		x = (x << 1) + (x << 3) + (c ^ 48);
	}while(isdigit(c = getchar()));
	return x;
}

char top = 0, stk[20];
inline void write(int x)
{
	do{
		stk[++top] = x % 10;
		x /= 10;
	}while(x);
	for(register int i = top; i; --i)
		putchar(stk[i] | 48);
	putchar('\n'); top = 0;
	return ;
}

char arv[1010][1010][5][2];
char sz[1010][1010];
short n, m;
short opex[4] = {-1, 0, 1, 0}, opey[4] = {0, -1, 0, 1};
int res = 20000000;
struct node
{
	char head;
	char scent;
	short x;
	short y;
	int cnt;
};
queue<node> q;

inline char red(short x, short y)
{return sz[x][y] == 0;}
inline char blue(short x, short y, char scent)
{return sz[x][y] == 3 && scent == 0;}
inline char vis(short x, short y, char head, char scent)
{return arv[x][y][head][scent];}
inline char total(short x, short y, char head, char scent)
{return red(x, y) || blue(x, y, scent) || vis(x, y, head, scent);}

inline void bfs()
{
	while(!q.empty())
	{
		node tmp = q.front(); q.pop();
		if(tmp.x == n && tmp.y == m)
		{
			res = min(res, tmp.cnt);
			continue;
		}
		bool valid = false;
		short newx, newy; char newscent, newhead;
		if(tmp.head != 4)
		{
			newx = tmp.x + opex[tmp.head];
			newy = tmp.y + opey[tmp.head];
			if(!total(newx, newy, tmp.head, 0))
			{
				valid = true;
				if(sz[newx][newy] != 4)
				{
					arv[newx][newy][tmp.head][sz[newx][newy] == 2] = true;
					q.push((node){4, sz[newx][newy] == 2, newx, newy, tmp.cnt + 1});
				}
				else
				{
					arv[newx][newy][4][sz[newx][newy] == 2] = true;
					q.push((node){tmp.head, sz[newx][newy] == 2, newx, newy, tmp.cnt + 1});
				}
				continue;
			}
		}
		if(!valid) tmp.head = 4; else continue;
		for(register char i = 0; i <= 3; ++i)
		{
			newx = tmp.x + opex[i]; newy = tmp.y + opey[i];
			if(sz[newx][newy] == 2) newscent = 1;
			else newscent = tmp.scent;
			if(sz[newx][newy] == 4) newhead = i;
			else newhead = 4;
			if(!total(newx, newy, newhead, newscent))
			{
				arv[newx][newy][newhead][newscent] = true;
				q.push((node){newhead, newscent, newx, newy, tmp.cnt + 1});
			}
		}
	}
	return ;
}

int main()
{
	n = read(); m = read();
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= m; ++j)
			sz[i][j] = read();
	arv[1][1][4][0] = true;
	q.push((node){4, 0, 1, 1, 0}); bfs();
	if(res == 20000000) printf("-1\n");
	else write(res); return 0;
}
```
这份代码是本题第一份卡进 300ms 的（虽然没有刻意去卡吧）。

---

## 作者：Loser_King (赞：1)

### Part 0 前言

以前没有AC掉的题目，然后使用了一个下午来调试。（（（

有很多细节的搜索题，需要花上较长的时间。

~~`inspired by the game "Undertale".`大好评（（（~~

## Part 1 题意

> （这里的翻译是自译英文的简明题意，可能会与洛谷上的翻译不同）
>
> 给定一个大小为 $N \times M$ 的数字矩阵，每种数字都代表了一个格子的颜色。
>
> - $0$ 表示红色格子，即不可以通过的格子；
>
> - $1$ 表示粉色格子，即可以正常通过的格子；
>
> - $2$ 表示橙色格子，即可以正常通过，但是会沾上橙子味的格子；
>
> - $3$ 表示蓝色格子，即有水虎鱼的格子，除非身上沾有橙子味，否则就无法通过。
>
> - $4$ 表示紫色格子，即会锁定行走方向直到到一个非紫色格子或走出边界。
>
>   这种格子会消除身上的橙子气味。
>
> 求从最左上角走到最右下角的最短距离。

## Part 2 解法

既然锁定了大方向是使用`bfs`来寻找最短路径，那么就只要确定几个搜索要素即可。

1. **状态**

   我的代码中使用了三个数字来组成状态：

   ```c++
   struct node{int x,y,stp,sm,dir;};
   ```

   其中`x`和`y`表示当前状态的坐标；

   `stp(step)`表示已经走了几步；

   `sm(smell)`表示当前身上有没有味道（0/1）；

   `dir(direction)`表示上一步的方向（0/1/2/3）。

2. **拓展**

   分两种情况：

   如果当前格为紫色格**而且`dir`的方向可以走**，则只能往`dir`的方向拓展；

   否则就往四个方向拓展。

3.  **初始&答案**

   初始比较好想，即`(node){1,1,0,0,0}`。

   答案也比较好想，当当前的节点的`x==n&&y==m`的时候输出答案。

实现中的坑点和技巧会在代码里讲。

## Part 3 代码

不加注释代码长度不到1K，是代码中比较短的了。

开O2时间最快797ms，（截止到了题解发布）是在最优解第2页。

```c++
#include<bits/stdc++.h>
using namespace std;
int const N=2333,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,vis[N][N][2][4],mp[N][N]; //出题人专门用了第12个点来卡map，所以只能用vis数组
struct node{int x,y,stp,sm,dir;};
queue<node>q;
inline int unreachable(node a){
	return //a.x<1||a.y<1||a.x>n||a.y>m这个可以不写，因为全局变量初始值为0，就是红格子
	       !mp[a.x][a.y]||!a.sm&&mp[a.x][a.y]==3;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>mp[i][j];
    q.push((node){1,1,0,0,0});
    vis[1][1][0][0]=1;
    while(q.size()){
    	node f=q.front();q.pop();
    	if(f.x==n&&f.y==m){cout<<f.stp;return 0;}
    	if(mp[f.x][f.y]==4){  //注意一步不能直接在紫格子上滑行
    		node t=(node){f.x+dx[f.dir],f.y+dy[f.dir],f.stp+1,0,f.dir}; //去掉味道
    		if(!unreachable(t)){
    			if(mp[f.x][f.y]==2)t.sm=1; //味道还要再加回来
    			q.push(t);continue; //注意只有这个格子可以达到才会拓展，否则就拓展4个方向
    		}
    	}
    	for(int i=0;i<4;i++){
    		node t=(node){f.x+dx[i],f.y+dy[i],f.stp+1,f.sm||mp[t.x][t.y]==2,i};
    		if(unreachable(t)||vis[t.x][t.y][t.sm][t.dir])continue;
    		vis[t.x][t.y][t.sm][t.dir]=1;q.push(t);
    	}
    }
    cout<<-1;
}
```

---

## 作者：seika27 (赞：0)

翻译略有毒瘤，其余倒是没什么。

看到数据范围考虑广搜，在这个题目里面的 ```vis```  数组，不仅要考虑坐标，方向和橘子味对答案都有影响，所以都记下来。

然后就是正常广搜流程，需要注意的是，如果你身处紫色格子，你就会沿着你现在的方向一直走，直到走到一个不是紫色的格子或者走不动了为止。

其余颜色就是按照题目所说模拟。

具体一些细节见代码。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
int n,m;
const int N=1e3+3;
int a[N][N];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
struct node{int val,x,y,ora,dir;};
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<48||57<c)c=getchar();
	while(48<=c&&c<=57)x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+48);
}
bool vis[N][N][4][2];     //分别为x,y,dir(方向),ora(橘子味)
std::queue<node>q;
inline void bfs()
{
	q.push({0,1,1,0,0});
	while(!q.empty())
	{
		node top=q.front();q.pop();
		int x=top.x,y=top.y,val=top.val,ora=top.ora,dir=top.dir;
		if(vis[x][y][dir][ora])continue;
		vis[x][y][dir][ora]=1;
		if(x==n&&y==m){write(val);return;}               //广搜的性质
		if(a[x][y]==4)              //如果当前格子是紫色就会一直滑
		{
			int nx=x+dx[dir];
			int ny=y+dy[dir];
			if(a[nx][ny]&&a[nx][ny]!=3)
			{
				q.push({val+1,nx,ny,a[nx][ny]==2,dir});
				continue;
			}
		}
		for(int i=0;i<4;++i)               //正常遍历
		{
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(!a[nx][ny])continue;
			if(a[nx][ny]==1)q.push({val+1,nx,ny,ora,i});
			if(a[nx][ny]==2)q.push({val+1,nx,ny,1,i});
			if(a[nx][ny]==3&&ora)q.push({val+1,nx,ny,1,i});
			if(a[nx][ny]==4)q.push({val+1,nx,ny,ora,i});
		}
	}
	puts("-1");
	return;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			a[i][j]=read();
		}
	}
	bfs();
}
```

---

## 作者：fanypcd (赞：0)

[P4818 [USACO15DEC]Bessie's Dream G - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P4818)

~~模拟题？~~

因为图较大，考虑记忆化。

------

定义 ```dis[i][j][1/0][pre]``` 表示当前位置为 $(i,j)$，是 / 否携带气味，且来到这个位置的方向为 pre 所需要的最小步数。（这里只有在滑动的状态下 pre 才有值，其他情况是 0）。

如果搜索到某时刻目前状态的 ```dis[i][j][1/0][pre]``` 小于等于记录的步数，就结束当前的搜索（可以理解为之前搜过一遍了）。

------



**定义 ```check(x, y, smell)``` 来检查扩展到的点的合法性：**

```cpp
inline bool check(int x, int y, int smell)
{
	if(x < 1 || x > n || y < 1 || y > m)
	{
		return 0;
	}
	if(!a[x][y] || (a[x][y] == 3 && !smell))
	{
		return 0;
	}
	return 1;
}
```

------



**然后是 ```update(node u)``` 函数，对当前点状态为 ```u``` 的情况进行扩展：**

```cpp
const int dx[5] = {0, 1, 0, 0, -1}, dy[5] = {0, 0, 1, -1, 0};
inline void update(node u)
{
	for(int i = 1; i <= 4; i++)
	{
		int xx = u.x + dx[i], yy = u.y + dy[i];
		if(check(xx, yy, u.smell))
		{
			if(a[xx][yy] == 2)
			{
				q.push((node){xx, yy, u.step + 1, 1, 0});
			}
			else if(a[xx][yy] == 4)
			{
				q.push((node){xx, yy, u.step + 1, 0, i});
			}
			else
			{
				q.push((node){xx, yy, u.step + 1, u.smell, 0});
			}
		}
	}
	return;
}
```

------

**然后 ```bfs``` 函数就比较显然了：**

```cpp
inline void bfs()
{
	q.push((node){1, 1, 0, 0, 0});
	while(!q.empty())
	{
		node u = q.front();
		q.pop();
		if(dis[u.x][u.y][u.smell][u.pre] <= u.step)
		{
			continue;
		}
		dis[u.x][u.y][u.smell][u.pre] = u.step;
		if(u.pre)
		{
			int xx = u.x + dx[u.pre], yy = u.y + dy[u.pre];
			if(!check(xx, yy, u.smell))
			{
				update(u);
			}
			else if(a[xx][yy] == 4)
			{
				q.push((node){xx, yy, u.step + 1, u.smell, u.pre});
			}
			else
			{
				if(a[xx][yy] == 2)
				{
					q.push((node){xx, yy, u.step + 1, 1, 0});
				}
				else
				{
					q.push((node){xx, yy, u.step + 1, u.smell, 0});
				}
			}
			continue;
		}
		update(u);
	}
	return;
}
```

最后在所有的 ```dis[n][m]``` 中取最小值输出即可。

------

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1005
struct node
{
	int x, y, step, smell, pre;
};
queue<node> q;
int n, m, a[N][N], dis[N][N][2][5];
inline bool check(int x, int y, int smell)
{
	if(x < 1 || x > n || y < 1 || y > m)
	{
		return 0;
	}
	if(!a[x][y] || (a[x][y] == 3 && !smell))
	{
		return 0;
	}
	return 1;
}
const int dx[5] = {0, 1, 0, 0, -1}, dy[5] = {0, 0, 1, -1, 0};
inline void update(node u)
{
	for(int i = 1; i <= 4; i++)
	{
		int xx = u.x + dx[i], yy = u.y + dy[i];
		if(check(xx, yy, u.smell))
		{
			if(a[xx][yy] == 2)
			{
				q.push((node){xx, yy, u.step + 1, 1, 0});
			}
			else if(a[xx][yy] == 4)
			{
				q.push((node){xx, yy, u.step + 1, 0, i});
			}
			else
			{
				q.push((node){xx, yy, u.step + 1, u.smell, 0});
			}
		}
	}
	return;
}
inline void bfs()
{
	q.push((node){1, 1, 0, 0, 0});
	while(!q.empty())
	{
		node u = q.front();
		q.pop();
		if(dis[u.x][u.y][u.smell][u.pre] <= u.step)
		{
			continue;
		}
		dis[u.x][u.y][u.smell][u.pre] = u.step;
		if(u.pre)
		{
			int xx = u.x + dx[u.pre], yy = u.y + dy[u.pre];
			if(!check(xx, yy, u.smell))
			{
				update(u);
			}
			else if(a[xx][yy] == 4)
			{
				q.push((node){xx, yy, u.step + 1, u.smell, u.pre});
			}
			else
			{
				if(a[xx][yy] == 2)
				{
					q.push((node){xx, yy, u.step + 1, 1, 0});
				}
				else
				{
					q.push((node){xx, yy, u.step + 1, u.smell, 0});
				}
			}
			continue;
		}
		update(u);
	}
	return;
}
inline void debug()
{
	putchar(10);
	putchar(10);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int tmp = 0x3f3f3f3f;
			for(int k = 0; k <= 5; k++)
			{
				tmp = min(tmp, min(dis[i][j][0][k], dis[i][j][1][k]));
			}
			printf("%d ", (tmp == 0x3f3f3f3f ? -1 : tmp));
		}
		putchar(10);
	}
	putchar(10);
	putchar(10);
	return;
}
signed main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	bfs();
	//debug();
	int ans = 0x3f3f3f3f;
	for(int i = 0; i <= 5; i++)
	{
		ans = min(ans, min(dis[n][m][0][i], dis[n][m][1][i]));
	}
	printf("%d", (ans == 0x3f3f3f3f ? -1 : ans));
	return 0;
}
```



---

## 作者：Lijiangjun4 (赞：0)

# P4818 题解
注：题目翻译中将原文的 blue 翻译成了绿色，本文统一改为蓝色。
## 解题思路
$1 \leq N,M \leq 1000$，所以我们可以放心大胆地**广搜**。  
对于每个节点，需要记录的信息有：
- 坐标；
- 步数；
- 橙子味；
- 方向（计算紫色方格时要用到）。

拓展每个节点的时候，先特判紫色格，如果可以漂移就将漂移后的格子推入队列，否则向四个方向进行拓展。  
为减小复杂度，记录 bool 数组 `vis[i][j][0/1][pre]` 来进行去重，其中 $i$ 为行号，$j$ 为列号，$0/1$ 表示是否带橙子味，$pre$ 为方向。

时间复杂度为 $O(nm)$，可以通过。

## AC Code

```cpp
#include<iostream>
#include<queue>
#define RED 0
#define PINK 1
#define ORANGE 2
#define BLUE 3
#define PURPLE 4
using namespace std;
int n,m;
struct node
{
	int step;    //步数 
	int f;       //方向 
	int x,y;     //坐标 
	bool orange; //橙子味 
};
queue<node> q;
int a[1005][1005],vis[1005][1005][2][5];
int px[4]={1,0,0,-1};
int py[4]={0,1,-1,0};
int bfs()
{
	q.push(node{0,0,1,1,false});
	while(q.size())
	{
		node t=q.front();
		q.pop();
		int x=t.x;
		int y=t.y;
		int step=t.step;
		int f=t.f;
		bool orange=t.orange;
		
		if(vis[x][y][orange][f]) continue;
		vis[x][y][orange][f]=true;
		if(x==n&&y==m) return step;
		
		//紫色格子
		bool flag=false;//能否漂移 
		if(a[x][y]==PURPLE)
		{
			int dx=x+px[f],dy=y+py[f];
			if(a[dx][dy]==RED||a[dx][dy]==BLUE)
			{
				/*啥也不做*/; 
			}
			else if(a[dx][dy]==PINK||a[dx][dy]==PURPLE)
			{
				q.push(node{step+1,f,dx,dy,false});
				flag=true;
			}
			else
			{
				q.push(node{step+1,f,dx,dy,true});
				flag=true;
			}
		}
		
		if(a[x][y]==PURPLE&&flag) continue;//已经漂移
		
		for(int i=0;i<4;i++)//枚举方向
		{
			int dx=x+px[i],dy=y+py[i];
			if(a[dx][dy]==RED) 
			{
				continue;
			}
			if(a[dx][dy]==BLUE && orange==false)
			{
				continue;
			}
			if(a[dx][dy]==ORANGE)
			{
				q.push(node{step+1,i,dx,dy,true});
			}
			else
			{
				q.push(node{step+1,i,dx,dy,orange});
			}
		}
	}
	return -1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	cout<<bfs();
	return 0;
}
```
[AC啦！](https://www.luogu.com.cn/record/173283262)

---

