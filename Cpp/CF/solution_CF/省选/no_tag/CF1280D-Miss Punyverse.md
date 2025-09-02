# Miss Punyverse

## 题目描述

The Oak has $ n $ nesting places, numbered with integers from $ 1 $ to $ n $ . Nesting place $ i $ is home to $ b_i $ bees and $ w_i $ wasps.

Some nesting places are connected by branches. We call two nesting places adjacent if there exists a branch between them. A simple path from nesting place $ x $ to $ y $ is given by a sequence $ s_0, \ldots, s_p $ of distinct nesting places, where $ p $ is a non-negative integer, $ s_0 = x $ , $ s_p = y $ , and $ s_{i-1} $ and $ s_{i} $ are adjacent for each $ i = 1, \ldots, p $ . The branches of The Oak are set up in such a way that for any two pairs of nesting places $ x $ and $ y $ , there exists a unique simple path from $ x $ to $ y $ . Because of this, biologists and computer scientists agree that The Oak is in fact, a tree.

A village is a nonempty set $ V $ of nesting places such that for any two $ x $ and $ y $ in $ V $ , there exists a simple path from $ x $ to $ y $ whose intermediate nesting places all lie in $ V $ .

A set of villages $ \cal P $ is called a partition if each of the $ n $ nesting places is contained in exactly one of the villages in $ \cal P $ . In other words, no two villages in $ \cal P $ share any common nesting place, and altogether, they contain all $ n $ nesting places.

The Oak holds its annual Miss Punyverse beauty pageant. The two contestants this year are Ugly Wasp and Pretty Bee. The winner of the beauty pageant is determined by voting, which we will now explain. Suppose $ \mathcal{P} $ is a partition of the nesting places into $ m $ villages $ V_1, \ldots, V_m $ . There is a local election in each village. Each of the insects in this village vote for their favorite contestant. If there are strictly more votes for Ugly Wasp than Pretty Bee, then Ugly Wasp is said to win in that village. Otherwise, Pretty Bee wins. Whoever wins in the most number of villages wins.

As it always goes with these pageants, bees always vote for the bee (which is Pretty Bee this year) and wasps always vote for the wasp (which is Ugly Wasp this year). Unlike their general elections, no one abstains from voting for Miss Punyverse as everyone takes it very seriously.

Mayor Waspacito, and his assistant Alexwasp, wants Ugly Wasp to win. He has the power to choose how to partition The Oak into exactly $ m $ villages. If he chooses the partition optimally, determine the maximum number of villages in which Ugly Wasp wins.

## 说明/提示

In the first test case, we need to partition the $ n = 4 $ nesting places into $ m = 3 $ villages. We can make Ugly Wasp win in $ 2 $ villages via the following partition: $ \{\{1, 2\}, \{3\}, \{4\}\} $ . In this partition,

- Ugly Wasp wins in village $ \{1, 2\} $ , garnering $ 181 $ votes as opposed to Pretty Bee's $ 170 $ ;
- Ugly Wasp also wins in village $ \{3\} $ , garnering $ 111 $ votes as opposed to Pretty Bee's $ 70 $ ;
- Ugly Wasp loses in the village $ \{4\} $ , garnering $ 0 $ votes as opposed to Pretty Bee's $ 50 $ .

Thus, Ugly Wasp wins in $ 2 $ villages, and it can be shown that this is the maximum possible number.

In the second test case, we need to partition the $ n = 2 $ nesting places into $ m = 1 $ village. There is only one way to do this: $ \{\{1, 2\}\} $ . In this partition's sole village, Ugly Wasp gets $ 563 $ votes, and Pretty Bee also gets $ 563 $ votes. Ugly Wasp needs strictly more votes in order to win. Therefore, Ugly Wasp doesn't win in any village.

## 样例 #1

### 输入

```
2
4 3
10 160 70 50
70 111 111 0
1 2
2 3
3 4
2 1
143 420
214 349
2 1
```

### 输出

```
2
0
```

# 题解

