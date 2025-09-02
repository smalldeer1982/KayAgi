# [GCJ 2012 Qualification] Speaking in Tongues

## 题目描述

我们在 Google 发明了一种最棒的语言，名叫 Googlerese。要将文本翻译成 Googlerese，我们会把任意消息中的每一个英文小写字母替换为另一个英文小写字母。这个映射是一一对应且满射的，即同一个输入字母总会被替换为同一个输出字母，不同的输入字母总会被替换为不同的输出字母。一个字母可以被替换为其自身。空格保持不变。

举个例子（这里有个提示！），我们酷炫的翻译算法包括如下三个映射：'a' $\to$ 'y'，'o' $\to$ 'e'，'z' $\to$ 'q'。这意味着 "a zoo" 会变成 "y qee"。

Googlerese 基于最优的替换映射，并且我们永远不会改变它。在每一个测试用例中都是一样的。我们不会告诉你剩下的映射规则，否则题目就太简单了，但下面有一些例子或许会帮到你。

现在，给定一些 Googlerese 的文本，你能把它翻译回普通文本吗？

## 说明/提示

**限制（15 分）**

- 仅有一个测试点，且结果可见。
- $1 \leq T \leq 30$。
- $\mathbf{G}$ 最多包含 100 个字符。
- 不保证文本一定是有效的英语。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
ejp mysljylc kd kxveddknmc re jsicpdrysi
rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd
de kr kd eoya kw aej tysr re ujdr lkgc jv```

### 输出

```
Case #1: our language is impossible to understand
Case #2: there are twenty six factorial possibilities
Case #3: so it is okay if you want to just give up```

# 题解

## 作者：hema5177 (赞：15)

### 题目大意

通过样例与题面破译出输入的字符串。

### 思路

依题意得，每一个字母都对应了另一个字母，也就是说密匙只有一个，字母之间一一对应。那么就可以研究样例得出结论了。

研究方法无非就是写一个程序，排列好一一对应的字母，然后输出这个数组。

但是你会发现有一些字母没有被映射，这时由题面就很容易可以得出剩下字母的对应字母。

研究过程的代码如下：


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
char a[101];
int h[31];
int main()
{
	for(int j=1;j<=3;j++)
	{
		string s1,s2;
		getline(cin,s1);
		getline(cin,s2);
		for(int i=0;i<s1.size();i++)
		{
			if(s1[i]!=' ')
			{
				a[s1[i]-'a'+1]=s2[i];
				h[s2[i]-'a'+1]=1;//这是用来判断哪一些字母没有被映射的桶排数组。
			}
		}
	}
	cout<<"a[27]={'0',";
	for(int i=1;i<=26;i++)
	{
		if(i!=26) cout<<"'"<<a[i]<<"',";
		else cout<<a[i]<<"};\n";
	}
	for(int i=1;i<=26;i++)
	{
		if(!h[i]) cout<<char(i+'a'-1)<<" ";
	}
}
/*
排列好的样例有助于输入。
ejp mysljylc kd kxveddknmc re jsicpdrysi
our language is impossible to understand
rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd
there are twenty six factorial possibilities
de kr kd eoya kw aej tysr re ujdr lkgc jv
so it is okay if you want to just give up
*/
```

于是我们就得到了密匙数组。接下来的就很简单了。不过注意在用 `getline` 读取字符串时要注意前面的 `cin`，如果有则要用 `cin.ignore()`。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
char a[27]={'0','y','h','e','s','o','c','v','x','d','u','i','g','l','b','k','r','z','t','n','w','j','p','f','m','a','q'};
int n;
int main()
{
	cin>>n;
	cin.ignore();//防止getline读入换行符。
	for(int i=1;i<=n;i++)
	{
		string s;
		getline(cin,s);
		cout<<"Case #"<<i<<": ";
		for(int j=0;j<s.size();j++)
		{
			if(s[j]!=' ') cout<<a[s[j]-'a'+1];
			else cout<<' ';
		}
		cout<<endl;
	}
}
```

---

## 作者：DeekSeep_V3 (赞：8)

事先说明：蒟蒻水平很低，神犇大佬勿喷

**题意分析**
---
给定 $N$ 个字符串，要你将字符串 $S$ 转化成字符串 $C$。

**做法**
---

作为蒟蒻的我，看到此题第一眼：哇塞！~~打表题~~ 可是，还是得自己手推一下具体怎么转化，是吧？？？
我们来看样例 1 中的第三个字符串：
```
de kr kd eoya kw aej tysr re ujdr lkgc jv
```

它转化成了这个模样：
```
so it is okay if you want to just give up
```

通过一一对应的映射关系，也就是说，字符`d`映射成`s`，而`e`映射成`o`。

快乐的代码时间到了
---


