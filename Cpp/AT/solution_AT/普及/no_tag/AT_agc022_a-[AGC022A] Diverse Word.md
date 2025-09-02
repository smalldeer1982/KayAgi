# [AGC022A] Diverse Word

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc022/tasks/agc022_a

ゴトウは辞書をもらいました。ところが、その辞書は知らない言語で書かれていました。 分析した結果、その辞書にはありうるすべての **多彩** な単語が辞書順に載っていることがわかりました。

単語は、それが英小文字からなる空でない文字列であって、単語内の文字がすべて異なる場合、そしてその場合に限って **多彩** であると呼ばれます。例えば、`atcoder`、`zscoder`、`agc` は多彩な単語ですが、`gotou`、`connect` は多彩な単語ではありません。

多彩な単語 $ S $ が与えられるので、この辞書で $ S $ の次に載っている単語、すなわち、$ S $ より辞書順で大きいような、辞書順で最小の多彩な単語を求めてください。あるいは、そのような単語は存在しないと判定してください。

なお、$ X\ =\ x_{1}x_{2}...x_{n} $、$ Y\ =\ y_{1}y_{2}...y_{m} $ を二つの異なる文字列とするとき、$ Y $ が $ X $ の接頭辞であるか、$ j $ を $ x_{j}\ \neq\ y_{j} $ であるような最小の整数として $ x_{j}\ >\ y_{j} $ である場合、そしてその場合に限って $ X $ は $ Y $ より辞書順で大きいといいます。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 26 $
- $ S $ は多彩な単語である。

### Sample Explanation 1

`atcoder` より辞書順で大きいような、辞書順で最小の多彩な単語は `atcoderb` です。`atcoderb` は `b` より辞書順で小さいことに注意してください。

### Sample Explanation 3

これが辞書順で最も大きい多彩な単語なので、答えは `-1` です。

## 样例 #1

### 输入

```
atcoder```

### 输出

```
atcoderb```

## 样例 #2

### 输入

```
abc```

### 输出

```
abcd```

## 样例 #3

### 输入

```
zyxwvutsrqponmlkjihgfedcba```

### 输出

```
-1```

## 样例 #4

### 输入

```
abcdefghijklmnopqrstuvwzyx```

### 输出

```
abcdefghijklmnopqrstuvx```

# 题解

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/AT_agc022_a)
# 思路
这道题要**分类讨论**。
### 第一种情况
首先是 $|S|<26$ 的情况。这种情况下直接找出最小的字符串中未出现的字符。然后将这个字符补充在原字符串的后面。

说明：如果或删除修改 $S$ 中的字符，那么最终得出来的字符串肯定要比上述方案得出来的更大，而上述方案添加的又是最小的字符，所以其在所有添加方案中字典序最小，所以上述方案是最优解。
### 第二种情况
其次是 $|S|=26$ 的情况。这种情况下只有在 $S=\texttt{zyxwvutsrqponmlkjihgfedcba}$ 时输出 $-1$。否则就用 `next_permutation` 求出 $S$ 的下一个全排列，用字符串 $T$ 保存。接着比对 $S$ 与 $T$，找出 $S$ 和 $T$ 中第一个不相同的字符，然后输出这个字符前的子串输出（子串包含该字符）。

