# 「ALFR Round 1」D 小山的元力

## 题目描述

小山有 $n$ 个相同的元素，他想将这 $n$ 个元素分为 $m$ 堆，显然有很多种分法。对于每种分法，定义 $a_i$ 为第 $i$ 堆的元素数量，$b_i=i!\times a_i$（其中 $i!$ 表示 $i$ 的阶乘），以及 $c=\sum\limits_{i=1}^mb_i$。而小山的元力为所有分法的 $c$ 值之和。小山想知道他的元力是多少，由于答案可能很大，所以最终答案应对 $p$ 取模（保证 $p$ 为质数）。

## 说明/提示

### 样例解释

将 $3$ 个元素分为 $2$ 堆的方案为：

1. `0 3`
2. `1 2`
3. `2 1`
4. `3 0`

小山的元力为：$(1!\times0+2!\times3)+(1!\times1+2!\times2)+(1!\times2+2!\times1)+(1!\times3+2!\times0)=18$。

### 数据范围
| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $n,m\le5$ |
| $1$ | $80$ | - |

对于 $100\%$ 的数据，$1\le n,m\le10^6$，$1\le p\le10^7$。

## 样例 #1

### 输入

```
3 2 37```

### 输出

```
18```

# 题解

## 作者：szh_AK_all (赞：5)

出题人题解。

同样，对于第一档部分分，直接暴力即可。

### 正解
既然需要求出每一种分法所贡献的值，不妨求出**每一堆**所贡献的值。

先考虑第一堆。

显然，可以考虑枚举第一堆的元素数量，即将 $i$ 从 $0$ 枚举到 $n$，其中 $i=0$ 的情况可以省略。当第一堆的元素数量确定时，它所产生的贡献与方案数有关。

这里的方案数值的是：当第一堆的元素数量为 $i$ 时，总共有多少种分法。

假设有 $x$ 中分法，那么此时所产生的贡献即为：$i\times x$。

关键在于如何求 $x$。

由于第一堆的数量已经确定，所以可以转换为这个问题：求将 $n-i$ 个元素分为 $m-1$ 堆的方案数。

这个问题可以用隔板法解决，方案数即为：$C_{n-i+m-2}^{m-2}$。

第一堆考虑完毕后，在考虑其他堆。

拿第二堆举例，第二堆的元素数量 $i$ 也可以从 $0$ 枚举到 $n$，且确定第二堆的元素数量后，方案数也为 $C_{n-i+m-2}^{m-2}$。唯一与第一堆不同的是，它所产生的贡献为：$2\times i\times x$，$x$ 的含义与上文相同。

同理，第三堆所产生的贡献即为：$6\times i\times x$。

依此类推，可以用递推的方法求出每一堆所产生的贡献。

注意特判 $m=1$ 的情况。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int jie[2000005];

int qpow(int a, int b, int p) {
	int ans = 1;
	while (b) {
		if (b % 2 == 1)
			ans = ans * a % p;
		a = a * a % p;
		b /= 2;
	}
	return ans % p;
}

int c(int n, int m, int p) {
	if (m > n)
		return 0;
	return jie[n] * qpow(jie[m], p - 2, p) % p * qpow(jie[n - m], p - 2, p) % p;
}

int lucas(int n, int m, int p) {
	if (!m)
		return 1;
	return lucas(n / p, m / p, p) * c(n % p, m % p, p) % p;
}

