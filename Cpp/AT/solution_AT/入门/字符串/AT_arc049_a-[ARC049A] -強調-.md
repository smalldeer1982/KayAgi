# [ARC049A] "強調"

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc049/tasks/arc049_a

文字列 $ S $ と、非負整数 $ A,\ B,\ C,\ D $ が与えられます。

$ S $ の、$ A,\ B,\ C,\ D $ 文字目の後ろにダブルクオーテーション`"`を挿入した文字列を出力してください。

ただし、$ 0 $ 文字目の後ろというのは、文字列の先頭を指すこととします。

## 样例 #1

### 输入

```
MinnnahaNakayoshi
0 6 8 17```

### 输出

```
"Minnna"ha"Nakayoshi"```

## 样例 #2

### 输入

```
Niwawo_Kakemeguru_Chokudai
11 17 18 26```

### 输出

```
Niwawo_Kake"meguru"_"Chokudai"```

## 样例 #3

### 输入

```
___
0 1 2 3```

### 输出

```
"_"_"_"```

# 题解

## 作者：liaokq (赞：3)

# 挑战本题最长题解

## 其实思路是一样的

题目如下：

输入字符串a和b, c, d, e,请在在字符串a的第b、第c、第d、第e处后加双引号

(如果是0就是在开头加一个双引号,0<=b<c<d<e<=字符串a的长度)

(如果是0就是在开头加一个双引号,0<=b<c<d<e<=字符串a的长度)

——————————————————————————

**其实就是要找出b,c,d,e在字符串a之中的位置**

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
char t;
int i,a,b,c,d,l;
int main()
{
	cin>>s>>a>>b>>c>>d;
	l=s.size();
	for(i=0;i<l;i++)
	{
		if(a==i)
		{
			t='"';
		    cout<<t;
		}
		if(b==i)
		{
			t='"';
		    cout<<t;
		}
		if(c==i)
		{
			t='"';
		    cout<<t;
		}
		if(d==i)
		{
			t='"';
		    cout<<t;
		}
        //有一点就是转成char类型输出
		cout<<s[i];
	}
	if(d==l)
	{
		t='"';
		cout<<t;
	}
    //特判：最后一个
	cout<<endl;
	return 0;
}
```


---

## 作者：159号程序员 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT1808)

今天我来给大家分享二种解此题的方法（有借鉴楼下大佬的方法Orz）

第一种：函数插入法

我想起了 _insert()_ 函数，可以来用。

废话不多说，现在上核心代码：

```cpp
int main()
{
    cin >> s;
    k += char(34);//评测机问题，输出char类型的ASCLL码
    for(int i = 0; i < 4; i++)
    {
        cin >> a;
        s.insert(a + i, k);//调用insert()函数
    }
    cout << s << endl;

}
```
这是最简单的方法了，但是我要解释一下insret()的原理图：
| 1 | 3 | 9 | 8 | 5 | x |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |

上面是一个数组，如果我想插入一个数字7在9的前面，怎么办？（保证内存充足，用x表示空）

首先，把9,8,5往后移，就像这样：
| 1 | 3 | x | 9 | 8 | 5 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
然后，把空白处写入7：
| 1 | 3 | 7 | 9 | 8 | 5 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
这样，就插入好了。

-------------------
第二种：先行输出法：
这个方法是碰到要输出“的时候，直接输出，不用对数组操作
上核心代码：
```cpp
    len = s.length();
    for(int i = 0; i < len; i++)
    {
        if(a == i || b == i || c == i || d == i)//判断是否该输出
        {
            k = char(32);
            cout << t;
        }

        cout << s[i];
    }    
    //最后一个特判
    if(d == l)
    {

        cout << t;
    }
    cout << endl;
