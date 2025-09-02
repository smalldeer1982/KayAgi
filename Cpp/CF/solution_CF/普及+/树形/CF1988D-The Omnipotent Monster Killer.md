# The Omnipotent Monster Killer

## 题目描述

You, the monster killer, want to kill a group of monsters. The monsters are on a tree with $ n $ vertices. On vertex with number $ i $ ( $ 1\le i\le n $ ), there is a monster with $ a_i $ attack points. You want to battle with monsters for $ 10^{100} $ rounds.

In each round, the following happens in order:

1. All living monsters attack you. Your health decreases by the sum of attack points of all living monsters.
2. You select some (possibly all or none) monsters and kill them. After being killed, the monster will not be able to do any attacks in the future.

There is a restriction: in one round, you cannot kill two monsters that are directly connected by an edge.

If you choose what monsters to attack optimally, what is the smallest health decrement you can have after all rounds?

## 说明/提示

In the first test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1 $ , so your health decreases by $ 10^{12} $ . Then kill the monster on vertex $ 1 $ .
- In the second round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 10^{12} $ .

In the second test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1,2,3,4,5 $ , so your health decreases by $ 47+15+32+29+23=146 $ . Then kill the monsters on vertex $ 1,4,5 $ .
- In the second round: first, receive the attack from the monster on vertex $ 2,3 $ , so your health decreases by $ 15+32=47 $ . Then kill the monsters on vertex $ 2,3 $ .
- In the third round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 193 $ .

In the third test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1,2,3,4,5,6,7 $ , so your health decreases by $ 8+10+2+3+5+7+4=39 $ . Then kill the monsters on vertex $ 1,3,6,7 $ .
- In the second round: first, receive the attack from the monster on vertex $ 2,4,5 $ , so your health decreases by $ 10+3+5=18 $ . Then kill the monsters on vertex $ 2,4,5 $ .
- In the third round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 57 $ .

## 样例 #1

### 输入

```
3
1
1000000000000
5
47 15 32 29 23
1 2
1 3
2 4
2 5
7
8 10 2 3 5 7 4
1 2
1 4
3 2
5 3
6 2
7 5```

### 输出

```
1000000000000
193
57```

# 题解

## 作者：lfxxx (赞：15)

默认游戏从第 $0$ 回合开始。

注意到，假若令点 $u$ 邻域上的点操作回合集合为 $S_u$，那么有 $u$ 的最优操作时间就是 $\text{mex}(S_u)$ 而一个显然的事实是 $\text{mex}(S_u) \leq d_u$。

考虑设计状态 $dp_{u,i}$ 表示考虑点 $u$ 的子树，点 $u$ 第 $i$ 个回合被操作的最小代价，每次加入一个儿子 $v$，有 $dp_{u,i} \gets dp_{u,i} \times \min_{j \not = i}( dp_{v,j})$，而 $i \leq d_v$ 的转移对 $dp_{v,j}$ 预处理出前缀后缀 $\min$ 后即可 $O(d_v)$ 地完成，对于 $i > d_v$ 地转移我们发现 $dp_{u,i}$ 的增量都是 $\min(dp_{v,i})$ 所以用一个差分处理即可。

时间复杂度 $O(\sum d_i)$ 也就是 $O(n)$。

