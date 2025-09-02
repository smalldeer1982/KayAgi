# Word Capitalization

## 题目描述

Capitalization is writing a word with its first letter as a capital letter. Your task is to capitalize the given word.

Note, that during capitalization all the letters except the first one remains unchanged.

## 样例 #1

### 输入

```
ApPLe
```

### 输出

```
ApPLe
```

## 样例 #2

### 输入

```
konjac
```

### 输出

```
Konjac
```

# 题解

## 作者：紫金依旧 (赞：18)

水题一道

首先，读题。

“大写是把第一个字母改成一个大写字母”

所以，我们只需要输入一段字符串，对其首字母进行操作。

好，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
char n[1005];
int i;
int main()
{
    while((n[i]=getchar())!='\n')
    	i++;//输入不解释
    if(n[0]>='a'&&n[0]<='z')
    	n[0]-=32;//判断如果是小写就改写成大写
    for(int j=0;j<i;j++)
        cout<<n[j];//输出该单词
    return 0;
}
```
好了，但是看在我对一道水题如此用心的份上
# 不给个赞在走么

---

## 作者：wuyutong111 (赞：9)

```pascal
这题……不想说
但高速一下P党，P语言有个upcase函数，可以把一个字符串（或一个字符）转化成大写，比如s:=upcase('w');那么s就等于'S'。
代码：
var
 s:ansistring;
begin
 readln(s);//输入s
 s[1]:=upcase(s[1]);//把第一个字符转化成大写
 writeln(s);//输出
end.

别忘记点赞o(￣▽￣)ｄ
```

---

## 作者：Higashikata_Jousuke (赞：4)

## 扯话区

这道题嘛。。。~~大水题~~

## 提示区

_只要对第一个字母进行特判，判断是否是小写就行了，如果是，就改为大写_ 


## 代码区

```
#include<iostream>
#include<cstring>
#include<cstdio> 
using namespace std;
char a[10001]；//防抄袭qwq
int main()
{
      cin>>a;
      if(a[0]>='a'&&a[0]<='z')
          a[0]-=32;   
 //因为输入默认是在a[0]，平时习惯a[1]的同鞋要注意惹！ 
      cout<<a;
      return 0;
}

```


### ~~编者的话~~
              
———————da♂ rk腹便便的分割线———————
              
in the end:
### 请勿抄袭！
              
管理大大给过鸭qaq

---

## 作者：Luban (赞：3)

## 这题很适合新手~~我~~练习字符串（~~大水题（雾）~~）

言归正传，最近我在使用string代替字符数组，下面就写个string吧（毕竟12篇题解里还没有~~可能是我瞎了~~）

就是判断第一个字符是不是小写，如果是改成大写

# 改成大写：str[i]+='A'-'a';

### 注意string是从0开始的数组，所以首字母在s[0]

上代码吧~~QAQ~~
```cpp
#include<iostream>
using namespace std;
int main()
{
    string s;
    cin>>s;
    if (s[0]>='a'&&s[0]<='z') s[0]+='A'-'a';
    cout<<s<<endl;
    return 0;
}
```
# 拒绝抄袭，共建美好洛谷

~~管理大大看我写了这么多字给过吧qwq~~


---

## 作者：SKTelecomT1_Faker (赞：2)

思路很简单：输入一个字符串，对其第一个字母进行判断，如果是大写直接无脑输出，是小写转成大写之后再无脑输出。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
signed main()//主程序
{
    string s;
    cin>>s;//输入
    if(s[0]>='a'&&s[0]<='z')//判断首字母大小写
    {
        s[0]-=32;//转大写
        cout<<s<<endl;//无脑输出
    }
    else cout<<s<<endl;//无脑输出
    exit(0);//好习惯伴我们一生
}
```
既然这篇文章提到了string，我们不妨来介绍一下它的用法：

string是C++、java、VB等编程语言中的字符串，字符串是一个特殊的对象，属于引用类型。 C++标准库中string类以类型的形式对字符串进行封装，且包含了字符序列的处理操作。在c++中头文件是#include<cstring>（string或string.h均可qaq）

int capacity()const; //返回当前容量（即string中不必增加内存即可存放的元素个数）

int max_size()const; //返回string对象中可存放的最大字符串的长度

int size()const; //返回当前字符串的大小

int length()const; //返回当前字符串的长度

bool empty()const; //当前字符串是否为空

void resize(int len,char c);//把字符串当前大小置为len，并用字符c填充不足的部分

