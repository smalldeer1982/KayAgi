# Diversity

## 题目描述

Calculate the minimum number of characters you need to change in the string $ s $ , so that it contains at least $ k $ different letters, or print that it is impossible.

String $ s $ consists only of lowercase Latin letters, and it is allowed to change characters only to lowercase Latin letters too.

## 说明/提示

In the first test case string contains $ 6 $ different letters, so we don't need to change anything.

In the second test case string contains $ 4 $ different letters: $ {'a','h','o','y'} $ . To get $ 5 $ different letters it is necessary to change one occurrence of $ 'o' $ to some letter, which doesn't occur in the string, for example, $ {'b'} $ .

In the third test case, it is impossible to make $ 7 $ different letters because the length of the string is $ 6 $ .

## 样例 #1

### 输入

```
yandex
6
```

### 输出

```
0
```

## 样例 #2

### 输入

```
yahoo
5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
google
7
```

### 输出

```
impossible
```

# 题解

## 作者：cq_loves_Capoo (赞：4)

这题应该不算很难的，做法显然，数据不强，做法大致如下：     
>先输入字符串 $st$ 和一个整数 $k$ 。      
>    
>接着判断字符串 $st$ 的长度是否小于 $k$ ，如果小于，就输出 $impossible$ ，并退出程序。  
>         
>下一步就是程序的关键了，从 $0$ 开始循环到字符串 $st$ 的长度，用数组计数记住每个字符出现的数量。   
>          
>然后就从字符 $a$ 循环到字符 $z$ ，如果该字符的出现次数大于 $0$ ，则累加不同的字符数量。    
>     
>最后输出n-不同字符的出现数量。   
>         
>**记住：如果答案出现负数要输出0**    
     
贴 $AC$ 代码：    
``` 
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n,ans,x[256];/*定义变量*/ string st;/*定义字符串*/
int main()
{
	ios::sync_with_stdio(false);//令cin和cout达到scanf和printf的速度 
	cin>>st>>n;//输入字符串和整数 
	if(n>st.length())//判断字符串长度是否小于k 
	{
		cout<<"impossible";//输出impossible 
		return 0;
	}
	for(int i=0;i<st.length();i++) //循环 
	{
		x[st[i]]++;//累加不同字符串出现数量 
	}
	for(int i='a';i<='z';i++) //从字符a循环到字符z 
	{
		if(x[i]>0) //如果出现次数大于0则累加 
			ans++;
	}
	cout<<max(0,n-ans);//输出，并且特判负数的情况 
	return 0;//要养成好习惯 
}
```

---

## 作者：lukelin (赞：4)

很简单，判断这个字符串有多少个不同的字符，让后用k减一减  
注意：  
1、如果不同字符数大于k，不要输出负数  
2、变量名别打错

上代码

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#define ll long long

using namespace std;

string s;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int vis[26];

int main(){
    while (cin >> s){
        memset(vis, 0, sizeof(vis));
        int k, s_l = s.length(), cnt = 0, cnt2 = 0;
        cin >> k;
        if (k > s_l || k > 26)
            printf("impossible\n");
        else{
            for (int i = 0; i < s_l; ++i){
                if (s[i] < 'a' || s[i] > 'z')
                    continue;
                if (!vis[s[i] - 'a']){
                    vis[s[i] - 'a'] = 1;
                    ++cnt;
                }
            }
            printf("%d\n", (k - cnt) < 0 ? 0 : (k - cnt));
        }
    }
    return 0;
}
```

---

## 作者：CZQ_King (赞：1)

``STL``大法好！

------------
思路：

1. 如果整个字符串的长度还没有$n$大，那么这是不可能的事，因此输出``impossible``。（因为不能加字符只能改变）
2. 首先删去重复的字符，然后：
    - 如果此时字符串的长度大于$n$，那么直接输出$0$，因为不需要更改。
    - 如果此时字符串的长度小于$n$，那么输出$n-s.size()$，即代表还需要更改几个。

而这些操作几乎都用了``STL``完成，先看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int main(){
	cin>>s>>n;
	if(n>s.size()){puts("impossible");return 0;}//不可能
	sort(s.begin(),s.end());//排序
	s.erase(unique(s.begin(),s.end()),s.end());//去重复
	if(s.size()>n)puts("0");//不需要更改
	else cout<<n-s.size();//需要更改
}
```

这里解释一下``unique``：

``unique(s.begin(),s.end())``在字符串中寻找相邻并相同的字符“删掉”，但并不是真正的删掉，而是将后面的字符串往前移而覆盖，例如
```
s="ass we can";
unique(s.begin(),s.end());
cout<<s;
```
最后输出的是``as we cann``，也就是说：把``s we can``往前移了一格，但最后面``can``的``n``并没有清除。

