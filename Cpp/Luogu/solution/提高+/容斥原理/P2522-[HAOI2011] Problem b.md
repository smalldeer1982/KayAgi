# [HAOI2011] Problem b

## 题目描述

对于给出的 $n$ 个询问，每次求有多少个数对 $(x,y)$，满足 $a \le x \le b$，$c \le y \le d$，且 $\gcd(x,y) = k$，$\gcd(x,y)$ 函数为 $x$ 和 $y$ 的最大公约数。

## 说明/提示

对于 $100\%$ 的数据满足：$1 \le n,k \le 5 \times 10^4$，$1 \le a \le b \le 5 \times 10^4$，$1 \le c \le d \le 5 \times 10^4$。

## 样例 #1

### 输入

```
2
2 5 1 5 1
1 5 1 5 2```

### 输出

```
14
3```

# 题解

## 作者：pengym (赞：54)

我顺便来安利一下自己的博客[peng-ym's blog](http://www.cnblogs.com/peng-ym/)里面也有[莫比乌斯反演](http://www.cnblogs.com/peng-ym/p/8647856.html)与[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)的介绍，不知道的可以看一看哦！
## 题目描述
- 对于给出的n个询问，每次求有多少个数对(x,y)，满足a≤x≤b，c≤y≤d，且gcd(x,y) = k，gcd(x,y)函数为x和y的最大公约数。

## 输入输出格式
- 输入格式：
第一行一个整数n，接下来n行每行五个整数，分别表示a、b、c、d、k
- 输出格式：
共n行，每行一个整数表示满足要求的数对(x,y)的个数

## 解题思路
- 这个题要求的其实就是:$Ans=\sum_{i=a}^{b}\sum_{j=c}^{d}[gcd(i,j)=k]$
- 如果做过一道叫:[[POI2007]ZAP-Queries](http://www.cnblogs.com/peng-ym/p/8660937.html )的题，那么这题就显得非常的简单了。因为那道题就是这道题的一个特殊情况$(a=1,c=d)$
- 我们可以发现本题所算的$a$~$b$,$c$~$d$的答案，实质上由一个简单的容斥就可以转换成:
$$Ans((1,b),(1,d))-Ans((1,b),(1,c-1))-Ans((1,a-1),(1,d))+Ans((1,a-1),(1,c-1))$$
- 也就是一种类似于前缀和的容斥。具体的原因，其实把$\sum$随便手写几项，就可以发现这一定是正确的。
- 至于如何求$1$~$n$,$1$~$m$，就按照那道题化简一下式子就可以了。
- 我们设：
$$f(k)=\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=k]$$
$$F(n)=\sum_{n|k}f(k)=\lfloor\frac{a}{n}\rfloor\lfloor\frac{b}{n}\rfloor$$
则可以由莫比乌斯反演可以推出：
$$f(n)=\sum_{n|k}\mu(\lfloor\frac{k}{n}\rfloor)F(k)$$
- **(PS:如果不知道为什么要设这两个函数，可以点开我上面放的链接)**
- 设完这两个函数之后，我们便惊喜的发现，$Ans=f(d)$
- 于是就直接开始推答案：
$$Ans=\sum_{d|k}\mu(\lfloor\frac{k}{d}\rfloor)F(k)$$
枚举$\lfloor\frac{k}{d}\rfloor$设为$t$
$$Ans=\sum_{t=1}^{min(a,b)}\mu(t)\lfloor\frac{a}{td}\rfloor\lfloor\frac{b}{td}\rfloor$$
这时候，这个式子已经可以做到$O(n)$的时间复杂度了，但是因为有多组数据，所以我们再用一下**[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)**，这式子就可以做到$O(\sqrt{n})$了。
- 我们只需要写一个这样的函数，每次询问调用四遍就可以了。

## 下附代码:

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define N 60010
using namespace std;
inline void read(int &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;	
}
bool vis[N];
int prim[N],mu[N],sum[N],cnt,k;
void get_mu(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]){mu[i]=-1;prim[++cnt]=i;}
        for(int j=1;j<=cnt&&i*prim[j]<=n;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+mu[i];
}
long long calc(int a,int b)
{
    static int max_rep;
    static long long ans;
    max_rep=min(a,b);ans=0;
    for(int l=1,r;l<=max_rep;l=r+1)
    {
        r=min(a/(a/l),b/(b/l));
        ans+=(1ll*a/(1ll*l*k))*(1ll*b/(1ll*l*k))*(sum[r]-sum[l-1]);
    }
    return ans;
}
int main()
{
//	freopen("P3455.in","r",stdin);
//	freopen("P3455.out","w",stdout);
    int t;
    read(t);
    get_mu(50000);
    while(t--)
    {
        static int a,b,c,d;
        read(a);read(b);read(c);read(d);read(k);
        printf("%lld\n",calc(b,d)-calc(b,c-1)-calc(a-1,d)+calc(a-1,c-1));
    }
    return 0;
}
```

---

## 作者：lukelin (赞：19)

**先安利我的博客:**
1. [莫比乌斯反演1](https://www.cnblogs.com/linzhengmin/p/10994520.html) 定理  
2. [莫比乌斯反演2](https://www.cnblogs.com/linzhengmin/p/11046230.html) 证明  
3. [莫比乌斯反演3](https://www.cnblogs.com/linzhengmin/p/11060871.html) 技巧  

&ensp;&ensp;&ensp;[整除分块](https://www.cnblogs.com/linzhengmin/p/11061244.html) 算法介绍

**前置技巧:**  
莫比乌斯反演，莫比乌斯函数线性筛，整除分块，简单容斥  
**首先我们要会这样一道题:**  
计算$1 \leq x \leq a$，$1 \leq y \leq b$，$gcd(x,y)=d$  
我先放一个上面那题的题解：  
题目要我们求
$$\sum_{i=1}^a\sum_{j=1}^b[gcd(i,j)=d]$$
按照[套路1](https://www.cnblogs.com/linzhengmin/p/11060871.html)，我们将其同时除以d转换为
$$\sum_{i=1}^{\lfloor\frac{a}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{b}{d}\rfloor}[gcd(i,j)=1]$$
按照[技巧1](https://www.cnblogs.com/linzhengmin/p/11060871.html)，我们将其变换为
$$\sum_{i=1}^{\lfloor\frac{a}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{b}{d}\rfloor}\sum_{x|gcd(i,j)}\mu(x)$$
按照[技巧3](https://www.cnblogs.com/linzhengmin/p/11060871.html)，我们将其变换为
$$\sum_{i=1}^{\lfloor\frac{a}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{b}{d}\rfloor}\sum_{x=1}^{\lfloor\frac{a}{d}\rfloor}\mu(x)\times[x|gcd(i,j)]$$
我们发现要满足$d|gcd(i,j)$，我们的i，j必须是d的倍数
然后我们可以开心地去掉两个$\sum$
$$\sum_{x=1}^{\lfloor\frac{a}{d}\rfloor}\mu(x)\times\lfloor\frac{a}{xd}\rfloor\lfloor\frac{b}{xd}\rfloor$$
至此化简结束，我们求出[$\mu$函数](https://www.cnblogs.com/linzhengmin/p/10994520.html)的前缀和  
然后我们[整除分块](https://www.cnblogs.com/linzhengmin/p/11061244.html)，解决问题  
**好了，接下来我们回到本题**  
然后发现这题就是那道题加一个容斥原理  
我们要求的答案就是$ans(b,d)-ans(b,c-1)-ans(a-1,d)+ans(a-1,c-1)$  
~~小学生都会证啊~~  
于是愉快的AC了  

**放一个代码**
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
#define MAXNUM 50005

int mu[MAXNUM], is_not_prime[MAXNUM], primes[MAXNUM / 10], prime_num;
// prefix
ll qzh[MAXNUM];

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

void init(){
    mu[1] = 1; is_not_prime[0] = is_not_prime[1] = 1;
    for (int i = 2; i <= MAXNUM; ++i){
        if (!is_not_prime[i]) mu[primes[++prime_num] = i] = -1;
        for (int j = 1; j <= prime_num && primes[j] * i <= MAXNUM; ++j){
            is_not_prime[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
            else
                mu[primes[j] * i] = -mu[i];
        }
    }
    for (int i = 1; i <= MAXNUM; ++i)
        qzh[i] = qzh[i - 1] + mu[i];
}

ll solve(int n, int m, int d){
	if (n == 0 || m == 0) return 0;
	ll ans = 0;
	n /= d, m /= d;
    if (n > m) n ^= m ^= n ^= m; ans = 0;
    for (int l = 1, r; l <= n; l = r + 1){
        r = std::min(n / (n / l), m / (m / l));
        ans += (ll)(qzh[r] - qzh[l - 1]) * (n / l) * (m / l);
    }
	return ans;
}

int main(){
    init();
    int T = read(), a, b, n, m, d; ll ans;
    while (T--){
        a = read(), n = read(), b = read(), m = read(), d = read();
        ans = solve(n, m, d) - solve(n, b - 1, d) - solve(a - 1, m, d) + solve(a - 1, b - 1, d);
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Adove (赞：18)

我来提供一下这题的优化方案

首先是莫比乌斯反演内容

$$f(x)=\sum_{i=a}^b \sum_{j=c}^d [(i,j)=x] $$

$$F(x)=\sum_{i=a}^b \sum_{j=c}^d [x|(i,j)]=(\lfloor \frac{b}{x} \rfloor - \lfloor \frac{a-1}{x} \rfloor)(\lfloor \frac{d}{x} \rfloor - \lfloor \frac{c-1}{x} \rfloor)$$

$$F(x)=\sum_{x|d} f(d)$$

$$f(x)=\sum_{x|d} \mu(\frac{d}{x}) F(d)$$

我们可以用整除分块优化，但没必要用分块计算4遍

只需要分三段求解就可以了

$$a \leq b,c \leq d$$

令$$a \leq c$$

那么需要求解的三段区间为：

$$[1,\lfloor \frac{a-1}{x} \rfloor]$$

$$(\lfloor \frac{a-1}{x} \rfloor,min(\lfloor \frac{c-1}{x} \rfloor,\lfloor \frac{b}{x} \rfloor)]$$

$$(min(\lfloor \frac{c-1}{x} \rfloor,\lfloor \frac{b}{x} \rfloor),min(\lfloor \frac{d}{x} \rfloor,\lfloor \frac{b}{x} \rfloor)]$$

整除分块优化可做到根号复杂度，且此算法常数是其他题解容斥作法的一半

```cpp
#include<cstdio>
#include<bitset>
#include<algorithm>
using namespace std;

