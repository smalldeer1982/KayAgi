# Infinite Chess

## 题目描述

The black king lives on a chess board with an infinite number of columns (files) and $ 8 $ rows (ranks). The columns are numbered with all integer numbers (including negative). The rows are numbered from $ 1 $ to $ 8 $ .

Initially, the black king is located on the starting square $ (x_s, y_s) $ , and he needs to reach some target square $ (x_t, y_t) $ . Unfortunately, there are also white pieces on the board, and they threaten the black king. After negotiations, the white pieces agreed to let the black king pass to the target square on the following conditions:

- each turn, the black king makes a move according to the movement rules;
- the black king cannot move to a square occupied by a white piece;
- the black king cannot move to a square which is under attack by any white piece. A square is under attack if a white piece can reach it in one move according to the movement rules;
- the white pieces never move.

Help the black king find the minimum number of moves needed to reach the target square while not violating the conditions. The black king cannot leave the board at any time.

The black king moves according to the movement rules below. Even though the white pieces never move, squares which they can reach in one move are considered to be under attack, so the black king cannot move into those squares.

Below are the movement rules. Note that the pieces (except for the knight) cannot jump over other pieces.

- a king moves exactly one square horizontally, vertically, or diagonally.
- a rook moves any number of vacant squares horizontally or vertically.
- a bishop moves any number of vacant squares diagonally.
- a queen moves any number of vacant squares horizontally, vertically, or diagonally.
- a knight moves to one of the nearest squares not on the same rank, file, or diagonal (this can be thought of as moving two squares horizontally then one square vertically, or moving one square horizontally then two squares vertically — i. e. in an "L" pattern). Knights are not blocked by other pieces, they can simply jump over them.

There are no pawns on the board.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1765I/ba9906dc29bd550b495cfec3cf65ba1929dd7c80.png)  King and knight possible moves, respectively. Dotted line shows that knight can jump over other pieces.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1765I/91042dc46fb92993448c908bdcb51af585b72aab.png)  Queen, bishop, and rook possible moves, respectively.

## 说明/提示

The image below demonstrates the solution for the second example. Here, the letters K, R, s, and t represent the white king, the white rook, the starting square, and the target square, respectively. Bold crosses mark the squares which are under attack by the white pieces. Bold dots show the shortest path for the black king.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1765I/3f349963b3ee29e9f77a6724908f8fe3d314c2f8.png)

## 样例 #1

### 输入

```
1 8
7 8
2
N 4 8
B 4 6```

### 输出

```
10```

## 样例 #2

### 输入

```
1 1
1 5
2
K 1 3
R 2 3```

### 输出

```
6```

## 样例 #3

### 输入

```
2 2
6 4
1
Q 4 3```

### 输出

```
-1```

# 题解

## 作者：elbissoPtImaerD (赞：3)

考虑暴力：直接 BFS。

优化？考虑到 $y$ 轴长度很小，根据棋子的移动规则，每个棋子能影响的 $x$ 轴范围也较小。

使用离散化将相同状态的列（即平行于 $y$ 轴的直线）压一起来跑最短路即可。

有一点细节。

