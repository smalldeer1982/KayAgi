# 最短 Hamilton 路径

## 题目描述

给定一张 $n$ 个点的带权无向图，点从 $0 \sim n-1$ 标号，求起点 $0$ 到终点 $n-1$ 的最短 Hamilton 路径。 

Hamilton 路径的定义是从 $0$ 到 $n-1$ 不重不漏地经过每个点恰好一次。

## 说明/提示

对于所有测试数据满足 $1 \le n \le 20$，$0 \le a[i,j] \le 10^7$

## 样例 #1

### 输入

```
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0```

### 输出

```
18```

# 题解

## 作者：Atserckcn (赞：35)

## [P10447 最短 Hamilton 路径](https://www.luogu.com.cn/problem/P10447) 题解

### 分析题目：

一张 $n$ 个点的带权无向图，求起点 $0$ 至终点 $n-1$ 的最短 Hamilton 路径（从 $0\sim n-1$ 不重复地经过每个点一次）。

初看题目，不难发现这道题是一个**状态压缩 dp** 的模板题。

#### 状态压缩简介：

状态压缩，字面意思就是把复杂的状态转化成简洁的**二进制**来表示，可减少时间与空间复杂度。

打个比方，二进制数 $01001101$ 表示的意思为：

$0$（$0$ 号节点没有被经过）$1$（$1$ 号节点已被经过）$00$（$2,3$ 号节点未经过）$11$（$4,5$ 号节点经过）$0$（$6$ 号节点没经过）$1$（$7$ 号节点已经过）。

而 $(01001101)_2=(77)_{10}$，我们只需操作 $77$ 次即可，简洁明了。

分析题目样例：

```
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0
```

可作图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0utyu6u7.png)

好啦，分析题目，我们不难想出定义一个 $f$ 数组，$f_{i,j}$ 表示在 $i$ 的状态下（上文已提到）最后经过的节点 $j$ 所得的最短 Hamilton 路径。

定义：
```cpp
int f[MAXM][MAXN];
```

那么我们该如何进行**状态转移**呢？

我们可以用三层循环来实现：

```cpp 
for(int i=1;i<(1<<n);i++)//枚举状态
	{
		for(int j=0;j<n;j++)//枚举每个点
		{
			if(!((i>>j)&1)) continue;//如果点j已经被经历过，就跳过它
			for(int k=0;k<n;k++)//这里比较难想，意思是在i的状态下已被经过的点的个数
				if(((i^(1<<j))>>k)&1)
					f[i][j]=min(f[i][j],f[i^(1<<j)][k]+a[k][j]);//状态转移方程，要么是本身，要么则为以i^(1<<j)为状态的节点k到j，有点类似最短路的floyd
		}
	}
```

最后我们的答案就是 $f_{2^{n}-1 , n-1}$。