但是，``unique``是有返回值的，它返回的是后面没有删除的那部分的开头，如上面就是返回``cann``的第二个``n``的位置，那么我们可以用``erase``函数删除后面的部分，于是就有了这条语句``s.erase(unique(s.begin(),s.end()),s.end());``

---

## 作者：DPair (赞：1)

## 这道题不难吧……还是比较好想的，要~~熟练~~运用$bool$数组

由于要使字符串中不同字母数个数达到$k$，那么只用特判一下字符串长度是不是没有$k$大（输出$impossible$），否则一定可行。

然后记录现在字符串中有几种不同的字符（$bool$数组判断不解释），再看一下还需要处理几次就好了。

### 注意：如果现在的不同字符数已经够大，输出$0$而非负数。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

bool c[256];
string s;
int ans, k;//ans记录不同字母数
inline int __fix(int x)//处理小于零的情况
{
    return (x < 0)? 0:x;
}
int main()
{
    cin >> s;
    cin >> k;
    if(k > s.size()){printf("impossible");return 0;}//特判
    for (register int i = 0;i < s.size();i ++)
    {
        if(!c[s[i]]) ans ++, c[s[i]] = true;//直接简单bool判断
    }
    printf("%d\n", __fix(k - ans));//处理小于零的情况，输出即可。
}

```

---

## 作者：cz666 (赞：0)

主观感觉这道题的题面翻译并不怎么好理解，~~或许这就是这道题被评为紫题的原因吧...~~，所以我给出了我认为比较好理解的题面翻译：

### 题面理解：

1. 先给你了一个由 $ a $ ~ $ z $ 26个字符构成的字符串 $ s $ ，让你找出这个字符串里有多少个不重复的字符（说白了就是把重复字符去掉，剩下的字符串长度）。

2. 然后第二行给了你一个正整数 $ k $ ，让你比较 $ (1) $ 中得到的不重复字符个数是否大于 $ k $ ，如果这个字符串中不重复字符数量小于 $ k $ ，那最少需要对这个字符串操作多少步（每步只能改变一个字符）使这个字符串中不重复字符数量达到要求的 $ k $ ，如果无法达到 $ k $ 的要求，就输出 $ impossible $ 。

Hint： $ k $ 的取值范围在 $ 1 $ ~ $ 26 $ 之间（包括两个端点），字符串 $ s $ 的长度在 $ 1 $ ~ $ 1000 $ 之间（也包括了两个端点）。

### 思路：

~~我一看，两军阵前...~~（还是认真点，不调侃了...）

我们认真审视题面，就会发现下面的几个基本事实：

1. 如果字符串 $ s $ 的长度比 $ k $ 小，那样无论如何都不可能做到不重复字符数量到达 $ k $ ，所以可以直接输出 $ impossible $ 。

2. 如果这个字符串 $ s $ 的不重复字符个数大于等于 $ k $ 时，里不重复字符的数量已经大于等于 $ k $ 了，那就可以直接输出 $ 0 $ 。

3. 剩下的情况输出 $ k-sum $ （ $ sum $ 是字符串 $ s $ 中的不重复字符数量）。

所以...

~~紫题居然可以模拟一下就通过了？！~~

不管了，先试一试再说：

1. 首先，我们先按照思路判断字符串 $ s $ 的长度是否小于 $ k $ ，解决掉特判部分。

2. 然后，我们按照题意找出字符串 $ s $ 里面的不重复字符个数 $ sum $ ，算好之后也不需要判断，直接输出 $ max(k-sum,0) $ 就可以了。

   （因为当这个字符串 $ s $ 的不重复字符个数大于等于 $ k $ 时， $ k-sum $ 小于等于 $ 0 $ ，而本来这个时候我们只要输出 $ 0 $ 就可以了，所以不用判断，直接写 $ max(k-sum,0) $ 作为输出部分就可以了，也不会影响 $ k-sum $ 大于 $ 0 $ 的那一部分答案。）

### 下面贴上我的AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
//开long long纯属手残，大佬别介意
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);puts("");}
inline void wlk(int x){write(x);printf(" ");}
#undef dd
//美妙的快读QwQ
string s;
signed main(){
	cin>>s;
  //读入该字符串
	int n=read(),a[27],sum=0;
  //读入n以及初始化sum
	for (register int i=1;i<=26;i++) a[i]=0;
  //初始化桶数组，防止WA掉
	if (s.length()<n) return printf("impossible\n"),0;
  //特判当n大于s.length()时，输出impossible
	for (register int i=0;i<s.length();i++)
	 if (!a[s[i]-'a'+1]) sum++,a[s[i]-'a'+1]++;
  //寻找字符串s里面有多少个不重复字符
	wln(max(n-sum,0ll));
  //输出部分（对于我的手残代码，max里不可以直接写0，要写0ll，这个要引起注意，max中的数据类型必须是一一对应的，不然会爆编译）
   return 0;//完美地结束程序
}
```

