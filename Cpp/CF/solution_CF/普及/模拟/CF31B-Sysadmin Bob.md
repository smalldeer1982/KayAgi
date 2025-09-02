# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 样例 #1

### 输入

```
a@aa@a
```

### 输出

```
a@a,a@a
```

## 样例 #2

### 输入

```
a@a@a
```

### 输出

```
No solution
```

## 样例 #3

### 输入

```
@aa@a
```

### 输出

```
No solution
```

# 题解

## 作者：zheysq_147 (赞：12)



刚看到这个题的时候，感觉是一道~~究极大水题~~，然后做题的时候发现要注意的细节很多，导致我3遍才AC，~~还是菜啊~~。


   
好，重点来了，这一道模拟题，我们如何去防坑？


$first$，需要把题目看懂。这道题概括来说，就是输入一个字符串，然后分成一些$A@B$形式的子串，如果无法做到，输出$No$ $solution$，如果能做到，输出任意一种即可。



$second$，找关键。这道题的关键在于这个字符：$@$.我们来梳理一下这个字符的用处。

我们可以定义一个集合，这个集合分为2部分，第一部分为不含$@$的字符串，第二部分为含$@$的字符串，可以选择分类讨论。

①，如果整个字符串没有这个字符，也就是说无法构成任意一个$A@B$形式的子串，那肯定要输出$No$ $solution$了。

②，如果这个字符串有这个字符，我们依旧需要去判断能不能做到把这个字符串分成一些$A@B$形式的子串，但是就比较easy了，几乎不用特判。

可以在纸上画一个图，我们考虑一下，如果有$@C@$或者$@@$这种情况,一定是不对的,所以输出$No$ $solution$.

然后,给出一个判断的code

```cpp
bool pd()
{
	for(i=2;i<=n-1;++i)
	{
		if(s[i]=='@'&&s[i+1]=='@')
		return 0;
	}
	for(i=2;i<=n-2;++i)
	{
		if(s[i]=='@'&&s[i+2]=='@')
		return 0;
	}
	return 1;
}
```

但是,这是不对的,因为我们少判了一种情况,如果是$s[1]$或者
$s[n]$=$@$,也是不对的,所以,可以加一句判断。

```
if(s[1]=='@'||s[n]=='@')
return 0;
```
判断的完整$code$就是这样的（第一种情况在输入中特判）:

```cpp
bool pd()
{
	if(s[1]=='@'||s[n]=='@')
	return 0;
	for(i=2;i<=n-1;++i)
	{
		if(s[i]=='@'&&s[i+1]=='@')
		return 0;
	}
	for(i=2;i<=n-2;++i)
	{
		if(s[i]=='@'&&s[i+2]=='@')
		return 0;
	}
	return 1;
}
```

接下来$third$,我们要关注输出部分的细节。一个程序，如果输出有问题，即使方法写的再好，也依旧是全WA，所以输出是重点！！！

题目要求输出任意一种可行的办法，我们可以这样想，假设一个字符串为$kkk@sc@03$，要求任意一种办法，可以把子串的倒数第二个字符做成$@$，这样就一定能保证方法可行。

如果不理解意思，请看下面

```
kkk@sc@03
    .
    .
.   .   .
  . . .
    .
kkk@s,c@03

Fz@zzzz@zzzz@zz@zzz
    .
    .
.   .   .
  . . .
    .
Fz@z,zzz@z,zzz@z,z@zzz
```
这里上code

```
void out()
{
        for(i=1;i<=n;++i)
	{
		if(s[i-2]=='@')
		printf(",");
		printf("%c",s[i]);
	}
}
```
然后发现还是错了。forth，自己出样例，找问题。于是，我就找到了这样一个样例

$kkk@sc@03$ 

我们预想它变成$kkk@s,c@03$

可是，它却变成了$kkk@s,c@0,3$ 

发现问题，最后一个被单独分开了。所以怎么办？我们可以在输入的地方去预处理，找到最后一个$@$的下标$last$，然后在判断$@$的那一句加上$last!=i-2$，这样我们正好可以在判断的地方写上:
```
if(last==-1)
return 0;//last初始值为-1
```
所以正确的判断code：

```cpp
bool pd()
{
	if(s[1]=='@'||s[n]=='@'||last==-1)
	return 0;
	for(i=2;i<=n-1;++i)
	{
		if(s[i]=='@'&&s[i+1]=='@')
		return 0;
	}
	for(i=2;i<=n-2;++i)
	{
		if(s[i]=='@'&&s[i+2]=='@')
		return 0;
	}
	return 1;
}
```


在输出的函数中，既然存在$i-2$，所以i从3开始就行了，$i<3$无意义。

正确的输出code：