const int MAXN=5e4+5;

int T,x,a,b,c,d;
long long p[MAXN],mu[MAXN],lis[MAXN];
long long sum;
bitset<MAXN> bist;

int main()
{
	mu[1]=lis[1]=1;scanf("%d",&T);
	for(int i=2;i<=MAXN-5;++i){
		if(!bist[i]) p[++p[0]]=i,mu[i]=-1;
		lis[i]=lis[i-1]+mu[i];
		for(int j=1;j<=p[0]&&i*p[j]<=MAXN-5;++j){
			bist[i*p[j]]=1;
			if(i%p[j]) mu[i*p[j]]=-mu[i];
			else {mu[i*p[j]]=0;break;}
		}
	}while(T--){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&x);
		a=(a-1)/x;b/=x;c=(c-1)/x;d/=x;sum=0;
		if(a>c){swap(a,c);swap(b,d);}
		int l=1,r;
		for(;l<=a;l=r+1){
			int ra=a/(a/l),rb=b/(b/l),rc=c/(c/l),rd=d/(d/l);
			r=min(ra,min(rb,min(rc,rd)));
			sum+=(lis[r]-lis[l-1])*(b/l-a/l)*(d/l-c/l);
		}for(;l<=min(b,c);l=r+1){
			int rb=b/(b/l),rc=c/(c/l),rd=d/(d/l);
			r=min(rb,min(rc,rd));
			sum+=(lis[r]-lis[l-1])*(b/l)*(d/l-c/l);
		}for(;l<=min(b,d);l=r+1){
			int rb=b/(b/l),rd=d/(d/l);
			r=min(rb,rd);
			sum+=(lis[r]-lis[l-1])*(b/l)*(d/l);
		}printf("%lld\n",sum);
	}return 0;
}
```

~~目前2520ms最优解~~

[蒟蒻的blog](https://mhrlovezmy.coding.me/)

---

## 作者：wasa855 (赞：11)

这题可以被认为是P2257的扩展。   
考虑容斥原理：（为避免公式过长，设$[\gcd(i,j)=k]$为$\text{A}$）   
$$\sum_{i=a}^b \sum_{j=c}^{d}[A]=\sum_{i=1}^b \sum_{j=1}^{d}[A]-\sum_{i=1}^{a-1} \sum_{j=1}^{d}[A]-\sum_{i=1}^b \sum_{j=1}^{c-1}[A]+\sum_{i=1}^{a-1} \sum_{j=1}^{c-1}[A] $$   
所以问题便转化为求
$$\sum_{i=1}^n \sum_{j=1}^{m}[\gcd(i,j)=k]$$
如果做过[P2257](https://www.luogu.org/problemnew/show/P2257)的话，可以马上得出答案：这个柿子$=\sum_{T=1}^{min(n,m)}(\lfloor \frac{N}{T} \rfloor \times \lfloor \frac{M}{T} \rfloor) \times \sum_{k\in prim,k|T}\mu(\frac{T}{k})$   
如果没做过的话，可以看看我的[题解](https://www.luogu.org/blog/70780/solution-p2257).

#### （重点）一些让代码更快的方法   
解法已经有太多的大佬讲过了，包括复杂度更低的方法，但优化和不优化仍有巨大的差距。   
首先，在所有变量都是```long long```的情况下（```#define int long long```），尽管两次增大时限，还是会超时。   
如果只给需要```long long```的变量开```long long```，虽然不超时，但还是比较慢。   
这时候发现$b,d\leq 50000$，那么一共的排列也只有$50000^2=2500000000$种，刚好超出了int的范围，但限制告诉我们，只有较少一部分数符合条件，那最大的答案是多少呢？   
在$a=c=1,b=d=50000$时，打表发现$k=1$的时候答案最大，且等于$1519848527$，这的确在int的范围内。于是将所有变量开成int不会溢出。   
这样优化之后代码还是很快的。   

#### 最后，在代码之前，祝大家NOIP/NOI/省选 2019 RP++   

