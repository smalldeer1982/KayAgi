# [BalticOI 2011] Treasures and Vikings (Day1)

## 题目描述

You have a treasure map that is arranged into a $N \times M$ grid. A grid square may be either sea or part of an island. In addition, the map shows the treasure and an enemy Viking ship that occupies one (sea) square. Finally, for convenience you have also drawn your own position.

Now you must set up a fixed route to get the treasure. The route must start at your position, end at the treasure, and consist of a sequence of moves. In each move, you can go only to an (horizontally or vertically) adjacent square that is not part of an island. But beware: The Viking ship might follow you, using the same kind of moves! After each of your moves according to your route, the Viking ship may move or not. Your move and the Vikings’ reaction together is called a round.

After every round, the following checks are made:

-    If you are in line with the Viking ship (you are in the same vertical or horizontal line as the Viking ship with only sea between the Viking ship and you), you are dead.
-    If you aren’t dead and at the treasure-spot, you get the treasure.

Write a program that decides whether it is possible to set up a fixed route in advance such that you can get the treasure by following this route and will not get killed by the Vikings – no matter how the Viking ship moves.

## 说明/提示

**Sample Explanation 1**

The route is:go down for three times,go right for three times too,go down at last.

**数据范围**

对于 $50\%$ 的数据，$1 \le N,M \le 200$。

对于所有数据，$1 \le N,M \le 700$。

## 样例 #1

### 输入

```
5 7
Y.....V
..I....
..IIIII
.......
...T...```

### 输出

```
YES```

## 样例 #2

### 输入

```
5 7
Y....V.
..I....
..IIIII
.......
...T...```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 3
.YT
VII```

### 输出

```
NO```

# 题解

## 作者：Cutata (赞：2)

#### 题意简述

-   本题翻译不全，重点：$Y$ 是你的船，$V$ 是贼船，$I$ 是岛屿，$T$ 是宝藏；你需要尽可能避免贼船攻击到你的船，并拿到宝藏。
-   贼船的攻击范围：以它能走到的每个点为中心，分别画一条垂直线和水平线，**直到碰到边界或岛屿才停止**。
-   由第三个样例可以看出，如果你的船出现在贼船下一步的攻击范围内，你同样会挂，**所以本题可以理解为贼船先走**。

#### 题目分析

-   本题与求最短路思想类似，并且数据范围 $1 \le N,M \le 700$，可以直接宽搜。
-   涉及到两个点的移动，为了提高效率，可以采取**同步宽搜**的方法，即定义两个队列，对它们同时进行入队出队操作。
-   优先对贼船的队列进行扩展，将其攻击范围打上标记。判出条件：你的船的队列为空（或者头指针 $>$ 尾指针），**注意与贼船的队列无关**。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 700 + 10;
bool visp[MAXN][MAXN], visq[MAXN][MAXN], tmap[MAXN][MAXN];
struct node{
	int x, y, step;
}q[MAXN * MAXN], p[MAXN * MAXN];
int n, m, ansx, ansy, frontp = 1, rearp = 1, frontq = 1, rearq = 1, tx, ty, nx, ny;
int dx[] = {0, 0, 1, 0, -1};
int dy[] = {0, 1, 0, -1, 0};
bool checkp(int x, int y)//判断贼船是否能走
{
	if(x < 1 or x > n or y < 1 or y > m or visp[x][y] or tmap[x][y])
	    return false;
	return true;
}
bool checkq(int x, int y)//判断你的船是否能走
{
	if(x < 1 or x > n or y < 1 or y > m or visq[x][y] or tmap[x][y])
	    return false;
	return true;
}
bool checkt(int x, int y)//判断贼船是否能攻击此格
{
	if(x < 1 or x > n or y < 1 or y > m or tmap[x][y])
	    return false;
	return true;
}
void bfs()
{
	while(frontq <= rearq){//判出
		for(int i = 0; i < 5; i++){//先对贼船队列进行扩展
			tx = p[frontp].x + dx[i];
			ty = p[frontp].y + dy[i];
			if(checkp(tx, ty)){
				rearp++;
				p[rearp].x = tx;
				p[rearp].y = ty;
				p[rearp].step = p[frontp].step + 1;
				visp[tx][ty] = visq[tx][ty] = true;
				nx = tx, ny = ty;
				while(checkt(nx - 1, ny)){//对四个方向进行攻击
					nx--;
					visq[nx][ny] = true;
				}
				nx = tx, ny = ty;
				while(checkt(nx, ny - 1)){
					ny--;
					visq[nx][ny] = true;
				}
				nx = tx, ny = ty;
				while(checkt(nx + 1, ny)){
					nx++;
					visq[nx][ny] = true;
				}
				nx = tx, ny = ty;
				while(checkt(nx, ny + 1)){
					ny++;
					visq[nx][ny] = true;
				}
			}
		}
		for(int i = 1; i < 5; i++){//对你的船的队列进行扩展
			tx = q[frontq].x + dx[i];
			ty = q[frontq].y + dy[i];
			if(checkq(tx, ty)){
				rearq++;
				q[rearq].x = tx;
				q[rearq].y = ty;
				q[rearq].step = q[frontq].step + 1;
				visq[tx][ty] = true;
				if(q[rearq].x == ansx and q[rearq].y == ansy){//找到宝藏
			        cout << "YES";
			        return;
		        }
			}
		}
		frontp++;
		if(q[frontq + 1].step < p[frontp].step)
		    frontq++, frontp--;//算法核心，保证两艘船的行动在同一时刻
	}
	cout << "NO";
}
int main()
{
	ios::sync_with_stdio(false);//优化，打消输入输出缓存
	cin >> n >> m;
	char ch;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> ch;
			if(ch == '.')
			    continue;
			if(ch == 'Y'){
				q[1].x = i;
				q[1].y = j;
				visq[i][j] = true;
			}
			else if(ch == 'V'){
				p[1].x = i;
				p[1].y = j;
				visq[i][j] = true;
			}
			else if(ch == 'I')
			    tmap[i][j] = true;
			else{
				ansx = i;
				ansy = j;
			}	
	    }
	}
	bfs();
	return 0;
}
```

