# [ABC176D] Wizard in Maze

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc176/tasks/abc176_d

縦 $ H $ マス、横 $ W $ マスの $ H\times\ W $ マスからなる迷路があります。

上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ は、$ S_{ij} $ が `#` のとき壁であり、`.`のとき道です。

マス $ (C_h,C_w) $ に魔法使いがいます。魔法使いは次の $ 2 $ 種類の方法で移動することができます。

- 移動A：現在いるマスと上下左右に隣接する道のマスへ歩いて移動する。
- 移動B：現在いるマスを中心とする $ 5\times\ 5 $ の範囲内にある道のマスへワープ魔法で移動する。

どちらの行動でも、迷路の外へ移動することはできません。

マス $ (D_h,D_w) $ まで移動するには、ワープ魔法を最低で何度使う必要があるでしょうか。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 10^3 $
- $ 1\ \leq\ C_h,D_h\ \leq\ H $
- $ 1\ \leq\ C_w,D_w\ \leq\ W $
- $ S_{ij} $ は `#` か `.`
- $ S_{C_h\ C_w} $ と $ S_{D_h\ D_w} $ は `.`
- $ (C_h,C_w)\ \neq\ (D_h,D_w) $

### Sample Explanation 1

例えば $ (2,2) $ まで歩いて移動し、$ (2,2) $ から $ (4,4) $ へワープ魔法で移動することで、ワープ魔法の使用回数を $ 1 $ 回にできます。 歩いて斜めに移動することはできません。

### Sample Explanation 2

現在地から動くことができません。

### Sample Explanation 3

ワープ魔法を使う必要はありません。

## 样例 #1

### 输入

```
4 4
1 1
4 4
..#.
..#.
.#..
.#..```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4
1 4
4 1
.##.
####
####
.##.```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 4
2 2
3 3
....
....
....
....```

### 输出

```
0```

## 样例 #4

### 输入

```
4 5
1 2
2 5
#.###
####.
#..##
#..##```

### 输出

```
2```

# 题解

## 作者：KukCair (赞：5)

~~谁没事手撸魔法方向数组啊~~

### 正解：

题目上说最少使用几次魔法，因此一定是正常上下左右移动的优先级更高。

bfs 的特点就是会先算队首，这也就意味着队首的优先级更高。

