# Translation

## 题目描述

### 题面描述

Berland 和 Birland 两地均有各自的语言，Berlandish 和 Birlandish。V 是一个翻译员，负责将 Berlandish 翻译成 Birlandish。将 Berlandish 翻译成 Birlandish 其实非常简单，只需把这个单词倒过来。比如单词`code`翻译过来就是`edoc`。但是粗心的 V 还是会犯一些错误。现在请你帮她判断一下他翻译的是否正确。

## 样例 #1

### 输入

```
code
edoc
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
abb
aba
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
code
code
```

### 输出

```
NO
```

# 题解

## 作者：Phykyer (赞：9)

楼下大佬的代码都是把字符串反转之后比较  
比起来我这个好像略显低级，但是很好懂  
直接两个数组比较就ok了
```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

char a[101],b[101];

int main()
{
	cin>>a;
	cin>>b;
	int lena=strlen(a);//读取长度的函数
	for(int i=0;i<lena;i++)
	{
		if(a[i]!=b[lena-i-1])//我这里是从0开始循环，所以要在b数组这里-1，不然会错
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";//若程序还未结束则翻译正确
	return 0;
}
```

---

## 作者：Playnext (赞：5)

一道模拟题，要求反转**字符串**。


这里我直接用头文件**algorithm**里的**reverse**，当然也可以手打一位一位交换。


代码1：


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext

string T1, T2;

int main () {
    cin >> T1 >> T2;
    reverse (T1.begin (), T1.end ());    //反转
    puts (T1 == T2 ? "YES" : "NO");        //string自带比较
    return 0;
}
```

或者用头文件**cstring**里的**strrev**。


代码2：


```cpp
#include <cstdio>
#include <cstring>
using namespace std;    //BY Playnext
const int MAXN=1e3+1;

char T1[MAXN], T2[MAXN];

int main () {
    scanf (" %s %s", T1, T2);
    strrev (T1);    //反转
    puts (strcmp (T1, T2) == 0 ? "YES" : "NO");
    return 0;
}
```

---

## 作者：XMK_萌新 (赞：1)

```cpp
//我宣誓：这题要用数据结构！
//假的【咧嘴笑】
//利用栈先进后出。。一次A 
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
string a,b,r;	//r是翻转后的a 
stack<char> s;
int main()
{
	cin>>a>>b;
	for(int i=0;i<a.size();i++) s.push(a[i]);
	while(!s.empty())
	{
		r+=s.top();
		s.pop();
	}
	if(b==r) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

求过QAQ

第一次竟然把“数据结构”打错了？？？QWQ

---

## 作者：Ca2ng (赞：1)

这是一道~~我最讨厌的~~字符串题目了  
但还是一遍过了（超小声  
# 思路如下  
1. 定义两个字符数组（主要是我不会string）  
1. 定义n表示字符的长度  
1. 循环检查当前的字符是否与对称字符一致  
1. 若不一致则输出并结束  
1. 若循环跑完还是一致的则输出并结束  
  
# 代码↓↓↓  
（别问我为什么没写注释，我是不会告诉你我懒的）
```cpp
#include<bits/stdc++.h>
using namespace std;
char x[101],y[101];
int main()
{
	cin>>x>>y;
	int n=strlen(x);
	for(int i=0;i<n;i++)↓
	{
		if(x[i]!=y[n-i-1]) 
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```



---

## 作者：土川崇贺 (赞：1)

    	首先判断两字符串长度是否相等，如果不相等直接输出NO，否则将a的第i位与b的第长度-i-1为比较，只要有一处不一样就输出NO，否则输出YES。
            代码奉上：
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    string a,b;//定义字符串
    cin>>a>>b;//输入字符串
    if(a.length()!=b.length())//如果长度不相等
    {
    	cout<<"NO";//直接输出NO
    	return 0;//结束程序
	}
	else
	{
		for(int i=0;i<a.length();i++)//循环比对
		{
			if(a[i]!=b[a.length()-i-1])//不相等
			{
				cout<<"NO";//输出NO
				return 0;//结束程序
			}
		}
	}
	cout<<"YES";//如果程序运行到这里，说明符合要求，输出YES
	return 0;//结束程序
}

