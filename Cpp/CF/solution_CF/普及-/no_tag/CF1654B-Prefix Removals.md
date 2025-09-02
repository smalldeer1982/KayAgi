# Prefix Removals

## 题目描述

You are given a string $ s $ consisting of lowercase letters of the English alphabet. You must perform the following algorithm on $ s $ :

- Let $ x $ be the length of the longest prefix of $ s $ which occurs somewhere else in $ s $ as a contiguous substring (the other occurrence may also intersect the prefix). If $ x = 0 $ , break. Otherwise, remove the first $ x $ characters of $ s $ , and repeat.

A prefix is a string consisting of several first letters of a given string, without any reorders. An empty prefix is also a valid prefix. For example, the string "abcd" has 5 prefixes: empty string, "a", "ab", "abc" and "abcd".

For instance, if we perform the algorithm on $ s = $ "abcabdc",

- Initially, "ab" is the longest prefix that also appears somewhere else as a substring in $ s $ , so $ s = $ "cabdc" after $ 1 $ operation.
- Then, "c" is the longest prefix that also appears somewhere else as a substring in $ s $ , so $ s = $ "abdc" after $ 2 $ operations.
- Now $ x=0 $ (because there are no non-empty prefixes of "abdc" that also appear somewhere else as a substring in $ s $ ), so the algorithm terminates.

Find the final state of the string after performing the algorithm.

## 说明/提示

The first test case is explained in the statement.

In the second test case, no operations can be performed on $ s $ .

In the third test case,

- Initially, $ s = $ "bbbbbbbbbb".
- After $ 1 $ operation, $ s = $ "b".

In the fourth test case,

- Initially, $ s = $ "codeforces".
- After $ 1 $ operation, $ s = $ "odeforces".
- After $ 2 $ operations, $ s = $ "deforces".

## 样例 #1

### 输入

```
6
abcabdc
a
bbbbbbbbbb
codeforces
cffcfccffccfcffcfccfcffccffcfccf
zyzyzwxxyyxxyyzzyzzxxwzxwywxwzxxyzzw```

### 输出

```
abdc
a
b
deforces
cf
xyzzw```

# 题解

## 作者：c20231020 (赞：7)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1654B)

[codeforces](https://codeforces.ml/contest/1654/problem/B)

### 题目大意
有一个字符串 $s$，对其进行如下操作：

+ 令 $x$ 表示 $s$ 最长并在 $s$ 的其他地方出现过的前缀的长度。如果 $x=0$，停止。否则，删除 $s$ 的前 $x$ 个字符。

输出操作完成后的字符串。

### 思路
其实，如果在 $s$ 中有一个前缀满足要求，那么此前缀中每个字符都必然在之后的字符串中出现过。所以，我们可以一个一个删，直到不能删为止。

例子：$s=\texttt{abcbadabc}$。
按照题目中的要求做如下操作：

$\texttt{\underline{abc}badabc}$

$\texttt{\underline{b}adabc}$

$\texttt{\underline{a}dabc}$

所以结果为 $\texttt{dabc}$。

按照思路，可以这样：

$\texttt{a}$ 在后面存在，$s$ 变成 $\texttt{bcbadabc}$。

$\texttt{b}$ 在后面存在，$s$ 变成 $\texttt{cbadabc}$。

$\texttt{c}$ 在后面存在，$s$ 变成 $\texttt{badabc}$。

$\texttt{b}$ 在后面存在，$s$ 变成 $\texttt{adabc}$。

$\texttt{a}$ 在后面存在，$s$ 变成 $\texttt{dabc}$。

这样结果还是 $\texttt{dabc}$。

时间复杂度：$O(\sum{n})$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,i;
char s[200010];
map<char,int> mp;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		l=strlen(s+1);
		for(i=1;i<=l;i++)mp[s[i]]++;//记录每个字符是否出现过
		for(i=1;i<=l;i++){
			if(mp[s[i]]==1)break;//判断后面是否还有此字符
			mp[s[i]]--;//删去这个字符
		}
		printf("%s\n",s+i);
		mp.clear();
	}
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

