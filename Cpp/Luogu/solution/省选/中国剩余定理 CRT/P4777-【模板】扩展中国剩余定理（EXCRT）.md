# 【模板】扩展中国剩余定理（EXCRT）

## 题目描述

给定 $n$ 组非负整数 $a_i, b_i$ ，求解关于 $x$ 的方程组的最小非负整数解。
$$\begin{cases}x\equiv b_1\pmod{a_1}\\x\equiv b_2\pmod{a_2}\\\dots\\x\equiv b_n\pmod{a_n}\end{cases}$$

## 说明/提示

对于 $100 \%$ 的数据，$1 \le n \le {10}^5$，$1 \le b_i,a_i \le {10}^{12}$，保证所有 $a_i$ 的最小公倍数不超过 ${10}^{18}$。

**请注意程序运行过程中进行乘法运算时结果可能有溢出的风险。**

数据保证有解。

## 样例 #1

### 输入

```
3
11 6
25 9
33 17
```

### 输出

```
809```

# 题解

## 作者：阮行止 (赞：617)

　　中国剩余定理(CRT)不能解决模数不互质情况的模线性同余方程组。这是中国剩余定理的原理所决定的。来看中国剩余定理的形式：
  $$\text{ans} \equiv \sum_{i} r_i \cdot M_i \cdot \text{inv}(M_i, m_i) \pmod M$$
  
　　其中的 $\text{inv}(M_i, m_i)$ 在 $M_i, m_i$ 不互质的情况下，根本不存在。而只要有任意两个模数不互质，就会产生 $M_i, m_i$ 不互质的情况，从而破坏掉整个解。
  
  
　　如果bug比较小，我们能否进行修复？很遗憾，这条路是没有希望的。CRT不能解决模不互质方程组的本质困难在于：CRT最核心的思想是构造一组 $R_i$ ，使得
  $$\begin{cases}R_i \% m_i=1 \\ R_i \% m_k = 0 ~ (i \neq k)\end{cases}$$
  
  
　　$R_i$的性质是如此美好，我们只需要把 $r_1R_1+r_2R_2+\cdots +r_nR_n$ 作为答案输出就行了。很显然，这个和式模 $m_1$ 余 $r_1$， 模 $m_2$ 余 $r_2$……总之完美地满足了我们的需求。但也就是这个 $R_i$ 需要用到逆元，使得CRT无法应对模不互质的情况。这个缺陷是在于CRT的核心思想，给它动小手术是没有用的。我们想找到解模不互质方程组的办法，就必须完全跳出CRT的窠臼。
  
  
　　那么我们应该怎么做呢？方程组是由很多个模线性同余方程构成的。假设我们能把两个模线性同余方程组，等价地合并成一个方程，问题就迎刃而解了——只需要不停地合并这些方程，只到只剩下一个。
  
  
　　理想是美好的，道路是曲折的。首先，未必两个方程可以合并成一个方程（我们可能找不到快速的实现方式）。此外，即使可以把两个方程合并成一个，这个变换也未必是等价变换（可能新方程的解未必是原方程的解，也可能原方程的解被新方程漏掉了）。我们要做的事情是：给出将两个方程合并成一个方程的方法，然后证明这个变换的等价性。
  
---
  
## 数学基础 
　　作为我们接下来讨论的基础，我想先展示几个例子。它们的规模都很小，完全可以手工验证。
  
$$\begin{cases}x \equiv 2 \pmod 4 \\ x \equiv 4 \pmod 6\end{cases} \quad \Rightarrow \quad x\equiv 10 \pmod {12}$$
$$\begin{cases}x \equiv 4 \pmod 6 \\ x \equiv 3 \pmod 5\end{cases} \quad \Rightarrow \quad x\equiv 28 \pmod {30}$$
$$\begin{cases}x \equiv 2 \pmod 4 \\ x \equiv 3 \pmod 6\end{cases} \quad \Rightarrow \quad \varnothing$$

