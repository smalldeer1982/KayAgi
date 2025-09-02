# [ABC387F] Count Arrays

## 题目描述

给定正整数 $N, M$ 以及长度为 $N$ 的数列 $A=(A_1,A_2,\dots,A_N)$，其中每个元素均为 $1$ 以上 $N$ 以下的整数。

请计算满足以下条件且每个元素均为 $1$ 以上 $M$ 以下整数的长度为 $N$ 的数列 $x=(x_1,x_2,\dots,x_N)$ 的数量，并将结果对 $998244353$ 取模。

- 对于所有 $i\ (1 \leq i \leq N)$，满足 $x_i \leq x_{A_i}$

## 说明/提示

### 约束条件

- $1 \leq N, M \leq 2025$
- $1 \leq A_i \leq N$
- 输入中的所有值均为整数

### 样例解释 1

满足条件的数列 $x$ 有 $(1,1,1)$、$(2,2,1)$、$(2,2,2)$、$(3,3,1)$、$(3,3,2)$、$(3,3,3)$，共 6 种。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 3
2 1 1```

### 输出

```
6```

## 样例 #2

### 输入

```
4 9
1 1 1 1```

### 输出

```
2025```

## 样例 #3

### 输入

```
10 5
9 4 5 5 4 2 1 5 7 2```

### 输出

```
10010```

# 题解

## 作者：ZHR100102 (赞：4)

一眼秒的计数题。

# 思路

显然，把小于等于的条件化为大的向小的连单向边，每个数的入度都是 $1$，就会形成一个基环树森林。

那么考虑这个环上能填什么数。因为所有数都小于等于他后面的数，所以所有数都只能相等。这就启发我们在基环树上缩点之后再进行计数。

那么当缩完点计数时如何计算呢？有个很简单的 dp，定义 $dp_{i,j}$ 表示考虑到节点 $i$，节点 $i$ 填 $j$ 的方案数，则很容易能写出转移：

$$dp_{i,j}=\prod_{k=1}^{\left|son_i\right|}(\sum_{a=1}^{j}dp_{son_{i,k},a})$$

直接转移是 $O(nm^2)$ 的，前缀和优化即可做到 $O(nm)$。

答案计算时将所有基环树的答案乘起来即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
using pii=pair<int,pi>;
const ll mod=998244353;
int n,m,a[10005];
int dfn[10005],low[10005],stk[10005],cnt=0,tp=0,scc[10005],tot=0;
bitset<10005>instk,vis,rd;
vector<int>g[10005],tr[10005];
ll ans=1,dp[3005][3005],f[3005][3005];
void tarjan(int u)
{
    dfn[u]=low[u]=++tot;
    instk[u]=1,stk[++tp]=u;
    for(auto v:g[u])
    {
        if(dfn[v]==0)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instk[v])
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u])
    {
        int now;
        cnt++;
        do{
            now=stk[tp--];
            instk[now]=0;
            scc[now]=cnt;
        }while(now!=u);
    }
}
void dfs(int u)
{
    for(int i=1;i<=m;i++)dp[u][i]=1;
    for(auto v:tr[u])
    {
        dfs(v);
        for(int i=1;i<=m;i++)
        {
            dp[u][i]=(dp[u][i]*f[v][i])%mod;
        }
    }
    for(int i=1;i<=m;i++)f[u][i]=(f[u][i-1]+dp[u][i])%mod;
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        g[a[i]].pb(i);
    }
    for(int i=1;i<=n;i++)if(dfn[i]==0)tarjan(i);
    for(int i=1;i<=n;i++)
    {
        int fu=scc[i];
        for(auto v:g[i])
        {
            int fv=scc[v];
            if(fu!=fv)
            {
                tr[fu].pb(fv);
                rd[fv]=1;
            }
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(rd[i]==0)
        {
            dfs(i);
            ans=(ans*f[i][m])%mod;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：lyas145 (赞：4)

题目在[这里](https://www.luogu.com.cn/problem/AT_abc387_f)。

赛时~~多了一条 $21$ 号染色体~~ tarjan 写寄了，赛后三分钟一遍过是真的难受啊！

写一篇题解纪念一下。

## 解题思路

我们可以**以 $x$ 的下标代替 $x$**，跟据 $x_i \le x_{a_i}$ 这个条件从 $a_i$ 到 $i$ 建**有向边**，这样就能保证从 $u$ 出发**所能到**的点所代表的 **$x$ 一定小于或等于 $x_u$**。

在理想状态下，我们希望建出来的图是个**类似于树且没有环**的图，这样 dp 比较方便。但是很明显，它不一定是我们理想状态下的。所以我们需要研究一下我们建出来的图，看看它是否能够变成我们理想状态下的图。

**环**这个东西非常特殊，如果存在环，那么会出现这种情况：$x_i \le x_j \le x_i$（$i \ne j$）。所以 $x_i$ 是会**等于** $x_j$ 的，进而推出**同一个环上的所有结点所代表的 $x$ 一定相同**，于是这个环就可以看作是一个**点**。可以用 tarjan 把每个环缩成一个点。

缩完点，形成的图一定是一个或多个**类似于树的图**，父节点到其儿子节点只会有一条有向边。为什么？因为每个点的**入度都是 $1$**。

缩完点后，这道题就已经变成了一道简单的**树形 dp** 题了。

设 $f_{u,i}$ 表示以 $u$ 为根节点且 $x_u \le i$ 的方案数。可是这样看上去并不好转移，所以在转移时，我们**强制 $x_u = i$**（注意：当 $v \in son(u)$ 时，$f_{v,i}$ 仍表示 $x_v \le i$ 时的方案数），这样转移就方便多了，转移方程如下：

$$f_{u,i} = \prod_{v \in son(u)}f_{v,i}$$

因为是为了方便转移才**强制 $x_u = i$** 的，所以在 $u$ 节点转移完后，$f_{u,i}$ 需要加上 $\sum\limits_{j = 1}^{i - 1}f_{u,j}$，类似于**前缀和**。

别忘了**初始化**：$f_{leaf,i} = i$，其中 $leaf$ 是叶子节点。（代码中写得不太一样，不过效果是一样的）

dp 的时间复杂度是 $\mathrm{O}(N \cdot M)$ 的，可以过。

## 码儿

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2030,P=998244353;
int n,m,ans;
int f[N][N];
bool st[N],vis[N];
int low[N],dfn[N],bl[N],dfi,cnt;
int h[N],e[N],ne[N],idx=1;
vector<int> g[N];
stack<int> stk;
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {f=(c=='-'?-1:1);c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
void add(int a,int b) {
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
void tarjan(int x) {
	dfn[x]=low[x]=++dfi;
	stk.push(x);
	vis[x]=1;
	for (int y : g[x]) {
		if (!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if (vis[y]) {
			low[x]=min(low[x],dfn[y]);
		}
	}
	if (dfn[x]==low[x]) {
		cnt++;
		while (stk.top()!=x) {
			int u=stk.top();
			stk.pop();
			bl[u]=cnt;
			vis[u]=0;
		}
		bl[x]=cnt;
		vis[x]=0;
		stk.pop();
	} 
}
void dfs(int u) {
	for (int i=h[u];i;i=ne[i]) {
		int v=e[i];
		dfs(v);
		for (int j=1;j<=m;j++) {
			f[u][j]=1ll*f[u][j]*f[v][j]%P;
		}
	}
	for (int i=2;i<=m;i++) {(f[u][i]+=f[u][i-1])%=P;}
}
int main() {
	n=read();m=read();
	for (int i=1;i<=n;i++) {
		g[read()].push_back(i);
		for (int j=1;j<=m;j++) {f[i][j]=1;}
	}
	for (int i=1;i<=n;i++) {
		if (!dfn[i]) {tarjan(i);}
	}
	for (int i=1;i<=n;i++) {
		for (int j : g[i]) {
			if (bl[i]==bl[j]) {continue;}
			add(bl[i],bl[j]);
			st[bl[j]]=1;
		}
	}
	ans=1;
	for (int i=1;i<=cnt;i++) {
		if (!st[i]) {
			dfs(i);
			ans=1ll*ans*f[i][m]%P;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

我也是能独立做出来 dp 了，只可惜 tarjan 写寄了。~~（首尾呼应）~~

Thanks for reading！

---

## 作者：Walrus (赞：4)

个人认为这题大于 E 小于 C，因为 E 比 F 更一眼。

首先应该可以把这个问题抽象成一个图论模型，显然可以将 $i\to a_i$ 连边，表示 $x_i\leq x_{a_i}$。然后会变成一张图，但是它上面是有环的，环怎么办，显然如果要满足环上的关系则**该环上的所有点值相同**。考虑 tarjan 然后缩点，这是个经典的套路，也应该很一眼吧。

缩完点显然是一个 DAG，然后跑拓扑，考虑怎么计数。

由于是给点赋权，不妨直接定义 $dp_{i,j}$ 表示第 $i$ 个点的权值是 $j$ 的方案数。那转移方程式就很显然了，在我们拓扑的时候，根据乘法原理有：

$$dp_{x,i}=\prod_{y\in son_x}\sum_{i=1}^m dp_{y,j}$$

又根据拓扑的性质，答案即为：

$$\prod_{x\in S}\sum_{i=1}^m dp_{x,i}$$

其中 $S$ 为出度为 $0$ 的 SCC。

code 跟他人题解略有不同（连边方式是反的）。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for (int i = j; i <= k; ++i)
#define pre(i, j, k) for (int i = j; i >= k; --i)
#define pb push_back
#define PII pair<int, int>
#define fi first
#define se second
#define int long long
#define inf LONG_LONG_MAX
#define repx(i, x) for (int i = head[x]; i; i = nxt[i])


using namespace std;
const int N = 3e3 + 5;
const int mod = 998244353;
int n, m, cnt, a[N], dp[N][N];
int dfn[N], low[N], ins[N], in[N], out[N], scc[N], T, ret;
vector<int> e[N], G[N];
stack<int> st;

void tarjan(int x) {
	dfn[x] = low[x] = ++T, ins[x] = 1, st.push(x);
	for(auto y : e[x]) {
		if(!dfn[y])
			tarjan(y), low[x] = min(low[x], low[y]);
		else if(ins[y])
			low[x] = min(low[x], dfn[y]);
	}
	
	if(dfn[x] == low[x]) {
		int u;
		++cnt;
		do {
			u = st.top(), st.pop();
			scc[u] = cnt, ins[u] = 0;
		} while(u != x);
	}
}

void topsort() {
	queue<int> q;
	rep(i, 1, cnt) if(!in[i]) q.push(i);
	while(q.size()) {
		int x = q.front();
//		cerr<<x;
//		cout << x << '\n';
		q.pop();
		for(auto y : G[x]) {
			if(!--in[y]) q.push(y);
			int sum = 0;
//			cerr<<y;
			rep(i, 1, m) {
				sum += dp[x][i], sum %= mod;
				dp[y][i] = dp[y][i] * sum % mod;
			}
//			cout << '!' << sum <<'\n';
		}
	}
}

void init() {
	rep(i, 1, n) if(!dfn[i]) tarjan(i);
	rep(i, 1, n) for(auto j : e[i]) if(scc[i] != scc[j]) G[scc[i]].pb(scc[j]), ++in[scc[j]], ++out[scc[i]];
	topsort();
}

signed main() {
	FASTIO
	ret = 1;
	cin >> n >> m;
	rep(i, 0, n + 1) rep(j, 1, m) dp[i][j] = 1;
	rep(i, 1, n) cin >> a[i], e[i].pb(a[i]);
	init();
	rep(i, 1, cnt) {
		if(!out[i]) {
			int sum = 0;
			rep(j, 1, m) sum += dp[i][j], sum %= mod;
			ret = ret * sum % mod;
		}
	}
	cout << ret;
	return 0;
}
```

