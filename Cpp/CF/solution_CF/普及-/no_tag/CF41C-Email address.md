# Email address

## 题目描述

Sometimes one has to spell email addresses over the phone. Then one usually pronounces a dot as dot, an at sign as at. As a result, we get something like vasyaatgmaildotcom. Your task is to transform it into a proper email address (vasya@gmail.com).

It is known that a proper email address contains only such symbols as . @ and lower-case Latin letters, doesn't start with and doesn't end with a dot. Also, a proper email address doesn't start with and doesn't end with an at sign. Moreover, an email address contains exactly one such symbol as @, yet may contain any number (possible, zero) of dots.

You have to carry out a series of replacements so that the length of the result was as short as possible and it was a proper email address. If the lengths are equal, you should print the lexicographically minimal result.

Overall, two variants of replacement are possible: dot can be replaced by a dot, at can be replaced by an at.



## 样例 #1

### 输入

```
vasyaatgmaildotcom
```

### 输出

```
vasya@gmail.com
```

## 样例 #2

### 输入

```
dotdotdotatdotdotat
```

### 输出

```
dot..@..at
```

## 样例 #3

### 输入

```
aatt
```

### 输出

```
a@t
```

# 题解

## 作者：Eason_AC (赞：1)

## Content
有一个字符串 $s$，它满足以下要求：

- 只包含 ``.``、``@`` 和小写字母。
- 不以 ``.`` 为开头或者结尾。
- 不以 ``@`` 为开头或者结尾，并只能包含一个 ``@``。

请将其进行如下操作，使得这个字符串长度最小：

- 将子串 ``dot`` 转化为 ``.``。
- 将子串 ``at`` 转化为 ``@``。

**数据范围：$1\leqslant |s|\leqslant 100$。**
## Solution
模拟就好，其实不需要什么 STL 里面的高级函数（只有一个 $\texttt{size}$ 函数）。

首先得要找到子串 $\texttt{dot}$ 和 $\texttt{at}$ 的位置，尤其要注意的是 ``@`` 最多只能用一次，所以开个变量判断一下。还有不能够在开头和结尾出现 ``.`` 或者 ``@``。
## Code
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int atflag;
string s;

int main() {
	cin >> s;
	int len = s.size();
	for(int i = 0; i < len;) {
		if(i > 0 && i < len - 3 && s[i] == 'd' && s[i + 1] == 'o' && s[i + 2] == 't') {
			printf(".");
			i += 3;
		} else if(i > 0 && i < len - 2 && s[i] == 'a' && s[i + 1] == 't' && !atflag) {
			printf("@");
			i += 2;
			atflag = 1;
		} else {
			printf("%c", s[i]);
			++i;
		}
	}
	return 0;
}
```

---

## 作者：hensier (赞：1)

# 大模拟！

这道题可以完美地利用$string$的相关系统函数操作。这里介绍本题所用的函数：

|函数名称|函数参数类型|功能|示例|
|-|-|-|-|
|$find$|$string$|在一个字符串中查找另一个字符串第一次出现的位置，查找不到则返回$string::npos$|$string$ s="121",t="1"，则$s.find(t)=0$|
|$replace$|$int,int,string$|从一个字符串中的某个位置开始，后续几个字符删除，并用另一个字符串替代|$string$ s="123123",t="@#!"，则$s.replace(0,3,t)$的运行结果为"@#!123"

接下来我们来分析思路。首先输入字符串，并不停地查找是否有"$at$"和"$dot$"，只要有就删掉并替换。

然后进行特判——如果字符串开头结尾为$@$或$.$就用$at,dot$替换。

如果用多个$@$，就从后往前替换——把$@$换成$at$，直到只剩下一个。

$AC$代码：
```cpp
#include<iostream>
using namespace std;
string s;
int n,i,p=-1;
void f(char c,string t)//特判函数
{
    if(s[0]==c)s.replace(0,1,t);
    if(s[s.size()-1]==c)s.replace(s.size()-1,1,t);
}
int main()
{
    cin>>s;
    while(s.find("at")!=string::npos)s.replace(s.find("at"),2,"@");//不停地替换
    while(s.find("dot")!=string::npos)s.replace(s.find("dot"),3,".");
    f('.',"dot");
    f('@',"at");//调用函数进行特判
    for(;s[i];i++)
    {
        if(s[i]=='@')
        {
            if(!n)p=i;
            n++;//n保存@的个数，p为第一个@的位置
        }
    }
    if(n<2)
    {
        cout<<s;
        return 0;
    }//如果只有一个或没有@就直接输出并结束程序
    for(i=s.size()-1;i>=0;i--)//从后往前替换
    {
        if(s[i]=='@')
        {
            s.replace(i,1,"at");//替换
            if(--n==1)//如果只剩一个就输出并结束程序
            {
                cout<<s;
                return 0;
            }
        }
    }
}
```

---

## 作者：TLMPEX (赞：0)

这是一道简单模拟题，边模拟边输出。但要注意一个字符串只能出现一个```@```并不能在开头和结尾，还有```.```也不能在开头和结尾，其他就没什么好说的了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
string k;
int main(){
	int i,ok=0;//ok一定要初始化
	cin>>k;
	for(i=0;i<k.size();i++){
		if(k[i]=='a'&&k[i+1]=='t'&&i!=0&&i!=k.size()-2&&!ok){
			cout<<"@";
			i++;
			ok=1;
			//如果这个字母和后面一个字母构成“at”且不在开头和结尾，并第一次出现，输出“@”并标记有过一个“@”了。
		}
		else if(k[i]=='d'&&k[i+1]=='o'&&k[i+2]=='t'&&i!=0&&i!=k.size()-3){
			cout<<".";
			i+=2;
			//操作原理同上
		}
		else cout<<k[i];//如果只是普通的小写字母直接输出
	}
}
```