说明：因为 $|S|=26$，所以无法进行添加操作，只能修改。因为当 $S=\texttt{zyxwvutsrqponmlkjihgfedcba}$ 时无论怎样修改都会使答案比原字符串小，所以输出 $-1$。而其它情况时，由于答案的字典序要最小，所以只修改一个字符就可以了，所以只用输出第一个不一样的字符前面的子串。
# 注意事项
**字典序与长度无关！**
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int n=s.size();
	if (n<26)
	{
		bool f[30]={};
		for(int i=0;i<n;i++)
			f[s[i]-96]=true;
		for(int i=1;i<=26;i++)
			if (!f[i])
			{
				cout<<s<<char(i+96)<<endl;
				break;
			}
	}
	else
	{
		if (s=="zyxwvutsrqponmlkjihgfedcba")
		{
			cout<<-1<<endl;
			return 0;
		}
		string t=s;
		next_permutation(s.begin(),s.end());
		for(int i=0;i<n;i++)
		{
			cout<<s[i];
			if (s[i]!=t[i])
				break;
		}
	}
}
```

---

## 作者：So_noSlack (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT_agc022_a)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/agc022_a)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定字符串 $S$，仅包含**互不相同的小写字母**，你需要找到仅包含**互不相同**的小写字母的字符串中，第一个**字典序比它大**的字符串，如果找不到输出 $-1$。（$| S | \le 26$）

## 思路

这篇题解主要分享一下 `map` 的做法。

可分两种情况讨论：

1. 字符串长度 $< 26$。

2. 字符串长度 $= 26$。

因为**互不相同**所以不会出现大于 $26$ 的情况。

对于样例 $4$：`abcdefghijklmnopqrstuvwzyx`。

可将 `w` 变为**它后面比它大但最小**的 `x`，后面**直接舍去**即可，变为 `abcdefghijklmnopqrstuvx`。

解释完样例，先来讨论一下情况 $1$，因为长度小于 $26$，所以至少有 $1$ 个字母**未出现过**，直接在字符串末尾加上**没出现过**的**最小**字母即可。

对于情况 $2$，就可参考以上样例 $4$ 的解释，可发现找到一个位置，把这个位置上的字母替换为**它后面比它大但最小**的字母即可，这个位置需要**从后向前枚举**。

那么接下来就是实现了，首先需要定义一个 `map` 容器，来**存储哪些字母出现过或没出现过**，对于情况 $1$ 直接模拟即可。

对于情况 $2$ 则需记录一个**最大值**，如果**当前位置小于最大值再枚举**，这样就**避免了不合法**的情况了。

经过以上分类讨论，很容易即可写出**代码**了：

```cpp
#include<iostream>
#include<map>
using namespace std;

string str;
int maxn;
map<char, int> mp;
map<int, bool> vis;

int max(int x, int y) { return (x > y) ? x : y; }

int main() {
	cin >> str;
	int n = str.length(); // 记录长度
	for(int i = 0; i < n; i ++) mp[str[i]] ++; // 计数
	if(n < 26) {
		for(int i = 'a'; i <= 'z'; i ++) 
			if(!mp[i]) {
				cout << str << char(i) << endl; // 没有出现过，直接输出结束
				return 0;
			}
	}
  	// 从后向前枚举
	for(int i = n - 1; i >= 0; i --) {
  		// 满足条件，可输出
		if(str[i] < maxn) {
			for(int j = 0; j < i; j ++) cout << str[j];
			for(int j = str[i] - 'a'; j < 26; j ++) 
				if(vis[j]) {
					cout << char(j + 'a'); // 输出替换的字母
					return 0;
				}
		}
		maxn = max(maxn, str[i]);
		vis[str[i] - 'a'] = true;
	}
	cout << "-1\n"; // 以上条件都不满足，输出 -1
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117918063)

$$\text{The End!}$$

---

## 作者：火车司机 (赞：2)

## 简要分析

分类讨论

- 长度小于26

说明至少有一个字母没出现过，在原字符串之后加上最小的没出现的字母即可

- 长度等于26

因为要使字典序增大，所以必然有一个位置上的字母要增大

每一个位置的字母可取值的范围只有它自己以及位置在它之后字母

所以我们要找到第一个小于它后方最大字母的位置

找不到输出 $-1$ 即可

