# Coprime Subsequences

## 题目描述

Let's call a non-empty sequence of positive integers $ a_{1},a_{2}...\ a_{k} $ coprime if the greatest common divisor of all elements of this sequence is equal to $ 1 $ .

Given an array $ a $ consisting of $ n $ positive integers, find the number of its coprime subsequences. Since the answer may be very large, print it modulo $ 10^{9}+7 $ .

Note that two subsequences are considered different if chosen indices are different. For example, in the array $ [1,1] $ there are $ 3 $ different subsequences: $ [1] $ , $ [1] $ and $ [1,1] $ .

## 说明/提示

In the first example coprime subsequences are:

1. $ 1 $
2. $ 1,2 $
3. $ 1,3 $
4. $ 1,2,3 $
5. $ 2,3 $

In the second example all subsequences are coprime.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
15
```

## 样例 #3

### 输入

```
7
1 3 5 15 3 105 35
```

### 输出

```
100
```

# 题解

## 作者：Lauzun (赞：13)

$($写题写累了，摸鱼来一篇题解$)$

小萌新对这个题只会最朴素的$DP($哭$)$

首先考虑使用容斥，使用序列总数——即 $2^n-1$，减去所有 $gcd>1$ 的子序列个数

倒序枚举因子 $i$，记录下来序列中 $i$ 的倍数总数 $sum$，然后用 $dp_i$ 记录下来，即 $(2^{sum} - 1)$ 种

但是还有一点，就是如果直接记录下 $(2^{sum} - 1)$ 可能会有重复，因为对于 $i$ 的倍数而言，它们构成的序列也有可能是以 $i$ 的倍数作为 $gcd$ 的，所以这里也算一个小容斥，需要枚举 $i$ 的倍数 $j$，然后从 $dp_i$ 中减去 $dp_j$，这样才能得到不会重复的结果

然后就是注意取模操作时如果碰到减法一定要先加 $mod$ 再取模，不然有爆负数的风险

代码$:$

```cpp
#include<stdio.h>
#define maxn 100005
#define mod 1000000007
using namespace std;
int n, x;//n为数字总数，x为序列中的数字 
long long dp[maxn], cnt[maxn], pow[maxn];
/*dp数组含义如上文， 
cnt数组类似桶记录序列中数字出现次数，
pow预处理2的次方 
*/ 
int main() {
	scanf("%d", &n);
	pow[0] = 1;//预处理2的次方 
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &x);
		cnt[x] ++;
		pow[i] = (long long)(pow[i - 1] * 2ll) % mod;
		//机智的小萌新选择边读入边预处理qwq 
	}
	for(int i = maxn - 1; i >= 1; i --) {
		long long sum = 0;//sum表示序列中i的倍数的个数 
		for(int j = i; j < maxn; j += i)
			sum = (sum + cnt[j]) % mod;
		dp[i] = pow[sum] - 1;
		for(int j = 2 * i; j < maxn; j += i)
			dp[i] = (dp[i] - dp[j] + mod) % mod;
			//这就是如上文提到的容斥 
	}
	printf("%lld\n", dp[1]);//按照dp数组的含义输出dp[1] 
}
```


---

## 作者：forever_nope (赞：2)

<https://www.luogu.com.cn/problem/CF803F>

与当前 No. 1 题解类似，使用容斥原理，不要莫反。

首先，我们知道，对于长度为 $n$ 的序列，他的子序列共有 $2^n-1$ 个。

不会这个的请不要看绿题，谢谢（）

然后我们考虑，这些子序列中，有哪些子序列的 $\gcd$ 不是 $1$ 的。

我们枚举一个 $k$，用 $f(k)$ 表示子序列 $\gcd$ 为 $k$ 的倍数的区间个数，

即定义式：$f(k)  = \sum_{S \in a}[k \mid \gcd(S)]$。

我们发现 $f(k)$ 可以非常简单的计算：

求出所有 $a$ 中，$k$ 的倍数的数的出现次数 $c_k$，$f(k)=2^{c_k}-1$。

然后考虑容斥。为什么要容斥？

显然 $k \mid \gcd(S)$ 显然会包括上其他的 $tk \mid \gcd(S)$（$t\ge2$），答案偏大。

那么我们设 $g(k)$ 表示子序列 $\gcd=k$ 的区间个数。

显然 $g(k)=f(k)-g(2k)-g(3k)-\dots-g(\lambda k)$。

白话：$\gcd$ 是 $k$ 的倍数的子序列个数，减去 $\gcd$ 为 $tk$（$t\ge2$）的子序列个数。

然后考虑实现，显然 $g(k)$ 要用到 $k$ 以后的元素，而 $f$ 与其他 $f$ 无关。

因此可以倒叙遍历 $k$。而 $a_i \le 10^5$，可以用桶实现。

有一个原理叫做一个序列的 $\gcd$ 一定 $\le$ 这个序列的任意一个数。

时间复杂度：$\mathcal{O}(n \log n)$（$n$ 与 $a_i$ 同阶）。

评测记录：<https://www.luogu.com.cn/record/144075059>。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;
constexpr ll MOD = 1e9 + 7;

int app[N];

ll fac[N], g[N];

inline ll mns(ll a, ll b) {
	return (a - b + MOD) % MOD;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int n, x; cin >> n;
	for (int i = 0; i < n; ++i) cin >> x, ++app[x];
	fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * 2 % MOD;
	for (int i = N - 1; i; --i) {
		int cnt = 0; for (int j = i; j < N; j += i) cnt += app[j];
		g[i] = fac[cnt] - 1;
		for (int j = i + i; j < N; j += i) g[i] = mns(g[i], g[j]);
	} cout << g[1] << endl;
	return 0;
}
```


