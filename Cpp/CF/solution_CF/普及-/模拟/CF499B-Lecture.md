# Lecture

## 题目描述

你现在有一位新图论教授，你觉得他讲课讲的很好，但他说话实在是太快了，搞得你根本没有时间记笔记。所以呢，你有一个计划来跟上他讲课时的“脚步”，并记下重要的笔记。

你总共会两种语言：A 语言和 B 语言，教授用来讲课的是其中的 A 语言。A 语言和 B 语言有以下共同点：

- 它们都由若干小写字母构成；
- 每个单词里都不包括空格；
- 它们的长度都不超过 10。

另外，可以保证同一种语言中任意两个单词都有不同的拼写，且 A 语言的每一个单词与 B 语言中的每一个单词一一对应。

你的做笔记方式如下：

- 你必须写出写出教授给出的每一个单词；
- 为保证写单词用时最短，你必须要选择两种语言中单词长度更短的一个；
- 如果两个单词的长度一样，为保证讲课的原汁原味，你会选择第一种语言来做笔记。

我们会给你教授的演讲。而你呢，需要编一个程序来写出你的笔记。

## 样例 #1

### 输入

```
4 3
codeforces codesecrof
contest round
letter message
codeforces contest letter contest
```

### 输出

```
codeforces round letter round
```

## 样例 #2

### 输入

```
5 3
joll wuqrd
euzf un
hbnyiyc rsoqqveh
hbnyiyc joll joll euzf joll
```

### 输出

```
hbnyiyc joll joll un joll
```

# 题解

## 作者：爬行者小郑 (赞：11)

## STL：map做法

注意到题目中说任意两种语言都不会有相同的单词，于是首先输入两个字符串，我们可以用一个map把两个对应的语言都存起来（因为语言间不会发生冲突）

这种做法不同点：不需要在输入的时候替换，不需要用pair插入，可以利用map直接访问就可以准确找到

楼上的同学其实不用遍历一遍。。。map直接访问就好了

code：
```
#include <iostream>//基本输入输出流
#include <cstring>//一会要用到string
#include <map>//要用到map来存词典
using namespace std;
map<string,string>ma;//词典
int n,m;//题目中的n，m
int main()
{
	cin>>n>>m;//输入n，m
	for(int i=1;i<=m;i++)
	{
		string a,b;
		cin>>a>>b;//输入一种语言的两种写法
		ma[a]=b;//注意：直接存储字符串类型的下标和字符串，不需要pair
		ma[b]=a;
	}
	for(int i=1;i<=n;i++)
	{
		string a;
		cin>>a;//输入叫兽讲的单词
		if(ma[a].size()<a.size())cout<<ma[a]<<" ";//注意，是严格小于，不能取等
		else cout<<a<<" ";//不需要替换
	}
	return 0;//养成好习惯，竞赛中没有直接爆零
}
```
c++中map使用非常广

谢谢大家


---

## 作者：_FILARET_ (赞：2)

如果你们没看懂题的话，就是说给你一堆a语言的单词和一堆b语言的单词，如果在最后的句子中对应的b语言的单词长度<a语言的单词长度，就将那个a语言的单词替换成b语言的单词QwQ

这道题可以使用以下两个STL库
- string 存单词用
- map 存【字典】用

好了废话不多说上代码

```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;
map<string, string> mp; //定义字典
int n, m;
string tmpa, tmpb; //循环输入的A语言和B语言
int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>tmpa>>tmpb; //输入一对词汇
        pair<string, string> tmp; //准备输到字典用的pair（如果你不知道的话，map得用pair来insert呦）
        tmp.first=tmpa;
        if(tmpa.length()<=tmpb.length())  tmp.second=tmpa; //这种情况下就不用动了
        else tmp.second=tmpb; //替换B语言
        mp.insert(tmp); //输到最后的字典里
    }
    for(int i=0;i<n;i++)
    {
        cin>>tmpa;
        cout<<mp[tmpa]<<" "; //输出单词
    }
    return 0; //回家领糖吃咯~
}
```

---

## 作者：SZ_Dong (赞：1)

## **题意**:

简单来说就是给出一些词汇,每个单词都有两种语言(语言不会冲突),然后给出一个句子,求这个句子的最短长度。

## **思路:**

