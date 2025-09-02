# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

A hero $ k $ times do the following operation:

- Choose some edge.
- Remove it.
- Take one of the two remaining parts and delete it.
- Write the number of vertices in the remaining part.

You are given an initial tree and the a sequence of written numbers. Find the number of ways to make operations such that the written numbers are equal to the given numbers. Due to the answer can be big, find it by modulo $ 998\,244\,353 $ . Two ways are considered different, if on some operation edge or remaining part are selected differently.

## 说明/提示

In the first test there are four possible ways to make operations:

- Remove the edge $ (1, 2) $ and delete vertex $ 1 $ . Remove the edge $ (2, 3) $ and delete vertex $ 2 $ .
- Remove the edge $ (1, 2) $ and delete vertex $ 1 $ . Remove the edge $ (3, 2) $ and delete vertex $ 3 $ .
- Remove the edge $ (3, 2) $ and delete vertex $ 3 $ . Remove the edge $ (1, 2) $ and delete vertex $ 1 $ .
- Remove the edge $ (3, 2) $ and delete vertex $ 3 $ . Remove the edge $ (2, 1) $ and delete vertex $ 2 $ .

In the second test there are two possible ways to make operations:

- Remove the edge $ (4, 1) $ and delete the part with vertex $ 4 $ . Remove the edge $ (2, 3) $ and delete the part with vertex $ 2 $ .
- Remove the edge $ (4, 1) $ and delete the part with vertex $ 4 $ . Remove the edge $ (3, 2) $ and delete the part with vertex $ 3 $ .

## 样例 #1

### 输入

```
3
1 2
2 3
2
2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
7
2 1
3 2
4 1
5 3
6 4
7 4
2
4 2```

### 输出

```
2```

## 样例 #3

### 输入

```
7
1 2
1 3
1 4
2 5
3 6
4 7
1
2```

### 输出

```
3```

## 样例 #4

### 输入

```
7
1 2
1 3
1 4
2 5
3 6
4 7
4
6 5 2 1```

### 输出

```
24```

## 样例 #5

### 输入

```
8
1 2
2 3
3 4
3 5
3 6
3 7
3 8
2
7 4```

### 输出

```
0```

# 题解

## 作者：_Cheems (赞：3)

很好的树上计数题，想通了就好做。
### 题意
给定一棵有根树。可以按顺序切掉 $k$ 条边，并进入两个联通块中的一个。要求第 $i$ 次进入的连通块大小 $=a_i$，求合法方案数？

$k\le 6$。
### 思路
看到题面和数据范围，应该想到树形 $\rm dp$，并状压操作序列。

将操作分为：
1. 进入子树。
2. 进入非子树。

先关注操作 $\rm 2$。非子树部分的大小不好考虑，不妨转换为割掉的子树大小为 $b_i=a_{i-1}-a_i$。至此完成题目的初步转化。

然后思考其它限制。对操作序列（时间轴）进行讨论：
* 对于操作 $\rm1$：当 $i$ 次操作为进入子树 $v$ 时，则 $i+1...n$ 操作都必定在 $v$ 内进行。
* 对于操作 $\rm2$：没有太多限制，可以理解为删掉某个子树。只需满足大小限制即可。

不难发现操作 $\rm2$ 更好做，先考虑全是它的情况。

定义 $g_{u,i}$ 表示在 $u$ 子树内，操作集合为 $i$ 且只有操作 $\rm 2$ 时的方案数。

然后想想转移，若按朴素的树形 $\rm dp$ 做法，我们还需枚举 $u\to v_i$ 的所有边。于是有个小技巧，状态多考虑 $u\to fa$ 这条边。于是只需枚举子集转移，最后考虑这条边的贡献即可。 

然后是操作 $1$。定义 $f_{u,i,tim}$ 表示 $u$ 子树操作集合为 $i$，且最早的操作 $\rm1$ 在 $tim$ 时刻的方案数。与 $g$ 交替转移即可。

总结下 trick：
1. 看数据范围考虑算法。
2. 充分利用条件，转换限制使其相对宽松。
3. 有多个数组需转移时，优先考虑简单的。
4. 树形 $\rm dp$ 时可以多向上考虑一条边。

具体转移还有其它细节就放到代码里了，复杂度 $O(nk3^k)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define ADD(a, b) a = ((a) + (b)) % mod
const int N = 5e3 + 5, M = 1 << 6, mod = 998244353;
int n, k, u, v, a[N], b[N];
int siz[N], ned[M + 5], mb[M + 5], g[N][M + 5], f[N][M + 5][15], ans;
vector<int>to[N];
//ned:状态i全是操作2时，删去的点数
//mb:i的最高位 

