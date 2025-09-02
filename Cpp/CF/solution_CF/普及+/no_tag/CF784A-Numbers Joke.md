# Numbers Joke

## 样例 #1

### 输入

```
3
```

### 输出

```
27
```

# 题解

## 作者：PC_DOS (赞：8)

同样地，这是一道愚人节题目。

一开始我以为这是纯粹的提交很多次然后用评测机返回的结果打表的题目，后来看了[别人的解说](http://www.cnblogs.com/shinianhuanniyijuhaojiubujian/p/7265135.html)发现其实这个数列有自己的名字: 史密夫数。

以下内容引用自[史密夫数-百度百科](https://baike.baidu.com/item/%E5%8F%B2%E5%AF%86%E5%A4%AB%E6%95%B0)

> 史密夫数（或作史密斯数）是指在某个进位下，它每一位数的数字的和相等於它因数分解（不用指数记数）中每一个因数的位数的和。

>在十进位下的史密夫数如下（OEIS中的数列A006753）：
4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645, 648, 654, 663, 666, 690, 706, 728, 729, 762, 778, 825, 852, 861, 895, 913, 915, 922, 958, 985, 1086

所以还是打表啊QwQ...
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int arrAns[30] = { 4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645 },nPos; //定义史密夫数列和需要输出的那个数的索引
	cin >> nPos; //输入索引
	cout << arrAns[nPos-1]; //打表输出
	return 0; //告辞
}
```

---

## 作者：无意识躺枪人 (赞：7)

~~大家看了讨论区都知道了，这题就是史密夫数~~

本蒟蒻上CF ~~xjb~~ 交了几个数据，根据返回的结果  ~~目测~~  上[神网站](http://oeis.org/)得出规律，这是史密夫数（十进制） ~~ORZ~~ OR2$\color{white}\text{这个屁股翘一点}$

```
史密夫数（或作史密斯数）是指在某个进位下，它每一位数的数字的和相等於它因数分解（不用指数记数）中每一个因数的位数的和
```

是不是完全没看懂？我们举个栗子

史密夫数：202（十进制）

2+0+2=$\color{red}4$

202=2 × 101

2+1+0+1=$\color{red}4$

懂了吧，那么史密夫数怎么求呢？

```c
#include <stdio.h>
#include <math.h>

int list[50]={2,3,0};//素数前两个

int judge(int x)/*判断是不是素数*/
{
	int i=0;
	while(list[i]*list[i]<=x)
	{
		if(x%list[i]==0)
		return 0;
		i++;
	}
	return 1;
}

int frist()/*素数表*/
{
	int i,k,j=1;
	for(i=5;i<=2100&&j<50;i++)
	{
		for(k=0;k<=j&&list[k]<=sqrt(i);k++)
		if(i%list[k]==0) break;
		if(k>j||list[k]>sqrt(i))
		{
			j++;
			list[j]=i;
		}
		else continue;
	}
	return 1;
}

int chg(int x) /*把此数各位数字进行相加*/
{
	int sum=0;
	while(x>10)
	{
		sum+=(x%10);
		x/=10;
	}
	sum+=x;
	return sum;
}

int zys(int x) /*求质因数的和*/
{
	int i,sum=0,y=x;
	for(i=2;i<=x;i++)
	if(judge(i)&&x%i==0)
	{
		if(i==y) return 1;
		sum+=chg(i);
		x/=i;
		i=1;
	}
	return sum;
}

int main()
{
	int i,n=0;
	frist();
	for(i=1;i<=10000;i++)
	{
		if(chg(i)==zys(i))
		{
			printf("%d\n",i);
			n++;
		}
	}
	printf("共%d个\n",n);
	return 0;
}
```

```pascal
var n,n1,n2,n3,i,a,b,s,s1,t:longint;
begin
write('n=');readln(n);
n3:=n;t:=0;
for n:=1 to n3 do begin
n1:=n;i:=2;s:=0;
while n1>=i do begin
while n1 mod i=0 do begin
b:=i;
while b>0 do begin
s:=s+b mod 10;
b:=b div 10;
end; {求质因数各位数字的和s}
n1:=n1 div i;
end;
i:=i+1;
end;
n2:=n;s1:=0;
repeat
a:=n2 mod 10;n2:=n2 div 10;
s1:=s1+a; {求此数各位数字的和s1}
until n2=0;
if (s=s1) and (i-1<>n) {排除素数} then begin
t:=t+1;writeln(n);
end;
end;
writeln(t);
readln;
end.
```

~~代码求解即可~~

打表天下第一！

自己打吧

看完点赞

---

## 作者：Rainbow_qwq (赞：5)

[原题](https://www.luogu.org/problem/show?pid=CF784A)

这居然是一道愚人节题目，看了都不知道要干什么，难怪是道紫题......

看了讨论区后才知道是要求第n个史密斯数。

~~注：这是正经题解，不是打表~~
```cpp
史密斯数是指在某个进位下，
它每一位数的数字的和相等于它因数分解中每一个因数的位数和。

如：27=3*3*3
2+7=9
3+3+3=9
```
由于这里只考虑十进制，会更简单一些。

首先是判断质数和计算一个数数位和。
```cpp
bool isprime(int n)//判断质数
{
	if(n<2)return 0;
	for(int i=2;i<=n/i;i++)
		if(n%i==0)return 0;
	return 1;
}
int sum(int n) 	   //数位和，可以用递归写
{
	if(n==0)return 0;
	return n%10+sum(n/10);
}
```
接下来是判断史密斯数的函数。
```cpp
int nextprime(int n)//找出下一个质数，方便快捷
{
	for(int i=n+1;;i++)
		if(isprime(i))return i;
}
bool issmith(int n)
{
	if(isprime(n))return 0;				//n为质数就砍了
	int sum1=0,sum2=sum(n);				//sum1为因数的位数和，sum2为n的位数和
	while(n>1)//分解质因数
	{
		for(int i=2;i<=n;i=nextprime(i))//从小到大一个个找
			if(n%i==0)
			{
				sum1+=sum(i);
				n/=i;
				break;
			}
	}
	return sum1==sum2;
}
```

主函数很简单，我就不贴了，大家自己写。

（大家不要复制代码哦）

---

## 作者：Ace_Radom (赞：3)

### 估计很多人第一眼看这题面是~~一脸懵逼~~。

楼上好多dalao说了，这是一道愚人节题目。

其实就是要输出**史密斯数中第 n 个**。

## 打表代码：

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
	int SmithNumber[31] = { 0 , 4 , 22 , 27 , 58 , 85 , 94 , 121 , 166 , 202 , 265 , 274 , 319 , 346 , 355 , 378 , 382 , 391 , 438 , 454 , 483 , 517 , 526 , 535 , 562 , 576 , 588 , 627 , 634 , 636 , 645 };
    //史密斯数预处理
	int n;
	cin >> n;
	cout << SmithNumber[n] << endl;
	return 0;
}
~~~

## 后面是正经的分析。

## 仅仅是要过了这题的可以不看。

那什么是史密斯数呢？

[百度百科传送门](https://baike.baidu.com/item/%E5%8F%B2%E5%AF%86%E6%96%AF%E6%95%B0/2564845?fr=aladdin)

	其实史密斯数就是指在某一进制下的一个数。
    它每一位数的数字的和相等于它的每一个因数的每一位数字之和。

我们可以举几个例子来说明一下：

	先看4
    	将4因式分解，得：4 = 2 × 2 
        2 + 2 = 4
    再看一个22
    	将22因式分解，得：22 = 2 × 11
        2 + 1 + 1 = 2 + 2 = 4
     最后看一个27
     	将27因式分解，得：27 = 3 × 3 × 3
        3 + 3 + 3 = 2 + 7 = 9
        
~~应该懂了~~

按照史密斯数的定义可以码一个程序，用它来求史密斯数。

## C++求史密斯数代码：

~~~C++
#include<bits/stdc++.h>
using namespace std;
bool IsPrime( int n ){  //判断是否是质数
    if ( n < 2 ) 
		return 0;
    for ( int i = 2 ; i <= n / i ; i++ )
        if ( n % i == 0 )
			return 0;
    return 1;
}
int FindSum( int n ){  //求出数位和
    if ( n == 0 )
		return 0;
    return ( n % 10 + FindSum( n / 10 ) );
    //这里用递归明显方便
}
int NextPrime( int n ){  //找出下一个质数
    for ( int i = n + 1 ; ; i++ )
        if ( IsPrime( i ) )
			return i;
}
//主要是为了方便后面分解质因数
int DPFSum( int n ){  //求出n各个因数的和
	int ans = 0;
	while ( n > 1 )  //分解质因数
	{
		for ( int i = 2 ; i <= n ; i = NextPrime(i) )//从小到大慢慢找
        //NextPrime多方便
		{
	        if ( n % i == 0 )
	        {
	            ans += FindSum(i);
	            n /= i;
	            break;
	        }
		}
	}
	return ans;
}
bool IsSmith( int n ){  //判断史密斯数
    if ( IsPrime( n ) ) 
		return 0;             
    //如果n是质数就不可能是史密斯数了，可以直接舍去
    int sum1 = DPFSum( n ),sum2 = FindSum( n );       //sum1为n的因数的位数和，sum2为n的位数和
    if ( sum1 == sum2 )  //是史密斯数
    {
    	return true;
	}
	return false;
}
int main(){
	int n;
	cin >> n;
	for ( int i = 1 ; i <= n ; i++ )
	{
		if ( IsSmith( i ) )
		{
			cout << i << endl;
		}
	}
	return 0;
}
~~~

再把它弄进程序即可。

## 正经的C++做法（部分）：

~~~C++
#include<bits/stdc++.h>
using namespace std;
......
int main(){
	int n,k = 0;  //k 用来记录是第几个了
	cin >> n;
	for ( int i = 1 ; ; i++ )
	{
		if ( IsSmith( i ) )
		{
			k++;
		}
        if ( k == n )  //找到第 n 个，直接退出
        {
        	cout << i << endl;
            return 0;
        }
	}
	return 0;
}

---

## 作者：gwx123456 (赞：1)

**愚人节题目**

这是纯粹的提交很多次然后用评测机返回的结果打表的题目

当然，这题也是有专有名词的数列的：史密夫数

史密夫数：是指在某个进位下，它每一位数的数字的和相等於它因数分解（不用指数记数）中每一个因数的位数的和。

在十进位下的史密夫数如下（OEIS中的数列A006753）： 4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645, 648, 654, 663, 666, 690, 706, 728, 729, 762, 778, 825, 852, 861, 895, 913, 915, 922, 958, 985, 1086

看完上面之后，我们就可以打表了

```
#include <bits/stdc++.h>//万能头
using namespace std; //命名空间
int arrAns[30] = { 4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645 },nPos; //定义史密夫数列和需要输出的那个数的索引
int main(){//主函数
    cin >> nPos; //输入索引
    cout << arrAns[nPos-1]; //打表输出
    return 0; //告辞
}
```


---

## 作者：松毛虫 (赞：1)

这个题目要求就是求史密夫数，根据在baidu中搜索到的史密夫数打表就可以了！
```cpp
#include<iostream>
using namespace std;
int main()
{
    const int ava[]={4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645};//这里要讲解的是，const的数组是不需要写有多长的，自己就会计算长度
    int qvq;
    cin>>qvq;
    cout<<ava[qvq-1];//为什么要减去1呢？因为数组开始是0，但是我们没有第0位数字，是从1开始的
    return 0;
}
```


---

## 作者：pV_equals_nRT (赞：1)

# 史密斯数
先来一发百科：\
美国有一位数字家名叫阿尔伯特·威兰斯基，他姐夫史密斯非常喜欢研究数学，所以两人经常在一起研讨各种数学问题。有时，两人碰不到一起，就习惯性地用电话交流。

一天，两人刚结束电话交谈，史密斯突然灵感来临，对威兰斯基的电话号码"4937775"产生了兴趣，总觉得这是个特别的数。可它的特殊之处究竟在哪儿呢?史密斯开始思索考证起来，他先把4937775分解质因数:4937775=3×5×5×65837，然后再把4937775所有质因数各位上的数字相加得:3+5+5+6+5+8+3+7=42，接着他又把4937775各位上的数字相加得:4+9+3+7+7+7+5=42

秘密终于找到了，原来这两个和相等。这真有意思，难道是巧合么?有没有其他的数也有此特点呢?史密斯不能解答这个问题。不过，他的这一发现引起了许多数学家的浓厚兴趣。数学家们带着这个疑问，纷纷对这一现象进行了研究。

结果发现，有许多数具有这样独特的性质，其中最小的数是4。大家不妨检查一下，4=2×2，2+2=4。类似的有，22=2×11,2+2=2+1+1;27=3×3×3，2+7=3+3+3。随着研究的不断深入，他们发现，在0至10000之间，共有376个这样的数;并且估计在0至100000之间有3300个这样的数。因为这些有趣数的发现，追本溯源是史密斯的功劳，所以数学家们把这样的数叫做"史密斯数"。
### 居然没有人用switch？
### 这应该也算是打表的一种
AC代码：
```cpp
#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);//输入
	switch(n)//判断
	{
		case 1:printf("4");break;
		case 2:printf("22");break;
		case 3:printf("27");break;
		case 4:printf("58");break;
		case 5:printf("85");break;
		case 6:printf("94");break;
		case 7:printf("121");break;
		case 8:printf("166");break;
		case 9:printf("202");break;
		case 10:printf("265");break;
		case 11:printf("274");break;
		case 12:printf("319");break;
		case 13:printf("346");break;
		case 14:printf("355");break;
		case 15:printf("378");break;
		case 16:printf("382");break;
		case 17:printf("391");break;
		case 18:printf("438");break;
		case 19:printf("454");break;
		case 20:printf("483");break;
		case 21:printf("517");break;
		case 22:printf("526");break;
		case 23:printf("535");break;
		case 24:printf("562");break;
		case 25:printf("576");break;
		case 26:printf("588");break;
		case 27:printf("627");break;
		case 28:printf("634");break;
		case 29:printf("636");break;
		case 30:printf("645");break;
	}
} 
```
话说这么水的一道题怎么是紫题呢？~~不应该是黑题吗？~~\
~~第N次发题解，求过QWQ~~

---

## 作者：wzm2007 (赞：1)

   	此题是求史密夫数
   	思路很简单,打表即可

------------

   	#include<iostream>
    using namespace std;
    int a[50]={4,22,27,58,85,94,121,166,202,265,274,319,346,355,378,382,391,438,454,483,517,526,535,562,576,588,627,634,636,645};  //打表
    int main()
    {
        int n;
        cin>>n;  //项数
        cout<<a[n-1];  //输出
        return 0;
    }

---

## 作者：CZQ_King (赞：0)

这是一道愚人节题目，求的是[史密夫数](http://oeis.org/A006753)。（其实题目就告诉你了，史密夫数有个别名叫``joke number``）

> 史密夫数（或作史密斯数）是指在某个进位下，它每一位数的数字的和相等於它因数分解（不用指数记数）中每一个因数的位数的和。
    ------百度百科
    
本题是在$10$进制下的，所以比较简单

例如说，拿$85$做例子

$85=5\times17$

然后$85$的数字和就是$8+5=13$

然后$5+1+7$也等于$13$，所以$58$就是史密夫数

~~居然没有py？！~~

蒟蒻发一个打表（$Python2$）
```
print[0,4,22,27,58,85,94,121,166,202,265,274,319,346,355,378,382,391,438,454,483,517,526,535,562,576,588,627,634,636,645][input()]# 将表打出来，输入n就输出第n个，注意是从0开始
```
~~史密夫数的发现是要从1975年袁隆平研制成功杂交水稻制种技术说起~~

---

