# [ABC287F] Components

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_f

$ N $ 頂点の木があります。頂点には $ 1 $ から $ N $ までの番号が付いており、$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

$ x=1,2,\ldots,N $ に対して次の問題を解いてください。

- 木の頂点の部分集合 $ V $ であって空でないものは $ 2^N-1 $ 通り存在するが、そのうち $ V $ による誘導部分グラフの連結成分数が $ x $ であるようなものは何通りあるかを $ 998244353 $ で割った余りを求めよ。
 
 誘導部分グラフとは $ S $ をグラフ $ G $ の頂点の部分集合とします。このとき、$ G $ の $ S $ による誘導部分グラフとは、頂点集合が $ S $ で、辺集合が「$ G $ の辺であって両端が $ S $ に含まれるものすべて」であるようなグラフです。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ a_i\ \lt\ b_i\ \leq\ N $
- 与えられるグラフは木
 
### Sample Explanation 1

以下の $ 5 $ 通りでは誘導部分グラフの連結成分数が $ 2 $、これら以外では $ 1 $ になります。 - $ V\ =\ \{1,2,4\} $ - $ V\ =\ \{1,3\} $ - $ V\ =\ \{1,3,4\} $ - $ V\ =\ \{1,4\} $ - $ V\ =\ \{2,4\} $

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
10
5
0
0```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
3
0```

## 样例 #3

### 输入

```
10
3 4
3 6
6 9
1 3
2 4
5 6
6 10
1 8
5 7```

### 输出

```
140
281
352
195
52
3
0
0
0
0```

# 题解

## 作者：泥土笨笨 (赞：13)

赛后十分钟做完此题，酸爽。

比较基础的树上背包DP。按照树上DP的套路，状态定义里面一定有 $u$ 表示目前递归到以 $u$ 为根的子树。另外因为要考虑连通块，自己这个点选不选会影响连通块的个数，用第二个维度表示 $u$ 选不选。选多少个点显然也会影响决策，再加一维。这样状态定义就好了：

用 $dp[u][0][i]$ 表示以 $u$ 为根的子树，$u$ 自己不选，整棵树里面总共选 $i$ 个连通块的方案数有多少。用 $dp[u][1][i]$ 表示以 $u$ 为根的子树，$u$ 自己选，整棵树里面总共选 $i$ 个连通块的方案数有多少。

显然只考虑根自己的时候，有：$dp[u][0][0] = 1$ 和 $dp[u][1][1] = 1$。

接下来考虑一个孩子一个孩子加进来，当前加进来的孩子是 $v$ ，先递归调用 $v$ 把它的所有dp值求好。然后考虑父子之间转移，当 $u$ 以及 $v$ 之前的孩子们中选 $i$ 个连通块，$v$ 中选 $j$ 个连通块，如果 $u$ 不选，那么总的连通块个数就是 $i+j$，因为它们相互之间被 $u$ 分开，肯定不连通。此时计算连通块的个数可以直接乘法原理，转移代码：

```cpp
dp[u][0][i + j] = (dp[u][0][i + j] + dp[u][0][i] * (dp[v][0][j] + dp[v][1][j]) % MOD) % MOD;
```

如果 $u$ 选，$v$ 不选，也是同理。唯一不同的是，如果 $u$ 和 $v$ 都选，总的连通块个数会少 $1$ 个，因为 $u$ 和 $v$ 所在的两个连通块连一起了。代码时间复杂度 $O(n^2)$。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = 5005;
const ll MOD = 998244353;
//dp[u][0][i]表示以u为根的子树，根不要，总共保留i个连通块的方案数。第二维1表示要根。
ll n, dp[MAXN][2][MAXN];
vector<int> adj[MAXN];

