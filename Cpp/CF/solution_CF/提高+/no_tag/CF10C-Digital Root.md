# Digital Root

## 题目描述

不久前，Billy 遇到了这样一个问题：给定三个自然数 $A$、$B$ 和 $C$，它们都在区间 $[1,N]$ 内，要求判断等式 $AB=C$ 是否成立。最近，Billy 学习了数字根的概念。我们需要提醒你，一个数 $x$ 的数字根 $d(x)$ 是该数各位数字之和 $s(x)$，如果 $s(x) \leq 9$，那么 $d(x) = s(x)$，否则 $d(x) = d(s(x))$。例如，数字 $6543$ 的数字根计算如下：$d(6543) = d(6+5+4+3) = d(18) = 9$。Billy 发现，两个数乘积的数字根等于这两个数数字根的乘积的数字根，即 $d(xy) = d(d(x)d(y))$。于是他想到如下解法：计算数字根并判断该条件是否成立。然而，Billy 怀疑这个条件是否充分。因此，他请你找出有多少组 $A$、$B$、$C$ 满足题意，使得 Billy 提出的算法会出错。

## 说明/提示

对于第一个样例，满足条件的三元组为 $(3,4,3)$ 和 $(4,3,3)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
6
```

# 题解

## 作者：Fading (赞：6)

比较水的一道题。

首先我们知道一个简单的结论

$$a \equiv s(a) (\text{mod}\ 9)$$

这个很好证明，然后我们就知道 $d(x)$ 的值了

很显然 $d$ 的值域是$[1,9](d(x)∈\mathbb{Z})$

我们用数学归纳法证明

$$d(x)=\left\{\begin{aligned}x\ \text{mod}\ 9\ (x\ \text{mod}\ 9\ !=0\ )\\9\ (x\ \text{mod}\ 9=0\ )\\\end{aligned}\right.$$

$x∈[1,9]$，显然$...$

假设对于$y<x$的$y$均成立

若$s(x)$不是$9$的倍数

那么$d(x)=d(s(x))=s(x)\ \text{mod}\ 9=x\ \text{mod}\ 9$

否则同理。。。

所以证完了

然后就很水了

统计$[1,n]$有多少个数满足$d(x)=1,2,3,...,9$

暴力枚举$[1,9]$就好了

最后会多出$a\times b=c$的答案

减掉就好了

个数就是$a\times b=c$的解数

如果$a$固定，解数$=\lfloor \frac n a\rfloor$

所以等价于求$\sum_{i=1}^n\lfloor\frac ni\rfloor$

随便整除分块一下就好了

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll ans;
inline ll d(ll a){
    return (a%9)?(a%9):9;
}
ll cnt[10],n,ansx;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cnt[d(i)]++;
    }
    for (int i=1;i<=9;i++){
        for (int j=1;j<=9;j++){
            for (int k=1;k<=9;k++){
                if (i*j%9==k%9){
                    ans+=cnt[i]*cnt[j]*cnt[k];
                }
            }
        }
    }
    for (ll l=1,r;l<=n;l=r+1){
        r=min(n,n/(n/l));
        ans-=(n/l)*(r-l+1);
    }
    cout<<ans;
}
```


---

## 作者：xiaorui2007 (赞：2)

首先，我们知道：
$$x\equiv s(x)\pmod 9$$

已知函数:
$$d(x)=\begin{cases}s(x)&s(x)\leqslant9\\d(s(x))&s(x)>9\end{cases}$$

可以看出 $d(x)$ 相当于 $s(s(\dots s(x)\dots))$，得出：
$$x\equiv d(x)\pmod 9$$

因此，
$$d(c)=d(d(a)d(b))\Leftrightarrow c\equiv d(a)d(b)\pmod 9\Leftrightarrow c\equiv ab\pmod 9$$

于是，题目变成了这样：给定一正整数 $n$，求满足 $\begin{cases}1\leqslant a,b,c\leqslant n\\c\ne ab\\c\equiv ab\pmod 9\end{cases}$ 的三元正整数对 $(a,b,c)$ 的数量。

显而易见，$c=ab\Rightarrow c\equiv ab\pmod 9$。  
我们可以先求出 $c\equiv ab\pmod 9$ 的组数，再减去 $c=ab$ 的组数。

---

