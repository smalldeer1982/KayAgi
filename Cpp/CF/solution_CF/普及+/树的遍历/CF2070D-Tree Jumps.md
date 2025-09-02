# Tree Jumps

## 题目描述

给定一棵包含 $n$ 个顶点的有根树。树中顶点编号为 $1$ 到 $n$，根为顶点 $1$。定义 $d_x$ 为根到顶点 $x$ 的距离（最短路径上的边数）。

初始时，一个棋子被放置在根节点。你可以执行以下操作任意次（包括零次）：

- 将棋子从当前顶点 $v$ 移动到顶点 $u$，满足 $d_u = d_v + 1$。如果 $v$ 是根节点，可以选择任意满足此约束的顶点 $u$；但如果 $v$ 不是根节点，则 $u$ 不能是 $v$ 的邻居（即 $v$ 和 $u$ 之间不能有直接边相连）。

例如在上图的树结构中，允许的移动包括：$1 \rightarrow 2$，$1 \rightarrow 5$，$2 \rightarrow 7$，$5 \rightarrow 3$，$5 \rightarrow 4$，$3 \rightarrow 6$，$7 \rightarrow 6$。

如果一个顶点序列满足：存在一种棋子移动方式，使得棋子按顺序恰好访问序列中的所有顶点（且仅这些顶点），则该序列被称为有效的。

你的任务是计算有效顶点序列的数量。由于答案可能很大，请输出其对 $998244353$ 取模的结果。

## 说明/提示

第一个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 4]$，$[1, 4, 3]$。

第二个示例中，有效序列为：$[1]$，$[1, 2]$。

第三个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 2, 7]$，$[1, 2, 7, 6]$，$[1, 5]$，$[1, 5, 3]$，$[1, 5, 3, 6]$，$[1, 5, 4]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
1 2 1
3
1 2
7
1 2 2 1 4 5```

### 输出

```
4
2
8```

# 题解

## 作者：postpone (赞：3)

比较好推的 dp。

跳是一层一层地跳，要求总共的方案数，实质上就是终点为每个点的方案数之和。

那么对于某一深度的某一个点（不是根），跳到这个点的方案数，就是上一层中，除了它的父亲以外的所有点的方案数之和——这也就是该题转移的核心思路。

先预处理出深度，以 $dp_i$ 表示以 $i$ 为终点的方案数，$g_j$ 表示深度为 $j$ 的方案数，一层一层递进地转移即可，核心代码如下。

```cpp
vector<Z> dp(n), g(n);
dp[0] = g[0] = 1;
for (int i = 1; i < n; i++) {
    for (auto u : f[i]) { // f[i] 存放深度为 i 的所有点
        dp[u] += g[i - 1];
        for (auto v : adj[u]) {
            dp[v] -= dp[u]; // 先让它儿子减去它，等价于儿子加上除了父亲以外所有方案
        }
        g[i] += dp[u];
    }
}
```
[完整代码](https://codeforces.com/contest/2070/submission/308173323)

---

## 作者：Tomwsc (赞：2)

# CF2070D Tree Jumps 题解

## 题意

有点难表述，直接[传送](https://www.luogu.com.cn/problem/CF2070D)吧。

## 思路

~~一开始看错题目，调了半天~~。

一道比较水的 dp。

由题意可得：若 $u$ 可以跳到 $v$，则 $v$ 的深度和 $u$ 相差 $1$。于是便可以想到用 $depth$ 数组记录每个节点的深度。同时，由于 $v$ 和 $u$ 的关系不能为父子节点，于是便可以令人想到用一个数组 $more$ 来记录以每个节点结尾的序列总数。这样在转移时，便可以用总数来减掉不能算的 $more_u$。

设 $dp_i$ 表示以第 $i$ 层的节点结尾的序列总数。假设现在转移到 $v$ 节点，其父亲为 $u$ 节点，则可以得到：

- $depth_v=depth_u+1$
- $dp_{depth_v}=dp_{depth_v}+dp_{depth_u}-more_u$
- $more_v=dp_{depth_u}-more_u$

因为序列可以以任意深度的节点结尾，所以有最终答案便是各深度 $dp$ 的值之和，即：

设最大深度为 $maxn$，$cnt$ 保存最终答案。

$$cnt=\sum_{i=1}^{maxn}dp_i$$

## 代码

注意：

- 要记得取模，同时注意做减法时要**先加模数**，防止出现负数。

- 多测要清空，但用 ```memset``` 会超时，所以使用 ```fill```。

代码如下：
```cpp
#include<bits/stdc++.h>
#define inf (1ll << 62)
#define regint register int
using namespace std;
const int MAXN = 3e5 + 10 , mod = 998244353;
int t , n;
int depth[MAXN] , dp[MAXN] , more[MAXN];
vector<int>G[MAXN];
struct Node {
	int u , fa;
};

