# Counting Arrays

## 题目描述

Consider an array $ a $ of length $ n $ with elements numbered from $ 1 $ to $ n $ . It is possible to remove the $ i $ -th element of $ a $ if $ gcd(a_i, i) = 1 $ , where $ gcd $ denotes the greatest common divisor. After an element is removed, the elements to the right are shifted to the left by one position.

An array $ b $ with $ n $ integers such that $ 1 \le b_i \le n - i + 1 $ is a removal sequence for the array $ a $  if it is possible to remove all elements of $ a $ , if you remove the $ b_1 $ -th element, then the $ b_2 $ -th, ..., then the $ b_n $ -th element. For example, let $ a = [42, 314] $ :

- $ [1, 1] $ is a removal sequence: when you remove the $ 1 $ -st element of the array, the condition $ gcd(42, 1) = 1 $ holds, and the array becomes $ [314] $ ; when you remove the $ 1 $ -st element again, the condition $ gcd(314, 1) = 1 $ holds, and the array becomes empty.
- $ [2, 1] $ is not a removal sequence: when you try to remove the $ 2 $ -nd element, the condition $ gcd(314, 2) = 1 $ is false.

An array is ambiguous if it has at least two removal sequences. For example, the array $ [1, 2, 5] $ is ambiguous: it has removal sequences $ [3, 1, 1] $ and $ [1, 2, 1] $ . The array $ [42, 314] $ is not ambiguous: the only removal sequence it has is $ [1, 1] $ .

You are given two integers $ n $ and $ m $ . You have to calculate the number of ambiguous arrays $ a $ such that the length of $ a $ is from $ 1 $ to $ n $ and each $ a_i $ is an integer from $ 1 $ to $ m $ .

## 样例 #1

### 输入

```
2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4 2```

### 输出

```
26```

## 样例 #3

### 输入

```
4 6```

### 输出

```
1494```

## 样例 #4

### 输入

```
1337 424242424242```

### 输出

```
119112628```

# 题解

## 作者：xkcdjerry (赞：12)

很有意思的一道题，考虑怎么样的一个数列是 ambiguous 的：在删除过程中的任意一个时刻，同时存在两个合法的可删除数。

由于 $\gcd(a_1,1)=1$，所以 $a_1$ 一定在每一轮都可以删除，由此可得：

* 任何一个序列要么存在且仅存在一种删除顺序，要么是 ambiguous 序列，**不存在**一种序列不能以任何顺序完全删除 （记为 **(1)**）  
* 任何序列均可以通过每次删除第一个完全删除，若仅存在一种删除顺序这也是唯一的删除顺序 （记为 **(2)**）

正难则反，考虑如何求 unambiguous 序列个数：

由 **(2)**，在任意一轮，所有 $1 \leqslant x \leqslant |a|$ 均满足 $\gcd(a_x,x) \neq 1$。

又由于 unambiguous 序列每次均删除第一个，所以原先位置在 $x$ 的数会依次处于位置 $x,x-1,x-2,...,1$，又因为序列是 unambiguous 的，所以任意 $2 \leqslant i \leqslant x$ 都满足 $\gcd(a_x,i) \neq 1$。

由 $\gcd$ 的定义可知，上式等效于：对于任意 $2 \leqslant i \leqslant x$ 均存在 $j$ 使得 $j|i$ 且 $j|a_x$。（记为 **(3)**）

定义 $g_i=\prod^{p \in primes}_{2 \leqslant p \leqslant i} p$，则：

若 $i$ 为质数，由 **(3)** 得 $a_x$ 必须满足 $i|a_x$，即 $g_x|a_x$ 是序列为 unambiguous 的必要条件。

又由于任意 $\geqslant 2$ 的正整数均可表示为若干个不大于它的质数之积，所以若 $a_x$ 与所有 $\leqslant x$ 的质数不互质，那么显然也与所有 $\leqslant x$ 的和数不互质，即 $g_x|a_x$ 为序列为 unambiguous 的充分条件。

