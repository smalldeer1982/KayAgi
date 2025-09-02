# [ABC208D] Shortest Path Queries 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc208/tasks/abc208_d

高橋王国には $ N $ 個の都市と $ M $ 本の道路があります。

都市には $ 1 $ から $ N $ の番号が、道路には $ 1 $ から $ M $ の番号が割り振られています。道路 $ i $ は都市 $ A_i $ から $ B_i $ へ向かう**一方通行**の道で、移動するのに $ C_i $ 分かかります。

$ f(s,\ t,\ k) $ を次のクエリへの答えとして定めます。

- 都市 $ s $ を出発して都市 $ t $ に到着するまでの最短時間を計算してください。ただし、通ってよい都市は $ s,\ t $ および番号が $ k $ 以下の都市のみとします。また、都市 $ t $ に到着できない場合や $ s\ =\ t $ である場合におけるクエリの答えは $ 0 $ とします。

全ての $ s,t,k $ に対して $ f(s,t,k) $ を計算して総和を出力してください。より厳密には、$ \displaystyle\ \sum_{s\ =\ 1}^N\ \sum_{t\ =\ 1}^N\ \sum_{k\ =\ 1}^N\ f(s,\ t,\ k) $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 400 $
- $ 0\ \leq\ M\ \leq\ N(N-1) $
- $ 1\ \leq\ A_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ B_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ A_i\ \neq\ B_i $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ C_i\ \leq\ 10^6 $ $ (1\ \leq\ i\ \leq\ M) $
- $ i\ \neq\ j $ ならば $ A_i\ \neq\ A_j $ または $ B_i\ \neq\ B_j $ である。
- 入力は全て整数である。

### Sample Explanation 1

$ f(s,t,k)\ \neq\ 0 $ であるような $ s,t,k $ を以下に挙げます。 - $ k\ =\ 1 $ のとき：$ f(1,2,1)\ =\ 3,\ f(2,3,1)\ =\ 2 $ - $ k\ =\ 2 $ のとき：$ f(1,2,2)\ =\ 3,\ f(2,3,2)\ =\ 2,\ f(1,3,2)\ =\ 5 $ - $ k\ =\ 3 $ のとき：$ f(1,2,3)\ =\ 3,\ f(2,3,3)\ =\ 2,\ f(1,3,3)\ =\ 5 $

### Sample Explanation 2

全ての $ s,t,k $ に対して $ f(s,t,k)\ =\ 0 $ です。

## 样例 #1

### 输入

```
3 2
1 2 3
2 3 2```

### 输出

```
25```

## 样例 #2

### 输入

```
3 0```

### 输出

```
0```

## 样例 #3

### 输入

```
5 20
1 2 6
1 3 10
1 4 4
1 5 1
2 1 5
2 3 9
2 4 8
2 5 6
3 1 5
3 2 1
3 4 7
3 5 9
4 1 4
4 2 6
4 3 4
4 5 8
5 1 2
5 2 5
5 3 6
5 4 5```

### 输出

```
517```

# 题解

## 作者：Yamchip (赞：4)

