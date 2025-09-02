# [ABC351D] Grid and Magnet

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_d

$ H $ 行 $ W $ 列のマス目があり、いくつか（$ 0 $ 個のこともある）のマスには磁石が置かれています。  
マス目の状態は $ H $ 個の 長さ $ W $ の文字列 $ S_1,S_2,\ldots,S_H $ で表され、 $ S_i $ の $ j $ 文字目が `#` のとき上から $ i $ 行目かつ左から $ j $ 列目のマスには磁石が置かれていることを、 `.` のとき何も置かれていないことを表しています。

高橋君は鉄の鎧を着ており、あるマスにいるとき次のように移動することができます。

- 現在いるマスの上下左右に隣り合うマスのいずれかに磁石が置かれているとき、どこへも移動することができない。
- そうでないとき、上下左右に隣り合うマスのいずれかを選んでそのマスに移動することができる。  
  ただし、マス目の外に移動することはできない。

磁石が置かれていない各マスについて、そのマスの自由度を、「最初高橋くんがそのマスにいるとき、そこから移動を繰り返して到達できるマスの個数」として定義します。 マス目のうち磁石が置かれていないマスの中における、マスの自由度の最大値を求めてください。

ただし、自由度の定義において、「移動を繰り返して到達できるマス」とは、最初にいるマスからそのマスまで移動を繰り返して到達する方法（$ 1 $ 回も移動しないものも含む）が $ 1 $ つ以上存在するようなマスのことであり、 最初のマスから始めてすべてのそのようなマスを巡るような移動方法が存在する必要はありません。特に（磁石の置かれていない）各マス自身は、そのマスから「移動を繰り返して到達できるマス」につねに含まれることに注意してください。

## 说明/提示

### 制約

- $ 1\leq\ H,W\leq\ 1000 $
- $ H,W $ は整数
- $ S_i $ は `.` と `#` のみからなる長さ $ W $ の文字列
- 磁石の置かれていないマスが少なくとも $ 1 $ つ存在する。

### Sample Explanation 1

上から $ i $ 行目かつ左から $ j $ 列目のマスを $ (i,j) $ で表します。 高橋君が最初に $ (2,3) $ にいるとき、高橋君の移動の例としては次のようなものなどが考えられます。 - $ (2,3)\to\ (2,4)\to\ (1,4)\to\ (1,5)\to\ (2,5) $ - $ (2,3)\to\ (2,4)\to\ (3,4) $ - $ (2,3)\to\ (2,2) $ - $ (2,3)\to\ (1,3) $ - $ (2,3)\to\ (3,3) $ よって、途中で到達しているマスも含めて高橋君は $ (2,3) $ から少なくとも $ 9 $ 個のマスに到達することができます。 一方、これら以外のマスには到達することができないため、$ (2,3) $ の自由度は $ 9 $ となります。 これは磁石が置かれていない各マスの自由度のうち最大であるため、$ 9 $ を出力します。

### Sample Explanation 2

磁石が置かれていないどのマスについても、上下左右に隣り合うマスのいずれかに磁石が置かれています。 よって、磁石が置かれていないどのマスからも移動することはできず、マスの自由度は $ 1 $ となります。 そのため、$ 1 $ を出力します。

## 样例 #1

### 输入

```
3 5
.#...
.....
.#..#```

### 输出

```
9```

## 样例 #2

### 输入

```
3 3
..#
#..
..#```

### 输出

```
1```

# 题解

## 作者：2huk (赞：5)

