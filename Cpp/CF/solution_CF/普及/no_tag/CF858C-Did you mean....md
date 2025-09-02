# Did you mean...

## 题目描述

Beroffice text editor has a wide range of features that help working with text. One of the features is an automatic search for typos and suggestions of how to fix them.

Beroffice works only with small English letters (i.e. with 26 letters from a to z). Beroffice thinks that a word is typed with a typo if there are three or more consonants in a row in the word. The only exception is that if the block of consonants has all letters the same, then this block (even if its length is greater than three) is not considered a typo. Formally, a word is typed with a typo if there is a block of not less that three consonants in a row, and there are at least two different letters in this block.

For example:

- the following words have typos: "hellno", "hackcerrs" and "backtothefutttture";
- the following words don't have typos: "helllllooooo", "tobeornottobe" and "oooooo".

When Beroffice editor finds a word with a typo, it inserts as little as possible number of spaces in this word (dividing it into several words) in such a way that each of the resulting words is typed without any typos.

Implement this feature of Beroffice editor. Consider the following letters as the only vowels: 'a', 'e', 'i', 'o' and 'u'. All the other letters are consonants in this problem.

## 样例 #1

### 输入

```
hellno
```

### 输出

```
hell no 
```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
abacaba 
```

## 样例 #3

### 输入

```
asdfasdf
```

### 输出

```
asd fasd f 
```

# 题解

## 作者：naroto2022 (赞：4)

### 题意
如果一个字符串同时满足：

1、三个或以上个连着的辅音字母

2、这一段连着的辅音字母不是全部一样的

则这个字符串非法

整个程序都用一个循环来模拟，要满足要求要求可以用一个 $num$ 来统计连续辅音字母的数量，大于等于 $3$ 且 $3$ 个辅音字母不一样，输出空格。

另外，我们可以加一个辅音元音判断的程序

```cpp
int pd(char x){
    for(int i=0; i<5; i++)
        if(x==y[i])//y数组来统计元音
            return 0;//如果是就返回0
    return 1;//辅音返回1
}
```
上总代码！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len,num;//len为字符串长度，num来统计连续辅音字母的数量
char y[5]={'a','e','i','o','u'};//y数组来储存元音字母
int pd(char x){//判断是否为辅音字母
    for(int i=0; i<5; i++)//循环枚举看x是否为元音字母
        if(x==y[i])//如果x是元音字母
            return 0;//返回0
    return 1;//返回1代表x为辅音字母
}
int main(){
    getline(cin,s);//输入字符串
    len=s.size();//len存字符串的长度
    num=pd(s[0]);
    /*
    如果返回1则s[0]为辅音字母，辅音字母的数量要+1
    （因为初始为0，函数返回1，num就等于1）
    否则s[0]为元音字母，函数返回0，辅音字母的数量也要为0
    */
    cout<<s[0];//输出第一个字符
    for(int i=1; i<len; i++){//循环模拟
        if(pd(s[i])==0) num=0;//如果s[i]为元音字母，连续辅音字母的数量清空为0
        else{//否则为辅音字母
            ++num;//连续辅音字母数量要“更新”(+1)
            if(num>=3&&!(s[i]==s[i-1]&&s[i-2]==s[i])){//判断是否满足题意
                cout<<' ';//满足要求就输出空格
                num=1;//字符串新开了一段，但开头仍为辅音字母，所以连续辅音字母的数量为1
            }
        }
        cout<<s[i];//原封不动的输出
    }
    return 0;//养成好习惯
}
```

### 洛谷讲究学术诚信，请勿复制！

---

## 作者：Archy_ (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF858C)   [CF链接](https://codeforces.com/problemset/problem/858/C)

## 题目简述：

一个字符串，如果它的子串**同时**满足

1. 三个或以上个连着的辅音字母。

2. 这一段连着的辅音字母不是全部一样的。

就认为它**不合法**。用**最少的空格**隔开这个字符串，使它**合法**。

## 思路：

使用最少的空格我们只需**在 $3$ 个连续互不相同的辅音字母的第 $2$ 个后面输出空格**即可。

辅音字母有很多个，但元音字母只有 $5$ 个，一个字母不是元音就是辅音，我们可以判断这个字母是否为辅音字母。

我们创建 $cnt$ 来**记录连续辅音字母的个数**，怎么判断呢？我们遇到一个辅音字母就加 $1$，如果遇到元音字母则清 $0$。当 $ans$ 为 $3$ 时我们需要输出空格，此时改 $ans$ 为 $1$。然后再输出这个字符。

