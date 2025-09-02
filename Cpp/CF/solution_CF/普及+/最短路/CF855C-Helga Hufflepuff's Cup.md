# Helga Hufflepuff's Cup

## 题目描述

Harry, Ron and Hermione have figured out that Helga Hufflepuff's cup is a horcrux. Through her encounter with Bellatrix Lestrange, Hermione came to know that the cup is present in Bellatrix's family vault in Gringott's Wizarding Bank.

The Wizarding bank is in the form of a tree with total $ n $ vaults where each vault has some type, denoted by a number between $ 1 $ to $ m $ . A tree is an undirected connected graph with no cycles.

The vaults with the highest security are of type $ k $ , and all vaults of type $ k $ have the highest security.

There can be at most $ x $ vaults of highest security.

Also, if a vault is of the highest security, its adjacent vaults are guaranteed to not be of the highest security and their type is guaranteed to be less than $ k $ .

Harry wants to consider every possibility so that he can easily find the best path to reach Bellatrix's vault. So, you have to tell him, given the tree structure of Gringotts, the number of possible ways of giving each vault a type such that the above conditions hold.

## 说明/提示

In test case $ 1 $ , we cannot have any vault of the highest security as its type is $ 1 $ implying that its adjacent vaults would have to have a vault type less than $ 1 $ , which is not allowed. Thus, there is only one possible combination, in which all the vaults have type $ 2 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
1 4
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2
1 3
2 1
```

### 输出

```
13
```

## 样例 #3

### 输入

```
3 1
1 2
1 3
1 1
```

### 输出

```
0
```

# 题解

## 作者：一扶苏一 (赞：7)

## Description

给你一个树，可以染 $m$ 个颜色，定义一个特殊颜色 $k$ ， 要求保证整棵树上特殊颜色的个数不超过 $x$ 个。同时，如果一个节点是特殊颜色，那么它的相邻节点的颜色编号必须全部小于 $k$。求方案数。

## Input

第一行 $n,m$ 代表节点个数和颜色树

下面 $n~-~1$ 行描述一棵树

最后一行是特殊颜色 $k$ 和颜色个数 $x$

## Output

输出一行一个整数，代表答案对 $10^9~+~7$ 取模结果

## Hint

$Forall:$

$n~\leq~10^5~,~m~\leq~10^9~,~k~\leq~m~,~x~\leq~10$

## Solution

这题感觉有点像[DDOSvoid的疑惑](https://www.luogu.org/problemnew/show/P5007)

~~**我 爆 破 我 自 己**~~

数数题，考虑DP。

显然这个题的选点分为三种，分别是小于 $k$，等于 $k$，大于 $k$。同时有颜色个数的限制，于是可以设 $f_{i,j,0/1/2}$ 代表以 $i$ 为根的子树，选了 $j$ 个特殊颜色，其中节点 $i$ 的颜色 小于/等于/大于 $k$

考虑一个节点只有两个儿子的情况，直接把贡献乘一下即可。

考虑一个节点有多个儿子的时候，每加入一个新节点产生的贡献如何计算：

设 $g_{i,j,0/1/2}$ 为 $u$ 的子树（省略第一维），考虑前 $i$ 个儿子，选了 $j$ 个 $k$，节点 $i$ 的状态是 $0/1/2$ 的方案数。

一下假设当前枚举的是 $u$ 的第 $i$ 个儿子。

考虑 $u$ 选小于 $k$ 的情况：

则该儿子可以选 $0/1/2$ 三种情况，这三种情况相互并行，应该将贡献相加，同时两两子树间互不影响，应将贡献相乘。

于是有

$$g_{i,j,0}~=~\sum_{h=0}^{j}(g_{i-1,j-h,0}~\times~\sum_{s=0}^{2}f_{to,h,s})$$

同理，$u$ 选等于 $k$ 的情况：

该儿子只能选 $0$ 一种情况，于是有

$$g_{i,j,1}~=~\sum_{h=0}^{j}(g_{i-1,j-h,1}~\times~f_{to,h,0})$$

同理，$u$ 选大于 $k$ 的情况：

该儿子可以选 $0/2$ 两种可能，于是

$$g_{i,j,2}~=~\sum_{h=0}^{j}(g_{i-1,j-h,2}~\times~\sum_{s=0,2}f_{to,h,s})$$

设 $u$ 有 $v$ 个孩子，于是

$$f_{u,j,0/1/2}~=~g_{v,j,0/1/2}$$

当然 $g$ 可以把第一维滚掉，这样就没有空间问题辣~

于是就可以统计答案了。记得取模。代码里面因为不知道哪里爆掉了于是干脆 $define~~int~~ll$ 了23333

## Code

```cpp
#include <cstdio>
#include <cstring>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long
#define int ll


