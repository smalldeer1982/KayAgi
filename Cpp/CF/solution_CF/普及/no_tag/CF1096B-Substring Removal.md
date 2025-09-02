# Substring Removal

## 题目描述

You are given a string $ s $ of length $ n $ consisting only of lowercase Latin letters.

A substring of a string is a contiguous subsequence of that string. So, string "forces" is substring of string "codeforces", but string "coder" is not.

Your task is to calculate the number of ways to remove exactly one substring from this string in such a way that all remaining characters are equal (the number of distinct characters either zero or one).

It is guaranteed that there is at least two different characters in $ s $ .

Note that you can remove the whole string and it is correct. Also note that you should remove at least one character.

Since the answer can be rather large (not very large though) print it modulo $ 998244353 $ .

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

Let $ s[l; r] $ be the substring of $ s $ from the position $ l $ to the position $ r $ inclusive.

Then in the first example you can remove the following substrings:

- $ s[1; 2] $ ;
- $ s[1; 3] $ ;
- $ s[1; 4] $ ;
- $ s[2; 2] $ ;
- $ s[2; 3] $ ;
- $ s[2; 4] $ .

In the second example you can remove the following substrings:

- $ s[1; 4] $ ;
- $ s[1; 5] $ ;
- $ s[1; 6] $ ;
- $ s[1; 7] $ ;
- $ s[2; 7] $ ;
- $ s[3; 7] $ .

In the third example you can remove the following substrings:

- $ s[1; 1] $ ;
- $ s[1; 2] $ ;
- $ s[2; 2] $ .

## 样例 #1

### 输入

```
4
abaa
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
aacdeee
```

### 输出

```
6```

## 样例 #3

### 输入

```
2
az
```

### 输出

```
3```

# 题解

## 作者：IGA_Indigo (赞：5)

## 题意分析
这道题实质上是一个字符串的灵活运用，意思就是给你一个字符串，问你有多少种删子串的方式能够把他删成一个字符完全相同的串或是空串（注意字串要连续）。
## 大体思路
一个字符串可以分为好几种类型，但因为字串是连续的，所以只有首尾连续相同字符的字串可能被保留，那我们就分两类讨论，一种是首尾一样的，一种是首尾不同的。我们可以遍历两次字符串，一次从前往后扫，一次从后往前扫，设 $t$ 代表从头到尾相同的字母个数，$w$ 代表从尾到前相同的字母个数。

### 第一种
第一种的话，字串首尾相同，那么有可能串完全相等，也有可能中间夹杂着一些乱七八糟的字符。

例子就有 ```aaaaaa``` 和 ```aaabccccbaaa``` 两种，第二种中间的字符串怎么也不可能取到，因为字串要求连续。删左边有 $0$ 到 $t$ 共 $t+1$ 种，删右边有 $0$ 到 $w$ 共 $w+1$ 种，因为前后相同，所以方案数就是 $(t+1)\times(w+1)$。可以自己推一下。
### 第二种
第二种我们要考虑保留前面的或后面的，前面就有 $t$ 种删法，后面就有 $w$ 种删法，再加上全删掉的方法，就有 $t+w+1$ 种删法。可以自己推一下。
## 注意事项
别忘了取模，别忘了开 long long。
## Code
放下代码，便于理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	s=' '+s;//下标从一开始便于操作 
	if(s[1]==s[n]){//第一种情况 
		long long t=0,w=0;
		for(int i=1;i<=n;i++){//从前往后扫 
			if(s[i]==s[1]){
				t++;
			}//一样的就增加个数 
			else{
				break;//不一样就跳出 
			}
		}
		for(int i=n;i>=1;i--){//从后往前扫 
			if(s[i]==s[1]){
				w++;//一样就增加个数 
			}
			else{
				break;//不一样就跳出 
			}
		}
		cout<<(t+1)*(w+1)%998244353;//计算答案，别忘了取模 
	}
	else{//第二种情况 
		long long t=0,w=0;
		for(int i=1;i<=n;i++){//从前往后扫
			if(s[i]==s[1]){ 
				t++;
			}
			else{
				break;//不一样就跳出 
			}
		}
		for(int i=n;i>=1;i--){//从后往前扫 
			if(s[i]==s[n]){
				w++;//一样就增加个数 
			}
			else{
				break;//不一样就跳出 
			}
		}
		cout<<(t+w+1)%998244353;//计算答案，别忘了取模 
	}
	return 0;
}
```

---

## 作者：_Qer (赞：3)

先将给定的字符串分类  

1. 首尾字符不同  
2. 首尾字符相同  

这两种类型的字符串用不同方法做  

----

首先，对于任意的字符串，由于需要删去的是子串，必须连续，所以最后剩下的要么是空串，要么一定含有最左边或最右边的字符，也就是说，最后剩下的只有3种情况，空、若干与首字符相同的字符、若干与尾字符相同的字符  
（题目保证至少2种字符）

----

然后按照上面的分类来看：  

#### 1.首尾字符不同

举个栗子

> 7  
> aacdeee

根据前面的说法，中间的`cd`必须删去，于是可以简化成  

> 5  
> aaeee

要求所有字符相同，所以最后要么剩下`a`，要么为`e`

- 当剩a时，为`aa`，`a`，所有`e`都要删，由于要连续，所以第一个一定留，也就是有2种情况（2删，2不删）。可以发现，有$n$个`a`时方法数一定为$n$

- 剩e时同理

- 最后加上空串

总结一下，方法数一定是两种字符数之和加一，可以自己验证一下


#### 2. 首尾字符相同 

栗子  

> 4  
> abaa

显然，中间的其他字符必须删去

然后来看左半部分（以中间的其他字符为基准，下同）  
有2种情况，即`a`删或不删  

看右边  
有3种情况（显然，不细说了）

似乎有一点规律？

假设某侧有$n$个`a`，可以删去$[0,n]$任意个字符，也就是有$n+1$种删法  
两侧都一样，于是相乘即可，同时注意，这里包括了空串的情况，不用加  

----

最后，注意答案要取模，~~血的教训~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    string s;
    cin >> n >> s;
    if (s[0] == s[n - 1]) {
        char t = s[0];
        long long c1 = 1, c2 = n - 2;
        while (s[c1] == t) { ++c1; }
        while (s[c2] == t) { --c2; }
        c2 = n - c2;
        cout << (c1 + 1) * c2 % 998244353 << endl;
    } else {
        long long c1 = 1, c2 = n - 2;
        while (s[c1] == s[0]) { ++c1; }
        while (s[c2] == s[n - 1]) { --c2; }
        cout << (c1 + (n - c2)) % 998244353 << endl;
    }
    return 0;
} 
```



