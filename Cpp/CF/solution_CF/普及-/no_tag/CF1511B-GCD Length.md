# GCD Length

## 题目描述

You are given three integers $ a $ , $ b $ and $ c $ .

Find two positive integers $ x $ and $ y $ ( $ x > 0 $ , $ y > 0 $ ) such that:

- the decimal representation of $ x $ without leading zeroes consists of $ a $ digits;
- the decimal representation of $ y $ without leading zeroes consists of $ b $ digits;
- the decimal representation of $ gcd(x, y) $ without leading zeroes consists of $ c $ digits.

 $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Output $ x $ and $ y $ . If there are multiple answers, output any of them.

## 说明/提示

In the example:

1. $ gcd(11, 492) = 1 $
2. $ gcd(13, 26) = 13 $
3. $ gcd(140133, 160776) = 21 $
4. $ gcd(1, 1) = 1 $

## 样例 #1

### 输入

```
4
2 3 1
2 2 2
6 6 2
1 1 1```

### 输出

```
11 492
13 26
140133 160776
1 1```

# 题解

## 作者：云浅知处 (赞：6)

题目让你构造一个十进制下的 $a$ 位正整数 $x$，$b$ 位正整数 $y$，使得 $\gcd(x,y)$ 有 $c$ 位。

保证 $c\le \min(a,b)$，$1\le a,b,c\le 9$。

直接把 $\gcd(x,y)$ 搞成 $10^{c-1}$ 是一个很自然的想法qwq。

那现在只需要让 $x,y$ 除以 $10^{c-1}$ 的商互质即可。

互质？管那么多干啥，直接搞成俩质数不就行了qwq。

所以我们对 $i=0,1,\cdots 9$，预处理出来 $[10^{i},10^{i+1})$ 中的两个不同质数，最后用 $10^{c-1}$ 乘上这俩质数就行了。

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cctype>

#define int long long

using namespace std;

int a,b,c,t;

int x[100]={0,2,11,101,1009,10007,100003,1000003,10000019,100000007,1000000007};
int y[100]={0,3,13,103,1013,10009,100019,1000033,10000079,100000037,1000000009};

int p,q,r;

signed main(void){

    cin>>t;
    while(t--){
        p=q=r=1;
        cin>>a>>b>>c;
        for(int i=1;i<c;i++)r*=10;
        cout<<r*x[a-c+1]<<" "<<r*y[b-c+1]<<'\n';
    }

    return 0;
}
```

---

## 作者：___cjy__ (赞：3)

# CF1511B GCD Length 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1511B)

[更好的阅读体验](https://www.luogu.com.cn/blog/509668/solution-cf1511b)

简单的橙题。

### 题目大意：

给定 $3$ 个整数 $a$,$b$,$c$，找出数对 $x$,$y$ 使得

- 去掉前导 $0$ 后的十进制整数 $x$ 有 $a$ 位。
- 去掉前导 $0$ 后的十进制整数 $y$ 有 $b$ 位。
- 去掉前导 $0$ 后的十进制整数 $\gcd(x,y)$ 有 $c$ 位。

### 正文：

一个构造题.先考虑构造 $\gcd(x,y)$，随后构造 $x$ 与 $y$。从最简单的角度来讲，$\gcd(x,y)$可以简单地设为 $10^{c-1}$。而 $x$ 与 $y$ 可以先连续乘两个不同的质数（例如 $3$ 和 $7$），直到 $x$ 与 $y$ 的长度分别为 $a-c+1$ 和 $b-c+1$，这样就可以使它们乘 $\gcd(x,y)$ 的长度分别为 $a$ 和 $b$，从而满足题目中的三个条件。

### AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 25
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int T, a, b, c, x, y, gcd; 
int num_size(int n){//计算数字长度 
	int x = 0;
	while(n != 0) 
		n /= 10, x ++;
	return x;
}
signed main(){
	scanf("%lld", &T);
	while(T--){
		x = y = gcd = 1; 
		scanf("%lld %lld %lld", &a, &b, &c);
		gcd = pow(10, c - 1);// 构造gcd(x, y) 
		while(num_size(x) < a - c + 1) x *= 3;//构造x 
		while(num_size(y) < b - c + 1) y *= 7;//构造y 
		x *= gcd, y *= gcd;
		printf("%lld %lld\n", x, y);
	}
	return 0;
}
```

