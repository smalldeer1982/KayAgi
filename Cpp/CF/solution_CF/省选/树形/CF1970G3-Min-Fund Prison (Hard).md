# Min-Fund Prison (Hard)

## 题目描述

现给出一张由 $n$ 个点 $m$ 条边构成的无向图，其 $m$ 条边为 $(u_i, v_i)$ ( $1\leq i\leq m$ )，表示 $u_i,v_i$ 相连。图中不存在重边，也没有自环。

你可以以 $c$ 的成本在任意两个点 $x, y$ 之间连一条边（连边操作进行之后图必须连通）。这个操作可以进行任意次，设你操作了 $k$ 次。要求操作结束后图是连通的。

在连边操作之后，你必须删去一条割边，使得剩下的图恰由 $2$ 个连通块组成。设两个连通块的大小为 $x,y$ ，请问 $x^2+y^2+kc$ 的最小值为何？

## 样例 #1

### 输入

```
4
4 6 5
4 3
2 3
2 4
1 2
4 1
3 1
6 6 2
1 4
2 5
3 6
1 5
3 5
6 5
6 5 7
1 4
2 5
3 6
3 5
6 5
7 5 4
1 4
3 6
3 5
6 5
2 7```

### 输出

```
-1
20
25
33```

# 题解

## 作者：zhongpeilin (赞：8)

## 题目大意：
有一张无向图，现在你要加一些边使得图联通，然后你再删掉一条边，使得图分成两部分，设 $k$ 为加的边个数，$x$ 为分开后其中一个的大小，$y$ 为另一个连通块的大小，代价就是 $k \times c + x^2 + y^2$，现在求最小代价。  
## 解题思路：
不难发现，最后删的那条边是一个**桥**，也就是说对于初始图中的边双，最后这里头的点一定分在同一集合，因为无法只删除一条边使得他们不连通。  

那么再考虑加边部分，一条加边两端一定不会链接两个在原图中可互相到达的点，因为加上这条边后它所连的两个端点在同一个边双里，说明最后不能删这条加边，但他还不影响连通性，又加了 $c$ 的代价，一定不优。  

**所以，$k$ 一定等于连通块个数减一**。  

那么接下来怎么处理呢？由于同一个边双的点最后一定在一个集合里，所以我们可以先边双缩点，然后就有了一些树，问题转化成：有一个森林，你可以将一棵树删掉一条边，构成两个新树，每个点都有一个大小，要将森林分成两组，使得 $x^2 + y^2$ 最小。  

我们对于每棵树设它的总大小为 $szz$，设一个子树大小为 $sz_{x}$，那么就将树中的每个 $szz - sz_{x}$ 和 $sz_{x}$ 都存起来，问题变成一个可行性分组背包，我们设 $dp_{i, j, k}$ 表示前 $j$ 棵树中，有没有用过删边操作后能不能选出 $k$。  
可以拿 bitset 优化，时间复杂度 $O(\frac{n^2}{w})$，可过。  
## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int col[100005], dcc[100005];
int n, m, c, dcctot, cnt, allsz;
int T, dfn[100005], low[100005];
vector<int> g[200005];
bitset<50005> dp[2][2]; //滚动数组，0表示用过删边的操作，1表示没有
stack<int> S;
vector<int> sz[100005];
bool vis[200005];

void tarjan(int x, int fa){
	S.push(x);
	dfn[x] = low[x] = ++T;
	bool flag = false;
	for(auto it : g[x]){
		if(it == fa && !flag){ //不要与来的那条边一样，但如果两点之间有重边就行
			flag = true;
			continue;
		}
		if(!dfn[it]){
			tarjan(it, x);
			low[x] = min(low[x], low[it]); 
		} else {
			low[x] = min(low[x], dfn[it]);
		}
	}
	if(dfn[x] == low[x]){
		int u = 0;
		dcctot++;
		dcc[dcctot] = 0;
		do{
			u = S.top();
			S.pop();
			col[u] = dcctot;
			dcc[dcctot]++;
		}while(u != x);
	}
}

