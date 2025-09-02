# [ABC276E] Round Trip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_e

縦 $ H $ 行、横 $ W $ 列のマス目があり、上から $ i\ \,\ (1\ \leq\ i\ \leq\ H) $ 行目、左から $ j\ \,\ (1\ \leq\ j\ \leq\ W) $ 列目のマスを $ (i,\ j) $ と表します。

各マスは「始点」「道」「障害物」のいずれかです。  
マス $ (i,\ j) $ の状態は文字 $ C_{i,\ j} $ で表され、$ C_{i,\ j}\ = $ `S` なら始点、$ C_{i,\ j}\ = $ `.` なら道、$ C_{i,\ j}\ = $ `#` なら障害物です。始点のマスはただ一つ存在します。

始点のマスを出発し、上下または左右に隣接するマスに移動することを繰り返して、障害物のマスを通らずに始点のマスへ戻ってくるような長さ $ 4 $ 以上の経路であって、最初と最後を除き同じマスを通らないようなものが存在するか判定してください。  
より厳密には、以下の条件を満たす整数 $ n $ およびマスの列 $ (x_0,\ y_0),\ (x_1,\ y_1),\ \dots,\ (x_n,\ y_n) $ が存在するか判定してください。

- $ n\ \geq\ 4 $
- $ C_{x_0,\ y_0}\ =\ C_{x_n,\ y_n}\ = $ `S`
- $ 1\ \leq\ i\ \leq\ n\ -\ 1 $ ならば $ C_{x_i,\ y_i}\ = $ `.`
- $ 1\ \leq\ i\ \lt\ j\ \leq\ n\ -\ 1 $ ならば $ (x_i,\ y_i)\ \neq\ (x_j,\ y_j) $
- $ 0\ \leq\ i\ \leq\ n\ -\ 1 $ ならばマス $ (x_i,\ y_i) $ とマス $ (x_{i+1},\ y_{i+1}) $ は上下または左右に隣接する

## 说明/提示

### 制約

- $ 4\ \leq\ H\ \times\ W\ \leq\ 10^6 $
- $ H,\ W $ は $ 2 $ 以上の整数
- $ C_{i,\ j} $ は `S`、`.`、`#` のいずれか
- $ C_{i,\ j}\ = $ `S` となる $ (i,\ j) $ がただ一つ存在する

### Sample Explanation 1

$ (3,\ 2)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (1,\ 2)\ \rightarrow\ (1,\ 3)\ \rightarrow\ (1,\ 4)\ \rightarrow\ (2,\ 4)\ \rightarrow\ (3,\ 4)\ \rightarrow\ (3,\ 3)\ \rightarrow\ (3,\ 2) $ という経路が条件を満たします。

## 样例 #1

### 输入

```
4 4
....
#.#.
.S..
.##.```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
S.
.#```

### 输出

```
No```

## 样例 #3

### 输入

```
5 7
.#...#.
..#.#..
...S...
..#.#..
.#...#.```

### 输出

```
No```

# 题解

## 作者：Binary_Lee (赞：5)

## [题面传送门](https://www.luogu.com.cn/problem/AT_abc276_e)

### 解决思路

发现题解区没有用 $\text{BFS}$ 写的类似的想法。

首先得出一个结论：要有一条长度 $\ge 4$ 的，起点终点相同的路径，这一条件等同于起点的上下左右四个点中，有任意两个是联通的。