即在状态为 $2^{n}-1$（全被经过了）下的 $n-1$ 号节点。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=25,MAXM=(1<<20),inf=0x3f;//定义变量，inf为无限
int n,a[MAXN][MAXN],f[MAXM][MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
   	//输入无需多嘴
	memset(f,inf,sizeof(f));//一开始f数组都是无限的
	f[1][0]=0;//还没开始旅程，为0
	for(int i=1;i<(1<<n);i++)//枚举状态
	{
		for(int j=0;j<n;j++)//枚举每个点
		{
			if(!((i>>j)&1)) continue;//经过了
			for(int k=0;k<n;k++)//上一次经过了哪些点？
				if(((i^(1<<j))>>k)&1)//枚举从上一个经过的节点走到j节点
					f[i][j]=min(f[i][j],f[i^(1<<j)][k]+a[k][j]);//状态转移
		}
	}
	printf("%d\n",f[(1<<n)-1][n-1]);//out
	return 0;
    //完结撒花
}
```

### [AC 记录](https://www.luogu.com.cn/record/159158680)

---

## 作者：残阳如血 (赞：22)

## $\textbf{Description}$
给定一张 $n$ 个点的带权无向完全图，求出从 $0$ 到 $n-1$ 经过每个点恰好一次的最短路径。
## $\textbf{Solution}$
### $\textbf{Brute Force}$
考虑最朴素的做法。

由于每个点只能经过一次，所以可以枚举 $n$ 个点的**全排列**。对于每个全排列，遍历每个点，计算路径长度。最后找到最短的路径长度即可。

时间复杂度：$O(n\cdot n!)$，$20!$ 铁定是会 TLE 的。
### $\textbf{DP}$
$n\le20$ 的数据范围，除了搜索，指数级别的算法也是可以的。可以考虑**状态压缩 DP**。

- 无后效性：每个点只能经过一次，后面的状态不会影响前面的状态；
- 最优子结构：每个状态的转移都是类似的，都是从前一个状态加上边权得到现有状态。

> 考虑已经经过了一些点到达了节点 $u$，现在再走一个点到达 $v$。由于每个点只能经过一次，我们不可避免地要关心每个点是否经过。但是与暴力做法相比，经过了这些点之后，就不再关心这些点经过的顺序。

#### 状态表示
首先，我们要在任何时刻都可以表示已经经过了哪些点。可以使用一个 $n$ 位二进制数 $S$，第 $i\,(0\le i<n)$ 位为 $1$ 则表示这个点已经经过，为 $0$ 则表示这个点尚未经过。

仅仅这样一个二进制数够了吗？假如已经知道通过的点集为 $S$，枚举了下一个点，但是无法得知是从哪个点过来的。

所以，我们还需要记录最后一个经过的点 $v$。

综上所述，状态标识为 $f(S,v)$，表示已经通过了 $S$ 中为 $1$ 的点，且最后一个点（当前所在的点）为 $v$。

#### 状态转移
显然，最外层循环要枚举 $S$，然后第二层循环枚举 $v$。然后需要进行一个特判。$v$ 是已经经过了的，但是如果 $S$ 中的第 $v$ 位为 $0$（即表示还没有经过），这是不合逻辑的，需要跳过。

现在，我们想要得到 $f(S,v)$ 的值。$v$ 是最后经过的点，那么我们需要知道，$v$ 是从哪个点过来的。所以可以在 $S$ 内枚举点 $u$，表示 $u\to v$。当然，可以特判 $u\not=v$，但是本题中保证 $u\to u$ 的边权为 $0$，所以可以不用判断。~~不判断比判断快了 0.2s。~~

接下来，$f(S,v)\gets f(S-\{v\},u)+g(u,v)$（$g(x,y)$ 表示 $x\to y$ 的边权），意义即为从没有经过 $v$ 的状态且最后一个点为 $u$，然后到达 $v$，此间路径长度增加了 $g(u,v)$。由于 $v\in S$，所以 $S-\{v\}$ 可以写成 `S-(1<<v)`。
![](https://cdn.luogu.com.cn/upload/image_hosting/oxp69wcc.png)
综上所述，
$$
f(S,v)=\min\limits_{u\in S}\Big(f(S-\{v\},u)+g(u,v)\Big)
$$
#### 初始化
开始时 $f$ 赋值为 $+\infty$，但是 $f(1,0)\gets0$。因为初始在 $0$ 点，$S_{(2)}=000\cdots01_{(2)}=1_{(10)}$，$v=0$，此时的路径长度为 $0$。
#### 转移细节
首先，$S\sub T$ 这一偏序关系被 $S<T$ 包含，所以可以从小到大枚举每一个 $S$。

$S$ 枚举要从 $0\sim2^n-1$ 吗？当然，结果为 $2^n-1$ 是确定的，但是从哪里开始呢？

- $S=0_{(10)}$：$v$ 一个值也找不到，没用；
- $S=1_{(10)}$：初始化过了，没用；
- $2\,|\,S_{(10)}$：$S_{(2)}=\cdots0_{(2)}$，$0$ 号点未经过，没用。

所以最外层循环可以这样写：`for (int S = 3; S < 1 << n; S += 2)`，比 `++S` 快了许多。
#### 结果
要通过每个点恰好一次并且最后到达点 $n-1$，所以 $S=\underbrace{111\cdots111}_{n\text{个}1}$，$v=n-1$。
#### 时空复杂度：
- 时间复杂度：$O(n^2\cdot2^n)$；
- 空间复杂度：$O(n\cdot2^n)$。
## $\textbf{Code}$
```c++
#include <vector>
#include <cstring>
#include <iostream>
#define min(a,b) ((a)<(b)?(a):(b))

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  int n; std::cin >> n;
  std::vector<std::vector<int>> g(n, std::vector<int>(n));
  std::vector<std::vector<int>> f(1 << n, std::vector<int>(n, 2e9)); // 初始值赋为每个元素为 +∞
  // f[S][i] 表示经过了 S 中为 1 的点，且最后一个点为 i 的最短路径
  for (auto &x : g) for (auto &y : x) std::cin >> y; // 读入边权
  f[1][0] = 0; // 初始化
  for (int S = 3; S < 1 << n; S += 2) // 加速优化
    for (int v = 1; v < n; ++v) if (S >> v & 1) // v ∈ S 时转移
      for (int u = 0; u < n; ++u)
        if (S >> u & 1) f[S][v] = min(f[S][v], f[S - (1 << v)][u] + g[u][v]); // u ∈ S 时转移
  std::cout << f[(1 << n) - 1][n - 1] << std::endl; // 最终结果。(1<<n)-1 就是 n 个 1 的二进制数
  return 0;
}
```
### $\textbf{Update}$
- Upd on 2024.6.23：修改了一处笔误。

---

## 作者：LostKeyToReach (赞：7)

这道题似乎是从 Acwing 搬过来的，我介绍一下蓝书上的做法。

如过直接枚举全排列并暴力计算，那么时间复杂度为 $O(n  \times n!)$，无法通过此题，但我们可以用状态压缩动态规划通过此题。

可以发现，我们可以用 $n$ 位二进制数来表示哪些点走过，$0$ 表示没走，$1$ 表示走了。$2^n-1$ 用二进制表示正好全是 $1$，可以表示已经走完了。

那么我们可以用 $f_{i,j}$ 表示经过 $i$ 集合的所有点且到 $j$ 点的最短 Hamilton 路径，不难得到这个状态转移方程：

$$
f_{i,j}=\min_{0 \le k \le n-1} f_{i \oplus 2^j,k}+dis_{k,j}
$$

初始赋值：$f_{1,0}=0$，其余为正无穷。

目标：$f_{2^n-1,n-1}$。

时间复杂度：$O(n^2 \times 2^n)$。

代码如下：

```cpp
int dis[23][23];
int f[1 << 21][21];
int n;
int main() {
	read(n);
	rep(i, 0, n - 1, 1) {
		rep(j, 0, n - 1, 1) {
			read(dis[i][j]);
		}
	}
	rep(i, 0, (1 << n) - 1, 1) {
		rep(j, 0, n - 1, 1) {
			f[i][j] = 0x3f3f3f3f3f3f;
		}
	}
	f[1][0] = 0;
	rep(i, 1, (1 << n) - 1, 1) {
		rep(j, 0, n - 1, 1) {
			if (i >> j & 1) {
				rep(k, 0, n - 1, 1) {
					if (i ^ (1 << j) >> k & 1) {
						f[i][j] = min(f[i][j], f[i ^ (1 << j)][k] + dis[k][j]);
					}
				}
			}
		}
	}
	writeln(f[(1 << n) - 1][n - 1]);
}
```

这份程序跑了 $685$ 毫秒，有没有继续优化的余地呢？有。

可以发现，我们在枚举 $i$ 的过程中，有些 $i$ 的最低位为 $0$，代表没有走过，所以我们可以进一步优化，排除所有 $i$ 最低位为 $0$ 的情况，这样程序跑得飞快，只需 $417$ 毫秒。

代码如下：

```cpp
int dis[23][23];
int f[1 << 21][21];
int n;
int main() {
	read(n);
	rep(i, 0, n - 1, 1) {
		rep(j, 0, n - 1, 1) {
			read(dis[i][j]);
		}
	}
	rep(i, 0, (1 << n) - 1, 1) {
		rep(j, 0, n - 1, 1) {
			f[i][j] = 0x3f3f3f3f3f3f;
		}
	}
	f[1][0] = 0;
	rep(i, 1, (1 << n) - 1, 1) {
		if (i & 1) {
			rep(j, 0, n - 1, 1) {
				if (i >> j & 1) {
					rep(k, 0, n - 1, 1) {
						if (i ^ (1 << j) >> k & 1) {
							f[i][j] = min(f[i][j], f[i ^ (1 << j)][k] + dis[k][j]);
						}
					}
				}
			}
		}
	}
	writeln(f[(1 << n) - 1][n - 1]);
}
```

---

## 作者：Stars_visitor_tyw (赞：7)

## P10447 最短 Hamilton 路径 题解
### 分析
状压模板题。终于上线状压模板题了！

用普通 $dp$ 做显然不行，因为你无法知道当前走过了哪几个点。很容易就想到状压。


状态：$dp_{i,j}$ 表示到达点 $j$，且目前经过的所有点的状态为二进制下的 $i$ 时最小边权和。

答案为 $dp_{2^{n-1},n-1}$。

状态转移：枚举二进制经过的点的状态，枚举当前位置 $j$，枚举上一个位置 $j$，则上一步状态为 $dp_{i \oplus 2^j,k}$。再加上 $w_{k,j}$ 取最小值即可。

初始状态：$dp_{1,0}=0$，其余极大值。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, dp[1<<20][25], w[25][25];
void work()
{
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
		{
			if((i>>j)&1)
			{
				for(int k=0;k<n;k++)
				{
					if((i>>k)&1)
					{
						dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+w[k][j]);
					}
				}
			}
		}
	}
}
signed main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			int k;
			cin>>k;
			w[i][j]=k;
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[1][0]=0;
	work();
	cout<<dp[(1<<n)-1][n-1];
}
```

