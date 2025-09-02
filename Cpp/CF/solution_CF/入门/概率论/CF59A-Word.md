# Word

## 题目描述

Vasya is very upset that many people on the Net mix uppercase and lowercase letters in one word. That's why he decided to invent an extension for his favorite browser that would change the letters' register in every word so that it either only consisted of lowercase letters or, vice versa, only of uppercase ones. At that as little as possible letters should be changed in the word. For example, the word HoUse must be replaced with house, and the word ViP — with VIP. If a word contains an equal number of uppercase and lowercase letters, you should replace all the letters with lowercase ones. For example, maTRIx should be replaced by matrix. Your task is to use the given method on one given word.

## 样例 #1

### 输入

```
HoUse
```

### 输出

```
house
```

## 样例 #2

### 输入

```
ViP
```

### 输出

```
VIP
```

## 样例 #3

### 输入

```
maTRIx
```

### 输出

```
matrix
```

# 题解

## 作者：char32_t (赞：8)

# 题解 CF59A 【Word】

------------

看到之前的几篇题解都是使用`ASCII`进行大小写字母的判断及变换的，其实也可以用**字符测试函数**、**字符转换函数**完成大小写字母的判断及变换。（需要包含头文件`<ctype.h>`）


### 字符测试函数


- isupper() 判断是否是大写英文字母

- islower() 判断是否是小写英文字母

### 字符转换函数


- tolower() 大写字母转小写

- toupper() 小写字母转大写

Code：

```cpp
#include<cstdio>
#include<cstring>
#include<ctype.h>//字符测试函数、字符转换函数头文件 
char ch[110];//字符数组 
int count_up=0, count_lo=0;//count_up->大写字母数  count_lo->小写字母数 
int main() {
    scanf("%s", ch);//输入字符串 
    int len=strlen(ch);//测出字符串长度 
    for(int i=0; i<len; i++) {//扫描字符串 
        if(isupper(ch[i])) count_up++;//计算大写字母数 
        if(islower(ch[i])) count_lo++;//计算小写字母数 
    }
    if(count_up>count_lo) {//如果大写字母多于小写字母 
        for(int i=0; i<len; i++)
            if(islower(ch[i])) ch[i]=toupper(ch[i]);//将小写字母转为大写字母 
    } else if(count_up<=count_lo)//如果大写字母少于或等于小写字母 
        for(int i=0; i<len; i++)
            if(isupper(ch[i])) ch[i]=tolower(ch[i]);//将大写字母转为小写字母 
    for(int i=0; i<len; i++) printf("%c", ch[i]);//输出 
    return 0;
}
```

---

## 作者：lsyx0918 (赞：2)

这道题就是考察字符之间的的规律，哪怕是蒟蒻都知道，数字之间只要减48在转换成int类型就可以得到0~9了，同样大家也会发现大小写字母之间的差距为32，且大写的ASCII码比小写的ASCII码要小。那么，这道题就破解了，只要会字符串，一切都OK！

现在开始上代码（两份代码，一份为string，一份为char）：
```cpp
#include<iostream>
#include<cstring>
//也可以用万能头
using namespace std;
string a;//定义全局变量
int main()
{
	getline(cin,a);
	int ANS=0,ans=0;//定义变量	
	for(int i=0;i<a.size();i++)
	{
		if(a[i]>='A'&&a[i]<='Z') ANS++;
		if(a[i]>='a'&&a[i]<='z') ans++;
	}
	//对大小写个数进行判断 
	for(int i=0;i<a.size();i++)
	{
		if(ANS<ans||ANS==ans) if(a[i]>='A'&&a[i]<='Z') a[i]+=char(32);
		if(ANS>ans) if(a[i]>='a'&&a[i]<='z') a[i]-=char(32);//这里我用else是答案是不对的
	}
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i];//输出
	}
	return 0;
} 
```
```cpp
#include<iostream>
//也可以用万能头，但是根本没有那个必要
using namespace std;
char a[10000000];//定义全局数组
int main()
{
	gets(a);
	int ANS=0,ans=0;//定义变量	
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]>='A'&&a[i]<='Z') ANS++;
		if(a[i]>='a'&&a[i]<='z') ans++;
	}
	//对大小写个数进行判断 
	for(int i=0;i<strlen(a);i++)
	{
		if(ANS<ans||ANS==ans) if(a[i]>='A'&&a[i]<='Z') a[i]+=char(32);
		if(ANS>ans) if(a[i]>='a'&&a[i]<='z') a[i]-=char(32);//这里我用else是答案是不对的
	}
	for(int i=0;i<strlen(a);i++)
	{
		cout<<a[i];//输出
	}
	return 0;
} 
```
OK，大功告成

---

## 作者：康娜卡姆依 (赞：2)

其实pascal有很多有趣的函数例如小写转大写（大写仍不变）是upcase,反之是lowercase。这样比ASCII转来转去繁琐的步骤好多了。

话不多说，上代码。
```pascal
var s:string;
    i,sum:longint;
begin
  readln(s);
  for i:=1 to length(s) do
  if (s[i]>='A')and(s[i]<='Z') then inc(sum);//记录大写个数
  if sum<=length(s) div 2 then write(lowercase(s))//判断+转化一体成型。
  else write(upcase(s));
end.
  
```


