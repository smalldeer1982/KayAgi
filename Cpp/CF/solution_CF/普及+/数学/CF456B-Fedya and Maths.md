# Fedya and Maths

## 题目描述

Fedya studies in a gymnasium. Fedya's maths hometask is to calculate the following expression:

 $ (1^{n}+2^{n}+3^{n}+4^{n}) mod 5 $ for given value of $ n $ . Fedya managed to complete the task. Can you? Note that given number $ n $ can be extremely large (e.g. it can exceed any integer type of your programming language).

## 说明/提示

Operation $ x mod y $ means taking remainder after division $ x $ by $ y $ .

Note to the first sample:

![](/predownloaded/21/5f/215f2e9eaa4d75e858b8e55199e51b0173dce047.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
124356983594583453458888889
```

### 输出

```
0
```

# 题解

## 作者：_Diu_ (赞：6)

## 翻译有误

先说一下这一题的翻译有一个地方有问题

要求的式子是$1^n+2^n+3^n+4^n\;mod\;5$

这里对$n=0$的情况有影响

好了，接下来是题解

## 循环

我们可知，这几个数的$n$次方$mod\;5$的数是有循环

我们来列一个表格

$\begin{vmatrix}n=&1&2&3&4&5&6\\1&1&1&…\\2&2&4&3&1&2&…\\3&3&4&2&1&3&…\\4&4&1&4&…\\sum&0&0&0&4&0&…\end{vmatrix}$

因此，我们可以每$4$个一个循环

结论：**如果$n\;mod\;4=0$，答案就是$4$，否则就是$0$**。

## 4的倍树的判定

我们就可以通过判定$n$是否是$4$的倍数来获取答案。

如果你看到这里，就可以通过**高精度**来$A$掉这一题了

当然还有更简便的方法

$n=100k+r(0<=r<100)$

因为$4|100$

所以$4|100k$

所以$n≡r(\;mod\;4)$

因此我们直接判定$n$的末两位是否是$4$的倍数就好了

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin>>s;
	puts(((s[s.size()-2]-'0')*10+s[s.size()-1]-'0')%4?"0":"4");
}
```

### ~~不知道为什么不会$RE$~~

## $END$

---

## 作者：Computer1828 (赞：6)

### 题目描述：

给定 $n (0 \leq n \leq 10^{10^5})$，求 $(1^n+2^n+3^n+4^n)\%5$。

### 分析：

$n$ 很大，但最后的模数很小，考虑直接欧拉降幂：

对于 $n \geq \varphi (p)$ 有 $a^b \equiv a^{b \% \varphi (p) + \varphi (p)} \pmod{p}$。

对于 $n < \varphi (p)$ 有 $a^b \equiv a^{b \% \varphi (p)} \pmod{p}$。

由于 $\varphi (5) = 4$，所以当 $n$ 的位数大于 $1$ 的时候，一边读入 $n$ 一边对它取模，然后按欧拉降幂做，最后快速幂求答案；当 $n$ 位数只有 $1$ 时，直接跑快速幂即可，而且 $1^9 + 2^9 + 3^9 + 4^9 = 282340$，所以并不需要使用 `long long`。

代码：

```cpp
#include<bits/stdc++.h>
#define mod 5
using namespace std;
char str[100005];
inline int qpow(int a,int b){
	int res = 1,base = a;
	while(b){
		if(b&1) res = res*base%mod;
		base = base*base%mod;
		b >>= 1;
	}
	return res;
}
int mi;
int main(){
	scanf("%s",str);
	int len = strlen(str);
	if(len == 1){
		mi = str[0]-'0';
		printf("%d",(1+qpow(2,mi)+qpow(3,mi)+qpow(4,mi))%mod);
	}else{
		for(int i = 0;i<len;++i){
			mi = mi*10+(str[i]-'0');
			mi = mi%4;
		}
		mi = mi+4;
		printf("%d",(1+qpow(2,mi)+qpow(3,mi)+qpow(4,mi))%mod);
	}
	return 0;
}
```

---

## 作者：Aya_tt (赞：1)

找题是个找规律和判断是否是 $4$ 的倍数的题。





# 推导

$1$，$1^n$（$mod$ $5$） 一定是 $1$。

$2$，$2^n$（$mod$ $5$） 也是有一定规律的，只要你用心算一算会发现有一个序列（从 $n=1$ 开始）: $2$,$4$,$3$,$1$,$2$,$4$,$3$,$1$......

$3$，$3^n$（$mod$ $5$）序列为（从 $n=1$ 开始 ）: $3$,$4$,$2$,$1$,$3$,$4$,$2$,$1$......

$4$，$4^n$（$mod$ $5$）序列为（从 $n=1$ 开始 ）: $4$,$1$,$4$,$1$,$4$,$1$,$4$,$1$......

$5$,把这几个加在一起 （$1^n+2^n+3^n+4^n$）（$mod$ $5$）的规律就出来：
$0$,$0$,$0$,$4$,$0$,$0$,$0$,$4$......

从上面，我们可以看出，当 $n$ 是 $4$ 的倍数时，就输出 $4$，否则，输出 $0$。




# 代码实现


求题目中 $n$ 的取值范围可以看出 $n$ 远远爆出了数据类型的范围，那我们应该怎么判断它是否是 $4$ 的倍数呢？

小学奥数教给我们判断一个数是否是 $4$ 的倍数的快捷方法就看这个数的后两位，具体为什么，我简单说说：先减去后两位，使后两位都是 $0$，所以他一定是 $100$ 的倍数，$100$ 又是 $4$ 的倍数，所以到最后，只需要看后两位，也就是我们只需要把输入的数的后两位提取出来就可以了，因为 $n$ 的值很大，又考虑到读入的方便，所以使用字符串。
 
如下就是代码：

```c
#include<bits/stdc++.h>
using namespace std;
string a;//没看见题目中说的n。
int main(){
    cin>>a;
    int t1 = a[a.length() - 1] - '0';//最后一位
    int t2 = a[a.length() - 2] - '0';//倒数第二位
    int t = t1 + t2 * 10;//最后两位
    if(t % 4 == 0) cout<<4;//判断是否是4的倍数
    else cout<<0;
}
```


---

## 作者：梧桐灯 (赞：1)

题面有锅，[点进去](http://codeforces.com/problemset/problem/456/B)发现：

- 没有$5^n$ ($n=0$时有影响)

- n <= ${10}^{10^5}$

我做法比较暴力，高精度+快速幂（不需要推末尾的式子，适用范围广）

代码：
```cpp

#include <cstdio>
using namespace std;

inline void swap (int& p, int& q) {int t = p; p = q; q = t;}

int a[100007], n;

inline void Divide () {
	int i;
	for (i = n; i; --i) {
		if (a[i] & 1) a[i - 1] += 10;
		a[i] >>= 1;
	}
	a[0] = 0;
	while (n && !a[n]) --n;
	return ;
} //高精除2

int main () {
	char c;
	while (~(c = getchar ())) {
		if (c >= '0' && c <= '9') a[++n] = c & 15;
	}
	int i;
	for (i = 1; i <= (n >> 1); ++i) swap (a[i], a[n - i + 1]);
	int p1 = 1, p2 = 2, p3 = 3, p4 = 4;
	int s1 = 1, s2 = 1, s3 = 1, s4 = 1;
	while (n) {
		if (a[1] & 1) {
			s1 = s1 * p1 % 5;
			s2 = s2 * p2 % 5;
			s3 = s3 * p3 % 5;
			s4 = s4 * p4 % 5;
		}
		p1 = p1 * p1 % 5;
		p2 = p2 * p2 % 5;
		p3 = p3 * p3 % 5;
		p4 = p4 * p4 % 5;
		Divide ();
	} //快速幂
	printf ("%d\n", (s1 + s2 + s3 + s4) % 5);
    return 0;
}
```



---

## 作者：OLE_OIer (赞：0)

这道题是一道比较~~水~~有难度的数论题目。

### Part $1$: 数论推导
题目让我们求 $(1^n+2^n+3^n+4^n)\,\mathrm{mod}\,5$, 所以我们可以用一些学过的数论方法来推导。

$$
\begin{aligned}
1^n+2^n+3^n+4^n&≡1^n+2^n+(-2)^n+(-1)^n
\end{aligned}
$$
在 $n≡1\,(\,\mathrm{mod}\,2\,)$ 的时候就有：
$$
\begin{aligned}
1^n+2^n+3^n+4^n&≡1^n+2^n+(-2)^n+(-1)^n\\
&≡1^n+2^n-2^n-1^n\\
&≡0\,(\,\mathrm{mod}\,5\,)
\end{aligned}
$$
在 $n≡2\,(\,\mathrm{mod}\,4\,)$ 的时候，设 $n=4k+2$，于是就有：
$$
\begin{aligned}
1^n+2^n+3^n+4^n&≡1^n+2^n+(-2)^n+(-1)^n\\
&≡2(1^{4k+2}+2^{4k+2})\\
&≡2(1+16^k\times4)\\
&≡10≡0\,(\,\mathrm{mod}\,5\,)
\end{aligned}
$$
在 $n≡0\,(\,\mathrm{mod}\,4\,)$ 的时候，设 $n=4k$，于是就有：
$$
\begin{aligned}
1^n+2^n+3^n+4^n&≡1^n+2^n+(-2)^n+(-1)^n\\
&≡2(1^{4k}+2^{4k})\\
&≡2(1+16^k)\\
&≡4\,(\,\mathrm{mod}\,5\,)
\end{aligned}
$$
综上所述，有：
$$
1^n+2^n+3^n+4^n≡\begin{cases}
  4 & \frac{n}{4} \in \mathbb Z \\
  0 & \frac{n}{4} \notin \mathbb Z \\
\end{cases}
\,(\,\mathrm{mod}\,5\,)
$$
### Part 2: 程序实现

因为 $n\leq10^{10^5}$，所以肯定要打高精度了！！！但是打高精度太太太慢了，有没有更好的方法呢？

这时候我们就又可以用数论来优化啦！

设 $n=100a+b$

则会有：
$n≡100a+b≡0a+b≡b\,(\,\mathrm{mod}\,4\,)$

所以只需判断 $n$ 的末两位是否可被 $4$ 整除即可。

附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string c;
	cin>>c;
	int len=c.length();
	int x=c[len-2]*10+c[len-1];
	if(x%4==0) cout<<"4";
	else cout<<"0";
	return 0;
}
```

---

## 作者：Citnaris (赞：0)

# CF456B Fedya and Maths

**前置知识**

对于一个数 $x=(a_1a_2......a_{l-1}a_l)$ ， $x=100\times(a_1a_2......a_{l-2})+10\times a_{l-1}+a_l$ 。因为 $100$ 是 $4$ 的倍数，那么 $x\ mod\ 4$ 就是 $(10\times a_{l-1}+a_l)\ mod\ 4$， 即 $x$ 的最后两位 $mod\ 4$ 。

**题目描述**

求 $1^{n}+2^{n}+3^{n}+4^{n}\ mod\ 5\ (n\le 10^{10^{5}})$

**正解**

看到 $n$ 的数据范围，我们意识到这道题的解法更偏向思维。

根据讨论 $i^{k}\ mod\ 5\ (i\in [1,\ 5])$ 的余数情况，我们得到：

* $1^{k}\ :\ 1\ 1\ 1\ 1\ 1\ 1\ 1\ 1\ 1......$

* $2^{4}\ :\ 2\ 4\ 3\ 1\ 2\ 4\ 3\ 1\ 2......$

* $3^{k}\ :\ 3\ 4\ 2\ 1\ 3\ 4\ 2\ 1\ 3......$

* $4^{k}\ :\ 4\ 1\ 4\ 1\ 4\ 1\ 4\ 1\ 4......$

* $\sum_{i=1}^{4}\sum_{k=1}^{n}i^{k}\ mod\ 5\ :\ 0\ 0\ 0\ 4\ 0\ 0\ 0\ 4\ 0......$

显然，其 $mod\ 5$ 的余数四个出现一个周期，即当 $n$ 为 $4$ 的倍数时，答案为 $4$ ，否则为 $0$ ，此步判断可运用前置知识部分的结论来处理。

**代码**
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int NR = 1e5 + 1;
char a[NR];
int x, len;

int main()
{
    scanf("%s", &a); // 用字符串读入更方便
    len = strlen(a);
    x = a[len - 2] * 10 + a[len - 1]; // 最后两位
    x % 4 == 0 ? putchar('4') : putchar('0'); // 判答案
    return 0;
}
```

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

首先声明，题目翻译有误：

求和时没有 $5^n$ ，

但这一漏洞只在 $n=0$ 是有所体现

（想想为什么

### 废话不说，开始找规律

| $n^m \bmod 5$ | 0 | 1 | 2 | 3 | 4|5|6|7|8
| -----------: | -----------: | -----------: | -----------: | -----------: |-----------: |-----------: |-----------: |-----------: |-----------: |-----------: |
| 1 |1  | 1 | 1 | 1 |1  | 1 | 1 | 1 |1
| 2 | 1 | 2 | 4 | 3 |1 | 2 | 4 | 3 |1
|  3| 1 | 3 | 4 | 2 |1 | 3 | 4 | 2 |1
| 4 | 1 | 4 | 1 | 4 |1 | 4 | 1 | 4 |1
|  1+2+3+4|4|0|0|0|4|0|0|0|4

我们可以发现，无论是单独的项还是求和，

数字都会每 $4$ 位一循环，

观察可得，当 $m \bmod 4 = 0 $ 时，

答案为 $4$，否则为 $0$。

于是我们就将问题转化成了

判断一个高精度数是否为 $4$ 的倍数的问题。

判断也很简单：

并不需要进行高精度 $\div$ 的运算，

因为所有以 $2$ 个 $0$ 结尾的数，

都能被拆解为 $n \times 25 \times 4$ 的形式，

故我们只需判断 $n$ 的末尾 $2$ 位是否能被 $4$ 整除。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a; cin>>a;
    if(a.size()==1) cout<<((a[0]-'0')%4==0?4:0);//特判
    else cout<<(((a[a.size()-2]-'0')*10+a[a.size()-1]-'0')%4==0?4:0);
    /*三目运算符
    写成：（判断语句?a:b），
    意为：若条件为真，返回 a，否则返回 b
    */
    return 0;
}

