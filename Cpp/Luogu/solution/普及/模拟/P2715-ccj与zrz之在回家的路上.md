# ccj与zrz之在回家的路上

## 题目背景

zrz走在回家了路上，突然很想上厕所，然后就冲到厕所门口，惊讶的发现门上有个算式。。。


## 题目描述

给出一个算式（a\*b=c或a/b=c或a+b=c或a-b=c）其中a，b，c是三个数字，但是其中有一个是问号，表示未知，请你求出未知的那一个量。


## 说明/提示

总长度小于200，所有数字和要求的数字均不会超过1000000000，也不会是负数。读入的数不会是小数，但答案有可能是


## 样例 #1

### 输入

```
1+1    =                     ?```

### 输出

```
2.00```

## 样例 #2

### 输入

```
1-?                     =0```

### 输出

```
1.00```

## 样例 #3

### 输入

```
2*?=                         6```

### 输出

```
3.00```

## 样例 #4

### 输入

```
8/5=?```

### 输出

```
1.60```

# 题解

## 作者：shame_djj (赞：18)

其实我的思路和楼上楼下都差不多，

那为什么发篇题解呢

我觉得我的代码有两个可取之处

一个是对于cin省去多余符号~~来节省码量~~

另一个是边输入边处理

code
```cpp

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int a, b;
char c, ch;

int main() {
	c = getchar();
	while (c == ' ')
		c = getchar();
	if (c == '?') {
		c = getchar();
		while (c == ' ')
			c = getchar();
		cin >> a >> ch >> b;
		if (c == '+') {
			printf("%.2lf\n", double(b) - double(a));
			return 0;
		}
		if (c == '-') {
			printf("%.2lf\n", double(b) + double(a));
			return 0;
		}
		if (c == '*') {
			printf("%.2lf\n", double(b) / double(a));
			return 0;
		}
		if (c == '/') {
			printf("%.2lf\n", double(b) * double(a));
			return 0;
		}
	}
	else {
		while (c >= '0' && c <= '9')
			a = a * 10 + c - '0', c = getchar();
		while (c == ' ')
			c = getchar();
		ch = c;
		c = getchar();
		while (c == ' ')
			c = getchar();
		if (c == '?') {
			cin >> c >> b;
			if (ch == '+') {
				printf("%.2lf\n", double(b) - double(a));
				return 0;
			}
			if (ch == '-') {
				printf("%.2lf\n", double(a) - double(b));
				return 0;
			}
			if (ch == '*') {
				printf("%.2lf\n", double(b) / double(a));
				return 0;
			}
			if (ch == '/') {
				printf("%.2lf\n", double(a) / double(b));
				return 0;
			}
		}
		else {
			while (c <= '9' && c >= '0')
				b = b * 10 + c - '0', c = getchar();
			if (ch == '+') {
				printf("%.2lf\n", double(a) + double(b));
				return 0;
			}
			if (ch == '-') {
				printf("%.2lf\n", double(a) - double(b));
				return 0;
			}
			if (ch == '*') {
				printf("%.2lf\n", double(a) * double(b));
				return 0;
			}
			if (ch == '/') {
				printf("%.2lf\n", double(a) / double(b));
				return 0;
			}
		}
	}
	return 0;
}

```

希望这篇题解能通过，

也希望大家Noip rp++

加油

---

## 作者：jinyijiang (赞：6)

看仅有的几篇题解中都没有人发挥好string的特点的，所以本人要为大家介绍find系列函数