---

## 作者：xiaoyuchenp (赞：3)

简单的构造题。

**思路**

首先考虑 $\gcd(x,y)$ 如何变成 $c$ 位，能想到的最简方式显然是构造 $10^{c-1}$。

若 $10^{c-1}$ 为 $x$ 与 $y$ 的最大公因数，显然 $x$ 与 $y$ 除以 $10^{c-1}$ 的商互质。想到 $x$ 必须有 $a$ 位，将 $x$ 设为 $10^{a-1}$，则 $x$ 与 $10^{c-1}$ 的商为 $10^{a-c}$。现在只需要构造 $y$ 与 $10^{c-1}$ 的商使得其与 $10^{a-c}$ 互质，既不能被 $2$ 或 $5$ 整除即可。

构造的方式很简单，为了简便把商的每一位设成相同的数字，$9$ 或 $7$ 或其他数字皆可，只需不被 $2$ 或 $5$ 整除即可。$9$ 的情况即为一些题解构造的 $10^{b-c+1}-1$。

时间复杂度为 $O(T \times \max(a,b))$。当然也可以用质数的方式构造 $x$ 与 $y$，时间复杂度还能做到更优。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a,b,c;

int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		cout<<1;
		for(int i=1;i<a;i++)cout<<0;
		cout<<' ';
		for(int i=1;i<=b-c+1;i++)cout<<7; //9或其他数字也可以，具体见思路部分
		for(int i=1;i<=c-1;i++)cout<<0;
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Mophie (赞：2)

这题是个较简单的构造。

首先考虑怎么让 $\gcd(x,y)$ 做到 $c$ 位，于是可以想到 $10^c$ 是非常简单的。

所以 $x,y$ 后面首先都放上 ${c-1}$ 个 $0$。

但现在要让剩下来的互质，用 $10^{a-c}$ 和 $10^{b-c+1}-1$ 即可。

因为后面的不被 $2$ 或 $5$ 整除，所以互质。

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
int taxi,a,b,c;
long long ans1,ans2;
signed main()
{
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		a=read(),b=read(),c=read();ans1=ans2=1;
		c--;putchar('1');
		for(int i=2;i<=a;i++)putchar('0');putchar(' ');
		for(int i=1;i<=b-c;i++)putchar('9');
		for(int i=1;i<=c;i++)putchar('0');
		puts("");
	}
	return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：1)

我们考虑随便构造一个有这么多位的最大公因数，为了方便这里直接用 $2$ 的幂构造就好了。             

接着你再把一个一直乘 $2$ 一个一直乘 $3$ 就好了，玩的就是手速。        
```cpp
#include "bits/stdc++.h"
using namespace std;
long long x,y,a,b,c,t;
long long p[15];
int main()
{
	p[1] = 1;
	for(int i = 2 ; i <= 9 ; i ++) p[i] = p[i - 1] * 10;
	scanf("%lld",&t);
	while(t --)
	{
		scanf("%lld %lld %lld",&a,&b,&c);
		long long GCD = 1;
		while(GCD < p[c]) GCD *= 2;
		x = GCD , y = GCD;
		while(x < p[a]) x = x * 3;
		while(y < p[b]) y = y * 2;
		printf("%lld %lld\n",x,y);
	}
	return 0;
}
```

---

## 作者：oimaster (赞：1)

为了方便表达，我们把 $\gcd(x,y)$ 称作 $z$。

那么，为了方便后面程序处理，我们就很容易想到把 $z$ 看作 $10^{c-1}$ 次方。也就是一个 $c$ 位数，除了首位是 $1$ 剩下 $c-1$ 位全是 $0$。

