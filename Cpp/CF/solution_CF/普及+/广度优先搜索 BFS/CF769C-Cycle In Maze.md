# Cycle In Maze

## 题目描述

The Robot is in a rectangular maze of size $ n×m $ . Each cell of the maze is either empty or occupied by an obstacle. The Robot can move between neighboring cells on the side left (the symbol "L"), right (the symbol "R"), up (the symbol "U") or down (the symbol "D"). The Robot can move to the cell only if it is empty. Initially, the Robot is in the empty cell.

Your task is to find lexicographically minimal Robot's cycle with length exactly $ k $ , which begins and ends in the cell where the Robot was initially. It is allowed to the Robot to visit any cell many times (including starting).

Consider that Robot's way is given as a line which consists of symbols "L", "R", "U" and "D". For example, if firstly the Robot goes down, then left, then right and up, it means that his way is written as "DLRU".

In this task you don't need to minimize the length of the way. Find the minimum lexicographical (in alphabet order as in the dictionary) line which satisfies requirements above.

## 说明/提示

In the first sample two cyclic ways for the Robot with the length $ 2 $ exist — "UD" and "RL". The second cycle is lexicographically less.

In the second sample the Robot should move in the following way: down, left, down, down, left, left, left, right, right, right, up, up, right, up.

In the third sample the Robot can't move to the neighboring cells, because they are occupied by obstacles.

## 样例 #1

### 输入

```
2 3 2
.**
X..
```

### 输出

```
RL
```

## 样例 #2

### 输入

```
5 6 14
..***.
*...X.
..*...
..*.**
....*.
```

### 输出

```
DLDDLLLRRRUURU
```

## 样例 #3

### 输入

```
3 3 4
***
*X*
***
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：qwqszxc45rtnhy678ikj (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF769C)
这题我们乍一看呢发现是个搜索，但一看 k 的范围大小，就可以知道，要用一点巧办法剪枝：
因为上下左右字典序排下来是 DLRU ，可以发现正好反过来（前半部分是 DL，后半部分 RU，也就说原路返回，字典序最小）
于是可以列下如下思路：

- k 是奇数的话无解
- 先用 dfs 求出前半部分，然后按照 D-U L-R ，得出后半部分 

但是，这样 test 49 就 wa 了，为什么，给出一个例子（其中 b 是空地）：
```
7 4 18
..X.
....
....
....
.**.
....
*b..
```
发现 DDDLLDDLD 后走到 b 就该原路返回了，但剩下走 RRUUULUUU 的话更优，算法不对。

所以我们换一种思想，先用 bfs 求出到每个点的距离，然后 dfs ，如果到 X 的距离大于了剩下可走的步数，剪枝，就解决了。

接着，上代码！！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, k, xx[] = {1, 0, 0, -1}, yy[] = {0, -1, 1, 0}, flag, ans[1000010], t[1010][1010];
char c[1010][1010], p[] = {'D', 'L', 'R', 'U'};
queue<long long> hx, hy;
void bfs(long long ux, long long uy) { //bfs
	hx.push(ux);
	hy.push(uy);
	t[ux][uy] = 0;
	while(!hx.empty()) {
		for(int i = 0; i < 4; i++) {
			long long tx = hx.front() + xx[i], ty = hy.front() + yy[i];//下一步走的地方
			if((tx % (n + 1)) && (ty % (m + 1)) && c[tx][ty] != '*' && t[tx][ty] > t[hx.front()][hy.front()] + 1) {//判断是否能走和有没有遍历过
				t[tx][ty] = t[hx.front()][hy.front()] + 1;
				hx.push(tx);
				hy.push(ty);
			}
		}
		hx.pop();
		hy.pop();
	}
}
void dfs(long long tx, long long ty, long long step) {//dfs
	if(step > k) {
		for(int i = 1; i <= k; i++) cout << p[ans[i]];//输出
		flag = 1;//标记已经得出答案了
		return;
	}
	for(int i = 0; i < 4; i++)
		if(((tx + xx[i]) % (n + 1)) && ((ty + yy[i]) % (m + 1)) && c[tx + xx[i]][ty + yy[i]] != '*') {//判断是否能走和有没有遍历过
			if(t[tx + xx[i]][ty + yy[i]] > k - step + 1) continue;//如果到X的距离大于了剩下可走的步数，剪枝
			ans[step] = i;
			dfs(tx + xx[i], ty + yy[i], step + 1);
			if(flag) return;//如果已经得出答案了就return
		}
}
int main() {
	memset(t, 0x7f, sizeof(t));//初始化
	cin >> n >> m >> k;
	if(k % 2) {//k是奇数就输出IMPOSSIBLE
		cout << "IMPOSSIBLE";
		return 0; 
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> c[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(c[i][j] == 'X') {//如果这个点是X
				bfs(i, j);
				dfs(i, j, 1);
			}
	if(!flag) cout << "IMPOSSIBLE";//如果没有遍历到，输出IMPOSSIBLE
	return 0;
}
```


