# Even String

## 题目描述

你需要构造一个由小写拉丁字母组成的字符串 $s$，满足以下条件：
- 对于任意两个满足 $s_{i} = s_{j}$ 的下标 $i$ 和 $j$，这两个下标之差的绝对值为偶数，即 $|i - j| \bmod 2 = 0$。

构造任意字符串太简单了，因此你会被给定一个包含 $26$ 个数字的数组 $c$ —— 表示字符串 $s$ 中每个字母必须出现的次数。也就是说，对于每个 $i \in [1, 26]$，拉丁字母表中的第 $i$ 个字母必须恰好出现 $c_i$ 次。

你的任务是计算满足所有这些条件的不同字符串 $s$ 的数量。由于答案可能非常大，请输出其对 $998\,244\,353$ 取模后的结果。

## 说明/提示

- 在第一个测试用例中，有 $4$ 个满足条件的字符串："abak"、"akab"、"baka" 和 "kaba"。


翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 3 0 0 0 0 0 0 0 0 0 0 0
1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 233527 233827```

### 输出

```
4
960
0
1
789493841```

# 题解

## 作者：chm_qwq (赞：8)

# CF2086D Even String
题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF2086D) and [Codeforces](https://codeforces.com/problemset/problem/2086/D)

## 题目大意

给出字符串内每个字母出现次数。

要求任意两个相同的字母之间的距离必须为偶数。

求满足要求的字符串的数量。

## 思路

要使得**任意两个相同的字母之间的距离为偶数**，意味着**相同的字母必须放在奇偶性相同的位置上**，即字母 $a$ 只能都放在偶数下标或奇数下标的位置上。

>反证法：
>如果奇偶性不同，那么选出位置奇偶性不同的两个相同的字母，这样它们的距离就是奇数了。

这启发我们对下标位置进行奇偶的分类讨论。

而字符串的最终总长度已经固定了记为 $S$，则下标为偶数的位置和下标为奇数的位置的数量也固定，分别记为 $S_0$ 和 $S_1$。

那么26个字母，每个字母只能是都放奇或都放偶，设 $X$ 为最终选择放在奇数位的字母的集合，则此时的不同的字符串数量为：

$$\prod_{i\in X} C(c_i,S_1-\sum_{j\in X \& j < i} c_j)\times\prod_{i\notin X} C(c_i,S_0-\sum_{j\notin X \& j < i} c_j)$$

即放完第一个字符后再放第二个，依此放入，每次产生不同的方案数用组合数计算。

接下来拆开这个式子，化简后可以得到：

$$\frac{S_1!}{\prod_{i\in X} c_i!}\times\frac{S_0!}{\prod_{i\notin X} c_i!}$$

即：

$$\frac{S_1!S_0!}{\prod_{i=1}^{26} c_i!}$$

注意到，这个式子与 $X$ 的具体情况无关，意味着无论怎么选，最终贡献的方案数是一个定值。

那么问题就转变为求共有多少种可能的 $X$ 的取法，即选一些数使其加和为某个值。

这就是一个经典的背包求方案数的问题了，转移式：

$$dp_{j} = \sum dp_{j-c_i}$$

如此，预处理阶乘，按上式计算每次的贡献，DP方案数，将两者相乘就是最终的答案了。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 30;
const int V = 26*5e5;

#define ll long long
const ll mod = 998244353;

int T;
int n;
ll c[N];
ll f[V+5],finv[V+5];
ll qpow (ll a,ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
void pre () {
	f[0] = finv[0] = 1;
	for (ll i = 1;i <= V;i++) 
		f[i] = f[i-1] * i % mod;
	finv[V] = qpow(f[V],mod-2);
	for (ll i = V-1;i >= 1;i--) 
		finv[i] = finv[i+1] * (i+1) % mod;
}
ll S,S1,S0,ans;
ll dp[V+5];
int main () {
	pre();
	scanf("%d",&T);
	while (T--) {
		S = 0;ans = 1;
		n = 26;
		for (int i = 1;i <= n;i++) {
			scanf("%lld",&c[i]);
			S += c[i];
		}
		for (int j = S;j >= 0;j--) dp[j] = 0;
		dp[0] = 1;
		S1 = S/2+(S&1),S0 = S/2;
		for (int i = 1;i <= 26;i++) {
			if (!c[i]) continue;
			for (int j = S;j >= 0;j--) 
				if (j + c[i] <= S) 
					dp[j+c[i]] = (dp[j+c[i]]+dp[j]) % mod;
		}
		ans = dp[S0] * f[S0] % mod * f[S1] % mod;
		for (int i = 1;i <= 26;i++) 
			ans = (ans * finv[c[i]]) % mod;
		printf("%lld\n",ans);
	}
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/wgy7mliy.png)

## End

第一次交题解，希望能过QwQ。

---

## 作者：zhangzhixing99 (赞：3)

如果您想拥有更优质的阅读体验，您可以尝试[隐藏评论区](https://www.luogu.me/paste/32rqh1k7)。
## 前情提要
~~我做这道题花费时间最长的部分居然是排队（In queue）。~~  
不就是个简单的~~01背包~~吗？看着大佬们写的题解的我一脸茫然。
## 题目摘要
- 构造一个由小写字母组成的字符串 $s$。
- 要求 $\forall\,i, j\,(i, j\,\isin\,|s|), |i - j|\,\equiv\,0\,(\bmod\,2)$，$\operatorname{if}\,s_i = s_j$。
- 固定每个小写字母的个数
## 前置知识
- [动态规划](https://blog.csdn.net/qq_43466788/article/details/109627650#_6)（只用看概念、定义和正确性证明即可）
## 正题开始
题目中的要求换一种说法就是相同种类的字母智能摆在奇偶性相同的位置。  
显然，我们可以将所有位置拉链式拆开。  
不妨设奇数位总数为 $L$，偶数位总数为 $R$。

于是我们发现，每种小写字母只可能全放奇数位或者偶数位。  
有种类数，有总量，有决策，联想到动态规划。

设 $f_{i, j}$ 表示轮到了 $\text{ASCII}$ 码为 ```i + 96``` 的小写字母进行决策，决策后奇数位填写了 $j$ 个字母。

第一种决策：放偶数位。
$$
[s_{i} - j \le R \operatorname{and} s_{i - 1} \ge j] \times f_{i - 1, j} \times \operatorname{C}^{c_i}_{R - (s_{i - 1} - j)}
$$
$$
(s_i = \sum_{k = 1}^{i} c_k)
$$

第二种决策：放奇数位。
$$
[j \ge c_i] \times f_{i - 1, j - c_i} \times \operatorname{C}^{L - (j - c_i)}_{c_i}
$$

求和即可。$\operatorname{C}$ 表示组合数。
## 实现方法
- 动态规划正常实现，不要压维。
- 不要忘记清空 $f$。
- 组合数 $\operatorname{C}^m_n = \frac{n!}{(n-m)! \times m!} = \frac{\frac{n!}{(n-m)!}}{m!}$，[逆元](https://blog.csdn.net/2401_87245677/article/details/145150316)（费马小定理求法）$+$ [快速幂](https://cloud.tencent.com/developer/article/2382608)预处理即可。
## 时间复杂度
- 预处理：$\Theta(s_n \times \log_2 s_n)$
- 求解：$\Theta(n \times s_n)$。
- 总时间复杂度：$\Theta(s_n)$。
- 其中 $n = 26$（英文小写字母个数）。
## 空间复杂度
- $\Theta(n \times s_n)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define EOL '\n'

#define __LOG true
#ifdef __LOG
#define PRINTF printf
#else
#define PRINTF //
#endif

#define __IOFILE true
#ifdef __IOFILE
#define FREOPEN freopen
#else
#define FREOPEN //
#endif

const int n = 26, mod = 998244353;

long long fact[500010], ifact[500010];
int g_c[30], g_s[30];
long long g_f[30][500010];

long long qpow(long long bas, long long t)
{
	long long ret = 1, mul = bas;
	while (t)
	{
		if (t & 1)
		{
			ret *= mul;
			ret %= mod;
		}
		mul *= mul;
		mul %= mod;
		t >>= 1;
	}
	return ret;
}

int comb(int n, int m)
{
	if (n < m)
	{
		return 0;
	}
	int ret = 1ll * fact[n] * ifact[n - m] % mod * ifact[m] % mod;
	return ret;
}

void solve()
{
	for (int i = 1; i <= n; ++i)
	{
		cin >> g_c[i];
		g_s[i] = g_s[i - 1] + g_c[i];
	}
	int L = (g_s[n] + 1) >> 1, R = g_s[n] >> 1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j <= g_s[n]; ++j)
		{
			g_f[i][j] = 0;
		}
	}
	g_f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (!g_c[i])
		{
			for (int j = 0; j <= min(g_s[i], L); ++j)
			{
				g_f[i][j] = g_f[i - 1][j];
			}
			continue;
		}
		for (int j = 0; j <= min(g_s[i], L); ++j)
		{
			if (g_s[i] - j <= R && g_s[i - 1] >= j)
			{
				g_f[i][j] += g_f[i - 1][j] * comb(R - (g_s[i - 1] - j), g_c[i]) % mod;
				g_f[i][j] %= mod;
			}
			if (j >= g_c[i])
			{
				g_f[i][j] += g_f[i - 1][j - g_c[i]] * comb(L - (j - g_c[i]), g_c[i]) % mod;
				g_f[i][j] %= mod;
			}
		}
	}
	cout << g_f[n][L] << EOL;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	fact[0] = ifact[0] = 1;
	for (int i = 1; i <= 5e5; ++i)
	{
		fact[i] = fact[i - 1] * i % mod;
		ifact[i] = qpow(fact[i], mod - 2);
	}
	int T;
	cin >> T;
	while (T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：wcy110614 (赞：1)

### D

感觉比较复杂的 DP，

首先把整个字符串分奇偶下标拆成两个字符串。

设 $f_{i,j}$ 为填完字母 $i$ 并且上面一行剩余 $j$ 个，然后讨论讨论转移就好了。

$$f_{i,j}\begin{cases}f_{i-1,j} & (c_i=0)\\C_{j+c_i}^{c_i}f_{i-1,j+c_i}+C_{n-j-\sum_{k=1}^{i-1}c_i}^{c_i}f_{i-1,j} & (\mathcal{c_i\not =0})\end{cases}$$

解释一下方程：因为 $C_n^m$ 就算是 $m=0$ 值也是 $1$，所以为了细节不算错就要直接当 $c_i=0$ 的时候直接把 $f_{i,j}:=f_{i-1,j}$。

之后考虑两种情况加起来：

1. 可以把这 $c_i$ 个字母全部放在上面一行，上面一行在放之前剩下 $j+c_i$ 个数，所以是在 $j+c_i$ 个位置里面选 $c_i$ 个位置放，也就有 $C_{j+c_i}^{c_i}f_{i-1,j+c_i}$ 种。
2.  放下面，下面一行原本只有 $n-j-\sum{_{k=1}^{i-1}c_i}$ 个位置，放 $c_i$ 个数，也就是 $C_{n-j-\sum_{k=1}^{i-1}c_i}^{c_i}f_{i-1,j}$ 了。
   
做到这里就已经可以处理出整个 $f$ 了，然后 $f[z][0]$ 就是答案。

```cpp
#include <bits/stdc++.h>
using ll=long long;
using namespace std;
const int N=5e5+10,Q=5e5+1;
const ll MOD=998244353;
ll f[30][N],fc[N],ifc[N];
int tt,n,m,c[30],tot;
ll qpow(ll a,ll b){
	ll res=1,base=a;
	while(b){
		if(b&1) (res*=base)%=MOD;
		(base*=base)%=MOD, b>>=1;
	}
	return res;
}
ll C(ll A,ll B){ if(!B)return 1;return fc[A]*ifc[B]%MOD*ifc[A-B]%MOD; }
inline void work(){
	n=m=tot=0;
	for(int i=1;i<=26;++i)cin>>c[i],n+=c[i];
	m=n>>1,n-=m,f[1][n-c[1]]=C(n,c[1]),f[1][n]=C(m,c[1]),tot+=c[1];
	for(int i=2;i<=26;++i){
		for(int j=0;j<=n;++j){
			if(!c[i]){
				f[i][j]=f[i-1][j];
				continue;
			}
			if(j+c[i]<=n)f[i][j]=f[i-1][j+c[i]]*C(j+c[i],c[i]);
			f[i][j]%=MOD;
			if(n+m-tot-j>=c[i])f[i][j]+=f[i-1][j]*C(n+m-tot-j,c[i]);
			f[i][j]%=MOD;
		}
		tot+=c[i];
	}
	cout<<f[26][0]<<"\n";
	for(int i=1;i<=26;++i)for(int j=0;j<=n;++j)f[i][j]=0;
	return void();
}
int main(){
	cin>>tt;
	fc[0]=1;
	for(int i=1;i<=Q;++i)fc[i]=i*fc[i-1]%MOD;
	ifc[Q]=qpow(fc[Q],MOD-2);
	for(int i=Q;i;--i)ifc[i-1]=ifc[i]*i%MOD;
	while(tt--)work();
	return 0;
}
```

---

## 作者：anotherobject (赞：0)

### 题意
给 $26$ 个字符的出现次数 $c$，对任意相同字符下标差都为偶数的字符串计数。$\sum c\le 5\times 10^5$。

### 题目解析
给定 $\sum c$ 的取值范围，考虑用关于 $\sum c$ 的算法解决。

分析题目中字符串的限制条件，发现下标差为偶数等于所有相同字符下表 $\bmod 2$ 必须相同。

只要把奇偶位的字符都得到，运用多重集排列公式 $\frac{n!}{\prod c_i!}$ 就可以得到组合方式。

所以考虑背包，多重集的贡献可以拆到每次 dp 转移。

具体实现的时候，我对 $n$ 的奇偶分开做，可能会方便一点。

---

## 作者：_iridescent (赞：0)

### 题意

要求你构造一个仅含有小写字母的字符串 $s$，需要满足：对于每对使得 $s_i = s_j$ 的 $i$ 和 $j$ ,有 $\left| i - j \right| \mod 2 = 0$。

给你 $T$ 组数据，每组数据中会给出在你要构造的 $s$ 中，$26$ 个字母的第 $i$ 个字母的出现次数 $c_i$，求满足条件的不同字符串 $s$ 的数量，并对 $998244353$ 取模。

### 思路

由于题目中说到相等的字母的下标差为偶数，可以推出不存在同一个字母同时存在在奇数位和偶数位上，所以我们可以考虑将原字符串按照下标的奇偶拆分成奇数串和偶数串来分开考虑。

我们知道，把 $n$ 个不同的元素放在 $n$ 个位置的方案数是 $n!$，而排列 $m$ 个相同元素的方案数是 $m!$。那么设奇偶数串的长度分别是 $len1$ 和 $len2$。很明显，我们可以先使用 $01$ 背包求出划分到 $len1$ 的方案数 $dp_{len1}$，再将其与 $n$ 个位置放 $n$ 个可能不同的元素的方案相乘就能得到答案了。 

放置 $len1$ 个可能相同的元素在 $len1$ 个位置上的方案数是：

$$\frac{len1!}{\Pi_{i \in [1,26] \cup i \mod 2 = 0 }c_i!}$$

总方案数则为：

$$dp_{len1} \cdot \frac{len1!}{\Pi_{i \in [1,26] \cup i \mod 2 = 1 }c_i!} \cdot \frac{len2!}{\Pi_{i \in [1,26] \cup i \mod 2 = 0 }c_i!} = dp_{len1} \cdot \frac{len1! \cdot len2!}{\Pi_{i=1}^{26}c_i!}$$

---

## 作者：AK_400 (赞：0)

注意到相同字符只能都在奇数位或都在偶数位，所以记 $dp_{i,j}$ 为考虑到第 $i$ 个字符，奇数位已经用了 $j$ 个，记出现的字符个数为 $s$，第 $i$ 个出现的字符的出现次数为 $c_i$，有

$$
dp_{i,j}=dp_{i-1,j}\times(^{\lfloor\frac{\sum_{k=1}^{s}c_k}2\rfloor-\sum_{k=1}^{i-1}c_k+j}_{c_i})+dp_{i-1,j-c_i}\times(^{\lceil\frac{\sum_{k=1}^{s}c_k}2\rceil-j+c_i}_{c_i})
$$

即放在奇数位和偶数位的情况。

答案为 $dp_{s,\lceil\frac{\sum_{k=1}^{26}c_k}2\rceil}$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,cc),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int c[27],sum[27];
int n;
#define odd (sum[n]+1>>1)
#define even (sum[n]>>1)
int dp[27][500005];
int fact[500005],inv[500005];
const int mod=998244353;
int qp(int x,int y){
    int res=1;
    while(y){
        if(y&1)res*=x,res%=mod;
        x*=x,x%=mod;
        y>>=1;
    }
    return res;
}
void init(){
    fact[0]=1;
    for(int i=1;i<=500000;i++)fact[i]=fact[i-1]*i%mod;
    inv[500000]=qp(fact[500000],mod-2);
    for(int i=499999;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int x,int y){
    return fact[x]*inv[y]%mod*inv[x-y]%mod;
}
vector<int>v;
void slv(){
    v.clear();
    v.push_back(0);
    for(int i=1;i<=26;i++){read(c[i]);if(c[i])v.push_back(c[i]);}
    n=v.size()-1;
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+v[i];
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=odd;j++){
            if(sum[i]-j>even)continue;
            if(sum[i]-j<0)continue;
            if(j-v[i]>=0){
                dp[i][j]+=dp[i-1][j-v[i]]*C(odd-j+v[i],v[i]);
                dp[i][j]%=mod;
            }
            if(sum[i]-j-v[i]>=0){
                dp[i][j]+=dp[i-1][j]*C(even-sum[i]+j+v[i],v[i]);
                dp[i][j]%=mod;
            }
        }
    }
    cout<<dp[n][odd]<<endl;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=odd;j++){
            dp[i][j]=0;
        }
    }
    return;
}
signed main(){
    init();
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

