# Palindromic Supersequence

## 题目描述

You are given a string $ A $ . Find a string $ B $ , where $ B $ is a palindrome and $ A $ is a subsequence of $ B $ .

A subsequence of a string is a string that can be derived from it by deleting some (not necessarily consecutive) characters without changing the order of the remaining characters. For example, "cotst" is a subsequence of "contest".

A palindrome is a string that reads the same forward or backward.

The length of string $ B $ should be at most $ 10^{4} $ . It is guaranteed that there always exists such string.

You do not need to find the shortest answer, the only restriction is that the length of string $ B $ should not exceed $ 10^{4} $ .

## 说明/提示

In the first example, "aba" is a subsequence of "aba" which is a palindrome.

In the second example, "ab" is a subsequence of "aabaa" which is a palindrome.

## 样例 #1

### 输入

```
aba
```

### 输出

```
aba```

## 样例 #2

### 输入

```
ab
```

### 输出

```
aabaa```

# 题解

## 作者：引领天下 (赞：4)

其实这题根本不用那么麻烦，只需一个数组即可。

由于没有限制是最小回文串，所以输出原串后再输出它的翻转即可。

这样的串一定是回文串。
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;//一个串足矣
int main(void){
    cin>>s;
    cout<<s;//先输出原串
    for(int i=s.size()-1;i>=0;i--)cout<<s[i];//翻转
}
```

---

## 作者：meyi (赞：1)

# STL大法好！
#### 本题是special judge，所以可以有多种答案，而最简单的答案便是输出原字符串后，再输出翻转后的原字符串。而STL中的reverse函数便可以帮助我们完成翻转的工作。
#### 接下来上代码：
```cpp
#include<cstdio>
#include<cstring>//strlen所在头文件
#include<algorithm>//reverse所在头文件
char s[1001];
main(){
	scanf("%s",s);//输入字符串，建议不要使用gets读取字符串
	printf("%s",s);//输出原字符串
	std::reverse(s,s+strlen(s));
    //reverse函数用法:reverse(首地址,尾地址),作用为翻转该数组头地址至尾地址-1之间的元素。
	puts(s);//输出翻转后的字符串。
}
```

---

## 作者：RedLycoris (赞：0)

来个python题解

由于只是要求A是B的子串，而没有限制长度最短（如果限制的话就比这难得多了），所以我们可以贪心的让B为A+A的反串。

代码如下：

```python3
s=input()
print("zrmtcl"+s+s[::-1]+"lctmrz")

# s[::-1]表示s的反串

# 由于限制B长度远大于A的长度的2倍，所以我们可以加一些私货（雾
```

---

## 作者：judgejudge (赞：0)

# 通俗易懂！！


------------

这道题最好的一点就是：**输出任意一个解！！！**

所以我们就把这**单词翻折过来，再输出**就好辽！！！

下面奉上AC代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	int i,j,k,n;
	string st;
	cin>>st;
	for(i=st.length()-1;i>=0;i--)st+=st[i];//在末尾加上倒过来的字符
	cout<<st;//输出
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

【题意】

> 给你一个字符串A，找一个字符串B，使得B是一个回文串，且A是B的子串

【分析与解】

> 如果B字符串中含有A字符串，那么A字符串便是B字符串的子串。所以我们可以在A字符串的基础上构造出一个新的字符串，使得该字符串为回文字符串

> 字符串的长度只有1e3，可以直接模拟输出答案。

代码详解：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define ss cout<<s[i]
string s;
int main()
{
    cin>>s;
    int ls,i;
    ls=s.size();//ls存放的是字符串s的长度
    cout<<s;//首先输出s，使得A串是B串的子串
    for (i=ls-1;i>=0;i--)//倒序输出A串，使得B串是回文字符串
    {
        ss;//上面有define的东西
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：Andysun06 (赞：0)

# 题解 CF932A
_______
## 为pascal同胞们送上福利~~~
## 其实是一道蛮简单的题，先把输入的字符串输出，再把它倒着输出
## 上代码：
    program andyCF932A;//防抄袭
    var s:ansistring;//string也可以
        i:longint;
    begin
     readln(s);//输入
     for i:=1 to length(s) do
      write(s[i]);//正的输出（也可以直接输出（本人刚刚才发现
     for i:=length(s) downto 1 do
      write(s[i]);//倒着输出
     writeln;//换行（在pascal软件里比较方便
    end.

---

## 作者：PC_DOS (赞：0)

既然这道题没有限制最短回文字符串，那么只要同时输出原串和它的倒转就可以了(题目保证字符串长度小于10^3，那么输出不会超过10^4)。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
string strReverse(string strOrigin){ //字符串倒转函数
    if (strOrigin.length() == 0){
        return "";
    }
    long long i;
    string ans;
    for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
    return ans;
}
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    string sInput; //字符串
    getline(cin,sInput); //读入串
    cout<<sInput<<strReverse(sInput); //输出原串和它的倒转
    return 0; //结束
}
```

---