综上，对于所有 $2 \leqslant x \leqslant |a|$，均有 $g_x|a_x$ 为 $a$ 为 unambiguous 序列的充要条件。

又因为 $1 \leqslant a_i \leqslant m$，所以对于 unambiguous 序列 $a$，$a_x$ 有 $\lfloor \dfrac{m}{g_x} \rfloor$ 种取值（注意 $g_1=1$）。

由 **(1)**，长度为 $x$ 的 ambiguous 序列的个数为长度为 $x$ 的序列个数减去长度为 $x$ 的 unambiguous 序列个数，若令长度为 $x$ 的 unambiguous 序列个数为 $f_x$，则答案为 $\sum^{i \leqslant n}_{i=1} {m^i-f_i}$，其中 $f_x=\prod^{i \leqslant n}_{i=1} \lfloor \dfrac {m}{g_i} \rfloor$。

由于 $n \leqslant 3 \times 10^5$ 可以埃式筛 $O(n \log \log n)$ 预处理质数然后 $O(n)$ 求出 $g_i$ 和 $f_i$，最后边扫边乘 $O(n)$ 求出答案（如果使用快速幂会多一只 $\log$ 比较危险），总时间复杂度 $O(n \log \log n)$ 复杂度瓶颈在于筛质数（使用线性筛可以降低复杂度到 $O(n)$）。

注意事项：
* 因为 $m \leqslant 10^{12}$ 而且 `long long` 的最大值大概只有 $9 \times 10^{18}$ 所以要处处取模  
* 由于求 $f$ 时的除法是向下取整所以 $g$ 不能取模，但是由于直接乘会炸 `long long` 可以在 $g_i > m$ 的时候把 $g_i$ 置为 $m+1$（保证向下取整除依然为 $0$ 的前提下减小 $g_i$ 的值避免溢出）

代码（为了清晰度有删减）：
```c++
#include <cstdio>
#define ll long long
#define p 998244353
#define N 300010
ll n,m,f[N],g[N];
bool vis[N];
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=2;i<=n;i++) if(!vis[i])
        for(int j=i;j<=n/i;j++) vis[i*j]=true;
    f[1]=m%p,g[1]=1;
    ll tmp=m%p,ans=0;
    for(int i=2;i<=n;i++)
    {
        g[i]=vis[i]?g[i-1]:g[i-1]*i;
        if(g[i]>m) g[i]=m+1;
        f[i]=f[i-1]*((m/g[i])%p)%p;
        tmp=tmp*(m%p)%p;
        (ans+=tmp-f[i])%=p;
    }
    printf("%lld",ans<0?ans+p:ans);
}
```

2022/11/30：修改了一处笔误

---

## 作者：wind_seeker (赞：7)

~~蒟蒻太菜了，想了好久~~

难得手切，还是要来写一篇题解的。


## 正文

### 题意

- 定义一次操作为选取位置 $i$，如果 $\gcd(a_i,i)\ = 1$，则可以消除 $i$ 位置上的数，并将后面的数字整体左移，得到**空序列**结束，并同时得到操作序列。

- 称两种不同的操作序列**当且仅当**有**一次**操作所选位置不同，求长度 $1$ 到 $n$，并满足所有数字范围为 $[1,m]$ 的序列中有多少序列可拥有**至少两种**操作序列。

**首先先考虑题目的性质针对其性质进行转化。**

### 转化

经过观察，不难发现，对于一个长度**不小于 $2$ 的序列**，**当且仅当**每一位上的数字都满足 
$$\gcd(a_i,i)\ne 1,\gcd(a_i,i-1)\ne 1\dots\gcd(a_i,2)\ne 1$$
才会使得这个序列不合法，所以我们求出不合法的序列个数即可。

### 进一步转化

- **当 $a_i$ 包含 $2\sim i$ 所有数字所包含的所有质因子时，才可满足上述条件**

### 更进一步转化

- **当 $a_i$ 能被 $2\sim i$ 中所有质数整除时，方能满足上述条件。**

### code

