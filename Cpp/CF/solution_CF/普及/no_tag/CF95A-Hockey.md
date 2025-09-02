# Hockey

## 题目描述

Petya loves hockey very much. One day, as he was watching a hockey match, he fell asleep. Petya dreamt of being appointed to change a hockey team's name. Thus, Petya was given the original team name $ w $ and the collection of forbidden substrings $ s_{1},s_{2},...,s_{n} $ . All those strings consist of uppercase and lowercase Latin letters. String $ w $ has the length of $ |w| $ , its characters are numbered from $ 1 $ to $ |w| $ .

First Petya should find all the occurrences of forbidden substrings in the $ w $ string. During the search of substrings the case of letter shouldn't be taken into consideration. That is, strings "aBC" and "ABc" are considered equal.

After that Petya should perform the replacement of all letters covered by the occurrences. More formally: a letter in the position $ i $ should be replaced by any other one if for position $ i $ in string $ w $ there exist pair of indices $ l,r $ ( $ 1<=l<=i<=r<=|w| $ ) such that substring $ w[l ... r] $ is contained in the collection $ s_{1},s_{2},...,s_{n} $ , when using case insensitive comparison. During the replacement the letter's case should remain the same. Petya is not allowed to replace the letters that aren't covered by any forbidden substring.

Letter $ letter $ (uppercase or lowercase) is considered lucky for the hockey players. That's why Petya should perform the changes so that the $ letter $ occurred in the resulting string as many times as possible. Help Petya to find such resulting string. If there are several such strings, find the one that comes first lexicographically.

Note that the process of replacements is not repeated, it occurs only once. That is, if after Petya's replacements the string started to contain new occurrences of bad substrings, Petya pays no attention to them.

## 样例 #1

### 输入

```
3
bers
ucky
elu
PetrLoveLuckyNumbers
t
```

### 输出

```
PetrLovtTttttNumtttt
```

## 样例 #2

### 输入

```
4
hello
party
abefglghjdhfgj
IVan
petrsmatchwin
a
```

### 输出

```
petrsmatchwin
```

## 样例 #3

### 输入

```
2
aCa
cba
abAcaba
c
```

### 输出

```
abCacba
```

# 题解

## 作者：柳易辰 (赞：5)

## 1.前置知识
本题只需要基本的字符串（`string`）操作，有一点思维难度，颜色大概为黄。算法：字符串 & 模拟 & 贪心。

