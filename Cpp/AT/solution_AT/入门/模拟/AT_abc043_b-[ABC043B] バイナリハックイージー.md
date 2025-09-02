# [ABC043B] バイナリハックイージー

## 题目描述

しぐ制作了一款键盘。这款键盘极致简约，仅有三个按键：`0` 键、`1` 键和退格键。

首先，しぐ打算用这款键盘操作一个简单的文本编辑器。这个编辑器始终显示一个字符串（也可能为空）。刚启动编辑器时，字符串为空。每当按下键盘上的某个按键时，字符串会发生如下变化：

- `0` 键：在字符串的最右端插入字符 `0`。
- `1` 键：在字符串的最右端插入字符 `1`。
- 退格键：如果字符串为空，则什么也不发生；否则，删除字符串最右端的 $1$ 个字符。

しぐ启动编辑器后，按下了若干次按键。给定しぐ按下的按键序列 $s$，其中字符 `0` 表示按下 `0` 键，字符 `1` 表示按下 `1` 键，字符 `B` 表示按下退格键。请问此时编辑器屏幕上显示的字符串是什么？

## 说明/提示

## 限制

- $1 \leq |s| \leq 10$（$|s|$ 表示 $s$ 的长度）
- $s$ 仅由字符 `0`、`1`、`B` 组成。
- 输出的字符串保证非空。

## 样例解释 1

每次按键后，编辑器中的字符串依次变为 `0`、`01`、`0`、`00`。

## 样例解释 2

每次按键后，编辑器中的字符串依次变为 `0`、（空字符串）、（空字符串）、`1`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
01B0```

### 输出

```
00```

## 样例 #2

### 输入

```
0BB1```

### 输出

```
1```

# 题解

## 作者：三点水一个各 (赞：15)


## 思路

一旦找到退格键(B)，从$s_{i-1}$开始删两个字符。

### 举个栗子

01B0 从$s_{1}$(1)开始删到$s_{2}$(B)，修改后的s为 00。

于是就有了

        while(i<s.length())
	    {
   	        if(s[i]!='0'&&s[i]!='1') s.erase(i-1,2);
	  	else i++;
        }
        
于是我WA了QAQ。

### 为什么呢？

s="01BB0" ，当删掉$s_{1}$(1)和$s_{2}$(B)后i依然等于2，而此时的$s_{i}$($s_{2}$) 是0，也就是原串的$s_{4}$。

于是我们漏掉了原串的$s_{3}$(B)。

### 好吧，那我们只要i--就好了。

        while(i<s.length())
	    {
   	        if(s[i]!='0'&&s[i]!='1') s.erase(i-1,2),i--;
	  	else i++;
        }
        
### 我的天哪，还是WA？？！

B1，当i=0，$s_{0}$='B'，执行i--，然后就出现了$s_{-1}$这种东西。

如果你打开.exe文件，Dos界面出现了火星文...

### 所以我们加上特判i==0的情况
~~(感觉AC率在滴血)~~。
        
就酱A了一道蓝题
***

## 一点关于字符串的小提示

### 头文件

string/string.h/csting。

### 举个栗子

s="01B0"时，$s_{0}$='0'   $s_{1}$='1' $s_{2}$='B' $s_{3}$='0'。

### [不会用string型的读入？](https://blog.csdn.net/duan19920101/article/details/50782816)
  
### [不会用string型的删除元素？](https://blog.csdn.net/lj_2_0_2/article/details/51848875)

***

## 轻轻的献上AC代码:

    #include<bits/stdc++.h>//轻巧的头文件
    using namespace std;
    string s; 
    int i=0;//string型的第一个元素
    int main()
    {    
        getline(cin,s); //读入
        while(i<s.length())
	    {
   	        if(s[i]!='0'&&s[i]!='1') //退格符
	    	{
		     if(i>0) s.erase(i-1,2),i--;//放心删掉
		       else s.erase(i,1);//特判
		}
	  	else i++;//正常情况
        }
        cout<<s<<endl;
        return 0;//好习惯
    }
    
### 打得超辛苦，点个赞再走吧~

---

## 作者：幻之陨梦 (赞：6)

## 萌新的一篇提解(好像没有跟我一样的)
### [$\color{blue}\text{AC证据}$](https://www.luogu.org/recordnew/show/19694984)

**上AC代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],x;//x是计数器
char c;
int main(void)
{
	while(cin>>c&&c!='\0')//每次输入一个字符
	{
		if(c=='0') a[x++]=0;//如果c为'0'a数组就存下0
		else if(c=='1') a[x++]=1;//如果c为'1'a数组就存下1
		else//如果c为'B'a数组就计数器退一位
		{
			if(x) x--;
		}
	}
	if(x)
	{
		for(int i=0;i<x;i++) printf("%d",a[i]);//输出
		printf("\n"); 
	}
}
```
### [$\color{blue}\text{上一章}$](https://www.luogu.org/blog/ZhanLang/dui-you-xian-dui-lie) [$\color{blue}\text{下一章}$](https://www.luogu.org/blog/ZhanLang/dui-lie-you-hua-bellman-ford-mu-ban)

