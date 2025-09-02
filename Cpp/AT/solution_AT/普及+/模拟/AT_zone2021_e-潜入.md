# 潜入

## 题目描述

[problemUrl]: https://atcoder.jp/contests/zone2021/tasks/zone2021_e

$ 2 $ 次元平面があり、あなたは今いる座標 $ (1,\ 1) $ から UFO のある座標 $ (R,\ C) $ に移動したいです。  
 あなたが $ (r,\ c) $ にいるとき、あなたは以下の $ 4 $ 種類の移動を行うことができます。

- $ (r,\ c) $ から $ (r,\ c\ +\ 1) $ に移動する。$ A_{r,\ c} $ のコストがかかる。この移動は $ c\ <\ C $ のとき使える。
- $ (r,\ c) $ から $ (r,\ c\ -\ 1) $ に移動する。$ A_{r,\ c\ -\ 1} $ のコストがかかる。この移動は $ c\ >\ 1 $ のとき使える。
- $ (r,\ c) $ から $ (r\ +\ 1,\ c) $ に移動する。$ B_{r,\ c} $ のコストがかかる。この移動は $ r\ <\ R $ のとき使える。
- $ 1\ <\ =\ i\ <\ r $ を満たす整数 $ i $ を $ 1 $ つ選び、$ (r,\ c) $ から $ (r\ -\ i,\ c) $ に移動する。$ 1\ +\ i $ のコストがかかる。

$ (1,\ 1) $ から $ (R,\ C) $ に移動するために必要な最小のコストを求めてください。

## 说明/提示

### ストーリー

暗号解読を進めていると、仲間のムーアが突如 UFO に吸い込まれ、連れ去られてしまった。 ムーアは UFO との通信システムをほぼ 1 人で開発していたため、このままでは UFO と交信することができない！  
 デスマーチが横行していたブラックスタートアップ時代を思い出す。 バス係数$ {}\ =\ 1 $ のチームはいつだって脆いものだ。  
 仕方がない、UFO 内に乗り込んで直接話すしかなさそうだ。 上空を見上げると、UFO から梯子のようなものが下されている。  
 だがよく見るとボロボロで所々腐り落ちているようだ。 どうにかしてうまい登り方を考えなければ。

### 制約

- 入力は全て整数
- $ 2\ <\ =\ R,\ C\ <\ =\ 500 $
- $ 0\ <\ =\ A_{i,j}\ <\ 10^3 $
- $ 0\ <\ =\ B_{i,j}\ <\ 10^3 $

### Sample Explanation 1

以下のように移動するとコスト $ 9 $ が達成できます。 - $ (1,\ 1) $ から $ (2,\ 1) $ に移動する。コストが $ 1 $ かかる。 - $ (2,\ 1) $ から $ (3,\ 1) $ に移動する。コストが $ 1 $ かかる。 - $ (3,\ 1) $ から $ (3,\ 2) $ に移動する。コストが $ 1 $ かかる。 - $ (3,\ 2) $ から $ (1,\ 2) $ に移動する。コストが $ 3 $ かかる。 - $ (1,\ 2) $ から $ (1,\ 3) $ に移動する。コストが $ 1 $ かかる。 - $ (1,\ 3) $ から $ (2,\ 3) $ に移動する。コストが $ 1 $ かかる。 - $ (2,\ 3) $ から $ (3,\ 3) $ に移動する。コストが $ 1 $ かかる。

## 样例 #1

### 输入

```
3 3
10 1
10 10
1 10
1 10 1
1 10 1```

### 输出

```
9```

## 样例 #2

### 输入

```
7 11
42 77 94 76 40 66 43 28 66 23
27 34 41 31 83 13 64 69 81 82
23 81 0 22 39 51 4 37 84 43
62 37 82 86 26 67 45 78 85 2
79 18 72 62 68 84 69 88 19 48
0 27 21 51 71 13 87 45 39 11
74 57 32 0 97 41 87 96 17 98
69 58 76 32 51 16 38 68 86 82 64
53 47 33 7 51 75 43 14 96 86 70
80 58 12 76 94 50 59 2 1 54 25
14 14 62 28 12 43 15 70 65 44 41
56 50 50 54 53 34 16 3 2 59 88
27 85 50 79 48 86 27 81 78 78 64```

### 输出

```
498```

## 样例 #3

### 输入

```
4 4
0 0 0
0 0 0
0 0 0
0 0 0
0 0 0 0
0 0 0 0
0 0 0 0```

### 输出

```
0```

# 题解

## 作者：Nightsky_Stars (赞：5)

# 题目大意：

给定两个数 $R$ 和 $C$，再给定给定两个数组 $A$ 和 $B$，然后计算点 $(1,1)$ 到 $(R,C)$ 的最短路。

假设当前点 $(i,j)$，则你有四种移动方式：

- 移动到 $(i,j+1)$，花费为 $A_{i,j}$。需要保证 $j<C$。

- 移动到 $(i,j-1)$，花费为 $A_{i,j-1}$。需要保证 $j\ge 2$。

- 移动到 $(i+1,j)$，花费为 $B_{i,j}$。需要保证 $i<R$。

- 选择一个整数 $k$ 满足 $1\le k<i$，移动到 $(i-k,j)$，花费为 $(1+k)$。

# 思路：
首先，我们可以暴力建图来找最短路，然后用一种类似于 dijkstra 的算法，用广搜和优先队列，再来一点小小的剪枝就行了。

```
#include<bits/stdc++.h>
using namespace std;
int r,c,a[510][510],b[510][510],d[510][510];
bool vis[510][510];
priority_queue<pair<int,pair<int,int>>>q;//优先队列
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void bfs(int x, int y){//广搜
	memset(d,0x3f3f3f3f,sizeof(d));
	q.push(make_pair(0,make_pair(x,y)));
	d[x][y]=0;
	while(!q.empty()){
		int tx=q.top().second.first,ty=q.top().second.second;
		q.pop();
		if(tx==r&&ty==c) return ;//小小的剪枝
		if(vis[tx][ty]) continue;
		vis[tx][ty]=1;
		if(ty<c&&d[tx][ty+1]>d[tx][ty]+a[tx][ty]){
			d[tx][ty+1]=d[tx][ty]+a[tx][ty];
			q.push(make_pair(-d[tx][ty+1],make_pair(tx,ty+1)));
		}
		if(ty>1&&d[tx][ty-1]>d[tx][ty]+a[tx][ty-1]){
			d[tx][ty-1]=d[tx][ty]+a[tx][ty-1];
			q.push(make_pair(-d[tx][ty-1],make_pair(tx,ty-1)));
		}
		if(tx<r&&d[tx+1][ty]>d[tx][ty]+b[tx][ty]){
			d[tx+1][ty]=d[tx][ty]+b[tx][ty];
			q.push(make_pair(-d[tx+1][ty],make_pair(tx+1,ty)));
		}
		for(int i=1;i<tx;i++) {
			if(d[tx-i][ty]>d[tx][ty]+1+i) {
				d[tx-i][ty]=d[tx][ty]+1+i;
				q.push(make_pair(-d[tx-i][ty],make_pair(tx-i,ty)));
			}
		}
	}
}
int main() {
	r=read();
	c=read();
	for(int i=1;i<=r;i++){
		for(int j=1;j<c;j++){
			a[i][j]=read();
		}
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<=c;j++){
			b[i][j]=read();
		}
	}
	bfs(1,1);
	cout<<d[r][c]<<"\n";
	return 0;
}
```

