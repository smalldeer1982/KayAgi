# Crazy Robot

## 题目描述

有一个网格，由  $n$ 行和 $m$ 列组成。网格的每个单元格要么是空的，要么是被阻塞的。其中有一个空单元内有一个实验室。超出网格边界的所有单元格也被阻塞。

一个疯狂的机器人从一个实验室逃了出来。它目前在网格的一些空单元中。您可以向机器人发送以下命令之一：“向右移动”、“向下移动”、“向左移动”或“向上移动”。每个命令意味着移动到相应方向的相邻单元格。

然而，由于机器人很疯狂，除了听从命令，它什么都会做。收到命令后，它将选择一个方向，使其与命令中的方向不同，并且该方向上的单元没有被阻塞。如果有这样的方向上的单元没有被堵塞，那么它就会移动到那个方向上的相邻单元格。否则，它什么都不做。

我们想让机器人到达实验室从而可以修理它。对于每个空单元，确定机器人是否可以从该单元开始到达实验室。也就是说，在机器人的每一步之后，都可以向机器人发送一个命令，这样无论机器人选择什么不同的方向，它最终都会进入实验室。

## 说明/提示

‎在第一个测试样例中，没有可以使机器人到达实验室的自由单元。考虑一个角单元格。给定任何方向，它将移动到相邻的边界网格，而不是一个角落。现在考虑一个非角自由单元。无论你向机器人发送什么方向，它都可以选择不同的方向，这样它就会落在角落里。‎

‎在最后一个测试样例中，您可以继续向机器人发送与实验室方向相反的命令，机器人将别无选择，只能向实验室移动。‎

## 样例 #1

### 输入

```
4
3 3
...
.L.
...
4 5
#....
..##L
...#.
.....
1 1
L
1 9
....L..#.```

### 输出

```
...
.L.
...
#++++
..##L
...#+
...++
L
++++L++#.```

# 题解

## 作者：cancan123456 (赞：7)

赛时写了个 dfs，惨烈牺牲……（关键是样例还过了）

首先我们考虑一个问题：1 个单元要想走到实验室，那么它周围的空单元（```+``` 不算）可以有几个呢？

如果有 1 个：让机器人向那个方向移动，则机器人一定会走向 ```+```，从而走向实验室。

如果有 2 个以上：无论让机器人向哪个方向移动，这个机器人总有一个能逃脱的方向可以走，那么就无法让它走回来了。

然后从实验室位置 ```bfs``` 即可。

