# Monitor

## 题目描述

Reca company makes monitors, the most popular of their models is AB999 with the screen size $ a×b $ centimeters. Because of some production peculiarities a screen parameters are integer numbers. Recently the screen sides ratio $ x:y $ became popular with users. That's why the company wants to reduce monitor AB999 size so that its screen sides ratio becomes $ x:y $ , at the same time they want its total area to be maximal of all possible variants. Your task is to find the screen parameters of the reduced size model, or find out that such a reduction can't be performed.

## 样例 #1

### 输入

```
800 600 4 3
```

### 输出

```
800 600
```

## 样例 #2

### 输入

```
1920 1200 16 9
```

### 输出

```
1920 1080
```

## 样例 #3

### 输入

```
1 1 1 2
```

### 输出

```
0 0
```

# 题解

## 作者：RagnaLP (赞：9)

这道题不要想多了，其实很简单。

**思路**：

把a,b拆分成许多长度分别为x,y的小段，这样就能保证满足 x:y 的比例（由于x,y可能不是最简整数比，拆之前要先化简），然后找出a有多少小段和b有多少小段，选取最小值（为了保证结果在a,b范围内），再分别乘上x,y就得到答案了。

代码：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a,b,x,y;//原长a,b，比例x,y
int gcd(int n,int m){
	if(n<m) swap(n,m);
	return n==0?n:gcd(m,n%m);
}//辗转相除法求最小公约数
int main() {
	cin>>a>>b>>x>>y;
	//为避免x：y不是最简整数比，找出x,y的最小公约数进行化简
    int k=gcd(x,y);
	x/=k,y/=k;//直接除
	if(a<x||b<y){//特判：a或者b不能拆成x,y组成的小段（就是说x>a或y>b)则无解
		printf("0 0");
		return 0;
	}
	int base=min(a/x,b/y);//a/x表示a被拆分的数量，b/x同理，找出a,b范围内的最大段数
	printf("%d %d",x*base,y*base);//用最大段数乘上x,y得解
	return 0;
}
```

---

## 作者：jijidawang (赞：8)

## 题面简述

> 给出一矩形长 $a$ 和宽 $b$，给出长宽比 $x:y$，缩短矩形的长和宽,使它的长和宽之比等于 $x:y$，试求最终的长宽。


## 算法分析


首先将 $x,y$ 约分。

若 $x>a$ 或 $y>b$  显然无解。

求出缩短比 $k=\min\left\{\dfrac{a}{x},\dfrac{b}{y}\right\}$。

然后用 $x,y$ 分别乘即可。


---

## 作者：rayluo (赞：3)

### description :

- 给定 a，b，x，y,要求将 a，b 分别减少一个非负数 c，d，使得 $a-c \equiv 0\pmod{x}$ 且 $b-d \equiv 0 \pmod{y}$ 且 $\frac{a-c}{b-d}= \frac{x}{y}$。

- x 与 a 对应，y 与 b 对应。

- 要求 $(a-c) \times (b-d)$ 最大，输出 $(a-c)$，$(b-d)$。

### solution :

一开始，我们就可以将 x，y 约分后把 $x>a$ 或 $y>b$ 的排除掉。

我们可以知道，当 $(a-c)$ 与 $(b-d)$ 中的任何一个被确定后，另外一个也是确定的，且因为都 x，y 是正整数，所以两数是成正比的。因此为使 $(a-c)*(b-d)$最大化，$(a-c)$ 与 $(b-d)$中至少有一个取到了最大值。

于是我们先试着将 $(a-c)$ 取到最大值，也就是 a 以下第一个被 x 整除的数  $\left\lfloor\dfrac{a}{x}\right\rfloor \times x$。再根据 $x:y$ 的比例关系算出 $(b-d)$，但如果算出来的 $(b-d) \geq b$ ，按题目要求需舍弃。再同样用 $(b-d)$ 做一遍，若两种都符合要求，就取乘积更大的那一个。

那有没有两种情况都不符合要求的呢。我们假设 $a \geq b$，求出来的最大的 $(a-c)$，$(a-c)\div x \times y > b$ 那么这时候由 b 得出的最大的 $(b-d)$，$(b-d) \div y \times x$ 必然小于等于 a。$a < b$ 同理，答案是否定的。

记得开 long long。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in inline
#define ll long long
in ll read()
{
	ll w=0,r=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')r=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar(); 
	}
	return w*r;
}

in ll gcd(ll x0,ll y0)  //最大公约数 用于约分 
{
	return y0?gcd(y0,x0%y0):x0;
}

ll a,b,x,y,a1,b1,ansa,ansb;  //a,b,x,y 为题目中所描述的。a1,b1 为 a,b 的备份。ansa,ansb 为最终结果。 

int main()
{
//	freopen(".in","r",stdin);
	a=read();
	a1=a;
	b=read();
	b1=b;
	x=read();
	y=read();
	ll k=gcd(x,y);
	x/=k;
	y/=k;
	if(x>a||y>b)
	{
		puts("0 0");
		return 0;
	}
	a=(a/x)*x;  //a 取能取的最大值时 
	b=(a/x)*y;
	if(a<=a1&&b<=b1)  //是否符合要求 
	{
		ansa=a;
		ansb=b;
	}
	a=a1;
	b=b1;
	b=(b/y)*y;  //b 取能取的最大值时  
	a=(b/y)*x;
	if(a<=a1&&b<=b1) 
	{
		if(ansa*ansb<a*b)  //取更大的那一个 
		{
			ansa=a;
			ansb=b;
		}
	}
	cout<<ansa<<" "<<ansb<<endl;
	return 0;
} 
```