否则，在它之前的字符原样输出，它所在的位置输出**它后方比它大的字母**中最小的一个，后面全部舍去即可

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int n, mx, v[30];
char s[30];
inline int mxx(int a, int b)
{
	return a > b ? a : b;
}
signed main()
{
	scanf("%s", s + 1), n = strlen(s + 1);
	if (n < 26)
	{
		for (ri i = 1; i <= n; ++i)
			v[s[i] - 'a'] = 1, putchar(s[i]);
		for (ri i = 0; i < 26; ++i)
			if (!v[i])
			{
				putchar(i + 'a');
				return 0;
			}
	}
	for (ri i = n; i; --i)
	{
		if (s[i] < mx)
		{
			for (ri j = 1; j < i; ++j)
				putchar(s[j]);
			for (ri j = s[i] - 'a'; j < 26; ++j)
				if (v[j])
				{
					putchar(j + 'a');
					return 0;
				}
		}
		mx = mxx(mx, s[i]), v[s[i] - 'a'] = 1;
	}
	puts("-1");
	return 0;
}
```


---

## 作者：feiji_code (赞：1)

## 思路：
我们先了解下 map。




```map```是一种 STL 容器，可以用
```char```，```int```，```string``` 之类的数据类型当下标。

这个题目需要**分类讨论**。

**字典序与长度无关**。
1. 字符串长度小于 $26$。

只需要输出最小的没出现过的字符就可以了。
```cpp
if(len<26){ for(int i='a';i<='z';i++) if(!mapp[i]){cout<<a;char c=i;cout<<c;return 0;}}
```
2. 字符串长度等于 $26$。

我们从后往前枚举 $a_i$ 和 $a_j$，如果 $a_j$ 的字典序大于 $a_i$ 就让 ```
m= min(m,a[j])```
 ，最后让 $a_i$ 等于 $m$ 并从 $0$ 输出到 $i$ 就完成了。
```cpp
char m=='z'+1;
	for (int i=len-1;i>=0;i--){
		for (int j=i+1;j<len; j++){
			if (a[j]>a[i]) m= min(m,a[j]);
		}
		if (m!='z' + 1){
			a[i] = m;
			for(int j=0;j<=i;j++) cout<<a[j];
			return 0;
		}
	}
```
**如果都不成立输出 $-1$。**
### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//主函数↓
map<char,bool> mapp;
string a;
int main(){
	cin>>a;
	int len=a.size();
	for(int i=0;i<len;i++){
		mapp[a[i]]=true;
	}
	if(len<26){ for(int i='a';i<='z';i++) if(!mapp[i]){cout<<a;char c=i;cout<<c;return 0;}}
	else{

		char m=char('z'+1);
		for (int i=len-1;i>=0;i--){
			for (int j=i+1;j<len; j++){
				if (a[j]>a[i]) m= min(m,a[j]);
			}
			if (m!=char('z' + 1)){
				a[i] = m;
				for(int j=0;j<=i;j++) cout<<a[j];
				return 0;
			}
		}
	}
	cout<<-1;
	return 0;



}

```




---

## 作者：ys_kylin__ (赞：1)

## 题意
给一个各个字符互不相同的小写字符串，求字典序比他大且最小的字符串。
## 思路
本题需要分类讨论。由于只能用小写字母且互不相同，所以字符串只可能有最大二十六的长度。在这里，考虑两种情况（在此设字符串为 $s$）：

1. 长度小于 $26$，则最为简单，从所有小写字符中找到一个从来没有出现的字符，塞到 $s$ 的尾部，就可以满足字典序最小。
2. 重头戏来了！如果长度等于 $26$ 的话，由于要让字典序小。自然地，从后倒枚（设倒枚中的下标为 $i$），而对于倒枚中的每个字符，用 $j$ 从 $i$ 到长度（$len$）遍历，找到比 $s _ i$ 大的且最小的字符 $s _ j$，然后将 $s _ i$ 替换为 $s _ j$，并将 $i$ 后面的数删除。最后输出 $s$ 数组。

