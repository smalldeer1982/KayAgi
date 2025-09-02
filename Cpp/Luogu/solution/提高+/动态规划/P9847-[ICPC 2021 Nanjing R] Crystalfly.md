# [ICPC 2021 Nanjing R] Crystalfly

## 题目描述

派蒙正在一棵树上抓晶蝶，这是一种提瓦特中特殊的蝴蝶。树是由 $n$ 个顶点和 $(n - 1)$ 条无向边组成的连通图。

![](https://cdn.luogu.com.cn/upload/image_hosting/awi9prsr.png)

初始时，第 $i$ 个顶点上有 $a_i$ 只晶蝶。当派蒙到达一个顶点时，她可以立即抓住该顶点上的所有剩余晶蝶。然而，晶蝶很胆小。当派蒙到达一个顶点时，所有相邻顶点上的晶蝶都会受到惊扰。对于第 $i$ 个顶点，如果晶蝶在第 $t'$ 秒开始时首次受到惊扰，它们将在 $(t' + t_{i})$ 秒结束时消失。

在第 $0$ 秒开始时，派蒙到达顶点 $1$ 并在第 $1$ 秒开始前停留在那里。然后在接下来的每一秒开始时，她可以选择以下两种操作之一：
- 移动到当前顶点的一个相邻顶点，并在下一秒开始前停留在那里（如果目的地的晶蝶将在该秒结束时消失，她仍然可以抓住它们）。
- 在当前顶点停留到下一秒开始前。

计算派蒙在 $10^{10^{10^{10^{10}}}}$ 秒内可以抓住的最多晶蝶数量。

## 说明/提示

对于第一个样例测试用例，按照以下策略进行：
- 在第 $0$ 秒
  - 派蒙到达顶点 $1$；
  - 派蒙抓住 $1$ 只晶蝶；
  - 顶点 $2$ 和 $3$ 的晶蝶受到惊扰。
- 在第 $1$ 秒
  - 派蒙到达顶点 $3$；
  - 派蒙抓住 $100$ 只晶蝶。
- 在第 $2$ 秒
  - 派蒙到达顶点 $1$；
  - 顶点 $2$ 的晶蝶消失。
- 在第 $3$ 秒
  - 派蒙到达顶点 $2$；
  - 顶点 $4$ 和 $5$ 的晶蝶受到惊扰。
- 在第 $4$ 秒
  - 派蒙到达顶点 $5$；
  - 派蒙抓住 $10000$ 只晶蝶；
  - 顶点 $4$ 的晶蝶消失。

对于第二个样例测试用例，最佳策略与第一个样例测试用例相同。顶点 $2$ 的晶蝶计划在第 $3$ 秒结束时消失（而不是第 $2$ 秒），这使得派蒙可以抓住它们。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
5
1 10 100 1000 10000
1 2 1 1 1
1 2
1 3
2 4
2 5
5
1 10 100 1000 10000
1 3 1 1 1
1 2
1 3
2 4
2 5
```

### 输出

```
10101
10111
```

# 题解

## 作者：Stone_Xz (赞：15)

## [传送门：[ICPC2021 Nanjing R] Crystalfly](https://www.luogu.com.cn/problem/P9847)

~~你说得对，但我不玩原神捏 QWQ~~

## 简要题意：

> 给定一棵 $n$ 个节点的树，每个节点上都有给定数量的晶蝶。每一秒可以移动到相邻的点并拿走这个点的晶蝶。当到达一个点 $u$ 时，与它相邻的点 $v$ 的晶蝶将会在 $t_v$ 秒后逃走。求最多能抓到的晶蝶数量。

## 思路分析：

我们不妨画一个最简单的树，来思考一下这题。

![](https://cdn.luogu.com.cn/upload/image_hosting/hqrlnjhu.png)

通过简单思考可以发现，假设当前节点为 $cur$，则如果对于 $cur$ 的子节点 $nxt$，$t_{nxt} < 3$，那么如果去了别的 $cur$ 的儿子节点，$nxt$ 的晶蝶就绝对抓不到了。

但是，在 $t_{nxt} = 3$ 的情况下，还有一种新的抓法：

![](https://cdn.luogu.com.cn/upload/image_hosting/6doaqwzu.png)

可以先到另一个儿子节点去，再**返回**到 $nxt$。

让我们总结一下：设当前节点为 $cur$，有两种抓晶蝶的方案：

 - 情况一：不返回 $cur$：只选一个儿子节点为方向去。
 
 - 情况二：返回 $cur$：如果子节点 $nxt$ 的 $t_{nxt} = 3$，可以先走到 $cur$ 别的儿子节点，再通过返回 $cur$ 走过去。
 
 
**以当前节点 $cur$ 为起点能抓到的最多晶蝶数，取决于以 $cur$ 的子节点 $nxt$ 为起点能抓到的最多晶蝶数，考虑树形 DP。**
 
## DP状态：

首先，有两个简单但重要的结论：

 - 当走到了点 $cur$，$cur$ 肯定没了。

 - 当走到了点 $cur$，$cur$ 的子节点会跑，但孙子节点完全不受影响，一直停着不动，**可以随时返回来抓**。
 
 当我们想返回时（即情况二），我们首先走到了 $i$，然后返回 $cur$，最后去点 $j$，此时点 $i$ 的子节点都跑了，后面我们来取的时候，为了方便更新，设计二维 DP 状态：
 
  - $dp[i][0]$ 表示以 $i$ 为根的子树，即当前起点为 $i$，$i$ 的子节点都逃走了，能抓到的最多晶蝶数量。
  
   - $dp[i][1]$ 表示以 $i$ 为根的子树，即当前起点为 $i$，$i$ 的子节点都还在，能抓到的最多晶蝶数量。
   
## 状态转移：

> 当前节点：$cur$，当前节点的儿子节点：$nxt$。

我们对于上文提到的两种情况分别考虑：

 1. 不返回 $cur$：只能选一个儿子节点去。
 
   	- 因为到了 $cur$ 后，$cur$ 的所有孙子节点不受影响，可以随时去抓，不用考虑，到时候再回来抓就行了。所以 $dp[cur][0]$ 和 $dp[cur][1]$ 都应该加上所有 $dp[nxt][1]$ 的和 $sum$（即 $cur$ 的儿子跑了，孙子却能抓）。
 
  	- $dp[cur][1]$：$cur$ 的儿子节点会跑，显然选择晶蝶数量最大的儿子节点去。
    
  	 - ```dp[cur][1] = sum + maxi_nxt; // 此处 maxi_nxt 是最大的 val[nxt]```
     
   	- $dp[cur][0]$：$cur$ 的儿子节点跑路了，但孙子节点都还能随便去，就是 $sum$。
    
    - ```dp[cur][0] = sum;```
 
 2. 返回 $cur$：如果子节点 $nxt$ 的 $t_{nxt} = 3$，可以通过返回过去。
 
  	- 过程：首先走到了 $i$，然后返回 $cur$，最后去点 $j$。
 
 	- 首先，我们确定要返回的点 $j$，肯定选 $cur$ 满足 $t_{nxt} = 3$ 的晶蝶数最大的子节点。可以想象成去掉以 $i$ 为根的子树后（因为要返回），选择最优的一个点去，与上文 $dp[cur][1]$ 不返回 $cur$ 的更新策略一样。
    
   	- ~~前方连珠炮！！！~~
    
   	- 枚举所有 $i$，对与每个 $i$，如果选择返回到其他节点，能抓到最大晶蝶数量 $tmpans$ 为：
    
   	- 首先到达 $i$，$tmpans = tmpans + val[i]$。
    
   	- $cur$ 的孙子都不会被影响，以后可以随便去抓，$tmpans = tmpans + sum$。
    
   	- 但是 $i$ 的子节点会跑，所以 $tmpans = tmpans - dp[i][1]$。
    
   	- 但是但是 $i$ 的子节点跑了，$i$ 的孙子节点还能去（~~逐渐离谱~~），此时 $dp[i][0]$ 终于派上用场，$tmpans = tmpans + dp[i][0]$。
    
   	- OK，现在返回 $cur$，无事发生。
    
   	- 最后到达 $j$，$tmpans = tmpans + val[j]$。
    
   	- 但是但是但是，有可能 $i = j$，所以为了应对这种情况，还要维护一个备选的 $j$，即 $cur$ 满足 $t_{nxt} = 3$ 的晶蝶数**次大**的子节 $j2$。如果出现这种情况，则返回 $j2$ 而不是 $j$。
   
   	- 但是但是但是但是，有可能 $j2$ 不存在，那就不返回了！到了 $cur$ 之后啥也不干了。（这样走好像没屁用，但是我们强制必须返回，所以就当凑数了~）
    
   	- 对于每个 $tmpans$，取最大的，并尝试更新 $dp[cur][1]$，如果情况二更优，则用情况二。
    
