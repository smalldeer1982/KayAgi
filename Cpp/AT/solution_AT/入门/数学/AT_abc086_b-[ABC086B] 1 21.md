# [ABC086B] 1 21

## 题目描述

シカの AtCoDeer くん找到了两个正整数 $a, b$。请判断将 $a$ 和 $b$ 按顺序连接后得到的数是否为一个平方数。

## 说明/提示

## 限制条件

- $1 \leq a, b \leq 100$
- $a, b$ 为整数

## 样例解释 1

$121 = 11 \times 11$，所以是平方数。

## 样例解释 2

$100100$ 不是平方数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 21```

### 输出

```
Yes```

## 样例 #2

### 输入

```
100 100```

### 输出

```
No```

## 样例 #3

### 输入

```
12 10```

### 输出

```
No```

# 题解

## 作者：LJY_ljy (赞：4)

### ~~相信各位大佬们数学好的会位值原理吧？~~


------------
~~我来为大家介绍一下位值原理~~[看过来](https://wenku.baidu.com/view/07c1010f03020740be1e650e52ea551810a6c9a0.html)

两个数连起来就是a*10^b的位数+b

平方数就是sqrt自己再平方以下还是自己的数就是**平方数**。

记得输出后要换行哟！

```cpp
//100分小学生代码。
#include<iostream>
#include <cmath>
using namespace std;
int beishu(int cifang,int shu)//就是不喜欢用pow函数。
{
    long long int sum=1;
    for (int i=1;i<=cifang;i++)
        sum*=shu;
    return sum;
}
int weishu(int x)
{
    int num=0;
    while (x)
    {
        num++;
        x/=10;
    }
    return num;
}
int main()
{
    int a,b;
    cin>>a>>b;
    long long int s;
    s=a*beishu(weishu(b),10);//位值原理。
    s+=b;
    int g=sqrt(s);
    if (g*g==s)//判断是否为平方数。
    	cout<<"Yes\n";//要换行。
    else
    	cout<<"No\n";//要换行。
    return 0;//完美100AC的结束了。
} 
```
(〃'▽'〃)

---

## 作者：Gu_Ren (赞：3)

~~还没学过字符串 出门左拐试练场~~

大家真强，这题pas党真的占优势(我也是)

按题意，一个读入处理加判断就可以完成的事

但是

我作为一名想要努力成为是神犇的蒟蒻，

怎可水这种红题

于是手痒打了个打了个二分练练手

不知道的蒟蒻可以学一学（实用又省时）

二分整体思想有点像詹天佑** 两端同时向中间凿进 **的办法

具体见代码↓

```cpp
var
  n,m,i,t:longint;
  s,ss:string;
  
 function poss:boolean;//二分
  var
    m,head,tail:longint;
  begin
    head:=1;
    tail:=t;//定义二分查找的范围
    while head<=tail do//如果'山被凿通了'就退出
    begin
      m:=(head+tail) div 2;//取一个他们的中间数
      if m=sqrt(t) then exit(true);//如果找到平方根数，詹天佑就可以回去休息了
      if m<sqrt(t) then head:=m+1//如果中间数比平方根数小，詹天佑就要从左一路挖到中间数的前面
      else tail:=m-1;//否则詹天佑就要从右一路挖到中间数的后面
    end;
    exit(false);//如果'山被凿通了'，詹天佑还是没挖到平方根数，那这个数就不是平方数
  end;
  
begin
  read(n,m);
  str(n,s);
  str(m,ss);
  s:=s+ss;
  val(s,t);//读入处理，
  if poss then write('Yes')
     else write('No');//判断找不找到
end.
```
~~(我不能误导新人啊)~~当然下面这段话也可以有其他的写法
```cpp
if poss then write('Yes')
     else write('No');
```
比如判断他的平方有没有小数
```cpp
if trunc(sqrt(t))=sqrt(t) then *****
   else *****
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if turnc(sqrt(t))*trunc(sqrt(t))=t **** *****
   **** *****
简短一点↕
if sqr(turnc(sqrt(t)))=t
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```
或是暴力枚举也行
```cpp
for i:=1 to t do
if i*i=t then begin write('yes');exit;end;
write('no');
```
《詹天佑》这篇文章小学语文应该有学过的吧(.=^・ェ・^=)

---

## 作者：yuzhechuan (赞：3)

~~其实就是模拟~~


------------

```cpp
#include <bits/stdc++.h>//一个万能库
using namespace std;

int a,b,c,len;

int main()
{
	scanf("%d%d",&a,&b);//读入~~
	c=b;//备份一个b
	while(c>0)//用一个while求出b的位数
	{
		c/=10;//删掉末尾
		len++;//位数加1
	}
	a=a*pow(10,len)+b;//pow()函数用于求幂
    				  //至于为什么是10的位数次方
                      //嗯...好像是因为位值原理...
	if(sqrt(a)==floor(sqrt(a)))printf("Yes");//判断部分比较a的平方和它平方的整数部分，如相等，就是完全平方数，输出Yes
	else printf("No");//否则输出No
}
```

---

## 作者：封禁用户 (赞：1)

首先，如果要合并，那肯定是字符串（大神：废话）；-->（别问我为什要用分号233）
献上我的第一次错误代码：
```pascal
var
    nm,i:longint;
    n,m:string;
