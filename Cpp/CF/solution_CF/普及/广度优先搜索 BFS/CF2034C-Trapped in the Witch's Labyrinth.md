# Trapped in the Witch's Labyrinth

## 题目描述

在《列王纪》传奇英雄鲁斯塔姆的第四个任务中，一个老女巫创造了一个迷宫来困住他。迷宫是一个 $n\times m$ 的矩形网格，迷宫中每一个单元格都有箭头，指向上、下、左或右的一个特定方向。女巫对鲁斯塔姆施了魔法，他每进入一个单元格，都会按照箭头的方向移动到下一个单元格。

如果鲁斯塔姆可以离开迷宫，他将战胜女巫。否则他将永远被困在迷宫中。

还有一些单元格的方向没有被女巫确定，她希望你指定一些方向，使得鲁斯塔姆能够被困住的起始格最多。你的任务是找到使得鲁斯塔姆被困住的最多起始单元格数。

## 样例 #1

### 输入

```
3
3 3
UUU
L?R
DDD
2 3
???
???
3 3
?U?
R?L
RDL```

### 输出

```
0
6
5```

# 题解

## 作者：Gary0925 (赞：7)

## 题意翻译

### 题目描述

在来自[沙纳玛](https://en.wikipedia.org/wiki/Shahnameh)的传奇英雄罗丹的[第四次行动](https://www.gathertales.com/story/the-tale-of-the-haft-khan-seven-labors-of-rostam/sid-604)中，一个女巫创造了一个神奇的迷宫来困住他。迷宫是一个 $ n $ 行 $ m $ 列的矩形网格。迷宫中的每个网格都指向一个特定的方向：上、下、左或右。女巫施了魔法，使罗丹在一个网格里会按照网格指示的方向移动到下一个网格。

![](https://espresso.codeforces.com/fe31b399bb2207f13616c91f5553e04c54d77805.webp)

如果罗丹最终走出迷宫，他将从女巫的魔法中解脱出来，并击败她。否则，他将永远无法逃脱。

女巫还没有确定所有网格指向的方向。她想为未分配方向的网格分配方向，使能让罗丹永远被困的起始格的数量最多。你的任务是找到最大数量的使罗丹永远被困的起始格。

### 输入格式

输入的第一行包含一个整数 $ t(1≤t≤10^4) $，表示测试数据的数量。

对于每个测试数据：

- 第一行包含两个整数 $ n $ 和 $ m(1 \leq n,m \leq 1000) $，表示迷宫的行数和列数。

- 接下来的 $ n $ 行包含一个字符串 $ m $，表示网格方向。每个字符都是以下字符之一：

  - U（上）
  - D（下）
  - L（左）
  - R（右）
  - ?（还未分配方向）

保证所有数据的 $ n \times m $ 之和最多为 $ 10^6 $。

### 输出格式

对于每个测试数据，输出将方向分配给未分配方向的单元格后，能让罗丹永远被困的起始格的最大数量。

## 思路

用记忆化 dfs 判断每个起始格能否让罗丹永远被困：

**如果当前格是 `U`、`D`、`L` 或 `R`**
+ 如果当前格出发会产生环，回到该格，罗丹永远被困。
+ 如果当前格指向的格能困住罗丹，罗丹永远被困。

**如果当前格是 `?`**
+ 如果当前格周围有 `?`，罗丹永远被困（两格互指）。
+ 如果当前格出发能产生环，回到该格，罗丹永远被困。
+ 如果当前格周围有格能困住罗丹，罗丹永远被困。

### 合并：

实际上，可以用一种巧妙的方法把所有情况和并为两种情况：
1. 当前格是 `U`、`D`、`L` 或 `R`
2. 当前格是 `?`

方法：

在继续向下搜索前把当前格的状态临时设为可以困住。  
这样如果当前格出发能产生环，搜回该格，会得到可以困住的结果。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define inf 0x7f7f7f7f
int t, n, m, out[1003][1003];//用 out 数组表示是否能出去，-1表示还没算过
char c[1003][1003];
bool dfs(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > m) return 1;
	if (out[i][j] == -1)
	{
		out[i][j] = 0;//在继续向下搜索前把当前格的状态临时设为可以困住。
		if (c[i][j] == 'U') out[i][j] = dfs(i - 1, j);
		else if (c[i][j] == 'D') out[i][j] = dfs(i + 1, j);
		else if (c[i][j] == 'L') out[i][j] = dfs(i, j - 1);
		else if (c[i][j] == 'R') out[i][j] = dfs(i, j + 1);
		else out[i][j] = dfs(i - 1, j) && dfs(i + 1, j) && dfs(i, j - 1) && dfs(i, j + 1);//如果四面都困不住才真的困不住
	}
	return out[i][j];
}
int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--)
	{
		memset(out, 0xff, sizeof(out));
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> c[i][j];
		int ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				ans += !dfs(i, j);
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：littlebug (赞：6)

## Solution

先考虑把能走出去的**已经确定**的格子筛掉。

因为在边缘处且指向边缘的格子一定能走出去，而指向这些格子的格子也一定能走出去，所以这个过程可以通过一个从外到内的 bfs 实现，于是我们就筛掉了所有一定能走出去的**已经确定**的格子。

然后看**还未确定**的格子，也就是 `?`。

我们发现，`?` 只能指向它四周的四个方向，而如果这四个方向都一定能走出去，那么该 `?` 指向哪里都是一样的，都一定能走出去。于是可以把这部分 `?` 筛掉。而对于有一个方向不确定是否能走出去的，只要让 `?` 指向这个方向就能使其一定**不能**走出去，简单分讨即可证明：

- 若情况形如 `?X`（`X` 为任意已确定的格子），则因为 `X` 不能走出去，所以当 `?` 指向 `X` 时 `?` 也不能走出去。
- 若情况形如 `??`，则我们可以将两个 `?` 分别指向对方，于是就只能在两者之间反复横跳了，也无法走出去。

注意要特判 `?` 在边界上的情况，某洛谷用户名以 L 开头的 fw 因为这个赛时没过，还不知道错哪了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<bitset>

#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair <int,int>
#define mp make_pair
#define st first
#define nd second

using namespace std;

const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
const char dc[5]={'-','U','D','L','R'};
const int MAXN=1000+5;
int n,m;
char a[MAXN][MAXN];
bitset <MAXN> b[MAXN];
int c[MAXN][MAXN];

il void mask(int i,int j)
{
    b[i][j]=1;
    rep(k,1,4) ++c[i+dx[k]][j+dy[k]];
}

il void bfs()
{
    queue <pii> q;
    rep(i,1,n) a[i][1]=='L' && (q.emplace(i,1),mask(i,1),1),a[i][m]=='R' && (q.emplace(i,m),mask(i,m),1); // L,R
    rep(j,1,m) a[1][j]=='U' && (q.emplace(1,j),mask(1,j),1),a[n][j]=='D' && (q.emplace(n,j),mask(n,j),1); // U,D

    pii ck; int x,y,nx,ny;
    while(!q.empty())
    {
        ck=q.front(); q.pop();
        x=ck.st,y=ck.nd;

        rep(i,1,4)
        {
            nx=x+dx[i],ny=y+dy[i];
            if(nx<1 || nx>n || ny<1 || ny>m || b[nx][ny] || a[nx][ny]!=dc[i]) continue;
            q.emplace(nx,ny),mask(nx,ny);
        }
    }
}

il void solve(int __Ti)
{
    cin>>n>>m;
    rep(i,1,n) rep(j,1,m) cin>>a[i][j];
    rep(i,0,n+1) rep(j,0,m+1) b[i][j]=0,c[i][j]=0;

    bfs();

    rep(i,1,n) ++c[i][1],++c[i][m]; // 特判边界！
    rep(j,1,m) ++c[1][j],++c[n][j];

    int ans=0;
    rep(i,1,n) rep(j,1,m) !b[i][j] && c[i][j]<4 && (++ans);
    cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int __T; cin>>__T; rep(__Ti,1,__T) solve(__Ti);
    return 0;
}
```

---

## 作者：HetmesAskalana (赞：4)

## 题目大意
有一个迷宫，迷宫每个格子都有一个方向，表示踏上这个格子时下一步的方向。冒险者可以将任意点作为起点，目的是走出迷宫；巫师可以将未指定方向的问号点替换成任意方向，来阻止冒险者走出迷宫。

当冒险者在经过无限次移动也无法离开迷宫，也就是陷入死循环时，即视为冒险者被困住。求在最优的替换方案下，最多的以此为起点出发会被困住的起点的数量。

## 情况分析
因为每次行动的方向一定，所以由该点出发的路径有且仅有一条。显而易见的，如果在在一个点出发时还会回到本次行动中走过的点，即在路径中形成环路，那在这个起点出发时必定会被困住。

### 对于问号点
#### 情况1：
```markdown
1
3 3
RDL
R?L
RUL
```
可以看出，当从一个点出发的时会抵达一个问号点的时候，那从这个点出发必然出不去。

我们可以将该问号点指向其四周任意一个问号点（参考题目样例2）或者指向该问号点的非问号点，那么从任意方向踏入这个问号点都会使其陷入死循环。比如如上样例：假设将 $(2, 2)$ 替换成 `U`，那么从 $(3, 2)$ 指向 $(2, 2)$ 时会被指向 $(1, 2)$，然后 $(2, 2)$，然后……这个结论对于 $(2, 1)$ 或 $(2, 3)$ 作为起点同样成立。

#### 情况2：
```markdown
1
3 3
RRD
U?D
ULL
```
我们可以看出，问号周围的一圈形成了一个环，这使得没有点指向问号，而问号指向任一点都会被困住。

所以可以得出结论，当在问号点选择周围四个点都无法离开迷宫时，从该问号点出发也会被困住。

## 解法
我们可以通过两轮深搜，一轮搜索**从该点出发时，能否抵达问号点**，一轮搜索**从该点出发时，是否可以离开迷宫**。

同样因为每个非问号点行动方向确定，不难得出，如果一个点 $A$ 可以抵达一个之前已经被访问过的点 $B$，那点 $A$ 会继承点 $B$ 的性质。

所以在以下五种情况满足任意一种时，从该点出发会被困住：
- 从该点出发，最终会抵达一个问号点
- 在该点是问号的情况下：
  - 该点的临点可以指向该点
  - 该点的临点为问号
  - 该点的任意一个临点的路径存在环路，无法离开迷宫
- 该点出发的路径存在环路，无法离开迷宫

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1050;

bool vis[N][N], vised[N][N], can[N][N], type[N][N];
char G[N][N];
int n, m; 

bool dfs(int nowx, int nowy){ // 能否指向问号，type数组
    if(nowx < 1 || nowx > n || nowy > m || nowy < 1) return false;
    if(G[nowx][nowy] == '?') return true;
    if(vis[nowx][nowy]) return type[nowx][nowy];
    vis[nowx][nowy] = true;
    int prex = nowx, prey = nowy;
    if     (G[nowx][nowy] == 'U') nowx -= 1;
    else if(G[nowx][nowy] == 'D') nowx += 1;
    else if(G[nowx][nowy] == 'R') nowy += 1;
    else if(G[nowx][nowy] == 'L') nowy -= 1;
    
    if(dfs(nowx, nowy)){
        type[prex][prey] = true;
        return true;
    }else return false;
}

bool dfss(int nowx, int nowy){ // 能否离开迷宫，can数组
    if(nowx < 1 || nowx > n || nowy > m || nowy < 1) return true;
    if(G[nowx][nowy] == '?') return false;
    if(vised[nowx][nowy]) return can[nowx][nowy];
    vised[nowx][nowy] = true;
    int prex = nowx, prey = nowy;
    if     (G[nowx][nowy] == 'U') nowx -= 1;
    else if(G[nowx][nowy] == 'D') nowx += 1;
    else if(G[nowx][nowy] == 'R') nowy += 1;
    else if(G[nowx][nowy] == 'L') nowy -= 1;
    if(dfss(nowx, nowy)){
        can[prex][prey] = true;
        return true;
    }else return false;
}

void solve(){
    cin >> n >> m;
    for(int i = 0; i <= n + 10; ++i){ // init
        for(int j = 0; j <= m + 10; ++j){
            vis[i][j] = vised[i][j] =  type[i][j] =  can[i][j] = false;
            G[i][j] = '?';
        }
    }
    int R = 0;
    bool tmp = 0;
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= m; ++j)
            cin >> G[i][j];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            dfs(i, j);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j){
            if(vised[i][j] || G[i][j] == '?') continue; // 已经搜过了，那么can数组会被刷新成需要的状态。同时，问号点不受can数组影响
            dfss(i, j);
        }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(type[i][j] && G[i][j] != '?'){ // 指到问号 顶回去
                R++;
                continue;
            }
            if(G[i][j] == '?'){
                if(
                    (i > 1 && type[i - 1][j]) || // 临点能指到问号
                    (i < n && type[i + 1][j]) || 
                    (j > 1 && type[i][j - 1]) || 
                    (j < m && type[i][j + 1]) ||
                    (i > 1 && G[i - 1][j] == '?') || // 临点他就是问号
                    (i < n && G[i + 1][j] == '?') ||
                    (j > 1 && G[i][j - 1] == '?') ||
                    (j < m && G[i][j + 1] == '?')||
                    (i > 1 && !can[i - 1][j]) || // 就算给临点指过去他也出不去
                    (i < n && !can[i + 1][j]) || 
                    (j > 1 && !can[i][j - 1]) || 
                    (j < m && !can[i][j + 1])
                ) R++;
                continue;
            }
            if(G[i][j] != '?' && !can[i][j]) R++; // 他自己就出不去
        }
    }
    cout << R << endl;
    return;
}

int main(){
    int T; cin >> T;
    while(T--) solve();
    return false;
}
```

---

## 作者：Eddie08012025 (赞：2)

## 思路
令第 $i$ 行第 $j$ 列的字符为 $z_{i,j}$。

考虑 dfs 枚举每一个点的行走路径，用 $vis$ 数组记录 $(i,j)$ 点，当：

- 点 $(i,j)$ 为起点，在前进途中会走出迷宫，此时标记 $vis_{i,j}\gets -1$。
- 点 $(i,j)$ 未被访问过，$vis_{i,j}\gets 0$。
- 点 $(i,j)$ 为起点，在前进途中会走回前进路径中的一个点，即构成环，此时标记 $vis_{i,j}\gets 1$。
- 点 $(i,j)$ 在前进路径中但还没有得到结果，即没有走出迷宫且没有构成环，标记 $vis_{i,j}\gets 2$。

当 $z_{i,j}\ne$ `?` 时，只有一种前进方向，假如 $z_{i,j}=$ `?`，有四种前进方向，只要四个方向有其中之一能构成路径环，$vis_{i,j}$ 与路径中其他点都标记为 $1$，否则为 $-1$。

最后的答案为 $vis$ 数组中 $1$ 的个数。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,vis[1005][1005];
char z[1005][1005];
int dfs(int x,int y){
	if(vis[x][y]==-1)return -1;
	if(vis[x][y]==1||vis[x][y]==2)return 1;
	vis[x][y]=2;
	if(z[x][y]=='U')vis[x][y]=dfs(x-1,y);
	if(z[x][y]=='D')vis[x][y]=dfs(x+1,y);
	if(z[x][y]=='L')vis[x][y]=dfs(x,y-1);
	if(z[x][y]=='R')vis[x][y]=dfs(x,y+1);
	if(z[x][y]=='?'){
		if(dfs(x-1,y)==1)vis[x][y]=1;
		else if(dfs(x+1,y)==1)vis[x][y]=1;
		else if(dfs(x,y-1)==1)vis[x][y]=1;
		else if(dfs(x,y+1)==1)vis[x][y]=1;
		else vis[x][y]=-1;
	}return vis[x][y];
}
int main(){
//	freopen("1.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>z[i][j];
				vis[i][j]=0;
			}
		}//标记边界为-1
        for(int i=1;i<=n;i++)vis[i][0]=vis[i][m+1]=-1;
		for(int i=1;i<=m;i++)vis[0][i]=vis[n+1][i]=-1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(vis[i][j]==0){
					vis[i][j]=dfs(i,j);
				}
			}
		}for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(vis[i][j]==1)ans++;
			}
		}cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：wuzebang2009 (赞：1)