**满足 $c\equiv ab\pmod 9$ 的组数**

$\kern{17pt}$ 用 $s_i$ 表示 $[1,n]$中被$9$除余$i$的数的个数。  
$\kern{17pt}$ 枚举 $a\mod9$，$b\mod9$ 即可。  
$\kern{17pt}$ 答案为 $\sum\limits_{i=0}^{8}{\sum\limits_{j=0}^{8}{s_is_js_{(ij\bmod9)}}}$。

---

**满足 $c=ab$ 的组数**

$\kern{17pt}$ 设满足 $c=ab$ 的组数为 $sum$，则：  
$$\begin{aligned}(1)\kern{10pt}sum&=\sum\limits_{a=1}^{n}{\left\lfloor\dfrac{n}{a}\right\rfloor}\\(2)\kern{10pt}sum&=\sum\limits_{c=1}^{n}{\sum\limits_{a|c}^{}{1}}\end{aligned}$$

$\kern{17pt}$ 先看 $(1)$，我们可以求 $1$ 到 $n$ 中 $1$ 的倍数的个数、$2$ 的倍数的个数 $\dots n$ 的倍数的个数之和就行，直接算即可，时间复杂度 $O(n)$ 。

$\kern{17pt}$ 能不能更快？

$\kern{17pt}$ 假设CF把 $n$ 的范围改到了 $10^{12}$ ，我们还能过此题吗？  
$\kern{17pt}$ 能！  
$\kern{17pt}$ 来看 $(2)$，这样需要计算 $1$ 到 $n$ 的所有数的因数个数和。
假设 $x$ 为 $n$ 的因数，那么 $\dfrac{n}{x}$ 也一定为 $n$ 的因数，那么 $n$ 的因数可以分为三部分，一部分小于 $\sqrt{x}$，一部分等于 $\sqrt{x}$，一部分都大于 $\sqrt{x}$。基于 $(1)$，我们也就只需要计算 $\sum\limits_{i=1}^{\left\lfloor\sqrt{x}\right\rfloor}{\dfrac{x}{i}}$ 的数值，然后再乘以 $2$，再减去 $\left\lfloor\sqrt{x}\right\rfloor$。  
$\kern{17pt}$ 但是，仔细看一下不难发现，对于小于 $\left\lfloor\sqrt{x}\right\rfloor$ 的因数，每个因数我们都多计算了 $\left\lfloor\sqrt{x}\right\rfloor$ 个，综合前面等于 $\left\lfloor\sqrt{x}\right\rfloor$ 的情况，也就是多计算了 $\left\lfloor\sqrt{x}\right\rfloor$ 个$\left\lfloor\sqrt{x}\right\rfloor$，所以最后需减去 $\left\lfloor\sqrt{x}\right\rfloor^2$。  
得：$sum=2\sum\limits_{i=1}^{\left\lfloor\sqrt{x}\right\rfloor}{x/i}-\left\lfloor\sqrt{x}\right\rfloor^2$。  
[解释来源](https://blog.csdn.net/u011787439/article/details/82183783?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-9.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-9.channel_param)  
时间复杂度 $O(\sqrt{n})$。利用算式 $(2)$ 的我把时间卡到了 $90$ ms。

---

**代码**

```cpp
#include<bits/stdc++.h>					//for 1
using namespace std;
int n;
long long s[10],ans;					//注意开long long
										//input:1000000
int main()								//output:111111074060178115
{
	cin>>n;
	for(int i=0;i<=8;i++)				//s[i]记录1~n中%9=i的数的个数
		s[i]=n/9;
	for(int i=n%9;i>=1;i--)
		s[i]++;
	for(int i=0;i<=8;i++)
		for(int j=0;j<=8;j++)
			ans+=s[i]*s[j]*s[i*j%9];	//求出c≡ab(mod 9)的组数
	for(int i=1;i<=n;i++)
		ans-=n/i;						//(1)
	cout<<ans<<endl;
	return 0;
}
```

```cpp
#include<bits/stdc++.h>					//for 2 相同处不作注释
using namespace std;
int n;
long long s[10],ans;

int main()
{
	cin>>n;
	for(int i=0;i<=8;i++)
		s[i]=n/9;
	for(int i=n%9;i>=1;i--)
		s[i]++;
	for(int i=0;i<=8;i++)
		for(int j=0;j<=8;j++)
			ans+=s[i]*s[j]*s[i*j%9];
	int t=sqrt(n);
	for(int i=1;i<=t;i++)
		ans-=n/i*2;						//(2)
	cout<<ans+t*t<<endl;				//注意+t*t
	return 0;
}
```

---

## 作者：sgl654321 (赞：1)

这还有蓝题，这还有 2000。评个下位黄算了。远古题，难评。

题目大意不想讲。

## 解题思路
首先你观察 $d(x)$ 是对一个数不停累加各位数字，最终得到的结果。这个东西其实就是 $x \bmod 9$，特别地当 $9\mid x$ 时 $d(x) = 9$。

然后找到 $d(c) = d(d(a)\times d(b))$ 其实就是找到 $c \equiv ab \pmod 9$。

我们枚举 $a,b,c$ 模 $9$ 的余数 $a_1,b_1,c_1$，计算出有多少 $[1,n]$ 之间的数模 $9$ 分别余 $a_1,b_1,c_1$ 即可。

另外题意要求 $ab\not =c$，我们先不考虑这个算出答案，再把这一部分减掉就行了。这个也很好算，枚举 $a$，算出有多少 $b$ 满足 $ab\le n$ 就行了。这个数其实就是 $\sum_{a=1}^n\lfloor \dfrac{n}{a}\rfloor$。

$n\le10^6$ 甚至不用除法分块。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define maxm 400010
using namespace std;
typedef long long ll;
ll n, ans;
ll work(ll x, ll y){
	if(x == 0) return y / 9;
	else y -= x;
	
	if(y < 0) return 0;
	return y / 9 + 1;
} 
int main(){
	cin >> n;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			int k = i * j % 9;
		//	cout << i << ' ' << j << ' ' << k << ":";
			ans += work(i, n) * work(j, n) * work(k, n); 
		//	cout << ans << endl;
		}
	for(int i = 1; i <= n; i++)
		ans -= n / i;
	cout << ans << endl;				
	return 0;
}


