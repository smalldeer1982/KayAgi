# String Task

## 题目描述

Petya 开始参加编程课程。在第一节课上，他的任务是编写一个简单的程序。该程序需要对给定的仅由大写和小写拉丁字母组成的字符串进行如下处理：

- 删除所有元音字母；
- 在每个辅音字母前插入一个字符“.”；
- 将所有大写辅音字母转换为对应的小写字母。

元音字母包括 “A”、“O”、“Y”、“E”、“U”、“I”，其余字母均为辅音。程序的输入为一个字符串，输出为经过上述处理后的字符串。

请帮助 Petya 完成这个简单的任务。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
tour
```

### 输出

```
.t.r
```

## 样例 #2

### 输入

```
Codeforces
```

### 输出

```
.c.d.f.r.c.s
```

## 样例 #3

### 输入

```
aBAcAba
```

### 输出

```
.b.c.b
```

# 题解

## 作者：蕙兰居士 (赞：13)

###### ~~水题一道~~
##### 本题模拟即可，大佬勿喷
# 主思路：先将大写字母转换为小写字母，再进行主判断（是否为辅音），元音略过
#### 上AC代码（附注释）——
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
string a;//定义一个字符串
int main(){
    cin>>a;//输入，不用说了吧
    int la=a.length();//为了方便
    for(int i=0;i<la;i++){//字符一律从0开始
        if(a[i]>='A'&&a[i]<='Z')
        	a[i]+=32;//大写字母转小写字母
        if(a[i]!='a'&&a[i]!='o'&&a[i]!='y'&&a[i]!='e'&&a[i]!='u'&&a[i]!='i')//暴力判断
        	cout<<"."<<a[i];//是辅音前面就输出“.”，然后是字符a[i]
    }
    return 0;//好习惯
}
```
//这是本蒟蒻第二篇题解，讲解的可能不够好，希望大家能给我指出不足之处，谢谢！
##### 杜绝抄袭，人人有责！

---

## 作者：T_F_P (赞：4)

~~水题~~

不明白大佬们为何如此~~繁琐~~……

 ~~我是蒟蒻~~

这道题的思路是这样的：先转小写（为了方便），再转换

下面是思路解析（我的题解基本都这样）

 输入（chenzhe大佬别打我……）：

```cpp
scanf("%s",aya);
```

转小写：

```cpp
	for(int i=0;i<strlen(aya);i++){
		if(aya[i]<='Z'){
			aya[i]+=('a'-'A');
		}
	}
```

判断+输出：

```cpp
	for(int i=0;i<strlen(aya);i++){
		if(aya[i]=='a'||aya[i]=='o'||aya[i]=='y'||aya[i]=='e'||aya[i]=='u'||aya[i]=='i'){
			//什么也不做 ，只是为了判断 
		}else{
			printf(".%c",aya[i]);
		} 
	}
```

下面附上有注释的代码：

```
#include <bits/stdc++.h>
using namespace std;
char aya[200000];//CZ大佬别打！！！ 
int main(){
	scanf("%s",aya);//输入 
	for(int i=0;i<strlen(aya);i++){
		if(aya[i]<='Z'){
			aya[i]+=('a'-'A');
		}
	}//换小写 
	for(int i=0;i<strlen(aya);i++){
		if(aya[i]=='a'||aya[i]=='o'||aya[i]=='y'||aya[i]=='e'||aya[i]=='u'||aya[i]=='i'){
			//什么也不做 ，只是为了判断 
		}else{
			printf(".%c",aya[i]);//愉快的输出 
		} 
	}
	return 0;//as usual
}
```

~~本蒟蒻的第五篇题解~~

#如果觉得有帮助，请点赞^&^（~~感觉有点不要脸~~）

---

## 作者：Vsh_fd (赞：2)

这是本蒟蒻第一次发布题解（除了这种题我好像也发不了别的）

