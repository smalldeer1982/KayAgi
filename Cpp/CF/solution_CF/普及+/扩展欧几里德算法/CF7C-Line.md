# Line

## 题目描述

给定一条直线 $Ax+By+C=0$，找到这条直线上任意一个点使得横纵坐标均为在 $-5\cdot 10^{18} \sim 5\cdot 10^{18}$ 之间的整数，或者确定没有这样的点。

## 样例 #1

### 输入

```
2 5 3
```

### 输出

```
6 -3
```

# 题解

## 作者：Crab_Dave (赞：71)

**upd：on 2019.11.13，增加了$L_A^TE_X$语句，看起来舒服多了qwq**

# 扩展欧几里得！！！

萌新刚学exgcd，来一波题解~

Q：这个算法叫什么名字？

A：扩展欧几里得，又称exgcd。

Q：讲一讲qwq？

A：我们先引入一条定理——

------------
**斐蜀定理：对任何$a,b∈Z$和它们的最大公约数$d$，关于未知数$x$和$y$的线性不定方程（称为裴蜀等式）：$ax+by=c$有整数解$(x,y)$当且仅当$d∣c$，可知有无穷多解。特别地，一定存在整数$x,y$，使$ax+by=d$成立。**

由裴蜀定理，我们可以得出一个小推论：

------------
**推论：$a,b$互质的充要条件是存在整数$x,y$使$ax+by=1$。**

这里作者推荐一篇[关于斐蜀定理的证明](http://blog.csdn.net/discreeter/article/details/69833579)

A：好，那么对于方程$ax+by=c$，设$d=gcd(a,b)$，根据斐蜀定理可知$ax+by=d$一定有正整数解，怎么求解$x,y$呢？

------------
**我们注意到：欧几里德算法停止的状态是：$a=d$，$b=0$，此时当$x=1,y=0$(实际任意值都可以)时$d*1+0*0=d$成立，这是最终状态，我们根据这个最终状态反推出初始状态的值即为答案，怎么反推？**

```
设x,y和x1,y1是两组解，且满足：

由  a*x+b*y=gcd(a,b)
	b*x1+(a%b)*y1=gcd(b,a%b)
得  a*x+b*y=b*x1+(a%b)*y1

设k=a/b,r=a%b,则r=a-k*b,代入上式得
	a*x+b*y=b*x1+(a-a/b*b)*y1
	a*x+b*y=a*y1+b*(x1-a/b*y1)
得  x=y1
	y=x1-a/b*y1
```

所以通过以下函数可以在求$a,b$的$gcd$的同时求出方程$ax+by=d$的一组特解
```cpp
int exgcd(int a,int b)
{
	if(b==0){x=1;y=0;return a;}
	int tmp=exgcd(b,a%b);
	int t=x;
	x=y;y=t-a/b*y;
	return tmp;
}
```
现在已经求出了一组特解$x_0,y_0$，$ax+by=d$的通解又是什么？

**直接给出：$x=x_0+b/d*k$，$y=y_0-a/d*k$，$k$为任意整数**

为什么是这个？因为它带入$ax+by=d$等式成立。

那你会问，带入等式成立的多了，比如$x=x_0+b*k$，$y=y_0-a*k$，为什么非要选它？

因为它能无遗漏的表示所有整数解。

------------
证明如下：

因为$b/d$是$b$的因子，所以$x_0+b/d*k$能取到的值比$x_0+b*k$多，同理$y_0-a/d * k$也是

设$B=b/d$,$A=a/d$，所以$A,B$互质，所以$A,B$为最小系数。

证毕。

好的，以上就是$exgcd$的基本定义及证明。

那么，我们可以用它干什么呢——

```cpp
1、求解不定方程ax+by=c
2、求解线性同余方程
3、求解模的逆元

题目不会让你求出所有解，一般会限定条件，
比如某个区间内的解，最小正整数解等等
```
## 解不定方程$ax+by=c$

由斐蜀定理知当$d|c$时才有整数解

将方程两边同时除以$gcd(a,b)$，设$a'=a/gcd(a,b)$，

$b'=b/gcd(a,b),c'=c/gcd(a,b)$，则方程变形为$a'x+b'y=c'$，因为$a',b'$互质，所以$gcd(a',b')=1$。

由扩展欧几里得定理知一定存在$x_0,y_0$使得$a'x_0+b'y_0=1$。

则可由$exgcd$求出$x_0,y_0$，将上式两边同时乘以$gcd(a,b)$得

$a'gcd(a,b)x_0+b'gcd(a,b)y_0=gcd(a,b)$

==> $ax_0+by_0=gcd(a,b)$

==> $ax_0+by_0=c/c'$，

所以

$x_1=x_0*c'=c/d*x_0$，$y_1=y_0*c=c/d*y_0$

为方程的另一组解

**则方程$ax+by=c$的通解为**

**$x=x_1+b/d*k=c/d*x_0+b/d*k$，$y=y_1-a/d*k=c/d*y_0-a/d*k$**

## 解线性同余方程
对于线性同余方程：$ax≡m(mod\ b)$

$ax$%$b=m$

-> $ax=by+m$

-> $ax-by=m$

-> $ax+by=m$

## 乘法逆元
存在$x$使得$ax≡1(mod\ p)$，则称$x$的最小正整数解是$a$关于$p$的乘法逆元

定理：$a$关于$p$的乘法逆元存在的充要条件是$gcd(a,p)=1$

逆元有什么作用呢？

```cpp

当要求(a/b)%p时，且a很大，我们就求b关于p的乘法逆元x，则有(a/b)%p = (a*x)%p

根据b*x≡1 (mod p)有b*x=p*y+1。

则x=(p*y+1)/b。

把x代入(a*x) mod p，得：
(a*(p*y+1)/b) mod p
=((a*p*y)/b+a/b) mod p
=[((a*p*y)/b) mod p +(a/b)] mod p
=[(p*(a*y)/b) mod p +(a/b)] mod p

//p*[(a*y)/b] mod p=0 
```
代码如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sut37udw.png)

