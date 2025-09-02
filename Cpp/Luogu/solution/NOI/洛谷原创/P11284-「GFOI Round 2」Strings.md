# 「GFOI Round 2」Strings

## 题目描述

给你两个正整数 $n, m$。

我们称一个长度为 $k$ 的正整数序列 $a_1, a_2, \ldots, a_k$ 是好的当且仅当：

- $\forall i \in [1, k], 1 \le a_i \le m$；
- 存在一个正整数 $l \in [1, \frac{k}{3}]$ 满足：$\forall i \in [1, l], a_i = a_{2l + 1 - i}$。

求有多少个长度 $\le n$ 的好的序列，对 $10^9 + 7$ 取模。

## 说明/提示

#### 【样例解释】

对于第一组数据，长度 $\le 3$ 的好的序列有 $[1, 1, 1], [1, 1, 2], [2, 2, 1], [2, 2, 2]$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | $n \le$ | $m \le$ | 子任务依赖 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $10^{18}$ | $1$ | 无 | $1$ |
| $2$ | $10$ | $4$ | 无 | $7$ |
| $3$ | $10^5$ | $10^{18}$ | $2$ | $28$ |
| $4$ | $10^{18}$ | $10^{18}$ | $1, 2, 3$ | $64$ |

对于所有数据，满足：

- $1 \le T \le 10$；
- $3 \le n \le 10^{18}$；
- $1 \le m \le 10^{18}$。

## 样例 #1

### 输入

```
4
3 2
5 3
10 4
100000 998244353123456```

### 输出

```
4
117
430352
967771719```

# 题解

## 作者：vzcx_host (赞：8)

upd on 24/11/22：回味子串没了，修订了一下表述错误。

记录赛时的爆标做法。

考虑设 $f_i$ 为长度为 $i$ 且不存在前缀回文子串的字符串数量，显然可以容斥，其暴力转移式为：
$$f_i=m^i-\sum_{j=1}^{\lfloor i/2\rfloor}f_j m^{i-2j}$$

令 $w=m^{-1},g_i=f_i\times w^{2i}$，有：
$$g_i=w^i(1-\sum_{j=1}^{\lfloor i/2\rfloor}g_j)$$

对于一个可以成为答案字符串，我们选择前缀回文子串中长度最短的串作为枚举对象，可以证明，若一个字符串存在前缀回文子串，其最短的前缀回文子串一定不长于原串的半长。枚举前缀回文子串的半长 $i$，答案式子为：
$$\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}\sum_{j=0}^{n-3i} f_im^{i+j}$$
$$=\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}f_i m^i(\dfrac{m^{n+1-3i}-1}{m-1})$$
$$=\dfrac{m^{n+1}\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}f_iw^{2i}-\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}f_im^i}{m-1}$$
$$=\dfrac{m^{n+1}\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}g_i-\sum_{i=1}^{\lfloor\frac{n}{3}\rfloor}g_im^{3i}}{m-1}$$

令 $v=w^{d+1}$ 考虑计算：
$$A(d,k)=\sum_{i=1}^{k}g_iw^{di}$$
$$=\sum_{i=1}^{k}w^{di}(w^i(1-\sum_{j=1}^{\lfloor i/2\rfloor}g_j))$$
$$=\sum_{i=1}^{k}v^i-\sum_{i=1}^{k}\sum_{j=1}^{\lfloor i/2\rfloor}v^ig_j$$
$$=\sum_{i=1}^{k}v^i-\sum_{j=1}^{\lfloor k/2\rfloor}g_j\sum_{i=2j}^{k}v^i$$
$$=\dfrac{v^{k+1}-v}{v-1}-\dfrac{\sum_{j=1}^{\lfloor k/2\rfloor}g_j(v^{k+1}-v^{2j})}{v-1}$$
$$=\dfrac{v^{k+1}-v}{v-1}-\dfrac{v^{k+1}A(0,\lfloor k/2\rfloor)-A(2d+2,\lfloor k/2\rfloor)}{v-1}$$