```cpp
/* let life be like summer flowers	*/
/* by wind_seeker					*/
/* 2023-01-07 08:56					*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1e3,mod=998244353;

inline int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}

int n,m,sum=1,answer,ans,tot,fac[N];

int qpow(int a,int b){
	int res=1;
	for(;b;a=a*a%mod,b>>=1) if(b&1) res=res*a%mod;
	return res;
}

void init(){
	fac[0]=1;
	for(int i=1;i<=n+1;i++) fac[i]=fac[i-1]*(m%mod)%mod;
}

int prime[N],nopri[N],pcnt=0;
void get_prime(){
	for(int i=2;i<=n;i++){
		if(!nopri[i]) prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*prime[j]<=n;j++){
			nopri[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}

signed main(){
	n=read(),m=read();//小心 m 本身大于 mod
	init();get_prime();
	int inv=qpow((m-1)%mod,mod-2);
	answer=m%mod*((fac[n]-1+mod)%mod)%mod*inv%mod;
	if(m==1) answer=n;//特判1
	tot=m%mod;ans=(ans+tot)%mod;
	for(int i=2;i<=n;i++){
		if(!nopri[i]) sum=sum*i;
		if(sum>m) break;
		tot=tot*((m/sum)%mod)%mod;//tot表示长度为 i 的不合法的序列
		ans=(ans+tot)%mod;
	}
	printf("%lld\n",(answer-ans+mod)%mod);
	return 0;
}

```

**蒟蒻拙见**


---

## 作者：DYYqwq (赞：1)

这题模拟赛场切了，发篇题解纪念一下。

首先我们发现一个很重要的性质，即 $b$ 序列必然有解。因为一直取 $a$ 数组中的第一个数就可以了嘛！

那这样我们考虑正难则反。我们思考有多少个好的序列。

它是好的序列当且仅当每一次我们都只能选 $a$ 数组中的第一个。那么发现第 $i$ 个数字随着前面的数不断被选择，它的排名也逐渐靠前，但是它的排名不到 $1$ 的时候，自己的权值和排名必须不能互质！因此第 $i$ 个元素必然是 $k \times \operatorname{lcm}(2,3,\dots,i-1,i)$，且 $k \in \N^+$，自然，不能让这个数超过 $m$。

于是自然可以对于每一个 $i$，统计其 $k$ 的可能数量，乘法原理乘起来即可。

但是不要忘记我们是算的好的序列数量，所以答案要用总数减一下。

具体看代码。赛时代码，注释较多。