好的，关于exgcd的用途也讲完了，那么我们回到
# [这道题](https://www.luogu.org/problem/CF7C)——

很明显，这道题是让我们求$Ax+By=-C$的一组解，并且$x,y∈[-5e18,5e18]$。

所以说这是$exgcd$的一道裸题~

直接上代码吧——

```
#include<cstdio>
using namespace std;

long long a,b,c,x,y,d;//这道题要开long long！！！

int exgcd(int a,int b)//扩展欧几里得
{
	if(b==0){x=1;y=0;return a;}//临界条件
	int tmp=exgcd(b,a%b);//逆推回去求解
	int t=x;
	x=y;y=t-a/b*y;
	return tmp;
}

int main()
{
	scanf("%lld%lld%lld",&a,&b,&c);
	c=-c;
	int d=exgcd(a,b);
	if(c%d!=0){printf("-1\n");return 0;}//如果无解
	x=c/d*x;
	y=c/d*y;//这里是求出k=0时的通解
	printf("%lld %lld\n",x,y);
	return 0;//功德圆满
}
//CSP2019rp++
```
谢谢各位的观看~如果不介意的话顶一个再走吧qwq~

---

## 作者：Dog_Two (赞：6)

求解线性方程嘛，很容易想到扩展欧几里得方法——

# 扩展欧几里得算法


## 定义

扩展欧几里得算法可以解决这样的问题：

- 求解一组p，q，令它们满足：p*a+q*b=gcd（a,b）

## 证明：
可以证明，一定存在这样的至少一组解：
```
有gcd(a,b)==gcd(b,a%b)，所以我们可以做如下处理：

p*a+q*b =gcd(a,b)
		=gcd(b,a%b)
		=p*b+q*(a%b)    
		=p*b+q*[a-(a/b)*b]    
		=q*a+[p-(a/b)*q]*b
```
- 上式中所有的“/”号都代表“整除”。

我们可以一直对上式作这样的推导，这也正是欧几里得算法的迭代过程。

于是，求解a,b的线性关系就可以转化为求解b,a%b的线性关系。

联想辗转相除法，显然，当b=0时，p=1,q=0，接着我们就可以递归返回求解。

## 代码
```
int ext_gcd(int a,int b,int &x,int &y){
	int res,tmp;
	if(!b){
		x=1,y=0;
		return a;
	}
	res=ext_gcd(b,a%b,x,y);
	tmp=x,x=y,y=tmp-a/b*y;
	return res;
	//返回值即gcd(a,b)
}
```

# 解线性方程

## 定义