下面非本题代码，复制保龄不负责
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s="Hello, world!";
	string filter=",!";
	cout<<s.find('l',1)<<endl;  //从s[1]第一个‘l’位置
	cout<<s.find("lo",7)<<' '<<string::npos<<endl;  //从s[7]找"lo"，没有，返回很大的数 
	cout<<s.rfind("lo",7)<<endl;  //往前找
	cout<<s.find_first_of(filter,2)<<endl;  //从s[2]开始找','或'!'第一个
	cout<<s.find_last_of(filter)<<endl; //从后找
	cout<<s.find_first_not_of(filter)<<endl; //找第一个不是
	cout<<s.find_last_not_of(filter,100)<<endl;  //找最后一个不是
	return 0;
}
```
~~大家可以不管这些~~

既然讲了find，就用在代码里
```cpp
#include <iostream>
#include <string>  //find在这里
using namespace std;
double pplus(string c1,string c2,string c3);
double mminus(string c1,string c2,string c3);
double ttime(string c1,string c2,string c3);
double ddi(string c1,string c2,string c3);
bool qq(string c);
int num(string c);
int main()
{
	string c;
	getline(cin,c);
	int a=c.find_first_of("+-*/"); //找运算符
	int b=c.find_first_of("=");  //找等于号
        //除去空格
	string c1=c.substr(0,a);
	string c2=c.substr(a+1,b-a-1);
	string c3=c.substr(b+1);
	double n;
	switch(c[a])//算结果
	{
		case '+':
			n=pplus(c1,c2,c3);
			break;
		case '-':
			n=mminus(c1,c2,c3);
			break;
		case '*':
			n=ttime(c1,c2,c3);
			break;
		case '/':
			n=ddi(c1,c2,c3);
	}
	printf("%.2lf",n);
	return 0;
}
//加法
double pplus(string c1,string c2,string c3)
{
	if(qq(c1))
	{
		int a=num(c2);
		int b=num(c3);
		return b-a;
	}
	if(qq(c2))
	{
		int a=num(c1);
		int b=num(c3);
		return b-a;
	}
	if(qq(c3))
	{
		int a=num(c2);
		int b=num(c1);
		//cout<<endl;
		return b+a;
	}
}
//减法
double mminus(string c1,string c2,string c3)
{
	if(qq(c1))
	{
		int a=num(c2);
		int b=num(c3);
		return b+a;
	}
	if(qq(c2))
	{
		int a=num(c1);
		int b=num(c3);
		return a-b;
	}
	if(qq(c3))
	{
		int a=num(c2);
		int b=num(c1);
		return b-a;
	}
}
//乘法
double ttime(string c1,string c2,string c3)
{
	if(qq(c1))
	{
		int a=num(c2);
		int b=num(c3);
		return 1.0*b/a;
	}
	if(qq(c2))
	{
		int a=num(c1);
		int b=num(c3);
		return 1.0*b/a;
	}
	if(qq(c3))
	{
		int a=num(c2);
		int b=num(c1);
		return b*a;
	}
}
//除法
double ddi(string c1,string c2,string c3)
{
	if(qq(c1))
	{
		int a=num(c2);
		int b=num(c3);
		return b*a;
	}
	if(qq(c2))
	{
		int a=num(c1);
		int b=num(c3);
		return 1.0*a/b;
	}
	if(qq(c3))
	{
		int a=num(c2);
		int b=num(c1);
		return 1.0*b/a;
	}
}
//找问号
bool qq(string c)
{
	bool f=0;
	int len=c.length();
	for(int i=0;i<len;i++)
	{
		if(c[i]=='?')
		{
			f=1;
		}
	}
	return f;
}
//字符串->整数
int num(string c)
{
	int n=0;
	int len=c.length();
	for(int i=0;i<len;i++)
	{
		if((c[i]>='0')&&(c[i]<='9'))
		{
			n*=10;
			n+=c[i]-'0';
		}
	} 
	return n;
}
```
P.S. 在输入时一定要保证'?'是英文字符，不然就会像本蒟蒻一样调试半天也调不出来

---

## 作者：做梦想Peach (赞：3)

$2333333$，改了半天，终于还是过了。

-----
由于这题的读入过于**毒瘤**，有一些空格，所以我用了gets函数来读入。

我用$x$表示这是哪一种运算，用$k$表示`?`的位置，便于输出。

再求`?`的位置时，我用`flag`记录`?`前有多少个数，$k$也就是`flag+1`。

然后也就没什么了。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
char s[210];
long long len,i,ans,x,a,b,k,flag;
int main () {
	gets (s+1);
	len=strlen (s+1);
	for (i=1;i<=len;i++) {
		if (s[i]=='+') x=1;
		if (s[i]=='-') x=2;
		if (s[i]=='*') x=3;
		if (s[i]=='/') x=4;//x表示那种运算。
	}
	for (i=1;i<=len;i++) 
		if (s[i]>='0'&&s[i]<='9') {
			while (s[i]>='0'&&s[i]<='9') {a=a*10+s[i]-'0';i++;}
			break;
		} //算第一个数字。
	for (;i<=len;i++) 
		if (s[i]>='0'&&s[i]<='9') {
			while (s[i]>='0'&&s[i]<='9') {b=b*10+s[i]-'0';i++;}
			break; 
		}//算第二个数字。
	for (i=1;i<=len;i++) {
		if (s[i]=='?') {k=flag+1;break;}
		if (s[i]>='0'&&s[i]<='9') {
			flag++;//注意是flag+1，而不是flag。
			while (s[i]>='0'&&s[i]<='9') i++;
		} 
	}
	if (k==1) {
		if (x==1) {printf ("%.2lf\n",(b-a)*1.0);return 0;}
		if (x==2) {printf ("%.2lf\n",(b+a)*1.0);return 0;}
		if (x==3) {printf ("%.2lf\n",b*1.0/a);return 0;}
		if (x==4) {printf ("%.2lf\n",b*1.0*a);return 0;}
	}
	if (k==2) {
		if (x==1) {printf ("%.2lf\n",(b-a)*1.0);return 0;}
		if (x==2) {printf ("%.2lf\n",(a-b)*1.0);return 0;}
		if (x==3) {printf ("%.2lf\n",b*1.0/a);return 0;}
		if (x==4) {printf ("%.2lf\n",a*1.0/b);return 0;}
	}
	if (k==3) {
		if (x==1) {printf ("%.2lf\n",(a+b)*1.0);return 0;}
		if (x==2) {printf ("%.2lf\n",(a-b)*1.0);return 0;}
		if (x==3) {printf ("%.2lf\n",a*1.0*b);return 0;}
		if (x==4) {printf ("%.2lf\n",a*1.0/b);return 0;}
	}//一些无脑的输出。
	return 0;
} 
```
没了QwQ。