## 题目意思：
给你一个 $${n}\times{m}$$ 的方格，每个方格上有五种字符 `U`，`D`，`L`，`R`，`?`，分别表示在站在此方格会向上，下，左，右移动一格，问号表示可以自由填一个字符，问哪几个格子开始，永远都走不到方格外。
## 题目思路：
这道题有点类似涂色问题，我们不想一个格子如何走到外面，而是想从外面能不能反向走到此格子，我们又知道如果一个方格能被外面反向走到，那么这个格子肯定不能成为答案的一部分，所以我们将不可能的格子标出，然后再看 `?` 字符，只要他周围有一个格子不能被反向走到，那么它也可以是答案的一部分。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;

void solve(){
    cin>>n>>m;
    vector<pair<int,int>> dir[n+2][m+2];
    char mp[n+2][m+2]={};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='U') dir[i-1][j].push_back(make_pair(i,j));
            if(mp[i][j]=='D') dir[i+1][j].push_back(make_pair(i,j));
            if(mp[i][j]=='L') dir[i][j-1].push_back(make_pair(i,j));
            if(mp[i][j]=='R') dir[i][j+1].push_back(make_pair(i,j));
        }
    }
    int vis[n+2][m+2]={0};
    queue<pair<int,int>> q;
    for(int i=1;i<=n;i++) vis[i][0]=1,q.push({i,0});
    for(int i=1;i<=n;i++) vis[i][m+1]=1,q.push({i,m+1});
    for(int i=1;i<=m;i++) vis[0][i]=1,q.push({0,i});
    for(int i=1;i<=m;i++) vis[n+1][i]=1,q.push({n+1,i});
    while(!q.empty()){
        pair<int,int> now=q.front();
        q.pop();
        int x=now.first,y=now.second;
        for(auto [a,b]:dir[x][y]){
            if(!vis[a][b]){
                vis[a][b]=1;
                q.push({a,b});
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='?' && vis[i-1][j]==1 && vis[i+1][j]==1 && vis[i][j-1]==1 && vis[i][j+1]==1){
                vis[i][j]=1;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){
                ans++;
            }
        }
    }
    cout<<ans<<endl;
}

