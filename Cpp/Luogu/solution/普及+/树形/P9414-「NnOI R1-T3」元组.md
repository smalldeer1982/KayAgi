# 「NnOI R1-T3」元组

## 题目背景

小 L 很喜欢树，很喜欢 $ \operatorname{LCA} $，很喜欢有序元组，于是有了这样一道题。

## 题目描述

对于一棵 $ n $ 点有根树（根为 $ 1 $），定义有序 $ p $ 元组 $ (a_1,a_2,......,a_p) $ 为 $ k $ 级 $ \operatorname{LCA} $ $ p $ 元组当且仅当：

* $ 1 \le a_1<a_2<......<a_p \le n $

* 存在 $ x $ 使得对于任意有序严格递增 $ k $ 元组 $ b \subseteq a $ 均满足 $ \operatorname{LCA}_{i=1}^{k}\{b_i\} = x $。

注意，$ \operatorname{LCA}(x,y) $ 指树上 $ x $ 点和 $ y $ 点的最近公共祖先，且 $ \operatorname{LCA}_{i=1}^{k}\{b_i\} $ 指的是所有的 $ b_i $ 的 $ \operatorname{LCA} $。

求出 $ k $ 级 $ \operatorname{LCA} $ $ p $ 元组的个数，对 $ 10^9+7 $ 取模。

## 说明/提示

**【样例 1 解释】**

对于样例 $ 1 $，我们发现符合要求的 $ 4 $ 元组只有 $ (3,4,5,6) $。

**【数据规模与约定】**

对于 $ 100\% $ 的数据，$ 2 \le n \le 5000 $，$ 2 \le k \le p \le n $。

**提示：本题开启捆绑测试。**

* Subtask 1（10 pts）：$ n \le 10 $。
* Subtask 2（20 pts）：$ n \le 20 $。
* Subtask 3（30 pts）：$ n \le 500 $。
* Subtask 4（10 pts）：$ 1 $ 和所有点存在直接连边。
* Subtask 5（30 pts）：无特殊限制。

**【贡献名单】**

data&check：EstasTonne。（主题库里这个题下一个题号的出题人）

## 样例 #1

### 输入

```
6 4 3
1 2
2 3
3 4
3 5
3 6```

### 输出

```
1```

## 样例 #2

### 输入

```
6 3 2
1 2
1 3
1 4
1 5
1 6```

### 输出

```
20```

## 样例 #3

### 输入

```
6 4 2
1 2
1 3
2 4
2 5
3 6```

### 输出

```
0```

# 题解

## 作者：Bulyly (赞：5)

- 很合胃口的一道题。


------------
- 考虑枚举每个点 $u$ 为 LCA 时对方案数产生的贡献。显然此时满足要求的点应该在 $u$ 的子树当中。将其子树中点对形成的 LCA 分为 $u$ 与非 $u$ 两类。

- 根据鸽巢原理可得，一个符合条件的 $p$ 元组应该最多只能出现 $k-1$ 个 LCA 为非 $u$ 类。于是问题转换为找非 $u$ 两类集合的数量。

- 更进一步，显然以子节点为根的树中任意点对才是非 $u$ 类的，所以一个子树中我们最多可选 $k-1$ 个。令 $f[u][t]$ 表示以 $u$ 为 LCA ,再子树中取 $t$ 个点的方案数。答案为 $f[u][p]$。用树上背包实现。

下附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5010,mod=1e9+7;
int n,p,k;
vector<int> e[N];
int sz[N];
int f[N][N];
ll ans;

void dfs(int u,int fa) {
	sz[u]=1,f[u][0]=f[u][1]=1;
	for(int j:e[u]) {
		if(j==fa)  continue;
		dfs(j,u);
		int psz=sz[u];
		sz[u]+=sz[j];
		for(int d=min(sz[u],p);d>=1;d--)
			for(int t=max(1,d-psz);t<=min(min(k-1,d),sz[j]);t++)
				f[u][d]+=1ll*f[u][d-t]*f[j][t]%mod,
				f[u][d]%=mod;
	}
	ans+=f[u][p]; 
	ans%=mod;
}

