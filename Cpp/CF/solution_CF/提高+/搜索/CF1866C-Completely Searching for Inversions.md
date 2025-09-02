# Completely Searching for Inversions

## 题目描述

给定一个有 $ N $ 个结点的有向无环图。结点 $ i $ 的出度为 $ S_i $。结点 $ i $ 的第 $ j $ 条出边指向 $ L_{i, j} $，边权为 $ W_{i, j} \text{ } (0 \le W_{i, j} \le 1) $。给出的图保证从结点 $ 1 $ 出发可以到达所有结点。

给定初始为空的数组 $ Z $。

定义函数 $ \texttt{dfs} $ 如下：

```cpp
// 以结点 i 为起点进行 dfs
void dfs(int i) {
    // 遍历 i 的每条出边
    for(int j = 1; j <= S[i]; j++) {
        Z.push_back(W[i][j]); // 将当前边的边权加入数组 Z 的末尾
        dfs(L[i][j]); // 从下一个结点继续 dfs
    }
}
```

请注意，以上函数并没有记录经过的结点，所以有些结点可能被经过不止一次。

在主函数中，程序调用了一次 $ \texttt{dfs(1)} $，得到了一个只包含 $ 0 $ 和 $ 1 $ 的数组 $ Z $。请你求出数组 $ Z $ 的逆序对数。

由于答案可能很大，你只需要输出答案对 $ 998 \text{ } 244 \text{ } 353 $ 取模的值。

## 样例 #1

### 输入

```
5
2
4 0
3 1
0
1
2 0
2
3 1
5 1
0```

### 输出

```
4```

# 题解

## 作者：c1ampy (赞：7)

因为每个结点的经过次数可能不止一次，所以数组 $ Z $ 的长度可能远超 $ N $，我们不能直接求出数组 $ Z $ 和其逆序对数。

既然不容易一次性求出答案，我们可以先求出部分答案再进行转化。

容易发现，对于一个结点 $ u $，无论 $ \texttt{dfs(u)} $ 被执行多少次，这行代码向数组 $ Z $ 添加的元素序列都是一定的。因此，对于一个结点，在第一次遍历到它时，我们可以记录一些有关的信息，在之后遍历到这个结点时，我们只需通过这些信息推算其对答案的贡献，

设 $ S_u $ 为执行一次 $ \texttt{dfs(u)} $ 所产生的边权序列，$ dp_u $ 为 $ S_u $ 的逆序对数，$ cnt_{u, i} $ 为 $ S_u $ 中数字 $ i $ 的个数，$ v $ 为结点 $ u $ 的出边所指向的结点，$ w_{u \to v} $ 为从结点 $ u $ 指向结点 $ v $ 的边的边权。

当 $ w_{u \to v} = 0 $ 时，可知 $ w_{u \to v} $ 会和已经被加入 $ S_u $ 的所有 $ 1 $ 构成逆序对，在答案递推过程中有
$$
dp_u \gets dp_u + cnt_{u, 1} \left(w_{u \to v} = 0\right)
$$

在 $ \texttt{dfs(v)} $ 执行完毕后，不仅 $ S_v $ 本身作为 $ S_u $ 的子序列会对 $ dp_u $ 产生贡献，而且 $ S_v $ 中的 $ 0 $ 还会和原先的 $ S_u $ 中的 $ 1 $ 组成逆序对，故有
$$
dp_u \gets dp_u + dp_v + cnt_{u, 1} \times cnt_{v, 0}
$$

通过递推得到 $ dp_1 $，我们即可在 $ \mathcal{O}(N) $ 的时间内解决问题。

