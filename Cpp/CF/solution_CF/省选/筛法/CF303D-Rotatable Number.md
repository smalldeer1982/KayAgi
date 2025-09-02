# Rotatable Number

## 题目描述

Bike is a smart boy who loves math very much. He invented a number called "Rotatable Number" inspired by $ 142857 $ .

As you can see, $ 142857 $ is a magic number because any of its rotatings can be got by multiplying that number by $ 1,2,...,6 $ (numbers from one to number's length). Rotating a number means putting its last several digit into first. For example, by rotating number $ 12345 $ you can obtain any numbers: $ 12345,51234,45123,34512,23451 $ . It's worth mentioning that leading-zeroes are allowed. So both $ 4500123 $ and $ 0123450 $ can be obtained by rotating $ 0012345 $ . You can see why $ 142857 $ satisfies the condition. All of the $ 6 $ equations are under base $ 10 $ .

- $ 142857·1=142857 $ ;
- $ 142857·2=285714 $ ;
- $ 142857·3=428571 $ ;
- $ 142857·4=571428 $ ;
- $ 142857·5=714285 $ ;
- $ 142857·6=857142 $ .

Now, Bike has a problem. He extends "Rotatable Number" under any base $ b $ . As is mentioned above, $ 142857 $ is a "Rotatable Number" under base $ 10 $ . Another example is $ 0011 $ under base 2. All of the $ 4 $ equations are under base $ 2 $ .

- $ 0011·1=0011 $ ;
- $ 0011·10=0110 $ ;
- $ 0011·11=1001 $ ;
- $ 0011·100=1100 $ .

So, he wants to find the largest $ b $ $ (1&lt;b&lt;x) $ so that there is a positive "Rotatable Number" (leading-zeroes allowed) of length $ n $ under base $ b $ .

Note that any time you multiply a rotatable number by numbers from 1 to its length you should get a rotating of that number.

## 样例 #1

### 输入

```
6 11
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 8
```

### 输出

```
-1
```

# 题解

## 作者：ACAね (赞：4)

#### 一些废话
*_嗯，这道题今天考试考了，写一篇题解祭奠一下。_*

昨天学了欧拉定理与欧拉函数，老师说不会考难题，于是我就刚这道题刚了2个小时，推了半天规律结果还是差了不少，不过代码和题解比较相似。但是结论有错误。(~~MMP~~我又不是欧拉，考场上推出原根定理？）

~~昨天学欧拉定理今天考原根，老师的良心呢~~

不管了。
# 正文
[老师给的题解原文(一堆易知)~~我太弱了~~](https://blog.csdn.net/wmdcstdio/article/details/45042353)

一看到题目142857，就想到了1/7.然后瞎猜应该和分数有关。

先在十进制下推，

假设我们有个循环数，比如142857.
令$x=0.14285714.... =(q/p) (gcd(p,q)==1)$

则
$x=0.142857142857……$
$2x=0.285714285714……$
$3x=0.428571428571……$
$4x=0.571428571428……$
$5x=0.714285714285……$
$6x=0.857142857142……$

$x=0.142857142857……$
$10x=1.428571428571……$
$100x=14.285714285714……$
$1000x=142.857142857142……$
$10000x=1428.571428571428……$
$100000x=14285.714285714285……$

因为x是一个无限纯循环小数，所以$gcd(10,p)=1$.

根据循环数的定义，他们的尾数相同。
所以，x是循环数$\Longleftrightarrow${$x$,$2x$,$3x$,...,$6x$}的小数部分与{$10^0x$,$10^1x$,...,$10^5x$}相同.
$\Longleftrightarrow${$q/p$,$2q/p$,$3q/p$,...$6q/p$}的小数部分与{$10^0q/p$,$10^1q/p$,...,$10^5q/p$}相同(均不考虑顺序)

$\because gcd(p,q)=1$

$\therefore$小数部分只由$mod\space p$的余数唯一确定。

故上式等价于{$q,2q,3q,...$}与{$10^0q,10^1q,10^2q,...$}在mod p意义下相同。

$\because gcd(p,q)=1$

必有$aq\equiv1(mod \space p)$

将上式同乘a,得到
{$1,2,3,4,5,6$}与{$10^0,10^1,...,10^5$}在mod p意义下相同。

显然{$1,10,...,10^5$}中有一个数模p余2.事实上它是100

(这里当然可以假设一个数推下去，但是结论是一样的，所以就直接未卜先知了)

且{$10^0,10^1,...,10^5$}与{$10^2,...,10^7$}在mod p意义下相同(循环数的性质)。

所以{$10^0,10^1,...,10^5$}与{$2*10^0,...,2*10^5$}在mod p意义下相同(循环数的性质)。

显然,{$1,2,3,4,5,6$}与{$2,4,6,8,10,12$}在mod p意义下相同。

$\therefore$ {$1,3,5$}与{$8,10,12$}在mod p意义下相同。

易知$p<8$

另一方面

显然有p>循环节长度。否则x*p将得到一个整数，不会循环下去。

$\therefore$ $p>6$

$\therefore$ $p=7$

上述论证在n≠6的时候仍然成立：p=循环节长度+1.

那么就有{$1,2,...,p-1$}和{$10^0,10^1,...,10^{p-2}$}在mod p意义下相同

$\therefore$ 那么就有{$2,...,p-1$}和{$10^1,...,10^{p-2}$}在mod p意义下相同

我们发现$10^1,...,10^{p-2}$中没有一个模p余1的数

即$1,...,p-2≠\phi(p)$

所以,p是质数，且10是p的原根

推广到b进制下，当且仅当p是质数且b是p的原根时，有循环数

这个时候我们就要掌握到一个求原根方法

求质数x的原根:
求出$x-1$所有不同的质因子$p_1,p_2...p_m$.

对于任何$a(2<=a<=x-1)$,判定a是否为x的原根，只需要检验$a^{(x-1)/p_1},a^{(x-1)/p_2},...,a^{(x-1)/p_m}$这m个数中，是否存在一个数$\bmod x$为1，若存在，a不是x的原根，否则就是x的原根。
对于合数，将x-1换成$\phi (x)$即可
___
证明：[原文](https://blog.csdn.net/dreamzuora/article/details/52744471)

假设存在一个$t<\phi(x)=x-1$使得$a^t = 1 (mod \space x)$  
  
那么由裴蜀定理，一定存在一组k,r使得$kt=(x-1)r+gcd(t,x-1)$  
  
而由欧拉定理有，$a^{x-1} = 1 \pmod {x}  $
  
于是$1 = a^{kt} = a^{xr-r+gcd(t,x-1)} = a^{gcd(t,x-1)}\pmod{x}  $
  
而$t<x-1$故$gcd(t,x-1)<x-1$  
  
又$gcd(t,x-1)|x-1 $于是$gcd(t,x-1)$必整除$(x-1)/p_1,(x-1)/p_2...(x-1)/p_m$其中至少一个，设其一为$(x-1)/p_i$  
  
那么$a^{(x-1)/pi} = (a^{gcd(t,x-1)})^s = 1^s = 1 (mod x)$
  
这与假设矛盾


___
所以只需要将小于x-1的b逐个判断是不是p的原根就行了。
使用快速幂时间复杂度为$\Theta(\sqrt{q}\log{q})$
但实际复杂度远远小于。~~过了就行~~

代码
```cpp
/*
@Date    : 2018-08-08 00:45:35
@Author  : Adscn
@Link    : https://www.luogu.org/blog/LLCSBlog/
*/
#include<bits/stdc++.h>
using namespace std;
#define IL inline
#define RG register
#define gi getint()
#define pi(k) putint(k)
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
IL int getint()
{
    RG int xi=0;
    RG char ch=gc;
    bool f=0;
    while(ch<'0'|ch>'9')ch=='-'?f=1:f,ch=gc;
    while(ch>='0'&ch<='9')xi=(xi<<1)+(xi<<3)+ch-48,ch=gc;
    return f?-xi:xi;
}
IL void putint(int k)
{
    if(k<0)k=-k,putchar('-');
    if(k>=10)putint(k/10);
    putchar(k%10+'0');
}
IL unsigned int LOG2(unsigned int x)
{
    unsigned int ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}
long long n,x;
const int MAX=5*1e6+1;
long long mod;
long long ksm(long long a,int b)
{
    long long ans=1,tmp=a;
    while(b)
    {
        if(b&1)ans=(ans*tmp)%mod;
        tmp=(tmp*tmp)%mod;
        b>>=1;
    }
    return ans;
}
IL bool checkp(long long p)
{
    if(p<2)return false;
    if(p==2||p==3)return 1;
    for(long long i=2;i*i<=p;i++)if(p%i==0)return false;
    return true;
}
IL bool check(long long k)
{
    if(k%mod==0)return false;
    for(long long i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            if(i<n&&ksm(k,i)==1)return false;
            if(i!=1&&ksm(k,n/i)==1)return false;
        }
    }
    return true;
}
int main(void)
{ 
//	File("number");
    cin>>n>>x;
//	getEuler();
    mod=n+1;
    if(!checkp(mod))return printf("-1")&0;
    for(int i=x-1;i>=2;i--)if(check(i))return printf("%d",i)&0;
    printf("-1");
    return 0;
}
```

---

## 作者：lzytag (赞：2)

### $2600$ 困难 MO 题
在一切开始前，我们必须知道一个在 $b$ 进制下长度为 $n$ 的正循环数 $x$ 具有何种性质。

我们首先发现，我们记 $b^n-1$ 为 $lim$，将 $x$ 循环位移 $y$ 位所得的数就是 $b^y \times x\bmod lim$，于是由题意可得，循环数具有的性质就是
$$\{x,2\times x,\dots,n\times x\} = \{b^0\times x\bmod lim,b^1\times x\bmod lim,\dots,b^{n-1}\times x\bmod lim\}$$

我们考虑消除 $x$ 对式子的影响，对两侧同时除以 $x$。但左侧有对 $lim$ 的取模，就会产生一个问题，那就是 $x$ 是不与 $lim$ 互质的。我们先记 $\frac{lim}{\gcd(lim,x)}$ 为 $T$。得到：

$$\{1,2,\dots,n\} = \{b^0\bmod T,b^1\bmod T,\dots,b^{n-1} \bmod T\}$$

我们根据 $b = 10,n = 6,x = 142857$ 的特例，猜测 $T = n+1$，接下来考虑证明。

首先，$n\times x < lim$，所以 $\gcd(x,lim)\le x<\frac{lim}{n}$，所以 $T = \frac{lim}{\gcd(x,lim)} > n$

因为 $lim = b^n-1$，当然也满足 $b^n\equiv 1\mod T$。所以我们将右侧所有数全部乘上一个 $b$，右侧的集合显然是不变的。又因为一定有一个 $b^i\equiv 2\mod T$。所以我们可以把右侧全部乘上一个 $b^i$，也就是 $2$。最后得到：
$$\begin{aligned}\{1,2,\dots,n\} &= \{2\times b^0\bmod T,2\times b^1\bmod T,\dots,2\times b^{n-1} \bmod T\}\\ &= \{2\bmod T,4\bmod T,\dots,2\times n\bmod T\}\end{aligned}$$
若 $n = 2*m+1$，消去相同项，得 $\{1,3,\dots,n\}$ = $\{n+1\bmod T,n+3\bmod T,\dots,2\times n\bmod T\}$。

考虑到 $1 \le n+1\bmod T < n+1$，所以 $T < n+1$ 与上文矛盾

若 $n = 2*m$，消去相同项得到 $\{1,3,\dots,n-1\} = \{n+2\bmod T,n+4\bmod T,\dots,2\times n\bmod T\}$。

考虑到 $1\le n+2\bmod T \le n-1$，所以 $T\le n+1$。所以 $T = n+1$。

证毕，所以：

$$\{1,2,\dots,T-1\} = \{b^0\bmod T,b^1\bmod T,\dots,b^{T-2}\bmod T\}$$

也就是说，$T$ 为素数，且 $b$ 为 $T$ 的一个原根。这时，有 $x = \frac{b^n-1}{n+1}$ 满足初始的定义。根据费马小定理，这显然是可以整除的。

实现上，我们只要从大到小枚举 $b$ 并判定是否为原根即可，找到一个原根就直接输出。

---

## 作者：金珂拉 (赞：1)

## 分析证明

首先我们先设这个整数是 $\overline{a_1a_2a_3...a_n}$ ，那么我们不妨设一个有理数 $ \frac{q}{p}=\overline{0.a_1a_2a_3...a_na_1a_2a_3...a_na_1a_2a_3...a_n...} $ ，其中 $\operatorname{gcd}(p,q)=1$

我们设 $\operatorname{float}(x)$ 表示 $x$ 的小数部分。

根据循环数的定义，有

$\{\operatorname{float}(\frac{q}{p}),\operatorname{float}(\frac{2q}{p}),...,\operatorname{float}(\frac{nq}{p})\} =\{\operatorname{float}(\frac{q}{p}),\operatorname{float}(\frac{bq}{p}),...,\operatorname{float}(\frac{b^{n-2}q}{p})\}$

显然 $\operatorname{float}(\frac{a}{p})=\operatorname{float}(\frac{b}{p})$  等价于 $\frac{a}{p}-\frac{b}{p} \in Z$ 等价于 $ a \equiv b\mod p$

又因为 $\operatorname{gcd}(p,q)=1$，所以 $\{1,2,...,n\} =\{1,b,...,b^{n-2}\}$ 。

易得 $p \gt n$。

因此 $\exists i,b^i=2$。

容易发现的是，实际上 $\forall i,\{1,2,...,n\} =\{b^i,b^{i+1},...,b^{i+n-2}\}$。

根据以上两行我们得到 $\exists i,\{1,2,...,n\}=\{b^i,b^{i+1},...,b^{i+n-2}\}=\{2,2b,...,2b^{n-2}\}=\{2,4,...,2n\}$。

接着我们分类讨论

首先,$n=2m+1$ 时，去掉相同项之后可得 $\{1,3,...,n\}=\{2m+2,2m+4,...,2n\}$

于是就有了 $0\lt n+1\mod p\le n $  ,那么显然 $p\lt n+1$ ，和之前矛盾，舍去。

再看 $n=2m$ 时，同理可得 $\{1,3,...,n-1\}=\{2m+2,2m+4,...,4m\}$

于是就有了 $0\lt n+2\mod p\le n-1 $  ,那么显然 $p\lt n+2$

于是 $p=n+1 $ 。

而此时显然有 $\{b^1,b^2,...,b^{p-1}\}=\{1,2,...,p-1\}$，因此 $b$ 是 $p$ 的原根。

又， $\{b^1,b^2,...,b^{p-1}\}=\{1,2,...,p-1\}$ ，因此p是质数。

故我们需要求出的就是 $x$ 内最大的原根。若 $p$ 不是质数就直接输出 $-1$。

从 $x$  开始倒着枚举并且一个个判断过去，不难证明当 $p$ 有原根的时候最多枚举 $p$ 次。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[6000003],vis[6000003];
int cnt=0;
void find(int n)
{
	prime[1]=0;
    for (int i=2;i<=n;++i)
    {
        if (!vis[i]) prime[++cnt]=i; 
        for (int j=1;j<=cnt && i*prime[j]<=n;++j)
        {
        	vis[i*prime[j]]=1;
            if (i%prime[j]==0) break;
        }
    }
    return; 
}
int n,x,p,a[6000003],tot=0;
void get(int x){
	for(int i=1;i<=cnt;i++) if(!(x%prime[i])) a[++tot]=prime[i];
}
long long qpow(long long a, long long n, long long m)
{
    long long ans = 1;
    while(n){
    if(n&1){ans=(ans * a) % m;}
    a=(a*a)%m;
    n>>=1;
    }
    return ans;
}
bool check(long long x){
	for(int i=1;i<=tot;i++) {
	if(qpow(x,(p-1)/a[i],p)==1) 
	return 0;	
	}
	return 1;
} 
int main(){
	int n,x;
	cin>>n>>x; 
	p=n+1;
	if((qpow(2,p-1,p)!=1 || qpow(3,p-1,p)!=1 || qpow(5,p-1,p)!=1) && p!=2 && p!=3 && p!=5){
	printf("-1");
	return 0;
	}
	find(p);
	get(p-1);
	for(int i=x-1;i>1;i--)
	if(check(i)){
	printf("%d",i);
	return 0;
	}		
	printf("%d",-1);
} 
```


---