用STL中的map，[不会map的同学点这里](https://oi-wiki.org/lang/csl/associative-container/)。每次读入单词时判断哪种语言更短，把最短的语言存到一个map里,最后根据读入输出最短的单词就行了。

## **code:**

```cpp
#include<iostream>
#include<map>
#include<cstring>
using namespace std;
typedef long long ll;

ll n,m;
map<string,string> a;
string x,y;

int main(){
    ios::sync_with_stdio(false); 

    cin>>n>>m;

    for(ll i=1; i<=m; i++) {
        cin>>x>>y;

        if(y.size()<x.size())
            a[x]=y;  

        else
            a[x]=x; 
    }

    for(ll i=1; i<=n; i++) {
        cin>>x;

        cout<<a[x]<<" "; 
    }
    
    return 0;  
}
```


---

## 作者：ljm1621 (赞：0)

# 思路

**STL是个好东西**，用map就能轻轻松松AC此题。

首先，读入的两个单词用map把各自对应的单词存起来。再将老师句子里每一个单词的长度与B语言比较，如果长度小于B语言的长度，就输出A语言的单词，其他的就输出B语言。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
map<string,string> mapp;
int main()
{
    int n,m;
    string a,b;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        mapp[a]=b;
        mapp[b]=a;
    }
    for(int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        if(mapp[s].length()<s.length())    cout<<mapp[s]<<" ";
        else                    cout<<s<<" ";
    }
    return 0;
}
```

[亲测AC](https://www.luogu.com.cn/record/45430436)


---

## 作者：Eason_AC (赞：0)

## Content
有一个教授用 $\texttt{A}$ 语言讲课。你觉得他讲的太快了，所以决定使用 $\texttt{A}$ 语言和 $\texttt{B}$ 语言记笔记。

已知 $\texttt{A}$ 语言和 $\texttt{B}$ 语言中的 $m$ 对单词的意思是互相对等的，因此，使用 $\texttt{B}$ 语言可能会让你的笔记更加简洁。当然，如果 $\texttt{A}$ 语言中的单词的长度和 $\texttt{B}$ 语言中意思相等的单词的长度相等，甚至 $\texttt{A}$ 语言中的单词长度还要短，那么你还是会首选用 $\texttt{A}$ 语言记笔记。

现在给出教授的演讲（有 $n$ 个单词），请你按照以上规则记好笔记。

**数据范围：$1\leqslant n,m\leqslant 3000$。**
## Solution
我们为什么不使用 $\texttt{map}$ 来解决这道题目呢？

由于可以肯定教授只用 $\texttt{A}$ 语言来演讲，因此我们直接将 $\texttt{A}$ 语言中的意思相等的单词用 $\texttt{map}$ 映射到 $\texttt{B}$ 语言中去，然后在每个单词对比是否会使记笔记的长度减少即可。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int n, m;
string a, b, sp[3007];
map<string, string> mm1;

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		cin >> a >> b;
		mm1[a] = b;
	}
	for(int i = 1; i <= n; ++i) {
		cin >> sp[i];
		if(mm1[sp[i]].size() < sp[i].size())	sp[i] = mm1[sp[i]];
	}
	for(int i = 1; i <= n; ++i)	cout << sp[i] << ' ';
}
```

---

## 作者：Suuon_Kanderu (赞：0)

这题，直接暴力模拟就可以。

思路：放三个string数组，一份放A语言，一份放B语言。

最后一份放叫兽的语言（叫兽？？）

输入不说了。输入完以后，暴力枚举叫兽的演讲中的词汇，看看和A语言中是否相等，若是，则再判断AB语言的长短，输出短的那个。特别暴力

O（n * m）代码，竟然能过？？

上代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
string a[3001],b[3001];
string c[3001];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)//输入
	{
		cin>>a[i];
		cin>>b[i];
	}
	for(int i=1;i<=n;i++)
	cin>>c[i];

for(int j=1;j<=n;j++)//开始枚举
{
    for(int i=1;i<=m;i++)//看看哪一个词和叫兽演
    讲词相等
	   if(a[i]==c[j])
       {
       if(b[i].size()<a[i].size())//判断那个
       长度短，注意是<而不是<=
             cout<<b[i]<<" ";
       else cout<<a[i]<<" ";	
     	}
 }
	
return 0;//养成习惯。

	
	 
}
```
注意，因为保证叫兽演讲的原汁原味，要用<而不是<=

我还想再强调一遍，因为我就因为这个调了半天。

另外，a.size()是取字符串长度的函数，

除此以外再介绍几个string函数，让不熟悉STL标准库的人了解了解。

a.length()和size函数一样，都是取字符串长度。

a.clear()清空数组。

insert()   
insert函数有多种用法

(1)a.insert(b,string1)把string1插入到a的b位置之后。

（2）a.string(it,it2,it3)it是欲插入的位置it2和it3
是要插入字符串的首尾选迭器。

a.erase()删除函数

（1）erase(pos,n); 删除从pos开始的
n个字符，比如erase(0,1)就是删除第一个字符

（2）erase(position);删除position处的一个字符(position是个string类型的迭代器)

（3）erase(first,last);删除从first到last之间的字符（first和last都是迭代器）

a.find(b)寻找函数。

当b是a的子串时，返回他第一次出现的位置，否则回-1，
当然也可以认为是unsigned int 的最大值4294967295。

string函数有很多，这里只介绍几个常用的。

感谢您的观看。



---

