# 「MCOI-08」Photoelectric Effect

## 题目描述

有一棵 $n$（$1\le n\le 10^5$）个点的树以及 $k$（$2\le k\le 5$）个颜色，根节点为 $1$。同时，给定一个颜色合并函数 $a\otimes b$，满足当 $1\le a,b\le k$，有 $1\le a\otimes b\le k$。

请问有多少个方案对所有点染色，使得当点对 $u,v$ 之间没有祖先关系，有：

 - $u$ 和 $v$ 最近公共祖先的颜色为点 $u$ 的颜色和点 $v$ 的颜色之并。

答案对 $10^9+7$ 取模。


## 说明/提示

#### 样例 1 解释

树的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/twht22a6.png)

设 $w_i$ 为第 $i$ 个点的点权，则有如下 $4$ 种分配方式：

- $w_i=\{1,1,1,1,1\}$；
- $w_i=\{2,2,2,1,1\}$；
- $w_i=\{2,1,1,2,2\}$；
- $w_i=\{1,2,2,2,2\}$。

#### 数据规模与约定

**本题采用捆绑测试。**

对于 $100\%$ 的数据，$1\le n,\sum n\le10^5$，$2\le k\le 5$，$1\le f_i<i$。

对于 $100\%$ 的数据，$1\le t\le 1000$。

 - Subtask 1（5 pts）：$n\le5$；
 - Subtask 2（11 pts）：树上任何节点孩子个数至多为 $2$；
 - Subtask 3（23 pts）：树上任何节点孩子个数至多为 $3$；
 - Subtask 4（13 pts）：$k=2$；
 - Subtask 5（17 pts）：$k\le3$； 
 - Subtask 6（31 pts）：无特殊限制。

## 样例 #1

### 输入

```
2
5 2
1 2
2 1
1 2 1 4
5 2
1 2
1 1
1 2 1 4```

### 输出

```
4
2```

# 题解

## 作者：Ryo_Yamada (赞：4)

高复杂度做法。

看到 $k=5$，可以思考一些复杂度带 $2^k$ 或 $k!$ 的做法。

我们发现从 $u$ 子树中选两个点 $x,y$ 使 $lca=u$，一定是 $x, \, y$ 属于 $u$ 两个不同的儿子的子树。于是如果我们知道了 $u$ 每个儿子的子树用了的颜色集合，就可以算出 $u$ 需要选的颜色（或无解）。

考虑先预处理出 $\text{trs}_{i,j}$ 表示：若对于一个节点 $u$ 的两个儿子 $x,\,y$，它们用了的颜色集合为 $i,\,j$，则 $u$ 需要用什么颜色（$-1$ 表示无解）。这个过程可以直接 $k^2 \times 2^{2k}$ 做。

接下来考虑如何进行树形dp。设 $dp_{u,i,j}$ 表示对于节点 $u$，当它用颜色 $i$ 且它的子树（不包括 $u$ 本身）所用颜色集合为 $j$ 时的方案数。

