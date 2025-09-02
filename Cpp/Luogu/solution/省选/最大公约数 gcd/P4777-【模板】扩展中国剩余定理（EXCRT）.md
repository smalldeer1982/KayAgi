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

## 作者：阮行止 (赞：598)

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

## 作者：niiick (赞：302)

[博客原文食用更佳](https://blog.csdn.net/niiick/article/details/80229217)
#### **问题**
求解同余方程组

$$\left\{\begin{aligned}x\equiv\ a_1(\mod m_1) \quad\\ x\equiv\ a_2(\mod m_2) \quad\\ x\equiv\ a_3(\mod m_3) \quad\\  ...\quad\\x\equiv\ a_k(\mod m_k) \quad\end{aligned}\right.$$ 


其中$m_1,m_2,m_3...m_k$为**不一定两两互质**的整数，
求x的最小非负整数解
#### **求解**

假设已经求出前k-1个方程组成的同余方程组的一个解为x

且有$M=\prod_{i-1}^{k-1}m_i$

（补充：代码实现中用的就是$M=LCM_{i-1}^{k-1}m_i$，~~显然易证~~这样是对的，还更能防止溢出，上述是为了先方便理解，评论区就别问那么多次了=_=）

则前k-1个方程的方程组通解为$x+i*M(i\in Z)$

那么对于加入第k个方程后的方程组

我们就是要求一个正整数t，使得
$x+t*M \equiv  a_k(\mod m_k)$

转化一下上述式子得
$t*M \equiv  a_k-x(\mod m_k)$

对于这个式子我们已经可以通过扩展欧几里得求解t

若该同余式无解，则整个方程组无解，
若有，则前k个同余式组成的方程组的一个解解为$x_k=x+t*M$

所以整个算法的思路就是求解**k次扩展欧几里得**

**另外，蒟蒻平常写题喜欢把后面一项看做b，所以输入和题目是反过来的**

**输入和题目是反过来的，输入和题目是反过来的，输入和题目是反过来的**
```cpp
//niiick
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long lt;

lt read()
{
    lt f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=100010;
int n;
lt ai[maxn],bi[maxn];

lt mul(lt a,lt b,lt mod)
{
    lt res=0;
    while(b>0)
    {
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

lt exgcd(lt a,lt b,lt &x,lt &y)
{
    if(b==0){x=1;y=0;return a;}
    lt gcd=exgcd(b,a%b,x,y);
    lt tp=x;
    x=y; y=tp-a/b*y;
    return gcd;
}

lt excrt()
{
    lt x,y,k;
    lt M=bi[1],ans=ai[1];//第一个方程的解特判
    for(int i=2;i<=n;i++)
    {
        lt a=M,b=bi[i],c=(ai[i]-ans%b+b)%b;//ax≡c(mod b)
        lt gcd=exgcd(a,b,x,y),bg=b/gcd;
        if(c%gcd!=0) return -1; //判断是否无解，然而这题其实不用
        
        x=mul(x,c/gcd,bg);
        ans+=x*M;//更新前k个方程组的答案
        M*=bg;//M为前k个m的lcm
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}

int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    bi[i]=read(),ai[i]=read();
    printf("%lld",excrt());
    return 0;
}
```

### update

OI退役以后就不怎么上洛谷了，评论区似乎对代码部分疑问有点多，所以就更新一下细节，~~当年喜欢压行确实是个很不好的习惯~~ 

针对一些对代码的疑问做点解答

> Q：c=(ai[i]-ans%b+b)%b是什么意思

我们推导出$t*M \equiv  a_k-x(\mod m_k)$

其中$a_k-x$对应$ax≡c(\mod b)$中的c，这句代码里$ans$对应$x$，$b$对应$m_k$

所以这句话就是把$a_k-x$先对$m_k$取模

> Q：为啥不加个括号变成c=((ai[i]-ans)%b+b)%b

ans%b的范围是[0,b-1)，a[i]-ans%b+b一定不会小于0的，当然加了也没问题

> Q：为什么$M*=bg$而不是$M*=b$

这里bg=b/gcd(a,b)对应到推到部分公式里的就是$bg=m_k/gcd(m_k,LCM_{i=1}^{k-1}m_i)$

$M*=bg$明显就是令M为前k个m的最小公倍数

> Q：这句话x=mul(x,c/gcd,bg)为什么要乘c/gcd，为什么模数是bg

建议复习[扩展欧几里得](https://blog.csdn.net/niiick/article/details/80119121)

---

## 作者：nekko (赞：148)

~~实际上是同余方程组的合并~~

# 简述

如果给定$n$个同余方程组

$$ \begin{cases} x &\equiv b_1 \pmod {a_1} \\ x &\equiv b_2 \pmod {a_2} \\ x &\equiv b_3 \pmod {a_3} \\ &\cdots \\ x &\equiv b_n \pmod {a_n} \\ \end{cases} $$

保证$a$是正整数，$b$是非负整数

现在要求找一个非负整数$x$，使得$x$最小且满足这$n$同余方程

**数据保证$x$不超过$10^{18}$**

# 题解

现在考虑合并两个同余方程的时候该怎么做

$$ \begin{cases} x \equiv b \pmod {a} \\ x \equiv B \pmod {A} \end{cases} $$

这个可以写作

$$ \begin{cases} x = ay + b \\ x = AY + B \end{cases} $$

由于$x$是一个常量，因此$ay+b=AY+B$，其中$a,b,A,B$都是常数

整理一下后就是$ay+A(-Y)=B-b$

通过$exgcd$，可以获得一组关于$ay+A(-Y)=\gcd(a,A)$的解$(y_0,-Y_0)$

即$a(y_0 \times \frac{B-b}{\gcd(a,A)})+A(-Y_0 \times \frac{B-b}{\gcd(a,A)})=\gcd(a,A) \times \frac{B-b}{\gcd(a,A)}=B-b$

由于$x=ay+b$，现在要最小化$x$，也就是最小化$y$，即最小化$t=y_0 \times \frac{B-b}{\gcd(a,A)}$

由于$t$的通解为$t+\frac{A}{\gcd(a,A)}k$，因此$t$的最小值为$t_0=t \bmod \frac{A}{\gcd(a,A)}$

于是就可以将这两个同余方程合并为

$$ x \equiv a \times t_0+b \pmod {\mathbb{lcm}(a,A)} $$

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
const int N = 1e5 + 10;
ll x, y, d; int n;

void exgcd(ll &x, ll &y, ll a, ll b) {
    if(!b) d = a, x = 1, y = 0;
    else exgcd(y, x, b, a % b), y -= a / b * x;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll a, b, A, B;

void merge() {
    exgcd(x, y, a, A);
    ll c = B - b;
    if(c % d) puts("-1"), exit(0);
    x = x * c / d % (A / d);
    if(x < 0) x += A / d;
    ll mod = lcm(a, A);
    b = (a * x + b) % mod; if(b < 0) b += mod;
    a = mod;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        long long _A, _B;
        scanf("%lld%lld", &_A, &_B), A = _A, B = _B;
        if(i > 1) merge();
        else a = A, b = B;
    }
    printf("%lld\n", (long long)(b % a));
}
```



---

## 作者：未来姚班zyl (赞：147)

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

## 作者：hwk0518 (赞：105)

我一开始写代码，就发现这道题好像很奇怪，几个mod如果都是质数一乘早就不能用long long存了，难道要写高精度吗？所以我就想从几位写题解的大佬的代码里得到一些启发。

不看不知道，一看吓一跳。我随便造了一组n=5的数据如下：

```
5
998244353 469904850
998244389 856550978
998244391 656199240
998244407 51629743
998244431 642142204
```

这组数据的答案是99999999999000019.

但是niiick,YCS1,PurpleWonder等几位大佬一人一个（错误）答案，Qihoo360大佬更是直接TLE了。所以没办法，只好自力更生。

我们想，如果没有题目中的一句“保证答案不超过1e18”，这道题或许真的就要写高精度。但是有这样一句话，或许我们能从中得到一些有用的信息。接下来说说我的算法。

我们知道，任意一个合数都能拆分为若干个**两两互素**的数的乘积。我们不妨设b由q个两两互素的数p1,p2,p3,...,pq构成。则x=a(mod b)这样一个条件实则就会拆分为x=a%p1(mod p1),x=a%p2(mod p2),...,x=a%pq(mod pq)这q个条件。

（事实上，由中国剩余定理，我们知道，由x=a%p1(mod p1),x=a%p2(mod p2),...,x=a%pq(mod pq)这q个条件确定的x在[0,b)中有且只有一个。所以不用担心两组条件不等价）

再来。我们知道2~37的所有素数相乘已经大于1e12了。所以一个条件至多只会被拆分成12个条件。所以条件总数不会大于120万。而且由唯一分解定理，条件都是形如x=a(mod p^q)的形式，其中p为素数。如果有两个条件x=a(mod p^q)和x=b(mod p^k)，其中q<k，那么显然满足条件2的x构成的集合真包含于满足条件1的x构成的集合，所以只要保留条件2.

现在我们已经得到至多120万个模数两两互素的条件了。不妨设有n个条件，第i个条件的模数是ai，且我们已经满足了前k个条件，考虑条件k+1.如果a1到ak的数的乘积已经大于1e18，由于满足条件的x在0~a1乘到ak中有且仅有一个，所以再加一个条件，满足条件的最小x只会变大，不会变小。而且一旦变大，就会至少变大a1乘到ak.这就和“保证答案不超过1e18”矛盾了。这时我们直接break，输出的一定是正确答案，而且不用担心目前的模数相乘不能用long long存。

我们知道，求CRT的过程至多运算O(120万)*O（log120万）次，是不会超时的。但是在拆分条件的过程中如果写暴力，一旦出现的素数很大，而且很多，就会超时。所以我们不得不加一些优化。

我加的优化是map优化，一旦在分解的过程中判定某个数是素数，就用map存起来。下一次再碰到这个数就不用再算了，这种算法在随机数据下表现良好，但是如果给的条件都是素数且两两不重复一样会超时。所以更完美的算法应当是Pollard Rho+Miller Rabin。

代码：

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
#include<time.h>
#include<map> 
using namespace std;

map<long long,bool> M;
const long long mod=1234577;
int n,tl,ftl;
long long a[100005],b[100005],fac[20];
struct node
{
	long long A,B,C;//mod A^B=C 
};
node t[1500005];
bool cmp(node x,node y)
{
	return x.A<y.A;
}

long long Mul(long long n,long long k)
{
	int i,x=0,y=0;
	for(i=1;i<19;++i) if(fac[i]>n)
	{
		x=i;break;
	}
	if(!x) x=19;
	for(i=1;i<19;++i) if(fac[i]>k)
	{
		y=i;break;
	}
	if(!y) y=19;
	return (x+y<=20);
}

long long mul(long long n,long long k,long long mod)
{
	long long ans=0;
	while(k)
	{
		if(k&1) ans=(ans+n)%mod;
		n=(n+n)%mod;
		k>>=1;
	}
	return ans;
}

long long F_p(long long x,long long y,long long z)
{
	long long bas=x%z,ret=1;
	while(y)
	{
		if(y&1) ret*=bas,ret%=z;
		bas*=bas,bas%=z;
		y>>=1;
	}
	return ret;
}

void insert(long long A,long long B,long long C)
{
	t[++tl].A=A,t[tl].B=B,t[tl].C=C;
}

void add(long long a,long long c)
{
	long long i,tmp,sq=sqrt(a);
	int cnt;
	for(i=2;i<=sq;++i)
	{
		cnt=0,tmp=1;
		while(a%i==0) ++cnt,a/=i,tmp*=i;
		if(cnt) insert(i,cnt,c%tmp);
		if(M[a]) break;
	}
	if(a>1) M[a]=1,insert(a,1,c%a);
}

void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	long long tmp=x;
	x=y;
	y=tmp-a/b*y; 
}

long long CRT()
{
	long long x,y,k;
	long long M=a[1],ans=b[1];
	int i;
	for(i=2;i<=ftl;++i)
	{
		long long A=M,B=a[i],C=(b[i]-ans%B+B)%B;
		exgcd(A,B,x,y);
		x=mul(x,C,B);
		ans+=x*M;
		if(!Mul(M,B)) return ans;
		else M*=B,ans=(ans%M+M)%M;
	}
	return ans;
}

int main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	int i,l,r;
	fac[0]=1;
	for(i=1;i<19;++i) fac[i]=fac[i-1]*10;
	long long maxx,mm;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		scanf("%lld%lld",&a[i],&b[i]);
		if(a[i]==1) continue;
		add(a[i],b[i]); 
	}
	
//	cout<<clock()<<endl; 
	sort(t+1,t+tl+1,cmp);
	
	l=r=1;
	while(l<=tl)
	{
		maxx=t[l].B,mm=t[l].C;
		while(t[r+1].A==t[l].A)
		{
			++r;
			if(t[r].B>maxx)
			{
				maxx=max(maxx,t[r].B);
				mm=t[r].C;
			}
		}
		a[++ftl]=pow(t[l].A,maxx),b[ftl]=mm;
		l=r+1,r=l;
	}
	
	printf("%lld\n",CRT());
	
	return 0;
}
```

---

## 作者：sumijie (赞：80)

## 对于一组同余方程

$\begin{cases} x \equiv a_1\ ({\rm mod}\ n_1) \\ x\equiv a_2\ ({\rm mod}\ n_2) \\ ... \\ x \equiv a_n\ ({\rm mod}\ n_n)\end{cases} $

**对于第一个和第二个式子**

**则有：**

$x = a_1 + k_1*n_1$

$x = a_2 + k_2*n_2$

**就有：**

$a_1 + k_1*n_1 = a_2 + k_2*n_2$

$k_1*n_1 - k_2*n_2 = a_2 - a_1$

**故我们设 $d = a_2 - a_1$**
**再变化一下形式就有：**

$k_1*n_1 + (-k_2)*n_2 = d$

**令 $g = gcd(n_1,n_2)$**

**这样我们就可以通过exgcd来求出一组解 $x_1,y_1$**

**满足 $x_1*n_1 + y_2*n_2 = g$**

**故：**
$x_1*d/g *n_1 + y_2*d/g*n_2 = g*d/g$

**则：**
$k_1 = x_1*d/g,k_2 = y_1*d/g$

**从而得到一组通解**

$k_1 = k_1 + n2/g*T$

$k_2 = k_2 - n1/g*T$



**要使所求得的解最小且为正整数则可以根据 $k_1$ 的通解形式求得**

$ k_1 = (k_1\%(n_2/g) + n_2/g)\%(n_2/g) $

**再带入 $x = a_1 + k_1*n_1$ 得到 $x$ **

**令 $A$ 为合并后的 $a$ , $N$ 为合并后的 $n$**

**所以$N =  lcm(n_1,n_2) = n_1 * n_2 / g$**

**根据$x \equiv A\ ({\rm mod}\ N)$ 且 $x$ 是满足该式子最小的值**

**得到：**
$A = x$

# 欢迎来卡


```cpp
#include<iostream>

typedef __int128 ll;

using namespace std;

void exgcd(ll a,ll b,ll &g,ll &x,ll &y) {
    if (b == 0) {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b,a%b,g,y,x);
    y-=(a/b)*x;
}

bool flag = false;

ll a1,a2,n1,n2;

ll abs(ll x) {
	return x>0?x:-x;
} 

void china() {
    ll d = a2 - a1;
    ll g,x,y;
    exgcd(n1,n2,g,x,y);
    if (d % g == 0) {
        x = ((x*d/g)%(n2/g)+(n2/g))%(n2/g);
        a1 = x*n1 + a1;
        n1 = (n1*n2)/g;
    }
    else 
        flag = true;
}

int n;

long long as[100001];

long long ns[100001];

ll realchina() {
    a1 = as[0];
    n1 = ns[0];
    for (ll i = 1;i<n;i++) {
        a2 = as[i];
        n2 = ns[i];
        china();
        if (flag)
            return -1;
    }
    return a1;
}

int main() { 
    cin>>n;
    flag = false;
    for (ll i = 0;i<n;i++)
        cin>>ns[i]>>as[i];
    cout<<(long long)realchina()<<endl; 
}
```

---

## 作者：Huami360 (赞：58)

## 注意一下：：

题目是
$$x≡b_i\pmod {a_i}$$

我总是习惯性的把a和b交换位置，调了好久没调出来，$qwq$。

# 本题解是按照
### $$x≡a_i\pmod {b_i}$$
# 讲述的，请注意

本题$m_i$不一定两两互质，所以中国剩余定理在本题不再适用。

~~说是扩展中国剩余定理，其实好像和中国剩余定理关系不大。~~


使用数学归纳法，如果我们已经知道了前$k-1$个方程组构成的一个解，记作$x$，记$m=\Pi_{i=1}^{k-1}b_i$，则$x+i*m(i∈Z)$是前$k-1$个方程的通解，如果这个不懂，就得去好好学学同余了。考虑对于第$k$个方程，求出一个$t$，使得
$$x+t*m≡a_i \pmod {b_i}$$
然后
$$x'=x+t*m$$
综上，循环$n$次即可。

讲一下如何用扩展欧几里德解线性同余方程。

大家都知道~~(假设大家都知道)~~，$exgcd$可以求出方程
$$ax+by=gcd(a,b)$$
的一组整数解。
我们要解的线性同余方程是这样的:
$$ax≡b\pmod m$$
可以写成这个形式：
$$ax+my=b$$
若方程有解，则
$$gcd(a,m)|b$$
一定成立。题目保证有解，无需特判。

于是我们用扩欧求出
$$ax+my=gcd(a,m)$$
的一组解，然后等式两边同时除以$gcd$再乘以$b$，得
$$a(x/gcd(a,m)*b)+m(y/gcd(a,m)*b)=b$$
得解。

还有个细节，就是乘的时候会爆long long，而__int128这个东西比赛时是不可用的，所以还是老老实实打快$(gui)$速乘吧。
其实和快速幂差不多的。
```cpp
ll Slow_Mul(ll n, ll k, ll mod){
    ll ans = 0;
    while(k){
      if(k & 1) ans = (ans + n) % mod;
      k >>= 1;
      n = (n + n) % mod;
    }
    return ans;
}
```
完整$AC$代码：
```cpp
#include <cstdio>
const int MAXN = 100010;
typedef long long ll;
int n;
ll a[MAXN], b[MAXN], ans, M, x, y;
ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){ x = 1; y = 0; return a; }
    ll d = exgcd(b, a % b, x, y);
    ll z = x; x = y; y = z - (a / b) * y;
    return d;
}
ll Slow_Mul(ll n, ll k, ll mod){
    ll ans = 0;
    while(k){
      if(k & 1) ans = (ans + n) % mod;
      k >>= 1;
      n = (n + n) % mod;
    }
    return ans;
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
       scanf("%lld%lld", &b[i], &a[i]);
    ans = a[1];
    M = b[1];
    for(int i = 2; i <= n; ++i){
       ll B = ((a[i] - ans) % b[i] + b[i]) % b[i];
       ll GCD = exgcd(M, b[i], x, y);
       x = Slow_Mul(x, B / GCD, b[i]);
       ans += M * x;
       M *= b[i] / GCD;
       ans = (ans + M) % M;
    }
    printf("%lld\n", ans);
    return 0;
}

```

---

## 作者：ecnerwaIa (赞：19)

[my blog](https://www.luogu.org/blog/wjr5082/)

[题目链接在此](https://www.luogu.org/problemnew/show/P4777)

对于中国剩余定理，相信大家都不陌生，但是如果 模数不是 两两互质又该如何解决呢？

首先，我们可以考虑下，如果已知了前 i-1 个方程，即

$\begin{cases}x\equiv b1\ mod(a1)\\{\vdots}\\x\equiv b_{i-2}\ mod(a_{i-2})\\x\equiv b_{i-1}\ mod(a_{i-1})\end{cases}$

然后我们求出了它的解 ans , 现在加入第 i 个方程 $x\equiv b_{i}\ mod(a_{i})$ 

#### 现在我们考虑绝前 i-1 个方程的解 和第i个方程 如何推出 前i个方程的解 

**我们假设 $M$ 为前 i-1个方程的最小公倍数**，那么前 i-1个方程通解 就是
**ans+M\*k**(k为任意整数)

别告诉我你不知道什么叫通解...通解就是所有满足的解的一个集合.比如 求 $x\equiv3\ mod(4)$通解是$3+4*k$, ...,-1,3,7...都是满足的，但是我们只求最小非负整数解，但是我们要知道这一类解都是满足的

回到正题，对任意k, $ans+M*k$都满足前$i-1$个方程的条件,那么我们不就是只要找到一个k使得他也能满足第$i$个方程不就好了吗？

当然找的 k肯定也不只有一个啦，只用找到一个即可,之后取模操作,会变成最小的. 

那就变成了求 $ans+k*M\equiv bi\ mod(ai)$ --->
$k*M\equiv b[i]-ans\ mod(a[i])$

那是不是可以看成我们要求 $k*M+a[i]*t =b[i]-ans$(k,t都是未知的)
那我们就可以先求 $k*M+a[i]*t=1$,然后两边同时乘 $b[i]-ans$，不就是求出了$k$吗？（那你怕不是个妖怪吧，连exgcd求的是什么都忘了！！$a[i],M$不一定互质哎）

设 $r=gcd(M,a[i])$,那我们求乘法逆元，求的是 $k*M+a[i]*t=r$,两边同时除以$r$,得 $k*(\frac{M}{r})+t*(\frac{a[i]}{r})=1$的解 $k_{1}$,那么回到式子 $k*M+a[i]*t=b[i]-ans$,不就是将我们上面的到的 两边乘 $r*(b[i]-ans)$吗，其中一个解不就是 $k_{1}*(\frac{b[i]-ans}{r})$吗 ?

但是我们要求的是最小的非负整数解啊，所以考虑要**对谁取模**？

抛开上面的，考虑这个式子 $a*x+b*y=1$(a,b互质并且已知),我们要找到最小的一个$x1,y1$ 使得$a*(x+x1)+b*(y+y1)=1$同样成立，那么不就有$a*x1+b*y1=0$吗, **此时a,b互质,那么x1最小为b,相应的y1=a**，因为x1=$-\frac{b*y1}{a}$, $a,b$互质，没有相同因子，又要让$x1$为整数，所以$a|y1$,所以$b|x1$,即$x1$最小为$b$

这时就可以得出上面的式子的通解间隔了，因为$\frac{M}{r}$与$\frac{a[i]}{r}$互质,所以k的通解间隔就是 $\frac{a[i]}{r}$了

#### 注：代码中注释a[i],b[i]和我题解是一个意思，代码中的我读入a[i]是b[i]，b[i]是a[i]，所以。。。。凑合着看吧，我懒得改了
```c
// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;
ll M,x,y,n;
ll ans,a[110000],b[110000];
inline ll exgcd(ll p,ll q,ll &x,ll &y){
    if(!q){
        x=1;
        y=0;
        return p;
    }
    ll g=exgcd(q,p%q,y,x);
    y-=(p/q)*x;
    return g;
}
inline ll mul(ll a,ll b,ll c){
	ll res=0;
	while(b>0){
		if(b&1){
			res=((res+a))%c;
		}
		a=(a+a)%c;
		b>>=1;
	}
	return (res%c+c)%c;
}
ll excrt(){
    M=b[1];
    ans=a[1];
    for(ll i=2;i<=n;++i){
        ll c=((a[i]-ans)%b[i]+b[i])%b[i];
        ll g=exgcd(M,b[i],x,y);
        ll p=b[i]/g;
        x=mul(x,c/g,p);
        ans+=x*M;
        M*=p;
        ans=(ans%M+M)%M;
    }
    return ans;
}
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;++i){
        scanf("%lld%lld",&b[i],&a[i]);
    }
    printf("%lld\n",excrt());
    return 0;
}

```

---

## 作者：灵乌路空 (赞：14)

无良宣传一下博客wwwwww  
[文章列表 - 核融合炉心 - 洛谷博客](https://www.luogu.org/blog/koishikoishi/)


------------

## 求解同余方程组 (扩展中国剩余定理)   
   
   [P4777 【模板】扩展中国剩余定理（EXCRT）](https://www.luogu.org/problemnew/show/P4777)
   
   - ##### 要解如下的同余方程组 ：
   
     $\begin{cases}x \equiv a_1\pmod {b_1}\\x \equiv a_2\pmod {b_2}\\......\\x \equiv a_n\pmod {b_n}\\\end{cases}$
   
     其中 , $a_i,b_i$为非负整数 ， $b_1,b_2,...,b_n$ 不一定互质
   
   - ###### 求解:
     
     假设已经求出了前 $k-1$ 个方程的解 $x_{k-1}$  
     设 $M=LCM_{i=1}^{k-1} bi$ , 即 $M$ 为前 $k-1$ 个模数 $b$ 的最小公倍数
     
     **则 :**    
     对于前 $k-1$个方程, 都满足$x_{k-1}+tM\equiv a_i\pmod {b_i}\ \ (t\in Z)$  
     即 : 前 $k-1$ 个方程 , 通解为 $x_{k-1}+tM\ \ (t\in Z)$
     
     欲求得第 $k$ 个方程的解 , 并且将求得的解 , 也满足前 $k-1$ 个方程 
    
     **则 :**   
     需要使第 $k$ 个方程的解 , 为前 $k-1$ 的方程的通解的同时 ， 也满足第 $k$ 个方程的条件 。
    
     设 : 第$k$ 个方程的解 $x_k = x_{k-1}+tM\ \ (t\in Z)$
     
     将此解代入第 $k$ 个方程中 , 可得 :   
     $x_{k-1}+tM\equiv a_k\pmod{b_k}$   
     即 :  $tM\equiv a_k-x_{k-1}\pmod{b_k}$  
     其中 : $M,a_k,x_{k-1},b_k$ 都是已知的 。
     
     使用 $exgcd$ 解出此同余方程 , 可以得到 $t$ 的值 。
     
     将 $t$ 的值代回 $x_k = x_{k-1}+tM\ \ (t\in Z)$ ，就可得到$x_k$的值
     
     进行 $k$ 次上述操作后 ，便可得到 方程组的解 。
     
   - ###### 本题坑点：
  
     ##### 数据范围：  
       如果只是开 $long\ long$ 的话，取余时无论如何都会炸掉     
       
       为了避免 变量爆破 ，要用一种叫做 **快速乘取余** 的奇$(ba)$妙$(ka)$ 算法。  
        
       - 快速乘取余 ~~(又称龟速乘)~~
         
         其本质与快速幂取余类似，都是二进制的拆分应用 。  
         
         假设有 $k$ 个 $a$ 相乘  
         快速乘 将其分解成了 $a\times 2a \times 4a\times ....$ 的形式。  
         这样就可以边乘边取余，来防止变量爆破 , 数据溢出。
         
         但是却将乘法的时间复杂度，  
         硬生生的拉到了 $O(logn)$ 级别
         
         ```cpp
		 ll mul(ll A,ll B,ll mod) //快速乘取余 模板
		 {
    	 	ll ans=0;
    	    while(B>0)
      		  {
        	  	if(B & 1) ans=(ans+A%mod)%mod;
        		A=(A+A)%mod;
        		B>>=1;
      		  }
    		return ans;
		  }
		  ```
     
------------
##### 上代码:

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll n;
ll a[100010],b[100010]; 
ll mul(ll A,ll B,ll mod) //快速乘取余 模板
{
	ll ans=0;
	while(B>0)
	  {
	  	if(B & 1) ans=(ans+A%mod)%mod;
	  	A=(A+A)%mod;
	  	B>>=1;
	  }
	return ans;
}
ll exgcd(ll A,ll B,ll &x,ll &y) //扩展欧几里得 模板
{
	if(!B)
	  {
	  	x=1,y=0;
	  	return A;
	  }
	ll d=exgcd(B,A%B,x,y);
	ll tmp=x;
    x=y , y=tmp-A/B*y;
    return d;
}
ll lcm(ll A,ll B) //求最小公倍数
{
	ll xxx,yyy;
	ll g=exgcd(A,B,xxx,yyy);
	return (A/g*B);
}
ll excrt() //重点:求解同余方程组
{
	ll x,y;
	ll M=b[1],ans=a[1]; //赋初值 
    //M为前k-1个数的最小公倍数，ans为前k-1个方程的通解
	for(int i=2;i<=n;i++)
	  {
	  	ll A=M,B=b[i];
		ll C=(a[i]-ans%B+B)%B; //代表同余方程 ax≡c(mod b) 中a,b,c
            
	  	ll g=exgcd(A,B,x,y);
        //求得A,B的最大公约数，与同余方程ax≡gcd(a,b)(mod b)的解，
            
	  	if(C%g) return -1; //无解的情况
            
	  	x=mul(x,C/g,B); //求得x的值,x即t 
	  	ans+=x*M;  //获得前k个方程的通解
	  	M=lcm(M,B); //更改M的值
	  	ans=(ans%M+M)%M;
	  }
	return ans;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	  scanf("%lld%lld",&b[i],&a[i]);
	ll ans=excrt();
	printf("%lld",ans);
}
```

---

## 作者：szr666 (赞：11)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problemnew/show/P4777)
------------


------------

华丽的分割线
# 解析

本题解由欧几里得求gcd和同余的性质去推导exgcd,crt,excrt

### 同余方程及性质

形如$ax\equiv b \ (mod \ p)$的式子称为同余方程,有如下性质

若$a\equiv b \ (mod \ p)\ \ c\equiv d \ (mod \ p)\ $则$\ ac\equiv bd \ (mod \ p)$

对于一个同余方程$\ ax\equiv b \ (mod \ p)\ $可化为$\ ax=b+k*p$

则$\ ax-kp=b\ $,其中$k$,$x$为未知数,这就是二元一次不定方程

### 扩展欧几里得

对于$\ ax+by=c\ $,$a\ $ $b\ $ $c\ $已知,当且仅当$gcd(a,b)\mid c$,方程有整数解

只要解决$\ ax+by=gcd(a,b)\ $,则$x$,$y$分别乘$\frac{c}{gcd(a,b)}$即可

因为$\ gcd(a,b)=gcd(b,a\ mod\ b)\ $,所以我们要找出

$\ bx_0+(a\ mod\ b)y_0=gcd(b,a\ mod\ b)\ $与原方程解的关系,则辗转相除即可

因为$(a\ mod\ b)=(a-\lfloor\frac{a}{b}\rfloor*b)$,所以把这带进去,系数分一下类,可得

$\ ay_0+b*(x_0-\lfloor\frac{a}{b}\rfloor*b*y_0)=gcd(b,a\ mod\ b)\ $

可得到$\begin{cases}x=y_0\\y= x_0-\lfloor\frac{a}{b}\rfloor*b*y_0\end{cases}$ 当$b=0$时,$x=1,y=0,gcd(a,b)=a$

递归即可求出不定方程的一组整数解,也就求出了同余方程的一个解

### 方程的通解

已知$x_0\ y_0$一组特解,如何求出方程所有解

设$x_0+c\quad y_0-d$也是一组解,求出最小的$c$和$d$,每次$x_0+kc\ y_0-kd$即可得到通解

则有$ax_0+ac+by_0-bd=ax_0+by_0$,则$ac=bd=lcm(a,b)$

因为$ac=bd$,二者均为$a,b$的倍数,且要求$c,d$最小,则为最小公倍数

则$ac=bd=\frac{ab}{gcd(a,b)}$,解得$c=\frac{b}{gcd(a,b)}\ d=\frac{a}{gcd(a,b)}$

所以方程通解为$\begin{cases}x=x_0+k*\frac{b}{gcd(a,b)}\\y=y_0-k*\frac{a}{gcd(a,b)}\end{cases}\quad$ 其中$k$为任意整数

我再提一下对于$x\ mod\ p$,把结果控制在0~p-1范围中需要

$x=((x\ mod\ p)+p)\ mod\ p$;因为$x\ mod\ p$在-(p-1)~p-1范围中

### 中国剩余定理

对于同余方程组$\begin{cases}x\equiv a_1(mod\ m_1)\\\qquad\vdots \\ x\equiv a_k(mod\ m_k)\end{cases}\ \ $当$m_1\dots m_k$两两互质时

可以用中国剩余定理解决,我们先构造一些东西

设$M=\prod_{i=1}^{k}m_i,\frac{M}{m_i}t_i\equiv1(mod\ m_i),t_i$为最小正整数解

$t_i$可用exgcd求出,则根据同余性质,$a_i*\frac{M}{m_i}t_i\equiv a_i(mod\ m_i)$

则对于同余方程组的解$x=\sum_{i=1}^{k}a_i*\frac{M}{m_i}t_i\qquad$WHY?

因为对于任意模数$m_i$,和中除第$i$项,模$m_i$均为0,因为$M$中含有$m_i$这个因子

但在第$i$项时$M/=m_i$,且模数两两互素,所以$M$中不含因子$m_i$,且余数为$a_i$

则方程最小正整数解为$((x\ mod\ M)+M)\ mod\ M\ $复杂度为$O(nlogn)$

### 扩展中国剩余定理

当$m_1\dots m_k$两两不互质时,便是我们的题目

设我们把前$k-1$个方程合并为一个方程,则

$\begin{cases}x\equiv A(mod\ M)\\ x\equiv a_k(mod\ m_k)\end{cases}\ \ =\ \ \begin{cases}x=A+t_1*M\\ x=a_k+t_2*m_k\end{cases}\ \ $

两式相减得$0=A-a_k+t_1*M-t_2*m_k$

$t_1*M-t_2*m_k=a_k-A\ \ $因为只有$t_1,t_2$未知,可用扩展欧几里得解出

设$e=a_k-A,d=gcd(M,m_k)$,则$x_0*\frac{e}{d}*M-y_0*\frac{e}{d}*m_k=d*\frac{e}{d}$

则$t_1=x_0*\frac{e}{d}$,则$x=A+t_1*M$

所以合并之后模数为$lcm(M,m_k)$,答案为$A+t_1*M$

2个变一个,3个变一个,以此类推,将$k$个方程合为一个方程

### 模数处理

对于上述$t_1$，不一定是最小正整数解,通解为$t_1=x_0*\frac{e}{d}+k*\frac{m_k}{d}$

则$t_1=((t_1\ mod\ \frac{m_k}{d})+\frac{m_k}{d})\ mod\ \frac{m_k}{d}$

对于新的答案,应用新模数$lcm(M,m_k)$去对$A+t_1*M$进行和$t_1$类似的操作

在乘法运算中会爆$longlong$,应使用快速乘~~龟速乘~~

# 代码

```cpp
#include<cstdio>
#define ll long long
using namespace std;
void read(int &x)
{
	x=0;
	int f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
void read(ll &x)
{
	x=0;
	ll f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
ll mul(ll a,ll b,ll p)
{
	ll ans=0,x=a;
	while(b!=0)
	{
		if(b&1)
		{
			ans=(ans+x)%p;
		}
		x=(x+x)%p;
		b>>=1;
	}
	return (ans%p+p)%p;
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	else
	{
		ll d;
		d=exgcd(b,a%b,y,x);
		y-=(a/b)*x;
		return d;	
	}
}
ll a[110000],m[110000];
int main()
{
	int n,i;
	read(n);
	for(i=1;i<=n;i++)
	{
		read(m[i]);
		read(a[i]);
	}
	ll M=m[1],ans=a[1];
	for(i=2;i<=n;i++)
	{
		ll e,x,d,y,nowm,newm;
		e=a[i]-ans;
		d=exgcd(M,m[i],x,y);
		nowm=m[i]/d;
		x=(x%nowm+nowm)%nowm;
		x=(mul(x,((e/d)%nowm+nowm)%nowm,nowm)+nowm)%nowm;
		newm=M*nowm;
		ans=(ans+mul(x,M,newm)+newm)%newm;
		M=newm;
	}
	printf("%lld",ans);
}
```



---

## 作者：瑜瑾瓒珏 (赞：9)

## 线性同余方程：

先给一个定理，这个定理告诉我们一元线性方程何时有解，在有解时有多少个膜 $m$ 不同于的解。


------------

------------

### 定理 1：

设 $a,b$ 和 $m$ 是整数，$m>0\ $, $\ gcd(a,m)=d$ .若 $d \nmid b$ , 则   $ ax\equiv b\pmod{m}$ 无解。反之， 则 $ ax\equiv b\pmod{m}$ 恰有 $d$ 个膜 $m$ 不同余的解。

------------


------------



### 证明：

要证明这个定理我们再给一个**定理 2**：（放心，绝对不会无限递归）

若 $a,b$ 和 $m$ 是整数， $ ax\equiv b\pmod{m}$ 当且仅当存在整数 $k$,使得 $a=b+km$

**证明**一下这个**定理 2**：

若 $ ax\equiv b\pmod{m}$ ，则 $m|(a-b)$ .这说明存在整数 $k$ ，使得 $km=a-b$ .所以 $a=b+km$ .

反过来，若存在整数 $k$ 使得 $a=b+km$ ，则 $km=a-b$ .于是, $ m|(a-b)$ , 因而  $ ax\equiv b\pmod{m}$.

上面这个**定理 2**还是简单的，可以帮助我们将同余式转换为等式.

------------


还有一个定理

**定理 3：**

设 $a,b$ 是整数且 $d=gcd(a,b)$. 如果 $d \nmid c$ ,那么方程 $ ax+by=c$ 没有整数解。反之，则存在无穷多个整数解。另外，如果 $x=x_0,y=y_0$ 是方程的一组特解，那么所有的解可以表示为：

$$x=x_0+(b/d)n \ \ ,\ \ y=y_0-(a/d)n$$

红红火火恍恍惚惚，这个大家自己脑子里随便想想都能证明。

------------



**定理1**的正规证明还是很长的，这里我们简单说说。

由**定理 2**我们可以将 $ ax\equiv b\pmod{m}$ 转换为 二元线性的方程（这是线性丢番图方程）：
 $ax-my=b$ 
 
整数 $x$ 是 $ ax\equiv b\pmod{m}$ 的解当且仅当存在 $y$ 使得 $ax-my=b$ .


由**定理 3**可知，若 $d \nmid b$,则这个丢番图方程无解 . 反之， $ax-my=b$ 有无穷多解 :

$$x=x_0+(m/d)t \ \ ,\ \ y=y_0+(a/d)t$$

但是我们要找的是不同余的解，所以我们要找一个条件，使得 $x_1,x_2$ 膜 $m$ 同余。

找到同余的条件是这样的：

$$x_0+(m/d)t_1 \equiv x_0+(m/d)t_2 \pmod{m}$$

化简：

$$(m/d)t_1 \equiv (m/d)t_2 \pmod{m}$$

因为 $gcd(m/d)|m$ ,所以 $gcd(m,m/d)=m/d\ $ , 可得：

$$t_1 \equiv t_2 \pmod{m}$$

这表明不同余的解的一个完全集合可以通过取 $ x=x_0+(m/d)t_1$ 得到，然后 $t$ 取遍膜 $d$ 的完全剩余系，这样，一个确定的集合就可以给出啦~~其中 $t=0,1,2,3,4..., d-1$。

证毕。



------------


------------

上面讨论了一般形式的同余方程，现在由一个特殊一点的形式来定义**模的逆**。

$ ax\equiv 1\pmod{m}$ ，由上面的定理可知，此方程有解且仅当        $gcd(a,m)=1$ .(也就是 $a,m$ 互质？)。于是其所有的解都膜 $m$同余。

**规定**（龟腚（啥呀--乌龟的屁股））：

给定整数 $a$ ,且满足 $gcd(a,m)=1$ ,称 $ ax\equiv 1\pmod{m}$ 的一个接为 $a$ 膜 $m$ 的逆。


------------


------------

## 中国剩余定理 ：

铺垫完以后，就进入正题。

中国剩余定理带上扩展两字后，就从特殊一点的形式转化为了更一般的形式。

先看 $m$ 互质的，看了之前的，也知道这是一个限制条件。

首先，构造同余方程组的一个联立解。为此，令 $M_k= \dfrac{\prod_{i=1}^r m_i }{m_k}$。因为 $j \neq k$ 时 $gcd(m_j,m_k)=1$,知  $gcd(M_k,m_k)=1$.可求得 $M_k$ 膜 $m_k$ 的一个逆 $ y_k$,所以 $M_k *y_k \equiv 1\pmod{m_k}$.现在构造和：

$$x=a_1M_1y_1+a_2M_2y_2...+a_rM_ry_r$$ （如果是要解方程，这里就结束了，但是接下来我们给出证明）

整数 $x$ 就是 $r$ 个同余方程的联立解。要证明这一点，只需要证明对于 $k=1,2,...,r$ 有 $x\equiv a_k \pmod{m_k}$ .因为 $j \neq k$ 时 $m_k|M_j$ ,所以 $M_j \equiv0\pmod{m_k}$。因此，在 $x$ 的和式中，除了第 $k$ 项之外的所有项都和 $0 (mod \ m_k)$同余。从而，$x \equiv a_kM_ky_k\equiv a_k \pmod{m_k}$ , 这是因为 $M_ky_k\equiv1\pmod{m_k}$.

好啦对于这个特殊的，先上一个代码：

```cpp
void exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
	{ 
	    x=1; 
	    y=0; 
	    return;
	}
    exgcd(b,a%b,x,y);
    int zz=x;
    x=y; 
	y=zz-a/b*y;
}
int main()
{
    int ans=0,M=1,x,y;
    for(int i=1;i<=k;++i) 
	{
    	M*=m[i];
	}
    for(int i=1;i<=k;++i)
    {
        int zz=M/m[i];
        exgcd(zz,m[i],x,y);
        x=(x%m[i]+m[i])%m[i];
        ans=(ans+zz*x*a[i])%M;
    }
    cout<<(ans+M)%M;
}

```
注意，重复强调，这里的 $m[i]$ 是互质的.

------------

对于模数不满足两两互质，我们也有方法判断线性同余方程组是否有解，并求出方程组的解。请看：

我们可以考虑使用数学归纳法，假设已经求出了前 $k-1$ 个同余方程构成的方程组的一个解 $x$. 记为 $m=\prod_{i=1}^{k-1} m_i$, 则 $x+i*m\ (i\in Z)$是前 $k-1$方程的通解。

考虑第 $k$ 个方程 求出 $t$ 使得  考虑第 $k$ 个方程 求出 $t$ 使得 $x+t*m \equiv a_k \pmod{m_k}$ .该方程等价于 $m*t \equiv a_k -x \pmod{m_k}$,其中 $t$ 是未知量。这就是一个线性同余方程，可以用扩展欧几里得算法判断是否有节，并求出它的解。若有解，则 $x'=x+t*m$ 就是前 $k$ 个方程构成的方程组的一个解。

综上所述，我们使用 $n$ 次扩展欧几里得算法，就求出了整个方程组的解。

### 代码如下 ：

```cpp
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0)
	{
	    x=1;
		y=0;
		return a;
	}
    long long d=exgcd(b,a%b,x,y);
    long long kk=x;
    x=y; 
	y=kk-a/b*y;
    return d;
}
long long china()
{
    long long x,y,k;
    long long M=m[1],ans=a[1];
    for(int i=2;i<=n;i++)
    {
        long long a=M,b=m[i]
		long long c=(ai[i]-ans%b+b)%b;
        long long d=exgcd(a,b,x,y)
		long long thea=b/d;
        if(c%d!=0) 
        {
        	return -1; 
		}
        x=mul(x,c/d,thea);//快速乘龟速乘你们随意，反正我懒得写了。 
        ans+=x*M;
        M*=thea;
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}

```

好了，关于扩展中国剩余定理就是这样。

---

## 作者：Great_Influence (赞：8)

前置要求:扩展欧几里得算法

先不考虑同时合并所有方程，而是考虑合并两个。

加入这两个方程联立得到的方程组为:

$$\begin{cases}x\equiv A\pmod{B}\\x\equiv a_i\pmod{b_i}\end{cases}$$

将膜方程组化成正常形式得:

$$\begin{cases}x= A+Bk_1\\x=a_i+b_ik_2\end{cases}$$

上下相减，得:

$$Bk_1-b_ik_2=a_i-A$$

运用扩展欧几里得算法可以解出$k_1=r+b_i t$($t$是任意整数)。

那么，回代可以算出$x=A+Br+Bb_i t$。

简单发现，这是$B$和$b_i$互质的情况。

那么，当$B$和$b_i$不互质时，考虑先除去$\gcd(B,b_i)$。即:

$$\frac{B}{\gcd(B,b_i)}k_1-\frac{b_i}{\gcd(B,b_i)}k_2=\frac{a_i-A}{\gcd(B,b_i)}$$

这样算出来$k_1=r+\displaystyle\frac{b_i}{\gcd(B,b_i)}t$。

回代后，解出:

$$x=A+Br+lcm(B,b_i)t$$

时间复杂度$O(n\log n)$。$\gcd$的$\log$一般跑不满。

注意，如果害怕溢出的话，可以全程使用__int128来解决。但是$CCF$系列就只能认真打慢速乘了。

代码:

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register uint32 i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register uint32 i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
#define pb push_back
using uint32=unsigned int;
using uint64=unsigned long long;
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}

template<typename T>inline void write(T x,char ed='\n')
{
    static int sta[111],tp;
    if(!x){putchar('0'),putchar(ed);return;}
    for(tp=0;x;x/=10)sta[++tp]=x%10;
    for(;tp;putchar(sta[tp--]^48));
    putchar(ed);
}

void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}

const int MAXN=1e6+7;

static int n;

typedef __int128 uint128;

inline void exgcd(uint128 a,uint128 b,uint128 &x,uint128 &y)
{
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	swap(x,y);y-=(a/b)*x;
}

inline uint128 getss(uint128 k,uint128 y){k%=y;k+=y;return k%y;}

inline void work()
{
	read(n);
	static __int128 x,y,X,Y,k,r,d;
	read(Y);read(X);
	Rep(i,2,n)
	{
		read(y);read(x);
		d=__gcd(y,Y);
		y/=d;
		exgcd(Y/d,y,k,r);
		Y*=y;
		k=(__int128)getss(k,Y)*getss((x-X)/d,Y)%Y;
		X=(X+(__int128)Y/y*k%Y)%Y;
	}
	printf("%lld\n",(long long)X);
}

int main(void)
{
    file();
    work();
    return 0;
}
```

---

## 作者：fighter (赞：5)

洛谷不知为何会炸Latex，推荐[博客](https://blog.csdn.net/qq_30115697/article/details/88196216)食用
# 中国剩余定理

## 用途

​	中国剩余定理一般用于求解模数互质线性同余方程组。形式如下：

$$
\begin{cases}
x \equiv {a_1} \pmod {b_1} \\
x \equiv {a_2} \pmod {b_2} \\
\ldots \\
x \equiv {a_i} \pmod {b_i} \\
\ldots \\
x \equiv {a_n} \pmod {b_n}
\end{cases}
$$

## 求解方法

​	首先设$M$为所有模数的乘积，即$\prod \limits_{i=1}^{n} b_i$。

​	我们构造一个$x=\sum \limits_{i=1}^{n} {a_i} \cdot {t_i} \cdot {m_i}$，其中$m_i=\frac{M}{b_i}$，$t_i\cdot m_i \equiv 1 \pmod{ b_i} $，可以证明$x$为方程组的一个特解。证明如下：

​	由于$m_i=\frac{M}{b_i}$，且**模数均两两互质**，那么其余模数必然是$b_i$的倍数。又因为$t_i\cdot m_i \equiv 1 \pmod{ b_i} $，所以$x \equiv a_i \pmod{b_i}$。得证。

​	观察$x$的构造过程，发现只有$t_i$是未知量，于是我们可以单独对于每一个方程，利用扩展欧几里得算法，求出每一个$b_i$对应的$t_i$，同时$ans$累加上${a_i} \cdot {t_i} \cdot {m_i}$。

## 例题&代码

### [洛谷P1495 曹冲养猪](https://www.luogu.org/problemnew/show/P1495)

中国剩余定理板子题，不过代码中的数组名称与上文的描述有些区别。

### 洛谷P3868 [TJOI2009]猜数字

还是模板题。

```cpp
//曹冲养猪
#include <bits/stdc++.h>
#define ll long long
#define MAXN 15
using namespace std;

int n;
ll mod[MAXN], b[MAXN], ans;

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll res = exgcd(b, a%b, x, y);
    ll t = x;
    x = y;
    y = t-a/b*y;
    return res;
}

void solve(){		//中国剩余定理 
    ll m = 1;
    for(int i = 1; i <= n; i++){
        m *= mod[i];
    }
    ll x, y, mi;
    for(int i = 1; i <= n; i++){
        mi = m/mod[i];
        exgcd(mi, mod[i], x, y);
        ans += (mi*x*b[i]);
        ans %= m;
    }
    ans = (ans+m)%m;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d%d", &mod[i], &b[i]);
    }
    solve();
    cout << ans << endl;
    
    return 0;
}
```

------

# 扩展中国剩余定理

## 用途

​	为什么需要这样一个扩展的定理呢？很明显，中国剩余定理的描述中有一个至关重要的限制条件：**模数两两互质**。	然而实际上，即使模数不互质，也能对方程组进行求解。这就是扩展中国剩余定理。但实际上，除了解决的问题基本相同，扩展中国剩余定理在证明和实现上都不仅仅是“扩展”，所以XX通索性称其为扩展欧几里得解线性同余方程。

## 求解方法

​	首先，我们改变一些定义，设当前正在处理第$i$个方程，则令$M$表示前$i-1$个模数的最小公倍数。令$x$为前$i-1$个方程的特解，$x'$为所求的前$i$组方程的特解。于是对于第$i$个方程，问题转化为求一个$t$，使得${x+m*t} \equiv {a_i} \pmod {b_i}$，而$x'={x+m*t}$。

​	该方程等价于$m*t \equiv {a_i-x} \pmod {b_i}$，显然只有$t$是未知量于是我们就可以利用扩欧求出$t$。一直重复$n$遍，最终就可以得到方程组的解。

## 例题&代码

### 洛谷P4777 【模板】扩展中国剩余定理（EXCRT）

真·模板题。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 100005
using namespace std;

ll n, m, ans;
ll a[MAX], b[MAX];

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){
        x = 1, y = 0;
        return a;
    }
    ll res = exgcd(b, a%b, x, y);
    ll t = x;
    x = y, y = t-a/b*y;
    return res;
}

ll mul(ll a, ll b, ll mod){
    ll res = 0, base = a;
    while(b){
        if(b&1){
            res = (res+base)%mod;
        }
        base = (base+base)%mod;
        b >>= 1;
    }
    return res;
}

ll excrt(){
    m = b[1], ans = a[1];
    for(int i = 2; i <= n; i++){
        ll p = ((a[i]-ans)%b[i]+b[i])%b[i];
        ll x, y;			//mx=p (mod b[i])
        ll gcd = exgcd(m, b[i], x, y);
        if(p % gcd) return -1;
        x = mul(x, p/gcd, b[i]/gcd);
        ans += x*m;
        m *= b[i]/gcd;
        ans = (ans%m+m)%m;
    }
    return (ans%m+m)%m;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &b[i], &a[i]);
    }
    printf("%lld\n", excrt());
    
    return 0;
}
```



# 完结撒花

## GL && HF!!!

---

## 作者：YCS_GG (赞：5)

我们先考虑简单的同余方程组

$$\left\{\begin{matrix}x \equiv b_1 (\mod a_1)\\ x \equiv b_2 (\mod a_2)\end{matrix}\right.$$
将其化成$\left\{\begin{matrix}x = b_1k_1 + a_1\\ x = b_2k_2 + a_2\end{matrix}\right.$即
$b_1k_1=a_2-a_1+b_2k_2$

根据拓展欧几里得,有解的充要条件为$gcd(b_1,b_2)|(a_2-a_1)$

令$t=gcd(b_1,b_2)$

等式两边同除以$t$得$$\frac{b_1}{t}k_1=\frac{a_2-a_1}{t}+\frac{b_2}{t}k_2$$即$$\frac{b_1}{t}k_1 \equiv \frac{a_2-a_1}{t} (\mod \frac{b_2}{t}) $$

化简得$$k_1 \equiv (\frac{b_1}{t})^{-1}*\frac{a_2-a_1}{t} (\mod \frac{b_2}{t})$$
$$k_1=(\frac{b_1}{t})^{-1}*\frac{a_2-a_1}{t}+y\frac{b_2}{t}$$

代回原式得

$$x=b_1*(\frac{b_1}{t})^{-1}*\frac{a_2-a_1}{t}+y\frac{b_1b_2}{t}+a_1$$

此时,我们得到新同余方程
$$x \equiv c (\mod m)$$

其中$c=b_1*(\frac{b_1}{t})^{-1}*\frac{a_2-a_1}{t}$,
$m=\frac{b_1b_2}{gcd(b_1,b_2)}$

然后仿照上面的步骤做就好了

#### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],b[100005];
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return ;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
int Inv(int a,int m){
	int x=0,y=0;
	exgcd(a,m,x,y);
	x=(x%m+m)%m;
	if(!x)
		x=m;
	return x;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=2;i<=n;i++){
		int a1=a[i-1],a2=a[i],b1=b[i-1],b2=b[i];
		int t=__gcd(a1,a2);
		a[i]=(a1*a2)/t;
		b[i]=Inv(a1/t,a2/t)*((b2-b1)/t)%(a2/t)*a1+b1;
		b[i]=(b[i]%a[i]+a[i])%a[i];
	}
	cout<<b[n];
}
```

---

## 作者：Fading (赞：4)

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

## 作者：名杨天吓 (赞：3)

# **三、扩展中国剩余定理**
解x关于多个ai，mi同时满足x$\equiv$ai (%mi)的多组不定方程解

考虑将两个方程合并，即将x$\equiv$a1 (%m1)与 x$\equiv$a2 (%m2)合并为一个新的不定方程

x$\equiv$A (%M)

现考虑A和M的值

若x满足两式，x的形式一定是x=um1+a1=vm2+a2;

对于um1+a1=vm2+a2,变形得um1-vm2=a2-a1①

m1，m2,a2-a1已知，u，v为待求未知量

类似于ax+by=c,所以可以套用exgcd求解

得出来一组解u0,v0（exgcd得出来的是um1+vm2=gcd(u,v)的解）

因为题目保证有解，所以gcd(u,v)|(a2-a1)

所以将u0,v0放大$\frac{a2-a1}{gcd(u,v)}$倍，得到关于①式的一组解u1,-v1（因为求解时将加减号反向，所以v的解符号也反向-v1为应为正数）；

因为结果要求最小正整数解，因此合并后的A应该最小，所以①式中u的解应该最小，需要通过调整将u1调整为最小解

u1m1-(-v1)m2=a2-a1

(u1-$m2 \over gcd$)m1-(-v1-$m1 \over gcd$)m2=a2-a1

所以u1不断减$m2 \over gcd$都为可行解，当u1减到不能减为止，即u'=u%$m2\over gcd$时，u'为最小解。这个减的数一定要为最小的可行跨度，不然会漏解，至于最小跨度为什么是$m2 \over gcd$，因为可以将m2,m1作为跨度,要使其缩小，就要同除一个数（必须整除）,所以除数最大就是gcd，所以$m2\over gcd$就是最小跨度。

用最小解更新A=u'*m1+a1;

现在一定有最小的x=A

但x还要满足其它更多的式子，因此x就要扩大，所以我们需要找到一个扩大的最小跨度使它始终满足x$\equiv$A （%M）,M就是最小跨度

这个最小跨度应为lcm(m1,m2),仔细想想应该知道，加上一个lcm，始终满足x=um1+a1=vm2+a2,只是u,v变大了而已

所以每次更新A和M，得到一个新的不定式方程，准备和下一个方程合并

最后只剩一个式子x$\equiv$A (%M) 满足这个式子的最小正整数解肯定为x=A，所以最后输出A即可。

在操作的时候要考虑负数，负数取模只需要用这样的操作(k%M+M)%M即可（不然龟速乘会死循环，因为负数右移最高位一直补1）


以下是代码
------------

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,m,A,M,d,u,v;
void exgcd(ll a,ll b,ll &d,ll &x,ll &y)
{
	if(b)	exgcd(b,a%b,d,y,x),y-=x*(a/b);//懒人精简版exgcd，理解不来可以背，也可以写普通的
	else d=a,x=1,y=0;
}

ll mul(ll a,ll b,ll p)
{
	ll ans=0;
	for(;b;b>>=1,a=(a+a)%p)
		if(b&1)	ans=(ans+a)%p;
	return ans;
}

int main()
{
	scanf("%lld",&n);
	scanf("%lld%lld",&M,&A);
	A%=M;
	for(int i=1;i<n;i++)
		{
			scanf("%lld%lld",&m,&a);//读入新的待合并的a,m
			a%=m;
			exgcd(m,M,d,u,v);	//求解um+vM=gcd(u,v)
			M=m/d*M;//更新M
			u=mul((u%M+M)%M,((A-a)/d%M+M)%M,M);//龟速乘，扩大还原解并调整成最小解
			A=(mul(u,m,M)+a)%M ;//更新A
		}
	printf("%lld\n",A);
	return 0;
}
```


---

## 作者：wwlw (赞：2)

##非扩展

用于求解线性同余方程组 ，**其中模数两两互质** .

先来看一看两个显然的定理：

   1.若 x $\equiv$ 0 (mod p) 且 y $\equiv$ 0 (mod p) ,则有 x+y $\equiv$ 0 (mod p)

   2.若 x $\equiv$ b (mod p) 且 y $\equiv$ 0 (mod p), 则有 x+y $\equiv$ b (mod p)  (0$\leq $b<p)

则整个方程组可以写为
 
$b_1$ $\begin{bmatrix}1\\0\\0\end{bmatrix}$ + $\cdots $+ $b_i$ $\begin{bmatrix}0\\1\\0\end{bmatrix}$ + $\cdots $ + $b_n$  $\begin{bmatrix}0\\0\\1\end{bmatrix}$

也就是说，想要求出最终方程组的解就只需要求出上面每个行列式的值。

考虑每个式子中，因为每两个模数之间两两互质，设 N=$ \sum_{i=1}^nm_i$

则GCD($\frac{N}{m_i}$ , $m_i$) = 1 , N/$m_i$即为其他模数的lcm，即为其他n-1个方程的解，第i个方程的解可以写成$x_i=N / m_i * y $
 
即 N/$m_i * y $ $\equiv$ $ 1 (mod$ $m_i)$

此方程等价于 N/$m_i * y + m_i$ * z=1 ,可以用扩展欧几里得求解。

求出$x_i$后 ，有 $b_i * x_i$ $\equiv $ $b_i$ (mod $m_i$)

最后整个方程组的解就为 X = $\sum_{i=1}^n b_i * x_i $ mod N

Code:
```cpp

#include<stdio.h>
#define N 100

long long W[N],B[N],nn,T;
inline void exgcd(long long a,long long b,long long &x,long long &y){
	if(!b){
		x=1;y=0;
	}else{
		exgcd(b,a%b,x,y);
		long long t=x;
		x=y;
		y=t-a/b*y;
	}
}
inline long long China(long long k){
	long long x,y,a=0,m,n=1;
	for(long long i=0;i<k;i++) n*=W[i];
	for(long long i=0;i<k;i++){
		m=n/W[i];
		exgcd(W[i],m,x,y);
		a=a+y*B[i]*m;
	}
	a%=n;
    while(a<=0) a+=n;
    while(a>=n) a-=n;
    return a;
}
signed main(){
	scanf("%lld",&nn);
	for(long long i=0;i<nn;i++)
		scanf("%lld",&B[i]);
	for(long long i=0;i<nn;i++)
		scanf("%lld",&W[i]);
	for(long long i=0;i<nn;i++)
		B[i]=(B[i]%W[i]+W[i])%W[i];
	printf("%lld",China(nn));
}
```

##扩展

   刚刚学习了中国剩余定理，现在来学习它的扩展。先说句闲话，不知道是不是扩展过头了，其实中国剩余定理和它的扩展关系不大，所以先请忘记刚刚在上文所看到的一切套路，开始新的征程。

   好了，现在模数**不是两两互质的**了，也就是说先前求的N不是它们的LCM，不能直接用。

   我们考虑构造的方法，假设我们已经求出了前k-1个方程的和解，现在需要**合并**第k个方程。

   设前k-1个方程的和解为X，则他们的通解可以写成 X + t * N (其中N为前k-1个模数的LCM)

   则要合并第k个方程，即要解如下方程
   $$ X + t * N \equiv b_k   ( mod  m_k )  $$

   此方程又等价于 $$ t * N + m_k * y = b_k-X $$

   晃眼一看，又是扩展欧几里得。求出 t 后 ，前k个方程的解就为 $X^*$ = X + t * N , 继续更新 N ,N = LCM(N,$m_k$)

   Code:
```cpp
#include<stdio.h>
#define N 100006
#define ll long long

ll a[N],b[N],ans,B,M,GCD,x,y;
int n;
template<class T>
inline void read(T &x){
	x=0;T flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	x*=flag;
}
inline ll exgcd(ll a,ll b,ll &xx,ll &yy){
	if(!b){
		xx=1;yy=0;
		return a;
	}
	ll gcd=exgcd(b,a%b,xx,yy);
	ll tmp=xx;
	xx=yy;
	yy=tmp-(a/b)*yy;
	return gcd;
}
inline ll mul(ll a,ll b,ll Mod){
	ll ans=0;
	while(b){
		if(b&1) ans=(ans+a)%Mod;
		a=(a<<1)%Mod;
		b>>=1;
	}
	return ans;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),read(b[i]);
	ans=b[1];
	M=a[1];
	for(int i=2;i<=n;i++){
		B=(b[i]-ans%a[i]+a[i])%a[i];
		GCD=exgcd(M,a[i],x,y);
		x=mul(x,B/GCD,a[i]);
		ans+=M*x;
		M*=a[i]/GCD;
		ans=(ans%M+M)%M;
	}
	printf("%lld",ans);
}
/*
3
11 6
25 9
33 17
*/
```

---

## 作者：Bob_Wang (赞：2)

# 什么是拓展中国剩余定理
相信大家都听说过中国剩余定理 ~~（其实没有听说过也没关系，因为拓展中国剩余定理与中国剩余定理其实没有什么关系）~~  。拓展中国剩余定理的大意是这样的：

**给定n组非负整数a~i~,b~i~,求解关于x的方程组：**
**x ≡ b~1~(mod a~1~)
x ≡ b~2~(mod a~2~)
……
x ≡ b~n~(mod a~n~)**
**的最小非负整数解**

# 拓展中国剩余定理的基本思路
假设已有答案 **ans**，满足前**k-1**项条件。

设 **M** 为 **a~1~ —a~(k-1)~** 的最小公倍数，则 **ans + x * M** 一定满足**ans + x * M ≡  b~1~—b~(k-1)~** 。

假设 **ans + x * M ≡  b~k~(mod a~k~)**，那么问题转化为求 **n * M + m * a~k~ = b~k~ - ans** 的最小正整数解。

但必须保证 **b~k~ - ans** 为正数。

# 代码
```cpp
#include<cstdio>
#define ll long long
using namespace std;
ll n,a,b,tot,M;
ll ans,x,y,r;
ll flag=1,mul;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	ll d=exgcd(b,a%b,x,y);
	ll t=y;
	y=x-(a/b)*y;
	x=t;
	return d;
}//求解同余方程
ll quick_mul(ll nw,ll aim,ll mod)
{
	ll res=0;
	while(aim>0)
	{
		if(aim&1)res=(res+nw)%mod;
		nw=(nw+nw)%mod;
		aim>>=1;
	}
	return res;
}//龟速乘QAQ（模板）
int main()
{
	scanf("%I64d",&n);
	while(n--)
	{
		x=0;
		y=0;
		tot++;//tot计数
		scanf("%I64d%I64d",&a,&b);
		if(tot==1)
		{
			ans=b;
			M=a;
			continue;
		}//初始化
		r=exgcd(M,a,x,y);//求最大公因数
		mul=((b-ans)%a+a)%a;
		x=quick_mul(x,mul/r,a);
		if((b-ans)%r!=0)
		{
			flag=0;
			continue;
		}//判断无解
		ans=ans+(x*M);
		M=(M*a)/r;//更新最小公倍数
		ans=(ans%M+M)%M;//保证ans为正值
	}
	if(flag)
	printf("%I64d",ans);
	else
	printf("No");
	return 0;
}
```

但是我这个代码过不了最后三个点，各位大神如果有更好的思路希望在下面评论哦！orz~~~

---

## 作者：C20203030 (赞：2)


最近搞了一发中国剩余定理，写个博客。**jzm orz or2 orz**

## 一、题目

 [点此看题](https://www.luogu.org/problem/P4777)

## 二、解法

**0x01 普通crt**

先讲一下普通$crt$,其实类似于拉格朗日插值法，我们可以构造出这样一个式子：

$x=a_1\frac{M}{m_1}t_1+a_2\frac{M}{m_2}t_2...+a_k\frac{M}{m_k}t_k$

其中$t_i$是$\frac{M}{m_i}$在模$mi$意义下的逆元。

考虑将$x$对$m_1$取模，发现余数就是$a_1$，因为其他的项因含有$m_1$都会被消去，所以我们构造的这个式子是正确的。


**0x02 扩展crt**

考虑两个♂两个取模式子合并的情况，有：

$x=a_1+k_1\cdot m_1$

$x=a_2+k_2\cdot m_2$

$-k_1\cdot m_1+k_2\cdot m_2=a_1-a_2$

设$m_1,m_2$的$gcd$为$d$，$a_1-a_2=c$

当$c$不是$d$的倍数时，$excrt$无解。

否则更新$x$，$x=x-k1\cdot m1$

**0x03 代码**

附上我开了$\_\_int128$的代码。


```cpp
#include <cstdio>
using namespace std;
#define int __int128
const int MAXN = 1e5+5;
int read()
{
	int x=0,flag=1;char c;
	while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
	while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*flag;
}
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1;y=0;return a;}
	int d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}
