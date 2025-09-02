# PermuTree (easy version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are the constraint on $ n $ and the time limit. You can make hacks only if both versions of the problem are solved.

You are given a tree with $ n $ vertices rooted at vertex $ 1 $ .

For some permutation $ ^\dagger $ $ a $ of length $ n $ , let $ f(a) $ be the number of pairs of vertices $ (u, v) $ such that $ a_u < a_{\operatorname{lca}(u, v)} < a_v $ . Here, $ \operatorname{lca}(u,v) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ u $ and $ v $ .

Find the maximum possible value of $ f(a) $ over all permutations $ a $ of length $ n $ .

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

The tree in the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)One possible optimal permutation $ a $ is $ [2, 1, 4, 5, 3] $ with $ 4 $ suitable pairs of vertices:

- $ (2, 3) $ , since $ \operatorname{lca}(2, 3) = 1 $ and $ 1 < 2 < 4 $ ,
- $ (2, 4) $ , since $ \operatorname{lca}(2, 4) = 1 $ and $ 1 < 2 < 5 $ ,
- $ (2, 5) $ , since $ \operatorname{lca}(2, 5) = 1 $ and $ 1 < 2 < 3 $ ,
- $ (5, 4) $ , since $ \operatorname{lca}(5, 4) = 3 $ and $ 3 < 4 < 5 $ .

The tree in the third test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/d99652a679d9214ec6283dd777f9d3b7f1434695.png)The tree in the fourth test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/1b3604b93549da62e326378a176bbc03c4448da2.png)

## 样例 #1

### 输入

```
5
1 1 3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 2 2 1 5```

### 输出

```
7```

## 样例 #4

### 输入

```
4
1 1 1```

### 输出

```
2```

# 题解

## 作者：EuphoricStar (赞：8)

考虑局部贪心，假设我们现在在 $u$，我们希望 $u$ 不同子树中的 $(v, w), a_v < a_u < a_w$ 的对数尽量多。

我们实际上只关心子树内 $a_u$ 的相对大小关系，不关心它们具体是什么。如果 $u$ 只有两个儿子 $v, w$，我们可以让 $v$ 子树内的 $a$ 全部小于 $w$ 子树内的 $a$，这样 $u$ 作为 $\text{LCA}$ 的贡献是 $sz_v \times sz_w$，是最大的。

那么对于 $u$ 有多个儿子的情况，推广可知相当于把 $u$ 的儿子分成 $S, T$ 两个集合，最大化 $\sum\limits_{v \in S} sz_v \times \sum\limits_{v \in T} sz_v$。考虑做一个 $sz_v$ 的 01 背包，若能把 $sz_v$ 分成大小为 $x$ 的集合，$u$ 对答案的贡献是 $x \times (sz_u - 1 - x)$。取这个的最大值即可。

