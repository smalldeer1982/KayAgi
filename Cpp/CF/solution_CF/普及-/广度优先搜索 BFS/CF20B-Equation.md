# Equation

## 题目描述

### 题目大意

给定 $A, B, C$，求方程 $Ax^2+Bx+C=0$ 的解的个数，如果有无穷个解，则输出 `-1`。

## 样例 #1

### 输入

```
1 -5 6
```

### 输出

```
2
2.0000000000
3.0000000000```

# 题解

## 作者：云浅知处 (赞：21)

本蒟蒻是一枚初一的MOer，看到这道题后开心地笑了。
***
[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-cf20b)
***
下面开始讲题：

$\text{step1}$: 一元二次方程的一些基本知识。

基础概念：形如 $ax^2+bx+c=0(a\ne0)$ 的等式叫做一元二次方程。

下面推导一元二次方程的求根公式及判别式。

将等式两边同时除以 $a$ （由于$a\ne0$，所以这是可行的)，得

$$x^2+\dfrac{b}{a}\cdot x+\dfrac{c}{a}=0$$

移项，得

$$x^2+\dfrac{b}{a}\cdot x=-\dfrac{c}{a}$$

等式两边同时加上$\dfrac{b^2}{4a^2}$，得

$$x^2+\dfrac{b}{a}\cdot x+\dfrac{b^2}{4a^2}=-\dfrac{c}{a}+\dfrac{b^2}{4a^2}$$

注意到：$x^2+\dfrac{b}{a}\cdot x+\dfrac{b^2}{4a^2}=(x+\dfrac{b}{2a})^2$

故原方程化为

$$(x+\dfrac{b}{2a})^2=-\dfrac{c}{a}+\dfrac{b^2}{4a^2}$$

化简得

$$(x+\dfrac{b}{2a})^2=\dfrac{b^2-4ac}{4a^2}$$

即

$$x+\dfrac{b}{2a}=\pm\sqrt{\dfrac{b^2-4ac}{4a^2}}$$

化简得

$$x+\dfrac{b}{2a}=\pm\dfrac{\sqrt{b^2-4ac}}{2a}$$

移项，得

$$x=\pm\dfrac{\sqrt{b^2-4ac}-b}{2a}$$

一般写为

$$x=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}$$

这就是一元二次方程的求根公式。

此时，根据平方根的定义，得：

当 $b^2-4ac\geqslant0$ 时，$\sqrt{b^2-4ac}$ 是实数，即原方程有实数根。

反之，当$b^2-4ac<0$ 时，$\sqrt{b^2-4ac}$ 无意义，即原方程无实数根。

进一步说：

当 $b^2-4ac>0$ 时，原方程有两个实数根，分别为：

$$x_1=\dfrac{-b+\sqrt{b^2-4ac}}{2a},x_2=\dfrac{-b-\sqrt{b^2-4ac}}{2a}.$$

当 $b^2-4ac=0$ 时，原方程有两个相同的实数根（称为重根），均为 $-\dfrac{b}{2a}.$

当 $b^2-4ac<0$ 时，原方程无实数根。

一般地，我们将 $b^2-4ac$ 称为一元二次方程的判别式，记作$\Delta.$
***
$\text{step2}$：做题

需要注意的是：**这道题可没说输入的一定是一元二次方程啊！$a=0$ 时它不是一元二次方程！**

所以，我们要**分类讨论**。

当$a=0$时，有以下三种情况：

$1.a=0,b=0,c=0$

显然，此时原方程有无数解，输出`-1`

$2.a=0,b=0,c\ne0$

原方程化为 $0x^2+0x+c=0$，即 $c=0$，这与 $c\ne0$ 矛盾。

故此时原方程无解，输出`0`。

$3.a=0,b\ne0$（此时 $c$ 的大小已经无所谓了）

原方程化为一元一次方程 $bx+c=0$。

解得 $x=-\dfrac{c}{b}$。

当$a\ne0$时，就是我们之前讲过的一元二次方程了。按照判别式与求根公式正常输出即可。
***
$\text{step3}$：上代码
```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;

int main(){
	long double a,b,c,delta,x1,x2;
	cin>>a>>b>>c;


	if(a==0&&b==0&&c==0){//如果a,b,c都等于0
		cout<<-1;//有无数解，输出-1
		return 0;//并结束程序
	}
	if(a==0&&b==0&&c!=0){//如果a,b等于0，c不等于0
		cout<<0;//无解，输出0
		return 0;//并结束程序
	}
	if(a==0&&b!=0){//如果a=0且b≠0
		cout<<"1\n"<<fixed<<setprecision(10)<<-c/b;//这里的fixed<<setpricision()是cout中自带的控制输出的函数，其作用是输出小数点后n位。
		return 0;
	}
	delta=b*b-4*a*c;//如果此时程序仍未结束，那么此方程就是个一元二次方程。
	if(delta<0){
		cout<<0;//无解，输出0
		return 0;//并结束程序。
	}
	if(delta==0){
		cout<<"1\n"<<fixed<<setprecision(10)<<-b/(2*a);
		return 0;
	}
	if(delta>0){
		cout<<"2\n";
		x1=(-b+sqrt(b*b-4*a*c))/(2*a);//利用求根公式求x1
		x2=(-b-sqrt(b*b-4*a*c))/(2*a);//利用求根公式求x2
		cout<<fixed<<setprecision(10)<<min(x1,x2)<<endl<<fixed<<setprecision(10)<<max(x1,x2);//注意此处要按从小到大的顺序输出，题中说的有。
		return 0;
	}

	
	return 0;//完结撒花
}
```
***
虽然这篇题解写得不一定很好，但您看得这么认真，不点个赞再走么？

