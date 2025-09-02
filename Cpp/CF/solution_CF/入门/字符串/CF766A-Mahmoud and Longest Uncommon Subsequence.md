# Mahmoud and Longest Uncommon Subsequence

## 题目描述

While Mahmoud and Ehab were practicing for IOI, they found a problem which name was Longest common subsequence. They solved it, and then Ehab challenged Mahmoud with another problem.

Given two strings $ a $ and $ b $ , find the length of their longest uncommon subsequence, which is the longest string that is a subsequence of one of them and not a subsequence of the other.

A subsequence of some string is a sequence of characters that appears in the same order in the string, The appearances don't have to be consecutive, for example, strings "ac", "bc", "abc" and "a" are subsequences of string "abc" while strings "abbc" and "acb" are not. The empty string is a subsequence of any string. Any string is a subsequence of itself.

## 说明/提示

In the first example: you can choose "defgh" from string $ b $ as it is the longest subsequence of string $ b $ that doesn't appear as a subsequence of string $ a $ .

## 样例 #1

### 输入

```
abcd
defgh
```

### 输出

```
5
```

## 样例 #2

### 输入

```
a
a
```

### 输出

```
-1
```

# 题解

## 作者：teacup (赞：11)

# CF766A Mahmoud and Longest Uncommon Subsequence  第三篇题解
### 其实这道题代码实现超级简单，只不过想法难想，容易想的太复杂，想太多。
思路大佬们都讲过了，就是只有当两个字符串完全相同时才输出“-1”，否则输出较长字符串的长度。

这篇题解的特点主要在于：
## 不用万能库！
代码来喽~~（注释版）
```cpp
#include<cstdio>
//scanf与printf要用
#include<cstring>
//strlen要用
using namespace std;
#define l (int)strlen/*本蒟蒻比较懒，不想打那么多遍
注意:(int)是必要的，没有会CE，本机编译都不通过，呵呵*/
char s1[100010],s2[100010];/*
不用string唯一麻烦点的地方就在这，注意数组大小
100010是可以的，最小可以开多少本蒟蒻不知道
各位神犇可以研究一下,tips:50010都不行*/
int main(){//主程序愉快地开始了
	scanf("%s%s",s1,s2);//读入
	if(!strcmp(s1,s2)) printf("-1");//不行的情况
	else printf("%d",l(s1)>l(s2)?l(s1):l(s2));
    //三目运算符的使用，相当于max函数
    return ~~(0-0);//愉快结束，卖个萌求通过
}
```
纯代码版来喽~~
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define l (int)strlen
char s1[50010],s2[50010];
int main(){
	scanf("%s%s",s1,s2);
	if(!strcmp(s1,s2)) printf("-1");
	else printf("%d",l(s1)>l(s2)?l(s1):l(s2));
    return ~~(0-0);
}
```
感谢您的观看，留下赞再走吧~~

---

## 作者：xujian (赞：4)

楼下那位大佬简直太强了，居然还手打了快读（好像不需要）。

首~~先，不得不说一下，这题理解了是真的水。~~

当蒟蒻看见“Uncommon Subsequence”这个东西的时候，还以为要找公共子序列。
### 可是这里说了“不是另一个字符串的子序列”，我们也可以理解为其中的一个串的子序列是否是另一个串的子序列。

### 显然，长的字符串永远不可能是短的字符串的子序列，于是我们可以得到那个所谓的“Uncommon Subsequence”其实就是长的字符串的长度。

于是，就只剩下了一种情况“Uncommon Subsequence”不存在，即两个字符串等长的时候，遇到这种情况输出-1就可以了。

## 所以结论：我们只要判断两个串是否等长，若等长输出-1，不等长输出两个串较长的串的长度就可以了。

蒟蒻的极简代码如下↓

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int main(){
	cin>>s1>>s2;
	if(s1==s2)puts("-1");
	else cout<<max(s1.size(),s2.size());
	return 0;
}
```

有误的地方欢迎指出，还有不懂的地方欢迎在这→评论哦~

---

## 作者：WRuperD (赞：2)

## 题意

题面说：

给你两个字符串，对于其中一个字符串的一个子序列，如果该子序列不是另一个字符串的子序列，定义该子序列为“Uncommon Subsequence”。

输入两行为两个字符串，输出一个数字为最长的“Uncommon Subsequence”的长度。如果不存在“Uncommon Subsequence”,输出-1。

说人话就是：

##### 输入两个字符串，如果 _完全相同_ ，就输出-1，否则输出较长的一个字符串的长度。


------------


## 正题

首先看英文版题目，有“string”这个字眼，证明这题要用string

然后，运用string库，得到两个字符串长度
```c
long long acnt = a.size(), bcnt = b.size();
```

最后，比较就行了。

## 完整代码

```c
#include<iostream>
#include<string>
using namespace std;
string a,b;//定义字符串
int main()
{
	
	cin>>a>>b;//输入
	long long acnt = a.size(), bcnt = b.size();//得到长度
	if(a == b)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<max(acnt,bcnt)<<endl;
	}//比较
	return 0;
}
```


---

## 作者：liuyifan (赞：2)

