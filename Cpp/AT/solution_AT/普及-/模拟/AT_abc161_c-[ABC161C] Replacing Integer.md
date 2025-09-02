# [ABC161C] Replacing Integer

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc161/tasks/abc161_c

青木君は任意の整数 $ x $ に対し、以下の操作を行うことができます。

操作: $ x $ を $ x $ と $ K $ の差の絶対値で置き換える。

整数 $ N $ の初期値が与えられます。この整数に上記の操作を $ 0 $ 回以上好きな回数行った時にとりうる $ N $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 0\ <\ =\ N\ <\ =\ 10^{18} $
- $ 1\ <\ =\ K\ <\ =\ 10^{18} $
- 入力は全て整数

### Sample Explanation 1

最初、 $ N=7 $ です。 $ 1 $ 回操作を行うと、$ N $ は $ |7-4|\ =\ 3 $ となります。 $ 2 $ 回操作を行うと、$ N $ は $ |3-4|=1 $ となり、これが最小です。

### Sample Explanation 2

$ 1 $ 回も操作を行わなかった場合の $ N=2 $ が最小です。

## 样例 #1

### 输入

```
7 4```

### 输出

```
1```

## 样例 #2

### 输入

```
2 6```

### 输出

```
2```

## 样例 #3

### 输入

```
1000000000000000000 1```

### 输出

```
0```

# 题解

## 作者：Otomachi_Una_ (赞：3)

大水题！！！

对于 $n$ ， 我们让其不断地减去 $k$ 会有以下过程：

$n$ $\Rrightarrow$ $n-k$ $\Rrightarrow$ $n-2\times k$ $\Rrightarrow$ ...... $\Rrightarrow$ $n \% k$ $\Rrightarrow$ $k- n\%k$ $\Rrightarrow$ $n\%k$ $\Rrightarrow$......

观察得到最小值必为 $n\%k$ 和 $k-n\%k$ 当中较小的一个。

## _Code_
```cpp
#include<iostream>
using namespace std;
long long n,k;
int main(){
    cin>>n>>k;
    cout<<min(n%k,k-n%k);
}
```


---

## 作者：_jimmywang_ (赞：1)

我又来写友好题啦~~

看到题目的第一眼：~~看不懂~~用$while$一下就好了~~

于是有了这份代码：

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll n,k;
ll ans=1000000000000000000;
int main(){
	scanf("%lld %lld",&n,&k);
	while(1){
		n=abs(n-k);
		if(n<ans)ans=n;
		else break;
	}
	cout<<ans;
	return 0;
}

```
$TLE$#$3$了呜呜呜~~~

不要伤心，不要难过！！！让我们看看！

比如这组数据：

$n=1000000000000000000$（别数了，18个0），$k=1$

那么你$while$的时候循环$10^{18}$次你有没有考虑过评测机的感受！！！

于是，评测机伤心的给你了一个$TLE$

于是我们继续分析：

其实真正可能成为最小值的有很多吗？$1000000000000000000$可能吗？$999999999999999999$可能吗？

所以真正争夺答案席位的只有两个数：$n$%$k$与$-$($n$%$k-k$),这两个数，只相差k（不加绝对值），但一个是自然数，另一个是负数。所以加上绝对之后，答案绝对是他们俩的$min$

于是主程序只有2行的代码写好了。。。

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll n,k;
ll ans;
int main(){
	scanf("%lld %lld",&n,&k);
	printf("%lld",min(n-n/k*k,-(n-n/k*k-k)));
	return 0;
}

```
撒花花啦！！！

---

## 作者：AmamiyaYuuko (赞：1)

题目大意：给出 $n, k$，每次可以将 $n$ 变为 $|n - k|$，求 $n$ 的最小值。$0 \le n \le 10^{18}, 1 \le k \le 10^{18}$。

进行分类讨论。如果 $n \le k$，那么 $n$ 的取值只会有两种，分别为 $n$ 和 $k - n$，输出较小的即可。

如果 $n > k$，容易发现操作会不断从 $n$ 减去 $k$ 直到 $n \le k$，最后的 $n$ 则为 $n \bmod k$，所以取 $n \bmod k$ 和 $k - (n \bmod k)$ 的最小值即可。

代码：

```cpp
read(n), read(k);
if (n <= k) {
    printf("%lld\n", std::min(n, k - n));
} else {
    LL m = n % k;
    printf("%lld\n", std::min(m, k - m));
}
```

---

## 作者：WHJ___ (赞：0)

我们可以从题目中获取一个结论：

$ans\in\{ans|n+pk,p\in Z\}$

那么就可以得到一个 while 做法。

我们先以 $n=7,k=3$ 为例:

