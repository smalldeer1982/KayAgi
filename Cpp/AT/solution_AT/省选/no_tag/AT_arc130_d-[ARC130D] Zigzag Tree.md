# [ARC130D] Zigzag Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc130/tasks/arc130_d

$ N $ 頂点からなる木が与えられます。頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 番目の辺は頂点 $ a_i $ と $ b_i $ を結んでいます。

正整数列 $ P\ =\ (P_1,\ P_2,\ \ldots,\ P_N) $ であって、以下の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ 1\leq\ P_i\leq\ N $
- $ i\neq\ j $ ならば $ P_i\neq\ P_j $
- $ 1\leq\ a,\ b,\ c\leq\ N $ に対して頂点 $ a $ と 頂点 $ b $、頂点 $ b $ と頂点 $ c $ がともに隣接しているならば、$ P_a\ <\ P_b\ >\ P_c $ または $ P_a\ >\ P_b\ <\ P_c $ が成り立つ。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3000 $
- $ 1\leq\ a_i,\ b_i\leq\ N $
- 入力されるグラフは木である

### Sample Explanation 1

条件を満たす $ P $ は以下の $ 4 $ 通りです。 - $ P\ =\ (1,\ 3,\ 2) $ - $ P\ =\ (2,\ 1,\ 3) $ - $ P\ =\ (2,\ 3,\ 1) $ - $ P\ =\ (3,\ 1,\ 2) $

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
12```

## 样例 #3

### 输入

```
6
1 2
2 3
3 4
4 5
5 6```

### 输出

```
122```

## 样例 #4

### 输入

```
9
8 5
9 8
1 9
2 5
6 1
7 6
3 8
4 1```

### 输出

```
19080```

# 题解

## 作者：Minecraft万岁 (赞：9)

[可能更好的阅读体验](https://www.cnblogs.com/FireAspect/p/17298350.html) 

[题目链接](https://atcoder.jp/contests/arc130/tasks/arc130_d)    
考虑这棵树在满足条件下是什么样子的？   

![Picture 1](https://s1.imagehub.cc/images/2023/04/08/d2a100629edb24c1cbcbea5d72b103ea.png)  

我们发现如果对于一棵树黑白染色，黑色表示周围的点大于自身，白色的点反之，是满足条件的。同时，将黑白点反色也是满足条件的。

我们考虑进行 $\text{dp}$，设 $dp_{i,j,0/1}$ 表示以点 $i$ 为根的子树，$i$ 点权值的排名是 $j$，且 $i$ 点颜色是黑或白的方案数。

![Picture 2](https://s1.imagehub.cc/images/2023/04/08/ab52705e986b4044a6c4340f287a55f8.png)

以 $x$ 点为白点为例，考虑将子树 $v$ 合并到 $x$ 的过程中前 $t$ 个点插入到了 $x$ 前，剩余的 $sz[v] - t$ 个点在 $x$ 后。那么此时转移为   
$$dp[x][i+t][1] += \binom{i-1+t}{t} \binom{sz[x]-i+sz[v]-t}{sz[v]-t} \times dp[x][i][1] \times dp[v][j][0](t \geq j)$$    
对于 $x$ 点是黑点的转移同理为
$$dp[x][i+t][0] += \binom{i-1+t}{t} \binom{sz[x]-i+sz[v]-t}{sz[v]-t} \times dp[x][i][0] \times dp[v][j][1] (t \leq j-1)$$   
此时 $dp$ 的转移复杂度为 $O(n^3)$，无法通过。

考虑枚举 $t$ 算所有能转移到 $t$ 的 $j$ 的贡献，式子改写为  
$$dp[x][i+j][1] += \binom{i-1+j}{j} \binom{sz[x]-i+sz[v]-j}{sz[v]-j} \times dp[x][i][1] \times pre[j] $$  
$$dp[x][i+j][0] += \binom{i-1+j}{j} \binom{sz[x]-i+sz[v]-j}{sz[v]-j} \times dp[x][i][0] \times suc[j+1] $$   
其中 
$$pre[j]= \sum_{k=1}^{j} dp[v][k][0]$$  
$$suc[j]= \sum_{k=j+1}^{sz[v]} dp[v][k][1]$$   
复杂度为 $O(n^2)$，可以通过。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=998244353;
const int N=3005;
struct node{
	int nxt;int to;
}e[N*2];
int head[N],tot;
int n,rx,ry;
int fa[N],sz[N];
int dp[N][N][2],pre[N],suc[N];
int g[N][2],ans;
int fac[N],ifac[N];
inline void read(int &x) 
{
	int f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
} 
inline int mn(int _x,int _y){return _x<_y?_x:_y;}
inline int mx(int _x,int _y){return _x>_y?_x:_y;}
inline int ab(int _x){return _x<0?-_x:_x;}
inline void add(int from,int to){
	e[++tot].to=to;e[tot].nxt=head[from];head[from]=tot;
}
inline int C(int n,int m){
	if(n<m) return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int qpow(int base,int cnt){
	int rest=1;
	while(cnt){
		if(cnt&1) rest=1ll*rest*base%mod;
		base=1ll*base*base%mod;
		cnt>>=1;
	}
	return rest;
}
inline void dfs(int x){
	sz[x]=1;
	dp[x][1][0]=dp[x][1][1]=1;
	for(int ei=head[x];ei;ei=e[ei].nxt){
		int v=e[ei].to;
		if(v==fa[x]) continue;
		fa[v]=x;dfs(v);
		for(int j=0;j<=sz[v]+1;j++) pre[j]=suc[j]=0;
		for(int j=1;j<=sz[v];j++) pre[j]=(pre[j-1]+dp[v][j][0])%mod;
		for(int j=sz[v];j>=1;j--) suc[j]=(suc[j+1]+dp[v][j][1])%mod;
		for(int i=1;i<=sz[x];i++){
			for(int j=0;j<=sz[v];j++){
            	//dp
				g[i+j][0]=(g[i+j][0]+1ll*C(i-1+j,j)*C(sz[x]-i+sz[v]-j,sz[v]-j)%mod*dp[x][i][0]%mod*suc[j+1]%mod)%mod;
				g[i+j][1]=(g[i+j][1]+1ll*C(i-1+j,j)*C(sz[x]-i+sz[v]-j,sz[v]-j)%mod*dp[x][i][1]%mod*pre[j]%mod)%mod;
			}
		}
		sz[x]+=sz[v];
		for(int i=0;i<=sz[x];i++){
			dp[x][i][0]=g[i][0];dp[x][i][1]=g[i][1];
			g[i][0]=g[i][1]=0;
		}
	}
//	for(int i=1;i<=sz[x];i++) printf("dp[%d][%d] [0]=%d [1]=%d\n",x,i,dp[x][i][0],dp[x][i][1]);
	return ;
}
int main()
{
	read(n);
	for(int i=1;i<n;i++){
		read(rx);read(ry);
		add(rx,ry);add(ry,rx);
	}
	fac[0]=1;for(int i=1;i<=n+1;i++) fac[i]=1ll*i*fac[i-1]%mod;
	ifac[n+1]=qpow(fac[n+1],mod-2);
	for(int i=n;i>=0;i--) ifac[i]=1ll*(i+1)*ifac[i+1]%mod;

	dfs(1);
	for(int i=1;i<=n;i++){//枚举根节点的排名并累加答案
		ans=(ans+dp[1][i][0])%mod;
		ans=(ans+dp[1][i][1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}  
```