---

## 作者：hensier (赞：3)

这道题用到了字符串的处理和数学中等式的性质的运用。为了方便，我们可以使用$\text{string}$来实现。

下面是本题的大体框架：

![](https://cdn.luogu.com.cn/upload/image_hosting/6rroh5ba.png)

首先，我们要实现基本的输入。假设字符串为$s$，则：

```cpp
while(true)
{
    char ch=getchar();//读入单个字符ch
    //也可以执行scanf("%c",&ch);或者cin>>ch;
    if(ch=='\n')break;//如果读到了换行符就结束循环
    if(ch!=' ')s+=ch;//如果不为空格就拼接到字符串后端
}
```

但是，上述的三种输入方式都会超时。其中`cin`超时最严重，所以还是直接单行输入比较高效：

```cpp
getline(cin,s);//读入整行字符串
```

接着，我们应当剔除字符串中的空格。具体的操作可以利用$\text{string:erase}$：

```cpp
for(int i=0;s[i];)
{
    if(s[i]==' ')s.erase(i,1);
    else i++;
}
/*
对于该段代码的简单解释：
s.erase(i,1);每一次去除i位置的1个字符，然后将后面字符往前推。
例如，有一个字符串：
1  +2=?
（1后面有2个空格）
那么，当i=0时，s[i]为1，不删除字符。
当i=1时，s[i]为空格，将其删除。
删除后，后面的所有内容紧接着往前推。
此时如果i++的话，那么会指向第二个空格右边的内容。
这时，我们就遗漏了一个空格。
因此，只有在当前字符为非空格的时候，我们才需要将i加1。
所以for循环的第三个语句是空语句。
*/
```

这样，我们就实现了空格的处理。接着我们需要找到运算符的位置。由于只有加减乘除中的一个，因此我们可以通过这样的函数来寻找：

```cpp
int pos()//返回的是第一个出现的四个运算符
{
    int a[4]={s.find('+'),s.find('-'),s.find('*'),s.find('/')};
    //find函数在字符串中找到另一个字符（串）第一次出现的位置，找不到则返回string::npos
    for(int i=0;i<4;i++)
    {
        if(a[i]==string::npos)continue;//找不到就继续找
        return a[i];//找得到就返回
    }
    return -1;//多余，但增加是为了防止编译提醒
}
```

然后，将字符串拆分成三段，分别是三个被操作数（包括一个问号）。具体可以利用$\text{string:substr}$来实现。

```cpp
a=pos();//调用之前的函数，让a为运算符（加减乘除中的一个）所在位置
b=s.find('=');//把b赋值为=号的位置
s1=s.substr(0,a);
//在s中取子串，从0开始，长度为a
s2=s.substr(a+1,b-a-1);
//同样在s中提取，从位置a+1开始，长度为b-a-1
s3=s.substr(b+1);
//特别地，如果只有一个参数，那么默认从该位置取到结束
```

再然后，我们需要进行逐一的双重判断——外层是运算符，内层是问号的位置：

```cpp
//ans保存答案，x、y、z分别表示s1、上
和s3转换为数字的结果
switch(s[a])//s[a]表示运算符
{
    case '+': //加号
    {
        if(s1=="?")ans=z-y;
        else if(s2=="?")ans=z-x;
        else ans=x+y;
        break;
        //注意switch语句每一个case末尾要break
    }
    case '-': //减号
    {
        if(s1=="?")ans=y+z;
        else if(s2=="?")ans=x-z;
        else ans=x-y;
        break;
    }
    case '*': //乘号
    {
        if(s1=="?")ans=1.0*z/y;//强制转换为浮点
        else if(s2=="?")ans=1.0*z/x;
        else ans=x*y;
        break;
    }
    case '/': //除号
    {
        if(s1=="?")ans=y*z;
        else if(s2=="?")ans=1.0*x/z;
        else ans=1.0*x/y;
        break;
    }
}
```

最后，我们只需要格式化输出$ans$即可，保留位数为$2$。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1,s2,s3;
int a,b,x,y,z;
double ans;
int pos()
{
    int a[4]={s.find('+'),s.find('-'),s.find('*'),s.find('/')};
    for(int i=0;i<4;i++)
    {
        if(a[i]==string::npos)continue;
        return a[i];
    }
    return -1;
}
int f(string s)//实现了将字符串转换为数字
{
    int x=0;
    for(int i=0;s[i];i++)
    {
        if(!isdigit(s[i]))break;//不是数字就结束循环
        x=(x<<3)+(x<<1)+(s[i]^48);
    }
    return x;
}
int main()
{
    getline(cin,s);
    for(int i=0;s[i];)//去空格
    {
        if(s[i]==' ')s.erase(i,1);
        else i++;
    }
    a=pos();//找运算符
    b=s.find('=');//找等号
    s1=s.substr(0,a);
    s2=s.substr(a+1,b-a-1);
    s3=s.substr(b+1);//取子串
    x=f(s1);
    y=f(s2);
    z=f(s3);//字符串转换为数字
    switch(s[a])//判断
    {
        case '+':
        {
            if(s1=="?")ans=z-y;
            else if(s2=="?")ans=z-x;
            else ans=x+y;
            break;
        }
        case '-':
        {
            if(s1=="?")ans=y+z;
            else if(s2=="?")ans=x-z;
            else ans=x-y;
            break;
        }
        case '*':
        {
            if(s1=="?")ans=1.0*z/y;
            else if(s2=="?")ans=1.0*z/x;
            else ans=x*y;
            break;
        }
        case '/':
        {
            if(s1=="?")ans=y*z;
            else if(s2=="?")ans=1.0*x/z;
            else ans=1.0*x/y;
            break;
        }
    }
    printf("%.2lf",ans);//保留两位小数输出ans
    return 0;
}
```

---

## 作者：max0810 (赞：3)

这道题主要讲一下读入。


------------

首先，是烦人的空格，大家知道cin是不会读入空格的，利用这一点写出代码
```cpp
while(cin >> s)a+=s;
```
于是，a就是不带空格的字符串了


------------

第二个，关于读入数字，这里给大家介绍一个叫find_first_of的函数，它要传一个字符串s和一个整数i，表示从第i位开始找第一个是s里面任意一个字符的字符，返回它的下标，如：
```cpp
a.find_first_of("+-*/");//找第一个是+-*/的字符的下标（第二个参数可以不传）
```

知道了这些，就很好写代码了。
```cpp
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
const int inf = 2000000000; //表示问号
double d[3],ans;
string a,s;
char f;  //符号

int read(int i)   //返回从第i位开始的数字
{
    if(a[i] == '?')return inf;
    int x = 0;
    for(;i < a.size()&&a[i]>='0'&&a[i]<='9';i++)
        x = x*10+(a[i]-'0');
    return x;
}
int main()
{
    while(cin >> s)a+=s;
    d[0] = read(0);
    int x = a.find_first_of("+-*/"); //现在x是符号的位置
    f = a[x];
    d[1] = read(x+1);
    x = a.find_first_of("=",x+1);  //现在x是=的位置
    d[2] = read(x+1);
    if(d[0]==inf)
    {
        if(f=='+')ans=d[2]-d[1];
        else if(f=='-')ans=d[2]+d[1];
        else if(f=='*')ans=d[2]/d[1];
        else ans=d[2]*d[1];
    }
    else if(d[1]==inf)
    {
        if(f=='+')ans=d[2]-d[0];
        else if(f=='-')ans=d[0]-d[2];
        else if(f=='*')ans=d[2]/d[0];
        else ans=d[0]/d[2];
    }
    else
    {
        if(f=='+')ans=d[0]+d[1];
        else if(f=='-')ans=d[0]-d[1];
        else if(f=='*')ans=d[0]*d[1];
        else ans=d[0]/d[1];
    }
    printf("%.2f",ans);
    return 0;
}

```


---

## 作者：_Ayanami_ (赞：2)

做法

- 整行读入

- 分类
1. 忽略非数字、非运算符、等号（等号的位置是固定的所以不用管）
1. 找出a，b，c对应的数字
1. 找出未知数
1. 找出运算符
- 分十二种情况计算得出答案

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;
int l,z,i,a=-1,b=-1,c=-1;
string s;
int num()//读取数字的函数
{
	int k=0;
	while(s[i]>='0'&&s[i]<='9'&&i<l)
	{
		k=k*10+s[i]-'0';
		i++;
	}
	return k;
}
int main()
{
	getline(cin,s);//getline读入整行
	l=s.length();
	for(i=0;i<l;i++)
	{
		//忽略无用内容
		while((s[i]<'0'||s[i]>'9')&&s[i]!='?'&&s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/'&&i<l-1)
		{
			i++;
		}
		//是数字
		if(s[i]>='0'&&s[i]<='9')
		{
			//abc是按顺序出现的所以按顺序填入
			if(a==-1)
			{
				a=num();
			}
			else if(b==-1)
			{
				b=num();
			}
			else
			{
				c=num();
			}
			i--;
			continue;
		}
		//是未知数
		if(s[i]=='?')
		{
			//道理同上
			if(a==-1)
			{
				a=-2;
			}
			else if(b==-1)
			{
				b=-2;
			}
			else
			{
				c=-2;
			}
			continue;
		}
		//是运算符
		if(s[i]=='+')
		{
			z=1;//加
		}
		else if(s[i]=='-')
		{
			z=2;//减
		}
		else if(s[i]=='*')
		{
			z=3;//乘
		}
		else if(s[i]=='/')
		{
			z=4;//除
		}
	}
	//计算答案（注意转为两位小数）
	if(z==1)//加
	{
		if(a==-2)//?+b=c，?=c-b
		{
			printf("%.2f",(double)c-b);
		}
		if(b==-2)//a+?=c，?=c-a
		{
			printf("%.2f",(double)c-a);
		}
		if(c==-2)//a+b=?，?=a+b
		{
			printf("%.2f",(double)a+b);
		}
	}
	if(z==2)//减
	{
		if(a==-2)//?-b=c，?=b+c
		{
			printf("%.2f",(double)b+c);
		}
		if(b==-2)//a-?=c，?=a-c
		{
			printf("%.2f",(double)a-c);
		}
		if(c==-2)//a-b=?，?=a-b
		{
			printf("%.2f",(double)a-b);
		}
	}
	if(z==3)//乘
	{
		if(a==-2)//?*b=c，?=c/b
		{
			printf("%.2f",(double)c/b);
		}
		if(b==-2)//a*?=c，?=c/a
		{
			printf("%.2f",(double)c/a);
		}
		if(c==-2)//a*b=c，?=a*b
		{
			printf("%.2f",(double)a*b);
		}
	}
	if(z==4)//除
	{
		if(a==-2)//?/b=c，?=b*c
		{
			printf("%.2f",(double)b*c);
		}
		if(b==-2)//a/?=c，?=a/c
		{
			printf("%.2f",(double)a/c);
		}
		if(c==-2)//a/b=?，?=a/b
		{
			printf("%.2f",(double)a/b);
		}
	}
}
```

---

## 作者：to_be_continued (赞：2)

这题说句实话不应该只有这个难度，因为他的坑点还是很多的。

做几个判断，写几个函数，就好了。

根据自己做题的经验，总结出以下几个坑点

### 1 它是保留两位小数，按我的方法做的话，函数里面也要调用double类型不然返回值会是int类型。

### 2 在第一个数和符号之间，可能有数字，等号，问号。如果只是随手判断的话，就回是输出为0，因为你根本不知道符号是什么，我被这个坑了好长时间。

### 3 这个不会被零除，也不会爆错误。还是比较良心的，但是还是判断一下比较好。

```cpp

//who表示的是是那个是问号，1->a ,2->b ,3->c
//which 表示的是是哪个符号，1->+ ,2->- ,3->* ,4->/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

double answer=0;

char ch=0;

inline bool check(char x){//判断x是否是可用字符
	if (x<='9'&&x>='0'){
		return 0;
	}
	if (x=='+'||x=='-'||x=='*'||x=='/'){
		return 0;
	}
	if (x=='='){
		return 0;
	}
	if (x=='?'){
		return 0;
	}
	return 1;

}

inline int read(){
	int AK=1,IOI=0;
	while (ch<'0'||ch>'9'){
		AK=ch=='-'?-1:1;
		ch=getchar();
	}
	while (ch<='9'&&ch>='0'){
		IOI*=10;
		IOI+=ch-48;
		ch=getchar();
	}
	return AK*IOI;
}

int who=1,which;
//下面三个函数是用来算答案的
inline double math(double x,double y,double z){
	if (z==1){
		return y-x;
	}
	if (z==2){
		return x+y;
	}
	if (z==3){
		return y!=0?y/x:0;
	}
	if (z==4){
		return x*y;
	}
}
inline double math1(double x,double y,double z){
	if (z==1){
		return y-x;
	}
	if (z==2){
		return x-y;
	}
	if (z==3){
		return y!=0?y/x:0;
	}
	if (z==4){
		return x!=0?x/y:0;
	}
}inline double math2(double x,double y,double z){
	if (z==1){
		return y+x;
	}
	if (z==2){
		return x-y;
	}
	if (z==3){
		return x*y;
	}
	if (z==4){
		return x!=0?x/y:0; 	
	}
}

int main(){
	int first=0,second=0,third=0;
	ch=getchar();
	while (check(ch)) ch=getchar();	//首先先把前面没有用的处理掉
	if (ch=='?'){
		who=1;
	} else first=read();//然后处理第一个数
	while (ch!='+'&&ch!='-'&&ch!='/'&&ch!='*') ch=getchar();
//这就是一个坑点，如果写成while (check(ch)) ch=getchar()，那么就是67分
    
	if (ch=='+'){
		which=1; 
	} 
	if (ch=='-'){
		which=2;
	}
	if (ch=='*'){
		which=3;
	}
	if (ch=='/'){
		which=4;
	}
	ch=getchar();
	while (check(ch)) ch=getchar();	
	
	if (ch=='?'){
		who=2;
	} else second=read();//处理第二个数
	
	while (check(ch)) ch=getchar();
	ch=getchar();
 //这里处理出来是等号，等号对答案没有影响所以直接忽略
	while (check(ch)) ch=getchar();
	
	if (ch=='?'){
		who=3;	
	} else third=read();//处理第三个数
	
	if (who==1){
		printf("%0.2lf",math(second,third,which));
	}
	if (who==2){
		printf("%0.2lf",math1(first,third,which));
	}
	if (who==3){
		printf("%0.2lf",math2(first,second,which));
	}//算答案
}
```

代码长度大概1.9k左右。嗯算比较短了。

本人为C++蒟蒻，在此膜拜各位C++巨佬

---

## 作者：issue_is_fw (赞：1)

看这里看这里看这里！！！

虽然是一道模拟题，这题却没有那么繁琐。
基本思路很清晰

1、拿a[1],a[2],a[3]记录三个数，设置p指针初始等于1.遇到数字就读取在a[p]，p加加。遇到"?"也p加加，这样a,b,c的关系就很明了了。

2、我们知道了?的位置，就可以开始分情况讨论啦。```cpp

```
#include <bits/stdc++.h>
using namespace std;
const int inf=99999999;
string s;
int a[100];
int du(int l)
{
	int temp=0;
	for(int i=l;i<s.length();i++)
	{
		if(s[i]<'0'||s[i]>'9')	return temp;
		temp=temp*10+(s[i]-'0');
	}
	return temp;
}
int main()
{
	getline(cin,s);
	int p=1;
	int x=-1;
	a[1]=a[2]=a[3]=inf;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]>='0'&&s[i]<='9')//遇到数字就读取，然后修改i 
		{
			a[p++]=du(i);
			for(int j=i;j<s.length();j++)
				if(s[j]<'0'||s[j]>'9')//找到下一个不是数字的位置 
				{
					i=j-1;
					break;
				}
		}
		else if(s[i]==' '||s[i]=='=')	continue;
		else
		{
			if(s[i]=='?')	p++;
			else if(s[i]=='+')	x=1;
			else if(s[i]=='-')	x=2;
			else if(s[i]=='*')	x=3;
			else if(s[i]=='/')	x=4;
		}
	}
	double ans;
	if(a[1]==inf)
	{
		if(x==1)	ans=a[3]-a[2];
		if(x==2)	ans=a[3]+a[2];
		if(x==4)	ans=a[3]*a[2];
		if(x==3)	ans=a[3]*1.0/a[2]*1.0;	
	}
	else if(a[2]==inf)
	{
		if(x==1)	ans=a[3]-a[1];
		if(x==2)	ans=a[1]-a[3];
		if(x==4)	ans=a[1]*1.0/a[3];
		if(x==3)	ans=a[3]*1.0/a[1];		
	}	
	else
	{
		if(x==1)	ans=a[1]+a[2];
		if(x==2)	ans=a[1]-a[2];
		if(x==4)	ans=a[1]*1.0/a[2];
		if(x==3)	ans=a[1]*a[2];	
	}
	printf("%.2lf",ans);
}

