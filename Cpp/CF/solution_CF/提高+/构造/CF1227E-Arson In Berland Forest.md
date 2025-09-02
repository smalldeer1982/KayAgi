# Arson In Berland Forest

## 题目描述

伯兰德森林可以被表示为一个无限的网格平面。每个格子里都有一棵树。也就是说，在最近的事件发生之前，每个格子都有树。

一场毁灭性的火灾席卷了森林，许多树木因此受损。具体来说，你有一张 $n \times m$ 的矩形地图，表示受损的森林区域。被烧毁的树用 "X" 标记，未受损的树用 "." 标记。你可以确定所有被烧毁的树都在地图上显示。地图外的所有树都是未受损的。

消防员很快扑灭了大火，现在他们正在调查起火原因。主要的猜测是有人纵火：在某一时刻（我们记作 $0$ 时刻），有一些树被点燃。在第 $0$ 分钟开始时，只有最初被点燃的树在燃烧。每过一分钟，在每一棵燃烧的树的 $8$ 个相邻格子的树都会被点燃。在第 $T$ 分钟开始时，大火被扑灭。

消防员想尽快找到纵火者。问题是，他们既不知道 $T$ 的值（火灾持续了多久），也不知道最初被点燃的树的坐标。你的任务是找出最大的 $T$（以便知道纵火者可能逃得多远），以及一种可能的最初被点燃的树的集合。