```cpp
#include<bits/stdc++.h> 
using namespace std;
int t,a[30]={0,25,8,5,19,15,3,22,24,4,21,9,7,12,2,11,18,26,20,14,23,10,16,6,13,1,17};//打表出对应关系
string s;
int main(){
	cin>>t; 
    for(int i=0;i<=t;i++){
        getline(cin,s);
        if(i) cout<<"Case #"<<i<<": ";
        for(int j=0;j<s.size();j++){
            if(s[j]!=' ') cout<<char(a[s[j]-'a'+1]+'a'-1);//转化，如果不是空格才进行此操作
            else cout<<" ";
        }
         if(i) cout<<endl;//注意换行
        
    }
    return 0;
}
```
完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：MAX_CURRY_JAMES (赞：6)

# [题目传送门](https://www.luogu.com.cn/problem/P13311)

这题其实很简单，难点主要是在如何确定字母的变化。

这题用题目给的样例，再自己写个代码，就可以求出每个字母的变化。

字母变化代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s1[10],s2[10];
map<char,char>a;
string ch;
signed main(){
	cin>>n;
	getline(cin,ch);//因为getline会有换行符，所以在输入字符串前要先把换行符给读掉
	for(int i=1;i<=n;i++)
	getline(cin,s1[i]);//,cin>>ch;
	for(int i=1;i<=n;i++)
	getline(cin,s2[i]);//,cin>>ch;
	for(int i=1;i<=n;i++){
		for(int j=0;j<s1[i].size();j++)
		a[s1[i][j]]=s2[i][j];
	}
	for(char i='a';i<='z';i++)
	cout<<i<<' '<<a[i]<<'\n';
}
/*
3
ejp mysljylc kd kxveddknmc re jsicpdrysi
rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd
de kr kd eoya kw aej tysr re ujdr lkgc jv
our language is impossible to understand
there are twenty six factorial possibilities
so it is okay if you want to just give up
*/

```


最后附上本题正确代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,char>a;
int n;
string str[35];
string ch;
signed main(){
	/*
        这里不给出字母变化，请自己写出
       */
	cin>>n;
	getline(cin,ch);
	for(int i=1;i<=n;i++){
		getline(cin,str[i]);
	}
	for(int i=1;i<=n;i++){
		cout<<"Case #"<<i<<": ";
		for(int j=0;j<str[i].size();j++)
		cout<<a[str[i][j]];
		puts("");
	}
}
```
最后再提醒一句：题解仅供学习参考使用，请勿抄题解


这是本蒟蒻的第一篇题解，恳请管理大大通过

---

## 作者：Xiaoshangjie (赞：6)

### 题外话
首先看到这题的时候就意识到了是打表，只不过推规律的时候还是很 ~~痛苦~~ 烧脑的。
### 题意
给定 $T$ 个字符串 $S$，每次需要根据一种特定的映射，转换成正确的字符串 $G$ 并输出。
### 思路
在输入输出样例中找到字母，相互对应，列出对应关系 ~~（打表就行）~~，输出答案时代入即可。

需要注意的有：  
1. 题干中给出的 $3$ 个参考映射中似乎有错误的。比如第 $3$ 组输入：
   ```
   de kr kd eoya kw aej tysr re ujdr lkgc jv
   ```
   输出是
   ```
   so it is okay if you want to just give up
   ```
   可以看出，单词`eoya`的映射是`okay`，即`o`映射`k`，而题干中是这么写的：
   > 举个例子（这里有个提示！），我们酷炫的翻译算法包括如下三个映射：'a' → 'y'，**'o' → 'e'**，'z' → 'q'。这意味着 "a zoo" 会变成 "y qee"
   
   ~~就因为这个，本人在这里 WA 了一次。~~
3. 必须用`getline`之类的方式输入，因为原字符串 $S$ 有空格。
4. 特别注意：对于下面代码中的 $c$，必须要从 $0$ 开始，否则会少输出 $1$ 行且答案错位；同时要记得特判 $c=0$ 的情况。（$t$ 也要加上 $1$ 哦）
### code
```cpp
#include <bits/stdc++.h>
using namespace std;
char m[30]={'y','h','e','s','o','c','v','x','d','u','i','g','l','b','k','r','z','t','n','w','j','p','f','m','a','q'};

int main()
{
    int t,c=0;
    string s;
    
    cin>>t;
    t++;
    while(t--)
    {
        getline(cin,s);
        if(c) cout<<"Case #"<<c<<": ";
        for(int i=0;i<s.size(); i++)
        {
            if(s[i]==' ') cout<<" ";
            else cout<<m[s[i]-'a'];
        }
        if(c) cout<<endl;
        c++;
    }
    return 0;
}
```

---

## 作者：abc1234shi (赞：4)

# 题意
密码翻译的模拟题。

给你加密后的字符串让你求原字符串。
# 思路
题目只给了 $3$ 个字母规则。所以我们要求出剩余字母规则。

怎么求呢？我们看一下样例。

样例给了 $3$ 个字符串的加密后的字符串和 $3$ 个原字符串，我们可以推导出一些字母加密后是哪些字母。

用脑子算很麻烦，所以我们可以写一段代码，将样例的六串字符串输入进去（三串未加密，三串已加密），将原字符串与加密后字符串进行比对。用一个数组存储，将 'a' 编号为 $0$，'b' 编号为 $1$，以此类推，编号实现只需要用此字母的 ASCLL 码减去 'a' 的 ASCLL 码即可。以被加密字母的编号为下标，存储原字母（它的解密字母）。