inline void init(){
	for(int i = 0; i < M;++i){
		for(int j = 5; j >= 0;--j) if((i >> j) & 1) {mb[i] = j; break;}
		for(int j = 0; j < 6;++j) if((i >> j) & 1) ned[i] += b[j + 1];
	}
	mb[0] = -114; //特殊情况，否则下面转移会错，样例都过不了 
}
inline void dfs(int u, int fa){
	g[u][0] = siz[u] = 1;
	for(auto v : to[u]){
		if(v ^ fa){
			dfs(v, u), siz[u] += siz[v];
			for(int i = M - 1; i > 0;--i) //注意先转移f再g 
				for(int tim = 0; tim < k;++tim)
					if((i >> tim) & 1)
						for(int j = i; j > 0;j = (j - 1) & i){ 
							if(mb[j] < tim) //选子树操作不在v内 
								ADD(f[u][i][tim], f[u][i ^ j][tim] * g[v][j] % mod);
							if(((j >> tim) & 1) && mb[i ^ j] < tim) //相反情况 
								ADD(f[u][i][tim], g[u][i ^ j] * f[v][j][tim] % mod);
						} 
			for(int i = M - 1; i > 0;--i)
				for(int j = i; j > 0;j = (j - 1) & i)
					ADD(g[u][i], g[u][i ^ j] * g[v][j] % mod); 
		}
	}
	if(fa){ //考虑删去u -> fa这条边 
		for(int i = M - 1; i > 0;--i)
			for(int tim = 0; tim < k;++tim)
				if((i >> tim) & 1){
					int j = i ^ (1 << tim);
					//即tim前面必须都是操作2 
					if(a[tim + 1] == (siz[u] - ned[j & ((1 << tim) - 1)])){ 
						for(int p = tim + 1; p < k;++p)
							ADD(f[u][i][tim], f[u][j][p]); //其余操作1必须在tim后面 
						ADD(f[u][i][tim], g[u][j]); //没有其余操作1 
					}
				} 
		for(int i = M - 1; i > 0;--i) //注意时间顺序：应该先修剪子树，再把整个子树剪掉 
			if(b[mb[i] + 1] == siz[u] - ned[i ^ (1 << mb[i])])
				ADD(g[u][i], g[u][i ^ (1 << mb[i])]);
	}
}
signed main(){
	cin >> n;
	for(int i = 1; i < n;++i) scanf("%lld%lld", &u, &v), to[u].pb(v), to[v].pb(u);
	cin >> k; a[0] = n;
	for(int i = 1; i <= k;++i) scanf("%lld", &a[i]), b[i] = a[i - 1] - a[i];
	
	init(), dfs(1, 0);
	
	ans = g[1][(1 << k) - 1];
	for(int i = 0; i < k;++i) ADD(ans, f[1][(1 << k) - 1][i]);
	cout << ans;
	return 0;
}
```

---

## 作者：Leasier (赞：3)

设 $e_i$ 表示删掉的第 $i$ 条边，$V_i$ 表示删完前 $i$ 条边后的连通块点集为 $V_i$。

考虑钦定一个点 $R$ 在最终的连通块 $V_k$ 中。不妨以 $R$ 为根，则所有被砍掉的边满足：

- 若 $i \neq j$ 且 $e_i$ 为 $e_j$ 的“祖先”，则 $i > j$。

注意到 $k$ 很小，考虑状压 dp。设 $dp_{u, S}$ 表示 $u$ 子树内有编号在 $S$ 中的父向边被删掉的方案数。

转移：首先考虑子树内被删掉的边，其只需要满足 $\cup_{v \in son_u} S_v= S$ 且 $S_v$ 两两不交，方案数为 $\displaystyle\prod_{v \in son_u} dp_{v, S_v}$。

接下来考虑 $u, fa_u$ 这条父向边是否删除。对于一个 $S$，若删除则一定会删除 $\max(S)$。

此时我们还需要判断当前删除的连通块的大小是否满足要求：令 $\Delta_i = s_{i - 1} - s_i$，则满足条件当且仅当 $size_u = \displaystyle\sum_{i \in S} \Delta_i$。~~感觉是最困难的一步。~~

但是直接枚举 $u$ 把答案求和显然会算重。不过注意到对于一种合法方案，$\forall u \in V_k$ 它都会被统计到，于是我们把答案除以 $s_k$ 即可。

换根 dp 即可。时间复杂度为 $O(n 3^k)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef struct Node_tag {
	int n;
	int a[67];
	Node_tag(){
		memset(a, 0, sizeof(a));
	}
} Node;

const int mod = 998244353;
int diff[7], s[7], sum[67], size[5007];
Node dp1[5007], dp2[5007], pre[5007], dp3[5007], suf[5007];
vector<int> v[5007];

inline int highbit(int x){
	return 31 - __builtin_clz(x);
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

inline Node conv(Node &a, Node &b){
	Node ans;
	ans.n = a.n;
	for (int i = 0; i <= a.n; i++){
		for (int j = i; ; j = i & (j - 1)){
			add(ans.a[i], 1ll * a.a[j] * b.a[i ^ j] % mod);
			if (j == 0) break;
		}
	}
	return ans;
}

inline Node cut(Node a, int size){
	Node ans;
	ans.n = a.n;
	for (int i = 0; i <= a.n; i++){
		ans.a[i] = a.a[i];
		if (sum[i] == size) add(ans.a[i], a.a[i ^ (1 << highbit(i))]);
	}
	return ans;
}

void dfs1(int u, int father, int full){
	int sz = v[u].size();
	size[u] = 1;
	for (int i = 0; i < sz; i++){
		if (v[u][i] == father){
			sz--;
			v[u].erase(v[u].begin() + i);
			break;
		}
	}
	dp1[u].n = full;
	dp1[u].a[0] = 1;
	for (int i = 0; i < sz; i++){
		int x = v[u][i];
		dfs1(x, u, full);
		size[u] += size[x];
		dp1[u] = conv(dp1[u], dp1[x]);
	}
	dp1[u] = cut(dp1[u], size[u]);
}

void dfs2(int u, int n, int full){
	int sz = v[u].size();
	for (int i = 0; i < sz; i++){
		pre[i] = dp1[v[u][i]];
		if (i > 0) pre[i] = conv(pre[i], pre[i - 1]);
	}
	dp3[u] = dp2[u];
	if (sz > 0) dp3[u] = conv(dp3[u], pre[sz - 1]);
	for (int i = sz - 1; i >= 0; i--){
		suf[i] = dp1[v[u][i]];
		if (i + 1 < sz) suf[i] = conv(suf[i], suf[i + 1]);
	}
	for (int i = 0; i < sz; i++){
		int x = v[u][i];
		dp2[x] = dp2[u];
		if (i > 0) dp2[x] = conv(dp2[x], pre[i - 1]);
		if (i + 1 < sz) dp2[x] = conv(dp2[x], suf[i + 1]);
		dp2[x] = cut(dp2[x], n - size[x]);
	}
	for (int i = 0; i < sz; i++){
		dfs2(v[u][i], n, full);
	}
}

inline int quick_pow(int x, int p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, k, full, ans = 0;
	cin >> n;
	for (int i = 1; i < n; i++){
		int s, f;
		cin >> s >> f;
		v[s].push_back(f);
		v[f].push_back(s);
	}
	cin >> k;
	full = (1 << k) - 1;
	s[0] = n;
	for (int i = 1; i <= k; i++){
		cin >> s[i];
		diff[i] = s[i - 1] - s[i];
	}
	for (int i = 1; i <= full; i++){
		int high = highbit(i) + 1;
		sum[i] = sum[i ^ (1 << (high - 1))] + diff[high];
	}
	dfs1(1, 0, full);
	dp2[1].n = full;
	dp2[1].a[0] = 1;
	dfs2(1, n, full);
	for (int i = 1; i <= n; i++){
		add(ans, dp3[i].a[full]);
	}
	cout << 1ll * ans * quick_pow(s[k], mod - 2) % mod;
	return 0;
}
```