![](https://cdn.luogu.com.cn/upload/image_hosting/gljujtlx.png)

如图，以 $1,2$ 两点为例，若他们是联通的，最差情况也是 $S\to 1\to X\to 2\to S$，长度为 $4$，满足要求。若 $X$ 有障碍，则路径会变得更长。

所以题目就转化为了求 $1,2,3,4$ 是否有任意两个点联通，只需从四个点分别开始 $\text{BFS}$ 染色即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,m,sx,sy,tot=1;
int X[4]={0,0,1,-1},Y[4]={1,-1,0,0};
char c;
struct node{
	int x,y;
};
queue<node> q;
signed main(){
	IOS;TIE;
	cin>>n>>m;
	int vis[n+5][m+5];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='#') vis[i][j]=1;
			if(c=='S') sx=i,sy=j,vis[i][j]=1;
		}
	}
	for(int i=0;i<4;i++){
		int x=sx+X[i],y=sy+Y[i];
		if(x<1||x>n||y<1||y>m) continue;
		if(!vis[x][y]){
			tot++;
			vis[x][y]=tot;
			while(q.size()) q.pop();
			q.push({x,y});
			while(q.size()){
				node k=q.front();q.pop();
				for(int j=0;j<4;j++){
					int xx=k.x+X[j],yy=k.y+Y[j];
					if(xx<1||xx>n||yy<1||yy>m||vis[xx][yy]) continue;
					vis[xx][yy]=tot;
					q.push({xx,yy});
				}
			}
		}
		else if(vis[x][y]!=1){
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
} 
```

---

## 作者：sunzz3183 (赞：3)

# [ABC276E] Round Trip 题解

## 题意

给定一个迷宫，询问从起点出发，能否一条长度大于等于 $4$ 且不经过重复的点的路径，回到起点。

## 分析

直接搜索

首先，长度要大于等于 $4$。其实，在方格图上，最小的回路就是等于 $4$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wg7yrkoi.png)

然后看如何搜索，直接在每个点时，向上下左右搜索。并设一个标记数组 $vis$，标记这个点是否被走过，如果在搜索中这个点被走过了，那么这个点延申出来的点肯定也被走过了。有点类似记忆化搜索。

那么我们就从起点出发，把起点看作墙，并向四个方向搜索，并在每次开始时，查询当前方向的点是否被走过，如果被走过显然出现了回路。

时间复杂度分析：每个点最多走一次，所以时间$O(H \times W)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e6+5,nxt[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int n,m,sx,sy;
char c;
vector<int>a[N];
void dfs(int x,int y){
	for(int i=0;i<4;i++){
		int tx=x+nxt[i][0],ty=y+nxt[i][1];
		if(tx<1||tx>n||ty<1||ty>m)continue;
		if(a[tx][ty])continue;
		a[tx][ty]=1;dfs(tx,ty);
	}
	return;
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;getchar(),i++){
		a[i].push_back(-1);
		for(int j=1;j<=m;j++){
			c=getchar();
			if(c=='#')a[i].push_back(-1);
			if(c=='S')a[i].push_back(-1),sx=i,sy=j;
			if(c=='.')a[i].push_back(0);
		}
	}
	for(int i=0;i<4;i++){
		int tx=sx+nxt[i][0],ty=sy+nxt[i][1];
		if(tx<1||tx>n||ty<1||ty>m)continue;
		if(a[tx][ty]==-1)continue;
		if(a[tx][ty]==1){puts("Yes");return 0;}\\向四个方向判断是否为回路
		a[tx][ty]=1;
		dfs(tx,ty);
	}
	puts("No");
	return 0;
}		
```


---

## 作者：FFTotoro (赞：3)

## 前言

官方题解：本题可以使用广度优先搜索或并查集实现。

我：运用深度优先搜索加一波奇怪的剪枝通过了本题。

## 解法

本题可以使用**深度优先搜索**加上**剪枝**实现。

首先我们用 `std::vector` 来实现一个 `bool` 型二维数组，存储每个点**是否能走**。具体地，这里的“不能走”的点分为 $3$ 类：

- 有障碍物的点；

- 已经走过过的点；

- 剪枝剪掉的点（这个在后面会详细说明）；

于是，我们就可以从起点开始，往四个方向暴搜。这时的暴搜中的 `bool` 数组只存储上面说的 $3$ 类的前面 $2$ 类点。

但是，你把暴搜的程序交上去，会发现有 $7$ 个 TLE。

所以，我们需要对搜索进行剪枝。

对于我们走到的点，不计它的前驱（也就是上一个搜到的点），一共还有 $3$ 个相邻的点。这时对其分类讨论一下：

- $3$ 个点都是“不能走的点”：这个点再搜下去没意义，剪掉；

- 有且仅有 $2$ 个点是“不能走的点”：可以继续搜索，但是**回溯的时候不要取消标记**，即让它成为上面所述“剪枝剪掉的点”（因为它四个相邻的点只有两个是“可走的”，如果我们从除了前驱的另一个点再搜回这个点，它的下一个点必然是原先搜索过的“前驱”，继续搜索是没有意义的，所以不去标记，让别的地方搜不到它）；

- 其他情况：按照普通的点搜索即可。

这样，TLE 就被完美地解决了。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,sx,sy;
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1}; // 方向数组
vector<string> s; // 地图数组
vector<vector<bool> > b; // 标记数组
bool dfs(int x,int y,int t){
    int c=0; b[x][y]=true;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i]; // 下一步可能搜到的点
        if(xx==sx&&yy==sy){
            if(t>=3){
                cout<<"Yes\n";
                return true; // 搜到了返回
            }
            else continue; // 步数不够
        }
        if(xx<0||xx>=h||yy<0||yy>=w||b[xx][yy]){c++; continue;} // 不合法方案（搜到边界或已经搜过）
        if(dfs(xx,yy,t+1))return true; // 合法方案
    }
    if(c<3)b[x][y]=false; // 需要去标记的情况
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>h>>w; s.resize(h);
    b.resize(h,vector<bool>(w));
    // 由于 h 和 w 不确定，所以需要开动态的 vector
    for(auto &i:s)cin>>i;
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            if(s[i][j]=='S')sx=i,sy=j;
            else if(s[i][j]=='#')b[i][j]=true;
    if(!dfs(sx,sy,0))cout<<"No\n"; // 无解的情况
    return 0;
}
```

---

## 作者：Semorius (赞：1)

由于路径除起点外不能重复经过一点且需要回到起点，那么出发时和结束时一定会经过与起点 $\text{S}$ 相邻的不同的点。如果存在两个这样的点联通，那么就存在这样一条从起点出发返回起点的回路。

但题目中有对路径长大于等于 $4$ 的限制，可以发现走一个 $2\times2$ 的矩阵回到原点是满足条件的最短可能路线，所以只要存在这样一条回路，其长度一定大于等于 $4$。

具体实现对每一个方格标号，使用路径压缩并查集维护点与点之间的连通性，最后判断是否存在与起点 $\text{S}$ 相邻的两个点在同一个联通块中。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int SIZE = 1000005;
const int mod = 998244353;
const int X[5] = {0, -1, 0, 1, 0};
const int Y[5] = {0, 0, -1, 0, 1};
int n, m;
vector<char> mp[SIZE];
int fa[SIZE];
int siz[SIZE];
int sx, sy;

inline int rd(){
	int f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

int get(int x){
	if(fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}

int getid(int x, int y){
	return (x-1)*m+y;
}

int main(){
	n = rd(), m = rd();
	for(int i = 1; i <= n; i++) mp[i].push_back('a');
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			char c; cin >> c;
			mp[i].push_back(c);
			fa[getid(i, j)] = getid(i, j);
			siz[getid(i, j)] = 1;
			if(c == 'S') sx = i, sy = j;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(mp[i][j] != '.') continue;
			for(int k = 1; k <= 4; k++){
				int x = i + X[k], y = j + Y[k];
				if(x <= 0 || y <= 0 || x > n || y > m || mp[x][y] != '.') continue;
				int xx = get(getid(i, j)), yy = get(getid(x, y));
				if(xx != yy) fa[xx] = yy, siz[yy] += siz[xx];
			}
		}
	}
	for(int i = 1; i <= 4; i++){
		int x1 = sx + X[i];
		int y1 = sy + Y[i];
		if(x1 <= 0 || y1 <= 0 || x1 > n || y1 > m || mp[x1][y1] != '.') continue;
		for(int j = i+1; j <= 4; j++){
			int x2 = sx + X[j];
			int y2 = sy + Y[j];
			if(x2 <= 0 || y2 <= 0 || x2 > n || y2 > m || mp[x2][y2] != '.') continue;
			int xx = get(getid(x1, y1)), yy = get(getid(x2, y2));
			if(xx == yy){
				printf("Yes\n");
				return 0;
			}
		}
	}
	printf("No");
	return 0;
}

```