---

## 作者：Gapple (赞：0)

我们注意到 $k \le 10^6$ 且有 15 秒时限，可以考虑 DFS 剪枝。

那么如何剪枝？

当剩余步数不足以回到起点时就剪枝，剩余步数可以 BFS 预处理。同时，搜索时按字典序升序的顺序搜索，即按 `DLRU` 的顺序搜索。

[AC 记录](https://vjudge.net/solution/54675528/iUWZU5ZI0u6GKepH5TdF)（264 ms）。

---

## 作者：ShanQing (赞：0)

upd：修改了代码里一处明显但没有报错的 RE 。

虽然整整 15s 的时限给足了 dfs 剪枝，但还是来个相对比较正经的解法。

两遍 bfs ，第一遍求出起点到所有点的最短路。  

然后开始算法。从起点开始，每一步根据 DLRU 的顺序依次判断，能走即走，最小化字典序。  

直到有一次不得不回去，即到起点的最短距离正好等于剩余步数，那就再 bfs 一遍，然后沿着所有最短路中当前点到起点的最小的字典序回去即可。具体的，想做到字典序最小化， bfs 里面的循环还是贪心式地根据 DLRU 的顺序遍历即可。

总结一下，第一次 bfs 求的是距离，以便能及时回溯，接着贪心地游走，最后需要回溯时第二遍 bfs 求的则是所有回溯方案中的最优方案，也就是做到字典序最小。

这个解法跑得贼快，实测用时 124ms ，貌似能排进目前的前三。

## code

非常的丑。

```cpp
//writer:Oier_szc

#include <bits/stdc++.h>
//#include <windows.h>
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=1e3+5,INF=2e9,mod=1e9+7;
int n,m,k;
int dr[4][2]={{1,0},{0,-1},{0,1},{-1,0}};
char a[N][N],op[4]={'D','L','R','U'};
char ans[N*N];
int vis[N][N],fr[N][N],dis[N][N];

bool in(int x,int y) {
	return x>=1&&x<=n&&y>=1&&y<=m;
}

void bfs(int x,int y) {
	queue<pii> q;
	q.push({x,y});
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			vis[i][j]=0;
		}
	}
	vis[x][y]=1,dis[x][y]=0;
	while(!q.empty()) {
		pii now=q.front();q.pop();
		for(int i=0;i<4;++i) {
			int tx=now.fi+dr[i][0],ty=now.se+dr[i][1];
			if(in(tx,ty)&&a[tx][ty]!='*'&&!vis[tx][ty]) {
				vis[tx][ty]=1,fr[tx][ty]=i;
				dis[tx][ty]=dis[now.fi][now.se]+1;
				q.push({tx,ty});
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int sx=-1,sy=-1,x,y;
	for(int i=1;i<=n;++i) {
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;++j) {
			if(a[i][j]=='X') {
				sx=i,sy=j;
				break;
			}
		}
	}
	if(k&1) {
		puts("IMPOSSIBLE");
		return 0;
	}
	bfs(sx,sy);
	x=sx,y=sy;
	for(int t=1;t<=k;++t) {
		if(k-t+1==dis[x][y]) {
			bfs(x,y),x=sx,y=sy;
			while(k>=t) {
				int way=fr[x][y];
				ans[k]=op[way];
				x+=dr[3-way][0],y+=dr[3-way][1];
				--k;
			}
			break;
		}
		int ok=0;
		for(int i=0;i<4;++i) {
			int tx=x+dr[i][0],ty=y+dr[i][1];
			if(in(tx,ty)&&a[tx][ty]!='*') {
				ans[t]=op[i];
				x=tx,y=ty,ok=1;break;
			}
		}
		if(!ok) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts(ans+1);
	return 0;
}
```

---

