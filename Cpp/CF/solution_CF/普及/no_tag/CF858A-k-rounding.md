# k-rounding

## 题目描述

给定一个正整数n， 要求求出一个最小的正整数，使得其末尾至少有k个连续的0，并且为n的倍数。

## 样例 #1

### 输入

```
375 4
```

### 输出

```
30000
```

## 样例 #2

### 输入

```
10000 1
```

### 输出

```
10000
```

## 样例 #3

### 输入

```
38101 0
```

### 输出

```
38101
```

## 样例 #4

### 输入

```
123456789 8
```

### 输出

```
12345678900000000
```

# 题解

## 作者：SqrtSecond (赞：6)

本题思路很多，我给大家提供三种。

------------

# 第一种

依次正序枚举$n$的倍数。

假设这个数为$i$，

此时如果$i$的末尾有$k$个$0$（即$i$能整除于$10^k$），就直接输出。

容易知道此时$i$为最小答案。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a;//记得开long long
int main()
{
	cin>>n>>k;
	a=1;
	while(k--)a*=10;//算出10的k次方
	for(long long i=n;i<=n*a;i+=n)
	{
		if(i%a==0)
		{
			cout<<i;
			return 0;
		}
	}
}
```

------------

# 第二种

我们可以知道$10=2\times5$

即$10^k=2^k\times5^k$

所以一开始算出还需要的$2$和$5$的数量，也就是$k$

然后减去$n$中有多少$2$和$5$的因数

最后再在**原来的**$n$上乘即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,s,t,ans; 
int main()
{
	cin>>n>>k;
	s=t=k;//还需要的2和5的个数 
	ans=n;//存储原来的n 
	while(n%2==0)
	{
		if(s==0)break;//如果已经不需要了就退出 
		s--;//个数减一 
		n/=2;
	}
	while(n%5==0)
	{
		if(t==0)break;
		n/=5;
		t--;
	}
	while(s--)ans*=2;
	while(t--)ans*=5;
	cout<<ans;
}
```


------------

# 第三种

本题让我们求$n$的倍数中有$k$个$0$的最小数

实际上就是求$\text{lcm}(n,10^k)$

即$\frac{n\times10^k}{\gcd(n,10^k)}$

