# Pattern

## 题目描述

Developers often face with regular expression patterns. A pattern is usually defined as a string consisting of characters and metacharacters that sets the rules for your search. These patterns are most often used to check whether a particular string meets the certain rules.

In this task, a pattern will be a string consisting of small English letters and question marks ('?'). The question mark in the pattern is a metacharacter that denotes an arbitrary small letter of the English alphabet. We will assume that a string matches the pattern if we can transform the string into the pattern by replacing the question marks by the appropriate characters. For example, string aba matches patterns: ???, ??a, a?a, aba.

Programmers that work for the R1 company love puzzling each other (and themselves) with riddles. One of them is as follows: you are given $ n $ patterns of the same length, you need to find a pattern that contains as few question marks as possible, and intersects with each of the given patterns. Two patterns intersect if there is a string that matches both the first and the second pattern. Can you solve this riddle?

## 说明/提示

Consider the first example. Pattern xab intersects with each of the given patterns. Pattern ??? also intersects with each of the given patterns, but it contains more question signs, hence it is not an optimal answer. Clearly, xab is the optimal answer, because it doesn't contain any question sign. There are a lot of other optimal answers, for example: aab, bab, cab, dab and so on.

## 样例 #1

### 输入

```
2
?ab
??b
```

### 输出

```
xab
```

## 样例 #2

### 输入

```
2
a
b
```

### 输出

```
?
```

## 样例 #3

### 输入

```
1
?a?b
```

### 输出

```
cacb
```

# 题解

## 作者：YUYGFGG (赞：6)