　　可以粗略地总结出几个规律：
- 新方程与原方程具有同样的形式。
- 新方程的模数，是之前两个模数的lcm.
- 可能存在无解的情况

这几条性质是整个算法的基石，我们会在后文详细讨论。这里先一步步摸出 “合并” 的算法。形式化地，考虑这样一组模线性同余方程：

  $$\begin{cases}a \equiv r_1 \pmod {m_1} \\ a \equiv r_2 \pmod {m_2}\end{cases}$$
  
　　这个方程组等价于：
  $$a = k_1m_1 + r_1 = k_2m_2 + r_2$$
　　移一下项，立刻有 
  $$k_1m_1 - k_2m_2 = r_2 - r_1$$
　　左边的$m_1, m_2$，右边的 $r_2-r_1$是已知量。这就是一个典型的不定方程。解不定方程这个任务，我们是熟悉的：可以通过裴蜀定理判断有没有解，可以用扩展欧几里得算法(exgcd)给出 $(k_1, k_2)$ 的整个解系。于是算法有了第一步：
  

- 如果 $\gcd(m_1, m_2) | (r_2-r_1)$，则判断方程有解
- 否则，报告无解

　接下来考虑如何求出一组 $k_1, k_2$. 约定几个记号：记 $d = \gcd(m_1, m_2), ~p_1=\frac{m_1}{d}, ~ p_2=\frac{m_2}{d}$. 显然 $p_1, p_2$ 是互质的。 那么把 $m_1$ 用 $p_1 d$来代替，$m_2$ 用 $p_2 d$来代替，可以把上面的式子写成：
 $$k_1 p_1 - k_2p_2 = \frac{r_2 - r_1}{d}$$
　　右边那一串东西是整数，因为当且仅当 $d | (r_2-r_1)$ 才会有解。左边满足了 $\gcd(p_1, p_2)$ 互质，因此求出整个解系是很容易的。现在假设我们拿exgcd求出了下面这个方程的解 $(\lambda_1, \lambda_2)$：
  $$\lambda_1p_1 + \lambda_2p_2 = 1$$
　　这是一个非常标准的exgcd. 求出来了 $\lambda_1, \lambda_2$ 之后，可以直接拼出 $k_1, k_2$：
  $$\begin{cases}k_1 = \frac{r_2-r_1}{d}\lambda_1 \\ k_2 = - \frac{r_2-r_1}{d}\lambda 2\end{cases}$$
　　于是
  $$x=r_1+k_1m_1 = r_1 + \frac{r_2-r_1}{d}\lambda_1m_1$$
　　至此，我们成功地构造出了一个 $x$，满足 $\begin{cases}x \equiv r_1 \pmod {m_1} \\ x \equiv r_2 \pmod {m_2}\end{cases}$. 但是整个解系如何给出呢？我们有
  
  
**【定理】** 若有特解 $x^*$, 那么 $\begin{cases}x \equiv r_1 \pmod {m_1} \\ x \equiv r_2 \pmod {m_2}\end{cases}$ 的通解是：$x ^ * + k\cdot \text{lcm}(m_1, m_2)$，亦即
$$x \equiv x^* \pmod {\text{lcm}(m_1, m_2)}$$

　　从线性代数的角度讲，这个通解的构造方式是十分平凡的。对 $\text{lcm}(m_1, m_2)$ 取模的结果，将整个整数集划分成了 $\text{lcm}(m_1, m_2)$ 个等价类，哪个等价类里面有特解，那整个等价类肯定全都是解。一人得道，鸡犬升天。接下来唯一需要说明的事情就是：为什么任意一个完全剩余系里面，只会有一个解？这个问题等价于：为什么 $0, 1,2,\cdots ,\text{lcm}(m_1, m_2)$ 里面，只有一个解？
  
  
　　证明解的唯一性，常常采用这样一种手段：假设 $x, y$ 都是原问题的解，然后经过一系列推理，得到 $x=y$，于是解的唯一性就不言而喻了。我们也采用这种手段来解决唯一性问题。设上述集合里面有 $0\leq x, y \leq \text{lcm}(m_1, m_2)$ 满足 
  $$\begin{cases}x\equiv a_1 \pmod {m_1} \\ x\equiv a_2 \pmod {m_2}\end{cases} ~ , ~ \begin{cases}y\equiv a_1 \pmod {m_1} \\ y\equiv a_2 \pmod {m_2}\end{cases}$$
