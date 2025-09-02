# [ABC170F] Pond Skater

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc170/tasks/abc170_f

アメンボのすぬけ君は南北 $ H $ マス東西 $ W $ マスの長方形の形をしたグリッド状の池に住んでいます。北から $ i $ 番目、西から $ j $ 番目のマスをマス $ (i,j) $ とします。

いくつかのマスには蓮の葉が浮かんでおり、すぬけ君はそれらのマスには入ることができません。 $ c_{ij} $ が `@` のときマス $ (i,j) $ に蓮の葉が浮かんでいること、`.`のときそうでないことを表します。

すぬけ君は一回水をかくことで東西南北のいずれかの方向に $ 1 $ マス以上 $ K $ マス以下移動することができます。 移動の途中に蓮の葉のあるマスがあってはいけません。また、蓮の葉のあるマスや池の外に移動することもできません。

すぬけ君がマス $ (x_1,y_1) $ から $ (x_2,y_2) $ まで移動するのに最小で何回水をかく必要があるか求めてください。 $ (x_1,y_1) $ から $ (x_2,y_2) $ まで移動することができない場合、そのことを指摘してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W,K\ \leq\ 10^6 $
- $ H\ \times\ W\ \leq\ 10^6 $
- $ 1\ \leq\ x_1,x_2\ \leq\ H $
- $ 1\ \leq\ y_1,y_2\ \leq\ W $
- $ x_1\ \neq\ x_2 $ または $ y_1\ \neq\ y_2 $
- $ c_{i,j} $ は `.` または `@`
- $ c_{x_1,y_1}\ = $ `.`
- $ c_{x_2,y_2}\ = $ `.`
- 入力される数はすべて整数である。

### Sample Explanation 1

はじめ、すぬけ君はマス $ (3,2) $ にいます。 以下のように $ 5 $ 回水をかくことでマス $ (3,4) $ まで移動することができます。 - マス $ (3,2) $ から西に $ 1 $ マス進み、マス $ (3,1) $ に移動する。 - マス $ (3,1) $ から北に $ 2 $ マス進み、マス $ (1,1) $ に移動する。 - マス $ (1,1) $ から東に $ 2 $ マス進み、マス $ (1,3) $ に移動する。 - マス $ (1,3) $ から東に $ 1 $ マス進み、マス $ (1,4) $ に移動する。 - マス $ (1,4) $ から南に $ 2 $ マス進み、マス $ (3,4) $ に移動する。

## 样例 #1

### 输入

```
3 5 2
3 2 3 4
.....
.@..@
..@..```

### 输出

```
5```

## 样例 #2

### 输入

```
1 6 4
1 1 1 6
......```

### 输出

```
2```

## 样例 #3

### 输入

```
3 3 1
2 1 2 3
.@.
.@.
.@.```

### 输出

```
-1```

# 题解

## 作者：Xiao_zhiwen (赞：7)

## 题意分析
在 $H\times W$ 的矩形迷宫中，指定每次的行动距离范围，求从起点到终点的最少移动次数。

- $ 1\leq H,W,K\leq 10^6 $
- $ H\times W\leq 10^6 $

