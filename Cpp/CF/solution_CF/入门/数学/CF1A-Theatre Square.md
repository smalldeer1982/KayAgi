# Theatre Square

## 题目描述

贝尔兰首都的剧院广场呈矩形，尺寸为 $n \times m$。在该市周年纪念日之际，人们决定用正方形的花岗岩石板铺设广场。每块石板的尺寸为 $a \times a$。

铺砌广场所需的石板最少数量是多少？石板可以覆盖比剧院广场更大的表面，但必须覆盖广场。不允许打碎石板。石板的边应与广场的某条边平行。

## 样例 #1

### 输入

```
6 6 4
```

### 输出

```
4
```

# 题解

## 作者：览遍千秋 (赞：71)

由画图可得，行长n，则需要$n/a$上取整的数目，列同理。则可以得到程序如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,a;
    cin>>n>>m>>a;
    if(n%a==0) n/=a;
    else n=n/a+1;
    if(m%a==0) m/=a;
    else m=m/a+1;
    cout<<n*m<<endl;
    return 0;
}
```

---

## 作者：jeremyjy (赞：69)

这道题完美地凸显了C++自带函数ceil的无穷用处（手动点赞）

极简思路：直接把n/a、m/a向上取整不就**行了吗**？？？

送来9行清新代码（if you can yahang，it will be less）
```cpp
#include<>//头文件
using namespace std;//使用名字空间
int main()//主程序
{
	int n,m,a;//定义变量
	cin>>n>>m>>a;//读入变量（如果你够无聊，可以写读优哈哈哈）
	cout<<(long long)(ceil(n/(double)a)*ceil(m/(double)a));//直接输出（小心中间的强制转换！！！）不转long long会出现一些奇奇怪怪的东东
	return 0;//华丽结束！
}
```

Tips：这个程序被做了手脚，请勿直接Ctrl+C、Ctrl+V！

---

## 作者：Yo_haor (赞：34)

楼下的dalao都写得很好，接下来看看我的qwq

我和楼下的dalao们(zhi)思(you)路(yi)都(zhong)一(jie)样(fa)

### 但我可以优化一下qwq

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;//大家都懂就不说了
long long n,m,a;//千万不要用int，蒟蒻第一次就WA一个点::>_<::
int main(){
	cin>>n>>m>>a;
	cout<<((n-1)/a+1)*((m-1)/a+1);
    //最好的优化，直接用少一行（列）来÷a，最后加多1行（列）qwq
	return 0;
}
```


---

## 作者：cpse (赞：23)

萌新第一篇题解，希望大佬支持
先定义m,n,a变量，再分别输入
```
#include<iostream>
using namespace std;
int main()
{
	int n,m,a;
	cin>>n>>m>>a;
	return 0;
}
```
然后作出基本输出操作
```
cout<<n/a*m/a<<endl;
//注意！顺序不能错！
```
不要急着抄，肯定有错误
原题说允许石板覆盖的区域超出广场，那么肯定石板的总面积要大于等于广场的面积，并且长和宽都长于广场。此时大家应该已经想到了C++的math.h头文件里的ceil函数，它的作用是取下整，所以，就有下面这段代码：
```c
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,m,a;
	cin>>n>>m>>a;
	cout<<ceil(n/a)*ceil(m/a)<<endl;
   	//顺序仍然不能错
	return 0;
}
```
可是大家知道，ceil函数的原型是
```
double ceil(double x);
```
它是要用double类型的变量，所以还要强制类型转换一下
代码如下：
```c
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,m,a;
	cin>>n>>m>>a;
	cout<<ceil(double(n)/double(a))*ceil(double(m)/double(a))<<endl;
	return 0;
}
```
试过的朋友有可能只有89分，因为1≤n,m,a≤10的9次方，所以要用long long类型的变量
真正代码如下：
```c
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	long long n,m,a;
	cin>>n>>m>>a;
	cout<<(long long)(ceil(double(n)/double(a))*ceil(double(m)/double(a)))<<endl;
	return 0;
}
```
到此结束！

---

## 作者：SUNCHAOYI (赞：9)

利用 C++ 函数库的。