~~真是一点都不恶心呢 ○( ＾芬芳＾)っ~~

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, T, dp[N][2], val[N], t[N];
vector<int> nbr[N], g[N]; 

void dfs(int cur, int fa)
{
	dp[cur][0] = dp[cur][1] = 0;
	
	int sum = 0, maxi_nxt = 0;
	// 注意 maxi_nxt 设为 0，否则如果 cur 是叶子节点就凉了 
	
	for(auto nxt : nbr[cur])
	{
		if(nxt == fa)
			continue;
		dfs(nxt, cur);
		
		// 最大的子节点 
		maxi_nxt = max(maxi_nxt, val[nxt]);
		
		// cur 的子节点的晶蝶都逃走了，但 cur 的孙子节点可以随时去取，对应 dp[nxt][1] 
		sum += dp[nxt][1];
	}
	dp[cur][0] = sum;
	dp[cur][1] = sum + maxi_nxt; // 所有孙子可以随便取，但儿子只能选一条路 
	
	if(g[cur].size() == 0) // 没有 t = 3 的儿子，可以结束 
		return ; 
		
	// 有 t = 3 的儿子，还有别的方法
	
	int max1 = -2e18, max2 = -2e18, maxi = -2e18;
	// 最大值、次大值、情况二最优解 
	int max1id = 0, max2id = 0;
	// 最大值下标、次大值下标 
	
	for(auto nxt : g[cur]) // 计算 max1 和 max2 
	{
		if(nxt == fa)
			continue;
		if(val[nxt] > max1)
		{
			max2 = max1;
			max2id = max1id; // 传给次大值 
			max1 = val[nxt];
			max1id = nxt;
		}
		else if(val[nxt] > max2)
		{
			max2 = val[nxt];
			max2id = nxt;
		}
	}
	for(auto nxt : nbr[cur]) // 枚举返回前去的点 
	{
		if(nxt == fa)
			continue;
		if(nxt == max1id) // 要返回的儿子刚好是最大的 t = 3 的子节点，只能去次大点 
		{
			if(max2id == 0) // 没有次大点，不走了 
				maxi = max(maxi, val[nxt] + sum - dp[nxt][1] + dp[nxt][0]);
			else            // 有次大点 
				maxi = max(maxi, val[nxt] + sum - dp[nxt][1] + dp[nxt][0] + max2); 
		}
		else // 返回去最大的儿子 
			maxi = max(maxi, val[nxt] + sum - dp[nxt][1] + dp[nxt][0] + max1);
	}
	dp[cur][1] = max(maxi, dp[cur][1]); // 第二种情况：返回 
	return ;
}