---

## 作者：FP·荷兰猪 (赞：1)

题意：给定一个字符串要求改变最少的字符使这个字符串中只有大写字母或小写字母，如果大写字符与小写字符个数一样，就全变为小写字符。

这题的题面很简单，解法也很简单，直接模拟即可。首先在读入字符串的同时计算出小写字母和大写字母分别有多少个，如果大写字母多就把所有字符转化成大写后输出；否则把所有字符转化成小写后输出。

代码详解：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
    cin>>s;
    int x,d,i;//x表示字符串s中小写字母的个数；d表示大写字母的个数
    x=d=0;
    for(i=0;i<s.size();i++)
    {
        if (s[i]>='a' && s[i]<='z')//如果该字符是小写字母，x++
        {
        	x++;
        }
        else//如果该字符是大写字母，d++
        {
        	d++;
        }
    }
    if(x>=d)//注意大写字母和小写字母个数相同时应当转化成小写字母输出
    {
        for(i=0;i<s.size();i++)
        {
            if(s[i]>='a' && s[i]<='z')
			{
				cout<<s[i];
			}
            else
			{
				printf("%c",s[i]+32);//用cout会很烦，这里直接用printf输出char
			}
        }
    }
	else
	{
        for(i=0;i<s.size();i++)
        {
            if(s[i]>='A' && s[i]<='Z')
			{
				cout<<s[i];
			}
            else
			{
				printf("%c",s[i]-32);
			}
		}
    }
    return 0;
}
```

---

## 作者：longyuxuan (赞：1)

思路：读入字符串后把大小写的字符数统计出来，~~虽然说这是这题的难点，但我还是认为这很简单~~，然后根据题目要求转化大小写

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int d=0,x=0,len; 
int main()
{
	cin>>s;len=s.size();
	for(int i=0;i<len;i++)//统计大小写个数
	  if(s[i]>='A'&&s[i]<='Z')  d++;
	  else x++;
	if(d<=x)//如果大写字符比小写字符少或跟小写字符一样多，就把字符串转为小写
	  for(int i=0;i<len;i++)
	    cout<<(char)/*如果使用三目运算符一定要加上这个东西，否则会输出一堆数字*/((s[i]>='a'&&s[i]<='z')?s[i]:s[i]+32);
	else
	  for(int i=0;i<len;i++)
	    cout<<(char)/*同上*/((s[i]>='A'&&s[i]<='Z')?s[i]:s[i]-32); 
	return 0; 
}
```
这题还有一个地方需要注意，将大写字符转化为小写字符是将ascll码加上32，不是减去32

---

## 作者：Siyuan (赞：1)

非常简单的一道模拟！


本题思路：


1. 以字符串形式读入，并求出字符串的长度。


2. 搜一遍字符串，统计大写和小写字母的数量。


3. 如果小写字母数量>=大写字母，那么转换成小写并输出；否则转换成大写。


上代码！（很多部分都是相同的）


```cpp
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;
string a;
int len,s1,s2;     //s1表示小写字母数量，s2表示大写字母数量
int main()
{
    cin>>a;
    len=a.size();
    for(register int i=0;i<len;i++)
        (a[i]>='a'&&a[i]<='z')?(s1++):(s2++);     //珂怕的三目运算符……
    //注意：  'A'=65     'a'=97
    if(s1>=s2)     //如果大写数量少
    {
        for(register int i=0;i<len;i++)     //转小写
            if(a[i]>='a'&&a[i]<='z')  printf("%c",a[i]);
            else  printf("%c",a[i]+32);
    }else{
        for(register int i=0;i<len;i++)     //转大写
            if(a[i]>='A'&&a[i]<='Z')  printf("%c",a[i]);
            else  printf("%c",a[i]-32);
    }
    return 0;
}
```

---

## 作者：向日葵小班 (赞：1)

**这题巨水，求出这个字符串大写字符和小写字符的数量，判断一下哪个数量多，若大写多将小写转大写，否则将大写转小写。**

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string a;//定义字符串
int dx,xx;//定义统计大小写数量变量
int main()
{
	cin>>a;//输入字符串a
	for(int i=0;i<a.size();i++)//从0循环到a的长度次
	{
		if(a[i]>='A'&&a[i]<='Z')dx++;//如果a里第i个字符为大写，dx++
		if(a[i]>='a'&&a[i]<='z')xx++;//如果a里第i个字符为小写，xx++
	}
	if(dx>xx)//如果大写数量大于小写数量
	{
		for(int i=0;i<a.size();i++)//从0循环到a的长度次
		{
			if(a[i]>='a'&&a[i]<='z')a[i]-=32;//如果a里第i个字符为小写，则-32，变成大写
		}
	}
	if(xx>=dx)//如果小写数量大于等于大写数量
	{
		for(int i=0;i<a.size();i++)//从0循环到a的长度次
		{
			if(a[i]>='A'&&a[i]<='Z')a[i]+=32;//如果a里第i个字符为大写，则+32，变成小写
		}
	}
	cout<<a;//输出a
    return 0;//完美结束
}