```cpp
const int inf=1<<30;
il void Solve()
{
  pii S,T;rd(S.x),rd(S.y),rd(T.x),rd(T.y),--S.y,--T.y;
  int n;rd(n);
  ve<int>lsh{S.x,T.x};
  ve<array<int,3>>o(n);
  for(auto&[_,x,y]:o) {
    char s;rd(s),rd(x),rd(y),--y;
    int L;
    if(s=='K') _=0,L=2;
    if(s=='Q') _=1,L=max(y,7-y)+1;
    if(s=='R') _=2,L=1;
    if(s=='B') _=3,L=max(y,7-y)+1;
    if(s=='N') _=4,L=3;
    for(int i=x-L;i<=x+L;++i) lsh.pb(i);
  }
  sort(all(lsh)),lsh.erase(unique(all(lsh)),end(lsh));
  auto F=[&](int x){return lower_bound(all(lsh),x)-begin(lsh);};
  S.x=F(S.x),T.x=F(T.x);
  int m=lsh.size();
  ve<array<int,8>>can(m);
  auto chk=[&](int x,int y){return 0<=x&&x<m&&0<=y&&y<8;};
  const pii dr[]={{-1,-1},{-1,1},{1,-1},{1,1}},dl[]={{0,1},{0,-1},{-1,0},{1,0}};
  ve<array<int,8>>est(m);
  for(auto&[_,x,y]:o) x=F(x),est[x][y]=can[x][y]=1;
  auto Kira=[&](int x,int y,int dx,int dy,int L)
  {
    for(int k=0,X,Y;k<L;++k) {
      X=x+dx,Y=y+dy;
      if(!chk(X,Y)||est[X][Y]) break;
      can[X][Y]=1,x=X,y=Y;
    }
    return;
  };
  for(auto&[_,x,y]:o) {
    if(!_||_==1||_==2) for(auto[dx,dy]:dl) Kira(x,y,dx,dy,_?inf:1);
    if(!_||_==1||_==3) for(auto[dx,dy]:dr) Kira(x,y,dx,dy,_?inf:1);
    if(_==4) for(auto[dx,dy]:(pii[]){{-2,1},{-1,2},{2,1},{1,2},{1,-2},{2,-1},{-2,-1},{-1,-2}}) Kira(x,y,dx,dy,1);
  }
  ve<ve<int>>dis(m,ve<int>(8,inf));
  using Info=array<int,3>;
  priority_queue<Info,ve<Info>,greater<>>hp;
  hp.ep(Info{dis[S.x][S.y]=0,S.x,S.y});
  for(;hp.size();) {
    auto[_,ux,uy]=hp.top();
    hp.pop();
    if(pii(ux,uy)==T) return cout<<_,void();
    if(_>dis[ux][uy]) continue;
    auto kira=[&](int vx,int vy,int dy)
    {
      if(chk(vx,vy)&&!can[vx][vy]&&cn(dis[vx][vy],_+max(abs(lsh[ux]-lsh[vx]),abs(dy)))) {
        hp.ep(Info{dis[vx][vy],vx,vy});
      }
    };
    for(auto[dx,dy]:dl) kira(ux+dx,uy+dy,dy);
    for(auto[dx,dy]:dr) {
      int vx=ux+dx;
      if(chk(vx,0)) for(int L=1;L<=abs(lsh[ux]-lsh[vx]);++L) {
        int vy=uy+dy*L;
        if(chk(vx,vy)&&!can[vx][vy]) kira(vx,vy,dy*L);
        else break;
      }
    }
  }
  cout<<-1;
  return;
}
```

---

## 作者：kimi0705 (赞：2)

本文部分参考官方题解。

点数: *2800

### 我会暴力
我们可以将字段限制为有限列。取最左边的位置和最右边的位置，每边再留出 $8$ 个单元格。显然 TLE/MLE。

### 我会离散化

注意到如果两列编号为 $i,j(i<j)$，并且 $j-i\ge20,[i+1,j-1]$ 区间都是**空的**，那么删除 $[i+9,j-9]$ 对答案的有无**没有区别**，删除之后只需将 $i+8$ 至 $j-8$ 这两列的距离设为 $j-i-16$，就可以删除无用的列了。所以考虑将有用的点**离散化**。
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline") // 编译优化。
using namespace std;

const int M = 2005; // 最大列数。
const int N = M * 40; // 离散化后的最大列数。
const int dx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 }; // 马移动的x方向数组。
const int dy[8] = { -1, 1, -2, 2, -2, 2, -1, 1 }; // 马移动的y方向数组。

int n, sx, sy, ex, ey; // 棋盘的行数、起始点和终止点的坐标。
int cnt, c[N]; // 离散化用的数组和计数器。
int x[N], y[N]; char z[N]; // 棋子的位置和类型
bool ban[N][10], cover[N][10]; // ban表示禁止的格子，cover表示被占据的格子
int dis[N][10]; // 用于Dijkstra算法的距离数组。

struct node {
	int x, y, dist; // 节点的坐标和距离。
	bool operator < (const node &x) const {return dist > x.dist; } // 优先队列的比较函数，距离小的优先。
};

priority_queue<node> qu; // 优先队列用于Dijkstra算法

// 插入函数，用于在列数的两边插入多个值进行离散化处理。
void insert(int x) { 
	for (int i = -18; i <= 18; i++) cnt++, c[cnt] = x + i; 
}

// 获取x在离散化后的数组中的位置。
int GET(int x) { 
	return lower_bound(c + 1, c + cnt + 1, x) - c; 
}

// 更新x的离散化位置。
void update(int& x) { 
	x = GET(x); 
}

// 判断坐标是否在合法范围内
bool judge(int x, int y) { 
	return 1 <= x && x <= cnt && 1 <= y && y <= 8; 
}

