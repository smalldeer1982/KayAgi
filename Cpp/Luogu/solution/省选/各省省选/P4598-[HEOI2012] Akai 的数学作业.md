# [HEOI2012] Akai 的数学作业

## 题目背景

这里是广袤无垠的宇宙

这里是一泻千里的银河

这里是独一无二的太阳系

这里是蔚蓝色的地球

这里，就是这里，是富饶的中国大陆！

这里是神奇的河北大地

这里是美丽的唐山

这里是神话般的唐山一中

这里是 Akai 曾经的教室

## 题目描述

黑板上还留有当年 Akai 做过的数学作业，其实也并不是什么很困难的题目:

“

给出一个一元 $n$ 次方程： 

$$a_0 + a_1x + a_2x^2 +…+ a_nx^n= 0$$ 

求此方程的所有有理数解。 

” 

Akai 至今还深刻记得当年熬夜奋战求解的时光

他甚至还能记得浪费了多少草稿纸

但是却怎么也想不起来最后的答案是多少了

你能帮助他么？

## 说明/提示

对于 30%的数据，$n\leq10$ 

对于 100%的数据，$n\leq100$，$|a_i| <= 2\times10^7$，$a_n\not= 0$

HEOI 2012 Day1 Task1

## 样例 #1

### 输入

```
3
-24 14 29 6 ```

### 输出

```
3
-4
-3/2
2/3 ```

# 题解

## 作者：nekko (赞：8)

设 $x=\frac{p}{q}$，且 $\gcd(p,q)=1$，则有：

$$\sum_{i=0}^{n}a_i\left(\frac{p}{q}\right)^i=0$$

通分得：

$$\sum_{i=0}^{n}a_ip^iq^{n-i}=0$$

在模 $p$ 意义下有：

$$a_0q^{n} \equiv 0 \bmod {p}$$

$\begin{aligned}&\because \gcd(p,q)=1 \\ &\therefore p \mid a_0 \end{aligned}$

在模 $q$ 意义下有：

$$a_0p^{n} \equiv 0 \bmod {q}$$

$\begin{aligned}&\because \gcd(p,q)=1 \\ &\therefore q \mid a_n \end{aligned}$

当然如果 $a_0=0$ 的话需要找到一个最小的 $t$ 满足 $a_t \not= 0$

然后就可以枚举 $p \mid a_0, q \mid a_n$ 了，然后暴力判断是否可行

判断的方法和 [P2312 解方程](https://www.luogu.org/problemnew/show/P2312) 这道题一样，即放到模 $mod$ 剩余系下判断是否为 $0$

时间复杂度：$O(\sqrt a_0 + \sqrt a_n + \sigma_0(a_0)\sigma_0(a_n)\gcd(\max(a_0,a_n)))$

---

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110, mod = 1e9 + 7;
int n, a[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll calc(ll p, ll q) {
    ll x = p * pw(q, mod - 2) % mod, pro = 1, res = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        res = (res + pro * a[i] % mod) % mod;
        pro = pro * x % mod;
    }
    return (res + mod) % mod == 0;
}

vector<int> split(int x) {
    x = abs(x);
    vector<int> res;
    for(int i = 1 ; i * i <= x ; ++ i)
        if(x % i == 0) {
            res.push_back(i);
            if(i != x / i) res.push_back(x / i);
        }
    return res;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b ) : a;
}

