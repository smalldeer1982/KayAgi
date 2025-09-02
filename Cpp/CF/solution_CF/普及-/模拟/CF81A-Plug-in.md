# Plug-in

## 题目描述

Polycarp thinks about the meaning of life very often. He does this constantly, even when typing in the editor. Every time he starts brooding he can no longer fully concentrate and repeatedly presses the keys that need to be pressed only once. For example, instead of the phrase "how are you" he can type "hhoow aaaare yyoouu".

Polycarp decided to automate the process of correcting such errors. He decided to write a plug-in to the text editor that will remove pairs of identical consecutive letters (if there are any in the text). Of course, this is not exactly what Polycarp needs, but he's got to start from something!

Help Polycarp and write the main plug-in module. Your program should remove from a string all pairs of identical letters, which are consecutive. If after the removal there appear new pairs, the program should remove them as well. Technically, its work should be equivalent to the following: while the string contains a pair of consecutive identical letters, the pair should be deleted. Note that deleting of the consecutive identical letters can be done in any order, as any order leads to the same result.

## 样例 #1

### 输入

```
hhoowaaaareyyoouu
```

### 输出

```
wre```

## 样例 #2

### 输入

```
reallazy
```

### 输出

```
rezy```

## 样例 #3

### 输入

```
abacabaabacabaa
```

### 输出

```
a```

# 题解

## 作者：Transparent (赞：3)

### 关于题意

总感觉翻译说得不清楚，用引用谷歌翻译的一句话解释就很清楚了：

您的程序应从字符串中删除所有连续的相同**字母对**。如果在删除之后出现了**新的配对**，则程序**也应该删除**它们。

------------

### 正题

既然第一次删除后的串中仍可能可以删除，那就不能用常规方法。

因此可以用栈。

- 从头到尾遍历这个字符串.

- 如果遇到一个字符与栈顶元素相等，
那么这个字符一定属于一个现在或多次操作后存在于字符串中的连续相同字母对，
于是就弹出栈顶，并不将当前元素加入栈，
这也就相当于从删除了这个连续相同字符对。

- 若这个字符不与栈顶元素相等，
则它一定不属于任意一个现在或多次操作后存在于字符串中的连续相同字母对，
于是就把它压入栈顶。

- 因为要使两个字符在若干次操作后靠在一起，
它们中间的所有字符都必须被删除（即被弹出栈），
所以以上方法是可行的。

- 因为栈是先进后出，后进先出，
所以最后输出时要从栈底到栈顶输出，
即按照弹出顺序相反的顺序输出。

------------

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char str[200001],ans[200001];//str表示原串，ans为逆序的答案 
stack<char>sta;//栈 
int tot;//计数用 
int main()
{
	scanf("%s",str+1);//从第一位开始输入 
	int len=strlen(str+1);//同样从第一位求长度 
	for(register int i=1;i<=len;i++)
	{
		if(!sta.empty()&&sta.top()==str[i])//注意先判空 
		sta.pop();
		else
		sta.push(str[i]);
	}
	while(!sta.empty())
	{
		ans[++tot]=sta.top();
		sta.pop();
	}
	for(register int i=strlen(ans+1);i>=1;i--)
	{
		printf("%c",ans[i]);//逆序输出 
	}
	return 0;
}
```


---

## 作者：xiaomuyun (赞：2)

# CF81A Plug-in 题解
[题目传送门](https://www.luogu.com.cn/problem/CF81A)
## 题意
总觉得这题的翻译需要改改……

给出一行字符串，你需要将其中所有相同且**连续**的字母对删除（**注意，删除字母对之后可能又会形成新的字母对**，比如 $\texttt{abba}$，删除了 $\texttt{bb}$ 之后又形成了 $\texttt{aa}$），最后输出结果。
## 分析
因为会形成新的字母对，所以要用一个栈来存，如果栈顶和当前字符相等，就可以出栈，否则就将当前字符也加入栈。
## 代码
这个蒟蒻选择了手写栈，这样好输出。
```cpp
#include<iostream>
#include<cstdio>
#include<stack>

using namespace std;

string s;
int cnt[30],sz=0;
char st[200001];