首先，对于每个叶子节点 $x$ 都有 $dp_{x,i,0}=1$。  
对于非叶子节点 $u$，枚举它的每个叶子节点 $v$。枚举 $u$ 当前用的颜色集合 $j$ 和 $v$ 的状态 $dp_{v,i',j'}$。若 $\text{trs}_{j,j'} \not= -1$，令 $js=j' | \, 2^{i'-1}$ 则可以转移到 $dp_{u,\text{trs}_{i, js}, i|js}$。最终时间复杂度 $O(nk \times 2^{2k})$，空间复杂度 $O(nk \times 2^k)$。能过也是奇迹（。

$\text{Code}$：

```cpp
def(N, int, 1e5 + 5)
def(p, int, 1e9 + 7)

int n, k, sta;
int to[6][6];
int trs[1 << 5][1 << 5];
vector<int> e[N];
int dp[N][6][1 << 5], f[N][6][1 << 5];

int get(int x, int y) {
	int res = 0;
	rep(i, 1, k) {
		if(!(x >> (i - 1) & 1)) continue;
		rep(j, 1, k) {
			if(!(y >> (j - 1) & 1)) continue;
			if(!res) res = to[i][j];
			else if(res != to[i][j]) res = -1;
		}
	}
	swap(x, y);
	rep(i, 1, k) {
		if(!(x >> (i - 1) & 1)) continue;
		rep(j, 1, k) {
			if(!(y >> (j - 1) & 1)) continue;
			if(!res) res = to[i][j];
			else if(res != to[i][j]) res = -1;
		}
	}
	return res;
}

void dfs(int u) {
	if(!e[u].size()) {
		rep(i, 1, k) dp[u][i][0] = 1;
		return ;
	}
	
	rep(l, 0, e[u].size() - 1) {
		int v = e[u][l];
		dfs(v);
		
		if(!l) {
			rep(nw, 1, k) rep(i, 0, sta) rep(j, 1, k) dp[u][nw][i | (1 << j - 1)] = (dp[u][nw][i | (1 << j - 1)] + dp[v][j][i]) % p;
			continue;
		}
		
		rep(i, 1, sta) rep(j, 1, k) f[u][j][i] = dp[u][j][i], dp[u][j][i] = 0;
		
		rep(i, 1, sta) {
			if(!dp[v][i]) continue;
			rep(j, 0, sta) {
				rep(nw, 1, k) {
					int js = (j | (1 << nw - 1));
					if(trs[i][js] == -1) continue;
					dp[u][trs[i][js]][i | js] = (dp[u][trs[i][js]][i | js] + 1ll * f[u][trs[i][js]][i] * dp[v][nw][j] % p) % p;
				}
			}
		}
	}
}

int main() {
	int t; cin >> t;
	W(t) {
		qread(n, k);
		sta = (1 << k) - 1;
		rep(i, 1, n) e[i].clear();
		rep(i, 1, k) rep(j, 1, k) qread(to[i][j]);
		rep(i, 2, n) {
			int f; qread(f);
			e[f].pb(i);
		}
		rep(i, 1, sta) rep(j, 1, sta) trs[i][j] = get(i, j);
		rep(i, 1, n) {
			memset(dp[i], 0, sizeof dp[i]);
			memset(f[i], 0, sizeof f[i]);
		}
		dfs(1);
		ll ans = 0;
		// rep(i, 1, n) rep(l, 1, n) rep(j, 0, sta) printf("dp[%d][%d][%d] : %lld\n", i, l, j, dp[i][l][j]);
		rep(l, 1, k) rep(i, 1, sta) ans = (ans + dp[1][l][i]) % p;
		cout << ans << '\n';
	}	
	return 0;
}
```


---

## 作者：Sakura_xyz (赞：4)

### 题意
有一棵 $n$ 个点的树以及 $k$ 个颜色，给定一个颜色合并函数（~~由于我不会打那个符号~~，不妨称其为 $F(i,j)$ ），求满足树上对于没有祖先关系的任意两点 $i$ 和 $j$ ， $i$ 和 $j$ 的最近公共祖先的颜色均是 $F(i,j)$ 的方案总数，对 $10^9+7$ 取模。

### 分析
考虑到看到数据范围有 $k\leq 5$ ，可以想到状压 dp 。

设 $dp_{u,i,S,x}$ 为在以 $u$ 为根的子树中，在 $u$ 的前 $i$ 棵子树中选择，其中不包括子树根节点 $u$ 时，选择的集合是 $S$ 时，$u$ 的颜色为 $x$ 时的方案数。

我们现在假设有两个集合 $A$ 和 $B$ ，其中 $\forall i \in A,\forall j \in B$ ，有 $F(i,j)=F(j,i)=x$ 成立，那么，当根节点 $u$ 的颜色为 $x$ 时，显然可以从 $A$ 与 $B$ 转移到 $A \cup B$ 。

为方便起见，我们考虑记 $sum_{u,S}$ 为在以 $u$ 为根的子树中，包括子树根节点 $u$ 时，选择的集合是 $S$ 时的方案数，显然，求出 dp 值后，总和能在可以接受的时间复杂度内求得。那么，我们首先枚举颜色 $x$ ，再枚举每棵子树 $v$ ，现在，对于两个集合 $A,B$ ，若两集合满足上述条件，则有以下转移：
$$dp_{u,i,A\cup B,x}=dp_{u,i,A\cup B,x}+dp_{u,i,A,x} \times sum_{v,B}$$

然后考虑到每个节点的 dp 状态的总和预处理，显然，对于有 $i$ 棵子树的节点 $u$ 的颜色为 $x$ ，且其子树的颜色集合为 $S$ 时，对 $sum_{u,S \cup \{x\}}$ 做出了贡献，记录即可。 

另外，我们可以暴力预处理出每两个集合是否在根节点为 $x$ 的情况下满足条件。枚举两个集合中的所有元素再判断即可。

易知，时间复杂度 $O(T\times (n \times 4^k \times k+4^k \times k^3))$ ，由于数据范围是 $n$ 的总和，在可接受的范围内。

### 优化

很显然的是，虽然看起来很极限，但是这种状态转移的时间复杂度是可以接受的，但是空间会炸，那么我们可以想到一种优化方式。首先，关于转移和求解答案时， dp 的状态并不会时刻用到，只关心的是总和的统计，因此，显然我们可以把颜色的一维直接压掉，另外，所有的子树的状态都是从上一棵子树中转移而来的，因此可以滚动数组优化，空间就不会炸了。

### AC 代码
说句题外话，月赛上这题调了 $2$ 个小时，心态调炸了，可能会有点乱。~~还是赛后继续调出来无数个锅才切的。~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 100005

using namespace std;

const int mod=1e9+7;

int n,k,fa[MAXN],cnt=0,F[6][6],dp[MAXN][2][32],sum[MAXN][32],head[MAXN];

bool pd[32][32][6];

struct e{
	int to,nxt;
}edge[MAXN];

void Add_Edge(int x,int y){
	edge[++cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
}

void Init(){
	scanf("%d%d",&n,&k); cnt=0;
	for(int i=1;i<=n;i++) head[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<k);j++){
			sum[i][j]=dp[i][0][j]=dp[i][1][j]=0;
		}
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			scanf("%d",&F[i][j]);
		}
	}
	for(int i=0;i<(1<<k);i++){
		for(int j=0;j<(1<<k);j++){
			for(int l=1;l<=k;l++){
				pd[i][j][l]=false;
			}
		}
	}
	for(int i=2;i<=n;i++) scanf("%d",fa+i),Add_Edge(fa[i],i);
}