int n,m[MAXN],r[MAXN];
int excrt()
{
	int M=m[1],R=r[1],x,y;
	for(int i=2;i<=n;i++)
	{
		int d=exgcd(M,m[i],x,y);
		if((R-r[i])%d) return -1;
		x=x*(R-r[i])/d%m[i];
		R-=x*M;
		M=M*m[i]/d;
		R%=M;
	}
	return (R%M+M)%M;
}
signed main()
{
	while(~scanf("%lld",&n))
	{
		for(int i=1;i<=n;i++)
			m[i]=read(),r[i]=read();
		printf("%lld\n",excrt());
	}
}
```


---

## 作者：五更琉璃 (赞：1)

## Chinese remainder theorem(CRT)

前置科技：$exgcd$

设 $m_1,m_2, \cdots m_n$ 是两两互质的整数，$m=\prod_{i = 1}^{n}m_i, M_i=m/m_i, t_i$ 是线性方程 $M_i t_i \equiv 1 \ (mod \ m_i) $ 的一个解，（用人话讲就是 $M_i$ 在模 $m_i$ 意义下的乘法逆元）。对于任意的 $n$ 个整数 $a_1, a_2, \cdots ,a_n$ ，方程组：

$$\begin{cases} x \equiv a_1 (mod \ m_1) \\ x \equiv a_2 (mod \ m_2) \\
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \vdots \\ x \equiv  a_n (mod \ m_n)\end{cases}$$
有整数解，解为 $x = \sum_{i=1}^{n}a_i M_i t_i$。

解方程组过程就是两个两个同余先解出一个解，贡献到答案里，然后合并成为一个方程。

对于两个方程：

$x = a_1 + k_1 * m_1 $

$x = a_2 + k_2 * m_2 $

消去 $x$ 并移项

$ k_1 * m_1 - k_2 * m_2 = a_2 - a_1 $

令 $ C = a_2 - a_1 $ , $ g = gcd(m_1, m_2) $

通过exgcd解得 $k$ 的一组解：$x_1, y_1$

则: 

$ k_1 = x_1 * C / g $


$ k_2 = x_2 * C / g $ 


通解为：

$ k_1 = k_1 + m_2 / g * T $ 

$ k_2 = k_2 + m_1 / g * T $

易得最小正整数解为：

$ k_1 = (k_1 \% (m_2 / g) + m_2 / g ) \% g $

再带入 $ x = a_1 + k_1 * n_1 $ 得到 $ x $ 
 
$ \begin{cases} x \equiv a_1 \ (mod \ m_1) \\ x \equiv a_2 \ (mod \ m_2) \end{cases} \Rightarrow x \equiv a_1 + x * m_1 \ (mod \ LCM(p_1, p_2))$

然后一个一个做下去就得到了最终的解。

[P4777 【模板】扩展中国剩余定理（EXCRT）](https://www.luogu.org/problem/P4777)

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 0; char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return f ? -x : x;
}

const int MAXN = 1e5 + 1;
int n;
int a[MAXN], ni[MAXN];

int exgcd(int a, int b, int &x, int &y) {
	if (!b) { x = 1, y = 0; return a; }
	int d = exgcd(b, a % b, x, y);
	int z = x; x = y; y = z - y * (a / b);
	return d;
}

int EXCRT() {
	int a1 = a[1], n1 = ni[1];
	for (int i = 2; i <= n; ++i) {
		int a2 = a[i], n2 = ni[i];
		int g, A, B, C = a2 - a1;
		g = exgcd(n1, n2, A, B);
		A = ((A * C / g) % (n2 / g) + (n2 / g)) % (n2 / g);
		a1 = A * n1 + a1;
		n1 = n1 * n2 / g;
	}
	return a1;
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i)
		ni[i] = read(), a[i] = read();
	printf("%lld\n", (long long)EXCRT());
	return 0;
}
```