struct T { ll p, q; };
vector<T> ans;
bool cmp(T a, T b) {
    return a.p * b.q < a.q * b.p;
}
bool operator == (T a, T b) {
    return a.p == b.p && a.q == b.q;
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i <= n ; ++ i) scanf("%d", &a[i]);
    int pos = 0; while(a[pos] == 0) ++ pos;
    vector<int> P = split(a[pos]),
                Q = split(a[n]);
    for(int i = 0 ; i < P.size() ; ++ i) {
        for(int j = 0 ; j < Q.size() ; ++ j) {
            int p = P[i], q = Q[j];
            if(gcd(p, q) == 1) {
                if(calc(p, q)) ans.push_back((T) { p, q });
                if(calc(-p, q)) ans.push_back((T) { -p, q });
            }
        }
    } 
    if(calc(0, 1)) ans.push_back((T) { 0, 1 });
    sort(ans.begin(), ans.end(), cmp);
    printf("%d\n", (int) ans.size());
    for(int i = 0 ; i < ans.size() ; ++ i) {
        ll p = ans[i].p, q = ans[i].q;
        if(q == 1) printf("%lld\n", p);
        else printf("%lld/%lld\n", p, q);
    }
}
```

---

## 作者：i207M (赞：8)

一看这道题，wdtn，HEOI2012D1T1考这么难的？求$n\le 100$次方程的所有有理数解？？？

不是说$\ge 4$次方程就没有求根公式了吗，难道数学又有了新的突破？？？~~抄题解去了~~

~~其实我觉得，其他题解对于，为什么$a[0]=0$时，要找最低的非0位解释的很匆忙，有一些漏洞~~

[idea from this](https://www.cnblogs.com/yousiki/p/6404149.html)

定理叫做多项式**高斯引理** ，大意是，复数域下的一个关于x的n次多项式$f(x)=a_{0}+a_{1}x+a_{2}x^{2}+a_{3}x^{3}+...+a_{n}x^{n}$，一定可以分解成n个含x的一次多项式相乘，即f(x)一定存在一种形如$f(x)=\prod{(b_{i}x+c_{i})}$的表示，其中每个式子都会产生一个复数域下的根（当然，这些根有可能重复）

这道题叫我们只用考虑有理数根，所以可以把式子改写为$f(x)=g(x)\prod{(b_{i}x+c_{i})}$的样子，其中g(x)是一个关于x的多项式，包含了所有的非有理数根，剩下的部分就表示了所有的有理数根。

发现每个有理数根都能表示成$x_{i}=\frac{c_{i}}{b_{i}}$，然后不难发现$f(x)=\sum_{i=0}^{n}{a_{i}x^{i}}$中的$a_0$包含了所有的$c_i$，而$a_n$包含了所有的$b_i$，所以**对于所有的合法有理数根$x_{i}=\frac{c_{i}}{b_{i}}$，$c_i$一定是$a_0$的约数，$b_i$一定是$a_n$的约数**。

所以可以先处理出$a_0$和$a_n$的所有约数，然后暴力枚举$b_i$和$c_i$，O(N)check是否合法即可。

check的方法是对一个大质数取模。

如果$a_0=0$怎么办？我们在答案中添加$x=0$的解，同时不断除掉x，放到$g(x)$中，直到最低不为0的项。

```cpp
#define N 105
int n;
int a[N];
il int F(int x)
{
	int r=0;
	for(ri i=n; i>=0; --i) r=add(mul(r,x),a[i]);
	return r;
}
void divi(int x,vector<int> &d)
{
	for(ri i=1; i*i<=x; ++i)
		if(x%i==0)
		{
			d.pb(i);
			if(i*i!=x) d.pb(x/i);
		}
}
vector<int>d[2];
vector<pii>ans;
il bool cmp(const pii &a,const pii &b)
{
	return (LL)a.fi*b.se<(LL)a.se*b.fi;
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n);
	for(ri i=0; i<=n; ++i) in(a[i]);
	int p=0;
	while(p<n&&a[p]==0) ++p;
	if(p==n)
	{
		out(0);
		return 0;
	}
	divi(abs(a[p]),d[0]),divi(abs(a[n]),d[1]);
	for(solid x:d[0]) for(solid y:d[1])
			if(__gcd(x,y)==1)
			{
				int t=mdinv(y);
				if(F(mul(x,t))==0) ans.pb(mp(x,y));
				if(F(mul(md-x,t))==0) ans.pb(mp(-x,y));
			}
	if(!a[0]) ans.pb(mp(0,1));
	sort(ans.begin(),ans.end(),cmp);
	out(Size(ans));
	for(solid v:ans)
		if(v.se==1) out(v.fi);
		else printf("%d/%d\n",v.fi,v.se);
	return 0;
}
```


---

## 作者：Akoasm_X (赞：5)

**之前的题解讲的挺清楚的，不过在检验答案时采取了比较复杂的方法，比如乘法逆元或者快速幂，我用了比较简单的计算方法。此外，代码的可读性对于萌新不太友好，~~我就没看明白~~，所以来交一次题解**

**做法：** 题目要求解以分数的形式输出，要求分子和分母互质，且分母必须是正整数，对于每个解可写为（p/q）其中p和q互质，那么方程可以写为(a[0]+a[1] * p/q+a[2] * (p/q)^2……a[n] * (p/q)^n) = 0。

左右两边同乘q^n 得到（a[0] * q^n+a[1]  * q^(n-1)*p……a[n] * p^ n） = 0。式子再模p，那么a[1]到a[n]都是等于0的,所以 （a[0] * q^n % p） 也应该等于0，前面说了p,q互质,**那么得出结论 分子p 被a[0]整除 ,同理，分母q被a[n]整除。**

那么我们算出所有满足条件的数，代入检验即可。**但我们不能保证a[0]!=0,所以结论里的a[0]其实应该代表最靠前的非零位**

**检验过程：** 只需要正序扫一遍，把每项都乘p^(i-1)，次幂的处理没必要用快速幂，直接定义变量，每次乘p即可。接下来倒序扫一遍，每项都乘q^(n-i+1),也是如此，注意取模即可

**还有要注意检验x=0的情况**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1231238613;
int n,cnt1,cnt2,cnt;
int data[105],p1[10005],p2[10005];
struct node
{
	int a,b;
}ans[105];

bool cmp(node x,node y)
{
	return 1ll * x.a * y.b < 1ll * y.a * x.b ;
}

int gcd(int a,int b)
{
	if(!b)
		return a;
	else
		return gcd(b,a%b);
}

bool judge(int x,int y)//判断是否可行 
{
	int temp[105];
	memset(temp,0,sizeof(temp));
	int a = 1,b = 1,sum = 0;
	for(int i=0;i<=n;i++)
	{
		temp[i] = (1ll*data[i]*a % mod + mod)%mod;
		a = 1ll*a*x%mod;
	}
	for(int i=n;i>=0;i--)
	{
		sum = (sum+1ll*temp[i]*b % mod+ mod)%mod;
		b = 1ll*b*y%mod;
	}
	return sum==0;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		scanf("%d",&data[i]);
	int t = 0;
	while(data[t]==0)
		t++;
	//找到第一个非零位 
	for(int i=1;i*i<=abs(data[t]);i++)
	{
		if(abs(data[t])%i==0)
		{
			p1[++cnt1] = i;
			if(i*i!=abs(data[t])&&abs(data[t])/i!=0)
				p1[++cnt1] = abs(data[t])/i;
		}
	} 
	for(int i=1;i*i<=abs(data[n]);i++)
	{
		if(abs(data[n])%i==0)
		{
			p2[++cnt2] = i;
			if(abs(data[n])/i!=0&&i*i!=abs(data[n]))
				p2[++cnt2] = abs(data[n])/i ;
		}
	}
	//取出data[t]和data[n]的约数
	for(int i=1;i<=cnt1;i++)
	{
		for(int j=1;j<=cnt2;j++)
		{
			if(gcd(p1[i],p2[j])!=1)
				continue;
			//枚举各自约数，如果是互质再判断是不是解 
			if(judge(p1[i],p2[j]))
			{
				ans[++cnt].a = p1[i];
				ans[cnt].b   = p2[j];
			}
			if(judge(-p1[i],p2[j]))
			{
				ans[++cnt].a = -p1[i];
				ans[cnt].b   = p2[j];
			}
			//正负有理数解 
		}
	}
	if(judge(0,1))
	{
		ans[++cnt].a = 0;
		ans[cnt].b   = 1;
	}//特判0的情况 
	printf("%d\n",cnt);
	sort(ans+1,ans+1+cnt,cmp);//对答案排序 
	for(int i=1;i<=cnt;i++)
	{
		if(ans[i].b==1)
			printf("%d\n",ans[i].a);
		else
			printf("%d/%d\n",ans[i].a,ans[i].b);
	}
	return 0;
}
```
完结撒花

