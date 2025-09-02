# Divisor Subtraction

## 题目描述

给定一个整数$n$，按照如下算法进行操作  
1. 如果$n=0$，结束算法；  
1. 找到$n$的最小质因子$d$；  
1. $n-=d$并回到操作$1$

## 样例 #1

### 输入

```
5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
```

# 题解

## 作者：幸存者 (赞：5)

## 思路
一看到这道题，就直接写了个递归，结果超时了。

开始思考怎么优化，不难发现一旦 $n$ 变为了 $2$ 的倍数，$n-2$ 还是 $2$ 的倍数，而 $2$ 是最小的质数，所以 $n$ 变为 $2$ 的倍数之后的循环次数就是 $n/2$。

于是就在递归里加了一句判断 $n$ 是否为 $2$ 的倍数，如果是就直接返回 $n/2$ 的语句，然后评测就过了。
## AC Code
```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long k(long long x)
{
    for (int i = 2; i <= sqrt(x); i++) if (x % i == 0) return i;
    return x;
}
long long f(long long x)
{
    if (x == 0) return 0;
    if (x % 2 == 0) return x / 2;
    return f(x - k(x)) + 1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    long long n;
    cin >> n;
    cout << f(n) << endl;
    return 0;
}
```

---

## 作者：damage (赞：4)

## 题意

珂朵莉给你一个数$n$（$1\leq{n}\leq{10^{10}}$），循环执行如下操作，初始时$m=0$

 1. 若$n=0$，则结束循环
 2. 找到$n$最小的质因数$d$
 3. $n-=d$
 4. $m++$
 5. 前往步骤$1$
 
循环结束时输出$m$（其实就是操作次数）

---

## 题解

很容易发现$n$为偶数时，操作$2$找到的$d=2$，偶数减偶数还是偶数，所以：

- 当$n$为偶数时，答案就是$n/2$

更容易地发现当$n$为质数时，找到的$d=n$，$n-n=0$，所以：

- 当$n$为质数时，答案就是$n$

剩下的情况就是$n$是奇合数了，只要循环枚举$n$以内的奇数，第一个找到的$n$的约数的数（很容易知道一定是质数）就是$d$。

设操作$2$的函数叫```findmin()```所以：

- 对于其余的$n$，答案就是$(n-$```findmin(n)```$)/2+1$

### 注意$n$最大为$10^{10}$，超过了$MAX\_INT$，所以要用$long\ long$
---

## 代码

> 注： 用了一点位运算，详见最后的说明。

> 因为$n$是$long\ long$，常量定义默认是$int$型，所以最好养成好习惯加一个```ll```在常量数字后面

```cpp
#include<cstdio>
long long n,res; //记得long long
bool isprime(long long x) //借用某大佬O(n/6)的质数判断
{
	if(x==1ll) return false;
	if(x==2ll||x==3ll) return true;
	if(x%6ll!=1ll&&x%6ll!=5ll) return false;
	for(register long long i=5ll;i*i<=x;i+=6ll)
		if(!(x%i)||!(x%(i+2ll))) return false;
	return true;
}
long long findmin(long long x) //findmin函数
{
	for(register long long i=3ll;i*i<x;i+=2)
		if(!(x%i)) return i;
	return 0ll;
}
int main()
{
	scanf("%lld",&n);
	if(isprime(n)) printf("1\n"); //如果n是质数就输出1
	else if(!(n&1)) printf("%lld\n",n>>1ll); //如果n是偶数就输出n/2
	else printf("%lld\n",((n-findmin(n))>>1ll)+1ll); //否则就输出(n-findmin(n))/2+1
	return 0;
}
```

---

## 说明

关于本篇涉及到的位运算的讲解（其实就一个）

```x>>1```表示```x/2```，其实$x$>>$i$ $=\frac{x}{2^{i}}$。

---

## 完结

---

## 作者：conti123 (赞：1)

### 思路
直接暴力出奇迹，然后 TLE。

考虑优化：

1. 我们知道，若 $n$ 为偶数，则一定有等式 $n=2k$ 其中 $k$ 为整数。

	所以当 n 为偶数时其最小质因子一定是 $2$，而因为 $n$ 是偶数，所以 $n-2$ 也一定是偶数，所以 $n-2$ 的最小质因子也一定是 $2$,这样每次都 $-2$，则操作次数为 ${n}\div{2}$。
