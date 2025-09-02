# [NWRRC 2015] Easy Arithmetic

## 题目描述

Eva 是一名三年级的小学生。她刚刚学会了如何进行任意精度整数的加减法。她的作业是计算一些表达式。这很无聊，所以她决定在作业中增加一点小技巧。Eva 想在表达式中添加一些加号和减号，使其值尽可能大。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10+20-30
```

### 输出

```
10+20-3+0
```

## 样例 #2

### 输入

```
-3-4-1
```

### 输出

```
-3-4-1
```

## 样例 #3

### 输入

```
+10
```

### 输出

```
+10
```

# 题解

## 作者：Wan__Ye__Chu (赞：5)

## 题目大意

给定一个仅含有加减号和数字的表达式，让你在中间添加若干个加减号，使它值最大。

## 思路

很明显， 这是一道贪心 ，如果不知道怎么贪心， 那跟我来看几个小例子。
```cpp
1:114514-1919810
可以转化为：114514-1+919810
     

没看懂？没关系我们再来看一个：

2:1145+4514-1919+810-114514+1919810

可以转化为：1145+4514-1+919+810-1+14514+1919810

 ```
于是，就明确了我们的思路：**这道题只用添加加号，且是在减的数中间加减号。
然后连续的第一个数不是零的减数可以直接用一个加号搞定。**

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;

string a;
int sum,j;

int main()
{
	ios::sync_with_stdio(0);
	cin>>a;
	int len=a.size();
	for(int i=0;i<len;i++)
	{
		if(a[i]=='+')
			sum=0;
		if(a[i]=='-')
		{
			sum=1;
			cout<<"-";
			continue;
		}
		if(sum==1 && a[i-1]!='-')
		{
			cout<<"+";
			if(a[i+1]!='-' && a[i+1]!='+' && a[i]=='0')
			{
				cout<<a[i];
				continue;
			}	
			sum=0;
		}
		cout<<a[i];
	}
	return 0;
}

---

## 作者：David_yang (赞：2)

[传送门](https://www.luogu.com.cn/problem/P7052)

第七篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

（似乎不用再归纳了，题目已经讲得简洁明了了……）

## 算法：

贪心。

## 解析：

首先拿到题，相信很多人都知道，在式子里添加减号是没用的，这只会让它更小。随便举个栗子：$+875$，这个你随便怎么加减号都会让它变小。如果是 $-875$，将它变为 $-8-7-5$ 确实变大了，但还是没有 $-8+7+5$ 大。（当然你把一个数改成 $-0$ 也没有错）。

接下来要解决的就是每个数不能含前导 $0$。其他两个要求只需加几个判断条件就行了。这次举个李子：$-6000114514$，要让它最大是不是只能为 $-6+0+0+0+114514$？如果是 $-6100014514$ 呢？是不是可以为 $-6+100014514$？所以这里得出一个结论：如果负号后第二个数不为零，直接打印加号；否则把每个零之前都加上一个加号，当识别到不为零的那一位，就可以直接输出后面的了。

能讲的也就那么点，下面就贴代码了。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		cout<<s[i];
		if(s[i]=='-')
		{
			i++;
			cout<<s[i];
			i++;						//看它的负号后第二位
			if(s[i]!='+' && s[i]!='-')	//这里我被坑了一下，注意如果这一位是符号，那没法加加号
			{
				while(s[i]=='0')
				{
					printf("+");
					cout<<s[i];
					i++;
				}
				if(i<s.length() && s[i]!='+' && s[i]!='-')
				{
					printf("+");
					cout<<s[i];
				}
				if(s[i]=='+' || s[i]=='-')
				{
					i--;				//注意遇到符号要减回来
				}
			}
			else
			{
				i--;					//也要减回来
			}
		}
	}
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：mbzdf (赞：1)

# P7052 题解

[传送门](https://www.luogu.com.cn/problem/P7052)

## 题目大意
> 向一个仅含有加减号和数字的表达式中**添加**一些加号或减号，使得操作后的**合法**表达式的值**最大**~~（关于合法的解释自行看题）~~

## 分析一下
> ~~我教练曾说过：“当你在一道简单题中发现了求最值，那这题不是 **DP** 就是**贪心**。”~~

容易发现，这道题是一道贪心。
#### 那么具体怎么做呢

+ 这道题只用添加 `+`，因为在没有负数的表达式里，添加 `-` 不会使表达式的值增大。

+ 加一个数不用改，因为你在里面添加符号也是只会使表达式的值减小。

**例如**
>
>`+123456`
>
>在里面任意位置添加符号只会使这个值减小。

+ 减少一个数，在这个数只有一位的情况无法修改。

+ 减少一个数，在这个数有多位的情况下只需要在这个数的**第一位后**添加 `+`，将其分割为一减一加。

#### 综上，我们只需要在减少一个多位数时，在这个数的第一位后添加 `+`。
### 一个需要注意的事情

>每一个数字不含前导零。

在添加符号时，注意前导零，将多个连续的 `0` 修改为多个 `0` 相加 ~~（当然相减也可以）~~。

**例如**
>
>将 `12-90020` 修改为 `12-9+0+0+20`。

## AC 代码 ~~（抄题解的不是好孩子）~~
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string a;
bool t = 0;
int main()
{
	cin >> a;
	int len = a.size();
	for(int i = 0;i < len;++ i)
	{
		if(a[i] == '+')
		{
			t = 0;
		}
		if(a[i] == '-')
		{
			t = 1;
			cout << '-';
			continue;
		}
		if(t && a[i - 1] != '-')
		{
			cout << '+';
			if(a[i] == '0')
			{
				if(a[i + 1] != '-' && a[i + 1] != '+')
				{
					cout << a[i];
					continue;
				}
			}
			t = 0;
		}
		cout << a[i];
	}
	return 0;
}
```

