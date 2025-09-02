# [NWERC 2024] Alphabetical Aristocrats

## 题目描述

现在是公元 1830 年，荷兰王国在摆脱法国压迫者独立后已经过去了 15 年。你是国务大臣，也是卢森堡大公、荷兰国王威廉一世陛下的助手——这是一个注定要繁荣昌盛、延续数百年的帝国。令国王极为震惊的是，南方的叛逆之徒最近竟敢违抗他仁慈的统治。他们自称为比利时人，并宣布建立自己的王国——这一事实，陛下至少还会否认七到十一年。威廉国王以其卓越的智慧，决定召集最值得信赖的贵族，策划一场针对这些叛逆分子的战役，这场战役将持续超过九天。

:::align{center}

![](https://upload.wikimedia.org/wikipedia/commons/1/13/Kroegtafereel%2C_circa_1601_-_circa_1700%2C_Groeningemuseum%2C_0040612000.jpg?20201110013918)

Abraham van den Hecken the Younger 所作《酒馆场景》。CC0 授权，来源于 [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kroegtafereel,_circa_1601_-_circa_1700,_Groeningemuseum,_0040612000.jpg)

:::

你需要整理一份值得信赖的贵族名单，并按照荷兰规则对他们进行排序。荷兰规则规定，姓氏的比较应从第一个大写字母开始，仅比较该部分，并按照 ASCII 字符的字典序进行。例如，国王威廉在比较他最喜欢的画家 Abraham $\texttt{van den Hecken the Younger}$ 的姓氏时，应以 $\texttt{Hecken the Younger}$ 作为比较依据。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
van der Steen
fakederSteenOfficial
Groot Koerkamp
Bakker
van den Hecken the Younger
de Waal
van 't Hek
```

### 输出

```
Bakker
Groot Koerkamp
van den Hecken the Younger
van 't Hek
van der Steen
fakederSteenOfficial
de Waal```

## 样例 #2

### 输入

```
5
var Emreis
an Gleanna
Terzieff Godefroy
aep Ceallach
of Rivia```

### 输出

```
aep Ceallach
var Emreis
an Gleanna
of Rivia
Terzieff Godefroy```

## 样例 #3

### 输入

```
7
van den Brand
den Brand Heek
Brand 'Heek
van Brand heek
DeN bRAnD hEeK
den brandHeek
der Brandheek```

### 输出

```
van den Brand
Brand 'Heek
den Brand Heek
van Brand heek
der Brandheek
DeN bRAnD hEeK
den brandHeek```

# 题解

## 作者：ELSIA (赞：4)

### 1.题目传送门：
[P13739 [NWERC 2024] Alphabetical Aristocrats](https://www.luogu.com.cn/problem/P13739)
### 2.思路：
先定义一个结构体，以便更好的排序。这道题比较的部分是从第一个大写字母开始，一直到最后一个字母，所以在结构体里面除了要定义原字符串，再需定义一个空字符串用来保存要比较的部分。我们还需注意名字里有空格所以需要用 `getline`，但用 `getline` 会使 $n$ 也就是姓氏的数量后面的空格被保存，所以我们可以输入 $n$ 后输入一个没有用(~~好像也有用~~)的字符串，用来去掉 $n$ 后面的空格。
### 3.代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct asd{
	string s;
	string b = ""; //b一定要清空
	int c = 0;
}a[10000];
bool cmp(asd x , asd y){
	int len = min(x.b.size() , y.b.size());
	for(int i = 0 ; i < len ; i++){
		if(x.b[i] != y.b[i]){
			return x.b[i] < y.b[i];
		}
	}
	return x.c < y.c;
}
int main(){
	int n;
	cin >> n;
	string e;
	getline(cin , e);
	for(int i = 1 ; i <= n ; i++){
		getline(cin , a[i].s);
		for(int j = 0 ; j < a[i].s.size() ; j++){
			if(a[i].s[j] >= 'A' && a[i].s[j] <= 'Z'){
				for(int q = j ; q <a[i].s.size() ; q++){
					a[i].b = a[i].b + a[i].s[q];
					a[i].c++; 
				} 
				break;
			}
		}
	}
	sort(a+1 , a+1+n , cmp);
	for(int i = 1 ; i <= n ; i++){
		cout << a[i].s << endl;
	}
	return 0;
}
```
当然这段代码还可以简化，我们也可以直接比较字符串。  
简化的代码如下:
```cpp
#include <bits/stdc++.h>
using namespace std;
struct asd{
	string s;
	string b = "";
}a[10000];
bool cmp(asd x , asd y){
	return x.b < y.b;
}
int main(){
	int n;
	cin >> n;
	string e;
	getline(cin , e);
	for(int i = 1 ; i <= n ; i++){
		getline(cin , a[i].s);
		for(int j = 0 ; j < a[i].s.size() ; j++){
			if(a[i].s[j] >= 'A' && a[i].s[j] <= 'Z'){
				for(int q = j ; q <a[i].s.size() ; q++){
					a[i].b = a[i].b + a[i].s[q];
				} 
				break;
			}
		}
	}
	sort(a+1 , a+1+n , cmp);
	for(int i = 1 ; i <= n ; i++){
		cout << a[i].s << endl;
	}
	return 0;
}
```



[AC记录](https://www.luogu.com.cn/record/232152896)   
~~如果觉得这篇代码对你有帮助，请点个赞再走谢谢。~~

---

## 作者：volatile (赞：4)

# 思路

首先输入时将每个名字存入一个 string 数组。

```cpp
string names[1145];
int n;
cin>>n;
string t;
getline(cin,t);//读入一个换行
for(int i=1;i<=n;i++){
    getline(cin,names[i]);
    //......
}
```

然后遍历每个名字，找到第一个大写字母后，用一个字符串暂时储存从这个大写字母开始的名字子串。

```cpp
t="";
bool flag=0;
for(int j=0;j<names[i].size();j++){
    if(names[i][j]>='A'&&names[i][j]<='Z') flag=1;
    if(flag) t+=names[i][j];//字符串的拼接
}
```

存入结构体用于排序。

```cpp
struct node{
    string name;
    int i;
}s[1145];
```

```cpp
s[i].name=t;
s[i].i=i;//这个子串属于哪一个名字
```

然后写比较函数。由于每个名字的这个子串都不一样，所以不用考虑别的。

```cpp
bool cmp(node x,node y)
{
    return x.name<y.name;
}
```

最后排序输出即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string names[1145];
struct node{
    string name;
    int i;
}s[1145];
bool cmp(node x,node y)
{
    return x.name<y.name;
}
signed main()
{
    int n;
    cin>>n;
    string t;
    getline(cin,t);
    for(int i=1;i<=n;i++){
        getline(cin,names[i]);
        t="";
        bool flag=0;
        for(int j=0;j<names[i].size();j++){
            if(names[i][j]>='A'&&names[i][j]<='Z') flag=1;
            if(flag) t+=names[i][j];
        }
        s[i].name=t;
        s[i].i=i;
    }
    sort(s+1,s+1+n,cmp);
    for(int i=1;i<=n;i++) cout<<names[s[i].i]<<endl;
    return 0;
}
```

---

## 作者：lizongrui000 (赞：3)

### 分析题目
给定 $n$ 个字符串，对他们从第一个大写字母及以后的子串进行字典序排序，最后按这个顺序输出原来的字符串。
### 代码思路
定义一个结构体，分别存储输入的字符串和从第一个大写字母及以后的子串，对子串进行字典序排序，最后输出。输入时要使用 `getline()` 输入一整行，注意由于 `getline()` 会读入空格，导致第一个读入的字符串会是 $n$ 后面的空行，所以要先读入一次，再读入 $n$ 个字符串，详见代码。在对结构体进行排序时要写一个函数，判断子串，写进 `sort` 函数。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct xs
{
	string a,b="";
}s[1005];
bool cmp(xs as,xs bs)
{
	return as.b<bs.b;
}
int main()
{
	int n;
	cin>>n;
	string f;
	getline(cin,f);
	for(int i=1;i<=n;++i)
	{
		getline(cin,s[i].a);
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<s[i].a.size();++j)
		{
			if(s[i].a[j]>='A'&&s[i].a[j]<='Z')
			{
				for(int l=j;l<s[i].a.size();++l)
				{
					s[i].b+=s[i].a[l];
				}
				break;
			}
		}
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		cout<<s[i].a<<endl; 
	}
	return 0;
}
```

---

## 作者：Il1_1_3 (赞：2)

# P13739 题解

一点闲话：建议评橙。

## 题意

给出几个表示姓名的字符串，要求比较各个名字中第一个大写字母后面的子串。

## 思路

因为每个字符串中有空格，所以读入时需要用 `getline` 函数读入每一行。此处要注意的是：**读入 $n$ 之后要用 `cin.ignore()` 函数忽略换行符，否则 `getline` 会读少一行。**

利用 `sort` 排序，比较函数中先找每个串中的第一个大写字母，再截取以它开头的整个串的后缀，在最后比较两个后缀即可。

时间复杂度 $\Theta(|s|\cdot n\log n)$。

## 代码

标注了一些重要的地方。

```cpp lines=11,19,30,33 line-numbers
#include <bits/stdc++.h>
using namespace std;
bool cmp(string s,string t)
{
	int x=s.size(),y=t.size();
	string up1,up2;
	for(int i=0;i<x;i++)
	{
		if(s[i]>='A'&&s[i]<='Z')
		{
			up1=s.substr(i);
			break;
		}
	}
	for(int i=0;i<y;i++)
	{
		if(t[i]>='A'&&t[i]<='Z')
		{
			up2=t.substr(i);
			break;
		}
	}
	return up1<up2;
}
int main() 
{
    int n;
    string s[1003];
    cin >> n;
    cin.ignore();//忽略换行符
    for(int i=1;i<=n;i++)
    	getline(cin,s[i]);
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++)
    	cout << s[i] << '\n';
    return 0;
}
```

---

## 作者：zxr_0102 (赞：1)

# 思路：
这道题的话，我觉得还是很简单的，可以先建立一个结构体，里面存储两个字符串，一个是输入的字符串，另一个是满足排序标准的字符串，在输入的时候，只需将原本输入的字符串转换为满足排序标准的字符串，并将满足排序标准的字符串存入结构体，再进行结构体排序即可。
# AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    string s1,s2;
}a[10005];
bool cmp(const node& a, const node& b){
    return a.s2<b.s2;
}
int main(){
    int n;
    cin>>n;
    cin.ignore();
    for(int i=1;i<=n;i++){
        getline(cin,a[i].s1);
        bool flag=0;
        for(int j=0;j<a[i].s1.size();j++){
            if((a[i].s1[j]>=65&&a[i].s1[j]<=90)||flag==1){
                flag=1;
                a[i].s2+=a[i].s1[j];
            }
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        cout<<a[i].s1<<"\n";
    }
    return 0;
}
```

---

## 作者：zyr2011 (赞：1)

### 题目大意
给你 $n$ 个人名，你需要从**人名的第一个大写字母**（可以理解成姓）开始，按照 ```ASCII``` 码排序，**从小到大**输出排序后的人名。
### 题目解法
定义一个有两个字符串的结构体，一个字符串用来**存人名**，一个字符串来存**姓氏后的字符用来排序**，直接用我们的 ```getline``` 函数读入第一个字符串后，遍历一遍人名，把**第一个大写字母后的所有字符**加入到另一个字符串中，把这个结构体**按照第二个字符串**排序，输出**第一个**字符串即可。
### 满分代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
const int N=1000+10;
struct node{
	string now,nxt;//now用来存人名，nxt用来存第一个大写字母后的字符 
}e[N];
bool cmp(node a,node b){
	return a.nxt<b.nxt;
}//从小到大排 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	for(re int i=1;i<=n+1;++i){
		getline(cin,e[i].now);
	}//getline会提前多读一行，所以循环终点是n+1 
	for(re int i=1;i<=n;++i){
		e[i].now=e[i+1].now;
	}//因为之前循环终点是n+1，所以这里要更新为1~n 
	for(re int i=1;i<=n;++i){
		int len=e[i].now.size();
		bool flag=false;
		for(re int j=0;j<len;++j){
			if(isupper(e[i].now[j])){
				flag=true;
			}//判断是否有大写字母 
			if(flag){
				e[i].nxt+=e[i].now[j];
			}//出现第一个大写字母后存入字符 
		}
	}
	sort(e+1,e+n+1,cmp);//排序 
	for(re int i=1;i<=n;++i){
		cout<<e[i].now<<"\n";
	}
	return 0;
}
```

---

## 作者：jzy20241021062 (赞：1)

## 简述题意

有 $n$ 个包含空格的字符串，需要从第一个大写字母开始按照 ASCII 码表的顺序对其进行排序。

## 题解

一道典型的签到题。

直接自己定义一个比较函数 `cmp` 并使用 `sort` 方法排序即可。

`cmp` 方法分别从头开始遍历两个字符串，记录第一个大写字母的位置，而后两个字符串分别从记录下来的两个位置开始比较即可。

**注意**：由于每个字符串中包含空格，所以使用 `getline` 方法读取。但是由于最开始有一个 $n$ 使用了 `cin` 读取，但是此时末尾的换行符 `\n` 还留在缓冲区，如果直接使用 `getline` 读取会导致读到一个空白的字符串，所以使用 `cin.ignore()` 将缓冲区中的 `\n` 丢弃掉。

还应注意，比较的部分包括所有的字符，不需要对空格等特殊字符进行特判。

## AC 代码
```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3 + 5;

string words[N];

bool cmp(const string &s1, const string &s2){
    int x, y;
    for (int i = 0; i < s1.size(); i ++) {
        if (s1[i] <= 'Z' && s1[i] >= 'A') {
            x = i;
            break;
        }
    }
    for (int i = 0; i < s2.size(); i ++) {
        if (s2[i] <= 'Z' && s2[i] >= 'A') {
            y = i;
            break;
        }
    }
    for (; x < s1.size() && y < s2.size(); x ++, y ++) {
        if (s1[x] != s2[y])
            return s1[x] < s2[y];
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i ++)
        getline(cin, words[i]);
    sort(words, words + n, cmp);
    for (int i = 0; i < n; i ++)
        cout << words[i] << endl;
    return 0;
}
```

---

