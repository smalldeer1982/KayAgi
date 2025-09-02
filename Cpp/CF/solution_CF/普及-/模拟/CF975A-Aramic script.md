# Aramic script

## 题目描述

In Aramic language words can only represent objects.

Words in Aramic have special properties:

- A word is a root if it does not contain the same letter more than once.
- A root and all its permutations represent the same object.
- The root $ x $ of a word $ y $ is the word that contains all letters that appear in $ y $ in a way that each letter appears once. For example, the root of "aaaa", "aa", "aaa" is "a", the root of "aabb", "bab", "baabb", "ab" is "ab".
- Any word in Aramic represents the same object as its root.

You have an ancient script in Aramic. What is the number of different objects mentioned in the script?

## 说明/提示

In the first test, there are two objects mentioned. The roots that represent them are "a","ab".

In the second test, there is only one object, its root is "amer", the other strings are just permutations of "amer".

## 样例 #1

### 输入

```
5
a aa aaa ab abb
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
amer arem mrea
```

### 输出

```
1```

# 题解

## 作者：Eason_AC (赞：2)

## Content
定义一个字符串的根为字符串中不同种类的字符按字典序非降序排列得到的字符串。例如 $\texttt{aaa}$ 的词根为 $\texttt{a}$，$\texttt{babb}$ 的词根为 $\texttt{ab}$，$\texttt{abczfee}$ 的词根为 $\texttt{abcefz}$，等等。

现在给出 $n$ 个字符串，求不同的根的个数。

**数据范围：$1\leqslant n\leqslant 10^3$，字符串长度不超过 $10^3$。**
## Solution
我们看完题之后分析一下就明白，这道题目主要是三个操作：

1. 字符串的每个字符按照字典序非降序排列。
2. 将重复的字符去掉。
3. 判断是否已经出现过。

那我们将每个操作依次分析一下吧。首先是第一个操作，这里教大家用一个非常好用的技巧——用 $\texttt{sort}$ 直接排序。你没听错，$\texttt{sort}$ 就是强大到可以直接将第一个操作一刀切。我们假设现在的字符串为 $s$，然后我们可以通过调用 $\texttt{sort(s.begin(), s.end());}$（其实也就相当于将字符串彻头彻尾地按照字典序非降序排列）就可以得到一个里面所有的字符都是按照字典序非降序排列的字符串了。

然后是第二个操作，排序完之后，我们直接遍历字符串，如果当前扫到的字符不和前面的字符相等就加到这个字符串的根里面去，直到扫完为止，这时我们就可以得到一个字符串的根了。

最后是第三个操作，我们可以开一个 $\texttt{map}$ 来直接将字符串是否出现映射到一个变量上去，这样就可以直接判断字符串的根是否出现过，不需要再用 $\texttt{hash}$ 判断了。

$\texttt{STL}$ 有时确实能让你的代码简洁很多，不妨多试试有关于 $\texttt{STL}$ 的题目。
## Code
```cpp
int n, ans;
string s;
map<string, int> vis;

int main() {
	getint(n);
	while(n--) {
		cin >> s;
		string root = "";
		sort(s.begin(), s.end());
		int len = s.size();
		_for(i, 0, len - 1)
			if(s[i] != s[i - 1])	root += s[i];
		if(!vis[root]) {ans++, vis[root] = 1;}
	}
	writeint(ans);
	return 0;
}
```

---

## 作者：Indulge_myself (赞：0)

本题的关键就在于如何把它去重相同的字母和如何把相同的字符串去掉，理解了它们一切都好弄了。

更详尽的注释在代码里。
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
set<string> sets;
int main()
{
	char strings[100005];//定义数组，开大一点保险
	long long n;
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>strings;
		sort(strings,strings+strlen(strings));//直接排序，保证 字母顺序不变 
		long long longer=unique(strings,strings+strlen(strings))-strings;//把重复的 字符放后面，这样不干扰最后的输出 
		strings[longer]='\0';//设置最后的下标 
		sets.insert(strings);//插入set类型 ，set自动去重 
	}
	printf("%d",sets.size());//因为最后的下标被改变了，所以它的长度就是答案。 
}

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF975A) & [原题链接](http://codeforces.com/problemset/problem/975/A)

---
题意：
输入 $n$ 个字符串，对于每个字符串，你需要完成一下几个操作：
1. 按字典序排序
2. 去除重复字符
3. 统计操作后不同的字符串的个数

---
### 按字典序排序：

我们可以使用 STL 模板库中的 ```sort``` 函数，实现快排。

sort 的时间复杂度： $O(n \log_2 n)$

使用方法：

1. 对 C++ 库中自带的数据类型进行排序：

```sort(首个数据的地址,最后一个数据的地址+1）```

2. 对使用了 ```struct``` 的自定义类型进行排序：

```sort(首个数据的地址,最后一个数据的地址+1,bool 类型的比较函数名称）```

如果你已经重载了 "<" ，那么使用方法就同第一种了。

对于字符串，可以与 ```begin()``` 和 ```end()``` 函数一起使用，更便捷。

示例：

```sort(s.begin(),s.end());```

---
### 去除重复字符:

我们可以遍历一次字符串，如果当前字符与前一个字符不同，就可以记录加进操作后的字符串啦。

---

### **统计操作后不同的字符串的个数：**

**本文重点： ```map```**

```map``` 就是在 STL 模板库中的哈希表，速度比手写哈希表略慢。

使用原理：

比如让模数为 3

现有数组 $A=\{14,16,24,19,42\}$

我们只需要用一个链表（ ```vector``` ）数组 $B$ ，来存数据。

$$B_{14 \mod 13}=14$$

$$B_{16 \mod 13}=16$$

$$B_{24 \mod 13}=24$$

$$B_{19 \mod 13}=19$$

$$B_{42 \mod 13}=42$$

为什么要用链表呢？就是因为避免重复。像 $14\mod 13=42\mod 13$ 这种重复的情况就可以用链表加上。

为什么用哈希表好呢？就是因为数据较为集中，空间浪费较少，还能把下标设为所有数据类型（对于 STL 比较方便而已）。

使用方法：

定义： ```map<下标类型,数据类型> 名字```

使用方法与数组相同

像这题，我们可以开一个 ```map<string,bool> vis;``` 来标记某个字符串是否出现过。

---

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans;
string s,t;
map<string,bool> vis;//全局的 bool 变量默认为 false 
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>s;
		sort(s.begin(),s.end());//排序
		t=s[0];
		for(int i=1;i<s.size();i++)//去重
			if(s[i]!=s[i-1])
				t+=s[i];
		if(!vis[t])//没出现过
		{
			ans++;
			vis[t]=true;//标记为出现过
		}
	}
	cout<<ans<<endl;
} 
```


---

## 作者：Zxsoul (赞：0)

**前言**
> 提供set的做法 最短代码

**思路**

首先找到每一个单词的根，这里可以用 `stl` 中的 `unique`，值得注意的是在用set进行维护时，插入长度以 `\0` 为结尾，因此我们需要在去重的位置改成 `\0` ，这样就等价于将单词去重

```c
	int len=unique(a,a+strlen(a))-a;//将重复的放在后面
	a[len]='\0';//结束符，使得后面被删去
	se.insert(a);  
	
