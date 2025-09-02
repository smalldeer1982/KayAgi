# Compressed Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

You can perform the following operation any number of times (possibly zero):

- choose a vertex which has at most $ 1 $  incident edge and remove this vertex from the tree.

Note that you can delete all vertices.

After all operations are done, you're compressing the tree. The compression process is done as follows. While there is a vertex having exactly $ 2 $  incident edges in the tree, perform the following operation:

- delete this vertex, connect its neighbors with an edge.

It can be shown that if there are multiple ways to choose a vertex to delete during the compression process, the resulting tree is still the same.

Your task is to calculate the maximum possible sum of numbers written on vertices after applying the aforementioned operation any number of times, and then compressing the tree.

## 样例 #1

### 输入

```
3
4
1 -2 2 1
1 2
3 2
2 4
2
-2 -5
2 1
7
-2 4 -2 3 3 2 -1
1 2
2 3
3 4
3 5
4 6
4 7```

### 输出

```
3
0
9```

# 题解

## 作者：Register_int (赞：11)

设 $dp_u$ 为 $u$ 子树内的答案，$v$ 为 $u$ 的儿子。先默认所有点都有父亲，那么 $u$ 儿子的删除情况有三种可能：

- 一个都不剩，答案为 $a_u$。
- 剩了一个，那么 $u$ 度数为 $2$ 会被压缩，答案为 $\max dp_v$。
- 剩了两个及以上，那么无事发生，选掉前两大后贪心地选非负贡献的儿子即可。

直接把所有儿子的 $dp_v$ 拉下来排序即可做到。接下来考虑如何统计答案：

- 全删光，答案为 $0$。
- 只剩下一个节点 $u$，答案为 $a_u$。
- 根 $u$ 的度数为 $1$，仅剩一个儿子，答案为 $a_u+\max dp_v$。
- 根剩下两个儿子，被缩掉了，答案为 $dp_v$ 的前两大之和。
- 根剩下不止两个儿子，强制选前三大后贪心选非负贡献的儿子即可。

时间复杂度 $O(n\log n)$，瓶颈在于排序。精细实现可做到 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;

int t, n; ll a[MAXN], dp[MAXN], ans;

vector<int> g[MAXN];