---

## 作者：fanfansann (赞：2)

## CF803F Coprime Subsequences（2000，容斥原理）

**Problem**

给定一个 $n$ 个数的序列，问你有多少个子序列的 $\gcd=1$ 。

**Solution**

序列一共有 $n$ 个数，显然一共有 $2^n-1$ 个子序列（每个数选或不选减去空集）

考虑容斥。显然答案就是 $2^n-1$ 减去 $\gcd>1$ 的子序列个数，设所有含有大于 $1$ 的因子的序列中的个数为 $x$ ，显然 $\gcd>1$ 的子序列的个数为 $2^x-1$。显然只与点的权值有关，而 $a[i]\le 10^5$，考虑维护权值。设序列中的数的最大值为 $m$。

- 设 $cnt_i$ 表示权值为 $i$ 的序列中的数的个数，可以在输入的时候处理一下。

- 设 $sum_i$ 表示含有因子 $i$  的数的个数，显然 $\displaystyle sum_i=\sum\limits_{i|j}{cnt_j}$，即序列中 $i$ 的倍数的个数。我们可以通过枚举倍数在 $O(mlogm)$ 的复杂度下计算。

- 设 $f_i$ 表示含有因子 $i$  的子序列的个数，显然 $\displaystyle f_i=2^{sum_i}-1=2^{\sum\limits_{i|j}{cnt_j}}-1$，显然 $sum<m\le10^5$，我们可以 $O(m)$ 预处理一下 $2$ 的次幂。

对于 $\gcd>1$ 的子序列个数，根据奇加偶减的容斥原理，显然为：含有因子 $2$ 的子序列的个数（$f_2$） $+$ 含有因子 $3$ 的子序列的个数（$f_3$） $+$ 含有因子 $5$ 的子序列的个数（$f_5$） $+$ $\cdots$ $-$ 含有因子 $2,3$ 的子序列的个数（$f_6$） $-$  含有因子 $2,5$ 的子序列的个数（$f_{10}$） $-\cdots$ + 含有因子 $2,3,5$（$f_{30}$） 的子序列的个数 $+\cdots$

最终的答案为 $2^n-1$ 减去 $\gcd>1$ 的子序列个数，即变为奇减偶加的形式，然后我们可以发现前面 $f_x$ 的系数实际上就是 $\mu(x)$（莫比乌斯函数本身就是一个容斥的映射）。

即答案为 
$$
2^n-1+\sum_{i=2}^{m}\mu(i)\times f_i
$$

**Time**

$O(mlogm),m=\max\{a[i]\}$

**Code**

