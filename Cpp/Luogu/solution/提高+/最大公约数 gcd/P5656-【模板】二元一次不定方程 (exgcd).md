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

## 作者：dengyaotriangle (赞：343)

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

## 作者：yangrunze (赞：87)

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

## 作者：linponess (赞：49)

### **2020/1/25 UPD:更正了证明过程中符号的问题。（By [weapon_zipper](https://www.luogu.com.cn/user/88207)）**
### **2019/12/11 UPD:更正了在题解页面Latex代码漏出的问题。**

------------
## 该题解主要由以下内容组成：
- **扩展欧几里得算法（exgcd）**
- **求二元一次方程/线性同余方程特解**
- **求二元一次方程/线性同余方程通解**
- **暴力解决本题**
- **对暴力进行优化**

------------


------------


------------

### **扩展欧几里得算法（exgcd）**
扩展欧几里得算法：用于求解形如ax+by=gcd(a,b)的不定方程特解。

**求解方法&证明：** 当b=0时，可以看出gcd(a,b)=a，而

$$\left\{\begin{aligned}x & = 1\\y & = 0\\\end{aligned}\right.$$

是方程的一组特解。

当b$\neq$0时，递归求解exgcd(b,a%b,x,y)，设

$$\left\{\begin{aligned}a' & = b\\b' & = a\%b\\\end{aligned}\right.$$

可以求得a'x'+b'y'=gcd(a,b)的一组特解，即x',y'。

因为a'x'+b'y'等价于bx'+(a%b)y'，再根据模运算的定义可得bx'+(a-a/b*b)y'

bx'+ay'-(a/b*b)y'

ay'+b(x'-a/b*y')

此时就得到了

$$\left\{\begin{aligned}x & = y'\\y & = x'-a/b*y'\\\end{aligned}\right.$$

**代码：**
```cpp

void exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	int p;
	exgcd(b,a%b,x,y);
	p=x;
	x=y;
	y=p-(a/b)*y;
	return;
}
```

------------
### **求二元一次方程/线性同余方程特解**
**二元一次方程：**
对于形如ax+by=c的二元一次方程，根据扩展欧几里得算法的定义可得，当且仅当gcd(a,b)|c(|为整除)时，存在整数解。

设g=gcd(a,b),a'=a/g,b'=b/g,c'=c/g,则ax+by=c$\Leftrightarrow$a'x+b'y=c'，

此时gcd(a',b')=1,可以利用exgcd求出a'x'+b'y'=1的一组特解，继而得出

$$\left\{\begin{aligned}x_0 & = c'x'\\y_0 & = c'y'\\\end{aligned}\right.$$

我们便求得了ax+by=c的一组特解。

**线性同余方程：**
对于形如ax$\equiv$c(mod b)的线性同余方程，根据模运算的定义，在方程左侧添加一个by不会对结果造成影响，其实质就等价于ax+by=c的不定方程，利用上述方法求解便可。

------------
### **求二元一次方程/线性同余方程通解**
**二元一次方程：**
对于形如ax+by=c的二元一次方程，整数解通解为

$$\left\{\begin{aligned}x_t & = x_0+b't\\y_t & = y_0-a't\\\end{aligned}\right.$$
(t$\in\mathbb{Z}$)

对其进行证明：a$x_{t}$+b$y_{t}$

a($x_{0}$+b't)+b($y_{0}$-a't)

a$x_{0}$+ab't+b$y_{0}$+a'bt

a$x_{0}$+b$y_{0}$+at$*$
$\displaystyle\frac{b}{g}$-bt$*$
$\displaystyle\frac{a}{g}$

a$x_{0}$+b$y_{0}$+$\displaystyle\frac{abt}{g}$-$\displaystyle\frac{abt}{g}$

a$x_{0}$+b$y_{0}$

因为lcm(a,b)=$\displaystyle\frac{ab}{g}$，x,y的系数分别为a,b，所以x,y的最小增减幅度分别为$\displaystyle\frac{b}{g}$，$\displaystyle\frac{a}{g}$即b',a'。

**线性同余方程：**
同理于二元一次方程。

------------
### **暴力解决本题**
观察本题，发现对于给出的条件有三种情况：无整数解、无正整数解但有整数解、有正整数解。

**无整数解：**
要求输出-1。根据扩展欧几里得算法的定义可得，当c%gcd(a,b)$\ne$0时方程无整数解，输出-1即可。

**判断有无正整数解：**
根据二元一次方程的通解可得，x,y的增减性相反，所以若存在正整数解，则当x取得最小正整数解时，y取得最大正整数解，若此时y$\le$0,则说明该方程无正整数解。

**无正整数解但有整数解：**
要求输出x,y的最小正整数解。通过整除运算计算出x取得最小正整数解时的k值，继而求出x的最小正整数解，同理可以求出y的最小正整数解。

**有整数解：**
此时要求最复杂，要求输出正整数解的数量、x,y的最小正整数解、x,y的最大正整数解。因为当x取得最小正整数解时，y取得最大正整数解，可以利用上述方法求出x取得最小正整数解时的k值，x的最小正整数解与y的最大正整数解，该方法同样可以用于求解x的最大正整数解与y的最小正整数解。正整数解的数量=$\displaystyle\frac{x_{max}-x_{min}}{b'}$+1或$\displaystyle\frac{y_{max}-y_{min}}{a'}$+1。

**代码:**
```cpp
#include<cstdio>
using namespace std;
int read()
{
	int res=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')
	c=getchar();
	while(c>='0'&&c<='9')
	{
		res=res*10+c-48;
		c=getchar();
	}
	return res;
}//因为题目描述“读入输出量较大，注意使用较快的读入输出方式”，所以使用快读，实际上不用也可以通过本题。 
long long gcd(long long n,long long m)
{
	return (n%m==0)?m:gcd(m,n%m);
}//gcd，不做说明。 
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	long long p;
	exgcd(b,a%b,x,y);
	p=x;
	x=y;
	y=p-(a/b)*y;
	return;
}//exgcd，本题核心代码，在上述内容中已做说明 。 
int t;
int main()
{
	t=read();
	while(t--)
	{
		long long x=0,y=0,a,b,c,g,xin,yin,xax,yax,npa=0,k;//t,x,y,a,b,c,g同先前描述，xin,yin为x,y的最小正整数解,xax,yax为x,y的最大正整数解，npa为正整数解数。 
		a=read();
		b=read();
		c=read();//读入部分。 
		g=gcd(a,b);
		if(c%g!=0)
		printf("-1\n");//判断有无整数解。 
		else
		{
			a/=g;
			b/=g;
			c/=g;
			exgcd(a,b,x,y);
			x*=c;
			y*=c;//求出一组特解。 
			for(int i=1;i<=2;i++)//因为在求解y取得最小正整数解时的k值可能使x的值小于等于0，所以要再求解一遍以求出x的最小正整数解与y的最大正整数解。 
			if(x<=0)
			{
				k=-(x/b)+1;
				x+=k*b;
				y-=k*a;
				xin=x;
				yax=y;
			}//求出x取得最小正整数解时的k值，x的最小正整数解与y的最大正整数解。 
			else if(y<=0)
			{
				k=-(y/a)+1;
				x-=k*b;
				y+=k*a;
				yin=y;
				xax=x;
			}//求出y取得最小正整数解时的k值，x的最大正整数解与y的最小正整数解。 
			if(x>0&&y>0)//判断方程有无正整数解。 
			{
				if(x%b!=0)
				{
					xin=x%b;
					yax=y+a*(x/b);
				}
				else
				{
					xin=x%b+b;
					yax=y+a*(x/b-1);
				}
				if(y%a!=0)
				{
					yin=y%a;
					xax=x+b*(y/a);
				}
				else
				{
					yin=y%a+a;
					xax=x+b*(y/a-1);
				}//用于求解x,y均大于等于0时x,y的最小最大正整数解。 
				npa=(xax-xin)/b+1;//求出正整数解的数量。 
			}
			if(!npa)
			printf("%lld %lld\n",xin,yin);
			else printf("%lld %lld %lld %lld %lld\n",npa,xin,yin,xax,yax);//输出部分。 
		}
	}
	return 0;
}
```

------------

### **对暴力进行优化**
由于以上代码不优化显得又长又慢常数巨大~~而且显得丑~~，所以尝试对暴力进行优化。

运用大眼观察法，可以发现我们能用模运算直接求出x,y的最小正整数解而不用求k值，对于x,y的最大正整数解则可以直接代入二元一次方程求解，即

$$\left\{\begin{aligned}x_{max}=\displaystyle\frac{c-x_{min}}{a}\\y_{max}=\displaystyle\frac{c-y_{min}}{b}\\\end{aligned}\right.$$

**代码：**
```cpp
#include<cstdio>
using namespace std;
int read()
{
	int res=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')
	c=getchar();
	while(c>='0'&&c<='9')
	{
		res=res*10+c-48;
		c=getchar();
	}
	return res;
}
long long gcd(long long n,long long m)
{
	return (n%m==0)?m:gcd(m,n%m);
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	long long p;
	exgcd(b,a%b,x,y);
	p=x;
	x=y;
	y=p-(a/b)*y;
	return;
}
int t;
int main()
{
	t=read();
	while(t--)
	{
		long long x=0,y=0,a,b,c,g,xin,yin,xax,yax,npa=0,k;
		a=read();
		b=read();
		c=read();
		g=gcd(a,b);
		if(c%g!=0)
		printf("-1\n");
		else
		{
			a/=g;
			b/=g;
			c/=g;
			exgcd(a,b,x,y);
			x*=c;
			y*=c;
			xin=x>0&&x%b!=0?x%b:x%b+b;//若x>0且x%b!=0，x的最小正整数解就等于x%b，否则则需要在x%b的基础上加b。 
			yax=(c-xin*a)/b;//求出对应的y的最大正整数解。 
			yin=y>0&&y%a!=0?y%a:y%a+a;
			xax=(c-yin*b)/a;//同理于x。 
			if(xax>0)//判断有无正整数解。 
			npa=(xax-xin)/b+1;//求出正整数解的数量。 
			if(!npa)
			printf("%lld %lld\n",xin,yin);
			else printf("%lld %lld %lld %lld %lld\n",npa,xin,yin,xax,yax);
		}
	}
	return 0;
}
```
再开个O2，交一发上去，发现跑得还挺快，能拿[rank6](https://cdn.luogu.com.cn/upload/pic/1024.png)(主要是因为人少)。
![](https://cdn.luogu.com.cn/upload/image_hosting/44m0pjiv.png?x-oss-process=image/resize,m_lfit,h_1000,w_2500)
最后一点：**记开long long**。

~~为什么我会这么不熟......~~



---

## 作者：Laser_Crystal (赞：17)

$Exgcd$的模板想必大家都很熟悉了，~~不然怎么会来做这道题~~

那么我就来喜闻乐见的讲一讲如何处理细节吧qwq

* 快读和快写。根据出题人的**温 馨 提 示**：“读入输出量较大，注意使用较快的读入输出方式”，所以快读和快写是必要的。快读快写的原理其实就是牺牲了C++标准输入输出的普适性来换取时间。

* 无解的情况只有一种情况，那就是不定方程$ax+by=c$中，$c\nmid\gcd(a,b)$时才无解，只要算出来两个数的最大公约数就OK了。然后我们知道有个函数叫做__gcd（滑稽滑稽

* 正整数指的是大于0的整数。尽管这很简单，，，但是，，，在判断不定方程的最大/小正整数解的时候要加特判

* 处理负数的模数，用$x\% Mod+Mod$（调试的时候一直错，后来才发现这样才能对（捂脸

* 额，，，剩下的就是小学数学了，，，（这说明小学数学挺重要的，，，，，，

Code（嗯，，，没有过度压行，，，

```cpp

#include<bits/stdc++.h> 
using namespace std;
inline long long read()
{
    long long s=0,f=1;        
    char ch=getchar();        
    while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}        
    while(isdigit(ch)) {s=s*10+ch-'0'; ch=getchar(); }        
    return s*f;        
}//快读
inline void write(long long x)        
{        
    if(x<0) {putchar('-');x=-x;}
	if(x>9) write(x/10);        
    putchar(x%10+'0');        
    return;        
}//快写 
inline void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0) x=1,y=0; 
	else  
	{
		exgcd(b,a%b,x,y);
		long long d=x;
		x=y,y=d-a/b*y;
	}
}//Exgcd板子       
int main()
{
	int T=0;
	T=read();
	for(register int i=0;i<T;i++)
	{
		long long a=read(),b=read(),c=read(),x,y,g=__gcd(a,b);
		if(c%g!=0) { printf("-1\n");continue;}//无解
		a/=g,b/=g,c/=g; exgcd(a,b,x,y); x*=c,y*=c;
		if(x<=0)
		{
			long long t;
			t=abs(x)/b; t++; x=x%b+b; y-=t*a;
			if(y<=0) {write(x),printf(" "),write(y%a+a),printf("\n");continue;}
		}//求出来的特解是x<=0时
		if(y<=0)
		{
			long long t;
			t=abs(y)/a; t++; y=y%a+a; x-=t*b;
			if(x<=0) {write(x%b+b),printf(" "),write(y),printf("\n");continue;}
		}//求出来的特解是y<=0时
		long long maxx,minx,maxy,miny;
		long long p,q;
		p=x/b; x%=b; if(!x) x+=b,p--; y+=p*a; minx=x,maxy=y;//计算x的最小值，y的最大值
		q=y/a; y%=a; if(!y) y+=a,q--; x+=q*b; miny=y,maxx=x;//计算x的最大值，y的最小值
		write((maxx-minx)/b+1),printf(" "),write(minx),printf(" "),write(miny),printf(" "),write(maxx),printf(" "),write(maxy),printf("\n");
	}//解的数量就是x或y的最大最小值之差相减然后除掉一个b或者a（这个就是不定方程的通解的性质
	return 0;
}
```

~~快读快写一弄，发现码量就一下子上去了~~

这样子就OK了喵ஐ٩(๑´ᵕ`)۶ஐ

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

## 作者：lndjy (赞：8)

做法：**exgcd+分类讨论**。

### exgcd

扩展欧几里得算法（exgcd）：用于求解形如 $ax+by=\gcd(a,b)$ 的不定方程特解。

exgcd code:
```cpp
int x,y;
void exgcd(int a,int b)
{
	if(b==0)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b);
	int t=x;
	x=y;
	y=t-a/b*y;      
}
```
求出的x，y就是解。

### 分类讨论

1.无解

当c不是 $\gcd(a,b)$ 的倍数时，显然无解。

2.无正整数解

当 $x$ 变化为最小正整数解时，$y$ 最大，若 $y$ 依然小于0，则没有正整数解。

当 $y$ 变化为最小正整数解时，$x$ 最大，若 $x$ 依然小于0，则没有正整数解。

3.有正整数解

$x$ 最小时 $y$ 最大，反之亦然同理。

解的个数是最大 $x$ 最小 $x$ 的差除以模数 $b$ 再加上1。

**注意：要开longlong**，我这里 define int long long 了。

AC代码：
```cpp
#include<iostream>
#include<cstdio>
#define int long long 
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
void write(int i)
{
	if(i<0)
	{
		putchar('-');
		i=-i;
	}
	if(i/10) write(i/10);
	putchar('0'+(i%10)); 
}
int x,y;
void exgcd(int a,int b)
{
	if(b==0)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b);
	int t=x;
	x=y;
	y=t-a/b*y;      
}
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
signed main()
{
	int T=read();
	while(T--)
	{
		int a=read(),b=read(),c=read(),d=gcd(a,b),t;
		if(c%d!=0)//无解。
		{
			write(-1);
			putchar('\n');
			continue;
		}
		a/=d;b/=d;c/=d;
		exgcd(a,b);
		x*=c;y*=c;
		if(x<=0)
		{
			int t=-x/b+1;
			x=x%b+b;
			y=y-t*a;
			if(y<=0)//无正整数解
			{
				write(x);
				putchar(' ');
				write((y%a)+a);
				putchar('\n');
				continue;
			}
		}
		if(y<=0)
		{
			int t=-y/a+1;
			y=y%a+a;
			x=x-t*b;
			if(x<=0)//同上
			{
				write((x%b)+b);
				putchar(' ');
				write(y);
				putchar('\n');
				continue;
			}			
		}
		t=x/b;//有正整数解
		x%=b;
		if(x==0)
		{
			x+=b;
			t--;
		}
		y+=t*a;
		int minx=x,maxy=y;//最小x最大y
		t=y/a;
		y%=a;
		if(y==0)
		{
			y+=a;
			t--;
		}
		x+=t*b;//现在x，y是最大x最小y
		write((x-minx)/b+1);//解的个数，最大减去最小
		putchar(' ');
		write(minx);
		putchar(' ');
		write(y);
		putchar(' ');
		write(x);
		putchar(' ');
		write(maxy);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：phigy (赞：7)

**11.24:修改了:**

**两个$\pm$应该改为一个$\pm$另一个$\mp$,因为其符号是相反的**

**感谢** @ [A_M](https://www.luogu.org/user/260738)

## 如何求出一组解

一下给出思路：

原方程$ax+by=c$

我们对它整体对$b$取模

$ax\,\equiv\, c ( mod\,b)$

这样就变成熟悉的一道题

[ 同余方程](https://www.luogu.org/problem/P1082)

只需解$ax\,\equiv1(mod\,b)$

再$x*=c$即可

----

## 关于无解
- 当 $a$ 是 $b$ 的倍数时，$ax \mod b = 0$。

	- 如果 $c$ 也是 $b$ 的倍数，则 $c \mod b = 0$，所以 $ax \equiv c \pmod b$恒成立（有无数解）。

	- 如果 $c$ 不是 $b$ 的倍数，则 $c\mod b ≠ 0$，故上面这个方程不可能成立。

- 若 a 不是 b 的倍数，那么因为模数是一个质数，所以 a 与 b 互质，那么 $bx_1 \equiv 1 \pmod p$一定有解,故一定有符合条件的 $x = c× x_1$

**以上来自某题解，选编时有改动**（

----
## 关于解的数量与最小，大值

如果我们解出一组解：

$ax_{1}+by_1=c$

根据~~大眼观察法~~

可得：

$a(x_1\pm bk)+b(y_1\mp ak)=c$

也是另一堆解，只是有些为负

于是就能顺利解决了

-----


### 到此大概的思路讲完了，谢谢管理员的审核

---

## 作者：thoq (赞：5)

扩欧，注意分类讨论和细节处理

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
ll gcd(ll a,ll b)
{
	if(!b)return a;
	return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	ll t=x;
	x=y,y=t-a/b*y;
}//扩欧模板
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ll a,b,c,x,y,t;
		scanf("%lld%lld%lld",&a,&b,&c);
		ll d=gcd(a,b);
		if(c%d!=0)
		{
			printf("-1\n");
			continue;
		}//方程有整数解等价于gcd(a,b)|c
		a/=d,b/=d,c/=d;//同除公约数，不然遍历通解会有遗漏
		exgcd(a,b,x,y);//得到ax+by=1的一组解
		x*=c,y*=c;//得到ax+by=c的一组解
		if(x<=0)
		{
			t=abs(x)/b+1;
			x=x%b+b;//负数取模较特殊
			y-=t*a;
			if(y<=0)//当x变化为最小正整数解时，y最大，若y依然小于0，则没有正整数解
			{
				printf("%lld %lld\n",x,y%a+a);
				continue;
			}
		}
		if(y<=0)//这几行与上几行同理
		{
			t=abs(y)/a+1;
			y=y%a+a;
			x-=t*b;
			if(x<=0)
			{
				printf("%lld %lld\n",x%b+b,y);
				continue;
			}
		}//此时，x>0,y>0
		t=x/b;
		x-=t*b;//等价写法： x%=b
		if(!x)x+=b,t--;//细节，特判
		y+=t*a;//此时，x最小，对应的，y最大
		ll xmin=x,ymax=y;
		t=y/a;
		y-=t*a;
		if(!y)y+=a,t--;
		x+=t*b;
		ll ymin=y,xmax=x;//这几行与前几行同理
		printf("%lld %lld %lld %lld %lld\n",(xmax-xmin)/b+1,xmin,ymin,xmax,ymax);
	}
	return 0;
}
```


---

