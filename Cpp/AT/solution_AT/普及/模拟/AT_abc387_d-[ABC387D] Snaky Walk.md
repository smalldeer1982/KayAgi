# [ABC387D] Snaky Walk

## 题目描述

有一个 $H$ 行 $W$ 列的网格。从上往下第 $i$ 行、从左往右第 $j$ 列的单元格记为 $(i,j)$。

每个单元格是起点、终点、空单元格或障碍物，这些信息由 $H$ 个长度为 $W$ 的字符串 $S_1,S_2,\dots,S_H$ 表示。具体来说，当 $S_i$ 的第 $j$ 个字符是 `S` 时，单元格 $(i,j)$ 是起点；是 `G` 时是终点；是 `.` 时是空单元格；是 `#` 时是障碍物。保证起点和终点各恰好存在一个。

你现在位于起点。你的目标是通过重复移动到当前单元格边相邻的单元格，最终到达终点。但有以下限制：不能移动到障碍物或网格外，且必须交替进行纵向移动和横向移动（首次移动方向可任选）。

请判断能否到达终点，若可能则求出移动次数的最小值。

更形式化地说，请判断是否存在满足以下所有条件的单元格序列 $(i_1,j_1),(i_2,j_2),\dots,(i_k,j_k)$，若存在则求 $k-1$ 的最小值：

- 对所有 $1 \leq l \leq k$，满足 $1 \leq i_l \leq H$ 且 $1 \leq j_l \leq W$，且 $(i_l,j_l)$ 不是障碍物
- $(i_1,j_1)$ 是起点
- $(i_k,j_k)$ 是终点
- 对所有 $1 \leq l \leq k-1$，满足 $|i_l - i_{l+1}| + |j_l - j_{l+1}| = 1$
- 对所有 $1 \leq l \leq k-2$，若 $i_l \neq i_{l+1}$，则 $i_{l+1} = i_{l+2}$
- 对所有 $1 \leq l \leq k-2$，若 $j_l \neq j_{l+1}$，则 $j_{l+1} = j_{l+2}$

## 说明/提示

### 约束条件

- $1 \leq H, W \leq 1000$
- $H, W$ 是整数
- $S_i$ 是由 `S`、`G`、`.`、`#` 组成的长度为 $W$ 的字符串
- 起点和终点各恰好存在一个

### 样例解释 1

