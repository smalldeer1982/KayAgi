# Extract Numbers

## 题目描述

You are given string $ s $ . Let's call word any largest sequence of consecutive symbols without symbols ',' (comma) and ';' (semicolon). For example, there are four words in string "aba,123;1a;0": "aba", "123", "1a", "0". A word can be empty: for example, the string $ s $ =";;" contains three empty words separated by ';'.

You should find all words in the given string that are nonnegative INTEGER numbers without leading zeroes and build by them new string $ a $ . String $ a $ should contain all words that are numbers separating them by ',' (the order of numbers should remain the same as in the string $ s $ ). By all other words you should build string $ b $ in the same way (the order of numbers should remain the same as in the string $ s $ ).

Here strings "101", "0" are INTEGER numbers, but "01" and "1.0" are not.

For example, for the string aba,123;1a;0 the string $ a $ would be equal to "123,0" and string $ b $ would be equal to "aba,1a".

## 说明/提示

In the second example the string $ s $ contains five words: "1", "", "01", "a0", "".

## 样例 #1

### 输入

```
aba,123;1a;0
```

### 输出

```
"123,0"
"aba,1a"
```

## 样例 #2

### 输入

```
1;;01,a0,
```

### 输出

```
"1"
",01,a0,"
```

## 样例 #3

### 输入

```
1
```

### 输出

```
"1"
-
```

## 样例 #4

### 输入

```
a
```

### 输出

```
-
"a"
```

# 题解

## 作者：liuchishahuang (赞：3)

## 题目翻译
给定一个字符串，我们将该字符串所有极长的被 
$\texttt{','}$ 或是 $\texttt{';'}$ 分隔开的子串称为“单词”。

如字符串： $\texttt{"aba , 123 , 1a , 0"}$。

一共有 $\texttt{"aba" 、 "123" 、 "1a" 、 "0"}$ 共4个单词。

其中不包含阿拉伯数字以外字符且无前导的单词 $0$ 被认为是数字单词。

现在请你将所有的单词进行分类，将所有的数字单词输出在第一行，其余的输出在第二行。

需要注意的是单词可以为空字符串，且此类单词被认为是非数字单词。
## 题目分析
本题其实是一道很简单的字符串模拟题。

仔细读题的话，我们可以发现，这里所说的数字单词和非数字单词是这样归类的：

1. 数字单词是正常的，我们在生活中见到的数。

2. 非数字单词是所有单词中除了数字单词以外的单词。

那么我们可以用两个字符串数组存储每一次查出的单词。

搜索过程如下：
```cpp
for(int i=0;i<s.size();){
		s1="";
		while(i<s.size()&&s[i]!=','&&s[i]!=';')s1+=s[i],i++;
		if(s1==""){ABC_number[++ABC_number_num]=s1;i++;continue;}
		if(s1=="0")number[++number_num]=s1;
		else if(s1[0]=='0')ABC_number[++ABC_number_num]=s1;
		else{
			bool flag=true;
			for(int j=0;j<s1.size();j++)
				if(s1[j]<'0'||s1[j]>'9'){flag=false;break;}
			if(flag)number[++number_num]=s1;
			else ABC_number[++ABC_number_num]=s1;
		}
		i++;
	}
```
那么，存储好的单词怎么输出呢？

这个其实很简单，按照题目要求输出就可以了。

这一部分代码如下：

```cpp
if(number_num==0)cout<<"-";
	else{
		cout<<"\"";
		for(int i=1;i<number_num;i++)cout<<number[i]<<",";
		cout<<number[number_num]<<"\"";
	}
	cout<<"\n";
	if(ABC_number_num==0)cout<<"-";
	else{
		cout<<"\"";
		for(int i=1;i<ABC_number_num;i++)cout<<ABC_number[i]<<",";
		cout<<ABC_number[ABC_number_num]<<"\"";
	}
```
那么整个程序就出来了,代码如下：

## 代码借鉴区