---

## 作者：Conical (赞：3)

# Description

给定一个数列 $a$，求 $a_0+a_1x+a_2x^2+\dots+a_nx^n=0$ 的所有有理数解。

# Solution

既然题目要求的是有理数解，我们考虑设 $x=\dfrac p q $，其中 $p$ 和 $q$ 互质。那么原方程可化简为：

$$a_0 + a_1\dfrac p q+a_2\left(\dfrac p q\right)^2 + \dots+a_n\left(\dfrac p q\right)^n=0$$

方程两边同乘 $q^n$，可得：

$$\sum_{i=0}^na_ip^iq^{n-i}=0$$

考虑在模 $p$ 意义下：

$$a_0q^n\equiv0\bmod p$$

由于 $p,q$ 互质，必定有 $p\mid a_0$。同理，必定有 $q\mid a_n$。由于最低项可能为 $0$，我们以第一个不为 $0$ 的项作为基准，枚举互质的 $p,q$ ，在多个质数的模意义下判断是否为 $0$ 即可。注意处理负数解的情况。

---

## 作者：zyn_ (赞：1)

首先把 $x=0$ 判了，下设 $a_0\neq 0$。由于 $x$ 是有理数，设 $x=\dfrac{p}{q}$，其中 $q>0$，$\gcd(p,q)=1$。代入方程得

