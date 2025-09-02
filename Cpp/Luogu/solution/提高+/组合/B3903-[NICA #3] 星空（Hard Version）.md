# [NICA #3] 星空（Hard Version）

## 题目背景

**Easy Version 和 Hard Version 差别在于数据范围。**

## 题目描述

小 R 有一个长度为 $n$ 的序列 $a$，保证序列中的每个数都是 $2$ 的整数次幂。

小 M 有一个数 $x$，她希望重新排列序列 $a$，使得不存在一个 $i\in[1,n)$ 满足 $a_i+a_{i+1}>x$。重排的方式为：选择一个 $1\sim n$ 的排列 $p$，然后令新序列 $a'$ 满足 $a'_i=a_{p_i}$。$a'$ 即为重排后的序列。

现在你想要知道有多少种重排的方式能满足小 M 的要求。两种重排方式不同当且仅当选择的排列 $p$ 不同。

## 说明/提示

数据保证，$2 \leq n \leq 10^5$，$1 \leq a_i \leq 2^{60}$，$1 \leq x < 2^{63}$。

## 样例 #1

### 输入

```
6 46
4 8 8 16 32 32```

### 输出

```
144```

# 题解

## 作者：GTAH2333 (赞：5)

提供一种支持多次询问的方法。

观察题目，发现可以一定可以将序列 $x$ 中的元素分成四类：黑球、灰球、白球和不可存在球。其中黑球是和灰球或黑球的数相加都大于 $x$ 的数，灰球是只与黑球相加大于 $x$ 的数，白球则与任何数相加都小于等于 $x$ ， 而不可存在球则是自身便大于等于 $x$ 的数。
 
可以这样分类的正确性显然可以证明：首先，题目要求 $a_i$ 一定是二的整数次幂，则可以将等于 $x$ 的二进制最高位的数作为黑球，然后将与黑球相加大于 $x$ 且不等于黑球的作为灰球，余下作白球。由于二的整数次幂的要求，白球一定小于等于灰球的一半，灰球一定小于等于黑球的一半，而黑球一定小于等于 $x$ ，则可以满足要求。若序列中有一个数大于等于 $x$ ，显然无解，因为无论是什么数排列在它旁边都不符合要求，特判设有即可。

现在我们将这个问题转化为一个排列问题。可设黑球个数为 $k_1$ ，灰球个数为 $k_2$ ，白球个数为 $k_3$ ，且要求黑黑不相邻，可得出如下公式：  

 $$A_{k_3}^{k_3}\times A_{k_3+1}^{k_1}\times \prod \limits ^{k_3+k_2-k_1}_{i=k_3-k_1+1} i$$

公式的意义：将白球有序排列后，将 $k_1$ 黑球放入 $k_3+1$ 个空并且两个球不在同一个空，在剩下的 $k_3-k_1+1$ 个空中依次放入灰球，而每放入一个灰球，空的个数就会加一，所以是连乘。
 
再特判一些特殊情况，即可正确求出答案。

code：
```cpp
#include<iostream>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
inline int qpow(int a,int b) {
	int res = 1;
	while(b) {
		if(b&1) res = (1ll*a*res)%mod;
		a = (1ll*a*a)%mod;
		b>>=1;
	} 
	return res;
}
int n, k1, k2, k3;
int jc[N] = {1,1}, inv[N] = {1,1};
unsigned long long x1, val, x, a[N];
int main() {
	n = read(), x = readULL(), x1 = x>>1;
	for(int i=1;i<=n;++i) {
		a[i] = readULL(), jc[i+1] = (1ll * (i+1) * jc[i]) % mod;
		if(a[i] > x) { cout<<0; return 0; }
		else if(a[i] > x1) ++k1, val = a[i];
	}
	inv[n+1] = qpow(jc[n+1], mod-2), x -= val;
	for(int i=n;i>=1;--i) {
		inv[i] = 1ll * inv[i+1] * (i+1) % mod;
		if(a[i] > x && a[i] != val) ++k2;
		else if(a[i] <= x) ++k3;
	}
	if(k1>k3+1) cout << 0;
	else if(k2 == 0) cout << 1ll * jc[k3] * jc[k3+1] % mod * inv[k3+1-k1] % mod;
	else cout << 1ll * jc[k3] * jc[k3+1] % mod * inv[k3+1-k1] % mod * jc[k3-k1+k2] % mod * inv[k3-k1] % mod;
	return 0;
} 
```

---

## 作者：ccxswl (赞：3)

提供一种 $O(1)$ 回答的方法。

---

如果存在一个 $a_i \ge x$，那么它和任意别的数相加都大于 $x$，答案为 $0$。

如果 $x$ 在二进制下只有一位且不存在 $a_i \ge x$，显然任意的顺序都合法，答案为 $n!$。

设 $B$ 类数为 $x$ 在二进制下最高一位所表示的数，$A$ 类数为与 $B$ 类数相加大于 $x$ 的数，$C$ 类数为其他数。

拿样例举例，$46$ 的二进制表示为 $101110$，那么二进制表示为 $100000$ 的数，即 $32$，为 $B$ 类数。$16$ 为 $A$ 类数，$4,8$ 为 $C$ 类数。

那么限制就是 $B$ 类数只能与 $C$ 类数相邻。

设 $A$ 类数有 $a$ 个，$B$ 类数有 $b$ 个，$C$ 类数有 $c$ 个。

假设已经放好了所有 $C$ 类数，考虑把所有 $B$ 类数放进去，现在有 $c+1$ 个空可以插 $B$ 类数，那么答案即为 ${c+1 \choose b}$。

现在考虑放 $A$ 类数，设放完 $B$ 类数后空的个数为 $t$，那么 $t=c+1-b$。现在要在这 $t$ 个空中放 $a$ 个数，一个空可以不放数，这是个经典问题（如果你不会，请看文末），答案为 ${a+t-1 \choose t-1}$。

根据乘法原理，相乘即可得到答案。

因为每个数互不相同，最后答案要乘上 $a!\times b! \times c!$。

答案为：
$$
{c+1\choose b}\times {a+t-1\choose t-1}\times a!\times b! \times c!
$$

```cpp
#include <bits/stdc++.h>

#define mkp make_pair
#define fi first
#define se second
#define vec vector
#define eb emplace_back

using namespace std;

#define int long long

const int mod = 1e9 + 7;

signed main() {
  int n, X;
  cin >> n >> X;
  vec<int> a(n + 3);
  int Mx = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], Mx = max(Mx, a[i]);

  if (Mx >= X) {
    cout << "0\n";
    return 0;
  }

  vec<int> fc(n * 2 + 3), ifc(n * 2 + 3);
  fc[0] = 1;
  for (int i = 1; i <= n * 2; i++)
    fc[i] = fc[i - 1] * i % mod;
  auto ksm = [](int a, int b = mod - 2) {
    int r = 1;
    while (b) {
      (b & 1) && (r = r * a % mod);
      a = a * a % mod;
      b >>= 1;
    }
    return r;
  };
  ifc[n * 2] = ksm(fc[n * 2]);
  for (int i = n * 2 - 1; i >= 0; i--)
    ifc[i] = ifc[i + 1] * (i + 1) % mod;

  auto Cc = [&](int n, int m) -> int {
    if (n < 0 || m < 0 || n < m) return 0;
    return fc[n] * ifc[m] % mod * ifc[n - m] % mod;
  };

  if (__builtin_popcountll(X) == 1) {
    // 计算二进制下 1 的个数
    cout << fc[n] << '\n';
    return 0;
  }

  auto tmp = X, ls = 0ll;
  while (tmp - (tmp & -tmp))
    ls = tmp, tmp -= tmp & -tmp;

  ls -= tmp;
  
  int A = 0, B = 0, C = 0;
  for (int i = 1; i <= n; i++)
    B += (a[i] == tmp), A += (tmp > a[i] && a[i] > ls);
  C = n - A - B;

  int t = C + 1 - B;
  int ans = Cc(C + 1, B) * (A ? Cc(A + t - 1, t - 1) : 1) % mod;
  
  ans *= fc[C] * fc[B] % mod * fc[A] % mod;
  ans %= mod;
  cout << ans << '\n';
}

```

---

有 $m$ 个小球，要放到 $n$ 个盒子中，盒子可以为空，求方案数。

设第 $i$ 个盒子中有 $x_i$ 个球，有 $\sum\limits_{i=1}^n x_i=m$，其中 $x_i\ge 0$。

我们不太会做 $x_i\ge 0$，但我们会做 $x_i\ge 1$。把上面变一下，有 $\sum\limits_{i=1}^n(x_i+1)=m+n$，其中 $x_i+1\ge 1$。相当于一共有 $n+m$ 个球放到 $n$ 个盒子中，盒子不能为空的方案数。$n+m$ 个球两两之间有 $n+m-1$ 个空，从中选 $n-1$ 个空可以把它们分成 $n$ 份，相当于放到 $n$ 个盒子中。

得到答案：
$$
{n+m-1\choose n-1}
$$

---

## 作者：AfterFullStop (赞：3)

无解的先判掉很容易，任意排列的先判掉也很容易。

那么对于剩下的所有情况，总是可以把这些数分成三类：最大值、与最大值相加大于 $x$，与最大值相加小于等于 $x$。分出来这些数是容易的。我们假设最大值为 A 球，与最大值相加小于等于 $x$ 的为 B 球，与最大值相加大于 $x$ 为 C 球，那么我们只要通过任意排列这些球使得 A 球互不相邻且 C 球与 A 球不相邻即可（注意球是有标号的，因此设 A 球有 $x$ 个，B 球有 $y$ 个，C 球有 $z$ 个，则最后要乘上 $x!\times y!\times z!$）。

考虑先将所有的 C 球插入 B 球。显然插进去之后会有若干个缝是不能让 A 球插的。

我们设共有 $m$ 个不能让 A 球插入的缝，那么显然，对于一段连续的 $n$ 个球，他们会构成 $n+1$ 个不能让 A 球插入的缝，故当我每多给 C 球分一组时，我的缝就会在原来的基础上加一，因此我们把 C 球分成 $m-z$ 份即可产生 $m$ 个缝。

因此我们可以从仅由 B 构成的 $y+1$ 个缝中选择 $m-z$ 个，然后再把 $z$ 个球分成 $m-z$ 份，前面的直接组合数，后面的插板法，可以得到
 $$\dbinom{y+1}{m-z}\times \dbinom{z-1}{m-z-1}$$
 
然后此时总共有 $y+z+1$ 个缝，其中有 $m$ 个缝是不可插入 A 的，故最后应在 $y+z+1-m$ 个缝中插入 $x$ 个，方案数为 $\dbinom{y+z+1-m}{x}$，乘上前面的一堆东西即为
 $$\dbinom{y+1}{m-z}\times \dbinom{z-1}{m-z-1}\times \dbinom{y+z+1-m}{x} \times x! \times y! \times z!$$

接着枚举 $m$ 求个和就做完了。

注意特判一下没有 C 球的情况。

代码中 $x,y,z$ 和上面不同。


```cpp
#include<bits/stdc++.h> 
#define ri register int
#define ll long long
using namespace std;
const int maxn=2e5+7;
const int mod=1e9+7;
int n;
ll xx;
ll a[maxn];
ll jc[maxn];
ll inv[maxn];
ll qpow(ll a,ll b,ll p){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
void init(int limit){
	jc[0]=1;
	for(ri i=1;i<=limit;i++){
		jc[i]=jc[i-1]*i%mod; 
	}
	inv[limit]=qpow(jc[limit],mod-2,mod);
	for(ri i=limit;i;i--){
		inv[i-1]=inv[i]*i%mod;
	}
}
ll C(int n,int m){
	if(n==m){
		if(1!=jc[n]*inv[m]%mod*inv[n-m]%mod){
			cout<<n<<endl;
			exit(0);
		}
		return 1;
	}
	if(n<0||m<0||m>n)return 0;
	return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>xx;
	init(2e5);
	for(ri i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	int x=-1,y=-1,z=-1;
	for(ri i=1;i<=n;i++){
		int pos=upper_bound(a+1,a+i,xx-a[i])-a;
		if(pos!=i){
			for(ri j=i+1;j<=n;j++){
				if(a[j]!=a[j-1]){
					cout<<0;
					return 0;
				}
			}
			if(a[pos]==a[i]){
				x=0,y=pos-1,z=n-pos+1;
			}
			else{
				x=i-pos,y=pos-1,z=n-i+1;
			}
			break;
		}
	}
	if(x==-1){
		cout<<jc[n]<<endl;
	}
	else{
		ll ans=0;
		if(x==0){
			cout<<C(y+1,z)*jc[x]%mod*jc[y]%mod*jc[z]%mod<<endl;
			return 0;
		}
		for(ri m=0;m<=x+y+1;m++){
			ans=(ans+C(y+1,m-x)*C(x-1,m-x-1)%mod*C(x+y+1-m,z)%mod)%mod;
		}
		ans=(ans*jc[x]%mod*jc[y]%mod*jc[z]%mod);
		cout<<ans<<endl;
	}
	return 0;
}
/*
6 46
4 8 8 16 32 32
*/

```

---