signed main() {
	int n, m, p;
	cin >> n >> m >> p;
	if (m == 1) {
		cout << n % p;
		return 0;
	}
	int tmp = 0;
	jie[0] = 1;
	for (int i = 1; i <= n + m; i++)
		jie[i] = jie[i - 1] * i % p;
	for (int i = 1; i <= n; i++)
		tmp += i * lucas(n - i + m - 2, m - 2, p), tmp %= p;
	int ans = tmp;
	for (int i = 2; i <= m; i++) {
		tmp = tmp * i % p;
		ans += tmp;
		ans %= p;
	}
	cout << ans;
}
```

---

## 作者：Pursuewind (赞：4)

遇到这种题，首先应该考虑拆贡献。

考虑当第 $k$ 堆的元素数量为 $i$ 时，它有多少分法。

此时分法的数量相当于把 $n-i$ 个元素分为 $m-1$ 组的方案数，隔板法可知方案数为 $C_{n-i+m-2}^{m-2}$ 种。

贡献等于方案乘权值，即 $k! \times C_{n-i+m-2}^{m-2}$。

所以输出

$$\left(\sum\limits_{k=1}^m \sum\limits_{i=1}^n k! \times C_{n-i+m-2}^{m-2}\right) \bmod P$$

但是这样是 $O(nm)$ 的，考虑优化。

$$\left(\sum\limits_{k=1}^m \sum\limits_{i=1}^n k! \times C_{n-i+m-2}^{m-2}\right) \bmod P$$
$$=\left(\sum\limits_{k=1}^m k! \left(\sum\limits_{i=1}^n C_{n-i+m-2}^{m-2}\right) \right)\bmod P$$

前面的 $\sum\limits_{k=1}^m k!$ 可以前缀和预处理出，后面的组合数可以用 Lucas 定理求得。

```cpp
/*
往第 i（1 <= i <= m）位填 j（0 <= j <= n） 的方案数有 C(n-j+m-2,m-2)
贡献为 i!*C(n-j+m-2,m-2) 
*/ 
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, m, P;
int fac[N], inv[N], a[N], ans = 0;
int sum[N];
int qpow(int a, int b){
	int res = 1, base = a;
	while (b){
		if (b & 1) res *= base;
		base *= base;
		res %= P;
		base %= P;
		b >>= 1;
	}
	return res;
}
int C(int n, int m){
	return fac[n] * inv[n - m] % P * inv[m] % P;
}
int Lucas(int n, int m){
	if (m == 0) return 1;
	return Lucas(n / P, m / P) * C(n % P, m % P) % P;
}
signed main(){
	cin >> n >> m >> P;
	fac[0] = fac[1] = inv[0] = inv[1] = sum[1] = 1;
	for (int i = 2; i <= N - 5; i ++){
		fac[i] = fac[i - 1] * i % P;
		sum[i] = (sum[i - 1] + fac[i]) % P;
		inv[i] = (P - P / i) * inv[P % i] % P;
	}
	for (int i = 1; i <= N - 5; i ++){
		inv[i] = inv[i - 1] * inv[i] % P;
	}
	if (m == 1){
		cout << n % P << "\n";
		return 0;
	}
//	cout << sum[m] << "\n";
//	for (int i = 1; i <= m; i ++){
		for (int j = 1; j <= n; j ++){
			int now = Lucas(m - 2 + n - j, m - 2);
			ans += (sum[m] * j % P * now % P);
			ans %= P;
//			cout << ans << " ";
		}
//		cout << "\n";
//	}
	cout << ans % P << "\n";
	return 0;
} 
```

---

## 作者：Wf_yjqd (赞：2)

数数，典，板。

------------

对于每个 $a$ 拆贡献就是 $a$，作为一堆的数量的次数，每堆的权值和（$\sum\limits_{i=1}^mi!$）的乘积。

作为一堆的数量的次数相当于把剩下 $n-a$ 个元素分成 $m-1$ 堆的方案数，隔板法得到 $\binom{n+m-a-2}{m-2}$。

处理 $p>n,m$ 的方法：

- [Lucas 定理](https://www.luogu.com.cn/problem/P3807)

- 对于组合中设计到的阶乘预处理 $p$ 的个数和除去所有 $p$ 后的值，每次算组合数模拟约分。

显然前者实现起来更无脑（如果会该定理），但后者让此题难度下限能达到橙。。

$\operatorname{O}(n\log n)$。

------------

注意特判 $m\le2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e7+26;
ll n,m,p,res,ress,jc[maxn],inv[maxn];
inline ll C(ll n,ll m){
    if(m>n)
        return 0;
    return jc[n]*inv[jc[n-m]]%p*inv[jc[m]]%p;
}
inline ll Lucas(ll n,ll m){
    if(m<0)
        return n==m;
    if(!m)
        return 1;
    return Lucas(n/p,m/p)*C(n%p,m%p)%p;
}
int main(){
    scanf("%lld%lld%lld",&n,&m,&p);
    jc[0]=jc[1]=inv[0]=inv[1]=1;
    for(ll i=2;i<=p;i++){
        jc[i]=jc[i-1]*i%p;
        inv[i]=p-(p/i)*inv[p%i]%p;
    }
    for(ll i=1;i<=m;i++)
        (res+=jc[i])%=p;
    for(ll i=1;i<=n;i++)
        (ress+=i*Lucas(n-i+m-2,m-2)%p)%=p;
    printf("%lld",res*ress%p);
    return 0;
}
```

---

## 作者：ask_silently (赞：1)

## 思路分析