---

## 作者：August_Light (赞：3)

# P10447 最短 Hamilton 路径 题解

[题目传送门](https://www.luogu.com.cn/problem/P10447)

题意：给定一张有向带权图（$n \le 20$）求点 $0$ 到点 $n-1$ 的最短哈密顿路径。

这是一道状压 DP 模板题。在状态压缩 DP 中，我们将一个集合压成一个二进制数。

设 $f_{u,i}$ 为已经走了集合 $u$ 中的节点，且现在在点 $i$ 的最短路。枚举路径上 $i$ 的前一个点 $j$ 进行转移。

时间复杂度 $O(n^2 2^n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

template<typename T>
void cmin(T &x, T y) {
    x = min(x, y);
}

const int N = 20;

int n;
int dis[N][N];

int f[1 << N][N];

int main() { ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dis[i][j];

    uint tot = (1 << n) - 1;
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    for (uint u = 0; u <= tot; u++)
        for (int i = 0; i < n; i++)
            if (u & (1 << i))
                for (int j = 0; j < n; j++)
                    if ((u ^ (1 << i)) & (1 << j))
                        cmin(f[u][i], f[u ^ (1 << i)][j] + dis[j][i]);
    cout << f[tot][n-1] << endl;
    return 0;
}
```

---

## 作者：PineappleSummer (赞：2)

[Problem](https://www.luogu.com.cn/problem/P10447)

算阶上的状压 DP 例题。

状压 DP 一般数据在 $20$ 左右，还是容易看出来的。

默认从 $1\sim n$ 标号。

设 $dp_{i,s}$ 为走了 $s$ 这个集合中的点，且最后走到的点为 $i$ 的最短长度。对于 $i$，可以枚举上一个走到的点进行转移。

枚举每个状态复杂度为 $O(2^n)$，枚举每个 $i$ 与上一个经过的点 $j$ 进行转移所需复杂度为 $O(n^2)$，总复杂度 $O(n^22^n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 22;
int n, m, a[N][N], dp[N][1 << N];
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	memset (dp, 0x3f, sizeof dp);
	dp[1][1] = 0; // 初始在第 1 个点长度为 0
	for (int mask = 2; mask < (1 << n); mask++) {
		for (int i = 1; i <= n; i++) {
			if (mask & (1 << (i - 1))) {
				for (int j = 1; j <= n; j++)
					if ((mask & (1 << (j - 1))) && i != j)
						dp[i][mask] = min (dp[i][mask], dp[j][mask - (1 << (i - 1))] + a[j][i]); // 从上一个点进行转移
			}
		}
	}
	cout << dp[n][(1 << n) - 1];
	return 0;
}
```

---

## 作者：huangzixi071018 (赞：1)

# 题目大意：
给定一张 $n$ 个点的带权无向图，点 $0$ 到终点  $n-1$ 的最短路径，这条路径要经过每一个点。

# 思路：
可以使用状压 $dp$ 求解，定义 $dp(i,j)$ 为第 $i$ 种状态，如二进制 $101$ 表示走了 $0$ 号和 $3$ 号点，$j$ 表示以第 $j$ 个点为这条路的终点，所以 $i$ 中一定包含了 $j$ 结点。然后枚举转移的结点 $k$ ，判断 $k$ 是否在 $i$ 中，可以推出转移方程，如代码所示，最后输出即可。

# 代码：
因为本人喜欢从 $1$ 开始，所以代码和转移方程略有不同，但思路一样。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[1<<20][25],d[25][25];
int main(){
	memset(dp,0x3f,sizeof(dp));
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>d[i][j];
		}
	}
	dp[1][1]=0;
	for(int i=1;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(((i>>(j-1))&1)==0)continue;
			for(int k=1;k<=n;k++){
				if((i^(k>>(j-1))>>k&1)==0)continue;
				dp[i][j]=min(dp[i][j],dp[i-(1<<(j-1))][k]+d[j][k]);
			}
		}
	}
	cout<<dp[(1<<n)-1][n]<<"\n";
	return 0;
}
```

---

## 作者：Nightsky_Stars (赞：1)

# 思路：
状压 DP 求解即可，$dp_{i,j}$ 表示集合 $i$ 内最短的 Hamilton 路径，即从起点 $0$ 出发经过 $i$ 中的所有点，到达终点时的最短路径。让 $i$ 从最小的子集逐步扩展到整个图，最后得到的 $dp_{N,n-1}$ 就是答案，$N$ 表示包含图上所有点的集合。

如何求 $dp_{i,j}$？可以从小问题 $i-j$ 递推到大问题 $i$，其中 $i-j$ 表示从集合 $i$ 中去掉 $j$，即不包含 $j$ 点的集合。

如何从 $i-j$ 递推到 $i$？设 $k$ 为 $i-j$ 中的一个点，以 $k$ 为变量枚举 $i-j$ 中的所有点，找出最短路径。

而状态转移方程就为 $dp_{i,j}=\min(dp_{i-j,k}+d_{k,j},dp_{i,j})$。

# CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[1<<20][30],d[30][30];
int main(){
	cin>>n;
	memset(dp,0x3f3f,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>d[i][j];
		}
	}
	dp[1][0]=0;
	for(int i=1;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if(i&(1<<j)){
				for(int k=0;k<n;k++){
					if(((i^(1<<j))>>k)&1){
						dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+d[k][j]);
					}
				}
			}
		}
	}
	cout<<dp[(1<<n)-1][n-1]<<"\n";
	return 0;
}
```