void work()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> val[i];
	for(int i = 1; i <= n; i++)
	{
		cin >> t[i];
		nbr[i].clear(); // 顺便把两个 vector 清空 
		g[i].clear();
	}
	for(int i = 1; i <= n - 1; i++)
	{
		int x, y;
		cin >> x >> y;
		
		// 记录能返回的点 
		if(t[x] == 3) g[y].push_back(x);
		if(t[y] == 3) g[x].push_back(y); 
		
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	dfs(1, 0);
	cout << dp[1][1] + val[1] << "\n"; // 注意 dp[1][1] 并不包含 val[1] 
	return ;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--)
		work();
	return 0;
}
// 码量感人 QWQ 
```

---

## 作者：JiuZhE66666 (赞：5)

**[更好的阅读体验](https://www.cnblogs.com/pure4knowledge/p/18019563)**

# 前景导入
当 $t\in [1,2]$ 时，本题如何求解？

答：树形 dp。

设 $f[i]$ 为以 $i$ 为根的树，根节点的晶蝶已消散且儿子节点的晶蝶还未被惊动，能获得的最大晶蝶数。

则有状态转移方程 $f[i]=(\sum f[u])+\max(a[u])$，其中 $u$ 为 $i$ 的儿子。

最终的答案即为 $f[1]+a[1]$。

# 划向更深处
当 $t=3$ 时，特殊点在哪？

我可以在踏入儿子节点后，再返回根节点，然后踏入 $t=3$ 的节点，这样的决策存在着可能的更大值。

设此时踏入的儿子节点为 $v$，$g[i]$ 为以 $i$ 为根的树，根节点的晶蝶和儿子节点的晶蝶均已消散，能获得的最大晶蝶数。

则可能的更大值为 
$f[i]=(\sum f[u])-f[v]+g[v]+a[v]+a[q]$，其中 $q \neq v$ 且 $q$ 为所有 $t=3$ 的儿子节点中 $a$ 最大的。

# Code
```
#define ll long long
#include<bits/stdc++.h>
using namespace std;

vector<ll> E[100005];
ll g[100005];
ll f[100005];
ll t[100005];
ll a[100005];

inline void read(ll &x) {
    x = 0;
    ll flag = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-') flag = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    x *= flag;
}

inline void write(ll x) {
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

void ss(ll now, ll fa) {
    ll max1=0, max1_i, max2=0, max2_i;

    ll add=0;
    for(auto next: E[now]) {
        if(next == fa) continue;

        ss(next, now);

        g[now] += f[next];
        add = max(add, a[next]);

        if(t[next] == 3) {
            if(a[next] > max1) {
                max2 = max1;
                max2_i = max1_i;
                max1 = a[next];
                max1_i = next;
            } else if(a[next] > max2) {
                max2 = a[next];
                max2_i = next;
            }
        }
    }

    f[now] = g[now] + add;

    for(auto next: E[now]) {
        if(next == fa) continue;
        if(next != max1_i) {
            f[now] = max(f[now], g[now] - f[next] + g[next] + a[next] + max1);
        } else {
            f[now] = max(f[now], g[now] - f[next] + g[next] + a[next] + max2);
        }
    }
}

int main() {
    ll N;
    read(N);
    while(N--) {
        ll n;
        read(n);
        for(ll i=1; i<=n; i++) {
            read(a[i]);
            E[i].clear();
            f[i] = 0;
            g[i] = 0;
            t[i] = 0;
        }

        for(ll i=1; i<=n; i++) read(t[i]);

        for(ll i=1; i<n; i++) {
            ll x, y;
            read(x); read(y);

            E[x].push_back(y);
            E[y].push_back(x);
        }

        ss(1, 0);

        write(f[1]+a[1]);
        putchar('\n');
    }
    return 0;
}


```

---

## 作者：Genshineer (赞：4)

## P9847 [ICPC2021 Nanjing R] Crystalfly

~~你说得对，但是刻晴更可爱捏~~

### 翻译

给定一个 $n(1\le n\le10^5)$ 个节点的树，每个节点上有 $a_i$ 只晶蝶。派蒙最初在 $1$ 号节点，并获得 $1$ 号节点的所有晶蝶，接下来每一秒她可以移动到相邻的节点上并获得节点上的所有晶蝶，但是当她每到达一个节点 $u$ 后，对于每个与 $u$ 相邻的节点 $v$，节点 $v$ 上的的晶蝶会在 $t_v(1\le t_v\le3)$ 秒内消失，在 $t_v$ 秒后再到达节点 $v$ 将无法获得节点上的晶蝶。现在需要你求出最多可以获得的晶蝶数。

### 分析

观察到特殊数据 $t_i\le3$，不难想到只有两种情况:

- 走进节点 $u$ 的一棵子树后放弃其他子树，转化成和原问题相同的子问题。
- 若 $t_i=3$ 则可以进入一个节点后再退出并进入另一棵子树，转化成子问题。

因此考虑树上 DP。

定义 $f_{u,0/1}$ 为遍历以 $u$ 为根的整棵子树且 $u$ 点的子节点的晶蝶**是否**消失的情况下所能获得的最大晶蝶数量。记与 $u$ 相邻的非父亲节点中 $t_i=3$ 的节点晶蝶数量的最大值和次大值（若存在，不存在特判即可）分别为 $max1,max2$。

如果当前节点不存在 $t_i=3$ 的节点，那么 $f_{u,0}=\sum\limits_{v\in son_u}f_{v,1},f_{u,1}=(\sum\limits_{v\in son_u}f_{v,1})+\max(a_v)$。

如果当前节点存在 $t_i=3$ 的节点，那么通过画图观察不难发现，记所有子节点的 $f_{v,1}$ 的和 $\sum\limits_{v\in son_u}f_{v,1}$ 为 $sum$，$f_{u,0}$ 结果不变，$f_{u,1}=\max(f_{v,0}+a_v+sum-f_{v,1}+max1,f_{v,0}+a_v+sum-f_{v,1}+max2)$。

这样最后的结果就变成了 $f_{1,1}+a_1$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1e5 + 5;
int f[maxn][2], a[maxn], TestCase, t[maxn], n;
vector<int> G[maxn], g[maxn];

inline void dfs(int u, int fa) {
	int maxx, res;
	maxx = res = 0;
	f[u][0] = f[u][1] = 0;
	
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		res += f[v][1];
		maxx = max(maxx, a[v]);
	}
	f[u][0] = res, f[u][1] = res + maxx;
	if (g[u].size()) {
		int maxx1, maxx2, maxid1, maxid2;
		maxx1 = maxx2 = -2e18;
		maxid1 = maxid2 = 0;
		for (auto v : g[u]) {
			if (v == fa) continue;
			if (maxx1 < a[v]) {
				maxx2 = maxx1;
				maxid2 = maxid1;
				maxx1 = a[v];
				maxid1 = v;
			}
			else if (maxx2 < a[v]) {
				maxx2 = a[v];
				maxid2 = v;
			}
		}
		maxx = -2e18;
		for (auto v : G[u]) {
			if (v == fa) continue;
			if (v == maxid1) {
				if (maxid2 == 0) maxx = max(maxx, a[v] + f[v][0] + res - f[v][1]);
				else maxx = max(maxx, a[v] + f[v][0] + res - f[v][1] + maxx2);
			}
			else maxx = max(maxx, a[v] + f[v][0] + res - f[v][1] + maxx1);
		}
		f[u][1] = max(maxx, f[u][1]);
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> TestCase;
	while (TestCase--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> t[i];
		for (int i = 1; i <= n; i++) G[i].clear(), g[i].clear();
		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			G[u].emplace_back(v), G[v].emplace_back(u);
			if (t[v] == 3) g[u].emplace_back(v);
            if (t[u] == 3) g[v].emplace_back(u);
		}
		dfs(1, 1);
		cout << a[1] + f[1][1] << "\n";
	}
	return 0;
}
```

### Feedback

不知道是不是造数据的时候数据生成的问题，在判断相邻两边是否是 $t=3$ 的点时：

```cpp
if (t[v] == 3) g[u].emplace_back(v);
if (t[u] == 3) g[v].emplace_back(u);
```

与

```cpp
if (t[v] == 3) g[u].emplace_back(v);
```

都可以通过本题。

显然后一种写法只有在 $u$ 始终为 $v$ 的根节点的时候才有正确性。

~~严重怀疑是不是 generator 采用了向前随机挂点的方法。~~

---

## 作者：Brilliant11001 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/P9847)

[更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18345484)

~~甘雨可爱捏~~

### 题目大意：

给定一棵有 $n$ 个节点的树，第 $i$ 个节点上有 $a_i$ 只晶蝶，现在从 $1$ 号点开始走，每走到一个点，获得该点的晶蝶但会惊动相邻点的晶蝶，第 $i$ 个节点上的晶蝶被惊动后会在 $t_i$ 后飞走，求问能获得最大晶蝶数量。

数据范围：$n\le 10^5, 1\le a_i\le 10^9, 1\le t_i\le 3$。

### 思路：

很明显是树形 dp。

从条件 $1\le t_i\le 3$ 入手，这个条件非常重要，因为它意味着晶蝶被惊动后很快就会飞走。

有多快？假如当前走到一个节点 $i$，然后立马返回了，那么 $i$ 的子节点一定全飞走了，就算有的子节点 $v$ 的 $t_v = 3$ 还能拿到，但这一定不是最优解（能一步拿到为什么要折返走三步？）。

所以可以分析出几种行走方式：

1. 走到节点 $i$，然后走到它的某个子节点处，其他子节点全部飞走；
2. 走到节点 $i$，然后走到它的某个子节点 $v_1$ 处，立即返回，走到另一个 $t = 3$ 的子节点 $v_2$ 处，其余子节点全部飞走，$v_1$ 的子节点也全部飞走。

根据以上分析，我们可以设计出两种状态：

设 $f(i, 0)$ 表示当前走到点 $i$，$i$ 的蝴蝶已经飞走但子节点还在，我们在以 $i$ 为根的子树中继续抓蝴蝶最多能抓住几只蝴蝶。

$f(i, 1)$ 表示当前走到点 $i$，然后立马折返回去，即拿到 $i$ 的蝴蝶，但子节点全部飞走，这种情况下最多能抓住几只蝴蝶。

发现 $1$ 的状态是可以由 $0$ 的状态转移到的：

$$f(i, 1) = a_i + \sum\limits_{j\in \text{subtree(i)},j\ne i}f(j, 0)$$

含义就是：第 $i$ 个点的蝴蝶能抓到，但各个子树的根上的蝴蝶都飞走了。

接下来就只用考虑 $f(i, 0)$ 怎么计算了。

考虑上面描述的两种行走方式：

设点 $i$ 的所有子节点 $j$ 的 $f(j, 0)$ 之和为 $sum$，即：

$$sum = \sum\limits_{j\in \text{subtree(i)},j\ne i}f(j, 0)$$

对于方式 $1$，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/qfyuuifd.png)