int dfs(int u, int f) {
    int tc = 1;//子树中点的数量
    dp[u][0][0] = 1;//初始化根的答案
    dp[u][1][1] = 1;
    for (int v: adj[u]) {
        if (v != f) {
            int ch = dfs(v, u);//递归调用孩子，保存孩子中点的数量
            //先计算u不要的情况
            for (int i = tc; i >= 0; --i) {
                for (int j = ch; j >= 1; --j) {
                    //注意这里j不取0，0的时候有一种方案，和原来的dp[u][0][i]乘完放回去，相当于dp[u][0][i]的值不动
                    //u不要，v要不要都行
                    dp[u][0][i + j] = (dp[u][0][i + j] + dp[u][0][i] * (dp[v][0][j] + dp[v][1][j]) % MOD) % MOD;
                }
            }
            //计算u要的情况
            for (int i = tc; i >= 1; --i) {
                for (int j = ch; j >= 1; --j) {
                    //注意这两句话顺序不能反，j等于1的时候，i + j - 1等于i，会改掉之前的值
                    dp[u][1][i + j] = (dp[u][1][i + j] + dp[u][1][i] * dp[v][0][j] % MOD) % MOD;
                    dp[u][1][i + j - 1] = (dp[u][1][i + j - 1] + dp[u][1][i] * dp[v][1][j] % MOD) % MOD;
                }
            }
            tc += ch;
        }
    }
    return tc;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << (dp[1][0][i] + dp[1][1][i]) % MOD << endl;
    }
    return 0;
}
```


---

## 作者：CrTsIr400 (赞：6)

代码和和动态规划的式子想必大家都已经很清楚了，但是为什么是 $O(n^2)$ 呢？

求证： $O(\sum\limits_{i=1}^n \sum\limits_{j\in son(i)} siz(j)\times (1+\sum\limits_{k\in visited\_son(i)} siz(k)))=O(n^2)$。

考虑一个这样的事实，对于 $i$ 从左到右扫描儿子 $j$，但是已经遍历过的儿子不会再对当前 $i$ 的答案造成贡献。

考虑 $siz(used)\times siz(j)$ 的时间复杂度意义，可以说是对于 $j$ 子树之中的每个节点，枚举其左边遍历过的儿子并且贡献答案。

而这个 DP 顺序使得左边遍历过的儿子不会重复遍历，所以对于每个节点，其左边已经遍历过的所有节点个数不会超过 $O(n)$ 级别，所以时间复杂度就是 $O(n^2)$ 级别的。

---

## 作者：fengenrong (赞：3)

### 题意
给你一棵有 $N$ 个节点的树，顶点标号为 $1,2,\dots,N$ ，第 $i$ 条边连接的端点是 $a_i,b_i$. 

对每一个 $x=1,2,\dots,N$ ,解决如下问题:

有 $2^N-1$ 个非空的顶点子集 $V$ ,求 $V$ 的刚好包含 $x$ 个连通块的诱导子图的数量。 

什么是诱导子图？

设 $S$ 是图 $G$ 的顶点的子集，$S$ 的诱导子图是包含 $S$ 的所有顶点和这些顶点之间的所有边，这些边的两个端点都必须在 $S$ 中。 


### 思路

不难看出这题是一道树形动态规划，我们可以用 $dp(i,j,0)$ 表示在 $i$ 的子树上有 $j$ 块并且不选第 $i$ 块的方案数，用 $dp(i,j,1)$ 表示在 $i$ 的子树上有 $j$ 块并且选第 $i$ 块的方案数。

由题意得，我们假如不选，则子节点可选可不选。如果选，则子节点要是选则选的块数是一样的，要是不选就要多加一块。

所以，我们可以分三类来讨论：

$i$ 点选择，可得：
$$dp(i,j+k,0)= \sum_{x\in ison} dp(i,j,0)\times (dp(x,k,1)+dp(x,k,0))$$
$i$ 点不选则且 $i$ 点的子节点也不选，可得：
$$dp(i,j+k-1,1)= \sum_{x\in ison} dp(i,j,1)\times dp(x,k,1)$$
$i$ 点不选则且 $i$ 点的子节点选，可得：
$$dp(i,j+k,1)= \sum_{x\in ison} dp(i,j,1)\times dp(x,k,0)$$

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct op {
    int from, to, next;//链式前向星
} a[10005];
int head[5005], cnt;
void add(int x, int y) { a[cnt].from = x, a[cnt].to = y, a[cnt].next = head[x], head[x] = cnt++; }//链式前向星存图 
const int mod = 998244353;
int son_sum[5005];
int dp[5005][5005][2];
bool vis[5005];
void dfs(int x, int father) {
    dp[x][0][0] = dp[x][1][1] = 1;//初始化 
    son_sum[x] = 1;//初始化 
    for (int i = head[x]; i != -1; i = a[i].next) {
        int y = a[i].to;
        if (y == father)
            continue;
        dfs(y, x);
        for (int j = son_sum[x]; j >= 0; j--) {
            for (int k = son_sum[y]; k >= 1; k--) {
            	//根据dp式 
                dp[x][j + k][0] =
                    ((dp[x][j + k][0]) + ((dp[x][j][0] * ((dp[y][k][1] + dp[y][k][0]) % mod)) % mod)) % mod;
                if (j == 0)
                    continue;
                dp[x][j + k][1] = ((dp[x][j + k][1]) + ((dp[x][j][1] * dp[y][k][0]) % mod)) % mod;
                dp[x][j + k - 1][1] = ((dp[x][j + k - 1][1]) + ((dp[x][j][1] * dp[y][k][1]) % mod)) % mod;
            }
        }
        son_sum[x] += son_sum[y];//记录当前子树一共有多少个点 
    }
}
signed main() {
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%lld", &n);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%lld%lld", &x, &y);
        add(x, y), add(y, x);//建边 
    }
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", (dp[1][i][0] + dp[1][i][1]) % mod);//输出答案，记得取模 
    }
    return 0;
}
```

---

## 作者：Composite_Function (赞：2)

**前言**：在空余时间与同学讨论题目时，看到了这道题。当时就给出了一个树上 DP 的想法，但惨遭质疑，因为 TA 认为这是 $\Theta(n^3)$。当时我在稀里糊涂中也以为是这样，但回来后竟然过了。故发此文说说这事。

------------

对于一道树上计数问题，发现一个子节点对应子树中已经确定后，该节点对应子树对答案或情况的影响极小，所以考虑树上 DP 的算法。那么这道计数 DP 的状态该如何定义呢？首先得有记录每个节点。观察到在子节点到父节点的转移过程中有可能会产生新的连通块，故还需要记录到这个节点为止的连通块长度。同样重要的还有子树的根节点有没有被选，因为这关乎了增加或减少连通块。所以 DP 的状态可以被定义为：

