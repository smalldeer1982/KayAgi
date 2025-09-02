# Code obfuscation

## 题目描述

Kostya likes Codeforces contests very much. However, he is very disappointed that his solutions are frequently hacked. That's why he decided to obfuscate (intentionally make less readable) his code before upcoming contest.

To obfuscate the code, Kostya first looks at the first variable name used in his program and replaces all its occurrences with a single symbol $ a $ , then he looks at the second variable name that has not been replaced yet, and replaces all its occurrences with $ b $ , and so on. Kostya is well-mannered, so he doesn't use any one-letter names before obfuscation. Moreover, there are at most 26 unique identifiers in his programs.

You are given a list of identifiers of some program with removed spaces and line breaks. Check if this program can be a result of Kostya's obfuscation.

## 说明/提示

In the first sample case, one possible list of identifiers would be "number string number character number string number". Here how Kostya would obfuscate the program:

- replace all occurences of number with a, the result would be "a string a character a string a",
- replace all occurences of string with b, the result would be "a b a character a b a",
- replace all occurences of character with c, the result would be "a b a c a b a",
- all identifiers have been replaced, thus the obfuscation is finished.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
jinotega
```

### 输出

```
NO
```

# 题解

## 作者：CQ_Bab (赞：1)

# 思路
这道题我们发现在 $a$ 后面的只可能是 $b$ 或者 $a$，而不可能比 $b$ 更大。所以我们就可以用循环去判断，并用一个 $cnt$ 表示现在出现了几个字符，然后判断若现在出现的一个 $s_i$ 大于了第 $cnt+1$ 个字母就不行。否则若都合理就可以了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
string s;
int cnt=1;
int main() {
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	map<char,int>mp;
	cin>>s;
	for(int i=0; s[i]; i++) {
		if(!mp[s[i]]&&cnt==s[i]-'a'+1) mp[s[i]]=1,cnt++;//判断出现过吗
		else if(s[i]-'a'+1>cnt) {
			cout<<"NO\n"; //不符合
			return false;
		}
	}
	cout<<"YES\n";
	return false;
}
```


---

## 作者：辛丑九月 (赞：1)

## Analysis

首先看原串变成新串的过程：假设当前已经出现了 $k$ 种字符，现在出现了 $k + 1$ 种，那么将这个字符映射为字符 `'a' + k`。

那么反过来说的话，就是在新串中每个字符第一次出现时已经有了 $k$ 种字符，那么这个字符一定是 `'a' + k`。 然后要做的就是模拟这个过程。

## Code

```cpp
# include <bits/stdc++.h>
using namespace std;

int k;
string s;
bool vis[40];

int main () {
	cin >> s;
	for (char i : s)
		if (!vis[i - 'a']) {
			vis[i - 'a'] = true;
			if (i - 'a' != k++) return puts ("NO"), 0;
 			// 如果当前出现的个数和 'a' + k 不同就是错的
		}
	return puts ("YES"), 0; // 否则就是对的
}
```

---

## 作者：33aaron (赞：1)

## 题目大意
Kostya在整理变量名，他要把所有的变量名都改为单个字母，他想要按照字母表顺序来声明变量。给定他调用变量（首次调用就是声明）的顺序，输出他是不是混淆了变量名。
## 题目分析
我们尝试运用一个 $maxchar$ 变量来记录下一个应该被声明的名为字母的变量名。则如果遍历到一个比这个字母的字母表顺序更大的字母的话则输出 $NO$ 然后退出程序，如果遍历到的字母就是这个字母说明在这一步声明了这个字母则我们自增 $maxchar$ 来记录这个变量已经被声明了，如果遍历到一个比这个字母的字母表顺序更小的字母的话就不用管了。
## AC Code
```cpp
#include <iostream>
#include <string>
using namespace std;
string in;
int maxchar = 'a';
int main() {
    cin >> in;
    for (int i = 0; i < in.size(); ++i)
        if (in[i] > maxchar) return cout << "NO", 0;
        else if (in[i] == maxchar) ++maxchar;
    cout << "YES";
    return 0;
}
```

---

## 作者：szhqwq (赞：0)

## 分析

据题可得：第一个出现的 `a` 一定不会在第一个出现的 `b` 的后面，我们用 $cnt$ 表示当前可以出现的最大的字符，$s$ 表示输入的字符串。

1. 如果 $s_i$ 比当前可以出现的最大字母 $cnt$ 大，则不合法；

2. 如果 $s_i$ 等于 $cnt$，$cnt \leftarrow (cnt + 1)$；

3. 反之，小于的时候一定是合法的。

## AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

string s;

signed main() {
	ios :: sync_with_stdio(false);
	cin >> s;
	int cnt = 0;
	for (int i = 0; i < s.size(); i ++ ) {
		if (s[i] > cnt + 'a') { puts("NO"); return 0; }
		else if (s[i] == cnt + 'a') cnt ++;
	}
	puts("YES");
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给你一个字符串，然后把它变成另一个字符串，如果第一个出现的字符就把他变成 `a`,第二个就变成 `b`，以此类推。

现告诉你转换后的字符串，问你是否有可能由其他字符串转换过来。

# 题目分析

遍历一遍字符串，如果当前字符比目前所有出现过的字符都要大，那么显然会混淆，直接输出 `NO`；

否则，更新到目前为止最大的出现过的字符。

# 代码

```cpp
//2022/1/14

string str;

int main(void)
{
	cin>>str;
	
	char maxchar='a';
	
	for(register int i=0;i<str.size();i++)
	{
		if(maxchar<str[i])
		{
			puts("NO");
			
			return 0;
		}
		
		else if(maxchar==str[i])
		{
			maxchar++;
		}
	}
	
	puts("YES");
	
	return 0;
}
```

---