---

## 作者：XYY1411 (赞：2)

提交地址：[洛谷 Luogu4668](https://www.luogu.com.cn/problem/P4668)，[洛谷 SP10128](https://www.luogu.com.cn/problem/SP10128)，[Sphere online judge SP10128](https://www.spoj.com/problems/TANDV/)

## 题目大意

有 $n \times m$ 的地图，地图上可能有海（`.`）、陆地（`I`）、你的船（`Y`）、维京船（`V`）和宝藏（`T`）。

你的目的是在不被维京人干掉的情况下得到宝藏。

你和维京船每回合可以移动到一个四联通块，也可以不移动，每个回合你先移动。

维京船会在回合结束时攻击与其在同一列或同一行的船，攻击不能穿过陆地。

如果有一条路径，使得无论维京船如何移动你都能得到宝藏，输出 `YES` 否则输出 `NO`。

## 分析

数据范围是 $n, m \le 700$，考虑直接广搜暴搜。

先看一个简单的问题：

有一张 $n \times m$ 的地图，地图上有个怪物，你和怪物每回合可以移动到一个四联通块，也可以不移动，问对于第 $i$ 个回合，哪里是安全的（怪物移动不到）。

答案很显然，直接让怪物扩展 $i$ 次，没扩展到的地方都是安全的。

那么这道题同理，我们每回合都让自己和维京扩展一格，然后给维京船能攻击到的地方打上标记即可。

注意如何打标记，我们准备两种标记，一种是竖着攻击，一种是横着攻击，如果这一格已经打过一种标记了不用再打第二次，但是另一种还是要打。

这样可以保证每个格最多只打两次标记，复杂度为 $O(nm)$。

整体复杂度 $O(nm)$。

## $\rm\color{Green}code$

```cpp
#include <cstring>
#include <cstdio>
#include <cctype>
#include <queue>
#include <cstdlib>
using namespace std;
// 枚举类型，用于存储每个格子状态，这么写可以将每个状态压到一个二进制位内
enum crt{land = 0, sea = 1, trea = 2, you = 4, youvis = 8, vik = 16, vikvis = 32, atkw = 64, atkh = 128};
constexpr int maxn = 705;
inline void print(bool t) {
    puts(t ? "YES" : "NO");
    exit(0);
}
int mp[maxn][maxn];
char s[maxn];
int n, m;
int yx, yy, vx, vy, sx, sy;
// 给维京船能攻击到的地方打标记
void vikatk(int x, int y) {
    mp[x][y] |= vikvis;
    if (!(mp[x][y] & atkw)) { // 打过了跳，下面同理
        for (int j = y; j > 0; --j)
            if (mp[x][j] & sea)
                mp[x][j] |= atkw;
            else
                break;
        for (int j = y; j <= m; ++j)
            if (mp[x][j] & sea)
                mp[x][j] |= atkw;
            else
                break;
    }
    if (!(mp[x][y] & atkh)) {
        for (int i = x; i > 0; --i)
            if (mp[i][y] & sea)
                mp[i][y] |= atkh;
            else
                break;
        for (int i = x; i <= n; ++i)
            if (mp[i][y] & sea)
                mp[i][y] |= atkh;
            else
                break;
    }
}
struct node {
    int x, y, p;
};
constexpr int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
queue<node> vm;
queue<node> ym;
// 维京船移动
void vikmove() {
    static int p = 0;
    ++p;
    while (!vm.empty() && vm.front().p <= p) {
        int x = vm.front().x, y = vm.front().y;
        vm.pop();
        for (int k = 0; k < 4; ++k) {
            int tx = x + dx[k], ty = y + dy[k];
            if (mp[tx][ty] == land) continue;
            if (!(mp[tx][ty] & vikvis)) {
                vm.push({tx, ty, p + 1});
                vikatk(tx, ty);
                // 如果维京船打到了宝藏就不可能能拿到了
                if ((mp[sx][sy] & atkh) || (mp[sx][sy] & atkw)) print(0);
            }
        }
    }
}
// 自己移动
void youmove() {
    static int p = 0;
    ++p;
    while (!ym.empty() && ym.front().p <= p) {
        int x = ym.front().x, y = ym.front().y;
        ym.pop();
        // 如果这个位置被打了就不能扩展
        if ((mp[x][y] & atkw) || (mp[x][y] & atkh)) continue;
        for (int k = 0; k < 4; ++k) {
            int tx = x + dx[k], ty = y + dy[k];
            if (mp[tx][ty] == land) continue;
            if (!((mp[tx][ty] & youvis) || (mp[tx][ty] & atkw) || (mp[tx][ty] & atkh))) {
                mp[tx][ty] |= youvis;
                ym.push({tx, ty, p + 1});
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j)
            switch (s[j]) { // 存状态
                case '.': mp[i][j] = sea; break;
                case 'I': mp[i][j] = land; break;
                case 'Y': mp[i][j] = sea | you | youvis;
                          yx = i, yy = j;
                          break;
                case 'V': mp[i][j] = sea | vik | vikvis;
                          vx = i, vy = j;
                          break;
                case 'T': mp[i][j] = sea | trea;
                          sx = i, sy = j;
                          break;
            }
    }
    // 初始状态入队
    ym.push({yx, yy, 1});
    vm.push({vx, vy, 1});
    while (!(ym.empty() && vm.empty())) {
        youmove();
        vikmove();
        // 得到了
        if (mp[sx][sy] & youvis) print(1);
    }
    // 死路
    print(0);
    return 0;
}
```

---

## 作者：ZPB2011 (赞：1)

# Treasures and Vikings

[题目传送门](https://www.luogu.com.cn/problem/P4668)。

思路：看完数据点就可以暴力，用 `bfs` 跑一遍得出贼船到每个点的距离，然后再用一次 `bfs` 判断是否可以得到宝藏。

易错：**在第一次跑完要清空！**

代码：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

int n, m, ex, ey, sx, sy, vx, vy, dis[705][705];
bool vis[705][705];
char board[705][705];

struct node {
	int x, y, dep;//位置和已经走了多少步
};

void bfs(int sx, int sy) {//得到贼船到各个点的距离
	memset(dis, 0x3f, sizeof(dis));//初始化
	queue<node> que;
	que.push({sx, sy, 0});
	while(!que.empty()) {
		node u = que.front();
		que.pop();
		dis[u.x][u.y] = min(dis[u.x][u.y], u.dep);
		for(int i = 1; i <= 4; i++) {
			int nx = u.x + dx[i], ny = u.y + dy[i];
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && board[nx][ny] != 'I') {
				vis[nx][ny] = true;
				que.push({nx, ny, u.dep + 1});
			}
		}
	}
}

bool check(int x, int y, int dep) {//判断是否会遇到贼船
	for(int i = y + 1; i <= m && board[x][i] != 'I'; i++) {
		if(dis[x][i] <= dep) return false;
	}
	for(int i = y; i >= 1 && board[x][i] != 'I'; i--) {
		if(dis[x][i] <= dep) return false;
	}
	for(int i = x + 1; i <= n && board[i][y] != 'I'; i++) {
		if(dis[i][y] <= dep) return false;
	}
	for(int i = x; i >= 1 && board[i][y] != 'I'; i--) {
		if(dis[i][y] <= dep) return false;
	}
	return true;
}

bool bfs2(int sx, int sy) {//判断我能不能拿到宝藏
	vis[sx][sy] = true;
	queue<node> que;
	que.push({sx, sy, 0});
	while(!que.empty()) {
		node u = que.front();
		que.pop();
		if(u.x == ex && u.y == ey) return true;//能拿到
		for(int i = 1; i <= 4; i++) {
			int nx = u.x + dx[i], ny = u.y + dy[i];
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && board[nx][ny] != 'I' && check(nx, ny, u.dep + 1)) {
				vis[nx][ny] = true;
				que.push({nx, ny, u.dep + 1});
			}
		}
	}
	return false;//拿不到宝藏
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> board[i][j];
			if(board[i][j] == 'Y') {//我的船位置
				sx = i;
				sy = j;
			}
			else if(board[i][j] == 'V') {//贼船位置
				vx = i;
				vy = j;
			}
			else if(board[i][j] == 'T') {//宝藏位置
				ex = i;
				ey = j;
			}
		}
	}
	bfs(vx, vy);
	memset(vis, false, sizeof(vis));//记得清空！！！
	if(bfs2(sx, sy)) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