从队首入队，需要使用 `deque`。此题中的 `step` 数组用于记录到当前点用了多少次魔法。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct p{
    int x, y;
};
int h, w, a, b, x, y, step[1005][1005];
//正常上下左右移动
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
//魔法方向数组
int sy[] = {-2, -1, 0, 1, 2, -2, -1, 0, 1, 2, -2, -1, 1, 2, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2};
int sx[] = {-2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
void bfs(){
    deque<p> q;//双端队列
    q.push_back({a, b});//初始起点入队
    step[a][b] = 0;//初始时最少使用0次魔法
    while(!q.empty()){
        int mx = q.front().x, my = q.front().y;
        q.pop_front();
        for(int i = 0; i <= 3; i++){//上下左右移动的
            int nx = mx + dx[i], ny = my + dy[i];
            //越界
            if(nx > h || ny > w || nx < 1 || ny < 1)continue;
            //一个点可以重复走过，但如果新的次数还大于原来的就不用往下找了，一定不会是最优解
            if(m[nx][ny] == '#' || step[nx][ny] <= step[mx][my])continue;
            step[nx][ny] = step[mx][my];
            q.push_front({nx, ny});//正常的优先级高，放前面
        }
        for(int i = 0; i <= 23; i++){//使用魔法的
            int nx = mx + sx[i], ny = my + sy[i];
            if(nx > h || ny > w || nx < 1 || ny < 1)continue;
            if(m[nx][ny] == '#' || step[nx][ny] <= step[mx][my] + 1)continue;
            step[nx][ny] = step[mx][my] + 1;
            q.push_back({nx, ny});//使用魔法的的优先级低，放后面
        }
    }
    if(step[x][y] != 0x3f3f3f3f) cout << step[x][y];//能走到
    else cout << -1;
}
int main(){
    memset(step, 0x3f, sizeof(step));//初始化，以免在取最小值时全为0
    cin >> h >> w >> a >> b >> x >> y;
    for(int i = 1; i <= h; i++)
        for(int j = 1; j <= w; j++)
            cin >> m[i][j];
    bfs();
    return 0;
}
```

---

## 作者：xibaohe (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc176_d)
# 题目翻译
迷宫由 $H$ 行 $W$ 列的格子组成。第 $i$ 行第 $j$ 列的格子 $(i,j)$ 用字符 $S_{i,j}$ 表示，井号表示墙壁，英文句号表示道路。

在格子 $(C_h,C_w)$ 有一个魔女，她可以用以下两种方式移动:
 - 移动到上下左右相邻的道路格子。
 - 使用折跃魔法，直接移动到以当前所在位置为中心的 $5×5$ 范围内的一个道路格子。
 
魔女想要到格子 $(D_h,D_w)$，她至少需要使用多少次折跃魔法?

# 题目思路
这是一道双端队列模板题，这里先给大家展示普通的队列广搜模板：
```cpp
#include<iostream>
#include<queue>
using namespace std;

int n, m, a[55][55], x1, y1, x2, y2;
bool vis[55][55];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct node
{
	int x, y, t;
};

queue<node> q;

int bfs()
{
	q.push(node{x1, y1, 0});
	vis[x1][y1] = true;
	while(!q.empty())
	{
		int x = q.front().x, y = q.front().y, t = q.front().t;
		if(x == x2 && y == y2) return t;
		q.pop();
		for(int i = 0; i <= 3; i++)
		{
			int x_new = x + dx[i], y_new = y + dy[i];
			
			if(x_new < 1 || x_new > n || y_new < 1 || y_new > m) continue;
			if(vis[x_new][y_new] == true) continue;
			if(a[x_new][y_new] == 0) continue;
			
			q.push(node{x_new, y_new, t + 1});
			vis[x_new][y_new] = true;
		}
	}
	return -1;
}

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%1d", &a[i][j]);
	cin >> x1 >> y1 >> x2 >> y2;
	
	cout << bfs() << endl;
	
	return 0;
}//模板
```
这道题需要用双端队列的原因是有两种优先级不同的移动方式：
 - 移动到上下左右相邻的道路格子。
 - 使用折跃魔法，直接移动到以当前所在位置为中心的 $5×5$ 范围内的一个道路格子。
 
由于需要求出折跃魔法次数最少的方式，因此第一种移动优先级最高，可以插入到队列前段，后一种则需要插入道队列后端。

# 双端队列
不清楚双端队列如何使用的同志们可以点开下面的链接去做一下链接里面的题：

[B3656 【模板】双端队列 1](https://www.luogu.com.cn/problem/B3656)

# 满分代码
```cpp
#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

int h, w, ch, cw, dh, dw, dis[1005][1005];
//dis[i][j]表示从(ch, cw)出发到达(i, j)所消耗跳跃魔法次数的最小值
char a[1005][1005];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

struct node
{ //从(ch, cw)出发到达(x, y)所消耗跳跃魔法次数的最小值t
	int x, y, t;
};

deque<node> q;

