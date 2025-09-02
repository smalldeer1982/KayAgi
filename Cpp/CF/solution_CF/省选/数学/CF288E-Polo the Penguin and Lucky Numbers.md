# Polo the Penguin and Lucky Numbers

## 题目描述

Everybody knows that lucky numbers are positive integers that contain only lucky digits 4 and 7 in their decimal representation. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Polo the Penguin have two positive integers $ l $ and $ r $ $ (l&lt;r) $ , both of them are lucky numbers. Moreover, their lengths (that is, the number of digits in the decimal representation without the leading zeroes) are equal to each other.

Let's assume that $ n $ is the number of distinct lucky numbers, each of them cannot be greater than $ r $ or less than $ l $ , and $ a_{i} $ is the $ i $ -th (in increasing order) number of them. Find $ a_{1}·a_{2}+a_{2}·a_{3}+...+a_{n-1}·a_{n} $ . As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
4
7
```

### 输出

```
28
```

## 样例 #2

### 输入

```
474
777
```

### 输出

```
2316330
```

# 题解

## 作者：naoliaok_lovely (赞：13)

$2800$ 暴推式子题，做的时候有点自闭，但是做出来的那一刻真的很爽！

# 大体思路
关键词：**数位 DP，数学**。看数据范围，$l\le r\le10^{10^5}$，很显然是数位 DP 题。问题出在需要求解的式子上。要求解的内容是 $\sum\limits_{i=1}^{n-1}a_ia_{i+1}$，这个式子看起来很陌生，但也不是完全不可做。由于数位 DP 的一大步骤就是**递推**，而从递推的角度看，这个式子还是可以入手的。考虑直接计算！

# 预处理
设 $f_i$ 表示 $i$ 位只有 $4,7$ 构成的数，对应的 $\sum\limits_{j=1}^{n-1}a_ja_{j+1}$ 的值。显然，初始化为 $f_0=0$。然后暴力拆解，大思路是单独拎出首位，然后就可以进行递推了。
$$
\begin{aligned}
f_i&=\sum a_ja_{j+1}\\
&=\left(\sum (t+b_j)(t+b_{j+1})\right)+477..7\times744..4\quad(t\in\{4\times10^{i-1},7\times10^{i-1}\},b_j=a_j-t)\\
&=\left(\sum b_jb_{j+1}+t(b_j+b_{j+1})+t^2\right)+477..7\times744..4\\
&=2f_{i-1}+(t_1+t_2)\left(\sum b_j+b_{j+1}\right)+(t_1^2+t_2^2)(2^{i-1}-1)+477..7\times744..4\\
&\quad(t_1=4\times10^{i-1},t_2=7\times10^{i-1})
\end{aligned}
$$
为了接下来计算方便，我们令：$g_i=\sum\limits_{j=1}^{n-1}a_j+a_{j+1},
num_i=11..1(i\text{ 个 }1)$，那么上式可以继续变形：
$$
f_i=2f_{i-1}+(t_1+t_2)g_{i-1}+(t_1^2+t_2^2)(2^{i-1}-1)+(4\times10^{i-1}+7num_{i-1})(7\times10^{i-1}+4num_{i-1})
$$

至此，我们结束了 $f_i$ 的线性递推！

接下来，我们将重点移到 $g_i$ 的递推上，思路不变，过程如下：
$$
\begin{aligned}
g_i&=\sum a_j+a_{j+1}\\
&=\left(\sum 2t+b_j+b_{j+1}\right)+477..7+744..4\quad(t\text{ 的意义同上})\\
&=2g_{i-1}+(t_1+t_2)(2^i-1)+11num_{i-1}
\end{aligned}
$$

纯数学推导，请读者理解上面的过程，因为接下来可能还会用到。  
到这里，本题已经完成了一大半。

# 数位 DP
由于此题的特殊性，在写数位 DP 时，作者并不是把 $l\sim r$ 差分成了 $1\sim n$，而是差分成了 $t\sim n$。（其中，$t$ 表示位数与 $l,r$ 相同的最小整数，注意，题目保证了 $l,r$ 的位数相同）在 DP 过程中，我主要记录了 $2$ 个变量：$t$ 表示当前已经选定的数，$la$ 表示满足条件且小于当前数字的最大值。然后就是数位 DP 的模板了，代码的有一部分发现是与 $f$ 数组的推导是一样的，复制过去即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int N = 1e5 + 10, mod = 1e9 + 7;
char l[N], r[N];
int n;

LL pow2[N], pow10[N], num1[N];
LL f[N], g[N];
void init()
{
	pow10[0] = pow2[0] = 1;
	for(int i = 1; i <= n; i++)
		pow2[i] = pow2[i - 1] * 2 % mod, pow10[i] = pow10[i - 1] * 10 % mod, num1[i] = (num1[i - 1] * 10 + 1) % mod;
	
	for(int i = 1; i <= n; i++)
	{
		LL t1 = 4 * pow10[i - 1] % mod, t2 = 7 * pow10[i - 1] % mod;
		f[i] = (2 * f[i - 1] + (t1 + t2) * g[i - 1] % mod + (t1 * t1 + t2 * t2) % mod * (pow2[i - 1] - 1 + mod) % mod + (t1 + 7 * num1[i - 1] % mod) * (t2 + 4 * num1[i - 1] % mod) % mod) % mod;
		g[i] = (2 * g[i - 1] + (t1 + t2) * (pow2[i] - 1) + 11 * num1[i - 1]) % mod;
	}
}

int dp(char c[])
{
	LL ans = 0, t = 0, la = 0;
	for(int i = 1; i <= n; i++)
	{
		int a = c[i] - '0';
		if(a < 4) break;
		if(7 <= a)
		{
			LL res = (t + 4 * pow10[n - i]) % mod, cnt = n - i;
			ans = (ans + f[cnt] + res * g[cnt] + res * res % mod * (pow2[cnt] - 1 + mod) + la * (res + 4 * num1[cnt] % mod)) % mod;
			la = (res + 7 * num1[cnt]) % mod;
		}
		if(7 <= a) t = (t + 7 * pow10[n - i]) % mod;
		else t = (t + 4 * pow10[n - i]) % mod;
		
		if(i == n) ans = (ans + la * t) % mod;
	}
	
	return ans;
}

int main()
{
	scanf("%s%s", l + 1, r + 1);
	n = strlen(l + 1);
	init();
	
	cout << (dp(r) - dp(l) + mod) % mod << endl;
	return 0;
}
```

