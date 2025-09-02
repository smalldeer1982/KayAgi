# Finite or not?

## 题目描述

有 $n$ 组数据，每一组数据读入一个分数的分子 $p$、分母 $q$ 和进制 $b$（分子、分母均以十进制读入）求在 $b$ 进制下 $\frac{p}{q}$ 是否为有限小数。如果是，输出 `Finite`，否则输出 `Infinite`

## 样例 #1

### 输入

```
2
6 12 10
4 3 10
```

### 输出

```
Finite
Infinite
```

## 样例 #2

### 输入

```
4
1 1 2
9 36 2
4 12 3
3 5 4
```

### 输出

```
Finite
Finite
Finite
Infinite
```

# 题解

## 作者：mraymes (赞：10)

~~刚刚打完CF比赛回来的我。。。第三题就差几分钟就做出来了气死我了~~

这题目就是考数学的。。。

首先我们要把分数给约分了，否则无法判断是否为有限小数。

接着就是判断是否为有限小数~~（从现在起分子的存在感降至0）~~

如果进制的质因数（忽略指数）中包括分母的所有质因数（同样忽略指数），就说明这个分数能化为有限小数。否则就不是有限小数（就是循环小数）。

- 这里质因数的意思就是将一个数分解质因数之后，忽略指数（去掉重复的）之后剩下的因数。
- 比如 $ 16 $ 的质因数在这里就只算一个 $ 2 $，$ 24 $ 的质因数为 $ 2 $ 和 $ 3 $

由于数据超级超级超级大（分母与进制都小于等于 $ 10^{18} $），把它们都分解质因数是不可能的~~（如果你不想 TLE）~~，所以必须用 GCD 来解决。

- 每次把 $ q $ 除以 $ \mathrm{gcd(\mathit{q}, \mathit{b})} $ 直到 $ q = 1 $ 或 $ \mathrm{gcd(\mathit{q}, \mathit{b})} = 1 $。这样可以把 $ q $ 和 $ b $ 共有的因子都从 $ q $ 中清除。如果当 $ \mathrm{gcd(\mathit{q}, \mathit{b})} $ 为 $ 1 $ 的时候 $ q $ 仍然不为 $ 1 $，意味着 $ b $ 和 $ q $ 已经互质而 $ q $ 中还有 $ b $ 没有的因子，说明在 $ b $ 进制下 $ \frac{p}{q} $ 不是有限小数。输出 `Infinite`。如果 $ q = 1 $ 则说明 $ q $ 的所有因子都是 $ b $ 的因子，在 $ b $ 进制下 $ \frac{p}{q} $ 是有限小数。输出 `Finite`。

	可是会TLE，所以需要优化↓

- 其实如果 $ b $ 含有 $ q $ 所没有的因子，可以把它们清除掉但不影响结果。所以每次清除 $ q $ 中重复的因子之前可以把 $ b $ 中多余的因子清除掉（将 $ b $ 赋值为 $ \mathrm{gcd(\mathit{q}, \mathit{b})} $）。此时 $ \mathrm{gcd(\mathit{q}, \mathit{b})} $ 不影响但是每次算的速度会增加。

↓↓↓具体见代码↓↓↓

```cpp
#include <bits/stdc++.h>

using namespace std;

long long gcd(long long x, long long y) // 求 GCD
{
	if (x == 0) return y;
	return gcd(y % x, x);
}

long long readll() // 快速读入
{
	char ch;
	long long num = 0;
	bool firstch = true;

	while (ch = getchar())
	{
		if (!firstch && isspace(ch))
			return num;
		if (!isspace(ch))
		{
			firstch = false;
			num = num * 10 + (long long)ch - (long long)'0';
		}
	}
}

int n;
long long p, q, b;

int main()
{
	scanf("%d", &n);

	while (n--)
	{
		p = readll();
		q = readll();
		b = readll();

		q /= gcd(p, q); // 约分

		while (true)
		{
			b = gcd(q, b); // 清除 b 中多余的因子

			if (b == 1) // 如果 b = 1 代表多余因子已经没有了, 判断是否为有限小数
			{
				if (q == 1) cout << "Finite\n"; // q 中不含有 b 所没有的因子，是有限小数
				else cout << "Infinite\n"; // 否则就是无限小数
				break; // 退出
			} // 这一段一定要放在下一段代码的前面
              // 如果 b = 1 而且没有及时退出，会无限 q = q / 1

			while (q % b == 0) q /= b; // 清除 q 中重复因子
		}
	}

	return 0;
}
```