inline void bfs() {
	queue<Node>q;
	q.push({1 , 0});
	depth[1] = 1;
	dp[1] = 1;
	while(!q.empty()) {
		int u = q.front().u;
		int fa = q.front().fa;
		q.pop();
		for(auto v : G[u]) {
			if(v == fa)
				continue;
			depth[v] = depth[u] + 1;
			dp[depth[v]] = ((dp[depth[v]] + dp[depth[u]]) % mod + mod - more[u]) % mod;
			more[v] = (dp[depth[u]] + mod - more[u]) % mod;
			q.push({v , u});
		}
	}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n; 
		for(regint i = 1;i <= n;i ++)
			G[i].clear();
		fill(depth + 1 , depth + 1 + n , 0);
		fill(dp + 1 , dp + 1 + n , 0);
		fill(more + 1 , more + 1 + n , 0);
		for(regint i = 2;i <= n;i ++) {
			int u;
			cin >> u;
			G[u].push_back(i);
			G[i].push_back(u);
		}
		bfs();
		int cnt = 0;
		for(regint i = n;i >= 1;i --)
			cnt = (cnt + dp[i]) % mod;
		cout << cnt << '\n';
	}
	return 0;
}
```

---

## 作者：Kendieer (赞：2)

传送门：[**Codeforces**](https://codeforces.com/contest/2070/problem/D#)、[**洛谷**](/problem/CF2070D)。

## 思路

由题可知，我们每次的路径都是不可逆的（即从一点出发后不能再原路返回），现在需要从根出发，问有多种不同的方案。

对于除根节点外的每一个节点，该节点所有能走的节点均为当前节点的下一层所有不与其直接相连的节点。

于是我们可以跑一次 **bfs** 得到每一层的序号。

那么我们如何得到方案数呢？不妨设 $d_i$ 为序号 $i$ 层数，$dp_i$ 为从 $1$ 号点出发到达 $i$ 号点的方案数。

我们定义 $d_1=1,dp_1=1$。

于是我们可以得到以下转移方程：

$dp_i=
\begin{cases}
1,&fa_i=1\\
\sum dp_j & j\in \{x|d_x=d_i+1,x\neq fa_i\}
\end{cases}$

最后答案为所有节点 $dp$ 值之和，时间复杂度为 $O(n^2)$。

很明显，这样是会 $\text {TLE}$ 的，因为我们在转移 $dp_i$ 值时需要遍历所有上一层的节点，那有没有办法转移的时候能快速转移呢？有的兄弟，有的。

由于每次转移仅有一个值是不需要累加的，其他需要正常累加，于是我们可以提前求出每一层的 $dp$ 值总和 $S_i$，则当前节点的 $dp$ 值为 $S-dp_{fa}$。

## 参考代码

PS：这里转移我使用了从最下层开始向上转移，所以结果会 $+1$，不影响结果。

赛时 [**Submission**](https://codeforces.com/contest/2070/submission/308154444)。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define Code_by_Kendieer while(n--) solve()

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using oiType = ll;
using namespace std;

inline oiType qread(int t=10);
inline char readChar();
void qwrite(oiType x,int t = 10);
std::istream& operator>>(std::istream &is,i128 &x);
std::ostream& operator<<(std::ostream &os,i128 x);

constexpr ll inf = 0x3f7f7f7f7f7f7f7f;
constexpr int maxn = 2e5 + 7;
int N = maxn;
constexpr int mod = 998244353;

struct Node {};

void solve(){
    int n = qread();
    vector<int> fa(n+3);
    vector<int> dep(n+3);
    vector<ll> sum(n+3),rem(n+3);
    vector<vector<int>> adj(n+3),nodes(n+3);
    fa[1] = 1;
    rep(i,2,n+1) fa[i] = qread(),adj[fa[i]].push_back(i);
    queue<int> q;
    q.push(1);
    dep[1] = 1;
    nodes[1].push_back(1);
    while(q.size()){
        int loc = q.front();
        q.pop();
        rep(i,0,adj[loc].size()){
            int to = adj[loc][i];
            q.push(to);
            dep[to] = dep[loc] + 1;
            nodes[dep[to]].push_back(to);
        }
    }
    repr(i,2,n+1){
        rep(j,0,nodes[i].size()){
            int idx = nodes[i][j];
            rem[fa[idx]] += sum[i] - rem[idx] + 1;
            rem[fa[idx]] %= mod;
            sum[i-1] += sum[i] - rem[idx] + 1 + mod;
            sum[i-1] %= mod;
        }
    }
    cout << ((sum[1]+1)%mod) << endl;
}

signed main(){
    // std::cin.tie(0),std::cout.tie(0);
    // std::ios::sync_with_stdio(0);
    int n = 1;
    n = qread();
    Code_by_Kendieer;
    return 0;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 |  Tips: qread() 为快读函数，读取下一个 t 进制整数（默认为十进制）。
 |        qwrite(x,t) 为快写函数，以t进制形式输出一个整数 x（默认为十进制）。
 |        readChar() 为读取下一个非空字符（跳过空格、换行）
 |        rep(变量名,a,b) 为 for 循环，自变量为变量名，循环为 [a,b) 顺序走。
 |        repr(变量名,a,b) 为 for 循环，自变量为变量名，循环为 [a,b) 倒序走。
 |        endl 已被重定义为 '\n'，而不是 "\r\n"。
 |        cin >> __int128, cout << __int128 已经被重载，能正常使用。
 |
 |   main 函数仅包含实现 t 组测试，无需关注，具体每组实现只需查看 solve() 即可。
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
inline oiType qread(int t){
    oiType r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while ((ch >= '0'&&ch <= '9')||(ch>='A'&&ch<='Z')) r=r*t+ch-'0'+(ch>='A'?10:0),ch = getchar();
    return r * s;
}
inline char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(oiType x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
std::istream& operator>>(std::istream& is,i128 &x){
    std::string s;i128 sign = 1;
    is >> s,x = 0;
    for(int i(0);i<s.size();i++)if (s[i] == '-') sign = -1;else x*=10,x+=s[i]-'0';
    x *= sign;
    return is;
}
std::ostream& operator<<(std::ostream& os,i128 x){
    if (x == 0) {
        os << 0;return os;
    } else if (x < 0)
        os << "-",x = -x;
    std::string s = "";
    while(x) s += x%10+'0',x /= 10;
    std::reverse(s.begin(), s.end());
    os << s;
    return os;
}

// =====================================================
//      Last updated: 02/20/2025
//      Code By Kendieer.
// =====================================================
```