```cpp
//CF600A Extract Numbers
//以合理借鉴为荣，以复制抄袭为耻
#include<bits/stdc++.h>
using namespace std;
string number[100010],ABC_number[100010];
int main(){
	string s,s1;int number_num=0,ABC_number_num=0;
	cin>>s;
	s+=";";
	for(int i=0;i<s.size();){
		s1="";
		while(i<s.size()&&s[i]!=','&&s[i]!=';')s1+=s[i],i++;
		if(s1==""){ABC_number[++ABC_number_num]=s1;i++;continue;}
		if(s1=="0")number[++number_num]=s1;
		else if(s1[0]=='0')ABC_number[++ABC_number_num]=s1;
		else{
			bool flag=true;
			for(int j=0;j<s1.size();j++)
				if(s1[j]<'0'||s1[j]>'9'){flag=false;break;}
			if(flag)number[++number_num]=s1;
			else ABC_number[++ABC_number_num]=s1;
		}
		i++;
	}
	if(number_num==0)cout<<"-";
	else{
		cout<<"\"";
		for(int i=1;i<number_num;i++)cout<<number[i]<<",";
		cout<<number[number_num]<<"\"";
	}
	cout<<"\n";
	if(ABC_number_num==0)cout<<"-";
	else{
		cout<<"\"";
		for(int i=1;i<ABC_number_num;i++)cout<<ABC_number[i]<<",";
		cout<<ABC_number[ABC_number_num]<<"\"";
	}
    return 0;
}
```


---

## 作者：Jerrywang09 (赞：1)

# 先说几句

只是一道讨厌的模拟。建议难度：普及。

# 解题思路

先在原始字符串上提取出每个子串。为了方便最后的处理，可以在原输入字符串最后加上一个分号。

每读到一个分号或逗号，当即进行判断。

写一个函数判断 $t$ 是否为数字串。清空字符串 $t$。

如果是数字串，就 ```ans1+=t```，否则就是字母串，```ans2+=t```。

为了方便输出，每 ```+=t``` 后都再加一个逗号。

最后了。如果没有数字串，就输出 ```-```。不然，就把 $ans_1$ 的最后一个多余的逗号去掉，前后加引号输出。反之亦然。
**注意：引号要使用转义字符。**

## 如何判断是否为数字串

如果字符串有前导零，只用看字符串的第一位是不是 $0$。

但如果字符串就是 ```0```，应当特判。

对字符串进行遍历。只要字符串出现非数字的字符，直接 ```return false```。

否则 ```return true```。

# 奉上代码

千万不要抄，小心棕名！

```cpp
// 600A Extract Numbers
#include <bits/stdc++.h>
#define var long long
using namespace std;
 
bool isNumber(string s)
{
	if(s=="0")
		return true;
	if(s[0]=='0')
		return false;
	for(int i=0; i<s.size(); i++)
		if(!('0'<=s[i] && s[i]<='9'))
			return false;
	return true;
}
 
int main()
{
	string s; cin>>s;
	s+=';';
	string t;
	string ans1;
	string ans2;
	for(int i=0; i<s.size(); i++)
	{
		if(s[i]!=',' && s[i]!=';')
			t+=s[i];
		else
		{
			if(t=="")
				ans2+=',';
			else if(isNumber(t))
				ans1+=t, ans1+=',';
			else
				ans2+=t, ans2+=',';
			t.clear();
		}
	}
	if(ans1=="")
		cout<<"-"<<endl;
	else
	{
		ans1.erase(ans1.size()-1);
		cout<<"\""<<ans1<<"\""<<endl;
	}
		
	if(ans2=="")
		cout<<"-";
	else
	{
		ans2.erase(ans2.size()-1);
		cout<<"\""<<ans2<<"\"";
	}	
 
    return 0;
}
```

---

## 作者：帅鹏 (赞：1)

## 题面翻译：

给定一个字符串，我们将该字符串所有极长的被 ',' 或是 ';' 分隔开的子串称为”单词“。
如字符串："aba,123;1a;0"。
一共有 "aba" 、 "123" 、 "1a" 、 "0" 共4个单词。
其中不包含阿拉伯数字以外字符且无前导的单词被认为是数字单词。
现在请你将所有的单词进行分类，将所有的数字单词输出在第一行，其余的输出在第二行。
需要注意的是单词可以为空字符串，且此类单词被认为是非数字单词。

