# [ABC151D] Maze Master

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc151/tasks/abc151_d

高橋君は、縦 $ H $ マス、横 $ W $ マスの $ H\ \times\ W $ マスからなる迷路を持っています。

上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ は、 $ S_{ij} $ が `#` のとき壁であり、`.` のとき道です。

道のマスからは、上下左右に隣接する道のマスに移動することができます。

迷路の外に移動すること、壁のマスへ移動すること、斜めに移動することはできません。

高橋君は、道のマスからスタートとゴールを自由に決め、迷路を青木君に渡します。

青木君は、移動回数が最小になるようにしてスタートからゴールまで移動します。

高橋君がスタートとゴールの位置を適切に定めたとき、青木君の移動回数は最大で何回になるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 20 $
- $ S_{ij} $ は `.` か `#`
- $ S $ は `.` を $ 2 $ つ以上含む
- 任意の道のマスから任意の道のマスまで $ 0 $ 回以上の移動で到達できる

### Sample Explanation 1

高橋君が左上のマスをスタート、右下のマスをゴールにした場合、青木君の移動回数は $ 4 $ 回になります。

### Sample Explanation 2

高橋君が左下のマスをスタート、右上のマスをゴールにした場合、青木君の移動回数は $ 10 $ 回になります。

## 样例 #1

### 输入

```
3 3
...
...
...```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5
...#.
.#.#.
.#...```

### 输出

```
10```

# 题解

## 作者：Zachary_Cloud (赞：3)

题意很简单，就是求**任意**两点之间**最长**的距离。

对于本题的数据范围，我们发现：

- $1 \le H,W \le 20$

于是，我们可以考虑对于每个点，用 BFS 跑一遍全图。

$\mathcal{O(n^4)}$ 是肯定不会爆的啦。

就能很愉快地水过去这道题。

代码+注释：

```cpp
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(0); //读入优化，取消 cin 与 scanf 的同步，时间能省很多
using namespace std;
int n, m, head, tail, Max;
int f[30][30][30][30];
int b[30][30];
int dx[4] = {-1, 0, 0, 1}; //方便取上下左右
int dy[4] = {0, -1, 1, 0};
char a[30][30];
struct Node {int l, r;} q[1000010];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> a[i][j]; //读入
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == '#') continue; //如果当前点是墙，直接跳过
			for (int x = 1; x <= n; ++x)
				for (int y = 1; y <= m; ++y) b[x][y] = 0; //初始化都标为未访问
			b[i][j] = 1; //本身已访问
			f[i][j][i][j] = 0; //表示从 [i,j] 到 [i,j] 的距离
			head = 1; tail = 1; //广搜
			q[head].l = i; q[head].r = j;
			while (head <= tail) {
				for (int k = 0; k <= 3; k++) {
					int x = q[head].l + dx[k], y = q[head].r + dy[k];
					if (a[x][y] == '.' && b[x][y] == 0) {
						tail++; b[x][y] = 1;
						q[tail].l = x; q[tail].r = y;
						f[i][j][x][y] = f[i][j][q[head].l][q[head].r] + 1; //距离+1
						Max = max(Max, f[i][j][x][y]); //取最大值
					}
				}
				head++;
			}
		}
	cout << Max;
	return 0;
}
```

---

## 作者：HYdroKomide (赞：2)

### 题意：
给定一个二维方格，有空地和障碍物，求任意两点间距离的最大值。

### 思路：
由于数据量较小，可以采用较为暴力的 BFS 解法。

首先一一枚举所有非障碍物的点，将此点设为起点后进行 BFS。

BFS 过程：

1. 将起点入队，距离设为 $0$。
2. 枚举所有入队的点，判断是否满足条件（未经过，不是障碍物，不出图）。
3. 如果满足条件，将此点入队，距离设为前一点加 $1$。
4. 取距离的最大值赋给返回值。
5. 重复过程 $2$，$3$，$4$ 直到所有点都已经经过。

总时间复杂度：$O(H^2W^2)$。

