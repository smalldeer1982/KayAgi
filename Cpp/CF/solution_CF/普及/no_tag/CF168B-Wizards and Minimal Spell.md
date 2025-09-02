# Wizards and Minimal Spell

## 题目描述

Let's dive into one of the most interesting areas of magic — writing spells. Learning this exciting but challenging science is very troublesome, so now you will not learn the magic words, but only get to know the basic rules of writing spells.

Each spell consists of several lines. The line, whose first non-space character is character "\#" is an amplifying line and it is responsible for spell power. The remaining lines are common, and determine the effect of the spell.

You came across the text of some spell. Spell was too long, so you cannot understand its meaning. So you want to make it as short as possible without changing the meaning.

The only way to shorten a spell that you know is the removal of some spaces and line breaks. We know that when it comes to texts of spells, the spaces carry meaning only in the amplifying lines, so we should remove all spaces in other lines. Newlines also do not matter, unless any of the two separated lines is amplifying. Thus, if two consecutive lines are not amplifying, they need to be joined into one (i.e. we should concatenate the second line to the first one). Removing spaces in amplifying lines and concatenating the amplifying lines to anything is forbidden.

Note that empty lines must be processed just like all the others: they must be joined to the adjacent non-amplifying lines, or preserved in the output, if they are surrounded with amplifying lines on both sides (i.e. the line above it, if there is one, is amplifying, and the line below it, if there is one, is amplifying too).

For now those are the only instructions for removing unnecessary characters that you have to follow (oh yes, a newline is a character, too).

The input contains the text of the spell, which should be reduced. Remove the extra characters and print the result to the output.

## 说明/提示

In the first sample the amplifying lines are lines 1 and 7. So, lines 2 to 6 are concatenated to each other, all spaces are deleted from them.

In the second sample the amplifying lines are lines 1 and 3. So, no lines are concatenated to each other.

## 样例 #1

### 输入

```
   #   include &lt;cstdio&gt;

using namespace std;

int main     (   ){
puts(&quot;Hello # World&quot;); #
#
}
```

### 输出

```
   #   include &lt;cstdio&gt;
usingnamespacestd;intmain(){puts(&quot;Hello#World&quot;);#
#
}
```

## 样例 #2

### 输入

```
#

#
```

### 输出

```
#

#
```

# 题解

## 作者：Wilderness_ (赞：3)

