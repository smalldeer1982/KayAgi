# [ABC213E] Stronger Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc213/tasks/abc213_e

$ H $ 行 $ W $ 列の格子状の区画に区切られた街があります。上から $ i $ 行目、左から $ j $ 列目の区画は、$ S_{i,j} $ が `.` のとき道、`#` のとき塀です。

高橋君は自分の家から魚屋に買い物に行くことにしました。高橋君の家は街の左上隅の区画にあり、魚屋は街の右下隅の区画にあります。

高橋君は、自分がいる区画から上下左右に隣接する道の区画に移動することができます。街の外に出ることはできません。  
 塀の区画に移動することはできませんが、高橋君は非常に腕力が強いため、パンチを $ 1 $ 回繰り出すことで任意の $ 2\times\ 2 $ の区画内の塀を壊して道にすることができます。

高橋君が魚屋にたどり着くためには、最低何回パンチを繰り出せばよいか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,W\ \leq\ 500 $
- $ H,W $ は整数
- $ S_{i,j} $ は `.` または `#`
- $ S_{1,1} $ と $ S_{H,W} $ は `.`

### Sample Explanation 1

例えば、以下の `\*` で表す $ 2\times\ 2 $ の区画にある塀を破壊すると魚屋にたどり着くことができます。 ``` ..#.. #.\*\*# ##\*\*# #.#.# ..#.. ``` 破壊対象の $ 2\ \times\ 2 $ の区画の全てが塀である必要はありません。

### Sample Explanation 2

遠回りが必要ですが、塀を破壊することなく魚屋にたどり着くことができます。

## 样例 #1

### 输入

```
5 5
..#..
#.#.#
##.##
#.#.#
..#..```

### 输出

```
1```

## 样例 #2

### 输入

```
5 7
.......
######.
.......
.######
.......```

### 输出

```
0```

## 样例 #3

### 输入

```
8 8
.#######
########
########
########
########
########
########
#######.```

### 输出

```
5```

# 题解

## 作者：yangyang1000 (赞：5)

先来看不用拳头的情况，每次上下左右一个，比较好办。

而用拳头相当于就是可以走到任意一个被拳头砸开的位置。

就比如说，开始我们在红点：