- 有一张 $n \times m$ 的网格图，某些位置上可能会有磁铁。如果与你当前位置四联通地方有磁铁，你就不能移动。定义一个没有磁铁的位置的自由度为从这里出发，存在至少一条路径能到达的点数。求网格图上的最大自由度。
  - $n, m \le 10^3$。

  显然是搜索。我们将网格上的点分为三类：

  1. 有磁铁的点；
  2. 靠近磁铁的点（即题目中到达后不能移动的点）；
  3. 不靠近磁铁的点。

  对于「贰」点，显然它们的自由度为 $1$。这样就不需要计算了。

  显然「叁」点构成的连通块中，每个点的自由度是相同的。所以我们可以只 bfs 搜索这些连通块中一个点的自由度。特别的，当搜索到某个「贰」点时，我们需要把它入队并加入答案，但是不需要从它开始往外扩展。这是题意要求的。

  这样的复杂度是线性的。

  ```cpp
  #include <bits/stdc++.h>

  using namespace std;

  const int N = 2010;

  int n, m, res;
  char g[N][N];
  const int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
  bool st[N][N];

  bool chk(int x, int y) {
      for (int i = 0; i < 4; ++ i ) {
          int a = x + dx[i], b = y + dy[i];
          if (a >= 1 && a <= n && b >= 1 && b <= m) {
              if (g[a][b] == '#') return true;
          }
      }
      return false;
  }

  int bfs(int x, int y) {
      if (chk(x, y)) return 1;
      if (st[x][y]) return -114514;

      queue<pair<int, int> > q;
      q.emplace(x, y);
      int ans = 0;
      st[x][y] = true;

      map<pair<int, int>, bool> S;

      while (q.size()) {
          int x = q.front().first, y = q.front().second;
          q.pop();
          ++ ans;
          if (!chk(x, y)) {
              for (int i = 0; i < 4; ++ i ) {
                  int a = x + dx[i], b = y + dy[i];
                  if (a >= 1 && a <= n && b >= 1 && b <= m && g[a][b] == '.') {
                      if (chk(a, b)) {
                          if (!S[{a, b}]) {
                              q.emplace(a, b);
                              S[{a, b}] = true;
                          }
                      }
                      else if (!st[a][b]) {
                          q.emplace(a, b);
                          st[a][b] = true;	
                      }
                  }
              }
          }
      }

      return ans;
  }

  int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; ++ i ) scanf("%s", g[i] + 1);
      for (int i = 1; i <= n; ++ i )
          for (int j = 1; j <= m; ++ j )
              if (g[i][j] != '#')
                  res = max(res, bfs(i, j));
      printf("%d\n", res);
      return 0;
  }
  ```

---

## 作者：HasNoName (赞：2)

### 思路

考虑广搜。

从每个不在磁铁上且不再磁铁旁边的位置广搜。

如果一个点可以被走到，那么这个点一定也可以走到走到它的那个点，不用考虑。

同理，两个点互相不能到达，它们之间只有位于磁铁旁边的位置可能搜到，每次搜完之后清空那些位置的标记。应为磁铁旁边的点最多遍历 $4$ 次，其余点最多遍历 $1$ 次，所以复杂度为 $O(HW)$。
### 代码

```cpp
#include<bits/stdc++.h>
#define to(x,y) {vis[x][y]=1;c++;q[++r]={x,y};}
using namespace std;
const int N=1005;
int a[N][N],vis[N][N],n,m;
struct T
{
    int x,y;
}q[N*N],p[N*N];
bool can(int x,int y)//一个点是否能移动（不再磁铁旁边）
{
    if(a[x-1][y]||a[x][y-1]||a[x+1][y]||a[x][y+1])
        return 0;
    return 1;
}
bool ok(int x,int y)//能到
{
    if(x<1||x>n||y<1||y>m||vis[x][y]||a[x][y])return 0;
    return 1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    char ch;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>ch;
            if(ch=='.')a[i][j]=0;
            else a[i][j]=1;
        }
    }
    int ans=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!can(i,j)||a[i][j]||vis[i][j])continue;
            int l=1,r=0,c=1,top=0;//对当前点进行广搜，c为当前点能到的点的数量
            q[++r]={i,j};
            vis[i][j]=1;
            while(l<=r)
            {
                int x=q[l].x,y=q[l].y;
                l++;
                if(!can(x,y))//将在磁铁旁的点入队
                {
                    p[++top]={x,y};
                    continue;
                }
                if(ok(x-1,y))to(x-1,y)
                if(ok(x+1,y))to(x+1,y)
                if(ok(x,y-1))to(x,y-1)
                if(ok(x,y+1))to(x,y+1)
            }
            for(int i=1;i<=top;i++)
                vis[p[i].x][p[i].y]=0;
            ans=max(ans,c);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ThisIsLu (赞：2)

初看题目，不难想到大力 dfs。

但是这样子 dfs 是极为低效的，考虑优化。

可以发现，如果两个方格可以互达，即两个方格旁边都没磁铁且相邻，那么它们能到达的方格是一样的。

于是我们想到了改进后的 dfs：每次 dfs 后保持原标记，将 dfs 时搜到的旁边有磁铁的方格的标记撤掉。

这样一来就不会重复搜索了，时间复杂度由于一个相邻磁铁的格子最多被搜到三次，仍然是线性的。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000+5;
int n,m;
char ch[N][N];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool vis[N][N];
int res;
int cnt,qx[N*N],qy[N*N];
void dfs(int x,int y){
    if(vis[x][y]) return;
    vis[x][y]=true;
    res++;
    bool flag=false;
    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(1<=nx&&nx<=n&&1<=ny&&ny<=m){
            if(ch[nx][ny]=='#'){
                flag=true;
                break;
            }
        }
    }
    if(!flag){
        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(1<=nx&&nx<=n&&1<=ny&&ny<=m){
                dfs(nx,ny);
            }
        }
    }
    else{
        cnt++;
        qx[cnt]=x;
        qy[cnt]=y;
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>ch[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(ch[i][j]=='#') continue;
            res=0;
            dfs(i,j);
            for(int k=1;k<=cnt;k++) vis[qx[k]][qy[k]]=false;
            cnt=0;
            ans=max(ans,res);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
给定一张 $H\times W$ 的由 `#` 和 `.` 组成的图。对于点 $(x,y)$，如果上下左右没有字符 `#` 可以向上下左右移动一点，否则不可移动。