```cpp
int dp[N][N][2];
```

其中的 `N` 为极大值大于节点编号的最大值和连通块最大值。定义为：

```cpp
const int N = 5010;
```

然后这个数组的第一位表示节点；第二位表示连通块个数；第三位表示是否选择这个节点，如果为 $0$ 那么是不选，是 $1$ 是选。

接下来考虑转移方程。先从简单的不选的情况入手。发现这个节点对应子树中的连通块个数就是子节点对应子树中的连通块之和。不难写出这样的转移：

```cpp
for (int i = sz; i >= 0; --i)
	for (int j = ssz; j >= 1; --j) 
		dp[u][i + j][0] = (dp[u][i + j][0] + dp[u][i][0] * (dp[v][j][0] + dp[v][j][1])) % mod;
```

其中 `u` 表示当前节点；`v` 表示转移的子节点； `sz` 表示的是当前已计算的子树大小，也就是目前连通块个数的上界；`ssz` 表示的是已计算的字数大小。

然后该如何计算选这个子树的大小呢？其实只需讨论两种情况：

2. 选了恰好 $1$ 个子节点对应的子树满足选了该子节点，即这颗子树的根节点
3. 选了 $>1$ 个子节点对应的子树满足选了该子节点，即这颗子树的根节点

然后就可以类似上面地写出这样的转移方程：

```cpp
for (int i = sz; i >= 1; --i)
	for (int j = ssz; j >= 1; --j) {
		dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][1] * dp[v][j][0]) % mod;
		dp[u][i + j - 1][1] = (dp[u][i + j - 1][1] + dp[u][i][1] * dp[v][j][1]) % mod;
}
```

符号同上略过不提。

接下来是初始值，发现只有：

```cpp
dp[u][0][0] = dp[u][1][1] = 1;
```

------------

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5010, mod = 998244353;
int n, dp[N][N][2];
vector<int> to[N];
int dfs(int u, int fa)
{
	int sz = 1;
	dp[u][0][0] = dp[u][1][1] = 1;
	for (int v : to[u]) {
		if (v == fa) continue;
		int ssz = dfs(v, u);
		for (int i = sz; i >= 0; --i)
			for (int j = ssz; j >= 1; --j) 
				dp[u][i + j][0] = (dp[u][i + j][0] + dp[u][i][0] * (dp[v][j][0] + dp[v][j][1])) % mod;
		for (int i = sz; i >= 1; --i)
			for (int j = ssz; j >= 1; --j) {
				dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][1] * dp[v][j][0]) % mod;
				dp[u][i + j - 1][1] = (dp[u][i + j - 1][1] + dp[u][i][1] * dp[v][j][1]) % mod;
			}
		sz += ssz; // !!!
	}
	return sz;
}
signed main()
{
	cin >> n;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
		cout << (dp[1][i][0] + dp[1][i][1]) % mod << endl;
	return 0;
}
```

注意标 `!!!` 的地方，这与复杂度有极大关系。这意味着如果把：

```cpp
		int ssz = dfs(v, u);
		for (int i = sz; i >= 0; --i)
			for (int j = ssz; j >= 1; --j) 
				dp[u][i + j][0] = (dp[u][i + j][0] + dp[u][i][0] * (dp[v][j][0] + dp[v][j][1])) % mod;
		for (int i = sz; i >= 1; --i)
			for (int j = ssz; j >= 1; --j) {
				dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][1] * dp[v][j][0]) % mod;
				dp[u][i + j - 1][1] = (dp[u][i + j - 1][1] + dp[u][i][1] * dp[v][j][1]) % mod;
			}
		sz += ssz; // !!!
```

改成：

```cpp
		int ssz = dfs(v, u);
		sz += ssz; // !!!
		for (int i = sz; i >= 0; --i)
			for (int j = ssz; j >= 1; --j) 
				dp[u][i + j][0] = (dp[u][i + j][0] + dp[u][i][0] * (dp[v][j][0] + dp[v][j][1])) % mod;
		for (int i = sz; i >= 1; --i)
			for (int j = ssz; j >= 1; --j) {
				dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][1] * dp[v][j][0]) % mod;
				dp[u][i + j - 1][1] = (dp[u][i + j - 1][1] + dp[u][i][1] * dp[v][j][1]) % mod;
			}