---

## 作者：Reico (赞：1)

扩展中国剩余定理（excrt）， 是中国剩余定理（crt）的扩展版，中国剩余定理用于解决同余方程组

$$\begin{cases}x\equiv a_1\left( mod\,\,m_1 \right)\\x\equiv a_1\left( mod\,\,m_2 \right)\\\vdots\\x\equiv a_n\left( mod\,\,m_n \right)\\\end{cases}$$	
其中$$m_1,m_2,\cdots,m_n$$两两互质

而excrt可以解决$$m_1,m_2,\cdots,m_n$$不互质的情况

~~然而crt和excrt没有半毛钱关系~~

前置知识：exgcd（可能）

规定：$g\left( a,b \right)$为$gcd\left( a,b \right)$

$Inv\left( a,b \right)$为a在mod b意义下的逆元

首先观察方程组$$\begin{cases}x\equiv a_1\left( mod\,\,m_1 \right)\\x\equiv a_1\left( mod\,\,m_2 \right)\\\vdots\\x\equiv a_n\left( mod\,\,m_n \right)\\\end{cases}$$
我们可以拿出两个同余方程，化成普通方程的形式$$\begin{cases}x= a_1+k_1m_1\\x=a_2+k_2m_2\\\end{cases}$$
合并两个方程$$a_1+k_1m_1=a_2+k_2m_2$$
进行移项$$k_1m_1=k_2m_2+a_2-a_1$$
然后我们求出g($m_1$,$m_2$)

