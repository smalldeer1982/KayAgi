# yyy loves Maths II

## 题目背景

上次蒟蒻 redbag 可把 yyy 气坏了，yyy 说他只是小学生，蒟蒻 redbag 这次不坑他了。


## 题目描述

redbag 给了 yyy 很多个数，要 yyy 计算这些数的和。

必须要快，redbag 只给了 yyy $1$ 秒的时间！！！


## 说明/提示

对于 $100\%$ 的数据，所有数 $ \le 233,333,333 $，保证在小数点后最多有 $6$ 位数，最多共有 $5\times 10^4$ 个数。

## 样例 #1

### 输入

```
1
```

### 输出

```
1.00000
```

# 题解

## 作者：『　』 (赞：210)

教大家一种不用循环的方法，主函数，是可以递归的，上代码

```cpp
#include<cstdio>
long double a,sum;//long double 保证精度没毛病
int main()
{
    if(scanf("%Lf",&a)!=EOF)
    {
        sum+=a*1000000;//去除小数部分，直接乘，变成整数
        main();//核心代码 
    }
    else printf("%.5Lf",sum/1000000);//除回来
    return 0;
}
```

---

## 作者：spcmdxp (赞：38)

这题目主体做法比较显然，把所有数读进去再加起来输出，但精度要求有点高(注意long double是%Lf不是%lf)

其中一个问题是不知道有多少数

要注意scanf失败返回值是-1，cin失败返回值是0
```cpp
#include<cstdio>
using namespace std;
long double yu=0,su;
int main(){
    while(scanf("%Lf",&su)!=-1)yu+=su;
    printf("%.5Lf",yu);
    return 0;
}
```
这个代码得80分，错误出在18和20列（很靠后），大概还是精度问题

瞎打一个代码测试
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long double yu=12456484332.123456;
    printf("%Lf",yu);
    return 0;
}
```
在线ide结果为12456484332.123455，小数部分有毛病
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long double yu=12456484332123456;
    printf("%Lf",yu/1000000);
    return 0;
}
```
正常了12456484332.123456

所以就决定不要把东西放在小数部分
```cpp
#include<cstdio>
//还是不想写四舍五入
using namespace std;
long double yu=0,su;
int main(int spcmdxp/*nonsense*/){
    while(scanf("%Lf",&su)!=-1)yu+=su*1000000;
    printf("%.5Lf",yu/1000000);
    return 0;
}
```
终于AC了

---

## 作者：jinruihai_2006 (赞：37)

## 题解 P2393 （给初学者看的，大佬勿喷）
#### **思路**：首先要计算很多数的和，题目中并没有说是多少个所以要做一个死循环，一直循环输入直到敲回车。
```
#include<bits/stdc++.h>
using namespace std;
double S,T;
int main()
{
    while((cin>>T)!=0)
    {
    	S+=T*1000000;//去除小数部分，直接乘，变成整数
	}
    cout<<fixed<<setprecision(5)<<S/1000000;//这个初学者可能看不懂，相当于printf（"%.5lf",s/1000000）。
    return 0;
 } 
```
####  - 然而只有70或80分，这是为什么，因为精度可能会出毛病。所以要用long double 保证精度没毛病
AC代码 供参考 
S=ans，T=tmp
```
#include<bits/stdc++.h>
using namespace std;
long double S,T;
int main()
{
    while((cin>>T)!=0)
    {
    	S+=T*1000000;
	}
    cout<<fixed<<setprecision(5)<<S/1000000;;
    return 0;
 } 
```
#### 谢谢各位大佬对本人的关心！！！

---

## 作者：封禁用户 (赞：28)

这是本蒟蒻发布的第一篇题解，如有不足之处，还请多多指教！Thanks♪(･ω･)ﾉ！

好，现在来讲一下主要的思路：
* 读入数据
* 读入的同时累加
* 输出答案

# 方法一：使用scanf()函数（不太适合新手）
那这里为了帮助萌新，我就介绍一下scanf()函数：

* 他是有返回值的
* 它的返回值有2种
* 如果结束了，会返回常数EOF，也就是-1
* 上面是一种，另外一种便是返回成功输入的个数