```


---

## 作者：灵小沙 (赞：1)

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
	string a,b;
	cin>>a>>b;
	int lena=a.size();//取a的长度 
	int i;
	if(b.size()!=lena)//如果a的长度和b的不一样 
	{
		cout<<"NO";//直接输出NO 
		return 0;//结束 
	} 
	else
	{
		for(i=0;i<lena;i++)
		{
			if(a[i]!=b[lena-i-1])//不等于就 
			{
				cout<<"NO";//输出NO 
				return 0;//结束 
			}
		}
	}
	cout<<"YES"; //最后还没有return 0就输出YES 
	return 0;
}


---

## 作者：yanjun (赞：1)

/\*
Berland和Birland两地均有各自的语言，Berlandish和Birlandish.V是一个翻译员，负责将Berlandish翻译成Birlandish.将Berlandish翻译成Birlandish其实非常简单，只需把这个单词倒过来.比如单词code翻译过来就是edoc.但是粗心的V还是会犯一些错误。现在请你帮她判断一下他翻译的是否正确。


输入格式


两行，分别是一个Berlandish单词和V翻译的Birlandish单词。单词中所有字母均为小写拉丁字母（其实就是英文字母）;单词长度均不超过100字符，单词中不包含任何多余空格。


输出

一行，如果V的翻译是正确的，输出YES。否则输出NO\*/

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    string a,b;
    cin>>a>>b;
    reverse(a.begin(),a.end());
    if(a==b)
    cout<<"YES"<<endl;
    else
    cout<<"NO"<<endl;
}

```

---

## 作者：OdtreePrince (赞：0)

# -字符串-

只能说纯模拟了

首先来个特判，如果长度不相同，那肯定错了

再用循环进行逐一判断，如果错了直接输出并退出

水过啦！！

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s1,s2;
    cin>>s1>>s2;
    if(s1.size()!=s2.size()){
        cout<<"NO";
        return 0;
    }
    for(int i=0;i<s1.size();i++){
        if(s1[i]!=s2[s2.size()-1-i]){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
    return 0;
}~~~

---

## 作者：SKTelecomT1_Faker (赞：0)

基本字符串倒置。（废话这可是红题）

把这个字符串转过来，所以我们需要另一个字符串进行储存结果，可以倒序字符串，最后进行比较。

注意YES和NO要大写。

Code↓
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
char a[101],b[101];
signed main()
{
    cin>>a>>b;
    int n=strlen(a);
    for(register int i=0;i<n;i++)
    {
        if(a[i]!=b[n-i-1])//比较两个字符串是否相反
        {
            cout<<"NO"<<endl;//是的话输出NO
            exit(0);//走了
        }
    }
    cout<<"YES"<<endl;//之前已判断，无脑输出YES
    exit(0);//好习惯伴随我们一生
}
```

当然这道题也可以用string做，Code↓
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
signed main()
{
    string a,b;
    cin>>a>>b;
    for(register int i=0;i<a.size();i++)
    {
        if(a[i]!=b[a.size()-i-1])//判断是否符合
        {
            cout<<"NO"<<endl;//输出NO
            exit(0);//走人
        }
    }
    cout<<"YES"<<endl;//之前已判断，无脑输出YES
    exit(0);//好习惯伴随我们一生
}
```
我们不妨来介绍一下它的用法：

string是C++、java、VB等编程语言中的字符串，字符串是一个特殊的对象，属于引用类型。 C++标准库中string类以类型的形式对字符串进行封装，且包含了字符序列的处理操作。在c++中头文件是#include<cstring>（string或string.h均可qaq）

int capacity()const; //返回当前容量（即string中不必增加内存即可存放的元素个数）

int max_size()const; //返回string对象中可存放的最大字符串的长度

int size()const; //返回当前字符串的大小

int length()const; //返回当前字符串的长度

bool empty()const; //当前字符串是否为空

void resize(int len,char c);//把字符串当前大小置为len，并用字符c填充不足的部分

这些都是一些常用技巧，string类长度用size或length求，为string(你自己设的未知量）.size()或为string(你自己设的未知量）.length(),读入用cin或scanf（记住是%s），输出用cout或printf（记住也是%s）相加后直接把两个拼在一起等。

希望对大家有帮助qwq。

---

## 作者：黯黑の夜 (赞：0)

这篇题解有点低级

用字符数组就能解决

代码来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    char a[101],b[101];
    cin>>a>>b;
    for(int i=0;i<strlen(a);i++)
    if(a[i]!=b[lena-i-1])
    {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    return 0;
}
```


---

