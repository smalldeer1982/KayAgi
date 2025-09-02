# Omkar and Last Class of Math

## 题目描述

In Omkar's last class of math, he learned about the least common multiple, or $ LCM $ . $ LCM(a, b) $ is the smallest positive integer $ x $ which is divisible by both $ a $ and $ b $ .

Omkar, having a laudably curious mind, immediately thought of a problem involving the $ LCM $ operation: given an integer $ n $ , find positive integers $ a $ and $ b $ such that $ a       + b = n $ and $ LCM(a, b) $ is the minimum value possible.

Can you help Omkar solve his ludicrously challenging math problem?

## 说明/提示

For the first test case, the numbers we can choose are $ 1, 3 $ or $ 2, 2 $ . $ LCM(1, 3) = 3 $ and $ LCM(2, 2) = 2 $ , so we output $ 2 \ 2 $ .

For the second test case, the numbers we can choose are $ 1,       5 $ , $ 2, 4 $ , or $ 3, 3 $ . $ LCM(1, 5) = 5 $ , $ LCM(2, 4)       = 4 $ , and $ LCM(3, 3) = 3 $ , so we output $ 3 \ 3 $ .

For the third test case, $ LCM(3, 6) = 6 $ . It can be shown that there are no other pairs of numbers which sum to $ 9 $ that have a lower $ LCM $ .

## 样例 #1

### 输入

```
3
4
6
9```

### 输出

```
2 2
3 3
3 6```

# 题解

## 作者：lingfunny (赞：4)

前言：此解法代码较简单，时间复杂度和另一位大佬的预处理时间复杂度相同，所以相较会更快。
## 题意简述
给定一个正整数 $n$，当正整数 $a,b$ 满足 $a+b=n$ 且 $LCM(a,b)$ 最小时， $a,b$ 的值分别是多少。
## 解法
时间复杂度 $\mathcal{O(T\sqrt{n})}$ 。

先说结论吧，先把 $n$ 进行质因数分解，找到最小的因数`minp`，直接`printf("%d %d\n", n/minp, n-n/minp)`即可。

### 证明：
首先不妨设 $a\le b$ 。

对于任意数 $n$ ，一定可以拆分为 $1$ 和 $n-1$，因为 $LCM(1,n-1) = n-1$ ，所以至少有一个解是 $n-1$ ，所以最终的答案的 $LCM$ 一定在 $[1,n-1]$ 。

因为 $LCM(a,b)\le n-1$ ，则 $a,b$ 一定存在倍数关系，即 $LCM(a,b)=b$ 。

为什么呢？

如果 $a,b$ 不存在倍数关系：

把 $a,b$ 质因数分解，因为不存在倍数关系，所以 $a$ 必然有 $b$ 没有的质因数，因为质因数最小为 $2$ ，所以 $LCM(a,b) \ge2b$ 。
$$\because b\ge a,a=n-b$$
$$\therefore b\ge n-b$$
$$\therefore 2b\ge n$$
$$\text{即 }LCM(a,b) \ge n$$
与 $LCM(a,b)\le n-1$ 不符，所以 $a,b$ 必然存在倍数关系。

既然存在倍数关系，接下来就好办了。因为 $LCM(a,b)=b$ ，所以只需要找到 $b$ 最小能取多少即可。不妨设 $b=ka(k\ge1)$ ，显然可以得到 $(k+1)a=n$ ，转换一下就可以得到 $a=\frac{n}{k+1}$ ，再转换下，可以得到 $b=\frac{nk}{k+1}$ 。因为这里的 $n\ge2$ ， 所以 $nk\ge2k$ ，正常人都看得出来， $k$ 越大 $b$ 就越大，所以只要 $k$ 取最小值就可以求出答案了。

但是不要忘记 $a$ 是一个整数， 而 $a=\frac{n}{k+1}$ ，所以 $k+1$ 应是 $n$ 的因数，而 $k+1\ge2$，所以只需要找到 $n$ 的最小质因数`minp`，`minp`的值即为 $k+1$。

相应的：
```
a = n/(k+1) = n/minp
b = n - a
```
这就是开头的那个式子了。

## 代码
```cpp
#include <cstdio>
int T;
int main(){
	scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		int key = n;
		for(int i=2;i*i<=n;++i)
		if(n%i == 0){
			key = i;
			break;
		}
		printf("%d %d\n", n/key, n-n/key);
	}
	return 0;
}
```

---

## 作者：Allen_lml (赞：2)

**思路简述**

其实就是一个素数筛问题，以朴素筛法为例，从2枚举到  $\sqrt{n}$，第一个出现的因子就是需要输出的两个数的*gcd*（最大公约数）啦。

