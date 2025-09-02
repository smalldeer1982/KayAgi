# Romaji

## 题目描述

Vitya has just started learning Berlanese language. It is known that Berlanese uses the Latin alphabet. Vowel letters are "a", "o", "u", "i", and "e". Other letters are consonant.

In Berlanese, there has to be a vowel after every consonant, but there can be any letter after any vowel. The only exception is a consonant "n"; after this letter, there can be any letter (not only a vowel) or there can be no letter at all. For example, the words "harakiri", "yupie", "man", and "nbo" are Berlanese while the words "horse", "king", "my", and "nz" are not.

Help Vitya find out if a word $ s $ is Berlanese.

## 说明/提示

In the first and second samples, a vowel goes after each consonant except "n", so the word is Berlanese.

In the third sample, the consonant "c" goes after the consonant "r", and the consonant "s" stands on the end, so the word is not Berlanese.

## 样例 #1

### 输入

```
sumimasen
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
ninja
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
codeforces
```

### 输出

```
NO
```

# 题解

## 作者：封禁用户 (赞：2)

## 前言

[题目传送门](https://www.luogu.com.cn/problem/CF1008A)

翻译可能有点误解。

它的意思是每个辅音后面都要跟着一个元音，如果那个辅音是 n 那么就不用执行这个规则，但是**如果一个辅音(不是 n )后面跟着一个 n**那么就是错误的。

## 分析

其实就是个模拟了，按照上面的要求。s 的长度也不超过 100 。

## 代码

Code :

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
string s1;//s1是读入的字符串。
//====================
bool check(char x)//判断它这个字符是不是元音。
{
	return x!='a' && x!='e' && x!='i' && x!='o' && x!='u';
}
//====================
int main()
{
	cin>>s1;//读入一个字符串。
	int len=s1.length();//判断它的长度。
	for (int i=0;i<len;i++)//然后再循环枚举，注意，cin 是从0开始读入的！
	{
		if (check(s1[i]) && check(s1[i+1]) && s1[i]!='n')//如果它自己不是元音也不是 n ，且后面的也不是元音。
		{
			printf("NO\n");//那么只要有一处是不行的那么就跳掉。
			exit(0);//这个和 return 0; 一样的功能。
		}
	}
	printf("YES\n");//如果都符合要求了，那么输出YES。
	return 0;
}
```

## 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏**

---

## 作者：goodlearndaydayup (赞：2)

这道题就是字符串的判断，感觉入门难度却被刷成普及-。
###### 直接把元音装进一个数组里面，然后根据题意判断一个字符串是不是除了'n'这个辅音后面总是跟着一个元音字母

## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[66666];
char ss[6]={'a','e','i','o','u'};//元音表
int pd(int i)//判断元音
{
	for(int j=0;j<5;j++)
	{
		if(ch[i]==ss[j]) return 1;
	}
	return 0;
}
int main()
{
    cin>>ch;
	int len=strlen(ch);//提取长度
    for(int i=0;i<len;i++)
    {
        if(!pd(i)&&!pd(i+1)&&ch[i]!='n') //判断
        {
		  cout<<"NO"<<endl;
		  return 0;
		}
    }
    cout<<"YES"<<endl;
    return 0;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 来自yyf的一句话题意：判断一个字符串是不是除了'n'这个辅音后面总是跟着一个元音字母
#include <iostream>
#include <string>

bool OK(char c) // 判断字母c是否为元音字母
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string Str;
    std::cin >> Str;

    // 继续默读来自yyf的一句话题意：判断一个字符串是不是除了'n'这个辅音后面总是跟着一个元音字母
    for (std::size_t i = 0; i < Str.size(); ++i)
    {
        if (OK(Str[i])) // 如果是元音字母，则不考虑
        {
            continue;
        }
        else if (Str[i] == 'n') // 如果是辅音字母但是是'n'，则不考虑
        {
            continue;
        }
        else if (i != Str.size() - 1 && OK(Str[i + 1])) // 否则需要在辅音后面跟一个元音字母
        {
            continue;
        }
        else   // 都不符合前面的条件则说明不是Berlanese
        {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    std::cout << "YES" << std::endl;

    return 0;
}
```

---