---

## 作者：Autream (赞：0)

## 题意简述

给定一棵 $n$ 个节点的有根树，每次操作可以从当前节点走到当前深度 +1 的非直接子节点，根节点可以走到自己所有的子节点。可以操作任意次，问有多少种从根开始路径是合法的。答案模 $998244353$。

## 题目分析

由于每个点只可能往深度更深的点走或者不走，因此考虑 DP。

设 $dp_u$ 表示从 $u$ 出发有多少条合法的路径。
显然，他们可以到达除了自己儿子以外的，深度比自己大 1 的所有节点，并且这些节点能到达的节点 $u$ 都能到达。

设 $cnt_i$ 表示深度为 $i$ 的节点有多少个，$sum_i$ 表示所有深度为 $i$ 的节点的 dp 值的和，$size_u$ 表示 $u$ 的子节点的个数。令当前节点为 $u$，深度为 $i$，状态转移方程：

$$
dp_u = cnt_{i + 1} - size_u + sum_{i + 1} - \sum _v dp_v + 1
$$

在实现上，不难发现每层节点都是由它的下一层转移的，考虑记录 BFS 的入队顺序，然后逆序操作即可。

时间复杂度 $O(n)$。

## AC Code

```cpp
// Problem: CF2070D Tree Jumps
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2070D
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Date: 2025/05/20 15:00:52
// Author: Li_Feiy

#include <bits/stdc++.h>
#define arrout(a, n) rep(i, 1, n) printk(a[i])
#define arrin(a, n) rep(i, 1, n) a[i] = read()
#define rep(i, x, n) for(int i = x; i <= n; i++)
#define dep(i, x, n) for(int i = x; i >= n; i--)
#define erg(i, x) for(int i = head[x]; i; i = e[i].nex)
#define dbg(x) std::cout << #x << ":" << x << " "
#define mem(a, x) memset(a, x, sizeof a)
#define all(x) x.begin(), x.end()
#define arrall(a, n) a + 1, a + 1 + n
#define PII std::pair<int, int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
	char ch = getchar();
	int r = 0, w = 1;
	while(ch < '0' || ch > '9') w = ch == '-' ? -1 : w, ch = getchar();
	while(ch >= '0' && ch <= '9')
		r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r * w;
}

void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
template <typename... Args> void print(int t, Args... args) {
	print(t), print(args...);
}

void printl(int x) { print(x), putchar('\n'); }
template <typename... Args> void printl(int t, Args... args) {
	printl(t), printl(args...);
}

void printk(int x) { print(x), putchar(' '); }
template <typename... Args> void printk(int t, Args... args) {
	printk(t), printk(args...);
}

CI N = 3e5 + 5, MOD = 998244353;
int T, n, dp[N], cnt[N], sum[N], vis[N], deep[N];
std::vector<int> e[N];
void dfs(int x, int fa, int depth) {
	deep[x] = depth, cnt[depth]++;
	for(int y: e[x]) {
		if(y == fa) continue;
		dfs(y, x, depth + 1);
	}
}
void bfs() {
	std::queue<int> q;
	std::stack<int> s;
	q.push(1), vis[1] = 1;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		s.push(x);
		for(int y: e[x])
			if(!vis[y]) q.push(y), vis[y] = 1;
	}
	while(!s.empty()) {
		int x = s.top();
		s.pop();
		dp[x] = (cnt[deep[x] + 1] - e[x].size() + sum[deep[x] + 1] + 1) % MOD;
		for(int y: e[x]) dp[x] = (dp[x] - dp[y] + MOD) % MOD;
		(sum[deep[x]] += dp[x]) %= MOD;
	}
}
signed main() {
	T = read();
	while(T--) {
		n = read();
		rep(i, 2, n) {
			int x = read();
			e[i].p_b(x), e[x].p_b(i);
		}
		dfs(1, 0, 1), bfs();
		for(int y: e[1]) (dp[1] += dp[y]) %= MOD;
		printl((dp[1] + e[1].size()) % MOD);
		rep(i, 1, n) dp[i] = 0, sum[i] = 0, vis[i] = 0, deep[i] = 0, cnt[i] = 0,
					 e[i].clear();
	}
	return 0;
}
```

