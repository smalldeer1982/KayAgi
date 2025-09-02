# Smooth Sailing (Easy Version)

## 题目描述

The only difference between the two versions of this problem is the constraint on $ q $ . You can make hacks only if both versions of the problem are solved.

Thomas is sailing around an island surrounded by the ocean. The ocean and island can be represented by a grid with $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The position of a cell at row $ r $ and column $ c $ can be represented as $ (r, c) $ . Below is an example of a valid grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/516df36ca6ac022124866d4043411e04ed0cf48c.png) Example of a valid gridThere are three types of cells: island, ocean and underwater volcano. Cells representing the island are marked with a '\#', cells representing the ocean are marked with a '.', and cells representing an underwater volcano are marked with a 'v'. It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is also guaranteed that the set of all island cells forms a single connected component $ ^{\dagger} $ and the set of all ocean cells and underwater volcano cells forms a single connected component. Additionally, it is guaranteed that there are no island cells at the edge of the grid (that is, at row $ 1 $ , at row $ n $ , at column $ 1 $ , and at column $ m $ ).

Define a round trip starting from cell $ (x, y) $ as a path Thomas takes which satisfies the following conditions:

- The path starts and ends at $ (x, y) $ .
- If Thomas is at cell $ (i, j) $ , he can go to cells $ (i+1, j) $ , $ (i-1, j) $ , $ (i, j-1) $ , and $ (i, j+1) $ as long as the destination cell is an ocean cell or an underwater volcano cell and is still inside the grid. Note that it is allowed for Thomas to visit the same cell multiple times in the same round trip.
- The path must go around the island and fully encircle it. Some path $ p $ fully encircles the island if it is impossible to go from an island cell to a cell on the grid border by only traveling to adjacent on a side or diagonal cells without visiting a cell on path $ p $ . In the image below, the path starting from $ (2, 2) $ , going to $ (1, 3) $ , and going back to $ (2, 2) $ the other way does not fully encircle the island and is not considered a round trip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/587237f643ee9a450f570eb64a27b00d982a357b.png) Example of a path that does not fully encircle the islandThe safety of a round trip is the minimum Manhattan distance $ ^{\ddagger} $ from a cell on the round trip to an underwater volcano (note that the presence of island cells does not impact this distance).

You have $ q $ queries. A query can be represented as $ (x, y) $ and for every query, you want to find the maximum safety of a round trip starting from $ (x, y) $ . It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

 $ ^{\dagger} $ A set of cells forms a single connected component if from any cell of this set it is possible to reach any other cell of this set by moving only through the cells of this set, each time going to a cell with a common side.

 $ ^{\ddagger} $ Manhattan distance between cells $ (r_1, c_1) $ and $ (r_2, c_2) $ is equal to $ |r_1 - r_2| + |c_1 - c_2| $ .

## 说明/提示

For the first example, the image below shows an optimal round trip starting from $ (1, 1) $ . The round trip has a safety of $ 3 $ as the minimum Manhattan distance from a cell on the round trip to an underwater volcano is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) Example of an optimal round tripFor the fourth example, remember that it is allowed for Thomas to visit the same cell multiple times in the same round trip. For example, doing so is necessary for the round trip starting from $ (7, 6) $ .

## 样例 #1

### 输入

```
9 9 3
.........
.........
....###..
...v#....
..###....
...##...v
...##....
.........
v........
1 1
9 1
5 7```

### 输出

```
3
0
3```

## 样例 #2

### 输入

```
3 3 5
..v
.#.
...
1 2
1 3
2 3
2 1
3 2```

### 输出

```
0
0
0
0
0```

## 样例 #3

### 输入

```
14 13 5
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
1 1
7 7
5 6
4 10
13 6```

### 输出

```
3
0
1
0
2```

## 样例 #4

### 输入

```
10 11 4
...........
..#######..
..#..#..#..
..#.....#..
..#..v..#..
..#.###.#..
..#.#.#.#..
..#...#.#..
..#####.#..
...........
7 6
3 7
6 8
1 1```

### 输出

```
1
2
3
4```

# 题解

## 作者：FL_sleake (赞：2)

魔幻暴力题。

### 题意简述

给你一张 $n\times m$ 的地图，每个点是海 `.`，岛屿 `#` 或者火山 `v`。保证岛屿和非岛屿均可以形成恰好一个四连通块且岛屿不与地图边界接壤，至少有一个岛屿点与一个火山点。

