# [AGC005A] STring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_a

文字列 $ X $ が与えられます。$ X $ の長さは偶数であり、半分は `S` 、もう半分は `T` からなります。

高橋君は `ST` という文字列が苦手です。なので以下の操作を $ 10^{10000} $ 回行うことにしました。

- $ X $ の(連続な)部分文字列で `ST` となるもののうち、最も左側にあるものを取り除く。存在しないならば何もしない。

最終的に $ X $ は何文字になるかを求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ |X|\ ≦\ 200,000 $
- $ X $ の長さは偶数
- $ X $ を構成する文字のうち半分は `S` であり、もう半分は `T` である

### 部分点

- $ 200 $ 点分のデータセットでは $ |X|\ ≦\ 200 $ が成り立つ

### Sample Explanation 1

$ 1 $ 回目の操作では `TSTTSS` の $ 2,3 $ 文字目が `ST` なので取り除きます。 $ X $ は `TTSS` になり、もう `ST` はないため残り $ 10^{10000}-1 $ 回は何もしません。 よって答えは $ 4 $ となります。

### Sample Explanation 2

`SSTTST` ⇒ `STST` ⇒ `ST` ⇒ `` となり、最終的に空文字列になります。

### Sample Explanation 3

`TSSTTTSS` ⇒ `TSTTSS` ⇒ `TTSS` となります。

## 样例 #1

### 输入

```
TSTTSS```

### 输出

```
4```

## 样例 #2

### 输入

```
SSTTST```

### 输出

```
0```

## 样例 #3

### 输入

```
TSSTTTSS```

### 输出

```
4```

# 题解

## 作者：HanPi (赞：6)