int T;

void dfs(int x){
	for(int i=head[x];i;i=edge[i].nxt) dfs(edge[i].to);
	//cerr << x << " : DP TEST\n";
	if(!head[x]){
		for(int i=1;i<=k;i++) sum[x][1<<(i-1)]=1;
		goto TEST;
	}
	for(int x_col=1;x_col<=k;x_col++){
		int now=0;
		for(int i=0;i<(1<<k);i++) dp[x][0][i]=sum[edge[head[x]].to][i];
		//cerr << "The color of root is : " << x_col << endl;
		for(int i=edge[head[x]].nxt;i;i=edge[i].nxt){
			now^=1;
			for(int j=1;j<(1<<k);j++) dp[x][now][j]=0;
			for(int j=1;j<(1<<k);j++){
				for(int l=1;l<(1<<k);l++){
					if(pd[j][l][x_col]){
						dp[x][now][j|l]=(dp[x][now][j|l]+1ll*sum[edge[i].to][j]*dp[x][now^1][l]%mod)%mod;
					}
				}
			}
		}
		//for(int i=1;i<(1<<k);i++) cerr << dp[x][now][i] << endl;
		for(int i=1;i<(1<<k);i++) sum[x][i|(1<<x_col-1)]=(sum[x][i|(1<<x_col-1)]+dp[x][now][i])%mod;
	}
	TEST: ;
		//for(int i=1;i<(1<<k);i++) cerr << sum[x][i] << ' ';
		//cerr << endl << x << " : DP TEST END\n";
}

void Solve(){
	for(int i=1,j,col,l,m;i<(1<<k);i++){
		for(j=1;j<(1<<k);j++){
			for(col=1;col<=k;col++){
				for(l=1;l<=k;l++){
					if(i&(1<<(l-1))){
						for(m=1;m<=k;m++){
							if(j&(1<<m-1)){
								if(F[l][m]!=col||F[m][l]!=col){
									goto ENDTAG;
								}
							}
						}
					}
				}
				pd[i][j][col]=true;
				// cerr << i << ' ' << j << ' ' << col << ' ' << "TEST\n";
				ENDTAG:;
			}
		}
	}
	// if(pd[1][2][1]) cerr << "CHECK ARRAY!" << endl;
	dfs(1);
}