考虑先求出 $b_i$，枚举每个 $i$ 与 $a_i$ 来求出 $b_i$。发现当前的 $b_i$ 会对答案造成多次贡献，考虑求出造成多少贡献，原本的 $n$ 个元素分为 $m$ 组被转化为 $n-a_i$ 个元素被分为 $m-1$ 组有多少方案，可以为空。则答案就是 $\binom{n-a_i+m-2}{m-2}$，详见[插板法](https://baike.baidu.com/item/%E6%8F%92%E7%A9%BA%E6%B3%95/4862293?fr=ge_ala)。

进一步考虑，发现对于第 $j$ 堆元素，其答案为：

$$\left(\sum\limits_{a_i=0}^{n} a_i \times \binom{n-a_i+m-2}{m-2}\right) \times j!$$

由于 $a_i=0$ 的时候没有值，所以 $a_i$ 的初始值可以为 $1$。发现对于每一个 $j$，前面的式子是一样的，所以可以将其变为：

$$\left(\sum\limits_{a_i=1}^{n} a_i \times \binom{n-a_i+m-2}{m-2}\right) \times \left(\sum\limits_{j=1}^{m}j!\right)$$

而前面的式子可以枚举每个 $a_i$ 进行求解，后面可以直接预处理。

注意：

- 求组合数的时候记得用 Lucas，因为如果直接求组合数，则求乘法逆元的时候，分母的阶乘有可能是 $p$ 的倍数，此时就会返回 $0$，而 Lucas 则保证 $x,y<p$，所以 $x,y$ 的阶乘也一定不是 $p$ 的倍数，此时求组合数就不会出问题。

- 阶乘的初始值要从 $0$ 开始赋值，即 $fact_0$ 要赋值为 $1$，因为 $\binom{n}{n}$ 等于 $1$ 而不是 $0$。

## AcCode


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e6+10; 

int n,m,p,ans1,ans2;
int fact[N];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

void solution(){
	/*
		将 n-i 个元素分到 m-1 组中
		每组可以为空
		有 n-i+m-1 个元素，插 m-2 个板
		有 n-i+m-2 个空隙
		ans=C_{n-i+m-2}^{m-2}
		
		对于第 j 组，每组答案为：
		i*C_{n-i+m-2}^{m-2} (i ∈ [1,n])  *   j!
		
		对于前面的式子，用 O(n) 求出
		后面的预处理得到 
		
		最后的答案为：
		cgm(i*C_{n-i+m-2}^{m-2}) * cgm(j!)    (i∈[1,n] j∈[1,m])  
	*/
}

int ksm(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=sum*x%p;
		x=x*x%p;
		y>>=1;
	}
	return sum;
}

int C(int x,int y){
	if(x<y) return 0;
	return fact[x]*ksm(fact[x-y],p-2)%p*ksm(fact[y],p-2)%p;
}

int lucas(int x,int y){
	if(y==0) return 1;
	return C(x%p,y%p)*lucas(x/p,y/p)%p;
}

void init(){
	fact[0]=1;
	for(int i=1;i<=n+m+2;i++) fact[i]=fact[i-1]*i%p;
}

signed main(){
	n=read(),m=read(),p=read();
	if(m==1){cout<<n%p;return 0;}
	init();
	for(int i=1;i<=n;i++) ans1=(ans1+i*lucas(n-i+m-2,m-2)%p)%p;
	for(int i=1;i<=m;i++) ans2=(ans2+fact[i])%p;
	cout<<ans1*ans2%p;
	return 0;
}

```

---

## 作者：yxans (赞：0)

我们肯定不能把所有分的方案都找出来再统计答案，那样子显然非常笨重。

于是考虑**拆贡献**。具体而言，对于我们要决策的第 $i$ 堆，我们钦定它后面的每一堆都是空的，然后枚举它有多少物品，它的贡献为：
$$
i!\times C_{n - i + m - 2}^{m - 2}
$$
则最终答案为:
$$
\sum_{j = 1}^m\sum_{i = 1}^ni!\times C_{n - i + m - 2}^{m - 2}
$$
这个式子是 $O(mn)$ 的。
显然可以优化成 $O(m + n)$：
$$
\sum_{j = 1}^m\sum_{i = 1}^ni!\times C_{n - i + m - 2}^{m - 2} = \sum_{j = 1}^m i! \times \sum_{i = 1}^nC_{n - i + m - 2}^{m - 2}
$$
做完了。

**code:**
```cpp
std::ios::sync_with_stdio(false);
cin.tie(0), cout.tie(0);
   
cin >> n >> m >> p;
int res = 0;
fac.resize(std::max({n, m, p}) + 1), inv.resize(std::max({n, m, p}) + 1);
fac[0] = 1, inv[0] = 1, fac[1] = 1, inv[1] = 1;
for(int i = 2; i <= std::max({p, n, m}); ++i){
  fac[i] = fac[i - 1] * i % p;
  inv[i] = (p - p / i) * inv[p % i] % p;
}
for(int i = 1; i <= m; ++i)
  (res += fac[i]) %= p;
int ans = 0;
for(int i = 1; i <= n; ++i){
  (ans += (i * lucas(n - i + m - 2, m - 2) % p)) %= p;
}
std::cout << (ans * res) % p << '\n';
return 0;
```

---

