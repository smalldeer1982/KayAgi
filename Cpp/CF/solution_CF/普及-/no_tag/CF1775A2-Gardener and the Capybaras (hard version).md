# Gardener and the Capybaras (hard version)

## 题目描述

有三个只由字符 `a,b` 构成的字符串 $a,b,c$ ，且 $a\le b,c\le b$ 或 $a\ge b,c\ge b$。 将它们拼在一起构成了一个新字符串 $s$。


现在给你 $s$，($3\le |s|\le 2\cdot 10^5$)，你要复原这三个字符串。

一共有 $T(T\le 10^4)$ 组测试数据，所有数据中字符串的总长不会超过 $4\cdot 10^5$。

## 说明/提示

定义字符串 $x$ 小于 $y$ ，当且仅当：

$x$ 是 $y$ 的前缀，且 $x \not =y$ 。

或

在 $x$ 与 $y$ 的第一个不同的位置，$x$ 的这一位字符是 `a`，$y$ 的这一位字符是 `b`。

## 样例 #1

### 输入

```
5
bbba
aba
aaa
abba
abbb```

### 输出

```
b bb a
a b a
a a a
ab b a
a bb b```

# 题解

## 作者：lovely_fcukh (赞：14)

# 题目大意
给定 $t$ 个字符串，对于每个字符串，将它分成三份连续的区间 $a,b,c$，要求满足字典序比较为 $b \leq a$ and $b \leq c$ 或 $a \leq b$ and $c \leq b$，输出任意满足条件的 $a,b,c$。
# 思路
我们可以发现这题的数据比弱化版增强了很多，用之前的暴力算法肯定会炸。通过观察字符串我们可以发现：  
* 这道题是诈骗，因为不管怎么样数据都必定有解。  
* 对于每组样例，如果除掉头和尾两个字符以外的字符中，如果当中有一个字符 'a'，那么我们把 $b$ 设为单个的 'a' 一定满足 $b \leq a$ and $b \leq c$。
* 对于每组样例，如果除掉头和尾两个字符以外的字符中，没有字符 'a'，那么代表除掉头和尾这一段全是 'b'，这样我们把 $b$ 设为除掉头和尾以外的字符就一定满足 $a \leq b$ and $c \leq b$。

这样我们按照发现的规律打代码就能通过了。
# Code
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n;
	while(n--){
		cin>>s;
		bool f=0;
		for(int i=1;i<s.size()-1;i++){
			if(s[i]=='a'){
				for(int j=0;j<i;j++)cout<<s[j];
				cout<<' '<<s[i]<<' ';
				for(int j=i+1;j<s.size();j++)cout<<s[j];
				cout<<endl;
				f=1;
				break;
			}
		}
		if(f)continue;
		cout<<s[0]<<' ';
		for(int i=1;i<s.size()-1;i++)cout<<s[i];
		cout<<' '<<s[s.size()-1]<<endl;
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：11)

# 题解

- 赛时想了很多解法，不过都很难写，但毕竟是 2A，应该时偏思维，码量并不大，于是就往这个方面想，于是就有了这个类似于贪心的解法。

- 分类讨论，看开头三个字符：

1. `aaa`，`aab`，`aba`，`baa`，`bba`，`bbb`，发现可以直接开头两个字符各一段，剩余的字符一段。

1. `abb`，发现与之前的情况不同，处理方法很简单，直接开头第一个字符一段，最后一个字符一段，中间的字符一段。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
string str;

int main()
{
	cin >> T;
	while (T --)
	{
		cin >> str;
		int len = str.size();
		if (str[0] == 'a' && str[1] == 'b' && str[2] == 'b')
		{
			cout << str[0] << " ";
			for (int i = 1 ; i < len - 1 ; i ++)
			{
				cout << str[i];
			}
			cout << " " << str[len - 1] << endl;
			continue;
		}
		cout << str[0] << " " << str[1] << " ";
		for (int i = 2 ; i < len ; i ++)
		{
			cout << str[i];
		}
		cout << endl;
	}
	return 0;
}

