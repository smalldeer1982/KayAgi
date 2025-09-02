# [ABC339D] Synchronized Players

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc339/tasks/abc339_d

$ N $ 行 $ N $ 列のグリッドがあり、各マスは空きマスか障害物のあるマスのいずれかです。グリッドの上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と表記します。

また、$ 2 $ 人のプレイヤーがグリッド上の相異なる空きマス上におり、各マスの情報は $ N $ 個の長さ $ N $ の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ として以下の形式で与えられます。

- $ S_i $ の $ j $ 文字目が `P` であるとき、$ (i,\ j) $ は空きマスであり、プレイヤーがいる
- $ S_i $ の $ j $ 文字目が `.` であるとき、$ (i,\ j) $ は空きマスであり、プレイヤーがいない
- $ S_i $ の $ j $ 文字目が `#` であるとき、$ (i,\ j) $ は障害物のあるマスである
 
以下の操作を繰り返し $ 2 $ 人のプレイヤーを同じマスに集めるために必要な操作回数の最小値を求めてください。ただし、操作の繰り返しにより $ 2 $ 人のプレイヤーを同じマスに集めることができない場合には `-1` を出力してください。

- 上下左右のいずれかの方向を決める。そして各プレイヤーはともにその方向に隣接するマスへの移動を試みる。各プレイヤーは移動先のマスが存在し、かつ空きマスであるならば移動し、そうでないならば移動しない。

## 说明/提示

### 制約

- $ N $ は $ 2 $ 以上 $ 60 $ 以下の整数
- $ S_i $ は長さ $ N $ の `P`, `.`, `#` からなる文字列
- $ S_i $ の $ j $ 文字目が `P` であるような組 $ (i,\ j) $ の個数はちょうど $ 2 $ つ
 
### Sample Explanation 1

はじめに $ (3,\ 2) $ にいるプレイヤーをプレイヤー $ 1 $、$ (4,\ 3) $ にいるプレイヤーをプレイヤー $ 2 $ とします。 例えば以下のようにすることで、$ 3 $ 回の操作で $ 2 $ 人のプレイヤーが同じマスに集まります。 - 左を選択する。プレイヤー $ 1 $ は $ (3,\ 1) $ に移動し、プレイヤー $ 2 $ は $ (4,\ 2) $ に移動する。 - 上を選択する。プレイヤー $ 1 $ は移動せず、プレイヤー $ 2 $ は $ (3,\ 2) $ に移動する。 - 左を選択する。プレイヤー $ 1 $ は移動せず、プレイヤー $ 2 $ は $ (3,\ 1) $ に移動する。

## 样例 #1

### 输入

```
5
....#
#..#.
.P...
..P..
....#```

### 输出

```
3```

## 样例 #2

### 输入

```
2
P#
#P```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
..........
..........
..........
..........
....P.....
.....P....
..........
..........
..........
..........```

### 输出

```
10```

# 题解

## 作者：cjh20090318 (赞：11)

思维难度不大，但是实现有很多小细节。

## 题意

有一个 $N \times N$ 的网格 $S$，其中 `.` 表示空地，`P` 表示空地上有一个玩家，`#` 表示障碍物。

你需要选择上、下、左、右四个方向之一带着两个玩家向同一个方向的相邻单元格移动。如果目标单元格存在且为空，则每个玩家移动，否则不移动。

## 分析

数据范围很小且给了一个地图，考虑广度优先搜索。

和其他简单的广度优先搜索题目不同，这次有两个点移动而非一个点，我们只需要把两个点移动视作一个点就可以了。

