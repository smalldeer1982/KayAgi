# [BalticOI 2018] 路径

## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day2「[Paths](https://boi18-day2-open.kattis.com/problems/boi18.paths)」**

给定一张 $N$ 个点 $M$ 条边的无向图，每个点有一个颜色，所有点的颜色共有 $K$ 种，编号为 $1\ldots K$。求图上有多少条长度至少为 $2$ 的简单路径，满足路径上的每一个点的颜色互不相同。

路径上的点的连接顺序不同看作不同的两条路径。

## 说明/提示

#### 样例 1 解释
![](https://gitee.com/mingqihuang/pics/raw/master/pathsfig.pdf.svg)

样例 1 中表达的图如上图所示。每个点的底色分别为白色（颜色 $1$）、灰色（颜色 $2$）或黑色（颜色 $3$）。共有 $10$ 条路径满足路径上的所有点的颜色都不同。它们是：``1-2``, ``2-1``, ``2-3``, ``3-2``, ``2-4``, ``4-2``, ``1-2-4``, ``4-2-1``, ``3-2-4`` 和 ``4-2-3``。

注意 ``1`` 不能看作是一条路径，因为一条路径至少连接两个点。``1-2-3`` 也不满足条件，因为有两个点都是 $1$ 号颜色。

|子任务|分值|数据范围|
|:--:|:--:|:--:|
|$1$|$23$|$1 \leqslant N,M \leqslant 100, 1 \leqslant K \leqslant 4$|
|$2$|$20$|$1 \leqslant N,M \leqslant 300\,000, 1 \leqslant K \leqslant 3$|
|$3$|$27$|$1 \leqslant N,M \leqslant 300\,000, 1 \leqslant K \leqslant 4$|
|$4$|$30$|$1 \leqslant N,M \leqslant 100\,000, 1 \leqslant K \leqslant 5$|

感谢 Hatsune_Miku 提供的翻译

## 样例 #1

### 输入

```
4 3 3
1 2 1 3
1 2
2 3
4 2```

### 输出

```
10

```

## 样例 #2

### 输入

```
9 11 4
1 2 3 4 1 2 1 2 2
1 2
1 3
2 3
2 4
3 6
6 2
6 5
4 3
4 5
7 8
9 8```

### 输出

```
70```

# 题解

## 作者：Hatsune_Miku (赞：4)

### Paths

### 路径

**翻译自 [BalticOI 2018 Day 2 题解](https://boi2018.progolymp.se/spoiler-day2.pdf)**

#### 子任务 1

暴力枚举所有合法的路径就可以得到子任务 1 的分数（见下面的算法，去掉记忆化搜索和动态规划部分以达到指数级复杂度）。

#### 子任务 2

因为颜色数最多为 $3$，所以路径的长度最多为 $3$，即路径的长度为 $2$ 或 $3$。长度为 $2$ 的路径条数容易计算：即起点和终点颜色不同的边的条数。长度为 $3$ 的路径条数需要更多的思考。我们可以通过枚举路径中间的一个点是哪一个点与起点终点的颜色来处理这个问题。那么以这个点为中间节点的路径条数就是与中间点相连的第一个颜色的点的个数和与中间点相连的第二个颜色的点的个数的乘积。

#### 子任务 3

子任务 3 是对子任务 2 的自然延伸。我们不枚举中间点是什么，而是枚举中间的一条**边**是什么，其余部分与子任务 2 完全一致。

#### 子任务 4

假设存在一个函数 $f$ 表示以某个点为起点的合法路径条数。那么答案就是对所有点的 $f$ 函数求和。关键在于因为数据很大，如何高效地计算函数 $f$ 的值。

令函数 $f$ 有两个参数 $c$（当前点）与 $C$ （一个表示目前已经用过的颜色的 ``bitset``，初始为 $0$）。由于一条路径上的颜色个数最多为 $5$，所以这样的 ``bitset`` 最多有 $2^5=32$ 个。这意味着函数 $f(c,\,C)$ 的参数的组合数小到我们可以打表：我们使用动态规划算法。

对参数 $c$ 和 $C$ 进行记忆化搜索，我们需要对所有相邻 $c$ 和 $C$ 将函数 $f(c',\,C')$ 的值求和，其中 $C'$ 为与 $C$ 相同的 ``bitset``，但是表示颜色 $c$ 的二进制位被标记了。我们保证不重复使用颜色，并且不会重复计算之前计算过答案的状态的答案。如此以来，问题的答案就是 $\sum f(i,\, 0)$ （需要保证不要计算长度为 $1$ 的路径！），还要注意使用 $64$ 位整数。

算法的时间复杂度为 $\mathcal{O}(2^{K}N)$。

有趣的一些东西：这个问题实质上是关于统计最大长度为 $k$ 的各点颜色不相同的路径条数。这个问题比计算长度最大为 $k!$ 的 **所有** 路径条数简单。后者暴力算法的复杂度为 $n^k$ 而不是 $2^kn$。这种思想可以作为一种通用算法技术提高多种问题的求解速度：多次随机选择颜色（严格的说，$O((\log n)^k)$ 次），然后使用一种限制各点颜色不同的算法。


---

## 作者：GLZP (赞：4)

本题的数据范围已经很明显的提示使用状压dp了，那么我们从状压方向入手

令dp[u][00000]为，走到u点，已经走了哪些颜色的方案数

预处理步骤：将dp[u][1<<(col[u]-1)]设为1

此时我们有两种方案：

一种先枚举点，再枚举状态进行转移

一种先枚举状态，再枚举点进行转移

前者会发现，某一状态的点可能会因为其它点还未被遍历，导致方案数未统计完全

比如遍历到点i，点i+1可以转移到i点，但点i+1的状态还没处理出来，导致i+1的方案不能统计到i点上

所以我们使用后者进行状态转移

状态转移的代码如下

```cpp
for(ll i=1;i<=S;i++)
	{
		ll t=book[i];//t看做状态就好了
		for(ll j=1;j<=n;j++)
		{
			if(dp[j][t])
			{
				if(check(t)>=2)ans+=dp[j][t];
               			//选择2个点以上才统计进答案
				for(ll k=head[j];k;k=next[k])
				{
					ll v=to[k];
					if(t&(1<<(col[v]-1)))continue;
					dp[v][t|(1<<(col[v]-1))]+=dp[j][t];
				}
			}
		}
	}
```



AC code
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
#define lowbit(i) i&(-i)
using namespace std;ll cnt=0;
ll head[300010],next[600010],to[600010];
void add(ll u,ll v)
{
	to[++cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt;
}
ll n,m,k,S,col[300010],dp[300010][32];//走到u点，已经经过了某些点 
ll check(ll x)
{
	ll cnt=0;
	while(x)
	{
		x-=lowbit(x);
		cnt++;
	}
	return cnt;
}
ll book[300010];
bool cmp(ll a,ll b)
{
	return check(a)<check(b);
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(ll i=1;i<=n;i++)scanf("%lld",&col[i]);
	S=(1<<k)-1;
	for(ll i=1;i<=S;i++)book[i]=i;
	sort(book+1,book+S+1,cmp);
	for(ll i=1;i<=m;i++)
	{
		ll x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(ll i=1;i<=n;i++)dp[i][(1<<(col[i]-1))]=1;
	ll ans=0;
	for(ll i=1;i<=S;i++)
	{
		ll t=book[i];
		for(ll j=1;j<=n;j++)
		{
			if(dp[j][t])
			{
				if(check(t)>=2)ans+=dp[j][t];
				for(ll k=head[j];k;k=next[k])
				{
					ll v=to[k];
					if(t&(1<<(col[v]-1)))continue;
					dp[v][t|(1<<(col[v]-1))]+=dp[j][t];
				}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：activeO (赞：3)

## 题目大意

本题[题面](https://www.luogu.com.cn/problem/P4796) 讲的比较清楚了，这里不细说。

## 思路

考虑状压 dp，$ dp_{i,S} $ 表示走到 i 点，已用颜色的状态是 S 的方案数。

初始化：很显然 $ dp_{i,1<<(a_i-1)} $ 应该初始化为 1。

转移：先枚举状态，再枚举点进行转移，如果有两个点以上（即 S 中有 2 个 1 以上）就可以统计进答案。

易得转移方程：$ dp_{v,t|(1<<(a_v)-1)} \gets dp_{v,t|(1<<(a_v)-1)} + dp_{j,t} $

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=3e5+10;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],n,m,k,s;
int dp[maxn][40],a[maxn];
int dt[maxn],cnt=0,ans=0;

void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int lowbit(int x){
	return x&(-x);
}
int num1(int x){
	int res=0;
	while(x){
		res++;
		x-=lowbit(x);
	}
	return res;
}

bool cmp(int x,int y){
	return num1(x)<num1(y);
}

inline void init(){
	s=(1<<k)-1;
	for(int i=1;i<=s;i++) dt[i]=i;
	sort(dt+1,dt+s+1,cmp);
	memset(dp,0,sizeof(dp));
	memset(head,-1,sizeof(head));
}
void solve(){
	for(int i=1;i<=n;i++) dp[i][1<<(a[i]-1)]=1;
	for(int i=1;i<=s;i++){
		int tmp=dt[i];
		for(int j=1;j<=n;j++){
			if(dp[j][tmp]){
				if(num1(tmp)>=2) ans+=dp[j][tmp];
				for(int k=head[j];k!=-1;k=e[k].nxt){
					int v=e[k].to;
					if(tmp&(1<<(a[v]-1))) continue;
					dp[v][tmp|(1<<(a[v]-1))]+=dp[j][tmp];
				}
			}
		}
	}
}

signed main(){
	
	scanf("%lld %lld %lld",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	
	init();
	
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%lld %lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	
	solve();
	
	printf("%lld\n",ans);
	
	return 0;
}


```


---

## 作者：huhexuan (赞：2)

看到此题，我的评价是我国 OI 遥遥领先。

注意到颜色个数只有 5，考虑状压。

$dp$ 数组第一维为当前枚举到第二个点，第二维则是当前该路径中的所有点中的颜色状态，其中的值即为当前状态的路径总数。

当该状态中的颜色个数超过 2 时，发现由于我们保证了颜色互不相同，所以此时的点的个数也超过了 2 将当前状态的 $dp$ 值累加答案即可。

状态转移极为简单，留给读者自行思考。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,a[300005],dp[300005][100],ans; 
vector<int>vec[300005];
int lowbit(int x)
{
    return x&-x;
}
int solve(int x)
{
	int cnt=0;
	while(x>0) x-=lowbit(x),cnt++;
	return cnt;
}
signed main() 
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i],dp[i][1<<(a[i]-1)]=1;
    for(int i=1;i<=m;i++)
    {
    	int a,b;
    	cin>>a>>b;
    	vec[a].push_back(b);
    	vec[b].push_back(a); 
	}
	for(int i=0;i<(1<<k);i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(solve(i)>1) ans+=dp[j][i];
			for(auto it:vec[j])
			{
				if(i&(1<<(a[it]-1))) continue;
				dp[it][i+(1<<(a[it]-1))]+=dp[j][i];
			}
		}
	}
	cout<<ans;
    return 0;
}

---

## 作者：Error_Eric (赞：2)

### Statement

[Link](https://www.luogu.com.cn/problem/P4796)

### Sol

这里提供一种更加简短的实现方式。目前的 submision 中最短的，~~win~~。

考虑状态压缩， $f_{i,b}$ 表示到了 $i$ 号节点，已经经过过的颜色集合为 $b$ 的方案数。特殊地，如果 $|b|=1$，那么 $f_{i,b}=1$。

显然来源状态是 $f_{j,b-\{c_i\}}$。注意这里 $b-\{c_i\}$ 表示的是 $\{x:x\in b,x\not=c_i\}$ 这个集合，状压的代码实现是 ``f[j][b^(1<<c[i])]``。枚举 $j$ 即可。每条边造成的转移次数不多于 $2^k$ 次，因此复杂度是对的。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
const int _=3e5+50;
int n,m,k,c[_],u,v;
long long f[_][1<<6],ans;
vector<int>e[_];
void fun(int val,int pos){
    int fr=val^(1<<c[pos]);
    if(fr==0) f[pos][val]=1; // 如果 |val|=1
    else{// 否则
        for(auto&to:e[pos]) // 枚举来源点
            f[pos][val]+=f[to][fr]; //转移
        ans+=f[pos][val]; // 直接统计进答案
    }
}
int main(){
    ios::sync_with_stdio(0),
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        cin>>c[i],--c[i];
    for(int i=1;i<=m;i++)
        cin>>u>>v,
        e[u].push_back(v),
        e[v].push_back(u);
    for(int i=1;i<(1<<k);i++)
    // 枚举状态。这个顺序是对的，想想为什么（
        for(int j=1;j<=n;j++)//枚举点
            if(i&(1<<c[j]))
                fun(i,j);//计算当前位置的 dp 值
    cout<<ans<<endl;
}
```

---

## 作者：TemplateClass (赞：1)

$\gdef \dp{\mathrm{dp}}$
$\gdef \col{\mathrm{color}}$

一个很神金的做法。

状态和大家设的一样，就是 $\dp _ {u, S}$ 表示走到 $u$ 点，状态为 $S$ 的方案数。

然后我们直接 bfs，初始时队列里是 $\left(i, 2 ^ {\col _ i - 1}\right)$，然后每次到一个结点就计算一下对答案的贡献。

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<utility>

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;

constexpr int N = 3e5 + 1;
constexpr int K = 5 + 1;

int n, m, k, col[N]; std::vector<int> G[N];
ull dp[N][1 << K], ans = 0ull;

inline void solve_bfs() {
	std::queue<pii> que;
	for(int i = 1; i <= n; ++i) {
		que.emplace(i, 1 << (col[i] - 1));
	}
	while(!que.empty()) {
		auto [u, mask_u] = que.front(); que.pop();
		if(!dp[u][mask_u]) continue;
		for(const auto& v : G[u]) {
			if(mask_u & (1 << (col[v] - 1))) continue;
			int new_mask = mask_u | (1 << (col[v] - 1));
			if(__builtin_popcount(new_mask) >= 2) ans += dp[u][mask_u];
			if(!dp[v][new_mask]) que.emplace(v, new_mask);
			dp[v][new_mask] += dp[u][mask_u];
		}
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n >> m >> k;
	for(int i = 1; i <= n; ++i) {
		std::cin >> col[i];
		dp[i][1 << (col[i] - 1)] = 1ull;
	}
	for(int i = 1; i <= m; ++i) {
		int u, v; std::cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	
	solve_bfs();
	std::cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
记 $f_{i,S}$ 表示以第 $i$ 个点为起点，路径颜色状态为 $S$ 的方案总数。

设每个点的颜色为 $c_i$。

对于每一个与 $i$ 相邻的点 $y$，且 $c_y\not=c_i$，可以得到这一项对 $f_{i,S}$ 的贡献为 $f_{y,S-2^{c_i}}$。

考虑记搜。

注意到走到第 $i$ 项时走第 $k$ 步的方案一定只会走一次，所以记录一下即可。

可以暴力枚举状态暴力判断。

由于每个状态只会搜一遍，故复杂度为 $O(N\times 2^K)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
typedef long long ll;
struct T
{
	int ne,to;
}e[2*N];
int c[N],he[N],idx;
ll f[N][1<<5],ans,vis[N][10];
void add(int x,int y)//建边
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
}
inline int get(int x)//判断状态x需走的步数
{
	int cnt=0;
	while(x)
	{
		x^=x&(-x);
		cnt++;
	}
	return cnt;
}
void dfs(int x,int k)
{
	if(vis[x][k]||k==1)return;
	vis[x][k]=1;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		dfs(y,k-1);
		for(int i=0;i<(1<<5);i++)
			if((i&(1<<c[x]))&&get(i)==k)//包含c[x]且步数为k
				f[x][i]+=f[y][i^(1<<c[x])];
		if(k==2)f[x][(1<<c[x])|(1<<c[y])]+=c[x]!=c[y];
	}
	for(int i=0;i<(1<<5);i++)
		if(get(i)==k)ans+=f[x][i];//答案为所有f[i][S]之和
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		c[i]--;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		dfs(i,k);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：panxz2009 (赞：1)

简单题。

容易发现 $K$ 很小，考虑状压。设 $f_{i,S}$ 表示当前的路径以 $i$ 作为路径终点，颜色集合为 $S$ 时，满足路径上每个点颜色各不相同的路径数。

转移时考虑枚举当前点 $x$ 的所有直接连接的所有点 $y$，如果 $y$ 的颜色不在集合 $S$ 里，说明 $y$ 可以被加到路径中，且颜色集合多一种颜色 $col_y$。
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 3e5 + 10;
int n, m, k, col[maxn], x, y;
LL f[maxn][1 << 6], ans;
vector <int> G[maxn];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &col[i]);
		f[i][1 << (col[i] - 1)] = 1;
	}
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int s = 0; s < (1 << k); s++) {
		for(int x = 1; x <= n; x++) {
			for(int y : G[x]) {
				if(s & (1 << (col[y] - 1))) continue;
				f[y][s | (1 << (col[y] - 1))] += f[x][s];
			}
		}
	}
	for(int s = 0; s < (1 << k); s++) {
		for(int x = 1; x <= n; x++) {
			if(__builtin_popcount(s) >= 2) ans += f[x][s];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

