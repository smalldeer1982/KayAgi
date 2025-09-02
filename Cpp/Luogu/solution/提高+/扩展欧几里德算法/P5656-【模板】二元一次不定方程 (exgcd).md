# 【模板】二元一次不定方程 (exgcd)

## 题目描述

给定不定方程

$$ax+by=c$$

若该方程无整数解，输出 $-1$。  
若该方程有整数解，且有正整数解，则输出其**正整数**解的数量，所有**正整数**解中 $x$ 的最小值，所有**正整数**解中 $y$ 的最小值，所有**正整数**解中 $x$ 的最大值，以及所有**正整数**解中 $y$ 的最大值。  
若方程有整数解，但没有正整数解，你需要输出所有**整数解**中 $x$ 的最小正整数值， $y$ 的最小正整数值。

正整数解即为 $x, y$ 均为正整数的解，$\boldsymbol{0}$ **不是正整数**。  
整数解即为 $x,y$ 均为整数的解。  
$x$ 的最小正整数值即所有 $x$ 为正整数的整数解中 $x$ 的最小值，$y$ 同理。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le T \le 2 \times {10}^5$，$1 \le a, b, c \le {10}^9$。

## 样例 #1

### 输入

```
7
2 11 100
3 18 6
192 608 17
19 2 60817
11 45 14
19 19 810
98 76 5432```

### 输出

```
4 6 2 39 8
2 1
-1
1600 1 18 3199 30399
34 3
-1
2 12 7 50 56```

# 题解

## 作者：dengyaotriangle (赞：359)

本题的出题人来放一个题解~

以这道题为模板，洛谷上所有$\text{exgcd}$的题直接改改都能过（

$$ax+by=c$$

显然有 $\gcd(a,b)|(ax+by)$ ，故若 $c$ 不是 $\gcd(a,b)$ 的倍数直接无解


我们已知$\text{exgcd}$可以求出

$$ax+by=\gcd(a,b)$$

的一组整数特解，我们记为 $x_0$ 与 $y_0$

则有

$$ax_0+by_0=\gcd(a,b)$$

$$a\frac{x_0c}{\gcd(a,b)}+b\frac{y_0c}{\gcd(a,b)}=c$$

故我们已经找到了原方程的一组整数特解，记为 $x_1$ 和 $y_1$

$$x_1=\frac{x_0c}{\gcd(a,b)}, y_1=\frac{y_0c}{\gcd(a,b)}$$

那么我们考虑构造原方程整数通解形式

我们设任意 $d \in \mathbb{Q}$ ，那么必有

$$a(x_1+db)+b(y_1-da)=c$$

（自行拆括号，直接消掉）

同时，通解需要保证 $x_1+db$ 与 $y_1-da$ 均为整数

因为 $x_1$ , $y_1$ 为整数，我们只需要保证

$db \in \mathbb{Z} $，$da \in \mathbb{Z} $

令当 $d$ 取到最小的可能的正值时的 $d_x=db$，$d_y=da$ ，那么任意解中这两个变量与 $x_1$ $y_1$ 的偏差一定分别是 $d_x$ 与 $d_y$ 的倍数

显然最小时 $d_x=\frac{b}{\gcd(a,b)}$ ， $d_y=\frac{a}{\gcd(a,b)}$，在$d=\frac{1}{\gcd(a,b)}$ 时取到

那么通解形式就出来了，

$$x=x_1+sd_x$$
$$y=y_1-sd_y$$

其中，$s$ 是任意整数

而且，随着 $x$ 增大 $y$ 减小 （废话，它们的和一定）

而且，$s$ 越大，$x$ 越大，$y$ 越小，反之亦然（重点）

故我们可以继续解题：

若我们限制 $x>0$，有$x_1+sd_x>0$，$s>-\frac{x_1}{d_x}$

若我们限制 $y>0$，有$y_1-sd_y>0$，$s<\frac{y_1}{d_y}$

那么我们有 $-\frac{x_1}{d_x}<s<\frac{y_1}{d_y}$

因为 $s$ 是整数，故有