---

## 作者：cherubim (赞：7)

### 看其他题解都是套求根公式，本蒟蒻写了个配方法

众所周知，解一元二次方程的方法有 **求根公式法**，**配方法**，因式分解法，直接开根法。

其中只有**求根公式法**和**配方法**是万能的，任何一个一元二次方程都可以根据这两个方法来求解。

其他题解都是公式法，那我就来说一说配方法的方法。

（因为配方法需要用到开根法，所以先解释一下）

开根法其实很简单，大概是就像是  $x^2$=2  然后解出 x=$\ \sqrt{2} $ 这样的形式。


但是很显然，很多方程并不可能都像这种美好的形式（请允许我使用这个形容词）那我们就得要想办法去将题目给的方程变成我们想要的那种形式，这时候，就要请出我们的**配方法**了。

**配方法**，顾名思义，就是想办法把一个长得看起来乱七八糟的一元二次方程弄成一个好康的可以直接开根的方程的形式。


------------

### 数学方法

下面看一看数学方法怎么实现（学过一元二次方程的同学请跳过这里）

我们的数学老师曾经说过配方的口诀：在二次项系数为1的情况下，配出一次项系数的一半。

（通俗一点就是先把方程两边同除a，让二次项系数为一，好配一些，这里就不具体展现证明过程，有兴趣的可以自行百度或询问数学老师）

那么举例，随便给出一个一元二次方程为  $x^2+3x=-2$ 

  
  
 我们一般认为一元二次方程的一般形式为  $ax^2+bx+c=0$
 
 所以整理上面这个方程为  $x^2+3x+2=0$
 
 (有人说这时候就可以因式分解了，但是因为这种方法不是万能的并且用代码不好实现，所以继续选择用配方法做)
 
 这时，我们可以看下这个方程的具体形式，很明显，可以看出对一次项配方有  $x^2+3x+2.25$  可以转化为  $(x+1.5)^2$  的形式，可以开方，所以，我们把原式整理为:
 
  $x^2+3x+2.25-2.25+2=0$
   
  然后接着整理：
  
  $(x+1.5)^2=0.25$
  
  接下来，我们就可以愉快的开方辣！
  
  然后得到  $x1=-1$ , $x2=-2$ 。
  


------------


### 代码重点

这道题真正坑的是某些特殊情况！！！！

（特别是根为0可能输出为-0，调死我了）
 
 具体的情况在代码中注释了，这里就不详细讲了。
 
 下面是喜闻乐见的代码环节。
 
 
 ~~顺便再求个赞啊QAQ~~
 
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}//快读
double A,B,C;
double b,c,tc,add,r,x_1,x_2;
signed main()
{
	cin>>A>>B>>C;
	
	if(A==0&&B==0&&C==0){//特判1：三个系数都为0的情况下， 输出-1
		printf("%d\n",-1);
		return 0;
	}
	else if(A==0&&B==0&&C!=0){//特判2：a=0，b=0但c不等于0，肯定是无解的，相当于只有系数，输出0 
		printf("%d\n",0);
		return 0;
	}
	else if(A==0&&B!=0){//特判3：如果a=0且b≠0，题目的一元二次方程转化为求一个一元一次方程的方程，直接移项输出答案 
		double ans=-C/B;
		if(ans==-0.0000000000) ans=0.0000000000;//这里要特判ans==-0的时候，直接-c/b有可能答案为-0，转化为0 
		printf("%d\n%.10lf\n",1,ans);
		return 0;
	}
	else if(A==0&&C==0){//特判4：方程为 bx=0  可以一眼看出答案为0，输出 
		printf("1\n0.0000000000");
		return 0;	
	}
	else if(A!=0&&B==0&&C==0){//特判5：方程为 ax^2=0  可以一眼看出答案为0，输出 
		printf("1\n0.0000000000");
		return 0;	
	}
	double derta=B*B-4*A*C;//如果不为特殊情况，则计算derta来判别有几个答案 
	if(derta>0){//derta>0时有两种 
		b=B/A;
		c=C/A;//化系数为1 
		tc=b/2;//二次项系数的一半 
		add=tc*tc;//一半的平方（套口诀 
		r=-c+add;// ( x + tc ) ^ 2 = -c + add  此时的方程可以转化为这样 
		x_1=sqrt(r)-tc;
		x_2=-sqrt(r)-tc;//开始计算两个根，开方 
		if(x_1<=x_2)
			printf("%d\n%.10lf\n%.10lf\n",2,x_1,x_2);
		else if(x_1>x_2)
			printf("%d\n%.10lf\n%.10lf\n",2,x_2,x_1);//这题要按从小到大的顺序输出 
	}
	else if(derta==0){//如果有一个根的情况，计算与两个根时的计算一模一样，输出不同而已 
		b=B/A;
		c=C/A;
		tc=b/2;
		add=tc*tc;
		r=-c+add;// ( x + tc ) ^ 2 = -c + add
		x_1=sqrt(r)-tc;
		x_2=-sqrt(r)-tc;
		if(x_1==-0.0000000000) printf("0.0000000000"); //特判-0的情况 
		else printf("%d\n%.10lf",1,x_1);
	}
	else if(derta<0) printf("%d\n",0);//如果小于0，直接无解，输出0 
	return 0;
}