代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int mu[50005];
int sum[50005];
int prim[50005];
bool mark[50005];
int cnt;
inline int read()
{
	char x=getchar();
	while(!isdigit(x))
	{
		x=getchar();
	}
	int ans=0;
	while(isdigit(x))
	{
		ans=ans*10+x-48;
		x=getchar();
	}
	return ans;
}
void getmu()
{
	int N=50000;
	mu[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(mark[i]==false)
		{
			prim[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt;j++)
		{
			if(i*prim[j]>N)
			{
				break;
			}
			mark[i*prim[j]]=true;
			if(i%prim[j]==0)
			{
				mu[i*prim[j]]=0;
				break;
			}
			mu[i*prim[j]]=-mu[i];
		}
	}
	for(int i=1;i<=N;i++)
	{
		sum[i]=sum[i-1]+mu[i];
	}
}
int work(int a,int b,int k)
{
	int ans=0;
	int mx=a/k;
	int my=b/k;
	for(int l=1,r;l<=min(mx,my);l=r+1)
	{
		r=min(mx/(mx/l),my/(my/l));
		ans+=(mx/l)*(my/l)*(sum[r]-sum[l-1]);
	}
//	printf("%lld %lld %lld : %lld\n",a,b,k,ans);
	return ans;
}
int main()
{
	getmu();
	int T;
	cin>>T;
	int a,b,c,d,k;
	for(int i=1;i<=T;i++)
	{
		a=read();
		b=read();
		c=read();
		d=read();
		k=read();
		printf("%d\n",work(b,d,k)-work(a-1,d,k)-work(b,c-1,k)+work(a-1,c-1,k));
	}
	return 0;
}

```

---

## 作者：Colin_Lovecraft (赞：8)

最近开始学习莫比乌斯函数,和莫比乌斯反演,这些题都好难啊.

这一道总算是一道比较简单的.

以下是推导过程:

我们要求的是
$$ans = \sum_{ a\leq i \leq b}\sum_{c\leq j \leq d}[gcd(i,j) = k]$$

我们用一个而为前缀和，转化为求
$$ans = \sum^n_{i = 1}\sum^m_{j = 1}[gcd(i,j) = k]$$

消去$i$和$j$的最大公约数$k$,得到
$$ans = \sum^{\lfloor\frac{n}{k} \rfloor}_{i = 1}\sum^{\lfloor\frac{m}{k} \rfloor}_{j = 1}[gcd(i,j) = 1]$$

因为当且仅当$gcd(i,j) = 1$时,方括号的值为1,否则为0,所以我们可以根据莫比乌斯函数的性质，得到

$$ans = \sum^{\lfloor\frac{n}{k} \rfloor}_{i = 1}\sum^{\lfloor\frac{m}{k} \rfloor}_{j = 1}\sum_{d|gcd(i,j)}\mu(d)$$

改变一下枚举的对象,不是枚举$i$和$j$,而是枚举$d$,改变枚举顺序,得到
$$ans = \sum_{d = 1}^{min(n,m)}\mu(d)\sum_{dki \leq n}\sum_{dkj \leq m}1$$
即
$$ans =\sum_{d = 1}^{min(n,m)}\mu(d)\lfloor\frac{n}{kd} \rfloor\lfloor\frac{m}{kd} \rfloor$$

这时的时间复杂度为$O(n)$,对于有多组数据的题目还是略慢，有没有继续优化的余地?

这时候我们发现:有许多的$\lfloor \frac{n}{i}\rfloor$的值是相等的,而且它们是连续的一段，这时候我们用到数论中一个很好用的技巧-------整除分块,可以将时间复杂度进一步降低到$O(\sqrt n)$,就可以AC了.
 
code:
```cpp
int n,m,k;
int mu[50000 + 5];
int is_prime[50000 + 5];
int prime[50000 + 5];

void get_mu(){
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= 50000; ++i) {
        if(!is_prime[i]) prime[++tot] = i, mu[i] = -1;
        for(int j = 1; j <= tot; ++j) {
            if(prime[j] > 50000 / i) break;
            is_prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for(int i = 1; i <= 50000; ++i) mu[i] += mu[i - 1];
}


ll solve(int n,int m){
    ll ans = 0;
    for(int d = 1,next_d;d * k <= min(n,m);d = next_d + 1){
        next_d = min(
            n / (n / d),
            m / (m / d)
        );
        ans += (ll)(mu[next_d] - mu[d - 1]) * (n / k / d) * (m / k / d);
    }
    return ans;
}
// completed
int main(){
    get_mu();
    int T = read();
    while(T--){
        int a = read();
        int b = read();
        int c = read();
        int d = read();
        k = read();
        cout<<(solve(b,d) - solve(b,c - 1) - solve(a - 1,d) + solve(a - 1,c - 1))<<endl;
    }
    return 0;
}
```

---

## 作者：chihik (赞：6)


显然，此题可用容斥化简：

$$\sum_{i=a}^b\sum_{j=c}^d[gcd(i,j)=k]$$

$$\Rightarrow\sum_{i=1}^b\sum_{j=1}^d[gcd(i,j)=k]-\sum_{i=1}^{a-1}\sum_{j=1}^d[gcd(i,j)=k]-\sum_{i=1}^b\sum_{j=1}^{c-1}[gcd(i,j)=k]+\sum_{i=1}^{a-1}\sum_{j=1}^{c-1}[gcd(i,j)=k]$$

对于每一部分，我们可以单独计算：

$$\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)=k]$$

$$\sum_{i=1}^{\lfloor \frac{n}{k} \rfloor }\sum_{j=1}^{\lfloor \frac{m}{k} \rfloor}[gcd(i,j)=1]$$

$$\sum_{i=1}^{\lfloor \frac{n}{k} \rfloor }\sum_{j=1}^{\lfloor \frac{m}{k} \rfloor}\sum_{d|gcd(i,j)}\mu(d)$$

$$\sum_{d=1}^{min(n,m)}\mu(d)\sum_{i=1}^{\lfloor \frac{n}{kd} \rfloor }\sum_{j=1}^{\lfloor \frac{m}{kd} \rfloor}$$

$$\sum_{d=1}^{min(n,m)}\mu(d)\lfloor \frac{n}{kd} \rfloor\lfloor \frac{m}{kd} \rfloor$$

可以用数论分块$\Theta(\sqrt{n}~)$解决，总复杂度为$\Theta(t\sqrt{n})$。

注意，这道题 #$define~int~~~long~long$会见祖宗的，答案开$long ~long$即可。


```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 50000;
int n , a , b , c , d , f[ MAXN + 5 ];

int mu[ MAXN + 5 ] , prime[ MAXN + 5 ] , k;
bool vis[ MAXN + 5 ];
void sieve( ) {
	mu[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) {
			prime[ ++ k ] = i;
			mu[ i ] = -1;
		}
		for( int j = 1 ; j <= k && 1ll * i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1;
			if( i % prime[ j ] == 0 ) break;
			mu[ i * prime[ j ] ] = -mu[ i ];
		}
	}
	for( int i = 1 ; i <= MAXN ; i ++ )
		f[ i ] = f[ i - 1 ] + mu[ i ];
}

long long solve( int n , int m ) {
	int d = min( n , m );
	long long Ans = 0;
	for( int l = 1 , r ; l <= d ; l = r + 1 ) {
		r = min( n / ( n / l ) , m / ( m / l ) );
		Ans = Ans + 1ll * ( f[ r ] - f[ l - 1 ] ) * ( n / k / l ) * ( m / k / l );
	}
	return Ans;
}
long long Get( ) {
	return solve( b , d ) - solve( a - 1 , d ) - solve( b , c - 1 ) + solve( a - 1 , c - 1 );
}

signed main( ) {
	sieve( ); 
	scanf("%d",&n);
	while( n -- ) {
		scanf("%d %d %d %d %d",&a,&b,&c,&d,&k);
		printf("%lld\n",Get( )); 
	} 
	return 0;
}
```


---

## 作者：吴恩泽 (赞：5)

最近在学习莫比乌斯反演，终于看到一道裸题可以让我A掉了

询问 a≤x≤b，c≤y≤d，且gcd(x,y) = k 的个数

即$F(a, b, c, d) = \sum_a^b{x}\sum_c^d{y}[gcd(x, y) == k]$


很明显我们可以用容斥转换成

$F(a, b, c, d)= F(1, b, 1, d) - F(1, b, 1, c - 1) - F(1, a - 1, 1, d) + F(1, a - 1, 1, c - 1)$


所以只需要求出:


$f(k, b, d) = \sum_1^b{x}\sum_1^d{y}[gcd(x, y) == k]$


通过莫比乌斯反演:


$f(k, b, d) =  \sum_ {k | t} g(t)μ(t / k)$


所以

$f(k, b, d) =  \sum_ {k | x}μ(\frac{x}{k}){[\frac{b}{x}]}[\frac{d}{x}]$


$   =  \sum_ {i = 1}^{[\frac{n}{k}]}μ(i){[\frac{\frac{b}{k}}{i}]}[\frac{\frac{d}{k}}{i}]$



然后预处理μ(n)的前缀和，后面可以$\sqrt{n}$ 算出

总复杂度 $n\sqrt{n}$


---

## 作者：derta (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P2522)

## 题意简述

求 $\sum_{x=a}^{b}\sum_{y=c}^{d}[\gcd(x,y)=k]$

## 思路
这是一种不需要容斥原理的做法

注意：以下柿子默认 $b \leqslant d$

把柿子整体除 $k$，得
$$\sum_{x=\lceil \frac{a}{k} \rceil}^{\lfloor\frac{b}{k}\rfloor}\sum_{y=\lceil \frac{c}{k} \rceil}^{\lfloor\frac{d}{k}\rfloor}[\gcd(x,y)=1]$$

利用 $\mu$ 的性质 $\sum_{d|n} \mu(d)=[n=1]$，得
$$\sum_{x=\lceil \frac{a}{k} \rceil}^{\lfloor\frac{b}{k}\rfloor}\sum_{y=\lceil \frac{c}{k} \rceil}^{\lfloor\frac{d}{k}\rfloor}\sum_{z|\gcd(x,y)}\mu(z)$$

把柿子改为枚举 $z$，得
$$\sum_{z=1}^{\lfloor\frac{b}{k}\rfloor}\mu(z)\sum_{x=\lceil \frac{a}{k} \rceil}^{\lfloor\frac{b}{k}\rfloor}\sum_{y=\lceil \frac{c}{k} \rceil}^{\lfloor\frac{d}{k}\rfloor}[z|\gcd(x,y)]$$

由 $\gcd$ 的性质，可以推出
$$\sum_{z=1}^{\lfloor\frac{b}{k}\rfloor}\mu(z)\sum_{x=\lceil \frac{a}{k} \rceil}^{\lfloor\frac{b}{k}\rfloor}\sum_{y=\lceil \frac{c}{k} \rceil}^{\lfloor\frac{d}{k}\rfloor}[z|x][z|y]$$

又因为任意两数 $n,m(n \geqslant m)$ 之间有 $\lfloor\dfrac{n}{k}\rfloor-\lfloor\dfrac{m-1}{k}\rfloor$ 个数能被 $k$ 整除，得
$$\sum_{z=1}^{\lfloor\frac{b}{k}\rfloor}\mu(z)(\lfloor\frac{\lfloor\frac{b}{k}\rfloor}{z}\rfloor-\lfloor \frac{\lceil \frac{a}{k} \rceil-1}{z} \rfloor)(\lfloor\frac{\lfloor\frac{d}{k}\rfloor}{z}\rfloor-\lfloor \frac{\lceil \frac{c}{k} \rceil-1}{z} \rfloor)$$

化简，得

$$\sum_{z=1}^{\lfloor\frac{b}{k}\rfloor}\mu(z)(\lfloor\frac{b}{kz}\rfloor-\lceil \frac{a-1}{kz} \rceil)(\lfloor\frac{d}{kz}\rfloor-\lceil \frac{c-1}{kz} \rceil)$$

预处理 $\mu$ 的前缀和，再把后面的一大坨整除分块就可以了

时间复杂度 $\Theta(n+T\sqrt n)$

这个方法应该是**理论常数较小**的算法，但我人比较傻，连第一页都挤不进去

Code：

```cpp
#include <iostream>
const int MAXN = 50000;
int Prime[5200], size, sum[MAXN + 5];
//Prime[i]=第i个质数，size=当前筛出的质数数量，sum[i]=mu[1]+mu[2]+...+mu[i] 
bool mark[MAXN + 5]; //mark[i]=true表示i为合数，反之为质数 

void sieve(int n) { //欧拉筛预处理mu 
	mark[1] = true;
	sum[1] = 1;
	//特判1 
	for(int i = 2; i <= n; ++i) {
		if(mark[i] == false) { //若mark[i]未被筛掉 
			Prime[size++] = i; //加入质数表 
			sum[i] = -1; //为了节省空间，我把mu[]与sum[]合并
			//这个sum[i]就是mu[i] 
		}
		for(int j = 0; j < size && i*Prime[j] <= n; ++j) {
			mark[i*Prime[j]] = true; //筛去 
			if(i%Prime[j] == 0) break;
			//注意，这句话必须在break后
			//因为break就代表i*Prime[j]有重复的质因子，此时mu[i*Prime[j]]=0 
			sum[i*Prime[j]] = -sum[i]; //质因子数量增加，故为原来的-1倍 
		}
		sum[i] += sum[i - 1]; //这时sum[i]不会再改变了，叠加前缀和 
	}
}

//为了卡常而生的3个函数 
inline int Min(int a, int b)
{ return a < b ? a : b; }

inline void swap(int& a, int& b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

inline void equal_min(int& a, int b)
{ if(a > b) a = b; }

int solve(int a, int b, int c, int d, int k) {
	if(b > d) { //为了保证b<=d 
		swap(a, c);
		swap(b, d);
	}
	a = (a - 1)/k, b /= k, c = (c - 1)/k, d /= k; //都除以k，减小常数 
	int ans = 0;
	for(int i = 1, ni; i <= b; i = ni + 1) { //ni表示下一个i 
		ni = Min(b/(b/i), d/(d/i)); //取最小值，否则两个块可能不一样大（“木桶效应”） 
		if(a >= i) equal_min(ni, a/(a/i));
		if(c >= i) equal_min(ni, c/(c/i));
		//这两个if是为了避免除以0而导致RE 
		ans += (sum[ni] - sum[i - 1])*(b/i - a/i)*(d/i - c/i);
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0); //加速cin,cout 
	sieve(MAXN); //欧拉筛 
	int n, k, a, b, c, d;
	std::cin >> n;
	while(n--) {
		std::cin >> a >> b >> c >> d >> k;
		std::cout << solve(a, b, c, d, k) << "\n";
	}
	return 0;
}
```

最后附上2道练习题：

[[POI2007]ZAP-Queries](https://www.luogu.com.cn/problem/P3455)

[YY的GCD](https://www.luogu.com.cn/problem/P2257)

个人认为的难度排序：

[POI2007]ZAP-Queries < [HAOI2011]Problem b < YY的GCD

---

## 作者：Yyxxxxx (赞：4)

学习大佬贴[博客](https://www.luogu.com.cn/blog/Ye-Star/)，如果题解又炸了那就去博客看吧。QAQ
- 题意

求$\sum\limits_{i=a}^b\sum\limits_{j=c}^d[gcd(i,j)=d]$

- 反演

比起上式，我们更容易得出

$ans(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[gcd(i,j)=d]$

的值  

$\because [gcd(i,j)=d]$

$\therefore \sum\limits_{i=1}^n\sum\limits_{j=1}^m[gcd(i,j)=d]=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}[gcd(i,j)=1]$

设：

$f(x)=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}[gcd(i,j)=x]$

$g(x)=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}[x|gcd(i,j)]$

$f(x)$表示最大公因数是$x$的点对

$g(x)$表示公因数是$x$的点对

显然有：

$g(x)=\sum\limits_{x|k,k \le n}f(x)$

~~一波~~反演~~猛如虎~~：

$f(x)=\sum\limits_{x|k}f(x)\mu(\frac{k}{x})\iff f(x)=\sum\limits_{x|k}\mu(x)f(\frac{k}{x})$

$g(x)=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}[x|gcd(i,j)]$

$=\sum\limits_{i=1}^{\frac{n}{dx}}\sum\limits_{j=1}^{\frac{m}{dx}}[1|gcd(i,j)]$

$=\sum\limits_{i=1}^{\frac{n}{dx}}\sum\limits_{j=1}^{\frac{m}{dx}}1$

$=\lfloor\frac{n}{dx}\rfloor\cdot\lfloor\frac{m}{dx}\rfloor$

故：

$ans(n,m)=f(1)=\sum\limits_{i=1}^n\mu(i)\lfloor\frac{n}{dx}\rfloor\lfloor\frac{m}{dx}\rfloor$

- 求解

我们要求$\sum\limits_{i=a}^b\sum\limits_{j=c}^d[gcd(i,j)=d]$  
直接求不好求，那咱就间接求   
间接求就考虑容斥


![](https://cdn.luogu.com.cn/upload/image_hosting/ldxqgbgr.png)


黑圈：$ans(b,d)$  
红圈：$ans(a-1,d)$  
绿圈：$ans(c-1,b)$  
紫色部分（红绿交集）：$ans(a-1,c-1)$   
蓝色部分（答案）：$ans(b,d)-ans(a-1,d)-ans(c-1,b)+ans(a-1,c-1)$ 


数论分块一下就可以$O(\sqrt{n})$做完啦！    
分块不会的话[[P1403]](https://www.luogu.com.cn/problem/P1403)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
#define ll long long
ll prime[maxn],mu[maxn],sum[maxn],cnt;
bool used[maxn];
inline int read()//快读
{
    int x=0;
    int p=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')p=-1;c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    return x*=p;   
}
void get_mu()//筛mu
{
    mu[1]=1;
    for(register int i=2;i<=maxn;i++)
    {
        if(!used[i]){mu[i]=-1;prime[++cnt]=i;}
        for(register int j=1;j<=cnt&&i*prime[j]<=maxn;++j)
        {
            used[i*prime[j]]=1;
            if(i%prime[j]==0)break;
            else mu[i*prime[j]]=-mu[i];
        }
    }
    for(register int i=1;i<=maxn;++i)sum[i]=sum[i-1]+mu[i];
}
ll getans(int a,int b,int k)//分块
{
    if(a==0||b==0)return 0;
    if(a>b)swap(a,b);
    ll ans=0,g=a;
    for(register int l=1,r;l<=g;l=r+1)
    {
        r=min(a/(a/l),b/(b/l));
        ans+=(long long)(a/(l*k))*(b/(l*k))*(sum[r]-sum[l-1]);
    }
    return ans;
}
void work()
{
    int a;int b;int c;int d;int k;
    a=read(),b=read(),c=read(),d=read(),k=read();
    //式子在题解里写了
    printf("%lld\n",getans(b,d,k)-getans(a-1,d,k)-getans(b,c-1,k)+getans(a-1,c-1,k));
}
int main()
{
    int t;
    t=read();
    get_mu();
    while(t--)work();//多组数据
    return 0;
}
```
















---

## 作者：loceaner (赞：3)

## [题目链接](https://www.luogu.com.cn/problem/P2522)

## 题意

有$n$组询问，每次给出$a,b,c,d,k$，求$\sum\limits_{x=a}^{b}\sum\limits_{y=c}^{d}[\gcd(x,y)=k]$ 

## 思路

> 容斥原理+数论分块+莫比乌斯反演

我做的莫比乌斯反演的第一道题= =

设$f(n,m)=\sum\limits_{i=1}^{n}\sum\limits_{j= 1}^{m}[\gcd(i,j)=k]$

那么根据容斥原理，题目中的式子就转化成了$f(b,d)-f(b, c - 1) - f(a - 1,d) + f(a - 1, c - 1)$

所以我们接下来的问题就转化为了如何求$f$的值

现在来化简$f$的值

1. 容易得出原式等价于$$\sum\limits_{i = 1}^{\lfloor\frac{n}{k}\rfloor}\sum\limits_{j = 1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(i,j) = 1]$$

2. 因为$\epsilon(n) =\sum\limits_{d|n}\mu(d)=[n=1]$，由此可将原式化为$$\sum\limits_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum\limits_{d|gcd(i,j)}\mu(d)$$

3. 改变枚举对象并改变枚举顺序，先枚举$d$，得$$\sum\limits_{d=1}^{\min(n,m)}\mu(d)\sum\limits_{i=1}^{\lfloor\frac{n}{k}\rfloor}[d|i]\sum\limits_{j=1}^{\lfloor\frac{m}{k}\rfloor}[d|j]$$

   也就是说当$d|i$且$d|j$时，$d|\gcd(i,j)$

4. 易得$1\sim \lfloor\frac{n}{k}\rfloor$中一共有$\lfloor\frac{n}{dk}\rfloor$个$d$的倍数，同理$1\sim \lfloor\frac{m}{k}\rfloor$中一共有$\lfloor\frac{m}{dk}\rfloor$个$d$的倍数，于是原式化为$$\sum\limits_{d=1}^{\min(n,m)}\mu(d)\lfloor\frac{n}{dk}\rfloor\lfloor\frac{m}{dk}\rfloor$$

此时已经可以$O(n)$求解，但是过不了，因为有很多值相同的区间，所以可以用数论分块来做

先预处理$\mu$，再用数论分块，复杂度$O(n+T\sqrt n)$

我的代码每次得分玄学，看评测机心情，建议自己写

## 代码

```cpp
/*
Author:loceaner
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 1e6 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return x * f;
}

int n, a, b, c, d, k, cnt, p[A], mu[A], sum[A];
bool vis[A];

void getmu() {
	int MAX = 50010;
	mu[1] = 1;
	for (int i = 2; i <= MAX; i++) {
		if (!vis[i]) mu[i] = -1, p[++cnt] = i;
		for (int j = 1; j <= cnt && i * p[j] <= MAX; j++) {
			vis[i * p[j]] = true;
			if (i % p[j] == 0) break;
			mu[i * p[j]] -= mu[i];
		}
	}
	for (int i = 1; i <= MAX; i++) sum[i] = sum[i - 1] + mu[i];
}

int work(int x, int y) {
	int ans = 0ll;
	int max = min(x, y);
	for (int l = 1, r; l <= max; l = r + 1) {
		r = min(x / (x / l), y / (y / l));
		ans += (1ll * x / (l * k)) * (1ll * y / (l * k)) * 1ll * (sum[r] - sum[l - 1]); 
	}
	return ans;
}

void solve() {
	a = read(), b = read(), c = read(), d = read(), k = read();
	cout << work(b, d) - work(a - 1, d) - work(b, c - 1) + work(a - 1, c - 1) << '\n';
}

signed main() {
	getmu();
	int T = read();
	while (T--) solve();
	return 0;
}

```

---

## 作者：nekko (赞：3)

## 题目描述

有$T$组询问，每次给定整数$a,b,c,d,k$，求有多少对正整数$x,y$，满足$a \le x \le b \wedge c \le y \le d \wedge (x,y)=k$

$1 \le a,b,c,d,k,T \le 50000 \wedge a \le b \wedge c \le d$

## 题解

不妨考虑$x \le a, y \le b$的情况（即bzoj 1101），然后二维前缀和容斥一下就好了

$\begin{aligned}a \le b \\\sum_{i=1}^{a}\sum_{j=1}^{b}[(i,j)=d] &=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}[(i,j)=1] \\&=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}\sum_{d' \mid (i,j)}\mu(d') \\&=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}\sum_{d' \mid i \wedge d' \mid j}\mu(d') \\&=\sum_{d'=1}^{\lfloor \frac{a}{d} \rfloor}\mu(d')\sum_{d' \mid i}^{\lfloor \frac{a}{d} \rfloor}\sum_{d' \mid j}^{\lfloor \frac{b}{d} \rfloor}1 \\&=\sum_{d'=1}^{\lfloor \frac{a}{d} \rfloor}\mu(d') \lfloor \frac{a}{dd'} \rfloor \lfloor \frac{b}{dd'} \rfloor\end{aligned}$

$\lfloor \frac{a}{dd'} \rfloor \lfloor \frac{b}{dd'} \rfloor$的取值只有$O(\sqrt a + \sqrt b)$种，预处理$\mu$的前缀和，单次询问可以$O(\sqrt n)$计算

## 代码

``` cpp
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 50000 + 10;

int mu[N], vis[N], p[N], tot;

ll sol(int n, int m, int d) {
    ll ans = 0;
    if(n > m) swap(n, m);
    n /= d, m /= d;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (ll) (mu[j] - mu[i - 1]) * (n / i) * (m / i);
    }
    return ans;
}

void sol() {
    int a, b, c, d, k; scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
    ll ans = sol(b, d, k) + sol(a - 1, c - 1, k) - sol(a - 1, d, k) - sol(b, c - 1, k);
    printf("%lld\n", ans);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= 50000 ; ++ i) {
        if(!vis[i]) mu[i] = -1, p[++ tot] = i;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= 50000 ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    int T; scanf("%d", &T);
    while(T --) sol();
}
```




---

## 作者：Gypsophila (赞：2)

### Description 

求有多少个数对 $(x,y)$ ，满足$ a \leq x \leq b$ ，$c \leq y \leq d$ ，且 $\gcd(x,y) = k$，$\gcd(x,y)$函数为 $x$ 和 $y$ 的最大公约数。多组询问。$a,b,c,d,k,T \leq 50000$

### Solution

莫比乌斯反演的经典题目QAQ

首相将问题转化成前缀上的问题。即需要求出 有多少个数对 $(x,y)$ ，满足$ 1 \leq x \leq a$ ，$1 \leq y \leq b$ ，且 $\gcd(x,y) = k$。如果能够快速算出来这个，容斥一下就可以求出最后答案。

考虑这个怎么求，开始推式子。这个东西显然就是

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}[\gcd(i,j)=k]$$

