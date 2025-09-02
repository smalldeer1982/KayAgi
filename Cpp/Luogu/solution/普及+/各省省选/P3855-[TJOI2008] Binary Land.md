# [TJOI2008] Binary Land

## 题目背景

Binary Land是一款任天堂红白机上的经典游戏，讲述的是两只相爱的企鹅Gurin和Malon的故事。两只企鹅在一个封闭的迷宫中，你可以控制他们向上下左右四个方向移动。但是他们的移动有一个奇怪的规则，即如果你按“上”或“下”方向键，两只企鹅会同时向上移动或向下移动1格；如果你按“左”方向键，则Malon向左移动1格，同时Gurin向右移动1格；如果你按“右”方向键，则Malon向右移动1格，Gurin向左移动1格。当然，如果某只企鹅被障碍挡住，它就不会移动了。另外，在迷宫的某些格子处有蜘蛛网，如果任何一只企鹅进入这种格子，则游戏失败。两只企鹅不会相互阻挡，即在相向运动时他们可以“穿过”彼此，也可以同时处于同一格子里。迷宫的某个格子上有一颗红心，游戏的任务就是使两只企鹅同时到达这个格子。

![](https://cdn.luogu.com.cn/upload/pic/6099.png)


## 题目描述

请编写程序找出完成任务所需的最少的操作步数。如果无法完成目标，输出“no”。


## 说明/提示

满足要求的一个操作序列为：上－右－左－左

3 ≤ R, C ≤ 30


## 样例 #1

### 输入

```
4 7
#######
#..T..#
#G##M##
#######
```

### 输出

```
4```

# 题解

## 作者：基地A_I (赞：8)

## 前言

本来想刷DP题刷到了这个（为什么标签里面有动态规划？），权当复习一下Bfs吧。

~~前面的dalao吊打我~~，我的代码比较繁琐emm。

## 题解

熟练Bfs的同学应该不要多讲吧，思路简单

### $\text{Bfs前准备}$

~~定义状态~~ Node
> xG,yG,xM,yM,step;	//表示**G与M的位置,移动步数**，看成一个**整体**

自然就有了**四维的vis数组** $vis[xG][yG][xM][yM]$，来表示**这个状态是否经历过**。

### $\text{Bfs}$

- 上下一起走

- 往左 G右 M左　；　往右　G左 M右 (~~有点绕~~)

- **注意：撞墙‘#’回来，蜘蛛网‘X’不可以走** ~~(不懂可以看一下游戏视频)~~

- 处理好这几点，你就可以A了这题。

## 后记

关于游戏视频 ---> [bilibili传送门](https://www.bilibili.com/video/av18788142?from=search&seid=1100729523807638344) （~~这个游戏看起来还蛮好玩~~）

祝你AC （~~其实这道题不是很水qwq~~）

$\texttt{Code}$


```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define N 37
using namespace std;
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};
int n,m,XG,YG,XM,YM,ans=-1;
char map[N][N];
bool vis[N][N][N][N];
struct Node {
	int xG,yG;
	int xM,yM;
	int step;
};
queue<Node> q;
//	修改操作 （入队列，标记） 
inline void update(int x1,int y1,int x2,int y2,int step) {
	q.push((Node){x1,y1,x2,y2,step});
	vis[x1][y1][x2][y2] = 1;
}
//	判断是否能走 
inline bool check(int x1,int y1,int x2,int y2) {
	if(x1>=1&&x1<=n&&y1>=1&&y1<=m && x2>=1&&x2<=n&&y2>=1&&y2<=m)
		if(map[x1][y1]!='X' && map[x2][y2]!='X' && !vis[x1][y1][x2][y2])
			return 1;
	return 0;
}
//	判断是否到终点 
inline bool result(int x1,int y1,int x2,int y2) {
	if(map[x1][y1]=='T' && map[x2][y2]=='T')
		return 1;
	return 0;
}
//	一次操作 
inline bool work(int nx1,int ny1,int nx2,int ny2,int step)
{
	if(result(nx1,ny1,nx2,ny2))  {
		ans = step + 1;
			return 1;
		}
	if(check(nx1,ny1,nx2,ny2))	
		update(nx1,ny1,nx2,ny2,step+1);
	return 0;
}
void Bfs()
{
	update(XG,YG,XM,YM,0);
	while(!q.empty())
	{
		Node now = q.front(); q.pop();
//		printf("OK  ");
//		printf("xG=%d,yG=%d  xM=%d,yM=%d ,step=%d\n",now.xG,now.yG,now.xM,now.yM,now.step);
		for(int i=0;i<2;++i)
		{
			int nx1 = now.xG + dx[i] ,ny1 = now.yG + dy[i];
			int nx2 = now.xM + dx[i] ,ny2 = now.yM + dy[i];
		if(map[nx1][ny1] == '#') nx1=now.xG ,ny1=now.yG;	//挡住不走 
		if(map[nx2][ny2] == '#') nx2=now.xM ,ny2=now.yM;
			if(work(nx1,ny1,nx2,ny2,now.step)) return ;
		}
		int nx1,ny1,nx2,ny2;
//		往右走 G左，M右 
		nx1 = now.xG + dx[2] ,ny1 = now.yG + dy[2];
		nx2 = now.xM + dx[3] ,ny2 = now.yM + dy[3];
		if(map[nx1][ny1] == '#') nx1=now.xG ,ny1=now.yG;	//挡住不走 
		if(map[nx2][ny2] == '#') nx2=now.xM ,ny2=now.yM;
		if(work(nx1,ny1,nx2,ny2,now.step)) return ;
//		往左走 G右，M左 
		nx1 = now.xG + dx[3] ,ny1 = now.yG + dy[3];
		nx2 = now.xM + dx[2] ,ny2 = now.yM + dy[2];
		if(map[nx1][ny1] == '#') nx1=now.xG ,ny1=now.yG;	//挡住不走 
		if(map[nx2][ny2] == '#') nx2=now.xM ,ny2=now.yM;
		if(work(nx1,ny1,nx2,ny2,now.step)) return ;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			cin >> map[i][j];
			if(map[i][j] == 'G') XG=i ,YG=j;
			if(map[i][j] == 'M') XM=i ,YM=j; 
		}
	Bfs();
	if(ans == -1) printf("no\n");
	else printf("%d\n",ans);
	return 0; 
}
```


---

## 作者：☯☯枫☯☯ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P3855)

**算法分析：BFS**

~~显然是爆搜题（虽然不知道为什么有 dp 标签）（雾）。~~

首先是状态，我们应该记录两只企鹅的位置和走到当前状态所需的步数，如果走过这个状态，那么不再重复走。

```
struct P {
	int x,y,a,b,step;//位置，步数 
}g,m;
```

其次是对状态的可行性检查。我在检查状态完毕后直接对状态进行了修改，这样可以使 BFS 主体简短一点。

```
inline bool check(int &x,int &y,int &a,int &b,P t) {
	//t 是没移动之前的状态 
	if(pc[x][y]=='X'||pc[a][b]=='X'){//蜘蛛网，失败 
		vis[x][y][a][b]=1;
		return false;
	}
	if(pc[x][y]=='#')vis[x][y][a][b]=1,x=t.x,y=t.y;//其中一只撞到了，就往回退 
	if(pc[a][b]=='#')vis[x][y][a][b]=1,a=t.a,b=t.b;//另一只... 
	if(vis[x][y][a][b])return false;//如果两只都撞到了，那么vis一定被标记过，退出 
	vis[x][y][a][b]=1;//没走过的状态，标记一下 
	return true;
}
```

最后是一些小技巧。比如说，预处理两只企鹅的移动，记录在数组 $g_1$ 和 $g_2$ 里。在预处理时，直接将两只企鹅的移动方式对应起来，这样在移动时比较方便（详见代码）。

---

下面是~~喜闻乐见的~~代码：
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
const int N=50;
bool vis[N][N][N][N];
char pc[N][N];
int g1[10][2] {1,0,0,-1,0,1,-1,0};
int g2[10][2] {1,0,0,1,0,-1,-1,0};
//g1 和 g2 在储存时直接对应起来 
struct P {
	int x,y,a,b,step;//位置，步数 
}g,m;
inline bool check(int &x,int &y,int &a,int &b,P t) {
	//t 是没移动之前的状态 
	if(pc[x][y]=='X'||pc[a][b]=='X'){//蜘蛛网，失败 
		vis[x][y][a][b]=1;
		return false;
	}
	if(pc[x][y]=='#')vis[x][y][a][b]=1,x=t.x,y=t.y;//其中一只撞到了，就往回退 
	if(pc[a][b]=='#')vis[x][y][a][b]=1,a=t.a,b=t.b;//另一只... 
	if(vis[x][y][a][b])return false;//如果两只都撞到了，那么vis一定被标记过，退出 
	vis[x][y][a][b]=1;//没走过的状态，标记一下 
	return true;
}
inline void bfs(int xx,int yy,int aa,int bb) {
	queue<P> q;
	q.push({xx,yy,aa,bb,0});
	vis[xx][yy][aa][bb]=1;
	while(!q.empty()) {
		reg P t=q.front();
		q.pop();
		for(reg int i=0; i<4; i++) {
			reg int x=t.x+g1[i][0],y=t.y+g1[i][1];//移动 
			reg int a=t.a+g2[i][0],b=t.b+g2[i][1];
			if(check(x,y,a,b,t)) {
				if(pc[x][y]=='T'&&pc[a][b]=='T') {//走到终点了 
					printf("%d",t.step+1);
					exit(0);
				}
				q.push({x,y,a,b,t.step+1});
			}
		}
	}
}
int main() {
	cin.tie(0);
	reg int r,c;
	cin>>r>>c;
	for(reg int i=1;i<=r;i++){
		for(reg int j=1;j<=c;j++){
			cin>>pc[i][j];
			if(pc[i][j]=='G')g={i,j};//Gurin位置 
			if(pc[i][j]=='M')m={i,j};//Malon位置 
		}
	}
	bfs(g.x,g.y,m.x,m.y);
	cout<<"no";
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/49355843)

~~（目前最优解）~~

欢迎交流讨论，请点个赞哦~

---

## 作者：Aurora_Borealis_ (赞：3)

# P3855 Binary Land 题解

【题意】

在一个迷宫里，有两个企鹅，简称为G和M，让你把他们在**同一时间**走到指定点。当按“上下”键时，两只企鹅都**同时向上/下移动**，当按“左右”键时，听话的M会**跟着键盘走**，而叛逆的G会**反着来**。

企鹅如果走到蛛网上，则失败。

【解析】

典型的一道走迷宫题，考虑搜索求解。但考虑到障碍物少时DFS可能会TLE，而本题空间足够，所以使用BFS。

因为有两只企鹅，所以考虑用四维数组$ flag_{gx,gy,mx,my}$来判重，其中$ gx $,$gy $表示G的坐标,$ mx $,$ my $表示M的坐标。

入队时，则只在“两只企鹅至少有一只移动的情况下”入队。

【代码】
```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int gsx,msx,gsy,msy,fx,fy;
char a[35][35];
bool flag[35][35][35][35];
struct pen{
	int gx,gy,mx,my,step;
};
queue<pen>q;
int xx[4]={-1,1,0,0};
int yy[4]={0,0,1,-1};
void bfs(){
	memset(flag,0,sizeof(flag));
	bool ok=1;
	flag[gsx][gsy][msx][msy]=1;
	q.push((pen){gsx,gsy,msx,msy,0});
	while(!q.empty()){
		pen tot=q.front();
		//cout<<tot.gx<<" "<<tot.gy<<" "<<tot.mx<<" "<<tot.my<<" "<<tot.step<<endl;
		q.pop();
		if(tot.gx==fx&&tot.mx==fx&&tot.gy==fy&&tot.my==fy){
			cout<<tot.step;
			ok=0;
			break;
		}
		for(int i=0;i<2;i++){
			int ngx=tot.gx+xx[i],ngy=tot.gy+yy[i];
			int nmx=tot.mx+xx[i],nmy=tot.my+yy[i];
			if(a[ngx][ngy]=='X'||a[nmx][nmy]=='X') continue;//蛛网不走
			if(a[ngx][ngy]=='#'&&a[nmx][nmy]=='#') continue;//不动不走
			if(a[ngx][ngy]=='#'){//G被挡着不走
				if(flag[tot.gx][tot.gy][nmx][nmy]) continue;
				flag[tot.gx][tot.gy][nmx][nmy]=1;
				q.push((pen){tot.gx,tot.gy,nmx,nmy,tot.step+1});
			}else if(a[nmx][nmy]=='#'){//M被挡着不走
				if(flag[ngx][ngy][tot.mx][tot.my]) continue;
				flag[ngx][ngy][tot.mx][tot.my]=1;
				q.push((pen){ngx,ngy,tot.mx,tot.my,tot.step+1});
			}else{//谁都没被挡着
				if(flag[ngx][ngy][nmx][nmy]) continue;
				flag[ngx][ngy][nmx][nmy]=1;
				q.push((pen){ngx,ngy,nmx,nmy,tot.step+1});
			}
		}
		for(int i=2;i<4;i++){
			int ngx=tot.gx-xx[i],ngy=tot.gy-yy[i];//因为G要反着来，所以减去
			int nmx=tot.mx+xx[i],nmy=tot.my+yy[i];
			if(a[ngx][ngy]=='X'||a[nmx][nmy]=='X') continue;
			if(a[ngx][ngy]=='#'&&a[nmx][nmy]=='#') continue;
			if(a[ngx][ngy]=='#'){
				if(flag[tot.gx][tot.gy][nmx][nmy]) continue;
				flag[tot.gx][tot.gy][nmx][nmy]=1;
				q.push((pen){tot.gx,tot.gy,nmx,nmy,tot.step+1});
			}else if(a[nmx][nmy]=='#'){
				if(flag[ngx][ngy][tot.mx][tot.my]) continue;
				flag[ngx][ngy][tot.mx][tot.my]=1;
				q.push((pen){ngx,ngy,tot.mx,tot.my,tot.step+1});
			}else{
				if(flag[ngx][ngy][nmx][nmy]) continue;
				flag[ngx][ngy][nmx][nmy]=1;
				q.push((pen){ngx,ngy,nmx,nmy,tot.step+1});
			}
		}
	}
	if(ok==1) cout<<"no";
	return;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='G'){
				gsx=i,gsy=j;
			}
			if(a[i][j]=='M'){
				msx=i,msy=j;
			}
			if(a[i][j]=='T'){
				fx=i,fy=j;
			}
		} 
	}
	bfs();
	return 0;
} 
```


---

## 作者：hater (赞：3)

这道题目应该改一下难度

~~感觉像恶意评分~~

前面有一位大佬过了

因为有题意 ：

题目描述

请编写程序找出完成任务所需的**最少的操作步数**。如果无法完成目标，输出“no”。

我也来用BFS跟一波

首先 这是一道不太寻常的搜索

不同于有两个企鹅同时行走

那么如何表示节点的信息呢

这个不难 

x1,y1(表示第一只企鹅的位置）,

x2,y2（表示第二只企鹅的位置）,

step（表示扩展到这个节点所需的步数）

封装在一个结构体里

之后用四维的vis数组表示节点是否扩展到

二维是不行的

因为一只企鹅走到（x,y)时

另一只企鹅可以在许多不同的位置上

最后是关于两只企鹅的行走 以及对墙和蜘蛛网的判断

方向不要搞混 逻辑要清晰

最后是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s1x,s1y,s2x,s2y;
struct mmp
{
    int x1,y1,x2,y2,step;
}f,v;
queue <mmp> q;
char Map[35][35];
bool vis[35][35][35][35];
int l1[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int l2[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
int bfs()
{
    vis[f.x1][f.y1][f.x2][f.y2]=1;
    q.push(f);
    while(!q.empty())
    {
        f=q.front(); q.pop();
        if(Map[f.x1][f.y1]=='T'&&Map[f.x2][f.y2]=='T') return f.step;
        //cout<<f.x1<<" "<<f.y1<<" "<<f.x2<<" "<<f.y2<<" "<<f.step<<endl;
        for(int i=0;i<4;i++)
        {
            v.x1=f.x1+l1[i][0];
            v.y1=f.y1+l1[i][1];
            v.x2=f.x2+l2[i][0];
            v.y2=f.y2+l2[i][1];
            v.step=f.step+1;
            if(v.x1<1||v.x1>n||v.y1<1||v.y1>m||v.x2<1||v.x2>n||v.y2<1||v.y2>m) continue;
            if(Map[v.x1][v.y1]=='#') v.x1=f.x1,v.y1=f.y1;
            if(Map[v.x2][v.y2]=='#') v.x2=f.x2,v.y2=f.y2;
            if(Map[v.x1][v.y1]=='X'||Map[v.x2][v.y2]=='X') continue;
            if(vis[v.x1][v.y1][v.x2][v.y2]) continue;
            vis[v.x1][v.y1][v.x2][v.y2]=1; q.push(v);
        }
    } 
    return -1;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
      {
      	  cin>>Map[i][j];
      	  if(Map[i][j]=='G') f.x1=i,f.y1=j;
      	  if(Map[i][j]=='M') f.x2=i,f.y2=j;
      }
    int ans=bfs();
    if(ans==-1) cout<<"no"<<endl;
      else cout<<ans<<endl;
    return 0;
}
```
~~不要在意奇怪的结构体的名字~~

最后温馨提示您：

AC千万条 仔细第一条

注释没注释 红光两行泪

我就因此WA了一次排查了 1 hour

---

## 作者：落花月朦胧 (赞：2)

马上就要考 SCP 了，赶紧写一些题解积累人品

## P3855 [TJOI2008]Binary Land 题解

~~很明显~~ 可以看出这道题就是一个 BFS 的题目，利用 BFS 暴力搜到答案。

### 题目在讲什么

先输入行数 $N$ 列数 $M$，再输入一个 $N * M$ 的字符串矩阵

有 1 对情侣，他们的位置在矩阵中分别用 $G$, $M$ 表示。

他们的运动方式特别， 上下运动他们运动方向是一样的，左右运动则相反。

最后他们要在 $T$ 点相遇，问最小的操作次数。

### 为什么BFS

+ 用矩阵读入，在一张图上操作，一般方法是搜索。

+ ~~标签里有~~。

+ 求的是操作次数， 可见是一道 BFS 的模板题再多一点东西。

### 如何处理方向相反

大家都知道，在 BFS 的题中经常会用 2 个数组分别表示向 $x$, $y$ 方向的移动步数

由于这里是 2 个角色， 我们也要用 4 个数组来表示。

稍微一想就可以想到把数组 $x$ 不变， $y$ 相反即可

### 关于结构体

这很好想，有 2 个角色， 可以分别用 2 个 pair 模拟， 最后再来一个队列表示步数就可以了，他们都是同时进行的，故步数只用一个即可。

其中也可以用一个结构体解决，但我用的是前者。

### 关于 MLE

开始我的代码是这样的：

[MLE代码](https://www.luogu.com.cn/paste/huze9wpa)

貌似没错，一交就基本全部 $MLE$ 了。

[MLE记录](https://www.luogu.com.cn/record/59828580)

经过检查发现没有用 $VIS$ 数组， 当即开了一四维数组表示状态，结果直接就过了

代码如下：（不用云剪贴板了

```cpp
#include <bits/stdc++.h>

using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') f=ch=='-'?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
inline void print(int x){
	char P[105];int w=0;if(x==0){putchar('0');return;}
	if(x<0) putchar('-'),x=-x;
	while(x) P[++w]=x%10+'0',x/=10;
	for(int i=w; i>=1; i--) putchar(P[i]);
}
struct node {
	int x, y;
} One_start, Two_start;
queue<node> one, two;
queue<int> q;
const int N = 30;
const int dx[] = {0, 0, 1, -1},
		  dy[] = {1, -1, 0, 0},
		  Dx[] = {0, 0, 1, -1},
		  Dy[] = {-1, 1, 0, 0};
int n, m;
bool vis[40][40][40][40];
char ch[N + 1][N + 1];
inline bool  check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m && ch[x][y] != 'X';
}
inline void bfs() {
	one.push(One_start), two.push(Two_start); q.push(0);
	while ("MLE") {
		if (one.empty()) break;
		if (two.empty()) break;
		if (q.empty()) break;
		int cnt = q.front(); q.pop();
		node o = one.front(), t = two.front();one.pop();two.pop();
		if (vis[o.x][o.y][t.x][t.y]) continue;
		vis[o.x][o.y][t.x][t.y] ^= 1;
		if (o.x == t.x && o.y == t.y && ch[o.x][o.y] == 'T') {
			print(cnt);
			exit(0);
		}
		for (int i = 0; i < 4; i++) {
			int x = dx[i] + o.x, y = dy[i] + o.y,
				X = Dx[i] + t.x, Y = Dy[i] + t.y;
			if (check(x, y) && check(X, Y)) {
				if (ch[x][y] == '#') 
					one.push({o.x, o.y});
				else 
					one.push({x, y});
				if (ch[X][Y] == '#') 
					two.push({t.x, t.y});
				else 
					two.push({X, Y});
				q.push(cnt + 1);
			}
		}
	}
}
int main () {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> ch[i][j];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		if (ch[i][j] == 'G') One_start = {i, j};
		if (ch[i][j] == 'M') Two_start = {i, j};
	}
	bfs();
	puts("no");
	return 0;
}
```



---

## 作者：借我昔日热忱 (赞：2)

** _~~又是一道不错的BFS练习题~~_ **
## 本题特色
首先，让我们来看看本题特色（毒瘤）的点：**两只企鹅**

**一，两只企鹅的状态处理**

欸嘿，这就与平常遇到的单个对象运动复杂了一点，主要复杂在：**如何对两只企鹅进行同时处理**

因为要同时处理，还要进行入队操作，所以自然想到两只企鹅的坐标必须封装在**同一个结构体中**。

**二，判定入队**

现在可以进行同时操作了，但是因为有两个对象，再结合题目的限制条件可以得到两条判定入队的基本规律：

**1.只要有一企鹅移动就属于一种新的状态，应该入队。**

也就是要实现一只企鹅撞墙时的“**退步**”操作

**2.只要有一只企鹅会碰到蜘蛛网，此状态作废。**

这两点实现了，那么入队操作就基本没有问题。

**三，关于读入地图**

我用的读入方法是字符转Ascll码在处理，这个方法稍微有些麻烦，不推荐使用。（纯属本人恶习）

全代码如下
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=50;
int map[40][40];
int dir[4][4]={-1,0,-1,0,1,0,1,0,0,-1,0,1,0,1,0,-1};
struct node{
	int mx,my,gx,gy;
	int step;
};
bool checkm(node w){
	if(map[w.mx][w.my]==13||map[w.mx][w.my]==119) return 1;
	else return 0;
}
bool checkg(node w){
	if(map[w.gx][w.gy]==13||map[w.gx][w.gy]==119) return 1;
	else return 0;
}
bool vis[maxn][maxn][maxn][maxn];
int bfs(node start){
	queue<node>q;
	q.push(start);
	node now,next;
	while(!q.empty()){
		now=q.front();
		for(int i=0;i<4;i++){
			next.mx=now.mx+dir[i][0];
			next.my=now.my+dir[i][1];
			next.gx=now.gx+dir[i][2];
			next.gy=now.gy+dir[i][3];
			next.step=now.step+1;
			if(map[next.gx][next.gy]==123||map[next.mx][next.my]==123) 
				continue;
			if(!checkm(next)){
				next.mx-=dir[i][0];
				next.my-=dir[i][1];
			}
			if(!checkg(next)){
				next.gx-=dir[i][2];
				next.gy-=dir[i][3];
			}
			if(map[next.gx][next.gy]==119&&map[next.mx][next.my]==119)
				return next.step;
			if(vis[next.gx][next.gy][next.mx][next.my]==0){
				q.push(next); 
				vis[next.gx][next.gy][next.mx][next.my]=1;
			//	printf("%d ",i);
			} 
				
		}
		q.pop();
	}
	return -1;
}
node st;
int main(){
	int r,c;
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;i++){
		string a;
		cin>>a;
		for(int j=1;j<=c;j++) {
			map[i][j]=a[j-1]^35; 
			if(map[i][j]==100){
				 map[i][j]=13;
				 st.mx=i;st.my=j;st.step=0;
			}
			if(map[i][j]==110){
				 map[i][j]=13;
				 st.gx=i;st.gy=j;st.step=0;	
			}
		}
	}
	vis[st.gx][st.gy][st.mx][st.my]=1;
	int ans=bfs(st);
	if(ans==-1) printf("no");
	else printf("%d",ans);

	return 0;
} 
```





---

## 作者：Konnyaku_ljc (赞：2)

关于各种迷宫的最短路，当然是毫不犹豫的BFS  
但是本题的BFS，还是有几个需要注意的地方  
- 如果你按“左”方向键，则Malon向左移动1格，同时Gurin向右移动1格；如果你按“右”方向键，则Malon向右移动1格
- 如果某只企鹅被障碍挡住，它就不会移动了（我开始没看见。。。）
- 在相向运动时他们可以“穿过”  

我感到唯一的难点就是被障碍挡住后就不会移动  
因为他不会移动，我们先假设他移动到了下一个点，若是障碍，再退回就好了qwq  
首先，我们定义一个结构体
```cpp
struct node { 
    int Gx,Gy,Mx,My,num; 
};
node p,f;
//Gx，Gy是Gurin的位置
//Mx，My是Malon的位置
//num是走的步数
```
剩下的定义
```cpp
int r,c;//图的大小
char a[32][32];//存图
bool v[32][32][32][32];
//第一维是Gx,第二维是Gy
//第三维是Mx,第四维是My
const int X[4] = {1,-1,0,0};
const int Y[4] = {0,0,1,-1};
//两个方向数组
queue<node> q;
//广搜用结构体
```
毫无新意的输入输出
```cpp
void _in()
{
	cin >> r >> c;
	for ( int i = 1; i <= r; i++ )
	    for ( int j = 1; j <= c; j++ )
	    {
	    	cin >> a[i][j];//将两点存下来
	    	if ( a[i][j] == 'G' ) p.Gx = i,p.Gy = j;
	    	if ( a[i][j] == 'M' ) p.Mx = i,p.My = j;
		}
	v[p.Gx][p.Gy][p.Mx][p.My] = 1;//此四点的组合已到达！
	q.push(p);//弹入队列
}
```
下面是广搜
```cpp
void bfs()//重点！！！
{
	while ( !q.empty() )//广搜基操
	{
		p = q.front() ;//取队头元素
		q.pop() ;//弹出队头
		for ( int i = 0; i < 4; i++ )
		{
			f = p;
			f.Gx += X[i] , f.Gy += Y[i];
			f.Mx += X[i] , f.My -= Y[i];
			f.num++;//将f（下一个点）记录下来
			if ( a[f.Gx][f.Gy] == '#' ) f.Gx -= X[i] , f.Gy -= Y[i];
			if ( a[f.Mx][f.My] == '#' ) f.Mx -= X[i] , f.My += Y[i];
            //若此点达不到，就相当于被挡住，退回上一个点
			if ( a[f.Gx][f.Gy] == 'T' && a[f.Mx][f.My] == 'T' )
			    cout << f.num , exit(0);//当到达终点，输出并结束程序
                //exit(0)在algorithm里，可直接将程序强制返回0（结束）
			if ( f.Gx <= r && f.Gy <= c && f.Mx <= r && f.My <= c )
            //超出图范围时，返回
			    if ( f.Gx >= 1 && f.Gy >= 1 && f.Mx >= 1 && f.My >= 1 )
                ////超出图范围时，返回
			        if ( a[f.Gx][f.Gy] != 'X' && a[f.Mx][f.My] != 'X' )
                    //为蜘蛛网时，返回
			            if ( !v[f.Gx][f.Gy][f.Mx][f.My] )
                        //此点走过时，返回
			                v[f.Gx][f.Gy][f.Mx][f.My] = 1 , q.push(f);
                            //标记此点到达过，弹入队列
		}
	}
	cout << "no";//到不了终点（为什么游戏会无解？qwq）
	exit(0);//强制结束
}
```
高大威猛的主函数
```cpp
int main()
{
	_in ();
	bfs ();
}
```
完整代码，码风较丑，不喜勿喷
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct node { 
    int Gx,Gy,Mx,My,num; 
};
node p,f;
int r,c;
char a[32][32];
bool v[32][32][32][32];
const int X[4] = {1,-1,0,0};
const int Y[4] = {0,0,1,-1};
queue<node> q;
void bfs()
{
	while ( !q.empty() )
	{
		p = q.front() ;
		q.pop() ;
		for ( int i = 0; i < 4; i++ )
		{
			f = p;
			f.Gx += X[i] , f.Gy += Y[i];
			f.Mx += X[i] , f.My -= Y[i];
			f.num++;
			if ( a[f.Gx][f.Gy] == '#' ) f.Gx -= X[i] , f.Gy -= Y[i];
			if ( a[f.Mx][f.My] == '#' ) f.Mx -= X[i] , f.My += Y[i];
			if ( a[f.Gx][f.Gy] == 'T' && a[f.Mx][f.My] == 'T' )
			    cout << f.num , exit(0);
			if ( f.Gx <= r && f.Gy <= c && f.Mx <= r && f.My <= c ) 
			    if ( f.Gx >= 1 && f.Gy >= 1 && f.Mx >= 1 && f.My >= 1 )
			        if ( a[f.Gx][f.Gy] != 'X' && a[f.Mx][f.My] != 'X' )
			            if ( !v[f.Gx][f.Gy][f.Mx][f.My] )
			                v[f.Gx][f.Gy][f.Mx][f.My] = 1 , q.push(f);
		}
	}
	cout << "no";
	exit(0);
}
void _in()
{
	cin >> r >> c;
	for ( int i = 1; i <= r; i++ )
	    for ( int j = 1; j <= c; j++ )
	    {
	    	cin >> a[i][j];
	    	if ( a[i][j] == 'G' ) p.Gx = i,p.Gy = j;
	    	if ( a[i][j] == 'M' ) p.Mx = i,p.My = j;
		}
	v[p.Gx][p.Gy][p.Mx][p.My] = 1;
	q.push(p);
}
int main()
{
	_in ();
	bfs ();
}
```

---

## 作者：Mr_罗 (赞：1)

$\tt{upd \ on \ 2021/10/16}$：修改错别字

$\tt{upd \ on \ 2021/10/17}$：删除无意义内容

[题目传送门](https://www.luogu.com.cn/problem/P3855)

## $Part 1$：读题

有两只企鹅叫做 $G$ 和 $M$，移动时上下同向、左右相反，走向墙壁时不会移动，走到蜘蛛网会 $\tt{Game \ Over}$，求同时走向终点所需最少步数。无解输出 `no`。

有几点需要注意：

- 有两只企鹅同时走。

处理方法：定义一个结构体，`gx`、`gy` 里面存 $G$ 的坐标，`mx`、`my` 里面存 $M$ 的坐标。

- 在按下左键时，$G$ 会向右走，$M$ 会向左走。反之亦然。

处理方法：在预处理移动数组时，将 $G$ 和 $M$ 左右移动的位置颠倒。

- 如果有一只企鹅被墙挡住，它就动不了了。

处理方法：先走过去，是障碍再走回来。

- 在相向运动时他们可以“穿过”

处理方法：不用管，正常走（少了一个特判条件）。

- 有蜘蛛网。

处理方法：走到蜘蛛网，就是一个不可行状态。

## $Part 2$：思路

......写 `bfs` 板子。~~这么说会不会有些敷衍？~~

具体思路见代码。

## $Part 3$：代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
    //G的坐标，M的坐标，步数
    int gx, gy, mx, my, st;
} q[1000001];

//队列记得定义大点，否则会RE+WA

//地图大小，G起点坐标，M起点坐标，终点坐标
int n, m, Gx, Gy, Mx, My, Tx, Ty;

//G的移动数组
int gdx[] = {1, 0, -1, 0}, gdy[] = {0, 1, 0, -1};

//M的移动数组
int mdx[] = {1, 0, -1, 0}, mdy[] = {0, -1, 0, 1};

//判重数组，感谢数据范围
bool vis[31][31][31][31];

//地图
char mp[31][31];

//判断能否走
bool check_way (int ggx, int ggy, int mmx, int mmy)
{
    if (mp[ggx][ggy] == 'X' || mp[mmx][mmy] == 'X' || vis[ggx][ggy][mmx][mmy])
        return 0;
    return 1;
}

//套板子
void bfs()
{
    //我习惯 l 指针指向队头前, r 指针指向末尾
    int l = 0, r = 0;
    q[++r] = {Gx, Gy, Mx, My, 0};
    
    while (l < r)
    {
        node tmp = q[++l];
        
        //到终点了
        if (tmp.gx == tmp.mx && tmp.gy == tmp.my && tmp.gx == Tx && tmp.gy == Ty)
        {
            cout << tmp.st << endl;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int dgx = tmp.gx + gdx[i], dgy = tmp.gy + gdy[i];
            int dmx = tmp.mx + mdx[i], dmy = tmp.my + mdy[i];
            
            //是墙？回来！
            if (mp[dgx][dgy] == '#')
                dgx = tmp.gx, dgy = tmp.gy;
            
            //同上
            if (mp[dmx][dmy] == '#')
                dmx = tmp.mx, dmy = tmp.my;
            
            //两边都是墙（一步没走）或无法行走
            if ((dgx == tmp.gx && dgy == tmp.gy && dmx == tmp.mx && dmy == tmp.my) || !check_way (dgx, dgy, dmx, dmy))
                continue;
            q[++r] = {dgx, dgy, dmx, dmy, tmp.st + 1};
            vis[dgx][dgy][dmx][dmy] = 1;
        }
    }
    cout << "no";
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> mp[i][j];
            if (mp[i][j] == 'G')
                Gx = i, Gy = j;
            else if (mp[i][j] == 'M')
                Mx = i, My = j;
            else if (mp[i][j] == 'T')
                Tx = i, Ty = j;
        }
    }
    bfs();
    return 0;
}
```

------------
### 完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

这道题可以使用广度优先搜索解决。

首先，存好地图，存好起点坐标（两个点），存好终点坐标（一个点）。

然后，对于每种情况分别枚举，如果到达蜘蛛网就不接受此命令，如果撞墙就不变化坐标。

最后，到达终点就能输出答案了。

另外，初始化 $ans$ 为 $-1$ 可以处理无解的情况。

看清楚我的四维数组哦，其实不复杂。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define max_n 30
int n;
int m;
int g[max_n+2][max_n+2];
int sx1,sy1;
int sx2,sy2;
int ex,ey;
bool vis[max_n+2][max_n+2][max_n+2][max_n+2];
struct W{
	int x1,y1,x2,y2,t;
}f;
queue<W>q;
const int dx[4]={-1,1,0,0};
const int dy1[4]={0,0,-1,1};
const int dy2[4]={0,0,1,-1};
int ans=-1;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P3855_1.in","r",stdin);
	freopen("P3855_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		char a[max_n+2];
		scanf("%s",a+1);
		for(int j=1;j<=m;++j){
			if(a[j]=='#')g[i][j]=0;
			else if(a[j]=='X')g[i][j]=1;
			else g[i][j]=2;
			if(a[j]=='G'){
				sx1=i;
				sy1=j;
			}
			if(a[j]=='M'){
				sx2=i;
				sy2=j;
			}
			if(a[j]=='T'){
				ex=i;
				ey=j;
			}
		}
	}
	memset(vis,0,sizeof(vis));
	vis[sx1][sy1][sx2][sy2]=true;
	q.push((W){sx1,sy1,sx2,sy2,0});
	while(!q.empty()){
		f=q.front();
		q.pop();
		if(f.x1==ex&&f.y1==ey&&f.x2==ex&&f.y2==ey){
			ans=f.t;
			break;
		}
		for(int d=0,nx1,ny1,nx2,ny2;d<4;++d){
			nx1=f.x1+dx[d];
			ny1=f.y1+dy1[d];
			nx2=f.x2+dx[d];
			ny2=f.y2+dy2[d];
			if(g[nx1][ny1]==1||g[nx2][ny2]==1)continue;
			if(!g[nx1][ny1]){
				nx1=f.x1;
				ny1=f.y1;
			}
			if(!g[nx2][ny2]){
				nx2=f.x2;
				ny2=f.y2;
			}
			if(vis[nx1][ny1][nx2][ny2])continue;
			vis[nx1][ny1][nx2][ny2]=true;
			q.push((W){nx1,ny1,nx2,ny2,f.t+1});
		}
	}
	if(ans==-1)printf("no\n");
	else printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58947628)

By **dengziyue**

---