```

---

## 作者：Daniel_xu (赞：1)

# P4668 [BalticOI 2011 Day1] Treasures and Vikings 题解
## 思路
这道题主要考察广度优先搜索，主要可以分为以下两部分。
1. 通过 BFS 遍历确定贼船到任意一个点的最短距离。
2. 考虑到深搜的时间复杂度，我们需要再进行一次广搜，从我的位置出发，如果能到达宝藏处，则输出 `YES`，否则输出 `NO`。
## 具体实现方法
- 定义一个数组，在第一次 BFS 中记录下贼船到任一点的最短距离。
- 从我的位置出发进行搜索时，可以进行向上下左右四个方向的循环判断，如果发现贼船到此的距离小于**或等于**我到此的距离，则说明此处不能走。
- 两次 BFS 都需要使用标记数组，避免多次经过同一个节点。
## AC 代码
具体细节见代码注释。
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=705;
int dist[N][N];//贼船到任意节点的距离 
bool vis[N][N];//标记数组 
char a[N][N];//存储输入数据 
int n,m;
struct Node{
	int x,y,step;
};
const short d[][2]={{-1,0},{1,0},{0,-1},{0,1}};//上下左右四个方向 
void bfs(int sx,int sy){
	memset(dist,0x3f,sizeof(dist));//初始化次大值 
	//广搜 
	queue<Node> q;
	q.push(Node{sx,sy,0});
	vis[sx][sy]=true;
	while(q.size()){
		Node h=q.front();
		q.pop();
		dist[h.x][h.y]=min(dist[h.x][h.y],h.step);//记录
		//扩展新节点 
		for(int i=0;i<4;i++){
			int xx=h.x+d[i][0];
			int yy=h.y+d[i][1];
			if(xx>=1 && xx<=n && yy>=1 && yy<=m && !vis[xx][yy] && a[xx][yy]!='I'){//合法性检查 
				vis[xx][yy]=true;//标记 
				q.push(Node{xx,yy,h.step+1});
			}
		}
	}
}
bool ok(int x,int y,int step){//上下左右有没有贼船（注意遇到贼船停止 
	for(int i=y+1;i<=m && a[x][i]!='I';i++){//右 
		if(dist[x][i]<=step)return false;
	}
	for(int i=y;i>=1 && a[x][i]!='I';i--){//左 
		if(dist[x][i]<=step)return false;
	}
	for(int i=x+1;i<=n && a[i][y]!='I';i++){//下 
		if(dist[i][y]<=step)return false;
	}
	for(int i=x;i>=1 && a[i][y]!='I';i--){//上 
		if(dist[i][y]<=step)return false;
	}
	return true;
}
int ex,ey;
bool bfs1(int sx,int sy){//第二个BFS（从我的位置遍历） 
	//广搜 
	vis[sx][sy]=true;
	queue<Node> q;
	q.push(Node{sx,sy,0});
	while(q.size()){
		Node h=q.front();
		q.pop();
		if(h.x==ex && h.y==ey)return true;//找到宝藏退出
		//扩展新节点 
		for(int i=0;i<4;i++){
			int xx=h.x+d[i][0];
			int yy=h.y+d[i][1];
			if(xx>=1 && xx<=n && yy>=1 && yy<=m && !vis[xx][yy] && a[xx][yy]!='I' && ok(xx,yy,h.step+1)){//合法性检查 
				vis[xx][yy]=true;//标记 
				q.push(Node{xx,yy,h.step+1});
			}
		}
	}
	return false;
}

int main(){
	int sx,sy,vx,vy;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='Y'){//我的位置 
				sx=i;
				sy=j;
			}else if(a[i][j]=='V'){//贼船位置 
				vx=i;
				vy=j;
			}else if(a[i][j]=='T'){//宝藏位置 
				ex=i;
				ey=j;
			}
		}
	}
	bfs(vx,vy);//得到贼船到任一点的距离 
	memset(vis,0,sizeof(vis));//清空 
	if(bfs1(sx,sy)){ 
		cout<<"YES";
	}else{
		cout<<"NO";
	}
	return 0;
}
```