[https://paste.ubuntu.com/p/T8dcy6cGS2/](https://paste.ubuntu.com/p/T8dcy6cGS2/) 


---

## 作者：Purple_wzy (赞：2)

题面：https://www.luogu.com.cn/problem/CF803F

一句话题意：给你一个序列，问你有多少个子序列的gcd=1

题解：
我们设f(x)表示gcd为x的子序列数。显然，我们要求f(1)。

因为是求子序列数，所以我们可以不用管数字的顺序。

观察x>1的情况，此时gcd不为1，也就是说，这些满足条件的子序列里的所有数都是x的倍数。
设t[i]表示序列中i的倍数的出现次数，这个可以n$\sqrt{n}$求出。

但是这样f(x)还是不好求。

那什么好求呢？发现如果子序列里的数都是x的倍数，就比较好求。

设g(x)表示序列中只有x的倍数组成的合法子序列个数。这个可以直接O(1)求，

g(x)=$2^{t[x]}$-1。

再回过头来研究f和g的关系：发现:$g=f*1$

用一下莫比乌斯反演，就可以得出$f(n)$= $\sum_{n|d}$g(d)

这样，f(1)就很好求了。筛一下$\mu$函数就好了~

复杂度O(n$\sqrt{n}$)

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define re register ll
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline ll
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
const ll Mod=1e9+7;
ll n,m,ans,v[101000],twice[101000],a[101000],t[101000],prime[101000],tot,mu[101000];
int main(){
	read(n);
	F(i,1,n)read(a[i]);
	F(i,1,n){
		F(j,1,sqrt(a[i])){
			if(a[i]%j==0){
				t[j]++;
				if(j*j!=a[i])t[a[i]/j]++;
			}
		} 
	}
	tot=0;mu[1]=1;twice[0]=1;
	F(i,1,100000)twice[i]=twice[i-1]*2ll%Mod;
	F(i,2,100000){
		if(!v[i])prime[++tot]=i,mu[i]=-1;
		F(j,1,tot){
			if(i*prime[j]>100000)break;
			v[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
	}
	F(i,1,100000)ans=(ans+(ll)(twice[t[i]]-1)*mu[i]+Mod)%Mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Kelin (赞：2)

题意:给你一个序列，问你有多少个子序列的$gcd=1$

----
考虑到$m=max\{a_i\}$不是很大,我们可以这样做

$g_i$表示$i$的个数

$f_i$表示$i$的倍数的个数$\Rightarrow f_i=\sum_{i|j}g_j$

$s_i$表示$i|gcd$的子序列个数,显然$s_i=2^{f_i}-1$

$ans_i$表示$gcd=i$的子序列个数$\Rightarrow ans_i=\sum_{i|j}\mu(\frac ji)*s(j)=s_i-\sum_{i|j}ans_j$

这样我们就可以通过枚举倍数在$O(m\log m)$的时间里完成这道题了

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+5,P=1e9+7;
typedef int arr[N];
int n,m;arr f,Mi,ans;
inline int add(int a,int b){return a+=b,a>=P?a-P:a;}
inline int sub(int a,int b){return a-=b,a<0?a+P:a;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);int x;Mi[0]=1;
    fp(i,1,n)sd(x),cmax(m,x),++f[x],Mi[i]=add(Mi[i-1],Mi[i-1]);
    fp(i,1,m/2)for(int j=2*i;j<=m;j+=i)f[i]+=f[j];
    fd(i,m,1){
    	ans[i]=Mi[f[i]]-1;
    	for(int j=2*i;j<=m;j+=i)
    		ans[i]=sub(ans[i],ans[j]);
    }we(ans[1]);
return Ot(),0;
}
```

---

## 作者：UperFicial (赞：1)

莫比乌斯反演模板题了吧。

设 $f(x)$ 表示 gcd 为 $x$ 的方案数，$g(x)$ 表示 gcd 为 $x$ 倍数的方案数。

$g(x)$ 容易求，设 $c_x$ 表示 $x$ 的倍数出现次数，任意多个结合都可使 gcd 为 $x$ 的倍数，但不可不选，则 $g(x)=2^{c_x}-1$。

根据定义容易列出 $f,g$ 的关系：$g(d)=\sum_{d|n} f(n)$，我们希望求 $f$ 而 $g$ 又可求，所以莫比乌斯反演。

得到 $f(d)=\sum_{d|n}\mu(\frac{n}{d})g(n)$。

由于要求 $f(1)$，易知答案为 $f(1)=\sum_{d}\mu(d)\left(2^{c_d}-1\right)$。

线性筛出 $\mu$ 后直接枚举 $d$ 即可完成本题。

---

## 作者：_lbw_ (赞：1)

所求即为 $\sum\limits_{T\subseteq S,T\not = \varnothing}[\gcd(T)=1]$.

$$= \sum\limits_{T\subseteq S,T\not = \varnothing}\sum\limits_{x\in T,p|x} \mu(p)$$

$$= \sum\limits_{p=1}^{\max{S}}\mu(p)\sum\limits_{T\subseteq S,T\not = \varnothing}\sum\limits_{x\in T,p|x} 1$$

$$= \sum\limits_{p=1}^{\max{S}}\mu(p) \times( 2^{\sum\limits_{x\in S,p|x}1}-1)$$

于是设 $\max S=x$ 复杂度为 $\mathcal{O}(x\ln x+n)$.

[码](https://www.luogu.com.cn/paste/ufxqecrm)

---

## 作者：RainFestival (赞：1)

注意到 $1\le a_i\le 10^5$，**尝试枚举**每一个 $\gcd$，然后利用**容斥**。

设 $\max\limits_{i=1}^{n}a_i=m$，可以注意到答案为 $\sum\limits_{i=1}^{m}\mu(i)\times (2^{cnt_i}-1)$，其中 $cnt_i=\sum\limits_{k=1}^{n}[i|a_k]$。

先筛出莫比乌斯函数的值，然后再计算即可解决。

时间复杂度 $O(n+m \log m)$。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#define mod 1000000007
int n,m,cnt[100005],mu[100005],p[100005],ans;
int main()
{
	scanf("%d",&n);
	p[0]=1,p[1]=2;for (int i=2;i<=n;i++) p[i]=p[i-1]*2%mod;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		++cnt[x];
		m=std::max(x,m);
	}
	mu[1]=1;
	for (int i=1;i<=m;i++)
		for (int j=2;j<=m/i;j++)
		    mu[i*j]=mu[i*j]-mu[i];
	for (int i=1;i<=m;i++)
	{
		int s=0;
		for (int j=1;j<=m/i;j++) s=s+cnt[i*j];
		ans=((ans+mu[i]*(p[s]-1))%mod+mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

$\texttt{623ms/1008KB}$，在目前 $21$ 份 $\texttt{AC}$ 记录中排名第 $3$。

---

## 作者：封禁用户 (赞：0)

容斥，设 $f_i$ 为 $\gcd$ 为 $i$ 的倍数、非空子序列个数。则若 $a$ 中有 $t$ 个数是 $i$ 的倍数，则 $f_i=2^t-1$。设 $g_i$ 为 $\gcd$ 恰为 $i$ 的非空子序列个数。那么
$$g_i=f_i-\sum_{i|j,j>i}g_i$$

时间复杂度 $O(m\log m+n)$，$m=10^5$。
```
#include <bits/stdc++.h>
#define MOD 1000000007
#define REP(temp, init_val, end_val) for (int temp = init_val; temp <= end_val; ++temp)
#define REPR(temp, init_val, end_val) for (int temp = init_val; temp >= end_val; --temp)
using namespace std;
int read(){
    int f = 1, x = 0;
    char c = getchar();
    while (c < '0' || c > '9'){if(c == '-') f = -f; c = getchar();}
    while (c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
    return f * x; 
}
inline int modadd(int x, int y){
    return (x + y >= MOD ? x + y - MOD: x + y);
}
int poww(int a, int b){
    int res = 1;
    while (b > 0){
        if (b & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD, b >>= 1;
    }
    return res;
}
int n, a[100005], cnt[100005] = {0};
int cntb[100005] = {0};
const int m = 100000;
int ans[100005];
void init(){
    n = read();
    REP(i, 1, n) a[i] = read(), ++cnt[a[i]];
    REP(i, 1, m)
        for (int j = i; j <= m; j += i)
            cntb[i] += cnt[j];
}
void solve(){
    REPR(i, m, 1){
        ans[i] = modadd(poww(2, cntb[i]), MOD - 1);
        for (int j = i + i; j <= m; j += i)
            ans[i] = modadd(ans[i], MOD - ans[j]);
    }
    printf("%d\n", ans[1]);
}
int main(){
    init();
    solve();
    return 0;
}
```

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF803F).

let $S=\{a_1,\cdots,a_n\},v=\max\{a_1,\cdots,a_n\}$.

$$\begin{aligned}
\mathtt{Ans}&=\sum_{T\subseteq S}\sum_{x\in T}\sum_{p\mid x}\mu(p)\\
&=\sum_{p\le v}\mu(p)\sum_{T\in S}\sum_{x\in T}[p\mid x]
\end{aligned}$$

We can found the fact that $\displaystyle\sum_{T\in S}\sum_{x\mid T}[p\mid x]=2^{\sum_{x\in S}[p\mid x]}-1$.

so let $\displaystyle c_x=\sum_{i=1}^n[x\mid a_i]$, now $\displaystyle\mathtt{Ans}=\sum_{p\le v}\mu(p)(2^{c_p}-1)$.

get $\mu_i,2^i,c_i$ for $1\le i\le v$, we can solve the problem in $O(v\ln v)$.

```cpp
#include<stdio.h>
#include<vector>

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int n,v,a[N],mu[N],vis[N];
int pow2[N],cnt[N],tot[N];
long long res;
std::vector<int> pri;

void sieve(){
	mu[1] = 1;
	for(int i = 2;i < N;++i){
		if(!vis[i]) pri.push_back(i),mu[i] = -1;
		for(int j : pri){
			if(i * j >= N) break;
			vis[i * j] = 1;
			if(i % j) mu[i * j] = -mu[i];
			else break;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;++i)
		scanf("%d",a + i),++cnt[a[i]];
	sieve();
	pow2[0] = 1;
	for(int i = 1;i < N;++i)
		for(int j = i;j < N;j += i) tot[i] += cnt[j];
	for(int i = 1;i < N;++i)
		pow2[i] = 2LL * pow2[i - 1] % mod;
	for(int i = 1;i < N;++i){
		if(mu[i] == -1) mu[i] = mod - 1;
		if(mu[i]) (res += 1LL * mu[i] * (pow2[tot[i]] - 1) % mod) %= mod;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

