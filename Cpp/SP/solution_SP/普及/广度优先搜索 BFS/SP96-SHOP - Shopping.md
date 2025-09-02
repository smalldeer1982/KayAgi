# SHOP - Shopping

## 题目描述

![Crowd in the supermarket](https://cdn.luogu.com.cn/upload/vjudge_pic/SP96/df9f7ec95f8af0b2332c4f2457bc0d39793311a7.png)The old tube screen to your computer turned out to be the cause of your chronic headaches. You therefore decide to buy one of these new flat TFT monitors. At the entrance of the computer shop you see that it is quite full with customers.

In fact, the shop is rather packed with customers and moving inside involves a certain amount of elbowing. Since you want to return home quickly to complete your half finished SPOJ tasks, you want to sidestep the crowd as much as possible. You examine the situation somewhat closer and realise that the crowding is less in some parts of the shop. Thus, there is reason for hope that you can reach your goal in due time, provided that you take the shortest way. But which way is the shortest way?

You sketch the situation on a piece of paper but even so, it is still a tricky affair. You take out your notebook from your pocket and start to write a program which will find the shortest way for you.

## 样例 #1

### 输入

```
4 3
X1S3
42X4
X1D2

5 5
S5213
2X2X5
51248
4X4X2
1445D

0 0```

### 输出

```
4
23```

# 题解

## 作者：Isshiki·Iroha (赞：8)

题目传送门：[SP96](https://www.luogu.com.cn/problem/SP96)

题目要求最短时间，其实就是求最短路，可以用 BFS，先找到起点，以起点为中心，向四个方向拓展，如果没有访问，就加入队列继续更新。但是你不能按板子写，不然会 WA。


如果按板子打，我们很容易（~~困难~~）发现一个问题：对于一个点 $(x,y)$，它第一次被更改后就不再访问了。但是如果后面又有更优解，它就不会继续更新，只会更新 $(x,y)$，所以我们就不用 vis 来判重，能更新就 push。

$10ms$ 代码如下：

```cpp
//只是删除了vis数组，和更改了bfs
void bfs() {
	queue<Chtholly>q;
	dis[sx][sy]=0;
	temp.x=sx;
	temp.y=sy;
	q.push(temp);
	while(!q.empty()) {
		Chtholly L=q.front();
		q.pop();
		ri ux=L.x;
		ri uy=L.y;
		for(ri i=0; i<4; ++i) {
			ri tx=ux+dx[i];
			ri ty=uy+dy[i];
			if(tx<1||ty<1||tx>n||ty>m||maps[tx][ty]==-1)continue;
			if(dis[tx][ty]>dis[ux][uy]+maps[tx][ty]) {
				dis[tx][ty]=dis[ux][uy]+maps[tx][ty];
				if(tx==ex&&ty==ey)continue;
				temp.x=tx;
				temp.y=ty;
				q.push(temp);
			}
		}
	}
}

```

玄学 $0ms$ 优化：

这里是在[倚栏丶听风](https://www.luogu.com.cn/user/247220)大佬的提示下写的:

**你可以试着在遇到数字大于 $1$ 时，比如 $3$，把这个点视作没访问过，站在原地访问 $2$ 次，最终得到的才是最优解（其实和 SPFA 比较像）。**

因为一个能到终点的点，最多能被更新 $3$ 次，因为有一边是到终点的，不可以更新 $4$ 次，那你一想，万一到这个点的一边有分叉，刚好能连续更新勒？那么那个点到这个点之前已经被更新了。所以至多更新 $3$ 次（我的思路）。

那我们判断 vis 小于 $2$ 就加入队列并标记就可以了（按我的思路改成 $3$ 就可以了）。

最后贴上目前最优解代码:

```cpp
#include<bits/stdc++.h>
#define reg register
#define ri reg int
using namespace std;
const int maxn=26;
const int INF=0x3f3f3f3f;
//bool vis[maxn][maxn];
int vis[maxn][maxn];
int dis[maxn][maxn],maps[maxn][maxn];
int n,m,sx,sy,ex,ey;
const int dx[4]= {0,0,1,-1};
const int dy[4]= {1,-1,0,0};
struct Chtholly {
	int x,y;
}temp;
void bfs() {
	queue<Chtholly>q;
	dis[sx][sy]=0;
	vis[sx][sy]=1;
	temp.x=sx;
	temp.y=sy;
	q.push(temp);
	while(!q.empty()) {
		reg Chtholly L=q.front();
		q.pop();
		ri ux=L.x;
		ri uy=L.y;
		for(ri i=0; i<4; ++i) {//四个方向遍历
			ri tx=ux+dx[i];
			ri ty=uy+dy[i];
			if(tx<1||ty<1||tx>n||ty>m||maps[tx][ty]==-1)continue;
			if(dis[tx][ty]>dis[ux][uy]+maps[tx][ty]) {
				dis[tx][ty]=dis[ux][uy]+maps[tx][ty];
				if(tx==ex&&ty==ey)continue;
				if(vis[tx][ty]<2) {
					temp.x=tx;
					temp.y=ty;
					q.push(temp);
					++vis[tx][ty];
				}
			}
		}
	}
}
inline void Memset() {//初始化
	for(ri i(1); i<=n; ++i) {
		for(ri j(1); j<=m; ++j) {
			dis[i][j]=INF;
			vis[i][j]=0;
			maps[i][j]=0;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	reg char a;
	while(true) {
		cin>>m>>n;
		if(n==0&&m==0) {
			return 0;
		}
		Memset();//多测不清空，爆零两行泪
		for(ri i(1); i<=n; ++i) {
			for(ri j(1); j<=m; ++j) {
				cin>>a;
				if(a=='S')sx=i,sy=j;
				else if(a=='D')ex=i,ey=j;
				else if(a=='X')maps[i][j]=-1;
				else maps[i][j]=a-'0';
			}
		}
      //找起点终点
		maps[sx][sy]=0;
		maps[ex][ey]=0;
		bfs();
		cout<<dis[ex][ey]<<endl;
	}
	return 0;
}
```



---

## 作者：Asimplename (赞：4)

首先，遇到搜索题，先要思考一个问题：走过的还要不要再走？

显然是不能的，因为走过的再走一遍说明绕远了。

由于求最短路，所以要用 Bfs。

但是，我们要注意一点，每次时间不是 +1 ，而是加上了矩阵的那一位。如果样例是这个：

3 3

S 4 X

1 D X

1 1 X

如果按照先到后到的顺序，先到的应该是 $a[1][1]$ $\to$ $a[1][2]$ $\to$ $a[2][2]$ , 这样就不是最优的了。

所以，我们需要一个二维数组 $vis[i][j]$ ，来保存起点到 $(i,j)$ 位的最短时间。

然后就上代码吧。

```cpp



#include<iostream>
#include<queue>//队列头文件。
#include<string.h>// memset 头文件

using namespace std;

int _N = 0;
int _M = 0;
char _map[3000][3000];//保存矩阵
int _changeX[5] = {0, 0, 1, 0, -1};//变换行数组。
int _changeY[5] = {0, 1, 0, -1, 0};//变换列数组。
int _vis[3000][3000];//到一个点的最短时间数组。
int _sx = 0;//起点行下标。
int _sy = 0;//起点列下标。
int _ex = 0;//终点行下标。
int _ey = 0;//终点列下标。
int _ste = 2147483647;//初始化到终点的时间为一个最大值。
struct qst{//每个点的信息。
	int x;//行下标。
	int y;//列下标
	int step;//到这个点的时间。
};
queue<qst> _que;

void Bfs() {
	int curX = 0;//到达的点的行下标。
	int curY = 0;//到达的点的列下标。
	int curS = 0;//到达一个点的一种时间。
	qst curQ;
	curQ.x = _sx;//起点行下标为 _sx。
	curQ.y = _sy;//起点列下标为 _sy。
	curQ.step = 0;
	_que.push(curQ);
	while(! _que.empty()){//若队列非空。
		for(int i = 1; i <= 4; i ++){//循环四个方向。
			curQ = _que.front();//要在 for 里每次都取队首，因为 curQ在后面可能变化了。
			curX = curQ.x + _changeX[i];
			curY = curQ.y + _changeY[i];
			if(curX == _ex && curY == _ey){//若到达终点。
				_ste = min(_ste, curQ.step);//找最小时间。
			}
			if(curX >= 1 && curX <= _N && curY >= 1 && curY <= _M && _map[curX][curY] >= '1' && _map[curX][curY] <= '9'){//如果到达的点不出界、可以走。
				curS = curQ.step + (_map[curX][curY] - '0');//由于 _map 是 char 类型，所以要 - '0'。
				if(_vis[curX][curY] < curS){//若到这个点的时间比之前到过的要大。
					continue;
				}
				_vis[curX][curY] = curS;//如果比 _vis[curX][curY] 小，保存这个时间。
				curQ.x = curX;
				curQ.y = curY;
				curQ.step = curS; 
				_que.push(curQ);
			}
		}
		_que.pop();//出队。
	}
}

int main () {
	memset(_vis, 0x7f, sizeof(_vis));//首先把最短时间数组初始化为一个很大的数。
	while(true){
		cin >> _M >> _N;//注意它是先输入列在输入行。
		if(_N == 0 && _M == 0){//若输入 0 0。
			break;
		}
		for(int i = 1; i <= _N; i ++){
			for(int j = 1; j <= _M; j ++){
				cin >> _map[i][j];//输入地图。
				if(_map[i][j] == 'S'){//如果找到起点
					_sx = i;//更新起点行下标。
					_sy = j;//更新起点列下标。
				}
				if(_map[i][j] == 'D'){//若找到终点。
					_ex = i;//更新终点行下标。
					_ey = j;//更新终点列下标。
				}
			}
		}
		Bfs();
		cout << _ste << endl;//输出最小时间。
		while(! _que.empty()){
			_que.pop();//把队列清空。
		}
		memset(_vis, 0x7f, sizeof(_vis));//由于 Bfs 里 _vis 变了，所以要再把它变为最大值。
		_ste = 2147483647;//把 _ste 变为最大值，以便下一次广搜。
	}
	return 0;
}
```

---

## 作者：Scorilon (赞：1)

To [SP96](https://www.spoj.com/problems/SHOP/)

这是一道比较简单的广搜，初学者可以锻炼一下自己理解题意和改代码的能力。

题目中有几个细节：
- $n$ 和 $m$ 的输入顺序，应该先输入 $m$ ，再输入 $n$ 。
- 要注意对换行符的处理。
- 当 $n=0$ $m=0$ 时，结束输入。
- 注意初始化。

一般的 bfs 则是开一个数组来储存这个点有无访问过，可是这道题，所要求的是最短时间，因此访问过的点不一定是最优路径，因此，应该换一种思路，**重开一个数组来储存到达这个点的最短时间**。

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct node{
	int x;
	int y;
	int time;
};
int n,m;
char mp[5000][5000];
int vis[5000][5000];
queue<node> Q;
int sx,sy,ex,ey;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int main(){
	while(1){
		scanf("%d%d",&m,&n);//输入的时候注意m和n的顺序
		if(n==0&&m==0){//结束输入
			break;
		}
		memset(mp,0,sizeof(mp));
		memset(vis,0x7,sizeof(vis));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf(" %c",&mp[i][j]);//过滤换行符
				if(mp[i][j]=='S'){//储存起点坐标
					sx=i;
					sy=j;
				}
				if(mp[i][j]=='D'){//储存终点坐标
					ex=i;
					ey=j;
				}
			}
		}
		node a,b,c;
		a.x=sx;
		a.y=sy;
		a.time=0;
		Q.push(a);
		while(!Q.empty()){
			b=Q.front();
			Q.pop();
			for(int i=0;i<4;i++){
				c.x=b.x+dx[i];
				c.y=b.y+dy[i];
				if(c.x==ex&&c.y==ey){
					if(vis[ex][ey]>b.time) vis[ex][ey]=b.time;
				}
				if(c.x>=0&&c.x<n&&c.y>=0&&c.y<m&&mp[c.x][c.y]>='1'&&mp[c.x][c.y]<='9'){
					c.time=b.time+(mp[c.x][c.y]-'0');
					if(c.time<vis[c.x][c.y]) vis[c.x][c.y]=c.time;
					else continue;//如果此方案无法更优，则直接废除此方案
					a.x=c.x;
					a.y=c.y;
					a.time=c.time;
					Q.push(a);
				}
			}
		}
		printf("%d\n",vis[ex][ey]);
		while(!Q.empty()){//清空队列
			Q.pop();
		}
	}
	return 0;
}
```


---

## 作者：032o35 (赞：0)

纯纯的广搜模板题。

每次到达，先改标志，再打上时间戳（~~这个名词是这么用的吗~~），最后入队。$dis_{i,j}$ 表示到此点最少的时间。用队列维护。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct noi{
	int x,y,time;
};
char mq[5005][5005];//读入地图
int dis[5005][5005];//存时间
queue<noi>q;//
int sx,sy,ex,ey;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};//方向
int n,m;
void bfs(){
	noi now;
	now.x=sx;
	now.y=sy;
	now.time=0;
	q.push(now);
	while(!q.empty()){
		noi a=q.front();//取队首
		q.pop();
		for(int i=1;i<=4;i++){
			noi next;
			next.x=a.x+dx[i];
			next.y=a.y+dy[i];
			if(next.x==ex&&next.y==ey){//如果到达终点
				if(dis[ex][ey]>a.time)dis[ex][ey]=a.time;//存时间
			}
			if(next.x&&next.x<=n&&next.y&&next.y<=m&&mq[next.x][next.y]>='1'&&mq[next.x][next.y]<='9'){//在地图内且是数字
				next.time=a.time+(mq[next.x][next.y]-'0');
				if(dis[next.x][next.y]>next.time)dis[next.x][next.y]=next.time;
				else continue;//已经不是最好的方案，跳过
				now.x=next.x;
				now.y=next.y;					
				now.time=next.time;
				q.push(now);//入队
			}
		}
	}
}
int main(){
	while(cin>>m>>n&&n&&m){//读入n，m且两者大于0
		memset(dis,0x7f,sizeof(dis));
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>mq[i][j];
			if(mq[i][j]=='S')sx=i,sy=j;//存起点
			if(mq[i][j]=='D')ex=i,ey=j;//存终点
		}
		bfs();//广搜
		cout<<dis[ex][ey]<<endl;
		while(!q.empty())q.pop();//清空队列
	}
	return 0;
}
```
感谢观看！

---

## 作者：haotian1234 (赞：0)

## 题意暗示
- 就是从 $S$ 到 $D$ 走一条不经过 $X$ 的、耗时最少的路径。
## 题目分析
可以用宽搜（~~不是可以，就是事实~~），用 $f_i,_j$ 来记录，从 $S$ 到这个位置的最小时间即可。

在走到这个位置时，要经过判断：

1. 是否越界
1. 是否碰到障碍 $X$
1. 时间是否小于原本保存的最小时间
## 题目坑点
- $m$ 与 $n$ 的位置反了！
- 有多组数据，数组初始化
- 用字符输入

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,a[1010][1010],x,y,xx,yy,mi,t,w,h1[100100],h2[100100],f[1010][1010],u[1010][1010];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
char ch;
int main(){
	while(scanf("%d%d",&m,&n)&&n!=0&&m!=0){//m与n的位置反了！
		ch=getchar();
		memset(a,0,sizeof(a));
		memset(u,0,sizeof(u));
		memset(f,0,sizeof(f));
		memset(h1,0,sizeof(h1));
		memset(h2,0,sizeof(h2));//有多组数据，数组初始化
		for (i=1;i<=n;i++){
			for (j=1;j<=m;j++){
				ch=getchar();
				if (ch=='S') x=i,y=j;
				else if (ch=='D') xx=i,yy=j;
				else if (ch=='X') a[i][j]=-1; 
				else a[i][j]=ch-'0';//用字符输入
			} 
			ch=getchar();
		}
		memset(f,63,sizeof(f));mi=2e9;
		t=w=1;h1[1]=x;h2[1]=y;f[x][y]=0;u[x][y]=1;
		while (t<=w){
			int f1=h1[t],f2=h2[t];
			for (i=0;i<4;i++){
				int xy=f1+dx[i],yx=f2+dy[i];
				if (xy>=1&&xy<=n&&yx>=1&&yx<=m&&a[xy][yx]!=-1){//判断
					if (f[xy][yx]>f[f1][f2]+a[xy][yx]){
						f[xy][yx]=f[f1][f2]+a[xy][yx];
						if (!u[xy][yx]){
							h1[++w]=xy;h2[w]=yx;
							u[xy][yx]=1;
						}
					}
				}
			}
			t++;
			u[f1][f2]=0;
		}
		printf("%d\n",f[xx][yy]);
	} 
	return 0;
}
```


---

## 作者：Justinalx (赞：0)

# **1.前言**
如果说这道题很难，其实也没有。用宽搜就可以了。但让也有人用最短路什么的。我没什么不用？~~我懒得用~~。我觉得没必要。
# **2.题目大意**
给你一个矩阵。对于每个格子，如果这个格子为字符 x，就不能走，S 为起点，D 为终点。如果这个格子为数字，则为走这个格子所需代价。问你从起点到终点做少要多少代价。
# **3.思路**
用两个一维数组记录每次走过的点的位置 $t$ 和 $w$ ，然后用队列思想进行宽搜，从起点开始，向上，下，左，右四个方向判断，如果可以到达，就是原来所需代价加上这个格子所需代价最小，就是可以到达。**注意，刚开始宽搜时，除起点外所有点初始值为0。** 最后，到达终点时要再次判断，因为终点的标志是字符 D。
# **4.程序（仅供参考）**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,f[1100][1010],xx,dx[11000000]= {1,0,-1,0},dy[11000000]= {0,1,0,-1},yy,t1,w1,t2,w2,t,w,b[1100],c[1100];
char a[1100][1100];
int main() {
	scanf("%d%d",&m,&n);
	while (n!=0&&m!=0) {
		for (i=1; i<=n; i++){
			cin>>a[i];
			for (j=1; j<=m; j++) {
				if (a[i][j-1]=='S') t1=i,w1=j-1,a[i][j-1]='0';
				if (a[i][j-1]=='D') t2=i,w2=j-1,a[i][j-1]='0';
			}
		}
		t=w=1;
		b[w]=t1;
		c[w]=w1;
		memset(f,63,sizeof(f)); //除起点外所有格子定位最大。
		f[t1][w1]=0;
		while (t<=w) {
			for (i=0; i<4; i++) {
				xx=b[t]+dx[i];
				yy=c[t]+dy[i]; //判断上，下，左，右。
				if (a[xx][yy]!='X'&&a[xx][yy]!='S'&&xx>0&&yy>-1&&xx<=n&&yy<m)
					if (f[b[t]][c[t]]+a[b[t]][c[t]]-48<f[xx][yy]) {
						f[xx][yy]=f[b[t]][c[t]]+a[b[t]][c[t]]-48;
						w++;
						b[w]=xx;
						c[w]=yy;//记录可以到达的点。
					}
			}

			t++;
		}
		cout<<f[t2][w2]<<endl;
		scanf("%d%d",&m,&n);
	}

}
```


---

## 作者：_HMZ_ (赞：0)

## 题目大意：

给你一个 $n \times m$ 的矩阵，对于每个格子，如果是 `X` 则代表不能通过。

如果是一个数字，这个格子可以通过，通过所需要的时间就是这个数字。

现在要求从 `S` 到 `D` 最短要花多少时间。

## 解题思路：

本身是一道广搜的裸题，但是大家都用了二维数组来记录到某个格子需要的最短时间。

其实这里可以用优先队列求解，在队列中可能有很多个格子，从花费时间最少的开始扩展。

那么这样做为什么是对的呢？如果当前走的就是最短的路线，那么就一直走下去就行。

如果不是，那么在拓展的过程中时间会越来越多，逐渐被其他格子所取代。

接着其他格子就会开始扩展，找到一条更短的路线。

## AC代码：

```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct node
{
	int x, y, t;
	bool operator<(const node& A) const//优先队列的重构函数，如果不写，程序不知道按照哪个参数排序。
	{
		return t > A.t;
	}
};
int n, m, bx, by, dx[] = { 0,0,-1,1 }, dy[] = { 1,-1,0,0 };
char map[1005][1005];
bool vis[1005][1005];
int bfs()//广搜
{
	priority_queue<node> q;
	node tmp;
	tmp.x = bx, tmp.y = by, tmp.t = 0;
	q.push(tmp);
	vis[bx][by] = true;
	while(!q.empty())
	{
		int nx = q.top().x, ny = q.top().y, nt = q.top().t;
		q.pop();
		if (map[nx][ny] == 'D')//找到最短路线。
			return nt;
		for (int i = 0; i < 4; i++)
		{
			int tx = nx + dx[i], ty = ny + dy[i];
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && !vis[tx][ty] && map[tx][ty] != 'X')
			{
				vis[tx][ty] = true;
				int plus = 0;
				if (map[tx][ty] >= '0' && map[tx][ty] <= '9')
					plus = map[tx][ty] - '0';
				node tmp;
				tmp.x = tx, tmp.y = ty, tmp.t = nt + plus;
				q.push(tmp);
			}
		}
	}
}
int main()
{
	while (cin >> m >> n)
	{
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 'S')
					bx = i, by = j;
			}
		}
		memset(vis, false, sizeof(vis));
		cout << bfs() << endl;
	}
	return 0;
}
```


---

## 作者：chinaxjh (赞：0)

# 前言
此题是宽搜裸题，适合刚学bfs的新手练练手（新手也可以考虑保存一下当模板）
# 思路
暴力宽搜，开辟一个f数组表示到达i行j列的最短时间，然后用类似于SPFA的更新操作就可以无压力一发Ac，可以看我的代码注释辅助理解
# 时空
#### 时间 
约O(knm)级别(k为较小的常数)
#### 空间
O(nm)级别
# Ac Code (pascal)
```pascal
const
  dx:array[1..4] of longint=(0,0,-1,1);
  dy:array[1..4] of longint=(1,-1,0,0);//dx,dy为四个方向
var
  ch:char;
  n,m,i,j,xx,yy,l,r,zz,startx,starty,overx,overy:longint;
  a,f:array[0..500,0..500] of longint;
  x,y,z:array[0..1000000] of longint;
function pd(xxx,yyy:longint):boolean;
begin
  if (xxx>0) and (yyy>0) and (xxx<=n) and (yyy<=m) and (a[xxx,yyy]<>10) then exit(true)
  else exit(false);
end;//判断是否越界，是否有障碍，如果有就返回false（不能走），否则返回true（能走）

begin
  while true do
  begin

  readln(m,n);
  fillchar(a,sizeof(a),0);//初始化
  if (m=0) and (n=0) then break;//结束
  for i:=1 to n do
  begin
   for j:=1 to m do
   begin
     read(ch);
     if ch='S' then begin startx:=i; starty:=j; end
     else if ch='D' then begin overx:=i; overy:=j; end
     else if ch='X' then a[i,j]:=10//障碍标记为10
     else a[i,j]:=ord(ch)-48;//读入并处理起点，终点与障碍，时间
     f[i,j]:=maxlongint;//f数组初始值为一个极大值
   end;
   readln;
  end;
  x[1]:=startx; y[1]:=starty; z[1]:=0;  l:=1; r:=1;//从起点开始宽搜
  while l<=r do
  begin
    for i:=1 to 4 do//向四个方向探查
    begin
      xx:=dx[i]+x[l];
      yy:=dy[i]+y[l];
      if pd(xx,yy) then//如果可以走
      begin
        zz:=z[l]+a[xx,yy];//累加时间
        if zz<f[xx,yy] then//判断是否更优，更优就更新，否则就不动
        begin
          f[xx,yy]:=zz;//更新
          inc(r);
          x[r]:=xx;
          y[r]:=yy;
          z[r]:=zz;//更优值入队列进行宽搜
        end;
      end;
    end;
    inc(l);
  end;//宽搜主体框架
  writeln(f[overx,overy]);//输出答案
  end;
end.

```
# 后记
如果还无法理解，建议去询问老师或其他dalao了解一下bfs(我自认为我已经在代码里写的够明白了)，或者如果发现本题解有问题也可以私信我

---