剩下的就是实现细节。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n;
char s[66][66];
const int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};//方位数组，方便移动。
bool d[66][66][66][66];
struct Node{
	int X1,Y1,X2,Y2,D;
	Node(int _X1=0,int _Y1=0,int _X2=0,int _Y2=0,int _D=0):X1(_X1),Y1(_Y1),X2(_X2),Y2(_Y2),D(_D){}
};//将两个玩家的位置压进同一个状态。
queue<Node> Q;//广度优先搜索。
int main(){
	scanf("%d",&n);
	int p1x=0,p1y=0,p2x=0,p2y=0;//两个玩家的初始位置。
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++)if(s[i][j]=='P'){
			if(p1x||p1y) p2x=i,p2y=j;
			else p1x=i,p1y=j;
		}
	}
	Q.emplace(p1x,p1y,p2x,p2y,0);
	int ans=0x3f3f3f3f;//将答案赋为极大值。
	for(Node u;!Q.empty();){
		u=Q.front();Q.pop();
		if(d[u.X1][u.Y1][u.X2][u.Y2]) continue;
		d[u.X1][u.Y1][u.X2][u.Y2]=1;
		if(u.X1==u.X2 && u.Y1==u.Y2){
			ans=min(ans,u.D);//更新最小值。
			continue;//不继续移动，停止。
		}
		for(int k=0,n1x,n1y,n2x,n2y;k<4;k++){
			n1x=u.X1+dx[k],n1y=u.Y1+dy[k],n2x=u.X2+dx[k],n2y=u.Y2+dy[k];//试图向四个方向移动，下一个位置。
			if(n1x<1||n1x>n||n1y<1||n1y>n||s[n1x][n1y]=='#') n1x=u.X1,n1y=u.Y1;//无法到达就回退。
			if(n2x<1||n2x>n||n2y<1||n2y>n||s[n2x][n2y]=='#') n2x=u.X2,n2y=u.Y2;
			Q.emplace(n1x,n1y,n2x,n2y,u.D+1);//距离加一。
		}
	}
	printf("%d\n",ans>=0x3f3f3f3f?-1:ans);//答案仍然是极大值，说明无法到达。
	return 0;
}
```

---

## 作者：apiad (赞：2)

我们叫两个玩家为 $A$ 和 $B$，设状态 $(a,b,c,d)$ 为 $A$ 在 $(a,b)$ 下标，$B$ 在 $(c,d)$ 下标时的最短路。我们单独判断 $A$ 和 $B$ 分别是否可以走，不可以走的话，就继承之前的点，否则就继续移动。按照这个方法，直接跑 Dij 暴力过去即可。就转移稍微分类讨论一下，其他的都是一样的最短路写法。

时间复杂度应该是 $O(n^4 \log n)$，对于 $n$ 那么小几乎不用考虑时间复杂度了。

[https://atcoder.jp/contests/abc339/submissions/49987794](https://atcoder.jp/contests/abc339/submissions/49987794)。

---

## 作者：Milthm (赞：2)

容易发现 $n\le 60$，于是可以想到搜索。

再看一眼，发现是求最少移动，应该是广搜。

再看一眼，只有两个玩家，状态只有 $n^2\times n^2=n^4$ 种，根本不会超时。

所以这就是一个广搜题，暴力广搜就可以了。

### AC code

```cpp
#include<bits/stdc++.h>
#define N 65
#define int long long
using namespace std;
int n,w[4][2]={{0,1},{1,0},{-1,0},{0,-1}},x,y,x2,y2,vis[N][N][N][N];
char a[N][N];
struct node{
	int x,y,x2,y2,d;
};
queue<node>q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>a[i][j];
			if(a[i][j]=='P'){
				if(!x)x=i,y=j;
				else x2=i,y2=j;
			}
		}
	}
	q.push({x,y,x2,y2,0});
	while(!q.empty()){
		node c=q.front();q.pop();
		x=c.x,y=c.y,x2=c.x2,y2=c.y2;
		if(x==x2&&y==y2){
			cout<<c.d;return 0;
		}
		if(vis[x][y][x2][y2])continue;
		vis[x][y][x2][y2]=1;
		for(int i=0;i<4;++i){
			int px=x+w[i][0],py=y+w[i][1];
			int px2=x2+w[i][0],py2=y2+w[i][1];
			if(!(px>=1&&px<=n&&py>=1&&py<=n)||a[px][py]=='#')px=x,py=y;
			if(!(px2>=1&&px2<=n&&py2>=1&&py2<=n)||a[px2][py2]=='#')px2=x2,py2=y2;
			q.push({px,py,px2,py2,c.d+1});
		}
	}
	cout<<-1;
	return 0;
}

```


---

## 作者：spire001 (赞：2)

## AT_abc339D题解

考虑到时限四秒，暴力 `bfs` 搜索。

将四个坐标用百进制拼在一起，哈希标记判重即可通过。

代码很好实现，速度不算很慢，最慢的点花了不到一秒。

### CODE

```cpp
# include <iostream>
# include <climits>
# include <charconv>
# include <cstring>
# include <algorithm>
# include <queue>
# include <vector>
# include <cstdio>
# define N 262
# include <ext/pb_ds/assoc_container.hpp>
# include <ext/pb_ds/hash_policy.hpp>
using namespace std;
constexpr int gox[] = {0 , 1 , 0 , -1};
constexpr int goy[] = {1 , 0 , -1 , 0};
string s;
char a[N][N];
__gnu_pbds::gp_hash_table <int , bool> box;//哈希表
int n;
struct node{
	int x , y;
	int xx , yy;
	int t;
}beg;

