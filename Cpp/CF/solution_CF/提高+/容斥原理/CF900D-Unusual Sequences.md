# Unusual Sequences

## 题目描述

Count the number of distinct sequences $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i} $ ) consisting of positive integers such that $ gcd(a_{1},a_{2},...,a_{n})=x $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900D/b6b0405f12ef386aeb195f818cd0534bcf4623e0.png). As this number could be large, print the answer modulo $ 10^{9}+7 $ .

 $ gcd $ here means the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 说明/提示

There are three suitable sequences in the first test: $ (3,3,3) $ , $ (3,6) $ , $ (6,3) $ .

There are no suitable sequences in the second test.

## 样例 #1

### 输入

```
3 9
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 8
```

### 输出

```
0
```

# 题解

## 作者：Siyuan (赞：29)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-900D-Unusual-Sequences/)

---

## Description

> 题目链接：[Codeforces 900D](https://codeforces.com/contest/900/problem/D)

求满足下面两个条件的数列 $a_1,a_2,\dots,a_n(1\le a_i)$ 的个数（答案对 $10^9+7$ 取模）：

1. $\gcd(a_1,a_2,\dots,a_n)=x$
2. $\sum_{i=1}^n a_i=y$

数据范围：$1\le x.y\le 10^9$

------

## Solution

如果在 $x\nmid y$ 的情况下，显然无解。

我们令 $m=\frac{y}{x}$，那么问题转化为：求满足 $\gcd(a_1,a_2,\dots,a_n)=1$ 且 $\sum_{i=1}^n a_i=m$ 的数列个数。

我们先不考虑 $\gcd=1$ 的限制，设 $g(x)$ 表示 $\sum_{i=1}^n a_i=x$ 的数列个数。

对于 $g(x)$ 的值，我们可以使用**隔板法**求解：
$$g(x)=\sum_{i=1}^x \binom{x-1}{i-1}=2^{x-1}$$
我们发现，$g(x)$ 的值又可以通过 $f(x)$ 求得：
$$g(x)=\sum_{d\mid x} f(d)$$
接下来介绍两种做法：

### 递推

我们可以考虑容斥原理：**所有序列数量**减去**不合法的序列数量**。我们枚举不合法的序列的 $\gcd$ 记为 $d$，显然 $d$ 必须满足 $d\mid x,d>1$，这样的序列数量为 $f\left(\frac{x}{d}\right)$（当然也可以通过 $g$ 和 $f$ 的关系得到）。
$$\begin{aligned}f(x)&=g(x)-\sum_{d\mid x,d>1} f\left(\frac{x}{d}\right) \\&=2^{x-1}-\sum_{d\mid x,d>1} f\left(\frac{x}{d}\right)\end{aligned}$$
由于一个数的因子的因子也一定是这个数的因子，所以我们发现需要的 $x$ 为 $d(m)$ 个，即不超过 $O(\sqrt m)$ 个，可以直接递归求解。

**时间复杂度**：$O(d(m)\sqrt m\log m)$

### 反演

我们发现：
$$g(x)=\sum_{d\mid x} f(d)$$
这个式子的本质是 $g=f\ast 1$，通过**莫比乌斯反演**可以得到：
$$f(x)=\sum_{d\mid x} \mu\left(\frac{x}{d}\right)g(d)$$
这样一来我们就可以直接暴力求解了。

**时间复杂度**：$O\left(\frac{m}{\log m}\right)$

------

## Code

### 递推

```cpp
#include <cstdio>
#include <map>

const int mod=1e9+7;
std::map<int,int> mp;

int pow(int x,int p) {
	int ret=1;
	for(;p;p>>=1,x=1LL*x*x%mod) if(p&1) ret=1LL*ret*x%mod;
	return ret;
}
void upd(int &x,int y) {
	(x+=y)>=mod&&(x-=mod);
}
int solve(int n) {
	if(n==1) return 1;
	if(mp.count(n)) return mp[n];
	int ans=0;
	for(int i=2;i*i<=n;++i) {
		if(n%i==0) {
			upd(ans,solve(i));
			if(i*i!=n) upd(ans,solve(n/i));
		}
	}
	upd(ans,solve(1));
	ans=(pow(2,n-1)-ans+mod)%mod;
	return mp[n]=ans;
}
int main() {
	int x,y;
	scanf("%d%d",&x,&y);
	if(y%x) return puts("0"),0;
	printf("%d\n",solve(y/x));
	return 0;
}
```

### 反演

```cpp
#include <cstdio>

const int N=1e5+5;
const int mod=1e9+7;
int x,y,tot,p[N];
bool flg[N];

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
int mu(int n) {
	int cnt=0;
	for(int i=1;i<=tot&&1LL*p[i]*p[i]<=n;++i) {
		if(n%p[i]) continue;
		int now=0;
		while(n%p[i]==0) n/=p[i],++now;
		if(now>1) return 0;
		++cnt;
	}
	if(n>1) ++cnt;
	return cnt%2==0?1:mod-1;
}
int pow(int x,int p) {
	int ret=1;
	for(;p;p>>=1,x=1LL*x*x%mod) if(p&1) ret=1LL*ret*x%mod;
	return ret;
}
void upd(int &x,int y) {
	(x+=y)>=mod&&(x-=mod);
}
int main() {
	sieve(N-5);
	scanf("%d%d",&x,&y);
	if(y%x) return puts("0"),0;
	int n=y/x,ans=0;
	for(int i=1;1LL*i*i<=n;++i) {
		if(n%i==0) {
			upd(ans,1LL*mu(n/i)*pow(2,i-1)%mod);
			if(i*i!=n) upd(ans,1LL*mu(i)*pow(2,n/i-1)%mod);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：big_news (赞：19)

[blog](https://big-news.cn/2020/07/08/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91Unusual%20Sequences/)

提供一个不使用反演的清奇思路。

设 $f(s,g)$ 表示和为 $s$ ,gcd为 $g$ 的数列的数量，容易发现以下性质：

$$ f(s,g)=0, \text{ }g\nmid s $$
$$ f(s,g)=f(s/g,1), \text{ } g|s $$

我们知道和为 $s$ 的数列应当有 $2^{s - 1}$ 个，即把 $s$ 看成 $s$ 个1，然后插上 $s - 1$ 个隔板。那么有：

$$\begin{aligned} 2^{s - 1} &= \sum\limits_{g=1}^s f(s,g)
\\ &=\sum\limits_{g | s}f(s,g)
\\ &=\sum\limits_{g | s}f(s/g,1)
\end{aligned}$$

移一下项，得到：
$$ f(s,1)=2^{s - 1}-\sum\limits_{g|s,g>1}f(s / g,1) $$

设 $f[s]$ 表示 $f(s, 1)$ ，得到递推方程：
$$ f[s] =  2^{s - 1}-\sum\limits_{g|s,g>1}f[s/g]$$

直接做是 $O(n\log n)$ 的，但是容易知道有些位置的值是用不到的。开一个 `map` 储存 $f[]$ 数组，大力递推计算，参考杜教筛的复杂度，大约是 $O(n^{\frac{3}{4}})$，但是实际上跑得出奇的快。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;

#define LL long long
const int P = 1e9+7;

int x,y;

int qp(int a,int b){
    int r = 1;
    while(b){
        if(b & 1) r = (1ll * a * r) % P;
        a = (1ll * a * a) % P; b >>= 1;
    }
    return r;
}
map<int, int> f;
int dfs(int s){
    if(s == 1) return 1;
    if(f.count(s)) return f[s];
    int r = qp(2, s - 1);
    for(int g = 2;g * g <= s;g++){
        if(s % g) continue;
        if(g * g == s) r = (r - dfs(g) + P) % P;
        else r = ((r - dfs(s / g) - dfs(g)) % P + P) % P;
    }
    return f[s] = (r - 1 + P) % P;
}

int main()
{
    // freopen("_in.in", "r", stdin);

    scanf("%d%d", &x, &y);
    if(y % x) puts("0");
    else printf("%d", dfs(y / x));
}
```

---

## 作者：1saunoya (赞：7)

问多少个序列 $sum = x$  $gcd = y$

显然如果 $x$ 不是 $y$ 的倍数就是 0 了。

然后 $sum = x/y$, $gcd = 1$ 就出来了。

隔板法可以求出来有多少种方案数 $sum = x/y$。

$g_{sum} = 2^{sum} - 1$

这个里面会有 $gcd > 1$ 的情况。

设 $f_{sum}$ 是 $gcd = 1$ 的方案数。

那么其实 $g_x = \sum_{d|x} f_x$

根据反演。

$f_x = \sum_{d|x} g(\frac{x}{d}) \mu_d$

就做完了。

---

## 作者：vvauted (赞：4)

- [CF900D Unusual Sequences](https://www.luogu.com.cn/problem/CF900D)

数论套路题，考虑题意可转化为：

> 求一个和为 $\frac y x$ 的序列，使得其 $\gcd$ 为 $1$

相当于把整体除以 $\gcd$，找到一个更好处理等价问题。

如果不考虑 $gcd$ 的限制的话，和为 $k$ 的序列共有 $2^{k-1}$ 种，设和为 $k$ 且 $\gcd = 1$ 序列有 $f(k)$ 种，受上步转化的启发可得到和为 $k$ 且 $\gcd = d$ 的序列有 $f(\frac k d)$ 种，且 $d$ 只能为 $k$ 的因数，则可以写出：

$$\sum_{d\mid k} f(\frac k d) = 2 ^{k - 1}$$

考虑一个容斥：

$$f(k) = 2^{k-1} - \sum_{d\mid k, d\neq 1} f(\frac k d)$$

递归的求 $f$ 即可，显然只有 $k$ 的因数会被计算到，且单次求和复杂度是根号的，所以复杂度正确。

**code**
 
```cpp
#include <bits/stdc++.h>
#define int long long
#define Add(x, y) x = add(x, y)
#define Mul(x, y) x = mul(x, y)

std :: map <int, int> ans;
int x, y; const int mod = 1e9 + 7;
int mul(int x, int y) { return x * y % mod; }
int add(int x, int y) { return (x + y) % mod; }

int qpow(int x, int y) {
	int ans = 1;  while(y) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x), y >>= 1;
	} return ans;
}

int calc(int o) {
    if(o == 1) return 1;
    if(ans[o]) return ans[o];
    int res = calc(1); 
    for(int i = 2; i * i <= o; ++ i) {
        if(o % i) continue;
        Add(res, add(calc(i), (i * i != o) * calc(o / i))); 
    } return ans[o] = add(qpow(2, o - 1), -res);
}

signed main() {
    scanf("%lld%lld", &x, &y);
    if(y % x) return puts("0"); 
    printf("%lld", add(mod, calc(y / x)));
}
```


---

## 作者：C　C　A (赞：3)

$$\Large \rm [CF900D]Unusual~Sequences$$

$\quad$易知，所有的数都包含一个因数 $x$，故问题等价于，求有多少个数列满足 $\gcd(a_1,a_2,a_3,\cdots)=1$ 和 $\sum a_i=\frac{y}{x}$，此处为方便后续表达，令 $n=\frac{y}{x}$.

$\quad$令 $f(x)$ 表示 $x|\gcd(a_1,a_2,a_3,\cdots)$ 的方案数，则使用隔板法可得 $f(x)=2^{\frac{n}{x}-1}$.

$\quad$令 $g(x)$ 表示 $\gcd(a_1,a_2,a_3,\cdots)=x$ 的方案数，由 $g$ 的定义易知 ：

$$f(x)=\sum_{x~|~k}g(k)$$

$\quad$考虑将其变换成可以使用莫比乌斯反演的形式，令 $f'(x)=f(\frac{n}{x})~,~g'(x)=g(\frac{n}{x})$.

$$\because x~|~k\Longleftrightarrow \frac{n}{k}~\big|~\frac{n}{x}$$

$$\therefore f(x)=\sum_{\frac{n}{k}~|~\frac{n}{x}}g\left(\dfrac{n}{\frac{n}{k}}\right)$$

$$\therefore f'(x)=\sum_{d~|~x}g'(d)$$

$\quad$根据莫比乌斯反演的结论 ：

$$g'(x)=\sum_{d~|~x}\mu(d)f'\left(\frac{x}{d}\right)=\sum_{d~|~x}\mu(d)f(d)$$

$\quad$答案即为 $g(1)=g'(n)=\sum_{d~|~n}\mu(d)f(d)$，现在考虑如何计算 $g'(n)$.

$\quad$首先对 $n$ 进行质因数分解，得到 $n=p_1^{q_1}\times p_2^{q_2}\times \cdots \times p_{\omega(n)}^{q_{\omega(n)}}$，考虑到当 $d$ 存在一个平方因子时 $\mu(d)=0$，故对 $n$ 的质因数进行 $\rm dfs$，所有指数的枚举上界均为 $1$，而对于 $f(d)$ 直接快速幂计算即可。

$\quad$时间复杂度 $\Theta(\sqrt{n}+2^{\omega(n)}\log n)$.

$\quad PS:stO$ 仙 $Achtoria$，本题数据范围可以开到 $n\leqslant 10^{14}$，另外，如果使用 $\Theta(n^{\frac{1}{4}})$ 的分解质因数算法，则数据范围可以开到 $n\leqslant 10^{18}$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define dep(i, r, l) for (int i = r; i >= l; --i)

const int mod = 1e9 + 7;

int n, x, y, p[20], cnt, ans;

int Pow (int a, int k) {
	if (k == 0) return 1;
	if (k == 1) return a;
	int S = Pow(a, k >> 1);
	if (k & 1) return 1ll * S * S % mod * a % mod;
	else return 1ll * S * S % mod;
}

int main () {

	scanf("%d%d", &x, &y), n = y / x;
	if (y % x) return puts("0"), 0;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			p[++cnt] = i;
			while(n % i == 0) n /= i;
		}
	if (n > 1) p[++cnt] = n;
	n = y / x;
	
	dep(S, (1 << cnt) - 1, 0) {
		int mu = 1, d = 1;
		rep(i, 0, cnt - 1) if ((S >> i) & 1)
			mu = -mu, d *= p[i + 1];
		ans = (ans + mu * Pow(2, n / d - 1)) % mod;
	}
	printf("%d", (ans + mod) % mod);

	return 0;
}
```

---

## 作者：SSHhh (赞：2)

看了下面那么多 $dalao$ 的高端数学方法，蒟蒻决定贡献一种简单易行的方法：

我们先来考虑这个问题的**退化版**：给定你一个总和为 $y$ 的数列，问你把它分割成 $gcd$ 为 $x$ 的倍数有多少种不同的方法。

这个做法是很明显的：隔板法。相当于一共有 $y$ 个数，每 $x$ 个可以插一个板，总方法数当然就是 $2^{y/x-1}-1$ 。

现在让我们回归原来的问题：$gcd$ 为 $x$ 和 $gcd$ 为 $x$ 的倍数到底有什么区别呢？显然前者的答案等于 $gcd$ 为 $x$ 的倍数的答案减去 $gcd$ 为 $x$ 的 $2$倍、$3$ 倍… $n$ 倍的答案。

等等，这不就是一个容斥吗？推到这里，正解的做法就呼之欲出了：枚举 $y\div x$ 的所有质因子组合，然后根据所含的因子数量决定是加上还是减去，最后统计答案即可。

细节的话，貌似没什么，注意别写挂就行了吧（乖巧。。。

剩下就是代码了：

```cpp
#include<vector>
#include<iostream>
#define mod 1000000007
using namespace std;
int ans,prime[100005],num[100005],cnt=0;
vector<int> q,p;
long long qpow(long long x,int mi) {
	long long sum=1;
	while(mi) {
		if(mi&1)	sum=sum*x%mod;
		x=x*x%mod,mi>>=1;
	}
	return sum;
}
void shuffle(int N) {
	prime[0]=prime[1]=1;
	for(int i=2;i*i<=N;i++)
		if(prime[i])
			for(int j=i*2;j*j<=N;j++)
				prime[j]=1;
	for(int i=2;i*i<=N;i++)
		if(!prime[i])
			q.push_back(i);
}
int deal(int x)	//不要管他
{
	int sum=0;
	for(int i=0;i<q.size();i++)
		while(x%q[i]==0)
			x/=q[i],sum++;
	if(x!=1)	sum++;
	return (sum%2)?-1:1;
}
void work(int x)	//找质因子
{
	for(int i=0;i<q.size();i++)
		if(x%q[i]==0) {
			p.push_back(q[i]);
			while(x%q[i]==0)
				x/=q[i];
		}
	if(x!=1)	p.push_back(x);
}
int xx(int x)	//用质因子个数决定是加还是减
{
	int sum=0,las;
	for(int i=0;i<q.size();i++)
		if(x%q[i]==0) {
			sum++,las=q[i];
			while(x%q[i]==0)
				x/=q[i];
		}
	if(x!=1)	sum++;
	return sum==1?las:-1;
}
void dfs(int now,int x,int y)	//dfs 枚举质因子组合
{
	if(now==p.size()) {
		int sum=x;
		for(int i=1;i<=cnt;i++)
			sum*=num[i];
		int k=deal(sum/x);
		ans=(ans+k*(qpow(2,(y/sum-1))-1)+mod)%mod;
		return;
	}
	num[++cnt]=p[now];
	dfs(now+1,x,y);
	num[cnt--]=0;
	dfs(now+1,x,y);
}
int main()
{
	shuffle(1000000000);
	int x,y;
	cin>>x>>y;
	if(y%x!=0) {
		cout<<0;
		return 0;
	}
	else if(y==2*x || y==x) {
		cout<<1;
		return 0;
	}
	int gg=xx(y);
	if(gg!=-1 && x==1) { //特判要注意
		ans=(ans+(qpow(2,y/x-1)-1)+mod)%mod;
		ans=(ans-(qpow(2,y/gg-1)-1)+mod)%mod;
		cout<<ans;
		return 0;
	}
	if(y/x<=1e6) { //不用管这个 if
		for(int i=x;i*2<=y;i+=x)
		{
			if(y%i==0)
			{
				int k=deal(i/x);
				ans=(ans+k*(qpow(2,(y/i-1))-1)+mod)%mod;
			}
		}
	}
	else {	//这才是正儿八经的容斥做法
		int now=y/x;
		work(now);
		dfs(0,x,y);
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：little_sun (赞：2)

# 题解 CF900D 【Unusual Sequences】
可以发现如果$x$不整除$y$那么肯定无解

不然我们可以发现其实求的就是和为$y/x$且$gcd(a_1,a_2,\cdots,a_n)=1$的序列个数

容易发现所有和为$y$的序列个数为$2^{n-1}$

而所有$gcd$不为$1$的序列，把每个数除以$gcd$,就又回到原题了

所以枚举每个可能的$gcd$(约数)，递归计算即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
const ll mod = 1e9 + 7;
std::map<int, int> m;
std::vector<int> v, vec;
int fast_pow(ll a, ll n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = (1ll * ret * a) % mod;
        a = (1ll * a * a) % mod;
        n >>= 1;
    }
    return ret;
}
int solve(int x)
{
    if (m[x])
        return m[x];
    if (x == 1)
    {
        m[x] = 1;
        return x;
    }
    int sum = 0;
    int s = sqrt(x);
    for (int i = 1; i <= s; i++)
    {
        if (x % i == 0)
        {
            if (i == 1 || i * i == x)
                sum = (sum + solve(i)) % mod;
            else
                sum = (sum + solve(i) % mod + solve(x / i) % mod) % mod;
        }
    }
    sum = (fast_pow(2, x - 1) - sum + mod) % mod;
    m[x] = sum;
    return sum;
}
int main()
{
    ll x, y;
    std::cin >> x >> y;
    if (y % x != 0)
        return 0 * printf("0");
    y /= x;
    std::cout << solve(y);
    return 0;
}
```

---

## 作者：Exschawasion (赞：1)

这题用 dp 的思想也可以引出正解。

首先很显然地，$\text{gcd}$ 为 $x$ 的数列和一定是 $y$ 的因子，所以 $x$ 不整除 $y$ 的话答案就是 $0$。

反之，我们可以将数列里的每个数都除以 $x$，则总和变为 $\frac{y}{x}$，公约数变为 $1$。令 $S=\frac y x$，则问题转化为：求数列总和为 $S$ 且公约数为 $1$ 的数列的数量。

一个比较套路的思路，考虑容斥。

根据上面的结论，如果对于一个 $j$  存在 $i=j\times k$，那么把满足和为 $j$ 的数列都乘上 $k$ 即可得到和为 $i$ 的数列。

设 $f[i]$ 表示总和为 $i$ 的公约数为 $1$ 的数列个数。则有：

$$f[i]=2^{i-1}-\sum_{d|i}f[\frac{x}{d}]$$

边界：$f[1]=1$。

意义显然：$2^{i-1}$ 是不考虑公约数的划分总数（可自行推导），因为如果 $i$ 是 $d$ 的倍数，那么 $f[\frac{x}{d}]$ 的公约数就会是 $d$ 而不是 $1$。因此要减去。

注意到 $x,y \leq 10^9$，数组开不下，要开一个 `map` 来保存。这个算法效率大约是 $O(V\log V)$ 的。

据说可以反演算这个式子，但是 dp 效率也不低（？）。

另外，不得不提的是：关于记忆化搜索和递推计算 dp 转移式效率上的差异，递推计算的效率瓶颈之一是频繁存取状态，因此如果使用 `map`（存取状态代价高），那么还是建议使用记忆化搜索。

代码中提供了记忆化搜索和递推计算的两个版本，可自行比较效率：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
inline int qpow(int x,int y){
	int ans=1;
	for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ans=1ll*ans*x%mod;
	return ans;
}
map<int,int>f;
int dp2(int x){
	if(x==1)return 1;
	if(f[x])return f[x];
	int lim=sqrt(x);
	int t=qpow(2,x-1);
	for(int i=1;i<=lim;i++){
		if(x%i==0){
			t=(t-dp2(i))%mod;
			if(i!=1&&i*i!=x)t=(t-dp2(x/i))%mod;
		}
	}
	return f[x]=(t%mod+mod)%mod;
}
void dp(int v){
	f[1]=1;
	for(int x=2;x<=v;x++){
		int lim=sqrt(x);
		int t=qpow(2,x-1);
		for(int i=1;i<=lim;i++){
			if(x%i==0){
				t=(t-f[i])%mod;
				if(i!=1&&i*i!=x)t=(t-f[x/i])%mod;
			}
		}
		f[x]=(t%mod+mod)%mod;
	}
	cout<<f[v]<<endl;
}
int main(){
	int x,y;cin>>x>>y;
	if(y%x)return puts("0"),0;
	cout<<dp2(y/x)<<endl;
//	dp(y/x);
	return 0;
}
```


---

## 作者：_Fontainebleau_ (赞：1)

### 题意

- 给定 $x,y$，满足 $\sum\limits_{i=1}^n a_i=y,\gcd\left(a_1,a_2,\dots,a_n\right)=x,1\le a_i$ 的数列 $\left\{a_i\right\}$ 的个数。
- $1\le x,y\le 10^9$。

### 做法


容易发现，所有的 $a_i$ 都有一个因数 $x$，所以原问题等价于求满足 $\sum\limits_{i=1}^n a_i=\dfrac yx,\gcd\left(a_1,a_2,\dots,a_n\right)=1$ 的数列个数。不妨令 $k=\dfrac yx$。

这样有什么好处呢？$\gcd$ 变成 $1$ 了！

令 $g\left(x\right)$ 表示 $\gcd\left(a_1,a_2,\dots,a_n\right)=x$ 的方案数。此时答案就是 $g(1)$。
怎么去算 $g$ 呢？

考虑这个问题的退化版：给定 $x,y$，满足 $\sum\limits_{i=1}^n a_i=y,x\mid \gcd\left(a_1,a_2,\dots,a_n\right)$ 的数列 $\left\{a_i\right\}$ 的个数。

相当于对于 $1$ 到 $y$ 这些数字中，选择一些 $x$ 的倍数。因为 $1$ 到 $y$ 中一共有 $\frac {y}{x}$ 个数是 $x$ 的倍数。那么答案很显然就是 $2^{\frac {y}{x} -1}$（至少要选一个）。

我们令 $f(x)$ 表示 $x\mid \gcd\left(a_1,a_2,\dots,a_n\right)$ 的方案数，根据上面的问题，我们知道 $f(x)=2^{\frac kx-1}$。

$$f(x)=\sum_{x\mid d}g(d)$$

似乎可以看出一点反演的端倪。我们只要稍微变一变就可以。

令 $f'\left(x\right)=f\left(\dfrac kx\right),g'\left(x\right)=g\left(\dfrac kx\right)$。

因为 $x\mid d \Longleftrightarrow {\dfrac kd} \mid {\dfrac kx}$，所以 $\displaystyle f(x)=\sum_{\frac kd \mid \frac kx}g\left(\dfrac {k}{\frac kd}\right)$。$d \gets\frac kd,x\gets \frac kx$，则有 $f'\left(x\right)=\sum\limits_{d\mid x}g'(x)$。

所以

$$g'(x)=\sum_{d\mid x}\mu\left(d\right)f'\left(\dfrac xd\right)$$

答案就是 $ g(1)=g'(k)=\sum\limits_{d\mid k}\mu\left(d\right)f'\left(\dfrac kd\right)=\sum\limits_{d\mid k}\mu(d)f(d)$。

注意：这里 C　C　A 神仙的题解有一点小问题，只有算 $g'(k)$ 时 $f'\left(\dfrac kd\right)$ 才能转化成 $f\left(d\right)$，其他时候 $f'\left(\dfrac xd\right)$ 是不能的。~~虽然这不影响最终答案。~~

怎么算 $g'(k)$？

先对 $k$ 进行标准分解， $k=p_1^{\alpha_1}p_2{^{\alpha_2}}\cdots p_t^{\alpha_t}$。当 $d$ 存在平方因子时， $\mu(d)=0$，直接对 $k$ 的质因数进行 dfs 即可。

复杂度大概是 $O\left(\sqrt k +\frac{\sqrt k}{\log k}+k^{\frac 13}\log k\right)$。

$O\left(\sqrt k\right)$ 是线性筛，如果多测的话，应该会跑的比较快一点。

如果不是多测，但 $n$ 特别大，可以尝试 Pollard-Rho，但是这都不是本题的核心了。

**不同于其他莫反题，都是化出 $\left[x=1\right]$ 再 Mobius inverse 的，本题是在一个大式子上运用了莫反的结论。**

### 代码


```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
bitset<31625> used;
int prime[31625],cnt;
int p[15],pn;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline void sieve(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++)
		{
			used[prime[j]*i]=1;
			if(!(i%prime[j]))	break;
		}
	}
}
inline int f(int x,int y)
{
	int p=x,res=1;
	while(y)
	{
		if(y&1)	res=1ll*res*p%mod;
		p=1ll*p*p%mod;y>>=1;
	}
	return res;
}
inline int add(int x)
{
	return x>=mod?x-mod:x;
}
int dfs(int u,int mu,int k)
{
	if(!u)	return 1ll*mu*f(2,k-1)%mod;
	return add(dfs(u-1,mu,k)+dfs(u-1,mod-mu,k/p[u]));
}
int main()
{
	int x=read(),y=read();
	if(y%x)	return puts("0"),0;
	y/=x;
	sieve(31623);
	int tmp=y;
	for(int i=1;prime[i]*prime[i]<=y;i++)
		if(!(y%prime[i]))
		{
			p[++pn]=prime[i];
			while(!(y%prime[i]))	y/=prime[i];
		}
	if(y!=1)	p[++pn]=y;
	int ans=dfs(pn,1,tmp);
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：木木！ (赞：1)

思路是莫比乌斯反演，把式子中的 $[\gcd(x_i)=1]$ 拆成 $\mu(d)[d|\gcd(x_i)]$。

只是想说明一下在计算一个数的所有因子的 $\mu$ 的时候，可以直接 dfs。在 dfs 的过程中只需要枚举每个可能的质数取或不取，如果取两个及以上的话系数肯定为 0。

时间复杂度约为 $\Theta(\sqrt{y}+\frac{\sqrt{y}}{\log y}+y^{\frac 13}\log y)$，跑不满。$\sqrt{y}$ 的复杂度来源于线性筛，所以可能会在多组数据上表现更优秀。

常数大大减小的同时代码难度也很小（拆出所有质因数之后 dfs 过程只有两行）。

附 AC 代码：

```cpp
#include <cstdio>
using namespace std;

#define mod 1000000007

int pfix(int x) { return x>=mod ? x-mod : x; }

int qpow(int a,int b)
{
	int res = 1;
	for(; b; b>>=1)
	{
		if(b&1) res = 1LL*res*a%mod;
		a = 1LL*a*a%mod;
	}
	return res;
}

int isprime[32005];
int primes[32005];
int primen;

void liner_seive(int n)
{
	for(int i=2; i<=n; ++i)
	{
		isprime[i] = 1;
	}
	for(int i=2; i<=n; ++i)
	{
		if(isprime[i])
		{
			primes[++primen] = i;
		}
		for(int j=1; i*primes[j]<=n; ++j)
		{
			isprime[i*primes[j]] = 0;
			if(!(i%primes[j])) break;
		}
	}
}

int pi[15];

int dfs(int c,int xs,int val)
{
	if(!c) return 1LL*xs*qpow(2,val-1) %mod;
	return pfix(dfs(c-1,xs,val) + dfs(c-1,mod-xs,val/pi[c]));
}

int main()
{
	int x,y;
	scanf("%d%d",&x,&y);
	if(y%x) return printf("0\n"),0;
	y /= x;

	liner_seive(31999);

	int pn = 0;
	int cury = y;
	for(int i=1; primes[i]*primes[i]<=y; ++i)
	{
		if(!(y%primes[i]))
		{
			pi[++pn] = primes[i];
			while(!(y%primes[i])) y/=primes[i];
		}
	}
	if(y!=1) pi[++pn] = y;

	printf("%d\n",dfs(pn,1,cury));
}
```

---

## 作者：Weng_Weijie (赞：1)

首先发现如果$x \nmid y$ 肯定无解

令$f(x)$为$gcd=x$,和$=y$的数列个数

那么直接求$f(x)$不好求

设$g(x)$为$x|gcd$,和$=y$的数列个数

可以由插板法得到

那么$g(x)=2^{\frac yx-1}$

$$f(x)=\displaystyle\sum_{x|k,k|y}g(k)\mu(\frac kx)$$

$$=\displaystyle\sum_{k\mid\frac yx}\mu(k)2^{\frac{y}{ix}-1}$$

然后就可以算了

```cpp
#include <cstdio>
#include <vector>
int x, y;
const int mod = 1000000007;
typedef long long LL;
int pow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = static_cast<LL> (x) * x % mod)
        if (y & 1) ans = static_cast<LL> (ans) * x % mod;
    return ans;
}
typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;
typedef std::vector<int> VI;
VPII d;
VI p;
void up(int &x, int y) { if ((x += y) >= mod) x -= mod; }
void dfs(int dep, int val, int miu) {
    if (dep == p.size()) return d.push_back(std::make_pair(val, miu));	
    dfs(dep + 1, val, miu);
    dfs(dep + 1, val * p[dep], mod - miu);
}
void solve() {
    int k = y / x, tmp = k;
    for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
        int cnt = 0;
        while (tmp % i == 0) ++cnt, tmp /= i;
        p.push_back(i);
    }
    if (tmp > 1) p.push_back(tmp);
    dfs(0, 1, 1);
    int ans = 0;
    for (VPII::iterator it = d.begin(); it != d.end(); ++it) {
        up(ans, static_cast<LL> (it->second) * pow(2, k / it->first - 1) % mod);
    }
    std::printf("%d\n", ans);
}
int main() {
    std::scanf("%d%d", &x, &y);
    if (y % x) std::printf("%d\n", 0);
    else solve();
    return 0;
}
```

---

## 作者：chihik (赞：1)

建议先做 [CF439E](https://www.luogu.com.cn/problem/CF439E)。

$$\sum_{n=1}^y\sum_{i_1=1}^y\sum_{i_2=1}^y...\sum_{i_n=1}^y [\sum{a_i}=y][\gcd{a_i}=x]$$

$$\sum_{n=1}^y\sum_{i_1=1}^{\frac{y}{x}}\sum_{i_2=1}^\frac{y}{x}...\sum_{i_n=1}^\frac{y}{x} [\sum{a_i}=\frac{y}{x}][\gcd{a_i}=1]$$

$$\sum_{n=1}^y\sum_{d|\frac{y}{x}} \mu(d) \sum_{i_1=1}^{\frac{y}{xd}}\sum_{i_2=1}^{\frac{y}{xd} }...\sum_{i_f=1}^{\frac{y}{xd}} [\sum{a_i}=\frac{y}{xd}]$$

后面枚举 $i$ 的过程可以看作将 $\frac{y}{xd}$ 个相同的球放进 $n$ 个不同的盒子，且不能有空盒的方案数，利用插板法可得： $\binom{\frac{y}{xd}-1}{n-1}$

那么原式即为：

$$\sum_{n=1}^y\sum_{d|\frac{y}{x}} \mu(d) \binom{\frac{y}{xd} - 1 }{n-1}$$

$$\sum_{d|\frac{y}{x}}\mu(d)  \sum_{n=1}^y\binom{\frac{y}{xd} - 1 }{n-1}$$

$$\sum_{d|\frac{y}{x}}\mu(d)  \sum_{n=1}^{\frac{y}{xd}}\binom{\frac{y}{xd} - 1 }{n-1}$$

$$\sum_{d|\frac{y}{x}}\mu(d)  \sum_{n=1}^{\frac{y}{xd}}\binom{\frac{y}{xd} - 1 }{n-1}$$

$$\sum_{d|\frac{y}{x}}\mu(d)  2^{\frac{y}{xd}-1}$$


```cpp
#include <cstdio>

