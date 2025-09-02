# Count Supersequences

## 题目描述

You are given an array $ a $ of $ n $ integers, where all elements $ a_i $ lie in the range $ [1, k] $ . How many different arrays $ b $ of $ m $ integers, where all elements $ b_i $ lie in the range $ [1, k] $ , contain $ a $ as a subsequence? Two arrays are considered different if they differ in at least one position.

A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by the deletion of several (possibly, zero or all) elements.

Since the answer may be large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

For the first example, since $ k=1 $ , there is only one array of size $ m $ consisting of the integers $ [1, k] $ . This array ( $ [1, 1, \ldots, 1] $ ) contains the original array as a subsequence, so the answer is 1.

For the second example, the $ 9 $ arrays are $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [1, 2, 2, 3] $ , $ [1, 2, 3, 2] $ , $ [1, 3, 2, 2] $ , $ [2, 1, 2, 2] $ , $ [3, 1, 2, 2] $ .

For the fourth example, since $ m=n $ , the only array of size $ m $ that contains $ a $ as a subsequence is $ a $ itself.

## 样例 #1

### 输入

```
7
1 1000000 1
1
3 4 3
1 2 2
5 7 8
1 2 3 4 1
6 6 18
18 2 2 5 2 16
1 10 2
1
8 10 1234567
1 1 2 1 2 2 2 1
5 1000000000 1000000000
525785549 816356460 108064697 194447117 725595511```

### 输出

```
1
9
1079
1
1023
906241579
232432822```

# 题解

## 作者：1saunoya (赞：12)

开始复健。

---

$a_i$ 无论是什么对答案都没有影响。

$f_{i, j} = (k-1)f_{i-1,j} + f_{i-1,j-1}+[j=n]f_{i-1,j}$

这样复杂度可以做到 $nm$。

我们可以反过来考虑这个问题，合法的减掉不合法的。

总数容易知道是 $k^m$。

枚举匹配上的长度 $i(i=0...n-1)$

当匹配上前 i 位的时候，方案数是 $\binom{m}{i} ·(k-1)^{m-i}$。

答案只需要用合法的减掉不合法的也就是

$k^m - \sum \binom{m}{i} ·(k-1)^{m-i}$ 就可以了。

发现 i 并不大，没必要用什么奇淫技巧，直接算就可以了。