这是道简单的入门题，我们有了思路，便可以得出第一版代码：
```cpp
#include<cstdio>
long double ans,tmp;
int main()
{
	while((scanf("%Lf",&tmp))!=EOF)
	{
		ans+=tmp;
	} 
	printf("%.5Lf",ans);
	return  0;
}
```
**注意！scanf()函数输入long double是“%Lf”，而不是“%llf”**

然而交上去后：代码只有80分！
那是因为小数的**精度问题**！很多人在NOIP都会犯这样的错误！
既然如此，我们便将它化成整数，后面再变回来，于是就有了第二版代码：
```cpp
#include<cstdio>
long double ans,tmp;
int main()
{
	while((scanf("%Lf",&tmp))!=EOF)//判断是否结束
	{
		ans+=tmp*1000000;//化成整数，防止小数的精度问题
	} 
	printf("%.5Lf",ans/1000000);//hey，我再变回来！
	return 0;
}
```
现在提交，完美AC！

# 方法二：使用cin（萌新专用）
**注意：scanf()读完返回-1，而cin返回0，要区分开来**
根据上面的方法，否则出现精度问题：
```cpp
#include<iomanip>//cout保留小数需使用此库
#include<iostream>
using namespace std;
long double ans,tmp;
int main()
{
	while((cin>>tmp)!=0)//判断是否结束,可以化简成while(cin>>tmp)
	{
		ans+=tmp*1000000;
	} 
	cout<<fixed<<setprecision(5)<<ans/1000000;//使用cout保留小数
	return 0;
}
```
就可以成功AC！

