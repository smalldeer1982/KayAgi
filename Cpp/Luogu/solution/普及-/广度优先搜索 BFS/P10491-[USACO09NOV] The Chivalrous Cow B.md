# [USACO09NOV] The Chivalrous Cow B

## 题目背景

农民 John 有很多牛，他想交易其中一头被 Don 称为 The Knight 的牛。这头牛有一个独一无二的超能力，在农场里像 Knight 一样地跳（就是我们熟悉的象棋中马的走法）。虽然这头神奇的牛不能跳到树上和石头上，但是它可以在牧场上随意跳，我们把牧场用一个 $x，y$ 的坐标图来表示。

## 题目描述

这头神奇的牛像其它牛一样喜欢吃草，给你一张地图，上面标注了 The Knight 的开始位置，树、灌木、石头以及其它障碍的位置，除此之外还有一捆草。现在你的任务是，确定 The Knight 要想吃到草，至少需要跳多少次。The Knight 的位置用 `K` 来标记，障碍的位置用 `*` 来标记，草的位置用 `H` 来标记。

这里有一个地图的例子：
```
             11 | . . . . . . . . . .
             10 | . . . . * . . . . . 
              9 | . . . . . . . . . . 
              8 | . . . * . * . . . . 
              7 | . . . . . . . * . . 
              6 | . . * . . * . . . H 
              5 | * . . . . . . . . . 
              4 | . . . * . . . * . . 
              3 | . K . . . . . . . . 
              2 | . . . * . . . . . * 
              1 | . . * . . . . * . . 
              0 ----------------------
                                    1 
                0 1 2 3 4 5 6 7 8 9 0 
```
The Knight 可以按照下图中的 $A,B,C,D...$ 这条路径用 $5$ 次跳到草的地方（有可能其它路线的长度也是 $5$）：
```
             11 | . . . . . . . . . .
             10 | . . . . * . . . . .
              9 | . . . . . . . . . .
              8 | . . . * . * . . . .
              7 | . . . . . . . * . .
              6 | . . * . . * . . . F<
              5 | * . B . . . . . . .
              4 | . . . * C . . * E .
              3 | .>A . . . . D . . .
              2 | . . . * . . . . . *
              1 | . . * . . . . * . .
              0 ----------------------
                                    1
                0 1 2 3 4 5 6 7 8 9 0
                ```

## 说明/提示

Hint：这类问题可以用一个简单的先进先出表（队列）来解决。

## 样例 #1

### 输入

```
10 11
..........
....*.....
..........
...*.*....
.......*..
..*..*...H
*.........
...*...*..
.K........
...*.....*
..*....*..```

### 输出

```
5```

# 题解

## 作者：2023gdgz01 (赞：10)

bfs 模板题。

用队列 $q$ 来存储遍历的点，其类型为 `queue<pair<int, int> >`；用 $dis_{(x,y)}$ 记录从起点到 $(x,y)$ 的距离。初始时，$q$ 中仅有起点 $(sx,sy)$，即 The Knight 的初始位置，$dis_{(i,j)}=\begin{cases}0&i=sx,j=sy\\-1&\operatorname{otherwise}\end{cases}$，其中 $-1$ 表示未到达。

当 $q$ 不为空时，取出队首并存入 $temp$。若已到达草的位置，则结束 bfs；否则更新 $temp$ 能够到达的点。象棋中马的走法如下（`a` 表示当前位置，`b` 表示可能到达的位置，`.` 表示其它位置）：

```plain
.b.b.
b...b
..a..
b...b
.b.b.
```

由此，我们可以求出偏移量数组，即下一步坐标的变化方式：

```cpp
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}; //横坐标的变化方式
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1}; //纵坐标的变化方式
```

$temp$ 下一步的更新就依赖于偏移量数组，具体如下：遍历偏移量数组，求出可能的下一步 $(nx,ny)$，其中 `nx = temp.first + dx[i], ny = temp.second + dy[i]`，若 $(nx,ny)$ 不越界、未访问且不是灌木，则称 $(nx,ny)$ 位置合法，并将 $(nx,ny)$ 入队，`dis[nx][ny] = dis[temp.first][temp.second] + 1;`，完成更新。可结合代码理解。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <utility>
#include <queue>

using namespace std;

char g[155][155];
int n, m, sx, sy, ex, ey, nx, ny, dis[155][155], dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
queue<pair<int, int> > q;
pair<int, int> temp;

