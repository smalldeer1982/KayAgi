# Boy or Girl

## 题目描述

Those days, many boys use beautiful girls' photos as avatars in forums. So it is pretty hard to tell the gender of a user at the first glance. Last year, our hero went to a forum and had a nice chat with a beauty (he thought so). After that they talked very often and eventually they became a couple in the network.

But yesterday, he came to see "her" in the real world and found out "she" is actually a very strong man! Our hero is very sad and he is too tired to love again now. So he came up with a way to recognize users' genders by their user names.

This is his method: if the number of distinct characters in one's user name is odd, then he is a male, otherwise she is a female. You are given the string that denotes the user name, please help our hero to determine the gender of this user by his method.

## 说明/提示

For the first example. There are 6 distinct characters in "wjmzbmr". These characters are: "w", "j", "m", "z", "b", "r". So wjmzbmr is a female and you should print "CHAT WITH HER!".

## 样例 #1

### 输入

```
wjmzbmr
```

### 输出

```
CHAT WITH HER!
```

## 样例 #2

### 输入

```
xiaodao
```

### 输出

```
IGNORE HIM!
```

## 样例 #3

### 输入

```
sevenkplus
```

### 输出

```
CHAT WITH HER!
```

# 题解

## 作者：boshi1 (赞：11)

洛谷新晋蒟蒻一枚

第一次发题解，大佬勿喷

### 还是python代码简洁

```python
s=len(set(input()))         #去重来算出不同的字母
if s%2==0:                  #判断奇数偶数
    print('CHAT WITH HER!') #输出Yes
else:
    print('IGNORE HIM!')    #输出No
```

---

## 作者：Level_Down (赞：5)

这道题很水，我就来讲一个新方法。

首先我们开一个桶记录每个字母的出现次数：

```
int a[27]；
```
然后就是最重要的部分了：

```
char s;
while (cin >> s)
	{
		a[s-96]++;
	}
```

这里我用了一个字符的妙用，由于输入的都是小写字母，

asall值从97开始增加，于是才有了这种写法。

存完后，只需要将a数组扫一遍即可。

奉上AC代码：

```
#include <bits/stdc++.h>
using namespace std;
int a[27],ans;
int main()
{
	char s;
	while (cin >> s)
		{
			a[s-96]++;//如上
		}
	for (int i = 1; i <= 26; i++)
		{
			if (a[i] != 0) ans++;//扫描a数组
			}	
	if (ans % 2 == 0) cout << "CHAT WITH HER!";
		else cout << "IGNORE HIM!";//最后的判断		
	return 0;//完美结束
 } 

```

可能我的方法不是最佳解法，但应该是最容易懂的。

---

## 作者：一滴小水滴 (赞：2)

## ~~这道题实在是太水了！！！~~
***
### 思路：定义一个bool变量，来记录字母是不是被判过。直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int tot=0;   //tot记录不同字符的个数。
bool t[255];   //t记录字符是不是被记录过。
int main()
{
	memset(t,0,sizeof(t));   //先将t全部初始化为false。
	getline(cin,s);
	for(int i=0;i<s.size();i++)
	{
		if(!t[(int)s[i]])
		{
			tot++;
			t[(int)s[i]]=1;
		}   //如果这个字符以前没有出现过，tot自增，
                           //并把这个字符的相应位置改为true。
	}
	if(tot%2)cout<<"IGNORE HIM!"<<endl;
	else cout<<"CHAT WITH HER!"<<endl;
    		//输出tot相对应的答案（注意：全部都是大写）。
	return 0;
}
```
***
## 珍爱生命，远离抄袭，蟹蟹

---

## 作者：CZQ_King (赞：1)

这里提供两种新方法

1. $sort+if$

因为在排序后相同的字符会在一起，那么当$for$扫过去时，只统计最后一个字母即可

例如一个字符串后排序为``122233``，那么只统计``1``22``2``3``3``。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l;
int main(){
	cin>>s;
	sort(s.begin(),s.end());//排序
	for(int i=1;i<s.size();i++)if(s[i]!=s[i-1])l++;//只统计最后一个
	puts(l&1?"CHAT WITH HER!":"IGNORE HIM!");//判断是奇数还是偶数
}
```

2. ``STL``大法好！

看到有个大佬也是用的``STL-set``，~~我从来不用什么``set``~~，这里用的是``sort+erase+unique``。

``sort``和``erase``相信大家是十分了解，唯独``unique``不了解，这里讲一下：

``unique(s.begin(),s.end())``在字符串中寻找相邻并相同的字符“删掉”，但并不是真正的删掉，而是将后面的字符串往前移而覆盖，例如
```
s="ass we can";
unique(s.begin(),s.end());
cout<<s;
```
最后输出的是``as we cann``，也就是说：把``s we can``往前移了一格，但最后面``can``的``n``并没有清除。