---

## 作者：FReQuenter (赞：1)

## 思路

### 读入和存储

我们可以使用 STL 里的 `vector` 和 `string` 来实现。

`vector` 是向量，形象来说就是“可变长数组”，里面的元素个数可以动态变化；

`string` 是封装好的字符串，同样可以动态调整元素个数。

`vector` 的具体使用方法：可以参见 cpp reference 或 <https://blog.csdn.net/wangzhening/article/details/124061904>

`string` 的具体使用方法：可以参见 cpp reference 或 <https://www.bilibili.com/read/cv15716995>

### 寻找答案

我们可以使用搜索（BFS，DFS 均可），进行判重（即一个点是否搜索过，搜索过就不再继续搜索），使得复杂度为 $O(HW)$，如果第二次搜索到起点（即回到起点）且搜索深度大于等于四（即走了 $4$ 步及以上），则输出 `Yes`；若全图都已遍历过了仍会不去，则为 `No`。细节参见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int X[]={0,0,0,1,-1},Y[]={0,1,-1,0,0};
//搜索的 4 个方向
struct node{
	int x,y,step;
	node(){
	
	}node(int a,int b,int c){
		x=a,y=b,step=c;
	}
};
vector<string> a;
vector<vector<bool>> vis;
int n,m,sx,sy;
void dfs(int x,int y,int step){
	//我是用的 DFS
	vis[x][y]=1;//当前点标记访问
	for(int i=1;i<=4;i++){
		int nx=x+X[i],ny=y+Y[i];//新的位置
		if(nx==sx&&ny==sy&&step+1>=4){
        //如果是起点且走了 >=4 步
			cout<<"Yes";
			exit(0);
		}
		if(nx<1||ny<1||nx>n||ny>m||a[nx][ny]=='#'||vis[nx][ny]) continue;//如果不在棋盘内，或已经搜索过
		dfs(nx,ny,step+1);
	}
}
signed main(){
	cin>>n>>m;
	a.resize(n+1);
	vis.resize(n+1); 
	for(int i=1;i<=n;i++){
		//a[i].resize(m+1);
		vis[i].resize(m+1);
		cin>>a[i];
		a[i]='#'+a[i];
		for(int j=1;j<=m;j++){
			if(a[i][j]=='S'){
				sx=i,sy=j;
			}
			vis[i][j]=0;
		}
	}
	vis[sx][sy]=1;
   //读入，可以先参考过博客再来看
	dfs(sx,sy,0);
   //状态(x坐标，y坐标，步数)
	cout<<"No";
   //没有搜索回到起点
	return 0;
}
```

---

## 作者：Y2y7m (赞：1)

搜索题，~~为啥ABC会出搜索题啊~~。

由于要走一个环，所以直接 ```BFS``` 会出事。

枚举这条路径上第一个不是起点的点是什么，最后一个不是终点的点是什么，由于不会经过起点，所以路径最短也为 $4$，跑 ```BFS``` 即可（注意要预先标记起点，保证搜索时不会经过起点）。

复杂度：$O(16\times n\times m)$。

代码:

```cpp
#include <bits/stdc++.h>