void Output(){
	int ans=0;
	for(int i=0;i<(1<<k);i++) ans=(ans+sum[1][i])%mod;
	printf("%d\n",ans);
}

int main(){
	scanf("%d",&T);
	while(T--) Init(),Solve(),Output();
	return 0;
}
```


---

## 作者：Eibon (赞：1)

时隔几个月，终于过了，致敬数组开反人。

---

考虑 $k\le5$，所以可以随便做（$2^{k}$ 或者 $k!$ 时间复杂度）。

设 $col_{i,j,k}$ 表示子节点颜色集合分别为 $i$ 和 $j$，父亲节点的颜色为 $k$ 是否合法。

因为要求方案数，所以自然想到 dp。

设 $dp_{i,0/1,s}$ 表示以 $i$ 为根的子树，当前遍历到第几个儿子节点（滚动数组），当前遍历儿子子树颜色集合。

设 $sum_{i,s}$ 表示以 $i$ 为根的子树，颜色集合为 $s$。

然后在遍历的过程中判断能否将某种颜色集合的儿子加入方案中，用 $col$ 判断就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int mod=1e9+7;
int T=1,n,m,cnt,tot,ans;
int head[maxn],a[10][10],col[45][45][10],dp[maxn][2][45],sum[maxn][45];
struct edge
{
	int to,nxt;
};
edge e[maxn<<1];
void add(int u,int v)
{
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,int pa)
{
	int flag=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==pa){
			continue;
		}
		flag=0;
		dfs(v,u);
	}
	if(flag){//没儿子
		for(int i=1;i<=m;i++){
			sum[u][(1<<(i-1))]=1;
		}
		return;
	}
	for(int k=1;k<=m;k++){
		int now=0;
		for(int i=0;i<(1<<m);i++){
			dp[u][0][i]=sum[e[head[u]].to][i];
		}
		for(int i=e[head[u]].nxt;i;i=e[i].nxt){
			now^=1;
			for(int j=1;j<(1<<m);j++){
				dp[u][now][j]=0;
			}
			for(int j=1;j<(1<<m);j++){
				for(int l=1;l<(1<<m);l++){
					if(col[j][l][k]){
						dp[u][now][j|l]=(dp[u][now][j|l]+1ll*sum[e[i].to][j]*dp[u][now^1][l]%mod)%mod;
					}
				}
			}
		}
		for(int i=0;i<(1<<m);i++){
			sum[u][i|(1<<(k-1))]=(sum[u][i|(1<<(k-1))]+dp[u][now][i])%mod;
		}
	}
}
void solve()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=1;i<(1<<m);i++){
		for(int j=1;j<(1<<m);j++){
			for(int k=1;k<=m;k++){
				bool flag=1;
				for(int x=1;x<=m;x++){
					if(i&(1<<(x-1))){
						for(int y=1;y<=m;y++){
							if(j&(1<<(y-1))){
								if(a[x][y]!=k||a[y][x]!=k){
									flag=0;
									break;
								}
							}
						}
					}
					if(!flag){
						break;
					}
				}
				if(flag){
					col[i][j][k]=1;
				}
			}
		}
	}
	for(int v=2;v<=n;v++){
		int u;
		scanf("%lld",&u);
		add(u,v);
	}
	dfs(1,0);
	ans=0;
	for(int i=0;i<(1<<m);i++){
		ans=(ans+sum[1][i])%mod;
	}
	printf("%lld\n",ans);
	tot=0;
	for(int i=1;i<(1<<m);i++){
		for(int j=1;j<(1<<m);j++){
			for(int k=1;k<=m;k++){
				col[i][j][k]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<m);j++){
			sum[i][j]=dp[i][0][j]=dp[i][1][j]=0;
		}
	}
	for(int i=1;i<=n;i++){
		head[i]=0;
	}
}
signed main()
{
//	cout<<((double)(sizeof(dp)+sizeof(col)+sizeof(sum))/1024/1024);
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：zesqwq (赞：1)

# P8280 「MCOI-08」Photoelectric Effect 题解

[题目传送门](https://www.luogu.com.cn/problem/P8280)

看到这种树上的计数类问题，而且条件那么多，可以想到使用 $\text{dp}$。

我们发现颜色的数量很小，所以可以将颜色状态压缩。

我们用 $f_{i,j,k,l}$ 表示第 $i$ 个节点，考虑到第 $j$ 个孩子，第 $i$ 个节点的颜色是 $k$，除了第 $i$ 个节点外其子树的颜色状压后是 $l$ 的情况总数。使用 $g_{i,j}$ 表示第 $i$ 个节点包括 $i$ 本身在内的颜色状压。即 $g$ 是 $f$ 的一个统计，然后与处理好 $\operatorname{merge}(i,j)$ 表示状态压缩颜色 $i$ 和 $j$ 的所有子颜色的合并，若合并出了多个颜色，值为 $-1$。

考虑转移，我们用 $ch_{i,j}$ 表示 $i$ 节点的第 $j$ 个孩子（其中 $\operatorname{or}$ 表示按位或，$j$ 从 $0$ 开始编号）：

$$
f_{i,j,k,l} = \begin{cases}
	[l = 0] & \text{i没有孩子} \\
    g_{ch_{i,j},l} & \text{j = 0} \\
    \sum_{x=1}^l \sum_{y=1}^l f_{i,j-1,k,x} \times g_{ch_{i,j},y} \times [(x \operatorname{or} y) =l][merge(x,y)=k] & \text{otherwise}
\end{cases}
$$
时间复杂度 $O(Tnk2^{3k})$，空间复杂度 $O(n^2k2^k)$。无法通过。


然后可以优化，$k,l$ 这两个维度在转移的时候就可以不用枚举，可以直接枚举从哪两种颜色状态（即上文的 $x, y$）合并而来。$j$ 维度可以滚动，然后这样就可以 $\text{AC}$ 了，时间复杂度 $O(Tn2^{2k})$,空间复杂度 $O(nk2^k)$。

$\text{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
const int K = 5, N = 1e5 + 10, S = 32, P = 1e9 + 7;
int table[K][K], fa[N], s;
int f[N][2][K][S], g[N][S];
int fmerge[S][S];
inline int merge(int a, int b) {
    int ans = 9;
    for (int i = 0; i < k; i++) {
        if (a & (1 << i))
            for (int j = 0; j < k; j++) {
                if (ans == -1) break;
                if (b & (1 << j)) {
                    if (ans == 9)
                        ans = table[i][j];
                    else if (ans != table[i][j])
                        ans = -1;
                }
            }
    }
    if (ans == -1) return ans;
    return ans;
}
vector<int> vec[N];
void dp(int u) {
    int v, tmp;
    if (!vec[u].size()) {
        for (int i = 0; (1 << i) < s; i++) g[u][1 << i] = 1;
        return;
    }
    dp(v = vec[u][0]);
    for (int i = 0; i < k; i++) memcpy(f[u][0][i], g[v], sizeof(f[u][0][i]));
    for (int i = 1; i < vec[u].size(); i++) {
        dp(v = vec[u][i]), memset(f[u][i & 1], 0, sizeof(f[u][i & 1]));
        for (int j = 1; j < s; j++)
            for (int l = 1; l < s; l++) {
                tmp = fmerge[j][l];
                if (tmp == -1) continue;
                f[u][i & 1][tmp][j | l] = (f[u][i & 1][tmp][j | l] + 1ll * f[u][i & 1 ^ 1][tmp][j] * g[v][l]) % P;
            }
    }
    for (int i = 0; i < k; i++)
        for (int j = 1; j < s; j++) g[u][j | (1 << i)] = (g[u][j | (1 << i)] + f[u][vec[u].size() & 1 ^ 1][i][j]) % P;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d %d", &n, &k), s = (1 << k);
        for (int i = 1; i <= n; i++) memset(g[i], 0, sizeof(g[i])), memset(f[i], 0, sizeof(f[i])), vec[i].clear();
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++) scanf("%d", &table[i][j]), --table[i][j];
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                fmerge[i][j] = merge(i, j);
                int g = merge(j, i);
                if (g != fmerge[i][j]) fmerge[i][j] = -1;
            }
        }
        for (int i = 2; i <= n; i++) scanf("%d", &fa[i]), vec[fa[i]].push_back(i);
        dp(1);
        long long ans = 0;
        for (int i = 1; i < s; i++) ans = (ans + g[1][i]) % P;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