---

## 作者：Jayfeather2012 (赞：2)

### 题意：
给定一个 $R\times C$ 的矩阵，求从 $(1,1)$ 移动到 $(R,C)$ 的最小代价。

若你在 $(i,j)$，你有四种移动方式。

1. 移动到 $(i,j+1)$，代价为 $A_{i,j}$。需要保证 $j<C$。

2. 移动到 $(i,j-1)$，代价为 $A_{i,j-1}$。需要保证 $j\ge 2$。

3. 移动到 $(i+1,j)$，代价为 $B_{i,j}$。需要保证 $i<R$。

4. 选择一个整数 $k$ 满足 $1\le k<i$,移动到 $(i-k,j)$，代价为 $(1+k)$。

### 思路：
这道题其实就相当于求从 $(1,1)$ 到 $(R,C)$ 的最短路，就很容易想到广搜配优先队列，我们用 $f$ 数组表示从 $(1,1)$ 到 $(i,j)$ 的最短路，若当前价值小于当前位置最小价值，就将当前位置最小价值设为当前价值,否则放弃该节点（因为前面已有更优的节点往下走过了）。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct datax
{
	int x,y,s; 
	bool operator <(const datax & a) const {
		return s>a.s;
	}
};
int n,m,a[505][505],b[505][505],f[505][505];
priority_queue<datax>q;//小根堆 
int bfs()
{
	q.push({1,1,0});
	while(q.size())
	{
		int x=q.top().x,y=q.top().y,s=q.top().s;
		q.pop();
		if(x==n&&y==m)return s;//达到目标返回答案 
		if(s>f[x][y])continue;
		else f[x][y]=s;
		//继续往下走，注意判断是否出界
		//优化：在当前位置的时候就判断下一步是否放弃 
		if(x>=1&&y>=1&&x<=n&&y<m&&s+a[x][y]<f[x][y+1])//第一种 
		{
			q.push({x,y+1,s+a[x][y]});
			f[x][y+1]=s+a[x][y];
		}
		if(x>=1&&y>1&&x<=n&&y<=m&&s+a[x][y-1]<f[x][y-1])//第二种 
		{
			q.push({x,y-1,s+a[x][y-1]});
			f[x][y-1]=s+a[x][y-1];
		}
		if(x>=1&&y>=1&&x<n&&y<=m&&s+b[x][y]<f[x+1][y])//第三种 
		{
			q.push({x+1,y,s+b[x][y]});
			f[x+1][y]=s+b[x][y];
		}
		if(x>=1&&y>=1&&x<=n&&y<=m)//第四种
		{
			for(int i=1;i<x;++i)
			{
				if(s+1+i<f[x-i][y])
				{
					q.push({x-i,y,s+1+i});
					f[x-i][y]=s+1+i;
				}
			}
		}
	}
	return 0;
}
int main()
{
	memset(f,0x3f,sizeof(f));//初始化成最大值 
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<m;++j)scanf("%d",&a[i][j]);
	for(int i=1;i<n;++i)
		for(int j=1;j<=m;++j)scanf("%d",&b[i][j]);
	printf("%d",bfs());
	return 0;
}
```

---

## 作者：lovely_codingcow (赞：2)

# AT_zone2021_e
## 题意

由于洛谷的题意太不好理解了，我是看了英文题面才理解的。下面简述一下题意：

> 首先题目给定两个数 $R$ 和 $C$ ，同时给定两个数组 $A$ 和 $B$，$A$ 的大小是 $R \times C - 1$ ，$B$ 的大小是 $R - 1 \times C$ 。然后计算点 $(1,\, 1)$ 到点 $(R,\, C)$ 的最短路径。
>
> 其中，假定当前的点为 $(i, \, j)$ ，那么有几种移动的方式：
>
> - 移动到 $(i,\, j+1)$，花费为 $A_{i,\,j}$。需要保证 $j<C$。
>
> - 移动到 $(i,\, j-1)$，花费为 $A_{i,\,j-1}$。需要保证 $j\ge 2$。
>
> - 移动到 $(i+1,\, j)$，花费为 $B_{i,\,j}$。需要保证 $i<R$。
>
> - 选择一个整数 $k$ 满足 $1\le k<i$，移动到 $(i-k,\,j)$，花费为 $(1+k)$。

## 思路

### 第一版

我的第一版思路较为简单。首先我们看一下题目，会发现与 Dijkstra 最短路算法很相似我们直接尝试使用类似 Dijkstra 的算法。我们使用广搜，加上优先队列优化，可以写出时间复杂度较为优秀的算法。

#### 具体实现方法

初始化一个数组 $dis$ 为极大值，用于保存点 $(1, \, 1)$ 到其余点的最短路径长度。初始化一个优先队列，用于存储节点，注意让长度短的节点处于堆顶。然后进入循环，截止条件为优先队列为空。对于每次循环，取出堆顶，然后按照题目给定的四种移动方式进行松弛操作，逐步的使 $dis$ 数组收敛到最小值，返回即可。

但是当你打出来的时候，你会发现似乎第四种移动方法会运行的比较慢。不管了，直接交！交完了你会发现实际上这个算法还是比较优秀的，只 TLE 了一个点。

#### 代码：

```cpp
#include <iostream>
#include <queue>
#include <cstring>

//#define int long long

using namespace std;

bool vis[509][509];
int r, c, a[509][509], b[509][509], dis[509][509];
priority_queue<pair<int, pair<int, int> > > pq;

void bfs(int x, int y) {
	memset(dis, 63, sizeof dis);
	pq.push({0, {x, y}});
	dis[x][y] = 0;
	while (!pq.empty()) {
		int fx = pq.top().second.first, fy = pq.top().second.second;
//		cout << fx << " " << fy << endl;
		pq.pop();
		if (vis[fx][fy]) {
			continue;
		}
		vis[fx][fy] = true;
		if (fy < c && dis[fx][fy + 1] > dis[fx][fy] + a[fx][fy]) {
			dis[fx][fy + 1] = dis[fx][fy] + a[fx][fy];
			pq.push({-dis[fx][fy + 1], {fx, fy + 1}});
		}
		if (fy > 1 && dis[fx][fy - 1] > dis[fx][fy] + a[fx][fy - 1]) {
			dis[fx][fy - 1] = dis[fx][fy] + a[fx][fy - 1];
			pq.push({-dis[fx][fy - 1], {fx, fy - 1}});
		}
		if (fx < r && dis[fx + 1][fy] > dis[fx][fy] + b[fx][fy]) {
			dis[fx + 1][fy] = dis[fx][fy] + b[fx][fy];
			pq.push({-dis[fx + 1][fy], {fx + 1, fy}});
		}
		for (int i = 1; i < fx; i++) {
			if (dis[fx - i][fy] > dis[fx][fy] + 1 + i) {
				dis[fx - i][fy] = dis[fx][fy] + 1 + i;
				pq.push({-dis[fx - i][fy], {fx - i, fy}});
			}
		}
	}
}

signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j < c; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i < r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> b[i][j];
		}
	}
	bfs(1, 1);
	cout << dis[r][c];
}
```



### 第二版

考虑如何优化第一版的算法。我们考虑一下，第一版的时间复杂度是 $O(|E|\log|E|)$ ，而 $|E|$ 可以达到 $3 \times R^2 \times C$ 的级别，又因为 $2 \leq R,\, C \leq 500$ ，所以总时间复杂度可以达到 $10^{10}$ 的级别，这是绝对无法通过的。但是由于算法本身已经足够优秀了。我们只需要考虑做一些简单的优化。

此时我们可以考虑剪枝，由于图中的边权较为固定（除了第四种操作），因此可以考虑计算出答案就返回。这种剪枝方法可以在保证答案无误的情况下，大幅度的调程序运行的效率。

尝试加入剪枝后，你就可以较为轻松的 AC。

#### 代码：

```cpp
#include <iostream>
#include <queue>
#include <cstring>

//#define int long long

using namespace std;

bool vis[509][509];
int r, c, a[509][509], b[509][509], dis[509][509];
priority_queue<pair<int, pair<int, int> > > pq;

void bfs(int x, int y) {
	memset(dis, 63, sizeof dis);
	pq.push({0, {x, y}});
	dis[x][y] = 0;
	while (!pq.empty()) {
		int fx = pq.top().second.first, fy = pq.top().second.second;
//		cout << fx << " " << fy << endl;
		pq.pop();
		if (fx == r && fy == c) {
			return;
		}
		if (vis[fx][fy]) {
			continue;
		}
		vis[fx][fy] = true;
		if (fy < c && dis[fx][fy + 1] > dis[fx][fy] + a[fx][fy]) {
			dis[fx][fy + 1] = dis[fx][fy] + a[fx][fy];
			pq.push({-dis[fx][fy + 1], {fx, fy + 1}});
		}
		if (fy > 1 && dis[fx][fy - 1] > dis[fx][fy] + a[fx][fy - 1]) {
			dis[fx][fy - 1] = dis[fx][fy] + a[fx][fy - 1];
			pq.push({-dis[fx][fy - 1], {fx, fy - 1}});
		}
		if (fx < r && dis[fx + 1][fy] > dis[fx][fy] + b[fx][fy]) {
			dis[fx + 1][fy] = dis[fx][fy] + b[fx][fy];
			pq.push({-dis[fx + 1][fy], {fx + 1, fy}});
		}
		for (int i = 1; i < fx; i++) {
			if (dis[fx - i][fy] > dis[fx][fy] + 1 + i) {
				dis[fx - i][fy] = dis[fx][fy] + 1 + i;
				pq.push({-dis[fx - i][fy], {fx - i, fy}});
			}
		}
	}
}

signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j < c; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i < r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> b[i][j];
		}
	}
	bfs(1, 1);
	cout << dis[r][c];
}
```

## 总结

这道题总体来说还是比较水的，是一个**优先队列优化 BFS** + **剪枝**的还不错的练习题。可以锻炼一下自己的代码能力，毕竟 BFS 写挂的可能性还是非常高的。注意细节和特殊优化即可通过。

---

## 作者：appear_hope (赞：1)

考虑状态设计：

状态：$(x, y, sum)$，表示走到 $(x, y)$ 这个位置的总花费。

转移：

$(x, y, sum) \rightarrow (x, y + 1, sum + a{_x, _y})$， 其中 $y < c$。

$(x, y, sum) \rightarrow (x, y  - 1, sum + a{_x, _y - 1})$，其中 $y \le 2$。

$(x, y, sum) \rightarrow (x + 1, y, sum + b{_x, _y})$，其中 $x < R$。

$(x, y, sum) \rightarrow (x - k, y, sum + 1 + k)$，其中 $1 \le k < x$。

这个转移并没有拓扑序，转移的代价不一定相等，所以使用 dijkstra。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 505;

struct Node{
	int x, y, sum;
	bool operator < (const Node &b) const{
		return sum > b.sum;
	}
};

bool vis[N][N];
priority_queue<Node> heap;
int n, m, a[N][N], b[N][N], dist[N][N];

void Record(int x, int y, int sum){ //判断转移是否非法
	if(x < 1 || x > n || y < 1 || y > m || sum >= dist[x][y]){
		return ;
	}
	dist[x][y] = sum, heap.push({x, y, sum});
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= m; j++){
			cin >> b[i][j];
		}
	}
	fill(&dist[1][1], &dist[n][m] + 1, INT_MAX);
	Record(1, 1, 0);
	while(!heap.empty()){
		Node q = heap.top();
		heap.pop();
		if(vis[q.x][q.y]) continue;
		vis[q.x][q.y] = 1;
		Record(q.x, q.y + 1, q.sum + a[q.x][q.y]);
		Record(q.x, q.y - 1, q.sum + a[q.x][q.y - 1]);
		Record(q.x + 1, q.y, q.sum + b[q.x][q.y]);
		for(int i = 1; i < q.x; i++){
			Record(q.x - i, q.y, q.sum + 1 + i);
		}
	}
	cout << dist[n][m];
	return 0;	
}
```

这个代码的时间复杂度是 $O(V \times \log V \times R)$，而 $1 \le V \le R \times C$，考虑剪枝，如果搜到答案就返回答案，这样可以大幅度提升程序的效率。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 505;

struct Node{
	int x, y, sum;
	bool operator < (const Node &b) const{
		return sum > b.sum;
	}
};

bool vis[N][N];
priority_queue<Node> heap;
int n, m, a[N][N], b[N][N], dist[N][N];

void Record(int x, int y, int sum){ //判断转移是否非法
	if(x < 1 || x > n || y < 1 || y > m || sum >= dist[x][y]){
		return ;
	}
	dist[x][y] = sum, heap.push({x, y, sum});
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= m; j++){
			cin >> b[i][j];
		}
	}
	fill(&dist[1][1], &dist[n][m] + 1, INT_MAX);
	Record(1, 1, 0);
	while(!heap.empty()){
		Node q = heap.top();
		heap.pop();
		if(vis[q.x][q.y]) continue;
		if(q.x == n && q.y == m){
			break;
		}
		vis[q.x][q.y] = 1;
		Record(q.x, q.y + 1, q.sum + a[q.x][q.y]);
		Record(q.x, q.y - 1, q.sum + a[q.x][q.y - 1]);
		Record(q.x + 1, q.y, q.sum + b[q.x][q.y]);
		for(int i = 1; i < q.x; i++){
			Record(q.x - i, q.y, q.sum + 1 + i);
		}
	}
	cout << dist[n][m];
	return 0;	
}
```

---

## 作者：Night_sea_64 (赞：1)

很容易想到，这题可以用优先队列的 bfs。

但是最后一种移动方式很讨厌，因为如果有这种移动方式的话，每个点最多可以到达另 $(R+1)$ 个点（在图论里看作每个点连 $R$ 条边）。而这种算法跟 Dijkstra 一样，时间复杂度为 $O(m\log m)$（$m$ 表示图论中的边数），不能通过。

我们心想：要是每个点只能到达上下左右相邻的四个点该多好啊，这样就能过了！

其实，最后一种移动方式就可以转化成 $k$ 次，每次向上走一格。但是这 $k$ 次移动需要 $(1+k)$ 的边权啊，我们不妨让第一次走 $2$ 的边权，后面几次走 $1$ 的边权。这需要记录一个值 $f$ 表示上一步是不是往上走。

这样还没完，我们记录某个位置是否走过的时候，要给这个位置按 $f$ 分类。因为有可能有两种状态到达同一个点并且花费相同，但一个是往右走过来，另一个往上走过来，你如果先扫到了往右走过来的这个状态，那你再往上走需要 $+2$。但实际上如果采用往上走过来的状态，再往上走只会 $+1$。

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,m;
int a[510][510],b[510][510];
bool flag[510][510][2];
struct node{int x,y,step;bool f;};
bool operator<(const node &x,const node &y){
    return x.step>y.step;
}
priority_queue<node>q;
bool chk(int x,int y,int dx,int dy){
    int nx=x+dx,ny=y+dy;
    if(nx<1||nx>n||ny<1||ny>m)return 0;
    return 1;
}
void bfs()
{
    q.push({1,1,0,0});
    while(!q.empty())
    {
        int x=q.top().x,y=q.top().y,step=q.top().step;
        bool f=q.top().f;
        q.pop();
        if(flag[x][y][f])continue;
        flag[x][y][f]=1;
        if(x==n&&y==m)
        {
            cout<<step<<endl;
            return;
        }
        if(chk(x,y,0,1))
            q.push({x,y+1,step+a[x][y],0});
        if(chk(x,y,0,-1))
            q.push({x,y-1,step+a[x][y-1],0});
        if(chk(x,y,1,0))
            q.push({x+1,y,step+b[x][y],0});
        if(chk(x,y,-1,0))
        {
            if(f)q.push({x-1,y,step+1,1});
            else q.push({x-1,y,step+2,1});
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
            cin>>a[i][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
            cin>>b[i][j];
    bfs();
    return 0;
}
```

