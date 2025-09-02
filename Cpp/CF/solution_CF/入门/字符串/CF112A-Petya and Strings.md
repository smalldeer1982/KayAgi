# Petya and Strings

## 题目描述

输入两个字符串，大小写无关紧要，比较它们的大小。

## 样例 #1

### 输入

```
aaaa
aaaA
```

### 输出

```
0
```

## 样例 #2

### 输入

```
abs
Abz
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
abcdefg
AbCdEfF
```

### 输出

```
1
```

# 题解

## 作者：jeremyjy (赞：9)

**蒟蒻第一次写题解……先卖个萌0=w=0**

这道题是道字符串入门题，思路很简单。先大写转小写，再比大小即可！

话不多说，上代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int main()
{
	string a,b;//定义字符串（也可用char数组）
	int i;
	cin>>a>>b;//输入
	for(i=0;i<a.size();i++)
		if(a[i]>='A'&&a[i]<='Z')//转小写
			a[i]+=32;
	for(i=0;i<b.size();i++)
		if(b[i]>='A'&&b[i]<='Z')//同上
			b[i]+=32;
	if(a<b)
		cout<<-1;//比大小
	else
		if(a==b)
			cout<<0;//同上
		if(a>b)
			cout<<1;//同上
	return 0;//好习惯，好人生
}
```

---

## 作者：哔哩哔哩 (赞：5)

一道水题

估计CF比赛时秒切的有很多人吧

```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[105],s2[105];
int main()
{
	cin >> s1 >> s2;
	int l1 = strlen(s1), l2 = strlen(s2);
	for (int i = 0; i < l1; i++) s1[i] = towlower(s1[i]);
	for (int i = 0; i < l2; i++) s2[i] = towlower(s2[i]);
	int ans = strcmp(s1, s2);
	printf("%d", ans==0?0:(ans>0?1:-1));
	return 0;
}
```

思路：
1. 全部统一大小写

2. C++ strcmp

---

## 作者：云浅知处 (赞：5)

## [$\operatorname{CF112A}$](https://www.luogu.com.cn/problem/CF112A)题解

$\operatorname{step}\!1$：审题
***
输入两个字符串，大小写无关紧要，比较它们的大小。
***
$\operatorname{step}\!2$：做题

先来介绍一下$\operatorname{C}++$中自带的字符串比较程序：```strcmp```

其原型为：

```int strcmp(const char *a,const char *b)```

其返回值为：

>当字符串a大于字符串b时，返回一个正值；

>当字符串a等于字符串b时，返回0；

>当字符串a小于字符串b时，返回一个负值；

不过，如果你使用```==```来比较$\operatorname{C}$风格字符串，那么返回值永远是```false```。

这是因为在使用```==```比较$\operatorname{C}$风格字符串时，你实际上是在比较这两个$\operatorname{C}$风格字符串的地址。

这牵扯到指针，这里就不多说了。

举个例子：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char str1[10]="Hello";
    char str2[10]="Hello";
    if(str1==str2){
        cout<<"Equal\n";
    }
    else{
        cout<<"Not equal\n";
    }//此时程序会输出“Not equal”
    if(strcmp(str1,str2)==0){
        cout<<"Equal\n";
    }
    else{
        cout<<"Not Equal\n";
    }//此时程序会输出"Equal"
    return 0;
}
```

运行结果为：
```cpp
Not equal
Equal
```
***
~~自认为已经清楚地讲完了```strcmp```的用法~~
***
不过，由于题中说：

>大小写无关紧要

所以我们还需要把这两个字符串统一成小写。
***
此时我们还不知道这两个字符串的长度，可以使用```strlen```来读取$\operatorname{C}$风格字符串的长度。

使用方法如下：

```cpp
//头文件什么的就不写了吧
char s[10];//定义一个C风格字符串
cin>>s;//输入
int n=strlen(s);//将这个字符串的长度赋值给n
cout<<n;
//......
```
如果我们输入：```hello```

程序将会输出：```5```

知道了字符串的长度之后，我们就可以遍历整个字符串，如果有大写字母，那么就转化为小写字母。