void dfs(int u, int fa) {
	ll x; vector<ll> d; dp[u] = a[u], ans = max(ans, dp[u]);
	for (int v : g[u]) {
		if (v == fa) continue; dfs(v, u), d.push_back(dp[v]);
		ans = max(ans, a[u] + dp[v]), dp[u] = max(dp[u], dp[v]);
	}
	sort(d.begin(), d.end(), greater<ll>());
	if (d.size() >= 2) {
		x = d[0] + d[1], ans = max(ans, x);
		for (int i = 2; i < d.size() && d[i] > 0; i++) x += d[i];
		dp[u] = max(dp[u], a[u] + x);
	}
	if (d.size() >= 3) {
		x = d[0] + d[1] + d[2];
		for (int i = 3; i < d.size() && d[i] > 0; i++) x += d[i];
		ans = max(ans, a[u] + x);
	}
}

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), ans = 0;
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1, u, v; i < n; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v), g[v].push_back(u);
		}
		dfs(1, 0), printf("%lld\n", ans);
	}
}
```

---

## 作者：nullqtr_pwp (赞：4)

换根可以做这题，但是没有必要。

题意：在 $n$ 个点的树上任取一个连通块，重复执行以下操作：找到一个度数为 $2$ 的点，删去这个点，并且将原先连接这个点的两个点连边，求最后剩下的点的点权之和最大值。

看上去就不好贪心，又是最优化问题，我们可以考虑 $dp$。
容易发现这个操作就是诈骗。它不会改变**所有点的度数（除了度数为 $\textbf{2}$ 的被删去）**。设这次度数为 $2$ 的点为 $u$，与之相邻的是 $v,w$，那么 $v,w$ 都是删一条后再添加一条，度数不变。

点权的计算方式，可以改成**所有点的点权和，减去度数为 $\textbf{2}$ 的点的点权和。**

直接令 $f[u][1/2/3]$ 表示以 $u$ 为根的连通块，$u$ 在连通块中的度数分别为 $1,2,>2$。对于 $f[u][1/3]$：$a_u$ 是要算入连通块点权和的。而 $f[u][2]$ 显然不能将 $a_u$ 算入。

直接逐个考虑子节点 $v$ 即可。考虑 $u$ 与 $v$ 相接的情况，会将 $v$ 的连通块合并到 $u$ 上，注意 $v$ 度数会 $+1$，所以 $f[v][1]$ 合并时要减去 $a_v$，$f[v][2]$ 合并时要加上 $a_v$（$v$ 的度数会分别变为 $2,3$），而 $f[u][3]$ 可以从 $f[u][2]$ 合并 $v$ 或者 $f[u][3]$ 合并 $v$ 或者啥都不干得来。对于 $u$ 度数为 $1$ 的情况直接算最大值即可。

时间复杂度 $O(n)$。
```cpp
void dfs(int u,int fa){
	dp[u][0]=a[u];
	vector<ll>vec;
	for(int v:g[u]) if(v^fa){
		dfs(v,u);
		ll val=max({a[v],dp[v][1]-a[v],dp[v][2]+a[v],dp[v][3]});
		ll A=max(dp[u][1],val),B=max(dp[u][2],dp[u][1]+val),C=max(dp[u][2]+val,dp[u][3]+max(val,0ll));
		chkmax(dp[u][1],A),chkmax(dp[u][2],B),chkmax(dp[u][3],C);
	}
	dp[u][1]+=a[u],dp[u][3]+=a[u];
	F(i,0,3) chkmax(ans,dp[u][i]);
}
```

---

## 作者：TruchyR (赞：3)

当时被学长拉上去讲的时候成功把所有人绕晕了。  

但是这种方法分类讨论会少一点。  

首先发现压缩过程就是把所有度数为 $2$ 的点删除。  

设 $f_i$ 为 $i$ **子树和 $i$ 连向父亲的边** 的答案。  

考虑如何更新 $f_i$：
1. 将儿子 $u$ 的 $f_u$ 加入计算，其中 $f_u$ 是未加入的最大的答案。  
2. 考虑点 $i$ 会不会被压缩：
    - 如果只有**一个**儿子的答案，那么点 $i$ 度数为 $2$，会被压缩。
    - 否则点 $i$ 度数不为 $2$，不会被压缩，计入答案。
3. 重复前两步，取最大值。

注意要从大到小贪心地把儿子的答案加入计算。  

那么我们要怎么更新真正的答案呢？  

设 $ans_i$ 为 $i$ **子树** 的答案。  

在更新 $f_i$ 时，一起更新 $ans_i$ 的步骤如下：  
1. 将儿子 $u$ 的 $f_u$ 加入计算，其中 $f_u$ 是未加入的最大的答案。  
2. 考虑点 $i$ 会不会被压缩：
    - 如果有**两个**儿子的答案，那么点 $i$ 度数为 $2$，会被压缩。
    - 否则点 $i$ 度数不为 $2$，不会被压缩，计入答案。
3. 重复前两步，取最大值。

在代码中这两个数组的计算可以放在一起。  

最终答案就是 $ans$ 的最大值。

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define MX 500005
#define int long long
#define INF 1000000000000000ll
using namespace std;
const int CHECK=0;int read();
int T,n,a[MX],f[MX],g[MX],x,y,res;
vector<int> v[MX],q[MX];
bool cmp(int X,int Y){return X>Y;}
void dfs(int t,int fa=-1){
	if(g[t]) return;
	for(auto i:v[t]){
		if(i==fa) continue;
		dfs(i,t);q[t].push_back(f[i]);
		//计算儿子的答案
	}
   sort(q[t].begin(),q[t].end(),cmp);
	f[t]=a[t];res=max(res,a[t]);//儿子都不选，答案就是 a[i]
	int ans=0,cnt=0;
	for(auto i:q[t]){
		cnt++;ans+=i;//从大到小加入计算
		f[t]=max(f[t],ans+(cnt!=1)*a[t]);
		res=max(res,ans+(cnt!=2)*a[t]);
	}
}
signed main(){
	T=read();while(T--){
		n=read();res=0;
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++){
			v[i].clear();q[i].clear();
			f[i]=-INF,g[i]=0;
		}
		for(int i=1;i<n;i++){
			x=read();y=read();
			v[x].push_back(y);
			v[y].push_back(x);
		}dfs(1);
		printf("%lld\n",res);
	}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：arrow_king (赞：1)

一道简单的树形 dp 题。

显然这个压缩操作不会改变其他点的度数，因此考虑 dp。看到联通块想到枚举联通块的根，最后再取 max。

又因为答案和根的度数有关，因此设状态 $dp_{u,0/1/2/3}$ 表示考虑 $u$ 子树且强制选 $u$ 时、$u$ 的度数为 $0$ / $1$ / $2$ / $3$ 以上 的最大和。特殊的是如果 $u$ 的儿子不够那么对应的 $dp$ 值为 $-\infty$。

考虑合并子树，注意到子树和子树之间没有影响，因此可以提前计算一个子树对父亲的最大贡献。方法是枚举当前点 $v$ 的度，再加上父亲 - 儿子边的额外度来计算。如果选择之前 $v$ 的度为 $1$，那么连接之后度为 $2$，需要删除；如果选择之前 $v$ 的度为 $2$，那么连接之后度为 $3$，需要再把 $v$ 救回来。综上我们写出计算公式
$$
ctr_v=\max\{dp_{v,0},dp_{v,1}-a_v,dp_{v,2}+a_v,dp_{v,3}\}
$$
那么转移方程是
$$
\begin{cases}
dp_{u,3}\leftarrow\max\{dp_{u,2}+a_u,dp_{u,3}\}+ctr_v\\
dp_{u,2}\leftarrow dp_{u,1}-a_u+ctr_v\\
dp_{u,1}\leftarrow a_u+ctr_v
\end{cases}
$$
三个式子按照顺序转移，不然会出现类似 01 背包循环顺序写挂一样类型的错误。最后答案自然是 $dp_{u,0/1/2/3}$ 的最大值。

时间复杂度是 $O(n)$。

```cpp
il void dfs(int u,int fa) {
	dp[u][0]=a[u],dp[u][1]=dp[u][2]=dp[u][3]=-INF;
	for(auto v:g[u]) {
		if(v==fa) continue;
		dfs(v,u);
		ll tmp=dp[v][0];
		if(g[v].size()>1) tmp=max(tmp,dp[v][1]-a[v]);
		if(g[v].size()>2) tmp=max(tmp,dp[v][2]+a[v]);
		if(g[v].size()>3) tmp=max(tmp,dp[v][3]);
		dp[u][3]=max(dp[u][3],max(dp[u][2]+a[u],dp[u][3])+tmp);
		dp[u][2]=max(dp[u][2],dp[u][1]-a[u]+tmp);
		dp[u][1]=max(dp[u][1],a[u]+tmp);
	}
}
```

---

## 作者：233L (赞：1)

**假如没有压缩操作**，那么直接树上 dp，令树根为 $1$，记 $f_u$ 表示以 $u$ 为根的子树的答案。

$f_u=a_u+\sum_v \max(f_v,0),ans=\max(0,\max_{i=1}^n f_i)$

**观察压缩操作**，发现其实就是 $2$ 度点没有贡献。所以修改以下上面的 dp，定义不变，我们认为 $u$ 有父亲（影响 $u$ 的度数）。

考虑转移，把 $f_v$ 降序排序，第 $i$ 大的记作 $arr_i$。然后对 $u$ 的度数分讨。

1. 度数大于 $2$，$a_u$ 有贡献，选儿子时贪心选所有正的，如果不够 $2$ 项再补齐。

2. 度数等于 $2$，$a_u$ 没有贡献，选儿子贪心选最大的。

3. 度数等于 $1$，只有 $a_u$。

这样就转移好了，有点细节，赛时调了好久 qwq。

然后是更新答案，其实和转移类似，只是此时 $u$ 没有父亲，不在赘述。

时间复杂度 $O(n \log n)$，如果实现精细应该可以做到 $O(n)$。具体细节见[代码](https://codeforces.com/contest/1901/submission/234098783)。

---

## 作者：mango2011 (赞：0)

来一发 $O(n)$ 做法。

我们观察到一个连通块“压缩”之后得到的权值就是所有度数不为 $2$ 的点的权值之和。因此，我们可以考虑树形 dp：

考虑 $u$ 子树内的情形：

$u$ 有可能连向 $0$ 个，$1$ 个，$2$ 个，$3$ 个或者是更多个儿子。发现对于 $u$ 连向至少 $3$ 个儿子的情形 $u$ 都一定会产生贡献，所以可以归结为一类。

因此，我们可以维护 $dp_{u,0},dp_{u,1},dp_{u,2},dp_{u,3}$，分别表示：$u$ 的子树中，包含 $u$ 的连通块中 $u$ 的度数分别为 $0,1,2,\ge3$ 时的最大贡献，则我们可以实现转移与初始值：

$dp_{u,0}=a_u$（没有什么好说的）。

考虑每一个 $v$ 的最大可能贡献（假设 $u$ 有边连向 $v$），根据度数限制就可以得到该值为：$\max\{dp_{v,0},dp_{v,1}-a_v,dp_{v,2}+a_v,dp_{v,3}\}$。

不妨设我们将这些贡献从大到小排序之后依次为 $w_1,w_2,w_3,\dots,w_k$。

那么 $dp_{u,1}=w_1+a_u$，$dp_{u,2}=w_1+w_2$。

$dp_{u,3}$ 的处理需要特别注意：

1) $w_3>0$，这意味着可能可以我们贪心地取更多的点，因此 $dp_{u,3}=a_u+\displaystyle\sum_{i=1}^{k}w_i[w_i>0]$。

2) $w_3\le0$，这说明选取更多的子节点没有任何好处，所以 $dp_{u,3}=a_u+w_1+w_2+w_3$。

实现的时候我们只需要维护前 $3$ 大值，进行上述分类讨论即可。

于是，我们就做完了，总复杂度 $O(n)$，但是常数不小（貌似还比不过 $O(n\log n)$）。

[评测记录](https://codeforces.com/contest/1901/submission/276743075)

---

## 作者：__log__ (赞：0)

#

[~~Fleet beacon~~](https://www.luogu.com.cn/problem/CF1901E)

677 要我找一道树上 dp，难度 \*2200~\*2300，但我切过的题没几道树形 dp，只能现切了。

先乱写一个状态 $dp_u$ 表示在以 $u$ 为根的子树内选节点，选出的最大权值和。

观察到每个节点是否能加进答案，只与这个节点与其他被选定节点之间的度数有关，所以 dp 的时候要加一维确定度数。

$dp_{u,0/1/2/3}$ 表示以 $u$ 为根的子树内选节点，$u$ 节点与其他选定节点的度数为 $0/1/2/\text{更多}$ 的最大权值和。

为了方便转移，我们再加一维作为是否选定父亲节点。

所以现在的状态为 $dp_{u,0/1/2/3,0/1}$ 表示以 $u$ 为根的子树内选节点，$u$ 节点与其他选定节点的度数为 $0/1/2/\text{更多}$，不选择/选择父亲的最大权值和。

然后式子乱写即可，当处理到 dfs 的根的时候要特判，下面的式子**不一定**适用于 dfs 的根。

为了方便，设 $f_u = \max\{dp_{u,1,1},dp_{u,2,1},dp_{u,3,1}\}$（所有与父亲相连的状态的最大权值）。

$$dp_{u,0,0} = \max\{0,a_u\}$$

下面这 $1$ 个是不合法状态，设为负无穷即可：
$$dp_{u,0,1} = -\infty$$

剩下的要注意度数限制：

$$dp_{u,1,0} = a_u + \max_v{f_v}$$

$$dp_{u,1,1} = a_u$$

$$dp_{u,2,0} = \max_{v1,v2}\ f_{v1}+f_{v2}$$

$$dp_{u,2,1} = \max_{v}\ f_v$$

$$dp_{u,3,0} = a_u +  
\left\{
    \begin{array}{ll}
        \max_{v1,v2,v3} f_{v1}+f_{v2}+f_{v3} & \sum_{v}[f_v\ge 0] < 3\\
        \sum_v [f_v \ge 0]f_v & \text{otherwise}\\
    \end{array}
\right.
$$

$$dp_{u,3,1} = a_u +  
\left\{
    \begin{array}{ll}
        \max_{v1,v2} f_{v1}+f_{v2} & \sum_{v}[f_v\ge 0] < 2\\
        \sum_v [f_v \ge 0]f_v & \text{otherwise}\\
    \end{array}
\right.
$$

## Code

记得把要初始化的**全部**初始化掉！！！

```cpp
// I love Furina forever.
# include <bits/stdc++.h>
# define maxn 500100
# define inf 9e18
# define int long long
# define go(u) for(int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
# define rep(i, j, k) for(int i = j; i <= k; ++i)
# define per(i, j, k) for(int i = j; i >= k; --i)
using namespace std;

