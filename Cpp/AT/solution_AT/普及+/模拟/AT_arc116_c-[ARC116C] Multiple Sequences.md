# [ARC116C] Multiple Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc116/tasks/arc116_c

整数 $ N $ , $ M $ が与えられます。 長さ $ N $ の整数列 $ A $ であって、以下の条件を満たすものの数を答えてください。

- $ 1\ \leq\ A_i\ \leq\ M\ \left(i\ =\ 1,\ 2,\ \ldots,\ N\right) $
- $ A_{i+1} $ は $ A_i $ の倍数 $ \left(i\ =\ 1,\ 2,\ \ldots,\ N\ -\ 1\right) $

ただし、答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $

### Sample Explanation 1

条件を満たす数列 $ A $ として、例えば以下のようなものが考えられます。 - $ A\ =\ \left(1,\ 1,\ 4\right) $ - $ A\ =\ \left(3,\ 3,\ 3\right) $ - $ A\ =\ \left(1,\ 2,\ 4\right) $

## 样例 #1

### 输入

```
3 4```

### 输出

```
13```

## 样例 #2

### 输入

```
20 30```

### 输出

```
71166```

## 样例 #3

### 输入

```
200000 200000```

### 输出

```
835917264```

# 题解

## 作者：cherry2010 (赞：4)