```


---

## 作者：Mine_King (赞：5)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# A2. Gardener and the Capybaras

## Problem

[CF1775A2 Gardener and the Capybaras](https://codeforces.com/contest/1775/problem/A2)

**题目大意：**

给你一个由 `a` 和 `b` 组成的字符串，要将它分成三个子串，使得中间那个串字典序最大或最小，输出任意一种方案。若无解，输出 `:(`。

## Solution

这个只有 `a` 和 `b` 的条件其实是无用的。

考虑使其字典序最小，则一定是中间找出一个字典序最小的字符成为中间一段，剩下的成为左右两段。故可以使中间的串字典序最小当且仅当全串最小的字符在中间（即非第一个和最后一个字符）出现。

考虑使其字典序最大，沿用上面的思路一定是从字典序最大的字符开始。但为了使其字典序更大应该一直往后扩展直到最后一个字符之前。

可以证明上面两种构造方法是不劣的，所以若无法用上面两种方法构造则无解。

## Code

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T;
string s;

int main() {
	cin>>T;
	while (T--) {
		cin>>s;
		char mn=127,mx=0;
		for (char ch:s) mn=min(mn,ch),mx=max(mx,ch);
		string s1="",s2="",s3="";
		for (int i=1;i<(int)s.length()-1;i++)
			if (s[i]==mn) {
				for (int j=0;j<i;j++) printf("%c",s[j]);
				putchar(' ');
				printf("%c",s[i]);
				putchar(' ');
				for (int j=i+1;j<(int)s.length();j++) printf("%c",s[j]);
				puts("");
				goto NXT;
			}
		for (int i=1;i<(int)s.length()-1;i++)
			if (s[i]==mx) {
				for (int j=0;j<i;j++) s1.push_back(s[j]);
				for (int j=i;j<(int)s.length()-1;j++) s2.push_back(s[j]);
				s3.push_back(s.back());
				break;
			}
		if (s2>=s1&&s2>=s3) cout<<s1<<' '<<s2<<' '<<s3<<'\n';
		else puts(":(");
		NXT:;
	}
	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：4)

### 前置芝士：

[简单版](https://www.luogu.com.cn/blog/686297/solution-cf1775a1)

由于一开始是简单版，$n^3$ 并不会超时，而现在数据增强，我们只能用优化的代码。

我们经过之前代码的部分优化，可以把他压缩成**双重循环**：
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main()
{
	int n;
	cin>>n;
	while(n--){
		string st,a="",b="",c="";
		cin>>st;
		for(int i=0;i<st.size();i++){
			a+=st[i];
			b="";
			c="";
			for(int j=i+1;j<st.size();j++){
				b+=st[j];
				c=st.substr(j+1,st.size());//优化部分
				if(a<=b&&c<=b||a>=b&&c>=b)goto print;
			}
		}
		print:
		cout<<a<<' '<<b<<' '<<c<<'\n';
	}
}
```

但是如果拿这个代码交的话，还是过不了，因为数据范围是 $ 3 \le |s| \le 2 \cdot 10^5 $ 。

我们通过题目可以发现，要么就是 $b$ 最小，要么就是 $b$ 最大，而且只由 `a`，`b` 两种字符组成，我们可以从中找到以下方案：

1.当第二位是 `a` 时，我们可以把第一位的字符给 $a$ ，第二位给 $b$ ，其余的都给 $c$ ，这样的话 $b$ 就是最小的，而 $a$ 和 $c$ 可以保证比 $b$ 要大或者一样。

2.当第二位是 `b` 时，我们可以把第一位的字符给 $a$ ，最后一位给 $c$ ，中间的都给 $c$ ，这样的话 $b$ 就是最大的，而 $a$ 和 $c$ 可以保证比 $b$ 要小或者一样。

得出以上方案后，我们其实就可以发现，输出 `:(` 的情况是不存在的。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main()
{
	int n;
	cin>>n;
	while(n--){
		string st,a="",b="",c="";
		int ans=0;
		cin>>st;
		if(st[1]=='a')
			cout<<st[0]<<' '<<'a'<<' '<<st.substr(2,st.size()-1)<<'\n';
		else
			cout<<st[0]<<' '<<st.substr(1,st.size()-2)<<' '<<st[st.size()-1]<<'\n';
	}
}
```

---

## 作者：11111118m (赞：3)

# 题意
给你一个字符串 $S$，请你把它分解成三段，设第一段为 $A$，第二段为 $B$，第三段为 $C$，要求以字典序排列时 $B \le A$，且 $B \le C$；或 $B \ge A$，且 $B \ge C$。
# 解法
当 $S$ 的除了最后一个字符和第一个字符还有 $a$ 字符时，设除了最后一个字符和第一个字符后的第一个 $a$ 字符位置为 $pos$，则 $A$ 为 ```s.substr(0, pos)```，$B$ 为 ```a```，$C$ 为 ```s.substr(pos + 1)```

除此之外，$A$ 为 $S$ 的第一个字符，$C$ 为最后一个字符，剩下的是 $B$。
# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
void solve() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    if (s[0] == s[n - 1]) { std::cout << s[0] << ' ' << s.substr(1, n - 2) << ' ' << s[n - 1] << '\n'; return; }
    else {
        int pos = 0;
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == 'a') {
                pos = i;
                break;
            }
        }

        if (pos) {
            std::cout << s.substr(0, pos) << " " << 'a' << " " << s.substr(pos + 1) << "\n";
            return;
        }
        else {
            std::cout << s[0] << " " << s.substr(1, n - 2) << " " << s[n - 1] << "\n";
            return;
        }
    }
    std::cout << ":(\n";
}
int main() {
    std::cin.tie(0)->std::ios::sync_with_stdio(0);
    int _ = 1;
    std::cin >> _;
    while (_--)  solve();
    return 0;
}
```

---

## 作者：_Z_F_R_ (赞：1)

让本蒟蒻讲一个思路清奇的做法。

注：本题解中的字符串下标从 1 开始编号。
***
根据题意可知，字符串 $\texttt{a}$ 是字典序最小的一个字符串。因此，若 $S_2,S_3,S_4,\dots,S_{|S|-2},S_{|S|-1}$ 中有一个是 $\texttt{a}$（设这个字符的下标为 $i$），那么 $a=S[1,i-1],b=S[i,i],c=S[i+1,|S|]$ 即可满足 $b \ge a,b \ge c$ 的要求。

若 $S_2,S_3,S_4,\dots,S_{|S|-2},S_{|S|-1}$ 中有没有一个是 $\texttt{a}$，那么这个字符串必为 $\texttt{?bbbbb} \dots \texttt{bbbbb?}$，问号为不知道的字符。

易发现 $a=S[1,1],b=S[2,|S|-1],c=S[|S|,|S|]$ 必定满足 $a \le b,c \le b$ 的要求。

综上，问题得解。
***
代码在此：

```cpp
#include<bits/stdc++.h>
using namespace std;

void Write(int s1,int s2,string s)//输出并加空格
{
	int i;
	for(i = 0;i < s.size();i++)
	{
		putchar(s[i]);
		if(i == s1 - 1 || i == s2 - 1)
			putchar(' ');
	}
	putchar('\n');
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		string s;
		cin >> s;
		int i,sub1 = -1,sub2 = -1;//sub1 是字符串 b 的起始位置，sub2 是字符串 c 的起始位置。
		for(i = 1;i < s.size() - 1;i++)
			if(s[i] == 'a')//找到了一个 a
			{
				sub1 = i;
				sub2 = i + 1;
				break;
			}
		if(sub1 != -1)
		{
			Write(sub1,sub2,s);
			continue;
		}
		Write(1,s.size() - 1,s);//没找到 a
	}
}
```

---

## 作者：chlchl (赞：1)

考场 10min 想到 A1、A2 做法，然后开 B、C、D，全部有思路但是全部差关键问题，不然 rated 可以翻倍了……

## 题意简述
给定一个 $ab$ 串 $s$，将其拆成连续的三份，分别记为 $a,b,c$，要求 $a\leq b,c\leq b$ 或者 $a\geq b,c\geq b$。

其中比较符号代表的是字典序的比较。请输出任意一种方案。

## 做法
本博客默认字符串下标从 $1$ 开始，$|s|=n$，一个子串表示为 $s_{l,r}$。

都说 CF 偏构造，这题就挺构造，典型 CF 风格的签到题。

长度 $\geq 3$ 的字串，只要按照我下面的构造方法一定有解。而题目数据又保证长度 $\geq 3$，所以这道题不需要判无解。

首先我们可以确定，$s$ 的第一个位置一定属于 $a$，我们把它记为 $c$。

因为题目要求 $b$ 一定要是最大或最小的，所以我们可以考虑一种山峰、山谷构造法。

我们找到 $s$ 下一个出现的字符 $c$（这个位置记为 $idx$）。显然 $s_2\sim s_{idx-1}$ 都是另一种字符，这时我们只要让 $a=s_1$，$b=s_{2,idx},c=s_{idx,n}$，一定能满足题目要求。

为什么？因为 $a,c$ 的开头字符都与 $b$ 不一样，字典序肯定能够比较出来，并且 $a,c$ 的**开头字符是一样的，所以它们相对于 $b$ 必定同大同小**。

这可以解决大多数情况，但还有两种特殊情况我们需要讨论：
- $s_1$ 之后全都是另一种字符，类似 $abbb\cdots$。这时我们需要分类讨论：以 $abbbb$ 的形式为例，此时 $a$ 字典序一定小于 $b$，所以我们可以只分一个字符给 $c$，这样 $c$ 一定是 $b$ 的一个前缀，字典序不会大于 $b$。请读者自行完成 $baaaa$ 的情况。
- $s_2=s_1$，这时我们让 $a=s_1,b=s_2$，那 $a=b$，后面的全分给 $c$ 就行，因为无论 $c$ 大于还是小于 $b$，$a,b$ 之间永远相等，必定满足关系。

然后就讨论得差不多了，注意 `printf` 不能输出字符，请使用 `putchar`。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int T, n;
char s[N];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s", s + 1);
		n = strlen(s + 1);
		int idx = -1;
		char c = s[1];
		for(int i=2;i<=n;i++){
			if(s[i] == c){
				idx = i;//找到下一个与 s[1] 相等的字符 
				break;
			}
		}
		if(idx == 2){ 
			putchar(s[1]), putchar(' '), putchar(s[2]), putchar(' ');
			for(int i=3;i<=n;i++)
				putchar(s[i]);
			putchar('\n');
			continue;
		}
		if(idx == -1){//后面全都是另一个字符
			putchar(s[1]), putchar(' ');
			if(c == 'a'){//abbbbbb
				for(int i=2;i<n;i++)
					putchar(s[i]);
				putchar(' ');
				putchar(s[n]), putchar('\n');
			}
			else{//baaaaaaaa
				putchar(s[2]), putchar(' ');
				for(int i=3;i<=n;i++)
					putchar(s[i]);
				putchar('\n');
			}
			continue;
		}
		putchar(s[1]), putchar(' ');//a=s[1]
		for(int i=2;i<idx;i++)
			putchar(s[i]);//b=s[2,idx-1]
		putchar(' ');
		for(int i=idx;i<=n;i++)
			putchar(s[i]);//c=s[idx,n]
		putchar('\n');
	}
	return 0;
} 
```

这份代码可以直接过 A1，A2，写起来不难，理清思路 10min 可以切掉。

时间复杂度 $O(\sum|S|)$，A2 保证不超过 $4\times 10^5$，绰绰有余。

---

## 作者：baiABC (赞：1)

首先观察到，如果字符串 $a$，$b$，$c$ 中有两个相同，剩下一个取任意非空字符串都可以。

有如下情况：（$\texttt{*}$ 表示任意非空 $\texttt{ab}$ 串）
1. $\texttt{a*a}$
2. $\texttt{b*b}$
3. $\texttt{aa*}$
4. $\texttt{*aa}$
5. $\texttt{bb*}$
6. $\texttt{*bb}$
7. $\texttt{ab*ab}$
8. $\texttt{ba*ba}$
9. $\texttt{a b ab}$
10. $\texttt{b a ba}$

分讨即可，没有无解情况。
时间复杂度 $O(\sum |s|)$
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[400010];
int main()
{
   int T; scanf("%d", &T);
   while(T--)
   {
      scanf("%s", s);
      int n = strlen(s);
      if(s[0] == s[n-1])
      {
         char c = s[n-1]; s[n-1] = '\0';
         printf("%c %s %c\n", s[0], s+1, c);
         continue;
      }
      if(s[0] == s[1])
      {
         printf("%c %c %s\n", s[0], s[1], s+2);
         continue;
      }
      if(s[n-1]==s[n-2])
      {
         char c1 = s[n-1];
         s[n-2] = '\0';
         printf("%s %c %c\n", s, c1, c1);
         continue;
      }
      if(n != 4)
      {
         s[n-2] = '\0';
         printf("%c%c %s %c%c\n",s[0],s[1],s+2,s[0],s[1]);
         continue;
      }
      if(s[0]=='a') puts("a b ab");
      else puts("b a ba");
   }
   return 0;
}
```