```

**Code**
```c
#include <set>
#include <cstdio>
#include <iostream>
using namespace std;

char a[1009];
set<string> se;
int n;
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a;
		sort(a,a+strlen(a));
		int len=unique(a,a+strlen(a))-a;//将重复的放在后面
		a[len]='\0';//结束符，使得后面被删去
		se.insert(a);  
	}
	printf("%d",se.size());
}
```

---

## 作者：B_lhx (赞：0)

[CF975A Aramic script](https://www.luogu.com.cn/problem/CF975A)
==
这是一篇 **c++** 题解

题目翻译：
--
```
有一个神奇的语言叫“Aramic”，它有以下特点：
1：如果一个单词没有重复的字母，那它就是词根
2：一个词根的字母不管调换顺序都还是这个词根
3：一个单词y的词根x是把y里面不同的字母挑出来按字典序排序得到的，比如“aaaa”，“aa”，“aaa”等的词根都是“a”，而“aabb”，“bab”，“baabb”等的词根都是“ab”
4：任何单词表示的意思和它的词根一样

输入n，然后输入n个Aramic语单词，输出一共有多少个不同的意义（有多少个不同的词根）
```
思路：
--

运用知识点：快排，字符串，自定义函数

首先，把每个单词转换为词根，然后统计词根数

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10005][105];//Aramic语单词输入，因为要用sort，char更方便
string rs[10005];//转换为词根形态的单词
string spd[10005];//判重
int len=0;//判重字符数组的长度
bool my_find(string z){//查找函数
	for(int i = 0;i<len;i++){//循环查找字符串在不在判重字符数组里
		if(spd[i]==z){//如果找到了
			return true;//返回找到了
		}
	}
	return false;//返回没找到
}
bool cmp(char x,char y){//排序函数
	return x<y;//按升序排序
}
int main(){
int n;//n
cin>>n;//输入n
for(int i = 0;i<n;i++){//循环n次
	cin>>s[i];//输入，边循环边做字典序
	sort(s[i],s[i]+strlen(s[i]),cmp);//排序
	int pd[27]={0};//小判重数组
	for(int j = 0;j<strlen(s[i]);j++){//循环
		if(pd[s[i][j]-'a']==0){//如果这个字母没出现
			rs[i]+=s[i][j];//词根添加这个字母
			pd[s[i][j]-'a']=1;//小判重数组标注这个字母出现了
		}
	}
}
for(int i = 0;i<n;i++){//循环词根判重
	if(!my_find(rs[i])){//如果没找到
		spd[len]=rs[i];//加入判重字符数组
		len++;//长度++
	}
}
cout<<len;//输出长度len
return 0;
}
```

---

## 作者：TLE自动机 (赞：0)

#### ~~不会告诉你们我在打cf的时候wa了两次~~

水题，先把每个字符串不同字符求出来，再用字典序排序，即得到所有"root"。每个root用map存，判断有无此root，如第一次出现则cnt++

也可以用hash表，但是我看了看数据范围。。。

代码：
```cpp
#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
bool cmp(char a,char b){
    return int(a)<int(b);//char排序cmp函数
}
int main(){
    map<string,bool>ma;
    int n,cnt=0;string q;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>q;
        bool p[501];
        fill(p+1,p+500,0);
        char w[1001];
        int top=0;
        string e;
        for(int j=0;j<q.length();j++){
            if(!p[q[j]]) {
                p[q[j]]=1;
                w[++top]=q[j];//存每个不同字母
            } 
        }
        sort(w+1,w+top+1,cmp);//字典序
        for(int i=1;i<=top;i++){
            e+=w[i];//转化成string
        }
        if(ma[e]==0) {//map映射
            cnt++;	
            ma[e]=1;
        }
    }
    cout<<cnt;//输出结果
    return 0;
}
```

---

