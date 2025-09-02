# Simple Strings

## 题目描述

zscoder loves simple strings! A string $ t $ is called simple if every pair of adjacent characters are distinct. For example ab, aba, zscoder are simple whereas aa, add are not simple.

zscoder is given a string $ s $ . He wants to change a minimum number of characters so that the string $ s $ becomes simple. Help him with this task!

## 样例 #1

### 输入

```
aab
```

### 输出

```
bab
```

## 样例 #2

### 输入

```
caaab
```

### 输出

```
cabab
```

## 样例 #3

### 输入

```
zscoder
```

### 输出

```
zscoder
```

# 题解

## 作者：三点水一个各 (赞：7)

### 题目是我翻译的：

给定一个字符串t (t的长度<2*$10^{5}$)。每次可以将t中的任一字符改为另一字符（a~z），要求在最短的操作后，t任意两个相邻的字符互不相等。

***
我先讲一下样例

"aab"的开头两个就是相同的,如果简单的比较$t_{1}$和$t_{2}$,再将$t_{2}$修改成'b',会发现与$t_{3}$相等。

***
### 算法：

那么,我们只要将$t_{i}$改变成与$t_{i-1}$和$t_{i+1}$不相等的字符就可以了,因为`可能有多个答案，请输出任意一种`，修改后的字符一定`可以`是'a','b','c'中的一个,这种方法只需要比较$t_{i-1}$和$t_{i}$就可以了。

#### 我是用string类做的,s.length()获取了字符串的长度，但是它其实有第0位，所以从i=1开始

#### 注意j循环时不可以写int j，具体可以看代码。

题目很仁慈，只要输出任意一种。

***

~~还恳请诸位大佬多多支持这道黑题。~~
***
    #include<bits/stdc++.h>
    using namespace std;//交了两遍,后来发现这句忘写了
    string s;
    int j;
    int main()
    {
        getline(cin,s);  
        for(int i=1;i<=s.length();i++)//s[1]其实是t[2]
        {
            if(s[i]==s[i-1])
	        {
                for(j='a';j<='c';j++)//不可以写int j
		      if(j!=s[i-1]&&j!=s[i+1]) break;
                s[i]=j;
            }
        }
        cout<<s;
    }

---

## 作者：FatOldEight (赞：2)

[题目描述](https://www.luogu.com.cn/problem/CF665C)
# 分析
根据题意，我们只需要当 $t_i=t_{i+1}$ 或 $t_i=t_{i-1}$ 时改变 $t_i$ 的值，

因为只用**输出任意答案**，所以只需要备选三个字母进行修改即可。
# 代码
~~~ cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000005];
int n;
int main()
{
    scanf("%s",a+1);//输入
    n=strlen(a+1);
    for(int i=2;i<=n;i++)//注意要从2枚举到n
    {
        if(a[i]==a[i-1])//判断a[i]是否与a[i-1]相等
        {
            if('a'!=a[i-1]&&'a'!=a[i+1])a[i]='a';
            else if('b'!=a[i-1]&&'b'!=a[i+1])a[i]='b';
            else a[i]='c';//改变a[i]的值，我在这里选的是a、b、c
        }
    }
    printf("%s",a+1);//输出
    return 0;
}
~~~

---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意
给定一个字符串 $t$，你可以随意修改字符串中的字符，要求字符串中任意字符与左右两个字符互不相等。
## 思路
从左往右枚举字符，如果发现有字符与上一个字符相等，就枚举 $26$ 个字母，直到找到第一个与此字符左右字符互不相等字母即可；
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin >> s;
	for(int i = 1; i < s.size(); i++){ 
		if(s[i] == s[i - 1]){ // 如果与前一个字符相等
			char c;
			for(char a = 'a'; a <= 'z'; a++){ // 枚举 26 个字母
				if(a != s[i + 1] && a != s[i - 1]){ // 找到与前后字符都不相等的字母
					c = a;
					break; // 退出循环
				}
			}
			s[i] = c; // 替换为第一个符合条件的字母
		}
	}
	cout << s;
	return 0;
}
```

---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF665C)|[博客使用更佳](https://dguru.blog.luogu.org/)|[通过记录](https://www.luogu.com.cn/record/66367417)

# 题意

给出一个字符串，要求将相邻且相同的字符全部替换。

# 思路

此题是一道模拟题，我们可以从字符串的第一个下标开始遍历，判断是否与上一个字符相同，如果相同，枚举 26 个字母。

但是，这样的思路未必太敷衍了，注意题目，此题只要求输出任意一种答案，因此，我们可以利用 cstdlib 库里的 srand 函数和 rand 函数进行随机化替换，注意不要乱用，rand 很容易卡 waiting。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void do_noth()//一个不执行任何指令的函数，下面你们就知道为什么要定义这个函数了
{
	return;
}
int main()
{
	string s;
	cin>>s;
	srand(time(0));//初始化指针
	for(int i=1;i<s.length();i++)//注意是i=1不是i=0
	{
		if(s[i]==s[i-1])
		{
			for(char c='a';c<='z';c++)//没错，for中的循环变量可以定成char型
			{
				if(c!=s[i-1]&&c!=s[i+1])//与前后都不相等
				{
					s[i]=c;
					if(rand()%2==0)goto brk;//有一半的概率继续执行
				}
			}
		}
		brk:
		do_noth();//因为goto的标签后面必须有语句，所以我们可以用一个空语句占位
	}
	cout<<s;
	return 0;
} 
```

---

## 作者：Yi_Fan (赞：0)

# 题意：
给出一个字符串，其中的字符可以变为 $a 
 $ 至 $z$ 中的任意一个字符，要最后相邻的字符都不相等
 

------------
# 分析：

1.  首先看数据，$t$ 的长度 $<2*10^5$ 而只有 $26$ 种字符，所以优先采取暴力枚举
 
1. 从第 $2$ 位到最后一位看是否与前一位相同是就找一个与前后不相同的替换

------------
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//变量区 
string t;//字符串 
//主函数 
int main()
{
	cin>>t;
	for(int i = 1;i < t.length(); i ++){
		if(t[i] == t[i-1] )//如果前后两个相等就改变后一个 
		for(char j = 'a';j <= 'z'; j ++){//枚举，其中一定有答案 
			if(j != t[i-1] && j != t[i+1]){//判断是否可以取 
				t[i] = j;//替换 
				break;//跳出 
			}
		}
	}
	cout<<t;
 	return 0;
}
```


---

## 作者：KazamiHina (赞：0)

先找到相邻的两位，然后暴力从 $a$ 枚举到 $z$，如果都不相同，就把这位替换就好了$qwq$

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

string a;
int len;

int main(){
	cin>>a;len=a.size()-1;
	for(int i=1;i<=len;i++){
		if(a[i]==a[i-1]){//找相邻两位相同的
			for(char j='a';j<='z';j++){//枚举
				if(a[i-1]!=j && a[i+1]!=j){//都不相同
					a[i]=j;//替换
					break;
				}
			}
		}
	}
	cout<<a;//直接输出修改完的序列
	return 0;
}
```

$qwq$

---