---

## 作者：__polar_ice (赞：0)

~~这是我发布的第一篇题解~~

---
这道关于**邮箱**的题其实挺有意思的

我就发一个`正常`的思路

在读入之后通过$if$语句直接寻找doc和at的位置

题目中不让在开头和结尾出现**doc**和**at**

所以**直接输出**头和尾是一个好办法，再特判末尾有没有出现dot和at就行了

就像这样：
---

输入$1$（自编）

`dotdotdotdotdotbaidudotcomatat`

很容易得出结果为`dot....baidu.com@at`

所以直接输出头和尾相当于判断的字符串为`otdotdotdotdotbaidudotcomata`

最后再对于原字符串末尾的"$tat$"部分**特判**即可

----

输入$2$（自编）

`atdotdoadotatdotdot`

去头去尾后判断`tdotdoadotatdotdo`

特判原字符串"$dot$"部分

输出：`at.doa.@.dot`

---

所以**上代码**

$code$


```cpp
#include<cstdio>
#include<cstring>

//using namespace std;
char s[105];
int len;

bool d=0;//判断at的位置，标记at是否出现
int main()
{
    scanf("%s",s);//不用‘&’
    len=strlen(s);
    printf("%c",s[0]);//头和尾直接输出，不用特判
    for(int i=1;i<len-1;++i)//搜索除头和尾的部分
    {
        if((s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t')&&(i!=len-3))//判断dot
        /*“i!=len-3”防止dot出现在最后三个字符里*/
        {
            printf(".");
            i+=2;
            continue;//跳过ot
        }
        if((s[i]=='a'&&s[i+1]=='t')&&!d&&(i!=len-2))//判断at，第一个出现的位置
        {
            printf("@");
            i++,d=1;
            continue;//跳过t
        }
        /*“i!=len-2”防止at出现在最后两个字符里*/
        printf("%c",s[i]);//如果不是dot和at就直接输出
    }
    printf("%c",s[len-1]);//直接输出尾
    return 0;
}
```

`谢谢`~

---

## 作者：_Dominater (赞：0)

## 这是一道很好的~~水题~~
First,先从材料分析

①将子串“dot“转换为‘.’（小数点）

②将子串”at“转换为‘@’

一个正确的电子邮件地址满足以下条件：

①只包含小数点(.)，符号(@)和小写的拉丁字母

②不以一个点开始，也不以点结束

③不以一个‘@’符号开头或结尾

④恰好包含一个‘@’，但它可能包含任何东东

⑤使得电子邮件地址尽可能地短，如果长度相同则输出字典序最小的

**可得出一下结论:**

1.将"dot"改为"."

2.将"at"改为"@"

3.开始先判断是否有"@".有,就不要转换了.没有,转换一次就  不要转了,需要特判:
```
bool flag;
char a[101];
for(int i=0;i<len;i++)
    if(a[i]=='@') flag=true;
```
4.电子邮件地址前不能出现"@"或".".
## 话不多说,请看代码:
```
#include<bits/stdc++.h>//万能脑袋
using namespace std;
char a[101];
int len;
string s;//读取answer
bool flag;//flag记录是否存在"@"
int main()
{
    scanf("%s",&a);//输入,千万不可用gets,洛谷会判错
    len=strlen(a);
    for(int i=0;i<len;i++)
        if(a[i]=='@') flag=true;//特判,刚刚说过
    for(int i=0;i<len;i++)
    {
    	if(a[i]=='d'&&a[i+1]=='o'&&a[i+2]=='t'&&i!=0&&i!=len-3)//特判是否在最前或末尾
    	   s+='.',a[i]=' ',a[i+1]=' ',a[i+2]=' ';
    	if(a[i]=='a'&&a[i+1]=='t'&&i!=0&&i!=len-2&&flag==false)//特判是否在最前或末尾,以及是否出现"@"
		   s+='@',a[i]=' ',a[i+1]=' ',flag=true;//将不要的变成"空气",用flag告诉不要转"@"了
		else if(a[i]!=' ') s+=a[i];//将非"空气"读入answer
	}
	cout<<s;//输出答案    
	cout<<endl;//无聊
	return 0;
}
```
如果小伙伴们还有想刷水题的,可以试试如下题:

