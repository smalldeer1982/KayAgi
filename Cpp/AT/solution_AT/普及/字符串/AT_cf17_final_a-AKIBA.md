# AKIBA

## 题目描述

输入一个字符串S，高桥君在其中任意位置插入A，问是否可以变成AKIHABARA

## 样例 #1

### 输入

```
KIHBR```

### 输出

```
YES```

## 样例 #2

### 输入

```
AKIBAHARA```

### 输出

```
NO```

## 样例 #3

### 输入

```
AAKIAHBAARA```

### 输出

```
NO```

# 题解

## 作者：Texas_the_Omertosa (赞：22)

[题目传送门](https://www.luogu.com.cn/problem/AT3602)

## 本题考查点：

字符串匹配。

## 题意：

你可以在输入的字符串任意位置插入字母 *A* ，问是否能变成   **AKIHABARA** 。

## 思路：

用两个指针去一个一个进行匹配，如果匹配就一起后移，遇 A 不匹配，则用来匹配的指针后移，否则为不匹配。

最后要再扫一遍，遇见不是 A 的就加起来，如果不是 5 个，也是不匹配的，如果不再扫一遍，第 14 个测试点会 WA 。

### 注意：

AT 的题目最后要换行。

废话不多说，上 AC 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>//常用头文件，我一般写好来方便直接调用
using namespace std;
string st;
string str="AKIHABARA";//定义一个用来匹配
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//输入输出加速
	cin>>st;
	if(st==str)
	{
		cout<<"YES"<<'\n';
		return 0;
	}//一样，直接匹配成功
    if(st.size()==str.size()||st.size()>str.size())
	{
		cout<<"NO"<<'\n';
		return 0;
	}//长度相同但不一样，匹配失败，长度更长更不用说
	int n=0;
	int i=0;//模拟指针
	while(i<st.size())
	{
		if(st[i]==str[n])
		{
			++n;
			++i;
			continue;
		}//匹配成功，指针后移
		if(str[n]=='A')
		{
			++n;
			continue;
		}//是 A 但不匹配，跳过
		cout<<"NO\n";
		return 0;//匹配失败
	}
	int len=0;//计数
	int j=0;
	while(j<st.size())
	{
		if(st[j]!='A')
			++len;
		++j;
	}//扫一遍，不是 A 就加
	if(len==5)
	{
		cout<<"YES\n";
	}//不是 A 的字符有 5 个，匹配成功
	else
	{
		cout<<"NO\n";
	}//匹配失败
	return 0;
}
```

我不是 dalao ，但是请帮我点下面那个向上的大拇指 (2n+1) 次，蟹蟹！

---

## 作者：上杉越 (赞：7)

[题目链接](https://www.luogu.com.cn/problem/AT3602)
## 题目大意：
就是给定一个字符串 $s$ ,你可以在$s$的任意位置插入字母 A ，问 $s$ 能否变成 AKIHABARA 。


## 思路:
**大体：这道题因为情况比较有限，所以可以给字符串排个序,然后判断仅有的那几种情况是否符合就大概可以了。**

首先，先把已有的几种情况找出来（分别是:没有 A,一个 A,两个 A,三个 A,四个 A）：
```
s[5]={"RKIHB","RKIHBA","RKIHBAA","RKIHBAAA","RKIHBAAAA"};
```

其次将字符串进行排序。
```
bool cmp(char a,char b){
	return a>b;
}
sort(n.begin(),n.end(),cmp);
```
最后进行枚举，判断是否符合这几种情况就行了。 
如果能变成 AKIHABARA 就输出 YES 否则输出 NO 。

代码就不贴了。

---

## 作者：Anguei (赞：5)

据题意，使用一行正则表达式进行匹配即可：
```plaintext
A?KIHA?BA?RA?$
```

Python 代码：
```python
import re
p = 'A?KIHA?BA?RA?$'
s = raw_input()
print ['NO', 'YES'][re.match(p, s) != None]

