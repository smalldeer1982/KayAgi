# Imagination Castle

## 题目描述

Given a chessboard of size $ N \times M $ ( $ N $ rows and $ M $ columns). Each row is numbered from $ 1 $ to $ N $ from top to bottom and each column is numbered from $ 1 $ to $ M $ from left to right. The tile in row $ r $ and column $ c $ is denoted as $ (r,c) $ . There exists $ K $ distinct special tiles on the chessboard with the $ i $ -th special tile being tile $ (X_i,Y_i) $ . It is guaranteed that tile $ (1,1) $ is not a special tile.

A new chess piece has been invented, which is the castle. The castle moves similarly to a rook in regular chess, but slightly differently. In one move, a castle that is on some tile can only move to another tile in the same row or in the same column, but only in the right direction or the down direction. Formally, in one move, the castle on tile $ (r,c) $ can only move to tile $ (r',c') $ if and only if one of the following two conditions is satisfied:

- $ r'=r $ and $ c'>c $ .
- $ c'=c $ and $ r'>r $ .

Chaneka and Bhinneka will play a game. In the beginning of the game, there is a castle in tile $ (1,1) $ . The two players will play alternatingly with Chaneka going first. In one turn, the player on that turn must move the castle following the movement rules of the castle.

If a player moves the castle to a special tile on her turn, then that player wins the game and the game ends. If on a turn, the castle cannot be moved, the player on that turn loses and the game ends.

Given the size of the board and the locations of each special tile. Determine the winner of this game if Chaneka and Bhinneka plays optimally.

## 说明/提示

In the first example, the following is an illustration of the chessboard in the beginning of the game.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1866I/abb2443546fc42613e118bd34d78329cb16fee7a.png)

Chaneka can move the castle to special tile $ (1,3) $ or $ (1,5) $ directly on her first turn. Therefore, Chaneka is the winner.

In the second example, the following is an illustration of the chessboard in the beginning of the game.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1866I/138a57545a74e3d437b301db2aa50b2038494a7a.png)

Chaneka can only move the castle to tile $ (1, 2) $ or $ (2, 1) $ on her first turn. Whatever Chaneka does, Bhinneka will be able to directly move the castle to tile $ (2, 2) $ . After that, on Chaneka's turn, she cannot move the castle, so Chaneka loses. Therefore, Bhinneka is the winner.

## 样例 #1

### 输入

```
4 5 3
1 3
4 4
1 5```

### 输出

```
Chaneka```

## 样例 #2

### 输入

```
2 2 0```

### 输出

```
Bhinneka```

# 题解

## 作者：软糖RT (赞：3)

和题解做法一样。

