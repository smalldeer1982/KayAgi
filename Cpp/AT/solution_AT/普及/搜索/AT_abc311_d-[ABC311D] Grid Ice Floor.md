# [ABC311D] Grid Ice Floor

## 题目描述

有一个 $N \times M$ 的矩阵，并且有一个玩家站在上面。
其中 $(i, j)$ 表示矩阵的第 $i$ 行第 $j$ 列。
矩阵被表示为 $N$ 个字符串 $S_1 S_2S_3...S_N$，每个字符串长 $M$ 个字符。

矩阵每个格子都是冰或者岩石：如果 $S_i$ 的第 $j$ 个字符，即 $(i, j)$ 对应的字符为 `.`，那么 $(i, j)$ 是冰；如果是 `#`，$(i, j)$ 就是岩石。

这个矩阵的一周（第 $1$ 行、第 $N$ 行、第 $1$ 列，第 $M$ 列）均为岩石。
玩家起始所站的点 $(2, 2)$ 恒为冰。

玩家可以移动零次或任意次，每次移动需要先选定一个方向（上下左右），并且一直沿着这个方向移动直到遇到岩石（或不是冰）。

计算出玩家可以抵达或途径的所有格点（包括滑过的）。

## 说明/提示

对于 $100\%$ 的数据：

$ 3 \le N, M \le 200 $

$S_i$ 是长为 $M$ 的字符串，仅包含 `.` 和 `#`。

矩阵的边缘都是 `#`（岩石），且 $(2,2)$ 处一定为 `.`（冰）。

#### 样例1解释
比如玩家可以经过 $(5,5)$ 通过这样移动：

$(2, 2)$ → $(5, 2)$ → $(5, 5)$

玩家也可以经过 $(2, 4)$：

$(2, 2)$ → $(2, 5)$，途经 $(2, 4)$。

但玩家无法到达 $(3, 4)$。

## 样例 #1

### 输入

```
6 6
######
#....#
#.#..#
#..#.#
#....#
######```

### 输出

```
12```

## 样例 #2

### 输入

```
21 25
#########################
#..............###...####
#..............#..#...###
#........###...#...#...##
#........#..#..#........#
#...##...#..#..#...#....#
#..#..#..###...#..#.....#
#..#..#..#..#..###......#
#..####..#..#...........#
#..#..#..###............#
#..#..#.................#
#........##.............#
#.......#..#............#
#..........#....#.......#
#........###...##....#..#
#..........#..#.#...##..#
#.......#..#....#..#.#..#
##.......##.....#....#..#
###.............#....#..#
####.................#..#
#########################```

### 输出

```
215```

# 题解

## 作者：ran_qwq (赞：7)

为啥大家都写 bfs，蒟蒻写一篇 dfs 的题解。

本题与普通的洪水填充问题有一点区别：向一个方向走需要一直走到碰到岩石为止。

也就是说，一个点可能不止经过一次。

为什么呢？举个例子：

```
######
#.#..#
#....#
###.##
######
```

要从 $(2,2)$ 走到 $(4,4)$（最下面的冰块），需要这样走：$(2,2)\rightarrow(3,2)\rightarrow(3,3)\rightarrow(3,4)\rightarrow(3,5)\rightarrow(2,5)\rightarrow(2,4)\rightarrow(3,4)\rightarrow(4,4)$。其中经过 $(3,4)$ 两次。

但是，容易发现，每个点从每个方向来只经过一次。

于是我们可以在 vis 数组中加多一维，记录有没有从每个方向来即可。