## 题目大意：

把不包含阿拉伯数字以外字符且无前导的单词从其他字符串里分离出来，并输出这两个字符串。


## 做法

这道题是较为基础的字符串模拟题，读清题意，注意细节即可。需要注意的是双引号的输出方法，需要用单引号来代替双引号括住双引号输出。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define N 110000
char s[N];
int ans[2][N];
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	s[++n]=';';//在结尾添加;方便处理
	for(int i=1,k=1,fg=1;i<=n;i++)//k表示当前单词的起始点，fg表示当前单词是否为数字单词
	if(s[i]==','||s[i]==';'){
		if(k==i)fg=0;//特判空字符串
		ans[fg][++ans[fg][0]]=k;
		k=i+1;
		fg=1;
	}else{
		if(!isdigit(s[i])||(i==k+1&&s[i-1]=='0'))
		fg=0;
	}
	for(int o=1;o>=0;o--){//分别输出数字单词和非数字单词
	if(!ans[o][0]){
		printf("-\n");
		continue;
	}//特判单词数量为0
	printf("\"");
	for(int i=1;i<=ans[o][0];i++){
		int x=ans[o][i];
		while(s[x]!=','&&s[x]!=';')putchar(s[x++]);
		if(i!=ans[o][0])printf(",");
	}
		printf("\"\n");
	}
	return 0;
}

---

## 作者：cyz_czy (赞：0)

# CF600A 题解

这道题其实非常简单，对于输入的字符串我们需要读取题中给定标点符号`,`和`;`之间的每一个单词，在进行题中所给的判断方式筛选数字单词，将数字单词存在一个字符串数组中，讲非数字单词存在另一个数组中，在进行相应输出即可。

我们可以定义一个判断函数，用双重循环嵌套，第一层的条件是字符串长度，即从头到尾的读取每一个单词。第二重循环判断条件则是`.`和`;`两个，即单词之间的界限，在此循环外定义一个`bool`变量赋值为`false`，若在读取单词时读取到非阿拉伯数字则转换为`true`；一个字符串累加单词，直到碰到界限。

在碰到界限后需要进行判断。如果有前导$0$且累加字符串长度大于一，即单词不是$0$并且有前导$0$；或者`bool`变量为`true`，，即出现了非阿拉伯数字，则为非数字单词。否则，就是数字单词。将两种不同的单词放入两个数组即可。在读取完一个单词后，判断下标加$1$,跳过该界限，进入下一次读取。

注意：若在读取时第一个就读到了界限，则这是一个空单词；字符串的最后一个若是界限，则还有一个空单词；空单词是非数字单词。

此部分如下：
```cpp
void du(){
	while(d<l.length()){
		bool t=false;
		
		if(l[d]==';'||l[d]==','){
			ans2[c2]="";
			c2++;
			d++;
			continue;
		}
		
		std::string s="";
		while(l[d]!=';'&&l[d]!=','&&d<l.length()){
			if(l[d]<48||l[d]>57)
				t=true;/
			s+=l[d];
			d++;
		}
		
		if(s[0]=='0'&&s.length()!=1||t)ans2[c2]=s,c2++; 
		else ans1[c1]=s,c1++;
		
		d++;
	}
	
	if(l[d-1]==';'||l[d-1]==',')
		ans2[c2]="",c2++;
	
	return ;//养成好习惯
}
```

对于输出，按照题目和样例输出即可。


个人建议：字符串的输入和输出最好用`cin`和`cout`。

