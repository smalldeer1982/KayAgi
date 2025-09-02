# Make It One

## 题目描述

Shirley有一个数列$\{a_i\}_{i=1} ^n$，她可以选出这些数中的任意多个（不必连续——原文为“subset子集”），然后得到等于这些数最大公因数的分数。   
现在，她想要在得到1分的前提下，使选择的数尽可能少，那么，她应该选择多少个数呢？   
如果任意选择都不能得到1分，请输出-1.

## 说明/提示

$1\leq n\leq 300,000$；$1\leq a_i \leq 300,000$.

## 样例 #1

### 输入

```
3
10 6 15
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
2 4 6
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
30 60 21 42 70 15 30
```

### 输出

```
3
```

# 题解

## 作者：ywy_c_asm (赞：22)

首先我们应该注意到，$300000$内的数最多只有6个质因子，然后我们可以果断猜测答案上界是$6$……吗？

……其实，答案上界是$7$，因为这才是最极限的一种情况：

```cpp
x1=  3*5*7*11*13*17
x2=2 * 5*7*11*13*17
x3=2*3 * 7*11*13*17
x4=2*3*5 * 11*13*17
x5=2*3*5*7 *  13*17
x6=2*3*5*7*11 *  17
x7=2*3*5*7*11*13
```

这样的话每个数都有6个质因子，而它们的质因子集合互不相同，这个不可能再大了。

然后我们暂且抛开这个答案的上界，很自然的就会想一个暴力$dp[i][j]$为前$i$个数$gcd$为$j$的集合最少为多大，我们其实就是想求$dp[n][1]$。

实际上这题给出的是一个**集合**而非序列，对于很多这样的题我们并不能去从序列上考虑，而是应该从诸如**值域**之类的去考虑。

然而我们发现在值域上还是似乎没法$dp$出最小值，那么我们就考虑答案上界是7这个事实，枚举答案，判断是否存在一个$k$个数的集合使得$gcd$为1。

我们考虑统计$gcd=x$的方案数。这类问题有一个套路就是我们并不在实际的数上面算，而是考虑他们的所有约数，在约数上搞事情，最后再反演/容斥到实际的数上。

那么我们就不妨设$f[i]$为选$k$个数，$i$为它们的**公约数**的方案。这个容易，我们统计出有多少个数是$i$的倍数，设为$cnt[i]$，那么$f[i]=C_{cnt[i]}^k$。然后考虑求$g[i]$为选$k$个数然后$gcd=i$的方案数，考虑容斥，显然有$g[i]=f[i]-\sum_{j=2}^{ij<=n}g[ij]$。$O(n\log n)$。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 998244353
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll jc[300001], jcny[300001], f[300001];
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	inline ll cnm(int n, int m) {
	    if (n < m)
	        return (0);
	    ll cjr = jc[n];
	    cjr *= jcny[m];
	    cjr %= p;
	    cjr *= jcny[n - m];
	    return (cjr % p);
	}
	int cnt[300001], yuecnt[300001];
	void ywymain() {
	    int m = get(), n = 0;
	    for (register int i = 1; i <= m; i++) {
	        int x = get();
	        n = max(n, x);
	        cnt[x]++;
	    }
	    jc[0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = i; j <= n; j += i) yuecnt[i] += cnt[j];
	    }
	    for (register int i = 1; i <= m; i++) jc[i] = (jc[i - 1] * i) % p;
	    jcny[m] = mi(jc[m], p - 2);
	    for (register int i = m - 1; i >= 0; i--) jcny[i] = (jcny[i + 1] * (i + 1)) % p;
	    for (register int k = 1; k <= 7; k++) {
	        for (register int i = n; i >= 1; i--) {
	            f[i] = cnm(yuecnt[i], k);
	            for (register int j = i * 2; j <= n; j += i) f[i] = (f[i] + p - f[j]) % p;
	        }
	        if (f[1]) {
	            cout << k << endl;
	            return;
	        }
	    }
	    cout << -1 << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：nkwhale (赞：5)

注意：这篇题解是乱搞（能过），如果想看严格做法请转其他题解。

今天模拟赛考了这个，场上写了个乱搞做法，发现 CF 上也能过，就来写个题解。

考虑减短那个序列，先去重，然后考虑数列中如果有一个数是另一个的倍数那那个数肯定没用，把这种数也去掉。

显然答案很小，考虑暴力增加答案 ans 算出 ans 个数的 gcd 能是哪些，每次和上一个 ans 的答案合并即可。

为了在枚举到正确答案的时候不让算法跑满，就加了个 random shuffle。

具体实现可以看代码，很好懂。