```

---

## 作者：lzxhdxx (赞：4)

# AT3602 AKIBA
这是当前次优解&C++最优解

竟然没有打表题解！竟然没有打表题解！

### 题意
输入一个字符串s，判断该字符串是否能只插入'A'就变成"AKIHABARA"

### 思路
题意告诉我们，s（即输入的字符串）经过重复插入'A'的操作后必须与"AKIHABARA"全字匹配，所以如果能变成"AKIHABARA"，s只能缺少'A'，如果别的字符有出入就肯定不能变成"AKIHABARA"

我们把"AKIHABARA"中的四个'A'编号为1、2、3、4，根据这个思路整理一下：

1.s中没有'A'时：

/(只有一种情况，四个'A'都没有)

2.s中只有一个'A'时：

1 2 3 4

3.s中有两个'A'时：

12 13 14 23 24 34

4.s中有三个'A'时：

123 124 134 234

5.s中有四个'A'时：

1234

PS：每种情况下的数字代表s中有的'A'的编号，如：234代表s中有第2、3、4个'A'，而第一个没有

综合以上整理，我们得到下面这个表：

```cpp
str[100] = {"KIHBR","AKIHBR","KIHABR","KIHBAR","KIHBRA","AKIHABR","AKIHBAR","AKIHBRA","KIHABAR","KIHABRA","KIHBARA","AKIHABAR","AKIHABRA","AKIHBARA","KIHABARA","AKIHABARA" }
```

得到表以后，我们就可以开心地打代码了！

Code:
```cpp
#include <iostream>

using namespace std;

string str[100] = { "KIHBR","AKIHBR","KIHABR","KIHBAR","KIHBRA","AKIHABR",
"AKIHBAR","AKIHBRA","KIHABAR","KIHABRA","KIHBARA",
"AKIHABAR","AKIHABRA","AKIHBARA","KIHABARA","AKIHABARA" }, s;//表和输入的字符串

int main()
{
	ios::sync_with_stdio(false);//加速
	cin >> s;//输入s
	for (int i = 0; i < 16; i++)//一共十六种可能，分别存在str[0]~str[15]中
		if (s == str[i])//如果匹配上了
			return cout << "YES\n", 0;//输出能并直接return 0
	cout << "NO\n";//如果没输出YES就是不匹配，输出NO
	return 0;
}
```
数据：21ms /  256.00KB /  411B C++ 

是不是很简单，而且很快呢？打表是一种~~很好~~比较有用而且很简单的做法，学会了能很简单地解决不少题目呢！

目前没有打表题解，求管理大大给过

---

## 作者：happybob (赞：3)

你们 `python` `java` 都用 $\large \color{red} \text{正则表达式}$，不要以为 `c++` 没有正则表达式了！

`c++` 中的正则表达式需要包含头文件 `<regex>`，然后就可以声明某个正则表达式：

```cpp
regex name(^value$); // 其中^与$均可省略，^代表开始，$代表结束

如：
regex reg("^abc+$");
```
那么这里可以匹配的字符串就有：

```cpp
abc
abcc
abccc
abcccc
abccccc
abcccccc
abccccccc
以及其他前面ab并且后面有大于等于1个的c
```

那么正则表达式还有一个重要字符 `?`，它代表前面括号中（如果没有括号就是前一个字符）的字符串有也可以没有，所以对于正则表达式 `ab(cc)?`， `abcc` 与 `ab` 均可以匹配，而 `abc` 则不能匹配。

那么如何判断某个字符串与某个正则表达式匹配？我们需要用到函数 `regex_match`，其函数通常为两个，第一个是需要匹配的字符串，第二个是正则表达式，返回值为 `bool` 类型，匹配成功返回 `true`，否则返回 `false`。

其实正则表达式还有很多其他符号与函数，可以自行百度。

所以本题其实可以用正则表达式做：

```cpp
#include <regex>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    regex reg("^A?KIHA?BA?RA?$");
    string st;
    cin >> st;
    if(regex_match(st, reg))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
    return 0;
}
```

码字不易，求赞！

---

## 作者：RioBlu (赞：1)

我觉得本体有点hard
```
#include<bits/stdc++.h>
using namespace std;
string a,yl="AKIHABARA";
int now,k;
int main()
{
	cin>>a;
	for(int s=0;s<a.size();s++)
	{
		if(a[s]==yl[now])//匹配成功
		{
			now++;
		}
		else//匹配不成功
		{
			if(s>0)
			if(a[s]==a[s-1])//连续两个一样
			{
				cout<<"NO"<<endl;
				exit(0);
			}
			if(yl[now]=='A')now++,s--;//是A，pass
			else//不是A，输出NO
			{
				cout<<"NO"<<endl;
				exit(0);
			}
		}
	}
	k=a.size();//最后，查错
	for(int s=0;s<a.size();s++)
	{
		if(a[s]=='A')k--;
	}
	if(k==5)
	cout<<"YES"<<endl;
	else
	cout<<"NO"<<endl;
}
````

