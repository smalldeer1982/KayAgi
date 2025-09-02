# 天下一リテラル

## 题目描述

一种脚本语言 hnw 有 $3$ 种类型，分别是整数（integer）、字典（dict）和非空集合（set）。其组成如下：
```
dict={expr:expr{,expr:expr}}或{}；
set={expr{,expr}}；
expr=dict或set或integer。
（内层大括号内的元素为可继续添加的元素的类型）
```
现在输入一段脚本，请判断它是字典型脚本还是非空集合型脚本？

## 说明/提示

**数据规模与约定**

所有输入数据保证：

- $s$ 的长度不大于 $50000$；

## 样例 #1

### 输入

```
{1:2}```

### 输出

```
dict```

## 样例 #2

### 输入

```
{1,2}```

### 输出

```
set```

## 样例 #3

### 输入

```
{}```

### 输出

```
dict```

# 题解

## 作者：Lovely_Chtholly (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_tenka1_2015_qualB_b)

### 【分析】

若脚本长度为 $2$，即只有大括号：`{}`，那么这个脚本就是字典型（`dict`）。若脚本长度大于 $2$，那么在括号层数为 $1$ 时出现 `:` 就代表此脚本是字典型的，否则它就是非空集合型（`set`）。但是因为这道题是 AT 的题，所以输出完后还需换行，如果你觉得思路没问题但是 WA 了可能就是这个原因。

### 【AC 代码】

```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
bool flag;//这里我用 flag 存脚本的类型，flag 为 1 时脚本是字典型，为 0 时是非空集合型。
string s;
signed main()
{
	cin>>s;
	if(s.size()==2)flag=true;
	for(int i=0,sum=0;i<s.size();i++)
	{
		if(s[i]=='{')sum++;
		else if(s[i]=='}')sum--;
		if(sum==1 and s[i]==':')flag=true;
	}
	if(flag)puts("dict");
	else puts("set");
	return 0;
}
```

~~高尔基说过：~~

>~~莫抄袭，棕了你的名，空悲切！~~

---

## 作者：So_noSlack (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT_tenka1_2015_qualB_b)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/tenka1_2015_qualB_b)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定一个集合形式，判断此集合是 `dict` 还是 `set`。

## 思路

简单的**模拟题**。

首先需要**特判** `{}` 的情况，应**直接输出** `dict`。

接着观察两个集合的特征，很容易即可发现 `dict` 和 `set` 的最**明显的区别**就是一个有 `:` 一个没有，而我们需要注意 `expr` 可是**任何集合或者数字**，所以有可能出现 `{1,{2:3}}` 的情况，**而这种情况就不能直接看有无冒号进行判断了**。

我们需要用 $num$ 来记录当前是**第几层括号**，如果**在第一层括号中发现了冒号**，那么这个集合就是 `dict` 了，反之就是 `set`。

经过以上分析，很容易即可写出**代码**了：

```cpp
#include<iostream>
using namespace std;

string str;

int main() {
	cin >> str;
  	// 特判 {} 的情况
	if(str.length() == 2) {
		cout << "dict\n";
		return 0;
	}
	int num = 0; // num 记录层数
	for(int i = 0; i <= str.length(); i ++) {
		if(str[i] == '{') num ++; // 遇到 { 层数加 1
		if(str[i] == '}') num --; // 遇到 } 层数减 1
		if(str[i] == ':' && num == 1) {
			cout << "dict\n"; // 最外层遇到 ：
			return 0;
		}
	}	
	cout << "set\n"; // 换行好习惯
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117821306)

$$\text{The End!}$$

---

## 作者：Eason_cyx (赞：1)

开头说句题外话：这题居然有 $105$ 个测试点。

[题目传送门](https://www.luogu.com.cn/problem/AT_tenka1_2015_qualB_b)

我们首先观察 dict 和 set 的区别。

可以发现：dict 有冒号，而 set 没有。

按这个思路写，你会 WA on #7。

为什么？因为它是可以嵌套的，而题目求的是最外边一层是什么类型。

所以我们只需要开一个计数器，当遇到大括号时加 $1$，表示进入新的一层，当遇到反大括号时减 $1$，表示跳出这一层。遇到冒号时，如果在最外面这一层，就是 dict；反之就是 set。

有个小细节：一对空的大括号是 dict，需要特判。

代码很简单：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s; cin >> s;
    if(s.size() == 2 && s[0] == '{' && s[1] == '}') {
        cout << "dict" << endl;
        return 0;
    }
    bool flag = false;
    int sum = 0;
    for(int i = 0;i < s.size();i++) {
        if(s[i] == '{') sum++;
        if(s[i] == '}') sum--;
        if(s[i] == ':' && sum == 1) flag = true;
    }
    if(flag) cout << "dict" << endl;
    else cout << "set" << endl;
    return 0;
}
```

