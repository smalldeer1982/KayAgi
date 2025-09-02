# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA
```

### 输出

```
AB
```

## 样例 #2

### 输入

```
5
ZZZAA
```

### 输出

```
ZZ
```

# 题解

## 作者：WinterRain208 (赞：2)

CF977B 【Two-gram】

### 前言：如何给你的$DEV$开一个$cpp11$

已经开过的用户可以直接跳过啦。

工具->编译选项->编译时加入以下命令

```
-std=c++11
```
为什么要怎么做呢，因为我们要用$map$做这题。

### 题意分析

给一个字符串，求出现次数最多的长度为二的子串。


### $SOLUTION$

用$map$。

~~顾名思义~~ 和数组不同的地方是字符串，长整型，字符都可以作为下表使用，非常方便。

缺点是没有数组桶自带的排序功能，也不能直接排序。

这题枚举所有长度为二的子串，存入$map$，在打擂台求最值就可以了。

注意$map$的遍历方式很特殊，要用$cpp11$的功能。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

string a;
string ans;
int M=-1;

map <  string , int > m; 
int main(){
	cin>>a;
	cin>>a;
	F(i,0,a.size()-2)
		m[a.substr(i,2)]++;
	for( auto && p : m )
		if(p.second>M){
			M=p.second;
			ans=p.first.c_str();
		}
	cout<<ans<<endl;
    return 0;
}

```
可以看到

```
for ( auto && p : m )
	
```
是我们定义的一个指针，$first$是下表，要用$c$_$str$来获取，因为是字符串，$second$就是值了。

扩展一下，如果你的$map$是这样的。

```cpp
map < string , map < string , int > >
```
那应该

```
for(auto&&p:m)
	for(auto&&p2:p.second)
```


如果有错误欢迎指出。

$wtrl$。


---

## 作者：happybob (赞：2)

STL！！！

最近做题喜欢上了STL，来一发map

因为：

```cpp
找出现次数最多的长度为2的子串
```

所以说map需要为 <string, int>，每两位加一次，类似桶排序

但是问题来了，string的某一下标的数据是char类型，如何转换成string呢？

告诉你吧：

在c++中有一个函数

string 变量名称

而其中有一个参数是这样的：

string(size_t n, char c)

可以实现char转string

代码：

```cpp
#include <iostream>
#include <map>
using namespace std;

map <string, int> mp;//构造映射

string str, y;

int main()
{
    int n, max = 0;
    cin >> n >> str;
    for(int i = 1; i <= n - 1; i++)
    {
        //char转string
        string v(1, str[i]);
        string c(1, str[i - 1]);
        mp[c + v]++;//c + v不是v + c
    }
    for(map <string, int>::iterator it = mp.begin(); it != mp.end(); it++)//迭代器
    {
        if(it -> second >= max)//使用 -> second访问值
        {
            max = it -> second;
            y = it -> first;//使用 -> second访问下标
        }
    }
    cout << y << endl;
    return 0;
}
```


---

## 作者：Cult_style (赞：2)

我的思路是用字母转为数字作为下标，用一个二维数组（一个下标表示左边的字母，一个下标表示右边的字母），存着出现的个数，找到出现个数最多的输出就行了。

```
#include<bits/stdc++.h>
using namespace std;
int n;
int k[30][30];
char a[105];
int ma;
int main(){
	scanf("%d",&n);
	cin>>a;
	for(int i=0;i<n-1;i++){
		int x=a[i]-'A',y=a[i+1]-'A';
		k[x][y]++;
        	//转换为数字，个数加一
		if(k[x][y]>ma) ma=k[x][y];	
        	//找出现次数最多的
	}
	for(int i=0;i<26;i++){
		for(int j=0;j<26;j++){
			if(k[i][j]==ma){
				printf("%c%c",i+'A',j+'A');
                		//一找到就输出
				return 0;
			}
		}
	}
	
	return 0;
}
```


---

## 作者：GusyNight (赞：1)

