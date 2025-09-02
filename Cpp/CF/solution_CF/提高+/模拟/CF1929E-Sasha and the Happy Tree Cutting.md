# Sasha and the Happy Tree Cutting

## 题目描述

Sasha was given a tree $ ^{\dagger} $ with $ n $ vertices as a prize for winning yet another competition. However, upon returning home after celebrating his victory, he noticed that some parts of the tree were missing. Sasha remembers that he colored some of the edges of this tree. He is certain that for any of the $ k $ pairs of vertices $ (a_1, b_1), \ldots, (a_k, b_k) $ , he colored at least one edge on the simple path $ ^{\ddagger} $ between vertices $ a_i $ and $ b_i $ .

Sasha does not remember how many edges he exactly colored, so he asks you to tell him the minimum number of edges he could have colored to satisfy the above condition.

 $ ^{\dagger} $ A tree is an undirected connected graph without cycles.

 $ ^{\ddagger} $ A simple path is a path that passes through each vertex at most once.

## 说明/提示

In the first test case, Sasha could have colored only one edge $ (1, 2) $ . Then, there would be at least one colored edge on the simple path between vertices $ 1 $ and $ 3 $ , and vertices $ 4 $ and $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929E/a12ac27221d04aa56e014cbf2e8421ab5e15a544.png)In the second test case, Sasha could have colored the edges $ (1, 6) $ and $ (1, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929E/6df2f20069f97a0b34db8fc6f8d67fe5a3f5659b.png)

## 样例 #1

### 输入

```
3
4
1 2
2 3
2 4
2
1 3
4 1
6
1 2
3 1
6 1
5 2
4 2
3
3 1
3 6
2 6
5
1 2
2 3
3 4
4 5
4
1 2
2 3
3 4
4 5```

### 输出

```
1
2
4```

# 题解

## 作者：min_inf (赞：9)

场上思路，好像没人写。

题目显然提示了复杂度里有个 $2^k$。考虑把一条路径拆成 $u\to\operatorname{lca}(u,v)$ 和 $v\to\operatorname{lca}(u,v)$ 两部分，$O(2^k)$ 枚举用哪部分，这样我们只需要考虑路径是祖孙链的情况。

按 $\operatorname{lca}(u,v)$ 深度从大到小考虑每条路径，对于一条路径如果当前没有染色就把最上面那条边染色，由于其他路径也都是祖孙链所以染最上面一定能覆盖到最多的路径。

染色就是一个单点加路径和，可以转化为子树加单点查，树状数组维护。

