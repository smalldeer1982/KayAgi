# Letters Cyclic Shift

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase English letters. You have to pick exactly one non-empty substring of $ s $ and shift all its letters 'z' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'y' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'x' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/23d27bb9cf2cd76a0555d2babeb08bc9315530bc.png) 'b' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'a' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'z'. In other words, each character is replaced with the previous character of English alphabet and 'a' is replaced with 'z'.

What is the lexicographically minimum string that can be obtained from $ s $ by performing this shift exactly once?

## 说明/提示

String $ s $ is lexicographically smaller than some other string $ t $ of the same length if there exists some $ 1<=i<=|s| $ , such that $ s_{1}=t_{1},s_{2}=t_{2},...,s_{i-1}=t_{i-1} $ , and $ s_{i}&lt;t_{i} $ .

## 样例 #1

### 输入

```
codeforces
```

### 输出

```
bncdenqbdr
```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
aaacaba
```

# 题解

## 作者：q779 (赞：2)

要求字典序最小，首先想到从最左端开始改变

那么这样做一定是最小的吗？例如下面这种

```aabcdefabb```

如果改变了第一个字符```a```，它会变成```z```，字典序不降反升

我们可以初步得到结论，从**第一个不为**```a```**的位置**开始改变，能得到最小结果

再看题目，要求改变的是**非空**[**子串**](https://baike.baidu.com/item/%E5%AD%90%E4%B8%B2/11047664?fr=aladdin)，因此只能改变到**下一个不为**```a```**的位置**

因此```aabcdefabb```改变后变为```aaabcdeabb```

还有一种情况要**特判** 例如```aaaaa```

题目要求你必须选择一个非空子串，这种情况只要把最后一个字符改变就行了

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
string s;
bool flag;
signed main()
{
    cin>>s;
    for(R int i=0; i<s.size(); i++)
        if(s[i]^97) //s[i]!='a'
        {
            s[i]--;flag=1;
        }
        else if(flag) return cout<<s,0;
    if(!flag)s[s.size()-1]='z';//特判
    cout<<s;
    return 0;
}
```

---

## 作者：Yi_Fan (赞：2)

# 前言：
写程序要注意解题技巧，考虑全面


------------
# 题意：
简介来说就是将 $b$ 等字符变为前一个，而 $a$ 变为 $z$ ,让一段字串发生上述变化，让字符串变为最小字符串。
#### 补充：
**最小字符串**：从头至尾最小字符组成的字符串，例如，$a<b<c<d$ 等就像 $1<2<3<4$ ,其实就是类似整数的东东


------------
# 分析：
1. 求最小字符串，所以**一定**不改变$a$字符
从头开始模拟从第一个非 $a$ 字符到第二个 $a$ 字符之前

1. 当从未出现非 $a$ 字符就将最后一个 $a$ 变为 $z$


------------
# 程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
//变量区
string s;//记录字符串
bool a = false;//判断是否进入子串变化
//主函数
int main(){
	cin >> s;
    for(int i = 0 ; i < s.length(); i ++){
        if(s[i] != 'a'){
            if(a == false)//如果第一次进入，改变变化
            a = true;
            s[i]--;
        }
        else
        if(s[i] == 'a' && a == true)//如果已经开始变化但碰到a就退出
        break;
    }
    if(a == false)//从未变化就代表全部为a，所以最后一位a变为z
    s[s.length()-1] = 'z';
    cout << s;
    return 0;
}
```


---

## 作者：Sternenlicht (赞：1)

思路：

要求字典序最小，那我们就不能让字符串 $s$ 中第一个 'a' 变为 'z'，这样反而让字典序增加了。

我们可以这样做：用一个 bool 变量 flag ，初始化为 $0$。遍历 $s$，碰到不是 'a' 的字符，就让这个字符减一，这样一定可以使字典序小，且让 flag 变为 $1$。碰到 'a' 字符时，若不是第一个，则输出 $s$，结束程序。

遍历结束后，若程序还未结束，且 flag 为 $0$，说明 $s$ 中的所有字符都是 'a'，就要让最后一个 'a' 改为 'z'。无论如何，输出 $s$。

```cpp
#include <bits/stdc++.h>
#define endl '\n'//优化endl的速度 
using namespace std;

int main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);//优化读入速度 
	string s;cin>>s;bool flag=0;
	for (int i=0;i<s.size();i++)
		if (s[i]!='a')s[i]--,flag=1;//不为a，s[i]-1，标记 
		else if (flag)return cout<<s<<endl,0;//为a且不是第一个，输出 
	if (!flag)s[s.size()-1]='z';//若s中所有元素都是a，则让最后一个a变z 
	cout<<s<<endl;//输出s 
    return 0;
}
```

---

## 作者：Tiago (赞：0)

## 题意简述

给你一个由小写字母组成的非空字符串 $s$，请你修改一串**连续**的子串，使每个字符往前移一位（其中 `a` 变为 `z`），问：修改后字典序最小的字符串是什么？

## 题目分析

考虑几种情况：

1. 普通情况

很显然 `a` 不需要改动，因为 `z` 的字典序大于 `a` 的字典序。

在看下样例：

`codeforces` --> `bncdenqbdr`

`abacaba` --> `aaacaba`

是不是只改动了非 `a` 的字符（以下简称其他字符）。

其中，样例 $2$ 又之改动了最开始两个 `a` 中间的字符（或者说是改动了出现过其他字符后第一个的 `a` 前面的字符）。

于是，不难打出以下代码：

```cpp
for(int i=0;i<st.size();i++)
	if(st[i]!='a')st[i]--,t++;//t 表示出现了几个其他字符
		else if(t!=0)break;//如果此时的 a 前面已经有了其他字符，则退出循环