题目链接：[CodeForces](https://codeforces.com/problemset/problem/168/B) / [Luogu(目前 RMJ 炸了)](https://www.luogu.com.cn/problem/CF168B).

### 翻译
输入若干行字符串 $S$（保证行数 $n$ 满足 $0<n\le2^{20}$，且每行包含的字符 $c\in [32,127]$ 包括换行符），你需要将 $S$ 按以下规则缩短：

1. 删除除了以字符 `#` 开头的行以外的其余行的所有空格；
2. 若有连续两行未以 `#` 开头，则需要将这两行合并为一行；
3. 若一个空行上下两行都以 `#` 开头，则保留此空行，否则删除空行。

请输出缩短之后的字符串 $S$。

### 思路
模拟。

分行读入，碰见 `#` 时做标记，然后输出这整一行，否则就逐个字符判断是否为空格，不是则输出。

如果我们前一行做了标记，后一行也做了标记，那么中间行若为空行直接输出。

最后别忘了再输出一个换行符，不然会 WA，原因未知。
### Code:
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int fg=0,pos;
	string s;
	while(getline(cin,s))
	{
		for(pos=0;pos<s.size();++pos)
			if(s[pos]!=' ')
				break;
		if(pos==s.size()||s[pos]!='#')
		{
			if(fg==2)putchar('\n');
			for(pos=0;pos<s.length();++pos)
				if(s[pos]!=' ')
					putchar(s[pos]);
			fg=1;
		}
		else 
		{
			if(fg)putchar('\n');
			cout<<s;
			fg=2;
		}
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：Yamchip (赞：3)

## 思路
首先我们需要第一个非空格的字符，如果为 `#` 那么这一行直接输出。其次，换行的控制需要用一个变量，记录上一行是不是特殊行。最后，还要输出一个神奇的换行。否则就会变成这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/58rimoc0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
## Code
```
#include<bits/stdc++.h>
using namespace std;
string code;
int t = -1;
int main()
{
	while(getline(cin, code))
	{
		int x = 0;
		for(int i = 0;i < code.size();i++)
			if(code[i] != ' ')
			{
				x = i;
				break;
			}
		if(code[x] == '#')
		{
			if(!t && t != -1) cout << endl;
			t = 1;
			cout << code << endl;
		}
		else
		{
			t = 0;
			for(int i = 0;i < code.size();i++)
			if(code[i] != ' ')
				cout << code[i];
		}
	}
	if(!t)
		cout << endl;
	return 0;
}
```

---

## 作者：玉树临风英俊潇洒 (赞：2)

这题是一道模拟题。

以下是本题重要和注意点。

1.  删除除了以字符 # 开头的行以外的其余行的所有空格。

1. 若有连续两行未以 # 开头，则需要将这两行合并为一行。

2. 若一个空行上下两行都以 # 开头，则保留此空行，否则删除空行。

3. 别忘了再输出一个换行符，不然就等着0分吧！ ~~(为什么不知道)~~ ！
```
#include<bits/stdc++.h>
using namespace std;
int flag;
int main(){
	int i;
	string s;
	while(getline(cin,s)){
		for(i=0;i<s.size();i++)if(s[i]!=' ')break;
		if(i==s.size()||s[i]!='#'){
			if(flag==2)cout<<"\n";
			for(i=0;i<s.size();i++)if(s[i]!=' ')cout<<s[i];
			flag=1;
		}
		else{
			if(flag)cout<<"\n";
			cout<<s;
			flag=2;
		}
	}
	cout<<"\n";
	return 0;
}
```
请不要抄题解哟！

最后再求一个点赞和关注！

---

## 作者：abc1234shi (赞：2)

这题是一道模拟题。

1. 如果字符串由 `#` 这个字符开头就把整行输出了，否则只输出非空格部分。

2. 如果某一行和它后面的一行都不是由 `#` 开头，那么此行只输出非空格部分后不用输出换行了，直接连着下一行一起输出了。

3. 如果有空行，得看此空行如果前面和后面都是由 `#` 开头，那么输出这一空行，否则不输出这一空行。

4. 最后记住要一定要输出换行。

---

## 作者：beigongbaishan (赞：0)

# 题意简述
有一个好几行的字符串 $S$ ，你要对它进行如下操作：  
1. 若此行以 `#` 开头，直接输出。
2. 若此行不以 `#` 开头，且下一行以 `#` 开头，过滤空格并输出。
3. 若此行与下一行皆以 `#` 开头，将两行连在一起过滤空格并输出。
4. 如果一个空行上下两行皆以 `#` 开头，直接输出，否则删除此空行。
5. 最后要输出一个换行（玄学）。
# 解题思路
1. 逐行读入，若此行以 `#` 开头，标记下来。
2. 逐行遍历，若此行被标记，直接输出。
3. 若此行未被标记，过滤空格并输出，若上一行，也未被标记，忽略空格。
4.  如果一个空行上下两行皆以 `#` 开头，直接输出，否则忽略此空行。
5.  最后输出一个换行符。

完结撒花~

---

## 作者：Phoenix114514 (赞：0)

# CF168B Wizards and Minimal Spell
## 思路
主打一个模拟。

输入时一行一个字符串，如果有 ```#``` 就直接输出这一行。
否则把 $s$ 跑一遍，不是空格则输出。

如若第 $i+1$ 做了标记，第 $i-1$ 行也做了标记，那么中间所在的这一行若为空行直接输出。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int flag;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	int i;
	string s;
	while(getline(cin,s)){
		for(i=0;i<s.size();i++)if(s[i]!=' ')break;
		if(i==s.size()||s[i]!='#'){
			if(flag==2)cout<<"\n";
			for(i=0;i<s.size();i++)if(s[i]!=' ')cout<<s[i];
			flag=1;
		}
		else{
			if(flag)cout<<"\n";
			cout<<s;
			flag=2;
		}
	}
	cout<<"\n";//和某位大佬一样，没加换行就 WA。
	return 0;
}
```

---

## 作者：cloud2764scallop_eve (赞：0)

传送门：[luogu](https://www.luogu.com.cn/problem/CF168B) 和 [codeforces](https://codeforces.com/problemset/problem/168/B)。

## 题意

给定若干行长度为 $n$ 的字符串，要求进行以下操作：  
- 若字符串不以 `#` 开头，则删去所有空格；
- 若第 $i$ 行和第 $i + 1$ 行都不以 `#` 开头，则将这两行合并为同一行；
- 若第 $i$ 行为空行，除非第 $i - 1$ 和 $i + 1$ 行都以 `#` 开头，否则删去此行。

求经过所有操作后的字符串 $S$。

## 思路

~~不是这纯英语体面给谁看的啊！~~

感谢楼上的翻译和 DeepL 翻译。

纯纯的小模拟。不过模拟的思路楼上已经说过了，来一个别的。

首先介绍一个特殊的流类：`stringstream`。它允许将字符串作为输入和输出流进行处理。字符串流提供了一种方便的方式，可以将字符串与其他基本类型进行转换、拼接、解析等操作。

于是乎，就可以借助 `stringstream` 的功能，把用 `vector` 存储的值转换为 `string`。然后再对题目要求中的条件分别做判断，分别处理即可。

这里处理的整体思路其实和直接模拟没有太多区别，~~所以我其实是个标题党~~。

具体细节见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace xycyx {
	vector<string> v, res;
	bool isamp(string &str) {
		stringstream ss(str);
		string x;
		ss >> x;
		return (int)x.size() && x[0] == '#';
	}
	void solve() {
		string str;
		while (getline(cin, str))
			v.push_back(str);
		bool flag = 1;
		for (int i = 0; i < (int)v.size(); i++) {
			str = "";
			stringstream ss(v[i]);
			ss >> str;
			if ((int)str.size() && str[0] == '#') {
				res.push_back(v[i]);
				flag = 1;
				continue;
			}
			if ((int)str.size() == 0) {
				string st = (int)res.size() ? res.back() : "#";
				string en = i + 1 < (int)v.size() ? v[i + 1] : "#";
				if (isamp(st) && isamp(en)) res.push_back(str);
				else continue;
			} else {
				string tot = str;
				while (ss >> str) tot += str;
				if (!flag) res[(int)res.size() - 1] += tot;
				else res.push_back(tot);
				flag = 0;
			}
		}
		for (int i = 0; i < (int)res.size(); i++)
			cout << res[i] << "\n";
	}
}
int main() {
	xycyx::solve();
	return 0;
}
```

> 在函数 `isamp` 中，`return` 的句子等价于：  
```cpp
if ((int)x.size() != 0 && x[0] == '#') return true;
else return false;
```

---