```cpp
const int N=300300,M=300000;
int prt,pri[N],npr[N],a[N],b[N],c[N],ton[N];
inline int gcd(int x,int y){return y?gcd(y,x%y):x;}

inline void sieve(){
	for(re int i=2;i<=M;++i){
		if(!npr[i]) pri[++prt]=i;
		for(re int j=1,k=pri[j];j<=prt&&i*k<=M;k=pri[++j]){
			npr[i*k]=1;
			if(!(i%k)) break;
		}
	}
}

signed main(){
	sieve();srand(time(0));
	int n=win(),d=win(),m=0,ans=2,l=0;a[1]=d;
	for(re int i=2;i<=n;++i) a[i]=win(),d=gcd(d,a[i]);
	if(d!=1) return puts("-1"),0;
	sort(a+1,a+n+1);
	if(a[1]==1) return puts("1"),0;
	for(re int i=1;i<=n;++i) if(!ton[a[i]]){
		b[++m]=a[i];
		for(re int j=a[i];j<=M;j+=a[i]) ton[j]=1;
	}
	n=m;
	for(re int i=1;i<=n;++i) a[i]=b[i];
	memset(ton,0,sizeof ton);
	while(1){
		random_shuffle(a+1,a+n+1);
		random_shuffle(b+1,b+m+1);
		for(re int i=1;i<=n;++i) 
			for(re int j=1,tmp;j<=m;++j) if(a[i]!=b[j]){
				tmp=gcd(a[i],b[j]);
				if(tmp==1) return printf("%d\n",ans),0;
				if(!ton[tmp]) ton[tmp]=1,c[++l]=tmp;
			}
		for(re int i=1;i<=l;++i) ton[b[i]=c[i]]=0;
		m=l,l=0,++ans;
	}
	return 0;
}

```

等老哥来 hack/xyx。

---

## 作者：A_Pikachu (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/CF1043F)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf1043f-make-it-one)）

$\Large\mathscr{P}\mathit{art}\,\,1\;\;\text{基本思路}$

题目要求数列中最大公因数为 $1$ 的集合大小最小值，而值域只有 $3 \times 10^5$，因为在答案集合中任意去掉一个数都会出现其它数有不为 $1$ 的最大公因数，又因为 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 = 510510 > 3 \times 10^5$，所以不难想到答案集合中每个数恰好是它们最小公倍数去除某一个质因子时理论上最小值最大，即 $Ans=\{\frac{(\prod p_i)}{p_i}\}$，所以最大大小为 $7$，其中最大数为 $3 \times 5 \times 7 \times 11 \times 13 \times 17 = 255255 \lt 3 \times 10^5$。

既然我们知道了答案的最大值，那么可以考虑在当前答案选取 $s$ 个数时，判断其合法性，也就是至少有一种选择方案能够满足。设 $f[i]$ 表示选 $s$ 个数时，最大公因数为 $i$ 的方案数，那么合法答案就是 $[f[1] \gt 0]$。

先想最大公因数为 $i$ 的倍数时的方案，则需要从 $i$ 的倍数中选 $s$ 个数。

再排除最大公因数大于 $i$ 且为 $i$ 的倍数的方案，即 $\displaystyle\sum_{j=2,\ ij\le V} f[ij]$。

设 $g[i]$ 为 $i$ 在数列中的倍数个数，则易得转移方程为 $g[i]=\displaystyle\sum_{j=2,\ ij\le V} g[ij]$，初始状态为 $g[a[i]]=1$。

最终可得转移方程为 $f[i]=\dbinom{g[i]}{s}-\displaystyle\sum_{j=2,\ ij\le V} f[ij]$。

$\Large\mathscr{P}\mathit{art}\,\,2\;\;\text{Code}$

```cpp
#include <cstdio>
const int N=3e5+5,MOD=1000000007;
int n,u,ans,inv[N],fac[N],f[N],g[N];
int C(int x,int y){return 1LL*fac[x]*inv[x-y]%MOD*inv[y]%MOD;}
bool ck(int s){
	for(int i=N-1; i; i--){
		f[i]=C(g[i],s);
		for(int j=2; i*j<N; j++) f[i]=(f[i]-f[i*j]+MOD)%MOD;
	}
	return f[1];
}
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&u),++g[u];
	for(int i=1; i<N; i++) for(int j=2; i*j<N; j++) g[i]+=g[i*j];
	inv[0]=inv[1]=fac[1]=fac[0]=1;
	for(int i=2; i<=n; i++) inv[i]=(-1LL*inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
	for(int i=2; i<=n; i++) inv[i]=1LL*inv[i-1]*inv[i]%MOD,fac[i]=1LL*fac[i-1]*i%MOD;
	for(int i=1; i<=7; i++){
		if(!ck(i)) continue;
		printf("%d\n",i);
		return 0;
	}
	printf("-1\n");
	return 0;
}
```

