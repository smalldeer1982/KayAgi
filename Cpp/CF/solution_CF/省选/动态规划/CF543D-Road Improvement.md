# Road Improvement

## 题目描述

这个国家有n座城市和n-1条双向道路，你可以沿道路从一个城市到任意一个其他城市。这些城市被编号为整数1到n。

所有的道路最初都是不良的，但是政府想要改善一些路的状况。我们认为如果从首都x城到其他城市的道路最多包含一条不良道路，市民会对此感到满意。
你的任务是——对于每一个可能的x，求出所有能够满足市民条件的改良道路的方式。因为结果可能很大，你需要输出mod 1000000007 ( 10^9+7 )后的结果。

## 样例 #1

### 输入

```
3
1 1
```

### 输出

```
4 3 3```

## 样例 #2

### 输入

```
5
1 2 3 4
```

### 输出

```
5 8 9 8 5```

# 题解

## 作者：Binary_Search_Tree (赞：12)

[题目传送门](https://www.luogu.org/problem/CF543D)

**首先，考虑当根固定时本题怎么做。**

~~看到答案这么大，显然是DP不用说了吧~~

设$F(i)$表示以$i$为根的子树中改良道路的方案数，考虑如何转移

当i为叶子节点时，没有可以改善的道路，所以$F(i)=1$

枚举$i$的每一个子树，设当前i的子树为$j$

若$i$到$j$这条路不改善，则i的子树中的道路必须全部维修，方案数为$1$

若$i$到$j$这条路改善，则显然方案数为$F(j)$

综上所述，由乘法原理可得$F(i)=\prod\limits_{j\in son(i)}(F(j)+1)$

**那么当根不固定时，答案应该如何计算呢？**

发现当根从$i$变成$i$的某个孩子$j$时，只有$F(i)$和$F(j)$发生了变化。

设$F'(i)$表示根变化后$F(i)$的值，则

$F'(i)=\prod\limits_{k\in son(i),k\neq j}(F(k)+1)  $&#8195;$F'(j)=F(j)(F(i)+1)$

前面的式子可以直接通过前缀积/后缀积求出。

（如果直接乘逆元可能会碰到0不存在逆元的情况）

**这就是换根DP的思想。**

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#define M 1000005
#define mod 1000000007ll
using namespace std;
int n,nxt[M],head[M],to[M],tot;
long long F[M],ans[M];
vector <long long> F1[M],F2[M];//用vector记，防止MLE
int read(){//快读
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans;
}
void add(int u,int v){//加边（双向边）
	nxt[++tot]=head[u];head[u]=tot;to[tot]=v;
	nxt[++tot]=head[v];head[v]=tot;to[tot]=u;
	return;
}
void dfs1(int x,int fa){//先预处理F数组
	F[x]=1;
	for (register int i=head[x];i;i=nxt[i])
		if (to[i]!=fa) dfs1(to[i],x),F[x]=F[x]*(F[to[i]]+1)%mod;
	return;
}
void dfs2(int x,int fa){//换根DP
	ans[x]=1;
	for (register int i=head[x];i;i=nxt[i]){
		ans[x]=ans[x]*(F[to[i]]+1)%mod;
		if (to[i]!=fa) F1[x].push_back(F[to[i]]+1),F2[x].push_back(F[to[i]]+1);
	}//F1表示前缀积，F2表示后缀积
	for (register int i=1;i<F1[x].size();i++) F1[x][i]=F1[x][i]*F1[x][i-1]%mod;
	for (register int i=F2[x].size()-2;i>=0;i--) F2[x][i]=F2[x][i]*F2[x][i+1]%mod;
	int cnt=0;
	for (register int i=head[x];i;i=nxt[i]){
		if (to[i]==fa) continue;F[x]=(fa?F[fa]+1:1);
		if (cnt>0) F[x]=F[x]*F1[x][cnt-1]%mod;//防止越界
		if (cnt<F2[x].size()-1) F[x]=F[x]*F2[x][cnt+1]%mod;//防止越界
		dfs2(to[i],x);++cnt;
	}
	return;
}
int main(){
	n=read();
	for (register int i=2;i<=n;i++) add(read(),i);
	dfs1(1,0);dfs2(1,0);
	for (register int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

如果有帮助就点个赞吧~ 

---

## 作者：lndjy (赞：5)

首先，看到每个首都，想到换根 dp。

先考虑指定 $1$ 为根时怎么做。

首先有一个容易的转化，就是转化为一开始全是好的，根到 叶节点只能有一个变坏。

设 $f[u][0/1]$ 表示 $u$ 子树，$1$ 为已经有变坏的，$0$ 为没有。转移为：

$$f[leaf][0]=1,f[leaf][1]=0$$

$$f[u][0]=\prod f[v][0]$$

$$f[u][1]=\prod (f[v][0]+f[v][1]+f[v][0])-1$$

$$ans=f[root][0]+f[root][1]$$

第三个方程解释一下，就是对于一个子树，如果不变连接边，里面随便，变了的话里面只能没变过，最后如果都选择不变也会计入其中，所以要减一。

然后看着这个方程发现，$f[u][0]$ 恒等于 $1$，数学上解释就是 $1^n=1$，从实际上解释就是都不变只有一种方案。

那么我们可以化简这个方程：

$f[u]$ 表示 $f[u][0]+f[u][1]$。

$$f[leaf]=1$$

$$f[u]=\prod (f[v]+1)$$

这个方程简单的多，可以考虑换根了。

设 $g[i]$ 表示以 $i$ 为根的答案。

$$g[1]=f[1]$$

$$g[v]=f[v]\times (\frac{g[u]}{f[v]+1}+1)$$

然后注意 $f[v]+1$ 可能没有逆元，需要特殊处理。

---

## 作者：UltiMadow (赞：5)

换一个姿势换根dp（好像也差不多？）

按照换根dp的老套路，我们令 $g_u$ 为修好以 $u$ 为根的**子树**当中的路有多少种方案；$f_u$ 为修好以 $u$ 为根的**整棵树**的路，**并且除去原来以 $u$ 为根的子树**有多少种方案

先考虑 $g$

考虑一条 $u\rightarrow v$ 的边，如果这条边不修，则 $v$ 子树中的所有边必须要修，则有 1 种修法；如果这条边修，则 $v$ 子树中的贡献为 $g_v$，则 $v$ 子树的总贡献为 $g_v+1$

那么，$g_u=\prod_{v\in son_u}(g_v+1)$

再考虑 $f$

设 $v$ 为 $u$ 的一个儿子，则有 $f_v=f_u\times \frac{g_u}{g_v+1}+1=f_u\times \prod_{w\in son_u,w\not=v}(g_w+1)+1$

（其中加一的原因是和上面一样的）

$\prod_{w\in son_u,w\not=v}(g_w+1)$ 可以预处理一个前缀积和一个后缀积 $\Theta(1)$ 求出

然后每个点的答案即为 $f_u\times g_u$

感觉这样做的思路比楼上那么写容易理解一点？

时间复杂度 $\Theta(n)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 200010
#define pb push_back
#define int long long
#define p 1000000007
using namespace std;
int n;
struct Node{int to,next;}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v){Edge[++cnt_Edge]={v,Head[u]};Head[u]=cnt_Edge;}
int g[MAXN],f[MAXN],son[MAXN];//g&f&每个点儿子数量
vector<int>pre[MAXN],suf[MAXN];//前缀积&后缀积
void dp1(int u,int fa)
{
	g[u]=1;pre[u].pb(1);suf[u].pb(1);
	for(int i=Head[u];i;i=Edge[i].next)
	{
		int v=Edge[i].to;if(v==fa)continue;
		dp1(v,u);g[u]=g[u]*(g[v]+1)%p;son[u]++;
		pre[u].pb(g[v]+1);suf[u].pb(g[v]+1);
	}pre[u].pb(1);suf[u].pb(1);//前后建立哨兵点防止溢出问题
	for(int i=1;i<=son[u];i++)pre[u][i]=pre[u][i]*pre[u][i-1]%p;
	for(int i=son[u];i;i--)suf[u][i]=suf[u][i]*suf[u][i+1]%p;
}//处理g,前缀积和后缀积
void dp2(int u,int fa)
{
	for(int i=Head[u],j=1;i;j++,i=Edge[i].next)
	{
		int v=Edge[i].to;if(v==fa)continue;
		int now=(u==1)?1:f[u];
		f[v]=(now*pre[u][j-1]%p*suf[u][j+1]%p+1)%p;
		dp2(v,u);
	}
}//处理f
signed main()
{
	scanf("%lld",&n);
	for(int i=2;i<=n;i++)
	{
		int u;scanf("%lld",&u);
		Add_Edge(u,i);Add_Edge(i,u);
	}dp1(1,0);f[1]=1;dp2(1,0);printf("%lld",g[1]%p);
	for(int i=2;i<=n;i++)printf(" %lld",f[i]*g[i]%p);//输出答案
	return 0;
}
```

---

## 作者：activeO (赞：3)

## 题目大意

给定一颗 $ n $ 个点的无根树，当把一个点 $ x $ 设置为首都时，要求从 $ x $ 到任意别的点的路径上有不超过 $ 1 $ 条未维修的边，现在问你当每一个点作为首都的维修方案数。

## 思路

先考虑设置了首都为 $ x $，那它就是一个简单的树形 dp，令 $ dp_u $ 表示以 $ u $ 为根的子树内满足条件的维修方案，可以发现如果 $ u \rightarrow v $ 的这条边不维修的话，那么以 $ v $ 为根的子树内的所有边都必须维修，并且所有 $ u $ 的儿子 $ v $ 是互不影响的。所以得 dp 方程：

$ dp_u \leftarrow \prod_{ v \in son_u} (dp_v + 1) $

但是这只是确定根后的做法，数据范围：

$ n \leq 2 \cdot 10^5 $

所以我们显然不能枚举每个点作为根。

这时候就要换根 dp。考虑当根节点从 $ u $ 变为儿子 $ v $ 时：

- 对于 $ u $ 就是少了一颗子树，所以 $ dp_u \leftarrow \prod_{ k \in son_u} (dp_k + 1)  (k \neq v) $。这个东西不能用逆元，只能用前后缀积，因为 $ 0 $ 没有逆元。

- 对于儿子 $ v $，就是多了它父亲这颗子树，所以 $ dp_v \leftarrow dp_v \cdot (dp_u+1) $，这里的 $ dp_u $ 当然就是变更后的了。

具体看代码实现。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=2e5+5;
const int mod=1e9+7;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],len;
int dp[maxn],res[maxn];
vector<int> pre[maxn],suf[maxn];

inline void init(){
	memset(head,-1,sizeof(head));
	len=0;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

void dfs1(int u,int fa){
	dp[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		dp[u]=(1ll*dp[u]*(dp[v]+1))%mod;
	}
}
void dfs2(int u,int fa){
	res[u]=dp[u];
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		// if(v==fa) continue;
		// res[u]=1ll*res[u]*(dp[v]+1)%mod;
		pre[u].push_back((dp[v]+1));
		// printf("jjjjjjjjjjjjjj%d %d\n",v,dp[v]+1);
		suf[u].push_back((dp[v]+1));
	}
	// reverse(suf[u].begin(),suf[u].end());
	int lpre=pre[u].size(),lsuf=suf[u].size();
	for(int i=1;i<lpre;i++) pre[u][i]=1ll*pre[u][i-1]*pre[u][i]%mod;
	for(int i=lsuf-2;i>=0;i--) suf[u][i]=1ll*suf[u][i+1]*suf[u][i]%mod;
	int j=0;
	for(int i=head[u];i!=-1;i=e[i].nxt,j++){
		int v=e[i].to;
		if(v==fa) continue;
		// if(u==2){
			// for(int k=0;k<(int)pre[u].size();k++) printf("%d ",pre[u][k]);
			// puts("");
			// for(int k=0;k<(int)suf[u].size();k++) printf("%d ",suf[u][k]);
			// puts("");
		// }
		dp[u]=1ll*(j>0?pre[u][j-1]:1ll)*(j<lsuf-1?suf[u][j+1]:1ll)%mod;
		dp[v]=(1ll*dp[v]*(dp[u]+1))%mod;
		// printf("%d -> %d : %d && %d\n",u,v,dp[u],dp[v]);
		dfs2(v,u);
	}
}

int main(){
	
	init();
	
	int n;
	
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		add(x,i);
		add(i,x);
	}
	
	dfs1(1,0);
	
	// for(int i=1;i<=n;i++) printf("%d ",dp[i]);
	// puts("");
	
	dfs2(1,0);
	
	for(int i=1;i<=n;i++) printf("%d ",res[i]);
	puts("");
	
	return 0;
}
```


---

## 作者：titititing (赞：3)

解题思路：

可以写出n^2的dp

每个点的值=它子树的值相乘

经过一定的思考之后我们可以发现

换根操作是可以在O（1）时间内完成的

我们只需要把那个子树的传回来的值除掉（*逆元）

但是：

这道题好像还卡了模数，当dp值=1e9+6的时候

（你能算逆元吗？）

所以我们对于这种点单独处理

下面来看代码：

```cpp

#include<bits/stdc++.h>
#define N 200005
using namespace std;
struct Edge{
	long long to,nxt;
}E[N*2];
long long Head[N],x,y,n,tot,dp[N],aux[N],ans[N];
bool vis[N];
const long long mod=1000000007;
void addedge(long long x,long long y){
	E[++tot]=(Edge){y,Head[x]};
	Head[x]=tot;
}
inline long long ksm(long long b,long long p){
    long long res=1;
    for (p<<=1;p>>=1;b=b*b%mod)
        if (p&1) res=res*b%mod;
    return res;
}//快速幂 
inline long long getinv(long long x){
	long long res=ksm(x,mod-2);
	return res;
}//逆元 
void dfs(long long v,long long fa){//第一遍dfs算出根 为1 
	dp[v]=1;
	bool skip=false;
	for (int i=Head[v];i;i=E[i].nxt){
		if (E[i].to==fa) continue;
		dfs(E[i].to,v);
		if (dp[E[i].to]+1==mod&&!skip)
			vis[E[i].to]=true,skip=true; else
			dp[v]*=(dp[E[i].to]+1),
			dp[v]%=mod;
	} 
	if (skip)
		aux[v]=dp[v],dp[v]=0;
}
void dfs_2(int v,int fa){//第二遍dfs换根 
	ans[v]++;
	for (int i=Head[v];i;i=E[i].nxt){
		if (E[i].to==fa) continue;
		if (!vis[E[i].to])
			ans[E[i].to]=ans[v]*dp[v]%mod*getinv(dp[E[i].to]+1)%mod; else 
			ans[E[i].to]=ans[v]*aux[v]%mod;
		dfs_2(E[i].to,v);
	}
}
void read(){
	scanf("%lld",&n);
	for (int i=2;i<=n;i++){
		scanf("%lld",&x);
		addedge(i,x);
		addedge(x,i);
	}
} 
void solve(){
	dfs(1,0);
	memset(ans,0,sizeof(ans));
	dfs_2(1,0); 
	for (int i=1;i<=n;i++)
		printf("%lld ",ans[i]*dp[i]%mod);
}
int main(){
	read();
	solve();
	return 0;
} 
```

---

## 作者：CWzwz (赞：1)

[CF543D](https://www.luogu.com.cn/problem/CF543D) 题解

[CodeForces](https://codeforces.com/problemset/problem/543/D)

------------

独立做出来了，开心。

考虑从 $x$ 出发、到叶子的一条链，中间有了一条“不良的路”后，后面的边一定都是“改善的路”。

设 $f_i$ 表示 $i$ 的子树内的方案数，$ans_i$ 表点 $i$ 的答案。

$f$ 利用乘法原理转移（儿子子树方案数相乘）：

$$f_u=\prod_{v\in \operatorname{son}_u}(f_v+1)$$

（加的那个 $1$ 是不良道路正好在 $u,v$ 间的情况。）

- 算出 $f_u$ 后，$ans$ 的转移（除掉 $u$ 子树的贡献，得到**点 u 子树外的答案**，然后把结果转化为以 $u$ 为根时的贡献，再把 $u$ 子树乘回去）：

$$ans_u=(\frac{ans_{fa}}{f_u+1}+1)\times f_u$$

（把 $\frac{ans_{fa}}{f_u+1}$ 加 $1$ ，加的是不良道路正好在 $u$ 和 $fa$ 间的情况。）

但是做除法的话，可能出现 $10^9+7$ 的倍数导致没有逆元而出错。所以考虑另一种统计方法。

求上面“点 $u$ 子树外的答案”的时候出了问题，考虑重新表示这个东西，设 $g_u$ 表示点 $u$ 的子树以外的答案。

转移平凡，从 $fa$ 到 $u$，会多包含 $u$ 的 $brother$。

$$g_u=g_{fa}\times\prod_{v\in\operatorname{brother}_u}(f_v+1)+1$$

这个 $+1$ 就是加的不良道路正好在 $u$ 和 $fa$ 间的情况。

前后缀积优化即可，记录所有儿子的 $f_v+1$ 的前后缀积。

那么 $ans$ 的转移中的 $\frac{ans_{fa}}{f_u+1}+1$ 就换成 $g_u$ 了。

[Submission](https://codeforces.com/contest/543/submission/240226230)

------------

双倍经验：[AT dp_v](https://www.luogu.com.cn/problem/AT_dp_v)，方程完全一样。

前者的“不良道路”可以理解为后者的“黑白点间的分界边”，只能有一条不良道路，就是说黑点互相联通，否则一条根叶路径上就有多条不良道路了。

---

## 作者：Daidly (赞：1)

换根 dp 保姆级题解。

按照一般换根 dp 的思路，可以考虑在子树 $u$ 中进行操作，第一维即为 $u$。此题也明确了一个“良”与“不良”，“良”占多数，所以可以考虑用 $0/1$ 来记录。而求解的是方案数，将这一信息记录在数值中。

设 $f[u][0/1]$ 为在子树 $u$ 中是否有不良边的方案数。

考虑转移，将 $f[u][0/1]$ 与 $f[v][0/1]$ 联系起来，其中 $v\in son(u)$。

可以发现：若子树 $u$ 中无不良边，则方案数一定为 $1$，也可以看作转移成所以无不良边的儿子子树方案数之积；若子树 $u$ 中有不良边，就稍微有点难转移了。

难在哪里？我们只能枚举子树 $v$ 中是否有不良边，并不能保证 $u$ 的所有儿子的子树中一共至少有一条不良边，若枚举后全都是良边，就不对了。

使用“一般减特殊”的方法，一般即为“枚举 $u$ 的儿子子树，从而计算出 $u$ 的子树中有不良边的方案数”，特殊即为“枚举时可能全是良边”有且仅有一种情况，大减小即可，也就是最后减去 $1$。

问题转换成：如何枚举子树 $u$ 中边的方案数。

由于只需要转移到 $v$，问题又转化成：枚举 $u,v$ 之间连边是否为良边，然后扔到 $v$ 子树中算就行了。根据乘法原理，对每一个子树方案数相乘即为答案。

当连边为良边，则 $v$ 子树中可以全为良边 $f[v][0]$ 也可以有不良边 $f[v][1]$；当连边为不良边，则 $v$ 子树中只能全为良边（想一想为什么？）

因为若 $(u,v)$ 为不良边，且 $v$ 子树中有不良边，则 $v$ 子树中一定有一个点到根节点的路径上经过了两条不良边，不符合题意。

把一个子树中的方案数全部加起来，再把每个子树中的方案数乘起来即可。

列出状态转移方程：

$$f[u][0]=\prod_{v\in son(u)}\big(f[v][0]\big),f[u][1]=\prod_{v\in son(u)}\big((f[v][0]+f[v][1])+(f[v][0])\big)-1$$

即为：

$$f[u][0]=1,f[u][1]=\prod_{v\in son(u)}\big(f[v][1]+2\big)-1$$

而 $f[u][0]+f[u][1]$ 就是以 $u$ 为根的整棵子树的方案数，所以我们考虑合并：记 $f[u]=f[u][0]+f[u][1]$。

则有：
$$
f[u]=\prod_{v\in son(u)}\big(f[v]+1\big)
$$
每棵 $v$ 子树对 $u$ 子树的贡献是 $v$ 子树本身加上与 $u$ 的连边，又由于每棵子树之间贡献独立，根据乘法原理乘起来即可。

计算完了 $f[u]$，考虑如何换根，计算 $g[u]$ 表示已 $u$ 为整颗树的根的方案数。

若第一次钦定根节点为 $1$，它的答案在 dfs1 中就已经求出，就有 $g[1]=f[1]$。

接下来看一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qpbl3bvr.png)

我们现在知道了 $f[1]=g[1],f[2]$，如何求 $g[2]$？

考虑 $g[2]$ 的组成，将 $2$ 看成根，则有 $g[2]=(f[4]+1)(f[5]+1)(f[6]+1)(f_2[1]+1)=f[2](f_2[1]+1)$，其中 $f_2[1]$ 表示以 $2$ 为整颗数的根时 $1$ 的 $f$ 值。但是，这个值我们不知道，我们只知道以 $1$ 为根时 $1$ 的 $f$ 值。想想，$f_2[1]$ 又等于什么？等于 $f[3]+1$。

然后我们看 $2$ 换根到 $5$ 的过程：$g[5]=f[5](f_5[2]+1)$，那么这个 $f_5[2]$ 有等于什么呢？$f_5[2]=(f[4]+1)(f[6]+1)(f_5[1]+1)$。咦？这里出现了 $f_5[1]$，它是不是等于 $f_2[1]$ 呢？在这里是等于的，但我们再换个点瞧瞧。如果 $f_i[u],i\ne 1$ 全都相等，我们可以预处理。

看 $3$ 换根到 $7$ 的过程：$g[7]=f[7](f_7[3]+1),f_7[3]=f_7[1]+1$，这里的 $f_7[1]$ 明显不等于 $f_5[1],f_2[1]$。

根据以上探究（手玩），我们可以得出以下三个结论：（这里的 $u,v$ 关系始终是以 $1$ 为根时的关系）

- 以 $v$ 为根的答案等于 $u$ 除 $v$ 以外的邻居的 $f$ 值 $+1$ 的成绩再 $+1$ 乘上 $f[v]$，即 $g[v]=f[v]\big(\prod (f[i]+1)+1\big)$，其中 $i$ 为 $u$ 的邻居。
- 邻居中不是 $u$ 的父亲的点好处理，直接用前后缀积计算即可，但 $fa_u$ 对于不同点的贡献不固定，不能与预处理，所以我们可以将传参下去，作为 `void dfs2(int u,int fa,int faw)` 的一个参数。
- 而父亲节点的贡献就等于父亲节点在计算时的前后缀积乘上 $fa_{fa}$ 的贡献。初始点 $1$ 的父亲 $0$ 的贡献记为 $1$。

第三个可以参照代码理解：

```cpp
g[v]=f[v]*(pre[u][i]*suf[u][i+1]%mod*faw%mod+1)%mod;
dfs2(v,u,pre[u][i]*suf[u][i+1]%mod*faw%mod+1);
```

[完整代码链接（开完隐的同学可能就看不到了哦）](https://www.luogu.com.cn/record/82749731)

总的来说：这一道题会意很容易，完全理解还要下一番功夫哦，可以作为一道换根 dp 的入门题。

换根 dp 常见套路：

- 两次 dfs。不要写混，比如 `dfs1()` 里套 `dfs2()`
- 前后缀积避免无逆元的情况。

完结撒花！

---

## 作者：Piwry (赞：1)

花了敲代码框架一倍多的时间解决逆元的问题... (

## 解析

题目要求求出以每个点为首都的答案，已经非常明显地提示换根 dp 了

首先考虑固定首都该怎么做

这个还是挺显然的。如果确定一个点到根的路径上的某条边是不良的，显然再往上都不可能再放置不良的边了；也就是说，一旦某个子树中存在不良的边，那么这颗子树根到它父亲（乃至到整棵树根）的边一定是良的

于是状态就可以设为：$dp(u, 1/0)$，表示以 $u$ 为根的子树是/否含有不良的道路，的所有可能的方案数

接下来考虑转移，

注意到，如果一颗子树只含有良的道路，那么它有且仅有一种方案。于是我们没必要特地开数组记录这类状态

接着考虑转移含有不良道路的状态。对于有不良道路的子树只能放置良道路；对于没有不良道路的子树既可以放也可以不放良道路——因为只要有一颗子树或和这颗子树之间的道路是不良的就可以了

在枚举每颗子树时考虑可能错误统计的没有不良道路的状态会很复杂；实际上，不含有不良道路的状态有且仅有一种，我们在**最后减掉**就可以了

含有不良道路状态的转移方程就为：$dp(u, 1) =\prod\limits_v(dp(v, 1)+2dp(v, 0))-1$，其中 $v$ 是 $u$ 的儿子。这个方程也可以写为 $dp(u, 1) =\prod\limits_v(dp(v, 1)+2)-1$

&nbsp;

至于换根，可以想到只要除掉当前子树的贡献即可，题目要求模数那么求逆元即可

但注意到，在个别情况下连乘中**是可能存在 $0$ 的**；于是考虑处理连乘的前缀/后缀积，这样就可以计算没有某个子树的贡献了（且能避免乘 $0$ 情况）

另外还要注意在换根 dfs 中也要维护前缀/后缀积。可以想到父亲结点（作为子树）的贡献是**一定计入**的，于是给前缀积**或**后缀积的每一项都乘上这个贡献即可

## CODE

感觉换根 dp 部分的状态设计还是很简单的，但逆元部分着实坑到了我（

```cpp
#include <cstdio>
#include <vector>
using std::vector;
using std::min;

const int MAXN =2e5+50;
const int M =1e9+7;

inline int del1(int x){ return (x == 0) ? M-1 : x-1; }

/*------------------------------Times------------------------------*/

vector<int> pre[MAXN], post[MAXN];/*前缀后缀积*/

int qPow(int x, int k){
	int ans =1;
	for(; k; x =1ll*x*x%M, k >>=1) if(k&1) ans =1ll*ans*x%M;
	return ans;
}

inline int Inv(int x){ return qPow(x, M-2); }

/*------------------------------Map------------------------------*/

vector<int> E[MAXN];
int son[MAXN];

/*------------------------------Dfs------------------------------*/

int dp[MAXN]/*子树内有至少一条不良道路且合法 ( 该点到子树内任意点路径最多一条不良 ) 的方案数*/;

void dfs1(int u, int fa){
	dp[u] =1;
	int k =0;
	pre[u].push_back(1);
	for(int v:E[u])
		if(v != fa){
			dfs1(v, u);
			dp[u] =1ll*dp[u]*(dp[v]+1+1)%M;/*子树有不良该边良，或子树全良 (1) 该边不良，或子树全良该边良*/
			/*因为只要有一个儿子有不良即可*/
			pre[u].push_back(dp[u]);
			++k;
		}
	
	int tmp =1;
	post[u].push_back(1);
	for(int vi =E[u].size()-1; vi >= 0; --vi)
		if(E[u][vi] != fa){
			tmp =1ll*tmp*(dp[E[u][vi]]+1+1)%M;
			post[u].push_back(tmp);
		}
	
	son[u] =k;
	dp[u] =del1(dp[u]);/*对于无儿子，这会使贡献为 0；对于有儿子，这会减掉全良的贡献*/
}

void dfs2(int u, int fa){
	int k =0;
	for(int v:E[u])
		if(v != fa){
			++k;
			int res =del1(1ll*pre[u][k-1]*post[u][son[u]-k]%M);
			dp[v] =1ll*(dp[v]+1)*(res+1+1)%M;
			dp[v] =del1(dp[v]);
			/*维护前缀后缀和，形象理解下。相当于在最前面 ( 最后面也可 ) 强制乘一个数*/
			for(int i =0; i < (int)pre[v].size(); ++i)
				pre[v][i] =1ll*pre[v][i]*(res+1+1)%M;
		//	for(int i =0; i < (int)post[v].size(); ++i)
		//		post[v][i] =1ll*post[v][i]*(res+1+1)%M;
			dfs2(v, u);
		}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read();
	for(int i =2; i <= n; ++i){
		int pi =read();
		E[i].push_back(pi), E[pi].push_back(i);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i =1; i <= n; ++i)
		printf("%d ", (dp[i]+1)%M);
}
```

---

## 作者：zhr1502 (赞：1)

~~看到题解里用的都是vector，我决定写一篇手打邻接表的题解~~
### 题意
- 给定一棵含 $n$ 个点， $n-1$ 条边的树。

- 选一个点为根，选若干条边打上标记（可以一条也不打），要求从任何一个节点到根节点路径上有标记的边不超过一条。

- 对于编号为 $1$ ~ $n$ 的每个点，你需要求出该点作为根节点一共有多少种打标记的方法，答案对 $1000000007$ 取模。

### 暴力做法：树形DP

规定题面中“不良好的道路”为打上标记的边。

对一颗根节点确定的树，我们容易发现**一个点**与它的**一个儿子节点**的连边有**打上标记与不打上标记**两种可能。

在**根节点确定的树**中，我们设 $f_{i}$ 为以 $i$ 为根的**子树**的合法方案。
- **如果打上标记，就要求该儿子所在子树不能有一个标记**（否则就会存在一个点到根节点路径上存在多条有标记的边），此时只有一种方案，即该子树的边全部没有标记。这种可能  的方案数为 $1$ 。
- **如果该边不打上标记**，那么该儿子所在子树只要也满足“路径上打标记的边不超过一条”即可。设 $j$ 为 $i$ 的一个儿子的编号，这种可能  的方案数为 $f_{j}$ 。

因此，对于一颗子树 $j$ 而言，可能的方案数为 $f_{j}+1$ 。由乘法原理易知：

$f_{i}=\prod (f_{j}+1)$

其中 $j$ 是 $i$ 的一颗子树。那么对于一颗根已经确定的树，我们就可以 $O(N)$ 求出对于这个根的可能的方案数。由于我们要求出所有节点为根的方案数，也就要跑 $n$ 次，所以总的时间复杂度为 $O(N^{2})$ 。
~~于是我们成功的爆掉了~~。

### AC做法：树形DP+换根
其实与上一种做法大致是一样的。我们可以 $O(N)$ 计算出以**一个确定的点为根**的所有 $f$ 值。然后对于以 $i$ 为根的一颗**树**，选择其一个儿子 $j$ 作为新的根，此时可以将 $f_{i}$ 更改为 $\frac{f_{i}}{f_{j}+1}$ 去递归更新 $j$ （可以理解为 $i$ 降格为 $j$ 的子树），更新完成后再还原 $f_{i}$ 。

**那要怎么算 $\frac{f_{i}}{f_{j}+1}$ 呢？**

~~逆元~~

这道题卡了逆元，可能出现不存在逆元的情况。所以我们需要预处理前缀/后缀积以计算。即：

 $\frac{f_{i}}{f_{j}+1}=(f_{s_{1}}+1)\cdot (f_{s_{2}}+1) \cdots (f_{s_{p-1}}+1) \cdot (f_{s_{p+1}}+1) \cdots (f_{s_{k-1}}+1) \cdot (f_{s_{k}}+1)$

其中s为节点 $i$ 子节点编号构成的序列，且 $s_{p}=j$ 。所以需预处理出 $(f_{s_{1}}+1)\cdot (f_{s_{2}}+1) \cdots (f_{s_{p-1}}+1)$ 和 $(f_{s_{p+1}}+1) \cdots (f_{s_{k-1}}+1) \cdot (f_{s_{k}}+1)$ 即可。(第一次dp时就可以顺带进行预处理）

当然你可以使用vector来储存前/后缀积。但是我~~太菜不会用vector~~用了**邻接表**~~居然还摸了个最优解~~。细节见代码注释。


------------

### upd
一位巨神**随手**帮忙优化了一下空间。我们不需要使用邻接表存储，可以在预处理时直接将前缀积与后缀积的乘积记录在每一个子树上。核心部分见第二段代码。

------------

## code
#### 邻接表做法
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN 200010
#define MOD 1000000007
int n,hed[MAXN*2],nxt[MAXN*2],edg[MAXN*2],tot;		//hed,nxt,edg为存储树边的邻接表
int hepr[MAXN],nxpr[MAXN],tpr,helt[MAXN],nxlt[MAXN],tlt;
//hepr nxpr valpr (pr为pre)为存储前缀积的邻接表，topr为前缀积邻接表长度
//helt nxlt vallt (lt为last)为存储后缀积的邻接表,tolt为后缀积邻接表长度
//翻译:he=head nx=next val=value
long long valpr[MAXN],reg[MAXN],vallt[MAXN],mult[MAXN],ans[MAXN];
long long f[MAXN];
inline int getn(){													//快读
	register int a=0;
	bool b=1;
	register char c=getchar();
	for(;!((c>='0'&&c<='9')||c=='-');) c=getchar();
	for(;(c>='0'&&c<='9')||c=='-';){
		if(c=='-') b=0,c=getchar();
		a=(a<<1)+(a<<3)+int(c)-48;
		c=getchar();
	}
	if(!b) return -a;
	return a;
}
inline void add(int x,int y){
	edg[++tot]=y; nxt[tot]=hed[x]; hed[x]=tot;
	return;
}
void dp(int t,int fa){
	f[t]=1; int len=0,p=1;
	for(int i=hed[t];i;i=nxt[i]){
		if(edg[i]==fa) continue;			//遍历不经过父节点
		dp(edg[i],t);
		f[t]=(f[t]*(f[edg[i]]+1))%MOD;			//转移方程详见上面的解释
	}
	for(int i=hed[t];i;i=nxt[i])
		if(edg[i]!=fa) reg[++len]=f[edg[i]]+1;
//由于前缀积和后缀积，两者的方向相反
//邻接表的双向查询又较为麻烦，所以储存在一个数组中方便处理
	mult[1]=1;
	for(int i=1;i<=len;i++){
		mult[i+1]=(mult[i]*reg[i])%MOD;
		vallt[++tlt]=p; nxlt[tlt]=helt[t]; helt[t]=tlt;
//邻接表的插入会使得数列的方向反了一次，所以后缀积可以直接插入
		p=(p*reg[len-i+1])%MOD;
	}
	for(int i=len;i>=1;i--){
		valpr[++tpr]=mult[i]; nxpr[tpr]=hepr[t]; hepr[t]=tpr;
     //反向插入前缀积
	}
	return;
}
void dfs(int t,int fa){
	int s=1,a=hepr[t],b=helt[t];
	for(int i=hed[t];i;i=nxt[i]) s=(s*(f[edg[i]]+1))%MOD;   //更新该节点
	ans[t]=s;
	for(int i=hed[t];i;i=nxt[i]){
		if(edg[i]==fa) continue;
		f[t]=(((valpr[a]*vallt[b])%MOD)*(f[fa]+1))%MOD;
		//后缀积*前缀积*父节点权值 更改该节点
		a=nxpr[a]; b=nxlt[b];
		dfs(edg[i],t);
	}
	return;
}
signed main(){
	n=getn();
	for(int i=2;i<=n;i++){
		int p=getn();
		add(p,i); add(i,p);
	}
	dp(1,0);	//第一次dp
	dfs(1,0);		//换根法
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```
#### 无邻接表做法（dp+换根部分）
```cpp
void dp(int t,int fa){
	f[t]=1; int len=0,p=1;
	for(int i=hed[t];i;i=nxt[i]){
		if(edg[i]==fa) continue;
		dp(edg[i],t);
		f[t]=(f[t]*(f[edg[i]]+1))%MOD;
	}
	for(int i=hed[t];i;i=nxt[i])
		if(edg[i]!=fa) reg[++len]=f[edg[i]]+1;
	mult[len]=1;
	for(int i=len-1;i>=1;i--)
		mult[i]=(mult[i+1]*reg[i+1])%MOD;
    //计算后缀积
	for(int i=hed[t],j=1;i;i=nxt[i],j++){
		if(edg[i]==fa) continue;
		v[edg[i]]=(p*mult[j])%MOD;
        //将前缀积和后缀积的乘积直接记录在子树中
		p=(p*reg[j])%MOD;
        //计算前缀积
	}
	return;
}
void dfs(int t,int fa){
	int s=1;
	for(int i=hed[t];i;i=nxt[i]) s=(s*(f[edg[i]]+1))%MOD;   //更新该节点
	ans[t]=s;
	for(int i=hed[t];i;i=nxt[i]){
		if(edg[i]==fa) continue;
		f[t]=(v[edg[i]]*(f[fa]+1))%MOD;
		//调用之前已经运算的后缀积*前缀积
		dfs(edg[i],t);
	}
	return;
}
```

---

## 作者：_HCl_ (赞：0)

简单的换根 DP，但除法真不好处理。

# CF543D 题解

**题意简述**

给定一棵无根树，现在对树上的边进行染色，当以 $x$ 为特殊点时，要求 $x$ 到任意一点的路径上又不超过 $1$ 条未染色边。求出每个点事特殊点时的染色方案树。

**思路引导**

先考虑固定根的情况。设 $f_x$ 是以 $x$ 为根的子树的染色方案，并且从根到 $x$ 的路径都被染过色。

接下来考虑如何从子节点 $y$ 转移到父节点 $x$。

- 如果 $e_{x,y}$ 不染色，那么以 $y$ 为根的子树必须全部染色。否则其中一点到根的路径上就有两条未染色边。方案数为 $1$。
- 如果 $e_{x,y}$ 染色，那么以 $y$ 为根的子树染色方案数是 $f_y$。

根据乘法原理，$f_x=\prod_{y\in son_x}\limits(f_y+1)$。

然后考虑换根。用 $h_x$ 表示以 $x$ 往上的区域的方案数。如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/al2m940t.png)

其中，$h_y$ 是绿色区域，$h_x$ 是红色区域。$h_y$ 可以由 $h_x$ 转移而来，可以视为是 $x$ 下面的小三角形（子树）和红色区域 $h_x$ 合并的结果。那么有 $h_y=(h_x+1)\dfrac{f_x}{f_y+1}$。其中，$\dfrac{f_x}{f_y+1}$ 就是小三角形所表示的。

设 $g_x$ 是以 $x$ 为特殊点（根）的答案，那么有 $g_x=f_x(h_x+1)$。

但是考虑到可能 $MOD\mid (f_y+1)$，此时 $(f_y+1)$ 的逆元不存在，所以不能用逆元处理。因此我们考虑，对于 $x$，求出 $(f_y+1)$ 的前缀积 $pre$ 和后缀积 $suf$，其中 $y$ 是 $x$ 的儿子。这样就可以用 $pre$ 和 $suf$ 相乘代替除法。

对于 DP 的边界条件，$f_x=1$ 当 $x$ 是叶子节点时；$g_1=f_1$；$h_1=0$。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005,MOD=1000000007;
int n;
vector<int> e[N];
int f[N],g[N],h[N],pre[N],suf[N];
void dfs1(int x,int fa){
	f[x]=1;
	for(auto y:e[x]){
		if(y==fa)continue;
		dfs1(y,x);
		f[x]=(f[x]*(f[y]+1))%MOD;
	}
} 
int las[N],nxt[N];
void dfs2(int x,int fa){
	pre[0]=1;
	int ls=0;
	for(int i=0;i<e[x].size();++i){
		int y=e[x][i];
		if(y==fa)continue;
		las[i]=ls;//las 是 y 左边的节点在 pre 中的下标 
		pre[i+1]=pre[ls]*(f[y]+1)%MOD;//为了方便，整体往右移 
		ls=i+1;
	}
	suf[e[x].size()]=1;
	int nx=e[x].size();
	for(int i=e[x].size()-1;i>=0;--i){
		int y=e[x][i];
		if(y==fa)continue;
		nxt[i]=nx;//nxt 是 y 右边的节点在 suf 中的下标 
		suf[i]=suf[nx]*(f[y]+1)%MOD;
		nx=i;
	}
	for(int i=0;i<e[x].size();++i){
		int y=e[x][i];
		if(y==fa)continue;
		h[y]=(h[x]+1)*pre[las[i]]%MOD*suf[nxt[i]]%MOD;
		g[y]=f[y]*(h[y]+1)%MOD;
	}
	for(auto y:e[x]){
		if(y==fa)continue;
		dfs2(y,x);
	} 
}
signed main(){
	cin>>n;
	for(int i=2;i<=n;++i){
		int p;scanf("%lld",&p);
		e[i].push_back(p);
		e[p].push_back(i);
	}
	dfs1(1,0);
	g[1]=f[1];
	dfs2(1,0);
	for(int i=1;i<=n;++i)cout<<g[i]<<" ";
}
```

---

## 作者：huangrenheluogu (赞：0)

感觉这道题重点根本不是树形 dp，而是逆元的处理。

定首都为根，并且认为不良边为特殊边。

所以首都到任何一个节点之多只有一条特殊边。

因为到任何节点只有一条特殊边，所以可以得到 $x$ 的子树内有特殊边，那么 $x$ 到它父亲的边必然不是特殊边。

这样就有转移了，$f_{x,0/1}$ 表示 $x$ 子树内有/无特殊边的方案总数，细想发现 $f_{x,0}=1$，所以只用考虑 $f_{x,1}$，但是是后来想到了，所以代码里还有 $f_{x,0}=1$ 的描述。

下文中仍然用 $f_{x,0}$ 和 $f_{x,1}$ 描述。

转移是显然的，$f_{x,1}=(\prod\limits_{v\in son_x}(2f_{v,0}+f_{v,1}))-f_{x,0}$。

就是一个简单的容斥。考虑 $(x,v)$ 这一条边，如果 $v$ 子树内没有特殊边，那么可以选择特殊或者不特殊，否则这一条边必须是不特殊的。最后，还会加上所有 $f_{v,0}$ 都选择了不特殊边这样一种情况，那么就减掉 $f_{x,0}$ 即可。

如果上面合并了，可能这个转移比较难解释。

换根很简单，就是记录父亲的贡献，然后对于一个点，去掉答案的贡献（乘上逆元）就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, fir[N], nxt[N], son[N], tot, u, v, f[N][2], ans[N];
inline void add(int x, int y){
    nxt[++tot] = fir[x];
    fir[x] = tot;
    son[tot] = y;
}
inline int ksm(int x, int y){
    int res = 1ll;
    while(y){
        if(y & 1) res = res * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return res;
}
inline int inv(int x){
    x %= mod;
    return ksm(x, mod - 2);
}
inline void dfs(int x){
    f[x][0] = f[x][1] = 1ll;
    for(int i = fir[x]; i ; i = nxt[i]){
        dfs(son[i]);
        (f[x][1] *= (f[son[i]][0] * 2 + f[son[i]][1]) % mod) %= mod;
        (f[x][0] *= f[son[i]][0]) %= mod;
    }
    (f[x][1] -= f[x][0] - mod) %= mod;
    return ;
}
inline void dfs2(int x, int fa0 = 1ll, int fa1 = 1ll){
    if(x != 1){
        f[x][1] = (f[x][1] + f[x][0]) % mod * ((fa0 * 2 + fa1) % mod) % mod;
        (f[x][0] *= fa0) %= mod;
    }
    else (f[x][1] += f[x][0]) %= mod;
    ans[x] = f[x][1];
    int val0, val1;
    for(int i = fir[x]; i ; i = nxt[i]){
        val0 = f[x][0], val1 = f[x][1];
        (val1 *= inv(f[son[i]][0] * 2 + f[son[i]][1] % mod)) %= mod;
        (val0 *= inv(f[son[i]][0])) %= mod;
        dfs2(son[i], val0, (val1 - val0 + mod) % mod);
    }
}
signed main(){
    //freopen("data.in", "r", stdin);
    scanf("%lld", &n);
    for(int i = 2; i <= n; i++){
        scanf("%lld", &u), v = i;
        add(u, v);
    }
    dfs(1);
    //for(int i = 1; i <= n; i++) printf("%lld %lld %lld\n", i, f[i][0], f[i][1]);
    dfs2(1);
    for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    puts("");
    return 0;
}
```

发现 WA on test 10。原因在于逆元中会有 $0$，这样需要特殊关照，写写看比较麻烦（可能我太弱了，现在想来其实挺简单的），所以介绍一种 trick（其实是题解看过来的）。

记录前缀积和后缀积，到时候前缀积和后缀积乘起来，就可以避免逆元的操作。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, fir[N], nxt[N], son[N], tot, u, v, f[N][2], ans[N];
vector<int>a[N], b[N];
inline void add(int x, int y){
    nxt[++tot] = fir[x];
    fir[x] = tot;
    son[tot] = y;
}
inline int ksm(int x, int y){
    int res = 1ll;
    while(y){
        if(y & 1) res = res * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return res;
}
inline int inv(int x){
    x %= mod;
    return ksm(x, mod - 2);
}
inline void dfs(int x){
    f[x][0] = f[x][1] = 1ll;
    for(int i = fir[x]; i ; i = nxt[i]){
        dfs(son[i]);
        (f[x][1] *= (f[son[i]][0] * 2 + f[son[i]][1]) % mod) %= mod;
        (f[x][0] *= f[son[i]][0]) %= mod;
    }
    (f[x][1] -= f[x][0] - mod) %= mod;
    return ;
}
inline void dfs2(int x, int fa0 = 0ll, int fa1 = 1ll){
    if(x != 1){
        //printf("%lld %lld %lld\n", x, fa0, fa1);
        f[x][1] = (f[x][1] + f[x][0]) % mod * ((fa0 * 2 + fa1) % mod) % mod;
        (f[x][0] *= fa0) %= mod;
    }
    else (f[x][1] += f[x][0]) %= mod;
    ans[x] = f[x][1];
    a[x].pb(1ll), b[x].pb(1ll);
    for(int i = fir[x]; i ; i = nxt[i]){
        a[x].pb((2 * f[son[i]][0] + f[son[i]][1]) % mod);
        b[x].pb((2 * f[son[i]][0] + f[son[i]][1]) % mod);
    }
    a[x].pb((2 * fa0 + fa1) % mod);
    b[x].pb((2 * fa0 + fa1) % mod);
    int cnt = a[x].size(), val0, val1;
    for(int i = 1; i < cnt; i++) a[x][i] = a[x][i] * a[x][i - 1] % mod;
    for(int i = cnt - 2; ~i; i--) b[x][i] = b[x][i] * b[x][i + 1] % mod;
    cnt = 0;
    for(int i = fir[x]; i ; i = nxt[i]){
        cnt++;
        val0 = 1ll;
        val1 = a[x][cnt - 1] * b[x][cnt + 1] % mod;
        dfs2(son[i], 1ll, (val1 - 1ll + mod) % mod);
    }
}
signed main(){
    //freopen("data.in", "r", stdin);
    scanf("%lld", &n);
    for(int i = 2; i <= n; i++){
        scanf("%lld", &u), v = i;
        add(u, v);
    }
    dfs(1);
    //for(int i = 1; i <= n; i++) printf("%lld %lld %lld\n", i, f[i][0], f[i][1]);
    dfs2(1);
    for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：liangbowen (赞：0)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF543D)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17398821.html)

比较有趣的换根 DP。

## 思路

### First DFS

按照换根 DP 套路，先钦定 $1$ 为首都（即根节点），并计算。

显然是树形 DP。设 $dp_{u}$ 表示以 $u$ 为根的子树全部满足的方案数。

对于一条树边 $(u, v)$：

+ 如果 $(u,v)$ 修，就意味着 $v$ 对应子树的所有点，还有一次不修的机会，即 $dp_v$。
+ 如果 $(u,v)$ 不修，没容错了，下面的全得修，就是 $1$。

综上，$dp_u=\prod\limits_{\text{son}=v} dp_u \times (dp_v+1)$。

### Second DFS

进行换根。

假设当前根为 $u$。对于一条树边 $(u, v)$，我们可以换根 $\text{root}=v$，那么：

+ $u$ 少了 $v$ 原本的那个子树。相当于原本答案去除 $(dp_v+1)$ 这个分支，即除法（考虑逆元？）。
+ $v$ 多了 $u$ 这个子树。同样的，相当于添加了 $(dp_u+1)$ 这个分支，即乘法。

按照上述转移就做完了。但是！由于 $0$ 没有逆元，所以直接除不可取。使用前后缀积的方式快速维护，参考代码。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
struct Edge {int now, nxt;} e[N << 1];
int head[N], cur;
void add(int u, int v)
{
	e[++cur].now = v, e[cur].nxt = head[u];
	head[u] = cur;
}
int dp[N]; //dp[u] : 以u为根的方案数 
//如果(u,v)修，就是 dp[v]：如果(u,v)不修，下面的全得修，就是1。dp[u]=prod dp[u] * (dp[v]+1)
void dfs(int u, int fa)
{
	dp[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (v == fa) continue;
		dfs(v, u), dp[u] = 1ll * dp[u] * (dp[v] + 1) % mod;
	}
}
#define update(x) pre.push_back(x + 1), suf.push_back(x + 1)
void DFS(int u, int fa, int mulfa)
{
	vector <int> pre, suf;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (v == fa) {if (mulfa != -1) update(mulfa);}
		else update(dp[v]);
	}
	int siz = pre.size();
	
	#define lst(i) (i == 0 ? 1 : pre[i - 1])
	#define nxt(i) (i == siz - 1 ? 1 : suf[i + 1])
	for (int i = 0; i < siz; i++) pre[i] = 1ll * pre[i] * lst(i) % mod;
	for (int i = siz - 1; ~i; i--) suf[i] = 1ll * suf[i] * nxt(i) % mod;
	
	for (int i = head[u], pos = 0; i; i = e[i].nxt, pos++)
	{
		int v = e[i].now;
		if (v == fa) continue;
		int tmp = 1ll * lst(pos) * nxt(pos) % mod;
		dp[v] = 1ll * dp[v] * (tmp + 1) % mod, DFS(v, u, tmp);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
	{
		int u;
		scanf("%d", &u);
		add(i, u), add(u, i);
	}
	dfs(1, 0), DFS(1, 0, -1);
	for (int i = 1; i <= n; i++) printf("%d ", dp[i]);
	return 0;
}
```

希望能帮助到大家！

---

## 作者：81179332_ (赞：0)

换根 dp

先考虑固定根的情况：设 $f_i$ 表示子树 $i$ 的方案数

对于叶子节点，显然 $f_i=1$

设当前节点为 $u$，它的一个儿子节点为 $v$，若改善 $u\rightarrow v$ 的边，则方案为 $f_v$；若不改善，则方案为 $1$

所以 $f_u=\prod\limits_{v\in son(u)}(f_v+1)$

考虑将 $u$ 从根变为 $v$ 的儿子，则 $f'_u=\dfrac{f_u}{f_v+1}=\prod\limits_{j\in son(u),j\neq v}(f_j+1)$

这个维护一个前缀积一个后缀积即可

```cpp
//timeuse:15min
const int N = 200010,M = N;
int n;EE(1);
ll dp[N],ans[N];
void dfs1(int u,int fa)
{
	dp[u] = 1;
	for(int i = head[u],v;i;i = e[i].nxt) if((v = e[i].to) != fa)
		dfs1(v,u),dp[u] = dp[u] * (dp[v] + 1) % mod;
}
void dfs2(int u,int fa)
{
    ans[u] = 1;vector<ll> pre,suf;
    int tot = 0;
    for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].to;
		ans[u] = ans[u] * (dp[v] + 1) % mod;
		if(v != fa) pre.push_back(dp[v] + 1),suf.push_back(dp[v] + 1),tot++;
	}
	for(int i = 1;i < tot;i++) pre[i] = pre[i] * pre[i - 1] % mod;
	for(int i = tot - 2;i >= 0;i--) suf[i] = suf[i] * suf[i + 1] % mod;
    int now = 0;
    for(int i = head[u],v;i;i = e[i].nxt) if((v = e[i].to) != fa)
	{
		dp[u] = dp[fa] + 1;
		if(now > 0) dp[u] = dp[u] * pre[now - 1] % mod;
        if(now < tot - 1) dp[u] = dp[u] * suf[now + 1] % mod;
        dfs2(v,u),now++;
    }
}
int main()
{
	n = read();for(int i = 2;i <= n;i++) add_edge(read(),i);
	dfs1(1,0),dfs2(1,0);
    for(int i = 1;i <= n;i++) pprint(ans[i]);
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

记 $f_i$ 为 $i$ 到子树内点都满足要求的方案数，$g_i$ 为 $i$ 到子树外点都满足要求的方案数，那么对于最后的每个点的答案就是 $f_i \cdot g_i$。

首先考虑 $f_i$，我们显然有转移 $f_u = \prod_{v \in \text{son}_u} (f_v + 1)$。然后我们考虑换根计算 $g_i$，我们考虑当前计算的是 $g_u$，那么我们的答案就分为两个部分，第一个部分是 $g_{fa_u}$，代表先从 $u$ 走到 $fa_u$ 然后满足条件的方案数，第二种是走到 $fa_u$ 其他子树的点，这种情况的答案为 $\prod_{v \in \text{son}_{fa_u}, v \neq u} (f_v + 1)$，用一个前缀积和一个后缀积即可计算，这两个部分乘起来即可，但是这样我们没考虑所有边都修的情况，所以答案要加 $1$。时间复杂度 $O(n)$。[Code](https://codeforces.com/contest/543/submission/211349997)

---

## 作者：derta (赞：0)

以下的转移方程均在模 $10^9+7$ 意义下进行

设 $f_i$ 为以 $i$ 为根的子树首都为 $i$ 时改良道路的方案数，则有
$$f_i=\prod_{j \in \text{son}(i)} (f_j+1)$$
$f_j$ 代表改良 $i$ 到 $j$ 这条路，$1$ 代表不改良 $i$ 到 $j$ 这条路（此时以 $j$ 为根的子树中的道路必须全部被改良，故只有 $1$ 种）

之后考虑换根 dp，设 $g_i$ 为首都为 $i$ 时道路改良的方案数，则
$$g_i=f_i\left(\frac{g_{\text{father}(i)}}{f_i+1}+1\right)$$
再令 $f_i=g_i$，求解子树即可

但这样就完了吗？不是的，如果 $f_i+1=0$ 上式就炸了。于是设 $h_i$ 表示去掉一个满足 $f_j+1=0$ 的以 $j$ 为根的子树后改良道路的方案数，可以发现不管去掉哪棵子树 $h_i$ 都是一样的。转移方程不太好解释，具体见代码

```cpp
void get_f(int i, int father) {
	bool flag = false; //有没有去掉过方案数为0的子树 
	f[i] = h[i] = 1; //别忘了给h赋初始值 
	for(int j = 0; j < (int)G[i].size(); ++j) {
		int s = G[i][j];
		if(s != father) {
			get_f(s, i);
			f[i] = 1LL*f[i]*(f[s] + 1)%MOD; 
			if(f[s] + 1 != MOD || flag == true) //子树方案数不为0 或 已经去掉一个方案数为0的子树了 
				h[i] = 1LL*h[i]*(f[s] + 1)%MOD; //注意是乘，不是直接赋f[i] 
			else //子树方案数为0 且 没有去掉过方案数为0的子树 
				flag = true; //把当前子树去掉，更新标记 
		}
	}
}
```

然后就是换根，注意及时更新 $f_i$ 和 $h_i$

```cpp
void get_g(int i, int father) {
	//这里是用g[i]转移到g[son(i)] 
	for(int j = 0; j < (int)G[i].size(); ++j) {
		int s = G[i][j];
		if(s != father) {
			int fs = f[s], fi = (fs + 1 == MOD ? h[i] : 1LL*f[i]*inv(fs + 1)%MOD), hs = h[s];
			//fs表示题解中的f[i]，fi表示题解中的g[father(i)]，hs表示题解中的h[i] 
			g[s] = f[s] = 1LL*fs*(fi + 1)%MOD;
			if(f[s] != 0 || fs == 0) //没有方案数为0的子树 或 已经去掉过方案数为0的子树了 
				h[s] = 1LL*h[s]*(fi + 1)%MOD; //注意这里不是直接赋f[s] 
			get_g(s, i);
			f[s] = fs, h[s] = hs; //回溯 
		}
	}
}
```

---

