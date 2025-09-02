# 差の平均

## 题目描述

给定一个数列 $a$，有 $n$ 个元素 $\{a_1,a_2,a_3\cdots a_{n-1},a_n\}$，求
$$\dfrac{(a_2-a_1)+(a_3-a_2)+(a_4-a_3)+\cdots+(a_n-a_{n-1})}{n-1}$$

如果不整除，则保留 $3$ 位小数输出，否则直接输出。

与正确答案相差不超过 $0.001$ 的答案也可通过。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le100,1\le a_i\le10^9$。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
4
1 2 3 5```

### 输出

```
1.333```

## 样例 #3

### 输入

```
4
1000000000 1000000000 1000000000 1000000000```

### 输出

```
0```

## 样例 #4

### 输入

```
4
1000000000 324219581 581395481 2319```

### 输出

```
-333332560.333333313```

# 题解

## 作者：char32_t (赞：5)

# 题解 AT1097 【差の平均】
------------
通过化简可得，原式=`(a[n]-a[1])/(n-1)`，所以只需要记录第一个数和最后一个数即可。

code：
```cpp
#include<cstdio>
int a[110];//数列 
double ans;
int main(){
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);//读入数据 
	ans=(double)(a[n]-a[1])/(n-1);//将答案转换为double类型 
	printf("%.3lf", ans);//输出 
    return 0;
}
```

---

## 作者：硫酸钒酰 (赞：3)

$\Huge\text{这题绝对不是普及-！}$

## 小学奥数题：

求	$\frac{1}{2}$+$\frac{1}{6}$+$\frac{1}{12}$+$\frac{1}{20}$+$\frac{1}{30}$+$\frac{1}{42}$+$\frac{1}{56}$+$\frac{1}{72}$+$\frac{1}{90}$的值。

呵呵，是不是看到题目就蒙了，想暴力求解……

## 其实完全不用！

如果你对数字十分敏感，就会看出

原式=$\frac{1}{1*2}$+$\frac{1}{2*3}$+$\frac{1}{3*4}$+$\frac{1}{4*5}$+$\frac{1}{5*6}$+$\frac{1}{6*7}$+$\frac{1}{7*8}$+$\frac{1}{8*9}$+$\frac{1}{9*10}$

=（1-$\frac{1}{2}$）+（$\frac{1}{2}$-$\frac{1}{3}$）+（$\frac{1}{3}$-$\frac{1}{4}$）+（$\frac{1}{4}$-$\frac{1}{5}$）+（$\frac{1}{5}$-$\frac{1}{6}$）+（$\frac{1}{6}$-$\frac{1}{7}$）+（$\frac{1}{7}$-$\frac{1}{8}$）+（$\frac{1}{8}$-$\frac{1}{9}$）+（$\frac{1}{9}$-$\frac{1}{10}$）

=1-$\frac{1}{2}$+$\frac{1}{2}$-$\frac{1}{3}$+$\frac{1}{3}$-$\frac{1}{4}$+$\frac{1}{4}$-$\frac{1}{5}$+$\frac{1}{5}$-$\frac{1}{6}$+$\frac{1}{6}$-$\frac{1}{7}$+$\frac{1}{7}$-$\frac{1}{8}$+$\frac{1}{8}$-$\frac{1}{9}$+$\frac{1}{9}$-$\frac{1}{10}$

=1-$\frac{1}{10}$=$\frac{9}{10}$

就是这么简单，就是列项相消的效果。

那么，我们回到这道题

 求[$A_2$-$A_1$+$A_3$-$A_2$+......+$A_n$-$A_(n-1)$] / ($N-1$) 的商
 
很明显，要分成两部分来求

$N-1$好办，但是要记得强制数据类型转换！
 
利用上面的方法，很容易得到：

[$A_2$-$A_1$+$A_3$-$A_2$+......+$A_n$-$A_(n-1)$]=$A_n$-$A_1$  

**（也需要进行强制数据类型转换！）** 

还有就是

# $\Huge\text{输出后换行！}$
 
所以综上所述，代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>		//还是那五个头文件
using namespace std;
int main()
{
	long long n,a[101],sum=0,i;  //题中N>=2且N<=100,记得sum清零，否则会发生奇怪的错误
	double ans;
	scanf("%lld",&n);    //scanf读入较cin快且能保留小数，故用scanf
	for(i=1;i<=n;i++)
	scanf("%lld",&a[i]);	//循环读入
	sum=a[n]-a[1];			//由上面的分析，显而易见
	ans=(double)(sum)/(double)(n-1);//注意强制数据类型转换的格式：(数据类型)(变量/常量)
	if(sum%(n-1)==0)		//特判，这是输出整数的情况
	printf("%.0lf\n",ans);	//整数是%.0lf
	else
	printf("%.3lf\n",ans);	//保留三位小数，注意：AT的题一定要换行！！！
	return 0;
}
```

就是这样，喵~~

---

## 作者：空城旧梦— (赞：3)

## 怎么能没有pascal！！
首先这是一题十分简单的数学题

看似很长的一段的算式抵消后会发现只剩下（a[n]-a[1]）/(n-1)

于是代码就变得非常简单

