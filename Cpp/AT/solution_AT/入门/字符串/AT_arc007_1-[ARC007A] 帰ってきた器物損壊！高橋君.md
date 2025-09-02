# [ARC007A] 帰ってきた器物損壊！高橋君

## 题目描述

有一天，高桥君发现电脑键盘中的一个键坏了，这个键即使按下也不会输出文字。

但是高桥君并不介意，所以决定继续使用那个坏掉的键盘。

给出高桥君打字的字符串和坏掉的键，请回答用坏了的键盘打字时的输出结果。

# 题解

## 作者：_Qer (赞：9)

题意：给定一个字符a和一个字符串s，将s中所有a去除后输出。

我们先解决字符串的问题，可以用一个char类型的变量不断输入，以达到输入字符串的目的。

然后来搞这个字符，只需在程序开头读入然后与每次输入的字符比较，若不相等则不用去掉它，按原样输出即可。

用char来做的原因是：一开始输入的是一个字符，而字符与字符比对最为方便，而且还省空间，一次处理一个字符也不容易（应该吧）出错，所以选用下面的方法。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c,x;//c存输入的字符串中的某个字符，x为去掉的字符
int main(){
    cin>>x;//先把去掉的读进来
    while(cin>>c){//不断输入，不输入时结束
        if(c!=x){//不相等
            cout<<c;//不用处理，直接输出
        }//如果是相等的就不会执行上面的输出，相当于去掉了
    }
    cout<<endl;//回车保险
    return 0;
}
```

---

## 作者：二字 (赞：3)

# 最短代码

### 本题其实不需要while(cin>>s)这样的东西因为数据全都是一个字符串，但这题坑点很多，只要不被坑基本AC稳稳的

下面贴代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	char x;
	cin>>x>>s;////坑点1！先输入字符再输入字符串！
	for(int i=0;i<s.length();i++) if(s[i]!=x) cout<<s[i];//坑点2！x不是'x'！ 
	cout<<endl;//坑点3！岛国题要换行！ 
	return 0; 
} 
```

是不是很简短？

---

## 作者：Cambridge (赞：1)

小学生又来发题解了！

这道题十分简单，但是我们要注意：要先读入字符，再读入字符串，然后将字符串的每一位逐一枚举，如果当前要输出的字符的按键没坏，就输出当前字符，否则不输出。