```

---

## 作者：AFOed (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF456B)

题意（翻译有问题）：求 $1^n+2^n+3^n+4^n~mod~5$

~~有关欧拉降幂的知识最顶上那位奆佬已经讲了，我也就不讲了~~

还是讲一下吧

$5$是一个质数

依据[费马小定理](https://baike.baidu.com/item/%E8%B4%B9%E9%A9%AC%E5%B0%8F%E5%AE%9A%E7%90%86/4776158?fr=aladdin#2)可得 ， 当$n$是一个质数时 $ a^{n-1}≡1~( mod~n) $

所以 $ a^{4}≡1~( mod~5) $

两边同时乘 $a$，所以 $ a^{5}≡a~( mod~5) $

所以 $ a^{n}≡a^{n-4}( mod~5) $

$mod$ 其实就是不停地减 ， 所以 $ a^{n}≡a^{n ~mod~4}~( mod~5) $

据此知道：对于 $a^n~( mod~5)$  一定存在一个长度为 $n-1$ 的循环节 $（①）$
- 考虑把 $(a+b+c+d+e)~mod~f$ 转化成 $a~mod ~f~+~b~mod ~f~+~c~mod ~f~+~d~mod ~f~+~e~mod ~f~$
- 对于 $1^n~( mod~5)$  都等于$1$
- 对于 $2^n~( mod~5)$ 依据$①$知道循环节长度为$4$，找到循环节为 $1~2~4~3$：
	```cpp
	A = 2 ^ n mod 5 
	n = 0 : A = 1
	n = 1 : A = 2 
	n = 2 : A = 4 
	n = 3 : A = 3 
	n = 4 : A = 1 
	n = 5 : A = 2 
	n = 6 : A = 4 
	n = 7 : A = 3 
	n = 8 : A = 1
	......
	```
- 对于 $3^n~( mod~5)$ 找到循环节为 $1~3~4~2$：
	```cpp
	B = 3 ^ n mod 5 
	n = 0 : B = 1
	n = 1 : B = 3
	n = 2 : B = 4
	n = 3 : B = 2
	n = 4 : B = 1
	n = 5 : B = 3
	n = 6 : B = 4
	n = 7 : B = 2
	n = 8 : B = 1 
	........
	```
- 对于 $4^n~( mod~5)$ 找到循环节为 $1~4~1~4$：
	```cpp
	C = 4 ^ n mod 5
	n = 0 : C = 1
	n = 1 : C = 4
	n = 2 : C = 1
	n = 3 : C = 4
	n = 4 : C = 1
	n = 5 : C = 4
	n = 6 : C = 1
	n = 7 : C = 4
	n = 8 : C = 1
	........
	```

所以一开始我写出了下面的代码：

先把 $2,3,4$ 的循环节存进一个表里，然后输出时直接调用即可（不知道为什么输入用char会RE）

```cpp
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std ;
string ch ;
int ans , n , A [ 3 ] [ 4 ] =
{
	{ 1 , 2 , 4 , 3 } ,
	{ 1 , 3 , 4 , 2 } ,
	{ 1 , 4 , 1 , 4 } 
} ;
signed main ( )
{
	cin >> ch ;
    //char ch = getchar () , c ;
   	//for ( ; ( ch = getchar ( ) ) and ch >= '0' and ch <= '9' ; ) c = ch ;
	int L = ch . size ( ) - 1 ;
	n = ( ch [ L - 1 ] ^ 48 ) * 10 + ( ch [ L ] ^ 48 ) ;
	ans = 0 ;
	ans += 1 ;
	ans = ( ans + A [ 0 ] [ n % 4 ] + A [ 1 ] [ n % 4 ] + A [ 2 ] [ n % 4 ] ) % 5 ;
	printf ( "%d\n" , ans ) ;
}