```

---

## 作者：封禁用户 (赞：0)

## 思路

一道数学题，这蓝 tag 是假的。

题目上的函数 $d(x)$ 翻译过来就是：

 $d \left( x \right) = \begin{cases} s\left( x \right)  & \text{ if } s \left( x \right) \le 9 \\ d \left( s \left( x \right) \right)  & \text{ if } s \left( x \right) > 9 \end{cases}$ 

很好想到 $d \left( x \right)$ 就是 $x$ 套在无限个 $s$ 函数里面。

又因为 $x \equiv s\left(x\right) \pmod{9} $，则很容易得出 $x \equiv d\left(x\right) \pmod{9} $。

再来看题目，思路就变得清晰了。$d\left(c\right)=d\left(d\left(a\right)d\left(b\right)\right)$ 就可转化为 $ab \equiv c \pmod{9} $，但不满足 $ab = c$。于是利用容斥原理就解决了这道题。

## code

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;

int read() {
	int ret = 0, f = 1;char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -f;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		ret = (ret << 3) + (ret << 1) + (ch ^ 48);
		ch = getchar();
	}
	return ret * f;
}

int n, ans, d[10];
signed main() {
    n = read();
    for (int i = 1;i <= n;i++) d[i % 9]++;
    for (int i = 0;i < 9;i++) for (int j = 0;j < 9;j++) ans += d[i] * d[j] * d[i * j % 9];
    for (int i = 1;i <= n;i++) ans -= n / i;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：DDF_ (赞：0)

## 题解

我的小学老师曾经说过：判断一个数是 $9$ 的倍数，就是将其每个位加起来是否是 $9$ 的倍数，而这个判定的原理是 $10 \equiv 1 \pmod 9$。所以对于任意数字 $i$，有 $s(i) \equiv i \pmod 9$。

以此类推，$d(i) \equiv i \pmod 9$。

又因为 $d(i)$ 是一位数，所以题目中对 $a,b,c$ 的要求可转化为 $a \times b \equiv c \pmod 9$ 且 $a \times b \not = c$。

易证 $a \times b = c$ 是 $a \times b \equiv c \pmod 9$ 方案的子集。

所以可以求 $a \times b \equiv c \pmod 9$ 的方案数，然后减去 $a \times b = c$ 的方案数就可以。

考虑开桶，用一个数组 $cnt$，记录 $[1,n]$ 中所有数对 $9$ 取模得到的数的个数，然后 $a \times b \equiv c \pmod 9$ 的方案数就是 $\sum _{i=0}^{9} \sum_{j=0}^{9} cnt_{i} \times cnt_{j} \times cnt_{i \times j \bmod 9}$。

然后求 $a \times b = c$ 的方案数，因为 $c \le n$，所以 $a \times b \le n$，所以 $1 \le b \le \lfloor \frac{n}{a} \rfloor$，则这个方案数为 $\sum_{i=1}^{n} \lfloor \frac{n}{a} \rfloor$，这个式子可以直接暴力，也可以数论分块。

最后相减就可以了。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll cnt[9];
ll cnt1,cnt2;
int main() {
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) cnt[i%9]++; //开桶
	for(ll i=0;i<9;i++) 
		for(ll j=0;j<9;j++) cnt1+=cnt[i]*cnt[j]*cnt[i*j%9]; //a*b%9=c%9的方案数
	for(ll l=1,r;l<=n;l=r+1) {
		r=min(n,n/(n/l));
		cnt2+=(n/l)*(r-l+1); //a*b=c的方案数
	}
	printf("%lld",cnt1-cnt2); //相减
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

[CF10C Digital Root](https://www.luogu.com.cn/problem/CF10C)

在做这道题之前，想一下小学奥数学过的知识。

$$
123456789\bmod 9=(1+2+3+4+5+6+7+8+9)\bmod 9

$$

发现 $1\sim 9$ 的和为 $45$，代入原式：

$$

123456789\bmod 9=45\bmod 9=(4+5)\bmod 9=9\bmod9

$$

发现其原理与 $s(x)$ 相同。

得 
   $\ d(x) = s(x)=\left\{\begin{matrix} 
  x\bmod 9,x\bmod 9  \ne 0 \\ 
  9,x\bmod 9 = 0 \\ 
\end{matrix}\right. $。

记 $cnt_x$ 为 $\sum_{i=1}^n[d(i)=x]$。

可以用桶来实现，然后根据题意模拟可以得到答案为 $\sum_{i=1}^9\sum_{j=1}^9\sum_{k=1}^9[d(d(i)d(j))=d(k)]cnt_icnt_jcnt_k$，代码此处采用了更简洁的写法。

最后根据题意，需将答案减去 $\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[ij=k]$ 的个数。


这个式子先枚举 $k$。

变为 $\sum_{k=1}^nf(k)$，其中 $f(k)$ 为 $\sum_{i=1}^n\sum_{j=1}^n[ij=k]$，化简可得 $f(k)=\sum_{i=1}^n\sum_{j=1}^n[j=\dfrac{k}{i}]$，也就是说，对于每个固定的 $i\mid k$，则有一个 $j$ 满足条件。所以 $f(x)=\sum_{i\mid x}1$，枚举 $f(i)=l$，则有 $\lfloor \dfrac{n}{l} \rfloor$ 个 $k$ 满足条件。

这个式子的结果为 $\sum_{i=1}^n\lfloor \dfrac{n}{i} \rfloor$。

```
#include <bits/stdc++.h>
#define f(c, a, b) for (register int c = a; c <= b; c++)
#define fd(c, a, b) for (register int c = b; c >= a; c--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define int long long
#define vpii vector<pi>
#define il inline
#define ri register
#define aint(a) a.begin(), a.end()
#define fr(a) freopen(a, "r", stdin)
#define fo(a) freopen(a, "w", stdout);
#define debug puts("------------------------")
#define lowbit(x) (x & -x)
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define co const
using namespace std;
const int N = 1e6 + 3;
int n, m;//**//
const int INF=2e9,P=1000000007;
const double eps=1e-6;
typedef long double lb;
namespace DEBUG{
	const bool DeBug=true;
	int db_cnt;
	il void db() { if (DeBug) puts("--------------"); return; }
	il void db(const auto a) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : " << a << '\n'; return; }
	il void db(const auto a, const auto b) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : " << a << ", " << b << '\n'; return; }
	il void db(const auto a, const auto b, const auto c) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << '\n'; return; }
	il void db(const auto a, const auto b, const auto c, const auto d) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << '\n'; return; }
	il void db(const auto a, const auto b, const auto c, const auto d, const auto e) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << ", " << e << '\n'; return; }
	il void db(const auto *a, const auto len) { if (DeBug) { ++ db_cnt; cerr << "-- | t" << db_cnt << " : {"; if (!len) cout << "empty";else { cout << a[1]; for (int i = 2; i <= len; ++ i ) cerr << ", " << a[i]; } cout << "}\n"; } return; }
	il void db(const pair<auto, auto> a) { if (DeBug) ++ db_cnt, cerr << "-- | t" << db_cnt << " : <" << a.first << ", " << a.second << ">\n"; return; }
}
namespace Mod{
	template<int mod>
	inline unsigned int down(unsigned int x) {
		return x >= mod ? x - mod : x;
	}
	template<int mod>
	struct Modint {
		unsigned int x;
		Modint() = default;
		Modint(unsigned int x) : x(x) {}
		friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
		friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
		friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
		friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
		friend Modint operator*(Modint a, Modint b) {return 1LL * a.x * b.x % mod;}
		friend Modint operator/(Modint a, Modint b) {return a * ~b;}
		friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
		friend Modint operator~(Modint a) {return a ^ (mod - 2);}
		friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
		friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
		friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
		friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
		friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
		friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
		friend Modint& operator++(Modint& a) {return a += 1;}
		friend Modint& operator--(Modint& a) {return a -= 1;}
		friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
		friend bool operator!=(Modint a, Modint b) {return !(a == b);}
		friend bool operator<(Modint a, Modint b) {return (a.x<b.x);}
		friend bool operator>(Modint a, Modint b) {return (a.x>b.x);}
	};
	typedef Modint<998244353> _int;
}
namespace Functions{
	il auto Max(const auto x,const auto y){return x>y?x:y;};
	il auto toMax(auto &x,const auto y){return x=(x>y?x:y);};
	il auto Min(const auto x,const auto y){return x<y?x:y;};
	il auto toMin(auto &x,const auto y){return x=(x<y?x:y);};
	il auto Add(const auto x,const auto y){return x+y;};
	il auto toAdd(auto &x,const auto y){return x=(x+y);};
	il auto Mus(const auto x,const auto y){return x-y;};
	il auto toMus(auto &x,const auto y){return x=(x-y);};
	il auto Mul(const auto x,const auto y){return x*y;};
	il auto toMul(auto &x,const auto y){return x=(x*y);};
	il auto Mul(const auto x,const auto y,const auto p){return (x*y)%p;};
	il auto toMul(auto &x,const auto y,const auto p){return x=((x*y)%p);};
	il auto Div(const auto x,const auto y){return x/y;};
	il auto toDiv(auto &x,const auto y){return x=(x/y);};
	il int Xor(const int x,const int y){return x^y;};
	il int toXor(int &x,const int y){return x=(x^y);};
	il int And(const int x,const int y){return x&y;};
	il int toAnd(int &x,const int y){return x=(x&y);};
	il int Or(const int x,const int y){return x|y;};
	il int toOr(int &x,const int y){return x=(x|y);};
	il int popcnt(const int x){return __builtin_popcount(x);}
	il auto Sqr(const auto x){return x*x;}
	il auto toSqr(auto &x){return x=x*x;}
	il auto Sqr3(const auto x){return x*x*x;}
	il auto toSqr3(auto &x){return x=x*x*x;}
	il auto Sqr4(const auto x){return x*x*x*x;}
	il auto toSqr4(auto &x){return x=x*x*x*x;}
	il auto Sqr(auto x,int res,const int Mod){auto now=x;while(res){if(res&1) toMul(now,x);toMul(x,x);res>>=1;}return now;}
	il auto toSqr(auto x,const int res,const int Mod){return x=(Sqr(x,res,Mod));};
	il auto H_dis(const auto x,const auto y,const auto a,const auto b){return abs(x-a)+abs(y-b);}
	il auto H_dis(const pair<auto,auto> x,const pair<auto,auto> y){return H_dis(x.first,x.second,y.first.y.second);};
	il auto O_dis(auto x,auto y,auto a,auto b){return (lb)sqrt(Sqr(x-a)+Sqr(y-b));}
	il auto O_dis(const pair<auto,auto> x,const pair<auto,auto> y){return O_dis(x.first,x.second,y.first.y.second);};
}
namespace FastIO{
	il int read() {ri int ans = 0;ri char c = getchar();ri bool neg = 0;while ((c < '0') | (c > '9')) neg ^= !(c ^ '-'), c = getchar();while ((c >= '0') & (c <= '9')) ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();return neg ? -ans : ans;}
	il void write(ri int x) {if (x < 0)x = -x, putchar('-');if (x > 9)write(x / 10);putchar(x % 10 + '0');}
	il void writes(ri int x) {write(x);putchar(' ');}
	il void writed(ri int x) {write(x);putchar('\n');}
}