注意，你需要最大化 $T$ 的值，但最初被点燃的树的集合可以是任意的。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 6
XXXXXX
XXXXXX
XXXXXX
```

### 输出

```
1
......
.X.XX.
......
```

## 样例 #2

### 输入

```
10 10
.XXXXXX...
.XXXXXX...
.XXXXXX...
.XXXXXX...
.XXXXXXXX.
...XXXXXX.
...XXXXXX.
...XXXXXX.
...XXXXXX.
..........
```

### 输出

```
2
..........
..........
...XX.....
..........
..........
..........
.....XX...
..........
..........
..........
```

## 样例 #3

### 输入

```
4 5
X....
..XXX
..XXX
..XXX
```

### 输出

```
0
X....
..XXX
..XXX
..XXX
```

# 题解

## 作者：wlj_55 (赞：0)

## 题目分析
容易发现如果一个 $T$ 能够满足题意的话，那么任意小于 $T$ 的数均可满足题意，所以我们可以想到二分答案。

那么二分后如何验证呢？

一棵树在点燃 $T$ 分钟后所扩展出的形状一定是一个边长为 $2T+1$ 的正方形，由于题目没有限制初始被点燃的数的多少，所以我们可以考虑将所有引燃后能够在 $T$ 分钟内不超过边界的树点燃，这样一定能够覆盖最多的面积，然后判断扩展到的格子的总数是否为原来被引燃的树木的总数。

注意此题暴力查找能否点燃会超时，记录一个前缀和，然后判断扩展到的格子里 "X" 的个数是否为该正方形面积即可。

时间复杂度 $\mathcal{O}(nm\log\max(n, m))$

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n, m, cnt;
vector<int> f[1000005], a[1000005];
char ch[1000005];
int calc(int x1, int y1, int x2, int y2) {
	if(x1 <= 0 || y1 <= 0 || x2 > n || y2 > m)  return -1;
	--x1, --y1;
	return f[x1][y1] + f[x2][y2] - f[x2][y1] - f[x1][y2];
}
int dx[9] = {0, -1, 1, 0, 0, 1, -1, 1, -1}, dy[9] = {0, 0, 0, -1, 1, 1, -1, -1, 1};
bool chk(int x) {       //判断时间为x时是否可行 
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)  a[i][j] = 0;
	queue<pair<pair<int, int>, int> > q;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(calc(i - x, j - x, i + x, j + x) == (2 * x + 1) * (2 * x + 1)) {
				a[i][j] = 1;
				q.push(make_pair(make_pair(i, j), 0));
			}
		}
	}
	int Cnt = 0;
	while(!q.empty()) {
		pair<int, int> u = q.front().first;
		int d = q.front().second; q.pop();
		++Cnt;
		for(int i = 1; i <= 8; i++) {
			int xx = u.first + dx[i], yy = u.second + dy[i];
			if(d == x)  break;
			if(xx >= 1 && yy >= 1 && xx <= n && yy <= m && !a[xx][yy]) {
				a[xx][yy] = 1;
				q.push(make_pair(make_pair(xx, yy), d + 1));
			}
		}
	}
	return Cnt == cnt;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)  f[i].push_back(0), a[i].push_back(0);
	for(int i = 1; i <= n; i++) {
		scanf("%s", ch + 1);
		for(int j = 1; j <= m; j++) 
		    cnt += (f[i][j] = ((ch[j] == 'X') ? 1 : 0));
	}
	for(int i = 1; i <= n; i++)
	    for(int j = 1; j <= m; j++)
	        f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
	int l = 1, r = max(n, m), ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(chk(mid))  ans = mid, l = mid + 1;
		else  r = mid - 1;
	}
	cout << ans << endl;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(calc(i - ans, j - ans, i + ans, j + ans) == (2 * ans + 1) * (2 * ans + 1))
			    putchar('X');
			else  putchar('.');
		}
		puts("");
	}
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
在一个无限大的矩阵中，每个位置是一棵树。在一个 $n \times m$ 的子矩阵中，发生了一场火灾，一些树被摧毁了。被摧毁的树用字符 `X` 表示，未被摧毁的树用字符 `.` 表示。子矩阵外的树都没有被摧毁.

- 在 $0$ 时刻，有些树是自发着火的.
- 接下来的每一分钟内，每一棵着火（也即，被摧毁）的树，会使得它周围的 $8$ 个相邻的树着火.
- 在第 $T$ 分钟初，火灾停止.

现在给定最后被摧毁的树，求最大可能的 $T$，并求出任意一种满足的、自发着火的树的集合.
## $\text{Solution}$
bfs 预处理出每个燃烧点到外部的最短距离 $dis$.  
二分时间 $t$，那么 $dis\ge t$ 的点是可以初始燃烧的.  
从可以初始燃烧的所有点 bfs $t$ 次，若 bfs 的地图和原图一致，则合法.  
注意边界的树是完好的.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=3e6+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
#define id(a,b) ((a)*(m+2)+(b))
bool vis[N];
int mp[N],dis[N];
int dx[9]={0,-1,-1,-1,0,1,1,1,0},dy[9]={0,-1,0,1,1,1,0,-1,-1};
#define pr pair<int,int>
#define mkp make_pair
pr q[N];
int st,ed;
void bfs(){
  st=1;ed=0;
  for(int i=0;i<=n+1;i++){
    for(int j=0;j<=m+1;j++){
      if(!mp[id(i,j)]){
	vis[id(i,j)]=1;q[++ed]=mkp(i,j);
      }
    }
  }
  while(st<=ed){
    int x=q[st].first,y=q[st].second;++st;
    //printf("(%d %d)\n",x,y);
    for(int i=1;i<=8;i++){
      int xx=x+dx[i],yy=y+dy[i];
      if(xx<1||xx>n||yy<1||yy>m) continue;
      if(vis[id(xx,yy)]) continue;
      //printf("  ->(%d %d)\n",xx,yy);
      vis[id(xx,yy)]=1;dis[id(xx,yy)]=dis[id(x,y)]+1;
      q[++ed]=mkp(xx,yy);
    }
  }
  return;
}
int a[N];
bool check(int k){
  st=1,ed=0;
  memset(vis,0,sizeof(vis));
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) if(dis[id(i,j)]>=k) q[++ed]=mkp(i,j),vis[id(i,j)]=1;
  }
  //for(int i=1;i<=n;i++){
  //for(int j=1;j<=m;j++) printf("%d",vis[id(i,j)]);
  //putchar('\n');
  //}
  for(int ned=ed,i=1;i<k;i++,ed=ned){
    while(st<=ed){
      int x=q[st].first,y=q[st].second;++st;
      for(int i=1;i<=8;i++){
	int xx=x+dx[i],yy=y+dy[i];
	if(xx<1||xx>n||yy<1||yy>m) return false;
	if(vis[id(xx,yy)]) continue;
	vis[id(xx,yy)]=1;
	q[++ned]=mkp(xx,yy);
      }
    }
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) if(vis[id(i,j)]^mp[id(i,j)]) return false;
  }
  return true;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  char c;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      scanf(" %c",&c);
      mp[id(i,j)]=c=='X';
    }
  }
  bfs();
  //printf("%d\n",check(2));
  //return 0;
  int st=1,ed=max(n,m);
  while(st<ed){
    int mid=(st+ed+1)>>1;
    if(check(mid)) st=mid;
    else ed=mid-1;
  }  
  printf("%d\n",st-1);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(dis[id(i,j)]>=st) putchar('X');
      else putchar('.');
    }
    putchar('\n');
  }
  return 0;
}
/*
*/

```


---