$$
\sum_{i=0}^n a_i(\frac{p}{q})^i=0 \\
\sum_{i=0}^n a_ip^iq^{n-i}=0 \\
a_0q^n\equiv 0\pmod p \\
a_np^n\equiv 0\pmod q
$$

于是 $p\mid a_0$，$q\mid a_n$。枚举 $(p,q)$（注意 $p$ 可能为负）并验证即可。注意到使 $p\mid a_0$，$q\mid a_n$，$p,q>0$ 且 $p,q$ 互质的二元组 $(p,q)$ 有 $d(a_0a_n)$ 对（$d(n)$ 代表 $n$ 的正因子个数）（这个结论请自证）。时间复杂度 $O(\sqrt{a_0}+\sqrt{a_n}+d(a_0)d(a_n)+nd(a_0a_n))$，精细实现可以 $O(\sqrt{a_0}+\sqrt{a_n}+nd(a_0a_n))$……吗？

等等，如何验证一个 $x$ 是否是方程的根？直接代入原式的话，$x$ 是个分数，就不好办了。如果代入

$$
\sum_{i=0}^n a_ip^iq^{n-i}=0
$$

显然要爆 `long long`。寄！

有一种解法，是把这个式子对大质数取模，多选几个质数，只有每次都算出 $0$ 才认为 $x$ 是根。虽然这样能过，但是：要写快速幂；常数大；实现不当还会使复杂度带上 $O(\log V)$……能不能再优秀一点？

学因式分解时，你应该接触过试根法（其实本题就是试根法的板子）。想想看手算时是如何验根的？

比如 $6 x^3 - 7 x^2 - 28 x + 20=0$，要验根 $x=\dfrac{2}{3}$。如果直接代入算，那么 $6x^3$，$-7x^2$ 这些项总有点麻烦。这里给出一种方法：

$$
\begin{aligned}
6&=6 \\
6x-7&=\frac{2}{3}\times 6-7=-3 \\
6x^2-7x-28&=x(6x-7)-28=\frac{2}{3}\times(-3)-28=-30 \\
6x^3-7x^2-28x+20&=x(6x^2-7x-28)+20=\frac{2}{3}\times(-30)+20=0
\end{aligned}
$$

于是 $x=\dfrac{2}{3}$ 是根。

如果要验根 $x=\dfrac{4}{3}$：

$$
\begin{aligned}
6&=6 \\
6x-7&=\frac{4}{3}\times 6-7=1 \\
6x^2-7x-28&=x(6x-7)-28=\frac{4}{3}\times 1-28=-\frac{80}{3}\\
\end{aligned}
$$

这一项不是整数了。那么**结论是，$x=\dfrac{4}{3}$ 不是根。**

为什么结论是对的？

先刻画一下以上验根的过程。若 $f(x)=\sum_{i=0}^n a_ix^i$：

1. 初始令 $y=a_n$。
2. 遍历 $i=n-1,n-2,\dots,1,0$，令 $y\gets yx+a_i$。
3. $x$ 是根当且仅当最终 $y=0$。

过程正确性显然，一层层代入即可验证。

仍设 $x=\dfrac{p}{q}$。如果在某一步中 $y$ 不是整数了，$y=\dfrac{r}{s}$，$\gcd(r,s)=1$，那么之后 $y$ 可能变回整数吗？结论是，**不能**。

