# Nash Matrix

## 题目描述

Nash designed an interesting yet simple board game where a player is simply required to follow instructions written on the cell where the player currently stands.

This board game is played on the $ n\times n $ board. Rows and columns of this board are numbered from $ 1 $ to $ n $ . The cell on the intersection of the $ r $ -th row and $ c $ -th column is denoted by $ (r, c) $ .

Some cells on the board are called blocked zones. On each cell of the board, there is written one of the following $ 5 $ characters — $ U $ , $ D $ , $ L $ , $ R $ or $ X $ — instructions for the player. Suppose that the current cell is $ (r, c) $ . If the character is $ R $ , the player should move to the right cell $ (r, c+1) $ , for $ L $ the player should move to the left cell $ (r, c-1) $ , for $ U $ the player should move to the top cell $ (r-1, c) $ , for $ D $ the player should move to the bottom cell $ (r+1, c) $ . Finally, if the character in the cell is $ X $ , then this cell is the blocked zone. The player should remain in this cell (the game for him isn't very interesting from now on).

It is guaranteed that the characters are written in a way that the player will never have to step outside of the board, no matter at which cell he starts.

As a player starts from a cell, he moves according to the character in the current cell. The player keeps moving until he lands in a blocked zone. It is also possible that the player will keep moving infinitely long.

For every of the $ n^2 $ cells of the board Alice, your friend, wants to know, how will the game go, if the player starts in this cell. For each starting cell of the board, she writes down the cell that the player stops at, or that the player never stops at all. She gives you the information she has written: for each cell $ (r, c) $ she wrote:

- a pair ( $ x $ , $ y $ ), meaning if a player had started at $ (r, c) $ , he would end up at cell ( $ x $ , $ y $ ).
- or a pair ( $ -1 $ , $ -1 $ ), meaning if a player had started at $ (r, c) $ , he would keep moving infinitely long and would never enter the blocked zone.

It might be possible that Alice is trying to fool you and there's no possible grid that satisfies all the constraints Alice gave you. For the given information Alice provided you, you are required to decipher a possible board, or to determine that such a board doesn't exist. If there exist several different boards that satisfy the provided information, you can find any of them.

## 说明/提示

For the sample test 1 :

The given grid in output is a valid one.

- If the player starts at $ (1,1) $ , he doesn't move any further following $ X $ and stops there.
- If the player starts at $ (1,2) $ , he moves to left following $ L $ and stops at $ (1,1) $ .
- If the player starts at $ (2,1) $ , he moves to right following $ R $ and stops at $ (2,2) $ .
- If the player starts at $ (2,2) $ , he doesn't move any further following $ X $ and stops there.

The simulation can be seen below :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/cb2fbba5dfce3a1de517dfe2ea9b356af74a9df6.png)For the sample test 2 :

The given grid in output is a valid one, as a player starting at any cell other than the one at center $ (2,2) $ , keeps moving in an infinitely long cycle and never stops. Had he started at $ (2,2) $ , he wouldn't have moved further following instruction $ X $ .

The simulation can be seen below :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/1eb3dd4d726b75341ce98cd63cef3956c6e3a050.png)

## 样例 #1

### 输入

```
2
1 1 1 1
2 2 2 2```

### 输出

```
VALID
XL
RX```

## 样例 #2

### 输入

```
3
-1 -1 -1 -1 -1 -1
-1 -1 2 2 -1 -1
-1 -1 -1 -1 -1 -1```

### 输出

```
VALID
RRD
UXD
ULL```

# 题解

## 作者：little_sun (赞：3)

### 题目大意

有一个$n \times n$大小的棋盘，棋盘的每个格子上有一个字母（是`U,L,R,D,X`中之一），其中`U`表示向上走，`D`表示向下走，`L`表示向左走，`R`表示向右走，`X`表示走到这个格子就停止。

现在给你$n ^ 2$个坐标$(x_{i,j}, y_{i, j})$表示从$(i, j)$出发能走到的位置（如果无限循环则为$-1$），你需要构造出这个棋盘，或者输出`INVALID`，$n \leq 10^3$ 

### 分析

容易发现一个性质：所有终点相同的点形成独立的联通块

证明很显然，如果$A$的终点是$(x_1, y_1)$，$B$的终点是$(x_2,y_2)$($(x_1,y_1) \not= (x_2, y_2)$)，且$A$有边连到$B$的话，那么$A$的终点就不可能是$(x_1, y_1)$，而会是$(x_2,y_2)$与题设矛盾。

那么问题就好解决了

我们首先忽略掉死循环的情况，对于一个（非死循环）联通块，我们可以从这个联通块的终点（即$(i,j)=(x_{i,j},y_{i,j})$的点）向外开始$\texttt{DFS}$，遍历所有与他相邻的点并记录答案。