---

## 作者：Nesraychan (赞：3)

## $\texttt{Description}$

给你一个有 $n$ 个点的树和一个长度为 $k$ 的序列 $s_i$，你要执行以下操作 $k$ 次：

- 选出目前存在的一条边。

- 删除这条边。

- 选出分裂出的两个联通块的其中一块。

- 删除这个联通块，并写下剩余的联通块的大小。

问有多少种不同的操作方案使得写下的序列等于给出的序列，答案对 $998244353$ 取模。

$n\le 5000,k\le 6$。

## $\texttt{Solution}$

没看懂官方题解在说什么，于是自己搞了一个做法，复杂度比标算劣一些。

考虑操作 $u$ 到其父亲的边，一种可能是保留以 $u$ 为根的子树，一种可能是删除以 $u$ 为根的子树。如果是后者，将符合题意的条件从保留的联通块大小为 $s_i$，改成删去大小为 $s_{i-1}-s_i$ 的联通块，容易发现这是等价的。

这样转化的好处是，每次操作都是对一个子树操作，方便树形 dp。

状压，记 $f(u,i,s)$  表示以 $u$ 为根的子树，子树内最早的保留子树操作是 $i$（如果不存在，则认为 $i=k+1$），操作的是以 $u$ 为根的子树的子树的集合为 $s$。

合并两个子树的时候，要求至多有一个子树满足 $i\le k$，且两个子树的集合 $s1,s2$ 满足 $s1\cap s2=\emptyset$。

在合并完所有儿子后，再考虑操作 $u$ 的子树，枚举对应的操作 $j$。

如果这是一个保留子树的操作，则要求 $i>j$；如果是一个删除子树的操作，则要求 $j>\forall l\in s$。同时，可以简单计算出操作 $j$ 之前 $u$ 的子树大小，从而判断出是否满足条件。

时间复杂度 $O(n(k3^k+k^22^k))$，可以通过高维前缀和优化到 $O(nk^22^k)$，但是没有必要。

## $\texttt{Code}$

需要注意的是，代码中的 $s_i$ 是从 $0$ 开始编号的，所以上述的值部分要减一。