queue <node> q;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
			if(a[i][j] == 'P')
			{
				if(!beg.x)
				{
					beg.x = i;//找起点
					beg.y = j;
				}
				else
				{
					beg.xx = i;
					beg.yy = j;
				}
			}
		}
		
	q.push(beg);//初始状态
	int ans = -1;
	while(!q.empty())
	{
		auto tmp = q.front();q.pop();
		if(tmp.x == tmp.xx && tmp.y == tmp.yy)
		{
			ans = tmp.t;
			break;//找到了
		}
		auto nx = tmp;
		nx.t++;
		for(int i = 0; i != 4; i++)
		{
			nx.x = tmp.x + gox[i];
			nx.y = tmp.y + goy[i];
			if(a[nx.x][nx.y] == '#' || nx.x <= 0 || nx.x > n || nx.y <= 0 || nx.y > n)
			{
				nx.x = tmp.x;//注意这里不是continue，而是不动
				nx.y = tmp.y;
			}
			nx.xx = tmp.xx + gox[i];
			nx.yy = tmp.yy + goy[i];
			if(a[nx.xx][nx.yy] == '#' || nx.xx <= 0 || nx.xx > n || nx.yy <= 0 || nx.yy > n) 
			{
				nx.xx = tmp.xx;//注意这里不是continue，而是不动
				nx.yy = tmp.yy;
			}
			int tag = 0;
			tag = nx.x + nx.y * 100 + nx.xx * 10000 + nx.yy * 1000000;
			if(box[tag]) continue;//标记，防止重复状态导致超时
			else box[tag] = true;
			q.push(nx);
		}
	}
	cout << ans;//没找到ans就是初始值-1
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)


###### 前提提要：本题使用了广度优先搜索（BFS）算法

[题目链接](https://www.luogu.com.cn/problem/AT_abc339_d)

问题简述：给定一个 $N \times N$ 网格，其中包含两个玩家和一些障碍物。玩家可以从四个方向中选择一个移动，但不能穿越障碍物。目标是找到将两个玩家带到同一格所需的最少步数。如果无法将两个玩家带到同一格，则输出 ```-1```。

思路：

1. 可以先将每个状态定义为两个玩家的坐标。从两个起始点开始，将它们作为初始状态放入队列中。

2. 开始迭代队列，每次迭代处理队列中的一层节点。对于每个节点，尝试从四个方向移动玩家，并更新他们的坐标。如果新的坐标是有效的且未被访问过，则将其标记为已访问，并将其添加到队列中。

通过这种方式，就可以逐层扩展搜索，直到找到两个玩家的坐标相同时。这意味着找到了一条路径，可以将两个玩家带到同一格。然后可以返回当前的步数作为结果。

如果队列为空，表示无法将两个玩家带到同一格，即不存在路径。在这种情况下，返回 ```-1```。



------------

证明：通过使用BFS算法，可以保证找到的路径是最短路径（逐层扩展搜索的）。这是因为首先访问距离起始点最近的节点，然后逐渐向外扩展。因此，当找到两个玩家的坐标相同时，可以确保这是最短路径。

#### 总结思路 ~~（简化）~~ ：从两个起始点开始，通过逐层扩展搜索，找到将两个玩家带到同一格所需的最少步数。


AC code：
```
#include <bits/stdc++.h>
using namespace std;
//免责声明：本人码风不好，不喜勿喷
const int MAXN = 60;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

int N;
string grid[MAXN];
bool visited[MAXN][MAXN][MAXN][MAXN];

bool valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && grid[x][y] != '#';
}
int bfs(pair<int, int> start1, pair<int, int> start2) {
    queue<pair<pair<int, int>, pair<int, int>>> q;
    q.push(make_pair(start1, start2));
    visited[start1.first][start1.second][start2.first][start2.second] = true;

    int steps = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto front = q.front(); q.pop();
            auto p1 = front.first;
            auto p2 = front.second;
            if (p1 == p2) return steps;

            for (int i = 0; i < 4; ++i) {
                int nx1 = p1.first + dx[i], ny1 = p1.second + dy[i];
                int nx2 = p2.first + dx[i], ny2 = p2.second + dy[i];

                if (!valid(nx1, ny1)) { nx1 = p1.first; ny1 = p1.second; }
                if (!valid(nx2, ny2)) { nx2 = p2.first; ny2 = p2.second; }

                if (!visited[nx1][ny1][nx2][ny2]) {
                    visited[nx1][ny1][nx2][ny2] = true;
                    q.push(make_pair(make_pair(nx1, ny1), make_pair(nx2, ny2)));
                }
            }
        }
        ++steps;
    }
    return -1;
}
int main() {
    cin >> N;
    pair<int, int> start1, start2;
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'P') {
                if (start1.first == 0 && start1.second == 0) start1 = {i, j};
                else start2 = {i, j};
            }
        }
    }

    cout << bfs(start1, start2) << endl;
    return 0;
}
```



---

## 作者：Genius_Star (赞：1)

### 思路：

定义 $dis_{a,b,c,d}$ 表示使得第一个人在 $(a,b)$，第二个人在 $(c,d)$ 的最小操作数。

初始 $dis_{A,B,C,D}=0$，其他点为正无穷，即第一个人刚开始在 $(A,B)$，第二个人刚开始在 $(C,D)$；然后 dijkstra 或者 bfs 跑最短路即可。

时间复杂度：$O(N^4 \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=65,INF=1e18;
inline ll read(){
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
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll data;
	ll a,b,c,d;
	bool operator<(const Node&rhs)const{
		return rhs.data<data;
	}
};
ll n,X1,Y1,X2,Y2,ans=INF;
ll A[N][N];
ll dis[N][N][N][N];
bool f[N][N][N][N];
priority_queue<Node> Q;
ll dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char c;
void dijkstra(){
    while(!Q.empty()){
        Node t=Q.top();
        Q.pop();
        ll a=t.a,b=t.b,c=t.c,d=t.d;
        if(f[a][b][c][d])
          continue;
        f[a][b][c][d]=1;
        for(int i=0;i<4;i++){
        	ll a1=a+dx[i],b1=b+dy[i];
        	ll c1=c+dx[i],d1=d+dy[i];
        	if(a1<1||a1>n||b1<1||b1>n)
        	  a1=a,b1=b;
        	if(c1<1||d1>n||c1<1||d1>n)
        	  c1=c,d1=d;
        	if(A[a1][b1]==-1)
        	  a1=a,b1=b;
        	if(A[c1][d1]==-1)
        	  c1=c,d1=d;
        	if(dis[a1][b1][c1][d1]>dis[a][b][c][d]+1){
        		dis[a1][b1][c1][d1]=dis[a][b][c][d]+1;
        		Q.push({dis[a1][b1][c1][d1],a1,b1,c1,d1});
			}
		}
    }
}
int main(){
	n=read();
	for(int a=1;a<=n;a++)
	  for(int b=1;b<=n;b++)
	    for(int c=1;c<=n;c++)
	      for(int d=1;d<=n;d++)
	        dis[a][b][c][d]=INF;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%c",&c);
			if(c=='#')
			  A[i][j]=-1;
			else
			  A[i][j]=1;
			if(c=='P'){
				if(X1){
					X2=i;
					Y2=j;
				}
				else{
					X1=i;
					Y1=j;
				}
			}
		}
		getchar();
	}
	dis[X1][Y1][X2][Y2]=0;
	dis[X2][Y2][X1][Y1]=0;
	Q.push({0,X1,Y1,X2,Y2});
	Q.push({0,X2,Y2,X1,Y1});
	dijkstra();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    ans=min(ans,dis[i][j][i][j]);
	write(ans==INF?-1:ans);
	return 0;
}
```


---

## 作者：CheZiHe929 (赞：1)

# AT_abc339_d 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc339/tasks/abc339_d)

[Luogu](https://www.luogu.com.cn/problem/AT_abc339_d)

### 题目大意

有一个 $n \times n$ 的网格：

- 如果 $c_{i,j}$ 为 `P`，则说明 $(i,j)$ 为空地，且上面有一个棋手（共有两个棋手）。

- 如果 $c_{i,j}$ 为 `.`，则说明 $(i,j)$ 为空地。 

- 如果 $c_{i,j}$ 为 `#`，则说明 $(i,j)$ 为障碍物。 