　　不妨设 $x\geq y$. 那立刻就可以发现
  $$\begin{cases}(x-y) \bmod m_1 = 0 \\ (x-y) \bmod m_2 = 0\end{cases} \quad \Rightarrow \quad\text{lcm}(m_1, m_2) ~ | ~ (x-y) $$
　　$x, y$ 都是小于 $\text{lcm}(m_1, m_2)$ 的数，它们的差也必然要小于  $\text{lcm}(m_1, m_2)$. 但 $(x-y)$ 又要被 $\text{lcm}(m_1, m_2)$ 整除，那怎么办？只有 $x-y=0$，也就是 $x=y$. 到此为止，我们证明了：一个完全剩余系中，有且仅有一个解。以上就是整个 exCRT 算法的全部数学基础。
  

### 算法流程及实现
1. 读入所有方程组。
2. 弹出两个方程，先判断有没有解。
    - 无解：报告异常
    - 有解：合并成同一个方程，然后压进方程组
3. 执行上述步骤(2), 直到只剩下一个方程。这个方程就是解系。 

本题代码如下：
```python
from functools import reduce

def gcd(a, b):
    if b==0: return a
    return gcd(b, a%b)

def lcm(a, b):
    return a * b // gcd(a,b)

def exgcd(a, b):
    if b==0: return 1, 0
    x, y = exgcd(b, a%b)
    return y, x - a//b*y

def uni(P, Q):
    r1, m1 = P
    r2, m2 = Q

    d = gcd(m1, m2)
    assert (r2-r1) % d == 0

    l1, l2 = exgcd(m1//d, m2//d)
    
    return (r1 + (r2-r1)//d*l1*m1) % lcm(m1, m2), lcm(m1, m2)

def CRT(eq):
    return reduce(uni, eq)

if __name__ == "__main__":
    n = int(input())
    eq = [list(map(int, input().strip().split()))[::-1] for x in range(n)]
    print(CRT(eq)[0])
```

---

## 作者：未来姚班zyl (赞：163)

## 题目大意

求解同余方程组：

$$\begin{cases} x \equiv b_1\ ({\rm mod}\ a_1) \\ x\equiv b_2\ ({\rm mod}\ a_2) \\ ... \\ x \equiv b_n\ ({\rm mod}\ a_n)\end{cases}$$

$a_i\le 10^{12}$。$a_i$ 的 $\operatorname{lcm}$ 不超过 $10^{18}$。

## 题目分析