$O((n+2^kk)\log n)$。[code](https://codeforces.com/contest/1929/submission/246551195)


---

## 作者：ATZdhjeb (赞：9)

### 题目大意

给定一棵 $n$ 个点的树，再给定树上的 $k$ 条链，求最少标记多少条边，使得每一条给定链上均有至少一条边被标记。多测。

数据范围：

$1\le T \le 10^4$。

$2\le \sum n\le 10^5$。

$1\le \sum 2^k\le 2^{20}$。

### 简要分析

首先，数据范围明示状压。

一个比较显然的想法是预处理出每一条边能贡献哪些链，然后注意到答案的上界是 $O(k)$ 的，所以每轮找出能贡献新链最多的一条边选上，进行一个贪心。当然，这样是错的，hack 数据放在最后。

那么一个更正确的做法是考虑 DP，令 $f_S$ 代表标记集合 $S$ 中的链的最小代价，然后拿每一条边都去更新一下，也就是 $f_{S\cup s_{i}} \gets \min\{f_{S\cup s_{i}},f_{S}+1\}$，其中 $s_i$ 是第 $i$ 条边能贡献的链的集合。这样直接做是 $O(2^kn)$ 的。

考虑优化上述做法。直觉上我们知道，可能有一些边对应的 $s_i$ 是一样的，这样的边可以优化掉。进一步地，考虑这 $k$ 条链的端点所构成的虚树，我们知道虚树的每一条边一定对应原树的一条链（不一定是给出的），且这条链上的所有边的 $s_i$ 都是相同的。因为如果一条给定的链经过了这条链上的某一些边而不经过其它的，那么就意味着它从链的中间“拐弯离开”或“结束”了，而在这两种情况中都应该在虚树上新建一个点，将这些边在虚树上分为两条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/af8t8ijc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~图是手画的，可能有点草率。~~

~~蓝点和最上面红点之间也有一段红边的，但是被覆盖了。~~

如上图，如果虚树上红边对应的 $s_i$ 不尽相同，那么必然有一条题目给定的链是如绿链那样的；但是在这种情况下，虚树中应该还有一个蓝点，这样那些 $s_i$ 不同的边就不会对应到虚树上的一条红边，而是一段红边和一段绿边。

我们知道虚树的大小是 $O(k)$ 的，因此虚树上的边数是 $O(k)$ 的，因此最多有 $O(k)$ 种互不相等的 $s_i$。我们只用这些不同的边去更新 DP 数组就可以了。时间复杂度 $O(2^kk)$，可以通过本题。

### 代码实现

注意写的时候并不用真的把虚树建出来，只需要对 $s_i$ 去重就可以了。

针对上文错误贪心的 hack 数据在代码最后的注释里。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pii pair<int,int>
#define cpx complex<double>
#define INF 0x3f3f3f3f
#define mod 998244353
#define rep(i,a,b) for (int (i) = (a); (i) <= (b); ++(i))
#define per(i,a,b) for (int (i) = (a); (i) >= (b); --(i))

using namespace std;

inline int input() {
	int x = 0,f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

inline char get() {
	char c = getchar();
	while (isspace(c)) c = getchar();
	return c;
}

const double PI = acos(-1);

int T,n,k,a[100010],dep[100010],fa[100010],dp[1000010];
vector<int> e[100010];

void DFS1(int u,int p) {
	fa[u] = p;
	dep[u] = dep[p] + 1;
	for (int i : e[u]) if (i != p) DFS1(i,u);
}

void modify(int u,int v,int k) {
	if (dep[u] < dep[v]) swap(u,v);
	while (dep[u] != dep[v]) {
		a[u] |= (1 << k);
		u = fa[u];
	}
	if (u == v) return;
	while (u != v) {
		a[u] |= (1 << k);
		a[v] |= (1 << k);
		u = fa[u];
		v = fa[v];
	}
}

void solve() {
	n = input();
	rep (i,1,n) a[i] = 0;
	rep (i,1,n) e[i] = vector<int>();
	rep (i,1,n - 1) {
		int u = input(),v = input();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	DFS1(1,0);
	k = input();
	rep (i,1,k) {
		int u = input(),v = input();
		modify(u,v,i - 1);
	}
	rep (i,1,(1 << k) - 1) dp[i] = INF;
	sort(a + 2,a + n + 1);
	int N = unique(a + 2,a + n + 1) - a - 1;
	rep (i,2,N) rep (j,0,(1 << k) - 1) dp[j | a[i]] = min(dp[j | a[i]],dp[j] + 1);
	printf("%d\n",dp[(1 << k) - 1]);
}

int main() {
	T = input();
	while (T--) solve();
	return 0;
}

/*
1
8
2 1
3 1
4 3
5 2
6 2
7 3
8 1
5
1 8
4 6
7 1
8 2
6 3
*/
```

---

## 作者：苏联小渣 (赞：2)

其实是简单题，感觉没做出来主要原因是少了一个小观察。

首先我们可以对于每条边，求出有哪些路径经过了这条边，然后把它状压起来，这部分容易实现，时间复杂度 $O(nk)$。

然后我们现在有若干个**本质不同**的状态，问题转化为，选出最少本质不同的状态，使得它们或起来等于全集。

容易有一个 dp：设 $f_S$ 表示到达 $S$ 的选的最少状态，转移的时候，对于所有本质不同的状态 $\{M\}$，有 $f_{S|M_i} = \min (f_{S|M_i},f_S+1)$。

然后可能会认为本质不同的状态是 $O(n)$ 的，于是就会以为这是个暴力导致没有写，但其实这是对的，本质不同的状态只有 $O(k)$ 个。

证明类似于虚树大小，由于是本质不同，只有在关键点才会产生，而关键点个数是 $O(k)$ 的，所以总时间复杂度 $O(nk+k2^k)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, m, p, x, y, h[100010], b[100010], f[2000010];
struct node{
	int x, y, id, next;
}d[200010];
void add(int x, int y, int id){
	d[++p].y = y, d[p].id = id, d[p].next = h[x], h[x] = p;
} 
vector <int> cun;
int dfs(int x, int fa, int lim, int ed){
	int ret = 0;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		int now = dfs(y, x, lim, ed);
		if (now) b[d[i].id] |= (1 << lim);
		ret |= now;
	}
	if (x == ed) ret = 1;
	return ret;
}
int main(){
	scanf ("%d", &t);
	while (t --){
		cun.clear();
		scanf ("%d", &n);
		p = 0;
		for (int i=1; i<=n; i++) h[i] = b[i] = 0;
		for (int i=1; i<n; i++){
			scanf ("%d%d", &x, &y);
			add(x, y, i); add(y, x, i);
		}
		scanf ("%d", &m);
		for (int i=0; i<(1<<m); i++){
			f[i] = 1e9;
		}
		for (int i=1; i<=m; i++){
			scanf ("%d%d", &x, &y);
			int tmp = dfs(x, 0, i-1, y);
		}
		for (int i=1; i<n; i++){
			if (b[i]) f[b[i]] = 1;
		}
		for (int i=1; i<(1<<m); i++){
			if (f[i] == 1) cun.push_back(i);
		}
		for (int i=1; i<(1<<m); i++){
			if (f[i] == 1e9) continue;
			for (int j=0; j<cun.size(); j++){
				int now = cun[j];
				f[i|cun[j]] = min(f[i|cun[j]], f[i] + 1);
			}
		}
		printf ("%d\n", f[(1<<m)-1]);
	} 
	return 0;
}

```

---

## 作者：251Sec (赞：2)

为啥这场 Div.2 的 EF 都这么弱智啊，有一种 Div.3 的感觉。

---

考虑一个暴力：预处理出每条边会被哪些路径覆盖，设这个东西为 $g(e)$，这个东西容易用树上差分预处理。然后直接 DP：设 $f(S)$ 代表集合 $S$ 里的路径上都有至少一条边的最小代价。转移枚举一条树上的边 $e$，则 $f(S \cup g(e)) \gets \min(f(S \cup g(e)), f(S)+1)$。这个东西的复杂度是 $O(2^kn)$ 的。

考虑把所有 $g(e)$ 去重。注意到组成 $k$ 条路径的 $2k$ 个点的虚树大小是 $O(k)$ 的，所以去重后只有 $O(k)$ 个不同的 $g(e)$，运行刚刚那个暴力算法，复杂度 $O(2^kk+n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n, k;
struct Edge {
	int to, next;
} e[200005];
int head[100005], len;
int w[100005];
void Insert(int u, int v) {
	e[++len] = { v, head[u] };
	head[u] = len;
}
unordered_set<int> g;
int f[1100005];
void DFS(int u, int fa) {
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		DFS(v, u);
		g.insert(w[v]), w[u] ^= w[v];
	}
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1, u, v; i < n; i++) {
			scanf("%d%d", &u, &v);
			Insert(u, v), Insert(v, u);
		}
		scanf("%d", &k);
		for (int i = 0, u, v; i < k; i++) {
			scanf("%d%d", &u, &v);
			w[u] ^= (1 << i), w[v] ^= (1 << i);
		}
		DFS(1, 0);
		for (int i = 1; i < (1 << k); i++) f[i] = 1e9;
		for (int x : g) for (int i = 0; i < (1 << k); i++) f[i | x] = min(f[i | x], f[i] + 1);
		printf("%d\n", f[(1 << k) - 1]);
		g.clear();
		for (int i = 1; i <= n; i++) w[i] = head[i] = 0;
		len = 0;
	}
	return 0;
}
```

---

## 作者：Reunite (赞：1)

题意：在树上选择最少的关键点，使给定的 $k$ 条路径上都有关键点。

## 一
---

诈骗题，我被骗了好几分钟。

考虑状压，因为 $k \le 20$，我们可以暴力跳 $lca$，给每个点标记，这样我们可以 $O(kn)$ 预处理出 $fs_{u}$ 表示经过 $u$ 节点的路径状压集合。

考虑最朴素的暴力怎么做，我们设 $f_{s}$ 表示二进制状态为 $s$ 的那些路径已经合法的最少关键点，那么我们枚举每个点，有：

$$f_{s|fs_u}\leftarrow \min(f_{s|fs_u},f_s+1)$$

意义显然，但这样复杂度高达 $O(n2^k)$，直接上天了。注意到本质不同的 $fs_u$ 其实很少，一个的上界是 $4k-1$。所以我们对于每个不同的 $fs_u$ 做一遍就好了，复杂度降为 $O(k2^k)$。

稍微说明一下本质不同的数量，可以考虑虚树，$2k$ 的点构建出的虚树点数是最多是 $4k-1$ 的，而这显然包含了 $k$ 条路径的各种组合形式，所以复杂度是对的。

---
## 二
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int t,n,k;
int f[2002144];
int fs[100005];
int fa[100005];
int dep[100005];
bool mp[2000000];
vector <int> g[100005];

inline void in(int &n){
	n=0;
	char c=getchar();bool ok=c=='-';
	while(c<'0' || c>'9') c=getchar(),ok|=c=='-';
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	n=(ok?-n:n);
	return ;
}

inline void init(int u,int fath){
	dep[u]=dep[fath]+1;
	fa[u]=fath;
	for(int v:g[u]){
		if(v==fath) continue;
		init(v,u);
	}
	return ;
}

int main(){
	int t;
	in(t);
	while(t--){
		in(n);
		for(int i=1;i<=n;i++) g[i].clear(),fs[i]=0;
		for(int i=1;i<n;i++){
			int u,v;
			in(u),in(v);
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		init(1,0);
		in(k);
		for(int i=0;i<(1<<k);i++) f[i]=1e9,mp[i]=0;
		for(int i=1;i<=k;i++){
			int u,v;
			in(u),in(v);
			if(dep[u]<dep[v]) swap(u,v);
			while(dep[u]!=dep[v]) fs[u]|=(1<<(i-1)),u=fa[u];
			while(u!=v) fs[u]|=(1<<(i-1)),fs[v]|=(1<<(i-1)),u=fa[u],v=fa[v];
		}
		f[0]=0;
		for(int i=1;i<=n;i++){
			if(mp[fs[i]]) continue;
			mp[fs[i]]=1;
			for(int s=(1<<k)-1;~s;s--)
				f[fs[i]|s]=min(f[fs[i]|s],f[s]+1);
		}
		printf("%d\n",f[(1<<k)-1]);
	}

	return 0;
}
```

---

## 作者：wangzhiyuan123 (赞：1)

定义一条边能影响到一个点对为这条边在这对点之间的简单路径上。  
考虑设一条边能影响到的点对集合为 $s$，树上总共有多少种不同的 $s$。对于一条虚树上的边所包含的原树上的边显然 $s$ 相同。故 $s$ 不同的边数量不超过 $O(k)$。显然 $s$ 不同的边只需保留一条。  
直接状压跑背包即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int w=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) w=w*10+ch-'0',ch=getchar();
	return w;
}
int t,n,m;
vector<int> tr[100005];
int dep[100005],pa[100005];
int c[100005];
void dfs(int x,int fa){
	pa[x]=fa;
	dep[x]=dep[fa]+1;
	for(int i=0;i<tr[x].size();i++){
		int y=tr[x][i];
		if(y==fa) continue;
		dfs(y,x);
	}
}
void color(int u,int v,int id){
	while(u!=v){
		if(dep[u]<dep[v]) swap(u,v);
		c[u]|=(1<<id);
		u=pa[u];
	}
}
int dp[2000005],vis[2000005];
void solve(int val){
	for(int i=0;i<(1<<m);i++) dp[i|val]=min(dp[i|val],dp[i]+1);
}
main(){
	t=read();vis[0]=1;
	while(t--){
		n=read();
		for(int i=1;i<=n;i++) tr[i].clear(),c[i]=0;
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			tr[u].push_back(v);
			tr[v].push_back(u);
		}
		dfs(1,0);
		m=read();
		for(int i=1;i<(1<<m);i++) dp[i]=m+1,vis[i]=0;
		dp[0]=0;
		for(int i=0;i<m;i++){
			int u=read(),v=read();
			color(u,v,i);
		}
		for(int i=2;i<=n;i++){
			if(!vis[c[i]]){
				vis[c[i]]=1;
				solve(c[i]);
			}
		}
		printf("%d\n",dp[(1<<m)-1]);
	}
}
```


---

## 作者：DegChuZm (赞：0)

### 鲜花
此题就是 [ABC125F](https://atcoder.jp/contests/abc152/tasks/abc152_f) 的加强版，改改转移就过了。
### sol
直接状压。

设 $dp_i$ 表示满足限制为 $i$ 的最小代价。

然后依次考虑每条边涂黑会影响到哪些限制，这个可以直接 $O(n)$ 去找。

然后把涂黑第 $i$ 条边可以满足的限制记录为 $vis_i$。

然后直接开始枚举第 $i$ 条边和状态，$dp_{j|vis_i}=min\{dp_{j|vis_i},dp_j+1\}$

时间复杂度 $O(n \cdot 2^m)$，于是 T 飞了。

怎么优化呢？

因为这是一颗可爱的树，所以一条边的影响很有可能与其他的边的影响重复。

搞个 `unique` 去重就行了。

可以证明去重完后的状态数是 $O(k)$ 级的。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt=1,head[200001],ans,f[100001],dep[100010],yx[100001],m,o,x,y,z,vis[100001],dp[1<<20],t;
struct dcz{
	int to,nex,val;
}a[200001];
void add(int x,int y){
	a[++cnt].nex=head[x];
	a[cnt].to=y;
	head[x]=cnt;
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u]=fa;
	for(int i=head[u];i;i=a[i].nex){
		int v=a[i].to;
		if(v!=fa) dfs(v,u);
		yx[v]=i/2;
	}
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) head[i]=0;
		cnt=1;
		for(int i=1;i<n;i++){
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		for(int i=1;i<=n;i++) yx[i]=0,vis[i]=0,dep[i]=0,f[i]=0;
		dfs(1,0);
		cin>>m;
		for(int i=0;i<(1<<m);i++) dp[i]=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=m;i++){
			cin>>x>>y;
			if(dep[x]<dep[y]) swap(x,y);
			while(dep[x]>dep[y]){
				vis[yx[x]]|=(1<<(i-1));
				x=f[x];
			}
			while(x!=y){
				vis[yx[x]]|=(1<<(i-1));
				vis[yx[y]]|=(1<<(i-1));
				x=f[x];
				y=f[y];
			}
		}
		dp[0]=0;
		sort(vis+1,vis+n);
		n=unique(vis+1,vis+n)-vis;
		for(int i=1;i<n;i++){
			for(int j=(1<<m)-1;j>=0;j--){
				if((j|vis[i])!=j) dp[j|vis[i]]=min(dp[j|vis[i]],dp[j]+1);
			}
		}
		cout<<dp[(1<<m)-1]<<endl;
	}
}
```