using namespace std;
int n,m;
vector<char> a[1000010];
struct node
{
	int x,y,step;
};
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
bool inbound(int x,int y)
{
	return x>0&&x<=n&&y>0&&y<=m;
}
int sx,sy;
void bfs(int tsx,int tsy,int ex,int ey)
{
	bool vis[n+10][m+10];
	memset(vis,0,sizeof(vis));
	vis[sx][sy]=1;
	char mp[n+10][m+10];
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			mp[i][j+1]=a[i][j];
		}
	}
	queue<node> q;
	q.push({tsx,tsy,0});
	vis[tsx][tsy]=1;
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=t.x+dx[i],ny=t.y+dy[i];
			if(!inbound(nx,ny)) continue;
			if(vis[nx][ny]) continue;
			if(mp[nx][ny]=='#') continue;
			if(nx==ex&&ny==ey)
			{
				cout<<"Yes"<<endl;
				exit(0);
			}
			vis[nx][ny]=1;
			q.push({nx,ny,t.step+1});
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	string s;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		for(int j=0;j<s.size();j++)
			a[i].push_back(s[j]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(a[i][j]=='S')
			{
				sx=i,sy=j+1;
				break;
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		int tsx=sx+dx[i],tsy=sy+dy[i];
		if(!inbound(tsx,tsy)) continue;
		if(a[tsx][tsy-1]=='#') continue;
		for(int j=0;j<4;j++)
		{
			int ex=sx+dx[j],ey=sy+dy[j];
			if(!inbound(ex,ey)) continue;
			if(a[ex][ey-1]=='#') continue;
			bfs(tsx,tsy,ex,ey);
		}
	}
	cout<<"No"<<endl;
	return 0;
}

```


---

## 作者：Jerrywang09 (赞：0)

没什么人写并查集，我来补充并查集的解法。

并查集是什么？就是一种能快速查询两个点是否属于同一个连通分量的数据结构。可以使用路径压缩，把复杂度直接降到接近 $O(n)$。

首先，明确大体思路。如果不通过起始点，能够找到起始点的两个合法相邻点互通，说明可以实现 Round Trip。

那么，任意两个相邻空地，都可以互相连通，这样，就可以使用并查集维护连通关系。因为并查集是一维的，所以需要使用 $id$ 函数把给定的二维下标压到一维。

最后，查看起始点的 $4$ 个相邻点，两两匹配，如果在同一个连通分量里，输出 `Yes`。否则输出 `No`。

```cpp
#include <bits/stdc++.h>
#define SIZE 5000010
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl
using namespace std;