问以某点为起点，最多可以抵达多少点。
# 思路
首先不难想到深搜暴力，但是 $H,W\le10^3$ 在单纯暴力深搜下的时间复杂度可以达到 $O(H^2W^2)$，肯定是不行的。

不难发现，对于两个相邻点，如果它们可以互相到达，那么以这两点为起点的情况下答案是相同的。于是，我们给每个点一个 $vist$ 标记，记录它是否被遍历过，如果这个点有 $vist$ 标记，那么它就没有必要遍历。

同时，对于不可移动的点，直接对贡献加一即可。

按照上述思路构了一版代码，发现样例都过不了。最后发现问题在于同一个不可移动点可能会被计数多次，然后用 set 存储遍历过的点，每次答案为 set 内元素数量。

上述思路整合，不难发现时间复杂度是 $O(HW)$ 的。
# 代码
```cpp
#include<bits/stdc++.h>

#define F first
#define S second

using namespace std;

const int N=1e3+5;
const int mx[4]={1,-1,0,0};
const int my[4]={0,0,1,-1};

int n;
int h,w;
int ans;

char mp[N][N];

bool mo[N][N];
bool vs[N][N];

set<pair<int,int>> v;

inline void dfs(int x,int y){
    
    if(x<1||y<1||x>h||y>w||mp[x][y]=='#')
        return;

    if(mo[x][y]){

        v.insert({x,y});
        return;
    }

    if(vs[x][y])
        return;

    vs[x][y]=1;

    v.insert({x,y});

    for(int i=0;i<4;i++)
        dfs(x+mx[i],y+my[i]);

}

main(){

    scanf("%d%d",&h,&w);

    for(int i=1;i<=h;i++)
        scanf("%s",mp[i]+1);

    for(int i=1;i<=h;i++){

        for(int j=1;j<=w;j++){

            if(mp[i][j]!='#'){

                if(mp[i+1][j]=='#'||mp[i-1][j]=='#'||mp[i][j+1]=='#'||mp[i][j-1]=='#')
                    mo[i][j]=1;
            }
        }
    }
    for(int i=1;i<=h;i++)
    for(int j=1;j<=w;j++)
        if(mp[i][j]!='#'&&!vs[i][j]){

            v.clear();
            
            dfs(i,j);

            ans=max(ans,(int)v.size());

        }

    printf("%d",ans);

    return 0;
}
```

---

## 作者：ykzzldz (赞：1)

这道题目我的做法是建图+染色（好像和大家思路有点不太一样？），下面正文开始：