膜拜大佬 [Katyusha_01](https://www.luogu.com.cn/user/533742) 提供的宝贵思路，经同意转述。

我们尊敬的阮老师在题解中提到：

![](https://cdn.luogu.com.cn/upload/image_hosting/688wbqro.png)

题解区现有的 $24$ 篇题解没有一篇对这段话提出质疑。

给它动小手术是没有用的，吗？

既然都叫 EXCRT 了，我们就要由 CRT 扩展出新的做法！

大佬的第一步是，既然模数不互质，那么我们就想办法拆方程，将模数转化为互质的，就可以使用 CRT 了。

我们能想到的唯一方法就是质因数分解了。我们有以下结论：

> 同余方程 $x \equiv b\ ({\rm mod}\ a)$ 等价于方程组 $\begin{cases} x \equiv b\ ({\rm mod}\ p_1^{k_1}) \\ x\equiv b\ ({\rm mod}\ p_2^{k_2}) \\ ... \\ x \equiv b\ ({\rm mod}\ p_m^{k_m})\end{cases}$。其中 $p_i^{k_i}$ 是对 $a$ 质因数分解的结果。

这个结论在 exLucas 中有典型的应用，证明非常简单，无需赘述。

在此题中，有 $a_i$ 的 $\operatorname{lcm}$ 小于等于 $10^{18}$，设其为 $V$，故将所有方程分解后的 $p_i$ 的种类不会超过 $\log V$。所以我们可以遍历 $a$，两步分解质因数：第一步，使用之前分解出的质数来尝试分解，复杂度 $O(\log V)$。第二步，将第一步分解完后剩下的 $a_i$ 暴力分解，这一步单次 $O(\sqrt {a_i})$，但只会执行 $O(\log V)$ 次，在此题复杂度正好足够。

对于分解出来的质数 $p_i$，可能有多个对应的 $k_i$ 的模数，它们并不互质，但没关系，我们还有一个性质。

> 对于质数 $p$，正整数 $k_1<k_2$，若 $x \equiv b\ ({\rm mod}\ p^{k_2})$，则 $x \equiv b\ ({\rm mod}\ p^{k_1})$。

这个性质可以理解为，$x$ 在 $p$ 进制下，$x \equiv b\ ({\rm mod}\ p^{k})$ 相当于限制了 $x$ 的后 $k$ 位需要和 $b$ 相同，所以 $k$ 大时限制更强。

所以对于单个质数 $p_i$，我们只需要保留限制最强的也就是最大的 $k_i$ 对应的方程，如果这个方程和其它方程有矛盾，则说明方程组无解。

这样留下来的就是若干个不同的质数的次幂作为模数，它们互质，这时候就可以放心的使用 CRT 求解了！！

复杂度 $O(\sqrt{V_1}\log V_2+\log^2 V_2)$，其中 $V_1$ 为模数的值域，$V_2$ 为模数的 $\operatorname{lcm}$ 的值域，瓶颈在于质因数分解，如果使用高级的分解质因数算法，这个方法的使用范围可能能广一点。

我们不仅对 CRT 动了小手术，还对它动了两次手术！！！

经本人允许，代码也给出 Katyusha_01 的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
void exgcd(long long a,long long b,long long& x,long long& y)
{
	if(!b) return x = 1,y = 0,void();
	exgcd(b,a % b,y,x),y -= a / b * x;
}
long long ny(long long a,long long mod)
{
	a %= mod;
	long long x,y;
	exgcd(a,mod,x,y);
	return (x % mod + mod) % mod;
}
int n;
long long a[100011],b[100011];
long long p[111],mod[111],rem[111],idx;
void Insert(long long& x,long long y,int i)
{
	long long nmod = 1;
	while(x % p[i] == 0)
		x /= p[i],nmod *= p[i];
	if(nmod > mod[i])
		mod[i] = nmod,rem[i] = y % nmod;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i] >> b[i];
		for(int j = 1;j <= idx;j++)
			Insert(a[i],b[i],j);
		if(a[i] > 1)
		{
			for(long long np = 2;np * np <= a[i];np++) if(a[i] % np == 0)
				p[++idx] = np,Insert(a[i],b[i],idx);
			if(a[i] > 1)
				p[++idx] = a[i],Insert(a[i],b[i],idx);
		}
	}
	long long M = 1;
	for(int i = 1;i <= idx;i++)
		M *= mod[i];
	long long ans = 0;
	for(int i = 1;i <= idx;i++)
		(ans += (__int128)(M / mod[i]) * ny(M / mod[i],mod[i]) % M * rem[i] % M) %= M;
	cout << ans;
	return 0;
}
```

---

## 作者：Tyih (赞：9)

# 扩展中国剩余定理（EXCRT）

​
题目：[​P4777 - 洛谷​](https://www.luogu.com.cn/problem/P4777)

## 简述

如果给定 $n$ 个同余方程组

$$
\begin{cases} x \equiv b_1 \pmod {a_1} \\
x \equiv b_2 \pmod {a_2} \\
x \equiv b_3 \pmod {a_3} \\
\cdots \\
x \equiv b_n \pmod {a_n} \\
\end{cases}
$$

保证 $a$ 是正整数，$b$ 是非负整数

现在要求找一个非负整数 $x$，使得 $x$ 最小且满足这 $n$ 同余方程

**数据保证 $x$ 不超过 $10^{18}$**

## 做法

**可以考虑将同余方程合并**

对于一个合并完后的方程以及一个需要合并的方程：

$$
\begin{cases} x \equiv B \pmod {A} \\
x \equiv b \pmod {a} \\
\end{cases}
$$

可以推出：

$$
x+A\times X=B \ (X\in \mathbb{Z})\\
x+a\times Y=b \ (Y\in \mathbb{Z})
$$

即：

$$
B-A\times X=b-a\times Y
$$

整理得：

$$
A\times X - a\times Y=B-b
$$

我们就可以用 exgcd 求出 $A\times X - a\times Y=\gcd(A,a)$ 其中一个解。再同时乘 $(B-b) \ \div \ \gcd(A,a)$，可以得到一个解 $x_0,y_0$。

我们可以从其得到其通解为：

$$
X=x_0+\frac{a}{\gcd(A,a)}\times k\\
Y=y_0-\frac{A}{\gcd(A,a)}\times k
$$

由前面我们可知 $x=B-A\times X$，将 $X$ 的通解带入，可以得到：

$$
x=B-A\times (x_0+\frac{a}{\gcd(A,a)}\times k)\\
\ =B-A\times x_0 \ -\ \frac{A\times a}{\gcd(A,a)}\times k\\
=B-A\times x_0 \ - \operatorname{lcm}(A,a)\times k
$$

我们可以得到一个同余方程：

$$
x \equiv B-A\times x_0 \pmod {\operatorname{lcm}(A,a)}
$$

对于多个方程只需将其两两合并即可。
以上就是所有思路过程了。

## Code

```
#include<bits/stdc++.h>
#define IOS cin.tie(0),cout.tie(0),ios::sync_with_stdio(0)
#define mod 998244353
#define ll __int128
#define lll long long
#define db double
#define pb push_back
#define MS(x,y) memset(x,y,sizeof x)
using namespace std;
const int N=1e5+5,M=1e5+5;
const ll INF=1ll<<60;
int n;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	else{
		ll aa=exgcd(b,a%b,y,x);
		y-=a/b*x;
		return aa;
	}
}
ll A,B,x,y;
int main(){
	lll a,b;
	IOS;cin>>n;
	A=1;B=0;//因为 x mod 1 一定等于零
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		ll gd=exgcd(A,a,x,y);
		x=(B-b)/gd*x;
		B=B-A*x;
		A=a/gd*A;
		B=(B%A+A)%A;
	}
	lll ans=(B%A+A)%A;
	cout<<ans<<"\n";
	return 0;
}
```

$\LARGE{\mathbb{END}}$

---

## 作者：Fading (赞：7)

### 扩展中国剩余定理 exCRT 

### 问题

求

$$\begin{cases} x \equiv b_1\ ({\rm mod}\ a_1) \\ x\equiv b_2\ ({\rm mod}\ a_2) \\ ... \\ x \equiv b_n\ ({\rm mod}\ a_n)\end{cases}$$

### 算法

考虑合并

$$\left\{\begin{aligned}x\equiv B \pmod A\\x\equiv b_i\pmod {a_i}\\\end{aligned}\right.$$

设

$$x=Am_1+B=a_im_2+b_i$$

$$\therefore Am_1-a_im_2=b_i-B$$

由于 bezout 定理，

$$\gcd(A,a_i)|(b-B)$$

否则无解。

设$G=\gcd(A,a_i)$

$$\therefore A\frac {m_1G}{b_i-B}+a_i\frac {m_2G}{b_i-B}=G$$

设

$$t_1=\frac {m_1G}{b_i-B},t_2=\frac {m_2G}{b_i-B}$$

$$\therefore At_1+a_it_2=G$$

用 exgcd 解出一组特解$t_x,t_y$。

根据不定方程特解公式：

$$t_1=t_x+d\frac {a_i}{G}$$

$$m_1=(t_x+d\frac {a_i}{G})\frac {b_i-B}{G}$$

$$x=A(t_x+d\frac {a_i}{G})\frac {b_i-B}{G}+B
$$

$$x=At_x\frac {b_i-B}{G}+d\cdot A\frac {a_i}{\gcd(a_i,A)}\frac {b_i-B}{G}+B$$

$$x=At_x\frac {b_i-B}{G}+d\cdot \text{lcm}(A,a_i)\frac {b_i-B}{G}+B$$

显然$d=0$解最小，所以原方程最小解

$$x=At_x\frac {b_i-B}{G}+B$$

合并之后的通解就是

$$x\equiv At_x\frac {b_i-B}{G}+B \pmod {\text{lcm}(A,a_i)}$$

这就是扩展中国剩余定理的本质了。

算法？就是方程两两合并。最后的余项就是答案。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
#ifdef Fading
#define gc getchar
#endif
inline ll read(){
    ll x=0,f=1;char ch=gc();
    while(!isdigit(ch)) {if (ch=='-') f=-1;ch=gc();}
    while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
    return x*f;
}
void exgcd(ll a,ll b,ll &x,ll &y){
    if (!b) return (void)(x=1,y=0);
    exgcd(b,a%b,x,y);
    ll tmp=x;x=y;y=tmp-a/b*y;
}
ll gcd(ll a,ll b){
    if (b==0) return a;
    return gcd(b,a%b); 
}
inline ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
}
inline ll mabs(ll x){
    return (x>0?x:-x);
}
inline ll fast_mul(ll a,ll b,ll p){
	ll t=0;a%=p;
	while (b){
		if (b&1LL) t=(t+a)%p;
		b>>=1LL;a=(a+a)%p;
	}
	return t;
}
ll a[1000001],A,B,b[1000001],n;
signed main(){
    n=read();
    //x=b (mod a)
    for (int i=1;i<=n;i++){
        a[i]=read();b[i]=read();
    }
    A=a[1],B=b[1];
    ll x,y;
    for (int i=2;i<=n;i++){
        ll G=gcd(A,a[i]);
        if (mabs(b[i]-B)%G){
            printf("No solution!\n");
            return 0;
        }
        exgcd(A,a[i],x,y);
        x=fast_mul(x%(a[i]/G)+(a[i]/G),((b[i]-B)/G)%(a[i]/G)+a[i]/G,a[i]/G);
        ll mod=lcm(A,a[i]);B=(fast_mul(x,A,mod)+B)%mod;A=mod;
    }
    cout<<(long long)B;
    return 0;
}

```


