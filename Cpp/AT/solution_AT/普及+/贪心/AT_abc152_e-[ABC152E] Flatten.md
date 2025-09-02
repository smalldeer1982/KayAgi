# [ABC152E] Flatten

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc152/tasks/abc152_e

$ N $ 個の正整数 $ A_1,...,A_N $ が与えられます。

次の条件を満たすような正整数 $ B_1,...,B_N $ を考えます。

条件：$ 1\ \leq\ i\ <\ j\ \leq\ N $ を満たすどのような $ i,j $ についても $ A_i\ B_i\ =\ A_j\ B_j $ が成り立つ。

このような $ B_1,...,B_N $ における $ B_1\ +\ ...\ +\ B_N $ の最小値を求めてください。

ただし、答えは非常に大きくなる可能性があるため、$ (10^9\ +7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^4 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ B_1=6 $, $ B_2=4 $, $ B_3=3 $ とすると条件を満たします。

### Sample Explanation 2

全ての $ B_i $ を $ 1 $ とすればよいです。

### Sample Explanation 3

和を $ (10^9+7) $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3
2 3 4```

### 输出

```
13```

## 样例 #2

### 输入

```
5
12 12 12 12 12```

### 输出

```
5```

## 样例 #3

### 输入

```
3
1000000 999999 999998```

### 输出

```
996989508```

# 题解

## 作者：_Tooler_Fu_ (赞：3)

看到还没有 python 的题解，就来贡献一份。

显然，令 $a_i \times b_i$ 都为 $\operatorname{lcm}(a_1,a_2,...a_n)$ 时答案最小。

考虑如何求整个 $a$ 序列的 $\operatorname{lcm}$。

考虑数据范围 $1 \le a_i \le 10^6$ 可知该 $\text{lcm}$ 会爆 long long。

那怎么办呢？用 python 直接莽！

~~然后就过了？~~

代码如下：

```python
from math import gcd
n=int(input())
a=input().split()
hh=0
ans=0
for i in range(0,len(a)):
	a[i]=int(a[i])
for i in a:
	if (hh==0):
		hh=i
	else:
		cc=gcd(hh,i)
		hh=hh//cc
		hh*=i
for i in a:
	ans+=hh//i
ans=ans%(1000000007)
print(ans)
```


---

## 作者：_7Mr (赞：2)

# 思路
思路很简单，就是求个公倍数，然后求和就好了，但问题是我们的公倍数连 `__int128` 都会爆，所以说我们需要使用逆元，~~当然逆元肯定是不会的~~，我太蒟蒻了，所以用了一种取巧的办法，使用了 Boost 库。

> Boost 库是一个功能强大、构造精巧、跨平台、开源并且完全免费的 C++ 程序库。

当然在正式比赛中千万不要使用，不要怪我没有提醒你。

用这个有什么用呢，他自带高精度，这时我们就不会爆了，那么就可以愉快的 AC 了。
# ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>//使用库
using namespace boost::multiprecision;
int n,mod=1e9+7; 
signed main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cpp_int ans,a[10005],lcm=1;//cpp_int->自带高精度
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];	
    	lcm=a[i]*lcm/__gcd(a[i],lcm);
	}
//	cout<<lcm<<endl;
	for(int i=1;i<=n;i++) ans+=(lcm/a[i]);
	cout<<ans%mod<<endl;
    return 0;
}


```

---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc152_e)。

#### 思路

首先可以看出本题求的是 $\sum_{i=1}^N \dfrac{\operatorname{lcm}}{A_i}$，一种简单的贪心策略。

$\operatorname{lcm}$ 指的是 $\operatorname{lcm}(A_1,A_2,\dots,A_n)$。

但由于 $\operatorname{lcm}$ 是一个很大的数，因此我们需要采用质因数分解来求得最小公倍数，首先把所有 $a_i$ 分解质因数，找出每个质因子出现的最大次数，相乘即可，由于涉及到除法取模，需要再来一个逆元。