### AC代码（有点丑QAQ）

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int t,n;
int a,b;

void LCM(int k)
{
	a=0,b=0;
	for(int i=2;i*i<=k;i++)
		if(!(k%i))
		{
			a=k/i;
			b=k-a;
			return ;
		}	
	a=1,b=k-a;
	return ;
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		LCM(n);
		printf("%d %d\n",a,b);
	}
	return 0;
}
```


### 朴素筛法

只需从2枚举到$\sqrt{n}$就可

**为什么从2枚举到$\sqrt{n}$就能找出所有因子呢**

如果n=1，显然不是。

不妨假设有一个因子大于$\sqrt{n}$，那么n/$\sqrt{n}$一定是n的一个因子，且必然小于$\sqrt{n}$。既然该因子已经小于$\sqrt{n}$了，那么它必然在之前已经枚举过，所以$\sqrt{n}$在之前已经找到

这是代码

~~不会吧，不会真的有哪个小可爱不会吧？~~

```cpp
bool isprime(int n)
{
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
            return false;
    return true;
}
```


时间复杂度为**O($\sqrt{n}$)**

### 埃氏筛

这里再复习一下埃氏筛：

**埃拉托斯特尼筛法**，简称**埃氏筛**或**爱氏筛**

是一种由希腊数学家埃拉托斯特尼所提出的一种简单检定素数的算法。

*要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。*——百度百科

埃氏筛的时间复杂度为**O（n*lglgn）**，具体证明较复杂，感兴趣可自行*BFS*

下面给出埃氏筛的代码

```cpp
void primeSelect(int n)
{
    memset(prim,true,sizeof prim);
    prim[0]=prim[1]=false;
    for(int i=2;i*i<=n;i++) //筛到sqrt n即可
        if(prim[i])
            for(int j=i*2;j<=n;j+=i) //从i*2开始，将i的倍数打上标记
                prim[j]=false;
}
```

### 线性筛（欧拉筛）
~~线性筛-->xxs--> ？~~

因为埃氏筛会重复对一个数打标记，所以会浪费一些时间，比如：

15被3打了一次标记，又被5打了一次标记

```cpp
for(int i=2;i<=maxn;i++)
    {
        if(!vis[i]) //没访问过的就是素数
            prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=maxn;j++) //遍历每一个已找到的素数
        {
            vis[i*prime[j]]=true;
            if (i%prime[j]==0) //每个数只被它的最小质因子筛一次
                break;
        }
    }