- 定义形如 ax+by=c的方程（其中x,y为未知数）的方程叫做“线性方程”；
- 它的解总是成对出现的（类比线的上点）；
- 它等价于求解ax≡c(mod b)；
- 它有整数解的**充要条件**是c%gcd(a,b)=0。

## 求解方法

根据以上条件，我们可以：

①用扩欧求出其中的一组x0,y0，满足ax0+by0=gcd(a,b)；

②再将等式两边同除gcd(a,b)、同乘c，就得到了方程组的一组解。

③我们还有一个结论：如果gcd(a,b)=1,x0,y0为线性方程组的一组解，那么方程的任何一组解都可以表示为：x=x0+bt,y=y0-at。对于任意整数t，都成立。

- 对于③，我们可以想象：坐标系中的一条直线上总有无数个**格点**（即横纵坐标均为整数），已知直线的斜率（k=a/b）和直线上一个点(x0,y0)，我们可以利用点斜式表示其他所有的点。

④特殊地，当c=1，gcd(a,b)=1时，这个线性方程组只有唯一解（x），我们称解同余方程ax≡1(mod b)得到的结果为**a关于模b的乘法逆元**。

# 解决题目

显然是求解线性方程ax+by=-c，利用如上内容求解即可，模板如下：
```
#include<bits/stdc++.h>
using namespace std;
long long ext_gcd(long long a,long long b,long long &x,long long &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	long long d=ext_gcd(b,a%b,x,y);
	long long temp=x;x=y,y=temp-a/b*y;
	return d;
}
bool linear_Eqa(long long a,long long b,long long c,long long &x,long long &y){
	long long d=ext_gcd(a,b,x,y);
	if(c%d) return false;
	//不可用同余式表示，方程无整数解 
	long long k=c/d;
	x*=k,y*=k;
	return true;
}
int main(){
	long long a,b,c,x,y;
	cin>>a>>b>>c; c=-c;
	//a b c 为方程内的系数（和常数） 
	if(linear_Eqa(a,b,c,x,y)) printf("%lld %lld\n",x,y);
	else puts("-1");
	return 0;
}
```


---

## 作者：KagurazakaKano (赞：5)

### ex_gcd定义

首先我们要理解原生 $\gcd$ 算法：

$\gcd(a, b)$ 表示的是 $a, b$ 的**最大公约数**。

ex_gcd算法可以解决这样的问题：

> #### 解一组 $x, y$, s.t. $ax+by=\gcd(a,b)$。

### 代码

```cpp
void ex_gcd (LL a, LL b, LL &x, LL &y) {
	if(!b) {x = 1; y = 0;}
	else {ex_gcd(b, a % b, y, x); y -= a / b * x;}
}
```

~~反正我是背结论的，因为不会证这玩意qwqq。~~

### 关于线性方程

通过ex_gcd可以解线性方程 $ax+by=c$ ；

其实它等价于求解 $ax\equiv c \pmod{b}$；

它有整数解的**充要条件**是 $c\%\gcd(a,b)=0$。

### 求解方法

1. 首先用ex_gcd求出其中的一组特解 $x,y$ s.t. $ax+by=\gcd(a,b)$ 。

2. 再将等式两边同除 $\gcd(a,b)$ 、同乘 $c$，就得到了方程组的一组解。

由于这是个不定方程，因此这个方程显然有无数多组解，只要加减一个 $\gcd$ 即可。

### 对于本题

$Ax+By+C=0$ 显然可以写作：$Ax+By=-C$。

因此我们只要通过上面的方法求出一组 $x,y$ 作为特解即可。