void bfs()
{
	q.push_front(node{ch, cw, 0});
	dis[ch][cw] = 0;
	
	while(!q.empty())
	{
		int x = q.front().x, y = q.front().y, t = q.front().t;
		q.pop_front();
		
		//(x,y)普通移动能达到的子结点插入队首
		for(int i = 0; i <= 3; i++)
		{
			int x_new = x + dx[i], y_new = y + dy[i];
			if(x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
			if(a[x_new][y_new] == '#') continue;
			if(dis[x_new][y_new] <= dis[x][y]) continue;
			q.push_front(node{x_new, y_new, t});
			dis[x_new][y_new] = t;
		}
		
		//(x,y)跳跃魔法移动能达到的子结点插入队尾
		for(int x_new = x - 2; x_new <= x + 2; x_new++)
			for(int y_new = y - 2; y_new <= y + 2; y_new++)
			{
				if(x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
				if(a[x_new][y_new] == '#') continue;
				if(dis[x_new][y_new] <= dis[x][y] + 1) continue;
				q.push_back(node{x_new, y_new, t + 1});
				dis[x_new][y_new] = t + 1;
			}
	}
}

int main()
{
	cin >> h >> w;
	cin >> ch >> cw;
	cin >> dh >> dw;
	for(int i = 1; i <= h; i++)
		for(int j = 1; j <= w; j++)
			cin >> a[i][j];
			
	memset(dis, 0x3f, sizeof(dis));
	bfs();
	
	if(dis[dh][dw] == 0x3f3f3f3f) cout << -1 << endl;
	else cout << dis[dh][dw] << endl;
	
	return 0;
}
```



---

## 作者：shaozhehan (赞：3)

[原题链接](https://www.luogu.com.cn/problem/AT_abc176_d)

[Atcoder 链接](https://atcoder.jp/contests/abc176/tasks/abc176_d)

题目大意：

一个人在迷宫里，有可走的点和不可走的点，他即可以移动到上、下、左、右，又可以使用魔法，让自己移动到以自己为中心的 $5\times 5$ 的正方形内任意可走的点，求这个人从起点到终点使用魔法的最小次数。

思路：

这一个题一看就是 BFS，我们采用双端队列 ```deque``` 解决此题。我们用结构体来存储情况，放到双端队列里。显然移动到上、下、左、右优先级更高，所以对于这种情况我们使用 ```push_front``` 函数，即把这种情况放到双端队列的队头。第二种情况就是使用魔法，优先级更低，我们使用 ```push_back``` 函数，把这种情况放到队尾。在搜索的过程中。我们用一个 $dis$ 数组，$dis(r,c)$ 表示从起点到坐标 $(c,r)$ 所需的魔法次数。

上代码：
```cpp
#include <deque>
#include <cstring>
#include <iostream>
using namespace std;

string a[1001];// 迷宫地图
int dis[1001][1001];
const int dx[4] = {-1, 1}, dy[4] = {0, 0, -1, 1};// 往上、下、左、右时行和列的编号需要加的数

struct node{
    int x, y, step;
};// 每一个情况，在 x 行 y 列使用了 step 次魔法
deque<node> dq;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int h, w, ch, cw, dh, dw;
    cin >> h >> w >> ch >> cw >> dh >> dw;
    for (int i = 1; i <= h; i++){
        cin >> a[i];
        a[i] = " " + a[i];
    }
    memset(dis, 63, sizeof(dis));
    node temp, ntemp;
    // 初始情况入队
    temp.x = ch;
    temp.y = cw;
    temp.step = 0;
    dis[ch][cw] = 0;
    dq.push_back(temp);
    while (!dq.empty()){
        // 保存情况、取出队头
        temp = dq.front();
        dq.pop_front();
        // 第一种情况：往上、下、左、右移动
        ntemp.step = temp.step;
        for (int i = 0; i < 4; i++){
            int nx = temp.x + dx[i], ny = temp.y + dy[i];
            if (1 <= nx && nx <= h && 1 <= ny && ny <= w && a[nx][ny] != '#' && dis[nx][ny] > dis[temp.x][temp.y]){
                // 注意：点可以重复，但是如果有一个情况比原来标记的情况还要多，那么就不用管它
                ntemp.x = nx;
                ntemp.y = ny;
                dq.push_front(ntemp);
                dis[nx][ny] = ntemp.step;
            }
        }
        ntemp.step = temp.step + 1;
        for (int i = temp.x - 2; i <= temp.x + 2; i++){
            for (int j = temp.y - 2; j <= temp.y + 2; j++){// 坐标枚举
                if (1 <= i && i <= h && 1 <= j && j <= w && a[i][j] != '#' && dis[i][j] > dis[temp.x][temp.y] + 1){
                    // 注意：这里要改成 dis[temp.x][temp.y] + 1，因为已经使用了一次魔法
                    ntemp.x = i;
                    ntemp.y = j;
                    dq.push_back(ntemp);
                    dis[i][j] = temp.step + 1;
                }
            }
        }
    }
    if (dis[dh][dw] == 0x3f3f3f3f){// 注意：如果无解就输出 -1
        cout << "-1\n";
    } else {
        cout << dis[dh][dw] << "\n";
    }
    return 0;
}
```

---

## 作者：hellolin (赞：1)


[题面(洛谷)](https://www.luogu.com.cn/problem/AT_abc176_d)

[题面(AtCoder)](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc176_d)

## 题意

- $H$ 行 $W$ 列的方格，每个方格都是 `#`（墙）或者 `.`（路）。
- 魔术师一开始在位置 $(C_h, C_w)$，他想到达位置 $(D_h, D_w)$。
- 魔术师有两种移动方式：上下左右走，或者使用魔法瞬移到以当前格为中心的 $5 \times 5$ 正方形中任意一格。
- 问魔术师最少用几次瞬移魔法能到目标位置。

## 思路

一道很适合练习广搜 (BFS) 的题。

第二种方法要尽量少用，所以可以试着能否通过第一种方法走到终点，如果不能就用一下下第二种方法，继续重复判断能否走到终点。

基于上面的想法，可以开一个双端队列，第一种方法的优先级高，所以把第一种走的方法压在队列前面，第二种方法压在队列后面。

其余的细节都写在代码里啦！

## 代码

``` cpp
// Coder          : Hellolin
// Time           : 2023-02-06 12:32:38
// Problem        : [ABC176D] Wizard in Maze
// Contest        : Luogu
// URL            : https://www.luogu.com.cn/problem/AT_abc176_d
// Time Limit     : 2000 ms
// Memory Limit   : 1 GiB

#include <iostream>
#include <utility> // pair 大法好
#include <deque>
#include <cstring>
using namespace std;
#define pi pair<int, int>
#define fi first
#define se second
#define rep(x, y, z) for (int x = y; x <= z; x++)

const int MAX = 1e3 + 114;

deque<pi> a;
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};
int path[MAX][MAX];

int h, w, ans;
// 开始位置 结束位置 当前位置 下一个移动位置
pi str, fin, now, mv;
char tmp;
bool img[MAX][MAX];

void init()
{
    ans = -1;
    memset(path, -1, sizeof(path));
    // 记得起始位置 path 设 0
    path[str.fi][str.fi] = 0;
    a.clear();
    // 在前面压一个开始位置
    a.push_front(str);
}

void bfs()
{
    while (a.size()) // while (!a.empty())
    {
        now = a.front();
        a.pop_front();

        if (now == fin) // 到终点了
        {
            ans = path[now.fi][now.se];
            return;
        }

        // 上下左右四个方向
        rep(i, 1, 4)
        {
            mv = now;
            mv.fi += dx[i];
            mv.se += dy[i];

            if (mv.fi < 1 || mv.fi > h || mv.se < 1 || mv.se > w) // 越界检查
                continue;

            if (!img[mv.fi][mv.se])
            {
                // 当前这条路还没走过，或者当前这条路使用过魔法次数较少
                if (path[mv.fi][mv.se] == -1 || path[mv.fi][mv.se] > path[now.fi][now.se])
                {
                    // 普通移动，放到队首
                    a.push_front(mv);
                    // 普通移动不需要 +1
                    path[mv.fi][mv.se] = path[now.fi][now.se];
                }
            }
        }

        // 以当前方格为中心的 5x5
        rep(x, now.fi - 2, now.fi + 2)
        {
            rep(y, now.se - 2, now.se + 2)
            {
                if (x < 1 || x > h || y < 1 || y > w) // 越界检查
                    continue;

                if (!img[x][y])
                {
                    // 当前这条路还没走过
                    if (path[x][y] == -1)
                    {
                        // 魔法移动，放到队尾
                        a.push_back({x, y});
                        // 魔法移动记得 +1
                        path[x][y] = path[now.fi][now.se] + 1;
                    }
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> h >> w;

    cin >> str.fi >> str.se;
    cin >> fin.fi >> fin.se;

    rep(i, 1, h)
    {
        rep(j, 1, w)
        {
            cin >> tmp;
            img[i][j] = (tmp == '#'); // 记 墙=1 路=0
        }
    }

    init();
    bfs();

    cout << ans << endl;

    return 0;
}
```


---

## 作者：DHT666 (赞：0)

## 题意
[传送门](https://www.luogu.com.cn/problem/AT_abc176_d)

给定一个有障碍的迷宫，每次移动可以上下左右移动一格，或使用魔法传送至**以当前点为中心的 $5\times 5$ 正方形区域内任意一点**，问从给定的起点移动至终点最少使用魔法的次数。

## 思路
因为是求最小次数，所以考虑宽搜。

有两种移动方式，但想要使用魔法的次数最少，那么就尽量先用走路的方式。

转换为宽搜，开双端队列，用走路的方式就插入至队头，用魔法就插入至队尾。

## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1010;

int sx,sy,ex,ey;
int n,m; 
bool Map[N][N]; // 存图 
int ans[N][N]; // 记录答案 
int dx[] = {0,1,-1,0,0}; // 增量数组 
int dy[] = {0,0,0,1,-1};

struct node {
	int x,y;
};

void bfs() {
	deque<node> q; // 如上，双端队列 
	node x; x.x = sx,x.y = sy;
	q.push_back(x);
	memset(ans,0x3f,sizeof ans); // 要初始化 
	ans[sx][sy] = 0;
	while(q.size()) {
		node tot = q.front();
		q.pop_front();
		if(tot.x == ex && tot.y == ey) { // 到达终点 
			cout<<ans[ex][ey];
			return;
		}
		for(int i=1;i<=4;i++) {
			int nx = tot.x + dx[i];
			int ny = tot.y + dy[i];
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && Map[nx][ny] && ans[nx][ny] > ans[tot.x][tot.y]) { // 没越界、可走、没走过 
				ans[nx][ny] = ans[tot.x][tot.y]; // 记录答案 
				node qwq; qwq.x = nx,qwq.y = ny;
				q.push_front(qwq); // 是走路的情况，队头入队 
			}
		}
		for(int i=-2;i<=2;i++) { // 5 * 5 的范围 
			for(int j=-2;j<=2;j++) {
				if(i == 0 && j == 0) continue; // 原地踏步 
				int nx = tot.x + i;
				int ny = tot.y + j;
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && Map[nx][ny] && ans[nx][ny] > ans[tot.x][tot.y] + 1) { // 没越界、可走、没走过 
					ans[nx][ny] = ans[tot.x][tot.y] + 1; // 记录答案 
					node qwq; qwq.x = nx,qwq.y = ny; 
					q.push_back(qwq); // 使用魔法，队尾入队 
				}
			}
		}
	}
	cout<<-1; // 无解 
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>sx>>sy>>ex>>ey;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			char x; cin>>x;
			if(x == '.') Map[i][j] = 1; // '.' 表示没有障碍 
		}
	}
	
	bfs();
	 
	return 0;
}
~~~