```

2. 特殊情况

及全是 `a` 的情况。

此时应该把最后一位改为 `z`（因为必须改动一次）。

代码：

```cpp
if(t!=0)cout<<st;//有其他字符，说明已经改动过了，直接输出
	else st[st.size()-1]='z',cout<<st;//t 为0，说明没有其他字符（及全是 a），把最后一位改为 z，后输出
```

## 代码

注释就不打了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int main()
{
	string st;cin>>st;
	for(int i=0;i<st.size();i++)
		if(st[i]!='a')st[i]--,t++;
			else if(t!=0)break;
	if(t!=0)cout<<st;
		else st[st.size()-1]='z',cout<<st;

	return 0;
}
```

---

## 作者：judgejudge (赞：0)

# 极简代码

因为只对一个子串修改，所以我们只能连续修改一次。

那么修改就是**在第一个a到第2个a之间**。

但万一全都是a？那么就在最后一个a上，将其改为z。

代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;//没啥用
string st;
bool opt=false;//用来判断是否执行过
int main(){
	register int i,j;
	cin>>st;
	for(i=0;i<st.length();i++)
	if(st[i]!='a'){//如果不是
		if(opt==false)opt=true;//第一次执行
		st[i]--;//移位
	}
	else if(opt==true)break;//如果已经到第二个a，即执行过，跳出循环
	if(opt==false)st[st.length()-1]='z'; //特殊情况
	cout<<st<<endl;
	return 0;
}
```


---

## 作者：codemap (赞：0)

这道题要注意的地方比较多，要分很多种情况讨论

主要就是尽量改前面的,并且尽量不改a

第一种:全都是a,因为必须要更改,所以只需将最后一位改为z(这一种卡了我好久)

第二种:首位为a.不全是a,修改第一个不是a的到下一个a之前

第三种:首位不是a,不全是a,从第一个修改到第一个a之前

上代码
```c
#include<iostream>
using namespace std;
int main()
{
    string a;
    int i,p;//p后面有用
    bool f=0;//后面有用
    cin>>a;
    for(i=0;i<a.size();i++)
        if(a[i]!='a')//如果不是a
        {
            f=1;//有不是a的
            break;//跳出循环
        } 
    if(!f)//如果全都是a
    {
        for(i=0;i<a.size()-1;i++)
            cout<<'a';//从第一个到倒数第二个不动
        cout<<'z';//最后一个改为z
    }
    else//不全是a
    {
        if(a[0]=='a')//如果首位为a
        {
            for(i=1;i<a.size();i++)
                if(a[i]!='a')//如果不是a了
                {
                    p=i;//记录一下第一个不是a的位置
                    break;//跳出循环
                }
            for(i=p;i<a.size();i++)//从p到最后
            {
                if(a[i]=='a')//如果是a了
                    break;//跳出循环
                a[i]=char(a[i]-1);//只要没到a就修改
            }
        }
        else//如果首位不是a
            for(i=0;i<a.size();i++)
            {
                if(a[i]=='a')//如果是a了
                    break;//跳出循环
                a[i]=char(a[i]-1);//只要没到a就修改
            }
        cout<<a;//输出修改之后的结果
    }
    return 0;//完美结束
}
```
# 请勿抄袭

---

## 作者：RioBlu (赞：0)

此题就是，你得用一次机会，在这个字符串的某个连续一段做这样的手断：（将z→y→x→......b→a→z）

#### 然后让这个字符串的字典序最小

刚开始我懵逼了，s的长度100000。

#### 后来仔细一想，含'a'最好不改变。

#### 改变了就肯定变大了。

改哪个地方好呢？

最前边的一个不包含'a'的连续一段

## 要是全'a'呢？改最后一个（因为必须要改）
```
#include<bits/stdc++.h>
using namespace std;
string a;
long long tou=-1,wei=-1,mk;
int main()
{
	cin>>a;
	for(int s=0;s<a.size();s++)//寻找头尾
	{
		if(a[s]!='a')
		{
			if(tou==-1)tou=s;
			mk=1;
		}
		else
		{
			if(tou!=-1)
			{
				wei=s-1;break;
			}
		}
	}
	if(wei==-1&&mk==1)wei=a.size()-1;
	if(mk==0)//改最后一个
	{
		a[a.size()-1]='z';
	}
	else
	for(int s=max((long long)0,tou);s<=wei;s++)//改变
	{
		a[s]=char((int)a[s]-1);
	}
	cout<<a<<endl;
}
```

---