&nbsp;
## 2.题意翻译
题目翻译稍微有一点错误，建议看 [Codeforces 原题](https://codeforces.com/problemset/problem/95/A)， 中文简化一下：

给定一个正整数 $n(1\le n\le100)$ 和 $n$ 个字符串 $s_i(1\le|s_i|\le100)$，另外还有一个字符串 $w(1\le |w|\le100)$ 和一个字母 $c$。（字符串均由大小写字母组成）

设字符串 $w$ 的第 $i$ 个字母为 $w_i$。对于 $1\le l\le r\le|w|$，如果字符串 $w[l\dots r]=s_i$（不论大小写），那么 $\forall l\le j\le r$，字母 $w_j$ **必须**被替换。每个字母只能替换一次，设替换后的字符串 $w$ 为 $w'$，则 $w_j\neq w_j'$。

要使字符串 $w'$ 中字母 $c$ 的出现次数尽可能多，求字母 $c$ 出现次数最多时的 $w'$。若有多个字符串 $w'$ 满足字母 $c$ 的出现次数最多，输出字典序最小的字符串 $w'$。

&nbsp;
## 3.思路
1. 输入 $n,s_1\dots s_n,w,c$，将所有字符串和字母 $c$ 改为小写，方便处理。
2. 把字符串 $w$ 中所有要修母的字符遍历出来。由于 $|w|$ 很小，暴力匹配。时间复杂度 $O(|w|^3)$，可过。
3. 对于每一个要修改的字母 $i$，如果 $i=c$，那么尽量往字典序小的替换，即替换为字母 $\tt A$ 或 $\tt a$。当然，因为替换后的字符不能与原来的相同，所以 $i=\tt a$ 时，替换为字母 $\tt B$ 或 $\tt b$。否则替换为字母 $c$。时间复杂度 $O(|w|)$。这样替换能保证字母 $c$ 出现次数最多且 $w'$ 字典序最小，易证。
4. 按原先字符串 $w$ 中字母的大小写输出。

四步就可以了，第一步处理要修改的字母，第二步处理修改为字典序最小。时间复杂度 $O(|w|^3)$，KMP 优化后为 $O(|w|^2)$，主要都是第一步的时间，不优化也行。  
&nbsp;  
## 4.部分代码
第一步：输入 & 改小写  

小写函数：
```cpp
void lowercase(string &k)
{ 
    for (int i(0); i < (int)size(k); ++i)
        if (k[i] < 'a')
            k[i] += 32; 
} 
```
```cpp
cin >> n;
for (int i(1); i <= n; ++i) cin >> s[i], lowercase(s[i]);
cin >> w >> c; lowercase(x = w); const int l((int)size(w));
```
字符串 $x$ 是字符串 $w$ 的小写。  
&nbsp;

第二步：处理位置
```cpp
for (int i(1); i <= n; ++i)
	for (int j(0); j + (int)size(s[i]) <= l; ++j)
		if (x.substr(j, size(s[i])) == s[i])
			for (int k(j); k < j + (int)size(s[i]); ++k)
				b[k] = true;
```
$b$ 是记录字符串 $w$ 中任意一个字母要不要修改的 `bool` 数组。若 $w_i$ 要修改，$b_i=\tt true$，否则 $b_i=\tt false$。  
&nbsp;

第三步：替换
```cpp
for (int i(0); i < l; ++i)
	if (b[i])
	{
		if (x[i] == c) x[i] = ((c == 'a') ? 'b' : 'a');
		else x[i] = c;
	}
```
简单易懂，不必解释。  
&nbsp;

第四步：输出 & 恢复大小写
```cpp
for (int i(0); i < l; ++i)
    if (w[i] < 'a') putchar(x[i] - 32);
    else putchar(x[i]);
```
那么这道题就简单地结束了。

---

## 作者：alan1118 (赞：3)

一道字符串的模拟题模拟题，不难，但是有一些细节要注意。

## 题意

给定一个字符串 $str$，$n$ 个禁止出现的字符串 $s_1,s_2,\ldots,s_n$ 和一个幸运字母 $ch$。

### 现在要求：

1. 字符串 $str$ 中如果出现禁止字符串，那么禁止字符串中的每一个字符都要修改；

2. 修改后的字符串中幸运数字出现的次数越多越好（大小写不限）；

3. 保证前两条的前提下，修改后的字符串的字典序尽可能小。

## 思路

### 预处理

首先现将 $str$（后边用 “原字符串” 表示）和禁止出现的字符串统一变成小写，方便处理。

### 记录需要修改的位置
枚举原字符串的每一个字符作为左端点，以这个点向右的 $|s_i|$ 个字符组成的字符串如果等于 $s_i$，那么就将这个点标记为 `true`，表示要修改。

知识点补充：`str.substr(pos, len)`：$str$ 字符串 $[pos,\ pos+len)$ 所构成的字符串（$pos,len$ 均为整数）。


### 修改字符串
枚举原字符串的每一位，如果需要替换就替换为幸运字母就可以了。但是有一点要注意，如果这一位本来就是幸运字母的话，因为不能替换成与原来一样的字母，要保证字典序最小，只能换成 `a`，但如果幸运字母就是 `a` 的话就只能替换成 `b` 了。

### 输出
这里要注意一点，题目中要求修改后字符串的大小写与原字符串保持一致。

## 代码
```cpp
#include <iostream>
#include <string>
using namespace std;

int n;
string str;
char ch;
string s[105];
bool isch[105];

void tolow(string& c) // 转成小写
{
	for(int i = 0; i < c.size(); i++)
		c[i] = (c[i]>='a') ? c[i] : c[i]-'A'+'a';
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> s[i];
		tolow(s[i]);
	}
	cin >> str;
	cin >> ch;
	
	string t = str;
	tolow(t);
	for(int i = 1; i <= n; i++) // 查找需要修改的字符
		for(int l = 0; l+s[i].size() <= t.size(); l++)
			if(t.substr(l, s[i].size()) == s[i])
				for(int j = l; j < l+s[i].size(); j++)
					isch[j] = true;
					
	for(int i = 0; i < t.size(); i++) // 修改
		if(isch[i])
		{
			if(t[i] == ch) t[i] = (ch == 'a') ? 'b' : 'a';
			else t[i] = ch;
		}
	
	for(int i = 0; i < t.size(); i++) // 输出
	{
		if(str[i] >= 'a') cout << t[i];
		else cout << char(t[i]-'a'+'A');
	}
	return 0;
}
```

---

## 作者：syf159 (赞：0)

## 分析
本题考点为字符串操作，数据不大，直接模拟即可。

1. 读入队员名字，队伍名字，用 $$，和队员们喜爱的字母（$love$）,并且大写转小写；
```cpp
string ch_sma(string x)
{
    for(int i=0; i<x.size(); i++)
    {
        if(x[i]>='A'&&x[i]<='Z')
		{
			x[i]=(char)(x[i]-'A'+'a');
		} 
    }
    return x;
}

  cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>mem[i];
		mem[i]=ch_sma(mem[i]);
	}
	cin>>team>>love;
	ans=team;
	team=ch_sma(team);
	if(love>='a'&&love<='z') love=love-'a'+'A';
```
2. 用原队伍名字匹配队员名字，匹配上的在 $ans$ 字符串中替换；
```cpp
void change(int x,int len)
{
	for(int i=x; i<x+len; i++)
	{
		if(team[i]!=(love-'A'+'a'))
		{
			if(ans[i]>='A'&&ans[i]<='Z') ans[i]=love;
		    else ans[i]=love-'A'+'a';
		}
		else
		{
			if(ans[i]>='A'&&ans[i]<='Z') ans[i]=((love=='A')?'B':'A');
		    else ans[i]=((love=='A')?'b':'a');
		}
	}
}
for(int i=0; i<team.size(); i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(team.substr(i,mem[j].size())==mem[j]) change(i,mem[j].size());
		}
	}
```
3. 最后输出 $ans$ 字符串即可

## 注意事项
1. 在这题里面，输出的 $ans$ 要与原队名的大小写相同；
2. 当要替换的字符与喜爱的字符相等时，要替换成不一样的字符。

---

## 作者：qingchenMC (赞：0)

## 思路

字符串模拟题。跟着题义做就行，但是对于题目中的隐藏条件或者要求，也要能够注意到。

输入之后，按顺序遍历字符串 $s$，暴力枚举 $l$ 端点，找出所有名字中最大的长度 $mx$，从每个 $l$ 开始截取 $mx$ 个字符，每多截取一个就拿截出来的字符串与每个名字一一对比（在这里为了方便我重载了 `string` 的逻辑等于，使其忽视大小写）。如果相同，再用一个循环，将 $[l,r]$ 这段区间标记上（$del[m]=1$）。

上述操作完成后，遍历字符串 $s$，检查每一个字符上是否有标记。若有，先判断要改的字符是否和原来的一样。如果一样，再判断这个字符是不是 `a`（注意大小写！）。如果是，因为要字典序最小，所以把他改为 `b`。如果不是 `a`，那就可以改为字典序最小的 `a`。如果这个字符和原来的不一样，就直接改为新字符。

还有，因为题目要求替换时要保留原字符串大小写，所以我们在一开始遍历字符串 $s$，如果一个字符是大写，将标记数组对应下标设为 $1$。在最后替换时检查标记数组，如果是 $1$，就将该字符转为大写。

最后输出，我们就把这题做完了。这道题很考验细心的能力。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

string s,name[102];
char t;
int l=-1;
bool del[102],up[102];

bool operator==(string a,string b){
	if(a.size()==b.size()){
		for(int i=0;i<a.size();i++){
			if(tolower(a[i])!=tolower(b[i])){
				return 0;
			}
		}
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>name[i];
		l=max(l,(int)name[i].size());
	}
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		if(isupper(s[i])){
			up[i]=1;
		}
	}
	for(int i=0;i<s.size();i++){
		string tmp;
		for(int j=i;j<=i+l-1&&j<s.size();j++){
			tmp+=s[j];
			for(int k=1;k<=n;k++){
				if(tmp==name[k]){	
					for(int m=i;m<=j;m++){
						del[m]=1;
					}
				}
			}
		}
	}
	for(int i=0;i<s.size();i++){
		if(del[i]){
			if(tolower(s[i])==t){
				if(tolower(s[i])=='a'){
					s[i]='b';
				}
				else{
					s[i]='a';
				}
			}
			else{
				s[i]=t;
			}
			if(up[i]){
				s[i]=toupper(s[i]);
			}
		}
	}
	cout<<s;
	return 0;
}
//https://codeforces.com/contest/95/submission/302871733
```

---

## 作者：OIerZhang (赞：0)

# [CF95A Hockey](https://www.luogu.com.cn/problem/CF95A)

这题坑点还是挺多的，不过翻译挺良心。

## 思路

这题的数据范围极小，只有 $100$，我们就可以直接用暴力解决。

我们来一点一点地分析（翻译里的六点）：

1. 由于判断字符串不考虑大小写，所以在开头我们要先把字符串统一转小写，方便处理。
2. 判断 $w_i$ 是否被替换，我们直接暴力枚举 $l$，再枚举所有人名，如果相等就打上标记。
3. 要使队员们喜欢的字符出现次数最多，我们可以把打上标记（需要替换）的字符全部替换成这个字符。
4. 要求保留原字符串大小写，我们需要先保留原字符串，输出时将答案与它的大小写匹配即可。
5. 如果队员们喜欢的字符与要修改的字符一样，这样是没有意义的，根据第三点字典序最小，我们可以贪心地把它变成 `a`。（这里有一个坑，稍后解释）
6. 如果修改过一次反而出现了人名，不需要再改，这是符合题意的。

如果你按照这六点写完了代码，你就会 [Wrong answer on test 9](https://mirror.codeforces.com/problemset/submission/95/302825835)。测试点如下：

```plaintext
3
ab
Ba
aB
ABBA
a
```

我们会发现，当队员们喜欢的字符与要修改的字符都为 `a` 时，不能把它变成 `a`，这时应把它变成 `b`。

## 代码

时间复杂度 $O(n^3)$，足以通过此题。当然，各位大佬可以用 KMP 将其优化到 $O(n^2)$。

```cpp
// CF-95A