```cpp
#include<bits/stdc++.h>
#define int long long
//typedef __int128 i128;
using namespace std;
const int mod = 998244353;
int n , m , lcm[300010] , ans , cnt , now = 2;
bool flag = false , op[300010] , flagg[300010];
int fast_mi(int x , int y)
{
	int ans = 1 , qwq = x;
	while(y)
	{
		if(y & 1) ans *= qwq , ans %= mod;
		y >>= 1 , qwq *= qwq , qwq %= mod;
	}
	return ans;
}
void get_prime(int x)
{
	for(int i = 1 ; i <= sqrt(x) ; i ++)
	{
		if(x % i == 0)
		{
			if(!flagg[i])
			{	
				if(!op[i] && flag == false) op[i] = 1 , now *= i;// , printf("now::%lld i::%lld\n" , now , i);
				if(now > m) flag = true;
			}
			if(!flagg[x / i])
			{
				if(!op[x / i] && flag == false) op[x / i] = 1 , now *= x / i;// , printf("now::%lld x / i::%lld\n" , now , x / i);
				if(now > m) flag = true;
			}
		}
	}
}
void gett_prime()
{
	for(int i = 2 ; i <= n ; i ++)
	{
//		if(!flagg[i]) prime[++ cnt] = i;
		if(flagg[i]) continue;
		for(int j = 2 ; j * i <= n ; j ++) flagg[j * i] = 1;
	}
}
signed main()
{
//	freopen("Node_Pairs.in" , "r" , stdin);
//	freopen("Node_Pairs.out" , "w" , stdout);
	op[2] = 1 , flagg[1] = 1;
	scanf("%lld%lld" , &n , &m);
	gett_prime();
//	for(int i = 1 ; i <= n ; i ++) if(!flagg[i]) printf("prime:%lld\n" , i);
	int awa = 0;
	for(int i = 1 ; i <= n ; i ++) awa += fast_mi(m % mod , i) , awa %= mod;
//	printf("awa:%lld\n" , awa);
	int lst = m % mod , ans = m % mod;
	for(int i = 2 ; i <= n ; i ++)
	{
		if(flag == false)
		{
			if(i == 2) op[2] = 1 , now = 2ll;
			else if(i == 3) op[3] = 1 , now = 6ll;
			else get_prime(i);
		}
		if(now > m) flag = true;
		if(flag == false){
			ans += lst * ((m / now) % mod) % mod , ans %= mod ;
//			printf("i:%lld lst * (m / now):%lld\n" , i , lst * ((m / now) % mod) % mod);
//			if(lst * ((m / now) % mod) % mod < 0)
//			{
//				printf("Pizar:i:%lld lst * (m / now):%lld (m / now):%lld lst:%lld\n" , i , lst * ((m / now) % mod) % mod , m / now % mod , lst);
//			}
			lst *= ((m / now) % mod) , lst %= mod;
//			assert(((m / now) % mod) >= 0);
//			assert(((m / now) % mod) < mod);
		}
		
		if(flag == true) break;
//		printf("i:%lld now:%lld\n" , i , now);
	}
//	if(flag == true) printf("i am sb\n");
	printf("%lld" , (awa - ans + mod) % mod);
	return 0;
}
// 300000 1000000000000
```

---

## 作者：__Creeper__ (赞：1)

### 题目大意
- 给定一个数组 $a$,选择个数 $i$，若 $\gcd(a_{i}, i) = 1$,我们就可以将当前的第 $i$ 位上的数字 $a_{i}$ 移除掉，而后面的数字会以此补上空缺，这称为一次操作。

- 定义一个序列 $b$ 为一个“移除序列”，当且仅当我们可以通过依次选取 $b_{1}$ 到 $b_{n}$，进行上面所说的操作，最终将整个 $a$ 数组移除。

- 定义一个数组 $a$ 是不好的，当且仅当其有不止一个移除序列。你需要统计出长度为 $[1,n]$ 范围内正整数的，各元素为 $[1,m]$ 范围内正整数的不好的序列的个数，取模 $998244353$。

### 思路
这道题因为删除 $a_{i}$ 后，$a_{i+1}$ 至 $a_{n}$ 会整体向左移一位，如果直接去求满足条件的个数会非常麻烦，可以转坏为求不满足条件的个数。

#### 第一步转换
- 对于长度大于等于2的序列，每一位上的数字都满足 $\gcd(a_{i}, i) ， \gcd(a_{i}, i-1) \dots \gcd(a_{i}, 2)\neq 1$ 才会使得这个序列不合法，所以我们求出不合法的序列个数即可。

#### 第二步转换
- 当 $a_{i}$ 能被 $2 \sim n$ 的质因子整除，及能被 $2 \sim n$ 所有质数整除。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 1000, mod = 998244353;
int n, m, pr[N], p[N], fc[N], cnt, sum = 1;
int maxx, inv, tot, ans;

int power ( int a, int b )
{
	int mul = 1, ans = a;
	while ( b )
	{
		if ( b & 1 == 1 )
			mul = mul * ans % mod;
		ans = ans * ans % mod;
		b >>= 1;
	}
	return mul;
}

void prime ()
{
	for ( int i = 2; i <= n; i++ )
	{
		if ( !p[i] ) pr[++cnt] = i;
		for ( int j = 1; j <= cnt && i * pr[j] <= n; j++ )
		{
			p[i * pr[j]] = 1;
			if ( i * pr[j] == 0 ) break;
		}
	}
}

void init ()
{
	fc[0] = 1;
	for ( int i = 1; i <= n + 1; i++ ) fc[i] = ( fc[i-1] * ( m % mod ) ) % mod;
}