---

## 作者：_coastline_ (赞：2)

# [P4777 【模板】扩展中国剩余定理（EXCRT）](https://www.luogu.com.cn/problem/P4777)

前言：如果你没有学过中国剩余定理~~应该~~问题不大，~~因为 CRT 和 exCRT 基本上没什么联系 qwq。~~

> Q：求解以下线性同余方程组：
>
> $$\begin{cases}
>  x \equiv r_1 \pmod {m_1} \\
>  x \equiv r_2 \pmod {m_2} \\
>  ... \\
>  x \equiv r_n \pmod {m_n} \\
> \end{cases}$$
>
> 其中模数 $m_1, m_2, ..., m_n$ 为**不一定两两互质**的整数，求 $x$ 的最小非负整数解。

- 我们先来回忆一下：求解线性同余方程组，应该用什么东西呢？没错，就是中国剩余定理：

  $(1)$ 计算所有模数的积 $M = \displaystyle \prod_{i=1}^{n} m_i$；

  $(2)$ 计算 $c_i = \dfrac{M}{m_i}$；

  $(3)$ 计算 $c_i$ 在模 $m_i$ 意义下的乘法逆元 $c_i^{-1}$；

  $(4)$ 计算解 $x = \displaystyle (\sum_{i=1}^{n} r_i c_i c_i^{-1}) \bmod M$。