const int MAXN = 1e5 , Mod = 1e9 + 7;

int Quick_pow( int x , int po ) { int p = 1; for( ; po ; po >>= 1 , x = 1ll * x * x % Mod ) if( po & 1 ) p = 1ll * p * x % Mod; return p; }
int Inv( int x ) { return Quick_pow( x , Mod - 2 ); }

int mu( int n ) {
	int Ans = 1;
	for( int i = 2 ; i * i <= n ; i ++ )
		if( n % i == 0 ) {
			int p = 0; for( ; n % i == 0 ; n /= i ) p ++;
			if( p > 1 ) return 0;
			Ans *= -1;
		}
	if( n > 1 ) Ans *= -1;
	return Ans;
}

int x , y;
int main( ) {
	scanf("%d %d",&x,&y);
	if( y % x != 0 || y < x ) return printf("0\n") & 0;

	int Ans = 0;
	for( int d = 1 ; d * d <= y / x ; d ++ )
		if( y / x % d == 0 ) {
			Ans = ( Ans + mu( d ) * Quick_pow( 2 , y / x / d - 1 ) % Mod ) % Mod;
			if( d * d != y / x )
				Ans = ( Ans + mu( y / x / d ) * Quick_pow( 2 , d - 1 ) % Mod ) % Mod;
		}
	printf("%d\n", ( Ans + Mod ) % Mod );
	return 0;
}
```

---

## 作者：fanypcd (赞：0)

萌新的容斥入门题。

易于发现题目可以转化为求满足以下条件的正整数序列个数：

- $\sum \limits_{i=1} ^{n} a_i = \frac {y}{x} \mid \gcd \limits_{i=1} ^{n} a_i = 1$

记 $f(x)$ 表示和为 $x$，gcd 为 1 的正整数序列个数，发现不好直接求出，考虑补集转化。

记 $g(x)$ 表示和为 $x$ 的正整数序列个数，则枚举划分的个数 $n$，转化为不定方程的正整数解的个数，易得 $g(x) = \sum \limits_{i=1} ^{n} {n - 1 \choose i} = 2^{n - 1}$。

那么枚举不合法的序列（公约数 d 满足 $1 < d \leq x$，则这种序列的个数为 $f(\frac{x}{d})$），则：

$$f(x) = g(x) - \sum \limits_{d | x,d > 1}f(\frac{x}{d})$$

复杂度的话，每个数能递归调用的参数就是它的所有约数，不会超过 30 个。

用 map 记忆计算过的位置的答案即可。

$O(30 \times \sqrt n \times \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 1e9 + 7;
int qpow(int a, int b)
{
	int ans = 1;
	while(b)
	{
		if(b & 1)
		{
			ans = 1ll * ans * a % mod;
		}
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
map<int, int> mem;
int solve(int x)
{
	if(mem.count(x))
	{
		return mem[x];
	}
	int ans = qpow(2, x - 1);
	for(int i = 2; i * i <= x; i++)
	{
		if(x % i == 0)
		{
			ans = (ans - solve(x / i) + mod) % mod;
			if(x / i != i)
			{
				ans = (ans - solve(i) + mod) % mod;
			}
		}
	}
	ans = (ans - 1 + mod) % mod;
	return mem[x] = ans;
}
signed main()
{
	int x, y;
	read(x), read(y);
	if(y % x)
	{
		printf("0");
		return 0;
	}
	mem[1] = 1;
	printf("%d", solve(y / x));
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

萌萌题。首先如果 $y$ 不是 $x$ 的倍数，答案显然为 $0$。于是 $y \gets \dfrac{y}{x}$，问题变成了有多少个序列，序列的 $\gcd$ 为 $1$，并且序列和为 $y$。

先扔掉 $\gcd$ 为 $1$ 的限制条件考虑怎么做。隔板法得到：

$$
\sum_{i=0}^{y-1} \dbinom{y-1}{i} = 2^{y-1}
$$

然后枚举 $\gcd$，直接容斥，根据莫比乌斯反演，容斥系数显然是 $\mu$。于是暴力枚举 $y$ 的因数，暴力计算 $\mu$ 函数即可。时间复杂度 $O(n^{\frac{3}{4}})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL QuickPow(LL x,LL p)
{
	if(x==0)	return 0;
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
LL mu(LL x)
{
	LL st=1;
	for(LL i=2;i*i<=x;++i)
	{
		if(x%i==0)
		{
			x/=i;
			st=MOD-st;
			if(x%i==0)	return 0;
		}
	}
	if(x!=1)	st=MOD-st;
	return st;
}
LL calc(LL sum){return QuickPow(2,sum-1);}
LL x,y;
int main(){
	scanf("%lld %lld",&x,&y);
	if(y%x)	return puts("0")&0;
	y/=x;
	LL ans=0
	for(LL i=1;i*i<=y;++i)
	{
		if(y%i==0)
		{
			ans=(ans+mu(i)*calc(y/i)%MOD)%MOD;
			if(i*i!=y)	ans=(ans+mu(y/i)*calc(i)%MOD)%MOD;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

对于 $\gcd(a_1, a_2, \cdots, a_n) = x$, 必有 $\gcd(\frac{a_1}{x}, \frac{a_2}{x}, \cdots, \frac{a_n}{x}) = 1$.  
此时 $a_1 + a_2 + \cdots + a_n = \frac{y}{x}$ .  
对于 $x \nmid y$ 的情况显然不存在合法方案。  
对于 $x \mid y$ : 根据上面说的可以等价到 $\gcd(a_1, a_2, \cdots, a_n) = 1$ , $a_1 + a_2 + \cdots + a_n = \frac{y}{x}$。我们设这个答案为 $f(\frac{y}{x})$。  
考虑求 $f(\frac{y}{x})$。  
将 $\frac{y}{x}$ 的数值划分为若干($1, 2, \cdots, n-1$)个正数的合是一个经典的组合问题, 总的方案数为 $\sum_{i=1}^{\frac{y}{x}-1}\binom{\frac{y}{x}-1}{i} = 2^{\frac{y}{x}-1}$ 。 这些区间包含 $\gcd(a_1, a_2, \cdots, a_n) = d$ 的所有情况, 其中 $d \mid \frac{y}{x}$ 。而这些情况的方案数又可以等价于 $f(\frac{y}{dx})$ 。  
于是有  
$$
\sum_{d \mid \frac{y}{x}} f(d) = 2^{\frac{y}{x}-1}
$$
设 $g(x) = 2^{x-1}$ , 有  
$$
f * 1 = g
$$
运用莫反公式
$$
f*1*\mu = g*\mu \to f = g* u
$$
于是可以转为求单点的值。  
$f(\frac{y}{x}) = \sum_{d \mid \frac{y}{x}}{\mu(d)2^{\frac{y}{x}-1}}$  

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100010, Mod = 1000000007;
inline int Inc(int x, int y) { return (x+=y) < Mod ? x : x - Mod; }
inline int Dec(int x, int y) { return (x-=y) < 0 ? x + Mod : x; }
inline int Mul(int x, int y) { return 1ll * x * y % Mod; }
inline int Power(int x, int y) {
	int ret = 1;
	for(; y; y >>= 1) {
		if(y&1) ret = Mul(ret, x);
		x = Mul(x, x);
	}
	return ret;
}
int Prime[N], vp[N], tot;
void seive(int n) {
	for(int i = 2; i <= n; ++i) {
		if(!vp[i]) Prime[++tot] = i;
		for(int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
			vp[i*Prime[j]] = 1;
			if(i % Prime[j] == 0) break;
		}
	}
}

int mu(int n) {
	if(n == 1) return 1;
	int ret = 1;
	for(int i = 1, j = Prime[i]; i <= tot && 1ll * j * j <= n; j = Prime[++i]) {
		if(n % (j*j) == 0) return 0;
		if(n % j == 0) ret = -ret, n /= j;
	}
	ret = n == 1 ? ret : -ret;
	return ret < 0 ? ret + Mod : ret;
}

int main() {
	seive(N - 10);
	int x, y;
	cin >> x >> y;
	if(y % x != 0) {
		cout << 0 << endl;
		return 0;	
	}
	int ans = 0, n = y / x;
	for(int i = 1; 1ll * i * i <= n; ++i) if(n % i == 0) {
		ans = Inc(ans, Mul(mu(i), Power(2, n/i-1)));
		if(i * i != n) ans = Inc(ans, Mul(mu(n/i), Power(2, i-1)));
	}
	cout << ans << endl;
	return 0;
}
```

---