把 $k$ 提出来可得

$$\sum\limits_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(i, j)=1]$$

然后把后面这个 $[\gcd(i,j)=1]$ 反演掉，得

$$\sum\limits_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum\limits_{d|\gcd(i,j)}\mu(d)$$

把 $d$ 搞到前面来，得到

$$\sum\limits_{d=1}^{\lfloor \frac{n}{k} \rfloor} \mu(d)\lfloor \frac{n}{kd} \rfloor\lfloor \frac{m}{kd} \rfloor$$

好了，这个玩意可以预处理出 $\mu$ 得前缀和然后分块完事。

### Code 
[看代码戳这里](https://www.cnblogs.com/acfunction/p/10127599.html)

---

## 作者：y2823774827y (赞：2)

纪念第一次不看题解A的莫比乌斯反演

求$\sum\limits_{i=a}^{b}\sum\limits_{j=c}^{d}[gcd(i,j)=k]$

由容斥原理可得原式可化为：

$\sum\limits_{i=1}^{b}\sum\limits_{j=1}^{d}[gcd(i,j)=k]-(\sum\limits_{i=1}^{a-1}\sum\limits_{j=1}^{d}[gcd(i,j)=k])+\sum\limits_{i=1}^{b}\sum\limits_{j=1}^{c-1}[gcd(i,j)=k]-\sum\limits_{i=1}^{a-1}\sum\limits_{j=1}^{c-1}[gcd(i,j)=k]$

发现这几个式子只有上界不同，则实际上要化简的式子为：

$\sum\limits_{i=1}^n\sum\limits_{j=1}^m[gcd( i,j)=k]$

设函数$f(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[gcd(i,j)=k]$ ：公约数为$k$的个数

设函数$F(k)=\sum\limits_{k|d}f(d) (d<=min(n,m))$公约数为$k$的倍数$(d)$的个数

则根据莫比乌斯反演：

$f(k)=\sum\limits_{k|d}\mu(\left\lfloor\dfrac{d}{k}\right\rfloor)F(k)$

$k|d$不好处理，改为枚举$x=\left\lfloor\dfrac{d}{k}\right\rfloor$，化为：

$f(k)=\sum\limits_{x=1}^{min(\frac{n}{k},\frac{m}{k})}\mu(x)F(xk)$

$~~~~~~~~=\sum\limits_{x=1}^{min(\frac{n}{k},\frac{m}{k})}\mu(x)\left\lfloor \dfrac{n}{xk}\right\rfloor \left\lfloor \dfrac{m}{xk}\right\rfloor$

对后面分块一下就好了

```cpp
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int maxn=50000+9;
inline int Read(){
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0',c=getchar();
	}
	return x*f;
}
int T;
int mu[maxn],sum[maxn],prime[maxn];
bool visit[maxn];
inline void F_phi(LL N){
	mu[1]=1;
	int tot(0);
	for(int i=2;i<=N;++i){
		if(!visit[i]){
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*prime[j]<=N;++j){
			visit[i*prime[j]]=true;
			if(i%prime[j]==0)
			    break;
			else
			    mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=N;++i)
	    sum[i]=sum[i-1]+mu[i];
}
inline LL Solve(int n,int m,int d){
	if(n>m)
		swap(n,m);
	LL num(0);
	int N=n/d;
	for(int l=1,r;l<=N;l=r+1){
		r=min((n/d)/(n/l/d),(m/d)/(m/l/d));
		num=num+1ll*(sum[r]-sum[l-1])*1ll*((n/l/d)*1ll*(m/l/d));
	}
	return num;
}
int main(){
	T=Read();
	F_phi(50000);
	while(T--){
		int a=Read(),b=Read(),c=Read(),d=Read(),k=Read();
		LL ans=Solve(b,d,k)-Solve(a-1,d,k)-Solve(b,c-1,k)+Solve(a-1,c-1,k);
		printf("%lld\n",ans);
	}
	return 0;
}/*
2
2 5 1 5 1
1 5 1 5 2

14
3
*/
```

---

## 作者：kradcigam (赞：1)

$$\sum\limits_{i=a}^{b} \sum\limits_{j=c}^{d} [\gcd(i,j)=k]$$

设

函数 $f(x,y)$ 为：

$$\sum\limits_{i=1}^{x} \sum\limits_{j=1}^{y} [\gcd(i,j)=k]$$

那么，运用容斥原理，原式就 $= f(b,d) - f(a,d) - f(b,c) + f(a,c)$

所以现在问题就转换为了求 $f$ 函数。

$$\begin{aligned}&\sum\limits_{i=1}^{x} \sum\limits_{j=1}^{y} [\gcd(i,j)=k] \\=& \sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(i,j)=1]\\=& \sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\varepsilon(\gcd(i,j))\\=& \sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d \mid \gcd(i,j) }\mu(d)\\=& \sum_{d=1 }\mu(d)\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}[d \mid i]\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[d \mid j]\\=&\sum_{d=1}\mu(d)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor\end{aligned}$$