[AT2059 【[AGC005A] STring】](https://www.luogu.com.cn/problem/AT2059)

$\texttt{Update:修改了 \LaTeX}$

我一开始是以为搜索 `ST` 然后删除就可以了,但是没想到竟然 $\footnotesize\color{white}\colorbox{#052242}{ \texttt{TLE} }$ 了.

经过思考,我发现我们只需要用栈即可.

既然题目要求遇到 `ST` 就删掉,那我们每次读入一个字符,如果是 `'T'` 且栈顶是 `'S'` 就弹出. 否则则将该字符压入栈中.

答案就是栈的大小

$\huge\tt{Code:}$

本质上是一个栈,~~不过我不喜欢循环,用了递归~~

~~众所周知main函数是可以递归的~~

```c
#include <stdio.h>
char st[200009];
int sz;
int main()
{
	char c=getchar();
	if(c=='\r'||c=='\n')
	{
		printf("%d",sz);
		exit(0); //强行结束程序
	}
	if(sz)
	{
		if(c=='T'&&st[sz-1]=='S')
		{
			st[sz--]=0;
			main();
		}
	}
	st[sz++]=c;
	main();
  	return 0;
}
```


------------
话说这道题用 $\tt{KMP}$ 竟然 
[$\color{white}\colorbox{#052242}{ \texttt{TLE} }$](https://atcoder.jp/contests/agc005/submissions/18615856) 是什么鬼??

---

## 作者：happybob (赞：2)

本题与括号匹配相似

~~我用的两个栈~~

好吧，这种题目用vector的erase都能过，况且这个vector常数小

而大家都是用栈，我也用。

代码：

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<char> st, st2;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int len = s.length() - 1;
    for(register int i = 0; i <= len; i++)
    {
        if(s[i] == 'S') st.push('S');
        else if(s[i] == 'T' && !st.empty()) st.pop();
        else st2.push('T');
    }
    cout << st.size() + st2.size() << endl;
    return 0;
}
```


---

## 作者：TRZ_2007 (赞：2)

## Solution
这道题目初看的时候可能一点思路都没有，因为它需要删除字符，~~让我们想起了消灭星星~~，但是我们可以这么反过来想，我们可以统计字符$S$出现的次数，在字符$S$有出现的前提下，如果出现了$T$，那么就丢出一个$S$来和$T$匹配，需要删除的数量**自加2**，最后把总长度减去删除长度就可以了，注意，**AT题需要换行！！！**  
### $code$

```
#include <bits/stdc++.h>
using namespace std;

string S;
int sums,sumt;

int main()
{
	cin>>S;
	for(int i=0;i<S.size();i++)
	{
		if(S[i] == 'S') sums++;//有S，S出现的次数++
		if((sums)&&(S[i]=='T'))//在有S的前提下，有T
		{
			sums--;//丢出一个S
			sumt+=2;//自加2，因为需要删除S和T
		}
	}
	cout<<S.size()-sumt<<"\n";//最后输出即可
}
```

---

## 作者：勘探员·引魂人 (赞：2)

**前言：我想问一下：“请问洛谷不嫌AT字符串入门题多吗？”**

**思路：先枚举'S',一找到，'S'的个数就++，只要'S'的个数>=1并且找到了'T'，就视为'S'和'T'配对成一组成功，'S'的个数--，需要处理字符串长度-=2（以上过程全在check函数里执行）**

```
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>//别问我为什么不打万能文件（因为不会）
using namespace std;
string st;//定义需要处理的函数
int check(string x)//定义check函数
{
	int sg,h=x.size();//sg是记录'S'的个数，h的值直接赋为需要处理的字符串的长度
	for(int i=0;i<x.size();i++)//开始处理，从0枚举到n
	{
		if(x[i]=='S') sg++;//如果找到了一个'S','S'的个数++
		if(sg>=1&&x[i]=='T')//如果'S'的个数>=1而且找到了一个'T'就视为'S'和'T'配对成一组成功
		{
			sg--;//'S'的个数--
			h-=2;//总长度-=2
		}
	}
	return h;//return 现在的总长度
}
int main()
{
    cin>>st;//输入要处理的字符串
    cout<<check(st)<<endl;//直接调用check函数输出（记得换行）

    return 0;//结束" “ST”ring "程序
}
```


---

## 作者：PrincessQi (赞：1)

提供几种不同的方法。

思路：从输入的字符串头扫到字符串尾，如果扫到的字符为 $\texttt{T}$ 且上一个字符为 $\texttt{S}$，就将这两个字符删掉。

那怎么处理删除操作呢？

有三~~四~~种想法：

1.我会栈！我们可以使用栈来记录前面还有多少个可用字符。如果扫到 $\texttt{T}$ 且栈顶为 $\texttt{S}$ 就把栈顶弹出，否则就把该字符加入栈。最后栈中剩下的字符数量就是答案。考虑到可以统计删掉了多少个数，再用总数减去就是答案，且栈中最后剩下的字符一定是形如 $\texttt{TT...TTSS...S}$ 的字符串，则可以统计栈中还有多少 $\texttt{S}$ ，这样可以节省空间。

2.我会链表！我们可以使用链表，首先建一个数组``pre[]``表示每个字符的前一个字符的编号。如果扫到 $\texttt{T}$ 且``pre[i]``为 $\texttt{S}$ ，就将``pre[i+1]``修改为``pre[pre[i]]``。最后剩下的字符数量就是答案。

3.我会``vector``！直接使用``vector``中自带的``erase``就好了。

~~4.我会平衡树！只要你愿意用，没人拦你。~~

鉴于此题其他题解全都是使用栈来解决此题（虽然栈确实是解决此类问题最经典的方法），我的代码使用的是链表。

```
#include<bits/stdc++.h>
using namespace std;
int pre[200005],ans;
string s;
int main(){
	cin>>s;
	int l=s.size();
	for(int i=1;i<l;i++)
		pre[i]=i-1;
	for(int i=1;i<l;i++)
		if(s[pre[i]]=='S'&&s[i]=='T')pre[i+1]=pre[pre[i]],ans+=2;
	printf("%d",l-ans);
	return 0;
}
```


---

## 作者：MilkyCoffee (赞：1)

这里我们根据题意说，要一对儿一对儿删除 $S$ 和 $T$ ，看起来比较难办，可是如果有 $S$ 和 $T$ ，它们肯定是连载一起的，我们只需要用字符串总长度减去能减的 $S$ 和 $T$ 就好啦。

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int sums, summinus;

int main()
{
	cin >> s;
    int tmp = s.length(); // #1
	for(int i = 0; i < tmp; i++) {
		if (s[i] == 'S') sums++; // #2
		if (sums != 0 && (S[i]=='T')) { // #3
			sums--;
			summinus += 2;
		}
	}
	cout << tmp - summinus << endl;
}
```
1 : 这里是细节，如果我们把s.length放在外面，就不需要每次都判断s的长度是多少，能大大优化程序执行时间。

2 : 如果有s，就把它放在统计变量里

3 : 如果在有s的条件下还有t，就删除一个s

---

## 作者：Fengxiang008 (赞：0)

## 本题思路：

### 大致思路：
-----
这题方法十分类似于栈。        
用一个容器记下 S 的个数，另一个容器记录要删除的个数。
然后用字母的总数减去要删除的个数，就是答案。

-----
### 具体操作：
-----
当遇到 S 时，存 S 的容器内的 S 数量加1；

当遇到 T 时，若存 S 的容器大于 0，减少一个容器内的 S ，将记录删除的数量的容器内加二。

用代码实现：（其中 anss 表示 S 数量， de 表示需删除的数量, x表示当前字母）
```cpp
if(x == 'S')
{
	anss++;//有S，S出现的次数++
}
if((anss>0)&&(x=='T'))//如果在有S的前提下，有T
{
	anss--;//消掉一个S
	de+=2;//自加2，因为删除的是S和T两个字母
}
```

---

## 上代码：
```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;
int main()
{
	string str;//定义一个字符串 
	int anss=0,de=0;//分别存S数量和删除字符数量的两个容器 
	cin>>str;
	for(int i=0;i<str.size();i++)//str.size()表示str内存的数的数量，注意从0开始 
	{
		if(str[i] == 'S')
		{
			anss++;
		}
		if((anss>0)&&(str[i]=='T'))
		{
			anss--;
			de+=2;
		}
	}
	printf("%d\n",s.size()-de);//输出结果 
	return 0;//好习惯
}
```


---

## 作者：Otue (赞：0)

### 思路
因为它需要删除字符，我们可以这么反过来想，我们可以统计字符S出现的次数，在字符S有出现的前提下，如果出现了T，那么就丢出一个S来和T匹配，需要删除的数量自加2，最后把总长度减去删除长度就可以了

或者用栈：

如果当前读入到 T 并且栈顶为 S，就将栈顶的 S 出栈，并不将 T 加入栈。

否则将读到的字符入栈。

最后栈的元素个数即为答案。
### 代码：
```
#include <bits/stdc++.h>
using namespace std;
string s;
int sum,sum1;
int main(){
	cin>>s;
	int sum1=s.size();
	for(int i=0;i<s.size();i++){
		if(s[i]=='S') sum++;
		if(sum>0&&s[i]=='T'){
			sum--,sum1-=2;
		}
	}
	cout<<sum1<<endl;
}
```

---

## 作者：hhz007 (赞：0)

因为它需要删除字符，我们可以这么反过来想，我们可以统计字符S出现的次数，在字符S有出现的前提下，如果出现了T，那么就丢出一个S来和T匹配，需要删除的数量自加2，最后把总长度减去删除长度就可以了
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int sum,sum1;
int main()
{
	cin>>s;
	int sum1=s.size();
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='S') sum++;
		if(sum>0&&s[i]=='T')
			sum--,sum1-=2;
	}
	cout<<sum1<<endl;
	return 0;
}
```


---

## 作者：xiezihan (赞：0)

来一篇C语言的



------------
这题就是找到```S```和```T```，并并把它们一一配对就好了，让后然总长度减去数量，此题AC



------------
上代码
```c
#include<stdio.h>
#include<string.h>
using namespace std;
char a[200000];
int main()
{
	int n=0,i=0,tmp=0,s=0;
	scanf("%s",a);
	n=strlen(a); 
	for(i=0;i<n;i++)
	{
		if(a[i]=='S')
		{
			tmp++;
		}
		if(tmp!=0&&a[i]=='T')
		{
			tmp--;
			s+=2;
		}
	}
	printf("%d\n",n-s);
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/43393082)



---

## 作者：efgh123 (赞：0)

先认识一个函数
```cpp
erase();
```
如：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s,s2;
	s="Hello C++ Would!";
	s2="Hello C++ Would!";
	s.erase(6,4);//s字符串从第六个字符开始，删除4个字符 
	s2.erase(6);//s2字符串从第六个字符开始，删除后面全部字符 
	cout<<s<<"\n"<<s2;
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/a3phb1br.png)
## 题目
有一个字符串X，对它进行操作。 该串只含S和T，凡是S与T连在一起都要将它们一起去掉 现在进行若干次操作直到该串中没有连在一起的ST，问剩下的长度。