int T, n, ans;
int a[maxn], deg[maxn], dp[maxn][4][2], f[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], tot;

inline int max(int x, int y, int z) {return max(x, max(y, z));}
inline void add_edge(int u, int v) {nxt[++tot] = head[u]; to[tot] = v; head[u] = tot; deg[u]++;}
inline void init() {
    rep(i, 1, n) head[i] = f[i] = deg[i] = 0;
    rep(i, 1, n) memset(dp[i], -0x3f, sizeof(dp[i]));
    tot = ans = 0;
}

void dfs(int u, int fa) {
    dp[u][0][0] = max(0ll, a[u]); dp[u][0][1] = -inf; dp[u][1][1] = a[u];
    int Max = -inf, Max2 = -inf, Max3 = -inf, sum = 0, cnt = 0;
    go(u) if(v != fa) {
        dfs(v, u);
        if(f[v] > 0) sum += f[v], cnt++;
        if(f[v] >= Max) Max3 = Max2, Max2 = Max, Max = f[v];
        else if(f[v] >= Max2) Max3 = Max2, Max2 = f[v];
        else if(f[v] >= Max3) Max3 = f[v];
    }
    if(u == 1) {
        dp[u][1][0] = Max + a[u];
        if(deg[u] >= 2) dp[u][2][0] = Max + Max2;
        if(deg[u] >= 3) dp[u][3][0] = (cnt >= 3 ? sum : Max + Max2 + Max3) + a[1];
    }
    else {
        if(deg[u] >= 2) dp[u][1][0] = Max + a[u], dp[u][2][1] = Max;
        if(deg[u] >= 3) dp[u][2][0] = Max + Max2, dp[u][3][1] = (cnt >= 3 ? sum : Max + Max2) + a[u];
        if(deg[u] >= 4) dp[u][3][0] = (cnt >= 3 ? sum : Max + Max2 + Max3) + a[u];
    }
    f[u] = max(dp[u][1][1], dp[u][2][1], dp[u][3][1]); // 不能有 0
    ans = max(ans, dp[u][3][0], max(dp[u][0][0], dp[u][1][0], dp[u][2][0]));
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    rep(i, 1, T) {
        cin >> n; init();
        rep(i, 1, n) cin >> a[i];
        rep(i, 1, n - 1) {int u, v; cin >> u >> v; add_edge(u, v); add_edge(v, u);}
        dfs(1, 1);
        cout << ans << '\n';
    }
    return 0;
}
```

强烈要求 CF 增加评测机以加快评测进度。

~~为什么我用拼音敲 `fu` 第一个出来的是 `芙`？敲 `yy` 第一个是 `饮月`？~~

---

## 作者：yzy4090 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1901E)  
首先题面定义了一个叫“压缩”的操作，模拟一下可以发现它只会删除未进行操作时度为 $2$ 的节点，且不改变其余节点的度。  
其次在树上维护点权和最大的连通块，这是相当好做的，请见 [P1122](https://www.luogu.com.cn/problem/P1122)。  
所以我们额外考虑每个节点的度即可。做一个树形 dp，状态为 `dp[u][0/1/2/3]`，意义为“在 $u$ 的子树中选择 $0,1,2,\ge3$ 个儿子（等同于度的大小），并不选择 $u$ 的父亲，点权和的最大值”。  
当父亲 $fa_u$ 和一个选择 $1$ 个儿子的节点 $u$ 同时被选择时，需要额外减去 $a_u$，因为 $u$ 最终会被删除。若 $u$ 有 $2$ 个儿子时，需要额外加上 $a_u$。  
求最大值肯定是贪心选择，所以需要维护前三大 `dp` 值的儿子。  
时间复杂度 $\mathcal{O}\left(n\right)$。  
[代码](https://codeforces.com/problemset/submission/1901/260466066)

---

## 作者：spider_oyster (赞：0)

感觉挺简单的，但细节挺多。

树形 dp。设 $f(u,0/1)$ 表示考虑以 $u$ 为根的子树，保留/删除 点 $u$ 的最大值。

那么保留 $u$ 要么只保留点 $u$，要么至少选 2 棵子树。

删除 $u$ 只能选一棵子树，且需要连向父亲。

直接转移即可。

考虑更新答案。

有三种情况：

- 保留 $u$，选一棵子树。
- 删除 $u$，选两棵子树。
- 保留 $u$，选至少三棵子树。

可以用 vector 把儿子的 dp 值排序，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=5e5+5;
int n,m,ans,a[N],f[N][2];
vector<int> G[N];

inline int rd()
{
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}

void dfs(int u,int fa)
{
    f[u][0]=a[u];
    ans=max(ans,a[u]);
    vector<int> p;
    for(int v:G[u]) if(v!=fa) dfs(v,u),p.push_back(max(f[v][0],f[v][1]));
    sort(p.begin(),p.end(),greater<>());
    if(!p.size()) f[u][1]=-1e16;
    else if(p.size()==1) f[u][1]=p[0],ans=max(ans,a[u]+p[0]);
    else
    {
        f[u][0]=a[u]+p[0]+p[1],f[u][1]=p[0];
        for(int i=2;i<p.size();i++) f[u][0]+=max(p[i],0ll);
        f[u][0]=max(f[u][0],a[u]);
        ans=max(ans,max(a[u]+p[0],p[0]+p[1]));
        if(p.size()>=3) ans=max(ans,f[u][0]-max(0ll,-p[2]));
    }
}

void solve()
{
    n=rd();ans=0;
    for(int i=1;i<=n;i++) G[i].clear(),f[i][0]=f[i][1]=0;
    for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=1;i<n;i++)
    {
        int u=rd(),v=rd();
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<'\n';
}

signed main()
{
    int t=rd();
    while(t--) solve();
}
```

