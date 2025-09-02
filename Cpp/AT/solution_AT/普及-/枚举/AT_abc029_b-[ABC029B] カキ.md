# [ABC029B] カキ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc029/tasks/abc029_b

英小文字からなる $ 12 $ 個の文字列 $ S_1 $, $ S_2 $, ..., $ S_{12} $ が入力されます。  
これらの文字列のうち、文字 `r` が含まれるものの個数を数えてください。

## 说明/提示

### Sample Explanation 1

$ S_1 $, $ S_2 $, $ S_3 $, $ S_4 $, $ S_9 $, $ S_{10} $, $ S_{11} $, $ S_{12} $ の $ 8 $ 個の文字列に文字 `r` が含まれています。 $ S_2 $ には `r` が $ 2 $ 回出現していますが、一度しか数えません。

## 样例 #1

### 输入

```
january
february
march
april
may
june
july
august
september
october
november
december```

### 输出

```
8```

## 样例 #2

### 输入

```
rrrrrrrrrr
srrrrrrrrr
rsr
ssr
rrs
srsrrrrrr
rssrrrrrr
sss
rrr
srr
rsrrrrrrrr
ssrrrrrrrr```

### 输出

```
11```

# 题解

## 作者：hjxxcbq (赞：3)

### 没想到，这道题是普及难度，我本人认为，这道只是入门难度。（~~提交2次才AC~~）

只用**find()函数**就搞定了。

**让我来补充补充find()函数吧：find()就是查找，如一个字符串.find('r')意思是在那一个字符串找r，查找成功，返回按查找规则找到的第一个字符或子串的位置；若查找失败，返回npos，即-1。**

所以这道题很简单。

代码如下：
```
#include<bits/stdc++.h>/万能头文件
using namespace std;//使用标准命名空间
string a;//一个字符串
int s;//专门累加的
int main()//可以直接main()，不用int 。
{
for(int i=0;i<12;i++)//有12个单词，所以循环到12。
{
cin>>a;//输入这个字符串
if(a.find('r')!=-1)s++;//a.find('r')不是-1，s加1
}
cout<<s;//输出s
return 0;//注意要return 0;
}
```

噢！是错的！

