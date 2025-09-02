# I've Been Flipping Numbers for 300 Years and Calculated the Sum

## 题目描述

经过三百年的史莱姆养殖，Akito 终于获得了魔法数字 $n$。当他找到商人准备兑换黄金时，商人却给了他一个任务。

商人表示，完成这个任务需要用到技能 $\text{rev}(n, p)$，而 Akito 恰好最近学会了这个技能。$\text{rev}(n, p)$ 表示以下操作流程：

1. 将数字 $n$ 以 $p$ 进制表示，记作 $n = \overline{n_{\ell - 1} \ldots n_1 n_0}$，其中 $\ell$ 是 $n$ 的 $p$ 进制表示的位数长度。
2. 反转这个 $p$ 进制表示，得到 $m = \overline{n_0 n_1 \ldots n_{\ell - 1}}$。
3. 将 $m$ 转换回十进制并作为结果返回。

商人的任务是计算总和 $x = \sum\limits_{p = 2}^{k} \text{rev}(n, p)$。由于这个数字可能非常大，只需要输出 $x$ 对 $10^9 + 7$ 取模后的余数。商人还提到，上一个旅行者计算这个和已经用了三百年仍未完成。但你一定会帮助 Akito 更快完成，对吗？

## 说明/提示

在第三个测试用例中，$n = 1$。数字 1 在任何进制下都表示为单个数字，这意味着对于任意 $p \ge 2$ 都有 $\text{rev}(1, p) = 1$。因此，$x = \sum\limits_{p = 2}^{k} 1 = \sum\limits_{p = 2}^{10} 1 = 10 - 2 + 1 = 9$。

在第四个测试用例中，$x = \text{rev}(4, 2) + \text{rev}(4, 3) + \text{rev}(4, 4)$。计算各项：
- $4 = 100_2 \rightarrow \text{rev}(4, 2) = 001_2 = 1$
- $4 = 11_3 \rightarrow \text{rev}(4, 3) = 11_3 = 4$
- $4 = 10_4 \rightarrow \text{rev}(4, 4) = 01_4 = 1$
因此，$x = 1 + 4 + 1 = 6$。

在第七个测试用例中，$x = \text{rev}(9, 2) + \text{rev}(9, 3)$。计算各项：
- $9 = 1001_2 \rightarrow \text{rev}(9, 2) = 1001_2 = 9$
- $9 = 100_3 \rightarrow \text{rev}(9, 3) = 001_3 = 1$
因此，$x = 9 + 1 = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
12
3 2
42 52
1 10
4 4
16 2
69 69
9 3
19 84
9982 44353
100000 1000000007
17 30
777 1000000000000000000```

### 输出

```
3
7594
9
6
1
33471
10
2006
120792461
584502117
775
46058362```

# 题解

## 作者：dingxiongyue (赞：7)

# 题解：CF2072G I've Been Flipping Numbers for 300 Years and Calculated the Sum  

[更好的阅读体验](https://www.luogu.com.cn/article/rlb9fj8d)

## Description：
给出两个整数 $n$，$k$，求 $\sum _ {p = 2} ^ k \operatorname{rev} (n,p)$，其中 $\operatorname{rev} (n,p)$ 定义为 $p$ 进制下将 $n$ 翻转后的十进制值。  

## Analysis：
考虑**根号分治**。  


* **当 $2 \le p \le \sqrt n$ 时**：直接 $O(\sqrt n \log n)$ 暴力模拟翻转即可，代码如下：
```cpp
int calc(int x, int p) {
	int ans = 0 ;
	while (x) {
		ans = (ans * p % mod + x % p % mod) % mod;
		x /= p;
	}
	return ans;
}