---

## 作者：PENTIUM_80586 (赞：5)

## Finite or not?

### 阅读题干
 
题意非常好理解，就是在 $b$ 进制下 $\frac{p}{q}$ 是否是有限小数。

由输出样例 $2$ 可知，整数也属于有限小数（当然两者在数学里是有界限的）

### 分析题目

首先，介于 $\le 10^{18}$ 的数据，我们必须使用大小高于 int 的数据类型。而这就意味着，如不考虑太多，我们将用**数位**计算规律。

但是，光是整数部分，位数就多于 int 类型，并且，如果强制通过小数数位得到规律，可能会不准确（例如：循环节长度超过 double 范围)

所以，我们就应进一步思考，是否题目里内含我们即将证明的公式？

正解思考如下：

我们要明确，不同进制下的分数有什么规律。

我们从 $10$ 进制入手，对于 $10$ 进制分式 $\frac{1}{x}$，将 $x$ 分解质因数，找一个简单的规律。

注：不熟悉唯一分解定理的[请点这里。](https://blog.csdn.net/g1129qaz/article/details/107913133)

|$x$|数值（保留五位小数）|是不是有限小数|分解质因数|
| -----------: | -----------: | -----------: | -----------: |
|$1$|$1.00000$|是|无|
|$2$|$0.50000$|是|$2=2$|
|$3$|$0.33333$|不是|$3=3$|
|$4$|$0.25000$|是|$4=2^2$|
|$5$|$0.20000$|是|$5=5$|
|$6$|$0.16667$|不是|$6=2\times 3$|
|$7$|$0.14286$|不是|$7=7$|
|$8$|$0.12500$|是|$8=2^3$|
|$9$|$0.11111$|不是|$9=3^2$|
|$10$|$0.10000$|是|$10=2\times 5$|

由此，我们发现，那些符合有限小数的分式，其分母都可分解为若干个 $2$ 和若干个 $5$ 的乘积。

第一次见到这道题的人可能会在这一步卡住，但是，当我们进一步思考时，我们便会发现：进制数 $10$ 的唯一分解也是 $10=2\times 5$。

我们会想，是不是对于每个进制，都符合：在这个进制下所有是有限小数的分数，它**化简后**分母质因数的种类与进制数质因数的种类是完全一样的？

在考场上，我们可以用计算器验证 $2$ 进制，$8$ 进制以及 $16$ 进制的数，以进一步确认我们的猜想。

并且，我们还有一个非常容易理解的结论：在任何进制的情况下，如果一个分数可以化成有限小数，那它**必然**可以通过多次乘进制数成为整数。

### 解题思路

有了这两个结论，我们回到题目上。我们考虑先将分数用 $p$，$q$ 的最大公约数化简分数，再不断让 $q$ 除以 $\gcd(b,q)$，相当于不断乘 $b$，将 $q$ 化为 $1$，成为正整数。

如果 $q$ 可以被约为 $1$，则证明是有限小数，输出```Finite```，否则输出```Infinite```。

实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n;scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		long long p,q,b;scanf("%lld%lld%lld",&p,&q,&b);
		q/=__gcd(p,q);
		long long g=__gcd(b,q);
		while(q>1 && g!=1) q/=g,g=__gcd(b,q);
		if(q==1) printf("%s\n","Finite");
		else printf("%s\n","Infinite"); 
	}
	return 0;
}
//本人善于设置 long long，原因是吃了一道题的亏，代码是合理的
```

数据可能差值过大，因此此代码只可过部分测试点，其余超时，所以我们考虑优化。

我们可以将 $b$ 设为 $\gcd(b,q)$，这样既可以加快约分，又可以减少不必要的最大公约数求解。

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n;scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		long long p,q,b;scanf("%lld%lld%lld",&p,&q,&b);
		q/=__gcd(p,q);
		while(b!=1){
			b=__gcd(b,q);
			while(!(q%b) && b!=1) q/=b;
		}
		if(q==1) printf("%s\n","Finite");
		else printf("%s\n","Infinite"); 
	}
	return 0;
}
```




---

## 作者：simonG (赞：3)