时间复杂度 $\Theta(V \ln V+n)$，其中 $V$ 表示值域，由于 $V$ 和 $n$ 同级，所以实际就是 $\Theta(n \ln n)$。

---

## 作者：YLWang (赞：5)

提供一种简单直接暴力的推式子办法。

首先发现答案必定 $\leqslant 7$。否则必定无解。

我们考虑记录取 $t$ 个数的时候，每个数作为 $\gcd$ 出现的方案数。

有 
$$ 
c_k = \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} [\gcd(i,j)=k]a_ib_j
$$

这玩意是个 $\gcd$ 卷积状物。对于这种玩意我们是有 $O(n\ln n)$ 的做法的。具体地，我们考虑先求出 $d$ 数组表示不考虑 $\gcd$ 条件的方案数，即为反演的 $F$ 函数。可以简单地枚举倍数。然后反演。枚举倍数即可。

```cpp
const int MAXN = 3e5 + 5;
#define vi vector < int > 
vi a, st; int n, m, val[MAXN];
int mu[MAXN], prime[MAXN], tot, vis[MAXN];
void init(int n = MAXN - 5) {
	mu[1] = 1;
	For(i, 2, n) {
		if(!vis[i]) prime[++tot] = i, mu[i] = -1;
		for(int j = 1; j <= tot && i * prime[j] <= n; j++) {
			int to = i * prime[j]; vis[to] = 1;
			if(i % prime[j] == 0) {
				mu[to] = 0; break;
			} else mu[to] = -mu[i];
		}
	}
}
vi operator * (const vi &a, const vi &b) {
	vi ans(m + 5);
	For(i, 1, m) {
		int t1 = 0, t2 = 0;
		for(int j = 1; i * j <= m; j++)
			t1 += a[i * j], t2 += b[i * j];
		ans[i] = t1 * t2;
	}
	For(i, 1, m)
		for(int j = 2; i * j <= m; j++)
			ans[i] += ans[i * j] * mu[j];
	return ans;
}
signed main()
{
    #ifndef ONLINE_JUDGE
        file("pro");
    #endif
	n = read(); 
	For(i, 1, n)
		val[i] = read(), ckmax(m, val[i]);
	init(); st.resize(m + 5); 
	For(i, 1, n) st[val[i]] = 1;
	if(st[1]) return printf("1\n"), 0;
	a = st;
	For(i, 1, 6) {
		a = a * st;
		if(a[1]) return printf("%lld\n", i + 1), 0;
	}
	printf("-1\n");
    return FastIO::Fflush(), 0;
}
```

---

## 作者：syzf2222 (赞：4)

容易判断无解当且仅当整体的 $\gcd$ 不为 $1$。

定义 $\gcd$ 卷积为 $h_i=or f_jg_k [\gcd(j,k)=i]$，是布尔数组的变换。

我们可以在 $\text{polylog}$ 的复杂度内实现它。

具体地，我们考虑计算 $h_i=\sum \limits_{\gcd(j,k)=i} f_jg_k$，然后判断其是否为 $0$。

记 $sf_i=\sum\limits_{i|j}f_j$，$sg_i=\sum\limits_{i|j}g_j$，这可以 $\Theta(n\ln n)$ 地计算。

$h_i=\sum\limits_{\gcd(j,k)=i}f_jg_k=\sum\limits_{d=1}^{[\frac{n}{i}]}\mu(d) sf_{id}sg_{id}$，也可以 $\Theta(n\ln n)$ 地计算。

容易发现任何时候不可能所有的数都是最小的数的倍数，否则无解，所以每一次 $\gcd$ 卷积最小值都至少会减半，故答案是 $\log$ 级别的。

至此我们得到了一个 $\Theta(n\ln n\log n)$ 的做法，考虑继续优化。

考虑倍增，设初始数组为 $f$，则预处理 $f^{2^i}$，不难发现 $i$ 是 $\log\log$ 级别的。于是从高位往低位依次判断即可。

