# [USACO10JAN] Shipping Around an Island G

## 题目描述

Farmer John decided to start his own cruise ship line! He has but one ship, but is hoping for big growth. He recently acquired a map of the area of ocean where his cruise ship will operate. It looks something like the diagram below, with height H (3 <= H <= 1000) and width W (3 <= W <= 1000).

```cpp
................... 
................... 
.....A............. 
.....A..x.......... 
..x..A.....AAAA.... 
.....A.....A..A.... 
.....AAAAAAAA.A.... 
........A.....A.... 
.xx...AAA...x.A.... 
......A............ 
...AAAAAAAAAAAAA... 
................... 
```
In this map, '.' denotes water; 'A' is an element of the main island; and 'x' are other islands.

Farmer John has decided his cruise ship will loop around the main island. However, due to trade restrictions, the path his ship takes is NOT allowed to go around any OTHER islands. For instance, the following path of length 50 is not allowed because it encloses the island denoted by 'x'.

```cpp
................... 
....+--+........... 
....|A.|........... 
....|A.|x.+-----+.. 
..x.|A.+--+AAAA.|.. 
....|A.....A..A.|.. 
....|AAAAAAAA.A.|.. 
....|...A.....A.|.. 
.xx.|.AAA...x.A.|..    <--- route circumnavigates 'x' -- illegal! ..+-+.A.........|.. 
..|AAAAAAAAAAAAA|.. 
..+-------------+.. 
```
Given a map, help Farmer John determine the shortest path his cruise ship can take to go around the main island without going around any other islands.

Two cells are considered connected if they lie vertically or

horizontally across from one another (not diagonally). It is

guaranteed that the main island is connected and that a solution exists.

Note that FJ's path may visit the same square more than once, for instance there are three squares that are visited more than once in FJ's optimal path (of length 62) for the example:

```cpp
................... 
....+--+........... 
....|A.|........... 
....|A.|x.+----+... 
..x.|A.+--+AAAA|... 
....|A.....A..A|... 
....|AAAAAAAA.A|... 
....|...A..+-+A|... 
.xx.|.AAA..|x|A|... 
..+-+.A....+-+-++.. 
..|AAAAAAAAAAAAA|.. 
..+-------------+.. 
```
The above diagram is somewhat unclear because of the path overlapping itself.  Drawn in two stages, FJ's optimal path is:

```cpp
...................            ................... 
...................            ....+--+........... 
.....A.............            ....|A.|........... 
.....A..x..........            ....|A.|x.+----+... 
..x..A.....AAAA....            ..x.|A.+--+AAAA|... 
.....A.....A..A....  and then  ....|A.....A..A|... 
.....AAAAAAAA.A....            ....|AAAAAAAA.A|... 
....V...A..+>.A....            ....V...A...>+A|... 
.xx.|.AAA..|x.A....            .xx...AAA...x|A|... 
..+-+.A....+----+..            .....A.......+-+... 
..|AAAAAAAAAAAAA|..            ...AAAAAAAAAAAAA... 
..+-------------+..            ................... 
```

John 得到一份地图，长 $H$（$3 \leq H\leq 1000$）宽 $W$（$3 \leq W\leq 1000$），地图中 ``.`` 表示水，`A` 表示大陆，`x` 表示其他小岛。他决定驾驶他的船绕大陆一圈，但并不想环绕其他小岛。John 可以再任意有水的格子出发，求绕一周最小路径长度（一个格子可以经过任意多次）。

输入格式：

第一行两个空格隔开正整数 $H$ 和 $W$（$3 \leq H,W\leq 1000$），接下来有 $H$ 行，每行 $W$ 个字符表示地图。

## 样例 #1

### 输入

```
12 19 
................... 
................... 
.....A............. 
.....A..x.......... 
..x..A.....AAAA.... 
.....A.....A..A.... 
.....AAAAAAAA.A.... 
........A.....A.... 
.xx...AAA...x.A.... 
......A............ 
...AAAAAAAAAAAAA... 
................... 
```

