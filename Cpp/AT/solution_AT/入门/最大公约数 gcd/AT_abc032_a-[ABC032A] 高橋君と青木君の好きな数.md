# [ABC032A] 高橋君と青木君の好きな数

## 题目描述

青木君喜欢能被整数 $a$ 整除的数。高桥君喜欢能被整数 $b$ 整除的数。

请输出不小于 $n$ 的整数中，既能被 $a$ 整除又能被 $b$ 整除的最小的数。

## 说明/提示

### 样例解释 1

$12$ 是大于等于 $8$ 的整数中，能被 $2$ 和 $3$ 同时整除的最小值。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
12```

## 样例 #2

### 输入

```
2
2
2```

### 输出

```
2```

## 样例 #3

### 输入

```
12
8
25```

### 输出

```
48```

# 题解

## 作者：云浅知处 (赞：7)

首先，审题！
***
输入$a,b,n$，请输出大于等于$n$的$a$和$b$的最小公倍数
***
思路：

$1.$因为答案需要求大于$n$的$a$,$b$的最小公倍数，而公倍数都是最小公倍数的倍数，所以我们可以开一个循环，依次计算$a$,$b$的最小公倍数的$1$倍，$2$倍，$3$倍，$.\cdots\cdots$，直到这个公倍数大于等于$n$。

这里是程序图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g74pff8b.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![](https://cdn.luogu.com.cn/upload/image_hosting/0cgqo6p7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

(由于某种神奇的原因，一张完整的、竖着的图放不出来，不过这样也能看）

$2.$两个数的最小公倍数怎么求呢？
***
推导如下：

设两个数$a,b$的最大公因数为$m$

则一定有$a=mx,b=my\ (\text{最大公因数的性质)}$

则$a,b$的最小公倍数为$m\cdot x\cdot y\ \text{（最小公倍数的定义）}$

$\therefore a,b$的最小公倍数与最大公因数的乘积为

$$m\cdot m\cdot x\cdot y=m^2xy$$

又$\because a=mx,b=my$

$\therefore ab=mx\cdot my=m^2xy$

于是：$a$与$b$的乘积等于$a,b$的最小公倍数与最大公因数的乘积

即$ab=\operatorname{lcm}(a,b)\times\gcd(a,b)$

整理得$\operatorname{lcm}(a,b)=\dfrac{ab}{\gcd(a,b)}$

***
$3.C\!+\!+$中自带有求最大公因数的程序：```__gcd(a,b)```

它的返回值是$a,b$的最大公因数。
***
下面，开始写代码啦！

代码如下：
```cpp
#include<algorithm>
#include<bitset>
#include<bits/stdc++.h>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstddef>
#include<csetjmp>
#include<cstdarg>
#include<climits>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iosfwd>
#include<iterator>
#include<iostream>
#include<list>
#include<locale>
#include<limits>
#include<memory>
#include<map>
#include<numeric>
#include<new>
#include<ostream>
#include<queue>
#include<stdexcept>
#include<set>
#include<stack>
#include<sstream>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<wctype.h>
#include<wchar.h>//一大波头文件汹汹来袭
using namespace std;
int main(){
	int a,b,n,k;//a,b,n如题意，k是a,b的公倍数
	cin>>a>>b>>n;//输入
	for(int i=1;;i++){//枚举1*k,2*k,......
		k=(a*b)/(__gcd(a,b))*i;//将a,b的最小公倍数的i倍赋值给k
		if(k>=n){//判断k与n的大小
			cout<<k<<endl;//如果k大于等于n，输出k
			return 0;//并结束程序
		}
	}
	return 0;//感觉这里的这个return 0没什么用，保险起见还是加上了
}
```
***
运行结果看[这里](https://www.luogu.com.cn/record/31871519)
***
最后：$\Huge\text\color{red}\colorbox{yellow}{共创文明洛谷，拒绝Ctrl+C!!!}$

---

## 作者：CZQ_King (赞：6)

## 这道题，不用暴力，不用取反，只要向上取整!!

------------
### 思路：
1. 因为答案需要是$a$和$b$的最小公倍数，如果要满足这个数大于等于$n$，只需要翻$ceil(n/a$和$b$的最小公倍数$)$倍就可以了。
2. 在$C++$里，有一个可以求$a$和$b$的最大公因数的函数，叫做$_{--}gcd(a,b)$，并且我们已经知道$a$和$b$的最小公倍数$=a*b/_{--}gcd(a,b)$,所以就可以求出答案了。
3. 推导出公式$ans=ceil(\frac{n}{(a*b/_{--}gcd(a,b))})*(a*b/_{--}gcd(a,b))$
------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
#define z (a*b/__gcd(a,b))//先来个宏定义，好看一点
using namespace std;
int a,b,n;
int main(){
    cin>>a>>b>>n;//输入
    cout<<ceil((double)n/z)*z<<endl;//按照公式模拟
    return 0;//结束
}
```