---

## 作者：ran_qwq (赞：1)

分类讨论。

如果字符串中有 $\texttt{a}$ 且不为第一个字符和最后一个字符，则可以把 $\texttt{a}$ 作为第二个字符。因为 $\texttt{a}$ 的字典序是最小的，所以两边无论是什么字符串都满足条件。

如果没有 $\texttt{a}$，则字符串的第二个字符必为 $\texttt{b}$，截取第 $2$ 到 $n-1$ 个字符，则它的字典序肯定大于等于 $\texttt{a}$ 或 $\texttt{b}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1e9,Mod=998244353;
//省略快读快写
int T;
signed main()
{
	T=read();
	while(T--)
	{
		string s;cin>>s;int len=s.size(),flag=1;
		for(int i=1;i<len-1&&flag;i++)
			if(s[i]=='a')
			{
				flag=0;
				for(int j=0;j<i;j++)
					cout<<s[j];
				cout<<" "<<s[i]<<" ";
				for(int j=i+1;j<len;j++)
					cout<<s[j];
				puts("");
			}
		if(flag)
		{
			cout<<s[0]<<" ";
			for(int i=1;i<len-1;i++)
				cout<<s[i];
			cout<<" "<<s[len-1]<<"\n";
		}
	}
}

```


---

## 作者：fengxiaoyi (赞：0)

### 思路

首先，查找第 $2$ 个字符到第 $n-1$ 个字符是否有 `a`（其中 $n$ 表示字符串的长度），如果有，设这个位置为 $k$，输出第 $1$ 个字符到第 $k-1$ 个字符然后输出空格，接着输出第 $k$ 个字符，然后再输出一个空格最后输出第 $k+1$ 个字符到第 $n$ 个字符。

否则，说明 $2\sim n-1$ 个字符都是 `b`，输出第 $1$ 个字符、第 $2\sim n-1$ 个字符、第 $n$ 个字符。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
char s[200010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		int n=strlen(s+1),l;
		if(n<3){
			printf(":(\n");
			continue;
		}
		bool f=0;
		for(int i=2;i<n;i++){
			if(s[i]=='a'){
				f=1;
				l=i;
				break;
			}
		}
		if(!f){
			printf("%c ",s[1]);
			for(int i=2;i<n;i++) putchar(s[i]);
			printf(" %c\n",s[n]);
		}
		else{
			for(int i=1;i<l;i++) putchar(s[i]);
			printf(" a ");
			for(int i=l+1;i<=n;i++) putchar(s[i]);
			putchar('\n');
		}
	}
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

本题解对 CF1775A1 和 CF1775A2 均有效。

### 一、思路

题意：将一个大字符串分割成 $3$ 个非空的小字符串，使中间的小字符串同时大于等于两边的小字符串或同时小于等于两边的小字符串。**大字符串只含 `ab`。**

我们可以分类讨论。

1. 当大字符串长度为 $3$ 时：

   不难发现此时直接分割即可，无论两端的字符是否相等。
   
2. 当两端字符相等时：

   将两端的字符单独分割出来，作为第 $1$ 和第 $3$ 个小字符串，中间的字符串作为第 $2$ 个小字符串。
   
   显然，此时中间的字符串一定同时小于等于（或同时大于等于）两边的字符串，因为两边字符串相等。
   
3. 考虑以上条件后，第一个字符为 `a`（最后一个字符为 `b`）时：

   找到在第 $2$ 到第 $n-1$ 个字符中，第一个为 $b$ 的，记录位置为 $o$。
   
   然后，三个小字符串分别是第 $[1,o-1],[o,n-1],[n,n]$ 个大字符串。
   
   证明：中间的小字符串一定大于左边的小字符串，因为左边的小字符串以 `a` 开头，中间的小字符串以 `b` 开头；中间的小字符串一定大于等于右边的小字符串，因为右边的小字符串是中间的小字符串的前缀（就是一个字符 `b`），中间的小字符串却有较大的长度。
   
   如果找不到，就说明整个字符串除了最后一个字符都是 `a`。此时三个小字符串分别是第 $[1,n-2],[n-1,n-1],[n,n]$ 个大字符串。请读者自行证明。

4. 考虑以上条件后，第一个字符为 `b`（最后一个字符为 `a`）时：

   找到在第 $2$ 到第 $n-1$ 个字符中，最后一个为 $b$ 的，记录位置为 $o$。
   
   然后，三个小字符串分别是第 $[1,o-1],[o,o],[o+1,n]$ 个大字符串。请读者自行证明。
   
   如果找不到，就说明整个字符串除了第一个字符都是 `a`。此时三个小字符串分别是第 $[1,1],[2,n-1],[n,n]$ 个大字符串。请读者自行证明。

我们惊喜地发现，不存在无解情况。

以上解法并不完美，太长了。不过能用就好。

### 二、代码

```cpp
// Problem: A1. Gardener and the Capybaras (easy version)
// Contest: Codeforces Round #843 (Div. 2)
// URL: https://codeforces.com/contest/1775/problem/A1
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
#include<cstring>
using namespace std;
int t;
char s[200005];
int n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		if(n==3)
		{
			printf("%c %c %c\n",s[1],s[2],s[3]);
			continue;
		}
		if(s[1]==s[n])
		{
			printf("%c ",s[1]);
			for(int i=2;i<n;i++)
			{
				printf("%c",s[i]);
			}
			printf(" %c\n",s[n]);
			continue;
		}
		if(s[1]=='a')
		{
			int flag=0;
			for(int i=2;i<n;i++)
			{
				if(s[i]=='b')
				{
					flag=i;
				}
			}
			if(flag)
			{
				for(int i=1;i<flag;i++)
				{
					printf("%c",s[i]);
				}
				printf(" ");
				for(int i=flag;i<n;i++)
				{
					printf("%c",s[i]);
				}
				printf(" %c\n",s[n]);
			}
			else
			{
				for(int i=1;i<=n-2;i++)
				{
					printf("%c",s[i]);
				}
				printf(" %c ",s[n-1]);
				printf("%c\n",s[n]);
			}
		}
		if(s[1]=='b')
		{
			int flag=0;
			for(int i=n-1;i>1;i--)
			{
				if(s[i]=='a')
				{
					flag=i;
					break;
				}
			}
			if(flag)
			{
				for(int i=1;i<flag;i++)
				{
					printf("%c",s[i]);
				}
				printf(" %c ",s[flag]);
				for(int i=flag+1;i<=n;i++)
				{
					printf("%c",s[i]);
				}
				printf("\n");
			}
			else
			{
				printf("%c ",s[1]);
				for(int i=2;i<n;i++)
				{
					printf("%c",s[i]);
				}
				printf(" %c\n",s[n]);
			}
		}
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