这是因为，$y$ 是因为乘了 $x$ 变成分数的，$y$ 的分母 $s$ 的质因子都来自 $x$ 的分母 $q$。而 $\gcd(p,q)=1$，因此 $\gcd(p,s)=1$。为了使 $y$ 变回整数，$yx=\dfrac{r}{s}\times\dfrac{p}{q}$ 应为整数，而 $\gcd(r,s)=1$，为了约去 $s$，只能通过 $p$。矛盾！

好，有了这个结论，验根时就可以避开分数了。然而即使每步的运算结果均为整数，还是有爆 `long long` 的风险！怎么办？

令值域 $V=2\times 10^7$。再次考察给出的验根的过程，可以发现：

1. 如果 $|x|\le 1$ 则 $|y|$ 全程不超过 $nV$。事实上，最终 $|y|=|\sum_{i=0}^na_ix^i|\le\sum_{i=0}^n|a_ix^i|\le\sum_{i=0}^n|a_i|\le nV$，并且过程中每一步的 $y$ 都相当于一个系数为 $a_n,a_{n-1},\dots,a_{n-k}$，次数为 $k$ 的多项式的点值，其值也不超过 $nV$。
2. 如果 $|x|\gt 1$，则可以修改以上验根过程：如果某一步中 $|y|\gt nV$，则**直接判定所验的根不是正确的根**。不失一般性，设 $x>1$，$y>nV$。那么接下来每一次 $y\gets yx+a_i$ 都至多让 $y$ 减少 $V$，一共至多减少 $nV$，导致最终 $y$ 不可能为 $0$。

这样就不会爆 `long long` 了。

没有精细实现，但是[暂时最优解](https://www.luogu.com.cn/record/201945684)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 109
#define M 2000000000
int n,z,cnt;ll a[N],x,y;
struct frac{ll x,y;/*x/y, y>0*/}r[N];
inline bool cmp(const frac&a,const frac&b){
	return a.x*b.y<b.x*a.y;
}
inline void output(const frac&f){
	if(f.y==1)printf("%lld",f.x);
	else printf("%lld/%lld",f.x,f.y);
}
vector<ll> l1,l2;
bool check(ll x,ll y)/*x/y*/{
	ll t=a[n];
	for(int i=n-1;i>=0;--i){
		if(llabs(t)>M)return 0;
		if(t%y)return 0;
		t=t*x/y+a[i];
	}
	return t==0;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;++i)scanf("%lld",&a[i]);
	if(a[0]==0){
		r[++cnt]={0,1};
		while(a[z]==0)++z;
		for(int i=0;i<=n-z;++i)a[i]=a[i+z];
		n-=z;
	}
	x=llabs(a[0]),y=llabs(a[n]);
	for(ll i=1;i*i<=x;++i)if(x%i==0){
		l1.push_back(i);
		if(i*i!=x)l1.push_back(x/i);
	}
	for(ll i=1;i*i<=y;++i)if(y%i==0){
		l2.push_back(i);
		if(i*i!=y)l2.push_back(y/i);
	}
	for(ll i:l1)for(ll j:l2)if(__gcd(i,j)==1){
		if(check(i,j))r[++cnt]={i,j};
		if(check(-i,j))r[++cnt]={-i,j};
	}
	sort(r+1,r+cnt+1,cmp);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)output(r[i]),puts("");
	return 0;
}
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：0)