递归计算即可，容易证明状态总数是 $O(\log^2 n)$ 的，根据实现的精细程度可以做到 $O(\log^2 n)$ 或 $O(\log^3 n)$。赛时代码为后者。

upd：新增没有细节判断的 $O(\log^2 n)$ 代码，该代码在洛谷上单测试点最慢为 4ms：
```cpp
val[0]=0;
for(int i=1;i<=64;i++)
    val[i]=(val[i-1]*2+2)%(mod-1);
vkc[ln=0]=n/3;
while(vkc[ln]!=1){vkc[ln+1]=vkc[ln]/2;ln++;}
for(int i=0;i<=ln;i++){
    vkg[i]=Pow(w,val[i]+1);
    nkg[i]=Pow(vkg[i]-1,mod-2);
    vd[ln][i]=dp[ln][i]=vkg[i];
}
for(int i=ln-1;i>=0;i--)
    for(int j=0;j<=i;j++){
        vd[i][j]=vd[i+1][j]*vd[i+1][j]%mod;
        if(vkc[i]&1)vd[i][j]=vd[i][j]*vkg[j]%mod;
        vx=vd[i][j]*vkg[j]%mod;
        dp[i][j]=(vx+mod-vkg[j]+mod-(vx*dp[i+1][0]+mod-dp[i+1][j+1])%mod)*nkg[j]%mod;
    }
ans=Pow(m,(n+1)%(mod-1))*dp[0][0]%mod;
now=mod-4;vg=1;
for(int i=0;i<ln;i++){
    v=Pow(w,now+1);vx=Pow(v,vkc[i]+1);vg=vg*Pow(v-1,mod-2)%mod;
    ans+=mod-vg*(vx+mod-v+mod-vx*dp[i+1][0]%mod)%mod;
    now=(now*2+2)%(mod-1);
}
ans+=mod-vg*Pow(w,now+1)%mod;
```

---

## 作者：_lbw_ (赞：4)

本文除法全部下取整。

设 $f_n$ 为长度 $2n$ 最短偶回文前缀为 $n$ 的序列个数。有转移：

$$f_n=m^n-\sum\limits_{i=1}^{n/2}f_im^{n-2i}$$

枚举答案序列最短偶回文前缀 $2l$，答案即为：

$$\sum\limits_{l=1}^{n/3}f_l\sum\limits_{i=3l}^nm^{i-2l}$$

$$=\sum\limits_{l=1}^{n/3}f_lm^{-2l}\sum\limits_{i=3l}^nm^i$$

$$=\sum\limits_{l=1}^{n/3}f_lm^{-2l}\dfrac{m^{3l}-m^{n+1}}{1-m}$$

容易发现答案可以被函数 $S(n,k)=\sum\limits_{l=1}^nf_lm^{kl}$ 表示。

考虑递归计算，使用与对答案类似的处理技巧：

$$S(n,k)=\sum\limits_{l=1}^nf_lm^{kl}$$
$$=\sum\limits_{l=1}^nm^{kl}(m^l-\sum\limits_{i=1}^{l/2}f_im^{l-2i})$$
$$=\sum\limits_{l=1}^nm^{(k+1)l}-\sum\limits_{l=1}^n\sum\limits_{i=1}^{l/2}f_im^{(k+1)l-2i}$$

前面部分可以等比数列求和，后半部分：

$$\sum\limits_{l=1}^n\sum\limits_{i=1}^{l/2}f_im^{(k+1)l-2i}$$

$$=\sum\limits_{i=1}^{n/2}\sum\limits_{l=2i}^nf_im^{(k+1)l-2i}$$

$$=\sum\limits_{i=1}^{n/2}m^{-2i}\sum\limits_{l=2i}^nf_im^{(k+1)l}$$