---

## 作者：zk_y (赞：0)

这道题目一开始看还挺吓人，但是仔细一看我们只需要输出 ``dict`` 或者 ``set`` 就可以了。

## 特判

我们发现如果这个字符串是 ``{}``。那么他一定是要输出 ``dict``。

写出特判代码：
```cpp
if(a[0]=='{'&&a[1]=='}'&&a.length()==2){
	printf("dict\n");
	return 0;
}
```
## 普通结论

我们发现对于 ``dict``，他的某一位中一定含有 ``:`` ，但是如果 ``set`` 中带有 ``dict``，他也是有 ``:`` 的。我们应该怎么办呢？

我们发现，在最外面的一层括号，只有 ``dict`` 是含有 ``:`` 的。那么，我们只需要枚举最外面一层括号就行了。我们可以设定一个括号的层数，如果遇到前大括号就加 $1$，如果遇到后大括号就减 $1$。如果遇到其他的（除了``:``）就需要跳过。如果遇到了 ``:``，我们就需要判断此时的括号数，如果是 $1$（注意这里必须是 $1$，不能大于 $1$)，那么我们直接输出 ``dict`` 就行了。如果到最后还没有输出，那么我们就输出  ``set``。

---

# AC 代码
```
#include<bits/stdc++.h>
using namespace std;
string a;
int kuohao_num;
int main(){
	cin>>a;
	if(a[0]=='{'&&a[1]=='}'&&a.length()==2){
		printf("dict\n");
		return 0;
	}
	for(int i=0;i<a.length();i++){
		if(a[i]=='{')kuohao_num++;
		if(a[i]=='}')kuohao_num--;
		if(kuohao_num==1&&a[i]==':'){
			printf("dict\n");
			return 0;
		}
	}
	printf("set\n");
	return 0;
}
```


---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，“输入的脚本的类型”指的是**最外层**的类型。要判断其实不难，易错点在于在哪里判断。我的方法是遍历输入时计算左右括号数量之差，当差为 $0$ 时就在最外层。

1. 设置变量 $b \gets 0$，遍历输入时忽略第一个括号和最后一个括号，遇到 `{` 则 $b \gets b+1$，遇到 `}` 则 $b \gets b-1$，当 $b=0$ 时就在最外层。

1. 在最外层遇到 `:` 就是 `dict`，一直没有遇到就是 `set`。

另外，输入为 `{}` 时特判为 `dict`。
## 代码
```python
a = list(input())
b,c = 0,0
if a!=['{','}']:
    for d in range(1 , len(a)-1):
        if b == 0 and a[d] == ':':
            print('dict')
            c = 1
            break
        if a[d] == '{':
            b += 1
        elif a[d] == '}':
            b -= 1
    if c == 0:
        print('set')
else:
    print('dict')
```
还没有 python 题解，希望管理员通过！

---

## 作者：ylch (赞：0)

# AT_tenka1_2015_qualB_b 天下一リテラル 题解

~~小日子过得不错国的题？A 了它！~~