```pascal
var  a:array[1..100]of  longint;
     ans,n,i,j,k,l:longint;
     x:real;
begin
  readln(n);
  for  i:=1  to  n  do
    read(a[i]);
  ans:=trunc( (a[n]-a[1])/(n-1) );//直接计算第一个和最后一个
  if  ans*(n-1)=a[n]-a[1]  then//判断一下结果是否有小数
    begin
      writeln(ans);
      exit;
    end;
  x:=(a[n]-a[1])/(n-1);
  writeln(x:0:3);//保留小数点后三位
end.  
```

---

## 作者：МiсDZ (赞：3)

这绝对是一道小学奥数神题。。。蒟蒻的我竟然花了20秒写这题。。。我也不知道为什么是一道黄题。。。
#### 主要思路
许多项都抵消了，只剩下a$_n$-a$_1$。于是就有了下面这段代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	double a1,an;
	for(int i=1;i<=n;i++){
		int k;
		cin>>k;
		if(i==1)a1=k;//找到a1
		if(i==n)an=k;//找到an
	}
	printf("%.3lf",(an-a1)/(n-1));//输出结果，保留3位小数
}
```

---

## 作者：陈江河 (赞：1)

~~我也不知道为啥智能推荐给我推荐了这么水的题~~

~~日常上洛谷水题的我顺手就把这道题写了~~

我一开始没控制好精度结果WA了四次.....五次才过QAQ

这道题看着很水其实考察的选手的基本控制精度的能力

做完后翻了翻题解发现各位dalao判断整数的方法好难懂

作为一个蒟蒻我就直接丢出不用特判的代码叭QWQ

但愿管理给过
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iomanip>
using namespace std;
int main()
{
    int a,n;
    double ans = 0.0;
    cin >> n;
    for(int i = 1;i <= n;i ++)
    {
        cin >> a;
        if(i == 1) ans -= a;
        if(i == n) ans += a;
    }
    cout << fixed << setprecision(3) << ans/(n-1) << endl;
    return 0;
}
```

唯一需要注意的就是fixed和setprecision函数的结合应用，只用setprecision的话是有效数字....

一起用可以直接保留并舍弃零，就不需要特判整数辣！
两个函数应该都在iomanip库里，不确定的话可以直接用 `#include<bits/stdc++.h>` （嘿，嘿嘿...）

---

## 作者：封禁用户 (赞：0)

## ~~这是道红题&小学奥数题~~

经过一系列的抵消，最后会变为：

	(a[n]-a[1])/(n-1)
    
所以就很简单了，需要注意的就是三位小数

$$\bold{\text{史上最短主程序：(纯属娱乐，切勿模仿}}$$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define c cin>>n
#define f for(int i=1;i<=n;i++)cin>>a[i]
#define an ans=(double)(a[n]-a[1])/(n-1)
#define co printf("%.3lf",ans)
//一个神奇的东西
using namespace std;
int n;
double ans;
int a[100+10];
//定义变量
int main(){
	c;
	f;
	an;
	co;
    //六个字母+四个分号搞定qwq
	return 0;
}
```


---

## 作者：stry (赞：0)

这真的是一道
$\color{orange}\text{普及-}$ 的题吗？

确定不是 
 $\color{red}\text{入门}$
题吗

其实这题只需要知道原式=(a[n]-a[1])/(n-1)，所以只需要记录第一个数和最后一个数就OK了

这就不用发代码了吧

```cpp
#include<cstdio>
int a[110];//数列 
double he;
long long n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cout<<a[i];
    } 
    he=(double)(a[n]-a[1])/(n-1);//将答案转换为double类型 
    cout<<he;//输出 
    return 0;
}
```

我只是个蒟蒻，若有不足之处，请勿喷

---

## 作者：封禁用户 (赞：0)

这真的是一道
### $\color{orange}\text{普及-}$
的题吗？

~~确定不是$\color{red}\text{入门}$题吗~~

其实这题只需要知道原式=(a[n]-a[1])/(n-1)，所以只需要记录第一个数和最后一个数就OK了

这就不用发代码了吧
```cpp
#include<cstdio>
int a[110];//数列 
double he;
long long n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cout<<a[i];
    } 
    he=(double)(a[n]-a[1])/(n-1);//将答案转换为double类型 
    cout<<he;//输出 
    return 0;
}
```
我只是个蒟蒻，若有不足之处，请勿喷

---

## 作者：不到前10不改名 (赞：0)

//前面那些大佬都说可以化为(srx[n]-srx[1])/(n-1)的式子，但都没有原因，我来说一下，这是求和公式，求一组数的总和然后平均值
```
#include<stdio.h>
#include<math.h>
int srx[110],n,i; 
float sry;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++) 
    scanf("%d",&srx[i]);
    sry=1.0*(srx[n]-srx[1])/(n-1);//加一个1.0卡精度
    if(fabs(sry-(int)sry)<1e-10)//判零，好多人都没判断qwq~
    {printf("%.0lf\n",sry);//毕竟是小数，不能输出%d，printf就是麻烦呢~
    return 0;}
    printf("%.3lf",sry);//3位小数的精度足够
    return 0;
}
```

---

## 作者：远山淡影 (赞：0)

其实这只是一道很简单的奥数题，这个式子消掉之后就只剩下了[An-A1]/ (N-1).
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
using namespace std;
int n;
int a[21000];
double ans=0;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
	}
	ans=a[n]-a[1];//上面有说。。。 
	ans/=(n-1);
	if(fabs(ans-(int)ans)<1e-10)//很重要，判断是否是整数。 
	{
		printf("%.0lf\n",ans);
	}
	else printf("%.3lf\n",ans);
	return 0;
}
```

---