```

然后呢，我在调试上面的代码的时候把 $n=0$ 到 $n=100$ 的情况都输出了一遍，打出了下面的表：

______
| $ ~n$ | $ ~ans$ |
| :----------: | :----------: |
|  0|  4|
|  1|  0|
|  2|  0|
|  3|  0|
|  4|  4|
|  5|  0|
|  6|  0|
|  7|  0|
|  8|  4|
|  ...|  ...|
______

似乎发现了另一个循环节： $ 4~0~0~0 $

接着我写出了下面的代码：

当$n$除以$4$余$0$时，输出$4$，否则输出$0$，然后就能A掉这题了

```cpp
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std ;
string ch ;
signed main ( )
{
	cin >> ch ;
	int L = ch . size ( ) - 1 ;
	int n = ( ch [ L - 1 ] ^ 48 ) * 10 + ( ch [ L ] ^ 48 ) ;
	printf ( "%d\n" , n % 4 ? 0 : 4 ) ;
}
```

总结：

一道 ~~打表题？~~ 数学题 ， 看来学oi还是要先学好数学。

---

## 作者：WinterRain208 (赞：0)

CF456B 【Fedya and Maths】

###### ~~题外话 这篇题解打算认真写了~~

### 题意分析

给定$n$。
求($1^n+2^n+3^n+4^n+5^n$)$mod5$.

我习惯性去看了一下英文题面，发现不含$5^n$，但其实是对答案没有影响到。后面会说原因。

考虑做法。

直接求，高精快速幂取模求解，时间复杂度过高，不用说这不是正解。

那么我们来找规律，因为数据太大了，所以直接暴露了这是一道规律题的事实。

#### 求$1^n$

想出这个应该不难，因为我们知道$1$的任何次方都是其本身。

我们看出，无论$n$取何值，$1^n$=$1^nmod5$=$1$

#### 求$2^n$

从这里开始我们就直接放表了，$2,3,4$，算他们的一到十次方都可以口算，规律也很好找。

周期为四个一周期，$3,2,4,1$。

我们得出：

$n%4=1$则$2^nmod5=2$

$n%4=2$则$2^nmod5=4$

$n%4=3$则$2^nmod5=3$

$n%4=4$则$2^nmod5=1$

接下来的大致一样，就不放像上面一样详细的分类了。

#### 求$3^n$

大概是$2,9,27,81,243,729$。

也是四个一周期，$3,4,2,1$。

#### 求$4^n$

设$k=n*2$，则$4^n$=$2^k$，因为$4=2^2$。

也就是一两个为一周期，$4,1$循环。



也不难算，相信大家都背诵过。

#### 求$5^n$

因为包含五，所以不管$n$取何值，这一项答案为$0$。

这就是为什么翻译有误却不影响。

###  继续分析

因为要求循环节，所以要计算$n%4$和$n%2$。

整除特征不用介绍，$4$取$n$的后两位$mod4$，$2$是后一位即可，位置原理普及一下。

#### $SOLUTION$

分别求，相加记得再$mod5$.

## $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

int ans=0;

void add2(string x){
	int k=(x[x.size()-2]-'0')*10+(x[x.size()-1]-'0');
	if(k%4==1)ans+=2;
	if(k%4==2)ans+=4;
	if(k%4==3)ans+=3;
	if(k%4==0)ans+=1;
}

void add3(string x){
	int k=(x[x.size()-2]-'0')*10+(x[x.size()-1]-'0');
	if(k%4==1)ans+=3;
	if(k%4==2)ans+=4;
	if(k%4==3)ans+=2;
	if(k%4==0)ans+=1;
}

void add4(string x){
	int k=x[x.size()-1]-'0';
	if(k%2)ans+=4;
	else ans+=1;
}
int main(){
	string s;
	cin>>s;
	s="000"+s;
	add2(s),add3(s),add4(s);
	cout<<(ans+1)%5;
    return 0;
}
//1 2 3 4 5 6 7 8 9 10
//2 4 3 1 2 4 3 1 2 4
//2 4 8 16 32 64 128 256 512 1024
//1 2 3 4 5 6
//3 4 2 1 3 4 2 1
//3 9 27 81 243 729
//1 2 3 4 5 6
// 4 1 4 1 4 1
// 4 16 64 256 1024 4096
```
完结撒花。