由于走到了一个磁铁的旁边就不能够再次移动，所以我们在两个周围没有磁铁的空格之间连一条双向边，表示可以互通。在一个空格与一个磁铁旁的格子间连一条单向边，表示只能从一个格子走向另外一个格子（有去无回）。

最后只要对一个图进行染色即可，这里就不多赘述了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[1100000];
int m,n,ans;
char a[1100][1100];
vector<int>e[1100000];
int id(int x,int y){
	return y+(x-1)*m;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='#')vis[id(i,j)]=n*m+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='#')continue;
			if(i>1&&a[i-1][j]=='#')a[i][j]='@';
			if(j>1&&a[i][j-1]=='#')a[i][j]='@';
			if(i<n&&a[i+1][j]=='#')a[i][j]='@';
			if(j<m&&a[i][j+1]=='#')a[i][j]='@';
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a1=id(i,j);
			if(a[i][j]=='#')continue;
			if(a[i][j]=='.'){
				if(j-1>0&&a[i][j-1]!='#'){
					int b1=id(i,j-1);
					if(a[i][j-1]=='.'){
						e[a1].push_back(b1);
						e[b1].push_back(a1);
					}
					else{
						e[a1].push_back(b1);
					}
				}
				if(i-1>0&&a[i-1][j]!='#'){
					int b1=id(i-1,j);
					if(a[i-1][j]=='.'){
						e[a1].push_back(b1);
						e[b1].push_back(a1);
					}
					else{
						e[a1].push_back(b1);
					}
				}
			}
			if(a[i][j]=='@'){
				if(j-1>0&&a[i][j-1]!='#'){
					int b1=id(i,j-1);
					if(a[i][j-1]=='.'){
						e[b1].push_back(a1);
					}
				}
				if(i-1>0&&a[i-1][j]!='#'){
					int b1=id(i-1,j);
					if(a[i-1][j]=='.'){
						e[b1].push_back(a1);
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int p=id(i,j);
			if(vis[p]==0){
				queue<int>q;
				q.push(p);
				vis[p]=p;
				int jsq=0;
				while(!q.empty()){
					int u=q.front();
					q.pop();
					jsq++;
					for(int k=0;k<e[u].size();k++){
						int v=e[u][k];
						if(vis[v]!=p){
							vis[v]=p;
							q.push(v);
						}
					}
				}
				ans=max(ans,jsq);
			}
		}
	}
	cout<<ans;
    return 0; 
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc351_d

## 解题思路

典型 dfs，flood fill 求一遍连通块即可。

唯一需要特殊处理的就是 `#` 周围四个点。由于走到这里就不能再走了，但是或许可以从不同连通块走到同一个点，这就导致如果我们再走完之后直接在 vis 数组里标记掉就可能让别的连通块少算，如果我们不标记就可能在一个联通块内多次重复记录。

我的解决方法是把这些点放进队列里，搜完一个连通块再把它们清空掉。

code：
```cpp
// Problem: D - Grid and Magnet
// Contest: AtCoder - AtCoder Beginner Contest 351
// URL: https://atcoder.jp/contests/abc351/tasks/abc351_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-04-27 20:13:41

#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
queue<pair<int,int> > q;
int n,m,cnt,ans;
int siz[1000006];
bool vis[1003][1003];
char mp[1003][1003];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
void dfs(int x,int y){
	siz[cnt]++;
	vis[x][y]=1;
	if(mp[x+1][y]=='#'||mp[x-1][y]=='#'||mp[x][y+1]=='#'||mp[x][y-1]=='#'){
		q.push({x,y});
		return;
	}
	for(int i=0;i<4;i++){
		int px=x+dir[i][0];
		int py=y+dir[i][1];
		if(!vis[px][py]&&mp[px][py]=='.')
			dfs(px,py);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>mp[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j]&&mp[i][j]!='#'){
				cnt++,dfs(i,j),ans=max(ans,siz[cnt]);
				while(!q.empty())
					vis[q.front().first][q.front().second]=0,q.pop();
			}
	cout<<ans;
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

题目大意：

- 有一个迷宫，其中有磁铁 `#` 和空格 `.` 两种格子。如果某一个格子的与之相邻（四联通）的格子有磁铁，那么高桥不能移动，否则可以。

- 你可以选择一个点，使得高桥从这个点出发能够到达的点数最多，输出这个最大值。

思路：

- 首先，我们把与之相邻（四联通）的格子有磁铁的格子称作特殊格子，那么每个特殊格子显然可以当作两个或多个联通块的交点来看待。

- 所以我们想到使用 bfs 解决。对于每个未被访问的点，如果它不是磁铁且不是特殊格，一定是一个新的联通块内的。对于每个格子，如果这个格子本身就是特殊格子那么就不能扩展。对于其他情况，如果能访问到的格子不是特殊格子，那么很显然只能被访问一次，直接标记并入队。如果能访问到的格子是特殊格子，不管有没有被标记过，都可以占为己有并入队（前面说过特殊格子是两个或多个联通块的交点）。对于每个已经访问的格子，把这个联通块的大小加上 $1$ 即可，最后在所有联通块大小中取最大值。

代码如下。

```cpp
#include <iostream>
#include <queue>
using namespace std;

int n, m, vis[1005][1005], pd[1005][1005], cnt;

char a[1005][1005];
queue <int> qx, qy;
int dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1};

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if(a[i][j] == '#') {
				pd[i - 1][j] = pd[i + 1][j] = pd[i][j - 1] = pd[i][j + 1] = 1;
			}
		}
	}
	int maxn = 0, flag = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(pd[i][j]) {
				flag = 1;
				continue;
			}
			if(a[i][j] == '#') continue;
			if(!vis[i][j]) {
				int count = 0;
				vis[i][j] = ++cnt;
				qx.push(i), qy.push(j);
				while(!qx.empty()) {
					count++;
					int nx = qx.front(), ny = qy.front();
					qx.pop(), qy.pop();
					if(pd[nx][ny]) continue;
					for(int k = 1; k <= 4; k++) {
						int tx = nx + dx[k], ty = ny + dy[k];
						if(tx < 1 || tx > n || ty < 1 || ty > m) continue;
						if(!vis[tx][ty]) {
							vis[tx][ty] = cnt;
							qx.push(tx), qy.push(ty);
						} else if(pd[tx][ty] && vis[tx][ty] != cnt) {
							vis[tx][ty] = cnt;
							qx.push(tx), qy.push(ty);
						}
					}
				}
				maxn = max(maxn, count);
			}
		}
	}
	if(maxn == 0) {
		cout << flag;
	} else {
		cout << maxn;
	}
}
```

---

## 作者：Ivan422 (赞：0)

又是一道搜索。

题目：给定一个 $n$ 行 $m$ 列的棋盘，由 `#` 代表障碍物。在障碍物的四周不能移动。问从一个点最多能到达多少个点。

思路：考虑直接爆搜。我们会发现爆搜的复杂度是 $O(nm)$ 的，非常安全。而我们发现不被障碍物吸附的点搜过一次就处于同一区域内，不能重复访问。而吸附过的点可以同时为 $4$ 个区域使用。就算有重复使用，复杂度还是不会被卡掉。

这题其实就是一个走迷宫，求能最多走到多少个位置。要注意处理被吸附的点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,m,dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int ans,f[N*N],cur;
char a[N][N];
int vis[N][N];
void dfs(int x,int y){
    if(a[x][y]=='C'){vis[x][y]=cur;f[cur]++;return;}
    if(a[x][y]=='#'){return;}
    f[cur]++;
    vis[x][y]=cur;
    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<1||ny<1||nx>n||ny>m)continue;
        if(vis[nx][ny]==cur)continue;
        if(vis[nx][ny]&&a[nx][ny]!='C')continue;
        dfs(nx,ny);
    }
    return;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){for(int j=1;j<=m;j++){cin>>a[i][j];}}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]=='#'){
        for(int k=0;k<4;k++){
            int nx=i+dx[k],ny=j+dy[k];
            if(a[nx][ny]=='.')a[nx][ny]='C';
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='#'){
        if(a[i][j]=='.'&&vis[i][j])continue;
        ++cur;
        dfs(i,j);
        ans=max(ans,f[cur]);
    }
    cout<<ans;
    return 0;
}
```

---