---

## 作者：DailyPracticeAnn (赞：1)

AT_zone2021_e 潜入 做完不得不说，码量还可以，大概 $80$ 行。

这是一道最短路题。
- 思路：
1. 首先，我们可以考虑给它暴力建图来找最短路，但由于向上走的话，每个在它上面的点都可以被走到 ，所以我们的边数可能会达到 $n^4$ 级别，明显是不行的。于是，我们得想一些方法来缩小它的边数。
1. 从点 $i$ 向上走到点 $j$ 的花费是 $i - j + 1$，关键点在于这个 $+1$。
1. 我们可以借鉴一些我们网络流分块的建图方法，实际上并不需要分块，对于每一个点建一个虚点，点 $i$ 到虚点 $i'$ 的距离为 $1$，再从 $i'$ 依次向 $(i-1)'$ 连一条长度为 $1$ 的边，最后从 $i'$ 到 $i$ 连一条长度为 $0$ 的边。
1. 这样，就可以边数达到 $n^2$ 的级别了，点数也是 $n^2$ 级别的。然后，就是最短路。

当然，换上堆优化的 dij 就可以过了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
template<typename _T>
_T Fabs(_T x) {
	return x < 0 ? -x : x;
}
template<typename _T>
void read(_T &x) {
	_T f = 1;
	x = 0;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-') {
			f = -1;
			ch - getchar();
		} 
	}
	while ('0' <= ch && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	x *= f;
}
int r, c, head[510 * 510 * 2], tot, dis[510 * 510 * 2];
struct edge {
	int to, nxt, paid;
} e[510 * 510 * 10];
void addEdge(int u, int v, int w) {
	e[++tot] = (edge){v, head[u], w};
	head[u] = tot;
}
int Id(int x, int y) {
	return (x - 1) * c + y;
}
struct ming {
	int u, t;
	friend bool operator < (const ming &x, const ming &y) {
		return x.t > y.t;
	}
};
priority_queue<ming> q;
signed main() {
	read(r);
	read(c);
	for (int i = 1;i <= r;i++) {
		for (int j = 1, x;j < c;j++) {
			read(x);addEdge(Id(i, j), Id(i, j + 1), x);
			addEdge(Id(i, j + 1), Id(i, j), x);
		}
	}
	for (int i = 1;i < r;i++) {
		for (int j = 1, x;j <= c;j++) {
			read(x);
			addEdge(Id(i, j), Id(i + 1, j), x);
		}
	}
	for (int i = 1;i <= r;i++) {
		for (int j = 1;j <= c;j++) {
			addEdge(Id(i, j), Id(i, j) + r * c, 1);
			addEdge(Id(i, j) + r * c, Id(i, j), 0);
			if (i > 1) addEdge(Id(i, j) + r * c, Id(i - 1, j) + r * c, 1);
		}
	}
	for (int i = 1;i <= 2 * r * c;i++) dis[i] = 0x7f7f7f7f;
	dis[1] = 0;
	q.push((ming){1, 0});
	while (!q.empty()) {
		ming tmp = q.top();
		q.pop();
		if (tmp.t != dis[tmp.u]) continue;
		for (int i = head[tmp.u];i;i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[tmp.u] + e[i].paid) {
				dis[v] = dis[tmp.u] + e[i].paid;
				q.push((ming){v, dis[v]});
			}
		}
	}
	cout << dis[Id(r, c)] << endl;
	return 0;
}
```
### 蟹蟹观看！
#### $\text{THANKS FOR WATCHING!}$

---

## 作者：小小小朋友 (赞：1)

## 题意

题面已经较为清楚，翻译有一处翻译错误，第三个操作应为“花费为 $B_{i,j}$。”

## 做法

本题符合 atcoder 的一贯风格，将三个比较简单的操作和一个较为困难的操作放在一起加以迷惑，需要选手多加思考。

本题解为官方题解做法。

前三个操作可以直接按照题面要求暴力建边解决。接下来考虑第四个操作：

首先考虑如果花费为 $k$ 该如何处理，发现只要转化为对于每个点 $(i,j)$ 建到点 $(i+1,j)$ 的长度为 $1$ 的边即可。

再考虑花费为 $k+1$，想到一种类似分层图的做法：

把图拆为两层，一层为前三个操作建边所得图，一层为上述做法所建得的图。第一层建立到第二层长度为 $1$ 的边，第二层建立到第一层长度为 $0$ 的边。

具体的，

对于每个点 $P(i,j)$，建立一个点 $Q(i,j)$ 和如下边：

- $P(i,j)$ 到点 $Q(i,j)$，长度为 $1$ 的边。

- $Q(i,j)$ 到点 $Q(i-1,j)$，长度为 $1$ 的边。

- $Q(i,j)$ 到点 $P(i,j)$，长度为 $0$ 的边。

之后跑 dijkstra 即可通过本题。

## 代码

该代码较为朴实，较为科技（ NOI 系列竞赛不能使用）的代码请参见[官方题解](https://atcoder.jp/contests/zone2021/editorial/1213)。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[550005],w[550005];
int n,m,a[505][505],b[505][505];
long long dis[550005];
bool vis[550005];
priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int> > > pq;
int td(int tp,int i,int j){//获取节点编号，tp表示在哪一层上。
	if(tp) return 250505+i*500+j;
	else return i*500+j;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m-1;j++) cin>>a[i][j];
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m;j++) cin>>b[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int nd1=td(0,i,j),nd2=td(1,i,j);
			if(j<m) v[nd1].push_back(td(0,i,j+1)),w[nd1].push_back(a[i][j]);
			if(j>=2) v[nd1].push_back(td(0,i,j-1)),w[nd1].push_back(a[i][j-1]);
			if(i<n) v[nd1].push_back(td(0,i+1,j)),w[nd1].push_back(b[i][j]);
			if(j>=2){//第四个操作
				v[nd1].push_back(nd2);w[nd1].push_back(1);
				v[nd2].push_back(td(1,i-1,j));w[nd2].push_back(1);
				v[nd2].push_back(nd1);w[nd2].push_back(0);
			}
		}
	memset(dis,0x3f,sizeof(dis));
	vis[td(0,1,1)]=1,dis[td(0,1,1)]=0;
	pq.push(make_pair(0,td(0,1,1)));
	while(!pq.empty()){
		pair<int,int> fr=pq.top();pq.pop();
		int nt=fr.second;
		for(int i=0;i<v[nt].size();i++){
			if(dis[v[nt][i]]>dis[nt]+w[nt][i]){
				dis[v[nt][i]]=dis[nt]+w[nt][i];
				if(!vis[v[nt][i]]) pq.push(make_pair(dis[v[nt][i]],v[nt][i]));
			} 
		}
	}
	cout<<dis[td(0,n,m)];
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题意简述

给定两个整数 $R,C$，以及一个点到另一个点的花费，求出 $(1,1)$ 到 $(R,C)$ 的最小费用。

### 题目分析

我们可以根据题意暴力建图，然后跑一遍最短路就行了。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void dfs ();
const int MAXN = 250000 + 10, MAXM = 500 + 10;
int a[MAXM][MAXM], b[MAXM][MAXM], shu[MAXN], n, m;
vector <tuple <int, int> > vec[MAXN];
priority_queue <pair <ll, ll>, vector <pair <ll, ll> >, greater <pair<ll, ll> > > q;
bool vis[MAXN];
void dfs (int s) {
	memset (shu, 0x3f, sizeof (shu));
	shu[s] = 0; q.push ({0, s});
	while (!q.empty ()) {
		int now = q.top ().second;
		q.pop ();
		if (vis[now] == true) continue;
		vis[now] = true;
		for (auto [v, w] : vec[now]) {
			if (shu[v] > shu[now] + w) {
				shu[v] = shu[now] + w;
				q.push ({shu[v], v});
			}
		}
	}
}
int main () {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j < m; j ++) cin >> a[i][j];
	for (int i = 1; i < n; i ++) 
		for (int j = 1; j <= m; j ++) cin >> b[i][j];
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j < m; j ++) {
			int h = (i - 1) * m + j;
			vec[h].push_back ({h + 1, a[i][j]});
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 2; j <= m; j ++) {
			int h = (i - 1) * m + j;
			vec[h].push_back ({h - 1, a[i][j - 1]});
		}
	}
	for (int i = 1; i < n; i ++) {
		for (int j = 1; j <= m; j ++) {	
			int h = (i - 1) * m + j;
			vec[h].push_back ({h + m, b[i][j]});
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			for (int k = 1; k < i; k ++) {
				int h = (i - 1) * m + j;
				vec[h].push_back ({h - k * m, 1 + k});
			}
		}
	}
	dfs (1);
	cout << shu[n * m] << endl;
	return 0;
}
```

