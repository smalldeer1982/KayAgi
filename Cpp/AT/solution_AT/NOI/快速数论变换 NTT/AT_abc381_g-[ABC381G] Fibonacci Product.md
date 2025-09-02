# [ABC381G] Fibonacci Product

## 题目描述

# [ABC381G] 斐波那契积

## 问题描述

[problemUrl]: https://atcoder.jp/contests/abc381/tasks/abc381_g

定义数列 $ a_1,\ a_2,\ a_3,\ \dots $ 的通项公式如下：

$$ a_n\ =\ \begin{cases}x\ \ &(n=1)\ \\ y\ \ &(n=2)\ \\ a_{n-1}\ +\ a_{n-2}\ \ &(n\geq 3)\ \\ \end{cases} $$ 

请计算 $ \left(\displaystyle\ \prod_{i=1}^N\ a_i\right)\ \bmod{998244353} $。

本题多测，给定 $ T $ 组数据，请你对每一组数据求解。

## 说明/提示

### 限制条件

- $ 1\ \leq\ T\ \leq\ 5 $
- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 0\ \leq\ x\ \leq\ 998244352 $
- $ 0\ \leq\ y\ \leq\ 998244352 $
- 输入的所有值均为整数

### 样例解释 1

对于第 $ 1 $ 个测试用例，数列的各项为 $ 1,\ 1,\ 2,\ 3,\ 5,\ 8,\ \dots $。因此，$ (1\ \times\ 1\ \times\ 2\ \times\ 3\ \times\ 5)\ \bmod{998244353}\ =\ 30 $ 为答案。

## 样例 #1

### 输入

```
3
5 1 1
2024 11 22
1000000000000000000 12345 6789```

### 输出

```
30
577322229
726998219```

# 题解

## 作者：Argon_Cube (赞：13)

赛后 6 分钟通过喜提赛后首 A/ll/fn

洛谷首 A 来发篇题解，纪念一下这个差点赛时过的铜牌。

-----

首先显然不可能直接用 $f_n$ 来乘的，要将 $f_n$ 写成这种形式：

$$f_n=a\phi^n+b(-\phi)^{-n}$$

其中 $\phi=0.5(1+\sqrt 5)$。容易通过 $f_0=y-x,f_1=x$ 解出 $a,b$。

到这里你就会发现 $\sqrt 5$ 在模 $p=998244353$ 时不存在所以你还要扩域，比较烦但是还能接受。

众所周知 Fibonacci 数是有循环节的，$f_n\bmod p$ 的循环节为 $2p+2$，所以以下我们认为 $N<2p+2$。$N$ 更大时容易化为 $N\bmod(2p+2)$ 的情形。

现在原来的式子变成了

$$\prod_{i=1}^Na\phi^i+b(-\phi)^{-i}=\left(\prod_{i=1}^{N}(-\phi)^{-i}\right)\left(\prod_{i=1}^N(a(-\phi^2)^i+b)\right)$$

前面是容易计算的，后面显然可以使用快速阶乘的技巧。对原式分块，令块长为 $B=\sqrt{2p+2}$，$c=-\phi^{2B}$，则我们只需要计算 $f(c^0),f(c^1),f(c^2),\cdots,f(c^{\lfloor\frac{2p+2}B\rfloor})$，其中

$$f(x)=\prod_{i=1}^B(a(-\phi^2)^ix+b)$$

容易使用 Chirp Z-Transform 解决以上问题，于是我们得到了本题的 $\Omicron(\sqrt p\log p)$ 解法。