$$\lceil\frac{-x_1+1}{d_x}\rceil\leq s\leq\lfloor\frac{y_1-1}{d_y}\rfloor$$

若 $\lceil\frac{-x_1+1}{d_x}\rceil> \lfloor\frac{y_1-1}{d_y}\rfloor$，那么显然不可能让两个都是正整数（因为没有合法的 $s$）

此时，答案即为没有正整数解但有整数解，$x$ 最小即为$s=\lceil\frac{-x_1+1}{d_x}\rceil$时 $x$ 的值，$y$ 最小即为$s=\lfloor\frac{y_1-1}{d_y}\rfloor$时 $y$ 的值

否则，就有正整数解，正整数解个数即为 $s$ 的合法整数取值个数，算好上下界直接做。

而最大最小值什么的，$x$ 的最大值和 $y$ 的最小值都是在 $s$ 最大时取到，而  $x$ 的最小值和 $y$ 的最大值都是在 $s$ 最小时取到，直接计算即可。

其实这些玩意是可以化简为更简单的形式的（详见其他题解），但我认为这个解题思路最容易让初学者理解。

代码就不放了，丑死了，照着题解里公式敲一遍就完事了。

关于坑点：

开long long。

---

## 作者：yangrunze (赞：122)

先说两句：
1. 本题解学习了编程&$\LaTeX$神仙 $\color{black}{\text{离}}\color{red}\text{散小波变换\degree}$ 的思路，让我们一起%ta！~~（管理员：题解抄袭题解，棕了！）~~
2. 在阅读本文之前，如果你已经学会了exgcd的基础用法，并且AC  [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)，那就更好啦！

没有做到也没关系，让我们先来了解一下exgcd的基础用法：

exgcd算法，听名字就知道跟辗转相除法求$\gcd$有关，我们用的就是辗转相除法的核心式子：

$\gcd(a,b)=\gcd(b,a\bmod b)$

exgcd：求$ax+by=\gcd(a,b)$的整数解

设$\gcd(a,b)=d$

则$ax+by=d$

我们设已经找到了一组解$x',y'$，使$bx'+(a \bmod b)y'=\gcd(a,b)$

$bx'+(a \bmod b)y'=d$

由于商$\times$除数+余数=被除数，$a\bmod b$可以这么表示：

$bx'+(a-\lfloor\dfrac{a}{b}\rfloor\times b)y'=d$

给它稍微变个形：

$bx'+ay'-\lfloor\dfrac{a}{b}\rfloor\times by'=d$

$ay'+b(x'-\lfloor\dfrac{a}{b}\rfloor\times y')=d$

和原式对比一下，你会惊奇地发现：

$\begin{cases}x=y'\\y=x'-\lfloor\dfrac{a}{b}\rfloor\times y'\end{cases}$