signed main()
{
	cin >> n >> m;
	init();
	prime();
	inv = power ( ( m - 1 ) % mod, mod - 2 );
	maxx = m % mod * ( ( fc[n] - 1 + mod ) % mod ) % mod * inv % mod;
	if ( m == 1 ) maxx = n;
	tot = m % mod;
	ans = ( ans + tot ) % mod;
	for ( int i = 2; i <= n; i++ )
	{
		if ( !p[i] ) sum = sum * i;
		if ( sum > m ) break;
		tot = tot * ( ( m / sum ) % mod ) % mod;
		ans = ( ans + tot ) % mod;
	}
	cout << ( maxx - ans + mod ) % mod;
	return 0;
}
```

---

## 作者：mango2011 (赞：1)

其实这又是一道诈骗题（话说怎么俄罗斯人那么喜欢诈骗题）。

首先，我的主观感受就是这个“不好的序列”非常难求，所以考虑先统计出所有“好的序列”的总数 $M_1$，然后用序列总数 $M_2$，减去 $M_1$ 得到答案。

那么，我们考虑怎样的序列是好的：

1) 我们惊奇的发现：$b_i=1(1\le i\le n)$ 显然是一种合法的“操作序列”，这意味着，除此之外，没有别的操作序列了。

2) 没有别的操作序列，与数列中的任意一个数 $a_i(2\le i\le n)$，都有 $\gcd(a_i,i)>1$ 等价。

3) 任意时刻，$2$ 均成立。

以上，我们就得到了“好的序列”的充分必要条件。

我们考虑总结 $2$ 和 $3$，我们发现：

对于任意的 $i(1\le i\le n)$，对于任意的 $j(2\le j\le i)$，均有 $\gcd(a_i,j)>1$，这是因为任意时刻 $2$ 均成立。

有了上面的充要条件，我们考虑开始统计“好的序列”的个数：

假设 $a$ 的长度为 $i$ 时，已经满足条件。

考虑插入新的数 $a_{i+1}$：

$a_{i+1}$ 的选法数量为满足 $2\le j\le i,\gcd(j,k)>1$ 的 $k$ 的数量。我们发现统计 $2\sim m$ 之间所有质数的乘积即可。

不妨设这个乘积为 $M$，则 $a_{i+1}$ 的选法总数为 $\frac{m}{M}$。

实现的时候，对于每一个 $i\le n$ 统计答案，并开一个临时计数器 $temp$，一旦遇到 $M>m$，则终止程序，输出答案。

综上，我们就得到了最优解。

此外，文中有一些“显然”，读者可以自行替换成“证明”。

谢谢观看！

---

## 作者：Allanljx (赞：1)

## 思路
考虑容斥，不 ambiguous 的 $a$ 数组的数量就是所有 $a$ 数组的数量减去 ambiguous 的 $a$ 数组的数量。所有 $a$ 数组的数量是 $\sum_{i=1}^n m^i$，所以现在要求的变成了 ambiguous 的 $a$ 数组的数量。不难发现，所有序列一定存在一种删法是每次删第一个数，所以每个 ambiguous 的序列要满足 $\forall_{i>1},\forall_{1<j\leq i},\gcd(a_i,j)>1$，也就是说所有 $a_i$ 应该被所有小于 $i$ 的质数整除，相当于被所有小于 $i$ 的质数的乘积整除，设小于 $i$ 的质数的乘积是 $x$，那么这个位置能放的数有 $\left\lfloor\dfrac{m}{x}\right\rfloor$ 个，注意一下 $x$ 如果大于 $m$ 就说明不管放什么数都会是不 ambiguous 的。

具体实现细节见代码。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int vis[300005];
const int mod=998244353;
__int128 tmp=1;
int ans1;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	vis[1]=1; 
	for(int i=2;i<=300000;i++)//筛质数
    {
    	if(vis[i]) continue;
    	for(int j=i*i;j<=300000;j+=i) vis[j]=1;
    }
	cin>>n>>m;
	for(int i=1;i<=n;i++)//计算所有a数组的数量，要开__t128
	{
		tmp*=m;
		tmp%=mod;
		ans1=(ans1+tmp)%mod;
	}
	int ans=1,sum=1;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]&&sum<=m) sum*=i;//是质数
		if(sum>m) ans=0;//必然是不ambiguous的
		else ans=ans*((m/sum)%mod)%mod;
		ans1=(ans1-ans+mod)%mod;
	}
	cout<<ans1<<endl;
}
```

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17649869.html)