---

## 作者：Pink_Dove (赞：0)

[AC 记录](https://codeforces.com/contest/2070/submission/312551502)

[更萌的食用体验](https://yumomeow.github.io/2025/03/26/solution-CF2070D/)

### 题意
给定一棵树，可以从一个节点走到下一层的节点，但当处在非根节点时不可以走到儿子节点，求合法走法的方案数。

### 题解
考虑 dp。设 $f_i$ 表示以点 $i$ 为结尾的合法序列数，答案即为 $\sum f_i$。考虑转移。设节点 $i$ 位于 $dep_i$ 层。
$$
f_i=\bigg(\sum_{\{j|dep_j=dep_i-1\}}f_j\bigg)-f_{fa_i}
$$
将每一层的 $f_i$ 求和即可优化到 $O(n)$。

由于转移时要先求出上一层的所有答案，所以使用 BFS 来求。注意特判节点 $1$，要将以它结尾的一种方案计入 $sum$ 与 $ans$，但 $f_1$ 应该等于 $0$ 以保证答案正确，因为第二层不需要减去。

### 代码
```cpp
#include<iostream>
#include<queue>
#define int long long
using namespace std;
const int N=3e5+10,MOD=998244353;
int n,fa[N],sum[N],head[N],tot,f[N],dep[N],ans;
queue<int> q;
struct Edge{int to,nxt;}e[N];
void add(int u,int v){e[++tot]={v,head[u]};head[u]=tot;}
int solve(){
    for(int i=1;i<=n;i++) head[i]=dep[i]=f[i]=sum[i]=0;
    ans=0;dep[1]=sum[1]=ans=1;
    cin>>n;
    for(int i=2;i<=n;i++) cin>>fa[i],add(fa[i],i),dep[i]=dep[fa[i]]+1;
    for(int i=head[1];i;i=e[i].nxt) q.push(e[i].to);
    while(q.size()){
        int u=q.front();q.pop();
        f[u]=(sum[dep[u]-1]-f[fa[u]]+MOD)%MOD;
        sum[dep[u]]=(sum[dep[u]]+f[u])%MOD;
        ans=(ans+f[u])%MOD;
        for(int i=head[u];i;i=e[i].nxt) q.push(e[i].to);
    }
    cout<<ans<<'\n';
    return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：zzldd (赞：0)

[原题链接](https://codeforces.com/contest/2070/problem/D) \
由题意知，我们可以从深度为 $i$ 的节点移动到深度为 $i+1$ 的任意不与当前节点相连的节点（可以从根节点移动到任意深度为 $2$ 的节点） \
考虑进行树形 dp。\
由于直接转移并不是很方便，我们可以考虑先统计第 $i+1$ 层所有节点的方案数之和，记录为 $sum_{i+1}$，第 $i+1$ 层所有与当前节点相连的方案数之和，记录为 $tt$，则当前节点的方案数 $ans_{now}=sum_{i+1}-tt+1$。\
首先 dfs 统计各个节点的深度，记录最大深度为 $cmax$。 \
之后从最深层开始遍历，统计方案数。\
最终答案即为 $sum_2 +1$（1 号节点自己可以作为一个方案）。\
注意，在进行转移时，可能出现负数，需要先 $+998244353$ 再进行取模。

```cpp
#include<bits/stdc++.h>
#define int long long
#define md 998244353
using namespsume std;
int T,cnt=0,cmax=0,n,h[300005],ans[300005],sum[300005];
struct nd{
	int u,v,nxt;
}e[300005];
vector<int> d[300005];
void dfs1(int u,int c){
	cmax=max(cmax,c);
	d[c].push_bsumk(u);
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		dfs1(v,c+1);
	}
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;cnt=cmax=0;
		for(int i=2;i<=n;i++){
			int x;              //建图 
			cin>>x;
			e[++cnt].u=x;
			e[cnt].v=i;
			e[cnt].nxt=h[x];
			h[x]=cnt;
		}dfs1(1,1);
		for(int i=cmax;i>1;i--){
			int sz=d[i].size();
			for(int j=0;j<sz;j++){
				int tt=0,now=d[i][j];
				for(int x=h[now];x;x=e[x].nxt) tt=(tt+ans[e[x].v])%md; 
				ans[now]=sum[i+1]+1-tt+md;
				sum[i]+=ans[now]+md;
				ans[now]%=md;
				sum[i]%=md;
			}
		}cout<<(sum[2]+1)%md<<"\n";
		//多测清空 
		for(int i=0;i<=cmax;i++) d[i].clear();
		for(int i=0;i<=n+1;i++) h[i]=sum[i]=ans[i]=0;
	}
}