![](https://img.atcoder.jp/abc387/6ef2f123adae6bc6bb157af8f30afe89.png)  
按照左图的路径 $(1,2) \rightarrow (2,2) \rightarrow (2,3) \rightarrow (3,3) \rightarrow (3,4) \rightarrow (2,4) \rightarrow (2,5) \rightarrow (1,5)$，可以通过 7 次移动到达终点。无法用 6 次或更少移动到达终点，因此答案是 7。注意右图所示的连续横向移动（或连续纵向移动）路径是不被允许的。

### 样例解释 2

无法到达终点。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 5
.S#.G
.....
.#...```

### 输出

```
7```

## 样例 #2

### 输入

```
3 5
..#.G
.....
S#...```

### 输出

```
-1```

## 样例 #3

### 输入

```
8 63
...............................................................
..S...#............................#####..#####..#####..####G..
..#...#................................#..#...#......#..#......
..#####..####...####..####..#..#...#####..#...#..#####..#####..
..#...#..#..#...#..#..#..#..#..#...#......#...#..#..........#..
..#...#..#####..####..####..####...#####..#####..#####..#####..
................#.....#........#...............................
................#.....#........#...............................```

### 输出

```
148```

# 题解

## 作者：ikunTLE (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc387_d)

### 思路

可以使用 **bfs** 解决此题。

与普通 bfs 不同，这道题遍历需要横纵交替。于是可以在 bfs 队列中增加一维，表示上一次操作是横还是纵。在下一次进入时，就可以根据队列中新增的一维来判断应该横向走还是纵向走。

bfs 的时间复杂度为 $\mathcal{O}(N^2)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10;
int dx1[]={0,0,0},dy1[]={0,-1,1};
int dx2[]={0,-1,1},dy2[]={0,0,0};
struct node{
	int x,y,flag;
};queue<node>q;
char s[N][N];
bool vis[N][N][2];
signed main(){
	int h=read(),w=read();
	for(int i=1;i<=h;++i)
		scanf("%s",s[i]+1);
	int bx,by,ex,ey;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			if(s[i][j]=='S')
				bx=i,by=j;
			else if(s[i][j]=='G')
				ex=i,ey=j;
	q.push({bx,by,0}),q.push({bx,by,1});
	vis[bx][by][0]=true,vis[bx][by][1]=true;
	int dis=0;
	while(!q.empty()){
		int n=q.size();
		while(n--){
			node u=q.front();q.pop();
			int x=u.x,y=u.y,op=u.flag;
			if(x==ex&&y==ey)
				return printf("%lld\n",dis),0;
			if(!op)
				for(int i=1;i<=2;++i){
					int xx=x+dx1[i],yy=y+dy1[i];
					if(xx>=1&&xx<=h&&yy>=1&&yy<=w&&s[xx][yy]!='#'&&!vis[xx][yy][1]){
						vis[xx][yy][1]=true;
						q.push({xx,yy,1});
					}
				}
			else for(int i=1;i<=2;++i){
					int xx=x+dx2[i],yy=y+dy2[i];
					if(xx>=1&&xx<=h&&yy>=1&&yy<=w&&s[xx][yy]!='#'&&!vis[xx][yy][0]){
						vis[xx][yy][0]=true;
						q.push({xx,yy,0});
					}
				}
		}
		++dis;
	}
	printf("-1\n");
	return 0;
}
```

---

## 作者：_anll_ (赞：4)

比 C 简单。
## 思路
和最板的 bfs 相比只多了方向限制。那我们只需要在每次入队时多存一个上次是从哪个方向来的即可。结构体搞定，或者你想用 `pair<pair<int,int>,int>` 我也拦不了你。

注意判边界和无解时输出 `-1`。

## 代码
```cpp
#include<queue>
#include<iostream>
#define int long long
using namespace std;
const int N=1e3+5;
struct P{int x,y,f;};
int n,m,sx,sy,ex,ey,mp[N][N],vu[N][N][2];
queue<P> qo;
void Push(int x,int y,int k,int c){
	if(x<1||x>n||y<1||y>m||vu[x][y][k]||mp[x][y]) return;
	vu[x][y][k]=c;qo.push({x,y,k});
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;char a;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a;
			if(a=='S') sx=i,sy=j;
			else if(a=='G') ex=i,ey=j;
			else if(a=='#') mp[i][j]=1;
		}
	}
	qo.push({sx,sy,0});qo.push({sx,sy,1});
	vu[sx][sy][0]=vu[sx][sy][1]=1;
	while(!qo.empty()){
		P p=qo.front();qo.pop();
		if(p.x==ex&&p.y==ey){
			cout<<vu[p.x][p.y][p.f]-1;
			return 0;
		}
		if(p.f){
			Push(p.x-1,p.y,0,vu[p.x][p.y][p.f]+1);
			Push(p.x+1,p.y,0,vu[p.x][p.y][p.f]+1);
		}
		else{
			Push(p.x,p.y-1,1,vu[p.x][p.y][p.f]+1);
			Push(p.x,p.y+1,1,vu[p.x][p.y][p.f]+1);
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：xyx404 (赞：2)

## 思路：
 
BFS。

如没学过，可以先看看 [OI Wiki](https://oi-wiki.org/graph/bfs/)，然后把模版题 [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)做了。

考虑到题目要求，上一次横着走，那下一次就必须竖着走；上一次竖着走，那下一次就必须横着走，所以 BFS 的队列里的变量要多一个变量 $cx$ 表示上一次走的方向，同时考虑到可能横着走到达这个点不可以到达终点，但是竖着走到达这个点可能可以到达终点，所以标记数组也要多一维，表示方向，当现在到达的点为终点时，说明可以到达输出答案。

其余的就是 BFS 的模版了。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int h,w;
int sx,sy,ex,ey;
bool bj[1200][1200][4];
char jz[1200][1200];
struct node{
	int x,y;
	int cx;// 上一次的上下/左右/起点 
	int step;
};
queue<node>dl;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1}; 
int main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++){
		cin>>jz[i][j];
		if(jz[i][j]=='S')sx=i,sy=j;
		else if(jz[i][j]=='G')ex=i,ey=j;
		else if(jz[i][j]=='#')bj[i][j][1]=1,bj[i][j][2]=1,bj[i][j][0]=1;
	}
	dl.push({sx,sy,0,0});
	while(dl.empty()==0){
		node tamp=dl.front();dl.pop();
//		cout<<tamp.x<<" "<<tamp.y<<"\n";
		if(tamp.x==ex&&tamp.y==ey){
			cout<<tamp.step;
			return 0;
		}
		if(bj[tamp.x][tamp.y][tamp.cx])continue;
		bj[tamp.x][tamp.y][tamp.cx]=1;
		for(int i=0;i<4;i++){
			int tx=tamp.x+dx[i],ty=tamp.y+dy[i];
			if(tx<1||ty<1||tx>h||ty>w)continue;
			if(i<=1&&tamp.cx!=1){
				dl.push({tx,ty,1,tamp.step+1});
			}
			else if(i>1&&tamp.cx!=2){
				dl.push({tx,ty,2,tamp.step+1});
			}
		}
	} 
	cout<<-1;
	return 0;
}


