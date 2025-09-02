# Lucky String

## 题目描述

Petya loves lucky numbers. We all know that lucky numbers are the positive integers whose decimal representations contain only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya recently learned to determine whether a string of lowercase Latin letters is lucky. For each individual letter all its positions in the string are written out in the increasing order. This results in $ 26 $ lists of numbers; some of them can be empty. A string is considered lucky if and only if in each list the absolute difference of any two adjacent numbers is a lucky number.

For example, let's consider string "zbcdzefdzc". The lists of positions of equal letters are:

- b: $ 2 $
- c: $ 3,10 $
- d: $ 4,8 $
- e: $ 6 $
- f: $ 7 $
- z: $ 1,5,9 $
- Lists of positions of letters a, g, h, ..., y are empty.

This string is lucky as all differences are lucky numbers. For letters z: $ 5-1=4 $ , $ 9-5=4 $ , for letters c: $ 10-3=7 $ , for letters d: $ 8-4=4 $ .

Note that if some letter occurs only once in a string, it doesn't influence the string's luckiness after building the lists of positions of equal letters. The string where all the letters are distinct is considered lucky.

Find the lexicographically minimal lucky string whose length equals $ n $ .

## 说明/提示

The lexical comparison of strings is performed by the < operator in modern programming languages. String $ a $ is lexicographically less than string $ b $ if exists such $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ .

## 样例 #1

### 输入

```
5
```

### 输出

```
abcda
```

## 样例 #2

### 输入

```
3
```

### 输出

```
abc
```

# 题解

## 作者：Andysun06 (赞：1)

## CF110B 题解
这题居然没有 Pascal 的题解，那我就写一篇吧。
### 题目翻译&做法分析：
给定一个数 $n$ 让你输出满足这三个条件的字符串：
- 整个字符串都由小写字母组成；
- 两个相同字母之间的距离为 4 或 7。
- 在满足以上条件的前提上，字符串尽量最小。

然后我们就可以开始找规律，首先，字典序是最小的，那不就是 $a$,$b$,$c$,$d$…… 等等，按顺序来。

接着，我们画出一个表格：

先把字典序最小的 $a$ 填进去（注意：两个相同字母之间的距离为 4 或 7。） 为了字典序最小，所以肯定是字典序越小的字母越往前。
 
| a | b | c | d | a | b | c | d | a | …… |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

照上面这样子填下去，发现有一个循环节 `a`+`bcda`+`bcda`+`bcda`+…… 那我们就可以开始写程序了。

### 完整代码：

- Pascal 代码：
```pas
var n,i:longint;
begin
    read(n); //输入
    for i:=0 to n-1 do //循环 n 次
        write(chr(97+i mod 4)); //刚刚找到的规律
end.
```

- C++ 代码：
```cpp
#include<iostream>
#include<cstdio>
int i,j,n,m;
int main(){
    scanf("%d",&n); //输入
    for(i=0;i<n;i++) //循环 n 次
        putchar(97+i%4); //刚刚找到的规律
}
```

提交结果显示，Pascal 的代码会比 C++ 慢 1~2 秒，但内存要更少。

希望本题解对大家有帮助，也感谢管理员在百忙之中帮助我审核题解，谢谢！


---

## 作者：ForeverHYX (赞：1)

# 题解005 CF110B
## 01 前置芝士 贪心

贪心是一种~~目光短浅~~的算法，即我们只关注局部最优解，因此可以使用贪心的题目必须保证局部最优解的正确性代表全局最优解的正确性。

## 02 本题思路

很显然为了让字典序最小我们只需要保证每次字母都是连续的，这个非常容易证明。然后我们应当每四个字节循环一次，如何证明这一正确性呢？

$a,b,c,d,e$ 和 $a,b,c,d,a$ 两种排序显然都是合法的，但是显然后者的字典序更加小，因此我们不严格的证明了上面这一结论。

而这道题的本质就是在一个 $abcdabcd...$ 的无限字符串中截取长度为 $n$ 的部分。

## 03 本体做法

### 我们采用局部打表和模拟的方法来截取出所需的字符串。

首先我们发现使用 $abcd$ , $abc$ , $ab$ , $a$ 这四个字符串就可以获取所有的字符串，我们只需要不断地将 $n/4$ ，不断输出 $abcd$ ，最后再根据余数输出剩余部分就好了。 

## 04 AC代码

```cpp
#include<string>
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int n;
string s[4]={"a","ab","abc","abcd"};//局部打表 
int main(){
     cin>>n;
     while(n>n%4){
         n-=4;
		 cout<<s[3]; //输出重复部分 
     }
     cout<<s[n-1];//处理余数部分，因为数组从0计数所以-1 
}
```
抄代码是没有意义哒，建议看完自己写。

 _本蒟蒻的第五篇题解，希望管理员大大通过，祝大家国庆，中秋快乐！！！_ 


---

## 作者：123456zmy (赞：1)

题意：  
输入 $n$，输出一长度为 $n$ 的满足以下条件的字符串：
* 由小写字母组成；
* 相邻两个相同字母之间的距离为 $4$ 或 $7$。
* 在满足以上条件时，字典序最小。
___
~~样例中都有提示的贪心。~~

尽可能选靠前的字母，于是~~显然~~答案会是这种形式：`abcdabcdabcdabcda...`，输出前 $n$ 个即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)putchar('a'+i%4);
	return 0;
}
```

---

## 作者：hswfwkj_ (赞：0)

大水题，分析题意可得，显然当相同字母的距离是 $4$ 时，构造出来的字符串才是最优解。同时，题目还要求字典序最小，那么，显然从 $a$ 开始构造，答案字典序最小。

简单打个表，我们可以发现：

| 1 | 2 | 3 |4 | 5 | 6 | 7 | 8 |······ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| a |b|c|d|a|b|c|d|······

显然，我们只需一直 $abcd$，$abcd$ 循环下去，这样就可以通过本题了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i=-~i)
		putchar('a'+(i&3));//i&3<=>i%4
	return 0;
}
```

---

## 作者：_tommysun_ (赞：0)

这是一道比较简单的字符串题。由于要使输出的字符串的字典序最小，所以相邻两个字母之间的距离越短越好。题目中的最短距离是4，所以每相隔4位就有一个重复的字母。

由于每四位都是重复的，就形成了一个周期为4，循环节是abcd的字符串。例如，当$n=8$时，输出的字符串便是```abcdabcdb```。最后模拟一下，输出即可。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n/4;i++) cout<<"abcd"; //算出周期数。 
	n%=4;
	for(int i=0;i<n;i++) cout<<char('a'+i); //输出不足以成为一个周期的字符。 
	return 0; 
}
```


---