在这里，我们用 map 维护每个字符是否出现过，可以轻松完成目标，注意，假如字符串为 `zyxwvutsrqponmlkjihgfedcba`，输出 $-1$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
map <char,bool> mp;//mp记录每个字符是否出现过
char s[30];
int main(){
	scanf("%s",s);
	int len=strlen(s);
	for(int i=0;i<len;i++) {
		mp[s[i]]=true;
	}
	if(len<26) {
		for(char i='a';i<='z';i++) {
			if(mp[i]==false) {
				printf("%s%c",s,i);
				return 0;
			}
		}
	}
	else {
		char mc='{';//左大括号为ascll码中‘z’+1。
		for(int i=len-1;i>=0;i--) {
			for(int j=i+1;j<len;j++) {//寻找比s[i]大的最小字符
				if(s[j]>s[i]) {
					mc=min(mc,s[j]);
				}
			}
			if(mc!='{') {//有改变
				s[i]=mc;
				for(int j=0;j<=i;j++) printf("%c",s[j]);
				return 0;
			}
		}
	}
	printf("-1");//无解
	return 0;
}
```

---

## 作者：Storm_Lightning (赞：0)

## 思路

因为 $|s|  \le  26 $ 并且字符串 $s$ 的各个字符各不相同，所以我们可以分两种情况来考虑。

- $|s| < 26$ 在这种情况下，若想使字典序大于 $s$ 的字符串中最小的字符串尽可能的小，则只需在字符串 $s$ 的后面添上一个 $s$ 里面没有的字符即可。在这里，我会使用一种名为 map 的 STL。不回 map 的人请自行去学。

- $|s| = 26$ 这种情况下呢，我们只需在从前往后遍历的同时，字啊从当前的位置 $i$ 遍历到尾。这时我们需要一个临时字符变量 $m$ ，来记录在 $a[j] > a[i]$ 时，求 $m$ 和 $a[j]$ 中 ASCLL 的较小值，作为其中的中间拐点，然后从 $0$ 一直输出到当前的位置 $i$ 。

这样，我们就将 $|s|  \le  26 $ 的情况讨论完了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int> mapp;
string a;
int main()
{
	cin>>a;
	int len=a.size();
	for(int i=0;i<len;i++)//如果a[i]出现，就把它扔进map里。 
	{
		mapp[a[i]]=true;
	}
	if(len<26)
	{ 
		for(char i='a';i<='z';i++) 
		{//判断这个字符在map里有没有出现，如果没出现，在字符串a后输出即可。 
			if(!mapp[i])
			{
				cout<<a<<i<<endl; 
				return 0;
			}
		}
	}
	else
	{
		char m='z';
		for(int i=len-1;i>=0;i--)
		{
			for(int j=i+1;j<len;j++)
			{
				if(a[j]>a[i])m=min(m,a[j]);
			}
			if(m!='z')
			{
				a[i]=m;
				for(int j=0;j<=i;j++) 
				{
					cout<<a[j];
				}
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_agc022_a [AGC022A] Diverse Word

### Description

给定一个所有字符互不相同且只包含小写字母的字符串。

求字典序比它大的所有字符互不相同且只包含小写字母的字符串中字典序最小的字符串。

如果不存在输出 $-1$。

### Solution

我们分以下两种情况讨论：

- 字符串长度 $<26$，此时至少有一个字母未出现过，我们只需查找未出现过的最小的字母，然后将其加在原字符串后面即可。

- 字符串长度 $=26$，因为改动后的字符串字典序比原字符串大，所以至少有一个字母要被改大，即改为位置在它之后的字母。因为要求满足要求的字典序最小的字符串，所以改动的位置要尽量靠后。我们倒着遍历原字符串，判断是否有比某个位置的字母大的字母未在该位置之前出现，若有，直接记录下该位置与比该位置的字母大满且未出现过的的最小字母，并输出该位置之前的字符串与该字母，若没有，输出 $-1$。

而记录一个字符是否出现过，我们可以使用 map。

另外再温馨提示：**字符串的字典序与字符串长度无关**。

### AC code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
map<char,int> m;
char c='J';
int ans,cnt,n,k,l,p; 
signed main(){
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++){
		m[s[i]]++;
	}
	if(len<26){
		cout<<s;
		for(int i=0;i<26;i++){
			if(m['a'+i]!=1){
				cout<<char('a'+i);
				return 0;
			}
		}
	}else{
		for(int i=len-1;i>=0;i--){
			k=s[i];
			m[s[i]]=0;
			for(int j=k+1;j<='z';j++){
				if(m[j]==0){
					c=j;
					l=i;
					break;
				}
			}
			if(c!='J') break;
		}
	}
	if(c=='J'){
		cout<<-1;
		return 0;
	}
	for(int i=0;i<l;i++){
		cout<<s[i];
	}
	cout<<c;
	return 0;
}


---

## 作者：___cjy__ (赞：0)

# [AGC022A] Diverse Word 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_agc022_a)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-at-agc022-a)

### 题目大意：

求字典序比给定字符串 $S$ 大的所有字符互不相同且只包含小写字母的字符串中字典序最小的字符串。

### 正文：

首先考虑无解的情况，当且仅当 `zyxwvutsrqponmlkjihgfedcba` 即字符串为降序的时候无解，只需要特判即可。

接下来根据字符串长度分类讨论：

- 当 $S$ 的长度为 $26$ 时：

这意味着每一种字符都已经出现过。要使字典序变大，则考虑从后往前遍历，当我们找到它后方最小比它大的字符的位置，便可以将当前位置的字符更改为它后方最小比它大的字符，随后丢弃当前字符以后的部分即可。

- 当 $S$ 的长度小于 $26$ 时：

这种情况就更简单了，找到最小的没有出现过的字符，直接加到字符串后面输出即可。

可以开桶记录。

### AC Code：

```cpp
#include <bits/stdc++.h>
//#define int long long
#define N 100005