而$\gcd$可以用欧几里得算法求得。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a=1;
long long gcd(long long a,long long b)
{
	return a%b? gcd(b,a%b):b;
}
int main()
{
	cin>>n>>k;
	while(k--)a*=10;
	cout<<n*a/gcd(n,a);
}
```


---

## 作者：fzj2007 (赞：1)

## 再来一发~~

# 第一步 读题

> 给定一个正整数 $n$， 要求求出一个最小的正整数，使得其末尾至少有 $k$ 个连续的 $0$，并且为 $n$ 的倍数。

现在给出两个思路：

## 思路一：寻找原本含有的5和2的个数。

我们可以发现 $10 ^ k = 5^k \times 2^k$。

我们可以直接寻找 $5$ 和 $2$ 的个数，然后把不够 $k$ 个的补出来，够了的做一个处理就可以了。

## 思路二：数论推导

我们需要最小的一个数同时拥有因数 $10 ^ k$ 和 $n$，由最小可以想到最小公倍数。那么我们要求的数就是 $\operatorname{lcm}(10^k,n)$。

# 第二步 lcm讲解

我们要如何求 $\operatorname{lcm}(10^k,n)$ 呢？我们可以先求出来  $\gcd(10^k,n)$，我使用[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675?fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95&fromid=4625352&fr=aladdin#3)最大公因数。即 $\gcd(10^k,n) = \gcd(n,10^k \bmod n)$，然后一遍一遍地运算下去，直到后面一项为0，返回前一项就是结果。程序：

```
long long gcd(long long x,long long y){
	if(y==0) return x;
   return gcd(y,x%y);
}
```
可以压行为
```
long long gcd(long long x,long long y){
   return y==0?x:gcd(y,x%y);//三目运算符，如果条件（问号前面部分）成立就执行第二部分（问号后面部分），否则执行第三部分（冒号后面部分）。
}
```
# 第三步 代码

终于到了代码部分了......这里提供上面两种做法。

快速幂可以在[这里](https://www.luogu.com.cn/problem/P1226)练习。

快速读入来[这里](https://www.luogu.com.cn/blog/encore/io-you-hua-nei-suo-shi)学习。

## 第一种做法

```
#include<bits/stdc++.h>
using namespace std; 
using std::cin;
using std::cout;
using std::endl;
namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::put;
using OUT::putc;
using OUT::putstr;
#define ll long long
ll n,m,f,t,k;//n,m读入，f存储因数5，t存储因数2，k用来存n
inline ll power(ll x,ll y){//快速幂板子
	ll re=1;
	while(y){
		if(y&1) re*=x;
		x*=x;
		y>>=1;
	}
	return re;
}
int main(int argc, char const *argv[]){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    read(n,m);//读入
    k=n;//复制n
    while(!(k&1)) t++,k>>=1;//来寻找2的个数
    while(!(k%5)) f++,k/=5; //寻找5的个数
    put((t>=m?1:power(2,m-t))*(f>=m?1:power(5,m-f))*n);//如果2的个数或5的个数超过应该有的，那么就记为1即可。否则记为剩余的
	 return 0;
}
```

## 第二种做法

```
#include<bits/stdc++.h>
using namespace std; 
using std::cin;
using std::cout;
using std::endl;
namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::put;
using OUT::putc;
using OUT::putstr;
#define ll long long
ll n,m,f,t,k;//同代码1
inline ll power(ll x,ll y){//快速幂
	ll re=1;
	while(y){
		if(y&1) re*=x;
		x*=x;
		y>>=1;
	}
	return re;
}
ll gcd(ll x,ll y){//最大公因数
	return y==0?x:gcd(y,x%y);
}
inline ll lcm(ll x,ll y){//最小公倍数
	return x/gcd(x,y)*y;
}
int main(int argc, char const *argv[]){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    read(n,m);//读入
    put(lcm(n,power(10,m)));//我们可以直接输出
	return 0;
}
```
结果......

发现代码1的速度为 `1.3ms`，代码2的速度为`1.39ms`，第一个比第二个快。

# 第四步 宣传

如果有帮助，请点个赞，谢谢！（撰文不易，dalao勿喷！）如果发现我的讲解有bug，请及时指出！

[我的主页](https://www.luogu.com.cn/user/172370)和[博客](https://www.luogu.com.cn/blog/fzj2007/)，欢迎关注！

---

## 作者：ttq012 (赞：0)

这个数需要满足末尾有 $k$ 个 $0$，那么我们就先构造一个最小的有 $k$ 个 $0$ 的数，也就是 $10^k$。

然后这一个数还要满足能被 $n$ 整除，那么将上面的答案和 $n$ 取一个 $\text {lcm}$ 就可以了。

答案就是 $\text{lcm}(10^k, n)$。

注意开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long lcm(long long a, long long b)
{
	return 1LL * a * b / __gcd(a, b);
}

int main(int argc, char *argv[])
{
	long long n, k;
	cin>> n >> k;
	long long m = pow(10, k);
	printf("%lld\n", lcm(n, m));
	return 0;
}

```

---

## 作者：零殇 (赞：0)

#### 题意

给定一个 $n$ 和 $k$ ，求最小的末尾有 $k$ 个 $0$ 的 $n$ 的倍数。

#### 思路

显然，用暴力枚举 $n$ 的倍数是很不明智的选择。

我们知道， $(a×b)^k=a^k×b^k$ 。

那么我们把 $10$ 分解质因数，可以得到

$10=2×5$

转化后，就能得到

$10^k=2^k×5^k$

因此我们只要对 $n$ 分解质因数，看看有几个 $2$ 和 $5$ ，再乘上还差的就好了。

但是这不是最简单的办法。

后面有 $k$ 个 $0$ ，就代表它是 $10^k$ 次方的倍数。

那么，我们只要求它们的最小公倍数就好了。

注意开`long long`

上代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,k;
long long gcd(long long x,long long y) {
	if(y==0) return x;
   return gcd(y,x%y);
}
int power(long long a,long long b) {
	long long ans=1;
	for(;b;b>>=1) {
		if(b&1)
		ans=(long long)ans*a;
		a=(long long)a*a;
	}
	return ans;
}
long long lcm(long long x,long long y) {
	if(x==0)
		return y;
	if(y==0)
		return x;
	return x/gcd(x,y)*y;
}
int main() {
	scanf("%lld%lld",&n,&k);
	k=power(10,k);
	printf("%lld\n",lcm(n,k));
	return 0;
}
```

完结撒花~

---

## 作者：Iron_Heart (赞：0)

## 思路

很容易想到，“末尾至少有 $k$ 个连续的 $0$”，就代表答案是 $10^k$ 的倍数。

这样问题就变得很简单了，只需求 $n$ 与 $10^k$ 的最小公倍数即可。

$x$ 和 $y$ 的最小公倍数就等于 $x \times y \div \gcd(x,y)$。

**注意：不开 long long 见祖宗。**

## 代码

```cpp
#include <cstdio>
typedef long long ll;
ll n, k;

ll pow(ll a, ll b) {
    ll res = 1;
    while (b--) {
        res *= a;
    }
    return res;
}