代码：

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector < vector < char > > map;
vector < vector < bool > > vis;
int n, m;
int dx[4] = {-1,  1,  0,  0};
int dy[4] = { 0,  0, -1,  1};
int inline CBC(int x, int y) { // 输出 (x, y) 周围的 . 的个数 
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (map[x + dx[i]][y + dy[i]] == '.') {
			cnt++;
		}
	}
	return cnt;
}
void bfs(int x, int y) {
	queue < pair < int , int > > q;
	q.push(make_pair(x, y));
	vis[x][y] = true; // 为了防止起点也被改成 + 
	while (!q.empty()) {
		pair < int , int > u = q.front();
		q.pop();
		int x = u.first;
		int y = u.second;
		for (int nx, ny, i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			//  判重            能否走过去            周围的 . 个数 < 2 
			if (!vis[nx][ny] && map[nx][ny] != '#' && CBC(nx, ny) < 2) {
				vis[nx][ny] = true;
				map[nx][ny] = '+';
				q.push(make_pair(nx, ny));
			}
		}
	}
}
void inline solve() {
	cin >> n >> m;
	// 清空数组 
	map.clear();
	vis.clear();
	// resize(n + 2) 的含义: 往一个 vector 里填充 n + 2 个空 / 值为 0 的元素 
	map.resize(n + 2);
	vis.resize(n + 2);
	for (int i = 0; i < n + 2; i++) {
		map[i].resize(m + 2);
		vis[i].resize(m + 2);
	}
	// 我习惯在边上围一圈 # 来判断边界 
	for (int j = 0; j < m + 2; j++) {
		map[0][j] = '#';
		vis[0][j] = true;
		map[n + 1][j] = '#';
		vis[n + 1][j] = true;
	}
	for (int i = 1; i <= n; i++) {
		map[i][0] = '#';
		vis[i][0] = true;
		map[i][m + 1] = '#';
		vis[i][m + 1] = true;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
		}
	}
	// 找到 L 的位置 
	int Lx, Ly;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 'L') {
				Lx = i, Ly = j;
			}
		}
	}
	bfs(Lx, Ly); // 搜索 
	// 输出 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << map[i][j];
		}
		cout << "\n";
	}
}
int main() {
	int t;
	cin >> t;
	while (t -- != 0) {
		solve();
	}
	return 0;
}
```

顺便一提：#16 是这样的：

```
1
1000000 1
.
.
.
.
.
（此处省略 999990 行）
.
.
.
.
L
```

所以用 ```endl``` 输出换行会直接炸掉。

---

## 作者：让风忽悠你 (赞：2)

## 做法

这类从哪些位置出发可以到达目标点的问题实际上可以转换为从目标点出发能到打哪些点，这样一来起点就确定了。

接下来说一下搜索的大概策略，由于机器人会向反方向走，而且又要确定的路线，不难想到就是要找路径上所有点都只能走两个方向的，但是注意在判断有多少的方向前要先判断当前点是否能走。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#define N 1000005

using namespace std;

const int ax[]={0,0,1,-1},ay[]={1,-1,0,0};
int T,n,m;
int sx,sy;
string map[N];

struct node{
	int x,y;
};

int can_go(int x,int y){
	int cnt=0;
	for(int i=0;i<4;i++){
		int fx=x+ax[i],fy=y+ay[i];
		if(fx<0 || fx>n-1 || fy<0 || fy>m-1) continue;
		if(map[fx][fy]=='.') ++cnt;
	}
	return cnt;
	// 统计有多少个方向可以走 
}

void bfs(int sx,int sy){
	queue <node> q;
	q.push((node){sx,sy});
	while(!q.empty()){
		node f=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int x=f.x+ax[i],y=f.y+ay[i];
			if(x<0 || x>n-1 || y<0 || y>m-1) continue;
			if(map[x][y]!='.') continue;
			if(can_go(x,y)>=2) continue;
			// 注意判断的顺序 
			map[x][y]='+'; // 可以走就标记上 
			q.push((node){x,y});
		}
	}
}

void print(){
	for(int i=0;i<n;i++){
		cout<<map[i];
		printf("\n");
	}
		
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			cin>>map[i];
			for(int j=0;j<m;j++)
				if(map[i][j]=='L') sx=i,sy=j; // 找到目标点并将其作为起点 
		}
		bfs(sx,sy);
		print();
	}
	return 0;
} 
```


---

## 作者：Purslane (赞：1)

## Solution

搜索题 . 

考虑如果一个点是 `+` , 那么必定满足下列要求 :

- 不是障碍或实验室

- 周围只有至多一个 `.` , 也就是说 , 可以让它向空格移动 , 然后它就无路可逃 .

- 所有 `+` 构成的块必须与 `L` 联通 , 否则就会无法到达 `L` 或者从中间溜走 .

因为联通 , 所以可以从 `L` 开始搜索 . 根据数据范围 , 果断选择 `BFS` .

每次 `BFS` 拓展时 , 如果已经是 `+` 或 `L` 或 `#` , 退出 ; 如果是 `.` 且周围至多有一个 `.` , 加入队列 ; 否则退出 .

注意这里如果在周围发现了超过一个 `.` , 不能判为不合法 , 因为周围的 `.` 可能变成 `+` , 使得这个点也可以变成 `+` .