inline int bfs() { //广度优先搜索
	q.push(make_pair(sx, sy));
	memset(dis, -1, sizeof(dis));
	dis[sx][sy] = 0;
	while (!q.empty()) {
		temp = q.front(); //队首出队
		q.pop();
		if (temp.first == ex && temp.second == ey) //到达草的位置
			return dis[ex][ey];
		for (register int i = 0; i < 8; ++i) { //更新下一步
			nx = temp.first + dx[i];
			ny = temp.second + dy[i];
			if (nx < 1 || nx > n || ny < 1 || ny > m || dis[nx][ny] != -1 || g[nx][ny] == '*') //下一步位置不合法
				continue;
			q.push(make_pair(nx, ny)); //合法位置入队
			dis[nx][ny] = dis[temp.first][temp.second] + 1; //更新距离
		}
	}
	//如果执行到这就说明到达不了草的位置，数据出错了
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> m >> n; //坑人
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j) {
			cin >> g[i][j];
			if (g[i][j] == 'K') { //确定 Knight 的位置
				sx = i;
				sy = j;
			}
			if (g[i][j] == 'H') { //确定草的位置
				ex = i;
				ey = j;
			}
		}
	cout << bfs();
	return 0;
}
```

时间复杂度为 $O(nm)$。[AC 链接](https://www.luogu.com.cn/record/159234017)

---

## 作者：_ayaka_ (赞：3)

### 思路
这道题数据范围极小，所以可以使用宽搜。

我们只需要用队列保存我们搜到的点的情况及到此处的步数，不断将点取出进行移动后再存入，并判定当前的位置是否是终点就行了！
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, a, b, vis[205][205];
int dx[]={0,1,-1,2,-2,1,-1,2,-2};
int dy[]={0,2,-2,1,-1,-2,2,-1,1};
char d[205][205];
struct node {
	int x, y, step;
};
queue <node> q;
void bfs() {
	q.push({a, b, 0});
	while (!q.empty()) {
		node h=q.front();
		q.pop();
		for(int i=1;i<=8;i++){
			int xx=h.x+dx[i],yy=h.y+dy[i];
			if(xx>=1&&yy>=1&&xx<=n&&yy<=m&&!vis[xx][yy]&&d[xx][yy]!='*'){
				vis[xx][yy]=1;
				if(d[xx][yy]=='H'){
					cout<<h.step+1<<"\n";
					return ; 
				}
				q.push({xx,yy,h.step+1});
			}
		}
	}
}
signed main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> d[i][j];
			if (d[i][j] == 'K') a = i, b = j;
		}
	bfs();
	return 0;
}
```

---

## 作者：_iridescent (赞：2)

### 题目大意 

给你一个牧场，牧场中有可以吃的草和不能走的障碍，现在有一头特殊的牛（走法和中国象棋中的马相同），给出牛当前的坐标，求这头牛要吃到草至少要走几步。

### 思路

和其他的搜索题几乎没有太大的区别，只需要设定初始位置和特殊的偏移量即可。

还有一点，在当前所在点第一次正好是草时，我们直接返回此时的步数，就可以得到最小值，无需再像其他搜索题那样通过打擂台比较答案大小。

具体的思路就在下面代码的注释里了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int maxn=155;
struct node{
    int x,y;
};
queue<node> q;
int n,m;
int vis[maxn][maxn],d[10][10]={{-2,-1},{-2,1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2},{-1,2}}; //d数组用来表示当前点可以移动的八个方向
char mp[maxn][maxn];
int bfs(int n,int m){
    // 将起点坐标入队，并标记为已访问
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='K'){
                q.push({i,j});
                vis[i][j]=1;
            }
        }
    }
    int ans=0;  // 步数计数器
    while(!q.empty()){
        int size=q.size();
        for(int i=1;i<=size;i++){
            node head=q.front(); // 获取队头坐标
            q.pop(); // 记得让其出队以便于之后计算下一个坐标
            if(mp[head.x][head.y]=='H')return ans;  // 如果到达终点，返回当前步数
            // 遍历八个可能的方向
            for(int i=0;i<8;i++){
                int xx=head.x+d[i][0],yy=head.y+d[i][1]; // 计算新的横纵坐标
                // 判断新坐标是否合法，并且未被访问过，如果符合条件则入队并标记为已访问
                if(xx>0&&xx<=n&&yy>0&&yy<=m&&mp[xx][yy]!='*'&&!vis[xx][yy]){
                    q.push({xx,yy});
                    vis[xx][yy]=1;
                }
            }
        }
        ans++;  // 当前层搜索结束后，步数加一
    }
    return -1;  // 如果无法到达终点，返回-1
}
signed main(){
    cin>>m>>n;  
    for(int i=1;i<=n;i++)cin>>mp[i];
    cout<<bfs(n,m)<<endl;
    return 0;
}