ll gcd(ll a, ll b) {
    if (!b) {
        return a;
    }
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

int main() {
    scanf("%lld%lld", &n, &k);
    printf("%lld", lcm(n, pow(10, k)));
    return 0;
}
```


---

## 作者：Cocoly1990 (赞：0)

## 前置芝士

$lcm$：最小公倍数，$gcd$：最大公约数

$\LARGE lcm(a,b)= \frac{a\times b}{gcd(a,b)}$

证明：

设：
 $$ a=m \times k,b=n\times k $$
 $$gcd(m,n)=1$$
则
 $$k=gcd(a,b)$$
又
 $$lcm(a,b)=m\times n \times k$$
 $$a\times b=m\times n \times k^2$$
易得
$$ lcm(a,b)= \frac{a\times b}{gcd(a,b)}$$
## 思路
`其末尾至少有k个连续的0` 可以认为这个数是$10^k$的倍数

所以这题只需要求$lcm(n,10^k)$

又$\large lcm(n,10^k)=\frac{n\times 10^k}{gcd(n,10^k)}$

$gcd$部分用内置函数``__gcd(a,b)``处理即可，当然手写辗转相除也没问题

$10^k$部分用函数``pow(a,b)``或者快速幂搞都可以，最后带进公式算一下就好

记得开$long$  $long$

代码丑，不贴


---

## 作者：tobie (赞：0)

首先，我们看题。

这道题要你求出一个数。

这个数末尾要有 $k$ 个 $0$ ，所以这个数得是 $10^k$ 的倍数。

这个数又得是 $n$ 的倍数。

所以这个数就是 $n$ 和 $10^k$ 的公倍数，即 $\operatorname{lcm}\left(n,10^k\right)=\dfrac{n\times10^k}{\gcd\left(n,10^k\right)}$

所以我们就可以打出代码了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long n,k;
long long qpow(long long x,long long y)//计算10^k
{
	long long ans=1;
	for(int i=1;i<=y;i++)
	ans*=x;
	return ans;
}
long long gcd(long long x,long long y)//计算gcd
{
	if(y==0) return x;
	return gcd(y,x%y);
}
int main()
{
	scanf("%lld%lld",&n,&k);
	printf("%lld",n*qpow(10ll,k)/gcd(n,qpow(10ll,k)));//刚才退的柿子
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

一句话题意：求出 $n$ 的倍数中，结尾有 $k$ 个 $0$ 的最小数。

## 解法

容易发现，结尾有 $k$ 个 $0$，也就意味着他是 $10^k$ 的倍数。

同时他又是 $n$ 的倍数，并且他要你求最小的——最小的，是公倍数……所以题目所求为：

$$\text{lcm}(n,10^k)$$

显然我们要把他转换成 $\gcd$ 来求，这就很简单了，~~为了防止题解过短~~，我们来说明一下 $\text{lcm}$ 和 $\gcd$ 的转换过程。

设 $x=\gcd(a,b)$，$y=\text{lcm}(a,b)$。

再设 $a=m\cdot x$，$b=n\cdot x$，因为 $x$ 是 $a$ 和 $b$ 的最大公因数，所以 $m$ 与 $n$ 互质。

那么我们就知道两数最小公倍数是互质的因子乘上公共的因子（也就是说公因数只乘一遍），即 $y=m\cdot n\cdot x$。

那么 $x\cdot y=m\cdot n\cdot x^2=mx\cdot nx=a\cdot b$

那么我们就知道 $\gcd(a,b)\cdot\text{lcm}(a,b)=a\cdot b$，简单的转换可以得到求解 $\text{lcm}$ 的做法：

$$\text{lcm}(a,b)=\dfrac{a\cdot b}{\gcd(a,b)}$$

那么我们只需要求：

$$\dfrac{n\cdot 10^k}{\gcd(n,10^k)}$$

首要问题，$\gcd$ 怎么求？什么，你说一个个试？太慢了太慢了（ $O(\min(a,b))$ ）我们知道：

$$\gcd(a,b)=\gcd(b,a\bmod b)$$

这么求就行力，复杂度是 $O(\log n)$ 的。


$n,k$ 很容易得到，那么，我们该怎么求出这个 $10^k$ 呢？

显然，暴力乘绝对没问题，但是为了更低的复杂度，我们可以使用 $O(\log k)$ 的快速幂，其核心思想如下：

$$10^k=10^{k\div 2}\times 10^{k\div 2}$$

如果 $k$ 是奇数就是：

$$10^k=10^{s}\times 10^{t}\quad s+t=k\quad s=t-1$$

我们就可以从小到大，进行乘法，达到了缩减规模的目的，虽然在此题实操中并无优化作用，但是他的复杂度好看。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,n;
int ksm(int base,int power){
	int ans=1;
	while(power){
		if(power&1)ans=ans*base;
		base=base*base;
		power>>=1;
	}return ans;
}signed main(){
    cin>>n>>k;
	int kk=ksm(10,k);
	cout<<(kk*n)/__gcd(kk,n)<<endl;
	return 0;
}
```

其中的 `__gcd` 是内置的求 $\gcd$ 函数，联赛不能用但是 OJ 上可以。

---

## 作者：zilingheimei (赞：0)

~~又是一个不知道怎么上黄的题目。~~

先看题目：

[CF858A k-rounding](https://www.luogu.com.cn/problem/CF858A)

一看数据范围 1 $\leq$ $n$ $\leq$ $10^9$ ，0 $\leq$ $k$ $\leq$ 8 ，也就是可以枚举题目要的答案。

------------

思路如下：

- 首先先输入一个 $n$,一个 $k$ ，然后将 $10^k$ 求出，记为 $x$ （因为问后面跟几个 $0$ ，将枚举的答案直接 $\bmod$ $x$ 看是不是为 $0$ 就知道了）：
```cpp
cin>>n>>k;//得用longlong。
for(int i=1;i<=k;i++){
	x*=10;
}
```
可以用循环求也可以直接用 $\operatorname{pow}$ 来求。

- 然后从$n$开始搜，一直搜到 $n$ $\cdot$ $x$ ，搜到可以被 $x$ 整除立刻结束，因为求最小：
```cpp
for(long long i=n;i<=n*x;i+=n){//注意除了k可以用int,其他都得用long long。
	if(i%x==0){
		cout<<i;
		return 0;
	}	
}
```

------------

上面主要代码都有了，总代码就不放了（

---

## 作者：Arghariza (赞：0)

不妨假设 $n=2^p\,\cdot\,5^q\,\cdot\,x=10^{min(p,q)}\,\cdot\,2^{p-min(p,q)}\,\cdot\,5^{q - min(p,q)}\,\cdot\,x$ 

因为我们需要 $k$ 个 $10$ ，所以需要 $2^k$ 以及 $5^k$ 。

所以我们还需要 $2^{k-p}\,\cdot\,5^{k-q}$ 。

那么结果就是 $n \,\cdot\, 2^{k-p}\,\cdot\,5^{k-q}$ ，当然，如果 $p,q$ 比 $k$ 还大就不需要乘了。

然后注意要开 $long\,long$，手写快速幂（第一次因为用 $pow$ 无情地 $\mathtt{\color{red}WA}$ 了 $\mathtt{QAQ}$ ）。

剩下的可以看注释：

```cpp
#include <bits/stdc++.h>
#define int long long// 开long long。
using namespace std;

int n, tn, cnt2, cnt5, k;// cnt2为2的个数，cnt5为5的个数。

int ksm(int p, int q) {// 手写快速幂。
	int res = 1;
	while (q) {
		if (q & 1) res *= p;
		p *= p;
		q >>= 1;
	}
	return res;
}

signed main() {
	scanf("%lld%lld", &n, &k);
	tn = n;// 要先记录一下，否则不好还原
	while (n % 2 == 0) cnt2++, n /= 2;// 统计2的个数。
	while (n % 5 == 0) cnt5++, n /= 5;// 统计5的个数。
	n = tn;// 还原n
	printf("%lld", n * ksm(2, cnt2 >= k ? 0 : (k - cnt2)) * ksm(5, cnt5 >= k ? 0 : (k - cnt5)));// 用了三目运算符，如果2或5的个数大于k，直接不用乘（即乘上2或5的0次方）即可。
	return 0;
}
```

---

## 作者：ShineEternal (赞：0)

首先$n\times 10^k$是一定可以的。

然后发现把他们可以除以$gcd(n,10^k)$，条件还是满足的

```cpp
#include<cstdio>
using namespace std;
long long gcd(long long x,long long y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	long long n,k;
	long long m=1;
	scanf("%lld%lld",&n,&k);
	while(k--)m=m*10;
	printf("%lld\n",n*m/gcd(n,m));
	return 0;
}
```

---

## 作者：da32s1da (赞：0)

考虑$10^k=2^k\times 5^k$，设$n=m\times 2^p\times 5^q$。

则答案是$$m\times2^{k+p-min(k,p)} \times5^{k+q-min(k,q)}=\frac{n\times10^k}{\gcd(n,10^k)}$$

```
#include<cstdio>
int n,k,_10;
int gcd(int u,int v){return v?gcd(v,u%v):u;}
int main(){
	scanf("%d%d",&n,&k);
	_10=1;
	for(int i=1;i<=k;i++)_10=_10*10ll;
	int Gcd=gcd(_10,n);
	printf("%I64d\n",1ll*n*_10/Gcd);
}
```

---