## code：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
char y[5]={'a','o','e','i','u'};
int cnt,len;
string s;
bool pd(char a){//判断是否为元音字母
	for(int i=0;i<5;i++)
		if(y[i]==a)return true;//是元音字母
	return false;//是辅音字母
}
int main(){
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++){
		if(pd(s[i]))cnt=0;//如果是元音字母cnt就清0
		else {
			cnt++;//如果是辅音字母cnt就加1
			if( cnt>=3 && !( s[i] == s[i-1] && s[i] == s[i-2]) ){//判断条件
				cout<<" ";//模拟题意
				cnt=1;//将cnt更新为1,因为空格后的字母也算。
			}
		}
		cout<<s[i];//输出这个字符，要放在循环最后面
	}
	cout<<"\n";//换行
	return 0;
} 
```
### 通过截图：
![](https://cdn.luogu.com.cn/upload/image_hosting/zu8emgex.png)


---

## 作者：abensyl (赞：1)

## [原题传送门](https://www.luogu.com.cn/problem/CF858C)

## 题意翻译

都是小写字母。

给你一个字符串，如果它的子串同时满足：

- 1.三个或以上个连着的辅音字母；

- 2.这一段连着的辅音字母不是全部一样的，

就认为它不合法。

现在要求用最少的空格隔开这个字符串，使得它变成合法的。

## 解决方案

- 先设一计数变量，表示连续辅音数量。

- 如果是原音，计数变量（连续辅音数量）赋值为 $1$。

- 如果是辅音，计数变量（连续辅音数量）加 $1$。

- 判断如果计数变量（连续辅音数量）大于等于 $3$，并且这三个连续的辅音不相同（题目中规定字符串违法的条件），那么就输出空格，分开字符串。

## 代码

```cpp
//小提示：看到很多写本题题解的大佬都是用cout输出的，但是putchar()比cout快得多
#include <iostream> 
#include <cstring> 
using namespace std;
const int N = 3e3 + 7;
char c[N];
bool check (char a) { //判断是否为辅音 
	if(a == 'a'|| a == 'e'|| a == 'i'|| a == 'o'|| a == 'u') 
        return 0; //如果是元音，返回false 
	return 1; //否则返回true
}
int main () {
	scanf("%s",c);
    int len = strlen(c); //即将字符串长度赋值给变量len，避免重复调用strlen()函数浪费时间
    int cnt = check(c[0]); //初始化计数变量cnt，用来记录连续辅音个数
    putchar(c[0]); //无论如何，都直接将第一个字符打出
	for(int i = 1; i < len; ++i) { //开始遍历整个数组，爆枚思想
        if(!check(c[i])) cnt = 0; //按题目要求，如果是原音，将计数变量cnt赋值为1，以备继续判断使用
        else {  //如果不是元音（是辅音）
			cnt++; //计数变量加一
			if(cnt >= 3 && !(c[i] == c[i-1] && c[i] == c[i-2])) 
            //判断如果连续辅音数量大于等于3，并且这三个连续的辅音不相同（题目中规定字符串违法的条件）
                putchar(' '), cnt = 1;
                //为避免字符串违法，加入空格，并将计数变量初始化为1，以备继续判断使用
		}
		putchar(c[i]); //不论是元音还是辅音，都应该输出这个字母
	}
	return 0; //好习惯养成从我做起
}
```

---

## 作者：xzy090626 (赞：1)

# CF858C 题解
[原题传送门](https://www.luogu.com.cn/problem/CF858C)
## 题意
给你一个字符串，如果它同时满足
1. 存在**三个或以上**连着的**辅音字母**；
2. 该段连着的辅音字母不是全部一样的。

那么该串非法。

现在要求用最少的空格隔开这个字符串，使得它变成合法的。


## 分析
从题面上我们可以得出本题的要点：

对于一个非法的字符串，导致其非法的子串必须满足三条：
1. 必须有三个及以上的长度；
2. 必须**均为**辅音字母；
3. 必须保证该子串含有**多种字母**（即各个字母非全部一样）。
## 思路
针对以上提到的要点，我们可以写出针对它们的判断程序。
首先，定义一个变量 $\text{ans}$，用来记录当前连续的辅音字母个数。

那么，$\text{ans} \geq 3$ 即为要点一的判断条件。
```cpp
bool In(char a){ //判断是否为辅音字母
	for(int i=0;i<5;++i){
		if(a==arr[i]) return 0;
	}
	return 1;
}
```
此段代码的目的是判断是否为辅音字母，符合要点二；

`!(s[i]==s[i-1]&&s[i-2]==s[i])` 

该行代码的作用是判断该子串是否有不同的字母，用于判断要点三。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3007;
char s[maxn];
const char arr[] = {'a','e','i','o','u'};
bool In(char a){ //判断是否为辅音字母
	for(int i=0;i<5;++i){
		if(a==arr[i]) return 0;
	}
	return 1;
}
int main(){
    cin>>s;
    int ans = In(s[0]);
    cout<<s[0];
    for(int i=1;i<strlen(s);++i){
        if(!In(s[i])) ans = 0;//若为元音字母，则更新 ans
        else{
            ++ans;
            if(ans>=3&&!(s[i]==s[i-1]&&s[i-2]==s[i])){ //判断是否满足题意，应当输出空格
                cout<<' ';
                ans = 1;
            }
        }
        cout<<s[i]; //输出该字母
    }
    return 0;
}
```
由于洛谷的 remotejudge 总是挂，所以就直接在 CF 上交了/jk