从数据范围可知：直接二维存矩阵会爆空间，所以要将为储存，用一个字符数组（char[]）即可。
## 思路分析
这道题其实是一道广搜 (BFS) + 优化。
如果直接进行广搜的话时间复杂度是$O(n^2\times m^2)$，显而易见速度会很慢。
#### 优化方法：
从当前所在位置向上下左右走，如果路途中遇到了一样或更近的点就可以结束，后面的位置显然可以通过这个点更快地走过去。时间复杂度为 $O(n\times m)$。
#### 存储实现
```cpp
int H,W,k,x[3],y[3],a[N];//a[place(x,y)] 表示到(x,y) 的最少步数
//因为x1,y1为某函数变量，所以不能使用
int dx[]={1,0,0,-1},dy[]={0,-1,1,0};//上下左右四个方向
char g[N];//储存地图
struct node{
  int x,y;
};
queue<node> q;
int place(int x,int y){
  return (x-1)*W+y;//将二维下标转换为一维
}
```
### 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N=1e6+10;
int H,W,k,x[3],y[3],a[N];
int dx[]={1,0,0,-1},dy[]={0,-1,1,0};
char g[N];
struct node{int x,y;};
queue<node> q;
int place(int x,int y){return (x-1)*W+y;}
void bfs(){
	node t;
	t.x=x[1],t.y=y[1];
	q.push(t);//将起点存下
	while(!q.empty()){//判读队列是否为空
		node u=q.front();q.pop();
		if(u.x==x[2] && u.y==y[2])//已经到了终点，提前退出
			return ;
		for(int i=0;i<=3;i++){//上下左右四个方向
			for(int j=1;j<=k;j++){//1~k步都遍历一遍
				int dxx=u.x+j*dx[i],dyy=u.y+j*dy[i];//下一步的位置
				if(dxx<1 || dxx>H || dyy<1 || dyy>W)//位置出界了，则提前结束
					break;
				if(g[place(dxx,dyy)]=='@')//前路不通，直接退出
					break;
				if(a[place(dxx,dyy)]!=0){//(dxx,dyy) 已经走过了
					if(a[place(dxx,dyy)]<=a[place(u.x,u.y)]) //从(dxx,dyy)出发比(u.x,u.y)更快，则退出
						break;
					continue;//否则下一步
				}
				a[place(dxx,dyy)]=a[place(u.x,u.y)]+1;//记录起点到(dxx,dyy)最少移动次数
				t.x=dxx,t.y=dyy;
				q.push(t);//将(dxx,dyy)存下来
			}
		}
	}
}
int main(){
    //因为使用的是 cin 和 cout 进行输入输出，所以需要关闭流同步提升速度
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    //读入数据
    cin>>H>>W>>k;
    cin>>x[1]>>y[1]>>x[2]>>y[2];
	for(int i=1;i<=H*W;i++)
		cin>>g[i];
	a[place(x[1],y[1])]=0;//从起点出发
	bfs();
	cout<<(a[place(x[2],y[2])]==0?-1:a[place(x[2],y[2])])<<endl;//如果没有走过则输出-1，否则输出最少步数
	return 0;
}
```

---

## 作者：CarroT1212 (赞：6)

### 题目大意

有一个 $H$ 行 $W$ 列，仅含 `.` `@` 的字符矩阵，你现在位于 $(x_1,y_1)$。每一步你可以向上下左右四个方向走 $1\sim K$ 格，你无法通过矩阵中为 `@` 的格子。问你最少需要多少步才能到达 $(x_2,y_2)$。

数据范围：$1 \le H,W,K \le 10^6$，$H \times W \le 10^6$，$(x_1,y_1),(x_2,y_2)$ 都不为 `@`。

------------

### 解法分析

考虑 bfs。

不考虑效率的话这题的普通 bfs 做法非常好写，注意一下 vector 的使用即可。

造成普通做法 TLE 的原因，显然是在枚举每个格子可以转移到的位置时花费了大量的时间，而这些位置大多都是重复的，所以考虑进行一些优化。

这个优化也非常简单。普通做法的转移写法一般是每找到一个格子 $(i,j)$，就先枚举转移的方向，再枚举转移的步数，枚举步数时如果遇到边界或障碍物就退出。这时，如果你枚到了一个你之前已经扫过的格子 $(a,b)$，而且从 $(x_1,y_1)$ 到 $(a,b)$ 的距离不超过到 $(i,j)$ 的距离，那么，这个方向上剩下没有枚举完的格子，肯定是不经过 $(i,j)$ 而从 $(a,b)$ 出发抵达更优。因为这样你可以到达更多的格子，而且步数也不可能比从 $(i,j)$ 出发更多。所以这种时候，你可以直接退出这个方向上的搜索，剩下那些格子等着搜到 $(a,b)$ 再推进队列即可。

容易发现优化之后时间复杂度大约也就是 $O(HW)$ 级别的，因为每个点最多会被上下左右四个方向上最早被搜到而且最近的点扫到一次，如果不是的话根本就碰不到，早就被前面更优的点拦下来了。

（话说这题的官解居然是 Dijkstra）

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=1e6+7;
int h,w,k,xa,ya,xb,yb,xx[4]={-1,0,1,0},yy[4]={0,-1,0,1};
char inp[N];
vector <int> vis[N]; // vis[i][j] 表示从 (x1,y1) 到 (i,j) 的最小步数
vector <char> mp[N];
void bfs() {
	queue <pii > q;
	q.push({xa,ya}),vis[xa][ya]=1; // 这里为了少打几个字给步数加了个 1，输出的时候减掉即可
	while (!q.empty()) {
		int x=q.front().first,y=q.front().second; q.pop();
		for (int i=0;i<4;i++) for (int j=1;j<=k;j++) {
			int nx=x+xx[i]*j,ny=y+yy[i]*j;
			if (nx<1||nx>h||ny<1||ny>w||mp[nx][ny]=='@') break;
			if (vis[nx][ny]&&vis[nx][ny]<=vis[x][y]) break; // 优化
			if (!vis[nx][ny]) vis[nx][ny]=vis[x][y]+1,q.push({nx,ny});
		}
	}
}
int main() {
	scanf("%d%d%d%d%d%d%d",&h,&w,&k,&xa,&ya,&xb,&yb);
	for (int i=1;i<=h;i++) {
		scanf("%s",inp+1);
		mp[i].pb('~'),vis[i].pb(0);
		for (int j=1;j<=w;j++) mp[i].pb(inp[j]),vis[i].pb(0);
	}
	bfs();
	printf("%d",vis[xb][yb]-1);
	return 0;
}
```

---

## 作者：CommandSR (赞：5)

## BFS + 优化

### 数据存储
$1 ≤ H,W,K ≤ 10^6 
$ ，普通数组空间存不下。

考虑用 vector。
```cpp
vector <char> a[1000010];
vector <int> dis[1000010];
```
地图数组和记录数组都需要 vector ，输入时都要 push_back。

---

### 每次可以走 1~k 步
在 BFS 模板枚举方向的同时，加上一层循环。

注意一旦**碰到障碍（即不能跳过石头），移出边界，或被标记过**，若当前在走第 $j$ 步，则后面的 $[j+1, k]$  均不可走。

```cpp
for (int i = 0; i < 4; i++)
{
  for (int j = 1; j <= k; j++)
  {
    v.x = u.x + dx[i] * j;
    v.y = u.y + dy[i] * j;
    if (v.x < 0 || v.x >= n || v.y < 0 || v.y >= m) break ;
    if (dis[v.x][v.y] && dis[v.x][v.y] <= dis[u.x][u.y]) break ;
    if (dis[v.x][v.y]) continue ;
    if (a[v.x][v.y] == '@') break ;
    q.push(v);
    dis[v.x][v.y] = dis[u.x][u.y] + 1;
  }
}
```