## 思路
既然是要求多源最短路，可以使用 Floyd。$n \le 400$ 的范围 Floyd 可以轻松跑过。状态转移方程：$f_{k,i,j}=\min(f_{k-1,i,j},f_{k-1,i,k}+f_{k-1,k,j})$，发现这不就是没有滚动数组的 Floyd 吗。回想 Floyd 转移方程的含义：只允许经过节点 $1$ 到 $k$ 的，节点 $i$ 到结点 $j$ 的最短距离。这不就是题目要求的，带进去跑一遍即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, dp[405][405][405];
long long ans;//不开__见祖宗
int main()
{
    cin >> n >> m;
    memset(dp, 0x3f, sizeof dp);
    for(int i = 1, u, v, w;i <= m;i++)
    {
        cin >> u >> v >> w;
        dp[0][u][v] = w;
    }
    for(int i = 0;i <= n;i++)
        for(int j = 1;j <= n;j++)
            dp[i][j][j] = 0;
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                dp[k][i][j] = min(dp[k - 1][i][j], dp[k - 1][i][k] + dp[k - 1][k][j]);
    for(int k = 1;k <= n;k++)
	    for(int i = 1;i <= n;i++)
	        for(int j = 1;j <= n;j++)
	            ans += 1ll * dp[k][i][j] * (dp[k][i][j] < 0x3f3f3f3f);
    cout << ans;
    return 0;
}
```

#### 一些别的
今天是除夕，祝大家新年快乐。

---

## 作者：403notfound (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc208_d)
## 思路
一道很简单的弗洛伊德，详见 [oi-wiki](https://oi-wiki.org/graph/shortest-path/#floyd-%E7%AE%97%E6%B3%95)。
### 定义状态
我们定义状态 $f_{x,y,k}$ 为在结点 $1$ 到 $k$，的子图中，结点 $x$ 到 $y$ 的最短路长度。可以发现，$f_{x,y,n}$ 为 $x$ 到 $y$ 的最短路长度。
### 转移与初始化
需要注意的是本题算的是最短路，所以答案数组应该初始化为极大值。我们又发现，因为此题为正图，所以自己到自己的最短路为零。

考虑转移，可以得到状态转移方程 $f_{x,y,k}=\min(f_{x,y,k-1},f_{x,k,k-1}+f_{k,y,k-1})$。

然后统计答案时无法走到的两点的答案的值会为初始值，所以需要特判这种情况。
## 代码
```cpp
#include <vector>
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define fi first
#define se second
using namespace std;
ll const N = 405 , M = 0x3f3f3f3f3f3f;
ll n , m , f[N][N][N] , ans;
signed main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	memset(f , 0x3f , sizeof(f));//初始化
	for (int i = 1 , u , v , w;i <= m;i++){
		cin >> u >> v >> w;
		f[u][v][0] = w;//单向图
	}
	for (int i = 1;i <= n;i++) 
		for (int j = 0;j <= n;j++) f[i][i][j] = 0;//自己到自己的最短路为0。
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
				f[i][j][k] = min(f[i][k][k - 1] + f[k][j][k - 1] , f[i][j][k - 1]);
 	//floyd模板
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
					if (f[i][j][k] < M) ans += f[i][j][k];//统计答案
	cout << ans << "\n"; //输出
	return 0;
}
```

---

## 作者：Brilliant11001 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc208_d)

#### [更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18351944)

做完这道题后感觉对 Floyd 的理解更深了。

根据题面要求，设 $f(k, i, j)$ 表示从 $i$ 到 $j$ 的所有**只经过 $1\sim k$ 的点的所有路径的最短距离**。

很明显 $k$ 那一维是**阶段**，因为它描述了从 $i$ 到 $j$ 路径中的不同点，而我们就是根据这一条件来划分集合，这也是为什么 $k$ 必须放在最外层循环。

所以状态转移方程为：

$$f(k, i, j) = \min\limits_{1\le i,j\le n}\{f(k - 1, i, k) + f(k - 1, k, j)\}$$

由于第 $k$ 层只会用到第 $k - 1$ 层的状态，所以可以加滚动数组优化。

和背包的状态转移方程就相似，还可以直接将这一维省去，因为在外层循环到 $k$ 时，$f(i, k)$ 恰好等于 $f(k - 1, i, k)$，$f(k, j)$ 同理。

再特判一个走不到的情况，即 $f(k, i, j) = \infty$，然后全加起来就好了。

时间复杂度为 $O(n^3)$。

$\texttt{Code:}$

```cpp
#include <iostream>

using namespace std;