---

## 作者：Jorisy (赞：1)

注意到 $n\le20$，容易想到状压 dp。

因为要经过所有点，因此记一个二进制状态 $i$，其中 $i$ 二进制的每一位表示每个节点当前是否已经经过。

然后我们设计状态 $f_{i,j}$ 表示走到节点 $j$ 且当前状态为 $i$ 的最短路长度。

于是，对于状态的转移，我们只要枚举下一个节点进行转移即可。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,g[25][25],f[2000005][25];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>g[i][j];
		}
	}
	memset(f,0x3f,sizeof(f));
	f[1][1]=0;//注意初值
	for(int i=2;i<(1<<n);i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!(i&(1<<j-1))) continue;//排除不合法状态
			for(int k=1;k<=n;k++)
			{
				if(j==k||!(i&(1<<k-1))) continue;
				f[i][j]=min(f[i][j],f[i^(1<<j-1)][k]+g[j][k]);//转移，根据题目条件可知 i->k 的代价必然小于 i->j->k
			}
		}
	}
	cout<<f[(1<<n)-1][n];
 	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

状压模板题。

设 $dp_{i,S}$ 为当前在 $i$，已经走了 $S$ 中的所有点的最长路。

那么，如何快速存储 $S$ 呢，因为 $S$ 是个 $01$ 串，而 C++ 中有许多针对二进制的符号，所以我们可以把 $01$ 串换成二进制存储。