可以把式子化成$$\frac{k_1m_1}{g\left( m_1,m_2 \right)}=\frac{k_2m_2}{g\left( m_1,m_2 \right)}+\frac{\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)}$$

很显然$g\left( m_1,m_2 \right)|m_1$且$g\left( m_1,m_2 \right)|m_2$，也就是说该式子有解当且仅当$g\left( m_1,m_2 \right)|\left( a_2-a_1 \right)$

我们将该式子化为同余方程，可以得到$$\frac{k_1m_1}{g\left( m_1,m_2 \right)}=\frac{\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)} mod \left( \frac{m_2}{g\left( m_1,m_2 \right)} \right)$$此时我们就可以用我们的exgcd求逆元，将式子化成这种形式$$k_1=Inv\left( \frac{m_1}{g\left( m_1,m_2 \right)},\frac{m_2}{g\left( m_1,m_2 \right)} \right)\times\frac{\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)} mod \left( \frac{m_2}{g\left( m_1,m_2 \right)} \right)$$

再带回去~~好**啊~~

$$k_1=Inv\left( \frac{m_1}{g\left( m_1,m_2 \right)},\frac{m_2}{g\left( m_1,m_2 \right)} \right)\times\frac{\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)}+y\times\frac{m_2}{g\left( m_1,m_2 \right)}$$
是不是没法化简了？~~这就体现了我非常的弱~~