代码如下：
```cpp
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; std::cin >> n;
	std::vector<std::vector<std::pair<int, int>>> edge(n);
    for (int u = 0, outd; u < n; ++u) {
        std::cin >> outd;
        for (int i = 0, v, w; i < outd; ++i) {
            std::cin >> v >> w, --v;
            edge[u].push_back(std::make_pair(v, w));
        }
    }

	const int mod = 998244353;
	std::vector<bool> vis(n);
    std::vector<std::vector<int>> cnt(n, std::vector<int>(2));
	std::vector<int> dp(n);
	auto solve = [&](const int u, const auto &self) -> void {
		vis[u] = true;
		for (const auto [v, w] : edge[u]) {
			if (!w) dp[u] = (dp[u] + cnt[u][1]) % mod;
			++cnt[u][w];

			if (!vis[v]) self(v, self);
			
			dp[u] = (dp[u] + dp[v] + (long long)cnt[v][0] * cnt[u][1]) % mod;
			for (int i = 0; i <= 1; ++i)
				cnt[u][i] = (cnt[u][i] + cnt[v][i]) % mod;
		}
	};
	solve(0, solve);

    std::cout << dp[0] << std::endl;

    return 0;
}
```


---

## 作者：YangRuibin (赞：1)

# 思路构建
本题要求路径上边权组成的逆序对，其实就是对于每个 $1$ 求出它后面 $1$ 的个数。大思路是倒着 dp 记录对于每个点 $i$ 它的子路径中经过的 $0$ 的个数 $n0_i$ 和 $1$ 的个数 $n1_i$ 以及子路径的逆序对数 $na_i$~~（谅我变量名起得不好）~~。

# 转移方程推导
前置说明：令 $son_i$ 为 $i$ 的子节点集合，令 $dis_{i,j}$ 为 $i$ 与 $j$ 之间所连边的边权。

对于 $n0_i$ 与 $n1_i$，因为依题意会依次遍历每个子节点的子路径，所以转移方程如下。
$$
n0_i = \sum_{j \in son_i} n0_j + (!dis_{i,j})
$$
$$
n1_i = \sum_{j \in son_i} n1_j + dis_{i,j}
$$
关键是 $na_i$ 的计算。为了方便理解，我先放上一张图。
![](https://cdn.luogu.com.cn/upload/image_hosting/rtre3up8.png)

上图列出了 $na_i$ 的 3 种类别，对它们求和即可。

# 一些细节
1. 在 dfs 时,要求的“前几个子路径 $0$ 的个数总和”可以内化为当前还没算完的 $n0_i$。
2. 如果用链式前向星存图，因为链表本身会反一下，所以按输入顺序加边即可。

# 代码
因为码量少，而且主要变量名与前面说的相吻合，~~就不加注释了~~。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,M=2e5+5,mod=998244353;
int n,head[N],tot,n0[N],n1[N],na[N],v[N];
struct node{
	int to,dis,next;
}edge[M];
void add(int from,int to,int dis)
{
	++tot;
	edge[tot].to=to;
	edge[tot].dis=dis;
	edge[tot].next=head[from];
	head[from]=tot;
}
void dfs(int x)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to,dis=edge[i].dis;
		if(!v[to])v[to]=1,dfs(to);
		n1[x]+=n1[to]+dis;n1[x]%=mod;
		na[x]+=na[to]+dis*n0[to]%mod+(n1[to]+dis)*n0[x]%mod;na[x]%=mod;
		n0[x]+=n0[to]+(!dis);n0[x]%=mod;
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1,x,l,w;i<=n;i++)
	{
		scanf("%lld",&x);
		for(int j=1;j<=x;j++)
			scanf("%lld%lld",&l,&w),add(i,l,w);
	}
	dfs(1);
	printf("%lld",na[1]);
	return 0;
}
```

---

## 作者：Lily_White (赞：1)

## 题意简述
执行 DAG 上的 DFS 算法（但不记录是否已经访问），经过边时记录边权，求最终得到的序列的逆序对数。

## 思路分析
首先，得到的序列可能非常长。同时，由于边权只能是 $0$ 或 $1$，这就提示我们本题中的逆序对可能不是按照传统的方法来计数的。

遇到这种情况，很多时候可以通过计算贡献来累计答案，我们这次也来试一试。一个点如果连出一条边权为 $1$ 的边，那么一旦经过了它，它对后面经过的边权为 $0$ 的边就都造成 $1$ 的贡献。

同时我们注意这样的一个性质：**一个点不论何时被经过，它会向最终得到的序列中加入的那些量是不会变的。** 这就提示我们可以运用记忆化的思想，把它的贡献记录下来。

我们定义 `cnt[0/1][i]` 表示从 $i$ 开始执行 DFS，连出的边权是 $0/1$ 的个数。这就完成了我们的记忆化过程。

接着，如果当前点开始有 $a$ 个 $1$，下一个点开始有 $b$ 个 $0$，那么贡献就是 $ab$，这样，我们就可以用 DAG 上记忆化搜索的方式来解决这个问题。

## 参考代码
```cpp
void madd(ll &x, ll y) { x = (x + y) % MOD; }
void dfs(int u) {
    vis[u] = true;
    for (auto [v, w] : g[u]) {
        if (!w) {
            madd(dp[u], cnt[1][u]);
        }
        cnt[w][u]++;
        if (!vis[v]) dfs(v);
        madd(dp[u], dp[v]);
        madd(dp[u], cnt[0][v] * cnt[1][u] % MOD);
        madd(cnt[0][u], cnt[0][v]);
        madd(cnt[1][u], cnt[1][v]);
    }
}
void Main() {
    int n;
    rd(n);
    repn(i, n) {
        int m;
        rd(m);
        while (m--) {
            int v, w;
            rd(v, w);
            g[i].emplace_back(v, w);
        }
    }
    dfs(1);
    cout << dp[1] << endl;
}
```

## 补充知识
代码中用到的 ```for (auto [v, w] : g[u])``` 是 C++17 中新增的**结构化赋值**语法。可以很方便地“解开”一个 pair 或其他类型的数据结构。~~但是，请注意 C++17 在当前的 NOI 系列活动中不可用。~~经提醒，由于 NOI Linux 的 gcc 版本足够高，结构化赋值可能可用。但请务必检查是否编译成功再使用。

---

## 作者：myster1ous (赞：0)

## 题解：CF1866C Completely Searching for Inversions

### 题目大意

给定一个有向无环图，运行以下代码：

```cpp
void dfs(int u);