如果想让 $b$ 的字典序尽可能小，不难想到让 $b=\tt a$，左边是 $a$，右边是 $c$，显然的，$b$ 的位置不能是 $1$ 或 $n$（其中 $n$ 是字符串的长度，下文同）。

如果在区间 $[0, n-1]$ 中，没有一个字符是 $\tt a$，那我们就要让 $b$ 尽可能大。因为这一段没有一个是 $\tt a$，所以这一段必定全都是 $\tt b$。

考虑把这一段所有字符（全是 $\tt b$）都给 $b$，然后 $a=s_1$，$c=s_n$，这样 $b$ 的字典序必定是最大的。



```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
void print(int x) {
  for (int i = 0; i < x; ++i) cout << s[i];
  cout << ' ';
  cout << s[x];
  cout << ' ';
  for (int i = x + 1; i < s.size(); ++i) cout << s[i];
  cout << endl;
}
void solve() {
  cin >> s;
  string a, b, c;
  for (int i = 1; i < s.size() - 1; ++i) {
    if (s[i] == 'a') {
      print(i); return ;
    }
  }
  cout << s[0] << ' ';
  for (int i = 1; i < s.size() - 1; ++i) cout << s[i];
  cout << ' ';
  cout << s[s.size() - 1];
  cout << endl;
}
int main() {
  int q; cin >> q;
  while (q--) {
    solve();
  }
  return 0;
}
```