> 给定一个数组 $a$，同时给定一个操作：选取一个数字 $i$，如果 $\gcd(a_i,i) = 1$，我们就可以将**当前**的第 $i$ 位上的数字 $a_i$ 移除掉，而后面的数字会以此补上空缺。
>
> 定义一个序列 $b$ 为一个“移除序列”，当且仅当我们可以通过依次选取 $b_1$ 到 $b_n$ 进行上面所说的操作，最终将整个 $a$ 数组移除。
>
> 定义一个数组 $a$ 是不好的，当且仅当其有不止一个移除序列。你需要统计出长度为 $[1,n]$ 范围内正整数的，各元素为 $[1,m]$ 范围内正整数的不好的序列的个数，模 $998244353$。
>
> $n \le 3 \times 10^5$，$m \le 10^{12}$。

~~题意是抄翻译的请见谅。~~

首先一个序列最少也会有一个删除序列，因为可以把下标 $1$ 对应的数一个一个删掉。题目中规定一个数 $a_i$ 可以在位置 $i$ 被删掉，当且仅当 $a_i \perp i$，然后一个关键观察是，在原数组中位置为 $i$ 的数，如果没有被途中删除的话，那么在删除过程中一定会经过 $[1, i]$ 的所有位置，那么我们发现，一个数不能在途中被删掉，当且仅当对于任意 $j \in [2, i]$，都有 $a_i \not \perp j$，即 $\gcd(a_i, j) \not = 1$。

正难则反，将问题转化为求好的方案数。由上边的分析我们得到，一个序列是好的，当且仅当对于任意 $2 \le j \le i \le n$，都有 $\gcd(a_i, j) \not = 1$，也就意味着 $a$ 中的所有数都只能在位置 $1$ 被删掉，也就只有一种删除序列了。通过算数基本定理，满足对于所有 $i \in [2, n]$ 的 $i$，满足 $\gcd(x, i) \not = 1$ 的最小 $x$ 为 $[2, n]$ 中所有出现过的质因子的乘积（每个只乘一次）。那么位置 $i$ 上满足上述条件的数的个数就等于 $\lfloor \dfrac{m}{\prod_{j \in \mathbb{P} \land j \le i} j} \rfloor$。那么根据乘法原理，直接对 $[1, n]$ 累乘即可得到好的序列的个数。

因为 $m$ 太大了可能会出现 `long long` 溢出，因此需要龟速乘。时间复杂度线性对数。