```
此外还有Miller-Rabin这种判断大素数的办法，这里就不展开了~~毕竟这题太水~~


---

## 作者：Werner_Yin (赞：1)

# 题目
[传送门](https://codeforces.com/contest/1372/problem/B)
## 题意
给出 $n$,输出 $a$ ,$b$ ($0 < a \leq b < n$),使$a+b=n$且 $\operatorname{lcm}(a,b)$ 最小。

# 思路
## 前言
[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13286923.html)

![](https://cdn.luogu.com.cn/upload/image_hosting/js977t4j.png)
如果你没有到现场，你永远也不会体验到cf 的 ```OI```赛制有多强，评测队列曾超过```15min```，不得不让此次比赛```unrated```。

![](https://cdn.luogu.com.cn/upload/image_hosting/abgrwq1n.png)

但是，我也不知道怎么B、C题提交把语言选成了：```C11``` ,然后在20分钟后完美地```CE``` 了。
## 声明

lcm : 最小公倍数

minn : n 的最小质因数

mul : n 的最大 $\neq n$ 的约数


## 分析
我们首先找出使 $\operatorname{lcm}(a,b)$ 最小的 $a$,$b$。

$\because \operatorname{lcm}(a,b)=\frac{a\times b}{\gcd(a,b)}$ , 

$\therefore$ 我们可以找到 $n$ 最小的质因数 $minn$ ，再找到 $n$ 最大的约数（$\neq n$）$mul=\frac{n}{minn}$。

1. 当 $n$ 为合数时，我们令答案为 $mul$ , $(minn-1)\times mul$。

1. 当 $n$ 为质数时，我们令答案为 $1$ , $n-1$。

输出即可。

## 正确性
### 证1
**证：**当 $n$ 为质数， $k_1=1$ 时 ，$\operatorname{lcm}(k_1,n-k_1)$ 最小

首先，设 $k_1 > 0$,$k_2=n-k_1$,且$k_1<k_2$。

$\because$ $n$ 为质数，$\gcd(k_1,k_2) = 1$,

$\therefore$ $\operatorname{lcm}(k_1,k_2)=k_1\times (n-k_1)$

当 $k_1 = 1$ ,$\operatorname{lcm}(k_1,k_2)=n-1$

若 $k_1 = 1 + h$($1\leq h\leq \frac{n}{2}$) ,则 

$\operatorname{lcm}(k_1,k_2)=(1+h)\times (n-1-h) = n - 1 +h \times (n-2-h) > n - 1$

$\therefore$ 当 $n$ 为质数时，$\operatorname{lcm}(1,n-1)$ 最小。

当然也可以表述为：当 $n$ 为质数， $a=1$ 时 ，$a\times (n-a)$ 最小

类似地，我们也可证明： $a=1$ 时 ，$a\times (n-a)$ 最小

我们已经证明了情况```2```。

### 证2
证：当 $n$ 为合数, $k_1=mul$ 时，$\operatorname{lcm}(k_1,n-k_1)$ 最小


首先，设 $k_1 > 0$,$k_2=n-k_1$,且$k_1<k_2$ ， $q = \gcd(k_1,k_2) > 1$。

令 $n=g \times q$ , $k_1=g_1 \times q$ ，$k_2 = g_2\times q$ ,  $g_1+g_2 =g$


$\operatorname{lcm}(k_1,n-k_2)=\frac{k_1 \times (n-k_1)}{q} = g_1\times q \times g_2$ 


$\therefore$ 当 $g_1=1$ , $g_1\times g_2$ 最小,

$\therefore \operatorname{lcm}(k_1,n-k_2)=g_1\times q \times g_2 \geq (g-1)\times q =n - q$ (仅当 $k_1 = q$ 等号成立）

我们再让 $q$ 取最大为 $mul$ 即可让$\operatorname{lcm}(k_1,n-k_2)$ 最小 ，此时 $k_1=mul$

**证明完毕（如有漏洞请轻喷)**

## 算法
先~~用线性筛~~筛出```1e5```以内素数，方便找答案。

再一个个枚举素数，找到最小的质因子（如果有），判断情况（如果找不到 $n$ 就肯定是素数），输出答案。

# 代码
~~请勿copy，直接抄你会爆零的~~
```cpp
/* 
	* Author :Werner_Yin 
	* Time: 2020-07-11 23:20:15
	* I believe I can AC !
*/ 
#include <bits/stdc++.h>
#define lol long long
#define GDB(x) cout<<"DATA "<<#x<<" :"<<x<<endl; 
#define mes(x) memset(x,0,sizeof(x))
using namespace std;
template <typename T>
void re(T &x){
	#define ge getchar() 
	x = 0;int sgn = 1;char ch = ge;
	for(;!isdigit(ch);ch = ge) if(ch == '-') sgn = -1;
	for(;isdigit(ch);ch = ge) x = (x<<1)+(x<<3)+(ch^48);
	x *= sgn;
}
template <typename T>
void write(T x){
	if(x == 0) putchar(48);
	else if(x < 0) putchar('-');
	int k = 0,que[20];
	while(x > 0){
		que[++k]=x % 10;
		x /= 10;
	}
	for(int i = k;i > 0;i--) putchar(que[i] + 48);
	return;
}
const int MAXN = 1e5 + 10;
int PrimeNum = 0,Prime[MAXN];
bool IsNotPrime[MAXN];
void shai (){
	for(int i = 2;i < MAXN;i++){
		if(!IsNotPrime[i]){
			Prime[PrimeNum++] = i;
		}
		for(int j = 0;j < PrimeNum && Prime[j] * i < MAXN;j++){
			IsNotPrime[Prime[j] * i] = 1;
			if(i % Prime[j])break;
		}
	}
}