---

## 作者：我是逍逍 (赞：1)

有 $ n \times m$ 的地图，地图上可能有海（.）、陆地（I）、你的船（Y）、贼船（V）和宝藏（T）。

你的目的是在不被贼船干掉的情况下得到宝藏。

贼船会在回合结束时攻击与其在同一列或同一行的船.

如果有一条绝对安全的路径，使得无论如何你都能得到宝藏，输出 YES 否则输出 NO。

##### 说明一下，题目的描述有点问题：并不是只要和贼船待在同一行或同一列就会挂，还必须要求两船之间没有岛屿

由于数据很小，我们考虑直接广搜，自己和贼船的两个搜索同时进行，按照自己先动，贼船后动的原则搜索即可，代码实现时细节较多，需要注意一下

```cpp
#include <iostream>
#include <queue>

using namespace std;

const int d[4][2] = {0, -1, -1, 0, 1, 0, 0, 1};

struct Pos {
    int x, y;
} t;

struct Bfs {
    Pos p;
    int step;
} b, c, e, f;

int n, m, step;
char a[750][750];
bool x[750][750], y[750][750], z[750][750];
queue<Bfs> p, q;

void cover(Pos i) {
    for (Pos j = i; j.x && a[j.x][j.y] != 'I'; j.x--)
        z[j.x][j.y] = true;
    for (Pos j = i; j.x <= n && a[j.x][j.y] != 'I'; j.x++)
        z[j.x][j.y] = true;
    for (Pos j = i; j.y && a[j.x][j.y] != 'I'; j.y--)
        z[j.x][j.y] = true;
    for (Pos j = i; j.y <= m && a[j.x][j.y] != 'I'; j.y++)
        z[j.x][j.y] = true;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];

            switch (a[i][j]) {
                case 'Y':
                    p.push({{i, j}, 0});
                    x[i][j] = true;
                    break;
                case 'V':
                    q.push({{i, j}, 0});
                    y[i][j] = true;
                    break;
                case 'T':
                    t = {i, j};
            }
        }

    while (!p.empty()) {
        step++;
        while (!p.empty() && p.front().step <= step) {
            b = p.front();
            p.pop();

            if (!z[b.p.x][b.p.y]) {
                if (b.p.x == t.x && b.p.y == t.y) {
                    cout << "YES" << endl;
                    return 0;
                }

                for (auto k : d) {
                    c = {{b.p.x + k[0], b.p.y + k[1]}, b.step + 1};
                    if (c.p.x && c.p.y && c.p.x <= n && c.p.y <= m && !x[c.p.x][c.p.y] && a[c.p.x][c.p.y] != 'I' &&
                        !z[c.p.x][c.p.y]) {
                        x[c.p.x][c.p.y] = true;
                        p.push(c);
                    }
                }
            }
        }

        while (!q.empty() && q.front().step <= step) {
            e = q.front();
            q.pop();

            for (auto k : d) {
                f = {{e.p.x + k[0], e.p.y + k[1]}, e.step + 1};
                if (f.p.x && f.p.y && f.p.x <= n && f.p.y <= m && a[f.p.x][f.p.y] != 'I' && !y[f.p.x][f.p.y]) {
                    y[f.p.x][f.p.y] = true;
                    cover(f.p);
                    q.push(f);
                }
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
```