题解不易，请点个赞再走谢谢！

$wtrl$


---

## 作者：damage (赞：0)

# 题解

题意即给定一个可能很大的$n$，求$(1^{n}+2^{n}+3^{n}+4^{n}+5^{n})\ mod\ 5$。

我们对于不同的数字（$1,2,3,4,5$）进行单独处理：

-  $1^{n}$，这种情况很简单，因为我们小学时就知道了~~一个举世闻名的定理~~：

 - $1$的任意次方都等于$1$
 
 所以只要在最后加上$1$再$mod\ 5$就可以了

- $2^{n}$，通过找规律发现$2$的$n$次方膜$5$的规律：

 > ```2 4 3 1 , 2 4 3 1...```
 
 发现每四个一循环，到时候计算$n\ mod\ 4$即可
 
 其实对于不同的$n$，有：
 
 - $n=4k+1(k\in{N^{+}})$，则
 
  > $2^{4k+1}\equiv{2\times{(2^{4})^{k}}}\equiv{2\times{16^{k}}}\equiv{2\times{1^{k}}}\equiv{2}\ (mod\ 5)$
 
 - $n=4k+2(k\in{N^{+}})$，则
 
  > $2^{4k+2}\equiv{2^{2}\times{(2^{4})^{k}}}\equiv{4\times{16^{k}}}\equiv{4\times{1^{k}}}\equiv{4}\ (mod\ 5)$
 
 - $n=4k+3(k\in{N^{+}})$，则
 
  > $2^{4k+3}\equiv{2^{3}\times{(2^{4})^{k}}}\equiv{8\times{16^{k}}}\equiv{3\times{1^{k}}}\equiv{3}\ (mod\ 5)$
 
 - $n=4k(k\in{N^{+}})$，则
 
  > $2^{4k}\equiv{(2^{4})^{k}}\equiv{16^{k}}\equiv{1^{k}}\equiv{1}\ (mod\ 5)$

