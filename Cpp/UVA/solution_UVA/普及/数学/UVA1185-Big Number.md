# Big Number

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3626

[PDF](https://uva.onlinejudge.org/external/11/p1185.pdf)

# 题解

## 作者：Hydrogen_Helium (赞：8)

第一次写一篇黑题的题解！！~~内心充满激动！~~

首先简述一下蒟蒻做这道题的过程：

这道题要求我们求$n!$的位数，所以蒟蒻首先打一个小小的表：

$1, 1, 1,2, 3, 3, 4 ,5, 6, 7, 8……$

貌似没有什么规律可找$……$

于是蒟蒻~~无耻地~~上了$OEIS$找了一下，发现了这么几个递推式：

$1·\quad a(n) = floor(log(n!)/log(10)) + 1$

这个式子要用到$n!$，所以显然不可用，看下一个。

$2·\quad a(n) = A027869(n) + A079680(n) + A079714(n) + A079684(n) + A079688(n) + A079690(n) + $
$\quad \quad \quad \quad \quad A079691(n) + A079692(n) + A079693(n) + A079694(n);$

解释一下，后面九个数列分别为$n!$中数字$1\sim9$出现的个数，显然这个公式也不太可用，看下一个。

$3·\quad a(n) = A055642(A000142(n)).$

这个式子中，外层为求$n$的位数，内层就是阶乘，所以显然也不可用。

$4·\quad a(n) = ceiling(log10(1) + log10(2) + ... + log10(n))$

等等！！这个式子貌似是$O(n)$的！！

于是，我们就愉快地$A$掉了此题。

---

但学习需要严谨的态度,所以我们来证明一下这个$O(n)$的式子：

首先，感谢[这篇博客](https://www.cnblogs.com/weiliuyby/p/5831991.html)提供证明思路。

$P.s.:$以下推导过程均默认$log$的底数为$10$。

对于一个正整数$n$，对于它有$10^{x-1}\leq n<10^x$，那么显然$n$有$x$位。继续向下推导：

$$log(10^{x-1})\leq log(n)<log(10^x)$$

$$x-1\leq log(n)<x$$

由于$c++$默认向下取整，所以$log(n)=x-1$，所以$n$的位数$=log(n)+1$.

所以，我们得出答案式子为$:$

$$ans=log(n!)+1$$

$$\quad\quad\quad\quad\quad\quad\quad\quad\quad\ =log(1 * 2 * 3 * …… * n) + 1$$

$$\quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad=log(1)+log(2)+……+log(n)+1$$

$$\quad\quad\quad= \sum_{i =1}^nlog(i)+1$$

证毕。

所以，我们预处理出$log$的前缀和，向上取整即可。

**code:**
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long

int n, temp;
double lg[10000001];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= 10000001; i++)
        lg[i] = lg[i - 1] + log10(i);
    while (n--) {
        scanf("%lld", &temp);
        printf("%lld\n", (long long)lg[temp] + 1);
    }
    return 0;
}