# Code:
```cpp
#include <iostream>

const int N=1e5+1e1;//养成好习惯

std::string ans1[N],ans2[N];// 存放两种不同类型的单词数组 ，第一个存数字单词，第二个存非数字单词 

std::string l;//输入的字符串 

int d;//判断时用的下标 
int c1,c2;//两组单词的个数与判断是用的下标 

void du(){
	while(d<l.length()){//将整个字符串读完 
		bool t=false;//判断是有没有非阿拉伯数字，若有则为true，没有为false 
		
		if(l[d]==';'||l[d]==','){//空单词 （是非数字单词） 
			ans2[c2]="";
			c2++;
			d++;
			continue;
		}
		
		std::string s="";//每个单词 
		while(l[d]!=';'&&l[d]!=','&&d<l.length()){
			if(l[d]<48||l[d]>57)
				t=true;//若出现非阿拉伯数字则不是数字单词 
			s+=l[d];//若没有碰到标点则累加 
			d++;//下标增加 
		}
		
		if(s[0]=='0'&&s.length()!=1||t)ans2[c2]=s,c2++;//判断：若单词不是“0”且有前导0则不是数字单词；若出现非阿拉伯数字也不是数字单词 
		else ans1[c1]=s,c1++;//不符合上述条件则是数字单词 
		
		d++;//跳过这次循环所碰到的标点符号 
	}
	
	if(l[d-1]==';'||l[d-1]==',')
		ans2[c2]="",c2++;//若在末尾还有标点，则还有一个空的费数字单词 
	
	return ;//养成好习惯
}

int main(){
	std::cin>>l;//输入 
	
	du();//读取每一个单词 
	
	bool t=false;//判断有没有数字单词 
	
	if(!c1)printf("-"),t=true;//没有 
	else std::cout<<"\""<<ans1[0];//一个\"表示一个双引号 
	
	for(int i=1;i<c1;i++)
		std::cout<<','<<ans1[i];//去掉末尾的，的输出方式 
	if(!t) printf("\"");//若没有输出单词则不输出后引号 
	
	printf("\n");//换行 
	
	t=false;//再次判断有没有非数字单词 
	
	//接下来的输出方式同上 
	
	if(!c2)printf("-"),t=true;
	else std::cout<<"\""<<ans2[0];
	
	for(int i=1;i<c2;i++)
		std::cout<<','<<ans2[i];
	
	if(!t)printf("\"");
	
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/109625336)

### 祝你 $\color{green}AC$ ！

---

## 作者：JerryMao (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF600A)

### 题意翻译

给定一个字符串，我们将该字符串所有极长的被 `,` 或是 `;` 分隔开的子串称为“单词”。

如字符串： `aba,123,1a,0`。

一共有 `aba` 、 `123` 、 `1a` 、 `0` 共 4 个单词。

其中不包含阿拉伯数字以外字符且无前导的单词 `0` 被认为是数字单词。

现在请你将所有的单词进行分类，将所有的数字单词输出在第一行，其余的输出在第二行。

需要注意的是单词可以为空字符串，且此类单词被认为是非数字单词。

首先为了方便，我们在字符串结尾加一个 `,` 或 `;` 表示字符串结束，然后把每一段分开，压到一个 vector<string> 里，然后判断每一段是数字还是单词。
  
首先，有一位不是数字的就是单词，其次，有前导 0 的不是（`0` 要特判），剩下的都是数字。
  
记录答案的时候也用 vector<string>，这样可以避免空串和空集合的问题，如果 `size==0` 就是空集合。

代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define rep(i,n) for(int i=0;i<n;i++)
#define Rep(i,x,n) for(int i=x;i<n;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define all(v) v.begin(),v.end()
#define itr_ iterator
#define p_b push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fr first
#define sc second
#define m_p make_pair
#define fill(a,b) memset(a,b,sizeof(a))
#define debug(x) cout<<#x<<":"<<x<<endl;
#define setp setprecision
#define over(x) {cout<<x<<endl; return ;}
using namespace std;
const ll INF=0x3f3f3f3f;
const ll mod=1000000007;
const ld eps=1e-14;

string s;
vector<string> v;
vector<string> words,numbers;

bool isnum(string t){
	if(t.size()==0) return 0;
	rep(i,t.size()){
		if(!isdigit(t[i])) return 0;
	}
	if(t.size()>1&&t[0]=='0') return 0;
	return 1;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin>>s;
	s+=';';
	int i=0,j=0;
	for(i=0;i<s.size();i++){
		string t="";
		for(j=i;s[j]!=','&&s[j]!=';';j++) t+=s[j];
		v.p_b(t);
		i=j;
	}
	rep(i,v.size()){
		if(isnum(v[i])) numbers.p_b(v[i]);
		else words.p_b(v[i]);
	}
	if(numbers.size()==0) cout<<'-'<<endl;
	else{
		cout<<'"';
		rep(i,numbers.size()){
			cout<<numbers[i];
			if(i<numbers.size()-1) cout<<',';
		}
		cout<<'"'<<endl;
	}
	if(words.size()==0) cout<<'-'<<endl;
	else{
		cout<<'"';
		rep(i,words.size()){
			cout<<words[i];
			if(i<words.size()-1) cout<<',';
		}
		cout<<'"'<<endl;
	}
	return 0;
}
```

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个字符串，其中有若干个单词由`,`或`;`隔开，将所有单词分为数字和非数字，分两行输出。