---

## 作者：DFM_O (赞：0)

## [AT_zone2021_e 题目](https://www.luogu.com.cn/problem/AT_zone2021_e)

### 解题思路
这表面上是一道动态规划题，实际上我们可以暴力建图，而且不需要任何转换，直接根据题意建即可，然后跑一遍最短路就直接过了，需要注意的是不能开 `long long`，否则会导致内存超限。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<tuple<int,int>> g[250001];
int a[501][501],b[501][501];
typedef pair<long long,long long> op;
priority_queue<op,vector<op>,greater<op>> pq;
int ds[250001];
bool st[250001];
inline void dij(int s)
{
	memset(ds,0x3f,sizeof(ds));
	ds[s]=0,pq.push({0,s});
	while(!pq.empty())
	{
		int now=pq.top().second;
		pq.pop();
		if(st[now]==1)
			continue;
		st[now]=1;
		for(auto [v,w]:g[now])
		{
			if(ds[v]>ds[now]+w)
				ds[v]=ds[now]+w,pq.push({ds[v],v});
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<m;j++)
			cin>>a[i][j];
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=m;j++)
			cin>>b[i][j];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<m;j++)
		{
			int h=(i-1)*m+j;
			g[h].push_back({h+1,a[i][j]});
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=2;j<=m;j++)
		{
			int h=(i-1)*m+j;
			g[h].push_back({h-1,a[i][j-1]});
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{	
			int h=(i-1)*+m+j;
			g[h].push_back({h+m,b[i][j]});
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=1;k<i;k++)
			{
				int h=(i-1)*m+j;
				g[h].push_back({h-k*m,1+k});
			}
		}
	}
	dij(1);
	int s=ds[n*m];
	cout<<s<<"\n";
	return 0;
}
```

---

## 作者：GoWithTheFlow (赞：0)

# 思路

观察题目，我们发现可以通过一个分层图的思想，将第四种操作建立到第二层图中，然后跑一边 Dijkstra 即可。具体的，对于第四种操作，我们可以：


- 建立分层图。现在我们假设有两层顶点，第一层 $(x_1, y_1)$ 和第二层 $(x_2, y_2)$。
- 从 $(x_1, y_1)$ 到 $(x_2, y_2)$ 添加一条代价为 $1$ 的边。
- 从 $(x_2, y_2)$ 到 $(x_2 - 1, y_2)$ 添加一条代价为 $1$ 的边。
- 从 $(x_2, y_2)$ 到 $(x_1, y_1)$ 添加一条代价为 $0$ 的边。


# 代码：

```c++
#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ios ios::sync_with_stdio(0)
#define endl '\n'
#define debug(x) cout << "x = " << x << endl;
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 1e7 + 5, P = 13331;
int n, m, a[505][505], b[505][505];
int dis[N], vst[N];
vector<pair<int, int>> e[N];
struct node
{
    int u, dis;
    bool operator<(const node &nd) const
    {
        return dis > nd.dis;
    }
};
int getid(int x, int y, int d)
{
    return d * 250000 + x * 500 + y;
}
void djk()
{
    for (int i = 0; i < N; i++)
        dis[i] = 1e15;
    priority_queue<node> pq;
    dis[getid(1, 1, 0)] = 0;
    pq.push({getid(1, 1, 0), 0});
    while (!pq.empty())
    {
        int u = pq.top().u, d = pq.top().dis;
        pq.pop();
        if (vst[u])
            continue;
        vst[u] = 1;
        for (auto it : e[u])
        {
            int v = it.first, w = it.second;
            if (dis[v] > d + w)
            {
                dis[v] = d + w;
                pq.push({v, dis[v]});
            }
        }
    }
}
void solve()
{
    int T = 1;
    // cin>>T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                cin >> a[i][j];
            }
        }
        for (int i = 1, w; i < n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> b[i][j];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                int u = getid(i, j, 0), v1 = getid(i, j + 1, 0);
                int v2 = getid(i, j - 1, 0), v3 = getid(i + 1, j, 0);
                if (j < m)
                    e[u].push_back({v1, a[i][j]});
                if (j >= 2)
                    e[u].push_back({v2, a[i][j - 1]});
                if (i < n)
                    e[u].push_back({v3, b[i][j]});
                if (i >= 2)
                    e[getid(i, j, 1)].push_back({getid(i - 1, j, 1), 1});
                e[getid(i, j, 0)].push_back({getid(i, j, 1), 1});
                e[getid(i, j, 1)].push_back({getid(i, j, 0), 0});
            }
        }
        djk();
        cout << dis[getid(n, m, 0)];
    }
}
signed main()
{
    ios;
    solve();
    return 0;
}
```

---

## 作者：hinin (赞：0)

#### 问题分析

我们需要从矩阵的左上角 $(1,1)$ 移动到右下角 $(R,C)$，并且每次移动都需要支付一定的费用。移动的方式有四种：

1.  向右移动 $(i,j) \to (i,j+1)$，费用为 $A_{i,j}$。
2.  向左移动 $(i,j) \to (i,j-1)$，费用为 $A_{i,j-1}$。
3.  向下移动 $(i,j) \to (i+1,j)$，费用为 $B_{i,j}$。
4.  向上移动 $(i,j) \to (i-k,j)$，费用为 $(1+k)$，其中 $1 \leq k < i$。

我们可以使用 Dijkstra 算法。我们将每个位置 $(i,j)$ 视为一个节点，移动的费用视为边的权重。我们需要维护一个优先队列来处理当前最小费用的节点。

时间复杂度：$O((R \times C) \times \log(R \times C))$；空间复杂度：$O(R \times C)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define pii pair<int, int>

using namespace std;

struct node {
	int id;
	ll vl;

	node(int _i = 0, ll _v = 0) : id(_i), vl(_v) {}
	bool operator<(const node& n) const { return vl > n.vl; }
};

const int N = 2.5e5 + 1, M = N * 6;
int sz, cnt, r, c, hd[N<<1], des[M], val[M], nxt[M];
ll dis[N<<1];
bool vis[N<<1];
node cur;
priority_queue<node> pq;

inline int mk(int rn, int cl) { return rn * c + cl; }

void add_edge(int s, int t, int v)
{
	des[cnt] = t, val[cnt] = v;
	nxt[cnt] = hd[s], hd[s] = cnt++;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	memset(hd, -1, sizeof hd);
	memset(dis, 0x3f, sizeof dis);

	cin >> r >> c;
	for(int i = 0, t; i < r; i++) {
		for (int j = 1; j < c; j++) {
			cin >> t;
			add_edge(mk(i, j - 1), mk(i, j), t);
			add_edge(mk(i, j), mk(i, j - 1), t);
		}
	}


	for(int i = 1, tb; i < r; i++) {
		for(int j = 0; j < c; j++) {
			cin >> tb;
			add_edge(mk(i-1,j), mk(i,j), tb);
		}
	}

	sz = r * c;
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			add_edge(mk(i, j), mk(i, j) + sz, 1);
			add_edge(mk(i, j) + sz, mk(i, j), 0);
			if(i) { add_edge(mk(i, j) + sz, mk(i - 1, j) + sz, 1); }
		}
	}

	dis[0] = 0;
	pq.emplace(0, 0);

	while(not pq.empty()) {
		cur = pq.top();
		pq.pop();

		if (not vis[cur.id]) {
			vis[cur.id] = true;
			for (int p = hd[cur.id]; p != -1; p = nxt[p]) {
				if (dis[des[p]] > dis[cur.id] + val[p]) {
					dis[des[p]] = dis[cur.id] + val[p];
					if(not vis[des[p]]) { pq.emplace(des[p], dis[des[p]]); }
				}
			}
		}
	}

	cout << dis[mk(r - 1, c - 1)] << endl;

	return 0;
}
```