---

### 剪枝

用上述方法通过将超时。

**注意到本来只需走 $k$ 步，但是如果路途中间遇到了一样近或更近的点就可以停止了，显然，后面那些没走的位置可以通过这个点走过去而不会更劣。**

```cpp
if (dis[v.x][v.y] && dis[v.x][v.y] <= dis[u.x][u.y]) break ;
```
--- 

#### 其余细节见注释
### AC CODE



```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, sx, sy, tx, ty;
vector <char> a[1000010];
vector <int> dis[1000010];
struct node
{
	int x, y;
};
queue <node> q;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
void bfs()
{
	q.push((node){sx, sy});
	dis[sx][sy] = 1;
	while (!q.empty())
	{
		node u = q.front(), v;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j <= k; j++) // 可以走1~k步
			{
				v.x = u.x + dx[i] * j;
				v.y = u.y + dy[i] * j;
				if (v.x < 0 || v.x >= n || v.y < 0 || v.y >= m) break ;
				if (dis[v.x][v.y] && dis[v.x][v.y] <= dis[u.x][u.y]) break ; // 剪枝
				if (dis[v.x][v.y]) continue ;
				if (a[v.x][v.y] == '@') break ;
				// 注意上文提到的直接 break 的情况
				q.push(v);
				dis[v.x][v.y] = dis[u.x][u.y] + 1; // 步数 + 1
			}
		}
	}
	if (dis[tx][ty]) cout << dis[tx][ty] - 1; // 最终答案
	else cout << -1;
}
int main() 
{
//	freopen("b.in", "r", stdin);
//	freopen("b.out", "w", stdout);	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	cin >> sx >> sy >> tx >> ty;
	// 由于vector存储，下标从0开始，故读入的起点和终点坐标数据要-1
	sx--, sy--, tx--, ty--;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char ch;
			cin >> ch;
			a[i].push_back(ch);
			dis[i].push_back(0);
			// vector 存储，注意dis数组也要push_back()，否则后面无法修改访问dis数组元素
		}
	}
	bfs();
	return 0;
}
```

---

## 作者：如履薄冰 (赞：4)

# 题意
给你一个 $h$ 行 $w$ 列的地图 mp，如果 $mp_{ij}$ 是障碍物，即 $mp_{ij}$ 是 ```@```，我们就不能通过 $mp_{ij}$ ，反之可以通过。你现在在 $mp_{x1y1}$，要走到 $mp_{x2y2}$，问至少需要几个步骤。在一个步骤内，你可以上下左右移动 $1$ 至 $k$ 个格子。
# 算法
广度优先搜索和优化。
# 解法
## 输入存放
我们可以用一个数据结构存放地图，由于$1 \le h,w \le 10^6$，所以数组存不下。因此，我们考虑使用 vector 或 map。
## 广度优先搜索实现
### 初始化
我们可以用一个队列 q 维护待扩展的状态。我们将 $(x1,y1)$ 入队。再定义一个名为 vis 的 vector，用来存放走每个点所需要的步骤。将 $vis_{x1y1}$ 设为 $1$。
为什么是 $1$ 而不是 $0$ 呢？因为 vis 不仅起到存放步骤的作用，还能用来判定一个点是否走过，如果你把 $vis_{x1y1}$ 设为 $0$，那么程序就会断定位置 $(x1,y1)$ 没有被走过。由于 $vis_{x1y1}$ 是 $1$,我们在输出答案 $vis_{x2y2}$ 时要减去一。
### 广度优先搜索主体
如何广度优先搜索我在这里就不陈述了，几乎就是个板子。我来说一下重要的部分。
#### 扩展
题目的特殊性质在于你一次可以走很多步，我们可以用一个循环枚举走 $1$ 步至走 $k$ 步的情况，一一扩展。
#### 优化
如果你现在想访问的点已经被访问过了，且走到此点的步数比你现在走到此点所需要的步数要少，就直接 break 掉。这个步骤被称为剪枝。
# 代码
我觉得我已经讲得够详细了，因此此处省略。

---

## 作者：如履薄冰 (赞：2)