#include <bits/stdc++.h>
#define int long long
#define ios ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string name[105], s, ans;
bool change[105];

void fill(int l, int r) // 标记
{
    for (int i = l; i <= r; i++)
        change[i] = true;
}

string lower(string str) // 转小写
{
    for (int i = 0; i < str.size(); i++)
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] += 32;
    return str;
}

void replace() // 大小写匹配
{
    for (int i = 0; i < s.size(); i++)
        if ('A' <= s[i] && s[i] <= 'Z')
            ans[i] -= 32;
}

signed main()
{
    ios;
    int n;
    char key;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> name[i], name[i] = lower(name[i]); // 1. 转小写
    cin >> s >> key;
    ans = lower(s);
    for (int l = 0; l < ans.size(); l++)
    {
        for (int i = 1; i <= n; i++)
        {
            string cmp = ans.substr(l, name[i].size()); // 取对应子串
            if (cmp == name[i]) // 2. 相等打标记
                fill(l, l + name[i].size() - 1);
        }
    }
    for (int i = 0; i < ans.size(); i++)
    {
        if (change[i]) // 3. 把打上标记的字符替换
        {
            if (ans[i] == key) // 5. 贪心思想替换
            {
                if (key == 'a') // 坑点！！！
                    ans[i] = 'b';
                else
                    ans[i] = 'a';
            }
            else
                ans[i] = key;
        }
    }
    replace(); // 4. 大小写匹配
    cout << ans; // 6. 无需再次修改，直接输出
    return 0; // 圆满结束！
}
```

本题解不对 CtrlCV 工程师开放。

---

## 作者：FireFy (赞：0)

# CF-95A Hockey 题解

### 题目描述

有一个字符串 $w$，需要你以一个**给定的字母**  $letter$ 换给定的原串子序列（注意有些给定的字符串并不是原串的子序列），输出替换后的串 $w$。

注意以下几点：

- 如果要判断一个字符串是否为 $w$ 的子串，**不用区分大小写**，也就是说  `FIrefY`  和  `FireFy`  是一样的。

- 你要使这个 $letter$ 出现次数最多。

- 如果有多种解，**输出字典序最小的。**

- 输出时保留原字符串格式，即大小写。

- 更改时要注意**每个字符都要用其他字符去更改**，所以如果某个需要修改的字符和 $t$ **一样**，**则它需要修改成别的字符。**

  

### 题目分析与思路

#### **大体思路：大模拟**

枚举原串 $w$ ，如果发现 $w$ 中有给定的子串，那么进行标记。

最后统计 $w$ 中被标记的字符，并以 $letter$ 替换被标记的字符

#### **有些细节需要注意**：

1. 将 $w$ 转为小写方便比较的同时，将 $w$ 备份至 $w1$，方便比对与输出
2. 将字符转化为 $letter$ 的同时，如果被替换的字符为**大写**，那么替换的 $letter$ 也应该改成大写

## 然后就可以开码了！

### AC Code (注释的还比较详细，可以结合上文一起食用)



```cpp
#include <bits/stdc++.h>
using namespace std;
string s[110],ans;
int len[110],mark[110];
char letter,w[110],w1[110];//string is rubbish 
void change(int p) 
{
	if(w[p]==letter&&letter=='a') w[p]='b';//字典序最小 
	else if(w[p]==letter&&letter!='a') w[p]='a';//同上 
	else w[p]=letter;
}
int main()
{
	int i,j,k,n,m,sum;
	cin>>n;
	cin>>w;
	cin>>letter;
	m=strlen(w);
	for(i=1;i<=n;i++) 
	{
		cin>>s[i];
		len[i]=s[i].size();
		for(int j=0;j<len[i];j++) //禁止的字符串改小写 
		{
			if(s[i][j]<'a') s[i][j]+=32;
		}
	}
	for(i=0;i<m;i++) 
	{
		w1[i]=w[i];//备份 
		if(w[i]<'a') w[i]+=32;//原字符串大写转小写 
	}
	for(i=1;i<=n;i++)//枚举禁止的字符串 
	{
		for(j=0;j<m;j++)//枚举子串在 w 中的起始端点 
		{
			k=0;
			bool flag=0;
			while(114514)
			{
				if(s[i][k]!=w[j+k]||j+k>=m) break;//判断子序列
				if(k+1==len[i])
				{
					flag=1;
					break;
				}
				k++;
			}
			if(flag==1)
			{
				for(int p=j;p<j+len[i];p++) mark[p]=1;	
			}
				
		}
	}
	for(int i=0;i<m;i++)
	{
		if(mark[i]) change(i);
	}
	for(i=0;i<m;i++)
	{
		if(w1[i]<'a') cout<<char(w[i]-32);//改成大写 
		else cout<<w[i];
	}
	return 0;
 } 
