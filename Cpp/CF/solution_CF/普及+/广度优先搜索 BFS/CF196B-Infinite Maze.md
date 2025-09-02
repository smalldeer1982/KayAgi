# Infinite Maze

## 题目描述

We've got a rectangular $ n×m $ -cell maze. Each cell is either passable, or is a wall (impassable). A little boy found the maze and cyclically tiled a plane with it so that the plane became an infinite maze. Now on this plane cell $ (x,y) $ is a wall if and only if cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/90d712000eb85a8bfa2ea0243ba4ea17c7b21954.png) is a wall.

In this problem ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/8f971526abdeb0e01a924ce3de8c76d38e0d2bfd.png) is a remainder of dividing number $ a $ by number $ b $ .

The little boy stood at some cell on the plane and he wondered whether he can walk infinitely far away from his starting position. From cell $ (x,y) $ he can go to one of the following cells: $ (x,y-1) $ , $ (x,y+1) $ , $ (x-1,y) $ and $ (x+1,y) $ , provided that the cell he goes to is not a wall.

## 说明/提示

In the first sample the little boy can go up for infinitely long as there is a "clear path" that goes vertically. He just needs to repeat the following steps infinitely: up, up, left, up, up, right, up.

In the second sample the vertical path is blocked. The path to the left doesn't work, too — the next "copy" of the maze traps the boy.

## 样例 #1

### 输入

```
5 4
##.#
##S#
#..#
#.##
#..#
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 4
##.#
##S#
#..#
..#.
#.##
```

### 输出

```
No
```

# 题解

## 作者：filletoto (赞：3)

## 思路

因为迷宫 $a$ 是无限大的，所以我们不可能开很大的数组，只能对坐标进行取模。

如果走到过某个点现在又走到了这个点，那么就是可以走无限远的。

那么如何判断是否走到过这个点呢？

记录取模的横纵坐标 $x$ 和 $y$ 时，同时记录没有取模的坐标 $lx$ 和 $ly$。

当第一次走这个迷宫的时候，$x$ 和 $y$ 与 $x$ 和 $y$ 肯定是分别相等的。

所以只要走到的一个点的时候，一个点的 $x$ 和 $y$ 与 $lx$ 和 $ly$ 不相等，那这个点一定是被走了第二遍。