时间复杂度 $\Theta(n \ln n \log\log n)$，喜提最劣解。

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
const int maxn=3e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int flag[maxn],mu[maxn],pri[maxn],tot;
int n,a[maxn],all,ans;
inline int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}
int f[6][maxn],res[maxn],flg,now[maxn];
int t1[maxn],t2[maxn];
inline void mul(int *f1,int *f2,int *f3){
	for(int i=1;i<=N;i++){
		t1[i]=t2[i]=0;
		for(int j=i;j<=N;j+=i)
			t1[i]+=f2[j],t2[i]+=f3[j];
	}
	for(int i=1;i<=N;i++){
		long long val=0;
		for(int j=1;j<=N/i;j++)
			val+=1ll*mu[j]*t1[i*j]*t2[i*j];
		f1[i]=(val!=0);
	}
}
int main(){
	mu[1]=1;
	for(int i=2;i<=N;i++){
		if(!flag[i])pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*pri[j]<=N;j++){
			flag[i*pri[j]]=1;
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}mu[i*pri[j]]=-mu[i];
		}
	}
	n=read();
	for(int i=1,x;i<=n;i++)
		x=read(),a[x]=1,all=gcd(all,x);
	if(all>1)return puts("-1")&0;
	if(a[1])return puts("1")&0;
	memcpy(f[0],a,sizeof(f[0]));
	for(int i=1;i<=5;i++)
		mul(f[i],f[i-1],f[i-1]);
	for(int i=5;~i;--i){
		if(!flg){
			if(!f[i][1]){
				memcpy(res,f[i],sizeof(res));
				flg=1;ans+=(1<<i);
			}continue;
		}mul(now,res,f[i]);
		if(!now[1]){
			memcpy(res,now,sizeof(res));
			ans+=(1<<i);
		}
	}printf("%d\n",ans+1);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：fade_away (赞：4)

## Solution
给大家提供一个暴力做法。

首先来看几个显然的性质：
- 一个数可以被分解为最多6个数
- 答案小于等于7
- 一个数分解后的质数幂次只保留1即可，对答案没有任何影响。

于是我们先特判存在1的情况，并且把每个数变成$p_1p_2p_3...p_k$的形式。

然后考虑枚举一个数，求出包含这个数的最小答案：现在相当于有$p_1,p_2,...p_k$这么多条件，要求选出最少的数把这些条件都干掉，注意到$k\leq 6$，因此我们可以对于所有$2^k$种状态求出是否存在一个数一次就可以干掉这个状态表示的所有条件，设其为$g_{1...2^k}$。

然后就相当于求出一个最小的$t$，使得$g$的$k$次$or$卷积满足$2^k-1$这个状态非空。

这个可以在$O(k^22^k)$的时间内完成，因此总复杂度为$O(nk^22^k)$。

还有一个问题是怎么快速求出$g_{1...2^k}$，我们可以预处理$tag_i$表示有多少个数和$i$不互质。这个可以通过对每个数的$2^k$个状态表示的数做一波容斥得到，时间复杂度$O(n2^k+n\ln n)$。

因此总复杂度$O(nk^22^k+n\ln n)$，但常数不大，稍微卡卡就能跑进$1s$。