```

---

## 作者：liuli688 (赞：0)

主要运用了 `std::string` 的一些函数，不过细节比较多。
### 前置知识：
`std::string` 的 `length()`（或 `size()`）和 `find(str,pos)` 两个函数。
#### 用法：
`length()` 函数返回字符串的长度。

`find(str,pos)` 函数可以用来查找字符串中一个字符/字符串在 `pos`（含）之后第一次出现的位置（若不传参给 `pos` 则默认为 `0`）。如果没有出现，则返回 `string::npos`（被定义为 `-1`，但类型仍为 `size_t`/`unsigned long`）。（摘自 [OI wiki](https://oi-wiki.org/lang/csl/string/#%E5%AF%BB%E6%89%BE%E6%9F%90%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%AC%AC%E4%B8%80%E6%AC%A1%E5%87%BA%E7%8E%B0%E7%9A%84%E4%BD%8D%E7%BD%AE)）

有了这个函数，字符串匹配就变得十分轻松了。

不过，虽然有了以上函数，本题坑点还是很多。
### 坑点：
```
Test: #3, time: 0 ms., memory: 0 KB, exit code: 0, checker exit code: 1, verdict: WRONG_ANSWER
Input
2
aCa
cba
abAcaba
c
Output
abAcaba
Answer
abCacba
Checker Log
wrong answer 1st words differ - expected: 'abCacba', found: 'abAcaba'
```
要注意大小写不敏感，且每个字符必须被替换成不同的字符。
```
Test: #9, time: 0 ms., memory: 4 KB, exit code: 0, checker exit code: 0, verdict: WRONG_ANSWER
Input
3
ab
Ba
aB
ABBA
a
Output
BAAB
Answer
AAAA
Checker Log
wrong answer 1st words differ - expected: 'BAAB', found: 'AAAA'
```
**每个**字符必须被替换成不同的字符，而不只是与除了队员们特别喜欢的字母之外的字母。
```
Test: #14, time: 0 ms., memory: 4 KB, exit code: 0, checker exit code: 0, verdict: WRONG_ANSWER
Input
2
A
B
abababBabaBBaBBBBAaaaAAAAA
a
Output
bababaAbabAAbAAAABbbbBBBBB
Answer
bababaAbabAAbAAAABbbbBBBBB
Checker Log
wrong answer 1st words differ - expected: 'bababaAbabAAbAAAABbbbBBBBB', found: 'baababBabaBBaBBBBAaaaAAAAA'
```
注意球队原来的名字中可能不止出现了一次同一个队员的名字。
### 思路：
首先，声明三个字符串 $s,s1,s2$。$s$ 为原队名，$s1$ 为转小写后的队名（方便匹配），$s2$ 为更改的队名。

接着对转小写后的每个球员名字 $name_i$ 进行匹配：不断对 $s1$ 进行 find 后，对需要替换的字符进行分类讨论：若它是队员们特别喜欢的字母，则换成队员们特别喜欢的字母之外的字典序最小的字母，否则换成队员们特别喜欢的字母。
### 代码：
```cpp
#define speedup ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define namesp using namespace std