int m, n;
int f[SIZE];

inline int id(int i, int j)
{
	return i*n+j;
}

// dsu find
int fa(int x)
{
	if(x==f[x]) return x;
	return f[x]=fa(f[x]);
}

signed main()
{
	scanf("%d %d", &m, &n);
	char a[m+1][n+1];
	memset(a, 0, sizeof(a));
	int si, sj;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
		{
			cin>>a[i][j], f[id(i, j)]=id(i, j);
			if(a[i][j]=='S') si=i, sj=j;
		}
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
		{
			if(a[i][j]!='.') continue;
			int u=fa(id(i, j));
			// up
			int v=fa(id(i-1, j));
			if(a[i][j]==a[i-1][j]) f[v]=u;
			// left
			int w=fa(id(i, j-1));
			if(a[i][j]==a[i][j-1]) f[w]=u;
		}
	
	// start points
	vector<int> sp;
	if(si-1>0  && a[si-1][sj]=='.') sp.push_back(id(si-1, sj));
	if(si+1<=m && a[si+1][sj]=='.') sp.push_back(id(si+1, sj));
	if(sj-1>0  && a[si][sj-1]=='.') sp.push_back(id(si, sj-1));
	if(sj+1<=n && a[si][sj+1]=='.') sp.push_back(id(si, sj+1));
	for(int x:sp) for(int y:sp)
		if(x!=y && fa(x)==fa(y))
			/*debug(x), debug(y), */puts("Yes"), exit(0);
	puts("No");

    return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：0)

非常简单的送分题，但是本蒟蒻因为懒得翻译没有读好题没有接到送的 $500$ 分 qwq 顺带一提，题解区好像只有我是用连通块 dfs 做的捏 qwq

**题意**

给你面积不超过 $10^6$ 的方格图。有起点、路和障碍。现在。请问能否找到一个包含起点的长度不小于 $4$ 的可走的
环。

**分析**

注意这句话“长度不小于 $4$ 的环”。

你想到可以搜索判环。但是这有点麻烦。**我们关注这个数字 $4$。方格图上长度为 $4$ 的环是什么样的？**

是这样的：

```cpp
..
..

(1,1) -> (1,2) -> (2,2) -> (2,1) -> (1,1)
```

我们发现，方格图中，**只要是环，长度就至少为 $4$**。加下来，我们加上起点：

```cpp
..
S.


```

我们又有一个发现：我们看起点右边相邻的点和上边相邻的点。**只要这两个点在不经过起点的前提下连通，它们和起点就能构成一个符合要求的环**。

**所以说我们只要看起点上下左右四个点中是否存在一对点在不经过起点的前提下连通即可。**

我们用 dfs 预处理出连通块，枚举进行查询。需要注意的是，本题不能用二维数组存图。（你也可以使用 `vector` 和 `map`，但是我个人认为 `map` 时间复杂度比较高）