```

---

## 作者：Albatross_LC (赞：2)

## 思路:

这是一道板子题，直接 BFS 即可。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const vector<pair<int, int>> knight_moves = {
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1}
};//八个方向
int main() {
    int cols, rows;
    cin >> cols >> rows;
    vector<string> farm(rows);
    for (int i = 0; i < rows; ++i)
        cin >> farm[i];
    pair<int, int> start, end;
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (farm[y][x] == 'K') start = {x, y};//起点
            else if (farm[y][x] == 'H') end = {x, y};//终点
    queue<pair<pair<int, int>, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    q.push({start, 0});
    visited[start.second][start.first] = true;
    while (!q.empty()) {
        auto [pos, jumps] = q.front();
        q.pop();
        int x = pos.first;
        int y = pos.second;
        if (x == end.first && y == end.second) {
            cout << jumps << endl;
            return 0;
        }
        for (const auto& move : knight_moves) {
            int nx = x + move.first;
            int ny = y + move.second;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && !visited[ny][nx] && farm[ny][nx] != '*') {
                visited[ny][nx] = true;
            	q.push({{nx, ny}, jumps + 1});//每次将当前点加入栈中，方便进行下次搜索
	    }
        }
    }
}
```

---

## 作者：nightwatch.ryan (赞：1)

### 思路
由于这道题需要求最小次数，所以我们使用广搜。将起始状态加入队列，然后枚举所有合法的状态加入队列，一步一步拓展，如果当前点是终点，就输出达到这个点的次数，因为广搜的性质，到达某个点的次数一定是最少的。
### 代码
```cpp
#include<iostream>
#include<queue>
#define N 155
int dx[8]={1,2,2,1,-1,-2,-2,-1};
int dy[8]={-2,-1,1,2,2,1,-1,-2};
struct Node{int x,y,s;};
char mp[N][N];
bool vis[N][N];
int main(){
	int r,c,sx,sy,fx,fy;
	std::cin>>r>>c;
	for(int i=1;i<=c;i++){
		for(int j=1;j<=r;j++){
			std::cin>>mp[i][j];
			if(mp[i][j]=='K')sx=i,sy=j;
			else if(mp[i][j]=='H')fx=i,fy=j;
		}
	}
	std::queue<Node>q;
	q.push({sx,sy,0});
	vis[sx][sy]=1;
	while(q.size()){
		Node u=q.front();
		q.pop();
		if(u.x==fx&&u.y==fy){
			std::cout<<u.s;
			return 0;
		}
		for(int i=0;i<8;i++){
			int nx=u.x+dx[i];
			int ny=u.y+dy[i];
			if(nx>=1&&nx<=c&&ny>=1&&ny<=r&&!vis[nx][ny]&&mp[nx][ny]!='*'){
				q.push({nx,ny,u.s+1});
				vis[nx][ny]=1;
			}
		}
	}
} 
```

---

## 作者：__qkj__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10491)
## 解题思路
直接 BFS。

**注意：$n,m$ 的输入是反的！**

在输入的时候保存 `K` 的下标，直接 `push` 到队列里。

我没有把起点、终点给置成 `.`，所以可以在判断是否到终点时，直接判断它是否等于 `H`，如果是，输出答案；否则，把它置成 `*`。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[200][200];
int dx[]={1,1,2,2,-1,-1,-2,-2};
int dy[]={2,-2,1,-1,2,-2,1,-1};
struct node
{
	int x,y,z;
}now,tmp;
queue<node>q;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>m>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='K')now.x=i,now.y=j;
		}
	q.push(now);
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		for(int i=0;i<8;i++)
		{
			int xx=now.x+dx[i];
			int yy=now.y+dy[i];
			if(xx<=n&&xx>=1&&yy<=m&&yy>=1&&a[xx][yy]!='*')
			{
				tmp.x=xx;
				tmp.y=yy;
				tmp.z=now.z+1;
				q.push(tmp);
				if(a[xx][yy]=='H')
				{
					cout<<tmp.z;
					exit(0);
				}
				a[xx][yy]='*';
			}
		}
	}
	return 0;
}