```
如果有疑问，欢迎私信~

~~第一篇题解求管理给过QAQ~~
   
 


---

## 作者：小恐 (赞：2)

~~一看到这道题，哇！本初一蒟蒻刚学二次方程，结果高高兴兴交了个代码，$a=0$时wa了，这也太坑了吧！~~

第一种情况：$a=0$、$b=0$、$c=0$，明显无数个解，输出-1。

第二种情况：$a=0$、$b=0$、$c\mathrlap{\,/}{=}0$，明显无解，输出0

第三种情况：$a=0$、$b\mathrlap{\,/}{=}0$，一个解，$-\dfrac c b$

第四种情况：$a\mathrlap{\,/}{=}0$，就是正常二次方程了，就是看$\Delta$的情况，如果小于0，则无解，如果等于0，则唯一解，如果大于0，则2个解。解为$\dfrac {-b\pm\sqrt {b^2-4 \times a \times c}} {2 \times a}$。

上代码：
```cpp
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
int main()
{
	long long a,b,c;
	scanf("%lld%lld%lld",&a,&b,&c);
	if(a==0&&b==0&&c==0)
		printf("%d",-1);
	else if(a==0&&b==0&&c!=0)
		printf("%d",0);
	else if(a==0&&b!=0)
		printf("1\n%.10lf",-double(c)/b);
	else
	{
		if(b*b-4*a*c<0)
			printf("0");
		else if(b*b-4*a*c==0)
		{
			printf("1\n");
			double x=double(-b)/2/a;
			printf("%.10lf",x);
		}
		else
		{
			printf("2\n");
			double x1=double(-b+sqrt(b*b-4*a*c))/2/a;
			double x2=double(-b-sqrt(b*b-4*a*c))/2/a;
			double t;
			if(x1>x2)
				t=x1,x1=x2,x2=t;
			printf("%.10lf\n%.10lf",x1,x2);
		}
	}
	return 0;
}
```

珍爱生命，远离抄袭！

PS：2020-04-17：发现一些小错，现已更正。

---

## 作者：Insouciant21 (赞：1)

一看题，解一元二次方程直接套求根公式 $x=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}$

但是这题有些细节：

- $a,b,c$ 可能为 $0$ 。

$a=0$ 且 $b\neq0$ 时，变成一元一次方程， $x=-\dfrac{c}{b}$ 。

$a=b=0$ 但 $c!=0$ 时，$ax^2+bx+c=0$ 变为 $c=0$ 与 $c!=0$ 不符，故无解。

$a=b=c=0$ 时，总有 $ax^2+bx+c=0$ ，故有无数解。

剩下的按照接二次方程的步骤解：

计算判别式 $\Delta=b^2-4ac$ ，注意$-10^5\leq a,b,c\leq10^5$，即可能出现 $b^2,4ac>2^{31}-1$ ，所以需要使用 `long long`

当 $\Delta>0$ 时，方程有两个不等的实数根。

当 $\Delta=0$ 时，方程有两个相等的实数根。

当 $\Delta<0$ 时，方程无实数根。

再代入求根公式中计算解即可（ 注意格式，至少需要 $5$ 位小数，且要从小到大输出 ）

AC 代码

```
#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main() {
    scanf("%d %d %d", &a, &b, &c);
    if (a != 0) {
        long long delta = 1LL * b * b - 4LL * a * c;
        if (delta > 0) {
            puts("2");
            double ans1 = (-b + sqrt(delta)) / 2.0 / a;
            double ans2 = (-b - sqrt(delta)) / 2.0 / a;
            if (ans1 > ans2)
                swap(ans1, ans2);
            printf("%.6lf\n%.6lf\n", ans1, ans2);
        }
        else if (delta == 0) {
            puts("1");
            double ans = (-b + sqrt(delta)) / 2.0 / a;
            printf("%.6lf", ans);
        }
        else {
            puts("0");
        }
    }
    else {
        if (b == 0 && c == 0)
            puts("-1");
        else if (b == 0 && c != 0)
            puts("0");
        else if (b != 0) {
            puts("1");
            printf("%.6lf", -c / double(b));
        }
    }
    return 0;
}
```



---

## 作者：WanderingTrader (赞：1)

数学好题
### 题目分析
题目说了，$a,b,c$都可能为0，所以要分四种情况讨论：
1. $a\neq0$  
此时$ax^2+bx+c=0$是一个一元二次方程，我们可以对其进行配方：  
$$ax^2+bx=-c\\x^2+\dfrac b ax+\left(\dfrac b{2a}\right)^2=-\dfrac c a+\left(\dfrac{b}{2a}\right)^2\\\left(x+\dfrac b{2a}\right)^2=\dfrac{b^2-4ac}{4a^2}\\$$  
因为
$$4a^2\ge0$$
所以 $b^2-4ac$ 对方程是否有实数解起到直观重要的作用，我们给它一个字母：$\Delta$  
即  
$$\Delta=b^2-4ac$$  
它也称为 **一元二次方程的判别式**。   
如果 $\Delta>0$，则
$$x+\dfrac b{2a}=\pm\dfrac{b^2-4ac}{4a^2}$$  
移项可得
$$x_1=\dfrac{-b+\sqrt{b^2-4ac}}{2a},x_2=\dfrac{-b-\sqrt{b^2-4ac}}{2a}$$  
如果 $\Delta<0$，那么方程无解  
如果 $\Delta=0$，那么方程有唯一解 $x=-\dfrac{b}{2a}$   
2. $a=0$且$b\ne0$  
方程化为 $bx+c=0$ 移项得 $x=-\dfrac c b$  
3. $a=0,b=0$ 且 $c\ne0$  
那么$c=0$，此时无解  
4. $a=0,b=0,c=0$  
那么$0=0$，方程有无数组解  
### 代码
把上述过程模拟一遍即可：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	ll a,b,c;
	scanf("%lld%lld%lld",&a,&b,&c);
	if(a)
	{
		ll delta = b*b - 4*a*c;
		if(delta < 0) printf("0\n");
		else if(delta)
		{
			double x1 = (-b+sqrt(delta))/(2*a);
			double x2 = (-b-sqrt(delta))/(2*a);
			if(x1 > x2) swap(x1,x2);
			printf("2\n%.5lf\n%.5lf\n",x1,x2);
		}
		else 
		{
			double x1 = (-b)/(2*a);
			printf("1\n%.5lf\n",x1);
		}
	}
	else if(b)
	{
		double ans = -1.0*c/b;
		printf("1\n%.5lf\n",ans);
	}
	else if(c) printf("0\n");
	else printf("-1\n");
	return 0;
}
```
注意由于数据的绝对值可以达到 $10^5$，所以中间某些部分（比如 $\Delta$ ）会爆int，要用longlong。  
$$\texttt{The\ End.}$$