```cpp
#include<iostream>
#include<cmath>//ceil函数的头文件 
using namespace std;
int main()
{
	int a,n,m;
	cin>>n>>m>>a;
	cout<<1ll * ceil(n/(double)a)*ceil(m/(double)a)<<endl;//注意m与n除以a都要是double型的 
	//ceil：向上取整 
	return 0;
}
```

---

自行编撰代码的

```cpp
#include<iostream>
int ceil(int a,int b);
using namespace std;
int main()
{
	int a,n,m;
	cin>>n>>m>>a;
	cout<<1ll * ceil(n,a)*ceil(m,a)<<endl;
	return 0;
}
int ceil(int a,int b) {return (a + b - 1) / b;} 
```

---

## 作者：日天君 (赞：8)

写在前面的话：
## ~~愿你在明天收获别样的快乐~~
### 2018.9.2 星期一
直接贴题解吧

### _Pas大法好_ 

```pascal
uses math;
var
    c,k:int64;
    n,m,a:int64;
begin
    readln(n,m,a);
	c:=ceil(n/a);    //c是长；
	k:=ceil(m/a);    //k是宽;
	writeln(c*k);    只要是adult only（滑稽）都能看懂
end.
```

看到前面C++说ceil很好吃，但我不吃。

###### ~~(math库真香)~~

---

## 作者：_Int_ (赞：5)

看了楼下**dalao**的题解，**蒟蒻**感觉不容易懂，来水一发

一道很简单的题，数学方法就够，但是要注意必须用long long，因为10的9方乘10的9方int会爆。还有一点，这一题是向上取整，直接用( n / a ) \* ( n / a )是不行的，顺便提一下，a除b的向上取整公式是( a + b - 1 ) / b。或者用< cmath >里的向上取整函数也可以，但是能不用小数就不用小数~~lalala~~

```cpp
# include < cstdio >
# include < iostream >
using namespace std ;       // 头文件准备好
int main ( ) {
    long long n , m , a ;         // long long 欧
    cin >> n >> m >> a ;      // 读入
    cout << ( ( n + a - 1 ) / a ) * ( ( m + a - 1 ) / a ) ;        // 输出
    return 0 ;          // 结束
}
~~短短短~~
```

---

## 作者：土川崇贺 (赞：4)

		分别求出长和宽能放几块，最后相乘输出。
```
#include<iostream>
using namespace std;
int main()
{
    long long n,m,a;
    cin>>n>>m>>a;
    if(n%a==0)
    {
    	n/=a;
	}
	else
	{
		n=n/a+1;
	}
	if(m%a==0)
	{
		m/=a;
	}
	else
	{
		m=m/a+1;
	}
	cout<<n*m;
	return 0;
}

```

---

## 作者：紫金依旧 (赞：4)

本题直接用大面积除以小面积是无法达到全AC的

而仔细看过题目的我们会发现:这只是一道有关上取整的问题.

而不会用函数库的蒟蒻(如我)怎么办呢?

祭出公式大法:

# _**n=(n-1)/a+1**_ ;

附上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
logn logn n,m,a;
int mian()
{
	cin>>n>>m>>a;
	n=(n-1)/a+1;
	m=(m-1)/a+1;
	cuot<<n*m;
	return 0;
}
```

打造文明洛谷,拒绝抄袭.(罒ω罒)

---

## 作者：Andysun06 (赞：3)

## 一道很~~难~~的数学题

# 公式：((n+a-1)div a)\*((m+a-1)div a)！！

#### pascal题解：

```cpp
###### var n,m,a:longint;  //integer会炸！
######  begin
######   readln(n,m,a);   //输入
######   writeln(((n+a-1)div a)*((m+a-1)div a));  //计算并输出
######  end. //完美的结束~~~
```
# 严禁抄袭！！！！

---

## 作者：chufuzhe (赞：1)

这题其实可以求长上铺几块石板，宽上铺几块石板，再把它们相乘就可以了。注意要向上取整，可以判断有没有余数，有就返回a/b+1，没有就返回a/b（a为被除数，b为除数），因为需要两次操作，为了使代码简洁，本题解用了函数；也可以用ceil函数，用法ceil(被除数/除数)或者先算出来再ceil(商)，在这里和上面操作相似，是整数就不变，不是整数就取整数部分再加一，如ceil(100/3)就等于34，ceil(5.01)就等于6
上代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;//声明一个命名空间
long long f(long long a,long long b)//f函数为向上取整
{
	//等同于return ceil(a/b);
	if(a%b==0) return a/b;
    //如果整除直接返回a/b,如果正好铺满，这一条边就只要a/b块石板
    //因为如果满足上面一个条件,就直接返回了,执行不到这里,所以不用else
	return a/b+1;
    //有余数就返回a/b+1,如果不能正好铺满，就要多铺一块
}
int main()//主程序
{
    long long n,m,a;
    //数据范围1≤n,m,a≤10^9，如果n为10^9，m为10^9，a为1，int就炸掉了，10^18要开long long
    cin>>n>>m>>a;//输入
    cout<<f(n,a)*f(m,a)<<endl;//输出
    return 0;//结束
}
```
这是本蒟蒻发布的第一篇题解,求通过(qwq)