```cpp
#include<bits/stdc++.h>
#define IL inline
#define reg register
#define N 5050
#define mod 998244353
IL int read()
{
	reg int x=0; reg char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}

IL int Add(reg int x,reg int y){return x+y<mod?x+y:x+y-mod;}
IL void Pls(reg int &x,reg int y){x=Add(x,y);}
IL int Mul(reg int x,reg int y){reg long long r=1ll*x*y; return r<mod?r:r%mod;}

int n,k,c[7],d[7];
std::vector<int>G[N];

IL void add(reg int u,reg int v){G[u].push_back(v),G[v].push_back(u);}

int full,f[N][7][1<<6|5],high[1<<6|5],sum[1<<6|5],sz[N],ans;

void dfs(reg int u,reg int fa=0)
{
	sz[u]=1;
	for(reg auto v:G[u])if(v!=fa)dfs(v,u),sz[u]+=sz[v];
	static int g[7][1<<6|5]; f[u][k][0]=1;
	for(reg auto v:G[u])if(v!=fa)
	{
		for(reg int j=0,s;j<=k;++j)for(s=0;s<=full;++s)g[j][s]=0;
		for(reg int s1=0,s2,s;s1<=full;++s1)for(s=s1;s<=full;s=(s+1)|s1)
			s2=s^s1,Pls(g[k][s],Mul(f[u][k][s1],f[v][k][s2]));
		for(reg int j=k,s1,s2,s;j--;)for(s1=0;s1<=full;++s1)if(f[u][j][s1]||f[v][j][s1])for(s=s1;s<=full;s=(s+1)|s1)
		{
			if(high[s2=s^s1]>j)continue;
			Pls(g[j][s],Mul(f[u][j][s1],f[v][k][s2])),Pls(g[j][s],Mul(f[v][j][s1],f[u][k][s2]));
		}
		for(reg int j=0,s;j<=k;++j)for(s=0;s<=full;++s)f[u][j][s]=g[j][s];
	}
	if(u==1)return;
	for(reg int j=0,s;j<=k;++j)for(s=0;s<=full;++s)g[j][s]=0;
	for(reg int j=0,l,s,S,x;j<=k;++j)for(s=0;s<=full;++s)if(f[u][j][s])for(l=0;l<j;++l)if(~s>>l&1)
	{
		S=s&(1<<l)-1,x=sz[u]-sum[S];
		if(x==c[l])Pls(g[l][s^(1<<l)],f[u][j][s]);
		if(x==d[l]&&l>high[s])Pls(g[j][s^(1<<l)],f[u][j][s]);
	}
	for(reg int j=0,s;j<=k;++j)for(s=0;s<=full;++s)Pls(f[u][j][s],g[j][s]);
}

main()
{
	n=read();
	for(reg int i=n;--i;add(read(),read()));
	k=read(),full=(1<<k)-1;
	for(reg int i=0;i<k;++i)c[i]=read(),d[i]=i?c[i-1]-c[i]:n-c[i];
	high[0]=-1;
	for(reg int s=0,i;s<=full;++s)for(i=0;i<k;++i)if(s>>i&1)high[s]=i;
	for(reg int s=1;s<=full;++s)sum[s]=sum[s^(1<<high[s])]+d[high[s]];
	dfs(1);
	for(reg int i=0;i<=k;++i)Pls(ans,f[1][i][full]);
	printf("%d\n",ans);
}
```

---

## 作者：IdnadRev (赞：2)

令 $f_i$ 表示 $i$ 在树上最后一个连通块的方案数，只需算出 $f$ 就能得知答案（$ans=\frac{\sum f_i}{s_k}$）。

$f$ 的计算可以考虑合并子树内外信息，使用换根 dp 计算出每个子树 / 子树补使用了某个操作集合的方案数，转移可以 $O(3^k)$ 暴力做。

复杂度 $O(n3^k)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5005,maxk=1<<6,mod=998244353;
int n,m,S,ans;
int inv[maxn],sum[maxk];
vector<int>v[maxn];
struct info {
	int sz;
	int a[maxk];
	inline int& operator[](int x) {
		return a[x];
	}
	info() {
		sz=0,memset(a,0,sizeof(a)),a[0]=1;
	}
} f[maxn],g[maxn],pre[maxn],suf[maxn];
info operator +(info a,info b) {
	info c;
	c[0]=0,c.sz=a.sz+b.sz;
	for(int i=0; i<S; i++)
		for(int j=i;; j=(j-1)&i) {
			c[i]=(c[i]+1ll*a[j]*b[i^j])%mod;
			if(j==0)
				break;
		}
	return c;
}
info fmt(info x) {
	for(int i=1; i<S; i++)
		if(sum[i]==x.sz)
			x[i]=(x[i]+x[i^(i&-i)])%mod;
	return x;
}
void dfs1(int x,int last) {
	f[x].sz=1;
	for(int i=0; i<v[x].size(); i++)
		if(v[x][i]!=last)
			dfs1(v[x][i],x),f[x]=f[x]+f[v[x][i]];
	f[x]=fmt(f[x]);
}
void dfs2(int x,int last) {
	vector<int>s;
	for(int i=0; i<v[x].size(); i++)
		if(v[x][i]!=last)
			s.emplace_back(v[x][i]),pre[s.size()]=pre[s.size()-1]+f[v[x][i]];
	suf[s.size()+1]=g[x],suf[s.size()+1].sz++;
	for(int i=s.size(); i>=1; i--)
		suf[i]=suf[i+1]+f[s[i-1]];
	ans=(ans+suf[1][S-1])%mod;
	for(int i=1; i<=s.size(); i++)
		g[s[i-1]]=fmt(pre[i-1]+suf[i+1]);
	for(int i=0; i<s.size(); i++)
		dfs2(s[i],x);
}
int main() {
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2; i<=n; i++)
		inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
	for(int i=1,x,y; i<n; i++)
		scanf("%d%d",&x,&y),v[x].emplace_back(y),v[y].emplace_back(x);
	scanf("%d",&m),S=1<<m;
	int lst=n;
	for(int i=1,x; i<=m; i++)
		scanf("%d",&x),sum[1<<(m-i)]=lst-x,lst=x;
	for(int i=1; i<S; i++)
		sum[i]=sum[i^(i&-i)]+sum[i&-i];
	dfs1(1,0),dfs2(1,0),printf("%d\n",(int)(1ll*ans*inv[lst]%mod));
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