### 程序如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int dx[]={0,0,1,-1};//设定四个BFS方向
const int dy[]={1,-1,0,0};
int n,m,sx,sy,dis[21][21],ans;
char a[21][21];
bool vis[21][21];
struct node{int x,y;};
queue<node>q;
int bfs(int sx,int sy){
	int ret=0;//用来存以sx，sy为起点的最大距离
	memset(vis,false,sizeof(vis));//清空之前的访问数组和距离数组
	memset(dis,0,sizeof(dis));
	q.push(node{sx,sy});
	vis[sx][sy]=true;
	while(!q.empty()){
		int x=q.front().x,y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){//四个方向BFS
			int xn=x+dx[i],yn=y+dy[i];
			if(xn<1||xn>n||yn<1||yn>m||a[xn][yn]=='#'||vis[xn][yn])continue;
            //出格或者是障碍物直接跳过
			vis[xn][yn]=true;
			dis[xn][yn]=dis[x][y]+1;
			ret=max(ans,dis[xn][yn]);//取目前距离最大值
			q.push(node{xn,yn});
		}
	}
	return ret;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];//输入字符时cin比较稳妥
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!='#')//判断是否是障碍物后进行BFS
				ans=max(ans,bfs(i,j));
	printf("%d\n",ans);
	return 0;
}
```
### THE END

---

## 作者：Herowin (赞：2)


都是dfs，bfs啊。
扔一个floyd解法

考虑到$n$很小，可以对给出的图进行建图，然后跑一个多源最短路，方可解决此题。

```cpp
	omiga = n * m ;
	rep (i , 1 , omiga) {
		rep (j , 1 , omiga) {
			if (i == j) d[i][j] = 0 ;
			else d[i][j] = 2e9;
		}
	}
	rep (i , 1 , n) {
		cin >> (ch[i] + 1) ;
	}
	rep (i , 1 , n) {
		rep (j , 1 , m) {
			if (ch[i][j] == '#') continue ; 
			if (i != n && ch[i + 1][j] != '#') {
				d[change(i,j)][change(i + 1 , j)] = 1 ;
			}
			if (j != m && ch[i][j + 1] != '#') {
				d[change(i,j)][change(i,j+1)] = 1 ;
			}
			if (i != 1 && ch[i - 1][j] != '#') {
				d[change(i,j)][change(i-1,j)] = 1 ;
			}
			if (j != 1 && ch[i][j - 1] != '#') {
				d[change(i,j)][change(i,j-1)] = 1 ;
			} 	
		}
	}

	for (int k = 1 ; k <= omiga ; k ++) {
		for (int i = 1 ; i <= omiga ; i ++) {
			for (int j = 1 ; j <= omiga ; j ++) {
				d[i][j] = min (d[i][j] , d[i][k] +d[k][j]) ;
			}
		}
	}
	rep (i , 1 , omiga) {
		rep (j , 1 , omiga) {
			if (d[i][j] == (int)2e9) continue ;
 			ans = umax (d[i][j] , ans) ;		
		}
	}
	cout << ans << endl ;