### 题目解读：
给一个一元 $n$ 次方程并求出有理数解，系数分别从 $a_0$ 到 $a_n$。
### 思路分析：
首先，我们知道大于四次的方程没有求根公式，所以这题是没法很容易求出所有解的，所以我们需要开始**数论**。  
作为上过数学竞赛的，我们都学过因式分解，当然，在本题显然不能直接使用，所以我们需要转化并证明（可见小蓝本初中版因式分解）。  
我们先给出结论：  
对于任意一个有理数解为 $\frac{p}{q}$（$p,q\in\mathbb Z,\gcd(p,q)=1,q\ne0$），满足 $p\mid a_0,q\mid a_n$。  
下面给出证明过程：  
因为
$$
\sum_{i = 0}^{n} a_ix^i=0
$$
所以
$$
\sum_{i = 0}^{n} a_i(\frac{p}{q})^i=0
$$
同时乘上 $q^n$ 后有
$$
\sum_{i = 0}^{n} a_ip^iq^{n-i}=0
$$
在模 $p$ 意义下有
$$
a_0q^n≡0\bmod p
$$
因为 $\gcd(p,q)=1$，所以 $p\mid a_0$。同理可得 $q\mid a_n$。  
因此我们可以枚举 $a_0,a_n$ 的因子，然后去判断是否符合等式。  
但是注意到 $a_0$ 可以为 $0$，所以我们应该找到第一个不为 $0$ 的数来替代 $a_0$，相当于将原式除以了一个 $x$ 的整数次方。**注意此时还有一个解为** $0$。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long p,q;
}ans[105];
long long gs;
bool cmp(node a,node b){
	return a.p*b.q<b.p*a.q; 
}
long long n;
long long a[105];
vector<long long>p;
vector<long long>q;
long long mod=19260817;
long long qpower(long long a,long long b){
	long long res=1;
	while(b)
	{
		if(b&1)
		{
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
bool check(long long fz,long long fm){//这里可以不使用高精度，直接对一个数取模，如果怕被卡的话可以多对几个数取模 
	long long i,now=0;
	for(i=0;i<=n;i++)
	{
		now+=(a[i]*qpower(fz,i)%mod*qpower(fm,n-i)%mod);
		now%=mod;
	} 
	return (now==0);
}
int main(){

	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin>>n;
	long long i,j;
	for(i=0;i<=n;i++)
	{
		cin>>a[i];
	}
	long long wz=0;
	for(i=0;i<=n;i++)
	{
		if(a[i]!=0)
		{
			wz=i;
			break;
		}
	}
	if(a[0]==0)//特判 
	{
		gs++;
		ans[gs].p=0;
		ans[gs].q=1;
	}
	for(i=wz;i<=n;i++)//除以x^wz 
	{
		a[i-wz]=a[i];
	}
	n-=wz;
	for(i=1;i*i<=abs(a[0]);i++)
	{
		if(abs(a[0])%i==0)
		{
			p.push_back(i);
			if(i*i!=abs(a[0]))
			{
				p.push_back(abs(a[0])/i);
			}
		}
	}
	for(i=1;i*i<=abs(a[n]);i++)
	{
		if(abs(a[n])%i==0)
		{
			q.push_back(i);
			if(i*i!=abs(a[n]))
			{
				q.push_back(abs(a[n])/i);
			}
		}
	}
	for(i=0;i<p.size();i++)
	{
		for(j=0;j<q.size();j++)
		{
			if(__gcd(p[i],q[j])==1)
			{
				if(check(p[i],q[j]))
				{
					gs++;
					ans[gs].p=p[i];
					ans[gs].q=q[j];
				}
				if(check(-p[i],q[j]))//可以在上面直接加入负因子，在这里判断同样可以 
				{
					gs++;
					ans[gs].p=-p[i];
					ans[gs].q=q[j];
				}
			}
		}
	}
	cout<<gs;
	sort(ans+1,ans+gs+1,cmp);
	for(i=1;i<=gs;i++)
	{
		cout<<"\n"<<ans[i].p;
		if(ans[i].q!=1)
		{
			cout<<"/"<<ans[i].q;
		}
	}

	return 0;
}
```

---

## 作者：lzh0220 (赞：0)

## 题意

给定一元 $n$ 次方程的 $n+1$ 个系数，求他的所有有理数解。

## 分析

感觉这道题难度到不了紫。

首先假设 $a_0\ne0$，考虑一个方程存在有理数解 $x=\frac{p}{q}$，则对该方程因式分解，一定存在形如 $qx-p$ 的因式。又由初中所学的基础因式分解知 $q \mid a_n$，$p \mid a_0$，因此可以枚举 $a_0$ 和 $a_n$ 的因数，判断是否成立即可。

考虑 $a_0=0$，则可将原方程整体提出 $x^k$ 的因式，不要忘记在答案中加入 $0$。

时间复杂度 $O(n\sigma(a_0)\sigma(a_n))$。

[code](https://www.luogu.com.cn/paste/f5lna0eg)

## 一些注意事项

- 记得判 $a_0\ne0$。

- 注意将 $p$，$q$ 约分。

---

## 作者：Dzhao (赞：0)

题意：给你一个一元 $n$ 次方程，请你求出该方程所有的有理数解。

我们设 $x=\dfrac{p}{q}(\gcd(p,q)=1)$，则原方程可以表示为：
$$\sum_{k=0}^n a_k\cdot\dfrac{p^k}{q^k}=0$$
将两边同时乘上 $q^n$，可以得到：
$$\sum_{k=0}^n a_k\cdot p^k\cdot q^{n-k}=0$$
我们发现只有 $k=0$ 时的那一项不一定为 $p$ 的倍数，所以我们可以化简得到：
$$\sum_{k=0}^n a_k\cdot p^k\cdot q^{n-k}\equiv0\ (\bmod\ p)$$
$$a_0\cdot q^n\equiv0\ (\bmod\ p)$$
而由于 $\gcd(p,q)=1$，所以可以得到 $p|a_0$，同理我们也可以得到 $q|a_n$。

所以我们只需要枚举 $p$ 和 $q$ 暴力判断就行了，当 $a_0=0$ 的时候只要不断往后移，直到找到第一个不为 $0$ 的 $a_i$ 就行了，注意特判解为 $0$ 的情况。 

由于上式加起来的过程中可能 ```long long``` 都存不下，所以我们可以考虑将上式求和的过程中对答案取模一个大质数，如果多个大质数取模后的答案都为 $0$，则该答案成立。只要选择的数的最小公倍数大于上式的最大值，就不会存在答案不为 $0$ 但是模大质数为 $0$ 了（其实本题随便选几个质数就行了，也不用选那么多），设选的质数个数为 $m$，则时间复杂度为 $\mathcal{O}(nm\sigma_0(a_0)\sigma_0(a_n)\log(\max(a_0,a_n)))$。

$\mathcal{View\ Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 105;
int n, a[N], pr[20], tot;
struct node {int p, q;} ans[N];
vector <int> vp, vq;
inline bool cmp(node a, node b) {
	return a.p * b.q < a.q * b.p;
}
int ksm(int x, int y, int P) {
	int res = 1;
	while(y) {
		if(y & 1) res = res * x % P;
		x = x * x % P, y >>= 1;
	}
	return res;
}
bool check(int p, int q) {
	for(int i = 0; i <= 11; i++) {
		int sum = 0;
		for(int k = 0; k <= n; k++)
			sum = (sum + a[k] * ksm(p, k, pr[i]) % pr[i] * ksm(q, n - k, pr[i]) % pr[i] + pr[i]) % pr[i];
		if(sum != 0) return 0;		
	}
	return 1;
}

signed main() {
	scanf("%lld", &n); for(int i = 0; i <= n; i++) scanf("%lld", &a[i]);
	pr[0] = 998244353, pr[1] = 993244353, pr[2] = 993244853;
	pr[3] = 998244853, pr[4] = 19260817, pr[5] = 1000000007;
	pr[6] = 10000019, pr[7] = 10000079, pr[8] = 10000103;
	pr[9] = 100000471, pr[10] = 100000609, pr[11] = 100000687;
	int pos = 0; while(a[pos] == 0) pos++;
	int a0 = abs(a[pos]), an = abs(a[n]);
	for(int p = 1; p * p <= a0; p++) 
		if(a0 % p == 0) {
			vp.push_back(p);
			if(p != a0 / p) vp.push_back(a0 / p);
		}
	for(int q = 1; q * q <= an; q++)
		if(an % q == 0) {
			vq.push_back(q);
			if(q != an / q) vq.push_back(an / q);
		}
	for(auto p : vp) for(auto q : vq) {
		if(__gcd(p, q) == 1) {
			if(check(p, q)) ans[++tot] = (node){p, q};
			if(check(-p, q)) ans[++tot] = (node){-p, q};
		}
	}
	if(check(0, 1)) ans[++tot] = (node){0, 1};
	sort(ans + 1, ans + 1 + tot, cmp);
	printf("%lld\n", tot);
	for(int i = 1; i <= tot; i++) 
		if(ans[i].q == 1) printf("%lld\n", ans[i].p);
		else printf("%lld/%lld\n", ans[i].p, ans[i].q);
	return 0;
}
```


---