[题目传送门](https://luogu.com.cn/problem/CF1654B)

首先我们可以发现，一次直接删掉前缀和一个一个字符删并没有区别。如果一个字符在前缀中被删掉，则后面一定有与这个字符相同的，所以它早晚会被删掉。

我们拿 $\mathtt{abcabdc}$ 来举例：

第一个字符是 $\mathtt{a}$，后面有，删除，字符串变为 $\mathtt{bcabdc}$；

第二个字符是 $\mathtt{b}$，后面有，删除，字符串变为 $\mathtt{cabdc}$；

第三个字符是 $\mathtt{c}$，后面有，删除，字符串变为 $\mathtt{abdc}$；

第四个字符是 $\mathtt{a}$，后面没有，停止。答案为 $\mathtt{abdc}$。

但如果真的这样做的话，最坏时间复杂度是 $O(n^2)$，可能会超时。

但是“正难则反”，我们可以从后面遍历，同时用 $t$ 数组来记录字符是否出现过。此时最前面的“后面没有”的字符和它后面的字符就会被保留，我用了变量 $m$ 来记录。最后输出下标 $m$ 到 $n-1$ 的字符就可以了。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,m;
bool t[27];
string s;
int main()
{
	cin>>T;
	getline(cin,s);
	while(T--)
	{
		getline(cin,s);
		for(int i=1;i<=26;i++)t[i]=0;
		for(int i=s.size()-1;i>=0;i--)if(!t[s[i]-96])t[s[i]-96]=1,m=i;
		for(int i=m;i<s.size();i++)printf("%c",s[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给定一个字符串 $s$，定义 $x$ 为 $s$ 中出现过不止一次的最长的前缀，把 $x$ 从 $s$ 中删掉，输出经过所有操作之后的 $s$。 

#### 思路分析


------------
显然，如果一个字符串的前缀出现过不止一次并且是最长的，那么这个前缀的前缀必定出现过不止一次且是这个前缀中最长的前缀，以此类推，可以发现每一个字符（由于都是小写字母）如果出现过不止一次就可以直接删去。按照此流程判断该字符串上的每一位是否满足删去条件，模拟即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
const int N = 2e5 + 10;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
char s[N];
int num[N];
signed main(){
	int T = read();
	while(T--){
        scanf("%s",s+1);
        s[0] = 'A';
        memset(num,0,sizeof num);
        int n;
        n = strlen(s+1);
        for(int i=1;i<=n;i++){
            num[s[i] - 'a' + 1]++;
        }
        for(int i=1;i<=n;i++){
            if(num[s[i] - 'a' + 1] > 1 && s[i-1] == 'A'){
                num[s[i] - 'a' + 1]--;
                s[i] = 'A';
            } 
        }
        for(int i=1;i<=n;i++){
            if(s[i] != 'A'){
                putchar(s[i]);
            }
        }
        printf("\n");
	} 
	return 0;
}
```


---

## 作者：lsj2009 (赞：0)

## 题目大意
给定字符串 $s$，每次删除最大前缀 $a$ 满足删除后的 $s$ 不包含 $a$，问最终的 $|s|$。
## 思路
其实只需要每次删除 $s$ 的首字符即可直至不满足条件即可。

为什么呢？首先假定 $a$ 为满足条件的最大前缀，那么有 $3$ 种情况：

- $|a|\ge 2$。$a$ 肯定满足其任意一个字符均在删除后的 $s$ 中出现过（若满足也不一定符合条件）。

- $|a|=1$。此时 $a$ 即 $s$ 的第一个字符。

- $|a|=0$。此时无法继续删除。

可以看到，如果我们采用每次删除 $s$ 首字符的情况那么一定满足后两者的情况。那么第一种呢？可以看见，可以删除 $s$ 的首字符是 $a$ 满足条件的必须情况，也就是说，如果可以删除 $a$ 那么就一定满足可以删除 $s$ 的第一个字符，如果不满足，那么 $s$ 将的长度将缩小，直至满足情况为止，将变成第二或第一种的情况。

我们也可以使用数学归纳法，将话说的标准一点：


- $|a|=0$ 时满足条件；

- $|a|=1$ 时满足条件；

- 当 $|a|-1$ 满足条件时，那么删除除 $a$ 的最后一个字符外的所有字符，如果可以继续删除则继续删除，反之不可以删除，停止删除。满足条件。

- 对于每一个 $|a|$ 都满足条件，证毕。

至于判断是否可以删除首字母，我们可以采用桶排解决。

## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template <typename T> inline void read(T& x) {
	x=0; T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x); read(arg...);
}
int power(int a,int b) { 
	int ans=1;
	do {
		if(b&1) ans*=a; a*=a;
	} while(b>>=1);
	return ans;
}
int T,cnt[128];
signed main() {
	read(T);
	while(T--) {
		memset(cnt,0,sizeof(cnt));
		string s;
		cin>>s;
		_for(i,0,s.size()-1)
			++cnt[s[i]];
		int k=-1;
		_for(i,0,s.size()-1)
			if(cnt[s[i]]>1)
				--cnt[s[i]],k=i;
			else
				break;
		_for(i,k+1,s.size()-1)
			putchar(s[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先我们记录字符串里每一个字符的最后出现的地方。

很明显，如果一个字符是在这个字符里最后一次出现（我们称之为“最后字符”），那么它和它后面的所有字符都不可能被删除。

那么，我们就找到所有“最后字符”中最左边的那个，将其（不含）前方的所有字符删除。我们可以证明，一个一个地删除它们总是可行的。

然后输出结果即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
char s[max_n+20];
int f[26];
int ans;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=1;i<=n;++i)f[s[i]-'a']=i;
        ans=1;
        for(int i=1;i<=n;++i){
            if(f[s[i]-'a']==i){
                ans=i;
                break;
            }
        }
        for(int i=ans;i<=n;++i)printf("%c",s[i]);
        printf("\n");
    }
    return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/72204753)

By **dengziyue**

---

## 作者：Argon_Cube (赞：0)

比赛的时候成功看错了题，看成了只移除开头的一个字符。

然而很显然这对答案并不影响，我还是对了。

* **【题目链接】**

[Link:CF1654B](https://www.luogu.com.cn/problem/CF1654B)

* **【解题思路】**

我们可以考虑，什么时候不能再移除了呢？当 $s$ 开头的那个字母在 $s$ 中只出现了一次时。否则，最少也可以删去一个字符。

然后就直接暴力找就行了。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
 
using namespace std;
 
array<int,26> cnt_alp;
string tmp;
 
int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		cnt_alp.fill(0);
		cin>>tmp;
		for(int i=0;i<tmp.size();i++)
			cnt_alp[tmp[i]-'a']++;
		int ptr;
		for(ptr=0;cnt_alp[tmp[ptr]-'a']>1;ptr++)
			cnt_alp[tmp[ptr]-'a']--;
		for(;ptr<tmp.size();ptr++)
			cout<<tmp[ptr];
		cout<<'\n';
	}
 	return 0;
}
 
```

---

## 作者：windflower (赞：0)

简要题意：
>给定一个字符串，每次删除在字符串中出现过不止一次的最长前缀子串直到无法删除，最后输出剩余字符串。

因为它每次都只是删除前缀，如果我们需要删除的最长前缀是 `"xyz"`，那么我们分三次操作删除 `'x'`、`'y'`、`'z'` 是等价的，因此每次只需要删除重复出现过的首字母。再简化一下，我们其实是要找到一个最短的后缀子串，使得它包含的元素种类数量与原串相同。

附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,f[200];
int main(){
	cin>>t;
	while(t--){
		memset(f,0,sizeof(f));
		cin>>s;
		int len=s.size(),begin=0;
		for(int i=0;i<len;i++)f[s[i]]++;
		while(--f[s[begin]])begin++;
		cout<<s.substr(begin)<<endl;
	}
	return 0;
}
```


---

## 作者：_Fatalis_ (赞：0)

### Solution

初看这道题，诶，有点难度，果然是 `Div.1 + Div.2` 的难度啊，AC 自动机？

啊不不不，完全可以不用 AC 自动机。

可以发现，只需要查找第一个字母是否出现在后面即可。

设字符串为 $s_i\ (1\le i\le |s|)$ 。

如果 $s_1\cdots s_k$ 在后面出现过，那么发现 $s_1$ 实际上也会在后面出现。

实际上 $s_2\cdots s_k$ 也都出现。（虽然都是废话）

所以只需要依次删除字符串的第一个字符，只要在后面找到，就说明这个字符必定是在当前最长前缀里头的，且之后的字符都可以依次删除。

那么，

时 $O(\sum|s|)$，空 $O(|s|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
string ac;

int main()
{
    int t,p;
    cin>>t;
    while(t--)
    {
        cin>>ac;
        while((p=ac.find(ac[0],1))!=ac.npos) ac=ac.substr(1);
        cout<<ac<<endl;
    }
    return 0;
}
```

---

## 作者：i_dont_know_who_am_i (赞：0)

一道比较简单的题。

给出一个字符串，让其中在字符串**最前面**且出现次数最多的字串从字符串前删去。

不难发现，只要当前最前面的一个字符在后面出现过，它一定会被删去。所以只需要从后往前扫一遍，用一个数组标记每个字母是否出现。再找出最前面一个在后面没有出现的字符，从这个字符往后输出整个字符串。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
bool a[26];
int main(){
	int t;
	cin >>t;
	while(t--){
		memset(a,0,sizeof(a));
		cin >>s;
		int id=-1;
		for(int i=s.size()-1;i>=0;i--){
			bool flag=1;
			if(a[s[i]-'a']){
				flag=0;
			}else{
				a[s[i]-'a']=1;
			}
			if(flag){
				id=i-1;
			}
		}
		for(int i=id+1;i<s.size();i++){
			cout<<s[i];
		}
		cout<<endl;
	}
}
```


---

## 作者：tongziyu (赞：0)

## Description
共 $t$ 组数据。


每组数据给定一个字符串 $s$，删除 $s$ 最长的作为子串在 $s$ 中其他地方出现过的前缀，并重复直到没有符合条件的前缀。输出处理后的 $s$。

------------

## Solution

其实对于一个前缀，它可以拆分成若干个单独的字母。因为会不断重复的删前缀直到不能删，一个一个删和一段一段删结果是一样的。

一个字母被删除，当且仅当它在 $s$ 的其它地方出现过。换句话说，就是删了之后 $s$ 中还有相同的字母。

那么我们只需从 $s$ 的开头开始，不断取出开头的字母，判断删去后在 $s$ 中是否还有相同的字母，没有就停止删除，最后输出结果。

存储每个字母在 $s$ 中出现的次数，可以用 map 实现，也可以用数组实现。 

------------

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
map <char, int> m;
inline int read()
{
	register int r = 0, c = getchar(), f = 1;
	while (c < '0' || c > '9')
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') r = (r << 1) + (r << 3) + (c ^ 48), c = getchar();
	return r * f;
}
int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	int t = read();
	while (t--)
	{
		m.clear();
		string s;
		cin >> s;
		for (int i = 0; i < s.size(); ++i) ++m[s[i]];
		int cnt = 0;
		while (--m[s[cnt++]]);
		--cnt;
		for (int i = cnt; i < s.size(); ++i) putchar(s[i]);
		putchar('\n');
	}
	return 0;
}
```
代码中的 $cnt$ 是用来记录当前删到了 $s$ 的哪一位。

---

## 作者：shiranui (赞：0)

## 题目大意

给定一个由小写英文字母组成的字符串 $s$， 对其进行一下操作：


设 $x$ 是 $s$ 的最长前缀的长度，该前缀作为相邻子串出现在 $s$ 中还会再次出现。如果 $x$ $=$ $0$ ，停止操作。否则，删除这个前缀，重复执行。

前缀是由给定字符串的几个首字母组成的字符串，不需要任何重新排序。空前缀也是有效的前缀。

## 思路

刚开始看题是懵的，向大佬学习了一下，然后明白了。

换个说法就能懂了：

给一个字符串，从前往后删除在后面出现过的字母，输出最后的结果。

比如说我们来对 $s$ $=$ "abcabdc" 操作一下。

1. 找到前缀 "ab"，删除，留下 $s$ $=$ "cabdc"。

2. 找到前缀 "c"，删除，留下 $s$ $=$ "abdc"。

3. 没有符合条件的前缀，停止操作。

这就相当于从前往后一个一个删掉后面出现的字母。

还是同一个字符串 $s$ $=$ "abcabdc"。

1. 找到 "a"，删除， 留下 $s$ $=$ "bcabdc"。

2. 找到 "b"，删除， 留下 $s$ $=$ "cabdc"。

3. 找到 "c"，删除， 留下 $s$ $=$ "abdc"。

4. 没有符合条件的前缀，停止操作。

第二次操作中的第一、二条对应第一次操作中的第一条， 第二次操作中的第三条对应第二次操作中的第二条。

这种操作时可行的，可以自己再验证一下。

就这么操作下去就好了。

## 代码

数组计数版：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
int t;
string a;
int cnt[26];
int main()
{
	t = read();
	while (t--)
	{
		for (int i = 0; i < 26; i++) cnt[i] = 0;
		cin >> a;
		for (int i = 0; i < a.size(); i++) cnt[a[i] - 'a']++;
		int f = 0;
		while (--cnt[a[f++] - 'a']);
		f--;
		for (int i = f; i < a.size(); i++) cout << a[i];
		cout << endl;
	}
	return 0;
}
```


map 版：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
int t;
string a;
map <char, int> m;
int main()
{
	t = read();
	while (t--)
	{
		m.clear();
		cin >> a;
		for (int i = 0; i < a.size(); i++) m[a[i]]++;
		int cnt = 0;
		while (--m[a[cnt++]]);
		cnt--;
		for (int i = cnt; i < a.size(); i++) cout << a[i];
		cout << endl;
	}
	return 0;
}
```

## 总结

本蒟蒻在写这题的时候犯了好多低级错误 QAQ。

看题目的时候顺便琢磨琢磨样例，有帮助于看题。

有问题欢迎指出~

---

## 作者：RocksonLee (赞：0)


## Problem

[Luogu](https://www.luogu.com.cn/problem/CF1654B)

[Codeforces](https://codeforces.com/contest/1654/problem/B)

## Solution

搜索一个前缀然后如果这个前缀在后面出现过就可以删除。

如果搜索到没有出现过的前缀则算法停止。

前缀可以是一串字符串也可以是 **一个字母**。

所以，我们需要记录每个字母出现的第一个位置，那个位置往后就是答案。

因此，从后往前搜索，如果字母没有出现过的，记录位置，即是答案。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define il inline
#define INF 0x3f3f3f3f
#define cl(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;

map<char, int> mp;

int ans, t, len;

char s[200200];

int main()
{
    scanf("%d", &t);
    for (int kkz = 0; kkz < t; kkz++)
    {
        ans = 0;
        scanf("%s", s);
        len = strlen(s);
        for (int i = len - 1; i >= 0; i--)
        {
            mp[s[i]]++;
            if (mp[s[i]] == 1) ans = i;
        }
        for (int i = ans; i < len; i++)
        {
            printf("%c", s[i]);
        }
        printf("\n");
        mp.clear();
    }
    return 0;
}
```


---

## 作者：IYSY2009I (赞：0)

### [本人的翻译](https://www.luogu.com.cn/paste/jn01q6mf)

我们容易发现，我们删除这个字符串满足要求的最长前缀，其实就相当于删除了许多次满足要求的较短前缀（举个例子，如果该最长满足要求的前缀为 ```ab```,那么其实就相当于你先找到了一个 ```a``` 并删除，再找到了一个 ```b``` 被删除）。因为我们可以发现，如果删去了满足要求的最长前缀的一部分，那么最长前缀中剩下部分的前缀仍然会在文中出现（假如这个满足要求的最长前缀为 $s_1,s_2,...,s_m$,他在 $s_{m-x},s_{m-x+1},...,s_n$ 中出现，那么删除前 $y$ 个前缀，则此时前缀为$s_{1+y},s_{2+y},...,s_m$,它对应 $s_{m-x+y},s_{m-x+1+y},...,s_n$,由于 $y$ 显然小于 $m-x+y$,所以不会删除对应的部分）。

这里为了方便做题，我们一次只删去一个字符。

我们如何判断一个字符如何在字符数组里出现呢？~~这十分的简单~~我们可以开一个桶，记录每个字符在字符串里出现的次数，如果删除了一个字符，该字符的计数器就 $-1$,如果当前字符的计数器 $\ge 2$,说明这个字符串里还存在除它本身外相同的字符，反之没有。

因为赛时我太懒了，直接写的 ```map```,正解应该是字符转整型存储，可以省一个 ```log```（不过因为数据范围太水了，```map``` 也可以过）

赛时丑陋的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	map<char,int> mp;
	char s[200005];
	cin>>s;
	int ls=strlen(s);
	for(int i=0;i<ls;i++)
		mp[s[i]]++;
	for(int i=0;i<ls;i++){
		if(mp[s[i]]>1) mp[s[i]]--;
		else{
			for(int j=i;j<ls;j++)
				printf("%c",s[j]);
			printf("\n");
			return;
		}
	}
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```

---