**AC CODE**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int a[MAXN];
int H,W,S;
int vis[MAXN];
void dfs(int u,int source)
{
	if(vis[u]) return;
	vis[u]=source;
 
	if(u>W)
	{
		int v=u-W;
		if(a[v]==1&&vis[v]==0) dfs(v,source);
 		//需要注意的是，我们不能经过起点，所以a[v]==3的情况不能被采取
	}
	if(u<=H*W-W)
	{
		int v=u+W;
		if(a[v]==1&&vis[v]==0) dfs(v,source);
	}
	if(u%W!=1)
	{
		int v=u-1;
		if(a[v]==1&&vis[v]==0) dfs(v,source);
	}
	if(u%W!=0)
	{
		int v=u+1;
		if(a[v]==1&&vis[v]==0) dfs(v,source);
	}
                //这四个其实是在枚举这个点上下左右的点
}
int main()
{
	scanf("%d %d",&H,&W);
	for(int i=1;i<=H;i++)
	{
		char s[MAXN];
		scanf("%s",s+1);
		for(int j=1;j<=W;j++)
		{
			int k=(i-1)*W+j;
			if(s[j]=='.') a[k]=1;
			if(s[j]=='#') a[k]=2;
			if(s[j]=='S') a[k]=3,S=k;
        //a 数组把两维压成一维                    
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=H*W;i++)
	{
		if(vis[i]==0&&a[i]==1) dfs(i,i);
	}
	int flag=0;
	int s[6]={0,0,0,0,0,0};
	if(S>W)
	{
		s[1]=S-W;
	}
	if(S<=H*W-W)
	{
		s[2]=S+W;
	}
	if(S%W!=1)
	{
		s[3]=S-1;
	}
	if(S%W!=0)
	{
		s[4]=S+1;
	}
                //枚举起点上下左右点
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(a[s[i]]==1&&a[s[j]]==1&&vis[s[i]]==vis[s[j]]&&i!=j)
			{
				flag=1;
			}
		}
	}
	puts(flag?"Yes":"No");
	return 0;
}
```


---

## 作者：__vector__ (赞：0)

### 题外话  
赛时很快就想出了一个自认为错的算法，还随便整了个 hack 数据，然后去看 F 题，G 题。过了半个小时回来看，分析一下发现是对的。不过还是赶在比赛结束前 20min 切了。  
### 做法  
搜索。  
没错，就是搜索。  
当然，不是指数级的爆搜，是记忆化。 
从起点开始搜，一旦找到任意一条从起点出发又回到起点的（长度大于 $0$ 的）路径，就退出；搜到一个已经访问到的点就立即返回。  

听上去很不对，因为如果第一条路径没走好，还会挡住后面更长的路径搜不到。  

但是，请注意，把图画出来之后，你会发现，只要找到任意一条从起点出发又回到起点的（长度大于 $0$ 的）路径，长度都符合要求，而显然只要存在从起点出发又回到起点的（长度大于 $0$ 的）路径，记忆化搜索肯定能找到其中一条。    
举个极端的例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/nhob8uhh.png?x-oss-process=image/resize,m_lfit,h_700,w_700)  
记忆化搜索找到了最短的一条从起点出发又回到起点的长度大于 $0$ 的路径，而这路径符合要求。  
### Code  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
string str[maxn];
map<pair<int,int>,bool> vis;
int h,w;
int sth,stl;
int ans=0;
void dfs(int i,int j,int cnt)
{
	if(ans||i>=h||i<0||j>=w||j<0||str[i][j]=='#')return;
	if(!(i==sth&&j==stl)&&vis.find(make_pair(i,j))!=vis.end())return;
	vis[make_pair(i,j)]=1;
	if(i==sth&&j==stl&&cnt!=0)
	{
		if(cnt>=4)ans=1;
		return;
	}
	dfs(i+1,j,cnt+1);
	dfs(i-1,j,cnt+1);
	dfs(i,j-1,cnt+1);
	dfs(i,j+1,cnt+1);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>h>>w;
	for(int i=0;i<h;i++)
	{
		cin>>str[i];
		for(int j=0;j<str[i].size();j++)
		{
			if(str[i][j]=='S')
			{
				sth=i,stl=j;
			}
		}
	}
	dfs(sth,stl,0);
	if(ans)printf("Yes");
	else printf("No");
	return 0;
}
```


---

## 作者：JiaY19 (赞：0)

### 题意

判断是否可以从起点出发，找到一条长度大于等于四且不重复经过某点（起点除外）最后回到起点的路径。

### 思路

由于路径长度要求仅仅为 $4$，那么很容易想到可以直接 $\text{dfs}$ 来进行判断。

我们可以从起点开始深搜。

不重复经过某一个点，判断一下是否可以再次到达起点即可。

时间复杂度：$O(nm)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 1000010;
 
int n, m, dx, dy, ans;
int vx[5] = {0, 0, 0, 1, -1};
int vy[5] = {0, 1, -1, 0, 0};
vector<int> a[N] , vis[N];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
inline int check(int x , int y)
{
    if(x < 1 || x > n || y < 1 || y > m)
        return 0;
    return a[x][y] != 2;
}
 
inline bool dfs(int x , int y , int fx , int fy)
{
    if (x == dx && y == dy && (x != fx || y != fy))
        return 1;
    if (vis[x][y]) return 0; vis[x][y] = 1;
    for (int i = 1;i <= 4;i++)
    {
        int nx = x + vx[i];
        int ny = y + vy[i];
        if(nx == fx && ny == fy)
            continue;
        if(check(nx , ny))
            if(dfs(nx, ny, x, y)) return 1;
    }
    return 0;
}
 
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n;i++)
        a[i].resize(m + 5), vis[i].resize(m + 5);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m;j++)
        {
            char ch; cin >> ch;
            if(ch == 'S') dx = i, dy = j;
            if(ch == 'S') a[i][j] = 1;
            if(ch == '#') a[i][j] = 2;
        }
    }
    puts(dfs(dx, dy, dx, dy) ? "Yes" : "No");
    return 0;
}

```


---