## Code
```cpp
int MN[105], cnt[105], mul[MAXN][64], tag[MAXN], f[105], g[105], mn[MAXN], prime[MAXN], pnum = 0, n;
vector<int> V[MAXN];
void Init(int n) {
	for (int i = 2; i <= n ; ++ i) {
		if (mn[i]) continue;
		for (int j = i; j <= n ; j += i) if (!mn[j]) mn[j] = i;
	}
}
void fwt(int *A, int n, int opt) {
	for (int i = 0; i < n ; ++ i)
		for (int j = 0; j < 1 << n ; ++ j)
			if (!((j >> i) & 1)) A[j | (1 << i)] += (opt == 1 ? A[j] : -A[j]);
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	Init(MX), read(n);
	for (int i = 1; i < 64 ; ++ i) MN[i] = (i & 1) ? 0 : MN[i >> 1] + 1, cnt[i] = cnt[i >> 1] + (i & 1);
	for (int i = 1, x; i <= n ; ++ i) {
		read(x);
		if (x == 1) { print(1); return 0; }
		while (x > 1) {
			if (!V[i].size() || mn[x] != V[i].back()) V[i].PB(mn[x]); 
			x /= mn[x];
		}
		mul[i][0] = 1;
		for (int j = 1; j < 1 << V[i].size() ; ++ j) {
			mul[i][j] = mul[i][j - (1 << MN[j])] * V[i][MN[j]];
			tag[mul[i][j]] += (cnt[j] & 1) ? 1 : -1;
		}
	}
	for (int i = MX; i >= 1 ; -- i)
		for (int j = i + i; j <= MX ; j += i) tag[j] += tag[i];
	int ans = INF;
	for (int i = 1; i <= n ; ++ i) {
		int len = V[i].size();
		for (int j = 1; j < 1 << len ; ++ j) f[j] = g[j] = (tag[mul[i][j]] < n);

		if (f[(1 << len) - 1]) { print(2); return 0; }

		fwt(g, len, 1);
		
		for (int t = 1; t <= min(len - 1, ans - 2) ; ++ t) {
			fwt(f, len, 1);
			for (int j = 0; j < 1 << len ; ++ j) f[j] = f[j] * g[j];
			fwt(f, len, -1);
			if (f[(1 << len) - 1]) { ans = t + 2; break; }
		}
	}
	if (ans == INF) { print(-1); return 0; }
	print(ans);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：3)

[CF1043F Make It One](https://www.luogu.com.cn/problem/CF1043F)

首先若有解则答案不超过 $7$，因为一个数最多有 $6$ 个质因子，我们先选择任意数，再对它的每个质因子选择不含该质因子的数。

算法一：

设 $f_{i, j}$ 表示大小为 $i$ 且 $\gcd = j$ 的子集数量。莫比乌斯反演，设 $g_{i, j}$ 表示 $\gcd$ 为 $j$ 的倍数的子集数量，则 $g_{i, j} = c_j ^ i$，其中 $c_j$ 表示初始序列中 $j$ 的倍数，则 $f_{i, j} = \sum_{j\mid k} \mu(\frac k j) g_{i, k}$，本质上就是倍数容斥。

至此已经可以通过了，但取模不太好看。

算法二：

考虑在 $f_{i - 1}$ 的基础上再添加一层 $f_1$，则 $f_i$ 等于 $f_{i - 1}$ 和 $f_1$ 做 $\gcd$ 卷积，即 $a_i b_j\to c_{\gcd(i, j)}$，这个倍数容斥直接做，也可以看成按位与卷积（$\gcd$ 和按位与在某种角度下是等价的），对整个数列做高维前缀和（狄利克雷前缀和）。每做一次卷积就令 $f_{i, j} = [f_{i, j} > 0]$，即修改 $f$ 的定义为是否存在大小为 $i$ 且 $\gcd = j$ 的子集。这样值域就在 $a ^ 2$ 范围内了，不需要取模。

两个做法本质上是相同的，它们都相当于对 $c_j ^ i$ 做狄利克雷差分，但是第二个做法降低了值域范围。

视 $n, a_i$ 同级。$i$ 的数量级为最大本质不同质因子数量 $\mathcal{O}(\frac {\log n} {\log \log n})$，每次暴力倍数容斥 $\mathcal{O}(n\ln n)$，时间复杂度为 $\mathcal{O}(\frac {n\log ^ 2 n} {\log\log n})$。[代码](https://codeforces.com/contest/1043/submission/190068997)。

若容斥部分用狄利克雷前缀和实现则复杂度为 $\mathcal{O}(n\log n)$。

进一步地，将算法一的枚举改成二分，算法二的枚举改成倍增，时间复杂度 $\mathcal{O}(n\log(\frac {\log n}{\log \log n}) \log\log n)$ 即 $\mathcal{O}(n\log ^ 2\log n)$。

---

## 作者：cirnovsky (赞：3)

## 题意简述

给定一个整数集合，让你挑出一个子集，使得子集里的数互素，问最少挑多少个。

## 题解

又是一道很妙的题。

好像其他的题解都是一维 DP 或者直接纯数学方法，这里提供一种好理解一点的二维 DP。

开始拿到这道题，没有任何思路。

然后开始猜答案的范围，想着能不能直接枚举或者二分。

然后发现 $2\times3\times5\times7\times11\times13\times17>300000$，所以 300000 以内的数字最多有 6 个质因子。

所以我们的答案最多为 6 吗？不是的，因为如果令七个数分别等于这七个质数的其中六个（互不相同），一共七个，所以答案上限为七。

那么基本上答案的枚举可以当成常数了。

这里有一个大胆的 DP：我们定义 `dp[i][j]`: 表示选 $i$ 个数的情况下所有选择的 $i$ 个数的 **公约数** 为 $j$ 的方案数。

为什么这里要设为公约数而不是最大公约数呢？

因为这样才方便我们去重。

本来我想的是定义存在性，不过好像方程不好找，于是放弃了。

那么方程为（未去重）：$dp_{i,j}=C_{cnt_{j}}^{i}$。

其中 `cnt[x]` 表示集合中有多少数是 $x$ 的倍数。

因为我们 DP 的定义是公约数，所以我们需要去掉不是最大公约数的情况。

所以去重过后，我们的 DP 方程为：$dp_{i,j}=C_{cnt_{j}}^{i}-\sum_{j\mid k\wedge k>j}dp_{k}$。

最后的答案就是 $\min\{i\},dp_{i,1}>0$。

```cpp
#include <cstdio>