### 输出

```
62 
```

# 题解

## 作者：Rigel (赞：21)

## 题意

在一个二维平面上，分布着水（$\texttt{.}$）、大陆（$\texttt{A}$）与小岛（$\texttt{x}$）。现要求一条长度最短的环线路线（起点与终点在同一位置），它应满足：

1. 这条路线经过的每一个格子只能是水（$\texttt{.}$）。

2. 这条环线路线的内部应包括整个大陆（$\texttt{A}$）。

3. 这条环线路线的内部不应包括**任一**小岛（$\texttt{x}$）。

此外，我们规定这条路线可以多次经过同一个格子。也就是说，路线可以重叠。求这条路线的长度，即这条路线经过格子的个数（数据保证有解）。

例如下图，这条红色的路线是不合法的（路线内部包括了一个小岛 $\texttt{x}$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/t50gbpb6.png)

如下图，这条蓝色的路线是合法的（图中深蓝色表示路径重叠部分，阴影部分表示环线路线的内部）。

![](https://cdn.luogu.com.cn/upload/image_hosting/veymid2m.png)

## 思路

### 染色

简而言之，这道题的本质就是染色。

染色在本题中体现为将一些水（$\texttt{.}$）染色成为大陆（$\texttt{A}$）。染色完毕后，只需求出整个大陆的周长即可。于是，如何染色成为了本题的重难点。

对于每一个水格子（$\texttt{.}$）是否应该被染色，我们从以这个格子为中心的 $3\times 3$ 方格来考虑。为简单起见，我们考虑如下图所示定义以水格子 $(i,j)$ 为中心的 $3\times 3$ 方格：

![](https://cdn.luogu.com.cn/upload/image_hosting/83dmb6r6.png)

当 $(i,j)$ 不是水（$\texttt{.}$）时，直接跳过该点；当 $(i,j)$ 是水时，分以下几种情况讨论：

1. 当格子 $2$、$4$、$6$、$8$ 中有**大于等于三个**格子是大陆（$\texttt{A}$）时，直接将 $(i,j)$ 染色为 $\texttt{A}$，因为最短的路不可能走到这里。例如下图，格子 $2$、$4$、$6$ 为 $\texttt{A}$，因此格子 $5$ 也被染成 $\texttt{A}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/zqtb0n8p.png)

2. 当格子 $2$、$4$、$6$、$8$ 中**恰好有两个**格子是大陆（$\texttt{A}$）时，且这两个 $\texttt{A}$ 分别位于格子 $5$ 的两侧，则这个格子**暂时不填**。例如下图，格子 $4$、$6$ 为 $\texttt{A}$。若将格子 $5$ 填上，则格子 $1$、$2$、$3$ 向外延伸的水连通块与格子 $7$、$8$ 向外延伸的水连通块有可能会被互相隔绝。

![](https://cdn.luogu.com.cn/upload/image_hosting/iizlnas6.png)

在下图的情况下，中间的格子是不能被填上的。因为如果填上了，会把里面的 $\texttt{x}$ 与外界隔绝，是不合法的。 

![](https://cdn.luogu.com.cn/upload/image_hosting/9fkvq4mm.png)

在下图的情况下，中间的格子之后会被自下而上地重新搜到而填充上色，因为下面的格子之后会被染色。

![](https://cdn.luogu.com.cn/upload/image_hosting/95kgwtfg.png)

因此，我们在将任一格子填充之后，必须重新判断这个格子周围一圈（八个）格子的情况并讨论其是否需要填充上色。

3. 当格子 $2$、$4$、$6$、$8$ 中**恰好有两个**格子是大陆（$\texttt{A}$）时，且这两个 $\texttt{A}$ 格子的顶点相邻（例如格子 $2$、$4$ 或格子 $4$、$8$），则分以下两种情况讨论：

（1）当格子 $5$ 填上后，会把这个 $3\times 3$ 方格中剩余的水格子分割成独立的两块，则这个点暂时不填，理由同第二种情况。例如下图，顶点相邻的格子 $4$、$8$ 为 $\texttt{A}$，若将格子 $5$ 填上，则可能会把格子 $1$、$2$ 向外延伸的水连通块与格子 $6$、$9$ 向外延伸的水连通块相互隔绝。

![](https://cdn.luogu.com.cn/upload/image_hosting/18x3j6kl.png)

需要注意的是，隔绝水格子的不只是大陆（$\texttt{A}$），也有可能是小岛（$\texttt{x}$）。

（2）当格子 $5$ 填上后，不会把这个 $3\times 3$ 方格中剩余的水格子分割成独立的两块，则这个点直接填上。例如下图，顶点相邻的格子 $4$、$8$ 为 $\texttt{A}$，我们将格子 $5$ 直接填上。

![](https://cdn.luogu.com.cn/upload/image_hosting/408mi8pp.png)

这种类型的格子直接填上的原因是：填上之后只有好处没有坏处。如左下图，填上之后路径长度没有改变；如右下图，填上之后会导致右边两个粉色的格子之后也被填上，最终路径长度缩短。换句话说，填这种类型的格子对路径有**截弯取直**的作用。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ryn5zmp.png)

4. 当格子 $2$、$4$、$6$、$8$ 中只有**小于等于一个**格子是大陆（$\texttt{A}$）时，这个格子**暂时不填**，同理，如有需要之后会重新搜回来。

按这种方式处理完所有格子之后，我们直接求一遍所得大陆的周长即可得出答案。

如下是样例染色前与染色后的对比。

```cpp
................... 
................... 
.....A............. 
.....A..x.......... 
..x..A.....AAAA.... 
.....A.....A..A.... 
.....AAAAAAAA.A.... 
........A.....A.... 
.xx...AAA...x.A.... 
......A............ 
...AAAAAAAAAAAAA... 
................... 
```

```cpp
...................
...................
....AAA............
....AAA.x..........
..x.AAA...AAAAA....
....AAAAAAAAAAA....
....AAAAAAAAAAA....
....AAAAAAA...A....
.xx.AAAAAAA.x.A....
....AAAAAAA........
...AAAAAAAAAAAAA...
...................
```

### 求大陆周长

我们采用常规思路：从第一次出现的大陆（$\texttt{A}$）的**上面一格**为起点开始走出第一步，紧贴大陆顺时针走一圈，并统计走过的格子个数。

假设上一步的方向为向右，则这一步应优先向下，因为我们需要紧贴大陆走一圈；如果无法往下，则应尝试向右；如果还是不行，则应向上（我们规定第一步的上一步方向为**向右**）。

如下图，分别给出了当上一步（红色）为向右时，这一步（蓝色）分别向右、向上、向下时的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/24i085gl.png)

同理，我们可得：若上一步的方向为 $\theta$（其中 $\theta$ 满足该方向所代表的射线绕原点顺时针旋转 $\theta$ 之后恰与 $x$ 轴正半轴重合），则下一步应优先向 $\theta-90\degree$（右转），若不行则向 $\theta$（直行），再不行则向 $\theta+90\degree$（左转），其中角度按模 $360\degree$ 计。

![](https://cdn.luogu.com.cn/upload/image_hosting/2a1ffbn5.png)

按此方法一直走，并记录经过的格子个数，直到走回起点。

## 代码实现 & 完整代码

由于这道题考察的主要是思维，且每个人的代码习惯不一，我会给出我的完整代码和注释，而不是每一步的具体实现方法。

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 1010
using namespace std;
int n,m,ans;
int d[10][2]={{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
int f[5][2]={{0,1},{1,0},{0,-1},{-1,0}};
char c[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
inline char GC(){
	char ch=getchar();
	while(ch!='.'&&ch!='A'&&ch!='x')ch=getchar();
	return ch;
}
bool check(int x,int y){ // 判断一个点是否在地图范围之内
	return (x>=1&&y>=1&&x<=n&&y<=m);
}
void color(int x,int y){ // 染色函数
	if(c[x][y]!='.')return; // 若当前格子不是水，直接跳过
	int cnt_A=0,cnt_x=0; // 统计该格子周围 A 的数量与 x 的数量
	for(int i=0;i<=3;i++){
		int xx=x+f[i][0],yy=y+f[i][1];
		if(!check(xx,yy))continue;
		cnt_A+=(c[xx][yy]=='A');
	}
	for(int i=0;i<=7;i++){
		int xx=x+d[i][0],yy=y+d[i][1];
		if(!check(xx,yy))continue;
		cnt_x+=(c[xx][yy]=='x');
	}
	int chk=0; 
	for(int i=0;i<=3;i++){
		if(c[x+f[i][0]][y+f[i][1]]=='A'&&c[x+f[(i+1)%4][0]][y+f[(i+1)%4][1]]=='A'&&c[x+f[(i+2)%4][0]][y+f[(i+2)%4][1]]=='.'&&c[x+f[(i+3)%4][0]][y+f[(i+3)%4][1]]=='.'){
            // 情况 3.
			chk=i+1;
			break;
		}
	}
	if((chk==1&&c[x-1][y-1]!='.')||(chk==2&&c[x-1][y+1]!='.')||(chk==3&&c[x+1][y+1]!='.')||(chk==4&&c[x+1][y-1]!='.'))chk=0; 
  	// 情况 3.(1)
	if((chk&&(!cnt_x))||cnt_A>=3){ // 情况 1. 或 3.(2)
		c[x][y]='A';
		for(int i=0;i<=7;i++){
			int xx=x+d[i][0],yy=y+d[i][1];
			if(!check(xx,yy))continue;
			color(xx,yy); // 染色之后要重新判断周围格子的情况
		}
	}
    // 情况 2. 与 4. 均不满足染色条件
}
void calc(int x,int y){ // 计算大陆周长
	int nx=x,ny=y,opt=0; // opt 为上一步方向编号
	do{
		for(int i=5;i>=3;i--){ // 按优先级尝试走每一个方向（i 取 5 至 3 是为了避免下标出现负数）
			int xx=nx+f[(opt+i)%4][0],yy=ny+f[(opt+i)%4][1];
			if(c[xx][yy]=='.'){
				nx=xx,ny=yy;
				opt=(opt+i)%4; // 更新方向编号
				break;
			}
		}
		ans++; // 记录经过的格子总数
	}while(!(nx==x&&ny==y));
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=GC();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)color(i,j); // 尝试对每一个格子做染色操作
	int chk=1;
	for(int i=1;i<=n&&chk;i++){
		for(int j=1;j<=m&&chk;j++){
			if(c[i][j]=='A'){
				calc(i-1,j); // 从第一次出现的 A 的上面一格开始计算大陆周长
				chk=0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

本文参考了[题解1](https://www.luogu.com.cn/article/1opr9pxw)和[题解2](https://www.luogu.com.cn/article/yjt8lx5w)。但其年代久远，有些地方没有讲清楚。这篇题解给出了更清楚的解题思路。

---

## 作者：Rigil_Kent (赞：5)

在 $H \times W$ 的地图上，存在水（`.`）、大陆（`A`）与小岛（`x`）。我们需要求一条长度最短的环形路线，使得：

- 路线只能经过水。

- 路线应包裹整个大陆。

- 路线不应包裹任一小岛。

---

我们考虑**填海造陆**。

对于每个格子，考虑以其为中心的 $3\times 3$ 方格。

设当前格子为 $(i,j)$。

- 与 $(i,j)$ 直接相连的 $4$ 个格子中只有 $1$ 个及以下为大陆时， $(i,j)$ 暂时不填。（Case 1）



- 与 $(i,j)$ 直接相连的 $4$ 个格子中有 $2$ 个为大陆时，分两种情况讨论：

  - 填上 $(i,j)$ 后，会将该 $3\times 3$ 方格中的水分成两部分，则 $(i,j)$ 暂时不填。（Case 2.1）

  - 填上 $(i,j)$ 后，不会将该 $3\times 3$ 方格中的水分成两部分，则将 $(i,j)$ 填为大陆。（Case 2.2）

- 与 $(i,j)$ 直接相连的 $4$ 个格子中有 $3$ 个及以上为大陆时，将 $(i,j)$ 填为大陆。（Case 3）


以下是每种情况的举例。

```
// Case 1:
A..
A..
...
```
```
// Case 2.1:
AA.
...
.A.

AA.
A..
A.x
```
```
// Case 2.2:
AA.
A..
A..
```
```
// Case 3:
AA.
A.A
...
```

若将 $(i,j)$ 填为大陆，需重新判断周围 $8$ 个格子的情况。

---

填海造陆后，求大陆周长即可。

由第一次出现的大陆的上面一格开始（令第一步正方向朝右），每一步依次尝试右转、直走、左转，直至走回起点。走过的格子数即为答案。

---

Code。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int d1[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
const int d2[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

int n, m, a[N][N];

int t[5];

int read ()
{
	int ret = 0	, f = 1; char ch = getchar ();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -f;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') ret = (ret << 3) + (ret << 1) + (ch & 15), ch = getchar ();
	return ret * f; 
}

bool chk (int x, int y)
{
	if (x < 1 || y < 1 || x > n || y > m) return 0;
	return 1;
}

void f (int x, int y)
{
	int cnt = 0;
	
	for (int i = 0; i <= 3; i++)
	{
		int now_x = x + d1[i][0], now_y = y + d1[i][1];
		if (chk(now_x, now_y))
		{
			if (a[now_x][now_y] == 'A') t[++cnt] = i;
		}
	}
	
	if (cnt <= 1) return;
	
	if (cnt == 2)
	{
		int id = -1;
		if (t[2] - t[1] == 1) id = t[1];
		if (t[2] - t[1] == 3) id = 3;
		if (id == -1) return;
		if ((id == 0 && a[x + 1][y + 1] != '.')) return;
		if ((id == 1 && a[x - 1][y + 1] != '.')) return;
		if ((id == 2 && a[x - 1][y - 1] != '.')) return;
		if ((id == 3 && a[x + 1][y - 1] != '.')) return;
	}

	a[x][y] = 'A';
	
	for (int i = 0; i <= 7; i++)
	{
		int now_x = x + d2[i][0], now_y = y + d2[i][1];
		if (chk(now_x, now_y)) if (a[now_x][now_y] == '.') f (now_x, now_y);
	}
}

int C (int x, int y)
{
	int ret = 0;
	int now_x = x,now_y = y, lst = 3;
	
	do
	{
		for (int i = -1; i <= 1; i++)
		{
			int now = (lst + i + 4) % 4;
			int _x = now_x + d1[now][0], _y = now_y + d1[now][1];
			if (a[_x][_y] != '.') continue;
			now_x = _x, now_y = _y;
			lst = now;
			break;
		}
		
		ret++;
		
	}while (now_x != x || now_y != y);
	
	return ret;
}

int main ()
{
	n = read(), m = read();
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char ch = getchar();
			while (ch != '.' && ch != 'A' && ch != 'x') ch = getchar();
			a[i][j] = ch;	
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i][j] == '.') f (i, j);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i][j] == 'A')
			{
				printf("%d\n", C (i - 1, j));
				return 0;
			}
		}
	}
}
```

时间复杂度为 $\mathcal{O}(H\times W)$。

---

## 作者：Limit (赞：1)

### 实在看不下去了，楼上的题解是个啥[ID34354的题解](https://www.luogu.org/blog/user34354/solution-p2976)还没有注释....
算了...
盯着看了2个小时，算是看懂了，解释一下吧
顺便给P党一些福音QAQ
~~为了解释方便，变量名几乎没变QAQ~~
```pascal
const z:array[1..4,1..2]of -1..1=((0,1),(1,0),(0,-1),(-1,0));//常量数组
//这个不可以随便定义
{
要→↓←↑的方式定义，不然...
}
var i,j,k,m,n,p,q,x,y,v,o:longint;
    a:array[0..1001,0..1001]of char;
procedure dfs(x,y:longint);//该程序最玄学的部分
var i,c,p,v:longint;
    u:array[1..4]of longint;
begin
  c:=0;
  for i:=1 to 4 do
  if a[x+z[i,1],y+z[i,2]]='A' then//统计出周围的A的个数与方向
  begin
    inc(c);
    u[c]:=i;
  end;
  if(c=2)and
  ((u[1]=1)and(u[2]=3)
  or(u[1]=2)and(u[2]=4)or
  (a[x-z[u[1],1]-z[u[2],1],
     y-z[u[1],2]-z[u[2],2]]<>'.'))then
  exit;
  {（Y为现在查找的位置）
  当出现
 A 
 Y
 A
 或
 AYA
 这种情况则可能是通道，不可以删去
 还有一种情况
   A
  AY
    x
 或
    A
  AY
    A
  这个情况比较特殊，因为不可以从x的外面走，所以Y是通道，不能删去
  }
  if(c>1)then
  begin
    a[x,y]:='A';
    //把当前位置删去
    for i:=1 to 4 do
    begin
      p:=x+z[i,1];
      v:=y+z[i,2];
      if(p>1)and(v>1)and(p<n)and(v<m)and(a[p][v]='.') then
      dfs(p,v);//查找下一个位置
    end;
  end;
end;
function vaild(x,y:longint):boolean;//判断这格可不可以走
begin
  exit((x>0)and(y>0)and(x<n+1)and(y<m+1)and(a[x,y]='.'));
end;
function left(fx:longint):longint;//左转
begin
  if fx=1 then exit(4) else exit(fx-1);
end;
function right(fx:longint):longint;//右转
begin
  if fx=4 then exit(1) else exit(fx+1);
end;
begin
  readln(n,m);
  for i:=1 to n do
  begin
    for j:=1 to m do
    read(a[i,j]);
    readln;
  end;
  for i:=2 to n-1 do
  for j:=2 to m-1 do
  if a[i,j]='.' then
  dfs(i,j);
  {看一下DFS完成后的样例效果
  把没用的.都变成了A
...................
...................
....AAA............
....AAA.x..........
..x.AAA...AAAAA....
....AAAAAAAAAAA....
....AAAAAAAAAAA....
....AAAAAAA...A....
.xx.AAAAAAA.x.A....
....AAAAAAA........
...AAAAAAAAAAAAA...
...................
}
  o:=0;//储存答案
  for i:=1 to n do
  for j:=1 to m do
  if a[i,j]='A' then
  begin
    //可以得出，该最佳路线必然进过最上端的A的上面
    p:=i-1;
    q:=j;
    v:=1;
    repeat//这个可以说是贪心吧...
    {
    为了让改路线尽可能的贴着大陆走
    因为初始方向为→
    所以说要贴着走的话，当可以右转时要右转，不可以则尽可能直走，再不行就只能左转，这样还可以防止直接走回起点(终点)
    就是要绕着这个处理好的岛屿顺时针转一圈
    }
      if(vaild(p+z[right(v),1],q+z[right(v),2]))then//最好右转
      begin
        p:=p+z[right(v),1];
        q:=q+z[right(v),2];
        v:=right(v);
      end
      else
      if(vaild(p+z[v,1],q+z[v,2]))then//尽可能直走
      begin
        p:=p+z[v,1];
        q:=q+z[v,2];
      end
      else
      if(vaild(p+z[left(v),1],q+z[left(v),2]))then//实在不行就左转
      begin
        p:=p+z[left(v),1];
        q:=q+z[left(v),2];
        v:=left(v);
      end;
      inc(o);//每走一步答案+1
    until(p=i-1)and(q=j);//转了一圈就结束了
    write(o);//输出结果
    {(+为走过的路线，F为起点)最后效果就是这样
...................
...+F+++...........
...+AAA+...........
...+AAA+x+++++++...
..x+AAA+++AAAAA+...
...+AAAAAAAAAAA+...
...+AAAAAAAAAAA+...
...+AAAAAAA+++A+...
.xx+AAAAAAA+x+A+...
..++AAAAAAA++++++..
..+AAAAAAAAAAAAA+..
..+++++++++++++++..
    }
    exit;
  end;
end.
```
只能说，有题解是好事，没有解释怎么办呢....QAQ

---

## 作者：zhenglier (赞：0)

~~现在居然出现一道题只有$pascal$题解没有$C++$题解的情况，小蒟蒻要打破它。~~

## 思维题：分类讨论

回归正题，此题十分考验思维，首先我们要考虑如何把不会走的地方给填上，使最后只用求一遍这个图的周长即可。考虑目标点的几种情况：

> $0.$当前点周围有三个$A$或四个$A$时：这个点肯定不会走到，直接用$A$填上。

> $1.$当前点夹在两个点中间，无法判断这个点被填上后是否会让两边出现独立的$x$，所以跳过该点，之后如果某一边被填满，会导致这个点被重新搜到，那时再考虑。

> $2.$当前点被两个相邻的$A$夹在一起，且当前点填上时周围**八格**没有任何$x$，那么直接填上。

> $3.$当前点被两个相邻的$A$夹在一起，且当前点填上时周围**八格**有$x$那么这个点**肯定**会被经过，因为无论往外怎么伸展，最后必须从这里过去以绕开那个$x$。

> $4.$当前点周围有一个$A$或没有$A$，那么这个点先不管，等会也可能再次搜到。

### 复杂度证明：因为每个点只会有一次变成$A$然后向外搜索，所以复杂度为$O(nm)$

对于处理出来的图，我们只用判断每个点会被经过几次就行了：每个点经过的次数等于这个点周围$八格$的连续$A$段数。

最后上神奇的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
int n,m;
char mp[N][N];
void dfs(int x,int y){
    int cnt=0;
    int u[5];
	for(int i=0;i<4;++i){
        int nx=x+dx[i],ny=y+dy[i];
        if(mp[nx][ny]=='A'){
            u[++cnt]=i;
		}
	}
	if(cnt==2){
		if(u[2]-u[1]==2)return;
	    if(mp[x-dx[u[1]]-dx[u[2]]][y-dy[u[1]]-dy[u[2]]]!='.')return;
	}
	if(cnt>1){
	    mp[x][y]='A';
	    for(int i=0;i<4;++i){
	        int nx=x+dx[i],ny=y+dy[i];
	        if(nx>1&&nx<n&&ny>1&&ny<m&&mp[nx][ny]=='.'){
	            dfs(nx,ny);
			}
		}
	}
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        scanf("%s",mp[i]+1);
	}
	for(int i=2;i<n;++i){
	    for(int j=2;j<m;++j){
	        if(mp[i][j]=='.')dfs(i,j);
		}
	}
	int ans=0;
	for(int x=1;x<=n;++x){
	    for(int y=1;y<=m;++y){
			int js=0;
	        if(mp[x][y]=='.'){
	            int u[5],cnt=0;
	            for(int i=0;i<4;++i){
	                int nx=x+dx[i],ny=y+dy[i];
	                if(mp[nx][ny]=='A')u[++cnt]=i;
				}
				if(cnt==1){
				    js=1;
				}else if(cnt==2&&abs(u[2]-u[1])==2){
				    js=2;
				}else if(cnt==2)js=1;
				for(int i=0;i<4;++i){
				    int nx=x+dx[i],ny=y+dy[i];
				    if(mp[nx][ny]!='A'){
				        nx=x+dx[(i+1)%4],ny=y+dy[(i+1)%4];
				        if(mp[nx][ny]!='A'){
				            nx=x+dx[i]+dx[(i+1)%4],ny=y+dy[i]+dy[(i+1)%4];
				            if(mp[nx][ny]=='A'){
				                js++;
							}
						}
					}
				}
				ans+=js;
			}
		}
	}
	cout<<ans<<endl;
}
```



---