具体的转换如下：
```cpp
char ch;
cin>>ch;
if(ch>='A'&&ch<='Z') ch+=32//转化为小写,这里加32是因为小写字母的ASCII码比大写字母多32.
cout<<ch;
```
***
第三步：开写代码！
```cpp
//————————————————————————————————————
//—————————————CF112A.cpp—————————————
//————————————————————————————————————
＃include<algorithm>
＃include<bitset>
＃include<bits/stdc++.h>
＃include<cstdlib>
＃include<cstring>
＃include<cctype>
＃include<cstddef>
＃include<csetjmp>
＃include<cstdarg>
＃include<climits>
＃include<deque>
＃include<exception>
＃include<fstream>
＃include<functional>
＃include<iosfwd>
＃include<iterator>
＃include<iostream>
＃include<list>
＃include<locale>
＃include<limits>
＃include<memory>
＃include<map>
＃include<numeric>
＃include<new>
＃include<ostream>
＃include<queue>
＃include<stdexcept>
＃include<set>
＃include<stack>
＃include<sstream>
＃include<streambuf>
＃include<string>
＃include<typeinfo>
＃include<utility>
＃include<valarray>
＃include<vector>
＃include<wctype.h>
＃include<wchar.h>//一大波头文件汹汹来袭
using namespace std；
//————————————————————————————————————
int main（）｛
	char str1[105]，str2[105]，len，ans；//str1,str2是题目中输入的两个字符串，len是长度，ans是这两个字符串比较的结果
	cin>>str1>>str2；//输入
	//————————————————————————————————
	//————————————————————————————————
	len＝strlen（str1）；//将这两个字符串的长度赋值给len
	for（int i=0；i<len；i++）｛//遍历两个字符串
		if（str1［i］>＝'A'&&str1［i］<＝'Z'）｛//如果有大写字母
			str1［i］＋＝32；//转换为小写
		｝
		if（str2［i］>＝'A'&&str2［i］<＝'Z'）｛//同上
			str2[i]+=32；
		｝
	｝
	ans＝strcmp（str1，str2）；//比较两个字符串
	//————————————————————————————————
	//————————————————————————————————
	if（ans>0）｛//如果第一个字符串小于第二个字符串
		cout<<1；//输出"-1"
	｝
	if（ans==0）｛//如果第一个字符串等于第二个字符串
		cout<<0；//输出"0"
	｝
	if（ans<0）｛//如果第一个字符串大于第二个字符串
		cout<<-1；//输出"1"
	｝
	return 0；//程序结束
｝
//防伪处理过了，复制粘贴保证CE。
```
最后：

$\Huge\color{red}\text{共创文明洛谷，拒绝Ctrl+C!!!}$

---

## 作者：SKTelecomT1_Faker (赞：3)

这道题难度系数不大，供新手完成。