---

## 作者：chenxi2009 (赞：4)

## 思路
树形 DP 题。\
数据范围提示 $O(NM)$ 算法。把限制条件看作一张有向图，称一个点 $i$ 受点 $A_i$ 直接限制。从所有 $i$ 向 $A_i$ 连边。\
令 $f_{i,j}$ 为 $X_i$ 的值为 $j$ 时，$i$ 以及所有受它直接或间接限制的点取值的方案数。由加、乘法原理和限制关系易得 $f_{i,j}$ 就是当前情况下所有它的入点的合法方案数的积，即：

$$
f_{i,j}=\prod_{u\ \text{directly reach}\ i}\sum_{k=1}^{j}f_{u,k}
$$
考虑统计 $f_u$ 的前缀和数组 $s_u$，得:
$$
f_{i,j}=\prod_{u\ \text{directly reach}\ i}s_{u,k}
$$

在上面的过程中我们得到了一个图，其中的强连通子图里面的点都是相互限制的，取值必须相等，所以可以直接缩成一个点。缩点之后得到了 DAG，直接拓扑即可。边界条件为 $f_{i,j}=1$。最终的答案为所有无出度的点的情况数的积。

很明显分析到这里有一个 Hack 思路：也许会有一个连通块中存在多个出度为零的点的情况，直接把方案数相乘岂不会重复？