---

## 作者：槑小杨 (赞：1)

一共4种情况：

1. $a=0$且$b=0$且$c=0$，方程有无数解。

2. $\Delta<0$ 方程无实数解。（由于此题没有延申至复数解，可以把无解和无实数解看作相同的）

3. $\Delta=0$ 方程有唯一解。

4. $\Delta>0$ 方程有正负两解。

所以超简洁代码奉上。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    double a,b,c,d,e,x1,x2;
    cin>>a;
    cin>>b;
    cin>>c;
    d=b*b-4*a*c;
    if(a==0&&b==0&&c==0)
    {
    	cout<<-1<<endl;
    }
    /*if(a==0&&b==0&&c!=0)
      {
         cout<<"0"<<endl;
      }*/
    if(d<0)
    {
        cout<<"0"<<endl;
    }
    if(d==0)
    {
        x1=x2=(-b)/(2*a);
        cout<<"1"<<endl; 
        printf("%.10lf",x1);
    }
    if(d>0)
    {
        e=sqrt(d);	
        x1=(-b+e)/(2*a);
        x2=(-b-e)/(2*a);
        cout<<"2"<<endl; 
        printf("%.10lf %.10lf",x1,x2);      
    }
    return 0;
}
```
稍微控制一下输出即可。

个人感觉码风比较舒畅，思路清晰，~~请管理通过qwq~~。


---

## 作者：Fengxiang008 (赞：1)

# 解题重要公式 + 思路
## 一元二次方程的重要公式：
### 根的数量的
判别式
$\bigtriangleup = \sqrt{b^2-4ac}$ 
### 求根公式：
$x{1}=\dfrac{-b+\sqrt{b^2-4ac}}{2a}$

$x{2}=\dfrac{-b-\sqrt{b^2-4ac}}{2a}$
### 总结归纳
当 $ b^2-4ac > 0 $时，方程有两个不同的跟：     
$x{1}=\dfrac{-b+\sqrt{b^2-4ac}}{2a}$

$x{2}=\dfrac{-b-\sqrt{b^2-4ac}}{2a}$


当 $ b^2-4ac = 0 $时，方程有两个相同的跟：
$x{1}=x{2}=\dfrac{-b}{2a}$

当 $ b^2-4ac = 0 $时，方程无实数跟
## 注意：
题目似乎没说 $a\ne0$ 一定成立
### 所以
此题只需要分类讨论   
当 $a=0$ 时，原方程化为： $bx+c=0 \Rightarrow x=-\dfrac{c}{b}$ 。  
当 $a\ne0$ 时，直接套一元二次方程求根公式即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long double a,b,c,check,x[3]; 
	cin>>a>>b>>c;
	if(a==0&&b==0&&c==0)
	{
		cout<<-1<<endl;//无限解的情况 
		return 0;//随后结束程序
	}
	if(a==0&&b==0&&c!=0)
	{
		cout<<0<<endl;//无解的情况 
		return 0;//随后结束程序
	}
	if(a==0&&b!=0)//如果a=0且b≠0
	{
		printf("1\n%.10lf",-c/b);//只有一个跟的情况 
		return 0;//随后结束程序
	}
	//若此时程序仍未结束 
	//则此方程为一元二次方程
	check=b*b-4*a*c;//判别式 
	if(check<0)//判别式<0 
	{
		cout<<0<<endl;//无解，输出0
		return 0;//随后结束程序
	}
	if(check==0)//判别式=0 
	{
		printf("1\n%.10lf",-b/(2*a)*1.0);//一个根 
		return 0;
	}
	if(check>0)//判别式>0 
	{
		x[1]=(-b+sqrt(b*b-4*a*c))/(2*a)*1.0;//利用求根公式求x[1]
		x[2]=(-b-sqrt(b*b-4*a*c))/(2*a)*1.0;//利用求根公式求x[2]
		//两个根的情况 
		printf("2\n%.10lf\n%.10lf",min(x[1],x[2]),max(x[1],x[2]));//注意要按从小到大输出
		return 0;
	}
	return 0;
}
```