```

将会 TLE。

构造：一条链。不难发现此时的时间复杂度可以达到达到了：$\Theta((n-1)^2+(n-2)^2+...+1^2)=\Theta(n^3)$。

------------

**复杂度分析**：对于节点 $u$，设其有 $son_u$ 个子节点，对应子树大小依次为：$size_1,size_2,...,size_{son_u}$。则计算这个节点答案的时间复杂度为 $\Theta(\sum_{i=1}^{son_u}(\sum_{j=1}^{i-1}size_j+1)size_i)=\Theta(\sum_{i=1}^{son_u}\sum_{j=1}^{i-1}size_jsize_i+size_i)$。

考虑对每个子树中的一个节点，DP 遍历的顺序保证了其对答案的贡献不会超过 $\Theta(n)$。所以加起来贡献也不会超过 $\Theta(n^2)$。

总之非常玄学就是了。

------------

篇幅挺长的，感谢阅读。

---

## 作者：DengDuck (赞：2)

我们设 $f(i,j,0)$ 表示不选择点 $i$，在 $i$ 的子树连通块有 $j$ 块的方案数。

$f(i,j,1)$ 表示选择点 $i$，在 $i$ 的子树连通块有 $j$ 块的方案数。

讨论三种情况：

如果点 $x$ 不选择，对于 $x$ 的一个子树 $i$，选择和不选择都可以，那么得：

$$
f(x,j+k,0)=\sum_{i\in xson} f(x,j,0)\times( f(i,k,1)+f(i,k,0))
$$


如果点 $x$ 选择，不选择 $x$ 的一个子树 $i$，那么得：

$$
f(x,j+k,1)=\sum_{i\in xson} f(x,j,1)\times f(i,k,0)
$$

如果点 $x$ 选择，选择 $x$ 的一个子树 $i$，那么得：

$$
f(x,j+k-1,1)=\sum_{i\in xson} f(x,j,1)\times f(i,k,1)
$$

这种情况的块数比较特殊，主要是 $i$ 和 $x$ 连成了一个连通块，所以只有 $j+k-1$ 个连通块。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=5e3+5;
const LL mod=998244353;
LL n,sz[N],f[N][N][2],val[N],son[N],x,y;
vector<LL>v[N];
void dfs(LL x,LL fa)
{
	f[x][0][0]=f[x][1][1]=1;
	sz[x]=1;
	for(auto i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		for(int j=sz[x];j>=0;j--)
		{
			for(int k=sz[i];k>=1;k--)
				f[x][j+k][0]=(f[x][j+k][0]+f[x][j][0]*(f[i][k][1]+f[i][k][0])%mod)%mod;
		}
		for(int j=sz[x];j>=1;j--)
		{
			for(int k=sz[i];k>=1;k--)
			{
				f[x][j+k][1]=(f[x][j+k][1]+f[x][j][1]*f[i][k][0]%mod)%mod;
				f[x][j+k-1][1]=(f[x][j+k-1][1]+f[x][j][1]*f[i][k][1]%mod)%mod;
			}
		}
		sz[x]+=sz[i];
	}
}
int main()
{
	
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		cout<<(f[1][i][0]+f[1][i][1])%mod<<endl; 
	}
}
```

---

## 作者：dengchengyu (赞：1)

## abc287_f

一眼树上背包，并且看到 $n\le 5000$ 是可以通过的。

我们要注意在限制枚举范围的情况下，树上背包的复杂度是 $O(n^2)$ 的。

设 $f_{i,j}$ 表示选择点 $i$ 且子树内有 $j$ 个连通块的方案数，$g_{i,j}$ 表示不选择点 $i$ 的方案数。

$f\to g,g\to g,g\to f$ 都是直接把连通块个数相加，$f\to f$ 则把连通块个数相加后减 1。

注意要先转移再把 $sz$ 加上复杂度才是正确的。

AC 代码：

```cpp
const int N=5005;
const int mod=998244353;
int n;
vector<int> G[N];
int f[N][N],g[N][N];
int sz[N];
void dfs(int x,int y){
	g[x][0]=1;
	f[x][1]=1;
	sz[x]=1;
	for(int v:G[x]){
		if(v==y)continue;
		dfs(v,x); 
		fd(i,sz[x],0){
			fd(j,sz[v],1){
				g[x][i+j]=(g[x][i+j]+(ll)g[x][i]*g[v][j])%mod;
				g[x][i+j]=(g[x][i+j]+(ll)g[x][i]*f[v][j])%mod;
				f[x][i+j]=(f[x][i+j]+(ll)f[x][i]*g[v][j])%mod;
				f[x][i+j-1]=(f[x][i+j-1]+(ll)f[x][i]*f[v][j])%mod;	
			}
		}
		sz[x]+=sz[v];
	}
}
signed main(){
	read(n);
	fo(i,1,n-1){
		int u,v;
		read(u,v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	fo(i,1,n){
		write((f[1][i]+g[1][i])%mod,'\n');
	}
	return 0;
}
```

---

## 作者：AC_love (赞：1)

设 $f(i, j, 0 / 1)$ 表示 $i$ 子树中有 $j$ 个联通块，且 $i$ 这个点没被选中 / 被选中的情况。

只有根节点的时候，显然有 $f(i, 0, 0) = 1$ 且 $f(i, 1, 1) = 1$。

然后我们考虑根节点的每棵子树，求出某个儿子几点的 $f$，考虑如何向上合并：

对于某个儿子 $x$，我们枚举原来有几个联通块 $u$ 和 $x$ 有几个联通块 $v$，得到转移：

$$f(i, u + v, 0) \leftarrow f(i, u + v, 0) + f(i, u, 0) \times f(x, v, 0) + f(i, u, 0) \times f(x, v, 1)$$