- 但是，题目中提到，模数不一定两两互质，所以此时**中国剩余定理已失效**，原因：

  已知 CRT 中的构造解 $x = \displaystyle (\sum_{i=1}^{n} r_i c_i c_i^{-1}) \bmod M$。
  
  其中 $c_i = \dfrac{ \prod_{j=1}^{n} m_j }{m_i}$，$c_i c_i^{-1} \equiv 1 \pmod {m_i}$。

  而 $c_i^{-1}$ 的存在条件为 $\gcd(c_i, m_i) = 1$。
  
  若 $c_i, m_i$ 不互质，则 $c_i^{-1}$ 不存在，算法失效。

* 此时，我们需要使用**扩展中国剩余定理**，过程如下：

  将前两个方程：
  
  $$\begin{cases}
      x \equiv r_1 \pmod {m_1} \\
      x \equiv r_2 \pmod {m_2} \\ 
  \end{cases}$$

  转化为：
  
  $$\begin{cases}
      x = m_1p+r_1 \\
      x = m_2q+r_2 \\ 
  \end{cases}$$

  $$\therefore x = m_1p+r_1 = m_2q+r_2$$
  
  $$\therefore m_1p - m_2q = r_2-r_1$$

  由裴蜀定理可得，  
  当 $\gcd(m_1,m_2) \mid r_2-r_1$ 时，有解；  
  当 $\gcd(m_1,m_2) \nmid r_2-r_1$ 时，无解。 

  若有解，由扩欧解得特解为：
  
  $$\begin{cases}
    p = p_0 \times \frac{r_2-r_1}{ \gcd(m_1,m_2) } \\
    q = q_0 \times \frac{r_2-r_1}{ \gcd(m_1,m_2) }
  \end{cases}$$
  
  通解为：
  
  $$\begin{cases}
    P = p + \frac{m_2}{ \gcd(m_1,m_2) } \times k \\
    Q = q - \frac{m_1}{ \gcd(m_1,m_2) } \times k 
  \end{cases}$$

  $$\begin{aligned}
    \therefore x &= m_1 P + r_1 \\
                 &= \frac{m_1m_2}{ \gcd(m_1,m_2) } \times k + m_1 p + r_1
  \end{aligned}$$
  
  $\therefore$ 前两个方程可**等价合并**为 $x' \equiv r \pmod m$，

  其中 $r = m_1 p + r_1$，$m = \frac{m_1 m_2}{ \gcd(m_1,m_2) } = \operatorname{lcm}(m_1,m_2)$。

  综上，可将 $n$ 个方程合并 $n-1$ 次，即可求解。

  时间复杂度：$O(n\log m)$。

