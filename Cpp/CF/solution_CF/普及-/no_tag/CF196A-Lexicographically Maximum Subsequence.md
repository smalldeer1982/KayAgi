# Lexicographically Maximum Subsequence

## 题目描述

你现在有一个只包含小写英文字母的字符串，要求求它的最大字典序子序列。

我们把一个非空字符串s[p_{1}p_{2}...\ p_{k}]=s_{p1}s_{p2}...\ s_{pk}(1<=p_{1}<p_{2}<...<p_{k}<=|s|)叫做字符串s=s1s2…s|s|的一个子序列。

如果|x|>|y|而且x1=y1,x2=y2…X|y|=Y|y|或者存在一个数字r (r<|x|,r<|y|)满足x1=y1,x2=y2…X|y|=Y|y|并且x_{r+1}>y_{r+1}，那么字符串x=x1x2…x|x|在字典序上比字符串y=y1y2…y|y|大。在行中的字符根据他们的ASCII码进行比较

## 说明/提示

让我们看一下样例并看一看待求的子序列长什么样子(用大写粗体字母标注）

样例1:a**B**a**BBA**

样例2:abb**C**b**CC**a**C**bb**CB**aa**BA**

## 样例 #1

### 输入

```
ababba
```

### 输出

```
bbba
```

## 样例 #2

### 输入

```
abbcbccacbbcbaaba
```

### 输出

```
cccccbba
```

# 题解

## 作者：lhjy666 (赞：2)

水题
只要从头开始取，取每个比后面所有数都大的数就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000005],b[1000005];
int main()
{
	scanf("%s",a);
	int l=strlen(a);
	for (int i=l-1;i>=0;i--)
	{
		b[i]=max(b[i+1],a[i]);
	}//b[i]表示b[i]位后面最大的数
	for (int i=0;i<=l-1;i++)
	{
		if(a[i]==b[i])
		{
			printf("%c",a[i]);
		}
	}
	return 0;
}
```

---

## 作者：精神小伙！ (赞：1)

## 思路

只需要不断取字典序最大的字符就可以了。

如何找字典序最大的字符：倒着查找，只要字符比后面所有的字符的字典序大或相等就做个记号，最后正着输出。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
string s;
int a[100010];
char maxx='0';
int main()
{
	cin>>s;
	for(int i=s.size()-1;i>=0;--i)
	{
		if(s[i]>=maxx) {maxx=s[i];a[i]=1;}
	}
	for(int i=0;i<s.size();++i)
	    if(a[i]==1) cout<<s[i];
	return 0;
}

```

---

## 作者：BlackPanda (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF196A)

------------
## 题目描述：
读入字符串，求该串的**最大字典序子序列**。

------------
## 我的思路：
循环判断**只要当前字符比后面所有的字符的字典序**大，就把这个字符存到另一个字符串中，最后和输入的字符串循环比较如果该字符和输入时的是相同的，就输出。

------------
## 注意：
因为比较字符串的字典序是要从第一个字符开始依次往后比较的，所以要想取到最大字典序子序列，就要倒着查找！

------------

## Code：
```cpp
#include <bits/stdc++.h>	//万能头文件 
using namespace std;
string st;
char t[100005];
int a[100005];
int main(){
	cin>>st;	//读入字符串
	int len=st.length();
	for(int i=len-1;i>=0;i--){
		t[i]=max(t[i+1],st[i]);	
	}
	for(int i=0;i<len;i++){
		if(t[i]==st[i])
			cout<<st[i];
	}
	return 0;
}

```


---

## 作者：Allanljx (赞：0)

## 题意
给你一个字符串，让你求字典序最大的字串。