---

## 作者：2022linzhiyi (赞：0)

# 题目大意
给定两个整数 $r$ 和 $c$ 以及一个点到另一个点的花费，求出 $(1,1)$ 到 $(r,c)$ 的最小费用。
# 思路
这道题一眼看去很像最短路，但是直接连边会炸（吗？）。所以我用了 bfs 来解决，只需要把队列改成优先队列就可以了。另外需要稍微剪枝一下，常数太大容易跑不过去。
# 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=510;
struct node {
	int x,y,step;
};
bool operator > (const node a,const node b) {
	return a.step > b.step;
}
inline int read() {
	int x=0; char ch=getchar();
	while (ch < '0' || ch > '9') ch=getchar();
	while (ch >= '0' && ch <= '9') x=x*10+ch-'0',ch=getchar();
	return x;
}
int n,m,a[N][N],b[N][N],cost[N][N];
bool vis[N][N];
int bfs() {
	priority_queue<node,vector<node>,greater<node> > q;
	q.push((node){1,1,0});
	memset(cost,0x3f,sizeof cost);
	while (!q.empty()) {
		node t=q.top(); q.pop();
		if (vis[t.x][t.y]) continue;
		vis[t.x][t.y]=1;
		if (t.x == n && t.y == m) return t.step;
		if (t.y+1 <= m && cost[t.x][t.y+1] > t.step+a[t.x][t.y]) {
			cost[t.x][t.y+1]=t.step+a[t.x][t.y];
			q.push((node){t.x,t.y+1,t.step+a[t.x][t.y]});
		}
		if (t.y-1 > 0 && cost[t.x][t.y-1] > t.step+a[t.x][t.y-1]) {
			cost[t.x][t.y-1]=t.step+a[t.x][t.y-1];
			q.push((node){t.x,t.y-1,t.step+a[t.x][t.y-1]});
		}
		if (t.x+1 <= n && cost[t.x+1][t.y] > t.step+b[t.x][t.y]) {
			cost[t.x+1][t.y]=t.step+b[t.x][t.y];
			q.push((node){t.x+1,t.y,t.step+b[t.x][t.y]});
		}
		for (int k=1;k<t.x;k++)
			if (cost[t.x-k][t.y] > t.step+k+1) {
				cost[t.x-k][t.y]=t.step+k+1;
				q.push((node){t.x-k,t.y,t.step+k+1});
			}
	}
}
int main() {
	n=read(); m=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<m;j++) a[i][j]=read();
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++) b[i][j]=read();
	cout << bfs();
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：

- 这道题的难点在于第四个操作，前三个简单操作可以直接套 Dijkstra 的模板，所以就不再赘述，重点讲解第四个操作。

- 第四个操作，简单来说就是水平上升 $x$ 个单位位置，花费 $x+1$（$1\le x$）。又因 $R$ 最多为 $500$，所以在跑最短路的时候，假如当前坐标为（$x_1,y_1$），那么我们只用暴力枚举 $1 \le x \le x_1$ 这个范围内的所有 $x$ 即可。