```
完结撒花(✪ω✪)






---

## 作者：Kuriyama_Mirai (赞：7)

第二次给黑题写题解……

## 读题

首先，看到题目，你会发现这题貌似很水……一直看到输入：

``
N（小于10的7次方的正整数）
``

鼓掌！这样子貌似用``long double``也会咕咕咕……

以下是你可能的想法：

- 高精度
- 暴力骗分
- $Hack$
- 离开
- ~~参考题解……~~

但是我们这里使用一个好东西——斯特林公式。

## 斯特林公式是啥？

斯特林公式（Stirling's approximation）是一条用来取n的阶乘的近似值的数学公式。一般来说，当n很大的时候，n阶乘的计算量十分大，所以斯特林公式十分好用，而且，即使在n很小的时候，斯特林公式的取值已经十分准确。

——摘自百度百科

这个公式是这样子的：

$$n! \approx \sqrt{2 \pi n} \left( \dfrac n e \right)^n$$

证明请见[百度百科](https://baike.baidu.com/item/%E6%96%AF%E7%89%B9%E6%9E%97%E5%85%AC%E5%BC%8F/9583086?fr=aladdin#3)……

## 推导！

要求$n!$的位数，就是求$\left\lfloor \lg(n!)+1 \right\rfloor$。（本文用$\lg$表示$log_{10}$）

然后就愉快地推导起来……

$$\because \lg(n!)+1 \approx \lg \left( \sqrt{2 \pi n}  \left( \dfrac n e \right)^n\right)$$

$$\lg \left( \sqrt{2 \pi n}  \left( \dfrac n e \right) ^n \right) = \lg \left( \sqrt{2 \pi n} \right) + \lg \left( \left( \dfrac n e \right) ^n \right)$$

$$\lg \left( \sqrt{2 \pi n} \right) + \lg \left( \left( \dfrac n e \right) ^n \right) = \lg \left( \sqrt{2 \pi n} \right) + n\lg \left( \dfrac n e\right)$$

$$\therefore \lg(n!)+1 \approx \lg \left( \sqrt{2 \pi n} \right) + n\lg \left( \dfrac n e\right)$$

（事实上当$n=1$时它们就很接近了，所以我们可以直接取）

$$\left\lfloor \lg(n!)+1 \right\rfloor \approx    \left\lfloor \lg \left( \sqrt{2 \pi n} \right) + n\lg \left( \dfrac n e\right) \right\rfloor$$

## 代码：

可能要注意一下，$lg$在$C++$里是一个cmath或math.h里的函数log10。

**注意！代码来了**

```cpp
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

#define PI 3.141592653589 //两个常数
#define E  2.7182818284 

queue<int> que; //休闲娱乐用

int main() {
    int n, in;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i ++) {
    	scanf("%d", &in);
    	que.push((int)(log10(sqrt(2 * PI * in)) + in * log10(in / E)) + 1);
	}
	
	while (not que.empty()) { //纯属无聊
		printf("%d\n", que.front());
		que.pop();
	}
	return (0-0);//卖萌(✺ω✺)
}
```

## 番外：优化？

当你看到这里时，你有没有想过，可能还有优化？

其实上面的还可以再优化（一点点优化），优化成：

$$\because \lg \left( \sqrt{2 \pi n} \right) + n \lg \left( \dfrac n e \right) = \lg \left( \sqrt{2 \pi} \right) + \lg \left( \sqrt n \right) + n\lg n - n \lg e$$

$$\lg \left( \sqrt{2 \pi} \right) + \lg \left( \sqrt n \right) + n\lg n - n \lg e = \lg \left( \sqrt{2 \pi} \right) - n \lg e + \dfrac 1 2 \lg n + n \lg n$$

$$\lg \left( \sqrt{2 \pi} \right) + n \lg e + \dfrac 1 2 \lg n + n \lg n = \lg \left( \sqrt{2 \pi} \right) - n\lg e + \dfrac{2n+1}{2} \lg n$$

$$\therefore \lg \left( \sqrt{2 \pi n} \right) + n \lg \left( \dfrac n e \right) = \lg \left( \sqrt{2 \pi} \right) - n\lg e + \dfrac{2n+1}{2} \lg n$$

$$\therefore \left\lfloor \lg(n!)+1 \right\rfloor \approx \left\lfloor \lg \left( \sqrt{2 \pi} \right) - n\lg e + \dfrac{2n+1}{2} \lg n\right\rfloor$$

代码就是做小小改动，把$\lg\left(\sqrt{2\pi}\right)$ 和 $-n\lg e$ 先算好，存起来，再代入上式解答。（能优化一点点时间吧）（注意不要傻傻地将$\lg n$算两遍！）

---

## 作者：Adove (赞：7)

这题其实就是要求lg函数值的前缀和啊

对于一个数x，若$\lg x=y$，则其位数为$\lfloor y+1 \rfloor$

然后对于对数，我们有$\lg \prod_{i=1}^x i= \sum_{i=1}^x \lg i$

预处理前缀和之后在线$\Theta(1)$回答询问即可

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
#include"cmath"
using namespace std;

const int MAXN=1e7+5;
const double eps=1e-8;

double lg[MAXN];
int tp[MAXN];
int T;

int main()
{
	for(int i=1;i<=1e7;++i) lg[i]=lg[i-1]+log10(i);
	for(int i=1;i<=1e7;++i) tp[i]=lg[i]+1;
	scanf("%d",&T);
	while(T--){
		int x;scanf("%d",&x);
		printf("%d\n",tp[x]);
	}return 0;
}
```