而对于死循环的情况，显然如果单独的一个点死循环的话肯定是不可能的，这时候输出`INVALID`即可

否则我们枚举两个相邻的点作为起点，把这两个点连成双元环，然后分别从这两个点开始$\texttt{DFS}$，遍历所有在不经过其中一个点的情况下能走到的所有点并记录答案（详情参见代码）

最后，如果有某一个点没有被遍历到的话则输出`INVALID`，否则就输出`VALID`并输出前文处理出的答案

### 代码

``` cpp
#include <bits/stdc++.h>
 
#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define check(x, y) ((x > 0) && (x <= n) && (y > 0) && (y <= n))
 
const int MaxN = 1e3 + 10;
const char op[] = {'U', 'L', 'D', 'R', 'X'};
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
 
int n, vis[MaxN][MaxN];
char ans[MaxN][MaxN];
std::vector<std::pair<int, int>> v;
std::pair<int, int> a[MaxN][MaxN];
 
int nxt(int x, int y, int ex, int ey)
{
    for (int i = 0; i <= 3; i++)
        if (x + dx[i] == ex && y + dy[i] == ey)
            return i;
    return -1;
}
 
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? x : (-x);
}
 
void dfs(int x, int y, int Dx) // 正常联通块求解
{
    if (ans[x][y]) return;
    ans[x][y] = op[Dx];
    for (int i = 0; i <= 3; i++)
    {
        int ex = x + dx[i], ey = y + dy[i];
        if (check(ex, ey) && a[ex][ey] == a[x][y])
            dfs(ex, ey, i);
    }
}
 
void get(int x, int y) // 求死循环联通块大小
{
    vis[x][y] = 1, v.push_back(std::make_pair(x, y));
    for (int i = 0; i <= 3; i++)
    {
        int ex = x + dx[i], ey = y + dy[i];
        if (check(ex, ey) && a[ex][ey].first == -1 && a[ex][ey].second == -1 && !vis[ex][ey])
            get(ex, ey);
    }
}
 
void Dfs(int x, int y, int banx, int bany, int Dx) // 死循环联通块遍历
{
    if (ans[x][y]) return;
    ans[x][y] = op[Dx];
    for (int i = 0; i <= 3; i++)
    {
        int ex = x + dx[i], ey = y + dy[i];
        if (check(ex, ey) && (a[ex][ey].first == -1 && a[ex][ey].second == -1) && (ex != banx || ey != bany))
            Dfs(ex, ey, banx, bany, i);
    }
}
 
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            a[i][j].first = read(), a[i][j].second = read();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j].first == i && a[i][j].second == j)
                dfs(i, j, 4);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j].first == -1 && a[i][j].second == -1 && !vis[i][j])
            {
                v.clear(), get(i, j);
                if (v.size() == 1) return 0 * printf("INVALID");
                for (int k = 1; k < v.size(); k++)
                {
                    int x = nxt(v[k - 1].first, v[k - 1].second, v[k].first, v[k].second);
                    if (~x)
                    {
                        Dfs(v[k].first, v[k].second, v[k - 1].first, v[k - 1].second, x);
                        x = nxt(v[k].first, v[k].second, v[k - 1].first, v[k - 1].second);
                        Dfs(v[k - 1].first, v[k - 1].second, v[k].first, v[k].second, x);
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!ans[i][j])
                return 0 * printf("INVALID");
    puts("VALID");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            putchar(ans[i][j]);
        puts("");
    }
    return 0; 
}
```



---

## 作者：syksykCCC (赞：1)

分两个部分，第一部分处理会终止的结点，第二部分处理不会终止的结点

试想，对于一个 $(i, j)$，停止于 $(ex_{(i, j)}, ey_{(i, j)})$，那么，我们先随便拉出来一条路径，一定会知道，**路径上的每一个点都会停止于 $ {(ex_{(i, j)}, ey_{(i, j)})}$**，所以，这张图一定是若干个连通块，某一个连通块内，点的停止点应该是相同的。

我们找到所有的自停止点，也就是 $(i, j) = (ex_{(i, j)}, ey_{(i, j)})$，显然这个点应当是 `X`，然后我们从它开始，在满足停止点是它的连通块内构造答案。这很简单，只要我们 DFS 一遍，把访问到一个点的方向都反过来就行了。