代码如下：


```cpp
  int s[110];
  string a,b,c;
	a="ejp mysljylc kd kxveddknmc re jsicpdrysi";
	b="rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd";
    c="de kr kd eoya kw aej tysr re ujdr lkgc jv";
    string e,f,g;
    e="our language is impossible to understand";
    f="there are twenty six factorial possibilities";
    g="so it is okay if you want to just give up";
    for(int i=0;i<a.length();i++){
    	if(a[i]>='a'&&a[i]<='z'){
    		s[a[i]-'a']=e[i];
		}
	}
	for(int i=0;i<b.length();i++){
    	if(b[i]>='a'&&b[i]<='z'){
    		s[b[i]-'a']=f[i];
    		
		}
	}
	for(int i=0;i<c.length();i++){
    	if(c[i]>='a'&&c[i]<='z'){
    		s[c[i]-'a']=g[i];
		}
	}

```
输出一下，发现：

`
y h e s o c v x d u i g l b k r   t n w j p f m a
  `

不对啊，'q' 和 'z' 都没有解密字母？再回到题目，发现题目中有说 'z' 的解密字母是 'q'。

所以只差找 'q' 的解密字母了。

让我们看看，我们已经知道 $25$ 个字母的解密字母了，而不同的输入字母总会被替换为不同的输出字母，差一个 'q' 没有解密字母和一个 'z' 没有加密字母，所以 'q' 的解密字母就是 'z'。

我们知道每个字母解密后是什么了，接下来不就简单了吗？

接下来，我们输出字符串中的每一个字母的解密字母，只需要在刚刚存储的数组找到此字母的编号项并输出，就是它的解密字母了。

# 完整代码（细节在注释里）

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1100];
int main(){
  s['z'-'a']='q';
  s['q'-'a']='z';
	int n;
	cin>>n;
	scanf(" ");//清除一下缓存，不然输入不了
	string a,b,c;
	a="ejp mysljylc kd kxveddknmc re jsicpdrysi";
	b="rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd";
    c="de kr kd eoya kw aej tysr re ujdr lkgc jv";
    string e,f,g;
    e="our language is impossible to understand";
    f="there are twenty six factorial possibilities";
    g="so it is okay if you want to just give up";
    for(int i=0;i<a.length();i++){//字符串中从零开始存储
    	if(a[i]>='a'&&a[i]<='z'){
    		s[a[i]-'a']=e[i];
		}
	}
	for(int i=0;i<b.length();i++){
    	if(b[i]>='a'&&b[i]<='z'){
    		s[b[i]-'a']=f[i];
    		 
		}
	}
	for(int i=0;i<c.length();i++){
    	if(c[i]>='a'&&c[i]<='z'){
    		s[c[i]-'a']=g[i];
		}
    }
	//for(int i=0;i<26;i++)cout<<s[i]<<" ";
	for(int i=1;i<=n;i++){
		char k[1100];
		cin.getline(k,1100,'\n');//输入一行字符串，不会的可以学一下
        int h=0;
        while(k[h])h++;//计算字符数组大小
		cout<<"Case #"<<i<<": ";//输出第几个用例
		for(int j=0;j<h;j++){
			if(k[j]>='a'&&k[j]<='z'){
				cout<<s[k[j]-'a'];
			}
			else cout<<" ";//如果不是字母就是空格，直接输出空格
		}
		cout<<endl;//多组用例，要换行
	}
	return 0;
}
```

---

## 作者：_mei_tou_nao_ (赞：2)

## 解法说明
由题目可知：在本题中，所有的字母都是一一对应转换。那么我们便可以从样例中推导转换。如：`ejp mysljylc kd kxveddknmc re jsicpdrysi` 会转换为 `our language is impossible to understand` 其中：e 变为 o，j 变为 u……以此类推。我们便可以得到一个字母转换表。这里我使用 map 进行存储。
```

map<char, char>w = {
	{'a', 'y'}, {'b', 'h'}, {'c', 'e'}, {'d', 's'}, {'e', 'o'},
	{'f', 'c'}, {'g', 'v'}, {'h', 'x'}, {'i', 'd'}, {'j', 'u'},
	{'k', 'i'}, {'l', 'g'}, {'m', 'l'}, {'n', 'b'}, {'o', 'k'},
	{'p', 'r'}, {'q', 'z'}, {'r', 't'}, {'s', 'n'}, {'t', 'w'},
	{'u', 'j'}, {'v', 'p'}, {'w', 'f'}, {'x', 'm'}, {'y', 'a'},
	{'z', 'q'}
};
```
考虑到常规的 cin 输入字符串遇到空格时会停止输入，于是我们可以使用 `getline(cin, s);` 进行整行输入，之后再对照字母转换表进行转换后输出即可。
## 完整代码
```
#include <bits/stdc++.h>
using namespace std;

