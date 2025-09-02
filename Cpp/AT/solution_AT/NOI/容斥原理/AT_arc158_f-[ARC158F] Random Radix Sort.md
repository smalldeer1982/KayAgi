# [ARC158F] Random Radix Sort

## 题目描述

对于非负整数 $x,\ k$，$x$ 的 $10^k$ 位是指 $\bigl\lfloor\ \frac{x}{10^k}\bigr\rfloor$ 除以 $10$ 的余数。例如，$123$ 的 $10^0$、$10^1$、$10^2$、$10^3$ 位分别为 $3,\ 2,\ 1,\ 0$。

给定正整数 $N,\ M,\ K$ 以及非负整数序列 $A = (A_1,\ \ldots,\ A_N)$，$B = (B_1,\ \ldots,\ B_N)$。

我们考虑通过以下步骤对 $A$ 进行重排：

- 重复 $M$ 次以下操作：
  - 选择一个整数 $k$，满足 $0 \leq k \leq K-1$。
  - 然后，对 $A$ 按照 $10^k$ 位进行稳定排序。也就是说，对于 $d=0,1,\ldots,9$，定义 $A^{(d)}$ 为 $A$ 中 $10^k$ 位等于 $d$ 的所有元素组成的子序列，然后将 $A^{(0)},\ A^{(1)},\ \ldots,\ A^{(9)}$ 按顺序连接起来，替换 $A$。

这样的操作共有 $K^M$ 种可能。请计算，经过这些操作后，$A$ 恰好变为 $B$ 的方案数，并对 $998244353$ 取模。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 10^9$
- $1 \leq K \leq 18$
- $0 \leq A_i < 10^K$
- $0 \leq B_i < 10^K$
- $A$ 和 $B$ 作为多重集是相同的。也就是说，对于任意整数 $x$，$x$ 在 $A$ 中出现的次数等于其在 $B$ 中出现的次数。

## 样例解释 1

第 $1$ 次选择的 $k$ 记为 $k_1$，第 $2$ 次选择的 $k$ 记为 $k_2$。例如，当 $k_1 = 0,\ k_2 = 1$ 时，$A$ 的变化如下：
- 先对 $10^{k_1} = 10^0$ 位进行稳定排序，$A$ 变为 $(42,74,54)$。
- 再对 $10^{k_2} = 10^1$ 位进行稳定排序，$A$ 变为 $(42,54,74)$。

所有操作及其结果如下：
- $(k_1, k_2) = (0,0)$：$A = (42,74,54)$。
- $(k_1, k_2) = (0,1)$：$A = (42,54,74)$。
- $(k_1, k_2) = (0,2)$：$A = (42,74,54)$。
- $(k_1, k_2) = (1,0)$：$A = (42,54,74)$。
- $(k_1, k_2) = (1,1)$：$A = (42,54,74)$。
- $(k_1, k_2) = (1,2)$：$A = (42,54,74)$。
- $(k_1, k_2) = (2,0)$：$A = (42,74,54)$。
- $(k_1, k_2) = (2,1)$：$A = (42,54,74)$。
- $(k_1, k_2) = (2,2)$：$A = (74,42,54)$。

## 样例解释 2

不存在满足条件的操作方案。

## 样例解释 3

