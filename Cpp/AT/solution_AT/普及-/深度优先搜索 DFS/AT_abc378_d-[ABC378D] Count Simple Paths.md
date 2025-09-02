# [ABC378D] Count Simple Paths

## 题目描述

给定一个 $H$ 行 $W$ 列的网格；令 $(i, j)$ 为网格中从上到下第 $i$ 行、从左到右第 $j$ 列的格子。 

当 $ S_{i,j} $ 为 `.` 时，格子为空格；当 $ S_{i,j} $ 为 `#` 时，格子为障碍物。

请计算从某个空格出发，经过 $K$ 次移动（上下左右），不经过障碍物且不重复经过同一个格子的路径数。

具体地，统计满足以下条件的，长度为 $K+1$ 的序列 $((i_0,j_0),(i_1,j_1),\dots,(i_K,j_K))$

- 对于每个 $ 0\ \leq\ k\ \leq\ K $，都有 $ 1\ \leq\ i_k\ \leq\ H,\ 1\ \leq\ j_k\ \leq\ W $，且 $ S_{i_k,j_k} $ 为 `.`。
- 对于每个 $ 0\ \leq\ k\ \leq\ K-1 $，有 $ |i_{k+1}-i_k|\ +\ |j_{k+1}-j_k|\ =\ 1 $。
- 对于每个 $ 0\ \leq\ k\ <\ l\ \leq\ K $，有 $ (i_k,j_k)\neq\ (i_l,j_l) $。

## 说明/提示

-  $1 \leq H, W \leq 10$
-  $1 \leq K \leq 11$
-  $H$, $W$, 和 $K$ 均为整数。
-  每个 $S_{i,j}$ 均为 `.` 或 `#`。
-  网格中至少存在一个格子为空格。

## 样例 #1

### 输入

```
2 2 2
.#
..```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3 1
.#.
#.#```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10 11
....#..#..
.#.....##.
..#...##..
...#......
......##..
..#......#
#........#
..##......
.###....#.
...#.....#```

### 输出

```
218070```

# 题解

## 作者：zaolong (赞：2)

### 题目大意
有一个由 $H \times W$ 个单元格组成的网格。让 $(i, j)$ 表示从上往下第 $i$ 行，从左往上第 $j$ 列的单元格。如果 $S_{i,j}$ 是"."，那么 $(i,j)$ 单元格是空的，如果是 "#"，那么 $(i,j)$ 单元格是阻塞的。

要求计算从一个空单元格开始，向相邻单元格进行 $K$ 移动(向上、向下、向左或向右)，而不经过被阻塞的方格，也不多次访问同一单元格的方法的数目。

### 题目分析
这道题目初看像是动态规划（DP）问题，但鉴于数据范围，深度优先搜索（DFS）更为合适。首先用双重循环枚举每一个出发点，然后再调用函数进行 DFS 向四个方向中可以走的方向搜索，只要步数到达 $k$ 次 $ans$ 就加上 $1$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans;
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
bool bj[105][105]; 
void dfs(int x,int y,int s){
//	cerr<<x<<" "<<y<<" "<<s<<endl;
	if(s==k+1){
		//如果距离达到限制ans+1
		ans++;
		return;
	}
	for(int i=0;i<4;i++){
		//四个方向枚举 
		int xx=x+dx[i];
		int yy=y+dy[i];
		//判断可不可以走 
		if(bj[xx][yy]==0&&1<=xx&&xx<=n&&1<=yy&&yy<=m){
			//标记走过 
			bj[xx][yy]=1;
			//继续搜 
			dfs(xx,yy,s+1);
			//回溯 
			bj[xx][yy]=0;
		}
	}
}
main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			bj[i][j]=(x=='#');
		}
	}
	//枚举每个出发点 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(bj[i][j]==0){
				bj[i][j]=1;
				dfs(i,j,1);
				bj[i][j]=0;	
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：sjh0626 (赞：2)

## 题意概括

给定一个 $H$ 行 $M$ 列的表格，定义 $(i,j)$ 为从上到下的第 $i$ 行的从左到右的第 $j$ 列的单元格。

如果单元格 $(i,j)$ 为 `.`，则单元格为空，如果单元格 $(i,j)$ 为 `#`，则单元格有障碍物。

计算从空单元格开始移动到其他相邻单元格（上、下、左、右）不经过有障碍物的单元格，并且不重复走过同一个单元格的路线的数量。

总的来说，计算路线长度为 $K + 1$，路径为 $((i_0,j_0),(i_1,j_1),\cdots,(i_K,j_K))$ 的路线的数量，而路径得满足以下条件：