map<char, char>w = {
	{'a', 'y'}, {'b', 'h'}, {'c', 'e'}, {'d', 's'}, {'e', 'o'},
	{'f', 'c'}, {'g', 'v'}, {'h', 'x'}, {'i', 'd'}, {'j', 'u'},
	{'k', 'i'}, {'l', 'g'}, {'m', 'l'}, {'n', 'b'}, {'o', 'k'},
	{'p', 'r'}, {'q', 'z'}, {'r', 't'}, {'s', 'n'}, {'t', 'w'},
	{'u', 'j'}, {'v', 'p'}, {'w', 'f'}, {'x', 'm'}, {'y', 'a'},
	{'z', 'q'}
};

long long n;
string s;

int main() {
	cin >> n ;
	getline(cin, s);
	for (int i = 1; i <= n; i++) {
		getline(cin, s);
		cout << "Case #" << i << ": ";
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == ' ') {
				cout << " ";
			} else {
				cout << w[s[j]];
			}
		}
		cout << endl;
	}
	return 0;
}
```
最后，如果觉得这篇题解对您有用处的话，请点赞支持一下，谢谢。

---

## 作者：Wzmois (赞：1)

## 前记
这是 OI 题吗？给我干哪来了？感觉大脑的褶皱一瞬间被抚平了，梦回了 2025 年愚人节比赛时被爆杀的场景。对比来说，这道题确实简单了一点。

**Warning：本题解运用暴力打表，可能并非最优解法。**

## solution
### part 1
题目说要映射？有什么规律吗？好像没有吧......

不管，暴力！

先输入 Googlerese 的文本，再输入普通文本，并对应进行映射。
输入：
```
3
ejp mysljylc kd kxveddknmc re jsicpdrysi
our language is impossible to understand
rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd
there are twenty six factorial possibilities
de kr kd eoya kw aej tysr re ujdr lkgc jv
so it is okay if you want to just give up
```
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,char> m;
void sol(){
    string s,p;
    s="";p="";
    getline(cin,s);
    getline(cin,p);
    for(int i=0;i<s.size();i++){
        m[s[i]]=p[i];
    }
}
int main(){
    int T;
    string s;
    getline(cin,s);
    T=atoi(s.c_str());//字符串转数字
    while(T--){
        sol();
    }   
    for(auto t:m){
        cout<<"{'"<<t.first<<"','"<<t.second<<"',}";
    }
    return 0;
}
``````
哇！太神奇了！只有 `q` 和 `z` 没映射了，而题目说了 `z->p`，那么再一眼瞪出只剩下 `q->z` 这一条了（其他 26 个字母都已被映射，除了 `q->z`）。

解决了！映射之后应该是：
```
{' ',' '},//空格也要算进去
{'a','y'},
{'b','h'},
{'c','e'},
{'d','s'},
{'e','o'},
{'f','c'},
{'g','v'},
{'h','x'},
{'i','d'},
{'j','u'},
{'k','i'},
{'l','g'},
{'m','l'},
{'n','b'},
{'o','k'},
{'p','r'},
{'q','z'},
{'r','t'},
{'s','n'},
{'t','w'},
{'u','j'},
{'v','p'},
{'w','f'},
{'x','m'},
{'y','a'},
{'z','q'}
```
### part 2
预处理成功，那么就到了解密了。
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,char> m={
    {' ',' '},
    {'a','y'},
    {'b','h'},
    {'c','e'},
    {'d','s'},
    {'e','o'},
    {'f','c'},
    {'g','v'},
    {'h','x'},
    {'i','d'},
    {'j','u'},
    {'k','i'},
    {'l','g'},
    {'m','l'},
    {'n','b'},
    {'o','k'},
    {'p','r'},
    {'q','z'},
    {'r','t'},
    {'s','n'},
    {'t','w'},
    {'u','j'},
    {'v','p'},
    {'w','f'},
    {'x','m'},
    {'y','a'},
    {'z','q'}
};
void sol(int mois){
    string s,p;
    s="";p="";
    getline(cin,s);
    for(int i=0;i<s.size();i++) s[i]=m[s[i]];//解密
    cout<<"Case #"<<mois<<": "<<s<<endl;
}
int main(){
    int T;
    string s;
    getline(cin,s);
    T=atoi(s.c_str());
    for(int i=1;i<=T;i++) sol(i);
    return 0;
}
``````
完结撒花！
## 后记
**制作不易，如有问题请审核或读者将问题详细反馈给我。**

---

## 作者：封禁用户 (赞：1)

# [P13189 [GCJ 2016 #1A] The Last Word](https://www.luogu.com.cn/problem/P13189)
## 题目介绍：
要将文本翻译成 Googlerese，需要把每一个英文小写字母替换为另一个英文小写字母。这个映射是一一对应且满射的，即同一个输入字母总会被替换为同一个输出字母，不同的输入字母总会被替换为不同的输出字母。一个字母可以被替换为其自身。空格保持不变（但是你并**不知道**映射规则）。

## 题目分析：
这道题重点在于我们并**不知道**映射规则，所以必须靠他给的样例**推**出来。

举第一行的例子，可知：'e' $\to$ 'o'，'j' $\to$ 'u'，'p' $\to$ 'r'，'m' $\to$ 'l'。这里太多便不一一列举了。

完整映射表：'a' $\to$ 'y'，'b' $\to$ 'h'，'c' $\to$ 'e'，'d' $\to$ 's'，'e' $\to$ 'o'，'f' $\to$ 'c'，'g' $\to$ 'v'，'h' $\to$ 'x'，'i' $\to$ 'd'，'j' $\to$ 'u'，'k' $\to$ 'i'，'l' $\to$ 'g'，'m' $\to$ 'l'，'n' $\to$ 'b'，'o' $\to$ 'k'，'p' $\to$ 'r'，'q' $\to$ 'z'，'r' $\to$ 't'，'s' $\to$ 'n'，'t' $\to$ 'w'，'u' $\to$ 'j'，'v' $\to$ 'p'，'w' $\to$ 'f'，'x' $\to$ 'm'，'y' $\to$ 'a'，'z' $\to$ 'q'。

然后，只需将他们都存到一个数组里，再遍历每一个字符，如果是空格，就输出空格，否则输出对应的字符。

奉上代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long

char a[27] = {
    'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'z', 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', 'q'
};

signed main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n; ++i) {
        string s;
        getline(cin, s);
        cout << "Case #" << i << ": ";
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == ' ') {
                cout << ' ';
            } else {
                cout << a[s[j] - 'a'];
            }
        }
        cout << endl;
    }
    return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：Natural_Selection (赞：1)

# 题解：[P13311](https://www.luogu.com.cn/problem/P13311)

###### ~~感谢风，感谢雨，感谢 cz 让我有 tj 可写~~

## 思路

看到 $\texttt{Googlerese}$ 语言这个词时，第一反应就是肯定是 $\texttt{ASCII}$ 码找规律的题，结果按照题目给的三个栗子找了半天找不着一点，不得不说这题有点意思。

这时我发现了这句话：

+ Googlerese 基于最优的替换映射，并且我们永远不会改变它。在 **每一个测试用例中都是一样的**。

**那我们看样例就行了啊！**

经过对样例的输入输出的比较，我们很容易就找出了大部分的转换规则，其他的我们通过找规律也不难发现，这里就不放过程了。

最后，我们将其打表，如下：
```cpp
char wordlist[27]={
' ','y','h','e','s',
'o','c','v','x','d',
'u','i','g','l','b',
'k','r','z','t','n',
'w','j','p','f','m',
'a','q'};
```

然后就很简单了。

## [AC](https://www.luogu.com.cn/record/225113078) CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
char wordlist[27]={
' ','y','h','e','s',
'o','c','v','x','d',
'u','i','g','l','b',
'k','r','z','t','n',
'w','j','p','f','m',
'a','q'};
int t,k;
int main(){
	cin>>t;
	string str;
	while(getline(cin,str)){
		if((++k)-1==0){
			k++;
			continue;
		}
		printf("Case #%d: ",((++k)-2)/2);
		for(int i=0;i<str.size();i++){
            if('a'<=str[i]&&str[i]<='z'){
    			cout<<wordlist[int(str[i]-'a'+1)];continue;}
            cout<<str[i];
		}
		cout<<endl;
	}
    return 0;
}
```
#### 有意思的事