所有 $4^{100}$ 种操作方案都满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 3
74 42 54
42 54 74```

### 输出

```
5```

## 样例 #2

### 输入

```
2 1 1
2 3
3 2```

### 输出

```
0```

## 样例 #3

### 输入

```
5 100 4
0 12 34 56 78
0 12 34 56 78```

### 输出

```
982924732```

# 题解

## 作者：云浅知处 (赞：5)

首先，对于相同的元素，由于稳定排序不改变相对次序，因此我们可以直接处理出来每个 $B_i$ 对应的是哪个 $A_j$。

考虑先后两次排序 $0\le i,j<K$，发现相当于按照第 $j$ 位为第一关键字，第 $i$ 位为第二关键字的排序。显然多次排序也是一样的，那么如果出现了 $i,j,i$ 这样的排序，相当于以 $i$ 为第一关键字，$j$ 为第二关键字，接下来应该是 $i$ 为第三关键字排序；但是 $i$ 本来就是第一关键字，因此前面那次排序是没用的。

因此，我们只需要考虑每一个位最后被排序的时刻，然后会得到一个 $0,1,\cdots,K-1$ 的排列（准确来说不一定是排列，某些元素可能根本没有出现过）。我们要做的就是对每个排列判断是否合法，再计算方案数。

枚举排列自然是不行的。首先考虑方案数怎么算，发现每一位等价，因此这个数只与排列大小相关；对于 $a$ 元的排列，他就等于最终恰好用到这 $a$ 个数的方案数除掉 $a!$。由容斥可得方案数为

$$
\frac{1}{a!}\sum_{i=0}^a(-1)^i\binom{a}{i}(a-i)^M
$$

- 实际上这就是第二类斯特林数。

对于排列的部分，考虑 $B$ 那边的限制实际上是啥。发现只需要最终 $B_i$ 在 $B_{i+1}$ 的左边。

如果 $B_i=B_{i+1}$，那么没有约束；否则考虑所有 $B_{i,x}\neq B_{i+1,x}$ 的位 $x$（这里记 $B_{i,x}$ 表示 $B_i$ 在十进制下的第 $x$ 位），把他们分为 $B_{i,x}<B_{i+1,x}$ 与 $B_{i,x}>B_{i+1,x}$ 的两个集合 $S,T$，那么对任意 $x\in T$，$x$ 的关键字次序前面必须排一个 $y\in S$ 的 $y$；如果 $T=\varnothing$，那么就不能有这样的 $x$。此外，如果原序列中 $B_i,B_{i+1}$ 的次序和现在这个序列不一样，那么至少要进行一次 $x\in S$ 的排序。

接下来就可以状压了。从高优先级的关键词往低优先级的关键字填，$f(S)$ 表示填完 $S$ 的方案数。那么接下来能填 $x$ 当且仅当对每个 $x$ 的约束 $T$，均有 $S\cup T\neq \varnothing$。那么不能填 $x$ 就当且仅当存在 $x$ 的约束 $T$ 使得 $T\subseteq U-S$。对每个 $x$ 做高维前缀和即可，复杂度 $O(K^22^K)$。

总复杂度 $O(N\log N+NK+K^22^K)$，三部分分别是求对应次序，处理约束，高位前缀和及状压 DP。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define int long long//他急了他急了 

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=2e5+5;
const int K=18;

ll a[N],b[N];
int n,m,k,w[K+1],f[1<<K];
int fac[K+1],ifac[K+1];

void init(int MV){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=MV;i++)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[MV]=inv(fac[MV]);for(int i=MV-1;i>=1;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
	if(x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

pair<ll,int>pa[N],pb[N];
#define fi first
#define se second
#define mk make_pair

int pos[N];
vector<int>lim[K],L;

void FMT(vector<int>&A){
	for(int i=0;i<k;i++){
		for(int S=0;S<(1<<k);S++)if(S&(1<<i))A[S]|=A[S^(1<<i)];
	}
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read(),m=read(),k=read();init(k+1);
	for(int i=1;i<=n;i++)a[i]=read(),pa[i]=mk(a[i],i);
	for(int i=1;i<=n;i++)b[i]=read(),pb[i]=mk(b[i],i);
	
	sort(pa+1,pa+n+1),sort(pb+1,pb+n+1);
	for(int i=1;i<=n;i++){
		assert(pa[i].fi==pb[i].fi);
		pos[pb[i].se]=pa[i].se;
	}
	
	for(int i=0;i<k;i++)lim[i].resize(1<<k);L.resize(1<<k);
	for(int i=1;i<n;i++){
		int S=0,T=0;ll x=b[i],y=b[i+1];
		for(int j=0;j<k;j++){
			if(x%10<y%10)S|=(1<<j);
			if(x%10>y%10)T|=(1<<j);
			x/=10,y/=10;
		}
		for(int j=0;j<k;j++)if(T&(1<<j))lim[j][S]=1;
		if(pos[i]>pos[i+1])L[S]=1;
	}
	
	for(int i=0;i<k;i++)FMT(lim[i]);FMT(L);
	
	for(int i=1;i<=k;i++){
		for(int j=0;j<=i;j++){
			if(j&1)add(w[i],mod-1ll*C(i,j)*ksm(i-j,m)%mod);
			else add(w[i],1ll*C(i,j)*ksm(i-j,m)%mod);
		}
		w[i]=1ll*w[i]*ifac[i]%mod;
	}
	
	f[0]=1;int U=(1<<k)-1;
	for(int S=0;S<(1<<k);S++){
		for(int i=0;i<k;i++){
			if(S&(1<<i))continue;
			if(lim[i][U-S])continue;
			add(f[S|(1<<i)],f[S]);
		}
	}
	int ans=0;
	for(int S=0;S<(1<<k);S++){
		if(L[U-S])continue;
		add(ans,1ll*f[S]*w[__builtin_popcount(S)]%mod);
	}
	cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc158_f)

**题目大意**

> 给 $n$ 个十进制 $k$ 位数，$m$ 次操作，每次选一个位 $d\in[0,k)$，按第 $d$ 位上的值从小到大进行稳定排序。
>
> 求最终让 $a_1\sim a_n$ 变成 $b_1\sim b_n$ 的方案数。
>
> 数据范围：$n\le 2\times 10^5,k\le 18$。

**思路分析**

首先同一个 $d$ 操作多次，只有最后一次操作有意义，因此我们只要暴力一个长度 $\le k$ 的排列即可。

对于一个长度为 $i$ 的排列，把他们填进长度为 $m$ 的序列且每种颜色最后一项满足顺序要求方案数就是 $\begin{Bmatrix}m\\i\end{Bmatrix}$（第二类斯特林数），即把 $m$ 个下表分成 $i$ 个颜色，颜色之间按最大下标自动定序。

接下来只要考虑一些排列是否合法即可。

由于基数排序不改变值相等的数的相对顺序，因此我们能知道 $b_i$ 究竟是原来的那个元素 $a_{p_i}$。

对于每一对 $(b_i,b_{i+1})$，设 $S_i=\{j\mid b_{i,j}<b_{i+1,j}\},T_i=\{j\mid b_{i,j}>b_{i+,j}\}$。

显然为了保证他们的相对顺序，我们要求所有 $T_i$ 中最后一个元素出现早于 $S_i$ 中最后一个元素出现。

但这并不够，如果 $p_i>p_{i+1}$，我们们要求 $S_i$ 中至少有一个元素被选。

然后就可以 dp 了，从后往前考虑排列 $f_{s}$ 表示当前排列的后缀时 $s$ 的答案。

加入 $k$ 时我们要求 $\forall k\in T_{x},S_x\cap s=\varnothing$，这个可以快速判定，维护所有 $S_x$ 的超集，并判断其中是否有 $\overline s$ 即可，用高维前缀和维护即可。

最后统计答案类似，维护所有 $p_i>p_{i+1}$ 的 $S_i$ 的超集，如果 $\overline s$ 不在其中就把答案加上 $dp_s\times \begin{Bmatrix}m\\s\end{Bmatrix}$。

第二类斯特林数可以用容斥原理暴力算。

时间复杂度 $\mathcal O(n\log n+nk+k^22^k)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
ll a[MAXN],b[MAXN];
int n,k,m,ida[MAXN],idb[MAXN],pre[MAXN];
bool p[18][1<<18],q[1<<18]; //insert after & not empty
ll dp[1<<18],fac[20],ifac[20],f[20];
ll C(int x,int y) { return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD; }
void fwt(bool *r) { for(int u=0;u<k;++u) for(int i=0;i<(1<<k);++i) r[i|(1<<u)]|=r[i]; }
signed main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),ida[i]=i;
	for(int i=1;i<=n;++i) scanf("%lld",&b[i]),idb[i]=i;
	stable_sort(ida+1,ida+n+1,[&](int x,int y){ return a[x]<a[y]; });
	stable_sort(idb+1,idb+n+1,[&](int x,int y){ return b[x]<b[y]; });
	for(int i=1;i<=n;++i) pre[idb[i]]=ida[i];
	for(int i=1;i<n;++i) {
		int s=0,t=0; ll x=b[i],y=b[i+1];
		for(int j=0;j<k;++j) {
			if(x%10<y%10) s|=1<<j;
			if(x%10>y%10) t|=1<<j;
			x/=10,y/=10;
		}
		if(pre[i]>pre[i+1]) q[s]=1;
		for(int j=0;j<k;++j) if(t&(1<<j)) p[j][s]=1; 
	}
	fwt(q);
	for(int i=0;i<k;++i) fwt(p[i]);
	int A=(1<<k)-1; dp[0]=1;
	for(int s=0;s<(1<<k);++s) if(dp[s]) {
		for(int j=0;j<k;++j) if(!(s&(1<<j))&&!p[j][A^s]) {
			dp[s|(1<<j)]=(dp[s|(1<<j)]+dp[s])%MOD;
		}
	}
	for(int i=fac[0]=ifac[0]=1;i<=k;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=0;i<=k;++i) {
		for(int j=0;j<=i;++j) {
			f[i]=(f[i]+(j&1?-1:1)*ksm(i-j,m)*C(i,j))%MOD;
		}
		f[i]=(f[i]+MOD)*ifac[i]%MOD;
	}
	ll ans=0;
	for(int s=0;s<(1<<k);++s) if(!q[A^s]) ans=(ans+dp[s]*f[__builtin_popcount(s)])%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：vegetable_king (赞：2)

在[博客](https://yjh965.github.io/post/arc158f-random-radix-sort-ti-jie/)食用更佳。

首先可以发现一个显然的结论，就是对于每一种排序操作，只有最后一次该操作是对最终序列有影响的，于是一个长度为 $m$ 的操作序列 $x$，我们把 $x$ 中所有非最后一次出现的元素删去得到长度最多为 $k$ 的操作序列序列 $y$，这两个操作序列是等价的。

我们考虑对合法的 $y$ 计数，然后考虑乘上一个系数表示每一个 $y$，能拓展出多少种长度为 $m$ 的 $x$。设这个 $y$ 的长度为 $l$，显然乘的系数就是第二类斯特林数 $\begin{Bmatrix}m\\l\end{Bmatrix}$（考虑把 $m$ 个位置划分为无序的 $l$ 组，按照每一组最靠后的位置顺序来给该组元素安排操作），可以用容斥 $O(k^2 \log m)$ 预处理。

现在只需要计数 $y$，考虑对于合法的 $y$ 有什么限制，显然最终只要满足每一个 $i$ 都满足 $b_i$ 都在 $b_{i + 1}$ 的前面即可。

对于每一个 $i$，都有一些位 $p$ 满足 $b_{i, p} < b_{i + 1, p}$，我们称这些位的集合为 $S_i$；还有一些位 $q$ 满足 $b_{i, q} > b_{i + 1, q}$，我们称这些位的集合为 $T_i$。则限制变成以下两种：

1. 对于每一个 $i$，$S_i$ 出现在 $y$ 序列内的最后位置一定后于 $T_i$ 出现在 $y$ 序列内的，否则 $b_i$ 会被排到 $b_{i + 1}$ 之后。

2. 对于所有原本 $b_i$ 在 $b_{i + 1}$ 后面的 $i$，$y$ 序列里必须出现至少一个 $S_i$ 内的元素。

这两种限制都可以简单处理，对于第一种限制，预处理 $bd_j$ 为选了集合 $j$ 的元素，接下来不能放在最前面的元素集合；对于第二种限制，预处理 $ce_j$ 为选了集合 $j$ 的元素，是否满足强制要求。

最后直接 DP 即可：设 $f_j$ 为包含元素为集合 $j$ 的 $y$ 序列方案数，转移则考虑枚举最前面新放了什么。

最终答案为：

$$\sum_S ce_S \begin{Bmatrix}m\\|S|\end{Bmatrix} f_S$$

时间复杂度为 $O(nk + k^2 \log m + k2^k)$，可以轻松通过。

---

## 作者：forest114514 (赞：0)

01 trick 可不是一个能无脑套的东西，随便乱想害人害己，这题也告诉我们看见小值域和排序不一定都是无脑转 01 序列的。

我们发现操作 $m$ 次是诈骗，我们只关心操作过哪些位置，这些位置的第一次操作是有效的，后面都没用了，只用关心选的数量和方案，最后拿个斯特林子集数合并即可，因为斯特林数上指标 $m$ 比较大，拿那个经典的容斥式子算即可做到 $O(K^2\log m)$。

因为稳定排序同数之间顺序不变，首先我们已知最后得到了 $A_{p_i}\to B_i$ 这样一个结果，但是乍一看没啥用，需要考虑尝试得知需要进行哪些排序。

对于相邻的数 $B_i,B_{i+1}$，首先我们知道满足 $b_{i,j}>b_{i+1,j}$ 的位置 $j$ 不能存在一个位置晚于所有 $b_{i,j}<b_{i+1,j}$ 的位置被操作，然后原来的位置 $p_i>p_{i+1}$ 的话满足 $b_{i,j}<b_{i-1,j}$ 的 $j$ 至少一个被操作了。

发现这是一个充要限制，只要相邻两个数知道大小关系所有数都知道了。

总结一下，就是若干条两种限制：

1. 选了某个位置，后面还要有若干个子集，貌满足子集中至少选了一个位置。
2. 某个集合中的位置要选至少一个。

第一条限制的话正着考虑的话后面必须存在这个限制不好满足，我们倒着 DP，这样改成一个数加入的时候需要判断是否合法。

对每个位置显然就是那些限制子集的补集的并集不合法，记录这个极大集合是 $T_a$，所有 $T_a$ 的子集都不合法。

转移就是 $f_{S}\to f_{S\cup \{a\}}(S\nsubseteq T_a)$，这样随便做就行了。

第二条限制容易得到哪些选定的子集不合法在最后考虑就行了。

时间复杂度 $O(nK+K2^K+K^2\log m)$，不是很懂 FWT 在哪一步需要啊，所有限制都是一个极大集合的子集不合法，而且官方题解也是 $O(k2^k) $ 的。

---

## 作者：happybob (赞：0)

不难注意到排序的本质是，从后往前考虑每种排序规则，最后考虑原序列的顺序。所以显然可知对于每一种排序规则只需要保留最后一次，如果确定了最后出现的排序规则的排列，大小为 $|S|$，则原方案数就是 $\begin{Bmatrix} m \\ |S|\end{Bmatrix}$，证明大概就是你要把这 $m$ 个下标分到这些集合，然后由于顺序确定所以集合是无序的，这个直接容斥就能求，当然没注意到这个也可以矩阵快速幂，不是复杂度瓶颈。

然后考虑怎么刻画最后出现的排序，这个东西考虑直接状压 DP，发现对于目前集合 $S$，加入第 $x$ 位是否仍符合条件和 $S$ 具体是什么无关。更具体地只需要考虑对于 $i$ 与 $i+1$，若在 $x$ 位顺序不对，则要求 $S$ 内存在某一位使得 $b_i$ 严格小于 $b_{i+1}$，这个可以直接对每一位做高维前缀和，然后轻松做到 $O(kn+k^22^k+k^2\log m)$，已经可以通过了。

事实上对每一位做高维前缀和是不必要的，因为你只需要维护一个本质上是只有 $0,1$ 的高维前缀或，这个东西压在一起用整数存就行了。复杂度 $O(kn+k2^k+k^2\log m)$。

---

## 作者：Dovish (赞：0)

首先，我们把 $b$ 拆开，下文中 $val_{i,j}$ 表示 $b_j$ 的第 $i$ 位。

我们观察一下发现，对于每一位的每一个交换，只有最后一步是有意义的，故本质不同的操作序列只有 $O(k!)$ 个。

并且我们可以观察到，这个操作本质上是一种基数排序，以操作的最后一位的第一关键字，倒数第二位为第二关键字……如此类推。

先考虑暴力做法 $O(k!kn\log n)$ 求出哪些本质不同的操作是合法的。

然后再反推多少个序列满足“每种操作的最后一次操作”的顺序是我们想要的。

我们可以直接设 $f_{i,j}$ 表示考虑到第 $i$ 位，有 $j$ 个位置已经被钦定了不能选。

转移就是：
$$
f_{i,j}\times (k-j)\to f_{i+1,j}\\
f_{i,j}\to f_{i+1,j+1}\\
$$
最终 $f_{m,k}$ 就是我们想要的答案。

显然可以矩阵快速幂优化。

注意，可能存在最终操作序列没有用到 $k$ 种元素的情况，所以对于每一个 $i\in[1,k]$ 都要求一遍上式。

这一步的复杂度是 $O(k^4\log m)$。

继续考虑怎么求出合法的操作序列。

对于排列相关的计数，容易想到状压 DP。

我们对于本质不同操作计数：

从后往前已经考虑了的数位的集合为 $x$，下一个希望插入的位置是 $i$，集合 $x$ 中每一个数位构成的连续段的开头位置的集合的并为 $S$。当且仅当 $S$ 和满足 $val_{i,j}\ge val_{i,j-1}$ 的 $j$ 的集合的并为全集时，$i$ 可以接到 $x$ 前边。

那么我们怎么快速求一个集合 $x$ 能否转移到任意一个 $i$ 呢？正着做是困难的，考虑求不能转移的情况：一个集合 $x$ 不能转移到 $i$，当且仅当存在一个 $j$ 使得上 $x$ 集合的每一个 $l$ 都满足 $val_{l,j}=val_{l,j-1}$ 且 $val_{i,j}<val_{i,j-1}$。

于是直接分讨每一个位置即可，用一个高维前缀和求出转移矩阵。

然后DP计数就是直接按照转移矩阵去做就是简单的了。

故总复杂度 $O(k^4\log m+(2^k+n)k^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc (u<<1)
#define rc (u<<1|1)
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define fst first
#define sed second
using namespace std;
const int N=2e5+10,M=1e6+10,inf=1e9,mod=998244353;
int qpow(int a,int b){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
int inv(int a){return qpow(a,mod-2);}
void Mul(int&a,int b){a=1ll*a*b%mod;}
void Add(int&a,int b){a+=b;if(a>=mod)a-=mod;}
void Dec(int&a,int b){a-=b;if(a<0)a+=mod;}
int mul(int a,int b){return 1ll*a*b%mod;}
int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
struct matrix
{
	int f[19][19];
	matrix(){memset(f,0,sizeof f);}
	void init(){memset(f,0,sizeof f);}
	int*operator[](int x){return f[x];}
	matrix operator*(const matrix&b)const
	{
		matrix c;
		rep(i,0,18)
		rep(k,0,18)
		{
			int val=f[i][k];
			rep(j,0,18)
			Add(c.f[i][j],mul(val,b.f[k][j]));
		}
		return c;
	}
};
bool MS;int used;
int n,m,k;
int a[N],b[N];
bitset<N>g[19],h[19];
int val[N][19];
int base[19];
int f[N][19];
bool tr[(1<<18)][19];//i状态转移到j的可行性 (0为可行!1为不行!)
int dp[(1<<18)];
void init()
{
	rep(w,1,k)
	{
		matrix res,trans;
		res[0][0]=1;
		trans[0][0]=w;
		rep(i,1,w)
		{
			trans[i-1][i]=1;
			trans[i][i]=w-i;
		}
		int b=m;
		while(b)
		{
			if(b&1)res=res*trans;
			trans=trans*trans;
			b>>=1;
		}
		base[w]=res[0][w];
	}
}
map<int,queue<int>>pos;
int ans;
bool MT;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	init();
	rep(i,1,n)
	{
		cin>>a[i];
		pos[a[i]].push(i);
	}
	rep(i,1,n)
	{
		cin>>b[i];
		int now=b[i];
		if(!pos[b[i]].size())
		return cout<<0,0;
		val[i][k]=pos[b[i]].front();
		pos[b[i]].pop();
		rep(j,0,k-1)
		{
			val[i][j]=now%10;
			now/=10;
		}
	}
	rep(j,0,k)
	rep(i,1,n)
	{
		g[j][i]=(val[i][j]>=val[i-1][j]);
		h[j][i]=(val[i][j]!=val[i-1][j]);//每一段的开头 
	}
	rep(j,0,k)
	rep(i,1,n)
	if(!g[j][i])
	{
		int base=0;
		rep(l,0,k-1)
		if(!h[l][i])base|=(1<<l);
		tr[base][j]=1;
	}
	rep(j,0,k)
	{
		per(i,(1<<k)-1,0)
		if(tr[i][j])
		{
			rep(l,0,k-1)
			if((1<<l)&i)
			tr[i^(1<<l)][j]=1;
		}
	}
	dp[0]=1;
	rep(i,0,(1<<k)-1)
	{
		rep(j,0,k-1)
		if((tr[i][j]^1)&&!(i&(1<<j)))
		dp[i|(1<<j)]+=dp[i];
		if(tr[i][k]^1)//可以转移到初始状态，即是合法状态
		ans+=dp[i]%mod*base[__builtin_popcount(i)]%mod;
	}
	cout<<ans%mod<<'\n';
	cerr<<"Memory:"<<(&MS-&MT)/1048576.0<<"MB Time:"<<clock()/1000.0<<"s\n";
}
```