#### CODe

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e6+7,Mod=1e9+7;
int prime[Maxn/2],in[Maxn],cnt,p[Maxn],g[Maxn];
bool isprime[Maxn];
inline void EulerSieve(ll N){
	isprime[1]=isprime[0]=1;
	in[1]=1;
	for(ll i=2;i<=N;i++){
		if(!isprime[i]) prime[++cnt]=i,in[i]=i;
		for(ll j=1;j<=cnt&&prime[j]*i<=N;j++){
			isprime[i*prime[j]]=1;
			in[i*prime[j]]=prime[j];
			if(!(i%prime[j])) break;
		}
	}
}
inline ll ksm(ll a,ll b,ll mod){
	ll z=1;
	while(b){
		if(b&1) z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
inline ll inv(ll a,ll mod){
	return ksm(a,mod-2,mod);
}
ll n,a[Maxn],Lcm=1,ans;
int main(){
	EulerSieve(Maxn-7);
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++){
		ll x=a[i];
		while(in[x]!=x){
			p[in[x]]++;
			g[in[x]]=max(g[in[x]],p[in[x]]);	
			x/=in[x];
		}
        // 统计质因数
		g[x]=max(g[x],p[x]+1);
		x=a[i];
       	// 清空数组
		while(in[x]!=x){
			p[in[x]]=0;
			x/=in[x];
		}
		p[x]=0;
	}
	for(ll i=1;i<=Maxn-6;i++) 
		if(g[i]!=0) Lcm*=ksm(i,g[i],Mod),Lcm%=Mod;
	for(ll i=1;i<=n;i++) ans=(ans+Lcm*inv(a[i],Mod)%Mod)%Mod;
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

发现所有 $A_iB_i$ 值都一样。这个只最小化，$B_i$ 也会最小化。最小可能的 $A_iB_i$ 为`lcm A`，应为`lcm A`定义为最小的正整数除了所有 $A_i$ 还满足 $B_i$ 的正整数条件。则答案为
$$\sum_{i\in A}\frac{\text{lcm} A}{i}$$

两个方法：

 1. 采用python自带的高精度 ~~调二十分钟玄学RE~~
 2. `lcm`取模算，对所有 $A_i$ 找到乘法逆元

讨论方法二；来取模算`lcm`，先素因数分解成素数的次幂，对每个素数次幂的`max`保存来构造最终`lcm`的素因数分解，以及求出 $A$ 里所有元素的乘法逆元。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int aray[10004], gcdForw[10004], gcdBack[10004];

int qpow(int base, int expo) {
	if(expo == 0) return 1;
	if(expo == 1) return base;
	ll v = qpow(base, expo>>1);
	v = (v * v % MOD);
	if(expo&1) v = (v * base % MOD);
	return v;
}

int modinv(ll val) {
	return qpow(val%MOD, MOD-2);
}

int mx[1000006];

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int N; cin >> N;
	ll lcm = 1;
	rep(i, N) {
		cin >> aray[i];
		int x = aray[i];
		for(int v=2; v*v<=x; v++) {
			if(x%v) continue;
			int cur = 0;
			while(x%v == 0) {
				cur++;
				x /= v;
			}
			mx[v] = max(mx[v], cur);
		}
		if(x != 1) mx[x] = max(mx[x], 1);
	}
	rep(i, 1000006) {
		if(mx[i]) lcm = (lcm * qpow(i, mx[i])) % MOD;
	}
	log(lcm);
	ll su = 0;
	rep(i, N) su = (su + lcm * modinv(aray[i])) % MOD;
	cout << su << endl;
}
```

---

## 作者：SilverLi (赞：1)

[Flatten の 传送门](https://www.luogu.com.cn/problem/AT_abc152_e)

题目中要求 $a_i\times b_i=a_j\times b_i$，也就可以求出所有数的最小公倍数。

然后就可求出每一个 $b_i=\operatorname{lcm}/a_i$。

但是，再求 `lcm` 的过程中，`long long` 都存不下。

所以先对每个 $a_i$ 分解质因数，把每个质因数的最大出现次数存存起来，以及在计算 $\operatorname{lcm}/a_i$ 时加个逆元。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 10005
#define M 1000005
#define mod 1000000007
#define int long long
int n,a[N],p[M];
int ans,LCM=1;
inline bool get(int x) {
	int q=sqrt(x);
	for(int i=2;i<=q;++i)
		if(!(x%i))	return 0;
	return 1;
}
inline int qpow(int x,int p) {
	int res=1;
	while(p) {
		if(p&1)	res=(res*x)%mod;
		p>>=1,x=(x*x)%mod;
	}
	return res;
}
inline int inv(int x) {return qpow(x,mod-2)%mod;}
inline int ch(int i,int j) {return (i*inv(j))%mod;}
signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) {
		cin>>a[i];
		int k=a[i],q=sqrt(a[i]);
		if(get(k)) p[k]=max(p[k],1ll);
		for(int j=2;j<=q;++j)
			if(!(k%j)) {
				int ps=0;
				while(!(k%j))	++ps,k/=j;
				p[j]=max(p[j],ps);
			}
		if(k>1)	p[k]=max(p[k],1ll);
	}
	for(int i=2;i<=M-5;++i)	LCM=(LCM*qpow(i,p[i]))%mod;
	for(int i=1;i<=n;++i)	ans=(ans+ch(LCM,a[i]))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

~~模拟赛时划水切的题……~~

- 题意

给定长度为 $n$ 的序列 $a$，构造 $b$ 使得对于 $\forall 1\le i \le n,a_i\times b_i$ 相等，求 $\sum\limits_{i=1}^nb_i$ 的最小值。

- 分析

考虑显然令 $a_i\times b_i$ 均为 $\operatorname{lcm}(a_1,a_2,\dots,a_n)$ 最小，记 $L=\operatorname{lcm}(a_1,a_2,\dots,a_n)$。

考虑一种 naive 的做法，直接暴力求 $L$，$b_i=\frac{L}{a_i}$，这样肯定过不了，显然 $L$ 太大了，考略优化。

你可以对每一种质因数考虑，考略一种质因数 $x$，$cnt_{LCM,x}=\max\limits_{i=1}^n(cnt_{a_i,x})$，其中记 $cnt_{y,x}$ 为 $y$ 中 $x$ 的个数。对于每种质因数考虑，小于 $1000$ 的质数只有 $168$ 个，直接暴力，对于大于 $100$ 的大质因数，显然可以统计其最小公倍数，记为 $L^\prime$，$b_i=b_i\times\frac{L^\prime}{a_i}$，那就做完了！

- code

```cpp
#include <bits/stdc++.h>
#define LL long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e4 + 500), mod(1e9 + 7);
int n, a[maxn], pr[205], tot, cnt[maxn][205], b[maxn], mx[205], sum(1), ans;
bool vis[1000005];

int ksm (int b, int k) {
	int res = 1;
	for (; k; k >>= 1, b = (LL)b * b % mod) if (k & 1) res = (LL)res * b % mod;
	return res;
}

int main () {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(), b[i] = 1;
	for (int i = 2; i <= 1000; i++) {
		if (!vis[i]) pr[++tot] = i;
		for (int j = 1; j <= tot && i * pr[j] <= 1000; j++) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= tot; j++)
			while (a[i] % pr[j] == 0) ++cnt[i][j], a[i] /= pr[j];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= tot; j++) mx[j] = max(mx[j], cnt[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= tot; j++)
			b[i] = (LL)b[i] * ksm(pr[j], mx[j] - cnt[i][j]) % mod;
	for (int i = 1; i <= n; i++) {
		if (vis[a[i]] || a[i] == 1) continue;
		vis[a[i]] = 1;
		sum = (LL)sum * a[i] % mod;
	}
	for (int i = 1; i <= n; i++) b[i] = (LL)b[i] * sum % mod * ksm(a[i], mod - 2) % mod;
	for (int i = 1; i <= n; i++) ans = (ans + b[i]) % mod;
	write(ans);
}
```

---

## 作者：dingshengyang (赞：1)

我是**。

---
+ $\text{level 1}$

找出所有 $a_i$ 的 $\operatorname{lcm}$，记作 $LCM$。

则答案为 $\sum_{i=1}^n \dfrac{LCM}{a_i}$。


+ $\text{level 2 to 4 }$

不想听我烦的可以跳过。($LCM$ 爆 `long long` 了。)

否则请先到 [gate](https://www.luogu.com.cn/paste/0qpf764b)。

+ $\text{level 5}$

~~恭喜你，达到了炮姐的水平。~~

把所有数分解质因子。
对于每个数，减去它之后其他的部分，便是 $\dfrac{LCM}{a_i}$。


```cpp
#include <bits/stdc++.h>
using namespace std;
//来一发 OOP！！！！！ 
class slove{
	static const int N = 1e6+5;
	static const int MOD = 1e9+7;
	typedef long long LL;
	LL* a = new LL[N]{};
	int* st = new int[N]{};
	int n,maxn;
	public:
	void input(){
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++)
			scanf("%lld",&a[i]),maxn=max(maxn,int(a[i]));
	}
	void get(LL m){
		LL t = sqrt(m) + 5;
		for(int i = 2;i <= t;i ++){
			int cnt = 0;
			while(m%i==0){
				m/=i;
				cnt ++;
			}
			st[i] = max(st[i],cnt);
//			printf("st[%d]=%d\n",i,st[i]);
		}
		if(m != 0) st[m] = max(st[m],1);
	} 
	LL quick_power(LL a,LL b){
		LL s = 1;
		while(b){
			if(b&1)s=(s*a)%MOD;
			b >>= 1;a=(a*a)%MOD;
		}
		return s;
	}
	LL inv(LL m){
		if(m%MOD == 0)return -1;
		else return quick_power(m,MOD-2);
	} 
	LL get_lcm(){
		for(int i = 1;i <= n;i ++)get(a[i]);
//		for(int i = 1;i <= maxn;i ++){
//			printf("st%d\n",st[i]);
//			if(i%5==0)printf("\n");
//		}
		LL ans = 1;
		for(LL i = 2;i <= maxn;i ++){
			if(st[i] == 0)continue;
//			printf("i=%d\nst[i]=%d\n",i,st[i]);
			ans = ans*quick_power(i,st[i])%MOD;
		}
//		printf("lcm=%lld\n",ans);
		return ans;
	}
	slove(){
		input();//我甚是傻逼，input 输入忘记写 ！！！ 
		LL tmp = get_lcm();
//		printf("tmp=%lld\n",tmp);
		LL ans = 0;
		for(int i = 1;i <= n;i ++)ans = (tmp*inv(a[i])+ans)%MOD;
		printf("%lld\n",ans);
	}
	~slove(){
		delete[] a; 
	}
}; 
int main() {
	slove slover;
	return 0;
}
//gcd 不会爆 long long
//lcm 会
//分解质因数！！！ O(N sqrt N)
//看看那个因数大 ，累乘求 lcm O((sqrt N)*log2(N)) 

