# MADMAX

## 题目描述

As we all know, Max is the best video game player among her friends. Her friends were so jealous of hers, that they created an actual game just to prove that she's not the best at games. The game is played on a directed acyclic graph (a DAG) with $ n $ vertices and $ m $ edges. There's a character written on each edge, a lowercase English letter.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/069e27c85e808ca91bd505121a515c236f5fa449.png)Max and Lucas are playing the game. Max goes first, then Lucas, then Max again and so on. Each player has a marble, initially located at some vertex. Each player in his/her turn should move his/her marble along some edge (a player can move the marble from vertex $ v $ to vertex $ u $ if there's an outgoing edge from $ v $ to $ u $ ). If the player moves his/her marble from vertex $ v $ to vertex $ u $ , the "character" of that round is the character written on the edge from $ v $ to $ u $ . There's one additional rule; the ASCII code of character of round $ i $ should be greater than or equal to the ASCII code of character of round $ i-1 $ (for $ i>1 $ ). The rounds are numbered for both players together, i. e. Max goes in odd numbers, Lucas goes in even numbers. The player that can't make a move loses the game. The marbles may be at the same vertex at the same time.

Since the game could take a while and Lucas and Max have to focus on finding Dart, they don't have time to play. So they asked you, if they both play optimally, who wins the game?

You have to determine the winner of the game for all initial positions of the marbles.

## 说明/提示

Here's the graph in the first sample test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/f151740282c29ba680f87bf7d965be1031607fc5.png)Here's the graph in the second sample test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/69855104972fed090a243866610202e10d83d508.png)

## 样例 #1

### 输入

```
4 4
1 2 b
1 3 a
2 4 c
3 4 b
```

### 输出

```
BAAA
ABAA
BBBA
BBBB
```

## 样例 #2

### 输入

```
5 8
5 3 h
1 2 c
3 1 c
3 2 r
5 1 r
4 3 z
5 4 r
5 2 h
```

### 输出

```
BABBB
BBBBB
AABBB
AAABA
AAAAB
```

# 题解

## 作者：rui_er (赞：3)

一道比较简单的 DP。

我们开一个三维数组 $dp_{i,j,w}$ 表示一个人在 $i$，另一个人在 $j$，且另一个人上一步走棋走的边权值为 $w$ 的胜负情况。转移时枚举 $i$ 的所有权值不小于 $w$ 的出边，如果可以走到“必败状态”则当前点为“必胜状态”，如果无法走到则为“必败状态”。

由于初始状态和转移的顺序不太好处理（也许可以拓扑排序，但我懒），所以我们采用记忆化搜索来求答案。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 105;

int n, m, dp[N][N][26];
vector<tuple<int, int> > e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int dfs(int u, int d, int now) {
	if(~dp[u][d][now]) return dp[u][d][now];
	for(auto i : e[u]) {
		int v = get<0>(i), w = get<1>(i);
		if(w < now) continue;
		if(!dfs(d, v, w)) return dp[u][d][now] = 1;
	}
	return dp[u][d][now] = 0;
}

int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		int u, v, w;
		scanf("%d%d %c", &u, &v, &w);
		e[u].push_back(make_tuple(v, w-'a'));
	}
	rep(i, 1, n) {
		rep(j, 1, n) {
			putchar('A'+!dfs(i, j, 0));
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

dp(i,j,k)表示先手在第i个点，后手在第j个点，上一步的边权为k为必胜还是必负，如果能转移到必负，则为必胜，否则必负。状态总数为100*100*26=2.6e5

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int dp[N][N][30];
vector<pair<int,int>>e[N];
int dfs(int a,int b,int c)
{
	if(dp[a][b][c]!=-1)
		return dp[a][b][c];
	dp[a][b][c]=0;
	for(int i=0;i<e[a].size();i++)
	{
		int v=e[a][i].first;
		if(e[a][i].second<c)
			continue;
		if(!dfs(b,e[a][i].first,e[a][i].second))
		{
			dp[a][b][c]=1;
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	memset(dp,-1,sizeof(dp));
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		char c;
		cin>>u>>v>>c;
		e[u].push_back(make_pair(v,c-'a'));
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(dfs(i,j,0))
				cout<<'A';
			else
				cout<<'B';
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：1234567890sjx (赞：0)

简单 dp。设 $f_{i,j,k}$ 表示当前要走的人棋子位于 $i$，上一个走的人把她的棋子走到了 $j$，走过的边权是 $k$，当前走的人是否能获胜。每一次转移的时候直接枚举 $i$ 所有的出边，判断权值是否大于或等于 $k$，然后直接暴力转移即可。具体实现的话可以写一个记忆化搜索然后一个状态一个状态暴力搜索，但是容易证明时间复杂度正确。然后就做完了。$1700$ 就是水。

---

