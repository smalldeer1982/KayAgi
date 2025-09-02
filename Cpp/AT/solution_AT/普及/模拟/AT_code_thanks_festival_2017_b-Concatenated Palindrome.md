# Concatenated Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-thanks-festival-2017/tasks/code_thanks_festival_2017_b

英小文字からなる文字列 $ S $ が与えられます。   
 $ S $ の後ろに英小文字からなる任意の文字列 $ T $ (空文字列も含む)を連結することで、回文にしたいです。   
 条件を満たす文字列 $ T $ のうち、$ T $ の最小の長さを求めてください。

## 说明/提示

### 制約

- $ 1≦|S|≦50 $ ($ |S| $ は文字列 $ S $ の長さ)
- 文字列 $ S $ は英小文字から成る。

### Sample Explanation 1

$ T="dcba" $ とすると、文字列 $ S $ と 文字列 $ T $ を順番に連結した文字列は回文になります。 この文字列 $ T $ は条件を満たす中で最小の長さであるため、答えは $ 4 $ です。

### Sample Explanation 2

文字列 $ S $ は回文であるため、文字列 $ T $ は空文字列でも条件を満たします。 空文字列の長さは $ 0 $ であるため、答えは $ 0 $ です。

## 样例 #1

### 输入

```
abcde```

### 输出

```
4```

## 样例 #2

### 输入

```
level```

### 输出

```
0```

## 样例 #3

### 输入

```
codethanksfestival```

### 输出

```
17```

## 样例 #4

### 输入

```
abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcb```

### 输出

```
1```

# 题解

## 作者：XKqwq (赞：3)

#### 由于数据范围过小，可以直接暴力。

首先拿样例 $1$ 理解题意：

要往字符串 $\texttt{abcde}$ 后添加 一个字符串，使得字符串对称。

我们可以：
1. 从头截取若干个字符串。

2. 反转后拼到后面。

3. 判断是否对称，输出对称时拼接的字符串的长度即可。


详细： （ 这里 < str >表示倒过来的字符串 str ）

长度为 $1$ ： $\texttt{abcde + <a>} \ =\  \texttt{abcdea}$ , 不对称。

长度为 $2$ ： $\texttt{abcde + <ab>} \ =\  \texttt{abcdeba}$ , 不对称。
  
长度为 $3$ ： $\texttt{abcde + <abc>} \ =\  \texttt{abcdecba}$ , 不对称。
  
长度为 $4$ ： $\texttt{abcde + <abcd>} \ =\  \texttt{abcdedcba}$ , 对称。
  
### $\texttt{Code:}$
  
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define endline putchar('\n')
#define ri register int
#define ll long long

using namespace std;

bool rightstr(string s){ //判断是否对称
	int l=s.size();
	for(int i=0;i<l/2;i++){
		if(s[i]!=s[l-i-1]) return false;
	}
	return true;
}
string changestr(string s){ //把字符串倒过来 （为了易懂就不用自带的函数了）
	int l=s.size();
	for(int i=0;i<l/2;i++){
		swap(s[i],s[l-i-1]);
	}
	return s;
}
string findstr(string s,int n){ //截取字符串的一段
	string t;
	for(int i=0;i<n;i++) t+=s[i];
	return changestr(t);
}