由于$b=0$时$\begin{cases}x=1\\y=0\end{cases}$，所以递归求解即可

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
ll x,y; 
void exgcd(ll a,ll b){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b);
	ll t=x;
	x=y;
	y=t-a/b*y;
}
int main(){
	ll a,b;
	cin>>a>>b;
	exgcd(a,b);
	cout<<(x%b+b)%b;
}
```
以上就是最基础的exgcd啦！但是我们肯定不能只满足于这些，接下来

正 片 开 始


……题目看样子好难鸭……

没关系，咱们一个一个来看！

>若该方程无整数解，输出 $-1$

这个很好办，根据**裴蜀定理**，如果$c$不是$gcd(a,b)$的倍数，方程必定无解

（不了解裴蜀定理的小伙伴[戳这](https://www.luogu.com.cn/blog/ravenclawyangrunze/ma-ma-wo-jing-ran-zheng-chu-liao-pei-shu-ding-li-post)，本文有很多地方也cv自这篇文章）

接下来，用exgcd求出$ax+by=\gcd(a,b)$的整数解之后，就是各种整数解的讨论啦！

把大象关进冰箱里要分三步，那么要解一个二元一次不定方程要分几步呢？也是三步

首先，咱们来想这样一个问题，

> step 1.用$ax+by=\gcd(a,b)$的整数解来**求$ax+by=c$的整数解**

这就非常简单了，咱还是设 $\gcd(a,b)=d$

由于$d$是$a$和$b$的最大公因数，所以$d$肯定能被他俩整除

从刚才的得到的结论出发，我们设已知$ax'+by'=d$，$d\times q=c$

两边同时乘$q$，这样的话就可以发现$ax'\times q+by'\times q=d\times q$，即$ax'\times q+by'\times q=c$

$\begin{cases}x=x'\times q\\y=y'\times q\end{cases}$就是方程的一组解啦

也就是说，这组解就是 $\begin{cases}x_0=x'\times \dfrac{c}{d}\\y_0=y'\times \dfrac{c}{d}\end{cases}$

> step 2.用这组解$x_0,y_0$找出方程所有的解

咱们还是先从这组解$x_0,y_0$出发，设$a(x_0+m)+b(y_0+n)=c$

这样的话我们只需要求出$m$和$n$就好啦

从这个式子出发：$a(x_0+m)+b(y_0+n)=c$

展开它：$ax_0+am+by_0+bn=c$

那只要让$am+bn=0$，那就没问题啦！

继续设$\gcd(a,b)=d$，我们让$\begin{cases}m=t\times \dfrac{b}{d}\\n=-t\times \dfrac{a}{d}\end{cases}$

带进去算一下$am+bn$得到$\dfrac{ab}{d}-\dfrac{ab}{d}$，果然是$0$！

任取一个$t$，就可以算出相应的$m$，$n$，进而推出$x$和$y$，通解get！

> step 3：考虑最大/最小值

这一步是重难点，竖起耳朵认真听哟！

首先，$\begin{cases}x=x_0+t\times \dfrac{b}{d}\\y=y_0-t\times \dfrac{a}{d}\end{cases}$

可以看出，**当$t$增大的时候，$x$越来越大，$y$越来越小**

由于增加/减少的值太难写了，接下来设$t\times \dfrac{b}{d}$为$t_x$，$-t\times \dfrac{a}{d}$为$t_y$，也就是$\begin{cases}x=x_0+t_x\\y=y_0+t_y\end{cases}$

接下来，我们需要找出$x$的最小整数解$x_{\min}$，只需要把$x_0$减去好多好多个$t$就好

那到底减多少呢？

既然是正整数，那就要求$x_{\min}\geq 1$，设减去$k$个$t$，就可以得到：

$x_0+kt_x\geq1$

接下来就是解一元一次不等式啦！

$kt_x\geq1-x_0$

两边同时除以$t$，因为这里要求$x$越来越小，所以$t$要小于$0$，注意要变号哟！

$k\geq\lceil\dfrac{1-x_0}{t_x}\rceil$

因为这边必须大于这个值，所以要取上整

这样的话，我们就可以得到$x_{\min}$，也就是$x_0-\lceil\dfrac{1-x_0}{t_x}\rceil$啦！

通过刚才的分析呢，$x_{\min}$对应的$y$值正好是$y_{\max}$，如果$y_{\max}<0$呢，那就没有正整数解啦！

（没有整数解的话，我们还需要把$y_{\min}$求出来，这个就和刚才处理$x_{\min}$的方法一样了，$y_{\min}=y_0-\lceil\dfrac{1-y_0}{t_y}\rceil$）


搞定了两个解，接下来咱们在搞剩下的两个：$x_{\max}$和$y_{\min}$

先来看$y_{\min}$：我们需要将$y_{\max}$减去尽可能多的$t_y$，使其为正整数

有没有发现一个神奇的事情？我们要求的$y_{\min}$，正好就是$y_{\max}\bmod t_y$！不过为了防止$0$之类的特殊情况，我们还是把它写成$(y_{\max}-1)\bmod t_y+1$

那我们的$x_{\max}$呢？很简单，只要加上和$y_{\max}$减去的相同的$t_x$就行惹，也就是$x_{\min}+\lfloor \dfrac{y_{\max}-1}{t_y}\rfloor\times t_x$

最后还剩下一个解的个数，还是看$y_{\max}$减到$y_{\min}$的过程，可以有$\lfloor \dfrac{y_{\max}-1}{t_y}\rfloor+1$个解

总结一下就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/o3cf069m.png)

放码过来呀！

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;//十年OI一场空，不开long long见祖宗
ll x,y;
inline ll read(){//卡常卡得好，快读不能少
	char c=getchar();
	int f=1;
	ll x=0;
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
} 
inline ll exgcd(ll a,ll b){//来一份萌萌哒exgcd
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll d=exgcd(b,a%b);
	ll t=x;
	x=y;
	y=t-a/b*y;
	return d;//顺便把最大公因数也给求出来了呢！
}
int main(){
	ll t=read();
	while(t--){
		ll a=read(),b=read(),c=read();
		ll d=exgcd(a,b);//求出d
		if(c%d){//不满足裴蜀定理，直接输出-1
			printf("-1\n");
			continue;
		}
		x=x*c/d,y=y*c/d;//求出x0和y0，tx和ty
		ll tx=b/d,ty=a/d;
		ll k=ceil((1.0-x)/tx);//求出k
		x+=tx*k;
		y-=ty*k;	
		if(y<=0){//如果没有正整数解，算出ymin之后输出
			ll ymin=y+ty*1ll*ceil((1.0-y)/ty);
			printf("%lld %lld\n",x,ymin);
		}
		else{//按照刚才说的处理
			printf("%lld ",(y-1)/ty+1);
			printf("%lld ",x);
			printf("%lld ",(y-1)%ty+1);
			printf("%lld ",x+(y-1)/ty*tx);
			printf("%lld\n",y);
		}
	}
	return 0;
}
```
The end