这是我一开始的代码（部分）：

```cpp
	cin>>t;
	while(t--){
		string str;
		getline(cin,str);
    }
```
它竟然把 $t$ 读到 `getline` 里了，迫不得已我把它改成上面那样才 AC 的。

---

## 作者：_ByTT_ (赞：1)

# 题解：P13311 [GCJ 2012 Qualification] Speaking in Tongues
### 题意
一种新的加密语言，每个字母都被替换掉了，但是加密规则是**永远不变**的，包括题目中给出的样例和举例。现在给你加密字符串，由**小写字母**和**空格**组成，求解密后的字符串。
### 思路
题目看起来有一点奇怪，但需要注意的是，加密规则永远不变，那么我们可以通过样例来判断加密规则。

#### 判断规则的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[27];int b[27];
int main(){
	string s1="ejpmysljylckdkxveddknmcrejsicpdrysirbcpcypcrtcsradkhwyfrepkymveddknkmkrkcddekrkdeoyakwaejtysrreujdrlkgcjv";
	string s2="ourlanguageisimpossibletounderstandtherearetwentysixfactorialpossibilitiessoitisokayifyouwanttojustgiveup";
	for(int i=0;i<s1.length();i++){
		a[int(s1[i]-'a')]=s2[i];
		b[int(s2[i]-'a')]++;
	}
	for(int i=0;i<26;i++){
		cout<<char('a'+i)<<":"<<a[i]<<',';
		if(b[i]==0) cout<<char('a'+i)<<"\n";
	}
	return 0;
}
```
注意代码中有两个数组，其中 $a$ 是用来记录样例规则的。而样例中有字母没有被提到，通过 $b$ 数组可以知道是 $q,z$，所以再回看题面，发现 $q$ 对应的是 $z$，那么由于二十六个字母已经被用光二十五个了，所以最后一个字母 $z$ 对应的就是最后一个字母 $q$。

输入输出时注意格式，需要使用可以输入空格的字符串输入。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char ch[40]={'y','h','e','s','o','c','v','x','d','u','i','g','l','b','k','r','z','t','n','w','j','p','f','m','a','q'};
int main(){
	int n;string s;
	cin>>n;getline(cin,s);
	for(int i=1;i<=n;i++){

		getline(cin,s);
		for(int j=0;j<s.length();j++){
			if(s[j]!=' ') s[j]=ch[int(s[j]-'a')];
		}
		cout<<"Case #"<<i<<": "<<s<<'\n';
	}
	return 0;
}
```

