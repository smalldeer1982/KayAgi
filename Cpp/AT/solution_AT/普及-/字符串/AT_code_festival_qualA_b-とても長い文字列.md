# とても長い文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-quala/tasks/code_festival_qualA_b

文字列 $ S $ は、文字列 $ A $ を、$ 10^{100} $ 個連結させた文字列です。

文字列 $ S $ の $ B $ 文字目の文字は何かを出力しなさい。

## 说明/提示

### 部分点

- $ 1\ ≦\ B\ ≦\ 100,000 $ の全てのテストケースに正解すると、 $ 20 $ 点が与えられる。
- 残りの全てのテストケースに正解すると、さらに $ 80 $ 点が与えられる。

### Sample Explanation 1

文字列 $ S $ は、`abcabcabcabc…` と続く文字列です よって、$ 7 $ 文字目は `a` となります。

### Sample Explanation 2

文字列 $ S $ に含まれる全ての文字は `b` なので、$ 9 $ 文字目も `b` となります。

### Sample Explanation 3

大きな整数が入力されることがあることに注意してください。

## 样例 #1

### 输入

```
abc
7```

### 输出

```
a```

## 样例 #2

### 输入

```
bbb
9```

### 输出

```
b```

## 样例 #3

### 输入

```
kljhasdfkjahfadfakhsdfaklh
1000000000```

### 输出

```
h```

# 题解

## 作者：goodlearndaydayup (赞：10)

这道题求字符串A然后A.size()+1为A[0],一直重复下去，求第n位。但是从n的数据范围很明显要%而不能直接-。
%有一个坑，所以我们可以：
   n=(n-1)%A.size()+1;
   废话不多说直接上代码```
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
string s;
int n;
int main()
{
     cin>>s;
     cin>>n;
	 n=(n-1)%s.size()+1;
	 cout<<s[n-1];
    return 0;
}
```
QAQ

---

## 作者：rui_er (赞：3)

本题的数学方法有过了，我来一发循环链表（C/C++专属福利）。

根据题目意思，要我们循环遍历一个字符串。自然可以想到循环链表。

把样例1建入循环链表长什么样呢？如下图

![](https://cdn.luogu.com.cn/upload/pic/62743.png)

可以看到效果很好。

[关于循环链表的知识](http://baidu.apphb.com/?q=%E5%BE%AA%E7%8E%AF%E9%93%BE%E8%A1%A8)

代码：

```cpp
#include <iostream>
using namespace std;

struct node
{
	char data;
	node* next;
};

int main()
{
	string s;
	int n;
	cin>>s>>n;
	int l = s.length();
	int k;
	node *first, *last;
	first = NULL, last = NULL;
	for(k=0;k<l;k++)
	{
		node *p = new node;
		p->data = s[k];
		p->next = NULL;
		if(k == 0) first = p;
		else
		{
			if(k == l - 1) p->next = first;
			last->next = p;
		}
		last = p;
	}
	last = first;
	for(k=1;k<n;k++,last=last->next);
	cout<<last->data<<endl;
	return 0;
}
```

---

## 作者：lsyx0918 (赞：1)

这道题就是让搜索在第n个位置的字符。但是有时候可能会超限，所以中间还需再次计算（仿佛闻到了Python列表的味道）

您预订的题解套餐已在你的家门口：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
//定义全局变量 
string s;
int n;
int main()
{
	//输入 
    cin>>s;
    cin>>n; 
    n=(n-1)%s.size()+1;//计算b在s的哪个位置上
    cout<<s[n-1];//输出 
    return 0;//结束 
}
```

一定要记住：

**AT不换行，暴零两行泪！**

---

## 作者：据设错了 (赞：1)

                         **见这道题这么水，我也来水一发**
                      不说了~~我偏要说你来咬我啊~~直接上代码
简的不能再简的代码（温馨提示：该程序有毒，请不要抄袭，要抄就把他改正好）：
```
#include<bits/stdc++.h>//万能头
using namespace std;
int b;//int够用了
string a;
int main()
{
	cin>>a>>b;
	cout<<a[(b-1)%strlen(a)];
}//输入输出，完美结束
```


---

## 作者：残夕·无月 (赞：1)

## 吼吼吼第一弹题解~~~

首先了解一下本题题意：

此处有一串字符串与一个数。

a串长<=50,且数b：1<=b<=1,000,000,000

现在从a串第一个元素开始(到最后一个时再返回至第一个)，求第b个元素。

在了解题意的基础上，问题也就迎刃而解了。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N(55);
char a[N];
int n;//int型的数到2147483647，可过
int main()
{
	scanf("%s",a);
	scanf("%d",&n);
	int count=(n-1)%(strlen(a))+1;//计算出在执行到第n次时所对应的字母
	printf("%c",a[count-1]);//由于数组从0存储，故需-1
	while(1);
    return 0;
}

```
结束 O(∩_∩)O

by某蒟蒻 

~~我好强大~~

---

## 作者：wushuang0828 (赞：0)

思路：先求出第b个字符到底是字符串中的第几个字符，并输出这个字符。

题目很水，废话不多说，放代码：
```pascal
var
 b,x:longint;
 a:string;
begin
 readln(a);//输入
 readln(b);//输入
 x:=(b-1) mod length(a)+1;//求出第b个字符，到底是字符串中的第几个字符
 writeln(a[x]);//输出第b个字符
end.
```

---

## 作者：I_will (赞：0)

我我又又来来发发题题解解了了：：

这道题其实很简单，

* 输入：一个字符串+一个数（要用long long）。
* 过程：判断（数-1）%字符串的长度。
* 输出：用for判断在哪一位，找到再输出就可以退出了。

这是程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
string x;
long long xd,o;
int main()
{
	cin>>x;
	cin>>xd;
	o=(xd-1)%x.size();
	for(long long i=0;i<x.size();i++)
	{
		if(i==o){cout<<x[i]<<endl;break;}
	}
	return 0;
}
``` 

---

## 作者：stry (赞：0)

其实这道题求字符串st然后st.size()+1为st[0],一直重复下去，求第n位就行了。

但是从n的数据范围很明显要%而不能直接-。 %有一个坑，所以我们可以： n=(n-1)%A.size()+1; 

废话不多说，看代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
string st;
long long n,m;
int main()
{
     cin>>st>>n;
     n=(n-1)%st.size()+1;
     m=n-1;
     cout<<st[m];
    return 0;
}
```


---

