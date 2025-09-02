# HQ9+

## 题目描述

HQ9+是一种搞笑的编程语言，只有4种指令，都是单个字符的：
"H"输出"Hello, World!"；
"Q"输出这个程序本身的源代码；
"9"输出歌曲"99 Bottles of Beer"的歌词（你可以自己上网搜这首歌）；
"+"增加内部储存中的数值

注意"H"和"Q"指令是区分大小写的，必须使用大写。程序中不属于这些指令的字符请忽略。

给你一个用HQ9+写的程序，问这个程序是否会有任何输出。

## 说明/提示

第一个样例中只有一个指令"H"，输出了"Hello, World!"。

第二个样例中没有任何一个字符是这个程序的指令。
翻译贡献者UID：68708

## 样例 #1

### 输入

```
Hi!
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
Codeforces
```

### 输出

```
NO
```

# 题解

## 作者：紫金依旧 (赞：4)

发一篇题解.

其实这道题的题意很简单——

# 在这句代码中含有H、Q、9就输出YES

重点是——

# ‘+’不执行输出，只进行运算，故应输出NO。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a; 
int main()
{
	cin>>a;
  	int len=a.length();//求长度
	for(int i=0;i<len;i++)
		if(a[i]=='H'||a[i]=='Q'||a[i]=='9')//如果含有H,Q,9
		{	
			cout<<"YES";
			return 0; 
		}
	cout<<"NO";	//否则输出NO
	return 0; 
}
```
打造文明洛谷,拒绝抄袭

---

## 作者：松毛虫 (赞：1)

比较简单的一道题，你甚至只需要用一个变量就可以解决。
阅读题目，可以发现，只要这个字符串里面有H或Q或9就OK了！
```cpp
#include<iostream>
using namespace std;
int main()
{
    char c;//定义字符
    while(cin>>c){//直接在循环里读入
        if(c == 'Q' || c == 'H' || c == '9' ){//判断这个字符能否输出
        cout<<"YES";//能输出YES
        return 0;//结束程序
        }
    }
    cout<<"NO";//如果所有字符都输入来了还不可以，就是输出NO。
    return 0;
}
```


---

## 作者：秋本馄淡 (赞：1)

只要用字符串枚举一下 或者 一个个字符输入就好了

为了省时，用字符输入的形式：
```
var
  c:char;
begin
  while not eoln do
  begin
    read(c);
    if c in['H','Q','9'] then
    begin writeln('YES');
    halt; end;
  end;
  writeln('NO');
end.
```

---

## 作者：幻蓝 (赞：1)

其实只要 H、Q、9 这三个字符每个pos一遍就行了，如果任何一个 pos的位置>=1 就说明有输出。

不废话，上代码：
```pascal
var
        s:string;
        a,b,c:integer;
begin
        readln(s);
        a:=pos('H',s);
        b:=pos('Q',s);
        c:=pos('9',s);
        if (a>=1)or(b>=1)or(c>=1) then writeln('YES')
        else writeln('NO');
end.
```

---

## 作者：Clever_Jimmy (赞：1)

这是道大水题……（并不知道为什么不用CF的Berlandish）

题目意思简洁明了，说白了就是输入一个字符串，看里面有没有‘H’或者是‘Q’或者是‘9’

那么就简单了，遍历就行了。代码如下：
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mian()
{
	char a[10000];//存储字符串
    int len,i,flag=0;
    /*
		len是字符串的长度；
        i是循环用的；
        flag是看它有没有要求的字母
    */
    scanf("%s",a);//输入字符串
    len=strlen(a);//求长度
    for(i=0;i<len;i++)//遍历
		if(a[i]=='H' || a[i]=='Q' || a[i]=='9')//如果有
			flag=1;
    if(flag==1)
		printf("YES");
    else
		printf("NO");
	system("pause");
	return 0;//完美结束
}

```


---

## 作者：lsyx0918 (赞：0)

这道题是一道~~大水题~~，只需判断字符串里有没有'H''Q'和'9'就可以了。主要考察的是字符串中字符的判断。

话不多说，上代码喽（此题解为DEV-C++ 5.11）：
```cpp
#include<iostream>
#include<cstring>//在这里也可以用万能头，但是在考试中不建议用
using namespace std;
int main()
{
	string a;//定义字符串a，当然也可以用char类型数组，一会我会单说
	getline(cin,a);//输入
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='H' or a[i]=='Q' or a[i]=='9')
		{
			cout<<"YES"<<endl;
			return 0;
		}
	}
	//遍历，判断 
	cout<<"NO"<<endl;
	return 0;
}
```
还有一种方法，比楼上的那个简单得多，用的是char类型数组：
```cpp
#include<iostream>//可以用万能头哟
using namespace std;
int main()
{
	char a[10000000];//定义char类型数组，忘了有多长了，干脆就定义这么多
	gets(a);//输入
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]=='H' or a[i]=='Q' or a[i]=='9')
		{
			cout<<"YES"<<endl;
			return 0;
		}
	}
	//遍历，判断 
	cout<<"NO"<<endl;
	return 0;
}
```
最后，提醒一下：