- 因为 Dijkstra 加上堆优化的复杂度约为 $O(n \log n)$，其实在加上一个暴力循环操作复杂度基本无差，得益于细微的剪枝 `if(v>d[x][y]) continue;`，使每个点被枚举到的次数较小。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[1010][1010];
long long a[1010][1010],b[1010][1010];
int wx[]={-1,1,0,0};
int wy[]={0,0,-1,1};
int r,c;
const int inf=1e9;
void bfs()
{
	for(int i=0;i<=r;i++)for(int j=0;j<=c;j++) d[i][j]=inf;
	d[1][1]=0;
	priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>q;
    q.push(make_pair(0,make_pair(1,1)));
    while(!q.empty())
    {
    	auto f=q.top();q.pop();
    	int v=f.first;
		int x=(f.second).first;
		int y=(f.second).second;
			//cout<<d[3][3]<<endl;
		if(v>d[x][y]) continue;
		//printf("d[%d][%d]=%d\n",x,y,v);
		for(int i=0;i<4;i++)
		{
			if(i==0)
			{
				for(int j=x-1;j>=1;j--)
				{
					if(v+(x-j+1)<d[j][y])
					{ 
					    d[j][y]=v+(x-j+1); 
						q.push(make_pair(v+(x-j+1),make_pair(j,y)));
                    }				
				}
			}
			else
			{
				int fx=x+wx[i];
				int fy=y+wy[i];
				if(fx>r || fx<1 || fy>c || fy<1)
				{
					continue;
				}
				int new_v=v;
				if(i==1)
				{
					//cout<<b[x][y]<<endl;
					new_v+=b[x][y]; 
				}
				if(i==2)
				{
					new_v+=a[fx][fy];
				}
				if(i==3)
				{
					new_v+= a[x][y];
				}
				//cout<<new_v<<endl;
				if(new_v<d[fx][fy])
				{
					d[fx][fy]=new_v;
					q.push(make_pair(new_v,make_pair(fx,fy)));
				}
			}
		} 
	}
	cout<<d[r][c];
}   
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<c;j++)
		{
			cin>>a[i][j];
		} 
	}
	for(int i=1;i<r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cin>>b[i][j];
		} 
	}
	bfs(); 
}
```
[AC 记录](https://www.luogu.com.cn/record/157563442)

---

## 作者：UniGravity (赞：0)

## Solution AT_zone2021_e 潜入
### 思路
看到最短路首先想到 dijkstra。

首先前三个操作是容易的，只需要将 $(i,j)$ 与 $(i+1,j),(i,j+1),(i,j-1)$ 按权值连边即可。

最后一个操作，我们发现 $1+k$ 的权值有些难以处理。如果不是 $1+k$ 而是 $k$ 就可以直接向后权值连为 $1$ 的边。

那么考虑转换。我们可以挂一条新的链上去，可以理解成高速公路。从 $(i,j,0)$ 到 $(i,j,1)$ 需要额外的 $1$ 权值，而 $(i,j,1)$ 到 $(i,j,0)$ 的权值是 $0$。

发现这样只会有 $nm$ 级别的点和边，直接跑最短路即可。

### 代码
```cpp
// AT_zone2021_e 潜入
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 6250005;
int n, m, a[1005][1005], b[1005][1005];
vector< pair< int, int > > edge[N];

inline int pos(int a, int b, int c) {
    return a + b * n + c * n * m;
}

struct Node {
    int dis, x;
    bool operator >(const Node &a) const {return dis > a.dis;}
};

int dis[N], vis[N];
inline int dijkstra() {
    for (int i = 0; i <= 6250000; i++) dis[i] = 0x3f3f3f3f3f3f3f3fll;
    dis[pos(1, 1, 0)] = 0;
    priority_queue< Node, vector< Node >, greater< Node > > q;
    q.push({0, pos(1, 1, 0)});
    int x, y, w;
    while (!q.empty()) {
        x = q.top().x; q.pop();
        if (vis[x]) continue; vis[x] = 1;
        for (int i = 0; i < edge[x].size(); i++) {
            y = edge[x][i].first, w = edge[x][i].second;
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                q.push({dis[y], y});
            }
        }
    }
    return dis[pos(n, m, 0)];
}

signed main() {
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            scanf("%lld", &a[i][j]);
            edge[pos(i, j, 0)].push_back(make_pair(pos(i, j + 1, 0), a[i][j]));
            edge[pos(i, j + 1, 0)].push_back(make_pair(pos(i, j, 0), a[i][j]));
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &b[i][j]);
            edge[pos(i, j, 0)].push_back(make_pair(pos(i + 1, j, 0), b[i][j]));
            edge[pos(i + 1, j, 1)].push_back(make_pair(pos(i, j, 1), 1));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            edge[pos(i, j, 0)].push_back(make_pair(pos(i, j, 1), 1));
            edge[pos(i, j, 1)].push_back(make_pair(pos(i, j, 0), 0));
        }
    }
    printf("%lld", dijkstra());
    return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路
不能直接 Dijkstra，会 TLE。

考虑优化。

操作一，二，三比较简单。

操作四可以这样做：

对于一个点 $(x,y)$，可以建出这个点的对应点 $(xx,yy)$。

- 先从 $(x,y)$ 连一条到 $(xx,yy)$ 的长度为 $1$ 的边。

- 再从 $(xx,yy)$ 连一条到 $(x-1,y)$ 的对应点的长度为 $1$ 的边。

- 最后从 $(xx,yy)$ 连一条到 $(x,y)$ 的长度为 $0$ 的边。

这样，从 $(x,y)$ 到 $(x-k,y)$ 可以转化为：

- 先从 $(x,y)$ 到对应点，花费为 $1$。

- 再向上走 $k$ 格，花费为 $k$。

- 最后回到 $(x-k,y)$，没有花费。

最终花费为 $k+1$，符合题意。

最后，做一遍 Dijkstra。不过要压成一维。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define pii pair<int,int>
#define pb push_back
#define p_q priority_queue
#define fi first
#define se second
vector<pii>g[1000005];//图
int n,m,a[505][505],b[505][505],dis[1000005];
int f(int x,int y){//二维变一维
	return (x-1)*m+y;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&b[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j<m){
				g[f(i,j)].pb({f(i,j+1),a[i][j]});//连边
			}
			if(j>=2){
				g[f(i,j)].pb({f(i,j-1),a[i][j-1]});
			}
			if(i<n){
				g[f(i,j)].pb({f(i+1,j),b[i][j]});
			}
			int x=i+505,y=j+505;//对应点
			g[f(i,j)].pb({f(x,y),1});
			g[f(x,y)].pb({f(x-1,y),1});
			g[f(x,y)].pb({f(i,j),0});
		}
	}
	p_q<pii,vector<pii>,greater<pii> >q;//最短路
	q.push({0,1});
	memset(dis,INF,sizeof dis);
	dis[1]=0;
	while(!q.empty()){
		int x=q.top().se,c=q.top().fi;
		q.pop();
		if(c!=dis[x]) continue;
		for(auto i:g[x]){
			if(c+i.se<dis[i.fi]){
				dis[i.fi]=c+i.se;
				q.push({dis[i.fi],i.fi});
			}
		}
	}
	cout<<dis[f(n,m)];//输出
    return 0;
}
```


---

## 作者：DerrickLo (赞：0)

容易想到可以最短路。

设 $dis_{i,j}$ 表示到 $(i,j)$ 的最小花费，每次到一个点 $(x,y)$ 时，有几种情况如下。

- 往上走，即走到 $(x,y-1)$。

- 往下走，即走到 $(x,y+1)$。

- 往右走，即走到 $(x+1,y)$。

- 往左走，即走到 $(x-i,y)$，$i\in [1,x-1]$。

这样跑一遍 `dijkstra` 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[505][505],b[505][505],dis[505][505],vis[505][505];
priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>qu;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)cin>>a[i][j];
	for(int i=1;i<n;i++)for(int j=1;j<=m;j++)cin>>b[i][j];
	memset(dis,0x3f,sizeof dis);
	dis[1][1]=0,vis[1][1]=1; 
	qu.push({0,{1,1}});
	while(!qu.empty()){
		auto ft=qu.top();qu.pop();
		int x=ft.second.first,y=ft.second.second,w=ft.first;
		if(x==n&&y==m){
			cout<<w;
			return 0;
		}
		if(y<m){
			if(dis[x][y+1]>dis[x][y]+a[x][y]){
				dis[x][y+1]=dis[x][y]+a[x][y];
				if(!vis[x][y+1])qu.push({dis[x][y+1],{x,y+1}});
			}
		}
		if(y>1){
			if(dis[x][y-1]>dis[x][y]+a[x][y-1]){
				dis[x][y-1]=dis[x][y]+a[x][y-1];
				if(!vis[x][y-1])qu.push({dis[x][y-1],{x,y-1}});
			}
		}
		if(x<n){
			if(dis[x+1][y]>dis[x][y]+b[x][y]){
				dis[x+1][y]=dis[x][y]+b[x][y];
				if(!vis[x+1][y])qu.push({dis[x+1][y],{x+1,y}});
			}
		}
		for(int i=1;i<x;i++){
			if(dis[x-i][y]>dis[x][y]+i+1){
				dis[x-i][y]=dis[x][y]+i+1;
				if(!vis[x-i][y])qu.push({dis[x-i][y],{x-i,y}});
			}
		}
	}
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [Zone2021E](https://www.luogu.com.cn/problem/AT_zone2021_e)

看到这个数据范围，可以用 $O(n^3\log n)$ 的 dij。

这个复杂度看似不行，实际上常数很小，最后跑起来大概是 $O(n^2\log n)$ 的。

当然，要加上一个优化：如果处理到终点，就直接输出答案结束程序，否则可能会被卡掉。

具体地，对于每一个点，暴力让它连向能达到的 $i + 3$ 个点即可。在线处理。

```cpp
// 代码不太美观，不喜勿喷。
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 505