01 背包暴力做即可，根据树形背包的那套理论，每个点对只会在 $\text{LCA}$ 处被统计，所以时间复杂度 $O(n^2)$，[可以通过 E1](https://codeforces.com/contest/1856/submission/217388158)。

---

## 作者：Pengzt (赞：6)

[CF1856E1](https://www.luogu.com.cn/problem/CF1856E1)

发现题目的要求只需要相对的大小关系，考虑一个子树时，不妨令子树内部编号连续。类似于一个 dp，这样也可以更好地将信息由儿子转移到父亲。

设 $u$ 的孩子为 $v_1,v_2,\dots,v_k$。由于每棵子树内的编号是连续的，令以 $v_i$ 为根的子树的编号为 $[l_i,l_i+siz_{v_i}-1]$，$siz$ 为子树的大小。令 $l_i<l_j(i<j)$。

容易发现此时可以将 $v_1\sim v_k$ 分为两个互不相交集合 $\{S_1\},\{S_2\}$，令 $sum(\{S\})$ 表示 $\sum siz_{v_i} (i\in \{S\})$ 则这棵子树的答案显然为 $\max(sum(\{S_1\})\times sum(\{S_2\}))$

这是枚举每个值是否能够用某些 $siz$ 的值表示出来，然后判一下即可，这可以用背包解决。

时间复杂度：$\mathcal{O}(n^2)$

[评测记录](https://codeforces.com/contest/1856/submission/218452172)

---

## 作者：Hisaishi_Kanade (赞：4)

easy version 简单题，hard version 下头题。

其实等价于给每个点重新赋权值 $w_i$，使得 $w_u<w_{\text{lca}(u,v)}<w_v$。

很显然的对于某个节点 $i$，我们可以使得有一部分子树的 $w$ 全部小于 $w_i$，剩下的则全部大于 $w_i$，$w$ 是排列使得它不会有重复。

两类子树的节点个数和的乘积则是 $i$ 的贡献。我们发现 $i$ 的贡献算完之后这些子树就互不相干了，当前只需要最大化 $i$ 就行。

我们对子树大小进行可行性的背包，对于 $f[k]$ 为真能然后求最大的 $\sum {k\times{siz[i]-k}}$。这题 $n^2$ 都可以过直接从 $1$ 枚举到 $siz[u]$ 就可以了，其实从一半开始枚举就是对的。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
int t,n,i,j,k,l,r,ret,maxn,now,kk;long long ans;
const int N=5e4+5;
vector<int> e[N];
bool f[N];
int a[N],siz[N];
inline void dfs0(int u,int fa)
{
	siz[u]=1;
	if(e[u].empty())
	{
		siz[u]=1;return ;}
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
		dfs0(nxt,u);
		siz[u]+=siz[nxt];
	}
	return ;
}
inline void dfs1(int u,int fa)
{
	f[0]=true;
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
//		rep(j,0,siz[u])f[tot][j]=f[tot-1][j];
		req(j,siz[u],siz[nxt])
			f[j]|=f[j-siz[nxt]];
	}
//	printf("%d\n",u);
//	rep(i,1,n)printf("%d ",f[i]);
//	puts("");
	int bst=0;
	rep(i,1,siz[u])if(f[i])bst=max(bst,i*(siz[u]-1-i));
//	printf("%d %d %d\n",u,siz[u],bst);
	ans+=bst;
	memset(f,0,sizeof f);
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
		dfs1(nxt,u);
	}
	return ;
}
int main()
{
	ans=0;int x;
	scanf("%d",&n);
	rep(i,2,n)
	{
		scanf("%d",&x);
		e[x].emplace_back(i);
	}
	dfs0(1,0);
	dfs1(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：happybob (赞：3)

考虑对于每个点算贡献。设以其所有儿子为根的子树大小为 $sz_1, sz_2, \cdots, sz_k$。设和为 $s$，我们要求一个非空子集，设子集和为 $s2$。则贡献为 $s2 \times (s-s2)$。意味着 $s$ 这些点在排列中全部在这个点左边，其余的在右边。

感性理解可以发现，无论上述方案如何分配，都不会对以其他点为 LCA 的贡献产生影响。

所以我们要对每个前，求 $s2 \times (s-s2)$ 最大值。

考虑每个点做一次，朴素地 01 背包可以求出哪些点可以为子集和。显然 $s \leq 5000$。所以可以在 $O(n^2)$ 的时间复杂度内求出来，就做完了。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define int long long

const int N = 5005, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
vector<int> G[N];
long long ans = 0LL;
long long sz[N];

long long a[N];
bool canc[N];

void predfs(int u)
{
	sz[u] = 1;
	for (auto& j : G[u])
	{
		predfs(j);
		sz[u] += sz[j];
	}
}

void dfs(int u)
{
	int idx = 0;
	long long maxn1 = 0, maxn2 = 0, sum = 0, res = 0LL;
	for (auto& j : G[u])
	{
		a[++idx] = sz[j];
	}
	canc[0] = 1;
	for (int i = 1; i <= idx; i++)
	{
		sum += a[i];
		for (int j = sum; j >= a[i]; j--)
		{
			canc[j] |= canc[j - a[i]];
		}
		for (int j = 1; j <= sum; j++)
		{
			canc[sum - j] |= canc[j];
		}
	}
	for (int i = 1; i < sum; i++)
	{
		if (canc[i])
		{
			res = max(res, i * (sum - i));
			canc[i] = 0;
		}
	}
	for (int i = 0; i <= sum; i++) canc[i] = 0;
	ans += res;
	for (auto& j : G[u])
	{
		dfs(j);
	}
}

signed main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
		int fa;
		cin >> fa;
		G[fa].emplace_back(i);
	}
	predfs(1);
	dfs(1);
	cout << ans << "\n";
	return 0;
}
```


---

## 作者：出言不逊王子 (赞：2)

我们发现这棵树长得很像二叉查找树，所以我们考虑像一棵二叉查找树一样去填数。

具体地，我们假设一棵子树是一个节点，那么我们选择部分节点将一个区间分配进去，填到一半时给根节点赋权值 $x$，剩下的再给其他子树。

这样一来，在根节点产生的贡献就是 $(\sum_{v=\text{son}_u} sz_v[val_v<x])\times (\sum_{v=\text{son}_u} sz_v[val_v>x])$。

根据基本不等式，我们考虑希望让左右两边的部分尽量少。

所以我们现在要解决一个问题：

有 $n$ 个物品，每个物品有重量 $a_i$。你需要选出一些物品，使得选出的物品的重量和与未选的物品的重量和的差的绝对值最小。

这个背包是 $O(n^2)$ 的，然后就做完了。

---

## 作者：shinzanmono (赞：2)

# E1 - PermuTree (easy version)

由于是 Easy Version，先看数据范围，$n\leq5000$，说明 $O(n^2)$ 可过。

由于 $a$ 是一个排列，且给定的是一棵树，所以我们考虑在 $lca$ 上找性质，可以发现如果一棵子树对应的是排列中的一个连续区间的话，如果根节点的值为 $val$ 的话，那么这颗子树的贡献就是 $val(size-1-val)$。

我们让一整颗子树对于排列一个连续的区间，那么这样可取到最大值。

考虑让贡献值最大，设函数 $f(x)=x(C-x)$，其中 $C$ 为非负整数，则当 $x=\frac C2$ 时，$f(x)$ 有最大值。

回到问题，我们可以看出我们要让 $val$ 与 $\frac{size-1}2$ 尽可能地接近，且不超过 $\frac{size-1}2$。简化问题可得，选择一些子树，使得他们的大小和尽可能接近但不超过 $\frac{size-1}2$，这也是这道题目的核心。

对于选取一些总和尽可能接近但不超过 $x$ 的元素，我们可以考虑背包。

令每个子树的重量和价值均为他的大小，则我们求出背包大小为 $\frac{size+1}2$ 的最大值即可。

分析一下复杂度，首先我们对于树进行 DFS，到了每个结点，先更新这个节点的子树大小 $size$。然后跑一边背包，这样的话，每个节点进入背包一次，背包的大小是 $O(n)$ 的，故时间复杂度 $O(n^2)$，可以通过本题。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
const int sz=5010;
std::vector<int>graph[sz];
long long ans=0,f[sz];
int size[sz];
void dfs(int u){
    size[u]=1;
    for(int v:graph[u])dfs(v),size[u]+=size[v];
    long long cnt=0,sum=0;
    std::fill(f+1,f+size[u]+1,0);
    for(int v:graph[u])
        for(int j=size[u];j>=size[v];j--)
            f[j]=std::max(f[j],f[j-size[v]]+size[v]);
    ans+=f[size[u]-1>>1]*(size[u]-1-f[size[u]-1>>1]);
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    for(int i=2,f;i<=n;i++)
        std::cin>>f,graph[f].push_back(i);
    dfs(1);
    std::cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

~~这个 E1 好水啊，VP 的时候用了 8min 切了。~~

~~然后 E2 不会，就来水题解。~~

考虑对于每一个节点，考虑一个节点 $x$ 作为 lca 的情况，根据 $a_{x}$，可以把其它店的权值分成大于 $a_{x}$ 的和小于 $a_{x}$ 的。

下面这个贪心使显然的：在 $x$ 的同一棵子树内，子树内的权值和 $a_x$ 关系相同。简要证明一下：

> 在其它子树内的点确定的情况下，对于该子树内的点，如果大于 $a_x$ 的点较多，那么就选择小于 $a_x$ 的，用来和更多的点产生贡献；否则，就选择大于 $a_x$ 的。用调整法即可说明上述贪心正确。

补充一下，上面的贪心用到了我们只需要知道每一个点和其它点的相对关系，$a_x$ 的值可以不知道，只要知道 $a_x$ 排第几个即可。

既然可以这么贪心，那么，我们可以把 $x$ 的儿子代表的子树分成两个集合，$S_1$ 表示这些子树内的点 $y$ 满足 $a_y>a_x$，$S_2$ 表示这些子树内的点 $y$ 满足 $a_y<a_x$。

下面记 $sz_x$ 为 $x$ 子树的大小。那么，对于一个节点 $x$，它作为 lca 的贡献是 $\sum\limits_{a\in S_1}\sum\limits_{b\in S_2}sz_asz_b$。

可以统计哪些值是可以凑出来的，可以用 bitset 解决，之后扫一遍，取 $\max$ 计入答案即可。

[code](https://codeforces.com/contest/1856/submission/240193028)

---

## 作者：modfisher (赞：1)

## 思路
先贪一贪嘛。

对于任意一个节点 $x$，当它作为中间结点时，它的贡献即为 子树内比它小的节点个数 $\times$ 子树内比它大的节点个数。有没有一种方法可以使每一个节点的贡献最大化呢？

考虑这样一种做法：

对于每一个结点 $x$，把它的儿子分成两堆，一堆里面的所有儿子及其后代都比 $x$ 小，一堆都比 $x$ 大。容易发现这是可以做到的。这样问题就转换为了：

对于一些数 $a_1,a_2,\dots ,a_k$，构造集合 $A$ 和 $B$，使得 $A\cup B=\{1,2,\dots ,k\}$，$A\cap B=\varnothing$，满足 $\sum_{i\in A}a_i\times\sum_{i\in B}a_i$ 最大。

其中 $a_i$ 表示第 $i$ 个儿子的子树大小。

很容易发现，这要求 $\sum_{i\in A}a_i$ 和 $\sum_{i\in B}a_i$ 最接近，即都接近 $\frac{\sum_{i=1}^{k}a_i}{2}$。

这可以用一个背包解决。

然后就完事了。复杂度 $O(n^2)$。
## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 5e3 + 5;

vector<int> G[maxn];
int fa[maxn], siz[maxn], sons[maxn], dnt = 0;
ll ans = 0, dp[maxn];

void dfs1(int x){
	siz[x] = 1;
	for(int i = 0; i < G[x].size(); i ++){
		int j = G[x][i];
		dfs1(j);
		siz[x] += siz[j];
		sons[x] ++;
	}
}
void dfs2(int x){
	if(!sons[x]){
		return;
	}
	int up = (siz[x] - 1) / 2;
	for(int i = 0; i < G[x].size(); i ++){
		int j = G[x][i];
		for(int k = up; k >= siz[j]; k --){
			dp[k] = max(dp[k], dp[k - siz[j]] + siz[j]);
		}
	}
	ans += dp[up] * (siz[x] - dp[up] - 1);
	for(int i = 0; i <= up; i ++) dp[i] = 0;
	for(int i = 0; i < G[x].size(); i ++){
		int j = G[x][i];
		dfs2(j);
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 2; i <= n; i ++){
		int f;
		scanf("%d", &f);
		G[f].push_back(i);
		fa[i] = f;
	}
	dfs1(1);
	dfs2(1);
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：KingPowers (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1856E1)

简单题，但是赛时脑淤血地交了一发假的贪心，而且和 E2 难度差距过大。

不难发现子树之间的答案都是相互独立的，因此我们对于每个点分别求出以它为根的子树的最大答案，最后再累加就可以了。

考虑将构造排列 $a$ 的过程理解为给树上的点填数。假设当前点为 $u$，我们要做的事情其实类似于，将 $u$ 的若干个儿子所代表的子树划分为两组，一组填的数比填在 $u$ 的数小，另一组填的数比填在 $u$ 的数大。假设两组的点数分别为 $s_1,s_2$，那么这个分组方案对答案的贡献即为 $s_1\times s_2$。

不难发现我们可以直接对树上的每个点做一遍 01 背包（把儿子看成物品，价值为它的 $siz$），求出一组内可以有多少个点，然后枚举一组内的点数即可。

```cpp
int n,fa[N],siz[N],ans[N];
bool dp[N];
vector<int>g[N];
void dfs(int now){
	siz[now]=1;
	for(int to:g[now]) dfs(to),siz[now]+=siz[to];
	dp[0]=1;
	For(i,1,siz[now]) dp[i]=0;
	for(int to:g[now]) Rof(i,siz[now]-1,siz[to])
		dp[i]|=dp[i-siz[to]];
	For(i,0,siz[now]) if(dp[i]) ans[now]=max(ans[now],i*(siz[now]-1-i));
}
void Main(){
	cin>>n;
	For(i,2,n){
		cin>>fa[i];
		g[fa[i]].pb(i);
	}
	dfs(1);
	int res=0;
	For(i,1,n) res+=ans[i];
	cout<<res<<'\n';
}
```

别急，这样写看上去时间复杂度是 $O(n^3)$ 的。但是我们考虑均摊分析：每个点做 01 背包的复杂度是 $O(\text{儿子个数}\times n)$ 的，而所有点的儿子个数之和为 $n$，因此实际时间复杂度为 $O(n^2)$。

---

## 作者：eb0ycn (赞：0)

首先~~很难不~~发现，这题 $O(n^2)$ 可以过。

直接在树上考虑。类似于分治思想，假设子树内已经计算完，现在要考虑子树间的贡献。

如果这棵树是个二叉树，那么按照二叉搜索树的方法填一定是不劣的，因为任何一对兄弟都会产生贡献。

对于普通树，也用类似的方法。若当前考虑到子树 $u$，钦定 $u$ 一些儿子的子树点权都比根节点小，称为“左部点”，剩下的都比根节点大，称为“右部点”。若子树 $u$ 的大小为 $sz_{u}$，左部点的大小为 $x$，则对答案产生 $x \times (sz_{u}-1-x)$ 的贡献。由数学知识可知，当 $x = sz_{u}-1-x$，即 $x=\frac{sz_{u}-1}{2}$ 时贡献最大。 显然，我们可以用背包解决这个问题。（找到最大的不超过 $\lceil\frac{sz_u-1}{2}\rceil$ 的 $x$）

注意 bitset 的清空。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot,nxt[5000],to[5000],head[5001],u,sz[5001];
long long ans;
bitset<2501>f;
void add(int u,int v){nxt[++tot]=head[u],head[u]=tot,to[tot]=v;}
void dfs(int x){
	sz[x]=1;
	for(int i=head[x];i;i=nxt[i])dfs(to[i]),sz[x]+=sz[to[i]];
	f.reset(),f[0]=1;
	for(int i=head[x];i;i=nxt[i])f|=f<<sz[to[i]];
	for(int i=sz[x]>>1;i;--i)if(f[i]){
		ans+=1ll*i*(sz[x]-1-i);
		return;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i)scanf("%d",&u),add(u,i);
	dfs(1);
	return 0&printf("%lld",ans);
}
```