---

## 作者：Jorisy (赞：0)

注意本文中的字符串 $s$ 的下标是 $0\sim n-1$。

---

一道分讨题。

首先可以想到的，若 $s_0=s_{n-1}$，则 $s_{1\sim n-2}$ 要么是三个中字典序最大的，要么是最小的。即输出 $s_0,s_{1\sim n-2},s_{n-1}$。

剩下的情况，就是 $s_0\neq s_{n-1}$，那么 $s_0$ 和 $s_{n-1}$ 必定是 $\texttt{a}$ 或 $\texttt{b}$。那中间的字符串要使得字典序最小是不一定的（因为 $\texttt{a}$ 是字典序最小的）。但是，我们可以知道的是，如果 $s_1=\texttt{b}$，那么 $s_{1\sim n-2}$ 必定是三个中字典序最大的（因为它和 $\texttt{b}$ 第一个字符相同且长度比 $\texttt{b}$ 大）。即也输出 $s_0,s_{1\sim n-2},s_{n-1}$。

最后的情况，也就是 $s_1=\texttt{a}$。我们知道，$\texttt{a}$ 是字典序最小的，因此，我们就可以让中间的字符串字典序最小（两边的字符串再怎么做也不会比 $\texttt{a}$ 小）。即输出 $s_0,s_1,s_{2\sim n-1}$。