---

## 作者：Leasier (赞：0)

直接考虑单调递增是很难办的，考虑**拆条件**：$B$ 单调递增等价于 $\forall i \in [1, m)$，最终 $b_i$ 在 $b_{i + 1}$ 前面。

考虑某个 $i$ 对操作序列的限制。设 $S_i = \{x \mid bit(b_i, x) < bit(b_{i + 1}, x)\}$，$T_i = \{x \mid bit(b_i, x) > bit(b_{i + 1}, x)\}$，则：

- $\mathcal{P}$：论最后一个出现的位置，$S_i$ 中的元素在 $T_i$ 后。
- $\mathcal{Q}$：若在 $a$ 中，初始 $b_i$ 在 $b_{i + 1}$ 后面，则需要**出现** $S_i$ 中的元素。

但直接对操作序列计数也很难办，因为上面有一个隐含条件是末尾允许有若干不在 $S_i, T_i$ 中的元素。

注意到我们只关心**最后一个出现的位置**，据此简化上面的限制条件：

- 设 $p_i$ 表示 $i$ 最后一个出现的位置。
- $\mathcal{P}$：$\displaystyle\max_{x \in S_i} p_x > \max_{x \in T_i} p_x$。
- $\mathcal{Q}$：$\exists x \in S_i$，$p_x$ 有效。