const int N = 410, inf = 0x3f3f3f3f;
int n, m;
int g[N][N];
long long res;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i != j) g[i][j] = inf;
    int a, b, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        g[a][b] = min(g[a][b], w); //防重边
    }
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                if(g[i][j] < inf) res += g[i][j];
            }
    printf("%lld", res);

    return 0;
}
```

---

## 作者：__Creeper__ (赞：3)

## 思路

这道题是要求多源最短路，可以使用 [Floyd](https://oi-wiki.org/graph/shortest-path/#floyd-%E7%AE%97%E6%B3%95)，$n \le 400$ 的范围 $O(n^3)$ 的时间复杂度可以通过。

定义 $dis_{i,j}$ 表示点 $i$ 到点$j$ 的最小距离，循环枚举中间点 $k$，这里的 $k$ 就等于题目当中的 $k$，因为小于等于 $k$ 的所有点都被当作过中间点转移过，而大于 $k$ 的所有点都没有被当作过中间点转移过，直接用 Floyd 就可以了。

- 状态转移：$dis_{i,j} = \min (dis_{i,j},dis_{i,k}+dis_{k,j})$ 

注意：一定要**特判 $i = j$** 的情况。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 405;
int dis[N][N];

signed main() 
{
	memset ( dis, 0x3f, sizeof ( dis ) );
	int n, m;
	cin >> n >> m;
	for ( int i = 1; i <= m; i++ ) 
	{
		int u, v, w;
		cin >> u >> v >> w;
		dis[u][v] = w;
	}
	int ans = 0;
	for ( int k = 1; k <= n; k++ ) 
	{
		for ( int i = 1; i <= n; i++ ) 
		{
			for ( int j = 1; j <= n; j++ ) 
			{
				dis[i][j] = min ( dis[i][j], dis[i][k] + dis[k][j] );
				if ( dis[i][j] < 1e16 ) ans += dis[i][j];
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：2020luke (赞：2)

# [[ABC208D] Shortest Path Queries 2](https://www.luogu.com.cn/problem/AT_abc208_d) 题解

## 思路解析

此题的本质其实就是 Floyd。我们在进行 Floyd 时会有一个 $k$ 充当中间点，可见这里的 $k$ 就等于题目当中的 $k$，因为小于等于 $k$ 的所有点都被当作过中间点转移过，而大于 $k$ 的所有点都没有被当作过中间点转移过，于是直接进行 Floyd 即可。

**一定要记得特判 Floyd 中 $i=j$ 的情况。**

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 410;
int n, m, f[N][N];
signed main() {
	memset(f, 0x3f, sizeof(f));
	cin >> n >> m;
	for(int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w;
		f[u][v] = w;
	}
	int ans = 0;
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(i != j) {
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
					if(f[i][j] < 1e16) ans += f[i][j];
				}
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Swirl (赞：1)

> Floyd。

$n \le 400$，可以跑一个全源最短路。

首先，写出一个 Floyd 的代码：

```cpp
for (int k = 1; k <= n; k++) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
	}
}
```

我们知道，第一层循环代表经过的点，第二层循环代表起点，第三层循环代表终点。

而对于循环中每一个 $(k, i, j)$，$g_{i, j}$ 代表从 $i$ 到 $j$ 的路径中，只经过编号为 $1$ 到 $k$ 的点的最短路。

这不正好符合题目中 $f(i, j, k)$ 的定义吗？

故，我们把所有的 $g_{i, j}$ 统计一下即可。

```cpp
void chmin(int& x, int c) {
	x = min(x, c);
}
namespace zqh {
	const int N = 405;

	int n, m;
	int g[N][N];

	void init() {
		cin >> n >> m;
		memset(g, 0x3f, sizeof g);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			g[u][v] = w;
		}
		for (int i = 1; i <= n; i++) {
			g[i][i] = 0;
		}
	}

	void solve() {
		int ans = 0;
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					chmin(g[i][j], g[i][k] + g[k][j]);
					ans += (g[i][j] == 0x3f3f3f3f3f3f3f3f ? 0 : g[i][j]);
				}
			}
		}
		cout << ans;
	}

	void main() {
		init();
		solve();
	}
}  // namespace zqh
```

---

## 作者：littlebug (赞：1)

## Solution

设 $i \to j$ 为 $i,j$ 之间的最短路。

题目说要计算只使用 $1 \sim k$ 中的点时，$i,j$ 之间的最短路，我们很容易可以想到 Floyd 求全源最短路的算法，因为 Floyd 算法是通过对于每个点 $k$，依次枚举 $i,j$，判断 $i \to j$ 是否可以通过 $i \to k$ 加上 $k \to j$ 来更新。所以答案所求的最短路就是在 Floyd 过程中每次更新后的 $dis_{i,j}$ 呀！

需要注意的是，当 $i=j$ 的时候，$dis_{i,j}=0$，所以这时需要跳过循环。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define il inline
using namespace std;
const int MAXN=400+5;
int n,m;
int dis[MAXN][MAXN],ans=0;
il void floyd()
{
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				if(i==j) continue;
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				if(dis[i][j]<1e15) ans+=dis[i][j];
			}
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	memset(dis,0x3f,sizeof(dis));
	int u,v,w;
	for(int i=1;i<=m;++i)
	{
		cin>>u>>v>>w;
		dis[u][v]=w;
	}
	floyd();
	cout<<ans;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[D - Shortest Path Queries 2](https://atcoder.jp/contests/abc208/tasks/abc208_d)

考虑设 $f_{i,j,k}$ 为只经过 $i,j$ 及 $1\sim k$ 中的点，从点 $i$ 到点 $j$ 的最短路径长度。

想到使用 Floyd 求解，考虑外层枚举 $k$ 进行转移，容易得到：
$$f_{i,j,k}=\min(f_{i,j,k-1},f_{i,k,k-1}+f_{k,j,k-1})$$

统计答案的时候枚举 $i,j,k$ 即可，判断 $f_{i,j,k}$ 是否是初值，如果不是，答案加上 $f_{i,j,k}$。

[完整代码](https://atcoder.jp/contests/abc208/submissions/54659638)，时间复杂度 $O(n^3)$。

---

## 作者：Expert_Dream (赞：1)

先看数据范围，哦？$n \le 400$，这显然给 $O(n^3)$ 开的友好数据范围！！！

由于是最短路，想到 Floyd，如果你只知道他的转移公式是 $dis_{i,j} = dis_{i,k} + dis_{k,j}$ 的话，并且只会在最短路题里偷懒，那你真的没有学 Floyd。我们想想他的本质是啥？

显然，那个 $k$ 是**新加入进来**的节点，然后所有 $i$ 和 $j$ 都会经过 $k$ 做一条线段，更新他们的最短路。

那么，你可以做这一题了，所以你会发现，哎呀，这题求得不就是我们每一个转移方程的累加和吗？对的没错！！

所以在跑 Floyd 的时候记录 $sum$ 即可。

[link](https://atcoder.jp/contests/abc208/submissions/51964217)。

---

## 作者：zk_y (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc208_d)

简单的 ``Floyd``，我们只需要在原有 ``dis`` 数组的基础上，加上一维就可以了。


但是，在统计答案的时候，我们需要特判两个点是否不是相互连通就可以了。

# AC 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long F[405][405][405],n,m,u,v,w,ans;
int main(){
	cin>>n>>m;
	memset(F,0x3f3f3f3f,sizeof(F));
    	//初始化
	while(m--){
		cin>>u>>v>>w;
		F[0][u][v]=w;
	} 
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			F[i][j][j]=0;
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				F[k][i][j]=min(F[k-1][i][j],F[k-1][i][k]+F[k-1][k][j]);//状态转移方程
			}
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans+=(F[k][i][j]>=0x3f3f3f3f?0:F[k][i][j]);
			}
		}
	}		
	cout<<ans;	
    return 0;
}
```