---

## 作者：林家三少 (赞：4)

今天本蒟蒻又来发题解了！(要fAKe,要fAKe)

这题我用的方法和思路和 [墨染纸上](https://www.luogu.org/space/show?uid=130069) 大佬的第二种方法差不多([链接](https://www.luogu.org/problemnew/solution/AT1741?page=2))

不过我是用函数+累加来做的,思路就是先求出a,b的最小公倍数,然后如果条件不符合,就让最小公倍数乘2,那为什么我要定个别的变量累加呢？我来举个例子:

	假设gs(a,b的最小公倍数)=10
    那么他的2倍,3倍,4倍应该是
    20,30,40
    可是如果我们用gs*=2这个语句的话,会发现结果是
    20,40,80
    那么这样就不行了,所以我还用了一个m(也是a,b的最小公倍数),然后gs+=m,而m又不会改变,这样就OK了

这就是我的思路,接下来上程序:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>  //用min or max是要打的文件头
using namespace std;
int a,b,n,gs,m;  //定义变量,个人建议定在函数上面,不然可能会和函数变量重复了
int Minimum(int x,int y)  //函数求最小公倍数
{
	for(int i=max(x,y);i<=x*y;i++)  //就是一个普通的求最小公倍数的for
	{
		if(i%x==0&&i%y==0)
			return i;  //函数这里不用再加个break了,因为它会return以后自动退出
	}
}
int main()
{
	cin>>a>>b>>n;
	gs=Minimum(a,b);  //a,b的最小公倍数
	m=Minimum(a,b);  //这个是用来累加最小公倍数的变量
	for(int i=1;i<=10000;i++)
	{
		if(gs>=n)  //如果条件满足了
		{
			cout<<gs<<"\n";  //输出,记得要换行
			return 0;  //这里就可以直接结束了
		}
		gs+=m;  //否则可以再加a,b的最小公倍数
	}
	return 0;
}
```


---

## 作者：向日葵小班 (赞：3)

### 我不用一坨乱七八糟的，直接暴力（因为是$\color{red}\text{红题}$吗！）


## 思路：

**1.定义a,b,n**

**2.输入a,b,n**

**3.从n开始无限循环，用i作下标**

**4.判断，如果i%a==0&&i%b==0就输出i（P.S：AT$\color{red}\text{要换行}$，不换$\color{red}\text{WA}$两行泪），然后结束(return 0)**

## 放代码,十行:
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,b,n;//定义a,b,n
int main()
{
	cin>>a>>b>>n;//输入a,b,n
	for(int i=n; ;i++)//从n开始无限循环，用i作下标
    if(i%a==0&&i%b==0){cout<<i<<endl;return 0;}//判断，如果i%a==0&&i%b==0就输出i，然后结束(return 0)
    return 0;
}
```

## 最重要的一点：

$\color{red}\text{AT要换行，爆零两行泪！！！}$

$\color{red}\text{AT要换行，爆零两行泪！！！}$

$\color{red}\text{AT要换行，爆零两行泪！！！}$

$\color{red}\text{AT要换行，爆零两行泪！！！}$

$\color{red}\text{AT要换行，爆零两行泪！！！}$



---

## 作者：I_will (赞：1)

这道题我做了好多次WA，终于AC。
首先是要判断最小公倍数：
```
x=__gcd(a,b);
x=a*b/x;
```
我运用一个函数来解决！
```
if(n%o==0&&n>=o)return n;
else return (n/o+1)*o;
```    
最后输出没了

	cout<<h<<endl;\\注意：有换行，不然全错【所有的AT题最后都要“\n”（换行）】。
---------
完整程序：
```
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
long long a,b,n;
long long h,x;
long long panduan(long long o)
{
	if(n%o==0&&n>=o)return n;
	else return (n/o+1)*o;
}
int main()
{
	cin>>a>>b>>n;
	x=__gcd(a,b);
	x=a*b/x;
	h=panduan(x);
	cout<<h<<endl;

	
	return 0;
}
```

---

## 作者：不到前10不改名 (赞：1)

//好久没做at的题目了，换行都忘了
```
#include<stdio.h>
#include<math.h>
int n,a,b,t,i;
int lgx(int x,int y)//gcd，最大公因数
{
    int i;
    while(y)//碾转相除法（欧几里得）
    {i=x%y;
    x=y;
    y=i;}
    return x;
}
int main()
{
    scanf("%d%d%d",&a,&b,&n);
    t=a*b/lgx(a,b);//很明显，两数的最小公倍数就是两数之积除以最大公约数
    if(n%t)//不能为n的整倍
    printf("%d\n",(n/t+1)*t);//此处向上取整
    else//为n的整倍
    printf("%d\n",n/t*t);
    return 0;
    }
```

---

## 作者：wushuang0828 (赞：1)

**暴力……**

没有什么可以说的了

只是题目有bug，不是“最小公倍数”，其它只能说water

接下来，你们最喜欢的环节到了……
```pascal
var
 a,b,n,k:longint;
begin
 readln(a);//输入
 readln(b);//输入
 readln(n);//输入
 k:=n;//由于题目说答案大于等于n，那就从n开始枚举
 while (k mod a<>0) or (k mod b<>0) do inc(k);//寻找a和b的公倍数，因为是从n开始枚举所以一定大于等于n
 writeln(k);//输出
end.//结束
```

---

## 作者：Ophelia (赞：1)

$\color{blueviolet}\text{暴力出奇迹}$
题目的意思实际上误导了我们，题目实际上不是最小公倍数，所以不用最小公倍数的算法。题目要我们求的，**是a与b最小的不小于n的公倍数**。所以，我们暴力。没错，暴力。
```
#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int main()
{
	int a,b,n,x;
	cin>>a>>b>>n;//输入，准备暴力枚举
	for(int i=1;i<=1000000;i++)//1000000对于AT这么水的题库够了
	{
		if(i>=n&&i%a==0&&i%b==0)//判断
		{
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Star_Wind (赞：0)

# c++大法好！！！！！

__gcd（）大法好！！！

因为我们知道a,b的最小公倍数是a*b/（a,b的公约数）

所以先求出a,b的最小公倍数，之后while1找就行了

简单代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,p,s;
int main()
{
    cin>>a>>b>>n;
    p=a*b/__gcd(a,b);
    s=p;
    do
    {
    	if(p<n) p+=s;
    	else {cout<<p<<endl;break;}
	}
	while(1);
    return 0;
}
```


---

## 作者：hjxxcbq (赞：0)

# 这道题不难!
[题目传送门](https://www.luogu.org/problemnew/show/AT1741)

要注意，是求**a和b的最小的大于或等于n的公倍数**，而不是直接求a和b的最小公倍数。

第一种办法：只要从n开始枚举，枚举到可以除到a,b没有余数为止。

献上代码：
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a,b;//定义a,b,n
int main()
{ 
cin>>a>>b>>n;//输入a,b,n
for(int i=n;;i++)
{
if(i%a==0&&i%b==0)//判断
{
cout<<i;//判断到就输出
break;//停止，也可以是return 0;
}
}
return 0;
}
```

### 但是错的！

[红的一片](https://www.luogu.org/recordnew/show/19186186)


哦！原来是没换行。

```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a,b;//定义a,b,n
int main()
{ 
cin>>a>>b>>n;//输入a,b,n
for(int i=n;;i++)
{
if(i%a==0&&i%b==0)//判断
{
cout<<i<<endl;//判断到就输出，注意要换行！
break;//停止，也可以是return 0;
}
}
return 0;
}
```

[AC](https://www.luogu.org/recordnew/show/19186363)

第二种办法：把较大的数翻倍，翻到是a和b的最小的大于或等于n的公倍数。

```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a,b,c;
int main()
{ 
cin>>a>>b>>n;
c=max(a,b);
if(c%a==0&&c%b==0&&c>=n)//如果a和b较大数是a和b的最小的大于或等于n的公倍数
{
cout<<c<<endl;
return 0;
}
for(int i=2;;i++)//从2开始翻
{
if(c%a==0&&c%b==0&&c>=n)//判断
{
cout<<c<<endl;//输出c，要换行！
break;
}
c/=(i-1);//还原。
c*=i;再乘。
}
return 0;
}
```

[AC](https://www.luogu.org/recordnew/show/19186563)

没想到第一种方法比第二种方法还好！

第一种方法，枚举：

代码 C++，0.17KB

耗时/内存 18ms, 256KB

第二种方法，翻倍：

代码 C++，0.27KB

耗时/内存 18ms, 256KB

耗时/内存是一样。

但第一种是0.17KB，而第二种是0.27KB！

0.17KB>0.27KB

所以枚举吧......

---

## 作者：zy_turtle (赞：0)

题目其实挺简单的。。。。。。   
就是用一个GCF函数（greatest common factor，最大公因数）和一个LCM函数（lowest common multiple，最小公倍数）
   
     
     
代码实现长这样：
```cpp
int gcf(int a, int b) {
	if (b == 0) {
		return a;
	}

	return gcf(b, a % b);
}

int lcm(int a, int b) {
	int n = gcf(a, b);

	return a / n * b;
}
```

   
然后呢，先存a和b的lcm，再存个副本（后面有用）,然后和n比较  
 如果是>=n 就直接输出  
 不是的话,就用while循环  
 每次都把那个lcm加上副本（lcm本身）  
 当>=n时输出，结束，就行了
 
 代码实现长这样：  
 ```cpp
#include <iostream>
using namespace std;

int gcf(int a, int b);
int lcm(int a, int b);

int main() {
	int a, b, n;
	int t = 0;

	cin >> a >> b >> n;

	t = lcm(a, b);
    int te = t;
	if (t >= n) {
		cout << t << endl;
		return 0;
	}

	while (true) {
		t += te;
		if (t >= n) {
			cout << t << endl;
			break;
		}
	}

	return 0;
}

int gcf(int a, int b) {
	if (b == 0) {
		return a;
	}

	return gcf(b, a % b);
}

int lcm(int a, int b) {
	int n = gcf(a, b);

	return a / n * b;
}

```  
  
[AC](https://www.luogu.org/record/show?rid=15074196)

---

## 作者：climax (赞：0)

这道题太容易了，只需从小的那个数开始，暴力枚举，直到找出那个符合要求的数就可以了。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int i,j,a,b,n,k;
  cin>>a>>b>>n;//输入a，b两个数以及n。
  if(a>=b)//如果前面的数比后面的大，就交换它们的位置。
  {
  	i=a;
  	a=b;
  	b=i;
  }//这里之所以这么做是为了后面更好进行操作一点。
  if(a==n&&b==n)//特判，如果a和b相同，且a和b也等于n，那这个大于等于n的a和b的公倍数，就是a和b本身。
  {
    cout<<a<<endl;
    return 0;
  }
  for(i=a;;i++)//暴力枚举
    if(i%a==0&&i%b==0&&i>=n)//如果这个数是符合要求的，就输出这个数。
    {
      cout<<i<<endl;//要换行
      return 0;//结束了
	}
  return 0;
}
```

---

## 作者：RioBlu (赞：0)

__gcd(A,B):求A和B的最大公约数

A*B/__gcd(A,B):求A和B的最小公倍数

!(!(A%B))):取两次反，目的是为了把>1的变成1
```
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,ans;
int main()
{
	cin>>a>>b>>c;
	ans=a*b/__gcd(a,b);//求A和B的最小公倍数
	cout<<(c/ans+!(!(c%ans)))*ans<<endl;
}
```

---

## 作者：Yoo_ (赞：0)

看了看他们的题解，貌似没有一个用函数的，那我就来补个缺吧
其实这道题就是个暴力题
```
#include<bits/stdc++.h>
#define noiprp 600//祝你们AKnoip！！！
using namespace std;
int youxiu(int a,int b,int n)
{
    for(int i=n;1;i++)//用i表示第一个大于n的ab的公倍数
    {
        if(i%b==0&&i%a==0)//公倍数不解释
        {
            return i;//i是返回值
        }
    }
}
int main()
{
    int a,b,n;
    cin>>a>>b>>n;
    cout<<youxiu(a,b,n)<<endl;//endl要注意
    return 0;
}
```

---