当我们已知 $p$，方案数则为 $S_2(m, |p|)$，其中 $|p|$ 表示出现过的元素个数。

接下来一个简单的想法是直接枚举 $p$ 并检验其是否满足以上条件，但时间复杂度为 $O(n \log n + n k!)$，显然不能通过。

考虑从大到小加入 $p_i$ 来 dp。设 $dp_S$ 表示 $p$ 中前 $|S|$ 大的元素集合为 $S$ 的方案数。

转移：设我们现在要将 $x$ 加入 $S$ 中，则条件为：

- $\mathcal{P}$：若 $S \cap S_i = \emptyset$，则 $x \not\in T_i$。
- 条件 $\mathcal{Q}$ 这里不需处理。

答案：$\displaystyle\sum_S [\forall \text{condition } \mathcal{Q}, S \cap S_i \neq \emptyset] dp_S S_2(n, |S|)$。

但转移与计算答案时直接暴力检验的时间复杂度为 $O(n \log n + nk 2^k)$，仍不能通过。

考虑对每个 $x$ 预处理出将其加入 $S$ 是否合法。具体地，若 $x \in T_i$，我们将 $U - S_i$ 的子集标记为非法。

又考虑对每个 $S$ 预处理出其作为答案是否合法。具体地，我们将每个 $\mathcal{Q}$ 对应的 $U - S_i$ 的子集标记为非法。