---

## 作者：AnnGreen (赞：1)

很好奇为什么通过的都用的模拟而题解...都是些dalao一般的做法...

对于其他高级题解有可能看不懂，然而模拟就能a了的情况。

虽说模拟大家大概都会（毕竟像我这种巨菜无比的蒟蒻都能过），有可能有一些细节会把大家卡住，于是就发上来。

大体的思路就是：

1.读入

2.循环挨个儿判

3.记录加减乘除法以及未知数为第几个

4.根据记录进行计算

要注意的一个小坑：读入的数的十位和个位之间可能还会有多余的空格，所以要用类似于read一般的记录方式

其他的在代码的注释里写得很清楚了（其实都快接近于啰嗦了），应该不会有未照顾到的解释之处了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

int jj,figure,now=1;     //jj为记录加减乘除的变量(虽说这个变量名吧emmm...),figure为未知数所在的位置,now为目前该读入的数字. 
string s;          //存算式的字符串 
double a[4];          //存算式中的三个数 

int main()
{
    getline(cin,s);     //读入字符串 
    
    for(int i=0;i<s.size();i++)     //循环挨个儿判 
    {
        if(s[i]==' ') continue;     //空格就不管跳过 
        if(s[i]<'0'||s[i]>'9')     //符号就改jj变量 
        {
            if(s[i]=='+')
            {
                jj=1;     //加法jj为1 
                now++;     //说明目前第一个数已经读入,将n推后为读入第二个数做准备 
                continue;
            }
            if(s[i]=='-')          //同上 
            {
                jj=2;
                now++;
                continue;
            }
            if(s[i]=='*')
            {
                jj=3;
                now++;
                continue;
            }
            if(s[i]=='/')
            {
                jj=4;
                now++;
                continue;
            }
            if(s[i]=='=')     //等于号无法判断任何加减乘除法,只为读入第三个数做准备 
            {
                now++;
                continue;
            }
            if(s[i]=='?')
            {
                figure=now;     //说明未知数是目前应读入的数
                continue;
            }
        }
        if(s[i]>='0'&&s[i]<='9')     //读入数 
        {
                a[now]=a[now]*10+s[i]-'0';     //这道题有个小坑,就是数的十位和个位之间也可能会有多余的空格 
            continue;
        }
    }
    
    if(jj==1)     //加法 
    {
        if(figure==1)
        {
            printf("%0.2lf",a[3]-a[2]);
            return 0;
        }
        if(figure==2)
        {
            printf("%0.2lf",a[3]-a[1]);
            return 0;
        }
        if(figure==3)
        {
            printf("%0.2lf",a[1]+a[2]);
            return 0;
        }
    }
    else
    {
        if(jj==2)     //减法 
        {
            if(figure==1)
                {
                    printf("%0.2lf",a[2]+a[3]);
                    return 0;
                }
                if(figure==2)
                {
                    printf("%0.2lf",a[1]-a[3]);
                    return 0;
                }
                if(figure==3)
                {
                    printf("%0.2lf",a[1]-a[2]);
                    return 0;
                }
            }
            else
        {
            if(jj==3)     //乘法 
                {
                    if(figure==1)
                    {
                        printf("%0.2lf",a[3]/a[2]);
                        return 0;
                    }
                    if(figure==2)
                    {
                        printf("%0.2lf",a[3]/a[1]);
                        return 0;
                    }
                    if(figure==3)
                    {
                        printf("%0.2lf",a[1]*a[2]);
                        return 0;
                    }
                }
                else
            {
                if(jj==4)     //除法 
                    {
                        if(figure==1)
                        {
                            printf("%0.2lf",a[2]*a[3]);
                            return 0;
                        }
                        if(figure==2)
                        {
                           printf("%0.2lf",a[1]/a[3]);
                            return 0;
                        }
                        if(figure==3)
                        {
                           printf("%0.2lf",a[1]/a[2]);
                           return 0;
                        }
                    }
               }
           }
   }
    return 0;
}
```

---

## 作者：loi_hjh (赞：0)

朴素的算法：本题的思路就是把不是空格的字符存起来，实在没看懂dalao们快速幂+分解质因数是啥情况~~（走错片场）~~ 

## 附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define in inline
#define ri register int
using namespace std;
int l,n,flag=1,num[11],place;//读入的字符串长度，有效字符长度，当前搜到了a+(-,*,/)b=c中a，b，c的哪个区间，a，b，c的值，？在a+(-,*,/)b=c中处于a，b，c中的哪个位置
char a[1010],ch[1010],calculation;//读入的字符串，有效字符，运算符号 
int main(){
	gets(a+1);//读入整行，包括空格 
	l=strlen(a+1); 
	for(ri i=1;i<=l;i++)//存储有效字符 
		if(a[i]!=' ') ch[++n]=a[i];
	for(ri i=1;i<=n;i++){
		if(flag==1){//当前搜到了a区间 
			if((ch[i]>='0')&&(ch[i]<='9')) num[1]=num[1]*10+ch[i]-'0';//如果a是已知数，就算出a的值 
			if(ch[i]=='?') place=1;//？在a区间 
			if((ch[i]=='+')||(ch[i]=='-')||(ch[i]=='*')||(ch[i]=='/')){//存储运算符，然后搜b 
				calculation=ch[i];
				flag++;
			}
		}
		if(flag==2){//同理搜b 
			if((ch[i]>='0')&&(ch[i]<='9')) num[2]=num[2]*10+ch[i]-'0';//如果b是已知数，就算出b的值 
			if(ch[i]=='?') place=2;//？在b区间 
			if(ch[i]=='=') flag++;//搜到了=就去搜c 
		}
		if(flag==3){//同理搜c 
			if((ch[i]>='0')&&(ch[i]<='9')) num[3]=num[3]*10+ch[i]-'0';//如果c是已知数，就算出c的值 
			if(ch[i]=='?') place=3;//？在c区间 
		}
	}
	//当答案为整数时，直接输出整型，再输出.00，下面的注释可能有误，如有错误，请类比其他看代码 
	if((calculation=='+')&&(place==1)) printf("%d.00",num[3]-num[2]);//a+b=c-->a=c-b; 
	if((calculation=='+')&&(place==2)) printf("%d.00",num[3]-num[1]);//a+b=c-->b=c-a; 
	if((calculation=='+')&&(place==3)) printf("%d.00",num[1]+num[2]);//a+b=c-->c=a+b; 
	if((calculation=='-')&&(place==1)) printf("%d.00",num[2]+num[3]);//a-b=c-->a=b+c;
	if((calculation=='-')&&(place==2)) printf("%d.00",num[1]-num[3]);//a-b=c-->b=a-c;
	if((calculation=='-')&&(place==3)) printf("%d.00",num[1]-num[2]);//a-b=c-->c=a-c;
	if((calculation=='*')&&(place==1)) printf("%.2lf",num[3]*1.0/num[2]);//a*b=c-->a=c/b; 
	if((calculation=='*')&&(place==2)) printf("%.2lf",num[3]*1.0/num[1]);//a*b=c-->b=c/a; 
	if((calculation=='*')&&(place==3)) printf("%d.00",num[1]*num[2]);//a*b=c-->c=a*b; 
	if((calculation=='/')&&(place==1)) printf("%d.00",num[2]*num[3]);//a/b=c-->a=b*c;
	if((calculation=='/')&&(place==2)) printf("%.2lf",num[1]*1.0/num[3]);//a/b=c-->b=a/c;
	if((calculation=='/')&&(place==3)) printf("%.2lf",num[1]*1.0/num[2]);//a/b=c-->c=a/b;
	return ~~(0-0);
}

```

---