std::vector<int> z;

int main() {
    dfs(1);
    return 0;
}

void dfs(int u) {
    for (int j = 1; j <= S[i]; j++) {
        z.push_back(W[i][j]);
        dfs(L[i][j]);
    }
}
```

求问：$z$ 之中有多少个逆序对？

#### 数据范围

- $2 \leqslant n \leqslant 10^5$；
- $0 \leqslant \text{S}_i \leqslant n - 1$；
- $0 \leqslant \sum \text{S}_i \leqslant 2 \times 10^5$；
- $1 \leqslant \text{L}(i,j) \leqslant n$；
- $0 \leqslant \text{W}(i,j) \leqslant 1$；
- 保证图中无重边，无环，从 $1$ 号点出发可以到达所有点；
- 答案对 $998,244,353$ 取模。

### 思路

#### 朴素做法

首先，我们肯定不能直接用题面的代码模拟后求出 $z$ 再求逆序对，因为在有向无环图中虽然不会死循环，但是点有可能被访问多次。

上面的代码是关于 $n$ 指数级别的，例如对于如下的图：

```cpp
    1
   / \
  2-->3
     / \
    4-->5
       / \
      6-->7  
        ... 
```

假如只有 $1 \sim 7$ 的 $4$ 层：
- 如果从 $5$ 开始 `dfs` 访问的节点就是 `5 6 7 7`，我们记这为 $s_1$；
- 如果从 $3$ 开始 `dfs` 访问的节点就是 `3 4 s1 s1`，我们记这为 $s_2$；
- 如果从 $1$ 开始 `dfs` 访问的节点就是 `1 2 s2 s2`，我们记这为 $s_3$；

$$
\begin{aligned}
s_1 & = 2^2\\
s_2 & = 2^3 + 2^1\\
s_3 & = 2^4 + 2^2 + 2^1\\
s_4 & = 2^5 + 2^3 + 2^2 + 2^1\\
\dots & \\
s_n & = 2^{n + 1} + 2^{n} - 1
\end{aligned}
$$

总复杂度是 $\mathcal{O}(2^n \times \log{2^n}) = \mathcal{O}(n \times 2^n)$ 的，显然过不了。

#### 优化

我们发现，同一个点被多次访问加入到 $z$ 中的数据**完全相同**，所以我们可以记忆化搜索：

- 记 $\text{dp}_u$ 表示以 $u$ 为起始节点的总逆序对数量。
- 答案即为 $\text{dp}_1$。
- 我们可以把整个以 $u$ 为起始节点插入到 $z$ 数组的数据构成逆序对分类：
  - 第一种逆序对的两个元素都在某一个 $\text{L}(u,i)$ 中。
  - 第二种逆序对的两个元素在不同的 $\text{L}(u,i)$ 中。
  - 第三种由 $\text{W}(u,i)$ 构成的逆序对。
- 我们考虑先统一计算方式：每一个插入的 $1$ 产生的逆序对的数量就是在这个 $1$ 的后边还将要插入的 $0$ 的数量。
- 因此，我们的搜索顺序就必须和原题的搜索顺序严格相反。
- 然后，让我们分类讨论不同种逆序对：
  - 第一种：$\sum \text{dp}_{\text{L}(u,i)}$。
  - 第二种：$\sum \text{one}_{\text{L}(u, i)} \times \text{currentzero}$。
  - 第三种：$\sum \text{W}(u,i) \times \text{currentzero}$。
- 我们不仅需要维护答案，还需要维护以 $u$ 为开头搜索出来会在 $z$ 中加多少个 $0$ 和 $1$，即 $\text{zero}_u$ 和 $\text{one}_u$。
- $\text{currentzero}$ 就是在这条边之前加入了多少个 $0$。

综上所述，我们对于每个点最多搜索一次，总时间复杂度 $\mathcal{O}(n + m)$，可以通过本题。

```cpp
#include <bits/stdc++.h>
#define int long long