#include <bits/stdc++.h>
namesp;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;

const int INF = INT_MAX;
const int UINF = INT_MIN;
const ll LINF = LONG_LONG_MAX;
const ll ULINF = LONG_LONG_MIN;

#define fp(i,a,b) for(i = a;i < b;i++)
#define fm(i,a,b) for(i = a;i > b;i--)
#define fl(i,a,b) for(i = a;i <= b;i++)
#define fg(i,a,b) for(i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register

#define freo(n,m) freopen(n,"r",stdin),freopen(m,"w",stdout)
#define frec(n) fclose(stdin),fclose(stdout)

#define mp make_pair
#define fir first
#define sec second

#define pb push_back
#define pf push_front

#define inline il

const int MAX = 1e2 + 1;
int n,len,p;
string name[MAX],s,s1,s2;
char l;

void lower(string& k)//转换为小写的函数
{ 
    reg int i,klen = k.length();
    fp(i,0,klen)
        if(k[i] < 'a')
            k[i] += 32; 
} 

char lch(char ch,bool caps)//求 ch 之外的字典序最小的字符，caps 表示是否大写
{
    reg int i;
    fp(i,0,26)
        if(i + (caps ? 'A' : 'a') != ch)
            return i + (caps ? 'A' : 'a');
}

signed main()
{
    speedup;
    reg int i,j;
    cin >> n;
    fp(i,0,n)
        cin >> name[i],lower(name[i]);
    cin >> s >> l;
    s2 = s1 = s;
    len = s.length();
    lower(s1);
    fp(i,0,n)//依次尝试球员名字
    {
        p = -1;//find 函数的返回值
        while(true)//重复执行，直到找不到这个球员的名字
        {
			p = s1.find(name[i],p+1);//一定要从 p+1 处开始找，否则会重复找同一个字符串
			if(p == name[i].npos)//找不到时跳出
				bk;
            len = name[i].length();
            fp(j,p,p+len)//替换球员名字内的字母
                if(s[j] <= 'Z')//如果是大写
                    if(s[j] == l - 32)//由于队员们特别喜欢的字母是小写，所以要-32
                        s2[j] = lch(s[j],true);//换成队员们特别喜欢的字母之外的字典序最小的字母
                    else
                        s2[j] = l - 32;//换成队员们特别喜欢的字母
                else//同理
                    if(s[j] == l)
                        s2[j] = lch(s[j],false);
                    else
                        s2[j] = l; 
        }
    }
    cout << s2;
    return 0;
}
```

---