容易证明上述情况不存在。由于每个点只有 1 条出边，构成 $N$ 个点的强连通子图至少需要 $N$ 条边，所以实际上的缩点缩的就是环（边数不足以构成更复杂的强连通分量）。\
接下来每个点只有一条出边，去掉必然存在的自环（否则点数和边数相同，每个点只有一条出边必定成环），剩下每个连通块内的点必然会构成一颗内向树，宏观上看就是一个内向森林。

综上既然每个部分是一颗内向树，即存在一个树根作为唯一出度为零的点，上述情况不会发生。

因为是树，所以除了拓扑还可以树形 DP。

**推荐树形 DP**，因为建图与上面相反（需要是外向树），每个点入度至多为 $1$，不需要处理重边。时间复杂度 $O(NM)$。

**赠品——解析图与样例三调试信息：**

防止有人和我一样变量名打错被硬控。

样例三建图与正确的 $f$ 数组的值，加深并相互靠近的点为同一强连通分量内的点。同时它们也是唯二的内向树根。

答案：$(1+1+1+1+1)\times(1+20+126+480+1375)=10010$。

![](https://cdn.luogu.com.cn/upload/image_hosting/bnao824r.png)

## 代码：树形 DP
```cpp
#include<bits/stdc++.h> 
using namespace std;
const long long MOD = 998244353ll;
int n,m,a[3000],d[3000],co[3000],col,low[3000],dfn[3000],cnt,fa[3000];
long long ans = 1,f[3000][3000],sum;
stack<int>s;
vector<int>e[3000],ne[3000];
void tar(int u){//缩点
	s.push(u),dfn[u] = low[u] = ++ cnt;
	for(auto v : e[u]){
		if(!dfn[v]) tar(v),low[u] = min(low[u],low[v]);
		else if(!co[v]) low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		col ++,co[u] = col;
		while(s.top() != u) co[s.top()] = col,s.pop();
		s.pop();
	}
	return;
}
void sch(int u){//DP
	for(int i = 1;i <= m;i ++) f[u][i] = 1;//初始化
	for(auto v : ne[u]){
		sch(v),sum = 0;
		for(int i = 1;i <= m;i ++){
			sum = (sum + f[v][i]) % MOD;//前缀和
			f[u][i] = f[u][i] * sum % MOD;//状态转移
		}
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		e[a[i]].push_back(i);//a_i 向 i 建图
	}
	for(int i = 1;i <= n;i ++) if(!dfn[i]) tar(i);
	for(int i = 1;i <= n;i ++){
		int u = co[i];
		for(int j = 0;j < e[i].size();j ++){
			int v = co[e[i][j]];
			if(u != v) ne[u].push_back(v),fa[v] = u,d[v] ++; //缩点后新图连边，统计入度
		}
	}
	for(int i = 1;i <= col;i ++){
		if(!d[i]){//没有入度，这是一个树根
			sch(i),sum = 0;
			for(int j = 1;j <= m;j ++) sum = (sum + f[i][j]) % MOD;//统计方案数之和
			ans = ans * sum % MOD;
		}
	}
	printf("%lld",ans);
	return 0;
}
```
## 代码——DP on DAG
```cpp
#include<bits/stdc++.h> 
using namespace std;
const long long MOD = 998244353ll;
int n,m,a[3000],d[3000],co[3000],col,low[3000],dfn[3000],cnt;
long long ans = 1,f[3000][3000];
stack<int>s;
queue<int>q;
vector<int>e[3000],ne[3000];
void tar(int u){//tarjan 求强连通分量
	s.push(u),dfn[u] = low[u] = ++ cnt;
	for(int i = 0;i < e[u].size();i ++){
		int v = e[u][i];
		if(!dfn[v]) tar(v),low[u] = min(low[u],low[v]);
		else if(!co[v]) low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		col ++;
		co[u] = col;
		while(s.top() != u) co[s.top()] = col,s.pop();
		s.pop();
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		if(i != a[i]) e[i].push_back(a[i]);
	}
	for(int i = 1;i <= n;i ++) if(!dfn[i]) tar(i);
	for(int i = 1;i <= n;i ++){
		int u = co[i];
		for(auto j : e[i]){
			int v = co[j];
			if(u != v) ne[u].push_back(v); 
		}
	}
	for(int i = 1;i <= col;i ++){
		if(ne[i].size()){
			sort(ne[i].begin(),ne[i].end());
			for(int j = 0;j < ne[i].size();j ++) if(j == 0 || ne[i][j] != ne[i][j - 1]) d[ne[i][j]] ++;//重边需要忽略
		}
		for(int j = 1;j <= m;j ++) f[i][j] = 1;
	}
	for(int i = 1;i <= col;i ++) if(!d[i]) q.push(i);
	while(q.size()){
		int u = q.front();
		q.pop();
		if(!ne[u].size()){
			long long sum = 0;
			for(int i = 1;i <= m;i ++) sum = (sum + f[u][i]) % MOD;
			ans = ans * sum % MOD;
			continue;
		}
		for(int i = 0;i < ne[u].size();i ++){
			if(i && ne[u][i] == ne[u][i - 1]) continue;//忽略重边
			int v = ne[u][i];
			long long sum = 0;
			for(int i = 1;i <= m;i ++){//前缀和统计
				sum = (sum + f[u][i]) % MOD;
				f[v][i] = f[v][i] * sum % MOD;
			}
			if(!-- d[v]) q.push(v);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：kkxacj (赞：3)

#### 前言

做 C 做了好久，如果没有这道题就掉分了。

#### 思路

首先很容易想到要缩点，一个环上的数值肯定都是一样的。

缩完点后，图就变成了多个 `DAG`，每个肯定是单独计算贡献，设 $f_{i,j}$ 表示第 $i$ 个点值为 $j$ 的方案数，$f_{x,j}= \prod_{y \in son_{x}} \sum_{k \le j}f_{y,k}$，预处理 $\sum_{k \le j}f_{y,k}$，然后乘的话直接乘，复杂度 $n^2$ 可以接受。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2030,mod = 998244353;
int n,m,f[N][N],a[N],sum,ans,col[N],o,vis[N],st[N],tot,head[N],cnt,cnt1,dfn[N],low[N],in[N],v[N],g[N];
struct w
{
	int to,nxt;
}b[N*2];
inline void add(int x,int y)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y;
	head[x] = cnt;
}
void dfs(int x,int fa)
{
	dfn[x] = low[x] = ++cnt1; st[++tot] = x;
	for(int i = head[x];i;i = b[i].nxt)
	{
		if(!dfn[b[i].to])
		{
			dfs(b[i].to,x);
			low[x] = min(low[x],low[b[i].to]);
		}
		else if(!vis[b[i].to]) low[x] = min(low[x],dfn[b[i].to]); 
	}
	if(dfn[x] == low[x])
	{
		o++;
		while(st[tot] != x) col[st[tot]] = o,vis[st[tot]] = 1,tot--;
		col[st[tot]] = o,vis[st[tot]] = 1,tot--;
	}
}
void dfs1(int x)
{
	for(int i = 1;i <= m;i++) f[x][i] = 1;
	for(int i = head[x];i;i = b[i].nxt)
	{
		dfs1(b[i].to);
		sum = 0;
		for(int j = 1;j <= m;j++)
		{
			sum = (sum+f[b[i].to][j])%mod;
			f[x][j] = f[x][j]*sum%mod;
		}
	}
}
signed main()
{
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(a[i]),add(a[i],i);
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) dfs(i,0);
	cnt = 0;
	for(int i = 1;i <= n;i++) head[i] = 0;
	for(int i = 1;i <= n;i++)
		if(col[a[i]] != col[i]) 
			add(col[a[i]],col[i]),in[col[i]]++;
	for(int i = 1;i <= m;i++) g[i] = 1;
	for(int i = 1;i <= o;i++)
		if(!in[i])
		{
			dfs1(i);
			sum = 0;
			for(int j = 1;j <= m;j++)
			{
				sum = (sum+f[i][j])%mod;
				g[j] = g[j]*sum%mod;
			}
		}
	for(int i = 1;i <= m;i++) ans += g[i]; 
	print(g[m]%mod); flush();
	return 0;
}
/*
*/
```

---

## 作者：_anll_ (赞：2)

比 C 和 E 简单。
## 思路
这题看起来很需要建图的亚子。具体地，因为对于 $x_i$ 而言，它至多能被另外一个点（否则就是自己），也就是 $x_{A_i}$ 限制，因此它应该会组成一个基环树森林。

先讨论在环上的点。如果 $a,b$ 成环，说明 $a\ge b,b\ge a$，那么当且仅当 $a=b$ 时成立。同理，若有若干个点成环，则说明它们应当相互相等。此时把它们视为一个点，即缩在一起即可。我这里无脑 tarjan 了，时间复杂度 $O(n)$，或许有更简单的做法。

缩完后得到新图，应当是一张普通森林，我们针对每棵树单独讨论。令 $l$ 为 $x$ 的子节点，因为 $l$ 的取值关于且仅关于它的祖先，所以考虑简单的树形 dp。具体地，令 $dp[x][i]$ 表示当 $x$ 取 $i$ 这个值时以 $x$ 为根的方案数个数，显然 $dp[x][i]=\prod_{l\in son[x]}\sum^{j=1}_{j\le i} dp[l][j]$。稍微优化一下计算过程，总 dfs 的时间复杂度就可以达到 $O(nm)$，轻松通过本题。

## 代码
```cpp
#include<vector>
#include<iostream>
#define int long long
#define mod 998244353
using namespace std;
const int N=3005;
int n,m,ans,num[N],vu[N],dp[N][N];
int tot,dfn[N],low[N];
int top,stk[N],instk[N];
int cnt,scc[N],scs[N];
vector<int> edges[N],ed[N];
void tarjan(int x){
	dfn[x]=low[x]=++tot;
	stk[++top]=x,instk[x]=1;
	for(auto l:edges[x]){
		if(!dfn[l]){
			tarjan(l);
			low[x]=min(low[x],low[l]);
		}
		else if(instk[l]) low[x]=min(low[x],dfn[l]);
	}
	if(dfn[x]==low[x]){
		int y;cnt++;
		do{
			y=stk[top--];instk[y]=0;
			scc[y]=cnt,scs[cnt]++;
		}while(x!=y);
	}
}
void dfs(int x,int fa){
	for(int i=1;i<=m;i++) dp[x][i]=1;
	for(auto l:ed[x]){
		if(l==fa) continue;
		dfs(l,x);int an=0;
		for(int i=1;i<=m;i++){
			an=(an+dp[l][i])%mod;
			dp[x][i]=dp[x][i]*an%mod;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=1;i<=n;i++)
		edges[num[i]].push_back(i);
	for(int i=1;i<=n;i++) if(!low[i]) tarjan(i);
	for(int f=1;f<=n;f++){
		for(auto l:edges[f]){
			if(scc[l]==scc[f]) continue;
			ed[scc[f]].push_back(scc[l]);
			vu[scc[l]]=1;
		}
	}
	for(int i=1;i<=cnt;i++)
		if(!vu[i]) ed[cnt+1].push_back(i);
	dfs(cnt+1,0);
	cout<<dp[cnt+1][m];
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
考虑树形动态规划。

对于一个节点 $i$，从 $A_i$ 向 $i$ 连边。

由于如果出现环，则环中的数字一定都相等。

因为一个环一定没有入度，所以从 $0$ 向这个环缩点后的编号连边。

最后对于以 $0$ 为根节点的树进行树形动态规划。记 $f_{i,j}$ 表示以 $i$ 为根的子树中 $i$ 号点权值为 $j$ 的方案总数，在用 $g_{i,j}$ 表示所有子结点权值小于等于 $j$ 的方案总数。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2030;
const int MOD=998244353;
struct T
{
	int ne,to;
}e[2*N];
int he[N],idx,dfn[N],low[N];
int f[N][N],n,m,vis[N],c[N];
int top,cnt,k,scc[N],a[N],d[N];
ll g[N][N];
void add(int x,int y)
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
	d[y]++;
}
void tarjan(int x)//缩点
{
	dfn[x]=++cnt;
	low[x]=cnt;
	vis[x]=1;
	c[++top]=x;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(low[x]>=dfn[x])
	{
		int y;
		k++;
		do
		{
			y=c[top];
			top--;
			vis[y]=0;
			scc[y]=k;
		}while(y!=x);
	}
}
void dfs(int x)//树形DP
{
	for(int i=1;i<=m;i++)g[x][i]=1;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		dfs(y);
		int sum=0;
		for(int j=1;j<=m;j++)
		{
			sum=(sum+f[y][j])%MOD;
			g[x][j]=g[x][j]*sum%MOD;
		}
	}
	for(int i=1;i<=m;i++)f[x][i]=(f[x][i]+g[x][i])%MOD;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		add(a[i],i);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	memset(he,0,sizeof(he));
	memset(d,0,sizeof(d));
	idx=0;
	for(int i=1;i<=n;i++)
		if(scc[a[i]]!=scc[i])
			add(scc[a[i]],scc[i]);
	n=k;
	for(int i=1;i<=n;i++)
		if(!d[i])add(0,i);
	dfs(0);
	cout<<f[0][m]<<'\n';
	return 0;
}

```

---

## 作者：zhangshirui (赞：1)

### 题目大意：

给你一个长度 $n$ 为数组 $A$，求出有多少个序列 $x$，满足 $x$ 中每个元素都在 $1$ 到 $m$ 之间的整数且其中第 $i$ 个元素小于等于第 $A_i$ 个元素，问有多少个合法的 $x$，数量对 $998244353$ 取模

### 题解：

如果我们把这个问题的依赖关系看作一个图，$A_i$ 看作一条$i$ 到 $A_i$ 的有向边，那么这个图显然是一个**内向的基环树森林**，显然环上的点的权值全部相同，所以考虑树形dp。

我们先对每个基环树分别考虑：

第一步，先找出每一个环，并对每个点的所属的环编号，因为 $n$ 小所以不乱搞应该都可以吧。

第二步，就是对每个点分别dp了，记 $dp_{i,j}$ 为 $i$ 号点值为 $j$ 的方案数，如何转移呢，设 $son_i$ 为 $A_x=i$ 的所有 $x$ 的集合,那它的转移方程式这样的：

$$dp_{i,j}=\prod_{x \in son_i} \sum_{y=1}^jdp_{x,y}$$

上面的式子求和部分很麻烦，前缀和一下即可，然后按照深度从下往上递推即可。但是要注意，环上的点不能作为转移的的来源。

现在我们已经得到了每个点的答案，如何得到一个环的答案呢？我们记 $ans_{i,j}$ 为第 $i$ 个环上全部选 $j$ 的答案，设第 $i$ 个环上的点集为 $R_i$，有：

$$ans_{i,j}=\prod_{x \in R_i}dp_{x,j}$$

因为每个点的子树选什么显然不被别的子树影响。而第 $i$ 个基环树上的所有贡献即为：

$$\sum_{j=1}^mans_{i,j}$$

为什么是求和呢？应为每一个颜色显然只能选其一，应该用加法原理。

那么基环树直接怎么合并呢？直接相乘即可，反正他们又不联通，不会互相影响。

### 代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
ll fa[2030],n,m,tot=0,on_rt[2030],ans[2030][2030],dp[2030][2030],sx[2030],dep[2030];
vector<int> edge[2030];
bool on_rotate(int x){//暴力找环，反正n小 
	int g=fa[x];
	for(int i=0;i<=n;i++){
		if(g==x){
			++tot;
			for(int i=0;i<=n;i++){
				on_rt[g]=tot;
				g=fa[g];
			}
			return 1;
		}
		g=fa[g];
	}
	return 0;
}
void dfs(int i,int d=0){//求出每个点的深度，用于确定dp顺序 
	dep[i]=d;
	for(int j:edge[i]){
		if(j!=fa[i]&&on_rt[j]==0)dfs(j,d+1);
	}
}
bool cmp(int i,int j){//用于按深度排序 
	return dep[i]>dep[j];
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>fa[i];
		edge[fa[i]].push_back(i);
		sx[i]=i;
	}
	for(int i=1;i<=n;i++)if(on_rt[i]==0)on_rotate(i);//找所有环 
	for(int i=1;i<=n;i++)if(on_rt[i])dfs(i);//对于每个环上的点，跑它的子树中每个点的深度 
	sort(sx+1,sx+1+n,cmp);//按深度排序降序，确定dp顺序 
	for(int i=0;i<2030;i++)for(int j=0;j<2030;j++)ans[i][j]=dp[i][j]=1;//初始化 
	for(int i=1;i<=n;i++){
		#define i sx[i]//原因是每次用sx[i]太麻烦了 
		ll sum=0;
		if(on_rt[i]==0)for(int j=1;j<=m;j++)sum=(sum+dp[i][j])%mod,dp[fa[i]][j]=dp[fa[i]][j]*sum%mod;//转移的另一种写法，从下往上转移 
		#undef i//撤销上面的宏定义，让后面正常使用 
	}
	for(int i=1;i<=n;i++){
		if(on_rt[i]){
			for(int j=1;j<=m;j++)ans[on_rt[i]][j]=ans[on_rt[i]][j]*dp[i][j]%mod;//求每个环的零散贡献 
		}
	}
	ll anss=1;//记录最终答案 
	for(int i=1;i<=tot;i++){
		ll sum=0;//记录这个环的完整贡献 
		for(int j=1;j<=m;j++){
			sum+=ans[i][j];
			sum%=mod;
		}
		anss*=sum;//直接乘 
		anss%=mod;
	}
	cout<<anss;
}
```

最后闲话两句：

我赛时求深度的dfs中 `on_rt[j]` 打成了 `on_rt[i]`，然后赛后五分钟调出来了，大悲。

顺带附一个我调试用的样例：

```
7 5
2 1 2 2 1 5 5
```

---

## 作者：_determination_ (赞：0)

E>>>F。

注意到建图之后是内向基环树，对于一个环显然取值应当一样。

那么显然要缩点，然后留下一个树，直接树上 dp。

$f_{x,y}$ 到第 $x$ 个点取值 $y$ 的方案数，然后是简单的。

[Link.](https://atcoder.jp/contests/abc387/submissions/61392838)

---

## 作者：Liuhy2996 (赞：0)

## 思路
建图，$i$ 指向 $a_i$，图实际上是基环树，环上的点都相同，可以缩成一个点。这样就变成了树形 dp 问题，$dp_{u,i}$ 表示以 $u$ 为根的子树中，$u$ 取 $i$ 时情况数。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e3+10,mod=998244353;
int n,m,ans=1,t,st[N],f[N],a[N],in[N],d[N],dp[N][N];
queue<int>q;
vector<int>e[N];
void dfs(int u){
	for(int i=1;i<=m;++i) dp[u][i]=1;
	for(int v:e[u]){
		dfs(v);
		for(int i=1;i<=m;++i) dp[u][i]=dp[u][i]*dp[v][i]%mod;
	}
	for(int i=1;i<=m;++i) dp[u][i]=(dp[u][i]+dp[u][i-1])%mod;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i],f[i]=i,++in[a[i]];
	for(int i=1;i<=n;++i)
		if(!in[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(); q.pop();
		--in[a[u]];
		if(!in[a[u]]) q.push(a[u]);
	}
	for(int i=1,p;i<=n;++i)
		if(in[p=i]){
			st[++t]=i;
			do{f[p]=i,in[p]=0,p=a[p];}while(p!=i);
		}
	for(int i=1;i<=n;++i)
		if(f[i]!=f[a[i]]) e[f[a[i]]].push_back(f[i]);
	for(int i=1;i<=t;++i) dfs(st[i]),ans=ans*dp[st[i]][m]%mod;
	cout<<ans;
	return 0;
}
```

---

