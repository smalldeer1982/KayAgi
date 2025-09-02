# [PA 2024] Grupa permutacji

## 题目背景

PA 2024 2A

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 2 [Grupa permutacji](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/gru/)**

在本题中，我们将处理 $n$ 个元素的排列。$n$ 个元素的排列是由 $1$ 到 $n$（包含两端）的 $n$ 个不同的自然数组成的序列。将排列 $a_1,a_2,\ldots,a_n$ 和排列 $b_1,b_2,\ldots,b_n$ 复合起来，会得到排列 $a_{b_1},a_{b_2},\ldots,a_{b_n}$。我们称任意满足 $i<j$ 且 $p_i>p_j$ 的数对 $(i,j)$ 为排列 $p_1,p_2,\ldots,p_n$ 的逆序对。

Bytie 是 $n$ 个元素的排列的忠实粉丝。他非常喜欢它们，并且其中有一些是他最喜欢的。他决定开始在一张纸上写下通过复合他最喜欢的排列（以任何顺序，也许多次使用其中一些排列）能得到的所有排列，并小心翼翼地保证不写出任何排列超过一次。

毫无疑问，他很快就用完了纸张。然后 Bytie 有一个问题：如果他列出所有可能的排列，它们平均会有多少个逆序对？

帮他写一个程序来计算这个值。更具体地说，输出答案对 $10^9+7$ 取模后的值（详见「输出格式」部分）。

## 说明/提示

在第一组样例中，Bytie 会写下排列 $\{1,2,3\}$（有 $0$ 个逆序对），排列 $\{2,3,1\}$（有 $2$ 个逆序对）和排列 $\{3,1,2\}$（有 $2$ 个逆序对）。因此平均逆序对个数为 $\frac{4}{3}$。且 $3^{-1}\equiv 333333336\pmod{10^9+7}$，因此答案为 $333333336\cdot 4\equiv 1333333344\equiv 333333337\pmod{10^9+7}$。

在第二组样例中，Bytie 会写下 $5$ 个元素的所有排列。容易证明它们平均有 $5$ 个逆序对。

## 样例 #1

### 输入

```
3 1
2 3 1
```

### 输出

```
333333337
```

## 样例 #2

### 输入

```
5 2
2 1 3 4 5
2 3 4 5 1
```

### 输出

```
5```

# 题解

## 作者：yyyyxh (赞：9)

orz 群论。