int main(){
    cin>>t;
    while(t--){
        solve();
    }
}
```

---

## 作者：wfc284 (赞：1)

先把一定能走出去的格子标记上。  
再考虑那些不是问号的但不知能不能出去的格子。实际上它们已经走不出去了（因为他们最后要么成环要么走向问号），标记上即可。

这里有个小问题：通向问号的格子能否走出去？  
答案是否定的。只要让问号通向【通向它的格子】，那都走不出去了。  

剩下的就是问号了。它走不出去的充要条件是：四周存在问号（这样可构造二元环），或周围存在已标记的走不出去的格子。  

还是有个小问题：问号连通块一定都走不出去吗？  
显然走不出去。可构造任意一个问号指向另外一个问号，就都走不出去了。  

最后数数就行。  

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 1e3+2, V = 2e6+2;
	const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int tab[200];
	
	int n, m;
	char c[N][N];
	int pos(int x, int y) { return x * (m+2) + y+1; }
	
	vector<int> g[V];
	int f[V];
	void DFS(int u) {
		f[u] = 1;
		for(auto v : g[u]) DFS(v);
	}
	
	void main() {
		tab['R'] = 0, tab['D'] = 1, tab['L'] = 2, tab['U'] = 3;
		
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) scanf("%s", c[i]+1);
		
		for(int i = 0; i <= n+1; ++i)
			for(int j = 0; j <= m+1; ++j) g[pos(i, j)].clear(), f[pos(i, j)] = 0;
		
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= m; ++j) {
				if(c[i][j] == '?') continue;
				int u = pos(i, j), v = pos(i + dir[tab[c[i][j]]][0], j + dir[tab[c[i][j]]][1]);
				g[v].push_back(u);
			}
		
		for(int i = 1; i <= n; ++i) 
			DFS(pos(i, 0)), DFS(pos(i, m+1));
		for(int j = 1; j <= m; ++j)
			DFS(pos(0, j)), DFS(pos(n+1, j));
			
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(c[i][j] == '?') {
					f[pos(i, j)] = 1;
					for(int k = 0; k < 4; ++k) {
						int nx = i + dir[k][0], ny = j + dir[k][1];
						if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
						if(c[nx][ny] == '?' || f[pos(nx, ny)] == 0) {
							f[pos(i, j)] = 0;
							break;
						}
					}
				}
		
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) ans += f[pos(i, j)] ^ 1;
		cout << ans << '\n';
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	scanf("%d", &_);
	while(_--) Traveller::main();
	return 0;
}
 
```