```cpp
void DFS(int p, int q, int sx, int sy) // 当前在 (p, q)，处理所有停止点是 (sx, sy) 的
{
	REP(i, 0, 3) // 枚举方向，dx[], dy[] 是增量数组
	{
		int tx = p + dx[i], ty = q + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= n && // 不越界
		  ex[tx][ty] == sx && ey[tx][ty] == sy && !ans[tx][ty]) // 终止点是 (sx, sy) && 没访问
		{
			ans[tx][ty] = dc[i]; // dc[] 存的是反方向
			DFS(tx, ty, sx, sy);
		}
	}
}
```

然后是 $-1$ 的情况。如果一个 $-1$ 连通块的大小为 $1$，那么结果肯定是 `INVALID`，因为一个点怎么也没法做到不停止。否则，我们选择这个连通块内相邻的两个点，把它们指向对方，然后让其他 $-1$ 都走到这两个点上面来，这个连通块就合法了。

这需要再写一种 DFS 吗？答案是否定的，我们把上面 DFS 的参数 $(sx ,s y)\gets (-1, -1)$，就是自动在找 $-1$ 连通块了。

别忘了构造题的惯常套路：构造完后再检验一遍。

```cpp
#include <bits/stdc++.h>
#define REP(i, x, y) for(register int i = x; i <= y; i++)
using namespace std;
const int N = 1e3 + 5;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
const char dc[4] = {'L', 'U', 'R', 'D'};
int n, ex[N][N], ey[N][N];
char ans[N][N];
void DFS(int p, int q, int sx, int sy)
{
	REP(i, 0, 3)
	{
		int tx = p + dx[i], ty = q + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= n &&
		  ex[tx][ty] == sx && ey[tx][ty] == sy && !ans[tx][ty])
		{
			ans[tx][ty] = dc[i];
			DFS(tx, ty, sx, sy);
		}
	}
}
int main()
{
	scanf("%d", &n);
	REP(i, 1, n) REP(j, 1, n) scanf("%d %d", &ex[i][j], &ey[i][j]);
	REP(i, 1, n) REP(j, 1, n)
		if(ex[i][j] == i && ey[i][j] == j)
			ans[i][j] = 'X', DFS(i, j, i, j); 
	REP(i, 1, n) REP(j, 1, n)
	{
		if(ex[i][j] == -1 && !ans[i][j])
		{
			// 注意，这里两种情况即可，因为 ...-1 的情况在 i=i-1 / j=j-1 的时候枚举到了 
			if(ex[i + 1][j] == -1) 
				ans[i][j] = 'D', ans[i + 1][j] = 'U', DFS(i, j, -1, -1), DFS(i + 1, j, -1, -1);
			if(ex[i][j + 1] == -1) 
				ans[i][j] = 'R', ans[i][j + 1] = 'L', DFS(i, j, -1, -1), DFS(i, j + 1, -1, -1);
		}
	}
	bool invalid = false;
	REP(i, 1, n) REP(j, 1, n) invalid |= !ans[i][j];
	if(invalid) return puts("INVALID") && 0;
	puts("VALID");
	REP(i, 1, n)
	{
		REP(j, 1, n) putchar(ans[i][j]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Andrewzdm (赞：1)

# [CF1316D Nash Matrix](https://www.luogu.com.cn/problem/CF1316D)
其实我们可以把所有的点分成两类：停不下来的和会停下来的。

我们优先解决会停下来的点。

### Case 1:
首先，如果一个点 $(i,j)$ 的终点为  $(i,j)$ ，那么毫无疑问，这个点肯定会被标记成 $X$ 。

然后我们从这个点出发dfs（当然bfs也可以），找到所有终点同样是 $(i,j)$ 的点，然后在路径上标记对应的字符。这样我们就把所有终点是同一点的格点连接在了一起。

所有停下来的点就解决了。
### Case 2:
接下来我们来解决不会停下来的点。

如果从一个点出发不会停下来，那么只有两种情况：
1. 这个点在一个环内；
2. 这个点有一条路径到达一个环。

而建立环的最简单的办法就是让两个点互相可达。

所以我们把所有能配对的相邻的两个点配对，再把剩下的点尽可能往其中一个环上添加路径。
解决！
### How to judge the result?
如果在建环配对时有一个点不能配对，那么结果就是`INVALID`；

如果有任何一个格点上没有标记路径，那么结果就是`INVALID`；

反之结果就是`VALID`。
## Code
附上AC代码：
```cpp
#include<cstdio> 
const int maxn = 1005;
int n;
char matrix[maxn][maxn];
int x[maxn][maxn], y[maxn][maxn];