## 思路

一道~~简单但是复杂的~~模拟。

用一个临时字符串存储每一个单词，顺便判断它的性质，用一个变量记录。

- 出现字母，不是数字；
- 首位是 $ 0 $ ，不是数字（特判"0"）；
- 啥都没有，不是数字。

记录一下是否出现数字或者不是数字，你可以选择用数组+变量来记录每一个单词，但我选择了用队列，可以少一个变量。

判了这么多，差不多就可以过了。要小心**细节**，比如逗号。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool flg=true;
char ch[100005];
queue<string> q,q1;
string nw;
int main(){
	cin>>ch+1; 
	n=strlen(ch+1)+1;
	ch[n]=';';
	for(int i=1,j=1;i<=n;i++){
		if(ch[i]==','||ch[i]==';'){
			if((flg&&nw!="")||nw=="0") q.push(nw);
			else q1.push(nw);
			nw="";
			flg=true;
			j=i+1;
		}
		else{
			nw+=ch[i];
			if((i==j&&ch[j]=='0')||ch[i]<'0'||ch[i]>'9') flg=false;
		}
	}
	if(q.size()){
		putchar('"');
		while(!q.empty()){
			cout<<q.front();
			q.pop();
			if(q.size()) putchar(',');
		}
		putchar('"');
	}
	else putchar('-');
	putchar('\n');
	if(q1.size()){
		putchar('"');
		while(!q1.empty()){
			cout<<q1.front();
			q1.pop();
			if(q1.size()) putchar(',');
		}
		putchar('"');
	}
	else putchar('-');
	return 0;
}
```

---

## 作者：qwcdim (赞：0)

# CF600A Extract Numbers
[题目传送门](https://www.luogu.com.cn/problem/CF600A)

乘机安利亿下[My blog](https://www.luogu.com.cn/blog/I-like-10/)

~~不好勿喷~~

万事开头难，我们首先要读懂题意。（~~不过为啥没人翻译呀~~）

## 题目描述：
给定一个字符串，我们将该字符串所有极长的被   $\texttt{','}$    或是  $\texttt{';'}$   分隔开的子串称为“单词”。

如字符串： "$\texttt{aba , 123 , 1a , 0}$"  。

一共有  $\texttt{"aba" 、 "123" 、 "1a" 、 "0"}$  共4个单词。

其中不包含阿拉伯数字以外字符且无前导的单词 $0$ 被认为是数字单词。

现在请你将所有的单词进行分类，将所有的数字单词输出在第一行，其余的输出在第二行。

需要注意的是单词可以为空字符串，且此类单词被认为是非数字单词。

## 题目分析：
这题其实是个模拟，模拟数字单词的条件就行了，要注意的是不能有前导$0$

最后发个~~高清无水的~~代码：
```cpp
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
string a,b,e[2][100001];
long long c=-1,d,f,g;
bool h;
int main(){
    cin>>a;
    a+=',';
    for(int x=0;x<a.size();x++){
        if(a[x]==','||a[x]==';'){
            if(x>c) b=a.substr(c+1,x-c-1);
            else b="\0";
            c=x;
            h=false;
            if(b=="\0"){
                e[1][++d]=b;
                continue;
            }
            if(b=="0"){
                e[0][++f]=b;
                continue;
            }
            for(int y=0;y<b.size();y++){
                if(!y&&b[y]=='0'||b[y]<'0'||b[y]>'9'){
                    h=true;
                    break;
                }
            }
            if(h) e[1][++d]=b;
            else e[0][++f]=b;
        } 
    }
    if(f!=0){
        cout<<'"';
        for(int x=1;x<=f;x++){
            cout<<e[0][x];
            if(x!=f) cout<<',';
        }
        cout<<'"'<<'\n';
    }else cout<<"-\n";
    if(d!=0){
        cout<<'"';
        for(int x=1;x<=d;x++){
            cout<<e[1][x];
            if(x!=d) cout<<',';
        }
        cout<<'"'<<'\n';
    }else cout<<"-\n";
}
```


---

## 作者：跳跳谷hj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF600A)

题意：给你一个正整数，要求你把数字单词和非数字单词分离出来并输出,有一点要注意的是有前导 $0$ 的单词和空字符串也是非数字单词。

我们清楚题意以后，我们可以在原字符串末尾添加一个 ";" 以方便处理。

处理一串单词是否为数字单词和非数字单词的代码可以这样写：

```cpp
	bool f=0;
    for(int i=0;i<s.size();i++){
        if((s[0]=='0'&&s.size()!=1)||!(s[i]>='0'&&s[i]<='9')){//要注意，有前导0的单词只用检查第一位并检查其长度是否为一才能知道这个单词是否是数字单词或非数字单词
            f=1;
            break;
        }
    }if(f||s=="")sss[ts++]=s;
    else sn[tn++]=s;