const int Maxn = 3e5 + 5, Maxv = Maxn - 5, Mod = 1e9 + 7;
int n, a[Maxn], cnt[Maxn], dp[10][Maxn], fac[Maxn], inv[Maxn];
// dp[i][j]: 表示选 i 个数的情况下公约数 为 j 的方案数

int add(int x, int y) { return ((x + y) % Mod + Mod) % Mod; }
int mul(int x, int y) { return (long long)x * y % Mod; }

void exgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return ;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

int Inv(const int a, const int m)
{
	int x, y;
	exgcd(a, m, x, y);
	return ((x % m) + m) % m;
}

int C(int n, int k)
{
	if (n < k)	return 0;
	return mul(fac[n], mul(inv[k], inv[n - k]));
} // 以上板子

signed main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		cnt[a[i]]++;
		dp[1][a[i]]++;
		if (a[i] == 1)
		{
			puts("1");
			return 0;
		}
	}
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)	fac[i] = mul(fac[i - 1], i);
	for (int i = 0; i <= n; ++i)	inv[i] = Inv(fac[i], Mod); // 预处理阶乘和逆元，组合数用
	for (int i = 1; i <= Maxv; ++i)
	{
		for (int j = (i << 1); j <= Maxv; j += i)	cnt[i] += cnt[j];
	} // 预处理 cnt
	for (int i = 2; i <= 7; ++i)
	{
		for (int j = Maxv; j >= 1; --j)
		{
			dp[i][j] = C(cnt[j], i);
			for (int k = (j << 1); k <= Maxv; k += j)	dp[i][j] = add(dp[i][j], -dp[i][k]);
		}
	}
	for (int i = 1; i <= 7; ++i)
	{
		if (dp[i][1])
		{
			printf("%d\n", i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：Purslane (赞：2)

## Solution

A bit difficult .

主要证明答案长度不大于 $7$ . 

> 假设答案大于 $8$ . 那么我们从答案数组中任意去掉一个数 , 数组 gcd 就会变成非 $1$ . 显然这些数肯定两两互质 , 不然数组 gcd 就会非 $1$ 了 . 那么每个数都有至少 $7$ 个不同的质因数 . 显然 $3 \times 10^5$ 的数据下不会有这么多质因数 .

然后就很简单 . $dp_{i,p}$ 表示选 $i$ 个数 , 最大公约数是 $p$ 的方案数 .

$$dp_{i,j}=C^{i}_{\sum [a_i|j]} - \sum dp_{i,kj} (k \in \mathbb{Z})$$ 

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300000+10,MOD=1e9+7;
int n,fc[MAXN],inv[MAXN],cnt[MAXN],a[MAXN],dp[8][MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans*=base,ans%=MOD;
		base*=base,base%=MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {if(u>d) return 0;return fc[d]*inv[d-u]%MOD*inv[u]%MOD;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];	
	fc[0]=1;ffor(i,1,n) fc[i]=fc[i-1]*i%MOD;
	inv[n]=qpow(fc[n],MOD-2);roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,1,n) cnt[a[i]]++;
	ffor(i,1,300000) ffor(j,2,300000/i) cnt[i]+=cnt[i*j];
	roff(i,300000,1) {
		ffor(k,1,7) {
			dp[k][i]=C(k,cnt[i]);
			ffor(j,2,300000/i) dp[k][i]-=dp[k][i*j],dp[k][i]%=MOD;
		}
	}
	ffor(i,1,7) if(dp[i][1]!=0) {cout<<i;return 0;}
	cout<<-1;
	return 0;
}
```

---

## 作者：影辰 (赞：2)

这是一道善良的题目

先考虑一下答案的上界

首先，如果增加一个数，无法使gcd更小，即去掉gcd至少一个质因数，那么他没有必要添加到里面去。

考虑一下3e5的数可能会有几个质因数

最小的七个 2*3*5*7*11*13*17=510510>300000

所以答案不会大于7

那么问题就转换为了判断是否可行

我们大概只需要算一下gcd为1时有多少种方案数

用fi表示gcd为i时的方案数

从后往前算，总复杂度为O(3e5*ln 3e5)

（当然也可以线性筛加反演，应该会快很多~~但是我懒得打~~）

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int sz=3e5+1;
const int mod=1e8+7;
int n,x;
int inv[sz],a[sz],b[sz];
int cnt[sz],f[sz];
void init(){
	a[0]=b[0]=1;
	inv[1]=a[1]=b[1]=1;
	for(int i=2;i<sz;i++){
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		a[i]=1ll*a[i-1]*i%mod;
		b[i]=1ll*b[i-1]*inv[i]%mod;
	}
}
int C(int n,int m){
	if(!n) return 0;
	return 1ll*a[n]*b[m]%mod*b[n-m]%mod;
}
bool cur(int len){
	for(int i=sz-1;i>=1;i--){
		f[i]=C(cnt[i],len);
		for(int j=2;i*j<sz;j++) f[i]=(f[i]-f[i*j]+mod)%mod;
	}
	return f[1];
}
int main(){
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&x),cnt[x]++;
	for(int i=1;i<sz;i++) for(int j=2;i*j<sz;j++) cnt[i]+=cnt[i*j];
	x=1;
	while(!cur(x)&x<=7) x++;
	if(x<=7) printf("%d",x);
	else printf("-1");
}
```

---

## 作者：fireinice (赞：0)

看到题解区里复杂度最优就是 $\Theta(n\log n)$ 了, $\gcd$ 卷积的一篇题解则只推到了 $\Theta(n\log n\log \log n)$, 所以来写写基于 $\gcd$ 卷积的 $\Theta(n(\log\log n)^2)$ 更优解法.

首先观察到答案上界和质因子个数线性相关, 经典结论是质因子个数量级是 $\Theta(\dfrac{\log n}{\log \log n})$.

于是考虑枚举一个答案为 $k$, 那么设 $b_n$, 其中 $b_i=\begin{cases}1 , \exists a_j=i\\ 0, \text{otherwise}\end{cases}$, 那么用 $\gcd$ 卷积算 $b^k$ 即可.

但 $\gcd$ 卷积并不像题解区里其他人说的是 $n\ln n$, 因为对 $b$ 预处理 $b'_i=\sum_{i\vert j} b_j$ 和相对应的逆变换实际上是迪利克雷后缀和/后缀差分, 复杂度是 $n\log \log n$. 而且也没必要每次都做变换: 直接算出 $b'$ 后 $b'_i={b'_i}^k$ 再逆变换多好啊. 此时复杂度就是 $\Theta(nk\log\log n)=\Theta(n\log n)$.

然后显然答案满足单调性, 加一个二分答案就是 $\Theta(n(\log \log n)^2)$ 了.

速度的话, 看看下面完全不卡常的代码也能冲进最优解第一页.

code:

```cpp
#include <iostream>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 3e5 + 500;

int ps[N], mps[N], pcnt;
void xxs(int n) {
    mps[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!mps[i])
            mps[i] = ps[++pcnt] = i;
        for (int j = 1; j <= pcnt; j++) {
            if (ps[j] > mps[i] || ps[j] * i > n)
                break;
            mps[i * ps[j]] = ps[j];
        }
    }
}
ll a[N], b[N], c[N];
int n;
const ll P = 998244353;
void dilisufsum(int n, ll* a) {
    for (int i = 1; i <= pcnt; i++)
        for (int j = n / ps[i]; j; j--)
            a[j] = (a[j] + a[j * ps[i]]) % P;
}
void invdilisufsum(int n, ll* a) {
    for (int i = 1; i <= pcnt; i++)
        for (int j = 1; j <= n / ps[i]; j++)
            a[j] = (a[j] - a[j * ps[i]]) % P;
}
ll fpow(ll a, ll b) {
    return b == 0 ? 1 : (b & 1 ? a * fpow(a * a % P, b / 2) % P : fpow(a * a % P, b / 2));
}
bool check(int n, int x) {
    for (int i = 1; i <= n; i++)
        c[i] = fpow(b[i], x);
    invdilisufsum(n, c);
    return c[1];
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    ll v = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[a[i]] = 1, v = max(v, a[i]);
    xxs(v);
    dilisufsum(v, b);
    int l = 1, r = 8;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(v, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if (l == 8)
        cout << -1 << endl;
    else
        cout << l << endl;
    return 0;
}
```

---

## 作者：GreenDay (赞：0)

### 没有模数的组合数学题目！

----

首先，我们进行读入的操作，把$-1,1$的情况给判掉.

我们~~看题解发现~~，这道题有一个非常强的性质：

**性质** $ans \le \log\log\max{a_i}$,在本题中$ans \le 7$

注意到$2*3*5*7*11*13*17\ge300000$，所以一个数最多6个质因子。最坏情况下，我们选出来7个数，每个数都有6个质因子，而且这7个数两两之间质因子仅有1个不同。这样答案达到最大值为7.

于是问题转化成：对于$[2,6]$之间的数判定答案是否可行。

我们考虑十分狂野的做法：**直接对答案计数** 。

考虑容斥原理：设当前要检验的答案是$x$,读入的数当中$i$的倍数数量是$vis_i$

- 加上总体的方案数：$+C_{vis_1}^x$

- 减去选出的数都是**某个质数倍数**的数：$-C_{vis_2}^x,-C_{vis_3}^x,-C_{vis_5}^x...$

- 加上选出来的数可以**被表示为$p_1*p_2$的数**：$+C_{vis_6}^x,+C_{vis_{10}}^x...$

- ...

想到了什么？**莫比乌斯反演！**，很容易观察到每个组合数的系数就是莫比乌斯函数（考虑莫比乌斯函数的意义）。莫比乌斯反演在本质上就是一种容斥。

故答案$x$可行，当且仅当$\sum\limits_i C_{vis_i}^x \mu_i>0$

实现的时候可以随便找个模数（哈希），然后预处理组合数，莫比乌斯函数，倍数就可以了。复杂度$O(a \log a)$.精细一点还可以更优。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 300010 , mod = 998244353;
int maxa , cnt[N];

void input() {
    int n , g = 0 , a;
    scanf("%d" , &n);
    while(n--) {
        scanf("%d" , &a);
        if(a == 1) {puts("1") ; exit(0); }
        maxa = max(maxa , a);
        cnt[a] = 1;
        g = __gcd(g , a);
    }
    if(g != 1) {puts("-1") ; exit(0); }
}

inline int qpow(int x , int y = mod - 2) {
	int res = 1;
	for(; y ; y >>= 1 , x = 1ll * x * x % mod)
		if(y & 1) res = 1ll * res * x % mod;
	return res; 
} 
int fac[N] , inv[N];
inline int C(int x , int y) {
	if(y < 0 || y > x) return 0;
	return 1ll * fac[x] * inv[y] % mod * inv[x - y] % mod; 
}
typedef long long int64;

void C_init(int n) {
    fac[0] = 1;
    for(int i = 1 ; i <= n ; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[n] = qpow(fac[n]);
    for(int i = n-1 ; ~i ; i--) inv[i] = inv[i + 1] * (i + 1ll) % mod;
}

int miu[N] , vis[N];
void prepare() {
    for(int i = 1 ; i <= maxa ; ++i) miu[i] = 1;
    for(int i = 2 ; i <= maxa ; ++i)
        if(!vis[i])
            for(int j = i ; j <= maxa ; j += i) {
                if((j / i) % i == 0) miu[j] = 0;
                else miu[j] *= -1;
                vis[j] = 1;
            }
    for(int i = 1 ; i <= maxa ; ++i) {
        vis[i] = 0;
        for(int j = i ; j <= maxa ; j += i) vis[i] += cnt[j];
    }
    C_init(maxa);
}

bool check(int x) {
    int res = 0;
    for(int i = 1 ; i <= maxa ; ++i) {
        res += C(vis[i] , x)*miu[i];
        if(res >= mod) res -= mod ;
        else if(res < 0) res += mod;
    }
    return res > 0;
}

int main() {
    input();
    prepare();
    if(check(2)) return puts("2") & 0;
    if(check(3)) return puts("3") & 0;
    if(check(4)) return puts("4") & 0;
    if(check(5)) return puts("5") & 0;
    if(check(6)) return puts("6") & 0;
    return puts("7") & 0;
}
```

---

## 作者：wsy_jim (赞：0)

CF1043F Make It One

题意：给定 $n$ 个数，要求在其中选择 $x$ 个数使它们的 $gcd$ 为 $1$，求 $x$ 的最小值，数据范围：$n\leq 300000,a_i\leq 300000$  

$300000$ 之内的质因数最多只有 $6$ 个，答案每加一个，从质因子集合里一定去除掉一个数，可以从 $gcd$ 的组合意义上考虑，指的是几个数标准分解后交的部分，$gcd$ 为 $1$ 也就说明这几个数质因子没有交集，而且要保证最小所以包含在原先几个数并的集合内的数一定可以不选，选和不选没什么区别，所以加进来的新数一定会从全集里再取掉一部分

但是答案最多是 $7$ 个，因为我们在质因子最多的情况下可考虑的质因子有 $7$ 个，要求无交，可以从七个质因子的积中每次去掉一个，这样每个数都少一个质因子，七个数无交

答案很小可以枚举，枚举选 $k$ 个数，然后容斥，设 $f[i]$ 为选 $k$ 个数，$gcd$ 为 $i$ 的方案数，如果 $f[1]\not=0$ 那就合法，$f[i]=\binom{cnt_i}k-\sum_{ij\leq a_{max}}f(ij)$，$cnt_i$ 是这 $n$ 个数里面有多少个是 $i$ 的倍数，理解就是从 $gcd$ 为 $i$ 和 $i$ 的倍数的方案里减掉 $gcd$ 是 $i$ 的倍数的方案数，这样就只剩下 $gcd$ 为 $i$ 的方案了  

---