---

## 作者：torque (赞：6)

## 题意

给定T个数，对于每一个n($n<=1e7$)，求n!的位数

## 思路

我的MA呀，这是道黑题？

其实如果你明白了思路，这道题就会很简单

### Step1
首先对于一个任意的数字x，它有几位呢？

朴素算法：

```cpp
int get(int x){
	if(x<10) return 1;
        else reutrn get(x/10)+1;
}
```

求一次x位数的复杂度为$O(log x)$，总共要求T次

那么最暴力的算法就出来了

时间复杂度$O(T*log(n!))$
### Step2

我们甚至可以对上面的算法进行优化：

首先将$[1,1e7]$内所有数的位数跑出来

对于每次询问就可以$O(1)$解决

时间复杂度$O(log(1e7!))$

好像这样时间复杂度上已经允许了？但是你要明白的是在不取模的情况下，1e7!它。。。

位数也就几千万位。。。

所以当你在计算1e7!时就已经去世了，虽然可以通过优化来解决问题，但是鉴于代码冗长~~我这样的蒟蒻才不要打高精度嘞~~，就暂不考虑

### Step3

上面的教训告诉我们，如果你的运算中出现了$n!$，代码将会非常难打，甚至可能打不出来，那么怎么样才能避开$n!$呢？

$n!$本质是$\prod\limits_{i=1}^ni$，我们要避免的实际上是乘法，而能把乘法转变为较为简便的计算方式就只有。。。

$\color{red}{\huge{\boxed{log}}}$

再仔细想一想，x所占有的位数不就是$\left\lfloor lg(x)\right\rfloor+1$吗？

那么$n!$所占有的位数就是$\left\lfloor lg(n!)\right\rfloor+1$

而$lg(n!)=lg(1*2*\cdots*n)=lg(1)+lg(2)+\cdots+lg(n)$

即$n!$的位数为$\left\lfloor\sum\limits_{i=1}^nlg(i)\right\rfloor+1$

最后结合**Step2**对于**Step1**的优化，我们可以在线性时间内得到$[1,1e7]$内所有数的阶乘的位数，最后询问的复杂度是$O(1)$

综合时间复杂度$O(1e7+T)$

代码也很短，很好写

## 代码
凑合着看吧
```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#define N 10000001
#define rnt register int
using namespace std;
int n,T;
double lg[N];
int main(){
	for(rnt i=1;i<=1e7;i=-~i) lg[i]=lg[i-1]+log10(i);
	scanf("%d",&T);
	Work:if(T){
		scanf("%d",&n);
		printf("%d\n",(int)lg[n]+1);
		--T;goto Work;
	}
	return 0;
}
```