```

## 接下来就是输出双引号的问题
双引号的输出可以用 ascii 码来强制转换，如果不记得双引号的 ascii 码可以自己现场写一个这样的程序来看：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    for(int i=0;i<=256;i++)cout<<" No."<<i<<' '<<(char)(i);
    cout<<"\n";
}
```

最后，贴上 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int tn,ts;
string sn[100010],sss[100010],ls,ss;
void pd(string s){
    bool f=0;
    for(int i=0;i<s.size();i++){
        if((s[0]=='0'&&s.size()!=1)||!(s[i]>='0'&&s[i]<='9')){
            f=1;
            break;
        }
    }if(f||s=="")sss[ts++]=s;
    else sn[tn++]=s;
}
int main(){
    cin>>ss;
    ss+=';';
    for(int i=0;i<ss.size();i++){
        if(ss[i]==','||ss[i]==';'){
            pd(ls);
            ls="";
        }else ls+=ss[i];
    }if(tn==0)printf("-");
    else{
        cout<<(char)(34)<<sn[0];
        for(int i=1;i<tn;i++)cout<<','<<sn[i];
        cout<<(char)(34);
    }printf("\n");
	if(ts==0)printf("-");
	else{
        cout<<(char)(34)<<sss[0];
        for(int i=1;i<ts;i++)cout<<','<<sss[i];
        cout<<(char)(34);
    }printf("\n");
	return 0;
}
```
感谢各位大佬们观看蒟蒻的题解，感谢各位善良的管理员


---

## 作者：Clever_Jimmy (赞：0)

【CodeForces】CF600A Extract Numbers

### 题意简述：

给定一个字符串，你要将其中的「非负整数」串与其他串分离出来，并输出这两堆字符串。

$1 \le n \le 10^5$。

[题目链接](https://codeforces.com/contest/600/problem/A)


### 解题思路：

如果一个串是空串，我们就补上一个字符 $\\$$，然后输出的时候跳过这个字符即可。

然后在遍历整个 $S$ 的时候，将答案放到两个另外的字符串 $A$ 和 $B$ 中去，最后输出 $A, B$。

代码实现 **极其细节**，建议自己动手实现一下。

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 1e5 + 5;

int n, m, lens, lena, lenb, firsta = 1, firstb = 1;
char tmp[N], str[N], S[N], A[N], B[N];

bool valid(char ch) {
	return ch != ',' && ch != ';';
}

void Output() {
	if(!lena)
		puts("-");
	else {
		printf("\"");
		for(int i = 1; i <= lena; ++i) {
			if(A[i] == '$')
				continue;
			putchar(A[i]);
		}
		puts("\"");
	}
	if(!lenb)
		putchar('-');
	else {
		printf("\"");
		for(int i = 1; i <= lenb; ++i) {
			if(B[i] == '$')
				continue;
			putchar(B[i]);
		}
		printf("\"");
	}
}

void solve() {
	int flg = 1;
	for(int i = 1; i <= lens; ++i)
		if(!isdigit(S[i]))
			flg = 0;
	if(!lens || lens >= 2 && S[1] == '0')
		flg = 0;
	if(flg) {
		if(!firsta)
			A[++lena] = ',';
		for(int i = 1; i <= lens; ++i)
			A[++lena] = S[i];
		firsta = 0;
		lens = 0;
	}
	else {
		if(!firstb)
			B[++lenb] = ',';
		for(int i = 1; i <= lens; ++i)
			B[++lenb] = S[i];
		firstb = 0;
		lens = 0;
	}
}

int32_t main() {
	scanf("%s", tmp + 1);
	m = strlen(tmp + 1);
	
	if(!valid(tmp[1]))
		str[++n] = '$';
	for(int i = 1; i <= m; ++i) {
		if(!valid(tmp[i]) && !valid(tmp[i - 1]))
			str[++n] = '$';
		str[++n] = tmp[i];
	}
	if(!valid(str[n]))
		str[++n] = '$';
    // 添加 '$' 字符来处理空串
	
	/*for(int i = 1; i <= n; ++i)
		putchar(str[i]);
	puts("");*/
	
	for(int i = 1; i <= n; ++i) {
		if(valid(str[i]))
			S[++lens] = str[i];
		else {
			int flg = 1;
			for(int i = 1; i <= lens; ++i)
				if(!isdigit(S[i]))
					flg = 0;
			if(!lens || lens >= 2 && S[1] == '0')
				flg = 0;
			if(flg) {
				if(!firsta)
					A[++lena] = ',';
				for(int i = 1; i <= lens; ++i)
					A[++lena] = S[i];
				firsta = 0;
				lens = 0;
			}
			else {
				if(!firstb)
					B[++lenb] = ',';
				for(int i = 1; i <= lens; ++i)
					B[++lenb] = S[i];
				firstb = 0;
				lens = 0;
			}
		}
	}
	solve();
	Output();
	return 0;
}
```

