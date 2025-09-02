# Dima and Text Messages

## 题目描述

Seryozha has a very changeable character. This time he refused to leave the room to Dima and his girlfriend (her hame is Inna, by the way). However, the two lovebirds can always find a way to communicate. Today they are writing text messages to each other.

Dima and Inna are using a secret code in their text messages. When Dima wants to send Inna some sentence, he writes out all words, inserting a heart before each word and after the last word. A heart is a sequence of two characters: the "less" characters (<) and the digit three (3). After applying the code, a test message looks like that: <3 $ word_{1} $ <3 $ word_{2} $ <3 ... $ word_{n} $ <3.

Encoding doesn't end here. Then Dima inserts a random number of small English characters, digits, signs "more" and "less" into any places of the message.

Inna knows Dima perfectly well, so she knows what phrase Dima is going to send her beforehand. Inna has just got a text message. Help her find out if Dima encoded the message correctly. In other words, find out if a text message could have been received by encoding in the manner that is described above.

## 说明/提示

Please note that Dima got a good old kick in the pants for the second sample from the statement.

## 样例 #1

### 输入

```
3
i
love
you
<3i<3love<23you<3
```

### 输出

```
yes
```

## 样例 #2

### 输入

```
7
i
am
not
main
in
the
family
<3i<>3am<3the<3<main<3in<3the<3><3family<3
```

### 输出

```
no
```

# 题解

## 作者：Withershine (赞：5)

大家好，我不喜欢 `string`，所以我选择用 `char` 来写。

[~~题目传送门，但不是洛谷。~~](https://codeforces.com/problemset/problem/358/B)

吐槽一下，这个翻译翻译的并不好，翻译中并没有说明“爱心”是指 `<3`，还是得去自己翻。

### 正文
将读入的单词连在一起，并穿插爱心，注意这里首尾都是爱心，需要手动补充。最后将得到的序列与输入的字符串进行比对即可。

### 关于样例 $2$
在样例 $2$ 中，输出 `no` 并不是因为前面多了一个 `the`，而是因为输入的字符串中没有 `no` 这个单词。题目中第三步是“在句子的任意地方插入字符”，因此多出来的 `the` 是第三步操作得来的，故无影响。

### 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	{
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n;
char s[1100000] , in[1100000] , s1[1100000];
ll len_in , len , o;
signed main()
{
	n = read();
	in[o++] = '<';
	in[o++] = '3';
	fr(i , 1 , n)
	{
		scanf("%s" , &s);
		len_in = strlen(s);
		fr(i , 0 , len_in - 1)
		{
			in[o] = s[i];
			o++;
		}
		in[o++] = '<';
		in[o++] = '3';
	}
	scanf("%s" , s1);
	ll k = 0;
	len = strlen(s1);
	fr(i , 0 , len - 1)
	{
		if(in[k] == s1[i])
		{
			k++;
		}
	}
	if(o == k)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}
   	return 0;
}
```

### 总结
认真读题真的很重要。

---

## 作者：清小秋ovo (赞：1)

# CF358B

[原题链接](https://codeforces.com/problemset/problem/358/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF358B)

## 题意
题意比较简单。

首先给出一个 $n$。在后面的 $n$ 行中一行给出一个字符，然后进行如下的操作：

1. 将所有单词连接到一起。
2. 在每个单词与每个单词之间加上 "<3"。
3. 随机加生成好的信息中加入字符。

随后给出一个字符串，判断根据这个字符串是否符合了刚刚提到的操作规则，并输出判断结果。

## 解题思路

根据题意模拟并生成一个标准的字符串。

随后扫一遍给出的字符串并判断给出的字符串中有序包含标准字符串中的所有字符。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b,tmp,love="<3";
int cnt,n;

void print(string b){
  //从前往后对比
	for(int i=0;i<b.size();i++){
		if(b[i]==a[cnt])cnt++;
	}
	if(cnt==a.size())cout<<"yes"<<endl;
	else cout<<"no"<<endl;
}

int main(){
	cin>>n;
	a+=love;
	string tmp;
	for(int i=0;i<n;i++){
		cin>>tmp;
		a+=tmp;
		a+=love;
	} //生成标准字符串
	cin>>b;
	print(b);
}
```




---

## 作者：kkksc031 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF358B)


**爱心表达成字符串为 "<3"**
# 题意
把给出的单词串联起来，在每两个单词间插入爱心，给出另一串字符，如果第一串字符能通过添加字符得到第二串字符，输出 `yes`，否则输出 `no`。
# 思路
循环第二串字符，看看里面是否有一个子串为第一串字符。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string h, a;
int main()
{
   cin>>n;
   a+="<3";
   while(n--)
   {
   	  cin>>h;
   	  a+=h;
   	  a+="<3";
	} 
    string b;
    cin>>b;
    int s=0,t=0;
    for(int i=0;i<b.size();i++)
    {
    	if(a[t]==b[i])t++,s++;
	}
	if(s==a.size())cout<<"yes\n";
	else cout<<"no\n";
  return 0;
}
```

---

## 作者：sunhaozhe111022 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF358B)

# 思路：

先输入单个的字符串，再用一个新的字符串用来记录之前的字符串并加上“爱心”。最后判断记录的字符串和最终字符串相同的字符数是否等于记录字符串的长度。

# 实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,ans;
string a,s,p;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		s+="<3";//加入“爱心” 
		s+=a; 
	}
	s+="<3";//在尾部加入“爱心”
	cin>>p;
	int k=s.size();
	for(int i=0;i<p.size();i++)
	{
		if(s[t]==p[i]) t++,ans++;//记录相同的字符数有多少 
	}
	//判断+输出 
	if(ans==k) cout<<"yes";
	else cout<<"no";
	return 0;
}

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/CF358B)
## 思路
首先按照操作一和操作二得到一个没有进行操作三的字符串 $s$，再判断 $s$ 是否是题目给定的字符串的子序列即可。
## Code
```cpp
#include<iostream>
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,cnt=0;
	cin>>n;
	string str="<3",s,str2;
	for(int i=0;i<n;++i) cin>>s,str+=s+"<3";//模拟操作一和操作二
	cin>>str2;
	for(int i=0;i<str2.size();++i) if(str2[i]==str[cnt]) ++cnt;//从左至右累加相同部分的长度
	cout<<(cnt==str.size()?"yes":"no");//如果相同部分的长度与只进行了操作一和操作二的字符串的长度相等就输出yes，反之输出no
	return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