关于必胜态，必败态等定义可以查询 [OIwiki](https://oi-wiki.org/math/game-theory/impartial-game/)，此处不赘述。

考虑一个特殊点会给我们带来什么信息：它上方和左方的所有点都会变成必胜态，而必败态的信息也一样。因而，我们可以考虑从右下往右上不断逼近我们的答案，目标是让我们的目前考虑的点只受到一个信息影响。

如果一个点右方有特殊点，那么这个点就是必胜的，进而的，这个点左方的点全是必胜的，所以这一行目前有效的信息已经算完，往上走一行。

如果一个点下方有特殊点，那么这个点就是必胜的，进而的，这个点上方的点全是必胜的，所以这一列目前有效的信息已经算完，往左走一列。

两个最基本的策略可以让我们在有特殊点的情况下迅速缩小问题规模，且保证所有我们即将考虑的点下方和右方都是必胜态，进而的：

如果一个点右方和下方都没有特殊点，因为我们先前的路径，你知道这个点没有被确定为必胜，而且，由于上方的保证和必败态的定义，这个点是必败的，根据必胜态的定义，这个点上方和左方都是必胜的。所以往左走一列，再往上走一行。

至此，我们只需要从 $(N,M)$ 开始递推，且最多访问 $N+M$ 个状态，直接朴素的查询，每一个特殊点也只会被考虑至多一次，所以时间复杂度是 $O(N+M+K)$ 的。

我们能够简洁的写出如下的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200004;
int n,m,k,ss,ans;
vector<int> spx[N],spy[N];//分别从 x,y 的视角查询 
void solve(int x,int y){
	for(int i=0;i<spx[x].size();i++){//考虑下方点 
		if(spx[x][i]>y){
			if(x==1){
				ans=1;
				return;
			}
			solve(x-1,y);
			return;
		}
	}
	for(int i=0;i<spy[y].size();i++){//考虑右方点 
		if(spy[y][i]>x){
			if(y==1){
				ans=1;
				return;
			}
			solve(x,y-1);
			return;
		}
	}
	if(x==1&&y==1){//如果已经到达第一行或者第一列，下一轮递推一定能算出目标值。 
		ans=0;
		return;
	}
	if(x==1||y==1){
		ans=1;
		return;
	}
	solve(x-1,y-1);
}
int main(){
	cin>>n>>m>>k;
	for(int i=1,x,y;i<=k;i++){
		cin>>x>>y;
		spx[x].push_back(y);
		spy[y].push_back(x);
	}
	solve(n,m);
	if(ans){
		cout<<"Chaneka";
	}else{
		cout<<"Bhinneka";
	}
	return 0;
} 
```


---

## 作者：Leasier (赞：2)

不难，但感觉很优雅 /jw

------------

首先可以考虑一个暴力的 bool SG：

- 设 $f(x, y)$ 表示棋子现在位于 $(x, y)$，先手必胜还是必败。
- $f(x, y)$ 为 $\operatorname{true}$ 当且仅当 $(x, y)$ 不为特殊点，且 $\exists y' > y, f(x, y') = \operatorname{false}$ 或 $\exists x' > x, f(x', y) = \operatorname{false}$。
- 直接求出每个 $f(x, y)$ 可以做到 $O(nm)$。

------------

不妨先来考虑 $n \leq m, k = 0$ 的情况，注意到此时：

- $f(n, m) = \operatorname{false}$，于是第 $n$ 行、第 $m$ 列的余下部分均为 $\operatorname{true}$。
- $f(n - 1, m - 1) = \operatorname{false}$，于是第 $n - 1$ 行、第 $m - 1$ 列的余下部分均为 $\operatorname{true}$。
- ……
- $f(1, m - n + 1) = \operatorname{false}$，于是第 $1$ 行、第 $m - n + 1$ 列的余下部分均为 $\operatorname{true}$。

于是当 $n \neq m$ 时先手必胜，否则先手必败。

------------

接下来我们尝试加入特殊点。对于一个特殊点而言，其带来的影响为：

- 左边和上边的非特殊点处的 $f$ 值全部变为 $\operatorname{true}$。

至此可以注意到我们事实上更加关心的是**一行最右侧的非特殊点且 $f$ 值为 $\operatorname{false}$ 的位置**。

遂考虑从下往上一行一行扫，记录一下扫到目前位置哪些列有 $\operatorname{false}$，双指针即可扫出这行中我们关心的位置。

时间复杂度为 $O(n + m + k)$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

bool vis[200007];
vector<int> v[200007];

int main(){
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++){
		int x, y;
		cin >> x >> y;
		if (x == 1){
			cout << "Chaneka";
			return 0;
		}
		v[x].push_back(y);
	}
	int lst = m;
	for (int i = n; i >= 1; i--){
		while (vis[lst]) lst--;
		if (lst == 0){
			cout << "Chaneka";
			return 0;
		}
		int size = v[i].size();
		bool flag = true;
		for (int j = 0; j < size; j++){
			vis[v[i][j]] = true;
			if (v[i][j] >= lst) flag = false;
		}
		if (flag) vis[lst] = true;
	}
	if (lst != 1){
		cout << "Chaneka";
	} else {
		cout << "Bhinneka";
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

tag：DP 优化

# Solution

考虑比较朴素的 DP，设 $f_{i,j}$ 为以 $(i,j)$ 是先手必胜还是后手必胜（先手必胜是 $1$），转移：
- $(i,j)$ 是特殊点，$f_{i,j}=0$；
- 否则，如果存在 $f_{i,y}=0\text{ }(y>j)$ 或 $f_{x,j}=0\text{ }(x>i)$ 则 $f_{i,j}=1$，否则 $f_{i,j}=0$。

可以发现一行最多只有一个 $0$，因为这个 $0$ 左边的可以从它转移来。从大到小枚举 $i$，用一个集合 $S$ 维护当前没有 $0$ 的列，每次把特殊点所在的列删除，然后取出坐标最大的列 $j$，如果这个列在所有特殊点右边，那么把它删除，否则不用管。

如果第一行取出的最大列是 $1$ 则说明 $f_{1,1}=0$，Chaneka 赢；否则 Bhinneka 赢。

用 `std::set` 实现复杂度线对，用双指针实现复杂度线性。

# Code

```cpp
typedef long long LL;
typedef pair<LL, LL> pii;
const int N = 1e6 + 5;
int n, m, k, x, y, t[N]; set<int> s, g[N];
int main() {
	cin >> n >> m >> k;
	REP(i, 1, k) cin >> x >> y, g[x].insert(y);
	REP(i, 1, m) s.insert(i);
	DEP(i, n, 1) {
		for (auto x : g[i])
			if (s.count(x)) s.erase(x);
		t[i] = (SZ(s) ? *s.rbegin() : 0);
		if (SZ(g[i]) && t[i] <= *g[i].rbegin()) t[i] = 0;
		if (t[i] > 0) s.erase(t[i]);
	}
	cout << (t[1] == 1 ? "Bhinneka" : "Chaneka") << '\n';
	return 0;
}
```

---