还记得一开始的式子么$x=k_1m_1$

我们为什么不代回去呢
$$x=a_1+Inv\left( \frac{m_1}{g\left( m_1,m_2 \right)},\frac{m_2}{g\left( m_1,m_2 \right)} \right)\times\frac{m_1\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)}+y\times\frac{m_1m_2}{g\left( m_1,m_2 \right)}$$

继续化成同余方程$$x=a_1+Inv\left( \frac{m_1}{g\left( m_1,m_2 \right)},\frac{m_2}{g\left( m_1,m_2 \right)} \right)\times\frac{m_1\left( a_2-a_1 \right)}{g\left( m_1,m_2 \right)}mod\left( \frac{m_1m_2}{g\left( m_1,m_2 \right)} \right)$$
此时我们就完成了两个式子的合并

推广下去，最终合并成一个式子

eg：洛谷P4777【模板】扩展中国剩余定理（EXCRT）

由于这题不存在无解的情况，所以我的代码里没用判断无解的情况，到时候用的时候自己判断一下即可 

code：
```cpp
#include <iostream>
#include <cstdio>

using namespace std ;

typedef __int128 ll ;
const int maxn = 1e5 + 5 ;

int n ;
long long p, q ;
ll x, y ;
ll c[maxn], m[maxn] ;

ll Gcd (ll a, ll b){
	return !b ? a : Gcd (b, a % b) ;
}

void Exgcd (ll a, ll b, ll &x, ll &y){
	if (!b){
		x = 1 ;
		y = 0 ;
		return ;
	}
	Exgcd (b, a % b, x, y) ;
	ll tmp = x ;
	x = y ;
	y = tmp - (a / b) * y ;
	return ;
}
	
ll Inv (ll a, ll b){
	Exgcd (a, b, x, y) ;
	while (x < 0) x += b ;
	return x ;
}

int main (){
	scanf ("%d", &n) ;
	for (int i = 1; i <= n; ++i){
		scanf ("%lld%lld", &p, &q) ;
		c[i] = q ;
		m[i] = p ;
	}
	for (int i = 2; i <= n; ++i){
		ll m1 = m[i - 1] ;
		ll m2 = m[i] ;
		ll c1 = c[i - 1] ;
		ll c2 = c[i] ;
		ll g = Gcd (m1, m2) ;
		m[i] = (m1 * m2) / g ;
		c[i] = (Inv (m1 / g, m2 / g) * (c2 - c1) / g) % (m2 / g) * m1 + c1 ;
		c[i] = (c[i] % m[i] + m[i]) % m[i] ;
	}
	long long res = (long long) c[n] ;
	printf ("%lld\n", res) ;
	return 0 ;
}
```