我们可以使用数论分块进行求解

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int N=50010;
int prim[N],mu[N],sum[N],cnt,k,T;
bool vis[N];
void init(){
	mu[1]=1;
	for(register int i=2;i<N;i++){
		if(!vis[i]){
			mu[i]=-1;
			prim[++cnt]=i;
		}
		for(register int j=1;j<=cnt&&i*prim[j]<N;j++){
			vis[i*prim[j]]=1;
			if(i%prim[j]==0)break;
			mu[i*prim[j]]=-mu[i];
		}
	}
	for(register int i=1;i<N;i++)sum[i]=sum[i-1]+mu[i];
}//莫比乌斯反演的板子
ll calc(int a,int b){
	ll ans=0;
	for(register int l=1,r;l<=min(a,b);l=r+1){
		r=min(a/(a/l),b/(b/l));
		ans+=(1ll*a/l)*(1ll*b/l)*(sum[r]-sum[l-1]);
	}
	return ans;
}
int main(){
	init();
	for(read(T);T--;){
		int a,b,c,d;
		read(a);read(b);read(c);read(d);read(k);
		a--;c--;a/=k;b/=k;c/=k;d/=k;
		printf("%lld\n",calc(b,d)-calc(b,c)-calc(a,d)+calc(a,c));
	}
	return 0;
}
```

---

## 作者：Spasmodic (赞：1)

莫比乌斯函数入门推式子套路题。

前置芝士：莫比乌斯函数基本性质。

显然只要求出二维前缀和就可以了，就转化成了[这道题](https://www.luogu.com.cn/problem/P3455)。

下面就是莫比乌斯反演套路部分了。
$$\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k]$$
$$=\sum_{i=1}^{[\frac{n}{k}]}\sum_{j=1}^{[\frac{m}{k}]}[\gcd(i,j)=1]$$

$$=\sum_{i=1}^{[\frac{n}{k}]}\sum_{j=1}^{[\frac{m}{k}]}\sum_{d|i,d|j}\mu(d)$$
$$=\sum_{d=1}^{min([\frac{n}{k}],[\frac{m}{k}])}\mu(d)\sum_{i=1,d|i}^{[\frac{n}{k}]}\sum_{j=1,d|j}^{[\frac{m}{k}]}1$$
$$=\sum_{d=1}^{min([\frac{n}{k}],[\frac{m}{k}])}\left[\frac{n}{dk}\right]\left[\frac{m}{dk}\right]$$
然后使用整数分块就完事。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
typedef long long ll; 
inline void read(int&x)
{
    int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=(x<<1)+(x<<3)+s-'0';s=getchar();}
    x*=f;
}
inline void print(ll x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
int pr[N],mu[N],sum[N],n;
int T,a,b,c,d,k;
bool vst[N];
ll calc(ll a,ll b,ll d){
	a/=d;b/=d;
	ll ans=0;
	for(int i=1,j;i<=min(a,b);i=j+1){
		j=min(a/(a/i),b/(b/i));
		ans+=(ll)(a/i)*(b/i)*(sum[j]-sum[i-1]);
	}
	return ans;
}
int main(){
	mu[1]=1;
	for(int i=2,tot=0;i<=50000;++i){
		if(!vst[i]){mu[i]=-1;pr[++tot]=i;}
		for(int j=1;i*pr[j]<=50000;++j){
			vst[i*pr[j]]=1;
			if(i%pr[j])mu[i*pr[j]]=-mu[i];
			else break;
		}
	}
	sum[1]=mu[1];
	for(int i=2;i<=50000;++i)sum[i]+=mu[i]+sum[i-1];
	read(T);
	while(T--){
		read(a),read(b),read(c),read(d),read(k);
		printf("%lld\n",calc(b,d,k)-calc(a-1,d,k)-calc(b,c-1,k)+calc(a-1,c-1,k));
	}
	return 0;
}
```