---

## 作者：沉石鱼惊旋 (赞：0)

### 题目翻译

输入一个字符串，可不可以在任意一位插入 $\tt A$，使这个字符串变为 `AKIHABARA`。

### 题目思路

`AKIHABARA` 中只出现了 $4$ 次 $\tt A$，所以，我们枚举所有可能，每个位置都可以有 _选_ 或 _不选_ 两种可能，所以一共只有 $2^4$ 种可能，十分少。

我们只要分别枚举 没有 $\tt A$、一个 $\tt A$、两个 $\tt A$、三个 $\tt A$、四个 $\tt A$ 的情况即可。

### 题目代码

```cpp
//没有 A
if(s=="KIHBR"){puts("YES");return 0;}
//一个 A
if(s=="AKIHBR"){puts("YES");return 0;}
if(s=="KIHABR"){puts("YES");return 0;}
if(s=="KIHBAR"){puts("YES");return 0;}
if(s=="KIHBRA"){puts("YES");return 0;}
//两个 A
if(s=="AKIHABR"){puts("YES");return 0;}
if(s=="AKIHBAR"){puts("YES");return 0;}
if(s=="AKIHBRA"){puts("YES");return 0;}
if(s=="KIHABAR"){puts("YES");return 0;}
if(s=="KIHABRA"){puts("YES");return 0;}
if(s=="KIHBARA"){puts("YES");return 0;}
//三个 A
if(s=="AKIHABAR"){puts("YES");return 0;}
if(s=="AKIHABRA"){puts("YES");return 0;}
if(s=="AKIHBARA"){puts("YES");return 0;}
if(s=="KIHABARA"){puts("YES");return 0;}
//四个 A
if(s=="AKIHABARA"){puts("YES");return 0;}
//都不满足
puts("NO");
```



---

## 作者：damage (赞：0)

## 楼下大佬@Anguei 讲了```python```的```正则表达式```，这里怎么能没有```java```的啦！

---

# 本题实质上可以转化为正则表达式匹配！

---

### 正则表达式

其中```()?```表示括号里的字符可以匹配也可以不匹配，若没有括号则匹配括号前的一个字符,其中```$```相当于匹配结束。

如```KIHABAR```这个字符串匹配正则表达式```A?KIHA?BA?RA?```，因为其中的字符```A```可选匹配(匹配了2个)，而其他字符都匹配成功了，所以可以匹配成功。

其他详情可以自己网上阅读资料了解。

---

代码：
```java
import java.util.Scanner; //java输入库
import java.util.regex.*; //java正则表达式库
public class Main //洛谷里默认类名(文件名)为Main
{
	public static void main(String args[])
	{
		Scanner input=new Scanner(System.in); //相当于输入流
		String str=input.nextLine(); //输入字符串(其实是读取一行)
		String pattern="A?KIHA?BA?RA?$"; //要被匹配的正则表达式
		if(Pattern.matches(pattern,str)) System.out.println("YES");  //如果匹配成功就输出"YES",函数参数顺序千万不能反了!
		else System.out.println("NO"); //反之则输出"NO"
   }
}
```

---

