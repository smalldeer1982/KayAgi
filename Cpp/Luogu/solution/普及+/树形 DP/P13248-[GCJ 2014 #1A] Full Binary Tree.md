# [GCJ 2014 #1A] Full Binary Tree

## 题目描述

树是一种**连通且无环**的图。

**有根树**是一种特殊的树，它指定了一个特殊的点作为根。在有根树中，如果存在一条边连接 $X$ 和 $Y$，且 $X$ 到根节点的最短路径长度小于 $Y$ 到根节点的最短路径长度，那么我们称 $Y$ 是 $X$ 的**子节点**。

**满二叉树**是一种有根树，其中每个节点要么恰好有 $2$ 个子节点，要么没有子节点。

你将获得一棵含有 $N$ 个节点的树 $G$（节点编号为 $1$ 到 $N$）。你可以**删除任意数量的节点**，每当你删除一个节点，与其相连的边也会一并删除。你的目标是：通过删除尽可能少的节点，使得剩下的节点可以构成一棵**满二叉树**（以剩余节点中的某个点作为根）。


## 说明/提示

**样例说明**

- 在第一个样例中，如果将节点 $1$ 作为根，那么 $G$ 已经是一棵满二叉树，因此不需要做任何操作。

- 在第二个样例中，可以删除节点 $3$ 和 $7$，然后以节点 $2$ 为根，就能形成一棵满二叉树。

- 在第三个样例中，可以删除节点 $1$，然后以节点 $3$ 为根，构成一棵满二叉树（也可以选择删除节点 $4$，并将 $2$ 作为根，同样成立）。

## 限制条件

- $1 \leq T \leq 100$
- $1 \leq X_i, Y_i \leq N$
- 每个测试用例保证输入构成一棵合法的连通树

**小数据集（9 分）**

- 时间限制：~~60~~ 3 秒
- $2 \leq N \leq 15$

**大数据集（21 分）**

- 时间限制：~~120~~ 10 秒
- $2 \leq N \leq 1000$

翻译由 ChatGPT-4o 完成。

## 样例 #1

### 输入

```
3
3
2 1
1 3
7
4 5
4 2
1 2
3 1
6 4
3 7
4
1 2
2 3
3 4```

### 输出

```
Case #1: 0
Case #2: 2
Case #3: 1```

# 题解

## 作者：BaiBaiShaFeng (赞：2)

## 题意

> 给你一棵 $n$ 个节点的树，询问最少删多少节点才能搞出来一棵满二叉树。

## 分析

满二叉树，要么恰好有两个子节点，要么没有。对于一个节点，如果我们知道每个子树的信息，我们从其中选出两个较小的就好，于是自然而然考虑动态规划，这个似乎连转移方程都不需要。

我们设 $dp_i$ 表示子树 $i$ 行成满二叉树的最小删除数。

对于我们的点 $i$ 有两种选择，一种是全删了，一种是取两颗子树，全删了的答案显然是这个子树的大小，我们记录所有子节点，选出来前两优秀的就好了。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MN=3000;
struct Node{
    int nxt, to;
}node[MN];
int head[MN], tottt;
inline void insert(int u, int v){
    node[++tottt].to=v;
    node[tottt].nxt=head[u];
    head[u]=tottt; return;
}
int dp[MN], n, siz[MN];
void dfs(int u, int father){
    siz[u]=1; vector <int> tmp;
    for(int i=head[u];i;i=node[i].nxt){
        int v=node[i].to;
        if(v==father) continue; dfs(v,u);
        siz[u]+=siz[v]; tmp.push_back(v);
    }
    int cnttt=0, op1, op2;
    for(auto v:tmp) cnttt+=siz[v];
    op1=cnttt; op2=0x3f3f3f3f;
    if(tmp.size()>=2){
        vector <int> vals;
        for(auto v:tmp){
            vals.push_back(dp[v]-siz[v]);
        }
        sort(vals.begin(),vals.end());
        op2=cnttt+vals[0]+vals[1];
    }
    dp[u]=min(op1,op2);
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); int T; cin>>T;
    for(int t=1; t<=T; ++t){
        cin>>n; memset(head,0,sizeof(head)); tottt=0;
        for(int i=1; i<n; ++i){
            int u, v; cin>>u>>v;
            insert(u,v); insert(v,u);
        }
        int ans=0x3f3f3f3f;
        for(int root=1; root<=n; ++root){
            dfs(root, -1);
            ans=min(ans, dp[root]);
        }
        cout<<"Case #"<<t<<": "<<ans<<'\n';
    }
    
    return 0;
}