---

## 作者：11D_Beyonder (赞：0)

## 分析  
[看博客体验更好](https://pro_11d_beyonder.gitee.io/2020/07/03/%E6%B4%9B%E8%B0%B7P2522-HAOI2011-Problem-b/)   
&emsp;&emsp;令二元函数 $f(x,y)=\sum\limits_{i=1}^x\sum\limits_{j=1}^y [\gcd(i,j)=k]$，其中 $x,y\in N^*$。由题意，所求答案为 $\sum\limits_{i=a}^b\sum\limits_{j=c}^d[\gcd(i,j)=k]$；依据容斥原理，$ans=f(b,d)-f(a-1,d)-f(b,c-1)+f(a-1,c-1)$。  
&emsp;&emsp;任务转化为，对于给定的 $n,m\in N^*$，求 $f(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m [\gcd(i,j)=k]$ 的值。  
&emsp;&emsp;首先，$k$ 为 $i,j$ 的最大公约数，故 $\frac{i}{k}$ 与 $\frac{j}{k}$ 互质，即 $\gcd(\frac{i}{k},\frac{j}{k})=1$。所以 $f(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m \left[\gcd\left(\frac{i}{k},\frac{j}{k}\right)=1\right]$；从此式看出，$\frac{i}{k}$ 的上限为 $\left\lfloor\frac{n}{k}\right\rfloor$，$\frac{j}{k}$ 的上限为 $\left\lfloor\frac{m}{k}\right\rfloor$；因此等价于， $f(n,m)=\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[\gcd(i,j)=1]$。  
&emsp;&emsp;接下来利用莫比乌斯反演的性质，$\gcd(i,j)=1\Leftrightarrow\sum\limits_{d\mid\gcd(i,j)}\mu(d)$。故 $f(n,m)=\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}\sum\limits_{d\mid\gcd(i,j)}\mu(d)$。    
&emsp;&emsp;接下来变换求和次序，改为枚举 $d$。$f(n,m)=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}\mu(d)[d\mid\gcd(i,j)]$；由于 $\mu(d)$ 为只与 $d$ 相关的函数，则 $f(n,m)=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\mu(d)\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[d\mid\gcd(i,j)]$。  
&emsp;&emsp;有条件 $d\mid\gcd(i,j)$，故可设 $\gcd(i,j)=pd$；由最大公约数的定义 $pd\mid i$ 且 $pd\mid j$，因此假设 $i=p_1pd$，$j=p_2pd$；其中，$p,p_1,p_2\in N^*$。经过上述略证， $d\mid\gcd(i,j)$ 的充要条件是：$i,j$ 都为 $d$ 的倍数。在区间 $\left[1,\left\lfloor\frac{n}{k}\right\rfloor\right]$ 中，$d$ 的倍数有 $\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor$ 个；在区间 $\left[1,\left\lfloor\frac{m}{k}\right\rfloor\right]$ 中，$d$ 的倍数有 $\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor$ 个；因此，满足条件 $d\mid\gcd(i,j)$ 的数对 $(i,j)$ 的个数有 $\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[d\mid\gcd(i,j)]=\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\times\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor$。   
&emsp;&emsp;将 $\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[d\mid\gcd(i,j)]=\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\times\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor$ 代入，得 $f(n,m)=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor\mu(d)$。该式可用数论分块解决。  
&emsp;&emsp;结合以上  
&emsp;&emsp;$\begin{aligned}f(n,m)&=\sum\limits_{i=1}^n\sum\limits_{j=1}^m [\gcd(i,j)=k]\\&=\sum\limits_{i=1}^n\sum\limits_{j=1}^m \left[\gcd\left(\frac{i}{k},\frac{j}{k}\right)=1\right]\\&=\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[\gcd(i,j)=1]\\&=\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}\sum\limits_{d\mid\gcd(i,j)}\mu(d)\\&=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}\mu(d)[d\mid\gcd(i,j)]\\&=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\mu(d)\sum\limits_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}[d\mid\gcd(i,j)]\\&=\sum\limits_{d=1}^{\min\left(\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k}\right\rfloor\right)}\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor\mu(d)\end{aligned}$   
&emsp;&emsp;综上所述，对于给定的 $n,m$ 最终用数论分块求解 $f(n,m)$ 的值 。假设在区间 $[l,r]$ 内，$\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\times\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor$ 恒为 $A$，则 $\sum\limits_{d=l}^r\left\lfloor\frac{\left\lfloor\frac{n}{k}\right\rfloor}{d}\right\rfloor\left\lfloor\frac{\left\lfloor\frac{m}{k}\right\rfloor}{d}\right\rfloor\mu(d)=A\sum\limits_{d=l}^r\mu(d)$；显然，我们要预处理莫比乌斯函数的前缀和，才能在 $O(1)$ 内求出一个分块的值。  
&emsp;&emsp;题目的最终答案为 $f(b,d)-f(a-1,d)-f(b,c-1)+f(a-1,c-1)$。  
## 代码  
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 50006
using namespace std;
bool vis[N];
int prime[N>>1];//质数
int mu[N];//莫比乌斯函数
int sum[N];//mu[i]的前缀和
int cnt;
int a,b,c,d,k;
//--------------------------------------------
//欧拉筛求得莫比乌斯函数
//求莫比乌斯函数的前缀和
void init(int n)
{
	mu[1]=1;
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) 
			{
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
	}
	for(i=1;i<=n;i++) sum[i]=sum[i-1]+mu[i];
}
//--------------------------------------------
//--------------------------------------------------
//对于给定的n,m
//计算f(n,m)
//将n/k,m/k看作整体
inline ll f(int n,int m)
{
	n/=k;
	m/=k;
	if(n>m) swap(n,m);
	int l,r;
	ll res=0;
	for(l=1;l<=n;l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		res=res+1ll*(n/l)*(m/l)*(sum[r]-sum[l-1]);
	}
	return res;
}
//--------------------------------------------------
int main()
{
	init(50000);
	int _;
	for(cin>>_;_;_--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		//容斥原理
		printf("%lld\n",f(b,d)-f(a-1,d)-f(b,c-1)+f(a-1,c-1));
	}
	return 0;
}
```

---

## 作者：huangzirui (赞：0)

如果 $\LaTeX$ 崩了就请到[我的博客](https://www.luogu.com.cn/blog/My-luoguBuoke-HZR/solution-p2522)来吧QAQ

题意：

求：

$$\sum_{i=a}^b\sum_{j=c}^d[\gcd(i,j)=e]$$

数据组数 $T\leq 5 \times 10^4\ \ \ \ a,b,c,d,e\leq5\times10^4$ 

---

考虑莫比乌斯反演。

对 $i,j$ 分别除以 $e$ 有：

$$
\sum_{i=\left\lfloor{\frac{a-1}{e}}\right\rfloor+1}^{\left\lfloor{\frac{b}{e}}\right\rfloor}

\sum_{j=\left\lfloor{\frac{c-1}{e}}\right\rfloor+1}^{\left\lfloor{\frac{d}{e}}\right\rfloor}

[\gcd(i,j)=1]
$$

那么设 $A=\left\lfloor{\frac{a-1}{e}}\right\rfloor+1,B=\left\lfloor{\frac{b}{e}}\right\rfloor,C=\left\lfloor{\frac{c-1}{e}}\right\rfloor+1,D=\left\lfloor{\frac{d}{e}}\right\rfloor$ ，那么原式等于：

$$
\sum_{i=A}^{B}

\sum_{j=C}^{D}

[\gcd(i,j)=1]
$$

于是可以直接莫比乌斯反演，原式转换如下：

$$
\sum_{i=A}^{B}

\sum_{j=C}^{D}

\sum_{d|i,j}

\mu(d)
$$

改变枚举顺序： ( 设 $B\leq D$ )

$$
\sum_{d=1}^D

\mu(d)

\sum_{i=\left\lfloor{\frac{A-1}{d}}\right\rfloor+1}^{\left\lfloor{\frac{B}{d}}\right\rfloor}

\sum_{j=\left\lfloor{\frac{C-1}{d}}\right\rfloor+1}^{\left\lfloor{\frac{D}{d}}\right\rfloor}

$$

$$
\sum_{d=1}^D

\mu(d)

(\left\lfloor{\tfrac{B}{d}}\right\rfloor-\left\lfloor{\tfrac{A-1}{d}}\right\rfloor)

(\left\lfloor{\tfrac{D}{d}}\right\rfloor-\left\lfloor{\tfrac{C-1}{d}}\right\rfloor)
$$

于是筛出 $\mu$ 以后套个数论分块即可。

~~四层数论分块可还行~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=50010;
int i,j,k,n,m,T;
int is_prime[N],prime[N],mu[N],Mu[N],num;
void init(){
	mu[1]=1;
	for(int i=2;i<N;i++)is_prime[i]=1;
	for(int i=2;i<N;i++){
		if(is_prime[i])prime[++num]=i,mu[i]=-1;
		for(int j=1;i*prime[j]<N&&j<=num;j++){
			is_prime[i*prime[j]]=0;
			if(i%prime[j]==0)break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<N;i++)Mu[i]=Mu[i-1]+mu[i];
}
inline int Min(int a,int b,int c,int d){
	return min(min(min(a,b),c),d);
}
inline int Get(int x,int y){
	return x>=y? x/(x/y):0x7f7f7f7f;
}
int A,B,C,D,E;
int main(){
	init();
	cin>>T;
	while(T--){
		cin>>A>>B>>C>>D>>E;
		A=(A-1)/E+1;B/=E;
		C=(C-1)/E+1;D/=E;
		ll ans=0;
//		cout<<A<<' '<<B<<' '<<C<<' '<<D<<endl;
		for(int l=1,r=0;l<=max(B,D);l=r+1){
			r=Min(Get(B,l),Get(A-1,l),Get(D,l),Get(C-1,l));
			ans+=((ll)B/l-(A-1)/l)*(D/l-(C-1)/l)*(Mu[r]-Mu[l-1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Tommy_clas (赞：0)

前言：其实我在写这道题的时候并没有用容斥统计答案，而是直接把四个端点套进数论分块里进行统计，然后两两做个差分（听起来可能很抽象，下面会有详细解释）。结果提交后发现错了，查看题解并改成容斥以后还是$WA$，不经意间瞟到一行代码，才发现原来$min$写成了$max......$改过来以后发现原做法竟然过了。在我大致看了一遍题解区并确保没有重复做法以后，我决定分享一下这个不用容斥的做法。

[传送门](https://www.luogu.com.cn/problem/P2522)

题目描述：给出五个整数$a,b,c,d,k$，设$a≤x≤b,c≤y≤d$，求$gcd(x,y)=k$的$(x,y)$对数。

具体做法大佬们的题解中已经讲的很详细了，我这里就说一下如何去求这个式子：

$\sum_{x=\frac{a}{k}}^{\frac{b}{k}}\sum_{y=\frac{c}{k}}^{\frac{d}{k}}\sum_{d|gcd(x,y)}\mu(d)$

首先不难证得$d|gcd(x,y)$相当于$d|x$且$d|y$，也就是说当我们枚举约数$d$的时候，我们要确保约数$d$的倍数既存在于$[\frac{a}{k},\frac{b}{k}]$（设存在个数为$u$），也存在于$[\frac{c}{k},\frac{d}{k}]$（设存在个数为$v$），则约数$d$对答案做出的贡献就是$\mu(d)\times u\times v$。然后再计算每个约数$d$的贡献，最后求和就行了。

然而单次计算时间复杂度是$O(n)$的，多组数据会$TLE$，可以考虑用数论分块优化一下。普通的数论分块一般都是卡一个端点（即一段连续的$d$使得$\frac{x}{d}$的值相同），一个区间范围内的数就需要卡两个端点（即一段连续的$d$使得$\frac{y}{d}-\frac{x-1}{d}$的值相同），而两个区间范围内的数就需要卡四个端点（即一段连续的$d$使得$u=\frac{y1}{d}-\frac{x1-1}{d}$的值相同且$v=\frac{y2}{d}-\frac{x2-1}{d}$的值相同且$u=v$）。

总而言之，上述过程就是把$u\times v$相同的$d$统一计算为$(sum\mu(r)-sum\mu(l-1))\times u \times v$①，这样就能把复杂度简化为$O(\sqrt{n})$。

由于要求卡四个端点，所以常数会稍微大一点，但是可以不需要容斥。（然而这样做的本质其实和容斥是相同的，感兴趣的读者可以把刚才统计的①式拆开，然后就能发现这就是容斥。）

详细的可以看一下代码。

上代码：
~~~cpp
//一开始挂了，然后错误地以为自己想错了
//然而并没有（只是单纯地把min写成了max） 
//可以直接把四个端点一起放进去搞数论分块，然后做个差分即可，不需容斥 
//多余常数大的一批，参照需谨慎 
#include<cstdio>
#include<iostream>
#define N 50005
#define ll long long
using namespace std;
int mu[N],prime[N],T;
ll sum_mu[N];
bool vis[N];
void init()
{
	mu[1]=1,vis[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=prime[0]&&prime[j]*i<=50000;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=mu[i]*(-1);
			else
			{
				mu[i*prime[j]]=0;break;
			}
		}
	}
	for(int i=1;i<=50000;i++)sum_mu[i]=sum_mu[i-1]+mu[i];
}
ll ask(ll xa,ll ya,ll xb,ll yb)
{
	ll res=0; 
	for(ll l=1,r=0;l<=min(ya,yb);l=r+1)
	{
		r=min(min(xa/l?xa/(xa/l):0x3f3f3f3f,ya/(ya/l)),min(xb/l?xb/(xb/l):0x3f3f3f3f,yb/(yb/l)));
		//xa/l（或者xb/l）可能会是0，xa/l=0说明区间[1,xa]不可能存在l~r的倍数，因此不需考虑它的分块右端点的取值，即设为无穷大
		//而ya/l=0或yb/l=0时会自动跳出，因此不需特判。 
		res+=(sum_mu[r]-sum_mu[l-1])*(ya/r-xa/r)*(yb/r-xb/r);
	}
	return res;
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--)
	{
		int a,b,c,d,k;
		scanf("%d %d %d %d %d",&a,&b,&c,&d,&k);
		a--,c--;
		a/=k,b/=k,c/=k,d/=k;
		printf("%lld\n",ask(a,b,c,d));
	}
	return 0;
}
~~~

---

## 作者：greenty (赞：0)

# 题意

对于给出的n个询问，每次求有多少个数对(x,y)，满足a≤x≤b，c≤y≤d，且gcd(x,y) = k，gcd(x,y)函数为x和y的最大公约数。

# 分析

所求 ：$\sum_{i=a}^b \sum_{j=c}^d [gcd(i,j)==k]$

二维区间和的问题通常会转化为二维前缀和来容斥

所求： $solve(n,m) = \sum_{i=1}^n \sum_{j=1}^m [gcd(i,j)==k]$

为了同一推导，默认$n\leq m$ ，如果 $n >m$可以交换$n,m$,因为solve(n,m) == solve(m,n)

我们常常研究互质的情况和性质，如果互质就容易联想到一系列积性函数

变形：$\sum_{i=1}^{\frac n k} \sum_{j=1}^{\frac m k} [gcd(i,j)==1]$

联想到$\epsilon (n)$ 也是在gcd == 1 的时候取值为1,其他情况取值为0

变形：$\sum_{i=1}^{\frac n k} \sum_{j=1}^{\frac m k} \epsilon (gcd(i,j))$

因为 $1* \mu = \epsilon$ （这里$*$指狄利克雷卷积）

变形：$\sum_{i=1}^{\frac n k} \sum_{j=1}^{\frac m k} \sum_{d|gcd(i,j)} \mu(d)$

交换求和顺序：通常可以从意义出发来推，实在不会可以展开找规律,在我们想要把$\mu(d)$提到最前面，便于计数 参考[另一篇博客的和式知识部分](https://www.luogu.org/blog/greenty1208/post-shuo-lun-mu-bi-wu-si-fan-yan)

因为$gcd(i,j) <= min(i,j)$

变形：$\sum_{d=1}^{\frac n k} \mu(d) \sum_{i=1}^{\frac n k}[d|i] \sum_{i=1}^{\frac m k}[d|j] $

考虑：已知d, 在\[1,n\] 中，共有 $\lfloor \frac n d\rfloor$ 个数满足能整除于d，

变形：$\sum_{d=1}^{\frac n k} \mu(d) \lfloor \frac n {kd} \rfloor \lfloor \frac m {kd} \rfloor$

这里我们变成了可以O(n)求解的式子

因为向下取整其实是阶梯函数，会有很多连续相等的部分，我们可以考虑聚合连续相等的部分一起算（也就是数论分块）

考虑含有$\lfloor \frac n i\rfloor$ 的式子（ｎ为常数）

对于任意一个$i$ 我们需要找到一个最大的$j$ 使得$\lfloor \frac n i \rfloor = \lfloor \frac n j \rfloor$

则$j = \lfloor \frac n {\lfloor \frac n i \rfloor} \rfloor$


利用上述结论，每次以$[i,j]$为一块

# 代码

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
bool not_prime[N];
int read() {
    int x=0;char ch = getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x;
}
int prime[N],cnt,mu[N];
int sum[N];
void mus(int n) {
    mu[1] = 1;
    cnt=0;
    for(int i=2;i<=n;i++) {
        if(!not_prime[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for(int j=1;j<=cnt && i*prime[j] <= n;j++) {
            not_prime[i*prime[j]]=1;
            if(i%prime[j]==0) {
                mu[i*prime[j]] = 0;
                break;
            } 
            else{
                mu[i*prime[j]] = -mu[i];
            }
        }
    }
    sum[0]=0;
    for(int i=1;i<=n;i++) {
        sum[i] = sum[i-1] + mu[i];
    }
}
int solve(int n,int m,int k) {
    if(n < k || m < k ) return 0;
    if(n > m) swap(n,m);
    int nn = n/k;
    int mm = m/k;
    int res=0;
    for(int d=1;d<=nn;) {
        int enn = nn/(nn/d);
        int enm = mm/(mm/d);
        int en = min(enn,enm);
        res += (sum[en]-sum[d-1])*(nn/d)*(mm/d);
        d = en+1;
    }

    return res;
}
int main() {
    mus(100000);
    int _=read();
    while(_--) {
        int a=read(),b=read(),c=read(),d=read(),k=read();
        int ans = solve(b,d,k) - solve(a-1,d,k) - solve(b,c-1,k) + solve(a-1,c-1,k);
        printf("%d\n",ans);
    }
}
```