---

## 作者：Need_No_Name (赞：0)

# CF20B 题解
## 题意

给定一个二元一次方程组 $ax^2 + bx + c = 0$ ，现在给定 $a$ , $b$ , $c$ ，求 $x$ 的值

特别说明：当 $x$ 无数解时，输出 $-1$ ，无解时，输出 $0$ 。

# 思路

这道题可以直接套二元一次求根公式。

公式： $\frac{-b±\sqrt{b^2 - 4ac}}{2a}$

当你兴高采烈地套上去，提交时，你会发现，你很快乐的```WA``` 了！！！

为什么呢，这道题需要考虑特殊情况

**1**.当 $\Delta$ (也就是 $\sqrt{b^2 - 4ac}$) 小于等于 $0$ 时，输出‘0’

**2**.当 $\Delta = 0$ 时候，解只有一个。不过，当 $a = 0, b = 0, c = 0$ 的时候，有无数种解

**3**.当 $\Delta > 0$ 时，有两种解，当然，也可能只有一种，下面进行讨论
	
   **A:** 当 $a = 0, b ≠ 0, c≠0$ 时，按照二元一次方程考虑，输出 $\frac{-c}{b}$
   
   **B:** 当 $a = 0, b ≠ 0,c = 0$ 时，因为 $2a$ 为 $0$ ，所以直接套会出大问题
   
   **C:** 当 $a = 0, b = 0, c ≠ 0$ 时，无解
   
   **D:** 剩余的情况，便可以直接套公式变可以了。
   
## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
double a, b, c;
signed main()
{
	cin >> a >> b >> c;
	if(a == 0 && b == 0 && c == 0)
	{
		cout << -1 << endl;
		return 0;
	}
	if(a == 0 && b != 0 && c != 0)
	{
		cout << 1 << endl;
		printf("%.10lf\n", (-1 * c) / b);
		return 0;
	}
	else if(a == 0 && b != 0 && c == 0)
	{
		cout << 1 << endl;
		cout << 0 <<endl;
		return 0;
	}
	else if(a == 0 && b == 0 && c != 0)
	{
		cout << 0 <<endl;
		return 0; 
	}
	double delta = b * b - 4 * a * c;
	if(delta < 0)
	{
		cout << 0 << endl;
		return 0;
	}
	else if(delta == 0) cout << 1 << endl;
	else cout << 2 << endl;
	double xx = (-1.0000000000 * b + sqrt(delta)) / (2.0000000000 * a);
	double xxx = (-1.0000000000 * b - sqrt(delta)) / (2.0000000000 * a);
	if(delta == 0)
	{
		printf("%.10lf\n", xx);
		return 0;
	}
	printf("%.10lf\n", min(xx, xxx));
	printf("%.10lf\n", max(xx, xxx));
	return 0;
}
```


---

## 作者：zsyyyy (赞：0)

# CF20B 数学

## 题意

给出一个形如 $Ax^2+Bx+C=0$ 的式子，问有多少个解。

## 思路

- 1.$a=0$ 

  1.1 $b≠0$：该式子是一元一次方程，有一个解：$-\frac{c}{b}$
  
  1.2 $b=0$ 且 $c=0$：有无限个解
  
  1.3 $b=0$ 且 $c≠0$：无解

- 2.$a!=0$ 也就是该式子是一元二次方程

  2.1 $b^2-4ac<0$：无解

  2.2 $b^2-4ac=0$：有一个解：$-\frac{b}{2a}$

  2.3 $b^2-4ac>0$：有两个解：$\frac{-b±\sqrt{b^2-4ac}}{2a}$



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
double a,b,c,ans,ans1,ans2;
signed main()
{
	cin>>a>>b>>c;
	if(a==0&&b!=0)
	{
		puts("1");
		ans=(-1*c)/b;
		printf("%.10lf",ans);
		return 0;
	}
	if((b*b-(4*a*c)<0)||(a==0&&b==0&&c!=0))
	{
		puts("0");
		return 0;
	}
	if(a==0&&b==0&&c==0)
	{
		puts("-1");
		return 0;
	}
	if(b*b-(4*a*c)==0)
	{
		ans=(-1*b)/(2*a);
		puts("1");
		printf("%.10lf",ans);
		return 0;
	}
	ans1=((-1*b)-sqrt((b*b)-(4*a*c)))/(2*a);
	ans2=((-1*b)+sqrt((b*b)-(4*a*c)))/(2*a);
	puts("2");
	if(ans1<ans2)  printf("%.10lf\n%.10lf",ans1,ans2);
	else  printf("%.10lf\n%.10lf",ans2,ans1);
	return 0;
}
```


---

## 作者：_lxy_ (赞：0)

### 题意

求解形如 $ax^2+bx+c=0$ 的方程。

### 分析

通过读题发现，可以分成几种情况：

1. $a=0,b=0,c=0$ 

   此时方程有无数个解。

2. $a=0,b=0,c \neq 0$

   此时方程无解。

3. $a=0,b \neq 0$

   此时方程有唯一解 $-\frac{c}{b}$。

4. $a \neq 0,\Delta>0$

   根据一元二次方程求根公式，此时方程有不相等的两个解 $x=\frac{-b \pm \sqrt{b^2-4ac}}{2a}$，注意从小到大输出。

5. $a \neq 0,\Delta=0$

   此时方程有两个相等的解 $x=\frac{-b + \sqrt{b^2-4ac}}{2a}$。

6. $a \neq 0,\Delta<0$

   此时方程无解。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &IEE,T2&... ls)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);IEE=x;qread(ls...);
}
long long a,b,c;
int main()
{
	qread(a,b,c);
	double d=b*b-4*a*c;
	if(a==0)
	{
		if(b==0)
		{
			if(c==0) printf("-1\n");
			else printf("0\n");
		}
		else printf("1\n%.10lf\n",-c/1.0/b);
	}
	else
	{
		if(d>0) printf("2\n%.10lf\n%.10lf\n",min((-b-sqrt(d))/2.0/a,(-b+sqrt(d))/2.0/a),max((-b-sqrt(d))/2.0/a,(-b+sqrt(d))/2.0/a));
		else if(fabs(d)<=1e-8) printf("1\n%.10lf\n",(-b+sqrt(d))/2.0/a);
		else printf("0\n");	
	}
	return 0;
}
```



---

## 作者：猜一猜我是谁 (赞：0)

# 题目大意
给一个形如 $ax^2+bx+c$ 的方程，求解的数量与解的值。
# 分析
一些一元二次方程的必备知识。

定义：形如 $ax^2+bx+c=0$ 的方程，其中 $a\ne0$ 。这样的方程叫一元二次方程。

下面来演示一元二次方程的推导过程。

移项，得
$$ax^2+bx=-c$$
二次项系数化为 $1$，得
$$x^2+\frac{b}{a}x=-\frac{c}{a}$$
两边加 $(\dfrac{b}{2a})^2$ （即配方法），得
$$x^2+\frac{b}{a}x+(\frac{b}{2a})^2=-\frac{c}{a}+(\frac{b}{2a})^2$$
左边写成完全平方形式，右边通分，即
$$(x+\frac{b}{2a})^2=\frac{b^2-4ac}{4a^2}$$
而式子 $b^2-4ac$ 的值有三种情况：

(1) $b^2-4ac>0$

此时
$$x+\frac{b}{2a}=\pm\frac{\sqrt{b^2-4ac}}{2a}$$
移项，得
$$x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$$
所以此时方程有两个不相同的实数范围内的解
$$x_1=\frac{-b+\sqrt{b^2-4ac}}{2a},x_2=\frac{-b-\sqrt{b^2-4ac}}{2a}$$
(2) $b^2-4ac=0$

此时 $\dfrac{b^2-4ac}{4a^2}=0$ ，所以方程有一个实数范围内的解
$$x=-\frac{b}{2a}$$
(3) $b^2-4ac<0$

此时 $(x+\dfrac{b}{2a})^2<0$，所以方程无实数范围内的解。
## 解题
输入数据不一定是一元二次方程，因为没有保证 $a\ne0$ 。

所以我们要加入特判。

$1.a=0,b=0,c=0$

此时方程有无数解。

$2.a=0,b=0,c\ne0$

此时方程无解。

$3.a=0,b\ne0$

此时为一元一次方程，解为 $\dfrac{-c}{b}$ 。

$4.a=0,c=0$

此时方程的解为 $0$ 。

$5.a\ne0,b=0,c=0$

此时方程为 $ax^2=0$ ，解得 $x=0$ 。

剩下的就是一元二次方程了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,x1,x2;
void print(double u){  //输出
    if(u==-0.0000000000) u=0.0000000000;
    printf("%.10lf\n",u);
}
int main(){
    cin>>a>>b>>c;
    if(!a&&!b&&!c) cout<<-1;
    else if(!a&&!b&&c) cout<<0;
    else if(!a&&b){
        x1=(-c)/b;
        cout<<"1\n";
        print(x1);
    }
    else if(!a&&!c) cout<<"1\n",print(0);
    else if(a&&!b&&!c) cout<<"1\n",print(0);
    else{
        double d=b*b-4*a*c;
        if(d<0) cout<<0;
        else if(d==0) cout<<"1\n",print(-b/(2*a));
        else{
            x1=(-b+sqrt(d))/(2*a);
            x2=(-b-sqrt(d))/(2*a);
            if(x2<x1) swap(x1,x2);
            cout<<"2\n",print(x1),print(x2);
        }
    }
}
```