[代码](https://codeforces.com/contest/1749/submission/219920110)。

---

## 作者：zhangxiaohan007 (赞：0)

## 大致题意
给定数组长度和元素大小的范围，求有多少符合要求的数组。（符合要求的数组的定义不再赘述。）
## 思路
直接硬做肯定不行，总不可能全都枚举一遍。正难则反，我们不妨换个思路，枚举不符合条件的，最后再用总数将其减去即可。

明确了目标，接下来要去实现。我们不难发现，如果一个序列不满足要求，当且仅当所有 $\gcd(a _ {i},i) , \gcd(a _ {i},i-1) \cdots \gcd(a _ {i},2)$ 都不等于 $1$ 时成立。所以对于每个 $a _ {i}$，它要被 $2$ 到 $i$ 所有质数整除才能满足上述条件。

## 注意事项
+ $m$ 不要忘了开 ```long long```。
+ 因为 $m$ 特别大，所以答案要边做边取模。

---

## 作者：aeiouaoeiu (赞：0)

首先发现一个数组至少有一个消除序列，即从首位不断删除元素，那么一个不好的数组 $a$ 应该存在一两个数 $2\le x\le y \le n$（$n$ 表示数组长度），使得 $\gcd(a_y,x)=1$。

设 $f_i$ 为长度为 $i$，由 $[1,m]$ 范围内的整数构成的不好的数组个数，则题目答案为 $\sum_{i=1}^{n}f_i$ 且显然有 $f_1=0$。

考虑如何从 $f_{i-1}$ 转移到 $f_i$：

- 如果一个长度为 $i-1$ 的数组是不好的，那么这个数组后可以加上任意一个 $[1,m]$ 范围内的整数。
- 如果一个长度为 $i-1$ 的数组是好的，那么这个数组后可以加上一个至少与 $[2,i]$ 中一个整数互质的，$[1,m]$ 范围内的整数。

可以得出 $f_i=mf_{i-1}+g_i(m^{i-1}-f_{i-1})$，其中 $g_i$ 为在 $[1,m]$ 范围内且至少与 $[2,i]$ 中一个整数互质的整数的数量。

由于一个整数可以拆分为若干个质数之积，我们可以进一步地把 $g_i$ 定义为在 $[1,m]$ 范围内且至少与 $[2,i]$ 中一个质数互质的整数的数量。

如何求出这个数量呢？考虑反向。设小于等于 $i$ 的全体质数的积为 $h_i$，由于质数两两互质，与其（指质数）不互质的数必然为 $h_i$ 的倍数，则 $g_i=m-\lfloor\frac{m}{h_i}\rfloor$。

还有一个小优化：$h_i$ 在 $i\ge 41$ 时会超过 $10^{12}$（$m$ 的上限），此时 $g_i=m$（事实上会导致 $f_{i+1}=m^{i+1}$ 使得往后的 $g_i$ 没有贡献），我们不需要额外计算 $i\ge 41$ 时 $g_i$ 的值。

最后一点：``__int128`` 在 CF 要用 C++20。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef __int128 dll;
typedef long double db;
const int maxn=300007;
const dll inf=1000000005ll,p=998244353;
ll n,m,ans;
ll pri[50]={0,2,3,5,7,11,13,17,19,23,29,31,37,41},vis[maxn],sum[50];
dll f[maxn],val[maxn],pw[maxn],now;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n>>m;
		sum[0]=pw[0]=1;
		for(int i=1;i<=18;i++) sum[i]=sum[i-1]*pri[i],vis[pri[i]]=1;
		for(int i=1;i<=n;i++) pw[i]=pw[i-1]*m%p;
		for(int i=2;i<=41;i++){
			if(vis[i]) now++;
			val[i]=m/sum[now];
		}
		for(int i=2;i<=n;i++) f[i]=(m*f[i-1]%p+(m-val[i])*(pw[i-1]-f[i-1]+p)%p)%p,ans=(ans+f[i])%p;
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：CENRUIYANG (赞：0)

首先发现当 $b_i$ 全部都为 $1$ 的时候一定满足条件，所以所谓 $\texttt{ambiguous array}$ 就是除了这种方式以外还有至少一种方式满足条件的数列，发现我们可以在 **进行了若干次（可以为 $0$）的 $1$ 操作** 之后进行任意一个 **非 $1$ 操作**，然后一直进行 $1$ 操作就可以了。

发现正着统计难以排除重复情况，考虑补集转换。只需要保证在进行了 **任意次 $1$ 操作后** 都没有其余可操作位置即可。所以 $i$ 这个位置的数必须满足 **$a_i$ 是 $[1,i]$ 中每一个质数的积的整数倍。** 也就是说，定义 $\le i$ 的质数之积为 $mul_i$ ，那么可以填在 $i$ 这个位置的数的数量是 $\lfloor\frac{m}{mul_i}\rfloor$ 。

注意 $m$ 不能直接 $\bmod\ p$ ，要开 `long long` ，当计算到 $mul_i \ge m$ 就可以 `break` 了。

[代码在此处。](https://codeforces.com/contest/1749/submission/180198357)

---