```

[AC 记录](https://atcoder.jp/contests/abc387/submissions/61400036)。

---

## 作者：Ambrose0321 (赞：1)

这我第一次在 ABC 里发现的比 C 题还简单的 D 题。

思路：
---

读完题，我们发现这道题跟网格图 bfs 很像，只要在 bfs 的队列加上要“蛇形走位”这个条件就行了。

我们不妨在 bfs 的队列里增加一维，用 $0$ 表示格子是从横向走过来的，$1$ 表示格子是从纵向走过来的。

这道题有个坑，从开始 bfs 时我们要注意横向纵向都要考虑一遍才对。

最后就是统计答案啦，答案需要特判一下：

1. 如果两次 bfs 都无法到达终点就输出 ``-1``.
2. 如果只有一次到不了终点就输出能到终点那一次的答案。
3. 两次都能到终点就按题意输出更小的那个。


这样，我们就开心的 AC 啦！



AC code:
---


```cpp
#include <bits/stdc++.h>
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef set<int> si;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int N = 500001, P = 998244353, INF = 2139062143;
int gcd(int A, int B) {return B ? gcd(B, A % B) : A;}
int lcm(int A, int B) {return A * B / gcd(A, B);}
// 上面的都可以不看
struct Node {
	int x, y;
	bool b;
	Node (int _x, int _y, bool _b) {
		x =_x, y = _y, b = _b;
	}
};
const int D[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int n, m, sx, sy, ex, ey, d1, d2, dis[1001][1001];
char s[1001][1005];
queue<Node> q;
bool check(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= m && s[x][y] != '#' && dis[x][y] == -1;
}

inline void bfs(bool p) {
	memset(dis, 255, sizeof(dis));
	dis[sx][sy] = 0;
	for (int i = 0; i < 4; i++) {
		if ((p && i > 1) || (!p && i < 2))
			continue;
		int x = sx + D[i][0], y = sy + D[i][1];
		if (check(x, y))
			dis[x][y] = 1, q.push(Node(x, y, !p));
	}
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y;
		bool b = q.front().b;
		q.pop();
		for (int i = 0; i < 4; i++) {
			if ((b && i > 1) || (!b && i < 2))
				continue;
			int xx = x + D[i][0], yy = y + D[i][1];
			if (check(xx, yy))
				dis[xx][yy] = dis[x][y] + 1, q.push(Node(xx, yy, !b));
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'S')
				sx = i, sy = j;
			if (s[i][j] == 'G')
				ex = i, ey = j;
		}
	}
	bfs(0);
	d1 = dis[ex][ey];
	bfs(1);
	d2 = dis[ex][ey];
	if (d1 == -1 && d2 == -1)
		puts("-1");
	else
		if (d1 == -1 || d2 == -1)
			printf("%d\n", max(d1, d2));
		else
			printf("%d\n", min(d1, d2));
}
```
这是本蒟蒻第一次发题解，请各位大佬不喜勿喷，希望能过审 qwq。

---

## 作者：Yuexingfei_qwq (赞：0)

我见过最简单的 D 题。
## 思路  
很明显是一道网格 BFS 的题目。  

其实和普通的网格 BFS 代码几乎一样，但是题目要求**水平和垂直交替走**，所以可以设 $p_{i,j}$ 表示走到坐标为 $(i,j)$ 的格子前一个格子的方向，$p_{i,j} = 0$ 表示水平方向行走，$p_{i,j} = 1$ 表示垂直方向行走。接下来在 BFS 里加点特判就好了。  

因为起点的出发方向是可以随机的，记得把两种情况都 BFS 一遍。

答案的话就得特判了。  
设 $ans$ 为起点出发方向是水平方向时的答案，$res$ 为起点出发方向是垂直方向时的答案。
- 如果 $ans$ 和 $res$ 都是 $-1$，说明无解，输出`-1`。
- 如果 $ans$ 和 $res$ 中只有一个是 $-1$，则输出不是 $-1$ 的那个。
- 如果 $ans$ 和 $res$ 都不是 $-1$，输出两者的较小值。
## AC CODE
赛时代码。

```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int h, w, sx, sy, ex, ey;
char s[1100][1100];
int p[1100][1100];
int ans;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int d[1100][1100];
struct Info {
	int x, y;
};
std::queue<Info> q;