using namespace Mod;
using namespace DEBUG;
using namespace Functions;
using namespace FastIO;
int a[N];
void solve(){
	n=read();
	f(i,1,n) a[i%9?i%9:9];
	f(i,1,9){
		f(j,1,9){
			f(k,1,9){
				if(i*j%9!=k%9)
				m+=a[i]*a[j]*a[k];
			}
		}
	}
	f(i,1,n) m-=(n/i);
	writed(m); 
	 return;
}

signed main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=1;

	while(T--)
	    solve();

    return 0;
}

```



---

## 作者：_Flame_ (赞：0)

## 思路

想做出这题，首先要搞清楚 $d$ 函数是什么东西。

首先知道一个结论，一个数模 $9$ 的余数是它的各个位数之和模 $9$ 的余数。及： 

$$ x \equiv s(x) \pmod 9$$

然后可以如下推出 $d(x)$。

因为 $d(x)=d(s(x))$，$s(x) \equiv x(\bmod 9)$。

所以 $d(x)=x\bmod 9$。

如果 $x\bmod 9=0$，则 $d(x)=9$。

这样 $d(x)$ 的值域非常明显为 $[1,9]$。

然后解法就非常简单了，只用先处理出 $1$ 到 $n$ 之间模 $9$ 为各种余数的数的个数，枚举 $1$ 到 $9$ 之间的三个数 $i$，$j$，$k$ 使得 $(i\times j) \bmod9=k \bmod 9$，将每种情况的总数量用乘法原理统计出来，并减去 $ i\times j=k$ 的情况即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=301000;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n;
int ans=0;
int t[maxn];

int d(int x){
	if(x%9!=0){
		return x%9;
	}
	else{
		return 9;
	}
}

void init(){
	for(int i=1;i<=n;i++){
		int x=d(i);
		t[x]++;
	}
}

void solve(){
	n=read();
	init();
	for(int i=1;i<=n;i++){
		ans-=n/i;
	}
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			for(int k=1;k<=9;k++){
				if(i%9==j*k%9){
					ans+=t[i]*t[j]*t[k];
				}
			}
		}
	}
	write(ans);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}





```