思考的时候一直卡在不会在低于 $O(n)$ 的时间内储存一个连通块的 $siz$ 有关的信息，看了洛谷题解之后才发现我真是个小丑。

树形 DP。对于一条我们需要操作的边 $(i,fa_i)$，我们将其分为保留子树和删除子树两种类型，对于删除子树，我们在判定其是否合法时候改为判定删除的连通块大小是否为 $s_{k-1}-s_k$，好处是我们只用关心子树内那一部分的 $siz$。

这样考虑 DP，$dp_{u,S,k}$ 表示考虑 $u$ 子树，有且仅有 $S$ 操作集合中的操作对应的 $i$ 在 $u$ 子树内，且这些操作中最早的保留子树操作是 $k$ 的方案数（不存在则 $k=c+1$）。考虑转移，先考虑怎么合并两个子树 $u,v$，假设要合并 $dp_{u,S,k_1}$ 和 $dp_{v,T,k_2}$，那么可以合并的充要条件是：

- $S\cap T=\varnothing$。
- $k_1=c+1$ 或 $k_2=c+1$
- 假设 $k_1\ne c+1$，那么 $T$ 中所有元素必须 $<k_1$。

然后考虑加入 $(u,fa_u)$ 边的方案数，我们枚举这条边对应的操作 $i$，那么：

- 如果这个操作是删除子树，那么要求 $S$ 中所有元素都 $<i$，并且当中没有任何一个元素是保留子树的操作。
- 如果这个操作是保留子树，那么要求其他操作中最早的保留子树的操作的时间 $>i$。

最后考虑怎么计算保留/删除的连通块的大小，其实是 trivial 的，因为两种情况都保证了我们在 $i$ 之前的所有操作都是删除子树的操作，所以就直接拿 $siz_u$ 减去 $S$ 中所有 $<i$ 的元素的 $s_{j-1}-s_j$ 即可。不需要额外记录 $O(n)$ 的一维。

```cpp
const int MAXN=5000;
const int MAXK=6;
const int MAXP=64;
const int MOD=998244353;
int n,k,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec,s[MAXK+3];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int dp[MAXN+5][MAXK+3][MAXP+5],siz[MAXN+5],mx[MAXP+5];
void dfs(int x,int f){
	dp[x][k+1][0]=1;siz[x]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f)continue;dfs(y,x);siz[x]+=siz[y];
		static int tmp[MAXK+3][MAXP+5];memset(tmp,0,sizeof(tmp));
		for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++){
			int rst=(1<<k)-1-S;
			for(int T=rst;;--T&=rst){
				if(mx[T]<=i)tmp[i][S|T]=(tmp[i][S|T]+1ll*dp[x][i][S]*dp[y][k+1][T])%MOD;
				if(i!=k+1&&mx[S]<=i)tmp[i][S|T]=(tmp[i][S|T]+1ll*dp[x][k+1][S]*dp[y][i][T])%MOD;
				if(!T)break;
			}
		}
		for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++)dp[x][i][S]=tmp[i][S];
	}
	if(x!=1){
		static int tmp[MAXK+3][MAXP+5];
		for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++)tmp[i][S]=dp[x][i][S];
		for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++)if(dp[x][i][S]){
			for(int j=1;j<i;j++)if(~S>>(j-1)&1){
				int sumsiz=siz[x];bool flg=1;
				for(int l=1;l<j;l++)if(S>>(l-1)&1)sumsiz-=(s[l-1]-s[l]);
				if(sumsiz==s[j])tmp[j][S|(1<<j-1)]=(tmp[j][S|(1<<j-1)]+dp[x][i][S])%MOD;
				if(sumsiz==s[j-1]-s[j]&&mx[S]<j)tmp[i][S|(1<<j-1)]=(tmp[i][S|(1<<j-1)]+dp[x][i][S])%MOD;
			}
		}
		for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++)dp[x][i][S]=tmp[i][S];
	}
//	for(int i=1;i<=k+1;i++)for(int S=0;S<(1<<k);S++)if(dp[x][i][S])
//		printf("dp[%d][%d][%d]=%d\n",x,i,S,dp[x][i][S]);
}
int main(){
	scanf("%d",&n);for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	scanf("%d",&k);for(int i=1;i<=k;i++)scanf("%d",&s[i]);s[0]=n;
	for(int i=1;i<(1<<k);i++)for(int j=1;j<=k;j++)if(i>>(j-1)&1)chkmax(mx[i],j);
	dfs(1,0);int res=0;
	for(int i=1;i<=k+1;i++)res=(res+dp[1][i][(1<<k)-1])%MOD;
	printf("%d\n",res);
	return 0;
}
```