---

## 作者：Terac (赞：0)

令 $f_i$ 表示，子树 $i$ 中仍有最终未被删除的点的最大贡献。

转移有 
$$f_u=\max\left\{a_u,\max\limits_{v\in son_u} f_v,a_u+\max\limits_{k\ge 2,v_1,v_2,\cdots,v_k\in son_u}\sum f_v\right\}$$
分别对应只保留 $u$，$u$ 被压缩和 $u$ 不被压缩三种情况。

考虑 $f_u$ 和答案的关系，我们钦定 $u$ 为根，有
$$ans=\max\left\{a_u,a_u+\max\limits_{k\ne 2,v_1,v_2,\cdots,v_k\in son_u} \sum f_v,\max\limits_{v_1,v_2\in son_u}(f_{v_1}+f_{v_2})\right\}$$

分别对应只保留 $u$，$u$ 不被压缩和 $u$ 被压缩三种情况。

简化一下，即
$$f_u=\max \left\{\max\limits_{v\in son_u} f_v,a_u+\max\limits_{k\ge 0,k\ne 1,v_1,v_2,\cdots,v_k\in son_u}\sum f_v\right\}$$
$$ans=\max \left\{\max\limits_{v_1,v_2\in son_u}(f_{v_1}+f_{v_2}),a_u+\max\limits_{k\ge 0,k\ne 2,v_1,v_2,\cdots,v_k\in son_u}\sum f_v\right\}$$