---

## 作者：World_Creater (赞：1)

小清新 $\verb!Floyd!$ 题，如果了解 $\verb!Floyd!$ 的本质 $1\min$ 就可以看出做法。

假定我们不会 $\verb!Floyd!$。

观察到数据范围允许 $O(n^3)$，我们不妨将状态设计的暴力一些：

令 $f_{k,i,j}$ 表示从 $i$ 到 $j$ 只经过 $1\sim k$ 点的最短路径。

我们有转移：$f_{k,i,j}=\min(f_{k-1,i,j},f_{k-1,i,k}+f_{k-1,k,j})$，即：要么继承上一层，要么以新的节点作为中转点作为最短路。

你会发现这个跟 $\verb!Floyd!$ 长的很像，不，就是一模一样。

$\verb!Floyd!$ 算法的本质就是利用上面的转移实现最短路，只不过在实际实现中，为了节省算法空间，将第一维滚掉了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
int f[405][405][405],ans;
int n,m;
signed main()
{
	memset(f,0x3f,sizeof(f));//初始无限（无法到达）
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		f[0][u][v]=w;
	}
	for(int i=0;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			f[i][j][j]=0;//自己到自己是0
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				f[k][i][j]=min(f[k-1][i][j],f[k-1][i][k]+f[k-1][k][j]);
			}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if(f[k][i][j]>=inf) continue ;
				ans+=f[k][i][j];
			}
	cout<<ans;
}
```

---

## 作者：zhanghaosong (赞：1)

# AT_abc208_d [ABC208D] Shortest Path Queries 2 题解

### 修正

之前的代码无法通过本题，原因是没开 `long long`。在此致歉。

### 思路

对于 $n\leq 400$ 的数据范围，发现 $O(n^3)$ 的数据范围可以优雅地通过本题（本题时限 $3$ 秒）。

发现这是一道最短路算法，而且是求多源最短路，那么我们不用跑 $n$ 遍 $\textsf{Dijkstra}$，而是直接跑一边 $\textsf{Floyd}$ 即可，时间复杂度符合要求。

开一个三维的数组，空间会超吗？

经过计算，是不会的。因为空间限制是 $\textsf{1.00GB}$。实测最大 $\textsf{510.38MB}$。

### 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long F[405][405][405],n,m,u,v,w,ans; //开 long long 呀
//F[i][j][k] 代表途径 i 个节点，从 j 到 k 的最短路
int main(){
	cin>>n>>m;
	memset(F,0x3f3f3f3f,sizeof(F)); //初始化一个非常大的数 
	while(m--){
		cin>>u>>v>>w;
		F[0][u][v]=w; //根据输入赋值 
	} 
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			F[i][j][j]=0; //自己指向自己的赋值为0 
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				F[k][i][j]=min(F[k-1][i][j],F[k-1][i][k]+F[k-1][k][j]); //状态转移方程 
			}
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans+=(F[k][i][j]>=0x3f3f3f3f?0:F[k][i][j]);
			}
		}
	}		
	cout<<ans;	
return 0;
}
```