[Code.](https://atcoder.jp/contests/abc381/submissions/60089993)

---

## 作者：bcdmwSjy (赞：11)

AT 又出了他最喜欢的多项式题，但是我们不会多项式怎么办呢 qwq，我们今天换一种不一样的做法。

下文中如无特殊说明，那么 $\operatorname{Fib}_{x,y}(n)$ 表示第一项为 $x$，第二项为 $y$ 的广义斐波那契数列的第 $n$ 项在模 $998244353$ 意义下的值。

这道题让我们求广义斐波那契数列前 $n$ 项的积，广义斐波那契数列 $F_n$ 由如下的递推公式给出：

$F_0=p,F_1=q,F_n=F_{n-1}+F_{n-2}$。

若 $p=0,q=1$ 即为一般的斐波那契数列，通项公式为： $f_n=\frac{a^n-b^n}{\sqrt5}$，其中 $a=\frac{1+\sqrt5}{2},b=\frac{1-\sqrt5}{2}$。

若 $p=2,q=1$ 即为卢卡斯数列，通项公式为： $L_n=a^n+b^n$。

广义斐波那契数列 $F_n$ 与斐波那契数列 $f_n$ 符合如下的关系式：$F_n=p\times f_n+q\times f_{n-1}$。

我们发现，从任意数开始的广义斐波那契数列，总存在相邻两项之比与斐波那契数列或卢卡斯数列的相邻两项之比相等。

即我们需要找到一对 $x,t$ 满足 $\dfrac{f_{x+1}}{f_{x+2}}=\dfrac{\operatorname{Fib}_{a,b}(t+1)}{\operatorname{Fib}_{a,b}(t+2)}$，或者是 $\dfrac{L_{x+1}}{L_{x+2}}=\dfrac{\operatorname{Fib}_{a,b}(t+1)}{\operatorname{Fib}_{a,b}(t+2)}$，求它可以采用类似 BSGS 的思想，先计算一部分存起来，再去找和前面匹配的元素。

求出后即可把问题转化为求两段斐波那契数列或卢卡斯数列前缀的乘积了，这可以采用分段打表完成，当然最后还需要乘上偏移量。

打表程序如下（跑得挺快的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod=998244353;

inline void NextFib(ll &a,ll &b){
	int c=(a+b)%mod;
	a=b;
	b=c;
}

int main(){
	ll a=1,b=1,t=1;
    for (ll i=2;i<=1996488708;i++){
        NextFib(a,b);
        t=t*a%mod;
		if ((i&1048575)==0) cout<<t<<",";
    }
    cout<<"\n"<<t;
	return 0;
}
```

打第二个表时只需要把 $b$ 的初始值改成 $3$ 即可。

我们发现，在打第一个表时，后面一些项的值都是 $0$，试一下发现 $\operatorname{Fib}_{1,1}(499122177)=0$ （正好是 $\frac{1}{2}$ 哎，真神奇），也就是说后面的乘积都变成 $0$ 了，可以进行一些优化。

代码如下，表太长就不放了，打表方法已经放在上面了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
const int inv2=499122177;
const int per=1996488708; // 2(mod+1) 循环节长度 
const int B=1048576,LB=20;
const ll Fib65535=752861792; // fib(65535)
const ll Fib65536=539562357; // fib(65536)
const ll Fib65537=294179796; // fib(65537)
const int table[2][4096]= {
    {1,/*我是表*/},
    {1,/*我也是表*/}
};
inline ll qpow(ll a,ll b) {
	ll res=1;
	for (; b; b>>=1,a=a*a%mod) if (b&1) res=res*a%mod;
	return res;
}
inline int divide(int a,int b) {
	return a*qpow(b,mod-2)%mod;
}
inline void nextFib(int &a,int &b) {
	int c=(a+b)%mod;
	a=b;
	b=c;
}
inline void nextFib65536(int &a,int &b) {
	int c=(a*Fib65535+b*Fib65536)%mod;
	b=(a*Fib65536+b*Fib65537)%mod;
	a=c;
}
inline pair<int,int> fib(int a,int b,int n) {
	while (n>=65536) nextFib65536(a,b),n-=65536;
	while (n--) nextFib(a,b);
	return {a,b};
}
unordered_map<int,pair<int,int>> mp;
// 初始化数列，id=0 为斐波那契数列，id=1 为卢卡斯数列
inline void init(int id,int a,int b) {
	for (int i=0; i<inv2; i+=65536) {
		mp[divide(a,b)]= {id,i};
		nextFib65536(a,b);
	}
}
inline pair<int,int> find(int a,int b) {
	for (int t=0;; t++,nextFib(a,b)) {
		if (mp.find(divide(a,b))!=mp.end()) {
			auto [p,q]=mp[divide(a,b)];
			// find fib_{1,p?3:1}(q+1)/fib_{1,p?3:1}(q+2)=fib_{a,b}(t+1)/fib_{a,b}(t+2)
//			cout<<"fib_{1,"<<(p?3:1)<<"}("<<q+1<<")/fib_{1"<<(p?3:1)<<"}("<<q+2<<")=fib("<<t+1<<")/fib("<<t+2<<")\n";
			return {p,q-t<0?q-t+inv2:q-t};
		}
	}
}
ll query(int id,ll n) {
	if (id==0 and n>=inv2) return 0;
	if (n>=per) return query(id,n%per)*qpow(998244337,n/per)%mod; // 998244337=\prod ^{1996488708}_{i=1} fib_{1,3}(i) 
	ll p=table[id][n>>LB]; // 查表
	auto [a,b]=fib(1,id?3:1,n>>LB<<LB); // 计算剩下的第一项
	for (int i=n&(B-1); i--; nextFib(a,b)) p=p*a%mod; // 暴力把剩下的算了
	return p;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	init(0,1,1);
	init(1,1,3);
	int T;
	cin>>T;
	while (T--) {
		ll n,x,y;
		cin>>n>>x>>y;
		if (x==0) {
			cout<<"0\n";
		} else if (y==0) {
			cout<<(n==1?x:0)<<"\n";
		} else {
			auto [id,pos]=find(x,y);
			ll t=divide(x,fib(1,id?3:1,pos).first);
			ll prod=divide(query(id,pos+n),query(id,pos)); // 计算从 pos 开始的 n 项
			cout<<prod*qpow(t,n%(mod-1))%mod<<"\n"; // 每一项都差 t，把差的重新乘上去，模 mod-1 是使用费马小定理降幂
		}
	}
	return 0;
}
```

这个做法看起来比较暴力，但是它的复杂度很低，单次查询大概是 $O(B+\sqrt{mod})$ 的，常数还比较小，为了能在洛谷把代码交上去，$B$ 取了 $1048576$，但是 AtCoder 可以交 512 KiB 的代码，所以令 $B=65536$，就可以在最大点 38 ms 的情况下抢到 AT 最优解。尽管在洛谷上提交不了那么长的表，那也要比第二跑的快将近一倍（不得不说，鱼鱼的多项式跑得真的快）。

---

## 作者：what_else (赞：8)

## 题目简述

给定广义斐波那契数列的前两项 $x,y$。求该斐波那契数列的前 $N$ 项之积。

## Solution


### Task1

如果你熟悉斐波那契数列的性质，你就会知道斐波那契数列在取模 $m$ 时循环。周期为 $O(m)$ 级别的。

广义斐波那契数列的周期是可以求的。因为模数为 $99824353$ 且为质数，我们利用矩阵快速幂可以求得该数列的周期 $T$。时间复杂度为 $O(\log N)$。

### Task2

我们假设 $f(x) = \prod^{x}_{i=1}a_i$，若我们求出来了周期 $T$，那么答案即为 $f(N \mod T) + f(T)^{\lfloor \frac{N}{T} \rfloor}$。

接下来考虑将题目范围缩小到 $998244353$ 级别怎么做。如果你做过快速阶乘，那么会想到类似的分块思想。现在将 $T$ 内的数字分为若干个块，块长为 $B$。如果要知道这个块的信息，必须要先知道前两个数的值，以方便斐波那契数列的递推。这部分可以使用矩阵快速幂，时间复杂度 $O(\frac{T}{B} \log T)$。

你把块剥离出来，假设某个块前两个数为 $x,y$，根据斐波那契数列的递推式，第三个数为 $x+y$，第 $B$ 个数为 $c_n x + d_n y$。那么这一段的积即为 $\prod^{B}_{i=1}(c_ix + d_iy)$。

不同的块只有 $x,y$ 不相同，系数是不变的，我们不妨预处理展开每一项的系数。这是 $B$ 个二项式相乘，时间复杂度 $O(B^2)$。

这是一个 $B$ 次的多项式，单次计算时间 $O(B)$。如果暴力对所有块计算，时间复杂度来到 $O(n)$，弗如暴力。

你知道有“多项式多点求值”这个东西，它可以实现 $O(\log n)$ 求出多项式的值。可是你搜索的所有“多项式多点求值”都是一元求值，并无二元求值。

本来以为成功的你大为失望，你愤恨，怒骂，质疑出题人为什么要放这么难的题在 G 上的时候，你看了看榜，只有三个人通过了此题，你又不慌了。

不知道过了多久，你准备关闭网页的时候，想到：为什么我要二元？你把上面的柿子转化成：

$$\prod^{B}_{i=1}(c_ix + d_iy) = \prod^{B}_{i=1}(c_i + d_i\frac{y}{x})x^B$$

你发现系数仍然未变，而 $\frac{y}{x}$ 是一元的。而你每个块是知道 $x,y$ 的，你想到了好做法：

将 $\frac{y}{x}$ 设为一个点，利用多项式单点求值求出这个固定的已知系数的多项式的值。$x^B$ 用个快速幂就可以求。你发觉：这个时间复杂度是 $O(\log B)$。

你算了算，总的时间复杂度是 $O(\frac{T}{B} \log B + B \log B + B^2)$。这个均值不等式你是会计算的。在取 $B = T^{\frac{1}{3}}$ 时或许可以做到最优，那么时间复杂度就变为了 $O(T^\frac{2}{3} \log T^\frac{1}{3})$。这个速度和你跑 $q = 10^6$ 的线段树差不多，然而常数比较大，不过时限是 4s（标解的时间复杂度是 $O(\sqrt T\log T)$）。

你直接就开始写。大概离比赛还有 5min 的时候，你看着还有大半没写完的代码陷入了沉思，然后大哭一场。

如果你不在那 20min 里去看 B 站，或许你还有机会把这题做出来。

就像 NOIP 一样。

---

## 作者：cyq32ent (赞：1)

NTT+Chirp Z 变换+广义斐波那契数列结论+扩域神题。

### 题意

已知 $f_n=\left\{\begin{matrix}
x & n=1\\
y & n=2\\
f_{n-1}+f_{n-2}  &n>2
\end{matrix}\right.$，求 $\prod_{i=1}^nf_i$。

### Chirp Z 变换
Chirp Z 变换对于多项式

$$A(x)=\sum_{i=0}^na_ix^i$$

给出 $A(c^m)$。其中 $m\in \mathbb N$。下面介绍该算法的具体内容。在下面，我们用 $[x^m]F(x)$ 表示多项式 $F(x)$ 的 $m$ 次项系数。令

$$a(x)=\sum_i a_{n-i}c^{-{{n-i} \choose 2}}x^i$$

$$b(x)=\sum_i c^{i \choose 2}x^i$$

则注意到

$$[x^{n+m}](a(x)b(x))=c^{m \choose 2}A(c^m)$$

所以我们只需要先计算 $a(x)b(x)$，然后递推计算 $c^i=c^{i-1 \choose 2}c^{i-1}$ 即可。

### 广义斐波那契数列的循环节

考虑题目中的广义斐波那契数列。令 $\alpha = \frac{1+\sqrt{5}}{2}$，$p=998244353$，则有

$$f_n=\lambda \alpha^{n}+\mu (-\alpha)^{-n}$$

我们发现 $5^{\frac{p-1}{2}}\equiv -1 \pmod p$，所以在模 $p$ 意义下，有

$$\alpha^p=(\frac{1+\sqrt{5}}{2})^p=\frac{(1+\sqrt{5})^p}{2}=\frac{1-\sqrt{5}}{2}=(-\alpha)^{-1}$$

又因为 $\alpha (-\alpha)^{-1}=-1$，令 $\beta = (-\alpha)^{-1}$，于是对于 $k\in \mathbb{N}$，有

$$\alpha^{2p+2+k}=\beta^2\alpha^2\alpha^k=\alpha^k\\
\beta^{2p+2+k}=\alpha^2\beta^2\beta^k=\beta^k$$

所以 $2p+2$ 为 $f_n$ 的一个周期。

### 扩域

发现在模 $p$ 意义下并不存在 $\sqrt{5}$。所以要进行扩域。扩域之后的数形如 $x+y \sqrt{5}$，从而可以定义加、减、乘、幂运算。

### 题解

由于 $f_n$ 在模 $p$ 意义下的循环节为 $2p+2$，所以我们只需要考虑 $n<2p+2$ 的情形就可以了。

$$\begin{align*}
\prod_{i=1}^nf_i &= \prod_{i=1}^n({\lambda \alpha^i+\mu (-\alpha)^{-i}}) \\
&= \prod_{i=1}^n({\lambda (-\alpha^{2})^{i}+\mu})\prod_{i=1}^n(-\alpha)^{-i} \\
&= (-\alpha)^{-\frac{n(n+1)}{2}}\prod_{i=1}^n({\lambda (-\alpha^{2})^{i}+\mu})
\end{align*}$$

我们使用分块的方法，令 $L=\lfloor\sqrt{n}\rfloor$，则令

$$g(x)=\prod_{i=1}^L({\lambda (-\alpha^{2})^{i}x+\mu})\\
c=(-\alpha^{2})^{L}$$

故

$$\prod_{i=1}^n({\lambda (-\alpha^{2})^{i}+\mu})=\prod_{i=0}^{\lfloor \frac{n}{L} \rfloor-1}g(c^i)\prod_{i=L \lfloor \frac{n}{L} \rfloor+1}^n({\lambda (-\alpha^{2})^{i}+\mu})$$

而 $g(x)$ 可以用以下方式算出：

$$\prod_{i=1}^{2l}({\lambda (-\alpha^{2})^{i}x+\mu})=\prod_{i=1}^l({\lambda (-\alpha^{2})^{i}x+\mu})\prod_{i=1}^l({\lambda (-\alpha^{2})^{i} ((-\alpha^{2})^{l}x)+\mu})$$

使用 Chirp Z 变换可以在 $\mathcal O(\sqrt{p} \log p)$ 时间内解决。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=998244353;
const int N=502412;
using ll=long long;

namespace Math{ll qpow(ll x,ll y);}

namespace Extended{
	struct LL{
		ll x,y;
		LL(){}
		LL(int x,int y):x(((x%P)+P)%P),y(((y%P)+P)%P){}
		friend LL operator+(const LL A,const LL B){
			return LL((A.x+B.x)%P,(A.y+B.y)%P);
		}friend LL operator-(const LL A,const LL B){
			return LL((A.x-B.x+P)%P,(A.y-B.y+P)%P);
		}friend LL operator*(const LL A,const ll B){
			return LL((A.x*(B%P))%P,(A.y*(B%P))%P);
		}friend LL operator*(const LL A,const LL B){
			return LL((A.x*B.x+A.y*B.y*5)%P,(A.x*B.y+A.y*B.x)%P);
		}friend LL operator*(const ll A,const LL B){
			return B*A;
		}friend LL operator/(const LL A,const LL B){
			ll x=(B.x*B.x-5*B.y*B.y)%P;x+=P;x%=P;
			return A*LL(B.x,P-B.y)*Math::qpow(x,P-2);
		}
	};
}
using namespace Extended;

namespace Math{
	ll qpow(ll x,ll y){
		ll ret=1;
		for(;y;y>>=1){
			if(y&1)ret=ret*x%P;
			x=x*x%P;
		}return ret;
	}
	LL qpow(LL x,ll y){
		LL ret(1,0);
		for(;y;y>>=1){
			if(y&1)ret=ret*x;
			x=x*x;
		}return ret;
	}
	ll C2(ll x){
		return (x*(x-1))/2;
	}
}
using namespace Math;


namespace NTT{
	ll r[N];
	void Ntt(LL *x,ll lim,ll opt){
		for(int i=0;i<lim;i++)if(r[i]<i)swap(x[i],x[r[i]]);
		for(int m=2;m<=lim;m<<=1){
			ll k=m>>1,gn=qpow(3,(P-1)/m);
			for(int i=0;i<lim;i+=m){
				for(int j=0,g=1;j<k;j++,g=g*gn%P){
					LL t=x[i+j+k]*g;
					x[i+j+k]=(x[i+j]-t);
					x[i+j]=(x[i+j]+t);
				}
			}
		}if(!~opt){
			reverse(x+1,x+lim);
			int li=qpow(lim,P-2);
			for(int i=0;i<lim;i++)x[i]=x[i]*li;
		}
	}void Multiply(LL* a,LL* b,ll n,ll m){
		ll bit=0,len=1;
		while(len<=n+m)len<<=1,bit++;
		for(int i=0;i<len;i++)r[i]=(r[i>>1]>>1)|((i&1)<<(bit-1));
		Ntt(a,len,1);Ntt(b,len,1);
		for(int i=0;i<len;i++)a[i]=a[i]*b[i];
		Ntt(a,len,-1);
		memset(r,0,sizeof r);
		for(int i=0;i<len;i++)b[i]=LL(0,0);
	}void Multiply2(LL *a,LL *b,ll n){//m=1
		LL p=b[1],q=b[0];//i i-1 p; i q
		a[n+1]=a[n]*p;
		for(int i=1;i<=n;i++){
			a[i]=a[i-1]*p+a[i]*q;
		}a[0]=q;
	}
}

namespace ChirpZ{
	LL A[N],B[N];
	void Generate(LL* a,ll n,LL c,ll sz){
		for(int i=0;i<=n;i++){
			A[i]=(a[n-i]/qpow(c,C2(n-i)));
		}for(int i=0;i<=n+sz;i++){
			B[i]=qpow(c,C2(i));
		}
		NTT::Multiply(A,B,n,n+sz);
		for(int i=0;i<=2*n+2;i++)B[i]=LL(0,0);
	}void Calculate(LL* a,ll n,LL c,ll sz){
		for(int i=0;i<N;i++)A[i]=B[i]=LL(0,0);
		Generate(a,n,c,sz);
		LL c_t(1,0);
		for(int t=0;t<=sz;t++){
			B[t]=A[n+t]/c_t;
			c_t=c_t*qpow(c,t);
		}for(int i=0;i<=n;i++)A[i]=LL(0,0);
	}
}

namespace Solve{
	LL alpha,beta,c,d,lambda,mu,g[N],h[N];
	ll L;
	void init(ll n,ll x,ll y){
		L=0,alpha=beta=c=d=lambda=mu=LL(0,0);
		for(int i=0;i<N;i++)g[i]=h[i]=LL(0,0);
		L=sqrt(n);
		alpha=LL(1,1)*qpow(2,P-2);
		beta=LL(1,-1)*qpow(2,P-2);
		d=LL(0,0)-alpha*alpha;
		c=qpow(d,L);
		lambda=x*(beta+LL(1,0))-y*beta;
		lambda=lambda/(alpha-beta);
		mu=y*alpha-x*(alpha+LL(1,0));
		mu=mu/(alpha-beta);
	}void CalcG(ll l){
		if(l==1){
			g[0]=mu;
			LL pw=lambda*d;
			g[1]=pw;
		}
		else{
			ll half=l>>1;
			ll odd =l&1;
			LL extra=qpow(d,half);
			CalcG(half);
			ll len1=half,len2=half;LL ex(1,0);
			for(int i=0;i<=len1;i++){
				h[i]=ex*g[i];
				ex=ex*extra;
			}
			NTT::Multiply(g,h,len1,len2);
			for(int i=0;i<=l;i++)h[i]=LL(0,0);
			if(odd){
				h[0]=mu;
				h[1]=lambda*qpow(d,l);
				len2=1;
				NTT::Multiply(g,h,l-1,1);
				for(int i=0;i<=l;i++)h[i]=LL(0,0);
			}
		}
	}LL Calculate(ll n,ll x,ll y){
		init(n,x,y);
		CalcG(L);
		LL ans=LL(1,0)/(LL(0,0)-alpha);
		ans=qpow(ans,n*(n+1)/2);
		ChirpZ::Calculate(g,L,c,n/L-1);
		
		for(int i=0;i<n/L;i++)ans=ans*ChirpZ::B[i],ChirpZ::B[i]=LL(0,0);
		LL al=qpow(d,L*int(n/L)+1)*lambda;
		for(int i=L*int(n/L)+1;i<=n;i++){
			ans=ans*(al+mu);
			al=al*d;
		}
		return ans;
	}ll Solve(ll n,ll x,ll y){
		ll mod=2*P+2;
		ll times=n/mod,remains=n%mod;
		LL ans(1,0);
		if(n>=mod)ans=Calculate(mod,x,y);
		ans=qpow(ans,times);
		if(remains)ans=ans*Calculate(remains,x,y);
		return ans.x;
	}
}

ll n,x,y,T;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>y;
		cout<<Solve::Solve(n,x,y)<<endl;
	}
}
```

---

## 作者：qczrz6v4nhp6u (赞：1)

### Solution

为方便描述，我们让 $a$ 从 $0$ 开始（即令 $a_0=x,a_1=y$，后同）。

考虑 $a$ 的通项。具体地，我们设 $A(z)=\sum_{n\ge 0}a_nz^n$，那么有：

$$
A(z)=zA(z)+z^2A(z)-xz+x+yz\\
A(z)=\frac{x+(y-x)z}{1-z-z^2}
$$

使用具体数学 7.3 中的方法（可以在我的 [博客](https://www.luogu.com.cn/article/2el91q01) 中查看），我们可以得到 $a$ 的通项：记 $c_1=\frac{1}{\sqrt 5}(\frac{\sqrt 5-1}{2}\cdot x+y),c_2=\frac{1}{\sqrt 5}(\frac{\sqrt 5+1}{2}\cdot x-y)$，则有

$$a_n=c_1\Big(\frac{1+\sqrt 5}{2}\Big)^n+c_2\Big(\frac{1-\sqrt 5}{2}\Big)^n$$

考虑 $a$ 的在 ${}\bmod 998244353$ 意义下的循环节。打表发现，$a_{1996488708}=x$（即 $a_{2\times (998244353+1)}=x$）。这意味着我们可以将 $n$ 对 $1996488708$ 取模，只需处理 $n<1996488708$ 的情况。

那么现在我们要求的即为：

$$\prod_{i=0}^{n-1}(c_1A^i+c_2B^i)$$

其中 $A=\frac{1+\sqrt 5}{2},B=\frac{1-\sqrt 5}{2}$。

下面我们来计算这个式子。令 $D=\frac{A}{B}$，则原式即为

$$\prod_{i=0}^{n-1}B^i(c_1D^i+c_2)=B^{\frac{n(n-1)}{2}}\prod_{i=0}^{n-1}(c_1D^i+c_2)$$

考虑根号分治计算后面那个式子。设块长为 $m$。下文假设 $m|n$，若不是直接 $O(m)$ 调整即可。则原式即为

$$\prod_{i=0}^{\frac{n}{m}-1}\prod_{j=0}^{m-1}(c_1D^{im+j}+c_2)=\prod_{i=0}^{\frac{n}{m}-1}\prod_{j=0}^{m-1}(c_1D^jX^i+c_2)$$

其中 $X=D^m$。

设 $F(z)=\prod_{j=0}^{m-1}(c_1D^jz+c_2)$，则我们可以 $O(m\log^2 m)$ 分治 NTT 或 $O(m\log m)$ 倍增展开 $F(z)$。

关于倍增展开的说明：设我们已经计算出了 $F(z)\bmod z^{m}$，现在计算 $F(z)\bmod z^{2m}$。记前者为 $F_0(z)$，后者为 $F_1(z)$，那么有：

$$\begin{aligned}
F_1(z)&=\Big(\prod_{i=0}^{m-1}(c_1D^iz+c_2)\Big)\times\Big(\prod_{i=m}^{2m-1}(c_1D^iz+c_2)\Big)\\
&=F_0(z)\times \prod_{i=0}^{m-1}(c_1D^i\times D^mz+c_2)\\
&=F_0(z)\times F_0(D^mz)
\end{aligned}$$

也就是说我们将 $F_0(z)$ 的第 $i$ 项乘上 $D^{im}$ 就能得到右半边的系数表示。

现在原问题可以表述为

$$\prod_{i=0}^{\frac{n}{m}-1}F(X^i)$$

我们可以通过 $O(\frac{n}{m}\log^2 \frac nm)$ 的多项式多点求值或 $O(\frac nm\log \frac nm)$ 的 Chirp Z Transform 求出每个 $F(X^i)$。

取 $m=\sqrt n$，有最优时间复杂度即为 $O(\sqrt n\log n)$，可以通过。

这里讲一下 Chirp Z Transform：

设我们要求的是 $F(1),F(X),F(X^2),\cdots,F(X^p)$。考虑这样一个事实：

$$ki={k+i\choose 2}-{i\choose 2}-{k\choose 2}$$

组合意义不难证明。应用到我们的式子中：

$$\begin{aligned}
F(X^k)&=\sum_{i=0}^{\deg F}[z^i]F(z)\times X^{ki}\\
&=\sum_{i=0}^{\deg F}[z^i]F(z)\times X^{{k+i\choose 2}-{i\choose 2}-{k\choose 2}}\\
&=X^{-{k\choose 2}}\sum_{i=0}^{\deg F}[z^i]F(z)\times X^{{k+i\choose 2}-{i\choose 2}}
\end{aligned}$$

令 $F_0(z)=\sum_{i=0}^{\deg F}[z^i]F(z)\times X^{-{i\choose 2}}$，$F_1(z)=\sum_{i=0}^{p+\deg F}X^{{^{i\choose 2}}}$，则不难通过一次差卷积计算出所有 $F(X^k)$。

另外，由于 $5$ 不是模 $998244353$ 意义下的二次剩余，我们需要扩域。单位根沿用 $3$ 即可，毕竟 NTT 的过程中并没有用到单位根的幂必须取遍整个域这个性质。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=262145,mod=998244353,loop=(mod+1)<<1,g=3,inv2=(mod+1)>>1;
ll n,m,x,y;
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
struct node{ // a + b * sqrt(5)
	ll a,b;
	node(){a=b=0;}
	node(ll _a,ll _b){a=_a,b=_b;}
	inline node operator +(ll _)const{return node(add(a,_),b);}
	inline node operator -(ll _)const{return node(sub(a,_),b);}
	inline node operator *(ll _)const{return node(a*_%mod,b*_%mod);}
	inline node operator +(const node &_)const{return node(add(a,_.a),add(b,_.b));}
	inline node operator -(const node &_)const{return node(sub(a,_.a),sub(b,_.b));}
	inline node operator *(const node &_)const{return node((a*_.a+b*_.b*5)%mod,(a*_.b+b*_.a)%mod);}
	inline node inv()const{
		static ll tmp;tmp=qpow((a*a-b*b*5%mod+mod)%mod,mod-2);
		return node(a*tmp%mod,(mod-b)*tmp%mod);
	}
	inline friend node operator /(const node &a,const node &b){return a*b.inv();}
};
inline ostream& operator <<(ostream& ouf,const node &x){
	return ouf<<'('<<x.a<<", "<<x.b<<')';
}
const node A(inv2,inv2),B(inv2,mod-inv2),D=A/B,I(0,1);
node c1,c2;
inline node qpow(node a,ll b){
	node res(1,0);
	for(;b;b>>=1,a=a*a)
		if(b&1)res=res*a;
	return res;
}
int lim,ilim,rev[N],w[N];
void initNTT(int n){
	lim=1;
	while(lim<=n)lim<<=1;
	ilim=qpow(lim,mod-2);
	for(int i=1;i<lim;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)*(lim>>1));
	for(int i=1;i<lim;i<<=1){
		ll wn=qpow(g,(mod-1)/(i<<1)),cur=1;
		for(int j=0;j<i;j++,cur=cur*wn%mod)
			w[i|j]=cur;
	}
}
using poly=vector<node>;
void NTT(node *F,int type){
	for(int i=0;i<lim;i++)
		if(i<rev[i])
			swap(F[i],F[rev[i]]);
	node x,y;
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++){
				x=F[j|k],y=F[i|j|k]*w[i|k];
				F[j|k]=x+y,F[i|j|k]=x-y;
			}
	if(type==1)return;
	reverse(F+1,F+lim);
	for(int i=0;i<lim;i++)F[i]=F[i]*ilim;
}
void mul(const poly &F,const poly &G,poly &H){
	static node A[N],B[N],C[N];
	int n=(int)F.size()-1,m=(int)G.size()-1;
	for(int i=0;i<=n;i++)A[i]=F[i];
	for(int i=0;i<=m;i++)B[i]=G[i];
	if(1ll*n*m<=1000){
		for(int i=0;i<=n+m;i++)C[i]=node(0,0);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				C[i+j]=C[i+j]+A[i]*B[j];
	}
	else{
		initNTT(n+m);
		for(int i=n+1;i<lim;i++)A[i]=node(0,0);
		for(int i=m+1;i<lim;i++)B[i]=node(0,0);
		NTT(A,1),NTT(B,1);
		for(int i=0;i<lim;i++)C[i]=A[i]*B[i];
		NTT(C,-1);
	}
	H.resize(n+m+1);
	for(int i=0;i<=n+m;i++)H[i]=C[i];
}
void solve1(poly &F,int n){
	if(n==1){
		F.resize(2);
		F[0]=c2,F[1]=c1;
		return;
	}
	static poly G;
	int m=n>>1;
	solve1(F,m);
	node cur(1,0),X=qpow(D,m);G.resize(m+1);
	for(int i=0;i<=m;i++,cur=cur*X)G[i]=cur*F[i];
	mul(F,G,F);
	if(n&1){
		F.emplace_back(0,0);
		node tmp=c1*qpow(D,n-1);
		for(int i=n;i>=0;i--)F[i]=(i>0?tmp*F[i-1]:node(0,0))+c2*F[i];
	}
}
inline ll C(int n){return n*(n-1ll)>>1;}
void solve2(const poly &F,const node &X,poly &G,int n){
	if(!n){G.resize(0);return;}
	static node iX;static poly F0,F1;
	iX=X.inv();
	F0.resize(F.size());
	F1.resize((int)F.size()+n-1);
	for(int i=0;i<(int)F0.size();i++)F0[i]=F[i]*qpow(iX,C(i));
	for(int i=0;i<(int)F1.size();i++)F1[i]=qpow(X,C((int)F1.size()-i-1));
	mul(F0,F1,F0);
	G.resize(n);
	for(int i=0;i<n;i++)G[i]=qpow(iX,C(i))*F0[(int)F1.size()-i-1];
}
poly F;
node calc(int n){
	if(!n)return node(1,0);
	m=sqrt(n);
	solve1(F,m);
	solve2(F,qpow(D,m),F,n/m);
	node ans(1,0);
	for(int i=0;i<(int)F.size();i++)ans=ans*F[i];
	node cur=qpow(D,n/m*m);
	for(int i=n/m*m;i<n;i++,cur=cur*D)ans=ans*(c1*cur+c2);
	return ans*qpow(B,C(n));
}
void solve(){
	cin>>n>>x>>y;
	c1=(node((mod-1)>>1,inv2)*x+y)/I;
	c2=(node(inv2,inv2)*x-y)/I;
	cout<<(qpow(calc(loop),n/loop)*calc(n%loop)).a<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _Test;cin>>_Test;
	while(_Test--)solve();
	return 0;
}
```