作为时任CF题库难度筛选排名第一的题目，竟没有一篇体面的题解咳咳

看到这道题，我的第一反应竟然是队列，，，然后马上就否决掉了（直接枚举判断就解决了呀）

一共两种判断，是否元音，是否小写
### 来源
Luogu CF118A

## 代码

```cpp
#include<iostream>
#include<cstdio>//竟然又忘掉了这个库导致编译错误
#include<string>
using namespace std;
string a;
int la;
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);

	cin>>a;
	la=a.length();
	for(int i=0;i<=la-1;++i)
		if(a[i]!='a' and a[i]!='o' and a[i]!='y' and a[i]!='e' and a[i]!='u' and a[i]!='i' and a[i]!='A' and a[i]!='O' and a[i]!='Y' and a[i]!='E' and a[i]!='U' and a[i]!='I'){//暴力判断元音
			printf(".");//无论是大写小写都要输出的吧
			if(a[i]>='a' and a[i]<='z')
				printf("%c",a[i]);
			else
				printf("%c",a[i]-('A'-'a'));//大写变小写(emm)
		}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

---

## 作者：秋本馄淡 (赞：1)

这道题可以看成一道模拟题，可以以字符或字符串的形式解题。

这是字符串：
```pascal
var
  c:char;s:string;i:longint;
begin
  readln(s);
  for i:=1 to length(s) do
  begin
    if s[i] in['A'..'Z','a'..'z'] then
    begin
      if not (s[i] in['A','E','I','O','U','Y','a','e','i','o','u','y']) then
      write('.',lowercase(s[i]));
    end else if not (s[i] in['a'..'z'])
              then write(s[i]);
  end;
  writeln;
end.         
```

这是字符的：
```pascal
var
  c:char;
begin
  while not eoln do
  begin
    read(c);
    if c in['A'..'Z','a'..'z'] then
    begin
      if not (c in['A','E','I','O','U','Y','a','e','i','o','u','y']) then
      write('.',lowercase(c));
    end else if not (c in['a'..'z'])
              then write(c);
  end;
  writeln;
end.
```

---

## 作者：xyn0901 (赞：1)

这么多题解竟然没有Pascal的，

那我就来一发

算法：直接模拟，遇到元音跳过
```pascal
var s:ansistring;
i,l,j:longint;
begin
read(s);
s:=lowercase(s);
l:=length(s);
for i:=1 to l do
if (s[i]<>'a')and(s[i]<>'e')and
(s[i]<>'i')and(s[i]<>'o')and
(s[i]<>'u')and(s[i]<>'y')
then write('.',s[i]);
end.
```

---

## 作者：肖泽源 (赞：0)

此题很水，我们只需要判断字母是不是a，e，y，i，o，u。
不过在这之前，要将它全部转换为小写
```
#include<bits/stdc++.h>
using namespace std;
bool xp(char c)//判断是否为元音
{
	if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y')return true;
	return false;
}
char a[110];
int main()
{
	scanf("%s",&a);//输入
	int len=strlen(a);
	for(int i=0;i<len;i++)
		if(a[i]>=65&&a[i]<=90)a[i]+=32;//转化为小写
	for(int i=0;i<len;i++)
		if(!xp(a[i]))printf(".%c",a[i]);//如果不是元音，就输出"."和字母
	return 0;
}
```

---

## 作者：Core (赞：0)

看各位大佬都没用erase，我就来写一个吧。

思路见原题，绝对模拟。（详见代码）

Code：

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    string str;     //字符串
    string::iterator it;      //迭代器
    cin>>str;       //输入
    for(int i=0;i<str.length();i++)
    {
       //如果为元音字母
       if(str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U'||str[i]=='Y'||str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='y')
        {
            it=str.begin()+i;    //it保存当前位置
            str.erase(it);      //删除
            i--;       //为防止删过后i++会跳过下一字母
        }
    }
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>='A'&&str[i]<='Z') cout<<"."<<char(str[i]+32);      //大写转小写
        else cout<<"."<<str[i];
    }
    cout<<endl;    //换行
    return 0;     //结束程序
}
```