# 题意
给你一个 $h$ 行 $w$ 列的地图 mp，如果 $mp_{i,j}$ 是障碍物，即 $mp_{i,j}$ 是 ```@```，我们就不能通过 $mp_{i,j}$ ，反之可以通过。你现在在 $mp_{x1,y1}$，要走到 $mp_{x2,y2}$，问至少需要几个步骤。在一个步骤内，你可以上下左右移动 $1$ 至 $k$ 个格子。
# 算法
广度优先搜索和优化。
# 解法
## 输入存放
我们可以用一个数据结构存放地图，由于$1 \le h,w \le 10^6$，所以数组存不下。因此，我们考虑使用 vector 或 map。
## 广度优先搜索实现
### 初始化
我们可以用一个队列 q 维护待扩展的状态。我们将 $(x1,y1)$ 入队。再定义一个名为 vis 的 vector，用来存放走每个点所需要的步骤。将 $vis_{x1,y1}$ 设为 $1$。
为什么是 $1$ 而不是 $0$ 呢？因为 vis 不仅起到存放步骤的作用，还能用来判定一个点是否走过，如果你把 $vis_{x1,y1}$ 设为 $0$，那么程序就会断定位置 $(x1,y1)$ 没有被走过。由于 $vis_{x1,y1}$ 是 $1$,我们在输出答案 $vis_{x2,y2}$ 时要减去一。
### 广度优先搜索主体
如何广度优先搜索我在这里就不陈述了，几乎就是个板子。我来说一下重要的部分。
#### 扩展
题目的特殊性质在于你一次可以走很多步，我们可以用一个循环枚举走 $1$ 步至走 $k$ 步的情况，一一扩展。
#### 优化
如果你现在想访问的点已经被访问过了，且走到此点的步数比你现在走到此点所需要的步数要少，就直接 break 掉。这个步骤被称为剪枝。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long h,w,k,xs,ys,xf,yf,dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char iin;
vector<char> mp[1100000];
vector<long long> vis[1100000];
struct node{
	long long x,y;
};
void bfs(){
	queue<node> q;
	q.push({xs,ys});
	vis[xs][ys]=1;
	while(!q.empty()){
		node cur=q.front();
		q.pop();
		for(int i=0;i<=3;i++){
			for(int j=1;j<=k;j++){
				node nxt;
				nxt.x=cur.x+dx[i]*j;
				nxt.y=cur.y+dy[i]*j;
				if(nxt.x<1||nxt.x>h||nxt.y<1||nxt.y>w||mp[nxt.x][nxt.y]!='.'){
					break;
				}
				if(vis[nxt.x][nxt.y]&&vis[cur.x][cur.y]>=vis[nxt.x][nxt.y]){
					break;
				}
				if(vis[nxt.x][nxt.y]){
					continue;
				}
				vis[nxt.x][nxt.y]=1;
				vis[nxt.x][nxt.y]=vis[cur.x][cur.y]+1;
				q.push({nxt.x,nxt.y});
			}
		}
	}
	if(vis[xf][yf]){
		cout<<vis[xf][yf]-1;
	}else{
		cout<<-1;
	}
}
int main(){
    ios::sync_with_stdio(false);
    cin>>h>>w>>k>>xs>>ys>>xf>>yf;
    for(int i=1;i<=h;i++){
    	mp[i].push_back('!');
    	vis[i].push_back(0);
    	for(int j=1;j<=w;j++){
    		cin>>iin;
    		mp[i].push_back(iin);
    		vis[i].push_back(0);
		}
	}
	bfs();
    return 0;
}
```

---

## 作者：guoxinda (赞：1)

## 题目大意
- すぬけ君每次划水可以向东、南、西、北方向移动 $1$ 至 $K$ 格。
- 路径上的所有格子都不能有莲叶（```@```），否则不能通过。
- 不能移动到池塘外部（超出边界）。\
すぬけ君从起点 $(x_1,y_1)$ 需要移动到目标 $(x_2,y_2)$，求最少需要多少次划水。
## 思路
考虑用 BFS（广度优先搜索）做此题。\
由于 $1\ \leq\ H,W,K\ \leq\ 10^6$，但没有说明 $w,k$ 的具体大小，所以不能用二维数组存，会爆空间。要改为用一维数组存。\
如何表示到下一行呢？只需要加上一个 $w$ 即可。\
但是普通的 BFS 会超时。\
容易发现现在队头的坐标 $(x,y)$ 往某个方向走到一定程度时，当前坐标 $(x_2,y_2)$ 需要走的步数小于现在队头的步数 $+1$，此时就可以停止往这个方向的搜索，因为从 $(x_2,y_2)$ 已经比从 $(x,y)$ 更优了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct stu{
	int f,s;
};
int ax,h,w,k,x1,yy1/*y1关键字，避坑！！！*/,x2,y2,xx,zz,a[1000010],dx[5]/*一维数组，用来计算一维坐标*/,gx[5]={-1,1,0,0},gy[5]={0,0,-1,1}/*gx,gy表示实际改变的x,y坐标增加了多少*/,ans=1e9;//gy!!!
int vis[1000010];//现在走到一维数组的某个位置最少需要多少步 
char c;
queue<int>x,z;//一维坐标和步数 
queue<stu>y;//表示实际坐标（可以不用，但更麻烦，会卡常的可以试一下） 
stu yy;
void bfs(){
	while(!x.empty()){
		xx=x.front(),yy=y.front(),zz=z.front();x.pop(),y.pop(),z.pop();
		if(xx==(x2-1)*w+y2){
			ans=min(ans,zz);
			return ;
		}
		for(int i=0;i<4;i++){
			for(int j=1;j<=k;j++){
				ax=xx+dx[i]*j;//现在的一维坐标 
				if(!(yy.f+gx[i]*j>=1&&yy.f+gx[i]*j<=h&&yy.s+gy[i]*j>=1&&yy.s+gy[i]*j<=w))break;
				if(vis[ax]==zz+1)continue;
				if(!(vis[ax]>zz+1&&a[ax]))break;
				//可以通过 
				vis[ax]=zz+1;
				x.push(ax),y.push({yy.f+gx[i]*j,yy.s+gy[i]*j}),z.push(zz+1);
			}
		}	
	}
}
int main(){
	cin>>h>>w>>k>>x1>>yy1>>x2>>y2;
	dx[0]=-w;//上 
	dx[1]=w;//下
	dx[2]=-1;//左
	dx[3]=1;//右 
	for(int i=1;i<=h*w;i++)vis[i]=1e9;//初始化 
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>c;
			if(c=='.')a[(i-1)*w+j]=1;
			else a[(i-1)*w+j]=0;
		}
	}
	x.push((x1-1)*w+yy1);//一维坐标 
	y.push({x1,yy1});//二维坐标 
	z.push(0);
	vis[(x1-1)*w+yy1]=0;
	bfs();
	if(ans==1e9)cout<<-1;
	else cout<<ans;
	cout<<endl;
	return 0;
}
```