```

---

## 作者：__Sky__Dream__ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P10491)

## 题目大意
给一个图，`*` 是阻碍物，`H` 是终点，`K` 是起点。

## 解题思路
这很像象棋，其实一个迷宫就是一个图，只是把 $(x,y)$ 映射为了一个节点而已。

如果遇到障碍物不能走，明显可以用 DFS 或者 BFS 去找最短路径。BFS 主要一点就在于，如何去记录路数。

我们先把这个无向图用邻接表存下来，然后把 $1$ 号点放入类型为 `data` 的 `queue` 中，然后再去找与 $1$ 号节点有直接边的节点，依次入队；同时需要标记这个节点有没有访问，因为如果你不标记那么在无向图里面就会返回访问，所以按照这个思路在去找 $2$ 号节点，以此类推。

最后结束条件就是队列如果为空,结束访问；因为这是权值都为 $1$ 的无向图，所以可以用 BFS。

注意这里需要记录最短路径，所以我们用一个节点的子节中的元素表示他的父节点走的步数。

其余见代码。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define long long ll;
int a[200][200];//整数的迷宫
int X,Y;
char ch[200][200];//字符型的迷宫
int endx,endy; //终点
int book[200][200];//标记
int dir[8][2]={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};//初始化8个方向
struct data
{//这里有坐标+一个记录步数
  	int x,y;
  	int dis;
  	data(int xx,int yy,int d):x(xx),y(yy),dis(d){}//构造函数
};
void bfs(int x,int y,int step)
{
	queue<data> q;
	q.push(data(x,y,step));
	while(q.size())
	{
	    data t=q.front();q.pop();
	   	for(int i=0;i<8;i++)
		{
	   		int nx=t.x+dir[i][0];//枚举8个方向
	   	   	int ny=t.y+dir[i][1];
	   	   	if(nx>=1&&nx<=Y&&ny>=1&&ny<=X&&book[nx][ny]==0&&a[nx][ny]!=1)
			{//没越界+没标记+没障碍物
			    book[nx][ny]=1;//标记这个节点，表示访问过了
			    if(nx==endx&&ny==endy)
				{//到了终点
			        cout<<t.dis+1;
			        exit(0);//结束程序
			    }
				else q.push(data(nx,ny,t.dis+1));//进队
			}
	    }
	}
}
int main()
{
	int sx,sy;
   	scanf("%d %d",&X,&Y);
   	for(int i=0;i<Y;i++)
	{
   		scanf("%s",ch[i]);
   	  	for(int j=0;j<X;j++)
		{
   	  	    if(ch[i][j]=='*') a[i+1][j+1]=1;//障碍物 
			if(ch[i][j]=='H')
			{
				endx=i+1;
				endy=j+1;//终点坐标
				  //a[endx][endy]=8;
			}
			if(ch[i][j]=='K')
			{
			//a[i+1][j+1]=9;
				sx=i+1;sy=j+1;//开始地方（因为我这里的坐标建立是没有（0，0）的）
			}
		}
   	}
  	book[sx][sy]=1;//标记这个点走过了
  	bfs(sx,sy,0);
	return 0;
}
```

拜拜！

---

## 作者：J_Kobe (赞：1)

### 思路
这道题我们可以用**广搜**来做，相信大家应该都会用广搜吧。

我们首先找到牛的位置与草的位置，用四个变量存储好。开一个标记数组，用来标记有没有走过这里与障碍的位置。用一个队列存下每次走过的点，如果没走过的话，就用标记数组给它标记一下，代表走过这里，最后如果到了终点的话，就返回答案。

**注意**牛的走法是按照象棋中马的走法去走的，有 $8$ 个位置可以走，还有就是终点要记得标记。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, qx, qy, zx, zy;
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
char s[200][200];
bool f[200][200];
struct node{
	int x, y, v;
};
int bfs()
{
	queue<node> q;
	q.push((node){qx, qy, 0});
	while (!q.empty())
	{
		node k = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			int x = dx[i] + k.x;
			int y = dy[i] + k.y;
			if (x < 0 || x >= m || y < 0 || y >= n)
			{
				continue;
			}
			if (f[x][y])
			{
				continue;
			}
			if (x == zx && y == zy)
			{
				return k.v + 1;
			}
			f[x][y] = 1;
			q.push((node){x, y, k.v+1});
		}
	}
}

signed main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> s[i][j];
			if (s[i][j] == 'K')
			{
				qx = i, qy = j;
				f[i][j] = 1;
			}
			if (s[i][j] == 'H')
			{
				zx = i, zy = j;
			}
			if (s[i][j] == '*')
			{
				f[i][j] = 1;
			}
		}
	}
	cout << bfs() << endl;
	return 0;
}
```

---