---

## 作者：myfly (赞：0)

任何字母（无论大小写）都可以通过**ch|=32**转化成其小写形式。（小写不变，大写转小写）

所以可以做如下简化：
```cpp
//CF118A String Task
# include <iostream>
# include <cstring>
# define L 105
using namespace std;
char str[L];
int main() {
    cin>>str;
    for (int i=0; i<strlen(str); i++) {
        str[i]|=32;
        if (str[i]=='o' || str[i]=='a' || str[i]=='e' 
            || str[i]=='y' || str[i]=='u' || str[i]=='i')
            continue;
        else cout<<'.'<<str[i];
    }
    return 0;
}
```

---

## 作者：loi_hjh (赞：0)

# 话说我这种方法有点不太道德（伪打表）

请忽略奇奇怪怪用来好看的头文件

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char a[10001];//模拟字符串 
int main(){
	scanf("%s",a+1);
	int l=strlen(a+1);//求长度来枚举 
	for(int i=1;i<=l;i++){
		if((a[i]=='A')||(a[i]=='E')||(a[i]=='I')||(a[i]=='O')||(a[i]=='U')||(a[i]=='Y')||(a[i]=='a')||(a[i]=='e')||(a[i]=='i')||(a[i]=='o')||(a[i]=='u')||(a[i]=='y')) printf("%c",a[i]);
		else printf(".");//是元音字母就输出，否则输出. 
	}
	return ~~(0-0);
}


```

---

## 作者：OdtreePrince (赞：0)

# -字符串-

用ch数组进行预处理，在循环中加个判断，就这么简单。

其实ch预处理可以不要，只可惜蒟蒻用不来ASCLL码

SHENBEN DALAO 勿喷  >-<

~~~
#include<bits/stdc++.h>
using namespace std;
char ch[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};//预处理
int main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]!='A'&&s[i]!='E'&&s[i]!='I'&&s[i]!='O'&&s[i]!='U'&&s[i]!='Y'&&s[i]!='a'&&s[i]!='e'&&s[i]!='i'&&s[i]!='o'&&s[i]!='u'&&s[i]!='y'){
            cout<<'.';
            if(s[i]<='Z') cout<<ch[s[i]-'A'];
            else cout<<s[i];
        }
    }
    return 0;
}~~~

---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，我们只需要依照题意，首先将整个串转为小写，之后遍历字符串，遇到元音字母则跳过，否则输出点号和对应字符即可。

唯一需要注意的是，在这里元音字母是A、E、I、O、U、Y。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
inline bool IsVowel(char chrTest){ //判断一个字符是不是元音字母的函数
    return (chrTest == 'A' || chrTest == 'E' || chrTest == 'I' || chrTest == 'O' || chrTest == 'U' || chrTest == 'Y' || chrTest == 'a' || chrTest == 'e' || chrTest == 'i' || chrTest == 'o' || chrTest == 'u' || chrTest == 'y');
}
string ToLower(string sOrigin){ //字符串转为小写的函数
    string ans("");
    if (sOrigin.length() == 0){
        return ans;
    }
    long long i;
    for (i = 0; i <= sOrigin.length() - 1; ++i){
        if (sOrigin[i] >= 'A' && sOrigin[i] <= 'Z')
            ans += char(sOrigin[i] + ('a' - 'A'));
        else
            ans += sOrigin[i];
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    string sInput; //输入的字符串
    register int i; //循环计数器
    getline(cin, sInput); //读入串
    sInput = ToLower(sInput); //转为小写
    for (i = 0; i < sInput.length(); ++i){ //遍历字符串
        if (!IsVowel(sInput[i])) //如果读到非元音字母
            cout << '.' << sInput[i]; //输出点号和对应字母
    }
    return 0; //结束
}
```

---