---

## 作者：一扶苏一 (赞：1)

## Description

给定一个长度为 $n$ 的字符串，请你从中去除一个子串，使得剩下的串要么为空，要么字符完全相同，输出方案数模 $998244353$

## Input

第一行是字符串长度 $n$

下面一行是一个长度为 $n$ 的字符串

## Output

输出一行一个整数，代表答案对 $998244353$ 取模的结果

## Hint

$2~\leq~n~\leq~2~\times~10^5$

保证给出的字符串全是小写字母且至少含有两种字符

## Solution

考虑删掉一个子串后，左边的串的字符必须相同，右边的串的字符必须相同，同时左右两侧的串的字符必须相同。

我们先考虑截完以后两侧都不为空的情况。

假设从右往左数有连续 $k$ 位和原串第一位相同，于是以左侧所有连续相同（即左侧的串为 $[1,1][1,2][1,3]~\dots$ )的串的后面一位作为左端点，显然右端点都有 $k$ 个位置可以对应。于是枚举一下左端点，求出合法的左端点个数再乘 $k$ 即可。

考虑左侧为空的情况，那么右侧显然有 $k~+~1$ 个位置作为右端点（因为包括了右侧也为空的情况）

右侧为空的情况同理。注意这两次统计都统计了两侧都为空的情况，所以答案要减去 $1$

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;
const int MOD = 998244353;

