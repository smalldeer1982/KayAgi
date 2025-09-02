# International Olympiad

## 题目描述

International Abbreviation Olympiad takes place annually starting from 1989. Each year the competition receives an abbreviation of form IAO'y, where $ y $ stands for some number of consequent last digits of the current year. Organizers always pick an abbreviation with non-empty string $ y $ that has never been used before. Among all such valid abbreviations they choose the shortest one and announce it to be the abbreviation of this year's competition.

For example, the first three Olympiads (years 1989, 1990 and 1991, respectively) received the abbreviations IAO'9, IAO'0 and IAO'1, while the competition in 2015 received an abbreviation IAO'15, as IAO'5 has been already used in 1995.

You are given a list of abbreviations. For each of them determine the year it stands for.

## 样例 #1

### 输入

```
5
IAO'15
IAO'2015
IAO'1
IAO'9
IAO'0
```

### 输出

```
2015
12015
1991
1989
1990
```

## 样例 #2

### 输入

```
4
IAO'9
IAO'99
IAO'999
IAO'9999
```

### 输出

```
1989
1999
2999
9999
```

# 题解

## 作者：rui_er (赞：4)

题意简述：IAO 比赛从 $1989$ 年开始举办，每一年都有一个数字缩写。前面的年份用过的缩写在后面不能再用，每次的缩写的长度尽量短。问一些缩写是哪些年份的缩写。

---

思路：

我的思路与 CF 官方题解的思路差不多，获取完数字后，每次加上最小的满足缩写的 $10$ 的整数次幂（根据数字长度计算），直到与缩写匹配成功。

于是便有了第一份代码的读入和获取长度部分：

```cpp
while(getchar() != '\'');
scanf("%d", &n);
int _ = n, len = 0;
while(_) ++len, _ /= 10;
```

自豪的说：我想到了一个别人都没想到的方法！（滑稽）

然后就成功的 Wrong Answer On Test 4 了……

只好重看代码，仔细检查了一下其他地方都没有错误，最大的可能就是输入这里错了。然后增加一处调试，把 $len$ 的值输出出来，发现遇到 $0$ 就可能出问题。对照了一下其他题解，最终找到了一个坑点——**考虑前导零**！

前导零也会影响缩写，但是按照我的方法，会直接将前导零忽略，给出小得多的答案。

于是尝试将输入部分改为：

```cpp
while(getchar() != '\'');
scanf("%s", s);
n = atoi(s);
int _ = 0, len = strlen(s);
```

自测正确，提交 Accepted。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T, n; 
char s[11];

int main() {
	scanf("%d", &T);
	while(T--) {
		while(getchar() != '\'');
		scanf("%s", s);
		n = atoi(s);
		int _ = 0, len = strlen(s);
		int _10 = 1;
		for(int i=1;i<len;i++) _ += (_10 *= 10);
		_10 *= 10;
		while(n < 1989 + _) n += _10;
		printf("%d\n", n);
	}
	return 0;
}
```

---

## 作者：Citnaris (赞：0)

# $\text{International Olympiad}$

**题意**

给定一个形式为 $\texttt{IAO'}x$ 的缩写，让你找出一个最小的数 $n$ ，满足 $x$ 是 $n$ 的后缀并且 $x$ 的所有后缀所对应的数均不是 $n$ 。**所有 $n$ 都要大于等于 $1989$** 。

**分析**

我们可以由递推的思路来解决这道题，每次先找到 $x$ 长度 为 $i$ 的一个后缀所代表的值，然后找到最小的后缀为 $x$ 的 $i+1$ 位后缀的数，该值即为 $i+1$ 位的答案。

例如样例中的 $\texttt{IAO'}2015$ ，我们有以下步骤：

* $199\color{Red}5\color{Black}>1989, ans(\color{Blue}5\color{Black})=1995$

* $20\color{Red}15\color{Black}>1995, ans(\color{Blue}15\color{Black})=2015$

* $3\color{Red}015\color{Black}>2015, ans(\color{Blue}015\color{Black})=3015$

* $1\color{Red}2015\color{Black}>3015, ans(\color{Blue}2015\color{Black})=12015$

所以最终答案为 $12015$ 。

**代码**

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int NR = 15;
const int P[NR] = {(int)1, (int)1e1, (int)1e2, (int)1e3, (int)1e4, (int)1e5, (int)1e6, (int)1e7, (int)1e8, (int)1e9, (int)1e10}; // 预处理 10 的幂次方
int T, len, cur, suf;
char a[NR];

int find(int gt, int sfi, int sz) // 查找 i + 1 位最小值 
{
	if (gt % P[sz] < sfi)
	    return gt - (gt % P[sz]) + sfi;
	else
	    return gt - (gt % P[sz]) + sfi + P[sz];
}

void solve()
{
	scanf("\nIAO'%s", a + 1); // 用 scanf 读入
	len = strlen(a + 1), suf = 0, cur = 1988; // 注意 cur 不是 1989 而是 1988
	for (int i = len; i >= 1; --i) // 递推
	    suf = suf + P[len - i] * (a[i] - '0'), cur = find(cur, suf, len - i + 1);
	printf("%d\n", cur);
	return;
}

int main(int argc, char *argv[])
{
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：三点水一个各 (赞：0)

### 思路：

如果不是~~恶心的~~1989，我才不会去~~打表~~。

因为这题有1989的存在，所以每进一位都要特判。

方法不难，但是有点麻烦。


```
#include<algorithm>
#include<iostream>
#include<cstring> 
#include<cstdio>
using namespace std;
int n;
string x;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		cin>> x;
		x=x.substr(4);  //把IAO'删掉，也可以通过x.erase来实现 
		if(x.length()==1)
		{
			if (x[0]>='0'&&x[0]<='8') cout<<"199"+x<<endl;
			else cout<<"1989"<<endl;      //特判1989，后面也是如此。 
		}
		else if(x.length()==2)
		{	
			if(x=="99") cout<<"1999"<<endl;
			else cout<<"20"+x<<endl;
		}
		else if(x.length()==3)
		{
			if (x>="000"&&x<="098") cout<<"3"+x<<endl;
			else cout<<"2"+x<<endl;
		}
		else if (x.length()==4)
		{
			if (x>="3099"&&x<="9999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
		}
		else if (x.length()==5)
		{
			if (x>="13099"&&x<="99999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
	   }
		else if (x.length()==6)
		{
			if (x>="113099"&&x<="999999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
		}
		else if (x.length()==7)
		{
			if (x>="1113099"&&x<="9999999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
		}
		else if (x.length()==8)
		{
			if (x>="11113099"&&x<="99999999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
		}
		else if (x.length()==9)
		{
			if (x>="111113099"&&x<="999999999") cout<<x<<endl;
			else cout<<"1"+x<<endl;
		}
	}
	return 0;
}
```

---