---

## 作者：cdcq (赞：0)

（我的推导似乎和大部分人的不太一样  
这个是距离高考还有10天写的……  
因为快高考了所以放飞自我，自习课不想复习拿反演玩一玩，发现这个挺简单的啊，以前怎么学不会呢  
大概是学高考增强了我的推公式的能力吧  

啊不扯了，直接开始题解 
首先必须要想到的思路是四项容斥简化问题  
问题转化为求有对少个数对$ (x,y) $满足$ 1\leq x \leq n, 1\leq y \leq m $且$ gcd(x,y)=1 $  
看过其他反演题的话可能容易想到，$ \sum \sum [gcd(i,j)=1] $是比较好算的  
那么可以把n和m都除等于k，问题就转化为求$ \displaystyle\sum_{i=1}^{n} \sum_{j=1}^{m} [gcd(i,j)=1] $  
因为考虑到对于原来的满足条件的一个数对$ (i,j) $，因为i和j的gcd是k，所以可以写成这样$ (i'\cdot k,j'\cdot k) $，并且i'和j'的gcd是1  
显然若$ i'\cdot k\leq n $，则$ i'\leq \lfloor \frac{n}{k} \rfloor$，j'同理  
现在的问题已经相对简单，剩下的就是推推推了~  
$$ ans(n,m)=\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=1] $$
$$ =\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|gcd(i,j)}\mu(d) $$
这里应用到了
$$ \sum_{d|n}\mu(d)=\begin{cases}0& n=1\\ 1& n\neq1 \end{cases} $$
的性质  
因为$ d|gcd(i,j) $这个表现形式不好，既不利于继续化简，亦不利于代码实现，所以现在换一种表示方式
$$ ans(n,m)=\sum_{d}^{min(n,m)}\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d}\rfloor}\mu(d) $$
先枚举所有可能的gcd，再枚举所有因子有这个gcd的i和j，不难想象和先枚举ij再枚举d所枚举到的东西是一样的，这个似乎是莫比乌斯反演里常用的转化方法  
$$ ans(n,m)=\sum_{d}^{min(n,m)}\mu(d)\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d}\rfloor}1 $$
因为d和ij的枚举情况无关所以可以提到前面来  
后面的东西就可以秒算了
$$ ans(n,m)=\sum_{d}^{min(n,m)}\mu(d)\cdot \lfloor \frac{n}{d} \rfloor \cdot \lfloor \frac{m}{d}\rfloor $$
至此公式推导完毕  
我的推导和popoqqq的不太一样，他是构造了f和F并使用反演的公式，我是根据反演的性质来转化问题，现在看来两种方法本质是一样的  
我的思路受《crash的表格》这道题的影响比较深  
直接$ O(n) $计算会T（因为有n组询问），需要用莫比乌斯反演常用的$ O(\sqrt{n}) $求答案的计算方式，这个在po姐的ppt里解释得很清楚，不在赘述  
代码：  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int rd(){int z=0,mk=1;  char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')mk=-1;  ch=getchar();}
	while(ch>='0'&&ch<='9'){z=(z<<3)+(z<<1)+ch-'0';  ch=getchar();}
	return z*mk;
}
int n,m,n1,n2,m1,m2;
int mu[51000],mus[51000];  //mu's!!!!!!
int prm[51000],prt=0;  bool prg[51000];
void gtmu(){
	memset(prg,0,sizeof(prg));
	mu[1]=mus[1]=1;  //注意mu[1]=1
	for(int i=2;i<=50000;++i){
		if(!prg[i])  prm[++prt]=i,mu[i]=-1;
		for(int j=1;prm[j]*i<=50000 && j<=prt;++j){
			prg[prm[j]*i]=true;
			if(!(i%prm[j])){  mu[i*prm[j]]=0;  break;}
			mu[prm[j]*i]=-mu[i];
		}
		mus[i]=mus[i-1]+mu[i];
	}
}
int sm(int x,int y){  return (x+1)*x*(y+1)*y/4;}
int cclt(int x,int y){
	if(x>y)  swap(x,y);
	int tmp,bwl=0;
	for(int i=1;i<=x;i=tmp+1){
		tmp=min(x/(x/i),y/(y/i));
		//bwl+=sm(x/i,y/i)*(mus[tmp]-mus[i-1]);
		bwl+=(x/i)*(y/i)*(mus[tmp]-mus[i-1]);
	}
	return bwl;
}
int main(){freopen("ddd.in","r",stdin);
	gtmu();
	cin>>n;
	while(n --> 0){  //趋向于
		//cin>>n1>>n2>>m1>>m2>>m;
		n1=rd(),n2=rd(),m1=rd(),m2=rd(),m=rd();
		printf("%d\n",cclt(n2/m,m2/m)+cclt((n1-1)/m,(m1-1)/m)-cclt((n1-1)/m,m2/m)-cclt(n2/m,(m1-1)/m));
		//注意-1
	}
	return 0;
}
```

---

## 作者：fcba (赞：0)

对于单次询问:

类似二维前缀和,问题可以转换为求[1,n] [1,m]中满足gcd==k的对数;

最暴力O(n2)就不说了吧;

使用NOI2010能量采集的方法,我们可以做到nlogn

//设f(i)表示gcd==i的对数,g(i)表示gcd|(整除)i的个数,则g(i)=(n/i)\*(m/i);   f(i)=g(i)-sigemaf(i\*kkk);(kkk\*i<=n);

又因为g(i)=Σi|d f(d); 反演后得:f(i)=Σi|d mu(d/i)g(d)=Σi|d mu(d/i) (n/i)\*(m/i);
我们就可以O(n)地处理每一个询问了;


但询问太多,我们无法处理

观察式子,我们发现 (n/i) 只有sqrt(n)种取值; (n/i) \*(m/i) 就只有2sqrt(n)+2sqrt(m) 种取值

枚举这些取值,并对mu维护前缀和就可以做到总复杂度O(nsqrt(n))了;


后面核心代码:


```cpp
long long solve(long long n,long long m)
{
    n/=k;m/=k;
    long long last,tot=0;if (m<n) swap(n,m);
    for (long long i=1;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        tot+=(n/i)*(m/i)*(sum[last]-sum[i-1]);
    }
    return tot;
}
```
参见 莫比乌斯反演 byPoPoQQQ;

---

## 作者：WJCwjc142857 (赞：0)

此题妙不可言，莫比乌斯反演裸题，和HDU1695很像，但是那题保证了a=c=1，所以那题是真的水爆了，这道题中把a和c不为0算之后，就又多了一个考点：容斥原理
```cpp
#include<bits/stdc++.h>
#define MAX 50001
using namespace std;
int p[50005],mu[50005],MU[50005];
bool p_b[50005];
void mobius()
{
    int i,j,num;
    num=0;
    p_b[1]=true;
    mu[1]=1;
    MU[1]=1;
    for (i=2;i<=MAX;i++)
    {
        if (!p_b[i])
        {
            p[num++]=i;
            mu[i]=-1;
        }
        for (j=0;j<=num&&i*p[j]<=MAX;j++)
        {
            p_b[i*p[j]]=true;
            if (i%p[j]==0)
            {
                mu[i*p[j]]=0;
                break;
            }
            mu[i*p[j]]=-mu[i];
        }
    }
    for (i=2;i<=MAX;i++) MU[i]=MU[i-1]+mu[i];
}
int solve(int l,int r)
{
    int i,last,ans;
    last=ans=0;
    for (i=1;i<=min(l,r);i=last+1)
    {
        last=min(l/(l/i),r/(r/i));
        ans+=(MU[last]-MU[i-1])*int(l/i)*int(r/i);
    }
    return ans;
}
int main()
{
    mobius();
    int n;
    scanf("%d",&n);
    for (;n--;)
    {
        int a,b,c,d,x;
     	scanf("%d%d%d%d%d",&a,&b,&c,&d,&x);
     	a-=1,c-=1;
        a/=x,b/=x,c/=x,d/=x;
        printf("%d\n",solve(b,d)+solve(a,c)-solve(a,d)-solve(c,b));
    }
}
```

---

## 作者：数学系 (赞：0)

这题会用到莫比乌斯反演，其中的原理已经被两位神犇讲的很清楚了。这里就给出代码：

```cpp
#include <iostream>