int main(){
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;++i){
		if(sz&&st[sz]==s[i]) --sz;//出栈
		else st[++sz]=s[i];//入栈
	}
	for(int i=1;i<=sz;++i) printf("%c",st[i]);//直接输出即可
	putchar('\n');
	return 0;
}
```
## 总结
一道栈的好题。希望大家能点个赞，制作不易~

---

## 作者：OI_AKed_me (赞：1)

# CF81A Plug-in题解 #
[原题链接](https://www.luogu.com.cn/problem/CF81A)

## 题意简述 ##
这道题翻译得不是很清楚，我也是看了其它题解才弄明白的，即**删除连续字母对，若删除后出现了新的字母对，也要删除。**

## 思路 ##
这题可以通过栈来实现，当新的元素与栈顶相匹配那就弹出栈顶，否则就将栈顶弹出。

## 实现 ##
很多人都是用栈实现的，用手写栈还好，但用 ``` stack ``` 来实现的话最后输出答案还得先重新存一下，比较麻烦，所以这题我比较推荐用 ``` deque ```，因为 ``` deque ``` 可以对队列头部进行操作也可以对队列尾部进行操作，而通过对队列尾部的操作就可以完成 ``` stack ``` 的操作，而对队列头部的操作就可以直接循环输出答案，详细实现见代码。

## 代码 ##
```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
deque <char> a;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(a.empty()) a.push_back(s[i]);//push_back 这相当于 stack 的 push
		else a.back()==s[i]?a.pop_back():a.push_back(s[i]);//back 相当于 stack 的 top，pop_back 相当于 stack 的 pop
	}
	while(!a.empty()){//这一块如果用 stack 就需要重新存进一个 ans 数组，然后进行输出。
		cout<<a.front();
		a.pop_front();
	}
	return 0;
}
```

---

## 作者：user470883 (赞：1)

## 题意：
从字符串中删除所有连续的相同字母对，然后删掉后有新的配对，也要删掉。

## 思路：
由于删掉后有新的配对，也要删掉，我们只能用栈来存。

栈就是一种先进后出的数据结构。

回归正题，我们可以先将当前字符加入栈，如果栈顶的前两个元素相同，弹掉那两个元素即可。

最后输出，注意栈是先进后出，所以我们需要从底下往上。

`C++` 里面有 `stack` 栈数据结构，不过为了最后较方便的输出，我们用一个数组去模拟栈。

## AC CODE:
```
#include<bits/stdc++.h>
using namespace std;

char st[200001];

int main()
{
    int si=0;//这个就是存当前栈总长度
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i ++)
    {
        si++;
        st[si] = s[i];
        if(si > 1 && st[si] == st[si - 1])
        {
            si -= 2;
        }//进行模拟
    }
    for(int i = 1; i <= si; i ++)
    {
        cout << st[i];
    }//输出
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/63076844)

---

## 作者：Rosmarinus (赞：1)

## 思路分析

题目要求删除字符串中所有连续且相同的字符。

显然，在删除部分连续相同字符时会导致新的连续相同字符出现。

考虑到较大的数据范围，如果使用循环必然会 TLE。

可以使用栈，每次将字符串中的字符加入栈，若栈顶的两个元素相同则将他们一起弹出。

在最后输出整个栈即可。

## Code
```cpp
#include<iostream>
using namespace std;
char st[2100000];
int len;
int main()
{
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i ++)
    {
        len ++;
        st[len] = s[i];
        if(len > 1 && st[len] == st[len - 1])
        {
            len -= 2;
        }
    }
    for(int i = 1; i <= len; i ++) cout << st[i];
    cout << endl;
    return 0;
}
```

---

## 作者：sysong (赞：1)

# 题解CF81A Plug-in

### 题目描述

Polycarp 经常思考生命的意义。他经常这么做，即使是在编辑器里输入。每次他开始沉思，他不能再完全集中精力，并重复按那些只需要按一次的按键。例如，他可以输入 "hhoow aaaare yyououu" 而不是 "how are you"。

Polycarp 决定自动化纠正这些错误的过程。他决定编写一个插件到文本编辑器，将删除相同的连续字母对(如果在文本中有的话)。当然，这不是 Polycarp 实际所需要的，但他总得有个开始！

