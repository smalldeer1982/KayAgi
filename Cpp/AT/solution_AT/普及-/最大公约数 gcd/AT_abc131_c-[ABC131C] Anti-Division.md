# [ABC131C] Anti-Division

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc131/tasks/abc131_c

整数 $ A,B,C,D $ が与えられます。$ A $ 以上 $ B $ 以下の整数のうち、$ C $ でも $ D $ でも割り切れないものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ A\leq\ B\leq\ 10^{18} $
- $ 1\leq\ C,D\leq\ 10^9 $
- 入力はすべて整数である

### Sample Explanation 1

$ 5,7 $ が条件を満たします。

## 样例 #1

### 输入

```
4 9 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
10 40 6 8```

### 输出

```
23```

## 样例 #3

### 输入

```
314159265358979323 846264338327950288 419716939 937510582```

### 输出

```
532105071133627368```

# 题解

## 作者：苏联小渣 (赞：3)

## 题目大意

求 $[A,B]$ 内不能被 $C$ **或** $D$ 整除的数。

## 分析

看到数据范围，不可能暴力枚举，考虑容斥，然后就变成了一道二年级数学题。

**容斥原理：** 

$Card (A \cup B)=Card(A)+Card(B)-Card(A\cap B)$

我们设 $[A,B]$ 内：

**·** 不能被 $C$ 整除的数有 $U$ 个；

**·** 不能被 $D$ 整除的数有 $V$ 个；

**·** 既不能被 $C$，又不能被 $D$ 整除的数有 $W$ 个；

**注意：既不能被 $C$，又不能被 $D$ 整除指的是不能被 $C$，$D$ 的最小公倍数整除。**

$\therefore$ 不能被 $C$ 或 $D$ 整除的数有 $U+V-W$ 个。

接着，我们再写一个函数，求区间 $[A,B]$ 内能被参数 $x$ 整除的数的个数。方法如下：

1、寻找第一个可以被 $x$ 整除的数；

2、寻找最后一个可以被 $x$ 整除的数；

3、等差数列公式 $\frac{R-L}{x}+1$ 求解个数。

最后再用总数减去可以整除的个数即可。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int x, y, z, w, s;
int calc(int p){
	int l = x + p - (x%p==0?p:x%p), r = y - y % p;
	return (r - l) / p + 1;
}
signed main(){
	scanf ("%lld%lld%lld%lld", &x, &y, &z, &w);
	printf ("%lld\n", y - x + 1 - calc(z) - calc(w) + calc(z*w/(__gcd(z, w))));
   //__gcd在洛谷评测系统下可以调用，一些评测系统下可能要手打
   //a*b/gcd(a,b)是求最小公倍数
	return 0;
}
```

附：还是把最大公约数的求法放出来：

```cpp
int gcd(int x, int y){
	if (y == 0) return x;
   else return gcd(y, x%y);
}
```

---

## 作者：seac_blue (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4237)

### 题意

给出四个整数 $A,B,C,D$。查找 $[A,B]$ 之间不能被 $C$ 或 $D$ 整除的整数数。

### 思路

前置知识：容斥原理。

容斥原理最基本的柿子如下：

$${A}\cup B\cup C = A+B+C - A\cap B - B\cap C - C\cap A + A\cap B\cap C$$

尝试用充斥原理分析该题。要求 $[A,B]$ 直接不能被 $C$ 或 $D$ 整除的正整数数，即：

1. 求出 $[A,B]$ 之间所有的正整数个数

2. 减去范围内能被 $C$ 整除的正整数个数

3. 减去范围内能被 $D$ 整除的正整数个数

4. 加上范围内同时被 $C$ 和 $D$ 整除的正整数个数

步骤 1 的结果容易发现是 $B-A+1$。

步骤 2,3,4 可以用一个函数实现：在 $[A,B]$ 范围内能被 $x$ 整除的数的个数。

在 $[1,A]$ 范围内满足条件的数显然是 $\lfloor\dfrac{A}{x}\rfloor$，在 $[1,B]$ 范围内满足条件的数显然是 $\lfloor\dfrac{B}{x}\rfloor$。

两式相减，易得 $(A,B]$ 范围内满足条件的数为 $\lfloor\dfrac{B}{x}\rfloor-\lfloor\dfrac{A}{x}\rfloor$。考虑到 $A$ 是 $x$ 的倍数的情况，对结果作小处理即可。

值得提出的是，**同时被 $C$ 和 $D$ 整除**的数不一定是能被 $C\times D$ 整除的数，而是**能被 $\text{lcm}(C,D)$ 整除的数**。由于 $\text{lcm}(C,D)=\dfrac{C\times D}{\gcd(C,D)}$，计算即可。

### 代码

代码省略了头文件和快读部分，读者可以自行添加或修改。

```cpp
// 头文件
using namespace std;
typedef long long ll;