- 对于每一个 $(i,j)$，每一个单元格 $(i,j)$ 为 `.`，并且满足每一个 $0 \le l < r \le K$ 对应 $(i_l,j_l) \ne (i_r,j_r)$。

## 思路分析

总的来说，这道题需要用 DFS 来解决（因为在赛时我用 BFS 写不出来，主要是因为 BFS 不能回溯）。

我们应该枚举每一个单元格他能延伸出来 $K$ 步的路径的数量（即循环去使用 DFS），然后代码就很简洁明了了。

## 代码解析

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n,m,k,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},ans;
char g[20][20];
bool vis[20][20];
void dfs(int x,int y,int step){
	if(step==k){
		ans++;
		return;
	}
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&g[nx][ny]=='.'&&vis[nx][ny]==0){
			vis[nx][ny]=1;
			dfs(nx,ny,step+1);
			vis[nx][ny]=0;
		}
	}
	vis[x][y]=0;
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(g[i][j]!='#')dfs(i,j,0);
		}
	}
	cout<<ans;
	sjh0626s code;
}
```

---

## 作者：PineappleSummer (赞：2)

搜索，BFS 和 DFS 均可。对于这道题用 DFS 应该更好写一些，但是赛时降智写了 BFS。

从每个 `.` 点出发进行 BFS，拓展到一个没有走过的 `.` 点，记一个步数 $step$，如果 $step$ 为 $k$，让答案加 $1$。

BFS 需要对于每种走的方案都开一个标记数组，我用了 `bitset` 处理。DFS 只需要开一个标记数组，搜完回溯即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair <int, int> pii;
const int N = 110;
int h, w, k, ans;
char a[N][N];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
struct Node {
    pii Pos; int step;
    bitset <210> vis;
};
void Bfs (int sx, int sy) {
    queue <Node> q;
    bitset <210> bs;
    bs.set (sx * w + sy, 1);
    q.push ({{sx, sy}, 0, bs});
    while (!q.empty ()) {
        int step = q.front ().step;
        auto [x, y] = q.front ().Pos;
        bitset <210> bb = q.front ().vis; 
        q.pop ();
        if (step == k) {
            ans ++;
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx >= 1 && xx <= h && yy >= 1 && yy <= w && a[xx][yy] == '.' && !bb[xx * w + yy]) {
                bb[xx * w + yy] = 1;
                q.push ({{xx, yy}, step + 1, bb});
                bb[xx * w + yy] = 0;
            }
        }
    }
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> h >> w >> k;
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            cin >> a[i][j];
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j) {
            if (a[i][j] == '.') Bfs (i, j);
        }
    cout << ans;
    return 0;
}
```

---

## 作者：hjyowl (赞：2)

### 题目大意

给定一个网格图，求出从任意一点开始，移动恰好 $k$ 次的所有路径数。

### 思路

枚举起点，然后直接暴力搜索即可，如果经历的次数超过 $k$ 了就答案加一，标记打好就可以了，还有就是不能越界，主要是一些细节。

