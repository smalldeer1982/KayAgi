# Letter

## 题目描述

### 题面描述

Vasya 决定利用报纸上的一段文字写一封匿名信。他可以从报纸上剪下一段文字（或字母），把他们粘贴到匿名信上去。已经剪下的文字不可重复使用。当然，匿名信中的空格不需要剪——他只要在空格处作出标记即可。现在，他知道报纸上的文字 $s1$ 和他即将写下的匿名信的内容 $s2$，请你帮他看看，他能否完成匿名信的书写。

## 样例 #1

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
where is your dog
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
Your dog is upstears
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
Instead of dogging your footsteps it disappears but you dont notice anything
Your dog is upstears
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
abcdefg hijk
k j i h g f e d c b a
```

### 输出

```
YES
```

# 题解

## 作者：agicy (赞：3)

# 思路

可以用一个数组来记录每个字符出现的次数，其中空格字符出现的次数可以设定为一个极大值，例如`1<<8`，即$256$，我们只需每次检查在目标字符串中每一个字符出现的次数是否小于等于数组中对应的值即可。

# 代码

代码如下。

```cpp
#include<stdio.h>

char str[256];//字符串
int a[256];//桶

int main(void){
	register int i;
	gets(str);
	for(i=0;str[i];i++)
		a[str[i]]++;//统计次数
	a[' ']+=256;//极大值
	gets(str);
	for(i=0;str[i];i++)
		if(--a[str[i]]<0)
			return puts("NO"),0;//出现次数多于对应值，输出NO
	puts("YES");//均小于等于对应元素，输出YES
	return 0;
}
```

## [我的评测记录](https://www.luogu.org/record/show?rid=9697204)

---

## 作者：TRZ_2007 (赞：0)

把各位大佬的题解翻了一遍，发现了一个共同点：都没有用上$map$！  
这道题目，就是用桶来储存啊，由于储存的是字符，用普通数组空间~~会爆~~太耗，这时就体会出$map$的魅力了。  
```
#include <stdio.h>
#include <string.h>
#include <map>//STL的map库
using namespace std;
map<char,int> book1,book2,book3,book4;//分别存储4类字符出现的个数
int main()
{
	char a[10001],b[10001];//不知道有多长，定义大一点总不是坏事
	gets(a);//读入
	gets(b);
	for(register int i=0;i<strlen(a);i++)//查找a的大写和小写字母
	{
		if(a[i]>='a'&&a[i]<='z')//如果的小写
			book1[a[i]]++;//该字母个数++
		if(a[i]>='A'&&a[i]<='Z')//如果是大写
			book3[a[i]]++;//该字母个数++
	}
	for(register int i=0;i<strlen(b);i++)//同上查找b
	{
		if(b[i]>='a'&&b[i]<='z')
			book2[b[i]]++;
		if(b[i]>='A'&&b[i]<='Z')
			book4[b[i]]++;
	}
	for(register char i='a';i<='z';i++)//从a到z循环查找小写字母出现的个数
		if(book1[i]<book2[i])//如果需要的大于现有的
		{
			 printf("NO\n");//肯定不行
			 return 0; 
		}
	for(register char i='A';i<='Z';i++)//同上查找大写字母
		if(book3[i]<book4[i])
		{
			printf("NO\n");
			return 0;
		}
	printf("YES\n");//都没有差错就输出YES
}
```

---

## 作者：Victory_Defeat (赞：0)

这道题乍一看上去好像很吓人，**但是**只是一道简单的模拟而已啦……

思路如下：

1. 统计两个字符串中**每个字母**出现个数**（注意：区分大小写）**

2. 判断是否有**第二个字符串中某一字母多**的情况。

3. 根据题意输出，若**有，则输出NO**，**否则，输出YES**。

简直是**So easy**有木有？**很水很水**啊

废话不多说，直接上代码：**（自行观察注释）**
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s1[205],s2[205];
int sum1[30],sum2[30],len1,len2,sum3[30],sum4[30];
//sum1,sum3分别表示字符串1中大小写字母个数，sum2,sum4同理
int main()
{
    gets(s1);
    gets(s2);
    //注意此处输入要用gets
    len1=strlen(s1);
    len2=strlen(s2);//记录s1,s2长度
    for(int i=0;i<len1;++i)
    {
        if(s1[i]>='a'&&s1[i]<='z')++sum3[s1[i]-'a'+1];
        else ++sum1[s1[i]-'A'+1];
    }
    for(int i=0;i<len2;++i)
    {
        if(s2[i]>='a'&&s2[i]<='z')++sum4[s2[i]-'a'+1];
        else ++sum2[s2[i]-'A'+1];
    }
    //第1步，统计字母个数
    for(int i=1;i<=26;++i)
        if(sum1[i]<sum2[i]||sum3[i]<sum4[i])
        {
            printf("NO");
            return 0;
    //第2,3步，判断并输出
    printf("YES");
}

```

---

## 作者：Lithium_Chestnut (赞：0)

纸老虎题，刚拿到题看题面，应该不太好写；但写完发现好简单，判断模拟就可以了，这里的 $a$ 和 $b$ 分别代表 $s1$ 和 $s2$。

大概思路：每次枚举 $b_i$，**判断 $b_i$ 是不是空格**。如果 $a$ 串里有 $b_i$，就删除 $a$ 串里那个的 $b_i$ 字符并枚举下一位，如果没有，则直接输出`NO`并返回 $0$；就这样一直枚举下去，如果枚举完所有的了，说明 $a$ 串空了，符合要求。此时循环已经结束，直接输出`YES`，返回 $0$。

好了，思路讲完了，讲讲涉及到的知识点与坑点：

$1.getline$

$getline$ 是一种可以读入**一整行**的函数，可以读入空格以后的东西（包括空格），**并且这东东只能读字符串**，想读其他的一整行，推荐使用 $gets$。$getline$ 用法：
```cpp
getline(cin,a);
getline(cin,b);
```

$2.length$

$length$ 是一个求`string`类型字符串长度的函数，与 $size$ 函数类似。$length$ 用法：
```cpp
int len=a.length();
```

$3.find$

$find$ 正如他的名字，这是一个寻找函数，直接查询$a$ 串里有没有 $b_i$，如果有，返回 $b_i$ 的位置，否则返回 $-1$。

$4.erase$

$a.erase(b,c)$ 就是从 $a$ 字符串的第 $b$ 位置开始，删除 $c$ 个字符。

好了，挂代码了，前面解释差不多了，先不放注释了。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int pd;
int main()
{
    getline(cin,a);
    getline(cin,b);
    for(int i=0;i<b.length();i++)
	{
	    if(b[i]!=' ')
	    {
	    	pd=a.find(b[i]);
		    if(pd=="-1")
			{
		        cout<<"NO";
		        return 0;
		    }
		    else a.erase(pd,1);
		}
		else continue;
    }
    cout<<"YES";
    return 0;
}
```

---