---

## 作者：chenxia25 (赞：2)

居然能独立过 2800，震撼，震撼（

---

**[Portal](https://www.luogu.com.cn/problem/CF288E)**

考虑使用类似数位 DP 的最后一步统计答案的方法。u1s1 有些人认为这个统计答案的方法才是数位 DP 的精髓，我不知道，我认为 DP 应该是 DP。

先将问题转化为前缀和。然后我们先算出当前 $n$ 位的最大的 $\leq r$ 的 lucky number。

根据数位 DP 的统计答案方法，我们先将 $n-1$ 位及以下对答案的贡献先累上去，这个显然是可以预处理的（注意各个位数之间是有衔接部分的，即 $x-1$ 个 $7$ 和 $x$ 个 $4$ 的乘积，这个需要计算一下，包括下面所有的衔接部分也是，具体如何计算这个显然可以预处理 $i$ 个 $4/7$ 的值常数算）。然后就考虑计算 $n$ 位的贡献。

我们一位一位地看，每次考虑前缀与当前前缀相等，并且当前位小于当前位的所有 lucky number 的贡献。那么显然它们构成的集合大小为 $2$ 的整次幂，其实就是规模小一点的所有 lucky number 前面都戴个前缀帽子。这个规模小一点的贡献我们是已经预处理出来了，于是我们想办法套上去。设帽子为 $head$，那么 $(head+x)(head+y)$ 可以用乘法分配律展开，有四项，一项是预处理出来的东西，两项是 $head$ 乘以 lucky number 们的和（这个也可以预处理），一项是 $head^2$ 乘以一个多少（这个太好算了）。

接下来考虑实现。

- 如何预处理：比较难的两个是 $i$ 位 lucky number 总贡献和 $i$ 位 lucky number 的和。注意到 $i$ 位 lucky number 有 $2^i$ 个，其中前 $2^{i-1}$ 是 $i-1$ 位戴 $4$ 帽子，后 $2^{i-1}$ 是戴 $7$ 帽子。我们可以利用这个来递推。也就很好推了，分配律展开即可，很长的柿子，贡献和需要用到和。然后其他的也就预处理一下 $2$ 和 $10$ 的幂，多少个 $4/7$。
- 如何算出 $\leq r$ 的最大 $n$ 位 lucky number。我当时写的时候脑子坏掉了，写了个从后往前的 DP，$dp_{i,0/1}$ 表示后缀 $i$ 第 $i$ 位为 $4/7$ 是否可行，最后路径还原。其实先判一下 $r$ 是否每位都 $\geq4$，若否则无，若是则显然每位的取值情况都是独立的，随便 xjb 贪即可。

综上，这题使用了数位 DP 的统计答案方法，但并没有 DP。

复杂度线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
const int N=100000;
int two[N+1],ten[N+1],four[N+1],seven[N+1],prod[N+1],sum[N+1],Prod[N+1];
void init(){
	two[0]=ten[0]=1;
	for(int i=1;i<=N;i++)two[i]=2*two[i-1]%mod,ten[i]=10*ten[i-1]%mod;
	for(int i=1;i<=N;i++)four[i]=(10*four[i-1]+4)%mod,seven[i]=(10*seven[i-1]+7)%mod;
	prod[1]=Prod[1]=28,sum[1]=11;
	for(int i=2;i<=N;i++)
		prod[i]=(prod[i-1]+4*ten[i-1]%mod*(2*sum[i-1]-four[i-1]-seven[i-1])%mod+4*ten[i-1]%mod*4*ten[i-1]%mod*(two[i-1]-1)+
		         prod[i-1]+7*ten[i-1]%mod*(2*sum[i-1]-four[i-1]-seven[i-1])%mod+7*ten[i-1]%mod*7*ten[i-1]%mod*(two[i-1]-1)+
		         (4*ten[i-1]+seven[i-1])%mod*(7*ten[i-1]+four[i-1])%mod)%mod,
		sum[i]=(2*sum[i-1]+11*ten[i-1]%mod*two[i-1]%mod)%mod,
		Prod[i]=(Prod[i-1]+prod[i]+seven[i-1]*four[i]%mod)%mod;
}
int na,nb;
char a[N+1],b[N+1];
int lar[N+1];
bool dp[N+1][2],pa[N+1][2];
int sol(int n,char s[]){
	memset(pa,-1,sizeof(pa));memset(dp,0,sizeof(dp));
	if(s[n]>='4')dp[n][0]=true;
	if(s[n]>='7')dp[n][1]=true;
	for(int i=n-1;i;i--){
		if(s[i]>='4'){
			if(dp[i+1][1])dp[i][0]=true,pa[i][0]=1;
			else if(dp[i+1][0])dp[i][0]=true,pa[i][0]=0;
		}
		if(s[i]>='7'){
			if(dp[i+1][1])dp[i][1]=true,pa[i][1]=1;
			else if(dp[i+1][0])dp[i][1]=true,pa[i][1]=0;
		}
	}
	int now=dp[1][1]?1:dp[1][0]?0:-1;
	lar[1]=now;
	for(int i=1;~now&&i<n;i++){
		now=pa[i][now];
		lar[i+1]=now;
	}
	int ans=Prod[n-1];
	if(!~now)return ans;
//	for(int i=1;i<=n;i++)cout<<lar[i];puts(" hsc 啊可爱哦爱");
	now=0;int las=0;
	if(n>1)las=seven[n-1];
	for(int i=1;i<=n;i++){
		int head=(10*now+4)%mod*ten[n-i]%mod;
		if(lar[i]==1)(ans+=las*(head+four[n-i])%mod+
		                   prod[n-i]+head*(2*sum[n-i]-four[n-i]-seven[n-i])%mod+head*head%mod*(two[n-i]-1)%mod)%=mod,
					 las=(head+seven[n-i])%mod;
		now=(10*now+(lar[i]==0?4:7))%mod;
	}
	(ans+=las*now)%=mod;
	return ans;
}
signed main(){
	init();
//	return cin>>a+1,na=strlen(a+1),cout<<sol(na,a)<<"\n",0;
	cin>>a+1>>b+1;
	na=strlen(a+1),nb=strlen(b+1);
	cout<<((sol(nb,b)-sol(na,a))%mod+mod)%mod<<"\n";
	return 0;
}
```

---

然后 tzc 还发了个 comment 题解，欢迎去观膜，反正我是 D 了他。

---

## 作者：Inui_Sana (赞：1)

虚高 *2800，放模拟赛 T1 人均切了。

这是 zlt 说的，不是我说的，我还是觉得没那么虚高的。

首先显然是数位 dp。

一个关键点就是怎么计算 $f_i\times f_{i+1}$。会发现可以将为 $4$ 的位置看作 $0$，否则为 $1$，则二进制下 $f_{i+1}=f_i+1$。此时问题就变成了进位所带来的贡献。

考虑一个数进位的条件及发生的变化。进位时，一个最大后缀 $7$ 连续段会变成 $4$，然后它前面接着的一个 $4$ 会变成 $7$，**再前面的数全部不变**。于是我们可以在数位 dp 的过程中找到那个 $4$，然后后面的 $7$ 都是确定的，直接预处理计数。

接下来，只用考虑在 $f_i,f_{i+1}$ 前面同时加上一个数的转移了。设 $f_i=a,f_{i+1}=b$，前面加上 $x=4/7\times10^k$。则原本 $a\times b$ 的贡献会变成 $(x+a)\times(x+b)=x^2+x\times(a+b)+a\times b$。所以可以在数位 dp 时记录选出 $f_i,f_{i+1}$ 的方案数，所有 $f_i,f_{i+1}$ 的方案的 $f_i+f_{i+1}$ 的和，所有 $f_i,f_{i+1}$ 的方案的 $f_i\times f_{i+1}$ 的和，上述第三种情况可以根据上面列出的式子转移，其他两种情况也是好推的。

于是再套一些数位 dp 基本操作即可。~~你不会数位 dp 我也讲不懂啊~~可能需要感性理解一下。

code：

```cpp
int n,m,b[13],c[13],f[N],g[N],pw[N],a[N],dp[N][3][2];
char s[N],t[N];bool pd[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
int dfs(int u,int p,int lim){
	if(u==n+1)return 0;
	if(~dp[u][p][lim])return dp[u][p][lim];
	int mx=lim?c[a[u]]:2,ret=0;
	rep(i,1,mx){
		int lm=lim&&i==mx;
		if(i==1&&!lm){
			if(p==0)ret=Mod(ret,1);
			if(p==1)ret=Mod(ret,Mod(Mod(1ll*b[1]*pw[n-u]%mod,g[n-u]),Mod(1ll*b[2]*pw[n-u]%mod,f[n-u])));
			if(p==2)ret=Mod(ret,(1ll*Mod(1ll*b[1]*pw[n-u]%mod,g[n-u])*Mod(1ll*b[2]*pw[n-u]%mod,f[n-u])%mod));
		}
		if(p==0)ret=Mod(ret,dfs(u+1,0,lm));
		if(p==1)ret=Mod(ret,Mod(dfs(u+1,1,lm),2ll*b[i]*pw[n-u]%mod*dfs(u+1,0,lm)%mod));
		if(p==2)ret=Mod(ret,Mod(dfs(u+1,2,lm),Mod(1ll*b[i]*pw[n-u]%mod*dfs(u+1,1,lm)%mod,1ll*b[i]*pw[n-u]%mod*b[i]%mod*pw[n-u]%mod*dfs(u+1,0,lm)%mod)));
	}
	return dp[u][p][lim]=ret;
}
int calc(char *s){
	mems(dp,-1);
	rep(i,1,n)a[i]=s[i]-'0';
	pd[n+1]=1;
	drep(i,n,1)pd[i]=pd[i+1]&(a[i]==b[2]);
	return dfs(1,2,1);
}
void Yorushika(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1);
	b[1]=4,b[2]=7;
	f[0]=g[0]=0,pw[0]=1;
	rep(i,1,n)f[i]=(10ll*f[i-1]+b[1])%mod,g[i]=(10ll*g[i-1]+b[2])%mod,pw[i]=10ll*pw[i-1]%mod;
	c[b[1]]=1,c[b[2]]=2;
	printf("%d\n",Mod(calc(t),mod-calc(s)));
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：EuphoricStar (赞：1)

虚高 *2800，放模拟赛 T1 人均切了。

首先我们发现这玩意有可减性，用 $[1, r]$ 的答案减去 $[1, l]$ 即可。所以接下来我们只讨论前缀的情况。

考虑数位 dp。为了计算题目的那玩意我们考虑把每个状态的 dp 值用一个三元组 $(a_1, a_n, \sum\limits_{i = 1}^{n - 1} a_i a_{i + 1})$ 表示。那么这样是可以合并的，$\sum\limits_{i = 1}^{n - 1} a_i a_{i + 1}$ 变成两边的 $\sum\limits_{i = 1}^{n - 1} a_i a_{i + 1}$ 之和再加上左边的 $a_n$ 乘上右边的 $a_1$ 即可。

但是我们发现我们还要进行让全部 $a_i$ 加上 $x = t \times 10^k$ 的操作。考虑 $\sum\limits_{i = 1}^{n - 1} (x + a_i) (x + a_{i + 1}) = (n - 1)x^2 + x \sum\limits_{i = 1}^{n - 1} (a_i + a_{i + 1}) + \sum\limits_{i = 1}^{n - 1} a_i a_{i + 1}$。所以我们多维护 $\sum\limits_{i = 1}^{n - 1} a_i + a_{i + 1}$ 和 $n$ 即可转移。

时间复杂度 $O(\log_{10} r)$。

[code](https://codeforces.com/contest/288/submission/243067781)

---

## 作者：tzc_wk (赞：1)

[题目传送门](https://codeforces.ml/contest/288/problem/E)

[似乎我的解法和官方题解不太一样](https://codeforces.ml/blog/entry/7241#comment-709625)

纪念自己独立做出来的一道难度 2800 的题。

我们记 $ans(x)$ 为 $[444...44,x]$ 的答案，显然答案为 $ans(r)-ans(l)$

其次我们考虑 $a_i$ 与 $a_{i+1}$ 之间有什么联系。

不难发现从 $a_i$ 变到 $a_{i+1}$，也就是把 $a_i$ 末尾一系列 $7$ 改为 $4$，再把从右往左数第一个 $4$ 改为 $7$。

这样我们就可以枚举末尾 $7$ 的个数，假设为 $cnt$。则 

$a_i=xxx...xx4777...77,a_{i+1}=xxx...xx7444...44$

如果把前面 $xxx...xx$ 记作 $X$，那么 $a_i=X \times 10^{cnt}+4777...77,a_{i+1}=X \times 10^{cnt}+7444...44$

把 $a_ia_{i+1}$ 暴力展开，即可得到一个关于 $X$ 的二次三项式 $AX^2+BX+C$，其中 $A,B,C$ 是只与 $cnt$ 有关的常数，它们具体是什么自己慢慢拆即可，这里就不再赘述了。。

接下来我们就要计算 $X^2$ 的和，$X$ 的和以及 $X$ 的个数，显然可以数位 $dp$ 预处理。

$dp[i][0/1]$ 表示考虑到第 $i$ 位，前 $i$ 位是否达到上界的答案。

其中 $dp[i][j]$ 中存三个值：平方和、和、以及个数。
转移可以从 $dp[i-1][0/1]$ 中转移过来。再根据 $(10x+4)^2=100x^2+80x+16$，$(10x+7)^2=100x^2+140x+49$ 化简。

```cpp
/*
Contest: - 
Problem: Codeforces 288E 
Author: tzc_wk
Time: 2020.10.12
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define pb			push_back
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define y1			y1010101010101
#define y0			y0101010101010
typedef pair<int,int> pii;
typedef long long ll;
const ll MOD=1e9+7;
char s[100005];int n;
struct data{
	ll sqr,cnt,sum;
	data(ll _sqr=0,ll _sum=0,ll _cnt=0){
		sqr=_sqr;sum=_sum;cnt=_cnt;
	}
} dp[100005][2];
ll pw[200005],seven[100005],four[100005];
inline data upd4(data p){
	return data(
	(p.sqr*100ll+p.sum*80ll+p.cnt*16ll)%MOD,
	(p.sum*10ll+p.cnt*4ll)%MOD,(p.cnt));
}
inline data upd7(data p){
	return data(
	(p.sqr*100ll+p.sum*140ll+p.cnt*49ll)%MOD,
	(p.sum*10ll+p.cnt*7ll)%MOD,(p.cnt));
}
inline void add(data &x,data y){
	x.sqr+=y.sqr;if(x.sqr>=MOD) x.sqr-=MOD;
	x.sum+=y.sum;if(x.sum>=MOD) x.sum-=MOD;
	x.cnt+=y.cnt;if(x.cnt>=MOD) x.cnt-=MOD;
}
inline ll get(data x,ll k);
inline ll calc(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=0;i<=n;i++) dp[i][0]=dp[i][1]=data(0,0,0);
	dp[0][1]=data(0,0,1);
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i][1]=data(0,0,0);
		if(s[i]=='4'){
			add(dp[i][0],upd4(dp[i-1][0]));
			add(dp[i][0],upd7(dp[i-1][0]));
			add(dp[i][1],upd4(dp[i-1][1]));
		}
		else{
			add(dp[i][0],upd4(dp[i-1][0]));
			add(dp[i][0],upd4(dp[i-1][1]));
			add(dp[i][0],upd7(dp[i-1][0]));
			add(dp[i][1],upd7(dp[i-1][1]));
		}
//		printf("%lld %lld %lld\n",dp[i][0].sqr,dp[i][0].sum,dp[i][0].cnt);
//		printf("%lld %lld %lld\n",dp[i][1].sqr,dp[i][1].sum,dp[i][1].cnt);
	}
	ll ans=0;
	for(int i=0;i<n;i++){
		if(s[i+1]=='4'){
			ans=(ans+get(dp[i][0],n-i-1))%MOD;
		} else{
			ans=(ans+get(dp[i][0],n-i-1))%MOD;
			ans=(ans+get(dp[i][1],n-i-1))%MOD;
		}
	}
//	printf("%lld\n",ans);
	return ans;
}
int main(){
	pw[0]=1;for(int i=1;i<=200002;i++) pw[i]=pw[i-1]*10%MOD;
	for(int i=1;i<=100000;i++) seven[i]=(seven[i-1]*10+7)%MOD;
	for(int i=1;i<=100000;i++) four[i]=(four[i-1]*10+4)%MOD;
	ll L=calc(),R=calc();
	printf("%lld\n",(R-L+MOD)%MOD);
	return 0;
}
inline ll get(data x,ll k){
//	printf("%d %d %d\n",x.sqr,x.sum,x.cnt);
	return (seven[k]*four[k]%MOD*x.cnt%MOD+seven[k]*pw[k+1]%MOD*x.sum%MOD+
	seven[k]*7%MOD*pw[k]%MOD*x.cnt%MOD+four[k]*pw[k+1]%MOD*x.sum%MOD+
	four[k]*4%MOD*pw[k]%MOD*x.cnt%MOD+pw[(k<<1)+2]*x.sqr%MOD+
	110*pw[k<<1]%MOD*x.sum%MOD+28*pw[k<<1]%MOD*x.cnt%MOD)%MOD;
}
```

---

## 作者：lzqy_ (赞：0)

考虑直接拆贡献。

设两个相邻的数 $x,y$，它们对答案的贡献为 $xy$。这是不好计算的，考虑将其写成 $x(x+(y-x))=x^2+x(y-x)$。前一部分是套路的，数位 DP 的时候统计 $\sum x^0,\sum x^1,\sum x^2$，即可，主要分析后一部分。

观察 $(y-x)$ 的特征。因为数字只由 $4,7$ 组成，所以加一的过程就是将末尾连续的 $7$ 换成 $4$，末尾第一个 $4$ 换成 $7$。考虑枚举末尾的 $4$，具体地，DP 时每加入一个 $4$，就将剩余部分全部加上 $7$ 的情况当做 $x$ 累加 $x(x-y)$ 即可。

注意特判 $R$ 全为 $7$（不存 $4$），以及减去 $R(nxt_R-R)$。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=100010;
const int mod=1e9+7;
il int fpow(int n,int m,int x=1){
	for(;m;m>>=1,n=1ll*n*n%mod)
		if(m&1) x=1ll*x*n%mod;
	return x;
}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
il void de(int &x,int y){if((x-=y)<0)x+=mod;}
char cL[maxn],cR[maxn];
int L[maxn],R[maxn],n;
int f1[maxn][2][2],f2[maxn][2][2],g[maxn][2][2];
int s1[maxn],s2[maxn],pow10[maxn],ok[maxn];
int ans;
//s1[i]:3*10^i-3*10^{i-1}-3*10^{i-2}-.....
//s2[i]:77777777..777(i)
//f1:x f2:x^2
void init(int n){	
	s1[0]=3,pow10[0]=1;
	for(int i=1,w=3,p=0;i<=n;i++){
		ad(p,w),w=10ll*w%mod;
		s1[i]=(w-p+mod)%mod;
		s2[i]=(10ll*s2[i-1]+7)%mod;
		pow10[i]=10ll*pow10[i-1]%mod;
	}ok[n+1]=1;
	for(int i=n;i;i--)
		ok[i]=ok[i+1]&(R[i]==7);
}
int main(){
	scanf("%s%s",cL+1,cR+1);
	n=strlen(cL+1);
	for(int i=1;i<=n;i++)
		L[i]=cL[i]-'0',R[i]=cR[i]-'0';
	g[0][1][1]=1,init(n);
	if(ok[1]) ans=(ans+1ll*s1[n]*s2[n])%mod;
	for(int i=0,tmp;i<n;i++)
		for(int c1=0,d1;c1<2;c1++)
			for(int c2=0,d2;c2<2;c2++){
				//s+4
				if(!g[i][c1][c2]) continue;
				if(!(c1&&L[i+1]==7)){
					d1=(c1&(L[i+1]==4)),d2=(c2&(R[i+1]==4));
					g[i+1][d1][d2]=(g[i+1][d1][d2]+g[i][c1][c2])%mod;
					f1[i+1][d1][d2]=(f1[i+1][d1][d2]+10ll*f1[i][c1][c2]+4ll*g[i][c1][c2])%mod;
					f2[i+1][d1][d2]=(f2[i+1][d1][d2]+100ll*f2[i][c1][c2]
									+80ll*f1[i][c1][c2]+16ll*g[i][c1][c2])%mod;
					//////
					if(!d2||ok[i+2]){
						int tmp=(10ll*f1[i][c1][c2]+4ll*g[i][c1][c2])%mod;
						tmp=(1ll*tmp*pow10[n-i-1]+1ll*g[i][c1][c2]*s2[n-i-1])%mod;
						ans=(ans+1ll*s1[n-i-1]*tmp)%mod;
					}
				} 
				//s+7
				if(!(c2&&R[i+1]==4)){
					d1=(c1&(L[i+1]==7)),d2=(c2&(R[i+1]==7));
					g[i+1][d1][d2]=(g[i+1][d1][d2]+g[i][c1][c2])%mod;
					f1[i+1][d1][d2]=(f1[i+1][d1][d2]+10ll*f1[i][c1][c2]+7ll*g[i][c1][c2])%mod;
					f2[i+1][d1][d2]=(f2[i+1][d1][d2]+100ll*f2[i][c1][c2]
									+140ll*f1[i][c1][c2]+49ll*g[i][c1][c2])%mod;
				}
			} 
	for(int c1=0;c1<2;c1++)
		for(int c2=0;c2<2;c2++)
			ad(ans,f2[n][c1][c2]);
	int tot=0,w=0;
	for(int i=1;i<=n;i++) 
		w=(10ll*w+R[i])%mod;
	for(int i=n;i;i--)
		if(R[i]==4) break;
		else tot++;
	ans=(ans-1ll*w*w-1ll*w*s1[tot])%mod;
	ans=(ans+mod)%mod,printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：Judgelight (赞：0)

来一发记搜的题解。

首先一个很显然的就是这题是数位 DP（l,r 的范围很明显），所以我们从数位 DP 的角度思考。

按照套路我们有一个 $f_{i,1/0}$ 表示前 $i$ 位，有无高位限制的信息，此题我们还是从这方面出发，但是问题就是求和的式子 $\sum a_ia_{i+1}$ 无法轻松做。

还是按照套路把高位取出来，设 $k$ 为当前的位数，这里让 $t=\lfloor\frac{a_i}{10^{k-1}}\rfloor$（直接考虑没有限制的，有限制的是一样的）：
$$\sum a_{i}a_{i+1}=\sum (t+a'_i)(t+a'_{i+1})=\sum t^2 +t(a'_i+a'_{i+1})+a'_ia'_{i+1}$$

所以就维护 **个数、和、应该输出的答案** 这三个东西。

具体细节可以自己写，写了这个挺让人费力的，但是对代码力应该来说挺有帮助。

屎山代码：

```cpp
#include<bits/stdc++.h>
#define N 100009
#define int long long
using namespace std;
const int mod=1e9+7;
char l[N],r[N];
int n,pw[N],pp[N],s[N];
void init(int n){
	pw[1]=pp[1]=1;
	for(int i=2;i<=n;i++){
		pw[i]=pw[i-1]*10%mod;
		pp[i]=(pp[i-1]+pw[i])%mod;
	}
}
struct Val{
	int s0,s1,s2;
}f[N][2];
Val dfs(int now,int limit,char num[]){
	if(now>n){
		return {1,0,0};
	}
	if(f[now][limit].s0!=-1||f[now][limit].s1!=-1||f[now][limit].s2!=-1){
		return f[now][limit];
	}
	Val ans;
	ans.s0=ans.s1=ans.s2=0;
	if(limit){
		if(num[now]=='4'){
			int t=4*pw[n-now+1]%mod;
			ans.s0+=dfs(now+1,1,num).s0;
			ans.s1+=dfs(now+1,1,num).s1+t*ans.s0%mod;
			ans.s1%=mod;
			ans.s2+=t*t%mod*(dfs(now+1,1,num).s0-1)%mod+t*(dfs(now+1,1,num).s1*2-pp[n-now]*4%mod-s[now+1])%mod+dfs(now+1,1,num).s2;
			ans.s2%=mod;
		}
		else{
			ans.s0+=dfs(now+1,0,num).s0+dfs(now+1,1,num).s0;
			ans.s0%=mod;
			int t1=4*pw[n-now+1]%mod,t2=7*pw[n-now+1]%mod;
			ans.s1+=dfs(now+1,0,num).s1+dfs(now+1,1,num).s1+dfs(now+1,0,num).s0*t1%mod+dfs(now+1,1,num).s0*t2%mod;
			ans.s1%=mod;
			ans.s2+=t1*t1%mod*(dfs(now+1,0,num).s0-1)%mod+t1*(dfs(now+1,0,num).s1*2-pp[n-now]*11%mod)%mod+dfs(now+1,0,num).s2+  t2*t2%mod*(dfs(now+1,1,num).s0-1)%mod+t2*(dfs(now+1,1,num).s1*2-pp[n-now]*4%mod-s[now+1])%mod+dfs(now+1,1,num).s2+(t1+pp[n-now]*7%mod)%mod*(t2+pp[n-now]*4%mod)%mod;
			ans.s2%=mod;
		}
	}
	else{
		ans.s0+=dfs(now+1,0,num).s0+dfs(now+1,0,num).s0;
		ans.s0%=mod;
		int t1=4*pw[n-now+1]%mod,t2=7*pw[n-now+1]%mod;
		ans.s1+=dfs(now+1,0,num).s1+dfs(now+1,0,num).s1+dfs(now+1,0,num).s0*t1%mod+dfs(now+1,0,num).s0*t2%mod;
		ans.s1%=mod;
		ans.s2+=t1*t1%mod*(dfs(now+1,0,num).s0-1)%mod+t1*(dfs(now+1,0,num).s1*2-pp[n-now]*11%mod)%mod+dfs(now+1,0,num).s2+  t2*t2%mod*(dfs(now+1,0,num).s0-1)%mod+t2*(dfs(now+1,0,num).s1*2-pp[n-now]*11%mod)%mod+dfs(now+1,0,num).s2+(t1+pp[n-now]*7%mod)%mod*(t2+pp[n-now]*4%mod)%mod;
		ans.s2%=mod;
	}
	//cout<<now<<" "<<limit<<" "<<ans.s0<<" "<<ans.s1<<" "<<ans.s2<<endl;
	return f[now][limit]=ans;
}
int calc(char num[]){
	memset(f,-1,sizeof(f));
	for(int i=n,j=1;i>=1;i--,j=j*10%mod){
		s[i]=(s[i+1]+(int)(num[i]-'0')*j%mod)%mod;
	}
	return dfs(1,1,num).s2;
}
signed main(){
	init(100000);
	scanf("%s",l+1);
	scanf("%s",r+1);
	n=strlen(l+1);
	printf("%lld",((calc(r)-calc(l))%mod+mod)%mod);
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：0)

卡了两天，调出来了……

------------

这题明显一眼**数位DP**。但是，同一般数位DP不同的是，这里的DP要在**边界数**（即除了首位其它位都是 $7$ 的数）处格外小心——因为，其它数假设我们在前面加上一个数（例如 $4$），应用乘法分配律，我们会发现：

$$(\overline{4x})\times(\overline{4y})=(4\times10^i)^2+4\times10^i(x+y)+xy$$

其中上划线表示将两数拼接。

但是，独独在边界数处，上式会失效（因为首位进了一位）。

我前几个思路设计的DP状态均包含了边界数，但是我最终发现包含边界数的状态非常难以转移，所以就有了下文的DP状态：

$num_{i,j}$ 表示长度为 $i$，首位为 $j$ 的数的数量（**不含边界数**）；

$sum_{i,j}$ 表示长度为 $i$，首位为 $j$ 的数的和（**包含边界数**）；

$ans_{i,j}$ 表示长度为 $i$，首位为 $j$ 的数的答案（**不含边界数**）；

下面考虑转移——

$$num_{i,j}=num_{i-1,4}+num_{i-1,7}+1$$

因为在前面填上一个数后，原本的边界数 $4777\dots$ 便不再是边界数了，故要加一。同时我们可以发现必有 $num_{i,4}=num_{i,7}$，但是为了区别我们还是把它们分开。

$$sum_{i,j}=\overline{j000\dots}\times(num_{i,j}+1)+sum_{i-1,4}+sum_{i-1,7}$$

这里的 $+1$ 是因为 $num$ 不包含边界，但 $sum$ 包含边界。

下面就是重头戏了。

我们考虑到上式

$$(\overline{4x})\times(\overline{4y})=(4\times10^i)^2+4\times10^i(x+y)+xy$$

于是求和便得到

$$ans_{i,j}=(\overline{j000\dots})^2\times num_{i.j}+\overline{j000\dots}\times\Big(2(sum_{i-1,4}+sum_{i-1,7})-\overline{777\dots}-\overline{444\dots}\Big)+(ans_{i-1,4}+ans_{i-1,7}+\overline{4777\dots}\times\overline{7444\dots})$$

其中加上或减去的一些都是边界数。

在预处理出三个数组之后，就可以类似地DP出 $l$ 和 $r$ 处的前缀和，并相减得到答案。具体过程和此类似，不再赘述。详情可以见代码。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int inv10=700000005;
int sum[100100][2],num[100100][2],ans[100100][2],n,res;
//sum[i][j]:the sum of numbers whose length is i and begin with number j.
//num[i][j]:the amount of so [except the boundary value,which is x7777...]
//ans[i][j]:the answer of so [except the boundary value,which is (x7777...)*(y4444...)]
char s[100100];
int func(){
	int _74=7,_47=4,_10=10,_4=4;
	for(int i=1;i<n;i++)_74=(10ll*_74+4)%mod,_47=(10ll*_47+7)%mod,_10=10ll*_10%mod,_4=(10ll*_4+4)%mod;
	int pref=0,ret=0;
	for(int i=0;i<n;i++){
		if(s[i]=='7'){
			int now=1ll*pref*_10%mod;
			int tmp=(2ll*sum[n-i-1][0]+(mod-_4)+(mod-_47))%mod;
			(ret+=(0ll+ans[n-i-1][0]+(1ll*now*now%mod)*num[n-i-1][0]%mod+1ll*now*tmp%mod+1ll*(now+_47)*(now+_74)%mod)%mod)%=mod;
		}
		pref=(10ll*pref+s[i]-'0')%mod;
		_74=1ll*(_74+mod-4)*inv10%mod,_47=1ll*(_47+mod-7)*inv10%mod,_10=1ll*_10*inv10%mod,_4=1ll*(_4+mod-4)*inv10%mod;
	}
	return ret;
}
int main(){
	scanf("%s",s),n=strlen(s);
    sum[0][0]=4,sum[0][1]=7;
    int _74=7,_47=4,_10=10,_7=7,_4=4;//74444...;47777...;1000...;7777...;4444....
    for(int i=1;i<n;i++){
    	int __4=4ll*_10%mod,__7=7ll*_10%mod;//4000...;7000...;
    	int tmp=(2ll*(sum[i-1][0]+sum[i-1][1])+(mod-_7)+(mod-_4))%mod;//the sum of the previous stage,except the two boundary values
        num[i][0]=(num[i-1][0]+num[i-1][1]+1)%mod;//+1 because after adding a number in the beginning, one previous boundary value is no longer hold.
        num[i][1]=(num[i-1][0]+num[i-1][1]+1)%mod;//num[i][0] always equals to num[i][1]; however we keep them both so as to distinguish them.
        ans[i][0]=(0ll+(1ll*_74*_47%mod+ans[i-1][0]+ans[i-1][1])%mod+(1ll*__4*__4%mod)*num[i][0]%mod+1ll*__4*tmp%mod)%mod;
        ans[i][1]=(0ll+(1ll*_74*_47%mod+ans[i-1][0]+ans[i-1][1])%mod+(1ll*__7*__7%mod)*num[i][1]%mod+1ll*__7*tmp%mod)%mod;
//consider using the equation (k+x)(k+y)=k^2+k(x+y)+xy,and you'll find why the transmission is like this.[remember to consider the no-longer boundary]
        sum[i][0]=(1ll*__4*(num[i][0]+1)%mod+sum[i-1][0]+sum[i-1][1])%mod;//still there's +1.
        sum[i][1]=(1ll*__7*(num[i][1]+1)%mod+sum[i-1][0]+sum[i-1][1])%mod;
        _74=(10ll*_74+4)%mod,_47=(10ll*_47+7)%mod,_7=(10ll*_7+7)%mod,_4=(10ll*_4+4)%mod,_10=10ll*_10%mod;
	}
	res=(mod-func())%mod;
	scanf("%s",s);
	(res+=func())%=mod;
	printf("%d\n",res);
	return 0;
} 
```


---

