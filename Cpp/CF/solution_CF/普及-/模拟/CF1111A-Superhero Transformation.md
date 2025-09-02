# Superhero Transformation

## 题目描述

We all know that a superhero can transform to certain other superheroes. But not all Superheroes can transform to any other superhero. A superhero with name $ s $ can transform to another superhero with name $ t $ if $ s $ can be made equal to $ t $ by changing any vowel in $ s $ to any other vowel and any consonant in $ s $ to any other consonant. Multiple changes can be made.

In this problem, we consider the letters 'a', 'e', 'i', 'o' and 'u' to be vowels and all the other letters to be consonants.

Given the names of two superheroes, determine if the superhero with name $ s $ can be transformed to the Superhero with name $ t $ .

## 说明/提示

In the first sample, since both 'a' and 'u' are vowels, it is possible to convert string $ s $ to $ t $ .

In the third sample, 'k' is a consonant, whereas 'a' is a vowel, so it is not possible to convert string $ s $ to $ t $ .

## 样例 #1

### 输入

```
a
u
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
abc
ukm
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
akm
ua
```

### 输出

```
No
```

# 题解

## 作者：si_zhong (赞：3)

这道题实际上作为题A还是挺水的。

接下来直接看代码吧！（注解标在代码里了。）

```cpp
#include <bits/stdc++.h>
using namespace std;

string a,b;
int changa,changb;
int main() {
	cin>>a;
	cin>>b;                  读入
	changa=a.length();       获取长度
	changb=b.length();
	if(changa!=changb) {
		printf("No");注意判长度是否相等，很多人没有这一步于是被hack了！！
		return 0;    不等的话直接结束。
	}
	for(int i=0; i<=changa-1; i++) {
		if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u') {
			if(b[i]=='a'||b[i]=='e'||b[i]=='i'||b[i]=='o'||b[i]=='u') {
				continue;
			} else {
				printf("No");这里就不多说了，简单的判断。
				return 0;          元音对元音
			}
		} else {
			if(b[i]=='a'||b[i]=='e'||b[i]=='i'||b[i]=='o'||b[i]=='u') {
				printf("No");这里就不多说了，简单的判断。
				return 0;          非元音对非元音
			} else {
				continue;
			}
		}
	}
	printf("Yes");  完美结束！
	return 0;
}
```

有问题的话私聊，我有空的话会立即给予答复。

望通过谢谢！

---

## 作者：wuwenjiong (赞：0)

## 题意：
给出两个字符串，问一个字符串可不可以转换成另一个字符串。字符转换规则：当两个字符同为元音，或同为辅音，就可以转换。
## 思路：
考虑无法转换的情况：
1. 两个字符串长度不同。
1. 同一个位置上，两个字符一个元音，一个辅音。

当不符合以上两种情况时，就是可以转换的。
```cpp
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;
bool x(char s){//判断元音辅音的函数
	if(s=='a'||s=='e'||s=='i'||s=='o'||s=='u')
		return 1;
	return 0;
}
int main()
{
    string a,b;
    int l1,l2,i;
    cin>>a>>b;//输入两个字符串
    l1=a.length();
    l2=b.length();//求两个字符串的长度
    if(l1!=l2){//第一种情况，若符合，输出No
    	putchar('N'),putchar('o');
    	return 0;
	}
	for(i=0;i<l1;i++)
		if(x(a[i])!=x(b[i])){//第二种情况，函数返回值不同，输出No
			putchar('N'),putchar('o');
			return 0; 
		}
	putchar('Y'),putchar('e'),putchar('s');//不符合那两种情况，输出Yes
    return 0;
}
```
谢谢！！！

---

## 作者：Cym10x (赞：0)

#### 题意复述
给定字符串 $s$ , $t$，试判断对于任意 $i$ ，$s$ 的第 $i$ 位字符与 $t$ 的第$i$位字符是否同为元音字母或同为辅音字母.
#### 算法解析
1. 输入字符串 $s$ , $t$；
2. 如果 $|s|\neq|t|$ ，则返回 `"No"` .**这一步非常重要，避免被Hack！**
3. 遍历字符串 $s$ 与 $t$ ：如果对于某一个 $i$ ，$s_i$ 与 $t_i$ 一个元音一个辅音，则返回 `"No"` 并停止遍历；
4. 遍历完成后，若无问题，返回 `"Yes"` 。
#### code
```cpp
#include<stdio.h>
#include<string.h>
#define judge(x) (x=='a'||x=='e'||x=='i'||x=='o'||x=='u')
//判断x是否为元音。是返回1，否返回0. 
char s[1010],t[1010];int l;
int main(int argc,char*argv[]){
	gets(s);
	gets(t);
	//使用gets获取输入，但并不提倡各位使用gets. 
	if(strlen(s)!=strlen(t)){
		//判断s,t位数是否相同 
		printf("No");
		return 0;
	}
	l=strlen(s);
	for(int i=0;i<l;i++){
		//遍历字符串 
		if(judge(s[i])!=judge(t[i])){
			//如果不同为元音或辅音，返回"No"
			printf("No");
			return 0;
		}
	}
	printf("Yes");
	//没有任何问题 
	return 0;
}
```