---

## 作者：huangrenheluogu (赞：0)

第一次用专栏写题解，感觉和博客可能差不多。

### 算法一

看到 $k\le 20$ 直接状压，可以 $O(nk)$ 或者 $O(n)$ 的复杂度做出每个点被那些路径覆盖。

此时转化成背包问题，如果直接把不同的物品拿过来 dp，预计复杂度 $O(2^{2k})$，但是通过了。于是，赛时部分结束了。

最后可以思考一下为什么边的种类是 $O(k)$。我们可以把 $k$ 条路径看成 $2k$ 个点构成的虚树，这样容易得到不同种类的边是 $O(k)$ 的。

### 算法二

考虑到 CF 比赛的时候没有打“部分分”的能力，因此这里提供我赛时的想法，很遗憾，需要赛后的点播。

感谢 [yangjl](https://codeforces.com/profile/yangjl) 大佬。

考虑获得了每一条边的贡献，发现是背包的合并问题。我们记 $f_i(x)$ 表示至少选择了 $i$ 条边 $x$ 的状态是否可达。

转移方程式式简单的。记 $f_1(x)=g(x)$。

$$f_i(x)=\sum\limits_{y|z=x}f_{i-1}(y)\cdot g(z)$$

用一下 FWT 就可以做到 $O(2^kk)$ 求。

发现 $i$ 上界是 $k$，因此可以 $O(k2^k\log 2^k)=O(k^22^k)$ 去做。

但是这仍然是 TLE 的。考虑优化，进行 FWT 操作之后不用进行 IFWT，我们只需要知道 $f_{i}(2^k-1)$ 的值，而不是 $f_i(x)$ 对于 $\forall x\in[0,2^k-1]$ 的所有值，因此在求的时候顺便处理一下就好了。

复杂度 $O(2^kk)$。

---

## 作者：TLE_Automat (赞：0)

## 题目链接

[https://codeforces.com/contest/1929/problem/E](https://codeforces.com/contest/1929/problem/E)

## 题目大意

给定一颗 $n$ 个结点的树，给定 $k$ 条树上的路径 $a_i, b_i$。现在要对树上的一些边染色，使得 $k$ 条路径中的每一条路径上都至少有一条边被染色，问最少染多少条边。

## 数据范围

- $2\le n \le 10^{5}$
- $1 \le k \le 20$

## 解题思路

考虑统计每一条边被那些路径覆盖，假设覆盖第 $i$ 边的路径集合为 $S_i$，那就是要找到一个长度最短的序列 $p_1, p_2, \cdots, p_m$ 使得 $S_{P_1} \cup S_{p_2} \cup \cdots \cup S_{p_m} = \{1, 2, \cdots, k\}$。

我们联想到了状压 dp，但发现直接 dp 复杂度是 $O(n\cdot 2^{k})$，是行不通的。

因为路径条数非常少，我们可以猜测本质不同的集合 $S_i$ 的个数跟 $k$ 是一个级别的。

证明可以考虑建出这 $2k$ 个点的虚树，由于虚树上最多只有 $4k - 1$ 个结点，$4k - 2$ 条边，所以最多只有 $4k - 2$ 种本质不同的 $S_i$​。 

有了上面的结论我们就可以直接 $O(2^{k}k)$ 地 dp 了。

## 参考代码

[https://codeforces.com/contest/1929/submission/246624331](https://codeforces.com/contest/1929/submission/246624331)

---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/260/)

# 前言

如何评价我场上 LCA 没清空 fa 数组没有 AK。

# 题目翻译

给定 $n$ 个点的一棵树，以及 $k$ 组点 $(u,v)$，表示 $u\to v$ 的简单路径包含特殊边。问至少多少边为特殊边。

多测，$1\leq t\leq 10^4,\sum n\leq10^5,\sum 2^k\leq 2^{20}$。

# 题目思路

$k$ 很小，考虑状压。$S_i$ 为一个 mask 表示第 $i$ 条边可能出现哪几条特殊边，也就是被哪几个路径包含。

设计 dp 状态 $f_{mask}$ 表示『包含集合 $mask$ 至少需要多少条边』。

直接转移是 $\mathcal O(2^k\times n)$ 的，无法通过。

发现 $k$ 条边至多 $2k$ 个点，直接建虚树大小为 $\mathcal O(k)$。~~所以我们建立虚树转移 dp。~~

我们直接对于 $S_i$ 进行去重，得到的集合大小只有 $\mathcal O(k)$ 了。现在复杂度为 $\mathcal O(2^k\times k)$，可以通过。

状压部分的染色，$u\to v$ 的简单路径就是 $u\to \operatorname{lca}(u,v)$ 加上 $v\to \operatorname{lca}(u,v)$，因此暴力跳 $fa$ 数组即可。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
typedef pair<int, int> pii;
pii E[100020];
int n, m;
vector<int> a[100020];
int dep[100020];
int fa[100020][20];
int S[100020]; // mask
int f[1 << 20];
map<pii, int> mp;
void dfs(int u, int p)
{
    dep[u] = dep[p] + 1;
    fa[u][0] = p;
    for (int i = 1; 1 << i <= dep[u]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v : a[u])
        if (v ^ p)
            dfs(v, u);
}
int LCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[x][i] ^ fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
void solve()
{
    read(n);
    for (int i = 1; i <= n; i++)
    {
        a[i].clear(), S[i] = dep[i] = 0;
        for (int j = 0; j < 20; j++)
            fa[i][j] = 0;
    }

    mp.clear();
    for (int i = 1; i < n; i++)
    {
        int u, v;
        read(u, v);
        E[i] = {u, v};
        a[u].push_back(v);
        a[v].push_back(u);
        mp[{u, v}] = mp[{v, u}] = i;
    }
    dfs(1, 0);
    read(m);
    for (int i = 0; i < m; i++)
    {
        int cnt = 1 << i;
        int u, v;
        read(u, v);
        int lca = LCA(u, v);
        for (int j = u; j != lca; j = fa[j][0])
            S[mp[{j, fa[j][0]}]] |= cnt;
        for (int j = v; j != lca; j = fa[j][0])
            S[mp[{j, fa[j][0]}]] |= cnt;
    }
    for (int i = 0; i < 1 << m; i++)
        f[i] = inf;
    set<int> s;
    for (int i = 1; i < n; i++)
        s.insert(S[i]);
    for (int i : s)
        f[i] = 1;
    // for (int i : s)
    //     cout << i << " ";
    // cout << endl;
    f[0] = 0;
    for (int i = 0; i < 1 << m; i++)
        for (int j : s)
            chkmn(f[i | j], f[i] + 1);
    cout << f[(1 << m) - 1] << '\n';
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1929E)

场上用时比 C 题还短，怎么回事呢。

注意到 $k\le 20$ 且允许带有 $2^k$ 的复杂度，这个条件一定非常关键。

考虑状压，令 $dp[S]$ 表示集合 $S$ 内的路径已经满足条件的最少边数，转移考虑去枚举下次染哪一条边。令 $mask_i$ 表示覆盖了第 $i$ 条边的路径集合，转移有

$$
dp[S]+1\to dp[S\cup mask_i]
$$

其中 $mask_i$ 可以 $O(nk)$ 暴力预处理出来。树上有 $n$ 条边，所以时间复杂度为 $O(n2^k)$，过不去。

但同样由于 $k\le 20$，不同的 $mask_i$ 种类并不会太多，也就是本质不同的边其实是很少的，直接将所有的 $mask_i$ 拉出来去重，然后再重新做 dp 即可。

事实上不同 $mask_i$ 的种类是 $O(k)$ 的，证明考虑将 $k$ 对点设为关键点并建出虚树，那么本质不同的边数其实就是虚树上的边数，显然为 $O(k)$。

因此本题复杂度为 $O(nk+k2^k)$。



```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e6 + 5;
int n, k, fa[N], dep[N], sta[N], dp[N];
int tot, buc[N];
vector<int> G[N];
void dfs(int now, int pa){
	dep[now] = dep[pa] + 1;
	fa[now] = pa;
	for(int to : G[now]){
		if(to == pa) continue;
		dfs(to, now);
	}
}
void Col(int x, int y, int id){
	while(true){
		if(dep[x] < dep[y]) swap(x, y);
		sta[x] |= 1 << (id - 1);
		x = fa[x];
		if(x == y) break;
	}
}
void Solve(){
	cin >> n;
	For(i, 1, n - 1){
		int u, v; cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	cin >> k;
	For(i, 1, k){
		int x, y; cin >> x >> y;
		Col(x, y, i);
	}
	tot = 0;
	For(i, 1, n) buc[++tot] = sta[i];
	sort(buc + 1, buc + tot + 1);
	tot = unique(buc + 1, buc + tot + 1) - buc - 1;
	For(i, 0, (1 << k) - 1) dp[i] = 1e9;
	dp[0] = 0;
	For(S, 0, (1 << k) - 1) For(i, 1, tot){
		int T = S | buc[i];
		dp[T] = min(dp[T], dp[S] + 1);
	}
	cout << dp[(1 << k) - 1] << '\n';
	For(i, 1, n) G[i].clear(), fa[i] = dep[i] = sta[i] = 0; 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：Xy_top (赞：0)

看到 $k\leq 20$ 能够想到状压，进一步地分析。我们设 $f_{s}$ 为每条路径有没有经过选的点的状态为 $s$ 时，所需选的最少的点的数量。初始时先 $O(n\times k)$ 预处理出选每条边能够使哪些路径经过（也是一个 $01$ 状态），然后可以作一个 $O(n\times 2^k)$ 的类似背包的东西就结束了。

但是这样会超时，考虑每条边的 $01$ 状态本质不同的数量，显然不会超过 $2\times k$。

于是去重后能优化到 $O(n\times k + k\times 2^k)$，可以通过。

[提交记录](https://codeforces.com/contest/1929/submission/246738250)

---

## 作者：MaxBlazeResFire (赞：0)

因为这场的 $\rm F$ 让我很生气，于是就来写一篇 $\rm E$ 的题解。

首先 $O(nk)$ 遍历所有路径，求出每条边 $e$ 能够覆盖的点对集合 $g_e$；问题转化为选出若干集合，使得其并为全集。

这个问题除了 $O(3^k)$ 做法之外只有 $O(N2^k)$ 的状压 $\rm DP$ 做法，其中 $N$ 为集合个数。前者肯定不能用，考虑后者，我们发现如果把 $2k$ 个点拿出来建虚树，那么虚树上的任意一条边上的所有原树边的代表集合相同；又注意到虚树的总边数为 $O(k)$，于是所有边的本质不同的 $g_e$ 只有 $O(k)$ 种，直接状压 $\rm DP$ 即可。

复杂度 $O(nk+k2^k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100005
#define MBIT 20

const int INF = 1000000000;

int n,k,w[MAXN],f[MAXN],h[MAXN],vis[MAXN];
int c[1 << MBIT],g[1 << MBIT];
//g[S] 表示使得得到集合 S 所需的最小边数
vector< pair<int,int> > E[MAXN];

void dfs( int x , int fa ){
	for( pair<int,int> p : E[x] ){
		int v = p.first,i = p.second;
		if( v == fa ) continue;
		f[v] = x,w[v] = i,dfs( v , x );
	}
}

inline void chkmin( int &x , int k ){ x = min( x , k ); }

inline void solve(){
	scanf("%lld",&n);
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%lld%lld",&u,&v);
		E[u].emplace_back( make_pair( v , i ) );
		E[v].emplace_back( make_pair( u , i ) );
	}
	dfs( 1 , 0 );
	scanf("%lld",&k);
	for( int i = 1 ; i <= k ; i ++ ){
		int u,v; scanf("%lld%lld",&u,&v);
		int tmp = u;
		while( tmp ) vis[tmp] = 1,tmp = f[tmp];
		tmp = v;
		while( !vis[tmp] ) vis[tmp] = 1,tmp = f[tmp];
		while( vis[tmp] ) vis[tmp] = 0,tmp = f[tmp];
		for( int j = 1 ; j <= n ; j ++ ) if( vis[j] ) h[w[j]] |= 1 << ( i - 1 );
		tmp = u;
		while( vis[tmp] ) vis[tmp] = 0,tmp = f[tmp];
		tmp = v;
		while( vis[tmp] ) vis[tmp] = 0,tmp = f[tmp];
	}
	for( int i = 1 ; i < n ; i ++ ) c[h[i]] = 1;
	for( int S = ( 1 << k ) - 1 ; S >= 0 ; S -- )
		for( int i = 0 ; i < k ; i ++ ) if( S >> i & 1 ) c[S ^ ( 1 << i )] += c[S];
	vector<int> R;
	for( int S = 0 ; S < 1 << k ; S ++ ) if( c[S] == 1 ) R.emplace_back( S );
	int siz = R.size();
	for( int S = 0 ; S < 1 << k ; S ++ ) g[S] = INF;
	g[0] = 0;
	for( int i = 0 ; i < siz ; i ++ )
		for( int S = ( 1 << k ) - 1 ; S >= 0 ; S -- ) chkmin( g[S | R[i]] , g[S] + 1 );
	printf("%lld\n",g[( 1 << k ) - 1]);
	for( int S = 0 ; S < 1 << k ; S ++ ) c[S] = g[S] = 0;
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear(),f[i] = h[i] = w[i] = 0;
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