---

## 作者：Swordmaker (赞：1)

# AT_abc170_f [ABC170F] Pond Skater

# 前置知识

本题需要用到 vector 这种数据结构，以及需要学习**广度优先搜索**算法。

# 思路分析

看到这道题，应该能一眼看出来是 BFS 较为模板的题。

不过，与纯粹的模板题相比，本题的**改进**是给定了一个范围 $k$，使得每次移动**并不是**只能移动到相邻的合法格子，**而是**可以在四个方向没有被障碍拦住的格子上**任意**拓展 $1$ 至 $k$ 步。

那么，就可以在原来的广搜模板上稍作改进，变成如下这样：
```
for(int i=0;i<4;i++)
{
	for(int j=1;j<=k;j++)//新加的循环 
	{
		int nowx=now.x+dx[i]*j; 
		int nowy=now.y+dy[i]*j;
		//以及对现在的位置进行一些处理 
	}
}
```
这样，本题的大致代码就差不多了。

不过，如果仅仅进行这样的修改，会有两个小小的问题：

首先，一般的数组存不下这张地图。

其次，会超时。

那么该如何改进呢？

# 优化改进

第一个问题还是比较简单的，我们可以使用具有动态大小的数组 vector 来存图。

至于第二个问题，需要运用一个小小的剪枝：
```
if(vis[nowx][nowy]&&vis[nowx][nowy]<=vis[now.x][now.y]) break;//如果说当前的位置已经被访问过了，且此前访问时的步数小于当前的步数，说明本次决策不优，退出循环
```
这样，我们就能愉快地通过这道~~很水的~~蓝题了。

# code
```
#include<bits/stdc++.h> 
#define int long long
using namespace std;
struct node
{
	int x,y;
};
int n,m,k,sx,ex,sy,ey;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
vector<char> g[1000005];
vector<int> vis[1000005];
queue<node> q;
void bfs()
{
	q.push(node{sx,sy});
	vis[sx][sy]=1;
	while(!q.empty())
	{
		if(vis[ex][ey]) break;
		node now=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			for(int j=1;j<=k;j++)
			{
				int nowx=now.x+dx[i]*j;
				int nowy=now.y+dy[i]*j;
				if(nowx>n||nowx<1||nowy<1||nowy>m||g[nowx][nowy]=='@') break;
				if(vis[nowx][nowy]&&vis[nowx][nowy]<=vis[now.x][now.y]) break;
				if(vis[nowx][nowy]) continue;
				vis[nowx][nowy]=vis[now.x][now.y]+1;
				q.push(node{nowx,nowy});
			}
		}
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	cin>>sx>>sy>>ex>>ey;
	for(int i=1;i<=n;i++)
	{
		g[i].push_back('@');
		vis[i].push_back(0);
		for(int j=1;j<=m;j++)
		{
			char in;
			cin>>in;
			g[i].push_back(in);
			vis[i].push_back(0);
		}
	}
	bfs();
	if(!vis[ex][ey]) cout<<-1<<"\n";
	else cout<<vis[ex][ey]-1<<"\n";
	return 0;
} 
```

---

## 作者：WFHFAQFXY (赞：1)

# 基本思路 #
看到走迷宫类的题，果断 bfs。

然后看到数据范围……直接开会炸。

然后看到 $H \times W \le 10^6$，发现这个数据下，直接开一个 $10^6 \times 10^6$ 的数组是肯定不行的，所以要用动态数组 vector，点数是少的，不会 MLE。

可以直接 bfs，再多加一个循环来枚举每一次的走的步数，如果一个点走不了了直接就 break，代码主体如下。

```cpp
while(q.size()&&!dis[xx][yy])
    {
        node nw=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            for(int j=1;j<=k;j++)
            {
                int nx=nw.x+jk[i][0]*j;
                int ny=nw.y+jk[i][1]*j;
                if(nx<1||nx>n||ny<1||ny>m||g[nx][ny]=='@') break;
                if(!dis[nx][ny])
                {
                	dis[nx][ny]=dis[nw.x][nw.y]+1;
                	q.push((node){nx, ny});
				}
            }
        }
    }
```

如果你交了会发现这样会超时，考虑剪枝。

这里我采用一种贪心，其实类似于最短路的方法，使用一个数组来记录走到这一步的最少步数，然后每次走到这个点的时候进行一次判断，如果当前的步数比数组里这个点存的步数还少，就对这个点进行“松弛”操作，否则就不继续搜索因为无论如何前面的那种方法一定比现在的更优了。代码如下。

```cpp
while(q.size()&&!dis[xx][yy])
{
	node nw=q.front();
	q.pop();
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<=k;j++)
		{
			int nx=nw.x+jk[i][0]*j;
			int ny=nw.y+jk[i][1]*j;
			if(nx<1||nx>n||ny<1||ny>m||g[nx][ny]=='@') break;
			if(dis[nx][ny]&&dis[nx][ny]<=dis[nw.x][nw.y]) break;//加入这句话，在这里实现记录操作
			if(!dis[nx][ny])
			{
				dis[nx][ny]=dis[nw.x][nw.y]+1;
				q.push((node){nx, ny});
			}
		}
	}
}
```
最坏时间复杂度表面上仍然和前面的差不多，但是由于每次在将节点取出时步数枚举量大幅减少了，所以时间复杂度应该小于上文的那种，毕竟只用一种就可以完全去除掉之后的状态。

# AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,x,y,xx,yy;
char mid;
vector<char> g[1000005];
vector<int> dis[1000005];
struct node{
	int x,y;
};
queue<node> q;
int jk[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int main()
{
    cin>>n>>m>>k>>x>>y>>xx>>yy;
    for(int i=1;i<=n;i++)
    {
        g[i].push_back('@');
        dis[i].push_back(0);
        for(int j=1;j<=m;j++)
        {
            cin>>mid;
            g[i].push_back(mid);
            dis[i].push_back(0);
        }
    }
    q.push((node){x,y});
    dis[x][y]=1;
    while(q.size()&&!dis[xx][yy])
    {
        node nw=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            for(int j=1;j<=k;j++)
            {
                int nx=nw.x+jk[i][0]*j;
                int ny=nw.y+jk[i][1]*j;
                if(nx<1||nx>n||ny<1||ny>m||g[nx][ny]=='@') break;
                if(dis[nx][ny]&&dis[nx][ny]<=dis[nw.x][nw.y]) break;
                if(!dis[nx][ny])
                {
                	dis[nx][ny]=dis[nw.x][nw.y]+1;
                	q.push((node){nx, ny});
				}
            }
        }
    }
    if(dis[xx][yy]) cout<<dis[xx][yy]-1;
    else cout<<-1;
    return 0;
}
```

---

## 作者：liruizhou_lihui (赞：1)

本题翻译有一点问题，假设行走 $x$ 步，那么 $1 \sim x-1$ 步之内也不可以是死路。

## 思路分析



首先你会发现如果直接开二维数组就会爆炸，可以考虑动态二维数组存储。

步入正题，这个题是个裸的宽搜，需要一点小优化。

优化思路：可以如果路途中间遇到了一样近或更近的点就可以停了，后面没走的那些位置显然可以通过这个点走过去而不会更劣。

## 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000000;//n最大值。
int n,m,k;
int x,y,xx,yy;//开始坐标和结束坐标。
char temp;//wyy替身。
vector<char>g[MAXN+5];//图。
vector<int>dis[MAXN+5];//dis[i][j]代表从 (x,y) 到 (i,j) 最短步数。
queue<pair<int,int>>q;// BFS 队列。
int dx[]={0,0,1,-1};//坐标转移。
int dy[]={-1,1,0,0};
int main()
{ 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>k;
	cin>>x>>y>>xx>>yy;
	for(int i=1;i<=n;i++)
	{
		g[i].push_back('@');//本人习惯从 1 开始。
		dis[i].push_back(0);
		for(int j=1;j<=m;j++)
		{
			cin>>temp;//输入。 
			g[i].push_back(temp);//弹进去。
			dis[i].push_back(0); 
		}
	}
	q.push(make_pair(x,y));
	dis[x][y]=1;//改成一步走到。
	while(!q.empty() && !dis[xx][yy])
	{
		pair<int,int>now=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			for(int j=1;j<=k;j++)// 1 到 k 步。
			{
				int nx=now.first+dx[i]*j;//构造出坐标。
				int ny=now.second+dy[i]*j;
				if(nx<1 || nx>n || ny<1 || ny>m || g[nx][ny]=='@')
				{//如果这些不合法那么后边更多肯定也不合法，所以直接 break 即可。
					break;
				}
				if(dis[nx][ny] && dis[nx][ny]<=dis[now.first][now.second])
				{//如果走过并且更优直接结束后面肯定也更优。 
					break;
				}
				if(dis[nx][ny])
				{//如果之前已经走过直接结束本次。 
					continue;
				}
				
				dis[nx][ny]=dis[now.first][now.second]+1;//标记路程。
				q.push(make_pair(nx,ny));//压入队列。
			}
		}
	}
	if(dis[xx][yy])//如果走到了。 
	{
		cout<<dis[xx][yy]-1<<"\n";//输出。
		//要 -1 是因为初始 dis[x][y] 是 1。 
	}
	else
	{
		cout<<-1<<"\n";//无解输出-1。
	}
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
直接一眼就可以看出用搜索了，但是一看这题值域可知普通搜索必定超时。考虑如何优化，也就是剪枝。假设有一个点对 $(x,y)$，和另一个点对 $(x,y1)$，有 $y1-y\leq k$。也就是说从 $(x,y)$ 用至多 $k$ 步可以到达 $(x,y1)$。设 $d_{xy}$ 为起点到 $(x,y)$ 所用步数，如果 $d_{xy1}>d_{xy}+1$，那么从 $(x,y)$ 到 $(x,y1)$ 的步数显然更优。当然，我们在搜索枚举每个方向以及这个方向所走的步数时，若存在一个点的步数比当前我所在的点的步数还要少，这个方向的点都没有必要更新了，因为从那个点出发去更新从原来的点出发可到达的点一定更优。 
### 代码
```cpp
// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC optimize(2)
#include<bits/stdc++.h>

#include<algorithm>

using namespace std;
#define int long long
// #define re register
#define For(i, l, r) for (int i = l; i <= r; i++)
    #define Rep(i, l, r) for (int i = l; i >= r; i--)
        #define ls(c) c << 1
#define rs(c) c << 1 | 1
#define max(x, y)((x) > (y) ? (x) : (y))
#define min(x, y)((x) < (y) ? (x) : (y))
const int N = 1e4 + 5;
inline void fast() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
inline void read(int & x) {
    x = 0;
    int f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}