---

## 作者：cold_cold (赞：0)

 [安利一波博客](https://www.cnblogs.com/cold-cold/p/10074267.html)


**题意：**

给一个字符串，里面的小字符串用','或者';'分开，筛选出所有的不含前导0的数字存在一个字符串里面，并用','分开

其余字符串存在另一个字符串里面，空字符串也要存，存在第二个字符串里面。

 
 

此题模拟即可

因为要判断前导0的时候

第一位出现1~9以外或以后的位数出现0~9进入非数字串

其他的主要是string库的运用

和输出  ” 时要打转义符 ‘\’

**另外样例有误，请管理员重新爬取**

实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
vector<string> m;
string a,cx,cy;
int n,la=0;
int che(int x,int y)
{
	if(y<x) return 0;
	if(x==y&&a[x]=='0') return 1;
	if(a[x]<='0'||a[x]>'9') return 0;
	for(int i=x;i<=y;i++) if(a[i]<'0'||a[i]>'9') return 0;
	return 1;
}
int main()
{
//    freopen("input","r",stdin);
//    freopen("output","w",stdout);
	getline(cin,a);
	a+=';';
	n=a.size();
	for(int i=0;i<n;i++)
	{
		if(a[i]==','||a[i]==';')
		{
			if(che(la,i-1))
				cx=cx+','+a.substr(la,i-la);
			else
				cy=cy+','+a.substr(la,i-la);
			la=i+1;
		}
	}
	if(n=cx.size())
	{
		printf("\"");
		for(int i=1;i<n;i++) printf("%c",cx[i]);
		printf("\"\n");
	}
	else puts("-");
	if(n=cy.size())
	{
		printf("\"");
		for(int i=1;i<n;i++) printf("%c",cy[i]);
		printf("\"\n");
	}
	else puts("-");
    return 0;
}
```

---