code:
[link](https://codeforces.com/contest/1838/submission/209360374)

---

## 作者：Miko35 (赞：7)

没有技巧，全是感情。

首先一个典中典是，将 $a$ 放在 $b$ 上从后往前贪心地匹配，考虑对于最后匹上的位置来构造合法的 $b$，显然：

- 匹配上的位置只有一种填法；
- $a_1$ 之前的位置有 $k$ 种填法；
- 其他位置不能与其后缀相同，有 $k-1$ 种填法。

发现系数只与 $a_1$ 匹配上的位置有关，记作 $i$ 并枚举之，那么我要做的事情就是在后面选出 $n$ 个位置放 $a$ 然后乱填。记答案 $f(n)$，有：

$$f(n)=\sum_{i=1}^{m-n+1}k^{i-1}\binom{m-i}{n-1}(k-1)^{m-n-i+1}$$

然后错项相消：

$$
\begin{aligned}
f(n)&=\sum_{i=0}^{m-n+1}k^{i-1}(k-1)^{m-n-i+1}\left(\binom{m-i-1}{n-1}+\binom{m-i-1}{n-2}\right)-k^{-1}(k-1)^{m-n+1}\binom{m}{n-1}\\
&=\dfrac{k-1}{k}\left(\sum_{i=1}^{m-n+1}k^{i-1}(k-1)^{m-n-i+1}\binom{m-i}{n-1}+\sum_{i=1}^{m-n+2}k^{i-1}(k-1)^{m-n-i+1}\binom{m-i}{n-2}-(k-1)^{m-n}\binom{m}{n-1}\right)\\
&=\dfrac{k-1}{k}\left(f(n)+\dfrac{f(n-1)}{k-1}-(k-1)^{m-n}\binom{m}{n-1}\right)\\
\end{aligned}
$$

移项整理：

$$
\begin{aligned}
f(n)&=(k-1)\left(\dfrac{f(n-1)}{k-1}-(k-1)^{m-n}\binom{m}{n-1}\right)\\
&=f(n-1)-(k-1)^{m-n+1}\binom{m}{n-1}\\
f(1)&=\sum_{i=0}^{m-1}k^{i}(k-1)^{m-1-i}=(k-1)^{m}\left(\left(\dfrac{k}{k-1}\right)^m-1\right)=k^m-(k-1)^m
\end{aligned}
$$

这样就可以 $O\left(T\log m+\sum n\right)$ 解决本题。

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a,i##i=b;i<=i##i;++i)
#define ROF(i,a,b) for(int i=a,i##i=b;i>=i##i;--i)
using namespace std;
typedef long long ll;
const int N=2e5+7,mod=1e9+7;
int T,n,m,k,x;
ll inv[N];
inline ll qpow(ll a,ll b){
    ll R=1;a%=mod;
    for(;b;b>>=1,a=a*a%mod)if(b&1)R=R*a%mod;
    return R;
}
void work(){
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n)scanf("%d",&x);
    ll ans=qpow(k,m)-qpow(k-1,m),iv=qpow(k-1,mod-2),kp=qpow(k-1,m),t=1;
    FOR(i,1,n-1){
        (kp*=iv)%=mod,(t*=m-i+1)%=mod;
        ans-=kp*inv[i]%mod*t%mod;
    }
    printf("%lld\n",(ans%mod+mod)%mod);
}
signed main(){
    inv[1]=1;
    FOR(i,2,N-2)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    FOR(i,2,N-2)(inv[i]*=inv[i-1])%=mod;
    for(scanf("%d",&T);T--;)work();
    return 0;
}
```



---

## 作者：Luciylove (赞：5)

诈骗题。

**首先 $a$ 是什么是无关的。**

因为这个是用所有的串减去不包含 $a$ 这个子序列的串，后者和 $a$ 的形态无关。

后面那个可以考虑一个 dp 的填数的过程，然后发现这个其实和 $a$ 没有任何关系。

因为 $m$ 很大，考虑正难则反，用所有的方案数减去不合法的方案。

$k^m$ 显然是所有的方案数。

由于上面那个结论，考虑将所有的 $a_i$ 看成一个东西，那不合法的就钦定其填了 $i$ 位，然后剩下的乱填，让其填不到 $i + 1$ 这一位即可。

所以答案的式子为 ：

$$k^m - \sum_{i = 1} ^ {n - 1} \tbinom{m}{i} (k - 1) ^{m - i}$$

因为 $m$ 很大，所以考虑递推算组合数即可。




---

## 作者：zyc070419 (赞：2)

## Count Supersequences 题解

首先容易想到 $\mathcal O(nm)$ 的 DP，$dp_{i,j}$ 表示到 $b$ 数组的第 $i$ 位，匹配到 $a$ 的第 $j$ 位的方案数，为了防止算重，$b$ 数组一定是能匹配 $a$ 数组就匹配，即转移方程为：
$$
dp_{i,j}=dp_{i-1,j}\times (k-1)+dp_{i-1,j-1}+dp_{i-1,j}[j=n]
$$
然后发现答案跟 $a_i$ 的值无关。考虑如何快速去算 $dp_{n,m}$ 的值，肯定是组合数，容易想到先确定 $b$ 数组中匹配 $a$ 的位置，然后其他位置算一下组合数即可，而观察发现剩余位置中除了 $a_n$ 的匹配位置 $pos_n$ 后面的位置有 $k$ 中取值，前 $pos_n-n$ 个空余位置都是只有 $k-1$ 个取值，所以枚举 $a_n$ 的位置即可，答案是：
$$
\sum_{i=n}^{m}\binom{i-1}{n-1}\times (k-1)^{i-n}\times k^{m-i}
$$
复杂度 $\mathcal O(Tm)$，显然超时。

而由于题目只保证 $\sum n$ 的值，所以肯定最后答案的计算式子肯定是枚举 $n$ 或者 $\mathcal O(1)$ 计算，而这种时候一般可以考虑一下容斥：**算出不合法的方案数，然后用总方案数减去它即可**，那么我们只用枚举匹配 $a$ 序列的长度，然后用类似上面的方法算方案数即可，但是这里注意：我们是算 **匹配 $a$ 的长度恰好为 $i$ 的方案数，因此在 $a_i$ 的匹配位置 $pos_i$ 后面的数还是只有 $k-1$ 种取值**，依次不合法方案数如下：
$$
\begin{aligned}
res=&\sum_{i=0}^{n-1}\sum_{j=i}^{m}\binom{j-1}{i-1}\times (k-1)^{j-i}\times (k-1)^{m-j}\\
=&\sum_{i=0}^{n-1}(k-1)^{m-i}\sum_{j=i}^{m}\binom{j-1}{i-1}\\
=&\sum_{i=0}^{n-1}(k-1)^{m-i}\times \binom{m}{i}
\end{aligned}
$$
则答案是 $k^m-res$。由于 $i$ 的值域很小，并且从 $\binom{m}{0}$ 到 $\binom{m}{n-1}$ 的值可以 $\mathcal O(n)$ 递推，加上递推 $k-1$ 的次幂，因此复杂度 $\mathcal O(T\log w+\sum n)$，$w$ 是值域。

或许 $k=1$ 的时候需要特判一下答案是 $1$ 吧，然后就结束了，**[代码如下](https://www.luogu.com.cn/paste/xtx56vzo)**。

---

## 作者：james1BadCreeper (赞：1)

发现 $a_i$ 换个数对 $b$ 的构造不会产生影响，然后又发现 $m$ 奇大无比，果断放弃复杂度跟 $m$ 有线性关系的做法。

考虑求答案的补集。枚举匹配的 $a$ 的长度，当匹配了 $i$ 个数时，要构造剩下的数一个匹配不上。在 $b$ 中钦定 $m$ 个匹配的，方案数为 $\binom{m}{i}$，剩下的只要跟 $a_i$ 不一样就行（让 $a_i$ 死活匹配不上），方案数为 $(k-1)^{m-i}$。

因此答案为 $k^m-\sum_{i=0}^{n-1}\binom m i (k-1)^{m-i}$，其中组合数递推计算即可。


```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