---

## 作者：Administrator2004 (赞：1)

直接向上取整即可，因为题目中说的可以把地砖铺到外面去，所以出现小数时要进上去。
c++自带的函数ceil很方便，但是用的时候要注意类型转换（详见注释）。
```cpp
#include <iostream>
#include <cmath>//ceil需要
using namespace std;
int main()
{
    int n,m,a;
    cin>>n>>m>>a;
    cout<<(long long)(ceil((double)n/a)*ceil((double)m/a));//重点在这一句：除运算时要转成小数，要保留小数位。如果不保留的话小数位会被截去，就像样例，6/4=1.5,要保留小数位。
    //为什么转成long long 呢？因为如果不转的话，会出现类似1e+018这种尴尬情况。double值太大会转成指数表达形式。
}
```

---

## 作者：康娜卡姆依 (赞：1)

楼下**dalao**们的公式实在有点。。。

来一点点最**基本(shui)**的解法

Pascal选手的福利——

```pascal
var n,m,x,y:int64; //数据范围要看仔细
    a:longint;
begin
  read(n,m,a);
  if n mod a<>0 then x:=n div a +1 else x:=n div a;//不能整除也就是不能刚好摆完就div掉再加1(完整石板数+1）否则直接除
  if m mod a<>0 then y:=m div a +1 else y:=m div a;//同上
  write(x*y);
end.
  
  
```

---

## 作者：Loner_Knowledge (赞：1)

这是一道数学题

---

设答案为$ans$，我们要使其满足这个式子$ans\times a^{2}\ge n\times m$，变形得$ans\ge\frac{n}{a}\times\frac{m}{a}$。


根据石板不可分割且石板需完全覆盖广场的条件可知$ans\ge\lceil\frac{n}{a}\rceil\times\lceil\frac{m}{a}\rceil$


我们只需要求满足以上式子的最小答案，于是$ans=\lceil\frac{n}{a}\rceil\times\lceil\frac{m}{a}\rceil$。


注：$\lceil\frac{a}{b}\rceil$为向上取整$\frac{a}{b}$


注意**数据范围**，答案要用$long\ long$。


```cpp
#include<cstdio>
int main() {
    int n,m,a;
    scanf("%d%d%d",&n,&m,&a);
    printf("%lld",(long long)(n/a+(n%a!=0))*(m/a+(m%a!=0)));
    //这里使用了逻辑表达式，当n%a==0时(n%a!=0)==0 (Fasle)，而当n%a!=0时(n%a!=0)==1 (True)，通过判断余数来决定是否+1，实现向上取整
    return 0;
}
```

---

---

## 作者：bym666 (赞：0)

# CF1A 【Theatre Square】
这道题用大面积初一小面积的方法是行不通的，应该求出每行每列用多少块再相乘。所以我按照这个思路提交了一下代码↓↓↓
```
#include <bits/stdc++.h> 
using namespace std;
int n,m,a,x,y; 
int main()
{
	cin>>n>>m>>a; 
	if(n%a==0) x=n/a; 
	else x=n/a+1; 
	if(m%a==0) y=m/a;
	else y=m/a+1;
	cout<<x*y;
}
```
当我颇为~~鸡冻~~激动地看着测评记录时，什么玩意儿，竟然WA了！