---

## 作者：ncwzdlsd (赞：0)

显然可知，$d(x)=x\bmod9$，所以 $d(d(a)\cdot d(b))=(a\times b)\bmod9=c\bmod9$。

由于 $a\times b\neq c$，所以考虑容斥原理，即用 $(a\times b)\bmod9=c\bmod9$ 的方案数减去 $a\times b=c$ 的方案数。

首先我们可以用两重循环解决 $[1,n]$ 中余数为 $[0,8]$ 的个数从而得出前面这坨方案数；对于后面这坨，相当于对每个 $c$ 求 $c$ 的因数，由于 $a$、$c$ 确定，所以 $b$ 也确定，所以我们只要求 $\sum_{i=1}^n\lfloor\dfrac{n}{i}\rfloor$ 即可。

代码实现也比较简单，看了一下我的代码好像是目前题解里最短的诶QwQ

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,ans,d[10];
signed main()
{
    cin>>n;
    for(int i=1;i<=n;++i) ans-=n/i,++d[i%9];
    for(int i=0;i<9;++i)
    	for(int j=0;j<9;++j)
        	ans+=d[i]*d[j]*d[i*j%9];
    cout<<ans;
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路

简单公式推导加一个整除分快。

直接做肯定不行，先化一下题目给的两个式子：$s(\overline{a_1a_2a_3...a_n})\equiv \sum_{i=1}^na_i\equiv \sum_{i=1}^n10^{i-1}a_i\equiv \overline{a_1a_2a_3...a_n} (\bmod 9)$（第二步就是一个 $10^k\equiv 1\pmod 9$）。

然后就可以发现 $d(a)\equiv a\pmod 9$，用一个递归的思想理解一下就行了。

所以满足条件的数就是所有可能的 $ab\equiv c\pmod 9$ 去掉所有的 $ab=c$ 的情况。

之后就是求 $ab=c$ 的个数，发现对于每一个数 $a$，满足条件的数一共有 $\left\lfloor\dfrac{n}{a}\right\rfloor$ 个，就是整除分块的板子题（好像连代码都是一样的）。

要注意 $s(9)=9$，虽然是同余的，但是具体求的时候不一样。

---
### 代码：

```cpp
#include<cstdio>
#define int long long
using namespace std;
int n,cnt[10],ans,r;
int D(int x){
	if(x%9==0)return 9;
	return x%9;
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++)cnt[D(i)]++;
	for(int i=1;i<=9;i++)
	for(int j=1;j<=9;j++)
	for(int k=1;k<=9;k++)
	if(i*j%9==k%9)ans+=cnt[i]*cnt[j]*cnt[k];
	for(int i=1;i<=n;i=r+1){
		r=n/(n/i);
		ans-=(r-i+1)*(n/i);
	}
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：pengyule (赞：0)

### 引理 1

$$
x\equiv s(x),\mod 9
$$

上述等式很好证明，由于 $10\equiv 1,\mod 9$，所以

$$
\overline {ABC}=A\cdot10^2+B\cdot10+C \\
\equiv A\cdot1^2+B\cdot1+C=A+B+C=s(\overline{ABC})
$$
因此 $d(x)=d(s(x))=\cdots=d(x\bmod 9)$，并规定 $d(0)=d(9)=9$。

### 引理 2

$$
AB=C\Rightarrow d(d(A)d(B))=d(C)
$$

由引理 1 得
$$
AB\equiv d(A)d(B)\equiv d(d(A)d(B))\\
AB=C\equiv d(C)\\
\Rightarrow d(d(A)d(B))=d(C)
$$

### 题解

所求即为 $d(d(A)d(B))=d(C)(1)$ 的三元组数减去 $d(d(A)d(B))=d(C),AB=C(2)$ 的三元组数。

$(1)$：我们可以枚举 $d(A),d(B)$，从而得出 $d(C)$，同时预先算出每一个 $d(x)$ 对应的 $x$ 有多少个（记作 $cnt(d(x))$），那么答案累加上 $cnt(d(A))\cdot cnt(d(B))\cdot cnt(d(d(A)d(B)))$。

$(2)$：那么只需要枚举 $C$，求它的约数个数（因为但凡 $k|C$，就一定产生三元组 $\{k,\frac{C}{k},C\}$ 满足 $(2)$）。较为高效的方法是预处理出 $1\sim 10^6$ 中的所有质数，在对每一个 $C$ 分解质因数的同时根据约数个数定理（乘法公式）算出它的约数个数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,d[N],cnt[N],r[10],prime[N],v[N];long long ans;
inline int s(int x){
	register int y=0;
	for(;x;x/=10)y+=x%10;
	return y;
}
inline int work(int x){
	int ans=1;
	for(int i=1;i<=m&&prime[i]*prime[i]<=x;i++)
		if(x%prime[i]==0){
			int tmp=1;
			while(x%prime[i]==0)x/=prime[i],tmp++;
			ans*=tmp;
		}
	if(x>1)ans*=2;
	return ans;
}
int main(){
	cin>>n;
	v[1]=1;
	for(int i=2;i<=n;i++){
		if(v[i])continue;
		prime[++m]=i;
		for(int j=i*2;j<=n;j+=i)v[j]=1;
	}
	for(int i=1;i<=9;i++)d[i]=i;
	for(int i=1;i<=9;i++)for(int j=1;j<=i;j++)if(i%j==0)r[i]++;
	for(int i=1;i<=1000000;i++){
		d[i]=d[s(i)];
		if(i>n)continue;
		cnt[d[i]]++;
		ans-=1ll*work(i);
	}//cout<<ans<<' ';
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			ans+=1ll*cnt[i]*cnt[j]*cnt[d[i*j]];
	cout<<ans;
}
```



---