思路：先输入两个字符串，之后把字符串统一转化为大写（我的爱好，小写当然也可以），之后直接用运算符号比较就行了，这是string一个很方便的地方。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main( )
{
	string s1,s2;//定义字符串
    cin>>s1>>s2;
    for(int i=0;i<s1.size();i++)//把小写转为大写
        if(s1[i]>='a'&&s1[i]<='z') s1[i]-=32;//A与a在ASCII码中差了32位
    for(int i=0;i<s2.size();i++)//字符串长度用size来算
        if(s2[i]>='a'&&s2[i]<='z') s2[i]-=32;
    if(s1>s2) cout<<"1"<<endl;//按题意输出
    if(s1==s2) cout<<"0"<<endl;
    else cout<<"-1"<<endl;
	return 0;
}
```

下面我介绍一下ASCII码（很常用的）

ASCII ((American Standard Code for Information Interchange): 美国信息交换标准代码）是基于拉丁字母的一套电脑编码系统，主要用于显示现代英语和其他西欧语言。它是最通用的信息交换标准，并等同于国际标准ISO/IEC 646。ASCII第一次以规范标准的类型发表是在1967年，最后一次更新则是在1986年，到目前为止共定义了128个字符，现在的编程软件基本上都用这种方式进行储存字符。

接下来发一张表：
[点我](https://baike.baidu.com/pic/ASCII/309296/0/e850352ac65c103880a07b53bc119313b17e8941?fr=lemma&ct=single#aid=0&pic=e850352ac65c103880a07b53bc119313b17e8941)

这就是所有字符表示方法，希望对大家有帮助

---

## 作者：天有不测风云 (赞：1)

先来分析题一下题目。

因为本题处理的字符串不区分大小写，所以可以考虑把字符串中的字符全部转换成大写或小写，再比较（本题解使用的方法为大写转小写）。

下面贴上我的代码，正版防抄代码，~~不用在意码风~~：

------------

```cpp
#<iostream>//输入输出头文件
#<string>//字符串头文件
using namespace std;//名字空间
long long a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;//不用在意这个
string S1,S2；//定义字符串变量
main()
{
	cin>>S1>>S2；//输入数据
	for(i=0;i<S1.size();i++）//转换第一个字符串的大小写
	{
		if(S1[i]>='A'&&S1[i]<='Z'）
		{
			S1[i]+=32；//大小写字符相差32
		}
	}
	for(i=0;i<S2.size();i++)//转换第一个字符串的大小写
	{
		if(S2[i]>='A'&&S2[i]<='Z'）
		{
			S2[i]+=32；//同上
		}
	}
   //输出
	if(S1>S2）
	cout<<1<<endl；
	if(S1<S2)
	cout<<-1<<endl；
	if(S1==S2)
	cout<<0<<endl；
	return 0;
}
```


---

## 作者：boshi1 (赞：1)

### 嘿！Python也有转大小写函数，也适用于字符串

$Python$转大小写函数分为三种，分为$lower$,$upper$和$capwords$。$lower$是
把字符串转小写，$upper$转大写。而$capwords$是把字符串里每个单词首字母大写，其他小写，不禁钦佩与$Python$的强大

话不多说，上代码：

```python
n=input();m=input();n=n.lower();m=m.lower()
if n>m:
    print(1)
elif n<m:
    print(-1)
else:
    print(0)
```

---

## 作者：封禁用户 (赞：1)

[这篇题解](https://www.luogu.org/blog/jeremyJ/cf112a-ti-xie)供习惯使用$\texttt{std::string}$的同学参考。

如果不用$\texttt{std::string}$而用$\texttt{char[]}$，应该使用[$\color{red}\texttt{strcmp}$](http://zh.cppreference.com/w/cpp/string/byte/strcmp)比较两个字符串的字典序。

下面为reference的节选：
> ```cpp 
int strcmp( const char *lhs, const char *rhs ); 
```
### 返回值 
- 若字典序中 `lhs` 先出现于 `rhs` 则为负值。
- 若 `lhs` 与 `rhs` 比较相等则为零。
- 若字典序中 `lhs` 后出现于 `rhs` 则为正值。

可以发现，返回值的符号正是我们想要的！

所以，定义符号函数

$$sgn\ x=\left\{\begin{aligned}1 & & {x>0}\\0 & & {x=0}\\-1 & & {x<0}\\\end{aligned}\right.$$

则输出$sgn\ \texttt{strcmp(a,b)}$即可。

```cpp
#include <cstdio>
#include <cctype>//tolower
#include <cstring>//strlen strcmp
inline int sgn(int x){
    if(x==0) return 0;
    return (x>0)?1:-1;
}
int main(){
    static char a[101],b[101];
    scanf("%s %s",a,b);
    for(int i=0,j=strlen(a);i<j;++i)
        a[i]=tolower(a[i]);//统一转化为小写字符以便比较
    for(int i=0,j=strlen(b);i<j;++i)
        b[i]=tolower(b[i]);
    printf("%d",sgn(strcmp(a,b)));
}
```

---

## 作者：hensier (赞：0)

这题如果不用字符串去做的话，可以使用$char*$，并用$strcmp$比较。本题中用了有关$strcmp$和引用、指针的用法。

在很多$void$函数的参数中都有引用的地址。例如：

```cpp
void swap(int &a,int &b)//参数都引用原变量
{
    int t=b;
    b=a;
    a=t;
}
```

上述函数中，如果不引用原变量就会是：

```cpp
void swap(int a,int b)//正常参数
{
    int t=b;
    b=a;
    a=t;
}
```

不引用原变量的函数无任何实际效果，只不过是在函数内部进行操作。因此，只有引用原变量，才能直接影响到主函数中使用该参数的变量。因此相似地我们可以编写下列函数：

```cpp
inline void f(char &c)
{
    if(c>='A'&&c<='Z')c-='A'-'a';
}
```

这个函数的参数是$\&c$，函数的意图也很简单，即把大写转换为小写。而虽然我们可以用$char$函数加一个判断取而代之，但是用$void+$引用就只需要一行代码就能完成，方便、简洁、快速。

关于$strcmp$的用法：

$strcmp$函数包含在$cstring$库中，因此要调用该头文件。假设我们有两个字符数组$a[20],b[50]$，而它们是这样的：

|$0$|$1$|$2$|$3$|$4$|$5$|$6$|...|$19$|$20$|...|$49$|$50$|$...$
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|$a$|$N$|$O$|$I$|$P$|$!$|\\$0$|||$-$|$-$|$-$|$-$|$-$|
|$b$|$N$|$O$|$I$|$P$|$!$|\\$0$||||||$-$|$-$|

上述表格中的\\$0$字符表示空字符，虽然无含义，但包含在字符数组中。表格中的$-$表示超出数组范围。而如果比较$a==b$，则永远返回假，因为$a,b$的数组元素总数不同。这时就需要$strcmp$的帮助。$strcmp$对于相同内容的两个字符数组返回$0$，不同返回$1$。

例如：$strcmp(a,b)$返回$0$（$a,b$均为"$NOIP!$"，但数组元素一个为$20$，一个为$50$，与上述相同。

如果我们新建$string$ $a,b$，赋值与上述相同的话，$a==b$就会返回真，即满足$a==b$。然而在字符数组中需要多加注意。

~~啰嗦了许久，你们等急了的~~$AC$代码~~来了~~：

```cpp
#include<cstdio>
#include<cstring>
char a[101],b[101];
int i,s[2]={-1,1};
inline void f(char &c)//inline节约时间，char类型变量c必须必须必须加取引用符号，否则该函数没有任何效果，满盘皆输！
{
    if(c>='A'&&c<='Z')c-='A'-'a';//统一转换为小写
}
int main()
{
    scanf("%s%s",a,b);
    for(;a[i];i++)
    {
        f(a[i]);
        f(b[i]);//a，b长度相等，所以一起转换为小写
    }
    if(!strcmp(a,b))printf("0");//用strcmp判断，相同为0，不同为1。
    else
    {
        for(i=0;a[i];i++)
        {
            if(a[i]!=b[i])
            {
                printf("%d",s[a[i]>b[i]]);//只要有不同就直接返回，如果a比b大就返回1，否则返回-1。s数组的目的是为了方便输出
                return 0;//直接退出程序
            }
        }
    }
}
```


---

## 作者：_cmh (赞：0)

这一题，估计很多人秒切把。。。

## ~~淼~~

本题，看到题目，我立刻想起了tolower和string

普及一下本题用到的方法：

1.用tolower能把不管大小写字符都转为小写

2.转为大写的则是toupper

3.string可以两个字符串直接比较是否相等

4.cout里可以直接写表达式

上代码（具体看注释）

```cpp
#include<iostream>//头文件 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
string a,b;//string定义字符串 
int main(){
	cin>>a>>b;//读入字符串 
	for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);//将A.B两个字符串都转为小写，转成大写就用toupper
	for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);
	cout<<!(a==b);//输出是否相等 
 	return 0;
}
```

**求赞！！！**

~~（逃）~~

---

## 作者：一滴小水滴 (赞：0)

## 这道题...真的是不能再水了... 直接用string比较两个字符串的大小就可以了
### 但是，首先我们要把字符都变成小写/大写，这里我是把所有字符变成小写。

```cpp
	for(int i=0;i<a.size();i++)
		if(a[i]>='A'&&a[i]<='Z')a[i]=a[i]-'A'+'a';
	for(int i=0;i<b.size();i++)
		if(b[i]>='A'&&b[i]<='Z')b[i]=b[i]-'A'+'a';
         //如果这是一个大写字母，就将它变成其对应的小写字母。
```

### 然后就可以直接比较a和b的大小了（C++的string可以直接用比较符号判断字典序大小）。

```cpp
	if(a>b)cout<<1<<endl;
	else if(a<b)cout<<-1<<endl;
	else cout<<0<<endl;
```
***

### 完整代码如下：
```cpp
#include<bits/stdc++.h>    //万能脑袋就不用说了。
using namespace std;
int main()
{
	string a,b;
	getline(cin,a);
	getline(cin,b);
	for(int i=0;i<a.size();i++)
		if(a[i]>='A'&&a[i]<='Z')a[i]=a[i]-'A'+'a';
	for(int i=0;i<b.size();i++)
		if(b[i]>='A'&&b[i]<='Z')b[i]=b[i]-'A'+'a';
        	//更改
	if(a>b)cout<<1<<endl;
	else if(a<b)cout<<-1<<endl;
	else cout<<0<<endl;
    		//比较
	return 0;
       //结束
}
```
***

## 这道水题相信大家都能不出INF遍就AC，那就快点吧！

---

