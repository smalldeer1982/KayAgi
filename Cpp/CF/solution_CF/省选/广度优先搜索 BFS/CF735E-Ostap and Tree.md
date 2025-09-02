# Ostap and Tree

## 题目描述

Ostap already settled down in Rio de Janiero suburb and started to grow a tree in his garden. Recall that a tree is a connected undirected acyclic graph.

Ostap's tree now has $ n $ vertices. He wants to paint some vertices of the tree black such that from any vertex $ u $ there is at least one black vertex $ v $ at distance no more than $ k $ . Distance between two vertices of the tree is the minimum possible number of edges of the path between them.

As this number of ways to paint the tree can be large, Ostap wants you to compute it modulo $ 10^{9}+7 $ . Two ways to paint the tree are considered different if there exists a vertex that is painted black in one way and is not painted in the other one.

## 说明/提示

In the first sample, Ostap has to paint both vertices black.

In the second sample, it is enough to paint only one of two vertices, thus the answer is $ 3 $ : Ostap can paint only vertex $ 1 $ , only vertex $ 2 $ , vertices $ 1 $ and $ 2 $ both.

In the third sample, the valid ways to paint vertices are: $ {1,3} $ , $ {1,4} $ , $ {2,3} $ , $ {2,4} $ , $ {1,2,3} $ , $ {1,2,4} $ , $ {1,3,4} $ , $ {2,3,4} $ , $ {1,2,3,4} $ .

## 样例 #1

### 输入

```
2 0
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1
1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 1
1 2
2 3
3 4
```

### 输出

```
9
```

## 样例 #4

### 输入

```
7 2
1 2
2 3
1 4
4 5
1 6
6 7
```

### 输出

```
91
```

# 题解

## 作者：青君 (赞：12)

思路来自@skylee，但他呀讲得不太对的亚子。  

不关心 是怎么想到的 的话可跳转至Part2的DP部分。
## Part 1

树形DP。定义~~着色点为着色点~~，合法点为与最近的着色点距离不超过 $k$ 的点，合法子树为全由合法点构成的子树。  

考虑要加上哪些状态。DP合并时，子树与子树之间有哪些相互作用呢？无非是一棵子树 $A$ 中的着色点对子树 $B$ 中的某些非合法点产生了贡献（使之变成合法点）。  

所以我们设 $f_{x,i,j}$ 表示以 $x$ 为根的子树，**子树内**离 $x$ 最近的着色点到 $x$ 的距离为 $i$，**子树内**离 $x$ 最远的非合法点到 $x$ 的距离为 $j$。然后就可以转移了。时间复杂度 $\Theta(nk^4)$，看一下数据范围好像能过？这就是 $k$ 搞这么小的意义所在吗。  
## Part 2

我们不满足于这个不优美的做法，考虑对其进行优化。   

有一个性质：  **两棵非合法子树合并后，最深的非合法点不可能被消去**  。  

证明：  
假设我们要合并 $f_{x,i,j}$ 与 $f_{y,i',j'}$  
其中 $i,i',j,j'<k$，$j\ge j'+1$
  