我们要加上所有子节点 $j$ 的 $f(j, 0)$，然后加上走向的那么子节点的蝴蝶数。

状态转移方程为：

$$f(i, 0) = sum + \max\limits_{j\in \text{subtree(i)},j\ne i}a_j$$


对于方式 $2$，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/1mehkabq.png)

我们要选出两棵子树来走，其他都是 $f(j, 0)$。

状态转移方程为：

$$f(i, 0) = sum + \max\limits_{j\in \text{subtree(i)},j\ne i}\{f(j, 1) - f(j, 0)\} + \max\limits_{k\in \text{subtree(i)},k\ne i,k\ne j,t_k = 3}\{a_k\}$$

**只考虑 $t = 3$ 的 $k$，不然来不及抓该点的蝴蝶。**

朴素思考，要枚举 $j,k$ 分别求最大值，时间复杂度为 $O(n^2)$，TLE。

其实本质上就是求除去一个子结点 $j$，剩下的子节点的最大值，因为 $j$ 必须要枚举，所以就优化找 $k$ 的过程即可。

可以预处理出子节点中蝴蝶数量的最大值、次大值以及它们分别是哪个子节点。这样的话，在枚举 $j$ 时若 $j$ 为最大值所在的那个子节点，就选次大值；否则选最大值，优化掉一层循环。

最后答案即为 $f(1, 0) + a_1$。

综上所述，两种行走方式的转移都是 $O(n)$ 的，所以整个做法的时间复杂度为 $O(n)$。

$\texttt{Code:}$