using namespace std;

const int maxn=100007;

int u[maxn];

bool notprime[maxn]={};
int prime[maxn]={};
int primenum=0;

int prefix[maxn]={};

int min(int a,int b)
{
	return a<b?a:b;
}

void swap(int &a,int &b)
{
	int tmp=a;
	a=b;
	b=tmp;
}

int N;
int a,b,c,d,k;

void Mobius()//求莫比乌斯函数
{
	u[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!notprime[i])
		{
			prime[++primenum]=i;
			u[i]=-1;
		}
		for(int j=1;j<=primenum && prime[j]*i<maxn;j++)
		{
			notprime[prime[j]*i]=1;
			if(i%prime[j]==0)
			{
				u[prime[j]*i]=0;
				break;
			}
			u[prime[j]*i]=-u[i];
		}
	}
}

int solve(int n,int m)
{
	n/=k;
	m/=k;
	int tot=0,last=0;
	if(m<n)
	    swap(n,m);
	for(int i=1;i<=n;i=1+last)
	{
		last=min(n/(n/i),m/(m/i));
		tot+=(prefix[last]-prefix[i-1])*(n/i)*(m/i);
	}
	return tot;
}

int main()
{
	Mobius();
	for(int i=1;i<maxn;i++)
		prefix[i]=prefix[i-1]+u[i];//莫比乌斯函数的前缀和
	cin>>N;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		ans=0;
		cin>>a>>b>>c>>d>>k;
		ans=solve(b,d)+solve(a-1,c-1)-solve(a-1,d)-solve(c-1,b);//容斥原理
		cout<<ans<<endl;
	}
	return 0;
}

```

其中求莫比乌斯函数用到了线性筛。
莫比乌斯函数性质：

(1) d=1  
u(d)=1

(2) d=p1*p2*p3*...*pk,其中pi为互异素数  
u(d)=(-1)^k

(3) 其他情况  
u(d)=0


---