[宣传本人博客](https://www.yuygfgg.ml/)

tips:不要以为样例没过就一定错

居然只有一个P党的题解

思路：什么也匹配不上的输出'?'，否则随便输出一个除了'?'的字母（这里是'a'）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a,b;
	int n;
	cin>>n>>a;
	for(int j=1;j<n;j++){
		cin>>b;
		for(int i=0;i<a.size();i++){
			if(a[i]=='?'){
				a[i]=b[i];
			}
			if(a[i]=='.'){
				continue;
			}
			else{
				if(a[i]!=b[i]&&b[i]!='?'){
					a[i]='.';
				}
			}
		}
	}
	for(int i=0;i<a.size();i++){
		if(a[i]=='.'){
			cout<<'?';
		}
		else{
			if(a[i]=='?'){
				cout<<'a';
			}
			else{
				cout<<a[i];
			}
		}
	}
	cout<<endl;
	return 0;
}
```



---

## 作者：崔化博 (赞：3)

## 思路
**如果某一位完全不匹配，那么那一位就等于 '!'。如果匹配，那么那一位就等于 '?'。**

'!' 代表要输出 '?'，'?' 代表可以是任何字符，我这里默认是 'a'。最后输出时判断一下就好了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string a,b;
	int n;
	cin>>n;
	for(int j=1; j<=n; j++) {
		cin>>b;
		if(j==1)
		{
			a=b;
			continue;
		}
		for(int i=0; i<a.size(); i++) {
			if(a[i]=='?')
				a[i]=b[i];
			if(a[i]!=b[i]&&b[i]!='?'&&a[i]!='!')
				a[i]='!';
		}
	}
	for(int i=0; i<a.size(); i++) {
		if(a[i]=='!')
			cout<<'?';
		else if(a[i]=='?')
			cout<<'a';
		else
			cout<<a[i];
	}
	return 0;
}

---

## 作者：蓝__ (赞：3)

## 原题链接：[CF412C](https://www.luogu.com.cn/problem/CF412C)

### 分析：
如果某一位能完全匹配（所有字符串该位都一样或只有部分为 ' ？' ），则输出它 ；

如果某一位上出现过除 ' ？' 外两个及以上的不同字符，则输出 ' ？' ；

否则随便输出一个字符。

------------

```cpp
#include<bits/stdc++.h>     //万能头 
#include<ctime>             //随机函数要用的头文件 
using namespace std;
char a[100001],ans[100001];
int n,l;
bool x[100001];             //解释一下：这个数组是用来起“锁定”的效果，
int main(){                 //如果某一位出现的字符种数达到两种，就“锁定”这一位
	ios::sync_with_stdio(0);        //读入优化，考试时别用 
	srand((unsigned)time(NULL));    //随机函数生成代码 
	cin>>n>>a;
	l=strlen(a);
	for(int i=0;i<l;i++) ans[i]=a[i];   //先将ans数组赋值为第一个字符串 
	for(int i=1;i<n;i++){
		cin>>a;                         //循环读入，节省空间 
		for(int i=0;i<l;i++){
			if(x[i]==true||a[i]=='?') continue;  //如果这一位被“锁定”或为‘？’ 
			if(ans[i]=='?') ans[i]=a[i];    //如果这一位不为‘？’且ans数组未录入判定字符 
			else if(ans[i]!=a[i]){        //如果某一位出现的字符种数达到两种
				ans[i]='?';              //改ans数组 
				x[i]=true;                //“锁定”这一位 
			}
		}
	}
	for(int i=0;i<l;i++){
		if(x[i]==false&&ans[i]=='?'){     //如果没被“锁定”且ans数组未录入判定字符
			int s=rand();                //随机生成一个非负数 
			s=s%26+'a';                   //赋值成小写字母 
			ans[i]=(char)s;                //录入ans 
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：Mysterious_Cat (赞：2)

### 题目思路：将第一个字符串作为答案串匹配，用M标记有矛盾的情况，？标记任意解的情况，最后加特判输出即可（M输出？，？输出$a$或$b$）
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    string s;
    cin >> n >> s;
    int len = s.size();
    for(int i = 1; i < n; i++)
    {
        string ss;
        cin >> ss;
        for(int i = 0; i < len; i++)
        {
            if(s[i] == '?') s[i] = ss[i];
            else if(s[i] != ss[i] && ss[i] != '?') s[i] = 'M';
        }
    }
    for(int i = 0; i < len; i++)
    {
        if(s[i] == 'M') printf("?");
        else if(s[i] == '?') printf("a");
        else printf("%c", s[i]);
    }
    
    return 0;
}
```


---

## 作者：落河之秋 (赞：1)

## 题意

给出 n 个包含着小写字母和字符 ? 的字符串，其中 ? 可看作**任何**一个小写字母。输出一个字符串，使输出字符串的每一位与原输入的**多个**字符串的对应位都相同。如果有某一位不同，输出用 ? 代替。

## 分析

题目看似很混乱，但认真考虑下来其实只有以下几种情况：

No.1：输入字符串的这一位上每个字符都是 ?，由于 ? 可看作任意一字符，所以我们可以输出任意字符，在本题解内用 x 代替。

No.2：如果输入字符串这一位上只存在一种小写字母和 ? ，我们需输出这一字母。

分析完毕，实现过程奉上。

## 代码
```cpp
#include<string>
#include<iostream>

using namespace std;

int main()
{
	int n;
	
	cin>>n;
	string s1,s2;
	cin>>s1;
	int len = s1.size();
	for(int i=2; i<=n; i++)
	{
		cin>>s2;
		for(int j=0; i<len; j++)
		{
			char q1 = s1[j],q2 = s2[j];
			if(q1 == '?')  
			{
				s1[j] = s2[j];
			}
			if(q1 != '?' and q1 != q2)
			{
				s1[j] = 'F';
			}
		}
	}
	for(int i=0; i<len; i++)
	{
		if(s1[i] == '?')
		{
			cout<<'x';  //分析1
			continue;
		}
		else if(s1[i] == 'F') //均不同
		{
			cout<<'?';
		}
		else
		{
			cout<<s1[i]; //分析2
		}
	}
}
```


---

## 作者：Okimoto (赞：1)

# 小模拟412C
将第一个字符串设为模板串 $s$ ，针对后面所输入的每一个字符串 $c$ 更新就好了。

输入的 $s$ 中的“？”为可变问号符号，在计算时会在满足题干所说的条件下尽可能变为一个字母，来减少“？”的数量

计算中的“！”为不可变问号符号，应为有多个字符串相同位置的某个字符不同，导致模板串中该位置的字符被替换为“！”。“！”也代表一个“？”，但是其与前一段所说的问号差别在于其是不可以改变的。

若$s_i == c_i $，$s_i$ 不改变。

否则，若$s_i$ = '!'， $s_i$ 不改变。

否则，若$s_i$ = '?'， $s_i = c_i$ 。

否则，若$c_i$ = '?'， $s_i$ 不改变。

否则，$s_i$ = '!'

输出前，将模板串中的'!'全部换为'?'

同时，将模板穿中所有的'?'换为任意字母。

代码
------------
```cpp
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int n;
string s;
string c;
int main()
{
	cin >> n;
	cin >> s;
	for(register int i = 1; i < n; i ++){
		cin >> c;
		for(register int j = 0; j < c.size(); j ++){
			if(s[j] == c[j])
				continue;
			if(s[j] == '!')
				continue;
			if(s[j] == '?')
				s[j] = c[j];
			else if(c[j] == '?')
				continue;
			else{
				s[j] = '!';
			}
		}
	}
	for(int i = 0; i < s.size(); i ++){
		if(s[i] == '!')
			s[i] = '?';
		else if(s[i] == '?')
			s[i] = 'a';
	}
	printf("%s", s.c_str());
	return 0;
}
```


---

## 作者：Digital_Sunrise (赞：0)

## CF412C题解
[题目链接](https://www.luogu.com.cn/problem/CF412C)

[Blog](https://www.luogu.com.cn/blog/yl2330/solution-cf412c)

**题外话**

[双倍经验](https://www.luogu.com.cn/problem/UVA1368)！

### 思路
简单来说就是大模拟。

遍历每一列，看出现了几种不同的字母（不包含 "?" ）。

1. 0个 随便输出一个字母。

2. 1个 输出那个出现的字母。

3. 2个 输出 "?"。

### Coding
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,len;
string s[100010];

int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
		cin >> s[i];
	len = s[1].length();
	for(int i = 0;i < len;i++)
	{
		char ch = '0';
		int sum = 0;
		for(int j = 1;j <= n;j++)
		{
			if(s[j][i] == '?')
				continue;
			if(s[j][i] != ch)
			{
				sum++;
				ch = s[j][i];
			}
			if(sum >= 2)
				goto End;
		}
		if(sum == 0) cout << 'a';
		if(sum == 1) cout << ch;
		continue;
		End:
		cout << "?";
	}
	return 0;
}
```

---

## 作者：thomas_zjl (赞：0)

思路很简单，就是一个模拟。

我们先来看一下题目的操作。

- 如果这一排全是'?'，则输出任意一个字母。

- 如果这一排的有字母的部分都一样，那么输出这个字母。

- 如果这一排有字母的部分不一样，那么输出'?'。

这就是思路。

接下来看看代码吧。

```
#include<bits/stdc++.h>
using namespace std;
string a[100001];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    char ans=0;
    for(int i=0;i<a[1].length();i++){
        ans=a[1][i];//先存一个。
        int flag=1;//用来表示操作的类型。
        for(int j=1;j<=n;j++){
            //如果这二个数不是'?'但他们不相同，输出'?'，跳出循环。
            if(ans!=a[j][i]&&(a[j][i]!='?'&&ans!='?')){
                flag=0;
                cout<<"?";
                break;
            }
            //如果他们之中有一个是'?',但另一个是字母。
            if((ans='?'||a[j][i]=='?')&&(ans!=a[j][i])){
                if(ans=='?')//如果存储的这个是'?'。
                    ans=a[j][i];//就要改变一下。
                flag=2;
            }
            //如果他们都是字母，且一样。
            if(ans==a[j][i]&&ans!='?')
                flag=2;//要改变一下操作的类型。
        }
        if(flag==1) 
            cout<<'x';
        if(flag==2)
            cout<<ans;
        //输出，不多讲了。
    }
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个长度均为 $s$ 的字符串，每个字符串都由小写字母和 $?$（表示这个字符不确定） 表示，求一个能使 $n$ 个字符串的每一位的字母均相等，如果有不符合规定的，则这个字符输出 $?$。你需要尽可能的使 $?$ 的数量最小。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant s\leqslant 10^5$。**
## Solution
每个字符串逐个字符去匹配，如果有不匹配的就用 $?$ 以外的其他字符表示（下面代码中用 $!$ 表示），其他的如果有不确定的随便弄个字母（下面的代码中使用的是 $\text{z}$ 这个字母），就可以过了。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

int n;
string a[100007];

int main() {
	scanf("%d", &n);
	cin >> a[1];
	for(int i = 2; i <= n; ++i) {
		cin >> a[i];
		for(int j = 0; j < a[i].size(); ++j) {
			if(a[1][j] == '?')
				a[1][j] = a[i][j];
			else if(a[1][j] == '!')	continue;
			else if(a[1][j] != a[i][j] && a[i][j] != '?') {
//				puts("Wrong: No");
//				printf("Wrong on text %d\n", j);
				a[1][j] = '!';
//				printf("%c\n", a[1][j]);
			}
		}
	}
	for(int i = 0; i < a[1].size(); ++i) {
//		printf("%c %d\n", a[1][i], a[1][i] == '!');
		if(a[1][i] == '!')	printf("?"); 
		else if(a[1][i] == '?')	printf("z");
		else printf("%c", a[1][i]);
	}
	return 0;
}
```

---