[赛时代码。](https://codeforces.com/contest/1988/submission/270711194)

---

## 作者：Alex_Wei (赞：14)

### [CF1988D The Omnipotent Monster Killer](https://www.luogu.com.cn/problem/CF1988D)

思想类似的题目：[CF1740H](https://www.luogu.com.cn/problem/CF1740H)。

考虑每个点被删去的时刻 $t_i$，则失去的血量为 $\sum_{i = 1} ^ n a_i t_i$，而不能同时删去相邻的点等价于相邻点的 $t_i$ 不同。显然存在 $\mathcal{O}(n\max t_i)$ 的树形 DP，现在要分析 $\max t_i$ 的上界。

设与 $i$ 相邻的点集为 $S$，则 $t_i$ 等于所有 $t_j\ (j\in S)$ 的 MEX，即最小的没有出现在 $\{t_j\}$ 当中的正整数。否则令 $t_i$ 等于该值，方案依然合法且代价更小。

设 $t_i = T$。以 $i$ 为根，则存在 $i$ 的 $T - 1$ 个儿子 $s_1, \cdots, s_{T - 1}$ 满足 $t_{s_j} = j\ (1\leq j < T)$。而 $t_{s_j} = j < T = t_i$，所以对于 $s_j$ 而言，为了能让 $t_{s_j}$ 取到 $j$，$t_i$ 是不产生贡献的，换言之，只能是 $s_j$ 的儿子 $r_1, \cdots, r_{j - 1}$ 满足 $t_{r_k} = k\ (1\leq k < j)$，以此类推。

设 $f_T$ 表示存在 $t_i = T$ 的树的最小大小，根据上述分析知 $f_T = 1 + \sum_{j = 1} ^ {T - 1} f_j$。由 $f_1 = 1$ 知 $f_T = 2 ^ {T - 1}$，因此 $t_i \leq \log_2 n + 1$。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1988/submission/270839086) 采用了复杂度更劣的实现。

---

## 作者：CReatiQ (赞：6)

观前提示：本题解重在记录&讲述本人~~愚蠢~~的思考历程，其它题解有更加简洁、优秀的方法。

---

这题的关键是：注意到操作次数上界较小。

而这个“注意”是有迹可循的：

如果问题只有两回合，便是一个平凡的树形 dp。

记 $f_{x,0/1}$ 为节点 $x$ 选/不选时，子树内 $\sum a$ 的最大值，则

$$
f_{x,0}=\sum_{y \in son_x} \min\{ f_{y,0},f_{y,1} \}
\\
f_{x,1}=\sum_{y \in son_x} f_{y,0}
$$

但现在问题是 $+\infty$ 回合，即所有节点最终都会被选中，我们可以把第二维换成“节点被选中的回合”。

即 $f_{x,i}$ 为节点 $x$ 在第 $i$ 回合被选中时，子树内怪物伤害的总和，则

$$
f_{x,i}=\sum_{y \in son_x}\min_{j \neq i} f_{y,j}
$$

假设 $i$ 的上界是 $I$。

$\mathcal{O}(nI)$ 预处理前后缀，便可 $\mathcal{O}(1)$ 解决 $\min$，这样整个 dp 过程也是 $\mathcal{O}(nI)$ 的。

根据数据范围可知：只要 $I$ 是 $\log$ 到根号的，这个算法便能通过，我们只需找出这样的一个**上界**（不是**上确界**）即可。

事已至此，你可以先随便写个 $I=100$ 交一发。

---

好的，题已经过了，接下来我们证明一个可以接受的**上界**。

考虑任意一条从某点到叶子的链：如果大于等于 $3$ 个相邻节点均不被选择，至少中间节点各自掏出一个不在路径上的儿子“李代桃僵”。

对于点数大于 $2$ 的情况，我们不妨强制规定：首个节点不被选择，并把“李代桃僵”的儿子们一并选入“链”中。（为了方便，下文仍将这一结构称为链）

把“李代桃僵”的儿子们插入其父亲与其父亲的后继节点之间。这样我们会得到什么？

**一条相邻三点间至少选择一点的链。**

最糟糕的情况是什么？形如 “不选-不选-选-不选-不选” 的链。即 $\frac{不选节点数}{总点数}$ 有上界 $\frac{4}{5}$。

实际上不会出现这么糟糕的情况，但记住：我们只需找出这样的一个**上界**即可。

对于点数为 $2$ 的情况，我们把叶子选上，此时 $\frac{不选节点数}{总点数}=\frac{1}{2}$。

对于点数为 $1$ 的情况：如果它父亲未选，我们把它选上；如果它父亲已选，它下回合会落单，我们不妨当它已选。

一棵树每剖下一条上述的链后，可能会变成一片森林（“李代桃僵”的儿子的儿子们会“分道扬镳”），但对森林中的每棵树，我们依然像这样递归操作，可以保证每个节点都被剖分到某条链中。

根据上面的分析，该流程循环 $\lfloor\log_{\frac{5}{4}} n\rfloor +1$ 次，便可以保证整棵树被选完。

而 $I$ 又是小于等于该流程循环次数的，所以取 $I \geq 57$ 一定可以得到正确答案。

尽管不是**上确界**，这也足矣。

---
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;

void R()
{
	int n,ans=inf;
	cin>>n;
	vector<int> a(n+1);
	vector<vector<int>> adj(n+1),f(n+1,vector<int>(61)),pre,suf;
	pre=suf=f;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=2;i<=n;i++)
	{
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	auto dfs=[&](auto self,int x,int p)->void
	{
		f[x][0]=f[x][60]=inf;
		for (int i=1;i<60;i++) f[x][i]=a[x]*i;
		for (auto y:adj[x])
		{
			if (y==p) continue;
			self(self,y,x);
			for (int i=1;i<60;i++)
				f[x][i]+=min(pre[y][i-1],suf[y][i+1]);
		}
		pre[x]=suf[x]=f[x];
		for (int i=1;i<=60;i++) pre[x][i]=min(pre[x][i],pre[x][i-1]);
		for (int i=59;i>=0;i--) suf[x][i]=min(suf[x][i],suf[x][i+1]);
	};

	dfs(dfs,1,1);
	for (int i=1;i<60;i++) ans=min(ans,f[1][i]);
	cout<<ans<<'\n';
}

signed main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while (T--) R();
	return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

设 $dp_{i,j}$ 表示节点 $i$ 点权为 $j$ 时点 $i$ 及其子树造成的损失生命值最小值。转移为：$dp_{i,j}=a_i\cdot j+\displaystyle\sum_{x\in\operatorname{son}_i}\min_{k\ne j}{dp}_{x,k}$。问题是 $j$ 的上界为多少？设 $T(n)$ 为构造出需要 $n$ 种颜色的最小点数，有 $T(n)=1+\displaystyle\sum_{i=1}^{n-1}T(i)$，且 $T(1)=1$，化简得到 $T(n)=2^{n-1}$，所以 $j$ 的上界为 $\lfloor\log n\rfloor+1$。

# Code
```cpp
#include<bits/stdc++.h>
typedef long long ll;
std::vector<int>v[300005];
ll dp[300005][20];
ll a[300005];
void dfs(int p,int dad){
	for(int i=1;i<20;++i)dp[p][i]=a[p]*i;
	for(const int&i:v[p]){
		if(i==dad)continue;
		dfs(i,p);
		for(int j=1;j<20;++j){
			static ll val;val=0x3f3f3f3f3f3f3f3f;
			for(int k=1;k<20;++k)
				if(j!=k)val=std::min(val,dp[i][k]);
			dp[p][j]+=val;
		}
	}
}
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),v[i].clear();
		for(int i=1,x,y;i<n;++i)
			scanf("%d%d",&x,&y),
			v[x].push_back(y),v[y].push_back(x);
		dfs(1,0);
		printf("%lld\n",*std::min_element(dp[1]+1,dp[1]+20));
	}
	return 0;
}
```

---

## 作者：ben090302 (赞：2)

树形dp。

形式化题意：

给每个点染色（设颜色为 $1$ 到 $w$）,相邻节点不能同色，求 $\sum\limits_{i=1}^{n}a_i col_i$ 的最小值。

考虑对于颜色的约束，我们可以使用一种类似于分层图的思想，设 $dp_{i,j}$ 表示 $i$ 染成 $j$ 色时子树内最小答案，我们很快可以想到一个转移方案：$dp_{i,j}$ 初始设为 $a_i\times j$，加上用儿子的最小值（和自己颜色不同的最小）。

就是这样：

```
for(int i=1;i<=MAXCOL;i++){
  int ass=LONG_LONG_MAX;
  for(int j=1;j<=MAXCOL;j++){
    if(i==j) continue;
      ass=min(ass,dp[x][j]);
    }
  dp[fa][i]+=(ass==LONG_LONG_MAX?0:ass);
}
```

我们发现复杂度是 $O(n(MAXCOL)^2)$，看起来好假的做法。但是我们容易发现这个 $MAXCOL$ 的大小貌似很小，感性理解以下每次染色都会把将近一半的点染成同一个颜色，下一次把剩下的点类似操作，打表或者观察几组数据发现上界大概就是 $\log n$ 了。

于是这个的复杂度就是 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=600005;
struct edge{
    int v,nxt;
}e[N];
int hd[N],tot=0;
void add(int u,int v){
     e[++tot]={v,hd[u]},hd[u]=tot;
     e[++tot]={u,hd[v]},hd[v]=tot;
}
int T;
int n,a[N];
int dp[N][25];
void dfs(int x,int fa=0){
    for(int i=hd[x];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,x);
    }
    if(x==1) return;   
    for(int i=1;i<=23;i++){
        int ass=LONG_LONG_MAX;
        for(int j=1;j<=23;j++){
            if(i==j) continue;
            ass=min(ass,dp[x][j]);
        }
        dp[fa][i]+=(ass==LONG_LONG_MAX?0:ass);
    }
}
void work(){
    for(int i=1;i<=n;i++) hd[i]=0;
    tot=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=23;j++){
            dp[i][j]=a[i]*j;
        }
    }
    dfs(1,0);
    int ans=LONG_LONG_MAX;
    for(int i=1;i<=23;i++) ans=min(ans,dp[1][i]);
    cout<<ans<<"\n";
}