![](https://i.loli.net/2019/05/28/5ceceab88c9e478140.png)

想了一下，原来是AT题，要换行！

AC代码如下：
```
#include<bits/stdc++.h>/万能头文件
using namespace std;//使用标准命名空间
string a;//一个字符串
int s;//专门累加的
int main()//可以直接main()，不用int 。
{
for(int i=0;i<12;i++)//有12个单词，所以循环到12。
{
cin>>a;//输入这个字符串
if(a.find('r')!=-1)s++;//a.find('r')不是-1，s加1
}
cout<<s;//输出s，注意要换行！
return 0;//注意要return 0;
}
```

![](https://i.loli.net/2019/05/28/5ceceb347bca939129.png)

一堆AC，真爽呀！

**题解有问题，可以私信我。**

---

## 作者：happybob (赞：1)

看见大家用的都是 `find` 函数，枚举等 `string` 基本操作，这里发一个正则表达式的做法。

首先，我们要了解一下正则表达式在 `c++` 中的定义以及其使用方法：

正则表达式是标准 `c++11` 中的一种常用与匹配两个字符串之间的数据结构，需要包含头文件 `<regex>`，然后就可以声明某个正则表达式：


```cpp
regex name(^value$); // 其中^与$均可省略，^代表开始，$代表结束

如：
regex reg("^abc+$");
```




那么我们刚才定义的 `abc+` 是什么意思呢？这要涉及到正则表达式的符号，这里介绍几种常用的：

# 1、+号

+号可以匹配其前面那个字符若干次（$\geqslant 1 \text{次}$）,如 `sjk+ ` 就可以与 `sjk`、`sjkk`、`sjkkk` 等匹配。如果加号前面出现括号，则可以匹配括号中的内容若干次（$\geqslant 1 \text{次} $）。

# 2、*号

*号可以匹配其前面那个字符若干次（$\geqslant 0\text{次}$），与+号不同的就在于0次也可以匹配。

# 3、[a-z]

代表所有小写字母。

# 4、[A-Z]

代表所有大写字母。

# 5、[0-9]

代表所有阿拉伯数字。

# 6、?号

?号代表其前面的字符可出现也可以不出现，若前面有括号，则代表括号内内容可出现也可以不出现，如 `(ak)?ioi` 可以与 `ioi` 和 `akioi` 成功匹配。

那么知道了定义方式和其基础符号，我们还要学习基本匹配函数 `regex_match`，这个函数可以有两或三个参数，常为两个参数，第一个参数是待匹配的字符串，第二个是一个正则表达式，返回值为布尔类型，如匹配成功返回 `true`，匹配失败返回 `false`。

学习完这些，这道题目不是迎刃而解了？

代码：


```cpp
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main()
{
    regex reg("^([a-z]+)?r([a-z]+)?$");
    string s; int cnt = 0;
    ios::sync_with_stdio(false);
    for(register int i = 1; i <= 12; i++)
    {
        cin >> s;
        cnt += regex_match(s, reg);
    }
    cout << cnt << endl;
    return 0;
}
```

这里重点说一下代码中定义的正则表达式：

因为题目说都是小写，那我们就写 `[a-z]`，但是不只是一个字符，我们写一个 `[a-z]+`。但是有个问题！如果根本没有这些字符，直接出现r，那怎么办？所以我们加上 `?`，并且把前面加上括号，然后写 `r`，后面也是同理。

但是 `regex_match` 匹配到 `r` 时不还是小写字母 `[a-z]` 中的一个吗？怎么跳到 `r`，系统早就帮你想好了，就不用担心了！

### 求赞

---

## 作者：Xiamo_Azure (赞：1)

题目本意：输入12个字符串，问有多少个字符串是包含r的字符串（12个字符串均是小写字母）

------------
我的理解：12个字符串，有r就++

------------
~~不说屁话~~  
~~说屁话~~  
~~屁话~~  
~~话~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;//计数：多少个有r的字符串 
string s[25];//字符串 
int main()
{
 for(int i=1;i<=12;i++) cin>>s[i];//输入 
 for(int i=1;i<=12;i++){
 	for(int j=0;j<s[i].size();j++)
 		if(s[i][j]=='r') { //判断 
 			ans++; //计数 多一个 有r的字符串 
 			break; //退出：下一轮 
 		}
 }
 cout<<ans<<"\n"; //输出 
 
 return 0;
}

```


---

## 作者：wushuang0828 (赞：1)

又是一道水……

思路：for循环输入字符串，并用pos函数判断字符串中有没有r这个字符，有就累加。

代码如下：
```pascal
var
 i,x,s:longint;
 s1:string;
begin
 for i:=1 to 12 do//一共有12个字符串
  begin
   readln(s1);//输入字符串
   x:=pos('r',s1);//用pos函数查找，字符串中有没有r这个字符
   if x<>0 then inc(s);//如果字符串中有r这个字符，s就加一
  end;
 writeln(s);//输出有多少个字符串中有r这个字符
end.
```

---

## 作者：xxxjz (赞：0)

今天就让本蒟蒻来给大家讲一下
#### 搜索大法

俗话说得好：AT结果不换行，满屏WA两行泪

这就是一个活生生的例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/48vojrgn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

算了，好汉不提当年“勇”，开始个大家讲思路吧！

- 我们搜索可以有两个参数（字符串类型，整数类型），分别代表的是（输入的字符串，当前字符串的位置）。

- 然后再进行判断，如果成立就累加，并退出搜索。段代码如下：
```cpp
if(st[q]=='r'){he++;return 0;}
```
- 否则就继续向后搜索。

- 记得一个必备的退出条件：如果当当前搜索的位置已经超过当前字符串的长度的话，就退出（否则TLE等着你！）段代码如下：
```cpp
if(q+1>st.size())return 0;
```

附赠代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int he;
int ss(string st,int q)
{
	if(q+1>st.size())return 0;
	if(st[q]=='r')
	{
	   he++;
	   return 0;	
	}
	ss(st,q+1);
}
int main()
{
	for(int i=1; i<=12; i++)
	{
		cin>>st;
		ss(st,0);
	}
	cout<<he<<endl;
	return 0;
}
```
如果你按照我上面的思路去做的话，保证你
![](https://cdn.luogu.com.cn/upload/image_hosting/yuu9cxq6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


---

## 作者：I_will (赞：0)

我做这道カキ，用的是一种不像递归的递归（有去无回的那种）。

* 首先，我们要递归12次，这是题目固定不变的。
* 接着，我们利用char边输入边判断是否有r存在，就h++。
* 最后，将h输出，再exit(0);就可以了。（真的有去无回，直接结束在递归中。）
* 然后就

![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)
![](https://cdn.luogu.com.cn/upload/image_hosting/2hqa2c8b.png?x-oss-process=image/resize,m_lfit,h_750,w_1022)

就可以了。

----

完美程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,p;
char c;

void cin_cout_r(int k,int n)
{
	if(k>n)
	{
		cout<<h<<endl;
		exit(0);
	}
	p=0;
	while(c=getchar(),c!='\n'){
		
		if(c=='r'&&p==0)p=1,h++;
	}
	cin_cout_r(k+1,12);
}
int main()
{
	cin_cout_r(1,12);
	
	
	
	
	return 0;
} 
```

---

## 作者：Ophelia (赞：0)

# C++ STL
我们当然知道我们可以用字符数组存储这种数据。边读入边计算。但是STL中，有一个容器可以支持不知道长度的字符串，并且提供很多操作。

$\LARGE\color{#66ccff}\text{String}$

string库中包含很多函数，可以支持查找字符的操作。
```
#include<string>
#include<iostream>
using namespace std;
string s;
int sum;
int main()
{
	for(int i=1; i<=12; i++)
	{
		cin>>s;
		if(s.find('r',0)!=string::npos)\\这里的find函数是核心。find函数的格式为(string类变量名).find('要查找的字符(串)',开始查找的位置)。如果查找到该字符(串)，返回该字符(串)在原字符串中第一次出现的位置，否则返回string::npos。所以我们可以直接比较函数值是否为string::npos来判断字符串中有没有要找的字串。
			sum++;
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：Jinyeke (赞：0)

### 题目：输入12个字符串，问有多少个字符串是包含r的字符串（12个字符串均是小写字母）
#### 这题就用pos函数啦，以下为代码（pascal）
```pascal
var
 i,s:longint;
 a:string;
begin
 for i:=1 to 12 do //循环输入12个字符串（懒得弄数组）
  begin
   readln(a);//输入
   if pos('r',a)<>0 then inc(s);//如果存在r就s就+1
  end;
  writeln(s);//输出带r的字符串的总数
  end.
```
### 共建文明洛谷，请勿Ctrl+C!

---

## 作者：Teddy·Bear (赞：0)

这题暴力蛮好的，至少可以过QWQ，也算是种~~新招数~~，暴力大法好！！！
慢慢暴力吧，贴代码
```
#include<bits/stdc++.h>
using namespace std;
int main() {
	int s,sum=0;
	char a[10005],b[10005],c[10005],d[10005],e[10005],f[100005],g[10005],h[10005],i[10005],j[10005],k[10005],l[100005];//华丽的初始化
	gets(a);//华
	gets(b);//丽
	gets(c);//的
	gets(d);//读
	gets(e);//入
	gets(f);//！
	gets(g);//！
	gets(h);//！
	gets(i);//
	gets(j);//
	gets(k);//
	gets(l);//
	for(s=0; s<strlen(a); s++) {//
		if(a[s]=='r') {//
			sum++;//
			break;//特判，若符合则加计数器，再跳出
		}//
	}//

	for(s=0; s<strlen(b);s++) {//同理
		if(b[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(c); s++) {//同理
		if(c[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(d); s++) {//同理
		if(d[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(e); s++) {//同理
		if(e[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(f);s++) {//同理
		if(f[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(g); s++) {//同理
		if(g[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(h); s++) {//同理
		if(h[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(i); s++) {//同理
		if(i[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(j); s++) {//同理
		if(j[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(k); s++) {//同理
		if(k[s]=='r') {
			sum++;
			break;
		}
	}
	for(s=0; s<strlen(l); s++) {//同理
		if(l[s]=='r') {
			sum++;
			break;
		}
	}
	cout<<sum<<endl;//输出
	return 0;
}
```
最后总结，暴力大法好，但要有耐心！！！QAQ

---

## 作者：YLZCB (赞：0)

入门难度，非常简单的一道题（坑死了                        
话不多说贴代码
```#include<iostream>
#include<cstdio>
#include<cmath>
#include<string> 
#include<cstring> 
#include<sstream>
using namespace std;
int main()
{
    char a[101];//定义
    int s=0;//定义计数器
    for(int i=0;i<12;i++)//循环，输入、判断
    {
        gets(a);//输入
        if(strstr(a,"r")) s++;//判断有多少个含有r的字符串
        //有的话s++
    }
    printf("%d\n",s);//输出
    return 0;
}```
附上题意：输入12个字符串，问有多少个字符串是包含r的字符串

---