---

## 作者：Eason_AC (赞：0)

## Content
解方程 $ax^2+bx+c=0$。

**数据范围：$-10^5\leqslant a,b,c\leqslant 10^5$。**
## Solution
很明显上求根公式。

先来给大家推推求根公式吧。

$$\begin{aligned}ax^2+bx+c&=0\color{Red}~(a\neq0)\\ax^2+bx&=-c&(1)\\x^2+\dfrac bax&=-\dfrac ca&(2)\\x^2+\dfrac bax+\left(\dfrac{b}{2a}\right)^2&=-\dfrac ca+\left(\dfrac{b}{2a}\right)^2&(3)\\\left(x+\dfrac{b}{2a}\right)^2&=\dfrac{b^2-4ac}{4a^2}&(4)\\x+\dfrac b{2a}&=\pm\sqrt{\dfrac{b^2-4ac}{4a^2}}=\pm\dfrac{\sqrt{b^2-4ac}}{2a}&(5)\\x&=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}&(6)\end{aligned}$$

（1）将常数项 $c$ 移到右边。  
（2）将方程两边同时除以 $a$。  
（3）配方，由于二次项系数是 $1$，因此很明显常数项是一次项的一半的平方。为了使方程两边相等，右边也要加上一个常数项。  
（4）将等号左边写成 $a^2$ 的形式，同时将等号右边通分。  
（5）开根号，注意右边的结果正负都可以（负负得正）。  
（6）将等号左边的常数项移到右边。

这样就得到了求根公式了：

$$\boxed{x_{1,2}=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}}$$

没错，$x_1,x_2$ 就表示成原方程的两个解。

然而，看到方程右边的条件了没有？$a\neq 0$。

而题目中并没有保证 $a\neq 0$（事实上有 $a=0$ 的数据）。

那么就需要分类讨论了：

一、如果 $a=0$。分三类。

1. $b,c=0$。那么原方程就变成了 $0=0$，显然有无数多个解。
2. $b=0,c\neq 0$。那么原方程就变成了 $c=0$，显然无解。
3. $b\neq 0$，那么原方程就变成了 $bx+c=0$，显然该方程的解只有一个，即 $-\dfrac cb$。

二、如果 $a\neq 0$，那么这个方程就是一元二次方程了。依照 $\Delta$ 分类讨论。

首先得讲讲 $\Delta$，其实就是上面求根公式中的 $b^2-4ac$。为什么要单独拿出这个式子呢？因为这和一元二次方程的解的情况有着密不可分的关系，具体如下：

- $\Delta>0$，那么原方程中 $x_1,x_2$ 显然都不相等因此原方程有两个不同的解。
- $\Delta=0$，那么原方程中的 $x_1,x_2$ 显然都是 $-\dfrac{b}{2a}$，因此原方程严格上讲**有两个相同的解**，但原题目貌似将这种情况算为只有一个解了，因此这里默认为**有一个解**。
- $\Delta<0$，显然，根号里面如果是负数是不在实数的讨论范围的，因此原方程严格上讲**无实数解**，但原题目貌似将这种情况算为无解，因此这里默认为**无解**。

其实只要找出 $\Delta$，这道题目就迎刃而解了，直接那上面三种情况分类讨论即可。注意，在有两个解的时候，本题要求从小到大输出，因此建议先把两个解存储进来（设为 $x,y$），然后输出 $\min\{x,y\}$ 和 $\max\{x,y\}$。