---

## 作者：PurpleWonder (赞：1)

话说洛谷更新速度真的惊人，NOIday2t1刚考完一天，模板题就出来了。

扩展中国剩余定理，又称~~中国单身狗定理~~孙子定理，是一种求解一次同余式组的方法。

在学习中国剩余定理之前，需要先学习扩展欧几里得定律。

扩展欧几里得定律具体作用为：给定两个正整数a，b，求得**一组**x,y，使a*x+b*y=gcd(a,b)。由于（不扩展的）欧几里得定律gcd(a,b)=gcd(b,a%b),我们可以尝试推导出b*x+(a%b)*y=gcd(a,b),再由此时的x与y求出上一步的x与y，递归求得结果。

推导方法：

b*x1+(a%b)*y1=gcd(b,a%b)

a*x2+b*y2=gcd(a,b)

由于gcd(b,a%b)=gcd(a,b)

所以a*x2+b*y2=b*x1+(a%b)*y1

a*x2+b*y2=b*x1+[a-(a/b)*b]*y1

a*x2+b*y2=b*x1+a*y1-(a/b)*b*y1

a*x2+b*y2=a*y1+b*[x1-(a/b)*y1]

根据恒等定理，

x2=y1

y2=x1-(a/b)*y1

求出一个x,y后，其余的x,y满足：