[AC记录](https://codeforces.com/problemset/submission/858/160425800)

---
## 总结
其实这道题十分细节，对于题目中每个关键点都需要考虑到才能通过本题。

这也告诉我们，在 OI 中，读题是非常重要的。（~~惨痛教训~~）

希望本题解能给您带来帮助。

---

## 作者：Wsy_flying_forever (赞：1)

## 贪心

本文本着把思路讲解得更清晰为初衷而作。


### 思路  
题目中说三个辅音字母及以上就要断开，则三个辅音字母间必有一个空格，当第一个字母与元音字母或空格相连，我们当然希望选择的空格位置在第二个和第三个之间。  
于是，我们可以总结出如下规则：  
1.$cnt$ 到达 $3$ 时要在当前字符前添加空格    
2.当前位置若为空格或元音，$cnt$ 清为 $0$。
### 代码实现
贪心加模拟，添加空格可以用 string 的 s.insert()。这里就不放代码了（其他题解有）。

完结撒花！

---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF858C)

# 题目描述

要你使用最少的空格隔开这个字符串，使它的每一段都是合法的，合法的要求就是这个字符串中没有三个字符及以上的非全部相等的连续的子串。

# 解题思路

记下当前辅音字母连续的长度 $l$ 和当前连续非全部相等辅音字母。

如果 $l \geq 3\ and\ c \geq 1$ 就要分段了！

（只要非全不相等（全相等为 $c \to 0$）并且长度大于等于 $3$ 就要分段。）

# 代码

```cpp
#include <iostream>
using namespace std;
string s, now;
int l, c;
bool Is(char);
int main() {
	cin >> s;
	if (Is(s[0]))
		l += 1;
	now = s[0]; // 特判第一个字符 (如果以后判的话s[i - 1]会越界)
	for (int i = 1; i < s.size(); i++) {
		if (Is(s[i]))
			l += 1;
		if (Is(s[i]) and s[i] != s[i - 1] and Is(s[i - 1]))
			c += 1; // 如果它和前面的字符不相等则c+1
		if (l >= 3 and c >= 1) {
			cout << now << " "; // 输出当前段
			now = "";
			l = 1; // 已经有一个辅音了
			c = 0;
		} else if (not Is(s[i])) // 如果不是辅音则重置
			l = c = 0;
		now += s[i];
	}
	if (now != "") // 如果最后还剩下了一段，就输出。
		cout << now;
	return 0;
}
bool Is(char ch) { // 判断是否是辅音的函数
	if (ch == 'a' or ch == 'e' or ch == 'i' or ch == 'o' or ch == 'u')
		return false;
	return true;
}
```

---

## 作者：laeva (赞：1)

### 贪心大法好

对于此题，我们只需维护这样的一个东西：纪录一个辅音块的长度，如果长度超过3且连续3个字符中又不一样的，断开它就行了

#### 这是为什么呢？？？

我们设想有这样的一个辅音块，他是不合法的，那么我们势必要断开他，，那当然是越晚断开越好（这样的话断点后面会更短，更容易合法）
~~就这样OK了~~
```
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 3010
using namespace std;
char s[MAXN];
int ask(char x)
{
    return x=='a'||x=='e'||x=='i'||x=='o'||x=='u';
}
int main(int argc, char const *argv[])
{
    scanf("%s",&s);
    int l=strlen(s);
    int ans=0;//ans记录辅音块长度
    if(!ask(s[0])) ans++;printf("%c",s[0]);
    for(int i=1;i<l;i++){
        if(ask(s[i])){
            ans=0;//前面的辅音块已处理，ans归零
        }
        else{
            ans++;
            if(ans>=3&&(s[i]!=s[i-1]||s[i-2]!=s[i-1])){
            	//如果此辅音块不合法
                printf(" ");
                ans=1;//注意是1，因为当前字符是划分后辅音块的开头
            }
        }
        printf("%c",s[i]);
    }
    return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF858C)&[CF 链接](https://codeforces.com/problemset/problem/858/C)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给你一个均为小写字母的字符串，如果它的子串同时满足：

1. 三个连着的辅音字母。

2. 这一段连着的辅音字母不是全部一样的。

就认为它不合法。

现在要求用**最少**的空格隔开这个字符串，使得它变成**合法**的。

## 思路

首先定义记录**当前位置是否是元音字母**的数组 $a$，并维护它，如下：

```cpp
for(int i = 0; i < n; i ++) {
		bool flag = false;
		for(int j = 0; j < 5; j ++) 
			if(str[i] == c[j]) flag = true;
		a[i] = flag;
	}