## [AC](https://codeforces.com/problemset/submission/196/222657565)代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define N 1500+5
int n,m,vis[N][N][3],st_x,st_y;
bool fl,a[N][N];
char ch;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
void dfs(int x,int y,int lx,int ly)
{
	if(vis[x][y][0]&&(vis[x][y][1]!=lx||vis[x][y][2]!=ly)) 
	{
		fl=1;
		return ;
	}
	if(fl) return ;
	vis[x][y][1]=lx;
	vis[x][y][2]=ly;
	vis[x][y][0]=1;
	for(int i=0;i<4;++i) 
	{
		int xx=(x+dx[i]+n)%n;
		int yy=(y+dy[i]+m)%m;
		int lxx=lx+dx[i];
		int lyy=ly+dy[i];
		if(!a[xx][yy]) 
		{
			if(vis[xx][yy][1]!=lxx||vis[xx][yy][2]!=lyy||!vis[xx][yy][0])
				dfs(xx, yy, lxx, lyy);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	fl=0;
	memset(a,0,sizeof(a));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j) 
		{
			cin>>ch;
			if(ch=='#') a[i][j]=1;
			if(ch=='S') 
			{
				st_x=i;
				st_y=j;
			}
		}
	}
	dfs(st_x,st_y,st_x,st_y);
	if(fl) puts("Yes");
	else puts("No");
	


	return 0;
}
```

---

## 作者：xukuan (赞：3)

这题的翻译完全没有和原题题意对上，可以看一下我的翻译：[https://www.luogu.org/blog/xukuan/translation-cf196b](https://www.luogu.org/blog/xukuan/translation-cf196b)

一道bfs，不过坑极多

### 大全：

Q1：以为是走出迷宫就可以A了（和翻译的原译者一样）

A1：你样例二看过没有？

Q2：以为把图复制成3\*3倍，再从起点开始能bfs到任意一个点就可以了

A2：第25组数据

```pascal
12 12
##.#######.#
#..#......S#
#.#..#######
..#.###.....
##..##..####
#..##..#####
..##..#.....
###..##.####
##..#...####
#..##.######
..##..####..
##...#####.#
```

你要复制n\*m倍，内存直接炸了

Q3：复制后走到另一幅图的S即可

A3：送一组数据4

```pascal
3 3
.#.
###
.#S
```

正解：dfs

dfs走到一个点。如果通过另一种方式能在出去这个图之后到这个点对应的点（两个点横坐标对n同余且纵坐标对m同余），就是能走无限。

时间复杂度：$O(nm)$，因为每个点至多被dfs1次

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio> 
#define ll long long
#define N 1510
using namespace std;

const ll dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
ll n,m,x,y,d[N][N][2];
string s[N];

void dfs(ll x,ll y){
    if(d[x%n][y%m][0]==-1&&d[x%n][y%m][1]==-1){//这个点之前没有到过
        d[x%n][y%m][0]=x;
		d[x%n][y%m][1]=y;
    }
    else if(d[x%n][y%m][0]!=x||d[x%n][y%m][1]!=y) exit(printf("Yes\n")&0);//这个点之前到过并且不是直接到的
    else return;//直接到过这个点
    for(ll i=0; i<4; i++){
    	ll X=x+dx[i],Y=y+dy[i];
		if(s[X%n][Y%m]=='.') dfs(X,Y);
    }
}
 
int main(){
    cin>>n>>m;
    for(ll i=0; i<n; i++){
    	cin>>s[i];
        for(ll j=0; j<m; j++){
            if(s[i][j]=='S'){
                s[i][j]='.';
                x=i+n*m;
                y=j+n*m;
                //防止减法溢出
            }
        }
    }
    memset(d,-1,sizeof(d));
	dfs(x,y);
    printf("No\n");
    return 0;
}
```

---

## 作者：__zhuruirong__ (赞：2)

本蒟蒻的第二篇题解，写的不好~~随时踩爆他~~

[更好的视觉体验](https://www.luogu.com.cn/blog/764442/solution-cf196b)

## 题目大意

有一个无限大的迷宫 $a$，是由无数个大小为 $n\times m$ 的相同的迷宫构成的（下面称为子迷宫），给你一个起始节点 $S$，问你能不能走到无穷远处。

## 解法分析

由于迷宫是无限大的，硬写暴力判断显然不行，考虑优化。

能发现，只要从 $S$ 一路走，一路标记，走到**另一个子迷宫**的一个已标记点且标记的迷宫不是当前迷宫，一定可以走到无穷远处。

证明：被标记的点只可能是能从 $S$ 走到的点，如果你走到了别的子迷宫的某个被标记位置，代表这两个子迷宫可以通过这种路径相连通，接下来只要不断重复这个路径就一定能走到无穷远处。算法正确性得证。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1510;
struct Node {
	bool is_find;
	int x, y;
}vis[N][N];
char s[N][N];
int n, m, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool dfs(int x, int y, int xx, int yy) {
	if(vis[x][y].is_find) { // 之前来过
		if(xx == vis[x][y].x and yy == vis[x][y].y) // 是在同一矩阵内
			return false;
		return true;
	}
	vis[x][y].is_find = true;
	vis[x][y].x = xx;
	vis[x][y].y = yy;
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i], nxx = xx, nyy = yy;
		if(nx < 1) {
			nxx--;
			nx = n;
		}
		else if(nx > n) {
			nxx++;
			nx = 1;
		}
		if(ny < 1) {
			nyy--;
			ny = m;
		}
		else if(ny > m) {
			nyy++;
			ny = 1;
		}
		if(s[nx][ny] == '#') continue;
		if(dfs(nx, ny, nxx, nyy))
			return true;
	}
	return false;
}