### 前言
为什么会发生无限循环小数？  
下面用十进制解释：
$$\dfrac{1}{3}=0.33…,\dfrac{1}{7}=0.142857…$$
### 详解
$$\dfrac{1}{2}=0.5,\dfrac{1}{5}=0.2,\dfrac{1}{10}=0.1$$
由前言的解释，我们可以发现，在10进制下，与10互质的分母数可构成无限循环小数。再看上面的样例，似乎与10互质的都可以。  
$$\dfrac{1}{6}=0.166…,\dfrac{1}{30}=0.033…$$
再看上面的例子，尽管$\gcd(10,6)=2$，但$6\div 2=3$，$\gcd(10,3)=1$。  
同理，$\gcd(10,30)=10$，但$\gcd(\dfrac{30}{10},10)=1$。  
$$\dfrac{1}{2^3}=0.125,\dfrac{1}{5^2}=0.04$$
同理。  
得出理论：一个分母，无限与该进制数进行去最大公因数，若结果为$\gcd(1,b)$，则$\texttt{Finite}$。  
最后， 
$$\dfrac{1}{q}\Longrightarrow \texttt{Finite}\Rightarrow \dfrac{p}{q}\Longrightarrow \texttt{Finite}$$
$$\dfrac{1}{q}\Longrightarrow \texttt{Infinite}\nRightarrow \dfrac{p}{q}\Longrightarrow \texttt{Ininite}$$
$$\dfrac{p}{q}\Longrightarrow\dfrac{p\div \gcd(p,q)}{q\div \gcd(p,q)}\Longrightarrow \texttt{Ininite}\Leftrightarrow \texttt{Finite}$$

### 代码
自行实现即可

---

## 作者：破壁少年 (赞：2)

### CF983A Finite or not? 题解

------------

~~这道题是我们作业题，但本蒟蒻写了很长时间~~

首先找规律，枚举一些 10 进制的无线小数进行推断，例如 $\frac{1}{3}$，$\frac{1}{6}$，$\frac{1}{3}$，$\frac{1}{7}$，发现分数的分母是和进制 $b$ 是有关系的，分母 $q$ 如果能被 $p \times b^{k}$ 整除，就是有限小数，否则为无限小数，所以考虑分解质因数，但 $b$ 和 $q$ 为  $10^{18}$ 暴力拆质因数超时，所以每次求出 $b$ 和 $q$ 的最大公约数，把 $q$ 中 $q$ 与 $b$ 重复的因子删去，再把 $b$ 赋成 $b$ 和 $q$ 的最大公约数即可，不会超时。

注意：一定要把分数化到最简，要用快读或 cin 优化。

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define naipaokuikui main
long long gcd(long long a,long long b) {
    return b==0?a:gcd(b,a%b);
}
int naipaokuikui(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	long long t;
	cin>>t;
	while(t--){
		
		long long p,q,b;
		cin>>p>>q>>b;
		q=q/gcd(p,q);
		while(b!=1)
		{
			b=gcd(q,b); 
			q/=b;
		};
		if(q==1) cout<<"Finite"<<endl;
		else cout<<"Infinite"<<endl;
	}
	return 0;
}
```


---

## 作者：Ender_NaCl (赞：1)

给定 $p$，$q$，$b$，判断 $\dfrac{p}{q}$ 在 $b$ 进制下是否为有限小数

先介绍一下十进制分数怎么转成 $b$ 进制数

分子每次乘上 $b$，再取整数部分，直到分子是分母的倍数时结束

比如 $(\dfrac{7}{12})_{10} = (0.33)_6$

接着回到题目

先约分 $\dfrac{p}{q}$，此时 $p$，$q$ 互质，我们再来思考一下怎么样才能在 $b$ 进制下形成有限小数

我只要使得我进行了多次乘 $b$ 的操作后消掉分母 $q$

即 $q \mid pb^k$ 由于 $p$，$q$ 互质，化简为 $q \mid b^k$

因为 $q$，$b$ $\le 10^{18}$，所以代码里不太好直接进行类似质因数分解的操作

不过我们可以利用这个思想

令 $q = p_1^{m_1} \times p_2^{m_2} \times \cdots \times p_n^{m_n}$，$p_i$ 为质数且互不相同

由于 $b$ 的个数不定，所以不用考虑质因数分解后的指数，只需要确保 $b$ 含有 $p_1,p_2 \cdots p_n$ 即可

这么一来，其实可以用 $\gcd$ 求解

上代码

```cpp
#include <iostream>

#include <cmath>

#define ll long long

using namespace std;