## 作者：zac2010 (赞：14)

  这道题是个简单题，但是我太菜了。

  根据数据范围，发现是个 $O(n^2)$ 的题。再一看，直接贪心似乎不行，因为你考虑假设现在断开了一个联通块，并且它是好的，但是假设把这个联通快再多加入一些节点，它还是好的，那么它可能让答案更优，因为当前已经选的联通快变少了，那么剩下可以分的联通块数也变多了，所以其它节点可能能创造更多好的联通快。那么不是贪心，也找不到什么特别好的性质，并且是一类最优解问题，不难想到动规。

  我们再一思考，这道题是在树上，树上 $n^2$ 的动规有哪几种可能？
  1. 其一，最简单的，一维状态，由子节点或者父节点转移过去。但是显然你想不太到这么简单的方案；
  2. 二维的状态，那第二维该弄个什么好呢？发现好像只能是块的个数。但是发现这样就变成树上背包了，也就是下面那种。
  3. 那就是树上背包。

  我们来具体讲一下怎么树上背包。首先状态不说，肯定是 $f[u][i]$ 表示以 $u$ 这个节点为根的子树分成 $i$ 块，不算 $u$ 所处的那一块的最大值，然后我们称一个点的权值为 $a_i$ ，其等于 $w_i - b_i$ 。然后我们经思考后，发现好像不能直接去树上背包，原因是你还是不知道当前根节点 $u$ 这一块的权值是多少。

  当时我就愣住了，之后便认为这道题恐怖如斯，不是我能做出来的题。但这时候就应该去找一些性质或者贪心策略以使这个问题可以迎刃而解。所以我们找到了一个非常漂亮的性质（贪心策略）：我们思考两种方案，第一种的块数比第二种多，但是第二种 $u$ 那个联通块的权值和大于第一种。

为了防止搞混两种，再清晰地理一下：
  1. 块数多
  2. $u$ 那个联通块的权值大

第一种一定 **不劣于** 第二种！

  我们采取反证法，思考假设第二种比第一种优会优再什么情况下：可能存在第二种他的权值很大，然后把上边权值是非正数的一块变成正数了，然后会使答案加 $1$ ，那么我们思考第一种，他可以把权值是非正数的那块不去管他，那么他在最差情况下也就是第二种在最好情况下会和第二种一样。那么什么情况下第一种会比第二种优呢？就比如说 $u$ 上面的所有节点权值都是正数，那么第二种就会比第一种要差。

  那么假设有两种方案块数相等，不难想到u那块必定是权值越大越好，因为可能越大。那么我们再用一个 $g[u][i]$ 表示在块数为 $f[u][i]$ 时 $u$ 那个联通块的最大权值。

  最后给转移方程（这里用的是刷表法）：
1. $v$ 所处的联通块不和 $u$ 合并，即单独划分

	用 $f_{u,i}+f_{v,j}+(g_{v,j}>0),g_{u,i}$ 去更新 $f_{u,i+j},g_{u,i+j}$ 的最优值。
2. $v$ 的那个联通块与 $u$ 合并

	用 $f_{u,i}+f_{v,j},g_{u,i}+g_{v,j}$ 去更新 $f_{u,i+j-1},g_{u,i+j-1}$ 的最优值。
    
边界是 $f[u][1]=0,g[u][1]=a_u$ 。