inline void write(int x) {
    if (x < 0) { x = -x;
        putchar('-'); }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int h, w, k;
int sx, sy, ex, ey;
char s[N][N];
int step[N][N];
struct Node {
    int x, y;
};
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
inline void solve() {
    queue < Node > q;
    q.push((Node) { sx, sy });
    step[sx][sy] = 0;
    while (q.size()) {
        Node fr = q.front();
        q.pop();
        For(i, 0, 3) {
            int nx = fr.x, ny = fr.y;
            For(j, 1, k) {
                nx += dx[i], ny += dy[i];
                if (s[nx][ny] == '@' || nx < 0 || nx >= h || ny < 0 || ny >= w || step[nx][ny] < step[fr.x][fr.y] + 1) break;
                if (step[nx][ny] > step[fr.x][fr.y] + 1) {
                    step[nx][ny] = step[fr.x][fr.y] + 1;
                    q.push((Node) { nx, ny });
                }
            }
        }
    }
    cout << (step[ex][ey] == 1e18 ? -1 : step[ex][ey]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> h >> w >> k >> sx >> sy >> ex >> ey;
    sx--;
    sy--;
    ex--;
    ey--;
    For(i, 0, h - 1) {
        // s[i]=" ";
        For(j, 0, w - 1) {
            cin >> s[i][j];
            step[i][j] = 1e18;
            // cout<<s[i][j];
        } //cout<<'\n';
    }
    solve();
    return 0;
}
```
#### 小坑
根据题目所述的 $H\times W \leq 10^6$，数组空间开到一万就可以了。

---

## 作者：csxx601cjy (赞：0)

### 题解：AT_abc170_f [ABC170F] Pond Skater
[题目传送门](https://www.luogu.com.cn/problem/AT_abc170_f)

~~我们老师居然给我们模拟赛 T2 做蓝题~~
### 思路
广搜模板加剪枝优化，不过这优化比较难想。

首先看范围，$1\le H,W\le10^6$，显然不能静态数组存。由于 $1\le H\times W\le10^6$，考虑使用 vector。

然后你就可以~~用每秒十万次的手速~~打好 bfs 模板：
```cpp
#include<bits/stdc++.h>
#define M 1000010
using namespace std;
struct d{int x,y;}st,ed;
int n,m,k,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector<int>g[M],dis[M];
char t;
queue<d>q;
int main(){
	cin>>n>>m>>k>>st.x>>st.y>>ed.x>>ed.y;
	for(int i=1;i<=n;i++){
		g[i].push_back(0);
		dis[i].push_back(0);
		for(int j=1;j<=m;j++){
			cin>>t;
			g[i].push_back(t=='.');
			dis[i].push_back(0);
		}
	}//输入数据
	
	//bfs模板
	q.push(st);
	dis[st.x][st.y]=1;
	while(!q.empty()&&!dis[ed.x][ed.y]){
		d now=q.front(),nxt;
		q.pop();
		for(int i=0;i<4;i++){//枚举方向
			for(int j=1;j<=k;j++){//枚举步数
				nxt.x=now.x+dx[i]*j;
				nxt.y=now.y+dy[i]*j;//走下一步
				if(nxt.x>n||nxt.x<1||nxt.y>m||nxt.y<1||!g[nxt.x][nxt.y])break;//是否能走
				if(dis[nxt.x][nxt.y])continue;
				dis[nxt.x][nxt.y]=dis[now.x][now.y]+1;
				q.push(nxt);
			}
		}
	}
	
	if(dis[ed.x][ed.y])cout<<dis[ed.x][ed.y]-1;
	else cout<<-1;//输出答案
	
	putchar('\n');
	return 0;
}
```
很明显，$k\le10^6$，过不了。

所以我们需要剪枝，考虑到从一个点走到另一个点，如果距离反而更长了，可以直接剪掉。因此，加上代码：
```cpp
if(dis[nxt.x][nxt.y]&&dis[nxt.x][nxt.y]<=dis[now.x][now.y])break;
```
可以优化，从而通过此题。

### 完整 AC 代码
```cpp
#include<bits/stdc++.h>
#define M 1000010
using namespace std;
struct d{int x,y;}st,ed;
int n,m,k,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector<int>g[M],dis[M];
char t;
queue<d>q;
int main(){
	cin>>n>>m>>k>>st.x>>st.y>>ed.x>>ed.y;
	for(int i=1;i<=n;i++){
		g[i].push_back(0),dis[i].push_back(0);
		for(int j=1;j<=m;j++){
			cin>>t;
			g[i].push_back(t=='.'),dis[i].push_back(0);
		}
	}
	q.push(st);
	dis[st.x][st.y]=1;
	while(!q.empty()&&!dis[ed.x][ed.y]){
		d now=q.front(),nxt;
		q.pop();
		for(int i=0;i<4;i++){
			for(int j=1;j<=k;j++){
				nxt.x=now.x+dx[i]*j;
				nxt.y=now.y+dy[i]*j;
				if(nxt.x>n||nxt.x<1||nxt.y>m||nxt.y<1||!g[nxt.x][nxt.y])break;
				if(dis[nxt.x][nxt.y]){
					if(dis[nxt.x][nxt.y]<=dis[now.x][now.y])break;
					else continue;
				}
				dis[nxt.x][nxt.y]=dis[now.x][now.y]+1;
				q.push(nxt);
			}
		}
	}
	if(dis[ed.x][ed.y])cout<<dis[ed.x][ed.y]-1;
	else cout<<-1;
	putchar('\n');
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## [ABC170F] Pond Skater 题解
### Solution
这是一道需要一些优化的广搜题。坑点较多，我们一起来看一下。
#### 初始化和读入
看到 $H \times W \le 10^6$，且 $H,W \le 10^6$，我们就会发现普通的二维数组会直接 MLE 掉。这里可以使用字符串数组或动态数组。我这里使用的是动态数组。根据个人不同的习惯，可以对数组进行一定的预处理。如果更习惯下标从 $1$ 开始，就可以初始时往里边随便压入一个数字或字符。
#### 搜索部分
两层 for 循环，枚举四联通和 $K$。但是纯暴力的话，时间复杂度约为 $O(NMK)$，大概率会爆炸。可以使用如下思路优化：

- 如果走当前步数的情况下，出现了越界、障碍物，那么在往下走就没有意义了，直接结束循环。
- 当你搜索到了一个点 $(i,j)$ 的扩展点 $(x_0,y_0)$，这个点之前已经走过且从起始点到达该点的距离**小于等于**从起点到达 $(i,j)$ 的距离，那么接下来一定以 $(x_0,y_0)$ 作为起点而不是以 $(i,j)$ 为起点更优。你就可以直接退出循环了。
- 其他同普通 BFS。

这样搜索的效率约为 $O(HW)$，因为每个点最多会被当作被扩展点一次，可以通过本题。
### [AC](https://www.luogu.com.cn/record/183519022) Code
```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int N=1e6+10;
struct Node{
	int x;
	int y;
}s,e;
int dx[]={0,0,0,1,-1};
int dy[]={0,1,-1,0,0};
vector<char>mp[N];
vector<int>dis[N];
queue<Node>q;	
int n,m,k;
bool check(int px,int py,int xx,int yy){
	if(xx<1||xx>n||yy<1||yy>m||mp[xx][yy]=='@') return 0;
	if(dis[xx][yy]&&dis[xx][yy]<=dis[px][py]) return 0;
	return 1;
}
void kkksc03(){
	q.push({s.x,s.y});
	while(!q.empty()){
		int prevx=q.front().x;
		int prevy=q.front().y;
		q.pop();
		for(int i=1;i<=4;i++){
			for(int stp=1;stp<=k;stp++){
				int xx=prevx+dx[i]*stp;
				int yy=prevy+dy[i]*stp;
				if(!check(prevx,prevy,xx,yy)) break;
				if(!dis[xx][yy]){
					dis[xx][yy]=dis[prevx][prevy]+1;
					q.push({xx,yy});
				}
			}
		}
	}
	return;
}
int main(){
	cin>>n>>m>>k;
	cin>>s.x>>s.y>>e.x>>e.y;
	for(int i=1;i<=n;i++){
		mp[i].push_back('$');//占位，使得下标从(1,1)到(n,m) 
		dis[i].insert(dis[i].begin(),m+1,0);
		for(int IOI=1;IOI<=m;IOI++){
			char ch;
			cin>>ch;
			mp[i].push_back(ch);
		} 
	}
	kkksc03();
	cout<<(dis[e.x][e.y]?dis[e.x][e.y]:-1)<<endl;
    return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

直接优化 bfs 的搜索方式即可过掉此题，之所以直接搜索会 TLE 就是因为当你发现从一个点走到 $(i,j)$ 比以前已经枚举了的一个点到 $(i,j)$ 优的时候，你就会花大量的时间重新入队，那么我们要做的就是最小化这个入队的次数，考虑从一个点走到另一个点，如果这个点到那个点的距离**不小于**之前枚举的点到那个点的距离，那么这一整条路上的点都不用继续看了，因为看了也是白看，明明有一个更优的方案，当然可以等待队列排到那个点再来枚举了，这样做的话时间复杂度就应该是 $O(HW)$ 的。

注意动态数组的使用，对平常不用动态数组的人来说可能会调试很久才能过编译。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,h,x,ne) for(register int i=h[x];~i;i=ne[i])
#define debug() puts("----------")
const int N=1e6+10;
using namespace std;
int n,m,k;
pii s,e;
vector<char> mp[N];
vector<int> dist[N];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
void bfs()
{
	rep1(i,1,n) 
	{
		dist[i].push_back(-1);
		rep1(j,1,m) dist[i].push_back(-1);
	}
	dist[s.x][s.y]=0;
	queue<pii> q;
	q.push(s);
	while(!q.empty())
	{
		pii t=q.front();
		q.pop();
		rep1(i,0,3)
		{
			int tx=t.x;
			int ty=t.y;
			rep1(j,1,k)
			{
				tx+=dx[i];
				ty+=dy[i];
				if(tx<=0||tx>n||ty<=0||ty>m||mp[tx][ty]=='@'||(~dist[tx][ty]&&dist[tx][ty]<=dist[t.x][t.y])) break; 
				if(~dist[tx][ty]) continue;
				dist[tx][ty]=dist[t.x][t.y]+1;
				q.push(make_pair(tx,ty));
			}
		}
	}
	return;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	m=read();
	k=read();
	s.x=read();
	s.y=read();
	e.x=read();
	e.y=read(); 
	rep1(i,1,n) 
	{
		mp[i].push_back('~');
		rep1(j,1,m)
		{
			char ch;
			cin>>ch;
			mp[i].push_back(ch);
		}
	}
	bfs();
	cout<<dist[e.x][e.y]<<endl;
	return 0;
}

```

---