这些都是一些常用技巧，string类长度用size求，为string(你自己设的未知量）.size(),读入用cin或scanf（记住是%s），输出用cout或printf（记住也是%s）相加后直接把两个拼在一起等。

希望对大家有帮助qwq。

---

## 作者：开心的猪 (赞：2)

这道题可以直接读入后判定第一个字母是否是小写字母，如果是的，就把它变成大写，如果不是，就原样输出。

下面是代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	char a[1000]={0};
	int ans=0;
	for(int i=0; i<1000; i++)
	{
		scanf("%c", &a[i]);
		if(a[i]=='\n')
		{
			a[i]=0;
			break;
		}
		ans=i;
	}
	if(a[0]<='z'&&a[0]>='a')
	{
		a[0]=a[0]-'a'+'A';
	}
	for(int i=0; i<ans+1; i++)
	{
		printf("%c", a[i]);
	}
	return 0;
}
```


---

## 作者：林家三少 (赞：0)

	CF题+1

其实我们只需要一个判断，判断第一个字母是不是大写，所以这题非常的水，代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>  //用string就要打这两个文件头
using namespace std;
string st;  //定义好变量
int main()
{
	cin>>st;  //将st输入
	for(int i=0;i<=st.size()-1;i++)  //开始循环输出
	{
		if(st[0]>='a'&&st[0]<='z'&&i==0)
			cout<<char(st[0]-32);  //如果它是小写那就把它改成大写
		else
			cout<<st[i];  //否则就输出
	}
	return 0;
}
```


---

## 作者：一滴小水滴 (赞：0)

## 这道题...也太水了一点吧！ ~~佩服那些没有过的人~~
## 这题只需要判断第一个字符是否大写（我用的是C++STL的islower())，是小写就变成大写（toupper(字符))，否则照抄    ~~我也真是没什么好讲的了~~
### 那我们直接看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	getline(cin,s);
	if(islower(s[0]))
	{
	    cout<<(char)toupper(s[0]);
	    for(int i=1;i<s.size();i++)
	        cout<<s[i];
	}    //用STL判断第一个字符是不是小写，如果是就将第一个转换为大写，
                          //其它的字符直接照抄。
	else cout<<s<<endl;   //不是小写就直接照抄。
	return 0;    //这个程序就这么愉快地结束了。
}
```
***
## 我也不知道该说什么好了，总之，大家天天AC！

---

## 作者：T_F_P (赞：0)

这道题考大写：

先普及一下：大写字母的ASCLL码比小写字母的大

所以——————只需要判断第一个字母是否大于‘Z’即可

下面附上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	char b[10000];
	scanf("%s",b);
	if(b[0]>'Z'){
		b[0]=b[0]-'a'+'A';
	}
	printf("%s",b);
	return 0;
} 

```


---

## 作者：Trans_Portal (赞：0)

很奇怪这题没有过水被隐藏。
## 由于C++自带字母大写转换函数（toupper，同样有小写转换tolower），这道题成为了难度接近a+b problem的题目。
------------
#### 不多说，上代码。
```cpp
#include<iostream>
using namespace std;
char a[1001];
int main(){
	cin>>a;
	a[0]=toupper(a[0]);
	cout<<a;
    return 0;
}
```

---

## 作者：Zirnc (赞：0)

首先友好地普及一下 `toupper` 函数的用法。
`toupper(int c)`，即将字符转成大写。如果原来是大写的不变。返回的是一个大写字符。参数就是你的 `char` 字符。

思路：输入一个字符串，然后改他的第一个字符就行了。

# 代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    string s;
    cin >> s;
    s[0] = toupper(s[0]);
    cout << s << endl;
    return 0;
}
```

---

## 作者：youyou2007 (赞：0)

这道题题意是将一个单词的首字母改成大写。我的思路就是判断首字母是不是大写，是，不变；否，变成大写（-32）.
下面上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
string s;
int main()
{
    cin>>s;//输入字符串
    if(s[0]<=91&&s[0]>=65)//判断首字母是不是大写
    cout<<s; 
    else//是，则-32，转换成大写
    {
        s[0]-=32;
        cout<<s;//输出即可
    }
 return 0;
}
```


---

## 作者：BB2655 (赞：0)

提供一种scanf的输入方法

在没有数据时，scanf的返回值为$EOF$，即$-1$

同时还要判断读入的字符是否为换行符

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char c=getchar()  //读入首位字母
	if(c>='a')  printf("%c",c-'a'+'A');
	else  printf("%c",c);  //判断大小写并输出
	while(~scanf("%c",&c)!=EOF&&c!='\n')  printf("%c",c);
    //开始循环输入输出
	return 0;
}
```

---

## 作者：meyi (赞：0)

#### 神犇们已经提供了使用字符串的解法，本蒟蒻再补充一种使用单个字符的解法。
#### 上代码：
```cpp
#include<cstdio>
main(){
    char ch=getchar();
    putchar(ch>96?ch-32:ch);//只需要将首字母大写即可
    while(~(ch=getchar()))putchar(ch);//后面的字符直接输出
}
```

---

## 作者：rill4474 (赞：0)

## 没啥好说，直接上代码
```pascal
var
 i,j:longint;
 s:string;
begin
read(s);//输入
s[1]:=upcase(s[1]);//转大写
write(s);//输出
end.
```

---

## 作者：该起什么名字 (赞：0)

就是把第一个单词判断一下就好了
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1005];
int main()
{
	cin>>s;
	if(s[0]>='a'&&s[0]<='z') s[0]=s[0]-' ';
    //判断是否是大写，如果不是，则转化 
	cout<<s;
	return 0;
}
```

---