接下来看转移，我们可以枚举与 $i$ 连着的边，设枚举到了 $j$，且 $j$ 不在 $S$ 中（即 $S\& 2^j=0$（$\&$ 表示按位与）），那么：

$$dp_{j,S\oplus2^j}=\max(dp_{j,S\oplus2^j},dp_{i,S}+dis_{i,j})$$

最终答案为 $dp_{n,2^n-1}$。

---

## 作者：niuzh (赞：0)

### 思路

由于 $n \le 20$，考虑使用状压 $dp$，令 $dp_{i,j}$ 为在 $i$ 这个集合中最后一个点为 $j$ 的最短 Hamilton 路径。然后枚举一个点 $k$，进行最短路的转移。

### 代码
```cpp
/*
 * @FilePath: test.cpp
 * @Author: niu-zh
 */
#include<bits/stdc++.h>
using namespace std;
const int N=30+10,M=1<<20;
int dp[1<<20][N],a[N][N];
int main()
{
	memset(dp,0x3f3f3f3f,sizeof(dp));
	int n;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cin>>a[i][j];
		}
	}
	dp[1][0]=0;
	for (int i=1; i<(1<<n); i++)
	{
		for (int j=0; j<n; j++)
		{
			if (i&(1<<j))//判断j是否在i里
			{
				for (int k=0; k<n; k++)
				{
					if (((i^(1<<j))>>k)&1)//判断k是否在i去除j里
					{
						dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+a[k][j]);
					}
				}
			}
		}
	}
	cout<<dp[(1<<n)-1][n-1]<<"\n";
	return 0;
}
```