```


---

## 作者：洛璟 (赞：2)

## Solution
这是我做过的比较简单的D题了……真的是简单……

我们观察数据范围，考虑暴力。

对每一个点跑bfs，最多为 $O(n^{4})$ 的时间复杂度，妥妥的不会爆时间，那么我们只需要对每一个点跑bfs，算出到每一个点的最短距离，最后取max即可

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int wk[5][5];
char c[25][25];
bool fg[25][25];
int ans;
struct cccp
{
    int x, y;
};
queue<cccp> q;
queue<int> t;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
void bfs(int sx, int sy)
{
    q.push((cccp) { sx, sy });
    t.push(0);
    fg[sx][sy] = 1;
    while (!q.empty())
    {
        int nx = q.front().x;
        int ny = q.front().y;
        int nt = t.front();
        ans = max(nt, ans);
        q.pop();
        t.pop();
        for (register int i = 1;i <= 4;++i)
        {
            int dx = nx + wk[1][i];
            int dy = ny + wk[2][i];
            int dt = nt + 1;
            if (dx < 0 || dy < 0 || dx >= n || dy >= m || fg[dx][dy] == 1 || c[dx][dy] == '#') continue;
            fg[dx][dy] = 1;

            q.push((cccp) { dx, dy });
            t.push(dt);
        }
    }
}
int main()
{
    wk[1][1] = 1;
    wk[1][2] = 0;
    wk[1][3] = 0;
    wk[1][4] = -1;
    wk[2][1] = 0;
    wk[2][2] = -1;
    wk[2][3] = 1;
    wk[2][4] = 0;
    std::ios::sync_with_stdio(false);
    cin>>n>>m;
    for (register int i = 0;i < n;++i)
    {
        cin >> c[i];
    }
    for (register int i = 0;i < n;++i)
    {
        for (register int j = 0;j < m;++j)
        {
            if (c[i][j] == '.')
            {
                memset(fg, 0, sizeof(fg));
                bfs(i, j);
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：happybob (赞：0)

题目传送门：[AT5220](https://www.luogu.com.cn/problem/AT5220)

这个题目用 `BFS` 解决即可，对于每一个点 `(i, j)`，判断是否是空格，是的话就 `BFS` 搜索即可，总的复杂度是 $O(H^2W^2)$，完全够用。

代码：

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 25;
char ch[N][N];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int H, W;
int ans;
bool visit[N][N];

struct Node
{
	int x, y, times;
};

void bfs(int x, int y)
{
	queue<Node> q;
	Node t;
	t.x = x; t.y = y; t.times = 0;
	q.push(t);
	visit[x][y] = true;
	while (!q.empty())
	{
		Node l = q.front();
		ans = max(ans, l.times);
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int new_x = l.x + dx[i];
			int new_y = l.y + dy[i];
			if (new_x < 1 || new_x > H || new_y < 1 || new_y > W || visit[new_x][new_y] || ch[new_x][new_y] == '#')
			{
				continue;
			}
			Node tmp;
			tmp.x = new_x;
			tmp.y = new_y;
			tmp.times = l.times + 1;
			q.push(tmp);
			visit[new_x][new_y] = true;
		}
	}
}

int main()
{
	cin >> H >> W;
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++) cin >> ch[i][j];
	}
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			if (ch[i][j] == '.')
			{
				memset(visit, false, sizeof(visit));
				bfs(i, j);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：yzyjh (赞：0)

思路就是dfs跑遍整张图，找到可以到达的最大点。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

int n, m;
vector < vector < char > > s;
vector < vector < vector < pair < int, int > > > > g;

void ckmax (int &a, int x) {
	a = max(a, x);
}

int bfs (pair < int, int > root) {//bfs跑遍整张图
	vector < vector < int > > d(n, vector < int > (m, 0));
	vector < vector < bool > > used(n, vector < bool > (m, 0));
	queue < pair < int, int > > q;
	used[root.x][root.y] = 1;
	q.push(root);
	while (!q.empty()) {
		pair < int, int > u = q.front();
		q.pop();
		for (auto v: g[u.x][u.y]) {
			if (!used[v.x][v.y]) {
				used[v.x][v.y] = 1;
				d[v.x][v.y] = d[u.x][u.y] + 1;
				q.push(v);
			}
		}
	}
	int res = 0;
	for (vector < int > arr: d) 
		ckmax(res, *max_element(arr.begin(), arr.end()));
	return res;
}

signed main () {
	cin >> n >> m;
	s.assign(n, vector < char > (m));
	g.assign(n, vector < vector < pair < int, int > > > (m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> s[i][j];
			if (s[i][j] == '.') {//等于点的情况
				if (i && s[i - 1][j] == '.') {
					g[i][j].push_back(make_pair(i - 1, j));
					g[i - 1][j].push_back(make_pair(i, j));
				}
				if (j && s[i][j - 1] == '.') {
					g[i][j].push_back(make_pair(i, j - 1));
					g[i][j - 1].push_back(make_pair(i, j));
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '.')
				ckmax(ans, bfs(make_pair(i, j)));
		}
	}
	cout << ans << '\n';//输出
}
```


---

## 作者：小小小朋友 (赞：0)

### 题意描述

给出一个迷宫，求最长的路径

### 思路

从每个点开始跑bfs 计算每个点可到达的最远点。

解释见代码

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int fx[]={1,-1,0,0},fy[]={0,0,1,-1};
struct node{
	int x,y;
};
int n,m,ans=0;
int d[25][25];
char p[25][25];
bool vis[25][25];
queue<node> q;
int main(){
	memset(p,0x3f,sizeof(p));
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>p[i][j];//输入
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(p[i][j]=='#') continue;//如果这个点是墙 就跳过
			memset(d,0,sizeof(d));//清空两个数组
			memset(vis,0,sizeof(vis));
			q.push((node){i,j});
			vis[i][j]=1;
			while(!q.empty()){//开始bfs 模板
				node no=q.front();
				q.pop();
				for(int k=0;k<4;k++){
					int nx=no.x+fx[k],ny=no.y+fy[k];
					if(nx<n&&ny<m&&nx>=0&&ny>=0&&p[nx][ny]=='.'&&!vis[nx][ny]){
						vis[nx][ny]=1;
						d[nx][ny]=d[no.x][no.y]+1;
						ans=max(d[nx][ny],ans);//取最大距离作为答案 这里d每个点都会重置为0
						q.push((node){nx,ny});
					}
				}
			}
		}
	}
	printf("%d",ans);//输出答案即可
	return 0;
}

```

---