综上，也就没有无解情况。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

void sol()
{
	string s;
	cin>>s;
	if(s[0]==s[s.size()-1])
	{
		cout<<s[0]<<' '<<s.substr(1,s.size()-2)<<' '<<s[s.size()-1]<<endl;
		return;
	}
	if(s[1]=='b')
	{
		cout<<s[0]<<' '<<s.substr(1,s.size()-2)<<' '<<s[s.size()-1]<<endl;
		return;
	}
	cout<<s[0]<<' '<<s[1]<<' '<<s.substr(2)<<endl;
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol();
 	return 0;
}
```

---

## 作者：loser_seele (赞：0)

感谢 @[CaCa_Condy](https://www.luogu.com.cn/user/320423) 提供的寄思路，让我 A 题花半个小时才做出来。

不难想到对头尾的字符串分类讨论。

分为以下 $ 4 $ 大类 $ 8 $ 小类情况：

第一种：第一个字符是 $ a $，末尾字符是 $ b $。

于是如果中间串能找到一个 $ a $ 直接分出来即可。显然 $ a $ 字典序最小。

如果找不到，证明字符串一定类似 $ abbbbb $ 这样的形式，于是分出中间一连串 $ b $ 字典序一定最大。

第二种：头尾都是 $ a $。

这个也不难讨论，同上即可。

第三种：头尾都是 $ b $。

如果中间有 $ a $ 同上，否则整个序列都是 $ b $，分出前面一整段 $ b $，则 $ a=bbbbbbb,b=b,c=b $，满足条件。

第四种：头是 $ b $，尾是 $ a $。

同第三种情况，但第二类小情况的构造是 $ a=b,b=bbbbbb,c=a $，满足条件。

有点难写，但注意到很多情况都可以中间拆出 $ a $，写起来也不是很多。

时间复杂度 $ \mathcal{O}(\sum n) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
char f(char c)
{
if(c=='a')
return 'b';
return 'a';
}
signed main()
{
int T;
cin>>T;
while(T--)
{
string s;
cin>>s;
if(s[0]==s[s.size()-1]&&s[0]=='a')
{
cout<<s[0]<<' ';
for(int i=1;i<s.size()-1;i++)
cout<<s[i];
cout<<' ';
cout<<s[s.size()-1]<<'\n';
}
else if(s[0]=='a')
{
int pos=0;
for(int i=1;i<s.size()-1;i++)
if(s[i]=='b')
pos=i;
if(pos)
{
for(int i=0;i<pos;i++)
cout<<s[i];
cout<<' ';
for(int i=pos;i<=s.size()-2;i++)
cout<<s[i];
cout<<' ';
cout<<s[s.size()-1]<<'\n';
}
else
{
for(int i=0;i<s.size()-2;i++)
cout<<s[i];
cout<<' ';
cout<<s[s.size()-2]<<' ';
cout<<s[s.size()-1]<<'\n';
}
}
else if(s[0]=='b'&&s[s.size()-1]=='b')
{
int pos=0;
for(int i=1;i<s.size()-1;i++)
if(s[i]=='a')
pos=i;
if(pos)
{
for(int i=0;i<pos;i++)
cout<<s[i];
cout<<' ';
cout<<s[pos]<<' ';
for(int i=pos+1;i<s.size();i++)
cout<<s[i];
cout<<'\n';
}
else
{
for(int i=0;i<s.size()-2;i++)
cout<<s[i];
cout<<' ';
cout<<s[s.size()-2]<<' ';
cout<<s[s.size()-1]<<'\n';
}
}
else if(s[0]=='b'&&s[s.size()-1]=='a')
{
int pos=0;
for(int i=1;i<s.size()-1;i++)
if(s[i]=='a')
pos=i;
if(pos)
{
for(int i=0;i<pos;i++)
cout<<s[i];
cout<<' ';
cout<<s[pos]<<' ';
for(int i=pos+1;i<s.size();i++)
cout<<s[i];
cout<<'\n';
}
else
{
cout<<s[0];
cout<<' ';
for(int i=0;i<s.size()-2;i++)
cout<<s[i];
cout<<' ';
cout<<s[s.size()-1]<<'\n';
}
}
}
}
```