你可以选择上下左右共四个方向，同时将两位棋手移动，问将两位棋手移动到同一位置所需要的最小步数。如果不能移动至同一位置，则输出 `-1`。

### 简要思路

$BFS$。

队列的类型设为一个结构体，里面存着两位棋手的坐标和当前的步数。

注意设立一个四维的 `vis` 数组，`vis[i][j][k][l]` 表示是否出现过棋手一走到 $(i,j)$ 且棋手二走到 $(k,l)$ 的情况，并注意实时更新即可。

如果出现两人坐标一致的情况下，直接返回当前答案即可，因为我们是按照步数从小到大的顺序加入到队列中的，所以这个答案一定是最小步数。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=65;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int n;
char c[MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN][MAXN];
struct node{int a,b,c,d,ans;};
int px1,px2,py1,py2;//两位棋手的坐标
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};//偏移量
std::queue<node> q;

bool check(int x,int y){//判断当前位置能否走到
	if(x<1||x>n||y<1||y>n||c[x][y]=='#')return false;
	else return true;
}

int bfs(){
	q.push({px1,py1,px2,py2,0});//初始情况加入
	vis[px1][py1][px2][py2]=1;//情况标记为 true
	while(q.size()){
		int x1=q.front().a;
		int y1=q.front().b;
		int x2=q.front().c;
		int y2=q.front().d;
		//我因为没用 using namespace std 所以才用的 x1,x2,y1,y2
		int now=q.front().ans;
		q.pop();
		
		if(x1==x2&&y1==y2)return now;//坐标一致，直接返回
		else{
			for(int i=0;i<4;i++)
				if(check(x1+dx[i],y1+dy[i])||check(x2+dx[i],y2+dy[i])){//判断两位棋手能否移动
					int _x1=x1,_x2=x2,_y1=y1,_y2=y2;
					if(check(x1+dx[i],y1+dy[i]))_x1+=dx[i],_y1+=dy[i];
					if(check(x2+dx[i],y2+dy[i]))_x2+=dx[i],_y2+=dy[i];//分别看能否移动
					if(!vis[_x1][_y1][_x2][_y2]){//情况未出现过
						vis[_x1][_y1][_x2][_y2]=1;
						q.push({_x1,_y1,_x2,_y2,now+1});//当前情况加入到队列中
					}
				}
		}
	}
	return -1;//无法走到一起
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			std::cin>>c[i][j];
			if(c[i][j]=='P'){
				if(!px1)px1=i,py1=j;
				else px2=i,py2=j;//记录两位棋手位置
			}
		}
	put(bfs(),1,1);
	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc339/submissions/49984057)