[P1308](https://www.luogu.com.cn/problem/P1308),
[P1067](https://www.luogu.com.cn/problem/P1067)
[P1117](https://www.luogu.com.cn/problem/P1117)



---

## 作者：outis_crypt (赞：0)

补充一个Java的吧。

**介绍一下Java中String类的replaceAll(String regex, String replacement)方法**

简单来说，就是将当前String对象中与regex匹配的子字符串序列全部替换成replacement代表的字符。

**例如将 字符串中的 " dot " 全部换成 " . "    ，就可以用下列代码**

**String regex="dot";**

**"dotdotdotatdotdotat".replaceAll(regex, ".");**


**替换完 " dot " 之后，找到第一个 " at " 的位置，换成 " @ "**

**最后特判一下首尾是否为 ' . '， 是的话就换成 " dot "**




完整代码如下：
```java
import java.util.*;
public class Main {
	public static void main(String[] args){
		Scanner reader=new Scanner(System.in);
		String string=reader.next();   //输入
		String regex="dot";
		string=string.replaceAll(regex, "."); //将所有 "dot" 换成 "."
		int i=0;
		for(i=1;i<string.length()-1;i++) {
			if(string.substring(i, i+2).equals("at")) {
				break;
			}
		}     //找第一个"at"所在的位置
		String a=string.substring(0,i)+"@"+string.substring(i+2); //替换第一个"at"为"@"
		if(a.charAt(0)=='.') {  //特判首尾是否为 "."
			a="dot"+a.substring(1);
		}
		if(a.charAt(a.length()-1)=='.') {
			a=a.substring(0,a.length()-1)+"dot";
		}
		System.out.println(a);  //输出
	}
}
```


---

## 作者：学霸壹号 (赞：0)

这道题我们可以用一个新的思路来解决它。
首先，读入应该没什么大不了的，我们读入一个字符串$s$。
```cpp
cin>>s;
```
接下来，我们不管那些~~乱七八糟的~~标点符号的用法，直接往上搞，当然，搞完后不打印输出，例如第二个样例我们在后台会把它弄成
```
...@..@
```
这个字符串我们把它叫做$x$。这一段你会写吗？应该很简单，我就给你看一下循环里的if语句。
```cpp
if(i+2<s.size()&&s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t'){
	x+='.';
	i+=2;
}
else if(i+1<s.size()&&s[i]=='a'&&s[i+1]=='t'){
	x+='@';
	++i;
}
else
	x+=s[i];
```
接下来，我们判断一下头和尾是否符合条件。

判断完后应该是这个样纸滴：
```
dot..@..at
```
你懂得这个意思了吗？如果两边的不符合要求，那么把它换成字母，可以存在$ans$里。
```cpp
if(x[0]=='@')
	ans+="at";
if(x[x.size()-1]=='@'){
	x.erase(x.size()-1);
	x+="at";
}
if(x[0]=='.')
	ans+="dot";
if(x[x.size()-1]=='.'){
	x.erase(x.size()-1);
	x+="dot";
}
if(x[0]!='@'&&x[0]!='.')
	ans+=x[0];
```
你有没有发现如果是最后一个字母有问题，并不把它存进去？后面我们会做的。

有些人说：“很好，这就是我想要的结果，打印吧。”

错的，如果中间有多个@，例如
```
abc@abc@abc
```
那怎么办？~~尽管这个电子邮箱有点不太靠谱哈~~

我们还要判断，并且我们刚刚只处理了第一个字符啊！

先弄个$j$。
```cpp
int j=1;
```
$j$是用来记处理到哪一位了，由于第$0$位已经处理过，我们把$j$设成$1$。

我们现在出发，找第一个@，这个@及前面的字符都是可以的，不是吗？
```
while(x[j]!='@'){
	ans+=x[j];
	++j;
}
```
这个循环结束后，$x[j]$一定是@，所以我们把@加入$ans$，同时++$j$。
```cpp
while(x[j]!='@'){
	ans+=x[j];
	++j;
}
ans+='@';
++j;
```
后面的@一律不算数~
```cpp
while(j<x.size()){
	if(x[j]!='@')
		ans+=x[j];
	else
		ans+="at";
	++j;
}
```
打印吧，已经OK了
```cpp
cout<<ans<<endl;
```
最后结束程序。
```cpp
return 0;
```
---
~~完整代码大家自己拼吧~~

---

## 作者：灵光一闪 (赞：0)

Aya，怎么感觉dalao的方法好腻害啊，我只好发一个我懂的……

思路大家都能想出来，但是这个题有
# 坑！
注释在代码里，大家轻喷
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
string s;
string t;
bool flag;
int main(){
    cin>>s;
    for(int i=0;i<s.size();){
        if(s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t'&&(i!=0&&i!=s.size()-3)){//如果这块可以组成dot也不在两端的话就放进t里
            t+='.';
            i+=3;//因为"dot"是三个字符
        }
        else if(s[i]=='a'&&s[i+1]=='t'&&(i!=0&&i!=s.size()-2)&&!flag){//跟上面差不多，flag是用来保证只有一个"@"的
            t+='@';
            i+=2;//因为"at"是两个字符
            flag=true;
        }
        else{//如果都不是就按常规来
            t+=s[i];
            i++;
        }
    }
    cout<<t<<endl;
    return 0;
}
```
1. 看清题意，不要犯一些基本错误

2. 交题前先试图hack一下自己，比如一些很坑的地方，然后AC率就会高很多

The End.

---

## 作者：落灰 (赞：0)

~~怎么没人发题解~~

## **按题目要求一步一步做就可以了**

### **找一找dot和at**
```
bool chdot(int i)
{
    if(s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t')
        return true;
    return false;
}
bool chat(int i)
{
    if(s[i]=='a'&&s[i+1]=='t')
        return true;
    return false;
}
```
### 接下来就慢慢跑循环啦，**注意这个循环中i的增加方式**
```
for(int i=0;i<s.size();)
    {
        if(i!=0&&i+2!=s.size()-1&&s[i]=='d'&&chdot(i))
        {
            ans.push_back('.');
            i+=3;
            continue;
        }
        if(!u&&i!=0&&i+1!=s.size()-1&&s[i]=='a'&&chat(i))
        {
            ans.push_back('@');
            i+=2;
            u=true;
            continue;
        }
        ans.push_back(s[i]);
        i++;
    }
```
#### AC代码：
```
#include<bits/stdc++.h>
using namespace std;
string s,ans;
bool u=false;
bool chdot(int i)
{
    if(s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t')
        return true;
    return false;
}
bool chat(int i)
{
    if(s[i]=='a'&&s[i+1]=='t')
        return true;
    return false;
}
int main()
{
    cin>>s;
    for(int i=0;i<s.size();)
    {
        if(i!=0&&i+2!=s.size()-1&&s[i]=='d'&&chdot(i))
        {
            ans.push_back('.');
            i+=3;
            continue;
        }
        if(!u&&i!=0&&i+1!=s.size()-1&&s[i]=='a'&&chat(i))
        {
            ans.push_back('@');
            i+=2;
            u=true;
            continue;
        }
        ans.push_back(s[i]);
        i++;
    }
    for(int i=0;i<ans.size();i++)
        cout<<ans[i];
    return 0;
}
```
### 于是，完了。

---

## 作者：EAT_NH4HCO3 (赞：0)

这题实际上很简单
就用replace函数来模一模就好了
其他的细节最后再处理~~（因为我懒）~~

```
//Codeforces
//41C Email Address

#include<bits/stdc++.h>

using namespace std;

string s;
bool flag=0;//记录@是否使用过

void error_deal()//处理开头和结尾的字符
{
	if(s[0]=='.')s.replace(0,1,"dot");
	if(s[(int)(s.length()-1)]=='.')s.replace((int)(s.length()-1),1,"dot");
}

int main()
{
	ios_base::sync_with_stdio(false);
	
	cin>>s;
	
	for(int i=0;i<(int)s.size();++i)
	{
		if(i!=0&&i!=(int)s.length()-1-1&&!flag&&s[i]=='a'&&s[i+1]=='t')//判断@的位置
		{
			s.replace(i,2,"@");
			flag=1;
		}
		
		if(s[i]=='d'&&s[i+1]=='o'&&s[i+2]=='t')//一次性处理掉所有dot
			s.replace(i,3,".");
	}
	
	error_deal();//再把开头结尾的dot恢复
	
	cout<<s<<endl;
	
	return 0;
}
```

---