ll read(){/*快读*/}
ll a,b,c,d;
ll f(ll div){// 在 [a, b] 范围内能被 div 整除的数的个数
	ll rval=b/div;
	ll lval=a/div;
	ll fix=0;
	if(!(a%div))fix=1;// 如果 a 能被 div 整除，则 a 也加入答案
	return rval-lval+fix;
}

ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}

int main(){
	a=read();b=read();c=read();d=read();
	ll g=gcd(c,d);
	printf("%lld\n",b-a+1-f(c)-f(d)+f(c*d/g));
        // c*d/g 即为 lcm(c, d) 的值
	return 0;
}
```

---

## 作者：Astatinear (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4237)

### 思路
**容斥问题**

题目意思:输入四个数字 $a,b,c,d$。求在 $a$ 到 $b$ 这个区间中有多少个数满足不整除 $c$ 或 $d$。

我的思路是运用容斥原理。

首先我们先求出在 $a$ 到 $b$ 这个区间中有 $x$ 个数不整除 $c$ ,然后再求出 $a$ 到 $b$ 这个区间中有 $y$ 个数不整除 $d$,最后再求出这个区间中有 $z$ 个数满足不整除 $c$ 和 $d$。

我们假设 $a$ 到 $b$ 这个区间中总共有 $w$ 个数。

则通过容斥原理,最终答案为 $w-x-y+z$。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
long long __gcd(long long x,long long y)
{
	long long aa=x,bb=y;//将这两个数先存下来
	while(aa!=bb)//他们两个不等的时候就继续减下去
	{
		if(aa>bb)//判断大小
		{
			aa=aa-bb;//辗转相减
		}
		else 
		{
			bb=bb-aa;//辗转相减
		}
	}
	return x*y/aa;//这里返回x,y的最小公倍数
}
ll a,b,c,d;
int main()
{
    cin>>a>>b>>c>>d;//输入
    //通过容斥原理进行计算
    ll k=__gcd(c,d);
    ll a1=b/c-(a-1)/c,a2=b/d-(a-1)/d,a3=b/k-(a-1)/k,a4=b-a+1;
    ll ans=a4-a1-a2+a3;
    cout<<ans<<endl;//输出
}
```

---

## 作者：zjr027 (赞：1)

思路：

读完这个题的翻译，我就立刻想到了暴力枚举。

但暴力枚举有一个必须要考虑的问题：

+ 是否超时，这就要看看题目的数据范围。

数据范围：超过了 $ 10^8 $。

如果暴力解决，必然超时。

所以我们需要寻找一种更好的方法。

题目要求出 A 到 B 中既不是 C 的倍数，也不是 D 的倍数的数的个数。

既然出现了 C 和 D 的倍数，我就又想到韦恩图。

韦恩图就是有两个集合圈，这两个集合圈有重叠，也有未覆盖的地方。

对于这道题，第一个集合圈我把它定义为是 C 的倍数的数，

第二个集合圈我把它定义为是 D 的倍数的数。

而这题的答案也就是未覆盖的地方了。

那么现在又出现了一个问题：

+ 怎么求出 A 到 B 中 C 的倍数的个数呢？

我们可以想算出 1 到 A - 1 中 C 的倍数的个数，假设成 x。

再算出 1 到 B 中 C 的倍数的个数，假设成 y。

那么 A 到 B 中 C的倍数的个数，就是 y - x。

代码：

+ 暴力枚举代码：

```c++
#include <bits/stdc++.h>
using namespace std;

int main(){
	long long a, b, c, d, cnt = 0;
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	for(long long i = a;i <= b;i++){ // 遍历判断
		if(i % c != 0 && i % d != 0){
			cnt++;
		}
	} 
	printf("%lld\n", cnt);
	return 0;
}
```

+ 韦恩图代码：

```c++
#include <bits/stdc++.h>
using namespace std;

long long gcd(long long n, long long m){ // 求最大公因数
	if(m == 0){
		return n;
	}
	return gcd(m, n % m);
}
int main(){
	long long a, b, c, d, cntc, cntd, cntcd, cnt;
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	c /= gcd(c, d); // 约分
	d /= gcd(c, d);
	cntc = b / c - (a - 1)/ c; // 第一个圈
	cntd = b / d - (a - 1)/ d; // 第二个圈
	cntcd = b / (c * d) - (a - 1)/(c * d); // 重叠部分
	cnt = (b - a + 1) - cntc - cntd + cntcd; // 未覆盖部分
	printf("%lld\n", cnt);
	return 0;
}
```