---

## 作者：lion0514 (赞：3)

# 一篇只能在noip评测机通过的题解，仅供参考，在ATCoder上不能通过

慕名而来，然后发现大部分题解都是以length为主要部分来解题的。
## 于是，我给大家分享一个好东西："\b"
\b=Insert键+←  
还是举粒子
```cpp
#include<iostream>
using namespace std;
int main(){
	cout<<"sb";
	cout<<"\b";
  	cout<<"henben";
}
```
结果：
>shenben

这样，我们就能轻松解决退格键的事了  
问：如果最后一个键是退格怎么办？
那我们就可以~~滥用自动忽略行末空格的程序解决了~~：
```
cout<<"\b"<<" "<<"\b";//把前一个字符换成空格，然后再退回去待命
```
那样我们也就不需要开字符串了，只要输一个0 or 1就放一个0 or 1

不废话，上代码——
```cpp
int main()
{
	char c;
	while(cin>>c){
		if(c=='B')
			cout<<"\b \b";
		else
			cout<<c;
	}
	cout<<endl;
}
```

附：做完题可以去看看这题的空间限制

---

## 作者：Rocket_raccoon_ (赞：1)

题意很好理解，可以说是字符串的入门题（AT混乱的评分已经司空见惯了）。    
这里主要是用C++的char数组实现字符串操作。    
如果有字符'B'将指针--，否则指针++，加入字符即可。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[6666],s2[6666];

int main(){
	int l,i,top=0;
	
	cin>>s;
	
	l=strlen(s);
	
	for (i=0; i<l; i++){
		if (s[i]=='B'){
			if (top>0) top--;//字符--，但是注意不要小于零
		}
		else {
			s2[++top]=s[i];
		}
	}
	for (i=1; i<=top; i++){
		cout<<s2[i];
	}
	
	cout<<endl; //岛国题记得换行
	
	return 0;
}
```


---

## 作者：Coding的欢乐 (赞：1)

又是一道字符串题
```cpp
#include<bits/stdc++.h>//把万能头建好
using namespace std;
string s;//定义好字符串
char a[100010];//定义好字符数组
int main()
{
	 cin>>s;//QWQ输入
	 int k=0;//再来个记录字符数组的小K
	 for(int i=0;i<s.size();i++)
	 {
	 	if(s[i]!='B') a[++k]=s[i];//一旦是B就转换
	 	else 
	     {
	     	k--;//不然就要-1
	     	if(k<0) k=0;//还有一种就是清零
	     }
	 }
	 for(int i=1;i<=k;i++)
	 	cout<<a[i];//输出
	 cout<<"\n";//别忘了回车
	 
 return 0;//完美结束
}
```


---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题十分简单，看一眼题目就知道是基本字符串的应用，~~温馨提示，实在不会erase函数的读者可以直接跳过这篇了~~讲一下思路：如果当前读入的字符不是退格键，字符串变量st2就加上当前字符，如果当前是退格符，st2删去最后一个字符，如果是空串，就不删。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    string st1,st2;//定义字符串变量
    int main()
    {
    cin>>st1;//读入
    for(int i=0; i<st1.size(); i++)
    {
        if(st1[i]!='B')st2+=st1[i];//如果不是退格符，字符串变量st2就加上当前字符
        else //如果是退格符
        {
        if(st2.size()>=1)//如果还能删就删
            st2.erase(st2.size()-1,1);
        }

    }
    cout<<st2<<endl;//输出最后结果并换行
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：向日葵小班 (赞：0)

## 我又来发起题解啦

**Because this is too water,so I 把解析放在了代码里**

## 放AC代码,17行

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string a;//定义字符串a
int b[15],q;//定义用于输出的数组b，下标q
int main()
{
	cin>>a;//输入字符串
	for(int i=0;i<a.size();i++)//循环a的长度次
	{
		if(a[i]=='0'){q++;b[q]=0;}//如果字符串a里的第i个字符==0，q++,数组b的第q个位置=0	
		if(a[i]=='1'){q++;b[q]=1;}//如果字符串a里的第i个字符==1，q++,数组b的第q个位置=1	
		if(a[i]=='B'&&q>=1)q--;	//如果字符串a里的第i个字符==B，q--
	}	 
	for(int i=1;i<=q;i++)cout<<b[i];//从1-q循环，输出b
	cout<<endl;//AT不换行,爆零两行泪！！！
    return 0;//完美结束！！！
}
```