---

## 作者：GenesisCrystal (赞：0)

## Solution

由题，我们可以知道这是一道 01BFS 的题目，所以采用双端队列解决。

对于上下左右的格子，边权为 $0$；对于 $5 \times 5$ 的方格内的格子，边权为 $1$。然后跑 01BFS 就行了。

## Code

```cpp
#include <iostream>
#include <deque>

using namespace std;

const int kMaxN = 1001, kD[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int f[kMaxN][kMaxN];
int n, m, sx, sy, ex, ey;
char a[kMaxN][kMaxN] = {};
struct Node {
	int x, y, s;
	Node(int x, int y, int s) : x(x), y(y), s(s) {}
};
deque<Node> q;

void REcord(int nx, int ny, int os, bool j) {
	if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#' || f[nx][ny] <= os + j) {
		return;
	}
	f[nx][ny] = os + j;
	if (!j) {
		q.push_front(Node(nx, ny, f[nx][ny]));
	} else {
		q.push_back(Node(nx, ny, f[nx][ny]));
	}
}

int Bfs() {
	q.push_front(Node(sx, sy, 0));
	f[sx][sy] = 0;
	while (!q.empty()) {
		Node t = q.front();
		q.pop_front();
		for (int i = 0; i < 4; i++) {
			REcord(t.x + kD[i][0], t.y + kD[i][1], t.s, 0);
		}
		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				REcord(t.x + i, t.y + j, t.s, 1);
			}
		}
	}
	return f[ex][ey] == 1e9 ? -1 : f[ex][ey];
}

int main() {
	cin >> n >> m >> sx >> sy >> ex >> ey;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			f[i][j] = 1e9;
		}
	}
	cout << Bfs();
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

经典题型啊，两种走的方式，一种有代价，一种没代价，那肯定是优先考虑没代价的，然后考虑有代价的，像这种类型的题目就可以考虑双端队列，每次将通过上下左右走动得到的点放入队列前端，这样下次会优先取到，而要用魔法的就往后面放。用一个数组单独储存答案，如果说出现更优方案就替换，再放入队列。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e3+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,m,ans[N][N];
char mp[N][N];
pii s,e;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
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
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
void bfs()
{
	memset(ans,inf,sizeof ans);
	deque<pii> q;
	q.push_front(s);
	ans[s.x][s.y]=0;
	while(!q.empty())
	{
		pii t=q.front();
		q.pop_front();
		rep1(i,0,3)
		{
			int tx=t.x+dx[i];
			int ty=t.y+dy[i];
			if(tx>=0&&tx<=n&&ty>=0&&ty<=m&&mp[tx][ty]=='.'&&ans[tx][ty]>ans[t.x][t.y])
			{
				ans[tx][ty]=ans[t.x][t.y];
				q.push_front(make_pair(tx,ty));
			}
		}
		rep1(ix,-2,2)
		{
			rep1(iy,-2,2)
			{
				int tx=t.x+ix;
				int ty=t.y+iy;
				if(tx>=0&&tx<=n&&ty>=0&&ty<=m&&mp[tx][ty]=='.'&&ans[tx][ty]>ans[t.x][t.y]+1)
				{
					ans[tx][ty]=ans[t.x][t.y]+1;
					q.push_back(make_pair(tx,ty));
				}
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
	s.x=read();
	s.y=read();
	e.x=read();
	e.y=read();
	rep1(i,1,n) rep1(j,1,m) cin>>mp[i][j];
	bfs();
//	rep1(i,1,n)
//	{
//		rep1(j,1,m) cout<<ans[i][j]<<' ';
//		putchar('\n');
//	}
	if(ans[e.x][e.y]>=inf) puts("-1");
	else cout<<ans[e.x][e.y]<<endl;
	return 0;
}

```