signed main(){
    cin>>T;
    while(T--){
        work();
    }
    return 0;
}
```

关于上界一个稍严谨一丢丢的推导：

假设对于每个点，我们希望把颜色卡满，那就让他的孩子跟他颜色不同。这是一个比较极端的情况。

那么设 $C_n$ 表示让树内颜色数达到 $n$ 的最小节点个数，$C_n=\sum\limits^{n-1}_{i=1}(C_i)+1$，$C_1=1$，简单算下就发现 $C_n=2^{n-1}$。那么当节点数量为 $n$ 的时候颜色树就为 $\log n$ 级别了。

---

## 作者：Daniel_yao (赞：2)

# Solve

第一眼有点像最大独立集，可以考虑往这方面想。

由于有了回合的限制，所以在 dp 时要多加一维来除去回合的后效性。设 $dp_{x,y}$ 表示第 $x$ 个点在 $y$ 回合被选中带来的最小贡献。很显然初始状态 $dp_{x,y}=a_x\times y$。

转移也很显然，父亲和儿子不能在同一回合被选中，所以只需要在 dfs 中枚举所有回合，然后把所有不同回合的儿子状态取最小贡献，转移至父亲即可。

考虑回合数，因为每一次选点会将树拆成森林，然后每一个小树又会减半，继续分。所以可以证明回合数在 $\log n$ 量级。

所以转移与计算贡献加上总时间复杂度 $O(n \log^2 n)$，可以通过此题。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e18

using namespace std;

const int N = 3e5 + 10;

struct Node {
  int v, nx;
} e[N << 1];

int T, n, a[N], h[N], dp[N][25], tot, m, sum, ans = inf;

void add(int u, int v) {
  e[++tot] = (Node){v, h[u]};
  h[u] = tot;
}

void dfs(int x, int fa) {
  for (int i = h[x]; i; i = e[i].nx) {
    int y = e[i].v;
    if(y == fa) continue;
    dfs(y, x);
  }
  if(x == 1) return ;
  For(i,1,m) {
    int num = inf;
    For(j,1,m) {
      if(i == j) continue;
      num = min(num, dp[x][j]);
    }
    dp[fa][i] += (num == inf ? 0 : num); 
  }
}

void solve() {
  ans = inf; sum = tot = 0;
  For(i,1,n) h[i] = 0;
  cin >> n;
  For(i,1,n) cin >> a[i], sum += a[i];
  For(i,1,n-1) {
    int u, v;
    cin >> u >> v;
    add(u, v), add(v, u);
  }
  m = (int)ceil(log2(n))+1;
  For(i,1,n) For(j,1,m) dp[i][j] = a[i] * j;
  dfs(1, 0);
  For(i,1,m) ans = min(ans, dp[1][i]);
  cout << ans << '\n';
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：sangshang (赞：2)

# Solution

DP 不难想。设 $f_{u,k}$ 表示 $u$ 点的怪物在第 $k$ 轮击杀，并考虑以 $u$ 为根的整颗子树所造成的最小伤害。

设 $\{v_u\}$ 是 $u$ 的儿子。容易想到：

$$f_{u,k}=hit_u\times k+\sum_{x\in v_u}\min_{i\ne k}\{f_{x,i}\}$$

$hit_u$ 表示怪物的伤害。

具体处理时可按如下步骤：

1. 递归处理儿子节点。

2. 对于每个子节点 $x\in v_u$，求出 $\{f_{x,i}\}$ 的最小值和次小值（非严格），设最小值可在 $i=y$ 时取得，因为 $u$ 点的怪物在第 $y$ 轮被杀时无法取最小值，只能取次小值。所以 $f_{u,y}$ 预先累加上次小值减最小值。

3. 计算 $sum=\sum_{x\in v_u}\min{f_{v,i}}$，所有 $f_{u,k}$ 加上 $sum+hit_u\times k$。

下面证明最优方案中最后被杀的怪物轮数不超过 $\log_2 n$ 这个级别，以保证此算法时间和空间复杂度都在 $O(n\log n)$。

设在决策过程中第一轮钦定一定要杀掉的怪物集合为 $S$，此时可能产生下面两种相互之间独立的子树。

1. 设与 $S$ 不相邻的点集为 $A$，容易想到，所以 $|A|\le n-|S|$，且第一回合 A 集合还可以再选出至少一半点杀掉。证明：考虑最糟糕的情况，所有 $A$ 都连成一棵子树。就算这样，一轮把深度为奇数，一轮把深度为偶数的点杀掉，就可以两轮内杀完所有点，因此，一定有一轮杀掉的点的数量大于等于 $|A|\div 2$，且剩余的点都不相连，即剩下的子树的大小为 $1$。

2. 设和 $S$ 相邻的点集为 $B$，其中与 $i$ 相邻的集合为 $B_i$。容易想到 $|B|\le b-|S|$ 和 $B_i$ 之间互不相连，即，$B_i$ 一定在不同的子树中。考虑 $j\ne i$，$B_i,B_j$ 中一些点相连使得这些点在一个子树中。容易想到对于一个 $x\in B_i$，一个 $j\ne i$，一定最多有一个 $y\in B_j$ 使得 $x,y$ 相连。因为如果有两个的话就原图必定成环，与原图是树不符。因此 $B$ 所形成的子树大小不超过 $|S|,n-|S|$。也就是说，不管 $|S|$ 是多少，这种子树大小不超过 $n\div 2$，就算加上情况一中子树大小，也只是 $n\div 2 + 1$。

综上所述，不论怎样钦定 $S$，最后所剩下的点连成的子树一定可以不超过 $n\div 2$ 级别。子树之间相互独立，互不影响，反复利用上述结论可得，子树一定在 $\lceil\log_2 n\rceil+1$ 轮之前大小变为一。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
class edge{
	public:
		int to,nex;
		edge(int to,int nex):to(to),nex(nex) {}
		edge() {}
};
edge e[maxn<<1];
int head[maxn],tot;
inline void add_edge(int from,int to){
	e[++tot]=edge(to,head[from]),head[from]=tot;
}
long long hit[maxn];
int fa[maxn],maxround;
inline void pre_work(int u,int father){
	fa[u]=father;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(v!=father){
			pre_work(v,u);
		}
	}
}
long long f[maxn][21];
inline void Solve(int u){
	f[u][0]=0x7f7f7f7f7f7f7f7f;
	long long sum=0;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(v!=fa[u]){
			Solve(v);
			int min_it=0,c_min_it=0;
			for(int j=1;j<=maxround;++j){
				if(f[v][j]<f[v][min_it]){
					c_min_it=min_it;
					min_it=j;
				}
				else if(f[v][j]<f[v][c_min_it]){
					c_min_it=j;
				}
			}
			f[u][min_it]+=f[v][c_min_it]-f[v][min_it];
			sum+=f[v][min_it];
		}
	}
	for(int i=1;i<=maxround;++i){
		f[u][i]+=sum+hit[u]*i;
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		tot=0;
		int n;
		scanf("%d",&n);
		maxround=ceil(log2(n))+1;
		for(int i=1;i<=n;++i){
			scanf("%lld",&hit[i]);
		}
		for(int i=1;i<n;++i){
			int u,v;
			scanf("%d%d",&u,&v);
			add_edge(u,v),add_edge(v,u);
		}
		pre_work(1,0);
		Solve(1);
		long long minn=0x7f7f7f7f7f7f7f7f;
		for(int i=1;i<=maxround;++i){
			minn=min(minn,f[1][i]);
		}
		printf("%lld\n",minn);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=maxround;++j){
				f[i][j]=0;
			}
			head[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：白鲟 (赞：2)

由于树是一个二分图，最少用两轮即可选完所有点。如果考虑每次只选择一个点，也只需要 $n$ 轮即可选完，此选法显然使用了大量的冗余轮数。带来的启发是所用的轮数不会很多。

试求所用轮数的上界。若一个点必须最早在第 $k$ 轮才能被选择，则与其直接相连的点中，最早在第 $1,2,\cdots,k-1$ 轮才能被选择的点分别至少存在一个。由此，设第 $k_0$ 轮选择完所有点，固定最晚被选择的一个点为根，试求结点个数的下界 $f(k_0)$，则其子结点中在第 $1,2,\cdots,k_0-1$ 轮才能被选择的点分别恰好存在一个；递归地，对于树上的每个点，若其在第 $k$ 轮被选择，均有与其直接相连的点中，除其亲结点外，最早在第 $1,2,\cdots,k-1$ 轮才能被选择的点分别恰好存在一个。因而，有 $g(k_0)=1+\sum_{k=1}^{k_0-1}g(k)=\operatorname{O}(2^{k_0})$，则 $k_0=\operatorname{O}(\log n)$。

轮数上界控制为 $\operatorname{O}(\log n)$ 后，一个简单的解法就呼之欲出了：设 $f_{i,j}$ 表示结点 $i$ 在第 $j$ 轮被选择时，以结点为根 $i$ 的子树的贡献之和，有 $f_{i,j}=ja_i+\sum_{k\in S}\min_{t\not=j}f_{k,t}$，其中 $S$ 为 $i$ 的子结点集合，保存 $f$ 关于 $j$ 的前后缀最小值即可快速转移。时间复杂度为 $\operatorname{O}(n\log n)$。

```cpp
#include <algorithm>
#include <cstdio>
#include <climits>
const int maxn = 3e5, maxlog = 40;
using ll = long long;
int T, tot, n, x, y, head[maxn + 1], suc[maxn << 1 | 1], to[maxn << 1 | 1];
ll ans, a[maxn + 1], f[maxn + 1][maxlog + 2], minsuf[maxn + 1][maxlog + 2], minpre[maxn + 1][maxlog + 2];
inline void add_edge(int x, int y){
    suc[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
void dfs(int now, int parent) {
    minpre[now][0] = minsuf[now][maxlog + 1] = f[now][0] = f[now][maxlog + 1] = __LONG_LONG_MAX__;
    for(int i = 1; i <= maxlog; ++i)
        f[now][i] = a[now] * i;
    for(int i = head[now]; i; i = suc[i]) {
        if(to[i] != parent) {
            dfs(to[i], now);
            for(int j = 1; j <= maxlog; ++j) {
                f[now][j] += std::min(minsuf[to[i]][j + 1], minpre[to[i]][j - 1]);
            }
        }
    }
    for(int i = 1; i <= maxlog; ++i) {
        minpre[now][i] = std::min(f[now][i], minpre[now][i - 1]);
    }
    for(int i = maxlog; i; --i) {
        minsuf[now][i] = std::min(f[now][i], minsuf[now][i + 1]);
    }
    return;
}
int main() {
    scanf("%d", &T);
    while(T--) {
        ans = __LONG_LONG_MAX__;
        tot = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            head[i] = 0;
        } 
        for(int i = 1; i < n; ++i) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        dfs(1, 0);
        for(int i = 1; i <= maxlog; ++i)
            ans = std::min(ans, f[1][i]);
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：EricWan (赞：2)

我们可以把题目抽象成这样：

有无限种颜色，编号从 $1$ 开始，给树染色，有边相连的节点不同色，总价值位颜色编号与点权的乘积之和，求最小总价值。

这里的颜色编号其实就是怪物去世的轮数，怪物会在去世前的每一个回合揍你一拳（包括它去世的那一个回合）。

考虑树形 DP。

定义 $f_{i,j}$ 为以第 $i$ 个点为根的子树，第 $i$ 个点颜色为 $j$，最小的总价值。

设我们该将 $i$ 的孩子 $k$ 转移过来了，那么转移方程就是 $f_{i,j}=f_{i,j}+\min(\min_{l=1}^{l<j}f_{j,l},\min_{l=j+1}^{l\le\text{颜色总数}}f_{j,l})$。

对于颜色的总数，它是在 $\log n$ 量级的，我的证明：

想要在某一轮保护一个怪，那么一定要有一个会被保护到这一轮的怪和它连边，因为怪在一个树上，所以如果要保护，每一轮的怪数也要减半，总轮数就是 $\log n$，构造方法类似如下，下面的数据中，$1$ 号点的怪会被保护到第 $4$ 轮。

```
8
1 100 10000 10000 1000000 1000000 1000000 1000000
1 5
2 6
3 7
4 8
1 3
2 4
1 2
```

有了这个性质，我们就可以开始打代码了，如果要无脑实现刚才的转移式 $f_{i,j}=f_{i,j}+\min(\min_{l=1}^{l<j}f_{j,l},\min_{l=j+1}^{l\le\text{颜色总数}}f_{j,l})$，时间复杂度是 $O(n\times\log^2 n)$ 的，可能超时，因此我们考虑用前缀最大值和后缀最大值优化 $\min_{l=1}^{l<j}f_{j,l}$ 和 $\min_{l=j+1}^{l\le\text{颜色总数}}f_{j,l}$ 就可以通过了。

具体代码看[我的提交记录](https://codeforces.com/contest/1988/submission/270715874)。

---

## 作者：Mirage_Insane (赞：2)

## 大致题意

给树上每个点 $i$ 确定一个删除时间 $t_i$，要求每条边连接的两个点的删除时间都不一样。整棵的代价为 $\sum a_i \times t_i$。求一种方案，使得整棵树的代价最小，输出这个最小的代价。

## 题解

其实删除时间最多只会到达 $\lceil\log_n\rceil$。感性理解一下：考虑从小到大往树里面填删除时间，对于连续的未被删除的三个点 $a$，$b$，$c$（即 $a$ 是 $b$ 的父亲，$b$ 是 $c$ 的父亲），如果存在一种方案 $p$ 使得这次删除的节点仍然不含这三个点，则必定有另一种方案 $q$，其在 $p$ 的基础上多删除了 $a$，$b$，$c$ 当中的至少一个点，且依旧合法。由于删除时间是从小到大的，所以 $q$ 一定比 $p$ 更优。

推广一下，对于当前还没被删除的点，设有 $k$ 个，则当前的最优方案一定删除了至少 $\lfloor\frac{k}{2}\rfloor$ 个点。

更严谨的数学证明不会。~~咱学OI的要啥严谨的数学证明啊。~~

于是设计 $dp_{i,j}$ 表示在 $i$ 的子树中满足 $t_i = j$ 的最小代价，暴力转移就可以了。

第二维开 20 就可以过了。

### Code:

```cpp
#define Vanishment return
#define This 0
#define World ;
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
struct Edge {
	int to, nxt;
}edge[600005];
int head[300005], cnt, a[300005], dp[300005][25];
void add(int u, int v) {
	edge[++cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}
void tree_DP(int x, int fa) {
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fa) continue;
		tree_DP(to, x);
		for(int j = 1; j <= 20; j++) {
			int sum = 1e18;
			for(int k = 1; k <= 20; k++) {
				if(j == k) continue;
				sum = min(sum, dp[to][k] + k * a[to]);
			}
			dp[x][j] += sum;
		}
	}
}
signed main() {
	int T;
	SF("%lld", &T);
	while(T--) {
		int n, ans = 1e18;
		SF("%lld", &n);
		for(int i = 1; i <= n; i++) SF("%lld", &a[i]);
		for(int i = 1; i < n; i++) {
			int u, v;
			SF("%lld%lld", &u, &v);
			add(u, v), add(v, u);
		}
		tree_DP(1, 0);
		for(int i = 1; i <= 20; i++) ans = min(ans, dp[1][i] + i * a[1]);
		PF("%lld\n", ans);
		for(int i = 1; i <= n; i++) {
			head[i] = 0;
			for(int j = 1; j <= 20; j++) dp[i][j] = 0;
		}
		cnt = 0;
	}
	Vanishment This World
}
```

---

## 作者：Iniaugoty (赞：0)

Update on 8.21：有个式子打错了已改正。

>给定一颗 $n (n \le 3 \times 10 ^ 5)$ 个结点的树，每个节点有权值 $a _ i (1 \le a _ i \le 10 ^ {12})$。请你为每个节点钦定另一个权值 $t _ i (1 \le t _ i \le 10 ^ {100})$，满足对于任意树上的边 $(u, v)$，$t _ u \neq t _ v$。求 $\sum _ {i = 1} ^ {n} a _ i t _ i$ 的最小值。

首先显然有一个 $O(n \max ^ 2 t)$（或者精细实现做到 $O(n \max t)$）的树形 DP 做法。设 $dp _ {u, i}$ 表示 $t _ u = i$ 时 $\sum _ {v \in \operatorname{subtree} (u)} a _ v t _ v$ 的最小值。枚举 $u$ 的孩子 $v$ 和 $t _ v$ 进行转移，有 $dp _ {u, i} = i a _ u + \sum _ {v \in \operatorname{son} (u)} \min _ {j \neq i} {dp _ {v, j}}$。

注意到 $\max t$ 可能比较小，但你不知道它有多小。考虑从最坏情况下证明。

设当前根结点为 $u$，度数为 $d _ u$。由于 $t _ u = \operatorname{mex} _ {v \in \operatorname{son} (u)} t _ v$，想让 $t _ u$ 最大化，显然要求 $u$ 的孩子们的 $t$ 值为 $1, 2, \dots, d _ u$，则此时 $t _ u = d _ u + 1$。

设 $f _ i$ 为：使 $t _ u$ 达到 $i$ 最少需要的总点数。则由上段分析，可以得到 $f _ i = \left( \sum _ {j = 1} ^ {i - 1} f _ j \right) + 1$，并且 $f _ 1 = 1$。易得 $f _ i = 2 ^ {i - 1}$。

这意味着至少需要 $2 ^ {n - 1}$ 个点才能使 $t _ u$ 达到最大值 $n$；也即 $n$ 个结点的树，根节点 $t _ u$ 最大只能达到 $\lfloor \log n \rfloor + 1$。

于是之前所说的树形 DP 做法的时间复杂度是 $O (n \log ^ 2 n)$（或 $O (n \log n)$）。

[代码](https://codeforces.com/contest/1988/submission/272042376)，采用的是较为简单但复杂度较劣的实现。

---

## 作者：_O_v_O_ (赞：0)

我们化简一下题意：

有一个 $n$ 个点的树，第 $i$ 个点的点权为 $a_i$。

现在要给每个点分配一个权值 $b_i$，满足有边链接的 $(u,v)$，$b_u\neq b_v$。

求 $\sum_{i=1}^n a_i\times b_i$ 的最小值。

---



我们充分发挥人类智慧，猜测 $b_i\le 30$。

那么我们就设 $dp_{i,j}$ 为在 $i$ 的子树中，$b_i=j$ 时的最小值。

这玩意儿很像没有上司的舞会啊，那么就有转移方程 $dp_{i,j}=\sum_{k\in son_i}\min_{l\le n\land l\neq j} dp_{k,l}$。

然后我们发现这样是 $O(nV^2)$ 的，其中 $V=30$，过不了。

然后我们发现在后面那一大坨 $\min_{l\le n\land l\neq j} dp_{k,l}$ 可以在算完一个 $dp_k$ 后预处理出来，那么这样就变成 $O(nV)$ 的了，可以过。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=3e5+5;
int T,n,a[N],dp[N][35],sum[N][35];
vector<int> e[N];

void dfs(int x,int fa){
	for(int i:e[x]){
		if(i==fa) continue;
		dfs(i,x);
	}
	for(int k=1;k<=30;k++){
		dp[x][k]=a[x]*k;
		for(int i:e[x]){
			if(i==fa) continue;
			dp[x][k]+=sum[i][k];
		}
	}
	int mn=1e18;
	for(int k=1;k<=30;k++){
		sum[x][k]=min(sum[x][k],mn);
		mn=min(mn,dp[x][k]);
	}
	mn=1e18;
	for(int k=30;k>=1;k--){
		sum[x][k]=min(sum[x][k],mn);
		mn=min(mn,dp[x][k]);
	}
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) e[i].clear();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=30;j++){
				sum[i][j]=1e18;
			}
		}
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dfs(1,0);
		int mn=1e18;
		for(int i=1;i<=30;i++) mn=min(mn,dp[1][i]);
		cout<<mn<<endl;
	}
	return 0;
}
```

好吧来补个证明：

我们注意到每次攻击完后树上活着的怪肯定会减半。

那么我们就发现 $b_i$ 是 $\log n$ 量级的，那么这样做的真实复杂度为 $O(n\log n)$ 的。

---

## 作者：鲤鱼江 (赞：0)

[link](https://www.luogu.com.cn/problem/CF1988D)

~~我 dfs 去哪儿了？？~~

![](https://cdn.luogu.com.cn/upload/image_hosting/246tqz24.png)

在最后会留一份数据生成器，供推了假结论的同学对拍。

感性理解一下一个赛时结论 ~~（其实是因为没有严格的证明）~~：那就是如果按最优方案删，树很快就会被删空，比如链只需要常数次删除。

有了这个结论，根本不用管节点的具体度数，可以选择直接暴力 DP，但我赛时选择了直接贪心，喜提 3k+ 的 rank。

具体来说，就是设 $dp_{i,j}$ 表示如果节点 $i$ 在第 $j$ 轮被删掉，其子树贡献的伤害最小是多少，因为我们不关心一个节点什么时候被删掉，而关心其造成的伤害，这个可以贡献提前计算。

设最大轮数为 $k$，则时间复杂度为 $O(k^2n)$ 实测 $k$ 选 $40$ 时稳过，其他不知道。

~~20也能过，我 naive 了~~。

其实看到这里就可以发现轮数大概是 $O(\log n)$ 级别的了，我们考虑使用理想构造法证明一下：

我们考虑最劣的情况，我们只考虑最后删的节点，对于这一个节点，它每一轮只删掉一个儿子，并且它的所有子孙都满足这个性质（条件很苛刻，因为很难卡满）。

于是我们将使用的轮数限定为可以递归的问题，设 $t_i$ 为 要卡成 $i$ 轮删光，至少多少个节点，有 $t_i=(\sum\limits_{j=1}^{i-1}t_j)+1$，分析一下发现是 $2$ 的次方级别。

[参考代码](https://codeforces.com/contest/1988/submission/270877145)

数据生成器：~~（这么短，至于吗）~~

```cpp
#include<bits/stdc++.h>

using namespace std;

const int n=5;
mt19937 rnd((unsigned)time(NULL));
inline int random(const int l,const int r){return rnd()%(r-l+1)+l;}

int main(){
	cout<<"1\n"<<n<<"\n";
	for(int i=1;i<=n;++i) cout<<random(1,10)<<' ';cout<<endl;
	for(int i=2;i<=n;++i) cout<<i<<' '<<random(1,i-1)<<endl;
	return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

他妈的我怎么这么唐。

需要观察性质，这个所谓的删除最多进行 $\log n$ 步。这是因为一轮删除后一个点被保留当且仅当跟他相连的点有一个被选。即每次删除会让极大联通块大小减半。

然后就唐完了。我赛时以为策略是删除 $\log n$ 次最大权独立集，然后这个是假的，然后就唐完了。

不妨设 $f_{x,i}$ 为 $x$ 子树内，$x$ 第 $i$ 次被 删除的最小代价。一个儿子的 $f_{v,j}$ 能向 $f_{x.i}$ 转移当且仅当 $i\ne j$。然后就做完了。

朴素实现 $O(n\log^2n)$。

```cpp
#include<iostream>
#include<vector>
#define pb push_back
const int N = 3e5 + 10;
std::vector<int> g[N];
int t, n; long long f[N][21], a[N];
void dfs(int x, int fa){
    for(int i = 1; i <= 20; i++) f[x][i] = 1ll * a[x] * i;
    for(auto v:g[x]) if(v != fa){
        dfs(v, x); for(int j = 1; j <= 20; j++){
            long long mx = 9e18;
            for(int k = 1; k <= 20; k++)
                if(j != k) mx = std::min(mx, f[v][k]);
            f[x][j] += mx;
        }
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0),std::cout.tie(0);
    std::cin >> t; while(t--){
        std::cin >> n; long long rs = 9e18;
        for(int i = 1; i <= n; i++) std::cin >> a[i], g[i].clear();
        for(int i = 1, x, y; i < n; i++)
            std::cin >> x >> y, g[x].pb(y), g[y].pb(x);
        dfs(1, 0); long long mx = 9e18;
        for(int i = 1; i <= 20; i++)
        	mx = std::min(mx, f[1][i]);
        std::cout << mx << '\n';
    }
}
```

---

## 作者：Light_snow (赞：0)

本文同步自 [24暑期赛训合集](https://www.cnblogs.com/dixiao/p/18279702)

又是一场想完没写完的做法。

场上一直写的是线性做法，我说怎么大家过的都这么快。

首先题意要求每次删除若干不连通点，最后求每个回合中的点权和。

考虑我们在第 $i$ 回合删除了点 $x$，他对最后答案的贡献为 $i \times a_x$ 。

那么我们将题目转化为我们需要为每个点赋上一个权 $b_i$，要求相邻点的赋权不相同,最小化 $\sum b_i \times a_i$。

我们容易写出 $f_{i,j}$ 表示 $i$ 点赋权 $j$，子树内 $\sum b_x \times a_x$ 的最小和。

容易写出转移式即 $f_{i,j} = \sum_{v \in son_i} \min_{k \neq j} f_{v,k} + j \times a_i$。

我们知道 $b_i \leq n$ ，但是 $n$ 只是我们随手估的一个不太好的上界，在官方题解中给出了一个更好的上界 $b_i \leq \log n$，于是可以在 $O(n\log^2 n)$ 或者 $O(n\log n)$ 中解决这个问题。

但是我们有完全不需要基于上界的做法。

我们思考 $\min_{k\neq j} f_{v,k}$ 这个函数，实际上的值是一个分类函数。

我们设 $s$，$f_{v,s} = \min f_{v,k}$。

同时设 $s'$,$f_{v,s'} = \min_{k \neq s}f_{v,s'}$。

即 $v$ 的最小值和次小值点。

当 $j$ 为 $s$ 时，其值为 $f_{v,s'}$ 。

当 $j$ 不为 $s$ 时，其值为 $f_{v,s}$。

于是我们发现实际上 $\sum_{v \in son_i} \min_{k \neq j} f_{v,k}$ 只有至多 $|son_i| + 1$ 种取值，即我们取任一子树的最小值对应的点，和不取任何一个所对应的值，这里我们称儿子的最小值的点的集合为 $S$ 。

那么我们发现我们实际上并不需要维护所有点，我们只需要维护一个点的最小值和次小值位置即可。

那么我们接着来考虑后面这个 $j \times a_i$ 函数，其为一个递增函数。我们考虑我们取任一子树的最小值对应的点，$j$ 是固定无法修改的。但是对 $j \not \in S$ ，我们只需要取 $\text{mex}(S)$ 和 $\text{mex}(S + \text{mex}(S))$ 。

在 $|son_i| + 2$ 种答案中就能取到最小值和次小值。

这里我们采取了直接暴力一点的做法我直接取了 $S,S + 1,S + 2$ 三种情况，在 $3|son_i|$ 种情况取最小值和次小值，容易证明 $\text{mex}(S) + \text{mex}(S + \text{mex}(S)) \in \{S + 1\} \cup \{S + 2\}$ 。

同时我在代码里使用 $\text{map}$，可以使用 数组 或 $\text{Hash}$ 表等其他线性映射结构来替代掉这个 $\text{log}$ 。

```c++
//樱花落尽阶前月，象床愁倚薰笼
#include<bits/stdc++.h>
#define ll long long 
#define N 5000005

int T;

ll a[N];

using std::vector;

vector<int>G[N];

int n;

struct P{int ind;ll val;}minn[N],minm[N];

bool operator < (P A,P B){return A.val < B.val;}
bool operator <= (P A,P B){return A.val <= B.val;}

using std::map;

map<int,ll>dval;
vector<int>check;

inline void dfs(int u,int fa){
	if(G[u].size() == 0 || (G[u].size() == 1 && G[u][0] == fa)){minn[u].ind = 1;minn[u].val = a[u];minm[u].ind = 2;minm[u].val = 2 * a[u];return ;}
	for(auto v : G[u]){			
		if(v == fa)continue;
		dfs(v,u);
	}
	dval.clear();check.clear();
	ll allval = 0;
	check.push_back(0);	
	for(auto v : G[u]){
		if(v == fa)continue;
		check.push_back(minn[v].ind);
		allval += minn[v].val;
		dval[minn[v].ind] += minm[v].val - minn[v].val;
	}
	P nowminn,nowminm;
	nowminn.ind = nowminm.ind = 0;
	nowminn.val = nowminm.val = 4e18;
	for(int i = 1;i < check.size();++i){
		ll x = check[i];
		P now;now.ind = x;now.val = allval + x * a[u];
		if(dval.find(x) != dval.end()){now.val += dval[x];}
		if(now.ind != nowminn.ind && now <= nowminn){nowminm = nowminn;nowminn = now;}
		else if(now.ind != nowminn.ind && now < nowminm){nowminm = now;}					
	}
	for(int i = 0;i < check.size();++i){
		ll x = check[i] + 1;
		P now;now.ind = x;now.val = allval + x * a[u];
		if(dval.find(x) != dval.end()){now.val += dval[x];}
		if(now.ind != nowminn.ind && now <= nowminn ){nowminm = nowminn;nowminn = now;}
		else if(now.ind != nowminn.ind && now < nowminm){nowminm = now;}				
	}	
	for(int i = 0;i < check.size();++i){
		ll x = check[i] + 2;
		P now;now.ind = x;now.val = allval + x * a[u];
		if(dval.find(x) != dval.end()){now.val += dval[x];}
		if(now.ind != nowminn.ind && now <= nowminn ){nowminm = nowminn;nowminn = now;}
		else if(now.ind != nowminn.ind && now < nowminm){nowminm = now;}				
	}		
	minn[u] = nowminn,minm[u] = nowminm;
}


signed main(){
	scanf("%d",&T);
	while(T -- ){
		scanf("%d",&n);
		for(int i = 1;i <= n;++i)scanf("%lld",&a[i]);
		for(int i = 1;i <= n;++i)G[i].clear();
		for(int i = 1;i < n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			G[x].push_back(y);
			G[y].push_back(x);
		}
		dfs(1,0);
		std::cout<<minn[1].val<<"\n";
	}
}
```

---