分 $k=1,2$ 和 $k\ge 3$ 的部分贪心取即可。时间复杂度 $O(n)$。

因为可以删光，记得 $ans$ 与 $0$ 取 $\max$。

---

## 作者：Sampson_YW (赞：0)

相当于找无根树的一棵虚树，让虚树上的点权值和最大。

虚树只有不超过两个点的情况：随便做。

虚树有大于两个叶子的情况：树形 DP。

对于每个在虚树上的点，分成四种情况考虑。

1. $x$ 是虚树的叶子节点 (选)。

它的儿子全都不在虚树里，$f_{x,1}$ = $val_x$。

2. $x$ 在虚树的边上 (不选)。

它恰有一个儿子在虚树上。

令 $v_y = \max (f_{y,1}, f_{y,2}, f_{y,3})$，$f_{x,2} = \max v_y$。

3. $x$ 是虚树的非叶非根节点 (选)。

它有至少两个儿子在虚树上。

先把最大的 $v$ 和次大的 $v$ 选了，剩下的 $v$ 和 $0$ 取 $\max$ 后求和，再加上 $val_x$。

4. $x$ 是虚树的根节点。

- 选。

  它不能有恰好两个儿子在虚树上。
  - 它有至少三个儿子在虚树上。
  转移和情况 3 类似，多选一个第三大就行。
  - 它只有一个儿子在虚树上。
  直接取 $\max v$。
  
  记得加上 $val_x$。
