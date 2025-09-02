# [ABC246E] Bishop 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc246/tasks/abc246_e

ここに、 $ N\ \times\ N $ のチェス盤があります。このチェス盤の上から $ i $ 行目、左から $ j $ 列目にあるマスをマス $ (i,j) $ と呼びます。  
 チェス盤の情報は $ N $ 個の文字列 $ S_i $ として与えられます。  
 文字列 $ S_i $ の $ j $ 文字目である $ S_{i,j} $ には、以下の情報が含まれています。

- $ S_{i,j}= $ `.` のとき マス $ (i,j) $ には何も置かれていない。
- $ S_{i,j}= $ `#` のとき マス $ (i,j) $ には白のポーンが $ 1 $ つ置かれている。このポーンを動かしたり取り除いたりすることはできない。

この盤面のマス $ (A_x,A_y) $ に、白のビショップを $ 1 $ つ置きました。  
 この白のビショップをチェスのルール (注記参照) に従ってマス $ (A_x,A_y) $ からマス $ (B_x,B_y) $ に移動させるために必要な最小の手数を求めてください。  
 ただし、移動できない場合は代わりに `-1` を出力してください。

## 说明/提示

### 注記

マス $ (i,j) $ に置かれている白の [ビショップ](https://ja.wikipedia.org/wiki/%E3%83%93%E3%82%B7%E3%83%A7%E3%83%83%E3%83%97) は、 $ 1 $ 手で以下のルールに従って移動することができます。

- 各正整数 $ d $ について、以下の条件を全て満たせばマス $ (i+d,j+d) $ に移動できる。
  
  
  - マス $ (i+d,j+d) $ が盤内に存在する
  - 全ての正整数 $ l\ \le\ d $ について、 $ (i+l,j+l) $ に白のポーンがない
- 各正整数 $ d $ について、以下の条件を全て満たせばマス $ (i+d,j-d) $ に移動できる。
  
  
  - マス $ (i+d,j-d) $ が盤内に存在する
  - 全ての正整数 $ l\ \le\ d $ について、 $ (i+l,j-l) $ に白のポーンがない
- 各正整数 $ d $ について、以下の条件を全て満たせばマス $ (i-d,j+d) $ に移動できる。
  
  
  - マス $ (i-d,j+d) $ が盤内に存在する
  - 全ての正整数 $ l\ \le\ d $ について、 $ (i-l,j+l) $ に白のポーンがない
- 各正整数 $ d $ について、以下の条件を全て満たせばマス $ (i-d,j-d) $ に移動できる。
  
  
  - マス $ (i-d,j-d) $ が盤内に存在する
  - 全ての正整数 $ l\ \le\ d $ について、 $ (i-l,j-l) $ に白のポーンがない

### 制約

- $ 2\ \le\ N\ \le\ 1500 $
- $ 1\ \le\ A_x,A_y\ \le\ N $
- $ 1\ \le\ B_x,B_y\ \le\ N $
- $ (A_x,A_y)\ \neq\ (B_x,B_y) $
- $ S_i $ は `.` および `#` からなる $ N $ 文字の文字列
- $ S_{A_x,A_y}= $ `.`
- $ S_{B_x,B_y}= $ `.`

### Sample Explanation 1

以下のように移動させることで $ 3 $ 手でビショップを $ (1,3) $ から $ (3,5) $ まで移動させることができます。 $ 2 $ 手以内でビショップを $ (1,3) $ から $ (3,5) $ まで移動させることはできません。 - $ (1,3)\ \rightarrow\ (2,2)\ \rightarrow\ (4,4)\ \rightarrow\ (3,5) $

### Sample Explanation 2

どのようにビショップを動かしても $ (3,2) $ から $ (4,2) $ に移動させることはできません。

## 样例 #1

### 输入

```
5
1 3
3 5
....#
...#.
.....
.#...
#....```

### 输出

```
3```

## 样例 #2

### 输入

```
4
3 2
4 2
....
....
....
....```

### 输出

```
-1```

## 样例 #3

### 输入

```
18
18 1
1 18
..................
.####.............
.#..#..####.......
.####..#..#..####.
.#..#..###...#....
.#..#..#..#..#....
.......####..#....
.............####.
..................
..................
.####.............
....#..#..#.......
.####..#..#..####.
.#.....####..#....
.####.....#..####.
..........#..#..#.
.............####.
..................```

### 输出

```
9```

# 题解

## 作者：DragonForge (赞：1)

## 题解：AT_abc246_e [ABC246E] Bishop 2
### 题目简述
给定一个 $n \times n$ 的矩阵和一个起点 $\left(sx,sy\right)$ 和一个终点 $\left(ex,ey\right)$，求最短路径长度，若无法到达输出 `-1`。
### 算法讲解
一看到最短路径和矩阵，马上就想到用 `BFS`。观察数据范围可以发现，$1 \le n \le 1500$，更加确定使用广度优先搜索。由于本蒟蒻刚刚学到 `01BFS`，于是趁热打铁使用了它。如果不太了解这一算法的话，可以[__>戳这<__](https://blog.csdn.net/Mr_dimple/article/details/116864052)。我使用了双端队列解决这一问题。

具体代码中，我让同一个双端队同时表示 $4$ 个信息，坐标以及方向和步数。同时用 $d_{i,j,k}$ 表示从不同方向到 $\left(i,j\right)$ 的步数。最后输出四个方向到达终点的最小步数。

#### code
思路已经明确，一些步骤的实现方式都已经在代码的注释里了。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int INF=1e9,MAXN=1510,kd[5][2]={{},{1,1},{1,-1},{-1,1},{-1,-1}};//注意细节：留空一位，只能走斜线

char c[MAXN][MAXN];
int d[MAXN][MAXN][5],n,m,sx,sy,ex,ey,t;
deque<array<int,4>> q;

int main(void){
  //freopen(".in","r",stdin);
  //freopen(".out","w",stdout);
  cin.tie(0)->sync_with_stdio(false);
  cout.tie(0)->sync_with_stdio(false);
  cin>>n>>sx>>sy>>ex>>ey;
  for(int i=1;i<=n;i++){
  	for(int j=1;j<=n;j++){
  		cin>>c[i][j];
		}
	}
	fill(d[0][0],d[n+1][0],INF);
	for(q.push_back({sx,sy,0,0});q.size();){
		auto p=q.front();
		q.pop_front();
		if(c[p[0]][p[1]]=='.'&&d[p[0]][p[1]][p[2]]==INF){
			d[p[0]][p[1]][p[2]]=p[3]; //储存步数
			q.push_front({p[0]+kd[p[2]][0],p[1]+kd[p[2]][1],p[2],p[3]});//加入队列
			for(int i=1;i<=4;i++){
				q.push_back({p[0],p[1],i,p[3]+1});//继续搜索
			}
		}
	}
	int ans=min({d[ex][ey][1],d[ex][ey][2],d[ex][ey][3],d[ex][ey][4]});//步数最少
	cout<<(ans==INF?-1:ans);//是否无解
  return 0;
}
```
#### 完结散花~~

---

## 作者：chengning0909 (赞：1)

# abc 246 e

[AT 链接](https://atcoder.jp/contests/abc246/tasks/abc246_e)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc246_e)

## 题意

有一个 $N \times N$ 的棋盘，$(i, j)$ 表示棋盘第 $i$ 行第 $j$ 列的格子，行编号和列编号都是 $1, 2, \dots, N$。

棋盘用 $N$ 个长度为 $N$ 的字符串 $S_i$ 描述：

- 如果 $S_{i, j} = $ `.`，则格子 $(i, j)$ 是空的。

- 否则，格子 $(i, j)$ 有障碍。

一开始格子 $(A_x, A_y)$ 放了一颗棋子。在每次移动中，棋子可以朝某个对角线（某个斜 45 度方向）行走若干步后停下。棋子不能走出棋盘范围，并且该次移动的路径中不能包含障碍格子。

请你求出棋子从 $(A_x, A_y)$ 走到 $(B_x, B_y)$ 所需的最少移动次数。如果无法移动到 $(B_x, B_y)$，输出 `-1`。

$2 \le N \le 1500$。

$1 \le A_x, A_y, B_x, B_y \le N$。

$(A_x, A_y) \ne (B_x, B_y)$。

## 思路

很明显，这题求最短路，是广搜。

但是，这个移动方式很让人头疼，每次到底挪动几次呢？

如果每次都去枚举移动的步数，时间复杂度又变成了 $O(n ^ 3)$，会超时。

那么，我们应该怎么解决呢？

其实，每次只用走一步，但是，我们每次需要记录是往哪个方向走的。

如果当前走的方向和转移来的那个状态的转移方向是不同的，就需要多一次操作，否则，就还是这次操作。

因为每次转移有可能增加操作次数，有可能不增加，所以是 **0-1 BFS**，用双端队列维护。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1510;

const int dx[] = {1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1};

int n, sx, sy, fx, fy, d[N][N][4];
char c[N][N];

struct Node {
  int x, y, dir;  // dir 表示方向
};

deque<Node> que;

void Record(int x, int y, int dis, int dir, int nowd) {
  if (x < 1 || x > n || y < 1 || y > n || c[x][y] == '#' || d[x][y][nowd] <= dis + (nowd != dir)) {
    return ;
  }
  d[x][y][nowd] = dis;
  if (nowd == dir) {
    que.push_front({x, y, nowd});
  } else {
    d[x][y][nowd]++;
    que.push_back({x, y, nowd});
  }
}

void bfs() {
  for (Record(sx, sy, 0, 4, 4); !que.empty(); ) {
    Node u = que.front();
    que.pop_front();
    for (int i = 0; i < 4; i++) {  // 转移
      Record(u.x + dx[i], u.y + dy[i], d[u.x][u.y][u.dir], u.dir, i);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> sx >> sy >> fx >> fy;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c[i][j];
      d[i][j][0] = d[i][j][1] = d[i][j][2] = d[i][j][3] = 1e9;  // 初始化
    }
  }
  bfs();
  int ans = 1e9;
  for (int i = 0; i < 4; i++) {
    if (d[fx][fy][i] != 1e9) {
      ans = min(ans, d[fx][fy][i]);
    }
  }
  cout << (ans == 1e9 ? -1 : ans);
  return 0;
}
```

---

## 作者：Tsawke (赞：1)

# [ABC246E Bishop 2](https://www.luogu.com.cn/problem/AT_abc246_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC246E)

## 题面

给定有障碍的网格图，`.` 为空地，`#` 为障碍。给定起点终点，每次移动仅可以斜向走任意长度，问从起点到终点的最少移动次数，可能无解，无解输出 `-1`。

## Solution

BFS 较为显然，因为时限 6000ms，只要写的不太丑直接搜也能过。对于本题，使用 01BFS 较为显然。我们在宽搜每次搜一步且距离仅为 $ 1 $，并记录上一步的方向，如果同向则认为走了一个 $ 0 $ 边，异向则为 $ 1 $ 边，开个双端队列，同向插到前面，反之插到后面，按照正常宽搜每次取队头扩展即可。

需要注意对于 01BFS 时，我们判断是否走过和是否为答案的时候，需要在从队头取元素的时候判断，而不是在扩展的时候判断。因为如果在某一次由 $ 1 $ 扩展的时候如果直接把 $ vis $ 设为 $ \texttt{true} $，但是这可能会导致后面从 $ 0 $ 扩展的，本应能插在队列中比这个更前面的更优的无法转移，使答案更劣。同时我们也需要考虑到不同方向的时候扩展也是不同，所以 $ vis $ 中也要考虑到方向这一维。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define CHK(x, y) (x >= 1 && x <= N && y >= 1 && y <= N && !mp[x][y])

template<typename T = int>
inline T read(void);

int N;
int dx[10] = {0,  -1, -1, 1, 1};
int dy[10] = {0,  -1, 1, -1, 1};
int vis[1600][1600][5];
bool mp[1600][1600];

struct Status{
    int x, y;
    int dir;//direction 1, 2, 3, 4
    int dist;
}S, T;
void Init(void){
    char c = getchar();
    for(int i = 1; i <= N; ++i)for(int j = 1; j <= N; ++j){
        while(c != '.' && c != '#')c = getchar();
        mp[i][j] = c == '.' ? false : true;
        c = getchar();
    }
}
void bfs(void){
    deque < Status > dq;
    dq.push_back(S);
    while(!dq.empty()){
        auto tp = dq.front(); dq.pop_front();
        if(vis[tp.x][tp.y][tp.dir])continue;
        vis[tp.x][tp.y][tp.dir] = true;
        if(tp.x == T.x && tp.y == T.y)
            printf("%d\n", tp.dist), exit(0);
        // printf("Current pos (%d, %d): dis = %d, dir = %d\n", tp.x, tp.y, tp.dist, tp.dir);
        for(int i = 1; i <= 4; ++i){
            int tx = tp.x + dx[i], ty = tp.y + dy[i];
            if(!CHK(tx, ty))continue;
            if(i == tp.dir)dq.push_front(Status{tx, ty, i, tp.dist});
            else dq.push_back(Status{tx, ty, i, tp.dist + 1});
        }
    }printf("-1\n");
}

int main(){
    // freopen("test_11.txt", "r", stdin);
    N = read();
    int x = read(), y = read(); S = Status{x, y, 0, 0};
    x = read(), y = read(); T = Status{x, y, 0, 0};
    Init();
    bfs();
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_21 初稿

---

## 作者：Meickol (赞：0)

给出三种做法，均能通过 Atcoder 的测评。

### 做法一：暴力 BFS + 简单剪枝

该做法虽然比较慢，但是可以通过 Atcoder 的测评。

很显然，如果我们沿着斜向移动的路径中存在障碍，那么我们就不可以沿这个斜向移动。

我们每次尝试将移动的距离大小进行扩充即可，也就是说假如我们对沿一个方向扩充时，先尝试扩充一个距离，再尝试扩充两个，如果尝试扩充两个时不行，那么扩充第三个第四个自然也就都不行了，那么就 break 掉。

你可以直接分四个方向进行处理，写四个 for 循环的事。

Atcoder 测评结果：约为 5000ms。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef pair<int,int> PII;
const int N=1.5e3+5;
int n;
int stx,sty,edx,edy;
char g[N][N];
int dist[N][N];
bool st[N][N];
void bfs(){
	queue<PII> q;
	q.push({stx,sty});
	memset(dist,0x3f,sizeof dist);
	dist[stx][sty]=0;
	st[stx][sty]=1;
	while(!q.empty()){
		auto t=q.front();
		q.pop();
		int x=t.first,y=t.second;
		rep(i,1,max(x,n-x)){ //右下
			int xx=x+i,yy=y+i;
			if(xx<1 || xx>n || yy<1 || yy>n) break;
			if(g[xx][yy]=='#') break;
			if(st[xx][yy]) continue;
			st[xx][yy]=1;
			q.push({xx,yy});
			dist[xx][yy]=dist[x][y]+1;
		}
		rep(i,1,max(x,n-x)){ //左下
			int xx=x+i,yy=y-i;
			if(xx<1 || xx>n || yy<1 || yy>n) break;
			if(g[xx][yy]=='#') break;
			if(st[xx][yy]) continue;
			st[xx][yy]=1;
			q.push({xx,yy});
			dist[xx][yy]=dist[x][y]+1;
		}
		rep(i,1,max(x,n-x)){ //左上
			int xx=x-i,yy=y-i;
			if(xx<1 || xx>n || yy<1 || yy>n) break;
			if(g[xx][yy]=='#') break;
			if(st[xx][yy]) continue;
			st[xx][yy]=1;
			q.push({xx,yy});
			dist[xx][yy]=dist[x][y]+1;
		}
		rep(i,1,max(x,n-x)){ //右上
			int xx=x-i,yy=y+i;
			if(xx<1 || xx>n || yy<1 || yy>n) break;
			if(g[xx][yy]=='#') break;
			if(st[xx][yy]) continue;
			st[xx][yy]=1;
			q.push({xx,yy});
			dist[xx][yy]=dist[x][y]+1;
		}
	}
}
void solve(){
	cin>>n;
	cin>>stx>>sty>>edx>>edy;
	rep(i,1,n) rep(j,1,n) cin>>g[i][j];
	bfs();
	if(dist[edx][edy]==0x3f3f3f3f) cout<<-1;
	else cout<<dist[edx][edy];
}
```



### 做法二：双端队列+剪枝

我们发现从一个点出发，如果移动方向是相同的，那么它们消耗的代价是一样的，因为从一个位置向外迈出一步之后再迈出一步就等同于一开始就沿该位置迈出两步，因为一次移动可以从该位置向一个方向迈出任意步距离。

举个例子，对于一个位置 $(x,y)$ 而言，如果 $(x,y)$ 这个位置是通过 $(x_0,y_0)$ 通过沿右下方方向过来的，那么接下来再从 $(x,y)$ 这个位置沿右下方方向到达 $(x_1,y_1)$ 这个位置其实并不需要再消耗代价，即 $(x_1y_1)$ 这个位置代价就等于 $(x,y)$ 这个位置的代价，因为显然 $(x_1,y_1)$ 这个点可以通过 $(x_0,y_0)$ 这个点过来。

而如果移动方向发生了改变，那么显然就需要额外消耗代价，这不难理解。

因此考虑增加一个 “方向” 的维度来存储每个位置沿不同方向移动的代价。

然后双端队列处理一下，判断移动方向是否相同，如果方向相同代价就是 $0$，否则代价就是 $1$。



Atcoder 测评结果：小于 400ms。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
const int N=1.5e3+5;
int n;
int stx,sty,edx,edy;
char g[N][N];
int dist[N][N][4];
bool st[N][N][4];
int dx[4]={-1,-1,1,1},dy[4]={-1,1,1,-1};
int bfs(){
	deque<PIII> q;
	memset(dist,0x3f,sizeof dist);
	rep(i,0,3){
		dist[stx][sty][i]=1;
		q.push_front({{stx,sty},i});
	}
	while(!q.empty()){
		auto t=q.front();
		q.pop_front();
		int x=t.first.first,y=t.first.second,dir=t.second;
		if(x==edx && y==edy) return dist[edx][edy][dir];
		if(st[x][y][dir]) continue;
		st[x][y][dir]=1;
		rep(i,0,3){
			rep(j,1,max(x,n-x)){
				int xx=x+j*dx[i],yy=y+j*dy[i];
				if(xx<1 || xx>n || yy<1 || yy>n) break;
				if(g[xx][yy]=='#') break;
				if(i==dir){
					if(dist[xx][yy][i]<=dist[x][y][i]) break;
					q.push_front({{xx,yy},i});
					dist[xx][yy][i]=dist[x][y][i];
				}
				else{
					if(dist[xx][yy][i]<=dist[x][y][dir]+1) break;
					q.push_back({{xx,yy},i});
					dist[xx][yy][i]=dist[x][y][dir]+1;
				}
			}
		}
	}
	return -1;
}
void solve(){
	cin>>n;
	cin>>stx>>sty>>edx>>edy;
	rep(i,1,n) rep(j,1,n) cin>>g[i][j];
	cout<<bfs();
}
```





### 做法三：BFS + 剪枝

分析一下你就会发现，其实本质就是做法二，只不过将双端队列的处理合并起来写了。

个人不太推荐此写法，推荐学习做法二，因此做法三看看就好。

Atcoder 测评结果：约为 800ms。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef pair<int,int> PII;
const int N=1.5e3+5;
int n;
int stx,sty,edx,edy;
char g[N][N];
int dist[N][N];
bool st[N][N];
int dx[4]={-1,-1,1,1},dy[4]={-1,1,1,-1};
void bfs(){
	queue<PII> q;
	q.push({stx,sty});
	memset(dist,0x3f,sizeof dist);
	dist[stx][sty]=0;
	st[stx][sty]=1;
	while(!q.empty()){
		auto t=q.front();
		q.pop();
		int x=t.first,y=t.second;
		rep(i,0,3){
			rep(j,1,max(x,n-x)){
				int xx=x+j*dx[i],yy=y+j*dy[i];
				if(xx<1 || xx>n || yy<1 || yy>n) break;
				if(g[xx][yy]=='#') break;
				if(dist[xx][yy]<dist[x][y]+1) break;
				q.push({xx,yy});
                dist[xx][yy]=dist[x][y]+1;
			}
		}
	}
}
void solve(){
	cin>>n;
	cin>>stx>>sty>>edx>>edy;
	rep(i,1,n) rep(j,1,n) cin>>g[i][j];
	bfs();
	if(dist[edx][edy]==0x3f3f3f3f) cout<<-1;
	else cout<<dist[edx][edy];
}
```

---