int dfs(int x){
	int szz = dcc[x - n];
	vis[x] = 1;
	for(auto it : g[x]){
		if(!vis[it]){
			szz += dfs(it);
		} 
	}
	sz[cnt].push_back(szz);
	return szz;
}
void solve(){
	while(!S.empty()) S.pop();
	cin >> n >> m >> c;
	dcctot = T = 0;
	for(int i = 1; i <= n; i++) {
		g[i].clear();
		dfn[i] = low[i] = 0;
	}
	for(int i = 1; i <= m; i++){
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x); 
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, 0);
	for(int i = n + 1; i <= 2 * n; i++) g[i].clear();
	for(int i = 1; i <= n; i++){
		for(auto it : g[i]){
			if(col[it] != col[i]){
				g[col[i] + n].push_back(n + col[it]);
			}
		}
	}
	if(dcctot == 1){ //不可能把他分成两份
		cout <<-1 << endl;
		return ;
	}
	cnt = 0;
	for(int i = 1; i <= 2 * n; i++) vis[i] = 0;
	for(int i = 1; i <= dcctot; i++){
		if(!vis[i + n]){
			sz[++cnt].clear();
			allsz = dfs(i + n);
			int len = sz[cnt].size();
			for(int j = 0; j < len; j++) sz[cnt].push_back(allsz - sz[cnt][j]);
		}
	}
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			dp[i][j].set(0);
		}
	}
	dp[0][0][0] = dp[1][0][0] = 1;
	for(int i = 1; i <= cnt; i++){
		int all = sz[i].size() / 2 - 1;
		dp[0][i % 2] = (dp[0][(i % 2) ^ 1] | (dp[0][(i % 2) ^ 1] << sz[i][all])); //全选
		for(auto szz : sz[i]){ //切割子树，选择要哪个
			dp[0][i % 2] |= (dp[1][(i % 2) ^ 1] << szz);
		}
		dp[1][i % 2] = (dp[1][(i % 2) ^ 1] | (dp[1][(i % 2) ^ 1] << sz[i][all]));
	}
	long long ans = 1e18;
	for(int i = n / 2; i >= 0; i--){
		if(dp[0][cnt % 2][i] || dp[1][cnt % 2][i]){
			ans = min(ans, 1ll * (cnt - 1) * c + 1ll * i * i + 1ll * (n - i) * (n - i));
		}
	}
	cout << ans << endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}

---

## 作者：rizynvu (赞：4)