**明确一点，题目翻译中没有说的，爱心其实是指 ```<3```**

## 思路

通过观察可以发现短语的结构为：```<3word_1<3word_2<3 ⋯ word_n<3```。

首先在插入字符前确定短语 $s$ 为：```<3 + word_1 + <3  ⋯  <3 + word_n + <3```。

接下来只需要将 $s$ 与输入中的那个字符串 $c$ 比较一下，如果发现 $c$ 比 $s$ 多出了字符，**不要**输出 ```no```，这种其实是合法的，因为可以在句子的任意地方插入字符。但是，如果少了字符，这种一定是不合法的，输出 ```no``` 就好了。如果扫完了发现都是合法的，输出 ```yes```。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	string t,s="<3";
	for(int i=0;i<n;i++)
	cin>>t,s+=t,s+="<3";
	cin>>t;
	int i=0,j;
	for(j=0;j<t.size()&&i<s.size();j++){
		if(s[i]==t[j])
		i++;
	}
	if(i==s.size())cout<<"yes\n";
	else cout<<"no\n";
	return 0;
}
```



---

## 作者：InversionShadow (赞：0)

首先是拼接：每输入一个字符串就在答案串加上当前字符串以及 `<3`，**初始为 `<3`**。

然后是判断：逐位判断，去判断题目给定的字符串中是否按顺序包含了这个字符串中的所有字母，如果是则输出 `yes`，否则输出 `no`。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
string s, ans = "<3", b;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    ans += s + "<3";
  }
  cin >> b;
  int cnt = 0;
  for (int i = 0; i < b.size(); i++) {
    if (b[i] == ans[cnt]) {
      cnt++;
    }
  } 
  if (cnt == ans.size()) {
    cout << "yes\n";
  } else {
    cout << "no\n";
  }
  return 0;
}
```

---

## 作者：ZQIN_P (赞：0)

[在我的博客中阅读](https://zqin-blog.netlify.app/2023/08/26/CF358B-Dima-and-Text-Messages-%E9%A2%98%E8%A7%A3/)

[题目传送门](https://www.luogu.com.cn/problem/CF358B)

## 题目大意：
给出 $n$ 个单词，之后将这些单词按顺序拼接起来，再在所有单词前和最后一个单词后加上爱心（```<3```），最后在其中任意位置加上任意字符。问能否通过这样的操作，使得到的一条信息与给出的最终信息相同。

## 思路：
因为最后一步可以在任意位置加入任意字符，故我们不需要考虑多出来的那些字符，只需要考虑所有的单词是否出现过，以及所有单词前和最后一个单词后是否有爱心。

我们可以在输入时就将所有的单词拼接起来，同时完成添加爱心的操作。代码如下：
```cpp
for(int i=1;i<=n;i++){
	cin>>word;
	words+=word+"<3";
}
```

之后我们只要去比较最终信息中是否按顺序包含了这个字符串中的所有字母，如果是则输出 ```yes```，反之则输出 ```no```。比较部分的代码如下：
```cpp
bool compare(string a,string b){
    int w=0;
    for(int i=0;i<b.size();i++){
        if(b[i]==a[w]) w++;
        if(w==a.size()) return true;
    }
    return false;
}
```

完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string words="<3",word,message;
bool compare(string a,string b){
    int w=0;
    for(int i=0;i<b.size();i++){
        if(b[i]==a[w]) w++;
        if(w==a.size()) return true;
    }
    return false;
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>word;
        words+=word+"<3";
    }
    cin>>message;
    if(message.size()<words.size()){
        printf("no");
        return 0;
    }
    if(compare(words,message)) printf("yes");
    else printf("no");
    return 0;
}
```

## 总结：
本题考查字符串基本操作与比较，难度不高，但是需要一定的思考才能确定最终的方法。

---

## 作者：WinterRain208 (赞：0)

本题的第一篇题解。

### 题意

有一个字符串，对他实行这三个操作：

第一步将所有单词连在一起

第二步在每个单词前和最后一个单词后加上爱心。

第三步在句子的任意地方插入字符。

给你一个字符串，问它是否有可能是最终字符串。

### 做法

首先，根据输入的单词我们可以求出如果不在句子之间加任何字母的字符串的样子，即第二步结束后字符串的样子。

随后因为执行第三步前的字符串所有字符在执行第三步时不会丢失 ，所以我们只要判断执行第三步之前的字符串是不是执行之后的字符串的子序列即可。

具体求子序列可以线性实现，用一个指针在扫描最终字符串时指向第三步前的字符串，最后判断指针位置。

其他细节请结合代码理解。

### 代码

这里只给出出主要部分 。

```cpp
F(i,0,str3.size()-1)
	if(str3[i]==str2[pos])++pos;
puts(pos==str2.size()?"yes":"no");
```

其中str3是最终输入的字符串，str2是第三步前的字符串。

---