int main (){
	shai();
	int T;
	re(T);
	while(T--){
		int n;
		re(n);
		int minn = -1;
		for(int i = 0;i < PrimeNum ;i++){
			if(n % Prime[i] == 0){
				minn = Prime[i];
				break;
			}
		}
		
		int mul = n / minn;
		if(minn == -1||mul == 1) {write(1);write(n-1);}
		else{write ( 1 * mul);write( (minn-1)*mul);}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Pollococido (赞：0)

数学题。
### 思路
首先要知道一个定理：
$$\operatorname{lcm}(a, b) = \dfrac{a \times b}{\gcd(a, b)}$$
那么我们就可以找到 $n$ 的最大真因数 $d$ 以及最小质因子 $p$，结果就是 $p$ 和 $(p - 1)d$，当然，若 $n$ 为质数，答案只能是 $1$ 和 $n - 1$。 
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;

signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        int a = -1, b = -1;
        for (int i = 1; i <= n / i; i++) {
            if (n % i == 0) {
                a = n / i;
                b = a * (i - 1);
            }
        }
        if (a != -1 && b != -1) cout << a << " " << b << endl;
        else cout << 1 << " " << n - 1 << endl;
    }
    return 0;
}
```

---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1372B)
### 题目分析
给出 $ n $，输出 $a,b(0<a \leqslant b<n)$ 且  $\operatorname{lcm}(a,b)$ 最小。
 
$\because \operatorname{lcm}(a,b)= \frac{a \times b}{\gcd(a,b)} $

$\therefore$ 我们可以找到 $n$ 最小的质因子 $\operatorname{minn}$，再找出 $n$ 最大的约数 $\operatorname{maxx}$，由于题目较水，可以使用朴素筛法。

这里就产生了两种情况：

$1.$ 当 $n$ 为合数时，我们可以使答案为 $\operatorname{minn}$ 和 $(\operatorname{minn}-1) \times \operatorname{maxx}$。

$2.$ 当 $n$ 为质数时，我们可以使答案为 $1$ 和 $n-1$。

### 代码如下：
```cpp
void lcm(int n){
	a=0,b=0;
	for(int i=2;i*i<=n;i++)
		if(n%i==0){
			a=n/i;//求最大约数maxx
			b=(i-1)*a;//求（minn-1）*maxx
			return;
		}	
	a=1,b=n-a;//第二种情况
	return;
}
```

### 不懂素数筛的可以看[这个](https://blog.csdn.net/lcx0128/article/details/128408977)。

### AC 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a,b;
void lcm(int n){
	a=0,b=0;
	for(int i=2;i*i<=n;i++)
		if(n%i==0){
			a=n/i;//求最大约数maxx
			b=(i-1)*a;//求（minn-1）*maxx
			return;
		}	
	a=1,b=n-a;//第二种情况
	return ;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		lcm(n);
		printf("%d %d\n",a,b);
	}
	return 0;
}
```
下期见！拜拜！

---

## 作者：enyyyyyyy (赞：0)

- 
	思路：先将 $1$ 至 $10^5$ 的质数筛出。顺序枚举每个质数，再将 $n$ 对质数取模，如果整除，那么这就是最大公因数了，即可输出 $n$ 除以最大公因数和 $n$ 减 $n$ 除以最大公因数。

- 
	注意：开 `long long`；如果 $n$ 为偶数时，直接输出 $n$ 除以 $2$ 和 $n$ 除以 $2$；如果 $n$ 为质数，输出 $1$ 和 $n-1$。
    
- 
	代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll x = 0, f = 0;
	char ch = 0;
	while (!isdigit(ch)) {
		f |= (ch == '-');
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f? -x: x;
}
inline void print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll _,n;
bool is_prime[1000005];
ll prime[1000005], tot;
void ai(ll MAXN) {
	for (ll i = 2; i <= MAXN; i++) is_prime[i]=1;
	for (ll i = 2; i <= MAXN; i++)
		if (is_prime[i]) {
			prime[++tot] = i;
			for (ll j = 2 * i; j <= MAXN; j += i)
				is_prime[j] = 0;
		}
}
int main() {
	ai(100000);
	_=read();
	while(_--) {
		n=read();
		if(n%2==0) {
			print(n/2),printf(" "),print(n/2),printf("\n");
			continue;
		}
		ll flag=0;
		for(ll i=1; i<=tot; i++)
			if(n%prime[i]==0) {
				print(n/prime[i]),printf(" "),print(n-n/prime[i]),printf("\n");
				flag=1;
				break;
			}
		if(!flag) print(1),printf(" "),print(n-1),printf("\n");
	}
	return 0;
}
```

---

## 作者：NaOHqwq (赞：0)

提示：各位读者做完本题可以去看看 [CF1765M](https://www.luogu.com.cn/problem/CF1765M) 这道题，与本题是同类型的。

## 题意

给定一个整数 $n$，输出 $a$ 和 $b (0 < a \leq b < n)$，使 $a+b=n$ 且 $\operatorname{lcm}(a,b)$ 最小。

我们知道 $\operatorname{lcm}(a,b)=\frac{a \times b}{\gcd(a,b)}$，所以 $a$ 和 $b$ 的乘积一定，$\operatorname{gcd}(a,b)$ 越大，$\operatorname{lcm}(a,b)$ 就越小。则要想满足题意，需要让 $a$ 和 $b$ 的最大公约数尽可能大。

接下来要解决的问题就是如何让 $\operatorname{gcd}(a,b)$ 尽可能大。

要使 $\operatorname{gcd}(a,b)$ 最大，就要使 $a=bx$，即 $a$ 是 $b$ 的 $x$ 倍，可得 $x$ 越小，$\operatorname{gcd}(a,b)$ 就越大。

那么接下来就可以遍历找 $x$ 了。如果找到了就按刚才的结论输出，如果没找到则说明 $n$ 是质数，输出 $1$ 和 $n-1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a;
	cin >> a;
	while(a--){
		int n;
		bool flag = true;
		cin >> n;
		for(int i = 2;i <= sqrt(n)+2;i++){ //遍历找 x
			if(n%i == 0){
				cout << n/i << " " << (n/i)*(i-1) << endl; //找到了
				flag = false;
				break;
			}
		}
		if(flag){
			cout << "1 " << n-1 << endl; //没找到，n 为质数
		}
	}
	return 0;
}
```