---

## 作者：IkillDream (赞：1)

# P13311 题解

## 思路

我们可以先构建一个字母映射表：

然后从样例输入输出中提取已知的字母映射。

接着推断未知字母的映射关系（利用字母频率统计或已知的英语单词）。

最后在反向翻译一下就好啦。

## [AC](https://www.luogu.com.cn/record/225033825) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int mp[26]={0};
	mp['y'-'a']='a';
	mp['e'-'a']='o';
	mp['q'-'a']='z';
	string g1="ejp mysljylc kd kxveddknmc re jsicpdrysi";
	string s1="our language is impossible to understand";
	string g2="rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd";
	string s2="there are twenty six factorial possibilities";
	string g3="de kr kd eoya kw aej tysr re ujdr lkgc jv";
	string s3="so it is okay if you want to just give up";
	for(int i=0;i<g1.size();i++) if(g1[i]!=' ') mp[g1[i]-'a']=s1[i];
	for(int i=0;i<g2.size();i++) if(g2[i]!=' ') mp[g2[i]-'a']=s2[i];
	for(int i=0;i<g3.size();i++) if(g3[i]!=' ') mp[g3[i]-'a']=s3[i];
	mp['z'-'a']='q';
	int t;
	cin>>t;
	cin.ignore();
	for(int kkk01=1;kkk01<=t;kkk01++){
		string g;
		getline(cin,g);
		string s;
		for(int i=0;i<g.size();i++)
			if(g[i]==' ') s+=' ';
			else s+=mp[g[i]-'a'];
		cout<<"Case #"<<kkk01<<": "<<s<<endl;
	}
	return 0;
}
```

## 后记

以上代码花费了我将尽一个小时的时间，如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

---

## 作者：_L_Z_Y_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13311)

### 这是一道$\color{red}\textsf{十分“简单的”}$找规律题

这道题它没有告诉我们所有的映射规则，所以我们只能一个一个对着样例找他的映射规则（本蒟蒻找了半小时OʌO）。

先把规律找出来，存在一个字符串```a```当中，再把输入的```s```一一对应，遇到空格就输出空格即可。

### 首先
先来看本蒟蒻找的规律：

![](https://cdn.luogu.com.cn/upload/image_hosting/pzhaxrop.png)

所以，我们```a```的字符串可以定义为：```string a="yhesocvxduiglbkrztnwjpfmaq";```。

那输入```s```后，轮流找```s[i]```，如果```s[i]```为空格，则直接输出空格，否则，用```s[i]-97```（注：97是小写a的ASCII码）。

那就这样啦！

哦，还有一件点，这个字符串会有空格，所以，我们要用:```getline(cin,s)```，输入完```n```，会有一个换行，所以，我们要再次使用```getline(cin,s)```。

这样，应该可以了吧？

行！上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a="yhesocvxduiglbkrztnwjpfmaq";//规律
long long n;
string s;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	getline(cin,s);
	for(int asd=1;asd<=n;asd++)
	{

		getline(cin,s);
		cout<<"Case #"<<asd<<": ";//千万不能忘！！！
		for(int i=0;i<s.size();i++)
		{
			if(s[i]!=' ')
			{
				cout<<a[s[i]-97];
			}
			else
			{
				cout<<' ';
			}
		}
		cout<<endl;
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/225139380)
##### ~~这是我第一篇题解，可以让我过吗？管理大大(OvO)。~~

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
将输入的字符串翻译回原文。

### 分析
~~这题真的有点坑！赤裸裸的解密？~~

首先我们要找到每一个字母对应的字母，这就需要观察题干以及样例的数据，最终可以发现如下：

```
a->y
b->h
c->e
d->s
e->o
f->c
g->v
h->x
i->d
j->u
k->i
l->g
m->l
n->b
o->k
p->r
q->?
r->t
s->n
t->w
u->j
v->p
w->f
x->m
y->a
z->q
```
最后一个 q 虽然没有，但是通过排除法得知对应的应该是 z。

~~一个一个找实在有些费眼睛~~，其实在题目下面的附件中已经含有密语与题解。

最后只需要输出对应的字母即可。

**注意**：输入建议用 getline，并对输入为空是重新输入。

## 参考代码
我下面是直接用 map 形成映射，自认为比较方便。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e5+5;
int t;
string s;
map<char,char>a;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>t;
    a['a']='y';
	a['b']='h';
	a['c']='e';
	a['d']='s';
	a['e']='o';
	a['f']='c';
	a['g']='v';
	a['h']='x';
	a['i']='d';
	a['j']='u';
	a['k']='i';
	a['l']='g';
	a['m']='l';
	a['n']='b';
	a['o']='k';
	a['p']='r';
	a['q']='z';
	a['r']='t';
	a['s']='n';
	a['t']='w';
	a['u']='j';
	a['v']='p';
	a['w']='f';
	a['x']='m';
	a['y']='a';
	a['z']='q';
	a[' ']=' ';//打表预处理 
    for(int o=1;o<=t;o++){
    	getline(cin,s);
    	while(s=="") getline(cin,s);//特别处理
//    	cout<<s<<endl;
    	cout<<"Case #"<<o<<": ";
    	for(auto i:s) cout<<a[i];
    	cout<<'\n';
	}
}
/*
a->y
b->h
c->e
d->s
e->o
f->c
g->v
h->x
i->d
j->u
k->i
l->g
m->l
n->b
o->k
p->r
q->?
r->t
s->n
t->w
u->j
v->p
w->f
x->m
y->a
z->q
*/
```