帮助 Polycarp 编写主插件模块。**你的程序应该从一个字符串中移除所有相同字母的对，它们是连续的。如果移除后出现新的配对，程序也应该移除它们。** 从技术上讲，它的工作应该等价于以下内容:

**当字符串包含一对连续的相同字母时，应该删除这一对。请注意，删除连续相同的字母可以按任何顺序进行，因为任何顺序都会导致相同的结果。**

输入一个仅由小写字母组成的字符串（$1 \le l \le 2 \times 10^{5}$），输出删除结束后的结果。

（原来翻译有点问题，没有强调**连续**字符，可能会误解 ，~~比如我~~）

### 思路

手动开栈模拟。

如果遇到重复字符，将其弹出，否则压栈。

输出时将最后一位设为`'\0'`，即可直接输出整串。

### $C++ \quad Code$

```c++
#include <cstdio>
#define R register
#define gc() getchar()
using namespace std;

char st[200001];
int tp;

int main(){
	R char c=gc();
	while(c!='\n'){
		if(tp&&c==st[tp])--tp;
		else st[++tp]=c;
		c=gc();
	}
	st[tp+1]='\0';
	printf("%s\n",st+1);
	return 0;
}
```



***by jsntsys***

$2020.12.11$



---

## 作者：Qerucy (赞：0)

~~毒瘤机器翻译搞得我半天才理解题意......~~

看到题解区的题解，觉得这些题解讲得很好，我给大家讲一个更加通俗易懂的方法吧

题意：从左到右把字符串扫一遍，删除连续字母对，若删除后出现了新的字母对，也要删除，输出删除后的字符串（~~从你谷题面抄下来的~~）

好吧，开始思考了。

先想暴力，循环执行以下操作：

从左到右扫描字符串，遇到一对字母对就把它们删除，直到字符串里没有字母对为止。

但是，这复杂度直接上天！！！

还是来想正解吧

我的方法：建立两个栈：$a$ 和 $b$，把字符串的字符全部装到 $b$ 中，把 $b$ 的字符一个个装到 $a$ 中，如果 $a$ 的顶部等于 $b$ 的顶部，就删除 $a$ 的顶部和 $b$ 的顶部，直到 $b$ 为空为止。

最后再输出 $a$ 就可以了，因为把字符装到 $b$ 时，已经是倒序存储了， 在 $b$ 的元素装入 $a$ 时也是倒序的，所以不需要再执行多余的操作。

代码：

```cpp
#include<cstdio>
#include<stack>
#include<string>
#include<iostream>

using namespace std;

string s;
stack<int>s1,s2;//两个栈

signed main(){
	cin>>s;
	
	for(int i=0;i<s.length();i++){
		s2.push(s[i]);
	}
	
	while(!s2.empty()){
		if(s1.empty()) s1.push(s2.top()),s2.pop();//特判栈是否为空
		else if(s1.top()==s2.top()){
			s1.pop();
			s2.pop();
		}
		else s1.push(s2.top()),s2.pop();
	}
	
	while(!s1.empty()){
		printf("%c",s1.top());
		s1.pop();
	}
	
	return 0;
}
```


---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------

给定一个字符串 $str$，去除其中重复的连续子串。

如果去除一些子串后又合成新的子串，这些重复的字串也要删除。

如样例 **#2** 就是如下得出的。

$\texttt{reallazy} \to \texttt{reaazy} \to \texttt{rezy}$

### 解题思路
------------

我们可以用**栈**来实现。

我们首先将第一个字符压入栈中。

每次遇到与栈顶一样的字符，就将栈顶弹出，否则，将这个元素入栈。

最后，将所有元素从栈中弹出，用一个数组记录，倒序输出即可。

显然我用的是系统栈，但也许这道题用手写栈会更简单一些？

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
string str; char ans[1000005];
stack<char> st; int num;
int main() {
	cin>>str; st.push(str[0]);
	for(int i=1;i<str.size();i++) {
		if(!st.empty()&&st.top()==str[i]) st.pop();
		else st.push(str[i]);
	}
	while(!st.empty()) {
		ans[++num]=st.top();
		st.pop();
	}
	for(int i=num;i>=1;i--) printf("%c",ans[i]);
	return 0;
}
//code by TheCedar
```

---