[AT 提交记录](https://atcoder.jp/contests/abc311/submissions/43850708)

---

## 作者：rickyxrc (赞：3)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

觉得自己的写法还算简洁，就来一篇。

## 题面大意

初始时，你处于静止状态，站在冰上，你可以选择一个方向，然后一直向这个方向移动直到碰到障碍物，然后重新变为静止状态，求你一共能走到多少点。

## 解题思路

这个可以应用 bfs 求解。

我们将状态定义为 $(x,y,pos)$，即坐标和方向。

然后这样设计状态写出来的程序就比较自然。

剩下其实就是 bfs 了，这里说一点注意事项。

1. 即使位置相同，能走到的点也不一定是相同的（方向不同），所以标记数组要开三维。
2. 相同位置只算一次贡献，可以开一个二维数组累计，二维数组和三维数组不要混用。
3. 注意判断两种情况的条件：即保持当前方向和向四周扩展，只有对应方向有障碍物的时候才能向四周扩展。

```cpp
#include <stdio.h>
#include <queue>

#define maxn ;

int n, m, mp[maxn][maxn];
int dx[4] = {0, 1, 0, -1},
    dy[4] = {1, 0, -1, 0};

int vis[maxn][maxn][4], book[maxn][maxn], res;

std::queue<std::pair<std::pair<int, int>, int>> qu;

char ch;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            do
            {
                ch = getchar();
            } while (ch != '.' && ch != '#');
            mp[i][j] = (ch == '.');
        }

    qu.push({{2, 2}, 0});
    qu.push({{2, 2}, 1});
    qu.push({{2, 2}, 2});
    qu.push({{2, 2}, 3});
    while (!qu.empty())
    {
        auto u = qu.front();
        qu.pop();
        if (!mp[u.first.first][u.first.second] || u.first.first == 0 || u.first.second == 0 || u.first.first > n || u.first.second >= m)
            continue;
        if (vis[u.first.first][u.first.second][u.second])
            continue;
        vis[u.first.first][u.first.second][u.second] = 1;
        if (!book[u.first.first][u.first.second])
            book[u.first.first][u.first.second] = 1,
            res++;
        if (mp[u.first.first + dx[u.second]][u.first.second + dy[u.second]])
            qu.push({{u.first.first + dx[u.second], u.first.second + dy[u.second]}, u.second});
        else
            for (int i = 0; i < 4; i++)
                qu.push({{u.first.first + dx[i], u.first.second + dy[i]}, i});
    }

    printf("%d", res);

    return 0;
}
```

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc311_d)

## 思路

用 bfs 的思路来做此题。

首先我们定义“落脚点”是每次在岩石前停下的那块冰。四联通 bfs 循环找没有被访问过的落脚点，然后入队。在走过的路径进行标点，最后二重循环统计被走到过的位置，然后计数器 $+1$。最后输出计数器即可。

- 记得标记走过的位置和**开始的位置** $(2,2)$。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=210;
int n,m,ans;//ans 就是上文提到的计数器。
bool vis[N][N],cnt[N][N];
char c[N][N];
struct node{
	int x,y;
};queue<node>q;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)cin>>c[i][j];
	}
	q.push({2,2});
	vis[2][2]=1;
	cnt[2][2]=1;
	while(q.size()){
		node now=q.front();
		q.pop();
		for(int i=0;i<4;++i){
			int xx=now.x;
			int yy=now.y;
			while(c[xx+dx[i]][yy+dy[i]]=='.'){
        //循环走，直到走到岩石前，停止。
				xx+=dx[i];
				yy+=dy[i];
				cnt[xx][yy]=1;
			}
			if(vis[xx][yy])continue;
			vis[xx][yy]=1;
			q.push({xx,yy});//存储没有被访问过的落脚点。
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(cnt[i][j])++ans;//统计走过的位置数。
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/117133379)

---

## 作者：cjh20090318 (赞：1)

## 题意

你在一个 $N \times M$ 的地图上，在地图上有两种地形：

- 冰块，用字符 `.` 表示。
- 岩石，用字符 `#` 表示。

你一开始在 $(2,2)$（保证为冰块），你可以向上下左右四个方向移动直到下一个运动的位置为岩石（中途不能停止），求你经过或停留的冰块数量。

## 分析

这个其实就是一道**广度优先搜索**。

和其他的题目处理略有些不同的地方在于，他不能在移动途中停留，这个特殊判断一下就可以了。

只有到了岩石前方，才能入队。

## 注意事项

由于本人设 $(0,0)$ 为坐标原点，故初始位置应为 $(1,1)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<queue>
#include<utility>
#define mp std::make_pair
#define x first
#define y second
typedef std::pair<int,int> PII;
int n,m;
char s[202][202];
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};//预处理方向数组，减少判断。
bool vis[202][202],vs[202][202];//前者为是否经过该点，后者是是否停留在该点上。
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",s[i]);
	std::queue<PII> Q;
	Q.push(mp(1,1));//加入初始坐标。
	for(PII u;!Q.empty();){
		u=Q.front();Q.pop();
		if(vs[u.x][u.y]) continue;
		vs[u.x][u.y]=1;//标记当前位置停留。
		for(int k=0,nx,ny;k<4;k++){
			for(nx=u.x,ny=u.y;nx>=0&&nx<n&&ny>=0&&ny<m&&s[nx][ny]=='.';nx+=dx[k],ny+=dy[k])vis[nx][ny]=1;//标记当前位置经过。
			nx-=dx[k],ny-=dy[k];//注意后退，因为此时可能已经越界。
			if(!vs[nx][ny]) Q.push(mp(nx,ny));//没有停留过，再次扩展加入队列。
		}
	}
	int sum=0;
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)sum+=vis[i][j];//计数。
	printf("%d\n",sum);
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

不撞南墙不回头，问能经过的所有 ``.`` 点的数量。

### 思路：