```
这种方法的优势在于比较好理解，不需要多说。

[引用1](https://www.luogu.com.cn/blog/dalaoisme/solution-at1808)

[引用2](https://www.luogu.com.cn/blog/Zoizer/solution-at1808)

---

## 作者：RioBlu (赞：1)

题目意思：输入字符串a和b,c,d,e，请在字符串a的第（b或c或d或e）个字符后加一个双引号

(如果是0就是在开头加一个双引号,0<=b<c<d<e<=字符串a的长度)
```
#include<bits/stdc++.h>
using namespace std;
string a;long long a1,b1,a2,b2; 
int main()
{
	cin>>a>>a1>>b1>>a2>>b2;
	if(a1==0)cout<<(char)34;//开头加双引号
	for(int s=1;s<=a.size();s++)
	{
		cout<<a[s-1];
		if(a1==s||b1==s||a2==s||b2==s)
		{
			cout<<(char)34;
		}
	}
	cout<<endl;
}
```

---

## 作者：CrTsIr400 (赞：1)

# 0.前言

这道题目没有黄的难度，我觉得只算是一道红。

适合字符串练手，也不用什么奇奇怪怪的`insert`函数。

# 1.如何插入

因为要修改的位置是比较字符串后读入的，所以不能边输入边输出。

楼下的题解说：$4$ 个`insert`没问题啊？

但是把这道题加强一点：给你在原字符串里插入 $m$ 个引号，给出这些引号的位置。

$1\leq |S|\leq m\leq 10^6$，其中 $|S|$ 为输入字符串的长度。

没辙了吧。

我们考虑因为每次插入（字符串是顺序存储结构）是 $O(|S|)$ 的时间复杂度（假设都在字符串头插入一个引号），所以可以**边输出边加引号。**

每次输出一个字符时，**考虑这个字符后面是否有引号，有就给他输出。**

但是时间复杂度其实还是挺大，有 $m$ 个引号的话，这个复杂度还是 $O(|S|\times m)$ 的。

# 2.如何降低时间复杂度

上面提到了这种一个点判断一次的时间复杂度是 $O(|S|\times m)$ 的，和暴力`insert`（往后移位）的效率是一样的。

诶？突然发现插入引号的位置有个范围限制诶！

发现这 $m$ 个引号的位置**不可能**超过 $|S|$ ，因为超过 $|S|$ 就没处加了。

新建一个标记数组 $b$，$b_i$ 表示这个字符串的第 $i$ 位是否要加上引号。

于是我们一边输入引号的位置一边在这个 $b$ 数组上打标记。

然后一边输出一边判断这个上面是否有标记。

时间复杂度 $O(|S|+m)$ 。

# 3.一些细节

注意 $0$ 的情况（字符串头插入引号），然后注意标记数组的大小要**开得和字符串长度一样大**。

# 4.参考代码

```cpp

char s[110];int a,n;bool b[110];
int main()
{
	cin>>s+1;n=strlen(s)-1;
	Fu(i,1,4)cin>>a,b[a]=1;
	if(b[0]==1)putchar('\"');
	Fu(i,1,n)
	{
		putchar(s[i]);
		if(b[i])putchar('\"');
	}
	return 0;
}
//BY 线段树蒟蒻


```

---

## 作者：meyi (赞：1)

这题其实就是一个字符串入门题啦，~~吐槽一下恶意评分~~

思路：使用string.insert()插入引号，因为编译器问题所以插入其ASCII码34.

上代码：
```cpp
#include<iostream>
using namespace std;
string s,t;
int a;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //毫无卵用的优化
    cin>>s;
    t+=char(34);//此时的t就相当于'"'
    for(register int i=0;i<4;++i){//循环四次输入
        cin>>a;
        s.insert(a+i,t);
        //插入字符，注意插入一个引号后就会多一个字符，所以要在a+i位置插入引号
    }
    cout<<s<<endl;
    //输出
}
```

---

## 作者：Vasily0959 (赞：0)

[题目地址](https://www.luogu.com.cn/problem/AT1808)

一道字符串入门题。

思路： 先输入，然后把字符串扫一遍，如果 $a[i]$ 不要加引号就直接输出，不然就输出一个引号再输出 $a[i]$ 。

要注意的是，如果最后一个引号在结尾（如样例），就要特判一下。

当然，不同的实现方法注意点不一样，有的可能要在开头特判。

最后，上代码：

```cpp
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstring>
# include <string>
# include <cstdlib>
# include <algorithm>
# include <stack>
# include <queue>
# include <vector>
# define maxx (103)
# define Pi (3.14159265358979)
# define inf (2147483647)
using namespace std;
string a;
int b,c,d,e,len;
int read() {
	int x=0,f=1;
	char ch;
	while(ch<'0'||ch>'9')  {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
int main() {

	cin >> a;
	b=read();
	c=read();
	d=read();
	e=read();
	len=a.length();

	int i;
	for(i = 0; i < len; i++) {
		if(i==b||i==c||i==d||i==e) {//如果是
			putchar('\"');//输出反斜杠转义引号。
		}
		putchar(a[i]);
	}
	if(e==len) {//特判
		putchar('\"');
	}
	puts("");//AtCoder特有的结尾换行

	return 0;
}
```


---

## 作者：Coding的欢乐 (赞：0)

```
#include<bits/stdc++.h>

using namespace std;
int a[5];
string s;
char c='"';
int main()
{
 //freopen(".in","r",stdin);
 //freopen(".out","w",stdout);
 cin>>s;
 for(int i=1;i<=4;i++)
 	cin>>a[i];
 for(int i=0;i<s.size();i++)
 {
 	for(int j=1;j<=4;j++)
 		if(a[j]==i) cout<<c; 
 	cout<<s[i];
 }
 for(int i=1;i<=4;i++)
 	if(a[i]>s.size()-1) cout<<c;
 cout<<endl; 
 
 return 0;
}
```


---