void dfs(int p, int q, char c)
{
	if(matrix[p][q] != '\0')
		return;
	matrix[p][q] = c;
	if(x[p - 1][q] == x[p][q] && y[p - 1][q] == y[p][q])//up
		dfs(p - 1, q, 'D');
	if(x[p + 1][q] == x[p][q] && y[p + 1][q] == y[p][q])//down
		dfs(p + 1, q, 'U');
	if(x[p][q - 1] == x[p][q] && y[p][q - 1] == y[p][q])//left
		dfs(p, q - 1, 'R');
	if(x[p][q + 1] == x[p][q] && y[p][q + 1] == y[p][q])//right
		dfs(p, q + 1, 'L');
}

bool connect(int p,int q,int r,int s,char c1,char c2)
{
	if(x[r][s] == -1 && y[r][s] == -1)
	{
		matrix[p][q] = c1;
		if(matrix[r][s] == '\0')
			matrix[r][s] = c2;
		return true;
	}
	else
		return false;
}

int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d%d",&x[i][j],&y[i][j]);
	//Case 1
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(x[i][j] == i && y[i][j] == j)
				dfs(i, j, 'X');
	//Case 2
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(x[i][j] == -1 && y[i][j] == -1)
			{
				bool flag = (matrix[i][j] != '\0');
				if(!flag)//from left to right
					flag = connect(i,j,i,j+1,'R','L');
				if(!flag)//from right to left
					flag = connect(i,j,i,j-1,'L','R');
				if(!flag)//from down to up
					flag = connect(i,j,i-1,j,'U','D');
				if(!flag)//from up to down
					flag = connect(i,j,i+1,j,'D','U');
				if(!flag)
				{
					printf("INVALID\n");
					return 0;
				}
			}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(matrix[i][j] == '\0')
			{
				printf("INVALID\n");
				return 0;
			}
	printf("VALID\n");
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			printf("%c",matrix[i][j]);
		printf("\n");
	}
	return 0;
}
```
时间复杂度 $O(n^2)$ 

---

## 作者：流绪 (赞：0)

dfs+ 构造！

有两种路需要我们来找。

⑴非循环的路，这显然是一条单向的路，很显然我们可以用 dfs 来做。我的做法是找到终点，赋上 X，然后反推回去。

⑵循环的路，这里我是直接构造，好像可以搜素写？但是我没调出来。构造的话，我们先找到一个循环里的点，然后从他四个方向里随便找一个也是循环里的点。如果第二个点还未构造，那么我们让这两个点互相走向对方，这样就循环了。如果第二个点已经构造，那么我们让这个点走向第一个点，那么这个点就会走向一个循环，符合题意。

做完上面两步后,遍历整个图看看有没有还没赋值的点,有的话就不存在这样的图,没有的话就是存在,输出即可。

我觉得比较难的是存图，试了几种方法，最后是二维结构体成功了。结构体下标存图的位置，结构体里面的变量存他要去的地方。

下面是 AC 代码,细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
#define db() cout << 1 << endl
using namespace std;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
char dz[]="LRUD";//dfs时反推的方向
char dzz[]="RLDU";//构造时正推的方向
char ans[1010][1010];//答案数组
struct node 
{
	int x,y;
	bool operator ==(node b)//重定义相等的符号
	{
		return (x==b.x&&y==b.y);
	}
}a[1010][1010];
int n;
void dfs(int x,int y)//从终点反推
{
	for(int i=0;i<4;i++)
	{
		int b=x+dx[i];
		int c=y+dy[i];//走到下一个
		if(b<1||b>n||c<1||c>n||ans[b][c])
			continue;//越界或已经找过
		if(a[b][c]==a[x][y])//如果下个位置要去的地方是现在的位置
			ans[b][c] = dz[i],dfs(b,c);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	int p = 0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin >> a[i][j].x >> a[i][j].y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j].x==i&&a[i][j].y==j)
			{//如果一个点的终点是自己,那么他就是非循环路的终点
				ans[i][j]='X';
				dfs(i,j);
			}		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)//枚举每一个点
			if(a[i][j].x==-1&&!ans[i][j])//如果是循环的点且未赋值
				for(int k=0;k<4;k++)
				{
					int b=i+dx[k];
					int c=j+dy[k];//走到下一个点
					if(b<1||b>n||c<1||c>n)
						continue;//越界
					if(a[b][c].x==-1)//找到了第二个循环的点
					{			
					//	cout << b << " "<< c << " " <<k<<endl;
						if(!ans[b][c])//第二个点未赋值
							ans[i][j] = dzz[k],ans[b][c] = dz[k];
						else//已赋值
							ans[i][j] = dzz[k];
						break;//找到一个即可,退出
					}		
				}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!ans[i][j])
			{
				cout << "INVALID";
				return 0;
			}//遍历看看有没有未赋值的点
	cout << "VALID\n";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout << ans[i][j];
		cout << endl;
	}
  	return 0;
}
```


---