---

## 作者：lzqy_ (赞：1)

哈哈嘿，又是一骑绝尘的最劣解！

一个 $O(6^kkn)$ 的无脑做法。

考虑将操作分为两种，进入一个大小为 $s_i$ 的子树或删去一个大小为 $s'_i$ 的子树。先 $2^k$ 穷举每一种可能，考虑对于一组操作怎么做。

如果只有删除是好做的。设 $f_{x,S}$ 表示在子树 $x$ 内执行了集合 $S$ 的删除操作，这是一个 $O(n3^k)$ 的 DP。

考虑进入一个子树对删除的限制。若当前进入子树是第 $i$ 个操作，那么对于第 $j(j>i)$ 个删除操作，必须在子树内进行。

设 $dp_{t,x,S}$ 表示在第 $t$ 个进入操作中进入了子树 $x$，在子树 $x$ 内进行了集合 $S$ 内的删除操作。

如果直接找下一个进入的子树是 $O(3^kkn^2)$ 的，无法接受。可以找到下一个进入的子树属于哪一个儿子，对于上一个 $f$ 的转移存下前缀和后缀的 DP 值，就能做到 $O(3^kkn)$ 转移了。

直接做似乎很难跑得动。观察到 DP 转移时会产生很多的空状态。因此在 $O(3^k)$ 合并两个 DP 状态时，先枚举其中一个子集而不是空集，如果该子集对应的 DP 值为空则直接 break，这样内层的 $O(3^k)$ 就非常近似于 $O(2^k)$ 了。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxk=15;
const int maxn=5010;
const int maxs=1<<6;
const int inf=1<<30;
const int mod=998244353;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
struct opt{
    int op,sz;
}a[maxk];
struct DP{
    int dp[maxs];
}zero;
vector<int>v[maxn];
vector<DP>f[maxn],g[maxn];
DP F[maxn],dp[maxk][maxn];
int er[maxn],l1[maxn],k1;
int en[maxn],l2[maxn],k2;
int n,k,s[maxk];
int sz[maxn],fa[maxn];
int Lst[maxs],Sum[maxs][maxk],Full[maxs][maxk];
il void merge(DP &a,DP b,DP c){
    int state=1<<k1;
    for(int t=0;t<state;t++)
    	if(b.dp[t])for(int s=t;s<state;s=(s+1)|t)
    		a.dp[s]=(a.dp[s]+1ll*b.dp[t]*c.dp[s^t])%mod;
}
void dfs(int x){
    for(int i=1;i<v[x].size();i++) dfs(v[x][i]);
    f[x][0].dp[0]=g[x][v[x].size()].dp[0]=1;
    for(int i=1;i<v[x].size();i++)
        merge(f[x][i],f[x][i-1],F[v[x][i]]);
    for(int i=v[x].size()-1;i;i--)
        merge(g[x][i],g[x][i+1],F[v[x][i]]);
    F[x]=g[x][1]; int state=1<<k1;
    for(int s=state-1;~s;s--){
        int tot=sz[x],lst=0;
        for(int i=1;i<=k1;i++)
            if(s&(1<<i-1)) lst=i,tot-=er[i];
        for(int i=lst+1;i<=k1;i++)
            if(er[i]==tot) ad(F[x].dp[s|(1<<i-1)],F[x].dp[s]);
    }
}
void DFS(int x){
    for(int i=1;i<v[x].size();i++) DFS(v[x][i]);
    int state=1<<k1;
    DP t1,t2;
    for(int t=0;t<k2;t++){
        for(int i=1;i<v[x].size();i++){
            t1=dp[t+1][v[x][i]],t2=zero;
            merge(t2,f[x][i-1],g[x][i+1]);
            for(int s=0;s<state;s++){
                if(Sum[s][t+1]+en[t+1]!=sz[v[x][i]]||!Full[s][t+1]) t1.dp[s]=0;
                if(Lst[s]>l2[t+1]) t2.dp[s]=0;
            }
            merge(dp[t][x],t1,t2);
        }
    }
    for(int t=0;t<k2;t++)
        for(int i=1;i<v[x].size();i++){
            t1=dp[t][v[x][i]],t2=zero;
            merge(t2,f[x][i-1],g[x][i+1]);
            merge(dp[t][x],t1,t2);
        }
    
    for(int s=0;s<state;s++)
	    if(Full[s][k2]&&Sum[s][k2]+en[k2]==sz[x]) 
			dp[k2][x].dp[s]=F[x].dp[s];
}
il void clear(){
    memset(Sum,0,sizeof(Sum));
    for(int i=1;i<=n;i++)
        for(int j=0;j<f[i].size();j++){
            memset(f[i][j].dp,0,sizeof(f[i][j].dp));
            memset(g[i][j].dp,0,sizeof(g[i][j].dp));
        }
    for(int i=1;i<=n;i++)
        memset(F[i].dp,0,sizeof(F[i].dp));
    for(int i=0;i<=k2;i++)
        for(int j=1;j<=n;j++)
            memset(dp[i][j].dp,0,sizeof(dp[i][j].dp));
    k1=k2=0;
}
il int calc(){
    clear();
//    for(int i=1;i<=k;i++)
//        printf("(%d,%d)\n",a[i].op,a[i].sz);
    for(int i=1;i<=k;i++)
        if(a[i].op==0) 
            er[++k1]=a[i].sz,l1[k1]=i;
        else en[++k2]=a[i].sz,l2[k2]=i;
    int state=1<<k1;
    for(int s=0;s<state;s++)
        for(int i=1;i<=k1;i++)
            if(s&(1<<i-1)) Lst[s]=l1[i];
	for(int t=0;t<=k2;t++)
		for(int s=0;s<state;s++){
			Full[s][t]=1;		
			for(int i=1;i<=k1;i++){
				if((s&(1<<i-1))&&l1[i]<l2[t])
					Sum[s][t]+=er[i];
				if(l1[i]>l2[t]) Full[s][t]&=bool(s&(1<<i-1));
			}
		}
    dfs(1);
    if(!k2) return F[1].dp[state-1];
    DFS(1);
    return dp[0][1].dp[state-1];
}
void init(int fath,int x){
    fa[x]=fath;
    for(int i=0;i<v[x].size();i++)
        if(v[x][i]^fath) init(x,v[x][i]),sz[x]+=sz[v[x][i]];
    sz[x]++;
}
void INIT(){
    v[1].insert(v[1].begin(),0);
    f[1].insert(f[1].begin(),zero);
    g[1].insert(g[1].begin(),zero);
    for(int i=1;i<=n;i++){
        f[i].push_back(zero);
        g[i].push_back(zero);
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<v[i].size();j++)
            if(v[i][j]==fa[i]){
                v[i].erase(v[i].begin()+j);
                v[i].insert(v[i].begin(),fa[i]);
                break;
            }
}
int main(){
//	freopen("CF.in","r",stdin);
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y),v[y].push_back(x);
        f[x].push_back(zero),g[x].push_back(zero);
        f[y].push_back(zero),g[y].push_back(zero);
    }
    init(0,1),INIT();
    k=read();
    for(int i=1;i<=k;i++) s[i]=read();
    int state=1<<k,ans=0; s[0]=n;
    for(int S=0;S<state;S++){
        for(int i=1;i<=k;i++)
            if(S&(1<<i-1)) a[i].op=1,a[i].sz=s[i];
            else a[i].op=0,a[i].sz=s[i-1]-s[i];
        ad(ans,calc());
    }  
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