[Luogu](https://www.luogu.com.cn/record/146034212)

**THE END.**

**THANK YOU.**

---

## 作者：Starrykiller (赞：1)


纪念一下首次 AK ABC。

直接 bfs 即可。由于状态数最多为 $\Theta(n^4)$ 所以复杂度是对的。

需要注意的是，需要在 push 之前检查是否 vis 过，以及设置 vis。否则可能造成 [MLE](https://atcoder.jp/contests/abc339/submissions/49965131) 等问题。

```cpp
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

#define int long long 
using ll=atcoder::modint998244353;

constexpr int MAXN=61;
char a[MAXN][MAXN]; int n;
bool vis[MAXN][MAXN][MAXN][MAXN];
struct node {
    int a,b,c,d,step;
}; int tx1, tx2, ty1, ty2;

bool check(int i, int j) {
    return i>=1 && i<=n && j>=1 && j<=n && a[i][j]!='#';
}

int dx[]={0,1,0,-1}, dy[]={-1,0,1,0};

int bfs() {
    queue<node> q; 
    q.push({tx1,ty1,tx2,ty2,0}); vis[tx1][ty1][tx2][ty2]=1;
    while (q.size()) {
        auto [x1,y1,x2,y2,step]=q.front(); q.pop();
        if (x1==x2&&y1==y2) return step;
        for (int t=0; t<4; ++t) { if (check(x1+dx[t],y1+dy[t]) || check(x2+dx[t],y2+dy[t])) {
            int tx1=x1, ty1=y1, tx2=x2, ty2=y2;
            if (check(x1+dx[t],y1+dy[t]))
                tx1+=dx[t], ty1+=dy[t];
            if (check(x2+dx[t],y2+dy[t]))
                tx2+=dx[t], ty2+=dy[t];
            if (!vis[tx1][ty1][tx2][ty2]) {
                vis[tx1][ty1][tx2][ty2]=1;
                q.push({tx1,ty1,tx2,ty2,step+1});
            }
        }}
    }
    return -1;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n;
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
        cin>>a[i][j];
        if (a[i][j]=='P') {
            if (tx1) tx2=i, ty2=j;
            else tx1=i, ty1=j;
        }
    }
    cout<<bfs();
    
}
```

---

## 作者：LiJoQiao (赞：1)

### 题意  
>有两个人在不同位置，每次可以选择一个方向使两人向那个方向移动，如只有一个人不能向那个方向移动就只让另一个人移动，求两个人到一个格子的最小步数。  

由于两个人所在位置的情况数不超过 $60^4$，我们直接上一个 BFS 或 Dijkstra 即可解决。  

到达边界或碰到障碍物就不能移动了，这时不能移动的人会待在原地，否则就朝他的方向移动。  

BFS 的过程中要对每个状态都记一下是否访问过，不然复杂度会炸掉。  

终止条件就是两个人的坐标完全相同，此时结束 BFS 即可。  

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int MAXN=70,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
char g[MAXN][MAXN];
int n,tot;
struct loc{
	int x,y;
}pl[5];
struct loca{
	loc x,y;int step;
};
queue<loca>q;
bool vis[MAXN][MAXN][MAXN][MAXN];
int ans=-1;
namespace sol{
	loc check(loc x,int d){
		int nx=x.x+dx[d],ny=x.y+dy[d];
		if(nx&&ny&&nx<=n&&ny<=n&&g[nx][ny]!='#')return (loc){nx,ny};
		return x;
	}
	void bfs(){
		q.push((loca){pl[1],pl[2],0});
		loca now=q.front(); 
		vis[now.x.x][now.x.y][now.y.x][now.y.y]=1;
		while(!q.empty()){
			now=q.front();q.pop();
			for(int i=0;i<4;++i){
				loc n1=check(now.x,i),n2=check(now.y,i);
				if(n1.x==n2.x&&n1.y==n2.y){
					ans=now.step+1;
					return;
				}
				if(!vis[n1.x][n1.y][n2.x][n2.y]){
					q.push((loca){n1,n2,now.step+1});
					vis[n1.x][n1.y][n2.x][n2.y]=1;
				}
			}
		}
	}
	void solve(){
		cin>>n;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j){
				cin>>g[i][j];
				if(g[i][j]=='P'){
					pl[++tot]={i,j};
				}
			}
		bfs();
		cout<<ans<<'\n';
	}
}
int main(){
	sol::solve();
	return 0;
}
```

---

## 作者：RandomLife (赞：0)

# 题意

在一个 $N\times N$ 的地图上，有两个人，还有一些障碍物，其余的是空地。我们可以进行若干次操作，每次操作选择上下左右，两个人都会试图向指定方向移动。但对于每个人，如果他移动后会到达障碍物或地图外面，则不移动。问至少要多少此操作可以将两个人移到同一位置，或给出无法做到。

# 题解

刚开始时，我考虑贪心：先不断向上走，使他们横坐标对齐，再不断向左走。但是，这样做，较下的人可能会被障碍物卡住，这就延伸出了很多情况，极其复杂，于是很快便被我否决了。

结果当我漫无目的的刷着题面是，才发现有 $N\leq 60$。（~~呵呵我瞎~~）

这就好办了，考虑 bfs。设状态 $dis_{x_1,y_1,x_2,y_2}$ 表示第一个人在 $(x_1,y_1)$，第二个人在 $(x_2,y_2)$，最少要用的步数。每次可以向四个方向移动后的状态转移。

显然，状态总数至多为 $N^4$，因此时空复杂度都为 $\Theta(N^4)$。算出来差不多也就 2000 万，虽然常数大了点，但这题时限开到了 4s，通过绰绰有余。

温馨提示：千万不要用 map 记录状态，否则 T 飞！！！（~~本人痛吃罚时~~）

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=65;
struct Node{
	int x1,y1,x2,y2;
	friend bool operator<(Node x,Node y){
		if(x.x1==y.x1){
			if(x.y1==y.y1){
				if(x.x2==y.x2)return x.y2<y.y2;
				return x.x2<y.x2;
			}
			return x.y1<y.y1;
		}
		return x.x1<y.x1;
	}
};
int n,p[2][2],tot=-1,ans=-1,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},cnt=0,dis[N][N][N][N];
bool vis[N][N][N][N];
char a[N][N];
queue<Node>q;
bool solve(int x,int y){
	return a[x][y]!='#'&&x>=1&&x<=n&&y>=1&&y<=n;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		scanf("%s",a[i]+1);
		for(int j=1;j<=n;++j)
			if(a[i][j]=='P')p[++tot][0]=i,p[tot][1]=j;
	}
	Node start=Node{p[0][0],p[0][1],p[1][0],p[1][1]};
	q.push(start),dis[start.x1][start.y1][start.x2][start.y2]=0;
	while(!q.empty()){
		Node node=q.front(),Next;
		if(node.x1==node.x2&&node.y1==node.y2){
			ans=dis[node.x1][node.y1][node.x2][node.y2];
			break;
		}
		vis[node.x1][node.y1][node.x2][node.y2]=true,q.pop();
		for(int i=0;i<4;++i){
			Next=node;
			Next.x1+=dx[i],Next.x2+=dx[i],Next.y1+=dy[i],Next.y2+=dy[i];
			if(!solve(Next.x1,Next.y1))Next.x1-=dx[i],Next.y1-=dy[i];
			if(!solve(Next.x2,Next.y2))Next.x2-=dx[i],Next.y2-=dy[i];
			if(!vis[Next.x1][Next.y1][Next.x2][Next.y2]){
				vis[Next.x1][Next.y1][Next.x2][Next.y2]=true;
				dis[Next.x1][Next.y1][Next.x2][Next.y2]=dis[node.x1][node.y1][node.x2][node.y2]+1;
				q.push(Next);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc339_d)

题意：现在平面上有两个人，一些障碍，一些空地，每次两个人可以向同一方向移动，如果移动到的目标超出边界或为障碍，就不移动。

没啥好说的，直接广搜就行，拿个数组存两个人的位置记录一下是否被访问过就行。

时间：$O(n^{4})$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,fx,fy,tx,ty;
int dx[4]={1,0,0,-1};
int dy[4]={0,1,-1,0};
char c[65][65];
int mp[65][65][65][65];
struct node{
	int tx,ty,fx,fy,ans;
};
int bfs(){
	queue<node> q;
	q.push({tx,ty,fx,fy,0});
	while(q.size()){
		node p=q.front();q.pop();
		tx=p.tx,ty=p.ty,fx=p.fx,fy=p.fy;
		if(tx==fx&&ty==fy) return p.ans;
		if(mp[tx][ty][fx][fy]||mp[fx][fy][tx][ty]) continue;
		mp[tx][ty][fx][fy]=mp[fx][fy][tx][ty]=1;
		for(int i=0;i<4;i++){
			int ltx=tx,lty=ty,lfx=fx,lfy=fy;
			tx+=dx[i],ty+=dy[i];
			fx+=dx[i],fy+=dy[i];
			if(tx<1||ty<1||tx>n||ty>n||c[tx][ty]=='#') tx-=dx[i],ty-=dy[i];
			if(fx<1||fy<1||fx>n||fy>n||c[fx][fy]=='#') fx-=dx[i],fy-=dy[i];
			q.push({tx,ty,fx,fy,p.ans+1});
			tx=ltx,ty=lty,fx=lfx,fy=lfy;
		}
	}
	return -1;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
			if(c[i][j]=='P'){
				if(!tx) tx=i,ty=j;
				else fx=i,fy=j;
				c[i][j]='.';
			}
		}
	}
	cout<<bfs();
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

我看到是这种网格的，还是求最小步数的，那铁定广搜了。

首先我们考虑能不能将这两个人当前所在的格子绑在一起，这样就能用四维表示状态，统计最短步数和是否遍历过。

看一下数据范围，发现 $2 \le N \le 60$，那么 $60^4$ 是 $12960000$，空间完全不会炸。

对于时间复杂度，因为我们是广搜，每一个状态就最多被遍历一遍，所以时间复杂度也不会炸。

那么剩下的就是一些细节上的问题了，比如在一个人不能走动的时候，具体看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 65;
bool vis[N][N][N][N];
int d[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
int n;
int dist[N][N][N][N];
bool a[N][N];
int x = -1, y, xx = -1, yy;
bool init(int x, int y) {
	return (x < 1 || y < 1 || x > n || y > n || a[x][y]);
}
int bfs(int x, int y, int xx, int yy, int dist[N][N][N][N]) {
	memset(vis, 0, sizeof(vis));
	queue<pair<pair<int, int> , pair<int, int> > > q;
	q.push(mp(mp(x, y), mp(xx, yy)));
	vis[x][y][xx][yy] = 1;
	dist[x][y][xx][yy] = 0;
	while (q.size()) {
		auto t = q.front();
		//cout << t.x.x << ' ' << t.x.y << ' ' << t.y.x << ' ' << t.y.y << '\n';
		if (t.x.x == t.y.x && t.y.y == t.x.y) {
			return dist[t.x.x][t.x.y][t.y.x][t.y.y];
		}
		q.pop();
		for (int i = 0; i < 4; i++) {
			int tx = t.x.x + d[i][0], ty = t.x.y + d[i][1];
			int txx = t.y.x + d[i][0], tyy = t.y.y + d[i][1];
			if (init(tx, ty)) tx = t.x.x, ty = t.x.y;
			if (init(txx, tyy)) txx = t.y.x, tyy = t.y.y;
			if (!vis[tx][ty][txx][tyy]) {
				q.push(mp(mp(tx, ty), mp(txx, tyy)));
				vis[tx][ty][txx][tyy] = 1;
				dist[tx][ty][txx][tyy] = dist[t.x.x][t.x.y][t.y.x][t.y.y] + 1;
			}
		}
	}
	return -1;
}
int main() {
	//cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	For(i, 1, n) {
		string s;
		cin >> s;
		For(j, 0, n - 1) {
			if (s[j] == '#') a[i][j + 1] = 1;
			if (s[j] == 'P') {
				if (x == -1) x = i, y = j + 1;
				else xx = i, yy = j + 1;
			}
		}
	}
	For(i, 1, n) {
		For(j, 1, n) {
			For(k, 1, n) {
				For(l, 1, n) {
					dist[i][j][k][l] = 1e9;
				}
			}
		}
	}
	cout << bfs(x, y, xx, yy, dist);
	return 0;
} 
```

### 谢谢观看

---

## 作者：Crazyouth (赞：0)

## 分析

显然这题两人的状态数不超过 $O(n^4)$，所以开 `map` 储存每个状态是否访问过，bfs 暴搜，记录当前步数，如果两人在同一格，结束。这里用了个 trick，把棋盘边缘全部变成 `#` 可避免越界。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
string s[100];
map<pair<pair<int,int>,pair<int,int>>,int> vis;
void bfs(int x1,int y1,int x2,int y2)
{
	queue<pair<pair<int,int>,pair<int,int>>> q;
	queue<int> step;
	q.push({{x1,y1},{x2,y2}});
	step.push(0);
	while(!q.empty())
	{
		int nx1=q.front().first.first,ny1=q.front().first.second,nx2=q.front().second.first,ny2=q.front().second.second;
		int st=step.front();
		q.pop();
		step.pop();
		//cout<<"now at ("<<nx1<<','<<ny1<<") and ("<<nx2<<','<<ny2<<')'<<endl;
		if(nx1==nx2&&ny1==ny2)
		{
			cout<<st;
			exit(0);
		}
		for(int i=0;i<4;i++)
		{
			int xx1=nx1,xx2=nx2,yy1=ny1,yy2=ny2;
			if(s[nx1+dx[i]][ny1+dy[i]]!='#') xx1+=dx[i],yy1+=dy[i];
			if(s[nx2+dx[i]][ny2+dy[i]]!='#') xx2+=dx[i],yy2+=dy[i];
			//cout<<"check "<<s[xx1][yy1]<<endl;
			//cout<<"now is ("<<xx1<<','<<yy1<<") and ("<<xx2<<','<<yy2<<')'<<endl;
			if(vis[{{xx1,yy1},{xx2,yy2}}]||xx1<1||xx1>n||yy1<1||yy1>n||xx2<1||xx2>n||yy2<1||yy2>n) continue;
			vis[{{xx1,yy1},{xx2,yy2}}]=1;
			q.push({{xx1,yy1},{xx2,yy2}});
			//cout<<"pushed ("<<xx1<<','<<yy1<<") and ("<<xx2<<','<<yy2<<')'<<endl;
			step.push(st+1);
		}
	}
}
int main()
{
	int x1=0,y1,x2,y2;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]='#'+s[i]+'#';
	for(int i=0;i<=n+1;i++) s[0]+='#',s[n+1]+='#';
//	for(int i=0;i<=n+1;i++)
//	{
//		for(int j=0;j<=n+1;j++)
//		cout<<s[i][j];
//		cout<<endl;
//	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(s[i][j]=='P'&&!x1) x1=i,y1=j;
		else if(s[i][j]=='P') x2=i,y2=j;
	}
	bfs(x1,y1,x2,y2);
	cout<<-1;
	return 0;
}