using pii = pair<int, int>;
using pip = pair<int, pii>;

int a[MAXN][MAXN];
int b[MAXN][MAXN];
int v[MAXN][MAXN];
int d[MAXN][MAXN];

int main()
{
	int r, c;
	cin >> r >> c;
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j < c; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1; i < r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cin >> b[i][j];
		}
	}
	memset(d, 0x3f, sizeof(d));
	d[1][1] = 0;
	priority_queue<pip> q;
	q.push({0, {1, 1}});
	while (!q.empty())
	{
		pii p = q.top().second;
		if (p == pii{r, c})
		{
			cout << -q.top().first << endl;
			return 0;
		}
		q.pop();
		v[p.first][p.second] = 1;
		if (p.second < c && !v[p.first][p.second + 1] && d[p.first][p.second + 1] > d[p.first][p.second] + a[p.first][p.second])
		{
			d[p.first][p.second + 1] = d[p.first][p.second] + a[p.first][p.second];
			q.push({-d[p.first][p.second + 1], {p.first, p.second + 1}});
		}
		if (p.second > 1 && !v[p.first][p.second - 1] && d[p.first][p.second - 1] > d[p.first][p.second] + a[p.first][p.second - 1])
		{
			d[p.first][p.second - 1] = d[p.first][p.second] + a[p.first][p.second - 1];
			q.push({-d[p.first][p.second - 1], {p.first, p.second - 1}});
		}
		if (p.first < r && !v[p.first + 1][p.second] && d[p.first + 1][p.second] > d[p.first][p.second] + b[p.first][p.second])
		{
			q.push({-(d[p.first + 1][p.second] = d[p.first][p.second] + b[p.first][p.second]), {p.first + 1, p.second}});
		}
		for (int k = 1; k < p.first; k++)
		{
			if (!v[p.first - k][p.second] && d[p.first - k][p.second] > d[p.first][p.second] + k + 1)
			{
				q.push({-(d[p.first - k][p.second] = d[p.first][p.second] + k + 1), {p.first - k, p.second}});
			}
		}
	}
	return 0;
}

```


---

## 作者：_WHITE_NIGHT_ (赞：0)

### 思路：
- 首先，看到题面，一眼 bfs 。确定是 bfs 后，发现移动的花费不同，所以确定为优先队列优化 bfs。但是和标准的 bfs 好像又不太一样，因为一般 bfs 移动的格数 $x$ 与 $y$ 一般都是确定的，所以，本题的重点在于如何将操作 $4$ 转化为 bfs 能够处理的情况。

- 对于操作 $4$,可以观察到：
> 选择一个整数 $k$ 满足 $1 \leq k < i$，移动到 $(i-k,j)$，花费为 $(1 + k)$。

这个条件很显然是有规律可循的。举个例子：("$\rightarrow$"表示移动到)

$(3,4)$ $\rightarrow$ $(3,2)$ 花费为 $3$

我们可以转化成：

$(3,4)$ $\rightarrow$ $(3,3)$ $\rightarrow$ $(3,2)$ 花费为 $4$

用 $x$，$y$ 来代替，则有：

$(x,y)$ $\rightarrow$ $(x-k,y)$ 花费为 $k+1$

$(x,y)$ $\rightarrow$ $(x-1,y)$ $\rightarrow$ $(x-k,y)$ 花费为 $k+2$。这意味着我们在做操作 $4$ 时，第一次的花费是 $2$，其余时候的花费是 $1$。

这样，我们就将移动未知的 $k$ 格转化成了 bfs 可以处理的每次移动 $1$ 格，这样，我们在 bfs 的模板上，加一个特判，判断是否第一次操作 $4$ 即可

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace FastIO
{
	const int Mt = 1e5;
	inline char getch()
	{
		static char buf[Mt],*p1 = buf,*p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,Mt,stdin),p1 == p2) ? EOF : *p1++;
	}
	
	inline int input()
	{
		int num = 0,f = 1;
		char ch = getch();
		while(ch < '0' || ch > '9')
		{
			if(ch == '-') f = -1;
			ch = getch();
		}
		while(ch >= '0' && ch <= '9')
		{
			num = (num << 1) + (num << 3) + (ch ^ 48);
			ch = getch();
		}
		return num * f;
	}
	
	inline void printNum(int num)
	{
		if(num >= 10) printNum(num / 10);
		putchar(num % 10 + 48);
	}
	
	inline void print(int num,char ch = ' ')
	{
		if(num < 0) putchar('-'),num = -num;
		printNum(num);
		putchar(ch);
	}
}
using FastIO::input;
using FastIO::print;

const int N = 505;
struct node
{
    int x,y,step,flag;
    bool operator < (const node B) const
    {   return step > B.step;}
};
int r,c;
int A[N][N],B[N][N];
bool vis[N][N][5];
priority_queue <node> q;

bool check(int x,int y)
{
    return (x >= 1 && x <= r && y >= 1 && y <= c);
}

int main()
{
    r = input(),c = input();
    for(int i = 1;i <= r;i++)
        for(int j = 1;j < c;j++)
            A[i][j] = input();
    
    for(int i = 1;i < r;i++)
        for(int j = 1;j <= c;j++)
            B[i][j] = input();
    
    int x,y,st,f;//f表示是否是第一次使用操作4
    q.push((node){1,1,0,1});
    while(!q.empty())
    {
        auto tmp = q.top();q.pop();
    	x = tmp.x,y = tmp.y,st = tmp.step,f = tmp.flag;
		if(vis[x][y][f]) continue;
		vis[x][y][f] = 1;//注意这里判断有无访问过该点时，要记得分类讨论f
        if(x == r && y == c) {print(st);return 0;}

        if(check(x,y+1))
			q.push((node){x,y+1,st+A[x][y],1});
        if(check(x,y-1))
			q.push((node){x,y-1,st+A[x][y-1],1});
        if(check(x+1,y))
			q.push((node){x+1,y,st+B[x][y],1});
        if(check(x-1,y))
			q.push((node){x-1,y,st+1+f,0});//这里压了一下行，直接加上f效果是一样的
    }
}
```


---