```
void out()
{
	for(i=1;i<=n;++i)
	{
		if(s[i-2]=='@'&&i-2!=last)
		printf(",");
		printf("%c",s[i]);
	}
}
```


万事俱备，只差AC！上code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 201
char s[N];
int i,n,last=-1;
void in()
{
	scanf("%s",s);
	n=strlen(s);
	for(i=n;i>=1;--i)
	{
		s[i]=s[i-1];
		if(s[i]=='@'&&last==-1)
		last=i;
	}
	s[0]=48;
}
bool pd()
{
	if(s[1]=='@'||s[n]=='@'||last==-1)
	return 0;
	for(i=2;i<=n-1;++i)
	{
		if(s[i]=='@'&&s[i+1]=='@')
		return 0;
	}
	for(i=2;i<=n-2;++i)
	{
		if(s[i]=='@'&&s[i+2]=='@')
		return 0;
	}
	return 1;
}
void out()
{
	for(i=1;i<=n;++i)
	{
		if(s[i-2]=='@'&&i-2!=last)
		printf(",");
		printf("%c",s[i]);
	}
}
int main()
{
	in();
	if(pd()==0)
	{
		printf("No solution");
		return 0;
	}
	out();
	return 0;
}
```

最后，请dalao们点个赞再走吧。


---

## 作者：皮卡丘最萌 (赞：5)

这题主要考虑这几种特殊情况：

1.字符串的**第一位为@**，例如$S=\texttt{@abc}$

2.字符串的**最后一位为@**，例如$S=\texttt{abc@}$

3.字符串中**没有@**，例如$S=\texttt{abcde}$

4.两个@之间**只有不到2个其他字符**，例如$S=\texttt{a@b@c}$（只有1个字符），
$S=\texttt{ab@@cd}$（没有字符）。

上述情况都直接输出$\texttt{No solution}$。

其余就是在两个合法串之间添加$','$，这里有多种选择方法。其中一种就是把这个串有@后的第一个字符后加$','$。

例如：$S=\texttt{qaq@qwq@qaqqwq@123}$，就可以分裂为
$S=\texttt{qaq@q,wq@q,aqqwq@123}$，值得注意的****是最后一个@后不要分裂****。

代码：
```pascal
var len,k:longint;
s,s1:ansistring;
procedure over;
begin
writeln('No solution'); halt;
end;

begin
readln(s);
len:=length(s);
if s[1]='@' then over;
if s[len]='@' then over;
if pos('@',s)=0 then over;    //判断前3种情况
while pos('@',s)<>0 do
  begin
  k:=pos('@',s);              //查找@的位置
  if (s[k+1]<>'@')and((k+2>length(s))or(s[k+2]<>'@')) then    //判断是否有至少2个其他字符在两个@之间
    s1:=s1+copy(s,1,k+1)+',' else over;
  delete(s,1,k+1);          //删除此部分
  end;
