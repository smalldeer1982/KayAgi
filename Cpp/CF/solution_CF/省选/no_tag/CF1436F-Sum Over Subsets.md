# Sum Over Subsets

## 题目描述

You are given a multiset $ S $ . Over all pairs of subsets $ A $ and $ B $ , such that:

- $ B \subset A $ ;
- $ |B| = |A| - 1 $ ;
- greatest common divisor of all elements in $ A $ is equal to one;

find the sum of $ \sum_{x \in A}{x} \cdot \sum_{x \in B}{x} $ , modulo $ 998\,244\,353 $ .

## 说明/提示

A multiset is a set where elements are allowed to coincide. $ |X| $ is the cardinality of a set $ X $ , the number of elements in it.

 $ A \subset B $ : Set $ A $ is a subset of a set $ B $ .

In the first example $ B=\{1\}, A=\{1,2\} $ and $ B=\{2\}, A=\{1, 2\} $ have a product equal to $ 1\cdot3 + 2\cdot3=9 $ . Other pairs of $ A $ and $ B $ don't satisfy the given constraints.

## 样例 #1

### 输入

```
2
1 1
2 1```

### 输出

```
9```

## 样例 #2

### 输入

```
4
1 1
2 1
3 1
6 1```

### 输出

```
1207```

## 样例 #3

### 输入

```
1
1 5```

### 输出

```
560```

# 题解

## 作者：Rainbow_qwq (赞：8)