另外，$b^2$ 和 $ac$ 有可能爆出 int 范围内（$10^5\times 10^5\geqslant2^{31}$），因此需要开 `long long`。
## Code
```cpp

long long a, b, c;

int main() {
	scanf("%lld%lld%lld", &a, &b, &c);
	long long delta = b * b - 4 * a * c;
	if(!a && !b && !c) return printf("-1"), 0;
    if(!a && !b) return printf("0"), 0;
    if(!a) return printf("1\n%.8lf", -c * 1.0 / b), 0;
	if(delta > 0)
		printf("2\n%.8lf\n%.8lf", min((-b - sqrt(delta)) * 1.0 / (a * 2.0), (-b + sqrt(delta)) * 1.0 / (a * 2.0)), max((-b - sqrt(delta)) * 1.0 / (a * 2.0), (-b + sqrt(delta)) * 1.0 / (a * 2.0)));
	else if(delta == 0)
		printf("1\n%.8lf", -b / (a * 2.0));
	else
		printf("0");
	return 0;
}
```

---

## 作者：lemonfor (赞：0)

一道很水的题，按照题意写即可。。。

1. 当只有 $A$ 为 $0$ 时，一个解。
2. 当 $A$ 为 $0$ 且 $B$ 为 $0$ ,$C$ 不为 $0$ 时 ，无解。
3. 当 $A ,B ,C$ 均为 $0$ 时，无数解
4. 三者均不为 $0$ 时，依照求根公式解即可

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define int long long
#define _ 0
#define rep(k ,l ,r) for(register int k = l ; k <= r ; ++ k)
using namespace std;
int A ,B ,C;
double del ,ans ,_ans;
int read() {
    char cc = getchar() ; int cn = 0 , flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
signed main() {
    A = read() ,B = read() ,C = read();
    if(!A) if(!B) if(!A && !B && !C) printf("-1");else printf("0");
    else printf("1\n%.10lf" ,(double) (- C) / (double)B);
    else {
        del = (double)(B * B - 4 * A * C) ,ans = (double)((- B + sqrt(del)) / (double)(2 * A)) ,_ans = (double)((- B - sqrt(del)) / (double)(2 * A));
        if(!del) printf("1\n%.10lf" ,ans);
        else if(del > 0) printf("2\n%.10lf\n%.10lf" ,min(ans ,_ans) ,max(ans ,_ans));
        else if(del < 0) printf("0");
    }
    return ~~(0^_^0);
}
```

---

## 作者：PC_DOS (赞：0)

想必各位在刚学一元二次方程的时候一定做过这道题目，刚学编程的时候可能也做过...


分A=0和A<>0两种情况讨论即可，不过请注意: A<>0时，二重根(也就是Delta=0)算有且仅有一根，复根(Delta<0)作无根处理，不需要考虑输出复数的情况。还有就是输出的时候注意控制一下精度(题目要求至少保留小数点后5位小数)。


代码:

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
    ios::sync_with_stdio(false); //关闭与STDIO的同步，一定意义上的输入输出加速
    long long iA, iB, iC,iDelta; //iA、iB、iC为各项系数，iDelta=iB^2-4*iA*iC
    double iX1, iX2; //两根
    cin >> iA >> iB >> iC; //输入
    if (iA == 0){ //如果二次项系数为0，退化为一元一次方程
        if (iB == 0 && iC == 0){ //形如0x=0，无数个解
            cout << -1;
            goto endapp;
        }
        else if (iB == 0 && iC != 0){ //形如0x=t(t<>0)，无解
            cout << 0;
            goto endapp;
        }
        else{ //有且仅有一解
            iX1 = double(-iC) / double(iB); //注意转一下类型
            cout.setf(ios::fixed); //设置定点数出
            cout << 1 <<setprecision(10)<< endl << iX1; //输出，这里保留10位小数
            goto endapp;
        }
    }
    iDelta = iB*iB - 4 * iA*iC; //计算Delta
    if (iDelta < 0){ //如果没有实数根
        cout << 0;
        goto endapp;
    }
    iX1 = (double(-iB) - sqrt(iDelta)) / (2 * double(iA));
    iX2 = (double(-iB) + sqrt(iDelta)) / (2 * double(iA)); //计算两根
    if (iX1 > iX2){ //题目要求从小到大输出，判定一下
        swap(iX1, iX2); //如果iX1>iX2，交换
    }
    if (iDelta != 0){ //如果有两个不等实根
        cout.setf(ios::fixed);
        cout << 2 << '\n' << setprecision(10) << iX1 << '\n' << iX2; //设置定点并输出
    }
    else{ //否则仅输出一解
        cout.setf(ios::fixed);
        cout << 1 << '\n' << setprecision(10) << iX1; //设置定点并输出
    }
endapp:
    return 0; //结束
}
```

---

