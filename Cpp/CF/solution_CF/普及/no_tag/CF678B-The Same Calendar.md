# The Same Calendar

## 题目描述

The girl Taylor has a beautiful calendar for the year $ y $ . In the calendar all days are given with their days of week: Monday, Tuesday, Wednesday, Thursday, Friday, Saturday and Sunday.

The calendar is so beautiful that she wants to know what is the next year after $ y $ when the calendar will be exactly the same. Help Taylor to find that year.

Note that leap years has $ 366 $ days. The year is leap if it is divisible by $ 400 $ or it is divisible by $ 4 $ , but not by $ 100 $ ([https://en.wikipedia.org/wiki/Leap\_year](https://en.wikipedia.org/wiki/Leap_year)).

## 说明/提示

Today is Monday, the $ 13 $ th of June, $ 2016 $ .

## 样例 #1

### 输入

```
2016
```

### 输出

```
2044
```

## 样例 #2

### 输入

```
2000
```

### 输出

```
2028
```

## 样例 #3

### 输入

```
50501
```

### 输出

```
50507
```

# 题解

## 作者：JimmyF (赞：2)

由于题目说
$n\leqslant100000$
，考虑枚举答案
~~（我不会O(1)）~~。

先打个判断闰年的函数，由于只有平年和闰年两种状态，所以用
$bool$
类型。

```cpp
bool check(int x)
{
	//四年一润，百年不润；四百年再闰
	if((x%4==0&&x%100!=0)||x%400==0)return 1; //是闰年则返回1
	return 0;  //不是返回0
}
```

#### 然后就到了本题的核心了（敲黑板）！

假设题目输入的年份为
$n$
，而输出的答案为
$m$
，
$n$
和
$m$
之间的天数为
$p$
，则应该满足：

1. $check(n)=check(m)$
2. $p \bmod 7=0$

就有了重要的模拟过程：
```cpp
cin>>n;   //输入
m=n;      //赋值
do
{
	++m;   //年份+1
	p=(p+365+check(m))%7; //计算当前的星期
}
while(!(check(n)==check(m)&&p==0));  //如果条件不成立才做
```

### 你们要的AC Code

```cpp
#include<bits/stdc++.h>
#include<con>
using namespace std;
int n,m,p;
bool check(int x)
{
	if((x%4==0&&x%100!=0)||x%400==0)return 1;
	return 0;
}
int main()
{
	cin>>n;
	m=n;
	do
	{
		++m;
		p=(p+365+check(m))%7;
	}
	while(!(check(n)==check(m)&&p==0));
	cout<<m;
	return 0;
}
```

#### ~~要抄袭请自便。~~

---

## 作者：JS_TZ_ZHR (赞：2)

~~让我来水过一波~~

  其实本题很简单，先给出一个初始年份，找到一个比初始年份大，天数与初始年份相同，第一天的星期也与初始年份相同，由于数据太水，直接枚举即可。~~(要是我会O(1)就好了)~~
  
  本题有一点绕，耐心做慢慢调就行了
#####     代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define date(n) (n%4==0?n%100==0?n%400==0?1:0:1:0)//令人眼花缭乱的三目运算符
int n,xq;
bool day;//因为一年只分平年和闰年，所以我用bool来存储
int main() {
	cin>>n;
	day=date(n);//计算n是平年还是闰年
	while(n++) {//一开始用++n害得我调试了半天
		xq=(xq+date(n)+1)%7;//平年余一天，闰年余两天
		if(date(n)==day&&xq==0/*如果星期一样会回到原来的初始值0*/) {
			cout<<n<<endl;
			break;//完美结束
		}
	}
}
```
~~所以这一题是黄题？~~

---

## 作者：Ag2WO4 (赞：1)

## 思路
**由于 $y<100000$ ，这题可以枚举。**

那么我们可以利用 Python 的 calendar 模块来帮助解决问题。模块中有一个 isleap 函数，它返回输入的年份是不是闰年，对应第一个要求（年长度相等）；模块中还有个 weekday 函数，它返回的是输入的日期是星期几，将月份和日期固定为元旦就能对应第二个要求。

接下来就是从 $y+1$ 开始枚举，判断闰年和星期，如果年份 $i$ 满足题目中的两个条件，输出 $i$ ，结束程序。
## 参考代码
```python
import calendar as c;a=int(input())
for i in range(a+1,1000000):
    if c.isleap(a)==c.isleap(i) and c.weekday(a,1,1)==c.weekday(i,1,1):
        print(i);exit()
```


---

## 作者：_短笛无腔_ (赞：1)

# 前置芝士：闰年(leap_year）

闰年，就是 $2$ 月多 $1$ 天，有 $366$ 天的年份。

判断闰年，记住一个口诀`四年一闰，百年不闰，四百年再闰。`

------------

# 正文

这道题主要是思维难度啦，代码难度一点不难。

我们先看到`天数与n相同`，想到什么呢？


```cpp
//判断闰年，不能用bool是因为要比较 
int leap(int year){
	//前面是非整百年，后面是整百年 
	if((year%4==0&&year%100!=0)||(year%400==0))return 1;//是闰年 
	return 0;//不是闰年 
}
```

关于那个用`bool`的问题我们亮完整代码时再谈。

再看`该年的第一天的星期与n年相同`。

有点懵？这不是问题，我们看一看良心提示，理一理思路：`Today is Monday, the 13 th of June, 2016.`

说~~人话~~中文就是：今天是 $2016$ 年 $6$ 月 $13$ 日，星期一。

我们用这个来算一下这一年开始的天数吧！

先背一下古诗：

```
一三五七八十腊，三十一天整不差。
四六九冬三十日，平年二月二十八，闰年二月把一加。
```

又因为 $2016$ 年是闰年，我们推出算式：`31+29+31+30+31+13=165`。

而 $165$ mod $7$ 为 $4$ ，所以`4+1=5`。

由此推断出这一年第一天是星期五。

我们发现，这一年的第一天就是一年的天数 mod $7$ $+$ $1$ 。如果遇上闰年，加 $2$ 。

所以我们高高兴兴的打出完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//判断闰年，不能用bool是因为要比较 
int leap(int year){
	//前面是非整百年，后面是整百年 
	if((year%4==0&&year%100!=0)||(year%400==0))return 1;//是闰年 
	return 0;//不是闰年 
}
int main(){
	int n,day=0;//day：天数 
	cin>>n;
	int s=n;
	//循环判断完全相同年 
	while(1){
		if(leap(n))day+=2;//闰年多一天 
		else day+=1;
		day%=7;//算星期
		n++;//过去了一年
		if(day==0&&leap(s)==leap(n)){
			cout<<n;
			break;
		} 
	}
	return 0;
}
```

关于不能用`bool`的问题，请大家看到这一段代码：

```cpp
if(day==0&&leap(s)==leap(n))
```

这里要是用`bool`不能正常比较。

然后，我们就愉快的$\color{white}\colorbox{green}{AC}$啦！

---

## 作者：智子·起源 (赞：0)

## 你们为什么做那么复杂？~~（逃）~~


### 1、理解题目：

我翻译了一下英文，它的意思是找到一个和当前年的阳历完全一样的未来年（最好输出距离当前年最近的）

确定完全一样的两个条件：

- 天数相同

- 第一天星期和当前年相同

题目还给了一个条件：Today is Monday, the 13 th of June, 2016.

（2016.6.13是星期一）



------------


### 2、明确思路

首先，这道题看起来条件复杂，其实很简单。

从当前年开始往后无限延长找，一旦找到一个符合条件的输出并结束程序即可。

#### 接下来是重点：判断条件

判断天数相同很容易，手打一个计算年的天数的函数——

```cpp
int getday(int q)
{
  int y;
  if(q%4==0&&q%100!=0||q%400==0)y=366;//如果闰年336天。
  else y=365;//平年365天。
  return y;
}
```

然后只要判断getday（n）和getday（当前年）相等即可。

==========

二：第一天星期相等

我们不妨这样想：他能把初始的星期维持住一样，那中间经过的天数必定是7的倍数。（一个星期天数）

我们只要用变量把当前年与开始年之间的天数累加起来即可。

（说不清，看程序。。。）

### 3、code

#### 红蝶在此，抄袭可耻。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;long long h;
int getday(int q)
{
  int y;
  if(q%4==0&&q%100!=0||q%400==0)y=366;
  else y=365;
  return y;
}
int main()
{
  cin>>n;x=getday(n);
  for(int i=n+1;;i++)
  {
    h+=getday(i-1);
    if(getday(i)==getday(n)&&h%7==0){cout<<i<<endl;return 0;}
  }
  return 0;
}
```

崭新的码风，望过

---

## 作者：yf最qhhh (赞：0)

~~这道题为什么写的这么复杂啊。。。~~

思路：判断是否都同为闰年或都同为平年

```cpp
if((x%400==0)||(x%4==0&&x%100!=0))
```
再判断是否跟输入的年份第一天是否为同一星期数，看$\mod 7$ 的余数是否为0就行了嘛.

唯一要注意的点是闰年会产生 $366$ 天

代码如下（或成为最短代码？）
```cpp
#include<cstdio>
#define rll register long long
#define ll long long
ll rrr(rll x){//判闰年的函数
	if((x%400==0)||(x%4==0&&x%100!=0))return 1;return 0;
}
int main(){
	rll n,sum=0,i;scanf("%lld",&n);for(i=n+1;;i++){sum+=rrr(i-1)==1?366:365;if(rrr(i)==rrr(n)&&sum%7==0)return printf("%lld",i),0;}//这一坨都是我之前提到过的操作。
}

```
完美AC！

---