之前看到 grass8cow 博客中关于 [Grupa Permutacji](https://www.luogu.com.cn/problem/P10353) 这道题做法的简略记述后一直感觉这个题是究极神秘题。APIO 听了 Kubic 的讲课（当时讲的是 [LOJ177 生成子群阶数](https://loj.ac/p/177)）后终于算是懂了一点了。

众所周知，所有有限群同构于一个置换群的子群。当我们拿着一堆置换，然后再复合来复合去，所有可能得到的结果自然生成了一个群。grupa 这个题研究了这个群的平均逆序对个数，而 LOJ177 研究了这个群的大小。以前我一直认为这种东西很难做，出乎意料的是这两个问题都可以做到 $O(\text{poly}(n))$。

解决这两个问题的第一个共同关键是在于生成子群的“均匀性”。我们这样描述这个性质：对于所有置换的第 $i$ 位 $p_i$ 来说，假设 $p_i$ 有 $k$ 种不同的取值 $a_1,a_2,\dots,a_k$，则 $p_i$ 取到这 $k$ 种取值中的每种取值的方案数都是一样的。这个结论不仅对于单个 $p_i$ 成立，对于多个 $p_i$ 取值集合笛卡尔积形成的多元组来说也是成立的。

比如说，对于 grupa 这个题我们研究逆序对，所以对于一个下标二元组 $(i,j)$，生成子群中所有元素的取值二元组 $(p_i,p_j)$ 取到每种可能的取值的概率相等。逆序对就是 $i<j,p_i>p_j$ 的元组。所以我们直接对于每一个生成元排列的每一个二元组连双向边 $(i,j)\leftrightarrow (p_i,p_j)$，然后统计每个连通块中满足 $i<j$ 和 $i>j$ 的元组数，分别设为 $a,b$，则从每个 $i<j$ 的元组出发到 $i>j$ 的元组的概率是 $\frac{b}{a+b}$，对答案的总贡献就是 $\frac{ab}{a+b}$。我们得到了一个 $O(n^3)$ 的做法。

如何说明这种“均匀性”呢？我们考虑建图分析。对于每个生成元置换 $s$ 中若干个固定的下标形成的多元组 $(\alpha_1,\alpha_2,\dots \alpha_m)$ 向 $(s_{\alpha_1},s_{\alpha_2},\dots s_{\alpha_m})$ 连边，再在这条边上写上 $s$ 作为边权。

由于置换群不断的复合自己总会走回自己，所以说我们同时可以连一条反向边，再写上 $s^{-1}$ 作为边权，所以我们可以直接将这张图当成无向图处理。不过就我们下面的分析来说有向图也没影响。

这样，你从任意元组 $rt$ 开始 dfs，能 dfs 到的所有元组就是它能取到的所有取值元组。而你取任意一条路径 $rt\to x$，其上的所有边依次复合就得到了取到这个取值元组的一个置换。

我们不妨取一个以 $rt$ 为根的 dfs 生成树。这样对于每一个 $rt\to x$ 就钦定了唯一一条路径，那么对于一个取值元组取到 $x$ 的方案，我们这条路径上的置换一一逆复合回去，由于置换群逆元存在且唯一，那么每一个取值元组取到 $x$ 的置换一一对应着一个取值元组取到 $rt$ 的置换。均匀性得证。

解决这两个问题第二个共同的关键在于如何削减生成元集合的大小，也就是说找到另一组生成元集合使得它们跟原生成元集合生成的群同构。如果你无聊中翻过 OI-wiki 中一些较为冷门的页面，你可能会知道 [schreier-sims 算法](https://oi-wiki.org/math/schreier-sims/) 给出了一个这个问题的确定性做法。我没有认真看过这个算法 QwQ，只大致看过 Kubic APIO 讲义里的东西，但是更适合 ~~OI 宝宝体质~~的做法是：随机选取一个生成元的子集，以任意顺序复合起来，重复足够多次之后将有大概率得到一些能够生成原来的群的置换。

所以对于 grupa 这个题我们选取 $O(\log)$ 个子集后就得到了一个 $O(n^2\log n)$ 的做法？！？！

```cpp
// ...
int n,k;
int a[N][N];
int p[N],q[N];
inline int id(int x,int y){return (x-1)*n+y;}
int f[N*N],inv[N*N];
int ca[N*N],cb[N*N];
int rt(int x){
	if(f[x]==x) return x;
	return f[x]=rt(f[x]);
}
int main(){
	n=read();k=read();
	for(int i=1;i<=k;++i)
		for(int j=1;j<=n;++j) a[i][j]=read();
	for(int i=1;i<=n*n;++i) f[i]=i;
	for(int it=0;it<L;++it){
		for(int t=1;t<=n;++t) p[t]=t;
		for(int i=1;i<=k;++i)
			if(rng()&1){
				for(int t=1;t<=n;++t) q[p[t]]=a[i][t];
				for(int t=1;t<=n;++t) p[t]=q[t];
			}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j){
				if(i==j) continue;
				f[rt(id(i,j))]=rt(id(p[i],p[j]));
			}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			if(i<j) ++ca[rt(id(i,j))];
			else ++cb[rt(id(i,j))];
		}
	inv[1]=1;
	for(int i=2;i<=n*n;++i) inv[i]=(ll)inv[P%i]*(P-P/i)%P;
	int res=0;
	for(int i=1;i<=n*n;++i)
		if(f[i]==i&&ca[i]&&cb[i]) res=(res+(ll)ca[i]*cb[i]%P*inv[ca[i]+cb[i]])%P;
	printf("%d\n",res);
	return 0;
}
```

再考虑 LOJ177 这个题。我们统计有多少种置换，不妨先统计 $p_n$ 有多少种取值，然后再统计强制 $p_n=n$ 的方案数，两者相乘就是答案。

前者方法我们已经熟知，后者可以这样考虑：之前我们建出来的每一个经过 $n$ 的环都是一个 $p_n=n$ 的方案，我们有一组可以生成它们的生成元：对于每一条边 $(u,v)$，取 $n\to u,u\to v,v\to n$ 这个环。对于这些生成元我们缩减它的集合大小至 $O(n)$，就可以递归到一个 $n-1$ 的问题了！我们在 $O(n^5)$ 的时间内解决了 LOJ177。

```cpp
// ... const int B >= O(n);
struct perm{
	int p[N];
	void init(){
		for(int i=1;i<=n;++i) p[i]=i;
	}
	friend perm operator+(const perm a,const perm b){
		perm c;
		for(int i=1;i<=n;++i) c.p[i]=b.p[a.p[i]];
		return c;
	}
	perm inv(){
		perm x;
		for(int i=1;i<=n;++i) x.p[p[i]]=i;
		return x;
	}
}a[N],b[N],path[N<<1];
vector<pii> vec[N];
ll res[10];int len;
bool vis[N];
void dfs(int u,perm cur){
	path[u]=cur;
	vis[u]=1;++num;
	for(auto [v,w]:vec[u]){
		if(vis[v]) continue;
		dfs(v,cur+a[w]);
	}
}
void iter(){
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j) vec[j].emplace_back(a[i].p[j],i);
	perm Init;
	Init.init();
	dfs(n,Init);
	for(int i=1;i<=n;++i) path[i+n]=path[i].inv(),vec[i].clear();
	for(int it=1;it<=B;++it){
		b[it].init();
		for(int i=1;i<=m;++i)
			for(int j=1;j<=n;++j)
				if(vis[j]&&(rng()&1)) b[it]=b[it]+path[j]+a[i]+path[a[i].p[j]+n];
	}
	for(int i=1;i<=n;++i) vis[i]=0;
	m=B;
	for(int i=1;i<=m;++i) a[i]=b[i];
	--n;
	ll carry=0;
	for(int i=0;i<=len;++i){
		res[i]*=num;res[i]+=carry;
		carry=res[i]/T;res[i]%=T;
	}
	if(carry) res[++len]=carry;
	num=0;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j) a[i].p[j]=read();
	res[len=0]=1;
	while(n) iter();
	printf("%lld",res[len]);
	for(int i=len-1;~i;--i) printf("%016lld",res[i]);
	putchar('\n');
	return 0;
}
```

upd:

拜谢环一周！在与环一周讨论后我们弄明白了这样一个问题：

对于一个群，我们求其最少生成元个数，称为这个群的秩。

一个群的秩是可以达到 $O(n)$ 级别的，构造一些二元环即可顶到这个界。

所以说求群阶数时一定要保留 $O(n)$ 级别的生成元。

但 grupa 那个题只需要你把生成元连成的图连出来，这时候不需要遍历到所有生成元就可以建出这张图了，所以只需要保留 $O(\log n)$ 级别的生成元。

---

## 作者：qiuzx (赞：3)

[PA2024 题解全集](https://www.luogu.com.cn/article/gi139pd4)

发现计算可以得到的排列总数这件事甚至都是困难的，因此我们的期望可能不能使用总和除以总数来计算。所以考虑直接从概率的角度入手，计算每一对 $i<j$ 在这些排列中满足 $p_i>p_j$ 的概率。

假如 $(i,j)$ 可以出现在 $(x_1,y_1),(x_2,y_2),\cdots,(x_k,y_k)$ 这些位置，那么根据对称性，$(i,j)$ 出现在这些位置中的每一个的概率都应该是相等的。那么如何求出这些位置呢？一个简单的想法就是将 $(i,j)$ 看成点，则对于每个排列 $p$，将 $(i,j)$ 和 $(p_i,p_j)$ 合并在一起，那么最后 $(i,j)$ 的等价类中的点就是它能够到达的点。这样可以使用并查集来维护。于是我们得到了一个复杂度 $O(kn^2)$ 的做法。

那么怎么优化呢？我们发现并没有更好的办法刻画 $(i,j)$ 能到达的点，于是只能从这个做法本身入手优化。假如数据随机，那么期望 $O(\log n)$ 个排列就可以组成所有的排列了。然而由于这里排列是给定的，所以可以卡满。但是我们可以利用和这个随机相似的想法搞一些事情。具体来说，如果我们随便从这些排列中选一些，将它们复合之后作为一个新的排列，那么这样是不是只需要随机期望 $O(\log n)$ 次就可以形成所有的排列了呢？事实上这个结论是对的，证明之后补上。

现在有了这个结论，那么做法就十分容易了。我们做 $O(\log n)$ 轮，每次对每个排列以 $1/2$ 的概率选择，若选择则将它作用到一个初始为单位排列的排列上，最后用这个排列来更新并查集。这样做的复杂度为 $O(n(n+k)\log n)$，可以通过。

``` c++
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define mod 1000000007
#define F first
#define S second
#define ll int
#define N 3010
#define M 10000010
using namespace std;
mt19937_64 rnd(114514);
ll ksm(ll x,ll y)
{
	ll ret=1;
	while(y)
	{
		if(y&1)
		{
			ret=(1ll*ret*x)%mod;
		}
		x=(1ll*x*x)%mod;
		y>>=1;
	}
	return ret;
}
ll n,k,fa[M],p[N][N],f[N],g[N],val[M][2];
ll getf(ll x){return x==fa[x]?x:fa[x]=getf(fa[x]);}
void update()
{
	ll i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
				fa[getf(i*n+j)]=getf(f[i]*n+f[j]);
			}
		}
	}
	return;
}
int main(){
	ll i,j,t;
	scanf("%d%d",&n,&k);
	for(i=0;i<k;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&p[i][j]);
			p[i][j]--;
		}
	}
	for(i=0;i<n*n;i++)
	{
		fa[i]=i;
	}
	for(t=0;t<40;t++)
	{
		for(i=0;i<n;i++)
		{
			f[i]=i;
		}
		for(i=0;i<k;i++)
		{
			if(rnd()&1)
			{
				for(j=0;j<n;j++)
				{
					g[j]=f[p[i][j]];
				}
				for(j=0;j<n;j++)
				{
					f[j]=g[j];
				}
			}
		}
		update();
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				continue;
			}
			val[getf(i*n+j)][i>j]++;
		}
	}
	ll ans=0;
	for(i=0;i<n*n;i++)
	{
		if(val[i][0]||val[i][1])
		{
			ans=(ans+((1ll*((1ll*val[i][0]*val[i][1])%mod)*ksm(val[i][0]+val[i][1],mod-2))%mod))%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