writeln(copy(s1,1,length(s1)-1)+s);   //输出答案
end.
```



---

## 作者：Ace_Radom (赞：2)

### 这题普及+？？？

其实就是考一个字符串成员函数的运用。

看了别的 dalao 的题解，一个用循环查找，一个用队列……

**成员函数**难道不香吗……



------------


## 开始正经的思路分析：

~~原题不解释了~~。

	题目给了一个字符串，要求编写一个程序，在里面提取邮箱地址。
    邮箱地址的格式是 A @ B ，其中 A 和 B 均为字符串。
    
看到这里，第一反应就是查找字符串中“@”的位置。

由于有不合法的情况，所以在分割之前要做判定。

不合法的情况共有三种：

- 在字符串首尾出现 @ 字符。

- 在两个 @ 字符中只有一个小写字母。

- 整个字符串不包含 @ 字符。

笔者在做这道题的时候前前后后交了五次，很大程度上就是因为第三种~~没考虑~~。

再看题目：

	答案可能不唯一，随意输出一个就好。
    
为了方便，我们需要采用统一的分割方法。

我采用的方法是在 @ 后保留一个字母，随后割开。
    
    比如 a@aaaa@aaa@a 就应该分割为 a@a,aaa@a,aa@a 。
    


------------


    
## 筛出不合法情况的方法：

	先判断在字符串首尾是否出现 @ 字符和整个字符串是否包含 @ 字符。

	然后如果仍然合法，就继续做。
    
    查找第一个 @ 字符，在它的周围判断字符串的合法性。
    
    这样一直做，直到检查完最后一个 @ 字符。
    
这里需要运用 STL 库中的成员函数，就~~不细讲了~~。

贴上这一部分的代码：

~~~
bool Inspect( string s ){
	if ( s.find( '@' ) == string::npos )  //第一步筛查
	{
		return false;
	}
	int l = s.size();
	if ( s[0] == '@' || s[l-1] == '@' )  //第二部筛查
	{
		return false;
	}
	int k = 0,Sk = 0;
    // k 是当前筛到的 @ 字符的位置，Sk 是上一个 @ 字符的位置
	while ( s.find( '@' , k + 1 ) != string::npos )  //如果后面还有
	{
		k = s.find( '@' , k + 1 );
		if ( Sk == 0 )  //表明是第一个 @ 字符
		{
			Sk = k;
			continue;  //不用继续判断
		}
		if ( ( k - Sk <= 2 ) || ( s.find( '@' , k + 1 ) - k <= 2 ) )  //第三部筛查
		{
			return false;
		}
	}
	return true;
}
~~~



------------



## 字符串分割的方法：

由于笔者 substr 用不好，所以~~偷懒~~没用。

有纯粹的 STL 做法，但这里讲一种比较朴素的算法。

	从字符串开始用 for 查找。
    
    找到 @ 字符以后，记录下它的位置。
    
    然后从上一个记录的 @ 位置（或开头）一直输出到当前 @ 位置的后一位，然后继续找。
    
但需要注意的是，如果从当前查找位置后没有 @ 字符了（换句话说，这是最后一个 @ 字符），就要全部输出。

然后我又优化了一下：

	查找 @ 字符的后一位，而不是查找 @ 字符的位置。
    
    这样可以避免是 +1 还是 +2 的困惑。

部分代码：

~~~
void Work( string s ){
	int l = s.size();
	int k = 0;
    // k 这里指这个邮箱地址的起始位置
	for ( int i = 0 ; i < l ; i++ )
	{
		if ( s[i-1] == '@' )  //上一位是 @ 字符
		{
			if ( s.find( '@' , i ) == string::npos )  //已经是最后一个 @ 字符了
			{
				for ( int j = k ; j < l ; j++ )  //直接输到最后
				{
					cout << s[j];
				}
				cout << endl;
				return;
			}
			else  //普通输出
			{
				for ( int j = k ; j <= i ; j++ )
				{
					cout << s[j];
				}
				cout << ",";  //不要忘了逗号
				k = i + 1;  //标记下一个邮箱地址的起始位置
			}
		}
	}
}
~~~

主程序代码~~太水了~~，就不贴出来了。



------------



## 做后心得：

本题有多种做法，可以按照自己的能力来选择。

代码能力要求较低，掌握了 C++ 自带的 string 或想到了用循环的朴素算法后基本上不会写不出。

思维量中等，需要考虑清楚不合法的情况有几种。

总之，个人认为这是一道很好的字符串练手题，可以练一练 find 等成员函数的运用。

---

## 作者：Eason_AC (赞：1)

## Content
给定一个字符串 $s$，请将其分解为诸如 $\texttt{xx@xx}$ 的子串，并将分解后的所有子串输出，或者说不存在这样的方案。

**数据范围：$1\leqslant|s|\leqslant 200$。**
## Solution
我们运用一点贪心的想法去做。考虑从后往前遍历字符串，一遍历到 ``@`` 的就直接将后面的还没占用过的所有字符全部和当前的 ``@`` 以及前一个字符组成一个子串。

请注意以下情况：

- 遍历到 ``@`` 后，后面没有字符能够和当前的 ``@`` 组合（包括 ``@`` 在字符串结尾的情况）。
- ``@`` 在字符串的开头。
- 字符串中根本就没有 ``@``。

## Code
```cpp
string s, ans[207];