[ARC116C Multiple Sequences](https://www.luogu.com.cn/problem/AT_arc116_c)

计数题。这里主要详解利用**隔板法**计数的推导过程。

## 思路

若不断地枚举倍数以转移 dp 方程，时间复杂度为 $O(NM)$，超时。  
考虑将枚举倍数转为枚举最后一个数 $x$，继而转为枚举其质因子，分配质因子的指数使数组单调上升至 $x$。即：  
![](https://pic.imgdb.cn/item/66c491e5d9c307b7e9c9a123.png)  
由于 $M\leq 2\times 10^5$，每个数至多有6个质因数。

设 $x$ 的质因子 $a$ 指数为 $m$，将其分配至前 $n-1$ 个数可以抽象为：**将 $m$ 个数分配给 $n$ 个抽屉（第 0 位也算抽屉），抽屉可以留空，求方案数。**

> **隔板法模型：$\sum_{i=1}^n x=m(x>0)$，即求方程的正整数解个数，可以表示为 $C_{m-1}^{n-1}$。**
> ![](https://pic.imgdb.cn/item/66c4ad42d9c307b7e9f930fc.png)

将题目再做转换：$\sum_{i=1}^n x=m(x\geq0)$，即求方程的**非负整数解**个数。那么如果可以将非负整数解转为整数解处理，即可使用隔板法。

$$\begin{equation*}\sum_{i=1}^n x=m(x\geq0)\end{equation*}$$  
$$\begin{equation*}n+\sum_{i=1}^n x=n+m(x\geq0)\end{equation*}$$  
$$\begin{equation*}\sum_{i=1}^n (x+1)=n+m(x\geq0)\end{equation*}$$

此时 $x+1>0$，故可以用隔板法 $C_{n+m-1}^{n-1}$ 求出 $x+1$ 的正整数解数量，即 $x$ 的非负整数解数量。

枚举时统计答案即可。

## 代码

```
#include <bits/stdc++.h>
using namespace std;

namespace Cherry
{
	const int N=4e5+25;
	const long long mod=998244353;
	int n,m,num;
	long long sum,ans;
	long long fc[N],inv[N];
	
	long long ksm(long long x,long long k)
	{
		long long res=1;
		while(k)
		{
			if(k&1) res=(res*x)%mod;
			x=(x*x)%mod;
			k>>=1;
		}
		return res;
	}
	
	long long C(int x,int y)
	{
		if(y==0||x==y) return 1;
		return fc[x]*inv[x-y]%mod*inv[y]%mod;
	}
	
	int main() {
		scanf("%d%d",&n,&m);
		fc[0]=1;
		for(int i=1;i<=400020;i++) fc[i]=(fc[i-1]*i)%mod; //预处理阶乘
		inv[400020]=ksm(fc[400020],mod-2);
		for(int i=400020-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod; //预处理阶乘逆元 
		for(int i=1;i<=m;i++) //枚举最后一个数
		{
			int x=i;
			sum=1;
			for(int j=2;j*j<=i;j++) //枚举质因子
			{
				num=0; //统计质因子的指数
				while(x%j==0)
				{
					x/=j;
					num++;
				}
				sum=(sum*C(n+num-1,n-1))%mod; //隔板法计算答案
			}
			if(x>1) sum=(sum*n)%mod; //注意x本身为质数时需要额外计算
			ans=(ans+sum)%mod;
		}
		printf("%lld",ans);
		
		return 0;
	}
}

int main() {
	Cherry::main();
	
	return 0;
} 
```

---

## 作者：HomuraAkemi (赞：3)

Let $f_n(m)$ be the answer where the length of the sequence is $n$ and the last element of the sequence is $m$. Obviously, $f_1(m)=1$ holds.

Consider the transition. Obvious we have

$$f_i(m)=\sum_{d\mid m} f_{i-1}(d)$$

Namely, $f_i=f_{i-1}\ast 1$, where $\ast$ denotes **Dirichlet Convolution** and $1$ denotes constant function, namely, $1(n)=1$ holds for all $n\in \mathbb{Z}_{\ge 1}$. By implementating a $\Theta(m\log m)$ convolution for $n$ times, now we have a $\Theta(nm\log m)$ solution.

Recall a $\Theta(\log n)$ algorithm to calculate the $n$-th power of a number $a$. Similarly, one can use a $\Theta(n\log^2 n)$ algorithm to speed up the calculation (Bonus: why this is correct?), which is able to pass the problem in $\Theta(m\log m\log n)$. [implementation](https://atcoder.jp/contests/arc116/submissions/56148332).

Now we introduce a better solution. Obviously $1$ is a multiplicative function, thus $1\ast 1\ast \cdots \ast 1$ (we denote it as $1^n$) is a multiplicative function. By evaling the function in $p^k$, one can calculate the values of all points. For $p^k$, by definition, we want to calculate

$$\sum_{d_1d_2d_3\cdots d_n=p^k} 1$$

Namely, the number of ways of seperating $k$ balls into $n$ boxes (empty boxes are allowed). We all know the count is $\displaystyle {n+k-1\choose n-1}$.

[P4714](https://www.luogu.com.cn/problem/P4714) is a similar problem.

---

## 作者：bobo2007 (赞：3)

### 题意

求以下数列的**个数**：

1. 数列长度为 $n$。
2. $\forall a_i (2 \le i \le n),a_{i-1} \mid a_i$。
3. $\forall a_i(1 \le i \le n),a_i \le m$。

### 题解

可以发现数列一定是单调不降且成一种**阶梯状**，具体来说，当 $a_i \not = a_{i-1}$，时  $a_i$ 相对于 $a_{i-1}$ 起码增长了 $2$ 倍，由于值域大小的限制，整个序列相邻数字增长的次数**不会超过** $\log m$ 次。

于是我们考虑先忽略不相等的情况，即对于一个长度小于等于 $n$ 的序列，满足相邻两个数都**不相等**。显然这个序列的长度是小于等于 $\log n$ 的。

然后设  $f_{i,j}$ 表示序列长度为 $i$，序列的最后一个数字为 $j$，则有转移方程 

$$f_{i,j} = \sum _ {k | j , k \not = j} f_{i-1,k}$$

发现枚举约数有点不方便，考虑倒过来，枚举已知状态中 $j$ 的倍数 $k$，满足 $k \not = 1$ 且 $j \times k \le m$，将 $f_{i-1,j}$ 加到  $f_{i,j \times k}$ 上即可。

接着考虑有数字相等的情况，此时我们发现可以用**插板法**，如果把乘的倍数看作板子，将它们”插”进所有不同数列中的方案数之和即是答案，注意当序列中的数都相等的时候答案累加上 $m$，于是最终答案为.

$ans = m + \sum _ {i=2} ^ {min(n-1 , \log m)} \sum_{j=1} ^ {m} f_{i,j} \times \binom {n-1}{i-1}$

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define p 998244353ll
long long ksm(long long x,long long y)
{
	long long anss=1;
	while(y)
	{
		if(y&1) anss=anss*x%p;
		x=x*x%p;y=y>>1;
	}
	return anss;
}
int n,m,tot=0;
long long f[21][200010],fac[200010],inv[200010];
long long C(int x,int y){return (fac[x]*inv[y]%p)*inv[x-y]%p;}
int main()
{
	scanf("%d%d",&n,&m);
	int i,j,k;long long ans=m;
	fac[0]=inv[0]=1;
	for(i=1;i<=n;i++) fac[i]=1ll*i*fac[i-1]%p;
	inv[n]=ksm(fac[n],p-2);
	for(i=n-1;i>=1;i--) inv[i]=1ll*(i+1)*inv[i+1]%p;
	for(i=1;i<=m;i++) f[0][i]=1;
	for(i=1;i<=min(20,n-1);i++)
	{
		for(j=1;j<=m;j++)
			for(k=2;1ll*k*j<=1ll*m;k++)
				f[i][k*j]=(f[i][k*j]+f[i-1][j])%p;
		for(j=1;j<=m;j++)
			ans=(ans+f[i][j]*C(n-1,i)%p)%p;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：2huk (赞：2)

## Description

给定两个整数 $n, m$，问有多少个序列 $a_1 \dots a_n$ 满足：

- $1 \le a_i \le m$；
- $a_{i + 1}$ 是 $a_i$ 的倍数。

## Solution

一方面，如果 $x$ 是 $y$ 的倍数，那么对于同一个质数 $p$ 而言，$x$ 分解质因数后包含的 $p$ 的个数一定不少于 $y$ 的。也就是说若 $x = 2^{x_1} \times 3^{x_2} \times 5^{x_3} \times 7^{x_4} \times \cdots$，$y = 2^{y_1} \times 3^{y_2} \times 5^{y_3} \times 7^{y_4} \times \cdots$，那么有 $x_1 \ge y_1$，$x_2 \ge y_2$，$x_3 \ge y_3$，以此类推。

另一方面，因为 $a_n$ 是 $a_{n - 1}$ 的倍数，$a_{n - 1}$ 是 $a_{n - 2}$ 的倍数，所以 $a_n$ 也是 $a_{n - 2}$ 的倍数（同余的传递性）。同理可以推出所有 $i < j$ 都有 $a_j$ 是 $a_i$ 的倍数。

结合起来，若将每个 $a_i$ 质因数分解，即 $a_i = \prod p_{i, k}^{q_{i, k}}$，那么可以得到对于所有 $i < j$，都有 $q_{i, k} \le q_{j, k}$。

那么考虑从 $1$ 到 $m$ 枚举 $a_n$ 的值。若 $a_n = \prod p_{n, k}^{q_{n, k}}$。根据上面的结论，可以得到：
$$
0 \le q_{1, k} \le q_{2, k} \le q_{3, k} \le \dots \le q_{n, k}
$$
别忘了，我们正在枚举 $a_n$，所以上面的 $q_{n, k}$ 是已知的。

所以把字母变一下会得到这道题。接下来都在讨论这道题。

> 给定 $n, m$，问有多少个整数序列 $a_1 \dots a_n$ 满足 $\forall 1 < i \le n$，有 $0 \le a_{i - 1} \le a_i \le m$。

这里的做法很多，随便列两个（其实只会两个）：

1. 无脑推式子。很显然 $0 \sim m$ 共有 $m + 1$ 个数。直接枚举有多少个不同的数，然后就是划分序列，直接插板。答案为：
   $$
   \sum _{i = 1}^{m + 1} \dbinom {m + 1}n \dbinom {n - 1}{i - 1} = \sum _{i = 1}^{m + 1} \dbinom {m + 1}i\dbinom {n - 1}{n - i} = \dbinom {n + m}m
   $$

2. 想象一个网格图。初始 $i = 1, a_1 = 0$。我们从 $(1, 0)$ 出发，如果下走表示 $i \gets i + 1$，如果往右走表示 $a_i \gets a_i + 1$。不能向上或向左走。那么显然最终走到 $(n, j), j \le m$ 后的 $a_1 \dots a_n$ 即为一种可行的答案。为了方便，设立一个超级汇点 $(n + 1, m)$，那么答案即为从 $(1, 0)$ 走到 $(n + 1, m)$ 的方案数。显然为 $\dbinom{n + 1 - 1 + m}{m - 0} = \dbinom {n + m}m$。

回到原问题。由于 $q_{n, k}$ 是已知的，所以相当于只有 $n - 1$ 个未知数。所以在上面的式子里减一，即 $\dbinom {n - 1 + m}m$。

那么对于所有的质因子 $p_{n, k}$，我们都要计算这个答案。很显然根据乘法原理将每个质因子计算的答案相乘即可。

最后将枚举的 $a_n$ 的答案相加即为总答案。

## Code

[Submission #48335260 - AtCoder Regular Contest 116](https://atcoder.jp/contests/arc116/submissions/48335260)

---

## 作者：Shizaki_Crazy_Three (赞：1)

## [题目链接](https://www.luogu.com.cn/problem/AT_arc116_c)


### 思路

一道计数好题。  
首先正着想，不难发现一个 dp。
设 $dp_{i,j}$ 为第 $i$ 位为 $j$ 的方案数，根据 $j$ 的质因子来转移，时间复杂度 $O(NM)$，无法通过本题，这里不过多赘述。

正难则反，我们发现 $M$ 很小，因此我们可以枚举最后一位的最大值，根据题意，前面的数必然是最后一位数的因数。  
因此我们可以假设前面的数列都为 $1$，将最后一位的质因子分给前面的数。

设它第 $i$ 个质因数的个数为 $m$，则求将 $m$ 个数分到 $n$ 个位置上（不是 $n-1$ 是因为我们可以将质因数给抛弃，也就是放在第 $0$ 位），可空。  
根据[球盒问题](https://blog.csdn.net/black_horse2018/article/details/81557039)可知答案即为 $C_{n+m-1}^{n-1}$。

因为答案互不干扰，算出每一种情况加起来即可，时间复杂度 $O(M\sqrt{M})$。

### code


```cpp
#define LOCAL
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ll long long
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int> 
#define max(a,b) ((a)<(b)?(b):(a))
#define min(a,b) ((a)<(b)?(a):(b))
#define sort stable_sort
using namespace std;
using namespace __gnu_pbds;
namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline int read(double &x){return scanf("%lf",&x);}
            inline int read(long double &x){return scanf("%Lf",&x);}
            inline void dwrite(const double &x,int y=6,bool flag=1){printf("%.*lf",y,x),flag?putchar(' '):putchar(' ');}
            inline void dwrite(const long double &x,int y=6,bool flag=1){printf("%.*Lf",y,x),flag?putchar(' '):putchar(' ');}
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const char *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch[50];read(ch),x=ch;}
            inline void write(const string &x){int len=x.length();for(int i=0;i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>
            inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar(' ');}
            inline __int128 read(){static __int128 x;return read(x);}
            template<typename type>
            inline type put(type x,bool flag=1){write(x),flag?putchar(' '):putchar(' ');return x;}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;
const int N=4e5+5;
const int M=1e6+5;
const int inf=1e9+5;
const int mod=998244353;
int B=705;
int n,m;
ll a[N];
inline ll ksm(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1){
			res=(res*a)%mod;
		}
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}

ll fac[N],fac_inv[N];
inline ll C(int n,int m){
	if(m<=0||n==m){
		return 1ll; 
	}
	return fac[n]*fac_inv[n-m]%mod*fac_inv[m]%mod;
	
}

inline void init(int x){
 	fac[0]=fac[1]=1;
 	for(int i=1;i<=x;i++){
 		fac[i]=(fac[i-1]*i)%mod;
 	}
 	fac_inv[x]=ksm(fac[x],mod-2);
 	for(int i=x-1;i>=0;i--){
 		fac_inv[i]=(fac_inv[i+1]*(i+1))%mod;
 	}
}
inline void solve(){
    init(4e5);
    read(n,m);
    ll ans=0;
    for(int i=1;i<=m;i++){
    	ll res=1;
    	int num=i;
    	for(int j=2;j*j<=num;j++){
    		ll cnt=0;
    		while(num%j==0){
    			num/=j;
    			cnt++;
    		}
    		res=(res*C(n+cnt-1,n-1))%mod;
    	}
    	if(num>1)res=(res*n)%mod;
    	ans=(ans+res)%mod;
    }
    write(ans);
}

signed main()
{   
    int _=1;
    while(_--) solve();
    return 0;
}

```

---

## 作者：Nicrobot (赞：1)

提供一种不同的做法。

注意到原题意可以转换如下：一个初始全为 $1$ 的序列，每次可以选择一段后缀乘上一个质数，问最终能得到多少种序列。钦定按质数从小到大操作，可以发现一种操作方案对应一种序列。

考虑对于每个质因子枚举它出现多少次，由于因子之间是独立的，可以计算完再乘起来。每个质数对应的方案数直接插板计算即可，就是 $n + c-1\choose n-1$，$c$ 为选择的个数。直接 DFS 暴搜计算即可，由于是很多数相乘要小于一个数字，方案数就不会多。

实测跑得飞快，$n=m=5\times 10^6$ 只要不到 400ms。


提交记录：[link](https://atcoder.jp/contests/arc116/submissions/52191659)。

---

## 作者：李承轩 (赞：1)

**思路**

我们可以很好的想到一种 $O(nm)$ 的 dp:

状态：$dp_{i,j}$ 为搜到第 $i$ 个,最后一个数是 $j$ 的方案数。

转移：$dp_{i,j} = \displaystyle\sum_{k|j,k\not =j}dp_{i-1,k}$

当然这是会超时的。

我们换一种思路，我们先枚举最后一个数，再计算方案数。

这有个好处，我们缩小了前面的数的范围，必定是最后一个数的因数。

我们先分解最后一个数的质因数，统计每个质因数的指数，质因数不超过 $6$ 个。

然后我们将质因数分配给前面的数，这里的分配是指：假设我分配了 $2$ 给一个数，则这个数是前面的一个数乘 $2$。

这样避免了前面的数不满足条件。

将质因数分配给前面的数，相当于 $n$ 个小球,放进 $m$ 个盒子里，可以留空。

也就是 $\tbinom{m-1}{n+m-1}$ 。

最后将答案统计起来就好了

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+100,Mod=998244353;
int n,m,ans;
int fac[N+10],inv[N+10];
int qpow(int a,int b)
{
	int res=1;
	for(;b;a=a*a%Mod,b>>=1)
		if(b&1)res=res*a%Mod;
	return res;
}
int C(int n,int m){return n==m||m==0?1:fac[n]*inv[n-m]%Mod*inv[m]%Mod;}
signed main()
{
	scanf("%lld%lld",&n,&m);
	fac[1]=1ll;
	for(int i=2;i<=N;i++)fac[i]=fac[i-1]*i%Mod;
	inv[N]=qpow(fac[N],Mod-2);
	for(int i=N-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%Mod;
	for(int i=1;i<=m;i++)
	{
		int temp=i,tmp=1;
		for(int j=2,cnt=0;j*j<=temp;j++)
		{
			cnt=0;
			while(temp%j==0)cnt++,temp/=j;
			tmp=tmp*C(cnt+n-1,n-1)%Mod;
		}
		if(temp!=1)tmp=tmp*n%Mod;
		ans+=tmp,ans%=Mod;
	}
	cout<<ans;
}
```









---

## 作者：Jekyll_Y (赞：1)

# 题解

## 题目大意

给定 $n , m$， 求按以下要求构造的序列有多少个，对 $998244353$ 取模

- $1 \le a_i \le m$ 

- $a_i | a_{i + 1} (1 \le i < n)$

## 数据范围

$ 1\le n, m \le 2 \times 10 ^ 5$

## 解法

首先注意到 $m \le 2 \times 10 ^ 5$ ，分解后质因子数最多为 $6$ 个，然后考虑枚举最后一个数为多少，将其质因数分解，然后先计算每个质因数指数分配的情况然后相乘，这时候等价于在 $n$ 个不同的盒子中放 $m$ 个相同的小球，方案数为 $\dbinom{n +m - 1}{n - 1}$ ，然后将每个质因数的答案乘起来就好了。时间复杂度 $O(n \sqrt n)$ 。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 2e5 + 10;
const int mod = 998244353;

int n, m;

ll ans;

ll qpow(ll a, ll b)
{
    ll t = 1;
    while(b != 0)
    {
        if(b & 1)t = t * a % mod;
        a = a * a % mod; b >>= 1;
    }
    return t;
}

ll inv(ll x)
{
    return qpow(x, mod - 2);
}

ll fac[N + 100], ifac[N + 100];

ll C(int n, int m)
{
    if(n < m)return 0;
    return fac[n] % mod * ifac[m] % mod * ifac[n - m] % mod;
}

int main()
{
    scanf("%d%d", &n, &m);
    fac[0] = ifac[0] = 1;
    for(ll i = 1; i <= N + 99; i++)
        fac[i] = fac[i - 1] * i % mod;
    for(int i = 1;i <= N + 99; i++)
        ifac[i] = inv(fac[i]);
    for(int i = 1; i <= m; i++)
    {
        int x = i; ll mul = 1;
        for(int j = 2; j * j <= x; j++)
        {
            if(x % j != 0)continue;
            int sum = 0;
            while(x % j == 0)
                sum++, x /= j;
            mul = mul * C(n + sum - 1, n - 1) % mod;
        }
        if(x != 1)mul = mul * 1ll * n % mod;
        ans = (ans + mul) % mod;
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

显然有一个的 dp 式子，设 $dp_{i,j}$ 表示序列长为 $i$ 是最后一个数字为 $j$，式子为：

$$dp_{i,j}=\sum\limits_{x\mid k} dp_{{i-1},x}$$

时间复杂度显然无法通过，显然需要优化。

枚举因数显然是不行的，考虑反过来枚举倍数，可以发现最多枚举 $\log m$ 次。

这时转移为：

$$dp_{i,j\times k}=dp_{i,j\times k}+dp_{{i-1},j}$$

考虑序列中有数字相同的情况，这是一个插板法问题，相当于在不同的序列中插入乘的倍数的板子，共有 $\binom{n-1}{i-1}$ 种情况，注意整个序列全部相同的情况，要加上 $m$ 种。

此时的答案为：

$$m+\sum\limits_{i=1}^{20}\sum\limits_{j=1}^{m}\binom{n-1}{i-1}\times dp_{i,j}$$

20 为 $\log m$ 的大概数值。


### $\text{code}$


```cpp

int n,m;

int dp[21][maxn];

int fac[maxn],inv[maxn],a[maxn];

int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}

void init(){
	fac[0]=1;
	inv[0]=1;
	for(int i=1;i<=maxn-5;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn-5]=ksm(fac[maxn-5],mod-2);
	for(int i=maxn-6;i>=1;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int ans=0;

void solve(){
	init();
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		dp[0][i]=1;
	}
	ans=m;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=m;j++){
			for(int k=2;k*j<=m;k++){
				dp[i][j*k]=(dp[i-1][j]+dp[i][j*k])%mod;
			}
			ans=(ans+(dp[i][j]*C(n-1,i))%mod)%mod;
		}
	}
	write(ans%mod);
	puts("");
	return ;
}


```




---

## 作者：xz001 (赞：0)

- 首先我们可以转化一下，设 $p_i$ 表示 $a_i/a_{i-1}$，这里我们假设 $a_0=1$，问题便转化为了有多少个序列 $p$，满足所有元素之积小于等于 $m$。
- 我们可以枚举所有元素之和，然后将其分解质因数，由于质因数之间不会互相干扰，所以我们可以对于每个质因数，求其有多少种乘在 $p$ 数列上的方式。问题即为在 $n$ 个不同的盒子里放 $m$ 个相同小球的方案数，基本组合数学知识，答案为 $C_{n-1}^{m-1+n}$。每个数的答案即为每个质因子贡献的乘积。
- 求和即可。
- 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;

const int N = 5e6 + 10;

int inv[N], jc[N];

int ksm (int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}

int exgcd (int a, int b, int &x, int &y) { 
	if (b) {
		int d = exgcd (b, a % b, y, x);
		y -= a / b * x;
		return d;
	} 
	x = 1;
	y = 0;
	return a;
}

int C (int n, int m) {
	if (n < m) return 0;
	if (n == m) return 1;
	if (!m) return 1;
	return jc[n] * inv[m] % mod * inv[n - m] % mod;
}

int A (int n, int m) {
	if (n < m) return 0;
	if (n == m) return jc[n];
	if (!m) return 1;
	return jc[n] * inv[n - m] % mod;
}

int Lucas (int n, int m) {
	return n ? Lucas (n / mod, m / mod) * C (n % mod, m % mod) % mod : 1;
}

int Katelan (int n) {
	return ((C (n << 1, n) - C (n << 1, ~-n)) % mod + mod) % mod;
}

void init() {
	inv[1] = 1;
	jc[0] = 1;
	jc[1] = 1;
	for (int i = 1; i <= 1e6; ++ i) {
		jc[i] = jc[~-i] * i % mod;
//		int x = 0, y = 0;
//		exgcd (jc[i], mod, x, y);
//		x = (x % mod + mod) % mod;
//		inv[i] = x;
        inv[i] = ksm (jc[i], ~-(~-mod));
	}
	return;
}

int n, m, ans;

signed main() {
	init();
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; ++ i) {
		int x = i, sum = 1;
		for (int j = 2; j * j <= x; ++ j) {
			if (x % j == 0) {
				int cnt = 0;
				while (x % j == 0) x /= j, ++ cnt;
				sum = (sum * C (cnt - 1 + n, n - 1)) % mod;
			}
		}
		if (x > 1) sum = sum * n % mod;
		ans = (ans + sum) % mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