---

## 作者：Chouquet (赞：0)

一个典型的字符栈的应用

用s表示这个栈，每次读入一个字符。遇到B时，如果栈不为空，就让前面读的字符出栈；其他字符就入栈，之后再打印栈内元素就可以了。

>附：栈的用法

>1.栈是一种后进先出的结构，能取出元素的位置在栈顶

>2.栈的各种操作：

>>- 建立栈：

>>>```cpp
>>>int stack[MAXN],top=0;//top：栈顶，一般设为0
>>>```

>>- 进栈：

>>>```cpp
>>>void push(int value){
>>>	stack[top++]=value;
>>>}
>>>```

>>- 出栈：
>>>```cpp
>>>void pop{
>>>	top--;
>>>}
>>>```

>>- 判断栈为空：
>>>```cpp
>>>bool empty{
>>>	return top==0;
>>>}
>>>```

现在就可以做了，代码如下：

```cpp
#include <cstdio>
using namespace std;
char s[105],c;int top=0;//声明字符栈
int main(){
	while((c=getchar())!='\n'){//每次读一个字符
		if(c=='B') {//是退格键
			if(top) top--;//栈不为空就出栈
		}
		else s[top++]=c;//是字符就入栈
	}
	for(int i=0;i<top;i++) printf("%c",s[i]);//输出栈里的元素
        putchar('\n');//别忘了加换行
	return 0;
}
```

---

## 作者：Heap_Sort (赞：0)

Pascal蒟蒻来发一篇题解。

入门者学习多种算法的一道好题。首先介绍纯模拟：如果读入的是1和0（即非B），就加到字符串末尾。如果读入的是B，就要用到删除函数delete。

函数的格式是delete（string，integer1，integer2）；string表示需要进行删除的字符串，integer1表示从哪个位置开始删除，integer2表示删除多长（注意:要包括开头的那一位）

举个栗子

字符串s=‘11001’，现在需要删除2，3，4三位。先找到起始位置，为2。删除长度为4-2+1=3。则使用delete（s，2，3）；

代码
```pascal
var
  c:char;
  s:string;
begin
  while not eof{文件结尾，在不知道要读多长时使用，可以一直读到末尾} do
   begin
    read(c);
    if c<>'B' then s:=s+c;
    if(c='B')and(length(s)<>0)then //保证字符串非空
     delete(s,length(s),1);
   end;
  writeln(s);
end.
```