// 将坐标(x, y)加入队列。
void add(int x, int y, int d) {
	if (judge(x, y) && ban[x][y] == 0 && dis[x][y] > d) 
		dis[x][y] = d, qu.push((node){x, y, d});
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> sx >> sy >> ex >> ey >> n; // 输入起点、终点和白棋数量。
	insert(sx), insert(ex); // 插入起点和终点的列数。
	for (int i = 1; i <= n; i++) 
		cin >> z[i] >> x[i] >> y[i], insert(x[i]); // 插入白棋的位置。
	sort(c + 1, c + cnt + 1);
	cnt = unique(c + 1, c + cnt + 1) - (c + 1); // 离散化。
	update(sx);
	update(ex);
	for (int i = 1; i <= n; i++) 
		update(x[i]);
	for (int i = 1; i <= n; i++) 
		cover[x[i]][y[i]] = 1; // 标记被占据的格子。
	for (int i = 1; i <= n; i++) 
		ban[x[i]][y[i]] = 1; // 标记禁止的格子。
	for (int i = 1; i <= n; i++) {
		// 根据棋子的类型标记被攻击的格子。
		if (z[i] == 'K')
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++) {
					int nx = x[i] + dx, ny = y[i] + dy;
					if (judge(nx, ny)) ban[nx][ny] = true;
				}
		if (z[i] == 'Q')
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
					for (int mutli = 1;; mutli++) {
						if (!judge(x[i] + mutli * dx, y[i] + mutli * dy) || cover[x[i] + mutli * dx][y[i] + mutli * dy]) {break;}
						else {ban[x[i] + mutli * dx][y[i] + mutli * dy] = true;}
					}
		if (z[i] == 'R') {
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] + mutli, y[i]) || cover[x[i] + mutli][y[i]])
					break;
				else
					ban[x[i] + mutli][y[i]] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] - mutli, y[i]) || cover[x[i] - mutli][y[i]])
					break;
				else
					ban[x[i] - mutli][y[i]] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i], y[i] + mutli) || cover[x[i]][y[i] + mutli])
					break;
				else
					ban[x[i]][y[i] + mutli] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i], y[i] - mutli) || cover[x[i]][y[i] - mutli])
					break;
				else
					ban[x[i]][y[i] - mutli] = true;
		}
		if (z[i] == 'B') {
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] + mutli, y[i] + mutli) || cover[x[i] + mutli][y[i] + mutli])
					break;
				else
					ban[x[i] + mutli][y[i] + mutli] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] - mutli, y[i] + mutli) || cover[x[i] - mutli][y[i] + mutli])
					break;
				else
					ban[x[i] - mutli][y[i] + mutli] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] + mutli, y[i] - mutli) || cover[x[i] + mutli][y[i] - mutli])
					break;
				else
					ban[x[i] + mutli][y[i] - mutli] = true;
			for (int mutli = 1;; mutli++)
				if (!judge(x[i] - mutli, y[i] - mutli) || cover[x[i] - mutli][y[i] - mutli])
					break;
				else
					ban[x[i] - mutli][y[i] - mutli] = true;
		}
		if (z[i] == 'N')  
			for (int j = 0; j < 8; j++) 
				if (judge(x[i] + dx[j], y[i] + dy[j])) ban[x[i] + dx[j]][y[i] + dy[j]] = true;
	}

	// 初始化距离数组
	for (int i = 0; i <= cnt + 1; i++) 
		for (int j = 0; j <= 9; j++) 
			dis[i][j] = 1e9;
	dis[sx][sy] = 0, ban[ex][ey] = 0;
	qu.push((node){sx, sy, 0});

	// Dijkstra算法
	while (qu.size()) {
		node top = qu.top(); qu.pop();
		int nx = top.x, ny = top.y, dist = top.dist;
		if (dis[nx][ny] ^ dist) continue;
		if (nx == ex && ny == ey) 
			return cout << dis[nx][ny] << '\n', 0;
		add(nx, ny - 1, dist + 1);
	    add(nx, ny + 1, dist + 1);
	    add(nx - 1, ny, dist + c[nx] - c[nx - 1]); 
	    add(nx + 1, ny, dist + c[nx + 1] - c[nx]); // 上下左右
	    if(c[nx] - c[nx - 1] == 1) {
	        add(nx - 1, ny - 1, dist + 1);
	        add(nx - 1, ny + 1, dist + 1);
	    }
	    if(c[nx + 1] - c[nx] == 1) {
	        add(nx + 1, ny - 1, dist + 1);
	        add(nx + 1, ny + 1, dist + 1);
	    }
    }
    return puts("-1"), 0;
}
```
~~都做 *2800 的紫题了，应该不会有人抄题解吧。~~

---

## 作者：Alex_Wei (赞：2)

直接 BFS，复杂度高达 $8\times 10 ^ 8$，无法接受。

注意到行数很少，这样斜向攻击只会影响到半径为 $8$ 的列邻域。而对于横向攻击，我们可以把一段每行被攻击状态相同的列缩成一列，相当于离散化。注意国王可以斜向走，所以两侧还要保留 $8$ 列。

离散化后模拟得到每个格子是否被攻击，跑最短路即可。时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1765/submission/185486952)。

---

## 作者：Jerrywang09 (赞：0)

不是很难的冷门题。

首先，看到横坐标无限，考虑离散化，但是由于一些预处理的需要，在离散化时要再往左右各延申 $10$ 个单位长度。

对于每个白棋子，预处理出其可以攻击到的地方，然后考虑求答案。由于离散化导致一步可以跨过很远的距离，因此要用 Dijsktra 算法。

不知道此题是如何做到 CF 评分 $2800$ 的。

```cpp
// Title:  Infinite Chess
// Source: CF1765I
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010, M=10; ll inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int dx[]={-2, -2, -1, -1, 1, 1, 2, 2};
int dy[]={-1, 1, -2, 2, -2, 2, -1, 1};
int sx, sy, tx, ty, n;
struct node
{
    char c; int x, y;
} a[N];
int b[N], nn; bool have[N][M], ban[N][M];
bool inrange(int x, int y)
{
    return 1<=x && x<=nn && 1<=y && y<=8;
}
void insert(int x)
{
    rep(xx, x-10, x+10) b[++nn]=xx;
}
struct qnode
{
    ll d; int x, y;
    bool operator <(qnode t) const {return d>t.d;}
}; priority_queue<qnode> q;
ll d[N][M]; bool vis[N][M];
void upd(int nx, int ny, ll val)
{
    if(!inrange(nx, ny) || ban[nx][ny]) return;
    if(val<d[nx][ny]) d[nx][ny]=val, q.push({val, nx, ny});
}
void dij()
{
    memset(d, 0x3f, sizeof d);
    q.push({0, sx, sy}); d[sx][sy]=0;
    while(q.size())
    {
        int x=q.top().x, y=q.top().y; q.pop();
        if(vis[x][y]) continue; vis[x][y]=1;
        upd(x, y-1, d[x][y]+1);
        upd(x, y+1, d[x][y]+1);
        upd(x-1, y, d[x][y]+b[x]-b[x-1]);
        upd(x+1, y, d[x][y]+b[x+1]-b[x]);
        if(b[x]-b[x-1]==1)
        {
            upd(x-1, y-1, d[x][y]+1);
            upd(x-1, y+1, d[x][y]+1);
        }
        if(b[x+1]-b[x]==1)
        {
            upd(x+1, y-1, d[x][y]+1);
            upd(x+1, y+1, d[x][y]+1);
        }
    }
}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
    scanf("%d", &n);
    insert(sx), insert(tx);
    rep(i, 1, n)
    {
        char op[2]; int x, y; scanf("%s%d%d", op, &x, &y);
        a[i]={op[0], x, y}; insert(x);
    }
    sort(b+1, b+nn+1); nn=unique(b+1, b+nn+1)-b-1;
    sx=lower_bound(b+1, b+nn+1, sx)-b;
    tx=lower_bound(b+1, b+nn+1, tx)-b;
    rep(i, 1, n)
    {
        a[i].x=lower_bound(b+1, b+nn+1, a[i].x)-b;
        have[a[i].x][a[i].y]=1;
    }
    rep(i, 1, n)
    {
        int x=a[i].x, y=a[i].y; ban[x][y]=1;
        if(a[i].c=='K')
        {
            rep(nx, x-1, x+1) rep(ny, y-1, y+1)
                if(inrange(nx, ny)) ban[nx][ny]=1;
        }
        if(a[i].c=='N')
        {
            rep(k, 0, 7)
            {
                int nx=x+dx[k], ny=y+dy[k];
                if(inrange(nx, ny)) ban[nx][ny]=1;
            }
        }
        if(a[i].c=='B' || a[i].c=='Q')
        {
            for(int dx:{-1, 1}) for(int dy:{-1, 1})
                for(int nx=x+dx, ny=y+dy; inrange(nx, ny) && !have[nx][ny]; nx+=dx, ny+=dy)
                    ban[nx][ny]=1;
        }
        if(a[i].c=='R' || a[i].c=='Q')
        {
            for(int dx:{-1, 0, 1}) for(int dy:{-1, 0, 1}) if(dx*dy==0)
                for(int nx=x+dx, ny=y+dy; inrange(nx, ny) && !have[nx][ny]; nx+=dx, ny+=dy)
                    ban[nx][ny]=1;
        }
    }
    dij();
    printf("%lld", d[tx][ty]<inf?d[tx][ty]:-1);

    return 0;
}
```

---