int main() {
	cin >> n >> m;
	int sx, sy;
	for(int i = 1; i <= n; i++) {
		cin >> s[i] + 1;
		for(int j = 1; j <= m; j++) {
			if(s[i][j] == 'S') {
				sx = i;
				sy = j;
			}
			vis[i][j].is_find = false;
		}
	}
	if(dfs(sx, sy, 0, 0))
		puts("Yes");
	else
		puts("No");
}

```

---

## 作者：syxmz (赞：2)


# CF197D Infinite Maze 解题报告

### 1 题目链接

[原题](https://codeforces.com/problemset/problem/197/D)

### 2 题目大意

有一个由已给出的地图周期性铺成的无限的迷宫，问从出发点 `S` 出发能否走到无穷远的地方。

### 3 解法分析

题目十分清晰，但似乎有一定的理解难度。

首先考虑什么情况才是符合题意的。

经过思考，可以知道如果可以走到相邻矩阵的同一个点，那么一定是可以永远走下去的。反之，若不能，则一定不能走下去。

于是你会发现这道题就非常简单了。

### 4 AC Code
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define N 1507
using namespace std;

int n, m;
int sx, sy;
int mp[N][N];
int vis[N][N];
int wx[N][N], wy[N][N];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool dfs(int x, int y) {
	int nx = ((x - 1) % n + n) % n + 1;
	int ny = ((y - 1) % m + m) % m + 1;
	if (mp[nx][ny])
		return 0;
	if (vis[nx][ny])
		return wx[nx][ny] != x || wy[nx][ny] != y;
	wx[nx][ny] = x;
	wy[nx][ny] = y;
	vis[nx][ny] = 1;
	rep(i, 0, 3)
		if (dfs(x + dx[i], y + dy[i]))
			return 1;
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) {
		string s;
		cin >> s;
		s = ' ' + s;
		rep(j, 1, m) {
			if (s[j] == 'S') {
				sx = i;
				sy = j;
			}
			mp[i][j] = (s[j] == '#');
			wx[i][j] = wy[i][j] = vis[i][j] = 0;
		}
	}
	puts(dfs(sx, sy) ? "Yes" : "No");
	return 0;
}
```

---

## 作者：XL4453 (赞：1)


~~一开始以为是个小清新，结果是个大毒瘤。~~

---
### 解题思路：

题目中的足够远意思是可以无限走下去。

如果一个点能从两个不经过相同点的路径到达，那么就一定可以无限地走下去。

考虑用搜索解决这个问题，记录下当前搜索到的点在整个迷宫中的坐标，然后可以算出这个点在题目给出的迷宫样板中的相对位置，如果一个相对位置被两个不同的整体坐标到达，那么就是满足条件的。

---

注意取模。

---
### 代码：

```
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,v[1505][1505][2],sx,sy,ans;
bool mp[1505][1505];
int dx[5]={-1,1,0,0,},dy[5]={0,0,1,-1};
char c;
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')
	c=getchar();
	return c;
}
void dfs(int x,int y){
	if(v[(x%n+n)%n][(y%m+m)%m][0]==x&&v[(x%n+n)%n][(y%m+m)%m][1]==y)return;
	
	if(v[(x%n+n)%n][(y%m+m)%m][0]==-1&&v[(x%n+n)%n][(y%m+m)%m][1]==-1)
	v[(x%n+n)%n][(y%m+m)%m][0]=x,v[(x%n+n)%n][(y%m+m)%m][1]=y;
	
	if(v[(x%n+n)%n][(y%m+m)%m][0]!=x||v[(x%n+n)%n][(y%m+m)%m][1]!=y)ans=1;
	
	if(ans)return;
	
	for(int i=0;i<=3;i++)
	if(mp[(x%n+n+dx[i])%n][(y%m+m+dy[i])%m]==0)
	dfs(x+dx[i],y+dy[i]);
}
int main(){
	memset(v,-1,sizeof(v));
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++){
		c=get();
		if(c=='#')mp[i][j]=1;
		if(c=='S')sx=i,sy=j;
	}
	dfs(sx,sy);
	if(ans==1)printf("Yes\n");
	else printf("No\n");
	return 0;
}
```