接下来介绍一种数据结构，[栈](https://baike.sogou.com/v67743459.htm?fromTitle=%E6%A0%88)。即插入和删除都在同一端进行。需要用一个数字记录有几个元素在栈里，即栈顶位置。

贴代码
```
var a:array[1..1000] of char;
  c:char;
  i,j:longint;
begin
  while not eof do
   begin
    read(c);
    if c<>'B' then begin inc(i);a[i]:=c;end;
    if(c='B')and(i<>0)then 
     begin a[i]:='';dec(i);end;
   end;
  for j:=1 to i do write(a[j]);
end.
```

本篇题解就到这里，谢谢大家！！

---

## 作者：rui_er (赞：0)

# C++党题解

~~P党请右转下楼，那里才是你们的基地~~

输入是从后面添加，退格是从后面删除。这个feature好像与什么相似……是什么呢？

懂了的[点我](https://www.luogu.org/problemnew/show/AT2018)

------------

好吧，没想到你还没懂。这就是个栈！FILO！

具体操作：

1. 对于数字键，push对应的数字

2. 对于退格键，如果文档非空则pop，否则什么都不做。

但是最后的文本是倒着的，怎么办呢？pop进另一个栈！这样就可以正过来了！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string oper;
    cin>>oper;
    int l = oper.length();
    stack<char> text, tmp;
    for(int i=0;i<l;i++)
    {
        if(oper[i] != 'B') text.push(oper[i]);
        else
        {
            if(!text.empty()) text.pop();
        }
    }
    while(!text.empty())
    {
        tmp.push(text.top());
        text.pop();
    }
    while(!tmp.empty())
    {
        cout<<tmp.top();
        tmp.pop();
    }
    return 0;
}
```

---

## 作者：百里亦守约 (赞：0)

# ~~我又来写题解了。~~

这道题的大意是：
## 0号键：一个文字0将被插入到字符串的右边。

## 1号键：一个文字1将被插入到字符串的右边。

## 退格键：如果字符串是空的，什么都不会发生。否则字符串最右边的文字将被删除。

所以根据题意和所学知识可以用字符串的一个函数：

#### 当前字符串.erase(需要删除的字符串的起点，删除字符的个数)（从左到右）

然后根据这个知识，就可以写出代码了。

代码如下：
```cpp
#include<bits/stdc++.h> //万能头
using namespace std;
string st,xst;
int main()
{
    cin>>st; //输入一个字符串
    for(int i=0;i<st.size();i++)
        if(st[i]=='0' || st[i]=='1') xst+=st[i]; //如果是0或1的话，那么按照平时打字的顺序将他们移到字符串的右边。
        else
            if(xst.size()>0) //如果当字符串有不是空串的情况并且是刚好输入删除符的话，那么就用这个函数编就可以了。
            xst.erase(xst.size()-1,1);
    cout<<xst<<endl; //输出记得换行。
    return 0; //结束
}
```



---

## 作者：TRZ_2007 (赞：0)

##  首先弱弱地问一个问题：~~这题真的是黄题吗~~

### 首先看到这道题目，心里第一个反应就是模拟，但是，如果用我们的$if$语句的话，就很难体现出我的~~蒟蒻~~，于是，就作死的用了$switch$。

```
#include <stdio.h>//大佬勿喷，C党强迫症
#include <string.h>
int main()
{
	char str[101],answer[101];//刚开始的时候的输入存在str数组里，输出存在answer数组里。
	gets(str);//输入我们的str数组
	int lens=strlen(str),i,lena=0;//lena是answer数组的长度，目前一个字符都没插，长度为0
	for(i=0;i<lens;i++)
		switch(str[i])
		{
			case '0':answer[lena]='0';lena++;break;//是0的情况，在空串的右边插入0
			case '1':answer[lena]='1';lena++;break;//同样
			case 'B':if(lena!=0) lena--;break;//是退格键的时候，先判断现在是不是空串，如果不是，就退一格
		}
	for(i=0;i<lena;i++)
		printf("%c",answer[i]);//输出
	printf("\n");//注意换行
}//完美收场23333（防伪标记）
```

---

## 作者：PC_DOS (赞：0)

一道适合初学者练习字符串操作的模拟题，在C++的<string>头文件中，提供了名为string的类来进行字符串操作，虽然比起char[]和char*，string类在性能上有所损失，但是很好地规避了定长字符串带来的风险，同时通过内部封装的动态内存分配避免了手写造成的潜在的内存泄露。
  
string类同时封装了大量的函数(包括重载的运算符)供用户调用。

关于题目中退格功能的实现的问题:

转义字符'\b'对应着退格，在某些实现(例如笔者使用的Visual C++ 2013，系统Windows 10 LTSB2016 x64)中，通过直接向字符串附加'\b'字符即可实现退格，但是测试表明在洛谷及ATCoder使用的评测环境下，该功能将导致输出的答案错误。

在string类中，提供了substr()函数，该函数可以从字符串指定位置开始提取指定长度的字符串，故此处使用该函数。

代码:

```cpp
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sResult(""), sOpr; //分别定义结果sResult和操作sOpr
	int i; //循环计数器
	getline(cin, sOpr); //读入操作
	for (i = 0; i < sOpr.length(); ++i){ //枚举每一个操作
		if (sOpr[i] == '0' || sOpr[i] == '1') //如果是输入操作
			sResult += sOpr[i]; //附加文字
		else if (sOpr[i] == 'B') //如果是退格
			if (sResult.length() != 0) //判断是否能退格
				sResult = sResult.substr(0, sResult.length() - 1); //若能，则退格，使用substr()函数，第一个参数表示开始位置，第二个表示提取长度
	}
	cout << sResult << endl; //输出答案
	return 0; //结束
}
```

---

## 作者：打表大蒟蒻 (赞：0)

这道题其实很多人都写的过于复杂了，我来补充一个简单算法(C++)

string类型中有许多特性，string类型可以用+运算符（重载的）在字符串尾进行添加操作，正好符合题目要求的1，2两种操作，对于第三种操作，即在字符串尾进行删除，可以用erase函数删除。erase函数使用模板如下：

s.erase(起始位置,终止位置);  如果在尾部删除，终止位置可以不用写。

当然添加也可以用自带函数来操作：s.insert(起始位置,终止位置);  
核心部分讲完了，下面贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main ()
{
    string s="", ss;  //字符串清空
    cin>>ss;  //读入操作序列
    for(int i=0;i<ss.size();i++){ 
    	if(ss[i]=='0') s+='0';  //添加操作
    	else if(ss[i]=='1') s+='1';  //添加操作
    	else{
    		int len=s.size();  //把串长存进len里
			if(len>0) s.erase(len-1); //删除操作
		}
	}
	cout<<s<<endl;  //输出
    return 0;
}
```


---