---

## 作者：wanggk (赞：3)

[cnblogs](https://www.cnblogs.com/wanggk/articles/-/ARC130D)

### 题意

给定一棵树，统计满足条件的点权序列的数量：

- 点权为 $1$ 到 $n$ 的排列。
- 对于任意点 $u$，其点权要么大于所有邻居，要么小于所有邻居。

$n \leq 3000$。

### 题解

我们称点权大于所有邻居的点为**大点**，点权小于所有邻居的点为**小点**。

一个点一定不会同时成为大小点，同一条边连接的两个点类型不同。

设 $f_{u,i,0/1}$ 表示以 $u$ 为根的子树，$u$ 在**子树内**排名为 $i$，点 $u$ 为小点或大点的方案数。

发现一定有 $f_{u,i,0}=f_{u,i,1}$，因此可以把最后一维去掉。

类似树上背包的转移，设 $g_i=f_{u,i}$ 为儿子 $v$ 向 $u$ 转移前的 $f_u$。

对于每个 $f_{u,j}$，枚举加入 $v$ 子树前 $u$ 的排名 $x$，有：

$$f_{u,j}= \sum_{\max(j-sz_v,1) \leq x \leq \min(j-1,sz_u)} C_{j-1}^{x-1} C_{sz_u+sz_v-j}^{sz_u-x}g_x \sum_{1 \leq y \leq j-x} f_{v,sz_v+1-y}$$

- 这篇题解的写法上，上文式子中的 $sz_u$ 并没有算入 $sz_v$。
- 第一个组合数：总共有 $j-1$ 个小于 $u$ 的排名的，选出 $x-1$ 个给加入 $v$ 子树前的点。
- 第二个组合数，同理，总共有 $sz_u+sz_v-j$ 个大于 $u$ 的排名的。
- 第二个求和中 $y$ 表示枚举 $v$ 子树中 $v$ 的排名，$sz_v+1-y$ 是做了一个翻转，因为我们把最后一维去掉了。
- 注意 $x,y$ 的枚举边界，边界不对的话复杂度就会错。和树上背包是同样的道理。

容易发现第二个求和可以前缀和优化：

$$f_{u,j}= \sum_{\max(j-sz_v,1) \leq x \leq \min(j-1,sz_u)} C_{j-1}^{x-1} C_{sz_u+sz_v-j}^{sz_u-x}g_x pre_{j-x}$$

最终的答案就是 $\sum f_{1,i}$。

### 代码

完整代码见[提交记录](https://atcoder.jp/contests/arc130/submissions/me)。

```cpp
void dfs(int u,int fa)
{
    for(int v:ve[u]) 
        if(v^fa) dfs(v,u);
    sz[u]=1;
    f[u][1]=1ll;
    for(int v:ve[u])
    {
        if(v==fa) continue;
        memcpy(g,f[u],sizeof(ll)*(sz[u]+1));
        memset(f[u],0,sizeof(ll)*(sz[u]+sz[v]+1));
        For(j,1,sz[v])
            pre[j]=(pre[j-1]+f[v][sz[v]+1-j])%mod;
        For(j,1,sz[u]+sz[v])
            For(x,max(j-sz[v],1),min(sz[u],j-1)){
                ll tmp=C(j-1,x-1)*C(sz[u]+sz[v]-j,sz[u]-x)%mod;
                qadd(f[u][j],tmp*g[x]%mod*pre[j-x]%mod);
            }
        sz[u]+=sz[v];
    }
}
```

---

## 作者：Reunite (赞：2)

我们称一个点是小的，当且仅当它小于所有相邻点；一个点是大的，当且仅当它大于所有相邻点。

转化一下题意，这个三点链的限制就是要求按照每个点的深度分层，所有奇数深度点都是大点，偶数深度点都是小点，或相反。

根据排列题经典套路，设 $f_{u,i}$ 为 $u$ 是小点，$u$ 在子树内的排名为 $i$ 的方案数，$g_{u,i}$ 类似地，为 $u$ 是大点排名为 $i$ 的方案数。

对于转移，先考虑子树之间的合并。如果 $u$ 为大点，则所有儿子为小点，那么只有点权最大的儿子有限制，合并两棵子树 $x,y$ 时，分别钦定 $x$ 和 $y$ 的相对大小。若 $x>y$，则枚举 $y$ 子树内有多少点 $<x$，然后两部分组合数互插，其他情况同理，我们有：

$$h_{t}=\sum_{j+k=t}^{j\le sz_v,1\le k\le sz_u}\sum _{i\le k} f_{x,i}\times f_{y,j}\times \binom{k+j-1}{j-1}\binom{sz_v-j+sz_u-k}{sz_v-j}$$

$$h_{t}=\sum_{i+k=t}^{i\le sz_u,1\le k\le sz_v}\sum _{j\le k} f_{x,i}\times f_{y,j}\times \binom{k+i-1}{i-1}\binom{sz_u-i+sz_v-k}{sz_u-i}$$

同理，对 $g$ 的合并：

$$t_{h}=\sum_{j+k=h}^{j\le sz_v,0\le k\le sz_u}\sum _{k< i \le sz_u}^{sz_u} g_{x,i}\times g_{y,j}\times \binom{k+j-1}{j-1}\binom{sz_v-j+sz_u-k}{sz_v-j}$$

$$t_{h}=\sum_{i+k=h}^{i\le sz_u,0\le k\le sz_v}\sum _{k<j\le sz_v}^{sz_v} g_{x,i}\times g_{y,j}\times \binom{k+i-1}{i-1}\binom{sz_u-i+sz_v-k}{sz_u-i}$$

然后发现和式后面只有 $f,g$ 里面用到了第二个求和符号里的枚举量，前后缀和优化即可做到 $n^2$。

最后考虑添加 $u$ 这个点的值插入进去，这个是简单的。总复杂度还是 $O(n^2)$，有一些上下界细节。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define int long long
#define mod 998244353
using namespace std;

int n;
int sz[3005];
int f[3005][3005];
int g[3005][3005];
int C[3005][3005];
vector <int> e[3005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void dfs(int u,int fa){
	sz[u]=1;
	int son=0;
	for(int v:e[u]){
		if(v==fa) continue;
		son++;
		dfs(v,u);
	}
	if(!son){
		f[u][1]=g[u][1]=1;
		return ;
	}
	son=0;
	for(int v:e[u]){
		if(v==fa) continue;
		son++;
		if(son==1){
			sz[u]=sz[v];
			for(int i=1;i<=sz[u];i++) f[u][i]=f[v][i],g[u][i]=g[v][i];
			continue;
		}
		int m=sz[u]+sz[v];
		int h[m+1]={0},t[m+1]={0};
		for(int i=1;i<=sz[u];i++)
			for(int j=1;j<=sz[v];j++){
				for(int k=i;k<=sz[u];k++)
					(h[k+j]+=f[u][i]*f[v][j]%mod*C[k+j-1][j-1]%mod*C[sz[v]-j+sz[u]-k][sz[v]-j])%=mod;
				for(int k=j;k<=sz[v];k++)
					(h[k+i]+=f[u][i]*f[v][j]%mod*C[k+i-1][i-1]%mod*C[sz[u]-i+sz[v]-k][sz[u]-i])%=mod;
			}
		for(int i=1;i<=sz[u];i++)
			for(int j=1;j<=sz[v];j++){
				for(int k=0;k<i;k++)
					(t[k+j]+=g[u][i]*g[v][j]%mod*C[k+j-1][j-1]%mod*C[sz[v]-j+sz[u]-k][sz[v]-j])%=mod;
				for(int k=0;k<j;k++)
					(t[k+i]+=g[u][i]*g[v][j]%mod*C[k+i-1][i-1]%mod*C[sz[u]-i+sz[v]-k][sz[u]-i])%=mod;
			}
		for(int i=1;i<=m;i++) f[u][i]=h[i],g[u][i]=t[i];
		sz[u]+=sz[v];
	}
	sz[u]++;
	int h[sz[u]+2]={0},t[sz[u]+2]={0};
	for(int i=1;i<sz[u];i++){
		for(int j=1;j<=sz[u];j++){
			if(j<=i) (h[j]+=g[u][i])%=mod;
			else (t[j]+=f[u][i])%=mod;
		}
	}
	for(int i=1;i<=sz[u];i++) f[u][i]=h[i],g[u][i]=t[i];
	return ;
}

signed main(){
	// freopen("qwq.in","r",stdin);
	in(n);
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=1;i<n;i++){
		int u,v;
		in(u),in(v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,0);
	int s=0;
	for(int i=1;i<=n;i++) (s+=f[1][i]+g[1][i])%=mod;
	printf("%lld\n",s);

	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑 $dp_{i,j,0/1}$ 表示确定 $i$ 子树内 $p$ 的顺序，$p_i$ 在其中排第 $j$ 个，钦定 $p_i$ 小于/大于周围值。

转移时，如果 $i$ 比周围大，那么其所有子树根都要比周围小。如果子树 $v$ 的 $p_v$ 在其子树内排 $j_v$，也就是计算在了 $dp_{v,j_v,0}$ 之中，那么 $i$ 在 $p_v$ 子树中的排名 $j'_v\leq j_v$。以 $p_i$ 为分界线分别用组合数合并不同子树大于 $p_i$，小于 $p_i$ 的部分即可。$i$ 比周围小同理。

不难发现这样是 $O(n^3)$ 的，因为我们既要枚举 $j_v$ 和 $j'_v$。考虑优化，在最开始对 $dp_{v,j,0/1}$ 分别做后/前缀和即可。总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int C[3005][3005];
int dp[3005][3005][2],siz[3005];
vector<int> vc[3005];
void dfs(int now,int fa){
	dp[now][0][0]=dp[now][0][1]=1;
	siz[now]=0;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		int tmp[3005][2]; memset(tmp,0,sizeof(tmp));
		for(int i=0;i<=siz[now];i++){
			for(int j=0;j<=siz[v];j++){
				(tmp[i+j][1]+=dp[now][i][1]*dp[v][j][0]%mod*C[i+j][i]%mod*C[siz[now]+siz[v]-i-j][siz[now]-i])%=mod;
				(tmp[i+j][0]+=dp[now][i][0]*dp[v][j][1]%mod*C[i+j][i]%mod*C[siz[now]+siz[v]-i-j][siz[now]-i])%=mod;
			}
		}
		siz[now]+=siz[v];
		for(int i=0;i<=siz[now];i++) dp[now][i][0]=tmp[i][0],dp[now][i][1]=tmp[i][1];
	}
	siz[now]++;
	if(now!=1){
		for(int i=siz[now];i>=0;i--) (dp[now][i][0]+=dp[now][i+1][0])%=mod;
		for(int i=siz[now];i>=1;i--) dp[now][i][1]=dp[now][i-1][1]; dp[now][0][1]=0;
		for(int i=1;i<=siz[now];i++) (dp[now][i][1]+=dp[now][i-1][1])%=mod;
	}
}
signed main(){
	for(int i=0;i<=3000;i++) C[i][0]=1;
	for(int i=1;i<=3000;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs(1,0);
	int ans=0;
	for(int i=0;i<=n;i++){
		(ans+=dp[1][i][0]+dp[1][i][1])%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

显然问题相当于要把整棵树重标号。

首先有一个粗略的观察：一个点要么小于其所有的邻居，要么大于其所有的邻居。我们下文称这两类点分别为大点与小点。

此时我们可能会想到钦定某个点是大点/小点。不过一个比较显然的事实是大点周围只会有小点，小点周围只会有大点，结合树是一张二分图可以得到大小点的分配方案本质上是树的一个黑白染色，可以对于每种黑白染色方案分别计算。

一个尝试就是考虑从 $1$ 到 $n$ 依次把标号填在树上的节点，小点必须是其与其邻居中第一个填的，大点必须是其与其邻居中最后一个填的。但是感觉这么考虑没有前途，毕竟太“全局观”了，不利于树上 DP 优化。

我们想一下怎么通过子树合并的角度来考虑。注意到子树间的合并本质上只是标号重新分配，转移只依赖子树 ``sze``，而方案的合法性只取决于相对大小。

于是可以令 $dp_{u,i}$ 为 $u$ 号点在子树中排名为 $i$ 的方案数。初始有 $dp_{u,1}=1$。

以钦定 $u$ 为极大点为例，则转移：

$$dp_{u,i+j} \leftarrow dp_{u,i}\binom{i-1+j}{i-1}\binom{sze_u-i+sze_v-j}{sze_u-i} \sum \limits_{k=1}^{j} dp_{v,j}$$

意义则为枚举 $v$ 子树中比 $u$ 小的有多少个节点，然后再枚举 $v$ 的排名。前缀和优化即可做到树上背包的 $O(n^2)$。

---

## 作者：wu__yue (赞：0)

## 前言
(这是我写的第一篇题解，~~这篇讲得很详细，适合我这样的蒟蒻~~。)

我还是太弱了，调了一下午才过，xzy 大佬说这题就是树形 dp 板子。

%%%% 膜拜 xzy 大佬，%%% 膜拜 @wangtairan114 大佬。



## 正文

### 题意 

  有一个 $n$ 个点的树，找出 $1∼n$ 的排列 $P$ 的个数，满足对于任意 $1\leq a,b,c\leq n$，其中点 $a$ 和点 $b$ 相邻，点 $b$ 和点 $c$ 相邻，都有  $ P_a\ <\ P_b\ >\ P_c $ 或 $ P_a\ >\ P_b\ <\ P_c $ 。对 $998244353$ 取模。

数据范围 $n\le 3000$。

### Solution
首先，这道题我们考虑树形 dp，我们设 $dp[i][j]$ 表示 $i$ 子树内 $i$ 这个点在子树内权值排名为 $j$ 的排列个数，为什么这样设呢，因为考虑这个限制，那么接下来的转移只会和 $i$ 点的值有关。

接下来我们考虑这个树的形态，显然是一层大的点（大的点指它大于所有相邻的点）一层小的点一层大的点这样交替（类似黑白染色），那么显然有两种情况，就是根节点是大的或者小的，但这两种情况显然是本质一样的，所以我们钦定 $depth$ 是奇数时的点是小的，然后只需要把算出来的答案乘二就行啦。

最后考虑转移，比如我们现在要求 $u$ 的 dp 值，假设现在 $u$ 已经合并了一部分子树现在大小是 $size[u]$，$v$ 子树大小为 $size[v]$（我们在树形 dp 的过程中算 $size$），那么我们接下来要考虑 $u$ 比 $v$ 小的限制（$u$ 比 $v$ 大的情况类似），所以就相当于现在有两个有序的排列长度为 $size[u]$ 和 $size[v]$，要把 $v$ 的这个排列插入到 $u$ 中，保证 $v$ 插在 $u$ 后面，很自然的可以想到枚举 $u$ 的排名，$v$ 的排名，那么只要仅把 $v$ 前的数插到 $u$ 前就可以保证，所以再枚举一下 $v$ 里几个数插到 $u$ 前就可以了。

但这样转移是 $O({n^3})$ 的显然不能过，考虑优化，只枚举 $u$ 的排名和 $v$ 里几个数插到 $u$ 前，假设插 $j$ 个，那么此时所有 $v$ 的排名大于 $j$ 的情况都是合法的，通过对 $dp[v]$ 后缀和（$u$ 比 $v$ 小时是前缀和）即可 $O(n^2)$ 转移。

最终的 dp 式子排列组合算一下就行啦，~~都来切紫题了肯定会吧。~~

我们还是讲一下式子，$g$ 为前后缀和，$u$ 的排名是 $i$，选 $j$ 个数插到 $u$ 前面，后面这两个组合数分别是把 $v$ 前面 $j$ 个数插到 $u$ 前面 $(i-1)$ 个数里的方案数，和把 $v$ 及其后面的 $(size[v]-j)$ 个数插进 $(size[u]-i)$ 个数里的方案数，然后此时 $u$ 新的排名是 $i+j$。

$$

dp[u][i+j]=dp[u][i]\cdot g[v][j]\cdot\binom{i-1+j}{j}\binom{size[u]-i+size[v]-j}{size[v]-j}

$$



```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=3000+100;
const int mod=998244353;
int n,m,k,t,cnt,ans,x,y,z,p[N],inv[N],siz[N],dep[N],f[N],ff[N];
int dp[N][N];
vector<int> g[N];
int C(int n,int m){
    if(n<m||n<0||m<0) return 0;
    return p[n]*inv[m]%mod*inv[n-m]%mod;
}
void dfsinit(int u,int fa){//预处理dep
    dep[u]=dep[fa]+1;
    for(auto v:g[u]){
        if(v==fa) continue;
        dfsinit(v,u);
    }
    return ;
}
void dfs(int u,int fa){
    siz[u]=1,dp[u][1]=1;
    for(int v:g[u]){
        if (v==fa) continue;
        dfs(v,u);

        if(dep[u]&1){//u是小的点
            fill(f,f+siz[u]+siz[v]+1,0);
            fill(ff,ff+siz[v]+1,0);
            ff[siz[v]]=dp[v][siz[v]];
            for(int i=siz[v]-1;i>=1;i--){
                ff[i]=(dp[v][i]+ff[i+1])%mod;//后缀和
                
            }
            for(int i=1;i<=siz[u];i++){
                for(int j=0;j<siz[v];j++){ 
                    f[i+j]+=dp[u][i]*ff[j+1]%mod*C((i-1)+j,j)%mod*C((siz[u]-i)+(siz[v]-j),siz[v]-j)%mod;

                    f[i+j]%=mod;
                }
            }
            siz[u]+=siz[v];
            for(int i=1;i<=siz[u];i++){
                dp[u][i]=f[i];
            }
        }
        else{//u是大的点
            fill(f,f+siz[u]+siz[v]+1,0);
            fill(ff,ff+siz[v]+1,0);
            ff[1]=dp[v][1];
            for(int i=2;i<=siz[v];i++){
                ff[i]=(dp[v][i]+ff[i-1])%mod;//前缀和
            }
            for(int i=1;i<=siz[u];i++){
                for(int j=1;j<=siz[v];j++){ 
                    f[i+j]+=dp[u][i]*ff[j]%mod*C((i-1)+j,j)%mod*C((siz[u]-i)+(siz[v]-j),siz[v]-j)%mod;
                    f[i+j]%=mod;
                }
            }
            siz[u]+=siz[v];
            for(int i=1;i<=siz[u];i++){
                dp[u][i]=f[i];
            }
        }
    }

    return ;
}

signed main(){

    p[0]=1;
    for(int i=1;i<N;i++){
        p[i]=p[i-1]*i%mod;
    }
    inv[0]=inv[1]=1;
    for(int i=2;i<N;i++){
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    }
    for(int i=2;i<N;i++){
        inv[i]=inv[i]*inv[i-1]%mod;
    }

    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        scanf("%lld%lld",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfsinit(1,0);
    dfs(1,0);

    for(int i=1;i<=siz[1];i++) ans+=dp[1][i],ans%=mod;
    printf("%lld\n",ans*2%mod);//最后乘二

    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

简单题。

对所有边定向。如果 $u \to v$，表示 $p_u < p_v$。

容易发现，从 $1$ 开始整棵树每一层边的顺序完全相同，且正反交替。我们不妨设 $dp_{u,i}$ 表示 $u$ 在他的子树中从小到大排名为 $i$，且要求下一层的边指向 $v$ 的方案数（另一种方法是完全对称的，只需要把 $dp$ 数组翻转一下）

考虑合并一棵树的所有儿子。把 $u$ 所有直接儿子当做是“关键的”。先把所有儿子的 $dp$ 数组翻转，那么我们要将儿子们进行归并，并且记录第一个儿子的位置。合并两颗子树的时候，枚举哪棵子树的最早关键点会成为合并后的最早关键点，并且使用后缀和优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MOD=998244353;
int n,sze[MAXN],dp[MAXN][MAXN],C[MAXN][MAXN];
vector<int> G[MAXN];
int tmp[MAXN],suf1[MAXN],suf2[MAXN];
void dfs(int u,int f) {
	int flg=0;
	for(auto v:G[u]) if(v!=f) {
		dfs(v,u);
		reverse(dp[v]+1,dp[v]+sze[v]+1);	
		if(!flg) {
			flg=1;
			ffor(i,1,sze[v]) dp[u][i]=dp[v][i];
			sze[u]+=sze[v];	
			continue ;
		}
		else {
			ffor(i,1,sze[u]) suf1[i]=dp[u][i];
			ffor(i,1,sze[v]) suf2[i]=dp[v][i];
			roff(i,sze[u]-1,1) suf1[i]=(suf1[i+1]+suf1[i])%MOD;
			roff(i,sze[v]-1,1) suf2[i]=(suf2[i+1]+suf2[i])%MOD;
			ffor(i,1,sze[u]+sze[v]) tmp[i]=0;
			ffor(i,1,sze[u]) ffor(j,0,sze[v]-1) tmp[i+j]=(tmp[i+j]+C[i-1+j][j]*C[sze[u]-i+sze[v]-j][sze[v]-j]%MOD*dp[u][i]%MOD*suf2[j+1])%MOD;
			ffor(i,1,sze[v]) ffor(j,0,sze[u]-1) tmp[i+j]=(tmp[i+j]+C[i-1+j][j]*C[sze[u]-i+sze[v]-j][sze[u]-j]%MOD*dp[v][i]%MOD*suf1[j+1])%MOD;
		}
		sze[u]+=sze[v];
		ffor(i,1,sze[u]) dp[u][i]=tmp[i];
	}
	if(!flg) return sze[u]++,dp[u][1]=1,void();
	sze[u]++;
	roff(i,sze[u]-1,1) dp[u][i]=(dp[u][i]+dp[u][i+1])%MOD;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);
	int sum=0;
	ffor(i,1,n) sum=(sum+dp[1][i])%MOD;
	cout<<sum*2%MOD;
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

经典题目。

既然是填排列，不难想到树上背包表示当前所在点、在子树里的相对位置、比周围大还是小。答案就是根节点所有情况的方案数加和。

考虑如何合并背包。我们发现自己和直接儿子的大小关系较为重要，和其他后代的大小关系不是那么重要。可以先考虑儿子的子树内比自己大（或小）的节点有几个，然后前缀和统计有多少方案能如此贡献，最后使用组合数合并排列。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;

const int N = 3010, mod = 998244353;
inline void exgcd(long long a, long long b, long long &x, long long &y)
{
	if(b == 0) {x = 1, y = 0; return ;}
	exgcd(b, a % b, y, x); y -= a / b * x;
}
inline long long Inv(long long num)
{
	long long x, y; exgcd(num, mod, x, y);
	x = (x % mod + mod) % mod; return x;
}
int n, h[N], cnt; struct edge {int to, next;} e[N * 2];
inline void add(int x, int y) {e[++cnt].to = y, e[cnt].next = h[x], h[x] = cnt;}
long long fac[N * 2], inv[N * 2];
inline long long C(long long n, long long m)
{return fac[n] * inv[n - m] % mod * inv[m] % mod;}
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 6000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[6000] = Inv(fac[6000]);
	for(int i = 5999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}
inline void Plus(long long &now, long long add)
{now += add; while(now >= mod) now -= mod; while(now < 0) now += mod;}

long long f[N][N][2], g[N][2], pre[N], suf[N]; int siz[N];
inline void treedp(int now, int prt)
{
	siz[now] = 1;
	f[now][1][0] = f[now][1][1] = 1;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to; if(to == prt) continue;
		treedp(to, now);
	}
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to; if(to == prt) continue;
		pre[0] = suf[siz[to] + 1] = 0;
		for(int j = 1; j <= siz[to]; ++j)
			pre[j] = (pre[j - 1] + f[to][j][0]) % mod;
		for(int j = siz[to]; j >= 1; --j)
			suf[j] = (suf[j + 1] + f[to][j][1]) % mod;
		memset(g, 0, sizeof(g));
		for(int j = 1; j <= siz[now]; ++j)
		{
			for(int k = 0; k <= siz[to]; ++k)
			{
				Plus(g[j + k][1], f[now][j][1] * pre[k] % mod * C(k + j - 1, k) % mod * C(siz[to] - k + siz[now] - j, siz[to] - k) % mod);
				Plus(g[j + k][0], f[now][j][0] * suf[k + 1] % mod * C(k + j - 1, k) % mod * C(siz[to] - k + siz[now] - j, siz[to] - k) % mod);
			}
		}
		siz[now] += siz[to];
		for(int j = 1; j <= siz[now]; ++j)
			f[now][j][0] = g[j][0], f[now][j][1] = g[j][1];
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init();
	cin >> n;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		add(x, y), add(y, x);
	}
	treedp(1, 0);
	long long ans = 0;
	for(int i = 1; i <= n; ++i)
		Plus(ans, f[1][i][0] + f[1][i][1]);
	cout << ans << '\n';
	return 0;
}

/*

*/
```

---