typedef long long ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;
const int maxm = 200010;
const int MOD = 1000000007;

struct Edge {
	int to, nxt;
};
Edge edge[maxm]; int hd[maxn], ecnt = 1;
inline void cont(ci from, ci to) {
	Edge &e = edge[++ecnt];
	e.to = to; e.nxt = hd[from]; hd[from] = ecnt;
}

int n, m, x, v, dv;
int frog[maxn][15][3], gorf[maxn][2][15][3];

void reading();
void dfs(ci, ci);

signed  main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(m);
	reading();
	qr(v); qr(x); dv = m - v;
	dfs(1, 0);
	int ans = 0;
	for (rg int i = 0; i <= x; ++i) 
		for(rg int j = 0; j < 3; ++j) ans = (ans + frog[1][i][j]) % MOD;
	qw(ans, '\n', true);
	return 0;
}

void reading() {
	int a, b;
	for (rg int i = 1; i < n; ++i) {
		a = b = 0;
		qr(a); qr(b);
		cont(a, b);
		cont(b, a);
	}
}

void dfs(ci u, ci pree) {
	int pre = 0;
	gorf[u][pre][0][0] = v - 1;
	gorf[u][pre][1][1] = 1;
	gorf[u][pre][0][2] = dv;
	for (int i = hd[u]; i; i = edge[i].nxt) if(i != pree) {
		int &to = edge[i].to;
		dfs(to, i ^ 1);
		pre ^= 1;
		memset(gorf[u][pre], 0, sizeof gorf[u][pre]);
		for (rg int j = 0; j <= x; ++j) {
			for (rg int k = 0; k <= j; ++k) {
				gorf[u][pre][j][0] = (gorf[u][pre][j][0] + 1ll * gorf[u][pre ^ 1][j - k][0] * (frog[to][k][0] + frog[to][k][1] + frog[to][k][2])) % MOD;
				gorf[u][pre][j][1] = (1ll * gorf[u][pre ^ 1][j - k][1] * frog[to][k][0] + gorf[u][pre][j][1]) % MOD;
				gorf[u][pre][j][2] = (1ll * gorf[u][pre ^ 1][j - k][2] * (frog[to][k][0] + frog[to][k][2]) + gorf[u][pre][j][2]) % MOD;
			}
		}
	}
	for (rg int i = 0; i <= x; ++i) 
		for (rg int j = 0; j < 3; ++j)
			frog[u][i][j] = gorf[u][pre][i][j];
#ifdef DEBUG
	printf("EM%d:\n", u);
	for (rg int i = 0; i <= x; ++i) {
		for (rg int j = 0; j < 3; ++j) 
			printf("%d %d %d\n",i, j, frog[u][i][j]);
	}
#endif
}
```

## Summary

这类树上求方案数的问题都需要在转移时借助一个辅助数组，记录已经枚举过得儿子的信息，然后计算当前这个儿子加入的贡献。

---

## 作者：Powerless233 (赞：5)

## Description
原题的翻译多少有点问题。搬一下 一扶苏一 在题解中的翻译：

给你一个树，可以染 $m$ 个颜色，定义一个特殊颜色 $k$ ， 要求保证整棵树上特殊颜色的个数不超过 $x$ 个。同时，如果一个节点是特殊颜色，那么它的相邻节点的颜色编号必须全部小于 $k$。求方案数。

## Analysis
读题意，树上方案数统计问题，显然树形 dp 。

考虑什么因素会对答案造成影响：子树内 **已经染的特殊颜色数量**，当前点编号 **与特殊颜色编号的关系** 。

与特殊编号的关系无非 $3$ 种，小于，等于，大于，只要是这 $3$ 种情况中的一种，具体的颜色不会对答案造成影响（例如 $k=3$ ，当前节点是 $1/2$ 不影响答案）。

那么状态就很显然了。

设 $f_{x,j,0/1/2}$ 表示在 $x$ 的子树内已经取了 $j$ 个特殊颜色，当前节点颜色编号 小于/等于/大于 $k$ 的方案数。

接下来，就是一般的树形背包了。

根据题意，有状态转移方程：

（其中， $x$ 表示当前节点， $y$ 表示当前正在合并的子树， $si_{i}$ 表示在以 $i$ 为根的子树内点的数量。）

1. 当前节点编号 $< k$ ，那么儿子随便取：

$$f_{x,i+j,0}=\sum\limits_{i=0}^{si_{x}}\sum\limits_{j=0}^{si_{y}}f_{x,i,0}\times(f_{y,j,0}+f_{y,j,1}+f_{y,j,2})$$

2. 当前节点编号 $= k$ ，那么儿子编号 $<k$ ：

$$f_{x,i+j,0}=\sum\limits_{i=0}^{si_{x}}\sum\limits_{j=0}^{si_{y}}f_{x,i,0}\times f_{y,j,0}$$

3. 当前节点编号 $> k$ ，那么儿子只有 $k$ 不能取：

$$f_{x,i+j,0}=\sum\limits_{i=0}^{si_{x}}\sum\limits_{j=0}^{si_{y}}f_{x,i,0}\times (f_{y,j,0}+f_{y,j,2})$$

边界情况：

$$f_{x,0,0}=k-1$$

$$f_{x,1,1}=1$$

$$f_{x,0,2}=m-k$$

## Notice

- 注意取模。

- 背包的时候下标可能会重复，记得先记下原子树的信息再更新。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define inf 0x3f3f3f3f
using namespace std;
inline LL read(){
	LL res=0,fl=1;
	char ch=getchar();
	while(!(ch>='0' && ch<='9')){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0' && ch<='9')res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return res*fl;
}
inline LL max(LL a,LL b){return a>b?a:b;}
inline LL min(LL a,LL b){return a<b?a:b;}
inline void swap(int &a,int &b){int c;c=a;a=b;b=c;}
const int MAXN=1e5+5,MAXK=10+5,mod=1e9+7;
int n,m,k,p,ans=0,si[MAXN],f[MAXN][MAXK][3],g[MAXN][MAXK];
vector<int> e[MAXN];
inline void Tree_dp(int x,int fa){
	si[x]=1;
	f[x][0][0]=k-1;
	f[x][1][1]=1;
	f[x][0][2]=m-k;
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i];
		if(y!=fa){
			Tree_dp(y,x);
			int up1=min(si[x],p),up2;
			for(int j=0;j<=up1;j++)
				for(int c=0;c<=2;c++)
					g[j][c]=f[x][j][c],f[x][j][c]=0;
			
			for(int j=0;j<=up1;j++){
				up2=min(si[y],p-j);
				for(int l=0;l<=up2;l++){
					f[x][j+l][0]=(f[x][j+l][0]+1LL*g[j][0]%mod*((f[y][l][0]+f[y][l][1])%mod+f[y][l][2])%mod)%mod;
					f[x][j+l][1]=(f[x][j+l][1]+1LL*g[j][1]%mod*f[y][l][0]%mod)%mod;
					f[x][j+l][2]=(f[x][j+l][2]+1LL*g[j][2]%mod*(f[y][l][0]+f[y][l][2])%mod)%mod;
				}
			}
			si[x]+=si[y];
		}
	}
}
int main() {
	int x,y;
	n=read(),m=read();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	k=read(),p=read();
	Tree_dp(1,0);
	for(int i=0;i<=p;i++)
		for(int j=0;j<=2;j++)
			ans=(ans+f[1][i][j])%mod;
	cout<<ans<<'\n';
	return 0;
}


```