给定一棵 $n$ 个点的树，进行以下操作 $k$ 次：

- 选择一条边并删除；
- 将两个连通块的其中一个删除。
- 设当前是第 $i$ 次操作，要求剩下连通块的大小等于 $s_i$。

计算有多少种进行 $k$ 次操作的方案，对 $998244353$ 取模。

两种方案不同，当且仅当在其中一次操作选择的边不同，或删除的连通块不同。

$2 \le n \le 5000$，$1 \le k \le \min(6, n - 1)$，$n > s_1 > s_2 > \cdots > s_k \ge 1$。

----

直接对着题目的操作做是比较难设 DP 状态的。所以可以考虑做一些转化。

设当前为第 $i$ 次操作。我们给被删除的连通块标上 $i$。所有操作后给剩下的所有点标上 $k + 1$。

现在问题变成，有多少种给每个点标 $1 \sim k + 1$ 整数的方案，使得：

- 对于所有 $1 \le i \le k + 1$，标 $i$ 的所有点构成一个连通块（称其为连通块 $i$），其大小为 $s_{i - 1} - s_i$（设 $s_0 = n$，$s_{k + 1} = 0$）；
- 对于所有 $1 \le i \le k$，连通块 $i$ 恰好有一条边连向连通块 $i + 1$。否则第 $i$ 次操作无法进行。

这个问题是好做的。直接设 $f_{u, S, i, 0/1}$ 表示 $u$ 子树内包含了所有 $S$ 中的连通块（且这些连通块已经封闭，不会再新加点），$u$ 标的整数为 $i$，连通块 $i$ 是否已经有一条连向连通块 $i + 1$ 的边，的方案数。

转移枚举另一棵子树状态就可以做到 $O(nk^23^k)$ 的时间复杂度。常数很小可以轻松通过。