## 思路
众所周知，字典序是从前往后比较的，所以，如果有一个字符的字典序比另一个字符小，那么就算他后面有无数个字符，字典序也要更小一些。所以要尽量取字典序更大的字符。取完最大的了，就要取比最大的小一的字符，以此类推。所以，当且仅当这个字符比所有后面的字符字典序都大时才能取。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool b[100001];//记录当前这位取不取
signed main()
{
	string a;
	char c='0';
	cin>>a;
	int l=a.length();
	for(int i=l-1;i>=0;i--)
	{
		c=max(c,a[i]);//当前这个字符后面所有字符中最大的字符
		if(a[i]>=c) b[i]=1;
	}
	for(int i=0;i<l;i++)
	{
		if(b[i]==1) cout<<a[i];
	}
    return 0;
}
```


---

## 作者：ModestCoder_ (赞：0)

最近脑子比较迟钝，恶评题还想了好一会儿

要是字典序最大，当然首字母要是整段字符串中最大的字符

那么我们找到这个最大的字符之后就要取出字符后面那串个字符串中最大的字符……

直到无法再取为止

所以一个字符要输出的充要条件是从这个字符开始的后缀最大字符就是本身

直接一个后缀和完事

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
char s[maxn], sum[maxn];

int main(){
	scanf("%s", s + 1) ;
	int n = strlen(s + 1);
	for (int i = n; i; --i) sum[i] = max(s[i], sum[i + 1]);
	for (int i = 1; i <= n; ++i) if (s[i] == sum[i]) putchar(s[i]);
	return 0;
}
```


---

## 作者：小水滴 (赞：0)

题目大意：给定一个仅含小写字符的字符串，求出其最大词典最大子序列。

在本题中，子序列的比较方式是这样的：

设两个字符串$s1(|s1|=x)$, $s2(|s2|=y)$

 如果满足 $s1k=s2k$   $(k=1..|y|)$ 而且$|x|>|y|$
 
 或者 $s1r=s2r$  $(r<|x|, r<|y|)$ 而且$s1(r+1)>s2(r+1)$
 
 那么$s1>s2$
 
 解题思路：与数字的比较不同，本题的比较方式的第一关键是字符大小，第二关键是长度，即先按位比较，如果无法判别再比较长度。
 
由此，我们可以想到，一定要将大的字符放在前面，即先将第一大字符全部选出来再在剩余的部分中选第二大，第二大选完再在剩余的部分中选第三大，以此类推，直到全部选完。

举个例子：样例$abbcbccacbbcbaaba$

先找出最大的字符是$c$，将$5$个$c$都找出来，剩下的是$baaba$，将$2$个$b$都找出来，剩下$a$，也选上。故最后的答案是$cccccbba$。

然而本题中字符串的长度$n<=10^5$，如果暴力枚举是要超时的，所以要使用动态规划。设$nxt[i][j]$表示字符串中，第$i$位以后的第一个$j$字符的位置，如果没有则为$-1$。字符是按照$ASCII$码顺序来排列的，$a$是$1$，$b$是$2$，以此类推。

初始化时，毫无疑问应该将$nxt[n-1][j]$全部赋值为$-1$。然后再从后往前循环，设当前循环到第$i$位，当前字符是$a[i]$，那么$nxt[i-1][a[i]]=i$, $nxt[i-1][j]=nxt[i][j]$，$j$是除了$a[i]$以外的所有字符。

这样，我们就预处理出了$nxt$数组。

设整个字符串中最大的字符为$maxx$，从第$0$位开始，不断将下一个$maxx$位置记入到答案数组中，直到该字符都已取走，此时再换第二大，重复以上的操作，直到循环的位置超出了$n-1$，或是枚举的字符到了$0$。

最后输出答案数组中的答案即可。

下面发上AC代码（思路已经很详细，不放注释了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100005];
int a[100005];
int nxt[100005][28],len,maxx;
int ans[100005],h;
int main()
{
    gets(s);
    len=strlen(s);
    for(int i=0;i<len;i++)
    {
        a[i]=s[i]-96;
        maxx=max(maxx,a[i]);
    }
    for(int i=1;i<=26;i++)
      nxt[len-1][i]=-1;
    for(int i=len-1;i>=0;i--)
    {
        nxt[i-1][a[i]]=i;
        for(int j=1;j<=26;j++)
          if(j!=a[i])
            nxt[i-1][j]=nxt[i][j];
    }
    int i;
    if(a[0]==maxx) i=0;
    else i=nxt[0][maxx];
    for(;i<len;)
    {
        ans[++h]=i;
        if(nxt[i][maxx]==-1)
        {
            while(maxx>=1 && nxt[i][maxx]==-1) maxx--;
        }
        if(maxx==0) break;
        i=nxt[i][maxx];
    }
    for(int i=1;i<=h;i++)
      printf("%c",a[ans[i]]+96);
    return 0; 
}
```

整体点评：有难度的一道题，必须先根据判定条件想出思路，再通过动态规划来实现，较为综合。


---