$$=\sum\limits_{i=1}^{n/2}m^{-2i}\dfrac{m^{2i(k+1)}-m^{(n+1)(k+1)}}{1-m}$$

$$=\dfrac{S(n/2,2k)-m^{(n+1)(k+1)}S(n/2,-2)}{1-m}$$

发现 $S$ 只有 $\dfrac{n}{2^a},\pm2^b$ 位置会被计算到，记忆化之。

时间复杂度 $\mathcal{O}(T\log^2n(\log \textsf{mod}+\log n))$。


```cpp
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<bitset>
#include<cstdio>
#include<random>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
#define IV void
#define her1 20081214
#define cht 1000000007
#define ull unsigned long long
#define mem(x,val) memset(x,val,sizeof x)
#define F(i,j,n)for(register int i=j;i<=n;i++)
#define D(i,j,n)for(register int i=j;i>=n;i--)
#define E(i,now)for(register int i=first[now];i;i=e[i].nxt)
#define FL(i,j,n)for(register i64 i=j;i<=n;i++)
#define DL(i,j,n)for(register i64 i=j;i>=n;i--)
#define EL(i,now)for(register i64 i=first[now];i;i=e[i].nxt)
ll read(){
	ll ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')ans=ans*10+c-'0',c=getchar();
	return ans*f;
}
#undef ll
#include "assert.h"
mt19937_64 rnd(her1);
#include "functional"
using i64 = long long;
i64 qpow(i64 n,i64 base=cht-2){
	base%=(cht-1);n%=cht;
	if(base<0)base+=cht-1;
	i64 ans=1;
	while(base){
		if(base&1)ans=ans*n%cht;
		n=n*n%cht;base>>=1;
	}
	return ans;
}
IV cadd(i64&x,i64 val){x=(x+val)%cht;}
const int maxn = 1e5+5;
i64 n,m;
map<pair<i64,i64>,i64>mp;
i64 S(i64 n,i64 k){
	if(n==1)return qpow(m,k+1);
	if(mp.count({n,k}))return mp[{n,k}];
	i64 Ans=0,pw=qpow(m,k+1);
	if(pw==1)Ans=n;
	else Ans=qpow(pw-1)*(qpow(pw,n+1)-qpow(pw,1))%cht;
	i64 s=(S(n/2,2*k)-S(n/2,-2)*qpow(m,(n%(cht-1)+1)*(k%(cht-1)+1)))%cht;
	s=s*qpow(1-qpow(m,k+1))%cht;
	return mp[{n,k}]=(Ans-s)%cht;
}
IV solve(){
	n=read();m=read();mp.clear();
	if(m==1)return(void)(printf("%lld\n",(n-2)%cht));
	i64 Ans=(S(n/3,1)-S(n/3,-2)*qpow(m,n+1))%cht;
	printf("%lld\n",(Ans*qpow(1-m)%cht+cht)%cht);
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	i64 T=read();while(T--)solve();return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

设 $f_i$ 为存在一个偶回文前缀的序列个数。有转移：
$$
f_i = \begin{cases} f_{i - 1} \times m & i \bmod 2 = 1 \\ f_{i - 1} \times m + m^{\frac{i}{2}} - f_{\frac{i}{2}} & i \bmod 2 = 0 \end{cases}
$$
答案即为
$$
\sum\limits_{i = 1}^n f_{2 \left\lfloor\frac{i}{3}\right\rfloor} m^{i - 2 \left\lfloor\frac{i}{3}\right\rfloor}
$$
可以用 [CF1864H 第一篇题解的做法](https://www.luogu.com.cn/problem/solution/CF1864H) 在 $O(\log^4 n)$ 时间内求出单个 $f_n$，大概就是矩阵维护 $f_{\left\lfloor\frac{i}{2^k}\right\rfloor}$ 和 $m^{\left\lfloor\frac{i}{2^k}\right\rfloor}$ 的转移。

考虑如何求答案式子。枚举 $2 \left\lfloor\frac{i}{3}\right\rfloor$，相当于要求一个类似于 $\sum\limits_{i = 1}^N [i \bmod 2 = 0] f_i (m^{\frac{i}{2}} + m^{\frac{i}{2} + 1} + m^{\frac{i}{2} + 2})$ 的东西。提出 $1 + m + m^2$ 后变成 $\sum\limits_{i = 1}^N [i \bmod 2 = 0] f_i m^{\frac{i}{2}} = m^{\frac{N}{2}} \sum f_i (m^{-1})^{\frac{N}{2} - \frac{i}{2}}$。这玩意可以用一个变量 $ans$ 维护，当 $i \bmod 2 = 0$ 时让 $ans \gets m^{-1} ans + f_i$ 即可。

时间复杂度 $O(T \log^4 n)$。


```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef __uint128_t u128;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 122;
const ll mod = 1000000007;