---

## 作者：Loser_Syx (赞：0)

状态数不多，每个人最多 $n^2$ 种状态，两个人一共 $n^4$ 种状态，约为 $10^7$ 种，可以考虑 bfs。

我们将每个人目前在的位置和当前的步数打包入队，然后枚举方向，计算每个人现在的位置。

但是注意如果位置不合法是不动。

最后判断是否已被访问过这个状态了，因为是 bfs 队列维护的，所以可以保证一定是按照步数升序搞的。

双倍经验 P3610。

[代码](https://atcoder.jp/contests/abc339/submissions/49932450)。

---

## 作者：yyrwlj (赞：0)

## 题意简述

棋盘上有两枚棋子，有些格子可以到达，有些不能，不能超出边界。

每次可以让两枚棋子朝相同的方向移动，若某个棋子的下一个位置不允许到达，则该棋子这次不会移动。求将两枚棋子移动到同一格

## 思路

考虑 bfs，因为 $n \le 60$，所以总状态数最多是 $60^4 = 12960000$，不会超时和超空间。

队列同时记录两个棋子的位置，然后记忆化一下，不走重复的状态。

然后按照题意模拟即可，如果某个棋子扩展出来的位置无法到达，那就让它保持不动就行。

## Code

```cpp
const int mx[4] = {0, 1, 0, -1}, my[4] = {1, 0, -1, 0};
struct Node{
    int x1, y1, x2, y2, s;
};
int main()
{
    cin >> n;
    int x1 = 0, y1, x2, _y2; 
    memset(a, '#', sizeof a);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 'P')
            {
                if (x1)
                    x2 = i, _y2 = j;
                else
                    x1 = i, y1 = j;
            }
        }
    f[x1][y1][x2][_y2] = true;
    q.push({x1, y1, x2, _y2, 0});
    while (!q.empty())
    {
        Node t = q.front();
        q.pop();
        if (t.x1 == t.x2 && t.y1 == t.y2)
        {
            printf("%d", t.s);
            return 0;
        }
        for (int i=0;i<4;i++)
        {
            int nx1 = t.x1 + mx[i], ny1 = t.y1 + my[i];
            int nx2 = t.x2 + mx[i], ny2 = t.y2 + my[i];
            if (a[nx1][ny1] == '#')
                nx1 = t.x1, ny1 = t.y1;
            if (a[nx2][ny2] == '#')
                nx2 = t.x2, ny2 = t.y2;
            if (f[nx1][ny1][nx2][ny2])
                continue;
            f[nx1][ny1][nx2][ny2] = true;
            q.push({nx1, ny1, nx2, ny2, t.s + 1});
        }
    }
    puts("-1");
    return 0;
}
```

---