一些细节还希望各位多多思考一下，如有问题，请指出。

---

## 作者：Andysun06 (赞：3)

### CF16C 题解
这题居然没有 Pascal 题解，那我就来一篇吧。
#### 做题思路：
先找到 $x$,$y$ 的最小公因数，然后把他们分别除以他们的最小公因数 $\gcd(x,y);$ 再将 $a$,$b$ 分别除以它们，将最小值 $minn$ 找出来，输出他们与 $minn$ 的乘积。

但是当我们这样做时，发现总是卡在一个点，当我们仔细想想你就会发现，万一 $a<x$ 或 $b<x$ 呢？那不是要输出 `0 0` 吗？所以，加一个特判解决所有问题

#### 大致难度：
个人认为在 `入门` 左右，思维难度简单。

#### 完整代码：
```pas
uses math;  //打开数学库
function gcd(a,b:longint):longint;//函数定义，辗转相除求最大公约数
begin
  if b=0 then exit(a);
  exit(gcd(b,a mod b));
end;
var a,b,c,d,k,minn:longint; //定义
begin
  readln(a,b,c,d);
  k:=gcd(c,d);  //求 c,d 的最大公约数
  c:=c div k;  //分别除以 c,d 的最大公约数
  d:=d div k;
  if (a<c) or (b<d) then //务必加上，特判
  begin
    writeln('0 0');
    halt;  //终止程序
  end;
  minn:=min(a div c,b div d);  //将最小值 minn 找出来
  writeln(c*minn,' ',d*minn);  //输出他们与 minn 的乘积
end.  //结尾句号，勿忘

```

希望本题解对大家有帮助，也感谢管理员百忙之中帮我审核题解，谢谢！

---

## 作者：Eraine (赞：1)

# 题面
[CF16C](https://www.luogu.com.cn/problem/CF16C#submit)

难度：☆☆☆☆（普及+/提高）
知识点：数论，数学
# 思路
这一题别看难度很大，其实写起来很简单。
为什么要取**最小值**？因为要求最大的长宽，但是保证不能超过原来的数，所以取最小值。
需要注意的是a和b需要**化简**！（即化成最简比）否则在#6就会WA了。
```C++
	int d=__gcd(a,b);
	a=a/d;
	b=b/d;
```
只要数学好的人就会理解。其他的人可能需要慢慢消化。
# AC代码
```C++
#include<iostream>
#include<algorithm>//为了调用函数__gcd()
using namespace std;
int main(){
	long long x,y,a,b;
	cin>>x>>y>>a>>b;
	int d=__gcd(a,b);//最大公约数函数
	a=a/d;
	b=b/d;
	long long c=2000000035;//保证不超过x/a和y/b
	c=min(c,x/a);
	c=min(c,y/b);
	cout<<a*c<<" "<<b*c;
	return 0;
}
```

---