在思路这块，最后写上：AT不换行，爆零两行泪。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    char a;//定义字符
    string st1;//定义字符串
    int ll;//定义存储字符串长度的变量
    int main()
    {
        cin>>a>>st1;//读入
        ll=st1.size();//存储字符串长度
        for(int i=0; i<ll; i++)
        {
            if(a!=st1[i])cout<<st1[i];//如果这字符按键没坏，输出
            else continue;
        }
        cout<<endl;//AT题记得换行
        return 0;//要有好习惯
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：封禁用户 (赞：1)

 ### 古今多少话，都付代码中：
**字符串版**
```cpp
#fangweibiaoshi
#include<bits/stdc++.h>	//万能头文件
using namespace std;

string s;	//用string来存放字符串
int main (void)
{
	char x;	//坏掉的键
	ios::sync_with_stdio(0);
	cin>>x;
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==x)
			continue;	//如果这个字母是坏掉的键，跳过输出
		else
			cout<<s[i];
	}
	cout<<endl;	//空行勿忘
	return 0;
}
!
```
**数组版**

没想到吧，这题还能用数组来做！
```cpp
#fangweibiaoshi
#include<bits/stdc++.h>	//万能头文件
using namespace std;

char s[52];	//用数组来存放字符串
int main (void)
{
	char x;	//坏掉的键
	ios::sync_with_stdio(0);
	cin>>x;
	cin>>s;	//再次让你没想到，数组也可以当做字符串来读入！
	for(int i=0;i<50;i++)
	{
    	if(s[i]=='\0')	//由于把他当做字符串来读入，所以末尾会有一个'\0'标识符
        	break;	//跳出输出循环
		else if(s[i]==x)
			continue;	//如果这个字母是坏掉的键，跳过输出
		else
			cout<<s[i];
	}
	cout<<endl;	//空行勿忘
	return 0;
}
!
```



---

## 作者：远山淡影 (赞：1)

这题意思就是给你一个字符和一条字符串，让你从字符串中去掉所有的这个字符后输出。记得一定要换行！！！
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
char ss,st[2100];
int main()
{
	scanf("%c%s",&ss,st);
	for(int i=0;i<strlen(st);i++)//strlen是获取字符串长度的函数，很有用 
	{
		if(st[i]==ss) continue;//如果是坏掉的那个按键，就结束单次循环，continue是结束单次循环用的。 
		else printf("%c",st[i]);//如果是好的按键就直接输出。 
	}
	printf("\n");//换行，千万别忘了，我的正确率TOT 
	return 0;//程序拜拜
}
```

---

## 作者：RKcer21 (赞：1)

```
var
  c:char;
  s:string;//不告诉你字符数量，还是用字符串吧！爱用数组的还是另求高人吧！
  i,j,k,n,t,x,y:longint;
begin
  readln(c);//输入坏掉的键
  readln(s);//输入本来要打的键
  for i:= 1 to length(s) do
    if s[i]<>c then write(s[i]);//选择性替换，遇到坏掉的键不选择输出
writeln;    //本题不换行0分，要小心了！！！  
end.    
```

Pascal题解献上


---

## 作者：forever_0805 (赞：1)

这道题目实际上很简单的,首先:题目说了,先读入一个字符c,然后在读入一个字符串s,将这个字符串s中的所有字符c都给删去,就可以得出最后的答案了.

思路为:      
首先读入,      
然后就是将字符中的每个字符判断过去,如果不是就输出,如果是,就跳过

------------------------防抄袭-----------------------
-----------------------------------------------------

题解:      
```pascal
var      
  c:char;//定义字符c      
  s:string;//定义字符串s      
  i:longint;            
begin      
  readln(c);      //读入字符c      
  readln(s);      //读入字符串s      
  for i:= 1 to length(s) do//进入循环,将每个字符判断一遍      
    if s[i]<>c then write(s[i]);//判断      
  writeln;  //注意,本题必须要加换行      
end.   
``` 

---

## 作者：stry (赞：0)

我们可以用一个char类型的变量不断输入，以达到输入字符串的目的

接着我们只需在程序开头读入然后与每次输入的字符比较，若不相等则不用去掉它，按原样输出即可

若有不懂，详情看代码：
```
#include<bits/stdc++.h>
using namespace std;
char c,x;//c存输入的字符串中的某个字符，x为去掉的字符
int main(){
    cin>>x;//先把去掉的读进来
    while(cin>>c){//不断输入，不输入时结束
        if(c!=x){//不相等
            cout<<c;//不用处理，直接输出
        }//如果是相等的就不会执行上面的输出，相当于去掉了
    }
    return 0;
}
```
别吵哟，我动了手脚的

就算你发现了，但如果你抄了的话，你会变棕哟

---

## 作者：吕舒君 (赞：0)

C#题解第一人

```
//引用库
using System;

namespace ConsoleApp5
{
    class Program
    {
        static void Main(string[] args)
        {
        	//先读入一个字符【不是字符串，是为了后面替换才转成字符串】
            string b = Convert.ToChar(Console.Read()).ToString();
            //读掉换行符（类似get()）
            Console.ReadLine();
            //读入字符串
            string a = Console.ReadLine();
            //替换坏掉的字符
            a = a.Replace(b, "");
            Console.WriteLine(a);
        }
    }
}

```

---

## 作者：linus_li (赞：0)

本人看题的时候脑子停了一下，于是执拗的认为要先把要输出的字符串存起来，然后一起输出。于是写了以下程序：
```
    #include<stdio>
	char s[100];
	int main()
	{
		char error;
		scanf("%c", &error);
		scanf("%s", s);
		for(int i = 1; i < 59; i++)//用59是因为数据最大50
		{
			if(s[i] == error)
			{
				for(int j = i; j < 59; j++)
				{
					s[j] = s[j+1];//把后面的字符移到前面
				}
			}
		}
		printf("%s\n", s);//要输出换行符
	}
    ```
看着挺简单，然后我发现有几个点没过，于是我就试了一下全是错误字母的字符串，发现会输出一半。我就大概知道了——判断完一个字符后进行了移位操作，导致被移的第一个字符没有被判断。

即：s[1] == error,s[2] == error, s[3] = c,

移位后变成

   s[1] == error,s[2] == c, s[3] = s[4],
   
接下来就开始判断s[2]了，所以s[1]就被越过了，要解决这个问题，就把i减一位就好啦！

附上代码
```
	#include<stdio>
	char s[100];
	int main()
	{
		char error;
		scanf("%c", &error);
		scanf("%s", s);
		for(int i = 1; i < 59; i++)//用59是因为数据最大50
		{
			if(s[i] == error)
			{
				for(int j = i; j < 59; j++)
				{
					s[j] = s[j+1];//把后面的字符移到前面
                    i--//再次判断s[i]
				}
			}
		}
		printf("%s\n", s);//要输出换行符
	}
    ```

---

## 作者：jinhangjie2006 (赞：0)

```pascal
var
  jj:char;
  s:string;
  i,j,k,n,t,x,y:longint;
begin
  readln(jj);//破掉的键
  readln(s);
  for i:= 1 to length(s) do
    if s[i]<>jj then write(s[i]);//破掉的键打不出 打不出的不输出就行了
    writeln;//回车 不然0分
end.    
```

---

## 作者：国服第一蒟蒻 (赞：0)

第一次发题解，有不好的请指出。
这道题目是一道简单的模拟题，不多说了，直接附上代码：
```pascal
var i:longint;//i为循环变量
    s1:char;//放入已损坏的键
    s2:string;//存储要打出的语段
begin
  readln(s1);//读入
  readln(s2);//读入
  for i:=1 to length(s2) do
    if s2[i]<>s1 then 
      write(s2[i]);//如果这个文字所代表的键没有损坏，就输出
  writeln;//日本题标准换行
end.
```

---

## 作者：向日葵小班 (赞：0)

**题意：给定一个字符和一个字符串，将字符串中所有字符去除后输出。**


**哈哈，水啊，water啊，不愧是一道红题啊，哈哈哈...哈...哈...哈.....(破音)**


**思路：输入字符和一个字符串后，开一个循环，范围为0到字符串的长度，再循环里判断，如果字符串的第i个字符不等于那个被高桥君的一阳指点爆的字符，那么就输出字符串的第i个字符，循环完后要换行！！！**


## 又到了好玩又有趣的放代码时间

```cpp
#include<iostream>//头文件
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
string a;//a用来存字符串
char b;//b用来存字符
int main()
{
     cin>>b>>a;//输入要删除的字符b和高桥君打的字符串a
     for(int i=0;i<a.size();i++)//循环，范围为0到a的长度
     {
 		 if(a[i]!=b)//判断，如果如果字符串的第i个字符不等于b
 		 {
 		 	cout<<a[i];//就输出字符串的第i个字符
 		 }
     }
     cout<<endl;//AT大坑：注意AT要换行

    return 0;//结束啦
}
```
**作为本蒟蒻写的第6篇题解，~~luogu给过吧~~**


---

## 作者：变成一名fw (赞：0)

### 首先感谢 @da32s1da 的补充（WA了好几次）
题目大意，把坏的按键输出的字母~~和谐~~了

## 看看代码


```cpp
#include<bits/stdc++.h>//万能文件头
using namespace std;
int main()
{
	char a;
	string b;
	int len,i;
	cin>>a;
	cin>>b;//这里没空格，是换行，所以不用那么麻烦；
	len=b.size();//这一部分是string的strlen；
	for(i=0;i<len;i++)
	{
	if(b[i]==a)//如果相等就不需变化了；
	i=i;
	else
	cout<<b[i];
}
cout<<endl;//结尾换行保平安；
}
```

# 感谢你们对本蒟蒻的支持

---