很经典的爆搜题目，貌似不需要剪枝都可以过诶……

从 $(2,2)$ 这个点开始，我们可以依次遍历 $1,2,3,4$ 这四种方向（自己定义一个 $dx$ 和 $dy$），然后设置一个判重的数组 $f$，注意要是三维的，第三维是当前点的方向（$1 \to 4$）。

对于我们当前搜到的这个点，需要判断在 $f_{x,y,i},1 \le i \le 4$ 的位置是否为 $1$，只要全部都不为 $1$，那么就可以将答案累加了。

当然，如果搜到的点是墙或者在当前方向已经走过了，那么就可以返回了。每次搜下一个点之后，如果这个点不是墙，那么对于每一个方向都要再次搜一次。

### 完整代码：
```cpp
#include<bits/stdc++.h>
#define INF INT_MAX
using namespace std;
typedef long long ll;
const int N=205;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,sum,dx[]={0,1,-1,0,0},dy[]={0,0,0,-1,1};
bool a[N][N],f[N][N][5];
char c;
void dfs(ll x,ll y,ll w){
	if(f[x][y][w]||!a[x][y])
	  return;
	bool k=0;
	for(int i=1;i<=4;i++)
	  if(f[x][y][i]) 
	    k=1;
	if(!k) 
	  sum++;
	f[x][y][w]=1;
	ll zx=x+dx[w],zy=y+dy[w];
	dfs(zx,zy,w);
	if(!a[zx][zy]){
		for(int i=1;i<=4;i++)
		  if(i!=w) 
			dfs(x+dx[i],y+dy[i],i);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
		  cin>>c,a[i][j]=(c=='.'?1:0);
	for(int i=1;i<=4;i++)
	  dfs(2,2,i);
	write(sum);
	return 0;
}
```


---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定一个 $n\times m$ 的只包含 `#`（代表岩石）和 `.`（代表冰块）的网格图，网格图的四周上的点都是岩石，你的初始位置为冰块 $(2,2)$。在每个冰块上，你可以向上下左后滑动，直至碰到岩石为止，此时你会停留在滑到岩石前的冰块。请求出你能**经过或停留在**多少个冰块上。

题目保证 $3\le n, m\le 200$。

### 题目分析

这是一道比较经典的 bfs 题目。我们可以向上下左右四个方向进行广搜，一直滑到岩石为止，用数组标记哪些点已经经过。

这道题的难点在如何实现记忆化。我们可以发现，如果我们停留在一个点，后面又停留在了这个点，那么这个点可能延伸出来的情况就已经被搜索过，就不必继续搜索。用一个数组标记已经停留在哪些点即可。

具体细节见注释。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205;
struct node{
	int x, y;
	node(int a, int b){
		x = a;
		y = b;
	}
};
int n, m, mp[MAXN][MAXN], ans = 0;
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
bool rst[MAXN][MAXN], pss[MAXN][MAXN]; // rst 代表是否停留过，pss 代表是否经过过
char c;
queue<node> q;
void bfs(){
	q.push(node(2, 2));
	rst[2][2] = pss[2][2] = 1; // 初始化
	while(!q.empty()){
		node f = q.front();
		q.pop();
		int nowx, nowy;
		for(int i = 0;i < 4;i++){
			nowx = f.x, nowy = f.y;
			while(!mp[nowx][nowy]){ // 遍历四个方向到岩石为止
				nowx += dx[i];
				nowy += dy[i];
				pss[nowx][nowy] = 1;
			}
			pss[nowx][nowy] = 0;
			nowx -= dx[i];
			nowy -= dy[i]; // 撤销撞到岩石对岩石的标记操作
			if(rst[nowx][nowy]){ // 记忆化判重
				continue;
			}
			rst[nowx][nowy] = 1;
			q.push(node(nowx, nowy));
		}
		
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> c;
			if(c == '#'){
				mp[i][j] = 1; // 标记岩石块
			}
		}
	}
	bfs();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(pss[i][j]){
				ans++;
			}
		}
	}
	printf("%d", ans);
	return 0;
}


```

---

## 作者：small_john (赞：0)

## 思路

还是挺简单的。直接 BFS 水过。

但是还是有一些细节需要注意：

1. BFS 中途遇到的格子不能进入队列，必须撞到石头才能入队；
2. 注意在移动的时候如果采用的是 `while` 循环，那最后一定要退一步。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e2+5;
int n,m,ans,mx[4] = {1,0,0,-1},my[4] = {0,1,-1,0};
bool vis[N][N],v[N][N];
char s[N][N];
void bfs()
{
	queue<int> x,y;
	x.push(2),y.push(2);
	while(!x.empty())
	{
		int ux = x.front(),uy = y.front();x.pop(),y.pop();
		if(v[ux][uy]) continue;
		v[ux][uy] = 1;//标记
		for(int i = 0;i<4;i++)
		{
			int X = ux,Y = uy;
			while(s[X][Y]=='.')
				vis[X][Y] = 1,X+=mx[i],Y+=my[i];
			X-=mx[i],Y-=my[i];//退一步
			x.push(X),y.push(Y);
		}
	}
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			ans+=vis[i][j];
	cout<<ans;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			cin>>s[i][j];
 	bfs();
	return 0;
}
```