---

## 作者：1234567890sjx (赞：1)

考虑这样的一个策略：

+ 若存在一个只包含 `?` 的四连通块满足该块内 `?` 的数目不小于 $2$，则考虑任选两个相邻的 `?` 并让它们互相只想对方，其余的 `?` 都指向这两个 `?` 中的一个。
+ 若某一个 `?` 四联通的某一个位置不是 `?`，且从该位置出发会无限循环，则让这个 `?` 指向这个位置。
+ 剩下的位置随便指向任意一个位置。

容易证明该策略正确。若把指向关系显示建图则形成一个基环森林，维护的话可以使用并查集和 dfs 找环。总时间复杂度为 $O(\alpha nm)$。

代码可能有点难写。

```cpp
char s[2010][2010];
int id[2010][2010], fa[N], fm[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int vis[2010][2010], n, m, dfn;
int dfs(int x, int y) {
    assert(s[x][y] != '?');
    if (x < 1 || y < 1 || x > n || y > m) return 0;
    if (vis[x][y] == dfn)
        return 1;
    else if (vis[x][y] && fm[id[x][y]])
        return 1;
    else if (vis[x][y])
        return 0;
    vis[x][y] = dfn;
    if (s[x][y] == 'U') {
        if (dfs(x - 1, y)) {
            fm[id[x][y]] = 1;
            return 1;
        }
    }
    if (s[x][y] == 'D') {
        if (dfs(x + 1, y)) {
            fm[id[x][y]] = 1;
            return 1;
        }
    }
    if (s[x][y] == 'L') {
        if (dfs(x, y - 1)) {
            fm[id[x][y]] = 1;
            return 1;
        }
    }
    if (s[x][y] == 'R') {
        if (dfs(x, y + 1)) {
            fm[id[x][y]] = 1;
            return 1;
        }
    }
    return 0;
}
void run() {
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stderr);
    int T = read(), ca = 1;
    while (T--) {
        n = read(), m = read();
        for (int i = 1; i <= n; ++i)
            scanf("%s", s[i] + 1);
        // if (ca++ == 41) {
        //     for (int i = 1; i <= n; ++i, cerr << '\n')
        //         for (int j = 1; j <= m; ++j) cerr << s[i][j];
        // }
        dfn = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (s[i][j] == '?')
                    for (int d = 0; d < 4; ++d) {
                        int ii = i + dx[d], jj = j + dy[d];
                        if (ii >= 1 && ii <= n && jj >= 1 && jj <= m && s[ii][jj] == '?') {
                            if (d == 0) s[i][j] = 'R', s[ii][jj] = 'L';
                            else if (d == 2) s[i][j] = 'L', s[ii][jj] = 'R';
                            else if (d == 1) s[i][j] = 'D', s[ii][jj] = 'U';
                            else s[i][j] = 'U', s[ii][jj] = 'D';
                            break;
                        }
                    }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (s[i][j] == '?')
                    for (int d = 0; d < 4; ++d) {
                        int ii = i + dx[d], jj = j + dy[d];
                        if (ii >= 1 && ii <= n && jj >= 1 && jj <= m) {
                            if (s[ii][jj] != '?') {
                                int ok = 0;
                                if (s[ii][jj] == 'L' && d == 0) s[i][j] = 'R', ok = 1;
                                else if (s[ii][jj] == 'R' && d == 2) s[i][j] = 'L', ok = 1;
                                else if (s[ii][jj] == 'U' && d == 1) s[i][j] = 'D', ok = 1;
                                else if (s[ii][jj] == 'D' && d == 3) s[i][j] = 'U', ok = 1;
                                if (ok) break;
                            }
                        }
                    }
        // for (int i = 1; i <= n; ++i, cout << '\n')
        //     for (int j = 1; j <= m; ++j) cout << s[i][j];
        int idx = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                ++idx;
                id[i][j] = idx;
                fa[idx] = idx;
                fm[idx] = 0;
                vis[i][j] = 0;
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (s[i][j] != '?')
                    ++dfn, dfs(i, j);
        // for (int i = 1; i <= n; ++i, cout << '\n')
        //     for (int j = 1; j <= m; ++j) cout << s[i][j];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (s[i][j] != '?') {
                    int ii, jj;
                    if (s[i][j] == 'L') ii = i, jj = j - 1;
                    else if (s[i][j] == 'R') ii = i, jj = j + 1;
                    else if (s[i][j] == 'U') ii = i - 1, jj = j;
                    else ii = i + 1, jj = j;
                    if (ii >= 1 && ii <= n && jj >= 1 && jj <= m) {
                        int x = find(id[i][j]), y = find(id[ii][jj]);
                        if (x != y) fm[y] |= fm[x], fa[x] = y;
                    }
                }
        // for (int i = 1; i <= n * m; ++i) cout << fm[i] << ' ';
        // cout << '\n';
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (s[i][j] == '?')
                    for (int d = 0; d < 4; ++d) {
                        int ii = i + dx[d], jj = j + dy[d];
                        if (ii >= 1 && ii <= n && jj >= 1 && jj <= m) {
                            assert(s[ii][jj] != '?');
                            if (fm[find(id[ii][jj])]) {
                                if (d == 0) s[i][j] = 'R';
                                else if (d == 2) s[i][j] = 'L';
                                else if (d == 1) s[i][j] = 'D';
                                else s[i][j] = 'U';
                                int x = find(id[ii][jj]), y = find(id[i][j]);
                                if (x != y) fm[y] |= fm[x], fa[x] = y;
                                break;
                            }
                        }
                    }
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cnt += fm[find(id[i][j])];
        // for (int i = 1; i <= n; ++i, cout << '\n')
        //     for (int j = 1; j <= m; ++j) cout << s[i][j];
        cout << cnt << '\n';
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                id[i][j] = 0;
                fa[idx] = 0;
                s[i][j] = 0;
                fm[idx] = 0;
                vis[i][j] = 0;
            }
    }
}
```