这是怎么回事呢？我一看数据范围，10^9，用int的话n和m不会超，但要是乘起来就要超了，所以应该用long long。改成long long之后，果然AC了。
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
long long n,m,a,x,y;//一定要用long long，否则会错 
int main()
{
	cin>>n>>m>>a;//输入 
	if(n%a==0) x=n/a;//如果n能整除a，每行就用n/a块 
	else x=n/a+1;//如果不能，每行就用n/a+1块 
	if(m%a==0) y=m/a;//如果m能整除a，每列就用m/a块 
	else y=m/a+1;//如果不能，每列就用m/a+1块
	cout<<x*y;//一共要用多少块 
}
```


---

## 作者：由比滨丶雪乃 (赞：0)

## CF1A Theatre Square

- [题目链接](https://www.luogu.org/problem/CF1A)

- [更好的阅读体验](https://www.luogu.org/blog/Hikigaya/cf1a-theatre-square-ti-xie-qwq)

题目意思很简单，暴力模拟就好了qwq

分3种情况

1. n,m可以整除a 

2. n,m其中有一个数可以整除a

3. n,m都不能整除a


**记得开longlong   qwq**

CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long

using namespace std;

ll n,m;
ll a;
ll ans;
ll sum1,sum2;

int main()
{
	scanf("%lld%lld%lld",&n,&m,&a);
	if(n%a==0&&m%a==0)//第一种情况
	{
		sum1=n/a;
		sum2=m/a;
	}
	if(n%a!=0&&m%a==0)//第二种情况
	{
		sum1=(n+a)/a;
		sum2=m/a;
	}
	if(n%a==0&&m%a!=0)
	{
		sum1=n/a;
		sum2=(m+a)/a;
	}
	if(n%a!=0&&m%a!=0)第三种情况qwq
	{
		sum1=(n+a)/a;
		sum2=(m+a)/a;
	}
	ans=sum1*sum2;
	printf("%lld\n",ans);//AC
	return 0;
}
```




---

## 作者：龙啸空 (赞：0)

# 入门难度题

对，就应该是入门难度。

一个公式解决：ans=(n/a+(n%a!=0))*(m/a+(m%a!=0));

代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    long long a,n,m;
    scanf("%lld%lld%lld",&n,&m,&a);
    long long ans;
    ans=(n/a+(n%a!=0))*(m/a+(m%a!=0));
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：盛其然 (赞：0)

这是一道很水的题目，判断一下是否整除，输出乘积就行了
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m;//注意一定要用long long,否则会爆。
    我就被卡了3次
	long long a;
	cin>>n>>m>>a;
	if((n%a==0)&&(m%a==0))//分别判断n与m是否整除
	cout<<n/a*m/a;
	if(!(n%a)&&(m%a))//同上
	cout<<(n/a)*(m/a+1);
	if((n%a)&&!(m%a))
	cout<<(n/a+1)*(m/a);
	if((n%a)&&(m%a))
	cout<<(n/a+1)*(m/a+1);
    while(1)//反作弊系统
    return 0;//养成好习惯
}
```
求管理员放过，谢谢~~

---

## 作者：FLASH_CM (赞：0)

### 【算法思路】
根据题意，简单而言，将长和宽分别除以石板的边长并向上取整相乘即可。
### 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	long long ans=0,n,m,a;
	scanf("%lld%lld%lld",&n,&m,&a);
	ans=((n-1)/a+1)*((m-1)/a+1);
	printf("%lld",ans);
	return 0;
}
```
### 【温馨提示】
1、10^9乘以10^9已经超过2^31，会爆int，所有我们要使用long long。

2、上面的代码比较有趣，建议不要直接Ctrl+C Ctrl+V，否则会发生有趣的事情。

---

## 作者：_Felix (赞：0)

不是很难，我想你看题解一定是因为没开long long吧，如果是这样，给我点个赞哦~
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    long long n,m,a;//一开始没开long long，我过了几个月回来试了试，才ac
    cin>>n>>m>>a;//读入
    n=ceil(n*1.0/a);//天花板函数万岁
    m=ceil(m*1.0/a);//天花板函数万岁
    cout<<n*m<<endl;//乘一下，输出！
    return 0;//good job！
}
```
**By czy(你们~~可爱~~的小萌新QAQ）**

---