const int maxn = 100010;
const int mod = 998244353;

int n, s[maxn];
std::vector<std::pair<int, int>> graph[maxn];

struct solveresult {
    int answer;
    int cnt[2];

    solveresult(int c0=0, int c1=0, int ans=0) {
        this->answer = ans;
        this->cnt[0] = c0;
        this->cnt[1] = c1;
    }
} dp[maxn];

solveresult solve(int x) {
    if (dp[x].answer != -1) return dp[x];

    solveresult ans(0, 0, 0);
    
    std::vector<solveresult> ress;
    for (int i = 0; i < s[x]; i++) {
        ress.push_back(solve(graph[x][i].first));
        ans.answer += ress.back().answer;
        ans.answer %= mod;
        ans.cnt[0] += ress.back().cnt[0];
        ans.cnt[1] += ress.back().cnt[1];
        ans.cnt[graph[x][i].second] += 1;
        ans.cnt[0] %= mod;
        ans.cnt[1] %= mod;
    }
    int zeros = 0;
    for (int i = s[x] - 1; i >= 0; i--) {
        ans.answer += ress[i].cnt[1] * zeros % mod; 
        ans.answer %= mod;
        zeros += ress[i].cnt[0];
        zeros += (graph[x][i].second == 0); 
        zeros %= mod;
        ans.answer += zeros * graph[x][i].second % mod;
        ans.answer %= mod;
    }

    return dp[x] = ans;
}

signed main() {
    std::cin.tie(0);
    std::cin.sync_with_stdio(0);
    
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];

        for (int j = 1; j <= s[i]; j++) {
            int u, v;
            std::cin >> u >> v;
            graph[i].emplace_back(u, v);
        }
    }

    for (int i = 1; i <= n; i++) dp[i] = solveresult(-1, -1, -1);

    std::cout << solve(1).answer << std::endl;
    return 0;
}
```

由于洛谷 CF RMJ 炸了，所以附上 CF AC [记录](https://codeforces.com/contest/1866/submission/304650873)。

---