```cpp
// Problem: H. Tree Cutting
// Contest: Codeforces - Codeforces Round 854 by cybercats (Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1799/H
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 5050;
const int mod = 998244353;

inline void fix(int &x) {
	x += ((x >> 31) & mod);
}

int n, m, a[99], b[99], c[999];
vector<int> G[maxn];

int f[maxn][7][128][2], g[7][128][2], sz[maxn];

void dfs(int u, int fa) {
	for (int i = 0; i < m; ++i) {
		f[u][i][0][0] = 1;
	}
	sz[u] = 1;
	for (int v : G[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		sz[u] += sz[v];
		for (int i = 0; i < m; ++i) {
			for (int S = 0; S < (1 << m); ++S) {
				for (int p = 0; p <= 1; ++p) {
					g[i][S][p] = f[u][i][S][p];
					f[u][i][S][p] = 0;
				}
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int S = 0; S < (1 << m); ++S) {
				if (S & (1 << i)) {
					continue;
				}
				for (int p = 0; p <= 1; ++p) {
					int v1 = g[i][S][p];
					if (!v1) {
						continue;
					}
					int U = (1 << m) - 1 - S;
					for (int j = 0; j < m; ++j) {
						for (int T = U;; T = (T - 1) & U) {
							if (T & (1 << i)) {
								continue;
							}
							if (i == j) {
								for (int q = 0; p + q <= 1; ++q) {
									int v2 = f[v][j][T][q];
									if (!v2) {
										continue;
									}
									fix(f[u][i][S | T][p + q] += 1LL * v1 * v2 % mod - mod);
								}
							} else if ((T & (1 << j)) && p + (i < j) <= 1) {
								for (int q = 0; q <= 1; ++q) {
									int v2 = f[v][j][T][q];
									if (!v2) {
										continue;
									}
									if (q + (j < i) == (j < m - 1)) {
										fix(f[u][i][S | T][p + (i < j)] += 1LL * v1 * v2 % mod - mod);
									}
								}
							}
							if (!T) {
								break;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int S = 0; S < (1 << m); ++S) {
			if (S & (1 << i)) {
				continue;
			}
			for (int p = 0; p <= 1; ++p) {
				int v = f[u][i][S][p];
				if (!v) {
					continue;
				}
				if (sz[u] > c[S | (1 << i)]) {
					f[u][i][S][p] = 0;
				} else if (sz[u] == c[S | (1 << i)]) {
					f[u][i][S | (1 << i)][p] = v;
					f[u][i][S][p] = 0;
				}
			}
		}
	}
}

void solve() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v);
		G[v].pb(u);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
	}
	b[0] = n;
	for (int i = 0; i <= m; ++i) {
		a[i] = b[i] - b[i + 1];
	}
	++m;
	for (int S = 0; S < (1 << m); ++S) {
		for (int i = 0; i < m; ++i) {
			if (S & (1 << i)) {
				c[S] += a[i];
			}
		}
	}
	dfs(1, -1);
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		fix(ans += f[1][i][(1 << m) - 1][i < m - 1] - mod);
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Hilaria (赞：0)

### [CF1799H Tree Cutting](https://www.luogu.com.cn/problem/CF1799H)

- 题意：

给定一个 $n$ 个点的树，有 $k$ 次操作，每次操作选定一条边进行删除，并选择剩下的两个部分中的其中一个进行删除，输出剩余部分中的节点数。

现在给定你最终输出的序列，问有多少中合法操作方案满足最终序列，答案可能较大，请对 $998244353$ 取模。（如果边或者剩余部分的选择不同，则将其视为不同的方案。）

$2\leq n \leq 5000,1\leq k\leq \min(6,n-1)$

- 思路：

首先观察到数据范围 $k$ 很小，感觉可能是状压。

然后先直接做树形 dp，但是发现每次操作可以删除一棵子树也可能只留下一棵子树，这不便于我们进行 dp，于是我们考虑能不能钦定一些东西使得根节点不被删掉，因为有了不能删根节点的限制的话，就比较容易进行树形 dp。

那么我们假设根节点一定不会被删，那么联系到 $n$ 的范围是支持平方算法的，哥们可以放心 dp。

现在钦定了根节点一定不会被删，那么题目会变成每次删一个特定大小的子树。

为了方便描述，我们将最终的序列改为每次删除的子树大小，如样例#2 ```4 2``` 就会变成 ```3 2```。

然后由于子树的删除是有顺序的，先被清除的子树中不能有后被清除的子树（就是想表达先删的一定要在后删的下面）。

那么联系到 $k$ 的范围，我们果断状压 dp，记 $f_{u,S}$ 为以 $u$ 为根的子树中删除的集合为 $S$。

然后枚举子集从 $v$ 中转移即可。

但是由于我们实际要做 $n$ 个根，直接做 $n$ 次是平方的，所以我们需要一个换根 dp，具体我们可以对每个点做一个前后缀优化，然后就能 $O(3^k)$ 得到一个点除去一个儿子的 $f$。

---