```
题意：CF第一套div3，难度开始下降，1600分以上的做了不会算rating，第一次是测试的，注册的人很多，很多大佬都AK了，仰望.....
输入n，然后输入n个字符，输出里面连续两个字符出现最多次数的那两个字母。
题解：模拟  用个map<string,int>每次分出两个字母，map<这两个字母>++，然后记录出现最大的数，和字母。sting,有个substr可以直接用，当然不用的话，就两层for循环。
```
**两层for循环代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int>m;
int main(){    
	int n,maxn=0;    
	string s,a,ans;    
	cin>>n>>s;    
	for(int i=0; i<s.size(); i++){        
		a.clear();        
		for(int j=i; j<=i+1&&j<s.size();j++){
			a+=s[j];  
		}      
		m[a]++;        
		if(m[a]>maxn){
			maxn=m[a];
			ans=a; 
		}   
	}    
	cout<<ans;    
	return 0;
}
```
**sbstr代码一层循环**
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int>m;
int main(){   
	int n,maxn=0;   
	string s,ans,a;   
	cin>>n>>s;   
	for(int i=0;i<n;i++){       
		a=s.substr(i,2);       
		m[a]++;       
		if(m[a]>maxn){
			maxn=m[a],ans=a;  
		}    
	}   
	cout<<ans;    
	return 0;
}
```

---

## 作者：judgejudge (赞：1)

# 近似于map映射原理的题解！！！
这道题我用了一个比较奇怪的方法：

首先这道题只让我们查找**长度为2**的字符串，因此我们可以**定义一个二维数组来储存这些字符串**：方法如下：
|  | A | B |C  | D |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| A | AA | AB | AC |AD  |
| B |BA  | BB |  BC|BD  |
|C  | CA |  CB| CC |CD  |
| D |  DA|  DB|  DC|DD  |

我们可以哦那个上面的表格看出：把**每一个大写字母的ASCII码减去64作为行和列**，比如AB就可以记作第1行第2列，其他以此类推。这样我们就可以储存出现次数。

然后我们再从这个二维数组当中查找最大值，输出其行和列就可以了。

下面奉上AC代码:

```cpp
#include <iostream>
#include <string>
using namespace std;
int a[27][27];
string st;
int main(){
	int i,j,k,n;
	cin>>n;
	cin>>st;
	int maxl=0,row,col;
	for(i=0;i<n-1;i++)
	a[st[i]-64][st[i+1]-64]++;//储存到二维数组之中
	for(i=1;i<=26;i++)
	for(j=1;j<=26;j++)
	if(maxl<a[i][j]){
		maxl=a[i][j];
		row=i;
		col=j;//找到最大值，储存行和列
	}
	cout<<(char)(row+64)<<(char)(col+64)<<endl;//注意：最后要把ASCLL码转回去！！！
	return 0;
}
```



---

## 作者：cyrxdzj (赞：1)

### 一、思路

我们一看数据范围：$2\le n\le100$，这不就是明摆着的暴力算法吗！
我们可以枚举每一种可能，找出出现次数最多的子串。

### 二、完整代码

```cpp
#include<iostream>
#include<string>
using namespace std;
int len;//字符串长度。
string input;//输入。
int ans_cnt;//出现次数最多的子串出现的次数。
int ans_i;//出现次数最多的子串的位置。
int main()
{
	cin>>len>>input;
	for(int i=0;i<len-2;i++)
	{
		int cnt=1;//思考题。Q1：初始化为1有何意义？Q2：如果手欠改为0，对运行结果有影响吗？
		for(int j=i+1;j<len-1;j++)
		{
			if(input[i]==input[j]&&input[i+1]==input[j+1])//如果是一个符合要求的子串：
			{
				cnt++;//增加计数器。
			}
		}
		if(cnt>ans_cnt)//打擂台。
		{
			ans_cnt=cnt;
			ans_i=i;//更新答案。
		}
	}
	cout<<input[ans_i]<<input[ans_i+1]<<endl;//输出。
	return 0;//完结撒花！
}

```

### 三、思考题答案

Q1：别忘了两行之前 `int i=0` 中的 `i` 所指的字符串也是子串之一！

Q2：无影响。因为运行结果不打印子串的出现次数。

### 四、后记

