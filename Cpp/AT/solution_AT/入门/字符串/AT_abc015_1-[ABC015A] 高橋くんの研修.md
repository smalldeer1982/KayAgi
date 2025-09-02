# [ABC015A] 高橋くんの研修

## 题目描述

高桥君在一家软件公司工作。在这家公司，大家相信短变量名容易导致 bug，因此有使用长变量名的习惯。

现在高桥君想出了 $2$ 个变量名，但遗憾的是他无法分辨它们的长度。

请你替这个在各方面都很可怜的他，从给定的两个只包含小写字母的字符串中，找出长度较长的那个字符串。

## 说明/提示

### 样例解释 1

`isuruu` 有 $6$ 个字符，`isleapyear` 有 $10$ 个字符，因此输出 `isleapyear`。

### 样例解释 2

这样的变量名虽然很奇怪，但在他所在的公司却是正义的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
isuruu
isleapyear```

### 输出

```
isleapyear```

## 样例 #2

### 输入

```
ttttiiiimmmmeeee
time```

### 输出

```
ttttiiiimmmmeeee```

# 题解

## 作者：_Qer (赞：1)

题意：给定两个字符串，求出两个字符串中较长的一个

我们可以用库函数.length()来获取string类型字符串的长度

比较两个字符串的长度后输出即可

```cpp
#include <bits/stdc++.h>//这个头文件包含所有其他头文件
//不用这个头文件就要加上string（cstring）头文件，否则会CE
using namespace std;
string a,b;//两个字符串
int main()
{
  	cin>>a>>b;//string类型可以直接使用cin输入
  	int l1=a.length(),l2=b.length();//取出两个字符串的长度
  	cout<<(l1>l2?a:b)<<endl;//?:   三目运算符
//当？前的逻辑表达式成立时，返回a，否则返回b
  	return 0;
}

```

---

## 作者：Xxzxx (赞：0)

看了楼下的大佬们，觉得就一篇能看懂。
剩下的我~~这个蒟蒻~~看不懂。
发一个C++的string类型题解……吧
```cpp
#include<bits/stdc++.h>//万能头不解释
using namespace std;
string a,b;//两个字符串
int main()//主函数
{
    cin>>a>>b;//输入两个字符串
    if(a.length()>=b.length())//判断条件
    cout<<a<<endl;//若a大就输出a
    else //b大的条件
    cout<<b<<endl;//输出b
    return 0;//程序结束
}
```
第一次发题解，求过QWQ

---

## 作者：Messi李 (赞：0)

这题是输入两个字符串，判断多的字符的那一个

还蛮简单，所以可以直接点做

```
#include<bits/stdc++.h> //万能头文件
using namespace std;
int main(){
    string a,b; //定义字符串，记得要用string
    cin>>a>>b; //输入
    if(a.length()>=b.length()) //根据题意，判断a的字母多还是b的字母多
    {
        cout<<a<<endl; //如果a多，输出a
    }
    else cout<<b<<endl; //否则输出b
}
```
第一次写题解，有不足之处请多多指教

---

## 作者：char32_t (赞：0)

# 题解 AT1013 【高橋くんの研修】
------------
除了使用C++的`string`类型之外，也可以使用C的字符数组实现判断长度。

code：
```cpp
#include<cstdio>
#include<cstring>
char a[100], b[100];//字符数组 
int main(){
	scanf("%s%s", a, b);//读入字符串 
	if(strlen(a)<strlen(b)) printf("%s", b);//判断长度并输出较长的字符串 
	else printf("%s", a);
	return 0;
}
```

---