$$f(i, u + v, 1) \leftarrow f(i, u + v, 1) + f(i, u, 1) \times f(x, v, 0) + f(i, u, 1) \times f(x, v + 1, 1)$$

直接转移即可。

不过需要注意的是：如果不注意转移顺序的话，可能出现转移过程中覆盖了之后转移时要用到的位置的情况，导致答案出错。我的解决办法是将转移的答案赋值到一个新数组中。转移结束之后，再把新数组的内容覆盖到旧数组上。

[code](https://atcoder.jp/contests/abc287/submissions/59997058)

---

## 作者：_shine_ (赞：1)

首先看到树上求方案数则很显然想到树形 DP。

看到这里首先定义 $sz_{m}$ 表示为以 $m$ 为根的子树的的节点数量，并定义 $f_{u,l}$ 表示为表示为以 $u$ 为根的子树且联通块数为 $l$ 的方案数。

则显然对于每个叶子节点，$f$ 的值为 $1$。
但是可以发现的是如果要在合并要分别合并两个 $f$ 的值则有有可能会导致联通块数量并不是两个的联通块的值的和（如图所示）。
![](https://cdn.luogu.com.cn/upload/image_hosting/is8tw6je.png)

这里可能出现的情况是说有可能当前选择了节点为 $2$ 的点，但在下面又选择了点为 $5$ 的点，导致了两个重合在了一起，联通块数减去一。

那么显然尝试把选不选择子树根节点的情况分离出来。
#### 重新定义
再次重新并新定义两个东西：$f_{u,l},g_{v,n}$，表示分别如下：
1. $f_{u,l}$ 表示为以 $u$ 为根的子树且要选择点 $u$，联通块为 $l$ 的方案数。
1. $g_{v,n}$ 表示为以 $v$ 为根的子树且不选择点 $u$，联通块为 $n$ 的方案数。

则还是如上图所示，把 $f$ 分离出 $g$ 后可以发现状态转移方程如下：
- $g_{u,j+k}=g_{u,j}\times \left(g_{v,k}+f_{v,k}\right)$
- $f_{u,j+k}=f_{u,j}\times g_{v,k}$
- $f_{u,j+k-1}=f{u,j}\times f_{v,k}$

又发现 $f_{u,j+k-1}$ 一栏可以把 $-1$ 消掉，则合并后分别处理即可，状态转移方程再次更新后如下：
- $g_{u,j+k}=g_{u,j}\times \left(g_{v,k}+f_{v,k}\right)$
- $f_{u,j+k}=f_{u,j}\times g_{v,k}$

注意在计算时有可能出现引用当前循环出现的值，所以尝试使用 $temp$ 先行记录下当前的值随后再更新即可。

则答案为 $f_{1,l}+g_{1,l}$。

---

## 作者：CodingShark (赞：1)

显然要用树形 dp 来做。

令 `dp[u][j][0 / 1]` 表示 (以 $u$ 为根的子树) (有 $i$ 个连通块) ($u$ 点选/不选）的方案数。

如果 $u$ 不选，那么在子树 $v$ 里选 $k$ 个，连通块数量就增加 $k$，前面的方案数（`dp[u][j][0]`）乘上这个子树的方案数（`dp[v][k][0] + dp[v][k][1]`）。

`dp[u][j + k][0] += dp[u][j][0] * (dp[v][k][0] + dp[v][k][1])`

如果 $u$ 选，则需要分情况讨论：

- 子树 $v$ 中不选 $v$，那么直接相乘即可：

`dp[u][j + k][1] += dp[u][j][1] * dp[v][k][0]`

- 子树 $v$ 中选 $v$，那么 $v$ 所在的连通块会与 $u$ 连通，形成一个连通块，所以总数要 -1：

`dp[u][j + k - 1][1] += dp[u][j][1] * dp[v][k][1]`

由于 $N \le 5000$，所以要用子树大小限制 dp 的范围，时间复杂度 $O(N^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
struct Edge
{
  int u, v, next;
} e[10005];
int n, pos, head[5005], siz[5005];
long long dp[5005][5005][2];
void addEdge(int u, int v)
{
  e[++pos] = {u, v, head[u]};
  head[u] = pos;
}
 
void dfs(int u, int fa = -1)
{
  siz[u] = 1;
  dp[u][0][0] = dp[u][1][1] = 1; // 初始化
  for (int i = head[u]; i; i = e[i].next)
  {
    int v = e[i].v;
    if (v == fa)
      continue;
    dfs(v, u);
    for (int j = siz[u]; j >= 0; j--) // 倒序枚举
      for (int k = siz[v]; k >= 1; k--)
      {
        dp[u][j + k][0] += dp[u][j][0] * (dp[v][k][0] + dp[v][k][1]);
        if (j > 0)
        {
          // 请注意这两个方程先后顺序，不能调换
          dp[u][j + k][1] += dp[u][j][1] * dp[v][k][0];
          dp[u][j + k - 1][1] += dp[u][j][1] * dp[v][k][1];
        }
        dp[u][j + k][0] %= mod, dp[u][j + k][1] %= mod, dp[u][j + k - 1][1] %= mod;
      }
    siz[u] += siz[v];
  }
}
 
int main()
{
  scanf("%d", &n);
  for (int i = 1; i < n; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    addEdge(u, v), addEdge(v, u);
  }
  dfs(1);
  for (int i = 1; i <= n; i++)
    printf("%lld\n", (dp[1][i][0] + dp[1][i][1]) % mod);
  return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## [ABC287F] Components 题解
upd 2025.1.10 修改了 $\LaTeX$。
### Solution
一道树上背包。

设计状态：我们定义 $dp_{i,j,0/1}$ 表示以 $i$ 为根的子树选择 $j$ 个连通块，其中根节点选或不选的方案数。

初始化：显然，最开始 $dp_{i,0,0}=dp_{i,1,1}=1$。因为不选根节点，选 $0$ 个连通块和选择根节点，选 $1$ 个连通块的方案数均为 $1$。此时根节点和子树未进行合并操作。

转移：我们开两层循环，第一层 $i$ 枚举根节点 $u$ 及已经合并的子树的大小；第二层 $j$ 枚举当前子节点 $v$ 所代表的子树大小，并分情况讨论：
- $dp_{u,i+j,0}$ 表示合并后不选择 $u$ 节点，那么 $u$ 节点必须不选择，有 $dp_{u,i,0}$ 种方案；子节点 $v$ 选不选都行，有 $dp_{v,j,0}+dp_{v,j,1}$ 种方案。根据乘法原理，两者相乘就可以得到结果。公式为 $dp_{u,i+j,0} \gets dp_{u,i+j,0}+dp_{u,i,0}(dp_{v,j,0}+dp_{v,j,1})$。
- $dp_{u,i+j,1}$ 表示此时根节点 $u$ 必须选择。与上文不同的是，此时 $v$ 节点不能选择，否则将形成新的连通块，与状态不符。公式为 $dp_{u,i+j,1} \gets dp_{u,i+j,1}+dp_{u,i,1}\times dp_{v,j,0}$。
- $dp_{u,i+j-1,1}$ 表示 $u$ 和 $v$ 都选，形成新的连通块，总个数发生改变，需要减 $1$。和上文原理相似，公式为 $dp_{u,i+j-1,1} \gets dp_{u,i+j-1,1}+dp_{u,i,1}\times dp_{v,j,1}$。

所以 $x=i$ 的答案就是 $dp_{1,i,0}+dp_{1,i,1}$。

时间复杂度 $O(N^2)$。

### [AC Code](https://www.luogu.com.cn/record/201519505)
```cpp
#include<iostream>
#include<vector>
#define ll long long
#define pb push_back
using namespace std;
const int N=5e3+10;
const int MOD=998244353;
vector<int>G[N];
int siz[N],n,u,v;
ll dp[N][N][2];//dp[i][j][0/1]:以i为根的子树，选择j个连通块，选/不选i节点的方案数之和 
void dfs(int x,int fa){
	siz[x]=1;
	dp[x][0][0]=dp[x][1][1]=1;
	for(auto i:G[x]){
		if(i==fa) continue;
		dfs(i,x);
		for(int j=siz[x];j>=0;j--){
			for(int k=siz[i];k>=1;k--){
				if(j+k<=n){
					dp[x][j+k][0]=(dp[x][j+k][0]+dp[x][j][0]*(dp[i][k][0]+dp[i][k][1])%MOD)%MOD;
				    dp[x][j+k][1]=(dp[x][j+k][1]+dp[x][j][1]*dp[i][k][0]%MOD)%MOD;
				}
				if(j+k-1<=n) dp[x][j+k-1][1]=(dp[x][j+k-1][1]+dp[x][j][1]*dp[i][k][1]%MOD)%MOD;
			}
		}
		siz[x]+=siz[i];
	}
	return;	
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) printf("%lld\n",(dp[1][i][0]+dp[1][i][1])%MOD);
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：0)

$\LARGE{\text{solution}}$

树上的问题我们一般可以用子节点为根的子树来更新父节点为根的树。这道题也是这样的一道树形 DP。

我们可以定义一个二维的数组 $f$,$f_{i,j}$ 表示以 $i$ 为根的子树刚好有 $j$ 个连通块的方案数。但是考虑到 $i$ 选或不选会对它父节点的更新造成影响（如果它和它的父节点都选，就在一个连通块里），所以用一个新数组（或者给 $f$ 加一维）$g$ 来记录 $i$ 不选的方案数，$f$ 记录 $i$ 要选的方案数。

那么现在我们就需要推式子。假设当前节点为 $u$，遍历到了它的子节点 $j$，那么我们把 $u$ 已经遍历过的子节点及其子树看成一部分，也是 $f_u$ 和 $g_u$ 记录的部分，把以 $j$ 为子树的看成一部分，去更新。

我们枚举 $u$ 的部分有多少个连通块和 $j$ 的部分有多少个连通块，然后把两部分合在一起去更新 $u$。设 $u$ 的部分有 $k$ 个连通块，$j$ 的部分有 $t$ 个连通块。合起来有两种情况：
>1. $u$ 和 $j$ 都选，那么两部分会有连接，就会把两个连通块合并成一个，总共就是 $t + k - 1$ 个。
>
>2. $u$ 和 $j$ 没有都选，两部分没有连接，总共有 $k + t$ 个连通块。

枚举这些情况：

```cpp
f[u][t + k] += f[u][k] * g[j][t];
f[u][t + k - 1] += f[u][k] * f[j][t];
g[t + k] += g[u][k] * (f[j][t] + g[j][t]);
//没有g[j + k - 1]，连通了就不能不选
```
然后可以合并一下前两个。

`f[u][t + k] += f[u][k] * (g[j][t] + f[j][t + 1]);`

但是不能直接这样更新，因为对数组的改变会影响其他情况的更新，用一个临时数组存值就行了。

最后输出答案，把根节点的两种情况加起来即可。

$\LARGE{\text{code}}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int sz[5010];
vector <int> v[5010];
int g[5010][5010], f[5010][5010];

void dfs(int u, int fa)
{
	sz[u] = 1;
	f[u][1] = 1, g[u][0] = 1;
	for (int son : v[u])
	{
		if (son == fa) continue;
		dfs (son, u);
		
		int tep1[10010] = {0};
		
		for (int j = 0; j <= sz[u]; j++)
			for (int k = 0; k <= sz[son]; k++)
				tep1[j + k] += g[u][j] * (f[son][k] + g[son][k]), tep1[j + k] %= mod;
				
		for (int i = 0; i <= sz[u] + sz[son]; i++) g[u][i] = tep1[i];
		
		int tep2[10010] = {0};
		
		for (int j = 0; j <= sz[u]; j++)
			for (int k = 0; k <= sz[son]; k++)
				tep2[j + k] += f[u][j] * (f[son][k + 1] + g[son][k]), tep2[j + k] %= mod;
				
		for (int i = 0; i <= sz[u] + sz[son]; i++) f[u][i] = tep2[i];
		sz[u] += sz[son];
	}
}

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back (b);
		v[b].push_back (a);
	}
	dfs (1, 0);
	for (int i = 1; i <= n; i++)
		cout << (f[1][i] + g[1][i]) % mod << endl; 
	return 0;
} 
```

---

## 作者：Register_int (赞：0)

第一眼设 $dp_{u,i}$ 为 $u$ 为根的子树内有 $i$ 个连通块，不过不好转移，因为你不知道合并的子树的连通块是否会与当前子树的根连一起。

不放加一维 $0/1$ 表示强制选/不选根，转移就是：

$$
\begin{aligned}
dp_{u,i+j,0}&\gets dp_{u,i+j,0}+dp_{u,i,0}\cdot(dp_{v,j,0}+dp_{v,j,1})\\
dp_{u,i+j,1}&\gets dp_{u,i+j,1}+dp_{u,i,1}\cdot dp_{v,j,0}+dp_{u,i-1,1}\cdot dp_{v,j,1}\\
\end{aligned}
$$

大力背包，时间复杂度 $O(n^2)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;
const int mod = 998244353;

/*
dp_u,i,0/1: 以 u 为根的子树，选出 i 个连通块，u 必选/不选的方案数
*/

vector<int> g[MAXN];

int s[MAXN]; ll dp[MAXN][MAXN][2], f[MAXN];

void dfs(int u, int fa) {
	dp[u][0][0] = dp[u][1][1] = s[u] = 1;
	for (int v : g[u]) {
		if (v == fa) continue; dfs(v, u);
		for (int i = 0; i <= s[u]; i++) {
			for (int j = 0; j <= s[v]; j++) {
				f[i + j] = (f[i + j] + dp[u][i][0] * (dp[v][j][0] + dp[v][j][1]) % mod) % mod;
			}
		}
		for (int i = 0; i <= s[u] + s[v]; i++) dp[u][i][0] = f[i], f[i] = 0;
		for (int i = 1; i <= s[u]; i++) {
			for (int j = 0; j <= s[v]; j++) {
				f[i + j] = (f[i + j] + dp[u][i][1] * dp[v][j][0] % mod) % mod;
				f[i + j - 1] = (f[i + j - 1] + dp[u][i][1] * dp[v][j][1] % mod) % mod;
			}
		}
		for (int i = 0; i <= s[u] + s[v]; i++) dp[u][i][1] = f[i], f[i] = 0;
		s[u] += s[v];
	}
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) printf("%lld\n", (dp[1][i][0] + dp[1][i][1]) % mod);
}
```

---

## 作者：WaterSun (赞：0)

# 思路

定义 $dp_{i,j,0/1}$ 表示在以 $i$ 为根的子树中（包括 $i$）选出 $j$ 个连通块，且 $i$ 不选/选 的方案数。

假设我们在 DFS 过程中，当前枚举到以 $u$ 为根节点的情况，那么显然有 $dp_{u,0,0} = dp_{u,1,1} = 1$。

然后，我们从 $u$ 开始向其儿子节点搜索，假设当前枚举到的点是 $v$。

那么，我们对于每一个 $v$，我们都可以对 $u$ 的选取情况作分类讨论（其中 $a,b$ 表示以 $u$ 为根的子树在没有 $v$ 之前的连通块数量，和以 $v$ 为根的子树中连通块的数量）：

1. 如果不选，那么两棵子树合并，连通块数量为 $a + b$，那么有 $dp_{u,a + b,0} \leftarrow dp_{u,a + b,0} + dp_{u,a,0} \times (dp_{v,b,0} + dp_{v,b,1})$。

2. 如果选，那么还需要根据 $v$ 的选取情况进行分类讨论：

 - 如果 $v$ 不选，那么两棵子树合并，连通块数量还是为 $a + b$，那么有 $dp_{u,a + b,1} \leftarrow dp_{u,a + b,1} + dp_{u,a,1} \times dp_{v,b,0}$。
 
 - 如果 $v$ 选，那么两棵子树合并，由于 $u,v$ 都要选，那么，包含  $u,v$ 的两个连通块将合并为一个，所以连通块数量为 $a + b - 1$，那么有 $dp_{u,a + b - 1,1} \leftarrow dp_{u,a + b - 1,1} + dp_{u,a,1} \times dp_{v,b,1}$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5010,M = 1e4 + 10,mod = 998244353;
int n;
int idx,h[N],e[M],ne[M];
int dp[N][N][2];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void add(int a,int b){
	ne[idx] = h[a];
	e[idx] = b;
	h[a] = idx++;
}

inline int dfs(int u,int fa){
	int sz = 1;
	dp[u][0][0] = dp[u][1][1] = 1;
	for (re int i = h[u];~i;i = ne[i]){
		int j = e[i];
		if (j == fa) continue;
		int ssz = dfs(j,u);
		for (re int a = sz;~a;a--){
			for (re int b = ssz;b;b--) dp[u][a + b][0] = (dp[u][a + b][0] + dp[u][a][0] * (dp[j][b][0] + dp[j][b][1]) % mod) % mod;
			// b 不能枚举到 0，因为如果 b 枚举到 0，那么将会有 dp[u][a][0] = 2 * dp[u][a][0] % mod，然而这种状态肯定是我们计算过的，所以不能枚举到 0 
		}
		for (re int a = sz;a;a--){
			for (re int b = ssz;b;b--){
				dp[u][a + b][1] = (dp[u][a + b][1] + dp[u][a][1] * dp[j][b][0] % mod) % mod;
				dp[u][a + b - 1][1] = (dp[u][a + b - 1][1] + dp[u][a][1] * dp[j][b][1] % mod) % mod;
			}
		}
		sz += ssz;
	}
	return sz;
}

signed main(){
	memset(h,-1,sizeof(h));
	n = read();
	for (re int i = 1;i < n;i++){
		int a,b;
		a = read();
		b = read();
		add(a,b);
		add(b,a);
	}
	dfs(1,-1);
	for (re int i = 1;i <= n;i++) printf("%lld\n",(dp[1][i][0] + dp[1][i][1]) % mod);
	return 0;
}
```

---

## 作者：Feyn (赞：0)

一道比较基础的树形 DP 题目。

用 $f_{x,y}$ 代表子树 $x$ 中选出的点形成了 $y$ 个连通块，并且点 $x$ 被选择了的方案数，$g_{x,y}$ 表示点 $x$ 没有被选择的方案数。

转移的过程比较简单，考虑如果当前已经有了 $a$ 个连通块，而枚举到的这个儿子有 $b$ 个连通块，分类讨论一下：如果点 $x$ 被选择并且这个儿子被选择，那么连通块的数量是 $a+b-1$，否则是 $a+b$，更新即可。细节参照其它树上背包板子，复杂度 $O(N^2)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=5010;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline void chk(int &s1,int s2){
	s1=(s1+s2)%mod;
}

struct edge{
	int t,nxt;
}e[N<<1];
int head[N],esum;
inline void add(int fr,int to){
	e[++esum]=(edge){to,head[fr]};head[fr]=esum;
}

int m;

int siz[N],f[N][N],g[N][N],ff[N],gg[N];
void solve(int wh,int fa){
	siz[wh]=1;f[wh][1]=g[wh][0]=1;
	for(int i=head[wh],th;i;i=e[i].nxt){
		if((th=e[i].t)==fa)continue;
		solve(th,wh);
		for(int x=0;x<=siz[wh]+siz[th];x++)ff[x]=gg[x]=0;
		for(int x=0;x<=siz[wh];x++){
			for(int y=0;y<=siz[th];y++){
				chk(gg[x+y],g[wh][x]*f[th][y]);
				chk(gg[x+y],g[wh][x]*g[th][y]);
				chk(ff[x+y],f[wh][x]*g[th][y]);
				if(x+y)chk(ff[x+y-1],f[wh][x]*f[th][y]);
			}
		}
		siz[wh]+=siz[th];
		for(int x=0;x<=siz[wh];x++)f[wh][x]=ff[x],g[wh][x]=gg[x];
	}
	return;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);int s1,s2;
	for(int i=1;i<m;i++){
		read(s1);read(s2);
		add(s1,s2);add(s2,s1);
	}
	solve(1,0);
	for(int i=1;i<=m;i++)printf("%lld\n",(f[1][i]+g[1][i])%mod);
	
	return 0;
}
```

---