树上背包的时间复杂度 $O(n^2)$ 的证明见我的[这篇博客](https://www.luogu.com.cn/blog/zaczac/solution-cf1499f)。

其实这跑得过去是必然的，因为我们考虑最坏情况， $m$ 全是 $3000$ ，由于一句很重要的话： $n$ 之和不超过 $10^5$ ，所以我们发现，利用乘法分配律，最大可能是 $3*10^8$ 。而时限不紧，有整整 $4$ 秒，且动态规划常数算很小所以就这么跑过去了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 3010;
int T, n, m, a[N], b[N], w[N], sz[N];
int f[N][N], r[N];
ll g[N][N], c[N];
vector<int>e[N];
void Init(){
	memset(f, 0, sizeof(f));
	memset(g, 0xf3, sizeof(g));
	L(i, 1, n) e[i].clear();
}
void Dfs(int u, int pa){
	f[u][1] = 0, g[u][1] = a[u];
	sz[u] = 1;
	for(int v: e[u]){
		if(v == pa) continue;
		Dfs(v, u);
		L(i, 1, min(m, sz[u] + sz[v]))
			r[i] = 0, c[i] = -3e12;
		L(i, 1, min(m, sz[u])){
			L(j, 1, min(m, sz[v])){
				ll ff = f[u][i] + f[v][j] + (g[v][j] > 0), gg = g[u][i];
				if(i + j <= m && ff > r[i + j] || ff == r[i + j] && gg > c[i + j])
					r[i + j] = ff, c[i + j] = gg;
				ff = f[u][i] + f[v][j], gg = g[u][i] + g[v][j];
				if(i + j - 1 <= m && ff > r[i + j - 1] || ff == r[i + j - 1] && gg > c[i + j - 1])
					r[i + j - 1] = ff, c[i + j - 1] = gg;
			}
		}
		L(i, 1, min(m, sz[u] + sz[v]))
			f[u][i] = r[i], g[u][i] = c[i];
		sz[u] += sz[v];
	}
}
void Solve(){
	scanf("%d%d", &n, &m); Init();
	L(i, 1, n) scanf("%d", &b[i]);
	L(i, 1, n) scanf("%d", &w[i]);
	L(i, 1, n) a[i] = w[i] - b[i];
	int u, v;
	L(i, 1, n - 1){
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	Dfs(1, 0);
	printf("%d\n", f[1][m] + (g[1][m] > 0));
} 
int main(){
	scanf("%d", &T);
	while(T--) Solve();
	return 0;
}
```

---

## 作者：万弘 (赞：9)

[本场比赛完整题解](https://www.luogu.com.cn/blog/c2522943959/cf1281round-607-div-2-ti-xie)

### F - Miss Punyverse
题意:给一棵$n$个点的树,每个点上有$a_i$个人支持$A$,$b_i$个人支持$B$.  
你要把它划分成$m$块.一个块支持$B$,当且仅当这个块内支持$A$的人**严格少于**支持$B$的人.求支持$B$的块至多有多少.  
$1\le m\le n\le 3000$

考虑树形dp.  
`f[u][i]表示把以u为根的子树划分成i块,支持B的至多有几块?`但是这样子信息不足,因为当块内支持$A$的人少于支持$B$的人时会有1的贡献,而这样无法处理.

再加一维?空间时间双起飞.  
考虑到两种划分方案$k1,k2$(都是在以$u$为根的子树中划分$i$块)

如果$k1$内支持$B$的块数多于$k2$,那么$k2$最后剩下的这一块支持$B$的人再多,也至多产生1的贡献,不会比$k1$更优.  
也就是说,这里可以贪心,我们**只需要保存支持的块最多,同时剩下的支持的人最多**.不妨用`pair`存储

`f[u][i].first表示把以u为根的子树划分成i块,最多有多少块支持B`  
`f[u][i].second表示这种最优情况下,最后剩下的支持的人最多有多少`

那么如何转移呢?设当前考虑的点是$u$(这里的$a_u$表示题目中的$b_u-a_u$,也就是$u$的点权)  
边界显然是$f[u][1]=(0,w_u)$  
假设正在处理孩子$v$,且$v$的信息已经递归处理完

$v$剩下的那一块单独划分,$f[u][j+k]\leftarrow^{max} f[u][j].first+f[v][k].first+(f[v][k].second>0),f[u][j].second$(因为如果$f[v][k].second>0$那么会有1的贡献)

$v$剩下的那一块和$u$拼到一起,$f[u][j+k-1]\leftarrow^{max} f[u][j].first+f[v][k].first,f[u][j].second+f[v][k].second$

为了避免这次用的$f[u][j]$已经被更新,可以用一个辅助数组暂存一下,然后复制回去.  
每个点都要决策$size[u]$次,总时间复杂度$\Theta(\sum_{u=1}^n size[u]^2)$

那这个会不会TLE呢?可以证明,这样是最坏$O(n^2)$的.
比如菊花图,链都是显然$O(n^2)$,然后满二叉树的时候是$n^2+2\times (n/2)^2+4\times (n/4)^2+..+1<2\times n^2=O(n^2)$
可以类似的画几个图算一下就好了.
```cpp
/**********/
typedef long long ll;
typedef std::pair<ll,ll> pll;
#define MAXN 3011
struct Edge
{
	ll v,nxt;
}e[MAXN<<1|1];
ll cnt=0,last[MAXN];
void adde(ll u,ll v)
{
	e[++cnt].v=v;
	e[cnt].nxt=last[u],last[u]=cnt;
}
 
ll a[MAXN],size[MAXN];
pll f[MAXN][MAXN],tmp[MAXN];
void upd(pll &a,pll t)//用上面的贪心策略更新方案,pair默认先比较第一关键字,再比较第二关键字
{
	if(t>a)a=t;
}
void dp(ll u,ll fa=0)
{
	size[u]=1;
	f[u][1]=pll(0,a[u]);//边界
	for(ll i=last[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)continue;
		dp(v,u);//递归处理
		for(ll j=1;j<=size[u]+size[v];++j)tmp[j]=pll(-1,0);//辅助数组初始化
		for(ll j=1;j<=size[u];++j)//树形dp的核心部分,就是那两个转移方程
			for(ll k=1;k<=size[v];++k)
			{
				upd(tmp[j+k],pll(f[u][j].first+f[v][k].first+(f[v][k].second>0),f[u][j].second));//v那一块独立划分
				upd(tmp[j+k-1],pll(f[u][j].first+f[v][k].first,f[u][j].second+f[v][k].second));//v那一块和u拼到一起
			}
		for(ll j=1;j<=size[u]+size[v];++j)f[u][j]=tmp[j];//复制回去
		size[u]+=size[v];
	}
}
int main()
{
	ll task=read();
	while(task--)
	{
		ll n=read(),m=read();
		for(ll i=1;i<=n;++i)a[i]=-read();
		for(ll i=1;i<=n;++i)a[i]+=read();
		for(ll i=1;i<n;++i)
		{
			ll u=read(),v=read();
			adde(u,v),adde(v,u);
		}
		dp(1);
		printf("%lld\n",f[1][m].first+(f[1][m].second>0));//最后可能还有一个贡献
		
		cnt=0;//清除数据
		for(ll i=1;i<=n;++i)
		{
			last[i]=0;
			for(ll j=1;j<=m;++j)f[i][j]=pll(0,0);
		}
		//clear();
	}
	return 0;
}
```

---

## 作者：_Cheems (赞：3)

显然先令 $a_i=w_i-b_i$，那么判定 $\sum a$ 是否是正数即可。

然后反悔贪心？试了下发现不太行。

观察到数据范围开了个标准的 $n^2$，于是考虑树形 $\rm dp$。定义 $f_{u,i}$ 表示 $u$ 子树内，分为 $i$ 个连通块时，合法连通块有几个。

不过还需记录此时最上面连通块的点权和，$f$ 数组的规模就会到达 $n^3$，不太行。

但是结合做题经验，我们猜测 $f_{u,i}$ 的大小只有 $1$，也就是说可以取到一个绝对最优的值。

试了下，发现确实可行。不过需要改变 $f_{u,i}$ 定义：分为 $i$ 个连通块，**除最上面的连通块外的**合法连通块数量 $cnt$，并记下最上面的连通块权值和 $sum$。

可以保证，$cnt_1>cnt_2$ 时，$f_1$ 一定不劣于 $f_2$。相等时取 $\max sum$ 即可。

转移很简单（记得卡好枚举的上界），于是这道题就做完了。

但提交前，你可能会注意到 $N=\sum n\le 100000$ 这一点。不过，因为单组数据 $O(n^2)$，令所有 $n$ 相等，总共 $O(n^2\frac Nn)=O(nN)$，也就是 $\rm 3e8$ 左右了，可过。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long 
#define pir pair<int, LL>
const int N = 3e3 + 5;
int T, n, m, _a, a[N], siz[N], u, v;
pir f[N][N], g[N]; 
vector<int> to[N];

inline pir mer(pir A, pir B) {return A.first == B.first ? pir{A.first, max(A.second, B.second)} : (A.first > B.first ? pir{A.first, A.second} : pir{B.first, B.second});}
inline void dfs(int u, int fa){
	f[u][1] = {0, a[u]}, siz[u] = 1;
	for(int i = 2; i <= m; ++i) f[u][i] = {-1, 0};
	for(auto v : to[u])
		if(v ^ fa){
			dfs(v, u);
			for(int i = 1; i <= min(m, siz[u] + siz[v]); ++i) g[i] = {-1, 0};
			for(int i = 1; i <= min(m, siz[u]); ++i)
				for(int j = 1; j <= siz[v] && i + j - 1 <= m; ++j){
					//不合并 
					if(i + j <= m)
						g[i + j] = mer(g[i + j], {f[u][i].first + f[v][j].first + (f[v][j].second > 0), f[u][i].second});
					//合并 
					if(i + j - 1 <= m)
						g[i + j - 1] = mer(g[i + j - 1], {f[u][i].first + f[v][j].first, f[u][i].second + f[v][j].second}); 
				}
			siz[u] += siz[v];
			for(int i = 1; i <= min(m, siz[u] + siz[v]); ++i) f[u][i] = g[i];
		}
}
signed main(){
	cin >> T;
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), to[i].clear();
		for(int i = 1; i <= n; ++i) scanf("%d", &_a), a[i] = _a - a[i];
		for(int i = 1; i < n; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
		dfs(1, 0); 
		printf("%d\n", f[1][m].first + (f[1][m].second > 0));
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1280D)

## 思路

比较简单的 $\rm 2500$。

这个范围 $n,m \le 3 \times 10^3$，是树形背包没错了，不妨设 $f_{x,i}$ 表示以 $x$ 为根的子树内选出 $i$ 个连通块的最大满足要求的块数。

但是发现这样很难转移，考虑表示出一个包含根节点的连通块，我们称为主块，再设 $g_{x,i}$ 表示以 $x$ 为根的子树内选出 $i$ 个连通块主块的 $\sum w_i-b_i$ 的最大值，然后把 $f_{x,i}$ 定义为除主块外最大满足要求的块数。这样就很好合并了。

合并可以直接分两类讨论：

+ 把 $v$ 的主块并成一个普通块内：

  $f_{x,i}=\max(f_{x,i},f_{x,j}+f_{v,i-j}+[g_{x,j}>0])$

  $g_{x,i}=\max(g_{x,i},g_{x,j})$

+ 把 $v$ 的主块与 $x$ 的主块合并成一个更大的主块：

  $f_{x,i}=\max(f_{x,i},f_{x,j}+f_{v,i-j+1})$
  
  $g_{x,i}=\max(g_{x,i},g_{x,j}+g_{v,i-j+1})$
  
然后就做完了，时间复杂度 $\mathcal O(n^2)$，理论上很难过，但是跑的挺快。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=3e3+10;
int f[N][N],g[N][N],m,b[N],w[N],siz[N],dp1[N],dp2[N];
vector<int>a[N];
inline void dfs(int x,int fa){
	siz[x]=1;g[x][1]=w[x]-b[x];
	for (auto v:a[x]){
		if (v==fa) continue;
		dfs(v,x);
		for (int j=1;j<=min(siz[x]+siz[v],m);++j) dp1[j]=0,dp2[j]=-9e18;
		for (int j=1;j<=siz[x];++j)
			for (int k=1;k<=siz[v];++k){
				int now=f[v][k]+f[x][j];
				if (g[v][k]>0) ++now;
				if (now>dp1[j+k]) dp1[j+k]=now,dp2[j+k]=g[x][j];
				else if (now==dp1[j+k]) dp2[j+k]=max(dp2[j+k],g[x][j]);
				if (g[v][k]>0) --now;
				if (now>dp1[j+k-1]) dp1[j+k-1]=now,dp2[j+k-1]=g[x][j]+g[v][k];
                else if (now==dp1[j+k-1])  dp2[j+k-1]=max(dp2[j+k-1],g[x][j]+g[v][k]);
            }
		for (int j=1;j<=siz[x]+siz[v];++j) f[x][j]=dp1[j],g[x][j]=dp2[j];
		siz[x]+=siz[v];
	}
}
inline void solve(){
	int n,u,v;cin>>n>>m;
	for (int i=1;i<=n;++i) cin>>b[i];
	for (int i=1;i<=n;++i) cin>>w[i];
	for (int i=1;i<=n;++i) a[i].clear();
	for (int i=1;i<n;++i) cin>>u>>v,a[u].push_back(v),a[v].push_back(u);
	memset(g,-0x3f,sizeof(g));
	memset(f,0,sizeof(f));dfs(1,-1);
	cout<<f[1][m]+(g[1][m]>0)<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Zxc200611 (赞：0)

upd：谢谢 @\_lxy\_ 的提醒。

# CF1280D Miss Punyverse

显然可以令 $val_i=w_i-b_i$，则问题变为求 $val$ 之和大于 $0$ 的最大块数。

考虑树形 dp。

设 $dp_{u,x}$ 表示将点 $u$ 的子树划分成 $x$ 个连通块，$val$ 之和大于 $0$ 的最大块数。然而发现无法转移，因为我们不知道 $u$ 所在连通块的 $val$ 之和是多少。

有一个性质：将每个子树中，不包含根所在连通块的部分，划分成相同的块数时，有一个划分方案 $A$ 使得 $val$ 之和大于 $0$ 的块数比另一个划分方案 $B$ 至少多 $1$，那么无论 $B$ 在树根处的连通块在上面怎样划分，对答案也至多贡献 $1$，不比 $A$ 优。

所以我们可以贪心地让（$u$ 子树不包含 $u$ 所在连通块的部分）的划分中，$val$ 之和大于 $0$ 的块尽量多。在此条件下，我们也想让 $u$ 所在的连通块 $val$ 之和最大，这样在上面就更有可能拼出一个 $val$ 之和大于 $0$ 的连通块。

于是我们设 $dp_{u,x}$ 表示将点 $u$ 的子树不包含 $u$ 所在连通块的部分划分成 $x$ 个连通块，$val$ 之和大于 $0$ 的最大块数。

再设 $mxv_{u,x}$ 表示将点 $u$ 的子树不包含 $u$ 的部分划分成 $x$ 个连通块，满足 $val$ 之和大于 $0$ 的块尽量多的条件下， $u$ 所在的连通块的 $val$ 之和最大是多少。

于是可以得到转移方程：

枚举每个 $u$ 的儿子 $v$。

当把 $u$、$v$ 划入两个不同的连通块时，$v$ 所在的连通块划分完毕（不能再往它里面加入新节点了），将其计入答案。
$$
\begin{aligned}
dp_{u,x+y+1} &\overset{\max}{\longleftarrow} dp_{u,x}+dp_{v,y}+[mxv_{v,y}>0]\\
&\Rightarrow mxv_{u,x+y+1} \overset{\max}{\longleftarrow} mxv_{u,x}
\end{aligned}
$$
当不把 $u$、$v$ 划开时，$u$、$v$ 所在的连通块合并为一个。
$$
\begin{aligned}
dp_{u,x+y} &\overset{\max}{\longleftarrow} dp_{u,x}+dp_{v,y} \\
&\Rightarrow mxv_{u,x+y} \overset{\max}{\longleftarrow} mxv_{u,x}+mxv_{v,y}
\end{aligned}
$$
(其中 $\Rightarrow$ 表示上面成功执行时才执行此操作。)

边界显然是 $dp_{u,0} \gets 0$，$mxv_{u,0} \gets val_u$。

不过，转移过程中，我们需要考虑每个子树的贡献（也就是说，不能因为某个子树无论怎么划分都不优就不考虑它）。所以我们在 $u$ 的答案中每加入一个子树 $v$，都要保证新的答案是原答案和 $v$ 的答案合并后的结果，即不能用原答案与合并后的结果取 $\max$。具体实现可见代码。

答案就是 $dp_{root,m-1}+[mxv_{root,m-1}>0]$。

设点 $u$ 的子树大小为 $siz_u$。

时间复杂度貌似是 $O\left(\sum_u siz_u^2\right)$，在数据为一条链时会被卡成 $O(n^3)$，难以通过。

不过实现的精细一点的话，每次只拿出 $dp_v$ 的前 $siz_v$ 项与 $dp_u$ 的前（$u$ 在 $v$ 之前的儿子的子树大小之和）项进行合并，总时间复杂度可以做到 $\sum_{u} \sum_{x,y \in son_u} siz_x siz_y$，其中 $siz_u$ 表示 $u$ 的子树大小。

可以推出：
$$
\begin{aligned}
&\ \ \ \ \ \sum_{u} \sum_{x,y \in son_u} siz_x siz_y \\
&= \dfrac{\sum_{u} siz_{u}^2-\sum_{x \in son_u}siz_x^2}{2} 
\end{aligned}
$$
我们发现，在上式中，每个点贡献的 $siz_u^2$ 会在 $u$ 的父亲中被减去，所以最后剩下的是 $\frac{siz_{root}^2}{2}=O(n^2)$。

故此做法足以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> t[3100];
int dp[3100][3100],mxv[3100][3100];
int tdp[3100],tmxv[3100];
int val[3100];
int siz[3100];
int blk[3100];
int n,m;
void init(int n,int m)
{
	memset(tdp,0,sizeof(tdp));
	memset(tmxv,0,sizeof(tmxv));
	for(int i=0;i<=n;i++)
	{
		t[i].clear();
		val[i]=0;
		for(int j=0;j<=m;j++)
		{
			dp[i][j]=mxv[i][j]=0;
		}
	}
}
void dfs(int u,int f)
{
	dp[u][0]=0;
	mxv[u][0]=val[u];
	siz[u]=1;
	for(int i=0;i<t[u].size();i++)
	{
		int v=t[u][i];
		if(v==f)
			continue;
		dfs(v,u);
		memset(tdp,128,sizeof(tdp));
		memset(tmxv,128,sizeof(tmxv));
		for(int x=0;x<=min(m-1,siz[u]-1);x++)
		{
			for(int y=0;y<=min(m-1,siz[v]-1);y++)
			{
				int tans=dp[u][x]+dp[v][y]+(mxv[v][y]>0);
				if(tdp[x+y+1]<tans||(tdp[x+y+1]==tans&&tmxv[x+y+1]<mxv[u][x]))
				{
					tmxv[x+y+1]=mxv[u][x];
					tdp[x+y+1]=tans;
				}
				tans=dp[u][x]+dp[v][y];
				if(tdp[x+y]<tans||(tdp[x+y]==tans&&tmxv[x+y]<mxv[u][x]+mxv[v][y]))
				{
					tmxv[x+y]=mxv[u][x]+mxv[v][y];
					tdp[x+y]=tans;
				}
			}
		}
		memcpy(dp[u],tdp,sizeof(dp[u]));
		memcpy(mxv[u],tmxv,sizeof(mxv[u]));
		siz[u]+=siz[v];
	}
}
signed main()
{
	int T;
	cin>>T;
	for(int _=1;_<=T;_++)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>val[i];
		}
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			val[i]=x-val[i];
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			t[u].push_back(v);
			t[v].push_back(u);
		}
		dfs(1,0);
		cout<<dp[1][m-1]+(mxv[1][m-1]>0)<<'\n';
		init(n,m);
	}
}
```

---

## 作者：dead_X (赞：0)

## 前言
好题，就是有点烂，树上背包模板题，$2500$ 刚好。
## 思路
首先把选票减一下，然后就变成连通块价值 $\sum>0$ 即合法了。

显然这种题只能 dp 了，考虑设个状态。

状态挺好想的，就是 $i$ 的子树选了 $j$ 个连通块，剩下一个包含根的连通块没选/全部选完。

于是果断设 $f_{i,j}$ 为上述情况的最大合法区域数量，但是这算不了，因为我们不知道没选的那个区域的 $\sum$ 是多少。

然后我们马上发现，显然 $f$ 更大更优，只需要在 $f$ 相同的时候记录最大 $\sum$ 记为 $g_{i,j}$ 即可。

因此我们可以做一遍树上背包，做完之后必定会留一个包含根的子树没被选，更新一轮把这个子树选掉的决策即可。

到根计算答案的时候记得不要搞这个决策了，直接将 $m-1$ 个连通块的答案输出就行了。

单组数据复杂度 $O(n^2)$，总复杂度 $O(n\sum n)$，因为树上背包跑的挺快所以就过去了。毕竟 $4$ 秒跑 $3\times 10^8$ 在 CF 是家常便饭了。
## 代码
```cpp
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[3003];
int sz[3003];
int f[3003][3003],tf[3003];
ll g[3003][3003],tg[3003];
int n,m;
vector<int> e[3003];
void dfs(int x,int fa)
{
	sz[x]=1;
	for(int i=1; i<=n; ++i) f[x][i]=-1;
	for(int i=1; i<=n; ++i) g[x][i]=-1;
	f[x][0]=0,g[x][0]=a[x];
	for(int i:e[x]) if(i!=fa)
	{	
		dfs(i,x);
		for(int j=0; j<sz[x]+sz[i]&&j<m; ++j) tf[j]=-1;
		for(int j=0; j<sz[x]+sz[i]&&j<m; ++j) tg[j]=-1;
		for(int j=0; j<sz[x]; ++j)
		for(int k=0; k<=sz[i]&&j+k<m; ++k)
		if(f[x][j]+f[i][k]>tf[j+k]) 
			tf[j+k]=f[x][j]+f[i][k],
			tg[j+k]=g[x][j]+g[i][k]; 
		else if(f[x][j]+f[i][k]==tf[j+k])
			tg[j+k]=max(tg[j+k],g[x][j]+g[i][k]);
		sz[x]+=sz[i];
		for(int j=0; j<sz[x]&&j<m; ++j) f[x][j]=tf[j];
		for(int j=0; j<sz[x]&&j<m; ++j) g[x][j]=tg[j];
	}
	if(x==1) printf("%d\n",f[x][m-1]+(g[x][m-1]>0));
	for(int i=min(sz[x],m-1)-1; i>=0; --i) 
	if(f[x][i]+(g[x][i]>0)>f[x][i+1]) 
		f[x][i+1]=f[x][i]+(g[x][i]>0),g[x][i+1]=0; 
	else if(f[x][i]+(g[x][i]>0)==f[x][i+1]&&g[x][i+1]<0)
		g[x][i+1]=0;
	return ;
}
signed main()
{
	for(int T=read();T--;)
	{
		n=read(),m=read();
		for(int i=1; i<=n; ++i) a[i]=-read();
		for(int i=1; i<=n; ++i) a[i]+=read();
		for(int i=1; i<=n; ++i) e[i].clear();
		for(int i=1; i<n; ++i)
		{
			int u=read(),v=read();
			e[u].push_back(v),e[v].push_back(u);
		}
		dfs(1,1);
	}
	return 0;
}
```

---

## 作者：sunzh (赞：0)

一个简单的树形dp的思路是用$dp_{i,j,0/1}$
表示$i$子树内划分为$j$个确定联通块，$fa_i->i$的边是否保留，所得到的合法的联通块的最大个数以及在此前提下最上面的联通块的$s_w-s_b$最大和

这样子时间复杂度是$O(4n^2)$的，很不幸地被出题人卡了

我们考虑把$0/1$去掉，后果是最上面联通块的答案是否统计引发歧义

我们考虑强行不计算最上面联通块，在$fa_i$中转移时再考虑$fa_i->i$的去留，根据记录的最大和判断贡献

这样的复杂度就降到了$O(n^2)$可以顺利AC

处理细节详见代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<set>
#include<vector>
#include<cmath>
#define PII pair<int,int>
#define pb push_back
#define ep emplace_back
#define mp make_pair
#define fi first
#define se second
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f==1?x:-x;
}
inline void print(int x){
	if(x<0) putchar('-'),x=~x+1;
	if(x>=10) print(x/10);
	putchar((x%10)|48);
}
int T;
int n,m;
PII dp[3010][3010];
vector<int>vec[3010];
int b[3010],w[3010];
int siz[3010];
PII tmp[3010];
const int inf=0x153f3f3f3f3f3f3fll;
void dfs(int x,int f){
	dp[x][1]=mp(0,w[x]-b[x]);
	siz[x]=1;
	for(int v:vec[x]){
		if(v==f) continue ;
		dfs(v,x);
		for(int j=1;j<=siz[x]+siz[v]+1&&j<=m;++j) tmp[j]=mp(-1,-inf);
		for(int j=1;j<=siz[x];++j){
			for(int k=1;k<=siz[v];++k){
				int sfi=dp[x][j].fi+dp[v][k].fi;
				sfi+=(dp[v][k].se>0);
				if(sfi>tmp[j+k].fi) tmp[j+k].fi=sfi,tmp[j+k].se=dp[x][j].se;
				else if(sfi==tmp[j+k].fi) tmp[j+k].se=max(tmp[j+k].se,dp[x][j].se);
				sfi-=(dp[v][k].se>0);
				if(sfi>tmp[j+k-1].fi) tmp[j+k-1].fi=sfi,tmp[j+k-1].se=dp[x][j].se+dp[v][k].se;
				else if(sfi==tmp[j+k-1].fi) tmp[j+k-1].se=max(tmp[j+k-1].se,dp[x][j].se+dp[v][k].se);
			}
		}
		siz[x]+=siz[v];
		for(int j=1;j<=siz[x];++j) dp[x][j]=tmp[j];
	}
}
signed main(){
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;++i) vec[i].clear();
		for(int i=1;i<=n;++i) for(int j=0;j<=m;++j) dp[i][j]=mp(-1,-0x3f3f3f3f);
		for(int i=0;i<=m;++i) tmp[i]=mp(-1,-0x3f3f3f3f);
		for(int i=1;i<=n;++i) b[i]=read();
		for(int i=1;i<=n;++i) w[i]=read();
		for(int i=1;i<n;++i){
			int u=read(),v=read();vec[u].pb(v),vec[v].pb(u);
		}
		dfs(1,0);
		printf("%d\n",dp[1][m].fi+(dp[1][m].se>0));
	}
}
```


---