### Code
```cpp
#include <cstdio>
typedef long long LL;

void ex_gcd (LL a, LL b, LL &x, LL &y) {
	if(!b) {x = 1; y = 0;}
	else {ex_gcd(b, a % b, y, x); y -= a / b * x;}
}

int main() {
	LL a, b, c, x = 0, y = 0, gcd;
	scanf("%lld %lld %lld", &a, &b, &c);
	c = -c; ex_gcd(a, b, x, y);  //求解 ax + by = gcd(a, b) 的一组特解
	gcd = a * x + b * y;
	if(c % gcd) return puts("-1"), 0;  //不满足有解
	x = c / gcd * x;  //先除，防止爆long long
	y = c / gcd * y;
	printf("%lld %lld\n", x, y);
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：2)

$\text{Update on 2020.9.4}$ 修正了一处错误（将后文的c改成-c）。

本蒟蒻刚学扩欧，讲得不好请见谅。

-----

根据题意，我们把$Ax+By+C=0$ 转化成 $Ax+By=-C$，然后横纵坐标（x,y）均为整数，也就是要求该方程的整数解。

看到这个二元一次不定方程，我们就马上想到了扩欧。

**该题重点算法：扩展欧几里得算法，又称ExGcd(Extended GCD)。**

扩展欧几里得算法，是用来在已知a,b，求解一组x,y使得$a*x+b*y=\gcd(a,b)$。

$$\because\gcd(a,b)=\gcd(b,a\%b)$$
$$\therefore a*x+b*y=\gcd(a,b)=gcd(b,a\%b)$$
然后右式$\gcd(b,a\%b)$ 又有一组x,y使得$b*x+y*(a\%b)=\gcd(b,a\%b)$，
$$\begin{aligned}\therefore gcd(b,a\%b)&=b*x+y*(a\%b)\\&=b*x+y*(a-a/b*b)\\&=b*x+y*a-y*a/b*b\\&=y*a+(x-y*a/b)*b\end{aligned}$$
这样它就将a与b的线性组合化简为b与a%b的线性组合。

a和b都在减小，当b为0时，得出$x=1,y=0$。递归回去就可以求出最终的x,y了。

代码：
```cpp
int Exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return a;
	}
	int ret,tmp;
	ret=Exgcd(b,a%b,x,y);
	tmp=x;
	x=y;
	y=tmp-a/b*y;
	return ret;
}//该函数返回值是gcd(a,b)
```
-----
但我们求出了一组 $x, y$ 还不够，我们的最终答案不是 $\gcd(a,b)$ 而是 $-c$。

我们发现， $a*x$ 和 $b*y$ 都是 $\gcd(a,b)$ 的倍数，如果想要整数解的话，那 $-c$ 肯定也要是 $\gcd(a,b)$ 的倍数。

所以先特判，如果 $c \bmod\gcd(a,b)\not=0$，则输出`-1`。

如果不是的话，那么可以继续推：

$$\begin{aligned}a*x+b*y&=\gcd(a,b)\\a*x*\frac{-c}{\gcd(a,b)}+b*y*\frac{-c}{\gcd(a,b)}&=\gcd(a,b)*\dfrac{-c}{\gcd(a,b)}=-c\end{aligned}$$

这样，一组整数解 $(x*\frac{-c}{\gcd(a,b)},y*\frac{-c}{gcd(a,b)})$ 就求出来了。

注意开`long long`，我为了方便直接`#define int long long`~~（其实是打的时候才发现要longlong）~~

代码：
```cpp
#include<iostream>
#include<cmath>
#define int long long//省力
using namespace std;
int Exgcd(int a,int b,int &x,int &y){//扩欧
	if(!b){
		x=1;
		y=0;
		return a;
	}
	int ret,tmp;
	ret=Exgcd(b,a%b,x,y);
	tmp=x;
	x=y;
	y=tmp-a/b*y;
	return ret;
}
signed main(){
	int a,b,c,x,y,d;
	cin>>a>>b>>c;
	c=-c;//别忘
	d=Exgcd(a,b,x,y);//求出gcd
	if(c%d) cout<<-1;//无整数解
	else{
		cout<<x*c/d<<" "<<y*c/d;
	}
	return 0;
} 
```


---

## 作者：fls233666 (赞：1)

首先我们从这个直线方程入手：

$$
Ax+By+C=0
$$

也许我们并不能从这个普通的直线方程里面看出什么。

但如果移项一下：

$$
Ax+By=-C
$$

好极了！现在这是**一个标准的二元一次不定方程**了！

下面我们考虑哪些数论知识和二元一次不定方程有关。