```

---

## 作者：lw393 (赞：0)

赛时过 D 不过 C，差评！！！

这道题只是考验 bfs 功底，仅此而已。

根据题目要求，我们可以很快的写出每个节点的答案。

$$ans_u = (\sum_{deep_v=deep_u - 1}ans_v) - ans_{fa_u}$$

然后由于是一棵树，所以 bfs 一定满足深度的有序性。直接统计即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 3e5 + 5, mod = 998244353;
vector<int>G[N];
#define pb push_back

int p[N];

int dep[N];

int ans[N];

void bfs(int n){
    map<int, int>dep_ans;
    queue<int>q;
    for(auto v : G[1]) { dep[v] = 1; ans[v] = 1; q.push(v); dep_ans[dep[v]] += 1; }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v : G[u]){
            q.push(v);
            dep[v] = dep[u] + 1;
            ans[v] = dep_ans[dep[u]] - ans[u];
            (ans[v] += mod) %= mod;
            dep_ans[dep[v]] += ans[v];
        }
    }
}

void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 2; i <= n; i++){
        cin >> p[i];
        G[p[i]].pb(i);
    }
    dep[1] = 0;
    ans[1] = 1;
    bfs(n);
    int res = 0;
    for(int i = 1; i <= n; i++){
        res += ans[i];
        res %= mod;
    }
    cout << res << '\n';
}

signed main(){
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

首次场切 Div.2 D。

考虑 DP。

令 $dp_i$ 表示以 $i$ 为结束时，有多少种方案。

因为只能从上一层结点转过来，且不能是父亲。

所以 $dp_i = s - dp_{fa_i}$（除了深度为 $2$ 的点不用减），$s$ 指的是上一层所有点的方案数之和，$fa_i$ 表示 $i$ 的父亲，dp 时按照层数进行即可。

答案就是 $\sum_{i = 1}^n dp_i$。

时间复杂度：$O(n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 3e5 + 10;
const int inf = 1e16;
const int mod = 998244353;
int T,n;
int dep[N],dp[N],fa[N];
vector <int> g[N];
struct node{
	int v,dep;
};
node b[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool cmp (node x,node y){
	return x.dep < y.dep;
}
void dfs (int u,int f){
	dep[u] = dep[f] + 1;
	for (auto v : g[u]){
		if (v == f) continue;
		dfs(v,u);
	}
}
void solve(){
	cin >> n;
	for (int u = 2 ; u <= n ; u++){
		int v;
		cin >> v;
		fa[u] = v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	for (int i = 1 ; i <= n ; i++)
		b[i] = (node){i,dep[i]};
	sort (b + 1,b + n + 1,cmp); // 对所有点按照深度排序
	dp[1] = 1; // dp 初始化
	int now = 2,sum = 1;
	for (int i = 2 ; i <= n && now <= n ; i++){
		if (b[now].dep != i) continue;
		int idl = now,idr = now;
		while (idr < n && b[idr + 1].dep == i) idr++; // 求这个深度的点的区间
		for (int j = idl ; j <= idr ; j++)
			dp[b[j].v] = (i == 2 ? sum : (sum - dp[fa[b[j].v]] + mod) % mod);
		sum = 0; // 记录
		for (int j = idl ; j <= idr ; j++)
			sum = (sum + dp[b[j].v]) % mod;
		now = idr + 1; // 跳到下一个点
	}
	int ans = 0;
	for (int i = 1 ; i <= n ; i++) ans = (ans + dp[i]) % mod;
	cout << ans << endl;
	for (int i = 1 ; i <= n ; i++) dp[i] = dep[i] = 0;
	for (int i = 1 ; i <= n ; i++) g[i].clear();
}
signed main(){
	close();
	T = 1;
	cin >> T;    
	while (T--) solve();
	return 0;
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你一颗树。你要按照以下方式移动：

- 你可以从根节点走到与他相邻的节点。

- 你可以从非根节点 $u$ 走到 $dep_v = dep_u + 1$ 的点 $v$，但 $v$ 不能是 $u$ 的儿子。

你需要求出合法的顶点访问序列的方案数。
## Solution
考虑设 $f_i$ 表示到了点 $i$ 的方案数，那么转移就是：

$$f_v = (\sum_{dep_u = dep_v - 1} f_u) - f_{\text{father}}$$

然后我们直接设 $s_i$ 表示 $dep$ 为 $i$ 的 $f$ 值的和，然后就优化完了。

因为可以在任意点停下，所以答案就是所有的 $f_i$ 的和。

注意：因为我们要把当前点的上一层全转移完才能转移这一层，所以用 `bfs` 实现即可。
## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6 + 10, P = 998244353;

int n, f[N], s[N];
vector<int> e[N];

struct Node { int u, fa, dep; };

int bfs(int x)
{
    queue<Node> q;
    s[1] = 1;
    for (auto v : e[x]) q.push({v, 0, 2});
    int res = 0;
    while (q.size())
    {
        int u = q.front().u, dep = q.front().dep, fa = q.front().fa;
        q.pop();
        f[u] = ((s[dep - 1] - f[fa]) % P + P) % P;
        s[dep] = (s[dep] + f[u]) % P;
        for (auto v : e[u]) q.push({v, u, dep + 1});
    }
    for (int i = 1; i <= n; i++) res = (res + s[i]) % P;
    return res;
}

int main()
{
    fst
    int t; cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++) f[i] = s[i] = 0, e[i].clear(); 
        for (int i = 2, j; i <= n; i++) cin >> j, e[j].push_back(i);
        cout << bfs(1) << '\n';
    }
    return 0;
}
```

---