---

## 作者：KaguyaH (赞：0)

> [CF1372B](https://codeforces.com/contest/1372/problem/B).
> [Github blog](https://9u46-mx.github.io/post/Solution-CF1372B/).

---

本题解中所有数据均为正整数。

给定正整数 $n$，求最大的 $m$ 使得 $\exists\ a, b$ 满足 $a + b = n \land \operatorname{lcm}(a, b) = m$。

$1 \leqslant t \leqslant 10$，$2 \leqslant n \leqslant 10^9$。

---

设 $p$ 为 $n$ 的最小质因子，显然 $a = \frac n p$，$b = n - a$ 即可。时间复杂度 $\mathcal O(t \sqrt n)$。

然后就 AC 了，考虑证明。假设 $a \leqslant b$。

---

$b = n - a = \frac{n(p - 1)}p$，显然 $a \mid b$，$\operatorname{lcm}(a, b) = b$。

若存在 $a' \leqslant b'$ 满足 $a' + b' = n \land \operatorname{lcm}(a', b') < b$，则显然 $a < a' \leqslant  b' < b$。

故 $a'b' > ab$，故 $\gcd(a', b') > \gcd(a, b) = a$。

而 $\gcd(a', b') = \gcd(a', n - a') = \gcd(a', n)$，又有 $a' < n$，

故 $\gcd(a', b') \leqslant \frac n p = a$。矛盾。

故 $a, b$ 即为答案。

---

```cpp
# include <cstdio>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
    }
    using namespace Source;
    namespace Solve {
        static uint n;
        static inline const void main() {
            scanf("%u", &n);
            for (hu i(2); 1u * i * i <= n; ++i)
                if (not(n % i)) return (const void)printf("%u %u\n", n / i, n - n / i);
            printf("1 %u\n", n - 1);
        }
    }
    static hu t;
    static inline const void main() {
        scanf("%hu", &t);
        for (hu i(0); i < t; ++i) Solve::main();
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：chenwenda316 (赞：0)

这一道题是一道数学题，题意是把 $n$ 分成 $a$ 和 $b$ ，使 $\operatorname{lcm}(a,b)$ 最小.

众所周知 $\operatorname{lcm}(a,b)=a \times b \div \gcd(a,b)$ ，所以，最大公因数越大，$\operatorname{lcm}(a,b)$ 越小。

要使 $\gcd(a,b)$ 最大，必须 $a$ 是 $b$ 的 $x$ 倍，所以 $a=n\div \left(x+1\right),b=n-n\div \left(x+1\right)$ ，又因为易证 $x$ 越小，$\gcd(a,b)$ 越大，所以可以用一个循环，从 $2$ 到 $\sqrt{n}+2$ 遍历一遍，找出 $x$ ，如果没找到 $x$ 就说明 $n$ 是质数，输出 $1$ 和 $n-1$ 即可。

代码如下：

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		int h=1;
		cin>>n;
		for(int i=2;i<=sqrt(n)+2;i++){
			if(n%i==0){
				cout<<n/i<<" "<<(n/i)*(i-1)<<"\n";
				h=0;break;
			}
		}
		if(h)cout<<"1 "<<n-1<<"\n";
	}
	return 0;
} 
```

---

## 作者：Theophania (赞：0)

题意和解题思路上一篇题解已经写的很完善了，但是由于题目中的数据范围是 $t\le 10,n\le 10^9$，我们可以不用写线性筛，直接用 $O(\sqrt n)$ 的暴力就可以了，甚至不需要任何优化。

以下代码即可AC

``` cpp

#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int T, n, ans;
    cin >> T;
	while (T--)
    {
		cin >> n;
		ans = n - 1;
		for (int i = 2; i * i <= n; ++i) 
			if (n % i == 0) 
				ans = min(ans , n - n / i);
		cout << n - ans << ' ' << ans << '\n';
	}
	return 0;
}

```



---