---

## 作者：Empty_Dream (赞：0)

# CF196B 解题报告

## 题意

给定长宽分别为 $n,m$ 的迷宫 $a$。

这个迷宫从顶部可以通向底部，同理从左边可以通向右边。即是有无限个这样的迷宫接在四个方向的。问你是否能在这个迷宫中走到无限远的地方。

## 分析

因为要走到无限远的地方，所以这个迷宫肯定能通过上边到达下边然后回到起点，左右同理。把迷宫拼起来后发现，如果 $s_{0,j}$ 可以走，那么 $s_{n,j}$ 肯定也可以走，左右同理。

之后直接从起点开始暴搜，判断是否满足条件。只要有一条合法路径，那么就能走到无限远。

考虑 dfs，可以直接使用 `bool` 类型函数判断到这个点是否有合法路径。dfs 中注意坐标的边界，当 $(x,y)$ 越过边界后，通过 $((x-1)\bmod n + n) \bmod n + 1$ 来更新 $x$，$((y-1) \bmod m + m) \bmod m + 1$ 来更新 $y$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m, sx, sy;
int vis[1505][1505], wx[1505][1505], wy[1505][1505];
string s[1505];

bool dfs(int x, int y){
	int nx = ((x - 1) % n + n) % n + 1;//更新
	int ny = ((y - 1) % m + m) % m + 1;
	if (s[nx][ny]) return 0;
	if (vis[nx][ny]) return wx[nx][ny] != x || wy[nx][ny] != y;//类似于判环，是否有几条路径走到这
	wx[nx][ny] = x, wy[nx][ny] = y;//记录一种到达(x,y)的情况
	vis[nx][ny] = 1;//标记走过
	for (int i = 0; i < 4; i++){
		if (dfs(x + dx[i], y + dy[i])) return 1;
	}
	return 0;
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++){
		cin >> s[i];
		s[i] = ' ' + s[i];
		for (int j = 1; j <= s[i].size(); j++){
			if (s[i][j] == 'S') sx = i, sy = j;
		}
	}
	if (dfs(sx, sy)) printf("Yes");//有一条路径满足
	else printf("No");
	return 0;
} 
```

---

## 作者：luxiaomao (赞：0)

## 朴素的 DFS 解法

题意应该不难理解，就是把一个迷宫视作一个小块，然后往上下左右无限堆积这个小块，构成一个无穷大的迷宫，求从出发点能不能走到无穷远。

刚开始我的想法是：只要能从初始的小迷宫中到达另一个小迷宫，那么同理，就能从这个新的小迷宫到达下一个小迷宫。

但是有一个 Hack：

```test
3 3
###
S#.
###
```

这样子，开局往左边走，确实可以到达另一个小迷宫，但是接下来就无路可走了。

所以，我们必须更改思路，重新审题：

> 从出发点走到无穷远。

由于这条无穷远的路线必然由无穷条贯穿小迷宫的路线组成，所以我们可以发现：这条路线必然反复经过小迷宫中的一些点。

听起来可能有点拗口，举个例子：如果从 $S$ 点出发，结果搜到了另一个小迷宫中的 $S$ 点，那么同理，从这个 $S$ 点又可以走到下一个 $S$ 点。这样子就可以无穷无尽地走下去了，符合题意。

## Code Time

其实思路得出后，代码的实现就不难了。

这里先说明一下码风：

- $x$ 和 $y$ 是坐标，$xx$ 和 $yy$ 是搜索时的搜到的新坐标。变量名加上 $m$ 前缀的就是进行取模后的坐标值。

- $vis$ 判断小迷宫中的这个位置之前有没有被走过，$las$ 储存小迷宫这个位置被走过时的坐标。（这样子，如果我们再次搜到小迷宫的这个位置，且当前坐标值与 $las$ 的坐标值不同，就说明我们已经在两个小迷宫中到达这个点了，符合题意，可以输出 `Yes`）

~~最后吐槽一下 CF 的 RMJ 也是非常稳定。~~

```cpp