![](https://cdn.luogu.com.cn/upload/image_hosting/3izcxkq2.png)  
因为 $x2,y2$不合法，所以 $i+j>k,i'+j'>k$  
如果合并后 $x2$ 变成了合法点，则 $i'+1+j\le k$，又 $j'+1\le j$ 所以 $i'+1+j'+1\le k$，与 $i'+j'>k$ 矛盾。  

**这个性质告诉我们，对于非合法子树，$j$ 的转移与 $i$ 无关，可以扬弃 $i$ 这维状态。**  

定义新的DP状态 $f_{x,i},0\le i \le 2k$  
当 $0\le i \le k$ 时，表示以 $x$ 为根的子树是一棵合法子树，且**子树内**离 $x$ 最近的染色点与 $x$ 的距离为 $i$；  
当 $k+1\le i \le 2k$ 时，表示以 $x$ 为根的子树是一棵非合法子树，且**子树内**离 $x$ 最远的非合法点与 $x$ 的距离为 $i-k-1$。  

答案为 $\sum_{0\le i \le k} f_{1,i}$  。  
一个孤点的DP值为 $f_{x,0}=f_{x,k+1}=1$  
考虑如何合并 $f_{x,i}$ 与 $f_{y,j}$  
1. 当 $i\le k,j\le k$ 时，合并为 $f_{x,min(i,j+1)}$；
2. 当 $i\le k,j> k,i+j-k\le k$ 时，$x$ 内的染色点可以贡献到 $y$ 内的非合法点，所以合并为 $f_{x,i}$；
3. 当 $i\le k,j> k,i+j-k> k$ 时，合并为 $f_{x,j+1}$；
4. 当 $i> k,j> k$ 时，合并为 $f_{x,max(i,j+1)}$；

于是就得到了代码中神奇的一句话转移：  
`t[i+j<=2*k?min(i,j+1):max(i,j+1)]+=f[x][i]*f[y][j]`  

时间复杂度 $\Theta(nk^2)$。

**Comment**：Part1 大概是 2500 的亚子，Part2 可能有 3000？最扯的是这个 2500 的DP都可以黑啊。 

```cpp
#include<bits/stdc++.h> 
#define mk make_pair
#define pk push_back 
using namespace std;
typedef long long LL;
typedef pair<int,int> pi;
template<class T> bool cmax(T &x,T y){return y>x?x=y,1:0;}
template<class T> bool cmin(T &x,T y){return y<x?x=y,1:0;}
const int N=105,K=45,mod=1e9+7;
int n,k,f[N][K],t[K];
vector<int> to[N]; 
void dfs(int x,int pre){
	f[x][0]=1,f[x][k+1]=1;
	for(auto y:to[x])if(y^pre){
		dfs(y,x);
		memset(t,0,sizeof t);
		for(int i=0;i<=2*k;++i)
			for(int j=0;j<=2*k;++j)
				(t[i+j<=2*k?min(i,j+1):max(i,j+1)]+=1ll*f[x][i]*f[y][j]%mod)%=mod;
		memcpy(f[x],t,sizeof t);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1,x,y;i<n;++i) cin>>x>>y,to[x].pk(y),to[y].pk(x);
	dfs(1,0); 
	int ans=0;
	for(int i=0;i<=k;++i) (ans+=f[1][i])%=mod;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：happybob (赞：7)

限制相当于对于每个点 $i$，离 $i$ 最近的染色点距离不超过 $k$。

对于每个 $i$，考虑记 $d_i$ 表示离 $i$ 最近的染色点距离，考虑每一组 $d_1,d_2,\cdots,d_n$ 至多对应一种染色方案，每种染色方案也恰对应一组 $a$，故考虑对可行的 $d$ 计数。

什么样的 $d$ 存在一种对应的染色方案呢？充要条件是：

1. 相邻两个的 $d$ 差值不超过 $1$。
2. 对于所有 $d_u \neq 0$，存在邻点 $v$ 使得 $d_v = d_{u}-1$。

必要性容易证明，充分性考虑对于 $d$ 的值从小到大归纳。

于是可以直接 DP，记 $f_{i,j,0/1}$ 表示以 $i$ 为根子树，$d_i = j$，是否存在 $i$ 的儿子 $v$ 使得 $d_v = j - 1$，转移是容易的，复杂度 $O(nk)$。

---

## 作者：skylee (赞：3)

### 题解地址：
[[CF735E/736C]Ostap and Tree - skylee's Blog](http://www.cnblogs.com/skylee03/p/8989401.html)

### 题目大意：

一个$n(n\le100)$个点的树，将一些点染成黑点，求满足每个点到最近黑点的距离$\le k(k\le\min(20,n-1))$的方案数。

### 思路：

树形DP。

用$f[i][j]$表示$i$的子树中离$i$最近黑点的距离为$j$，且距离超过$j$的点都被满足的方案数。转移时新建一个临时数组$tmp$保存转移后的$f[x]$。设$y$是$x$的子结点，枚举$f[x][i]$和$f[y][j]$，转移如下：

1. 若$i+j\le2k$，则此时$\min(i,j+1)\le k$，对于长度为$i+j+1$的链上的所有点都可以找到一边距离$\le k$，因此状态合并以后是合法状态，转移$tmp[\min(i,j+1)]+=f[x][i]\times f[y][j]$；  
2. 若$i+j>2k$，则此时$\max(i,j+1)>k$，链上肯定会存在一些点两边都够不到，转移$tmp[\max(i,j+1)]+=f[x][i]\times f[y][j]$。

初始状态$f[x][0]=1$，表示不考虑子树内的情况，选择自己的方案数为$1$；$f[x][k+1]=1$，表示自己本身不满足，但子结点都被满足的情况，主要是方便转移。

答案为$\sum_{i<=k}f[root][i]$。

时间复杂度$O(nk^2)$。

### 源代码：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<forward_list>
typedef long long int64;
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
const int N=101,K=41,mod=1e9+7;
int k,f[N][K],tmp[K];
std::forward_list<int> e[N];
inline void add_edge(const int &u,const int &v) {
	e[u].push_front(v);
	e[v].push_front(u);
}
void dfs(const int &x,const int &par) {
	f[x][0]=f[x][k+1]=1;
	for(int &y:e[x]) {
		if(y==par) continue;
		dfs(y,x);
		std::fill(&tmp[0],&tmp[k*2]+1,0);
		for(register int i=0;i<=k*2;i++) {
			for(register int j=0;j<=k*2;j++) {
				(tmp[i+j<=k*2?std::min(i,j+1):std::max(i,j+1)]+=(int64)f[x][i]*f[y][j]%mod)%=mod;
			}
		}
		std::copy(&tmp[0],&tmp[k*2]+1,f[x]);
	}
}
int main() {
	const int n=getint();k=getint();
	for(register int i=1;i<n;i++) {
		add_edge(getint(),getint());
	}
	dfs(1,0);
	int ans=0;
	for(register int i=0;i<=k;i++) {
		(ans+=f[1][i])%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：duyi (赞：2)

# CF736C Ostap and Tree

[题目链接](https://codeforces.com/contest/736/problem/C)

树形DP。设 $dp[u][x][y]$ 表示点 $u$ 的子树外与 $u$ 最近的黑点距离为 $x$，子树内与 $u$ 最近的黑点距离为 $y$，此时子树内的染色方案数。特别地，我认为“子树外”是包含 $u$ 的，“子树内”是不含 $u$ 的，所以 $0\leq x\leq k+1,1\leq y\leq k+1$。其中 $k+1$ 表示大于 $k$ 或根本不存在。

每次加入一个儿子$v$，做转移。转移时枚举儿子子树内与它最近的点的距离 $z$（显然，一定要满足 $z+1\geq y$）。那么从 $dp[u][x][y]$ 和 $dp[v][?][z]$ 转移到 $dp'[u][x][y]$。其中 $?$ 也就是 $v$ 子树外距离 $v$ 最近的黑点的距离，要么是 $x+1$ 要么是 $y+1$ 要么是 $0$（$v$ 自己就是一个黑点）。分类讨论一下即可转移。

根据 DP 数组的定义，我们枚举了 $z+1\geq y$，但我们还需要保证，至少有一个节点满足 $z+1=y$。所以可以在后面再加一维 $0/1$，表示是否已经存在至少一个节点，取到了等号。

还有一个小问题，我们说 $v$ 子树外距离 $v$ 最近的点，距离可以是 $x+1$ 或 $y+1$ 或 $0$，但这个 $y+1$ 是值得怀疑的。因为根据 DP 数组的定义，一种可能存在的特殊情况是，$v$ 恰好就是 $u$ 的唯一一个取到 $z+1=y$ 的儿子，那么此时就没有 $y+1$ 这个转移了。可以通过把最后一维 $0/1$ 改成 $0/1/2$ 来确定 $v$ 后面还有没有其它 $z+1=y$ 的儿子，这样就解决了这个小问题。

时间复杂度 $O(nk^3)$。

参考代码（细节较多，建议自行思考）：

```cpp
//problem:CF736C
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
 
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
 
const int MAXN = 100, MAXK = 20;
const int MOD = 1e9 + 7;
inline int mod1(int x){return x<MOD?x:x-MOD;}
inline int mod2(int x){return x<0?x+MOD:x;}
inline void add(int& x,int y){x=mod1(x+y);}
inline void sub(int& x,int y){x=mod2(x-y);}
inline int pow_mod(int x,int i){int y=1;while(i){if(i&1)y=(ll)y*x%MOD;x=(ll)x*x%MOD;i>>=1;}return y;}
 
int n, lim;
 
struct EDGE{int nxt,to;}edge[MAXN*2+5];
int head[MAXN+5],tot;
inline void add_edge(int u,int v){edge[++tot].nxt=head[u],edge[tot].to=v,head[u]=tot;}
 
 
int dp[MAXN + 5][MAXK + 5][MAXK + 5][3], tmp[MAXK + 5][MAXK + 5][3];
void dfs(int u, int fa) {
	for(int j = 0; j <= lim + 1; ++j) {
		for(int k = 1; k <= lim + 1; ++k) {
			if(j > lim && k > lim) continue;
			if(k <= lim) dp[u][j][k][0] = 1;
			else dp[u][j][k][1] = 1;
		}
	}
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(v == fa) continue;
		dfs(v, u);
		for(int j = 0; j <= lim + 1; ++j) {
			for(int k = 0; k <= lim + 1; ++k) {
				tmp[j][k][0] = tmp[j][k][1] = tmp[j][k][2] = 0;
			}
		}
		for(int j = 0; j <= lim + 1; ++j) {
			for(int k = 1; k <= lim + 1; ++k) {
				if(j > lim && k > lim) continue;
				for(int l = max(1, k - 1); l <= lim + 1; ++l) {
					if(k < j) {
						if(l + 1 == k) {
							add(tmp[j][k][2], (ll)dp[u][j][k][0] * dp[v][min(j + 1, lim + 1)][l][1] % MOD);
						} else {
							add(tmp[j][k][2], (ll)dp[u][j][k][2] * dp[v][k + 1][l][1] % MOD);
						}
						add(tmp[j][k][0], (ll)dp[u][j][k][0] * dp[v][k + 1][l][1] % MOD);
						add(tmp[j][k][1], (ll)dp[u][j][k][1] * dp[v][k + 1][l][1] % MOD);
					} else {
						if(l + 1 > k) {
							add(tmp[j][k][2], (ll)dp[u][j][k][2] * dp[v][min(j + 1, l + 1)][l][1] % MOD);
						}
						add(tmp[j][k][l + 1 == k], (ll)dp[u][j][k][0] * dp[v][min(j + 1, lim + 1)][l][1] % MOD);
						add(tmp[j][k][1], (ll)dp[u][j][k][1] * dp[v][min(j + 1, lim + 1)][l][1] % MOD);
					}
					if(k == 1) {
						add(tmp[j][1][1], (ll)dp[u][j][1][0] * dp[v][0][l][1] % MOD);
						add(tmp[j][1][1], (ll)dp[u][j][1][1] * dp[v][0][l][1] % MOD);
					}
				}
			}
		}
		for(int j = 0; j <= lim + 1; ++j) {
			for(int k = 1; k <= lim + 1; ++k) {
				dp[u][j][k][0] = tmp[j][k][0];
				dp[u][j][k][1] = tmp[j][k][1];
				dp[u][j][k][2] = tmp[j][k][2];
			}
		}
	}
	for(int j = 0; j <= lim + 1; ++j) {
		for(int k = 1; k <= lim + 1; ++k) {
			add(dp[u][j][k][1], dp[u][j][k][2]);
		}
	}
}
int main() {
	cin >> n >> lim;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1; i <= lim + 1; ++i) {
		add(ans, dp[1][lim + 1][i][1]);
		add(ans, dp[1][0][i][1]);
	}
	cout << ans << endl;
	return 0;
}
```









---

## 作者：cqbzlzm (赞：1)

### Description

对一棵树染色，要求距每个点最近的染色点的距离不超过 k 的染色方法总和。

$n\leq 100,k\leq 20$。

### Solution

sol1：

令 $f_{u,j}$ 表示以 $u$ 为根的子树合法，子树内离 $u$ 最近的染色点距离为 $j$。

令 $g_{u,j}$ 表示以 $u$ 为根的子树非法，子树内最远的非法点的距离为 $j$。

1. 合并 $f_{u,i}$ 和 $g_{v,j}$：（$i+j+1\leq k$）$f_{u,i}\leftarrow f_{u,i}\times g_{v,j}$，（$i+j+1>k$）$g_{u,j+1}\leftarrow f_{u,i}\times g_{v,j}$。
2. 合并 $f_{u,i}$ 和 $f_{v,j}$：$f_{u,\min(i,j+1)}\leftarrow f_{u,i}\times f_{v,j}$。

3. 合并 $g_{u,i}$ 和 $f_{v,j}$：（$i+j+1\leq k$）$f_{u,j+1}\leftarrow g_{u,i}\times f_{v,j}$，（$i+j+1>k$）$g_{u,i}\leftarrow g_{u,i}\times f_{v,j}$。
4. 合并 $g_{u,i}$ 和 $g_{v,j}$：$g_{u,\max(i,j+1)}\leftarrow g_{u,i}\times g_{v,j}$。

时间复杂度：$O(n\times k^2)$。

sol2：

记 $d_i$ 为 $i$ 到最近染色点的距离。

容易发现一个合法的 $d$ 序列唯一对应了一个染色方案。

合法条件：

1. 相邻两个 $d$ 相差不超过 1。
2. 对所有 $d_u>0$，存在邻点 $v$，$d_v=d_u-1$。

然后就好办了，令 $dp_{i,j,0/1}$ 表示 $i$ 子树，$d_i=j$，是否存上邻点 $v$ 满足 $d_v=d_u-1$。

时间复杂度：$O(n\times k)$。

### Code

sol2：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 100, MAXM = 20, mod = 1000000007;
int n, k;
vector<int> G[MAXN + 5];
int dp[MAXN + 5][MAXM + 5][2];
void dfs(int u, int fa) {
    for (int i = 1; i <= k; i ++) dp[u][i][0] = 1;
    dp[u][0][1] = 1;
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        for (int j = 1; j <= k; j ++) {
            dp[u][j][1] = (dp[u][j][1] * (((dp[v][j + 1][0] + dp[v][j + 1][1]) % mod) % mod + dp[v][j][1] + dp[v][j - 1][1]) % mod + dp[u][j][0] * dp[v][j - 1][1] % mod) % mod;
            dp[u][j][0] = (dp[u][j][0] * (((dp[v][j + 1][0] + dp[v][j + 1][1])  % mod) % mod + dp[v][j][1]) % mod) % mod;
        }
        dp[u][0][1] = dp[u][0][1] * (((dp[v][1][0] + dp[v][1][1]) + dp[v][0][1]) % mod) % mod;
    }
    return ;
}
signed main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i < n; i ++) {
        int x, y; scanf("%lld%lld", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, 0);
    int res = 0;
    for (int t = 0; t <= k; t ++) (res += dp[1][t][1]) %= mod;
    cout<<res;
    return 0;
}
```

---