---

## 作者：zeekliu (赞：0)

这题由于数据范围加到了 $10^4$ 和 $10^5$，所以 $O(n^2)$ 肯定要挂。

那么，考虑**构造**。

为了让那三个字符串更容易满足要求，所以其中两个字符串 $t1,t2$ 只有一个字母，因为第三个字符串 $t3$ 一定至少有一个以上的字母（$n=3$ 除外），所以一定有 $t3>t1$ 和 $t2>t1$，这样只需考虑 $t1$ 与 $t2$ 的关系。

补充说明：对于 $n=3$，`aaa`，`aab`，`aba`，`abb`，`baa`，`bab`，`bba`，`bbb`，全部成立，并不影响结果。

所以，对于 $t1$ 和 $t2$ 的位置有 $3$ 种情况：

第 $1$ 种，$t1=S_0,t2=S_{|s|-1}$；

第 $2$ 种，$t1=S_0,t2=S_1$；

第 $3$ 种，$t1=S_{|s|-1},t2=S_{|s|}$；

那么根据 $S_0$ 与 $S_1$ 和 $S_{|s|-1}$ 与 $S_{|s|}$ 的关系进行**分讨**即可，当数据时间复杂度 $O(1)$，具体部分见代码。

注：通过以下分讨可以发现，并不存在无解的情况，~~因为他样例就没有给无解的情况，那大概率一定有解。~~