```


---

## 作者：Sophon (赞：0)

翻了一下好像没有STL transform的，水一波
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long lowCnt=0,upCnt=0;//大小写字母计数器
	
	string str;
	cin>>str;
	
	for(string::size_type i=0;i<str.size();i++)//size_type消除warning
	{
		if(islower(str[i]))//判断大小写<cctype>或std::
		{
			lowCnt++;
		}
		else
		{
			upCnt++;
		}
	}
	
	if(upCnt<=lowCnt)
	{
		transform(str.begin(),str.end(),str.begin(),::tolower);//转小写
	}
	else
	{
		transform(str.begin(),str.end(),str.begin(),::toupper);//转大写
	}
	
	cout<<str<<endl;
}
```

---

## 作者：不到前10不改名 (赞：0)

//对于一个c党来说，每次看到这种转换题，就很头疼（没有cctype的那些函数），和某些stl一遍过的题一样...唉~QAQ   
//于是ASCII码值要记牢，例如今年pj第一题...
```
#include<stdio.h>
#include<string.h>
int n,i,sry;
char srx[1001];
int main()
{
    gets(srx);
    n=strlen(srx);
    for(i=0;i<n;i++)
    if(srx[i]>=65&&srx[i]<=90)//统计大写字母
    sry++;
    if(sry>n/2)//根本不用再算小写字母，字符串里减去大写就是小写，不超过一半就是转换小写方便
    {for(i=0;i<n;i++)
    if(srx[i]>=97&&srx[i]<=122)//数学太差，算ASCII码时少进了一位，第十三个点搞死过不去233...（不过这也能过12个点...）
    srx[i]-=32;}//利用ASCII码的值来转换
    else
    {for(i=0;i<n;i++)
    if(srx[i]>=65&&srx[i]<=90)//常用ASCII码值应该背掉（0是48,9是58）
    srx[i]+=32;}
    puts(srx);
    return 0;
}
```

---

## 作者：Teddy·Bear (赞：0)

看了这么多用string函数做的方法，我决定用最正规（~~最麻烦~~）的方法做！！！贴代码
```
#include<bits/stdc++.h>
using namespace std; 
int man()
{int sum1=0,sum2=0;//记录大写和小写字母个数
char a[10005];//a字符数组
gets(a);//读入
for(int i=0;i<strlen(a);i++)//记录大写和小写字母个数
{if(a[i]>='A'&&a[i]<='Z')
sum1++;
else
sum2++; 
} 
if(sum1>sum2)//当大写字母多于小写字母时
{for(int i=0;i<strlen(a);i++)//小写转大写
{if(a[i]>='a'&&a[i]<='z')
a[i]-=32;
}
}
else
{for(int i=0;i<strlen(a);i++)//如果二者相同或小写多时，大写转小写
{if(a[i]>='A'&&a[i]<='Z')
a[i]+=32;
}
}
puts(a);输出
cout<<endl;回车勿忘
return 0;
}
```

---

## 作者：灵小沙 (赞：0)

	#include<bits/stdc++.h>
	#include<string>
	#include<iostream>
	#include<cmath>
	#include<set>
	#include<stack>
	#include<queue>
	using namespace std;

	int main()
	{
		int x=0/*小写字母*/,d=0/*大写字母*/,i;
		string st;//一个字符串 
		cin>>st; 
		for(i=0;i<st.size()/*size()(长度)*/;i++)
		{
			if(st[i]>='a'&&st[i]<='z') x++;//判断小写  
			else if(st[i]>='A'&&st[i]<='Z') d++;//判断大写 
		
		}
		if(x>=d) //小大于大 （注意是>=） 
		{
			for(i=0;i<st.size();i++) 
			{
				if(st[i]>='a'&&st[i]<='z') st[i]+=32;//大写转小写 
			}
		}
		else //大大于小 
		{
			for(i=0;i<st.size();i++)
			{
				if(st[i]>='a'&&st[i]<='z') st[i]-=32;//小写转大写 
			}
		} 
		for(i=0;i<st.size();i++) cout<<st[i];//输出 
		return 0;
	}//~~~ 


---

## 作者：罗贤泽 (赞：0)

首先统计一下大小写字母的数量，然后比较一下，最后用一下tolower和toupper函数就行了


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int capital_letter=0,small_letter=0;//第一个变量是为了计算大写字母的数量，第二个则是为了计算小写字母的数量
    for(int i=0;i<s.size();i++)
    {
        if(islower(s[i]))//判断该字符是否为小写 
        {
            small_letter++;
        }
        if(isupper(s[i]))//判断该字符是否为大写 
        {
            capital_letter++;
        }   
    }
    for(int i=0;i<s.size();i++)
    {
        if(small_letter<capital_letter)//如果小写字母比大写字母少，就全变成大写字母
        {
            s[i]=toupper(s[i]);
        }   
        else//与上面的原因相同 
        {
            s[i]=tolower(s[i]);
        }
    }
    cout<<s;
    return 0;
}
```

---

