# Petya and Exam

## 题目描述

It's hard times now. Today Petya needs to score 100 points on Informatics exam. The tasks seem easy to Petya, but he thinks he lacks time to finish them all, so he asks you to help with one..

There is a glob pattern in the statements (a string consisting of lowercase English letters, characters "?" and "\*"). It is known that character "\*" occurs no more than once in the pattern.

Also, $ n $ query strings are given, it is required to determine for each of them if the pattern matches it or not.

Everything seemed easy to Petya, but then he discovered that the special pattern characters differ from their usual meaning.

A pattern matches a string if it is possible to replace each character "?" with one good lowercase English letter, and the character "\*" (if there is one) with any, including empty, string of bad lowercase English letters, so that the resulting string is the same as the given string.

The good letters are given to Petya. All the others are bad.

## 说明/提示

In the first example we can replace "?" with good letters "a" and "b", so we can see that the answer for the first query is "YES", and the answer for the second query is "NO", because we can't match the third letter.

Explanation of the second example.

- The first query: "NO", because character "\*" can be replaced with a string of bad letters only, but the only way to match the query string is to replace it with the string "ba", in which both letters are good.
- The second query: "YES", because characters "?" can be replaced with corresponding good letters, and character "\*" can be replaced with empty string, and the strings will coincide.
- The third query: "NO", because characters "?" can't be replaced with bad letters.
- The fourth query: "YES", because characters "?" can be replaced with good letters "a", and character "\*" can be replaced with a string of bad letters "x".

## 样例 #1

### 输入

```
ab
a?a
2
aaa
aab
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
abc
a?a?a*
4
abacaba
abaca
apapa
aaaaax
```

### 输出

```
NO
YES
NO
YES
```

# 题解

## 作者：伟大的王夫子 (赞：6)

这么好的字符串模拟题当然要我来写个题解啦。

首先，我们假设模式串的长度为 $n$，匹配串的长度为 $m$。

因为模式串中最多只有一个星号，所以说当 $n-1>m$ 时必然无解。

当模式串中没有星号时，若 $n \not = m$ 时必然无解。

然后我们就可以一位一位的匹配，并且不用考虑长度对不上这个问题了。当匹配到的字符为问号或一般的字母时都没有必要多说，重点要讲得是匹配到星号的情况。设当前匹配到模式串的字符的下标为 $p_1$，匹配串的下标为 $p_2$。那么因为匹配串的长度比模式串多 $m-n$，$p_2$ 就要多加个 $m-n$。当 $m<n$ 时其实也是这么做，只不过加上一个负数。注意要判断这段区间内的字符是否是坏的。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
bool v[26];
char a[100005], b[100005];
int n, m;
int main() {
	cin >> s;
	for (int i = 0; i < s.size(); ++i) v[s[i] - 'a'] = 1;
	scanf("%s", a + 1);
	n = strlen(a + 1);
	bool has_star = 0;
	for (int i = 1; i <= n; ++i) has_star |= a[i] == '*';
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", b + 1);
		m = strlen(b + 1);
		if (n - 1 > m || (!has_star && n != m)) puts("NO");
		else {
			int p1 = 1, p2 = 1;
			bool flag = 1;
			for ( ; p1 <= n && p2 <= m; ++p1, ++p2) {
				if (a[p1] == '?' && v[b[p2] - 'a']) continue;
				if (a[p1] == b[p2]) continue;
				if (a[p1] == '*') {
					int tmp = p2 + m - n;
					for (int j = p2; j <= tmp; ++j)
						if (v[b[j] - 'a']) {
							flag = 0;
							break;
						}
					if (!flag) break;
					p2 = tmp;
				}
				else {
					flag = 0;
					break;
				}
			}
			puts(flag ? "YES" : "NO");
		}
	}
}
```

---

## 作者：Together_ (赞：3)

这里就提一下思路，代码很雷同，可以查看楼上的。

# 思路：

### 什么时候无法匹配？
 
- 因为此题表示最多只有 $\mathtt 1$ 个星号，所以只要 $\mathtt{n-1 > m}$ 那么就说明无法构造。（$\mathtt n$ 是包含星号的字符串的长度，$\mathtt m$ 是希望匹配的字符串）
 
### 那么，是不是只要满足上述条件就一定能匹配呢？

- 很明显不是，举个例子：$\mathtt{a*b}$ 和 $\mathtt{abc}$ 能匹配吗？

### 我们应该如何判断是否成立呢？

- 如果两个字符串的长度是一样的，那么我们可以遍历一遍字符串，一一对应一下，如果遇到问号就看另一个字符串中此数位的字符是不是“好的”字符就行了，如果遇到的是星号，那么跳过即可，因为星号可以替换成任意一个字符。

- 如果两个字符串的长度相差 $\mathtt 1$（是有星号或问号的那个字符串长一点），那么只要将星号忽略，然后和上面一样处理即可。

代码就看楼上的博主啦！

---

## 作者：Bai_R_X (赞：0)

## 思路
首先特判一下长度是否可能相符：如果 $t$ 没星号，输入字符串的长度和 $t$ 应该相等，并且 $t$ 的长度减一要小于等于输入字符串的长度。

然后我们先检查在星号前的字符是否匹配，再检查 $t$ 星号后的字符是否与输入字符串的末尾相同，最后检查用星号填充的几位是否不包括在 $s$ 里。

~~讲句题外话，这题我最开始以为是正则表达式（尝试了然后运行时错误了）~~
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,t,x;
int q,i,j,star=INT_MAX;
set<char> st;
bool hav[256];
signed main()
{
	cin>>s>>t>>q;
	for(auto& it:s)hav[it]=1;
	for(i=0;i<t.size();i++)
	{
		if(t[i]=='*')
		{
			star=i;
			break;
		}
	}
	while(q--)
	{
		cin>>x;
		if(t.size()-1>x.size()||(star==INT_MAX&&t.size()!=x.size()))
		{
			cout<<"NO";
			goto exit;
		}
		if(x.size()<=star)
		{
			for(i=0;i<x.size();i++)
			{
				if((t[i]=='?'&&hav[x[i]]==0)||(t[i]!='?'&&x[i]!=t[i]))
				{
					cout<<"NO";
					goto exit;
				}
			}
			cout<<"YES";
			goto exit;
		}
		for(i=0;i<star;i++)
		{
			if((t[i]=='?'&&hav[x[i]]==0)||(t[i]!='?'&&x[i]!=t[i]))
			{
				cout<<"NO";
				goto exit;
			}
		}
		for(i=t.size()-1,j=x.size()-1;i>star;i--,j--)
		{
			if((t[i]=='?'&&hav[x[j]]==0)||(t[i]!='?'&&x[j]!=t[i]))
			{
				cout<<"NO";
				goto exit;
			}
		}
		for(;j>=star;j--)
		{
			if(hav[x[j]])
			{
				cout<<"NO";
				goto exit;
			}
		}
		cout<<"YES";
exit:
		cout<<endl;
	} 
	return 0;
}
```

---