[![](https://ss3.bdstatic.com/70cFv8Sh_Q1YnxGkpoWK1HF6hhy/it/u=2921431843,3149119026&fm=26&gp=0.jpg)](https://www.luogu.org/blog/oneJURUO/)

---

## 作者：VenusM1nT (赞：4)

数学方法。因为和位数有关，我们很容易想到一个函数：$log10$。因为非常显然，一个数 $x$，如果 $\lfloor log10(x)\rfloor = y$，那么 $x$ 的位数就是 $y+1$。

比如 $2333333$，因为 $log10(1000000)=6$，可得 $\lfloor log10(2333333)\rfloor=6$，所以 $2333333$ 的位数就是 $7$。

同时，对数可以化乘为加，可以得到

$$log10(\prod_{i=1}^{n}i)=\sum_{i=1}^{n}log10(i)$$

所以预处理一个 $log10$ 的前缀和，就可以 $\text{O}(1)$ 查询了。

```cpp
#include<bits/stdc++.h>
#define MAXN 10000005
using namespace std;
int n,ans[MAXN];
double _[MAXN];
int main()
{
	int Time;
	scanf("%d",&Time);
	for(int i=1;i<=MAXN-5;i++) _[i]=_[i-1]+log10(i);
	for(int i=1;i<=MAXN-5;i++) ans[i]=int(_[i])+1;
	while(Time--)
	{
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
```

---

## 作者：叫我DJ (赞：3)

这题也是一道水水的递推，求n！的位数，其实就是log10(n!)+1，（注意向下取整），推导什么的，下面就是：

log10(n!)

=log10(1∗2∗3…∗n)

=log10(1)+log10(2)+…+log10(n)

看起来不难，实际也不难

所以……

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

double a[10000001];
int n,c,i;

int main()
{
    cin>>n;
    for(i=1;i<=10000000;++i)
	a[i]=a[i-1]+log10(i);
    while(n--){
        cin>>c;
        cout<<(int)a[c]+1<<endl;
    }return 0;
}
```

---

## 作者：Ignotus (赞：2)

### ~~**不可思议，这竟然是我第一道黑题……**~~
C++中的cmath库有对数函数，再加上题目的数据范围真的不大，1e7的数据完全可以用循环直接完成。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>//包含double log10(double x) 函数
using namespace std;
int main()
{
	freopen("test.in","r",stdin);
   	freopen("test.out","w",stdout);//防抄
	int n,a;
	double len=1;//长度
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		len=1;
		for(double j=2;j<=a;j++) len+=log10(j);//不能取整！
		printf("%d\n",(int)len);//最后再输出整数部分，即位数
	}
	return 0;//华丽收场
}
```
虽然时间复杂度较高，但实为亲测AC代码（140ms），也是新手最容易理解的方法qwq\
望大佬们多多指教！

---

## 作者：QwQ蒟蒻wjr (赞：2)



## [原网页](https://uva.onlinejudge.org/external/11/p1185.pdf)

## [洛谷翻译网页](https://www.luogu.org/problem/UVA1185)

这是本蒟蒻发的第二篇黑题的题解，很开心。

根据log的定理,$log_n{(x\times y)}=log_n{x}+log_n{y}$，且任意一个数x的位数是$log_{10}(x)+1$，所以可以推出
$$log_{10}(n!)+1=log(\prod_{i=1}^{n}i)+1=\sum_{i=1}^{n} log_{10}i+1 $$
```cpp
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=getchar();
		while(!isdigit(ch)&&ch^'-')
			ch=getchar();
		if(ch=='-')
		{
			b=true;
			ch=getchar();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=getchar();
		}
		if(b)
			x=~x+1;
		return;
	}
	char Out[1000*7+10],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using IO::read;
using IO::write;
const int N=1e7+10;
int T,x,maxx,tmp[N];
double lg[N];
int main()
{
	read(T);
	for(re int i=1; i<=1e7; i++)
		lg[i]=lg[i-1]+log10(i);
	for(re int i=1; i<=1e7; i++)
		tmp[i]=lg[i]+1;
	while(T--)
	{
		read(x);
		printf("%d\n",tmp[x]);
	}
	return 0;
}
```



---

## 作者：Celtic (赞：1)

注：本题解中的$\log$均代表$\operatorname{log10}$。

首先我们考虑一个数的位数。

一个$n$位数$x$显然有$10^{n-1}\leq x < 10^{n}$

所以$n-1 \leq \log x<n$

所以$x$的位数$n=\log x+1$，其中$\log x$向下取整。

$x!$的位数$n=\log{n!}+1$

$\qquad\qquad \ \ \,=\log{1\times 2\times3\times \cdots\times n}+1$

$\qquad\qquad \ \ \,=\log 1+\log 2+\cdots+\log n+1$

所以预处理出$\log$的前缀和，$O(1)$求解。

代码

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define eps 1e-20
#define re register
#define N 500001
#define MAX 2001
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	ret=pd?-ret:ret;
}
db lg[10000001];
ll t,n; 
int main()
{
	for(re int i=1;i<=10000000;i++)
		lg[i]=lg[i-1]+log10(i);
	read(t);
	while(t--)
	{
		read(n);
		printf("%lld\n",ll(ll(floor(lg[n]))+1));
	}
    exit(0);
}
```


---

## 作者：mod998244353 (赞：1)

~~这题其实很水~~

**题意：**

- 首先输入一个数 $n$。
- 再输入 $n$ 个数，分别输出他们的阶乘的位数。
- $n≤1e7$。

我们**只**需要这四个公式：

1. $y$ 的位数求法：$log_{10}(y)+1$。
2. $log_{10}(n!)=log_{10}(\sqrt{2 \times \pi \times n})+n \times log_{10}(\frac{n}{e})$。
3. $\pi=acos(-1.0)$。
4. $e =exp(1.0)$。

知道了这些，本题是不是很简单呢？~~我的代码很丑~~，代码自己打吧！

---

## 作者：shenxinge (赞：1)

## 求n！的位数

（部分转自[ACM:n!的位数 :斯特林公式](https://www.kancloud.cn/weber_lzw/book/209019)）

针对每个非负整数n，计算其n!的位数,由于n的位数很大，我们不可能通过直接计算得到结果

设a=log10（n！） ，则n！=10^a,其中a是一个小数

设a=x+y，其中 x为整数，y为小数

因此 n！=10^x+10^y

10^x肯定为10的倍数,决定了n!的位数，10^y为（1～10，不取10），决定n！的各位数字

因此，只要知道了a就可以求出n!的位数

因为a= log10（n！）=log10(n)+ log10(n-1)+……log10(2)+log10(1)，所以a的值可以很容易求出


**（lg(n)=log10(n）)**

****所以求log10(n!),也就是lg(1)+lg(2)+lg(3)+……+lg(n)****

但是当N很大的时候，我们可以通过数学公式进行优化（即斯特灵公式）：

N！=sqrt（2 * pi*N）*（N/e）^N；（pi=3.1415926=acos（-1.0），e=2.718）


### lgN！=(lg(2 * pi)+lgN)/2+N*(lgN-lge);


**斯特林公式可以用来估算某数的大小结合lg可以估算某数的位数，或者可以估算某数的阶乘是另一个数的倍数**

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double pi= M_PI;
const double e=M_E;
double counta(int n){
	if(n==0) return 0;
	double a=0;
	a= (log10(2*pi)+log10(n))/2+n*(log10(n)-log10(e));
	return a;
} 
int main() {
	int n,x,y,p;
	double a;
	cin>>p;
	while(p--){
		cin >> n;
		a=counta(n);
		x=(int)a;
		y=a-x;
		cout<<x+1<<endl;
	}
	return 0;
}
```
### 

------------
**完美结束**

（求过
）


---

## 作者：Presentation_Emitter (赞：0)

Update:2020.02.16 公式更正

此处提供2种做法

方法一：自然数$n$的位数为$\operatorname{floor}(\lg n)+1$，同时$\lg ab=\lg a+\lg b$，所以我们先$O(n)$预处理$\sum^{10^7}_{i=1}\lg i$，然后即可$O(1)$查询

方法二：~~在翻了一下OEIS后~~，我找到了一个斯特林公式。公式如下：

$$\lim\limits_{n\to+\infty}\frac{n!}{\sqrt{2\pi n}\dbinom{n}{e}^n}=1$$

略微改一下，即：

$$n!\approx \sqrt{2\pi n}\dbinom{n}{e}^n$$

根据对数换底公式$\log_a b=\log_{n^x} n^y=\frac{\log_n b}{\log_n a}$，我们得到了以下的式子：

$$\operatorname{floor}(\lg n!)+1\approx \operatorname{floor}(\frac{\log_{10}(2\pi n)}{2} + n(\log_{10}(\frac{n}{e})))+1$$

实测这个式子在$1\le n\le 5\times 10^7$时有用。下面是AC代码：

```python
import math
n=int(input())
for i in range(n):
    c=int(input())
    print(int(math.log(2*math.pi*c,10)/2+c*(math.log(c/math.e,10)))+1)
```

~~PS:使用Python的原因：懒~~

---