inline int poww(int a, int b) {
	int r = 1; 
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
	return r; 
}

int n, m, k; 
int a[200005]; 

int main(void) {
	int T; scanf("%d", &T); 
	while (T--) {
		scanf("%d%d%d", &n, &m, &k); 
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		int ans = poww(k, m), u = 1, v = 1; 
		for (int i = 0; i < n; ++i) {
			ans = (ans - 1ll * u * poww(v, P - 2) % P * poww(k - 1, m - i) % P) % P; 
			u = 1ll * u * (m - i) % P; v = 1ll * v * (i + 1) % P; 
		}
		printf("%d\n", (ans + P) % P); 
	}
	return 0; 
}
```

---

## 作者：honglan0301 (赞：1)

## 题目分析

简单诈骗题，容易发现 $a_i$ 具体是什么跟答案一点关系都没有。因为你可以设 $f_{i,j}$ 表示序列 $b$ 填了 $i$ 个数，其与 $a$ 匹配了 $j$ 个数的方案数。此时考虑下一个数要么会与 $a_{j+1}$ 匹配（有 $[j<n]$ 种选法），要么与 $a_{j+1}$ 不匹配（有 $k-1+[j=n]$ 种选法），故转移是：

$$
f_{i,j}=f_{i-1,j}\times (k-1+[j=n])+f_{i-1,j-1}
$$

拿生成函数表示就是 $F^i(x)=F^{i-1}(x)\times(x+(k-1))$，其中要把 $n+1$ 次项的系数扔给 $n$ 次项。我们并不直接地考虑扔系数的过程，而是考虑把结果中 $\geq n$ 次项的系数都加起来，有 $f_{m,n}=\sum\limits_{i=n}^m[x^i]F^m(x)$。

而 $F^m(x)=(x+(k-1))^m$，所以二项式定理拆开得到 $f_{m,n}=\sum\limits_{i=0}^{m-n}C_{m}^i\times (k-1)^i$。因为 $m-n$ 很大而 $n$ 很小，所以再从反面考虑得到：

$$
f_{m,n}=\sum\limits_{i=0}^m C_{m}^i\times (k-1)^i-\sum\limits_{i=n+1}^{m}C_{m}^i\times (k-1)^i=k^m-\sum\limits_{i=0}^{n-1}C_{m}^i\times (k-1)^{m-i}
$$

后者可以利用 $C_m^i=C_m^{i-1}\times \frac{m-i}{i}$ 暴力算出每个 $C_m^i$，于是做完了，时间复杂度线性对数。

## 代码

只放核心部分。

```cpp
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k; na=ksm(k,m);
		for(int i=1;i<=n;i++) cin>>a[i]; int nk=ksm(k-1,m),nc=1;
		for(int i=0;i<n;i++)
		{
			na-=(nk*nc)%mod; na+=mod; na%=mod;
			nk*=ksm(k-1,mod-2); nk%=mod;
			nc*=(m-i); nc%=mod; nc*=ksm(i+1,mod-2); nc%=mod;
		}
		cout<<na<<endl;
	}
}
```


---

## 作者：EuphoricStar (赞：1)

**结论：$a_i$ 对答案没有影响。**

考虑设计一个 $O(nm)$ dp，$f_{i, j}$ 表示填到第 $i$ 个位置，匹配到了 $a$ 的第 $j$ 个位置。发现无论 $a_j$ 是什么，总是恰好有 $1$ 个 $1 \sim k$ 的数，满足填了它之后 $j$ 加 $1$，恰好有 $k - 1$ 个数，满足填了它后 $j$ 不改变。

既然跟 $a_i$ 是什么无关，就不妨让 $a_i = 1$，可以转化成，计数长度为 $m$，值域 $[1, k]$，至少有 $n$ 个 $1$ 的序列。这个计数是平凡的，容斥，变成 $1$ 的个数 $< n$。枚举 $1$ 的个数即可，答案为：

$$k^m - \sum\limits_{i = 0}^{n - 1} \binom{m}{i} (k - 1)^{m - i}$$

注意这题不能预处理阶乘及其逆元，但是 $\binom{m}{i}$ 是可以通过 $\binom{m}{i - 1}$ 递推得到的。

[code](https://codeforces.com/contest/1838/submission/208676286)

---

## 作者：mod998244353 (赞：1)

知识点：容斥

正着算有 $O(nm)$ 的 dp 做法，此处不做赘述。

正难则反，考虑用序列总数减去不合法的序列数。

可以发现一个序列 $b$ 不满足条件当且仅当 $a,b$ 的最长公共子序列长度小于 $n$。

枚举最长公共子序列的长度 $i$，则对应的方案数为 $\begin{pmatrix}m\\i\end{pmatrix}\times(k-1)^{m-i}$

这个式子的含义如下：

设 $f_x$ 表示 $b$ 长度为 $x$ 的前缀与 $a$ 的最长公共子序列的长度。

根据转移方程 $f_x=f_{x-1}+[b_x=a_{f_{x-1}+1}]$ 得到 $f_{x-1}\leq f_x\leq f_{x-1}+1$。

我们选出 $i$ 个满足 $f_{x-1}+1=f_{x}$ 的 $x$，方案数为 $\begin{pmatrix}m\\i\end{pmatrix}$。

而满足 $f_{x-1}=f_{x}$ 的 $x$ 满足 $b_{x}\not=a_{f_{x}+1}$，所以这些位置都有 $k-1$ 种取法，共 $(k-1)^{m-i}$ 种。

所以答案为 $k^m-\sum\limits_{i=0}^{n-1}\begin{pmatrix}m\\i\end{pmatrix}\times(k-1)^{m-i}$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005,mod=1000000007;
inline int read() {
	static int x=0,c=getchar(),f=1;
	for(f=1; c<=47||c>=58; c=getchar())f=f&&(c^45);
	for(x=0; c>=48&&c<=57; c=getchar())x=(x<<3)+(x<<1)+(c&15);
	return f?x:-x;
}
inline ll fastpow(ll a,ll k) {
	ll base=1;
	for(; k; k>>=1,a=a*a%mod)if(k&1)base=base*a%mod;
	return base;
}
ll inv[MAXN];
int n,m,k;
inline void solve() {
	n=read(),m=read(),k=read();
	for(int i=1; i<=n; ++i)read();
	ll ans=fastpow(k,m),tmp1=1,tmp2=fastpow(k-1,m),C=fastpow(k-1,mod-2);
	for(int i=0; i<n; ++i) {
		ans=(ans+(mod-tmp1)*tmp2)%mod;
		tmp1=tmp1*(m-i)%mod*inv[i+1]%mod;
		tmp2=tmp2*C%mod;
	}
	printf("%lld\n",ans);
}
int main() {
	inv[1]=1;
	for(int i=2; i<MAXN; ++i) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	int t=read();
	while(t--)solve();
	return 0;
}
```