然后我们就可以把 $x,y$ 的最后 $c-1$ 位设作 $0$，就可以保证 $
x,y$ 是 $z$ 的倍数。

然后我们把 $z$ 看作一个计数单位，让 $x,y$ 同时除以 $z$，得出的商叫做 $x',y'$。可以发现 $x'$ 和 $y'$ 一定互质。

那么我们就很容易想到 $10^{a-c}$ 次方和 $10^{b-c+1}-1$ 次方互质。用式子表现出来不舒服，让我们来看看形象化的例子：

- $z=100$
- $x=100000$
- $y=99900$

可以发现，除以 $z$ 后 $a$ 有 $2,5$ 的质因子，而 $b$ 没有，所以 $a,b$ 互质。

代码很容易写。

```cpp
#include<iostream>
using namespace std;
#define int long long
void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	cout<<1;
	for(int i=2;i<=a;++i)
		cout<<0;
	cout<<' ';
	for(int i=1;i<=b-c+1;++i)
		cout<<9;
	for(int i=1;i<c;++i)
		cout<<0;
	cout<<endl;
}
#undef int
int main(){
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：hubin1 (赞：0)

# GCD Length

## 题意
给出 $3$ 个数，求 $2$ 个数 $x$ 和 $y$。这 $3$ 个数分别表示 $x$ 的长度、$y$ 的长度和 $x$ 与 $y$ 的最大公因数的长度。

## 思路
1. 最大公因数可以是 $10^c$，这是最方便的。
2. 我们可以用让 $x$ 为 $10^a$、$y$ 为某个数乘 $10^{c-1}$ 的积的形式。
3. 在第二步中给 $y$ 乘的是 $10^{c-1}$ 而不是 $10^c$ 的原因是：在 $x$ 中，它还有一个数字 $1$，这个数字占 $1$ 位。因此，要乘 $10^{c-1}$。
4. 在第二步中这个“某个数”可以是连续的 $b-c$ 个数字，因为这样利于操作。这个数字并不唯一，例如 $7$、$9$。

## Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        cout<<1;
        c--;//因为上一行输出了一个1
        for(int j=2;j<=a;j++)
            cout<<0;
        cout<<" ";
        for(int j=1;j<=b-c;j++)
            cout<<7;
        for(int j=1;j<=c;j++)
            cout<<0;//保证gcd的位数
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1511B)

**构造题**。

首先让 $\gcd(x,y)=10^{c-1}$，也就是 $x$ 和 $y$ 最大公因数后面有 $c-1$ 个 $0$，最前面加个 $1$。就能满足 $\gcd(x,y)$ 的位数是 $c$。

接着，让 $x=10^{a-1}$ 次方，非常简单。

$y$ 有一点棘手，因为 $\frac{y}{\gcd(x,y)}$ 要与 $\frac{x}{\gcd(x,y)}$ 互质。

我们可以在 $y$ 前面构造 $b-c+1$ 个 $9$。

再输出 $c-1$ 个 $0$ 就可以了，这样构造出来一定互质。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,t;
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c;
		cout<<1;
		for(int i=1;i<=a-1;i++)
			cout<<0;
		cout<<" ";
		for(int i=1;i<=b-c+1;i++)
			cout<<9;
		for(int i=1;i<=c-1;i++)
			cout<<0;
		cout<<endl; 
	}
	return 0;
} 
```


---

## 作者：DANIEL_x_ (赞：0)

显然可以考虑到 $\gcd(x,y)=10^{c-1}$，也就成为了一个 $c$ 位数。

之后要互质。所以考虑 $10^{a-c}$ 和 $10^{b-c+1}-1$。

思路非常简单，复杂度：$O(T \times \max(a,c,b-c+1))$。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a,b,c,ans1,ans2;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		ans1=ans2=1;c--;
		cout<<'1';
		for(int i=2;i<=a;i++) 
			cout<<'0';
		cout<<' ';
		for(int i=1;i<=b-c;i++)
			cout<<'9';
		for(int i=1;i<=c;i++)
			cout<<'0';
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：TainityAnle (赞：0)