```cpp
#include <vector>
#include <iostream>

using namespace std;

const int N = 100010;
typedef long long ll;
typedef pair<ll, int> PLI;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int T, n;
vector<int> e[N];
int a[N], t[N];
ll f[N][2];

void dfs(int u, int fa) {
    ll sum = 0;
    int maxx = 0;
    for(auto v : e[u]) if(v != fa) {
        dfs(v, u);
        sum += f[v][0];
        maxx = max(maxx, a[v]);
    }
    f[u][0] = sum + maxx;
    //以上是走法一
    PLI maxx1 = {-inf, 0}, maxx2 ={-inf, 0};
    for(auto v : e[u]) if(v != fa && t[v] == 3) {
        PLI now = {a[v], v};
        if(maxx2 < now) maxx2 = now;
        if(maxx1 < maxx2) swap(maxx1, maxx2);
    }
    //以上是预处理最大值和次大值
    for(auto v : e[u]) if(v != fa) {
        ll tmp = sum + f[v][1] - f[v][0];
        if(v == maxx1.second) tmp += maxx2.first;
        else tmp += maxx1.first;
        f[u][0] = max(f[u][0], tmp); 
    }
    //以上是走法二
    f[u][1] = sum + a[u];
}

void solve() {
    for(int i = 1; i <= n; i++) e[i].clear();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &t[i]);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(1, -1);
    printf("%lld\n", f[1][0] + a[1]);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：紊莫 (赞：3)

首先显然是一个树形 DP。  

然后考虑 $t$ 的限制，当儿子 $t\le 2$ 时，假设我们到了当前节点 $u$，也就意味着我们一旦下去了，别的儿子的蝴蝶就会消失（来回至少需要 $2$ 的时间），换言之我们只能选择一个儿子。这个部分比较简单，考虑 $t=3$ 的情况，也就是我们存在一种转移，是到某个儿子去一下，然后赶紧回来到别的儿子再去一下。  

**注意**：当我们到达了某个儿子的时候，这个节点的儿子，也就是当前节点的孙子节点已经开始了倒计时，也就意味着我们无法在回来后取到孙子节点的权值。  

于是我们考虑记录这样的一个信息 $f_{u,0/1}$，分别表示以当前 $u$ 节点为根的子树中**儿子全不选**所能得到的最大权值，和以当前 $u$ 节点为根的子树中**自己不选**所能得到的最大权值。容易可以得到 $f_{u,0}=\sum f_{i,1},i\in son_u$。  

为了实现转移，我们需要记录子节点中的最大值和次大值，这样才能找到最优的转移，而又要按照 $t=3$ 进行分类，很是繁琐，~~我赛时写了一万年~~。所以下面的部分参考了知乎 @严格鸽 的部分处理方法。  

因为此题没有要求线性做法，所以我们可以维护一个 ``multiset``（注意权值可能相同），来代替直接维护满足 $t=3$ 中的最大和次大。转移方程不算太烦，第一个是简单的，注意到 $f_{u,1}=f_{u,0}+\max(v_{son})$，重点看第二个，假设我们现在钦定对于一个子节点 $i$ 进行转移，首先计算除了当前儿子，其他子树的答案是不变的，那么显然是 $f_{u,0}-f_{i,1}$，对于到达 $i$ 产生的贡献呢？就是 $f_{i,0}+a_i$，就是 $a_i$ 是能取到的，但是 $i$ 的儿子都是取不到的，因为我们还要再回来找一个 $t=3$ 的儿子。这个时候维护的 ``multiset`` 就可以方便的找到答案了，但是有一个比较显然的问题是，我们取出的最大值可能是 $i$ 自己，怎么办呢？直接在找最大值前把 $a_i$ 删除，之后再加入即可。

最后输出的答案是 $f_{1,1}+a_1$，注意这个和我们上面计算到达 $i$ 产生的贡献是不一样的，因为我们并不要求根节点的儿子不能选。

---

## 作者：MutU (赞：2)

### [原题传送门](https://www.luogu.com.cn/problem/P9847)
**这篇题解和原神没有任何关系捏**
## 题意阅读
> 给定一棵点权树，每一秒可以从当前节点移动至相邻的节点并累加点权。当某个点 $u$ 被访问后，它的每一个儿子节点 $v$ 的点权会分别在 $t_v$ 秒后变为 $0$。求从点 $1$ 开始能获得的最大点权和。

## 初步思考
- 注意到 $t_i$ 的范围只有 $1\sim3$。

- $t_i=1$ 的情况。显然，我们只要到达了点 $u$，就只能摘到一个儿子节点上的晶蝶了（其它都跑了）。略加思考容易想到用简单的树形 dp 求解。设 $f_u$ 表示从点 $u$ 出发，不算点 $u$ 本身，最多能够摘到的晶蝶数量。有 $f_u=(\sum{f_v})+\max(a_v)$。其中 $v$ 是 $u$ 的儿子。

- $t_i=2$ 的情况。考虑到达了节点 $u$，选择一个儿子 $v$ 下去。若想再回到节点 $u$，必然再消耗一秒。这样的话回来只是白亏了点 $v$ 子树上的晶蝶，不予考虑。因此仍然只能摘到一个儿子节点上的晶蝶。状态转移方程同上。

## 深入探究
让我们想想 $t_i=3$ 与上述情况有什么区别。

- 对于一个 $t_u=3$ 的节点 $u$，存在一种不同的方案。那就是**先自父亲节点下到某个兄弟节点 $v$，再回到父亲，最后下到节点 $u$**。这么做能够同时摘到点 $v$ 和 $u$ 上的晶蝶。

那么此时我们可以在原方程上加上这个点 $u$ 的权值。但是原本先到的那个儿子点 $v$ 已经到过了，于是它的儿子都跑了，应该在原本的值上减去 $f_v$，加上点 $v$ 的儿子都消失后的贡献。

所以我们可以设一个二维的 $f_{i,0/1}$，分别表示点 $u$ 的儿子跑了或没跑时，从它出发，能够摘到的最大晶蝶数。

所以对于节点 $u$，若它有至少一个 $t_v=3$ 的儿子 $v$，就可以一次枚举两个儿子，其中一个儿子 $v_0$ 的 $t_{v_0}=3$。按照上述操作更新最大值就行了......

**但是这样的做法会被卡成接近 $n^2$，是不够优秀的**

考虑是否有必要逐对枚举两个儿子：

- 假设我们已经确定其中一个儿子 $v_1$ 作为先从父亲 $u$ 到达的节点。

- 此时我们需要找到另外一个节点 $v_0$，使得最后的答案尽可能大。回顾答案的计算过程，我们发现，既然已经确定 $v_1$，答案的大小就只跟 $v_0$ 的点权有关了。

- **也就是说，只要预先找到点权最大且 $t_{v_0}=3$ 的儿子就行了！**

- 唯一的例外就是，这个点权最大的儿子也可以作为先从父亲 $u$ 到达的儿子。可以特判这个点权最大的儿子，不过我是选择维护第二大值。

- 至此，我们得到最终的状态转移方程。

核心代码如下：


```cpp
inline void dfs(int u,int fa){
	int maxv=-1,maxs=0,sum=0;
	int maxv0[2]={-1,-1},maxs0[2]={0,0};
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		sum+=f[v][0];
		maxs=max(maxs,a[v]);
		if(t[v]==3 && a[v]>maxs0[1]) maxv0[0]=maxv0[1],maxs0[0]=maxs0[1],maxv0[1]=v,maxs0[1]=a[v];//维护最大值和次大值 
		else if(t[v]==3 && a[v]>maxs0[0]) maxv0[0]=v,maxs0[0]=a[v];
	}
	f[u][0]=sum+maxs;
	f[u][1]=sum;
	if(maxv0[1]==-1) return; //若没有t=3的儿子 
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa || v==maxv0[1]) continue;
		f[u][0]=max(f[u][0],sum-f[v][0]+f[v][1]+a[v]+a[maxv0[1]]);
	}
	if(maxv0[0]==-1) return;
	f[u][0]=max(f[u][0],sum-f[maxv0[1]][0]+f[maxv0[1]][1]+a[maxv0[1]]+a[maxv0[0]]); //特判最大值作为先下去的节点的情况 
}
```

## Code


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100100;
vector <int> E[N];
int T;
int n,f[N][2],a[N],t[N];
inline void dfs(int u,int fa){
	int maxv=-1,maxs=0,sum=0;
	int maxv0[2]={-1,-1},maxs0[2]={0,0};
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		sum+=f[v][0];
		maxs=max(maxs,a[v]);
		if(t[v]==3 && a[v]>maxs0[1]) maxv0[0]=maxv0[1],maxs0[0]=maxs0[1],maxv0[1]=v,maxs0[1]=a[v];//维护最大值和次大值 
		else if(t[v]==3 && a[v]>maxs0[0]) maxv0[0]=v,maxs0[0]=a[v];
	}
	f[u][0]=sum+maxs;
	f[u][1]=sum;
	if(maxv0[1]==-1) return; //若没有t=3的儿子 
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa || v==maxv0[1]) continue;
		f[u][0]=max(f[u][0],sum-f[v][0]+f[v][1]+a[v]+a[maxv0[1]]);
	}
	if(maxv0[0]==-1) return;
	f[u][0]=max(f[u][0],sum-f[maxv0[1]][0]+f[maxv0[1]][1]+a[maxv0[1]]+a[maxv0[0]]); //特判最大值作为先下去的节点的情况 
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			E[i].clear();
		} 
		for(int i=1;i<=n;i++) cin>>t[i];
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			E[u].push_back(v);
			E[v].push_back(u);
		}
		dfs(1,0);
		cout<<a[1]+f[1][0]<<'\n';
	}
	return 0;
}
```