[-题目传送门-](https://www.luogu.com.cn/problem/AT_tenka1_2015_qualB_b)

### 题目简述

让你判断在某种编程语言中，一段字符串是集合类型（set）还是字典类型（dict）。

判断依据：

字典：花括号内部有若干对用冒号隔开的键值对，可能有嵌套情况。

集合：花括号内部是用逗号隔开的数字，可能会有嵌套的情况。

如果出现多种类型嵌套的情况，请求出最外层的类型。

### 解题思路

读懂了题意这道题就很简单了，就是判断特征，非一即二。

如果最外层花括号里有冒号，则为字典类型；否则为集合类型（别忘了特判只有两个大括号时为字典类型）。

判断花括号层数类似括号匹配的方法，用计数器来实现。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

signed main()
{
	cin >> s;
	if (s == "{}")	//空括号为字典型
		return puts("dict"), 0;
	int sum = 0;
	for (unsigned i=0; i<s.size(); i++)
	{
		if (s[i] == '{')	sum++;	//用类似模拟栈下标的方法判断层数
		else if (s[i] == '}')	sum--;
		if (sum == 1 && s[i] ==':')
			return puts("dict"),0;
	}
	return puts("set"), 0;
}
```

国外的题目一定要加换行！我用的 puts 函数是自带换行的。

End
----------

管理员大大辛苦啦~

谢谢大家！

---

## 作者：yyz_100110 (赞：0)

**题意：**   

读懂题目是写程序的第一步。输入一个字符串，```dict``` 是冒号，```set``` 用逗号。主要看他是不是有空集合的字符串，再判断是哪一个。     


**案例：**   


~~~cpp
{1:2}      
{1,2}
{  }
~~~
我们还是以案例入手，样例 1 是 ```{1:2}``` 样例 2 是 ```{1,2}```。我们其实可以对这一组案例经行对比。可以发现，主要是判断是什么符号，但我们现在还不能一股脑的去写代码，你还有两个大括号需要去解决，我们要先去排除他，或者用一个变量存起来，不要让他干扰到我们的判断，要不然就会出现你想的和 ```IDE``` 的答案根本对不上。然后第三个样例，几本不用管，给他单独处理就可以了。  


## **ACCode**
~~~cpp
#include<iostream>
//现在都没几个人去记头文件了，听句劝，别老用万能头，耗时间
#include<cstring>// string 的头文件，要记得
using namespace std;
string s,a="set";//专门找一个来当 set
int sum=0;
int main(){
    int i;
    cin>>s;//输入。
    if(s.length()==2){
        cout<<"dict"<<endl;//用来特判逗号，直接输出结束程序
        return 0;
    }
    for(int i=0;i<s.length();i++){// length 是给字符串用的
        if(s[i]=='{') //用来排除大括号
            sum++;//开始
        if(s[i]=='}') 
            sum--;//结束
        if(sum==1){
            if(s[i]==':') 
                a="dict";//只要找到冒号，就可以确定了
        }
    }
cout<<a<<endl;//日本题要记得换行
return 0;//比赛要写
}//求过！


---

## 作者：fish_love_cat (赞：0)

**题意：**

给你一个集合，如果他是非空集合，输出 ```set```，否则输出 ```dict```。

**对题意的补充：**

```dict``` 用 $\texttt{:}$ 来分隔开数据，```set``` 用 $\texttt{,}$ 来分隔开数据，空集合是 ```dict```，只有一个数据的集合算 ```set```，集合中的集合算大集合的一部分，而我们要求的是大集合的品种。

**思路：**

特判空集和只有一个数据的集，其余情况模拟即可。

我们初始默认该集合是 ```set```。

如果遇上 $\texttt{\{}$ 层数就加一，说明进入了小集合中；如果遇上 $\texttt{\}}$ 层数就减一，说明离开了当前集合，回到了大集合里。如果此时层数是 $1$ 就代表现在我们在最大的集合里，在这里如果当前遇上了 $\texttt{:}$，就说明这是 ```dict```，不是 ```set```，更新信息。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    int cs=0;
    string op="set";
    if(s.length()==2){
        cout<<"dict\n";
        return 0;
    }
    for(int i=0;i<s.length();i++){
        if(s[i]=='{') cs++;
        if(s[i]=='}') cs--;
        if(cs==1){
            if(s[i]==':') op="dict";
        }
    }
    cout<<op<<endl;
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

不难发现在第一层括号的字符决定了这是 ``dict`` 还是 ``set``，所以我们可以遍历 $s$ 并记录此时的括号层数，当层数为 $1$ 时，如果此时有字符 $\texttt{:}$ 那么就是 ``dict``，如果此时有字符 $\texttt{,}$ 那么就是 ``set``，如果第一层括号内什么也没有，如果 $s$ 是一对空括号就是 ``dict``，否则是 ``set``。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,cnt;
string s;
string solve(void){
	if(n==2) return "dict";
	for(int i=1;i<=n;i++){
		if(s[i]=='{') cnt++;
		if(s[i]=='}') cnt--;
		if(cnt==1){
			if(s[i]==':') return "dict";
			if(s[i]==',') return "set";
		}
	}
	return "set";
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>s;
		n=s.length(),s=" "+s;
		cout<<solve()<<"\n";
	}
	return 0;
}
```

---