---

## 作者：_Nancy_ (赞：1)

### [题目](https://www.luogu.com.cn/problem/P7052)


## 思路
要求表达式的值最大，改变加法运算中的数值显然会使值减小，所以只需要在运算减法添加加号即可。

需要注意的一点

如  
```
1+2-1100

```
操作后应表示为

```
1+2-1+100
```
而不是
```
1+2-1+1+0+0
```
注意处理前导零。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<string>
#include<stack>
#include<queue>
#include<set>
using namespace std;
#define MAXN 1010
#define R(x) x=read()
#define W(x) write(x)
#define int long long
#define INF 0x3f3f3f3f
inline int read()
{
	int x,y;
	char c=getchar();
	x=0,y=1;
	while(c<'0'||c>'9') {if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return x*y;
}
inline void write(int x)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
signed main()
{
	string s;
	cin>>s;
	int lens=s.size();
	for(int i=0;i<lens;i++)
	{
		if(s[i]=='-') 
		{
			cout<<s[i];
			i++;
			cout<<s[i];
			bool f=false;
			if(s[i+1]>='0'&&s[i+1]<='9') i++;
			else continue;
			while(s[i]>='0'&&s[i]<='9')
			{
				if(s[i]=='0')
				{
					if(!f) cout<<'+'<<s[i];
					else cout<<s[i];
				}
				else
				{
					if(!f) 
					{
						cout<<'+'<<s[i];
						f=true;
					}
					else cout<<s[i];
				}
				if(s[i+1]>='0'&&s[i+1]<='9') i++;
				else break;
			}
		}
		else cout<<s[i];
	}
	return 0;
}
```


---

## 作者：chatoudp (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7052)

题意：
	给定一个表达式，在里面添加一些加号或减号，让表达式合法且值最大。

让表达式值最大，就是让表达式加的多，减的少。而一个数在中间添加符号是无法让其变大的，所以遇到加法，后面的数只需正常输出。

减法后面的数中间一定是要加加法的，而加法插的位置一定是要尽量靠前的。如一个 $n$ 位数，$-$ $1$ 位数 $+$ $n-1$ 位数一定比 $-$ $2$ 位数 $+$ $n-2$ 位数 大。(第一个 $-$ 是减号，不是负号)

那前导零怎么办呢？

一些人可能会觉得在如果加加号会产生前导零，就不在那里加，再往后看哪里能加。

~~接下来按照这个思路写，就是令人愉快的 AC 时间了。~~
不，是令人伤心的 WA 时间，你会获得 WA on #4 的好成绩。

举个例子：

-10009

按上面的思路： -1000+9

正确答案： -1+0+0+0+9

所以遇到前导零也要加，前导零中间也加加号。

接下来才是真正的 AC 时间。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int main(){
	cin>>s;
	char ch;
	if(s[0]=='+'||s[0]=='-'){
		ch=s[0];
	} 
	else ch='+';
	string num="";
	for(int i=0;i<s.size();i++){
		if(s[i]=='+'||s[i]=='-'){
			if(ch=='-'&&i!=0){
				bool f=0;
				int id=-1;
				for(int i=0;i<num.size();i++)
				{
					printf("%c",num[i]);
					if(f==0&&i!=num.size()-1){
						id=i;
						f=1;
						printf("+");
					}else
						if(id==i-1&&i!=num.size()-1&&num[i]=='0'){
							printf("+");
							id++;
						}
					
				}
			}else
				cout<<num;
			num="";
			ch=s[i];
			printf("%c",s[i]);
		}else
			num=num+s[i];
	}
	if(ch=='-'){
		bool f=0;
		int id=-1;
		for(int i=0;i<num.size();i++)
		{
			printf("%c",num[i]);
			if(f==0&&i!=num.size()-1){
				id=i;
				f=1;
				printf("+");
			}else
				if(id==i-1&&i!=num.size()-1&&num[i]=='0'){
					printf("+");
					id++;
				}
					
		}
	}
	else cout<<num;
	num="";
	return 0;
}

```

---

## 作者：FarmarJohn (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P7052)
## 题目大意：
给定一个**仅含有加减号和数字的表达式**，让你在中间添加若干个加减号，使它值最大。
## 分析：
题目中有一个最重要的信息，那就是**让它值最大**。很明显，这题是个标准的贪心。

那有的小伙伴就要问了，**到底怎么贪呢？**

我们来举几个例子：

>`-114514`

如何让它变最大呢？很简单：

>`-1+14514`

再来一个：

>`10+20-30`

>`10+20-3+0`

看明白了吗？这道题只用添加加号，且是在减的数中间加减号。然后连续的第一个数不是零的减数可以直接用一个加号搞定。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int x=0;
    cin >> s;
    int l=s.size();
    for(int i=0;i<l;++i)
    {
        if(s[i]=='+')x=0;
        if(s[i]=='-')
        {
            x=1;
            putchar('-');
            continue;
        }
        if(x&&s[i-1]!='-')
        {
            putchar('+');
            if(s[i]=='0')
            {
                if(s[i+1]!='-'&&s[i+1]!='+')
                {
                    cout<<s[i];
                    continue;
                }
            }
            x=0;
        }
    	cout<<s[i];
    }
    return 0;
}
```


---