---

## 作者：serene_analysis (赞：1)

本篇题解参考了[此提交](https://loj.ac/s/956296)，引用了[此提交](https://loj.ac/s/237606)，如作者有意见请私聊我，我将完全尊重您的意见。

---

对题目的一点想法：这个题[暴力](https://loj.ac/s/237606)可以直接碾过去，方法是以贼船位置为起点，计算出每个点最少多少步就能被贼船控制，再以“你”的船位置为起点暴力 BFS 。时间复杂度 $\Theta(n^3)$ 带小常数。最大点在 $\text{900ms}$ 左右。

或许这道题在当年定位是一道完全爆搜？实测只需要 $n=800$，在左上角放``V``，在正中间放``Y``，在右下角放``T``，剩下的全放``.``，就可以在``-O2 -std=c++14``的环境下卡到 $\text{1.6s}$ 左右（当然可能是机房电脑是``i3``比较慢）。

另外这题时限好像有误， LOJ 上时限是 $\text{2s}$。如果是这样那暴力即为正解，本篇题解存在的意义也就变成了讲述优化。

（讲这么多是因为我觉得即使是简单题也要用严谨的态度去研究，还请多谅解）

---
提供一个 $\Theta(n^2)$ 的做法。

如果没有可以隔空阻拦的条件，那么这个题就可以完全爆搜~~吊打标算~~，考虑处理隔空阻拦。

观察发现贼船控制一行（列）的最早时间就是其到达这一行（列）的最早时间。以贼船为起点 BFS 出其到达每个点的最短时间，考虑 DP 计算出其控制每个点的最短时间，行列分开计算，``I``的点设成极大值即可。状态转移方程过于简单就不放了。

最后就是一个简单的 BFS 判断能否拿到宝藏。

update:原本的代码有一点问题。如果有贼船无法达到的位置，其`vdis`值将为 $0$，但最终我的 BFS 判定却是直接判的角色到达时间小于贼船到达时间。可以被如下数据 hack。（提供数据者不便公开）

```
3 3
IVI
III
YT.
```

在最新版代码中我改为使用 $-1$ 进行判定无法到达，然后对于初次搜索完毕后`vdis`值仍为 $-1$ 的点的`vdis`值改为极大值。

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
const int maxn=7e2+5;
const int maxm=7e2+5;
const int inf=1073741823;
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
struct point{
	int x;
	int y;
	void out(){
		printf("x=%d,y=%d\n",x,y);
		return;
	}
	friend bool operator==(point now,point oth){return now.x==oth.x&&now.y==oth.y;}
}you,vik,tre;
int n,m;
int vdis[maxn][maxm],ydis[maxn][maxm];
int linv[maxn][maxm],colv[maxn][maxm];
std::queue<point>q;
bool valid(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
signed main(){
	memset(vdis,-1,sizeof vdis);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("\n");
		for(int j=1;j<=m;j++){
			char ch=getchar();
			if(ch=='Y')you=(point){i,j};
			if(ch=='V')vik=(point){i,j};
			if(ch=='T')tre=(point){i,j};
			if(ch=='I')linv[i][j]=colv[i][j]=vdis[i][j]=ydis[i][j]=inf;
		}
	}
//	you.out(),vik.out(),tre.out();
	vdis[vik.x][vik.y]=0;
	q.push(vik);
	while(!q.empty()){
		point now=q.front();
		q.pop();
//		now.out();
		for(int i=0;i<4;i++){
			int nx=now.x+dx[i],ny=now.y+dy[i];
			if(valid(nx,ny)&&vdis[nx][ny]==-1){
				vdis[nx][ny]=vdis[now.x][now.y]+1;
				q.push((point){nx,ny});
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(vdis[i][j]==-1)vdis[i][j]=inf;
	for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++)linv[i][j]=colv[i][j]=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vdis[i][j]==inf)continue;
//			printf("vdis[%d][%d]=%d\n",i,j,vdis[i][j]);
			linv[i][j]=std::min(linv[i-1][j],vdis[i][j]);
			colv[i][j]=std::min(colv[i][j-1],vdis[i][j]);
//			printf("linv[%d][%d]=%d\n",i,j,linv[i][j]);
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			if(vdis[i][j]==inf)continue;
			linv[i][j]=std::min(linv[i+1][j],linv[i][j]);
			colv[i][j]=std::min(colv[i][j+1],colv[i][j]);
			vdis[i][j]=std::min(linv[i][j],colv[i][j]);
//			printf("vdis[%d][%d]=%d\n",i,j,vdis[i][j]);
		}
	}
	q.push(you);
	while(!q.empty()){
		point now=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int nx=now.x+dx[i],ny=now.y+dy[i];
			if(valid(nx,ny)&&!ydis[nx][ny]){
				ydis[nx][ny]=ydis[now.x][now.y]+1;
				if((point){nx,ny}==tre){
					printf("%s",ydis[nx][ny]<vdis[nx][ny]?"YES":"NO");
					return 0;
				}
				if(ydis[nx][ny]<vdis[nx][ny])q.push((point){nx,ny});
			}
		}
	}
	printf("NO");
	return 0;
}
```

感谢您的阅读！

---