---

所以有没有人会证这个循环节的结论啊 /kel

---

## 作者：违规用户名1425622 (赞：0)

### 1. 题意

定义一个数列 $f$ 为：

$f_n = \begin{cases} x & (n=1) \\ y & (n=2) \\ f_{n-1} + f_{n-2} & (n \geq 3) \\ \end{cases}$

请求出 $\left( \displaystyle \prod_{i=1}^n f_i \right) \bmod{998244353}$。

$n \le 10^{18},x,y \le 998244352$。

---

### 2. 解法

设 $\displaystyle \alpha=\frac{1+\sqrt{5}}{2},\beta=\frac{1-\sqrt{5}}{2},a=\frac{y-x\beta}{\alpha-\beta},b=\frac{x\alpha-y}{\alpha-\beta}$，则有 $f_n=a \alpha^{n-1}+b \beta^{n-1}$。

发现 $5$ 模 $998244353$ 意义下不存在二次剩余，考虑扩域，设新域为 $\displaystyle \{ a+b \sqrt{5} \mid a,b \le 998244352 \}$。

参考 P4000 中的结论，有 $a^{2p+2} \equiv b^{2p+2} \equiv 1$。

所以容易发现 $f$ 的循环节为 $2p+2$。

于是我们成功把 $n$ 的范围缩小到了 $2p+2$ 以内。

