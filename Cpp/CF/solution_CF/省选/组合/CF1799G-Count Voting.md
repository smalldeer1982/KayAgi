# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5```

### 输出

```
10```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4```

### 输出

```
5```

# 题解

## 作者：dead_X (赞：20)

## 前言
会不会开数据范围啊？
## 题解
记 $s_i$ 为第 $i$ 个阵营的人数。

考虑容斥有 $k$ 张票投自己阵营了，其中第 $i$ 个人有 $d_i$ 张票是从自己阵营投的，$c_i-d_i$ 张票放任自流，我们发现这样的方案数如下：

$$
\left(\prod_{i}\binom{s_i}{d_{j_1},d_{j_2},\cdots,d_{j_{s_i}}}\right)
\cdot\binom{n-\sum d_i}{c_1-d_1,c_2-d_2,\cdots,c_n-d_n}
$$

列出阶乘的式子可以发现，对于每个阵营只需要枚举 $\sum d_j$ 后求出 $\prod\frac{1}{d_j!(c_j-d_j)!}$，最后将各个阵营的 $\sum d_j$ 相加得到 $n-\sum d_i$。

最后将奇数项乘上 $-1$ 相加就是答案。

暴力卷积 $O(n^2)$，分治 FFT $O(n\log^2 n)$。
## 代码
```cpp
// Problem: G. Count Voting
// Contest: Codeforces Round #854 by cybercats (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1799/problem/G
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
vector<int> v[203];
int c[203],t[203],s[203];
int fac[203],ifac[203];
int f[203],deg=0;
int tf[203];
signed main()
{
	int n=read();
	fac[0]=ifac[0]=f[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2);
	for(int i=1; i<=n; ++i) c[i]=read();
	for(int i=1; i<=n; ++i)
		t[i]=read(),v[t[i]].push_back(c[i]),++s[t[i]];
	for(int i=1; i<=n; ++i)
	{
		tf[0]=1;
		int td=0;
		for(int z:v[i])	
		{
			for(int j=td+1; j<=td+z; ++j) tf[j]=0;
			for(int k=td; k>=0; --k)
			{
				int val=tf[k];tf[k]=0;
				for(int l=0; l<=z; ++l)
					tf[k+l]=(tf[k+l]+val
					*ifac[l]%p*ifac[z-l])%p;
			}
			td+=z;
		}
		td=min(td,s[i]);
		for(int j=0; j<=td; ++j)
			tf[j]=tf[j]*fac[s[i]]%p*ifac[s[i]-j]%p;
		for(int j=deg; j>=0; --j)
		{
			int val=f[j];f[j]=0;
			for(int k=0; k<=td; ++k)
				f[j+k]=(f[j+k]+val*tf[k])%p;
		}
		deg+=td;
	}
	int ans=0;
	for(int i=0; i<=deg; ++i)
		if(i&1) ans=(ans+p-f[i]*fac[n-i]%p)%p;
		else ans=(ans+f[i]*fac[n-i])%p; 
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Reunite (赞：12)

## 一
---

首先，发现这个要求是交错的，不好直接 DP，考虑容斥。我们有两种容斥的方向：

- 把每一个恰好要 $c_i$ 个容斥为至少要 $c_i$ 个，进行 DP。

- 把不能给自己组投票容斥，变为钦定 $i$ 个人一定给自己组投，剩下任意。

这里我选择的是第二种容斥方法，但我觉得第一种也是可做的。

考虑一组一组地进行 DP，我们设 $f_{i,j}$ 为我们考虑到了第 $i$ 组，前 $i$ 组钦定了 $j$ 个人必须给自己组投票的方案数，$len_i$ 为第 $i$ 组的人数。那么 $f$ 的转移应为：

$$f_{i,j}=\sum_{k=0}^{\min(j,len_i)}f_{i-1,j-k}\cdot g_{i,k}$$

上式的意义即为我们枚举第 $i$ 组投给自己的人数，做一个背包。关键变为求出第 $i$ 组钦定 $k$ 个人的方案数 $g_{i,k}$。下面默认以任一组为例。

考虑如下情况：如果我们知道，第 $i$ 个人的 $c_i$ 张票中，有 $a_i$ 张票是自己组的人投的，有 $\sum a_i=k$。假如到了 $i$，还剩 $j$ 个人，那我们选择组内给这个人投的方案数为 $\binom{j}{a_i}$，总共剩下没有钦定的 $len-k$ 个人，要分给所有 $c_i-a_i$ 里面，这部分是可重集排列，总的贡献为 $\frac{(n-\sum k)!}{\prod(c_i-a_i)!}$，但我们要 DP，不能直接得到后面的贡献，发现分子不变，考虑把分母拆到每一种方案里。

这样 $g$ 的转移就呼之欲出了（注意因为每一组不干扰，这里 $g$ 的意义改为对于某一组，$g_{i,j}$ 为考虑到第 $i$ 个人，分了 $j$ 张给自己组的票的方案数）：

$$g_{i,j}=\sum_{k=0}^{\min(j,c_i)} g_{i-1,j-k}\frac{1}{(c_i-k)!}\binom{len-j+k}{k}$$

最后整理一下，我们对于每一组，先做一遍对 $g$ 的 DP，然后转移 $f$。

然后经典容斥原理：
$$ans=\sum_{i=0}^n f_{m,i}(-1)^i (n-i)!$$

## 二
---

总时间复杂度是 $n^2$ 的，不会多项式科技卷积。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mod 998244353
using namespace std;

int n,m;
int c[205];
int t[205];
int b[205];
int len[200];
int slen[205];
int a[205][205];
ll f[205][205];
ll g[205][205];
ll inv[205];
ll fac[205];
ll infac[205];

inline ll C(int a,int b){return fac[a]*infac[b]%mod*infac[a-b]%mod;}

inline void init(int id){
	g[0][0]=1;
	for(int i=1;i<=len[id];i++){
		for(int j=0;j<=len[id];j++){
			g[i][j]=0;
			for(int k=0;k<=j&&k<=a[id][i];k++)
				(g[i][j]+=g[i-1][j-k]*infac[a[id][i]-k]%mod*C(len[id]-j+k,k))%=mod;
		}
	}
	return ;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]),b[i]=t[i];
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		t[i]=lower_bound(b+1,b+1+m,t[i])-b;
		len[t[i]]++;
		slen[t[i]]+=c[i];
		a[t[i]][len[t[i]]]=c[i];
	}
	fac[0]=fac[1]=infac[0]=infac[1]=inv[1]=1;
	for(int i=2;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		infac[i]=infac[i-1]*inv[i]%mod;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		init(i);
		for(int j=0;j<=n;j++){
			for(int k=0;k<=j&&k<=len[i];k++)
				(f[i][j]+=f[i-1][j-k]*g[len[i]][k]%mod)%=mod;
		}
	}
	ll ans=0;
	for(int i=0;i<=n;i++){
		ll x=f[m][i]*fac[n-i]%mod;
		if(i&1) x=mod-x;
		(ans+=x)%=mod;
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：Lgx_Q (赞：11)

标准容斥做法。

题目中各种性质夹交在一起，几乎无法计算，这时直接排上容斥大法。问题来了，我们应该容斥掉哪一个条件呢？

我思考了两个条件：

1. 每个人被投票次数满足 $c_i$。

2. 每组人不能投自己组。

思考片刻，发现如果要结合容斥第二个条件，可以用式子：

> 对于把 $a_1$ 个数字 $1$，$a_2$ 个数字 $2$，$\dots$，$a_n$ 个数字 $n$ 打乱，共有 $\frac{(\sum_{i=1}^na_i)!}{a_1!a_2!\dots a_n}$ 种方法。

在本题中，相当于 $n$ 个人投票，有 $\frac{n!}{c_1!c_2!\dots c_n!}$ 种方案。

所以考虑把不能投自己组容斥掉。

首先从 DP 的方向思考，发现预处理逆元后可以把分子和分母拆开贡献来算。具体来说，先 DP 出分母（计算时用逆元）的和，最后直接在每个 DP 值上乘分子即可。

对于投自己组的人，我们需要在每组内部对该组投自己组的人进行排列（用之前的式子），在每组内 DP 结束时乘上 投自己组 的人数（乘上分子）。对于剩下那些不钦定的人数，先算分母（用逆元算）的和，最和算总贡献时乘上分子。

设 $f_{i,j}$ 表示前 $i$ 组中共 $j$ 人投自己组，$dp_{i,j}$ 表示第 $i$ 组钦定 $j$ 个人投自己组。

$$f_{i,j}=\sum_{k=0}^{GroupSize(i)}f_{i-1,j-k}\times dp_{i,k}$$

每一组内部 DP 时，时间为 $O(L^3)$（$L$ 为组内人数）。但是第一重循环和外部枚举每一组的循环抵消为 $n$，所以总时间复杂度为 $O(n\sum L^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=210,mod=998244353;
ll n,c[maxn],t[maxn],dp[maxn][maxn],d[maxn][maxn][maxn],f[maxn][maxn],p[maxn],inv[maxn];
vector<ll>vec[maxn];
ll fac(ll n)
{
	return p[n];
}
ll C(ll n,ll m)
{
	return p[n]*inv[m]%mod*inv[n-m]%mod;
}
void subdp(ll c) //每组内部dp
{
	ll L=vec[c].size()-1;
	d[c][0][0]=1;
	for(ll i=1;i<=L;i++)
	{
		for(ll j=0;j<=L;j++)
		{
			for(ll k=0;k<=vec[c][i]&&k<=j;k++)
			{
				d[c][i][j]=(d[c][i][j]+d[c][i-1][j-k]*inv[k]%mod*inv[vec[c][i]-k])%mod;//其中一个逆元是对该组投自己组的贡献，在下面代码（函数结尾）会提到。另外一个逆元是不钦定投自己组的人，对最后计算的贡献
			}
		}
	}
	for(ll i=0;i<=L;i++)
	{
		dp[c][i]=d[c][L][i]*C(L,i)%mod*fac(i)%mod; //注意乘组合数
	}
}
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) vec[i].push_back(0);
	for(ll i=1;i<=n;i++) scanf("%lld",c+i);
	for(ll i=1;i<=n;i++) scanf("%lld",t+i), vec[t[i]].push_back(c[i]);
	p[0]=p[1]=inv[1]=inv[0]=1;
	for(ll i=2;i<=n;i++)
	{
		p[i]=p[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(ll i=2;i<=n;i++) inv[i]=inv[i]*inv[i-1]%mod;
	f[0][0]=1;
	for(ll i=1,s=0;i<=n;i++)
	{
		subdp(i);
		s+=vec[i].size()-1;
		for(ll j=0;j<=s;j++)
		{
			for(ll k=0;k<=j&&k<vec[i].size();k++)
			{
				f[i][j]=(f[i][j]+f[i-1][j-k]*dp[i][k])%mod;
			}
		}
	}
	ll ans=0;
	for(ll i=0;i<=n;i++)
	{
		ll tmp=f[n][i]*fac(n-i)%mod; //对不钦定的人的总贡献
		if(i&1) ans=(ans-tmp+mod)%mod;
		else ans=(ans+tmp)%mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：xixisuper (赞：3)

# CF1799G Count Voting 题解

氪鎄的容斥。

## 思路

### 简化版

先来考虑一个更简单的情况，假设所有的 $t_i=i$，那么答案应该是多少？

假设没有自己不能给自己投票这个限制，则最后的答案是一个不穿衣服的多重集排列数，计算公式为：

$$
\frac{n!}{\prod_{i=1}^nc_i!}
$$

现在考虑我们减去不合法的情况，我们记 $S_i$ 表示钦定 $i$ 个人把票投给自己的方案数，则根据容斥原理，答案就是：

$$
\frac{n!}{\prod_{i=1}^nc_i!}-\sum_{i=1}^n(-1)^{i+1}S_i
$$

现在我们考虑如何求 $S_i$，注意到有：

$$
\begin{aligned}
S_i&=\sum_{T\subseteq\{1,2,\cdots,n\},|T|=i}\frac{(n-i)!}{\prod_{j=1}^n(c_j-[j\in T])!}\\
&=(n-i)!\sum_{T\subseteq\{1,2,\cdots,n\},|T|=i}\left(\prod_{j=1}^n(c_j-[j\in T])!\right)^{-1}
\end{aligned}
$$

由于前面的 $(n-i)!$ 只和 $i$ 有关，所以我们把 $S_i$ 的定义变成后面那一坨，最后只需要乘上 $(n-i)!$ 即可。

现在我们希望能够求出后面那一坨东西，于是我们考虑 dp 设个状态。**设 $f_{i,j}$ 表示钦定第 $i$ 个人给自己投票，在 $[i,n]$ 中有 $j$ 个人给自己投票的多重集排列数的分母部分之和**，然后就有递推：

$$
f_{i,j}=c_j\sum_{k=i+1}^nf_{k,j-1}
$$

挺显然的吧，就是你把 $c_j-[j\in T]$ 这一步看成是把 $c_j$ 乘进去，然后就能得到这个递推，于是就有：

$$
S_i=\sum_{j=1}^nf_{j,i}
$$

对于 $f$ 的那个递推式，你可以把 $S$ 扩一维，令：

$$S_{i,j}=\sum_{k=1}^jf_{k,i}$$

于是：

$$
\begin{aligned}
f_{i,j}&=c_j\cdot\left(S_{j-1,n}-S_{j-1,i}\right)\\
S_{i,j}&=S_{i,j-1}+f_{j,i-1}
\end{aligned}
$$

初始化直接：

$$
f_{i,1}=c_i\cdot\left(\prod_{j=1}^nc_j!\right)^{-1}
$$

即可。

你得到了一个 $O(n^2)$ 的做法。

### 正解

考虑把那个简化版的部分做一个拓展。

注意到这个时候不合理的情况变成了某个位置 $i$ 选择了其所在组的某个人，所以我们把定义改一改。**设 $f_{i,j,k}$ 表示钦定第 $i$ 个组给自己投票，第 $i$ 个组中有 $j$ 个人给自己组投了票，在 $[i,n]$ 中有 $k$ 个人给自己的组投票的多重集排列数的分母部分之和**，然后就有递推：

$$
f_{i,j,k}=\left(\prod_{l=0}^{j-1}(c_i-l)\right)\cdot (S_{k-j,n}-S_{k-j,i})\cdot\binom{c_j}{j}
$$

$S$ 的定义不变，只不过求和时要枚举 $f$ 的两维。

初始化的时候直接：

$$
f_{i,j,j}=c_i\cdot\left(\prod_{k=1}^nc_k!\right)^{-1}\cdot\binom{c_i}{j}
$$

这是你可能会问，这不是 $O(n^3)$ 的递推吗？其实不是的，因为 $\sum c=n$，所以实际上 $f$ 的第二维在定死 $k$ 的情况下只会变化 $O(n)$ 次，所以实际上这是一个 $O(n^2)$ 的递推。

但是，最后的时候容斥出来的东西不是要减去的东西，由于你减去的东西实际上是**自己组给自己组投票的方案数**，是组给组的方案，而不是人给人的方案，所以最后还要乘上**组里人的多重集排列数**。我们记 $T_i$ 表示第 $i$ 个组的人数，则最后的答案为：

$$
\frac{n!}{\prod_{i=1}^nc_i!}-\left(\sum_{i=1}^n(-1)^{i+1}\cdot(n-i)!\cdot S_{i,n}\right)\cdot \frac{\prod_{i=1}^nT_i!}{\prod_{i=1}^nc_i!}
$$

时间复杂度 $O(n^2)$。

PS：实现的时候你发现 $f$ 的第 $3$ 维没啥用，直接滚掉就行。

## 代码

极丑无比，不建议阅读。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
const ll MOD=998244353;
const ll N=205;
ll ksm(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1) ret=ret*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return ret;
}
ll n,t[N],c[N],vt[N],ans;
ll jie[N],ycnt[N],top,C[N][N];
void init(){
	jie[0]=1;
	for(ll i=1;i<N;i++) jie[i]=jie[i-1]*i%MOD;
	for(ll i=0;i<N;i++){
		for(ll j=0;j<=i;j++){
			if(!j) C[i][j]=1;
			else C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
		}
	}
}
ll tsum[N],rcnt[N],pepo[N],f[N][N],sum[N][N];
void solve(){
	init();
	top=0;
	ll the_pep=0;
	for(ll i=1;i<=n;i++){
		if(!tsum[i]) continue;
		ycnt[++top]=tsum[i];
		rcnt[top]=pepo[i];
		the_pep+=pepo[i];
	}
	ans=jie[n];
	ll al_inv=1;
	for(ll i=1;i<=top;i++){
		al_inv=al_inv*ksm(jie[ycnt[i]],MOD-2)%MOD;
	}
	ans=ans*al_inv%MOD;
	ll minu=0;
	for(ll i=1;i<=the_pep;i++){
		for(ll j=1;j<=top;j++){
			if(i==1) f[j][1]=al_inv*ycnt[j]%MOD*C[rcnt[j]][1]%MOD;
			else{
				ll td=1;
				for(ll k=1;k<=min(i,min(rcnt[j],ycnt[j]));k++){
					ll bubao=(sum[i-k][top]-sum[i-k][j]+MOD)%MOD;
					if(i==k) bubao=al_inv;
					td=td*(ycnt[j]-k+1)%MOD;
					f[j][k]=bubao*td%MOD*C[rcnt[j]][k]%MOD;
				}
			}
			sum[i][j]=sum[i][j-1];
			for(ll k=1;k<=min(i,min(rcnt[j],ycnt[j]));k++){
				sum[i][j]+=f[j][k];
				if(sum[i][j]>=MOD) sum[i][j]-=MOD;
			}
		}
		if(i&1) minu=(minu+jie[n-i]*sum[i][top]%MOD)%MOD;
		else minu=(minu-jie[n-i]*sum[i][top]%MOD+MOD)%MOD;
	}
	ans=(ans-minu+MOD)%MOD;
	for(ll i=1;i<=n;i++) ans=ans*jie[tsum[i]]%MOD;
	for(ll i=1;i<=n;i++) ans=ans*ksm(jie[c[i]],MOD-2)%MOD;
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	bool B=1;
	for(ll i=1;i<=n;i++) cin>>c[i];
	for(ll i=1;i<=n;i++){
		cin>>t[i];
		pepo[t[i]]++;
		tsum[t[i]]+=c[i];
	}
	solve();
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑使用容斥原理。假设钦定了 $x$ 个人投了自己团队的方案数为 $g_x$，恰有 $x$ 个人投了自己团队的方案数是 $f_x$。

$$g_x=\sum_{i=x}^n C_i^x f_i$$

根据二项式反演，得到

$$f_x = \sum_{i=x}^n (-1)^{i-x} C_i^x g_i$$

我们要讨论 $f_0$，得到：

$$f_x = \sum_{i=0}^n (-1)^i g_i$$

然后利用一个多重组合数。如果我们要把 $n$ 个数分成大小为 $x_1,x_2,\dots,x_n$ 的集合的方案数为：

$$\frac{n!}{\prod_{i=1}^n x_i!}$$

对于这道题，我们考虑让每个人选定谁去投他。如果我们不加任何限制（就是钦定了 $0$ 个人），答案就是

$$\frac{n!}{\prod_{i=1}^n c_i!}$$

假设同一个联通块里面，每个人钦定了选 $p_i$ 个同组的。那么考虑这些同组的情况，方案数是：

$$\frac{|S_k|!}{(|S_k|-\sum_{u \in S_k} p_u)!\prod_{u \in S_k} p_u!}$$

然后考虑所有非同组的情况，得到：

$$\frac{(n-\sum_{i=1}^n p_i)!}{\prod_{i=1}^n (c_i - p_i)!}$$

然后可以在每一组内分别 DP，总体再 DP 一次即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200+5,MOD=998244353;
int n,t[MAXN],c[MAXN],frac[MAXN],inv[MAXN],C[MAXN][MAXN],g[2][MAXN],val[MAXN][MAXN],dp[MAXN][MAXN],f[MAXN];
vector<int> grp[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>c[i]; ffor(i,1,n) cin>>t[i];
	ffor(i,1,n) grp[t[i]].push_back(i);
	frac[0]=1; ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2);
	roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	C[0][0]=1;
	ffor(i,1,n) {
		C[i][0]=1;
		ffor(j,1,n) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	dp[0][0]=1;
	ffor(i,1,n) {
		memset(g,0,sizeof(g));
		int mx=grp[i].size();
		g[0][0]=1;
		ffor(j,0,mx-1) {
			int id=grp[i][j],st=(j+1)&1,lst=st^1;
			memset(g[st],0,sizeof(g[st]));
			ffor(x,0,n) ffor(y,0,c[id]) if(x+y<=n) g[st][x+y]=(g[st][x+y]+g[lst][x]*inv[y]%MOD*inv[c[id]-y]%MOD)%MOD;
		}
		ffor(x,0,n) val[i][x]=g[mx&1][x]*frac[x]%MOD*C[mx][x]%MOD;
		ffor(x,0,n) ffor(y,0,n-x) dp[i][x+y]=(dp[i][x+y]+val[i][x]*dp[i-1][y])%MOD;
	}
	ffor(i,0,n) f[i]=dp[n][i]*frac[n-i]%MOD;
	int ans=0;
	ffor(i,0,n) if(i&1) ans=(ans-f[i])%MOD; else ans=(ans+f[i])%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

同样来自 @Explodingkonjac 学长的讲题。但是我没认真听讲，所以自己想出来了。

原本的想法是设对于每一组分别设 $dp_{i,j}$ 为当前枚举到第 $i$ 个位置，已经钦定了 $j$ 个该组中的人投给自己组的方案数。转移就是枚举有多少人投给 $i$ 然后容斥。

但是可能是我没有处理好，总之这种转移似乎使每次切换组时就算上组内没被钦定的数的贡献。然而这样是错的因为后面组剩余的数量就是不确定的，有后效性了。

此时再仔细分析代码，发现复杂度不会超过 $\sum_i(\sum_j[t_j=i])^2\le n^2$。也就是说可以再加一维。

那么变成设 $dp_{i,j,k}$ 为当前枚举到第 $i$ 个位置，已经钦定了 $j$ 个人投给同组的人，已经钦定了 $k$ 个该组中的人投给自己组的方案数。转移是类似的，这样就可以最后再算没钦定的人的贡献了。时间复杂度 $O(n^3)$ 可以通过。

但是做完看题解发现原来有 $O(n^2)$ 做法，吐槽数据范围。大概做法就是把同组的一起算，再乘上组内排列贡献。

code（$O(n^3)$）：


code：

```cpp
int n,m,dp[N][N][N],c[N],fac[N],ifac[N];
struct node{int x,y;}a[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int binom(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void init(int n){
	fac[0]=1;
	rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	drep(i,n-1,0)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
il bool cmp(node x,node y){return x.y<y.y;}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i].x);
	rep(i,1,n){
		int x;scanf("%d",&x);
		c[x]++,a[i].y=x;
	}
	init(n);
	sort(a+1,a+n+1,cmp);
	dp[0][0][0]=1;
	rep(i,1,n){
		int s=c[a[i].y];
		rep(l,0,a[i].x){
			rep(j,l,n)rep(k,l,c[a[i].y]){
				if(l&1)dp[i][j][k]=Mod(dp[i][j][k],mod-1ll*dp[i-1][j-l][k-l]*binom(s-k+l,l)%mod*ifac[a[i].x-l]%mod);
				else dp[i][j][k]=Mod(dp[i][j][k],1ll*dp[i-1][j-l][k-l]*binom(s-k+l,l)%mod*ifac[a[i].x-l]%mod);
			}
		}
		if(a[i+1].y!=a[i].y){
			rep(j,0,n){
				rep(k,1,s)dp[i][j][0]=Mod(dp[i][j][0],dp[i][j][k]),dp[i][j][k]=0;
			}
		}
	}
	int ans=0;
	rep(i,0,n)ans=Mod(ans,1ll*dp[n][i][0]*fac[n-i]%mod);
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