void solve1() {
	for (int i = 2; i <= std::min(sqrt(n), k); i++) 
		ans = (ans + calc(n, i)) % mod;
}
```

* **当 $\sqrt n < p \le n$ 时**：$p$ 进制下 $n$ 至多只有两位，分别为 $\lfloor n/p \rfloor$ 与 $n \bmod p$，那么该部分对答案的贡献即为：

$$
\sum _ {p = \lfloor \sqrt n \rfloor + 1} ^ n (n \bmod p \times p + \lfloor n/p \rfloor)
$$

但如果这样模拟的话**时间**上还是无法通过此题，所以考虑把 $n \bmod p$ 换为 $n - \lfloor n/p \rfloor \times p$，原式就变为了：

$$
\sum _ {p = \lfloor \sqrt n \rfloor + 1} ^ n (np - \lfloor n/p \rfloor \times p ^ 2 + \lfloor n/p \rfloor) \\ = (n \sum _ {p = \lfloor \sqrt n \rfloor + 1} ^ n p) - (\lfloor n/p \rfloor \times \sum _ {p = \lfloor \sqrt n \rfloor + 1} ^ n p ^ 2) +  \lfloor n/p \rfloor \times (n - \sqrt n)
$$

然后再使用整除分块，令 $\lfloor n/p \rfloor = t$，把使 $t$ 相等的 $p$ 合并在一起，原式即为：

$$
n\sum_{p = \lfloor \sqrt{n} \rfloor + 1}^{n}p - t\sum_{p = \lfloor \sqrt{n} \rfloor + 1}^{n}p^{2}+t\left(n - \lfloor \sqrt{n} \rfloor\right)
$$

将 $\sum _ {i = l} ^ r i = \frac {(l + r) (r - l + 1)} {2}$，$\sum_{i = 1}^{n}i^{2}=\frac{n(n + 1)(2n + 1)}{6}$ 代入整理得：

$$
\frac{n(\lfloor \sqrt{n} \rfloor + 1 + n)(n - \lfloor \sqrt{n} \rfloor)}{2}-\frac{t\left[n(n + 1)(2n + 1)-\lfloor \sqrt{n} \rfloor(\lfloor \sqrt{n} \rfloor + 1)(2\lfloor \sqrt{n} \rfloor + 1)\right]}{6}+t\left(n - \lfloor \sqrt{n} \rfloor\right)
$$

这样就可以 $O(1)$ 计算该部分贡献，代码如下：
```cpp
int sum(int l, int r) {
	return (r - l + 1) % mod;
}

int sum_pow(int pos) {
	return (pos * (pos + 1) * (2 * pos + 1) / 6) % mod;
}

void solve2(int l, int r) {
    if (l > r) return;
	ans = (ans + n * (l + r) * (r - l + 1) / 2);
	while (l <= std::min(n, k)) {
		int tmp = n / l;
		r = std::min(n / tmp, std::min(n, k));
		ans = (ans + tmp * ((sum(l, r) - sum_pow(r) + sum_pow(l - 1) + 2 * mod) % mod)) % mod;
		l = r + 1;
	}
}
```

* **当 $p > n$ 时**：$p$ 进制下 $n$ 只有一位，值就是 $n$，翻转后不变，贡献仍是 $n$，所以该部分贡献即为：

$$
(p - n) * n
$$

可 $O(1)$ 计算，代码如下：
```cpp
void solve3() {
	if (k > n) 
		ans = (ans + (k - n) % mod * n % mod) % mod;
}
```

总时间复杂度 $O(T \cdot (\sqrt n \log n + \sqrt n)$。

## Code：
[AC记录](https://codeforces.com/contest/2072/submission/308450332)  
```cpp
#include <iostream>
#include <cmath>
#define int long long
const int mod = 1e9 + 7;
int T;
int n, k;
int sq;
int ans;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int calc(int x, int p) {
	int ans = 0 ;
	while (x) {
		ans = (ans * p % mod + x % p % mod) % mod;
		x /= p;
	}
	return ans;
}

int sum(int l, int r) {
	return (r - l + 1) % mod;
}

int sum_pow(int pos) {
	return (pos * (pos + 1) * (2 * pos + 1) / 6) % mod;
}

void solve1() {
	for (int i = 2; i <= std::min(sq, k); i++) {
		ans = (ans + calc(n, i)) % mod;
	}
}

void solve2(int l, int r) {
    if (l > r) return;
	ans = (ans + n * (l + r) * (r - l + 1) / 2);
	while (l <= std::min(n, k)) {
		int tmp = n / l;
		r = std::min(n / tmp, std::min(n, k));
		ans = (ans + tmp * ((sum(l, r) - sum_pow(r) + sum_pow(l - 1) + 2 * mod) % mod)) % mod;
		l = r + 1;
	}
}

void solve3() {
	if (k > n) 
		ans = (ans + (k - n) % mod * n % mod) % mod;
}

