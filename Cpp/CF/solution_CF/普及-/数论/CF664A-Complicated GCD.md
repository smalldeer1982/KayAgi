# Complicated GCD

## 题目描述

【问题描述】 给你若干个整数，它们是a,a+1,a+2,…,b，请求出它们的最大公约数，即 gcd(a, a+1, a+2, …, b)。

## 样例 #1

### 输入

```
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
61803398874989484820458683436563811772030917980576 61803398874989484820458683436563811772030917980576
```

### 输出

```
61803398874989484820458683436563811772030917980576
```

# 题解

## 作者：fsy_juruo (赞：6)

终于能写一道数论题的题解啦

题目意思就是求gcd(a,a+1,...,b)

乍一看，这道题貌似是一道模拟题，但看数据范围，果断放弃...

所以,这道题应该怎么解呢？其实，有一个结论，就是gcd(a,a+1)永远等于1.

如果不能理解的话，我们可以使用在OI中比较常用的辗转相除法求gcd这个方法来证明一下

	int gcd(int x,int y){
		return x%y==0? y:gcd(y,x%y);
	}
    
主要意思就是gcd(x,y)=gcd(y,x mod y)

然后，把x=a+1,y=a带入，得：gcd(a+1,a)=gcd(a,1)

因为gcd(a,1)=1,所以gcd(a+1,a)=1

命题得证。

回到原题，因为gcd(a,a+1)=1,所以当a<b时，必然存在一组相邻的数，因为相邻的数互质，所以gcd(a,a+1,..,b)=1

当a=b时，答案即为a

分析完毕。

在代码实现时，注意要用string存储，不要用long long！会炸的！

AC代码：

	#include<bits/stdc++.h>
	using namespace std;
	int main(){
  	  string a,b;
  	  cin>>a>>b;

  	  if(a==b)cout<<a<<endl;

    	else puts("1");
   	return 0;
	}
    



---

## 作者：hensier (赞：1)

看到$GCD$，本蒟蒻两眼放光，立刻点进去了。

然而$1\le a\le b\le 10^{100}$——高精度？不过本蒟蒻发现，要求$[a,b]$区间内所有整数的$GCD$。

为了简化代码，我们不妨假设任意差为$k(k>0)$的正整数都互质。设一个数为$x(x>0)$，则另一个为$x+k$。

假设$x$与$x+k$有最大公约数$p(p>1)$。则$x\%p=0,(x+k)\%p=0$。因此，这时必定满足$k\%p=0$。所以$k>=p$，满足这个的时候$x,x+k$有最大公约数。

因此$k<p$的时候，$x,x+k$互质。因为$p>1$，所以$k<=1$的时候，满足$x,x+k$互质。因为$k>0$，所以$k=1$。

所以$x,x+1$互质。

得到这个结论之后，我们可以用反证法进一步验证：

设这两个数分别为$n,n+1$。

假设$n,n+1$有最大公约数$p(p>1)$。这个时候设$n=ap,n+1=bp$。则$ap+1=bp$。所以$bp-ap=1$。所以$p(b-a)=1$。因此只能有$p=b-a=1$。而我们假设$p>1$，所以假设不成立。

因此$n,n+1$互质。

那么，对于$n,n+1,...,n+k$的最大公约数，那就只能是$1,n+2,...,n+k$的最大公约数，以此类推，也就只能是$1$了。当然，有可能会出现输入的两个数相等的情况，这个时候就要输出这两个数中的任意一个。

推理的过程较长，但是代码却很容易理解。

$C$语言（~~较长~~）：

```cpp
#include<cstdio>
char a[110],b[110];
int len(char x[])//返回字符数组长度
{
    int i=0;
    for(;x[i];i++);
    return i;
}
bool check(char x[],char y[])
{
    if(len(x)-len(y))return 0;//长度不相等直接返回0
    for(int i=0;x[i];i++)if(x[i]-y[i])return 0;//有一位不相等就返回0
    return 1;//否则返回1
}
int main()
{
    scanf("%s%s",a,b);//输入
    if(check(a,b))printf("%s",a);//a与b内容完全相同就输出a
    else printf("1");//否则输出1
}
```

$C++$（直接法）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    string a,b;
    cin>>a>>b;
    cout<<a==b?a:1;
}
```

$C++$（数组赋值法）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    string a,b,x[]={"1",""};
    cin>>a>>b;
    x[1]=a;
    cout<<x[a==b?1:0];
}
```

---

## 作者：andyli (赞：0)

题意：  
求$\gcd(a,a+1,a+2,...,b-1,b)$。  
$1\leq a\leq b\leq 10^{100}$。  

注意到$\gcd(a,a+1)=1$  
因此$a<b$时答案为$1$，否则答案为$a$。  

代码如下（[快读模板](https://andyli.blog.luogu.org/read-template)）：  
```cpp
const int maxn = 105;

char A[maxn], B[maxn];
int main()
{
    io.read(A);
    io.read(B);
    if (!strcmp(A, B))
        printf("%s\n", A);
    else
        printf("1\n");
    return 0;
}
```

---

## 作者：皮卡丘最萌 (赞：0)

这题咋一看很吓人，但是仔细想想，还是很简单的。

因为相邻2个自然数的最大公因数为1，如果他们的公约数不为1，那么他们的差值就至少为2，这就不满足相邻自然数的条件了。

这样题目就只有2种情况了：

 1.a=b，直接输出a；
 
 2.a≠b，因为相邻2个自然数的最大公因数为1，所以这些数的最大公因数为1。
 
但是由于数据范围，pascal需要用字符串来处理。

放代码：
```pascal
var s,s1:string; k:longint;
begin
readln(s);                        //读入数字
k:=pos(' ',s);                       //找出空格位置
s1:=copy(s,1,k-1);            //找出第1个数
delete(s,1,k);                 //找出第2个数
if s1=s then writeln(s)        //如果2个数相等，输出任意一个
  else writeln(1);            //不相同输出1
end.
```


---

## 作者：小小小朋友 (赞：0)

这是道数论题～

## **题面描述**:

给出$a$,$b$,求$a,a+1,a+2……b$的最大公约数

## **思路**:

**相邻两个自然数互质**，所以如果$a<b$的话，答案就是1，如果$a=b$的话，答案就是$a$～

**为什么呢？下面给出相邻两个自然数互质的证明**

&emsp;&emsp;_设小的数为$a$，则大的为$a+1$_ 

&emsp;&emsp;_假设两数不互质，则有一个大于1的公约数m_
 
&emsp;&emsp;_$\because$ 有一个大于1的公约数m_
 
&emsp;&emsp;_$\therefore$ $xm=a,ym=a+1$_
 
&emsp;&emsp;_$\therefore$ $m(y-x)=1$_
 
&emsp;&emsp;_$\because$ $m>1,y-x\geq1$_
 
&emsp;&emsp;_$\therefore$ 矛盾，命题不成立_

&emsp;&emsp;_$\therefore$ 相邻两个自然数互质_

但是我们发现$a,b<=10^{100}$所以我们可以使用$Python$自带高精度，如果要使用$C++$的话，就用两个字符串读入数然后逐个比较～

## **代码($Python$)**:

```python
a,b=input().split()#因为a,b在1行，所以使用split
a=int(a)#转整数
b=int(b)
if a<b:#如果a不等于b，输出1
    print(1)
else :#如果a等于b，输出a
    print(a)
```

最后来个小广告:[我的博客](https://www.lijiaan.top)

里面会教你PPT，教你做博客，教你A水题~


---