- $3^{n}$，通过找规律发现$3$的$n$次方膜$5$的规律：

 > ```3 4 2 1 , 3 4 2 1...```
 
 发现每四个一循环，到时候计算$n\ mod\ 4$即可
 
 其实$3^{n}\equiv{(-2)^{n}}\ (mod\ 5)$
 
 所以当：
 
 1. $n$为奇数时，$(2^{n}+3^{n})\ mod\ 5 =0$
 
 2. $n$为偶数时，$(2^{n}+3^{n})\ mod\ 5 =2^{n+1}\ mod\ 5$

- $4^{n}$，通过找规律发现$4$的$n$次方膜$5$的规律：

 > ```4 1 , 4 1 , 4 1...```
 
 发现每两个一循环，到时候计算$n\ mod\ 2$即可
 
 其实$4^{n}\equiv{(-1)^{n}}\ (mod\ 5)$
 
 所以当：
 
 1. $n$为奇数时，$(1^{n}+4^{n})\ mod\ 5 =0$
 
 2. $n$为偶数时，$(1^{n}+4^{n})\ mod\ 5 =2$
 


- $5^{n}$，简单说：

  > $5^{n}\equiv{0^{n}}\equiv{0}\ (mod\ 5)$

  所以$5^{n}\ mod\ 5$其实就等于$0$
  