```cpp
//CF1775A2 23.01.10
#include <bits/stdc++.h>
using namespace std;
string s;
int _,n;

inline void prt1()
{
    cout<<s[0]<<" ";
    for (int i=1;i<n-1;i++) cout<<s[i];
    cout<<" "<<s[n-1]<<endl;
    return;
}

inline void prt2()
{
    cout<<s[0]<<" "<<s[1]<<" ";
    for (int i=2;i<n;i++) cout<<s[i];
    cout<<endl;
    return;
}

inline void prt3()
{
    for (int i=0;i<n-2;i++) cout<<s[i];
    cout<<" "<<s[n-2]<<" "<<s[n-1]<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>_;
    while (_--)
    {
        cin>>s;
        n=s.length();
        if (s[0]!=s[1])
        {
            if (s[0]=='a') prt1();
            else prt2();
        }
        else if (s[n-1]!=s[n-2])
        {
            if (s[n-1]=='a') prt1();
            else prt3();
        }
        else 
        {
            if (s[0]==s[n-1]) prt1();
            else prt2(); 
        }
    }
    exit(0);
}
```

---

## 作者：yzy4090 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1775A2)  
本题希望我们将仅含有 $\tt a$ 和 $\tt b$ 的字符串 $S$ $(3\leq|S|\leq2\times10^5)$ 分成三个子串 $a,b,c$，使得条件 $1$ $(a\leq b$ 与 $c\leq b)$ 与条件 $2$ $(b\leq a$ 与 $b\leq c)$ 中至少有一个成立，并给出一种方案。  

我们可以先试玩一些 $S$，找到规律：

当 $S_0=\texttt a$ 时有如下几种情况：

- $S$ 形如 $\tt aaa...aaa$，此时一种方案为 $\tt a\ aa...aa\ a$。  
- $S$ 形如 $\tt aa...aab$，此时一种方案为 $\tt aa...a\ a\ b$。
- $S$ 形如 $\tt aa...aabb...bb$，此时一种方案为 $\tt aa...aa\ bb...b\ b$。
- 其他，此时一种方案为 $\tt a...\ b...\ a...$。  

对于 $S_0=\texttt b$ 的讨论类似。至此我们可以写出代码：  

```cpp
#include<iostream>
#include<cstring>
using namespace std;
void process(){
	string s;cin>>s;
	if(s[0]=='a'){
		int fira=0,firb=0;
		for(int i=1;i<(int)s.size();i++){
			if(s[i]=='b'&&!firb)firb=i;
			if(firb&&s[i]=='a'&&!fira)fira=i;
			if(firb&&fira)break;
		}
		if(fira==0&&firb==0){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==0)putchar(' ');
				if(i==(int)s.size()-2)putchar(' ');
			}
			return;
		}//aaaaaaaaa->a aaaaaaa a
		else if(fira==0&&firb!=0&&firb!=(int)s.size()-1){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==firb-1)putchar(' ');
				if(i==(int)s.size()-2)putchar(' ');
			}
			return;
		}//aaaabbbbb->aaaa bbbb b
		else if(fira==0&&firb!=0&&firb==(int)s.size()-1){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==firb-2)putchar(' ');
				if(i==(int)s.size()-2)putchar(' ');
			}
			return;
		}//aaaab->aaa a b
		else{
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==firb-1)putchar(' ');
				if(i==fira-1)putchar(' ');
			}
			return;
		}
	}//aabbab->aa bb ab
	else{
		int fira=0,firb=0;
		for(int i=1;i<(int)s.size();i++){
			if(s[i]=='a'&&!fira)fira=i;
			if(fira&&s[i]=='b'&&!firb)firb=i;
			if(fira&&firb)break;
		}
		if(firb==0&&s[1]=='a'){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==0)putchar(' ');
				if(i==1)putchar(' ');
			}
			return;
		}//baaaaaaa->b a aaaaaa
		if(fira==0&&firb==0){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==0)putchar(' ');
				if(i==(int)s.size()-2)putchar(' ');
			}
			return;
		}//bbbbbbbb->b bbbbbb b
		else if(firb==0&&fira!=0){
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==0)putchar(' ');
				if(i==(int)s.size()-2)putchar(' ');
			}
			return;
		}//bbbba->b bbb a
		else{
			for(int i=0;i<(int)s.size();i++){
				putchar(s[i]);
				if(i==fira-1)putchar(' ');
				if(i==firb-1)putchar(' ');
			}
			return;
		}//bbaaba->bb aa ba
	}
	return;
	
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		process();
		puts("");
	}
	return 0;
}
```


---