注意这题有点小卡常，会卡掉链式前向星？~~（也可能是我太蒻了）~~

---

## 作者：O_v_O (赞：2)

# P9847 [ICPC2021 Nanjing R] Crystalfly 题解

## 翻译

洛谷的翻译不好，先提供个翻译

### 题目描述

派蒙正在一棵树上捉晶蝇，这些晶蝇是提瓦特特有的一种蝴蝶。这棵树是一个由 $n$ 个顶点和 $(n - 1)$ 条无向边组成的连通图。

初始时有 $a_i$ 只晶蝇在第 $i$ 个顶点上。当派蒙到达一个顶点时，她可以立即捉住该顶点上剩余的所有晶蝇。然而，晶蝇很胆小。当派蒙到达一个顶点时，相邻顶点上的晶蝇会被惊动。对于第 $i$ 个顶点，如果该顶点上的晶蝇在第 $t'$ 秒开始时第一次被惊动，它们将在第 $(t' + t_{i})$ 秒结束时消失。

在第 $0$ 秒开始时，派蒙到达顶点 $1$ 并在第 $1$ 秒开始前停留在那里。然后在接下来的每一秒开始时，她可以选择以下两种操作之一：
- 移动到当前顶点的一个相邻顶点并在下一秒开始前停留在那里（如果目的地的晶蝇将在那一秒结束时消失，她仍然可以捉住它们）。
- 在当前顶点停留不动，直到下一秒开始前。

计算在 $10^{10^{10^{10^{10}}}}$ 秒内派蒙最多可以捉到多少只晶蝇。

### 输入

有多个测试用例。输入的第一行包含一个整数 $T$ ，表示测试用例的数量。对于每个测试用例：

第一行包含一个整数 $n$（$1 \le n \le 10^5$），表示顶点的数量。

第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n$（$1 \le a_i \le 10^9$），其中 $a_i$ 表示第 $i$ 个顶点上的晶蝇数量。

第三行包含$n$个整数 $t_1, t_2, \cdots, t_n$（$1 \le t_i \le 3$ ），其中 $t_i$ 表示第 $i$ 个顶点上的晶蝇在被惊动后消失前的时间。

接下来的 $(n - 1)$ 行，第$i$行包含两个整数 $u_i$ 和 $v_i$（ $1 \le u_i, v_i \le n$ ），表示树中连接顶点 $u_i$ 和 $v_i$ 的一条边。

保证所有测试用例的 $n$ 的总和不超过 $10^6$ 。

## 分析

看到这道题目，我们首先不要想 $dp$ 怎么写，先想想搜索应该怎么写。

写搜索时，我们的第一反应就是枚举情况。我们就会想到有三种情况：

- 自己这个点上的金蝶不在了，子节点的金蝶也不在了

- 自己这个点上的金蝶不在了，子节点上的金蝶还在

- 自己这个点上的金蝶在，子节点上的金蝶也在

然而我们发现，第三种情况就是第二种情况再加上自己的节点上的金蝶数，所以我们可以不用考虑第三种情况。

然后，我们还要考虑一个问题，就是在一个子节点上抓完金蝶，然后再去另一个子节点上抓，然而可以达成这种情况只有一种可能，那就时 $t = 3$ 的时候，所以我们还要开一个 `vector` （或链式前向星）来存储这种特殊情况。