### 题外话

今天洛谷的 RMJ 非常稳定，交了好多题。

---

## 作者：Stars_visitor_tyw (赞：0)

## 题解：AT_abc208_d [ABC208D] Shortest Path Queries 2
### 分析
良心题。

观察到数据范围不大，考虑使用 Floyd。

在写 Floyd 的时候要枚举一个中转点 $k$，正好就对应题面的 $k$，因为 $k$ 的定义是转移 $i$ 和 $j$ 的最短路是要经过的点。

思路就很明确了，定义一个三维的 $dis$ 数组，其中多的一维表示只经过点 $1$ 到点 $k$ 以及 $i$ 和 $j$。

状态转移：$dp_{k,i,j}=\min(dp_{k-1,i,j},dp_{k-1,i,k}+dp_{k-1,k,j})$。

初始除了给定的边和自己到自己的情况其他全部赋最大值。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dis[405][405][405], n, m, ans;
signed main()
{
    memset(dis,0x3f,sizeof dis);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        dis[0][u][v]=w;
    }
    for(int j=0;j<=n;j++)for(int i=1;i<=n;i++)dis[j][i][i]=0;
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                dis[k][i][j]=min(dis[k-1][i][j],dis[k-1][i][k]+dis[k-1][k][j]);
//                cout<<dis[k][i][j]<<"\n";
                if(dis[k][i][j]<1e16)ans+=dis[k][i][j];
            }
        }
    }
    cout<<ans;
    
}

---

## 作者：pengzy (赞：0)

### 题意
给定 $m$ 条有向边，对于每两个点，求出它们分别经过前 $k$ 个点的最短路总和。

### 思路
看到题目，显然要让我们求的是全源最短路，再看看数据范围，可以用 Floyed 求解。

在 Floyed 算法中，我们枚举中间点 $k$，用 $n$ 个 $k$ 点去更新每两点间的距离。$dis_{u,v,k}$ 代表经过前 $k$ 个点更新出来的 $u$ 到 $v$ 的最短路，正好和题意相符。

每次更新完，距离小于初始化的最大值，就是可以到达的，记录答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Max=410+10,inf=1e18;
int n,m,dis[Max][Max],ans;
signed main()
{
	memset(dis,0x3f,sizeof(dis));
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int u,v,w;cin>>u>>v>>w;
		dis[u][v]=w;
	}
	for(int i=1;i<=n;i++)
		dis[i][i]=0;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) {
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				if(dis[i][j]<1e18)ans+=dis[i][j];
			}
	cout<<ans;
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# AT_abc208_d [ABC208D] Shortest Path Queries 2 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc208_d)

### 思路

这道题看数据时，发现数据范围特别小，即使时间复杂度比较高也能通过。

然后又发现这是一道图论题目，由此我们自然联想到了 $ \texttt {Floyd}$。

想看板子的点[这里](https://www.luogu.com.cn/paste/ir07w4dx)。

所以我们只需要按这个板子，再进行一些初始化即可。

首先，应该把每条不指向自己的边标记为无穷，这样在后续的计算中不至于因取最小值导致错误（因为上一篇题解就这么挂了）。

然后再把每一条指向自己的边标记为 $0$。

接着套用板子进行计算。

最后判断如果能到达就输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
long long n,m,f[405][405][405],u,v,l,ans;
int main(){
	memset(f,0x3f,sizeof(f));
	cin>>n>>m;
	while(m--){
		cin>>u>>v>>l;
		f[0][u][v]=l;//标记有一条从u到v的路边权为l
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++)f[i][j][j]=0;//自己到自己边权为0
	}
	for(int k=1;k<=n;k++){
		for(int x=1;x<=n;x++){
			for(int y=1;y<=n;y++){
				f[k][x][y]=min(f[k-1][x][y],f[k-1][x][k]+f[k-1][k][y]);//板子
			}
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[k][i][j]<inf)ans+=f[k][i][j];//即如果能到达
			}
		}
	}
	cout<<ans;
	return 0;
}
```

### 附录

$2023.9.16$ 修正因初始化不为无穷的错误。

---

