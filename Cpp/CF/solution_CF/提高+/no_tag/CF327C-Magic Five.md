# Magic Five

## 题目描述

There is a long plate $ s $ containing $ n $ digits. Iahub wants to delete some digits (possibly none, but he is not allowed to delete all the digits) to form his "magic number" on the plate, a number that is divisible by $ 5 $ . Note that, the resulting number may contain leading zeros.

Now Iahub wants to count the number of ways he can obtain magic number, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ). Two ways are different, if the set of deleted positions in $ s $ differs.

Look at the input part of the statement, $ s $ is given in a special form.

## 说明/提示

In the first case, there are four possible ways to make a number that is divisible by 5: 5, 15, 25 and 125.

In the second case, remember to concatenate the copies of $ a $ . The actual plate is 1399013990.

In the third case, except deleting all digits, any choice will do. Therefore there are $ 2^{6}-1=63 $ possible ways to delete digits.

## 样例 #1

### 输入

```
1256
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
13990
2
```

### 输出

```
528
```

## 样例 #3

### 输入

```
555
2
```

### 输出

```
63
```

# 题解

## 作者：Wf_yjqd (赞：4)

模拟赛题，就推了推式子。

------------

考虑枚举每个 `0` 或 `5`，后面的都删去，考虑计算方案数。

若前面有 $a$ 个字符，这一个位置贡献的总方案数为 $\sum\limits_{i=0}^{k}2^{a+i\times n}$。

推导下：$=2^a\times\sum\limits_{i=0}^{k}2^{i\times n}=\frac{2^{(k+1)\times n+a-1}-2^a}{2^n-1}$。

运用费马小定理求逆元：$=(2^{(k+1)\times n+a-1}-2^a)\times(2^n-1)^{mod-2}$。

代入快速幂求解即可，复杂度 $\operatorname{O}(n\times\log{n})$。

------------