---

## 作者：LlLlCc (赞：4)

一道很好的树形$DP$

每个节点可以看成有三种取值，分别为大于$K$、等于$K$、小于$K$

不妨设：

$\large f_{i,j,k}:$ 以$i$为根的子树，有$j$个点为特殊颜色，$i$节点为$k$的方案数

其中$k$为$0,1,2$，分别为大于$K$、等于$K$、小于$K$

对于每一个节点，还要再进行一次$DP$，设：

$\large G_{x,i,j,k}:$ $x$为树的根，$x$的颜色为$k$，前$i$个子节点，其中$j$个子节点为特殊颜色的方案数。显然，前两维可以滚掉。

转移方程：

$\large G_{j+k,0}=f_{x,j,0}\times \sum\limits_{i=0}^2  \sum\limits_{i=0}^2 f_{son,k,i}$

$\large G_{j+k,0}=f_{x,j,0}\times f_{son,k,0}$

$\large G_{j+k,0}=f_{x,j,0}\times (f_{son,k,0}+f_{son,k,2})$

## code
```
#include<bits/stdc++.h>
#define maxn 100005
#define ll long long
using namespace std;
const ll TT=1e9+7;
int s[maxn],n,x,tot,y,lnk[maxn],m,K,nxt[maxn<<1],son[maxn<<1],N;
ll f[maxn][15][3],G[15][3],Ans;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Dfs(int x,int fa){
	f[x][0][0]=K-1;
	s[x]=f[x][1][1]=1;
	f[x][0][2]=m-K;
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa){
	  	Dfs(son[i],x);memset(G,0,sizeof G);
	  	for (int j=0;j<=s[x];j++)
	  	for (int k=0;k<=s[son[i]];k++){
	  		if (j+k>N) break;
	  		G[j+k][0]=(G[j+k][0]+f[x][j][0]*(f[son[i]][k][0]+f[son[i]][k][1]+f[son[i]][k][2]))%TT;
		    G[j+k][1]=(G[j+k][1]+f[x][j][1]*f[son[i]][k][0])%TT;
		    G[j+k][2]=(G[j+k][2]+f[x][j][2]*(f[son[i]][k][0]+f[son[i]][k][2]))%TT;
		  }
		s[x]=min(s[x]+s[son[i]],N);
		for (int j=0;j<=s[x];j++)
		for (int k=0;k<3;k++) f[x][j][k]=G[j][k];
	  }
}
int main(){
	n=read(),m=read();
	for (int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	K=read(),N=read();Dfs(1,0);
	for (int i=0;i<=s[1];i++)
	for (int j=0;j<3;j++) Ans=(Ans+f[1][i][j])%TT;
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：Otue (赞：2)

一道很有意思的树形 dp，和 [P4516 潜入行动](https://www.luogu.com.cn/problem/P4516) 非常相似。

考虑状态怎么定义。第一个维度肯定是以 $i$ 为根的子树，第二个维度是当前子树中的特殊节点个数，同时还要考虑**当前节点的颜色**，即为第三个维度。

**当前节点的颜色**无非跟 $k$ 有关，即小于 $k$，等于 $k$，大于 $k$ 这三种关系，将这三种关系记为 $0/1/2$。故定义 $dp_{i,j,k}$ 表示以 $i$ 为根的子树中有 $j$ 个特殊节点，且当前节点颜色编号关系是 $k$ 的染色方案数。

考虑初始化。$dp_{i,0,1}=k-1,dp_{i,1,1}=1,dp_{i,0,2}=m-k$。

考虑转移。套路的来讲，若 $x$ 是 $y$ 的父亲，则枚举 $x$ 选择 $j$ 个点，枚举 $y$ 选择 $k(k\leq j)$ 个点。即为 $dp_{x,j}=
\text{combine}(dp_{x,j-k},dp_{y,k})$。

此题中，因为加上了 $k$ 这个维度，所以需要讨论 $k=0/1/2$ 这三种情况。

* 若 $k=0$，即当前节点颜色编号小于 $k$，则儿子随便选。    
$dp_{u,j,0}=
\sum dp_{u,j-k,0}\times (dp_{v,k,0}+dp_{v,k,1}+dp_{v,k,2})$
* 若 $k=1$，即当前节点颜色编号等于 $k$，则儿子颜色编号只能小于 $k$。   
$dp_{u,j,1}=
\sum dp_{u,j-k,1}\times dp_{v,k,0}$
* 若 $k=2$，即当前节点颜色编号大于 $k$，儿子颜色编号除了 $k$ 其他都可以选。   
$dp_{u,j,2}=
\sum dp_{u,j-k,2}\times (dp_{v,k,0}+dp_{v,k,2})$

答案即为 $\sum_{i=0}^{x}\sum_{j=0}^{2
} dp_{1,i,j}$。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5, mod = 1e9 + 7;

int n, m, k, x, dp[N][11][3], tmp[11][3];

int en, first[N], sz[N];
struct edge {
	int e, next;
}ed[N * 2];

void add_edge(int s, int e) {
	en++;
	ed[en].e = e;
	ed[en].next = first[s];
	first[s] = en;
}

void init(int u, int fa) {  // 预处理子树大小
	sz[u] = 1;
	for (int p = first[u]; p; p = ed[p].next) {
		int e = ed[p].e;
		if (e == fa) continue;
		init(e, u);
		sz[u] += sz[e];
	}
}

void dfs(int u, int fa) {
	dp[u][0][0] = k - 1;
	dp[u][1][1] = 1;
	dp[u][0][2] = m - k;
	for (int p = first[u]; p; p = ed[p].next) {
		int e = ed[p].e;
		if (e == fa) continue;
		dfs(e, u);
		for (int j = 0; j <= x; j++) {
			for (int k = 0; k < 3; k++) {
				tmp[j][k] = dp[u][j][k];
				dp[u][j][k] = 0;
			}
		}
		for (int j = min(sz[u], x); j >= 0; j--) {
			for (int k = 0; k <= min(sz[e], j); k++) {
				dp[u][j][0] = (dp[u][j][0] + tmp[j - k][0] * (dp[e][k][0] + dp[e][k][1] + dp[e][k][2]) % mod) % mod;
				dp[u][j][1] = (dp[u][j][1] + tmp[j - k][1] * dp[e][k][0] % mod) % mod;
				dp[u][j][2] = (dp[u][j][2] + tmp[j - k][2] * (dp[e][k][0] + dp[e][k][2]) % mod) % mod;
			}
		}
	}
}

signed main() {
// 	freopen("color.in", "r", stdin);
// 	freopen("color.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v), add_edge(v, u);
	}
	cin >> k >> x;
	init(1, -1);
	dfs(1, -1);
	int res = 0;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j < 3; j++) res = (res + dp[1][i][j]) % mod; 
	}
	cout << res << endl;
}
```