---

## 作者：小恐 (赞：10)

UPD:2020/5/4 更正了一些$\LaTeX$

~~数学模板题这么点题解？那我就来发一篇吧。~~

当$\gcd(a,b)\nmid c$时，显然等式不可能成立，输出-1。

否则，可以将$a,b,c$都除以$\gcd(a,b)$，只要这个等式成立，原等式一定成立，这样也就使得$\gcd(a,b)=1$了。

然后用$\operatorname{exgcd}$求出使得$a\times x+b\times y=1$成立的$x$和$y$，再将$x$和$y$都乘$c$，这样就满足$a\times x+b\times y=c$了。$\operatorname{exgcd}$怎么用看[这里](https://www.luogu.com.cn/blog/fufufu/exgcd-di-yong-fa)。

然后考虑是否有正整数解。显然当$x$越小时$y$越大，那就让$x$取最小正整数，如果这时$y>0$，则有正整数解，否则没有。

那$x$如何取最小正整数呢？我们已知一组整数解了，设为$x_1$和$y_1$，$a\times x_1+b\times y_1=c$，再设x取最小正整数时$x$和$y$为$x_2$和$y_2$。即$a\times x_2+b\times y_2=c$。

则$(x_1-x_2)\times a+(y_1-y_2)\times b=0$，因为$\gcd(a,b)=1$，所以$x_1-x_2=k\times b$，$y_1-y_2=-k\times b$，其中$k\in Z$。所以$x_2=x_1 \bmod b$，特别的，当$x_1 \bmod b=0$时，$x_2=b$。然后算出来$y_2=\dfrac{c-a\times x_2}{b}$。然后分情况讨论：

+ 当$y_2>0$时，再同理求一下$y$为最小正整数下$x$和$y$的值。这就有四个答案了。还要求有多少组正整数解，因为$x$最大值与最小值之间每隔$b$个数就有一个解，所以个数为$\dfrac{x_{max}-x_{min}}{b}+1$，当然同理$\dfrac{y_{max}-y_{min}}{a}+1$也是可以的。

+ 当$y_2\le0$时，求一下$y$的最小正整数值就行了。

最后再提一句：十年OI一场空，不开long long见祖宗！

OK，那就上代码吧：
```cpp
#include<stdio.h>
using namespace std;
void read(int &x)
{
	x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=bei;
}
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void exgcd(int a,int b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	long long t=x;
	x=y;
	y=t-a/b*y;
}
int main()
{
	int t;
	read(t);
	int a,b,c,gong;
	long long x,y;
	while(t--)
	{
		read(a),read(b),read(c);
		gong=gcd(a,b);
		if(c%gong)
		{
			puts("-1");
			continue;
		}
		a/=gong,b/=gong,c/=gong;
		exgcd(a,b,x,y);
		x*=c;
		y*=c;
		x=(x%b+b)%b;
		x=x==0?b:x;
		y=(c-a*x)/b;
		if(y>0)
		{
			long long xmin,xmax,ymin,ymax;
			xmin=x,ymax=y;
			y%=a;
			y=y==0?a:y;
			x=(c-b*y)/a;
			xmax=x,ymin=y;
			printf("%lld %lld %lld %lld %lld\n",(xmax-xmin)/b+1,xmin,ymin,xmax,ymax);
		}
		else
		{
			long long xmin,ymin;
			xmin=x;
			y=y%a+a;
			ymin=y;
			printf("%lld %lld\n",xmin,ymin);
		}
	}
	return 0;
}
```


---

## 作者：DengStar (赞：7)

## 扩展欧几里得算法

前置知识：欧几里得算法

扩展欧几里得算法（Extended Euclidean algorithm, EXGCD）用于求形如
$$
ax + by = c
$$
的**二元一次不定方程**的所有整数解。

（为了方便，我们认为 $a, b, c \ge 0$。对于负数的情况可能需要多一点讨论。）

### 有解性判定——裴蜀定理

裴蜀定理（Bézout's lemma）给出了二元一次不定方程有整数解的充要条件：方程 $ax + by = c$ 有解当且仅当
$$
\gcd(a, b) \mid c
$$
**证明**

设 $\gcd(a, b) = g$。

**必要性** 由于等式左边一定是 $g$ 的倍数，因此等式右边也必须是 $g$ 的倍数。

**充分性** 为了方便，不妨设 $c = g$。如果在这种情况下存在某组解，那么当 $c$ 是 $g$ 的倍数时，把这组解扩大若干整数倍，就可以得到原方程的解。所以研究有解性时只需考虑这种情况。

设 $S = \{xa + yb | x, y \in \mathbb{Z}\}$。下面证明 $S$ 中的最小正元素为 $g$。

首先，$S$ 中至少有一个正元素（$a$ 和 $b$，说“一个”是因为二者可能相同），设最小的正元素为 $d_0 = x_0a + y_0b$。另取 $S$ 中任一正元素 $p = x_1a + y_1b$，考虑它对 $d$ 的带余除法 $p = qd_0 + r$，那么
$$
\begin{aligned}
r &= p - qd_0 \\
&= (x_1a + y_1b) - q(x_0a - y_0b) \\
&= (x_1 - qx_0)a + (y_1 + qy_0)b
\end{aligned}
$$
因此 $r \in S$。由于 $r$ 是 $p$ 除以 $d_0$ 的余数，所以 $0 \le r < d_0$。如果 $r$ 为正数，就与 $d_0$ 的最小性矛盾。因此 $r = 0$。那么可以推出：$S$ 中任意正元素都是 $d_0$ 的倍数。特别地，有 $d_0 \mid a$ 和 $d_0 \mid b$，因此 $d_0$ 是 $a$ 和 $b$ 的公约数。

另一方面，由于 $a$ 和 $b$ 都是 $g$ 的倍数，而 $d_0$ 是 $a$ 和 $b$ 的线性组合，因此 $d_0$ 也是 $g$ 的倍数（在 I 章中我们已经用过了这个结论）。结合两点可知 $d_0 = g$。至此，我们就证明了当 $c = g$ 时 $ax + by = c$ 一定有解。对于更一般的情况，如果 $c = c'g$，把 $ax + by = g$ 的每个解乘 $c'$ 倍就得到了 $ax + by = c$ 的解，所以两个方程的有解性相同。$\Box$

### 解的形式及个数

我们可以进一步说明，只要有解，就有无数组解。设 $(x_0, y_0)$ 是任意一组解，$a = a'g$，$b = b'g$，则方程的解集为
$$
A = \left\{ \left( x_0 + kb', y_0 - ka' \right) | k \in \mathbb{Z} \right \}
$$
换句话说，把 $x$ 加上若干个 $b'$，同时把 $y$ 减去若干个 $a'$ 不改变 $ax + by$ 的值，因为 $a \cdot \dfrac{kb}{g} = b \cdot \dfrac{ka}{g}$。另外，这两者显然都是整数，所以变换后得到的还是整数解。

另一方面，对于任意的解 $(x', y')$ 满足 $ax' + by' = c$，把此等式与 $ax_0 + by_0 = c$ 相减，有
$$
a(x' - x_0) + b(y' - y_0) = 0
$$
由于 $a = a'g$，$b = b'g$，所以
$$
a'(x' - x_0) = -b'(y' - y_0)
$$
左边是 $a'$ 的倍数，因此右边也是 $a'$ 的倍数。又因为 $a'$ 与 $b'$ 互质，所以 $y' - y_0$ 是 $a'$ 的倍数。设 $y' - y_0 = a'k$，则 $y' = y_0 + a'k$，代入得 $x' = x_0 - b'k$，这就把 $(x', y')$ 转化成了 $A$ 中的形式。所以，$A$ 确实包含了方程的**所有**整数解。