inline void bfs(int g) {
	p[sx][sy] = g;
	memset(d, 255, sizeof(d));
	d[sx][sy] = 0;
	q.push({sx, sy});
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y;
		q.pop();
		if (p[x][y] == 1) {
			F(k, 0, 1, 1) {
				int xx = x + dx[k], yy = y + dy[k];
				if (xx < 1 || xx > h || yy < 1 || yy > w || s[xx][yy] == '#' || d[xx][yy] != -1) {
					TheEnd;
				}
				q.push({xx, yy});
				d[xx][yy] = d[x][y] + 1;
				p[xx][yy] = 0;
			}
		}
		if (p[x][y] == 0) {
			F(k, 2, 3, 1) {
				int xx = x + dx[k], yy = y + dy[k];
				if (xx < 1 || xx > h || yy < 1 || yy > w || s[xx][yy] == '#' || d[xx][yy] != -1) {
					TheEnd;
				}
				q.push({xx, yy});
				d[xx][yy] = d[x][y] + 1;
				p[xx][yy] = 1;
			}
		}
	}
	if (g == 0) {
		ans = d[ex][ey];
	}
}

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> h >> w;
	F(i, 1, h, 1) {
		F(j, 1, w, 1) {
			cin >> s[i][j];
			if (s[i][j] == 'S') {
				sx = i, sy = j;
			}
			if (s[i][j] == 'G') {
				ex = i, ey = j;
			}
			p[i][j] = -1;
		}
	}
	bfs(0);
	bfs(1);
	if (ans == -1 && d[ex][ey] == -1) {
		cout << -1 << el;
		r0;
	}
	if (ans == -1) {
		cout << d[ex][ey] << el;
		r0;
	}
	if (d[ex][ey] == -1) {
		cout << ans << el;
		r0;
	}
	cout << std::min(ans, d[ex][ey]) << el;
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc387/submissions/61388059)

---
完结~~不~~散花。

---

## 作者：sjh0626 (赞：0)

## 题意概括
给你一个 $H$ 行 $W$ 列的网格，其中有四种单元格：
- `.`：空地
- `#`：障碍物
- `S`：起点
- `G`：终点

你只能在垂直移动和水平移动之间交替进行，但是开始的方向自己选择，求从起点到终点的最小步数。
## 思路分析
一个很水的广搜，但是要注意，我们要开两个数组，也就是在原本的基础上再增加方向一维，因为开始的方向有两种，接下来就是变换方向，这个也很简单，最后就可以通过此题。