一般，我们会最先想到的两个定理，就是 [裴蜀定理](https://oi-wiki.org/math/bezouts/) 和 [扩展欧几里得定理](https://oi-wiki.org/math/gcd/) 。

为什么呢？

先简单说明一下这两个定理分布有什么用处。

- 裴蜀定理：用于判定一个一元二次不定方程是否有整数解。
- 扩展欧几里得定理：用于求出一个有整数解的一元二次不定方程 $ax+by=\gcd(a,b)$ 的一组可行解。

而再看题目要我们做的事情：

- 判断直线上是否存在整点。
- 如果有整点，找到并输出一个整点。

正好和我们用这两个定理能做的事情一致！

下面开始介绍具体做法。

首先说明一下裴蜀定理的具体内容：

**对于一个一元二次不定方程 $ax+by=c$ ，它有整数解，当且仅当 $c$ 能够被 $\gcd(a,b)$ 整除。**

由此，判断 $C$ 是否能被 $\gcd(A,B)$ 整除，即可得到是否有解。

有解之后，再使用扩展欧几里得定理，我们可以求得一组关于方程 $Ax+By=\gcd(A,B)$ 的可行解。记这组可行解为 $x_0,y_0$。因为我们真正要求解的方程是 $Ax+By=-C$ ，所以最终答案为 $x=x_0 \times \frac{-C}{\gcd(A,B)},y=y_0 \times \frac{-C}{\gcd(A,B)}$ 

思路大致如上，下面就是代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

ll a,b,c,x,y,g;

ll exgcd(ll num1,ll num2){  //标准的EXgcd
	if(!num2){
		x=1;
		y=0;  //ax+by=a的一个可行解
		return num1;  //返回最大公约数
	}
	ll tg=exgcd(num2,num1%num2);  //辗转相除
	ll tmp=x;
	x=y;
	y=tmp-y*(num1/num2);  //转化可行解
	return tg;  //返回最大公约数
}

int main(){
	scanf("%lld%lld%lld",&a,&b,&c);
	g=exgcd(a,b);
	if(c%g)  //由裴蜀定理判无解
		printf("-1");
	else{  //求出题目要的答案
		x*=c/g;
		y*=c/g;
		printf("%lld %lld",-x,-y); 
	} 
	return 0;
}

```



---

## 作者：_LanFeng_ (赞：1)

这题一看就是扩欧水题（注意没学过扩欧那肯定就不是了，学过扩欧其实就是模板题），将此算式转换为Ax+By=-C即可，注意补充几个知识点（这几个知识点看完后可以自己写写代码，如果实在写不出来再来看代码，毕竟模板题记住就行了，但是还要理解）：

扩展欧几里得算法：对于整数a，b，必定存在整数对x，y满足a*x+b*y=gcd(a, b)

扩展欧几里得算法应用

1.不定方程ax+by=c无解判定：如果c%d==0有解，否则无解

2.求解不定方程ax+by=c：先用扩欧求出ax’+by’= d =gcd(a,b)的一组解x'和y'，则方程原来的一组解为 x=x'*c/d，y=y'*c/d，通解为x=x'*c/d+k*b/d，y=y'*c/d-k*a/d（k为任意整数）

3.解模线性方程：a ≡ b (mod n)的含义是a和b关于模n同余，即a mod n==b mod n，则ax-b=ny,移项得ax-ny=b,这恰好是一个二元一次不定方程，用2解决。

4.乘法逆元：ax ≡ 1 (mod n)的解x称为a关于模n的乘法逆元。若gcd(a,n)=1有唯一解，反之无解。注意：通过扩欧算出的不定方程有很多解，最终的逆元应该是（x%n+n）%n,也就是逆元的范围是[0,n-1]

5.改写算式：(a/b) mod p == (a*（b的逆元） ) mod p==((a mod p)*(（b的逆元） mod p)) mod p

至于证明就不再给出，毕竟LX说过：“证明是数竞选手的事，我们信竞看看，然后用就好了（百度一大堆感兴趣可自行搜索）。”

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
long long kuoou(long long a,long long b,long long &x1,long long &y1)//地址符号注意
{
    long long x2,y2;
    if(b==0)
    {
        x1=1;
        y1=0;
        return a;
    }
    long long d=kuoou(b,a%b,x2,y2);
    x1=y2;
    y1=x2-a/b*y2;
    return d;
}
int main()
{
    long long a,b,c,x,y;
    scanf("%lld%lld%lld",&a,&b,&c);
    c=-c;
    long long d=kuoou(a,b,x,y);//这里面的x，y只是当ax+by==gcd（a，b）时候的解，还要在下面进行转换
    if(c%d!=0)
    {
        printf("-1");
        return 0;
    }
    x=x*c/d;
    y=y*c/d;//这两步
    //如果不是随机解而是限制解怎么办呢（比如最小解）？
    //那么我们就要用到循环并分类讨论，具体代码不在阐述
    printf("%lld %lld",x,y);
    return 0;
}
```

---

## 作者：happybob (赞：1)

公式变形：

$\large∵ ax + by + c = 0$

$\large∴ ax + by = -c$

然后就请出我们的贝祖（也叫pei shu）定理：

$\large ax + by = n$ 且 $\large a, \,b, \,n \in Z$，当且仅当$\large gcd(a, b) \,|\, n$ 时有整数解。

证明：

设 $\large c = gcd(a, \,b)$，可将式子变为：

$\Large cp + cx = n$

然后乘法分配律：

$\Large c(p + x) = n$

所以，$\large gcd(a, b) \,|\, n$时有解

然后判断，有解 `exgcd` ，无解 `-1`。

但是我们用 `exgcd` 是对于形如 $\large ax + by = gcd(a, b)$ 的，那么我们既然知道$\large gcd(a, b)\,|\,n$，将其结果除以$\large gcd(a, b)$ 然后乘以拓欧的结果可得到正确答案。

代码：

```cpp
#include <iostream>
using namespace std;

#define int long long

inline int gcd(const int a, const int b)
{
	if(b == 0)	return a;
	return gcd(b, a % b);
}

inline bool bz(const int& a, const int& b, const int& n) {return n % gcd(a, b);} 

inline void exgcd(int& x, int& y, int a, int b)
{
	if(b == 0) {x = 1; y = 0; return ;}
	exgcd(y, x, b, a % b);
	y -= a / b * x;
}

signed main()
{
	int a, b, c;
	cin >> a >> b >> c; c = -c;
	if(bz(a, b, c)) {cout << "-1\n"; return 0;}
	int x, y; x = y = 0; exgcd(x, y, a, b);
	x = c / gcd(a, b) * x;
	y = c / gcd(a, b) * y;
	cout << x << " " << y << endl;
	return 0;
}
```


---

## 作者：Mysterious_Cat (赞：0)

## 题解 CF7C 【Line】
### a) 题目大意：求$ax+by=-c$的一组整数解。
### b) 题目思路：参见P1082，看出是一道极裸的扩展欧几里得算法。 
### c) 知识讲解：
 1. 扩展欧几里得  
   
 **根据斐蜀定理，可以进行以下推导：**
- $ax+by=c$
- $ax+by=gcd(a,b)$
- $bx_1+(a$%$b)y_1=gcd(b,a$%$b)$
- $bx_1+(a-[\frac{a}{b}]*b)y_1=gcd(b,a$%$b)$
- $gcd(a,b)=gcd(b,a$%$b)$
- $ax+by=bx_1+(a-[\frac{a}{b}]*b)y_1$
- $ax+by=ay_1+b(x_1-[\frac{a}{b}]y_1)$
- $x=y_1,y=x_1-[\frac{a}{b}]y_1$
 2. 代码实现
```cpp
int exgcd(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int xx, yy;
    int res = exgcd(b, a % b, xx, yy);
    x = yy;
    y = xx - a / b * yy;
    return res;
}
```
### d) 题目代码：$Ax+By+C=0 ==> Ax+By=-C$
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long exgcd(long long a, long long b, long long &x, long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long xx, yy;
    long long res = exgcd(b, a % b, xx, yy);
    x = yy;
    y = xx - a / b * yy;
    return res;
}
int main()
{
    long long a, b, c, x, y;
    scanf("%lld %lld %lld", &a, &b, &c);
    long long d = exgcd(a, b, x, y);
    c = -c;
    if(c % d != 0)
    {
        printf("-1");
        return 0;
    }
    x = c / d * x;
    y = c / d * y;
    printf("%lld %lld", x, y);
    
    return 0;
}
```



---

## 作者：Unordered_OIer (赞：0)

# CF7C 题解
最近在找扩欧的题，就找到了这道。

## 题意
求方程
$$ax+by+c=0$$
的一组解

## 题解
实际上我个人觉得这道题应该要用 $\colorbox{orange}{\color{white}SpecialJudge}$，但是其实扩欧写得对的话是都会算出一个结果的。。。

我们把这个方程转换一下
$$ax+by=-c$$
这就相当于求一个不定方程的一组特解。

首先由贝祖定理，我们知道当这个方程存在解，必须满足 $\gcd(a,b)\ |\ -c$，如果不满足的话就无解，输出 -1 即可。

然后任务就是求解
$$ax+by=-c$$

我们回顾一下 MO 里是如何求解  
$$ax+by=\gcd(a,b)$$
的，例如：  

求下列方程的一组解
$$20x+32y=4$$

首先先写出求 $\gcd(20,32)$ 的过程：  

$32 \div 20=1......12$  
$20 \div 12=1......8$  
$12 \div 8=1......4$  
$8 \div 4=2......0$  

则我们可以得到：

$4=12-8 \times 1$  
$=12-(20-12 \times 1) \times 1$  
$=12-20+12$  
$=12 \times 2-20 \times 1$  
$=(32-20 \times 1) \times 2-20 \times 1$  
$=32 \times 2-20 \times 3$  
$=32 \times 2+20 \times (-3)$

于是对于方程

$$20x+32y=4$$

我们就求出了一组特解：

$$\begin{cases}x=2\\y=-3\end{cases}$$

然后如果这个方程变为

$$20x+32y=4k(k \in \mathbb Z)$$

我们只需要在原先我们求解的 $20x+32y=4$ 的解的基础上统一乘上 $k$ 就行了。

以上算法称为 **扩展欧几里得** 算法，也就是 $\text{exgcd}$。

现在我们就是要用程序来求解这个问题，代码很简单：

```cpp
inline ll exgcd(ll a, ll b, ll &x, ll &y) {
  if(b==0) {x=1, y=0; return a;}
  ll r=exgcd(b, a%b, x, y), tmp=y;
  y=x-(a/b)*y, x=tmp;
  return r;
}
```

然后就是求解问题了：

```cpp
inline ll solve(ll a, ll b, ll c) {
	ll ng=gcd(a, b);
	c=-c;  //ax+by=  -c  !
	if(c%ng!=0)return -1LL;
	ll k=c/ng;
	exgcd(a, b, x, y);
	x*=k, y*=k;
	return 1LL;
}
```

## Code
完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();

    while (!isdigit(ch)) {
        if (ch == '-')
            f = -f;

        ch = getchar();
    }

    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }

    return x * f;
}
inline void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;

    if (x > 9)
        write(x / 10);

    putchar(x % 10 + '0');
}
inline void writeln(ll x) {
    write(x), putchar('\n');
}
ll a, b, c, x, y;
inline ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}
inline ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    ll r = exgcd(b, a % b, x, y), tmp = y;
    y = x - (a / b) * y, x = tmp;
    return r;
}
inline ll solve(ll a, ll b, ll c) {
    //ax+by=-c
    ll ng = gcd(a, b);
    c = -c;

    if (c % ng != 0)
        return -1LL;

    ll k = c / ng;
    exgcd(a, b, x, y);
    x *= k, y *= k;
    return 1LL;
}
int main() {
    a = read(), b = read(), c = read();

    if (solve(a, b, c) == -1LL)
        return puts("-1"), 0;

    write(x), putchar(' '), writeln(y);
    return 0;
}
```

完结撒花~求赞 qwq

---

## 作者：HoshiuZ (赞：0)

打算切一题再睡~~最好是那种不怎么费脑子的~~

于是便找到了这题。

看到第一眼：这不是扩欧的板子题吗？

稍微分析一下。

### 思路
其实就是求不定方程$Ax+By=-C$的整数解对$(x,y)$。

有个定理，对于不定方程$ax+by=c$，当且仅当$gcd(a,b)|c$时，方程有整数解。

于是便直接用扩欧算出$Ax+By=gcd(A,B)$的一对解，顺便记录$d=gcd(A,B)$，然后判断$C$是否是$d$的倍数，若不是就直接输出$-1$，若是的话将求出的$x,y$都乘上$-\frac{C}{d}$。

最终输出即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long 

using namespace std;

ll a,b,c,d,x,y;

void EXgcd(ll a,ll b,ll& d) {
	if(!b) {
		d=a;
		x=1,y=0;
		return ;
	}
	EXgcd(b,a%b,d);
	ll t=x;
	x=y;
	y=t-a/b*y;
}

int main() {
	cin>>a>>b>>c;
	
	EXgcd(a,b,d);
	if(c%d) cout<<-1<<endl;
	else cout<<-(c/d)*x<<" "<<-(c/d)*y<<endl;
	
	return 0;
}
```

---

## 作者：叶枫 (赞：0)

虽然我在洛谷上没过

![0.0..jpg](https://img.langlangago.xyz/2019/09/01/5d6af25fdddf4.jpg)

但是，我在CF上过了（滑稽

![](https://img.langlangago.xyz/2019/09/01/5d6af32cef154.jpg)

### 题目大意

给方程 $Ax+By+C=0$.其中$A$，$B$，$C$为已知,求$x$，$y$。 

### $Idea$

拓展欧几里得算法的模板题.

该算法求出线性方程$Ax + By = gcd(A, B)$

然后，这个方程可进行转换:

$$Ax + By = gcd(A, B)$$

$$\to Ax + By = -\frac{C}{z}, -\frac{C}{z}= gcd(A, B)$$

$$\to Ax\ast z + By\ast z = C.$$

其中$x$, $y$可以通过拓展欧几里得算法求出，

然后，我们只需要求出$z$， 而$z=-\frac{C}{gcd(A,B)}$;

所以， 最终答案$x=x\ast -\frac{C}{gcd(A,B)}$ , $y=y\ast -\frac{C}{gcd(A,B)}$;
_____
以下给出拓展欧几里得的模板
```cpp
inline int ecgcd(int a,int b,int &x,int &y){
	if(!b) {x=1; y=0; return a;}
	int d=exgcd(b,a%b,x,y);
	int z=x; x=y; y=z-y*(a/b);
	return d;
}
```
$AC$ 程序自己写

---

## 作者：PC_DOS (赞：0)

解决本题肯定不能暴力，需要使用\_**扩展欧几里得算法**\_:


\_**对于给定的整数a、b(a、b不同时为0)，一定存在一组整数(x,y)使得ax+by=GCD(a,b)=g。**\_


本题所给的直线方程Ax+By+C=0，必定可以化为Ax+By=-C，此时，问题转化为: 是否存在一个整数k和有序整数对(m,n)，使得-C=k·GCD(A,B)=(Am+Bn)·k=A(km)+B(kn)，此时，有序整数对(km,kn)即为题目所求的一个坐标。


参考资料:


[扩展欧几里德算法(百度百科)](https://baike.baidu.com/item/%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%B7%E7%AE%97%E6%B3%95)


代码:

```cpp
#include <iostream>
using namespace std;
long long ExtendedEculid(long long iNum1, long long iNum2, long long &iAnsX, long long &iAnsY){ //扩展欧几里得算法的具体实现，返回值为iNum1和iNum2的最大公约数，iAnsX和iAnsY传回使得iNum1·x+iNum2·y=GCD(iNum1,iNum2)的一组特解
    if (iNum2 == 0){ //若iNum2为0，递归终止
        iAnsX = 1; 
        iAnsY = 0; //传回(x,y)
        return iNum1; //传回最大公约数
    }
    long long ret;
    ret=ExtendedEculid(iNum2, iNum1%iNum2, iAnsX, iAnsY); //递归调用
    long long iTmp = iAnsX;
    iAnsX = iAnsY;
    iAnsY = iTmp - (iNum1 / iNum2)*iAnsY; //递归调用结束后，逐层返回，此时的(x,y)即为使得iNum1·x+iNum2·y=GCD(iNum1,iNum2)的一组特解
    return ret; //传回最大公约数
}
int main(){
    ios::sync_with_stdio(false); //关闭与STDIO的同步，加快输入输出速度
    long long iX, iY; //存放答案的坐标
    long long A, B, C,iGCD; //A、B、C的意义如题目所述，iGCD为A与B的最大公约数
    cin >> A >> B >> C; //输入A、B、C
    iGCD=ExtendedEculid(A, B, iX, iY); //调用扩展欧几里得算法的实现
    if (C%iGCD){ //如果C不能被GCD(a,b)整除，则不存在k使得-C=k·GCD(A,B)，无解
        cout << -1; //输出-1
        goto endapp; //结束
    }
    iX *= -C/iGCD; 
    iY *= -C/iGCD; //对扩展欧几里得算法解得的特解(x,y)进行处理，使其在给定直线上
    if (iX <= 5e18 && iX >= -5e18 && iY <= 5e18 && iY >= -5e18) //如果满足要求
        cout << iX << ' ' << iY; //输出(x,y)
    else
        cout << -1; //输出-1
endapp:
    return 0; //结束
}
```

---