注意到最大的循环周期也只有$4$，因为$n$可能会非常大，所以可以运用快读边读入边```%100```，因为:

> 假设$x=100k+a(k\in{N^{+}},a=[0,99])$，则：

 > $x\equiv{100k+a}\equiv{0k+a}\equiv{a}\ (mod\ 5)$
 
 所以其实对于任何一个正整数$n$，```n%4```的值等于$n$的后两位数字```%4```，所以只要在快读的时候边读入边```%100```
 
 最后将以上$5$个结果一一特判累加再```%5```即可（我太菜了）
 
---

# 代码

```cpp
#include<stdio.h>
#include<ctype.h>
int n,res;
void qread(int &x) //快读
{
	x=0;
	char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar()) x=(x*10+c-48)%100; //注意这里多了一个括号和%100
	return ;
}
void Add2() //特判第二种情况
{
	if((n&3)==1) res+=2; //这里用的是位运算，不会的大佬们请见后面
	else if((n&3)==2) res+=4;
	else if((n&3)==3) res+=3;
	else res+=1;
	return ;
}
void Add3() //特判第三种情况
{
	if((n&3)==1) res+=3; //这里用也的是位运算，不会的大佬们请见后面
	else if((n&3)==2) res+=4;
	else if((n&3)==3) res+=2;
	else res+=1;
	return ;
}
void Add4() //特判第四种情况
{
	if((n&1)) res+=4; //这里用也的是位运算，不会的大佬们请见后面
	else res+=1;
	return ;
}
int main()
{
	qread(n);
	Add2(); //第一种情况
	Add3(); //第二种情况
	Add4(); //第三种情况
	printf("%d\n",(res+1)%5); //记得加上第一种情况的1，第五种情况因为是0所以就可以不加了
	return 0;
}
```

---

## 说明

关于本篇涉及到的位运算的讲解

#### ```x&1```的返回值只有两种

1. 当$x$为奇数时，返回$1$

2. 否则返回$0$

此处就等于$x\%2$（或$x\%2==1$）

同理```x&3```也是

其实任何$x\%2^{i}$都可以转化为$x\&(2^{i}-1)$

---