但是要注意变换方向后只能上下或左右移动。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define int long long
using namespace std;
class FastIO{
	public:
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(int &x){
		x=read();
		return *this;
	}
};
FastIO qin;
struct node{
	int x,y,now,step;
};
queue<node>q;
bool vis[2][1010][1010];
char g[1010][1010];
int h,w,sx,sy,ex,ey,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},ans=1e9;
void bfs(int sx,int sy,int ex,int ey){
	vis[0][sx][sy]=vis[1][sx][sy]=1;
	q.push({sx,sy,0,0});
	q.push({sx,sy,1,0});
	while(!q.empty()){
		node u=q.front();
		q.pop();
		if(g[u.x][u.y]=='G'){
			ans=min(ans,u.step);
			continue;
		}
		for(int i=u.now*2;i<(u.now*2+2);i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(g[nx][ny]=='#'||nx<1||nx>h||ny<1||ny>w||vis[!u.now][nx][ny])continue;
			q.push({nx,ny,!u.now,u.step+1});
			vis[!u.now][nx][ny]=1;
		}
	}
}
signed main(){
	qin>>h>>w;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>g[i][j];
			if(g[i][j]=='S')sx=i,sy=j;
			else if(g[i][j]=='G')ex=i,ex=j;
		}
	}
	bfs(sx,sy,ex,ey);
	cout<<(ans==1000000000?-1:ans); 
	sjh0626s code;
}
```

---

## 作者：__Ship_ (赞：0)

## 题目大意

从起点到终点，水平走与垂直走交替，第一部可以选择任意方向，问到达终点所需的步数。不能输出 $-1$。

## 思路

首先，这道题要让我们求最短路，且没有边权，要么是记忆化搜索，要么是 BFS。

讲一下 BFS，可以将水平，垂直放在一起，也就是对 $x$ 的移动放在一起，$y$ 的移动放在一起。

像这样：

```cpp
int fx[5]={0,0,0,-1,1};
int fy[5]={0,-1,1,0,0};
```

然后对于整个队列，有 $4$ 个变量我们能判断怎么往下一个移动或者合不合法（至少我是这么想的吧）：

1. 坐标位置 $(x,y)$
2. 当前步数
3. 这个元素的上一步是垂直还是水平

像这样：

```cpp
struct node{
	int x,y,step,f;
};
```

考虑完这个，再来想想 BFS 里面该怎么写。

首先初始化不用想，来想想怎么判断是否合法。

合法有以下几步：

1. 先判断当前节点的上一步是怎么走过来的，在给定相应的走法
2. 判断是否出界
3. 判断是否能走
4. 判断这个点之前标记的节点是不是与自己走法一样，一样说明重复了，没必要走了

整体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int fx[5]={0,0,0,-1,1};
int fy[5]={0,-1,1,0,0};
int ans=-1e9,n,m,vis[1005][1005][2],ex,ey,bx,by;
char mp[1005][1005];
struct node{
	int x,y,step,f;
};
queue<node> q;
int bfs(int ex,int ey){
	node tmp;
	tmp.x=ex;
	tmp.y=ey;
	tmp.step=0;
	tmp.f=-1;
	q.push(tmp);
	while(!q.empty()){
		node t=q.front();
		if(t.f==-1){
			for(int i = 1 ; i <= 4 ; i++){
				int tx=t.x+fx[i];
				int ty=t.y+fy[i];
				if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&mp[tx][ty]!='#'){
					if(tx==bx&&ty==by){
						ans=t.step+1;
						return 1;
					}
					node used;
					used.x=tx;
					used.y=ty;
					used.step=t.step+1;
					used.f=(int)ceil(i*1.0/2);
					vis[tx][ty][(int)ceil(i*1.0/2)]=1;
					q.push(used);
				}
			}
		}
		else{
			if(t.f==1){
				for(int i = 3 ; i <= 4 ; i++){
					int tx=t.x+fx[i];
					int ty=t.y+fy[i];
					if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&mp[tx][ty]!='#'&&!vis[tx][ty][2]){
						if(tx==bx&&ty==by){
							ans=t.step+1;
							return 1;
						}
						node used;
						used.x=tx;
						used.y=ty;
						used.step=t.step+1;
						used.f=2;
						vis[tx][ty][2]=1;
						q.push(used);
					}
				}
			}
			else{
				for(int i = 1 ; i <= 2 ; i++){
					int tx=t.x+fx[i];
					int ty=t.y+fy[i];
					if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&mp[tx][ty]!='#'&&!vis[tx][ty][1]){
						if(tx==bx&&ty==by){
							ans=t.step+1;
							return 1;
						}
						node used;
						used.x=tx;
						used.y=ty;
						used.step=t.step+1;
						used.f=1;
						vis[tx][ty][1]=1;
						q.push(used);
					}
				}
			}
		}
		q.pop();
	}
	return -1;
}
int main(){
	cin>>n>>m;
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= m ; j++){
			cin>>mp[i][j];
			if(mp[i][j]=='S'){
				ex=i;
				ey=j;
			}
			if(mp[i][j]=='G'){
				bx=i;
				by=j;
			}
		}
	}
	bfs(ex,ey);
	if(ans==-1e9){
		cout<<-1;
	}
	else{
		cout<<ans;
	}
	return 0;
}

```

---

## 作者：Liuhy2996 (赞：0)

## 思路
如果没有方向要求，就是简单的 bfs。现在加入方向要求，只需在 bfs 时多加一个表示方向的状态即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e3+10,mod=998244353;
int n,m,sx,sy,tx,ty,d[N][N][4],dx[]={0,1,0,-1},dy[]={1,0,-1,0};
bool vis[N][N][4];
struct A{int x,y,d;};
queue<A>q;
char c[N][N];
bool chk(int x,int y,int d){return (x&&y&&x<=n&&y<=m&&!vis[x][y][d]&&c[x][y]!='#');}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>c[i][j];
			if(c[i][j]=='S') sx=i,sy=j;
			if(c[i][j]=='G') tx=i,ty=j;
		}
	for(int i=0;i<4;++i) q.push({sx,sy,i}),d[sx][sy][i]=1;
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,dir=q.front().d; q.pop();
		vis[x][y][dir]=1;
		if(x==tx&&y==ty) return cout<<d[x][y][dir]-1,0;
		for(int i=0;i<4;++i)
			if(((dir^i)&1)&&chk(x+dx[i],y+dy[i],i)&&!d[x+dx[i]][y+dy[i]][i])
				q.push({x+dx[i],y+dy[i],i}),d[x+dx[i]][y+dy[i]][i]=d[x][y][dir]+1;
	}
	cout<<-1;
	return 0;
}
```

---