- 不选。

  它恰好有两个儿子在虚树上。直接选最大和次大就行，不要加 $val_x$。
  
[code](https://codeforces.com/contest/1901/submission/234395745)

---

## 作者：huangrenheluogu (赞：0)

在树上求什么东西，直接 `树型dp`。

本来以为要换根，其实不用。我们只需要统计一个子树内的最值问题和需要向上传的最值问题。

原因在于如果以 $x$ 为根，需要一个 $fa_x$ 为根的子树，那么由于题中要求的是无根树，完全可以换成 $fa_x$ 为根，$x$ 为一棵子树的根。

记 $f_{x,0/1/2/3}$ 表示 $x$ 节点需要向上传的方案中，连接 $0/1/2/\ge3$ 棵子树的最值，$g_{x,0/1/2/3}$ 同理，区别在于 $g_x$ 是统计不往上传的方案总数。

考虑求法：

先不考虑第二个操作。

对于 $1\le i\le2,f_{x,i}=\max\{f_{x,i-1}+f_{son,j}\},j=0,1,2,3$，此处 $son$ 指 $x$ 子节点。

对于 $i=3,f_{x,i}=\max\{\max\{f_{x,2},f_{x,3}\}+f_{son,j}\}$。

对于 $i=0,f_{x,i}=a_x$。

发现 $g$ 的转移方程其实是和 $f$ 一样的。

$g$ 和 $f$ 不同点在于：

- 第二个操作时，$f_{x,1}$ 需要减掉 $a_x$，$g_{x,2}$ 需要减掉 $a_x$。原因在于是否和父亲连边。

- 上传给父亲用的是 $f$，统计答案用的是 $g$。

最后 $ans$ 就很好求了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5, inf = 1e18;
int T, n, a[N], f[N][4], fir[N], nxt[N << 1], son[N << 1], tot, u, v, ans, g[N][4], val, maxn, secmaxn, mmaxn;
inline void init(){
	for(int i = 1; i <= n; i++){
		f[i][0] = f[i][1] = f[i][2] = f[i][3] = -inf;
		g[i][0] = g[i][1] = g[i][2] = g[i][3] = -inf;
		fir[i] = 0;
	}
	for(int i = 1; i <= tot; i++) nxt[i] = 0;
	tot = 0ll;
	ans = 0ll;
}
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x, int ff){
	g[x][0] = f[x][0] = a[x];
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
	}
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		maxn = -inf;
		for(int j = 3; j >= 0; j--){
			maxn = max(maxn, f[son[i]][j]);
		}
		for(int j = 3; j >= 0; j--){
			f[x][min(3ll, j + 1ll)] = max(f[x][min(3ll, j + 1ll)], f[x][j] + maxn);
			g[x][min(3ll, j + 1ll)] = max(g[x][min(3ll, j + 1ll)], g[x][j] + maxn);
		}
	}
	f[x][1] -= a[x];
	g[x][2] -= a[x];
	ans = max(ans, g[x][1]);
	ans = max(ans, g[x][0]);
	ans = max(ans, g[x][2]);
	ans = max(ans, g[x][3]);
}
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		init();
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i < n; i++){
			scanf("%lld%lld", &u, &v);
			add(u, v), add(v, u);
		}
		dfs(1, 0);
		printf("%lld\n", ans);
	}
	return 0;
}
/*
1
4
1 -2 2 1
1 2
3 2
2 4
*/
/*
1
7
-2 4 -2 3 3 2 -1
1 2
2 3
3 4
3 5
4 6
4 7
*/
/*
1
3
-1 3 1
1 2
2 3
*/
/*
1
2
-2 -5
2 1
*/
```

---