---

## 作者：Wind_love (赞：0)

## 思路
读题，我们注意到题目要求从边缘走出，所有已确定方向的格子可以确定其能否离开迷宫，则我们很容易想到如下思路。  
对于每一个边缘格，进行深搜，按格子箭头前进，所有能搜到的格子标记为可离开，访问过或未确定的格子退出。  
因为题中要求使能困住的格子最多，则对于每一个未确定的格子，若其四面均为可离开的格子，则它也为可离开的格子，否则不是。  
最后，统计可离开格子个数，用总个数减去，即为最终答案。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
char a[1005][1005];
int vis[1005][1005],d[1005][1005],vis2[1005][1005],ans=0;
void dfs(int x,int y){
	if(vis[x][y])return;
	ans++,vis[x][y]=1;
	if(a[x][y+1]=='L')dfs(x,y+1);
	if(a[x][y-1]=='R')dfs(x,y-1);
	if(a[x-1][y]=='D')dfs(x-1,y);
	if(a[x+1][y]=='U')dfs(x+1,y);
	return;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ans=0;
		memset(vis,1,sizeof vis);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j],vis[i][j]=0;
		for(int i=1;i<=n;i++){
			if(a[i][1]=='L')dfs(i,1);
			if(a[i][m]=='R')dfs(i,m);
		}
		for(int i=1;i<=m;i++){
			if(a[1][i]=='U')dfs(1,i);
			if(a[n][i]=='D')dfs(n,i);
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]=='?'&&vis[i-1][j]&&vis[i+1][j]&&vis[i][j-1]&&vis[i][j+1])ans++;
		cout<<n*m-ans<<"\n";
	}
	return 0;
}