也许文章有点长，但只是为了方便刚成为OIer的萌新，~~希望管理给过~~，感谢您的阅读，喜欢不妨[打开后点一下关注](https://www.luogu.org/space/show?uid=127722)，感谢您的阅读！

---

## 作者：STLGirlfriend (赞：8)

C++ 扩展中有一种神奇的东西：`__float128`。

正如这东西的名字一样，她是 $128$ 位浮点数！

所以，直接用就好了。

然而这东西并不能用 `scanf` 和 `printf` 来输入输出，所以在输入输出时需要转成 `long double`。

P.S：NOIP 不能用的。  
P.S.2：同时还有 `__int128`。

```cpp
#include <cstdio>

int main() {
    __float128 sum = 0;
    for (long double x; ~scanf("%Lf", &x); sum += x);
    
    printf("%.5Lf\n", (long double)sum);
}
```

---

## 作者：按Ctrl加w会AC (赞：7)

使用 **unsigned long long** 处理

把所有读入的数据同时乘以 1000000 加起来

最后判断一下,四舍五入

```cpp
#include <cstdio>

typedef unsigned long long ULL;

ULL ans;
char s[105];

inline ULL read(){
	ULL d=0,f=0;
	int i=0,c=0;
	while (s[i]<48 || 57<s[i]) i++;
	while (47<s[i] && s[i]<58) d=(d<<1)+(d<<3)+(s[i++]&15);
	if (s[i]=='.') i++;
	while (47<s[i] && s[i]<58) c++,f=(f<<1)+(f<<3)+(s[i++]&15);
	while (c<6) c++,f=(f<<1)+(f<<3);
	return d*1000000+f;
}

int main(){
	while (scanf("%s",s)!=EOF) ans+=read();
	if (ans%10>=5) ans/=10,ans++; else ans/=10;
	printf("%llu.%05llu\n",ans/100000,ans%100000);
	return 0;
}
```

---

## 作者：SerokSSR (赞：6)

# Python题解
本题中用到了`decimal`模块，包含一个定点高精度小数类，因此可以保证精度。这个模块有很多丰富的功能，这里只用到了最基础的。

解决了精度问题后这道题就非常简单，思路就不多说了。

Code：
```python
from decimal import Decimal
s = input().split()
ans = Decimal(0)
for i in s:
    ans += Decimal(i)
print("{0:.5f}".format(ans))
```
___
### 但是，上面这分代码只能得到90分
___
## Why?
**原因就出在不合法的测试数据上。**

对这份代码来说，最毒瘤的测试数据恰恰是`Case #1`：
- 输入：空
- 输出：`0.00000`

原因也很好理解，当遇到`EOF`时，`input()`方法会抛出`EOFError`，自然会RE。

所以这里又要用到`try... except`语句，当捕获到`EOFError`时，直接输出`0.00000`。

#### ~~yyy dalao的题果然毒瘤~~

**完整代码：**
```python
from decimal import Decimal
try:
    s = input().split()
except EOFError:
    print("0.00000")
else:
    ans = Decimal(0)
    for i in s:
        ans += Decimal(i)
    print("{0:.5f}".format(ans))
```
### 完结撒花~


---

## 作者：acranker (赞：5)

一种很朴素的想法：
```cpp
#include <bits/stdc++.h>
using namespace std;
double sum=0,term;
int main(int argc, char const *argv[])
{
    while(scanf("%lf",&term)!=EOF) sum+=term;
    printf("%.5f\n",sum);
    return 0;
}
```
然鹅只有70分。。。
显然是精度不够，double只有大约17位有效数字。

现在，我们有了一个想法：把sum* 10^6换成整数，用高精度写，在自定义一个输出函数？

可以是可以，不过太烦了。

我们算一下sum的最大值=233333333\*10^6\* 50000=11666666650000000000;

log(2,sum)=63.339<64,在unsigned long long范围内。

~~不用写吃屎的高精度啦！~~

下面是ac代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int BASE=1e6;
unsigned long long sum=0;
double term;
int main(int argc, char const *argv[])
{
	while(scanf("%lf",&term)!=EOF)
	{
		term*=BASE;//最多六位小数，转成整数
		sum+=(unsigned long long)term;
	}
	//要求打印5为小数，去掉最后一位
	if(sum%10>=5) sum=sum/10+1;
	else sum=sum/10;
	BASE/=10;
	//%05llu让不足五位小数的部分用0补全
	printf("%llu.%05llu\n",sum/BASE,sum%BASE);
	return 0;
}
```

---

## 作者：氢氧化铯CsOH (赞：5)

#P2393题解

我的做法有些复杂。使用自定义Real类、异常抛出：

```cpp
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;

struct Real{
    ULL i;// 整数部分
    LD d; // 小数部分
    Real(ULL i = 0, LD d = 0):i(i), d(d){}// 构造函数
    // 重载operator +，计算两个Real之和
    friend Real operator + (const Real& a, const Real& b){
        LD d = a.d + b.d;
        ULL i = a.i + b.i + (ULL)floor(d);
        d -= floor(d);
        return Real(i, d);
    }
    // 重载+=
    Real operator += (const Real& rhs) {
        return (*this) = (*this) + rhs;
    }
    // 输出方法，用于输出该整数
    void print(){
        static char buf[15];
        sprintf(buf, "%.5Lf", d);
        printf("%llu.%s", i, buf + 2);
    }
};

Real nextReal() throw(int) {
    // 这里采用异常的方法来判断是否读到文件尾，如果到文件尾抛出一个-1
    Real ans;
    int c;
    do{
        if((c = getchar()) == EOF)
            throw -1;// 抛出异常
    }while(!isgraph(c));
    if(c != '.'){
        do{
            ans.i = ans.i * 10 + c - '0';
        }while(isdigit(c = getchar()));
    }
    LD base = 0.1L;// 第一个读入的是十分位
    if(c == '.'){
        while(isdigit(c = getchar())){
            ans.d = ans.d + (c - '0') * base;
            base *= 0.1;  // 0.1, 0.01, 0.001, ...
        }
    }
    return ans;
}

int main(){
    Real ans;
    // 异常
    /* try{
           A;
       }catch{
           B;
       }
       表示：执行A，如果收到异常执行B。
    */
    try{
        for(;;) ans += nextReal();
    }catch(int){
        // 正常情况不会抛出异常，如果抛出只可能是nextReal抛出-1，因此不必判断抛出的int是多少
        ans.print();
    }
}

```
虽然代码量大，但逻辑简单


---

## 作者：zhanghengrui (赞：3)

Java题解

用BigDecimal

直接读入，然后加起来就好了

可以用DecimalFormat来控制输出格式

```java
import java.util.Scanner;
import java.math.BigDecimal;
import java.text.DecimalFormat;
public class Main
{
    public static void main(String args[])
    {
        Scanner in=new Scanner(System.in);
        BigDecimal tmp,ans=new BigDecimal("0");
        while(in.hasNext())
        {
            tmp=new BigDecimal(in.next());//不要用nextBigDecimal，不然会超时
            ans=ans.add(tmp);
        }
        System.out.println(new DecimalFormat("0.00000").format(ans));//5位小数
    }
}
```

---

## 作者：worcher (赞：3)

这个方法注意几个点

1、要用long double而不能用double

2、long double的标识符为Lf而不是lf

    
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<bitset>
#define ll long long
#define mod 1000000007
using namespace std;
long double a,ans=0;
int main()
{
    while(scanf("%Lf",&a)!=EOF){ans=ans+a*1000000;}
    printf("%.5Lf",ans/1000000);
    return 0;
}
```

---

## 作者：doby (赞：3)

比较低级的方法，直接扩大忽略精度问题……

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long double n,ans=0;
int main()
{
    while(cin>>n){ans=ans+n*1000000;}//加到最终结果中
    printf("%0.5Lf",ans/1000000);//输出
    return 0;
}
```

---

## 作者：Aw顿顿 (赞：1)

这道题很简单

但是我一开始却错了

你们看一下这个代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double s=0,n;
int main()
{
	while(scanf("%lf",&n))s+=n;
	printf("%.5lf",s);
	return 0;
}
```
我一看：诶？不对，输入部分判断就有问题

那么为什么scanf不行，cin就可以呢？

原来，**scanf输入为NULL时返回的是-1**

于是更改代码为这个版本
```cpp
#include<bits/stdc++.h>
using namespace std;
double s=0,n;
int main()
{
	while(scanf("%lf",&n)!=EOF)s+=n;
	printf("%.5lf",s);
	return 0;
}
```
~~~
请注意!=EOF就是输入正确的判断条件
但是还是有问题，是什么问题呢？
我做了一下猜测与调试
~~~
1. double**精确度**不够，要使用long double

2. 当中s直接加n小数部分会有问题

于是，现将n*1000000然后加上

最后在输出时÷1000000

于是，就有了这个代码，**注意printf和scanf会更快一点**

然后，**请勿抄袭AC代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
long double s=0,n;
int main()
{
	while(scanf("%Lf",&n)!=EOF)s+=n*1000000;
	printf("%.5Lf",s/1000000);
	return 0;
}
```


---

## 作者：yjxyjx (赞：1)

这题，在不知道long double的人看来，是痛苦的，在知道long double的人看来………………~~也是痛苦的~~这题可以放到NOIP普及组T2.5那里


好了上面扯怎么多是为了不写思路的，可你们还要看过来，我对此非常讨厌并扔给你一份（我写~~（chao）~~的）垃圾代码供你食用：

噢对了还有一个坑点，就是我们喜闻乐见的——精度问题

CODE:
（80分，有两个蜜汁错误，如果有人发现请私信我，谢谢）
```
#include<bits/stdc++.h>

const int hehe = 10000000;

long double sum = 0, x;

int main() {
    while ((std::cin >> x) && (x != 0)) sum += x * hehe;
    std::cout << std::fixed << std::setprecision(5) << sum / hehe;
    return 0;
}

```

为了不让你们失望，我决定再扔一份dalao的代码（其实就是我楼下的）
```
/* 
#include<bits/stdc++.h>

const int hehe = 1000000; 

long double sum, x;

int main() {
    if (scanf("%lf", &x) != EOF) {
        sum += x * hehe;
        main();
    } else {
        printf("%.5Lf", sum / hehe);
    }
    return 0;
} */

```

END.



---

## 作者：你锡白大爷 (赞：0)

# 这题有毒！！！真的有毒！！！
### 记得scanf错误返回值是-1！！cin是1！！
先不说什么，其实挺水，我用的递归，其实用循环也能做。
```cpp
#include<bits/stdc++.h>
long double a,sum=0.0;
void hehe(){
	if(scanf("%Lf",&a)!=EOF)
    {
        sum+=a*1000000;
        hehe();
    }
    else
	{
    	printf("%.5Lf",sum/1000000);	
	}
} 
int main()
{
    hehe();
    return 0;
}
```
很迷的是这串代码是对的
```cpp
#include <bits/stdc++.h>
long double a , sum = 0.0;
void hehe ()
{
	if( scanf ( " %Lf " , &a ) != EOF )
    {
        sum += a * 1000000;
        hehe ();
    }
    else
	{
    	printf ( " %.5Lf " , sum / 1000000 );	
	}
  	return;
} 
int main ()
{
    hehe ();
    return 0;
}
```

这串就是错的

**_区别只是打了空格和没打空格而已，就很诡异_**

感到妈卖批…………………………


---

## 作者：wpy233 (赞：0)

（手动滑稽）~~教大家一种可以不用循环的方法，while循环的判断表达式里，是可以输入的~~

另外，这道题极其无耻，~~卡你精度，毁你人生~~，我们可以先把`long double`开上，然后发现WA了两个点。。。

有一种非常好的方法，就是先把输入的数先乘上一个大数转换成整数，最后输出是再除掉。一个关键的注意点：是`printf("%.5Lf",p);`而不是`printf("%.5f",p);`

最后上代码。。。
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	double a;
	long double p=0;
	while(cin>>a)//我有些皮
		p+=a*1000000;//转换成整数
	printf("%.5Lf",p/1000000);//保留五位小数输出
	return 0;
}
```

---

## 作者：Patchuli_Go (赞：0)

C/C++读入要用getchar优化，然而这题还有卡精度这种事。。。

将浮点数的整数部分和小数部分分别用整形进行模拟，由于保证小数点后只有六位，所以开个6个数的数组就好

注意数据规模，整数部分要用long long，小数部分由于50000\*9不超int所以不需要long long，最后一起处理进位就好。

不要忘记最后对末尾进行四舍五入。

```cpp
#include<cstdio>
using namespace std;
typedef unsigned int uint;
unsigned long long sa,a;
uint sb[6];
char c;
int main()
{
    while(1)
    {
        a=0;
        do
        {
            c=getchar();
            if(c==EOF) goto end;
        }while(c<'0'||c>'9');
        while(c>='0'&&c<='9')
        a=a*10+c-'0',c=getchar();
        sa+=a;
        if(c=='.')
        {
            a=0;c=getchar();
            while(c>='0'&&c<='9')
            sb[a++]+=c-'0',c=getchar();
        }
    }
    end:
        for(int i=5;i;i--)
        if(sb[i]>10)
        sb[i-1]+=sb[i]/10,sb[i]%=10;
        if(sb[0]>10)
        sa+=sb[0]/10,sb[0]%=10;
        if(sb[5]>4)
        sb[4]++;
        printf("%llu.%u%u%u%u%u",sa,sb[0],sb[1],sb[2],sb[3],sb[4]);
    return 0;
}
```

---

## 作者：江海寄余生 (赞：0)

这道题看着水比，其实有一些程序运行方面的小细节需要注意，我看AC的80%只抄了题解，自己做的大多60、70分。而原有题解并不十分详细，于是又来补充一番。下面题解针对pascal，C的方面就不清楚了，不过似乎C写起来很简单。


1、浮点数运算较为鬼畜。0.999999 可以变成 0.99999899999999997 再一trunc就是0.999998。所以\*1000000 再“round“全程用整数进行计算，包括最后的四舍五入。（四舍五入后再除下去也会爆几个点，鬼畜的浮点运算会毁了一切）


2、qword比int64要大！！！

qword:0到2^64-1；


int64:-2^63到2^63-1;

这道题乘上1000000后用int64最后四个点都要爆，所以用qword

明白了这两点再研究一下最后输出处理这道题就成小傻逼了

于是有可爱的代码君


```cpp
var
x:extended;
j,i:qword;
ii,k:longint;
xx:string;
begin
while not eof do
begin
read(x);
j:=round(x*1000000);
i:=i+j;
end;
j:=i mod 10;
i:=i div 10;
if j>4 then i:=i+1;
j:=i div 100000;
write(j);
write('.');
j:=i mod 100000;
str(j,xx);
k:=5-length(xx);
for ii:=1 to k do   //模100000取出小数后注意补零 比如1要变成00001
write('0');
write(j);
end.
```

---

## 作者：spacetime (赞：0)

```delphi

var
  ans,tmp:qword;
  t:extended;
procedure print(n,depth:longint);
begin
  if depth=0 then exit;
  print(n div 10,depth-1);
  write(n mod 10);
end;
begin
  while not eoln do begin
    read(t);
    inc(ans,trunc(t*1000000));
  end;
  write(ans div 1000000,'.');
  ans:=ans mod 1000000;
  print(ans div 100,4);
  ans:=ans mod 100;
  writeln(ans div 10+ord(ans mod 10>4));
end.

//Pascal题解：

//因为输入的数小数位不超过6位，我们可以把输入的数都乘上1000000再运算

```

---