### 过程

现在我们要求出 $ax + by = c$ 的**任意一组**解。先根据裴蜀定理判断是否有解，如果有解，为了方便仍然假设 $c = g$。求出一组解以后我们可以根据通解的公式求出其它的解。

我们使用和欧几里得算法类似的迭代方法：每次迭代都会使 $a$ 和 $b$ 减小，最终 $b$ 减小到 $0$ 时就可以得到显然的解，然后反推原方程的解。

具体地，如果 $b = 0$，那么 $\gcd(a, b) = a$，方程可以写为 $ax + 0y = a$。此时显然 $x = 1, y = 0$ 是一组解。当然，$y$ 可以取任何整数，但取 $0$ 比较方便，并且这保证了最终得到的原方程的解不会太大，

否则，我们把原方程迭代为一个新的方程：$a'x + b'y = \gcd(a', b')$，其中 $a' = b$，$b' = a \bmod b$。这样做的意义和欧几里得算法是相同的：迭代后方程的系数会减小，最终到达边界情况时就能得到解。那么，假设我们求出了这个方程的一组解 $(x_1, y_1)$，要如何反推回原方程的一组解 $(x_0, y_0)$ 呢？

由于 $\gcd(a, b) = \gcd(b, a \bmod b)$，所以 $\gcd(a, b) = \gcd(a', b')$，因此
$$
ax_0 + by_0 = bx_1 + (a \bmod b) y_1
$$
把 $a \bmod b$ 改写为 $a - b \cdot \left\lfloor \dfrac{a}{b} \right\rfloor$，那么
$$
ax_0 + by_0 = bx_1 + \left( a - b \cdot \left\lfloor \dfrac{a}{b} \right\rfloor \right)y_1
$$
整理等式右边，得到
$$
ax_0 + by_0 = ay_1 + b \left(x_1 - \left\lfloor \dfrac{a}{b} \right\rfloor y_1 \right)
$$
对比两边得到
$$
\begin{cases}
x_0 = y_1 \\
y_0 = \left(x_1 - \left\lfloor \dfrac{a}{b} \right\rfloor y_1 \right)
\end{cases}
$$
这就得到了两个方程解的关系。