记录：<https://www.luogu.com.cn/record/51630260>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Pkixzx (赞：1)

这道题其实是一个数组的题目。

我们循环这个字符串的1~n-1，然后把这两个字符丢进桶里。注意，这个桶是一个**二维数组**。接着我们循环每一个桶，最后输出桶里的数最多的那两个字符就可以了。

下面贴一下代码：
```
#include <bits/stdc++.h>
using namespace std; 
int hyf[110][110];
int main() 
{
	string s;
	char e,e1;
        long long n,n1,m1,m=0,j,k,i,t=-999;
        cin>>n>>s;
	for(i=0;i<n-1;i++)
	{
		hyf[int(s[i])][int(s[i+1])]++;//把每两个丢进桶里
	} 
	for(i=60;i<=90;i++)//循环每一个桶
	{
		for(j=60;j<=90;j++)
		{
			if(hyf[i][j]>t)//比桶里的个数，看看是不是最多的那个
			{
				t=hyf[i][j];
				e=char(i);
				e1=char(j);
			}	
		}
	}
	cout<<e<<e1;//输出
        return 0;
}
```


---

## 作者：封禁用户 (赞：1)

**STL**好题！  

---
主体：
$$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{map}\color{black}\texttt{<}\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{pair}\color{black}\texttt{<}\color{purple}\texttt{char}\color{black}\texttt{,}\color{purple}\texttt{char}\color{black}\texttt{>,}\color{purple}\texttt{int}\color{black}\texttt{>}$$  
其中，
$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{map}$记录$\underline\texttt{字符串->次数}$的映射
- $\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{pair}\color{black}\texttt{<}\color{purple}\texttt{char}\color{black}\texttt{,}\color{purple}\texttt{char}\color{black}\texttt{>}$记录$\underline\texttt{两个字符的字符串}$
- $\texttt{int}$记录$\underline\texttt{该字符串出现的次数}$

---
因此，这道题的暴力枚举方法是：
- 从$\texttt{i=0}$枚举到$\texttt{i=n-1}$，$\texttt{s}_\texttt{i}$和$\texttt{s}_\texttt{i+1}$组成的字符串出现次数+1
- 暴力枚举$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{map}$中的每个元素，找到出现次数最多的字符串并输出

时间复杂度$O(n)$。