```






















---

## 作者：Jairon314 (赞：1)

> [题目链接](https://atcoder.jp/contests/abc152/tasks/abc152_e)

$ Solution $

------------

发现最后的结果需要满足 $ A_{n-1}B_{n-1}=A_nB_n $

那么 $ A_{n-2}B_{n-2}=A_{n-1}B_{n-1}=A_nB_n $

可以发现 $ \forall \, i \in [1,n] ,A_iB_i=A_nB_n=LCM_{i=1}^n A_i  $

可是求最小公倍数时不可直接取模，而答案又非常大。

所以我们对每个 $ A_i $ 先分解质因数，然后找到每个因子出现的最大次数乘起来中间进行取模即可

[AC记录](https://atcoder.jp/contests/abc152/submissions/29156967)

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
using namespace std;

#define $int long long

/***** Fast_IO *****/

using vii = vector<int>;
using pii = pair<int,int>;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
	
	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }
	
	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
	#define db double
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

const $int mod = 1e9+7;

$int n;
$int a[maxn];

$int qpow($int a,$int b){
	$int res=1,tmp=a;
	while(b){ if(b&1){ res=(1ll*res*tmp)%mod; } tmp=(1ll*tmp*tmp)%mod; b>>=1; }
	return res;
}

$int inv($int k){ return qpow(k,mod-2); }

$int ans=0;

$int cnt[maxn];

void factor($int k){
	for($int i=2,c=0;i*i<=k;i++,c=0){ while(k%i==0){ k/=i; chmax(cnt[i],++c); } }
	chmax(cnt[k],1ll);
	return;
}

int main(){
	read(n);
	FOR(i,1,n){ read(a[i]); factor(a[i]); ans=(ans+inv(a[i]))%mod; }
	FOR(i,1,maxn){ if(cnt[i]){ ans=(ans*qpow(i,cnt[i]))%mod; } }
	printf("%lld\n",ans);
	return 0;
}
```


---