[我的博客](https://www.cnblogs.com/rizynvu/p/18374511)。

2024.12.18：修改了错误代码。

时间 $\mathcal{O}(\frac{n\sqrt{n}\log n}{\omega})$ 空间 $\mathcal{O}(\frac{n\log n}{w})$ 的爆标做法。

首先无解当且仅当图联通且无割边。

首先考虑加边的贡献。  
一个比较直观的感受就是只会尽可能少的加边，即加边到整个图连通。

证明考虑删掉的边。  
如果加多了边导致删除后不会有两个连通块一定不行；如果加多了边后最后分出的还是两个连通块显然加多的边是不必要的。

于是加边的贡献就好算了，因为加的边的数量一定是连通块数 $-1$。

接下来考虑删边后的贡献。  
显然的是肯定两部分大小越接近 $\frac{n}{2}$ 越优。

考虑两部分是如何组成的。    
能发现除了有一个连通块会被割边拆开，其他的连通块都会整体留下，并且这些连通块可以任意组合（还有一种情况是选的割边是加的边，即就是连通块任意组合，可以与上一种情况一同处理）。

于是就可以想到用背包的形式，得到去掉某一个连通块其他连通块大小的背包，这显然是可以 `bitset` 优化的。  

于是一个想法就是缺一分治，即分治时把一边贡献到递归下去的另一边处理，但复杂度为 $\mathcal{O}(\frac{n^2\log n}{\omega})$，还是不太行。

进一步的，考虑到除掉去除的连通块，对于其他的连通块其实只关心其大小。  
于是在缺一分治时，实际上只需要考虑对出现过的连通块的大小分治。

具体的，若一种连通块的大小的出现次数 $c \ge 1$，就可以先将 $c - 1$ 个用二进制分组的形式放入背包。  
那么缺一分治时，实际上涉及到的元素就是连通块的大小了。  
大小的种类数是 $\mathcal{O}(\sqrt{n})$ 的，所以这部分的复杂度是 $\mathcal{O}(\frac{n\sqrt{n}\log n}{\omega})$。

接下来优化求解答案。  
考虑到因为连通块大小的和 $= n$，所以可以直接暴力枚举划分情况，令其中一个块划分到的大小为 $x$，并钦定 $x$ 所在块大小 $\ge \lceil\frac{n}{2}\rceil$，再去找这个大小实际是多少。

那么就是找到最靠前的 $\ge \lceil\frac{n}{2}\rceil - x$ 的位置。  

一个想法是判定一下 $\lceil\frac{n}{2}\rceil - x$ 是否存在，不存在就用 `_Find_next`，$\mathcal{O}(\frac{n^2}{\omega})$。  
但是考虑到当 $x$ 递增时 $\lceil\frac{n}{2}\rceil - x$ 是递减的，这个最优的位置是可以继承的，就可以先 `_Find_next` 问出 $x = 0$ 的情况，然后扫一遍动态维护。

于是这部分复杂度就是 $\mathcal{O}(n + \frac{n\sqrt{n}}{w})$。

最后总时间复杂度 $\mathcal{O}(\frac{n\sqrt
n\log n}{\omega})$。  
因为分治的每一层都需要开一个 `bitset`，空间复杂度 $\mathcal{O}(\frac{n\log n}{\omega})$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
inline ll pw2(int n) {return 1ll * n * n;}
const int maxn = 1e5 + 10;
int n;
std::vector<int> to[maxn];
int dfn[maxn], low[maxn], ins[maxn], stk[maxn], top, dtot;
std::vector<int> S;
std::vector<int> vis[maxn];
int tot[maxn];
std::vector<int> val;
int dfs(int u, int fa) {
   dfn[u] = low[u] = ++dtot, ins[u] = 1, stk[++top] = u;
   int siz = 1;
   for (int v : to[u]) {
      if (v == fa) continue;
      if (! dfn[v]) {
         int siz_ = dfs(v, u); low[u] = std::min(low[u], low[v]);
         if (low[v] > dfn[u])
            S.push_back(siz_);
         siz += siz_;
      } else if (ins[v])
         low[u] = std::min(low[u], dfn[v]);
   }
   if (low[u] == dfn[u]) {
      int t;
      do {
         t = stk[top--], ins[t] = 0;
      } while (t != u);
   }
   return siz;
}
std::bitset<maxn> B[20];
ll ans;
void solve(int l, int r, int dep = 0) {
   if (l == r) {
      int x = val[l], n2 = n + 1 >> 1;
      int w = B[dep]._Find_next(n2);
      for (int i = 0; i <= x; i++) {
         if (n2 >= i && B[dep][n2 - i])
            w = n2 - i;
         if (vis[x][i] && w < maxn)
            ans = std::min(ans, pw2(w + i) + pw2(n - w - i));
      }
      return ;
   }
   int mid = (l + r) >> 1;
   B[dep + 1] = B[dep];
   for (int i = mid + 1; i <= r; i++)
      B[dep + 1] |= B[dep + 1] << val[i];
   solve(l, mid, dep + 1);
   B[dep + 1] = B[dep];
   for (int i = l; i <= mid; i++)
      B[dep + 1] |= B[dep + 1] << val[i];
   solve(mid + 1, r, dep + 1);
}
inline void Main() {
   int m, co; scanf("%d%d%d", &n, &m, &co);
   for (int i = 1; i <= n; i++)
      to[i].clear();
   for (int i = 1, x, y; i <= m; i++)
      scanf("%d%d", &x, &y), to[x].push_back(y), to[y].push_back(x);
   int cnt = 0;
   dtot = 0, memset(dfn, 0, sizeof(int) * (n + 1));
   for (int i = 1; i <= n; i++)
      tot[i] = 0, vis[i].clear();
   val.clear();
   for (int i = 1; i <= n; i++)
      if (! dfn[i]) {
         cnt++; int siz = dfs(i, 0);
         if (! tot[siz]++)
            vis[siz].resize(siz + 1), val.push_back(siz);
         for (int x : S)
            vis[siz][x] = vis[siz][siz - x] = 1;
         vis[siz][0] = vis[siz][siz] = 1;
         S.clear();
      }
   if (cnt == 1) {
      bool fl = 0;
      for (int i = 1; i < n; i++)
         fl |= vis[n][i];
      if (! fl)
         return puts("-1"), void();
   }
   B[0].reset(), B[0].set(0);
   ans = 1e18;
   for (int x = 1; x <= n; x++) {
      if (tot[x]) {
         int v = tot[x]; v--;
         for (int i = 1; i <= v; v -= i, i <<= 1)
            B[0] |= B[0] << i * x;
         B[0] |= B[0] << v * x;
      }
   }
   solve(0, val.size() - 1);
   printf("%lld\n", 1ll * co * (cnt - 1) + ans);
}
int main() {
   int T; scanf("%d", &T);
   while (T--) Main();
   return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

Wrong Answer on test 10！Wrong Answer on test 11！

upd on 2024.6.6：G2 特化代码贴错了，进行了修改。

# Part 2：正文

先来考虑树的部分，注意到全图联通，所以多连边是没有用的，我们只需要枚举在哪条边断掉即可。预处理每个点子树和子树补的大小即可做到时间复杂度 $O(n)$。

然后考虑图的部分。注意到如果我们选择断掉连通块里的边，则断掉的边一定是桥，否则断掉后不符合题意，同时，我们加边的目的也只会是把不连通的连通块连接起来，否则会减少桥的个数，一定不优。

基于以上分析，不难写出一个 dp。令 $f(i,j)$ 表示考虑到第 $i$ 个连通块，最终答案中某一个连通块的大小是 $j$ 是否可行。同时令 $g(i,j)$ 表示在不断边的情况下，前面的连通块是否可以构成一个大小为 $j$ 的连通块。枚举到一个连通块时，先求出这个连通块所有边双，缩掉边双成树后，统计树上每个点子树的大小。此时树上的每条边都是桥。如果当前选择断掉树上的边，设断掉后树两侧的节点树分别为 $v_1,v_2$，则有转移 $f(i,j)\leftarrow g(i-1,j-v_1),f(i,j)\leftarrow g(i-1,j-v_2)$，对 $g(i,j)$ 则有转移 $g(i,j)\leftarrow g(i-1,j-S)$，其中 $S$ 为连通块大小。最后在 $f(c,*)=1$ 处贡献答案即可，$c$ 为连通块个数。

直接 dp 即可做到 $O(n^2)$。注意到 $f$ 和 $g$ 均为 01，且转移形式简单，故可以 bitset 优化，做到 $O\left(\dfrac{n^2}{\omega}\right)$。

对于 G2 我们其实还有一个特化做法，枚举哪条边断掉，然后搜每个连通块的大小，直接对这个做背包，然后贡献到答案即可。注意到断掉非桥边一定不优于断掉连通块中的桥边，也不优于不断边，故可以保证正确性。时间复杂度 $O(n^2m)$ 到 $O\left(\dfrac{n^2m}{\omega}\right)$ 不等。

# Part 3：代码

[G2 特化做法](https://codeforces.com/contest/1970/submission/262382665) 



```cpp
// You don't have to be sorry
// 你也无需抱有歉意
// I don't have to be brave
// 而我也不必鼓起勇气
// I'm picking up where I started
// 我在重新拾起初忆
// And I'mma make it okay
// 我将会让一切回到正轨
// Leave the keys to my apartment
// 你走吧，不过记得把钥匙给我
// Cause I don't need you to stay
// 因为我并不需要你的留下
// Yeah you don't have to be sorry
// 没错，你无需抱有歉意
// And I'mma make it okay
// 我现在过得很是滋润
// Cause you make me better
// 都是你拜你所赐

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T>
void seq_read(T bg,T ed){for(auto i=bg;i!=ed;++i)read(*i);}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
//Some useful function

template<typename T>
void cmax(T& x,T y){x=max(x,y);}
template<typename T,typename... Args>
void cmax(T& x,T y,Args ...args){cmax(x,y);cmax(x,args...);}
template<typename T>
void cmin(T& x,T y){x=min(x,y);}
template<typename T,typename... Args>
void cmin(T& x,T y,Args ...args){cmin(x,y);cmin(x,args...);}
template<typename T,typename U>
void seq_assign(T bg,T ed,U val){for(auto i=bg;i!=ed;++i)(*i)=val;}
template<typename T,class F,class=enable_if_t<is_invocable_v<F>>>
void seq_assign(T bg,T ed,F func){for(auto i=bg;i!=ed;++i)(*i)=func(i);}
template<typename T>
void seq_copy(T dstbg,T dsted,T srcbg,T srced){for(auto i=dstbg,j=srcbg;i!=dsted&&j!=srced;++i,++j)(*i)=(*j);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=3e5+7;
constexpr ll inf=LONG_LONG_MAX;
int n,m,c;
vector<int>g[N];
int low[N],dfn[N],siz[N],dfx;
bitset<N>F,G,H;

bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(n,m,c);
	for(int i=1;i<=n;i++)
		g[i].clear(),dfn[i]=low[i]=0;
	dfx=0;
	F.reset(),G.reset();
	for(int i=1;i<=m;i++){
		int u,v;read(u,v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	vector<int>lis;
	auto tarjan=[&](auto self,int u,int fa)-> void {
		siz[u]=1;dfn[u]=low[u]=++dfx;
		for(auto v:g[u])
			if(!dfn[v])
				self(self,v,u),low[u]=min(low[u],low[v]),siz[u]+=siz[v];
			else if(v!=fa)
				low[u]=min(low[u],dfn[v]);
		if(dfn[u]==low[u])
			lis.emplace_back(siz[u]);
	};
	F.set(0);G.set(0);
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(!dfn[i]){
			++cnt;
			lis.clear();
			tarjan(tarjan,i,0);
			lis.pop_back();
			// printf("> ");
			// for(auto v:lis)
			// 	printf("%d ",v);
			// printf("\n");
			for(auto v:lis)
				F|=G<<v,F|=G<<(siz[i]-v);
			G|=G<<siz[i];
		}
	F|=G;
	ll ans=inf;
	for(int i=1;i<n;i++)
		if(F.test(i))
			ans=min(ans,(ll)(cnt-1)*c+(ll)i*i+(ll)(n-i)*(n-i));
	printf("%lld\n",ans==inf?-1ll:ans);
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;read(T);
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

## 作者：conti123 (赞：0)

## CF1970G

从 G1 来的，发现和后面其实有关系。

题意有些欠缺，加的边一定要使原图联通，然后才能断掉。

### Medium

注意到加的边一定是连通块数 $-1$ 条不变，因为这个坑了我好久，所以只需要最小化 $x^2+y^2$ 即可。

无解当且仅当原图是一个大的边双。

注意到删除的边一定是割边或者加入的边，而一个边双内的点一定在一个连通块内，考虑边双缩点。

于是变成了一颗森林，考虑可行性背包，$f_{i,j,k}$ 表示前 $i$ 个树删或没删完边后能否达到 $k$。

转移的话很简单，像 G1 一样看每一棵树能转移出多少，注意可以整棵树一起，也可以是砍掉一个子树后取剩下的，如果砍了 $j$ 记得变。

发现直接做时空复杂度均为 $O(n^2)$。

### Hard

考虑优化 G2 的做法，发现空间能用滚动数组滚去一维，变成 $O(n)$，时间上发现题解有 $O(\frac{n\sqrt n \log n}{w})$ 的神奇做法？

算了，我是蒟蒻，没想到可以用 bitset 优化，这样的话一次可以除去 $w$ 的常数，时间复杂度变为 $O(\frac{n^2}{w})$，可以通过此题。

```cpp
struct fy{
	int v,nxt;
}edge[N<<1];
int dfn[N],low[N],n,m,k,idx=1,head[N<<1],id,S[N],Sid,sum,inw[N],sz[N];
inline void add(int x,int y){
	edge[++idx].v=y,edge[idx].nxt=head[x],head[x]=idx;
}
inline void dfs(int u,int from){
	//printf("begin%d %d\n",u,from);
	dfn[u]=low[u]=++id;
	S[++Sid]=u;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(!dfn[v]){
			dfs(v,i);
			low[u]=min(low[u],low[v]);
		}
		else if(i!=(from^1))
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		sum++;
		int pp;
		do{
		//	printf("1\n");
			pp=S[Sid--];
			sz[sum]++;
			inw[pp]=sum;
		}
		while(pp!=u);
	}
//	printf("end%d %d\n",u,from);
}
int vis[N],szid=0,tsz[N];
vector<int>SZ[N],E[N];
int dfs1(int u){
	int siz=sz[u];
	vis[u]=1;
	for(int v:E[u]){
		if(vis[v])
			continue;
		siz+=dfs1(v);
	}
	SZ[szid].psb(siz);
	return siz;
}
bitset<50001>f[2][2];
inline int read(){
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')
		c=getchar();
	while(c<='9'&&c>='0')
		x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x;
}
void solve(){
//	printf("begin\n");
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		head[i]=0;
	idx=1,id=0,Sid=0,sum=0;
	szid=0;
	for(int i=1;i<=n;i++)
		dfn[i]=low[i]=inw[i]=sz[i]=0,E[i].clear(),SZ[i].clear(),tsz[i]=0,vis[i]=0;
	for(int i=1;i<=m;i++){
		int x,y;
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
//	printf("read ok\n");
	for(int i=1;i<=n;i++){
	//	printf("%d begin\n",i);
		if(!dfn[i])
			dfs(i,0);
	}
//	printf("1\n");
	if(sum==1){
		printf("-1\n");
		return ;
	}
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=edge[i].nxt){
			if(inw[edge[i].v]!=inw[u])
				E[inw[edge[i].v]].psb(inw[u]);
		}
	}
//	printf("2\n");
	for(int i=1;i<=sum;i++){
		if(!vis[i]){
			++szid;
			SZ[szid].clear();
			int tot=dfs1(i);
			tsz[szid]=tot;
			int len=SZ[szid].size()-1;
			for(int j=0;j<=len;j++)
				SZ[szid].psb(tot-SZ[szid][j]);
		}
	}
//	printf("3\n");
	f[0][0].set(0);
	f[0][1].set(0);
	f[1][0].set(0);
	f[1][1].set(0);
	f[0][0][0]=f[1][0][0]=1;
	for(int i=1;i<=szid;i++){
		f[0][i&1]=(f[0][i&1^1]|(f[0][i&1^1]<<tsz[i]));
		for(int v:SZ[i])
			f[0][i&1]|=(f[1][i&1^1]<<v);
		f[1][i&1]=(f[1][i&1^1]|(f[1][i&1^1]<<tsz[i]));
	}
//	printf("dp\n");
	long long ans=1e18;
	for(int i=0;i<=n/2;i++){
		if(f[0][szid&1][i]||f[1][szid&1][i])
			ans=min(ans,1ll*(szid-1)*k+1ll*i*i+1ll*(n-i)*(n-i));
	}
//	cout<<sum<<" "<<ans);
    printf("%lld\n",ans);
}
```

无力吐槽边双缩点的链式前向星了，吃了一堆罚时。

~~好在最后没过。~~

说一下为什么可以用 bitset 优化，因为是可行性背包，里面只有 $0$ 和 $1$，这样能提升效率的 bitset 用来干最合适了，所以用它优化。

---

## 作者：happybob (赞：0)

如果图连通，显然什么边都不用加。Tarjan 之后选一条割边就行。

如果不连通，观察发现最终必然只会连 $k-1$ 条边，其中 $k$ 为连通块个数。然后我们要找到一条边，使得这条边是割边且两边连通块大小差值尽量小。考虑一个朴素 DP，考虑每个联通块和块内每条割边即可转移。进一步注意到这个可以使用 `bitset` 优化，即可通过。复杂度 $O(\dfrac{n^2}{w})$。

代码：


```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int t, n, m, c;
array<vector<int>, N> G;
array<int, N> dfn, sz, low;
int idx;
array<bool, N> vis;
bitset<N> bt, bt2;
ll ans;
vector<int> szs;
int cnt;

void dfs(int u)
{
	vis[u] = 1;
	for (auto& j : G[u])
	{
		if (!vis[j]) dfs(j);
	}
}

void dfs2(int u)
{
	cnt++;
	vis[u] = 1;
	for (auto& j : G[u]) if (!vis[j]) dfs2(j);
}

void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++idx;
	sz[u] = 1;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		if (!dfn[j])
		{
			tarjan(j, u);
			sz[u] += sz[j];
			low[u] = min(low[u], low[j]);
		}
		else low[u] = min(low[u], dfn[j]);
		if (low[j] > dfn[u])
		{
			ans = min(ans, 1ll * sz[j] * sz[j] + 1ll * (n - sz[j]) * (n - sz[j]));
		}
	}
}

