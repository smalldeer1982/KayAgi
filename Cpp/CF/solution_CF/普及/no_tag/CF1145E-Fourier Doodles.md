# Fourier Doodles

## 题目描述

In this problem you have to solve a simple classification task: given an image, determine whether it depicts a Fourier doodle.

You are given a set of 50 images with ids 1 through 50. You are also given a text file labels.txt containing the labels for images with ids 1 through 20, which comprise the learning data set.

You have to output the classification results for images with ids 21 through 50 in the same format.

# 题解

## 作者：Trimsteanima (赞：12)

通过[此工具](http://www.ejectamenta.com/Imaging-Experiments/fourierimagefiltering.html)解析图片，可得到 (min(id, 25) + id) % (2 + id % 3)) > 0

---

## 作者：未来miss (赞：6)

# 按题目意思操作即可

[题目](https://www.luogu.org/problemnew/show/CF1145E)

这道题可以讲一下math库

在程序开头写下"uses math"即可使用math库的函数

十分方便
```pascal
函数介绍： 
 hypot 
原型：function hypot(x:float;y:float):float 
功能：返回直角三角形中较长边的长度，也就是sqrt(sqr(x)+sqr(y)) 
 ceil 
原型：function ceil(x:float):Integer 
功能：返回比参数大的最小整数 
引发错误：在x超出Integer的范围时会引发溢出错误 
 floor 
原型：function floor(x:float):Integer 
功能：返回参数小的最大整数 
引发错误：在x超出Integer的范围时会引发溢出错误 
 power 
原型：function power(base:float;exponent:float):float 
功能：返回base的exponent次方 
引发错误：在base为负数且exponent为小数时 
 intpower 
原型：function intpower(base:float;const exponent:Integer):float 
功能：返回base的exponent次方 
 ldexp 
原型：function ldexp(x:float;const p:Integer):float 
功能：返回2的p次方乘以x 
 log10 
原型：function log10(x:float):float 
功能：返回x的常用对数 
 log2 
原型：function log2(x:float):float 
功能：返回x以2为底的对数 
 logn 
原型：function logn(n:float;x:float):float 
功能：返回x以n为底的对数 
 Max 
原型：function Max(a:Integer;b:Integer):Integer 
function Max(a:Int64;b:Int64):Int64 
function Max(a:Extended;b:Extended):Extended 
功能：返回a与b中较大的一个 
 Min 
原型：function Min(a:Integer;b:Integer):Integer 
function Min(a:Int64;b:Int64):Int64 
function Min(a:Extended;b:Extended):Extended 
功能：返回a与b中较小的一个 
 arcsin 
原型：function arcsin(x:float):float 
功能：返回x的反正弦值，返回的是弧度指单位 
 arccos 
原型：function arccos(x:float):float 
功能：返回x的反余弦值，返回的是弧度指单位 
 tan 
原型：function tan(x:float):float 
功能：返回x的正切值，x以弧度为单位 
 cotan 
原型：function cotan(x:float):float 
功能：返回x的余切值，x以弧度为单位 
 arcsinh 
原型：function arcsinh(x:float):float 
功能：返回双曲线的反正弦 
 arccosh 
原型：function arccosh(x:float):float 
功能：返回双曲线的反余弦 
 arctanh 
原型：function arctanh(x:float):float 
功能：返回双曲线的反正切 
 sinh 
原型：function sinh(x:float):float 
功能：返回双曲线的正弦 
 cosh 
原型：function sinh(x:float):float 
功能：返回双曲线的正弦 
 tanh 
原型：function sinh(x:float):float 
功能：返回双曲线的正切 
 cycletorad 
原型：function cycletorad(cycle:float):float 
功能：返回圆的份数转换成弧度之后的值 
 degtorad 
原型：function degtorad(deg:float):float 
功能：返回角度转换成弧度之后的值 
 radtocycle 
原型：function radtocycle(rad:float):float 
功能：返回弧度转换成圆的份数之后的值 
 radtodeg 
原型：function radtodeg(rad:float):float 
功能：返回弧度转换成角度之后的值 
 MaxValue 
原型：function maxvalue(const data:Array[] of float):float 
function maxvalue(const data:Array[] of Integer):Integer 
function maxvalue(const data:PFloat;const N:Integer):float 
function maxvalue(const data:PInteger;const N:Integer):Integer 
功能：返回数组中的最大值 
 MinValue 
原型：function minvalue(const data:Array[] of float):float 
function minvalue(const data:Array[] of Integer):Integer 
function minvalue(const data:PFloat;const N:Integer):float 
function MinValue(const Data:PInteger;const N:Integer):Integer 
功能：返回数组中的最小值 
 sum 
原型：function sum(const data:Array[] of float):float 
function sum(const data:PFloat;const N:LongInt):float 
功能：求数组中所有数之和 
 sumsandsquares 
原型：procedure sumsandsquares(const data:Array[] of float;var sum:float; 
var sumofsquares:float) 
procedure sumsandsquares(const data:PFloat;const N:Integer; 
var sum:float;var sumofsquares:float) 
功能：将数组中的数求和放入num中，求平方和放入sumofsquares中 
 ** 
原型：function operator **(float,float):float(bas:float;expo:float):float 
function operator **(Int64,Int64):Int64(bas:Int64;expo:Int64):Int64 
功能：同等于Power，这是乘方的操作符 
```

```pascal
uses math;//调用math库
var
  i:longint;
begin
 for i:=21 to 50 do//暴力
     if (min(i,25)+i)mod(2+i mod 3)>0 then writeln(1)//依照题目来写
                                      else writeln(0); 
end.
```


---

## 作者：R·Buffoon (赞：4)

**打表好题！**
***
打表要用到**freopen**这个函数，相信有参加**NOIP**的**Oier**应该对这个函数很清楚

***

首先，用以下程序得到所有答案
~~~cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("answer.in","r",stdin);
    //因为本题没有输入，所以可以省略（其实打表的时候好像也用不到）
    //"r"代表read，即从文件读入，stdin代表文件读入，两者一起用
    
    freopen("answer.out","w",stdout);
    //会自动生成一个名为answer.out的文本文档在与这个程序同一个文件夹中
    //"w"代表write，即写入到文件，stdout代表写入到文件，两者一起用
    
    printf("int a[]={");//先输出一个数组，然后赋值
    for(int k=21;k<=50;++k)
        printf("%d,",((min(k,25)+k)%(2+k%3)>0)?1:0);
        //注意，这里每输出一个答案就跟一个半角逗号，这样是为了复制方便，不然要每个答案后人工加一个
        //输出的公式直接在题目中复制就行
        
    printf("};");//输出后半部分
    
    return 0;
}
~~~
运行该程序，可以在answer.out中看见这个
~~~cpp
int a[]={0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,};
~~~
当然，运行前首先要建一个名为“answer.in”的**空白**文本文档（其实把第一个freopen注释掉也行）

然后，删掉最后一个逗号，再把它复制粘贴到你的程序中，从0开始输出就行了（因为数组的第一个下标是0）

代码如下
~~~cpp
#include <bits/stdc++.h>
using namespace std;

int a[]={0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,
           1,1,1,0,1,1,1,1,1,0,1,0,1,1,1};
           //分两行看起来比较美观（看个人习惯）
           //空间大小放空可以防止数组开的过小
           //放空可以自动检测大小（好像是）

int main()
{
    for(int i=0;i<30;++i)//一共有30个数，从0输出到29（这个不会不理解吧）
        printf("%d\n",a[i]);//输出一个后要换行
        
    return 0;
}
~~~
这个题目打表的优势在哪里呢？我认为是减少常数，因为(min(i,25)+i)%(2+(i%3))>0常数可能~~有点大~~，但是练习一下打表总没错吧（逃
***
PS:再不过就重构！！！~~（这么完美的打表怎么会不过？）~~

---

## 作者：BCZSX (赞：4)

~~愚人节的题目，我也是醉了~~

直接上代码吧，也没什么好讲的……

```cpp
#include <cstdio>

using namespace std;

int main()
{
	printf("0\n1\n1\n0\n1\n1\n0\n1\n1\n1\n1\n1\n0\n1\n0\n1\n1\n1\n0\n1\n1\n1\n1\n1\n0\n1\n0\n1\n1\n1\n");
}
```

~~这么短的题解能过吗？~~

---

## 作者：CZQ_King (赞：2)

PHP大法好！

因为$PHP$标签外字符会被$PHP$解释器直接输出，所以我们直接把表写在代码里输出就可以过。

代码：
```php
0
1
1
0
1
1
0
1
1
1
1
1
0
1
0
1
1
1
0
1
1
1
1
1
0
1
0
1
1
1
```

---

## 作者：TCZN (赞：2)

我发现这道水题居然没有P党的题解

作为P党的蒻中蒻

就来发一篇吧

```pascal
var
  i,s:longint;
begin
 for i:=21 to 50 do
  begin
   if i<25 then s:=i
    else s:=25; //由于pascal没有min函数，所以需要手打一个
     if (s+i) mod (2+i mod 3) > 0 then writeln(1) 
      else writeln(0); //此地方需要特别注意，pascal的bool类型是输出true和false的，而c++的是输出1和0的，所以需要此判断，此处特别鸣谢 @WYXkk大佬
  end;
end.
```
附赠c++代码：
```cpp
#include <bits/stdc++.h> //van能头真好
using namespace std;
int main()
{
    for (int i = 21; i <= 50; i++)
      cout<<((min(i, 25) + i) % (2 + (i % 3)) > 0)<<endl; //c++真好，比pascal简单多了，直接ctrl+c搬运公式
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

这题其实很简单,按照题意操作就行了

如果($\min$($i,25$)$+i$) $\bmod$ ($2$+$i$ $\bmod$ $3$)$>0$ 输出$1$

否则输出$0$

代码 ($c++$):

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=21;i<=50;i++)
	{
		if((min(i,25)+i)%(2+i%3)>0)
			cout<<"1"<<endl;
		else
			cout<<"0"<<endl;
	}
	return 0;
}
```


---

## 作者：Terry88 (赞：1)

## 我来搞事了awa

各位巨佬都说这题目只要输出"011011011111010111011111010111"就可以AC，那我就不再对这串数字多说什么了，反正也是水题，水着也是水着，就用一些很~~神奇~~的方法来做。

首先，这串数字是一堆“0”和“1”，第一个想法就是把这个数字当成2进制数，然后输出~~awa~~。这一串数字总共有30个数字，把这30个数字全部压在一块QAQ
```pas
const t='011011011111010111011111010111';
var i,j,k:longint;
begin
  for i:=3 downto 1 do
  begin
    k:=0;
    for j:=i*10 downto 10*i-9 do
      k:=k<<1+ord(t[j])-ord('0');
    write(k,' ');
  end;
end.
```
```
运行结果：
943 747 950
```
所以说只需要输出就可以了（当然不是直接输出！）
```
const a:array[1..3]of integer=(950,747,943);
var i,j:longint;
begin
  for i:=1 to 3 do
    for j:=0 to 9 do
      writeln((a[i] mod (1<<(j+1)) div (1<<j)));
end.
```
首先，我们可以对"(950,747,943)"进行一个叫做插值的很神奇的东西，就是考试的时候的找规律神器。由于插值会涉及到一些过于难的数学知识，所以我尽量用小学生能懂得话来讲（我相信各位肯定有高中~~小学四年级~~文化）

首先，我们先对着一个很无辜的数列疯狂的求差，比如（3,7,13），这个的规律十分明显就是f(x)=$x^{2}$+$x$+1，但是因为我们今天讲的是插值，所以要用很简单的方法
```
3         7         13
   7-3=4     13-7=6
         6-4=2
```
所以这串数字的插值式子是$\left(3,4,2\right)$，因为所有的差都是确定的那不停的用加法可以让所有的值都确定这样就可以让整个式子都确定awa。

然后再放一些板子

$1=\left(1\right)$

$n=\left(1,1\right)$

$n^{2}=\left(1,3,2\right)$

$n^{3}=\left(1,7,12,6\right)$

我们只需要用上面这些东西凑出$\left(3,4,2\right)$即可。

首先，我们可以发现，如果说第3位确定了，那么使用1和$n$就无法让第三位改变值，那我们只需要从最高位一位一位除即可。

首先，我们显而易见先拿一个$n^{2}$，就有一个$\left(1,3,2\right)$了，还差一个$\left(2,1\right)$，那我们再拿一个$n$，还差一个$1$，最后再拿一个$1$即可。

最后得出$\left(3,4,2\right)$可以由$n^{2}+n+1$得出，这便是插值（比较烂的一种，O($n^{2}$）复杂度的插值。

那我们用同样的方法做$\left(950,747,943\right)$，可以得出结果

当$f\left(x\right)=\frac{399x^{2}-1603x+3104}{2}$时就可以了。那我们把这个东西带进代码里去，输出即可。
```
var i,j:longint;
begin
  for j:=1 to 30 do
    writeln(((399*sqr((j-1) div 10+1)-1603*((j-1) div 10+1)+3104) mod (1<<((j-1) mod 10+2)) div (1<<((j-1) mod 10+1))));
end.
```
[当场AC](https://www.luogu.org/record/26940711)

事实证明，红题确实可以很好的提升我们的能力，比如说通过这一道红题，又可以学会一种新的算法awa~~（只要你认真看完这一整篇题解的话）~~

本篇搞事题解到此结束，有疑问的可以私信骚扰作者。本题解由“一只爬行者，Terry88”共同编写

---

## 作者：4526_ (赞：1)

[题目链接](https://www.luogu.org/problem/CF1145E)

这题显然出自CF愚人节，so~

**主要思想：模拟**

大致思路：

1、把翻译里的公式复制下来

2、**注意细节**：mod 要改成 %，变量名不能弄错了（论本地编译的重要性

3、**头文件**：min函数在cmath里，当然如果用万能头就无所谓了

AC代码：

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int main(){
	for(int i=21;i<=50;++i){
		printf("%d\n",((min(i,25)+i)%(2+i%3)>0) ? 1 : 0);
	}
	return 0;
}
```

欢迎来[我的blog](https://www.luogu.org/blog/4526-Au/)看看

---

## 作者：WNico (赞：1)

## [原题](https://www.luogu.org/problem/CF1145E)

~~**水一发 超短**~~ $Python2$ :

```python
a=989573046
while a:
    print a%2
    a/=2
```
$C++$

```cpp
#include<iostream>
int main(){
	int ans = 989573046;
	do{
		std::cout<<ans%2<<"\n";
	}while(ans/=2);		//没有return 0 大家不要学
}
```

二进制转为十进制数

再将十进制数转为二进制输出即可

>~~这么短真的能过？？~~

---

## 作者：一个低调的人 (赞：0)

## 为什么会有只输出但又特别简单的题目QWQ

- 我要做一名好蒟蒻，不像下面的那些dalao那样打表！

- 作为一名好OIer，我又怎么能用万能头文件那样罪恶的东西呢！

- 于是，规规矩矩地写了个代码，就像这样：

```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	for(int i=21;i<=50;i++)
	{
		printf("%d\n",((min(i,25)+i)%(2+i%3) > 0)? 1: 0);
	}
	return 0;
}
```

## 于是就AC啦！

---