int main() {
	cin >> s;
	int len = s.size(), lastat = len - 1, vis[207] = {0}, cnt = 0;
	_rep(i, len - 1, 0) {
		if(s[i] == '@' && !vis[i + 1] && i != 0 && i != len - 1) {
			cnt++;
			_for(j, i - 1, lastat) {
				ans[cnt] += s[j];
				vis[j] = 1;
			}
			lastat = i - 2;
		}
		else if(s[i] == '@' && (vis[i + 1] || i == 0 || i == len - 1))
			return printf("No solution"), 0;
		else	continue;
	}
	if(!cnt)	return printf("No solution"), 0;
	string rest = "";
	_for(i, 0, lastat)	rest += s[i];
	ans[cnt] = rest + ans[cnt];
	_rep(i, cnt, 1) {
		cout << ans[i];
		if(i != 1)	printf(",");
	}
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：

> 给定一字符串s，请你将其分割为若干条由"A@B"构成的信息（A,B为字符串） 输入:一个字符串 输出:若不存在合法方案，输出"No solution"，否则输出用","分割的若干条信息，答案可能不唯一，随意输出一个就好 1<=s.l<=200

此题仅仅是模拟，代码如下：

```cpp
#include <cstdio>  
#include <queue>  
#include <iostream>  
using namespace std;  
  
int main()  
{  
    char s[202];  
    char c;  
   // int cnt1=0,cnt2=0;//cnt1、cnt2分别记录字母和@的个数  
    queue <int> pos;//记录出现@处的下标  
    bool OK=1;//判断是否能还原  
    int len,i,j;  
    for(len=0,i=0;scanf("%c",&c)!=EOF;len++)  
    {//cout<<1;  
        if(c=='\n' || c=='\r')  
        {  
            s[len]='\0';  
            break;  
        }  
        else if(c=='@')  
        {  
            //两个@间距不足两位,注意要在pos不为空时才执行。  
            if(!pos.empty() && len-pos.back()<3)  
            {//cout<<"*";  
                OK=0;  
                while(scanf("%c",&c) && !(c=='\n' || c=='\r')){}  
                break;  
            }  
            s[len]=c;  
            pos.push(len);  
        }  
        else  
        {  
            s[len]=c;  
            //cnt1++;  
        }  
    }  
    if(OK)  
    {  
        //如果不存在@ or 不存在字母 or 首字符是@ or 末字符是@  
        if(pos.empty() || !(len-pos.size()) || s[len-1]=='@' || s[0]=='@')  
        {  
            OK=0;  
        }  
        else  
            for(i=0;s[i]!='\0';)  
            {  
                if(pos.size()>1)  
                {  
                    for(;i<pos.front()+2;i++)  
                        cout<<s[i];  
                    cout<<",";  
                    pos.pop();  
                }  
                else  
                {  
                    for(;s[i]!='\0';i++)  
                        cout<<s[i];  
                    cout<<endl;  
                }  
            }  
    }  
    if(!OK) cout<<"No solution"<<endl;  
    return 0;  
} 
```

---

## 作者：Lucifer_Bartholomew (赞：1)

# ~~模拟~~
直接搜"@"的位置

注意要对特殊情况特判
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int a[1010];
int main()
{
	string s;
	cin>>s;
	int n=s.length(),flag2=0,k=0;
	bool flag=0;
	for(int i=0;i<n;++i)
	{
		if(s[i]=='@')
		{
			if(!flag||(flag&&s[i+1]=='@'))
			{
				puts("No solution");
				return 0;
			}
			else
			{
				a[++k]=flag2;
				i++;
				if(i==n)
				{
					puts("No solution");
					return 0;	
				}
				flag=0;
				flag2=i+1;
			}
		}
		else flag=1;
	}
	if(!k)
	{
		puts("No solution");
		return 0;
	}
	for(int i=1;i<k;++i)
	{
		for(int j=a[i];j<a[i+1];++j)
			printf("%c",s[j]);
		printf(",");
	}
	for(int j=a[k];j<n;++j)
		printf("%c",s[j]);
	puts("");
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：BotDand (赞：0)

# Problems
给定一字符串$s$，请你将其分割为若干条由$"A@B"$构成的信息（$A,B$为字符串） 输入:一个字符串 输出:若不存在合法方案，输出$"No$ $solution"$，否则输出用$","$分割的若干条信息，答案可能不唯一，随意输出一个就好。
# Answer
先判断边界条件：如果$n_1$为$@$，则输出$No$ $solution$；相反，如果$n_{n.length()}$为$@$，也输出$No$ $solution$。

如果两个$@$中只有一个字母或没有$@$时也输出$No$ $solution$。

下面扩展几个Pascal字符串处理函数：

* 搜索子串的位置$pos(s1,s2)$如果$s1$是$s2$的子串 ，则返回$s1$的第一个字符在$s2$中的位置，若不是子串，则返回$0$。例：$pos('ab','12abcd')=3$

* 插入子串。过程$insert(s1,s2,i)$把$s1$插入到$s2$的第$i$个位置。例：$s:=abc;insert('12',s,2);$结果$s:='a12bc'$

下面插入$','$就简单了：
# Code
```pascal
var
  n:string;
  i,j:longint;
begin
  readln(n);
  if n[1]='@' then begin writeln('No solution');exit;end;
  if n[length(n)]='@' then begin writeln('No solution');exit;end;
  if pos('@',n)=0 then begin writeln('No solution');exit;end;//特判
  i:=1;
  while i<=length(n) do
    begin
      if n[i]='@' then if (n[i+1]='@') or (n[i+2]='@') then begin writeln('No solution');exit;end;//如果中间的字母数小于2，无解
      if n[i]='@' then begin for j:=i+1 to length(n) do if n[j]='@' then break;if j=length(n) then break;insert(',',n,j-1);end;//如果当前字符为@，则找下一个@（这里注意一点：如果后面没有@了，直接推出循环），插入到下一个@的前面的前面
      inc(i);
    end;
  writeln(n);//输出
end.
```


---