其实写道这里，我们的 $dp$ 大致就可以写出来了。

### 定义状态

$dp_{i, 0/1}$ 表示 自己这个点上的金蝶不在了，子节点的金蝶也不在（或在）的情况所最多能抓到多少只金蝶。

### 状态转移方程

- 初始状态：

$dp_{i, 0} = \sum_{v \in son_u}$

$dp_{i, 1} = \sum_{v \in son_u} + \max(val_v)$

- 如果存在 $t = 3$ 的情况（`!g.empty()`）

1. $v = maxid1$

$dp_{u, 1} = \max(val_v + dp_{v, 0} + \sum_{v \in son_u} - dp_{v, 1} + max2)$

2. $v \not= maxid1$

$dp_{u, 1} = \max(val_v + dp_{v , 0} + \sum_{v \in son_u} - dp_{v, 1} + max1)$

解释一下，$max1$ 是最大值，$max2$ 是次大值，$maxid1$ 和 $maxid2$ 是最大值和次大值的节点编号。

## _AC Code_

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int q, n, val[N], t[N], x, y, dp[N][2];
vector<int> e[N], g[N];
void dfs(int u, int fa){
  int sum = 0, maxi = 0;
  dp[u][1] = dp[u][0] = 0;
  for(auto v : e[u]){
    if(v == fa)
      continue;
    dfs(v, u);
    sum += dp[v][1];
    maxi = max(maxi, val[v]);
  }
  dp[u][0] = sum;
  dp[u][1] = sum + maxi;
  if(g[u].size()){
    int maxi1 = -1e18, maxi2 = -1e18, maxid1 = 0, maxid2 = 0;
    for(auto v : g[u]){
      if(v == fa)
        continue;
      if(maxi1 < val[v]){
        maxi2 = maxi1;
        maxid2 = maxid1;
        maxi1 = val[v];
        maxid1 = v;
      }else if(maxi2 < val[v]){
        maxi2 = val[v];
        maxid2 = v;
      }
    }
    int maxx = -2e18;
    for(auto v : e[u]){
      if(v == fa)
        continue;
      if(v == maxid1){
        maxx = max(maxx, val[v] + dp[v][0] + sum - dp[v][1] + maxi2);
      }else
        maxx = max(maxx, val[v] + dp[v][0] + sum - dp[v][1] + maxi1);
    }
    dp[u][1] = max(dp[u][1], maxx);
  }
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> q;
  while(q--){
    cin >> n;
    for(int i = 1;i <= n;i++)
      cin >> val[i];
    for(int i = 1;i <= n;i++)
      cin >> t[i];
    for(int i = 1;i < n;i++){
      cin >> x >> y;
      e[x].push_back(y);
      e[y].push_back(x);
      if(t[x] == 3)
        g[y].push_back(x);
      if(t[y] == 3)
        g[x].push_back(y);
    }
    dfs(1, -1);
    cout << dp[1][1] + val[1] << '\n';
    for(int i = 1;i <= n;i++){
      e[i].clear();
      g[i].clear();
    }
  }
  return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路
读题，观察数据范围发现 $1 \le t _ v \le 3$。如此小的范围说明肯定有可以利用的特性在里面。

假设当前结点 $u$ 有 $d$ 个子结点，分别为 $v _ 1 \sim v _ d$ 且 $t _ {v _ i} = 1$。考虑能抓到的晶蝶数，当到达 $u$ 后只能任选一个 $v$ 获得 $a _ v$ 只，其它晶蝶都会在到达 $v$ 时跑掉。因此对于一个结点的所有 $t = 1$ 的子结点要选 $a$ 最大的那个抓。

对于 $t = 2$ 的情况一样：$u \to v \to u$ 需要 $2$ 步才能返回父结点，此时其它晶蝶跑了。因此上面的结论可以扩充为对于所有 $t \le 2$ 的结点选最大的抓。

如果有 $t = 3$ 的结点，那么可以选两个结点 $v, w$ 且 $t _ w = 3$，按照 $u \to v \to u \to w$ 的顺序抓。这种情况就要仔细考虑了。

首先，对于 $t = 1, 2$ 的情况显然树形 dp。接下来设计状态，由于 $t = 3$ 的情况存在需要考虑一个结点的所有子结点的晶蝶是否存在，因此设 $f _ {u, 0}$ 表示在结点 $u$ 且 $u$ 的子结点的晶蝶全部飞走能获取的最大晶蝶数量，$f _ {v, 1}$ 表示在结点 $u$ 且 $u$ 的子结点的晶蝶全部存在能获取的最大晶蝶数量。有转移方程：
- $f _ {u, 0} = \sum f _ {v, 1}$，表示去所有子结点 $v$ 抓完一遍的数量；
- $f _ {u, 1} = f _ {u, 0} + \max a _ v$，表示在 $u$ 可以去子结点晶蝶数量最多的 $v$ 抓；
- $f _ {u, 1} = \max\{f _ {u, 1}, f _ {u, 0} - f _ {v, 1} + f _ {v, 0} + a _ v + a _ w\}$，表示要么不改变计划，要么去结点 $v$ 抓到 $a _ v$ 只后返回再去 $w$。显然 $w$ 是 $u$ 的子结点中 $a$ 最大的。

最终答案为 $f _ {1, 1} + a _ 1$。
### 代码
```cpp
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using pii = std::pair<int, int>;
using ll = long long;

constexpr int N = 1e5 + 1;
int T, n, a[N], t[N]; ll f[N][2];
std::vector<int> G[N];

void dfs(int u, int fa) {
    int maxv = 0;
    pii son[4];
    for (auto v : G[u]) {
        if (v == fa)
            continue;
		dfs(v, u);
        f[u][0] += f[v][1];
        maxv = std::max(maxv, a[v]);
        if (t[v] == 3) {
            son[3] = pii{a[v], v};
            if (son[2].first < son[3].first)
                std::swap(son[2], son[3]);
            if (son[1].first < son[2].first)
                std::swap(son[1], son[2]);
        }
    }
    f[u][1] = f[u][0] + maxv;
    for (auto v : G[u]) {
        if (v == fa)
            continue;
        f[u][1] = std::max(f[u][1], f[u][0] - f[v][1] + f[v][0] + a[v] + son[(v == son[1].second) + 1].first);
    }
}

signed main() {
    for (scanf("%d", &T); T--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            f[i][0] = f[i][1] = 0;
            G[i].clear();
        }
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i <= n; ++i)
            scanf("%d", t + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);
        printf("%lld\n", f[1][1] + a[1]);
    }
    return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：0)

简单题。

假设走到一个节点 $u$，那么有两种可能的决策：

- 直接往一个儿子 $v$ 走下去，拿到 $v$ 的晶蝶，其他儿子上的晶蝶消失。
- 选择一个儿子 $v$ 走下去并拿到这个节点的晶蝶，放弃 $v$ 的儿子上的所有晶蝶并立即返回至 $u$，然后再选择一个 $v'$ 满足 $t_{v'}=3$ 的儿子节点，从 $v'$ 走下去，其他儿子上的晶蝶消失。

显然可以考虑记录每棵子树内的答案 $dp_i$，并记录 $son_i$ 表示 $i$ 所有儿子的 $dp$ 之和。考虑每个决策的转移式。

- 选择第一个决策，答案为 $son_u+a_v$。
- 选择第二个决策，答案为 $son_u+a_v+son_v-dp_v+a_{v'}$。注意这里的 $son_v-dp_v$ 相当于对 $v$ 的儿子的选择的晶蝶总数，而选择这个决策会导致无法选择 $v$ 的儿子，故需要如此变换。

对每个 $u$，同时暴力枚举 $v,v'$ 显然不行，但不难发现 $a_{v'}$ 取最大时才最优，所以可以记录 $a_{v'}$ 的最大值，对应 $v'=id$。由于选择 $v=id$ 时 $v'$ 不能重复选择 $id$，所以还需对应记录次大值。

因为最终答案没有算上根节点的晶蝶个数，所以答案为 $dp_1+a_1$。

```cpp
void dfs(int u,int fa){
	int mx=0,id=0,mx2=0;
	for (auto v:e[u]){
		if (v==fa) continue;
		dfs(v,u),son[u]+=dp[v];
		if (t[v]==3){
			if (a[v]>=mx) id=v,mx2=mx,mx=a[v];
			else if (a[v]>mx2) mx2=a[v];
		}
	}
	for (auto v:e[u]){
		if (v==fa) continue;
		dp[u]=max(dp[u],son[u]+a[v]);
		if (v!=id) dp[u]=max(dp[u],son[u]+a[v]+son[v]-dp[v]+mx);
		else dp[u]=max(dp[u],son[u]+a[v]+son[v]-dp[v]+mx2);
	}
}
```

---

## 作者：modfisher (赞：0)

## 思路
容易发现，$t=1,2$ 的结点本质上是一样的——如果你没有立刻拿走上面的晶蝶，你就永远拿不到了。而对于 $t=3$ 的结点，可以先到它的兄弟结点拿晶蝶，然后再赶过来拿。

考虑设 $dp_x$ 表示，在不计算 $x$ 上含有的晶蝶的情况下，$x$ 的子树可以得到的最多晶蝶数量。并记 $sum_x$ 表示 $x$ 的所有儿子的 $dp$ 值之和。

对于结点 $x$，只有两种拿的策略：

- 立刻拿走某个儿子 $j$ 里的晶蝶，并继续沿着这棵子树走下去。

- 先拿走某个儿子 $j$ 的晶蝶，然后回到 $x$，再拿走某个 $t=3$ 的儿子 $k$ 的晶蝶，并继续沿着 $k$ 的子树走下去。

所以，有如下转移：

$$dp_x=\max(sum_x+\max_{j}a_j,sum_x+\max_{j\ne k}(a_j+sum_j-dp_j+a_k))$$

其中 $j$ 表示 $x$ 的某个儿子，$k$ 表示 $x$ 的某个满足 $t_k=3$ 的儿子。

$\max$ 中的第一项即为第一种策略，第二项是第二种策略。在此解释一下为什么要加上一个 $sum_j-dp_j$：如果先拿了 $j$，再去拿 $k$，则 $j$ 的所有儿子都不可能被拿到了，所以要用 $sum_j$ 替换 $dp_j$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e5 + 5;

ll a[maxn], dp[maxn], sum[maxn], pre[maxn], suf[maxn];
int t[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;

void merge(int u, int v){
	nxt[++ cnt] = head[u], to[cnt] = v, head[u] = cnt;
}
void dfs(int x, int f){
	dp[x] = sum[x] = 0;
	bool fl = false;
	ll mx = 0;
	for(int i = head[x]; i; i = nxt[i]){
		int j = to[i];
		if(j == f) continue;
		dfs(j, x);
		sum[x] += dp[j], fl = fl || t[j] == 3, mx = max(mx, a[j]);
	}
	dp[x] = sum[x] + mx;
	if(fl){
		int s = 0;
		for(int i = head[x]; i; i = nxt[i]){
			int j = to[i];
			if(j == f) continue;
			s ++;
			if(t[j] == 3) pre[s] = suf[s] = a[j];
			else pre[s] = suf[s] = 0;
		}
		pre[0] = suf[s + 1] = 0;
		for(int i = 1; i <= s; i ++) pre[i] = max(pre[i - 1], pre[i]);
		for(int i = s; i >= 1; i --) suf[i] = max(suf[i + 1], suf[i]);
		s = 0;
		for(int i = head[x]; i; i = nxt[i]){
			int j = to[i];
			if(j == f) continue;
			s ++;
			dp[x] = max(dp[x], sum[x] + max(pre[s - 1], suf[s + 1]) + a[j] + sum[j] - dp[j]);
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i ++) scanf("%d", &t[i]);
		for(int i = 1; i < n; i ++){
			int u, v;
			scanf("%d %d", &u, &v);
			merge(u, v), merge(v, u);
		}
		dfs(1, 0);
		printf("%lld\n", dp[1] + a[1]);
		for(int i = 1; i <= n; i ++) head[i] = 0;
		cnt = 0;
	}
}
```

---