**AT不空行，暴零两行泪！**

---

## 作者：CZQ_King (赞：0)

最短代码！

利用``find``函数+``Python3``轻松解决！

------------
在``Python3``中的``find``函数与``C++``相似：

``s.find(str,begin,end)``在字符串``s``中``s[begin]``到``s[end]``之间寻找字符串``str``，若没有找到返回$-1$。

有一种略写：``s.find(str)``在``s``中寻找``str``，若没有找到返回$-1$。

因为我们要求有没有输出，而题意告诉我们字符串中含有$H,Q,9$都会输出。那么我们只需要寻找字符串中是否含有$H,Q,9$即可，于是使用``find``函数：

``s.find('H')+s.find('Q')+s.find('9')+3``

如果三个都没有找到，那么返回的就是$0$，即返回假，若有其中一个找到，那么返回一定是一个正数，即返回真。

------------
代码：
```python
s=input();print("YES"if(s.find('H')+s.find('Q')+s.find('9')+3)else"NO")
```

---

## 作者：开心的猪 (赞：0)

这道题输出的方法只有读入H/Q/9，这道题的最大难点可能在于如何读入。

PS:给大家一个地址，是99 bottles of beer。[19843 8 bottles of beer](http://www.99-bottles-of-beer.net)http://www.99-bottles-of-beer.net

下面是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	char a;
	for(int i=0; i<100; i++)
	{
		scanf("%c", &a);
		if(a<33||a>126)
		{
			break;
		}
		else if(a=='9'||a=='H'||a=='Q')
		{
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```


---

## 作者：二字 (赞：0)

# 最简短代码，主程序仅4行
### 本题就是求一个字符串里是否含有“H”“Q”“9”几个字符中的任意一个
我解题用的是find函数，这个函数不知道是在哪个库里的因为我用的是万能头文件，a.find(b)表示在a字符串中查找是否含有b字符串，如果有返回b的首字母所在的位置，如果没有返回-1

话不多说代码奉上：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
if(s.find("H")+s.find("Q")+s.find("9")!=-3) cout<<"YES";
	else cout<<"NO";
} 
```
if中如果它们三个find函数都找不到它们的和就是-3，如果但凡有一个找到它们的和就不是-3了

我没加return 0因为贪代码长度（滑稽）各位在比赛中请加上以免WA掉

---

## 作者：FP·荷兰猪 (赞：0)

总结：英文题面还是很迷惑人的！我第一眼点开题目还以为是一个大模拟呢！（我还是太菜了）

通俗来讲，本题的题意就是：**给你一个字符串，求这个字符串中有没有'H'，'Q'，'9'这三个字符中的任意一个或几个。**

数据范围很小，直接模拟即可。

代码**详解**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//读入优化肯定是要带上的
    string s;
	cin>>s;//输入一个字符串
    bool f;//f用来判断该字符串是否含有'H'，'Q'，'9'这三个字符
    f=false;//f初始化为假
	int i;
    for(i=0;i<s.size();i++)//i扫描一遍字符串里的所有字符
    {
        if(s[i]=='H' || s[i]=='Q' || s[i]=='9')//如果s[i]是'H'，'Q'，'9'三者其一，就说明该字符串一定含有这三个字符
        {
            cout<<"YES\n";
            return 0;//为减小时间复杂度，这里做一个剪枝，扫描到该字符立刻输出YES，停止程序
        }
    }
    cout<<"NO\n";//如果i扫描完一遍也没扫到合法字符，输出NO
    return 0;
}
```
~~我绝不会告诉你第一次我把YES打成了Yes结果WA了2333~~

---

## 作者：土川崇贺 (赞：0)

		本题便利逐个判断，如不符合要求，直接输出YES，程序结束；最后输出NO。
```
#include<iostream>
using namespace std;
int main()
{
    string a;
    cin>>a;
    for(int i=0;i<a.length();i++)
    {
    	if(a[i]=='H' || a[i]=='Q' || a[i]=='9')
    	{
    		cout<<"YES"<<endl;
    		return 0;
		}
	}
	cout<<"NO"<<endl;
	return 0;
}

```

---

## 作者：Ace_Radom (赞：0)

这道大水题，虽然有~~85组~~数据

# 唯一的坑就是“+”是不算的

### “+”不输出，只是执行“增加内部储存中的数值”操作

# 题目问你有没有输出

好了，上代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string n;  //定义字符串
	int l,i;
	getline( cin , n );  //读入一整行字符串
	l = n.size();  //求长度
	for ( i = 0 ; i < l ; i++ )
	{
		if ( ( n[i] == 'H' ) || ( n[i] == 'Q' ) || ( n[i] == '9' ) )  //一个一个查，“+”不算
		{
			cout << "YES";  //查到了，直接输出+return 0结束
			return 0;
		}
	}
	cout << "NO";  //没查到
	return 0;  //别忘了！
}
```

就是那么水啊-

---