---

## 作者：rainbow_cat (赞：0)

对于一个不是 `?` 的位置，若它可以循环回到自己，则无法走出，同时，若其到达一个 `?` 也无法走出，这是显然的。  
对于一个是 `?` 的位置，若其与 `?` 或无法走出但有方向的格子相邻，同样无法走出。   
综上，搜索预处理出哪些点无法到达迷宫外后判断即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans;
char c[1010][1010];
bool flag[1010][1010],vis[1010][1010];
void dfs(int x,int y)
{
	vis[x][y]=1;
	int nx=x,ny=y;
	if(c[x][y]=='U')nx--;
	if(c[x][y]=='D')nx++;
	if(c[x][y]=='L')ny--;
	if(c[x][y]=='R')ny++;
	if(c[x][y]=='?')return;
	if(nx>=1&&nx<=n&&ny>=1&&ny<=m)
	{
		if(vis[nx][ny])
		{
			flag[x][y]=flag[nx][ny];
			return;
		}
		dfs(nx,ny);
		flag[x][y]=flag[nx][ny];
	}
	else
	{
		flag[x][y]=1;
		return;
	}
}
int main()
{
//	freopen("in.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>c[i][j],flag[i][j]=vis[i][j]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!vis[i][j]&&c[i][j]!='?')
					dfs(i,j);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(c[i][j]=='?')
				{
					if(i!=1&&c[i-1][j]=='?'||i!=n&&c[i+1][j]=='?'||j!=1&&c[i][j-1]=='?'||j!=m&&c[i][j+1]=='?')ans++;
					else if(i!=1&&!flag[i-1][j]||i!=n&&!flag[i+1][j]||j!=1&&!flag[i][j-1]||j!=m&&!flag[i][j+1])ans++;
				}
				else if(!flag[i][j])ans++;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
/*
1
2 1
R
?
*/
```

---

## 作者：xuyifei0302 (赞：0)

# 题目解法

## 前置知识

并查集

## 解题思路

因为有一些格子是确定了所指方向的，因为做过[这道题](https://www.luogu.com.cn/problem/CF1495C)所以不难想到用并查集计算出从每一个格子出发，最终会到达哪一个格子，如果这个格子指向的是地图外，那么它不会是一个好单元格。但是，我们现在有一些单元格是没有确定方向的，我们就可以先不访问它，因为它可以指向任意方向。若一个确定了的格子指向的格子为地图内的一个单元格，则从这个格子出发，一定到不了地图外，因为从这个单元格出发，要么已经构成了环，要么可以通过未确定的格子构成环。对于未确定的格子，只要它的上下左右中有一个格子指向的单元格在地图内，则这个单元格一定可以是坏的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int x, y;
} f[1005][1005];
int t, n, m, a[1005][1005];
Node get_father(int x, int y) {
	if (f[x][y].x == x && f[x][y].y == y) {
		return f[x][y];
	} else {
		f[x][y] = get_father(f[x][y].x, f[x][y].y);
		return f[x][y];
	}
}
bool check(Node x, Node y) {
	if (x.x == y.x && x.y == y.y) {
		return true;
	} else {
		return false;
	}
}
bool g(Node x) {
	if (x.x >= 1 && x.x <= n && x.y >= 1 && x.y <= m) {
		return true;
	}
	return false;
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 1; i <= n; i ++) {
			string s;
			cin >> s;
			s = " " + s;
			for (int j = 1; j <= m; j ++) {
				if (s[j] == 'U') {
					a[i][j] = 1;
				} else if (s[j] == 'D') {
					a[i][j] = 2;
				} else if (s[j] == 'L') {
					a[i][j] = 3;
				} else if (s[j] == 'R') {
					a[i][j] = 4;
				} else if (s[j] == '?') {
					a[i][j] = 5;
				}
			}
		}
		for (int i = 0; i <= n + 1; i ++) {
			for (int j = 0; j <= m + 1; j ++) {
				f[i][j].x = i, f[i][j].y = j;
			}
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				if (a[i][j] == 1) {
					Node fx = get_father(i, j), fy = get_father(i - 1, j);
					if (check(fx, fy)) {
						continue;
					}
					f[fx.x][fx.y] = fy;
				} else if (a[i][j] == 2) {
					Node fx = get_father(i, j), fy = get_father(i + 1, j);
					if (check(fx, fy)) {
						continue;
					}
					f[fx.x][fx.y] = fy;
				} else if (a[i][j] == 3) {
					Node fx = get_father(i, j), fy = get_father(i, j - 1);
					if (check(fx, fy)) {
						continue;
					}
					f[fx.x][fx.y] = fy;
				} else if (a[i][j] == 4) {
					Node fx = get_father(i, j), fy = get_father(i, j + 1);
					if (check(fx, fy)) {
						continue;
					}
					f[fx.x][fx.y] = fy;
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				if (a[i][j] == 5) {
					Node fu = get_father(i - 1, j), fd = get_father(i + 1, j), fl = get_father(i, j - 1), fr = get_father(i, j + 1);
					if (g(fu) || g(fd) || g(fl) || g(fr)) {
						ans ++;
					}
					continue;
				}
				Node fx = get_father(i, j);
				if (g(fx)) {
					ans ++;
				}
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Karieciation (赞：0)

## 题目传送门

[luogu  门。](https://www.luogu.com.cn/problem/CF2034C)

[codeforces 门。](https://codeforces.com/contest/2034/problem/C)

~~（赛场上挂分了呜呜呜~~

## 题目大意分析

### 确定思路

本题给出一个迷宫，每个点可以有一种可能的移动方向（即 `U/L/D/R`），四种可能的移动方向（即 `?`），题目希望我们使尽可能多的格子走不出地图。

我们可以将题目抽象为：在一个集合里（这个集合**包括迷宫和迷宫外的地方**），每个点都向外发射一条边，考虑使用**并查集**。

### 并查集作用

**并查集**大家都很熟悉，它可以进行**合并**、**查找**的操作。我们可以使用并查集合并点来判断从当前点出发**是否能被困**在迷宫中——只要有迷宫外一点在一个集合内，本集合内点都不能被困，反之则永远被困。

### 本题性质

如果在迷宫中出现闭环，从此点出发一定被困，用并查集来实现的话，如果在**合并**操作中**被合并的两点本来就在一个集合中**，从这个集合里出发的点就一定被永远困在地图中，我们可以引入 `vis[]`，将本集合的父亲的 `vis[]` 设为 true，而由于一个点为 `?` 时他可以任意选择方向，所以只要有点指向 `?`，这个集合将都被困住，反之：一个点所在集合的父亲指向 `?`，这个集合也都被困住，所以，当一个 `?` 的四周有指向 `?` 的集合，这个 `?` 也被困住。

## 代码实现

我们最终会发现我们维护了一个 $(n+2)\times(m+2)$ 大小的矩阵，这里采用二维矩阵化一维链的方式来维护并查集和 `vis[]`，具体细节请详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1005,INF=0x3f3f3f3f;
int n,m,f[N*N];
char s[N][N];
bool vis[N*N];
int Find(int x)
{
	return x==f[x]?x:f[x]=Find(f[x]);
}
void merge(int x,int y)
{
	int xx=Find(x),yy=Find(y);
	if(xx!=yy)
		f[xx]=yy;
	else
		vis[xx]=true;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		for(int i=1;i<=m;i++)
			s[0][i]=s[n+1][i]=0;
		for(int i=1;i<=n;i++)
			s[i][0]=s[i][m+1]=0;
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=m+1;j++)
				f[i*(m+2)+j]=i*(m+2)+j,vis[i*(m+2)+j]=false;//初始化+打墙
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int now=i*(m+2)+j;
			if(s[i][j]=='U')
				merge(now,(i-1)*(m+2)+j);
			else if(s[i][j]=='L')
				merge(now,i*(m+2)+j-1);
			else if(s[i][j]=='D')
				merge(now,(i+1)*(m+2)+j);
			else if(s[i][j]=='R')
				merge(now,i*(m+2)+j+1);
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		if(s[i][j]=='?')
		{
			int now=i*(m+2)+j;
			int a=Find((i-1)*(m+2)+j);
			int b=Find(i*(m+2)+j-1);
			int c=Find((i+1)*(m+2)+j);
			int d=Find(i*(m+2)+j+1);
			if(a==now||b==now||c==now||d==now\
			||vis[a]||vis[b]||vis[c]||vis[d]\
			||s[a/(m+2)][a%(m+2)]||s[b/(m+2)][b%(m+2)]\
			||s[c/(m+2)][c%(m+2)]||s[d/(m+2)][d%(m+2)])//此处写法甚妙，看不懂的话可以细品
				vis[now]=true;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(vis[Find(i*(m+2)+j)])
					ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```

***

本做法仅使用并查集，希望能给大家带来帮助~

---

## 作者：HYdroKomide (赞：0)

### 题意：

一个有方向的迷宫，必须按照箭头方向移动，有些箭头未指定。问最多有多少起始格子无法离开迷宫。

### 思路：

我们无法改变确定了的格子，所以先用一个 dfs 把所有已经确定的格子遍历一遍，确认到了哪些格子一定可以逃离迷宫。

接着，我们考虑未确定的格子。如果有任何周围的格子指向未确定的这个格子，那么它一定是无法离开迷宫的（可以将两个格子互相指向对方）。如果周围有任何未确定的格子，两个格子互相指向对方，也可以做到困在迷宫中。如果周围有任何无法离开迷宫的方格，将它指向这个方格也永远出不去。

对于任何一个未确定的格子，只要它周围的四个格子中有以上任意一种情况，都是可以离开迷宫的。对于任何一个已经确定的格子，只有当它一定指向迷宫之外时才可逃离，否则一定会被困住。

模拟即可。

### 程序如下：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=1e3+5;
int T,n,m;
char mp[N][N];
bool vis[N][N];
struct TER{int x,y;}a[N][N],f[N][N];
TER dfs(int x,int y){
	if(x<1||x>n||y<1||y>m)return a[x][y]={-1,-1};
	if(a[x][y].x==114514)return {114514,114514};
	if(vis[x][y]||mp[x][y]=='?')return a[x][y]={114514,114514};
	if(f[x][y].x==-1||a[x][y].x==-1)return a[x][y]={-1,-1};
	vis[x][y]=true;
	a[x][y]=dfs(f[x][y].x,f[x][y].y);
	vis[x][y]=false;
	return a[x][y];
}
int main(){
	scanf("%d",&T);
	while(T--){
		int ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%s",mp[i]+1);
			for(int j=1;j<=m;j++){
				if(mp[i][j]=='U'){
					if(i==1)f[i][j]={-1,-1};
					else f[i][j]={i-1,j};
				}
				if(mp[i][j]=='D'){
					if(i==n)f[i][j]={-1,-1};
					else f[i][j]={i+1,j};
				}
				if(mp[i][j]=='L'){
					if(j==1)f[i][j]={-1,-1};
					else f[i][j]={i,j-1};
				}
				if(mp[i][j]=='R'){
					if(j==m)f[i][j]={-1,-1};
					else f[i][j]={i,j+1};
				}
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(mp[i][j]!='?'&&a[i][j].x!=-1&&a[i][j].x!=-114514){
					a[i][j]=dfs(i,j);
				}
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(mp[i][j]!='?'&&a[i][j].x!=-1)ans++;
				else if(mp[i][j]=='?'){
					if(a[i-1][j].x==114514||a[i+1][j].x==114514||a[i][j-1].x==114514||a[i][j+1].x==114514)ans++;
					else if(mp[i-1][j]=='?'||mp[i+1][j]=='?'||mp[i][j-1]=='?'||mp[i][j+1]=='?')ans++;
				}
			}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]={0,0},f[i][j]={0,0},vis[i][j]=false,mp[i][j]=0;
	}
	return 0;
}
```

### THE END

---