此算法时间复杂度的分析和欧几里得算法完全相同，二者的时间复杂度都是 $O(\log w)$，其中 $w$ 是 $a$ 和 $b$ 的值域，这里不再赘述。

以下是一份 exgcd 的示例代码，它返回一个二元组（`pair`），表示方程的解 $x, y$：

```cpp
auto exgcd(int a, int b) {
    if(b == 0) {
        return make_pair(1, 0);
    }
    auto [x, y] = exgcd(b, a % b);
    return make_pair(y, x - (a / b) * y);
}
```

这种写法比较美观，因为函数的返回值恰好就是方程的解。但我不知道使用 `pair` 会不会导致常数偏大。大多数人使用的是一种传引用的写法：

```cpp
void exgcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1, y = 0;
		return;
	}
	int x0, y0;
	exgcd(b, a % b, x0, y0);
	x = y0, y = x0 - (a / b) * y0;
}
```

### 值域分析

$ax + by = g$ 的解有无穷个，显然我们希望扩欧求出的是比较小的解，否则无法存下。幸运的是，如果在迭代的最后一步选取的解是 $x = 1, y = 0$，那么最终求出的解满足 $|x| \le b$，$|y| \le a$。实际上，这种情况下 $|x|$ 和 $|y|$ **同时**取到最小值。证明暂略，可以参考 [OI wiki](https://oi-wiki.org/math/number-theory/gcd/#%E5%80%BC%E5%9F%9F%E5%88%86%E6%9E%90)。

需要注意的是，我们只是说明了 $ax + by = g$ 的解的值域范围，但对于更一般的 $ax + by = c$ 的情况，把 $x$ 和 $y$ 同乘上 $c / g$ 以后，值域是没有限制的。

### 本题的求解

这道题不仅要求出解，还要回答有关解的一些其它问题。我们逐个来研究。

1. **是否有解？**

   我们用裴蜀定理判断是否有解。现在假设有解，并且已经用扩欧求出了一组解 $(x_0, y_0)$。

2. **是否有正整数解？**

   我们让 $x_0$ 对 $b'$ 取模，就得到了 $x$ 为正整数的解中最小的 $x$。（为了保证 $x$ 为正，当 $x_0 \bmod b' = 0$ 时应取 $x = b'$ 而不是 $0$。）求出对应的 $y$，由于 $x$ 和 $y$ 是此消彼长的关系，现在已经尽可能让 $x$ 在为正的情况下尽可能小了，如果存在正整数解，那么 $y$ 此时一定为正，据此可以判断是否有正整数解。

   如果有正整数解，那么显然现在求出的 $x$ 和 $y$ 分别是正整数解中最小的 $x$ 和最大的 $y$，记为 $x_{\min}$ 和 $y_{\max}$。同理还可以求出正整数解中最大的 $x$ 和最小的 $y$，记为 $x_{\max}$ 和 $y_{\min}$。而如果没有正整数解，我们实际上也已经求出了 $x$ 和 $y$ 的最小正整数值。

3. **如果有正整数解，有多少个？**

   只需求出 $x_{\max}$ 和 $x_{\min}$ 中有多少个可以作为解的 $x$ 即可，也就是
   $$
   \dfrac{x_{\max} - x_{\min}}{b'} + 1
   $$

综上所述，我们就解决了本题。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

i64 mod(i64 x, i64 y) {
    i64 t = (x % y + y) % y;
    return t ? t : y; // 取正值
}

auto exgcd(int a, int b) {
    if(b == 0) {
        return make_pair(1, 0);
    }
    auto [x, y] = exgcd(b, a % b);
    return make_pair(y, x - (a / b) * y);
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    int g = __gcd(a, b), a0 = a / g, b0 = b / g, c0 = c / g;
    if(c % g != 0) {
        cout << "-1\n"; // 无解
        return;
    }

    i64 x, y;
    tie(x, y) = exgcd(a, b);
    x *= c0, y *= c0;
    i64 xmin = mod(x, b0), ymax = (c - a * xmin) / b;
    i64 ymin = mod(y, a0), xmax = (c - b * ymin) / a;

    if(ymax > 0) {
        i64 cnt = (xmax - xmin) / b0 + 1;
        cout << cnt << ' ' << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
    } else {
        cout << xmin << ' ' << ymin << '\n';
    }
}

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}
```

---

## 作者：Mirasycle (赞：3)

扩展欧几里得算法是用于求解形如 $ax+by=c$ 的方程，根据裴蜀定理其有解的充要条件是 $\gcd(a,b) | c$。

我们可以利用类似于求解 $\gcd$ 的方法来算 exgcd。由于 $\gcd(a,b)=\gcd(b,a\bmod b)$，所以把系数替换成 $(b,a\bmod b)$ 不仅保证有解，而且还缩小了问题规模，如果不断缩小问题规模直到边界条件就可以很轻松的得到一组解，而且根据辗转相除法，我们进行这个轮数为 $O(\log V)$。

我们现在计算 $ax+by=d=\gcd(a,b)$。假设我们已经知道了 $bx'+(a\bmod b)y'=d$ 的解了，那么有

$ax+by=bx'+(a\bmod b)y'=bx'+(a-\lfloor\dfrac{a}{b}\rfloor\times b)y'$
也就是 $ay'+b(x'-\lfloor\dfrac{a}{b}\rfloor y')$。

对比系数，$x\gets y',y\gets x'-\lfloor\dfrac{a}{b}\rfloor y'$。

按照上述流程递归求解即可。

临界条件是最后 $a=d,b=1$，此时解为 $x=1,y=0$。

最后解出 $ax+by=d$ 后，将解 $\times\dfrac{c}{d}$，就可以得到一组特解 $(x_0,y_0)$ 了。

exgcd 求出来的特解是满足 $ax+by=d$ 的 $\lvert x\rvert+\lvert y\rvert$ 最小的一组解，**注意这里的必须是 $=d$ 的解，如果是 $=c$ 的话就不满足这个性质了！** 关于如何在 $=c$ 的时候求出这个最小解，可以去看看 [P3543](https://www.luogu.com.cn/problem/P3543)。

有了特解之后，我们需要得到方程的特解。

设 $x,y$ 的变化量为 $\Delta x$ 和 $\Delta y$，有 $a\Delta x+b\Delta y=0$。得到 $\Delta x=-\dfrac{b}{a}\Delta y=-\dfrac{b/d}{a/d}\Delta y$（最后一步是约分）。

所以可以得到方程的通解为 $\begin{cases} x=x_0+\dfrac{b}{d}k
\\y=y_0-\dfrac{a}{d}k
\end{cases}$

得到通解的表达式之后就可以求一些特殊位置的解了。

令 $A=\dfrac{a}{d},B=\dfrac{b}{d}$，根据通解表达式可以得到 $x\equiv x_0\pmod B$，于是 $x$ 的最小正整数解就是 

$$\begin{cases} x_0\bmod B&x_0>0
\\x_0\bmod B+B& x_0<0
\end{cases}$$

对于 $y$ 同理。

对于 $x,y$ 都是正整数的情况下，显然是其中一个变大会让另一个变小，所以 $x$ 的最小正整数解对应的是 $x>0$ 的情况下 $y$ 的最大值。注意特判掉此时 $y$ 最大值 $<0$ 的情况。

关于 $x,y>0$ 的解的个数，由于 $x$ 每次变化 $B$，那么就是 $\dfrac{x_{\max}-x_{\min}}{B}+1$ 了。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void exgcd(int a,int b,ll& x,ll& y){
	if(!b){ x=1; y=0; return ; }
	exgcd(b,a%b,y,x); y-=a/b*x;
}
void solve(){
	int a,b,c; cin>>a>>b>>c; int d=__gcd(a,b);
	if(c%d){ cout<<"-1\n"; return ; }
	ll x0=0,y0=0; exgcd(a,b,x0,y0);
	x0*=c/d; y0*=c/d;//特解 
	ll xmn=x0%(b/d),ymn=y0%(a/d);
	xmn=xmn<=0?xmn+b/d:xmn;
	ymn=ymn<=0?ymn+a/d:ymn;
	ll xmx=(c-b*ymn)/a,ymx=(c-a*xmn)/b;
	if(ymx<=0){ cout<<xmn<<" "<<ymn<<"\n"; return ; }
	cout<<(xmx-xmn)/(b/d)+1<<" "<<xmn<<" "<<ymn<<" "<<xmx<<" "<<ymx<<"\n";
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