定义一条合法的路径为，从一个非岛屿的点 $s$ 出发，每次向四联通的非岛屿点走一格，用航线包围岛屿一整圈后回到点 $s$。一条路径包围岛屿定义为，不存在一条从岛屿出发的八连通路径可以在不触及路径的前提下到达边界。一条路径的权值为途中经过的所有点到离其最近的火山的曼哈顿距离的最小值。

现有 $q$ 次询问，每次给定一个点 $(x,y)$，你需要求出从 $(x,y)$ 出发的合法路径的最大权值。

$3\leq n,m\leq 10^5,9\leq nm\leq 3\times 10^5,q\leq 5$。

### 解题思路

求最小值的最大值，具有单调性，可以二分。难点在于如何 check。

先跑一遍多源最短路把每个点离其最近的火山的曼哈顿距离算出来，记为 $dis_{i,j}$。若当前二分出来的答案为 $k$，则我们从询问的点 $(x,y)$ 出发，向四个方向走，**只能走 $dis$ 值大于等于 $k$ 的点**，将它们打上标记。

如何判断是否将岛屿围起来？考虑从岛屿点出发，向周围八个方向走，如果能够走到边界且路径上不经过被标记的点，则岛屿没有被完全包围。这个套路在 [ABC219 E](https://www.luogu.com.cn/problem/AT_abc219_e) 中也用到了。~~那题也是个暴力题~~。

于是我们就做完了。注意空间的问题，我 vector 用的不太熟练，被卡了好几发。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,Q,stx,sty;
int dx[10]={0,0,1,-1,1,-1,-1,1},dy[10]={1,-1,0,0,1,-1,1,-1};
string s[100010];
vector<int> dis[100010];
vector<bool> Mark[100010],vis[100010];
struct node{
	int x,y;
};
queue<node> q;
void Debug_dis(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<dis[i][j]<<" ";
		cout<<endl;
	}
}
void Debug_Mark_points(int k){
	cout<<"ans:"<<k<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<Mark[i][j]<<" ";
		cout<<endl;
	}
}
void Get_dis(){
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='v') dis[i][j]=0,q.push({i,j});
		}
	}
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=0;i<4;i++){
			int tx=u.x+dx[i],ty=u.y+dy[i];
			if(tx<1||tx>n||ty<1||ty>m) continue;
			if(dis[tx][ty]>dis[u.x][u.y]+1){
				dis[tx][ty]=dis[u.x][u.y]+1;
				q.push({tx,ty});
			}
		}
	}
}
void Mark_points(int k){
	for(int i=1;i<=n;i++) Mark[i]=vector<bool>(m+5,0);
	while(!q.empty()) q.pop();
	q.push({stx,sty});
	Mark[stx][sty]=1;
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=0;i<4;i++){
			int tx=u.x+dx[i],ty=u.y+dy[i];
			if(s[tx][ty]=='#') continue;
			if(tx<1||tx>n||ty<1||ty>m||dis[tx][ty]<k||Mark[tx][ty]) continue;
			Mark[tx][ty]=1;
			q.push({tx,ty});
		}
	}
}
bool check(int k){
	if(dis[stx][sty]<k) return 0;
	Mark_points(k);
	//if(k<=20) Debug_Mark_points(k);
	for(int i=1;i<=n;i++) vis[i]=vector<bool>(m+5,0);
	while(!q.empty()) q.pop();
	int X=0,Y=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) if(s[i][j]=='#') X=i,Y=j; 
	}
	vis[X][Y]=1;
	q.push({X,Y});
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=0;i<8;i++){
			int tx=u.x+dx[i],ty=u.y+dy[i];
			if(tx<1||tx>n||ty<1||ty>m) return 0;
			if(Mark[tx][ty]||vis[tx][ty]) continue;
			vis[tx][ty]=1;
			q.push({tx,ty});
		}
	}
	return 1;
}
void C_close(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int main(){
	C_close();
	cin>>n>>m>>Q;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=n;i++) dis[i]=vector<int>(m+5,1e6);
	Get_dis();
	//Debug_dis();
	while(Q--){
		cin>>stx>>sty;
		int l=0,r=n+m+5,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：sunkuangzheng (赞：2)

2600？1300！

最小值最大，考虑二分。

二分答案 $x$，多源 bfs 出不能经过的地方，再次 bfs 出从 $(x,y)$ 能到的地方。

判断存不存在环有个巧妙的方法：从中间的连通块往外 bfs，如果一个边界都到不了，就是存在环。注意这里是八连通。

时间复杂度 $\mathcal O(q \cdot nm \log nm)$。需要三次 bfs，写的时候尽量封成函数，代码会短很多。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 14.01.2024 01:10:02
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 1e5+5;
using namespace std;
int T,n,m,q,x,y,dx[9] = {0,1,0,-1,0,1,1,-1,-1},dy[9] = {0,0,1,0,-1,-1,1,-1,1};string s[N];
void los(){ 
    cin >> n >> m >> q;
    for(int i = 1;i <= n;i ++) cin >> s[i],s[i] = " " + s[i];
    vector<vector<int>> dis(n + 1,vector<int>(m + 1,-1)),mk(n + 1,vector<int>(m + 1,0));
    auto bfs = [&](vector<pair<int,int>> st,int op){
        queue<pair<int,int>> q;
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) dis[i][j] = -1;
        for(auto [x,y] : st) if(!mk[x][y]) dis[x][y] = 0,q.emplace(x,y);
        while(q.size()){
            auto [x,y] = q.front(); q.pop();
            for(int i = 1;i <= (op ? 4 : 8);i ++){
                int ax = x + dx[i],ay = y + dy[i];
                if(ax >= 1 && ax <= n && ay >= 1 & ay <= m && !mk[ax][ay] && dis[ax][ay] == -1)
                    q.emplace(ax,ay),dis[ax][ay] = dis[x][y] + 1;
            }
        }
    };
    auto sol = [&](int x,int y,int md){
        vector<pair<int,int>> acc,cjr;
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) mk[i][j] = 0;
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) 
            if(s[i][j] == '#') cjr.emplace_back(i,j); else if(s[i][j] == 'v') acc.emplace_back(i,j);
        bfs(acc,1);
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) 
            if(dis[i][j] != -1 && dis[i][j] < md) mk[i][j] = 1;
        for(auto [x,y] : cjr) mk[x][y] = 1;
        bfs({{x,y}},1);
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) mk[i][j] = (dis[i][j] != -1);
        bfs(cjr,0);
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) 
            if((i == 1 || i == n || j == 1 || j == m) && dis[i][j] != -1) return 0;
        return 1;
    };
    while(q --){
        cin >> x >> y;
        int l = 0,r = n * m;
        while(l <= r){
            int mid = (l + r) / 2;
            if(sol(x,y,mid)) l = mid + 1; else r = mid - 1;
        }cout << l - 1 << "\n";
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

二分橙，bfs 橙，这题评黄是不是很有道理啊。

---

## 作者：_determination_ (赞：1)

好魔幻的题目啊。

看到这种最小值最大的题目，自然想到二分。

考虑如何进行 check。首先我们将每个点到最近火山的距离预处理出来，这个过程可以用 bfs 简单解决。然后 check 的时候就可以处理出路径可以经过的点。

之后的一个关键问题：如何确定一个路径是否包围一个联通块？一个图形被一条线包围，当且仅当从图形一点出发引一条射线到边界，该线被经过奇数次。

那么考虑拆点，将一个点拆成两个状态：经过线奇数次和偶数次，如果一个点的两个状态可以联通那么就有合法路径。

然后我们就可以二分了。

[Link.](https://codeforces.com/contest/1920/submission/287203370)

---

## 作者：xzy090626 (赞：0)

水啊。其实只有 D 的难度，只不过码量上大了一点。

我们考虑预处理所有点到最近的火山的距离，这一步可以 BFS 线性做。

然后考虑二分答案，二分一个最小值 $x$，每次去掉 $dis \geq x$ 且能从 $(x,y)$ 走到的点，然后 BFS 判断是否可以包围。

具体地，从周围的边界加入队列，然后只走八联通方向且被保留的点，只要遇到了 `#` 就非法，否则合法。

复杂度 $O(nm\log nm)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<time.h>
#include<bitset>
#include<random>
#include<iomanip>
#include<assert.h>
#define pii pair<int,int>
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 1e5 + 7;
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
const int px[] = {1,1,1,0,0,-1,-1,-1};
const int py[] = {-1,0,1,-1,1,-1,0,1};
vector<char>s[N];
vector<int>dis[N];
int n,m,k;
int qx,qy;
vector<bool>vis[N];
queue<pii>q;
bool chk(int w){
	for(int i=0;i<=n+1;++i){
		for(int j=0;j<=m+1;++j) vis[i][j] = 0;
	}
	q.push({qx,qy}); vis[qx][qy] = 1;
	while(!q.empty()){
		auto u = q.front();q.pop();
		for(int i=0;i<4;++i){
			int x = u.x + dx[i],y = u.y + dy[i];
			if(x<1 || y<1 || x>n || y>m) continue;
			if(dis[x][y]<w || s[x][y]=='#') continue;
			if(vis[x][y]) continue;
			vis[x][y] = 1;
			q.push({x,y});
		}
	}
	for(int i=0;i<=n+1;++i){
		vis[i][0] = vis[i][m+1] = 1;
		q.push({i,0}),q.push({i,m+1});
	}
	for(int i=0;i<=m+1;++i){
		vis[0][i] = vis[n+1][i] = 1;
		q.push({0,i}),q.push({n+1,i});
	}
	while(!q.empty()){
		auto u = q.front();q.pop();
		for(int i=0;i<8;++i){
			int x = u.x + px[i],y = u.y + py[i];
			if(x<0 || y<0 || x>n+1 || y>m+1) continue;
			if(s[x][y]=='#'){
				while(!q.empty()) q.pop();
				return 0;
			}
			if(vis[x][y]) continue;
			vis[x][y] = 1;
			q.push({x,y});
		}
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=0;i<=n+1;++i){
		s[i].resize(m+5);
		dis[i].resize(m+5,1141919810);
		vis[i].resize(m+5);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>s[i][j];
			if(s[i][j]=='v'){
				q.push({i,j});
				dis[i][j] = 0;
			}
		}
	}
	while(!q.empty()){
		auto u = q.front();q.pop();
		for(int i=0;i<4;++i){
			int x = u.x + dx[i],y = u.y + dy[i];
			if(x<1 || y<1 || x>n || y>m) continue;
			if(dis[x][y]<=dis[u.x][u.y]+1) continue;
			dis[x][y] = dis[u.x][u.y] + 1;
			q.push({x,y});
		}
	}
	while(k--){
		cin>>qx>>qy;
		int l = 1,r = dis[qx][qy],ans = 0;
		while(l<=r){
			int mid = (l+r)/2;
			if(chk(mid)) ans = mid,l = mid + 1;
			else r = mid - 1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

思路不难但是写起来有如答辩，写之前一直在想这玩意儿凭啥 *2500，写完之后感觉实现细节不止这个难度……

最大化最小值，容易想到二分，二分这个最大权值 $mid$，问题在于 check。考虑对每个点求一个到它最近的火山的距离 $dis_{i,j}$，那么相当于只能走 $dis_{i,j}\le mid$ 的点。如何判定绕道路径？考虑从起点 $(sx,sy)$ 开始 bfs 找出所有可以走的点打上 $tag$，从每个岛屿开始 bfs，如果可以在不经过 $tag$ 点的情况下到达边界那么就说明这个绕岛路径失败了。询问的复杂度 $\mathcal{O}(qn\log n)$，$n,m$ 同阶。

接下来讲一下一些代码实现细节：

1. 首先求 $dis$ 需要一遍多源 Dijkstra。因为是每个点到**离其最近的火山的曼哈顿距离**，所以走的应该是**四联通**路径，并且**可以走岛屿点**，**岛屿点也会有 $dis$ 值**。把所有火山放到优先队列里面跑 Dijkstra 即可。
2. 打 $tag$ 需要一遍单源 bfs。需要注意如果 $dis_{sx,sy}\le mid$ 就不打 $tag$ 直接失败。从 $(sx,sy)$ 出发的路径是**四联通，只能走非岛屿点**，而且如果到的这个点 $dis_{sx,sy}\le mid$，那么不仅不可以给它打 $tag$，也不能通过它走到别的点因为这个点本身就不可走了。
3. 从岛屿开始走需要一遍多源 bfs。这里能否走岛屿并不影响因为走了岛屿点反而不优。但是要注意题目里面说的是**八联通**路径，和非岛屿点不同。

然后注意清空和 vector 的空间问题就行了。衷心祝愿大家一遍过。[Submission.](https://codeforces.com/contest/1920/submission/245934143)

---

## 作者：huangrenheluogu (赞：0)

闲话：当时 23:45 左右以为想到了 F2 的 Sol，测样例的时候发现假了，极限卡时(0:34:11)改成 F1 提交。


可以先 bfs 预处理出每一个点和最近火山的距离（$(i,j)$ 的距离记为 $f_{i,j}$）。这一部分可以使用 bfs 用 $O(nm)$ 完成。

容易发现如果距离为 $k$ 可行，那么距离为 $k-1$ 可行，说明可以二分答案。

下面简述一下判定 $mid$ 是否可行的过程。

首先，先用起始点 $(x,y)$ 走到可以走到的所有 $f_{i,j}\ge mid$ 的点，并且标记。

然后按照定义，把所有小岛的点开始走，看看不经过上一步标记的点到达边界，如果可以，说明不可行。

这样判定一次的复杂度是 $O(nm)$。

总时间复杂度 $O(qnm\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5, inf = 1e9;
int n, m, qq, nx, ny, l, r, mid, dis, z, d, X, Y;
int dx[8] = {0, 1, 0, -1, 1, -1, -1, 1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
char c;
vector<int>a[N], f[N], ans[N], inq[N];
struct node{
	int x, y;
};
vector<node>isla;
queue<node>q;
struct dots{
	int x, y, ans;
};
deque<dots>Q;
inline bool check(int x, int qx, int qy){
	while(!q.empty()) q.pop();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			inq[i][j] = 0;
		}
	}
	q.push((node){qx, qy});
	inq[qx][qy] = 1;
	int X, Y;
	while(!q.empty()){
		X = q.front().x;
		Y = q.front().y;
		q.pop();
		for(int k = 0; k < 4; k++){
			nx = X + dx[k], ny = Y + dy[k];
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue ;
			if(f[nx][ny] < x || inq[nx][ny] || a[nx][ny] == 2) continue ;
			q.push((node){nx, ny});
			inq[nx][ny] = 1;
		}
	}
	
	for(auto X : isla){
		q.push(X);
		inq[X.x][X.y] = 1;
	}
	while(!q.empty()){
		X = q.front().x;
		Y = q.front().y;
		q.pop();
		if(X == 0 || X == n - 1 || Y == 0 || Y == m - 1) return 0;
		for(int k = 0; k < 8; k++){
			nx = X + dx[k], ny = Y + dy[k];
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue ;
			if(inq[nx][ny]) continue ;
			q.push((node){nx, ny});
			inq[nx][ny] = 1;
		}
	}
	return 1;
}
int main(){
	scanf("%d%d%d", &n, &m, &qq);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			c = getchar();
			f[i].pb(inf);
			ans[i].pb(0);
			inq[i].pb(0);
			while(c != '.' && c != 'v' && c != '#') c = getchar();
			if(c == '.') a[i].pb(0);
			if(c == 'v'){
				a[i].pb(1);
				q.push((node){i, j});
				f[i][j] = 0;
			}
			if(c == '#'){
				a[i].pb(2);
				isla.pb((node){i, j});
			}
		}
	}
	while(!q.empty()){
		X = q.front().x;
		Y = q.front().y;
		q.pop();
		for(int k = 0; k < 4; k++){
			nx = X + dx[k], ny = Y + dy[k];
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue ;
			if(f[nx][ny] <= f[X][Y] + 1) continue ;
			f[nx][ny] = f[X][Y] + 1;
			q.push((node){nx, ny});
		}
	}
//	for(int i = 0; i < n; i++){
//		for(int j = 0; j < m; j++) printf("%d ", f[i][j]);
//		puts("");
//	}
	while(qq--){
		scanf("%d%d", &X, &Y);
		X--, Y--;
		l = 0, r = f[X][Y], dis = 0;
		while(l <= r){
			mid = l + r >> 1;
			if(check(mid, X, Y)) l = mid + 1, dis = mid;
			else r = mid - 1;
		}
		printf("%d\n", dis);
	}
	return 0;
}
/*
14 13 1
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
7 7
*/
```

---