[我的AC记录](https://www.luogu.org/recordnew/show/18139624)

---

## 作者：defense (赞：0)

emmmmm.....

------------------以上为吐槽内容-----------------------------------------
#### 进入正题：
给出一个字符串S与一个整数k。

你可以更改S中的任意字符，使得字符串S中有不小于k个不同的字符。

求最少的更改次数。
#### 变成人话就是：
求出字符串S中不同字符的个数，最后用k减。
#### 相信各位大佬已完全明白,so,不再赘述解题思路与过程。

#### 不过，这篇题解介绍一个东西。
## Map。
说白了是一个下标可以为任意类型的数组。
可用于映射。
#### 具体见代码：

```
#include<bits/stdc++.h>
using namespace std;
map<char,bool>str;
int k,ans=0;
int main(){
	string a;
	getline(cin,a);
	scanf("%d",&k);
	if(k>a.length()){
	    printf("impossible");return 0;
	}
    for(register int i=0;i<a.length();i++){
   	    if(!str[a[i]])ans++;
        str[a[i]]=1;
    }
    if(k<ans){
    	printf("0");
    	return 0;
	}
	printf("%d",k-ans);
	return 0;
}
```
AC





---

## 作者：RainFestival (赞：0)

这是紫题  ？×10^666，好简单

也许有些人恶意评分，我觉得橙题难度差不多啦

开桶保存各个字符

只有一种情况会输出impossible，length(st)<t

其他情况输出t-字符种数就可以啦

要注意当字符种数>=t时输出0

下面是代码：
```pascal
var
  st:ansistring;
  a:array[0..505] of boolean;
  i,p,k:longint;
begin
  readln(st);
  readln(k);
  if k>length(st) then
    begin
      writeln('impossible');
      halt;
    end;
  for i:=1 to length(st) do
    if not a[ord(st[i])] then
    begin
      a[ord(st[i])]:=true;
      inc(p);
    end;
  if k-p>0 then
  writeln(k-p)
  else writeln(0);
end.
```
时间559ms,空间 532KB，代码长度0.35KB

谢谢大家观赏


---

## 作者：CobaltChloride (赞：0)

```
太水了!!!
#include<bits/stdc++.h>
using namespace std;
long long k,n,difnum,i;
int a[27];
string s;
int main(){
    cin>>s>>k;
    if(k>s.length()){
    	puts("impossible");
    	return 0;
	}//显然当s的长度小于k时不可能 
    for(i=0;i<s.length();i++){
    	if(!a[s[i]-96]) difnum++;
    	a[s[i]-96]=1;
	}//求不同字母个数 
	if(k<=difnum) cout<<0;
	else cout<<k-difnum;
	//输出 
	return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

显然当长度小于k时不可能，否则只需统计出出现了多少字符再与k相减即可

代码：
```
var s:ansistring;
    a:array ['a'..'z'] of longint;
    i,k,ans:longint;
begin
  readln(s);
  read(k);
  if length(s)<k then writeln('impossible')//特判
  else begin
    for i:=1 to length(s) do if a[s[i]]=0 then a[s[i]]:=1 else inc(ans);//统计出现字母个数
    ans:=length(s)-ans;
    if ans>=k then writeln('0') else writeln(k-ans);//判断
  end;
end.
```

---

## 作者：lhjy666 (赞：0)

### 其实这道题就是考判断
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char a[1010];
int m[1010]={0};//清0很重要，虽然好像不用
int main()
{
	int x,f=0;
	int n;
	gets(a);//直接读入一行当然用scanf("%s",a);也可以
	scanf("%d",&n);
	int l=strlen(a);
	if(n>l)//如果n>l就肯定不行
	{
		printf("impossible");
		return 0;
	}
	for (int i=0;i<l;i++)
	{
		x=a[i]-'a'+1;
		m[x]=1;
	}
	for (int i=0;i<=1000;i++)//虽然不用1000只要200就够了但担心有别的字符
	{
		if(m[i]!=0)
		{
			f++;
		} 
	}
	int w=n-f;
	if(w>=0)
		printf("%d",n-f);
	if(w<0)
		printf("0");
}
```

---