signed main() {
	T = read();
	while (T--) {
		ans = 0;
		n = read(), k = read();
		sq = sqrt(n);
		solve1();
		solve2(sq + 1, std::min(n, k));
		solve3();
		write(ans);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：luqyou (赞：3)

## 思路

有一个很显然的优化：

考虑 $p>n$ 时有 $\text{rev}(n,p)=n$。

于是我们只需要暴力枚举 $1 \le p \le n$ 即可。

考虑优化。观察到对于 $p > \sqrt{n}$，有 $\text{rev}(n,p)=\lfloor \dfrac{n}{p} \rfloor + p \times (n \bmod p)=\lfloor \dfrac{n}{p} \rfloor + p \times n - p^2 \times \lfloor \dfrac{n}{p} \rfloor$。使用整除分块即可。

## code

```cpp
//calc(l,r):sum l<=i<=r i
//Calc(l,r):sum l<=i<=r i^2
int f(int x,int k){//sum 1<=i<=x k/i
    int res=0;
    for(int l=1,r;l<=x;l=r+1) r=min(x,k/(k/l)),res=(res+(r-l+1)*((k/l)%mod)%mod)%mod;
    return res;
}
int g(int x,int k){//sum 1<=i<=x i*i*(k/i)
    int res=0;
    for(int l=1,r;l<=x;l=r+1) r=min(x,k/(k/l)),res=(res+Calc(l,r)*((k/l)%mod))%mod;
    return res;
}
int rev(int x,int p){
    int s=0;
    while(x) s=(s*p+(x%p))%mod,x/=p;
    return s;
}
void solve(){
    cin>>n>>k;
    if(n==1) return cout<<(k-1+mod)%mod<<endl,void();
    int res=0,sq=sqrt(n);
    if(k<=sq){
        for(int i=2;i<=k;i++) res=(res+rev(n,i))%mod;
        return cout<<res<<endl,void();
    }
    for(int i=2;i<=sq;i++) res=(res+rev(n,i))%mod;
    res=(res+f(min(n,k),n)-f(sq,n)+mod)%mod;
    res=(res+calc(sq+1,min(n,k))*n)%mod;
    res=(res-g(min(n,k),n)+g(sq,n)+mod)%mod;
    res=(res+max(0ll,k-n)%mod*n)%mod;
    cout<<res<<endl;
}
```

---

## 作者：wmrqwq (赞：3)

这是一篇视频题解。

![](bilibili:BV1fHP3ewES9?t=447)

[代码链接](https://codeforces.com/contest/2072/submission/307825925)

---

## 作者：luogu_gza (赞：2)

感谢来自可爱喵喵 @Glacia_official 的指导。

考虑分一位，两位，三位，大于三位的情况。

1. 一位

参见其他题解，复杂度 $O(1)$。

2. 两位

相当于求 $\sum_{p=l}^{r}(n \bmod p)p+\lfloor \frac{n}{p} \rfloor=\sum_{p=l}^{r}(np-(p-1)\lfloor \frac np \rfloor)$。

$np$ 用脚求，$\lfloor \frac np \rfloor(p-1)$ 套用 DIVCNT1 的方法，但是计算一个梯形的贡献的时候我们使用类欧而非 DIVCNT1 中的皮克定理，复杂度 $O(n^{\frac 13}\log n)$。

3. 三位

相当于求 $\sum_{p=l}^{r}(n \bmod p)p^2+(\lfloor \frac np \rfloor \bmod p)p+\lfloor \frac n{p^2} \rfloor=\sum_{p=l}^{r}(n-\lfloor \frac np \rfloor)p^2+(\lfloor \frac np \rfloor-\lfloor \frac n{p^2} \rfloor p)p+\lfloor \frac n{p^2} \rfloor$。

$\lfloor \frac np \rfloor p^2$ 也可以用 DIVCNT1 套类欧解决，$\lfloor \frac np \rfloor p$ 上文已经说过了。

$\lfloor \frac n{p^2} \rfloor$，$\lfloor \frac n{p^2} \rfloor p^2$ 都可以用普通的整除分块解决，因为 $\lfloor \frac n{p^2} \rfloor$ 只有 $O(n^{\frac 13})$ 段。 

复杂度 $O(n^{\frac 13}\log n)$。

4. 大于三位

直接暴力，复杂度 $O(n^{\frac 13
}\log n)$。

---

总复杂度 $O(n^{\frac 13}\log n)$，代码也太难了，不想写。

---

## 作者：xxr___ (赞：1)

知识点：根号分治

首先我们发现如果 $k > n$ 了，那么无论怎么翻转都是 $n$。

其次，如果 $k > \sqrt n$ 那么这个数字只有两位，且翻转后的最低位是 $\lfloor\frac{n}{k}\rfloor$ 最高位是 $k\times (n \bmod k)$ 换成带余除法就是 $k\times (n - \lfloor \frac{n}{k}\rfloor \times k)$。

展开，得：$\sum_{k = \sqrt n + 1} ^ n \lfloor\frac{n}{k}\rfloor\times (1 - k^2) + nk$。

然后这是个整除分块的状物，可以枚举 $\lfloor \frac{n}{k}\rfloor$ 的值然后套上平方和公式即可。代码几乎没细节。
```cpp
#include<iostream>
#include<cmath>
#define int long long
using ll = long long;
const ll mod = 1e9 + 7;
int c[25];
ll n,k;
ll ask(ll x){
	return ((x * (x + 1) * (2 * x + 1)) / 6 ) % mod;
}
ll solve(ll l,ll r){
	if(l > r) return 0ll;
	ll ans = 0;
	ans = (l + r) * (r - l + 1) * n/ 2;
	ans %= mod;
	while(l <= std::min(n,std::min(k,r))){
		int now = n / l;
		int R = (n / now);
		R = std::min(std::min(n,k),R);
		(ans += now * (R - l + 1 + ask(l - 1) - ask(R) + mod + mod + mod) % mod + mod) %= mod;
		l = R + 1;
	} 
	return ans;
}
int32_t main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int T;
	std::cin >> T;
	while(T--){
		ll ans = 0;
		std::cin >> n >> k;
		ll len = std::sqrt(n);
		for(int i = 2;i <= std::min(k,len); ++i){
			int res = 0,cnt = 0,j = n;
			while(j){
				c[++ cnt] = j % i;j /= i;
			}
			for(int p = 1;p <= cnt; ++p){
				res = (res * i) + c[p];
				res %= mod; 
			}
			(ans += res) %= mod;
		}		
		ll l = len + 1;
		ans += solve(l,std::min(n,k));
		ans %= mod;
		if(k > n) ans += (k - n) % mod * n % mod;
		ans %= mod;
		std::cout << ans << '\n'; 
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：1)

纪念一下我自己想出来并实现并且一遍过的一道蓝题。

这个题的难点在于想到怎样根号分治，如果你想到以后，这个题就非常简单了。

首先我们可以拆一下进制的式子，然后发现，如果位数大于 $3$ 的话，式子里面一定包含 $k^2$，因此我们可以按照 $k$ 分治，对于 $k\le \sqrt n$ ，我们暴力去算，否则转化为 $k$ 进制以后只有不超过两位。一位的数我们直接去算就可以了，此时 $k>n$，我们考虑两位怎么算。

我们可以将 $n$ 表示为 $kx+y$，我们需要贡献 $ky+x$，而 $k>\sqrt n$，因此 $x<\sqrt n$，我们直接枚举 $x$，显然有 $\lceil \frac{n}{x+1} \rceil \le k \le \frac{n}{x}$，为了防止重复，当 $n$ 是 $x+1$ 倍数的时候，左端点要 $+1$。

然后考虑式子问题，将 $y$ 代换为 $n-kx$，代入得 $ky+x=nk-k^2x+x$，对于 $k$ 项我们做等差数列求和，对于 $k^2$ 项我们用平方和公式，然后再加上这些 $x$ 就可以了。具体公式见源代码（代码中我把左端点 $-1$ 便于计算）。

时间复杂度 $O(T\sqrt n)$。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;

int t,n,k,p[600][100],a[100];

signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	for(int i=2;i<=580;i++){
        p[i][0]=1;
		for(int now=i,j=1;now<=500000;now*=i,j++)p[i][j]=now;
	}
	while(t--){
		cin>>n>>k;int lim=sqrt(n);
		int ans=0;
		for(int i=2;i<=min(lim,k);i++){
			int m=n,pos=0;
			for(int j=1;;j++){
				if(m==0)break;pos++;
				a[j]=m%i;m/=i;
			}
			for(int j=pos;j>=1;j--){
				ans+=p[i][pos-j]*a[j]%mod;ans%=mod;
			}
		}
		for(int i=lim;i>=1;i--){
			int a=ceil(1.0*n/(i+1))-1,b=n/i;
            if(n%(i+1)==0)a++;a=max(a,1ll);b=max(b,2ll);
			if(a>=k)break;if(b<=lim)continue;b=min(b,k);
            if(b>n)break;
			ans+=n*(a+1+b)*(b-a)/2%mod;ans%=mod;
			ans-=(b*(b+1)*(2*b+1)/6%mod-a*(a+1)*(2*a+1)/6%mod+mod)%mod*i%mod;ans=(ans+mod)%mod;
			ans+=(b-a)*i%mod;ans=(ans+mod)%mod;
		}
		if(k>n)ans+=(k%mod-n)*n%mod;ans=(ans+mod)%mod;
		cout<<ans<<"\n";
	}
}

---

## 作者：swww77 (赞：1)

题目大意是：给定两个整数 $n$ 和 $k$ ，求出  $\sum\limits_{p=2}^{k}{\text{rev}(n, p)}$ 的值。

其中 $\text{rev}(n, p)$ 是把 $n$ 在 $p$ 进制下“倒置”，然后再转换成十进制的值。

有个显然的事情，当 $p$ 大于 $n$ 时，转换成 $p$ 进制一定只有一位，所以 $\text{rev}(n, p)=n$。

这样 $p$ 需要考虑的范围就跟 $n$ 的范围相同，直觉想的是直接模拟，对于每个进制 $p$，可以直接模拟转换进制的过程，这样的操作次数是 $T*\sum\limits_{p=2}^{n}{log_{p}{i}}$ 。由于题目没有对 $n$ 的总限制，所以当每次 $n$ 都拉满的时候必然超时。

观察到当 $p>\sqrt{n}$ 的时候，转换成 $p$ 进制的结果一定小于等于两位。此时可以推出转换成十进制的结果：$n \% p*p+n/p$。

使用数论分块，对于每个$a = \left\lfloor \frac{n}{p} \right\rfloor$ 相同的区间，可以一起处理答案。

将 $\text{rev}(n, p)$ 分解为：
$$
\text{rev}(n, p) = (n - a \times p) \times p + a = n \times p - a \times p^2 + a
$$
该表达式可以重新排列为：
$$
\text{rev}(n, p) = a(1 - p^2) + n \times p
$$

对于区间 $[l, r]$，累加和拆分为：
$$
\sum_{p=l}^{r} \text{rev}(n, p) = a \sum_{p=l}^{r} (1 - p^2) + n \sum_{p=l}^{r} p
$$
其中，$\sum (1 - p^2)$ 直接预处理计算，而 $\sum p$ 是等差数列求和 $\frac{(l+r)(r-l+1)}{2}$。这样的块总共有 $\sqrt{n}$ 个。

对于 $p\leq\sqrt{n}$ 的部分，我们模拟计算，时间复杂度  $\sum\limits_{p=2}^{\sqrt{n}}{log_{p}{i}}$，可以看成 $O(\sqrt{n})$ 带了点常数。所以总时间复杂度为 $O(T\times\sqrt{n})$。

代码如下。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int N1=5e3+10;
const int mod=1e9+7;
int pre[N];
int cal(int x,int base){
    vector<int> st;
    while(x){
        st.push_back(x%base);
        x/=base;
    }
    int ans=0;
    for(auto x:st){
        ans=(ans*base)%mod;
        ans+=x;
    }
    return ans%mod;
}
void Atomatic_AC_machine(){
    int n,k;cin>>n>>k;
    int ans=0;
    if(k>n){
        ans=((k-n)%mod*n)%mod;
        k=n;
    }
    int lim=min((int)sqrt(n),k);//如果k很小要判到k，而不是根号n
    for(int i=2;i<=lim;i++){
        ans=(ans+cal(n,i))%mod;
    }
    for(int l=lim+1,r;l<=k;l=r+1){
        int x=n/l;
        r=min(k,n/x);//每个块的最右边，注意不要大于r
        ans=(ans+(((l+r))*(r-l+1)/2)%mod*n)%mod;//这里要先除以2再取模不然是错的
        ans=(ans+((pre[r]-pre[l-1]+mod)%mod*x)%mod)%mod;
    }
    cout<<ans<<endl;
}   
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t=1,i=0;
    cin>>t;
    for(int i=1;i<=300000;i++){
        pre[i]=((pre[i-1]+(1-i*i))%mod+mod)%mod;
    }
    while(t--){
        Atomatic_AC_machine();
    }
    return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

### 题目大意

给定你 $n, k$，我们定义 $\text{rev}(n, p)$ 为 $n$ 在 $p$ 进制下反转后返回十进制结果，求：

$$
x = \sum_{p = 2} ^ k \text{rev}(n, p)
$$

对 $10^9 + 7$ 取模的结果。

### 解题思路

显然的分类讨论。

- 当 $p > n$ 时，我们有 $k - n$ 个 $p$ 满足 $\text{rev}(n, p) = n$，这一部分贡献为 $(k - n) \times n$。

- 当 $2 \le p \le n$ 时，我们需要找到一个位数 $L$ 满足：

  $$
  p^{L - 1} \le n < p^L.
  $$

  容易证明 $L \ge 2$，那么 $p$ 也就会存在一个界限。

    - 当 $L = 2$：显然地，可以推导出 $\sqrt{n} < p \le n$。此时式子转换一下：
      
      $$
      \begin{aligned}
      x &= \sum_{p = \lfloor\sqrt{n}\rfloor + 1} ^ n \text{rev}(n, p) \\
      &= \sum_{p = \lfloor\sqrt{n}\rfloor + 1} ^ n n \times p - \lfloor\frac{n}{p}\rfloor \times (p^2 - 1).
      \end{aligned}
      $$

      这个东西可以整除分块求。

  - 当 $L > 2$：此时必然有 $p \le \sqrt{n}$，转换一下式子我们就容易发现上述条件等价于：
    
    $$
    n^{\frac1L} < p \le n^{\frac{1}{L - 1}}.
    $$

    对于每个 $L$ 在区间 $[\max(2, \lfloor n^{\frac1L} \rfloor + 1), \min \{n, k, \lfloor n^{\frac{1}{L - 1}} \rfloor\}]$ 内枚举 $p$ 且暴力计算即可。

综上，时间复杂度 $\mathcal O(T\sqrt{n}\log n)$。

代码实现如下：

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 6, P = 1E9 + 7;

int power(int a, int b) {
	int res = 1;
	a %= P;
	while (b > 0) {
		if (b & 1) {
			res = res * a % P;
		}
		a = a * a % P;
		b >>= 1;
	}
	return res;
}

int pre_sum(int x) {
	x %= P;
	return x * (x + 1) % P * power(2, P - 2) % P;
}

int pre_sq(int x) {
	x %= P;
	return x * (x + 1) % P * (2 * x + 1) % P * power(6, P - 2) % P;
}

int rsum(int l, int r) {return (pre_sum(r) - pre_sum(l - 1) + P) % P;}

int rsq(int l, int r) {return (pre_sq(r) - pre_sq(l - 1) + P) % P;}

bool check(int x, int b, int n) {
	int p = 1;
	for (int i = 0; i < b; ++i) {
		if (p > n / x) return false;
		p *= x;
	}
	return p <= n;
}

int get(int n, int b) {
	int lo = 1, hi = n, ans = 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid, b, n)) lo = (ans = mid) + 1;
		else hi = mid - 1;
	}
	return ans;
}	

int rev(int n, int p) {
	int ans = 0;
	while (n > 0) {
		ans = (ans * (p % P) % P + n % p) % P;
		n /= p;
	}
	return ans;
}

void solve() {
	int n, k;
	std::cin >> n >> k;
	int ans = 0;
	if (n == 1) std::cout << (k - 1) % P << "\n";
	else {
		if (k > n)
			ans = (k - n) % P * n % P;
			int u = std::min(k, n);
			int p = 0;
			int sn = floor(sqrt((long double)n));
			int l = std::max(sn + 1, 2LL), r = u;
			if (l <= r) {
				int c = l;
				while (c <= r) {
					int q = n / c, p_ = r;
					if (q > 0)
						p_ = std::min(p_, n / q);
					int s1 = rsum(c, p_), s2 = rsq(c, p_);
					int cnt = (p_ - c + 1) % P;
					int s = ((n % P) * s1 % P - (q % P) * ((((s2 - cnt) % P) + P) % P) % P + P) % P;
					p = (p + s) % P;
					c = p_ + 1;
				}
			}
			int lm = floor(log2((long double)n)) + 1;
			for (int l = 3; l <= lm; ++l) {
				int lo = get(n, l) + 1, hi = get(n, l - 1);
				int lp = std::max(lo, 2LL), hp = std::min({hi, u, n});
				if (lp <= hp) {
					for (int pp = lp; pp <= hp; ++pp) {
						p = (p + rev(n, pp)) % P;
					}
				} 
			}
		std::cout << ((ans + p) % P + P) % P << "\n";		
	}
}

int32_t main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  int t;
  std::cin >> t;
  // t = 1;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

考虑根号分治。

我们注意到，对于 $p>n$ 的 $p$，$\operatorname{rev}(n,p)$ 总是 $n$，那么原式就变成了 $\sum\limits_{p=2}^n\operatorname{rev}(n,p)+(k-n)\times n$。

我们又注意到对于 $\sqrt n< p\le n$ 的 $p$，$n$ 在 $p$ 进制下最多只有 $2$ 位，那么 $\sum\limits_{p=\sqrt n+1}^n \operatorname{rev}(n,p)=\sum\limits_{p=\sqrt n+1}^n \lfloor\frac{n}{p}\rfloor+n\bmod p\times p=\sum\limits_{p=\sqrt n+1}^n \lfloor\frac{n}{p}\rfloor+(n-\lfloor\frac{n}{p}\rfloor\times p)\times p=\sum\limits_{p=\sqrt n+1}^n \lfloor\frac{n}{p}\rfloor+n\times p-\lfloor\frac{n}{p}\rfloor\times p^2=\sum\limits_{p=\sqrt n+1}^n \lfloor\frac{n}{p}\rfloor\times (1-p^2)+n\times p$，直接数论分块即可。

那么原式 $=\sum\limits_{p=1}^{\sqrt n} \operatorname{rev}(n,p)+\sum\limits_{p=\sqrt n+1}^n \lfloor\frac{n}{p}\rfloor\times (1-p^2)+n\times p+(k-n)\times n$，第一坨东西直接暴力求即可，时间复杂度 $O(\sum\sqrt n)$。

---

## 作者：DengStar (赞：0)

推荐 [在博客园中查看](https://www.cnblogs.com/dengstar/p/18762840)。

> 数论分块，根号分治

首先观察到当 $n$ 在 $p$ 进制下位数很多的时候，很难把 $p$ 不同的情况放在一起处理，只能老老实实地把 $n$ 展开成 $p$ 进制的形式再计算。由于当 $p^{2} < n$ 时 $n$ 的 $p$ 进制表示才多于 $2$ 位，所以可以暴力处理 $p < \sqrt{n}$ 时的情况，这样做的时间复杂度为 $O(\sqrt{n})$ $^{\ast}$。

$^{\ast}$：这里时间复杂度的上界容易分析到 $O(\sqrt{n} \log n)$，但实际上更紧的界是 $O(\sqrt{n})$，见 [CF 的这个评论](https://codeforces.com/blog/entry/140039?#comment-1250831)。

而 $n$ 的 $p$ 进制表示不超过 $2$ 位时，我们考虑一起处理。

当 $p > n$ 时，$n$ 的 $p$ 进制表示只有 $1$ 位，翻转以后的值仍为 $n$。

当 $n$ 的 $p$ 进制表示只有 $2$ 位时，$n$ 可以被表示成 $\lfloor n / p \rfloor p + (n \bmod p)$，于是 $\operatorname{rev}(n, p) = (n \bmod p) + \lfloor n / p \rfloor$。考虑如何快速计算 $\sum_{p = \lfloor \sqrt{n} \rfloor + 1}^{\min(n, k)} ((n \bmod p) + \lfloor n / p \rfloor)$。

（为了方便，下面省略求和符号中 $p$ 的上下界。）

对 $\lfloor n / p \rfloor$ 求和，容易想到数论分块，但 $n \bmod p$ 这一项不太好处理。把它改写成 $n - \lfloor n / p \rfloor p$，这样就统一凑成了整除的形式，于是待求式子变成
$$
\begin{aligned}
&\quad \sum_{p} ((n - \lfloor n / p \rfloor p)p + \lfloor n / p \rfloor) \\
&= \sum_{p} (np + \lfloor n / p \rfloor - p^{2}\lfloor n / p \rfloor) \\
&= n\sum_{p}p + \sum_{p} \lfloor n / p \rfloor + p^{2}\sum_{p} \lfloor n / p \rfloor 
\end{aligned}
$$
第一个和式可以直接计算，剩下两个和式都可以通过数论分块在 $O(\sqrt{n})$ 的时间内计算。

[AC 记录](https://codeforces.com/contest/2072/submission/309715140)

---

## 作者：11400F (赞：0)

## [2072G Div.3 最新最热](https://codeforces.com/contest/2072/problem/G)


[不知道怎么样的阅读体验](https://www.11490dx.net/2025/02/21/R702-cfra-practice-log/#g-div.3-%E6%9C%80%E6%96%B0%E6%9C%80%E7%83%AD)

---

这道题可惜了，如果想到拆式子，赛时就可以切掉这道题然后 AK 了。

首先，$p$ 大于 $n$ 的答案全是 $n$，显然。

其次，当 $\sqrt{n} < p \le n$ 时，$\text{rev}(n, p)$ 是 base $p$ 意义下的两位数。所以可以拆分，算出所有两位数的答案为：

$$
\begin{aligned}
&\sum_{p=sq+1}^{n} p(n\bmod p) + (n-n\bmod p)/p\\
= &\sum_{p=sq+1}^{n} p(n-\lfloor\frac{n}{p}\rfloor p) + \lfloor \frac{n}{p}\rfloor \\
= &\sum_{p=sq+1}^{n} np-\lfloor \frac{n}{p}\rfloor p^2 + \lfloor \frac{n}{p} \rfloor \\
= &\sum_{p=sq+1}^{n} \lfloor \frac{n}{p} \rfloor (1-p^2) + np

\end{aligned}
$$

然后就可以普通分块做了。预处理 $p^2$ 的前缀和然后求即可。时间复杂度 $O(\sqrt{n})$

最后，当 $p < \sqrt n$，暴力求即可。复杂度目测 $O(\sqrt n \log)$。能过就行。

同时，不要忘记判断 $k$ 的边界关系。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
typedef long long ll;
const ll mod = 1e9+7;
int n;
ll k, ans;
ll psquared[N];
void init(){
    for(int i=1;i<N;i++){
        psquared[i] = (psquared[i-1] + ll(i)*i) % mod;
    }
}
const ll inv2 = (mod+1)/2;
#define dcsl(x,y) (inv2*(x+y)%mod*(y-x+1)%mod)
#define sum(x,y) ((psquared[y] - psquared[x-1] + mod) % mod)

int st[N], len;

ll bruteforce(int bas){
    len = 0;
    int x = n;
    while(x){
        st[++len] = x%bas;
        x /= bas;
    }
    ll res = 0, powbas = 1;
    for(int i=len;i>=1;i--){
        res = (res + st[i]*powbas) % mod;
        powbas = powbas * bas % mod;
    }
    return res;
}

void solve(){
    cin>>n>>k;
    ans = 0;
    if(k > n){
        ans += (k-n)%mod*n%mod;
    }
    ll sq = int(sqrt(n));
    int bg = sq+1, ed = min(ll(n), k);
    // cout<<bg<<" ~ "<<ed<<'\n';
    while(bg <= ed){
        int l = bg, r = n/(n/bg);
        ll val = n/l;
        // cout<<"VAL = "<<val<<'\n';
        if(r <= ed){
            ans = (ans + val * (r-l+1 - sum(l, r) + mod)) % mod;
            ans = (ans + n*dcsl(l, r)) % mod;
        }else{
            ans = (ans + val * (ed-l+1 - sum(l, ed) + mod)) % mod;
            // cout<<"??? "<<ans<<'\n';
            ans = (ans + n*dcsl(l, ed)) % mod;
            break;
        }
        bg = r+1;
    }
    sq = min(sq, k);
    // cout<<ans<<'\n';
    for(int p=2;p<=sq;p++){
        ans = (ans + bruteforce(p)) % mod;
    }
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin>>t;
    init();
    while(t--){
        solve();
    }
    return 0;
}
```

---