2. 在计算 $n$ 的最小质因子时，若用暴力的算法，时间复杂度很大。
	
    所以设我们直接从 $3$ 枚举到 $\sqrt{n}$，如果 $i$ 是 $n$ 的因子，直接返回 $i$，循环结束后若还没找到 $i$,则返回 $n$。
    
    证明：若 $n={a}\times{b}$ 且 $a={p}\times{q}$ 则 $p$ 一定小于 $a$，所以在枚举到 $a$ 之前就已经枚举到 $p$ 了，所以这样做是正确的。
    
最后提醒一下：由于数据过大，要开 long long。
    

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int ga_(int x)
{
	int o=sqrt(x)+1;
	for(int i=3;i<=o;i++)
		if(!(x%i))
			return i;
	return x;
}
int ga(int x)
{
	if(x==0)
		return x;
	if(!(x%2))
		return x>>1;
	return ga(x-ga_(x))+1;
}
signed main()
{
	scanf("%lld",&n);
	printf("%lld",ga(n));
}
```

---

## 作者：Eason_AC (赞：1)

## Content
给定一个数 $n$，执行如下操作：

1. 如果 $n=0$ 结束操作。
2. 找到 $n$ 的最小质因子 $d$。
3. $n\leftarrow n-d$ 并跳到操作 $1$。

请求出循环操作的次数。

**数据范围：$2\leqslant n\leqslant 10^{10}$。**
## Solution
首先我们看是否是素数，如果是素数的话，那么其最小质因子一定是它本身，那么答案就是 $1$。

如果不是素数，我们再根据奇偶性来分类讨论。由于偶数的情况比较简单，我们先讨论 $n$ 是偶数的情况。很显然，其最小质因子一定是 $2$，并且因为减完以后还是偶数，所以一定会不停地减 $2$，所以答案就是 $\dfrac{n}{2}$。

最后再看到奇合数，我们找到一个最小的质因子 $d'$ 之后减去，因为奇合数一定都是由奇质数相乘得到，所以找到的最小质因子也一定是奇数，而我们都知道，奇数减奇数等于偶数，所以就又回到了偶数的情况了，所以答案就是 $\dfrac{n-d'}{2}+1$。

由于 $n\leqslant 10^{10}$，所以我们判断 $n$ 是否是素数可以直接用 $\mathcal{O}(\sqrt{n})$ 的试除法判断是否是素数，然后看最小质因子时，可以先用埃氏筛筛出 $10^5$ 以内的素数，然后再去一个一个找最小的质因子即可，并且可以证明，寻找最小质因子最多只需要 $1$ 次，所以复杂度可以算得上很优秀的了。
## Code
```cpp
long long n;
int isprime[100007];

bool prime(long long x) {
	for(int i = 2; i <= sqrt(x); ++i)
		if(!(x % i)) return 0;
	return 1;
}
void pre() {
	for(int i = 2; i <= 100000; ++i) isprime[i] = 1;
	for(int i = 2; i <= 100000; ++i)
		if(isprime[i])
			for(int j = i * 2; j <= 100000; j += i)
				isprime[j] = 0;
}
void work(long long x) {
	pre();
	for(int i = 2; i <= sqrt(x); ++i)
		if(!(x % i) && isprime[i]) {
			if(x % 2) printf("%lld", (x - i) / 2 + 1);
			else printf("%lld", x / 2);
			return;
		}
	return;
}

int main() {
	scanf("%lld", &n);
	if(prime(n)) printf("1");
	else work(n);
}
```

---

## 作者：_Winham_ (赞：0)

题意：

给定个整数 $n$，给出两种操作，问你需要的操作数。操作如下：

- 如果 $n$ 等于 $0$，终止。

- 否则，找到 $n$ 的最小的质因子，并把 $n$ 减去这个质因子，回到操作 $1$。

---

思路：

看了一下，第一秒想到递归，可做了之后发现超时。这是我们就得想一下优化的方法。如果 $n$ 为偶数，那么可以根据 `偶数 - 偶数 = 偶数` 得出，输出 $n {\div} 2$。如果不为偶数我们能知道 $n$ 的质因子肯定是奇数，而我们能根据 `奇数 - 偶数 = 偶数` 得知，先找出 $n$ 的第一个奇数因子（我们把第一个因子成为 $d$），然后直接输出 `(n - d) / 2 + 1`。

---
上代码。

```cpp