## 来普及一下C++常见字符模板
不需要[楼下](https://www.luogu.org/blog/Disjudge/solution-cf766a)这么复杂的写法,main内只要四行就能解决

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register将变量存在CPU缓存里面,更快
using namespace std;//在OI中建议都要加
char a[1000000],b[1000000];//char数组 
int main()
{
    scanf("%s%s",a,b);//输入字符数组a,b,注意不加& 
    if(!strcmp(a,b))puts("-1");//不是子串 
    //strcmp:判断两个字符串是否相等,相等返回0，不相等返回一个正数(目前暂未找到规律
    //扩展:strstr(a,b):判断b是否是a的字串
    //strcat(a,b):连接ab并储存在a中
	else printf("%d",max(strlen(a),strlen(b)));//较长的长度 
    //strlen:字符数组有效信息的长度,相当于string.length() or size()
    return 0;//结束 
}
```


---

## 作者：houyinuo (赞：1)

其实这题就是输出长度更长的串的长度，当两个串的长度相等时输出-1。

~~STL不香吗~~

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main (){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>a>>b;
	if (a==b) puts("-1");
	else printf ("%d",max(a.size(),b.size()));
    return 0;
}

```


---

## 作者：AdzearDisjudge (赞：1)

显然如果两个字符串相同则不存在“Uncommon Subsequence”，否则“Uncommon Subsequence”长度一定是较长的那个字符串的长度。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define per(i,a,n) for(register int i=a;i>=n;--i)
#define mem(a) memset(a,0,sizeof(a))
#define elif else if
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline ll read()
{
    ll f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-')
        f=-1;
    }
    while(ch<'0'||ch>'9');
    do
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*x;
}
string a,b;
int main()
{
	cin>>a>>b;
	if(a==b)
	{
		cout<<-1;
		return 0;
	}
	cout<<max(a.size(),b.size());
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：

> 给你两个字符串，对于其中一个字符串的一个子序列，如果该子序列不是另一个字符串的子序列，定义该子序列为“Uncommon Subsequence”。

> 输入两行为两个字符串，输出一个数字为最长的“Uncommon Subsequence”的长度。如果不存在“Uncommon Subsequence”,输出-1。

看懂了题意这题还是很水的。

如果两个字符串长度不相等，输出长度较大的字符串的长度，如果完全相同，输出“-1”。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	int l1=s1.size(),l2=s2.size();
	if (s1==s2)
	{
		cout<<"-1"<<endl;
	}
	else
	{
		cout<<max(l1,l2)<<endl;
	}
	return 0;
}
```

---

## 作者：江户川·乱步 (赞：0)



### 题目大意

   输入两行为两个字符串，输出一个数字为一个最长的长度的字符串。若相等,输出-1。
    
### 题目解法

   我们知道，C++有用来求长度的函数（好像有三个），分别是 `strlen`和`size` 还有`length`。
   
   比较大小可以用`max`函数，或者用`if`判断。

### 简洁的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main()
{
	cin>>a>>b;
	if(a==b) cout<<"-1";
	else cout<<max(a.size(),b.size());//取长度并且比较大小
	return 0;
}
```
附上一片[青青草原](https://www.luogu.com.cn/record/51080917)。


---

## 作者：juun07 (赞：0)

## 题意简述：

- 比较两个字符串

- 如果完全相同，输出“-1”

- 否则，输出较长字符串的长度



## 题目分析

要比较两个字符串

比较基础的有两种做法

1. 字符数组（char[]）
1. 字符串（string）

而这两种做法大同小异

都可以很方便的实现比较字符串

比如在字符数组内可以使用```strcmp()```函数来比较两个字符数组

而string数据类型就更简单了，直接用==即可

至于长度的求法，字符数组有```strlen()函数```，字符串有```size()```函数，自然也不必多说


## AC code（抄袭可耻，请注重个人诚信）：
### 字符数组做法

```cpp
#include<iostream>
#include<algorithm>	//max函数调用头文件
#include<cstring>	//strlen函数调用头文件
using namespace std;
char s1[50010],s2[50010];	//定义
int main()
{
	cin>>s1>>s2;
	int len=strlen(s1),len2=strlen(s2);	//求两个字符数组的长度
	if(!strcmp(s1,s2))	//如果两个字符数组相等则无解
	{
		cout<<"-1";
	}
	else			//如果不相等，就直接输出较长字符串的长度
	{
		cout<<max(len,len2);
	}
	return 0;	//好习惯
}

```

### string做法

```cpp
#include<iostream>
#include<algorithm>	//max函数需要调用的头文件
#include<string>	//string类型需要调用的头文件
using namespace std;
string s,s2;	//字符串的定义
int ans;	//最终答案
int main()
{
	cin>>s>>s2;
	if(s==s2)	//如果两字符串相等，那么肯定无解
	{
		cout<<"-1"<<endl;
	}
	else		//如果不相等，就直接输出较长字符串的长度
	{
		ans=max(s.size(),s2.size());	//size()函数求长度
		cout<<ans<<endl;
	}
	return 0;	//好习惯
}
```

## 完结撒花！

---

## 作者：sodak (赞：0)

## 思路
第一眼感觉像是DP？？(~~估计是傻了~~)，然后经过一翻~~仔细的推理~~不太仔细的口胡，就会发现，如果两个串完全相等，那么肯定无解，然后是不相等的情况，显然长的那个一定不是短的那个的子序列，所以输出两个中长度较长的就可以了

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register 
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
string s1,s2;
int main(){
	cin>>s1>>s2;
	if(s1==s2)puts("-1");
	else printf("%d\n",max(s1.length(),s2.length()));
}

```

---