**这是一篇比较暴力的题解**

~~发现下面的 dalao 讲的有些模糊，这里做了补充。~~

首先看数据，所有数据都不超过 $9$，所以直接考虑暴力。

一个一个算 $x$ 和 $y$ 的 $\gcd(x,y)$ 肯定是过于暴力了。所以我们需要考虑一下几点。

- 肯定是要构造 $x$ 和 $y$ 的，必需要考虑如何使 $x$ 和 $y$ 含有公因数  $\gcd(x,y)$。

这样的话就需要构造到一定程度，乘上一个 $\gcd(x,y)$。

- 需要考虑“一定程度”是什么。

这个时候就需要回归题面。

> - 去掉前导 $0$ 后的十进制整数 $x$ 有 $a$ 位。

> - 去掉前导 $0$ 后的十进制整数 $y$ 有 $b$ 位。

> - 去掉前导 $0$ 后的十进制整数 $\gcd(x, y)$ 有 $c$ 位。

$len(a\times b)=len(a)+len(b)$ 或 $len(a)+len(b)+1$。

我们必须要乘一个 $\gcd(x, y)$ 并且 $\gcd(x, y)$ 有 $c$ 位。所以我们只需要构造到 $len(a)\le a-c$，$len(b)\le b-c$ 即可。这样的话就能保证去掉前导 $0$ 后的十进制整数 $x$ 有 $a$ 位，去掉前导 $0$ 后的十进制整数 $y$ 有 $b$ 位。

- $\gcd(x,y)$ 如何构造？

这个其实不重要，就随便定一个 $c$ 位数就好了，毕竟答案和它没关系。最简单的定 $c$ 位数的方法就是 $10^{c-1}$ 就行了。

- 如果用构造的话，需要考虑如何使 $x$ 和 $y$ 互质。

让两个数从一开始构造就没有公因数，只需要让它们一直乘一个质数就好了。这里是 $10^9$，不会超时，保险起见就找两个最小的质数。

**AC Code**

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int T,a,b,c,x,y; 
int ws(int x){
	int k=0;
	while(x) x/=10,k++;
	return k;
}
int main(){
	cin>>T;
	while(T--){
		x=y=1; 
		cin>>a>>b>>c;
		whįle(ws(x)<=a-c) x*=2;
		while(ws(y)<=b-c) y*=3;
		x*=pow(10,c-1),y*=pow(10,c-1);
		cout<<x<<' '<<y<<endl;
	}
	return 0;
}
```

---

## 作者：linyuhao (赞：0)

# 思想
可以先构造 $\gcd(x,y)$，让 $\gcd(x,y)$ 只包含质因数 $2$。并满足有 $c$ 位。
那么让 $x$ 只乘上 $3$，$y$ 只乘上 $5$。不会影响 $\gcd(x,y)$。
只要让 $x$ 一直乘到有 $a$ 位，$y$ 一直乘到有 $b$ 位就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int check(long long s){
	int weishu=0;
	while(s){
		s/=10;
		weishu++;
	}
	return weishu;
}//判断位数
long long a[10]={0,2,16,128,1024,16384,131072,1048576,16777216,134217728};
//只包含质因数2
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c;
		cin>>a>>b>>c;
		long long x=a[c];long long y=a[c];
		while(check(x)!=a){
			x*=3;
		}
		while(check(y)!=b){
			y*=5;
		}
		cout<<x<<" "<<y<<endl;
	}
	return 0;
}
```



---

## 作者：sjr3065335594 (赞：0)

## 分享一个玄学做法