![](https://cdn.luogu.com.cn/upload/image_hosting/zpb8wxcv.png)

而我们可以走到的地方是绿色的：

![](https://cdn.luogu.com.cn/upload/image_hosting/htr3c6uo.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/eu3jrb1z.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/n189v3ul.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/b3kedeup.png)

那么整体来说，所有可以用拳头走到的地方是：

![](https://cdn.luogu.com.cn/upload/image_hosting/h3v64cw5.png)

按照这种方式转移即可。

代码：

```cpp
#include<iostream>
#include<deque>
#include<cstring>
using namespace std;

int h,w;
string a[1005];
int dx[10] = {0,0,1,-1},dy[10] = {1,-1,0,0};
int dis[1005][1005];

struct node
{
	int x,y;
};

deque<node> q;

void bfs()
{
	q.push_front({1,1});
	dis[1][1] = 0;
	while(!q.empty())
	{
		int x = q.front().x,y = q.front().y;
		q.pop_front();
		
		for(int i=0;i<4;i++)
		{
			int xnew = x + dx[i],ynew = y + dy[i];
			if(xnew < 1 || xnew > h || ynew < 1 || ynew > w || a[xnew][ynew] == '#' || dis[xnew][ynew] <= dis[x][y]) continue;
			q.push_front({xnew,ynew});
			dis[xnew][ynew] = dis[x][y];
		}
		
		for(int xnew=x-2;xnew<=x+2;xnew++)
			for(int ynew=y-2;ynew<=y+2;ynew++)
			{
				if(abs(xnew - x) + abs(ynew - y) == 4) continue;
				if(xnew < 1 || xnew > h || ynew < 1 || ynew > w  || dis[xnew][ynew] <= dis[x][y]+1) continue;
				q.push_back({xnew,ynew});
				dis[xnew][ynew] = dis[x][y]+1;
			}
	}
}

int main()
{
	cin >> h >> w;
	for(int i = 1; i <= h; i++)
	{
		cin >> a[i];
		a[i] = " " + a[i];
	}

	memset(dis, 0x3f, sizeof(dis));
	bfs();
	
	printf("%d",dis[h][w]);
	return 0;
}
```


---

## 作者：xibaohe (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc213_e)

# 题目大意
高桥从自己家出发，到鱼市去买鱼。街道的地图被分成 $H$ 行 $W$ 列的格子，第 $i$ 行第 $j$ 列用字符 $s_{i,j}$ 表示。高桥的家在第 $1$ 行第 $1$ 列，鱼市在第 $H$ 行第 $W$ 列。高桥每次只可以移动到上下左右相邻的可通行的格子，不能移动到有墙壁的格子。但是高桥可以出拳破坏墙壁。
高桥要到达鱼市，最少需要出拳多少次?

# 题目思路
这道题与 AT_abc176_d[ABC176D] Wizard in Maze 相似，都要用**双端队列**广搜来解决。不熟悉双端队列的小朋友们可以先做下面两道题（AT_abc176_d 我也发了题解）：

[B3656 【模板】双端队列 1](https://www.luogu.com.cn/problem/B3656)

[AT_abc176_d Wizard in Maze](https://www.luogu.com.cn/problem/AT_abc176_d)


这道题需要用双端队列的原因是有两种优先级不同的移动方式：

 - 移动到上下左右相邻的道路格子。
 - 使用拳击技术。
 
由于需要求出拳击技术次数最少的方式，因此第一种移动优先级最高，可以插入到队列前段，后一种则需要插入道队列后端。

# 满分代码

```cpp
#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

int h, w, dis[1005][1005];
//dis[i][j]表示从(1,1)出发到达(i,j)所消耗拳击技术次数的最小值
char a[1005][1005];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

struct node
{ //从(1,1)出发到达(x,y)所消耗拳击技术次数的最小值t
	int x, y, t;
};

deque<node> q;

void bfs()
{
	q.push_front(node{1, 1, 0});
	dis[1][1] = 0;
	while(!q.empty())
	{
		int x = q.front().x, y = q.front().y, t = q.front().t;
		q.pop_front();
		//(x,y)普通移动能达到的子结点插入队首
		for(int i = 0; i <= 3; i++)
		{
			int x_new = x + dx[i], y_new = y + dy[i];
			if(x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
			if(a[x_new][y_new] == '#') continue;
			if(dis[x_new][y_new] <= dis[x][y]) continue;
			q.push_front(node{x_new, y_new, t});
			dis[x_new][y_new] = t;
		}
		
		//(x,y)拳击技术移动能达到的子结点插入队尾
		for(int x_new = x - 2; x_new <= x + 2; x_new++)
			for(int y_new = y - 2; y_new <= y + 2; y_new++)
			{
				if(x_new == x-2&& y_new == y-2) continue;
				if(x_new == x-2&& y_new == y+2) continue;
				if(x_new == x+2&& y_new == y-2) continue;
				if(x_new == x+2&& y_new == y+2) continue;
				if(x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
				//if(a[x_new][y_new] == '#') continue;
				if(dis[x_new][y_new] <= dis[x][y] + 1) continue;
				q.push_back(node{x_new, y_new, t + 1});
				dis[x_new][y_new] = t + 1;
			}
	}
}

int main()
{
	cin >> h >> w;
	for(int i = 1; i <= h; i++)
		for(int j = 1; j <= w; j++)
			cin >> a[i][j];
			
	memset(dis, 0x3f, sizeof(dis));
	bfs();
	
	if(dis[h][w] == 0x3f3f3f3f) cout << -1 << endl;
	else cout << dis[h][w] << endl;
	
	return 0;
}
```


---

## 作者：ruanwentao666 (赞：3)

# [ABC213E] Stronger Takahashi题解
~~这高桥也不行啊，一次只能摧毁这么点范围。~~

## 题意分析
高桥有两种移动方式，要么正常走，要么~~发起疯来~~走。

## 解决方案
我们可以将两种方案可以到达的点记录在队列中，要注意优先级的问题，最后再输出即可。

## 注意
Q：队列有要求吗？

A：双端队列，因为优先级高的要放在前面，反之同理

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[505][505];
int dis[505][505];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
struct node{
	int x,y;
};
void bfs(){
	deque<node>d;
	d.push_back({1,1});
	dis[1][1]=0;
	while(!d.empty()){
		node q=d[0];
		d.pop_front();
		for(int i=0;i<4;i++){
			int nx=q.x+dir[i][0],ny=q.y+dir[i][1];
			if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&a[nx][ny]=='.'&&dis[nx][ny]>dis[q.x][q.y]){
				d.push_front({nx,ny});
				dis[nx][ny]=dis[q.x][q.y];
			}
			for(int i=max(nx-1,1);i<=min(nx+1,n);i++){
				for(int j=max(ny-1,1);j<=min(ny+1,m);j++){
					if(dis[i][j]>dis[q.x][q.y]+1){
						d.push_back({i,j});
						dis[i][j]=dis[q.x][q.y]+1;
					}
				}
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	memset(dis,0x3f,sizeof(dis));
	bfs();
	cout<<dis[n][m];
	return 0;
}

```


---

## 作者：Miss_SGT (赞：3)

我们对于每个点，与他直接相连的可以通过点深度肯定与他一样。假如要爆破，可以到达四个方向 $2 \times 3$ 的区间。我们广搜，每次先把深度相同的记录，然后再搜一遍，四个方向 $2 \times 3$ 的格子只要没到过，那就是费用加   $1$。
```cpp
	while(!q1.empty()&&!flag){
		while(!q1.empty()){
			now=q1.front();
			q2.push(now);
			q1.pop();
			if(now.x==n&&now.y==m){
				flag=1;
				break;
			}
			for(int i=0;i<4;i++){
				xs=now.x+fx[i][0];
				ys=now.y+fx[i][1];
				if(yj(xs,ys)&&!vis[xs][ys]&&a[xs][ys]=='.'){
					vis[xs][ys]=1;
					q1.push((node){xs,ys,now.s});
				}
			}
		}
		while(!q2.empty()&&!flag){
			now=q2.front();
			q2.pop(); 
			if(now.x==n&&now.y==m){
				flag=1;
				break;
			}
			for(int i=0;i<4;i++){
				for(int j=now.x+f[i][0];j<=now.x+f[i][1];j++){
					for(int k=now.y+f[i][2];k<=now.y+f[i][3];k++){
						if(!vis[j][k]&&yj(j,k)){
							vis[j][k]=1;
							q1.push((node){j,k,now.s+1});				
						}
					}
				}
			}
		}	
	}
```

---

## 作者：无咕_ (赞：2)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）。

是否吸氧：否。

不压行代码长度：54。

------------

## 题目大意
题面： [<传送门>](https://www.luogu.com.cn/problem/AT_abc213_e)

题意：给出一张 $n\times m(2\le n,m\le 500)$ 的网格图，每个点可以为障碍 `#` 或道路 `.`。可以向上下左右四个方向以 $0$ 的代价从一条道路上移动到另一条道路上，也可以以 $1$ 的代价摧毁 $2\times 2$ 范围内的障碍（破坏范围需贴近当前位置）。求从 $(1,1)$ 到达 $(n,m)$ 的最小代价。保证两点均为 `.`。

~~术语理解：01bfs。~~

## Solution

解法思路源于大佬 @He_Ren 。

首先考虑，数据范围不支持我们使用 `dfs`，故选择 `bfs`。

我们一定是在必须打拳时才会打拳（走投无路时），所以我们会**先考虑移动，再考虑打拳**。

思考：打拳会对地图造成影响，该如何处理？

首先，肯定不能考虑实际修改地图。我们只需将要爆破的范围点全部带入，即不考虑范围内原有的障碍，即使会跳到障碍上。我们附图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/v4usv3i0.png)

### 关于优先级的考虑

之前说到，先考虑移动，再考虑打拳（原因是代价）。显然，在 `bfs` 的转移中（广度扩展），由第 $k$ 层拓展到第 $k+1$ 层后，在处理第 $k+1$ 层的内容时，我们同样需要先处理第 $k$ 层转移来的移动，再处理第 $k$ 层转移来的打拳。故需考虑优先级问题。

**01bfs！**

运用 `deque` 双端队列，我们将移动的步骤放到队列前端，优先考虑；打拳放到后端，其次考虑。

## AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<deque>
using namespace std;
const int MAXN=1009;
int dis[MAXN][MAXN];//到达每点的最短距离
int n,m;
int qx[5]={0,1,-1,0,0},qy[5]={0,0,0,1,-1};
int fx[19]={0,0,0, 0, 0,1,1, 1, 1,-1,-1,-1,-1,-2,-2,-2,2,2, 2};
int fy[19]={0,1,2,-1,-2,1,2,-1,-2, 1, 2,-1,-2, 1, 0,-1,1,0,-1};
bool mp[MAXN][MAXN]; 
deque<pair<int,int> >q;
pair<int,int>p;
bool check(int x,int y,int tx,int ty){
	if(tx<1||tx>n||ty<1||ty>m)return false;//如果越界或者有更优方案，不选 
	return true;
}void bfs(){
	memset(dis,0x3f,sizeof(dis));
	dis[1][1]=0;
	q.push_front(make_pair(1,1));
	while(!q.empty()){
		p=q.front();
		q.pop_front();
		int x=p.first,y=p.second;
		for(int k=1;k<=4;k++){//正常走（不打拳） 
			int tx=x+qx[k],ty=y+qy[k];
			if(check(x,y,tx,ty)&&dis[tx][ty]>dis[x][y]&&mp[tx][ty]==1){
				q.push_front(make_pair(tx,ty));//放到前面，优先处理 
				dis[tx][ty]=dis[x][y];//代价0 
			}
		}for(int k=1;k<=18;k++){
			int tx=x+fx[k],ty=y+fy[k];
			if(check(x,y,tx,ty)&&dis[tx][ty]>dis[x][y]+1){
				q.push_back(make_pair(tx,ty));//放到后面 
				dis[tx][ty]=dis[x][y]+1;//代价1 
			}
		}
	} 
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			if(x=='.')mp[i][j]=1;
			else mp[i][j]=0;
		}
	}bfs();
	cout<<dis[n][m];
	return 0;
}
```

AC 记录 [<传送门>](https://www.luogu.com.cn/record/109457713)

## 类似题型

[B3656 【模板】双端队列 1](https://www.luogu.com.cn/problem/B3656)

---

## 作者：KAxdd (赞：2)

## 思路

这道题说有一个人可以走四个方向如果遇到街区可以打碎 $2\times2$ 个格子,花费一格体力值，如果不是街区，就可以不花费任何体力往前走。从 $(1,1)$ 到 $(n,m)$ 最少花费体力值。

然后我们可以先求包括 $(1,1)$ 的连通图，然后我们可以在每一个是通道的格子都可以选择打碎街区，我们可以把它看作花费一格能量，传送到一个曼哈顿距离不超过 3 的任意一个点。然后继续求连通图，由于每个点都会走一遍，所以时间复杂度是 $O(n^2)$ 符合要求。

曼哈顿距离小于等于三的图如下

![](https://cdn.luogu.com.cn/upload/image_hosting/2hfa4tpz.png)

好了，根据这个定理，代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int s[505][505];
int f[505][505],vis[505][505];
string ss;
queue<int>qx,qy;
int xx[15]={0,0,1,-1,-2,-2,-1,-1,0,0,1,1};
int yy[15]={1,-1,0,0,-1,0,-2,1,-2,1,-1,0}; 
void dfs(int x,int y){//求连通块
	if(vis[x][y]==1)return;
	else qx.push(x),qy.push(y);
	vis[x][y]=1;
	for(int i=0;i<4;i++)
		if(s[x+xx[i]][y+yy[i]]==0&&x+xx[i]>0&&x+xx[i]<=n&&y+yy[i]>0&&y+yy[i]<=m)f[x+xx[i]][y+yy[i]]=min(f[x+xx[i]][y+yy[i]],f[x][y]),dfs(x+xx[i],y+yy[i]);
	return;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>ss;
		for(int j=1;j<=m;j++){
			f[i][j]=1e9;
			if(ss[j-1]=='#')s[i][j]=1;
		}
	}
	f[1][1]=0;
	dfs(1,1);
	while(!qx.empty()){
		int x=qx.front(),y=qy.front();
		qx.pop(),qy.pop();
		for(int i=4;i<=11;i++){//在规定范围内跳跃
			if(x+xx[i]>0&&x+xx[i]<=n&&y+yy[i]>0&&y+yy[i]<=m)f[x+xx[i]][y+yy[i]]=min(f[x+xx[i]][y+yy[i]],f[x][y]+1);
			if(x+xx[i]+1>0&&x+xx[i]+1<=n&&y+yy[i]>0&&y+yy[i]<=m)f[x+xx[i]+1][y+yy[i]]=min(f[x+xx[i]+1][y+yy[i]],f[x][y]+1);
			if(x+xx[i]>0&&x+xx[i]<=n&&y+yy[i]+1>0&&y+yy[i]+1<=m)f[x+xx[i]][y+yy[i]+1]=min(f[x+xx[i]][y+yy[i]+1],f[x][y]+1);
			if(x+xx[i]+1>0&&x+xx[i]+1<=n&&y+yy[i]+1>0&&y+yy[i]+1<=m)f[x+xx[i]+1][y+yy[i]+1]=min(f[x+xx[i]+1][y+yy[i]+1],f[x][y]+1);
			if(x+xx[i]>0&&x+xx[i]<=n&&y+yy[i]>0&&y+yy[i]<=m)dfs(x+xx[i],y+yy[i]);
			if(x+xx[i]+1>0&&x+xx[i]+1<=n&&y+yy[i]>0&&y+yy[i]<=m)dfs(x+xx[i]+1,y+yy[i]);
			if(x+xx[i]>0&&x+xx[i]<=n&&y+yy[i]+1>0&&y+yy[i]+1<=m)dfs(x+xx[i],y+yy[i]+1);
			if(x+xx[i]+1>0&&x+xx[i]+1<=n&&y+yy[i]+1>0&&y+yy[i]+1<=m)dfs(x+xx[i]+1,y+yy[i]+1);
		}
	}
	cout<<f[n][m]<<" ";//输出到鱼店就可以了
	return 0;
}

---

## 作者：亡䒤兲新淏 (赞：1)

# ABC213E的题解

## 题目分析
首先，这道题的问题是从家到鱼市摧毁障碍物的最少次数。我们很容易想到用广搜的方法来做。因为 $2 \le H,W \le 500$，数据很小，理论上我们可以对于每个障碍物都进行一次爆破。

虽然爆破的范围是 $2 \times 3$，方向不一定，但是我们可以将爆破视作以爆破中心 $3 \times 3$ 范围进行爆破。

最后使用优先队列，以爆破次数进行排序，直到到达鱼市。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pipi;
#define F first
#define S second
inline int read()
{
	int x=0;
	bool f=0;
	char ch=getchar();
	while('0'>ch||'9'<ch)
	{
		if(ch=='-')f=1;
		ch=getchar();
	}
	while('0'<=ch&&'9'>=ch)
	{
		x=((x<<3)+(x<<1))+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
priority_queue<pipi,vector<pipi>,greater<pipi> >p;
bool mp[505][505],gone[505][505];
const int go[8][2]= {{1,0},{0,-1},{0,1},{-1,0},{1,1},{1,-1},{-1,-1},{-1,1}};
int main()
{
	int h=read(),w=read();
	for(int i=1; i<=h; ++i)
		for(int j=1; j<=w; ++j)
		{
			char c;
			cin>>c;
			mp[i][j]=(c=='.'?0:1);
		}
	p.push(pipi(0,pii(1,1)));
	while(!p.empty())
	{
		int b=p.top().F,x=p.top().S.F,y=p.top().S.S;
		p.pop();
		if(gone[x][y]||!x||!y||x>h||y>w)continue;
		gone[x][y]=1;
		for(int i=0; i<4; ++i)
		{
			int g=x+go[i][0],f=y+go[i][1];
			if(g==h&&f==w)
			{
				printf("%d",b);
				return 0;
			}
			if(mp[g][f])
			{
				for(int j=0; j<8; ++j)
					p.push(pipi(b+1,pii(g+go[j][0],f+go[j][1])));
				p.push(pipi(b+1,pii(g,f)));
			}
			else p.push(pipi(b,pii(g,f)));
		}
	}
	return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

## 前言
为什么要用广搜呢？~~用“BFS 判联通块 + 对每个联通块加边 + Dijkstra / BFS 跑最短路”它不好吗？~~
## 基本思路
首先，我们能发现，对于任意一个只包含“`.`”的连通块，无论怎么走，只要还在当前连通块中，就一点也不会产生消耗。

所以，我们可以在一开始，就用 BFS 标记每个连通块，为后面建边、跑最短路做准备。（当然，我认为这也可以理解成一次缩点，即将几个完全等价的点压缩为一个点）

接下来，就到了本题的**重中之重——连边**！

此题的**连边**挺特殊的，由于一次可以使 $2\times2$ 的区域变为“`.`”，所以我们先**枚举**这个小矩阵的位置。在每个位置，它所能产生的**边**见下图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/m4xsigik.png)
$$\text{图 1}$$

---
## 细节
但是，这样做时，下面的数据输出的结果就有问题：

- 输入：
```
5 5
.####
#####
#####
#####
####.
```
- 输出：
```
3
```
按**上面思路**写的代码，**输出结果**为 $2$。这是为什么呢？

这里的问题就出在**建边**以及**连通块**上。

- **连通块**：由题意，只有相邻的“`.`”才可以缩点，而“`#`”虽然不可以缩点，但其应该以自己为一个连通块，参与到连边之中（这也是一个坑点）。

- **建边**：在刚刚的数据中，我们输出**调试信息**（即地图上每个点的**最小花费**），就会发现，在**错误的跳法**中，每次都相当于从“$\text{图 1}$”中的 $1/2/3/6/7/10/11/12$ 这 $8$ 点之一（且为“`#`”），跳到其余点。我们应该阻止这种非法行为。也就是说，我们不能让小矩形外未变为“`.`”的点往外连边。

  具体实现为：
  - 若当前点为“`.`”：依旧枚举任一点连边。
  - 若当前点为“`#`”：只有在当前枚举的矩形内部，才能向外连边。
  
## 最后
既然最重要的两点都说完了，只需要我们写出 BFS / Dijksrta 的最短路模板，就到了喜闻乐见的 AC 时间啦。

参考代码，仅供参考（doge）：
```cpp
#include<stdio.h>
#include<memory.h>
#include<queue>
#include<set>
#define maxn 500
using namespace std;
struct edge
{
	int to, next;
	friend bool operator < (edge a, edge b) {return a.next > b.next;}
};
struct node
{
	int x, y;
};
edge e[maxn * maxn * 150 + 5];
priority_queue<edge> q;
int n, m, cnt, idx, last[maxn * maxn + 5], dis[maxn * maxn + 5], vis[maxn + 5][maxn + 5];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
char mp[maxn + 5][maxn + 5];
bool flag[maxn * maxn + 5];
void add(int st, int to)
{
	e[++cnt] = {to, last[st]};
	last[st] = cnt;
}
void bfs(int x, int y)//判连通块
{
	queue<node> que;
	que.push({x, y});
	vis[x][y] = ++idx;
	while(!que.empty())
	{
		node t = que.front();
		que.pop();
		for(int i = 0; i < 4; i++)
		{
			int nx = t.x + dx[i], ny = t.y + dy[i];
			if(nx && ny && nx <= n && ny <= m && mp[nx][ny] != '#' && !vis[nx][ny])
			{
				vis[nx][ny] = idx;
				que.push({nx, ny});
			}
		}
	}
}
void dijkstra(int st)//最短路，由于边权只会为 1，所以用 BFS 也行
{
	memset(dis, 63, sizeof dis);
	q.push({st, 0});
	dis[st] = 0;
	while(!q.empty())
	{
		int t = q.top().to;
		q.pop();
		if(t == vis[n][m]) return;
		for(int i = last[t]; i != -1; i = e[i].next)
		{
			if(dis[e[i].to] > dis[t] + 1)
			{
				dis[e[i].to] = dis[t] + 1;
				q.push({e[i].to, dis[t] + 1});
			}
		}
	}
}
bool in(int id, int x, int y)//判断连通块 id 是否可以连至以 (x, y) 为左上角的 2 × 2 小矩阵之中
{
	for(int i = x; i <= x + 1; i++)
	{
		for(int j = y; j <= y + 1; j++)
		{
			if(id == vis[i][j]) return true;
		}
	}
	return false;
}
int	main()
{
	memset(last, -1, sizeof last);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	for(int i = 1; i <= n; i++)//标记连通块
	{
		for(int j = 1; j <= m; j++)
		{
			if(vis[i][j]) continue;
			if(mp[i][j] == '#')
			{
				vis[i][j] = ++idx;
				flag[vis[i][j]] = true;
			}
			else bfs(i, j);
		}
	}
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j < m; j++)
		{
			set<int> st;//没什么用，就只是用于去重
			for(int hang = i; hang <= i + 1; hang++)//枚举每个能拓展的格子
			{
				for(int lie = j; lie <= j + 1; lie++)
				{
					for(int k = 0; k < 4; k++)
					{
						int nx = hang + dx[k], ny = lie + dy[k];
						if(nx && ny && nx <= n && ny <= m) st.insert(vis[nx][ny]);
					}
				}
			}
			for(int ii : st)
			{
				for(int jj : st)
				{
					if(ii != jj && (!flag[ii] || in(ii, i, j))) add(ii, jj);//连边
				}
			}
		}
	}
	dijkstra(vis[1][1]);
	printf("%d\n", dis[vis[n][m]]);//完结撒花
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/121722551)

---

## 作者：Demons_Killer (赞：0)

# 思路:
本题的高桥可以打碎一个 $2 \times 2$ 区间的障碍物，但既然要求最小花费的体力，是能不打则不打，可以去 BFS 整个网格图。注意的是这里需要用到双端队列，如果是打碎障碍后到达，就加到队列后面， 否则就要优先遍历到，就加在队列前面。

### 打碎障碍后能走到的点：

![](https://cdn.luogu.com.cn/upload/image_hosting/efjisu34.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

最后输出到右下角的最小花费就行了。

# Code：

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010;
struct node{
	int x,y;
};
int dist[N][N];//记录到地图上每个点的最小花费
char g[N][N];
int h,w;
int dx1[4][2]={{0,-1},{-1,0},{1,0},{0,1}};
int dx2[25][2]={{-1,-1},{1,1},{-1,1},{1,-1},{2,-1},{2,1},{1,2},{1,-2},{-2,1},{-2,-1},{-1,-2},{-1,2},{2,0},{0,2},{-2,0},{0,-2}};
void bfs(){
	deque<node> q;//双端队列
	dist[1][1]=0;
	q.push_front({1,1});
	while(!q.empty()){
		node a=q.front();
		q.pop_front();
		for(int i=0;i<4;i++){
			int tx=a.x+dx1[i][0];
			int ty=a.y+dx1[i][1];
			if(dist[tx][ty]>dist[a.x][a.y]&&tx>=1&&ty<=w&&tx<=h&&ty>=1&&g[tx][ty]=='.'){
				dist[tx][ty]=dist[a.x][a.y];
				q.push_front({tx,ty});
			}
		}
		for(int i=0;i<16;i++){
			int tx=a.x+dx2[i][0];
			int ty=a.y+dx2[i][1];
			if(dist[tx][ty]>dist[a.x][a.y]+1&&tx>=1&&ty<=w&&tx<=h&&ty>=1){
				dist[tx][ty]=dist[a.x][a.y]+1;
				q.push_back({tx,ty});
			}
		}
	}
}
signed main(){
	memset(dist,0x3f3f,sizeof(dist));
	cin>>h>>w;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)cin>>g[i][j];
	bfs();
	if(dist[h][w]==0x3f3f3f3f) cout<<-1;
	else cout<<dist[h][w];
	return 0;
}

```

---