#### 核心代码：
```cpp
// P4777 【模板】扩展中国剩余定理（EXCRT）
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	
	LL x1, y1, d;
	d = exgcd(b, a%b, x1, y1);
	x = y1, y = x1 - a/b*y1;
	return d;
}

LL EXCRT(LL m[], LL r[])
{
	LL m1 = m[1], r1 = r[1];
	for(int i = 2; i <= n; i ++)
	{
		LL p, q;
		LL d = exgcd(m1, m[i], p, q);
		if( (r[i] - r1) % d > 0)
			return -1;
		p = p * (r[i] - r1) / d; //特解
    	p = (p % (m[i]/d) + m[i]/d) % (m[i]/d); //求出 p 在模 m[i]/d 意义下的最小正整数
		r1 = m1 * p + r1, m1 = m1 * m[i] / d;
	}
	return (r1 % m1 + m1) % m1;
}
```

这里补充一点关于求 $p$ 的最小正整数的处理。

在前面，我们求得通解 $\displaystyle P = p + \frac{m_2}{ \gcd(m_1, m_2) } \times k$，即 $P \equiv p \pmod {\frac{m_2}{ \gcd(m_1, m_2) } }$。

因此，若 $p$ 要取得最小正整数，必须要跟特解 $P$ 取同等意义下的模数，即 $\displaystyle \frac{m_2}{ \gcd(m_1, m_2) }$。

---

