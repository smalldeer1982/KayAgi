# [CCC 2020] Cyclic Shifts

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Junior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCJrProblemSet.html) T4 Cyclic Shifts。

## 题目描述

Thuc 喜欢寻找字符串的循环移位。字符串的循环移位是通过不断将字符从字符串的开头移动到字符串的末尾来得到的。当然，一个字符串是它自身的循环移位。例如，`ABCDE` 的循环移位有：`ABCDE`，`BCDEA`，`CDEAB`，`DEABC`，`EABCD`。

给定一些文本串 $T$ 和一个字符串 $S$，判断 $T$ 是否包含 $S$ 的循环移位。

## 说明/提示

#### 【样例解释】
对于第一组样例，`CDEAB` 是 `ABCDE` 的循环移位，且存在于 `ABCCDEABAA` 之中。

对于第二组样例，易证明 `ABA` 的所有循环移位都不存在于 `ABCDDEBCAB` 之中。
#### 【数据范围】
**本题采用捆绑测试**。

对于 $40\%$ 的数据，$|S|=3$。

对于 $100\%$ 的数据，保证 $1\le |S|,|T|\le 1000$。

## 样例 #1

### 输入

```
ABCCDEABAA
ABCDE```

### 输出

```
yes```

## 样例 #2

### 输入

```
ABCDDEBCAB
ABA```

### 输出

```
no```

# 题解

## 作者：jiqihang (赞：2)

### 题目链接
[P11579 [CCC2020] Cyclic Shifts](https://www.luogu.com.cn/problem/P11579)
### 思路
注意看，数据范围写着 $1 \le |S|,|T| \le 100$。

那么 $|S|,|T|$ 是什么呢？

注意到，$S$ 和 $T$ 都是字符串，指的是其长度。

~~范围如此小，考虑打表！~~

好吧，这题打不了表。

那么我们就暴力加模拟。

1. 将 $s$ 的第一位放至末尾。
2. 在 $t$ 中找有没有移位后的 $s$，有则输出 `yes` 并且结束程序。
3. 如果没有，循环结束后输出 `no`。

注意字符串 $s$ 要找个替身来记录。

这里教你们两个字符串函数：

1. `substr` 函数：用于截取子字符串。本例中用于提取 $s$ 截取第一位后的字符串。
2. `find` 函数：寻找字符串。本例中用于在 $t$ 中找有没有移位后的 $s$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string t,s;
    cin>>t>>s;
    string ss=s;//找替身
    for(int i=0;i<s.size();i++)
    {
    	string hc;
    	hc+=ss[0];
    	ss=ss.substr(1); 
    	ss=ss+hc;
        //模拟组建过程
    	if(t.find(ss)!=-1)
    	{
    		cout<<"yes";
			return 0; 
		}//判断
	}
	cout<<"no";
	return 0;
}
```

---

## 作者：ClV_Csy (赞：2)

# P11579 [CCC2020] Cyclic Shifts
## 题意
给出两个字符串 `t` 和 `s`，判断 `t` 中是否有 `s` 的循环移位。对于每次循环移位，字符串中每一个字符都向后移动一位，原最后一位移到第一位。
## 思路
可以写一个函数 `change`，用来实现循环移位。现在先假设这个函数已经写好了，那么很容易就能写出以下代码：
```cpp
string t, s;
cin >> t >> s;
for (int i = 0; i < s.size(); i++) {
	s = change(s); //循环移位
	if (t.find(s) != string::npos) { //使用string头文件的find函数查找s是否是t的子串
		cout << "yes";
		return 0;
	}
}
cout << "no";
return 0;
```
接下来就是实现 `change` 函数了。  
用一个字符串 `a` 来存储循环移位后的字符串。遍历待移位的字符串 `s` 的下标为 $1$ 到 `s.size() - 1` 的每个字符并添加到 `a` 中，再把下标为 $0$ 的字符添加到 `a` 的末尾即可实现。

```cpp
string change(string s) {
	string a;
	for (int i = 1; i < s.size(); i++) {
		a += s[i];
	}
	a += s[0];
	return a;
}
```

## 代码
```cpp
#include <iostream> //iostream中已经包含了string头文件
using namespace std;
string change(string s) {
	string a;
	for (int i = 1; i < s.size(); i++) {
		a += s[i];
	}
	a += s[0];
	return a;
}
int main() {
	string t, s;
	cin >> t >> s;
	for (int i = 0; i < s.size(); i++) {
		s = change(s);
		if (t.find(s) != string::npos) { //使用find不要忘记包含string头文件
			cout << "yes";
			return 0;
		}
	}
	cout << "no";
	return 0;
}
```

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11579)
---

思路：首先我们把数据先输入进来，然后通过循环来找出字符串 $S$ 的所有移位，然后在文本串 $T$ 中找有没有和所有移位相同的字符串，如果有，就输出 ```yes```，然后结束程序就可以了，如果一直没找到，就输出 ```no``` 即可。

有了上面的思路我们就可以写出代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
string t, s, y[1005], temp;
int main()
{
    cin >> t >> s;//输入
    if (s.size() > t.size())//特判，如果字符串s的长度大于t的长度就直接输出no
    {
        cout << "no";
        return 0;//结束程序
    }
    for (int j = 1;j <= s.size();j++)//外层循环
    {
        for (int i = 1;i <= s.size();i++)//内层循环
        {
            y[j] += s[(i - 1 + j - 1) % s.size()];//y[j]加上s[i-1+j-1]，为了避免超出范围，要%s.size。这一步再求字符串s的每一个移位
        }
    }
    for (int i = 0;i <= t.size() - 1;i++)//找文本串t中有没有和移位相同的字符串
    {
        temp = "";//初始值为空串，每次循环前不初始化temp就会带着上一次的结果来执行这次循环
        for (int j = i;j <= s.size() - 1 + i;j++)
        {
            temp += t[j];//temp加上t[j]，temp用来存t里面所有长度和s的长度相同的字串
        }
        for (int j = 1;j <= s.size();j++)
        {
            if (temp == y[j])//找到了
            {
                cout << "yes";//输出yes
                return 0;//结束程序
            }
        }
    }
    cout << "no";//一直没有找到就输出no
    return 0;//代码完美结束！
}
```