答案即为 $\displaystyle \prod_{i=0}^{n-1} (a \alpha^i+b \beta^i)=a^n \alpha^{\frac{n(n-1)}{2}} \prod_{i=0}^{n-1}(1+\frac{b}{a}(\frac{\beta}{\alpha})^{i})$。

考虑分块，假设每 $\displaystyle T=\lfloor \sqrt{n} \rfloor$ 一块。

那么第 $k$ 块内的答案为 $\displaystyle \prod_{i=0}^{T-1}(1+\frac{b}{a}(\frac{\beta}{\alpha})^{i+kT})=\prod_{i=0}^{T-1}(1+\frac{b}{a}(\frac{\beta}{\alpha})^{i}((\frac{\beta}{\alpha})^{T})^k)$，那么设 $c=(\frac{\beta}{\alpha})^{T}$，则可以表达为 $\displaystyle \prod_{i=0}^{T-1}(1+\frac{b}{a}(\frac{\beta}{\alpha})^{i}c^k)$。

设多项式 $\displaystyle F_{T}(x)=\prod_{i=0}^{T-1}(1+\frac{b}{a}(\frac{\beta}{\alpha})^{i}x)$，那么所求即为 $F(c^0),F(c^1) \dots$，用分治 FFT 和多项式多点求值即可做到 $O(T \log^2 T)$。