vector<int> nsz;

void tarjan2(int u, int fa)
{
	dfn[u] = low[u] = ++idx;
	sz[u] = 1;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		if (!dfn[j])
		{
			tarjan2(j, u);
			sz[u] += sz[j];
			low[u] = min(low[u], low[j]);
		}
		else low[u] = min(low[u], dfn[j]);
		if (low[j] > dfn[u])
		{
			nsz.emplace_back(sz[j]);
			nsz.emplace_back(cnt - sz[j]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		ans = (ll)4e18;
		cin >> n >> m >> c;
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit(), vis[i] = dfn[i] = sz[i] = low[i] = 0;
		idx = 0;
		for (int i = 1; i <= m; i++)
		{
			int u, v;
			cin >> u >> v;
			G[u].emplace_back(v), G[v].emplace_back(u);
		}
		dfs(1);
		bool tag = 1;
		for (int i = 1; i <= n; i++)
		{
			tag &= vis[i];
		}
		if (tag)
		{
			tarjan(1, 0);
			cout << (ans >= (ll)4e18 ? -1ll : ans) << "\n";
		}
		else
		{
			szs.clear(), szs.shrink_to_fit();
			for (int i = 1; i <= n; i++) vis[i] = 0;
			vector<vector<int>> vc;
			for (int i = 1; i <= n; i++)
			{
				if (vis[i]) continue;
				nsz.clear(), nsz.shrink_to_fit();
				cnt = 0;
				dfs2(i);
				tarjan2(i, 0);
				sort(nsz.begin(), nsz.end());
				nsz.erase(unique(nsz.begin(), nsz.end()), nsz.end());
				szs.emplace_back(cnt);
				vc.emplace_back(nsz);
			}
			ans = 1ll * (szs.size() - 1) * c;
			for (int i = 1; i <= n; i++) bt[i] = bt2[i] = 0;
			ll minn = (ll)1e18;
			bt[0] = 1;
			bt2[0] = 1;
			int c = 0;
			for (auto& j : szs)
			{
				for (auto& k : vc[c])
				{
					bt2 |= (bt << k);
				}
				bt |= (bt << j);
				c++;
			}
			bt2 |= bt;
			for (int i = 1; i <= n; i++)
			{
				if (bt2.test(i))
				{
					minn = min(minn, 1ll * i * i + 1ll * (n - i) * (n - i));
				}
			}
			cout << ans + minn << "\n";
		}
	}
	return 0;
}
```

---