x=x+k*(b/gcd(a,b))

y=y-k*(a/gcd(a,b))(k为任意整数)

那么递归到什么时候呢？

根据欧几里得定律，辗转相除到b=0时，这时的a便为最初的a与b的最大公约数，因此此时的x=1,y=0

于是代码就出来啦：
```cpp
int ex_gcd(int a,int b,int &x,int &y){
    if (b==0){
        x=1;y=0;
        return a;
    }
    int gcd=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return gcd;
}
```

接下来便要正式介绍扩展中国剩余定理了，由于面对的是一个同余方程组，因此需要将每两个同余方程合并，直至只剩一个。如何合并呢？接下来是推导过程：

y=a1*x1+b1

y=a2*x2+b2

a1*x1+b1=a2*x2+b2

a1*x1-a2*x2=b2-b1

这时我们便把两个式子变成了可以用扩展欧几里得定律解决的式子，只要在这个式子中求出一对x1,x2使a1*x1-a2*x2=gcd(a1,a2)，再将x1,x2分别乘(b2-b1)/gcd，便可以得到上述式子的一个解，再将求得的式子代回去，便可求得y的值，成为合并后新式子的余数，而原来的两个模a1,a2的最小公倍数(即a1*a2/gcd(a1,a2)),便为新式子的模了。

最后的完整代码如下：

```cpp
#include<cstdio>
#define ll long long
using namespace std;

long long x,y;

struct node{
	ll a;//模 
	ll b;//余数 
}now,last;

int n;
//扩展欧几里得 
ll ex_gcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	ll gcd=ex_gcd(b,a%b,x,y);
	ll temp=y;
	y=x-a/b*y;
	x=temp;
	return gcd;
}
//扩展中国剩余定理 
node ex_crt(node p,node q){
	ll gcd=ex_gcd(p.a,q.a,x,y);
	x*=(q.b-p.b)/gcd;//求出一个x值 
	x%=q.a/gcd;//取模防止越界： 
	p.b=x*p.a+p.b;//求出新的余数 
	p.a=p.a*q.a/gcd;//求出新的模 
	p.b=((p.b%p.a)+p.a)%p.a;//对余数取下模，防止奇奇怪怪的问题 
	return p;
}

int main(){
	scanf("%d",&n);
	scanf("%lld %lld",&last.a,&last.b); 
	for(int i=1;i<n;i++){
		scanf("%lld %lld",&now.a,&now.b);
		last=ex_crt(last,now);
	}
	printf("%lld\n",last.b);
	return 0;
}
```