---

## 作者：ruanwentao666 (赞：0)

# [ABC176D] Wizard in Maze 题解
[题目面板(洛谷)](https://www.luogu.com.cn/problem/AT_abc176_d)

## 化繁为简
对于题目的描述，我们可以总结出两种移动方式：

- 他可以向上、下、左、右移动一次。

- 他可以使用一次魔法，将他移动到他现在的位置为中心的 $5 \times 5$ 的正方形中的任意位置。

现在，我们不考虑第二种移动方式，只考虑第一种。那这第一种移动方式就是广搜的模版代码，直接给出：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, sc, sr, ec, er;
char a[1005][1005];
int vis[1005][1005];
int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
struct node {
	int x, y;
};
void bfs() {
	queue<node>d;
	d.push((node) { sc, sr });
	vis[sc][sr] = 1;
	while (!d.empty()) {
		node q = d.front();
		d.pop();
		for (int i = 0; i < 4; i++) {
			int nx = q.x + dir[i][0], ny = q.y + dir[i][1];
			if (nx >= 1 && ny >= 1 && nx <= n && ny <= m && vis[nx][ny] && a[nx][ny] == '.') {
				d.push((node) { nx, ny });
				vis[nx][ny] = 1;
			}
		}
	}
}
int main() {
	cin >> n >> m >> sc >> sr >> ec >> er;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	bfs();
	if (!vis[ec][er])cout << "-1\n";
	else cout << vis[ec][er] << "\n";
	return 0;
}

```

接下来我们将考虑第二种移动方式。

### 优先级划分

请读者思考一下，上面提到的两种移动方法哪一种的优先级更高呢？

由于题目中说“最少使用几次魔法才能到位置”，所以不用魔法的移动方式显然优先级更高，即第一种方法优先级更高。

### 普通队列升级

既然第一种移动方式优先级更高，那么我们每次执行第一种移动方式时都应该将得到的结果放入队头，不应该是从队尾插入。所以，我们需要使用双端队列，在 C++ 中可以使用 deque 容器。不熟悉的读者可以去做一下[B3656](https://www.luogu.com.cn/problem/B3656)。

### 思路分析

按照广搜的思路，我们每次将第一种移动方式插入队头，将第二种移动方式插入队尾，其余不变。

## 代码展示
附上 AC 代码：
```cpp
#include<iostream>
#include<deque>
#include<cstring>
using namespace std;
int n, m, sc, sr, ec, er;
char a[1005][1005];
int vis[1005][1005];
int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
struct node {
	int x, y, tim;
};
void bfs() {
	deque<node>d;
	d.clear();
	d.push_front((node) { sc, sr, 0 });
	vis[sc][sr] = 0;
	while (!d.empty()) {
		node q = d.front();
		d.pop_front();
		for (int i = 0; i < 4; i++) {
			int nx = q.x + dir[i][0], ny = q.y + dir[i][1];
			if (nx >= 1 && ny >= 1 && nx <= n && ny <= m && vis[nx][ny] > vis[q.x][q.y] && a[nx][ny] == '.') {
				d.push_front((node) { nx, ny, vis[q.x][q.y] });
				vis[nx][ny] = vis[q.x][q.y];
			}
		}
		for (int i = max(q.x - 2, 1); i <= min(q.x + 2, n); i++) {
			for (int j = max(q.y - 2, 1); j <= min(q.y + 2, m); j++) {
				if (vis[i][j] > vis[q.x][q.y] + 1 && a[i][j] == '.') {
					d.push_back((node) { i, j, vis[q.x][q.y] + 1 });
					vis[i][j] = vis[q.x][q.y] + 1;
				}
			}
		}
	}
}
int main() {
	cin >> n >> m >> sc >> sr >> ec >> er;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	memset(vis, 0x3f, sizeof(vis));
	bfs();
	if (vis[ec][er] == 0x3f3f3f3f)cout << "-1\n";
	else cout << vis[ec][er] << "\n";
	return 0;
}

```

---

## 作者：happy_zero (赞：0)

首先要明白，这题是用用队列实现的 `bfs` 解决。如果要移动，有两种办法：首先是直接走，另一种是使用魔法。由于题目中说的是要使用魔法的次数最少，所以应该尽量用第一个魔法，这就可以用一个双端队列来实现 `bfs`，如果用的是第一种方法移动到的，就放入队首，否则就放入队尾。

要注意的小细节：
- 无论是否使用魔法，走到的地方都必须是 `.`；
- 只要比当前距离来得优，就是可以重复进队的。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
struct node
{
	int x;
	int y;
};
int n, m;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int dis[N][N];//记录起点到每个点的最少使用魔法次数
char a[N][N];
deque <node> q;
bool chk(int x, int y)//判断到的点是否合法
{
	if (x < 1 || x > n) return 0;
	if (y < 1 || y > m) return 0;
	if (a[x][y] == '#') return 0;
	return 1;
}
int main()
{
	int sx, sy, tx, ty;
	cin >> n >> m;
	cin >> sx >> sy >> tx >> ty;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	memset(dis, 0x3f, sizeof(dis));//所有都先赋成 INF
	q.push_back((node){sx, sy});
	dis[sx][sy] = 0;
	while (!q.empty())
	{
		node t = q.front();
		q.pop_front();
		int s = dis[t.x][t.y];
		for (int i = 0; i < 4; i++)//不用魔法
		{
			int nx = t.x + dx[i];
			int ny = t.y + dy[i];
			if (!chk(nx, ny)) continue;
			if (dis[nx][ny] > s)//只有比当前距离来得近才入队
			{
				dis[nx][ny] = s;
				q.push_front((node){nx, ny});
			}
		}
		for (int i = -2; i <= 2 ; i++)//不使用魔法
			for (int j = -2; j <= 2; j++)
			{
				int nx = t.x + i;
				int ny = t.y + j;
				if (!chk(nx, ny)) continue;
				if (dis[nx][ny] > s + 1)
				{
					dis[nx][ny] = s + 1;
					q.push_back((node){nx, ny});
				}
			}
	}
	if (dis[tx][ty] != dis[0][0]) cout << dis[tx][ty];
	else cout << -1;//注意还要判断无解的情况
	return 0;
}
```


---

## 作者：nyC20 (赞：0)

[AC记录](https://www.luogu.com.cn/record/145129795)
[题目传送门](https://www.luogu.com.cn/problem/AT_abc176_d)
# 思路
双向宽搜板子题，对于每一个点，都可以到达上下左右直接相邻的点，或者使用魔法到达以该点为中心的 $5 \times 5$ 的正方形以内的任意位置。最后求最小的魔法使用次数。注意范围和移动的方式，再加上剪枝就能 AC。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
pair<int,int> Start,End;
bool Map[1050][1050];//地图 
int used[1050][1050];//剪枝 
char tp;
deque<pair<int,int> > que;
int dx[4] = {1,-1,0,0};//正常移动 
int dy[4] = {0,0,-1,1};
int ddx[20] = {-2,-1,0,1,2,-2,-1,1,2,-2,2,-2,-1,1,2,-2,-1,0,1,2};//魔法移动 
int ddy[20] = {2,2,2,2,2,1,1,1,1,0,0,-1,-1,-1,-1,-2,-2,-2,-2,-2};
int bfs(){//宽搜 
	que.push_front(Start);//起点 
	used[Start.first][Start.second] = 0;
	while(que.size()){
		int x,y;
		x = que.front().first;
		y = que.front().second;
		que.pop_front();
		if(x == End.first && y == End.second){//到达终点 
			return used[x][y];
		}
		for(int i = 0; i < 4; i++){//正常移动 
			if(x+dx[i] < 1 || x+dx[i] > n || y+dy[i] < 1 || y+dy[i] > m){
				continue;
			}
			if(Map[x+dx[i]][y+dy[i]] || used[x+dx[i]][y+dy[i]] <= used[x][y]){
				continue;
			}
			que.push_front({x+dx[i],y+dy[i]});
			used[x+dx[i]][y+dy[i]] = used[x][y];
		}
		for(int i = 0; i < 20; i++){//魔法移动 
			if(x+ddx[i] < 1 || x+ddx[i] > n || y+ddy[i] < 1 || y+ddy[i] > m){
				continue;
			}
			if(Map[x+ddx[i]][y+ddy[i]] || used[x+ddx[i]][y+ddy[i]] <= used[x][y]+1){
				continue;
			}
			que.push_back({x+ddx[i],y+ddy[i]});
			used[x+ddx[i]][y+ddy[i]] = used[x][y]+1;
		}
	}
	return -1;
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&m,&Start.first,&Start.second,&End.first,&End.second);
	for(int i = 1; i <= n; i++){//存地图 
		scanf("\n");
		for(int j = 1; j <= m; j++){
			scanf("%c",&tp);
			if(tp == '#'){
				Map[i][j] = 1;
			}
		}
	}
	memset(used,0x3f,sizeof(used));
	printf("%d",bfs());
	return 0;
}
```


---