[code](https://codeforces.com/contest/1613/submission/144912593)

---

## 作者：zhangboju (赞：1)

### 简要题意

操作一个机器人在一个有障碍的 $n\times m$ 网格上移动，四联通，机器人每次 **一定不会** 按照指令行走，问从哪些网格出发，一定可以通过这样的方式到达给定终点。

### Solution

感觉做法还比较妙

考虑从终点出发开始拓展

记终点和当前所有确定可以为答案的点为 $S$

记 $deg_{i,j}=|{p|p \in con_{i,j} \land p \not\in S }|$

其中 $con_{i,j}$ 为四联通且考虑障碍意义下能到达 $(i,j)$ 的所有点

注意到当 $deg_{i,j} \le 1$ 的时候，这个点一定可以作为答案，因为此时只要往那个不在 $S$ 中的点走，就一定会到达一个可以作为答案的点，而这个点就相应的可以被作为答案

于是先预处理一边 $deg_{i,j}$，然后从终点出发 BFS，每次更新时维护一下 $deg_{i,j}$，然后判断能不能入队即可

时间复杂度 $O(\sum nm)$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)
template <typename T> inline void read(T &x)
{
	x=0;short f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;return;
}
const int N=2e6+5;
int n,m;
int id(int x,int y){return x*m+y;} 
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
string s[N];
int deg[N];
queue<pair<int,int>>q;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=0;i<n;++i) cin>>s[i];
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<m;++j)
			{
				deg[id(i,j)]=0;
				if(s[i][j]=='L') q.push({i,j});
				else if(s[i][j]=='.')
				{
					for(int d=0;d<4;++d)
					{
						int x=i+dx[d],y=j+dy[d];
						if(0<=x&&x<n&&0<=y&&y<m&&s[x][y]!='#') ++deg[id(i,j)];
					}
				} 
			}
		}
		while(!q.empty())
		{
			auto p=q.front();q.pop();
			int x=p.first,y=p.second;
			for(int d=0;d<4;++d)
			{
				int nx=x+dx[d],ny=y+dy[d];
				if(0<=nx&&nx<n&&0<=ny&&ny<m&&s[nx][ny]=='.')
				{
					--deg[id(nx,ny)];
					if(deg[id(nx,ny)]<=1)
					{
						s[nx][ny]='+';
						q.push({nx,ny});
					}
				}
			}
		}
		for(int i=0;i<n;++i) cout<<s[i]<<'\n';
	}
}
```

一个小细节是不要使用 ```std::endl```

---

## 作者：zhangjyoi (赞：0)

## CF1613E Crazy Robot 题解
### 题目大意
有一个机器人，他不听从指令，问在网格中机器人在哪些点可以被赶回实验室。
### 思路
如果我们从每一个点开始搜索，那么恭喜你，你被踢飞了。

我们看一下数据范围，$n \cdot m \le 10^6$，应该是 $O(nm)$ 的算法。所以我们想到了广搜。

我们从实验室搜起，如果当前位置有至少两个自由点，这个点就不符合要求。反之，这个点符合条件。
## ACode
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define f1 first
#define s2 second
#define pii pair<int,int>
using namespace std;
string a[1000050];
int T,n,m,lx,ly; 
const int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
queue<pii>q,q2;
void bfs(){
	q=q2;
	q.push(mp(lx,ly));
	while(!q.empty()){
		pii p=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int x=p.f1+dx[i];
			int y=p.s2+dy[i];
			if(x>=0&&x<n&&y>=0&&y<m&&a[x][y]=='.'){
				int sum=0;
				for(int j=0;j<4;j++){
					int _x=x+dx[j];
					int _y=y+dy[j];
					if(_x>=0&&_x<n&&_y>=0&&_y<m&&a[_x][_y]=='.')sum++;
				}
				if(sum<2)a[x][y]='+',q.push(mp(x,y));
			}
		}
	}
} 
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)cin>>a[i];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(a[i][j]=='L')lx=i,ly=j;
		bfs();
		for(int i=0;i<n;i++)cout<<a[i],putchar('\n');
		for(int i=0;i<n;i++)a[i]="";
	}
	return 0;
}
```
### 注意事项
注意，此题输出要用较快的方式。

---

## 作者：enyyyyyyy (赞：0)

- 
  	思路：简单的宽搜。

- 
	实现：从队列中取出一个元素，维护 $4$ 个方向：$(0,1),(-1,0),(1,0),(0,-1)$，表示每一个点接下来的位置选择，再去判断是否越界并且满足走法小于等于 $1$，如果成立，可以将点设为 `+`，并入队列。直到队列为空才停止。
    