Solution By [Cym_cd10x](/user/354015)

---

## 作者：Eason_AC (赞：0)

## Content
有两个字符串 $s,t$。规定元音字母只能够变换成元音字母，辅音字母只能够变换成辅音字母。试问 $s$ 能否经过若干次变换得到 $t$。

**数据范围：$1\leqslant |s|,|t|\leqslant 1000$。**
## Solution
首先看 $|s|$ 是否等于 $|t|$，如果不是的话就不可能将 $s$ 变换成 $t$，毕竟你不可以增加字符或者删除字符。然后再一个位置对应判断是否都是元音字母或者是否都是辅音字母。一旦有位置出现了不满足上述两个条件的情况，那么 $s$ 也不可能变换成 $t$。遍历完之后如果还没出现不能满足题目要求的情况，那么 $s$ 就能够变成 $t$。
## Code
```cpp
string s, t;

int vowel(char ch) {
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
	cin >> s >> t;
	int lens = s.size(), lent = t.size();
	if(lens != lent)	return printf("No"), 0;
	_for(i, 0, lens - 1)
		if(!((vowel(s[i]) && vowel(t[i])) || (!vowel(s[i]) && !vowel(t[i]))))	return printf("No"), 0;
	return printf("Yes"), 0;	
	return 0;
}
```

---

## 作者：zoobidubi (赞：0)

这题分为3个步骤

1. 判断字符串长度是否一致，如果不一致的话，无论怎么换都无法一样,所以直接输出No，结束程序

2. 在循环里枚举一个个字符，如果不相等，并且一个是元音一个是辅音的话那么就直接输出No，结束程序（因为它经过转换不可能变成另外一个字符）

3. 最后输出Yes就完事儿了

## 注意这里的no是No，不是NO，yes是Yes，不是YES，输出的时候一定要注意！

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
bool yy(char ss)//判断是否为元音的函数
{
	if (ss == 'a' || ss == 'e' || ss == 'i' || ss == 'u' || ss == 'o') return true;//是的话就true
	return false;//不是的话就false
}
int main()
{
    cin >> s >> t;
    if (s.size() != t.size())//长度不同直接输出No结束
	{
		puts("No");
		return 0;
	} 
	for (int i = 0; i < s.size(); i ++)
	    if (s[i] != t[i] && (yy(s[i]) != yy(t[i])))
        //判断交换的条件是否满足
	    {
	    	puts("No");//输出No
	    	return 0;//结束
		}
	puts("Yes");//否则输出Yes
    return 0;
}

```


---

## 作者：HoshizoraZ (赞：0)

蒟蒻的思路：

1. 先比较长度，如果两个字符串长度不一样，那就不用修改

2. 再比较串 $s$ 和串 $t$ 同一位置的字母是否都是元音或辅音字母

有人会问，怎么比较第二点呢？

其实，你只需要开一个布尔数组（容量足够），把下标为 $'a','e','i','o','u'$ 的字母设为真，其它字母设为假

然后再比较比较时的异或值

如果异或值为 $1$，说明它们一个是元音字母，一个是辅音字母，所以输出 $No$

如果异或值为 $0$，那么这两位可以互相交换，继续比较下一位

如果都通过了，就输出 $Yes$

代码：
```
#include <iostream>
#include <cstdlib>
#include <cstring> 
#include <cstdio>
using namespace std;
char s[1010],t[1010];
bool v[128];			//只要下标够就行了
int main()
{
	gets(s);
	gets(t);
	if(strlen(s)!=strlen(t)) printf("No\n");	//先比较长度
	else
    {
		v['a'] = v['e'] = v['i'] = v['o'] = v['u'] = true;	//打一个元音字母表
		for(int i=0;i<strlen(t);i++)
        {
			if(v[s[i]]^v[t[i]]) //一个元音字母，一个辅音字母
            {	
				printf("No\n");
				exit(0);	//当场停止
			}
		}
		printf("Yes\n");	//没有停止代表正确
	}
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

方法很简单，首先长度不同的两个串不可能互相转换，其次如果是同一类型的字符就可以互相转换，一个个判断就行了
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e3 + 5, mod = 10007;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
bool isf[N];
char s[N], t[N];

int main(void)
{
    rg int lens = fast_IO::chread(s + 1), lent = fast_IO::chread(t + 1);
    isf['a'] = isf['e'] = isf['i'] = isf['u'] = isf['o'] = true;
    if (lens != lent) { puts("No"); return 0; }
    for (rg int i = 1; i <= lens; ++i)
        if (isf[s[i]] != isf[t[i]]) { puts("No"); return 0; }
    puts("Yes");
    return 0;
}

```

---