string s;
int main(){
	cin>>s;
	int l=s.size();
	
	//首先判断是否对称
	if(rightstr(s)){
		puts("0");
		endline;
		return 0;
	}
	//需要拼接字符串 
	for(int i=1; i<l ;i++){
		if(rightstr(s+findstr(s,i))){
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
```
                     
  

---

## 作者：Night_sea_64 (赞：1)

本蒟蒻又来写题解了。。。这道题~~很水~~，主要考察的是字符串的基本操作。。。

题目内容很简单，就是有一个字符串 $s$，在后面拼接一个字符串 $t$ 之后就变成回文串。求 $t$ 的最短长度。

本来还以为这个题应该做一些优化，后来一看数据范围 $1≤|s|≤50$，才发现原来暴力就能解决。。。

怎么暴力呢？很显然枚举的是 $t$ 的长度，这样 $t$ 肯定就能确定下来，就是从 $s_0$ 开始取一个长度为 $t$ 的子串，然后再把字符顺序颠倒。比如样例里的 $\texttt{abcde}$，枚举到长度为 $4$ 的时候，取的子串是 $s_0-s_3$ 的子串，也就是 $\texttt{abcd}$，然后把字符顺序颠倒变成 $\texttt{dcba}$。这时得到的就是 $t$。把它拼接到 $s$ 的后面，变成 $\texttt{abcdedcba}$，正好是一个回文串。

如果还没有理解，请看一看具体的代码实现。AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string rev(string s)//把字符顺序颠倒过来的函数。
{
    string t;
    for(int i=0;i<s.size();i++)t=s[i]+t;
    return t;
}
int main()
{
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++)//枚举t的长度。
    {
        string t=rev(s.substr(0,i));
        if(rev(s+t)==s+t)//回文串满足颠倒过来的串和原串一样，所以顺便用这个函数判断回文了。
        {
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}
```

一道黄题就这么 AC 了！！！求各位 dalao 点个赞再走！！！

---

## 作者：lkjzyd20 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT3637)
___
### 思路

因为拼接后的字符串满足对称，所以这道题其实就是要求 $i \sim len$ 的字符串是否回文。

本题中字符串 $S$ 的长度很短，所以可以直接暴力，时间复杂度为 $O(n^2)$。

```cpp
//#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f,MOD=1e9+7;
#define pu putchar
#define endl puts("")
//#define int __int128
//#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define me0(a); memset(a,0,sizeof a);
#define me3(a); memset(a,0x3f,sizeof a);
#define PII pair<int,int>
void read(int &n){char c,w=1;for(;48>c||c>57;c=getchar())
w=c==45?-1:1;for(n=0;47<c&&c<58;c=getchar())n=n*10+c-48;n*=w;
}void write(int x){if(x<0)pu(45),x=-x;char c[41],s=0;
for(;x;)c[s++]=x%10,x/=10;if(!s)pu(48);for(;s--;)pu(c[s]+48);
}void debug(int n){printf("\tdebug:\t"); write(n); pu('\t');}
const int MAXN=2e5+10;
int len;
char s[60];
bool check(int x){
	rep(i,0,(len-x+1)/2){
		if(s[x+i]!=s[len-i]){
			return 0;
		}
	}return 1;
}main(){
	for(;;){
		char str=getchar();
		if(str=='\n'){
			break;
		}else{
			s[++len]=str;
		}
	}rep(i,1,len){
		if(check(i)) {
			write(i-1); endl;
			return 0;
		}
	}
}
```
### [$AC$ 记录](https://www.luogu.com.cn/record/86822512)
___

### 完结撒花 $\sim\sim\sim$

---

## 作者：zjc5 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT3637)

**思路：**

这道题其实就是要求后缀中最长的回文串。

本题中字符串 $S$ 的长度很短，所以可以直接暴力。

代码时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[60];
bool check(int a,int len){
	for(int j=0;j<=(len-a+1)/2;j++)
		if(s[a+j]!=s[len-j])
			return false;
	return true;
}
int main() {
	cin>>(s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
		if(check(i,len)) {
			cout<<i-1;
			return 0;
		}
}
```

---

## 作者：CaoXian (赞：1)

## AT3637 Concatenated Palindrome 题解

先分析一下题目，要求在给出字符串**末尾**添加一个字符串使新的字符串回文。

假设要添加的最短字符串的长度为 `l` ，那么一定是原字符串去掉长度为 `l` 的前缀就可以回文。因为在回文字符串中，两个相对的位置添加与删除相同的字符，回文的性质不会变。

那么要删除的前缀最短，就要剩下的回文字符串最长，所以题目就变成了：给你一个字符串，求出它最长的后缀回文子串，输出原字符串长度减去得到的子串的长度。

数据范围不大，直接暴力枚举，判断即可。

Code：
```cpp
#include <stdio.h>
#include <string.h>
char s[64];
int len;
inline bool check(int l, int r) {//判断回文
	while(l <= r) {
		if(s[l] != s[r]) return false;
		++l, --r;
	}
	return true;
}
int main() {
	fgets(s + 1, sizeof(s), stdin);
	len = strlen(s + 1) - 1;
	for(int i = 1; i <= len; ++i) if(check(i, len)) return 0 * printf("%d", i - 1);//暴力枚举
	return 0;
}
```

还拿了个最优解。。

---

## 作者：RioBlu (赞：1)

先看看翻译
```txt
输入一个字符串S，任意在字符串S后面拼接字符串T，拼接后的字符串满足对称

问$T$的长度最小是多少(注：可为0)

```
思路：寻找对称中心，看看哪里是对称中心

比如说$akioi$，此时$'o'$的位置可以成为对称中心
```
#include<bits/stdc++.h>
using namespace std;
string a;
long long A,ans=99999999;//初始化
long long PD(int l,int r)
{
	while(l!=-1&&A>r)
	{
		if(a[l]!=a[r])return 99999999;//不对称
		l--,r++;
	}
	return l+1;//还差多少东西可以形成对称
}
int main()
{
	cin>>a;
	A=a.size();
	for(int s=A/2;s<A;s++)
	{
		ans=min(PD(s,s),ans);
		if(!(A%2==1&&s==A/2))//如果不加上llb就输出0
		ans=min(PD(s-1,s),ans);
	}
	cout<<ans<<endl;
}
```

---

## 作者：hanyuchen2019 (赞：0)

### 2021-11-27：修改煞笔措辞和一些错字

看着简单，做着毒瘤。(代码相对于楼上大佬可能有点长，勿喷)

```cpp
#include<iostream>
#include<cstring>//提供string类型
#include<algorithm>//提供min函数
using namespace std;
int main()
{
	string s;
	cin>>s;//读入
	int l=s.length(),ans1=999999,ans2=999999;
	//字符串长度，以及两个存储答案的变量，待会儿要取最小值，所以初始化为INF
```
下面这一部分的两个大 `for` 循环，用来枚举答案，外层循环枚举“对称轴”的位置，内层循环用来枚举对称轴两边的字母，如果两边有不同，直接退出，直到右边枚举到头。

第一个大 `for` 循环用来枚举对称轴在字母上的情况。
```cpp
	for(int i=l/2;i<l;i++)//对称轴当然只能在后半部分啦~
	{
		bool f=true;//标记是否有不同
		for(int j=1;j<l-i;j++)//j是指当前两个位置离“对称轴”的距离
		{
			if(s[i+j]!=s[i-j])
			{
				f=false;
				break;//不一样，再见~
			}
		}
		if(f)//如果以i为对称轴的后半段对称，
		{
			ans1=i+i-l+1;//要添加的部分就是i-j。（j最后等于l-i+1）
			break;
		}
	}
```
第二个大 `for` 循环用来枚举对称轴在两个字母中间的情况。
```cpp
	for(int i=l/2;i<l;i++)
	{
		bool f=true;
		for(int j=0;j<l-i;j++)//离“对称轴”的距离为j+0.5
		{
			if(s[i+j-1]!=s[i-j])
			{
				f=false;
				break;
			}
		}
		if(f)
		{
			ans2=i+i-l;//要减掉2个0.5（坑人！）
			break;
		}
	}
```
后面是输出。
```cpp
	if(ans1==999999&&ans2==999999)//根本没有对称轴
	{
		cout<<l-1<<endl;//直接输出l-1
	}
	else cout<<min(ans1,ans2);//否则输出最小值
	return 0;
```

## 脚造 HACK 数据几组 

### #1
`input:abb`

`output:1`
### #2
`input:abac`

`output:3`

bye~

---