## 思路
1.输入

2.判断S和T连在一起

3.删去（用erase）

4.从头开始判断

5.输出

## 防作弊，不发代码


---

## 作者：小王子2021 (赞：0)

## 简单题意：

		要求把字符“S”与字符“T”一一配对并删除，输出剩下的长度
## Solution

看似是删除字符，但仔细分析，实际上有个引理：
  
  如果有S和T，那么它们肯定是连在一起的
  
这个引理其实是显而易见的（~~只要你有数学功底~~）,然后我们可以用总长度减去S和T一一能配对的个数即可求出答案

在此再对S和T能配对的个数讲解：（针对没学过stack的同学们

1. 如果字符串中有“S”，sumS的个数加一
2. 如果字符串中不是“S”，即字符串中是“T”，此时根据引理即可配对，但是需要注意有没有sumS,所以得当sumS大于0时，才能把sumS的个数减1（因为当成配对的了），同时tot的个数加2(一组两个字符配对）
3. 剩下的长度即为原始长度减去tot

二话不多说，上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len,sumS,tot;
int main()
{
	cin>>s;len=s.length();
	for(int i=0;i<tmp;i++)
    {
		if(s[i]=='S')sumS++;
		if(sumS!=0&&(S[i]=='T'))
        {
			sumS--;
			tot+=2;
		}
	}
	cout<<len-tot;
}
```
额外的注：

1.区分如何求s的长度

	求string s的长度为s.length();
 	求char s[101]的长度为strlen(s);


## The End
	这是小王子2020的题解的第二弹
   顺带膜拜膜拜机房巨佬FDY_ManchesterCity

---

## 作者：No_Au_No_Name (赞：0)

### 模拟判断

直接读入串 $s$，用一个 $ans$ 存储串中 `S` 的个数，然后与 `T` 匹配，每次配对成功就把 `S` 的个数减 $1$，然后把表示删除字符的个数的变量 $del$ 加 $2$，因为是`S` 和 `T` 一起删除，所以要加 $2$，问你最后长度，就是原长度 $-$ 删掉字符的个数。

```
#include<bits/stdc++.h>
using namespace std;
string s;
int ans,del;
int main()
{
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='S') ans++;
		if(ans!=0 and s[i]=='T')
		{
			ans--;
			del+=2;
		}
	}
	cout<<s.length()-del<<endl;
	return 0;
}
```

---

## 作者：Snow_Dreams (赞：0)

这道题其实很简单的

题意：
_有一个字符串X，对它进行操作。 该串只含S和T，凡是S与T连在一起都要将它们一起去掉 现在进行若干次操作直到该串中没有连在一起的ST，问剩下的长度。_ 

那我们就需要枚举

首先，读入数据，我建议用getchar()，如果读取到S，就将一个元素压入栈中，如果读取到T且栈中有元素，就弹出元素，如果没有，就cnt++

最后，输出cnt+栈中的元素个数即可

---

## 作者：我是蒟弱 (赞：0)

# $\color{red}\text{以ST治ST}$

题目$STring$,我$STack$

具体操作：

1.建造一个**栈($stack$)**

2.遇到$S$，入栈，遇到$T$，如果栈里有$S$，减去两个长度

### 这道题我用的while(cin>>ch){ 输入，交的时候是文件输入输出没有问题，本机测的时候，输入数据完了Ctrl+Z，看答案

### $\color{red}\text{循环输入可以一直输入，直到输入数据停，很有用}$

源代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<stack>
#include<cstring>
using namespace std;
stack<int>s;//建造一个栈
int main(){
	char ch;//输入
	int ans=0;//记长
	while(cin>>ch){//输入
		ans++;//加长度
		if(ch=='S') s.push(1);//入栈
		else if(!s.empty()) s.pop(),ans-=2;//减“ST”
	}
	cout<<ans<<endl;//输出长度
	return 0;
}

```


---

## 作者：该起什么名字 (赞：0)

感觉这题和[P1739](https://www.luogu.org/problemnew/show/P1739)有点像
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int sumt,sums,sum;
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++)
	{
		if(s[i]=='S') sums++;//计算S的个数
		else if(sums) sumt++;//如果有S，就计算T的个数（类似于有左括号再算右括号）
		if(sums>=sumt)//如果此时的S数量比T大了或相等(这里写的不大明白
		{
			sum+=min(sums,sumt)*2;//计算需要删去的数量
			sums-=min(sums,sumt);//减去用掉的S数
			sumt=0;//减去用掉的T数
		}
	}
	cout<<n-sum<<endl;
	return 0;
}


```

---

## 作者：Iron_Heart (赞：0)

## 思路

栈。

如果当前读入到 `T` 并且栈顶为 `S`，就将栈顶的 `S` 出栈，并不将 `T` 加入栈。

否则将读到的字符入栈。

最后栈的元素个数即为答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

char s[200100];
stack<char> st;

int main() {
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'T' && !st.empty() && st.top() == 'S') {
            st.pop();
        } else {
            st.push(s[i]);
        }
    }
    printf("%d\n", st.size());
    return 0;
}
```


---