int main() {
	
	scanf("%d%d%d",&n,&p,&k);
	for(int i=1;i<n;i++) {
		int a,b;
		cin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1,-1);
	cout<<ans<<endl;
}
```
完结撒花~

---

## 作者：船酱魔王 (赞：4)

# [NnOI-R1] T3 元组 官方题解

## 题意回顾

对于 $ n $ 点，以 $ 1 $ 为根的树，求出有多少个 $ p $ 元点集的任意 $ k $ 个点组成的子集 $ \operatorname{LCA} $ 相等。

$ 2 \le n \le 5000 $。

## 分析

显然不能枚举元组具体内容，故考虑枚举 $ \operatorname{LCA} $，设其为 $ u $ 点。设一个点 $ u $ 的子树大小（包含其本身）为 $ sz_u $。

首先点肯定在 $ u $ 的子树中。

考虑 $ \operatorname{LCA} $ 的本质，当 $ u $ 的子结点 $ v $ 子树包含了元组中的达到 $ k $ 个结点时，这 $ k $ 个结点的 $ \operatorname{LCA} $ 为 $ v $ 或其子结点，不满足要求。当不存在 $ u $ 的子结点 $ v $ 包含元组中达到 $ k $ 个结点时，显然任意 $ k $ 个元组内结点要么包含 $ u $，要么位于不同子树，均符合要求。

则 $ u $ 的任意子结点的子树中不包含达到 $ k $ 个元组内结点为 $ \operatorname{LCA} $ 为 $ u $ 的元组合法的充要条件，对每个结点背包动态规划即可。

时间复杂度为 $ O(n^2) $，注意背包 DP 循环上下界的设定避免退化为 $ O(n^3) $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int mod = 1e9 + 7;
const int N = 5005;
int n, p, k;
vector<int> g[N];
int c[N][N];
int dp[N][N];
int sz[N];
long long ans = 0;
void dfs(int u, int fath) {
	sz[u] = 1;
	for(int j = 2; j <= p; j++) {
		dp[u][j] = 0;
	}
	dp[u][0] = dp[u][1] = 1;
	int v;
	int tmp;
	for(int i = 0; i < g[u].size(); i++){
		v = g[u][i];
		if(v == fath) {
			continue;
		}
		dfs(v, u);
		for(int j = min(sz[u], p); j >= 0; j--) {
			tmp = min(sz[v], min(k, p - j));
			for(int l = 1; l <= tmp; l++) {
				dp[u][j + l] += (long long)dp[u][j] * dp[v][l] % mod;
				dp[u][j + l] %= mod;
			}
		}
		sz[u] += sz[v];
	}
	ans += dp[u][p];
	ans %= mod;
}
int main() {
	scanf("%d%d%d", &n, &p, &k);
	k--;
	int x, y;
	for(int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Lysea (赞：1)

### [P9414 「NnOI R1-T3」元组](https://www.luogu.com.cn/problem/P9414)

好题，没独立做出来，主要是没想到第一步。

其实原问题就等价于：枚举每个节点作为 LCA。对于每个节点 $i$，选择它子树中的 $q$ 个点，且满足任意儿子节点子树中选择点的总数不超过 $k-1$。

要选择 $i$ 子树中的点是因为若一个点不在子树内，它与其他点的点对的 LCA 就一定不是 $i$。

要求任意儿子节点子树中选择点的总数不超过 $k-1$，是因为假如不符合要求，那么一定存在 $k$ 个点的 LCA 为其他节点，而非 $i$。

因此这个问题就转化为了一个树上背包问题。

注意 $n\le 5000$，需要将边界设严格，防止复杂度退化至 $O(n^3)$。

具体地，令 $y$ 为 $x$ 的儿子节点，$dp_{i,j}$ 表示从 $i$ 的子树中选择 $j$ 个点且满足任意儿子节点子树中选择点的总数不超过 $k-1$，于是便有：

$$dp_{x,j}=dp_{x,j}+dp_{y,q}\times dp_{x,j-q}$$

其中 $q$ 表示从 $y$ 子树中选择的节点数，$j$ 表示 $x$ 子树中共要选择的节点数。

我们可以得到以下不等关系（下文中 $siz_x$ 已经累加过 $siz_y$）：

- $q<k$

- $q\le j$

- $q\le siz_y$

- $j-q\le siz_x-siz_y$（$i$ 前几棵子树共 $siz_x-siz_y$ 个点）

- $j\le siz_x$

- $j\le p$

- $j,q\ge 1$

由此可以得到 $1\le j\le\min\{siz_x,p\}$，$\max\{1,j+siz_y-siz_x\}\le q\le \min\{\min\{j,k-1\},siz_y\}$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 5005
#define INF 1e18
using namespace std;
struct star{
    int next,to;
}e[N<<1];
const int M=1e9+7;
int n,p,k,head[N],cnt,siz[N],ans,dp[N][N];
void add(int u,int v){
    e[++cnt].next=head[u];
    head[u]=cnt;
    e[cnt].to=v;
}
void dfs(int x,int f){
    siz[x]=1,dp[x][0]=dp[x][1]=1;
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to;
        if(y==f) continue;
        dfs(y,x),siz[x]+=siz[y];
        for(int j=min(siz[x],p);j;j--){
            for(int q=max(1ll,j+siz[y]-siz[x]);q<=min(min(j,k-1),siz[y]);q++){
                dp[x][j]=(dp[x][j]+
                dp[y][q]*dp[x][j-q]%M)%M;
            }
        }
    }
    ans=(ans+dp[x][p])%M;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>p>>k;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
```