inline ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

ll n, m;
struct mat {
	ll a[maxn][maxn];
	mat() {
		mems(a, 0);
	}
} F[maxn], G[maxn], H[maxn];

inline mat operator * (const mat &a, const mat &b) {
	mat res;
	for (int i = 0; i < maxn; ++i) {
		for (int j = 0; j < maxn; ++j) {
			u128 x = 0;
			for (int k = 0; k < maxn; ++k) {
				x += a.a[i][k] * b.a[k][j];
			}
			res.a[i][j] = x % mod;
		}
	}
	return res;
}

struct vec {
	ll a[maxn];
	vec() {
		mems(a, 0);
	}
};

inline vec operator * (const vec &a, const mat &b) {
	vec res;
	for (int i = 0; i < maxn; ++i) {
		for (int j = 0; j < maxn; ++j) {
			res.a[j] = (res.a[j] + a.a[i] * b.a[i][j]) % mod;
		}
	}
	return res;
}

inline ll calc(ll n) {
	vec ans;
	for (int i = 60; i < 120; ++i) {
		ans.a[i] = 1;
	}
	for (int i = 59; ~i; --i) {
		if (n & (1LL << i)) {
			ans = ans * G[i];
		}
	}
	return ans.a[0];
}

void solve() {
	scanf("%lld%lld", &n, &m);
	m %= mod;
	if (!m) {
		puts("0");
		return;
	}
	ll im = qpow(m, mod - 2);
	for (int l = 0; l < 60; ++l) {
		F[l] = mat();
		for (int i = 0; i <= 120; ++i) {
			F[l].a[i][i] = 1;
		}
		for (int i = 0; i <= l; ++i) {
			if (i < l) {
				F[l].a[i + 60][i + 60] = m;
			}
			for (int j = i; j < l; ++j) {
				F[l].a[j][i] = F[l].a[j + 60][i] = m * (((j - i) & 1) ? mod - 1 : 1) % mod;
			}
			F[l].a[l][i] = m * (((l - i) & 1) ? mod - 1 : 1) % mod;
		}
	}
	F[0].a[0][120] = 1;
	F[0].a[120][120] = im;
	G[0] = H[0] = F[0];
	for (int i = 1; i < 60; ++i) {
		G[i] = H[i - 1] * F[i];
		H[i] = G[i] * H[i - 1];
	}
	ll t = (n / 3 - 1) * 2 + 1, ans = 0;
	vec A;
	for (int i = 60; i < 120; ++i) {
		A.a[i] = 1;
	}
	for (int i = 59; ~i; --i) {
		if (t & (1LL << i)) {
			A = A * G[i];
		}
	}
	ans = (ans + A.a[120] * qpow(m, t / 2) % mod * (1 + m + m * m % mod)) % mod;
	t = calc(n / 3 * 2);
	for (ll i = n / 3 * 3; i <= n; ++i) {
		ans = (ans + t * qpow(m, i - i / 3 * 2)) % mod;
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