[CF1436F Sum Over Subsets](https://www.luogu.com.cn/problem/CF1436F)

---

看到 $\gcd=1$ ，可以莫比乌斯反演（容斥），枚举一个 $d$ ，求出 $ans(d)=$ 所有倍数 $=d$ 的树集合的答案，然后 $res=\sum_{d=1}^{1e5}\mu (d)ans(d)$ 。

这样 $\gcd=1$ 的条件没了，接下来就是求 给出一个 $S$ ， 求 

$\sum_{A\in S}\sum_{x \in A}{x} \cdot \sum_{x \in B}{x}$

其中 $B$ 为 $A$ 删掉一个数。

然后我想了一些推这个式子的方法，但都不行。

瞪着这个式子看一看，其实就是求 $\sum x\times y,x\in A,y\in B$

考虑分类讨论，下面设 $cnt=|S|$ 。

假设有一个数 $a_i\in S$ ，那 $a_i^2$ 的贡献为：

首先一定 $a_i\in A,a_i\in B$，那么 $a_i$ 这个数就确定要选。然后要在余下 $cnt-1$ 个数里选一个当删掉的，方案数 $cnt-1$。剩下 $cnt-2$ 个数可选可不选 ，$2^{cnt-2}$ 。

贡献为 $a_i^2 \times 2^{cnt-2} (cnt-1)$

假设有2个数 $a_i,a_j\in S$ ，那 $a_ia_j$ 的贡献为：

首先一定 $a_i,a_j\in A$。

若 $B$ 中有 $a_i,a_j$ ，方案数为 $2^{cnt-3}(cnt-2)$，理由同刚才 $a_i^2$ 的贡献。

若 $B$ 中 $a_i$ 被删了，方案数 $2^{cnt-2}$

所以贡献为 $a_ia_j(2^{cnt-3}(cnt-2)+2^{cnt-2})$ 。

---

计算 $a_i^2$ ，就处理 $s2=\sum a^2\times w$。

计算 $a_ia_j$ ，就处理 $s1=\sum a\times w$，那 $\sum a_ia_j=s1\times s1-s2$ 。

注意要用 long long 存，以及一些不能用 `int*long long` ，要先取模。

Code：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define mod 998244353
struct modint{
    int x;
    modint(int o=0){x=o;}
    modint &operator = (int o){return x=o,*this;}
    modint &operator +=(modint o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint &operator -=(modint o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint &operator *=(modint o){return x=1ll*x*o.x%mod,*this;}
    modint &operator ^=(int b){
    	if(b<0)return x=0,*this;
    	b%=mod-1;
        modint a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint &operator /=(modint o){return *this *=o^=mod-2;}
    modint &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint &operator /=(int o){return *this *= ((modint(o))^=mod-2);}
    template<class I>friend modint operator +(modint a,I b){return a+=b;}
    template<class I>friend modint operator -(modint a,I b){return a-=b;}
    template<class I>friend modint operator *(modint a,I b){return a*=b;}
    template<class I>friend modint operator /(modint a,I b){return a/=b;}
    friend modint operator ^(modint a,int b){return a^=b;}
    friend bool operator ==(modint a,int b){return a.x==b;}
    friend bool operator !=(modint a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint operator - () {return x?mod-x:0;}
};
inline modint qpow(modint a,int b){
	if(b<0)return 0;
	modint res=1;
	for(;b;b>>=1,a*=a)if(b&1)res*=a;
	return res;
}

#define maxn 400005
int n,m;
modint f[maxn];
long long s0[maxn];
modint s1[maxn],s2[maxn];

signed main()
{
	n=read();
	For(i,1,n){
		modint a=read(),w=read();
		int u=a.x;
		m=max(m,u);
		s0[u]=w.x,s1[u]=a*w,s2[u]=a*a*w;
	}
	For(i,1,m)
		for(int j=i*2;j<=m;j+=i)
			s0[i]+=s0[j],s1[i]+=s1[j],s2[i]+=s2[j];
	For(i,1,m)
	{
		long long cnt=s0[i];
		modint B=2;
		if(cnt<=1)continue;
//		cout<<s0[i]<<' '<<s1[i].x<<' '<<s2[i].x<<endl;
		f[i]+=(s1[i]*s1[i]-s2[i])*(qpow(2,cnt-2)+qpow(2,cnt-3)*(cnt%mod-2));
		f[i]+=s2[i]*(qpow(2,cnt-2)*(cnt%mod-1));
	}
	Rep(i,m,1)
		for(int j=i*2;j<=m;j+=i)
			f[i]-=f[j];
	cout<<f[1].x;
    return 0;
}
```

---

## 作者：duyi (赞：5)

# 题解 CF1436F Sum Over Subsets

[题目链接](https://codeforces.com/contest/1436/problem/F)

题目要求 $A$ 集合里数的 $\gcd = 1$。

考虑求出 $g_i$，表示 $\gcd = i$ 的答案。最后输出 $g_1$ 即可。

$\gcd$ 恰好等于 $i$ 不好求。我们可以先求一个 $f_i$，表示 $\gcd$ 是 $i$ 的倍数的答案，即 $f_i = \sum_{i|j}g_j$。然后再容斥回去，或者套用莫比乌斯反演的式子：$g_i = \sum_{i|j}f_j\cdot \mu(\frac{j}{i})$ 就能求出答案了。

依次枚举每个 $i$，考虑求 $f_i$。记所有 $i$ 的倍数组成的可重集为 $S$。则 $f_i = \sum_{B\subset A\subseteq S,|B|=|A|-1}\sum_{x\in A}x\times (\sum_{y\in B}y)$。可以写成：$\sum_{A,B}\sum_{x\in A,y\in B}x\cdot y$。那么我们考虑可重集 $S$ 里任意一对 $x,y$ 对答案的贡献。分两种情况。以下记在 $A$ 中但不在 $B$ 中的数为被踢出的数：

1. $x,y$ 是同一个数。对答案的贡献是 $x^2\times (|S|-1)\times2^{|S|-2}$。这个式子挺妙的。如果按照一般的想法，考虑 $A$ 集合的大小，再从中选出一个数踢出，这就需要枚举集合大小，时间复杂度很高。而现在我们**先选出要踢出的数**（$|S|-1$ 种选法），再让剩下的数随意组成集合（$2^{|S|-2}$ 种方案），就不用枚举集合大小了！
2. $x,y$ 不是同一个数。对答案的贡献是 $x\times y\times((|S|-2)\times2^{|S|-3} + 2^{|S|-2})$。前半部分和上一种情况类似。后面的 $2^{|S|-2}$ 是被踢出的数恰好是 $x$的情况。

记 $\text{freq}(x)$ 表示**数值** $x$ 的出现次数（请注意，这里与输入格式中的定义略有不同）。由于 $\text{freq}$ 高达 $10^9$，$S$ 集合的大小是巨大的。我们不可能真的枚举所有数。所以我们只能枚举**数值**。此时需要进一步讨论：

1. $x,y$ 是同一个数（也就是上述的情况 1）。对答案的贡献是 $x^2 \times(|S|-1)\times2^{|S|-2}$。
2. $x,y$ 是数值相等的**两个数**。对答案的贡献是 $x^2\times((|S| - 2)\times2^{|S|-3}+2^{|S|-2})\times \text{freq}(x)\times(\text{freq}(x)-1)$。
3. $x,y$ 是数值不相等的两个数。对答案的贡献是 $x\times y\times((|S| - 2)\times2^{|S|-3}+2^{|S|-2})\times \text{freq}(x)\times\text{freq}(y)$。但是这里我们不能真的枚举两个数值。可以先预处理出集合 $S$ 里所有数值的 $x\times\text{freq}(x)$ 之和，记为 $\text{sum}$。这样只要枚举 $y$，对 $f_i$ 的贡献就是 $y\times\text{freq}(y)\times(\text{sum}-y\times\text{freq}(y))\times((|S| - 2)\times2^{|S|-3}+2^{|S|-2})$。

于是我们对于每个 $i$，只需要枚举所有数值。即 $i,2i,3i,\dots$。时间复杂度是调和级数，即 $O(n\log n)$。

参考代码：

```cpp
// problem: CF1436F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;
const int MOD = 998244353;
inline int mod1(int x) { return x < MOD ? x : x - MOD; }
inline int mod2(int x) { return x < 0 ? x + MOD : x; }
inline void add(int &x, int y) { x = mod1(x + y); }
inline void sub(int &x, int y) { x = mod2(x - y); }
inline int pow_mod(int x, int i) {
	int y = 1;
	while (i) {
		if (i & 1) y = (ll)y * x % MOD;
		x = (ll)x * x % MOD;
		i >>= 1;
	}
	return y;
}

int p[MAXN + 5], cnt_p, mu[MAXN + 5];
bool v[MAXN + 5];
void sieve(int lim = MAXN) {
	mu[1] = 1;
	for (int i = 2; i <= lim; ++i) {
		if (!v[i]) {
			p[++cnt_p] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= cnt_p && p[j] * i <= lim; ++j) {
			v[i * p[j]] = 1;
			if (i % p[j] == 0) {
				break;
			}
			mu[i * p[j]] = -mu[i];
		}
	}
}
int n, m, freq[MAXN + 5];
int f[MAXN + 5];
int main() {
	sieve(n = MAXN);
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		int a;
		cin >> a;
		cin >> freq[a];
	}
	for (int i = 1; i <= n; ++i) {
		ll tot = 0;
		for (int j = i; j <= n; j += i) {
			tot += freq[j];
		}
		if (tot < 2) continue;
		int w2, w3;
		w3 = pow_mod(2, (tot - 2) % (MOD - 1));
		w2 = (ll)(tot - 1) % MOD * w3 % MOD;
		if (tot >= 3) w3 = ((ll)w3 + (ll)(tot - 2) % MOD * pow_mod(2, (tot - 3) % (MOD - 1))) % MOD;
		
		for (int j = i; j <= n; j += i) if (freq[j]) {
			f[i] = ((ll)f[i] + (ll)j * j % MOD * w2 % MOD * freq[j]) % MOD;
			if (freq[j] >= 2) {
				f[i] = ((ll)f[i] + (ll)j * j % MOD * w3 % MOD * freq[j] % MOD * (freq[j] - 1)) % MOD;
			}
		}
		/*
		for (int j = i; j <= n; j += i) if (freq[j]) {
			for (int k = i; k <= n; k += i) if (k != j && freq[k]) {
				f[i] = ((ll)f[i] + (ll)j * k % MOD * w3 % MOD * freq[j] % MOD * freq[k]) % MOD;
			}
		}
		*/
		int sum = 0;
		for (int j = i; j <= n; j += i) if (freq[j]) {
			sum = ((ll)sum + (ll)j * freq[j]) % MOD;
		}
		for (int j = i; j <= n; j += i) if (freq[j]) {
			int cur = mod2(sum - (ll)j * freq[j] % MOD);
			f[i] = ((ll)f[i] + (ll)j * freq[j] % MOD * cur % MOD * w3) % MOD;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (mu[i] == 1)
			add(ans, f[i]);
		if (mu[i] == -1)
			sub(ans, f[i]);
	}
	cout << ans << endl;
	return 0;
}
```





---

## 作者：FZzzz (赞：4)

~~按惯例写题解之前讲废话。~~

上个星期本来说打打 div2 复健一下，结果熬夜写演讲稿，所以就没打。

~~然后演讲还不搞了，日。~~

然后第二天云了一下题，发现竟然~~全是水题~~是上分场，我为什么没打啊日。

~~某神仙切了五个题 fst 了一个结果从 2000 出头直接 2100+，我要是打了 AK 了是不是就一场 IM 了（（~~

------------
废话结束开始做题。

首先你要知道这题对子集的定义非常神奇因为他是可重集，然后选了不同值相等的元素是会算不同的集合的。比方说 $\{1,1,1,1,1\}$ 就有 $10$ 个形如 $\{1,1,1\}$ 的子集，然后 $\{1,1,1\}$ 有 $3$ 个形如 $\{1,1\}$ 的子集，所以说样例三中 $A=\{1,1,1\}$，B=$\{1,1\}$ 的贡献就会被算 $30$ 遍。~~这个其实你可以通过手玩样例三玩出来。~~

~~如果元素都相等的可重集只算一遍贡献怎么做啊，有没有神仙教育我一下。~~

然后我们就可以开始做题了。首先你可以发现这个 $B$ 是假的，你直接算 $A$ 对答案的贡献，这个大概就是枚举一下哪个元素不在 $B$ 中，然后就可以得出贡献是 $(|A|-1)(\sum\limits_{x\in A}x)^2$。

发现这里有一个 gcd 为 $1$ 的条件，作为一个经验丰富的选手你直接把它换成 $\sum\limits_{\forall x\in A,d|x}\mu(d)$，然后 $d$ 丢到前面去枚举，对于每个数我们直接总复杂度 1log 枚举他的倍数计算答案然后乘上容斥系数 $\mu$，恭喜你去掉了这个限制。于是我们直接考虑怎么样在没有限制的情况下算这个题。

这个平方看起来很蛋疼，所以我们大胆一点直接把它拆开，直接算平方项的贡献和两个数乘起来的贡献。平方项的贡献直接算，两个数之积的贡献分为两个不等数和两个相等数，相等数直接算，不等数从前往后扫的时候维护一下你扫过的所有数的和。每一类贡献都需要我们算包含固定一些数的所有集合大小减一的和，推起来比较简单的方法就是用期望去乘数量。最后的式子就懒得写了~~应该没有人不会推这个吧~~。

因为有快速幂所有实际上大概是 2log，实现一波交上去你会发现在你的电脑上秒出答案的代码在号称神机的 cf 上直接 T 样例。于是你开始优化。首先你直接把 $\mu$ 值为零的数不考虑然后你会发现效果拔群，直接多跑了几十个点，然而并没有什么卵用。所以你一怒之下直接以 $2$ 为底做了一个[光速幂](https://loj.ac/problem/162)，然后就过了，然后就没有然后了。

最后的复杂度有一个应该比较松的上界是 $O(\sqrt{mod}+n\log n)$（实际上可以把根号换成任意多项式？）。还不懂看代码吧。
```cpp
#include<vector>
#include<cstdio>
#include<cctype>
using namespace std;
inline int readint(){
	int x=0;
	char c=getchar();
	bool f=0;
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxm=1e5+5;
int c[maxm];
typedef long long ll;
const ll mod=998244353;
const int S=4e4;
ll pw1[maxm],pw2[maxm];
ll ksm(ll b){
	b=(b%(mod-1)+mod-1)%(mod-1);
	return pw1[b%S]*pw2[b/S]%mod;
}
int mf[maxm];
vector<int> p;
ll mu[maxm];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	for(int i=2;i<maxm;i++){
		if(!mf[i]) p.push_back(i);
		for(int j=0;j<(int)p.size()&&1ll*i*p[j]<maxm;j++){
			mf[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	}
	mu[1]=1;
	for(int i=2;i<maxm;i++)
		if(!mf[i]) mu[i]=mod-1;
		else{
			if(i/mf[i]%mf[i]==0) mu[i]=0;
			else mu[i]=mu[mf[i]]*mu[i/mf[i]]%mod;
		}
	pw1[0]=pw2[0]=1;
	for(int i=1;i<=S;i++) pw1[i]=pw1[i-1]*2%mod;
	for(int i=1;i<=S;i++) pw2[i]=pw2[i-1]*pw1[S]%mod;
	int m=readint();
	while(m--){
		int a=readint();
		c[a]=readint();
	}
	ll ans=0;
	for(int i=1;i<maxm;i++) if(mu[i]){
		ll tot=0;
		for(int j=i;j<maxm;j+=i) tot+=c[j];
		ll res=0,s=0;
		for(int j=i;j<maxm;j+=i){
			res=(res+(tot-1+mod)%mod*ksm(tot-2)%mod*j%mod*j%mod*c[j]%mod)%mod;
			res=(res+tot%mod*ksm(tot-2)%mod*j%mod*s%mod*c[j]%mod)%mod;
			res=(res+tot%mod*ksm(tot-3)%mod*j%mod*j%mod*c[j]%mod*(c[j]-1)%mod)%mod;
			s=(s+1ll*j*c[j]%mod)%mod;
		}
		ans=(ans+res*mu[i]%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Saliеri (赞：2)

莫名其妙的新做法。$O(n\log\log n)$。目前是 rk1（并且还写豪放了）。

___

记 $S(A)$ 为 $A$ 中元素的和。

首先将问题转化为 $\sum_{\gcd(A)=1,A\subseteq T}(|A|-1)S^2(A)$，莫比乌斯反演去掉 $\gcd$ 的限制。筛出 $\mu$ 后最后 $O(n)$ 即可得答案。

考虑 $f_d = \sum_{A,\forall a\in A,d|a} (|A|-1)S^2(A)$。**我们不考虑贡献**，考虑 Dirichlet 后缀和。现在问题是，合并两个集合，快速维护 $f$ 值。

众所周知地，多项式可以通过记下低次项实现递推。考虑维护当前 $f$ 对应的子集的集合信息。

具体的，记下 $\sum_A 1,\sum_A S(A),\sum_A S^2(A),\sum_{A} |A|,\sum_{A} |A|S(A),\sum_A |A|S^2(A)$ 即可。转移篇幅过长，具体见下方代码。

对于每一个权值初始化 $f$ 时，我实现的是暴力龟速乘。这导致复杂度退化成了 $O(n\log n)$。当然，也可以通过组合恒等式 + 光速幂达到完美的 $O(n\log\log n)$。但是我懒了。

代码：

```cpp
//No More Time, No More Chance.
#include <cstdio>
namespace KamiyamaShiki{
	const int N = 1e5,maxn = 1e5+5,mod = 998244353;
	int vis[maxn],pr[maxn],mu[maxn],prcnt;
	void Sieve(){
		mu[1] = 1;
		for(int i=2;i<=N;++i){
			if(!vis[i])pr[++prcnt] = i,mu[i] = mod-1;
			for(int j=1;j<=prcnt&&i*pr[j]<=N;++j){
				vis[i*pr[j]] = 1;
				if(i%pr[j] == 0){mu[i*pr[j]] = 0;break;}
				mu[i*pr[j]] = mod-mu[i];
			}
		}
	}
	int n,buc[maxn];
	struct Sta{
		int s0,s1,s2,S0,S1,S2;
		Sta(){s0=1,s1=s2=S0=S1=S2=0;}
		Sta(int x){s0 = 2,s1 = x,s2 = 1ll*x*x%mod,S0 = 1,S1 = x,S2 = 1ll*x*x%mod;}
	}f[maxn];
	Sta operator +(Sta A,Sta B){
		Sta ret;
		ret.s0 = 1ll*A.s0*B.s0%mod;
		ret.s1 = (1ll*A.s0*B.s1+1ll*A.s1*B.s0)%mod;
		ret.s2 = (1ll*A.s0*B.s2+2ll*A.s1*B.s1+1ll*A.s2*B.s0)%mod;
		ret.S0 = (1ll*A.s0*B.S0+1ll*A.S0*B.s0)%mod;
		ret.S1 = (1ll*A.S1*B.s0+1ll*A.s0*B.S1+1ll*A.S0*B.s1+1ll*A.s1*B.S0)%mod;
		ret.S2 = (1ll*A.S2*B.s0+1ll*A.s0*B.S2+2ll*A.S1*B.s1+2ll*A.s1*B.S1+1ll*A.s2*B.S0+1ll*A.S0*B.s2)%mod;
		return ret;
	}
	Sta Ksm(int a,int x){
		Sta ans,bas(a);
		while(x){
			if(x&1)ans = ans+bas;
			bas = bas+bas,x >>= 1;
		}return ans;
	}
	//³£Êý·ÉÌì¡£ 
	int main(){
		Sieve();
		scanf("%d",&n);for(int i=1,x,y;i<=n;++i)scanf("%d %d",&x,&y),buc[x] = y;
		for(int i=1;i<=N;++i)f[i] = Ksm(i,buc[i]);
		for(int i=1;i<=prcnt;++i)
			for(int j=N/pr[i];j;--j)
				f[j] = f[j]+f[j*pr[i]];
		int ans = 0;
		for(int i=1;i<=N;++i)ans = (ans+1ll*mu[i]*(f[i].S2-f[i].s2+mod))%mod;
		return printf("%d\n",ans),0;
	}
}
int main(){return KamiyamaShiki::main();}
```

---

## 作者：masterhuang (赞：1)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)，第 $13$ 题。

前置芝士：狄利克雷和，建议到[我的博客](https://www.cnblogs.com/HaHeHyt/p/17185823.html)或[这里](https://blog.csdn.net/weixin_45697774/article/details/111052242)学习。 
  
这篇题解是对 $O(n\log\log n)$ 的做法的详细说明，参考了 **Salieri** 大佬的思路。是目前最优复杂度，且跑洛谷 **rk1**。**下面默认所有集合为可重集**。
  
记 $s(A)=\sum\limits_{x\in A} x,\gcd(A)=\gcd\limits_{x\in A}x$，记 $A$ 中的元素分别为 $A_1,A_2,\dots A_{|A|}$，$V$ 为所有数的最大值（值域），$S_d=\{x\mid x\in S,d\mid x\}$，即表示 $S$ 中 $d$ 的倍数构成的集合，$T_d$ 表示 $S$ 中所有等于 $d$ 的元素构成的可重集，有 $T_x\cap T_y(x\neq y)=\varnothing$。
  
$$\sum\limits_{\substack{A,B\subset S\\|B|=|A|-1\\\gcd(A)=1}} s(A)s(B)=\sum\limits_{A\subset S}s(A)^2(|A|-1)[\gcd(A)=1]$$
  
将 $[\gcd(A)=1]$ 莫反：

$$
\begin{aligned}
&\sum\limits_{A\subset S}s(A)^2(|A|-1)[\gcd(A)=1]\\=&\sum\limits_{A\subset S}s(A)^2(|A|-1)\sum\limits_{d\mid\gcd(A)}\mu(d)\\=&\sum\limits_{A\subset S}s(A)^2(|A|-1)\sum\limits_{d\mid A_1,d\mid A_2,\dots d\mid A_{|A|}}\mu(d)\\=&\sum\limits_{d=1}^V\mu(d)\sum\limits_{A\subset S_d} s(A)^2(|A|-1)
\end{aligned}
$$
  
我们只需快速计算 $f(d)=\sum\limits_{A\subset S_d} s(A)^2(|A|-1)$ 即可。我们注意到有 $S_x=\bigcup\limits_{x\mid d} T_d$，这让我们想到了狄利克雷后缀和。

现在问题是，合并两个集合，快速维护 $f$ 值。
  
注意到 $s(A)^2(|A|-1)$ 这种低次式子很能递推。具体来说：
  
记 $temp(A)=(a_1,a_2,a_3,a_4,a_5,a_6)=\left(\sum\limits_{A\subset AA} 1,\sum\limits_{A\subset AA} s(A),\sum\limits_{A\subset AA} s(A)^2,\sum\limits_{A\subset AA} |A|,\sum\limits_{A\subset AA} |A|s(A),\sum\limits_{A\subset AA} |A|s(A)^2 \right)$，类似定义 $b$。
  
令 $CC=AA\cup BB$，类似定义 $c$，我们需要快速合并出 $c$。
  
$$
\begin{aligned}
c_1&=\sum\limits_{A\subset AA\cup BB} 1=\sum\limits_{A1\subset AA,A_2\subset BB} 1=a_1b_1\\
c_2&=\sum\limits_{A1\subset AA,A_2\subset BB} s(A1)+s(A2)=\sum\limits_{A\subset AA} s(A)\sum\limits_{B\subset BB}1+\sum\limits_{A\subset AA} |1|\sum\limits_{B\subset BB}s(B)=a_2b_1+a_1b_2\\
c_3&=\sum\limits_{A1\subset AA,A_2\subset BB} (s(A1)+s(A2))^2=\sum\limits_{A\subset AA} |A|^2\sum\limits_{B\subset BB}1+\sum\limits_{A\subset AA} |1|\sum\limits_{B\subset BB}|B|^2+2\sum\limits_{A1\subset AA}\sum\limits_{,A_2\subset BB} s(A1)s(B2)=a_3b_1+a_1b_3+2b_2a_2
\\
c_4&=\sum\limits_{A\subset AA} |A|\sum\limits_{B\subset BB}1+\sum\limits_{A\subset AA} |1|\sum\limits_{B\subset BB}|B|=a_4b_1+a_1b_4\\
c_5&=\sum\limits_{A1\subset AA,A_2\subset BB}  (|A1|+|B1|)(s(A1)+s(B1))=a_5b_1+b_5a_1+a_4b_2+b_4a_2\\
c_6&=\sum\limits_{A1\subset AA,A_2\subset BB}  (|A1|+|B1|)(s(A1)^2+s(B1)^2+2s(A1)s(B1))=a_6b_1+a_1b_6+a_4b_3+a_3b_4+2(a_5b_2+a_2b_5)
\end{aligned}
$$

合并信息代码：
```cpp
struct node{int a,b,c,d,e,f;}a[N];
inline node operator+(node X,node Y)
{
	return {1ll*X.a*Y.a%mod,(1ll*X.a*Y.b+1ll*X.b*Y.a)%mod,(1ll*X.a*Y.c+1ll*X.c*Y.a+2ll*X.b*Y.b)%mod,
	(1ll*X.d*Y.a+1ll*X.a*Y.d)%mod,(1ll*X.e*Y.a+1ll*X.a*Y.e+1ll*X.b*Y.d+1ll*X.d*Y.b)%mod,
	(1ll*X.a*Y.f+1ll*X.f*Y.a+1ll*X.d*Y.c+1ll*X.c*Y.d+2ll*X.e*Y.b+2ll*X.b*Y.e)%mod};
}
inline void operator+=(node &X,node Y){X=X+Y;}
```
  
初始时我们在 $w_i$ 放上 $temp(T_i)$ 的标记，而后对 $w$ 做狄利克雷后缀和，其中加法变成信息的合并即可。答案中的 $f(d)$ 即为 $w_{i,6}-w_{i,3}$。抛去初始化复杂度为 $O(n\log\log n)$。
  
---  
前置芝士 1：[光速幂](https://www.cnblogs.com/Acestar/p/14423329.html)。
  
前置芝士 2：

$$
\begin{aligned}
f_0(y)&=\sum\limits_{i=0}^y\dbinom{y}{i}=2^y\\
f_1(y)&=\sum\limits_{i=0}^y\dbinom{y}{i}i=\sum\limits_{i=1}^y\dfrac{y}{i}\dbinom{y-1}{i-1}i=y\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}=y2^{y-1}\\
f_2(y)&=\sum\limits_{i=0}^y\dbinom{y}{i}i^2=y\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}(i+1)=y\left(\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}i+\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}\right)=y(f_1(y-1)+2^{y-1})\\
f_3(y)&=\sum\limits_{i=0}^y\dbinom{y}{i}i^3=y\left(\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}i^2+2\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}i+\sum\limits_{i=0}^{y-1}\dbinom{y-1}{i}\right)=y(f_2(y-1)+2f_1(y-1)+2^{y-2})
\end{aligned}
$$
  
接下来考虑如何亚 $O(n\log n)$ 初始化。设初始有 $y$ 个 $x$ 构成的集合 $T_x$，考虑计算此时的标记 $temp$。
  
此时光速幂预处理 $2$ 的幂次即可。注意 $f_2$ 要特判 $y=1$，$f_3$ 要特判 $y=1,2$。
  
有：$temp=(f_0(y),xf_1(y),x^2f_2(y),f_1(y),xf_2(y),x^2f_3(y))$。
  
注意没出现的数也要初始化，此时 $temp=(1,0,0,0,0,0)$。由于光速幂这样是线性的。
  
于是总复杂度为 $O(n\log\log n)$。

代码：  
```cpp
//洛谷 CF1436F
//https://www.luogu.com.cn/problem/CF1436F
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e5+5,M=4e4,mod=998244353;
int n,pr[N],mu[N],v[N],V[N],p2[N],P2[N],cnt,ans;
struct node{int a,b,c,d,e,f;}a[N];
inline node operator+(node X,node Y)
{
	return {1ll*X.a*Y.a%mod,(1ll*X.a*Y.b+1ll*X.b*Y.a)%mod,(1ll*X.a*Y.c+1ll*X.c*Y.a+2ll*X.b*Y.b)%mod,
	(1ll*X.d*Y.a+1ll*X.a*Y.d)%mod,(1ll*X.e*Y.a+1ll*X.a*Y.e+1ll*X.b*Y.d+1ll*X.d*Y.b)%mod,
	(1ll*X.a*Y.f+1ll*X.f*Y.a+1ll*X.d*Y.c+1ll*X.c*Y.d+2ll*X.e*Y.b+2ll*X.b*Y.e)%mod};
}
inline void operator+=(node &X,node Y){X=X+Y;}
inline void ad(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
#define md(x) (((x)>=mod)?(x)-mod:(x))
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline void init(int M)
{
	for(int i=2;i<=M;i++)
	{
		if(!v[i]) pr[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pr[j]<=M;j++)
		{
			v[i*pr[j]]=1;
			if(i%pr[j]==0){mu[i*pr[j]]=0;break;}mu[i*pr[j]]=-mu[i];
		}
	}mu[1]=1;
}
inline void FGT(node *a,int n){for(int i=1;i<=cnt;i++) for(int j=n/pr[i];j>=1;j--) a[j]+=a[pr[i]*j];}
#define pow2(x) (1ll*P2[(x)/M]*p2[(x)%M]%mod)
#define f1(y) (pow2(y-1)*(y)%mod)
#define f2(y) ((y==1)?1ll:(pow2(y-2)*(y-1)+pow2(y-1))%mod*(y)%mod)
#define f3(y) ((y==1)?1ll:((y==2)?10ll:(f2(y-1)+pow2(y-1)+2ll*f1(y-1))*(y)%mod))
#define Node(x,y) {pow2(y),1ll*x*f1(y)%mod,f2(y)*x%mod*x%mod,f1(y),f2(y)*x%mod,f3(y)*x%mod*x%mod}
int main()
{
	for(int i=p2[0]=1;i<=M;i++) p2[i]=md(p2[i-1]<<1);
	for(int i=P2[0]=1;i<=M;i++) P2[i]=1ll*P2[i-1]*p2[M]%mod;
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;int mx=0; 
	for(int i=1,x,y;i<=n;i++) cin>>x>>y,a[x]=Node(x,y),V[x]=1,mx=max(mx,x);init(mx);
	for(int i=1;i<=mx;i++) if(!V[i]) a[i]=Node(i,0);
	FGT(a,mx);for(int i=1;i<=mx;i++) ad(ans,md(mu[i]*md(a[i].f-a[i].c+mod)+mod));cout<<ans;
	return 0;
}
```

---

## 作者：FjswYuzu (赞：1)

令 $f(d)$ 为在满足条件 $1,2$ 并且 $A$ 中的所有元素最大公约数为 $d$ 的答案。令 $g(d) = \sum_{d|n} f(n)$，发现在知道 $g$ 的情况下可以 $O(n \ln n)$ 算出 $f(n)$，于是考虑计算 $g(n)$。

假设选出了集合 $A$，这个集合 $A$（假设其内部所有元素的最大公约数为 $d$）对 $g(d),g(2d),\cdots$ 的贡献为：

$$
\begin{aligned}
\left(\sum_{x\in A} x\right)\left(\sum_{x\in B} x\right)
\end{aligned}
$$


发现我们可以将其看成 $A$ 中的一个元素乘上可能的 $|A|$ 个 $B$ 中的所有元素。考虑枚举 $A$ 中的元素造成贡献：

- 如果两个元素 $x,y$ 一样：那么我们在剩下 $|A|-1$ 个元素中选择一个删除，并且在剩下 $|A|-2$ 个元素中存在要或者不要两种选项，因此贡献为：$x^2(|A|-1)2^{|A|-2}$；   
- 如果两个元素 $x,y$ 不同：
  - 如果 $x,y$ 同时存在于 $B$：在剩下 $|A|-2$ 个元素中选择一个删除，并且在剩下 $|A|-3$ 个元素中存在要或者不要两种选项，因此贡献为：$xy(|A|-2)2^{|A|-3}$；   
  - 否则，假设 $y$ 不存在于 $B$：在剩下 $|A|-2$ 个元素中中存在要或者不要两种选项，因此贡献为：$xy(|A|-2)2^{|A|-3}$。
  
注意到我们想快速处理这个 $xy$ 和 $x^2$。$x^2$ 是很好处理的，但是 $xy$ 不好处理。注意到 $\left(\sum_{x\in A} x\right)\left(\sum_{x\in A} x\right)- \left(\sum_{x\in A} x^2\right)$ 就是这个东西，于是预处理下面三个东西（其中 $p(d)$ 表示 $d$ 在集合内的数量）：

1. $s_0(d)=  \sum_{d|n} p(d)$；   
2. $s_1(d)=  \sum_{d|n} p(d)d$；   
3. $s_2(d)=  \sum_{d|n} p(d)d$。    

就可以解决上面的问题。同时可以发现 $s_1(d)^2-s_2(d)$ 就排除了两个相同元素相乘。

有一些代码细节，就 $s_0(d)$ 不能取模（因为有幂运算），$s_1(d),s_2(d)$ 必须取模。

最后 $O(n \ln n)$ 算一遍就行了。答案是 $f(1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=998244353;
LL sum0[100005],sum1[100005],sum2[100005],f[100005],cnt,maxn,n;
LL QuickPow(LL x,LL p)
{
	if(p<0)	return 0;
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=ans*base%MOD;
		base=base*base%MOD;
		p>>=1;
	}
	return ans;
}
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)
	{
		LL x,v;
		scanf("%lld %lld",&x,&v);
		sum0[x]=v;
		sum1[x]=x*v%MOD;
		sum2[x]=x*x%MOD*v%MOD;
		maxn=max(maxn,x);
	}
	for(LL i=1;i<=maxn;++i)	for(LL j=2;j*i<=maxn;++j)	sum0[i]+=sum0[i*j];
	for(LL i=1;i<=maxn;++i)	for(LL j=2;j*i<=maxn;++j)	(sum1[i]+=sum1[i*j])%=MOD;
	for(LL i=1;i<=maxn;++i)	for(LL j=2;j*i<=maxn;++j)	(sum2[i]+=sum2[i*j])%=MOD;
	for(LL i=1;i<=maxn;++i)
	{
		if(sum0[i]<=1)	continue;
		(f[i]+=((sum0[i]-1+MOD)%MOD*QuickPow(2,(sum0[i]-2))%MOD*sum2[i]%MOD)%MOD)%=MOD;
		(f[i]+=((sum0[i]-2+MOD)%MOD*QuickPow(2,(sum0[i]-3))%MOD*((sum1[i]*sum1[i]%MOD+MOD-sum2[i])%MOD)%MOD+QuickPow(2,(sum0[i]-2))*((sum1[i]*sum1[i]%MOD+MOD-sum2[i])%MOD)))%=MOD;
	}
	for(LL i=maxn;i;--i)	for(LL j=2;j*i<=maxn;++j)	(f[i]+=MOD-f[i*j])%=MOD;
	printf("%lld",f[1]);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

随机跳题看到的。为啥这种小清新送分题考场上只有 $3$ 位正式选手过了？

显然莫比乌斯反演。对于一个合法的 $A$，它对答案的贡献是 $(|A|-1) (\sum_{x \in A} x)^2$。随手展开，得到贡献为 $(|A|-1) \sum_{x \in A} \sum_{y \in A} xy$。

分别计算 $\sum_{A \text{ is legal}} |A| \sum_{x \in A} \sum_{y \in A} xy$ 和 $\sum_{A \text{ is legal}} \sum_{x \in A} \sum_{y \in A} xy$。

对于后者，考虑枚举 $x$ 和 $y$。分为两种情况（假设在这一波反演中，我们钦定了 $cnt$ 个数满足条件）

- $x=y$，此时有 $2^{cnt-1}$ 个集合 $A$ 包含了 $x$。
- $x \neq y$，此时有 $2^{cnt-2}$ 个集合 $A$ 包含了 $x$ 和 $y$。

对于前者，我们用 $\sum_{z \in A} 1$ 来刻画 $|A|$，于是转化为 $\sum_{A \text{ is legal}} \sum_{z \in A} \sum_{x \in A} \sum_{y \in A} xy$。

还是分类：

- 当 $x=y$ 的时候，有一个 $z =x$ 对应了 $2^{cnt-1}$ 个合法的集合 $A$ 包含了 $xyz$，$cnt-1$ 个 $z \neq x$ 对应了 $2^{cnt-2}$ 的集合 $A$ 包含了 $xyz$。
- 当 $x \neq y$ 的时候，有两个 $z = x$ 或 $z = y$ 对应了 $2^{cnt-2}$ 个合法的集合 $A$ 包含了 $xyz$，有 $cnt-2$ 个 $z \neq x$ 且 $z \neq y$ 对应了 $2^{cnt-3}$ 个集合包含了 $xyz$。

复杂度 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=998244353;
int n,cnt[MAXN],mu[MAXN],flg[MAXN];
int qpow(int base,int p) {
	if(p<0) return 0;
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void init(int mx) {
	mu[1]=1; vector<int> pr;
	ffor(i,2,mx) {
		if(!flg[i]) pr.push_back(i),mu[i]=-1;
		for(auto v:pr) {
			if(i*v>mx) break ;
			flg[i*v]=1;
			if(i%v==0) {mu[i*v]=0;break ;}
			mu[i*v]=-mu[i];
		}
	}
	return ;
}
int solve(int u) {
	int tsum=0,tcnt=0,ans=0;
	ffor(i,1,100000/u) tcnt+=cnt[u*i],tsum=(tsum+u*i*cnt[u*i])%MOD;
	if(tcnt==0) return 0; 
	int mul1=0,mul2=0;
	mul1=(qpow(2,tcnt-1)+(tcnt-1)%MOD*qpow(2,tcnt-2))%MOD;
	mul2=(2*qpow(2,tcnt-2)+(tcnt-2)%MOD*qpow(2,tcnt-3))%MOD;
	int pw=qpow(2,tcnt-2),ppw=qpow(2,tcnt-1);
	ffor(i,1,100000/u) {
		int val=u*i;
		if(cnt[val]==0) continue ;
		ans=(ans+(val*val%MOD*mul1%MOD+val*((tsum-val)%MOD)%MOD*mul2%MOD)%MOD*cnt[val])%MOD;
		ans=(ans-(val*val%MOD*ppw%MOD+val*((tsum-val)%MOD)%MOD*pw)%MOD*cnt[val])%MOD;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) {int w,val;cin>>w>>val,cnt[w]=val;}
	init(100000);
	int ans=0;
	ffor(i,1,100000) ans=(ans+mu[i]*solve(i))%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
//狼牙月 伊人憔悴 我举杯 饮尽了风雪
```

---

## 作者：daniEl_lElE (赞：0)

不难发现 $\{B\}$ 其实是无用的，题目本质上就是求所有 $\gcd_{x\in A}x=1$ 的 $(|A|-1)(\sum_{x\in A}x)^2$。

平凡地容斥一下（钦定 $d|\gcd_{x\in A}x$）。要求的是 $\sum_{A\in B}(|A|-1)(\sum_{x\in A}x)^2$，其中 $B$ 为所有 $d|a_i$ 组成的集合。

推个式子。

$$\sum_{A\in B}((|A|-1)(\sum_{x\in A}x^2)+(|A|-1)(\sum_{(x,y)\in A}2xy))$$

$$=\sum_{x\in B}x^2\sum_{x\in A\subset B}(|A|-1)+\sum_{(x,y)\in B}2xy\sum_{(x,y)\in A\subset B}(|A|-1)$$

$$=2^{|B|-2}(|B|-1)\sum_{x\in B}x^2+2^{|B|-3}|B|\sum_{(x,y)\in B}2xy$$

$$=2^{|B|-2}(|B|-1)\sum_{x\in B}x^2+2^{|B|-3}|B|((\sum_{x\in B}x)^2-\sum_{x\in B}x^2)$$

不难发现我们只需要对于每个 $d$ 计算出 $\sum_{d|i}freq_i\times a_i^k$，其中 $k=0,1,2$ 即可求出上式。最后容斥一下即可。

这边的容斥我写的是 $n\ln n$ 的调和级数暴力，实现精细可以做到 $n\log\log n$，反正能过就行。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=998244353;
//Combinatorics
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
//Fast input/output
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
void endl(){
	putchar(10);
}
int pw0[100005],pw1[100005],pw2[100005],ans[100005];
signed main(){
	init();
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		int a,fr; cin>>a>>fr;
		pw0[a]=fr;
		pw1[a]=a*fr%mod;
		pw2[a]=a*a%mod*fr%mod;
	}
	for(int i=1;i<=100000;i++) for(int j=i*2;j<=100000;j+=i) pw0[i]+=pw0[j],(pw1[i]+=pw1[j])%=mod,(pw2[i]+=pw2[j])%=mod;
	for(int i=1;i<=100000;i++) ans[i]=((pw0[i]-1)%mod*qp(2,pw0[i]-2)%mod*pw2[i]%mod+pw0[i]%mod*qp(2,pw0[i]-3)%mod*(pw1[i]*pw1[i]%mod+mod-pw2[i])%mod)%mod;
	for(int i=100000;i>=1;i--) for(int j=i*2;j<=100000;j+=i) (ans[i]+=mod-ans[j])%=mod;
	cout<<ans[1];
	return 0;
}

```

---

## 作者：_quasar_ (赞：0)

十分显然的莫比乌斯反演。

令 $f(d)$ 表示 $\gcd$ 为 $d$ 的方案数，并且令 $g(n)$：
$$
g(n)=\sum_{n|d} f(d)
$$
然后反演一下就有：
$$
f(n)=\sum_{n|d}\mu(\frac{d}{n})g(d)\ ,\ f(1)=\sum_{d\geq 1}\mu(d)g(d)
$$
然后这个数字最大也就 $10^5$ ，因此直接做就好。现在考虑如何求 $g(d)$ ，相当于将 $d$ 的倍数拿出来，然后算集合的贡献。考虑这个集合 $A$ 其实就是：
$$
\left(\sum_{x\in A}x\right)\cdot\left(\left(|A|\sum_{x\in A}x\right)-\left(\sum_{x\in A}x\right)\right)=|A-1|\left(\sum_{x\in A}x\right)^2
$$
后面那一个平方，考虑枚举两个数，然后算集合的贡献。

如果这两个数是不同的（此处的不同为**不同的元素**而非不同的值），那么假设剩下还有 $n$ 个元素，集合的贡献就是：
$$
\sum_{i=0}^{n}{n\choose i}(i+1)=\sum_{i=0}^{n}{n\choose i}i+2^{n}=n2^{n-1}+2^{n}
$$
如果两个数是相同的，也直接按照上式做即可。

注意模数问题。

```cpp
const int N=1e5+5;
int n,m,t[N]; ll _[N];
 
// {{{ Sieve
 
int cnt,vis[N],mui[N],prime[N];
 
inline void sieve(int L=N-5) {
    mui[1]=1;
    lep(i,2,L) {
        if(!vis[i]) prime[++cnt]=i,mui[i]=mod-1;
        for(int j=1;j<=cnt&&i*prime[j]<=L;++j) {
            vis[i*prime[j]]=true;
            if(!(i%prime[j])) {mui[i*prime[j]]=0; break;}
            mui[i*prime[j]]=mod-mui[i];
        }
    }
}
 
// }}}
 
inline int g(int d) {
    int all=0,ans=0,res=0; ll siz=0;
    for(int i=d;i<=m;i+=d) pls(all,mul(i,t[i])),siz+=_[i];
    siz-=2;
 
    res=mul(all,all);
    for(int i=d;i<=m;i+=d) sub(res,mul(t[i],mul(i,i)));
    pls(ans,mul(res,add(modpow(2,siz),mul((siz%mod+mod)%mod,modpow(2,siz-1)))));
 
    res=0;
    for(int i=d;i<=m;i+=d) pls(res,mul(t[i],mul(i,i)));
    pls(ans,mul(res,mul(((siz+1)%mod+mod)%mod,modpow(2,siz))));
 
    return ans;
}
 
int x,y;
int main() {
    sieve();
    IN(n);
    lep(i,1,n) IN(x,y),chkmax(m,x),pls(t[x],y),_[x]+=y;
 
    int f1=0;
    lep(i,1,m) pls(f1,mul(mui[i],g(i)));
    printf("%d\n",f1);
    return 0;
}
```

---