using namespace std;

string s;
int mp[N] = {0}, mi = 123, flag = 0;

signed main(){
	cin >> s;
	if(s == "zyxwvutsrqponmlkjihgfedcba"){
		cout << "-1";
		return 0;
	}
	for(int i=0; i<s.size(); i++){
		mp[(int)(s[i])] = 1;
	}
	if(s.size() == 26){
		for(int i=s.size()-1; i>=0; i--){
			for(int j=i+1; j<s.size(); j++){
				if(s[i] < s[j]) mi = min(mi, int(s[j])), flag = 1;
			}
			if(flag){
				cout << s.substr(0, i);
				cout << char(mi);
				return 0;
			}
		}
	}else{
		cout << s;
		for(int i=int('a'); i<=int('z'); i++){
			if(!mp[i]){
				cout << char(i);
				break;
			}
		}
	}
	
	
	return 0;
}
```

---

## 作者：LiJinLin_AFO (赞：0)

# AT_agc022_a 题解
首先介绍一个 STL 函数，有两种使用形式（见下）。
```cpp
bool next_permutation (BidirectionalIterator first, BidirectionalIterator last);
bool next_permutation (BidirectionalIterator first, BidirectionalIterator last, Compare comp);
```
它返回一个布尔值，并且将赋入的字符串或数组的范围进行下一个全排列。如果有下一个全排列，返回 $1$，否则返回 $0$（关于此函数的具体运用见代码）。

设输入字符串为 $a$，字符串长度为 $|a|$，我们需要进行分类讨论。

1. $|a|=26$ 且 $a=$`zyxwvutsrqponmlkjihgfedcba`。这种情况无解，输出 $-1$。

2. $|a|=26$，且为其他情况。但是，光有函数不能解决此问题。所以，需要我们判断，从哪里改变前的字符串和改变后的字符串开始不同，然后终止。

3. $|a|<26$。我们可以直接寻找在字符串中没有出现的最小的字符，并在输出原来字符串后再输出这个字符。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
bool is[100];
int main(){
	cin>>a;
	int len=a.size();
	if(a=="zyxwvutsrqponmlkjihgfedcba"){
		cout<<"-1";
		return 0;
	}//情况1
	if(len==26){
		string b=a;
		int i;
		next_permutation(a.begin(),a.end());//注意，这是本函数的标准使用方式
		for(i=0;i<len&&a[i]==b[i];i++) printf("%c",a[i]);
		cout<<a[i];
		return 0;
	}//情况2
	for(int i=0;i<len;i++){
		is[a[i]-'a'+1]=1;
	} 
	cout<<a;
	for(int i=1;i<=26;i++){
		if(!is[i]){
			printf("%c",'a'+i-1);
			return 0;
		}
	}//情况3
	return 0;
}
```

---

## 作者：Ezio__Auditore (赞：0)