int n;
ll ans;
char MU[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) do {MU[i] = IPT::GetChar();} while ((MU[i] > 'z') || (MU[i] < 'a'));
	MU[0] = MU[1]; MU[n + 1] = MU[n];;
	int pos = n; while (MU[pos] == MU[0]) --pos;
	int k = n - pos;
	for (rg int i = 1; i <= n; ++i) if (MU[i] == MU[i - 1]) {
		++ans;
	} else break;
	ans = (ans * k) % MOD;
	++ans;
	for (rg int i = 1; i <= n; ++i) if (MU[i] == MU[i - 1]) ++ans; else break;
	for (rg int i = n; i; --i) if (MU[i] == MU[i + 1]) ++ans; else break;
	qw(ans % MOD, '\n', true);
	return 0;
}
```



---

## 作者：Ryan_Adam (赞：0)

# CF1096B Substring Removal 题解
## 分析
每当你在字符串中删去一个子串，就会在左边和右边留下两个字符串，这两个字符串可以为空。问题就转化成了求字符串的前缀和后缀的排列，其中只能含有一种字母。

很简单，用 $l,r$ 分别统计字符串 $s$ 的最大只包含一种字母的前缀及后缀长度，结果就是乘法原理。左端可以剩下，前零个，前一个，前两个，…，前 $l$ 个，右端可以剩下后零个，后一个，后两个，……，后 $r$ 个。结果就是 $(l+1)\times (r+1)$。

需要注意的是，当 $s$ 首尾不一样时，只能选头、尾或者空，答案应是 $l+r+1$。

**坑点：**
- **不开`long long`见祖宗**
- **记得模**

## 示例代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace Raiden
{
    const int mod=998244353;
    signed work()
    {
        int n;
        string s;
        cin>>n>>s;
        int l=1,r=1;
        for(int i=0;i<n-1;i++)
        {
            if(s[i]==s[i+1])
            {
                l++;
            }
            else
            {
                break;
            }
        }
        for(int i=n-1;i>0;i--)
        {
            if(s[i]==s[i-1])
            {
                r++;
            }
            else
            {
                break;
            }
        }
        if(s[0]!=s[n-1])
        {
            cout<<(l+r+1)%mod<<endl;
        }
        else
        {
            cout<<(l+1)*(r+1)%mod<<endl;
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

仔细想想我们可以发现，如果我们最后要保留到只剩某字母，这个字母必须出现在第一个或者最后一个，不然没有办法在只删去一个子串的情况下保留这一个字母。

所以我们只考虑第一个字母或最后一个字母的情况，以开头为例，我们要找到这个字母分别在开头和结尾的连续个数，记为 $a$ 和 $b$，因为左边有 $a+1$ 种留的情况，右边也有 $b+1$ 种保留的情况，所以这个字母对答案的贡献为 $(a+1)\times(b+1)$，然后要注意第一个字母和最后一个是否相同，如果不同，记得将两个答案加起来的结果减一，也就是全部删掉的情况。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,ans;
string s;
signed main()
{
	cin>>n>>s;
	int cnt=1;
	for(int i=n-1;s[i]==s[0];i--)cnt++;
	for(int i=0;;i++)
	{
		ans=(ans+cnt)%mod;
		if(s[i]!=s[0])break;
	}
	if(s[0]!=s[n-1])
	{
		cnt=1;
		for(int i=0;s[i]==s[n-1];i++)cnt++;
		for(int i=n-1;;i--)
		{
			ans=(ans+cnt)%mod;
			if(s[i]!=s[n-1])break;
		}
		ans=(ans+mod-1)%mod;//防止对-1取模，不能直接减，虽然没什么用
	}
	cout<<ans;
}
```

---

## 作者：ljk_Elaina (赞：0)

只要分三种情况：
1. 所有字母都一样
1. 头尾字母一样，中间有不一样的
1. 头尾不一样

$flag$是用来判断是否所有都一样的（$True$为一样 $False$为不一样）

如果头尾一样，乘法原理：（头+1）×（尾+1）（加一是因为可以全部去掉）

如果不一样，加法原理：头+尾+1 ，要么全去头，要么全去尾，（可以空串再加一）

最后边忘了$MOD$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD=998244353;
ll n;
string str;

int main() {
	cin>>n;
	cin>>str;
	bool flag=true;
	ll c1=1,c2=1;
	for(int i=1; i<n; i++) {
		if(str[i]==str[i-1]) c1++;
		else {
			flag=false;
			break;
		}
	}
	if(flag) {
		printf("%I64d\n",((n+1)*n/2)%MOD);
		return 0;
	}
	for(int i=n-2;i>0;--i){
		if(str[i]==str[i+1]) c2++;
		else break;
	}
	if(str[0]==str[n-1]) printf("%I64d\n",((ll)(c1+1)*(ll)(c2+1))%MOD);
	else printf("%I64d\n",((ll)c1+(ll)c2+(ll)1)%MOD);
	return 0;
}
```

---

## 作者：LJC00118 (赞：0)

情况 1：所有字母都相同，输出 $ n * (n - 1) / 2 $ 即可
情况 2：左边有连续 $ x $ 个字母相同，右边有 $ y $ 个，第一个字母和最后一个字符相同，输出 $ (x + 1) * (y + 1) $
情况 3：左边有连续 $ x $ 个字母相同，右边有 $ y $ 个，第一个字母和最后一个字符不同，输出 $ x + y + 2 - 1 $，最后的 $ -1 $ 是因为整个串被算了 $ 2 $ 次

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 2e5 + 5, md = 998244353;

char c[N];
int cnt[23333];
int n, cut1 = -1, cut2 = -1;

inline int mul(int x, int y) { return (ll)x * y % md; }

int main() {
	read(n); scanf("%s", c + 1);
	for(register int i = 2; i <= n; i++) if(c[i] != c[i - 1]) { cut1 = i - 1; break; }
	for(register int i = n - 1; i >= 1; i--) if(c[i] != c[i + 1]) { cut2 = i + 1; break; }
	if(cut1 == -1) cout << (ll)n * (n - 1) / 2 % md << endl;
	else if(c[1] == c[n]) cout << mul(cut1 + 1, n - cut2 + 2) << endl;
	else cout << cut1 + 1 + n - cut2 + 2 - 1 << endl;
	return 0;
}
```

---