代码时间复杂度看着非常高但是能通过，主要是 $k$ 很小的原因。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char g[110][110];
bool st[110][110];
int n,m,k;
int res = 0;
void dfs(int x,int y,int s){
	if (s == k){
		res ++ ;
		return ;
	}
	if (s > k){
		return ;
	}
	int dx[4] = {-1,0,1,0},dy[4] = {0,-1,0,1};
	for (int i = 0; i <4 ; i++ ){
		int gx = x + dx[i],gy = y + dy[i];
		if (gx >= 1 && gx <= n && gy >= 1 && gy <= m){
			if (!st[gx][gy] && g[gx][gy] == '.'){
				st[gx][gy] = 1;
				dfs(gx,gy,s + 1);
				st[gx][gy] = 0;
			}
		}
	}
}
int main(){
	cin >> n >> m >> k;
	for (int i = 1; i <=n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			cin >> g[i][j];
		}
	}
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m ;j ++ ){
			if (g[i][j] == '.'){
				st[i][j] = 1;
				dfs(i,j,0);
				st[i][j] = 0;
			}
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：superLouis (赞：2)

## AT_abc378_d [ABC378D] Count Simple Paths 题解

本题个人认为难度为 ${\color{yellow} 普及/提高-}$，并不难。主要考验代码功底。

----------
#### 1. 大致题意
在一个 $H$ 行 $L$ 列的矩阵之中，若第 $i$ 行 $j$ 列为 `.`，表示可以通行，为 `#` 表示不能通行。请计算从空单元格开始并使 $K$ 移动到相邻单元格（向上、向下、向左或向右），不经过阻塞的方块并且不多次访问同一单元格的方法数量。

----------

#### 2. 解题思路
首先一点不可否认的是，这道题一定使用搜索。考虑使用深搜还是广搜。

- 广搜：不建议使用，可能很难写，甚至写不出来。因为广搜们个点都只被搜一次，不能覆盖掉所有的情况。
- 深搜：建议写。也就是直接爆搜，便于写代码可构思代码。

现在确定使用深搜了，思考如何解决此题。

由于 $K$ 和 $W$ 都小于等于 $10$，所以可以直接以每一个为 `.` 的点开始深搜。但是如何把每一种情况都搜到可能会为难大家。这里提供我的思路：

毋庸置疑，深搜使用的是递归。每一层递归如果不加引用的话，进入递归如同计入传送门，进一个个传送门。我们标记是否被访问过用的是布尔类型的 $vis$ 二维数组，记录每行每列的点是否被经过。我们只需要再进递归前将下一个要递归的坐标标记为访问过，出递归再将刚刚访问过的坐标标记为没访问过即可。

----------
#### 3. 代码
自认为码风良好

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int n, m, k, ans, dis[20][20];
char a[25][25];
bool inb(int x, int y) { return x > 0 && y > 0 && x <= n && y <= m; }
void dfs(int x, int y, int stx, int sty) {
    if (dis[x][y] == k) { ans++; return; }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (inb(nx, ny) && a[nx][ny] == '.' && !dis[nx][ny] && !(nx == stx && ny == sty)) {
            dis[nx][ny] = dis[x][y] + 1; dfs(nx, ny, stx, sty); dis[nx][ny] = 0;
        }
    }
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) if (a[i][j] == '.') 
            dfs(i, j, i, j); 
    cout << ans << "\n";
    return 0;
}
```
`inb` 函数是用来判断是否越界的。  
`dx`，`dy` 数组是方向数组。  
`dis` 数组是记录起点到该点的距离。注意每搜到一个为 `.` 的点，`dis` 数组**必须清空！**

[洛谷测评记录](https://www.luogu.com.cn/record/186829455) 

[Atcoder 测评记录](https://atcoder.jp/contests/abc378/submissions/59390735)

---

## 作者：Binah_cyc (赞：1)

一个有趣的简单题。

看到这道题，就应该想到搜索，没想到的应该反思反思自己的搜索是不是没学好。

考虑深度优先搜索，从每一个点开始暴搜，搜 $K$ 步并统计答案即可。

考虑时间复杂度，~~难倒真的有人会在打 ABC 的时候算复杂度吗~~，本题一共会走 $K$ 步，每一步都有 $4$ 种走法，在极限数据下复杂度为 $O(HW \times 2^K)$，能过。

代码：
```
// Problem: D - Count Simple Paths
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,ans;
char mp[15][15];
bool vis[15][15];
int dfs(int x,int y,int t)
{
	if(x<1||x>n||y<1||y>m) return 0;//走出地图
	if(vis[x][y]||mp[x][y]!='.') return 0;//不合法
	if(t==k+1) return 1;//走完了
	vis[x][y]=1;//标记该位置已经走过了
	int cnt=dfs(x-1,y,t+1)+dfs(x,y-1,t+1)+dfs(x+1,y,t+1)+dfs(x,y+1,t+1);
	vis[x][y]=0;//回溯的时候清空标记
	return cnt;
}
signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>mp[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(mp[i][j]=='.') ans+=dfs(i,j,1);
	cout<<ans;
	return 0;
}
```

---

## 作者：yzljy (赞：0)

## T4

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc378_d)  
[AT传送门](https://atcoder.jp/contests/abc378/tasks/abc378_d)

### 题意

给定一个长 $H \times W$ 的网格。网格中有些格子是障碍。现询问，从任意一个非障碍的格子开始，走恰好 $K$ 步，不走障碍格和已经走过的格子，一共有多少种方案。

$1 \le H,W \le 10$  
$1 \le K \le 11$

### 思路

如果使用 BFS 算法，暴力去做 $H \times W$ 次的时间复杂度是 $O(H^{2}W^{2})$ 的。（准确说应该是 $HW$ 乘上这个点能在 $K$ 步之内到达的点的数量）  
但是因为可以上下左右走，只要不走重复和障碍即可，BFS 的话并不是很好去统计方案数。（也可能是我太菜了xwx）

注意到数据范围很小。可以使用 **回溯算法** 计算。  
每次到一个点，先把这个点打上标记，然后查看周围四个点哪些点可以继续走。走到 $K$ 步的时候，将答案增加 $1$ 即可。  
回溯的时候把标记取消了即可。

设一个点的方案数为 $val_{i,j}$，则时间时间复杂度至少为（因为会走错误路线）。  
$$
O(\sum^{H}_{i=1}\sum^{W}_{j=1}val_{i,j})
$$

不妨跑一下极限数据，即 $10 \times 10$ 的网格，走 $11$ 步，并且没有障碍。我这里跑出来 DFS 函数也只会调用不到 $7\times 10^{6}$ 次，因此时间复杂度是没有问题的。

### 代码

```cpp
// Problem: D - Count Simple Paths
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int MAXN=10+10;
const int mod1=1e9+7;
const int mod2=998244353;
const int inf_int=0x7f7f7f7f;
const long long inf_long=0x7f7f7f7f7f7f7f7f;
const double eps=1e-9;
char Buf[1<<23],*P1=Buf,*P2=Buf;
#define getchar() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<23,stdin),P1==P2)?EOF:*P1++)
template<typename type>
inline void read(type &x){
	x=0;
	bool f=false;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename type,typename... args>
inline void read(type &x,args&... y){
	read(x),read(y...);
}

int h,w,k,ans;
char g[MAXN][MAXN];
bool vis[MAXN][MAXN];

struct node{
	int x,y,dis;
};

void dfs(int x,int y,int dis){
	if(dis==k){
		ans++;
		return;
	}
	vis[x][y]=true;
	if(x!=1&&!vis[x-1][y]&&g[x-1][y]=='.') dfs(x-1,y,dis+1);
	if(x!=h&&!vis[x+1][y]&&g[x+1][y]=='.') dfs(x+1,y,dis+1);
	if(y!=1&&!vis[x][y-1]&&g[x][y-1]=='.') dfs(x,y-1,dis+1);
	if(y!=w&&!vis[x][y+1]&&g[x][y+1]=='.') dfs(x,y+1,dis+1);
	vis[x][y]=false;
}

signed main(){
	cin>>h>>w>>k;
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) cin>>g[i][j];
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(g[i][j]=='#') continue;
			dfs(i,j,0);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Noah2022 (赞：0)

### 题目大意
给你一个 $ N \times M $ 的字符矩阵，问从任意一个不为 `#` 的地方开始，走 $ K $ 步， $ K $ 步中也不允许走到 `#` 的格子，有多少种不同的走法。

### 思路
对于每一个 `.` 开始， 搜索 $ K $ 步就 $ sum $ 加 $ 1 $ 。遍历完所有情况。
**注意：** 每次搜完一个以 `.` 开头的后，一定要清空标记。

### Code:
```cpp
#include <bits/stdc++.h>
#define maxn 100000
using namespace std;
int h,w,k,sum,dx[]={0,0,1,-1},dy[]={1,-1,0,0},bj[150][150];
char a[105][150];
inline void dfs(int x,int y,int step){
	bj[x][y]=1;
	if(step==k){
		sum++; // 一定不要 return 
	}
	else
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=1&&xx<=h&&yy>=1&&yy<=w&&a[xx][yy]=='.'&&bj[xx][yy]==0){
			dfs(xx,yy,step+1);
		}
	}
	bj[x][y]=0;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>h>>w>>k;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			memset(bj,0,sizeof(bj));  // 清空标记!!!
			if(a[i][j]=='.'){
				dfs(i,j,0);
			}
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Liuliuliuliuliu (赞：0)

# 题目大意
题意简化一下，就是求从 $(i_k,j_l)(0 \le k,l \le K)$ 出发，可以走 $K$ 步的二元组的个数。

# 思路
做题好习惯：先看数据范围。我们发现 $1 \le H,W \le 10$，再仔细看看 $1 \le K \le 11$，于是很容易联想到直接暴搜。

每次从满足条件的点出发，看看是否可以走 $K$ 步，然后统计答案。

# 注意点
1. 由于我们每个点都要搜索一遍，所以每个点dfs之前要清空数组。
2. 不要忘记回溯。
3. 注意边界条件。

# code
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm> 
using namespace std;
#define int long long  
inline int Read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int N=50;
const int fx[][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m,k,ans=0,t;
bool vis[N][N];
char s[N][N];
void dfs(int x,int y,int cnt){
	if(cnt==k){
		ans++;
		return ;
	}
	for(int i=0;i<4;i++){
		int dx=x+fx[i][0],dy=y+fx[i][1];
		if(dx<1||dx>n||dy<1||dy>m||s[dx][dy]=='#') continue;
		if(vis[dx][dy]) continue;
		vis[dx][dy]=1;
		dfs(dx,dy,cnt+1);
		vis[dx][dy]=0;
	}
}
signed main(){
	n=Read();m=Read();k=Read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int ii=1;ii<=n;ii++)
				for(int jj=1;jj<=m;jj++) 
					vis[ii][jj]=0;
			if(s[i][j]=='#') continue;
			vis[i][j]=1;
			dfs(i,j,0);
		}
	}
	if(ans<k) {
		puts("0");
		return 0;
	}
	printf("%lld\n",ans);
	return 0; 
}  

```

---

## 作者：cyq32ent (赞：0)

题意：一些点为墙，其他可以走，寻找长度为 $K$ 的路径总数。

直接暴搜即可。每搜到一个点，将其标记为墙，然后继续搜。边界全部视作墙可以避免特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[13][13],h,w,k;long long ans;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
void dfs(int i,int j,int d){
	if(d==k){
		ans++;return;
	}
	a[i][j]=0;
	for(int o=0;o<4;o++)
		if(a[i+dx[o]][j+dy[o]])dfs(i+dx[o],j+dy[o],d+1);
	
	a[i][j]=1;
}
int main(){
	cin>>h>>w>>k;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++){
		char c;cin>>c;a[i][j]=(c=='.');
	}
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)if(a[i][j])dfs(i,j,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

根据数据范围可以想到暴搜。

我们从每一个 `.` 格出发，用 dfs 找到它在 $k$ 步以后可以到达的所有位置，同时用一个 $vis$ 数组记录其已经经过的位置防止走重复路线，累加所有格子的答案即可，记得每次搜索前清空 $vis$ 数组。

[提交记录](https://atcoder.jp/contests/abc378/submissions/59365438)

---

## 作者：Fantasy_Segment_Tree (赞：0)

## 题意

在一个地图上只能往上下左右走，求走 $k$ 步有多少种可能的路径。

## 做法

发现 $H, W \leq 10$，于是可以暴力从每个点开始进行 dfs，对走过的点进行标记以保证不重复走点，记录 $step$ 表示已经走的步数，如果 $step \geq K$，那么直接将方案 $+1$，然后返回。

## 复杂度分析

时间复杂度为 $O(HW3^k)$，可以通过本题。

为什么是 $3^k$ 呢？因为每次只能往三个方向走，不能往过来的方向走。

代码不放了，非常好写。

---

## 作者：Heldivis (赞：0)

## [ABC378D] Count Simple Paths

发现 $H,W,K$ 都很小，考虑搜索。

设 $f(x,y,l)$ 为走到 $(x,y)$ 位置，当前路径长度为 $l$，那么当 $l=K$ 时记录到答案中并结束递归。

要求路径不经过重复点，加一个标记数组，回溯时清除即可。

代码：[赛时提交记录](https://atcoder.jp/contests/abc378/submissions/59363616)。

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个 $n\times m$ 的地图，每个格子是墙或空地，墙无法通行；给定 $k$，求所有长度为 $k$ 的简单路径的数量。
>
> $1\le n,m\le 10$，$1\le k\le 11$。

## 解法

地图非常小，我们考虑枚举起点然后 dfs 统计答案。时间复杂度 $O(\text{能过})$。具体实现就是在访问一个节点时打上走过的标记，回溯时取消标记；dfs 另记录一个步数，当步数等于 $k$ 时答案加一。由于每次枚举的起点不同所以不会重复统计。

## 代码

```cpp
// Problem: D - Count Simple Paths
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC)
mt19937 rnd(time(0));
const int maxn = 15, way[] = {0, 1, 0, -1, 0};
char mp[maxn][maxn]; int n, m, k;
bool vis[maxn][maxn]; int ans = 0;
void dfs(int x, int y, int stp) {
	if (x < 1 || x > n || y < 1 || y > m || vis[x][y] || mp[x][y] == '#')
		return ;
	if (stp == k) return ans ++, void(0);
	vis[x][y] = 1;
	for (int i = 0; i < 4; i ++)
		dfs(x + way[i], y + way[i + 1], stp + 1);
	vis[x][y] = 0;
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i ++)
		scanf("%s", mp[i] + 1);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			dfs(i, j, 0);
	printf("%d\n", ans);
	return 0;
}
```

---