```

接着直接根据题目要求**模拟**即可，定义 $num$ 记录**当前连续辅音字母的个数**，当这个个数 $\ge 3$ 之后**输出空格**即可，**这里需要注意：需要先输出空格再输出字母！**

经过以上分析及代码片段，很容易即可写出代码了：

```cpp
#include<iostream>
using namespace std;

char c[10] = {'a', 'e', 'i', 'o', 'u'}; // 元音字母数组
string str;
bool a[3005]; // 记录是否是元音字母

int main(){
	cin >> str;
	int n = str.length();
  	// 预处理 a 数组
	for(int i = 0; i < n; i ++) {
		bool flag = false;
		for(int j = 0; j < 5; j ++) 
			if(str[i] == c[j]) flag = true;
		a[i] = flag;
	}
	int num = !a[0]; // 初始化 num
	cout << str[0]; // 先输出第一个字母
	for(int i = 1; i < n; i ++) {
  		// 如果是辅音字母
		if(!a[i]) {
			num ++; // 增加计数
			if(num >= 3 && !(str[i - 2] == str[i] && str[i - 1] == str[i])) {
				cout << ' '; // 满足条件输出空格
				num = 1; // num 初始化
			}
		}
		else num = 0; // 元音字母
		cout << str[i]; // 正常输出
	}
	return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/117922496)

$$\text{The End!}$$

---

## 作者：LBYYSM_123 (赞：0)

### 题意
对同时拥有着三个或以上个连着的且互不相同辅音字母字符串用空格隔开。


------------
### 解法
运用**贪心**，每当出现满足条件的三个相连的辅音字母就用空格隔开，再重置计数器。


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool pd(char x){//判辅音字母
    if(x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y')
        return 0;
    return 1;
}
int main(){
    string s;int num;
    cin>>s;
    num=(int)pd(s[0]);
    cout<<s[0];
    for(int i=1;s[i]!='\0';i++){//循环遍历
        if(pd(s[i])==0) num=0;//如果s[i]为元音字母，连续辅音字母的数量清空为0
        else{
            ++num;//数量+1
            if(num>=3&&!(s[i]==s[i-1]&&s[i-2]==s[i])){//题意
                putchar(' ');
                num=1;
            }
        }
        putchar(s[i]);
    }
    return 0;
}

```


---

## 作者：zz_z2Spider (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF858C)

建议在[我的博客](https://www.luogu.com.cn/blog/zzpearl-han233/)食用更佳。

------------
###  题意概述：

给你一个字符串，如果它的子串**同时**满足以下条件就认为它**不合法**：

1. 子串是由三个或三个以上连续的辅音字母组成的。

2. 这一段连续的辅音字母各不相同。

现在要求用最少的空格将这个字符串隔开，使得它变成合法的。

###  解题方法

我们可以这么想：定义一个计数器，先判断这个字符串的第一个字符（无论如何第一个字符都要输出），再从字符串的第二个字符开始判断，是元音就直接不管，将计数器**清零**；如果是辅音就继续判断（由于判断到了辅音计数器要加一），如果满足题目要求的条件就输出空格同时将计数器**变为一**（因为这个字符虽然是这个子串的结尾，但却是下一个子串的开头）；最后输出这个字符。

###  代码实现

```
#include<iostream>
#include<string>

using namespace std;

string kazz;
int n;
int jsq=0;

bool check(char zz)
{
	if(zz=='a'||zz=='e'||zz=='i'||zz=='o'||zz=='u')return 0;//元音 
	else return 1;//辅音 
}

int main()
{
	cin>>kazz;n=kazz.size();
	int jsq=check(kazz[0]);//判断第一个字符是元音还是辅音 
	cout<<kazz[0];//无论在哪里放空格都要输出第一个 
	for(int i=1;i<n;i++)//已经输出了kazz[0]，从1开始判断 
	{
		if(check(kazz[i])==0)jsq=0;//如果是元音，清零 
		else//是辅音，开始计算 
		{
		    jsq++;
			if(jsq>=3&&!(kazz[i-1]==kazz[i]&&kazz[i]==kazz[i-2]))//看题目条件 
			{
				cout<<" ";//依照题意模拟输出空格 
				jsq=1;//处理好了空格，将计数器重新变为1，因为现在这个字符是下一个的开头 
			}
		}
		cout<<kazz[i];
	}
	return 0;
}
```



------------

 [AC 记录](https://www.luogu.com.cn/record/89821743) 

---