- 
	代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll x = 0, f = 0;
	char ch = 0;
	while (!isdigit(ch)) {
		f |= (ch == '-');
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f? -x: x;
}
inline void print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll _,n,m,x,y;
ll dx[]={-1,0,0,1};
ll dy[]={0,-1,1,0};
string a[1000005];
struct node {
	ll x,y;
};
ll check(ll x,ll y) {
	ll cnt=0;
	for(ll i=0; i<4; i++) {
		ll nx=x+dx[i],ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]=='.') cnt++;
	}
	return cnt<=1&&x>=1&&x<=n&&y>=1&&y<=m&&a[x][y]=='.';
}
void bfs(ll x,ll y) {
	queue<node>q;
	q.push((node) {x,y});
	while(!q.empty()) {
		node now=q.front();
		q.pop();
		for(ll i=0; i<4; i++) {
			ll nx=now.x+dx[i],ny=now.y+dy[i];
			if(check(nx,ny))
				a[nx][ny]='+',q.push((node) {nx,ny});
		}
	}
}
int main() {
	_=read();
	while(_--) {
		n=read(),m=read();
		for(ll i=1; i<=n; i++) {
			cin>>a[i];
			a[i]=' '+a[i];
			for(ll j=1; j<=m; j++)
				if(a[i][j]=='L') x=i,y=j;
		}
		bfs(x,y);
		for(ll i=1; i<=n; i++) cout<<a[i],printf("\n");
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$

---
### 解题思路

一个位置认为是不可逃脱当且仅当这个位置不是空的（也就是非“$\text{.}$”）。

对与任意一个位置，如果有多个方向可以逃脱，那么无论如何选取方向都不可能使得其到达不可逃脱位置，那么这个位置就是可以逃脱的。

---
考虑直接模拟这个过程，从实验室开始 $\text{BFS}$。注意拓展完一个位置之后并不能直接确定这个位置是可逃脱的，有可能有其他位置尚未拓展到，才导致的当前位置认为是不可逃脱。当且仅当一个位置从认为是可以逃脱变成不可逃脱的时候，进行四个方向的拓展。

实验室有且只有一个，而且每一个位置最多被四个方向上的四个点各拓展一次，如果这样还不能使得这个点变成不可逃脱点，那么一定不可能有下一次拓展了。所以总的复杂度为 $O(nm)$，$nm\le 10^6$ 可以接受。

---
注意数据的存储方式，以及对于边界的处理。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int T,n,m,sx,sy,nx,ny,dx[5]={0,0,1,-1},dy[5]={1,-1,0,0},cnt;
vector <int> s[1000005];
queue <int> qx,qy;
char c;
char get(){
	char c=getchar();
	while(c==' '||c=='\n'||c=='\r')c=getchar();
	return c;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n+1;i++)s[i].push_back(0);
		for(int i=1;i<=m;i++){
			s[0].push_back(0);
			s[n+1].push_back(0);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){	
				c=get();
				if(c=='.')s[i].push_back(1);
				if(c=='L'){
					s[i].push_back(3);
					for(int k=0;k<=3;k++){				
						qx.push(i+dx[k]);
						qy.push(j+dy[k]);
					}
				}
				if(c=='#')s[i].push_back(0);
			}
		}
		for(int i=0;i<=n+1;i++)s[i].push_back(0);
		
		while(!qx.empty()){
			nx=qx.front();ny=qy.front();
			qx.pop();qy.pop();
			if(nx>n||ny<1||nx<1||ny>m)continue;
			if(s[nx][ny]!=1)continue;
			cnt=0;
			for(int i=0;i<=3;i++)cnt+=(s[nx+dx[i]][ny+dy[i]]==1);
			if(cnt==1){
				s[nx][ny]=2;
				for(int i=0;i<=3;i++){
					qx.push(nx+dx[i]);
					qy.push(ny+dy[i]);
				}
			}
			if(cnt==0){
				int flag=0;
				for(int i=0;i<=3;i++)flag+=(s[nx+dx[i]][ny+dy[i]]==2||s[nx+dx[i]][ny+dy[i]]==3);
				if(flag!=0)s[nx][ny]=2;
			}
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i][j]==0)printf("#");
				if(s[i][j]==1)printf(".");
				if(s[i][j]==2)printf("+");
				if(s[i][j]==3)printf("L");
			}
			printf("\n");
		}
		//init
		for(int i=0;i<=n+1;i++)
		s[i].clear();
	}
	return 0;
}
/*
1
1 9
....L..#.
*/
```


---