#include<bits/stdc++.h>
using namespace std;

int n,m;
int sx,sy;
int mp[1505][1505];

bool ok,vis[1505][1505];
pair<int,int> las[1505][1505];

int gox[4] = {0,-1,0,1};
int goy[4] = {-1,0,1,0};

void dfs(int x,int y,int mx,int my)
{
	if(ok)return;
	if(vis[mx][my] && las[mx][my] != make_pair(x,y))
	{
		ok = 1;
		return;
	}
	vis[mx][my] = 1;
	las[mx][my] = make_pair(x,y);
	for(int i = 0;i < 4;i++)
	{
		int xx = x + gox[i],yy = y + goy[i];
		int mxx = (mx + gox[i] + n)%n,myy = (my + goy[i] + m)%m;
		if(mp[mxx][myy])
		{
			if(!vis[mxx][myy] || make_pair(xx,yy) != las[mxx][myy])
				dfs(xx,yy,mxx,myy);
		}
	}
	return;
}

int main()
{
	while(~scanf("%d",&n))
	{
		scanf("%d",&m);
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < m;j++)
			{
				char c;
				scanf(" %c",&c);
				if(c == 'S')
					mp[i][j] = 1,sx = i,sy = j;
				else if(c == '.')mp[i][j] = 1;
				else mp[i][j] = 0;
			}
		}
		ok = 0;
		memset(vis,0,sizeof(vis));
		dfs(sx,sy,sx,sy);
		if(ok)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

如果大家有问题欢迎私信我，谢谢~

---

## 作者：Lotus_Land (赞：0)

我们可以假设地图被复制了无限多块。

从任意一个起点开始 BFS，如果一个点在某一块地图上被走到了，在另一块地图上也被走到了，那么就可以从起点出发到达无限远的地方。