多提几个本人遇到的坑点：

1. 双向边开双倍空间。

2. $dp_{x,0}$ 要设为 $1$，方便后面处理没选满 $k$ 个点，所有点出自同一颗儿子节点子树的情况。

---

## 作者：云浅知处 (赞：1)

考虑枚举点集的 $\text{LCA}$，设为 $u$，那么方案数相当于要在 $u$ 的子树内放若干个点，但每个子树内不能放 $\ge k$ 个点。

我们只需要把 $u$ 的子树都拎出来，设它们的大小为 $s_1,\cdots,s_k$，设 $f(i,j)$ 表示考虑了前 $i$ 个子树，放了 $j$ 个点的方案数，有

$$
f(i,j)=\sum_{x=0}^{\min(k-1,s_i)}f(i-1,j-x)\times\binom{s_i}{x}
$$

初值为 $f(0,0)=f(0,1)=1$，含义为可以选择点 $u$ 或不选。

看上去直接做的复杂度是 $O(n^3)$，需要使用 NTT 等技巧优化转移。但注意到该过程类似树上背包，我们暴力地进行转移，总复杂度就是 $O(n^2)$。

只需要预处理组合数。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=5005;
int f[2][N],n,k,fa[N],p,sz[N],C[N][N],ans;
vector<int>G[N];

void dfs(int u){sz[u]=1;for(int v:G[u])if(v!=fa[u])fa[v]=u,dfs(v),sz[u]+=sz[v];}
void calc(int u){
	memset(f,0,sizeof(f));
	int cur=0;f[cur][0]=f[cur][1]=1;int now=1;
	for(int v:G[u]){
		if(v==fa[u])continue;
		int w=min(k-1,sz[v]);
		memset(f[cur^1],0,sizeof(f[cur^1]));
		for(int i=0;i<=now;i++){
			for(int j=0;j<=w;j++)add(f[cur^1][i+j],1ll*f[cur][i]*C[sz[v]][j]%mod);
		}
		now+=w,cur^=1;
	}
	add(ans,f[cur][p]);
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read(),p=read(),k=read();
	for(int i=2;i<=n;i++){
		int u=read(),v=read();
		G[u].emplace_back(v),G[v].emplace_back(u);
	}
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)Mod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	dfs(1);for(int i=1;i<=n;i++)calc(i);
	cout<<ans<<endl;

	return 0;
}
```

---