begin
    readln(n,m);
    val(n+m,nm);
    for i:=1 to trunc(sqrt(nm)) do
    if(sqr(i)=nm)then
    begin
        writeln('Yes');
        exit;
    end;
    writeln('No'); 
end.

```
大神们看出来了么，我忽略了空格；~~但我居然A了四个点~~
WA之后，改正了代码：
```pascal
var
    nm,i,x:longint;
    n:string;
begin
    readln(n);
    x:=pos(' ',n);//找空格
    delete(n,x,1);//把空格删去，即为合并
    val(n,nm);
    for i:=1 to trunc(sqrt(nm)) do//为优化，优化时间，虽说有很多蒟蒻会直接写（毕竟...你见过除一以外的数的平方等于这个数么）
    if(sqr(i)=nm)then//判断不解释哦
    begin
        writeln('Yes');
        exit;//这个其实可以不用，因为没有一个数是两个或两个以上得数的平方数
    end;
    writeln('No');
end.

```
撒fafa完结   
~~话说我挺喜欢3874这个数字的~~

---

## 作者：xyn0901 (赞：1)

我用的字符串


```pascal
var a,b:integer;
s1,s:string;
begin
read(a,b);
str(a,s1);
str(b,s);
s:=s1+s;
val(s,a);
if trunc(sqrt(a))=sqrt(a) then writeln('Yes') else writeln('No');
end.
```

---

## 作者：PC_DOS (赞：1)

这是一道模拟题，唯一要处理的就是将两个数字拼接，虽说我们可以使用数学方法(iNum1乘上10^len(iNum2)再加上iNum2)，但是我们也可以通过字符串实现数字的合并。

STL提供了名为字符串流(StringStream)的类，通过该类我们可以像使用cin/cout一样实现字符串(string)和其他类型之间的互相转化。

使用StringStream前，需要引入头文件sstream并实例化一个std::stringstream对象。

StringStream的简单使用:

插入流:

```
ssStringStream << source;
```

输出流:

```
ssStringStream >> target;
```

建议每次插入流之前调用ssStringStream.clear()方法以清空流中不再需要的数据。

但是请注意，由于种种封装、抽象化、具体化、实例化、安全检查等的存在string相比C风格字符串要慢，而StingStream更慢。

代码:
```
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
using namespace std; //头文件和命名空间
int main(){ 
	ios::sync_with_stdio(false); //输入输出加速
	long long iSqrt,iNum; //iSqrt-取整后的算术平方根；iNum-原始数
	string sNum1, sNum2; //两个分开的数
	stringstream ssStringStream; //字符串流
	while (cin >> sNum1 >> sNum2){ //读入数
		sNum1 += sNum2; //合并
		ssStringStream << sNum1; //从源插入流
		ssStringStream >> iNum; //从流进入目标
		iSqrt = sqrt(iNum); //开根号并取整
		if (iSqrt*iSqrt == iNum) //判断是不是完全平方
			cout << "Yes\n"; //是
		else
			cout << "No\n"; //不是
		ssStringStream.clear(); //清空流
	}
	return 0; //结束
}
```

---

## 作者：durbin中将 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	bool flag=false;//将来判断是否是平方数要用
	string A,B;//两个数
	int a,b,k,b1;
	cin>>A>>B;//输入两个数
	b1=B.length();//B的长度，也就是位数，和A拼一起时要用
	a=atoi(A.c_str());
	b=atoi(B.c_str());//把A，B转为数字
	k=(pow(10,b1))*a+b;//合起来的数：A乘以后面给它留的位数
	for(int i=1;i<=k;i++)
		if(i*i==k) flag=true;//判断是否为平方数
	if(flag==true) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;/输出
	return 0;//结束
}
```

---

## 作者：CZQ_King (赞：0)

## ~~JAPAN的水题~~
#### 用了$stringstream$（感觉好无聊）
~~判断一个数是不是整数居然不能用if(n%1==0)（我真无知）~~
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string b;//字符串（其实是第二个数）
int a,c;//a是第一个数，c是转成int的第二个数
double d;
stringstream ss;//stringstream大法
int main(){
    cin>>a>>b;
    ss<<b;ss>>c;//将第二个数转成int类型
    d=sqrt(a*pow(10,b.length())+c);//眼花缭乱的一行
    if(d-(int)d==0)cout<<"Yes"<<endl;//判断是否是完全平方数
    else cout<<"No"<<endl;//请区分大小写
    return 0;//完美结束
}
```

---

## 作者：Soyilieber (赞：0)

几行ac
周知，√￣121￣=11，11^2=121

但是， √￣122￣（取整）=11，11^2=121≠122

所以可以由这条式子是否可能相等来判断
- trunc(sqrt(a))*trunc(sqrt(a))=a


------------
代码：

```pascal
var
    s:string;
    a,p:longint;
begin
    readln(s);//读入字符串
    p:=pos(' ',s);//找空格
    delete(s,p,1);//删空格
    val(s,a);//字符转数字
    if trunc(sqrt(a))*trunc(sqrt(a))=a then//开方去整再^2是否=原数
    	writeln('Yes') else writeln('No');
end.
```

---