---

## 作者：c1ampy (赞：0)

本题与常规的 Flood Fill 问题极为相似，只不过对移动的方向做出了一定限制。只需将该限制添加至常规 Flood Fill 算法模板即可通过。

不过，由于本题添加了对移动方向的限制，而且本题对路径长度不做要求，就使得本题同样适合使用 DFS 解决。下面主要介绍本题的 DFS 解法。

本题中，在撞上石头前不能改变方向，因此我们不必也不能对路径上的每一个方格都进行搜索，只需也只能对一次移动的起点和该次移动的终点进行搜索。

当然，暴力搜索不可行，我们需要进行剪枝优化：

- 记忆化

	将已经搜索过的方格标记为已搜索，下一次尝试以该方格为起点进行搜索时直接返回，避免重复搜索。

- 排除等效冗余

	记录进入当前方格时的运动方向 $ dir $，在以当前网格为起点进行搜索时，不对 $ dir $ 的相反方向进行搜索，避免经过已经搜索过的路径。

代码如下：

```cpp
#include <iostream>

const int dr[5] = { 0, -1, 0, 0, 1 };
const int dc[5] = { 0, 0, -1, 1, 0 };
const int max_r = 210;
const int max_c = 210;

int R, C;
char map[max_r][max_c];
bool searched[max_r][max_c];
bool reachable[max_r][max_c];

void dfs(const int r, const int c, const int last_direction);

int main() {

	scanf("%d %d", &R, &C);
	for (int i = 1; i <= R; ++i) {
		scanf("%s", map[i] + 1);
	}

	dfs(2, 2, 0);

	int cnt = 0;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			cnt += reachable[i][j];
		}
	}

	printf("%d\n", cnt);

	return 0;
}

void dfs(const int r, const int c, const int last_direction) {
	// 记忆化
	if (searched[r][c]) {
		return;
	}
	searched[r][c] = true;

	reachable[r][c] = true;
	for (int direction = 1; direction <= 4; ++direction) {
		// 排除等效冗余
        if (direction + last_direction == 5) {
            continue;
        }
        int cur_r = r, cur_c = c;
        while (map[cur_r + dr[direction]][cur_c + dc[direction]] == '.') {
            cur_r += dr[direction];
            cur_c += dc[direction];
            reachable[cur_r][cur_c] = true;
        }
        dfs(cur_r, cur_c, direction);
	}
}
```

代码中 `searched` 数组用于标记是否曾以某方格为起点进行搜索，而 `reachable` 数组用于标记某方格是否可达，便于统计答案。请勿混淆二者含义及作用。

---

## 作者：luogu_gza (赞：0)

我们考虑搜索，题目的意思其实是所有**能**遍历到的点，而不是一次性能遍历到的点。

这里有几个细节需要注意：

1. 不能往回走。

2. 有些东西能打包成函数就打包好。

3. 不要怕复杂度高，一步一步走。

4. 路径可能重叠。

[code](https://atcoder.jp/contests/abc311/submissions/43877915)

---

## 作者：EmptyAlien (赞：0)

# [D - Grid Ice Floor](https://atcoder.jp/contests/abc311/tasks/abc311_d)

## Sol

考虑 BFS，每一次状态转移就是从这个点往四个方向延展，**中途遇到的格子不能放进队列中**，碰到后的那个格子如果没有走过就放进队列中。

代码细节较多，需要注意。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205;
queue<pair<int, int>> q;
int vis[MAXN][MAXN];
int n, m;
bool check(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < m;
}
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
string maze[MAXN];
void bfs() {
    vis[1][1] = 1;
    q.push(make_pair(1, 1));
    while (q.size()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tx = x;
            int ty = y;
            while (1) {
                if (!check(tx + dir[i][0], ty + dir[i][1]) or maze[tx + dir[i][0]][ty + dir[i][1]] == '#') {
                    if (!vis[tx][ty]) q.push(make_pair(tx, ty));
                    vis[tx][ty] = 1;
                    break;
                }
                vis[tx][ty] = 1;
                tx += dir[i][0];
                ty += dir[i][1];
            }
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> maze[i];
    bfs();
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans += vis[i][j];
    cout << ans << endl;
    return 0;
}
```

---