---

## 作者：goIdie (赞：0)

你说得对，但是我刚开始以为这题的映射有规律然后找了十分钟。

## 思路

注意到题面给的三个映射和样例包含的映射基本覆盖了全部的字母，所以我们开个 map，一个一个输进去即可。

找完发现还有一个 `z` 没有在键中出现，再找一下发现 `q` 没有在值中出现，将它们两个对应起来。

现在我们有了映射数组，剩下就简单了，遍历字符串，输出字符对应的值即可。

另外这题输入有点坑，因为字符串中有空格，所以只能用 `getline`，同时又因为 `getline` 会把 $T$ 也给读进去，所以需要用 `cin.ignore()`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
string s;
map<char,char>mp;
int main(){
	mp['a']='y',mp['b']='h',mp['c']='e',mp['d']='s',mp['e']='o',mp['f']='c';
	mp['g']='v',mp['h']='x',mp['i']='d',mp['j']='u',mp['k']='i',mp['l']='g';
	mp['m']='l',mp['n']='b',mp['o']='k',mp['p']='r',mp['q']='z',mp['r']='t';
	mp['s']='n',mp['t']='w',mp['u']='j',mp['v']='p',mp['w']='f',mp['x']='m';
	mp['y']='a',mp['z']='q',mp[' ']=' ';
	cin>>n;
	cin.ignore();
	for(int t=1;t<=n;t++){
		getline(cin,s);
		cout<<"Case #"<<t<<": ";
		for(int i=0;i<s.size();i++){
			cout<<mp[s[i]];
		}
		cout<<endl;
	}
}
```

---

## 作者：ttyy0518 (赞：0)

## 解题思路

题目描述很清晰，不再重复，需要注意题目要求的是把 Googlerese 文本转换成普通文本。

我们把题目样例中能获得的所有的映射规则取出，可以发现只剩下 $q$ 和 $z$ 没有对应。这时我们可以发现题目描述中说了 'z' $\to$ 'q'，又因为这个映射是一一对应且满射的，所以 $q$ 只能对应 $z$，即 'q' $\to$ 'z'。

现在我们得到了完整的映射表。把表存进一个数组中，再把每组字符串的字母对应的数组索引 `+'a'`, 就把 Googlerese 文本转换成了普通文本。

## 注意事项

- 数组一定要存对 ( ~~别像我把 q 打成 p~~)。
- 字符串用 `getline` 输入。
- 如果测试用例数 $T$ 用 `cin` 输入，在 `cin` 和 `getline()` 之间插入 `getchar();`，不然 `cin` 读取整数后遗留的换行符会被 `getline()` 捕获，导致直接跳过字符串输入‌。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[26]={'y','n','f','i','c','w','l','b','k','u','o','m','x','s','e','v','z','p','d','r','j','g','t','h','a','q'};
string s[35],d="";
int t;
int main(){
	cin>>t;
	getchar();
	for(int i=1;i<=t;i++){
		getline(cin,s[i]);
		d="";
		for(int j=0;j<s[i].size();j++){
			if(s[i][j]!=' '){
				for(int k=0;k<26;k++){
					if(s[i][j]==a[k]){
						d+=char('a'+k);
					}
				}
			}
			else d+=" ";
		}
		cout<<"Case #"<<i<<": "<<d<<endl;
	}
	return 0;
}
```

## [记录](https://www.luogu.com.cn/record/225067521)

---

## 作者：wangmutian (赞：0)

### 题目大意
定义一种新的语言，使用与英语字母表相同的字母和空格，然而每一个英文字母都会被映射为另一个字母，字母**一一对应**（空格保持不变）。给定 $T$ 行该语言的文本，其中**会有空格**，将其转换为英语并输出。