---

## 作者：YuzhenQin (赞：0)

## 题意

给定一张 $n$ 个点的带权无向图，点从 $0 \sim n-1$ 标号，求起点 $0$ 到终点 $n-1$ 的最短 Hamilton 路径。 

Hamilton 路径的定义是从 $0$ 到 $n-1$ 不重不漏地经过每个点恰好一次。

## 做法

暴搜是 $ O(n!) $ 的，会爆炸。考虑状压DP，设 $dp[i][j]$ 为目前在 $j$ 号点，访问过的点的方案为 $i$ 的最小费用，其中 $i$ 是一个 $2^n$ 的状态。

每次枚举从起点和终点以及当前状态。注意边界和限制，当前状态是否与枚举的点冲突（起点没来过或者终点去过）。起点一定是 $0$，终点一定是 $n-1$。

每次加上边权转移即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

int a[20][20], f[1 << 20][20];

int main(void) {
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> a[i][j];

	memset(f, 0x3f, sizeof(f));
	f[1][0] = 0;
	for(int i = 0; i < 1 << n; i++)
		for(int j = 0; j < n; j++)
            if((i >> j) & 1)
			    for(int k = 0; k < n; k++)
                    if(((i ^ (1 << j)) >> k) & 1)
				        f[i][j] = min(f[i][j], f[i ^ (1 << j)][k] + a[k][j]);
		
	cout << f[(1 << n) - 1][n - 1] << endl;
	
	return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

状压 DP 模板题。

- 状态：$dp_{i,j}$ 表示当前经过的点的状态为二进制下的 $i$，且当前到达点 $j$ 的最短路径长度。

- 初始状态：$dp_{1,0}=0$，其余极大值。

- 状态转移：枚举点的状态 $i$，当前点 $j$ 和上一个点 $k$。考虑到达点 $k$ 时的情况，当时还没有到达点 $j$。状态转移方程为 $dp_{i,j}=\min(dp_{i,j},dp_{i\text{ xor }2^j,k}+dis_{k,j})$。

- 答案：所有点均已到达，答案为 $dp_{2^n-1,n-1}$。

注意，所有点的编号从 $0$ 开始，即 $0\dots n-1$。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 20;

int n, dis[N][N], dp[1 << N][N];

signed main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> dis[i][j];
	memset(dp, 0x3f, sizeof dp);
	dp[1][0] = 0;	
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
			if ((i >> j) & 1)
				for (int k = 0; k < n; k++)
					if ((i >> k) & 1)
						dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][k] + dis[k][j]);
	cout << dp[(1 << n) - 1][n - 1];
	return 0;
}
```

---

## 作者：Tomle (赞：0)

# P10447 题解

状态压缩 dp，像是 [吃奶酪](/problem/P1433) 的数据加强版。

老套路，$f_{u, v}$ 表示走过了集合 $u$，终点为 $v$。如果 $v \notin u$ 则无意义。

转移：$f_{u, v} = \min\limits_{k \in u, k \ne v}\{f_{u-k,k}+dis_{k,v}\}$。

时间复杂度 $\mathcal{O}(n^22^n)$。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[25][25], f[(1 << 20) + 5][21];

int main() {
	memset(f, 0x3f , sizeof(f));
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}
	f[1][1] = 0;
	for (int i = 2; i < (1 << n); ++i) {
		for (int j = 1; j <= n; j++) {
			if (!(i >> j - 1 & 1)) continue;
			for (int k = 1; k <= n; k++) {
				if (!(i >> k - 1 & 1) || j == k) continue;
				f[i][j] = min(f[i][j], f[i ^ (1 << j - 1)][k] + a[k][j]);
			}
		}
	}
	cout << f[(1 << n) - 1][n];
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

设 $f_{i,j}$ 表示当前走过了 $i$ 集合中的所有的点，当前最后一个节点为 $j$，最短的 Hamilton 路径的长度是多少。容易发现答案为 $f_{2^n-1,n-1}$，初始条件为 $f_{2^0=1,0}=0$。

然后对于每一个状态 $f_{i,j}$，枚举一个新结点 $k$ 满足 $k\not\in i$，并通过 $f_{i,j}+\text{Dis}_{j,k}$ 来更新 $f_{i\operatorname{or} 2^k,k}$ 的值即可。其中 $\text{Dis}_{i,j}$ 表示从 $i$ 到 $j$ 的最短路长度，可以用一遍 Floyd 来预处理出。

时间复杂度为 $O(2^n\times n^2)$。

```cpp
int f[(1ll << 20) + 10][21], mp[21][21];
void $() {
    int n;
    cin >> n;
    F(i, 1, n) {
        F(j, 1, n) {
            cin >> mp[i][j];
        }
    }
    F(k, 1, n) {
        F(i, 1, n) {
            F(j, 1, n) {
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
            }
        }
    }
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    F(i, 1, (1ll << n) - 2) {
        F(j, 0, n - 1) {
            if (i >> j & 1) {
                F(k, 0, n - 1) {
                    if (~i >> k & 1) {
                        f[i | (1ll << k)][k] = min(f[i | (1ll << k)][k], f[i][j] + mp[j + 1][k + 1]);
                    }
                }
            }
        }
    }
    cout << f[(1ll << n) - 1][n - 1] << '\n';
}