---
如果不熟悉$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{pair}$，可以参考（放心，是中文的Reference）：
- [$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{pair}$](http://zh.cppreference.com/w/cpp/utility/pair)
- [$\color{orange}\texttt{std}\color{black}\texttt{::}\color{blue}\texttt{make\_pair}$](http://zh.cppreference.com/w/cpp/utility/pair/make_pair)

---
```cpp
#include <cstdio>
#include <map>
#include <functional>
typedef std::pair<char,char> pcc;
typedef std::map<pcc,int> mpcci;
int main(){
    int n,maxn=-1;
    char s[101],l,r;
	scanf("%d\n%s",&n,s);
	mpcci t;
	for(int i=1;i<n;++i) ++t[std::make_pair<char,char>((char)s[i-1],(char)s[i])];
	for(mpcci::iterator i=t.begin();i!=t.end();++i)
	    if((i->second)>maxn)
        //注意i是iterator，用法与指针相似，需用->first、->second
        //访问std::map中的两个元素时，直接.first、.second即可
	        l=(i->first).first,r=(i->first).second,maxn=i->second;
	printf("%c%c\n",l,r);
}
```

---
最后想说一句：$\LaTeX$的$\texttt{texttt}$太好啦！

---

## 作者：封禁用户 (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/977/B)

一道模拟题，然鹅我调了好久，是 set 的问题。

注：以下子串均指长度为 2 的子串
## 思路1
直接暴力，遇到每一个子串，都重新遍历一遍，判断与它相等的子串数量数量 cnt，再用 cnt 和已有的 max 比较，时间复杂度 $\mathcal O (n^2)$，由于字符串长度最长 100，此解能过得去。
(这里就不放代码了）

## 思路2
利用 [map](https://www.w3cschool.cn/cpp/cpp-fu8l2ppt.html) 和 [vector](https://www.w3cschool.cn/cpp/cpp-i6da2pq0.html) （数组也行），用 map 储存每个子串的数量，vector 储存每个子串，
```
vector<string> v;
map<string,int> mp;

```
然后再遍历字符串以获取每个子串以及和它相同的字串数量，

```
for(int i=0;i<n-1;i++){
   string x=str.substr(i,2);
   v.push_back(x);
   mp[x]++;
}
```

再通过 map 和 vector 算出每个子串（指一个子串及与它相等的子串）出现的数量即可。
```
 for(int i=0;i<n-1;i++){
   string x=v[i];
   if(mp[x]>mx)ans=v[i];
   mx=max(mx,mp[x]);
 }
    cout<<ans;
```
时间复杂度 $\mathcal O (n)$。

## 思路3
同思路2，将 vector 改为 set 去重，稍快一点，但时间复杂度没变，而且 set 容易写错，故不推荐。

### The end.

---

## 作者：UperFicial (赞：0)

# 看到楼下都是 $O(nlogn)$ 的，蒟蒻来篇 $O(n^2)$ 

### 题目大意

给定长度为 $n$ 的字符串 $S$，求出长度为 $2$ 且出现次数最多的一个子串。

**重点是数据范围：**$1\le n\le 100$。

### 解题思路

~~说句题外话：这道题感觉最多就是个红题~~

看到数据范围，这已经在预示着我们可以搞 $O(n^2)$ 的做法了！

所以不难发现，既然要寻找每个长度为 $2$ 的子串中出现次数最多的子串，那么便可以去枚举每一个长度为 $2$ 的子串，这就是一个 $O(n)$ 了，对于每个字串，再来在 $S$ 中找出出现次数，这又是一个 $O(n)$，对于每个出现次数若果比目前最大值更优，那么不单单要更新最大值，还要记录这个子串，所以总时间复杂度为 $O(n^2)$。

另外说明一点，记录子串的话可以不用记录 $char$ 类型或 $string$ 类型的子串，我们只要记录子串的第一个字符在 $S$ 中的位置就好，因为长度为 $2$ 的子串肯定是相邻的两个字符组合，记录第一个字符的位置即可。

### $Code:$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int MAXN=110;
int n,len,maxx,ans;
char s[MAXN];
int check(char x,char y)//查找在S中第一个字符为x，第二个字符为y的子串的个数 
{
	int tmp=0;
	for(register int i=0;i<len-1;i++)
		if(s[i]==x&&s[i+1]==y) tmp++;
	return tmp;
}
int main()
{
	n=read();
	scanf("%s",s);
	len=strlen(s);
	for(register int i=0;i<len-1;i++)
	{
		int tmp=check(s[i],s[i+1]);
		if(maxx<tmp) maxx=tmp,ans=i;//这里只记录位置即可 
	}
	printf("%c%c\n",s[ans],s[ans+1]);
	return 0;
}
```
$$\texttt{The End.by UF}$$

---

## 作者：Eason_AC (赞：0)

## Content
给定一个字符串 $s$，请求出出现次数最多的长度为 $2$ 的子串。

**数据范围：$2\leqslant |s|\leqslant 100$。**
## Solution
直接求出所有长度为 $2$ 的子串，然后比较它们出现的次数即可。统计次数这一块可以用 $\texttt{map}$ 直接映射来实现。
## Code
```cpp
int len, cnt, ans = 1;
string s, ss[107];
map<string, int> q;

int main() {
	getint(len);
	cin >> s;
	_for(i, 0, len - 2)
		ss[++cnt] += s[i], ss[cnt] += s[i + 1];
	_for(i, 1, cnt) {
		q[ss[i]]++;
		ans = max(ans, q[ss[i]]);
	}
	_for(i, 1, cnt)
		if(q[ss[i]] == ans) {cout << ss[i]; break;}
	return 0;
}
```

---

## 作者：Aehnuwx (赞：0)

话说这题就是暴力枚举orz

（好像那次比赛是div3）

就是要你求一个字符串内出现数量最多的两位子串，如果有多个就输出任意一个就行了。

说明中说了：

```
In the first example "BA" is also valid answer.
```

但是[@静静是我的，](https://www.luogu.org/space/show?uid=52012)在本题写的题解里说输出字典序最小的？题目里并没有说必须输出字典序最小的啊qwq。。希望[@静静是我的，](https://www.luogu.org/space/show?uid=52012)能够尽快更改一下，谢谢

既然是两位字串那不就可以暴力枚举了吗

直接上代码

$code$

```cpp
#include<cstdio>
#include<string>
#include<iostream> 
using namespace std; 
int main() {
    int n, maxs=0, x; //x在输出的时候有用，后面有解释
    scanf("%d", &n);
    char s[101]; //用string也行
    for(int i=1; i<=n; i++) cin>>s[i]; //把字符串输入进来
    for(int i=1; i<n; i++) { //注意不能枚举到n，只能枚举到n-1
    	//写了外层循环后就出来了一个两位子串：s[i]和s[i+1]
        int t=1; //统计有多少子串跟s[i]和s[i+1]这个子串一样，初始化为1
        for(int j=i+1; j<n; j++)
        	//这个内层循环又出来了一个两位子串：s[j]和s[j+1]
            if((s[i]-'0')==(s[j]-'0')&&(s[i+1]-'0')==(s[j+1]-'0')) t++; //如果两个两位子串完全相同，t自加1
        if(t>maxs) { //如果有更好的答案就更新答案
            maxs=t;
            x=i; //x把当前答案（两位子串）的第一位的编号保存了下来
        }
    }
    cout<<s[x]<<s[x+1]; //然后输出就行了
    return 0;
}
```

---

## 作者：静静是我的， (赞：0)

# 题意：找出最多出现的两位子串。
注意：如有数量相同，输出字典序最小的两位子串

------------
## 方案一：硬枚举

枚举的方法有2种，一是枚举子串。
```cpp
//手打程序没有把握
for (char i='A';i<='Z';i++)
for (char j='A';j<='Z';j++)   //进行枚举前一个和后一个的字母
{
	int ans=0;
	for (int k=1;k<st.size();k++)
    if (st[k]==j&&st[k-1]==i) ans++;    //通过一维枚举，枚举所拥有的个数
    if (Max<ans)     //注意：这里不要打‘<=’，因为就无法达到字典序小的输出
    {
    	Max=ans;   //覆盖
        c1=i;		//记录前一个。
        c2=j;		//记录后一个
	}
}
```
时间复杂最重要：26²*n=676*100=67600不超时

### 通过枚举子串来道出这里的个数，从而进行累加判断。

二是枚举字符串内的字符，
```cpp
for(int i=1;i<st.size();i++)   //枚举后一点
{
	int ans=0;
	for(int j=1;j<st.size();j++)     //通过一维枚举，枚举所拥有的个
    if (st[i-1]==st[j-1]&&st[i]==st[j]) ans++; //累加
    if (Max<ans)     //注意：这里不要打‘<=’，因为就无法达到字典序小的输出
    {
    	Max=ans;   //覆盖
        c1=i;		//记录前一个。
        c2=j;		//记录后一个
	}
}
```
时间复杂最重要：n²=100*100=10000不超时

### 通过枚举子串来道出这里的个数，从而进行累加判断。


------------
## 方案二：数组计数
把所有情况列入数组内，然后进行查找，输出。
```cpp
	for (int i=1;i<st.size();i++)	//枚举后一个点
	{
		a[st[i-1]-'A'][st[i]-'A']++;	//放入一个数组内
		Max=max(Max,a[st[i-1]-'A'][st[i]-'A']);		//找出最大的数值
	}
	for (int i=0;i<26;i++)
	for (int j=0;j<26;j++)      //已知最大值，用字典序查找
	if (a[i][j]==Max)
	{
		cout << (char)(i+'A')<<(char)(j+'A');输出
		return 0;
	}
```
时间复杂最重要：n+26²=100+676=776(其实在第一循环优化中加入计算字符可以把时间复杂度降低为100)


# **反思：全把大写写成小写，请大家注意一下**

---