inline ll read() //一定要写，不然被卡常 
{
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

ll gcd(ll n,ll m)
{
	if(m == 0) return n;
	else return gcd(m,n % m);
}

int main()
{
	int T;
	T = read();
	while(T--)
	{
		ll p,q,b,i,G;
		p = read();
		q = read();
		b = read();
		q = q / gcd(p,q); //约分 
		while(b != 1)
		{
			b = gcd(q,b); //去除多余因数 
			q/=b; //把重复因数除掉 
		}
		if(q == 1) cout<<"Finite"<<endl; //q的质因数被b的质因数包含，在除完后剩1 
		else cout<<"Infinite"<<endl;
	}
	return 0;
}
```


---

## 作者：Aw顿顿 (赞：1)

数学题。

> **命题 $\small 1.0$**：在 $\gcd(p,q)=1$ 的情况下，若 $\dfrac{p}{q}$ 是有限小数，那么 $\dfrac{1}{q}$ 就一定是有限小数。

那么可以继续推导：

> **命题 $\small 1.1$**： 一定存在 $x$ 使得 $b$ 进制下的 $\dfrac{b^x}{q}$ 为整数。

由于我们还可以由此推导出另一个命题是：

> **命题 $\small2.0$**： 若存在 $\dfrac{b^x}{q}$ 为整数则存在$\dfrac{\gcd(b,q)^y}{q}$ 为整数。

那么就可以推式子：

令 $s=\dfrac{q}{\gcd(b,q)}$，存在：

$$\dfrac{\gcd(b,q)^y}{s}$$

为整数。

那么就可以代码实现。
  
  

---

## 作者：Pecco (赞：1)

显然，既约分数 $\displaystyle\frac pq$ 是有限小数等价于 $\displaystyle\frac 1q$ 是有限小数。

如果 $\displaystyle\frac1q$ 是 $b$ 进制下的有限小数，那么一定存在正整数 $n$ 使得 $\displaystyle\frac{b^n}{q}$ 为整数，实际上这等价于存在正整数 $m$ 使得 $\displaystyle\frac{(\gcd(b,q))^m}{q}$ 为整数 [1]，进一步等价于存在正整数 $m$ 使 $\displaystyle\frac{(\gcd(b,q))^{m+1}}{q}=\frac{(\gcd(b,q))^m}{\frac{q}{\gcd(b,q)}}$ 是整数。现在我们把问题规模缩小了，可以递归求解。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool check(ll b, ll q) // 检查是否存在n使得b^n/q为整数
{
    ll d = __gcd(b, q);
    if (d == 1) // 递归出口，如果b, q互质，那除非q为1，否则肯定不成立
        return q == 1;
    return check(d, q / d); // 递归
}
int main()
{
    ios::sync_with_stdio(false);
    ll t, p, q, b;
    cin >> t;
    while (t--)
    {
        cin >> p >> q >> b;
        cout << (check(b, q / __gcd(p, q)) ? "Finite" : "Infinite") << endl;
    }
    return 0;
}
```


---
[1]：必要性显然。充分性：如果存在正整数 $n$ 使得 $\displaystyle\frac{b^n}{q}$ 为整数，$b$ 一定拥有 $q$ 的每个质因数，那么 $\gcd(b,q)$ 也拥有 $q$ 的每个质因数，那么肯定存在正整数 $m$ 使得 $\displaystyle\frac{(\gcd(b,q))^m}{q}$ 为整数。

---

## 作者：囧仙 (赞：1)

## 题目大意

$T$ 组询问，每次询问 $\frac{n}{m}$ 在 $b$ 进制下是否为循环小数。

## 题解

先将该分数化简为最简分数，即 $n,m$ 同时除以 $\gcd(n,m)$ 。此时有 $n,m$ 互质。

假定 $\frac{n}{m}$ 在 $b$ 进制下可以表示为有限小数。不妨设小数点后共有 $k$ 位。

于是，我们有：

$$\frac{n\times b^k}{m} \in \Bbb N^* , \iff m \ | \ n\times b^k ,\iff m \ | \ b^k$$

假设 $p$ 为 $m$ 的任意一个质因子。由于 $k$ 可以足够大，因此 $b$ 中至少应该含有一个 $p$ 。于是，问题转化为，$m$ 的每个质因子，都应该是 $b$ 的质因子。考虑如何求解。

由于 $m \le 10^{18}$ ，因此 $m$ 中每个质因子的次数不会超过 $60$ 。我们计算出 $b^{60}$ ，那么它对应质因子的次数必定不小于 $m$ 。于是，该分数可化为循环小数，当且仅当：

$$b^{60} \equiv 0 \pmod m$$

要注意的是，由于题目给出的数字较大，可能需要用快速乘法。

## 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define up(l,r,i) for(int i=l,END=r;i<=END;++i)
#define dn(r,l,i) for(int i=r,END=l;i>=END;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
i64 qread(){
    i64 w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
i64 mul(i64 x,i64 y,i64 p){
    i64 r=0,t=x%p; while(y){
        if(y&1) r+=t; t<<=1,y>>=1;
        if(t>=p) t-=p; if(r>=p) r-=p;
    }
    return r;
}
i64 pwr(i64 a,i64 b,i64 p){
    i64 r=1,t=a; while(b){
        if(b&1) r=mul(r,t,p); t=mul(t,t,p),b>>=1;
    }
    return r%p;
}
int main(){
    dn(qread(),1,T){
        i64 n=qread(),m=qread(),b=qread(),d=__gcd(n,m);
        n/=d,m/=d;
        puts(pwr(b,60,m)?"Infinite":"Finite");
    }
    return 0;
}
```


---

## 作者：wzt2012 (赞：0)

### 题目大意

[Finite or not?](https://www.luogu.com.cn/problem/CF983A)

### 解题方法

思路是**将小数部分采用十进制转二进制**。

- 于是我们将它看成分数，采用质因子分解的形式，每次的相除就是消去公有的质因子。

转化成 `while(q / gcd(q, b))` 的形式。

但是数字会很大，分解 $\text{log\ n}$，gcd 是 $\text{log\ n}$。

- 对于 `gcd != 1` 的时候，先整除完。再进行上述步骤就优化成 $\text{n\ log\ num}$。考虑 $q$ 是否能否 $b^n$ 整除。


-------

$\large\colorbox{#052242}{\color{white}\texttt{\:TLE code:\;}}$

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, gcd, gcd1;
ll p, q, b;
int main(){
    std::cin >> n;
    for(int i = 1; i <= n; i ++){
        std::cin >> p >> q >> b;
        gcd = __gcd(p, q);
        p /= gcd, q /= gcd;
        if(q == 1){
            printf("Finite\n");
        }else{
            while(true){
                gcd1 = __gcd(q, b);
                while(gcd1 != 1 && (q % gcd1 == 0)) q /= gcd1;
                if(gcd1 == 1 || q == 1) break;
            }
            if(q == 1) std::cout << "Finite" << endl; 
            else std::cout << "Infinite" << endl; 
        }
    }
	return 0;
} 

```
---

我们发现超时了，后来加个快读就好了。

---

$\large\colorbox{#52C410}{\color{white}\texttt{ AC code: }}$

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, gcd, gcd1;
ll p, q, b;
inline ll read(){
	ll x = 0, f = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = x * 10 + c - 48;
		c = getchar();
	}
	return x * f;
}
int main(){
    std::cin >> n;
    for(int i = 1; i <= n; i ++){
		p = read(), q = read(), b = read();
        gcd = __gcd(p, q);
        p /= gcd, q /= gcd;
        if(q == 1){
            printf("Finite\n");
        }else{
            while(true){
                gcd1 = __gcd(q, b);
                while(gcd1 != 1 && (q % gcd1 == 0)) q /= gcd1;
                if(gcd1 == 1 || q == 1) break;
            }
            if(q == 1) std::cout << "Finite" << endl; 
            else std::cout << "Infinite" << endl; 
        }
    }
	return 0;
} 
```

---

## 作者：RockyYue (赞：0)

# 解题思路

作为蓝题太水了，红题难度。

小学奥数学过，一个 $b$ 进制最简分数为有限小数当且仅当分母的质因子与 $b$ 完全相同。

所以先化成最简分数再用辗转相除就行了。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const char *s1 = "Finite", *s2 = "Infinite";
signed main() {
	ios :: sync_with_stdio(0);
	int _;
	cin >> _;
	while (_--) {
		int n, m, b;
		cin >> n >> m >> b;
		if (n % m == 0) {
			puts(s1);
			continue;
		}
		int G = __gcd(n, m);
		m /= G;
		while (m > 1 && (G = __gcd(b, m)) != 1) {
			while (m % G == 0) {
				m /= G;
			}
		}
		puts(m <= 1 ? s1 : s2);
	}
    return 0;
}
```

Good Good 贺题，Day Day Up！！

---