但是，``unique``是有返回值的，它返回的是后面没有删除的那部分的开头，如上面就是返回``cann``的第二个``n``的位置，那么我们可以用``erase``函数删除后面的部分，于是``s.erase(unique(s.begin(),s.end()),s.end());``这条语句可以删除多余的字符，一般给字符串去重也可以用这种方法。

代码：
```
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin>>s;
	sort(s.begin(),s.end());//记得要先排序
	s.erase(unique(s.begin(),s.end()),s.end());
	puts(s.size()&1?"IGNORE HIM!":"CHAT WITH HER!");//判断去重后长度是奇数还是偶数
}
```

---

## 作者：Sophon (赞：1)

好像没有STL的，水一波
```cpp  
#include <bits/stdc++.h>
using namespace std;

int main()
{
	set<char> uni;//存不同单词，set自动去重排序
	string s;
	cin>>s;
	
	for(string::size_type t=0;t<s.size();t++)//string::size_type强迫症去除warning
	{
		uni.insert(s[t]);//插入
	}
	
	if(uni.size()&1)//奇数
	{
		cout<<"IGNORE HIM!"<<endl;
	}
	else
	{
		cout<<"CHAT WITH HER!"<<endl;
	}
}
```

---

## 作者：pigstd (赞：1)

****思路：利用桶排的思想，在一个数组a中把每种字符的个数记录下来，然后寻找即可****

c++代码如下:

```
#include<bits/stdc++.h>
using namespace std;

char s[105];
int sum;
int a[150];//桶

int main()
{
	cin>>s;
	int len=strlen(s);//计算长度
	for (int i=0;i<len;i++)
		a[s[i]]++;//记录次数
	for (int i=0;i<=127;i++)
		if (a[i]!=0)
			sum++;//寻找
	if (sum%2==0)
		cout<<"CHAT WITH HER!";
	else
		cout<<"IGNORE HIM!";
	return 0;
}
```

求通过

---

## 作者：dl__hh6 (赞：0)

~~蒟蒻又来发题解了~~

**题意大概**：其实就是判断字符串中有多少没有重复的字符而已；

**小结：**~~一道模拟题而已~~；**只要用一个计数器来记下来；在判断有没有重复的，最后在输出时判断即可。**



~~详见代码注释~~


 # _代码：_ 
 ```pascal
var//定义
  s,ch:string;//s代表输入的字符串，ch表示正在循环到的
  字符；
  i,j,max:longint;//max计数器
  a:array[1..100000]of string;//a数组来存储已经循环到
  的字符；
begin
   read(s);//读入
    for i:=1 to length(s) do begin//将每一个字符都循环
    一遍；
     inc(max);//先+1再说
    ch:=copy(s,i,1);//将这个字符存入到ch和a数组中
   a[i]:=ch;
  for j:=i-1 downto 1 do //找在之前记下来的字符中又没
  重复的；
 if a[j]=ch then begin dec(max);有重复的就减去之前加的
 break;
end;
end;
  if max mod 2=0 then //判断是几是偶；
   write('CHAT WITH HER!')
 else write('IGNORE HIM!');
end.//完工
```
~~杜绝抄袭~~
 

---

## 作者：LW_h_FP (赞：0)

题目大意：读入一个名字（字符串），如果名字中不同的字母数量为奇数，这个人就是女的

这题的重点在于“不同”，就是说主要就是去重复，这里用map，其实我也不太会用，反正有这个功能吧

去完重复就可以看剩下的字母数量是不是奇数了

```
#include<iostream>
#include<cstring>
#include<map>
using namespace std;

char a[1010];
map<char,bool> b;
int ans,al;

int main(){
	cin>>a; al=strlen(a);
	for(int i=0;i<al;i++)
		if(b[a[i]]==0){   //判断map中是否为0,0即没出现过
			b[a[i]]=1;    //设为1，即出现过
			ans++;
		}
	if(ans%2==0) cout<<"CHAT WITH HER!"<<endl;
	else cout<<"IGNORE HIM!"<<endl;
	return 0;
}
```

当然如果这个人的名字非常，又不想浪费内存就可以改改主要的部分


```
	char a;
	while(cin>>a)   //一次读入一个
		if(b[a]==0){
			b[a]=1;
			ans++;
		}
```

这里有有必要说一下了，在窗口中while(cin>>a)不知道你什么时候结束，就没办法测试数据（当然可以用文件读入，只不过有点麻烦），不过在窗口中输入Ctrl+z就结束了


不会用map的话还有一种方法，只不过比较浪费时间和内存（不推荐）


```
	char a;
	char b[1010];   //用数组b记录没出现过的
	int ans,bl;
	bool ok=1;
	while(cin>>a){
		for(int i=0;i<bl;i++)
			if(b[i]==a) ok=0;
		if(ok){
			b[bl++]=a;
			ans++;
		}
		else ok=1;
	}
```

---