signed main() { $(); }
```

---

## 作者：UnfortunatelyDead (赞：0)

观察到 $1 \leq n \leq 20$，显然不能是爆搜，我们考虑状压。

具体地，我们枚举 $i \in [1,2^n-1]$ 的，令 $i$ 的二进制表示为 $1$ 的位 $j$ 表示该方案会选 $j$，由于枚举的特殊性，所以 $i$ 所包含的子方案一定是属于 $[1,i-1]$ 的，会被枚举到。

于是可以考虑定义 dp 状态了，我们定义 $f_{i,j}$ 为当前方案表示为 $i$，当前方案 $i$ 遍历完之后所在的节点为 $j$，那么我们对于这个 $i$，可以枚举它是由何而转移得来，即上一个方案停止的位置在哪，由于肯定包含所有的子方案，所以只要枚举选的点数量 $-1$ 个的方案是什么好了。

不妨设这个枚举得到的上一次停下的节点为 $k$，那么我们由 $k$ 到 $j$，花费增加了 $dis_{k,j}$（或 $dis_{j,k}$），而我们具体表示这个方案的值就是 $i$ 去掉 $j$ 的值，即 $i - 2^{j-1}$（如果默认都是从 $0$ 开始则不用减），记为 $s$，那么转移方程显而易见就是 $f_{i,j} = \min(f_{i,j},f_{s,k} + dis_{k,j})$。

由于给出的 $dis$ 数组保证都是两两的最短路径，所以拿到之后直接开始 dp 即可。

```cpp
int dis[25][25];
const int N = 2e6 + 19;
int f[N][25];
signed main() {
	int n = read();
	for (int i = 0; i < (1 << n); ++i) for (int j = 1; j <= n; ++j) f[i][j] = 1e9;
	f[1][1] = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) read(dis[i][j]);
	for (int i = 1; i < (1 << n); ++i) for (int j = 1; j <= n; ++j) if (i & (1 << j-1)) {
		for (int k = 1; k <= n; ++k) if ((i & (1 << k-1)) && j != k) smin(f[i][k], f[i - (1 << k-1)][j] + dis[j][k]);
	}
	write(f[(1 << n) - 1][n], '\n');
	return 0;
}
```

---

## 作者：zcz0263 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10447)

## 题意
给定一个有编号为 $0 \sim n-1$ 的点的完全图和每条边的权值，求从 $0$ 点经过所有点到 $n-1$ 点的最短路。

## 思路
观察到数据范围 $n \leq 20$，如果用全排列枚举路径的时间复杂度是 $O((n-2)! \times n)$ 的，不能通过此题。

考虑使用状态压缩 DP，设 $dp_{i,j}$ 表示以第 $i$ 个点为终点，已经走过的点在 $j$ 的二进制对应位为 $1$ 时的最短路径。不难想到每种情况的转移需要枚举上一步的终点，对应的 $j$ 即为将二进制下第 $i$ 位取反后的当前 $j$，状态转移方程为：
$$dp_{i,j}=\min_{1 \leq k < n} \left\{ dp_{k,j \oplus 2^i} + a_{k,i} \right\}(\lfloor\frac{j \oplus 2^i}{2^k}\rfloor \mod 2 = 1) $$
同时可以发现，若在一个状态中 $j$ 的二进制下第 $i$ 或第 $1$ 位为 $0$，则此状态不合法。

初始状态 $dp_{0,1}=0$，其余 $dp_{i,j}$ 为 `INF`，目标状态为 $dp_{n-1,2^n-1}$。

时间复杂度为 $O(2^n \times n^2)$
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
int a[25][25],dp[25][1<<21],n;
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n;
	rep(i,0,n-1) rep(j,0,n-1) cin>>a[i][j];
	memset(dp,0x3f,sizeof(dp));
	dp[0][1]=0;
	rep(j,1,(1<<n)-1)
		rep(i,0,n-1)
			if(((j>>i)&1)&&(j&1))
				rep(k,0,n-1)
					if(((j^(1<<i))>>k)&1)
						dp[i][j]=min(dp[i][j],dp[k][j^(1<<i)]+a[k][i]);
	cout<<dp[n-1][(1<<n)-1];
}
```

---