### 题目思路
题目中提到在不同的文本中不会改变字母的映射规则，因此可以直接通过观察输入输出样例以及题干中的例子推测出对应的字母。由于字母变化规则不变，可使用**数组**存储每一个字母对应的正常英语字母。

推理完输入输出样例后，可得到：
```cpp
char change[26] = {'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', ' ', 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', ' '};
```
此时我们发现，有两个字母没有出现在输入输出样例中。这时观察题中举的例子，可进一步得到字母 q 对应英文字母 z。
进一步得到：
```cpp
char change[26] = {'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'z', 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', ''};
```
此时仅剩余一个字母 z 规则未被找到，根据题意可得该字母对应英语字母 q。

最终得到：
```cpp
char change[26] = {'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'm', 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', 'q'};
```

### 细节处理
题目中提到单词与单词之间有空格，如果直接这样读入（如下）：
```cpp
string s;
cin >> s;
```
只能读取空格前的单个单词。

因此，此处应写成：
```cpp
string s;
getline(cin, s); //读取当前行的所有内容
```
注意读入字符 $T$ 后在行尾会出现一个换行符，需在下一次读入前，先执行一次上述代码。

除此以外，我们需要特判空格的情况，如遇空格直接原样输出，遇到字母则在数组中找到对应英语字母之后输出。

### 代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int t;
string s;
char change[26] = {'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'm', 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', 'q'};

int main()
{
    cin >> t;
    getline(cin, s);
    for (int i = 1; i <= t; i++)
    {
    	getline(cin, s); //提取当前一行的内容
    	cout << "Case #" << i << ": "; //注意输出格式
    	for (int j = 0; j < s.size(); j++) //遍历当前行
    	{
    		if (s[j] == ' ') //遇到空格，原样输出
    		{
    			cout << s[j];
    		}
    		else //遇到字母，找到对应英语字母
    		{
    			cout << change[s[j] - 'a'];
    		}
    	}
    	cout << endl; //不要忘记换行！！
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13311)
## 题目分析
希望审核大大给过。（不过估值就不保了啊）

这道题乍一看，太好了！竟然没有任何的思路，只有 `'a' - 'y'，'o' - 'e'，'z' - 'q'` 有一点用。但是，当你仔细观察时，会发现其实有大部分的字母都在样例里面出现了。不难统计，$26$ 个字母中只有 `q` 和 `z` 没有出现。但是前面题目已经告诉我们，`'z' - 'q'`，所以经排除法可知，`'q' - 'z'`，然后这道题就可以解出来了！

记住，一定要加前面的那一坨东西！！

下面是题目代码。
## 题目[代码](https://www.luogu.com.cn/record/225010954)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
map<char,char>mp;
signed main() {
	speed
	int T;
	cin>>T;
	mp['y']='a';
	mp['n']='b';
	mp['f']='c';
	mp['i']='d';
	mp['c']='e';
	mp['w']='f';
	mp['l']='g';
	mp['b']='h';
	mp['k']='i';
	mp['u']='j';
	mp['o']='k';
	mp['m']='l';
	mp['x']='m';
	mp['s']='n';
	mp['e']='o';
	mp['v']='p';
	mp['z']='q';
	mp['p']='r';
	mp['d']='s';
	mp['r']='t';
	mp['j']='u';
	mp['g']='v';
	mp['t']='w';
	mp['h']='x';
	mp['a']='y';
	mp['q']='z';
	mp[' ']=' ';
	cin.ignore();
	for(int i=1;i<=T;i++){
		string s;
		getline(cin,s);
		cout<<"Case #"<<i<<": ";
		for(int i=0;i<s.size();i++)cout<<mp[s[i]];
		cout<<'\n';
	}
	return 0;
}
关注一下作者吧！好可怜啊qwq
```

---

## 作者：libu2333 (赞：0)

由于 Googlerese 永远不会被改变，所以我们可以从题中找答案。题面和样例已经给了我们 $25$ 个英文字母的转换法则，那么剩下的那一个也就不难猜了。于是我们可以列出表格：

|原文|a|b|c|d|e|f|g|h|i|j|k|l|m|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|密文|y|n|f|i|c|w|l|b|k|u|o|m|x|

|原文|n|o|p|q|r|s|t|u|v|w|x|y|z|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|密文|s|e|v|z|p|d|r|j|g|t|h|a|q|

然后这道题就做完了。

下面是这道题的 Python 代码，注意题目要求是把密文转换为原文。

```python
mp = {
'y':'a','n':'b','f':'c','i':'d','c':'e','w':'f','l':'g','b':'h','k':'i','u':'j','o':'k','m':'l','x':'m',
's':'n','e':'o','v':'p','z':'q','p':'r','d':'s','r':'t','j':'u','g':'v','t':'w','h':'x','a':'y','q':'z',
' ':' ' # 空格也需要映射
}

n=int(input())
for i in range(1,n+1): # range() 左闭右开
    s=input().strip()
    t=''
    for j in range(len(s)):
        t+=mp[s[j]]
    print("Case #{}:".format(i),t)
```

---