## AT3946 [AGC022A] Diverse Word
[[Statment]](https://www.luogu.com.cn/problem/AT3946)

$Date:\ Dec.\ 2nd$

---
#### 题意：
 &emsp;&emsp;给定一个字符串 $S$ , 仅包含互不相同的小写字母， 你需要找到仅包含互不相同的小写字母的字符串中，第一个字典序比他大的字符串， 如果找不到输出 $-1$。 （$|S| \le 26$）
 
---
追随 [@火车司机](https://www.luogu.com.cn/user/51692) 的步伐刷 AtCoder。

---
#### 思路：
  注意，这里的字典序和长度无关。
  
  所以可以分为两类讨论：
  - &emsp;&emsp;$|S| \lt 26$ ：一定存在未出现过的小写字母，找到未出现字母中最小的一个接到原字符串后方即可。
  - &emsp;&emsp;$|S| = 26$ ：没有可以额外添加的字母了。为了让字典序增大，$S$ 中需要有有字符改变。
    
    &emsp;&emsp;思考可以发现，每个字符的可变范围是在他之后出现的字符, 为了让字典序增加且增加最少。
    我们可以**最后一个**满足后面的字符中存在比他大的字符，即 $i$ 满足 $\exists {S_j}_{\{j \in [i + 1, |S|]\}} > S_i$。
    
    之后我们找到的 $S_i$ 前的 $S$ 保留， 将 $S_i$ 换成**在他之后出现过且比 $S_i$ 大的最小字母**, 再将后面的字符清空输出。
    
    如果找不到这样的 $S_i$ 则输出 $-1$。 ~~当然也可以特判 "zyxwvutsrqponmlkjihgfedcba"。~~
  
  **复杂度: $O(n)$**
  
### Code: 
---

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

const int kMaxN = 26 + 1;
char s[kMaxN];
bool vis[kMaxN];
int main() {
  std::cin >> (s + 1);
  int n = strlen(s + 1);
  if (n < 26) {
    for (int i = 1; i <= n; i++) vis[s[i] - 'a'] =  (true);
    for (int i = 0; i < 26; i++) 
      if (!vis[i]) {
        printf("%s%c\n", s + 1, i + 'a'); // 找到第一个没出现过的小写字母并输出
        break;
      }
  } else {
    int max_suf = -1; // 记录后缀中出现的最大字符
    bool solution_flag = 0; 
    for (int i = n; i >= 1; i--) {
      if (max_suf > s[i] - 'a') {
        solution_flag = 1;
        for (int j = 1; j < i; j++)
          putchar(s[j]);
        for (int j = s[i] - 'a' + 1; j < 26; j++) 
          if (vis[j]) {
            putchar(j + 'a');
            break;
          }
        putchar('\n');
        break;
      }
      max_suf = std::max(max_suf, s[i] - 'a');
      vis[s[i] - 'a'] = 1;
    }
    if (!solution_flag) puts("-1");
  }
}
```

---

## 作者：copper_ingot (赞：0)

这题比较简单，就是给你一个各字符互不相同的字符串，让你求字典序比它大且最小的，并且各字符互不相同的字符串。

做这题要分类讨论。有两种情况：

（以下用 $s$ 表示原字符串，$\lvert s \rvert$ 表示 $s$ 的长度）

+ $\lvert s \rvert < 26$。只需要在 $s$ 后面加上一个未出现过的最小的小写字符即可。（我用了一个 bool 数组存储字符是否出现过，用 map 其实也可以）

+ $\lvert s \rvert = 26$。这时就不能往后添加字符了，但是我们可以从后往前枚举 $s_i$，如果出现 $s_i$ 后面有一个比 $s_i$ 大且最小的字符 $s_j$，那么就把 $s_i$ 改成 $s_j$，并删除 $s_i$ 后面所有的字符。

最后输出改变后的 $s$，这题就结束了。

记得有 $-1$ 的情况 `zyxwvutsrqponmlkjihgfedcba`，~~写代码时差点忘了~~

贴上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[30]; bool a[128];
int main(){
	scanf("%s", s);
	for (int i = 0; i < strlen(s); i++) a[s[i]] = true;
   //情况1
	if (strlen(s) < 26) for (int i = 97; i <= 122; i++)//本人习惯用int
		if (!a[i]){printf("%s%c", s, char(i)); return 0;}
   //情况2
   char minn = char('z' + 1);
	for (int i = strlen(s) - 1; i >= 0; i--){
		for (int j = i + 1; j < strlen(s); j++)
			if (s[j] > s[i]) minn = min(minn, s[j]);
		if (minn != char('z' + 1)){
			s[i] = minn;
			for (int j = 0; j <= i; j++) printf("%c", s[j]);
			return 0;
		}
	}
   printf("-1");
	return 0;
}
```

---