---

## 作者：Erotate (赞：0)

简单题。

考虑计算答案的补集，则我们只需要枚举有多少个位置与 $a$ 不同，然后在 $b$ 中选择这么多位固定下来，剩下的随便放,只要不与 $a$ 相同就行。

所以最后的答案就是

$$k^m-\sum^{n-1}_{i=0} \dbinom{m}{i} \times (k-1)^{m-i}$$

```cpp
const int P=1e9+7;
int ksm(int x,int y){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%P) 
		if(y&1) res=1ll*res*x%P;
	return res%P;
}
int T,n,m,k;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    T=read();
    while(T--){
    	n=read(),m=read(),k=read();
    	for(int i=1;i<=n;++i) read();
    	int res=ksm(k,m),a=1,b=1;
    	for(int i=0;i<n;++i){
    		res=(res-1ll*a*ksm(b,P-2)%P*ksm(k-1,m-i)%P+P)%P;
    		a=1ll*a*(m-i)%P,b=1ll*b*(i+1)%P;
		}
		Write(res);
	}
    return 0;
}

```


---

## 作者：jasonliujiahua (赞：0)

# CF1838E

[题目传送门](https://www.luogu.com.cn/problem/CF1838E)
## 题意简述：
给定一个长为 $n$ 的序列 $a$，$\forall i\in[1,n],a_i\in[1,k]$，有序列 $b$，满足 $a$ 是 $b$ 的子序列，$b_i \in [1,k]$ 且 $b$ 的长度为 $m$。
求满足条件的 $b$ 数组个数。
## 题目分析：
### Step 1：正面尝试
可以发现，最终的答案和 $a$ 在 $b$ 中的位置有关，因此考虑枚举 $a_n$ 的位置 $i$，有：
$$ans=\sum_{i=n}^{m}(k-1)^{i-n} \times \binom{i-1}{n-1}\times k^{m-i}$$
这里的 $\binom{i-1}{n-1}$ 是从 $i$ 之前选出 $n-1$ 个数作为 $a_1\sim a_{n-1}$。由于要避免重复，有 $(k-1)^{i-n}$ 种取值。$1\sim i-1$ 的其余位置只能有 $k-1$ 中取值，共。具体地，$a_j(j<i)$ 之前的不能等于 $a_j$。至于剩下的，由于已经确定了 $a_n$ 的位置，因此 $i$ 之后无论取什么都不会产生重复，有 $k^{m-i}$ 种取值。

然而，这个和式的变量 $i$ 与 $m$ 有关，复杂度无法接受，因此考虑如何避免 $m$。
### Step 2：容斥
考虑用所有的情况数减去非法的情况数。显然 $b$ 总共有 $k^m$ 种取值，接下来只用考虑非法的数量了。
如果一个序列非法，则其一定不能包含整个 $a$ 序列。考虑枚举 $b$ 与 $a$ 重合的个数 $i$，并类似地计算，有：
$$ans'=\sum_{i=0}^{n-1} \left (\sum_{j=i}^{m}(k-1)^{j-i} \times \binom{j-1}{i-1}\times (k-1)^{m-j}\right )$$
$$=\sum_{i=0}^{n-1} \left (\sum_{j=i}^{m}\times \binom{j-1}{i-1}\times (k-1)^{m-i}\right )$$
那么为什么这里的 $k^{m-j}$ 变成了 $(k-1)^{m-j}$ 呢？这是因为 $a_i$ 之后还有 $a_{i+1}$，因此当前枚举的 $a_i$ 的位置 $j$ 之后的数不能和 $a_{i+1}$ 相等，因此就变成了 $k-1$ 种。接下来进行化简：
$$\sum_{i=0}^{n-1} \left (\sum_{j=i}^{m}\times \binom{j-1}{i-1}\times (k-1)^{m-i}\right )$$
$$=\sum_{i=0}^{n-1} (k-1)^{m-i}\left (\sum_{j=i}^{m} \binom{j-1}{i-1}\right )$$
$$=\sum_{i=0}^{n-1} (k-1)^{m-i}\binom{m}{i}$$
可以发现此处组合数的上指标不变，下指标的范围是 $1\sim n$，有因此考虑递推计算
$$f_i=\binom{m}{i}=\frac{m^{\underline{i}}}{i!}=\frac{m^{\underline{i-1}}\times (m-i+1)}{(i-1)!\times i}$$
$$=f_{i-1}\times \frac{m-i+1}{i}$$

然后就直接计算即可。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int p=1e9+7;
int t,n,m,k,ans,inv[maxn],f[maxn];
inline int power(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=(res*x)%p;
        y>>=1;
        x=(x*x)%p;
    }
    return res;
}
void init()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
    }
}
void work()
{
    f[0]=1,ans=0;
    for(int i=0;i<n;i++)
    {
        if(i>1) inv[i]=((p-p/i)*inv[p%i])%p;
        else inv[i]=1;
        if(i) f[i]=(f[i-1]*(m-i+1)%p*inv[i])%p;
        ans=(ans+power(k-1,m-i)*f[i]%p)%p;
    }
    ans=((power(k,m)-ans)%p+p)%p;
    cout<<ans<<endl;
}
signed main()
{
    cin>>t;
    while(t--)
    {
        init();
        work();
    }
    return 0;
}
```

---