以上两步使用子集和算法（或称 FMT）即可。时间复杂度为 $O(n \log n + k^2 2^k)$。

代码：
```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

const int mod = 998244353;
int pos[200007], dp[262147];
ll fac[27], inv_fac[27], power[27], s2[27], a[200007], b[200007], bita[200007][27], bitb[200007][27];
bool f[262147], g[27][262147];
map<ll, vector<int> > mp;

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n, int m){
	fac[0] = 1;
	for (int i = 1; i <= m; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[m] = quick_pow(fac[m], mod - 2, mod);
	for (int i = m - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
	for (int i = 0; i <= m; i++){
		power[i] = quick_pow(i, n, mod);
	}
	for (int i = 0; i <= m; i++){
		for (int j = 0; j <= i; j++){
			if (j % 2 == 0){
				s2[i] = (s2[i] + inv_fac[j] * inv_fac[i - j] % mod * power[i - j] % mod) % mod;
			} else {
				s2[i] = ((s2[i] - inv_fac[j] * inv_fac[i - j] % mod * power[i - j] % mod) % mod + mod) % mod;
			}
		}
	}
}

inline void conv(bool f[], int n){
	int full = (1 << n) - 1;
	for (int i = full; i >= 1; i--){
		for (int j = 0; j < n; j++){
			if (i >> j & 1) f[i ^ (1 << j)] |= f[i];
		}
	}
}

int main(){
	int n, m, k, full;
	ll ans = 0;
	cin >> n >> m >> k;
	full = (1 << k) - 1;
	init(m, min(m, k));
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = n; i >= 1; i--){
		mp[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++){
		cin >> b[i];
		pos[i] = mp[b[i]].back();
		mp[b[i]].pop_back();
	}
	for (int i = 1; i <= n; i++){
		for (int j = 0; j < k; j++){
			bita[i][j] = a[i] % 10;
			bitb[i][j] = b[i] % 10;
			a[i] /= 10;
			b[i] /= 10;
		}
	}
	for (int i = 1; i < n; i++){
		int s = 0;
		for (int j = 0; j < k; j++){
			if (bitb[i][j] < bitb[i + 1][j]) s |= 1 << j;
		}
		s ^= full;
		if (pos[i] > pos[i + 1]) f[s] = true;
		for (int j = 0; j < k; j++){
			if (bitb[i][j] > bitb[i + 1][j]) g[j][s] = true;
		}
	}
	conv(f, k);
	for (int i = 0; i < k; i++){
		conv(g[i], k);
	}
	dp[0] = 1;
	for (int i = 1; i <= full; i++){
		for (int j = 0; j < k; j++){
			if (i >> j & 1){
				int x = i ^ (1 << j);
				if (!g[j][x]) dp[i] = (dp[i] + dp[x]) % mod;
			}
		}
	}
	for (int i = 0; i <= full; i++){
		if (!f[i]) ans = (ans + dp[i] * s2[__builtin_popcount(i)] % mod) % mod;
	}
	cout << ans;
	return 0;
}
```

---