---

## 作者：foryou_ (赞：0)

假定当前在节点 $u$，它拥有两棵子树 $v,w$，此时 $u$ 是 $\operatorname{lca}(v,w)$。

我们一定可以构造出一个排列 $a$，使得所有满足 $i \in v$ 的节点 $i$ 和满足 $j \in w$ 的节点 $j$，有 $a_i<a_u<a_j$。

因此此时点 $u$ 对于答案的贡献即为 $size_v \times size_w$，其中 $size_u$ 表示节点 $u$ 的子树大小。

进一步推广，若节点 $u$ 拥有多棵子树，则考虑将 $u$ 的子树分成两个集合 $S,T$，最大化 $\sum_{i \in S} i \times \sum_{j \in T} j$。

我们考虑进行树上 01 背包，若能分成大小为 $x$ 的集合 $S$，则节点 $u$ 对于答案的贡献即为 $x \times (size_u-x)$。

时间复杂度 $O(n^2)$。[代码](https://codeforces.com/contest/1856/submission/224866894)。

---

## 作者：Drind (赞：0)

赛时没做出来的题。

我们考虑用一种类似中序遍历的方式给每个点编号，对于一颗子树，它的根暂且记作 $u$，那么 $u$ 的所有子树分成两半，分别是编号均小于 $u$ 的和编号均大于 $u$ 的。那么以 $u$ 为 $lca$ 的答案就是两半子树大小的乘积。

怎么分成两半呢？讲讲我的错误解法：我的做法是排序然后贪心的从大往小取，我当初真没看出来这有什么问题啊，但是构造反例很简单的，甚至不需要对拍，随便写一组答案就是错的，比如 $5,5,3,3,3$，我的贪心会分成 $5,3,3$ 和 $5,3$ 两组，但是事实上应该分成 $5,5$ 和 $3,3,3$。

这个问题我们考虑用动态规划解决，设 $f_i$ 代表和为 $i$ 的子集是否存在，那么递推式就是 $f_i=max(f_i,f_{i-a_j})$，其中 $a_j$ 代表第 $j$ 个子树大小。可以用 $O(n^2)$ 的复杂度解决这题。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=10010;
struct node{
	int to,nxt;
}edge[N];
int head[N],cnt;
int siz[N],ans[N];
int tmp[N];
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

void dfs(int u,int fa){
	int flag=0; siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==fa) continue;
		flag=1;
		dfs(v,u);
		siz[u]+=siz[v];
		ans[u]+=ans[v]; //递归处理子树大小和答案
	}
	if(flag){
		memset(tmp,0,sizeof(tmp)); tmp[0]=1;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to; if(v==fa) continue;
			for(int j=siz[u];j>=siz[v];j--) tmp[j]=max(tmp[j-siz[v]],tmp[j]);//递推式
		}
		int l=0;
		for(int i=siz[u]/2;i>=1;i--) if(tmp[i]){
			 l=max(l,i*(siz[u]-i-1)); break;
		}//枚举子集合的值是多少的时候值最大，贪心地从中间开始扫
		ans[u]+=l;
	}
}

int main(){
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int t; cin>>t;
		adde(i+1,t);
	}
	dfs(1,0);
	cout<<ans[1]<<endl;
}

```

---