```

---

## 作者：MuktorFM (赞：2)

## 0. 闲话

最近在学习树形 DP，心血来潮，写一篇题解，顺便为我 9 月的 CSP 攒 rp。

评价：很~~水~~好的树形 DP 题。

---

## 1. 题意简述

很简单，就是给你一棵树，让你删除一些节点以及与它相连的边，使其成为一棵满二叉树。

题面中对于满二叉树的解释：满二叉树是一种有根树，其中每个节点要么恰好有 $2$ 个子节点，要么没有子节点。

---

## 2. 思路分析

存树采用邻接表。（也可以用链式前向星，不过本蒟蒻用邻接表习惯一些）

```cpp
vector<int> ve[1005];

for(int i = 1;i < n;i++){
    int u,v; cin >> u >> v;
    ve[u].push_back(v);
    ve[v].push_back(u);
}
```

由于满二叉树的根节点可能是任何节点，我们需要对每个点进行一次枚举。

接下来就是树形 DP 的过程了，新手建议仔细看。

关于状态定义：

对于每个节点 $now$，我们用 `dp[now]` 表示以当前节点为根的子树转换为满二叉树所需删除的最少节点数。

考虑状态转移：

作为叶子节点时：删除所有子节点，删除节点数为 $sz[now] - 1$。

```cpp
void dfs1(int now,int root){
  	sz[now] = 1;
  	for(auto i : ve[now]){
  		if(i == root) continue;
  		dfs1(i,now);
  		sz[now] += sz[i];
  	}
}
```

有两个子节点时：对于每个点 $i$，我们需要让 $dp[i] - sz[i]$ 尽可能小。（这个值越小则子树“性价比”更高）

因此我们每次选择两个子节点 $lson$ 和 $rson$，使：

$$
dp[lson] - sz[lson] + dp[rson] - sz[rson]
$$

尽可能小，此时删除：

$$
sz[now] - 1 + dp[lson] - sz[lson] + dp[rson] - sz[rson]

$$

个节点。

```cpp
void dfs2(int now,int root){
 	dp[now] = sz[now] - 1;
 	int minn = LLONG_MAX,minn2 = LLONG_MAX,cnt = 0;
 	for(auto i : ve[now]){
 		if(i == root) continue;
 		dfs2(i,now);
 		cnt++;
 		int w = dp[i] - sz[i];
 		if(w < minn){
 			minn2 = minn;
 			minn = w;
        }else if(w < minn2) minn2 = w;
    }
}
  ```

$dp[now]$ 取 $\min$ 即可。（注意计数 $cnt$ 需要大于等于 $2$ 才能证明它有两个子节点）

```cpp
if(cnt >= 2) dp[now] = min(dp[now],sz[now] - 1 + minn + minn2);
```

接下来对每个根节点 DFS 一遍，先计算子树大小 $sz$，再计算 $dp$ 的值，最小的 $dp$ 值即为答案。

由于有 $T$ 组数据，所以：

**多测不清空，爆零两行泪。**

~~[死亡记录](https://www.luogu.com.cn/record/225207784)~~

---

## 3. AC code

喜闻乐见的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
vector<int> ve[1005];
int sz[1005],dp[1005];
int ans = LLONG_MAX;
void dfs1(int now,int root){
	sz[now] = 1;
	for(auto i : ve[now]){
		if(i == root) continue;
		dfs1(i,now);
		sz[now] += sz[i];
	}
}
void dfs2(int now,int root){
	dp[now] = sz[now] - 1;
	int minn = LLONG_MAX,minn2 = LLONG_MAX,cnt = 0;
	for(auto i : ve[now]){
		if(i == root) continue;
		dfs2(i,now);
		cnt++;
		int w = dp[i] - sz[i];
		if(w < minn){
			minn2 = minn;
			minn = w;
		}else if(w < minn2) minn2 = w;
	}
	if(cnt >= 2) dp[now] = min(dp[now],sz[now] - 1 + minn + minn2);
}
signed main(){
	int T; cin >> T;
	for(int _ = 1;_ <= T;_++){
		cin >> n;
		for(int i = 1;i <= n;i++) ve[i].clear();
		for(int i = 1;i < n;i++){
			int u,v; cin >> u >> v;
			ve[u].push_back(v);
			ve[v].push_back(u);
		}
		int ans = n;
		for(int root = 1;root <= n;root++){
			for(int i = 1;i <= n;i++){
				sz[i] = 0;
				dp[i] = 0;
			}
			dfs1(root,0);
			dfs2(root,0);
			ans = min(ans,dp[root]);
		}
		cout << "Case #" << _ << ": " << ans << "\n";
	}
    return 0;
}
```