```c++
#include <bits/stdc++.h>
using namespace std;

long long gcd(long long n, long long m){ // 求最大公因数
	if(m == 0){
		return n;
	}
	return gcd(m, n % m);
}
int main(){
	long long a, b, c, d, cntc, cntd, cntcd, cnt;
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	cntc = b / c - (a - 1)/ c; // 第一个圈
	cntd = b / d - (a - 1)/ d; // 第二个圈
	cntcd = b / (c * d / gcd(c, d)) - (a - 1)/(c * d / gcd(c, d)); // 重叠部分
	cnt = (b - a + 1) - cntc - cntd + cntcd; // 未覆盖部分
	printf("%lld\n", cnt);
	return 0;
}
```



---

## 作者：RBI_GL (赞：0)

## 题意

给定 $4$ 个整数 $a,b,c,d$。求 $a
$ 到 $b$ 之间有多少个数既不能被 $c$ 整除，也不能被 $d$ 整除。


## 思路

容斥原理。

容易得到，答案为 $b-a+1$ $-$ 能被 $c$ 整除的数的个数 $-$ 能被 $d$ 整除的数的个数 $+$ 能被 $c$ 和 $d$ 整除的数的个数。

部分用最小公倍数求即可。

## 代码

```cpp
#include <bits/stdc++.h> 
using namespace std;
#define int long long
int a, b, c, d;
int gcd(int x, int y) {
	if (!y) return x;
	else return gcd(y, x % y);
}
int lcm(int p, int q) {
	return p * q / gcd(p, q);
}
int ans = 0;
signed main() {
	cin >> a >> b >> c >> d;
	ans = (b - a + 1) - (b / c - (a - 1) / c) - (b / d - (a - 1) / d) + (b / lcm(c, d) - (a - 1) / lcm(c, d));
	cout << ans << endl; 
	return 0;
}
```

---

## 作者：洛璟 (赞：0)

我的代码……貌似很复杂的样子？

这道题我们很快就能想到要把 $c$、$d$ 的倍数直接全部通过除法算出来，但是根据我在模拟赛多次被罚时的结果……还是用比较稳妥的方法 ~~（虽然本质貌似还是没变~~

那么我的思路也很简单，就是把 $c$、$d$ 和 $e$（即 $c$ 和 $d$ 的最小共公倍数） 在这个区间内的倍数全部算出来，当然由于我的神奇脑回路，因此我先把这个数列的起点和终点全部调成了当前要求的数的倍数。

至于 $e$ 的计算方法…… ~~貌似只有我这种小学数学没学过的人不会了~~就是两数相乘再除两数的最大公约数，那么在c++的库里边也有__gcd这种好东西（考场慎用，建议手写），这样一切都有了，暴力算就完事了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b, c, d;
int tmp, tmm, ans;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main()
{
    a = read();
    b = read();
    c = read();
    d = read();
    int qaq = __gcd(c, d);
    int e = (c * d) / qaq;
    if (a % c != 0)
        qaq = a + (c - (a % c));
    else qaq = a;
    int qwq = b - (b % c);//把数列开头调为c的倍数
    tmp = (qwq - qaq) / c + 1;//结尾调成c的倍数
    if (a % d != 0)
        qaq = a + (d - (a % d));
    else qaq = a;
    qwq = b - (b % d);
    tmp += (qwq - qaq) / d + 1;
    if (a % e != 0)
        qaq = a + (e - (a % e));
    else qaq = a;
    qwq = b - (b % e);
    tmm = (qwq - qaq) / e + 1;
    printf("%lld", (b - a + 1) - tmp + tmm);//减去两个数的
    //倍数后加上他们最小公倍数的倍数
    return 0;
}
```

~~（思路不错，代码太长）大雾~~

---

## 作者：leoair (赞：0)

# Anti-Division

题目大意:给出四个整数$a$、$b$、$c$和$d$，求$a$到$b$中有多少个数既不能被$c$整除，也不能被$d$整除(**含$a$和$b$**)。

这题可以当成容斥来做:

![](https://cdn.luogu.com.cn/upload/image_hosting/7aj488up.png?x-oss-process=image/resize,m_lfit,h_170,w_225)​

因此，只要算出$[a,b]$的数的个数$-$能被$c$ 整除的数的个数$-$能被$d$整除的数的个数$+$既能被$c$整除又能被$d$整除的数的个数即可。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll a, b, c, d;

inline ll read(){
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline ll gcd(ll n, ll m){																						//求最大公约数
	return m ? gcd(m, n % m) : n;
}

inline void work(){
	a = read(), b = read(), c = read(), d = read();
	ll lcm = c * d / gcd(c, d);																					//求最小公倍数
	printf("%lld\n", (b - a + 1) - (b / c - (a - 1) / c) - (b / d - (a - 1) / d) + (b / lcm - (a - 1) / lcm));	//求值(注意:(a-1)是的作用与求差分的(l-1)作用相同)
}

int main(){
	work();
	return 0;
}
```



---