#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int n;
int ans(int n){
	if(n%2==0)return n/2;
	for(int i=3;i*i<=n;i+=2){
		if(n%i==0)
			return (n-i)/2+1;
	}
	return 1;
}
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n;
	cout<<ans(n);
	return 0;
}


```

---

## 作者：Samhu07 (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1076B)&[CF 链接](http://codeforces.com/problemset/problem/1076/B)

## 题目简述

给定一个整数 $n$，按照如下算法进行操作：

1. 如果 $n=0$，结束算法；

2. 找到 $n$ 的最小质因子 $d$；

3. $n-=d$ 并回到操作 $1$。

求该算法进行循环操作的**次数**。

## 思路

简单**模拟题**，只需要按照算法要求模拟即可，不过还是需要**一点优化**。

因为看到**数据范围** $(2 \le n \le 10^{10})$ 比较大，所以直接模拟会**超时**，经过举例可推出：

在当前 $n$ 为 $2$ 的倍数的时候，直接返回 $n/2$ 即可，因为**如果 $n$ 为 $2$ 的倍数那么此时的 $n$ 的最小质因数一定为** $2$，那么此后的 $n$ 的最小质因数也会是 $2$ 就**不必再模拟**了。相当于**特判**。

经过以上优化，就很容易得到代码了：

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,x,y) for(int i = x;i<=y;i++)
#define go(i,x,y) for(int i = x;i>=y;i--)
const int inf = 2147483647;
const int mod = 1000000007;
using namespace std;
long long n,ans; //要开 long long
void work(){
	if(!(n%2)) return; // 优化
 	// 找 n 的最小质因数
	for(int i = 3;i*i <= n;i++) {
		if(n%i==0)
			n -= i; //找到了直接减，返回
			return;
		}
	n = 0; //n是质数
	return;
}
int main() {
	scanf("%d",&n);
  	// 模拟
	while(n % 2 && n > 0){
		work();
		ans ++;
	}
  	// 答案加上 n / 2，换行好习惯
  	printf("%d\n",ans+n/2);
	return 0;
}
```

$$\text{The End!}$$

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1076B)

# 题目大意

每次找到$\ n\ $最小的质因数减掉，求$\ n=0\ $时的操作次数。

# 思路

看到此题，不用想别的，直接上数学。

1. $n\ $为偶数 则$\ n\ $最小的质因数就是$\ 2$，而$\ n-2\ $还是偶数，所以$\ n\ $为偶数时，答案即为$\ n\ $除以$\ 2$。

1. $n\ $为奇数 则$\ n\ $最小的质因数必然也为奇数，相减又变回偶数。

1. $n\ $为素数 此时只需一步就能把$\ n\ $变成$\ 0$。



AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    cin>>n;
    if(n%2==0)cout<<n/2<<endl;
    else
    {
        bool flag=0;
        for(long long i=2;i*i<=n;i++)
        {
            if(n%i==0)
            {
                flag=1;
                cout<<1+(n-i)/2<<endl;
                break;
            }
        }
        if(!flag)cout<<"1";
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/110275778)

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1076B)                   
思维题。        
先上结论：设 $x$ 是 $n$ 的最小质因子，那么变成 $0$ 需要的步数是 $\frac{n-x}{2}+1$ 步。         
接下来解释一下。          
我们都知道，质数中，$2$ 既是最小的，也是唯一的偶数。        
那么，只要 $n$ 是偶数（$2$ 的倍数），那么需要的步数就是 $\frac{n}{2}$。        
那么 $n$ 是奇数呢？      
质数中，除了 $2$ 都是奇数，并且奇数减掉奇数是偶数。所以奇数减掉最小质因子后必然是偶数，步数很容易推，就是上面的那个结论。          
这个奇数的结论对偶数也有效。     
CODE：     
```cpp
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
using namespace std;
#define umap unordered_map
#define ll long long
#define pii pair<int,int>
#define pll pair<long long,long long>
namespace mySTL{
	inline int max(int a,int b){return a>b?a:b;}
	inline int min(int a,int b){return a<b?a:b;}
	inline int abs(int a){return a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline long long readll(){char c=getchar();long long f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void writell(long long x){if(x<0){putchar('-');x=-x;}
	if(x>=10){writell(x/10);}putchar(x%10+'0');}
	inline ll pw(ll a,ll b,ll p){if(b==0)return 1;
	if(b==1)return a;
	ll mid=pw(a,b/2,p)%p;
	if(b&1)return mid*mid%p*a%p;else{return mid*mid%p;}}
	inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
}
using namespace mySTL;
ll n;
inline ll prime(ll x){
	for(ll i=2;i<=x/i;i++){
		if(x%i==0){
			return i;
		}
	}
	return x;
}
int main(void){
	//freopen("data.txt","r",stdin);
	n=readll();
	writell((n-prime(n))/2+1);
	return 0;
}

```