本蒟蒻第一次写题解，望大家指教。

---

## 作者：Dawn_cx (赞：0)

先推一下本蒟蒻的博客吧 [博客](blog.csdn.net/dhdhdhx)

然后推一下本篇题解的博客[题解](https://blog.csdn.net/dhdhdhx/article/details/102990227)

$ok$入正题

首先 了解扩展中国剩余定理 你真的一点都不需要了解中国剩余定理

不过 你需要了解逆元 扩展欧几里得 


所以...

如果不会逆元的请看这里(中国剩余定理也有$----->$ [详解数论从入门到入土](https://blog.csdn.net/dhdhdhx/article/details/102690006)
$PS:$这篇题解非常详细 适合数论初学者哦!


想更好地把逆元应用到欧拉函数、欧拉定理、费马小定理、中国剩余定理请看这里$----->$[数论1](https://blog.csdn.net/dhdhdhx/article/details/97544878)

想更好地把逆元应用到组合数、扩展欧几里得请看这里$----->$[数论2](https://blog.csdn.net/dhdhdhx/article/details/97619552)
咳咳很好

ok说正事

什么是扩展中国剩余定理 就是下面这个:

$\begin{cases} n\equiv a_1(\mod m_1)\quad \\ n\equiv a_2(\mod m_2)\quad \\... \\ n\equiv a_k(\mod m_k)\quad \ \end{cases}$

其中$(m_1,m_2,...,m_k)$不一定是$1$,求$n$的最小非负整数解

$Solution:$
假设已经求出前$k-1$个方程组成的同余方程组的一个解为$x$
设$M=\prod_{i=1}^{k-1}m_i$，前$k-1$个方程的最小非负整数解为$x$

则前$k-1$个方程组的通解为$x+Mi\,\,\,\,\,\,(i∈Z)$

对于加入的第$k$个方程 我们就是要找一个$t∈Z$使得
 $x+Mt\equiv a_k(mod\,\,m_k)$
 
 即 $Mt\equiv a_k-x(mod\,\,m_k)$
 对于这个式子我们已经可以通过扩展欧几里得求解
 
 若该同余式无解，则整个方程组无解
 
 若有，则前$k$个同余式组成的方程组的一个解解为$x_k=x+Mt$
 
 所以整个算法的思路就是求解$k$次扩展欧几里得
 
 模板题:[洛谷P4777 【模板】扩展中国剩余定理（EXCRT）](https://www.luogu.org/problem/P4777)
 代码:
 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N int(1e5+10)
#define reg register
typedef long long ll;
inline void read(ll &x){
	ll s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
	x=s*w;
}
inline ll slowmul(ll x, ll y, ll m){
	while(x<0)x+=m;
	while(y<0)y+=m;
	if(x<y)swap(x,y);
	ll ret=0;
	while(y){
		if(y&1)(ret+=x)%=m;
		(x<<=1)%=m,y>>=1;
	}
	return ret;
}
void Extended_Greatest_Common_Divisor(ll a, ll b, ll &x, ll &y){
	if(!b){x=1,y=0;return;}
	Extended_Greatest_Common_Divisor(b,a%b,y,x);y-=(a/b)*x;
}
ll n,ai[N],bi[N];
ll Extended_Chinese_Remainder_Theorem(){
	ll x,y,a,b,c,M=bi[1],ans=ai[1],gcd;
	for(ll i=2;i<=n;i++){
		a=M,b=bi[i],c=(ai[i]-ans%b+b)%b,gcd=__gcd(a,b);
		if(c%gcd)return -1;
		a/=gcd,b/=gcd,c/=gcd;
		Extended_Greatest_Common_Divisor(a,b,x,y);
		x=slowmul(x,c,b),ans+=x*M,M*=b;
		ans=(ans%M+M)%M;
	}
	return ans;
}
int main(){
	read(n);
	for(reg ll i=1;i<=n;i++)read(bi[i]),read(ai[i]);
	printf("%lld\n",Extended_Chinese_Remainder_Theorem());
}
```
顺带一下中国剩余定理的模板题吧:

[[TJOI2009]猜数字](https://www.luogu.org/problem/P3868)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll slowmul(ll x, ll y, ll mod){
    if(x<0)x+=mod;if(y<0)y+=mod;
    if(y>x)swap(x,y);
    ll ret=0;
    while(y){
        if(y&1)(ret+=x)%=mod;
        (x+=x)%=mod,y>>=1;
    }
    return ret;
}
ll k,a[20],b[20],t[20];
void Extended_Greatest_Common_Divisor(ll n, ll m, ll &x, ll &y){
    if(!m){x=1,y=0;return;}
    Extended_Greatest_Common_Divisor(m,n%m,y,x);y-=(n/m)*x;
}
ll Chinese_Remainder_Theorem(){
    ll ans=0,lcm=1,x,y;
    for(int i=1;i<=k;i++)lcm*=b[i];
    for(int i=1;i<=k;i++){
        t[i]=lcm/b[i];
        Extended_Greatest_Common_Divisor(t[i],b[i],x,y);
        x=(x%b[i]+b[i])%b[i];
        ans=(ans+slowmul(slowmul(t[i],a[i],lcm),x,lcm))%lcm;
    }
    return (ans+lcm)%lcm;
}
int main(){
    scanf("%lld",&k);
    for(int i=1;i<=k;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=k;i++)scanf("%lld",&b[i]);
    printf("%lld\n",Chinese_Remainder_Theorem());
}


```

 


---

## 作者：Edward_Elric (赞：0)

### 扩展中国剩余定理(excrt)

还是对于
则对于方程组

$$\begin{cases}x\equiv a_1\pmod {m_1}\\x\equiv a_2\pmod {m_2}\\......\\x\equiv a_n\pmod {m_n}\end{cases}$$

如果$m$不互质。那么我们就没法使用$crt$。

那么这时候就需要$excrt$

$excrt$怎么操作

对于任意两个方程组
$$\begin{cases}x\equiv a_1\pmod {m_1}\\x\equiv a_2\pmod {m_2}\end{cases}$$

我们变为一元一次方程的形式

$$\begin{cases}x=k_1m_1+a_1\\x=k_2m_2+a_2\end{cases}$$

则有
$$k_1m_1+a_1=k_2m_2+a_2$$

移项
$$k_1m_1-k_2m_2=a_2-a_1$$

然后我们发现这个东西形如
$$ax+by=z$$
可以用$exgcd$解

我们知道$exgcd$无解情况$z\nmid gcd(a,b)$。

那么$(a_2-a_1)\nmid gcd(m_2,m_1)$时，$excrt$无解

于是我们知道了$k_1,k_2$的值，可以倒推回去求出一个$x_0$

这个有什么用呢,因为
$$\begin{cases}x=k_1m_1+a_1\\x=k_2m_2+a_2\end{cases}$$

很显然$x$的通解为$x=x+k* lcm(m_1,m_2)$

然后要用到一个同余奇巧淫技
$$x\equiv{x_0}\pmod{lcm(m_1,m_2)}$$

然后我们就这样快乐的把两个同余方程合成了一个。那么这样合$n-1$次最后$x_0$的最小正整数就是最终解了

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+100;
ll a[maxn],b[maxn];
ll x,y,d;
int n;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void exgcd(ll a,ll b,ll &x,ll &y,ll &d){
	if(!b){
		x=1,y=0,d=a;return;
	}
	exgcd(b,a%b,y,x,d);
    y-=a/b*x;
	return;
}
ll mul(ll a,ll b,ll p){
	ll ret=0;
	for(;b;b>>=1){
		if(b&1)ret=(ret+a)%p;
		a=(a+a)%p;
	}
	return ret;
}
ll excrt(){
	ll m=a[1],r=b[1];
	for(int i=2;i<=n;i++){
		exgcd(m,a[i],x,y,d);
		if((b[i]-r)%d)return -1;
		x=mul((b[i]-r)/d,(x%(a[i]/d)+(a[i]/d))%(a[i]/d),a[i]/d);
		r+=x*m;
		m*=a[i]/d;
		r%=m;
	}
	return ((r%m)+m)%m;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	printf("%lld\n",excrt());
	return 0;
}
```

---

## 作者：Ydkwia (赞：0)

对于此题，我们会想到中国剩余定理，然而~~跟这题没有任何关系~~
本题中ai不一定两两互质，所以中国剩余定理不在适用。

扩展中国剩余定理：
通过~~找规律~~数学归纳法，假设已经求出了前 k - 1 个方程的一个解x。记 m = lcm( m1 , m2 , ... , m(k-1) ) , 则 x + i * m ( i ∈ Z ) 是前 k - 1 个方程的通解。
考虑第 k 个方程 , 求出第一个整数 t , 使得 x + t * m ≡ ak ( mod mk ) 。该方程等价于 m * t ≡ ak - x ( mod mk ) , 其中 t 是未知量。这就是一个线性同余方程，可以用扩展欧几里得算法判断是否有解，并求出它的解。若有解，则前 k 个方程构成的方程组的一个解 ans 可以算出 ans = x + t * m 。
综上所述，我们使用n次欧几里得算法，就求出了整个方程的解。
									——《算法竞赛•进阶指南》
                                    
于是我们就可以做出这道题

但

请注意 请注意 请注意 请注意 ！！
如果你的代码几乎毫无问题，并且前面几乎一半的点都过了
那么，有极大的可能你的代码是对的，只是：
“请注意程序运行过程中进行乘法运算时结果可能有溢出的风险。”
注意，有乘又有除的式子，一定要先除再乘！！

```cpp
#include<bits/stdc++.h>

using namespace std ;

long long a[ 111111 ] , b[ 111111 ] , n , m , x , y , z , ans , d , u ;

long long exgcd( long long a , long long b )
{
	
	if ( ! b )
	{
		
		x = 1ll , y = 0ll ;
		
		return a ;
		
	}
	
	long long d = exgcd( b , a % b ) ;
	
	long long z = x ;
	
	x = y , y = z - a / b * y ;
	
	return d ;
		
}

long long mul( long long a , long long b , long long mod)
{
	
    long long res = 0 ;
    
    while ( b > 0 )
    {
    	
        if ( b & 1 ) res = ( res + a ) % mod ;
        
        a = ( a + a ) % mod ;
		 
        b >>= 1 ;
        
    }
    
    return res ;
    
}

int main()
{
	
	scanf( "%lld" , &n ) ;
	
	for ( long long i = 1 ; i <= n ; i ++ ) scanf( "%lld%lld" , &a[ i ] , &b[ i ] ) ;
	
	m = a[ 1 ] , ans = b[ 1 ] ;
		
	for ( long long i = 2 ; i <= n ; i ++ ) 
	{
		
		u = ( b[ i ] - ans % a[ i ] + a[ i ] ) % a[ i ] ;
				
		d = exgcd( m , a[ i ] ) ;
		
		if ( u % d ) 
		{
			
			printf( "-1" ) ;
			
			return 0 ;
			
		}
		
		x = mul( x , u / d , a[ i ] / d ) ;	
		
		ans += x * m ;
				
		m = a[ i ] / d * m ;
		
		( ans += m ) %= m ;
			
	}
			
	( ans += m ) %= m ;
			
	printf( "%lld" , ans ) ;
	
	return 0 ;
	
}
```


---