---

## 作者：xxx2022 (赞：1)

根据题意，我们可以发现这是一道树形 dp。首先考虑设计状态，注意到 $k$ 较小，那么我们可以在 dp 数组里面塞一维来维护特殊颜色点的个数。然后题目里有颜色编号的大小限制，所以第三维用 $0/1/2$ 来分别表示当前颜色小于/等于/大于 $k$ 的情况。那么这样的话就是用 $f_{i,j,0/1/2}$ 表示在以 $i$ 为根的子树内，有 $j$ 个特殊颜色在三种情况下的答案。那么转移方程式即为：

$$f_{x,i+j,0}=\sum \limits_{y \in son_x}{f_{x,i,0} \times (f_{y,j,0}+f_{y,j,1}+f_{y,j,2})}$$

$$f_{x,i+j,1} = \sum \limits_{y \in son_x}{f_{x,i,1} \times f_{y,j,0}}$$

$$f_{x,i+j,2} = \sum \limits_{y \in son_x}{f_{x,i,2} \times (f_{y,j,0}+f_{y,j,2})}$$

树形背包转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod=1e9+7;
const int N=1e5+10;
inline int read(){
    int f=1,w=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')  f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        w=(w<<1)+(w<<3)+(c^48);
        c=getchar();
    }
    return f*w;
}
struct node{
    int to,nex;
}e[N*2];
int head[N],tot;
void add_edge(int x,int y){
    e[++tot].to=y;
    e[tot].nex=head[x];
    head[x]=tot;
}
int n,m;
int k,lim;
int f[N][15][3];
int siz[N];
int tmp[15][3];
void dfs(int x,int fa){
    siz[x]=1;
    f[x][0][0]=k-1;
    f[x][1][1]=1;
    f[x][0][2]=m-k;
    for(int p=head[x];p;p=e[p].nex){
        int y=e[p].to;
        if(y==fa)   continue;
        dfs(y,x);
        siz[x]+=siz[y];
        for(int i=0;i<=min(siz[x],lim);i++){
            tmp[i][0]=f[x][i][0];
            f[x][i][0]=0;
            tmp[i][1]=f[x][i][1];
            f[x][i][1]=0;
            tmp[i][2]=f[x][i][2];
            f[x][i][2]=0;
        }
        for(int i=0;i<=min(siz[x],lim);i++){
            for(int j=0;j<=min(siz[y],lim-i);j++){
                (f[x][i+j][0]+=(tmp[i][0]*(((f[y][j][0]+f[y][j][1])%mod+f[y][j][2])%mod)%mod)%mod)%=mod;
                (f[x][i+j][1]+=tmp[i][1]*f[y][j][0]%mod)%=mod;
                (f[x][i+j][2]+=(tmp[i][2]*((f[y][j][0]+f[y][j][2])%mod)%mod)%mod)%=mod;
            }
        }
    }
}
signed main(){
    n=read();
    m=read();
    for(int i=1;i<n;i++){
        int x,y;
        x=read();
        y=read();
        add_edge(x,y);
        add_edge(y,x);
    }
    k=read();
    lim=read();
    dfs(1,0);
    int ans=0;
    for(int i=0;i<=lim;i++){
        (ans+=((f[1][i][0]+f[1][i][1])%mod+f[1][i][2])%mod)%=mod;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Judgelight (赞：1)

到不了紫，最多蓝。

假设对于 $k$ 没有相邻颜色编号大小的限制，就是一个比较明显的树上背包，背包容量为 $x$。

现在有了编号大小的限制，考虑把状态设为 $f_{u,s,0/1/2}$，表示 $u$ 的子树里面有 $s$ 个 $k$，并且 $u$ 的颜色编号小于/等于/大于 $k$，然后按照背包那样转移即可。

```cpp

f[u][0][0]=k-1,f[u][1][1]=1,f[u][0][2]=m-k;
for(int i=he[u];i;i=e[i].ne){
	int v=e[i].to;
	if(v==from)continue;
	dfs(v,u);
	for(int s=x;s>=0;s--){
		int ans[3];ans[0]=ans[1]=ans[2]=0;
		for(int j=0;j<=s;j++){
			ans[0]=md(ans[0]+1ll*md(md(f[v][j][0]+f[v][j][1])+f[v][j][2])*f[u][s-j][0]%mod);
			ans[1]=md(ans[1]+1ll*f[v][j][0]*f[u][s-j][1]%mod);
			ans[2]=md(ans[2]+1ll*md(f[v][j][0]+f[v][j][2])*f[u][s-j][2]%mod);
		}
		f[u][s][0]=ans[0],f[u][s][1]=ans[1],f[u][s][2]=ans[2];
	}
}
```

---