怎么判断呢？设走到了某点坐标为 $(x_1,y_1)$，如果存在整数 $x_2,y_2$ 满足 $x_1\not=x_2$ 或 $y_1\not=y_2$，且 $x_1\bmod n=x_2\bmod n,y_1\bmod m=y_2\bmod m$，那么说明这个点在在两块不同的地图上都被走到了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,stx,sty;
bool mp[1505][1505];
pair<int,int> vis[1505][1505];
bool sg[1505][1505];
string s;
int fx[]= {0,0,1,-1};
int fy[]= {1,-1,0,0};
queue<pair<int,int>>q;
bool BFS() {
	while(!q.empty())q.pop();
	q.push(make_pair(stx,sty));
	vis[stx][sty]=make_pair(stx,sty);
	sg[stx][sty]=1;
	while(!q.empty()) {
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		for(int i=0; i<4; i++) {
			int xx=x+fx[i],yy=y+fy[i];
			if(mp[(xx%n+n)%n][(yy%m+m)%m]) {
				if(!sg[(xx%n+n)%n][(yy%m+m)%m]) {
					sg[(xx%n+n)%n][(yy%m+m)%m]=1;
					vis[(xx%n+n)%n][(yy%m+m)%m]=make_pair(xx,yy);
					q.push(make_pair(xx,yy));
				} else {
					if(vis[(xx%n+n)%n][(yy%m+m)%m]!=make_pair(xx,yy)) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
int main() {
	cin>>n>>m;
	memset(vis,0,sizeof vis);
	memset(sg,0,sizeof sg);
	memset(mp,0,sizeof mp);
	for(int i=0; i<n; i++) {
		cin>>s;
		for(int j=0; j<m; j++) {
			if(s[j]!='#')mp[i][j]=1;
			if(s[j]=='S')stx=i,sty=j;
		}
	}
	if(BFS())printf("Yes\n");
	else printf("No\n");
	return 0;
}

```


---

## 作者：pidan (赞：0)

题意翻译好像没问题吧QwQ。

思路就是标记走过的点，判断是否能从某个点走到另一幅图的这个点。

另一篇题解的dalao给出了很多错误的思路和hack数据，我来水一篇更清晰的题解。

对于一个点，我们用x,y作为它在单个迷宫中的坐标，nx,ny作为它在整个迷宫中的实际坐标。

普通dfs中的vis数组一般记录了某个点是否走过，但在这题中，由于我们不好控制dfs走的方向，有可能走回一个标记的点，而迷宫又是无限的，所以我们把vis加上两个维度标记上次是在整个迷宫的哪个点走到的，如果再次走到该点且当前在整个迷宫的坐标不等于上次来到该点的坐标，就判断能走出迷宫

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int gox[4]={1,-1,0,0},goy[4]={0,0,1,-1};
int n,m,vis[1505][1505][3];
bool flag,a[1505][1505];
void dfs(int x,int y,int nx,int ny){
	if(flag)return;
	if(vis[x][y][0]&&(vis[x][y][1]!=nx||vis[x][y][2]!=ny)){//在小迷宫中走过该点且上次走到该点坐标不同，则以走出迷宫
		flag=1;
		return;
	}
	vis[x][y][0]=1;vis[x][y][1]=nx;vis[x][y][2]=ny;//标记nx和ny
	for(int i=0;i<4;i++){
		int p=(x+gox[i]+n)%n,q=(y+goy[i]+m)%m;//+n和+m保证p,q不为负数
		int np=nx+gox[i],nq=ny+goy[i];
		if(!a[p][q]){
			if(!vis[p][q][0]||vis[p][q][1]!=np||vis[p][q][2]!=nq)//只要没去过或者上次坐标与这次不相等就走
			dfs(p,q,np,nq);
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);//cincout优化
	cin>>n>>m
	flag=0;
	memset(a,0,sizeof(a));
	memset(vis,0,sizeof(vis));
	int stx,sty;char ch;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>ch;
			if(ch=='#')a[i][j]=1;
			if(ch=='S')stx=i,sty=j;
		}
	}
	dfs(stx,sty,stx,sty);
	if(!flag)puts("No");
	else puts("Yes");
	return 0;
}
```

---

## 作者：清小秋ovo (赞：0)

# CF196B 题解

看到各位大佬都是用 dfs 写的，这里给出一个 bfs 的思路。

## 题意

给出一个迷宫和起点，上下左右移动，迷宫周围用相同的地图无限拼接，问能否走到无穷？

首先想到了复制 $9$ 份原图进行求解，但是很明显这样做行不通。

所以转变思路：可以存一下原图里每个位置在别的小拼图里一样的相对位置里出现的，那个小地图里这个点的坐标，如果下一次发现要存的坐标和之前走过的不一样，那说明可以这个位置可以在两个小拼图里走，可以无限行走。

## 代码

常规的广搜，注意一下取模和 `vis`  数组。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1555;
const int INF = 0x3f3f3f3f;
char Map[N][N];
int n, m;
int sx, sy;
int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
struct node
{
    int x, y;
} vis[N][N];
bool bfs(int x, int y)
{
    node now, next;
    now.x = x;
    now.y = y;
    queue<node> q;
    q.push(now);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            int xx = (next.x % n + n) % n;
            int yy = (next.y % m + m) % m;
            if (Map[xx][yy] != '#')
            {
                if (vis[xx][yy].x == INF)
                {
                    vis[xx][yy].x = next.x;
                    vis[xx][yy].y = next.y;
                    q.push(next);
                }
                else if (next.x != vis[xx][yy].x || next.y != vis[xx][yy].y)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(vis, INF, sizeof(vis));
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> Map[i][j];
            if (Map[i][j] == 'S')
                sx = i, sy = j;
        }
    }
    if (bfs(sx, sy))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}

```


---