时间复杂度：$O(T\times N^2)$，AC。

[AC 记录](https://www.luogu.com.cn/record/225199204)

---

## 4. 拓展

对于本题来说，$N \le 10^3$，因此 $O(T \times N^2)$ 的时间复杂度是够用的。但对于更大的 $N$ 来说，我们需要[换根 DP](https://oi-wiki.org/dp/tree/#%E6%8D%A2%E6%A0%B9-dp)。

树上问题还有进阶，例如树上背包、树上贪心，请自学。

树形 DP 推荐练习：[P2018](https://www.luogu.com.cn/problem/P2018)、[P2014](https://www.luogu.com.cn/problem/P2014)、[P1272](https://www.luogu.com.cn/problem/P1272)

换根 DP 推荐练习：[P3478](https://www.luogu.com.cn/problem/P3478)、[P2986](https://www.luogu.com.cn/problem/P2986)、[CF1324F](https://www.luogu.com.cn/problem/CF1324F)

---

有问题欢迎随时在下面问我。当然如果你觉得这篇题解对你有帮助的话，留下一个关注再走哦。

---

## 作者：wangjingyaun (赞：1)

### 题意简述
#
对于一棵树，求要使它变成满二叉树，最少要删除多少节点。

> 满二叉树是一种有根树，其中每个节点要么恰好有 $2$ 个子节点，要么没有子节点
（这只是题目中的定义，实际满二叉树是除最后一层外必须拥有两个子节点）。

### 思路
#
#### 1、定义状态

  容易想到 $dp_u$ 表示以 $u$ 为根的子树成为满二叉树删除的最少节点数。$siz_u$ 表示以 $u$ 为根的子树大小。

#### 2、状态转移

对于节点 $u$，有两种情况：

一种是 $u$ 作为叶子节点，把子树全删了，即 $dp_u = siz_u-1$。

另一种是 $u$ 恰好有 $2$ 个子节点，即只保留两个子树，想要删除的最少的节点，就便必须保留两个最大的子树，使得 $dp_u=$ 其余的子树大小和。

对于节点 $v$，它的大小不是 $siz_v$，而是 $siz_v-dp_v$。

对于 $u$ 的两个最大的子树的大小 $f$ 和 $s$，有

- $dp_u=siz_u-1-f-s$

因为根节点的变化会导致答案变化，所以需要枚举所有根节点，统计最小值。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1003
int n,dp[N],siz[N];
vector<int> e[N];
inline void dfs(int u,int fa)
{
	siz[u]=1;
	int f=0,s=0,ch=0;
	//f：最大子树大小；s：次大子树大小；ch：儿子个数
	for(int v:e[u])if(v!=fa)
	{
		dfs(v,u);
		ch++;
		siz[u]+=siz[v];//计算本树大小
		int size=siz[v]-dp[v];//实际子树大小
		//更新最大、次大值
		if(size>f)
			s=f,f=size;
		else if(size>s)
			s=size;
	}
	dp[u]=siz[u]-1;//没有子节点的情况
	//因为e[u].size()中包含父节点，所以以儿子个数不是e[u].size()
	if(ch>=2)dp[u]=min(dp[u],siz[u]-1-f-s);//恰好有2个子节点
}
inline void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1,x,y;i<n;i++)
	{
		cin>>x>>y;
		e[x].push_back(y);	
		e[y].push_back(x);
	}
	int ans=INT_MAX;
	for(int rt=1;rt<=n;rt++)	
	{
		memset(dp,0,sizeof dp);
		dfs(rt,-1);
		ans=min(ans,dp[rt]);
	}
	printf("%lld\n",ans);
}
signed main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		printf("Case #%lld: ",i);
		solve();
	}
}
```

---

## 作者：liuchuliang666 (赞：0)

显然是树形 DP，注意到 $O(n ^ 2)$ 是可接受的，因此我们可以考虑对每个点为根 $O(n)$ 做一次 DP 而不需要换根 DP。

为了让删的最少，显然要留下最多。

令 $f_u$ 为在 $u$ 的子树中能形成的最大满二叉树。根据题中定义（请注意这与一般定义**不同!**），当 $u$ 没有两个子节点时，$f_u = 1$，否则 $f_u = f_{v_1} + f_{v_2} + 1$，其中 $f_{v_1}$ 和 $f_{v_2}$ 是 $\{f_v | v \in \text{son}(u)\}$ 中的非严格前两大。

然后就没有了，上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#endif
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val, len) memset(x, val, sizeof((x)[0]) * (int(len) + 1))
#define mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * (int(len) + 1))
#define Mst(x, val) memset(x, val, sizeof(x))
#define Mcp(from, to) memcpy(to, from, sizeof(from))
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define pbds __gnu_pbds
#define int int64_t
#define i128 __int128
#define vi vector<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define Add(a, b) ((a) = (((a) + (b)) % mod + mod) % mod)
#define Mul(a, b) ((a) = (((a) * (b)) % mod + mod) % mod)
#define add(a, b) (((a) += (b)) >= mod ? (a) -= mod : (a))
#define mul(a, b) (((a) *= (b)) %= mod)
constexpr int MAXN = 2e5 + 10, inf = 1e9, mod = 998244353, MAXV = MAXN << 2;
template <typename T> inline void chkmx(T &a, const T b) { a = a < b ? b : a; }
template <typename T> inline void chkmn(T &a, const T b) { a = a > b ? b : a; }
int lowbit(int x) { return x & (-x); }
int qpow(int a, int b)
{
    static int res;
    for (res = 1; b; b >>= 1, mul(a, a)) ((b & 1) && mul(res, a));
    return res;
}
int inv(int x) { return qpow(x, mod - 2); }
bool MST;
int n, f[MAXN];
vi e[MAXN];
void dfs(int u, int fa)
{
    int mx = 0, smx = 0;
    for (int v : e[u])
        if (v ^ fa)
        {
            dfs(v, u);
            if (f[v] > mx)
                smx = mx, mx = f[v];
            else
                chkmx(smx, f[v]);
        }
    if (!smx)
        f[u] = 1;
    else
        f[u] = smx + mx + 1;
}
int solve()
{
    cin >> n;
    rep(i, 1, n) e[i].clear();
    rep(i, 2, n, u, v) cin >> u >> v, e[u].eb(v), e[v].eb(u);
    int ans = 0;
    rep(i, 1, n) mst(f, 0, n), dfs(i, 0), chkmx(ans, f[i]);
    return n - ans;
}
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    int T;
    cin >> T;
    rep(i, 1, T) cout << "Case #" << i << ": " << solve() << endl;
    return 0;
}
```

---