真没想到一遍过了。。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7,maxn=1e5+84;
ll k,len,ans;
char s[maxn];
inline ll poww(ll x,ll y){
    if(!y)
        return 1;
    if(y&1)
        return x*poww(x,y-1)%mod;
    ll res=poww(x,y>>1);
    return res*res%mod;
}
int main(){
    scanf("%s",s+1);
    scanf("%lld",&k);
    k--;
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        if(s[i]=='0'||s[i]=='5')
            ans=(ans+((poww(2,(k+1)*len+i-1)-poww(2,i-1))%mod+mod)%mod*poww((poww(2,len)-1+mod)%mod,mod-2)%mod)%mod;
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：是个汉子 (赞：3)

搞一个有 $\LaTeX$ 的

### Solution

考虑只有一个 $a$ 串的情况：

当第 $i$ 位是 $0$ 或 $5$ 时，我们可以选择删或不删前 $0$ ~ $i-1$ 位（当然 $i$ 后面的必须删），设 $tmp_i$ 为有 $i$ 个串的情况，那么共有 $tmp_1=2^0\cdot(a_0==5||0)+2^1\cdot(a_1==5||0)+\cdots+2^i\cdot(a_i==5||0)\cdots$ 



然后考虑如果多了一个串：

那么 $tmp_1$ 要乘上 $2^{len_a}$ 即 $2^n$ ， $tmp_2=tmp1\cdot2^n$ 。

共有 $k$ 个串，所以 $tmp_k=tmp_1\cdot (2^n)^{k-1}$ ， $ans=tmp_1+tmp_2+\cdots+tmp_k$ ，由等比数列求和公式可化为： $ans=tmp_1\cdot\frac{2^{nk}-1}{2^n-1}$ 。（ $\frac 1{2^n-1}$ 用费马小定理求一下逆元，不然会超时滴 ）

注意：因为可能出现前导零，所以前导零也要算。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int mod=1e9+7;
char a[100005];
ll k,tmp;

ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int main(){
    scanf("%s%lld",a,&k);
    ll n=strlen(a);
    for(int i=0;i<n;i++)
        if(a[i]=='5'||a[i]=='0')
            tmp=(tmp+fpow(2,i))%mod;
    printf("%lld\n",tmp*(fpow(2,n*k)-1)%mod*(fpow(fpow(2,n)-1,mod-2))%mod);
    return 0;
}
```



---

## 作者：jinhangdong (赞：1)

# 思路
当个位是 $0$ 或 $5$ 时才是 $5$ 的倍数。
不难发现如果第 $i$ 位是 $0$ 或 $5$ 他的贡献是 $2^{i-1}$。

字符串会重复 $k$ 次，假设原字符串的贡献是 $ans$ ，那么总贡献是 $\displaystyle\sum_{i=0}^{k-1} 2^{i\times n}\times ans$（ $n$ 是原字符串长度）。

将式子化简再用费马小定理求逆元就变成了 $2^{nk}\times {(2^{n}-1)}^{1e9+5}$，别忘了随时取模。

# 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
long long k,ans,sum;
string s;
long long qpow(long long a, long long b, long long c)//快速幂 
{
    if(b==0) return 1;
    if(b==1) return a%c;
    long long t=qpow(a,b/2,c)%c;
    return (((t*t)%c)*(b%2==0?1:a%c))%c;
}
int main()
{
	cin>>s>>k;
	for(int i=0;i<s.size();++i)
	if(s[i]=='0'||s[i]=='5') ans+=qpow(2,i,Mod),ans%=Mod;//记录原字符串的涌现 
	cout<<(((qpow(2,s.size()*k,Mod)-1)*(qpow(qpow(2,s.size(),Mod)-1,1e9+5,Mod)))%Mod*ans)%Mod;//这里用到刚刚说的公式 
	return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先考虑非常暴力的方法，令 $s_i$ 表示这个数字的第 $i$ 位上的数。则对于一个 $s_i = 0/5$，则考虑将其留下成为最后一位元素：$i$ 之后的所有元素都必须删，并且在 $i$ 之前的元素可删可不删，因此贡献是 $2^{i - 1}$。得到如下表达式：

$$
\sum 2^{i - 1} [s_i = 0/5]
$$

但是你发现每一次循环的情况是已知的，发现如果 $s_i = 0/5$ 则 $s_{i + n} = 0/5$。因此你考虑计算每一位的对应位分开算，即：

$$
\sum_{i = 1}^{n}(2^{i - 1} + 2^{i + n - 1} + \dots 2^{i + (k - 1)n - 1})[s_i = 0/1]
$$

然后你发现中间那一个式子是一个公比为 $2^n$ 的等比数列，直接算即可：

$$
\sum_{i = 1}^{n}(2^{i - 1}\frac{2^{n^k} - 1}{2^n - 1})[s_i = 0/1]
$$

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) % mod + (b) % mod) % mod)
#define Sub(a,b) ((((a) % mod - (b) % mod) % mod + mod) % mod)
#define Mul(a,b) (((a) % mod) * ((b) % mod) % mod)

using namespace std;

const int N = 1e5 + 10,mod = 1e9 + 7;
int n,k,ans;
int pw[N];
string s;

inline int qmi(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) res = Mul(res,a);
        a = Mul(a,a);
        b >>= 1;
    }
    return res;
}

inline void init(){
    pw[0] = 1;
    for (re int i = 1;i <= n;i++) pw[i] = Mul(pw[i - 1],2);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s >> k;
    n = s.size();
    s = ' ' + s;
    init();
    for (re int i = 1;i <= n;i++){
        if (s[i] == '0' || s[i] == '5') ans = Add(ans,Mul(pw[i - 1],Mul(Sub(qmi(pw[n],k),1),qmi(Sub(pw[n],1),mod - 2))));
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Jerrywang09 (赞：1)

### 先说几句

综合性很强的数学题，考察组合计数和等比公式。

### 解题思路

先考虑没有 $k$ 的情况。

假设没有 $k$，我们可以选定任何一个 $i$ 使得数字串 $a$ 的第 $i$ 位 $a_i$ 为 $5$ 或 $0$。显然，需要删除 $i$ 后面所有的数位，前面的每一位都可以选择是否删除。假设使得 $a_i=5$ 的 $i$ 的集合 $S$，答案可以表示成 $\sum_{i\in S}2^i$。

注：本文中所有 $i$ 是从 $0$ 开始编号，从前往后计数的。

那么，带上 $k$ 应该怎么办呢？不要慌，对于 $i\in S$，重复过后，$i+|a|$ 的位置一定也是 $5$ 或 $0$。答案就是：

$$
\sum_{i\in S}\sum_{j=0}^{k-1}(2^{i+j\cdot |a|})
$$
打开里面的幂：
$$
\sum_{i\in S}\sum_{j=0}^{k-1}(2^i\cdot 2^{j\cdot |a|})
$$

容易发现，后面的 $\sum$ 其实就是等比数列求和！让我们一起回顾一下等比数列求和公式：

$$
x\cdot \frac{q^n-1}{q-1}
$$

其中，$x$ 是首项，这里是 $2^i$；$q$ 是公比，这里是 $2^{|a|}$；$n$ 是项数，这里是 $k$。

最后别忘了快速幂求逆元，和很多取模。注意细节，详见代码。


### 奉上代码

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(int i=(s); i<=(t); ++i)
#define F first
#define S second
#define pii pair<int, int>
#define int long long
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=200010, mod=1e9+7;
using namespace std;

int p2[N];

int qp(int x, int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	p2[0]=1;
	rep(i, 1, N-1) p2[i]=p2[i-1]*2%mod;
	string s; cin>>s; int n=s.size();
	int k; cin>>k;
	int sum=0;
	for(int i=s.size()-1; i>=0; i--)
	{
		if(s[i]=='0' || s[i]=='5')
		{
			int tmp=p2[i]*(qp(p2[n], k)-1+mod)%mod*qp((p2[n]-1+mod)%mod, mod-2)%mod;
			sum=(sum+tmp)%mod;
		}
	}
	cout<<sum;
	
	return 0;
}
```

---

## 作者：D2T1 (赞：1)

[luogu 题目链接](https://www.luogu.com.cn/problem/CF327C)

这种题都要写好久，wtcl。

下文下标从 $0$ 开始。$n$ 为原序列长度。

考虑 $k=1$ 的情况，显然要以 `0` 或 `5` 结束，前面随便选多少个，后面全不选。若前面有 $p$ 个数，方案数为 $2^p$。

若 $k\neq 1$，设 $mul = \sum\limits_{i=0}^{k-1}2^{in}$，答案乘上 $mul$ 即可。

为什么呢？若原序列中第 $p$ 位为 `0` 或 `5`，那么总序列中它会出现在 $p,p+n,p+2n,...,p+(k-1)n$。总方案数显然为 $2^p+2^{p+n}+...+2^{p+(k-1)n}$，即 $2^p*mul$。

这里 $k$ 很大，$mul$ 可以分治计算。设 $f_p$ 表示 $\sum\limits_{i=0}^{p}2^{in}$，则：

$$
\begin{cases}
f_p=f_{(p-1)/2} * 2^{(p+1)/2*n} + 1&&if&p\equiv1(\bmod 2)\\
f_p=f_{p-1} + 2^{pn}&&if&p\equiv0(\bmod 2)
\end{cases}
$$

最后 $mul$ 就是 $f_{k-1}$。

```cpp
//CF327C
#include <cstring> 
#include <cstdio>
typedef long long ll;

const int N = 1e5 + 10;
const ll P = 1e9 + 7;
ll mul, ans;
char s[N];
int k, n;

ll qp(ll a, ll b){
	ll ans = 1;
	while(b){
		if(b&1){
			ans = ans * a % P;
		}
		a = a * a % P;
		b >>= 1;
	}
	return ans;
}
ll calc(ll k){
	if(k == 0){
		return 1;
	}
	if(k&1){
		return calc(k/2) * (qp(2, ((k+1)/2)*n) + 1) % P;
	} else {
		return (calc(k-1) + qp(2, k*n)) % P;
	}
}

int main(){
	scanf("%s%d", s, &k);
	n = strlen(s);
	mul = calc(k-1);
	for(int i = 0; i < n; ++ i){
		if(s[i] == '0' || s[i] == '5'){
			ans += qp(2, i);
			ans %= P;
		}
	}
	printf("%lld\n", ans * mul % P);
	return 0;
}
111

---

## 作者：Nero_Claudius (赞：1)

这道题带坑，假如没有发现肯定会爆。

首先先搜索一遍0和5，储存在数组a里面。

那么应当有2 ^ a1 +2 ^ a2 +...+ 2 ^ an。

然而这道题没那么简单，数串还可以重复k次。

因此，需要在此基础上在乘上1 + 2 ^ l + 2 ^ 2l +...+ 2 ^ (k - 1)l。其中l为数串长度。

如果到这里就提交，那就只能和AC说拜拜了。

为了省去不必要的计算，可以通过等比数列求和公式将后一个算式化简为(2 ^ kl - 1) / (2 ^ l - 1)

可即便如此还是会炸，只能借助费马小定理：a ^ (p-1) % p == 1。

所以算式可以进一步化简为(2 ^ kl - 1) * (a ^ (l - 1) ^ (p-2)) / (2 ^ l - 1)

然后快速幂就OK了。

AC代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MODE = 1000000007;
const int maxn = 100100;
typedef long long ll;

ll power(ll a, ll n) {
	ll b = 1;
	while(n) {
		if(n & 1) {
			b *= a;
			b %= MODE;
		}
		n >>= 1;
		a *= a;
		a %= MODE;
	}
	return b;
}

ll k, ans, cur;
string num;

int main() {
	cin >> num >> k;
	for(int i = 0; i < num.length(); i++) {
		if(num[i] == '0' || num[i] == '5') {
			ans += power(2, i);
			ans %= MODE;
		}
	}
	cur += power(power(2, num.length()) - 1, MODE - 2) * (power(2, num.length() * k) - 1);
	cur %= MODE;
	ans *= cur;
	ans %= MODE;
	
	cout << ans;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
还是比较好想的。

首先不考虑 $k$，单看原字符串该怎么计数。遍历该字符串，如果找到了 $0$ 或者 $5$，那么就考虑将它后面的字符全删去，此时定然是 $5$ 的倍数，之后再来算前面的方案数。可以发现是杨辉三角一行的和，设该数字前有 $len$ 个数，那么答案就是 $2^{len}$ 种方案数。

再来考虑 $k$，可以发现字符串中同一个位置重复了 $k$ 次，自然贡献也重复了 $k$ 次，只是前面数字的长度发生有规律的变化，可以发现是一个等比数列求和，直接用公式秒了，这里的公比是 $2^{len}$，$len$ 为字符串长度。

最后一个问题，计算中会有除法运算，用费马小定理求解逆元即可。
### Code:
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
const int mod=1e9+7;
string s;
int len,k;
ll ans=0;
ll bi,inv_bi; 
ll qpow(ll a,int b,int mod){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main(){
	cin>>s>>k;
	len=s.size();
	bi=qpow(2,len,mod);
	inv_bi=qpow(bi-1,mod-2,mod);
	for(int i=0;i<len;i++){
		if(s[i]=='0' or s[i]=='5'){
			ll moxiang=qpow(2,i+k*len,mod);
			ll shouxiang=qpow(2,i,mod);
			ll x=(moxiang-shouxiang+mod)%mod*inv_bi%mod;
			ans=(ans+x)%mod;
		} 
	}
	cout<<ans;
 	return 0;
} 
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF327C)

# 前置知识

[等比数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527367) | [乘法逆元](https://oi-wiki.org/math/number-theory/inverse/)

# 解法

设 $lena$ 表示 $a$ 的长度。

首先，若一个数能被 $5$ 整除，则该数的末尾一定为 $0$ 或 $5$。故考虑枚举 $a$ 中所有的 $0$ 和 $5$ 的下标，设此下标后面有 $x$ 个数字，由于 $s$ 是由 $a$ 复制 $k$ 遍形成的，所以此下标的贡献为 $\begin{aligned}\sum\limits_{i=0}^{k-1}2^{x+i \times lena}=2^x \sum\limits_{i=0}^{k-1} (2^{lena})^i=2^x \dfrac{2^{lena} \times (2^{lena})^{k-1}-(2^{lena})^0}{2^{lena}-1}=2^x \dfrac{(2^{lena})^{k}-1}{2^{lena}-1} \end{aligned}$。对于分母中的 $2^{lena}-1$ 处理其逆元即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
char a[100002];
ll qpow(ll a,ll b,ll p)
{
    ll ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans%p;
}
int main()
{
    ll k,lena,i,ans=0,num,sum,p=1000000007;
    cin>>(a+1)>>k;
    lena=strlen(a+1);
    num=qpow(2,lena,p);
    sum=(qpow(num,k,p)-1+p)*qpow(num-1,p-2,p)%p;
    for(i=lena;i>=1;i--)
    {
        if(a[i]=='0'||a[i]=='5')       
        {
            ans=(ans+qpow(2,i-1,p)*sum%p)%p;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Obviathy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF327C)

## 解题思路：

看到这题第一眼感觉就是推式子题。（一开始以为需要处理前导零考虑了好久）

首先考虑 $5$ 的整除特征，即末尾为 $0$ 或 $5$，那么基本思路就是枚举每个 $0$ 和 $5$，删光前面的所有数，然后计算答案。

考虑到是不断复制 $k$ 次的，那么枚举一个里的就可以计算全局的答案，设输入的数字串长为 $n$，下标从 $1$ 开始。

考虑删光其前的数的方案是唯一的，后面可以乱选（因为你保留了一个 $5$ 或 $0$，所以不会删空）

那么我们就能得到：

$$\begin{aligned}ans & =\sum_{d}^{s_d=0\text{ or }s_d=5}\sum_{i=1}^k2^{(k-i)n+d-1}\\ &=\sum_{d}^{s_d=0\text{ or }s_d=5}2^{d-1}\sum_{i=1}^k2^{n(k-i)}\\ &=\sum_{d}^{s_d=0\text{ or }s_d=5}2^{d-1}\sum_{i=0}^{k-1}2^{ni} \\&=\sum_{d}^{s_d=0\text{ or }s_d=5}2^{d-1}\dfrac{1-2^{nk}}{1-2^n} \\&=\dfrac{1-2^{nk}}{1-2^n} \sum_{d}^{s_d=0\text{ or }s_d=5}2^{d-1}\end{aligned}$$

那么，前面的 $\dfrac{1-2^{nk}}{1-2^n}$ $O(\log nk)$ 地预处理即可，后面的枚举然后快速幂就能解决本题了。时间复杂度 $O(\log nk + n\log n)$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define file(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define endl "\n"
using namespace std;
const int mod = 1e9+7;
string s;
ll k,n,ans;
inline ll ksm(ll a,ll k){
	ll res = 1;
	while(k){
		if(k & 1)res = res * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return res;
}
int main(){
	cin >> s >> k;n = s.size();s = ' ' + s;
	ll cst = (ksm(2,k*n)-1+mod)%mod*ksm((ksm(2,n)-1+mod)%mod,mod-2)%mod;
	for(int i = 1;i <= n;i ++)if(s[i] == '5' || s[i] == '0')ans = (ans + ksm(2,i-1))%mod;
	ans = ans * cst % mod;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 题目分析：

考虑每一个单元串，可以且仅可以将某一个为 $0$ 或 $5$ 的数位前面随便去掉几个数并把后面的所有数全部去掉，根据这个，立刻有：方案数等于 $\sum[a_i=0,5]2^i$。

然后考虑如何计算 $k$ 个连续串的问题，若设 $p_i$ 等于第 $i$ 个子串能做出的方案贡献，显然有：$p_i=p_{i-1}\times2^{len}$，可以发现，这就是一个首项等于 $\sum[a_i=0,5]2^i$ 公比等于 $2^{len}$ 等比数列，需要求这个等比数列的前 $k$ 项之和。

根据等比数列的求和公式，得到：$\dfrac{p_1\times(1-2^{len\times k})}{1-2^{len}}$。

对于这一个式子，用费马小定理求出分母的逆元，再快速幂出分子相乘即可的出答案。

最终的式子是 $p_1\times(2^{len\times k}-1)\times(2^{len}-1)^{m-2}\bmod m$。

------------
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
#define int long long
const int MOD=1000000007;
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
string s;
int k,p1,ans;
signed main(){
	cin>>s;
	for(int i=0;i<s.length();i++)
	if(s[i]=='0'||s[i]=='5')p1=(p1+pow(2,i))%MOD;
	scanf("%I64d",&k);
	ans=(p1%MOD*(pow(2,s.length()*k)-1+MOD)%MOD)%MOD;
	ans=ans*(pow(pow(2,s.length())-1,MOD-2)%MOD)%MOD;
	printf("%I64d",ans);
	return 0-0;
}
```


---

