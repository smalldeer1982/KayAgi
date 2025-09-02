# [ABC082B] Two Anagrams

## 题目描述

给定仅由小写英文字母组成的字符串 $s$ 和 $t$。你可以任意重排 $s$ 的字符，得到字符串 $s'$；也可以任意重排 $t$ 的字符，得到字符串 $t'$。请判断是否存在一种重排方式，使得 $s'$ 在字典序上严格小于 $t'$。

## 说明/提示

## 注释

对于长度为 $N$ 的字符串 $a = a_1 a_2 \ldots a_N$ 和长度为 $M$ 的字符串 $b = b_1 b_2 \ldots b_M$，$a < b$ 在字典序上成立，当且仅当满足以下两个条件之一：

- $N < M$ 且 $a_1 = b_1, a_2 = b_2, \ldots, a_N = b_N$。
- 存在某个 $i$（$1 \leq i \leq N, M$），使得 $a_1 = b_1, a_2 = b_2, \ldots, a_{i-1} = b_{i-1}$ 且 $a_i < b_i$。其中字符之间按字母顺序比较。

例如，`xy` $<$ `xya`，`atcoder` $<$ `atlas`。

## 数据范围

- $s$、$t$ 的长度均为 $1$ 到 $100$ 之间。
- $s$、$t$ 仅由小写英文字母组成。

## 样例解释 1

例如，将 `yx` 重排为 `xy`，将 `axy` 重排为 `yxa`，则有 `xy` $<$ `yxa`。

## 样例解释 2

例如，将 `ratcode` 重排为 `acdeort`，将 `atlas` 重排为 `tslaa`，则有 `acdeort` $<$ `tslaa`。

## 样例解释 3

无论如何重排 `cd` 和 `abc`，都无法满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
yx
axy```

### 输出

```
Yes```

## 样例 #2

### 输入

```
ratcode
atlas```

### 输出

```
Yes```

## 样例 #3

### 输入

```
cd
abc```

### 输出

```
No```

## 样例 #4

### 输入

```
w
ww```

### 输出

```
Yes```

## 样例 #5

### 输入

```
zzz
zzz```

### 输出

```
No```

# 题解

## 作者：Swire (赞：3)

这道题的贪心思路很简单

既然要判断能否使s比t的字典序小

那么就把s按照字典序从小到大排序 t从大到小排序

然后比较输出即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e2+7;
char s[MAXN],t[MAXN];//这里我使用的是字符数组 用string应该更方便
bool cmp(char x,char y){
	return x>y;
}
int main(void){
	gets(s);//使用gets可以读入空格
	gets(t);
	int lens=strlen(s);//计算长度
	int lent=strlen(t);
	sort(s,s+lens);
	sort(t,t+lent,cmp);
	for(int i=0;i<max(lens,lent);i++){
		if(s[i]<t[i]){
			cout<<"Yes"<<endl;//如果中途可以判断就直接输出
			return 0;
		}
		else if(s[i]>t[i]){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;//注意 如果到最后还没出答案，那么两个字符串肯定相等，不能满足s<t，输出No
	return 0;
}
```



---

## 作者：☆木辛土申☆ (赞：2)

前面几楼都说的很清楚了，只要分别将两个字符串排序然后比大小即可，c++中是自带有比较函数的，但这里比较函数也可以用[lambda表达式写](https://zh.cppreference.com/w/cpp/language/lambda)(c++11)警告！

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>

int main(){
	std::string a,b;std::cin>>a>>b;
	std::sort(a.begin(),a.end(),[](const char &a,const char &b){return a<b;});
	std::sort(b.begin(),b.end(),[](const char &a,const char &b){return a>b;});
	printf("%s\n",a<b?"Yes":"No");return 0;
}
```
这只是lambda表达式的简单应用，虽然竞赛并不支持c++11，但在写一般程序和题目时在合适的时候使用可以提高不少效率。

---

## 作者：RioBlu (赞：2)

不要抢了，目前来说的最短代码
___
思路：a,b排序即可

但b要是字典序最大

a要是字典序最小
```c++
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main()
{
	cin>>a>>b;//输入a,b
	sort(b.begin(),b.end());//b字典序变为最小
	reverse(b.begin(),b.end());//翻转一下变为字典序最大
	sort(a.begin(),a.end());//a字典序变为最小
	if(b>a)
		puts("Yes");//可以
	else puts("No");//不行
}
```

---

## 作者：ShineEternal (赞：2)

# 灌水区

我的代码比楼下的要简单一些。。。

------------
# 算法区
此题因为是任意排序，所以我们要让s串从小到大，t串从大到小，而在实现程序时，可以两个串皆从小到大，然后t串从后往前比，s串从前往后比。


------------


# 代码区
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;//这一句话必须有
char s1[101],s2[101];
int main()
{
	gets(s1);
	gets(s2);
	int n=strlen(s1);
	int m=strlen(s2); //先记录下来两个串的长度，避免重复计算
	sort(s1,s1+n);
	sort(s2,s2+m);//对两个串进行排序
	for(int i=0;i<fmax(n,m);i++)//这里要循环到最大值，因为有空格，空格<小写字母
	{
		if(s1[i]<s2[m-i-1])//如算法区所示
		{
			printf("Yes\n");
			return 0;
		}
		if(s1[i]>s2[m-i-1])//一个不符，直接跳出
			break;
	}
	printf("No\n");//不是yes就是no
	return 0;
} 
```


------------
# 祈祷区
求过，求赞

---

## 作者：zhanghengrui (赞：1)

~~竟然没人用`std::string`，那我就水一发~~

思路跟楼上的一样，都是贪心，第一个字符串从小到大排，第二个从大到小排，然后直接比较

```cpp
#include<iostream>
#include<string>
#include<algorithm>
std::string str1,str2;
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::getline(std::cin,str1);
	std::getline(std::cin,str2);
	std::sort(str1.begin(),str1.end());//sort默认就是从小到大排
	std::sort(str2.begin(),str2.end(),std::greater<char>());//从大到小排
	std::cout<<(str1<str2?"Yes\n":"No\n");
	return 0;
}
```


~~这种题应该不会有人抄代码吧~~

---

## 作者：agicy (赞：0)

# 题意
给两个字符串$s,t$，每个字符串中字符的位置**可以自由改变**，问是否存在一种排列使$s$的字典序小于$t$的字典序。

# 思路

显然是运用**贪心**的思想，$s$从小往大排，$t$从大往小排，再进行比较。

# 代码

代码很简单，如下。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using std::sort;
//头文件
#define min(a,b) ((a) < (b) ? (a) : (b))//宏定义


char s1[128],s2[128];
int s1len,s2len;

bool judge(void);//比较函数
bool cmp1(char,char);
bool cmp2(char,char);

int main(void){
    scanf("%s",s1);//读入
    scanf("%s",s2);//读入
    s1len=strlen(s1);//获取长度
    s2len=strlen(s2);//获取长度
    sort(s1,s1+s1len,cmp1);//从小往大
    sort(s2,s2+s2len,cmp2);//从d大往小
    if(judge())
		puts("Yes");//用puts()输出后自动换行
    else
		puts("No");//用puts()输出后自动换行
    return 0;//结束
}

bool judge(void){
    int minlen=min(s1len,s2len);
    for(int i=0;i<minlen;i++)
        if(s1[i]<s2[i])
            return true;
        else if(s1[i]==s2[i])
        	continue;
        else
			return false;
    if(s1len<s2len)
    	return true;
    else
		return false;
}

bool cmp1(char a,char b){
    return a<b;
}

bool cmp2(char a,char b){
    return a>b;
}
```

---