![](https://cdn.luogu.com.cn/upload/image_hosting/5vlxio4b.png)

有图易见，此时的答案为 $1$，也就是$n\bmod k$。

但如果将图上这种方法暴力用 while 实现，那么时间复杂度可以达到 $O(\frac{n}{k})$，最多可以达到 $10^{18}$，超时是必然的，因此我们要寻找一个更优秀的方法。

我们再举一组例子 $n=7,k=4$：

![](https://cdn.luogu.com.cn/upload/image_hosting/84dycnl3.png)

由图可见，此时的答案为 $1$，但是此时的 $1$ 实际上是 $|n\bmod k-k|$。

综上显而易见，答案 $ans$ 只能是这两种情况中的最小值，即:
1. $n\bmod k$

2. $ |n\bmod k -k| $

这样才能使 $ans$ 更接近 $0$。

那么就可以得出：$ans=\min(n\bmod k,|n\bmod k -k|)$

代码就很简单了：

```cpp
#include<bits/stdc++.h>
#define I long long
#define il inline
#define rt return
using namespace std;
il I d(){
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	rt x;
}
signed main()
{
	I a,b;
	a=d();b=d();
	cout<<min(a%b,-(a%b-b));
	rt 0;
}
```


---

## 作者：PLDIS (赞：0)

已知两个数 $n$ 和 $k$，经过若干次让 $n$ 变成 $|n - k|$ 的操作，求 $n$ 的最大值。

我们一下子就会想到暴力，可是 $1≤n,k≤10^{18}$，暴力肯定TLE。所以，我们要找更优的解法。

我们先别看绝对值，不难发现，在它们相减到最小的正整数时，那个最小的正整数就是 $n\mod k$。可是，加上绝对值，我们可以得到，再减一次就成了 $n - (n \mod k)$。继续减，又成了 $n \mod k$，一直这样下去。所以，我们只要在 $n \mod k$ 和 $n - (n \mod k)$ 中比个小，再把它输出就行了。

## Code:

对，您没看错，就这么短！

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    long long a, b;
    cin >> a >> b;
    cout << min(a % b, b - (a % b));
    return 0;
}
```

---

## 作者：ljm1621 (赞：0)

很显然，$10^{18}$的数据暴力是过不了的。所以要想另一种方法。

因为$n$如果想让它最小，一定让它不断的减去$k$，所以最后的$n$总是会等于$n \bmod k$。

所以这道题求的就是$n \% k$和$\operatorname{abs}(n \% k-k)$中的最小值。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n,k;
    cin>>n>>k;
    n=min(n%k,abs(n%k-k));
    cout<<n<<endl;
    return 0;
}
```

[亲测AC](https://www.luogu.com.cn/record/45396353)

---

## 作者：TLMPEX (赞：0)

思路：这道题可以先用n%k可以省时间，因为n减m最终会减到n%k了。最后输出n和n-k的绝对值中小的一个。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	unsigned long long n,k;
	cin>>n>>k;
	n%=k;
	n=min(n,abs(n-k));
	cout<<n;
}
```


---

## 作者：iiawaKL (赞：0)

# ~~水题一个~~

我们只要求出n%k,k-n%k的最小值，就是这题的答案。

其实很简单，我就不多说了。

上代码。

 _Code->_
 
 ```
#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define forn(i,a,b) for(int i=a;i<=b;i++)
#define INF 2147483647
#define LLINF 9223372036854775807
using namespace std;
int main(){
	long long n,k;
	cin>>n>>k;
	cout<<min(n%k,k-n%k)<<endl;
	return 0;
}
```


---

## 作者：C171501 (赞：0)

本题有以下选项：

 - 当 $n\leq m$ 时，答案为 $\min(n,m-n)$。
 - 当 $n\geq m$ 时，$n$ 将减去多个 $m$ 直到 $n\leq m$，即 $n$ 的值变为 $n \bmod m$，故答案为 $\min(n \bmod m,m-n \bmod m)$。

但由于 $n \bmod m$ 在 $n\leq m$ 时仍然等于 $n$，故我们可以不用特判，直接将比较代码统一表示为 $\min(n \bmod m,m-n \bmod m)$，将代码缩短。

如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int main()
{
	cin>>n>>m;
	n%=m;
	n=min(n,m-n);
	cout<<n<<endl;
	return 0;
}
```


---

## 作者：1n1c5c5z (赞：0)

## 题意
给定 $N,K$，每次操作把 $N$ 变成 $|N-K|$，求 $N$ 的最小值。  数据范围：$0 \leq N \leq 10^{18},1 \leq K \leq 10^{18}$
## 思路：
分类讨论。  
- 当 $N=K$ 时，答案为 $0$。
- 当 $N<K$ 时，$N$ 的值在$N,N-K$之间徘徊，答案为 $\max(N,N-K)$。
- 当 $N>K$ 时，$N$ 的值会降到 $N \bmod K$，答案为 $\max(N \bmod K,K-N \bmod K)$
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long x,k,ans;
	cin>>x>>k;
	if (x==k)ans=0;
	else if (x<k)ans=min(x,k-x);
	else if (x>k)
	{
		x=x%k;
  		ans=min(x,k-x);
	}
	cout<<ans<<endl;
}
```

---