首先随便构造一个 $c$ 位的随机数作为最大公因数，然后把这个最大公因数用两个变量存储，对它们不断乘两个互质数（必须小于十，我用的是二和三），直到位数达到 $a$ 和 $b$，这样就能保证这两数的最大公因数不变。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b, c;
int p[]={0,1,12,123,1234,12345,123456,1234567,12345678,123456789,1234567890};//随便构造几个随机数，用rand也没问题
int main() {
    cin >> t;
    while(t--) {
        cin >> a >> b >> c;
        int gcd = p[c];//构造c位随机数
        int x = gcd, y = gcd;//存储
        while((int)(log10(x))+1 < a)//在位数不够时不断乘
            x *= 2;
        while((int)(log10(y))+1 < b)
            y *= 3; 
        cout << x << " " << y << " " << endl;
    }
    return 0;//完美结束
}
```

PS：$\left\lfloor \operatorname{lg} n\right\rfloor+1$ 是求 $n$ 的位数。

---

## 作者：Aw顿顿 (赞：0)

给定 $a,b,c\in \mathbb{Z}$，求 $x,y\in\mathbb{N_+}$ 满足：

- 在去掉前导零的条件下
- $x$ 有 $a$ 位，$y$ 有 $b$ 位，$\gcd(x,y)$ 有 $c$ 位。

本题有至多 $285$ 组多测，数据范围：

- $1\le a,b\le 9$。
- $1\le c\le\min(a,b)$。

## 解法

构造题。

显然令 $\gcd(x,y)=10^{c-1}$ 是保证其有 $c$ 位的最直接的想法，接下来我们需要找出合法的 $x$ 和 $y$。

试问这样的 $x$ 和 $y$ 的位数必须为 $a$ 和 $b$ 时，他们需要互质，那么我们让他们相差 $1$。

当然你用质数来构造也是挺不错的想法。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,ans1,ans2;
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&a,&b,&c);c--;
		cout<<'1';
		for(int i=1;i<a;i++)cout<<'0';
		cout<<' ';
		for(int i=0;i<b-c;i++)cout<<'9';
		for(int i=0;i<c;i++)cout<<'0';
		puts("");
	}return 0;
}
```

复杂度 $O(T\max(a,b))$，是个常数，然后你就可以忽略他了，用质数构造可以做到 $O(T\log\min(a,b))$

---

## 作者：dead_X (赞：0)

## 题意
给定 $a,b,c$，你需要输出两个数 $x,y$，满足以下三个要求：

* $x$ 在十进制下有 $a$ 位。 
* $y$ 在十进制下有 $b$ 位。 
* $\gcd(x,y)$ 在十进制下有 $c$ 位。 
## 思路
注意到一个数乘 $2,3,6$ 位数要么不变，要么增加 $1$。

所以设 $x=6^p\times 2^q$，$y=6^p\times 3^r$，调整 $p,q,r$ 即可。
## 代码
```cpp
// Problem: B. GCD Length
// Contest: Codeforces - Educational Codeforces Round 107 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1511/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
int d(int x)
{
	int D=0;
	while(x) x/=10,++D;
	return D;
}
signed main()
{
    for(int T=read();T--;)
    {
    	int a=read(),b=read(),c=read();
    	int C=1;
    	while(d(C)<c) C*=6;
    	int A=C,B=C;
    	while(d(A)<a) A*=2;
    	while(d(B)<b) B*=3;
    	printf("%lld %lld\n",A,B); 
    }
	return 0;
}
```

---

## 作者：YLWang (赞：0)

~~无内鬼，来点随机~~

考虑令 $C = 10^k$。于是现在就要找到两个互质的 $a = \dfrac{A}{C}, b = \dfrac{B}{C}$ 满足对应的位数。

互质是很好构造的，取质数就行。

质数是稠密的，随机就行。

```cpp
mt19937 rnd(time(0));
int p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
inline int random(int l,int r) {
	return rnd()%(r-l+1)+l;
}
int main() 
	int T=read();
	while(T--) {
		int a=read(),b=read(),c=read();
		a-=c-1,b-=c-1; 
		int x=random(p10[a-1],p10[a]-1),y=random(p10[b-1],p10[b]-1);
		
		while(__gcd(x,y)!=1) {
			x=random(p10[a-1],p10[a]-1),y=random(p10[b-1],p10[b]-1);
		}
		printf("%d %d\n",x*p10[c-1],y*p10[c-1]);
	}
	return FastIO::Fflush(),0;
}
```

---