无注释代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
string t, s, y[1005], temp;
int main()
{
    cin >> t >> s;
    if (s.size() > t.size())
    {
        cout << "no";
        return 0;
    }
    for (int j = 1;j <= s.size();j++)
    {
        for (int i = 1;i <= s.size();i++)
        {
            y[j] += s[(i - 1 + j - 1) % s.size()];
        }
    }
    for (int i = 0;i <= t.size() - 1;i++)
    {
        temp = "";
        for (int j = i;j <= s.size() - 1 + i;j++)
        {
            temp += t[j];
        }
        for (int j = 1;j <= s.size();j++)
        {
            if (temp == y[j])
            {
                cout << "yes";
                return 0;
            }
        }
    }
    cout << "no";
    return 0;
}
```

[AC](https://www.luogu.com.cn/record/198907982) 记录

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：P11579 [CCC2020] Cyclic Shifts
### 分析
数据范围很小，考虑暴力。

暴力对于 $s$ 循环移位，每次将 $s$ 的第一位放至末尾，再在 $t$ 中寻找是否存在当前移位后的 $s$，如果有输出 `yes`，最后如果都没有，输出 `no`。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string t, s;
signed main()
{
	cin>>t>>s;
	string s1=s;
	for(int i=0;i<s.size();i++)
	{
		string tmp="";
		tmp+=s1[0];
		s1=s1.substr(1);
		s1=s1+tmp;
		if(t.find(s1)!=-1)
		{
			cout<<"yes";
			return 0;
		}
	}
	cout<<"no";
}

---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P11579)

### 题目描述

Thuc 喜欢寻找字符串的循环移位。字符串的循环移位是通过不断将字符从字符串的开头移动到字符串的末尾来得到的。当然，一个字符串是它自身的循环移位。例如，`ABCDE` 的循环移位有：`ABCDE`，`BCDEA`，`CDEAB`，`DEABC`，`EABCD`。

给定一些文本串 $T$ 和一个字符串 $S$，判断 $T$ 是否包含 $S$ 的循环移位。

### 题目分析

暴力枚举字符串 $S$ 的所有情况，再用字符串查找去找。

### 代码如下

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string t,s;
    cin >> t >> s;
    bool found = false;
    for (size_t i = 0; i < s.size(); ++i) {
        string ac = s.substr(i) + s.substr(0, i);
        if (t.find(ac)!= string::npos) {
            found = true;
            break;
        }
    }	
    if (found) cout << "yes" << std::endl;
	else cout << "no" << std::endl; 
    return 0;
}
```
下次见！
拜拜！

---

## 作者：nannangua (赞：0)

[传送门](https://www.luogu.com.cn/problem/P11579)

由题意得，我们需要判断字符串 $T$ 是否包含字符串 $S$ 的任何一个循环移位，因此可以先生成所有可能的循环移位，再检查是否包含。

将字符串 $S$ 复制后，我们可以巧妙生成所有的循环移位。例如，对于字符串 `ABCDE`，我们遍历 `ABCDEABCDE` 的每个长度为 $s$ 的子串，我们就可以得到 $S$ 的所有循环移位。

最后使用 `std::string::find` 的方法检查这些循环移位是否存在于 $T$ 中就完美结束啦。

代码如下。


```cpp
#include<bits/stdc++.h>
using namespace std;
bool op(const string& T, const string& S) 
{
    int s=S.size();
    int t=T.size();
    string cnt=S+S;
    for(int i=0;i<s;i++) 
	{
        string c=cnt.substr(i,s);
        if(T.find(c)!=string::npos) 
		{
            return 1;
        }
    }
    return 0;
}
int main() 
{
    string T,S;
    getline(cin,T);
    getline(cin,S);
    if(op(T,S))  cout<<"yes"<<endl;
    else cout<<"no"<<endl;
    return 0;
}
```

---