但是当然可以做到更优。

先思考如何快速求出来 $F_T(x)$，发现 $\displaystyle F_{2k}(x)=F_k(x)F_k((\frac{\beta}{\alpha})^{k}x)$，那么复杂度 $T(n)=T(\frac{n}{2})+n\log n=O(n\log n)$。

接下来就是如何求出 $F(c^0),F(c^1) \dots$，可以使用 chirp-z transform，做到 $O(T \log T)$。

### 3. Code

放个代码。

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef unsigned long long ULL;
const int mod=998244353,G=21;
inline int add(int a,int b){return ((a+=b)>=mod)?a-mod:a;}
int qmi(int a,int b)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod;
		b>>=1;
	}
	return ans;
}
struct Node{
	int a,b;
	friend Node operator+(const Node a,const Node b)
	{return (Node){add(a.a,b.a),add(a.b,b.b)};}
	friend Node operator-(const Node a,const Node b)
	{return (Node){add(a.a,mod-b.a),add(a.b,mod-b.b)};}
	friend Node operator*(const Node a,const int b)
	{return (Node){1ll*a.a*b%mod,1ll*a.b*b%mod};}
	friend Node operator*(const int b,const Node a)
	{return (Node){1ll*a.a*b%mod,1ll*a.b*b%mod};}
	friend Node operator*(const Node a,const Node b)
	{return {(1ll*a.a*b.a+5ll*a.b*b.b)%mod,(1ll*a.a*b.b+1ll*a.b*b.a)%mod};}
	friend Node operator/(Node a,Node b)
	{
		int x=(1ll*b.a*b.a-5ll*b.b*b.b)%mod;
		if(x<0)x+=mod;
		b.b=mod-b.b;a=a*b;
		return a*qmi(x,mod-2);
	}
};
Node qmi(Node a,int b)
{
	Node ans={1,0};
	while(b){
		if(b&1)ans=ans*a;
		a=a*a,b>>=1;
	}
	return ans;
}
int iv[(1<<G)+5],w[1<<G];
static const int g=3,ig=qmi(g,mod-2),im=qmi(g,(mod-1)>>2);
void init()
{
	w[0]=iv[1]=1;LL f;
	const int x=qmi(g,(mod-1)>>G);
	for(int i=0;i+1<G;i++){
		f=qmi(x,1<<G-i-2);
		for(int j=(1<<i);j<(1<<i+1);j++)w[j]=f*w[j^(1<<i)]%mod;
	}
	for(int i=2;i<=(1<<G);i++)iv[i]=1ll*(mod-mod/i)*iv[mod%i]%mod;
}
struct poly:vector<Node>{
friend inline void formalize(poly &a)
{int n=1;while(n<a.size())n<<=1;a.resize(n);return;}
friend void ntt(poly &a,int ty)
{
	int n=a.size();Node g,h;if(ty==1){
		for(int len=n>>1;len;len>>=1)
			for(int j=0,x=0;j<n;j+=(len<<1),x++)
				for(int i=j;i<j+len;i++)
					g=a[i],h=a[i+len]*w[x],a[i]=g+h,a[i+len]=g-h;
	}else{
		for(int len=1;len<n;len<<=1)
			for(int j=0,x=0;j<n;j+=(len<<1),x++)
				for(int i=j;i<j+len;i++)
					g=a[i],h=a[i+len],a[i]=g+h,a[i+len]=(g-h)*w[x];
		
		const int inv=iv[n];
		for(int i=0;i<n;i++)a[i]=inv*a[i];
		reverse(a.begin()+1,a.end());
	}
}
friend void operator+=(poly &a,poly b)
{
	int len=max(a.size(),b.size());
	a.resize(len);
	for(int i=0;i<b.size();i++)a[i]=a[i]+b[i];
}
friend void operator*=(poly &a,poly b)
{
	int len=a.size()+b.size()-1;
	a.resize(len),b.resize(len);
	formalize(a),formalize(b);
	ntt(a,1),ntt(b,1);
	for(int i=0;i<a.size();i++)a[i]=a[i]*b[i];
	ntt(a,-1),a.resize(len);
}
};
const int MOD=mod*2+2,T=sqrt(MOD)+1;
LL n;
int x,y;
Node a,b,c,d,pw1[T+5],pw2[T+5];
poly f,t;
inline void get(int n)
{
	if(n==1){
		f.resize(2);
		f[0]={1,0},f[1]=d;
		return;
	}
	if(n&1){
		get(n-1);
		Node x=d*qmi(b,n-1);
		t=f;t.push_back({0,0});
		for(int i=t.size()-1;i>=1;i--)t[i]=t[i-1]*x;
		t[0]={0,0};
		f+=t;
	}
	else{
		get(n>>1);t=f;Node x=qmi(b,n>>1),s={1,0};
		for(int i=0;i<t.size();i++)t[i]=t[i]*s,s=s*x;
		f*=t;
	}
}
void init(Node x)
{
	pw1[0]={1,0};pw2[0]={1,0};
	for(int i=1;i<=T;i++)pw1[i]=pw1[i-1]*x;
	for(int i=1;i<=T;i++)pw2[i]=pw2[i-1]*pw1[T];
}
Node qmi(int b){return pw1[b%T]*pw2[b/T];}
int calc(int n)
{
	int x=T+1,y=n/T,i;
	poly g;
	Node s={1,0};
	for(i=0;i<y;i++)s=s*f[i];
	Node t=d*qmi(b,y*T);
	for(i=y*T;i<n;i++)s=s*(t+(Node){1,0}),t=t*b;
	s=s*qmi(c,n)*qmi(a,((LL)n*(n-1)>>1)%MOD);
	return s.a;
}
void solve()
{
	int i;
	cin>>n>>x>>y;
	b=b*a;
	c=(Node){y,0}-x*b,d=(Node){x,0}*a-(Node){y,0};
	c=c/(Node){0,1},d=d/(Node){0,1};
	b=b/a,d=d/c;
	Node w=qmi(b,T);
	init(w),get(T);
	f.resize(T<<1),t.resize(T<<1);
	for(i=0;i<=T;i++)f[i]=f[i]*qmi(MOD-((LL)i*(i-1)>>1)%MOD);
	for(i=0;i<(T<<1);i++)t[(T<<1)-1-i]=qmi(((LL)i*(i-1)>>1)%MOD);
	f*=t;
	for(i=0;i<T;i++)f[i]=f[(T<<1)-1-i]*qmi(MOD-((LL)i*(i-1)>>1)%MOD);
	int s=calc(n%MOD);
	if(n<=MOD)return cout<<s<<'\n',void();
	int t=calc(MOD);
	cout<<1ll*s*qmi(t,n/MOD)%mod<<'\n';
}
signed main()
{
	int _;
	cin>>_;
	init();
	a=(Node){iv[2],iv[2]},b=(Node){iv[2],mod-iv[2]};
	b=b/a;
	while(_--)solve();
}
```

---