---

## 作者：庄nnnn额 (赞：0)

我们分两种情况考虑。
1. $n$ 是偶数。一个偶数的最小质因数一定为 $2$，所以一开始 $n$ 就会减去 $2$。由于 $2$ 也是偶数，所以 $n-2$ 还是偶数，那么第二次还是减去 $2$。$n-2$ 减去 $2$ 后还是偶数，所以又会减 $2$……如此反复直到 $n$ 变成 $0$。总的操作数是 $\dfrac{n}{2}$。时间复杂度为 $\Theta(1)$。
2. $n$ 是奇数。在这种情况下，$n$ 的最小质因数一定是一个奇数。$n$ 在减去这个数之后就变成了偶数，又变成了第一种情况了。我们可以先找出这个最小质因数，把 $n$ 减去它，再按第二种情况处理。时间复杂度为 $\Theta(\sqrt{n})$。

下面给出代码（C++）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long n,a=0,f;
	scanf("%lld",&n);
	if(n&1){
		f=0,a=1;
		for(long long i=2;i*i<=n;i++){
			if(n%i==0){
				n-=i,f=1;
				break;
			}
		}
		n*=f;
	}
	printf("%lld",a+n/2);
	return 0;
}
```

---

## 作者：Kreedy_Ke (赞：0)

对于一个数 $n$，我们可以将其分为三种情况来讨论：

1. $n$ 为偶数时。此时 $n$ 的最小质因子肯定为 2，而偶数减去 2 结果也一定是偶数，如此下来，最终操作次数为 $\frac{n}{2}$ 次。
2. $n$ 为奇质数时。此时 $n$ 的最小质因子肯定为其本身，操作次数仅为 1 次。
3. $n$ 为奇合数时。此时 $n$ 的最小质因子肯定为奇数，而奇数减奇数为偶数，则跳转至情况 1，最终操作次数为 $\frac{n-n'}{2}+1$ 次，其中 $n'$ 为 $n$ 的最小质因子。

其实第一种和第三种情况本质上一样，所以在代码实现中我们可以放在一起写。

那么如何找到一个数的最小质因子呢？使用质数筛提前将 $10^5$ 里的所有质数都找到，存放在一个数组里。为什么是 $10^5$ 以内？因为一个合数 $n$ 的质因子中至少有一个小于 $\sqrt{n}$（可证），而如果不能找到这样的一个质数，说明 $n$ 本身就是一个质数。

提供一种质数筛板子，代码如下：

```
int tot,prime[N]; //质数个数与质数表
bool check ( int x )
{
    if ( x==2 || x==3 || x==5 || x==7 ) return 1;
    for ( int i=1 ; i<=tot ; i++ )
        if ( x%prime[i]==0 ) return 0;
    return 1;
}
void get()
{
    for ( int i=2 ; i<1e5+1 ; i++ )
        if ( check(i) ) prime[++tot]=i;
}
```

然后按照刚才的思路模拟就行了，需注意这题 $n$ 的最大值为 $10^{10}$，会爆 int 所以请开 long long。

以下为代码：

```
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define LL long long //别忘了开long long
using namespace std;
const int N=1e5+9;
int tot,prime[N]; //质数个数与质数表
bool check ( int x )
{
    if ( x==2 || x==3 || x==5 || x==7 ) return 1;
    for ( int i=1 ; i<=tot ; i++ )
        if ( x%prime[i]==0 ) return 0;
    return 1;
}
void get()
{
    for ( int i=2 ; i<1e5+1 ; i++ )
        if ( check(i) ) prime[++tot]=i;
}
int main()
{
    get();
    LL n; scanf("%lld",&n);
    for ( int i=1 ; i<=tot ; i++ )
        if ( n%prime[i]==0 ) //如果是个合数
        { 
            printf("%lld\n",(n-prime[i])/2+1); 
            return 0;
        }
    puts("1"); //否则是质数
    return 0;
}
```

---

