# Strings of Power

## 题目描述

Volodya likes listening to heavy metal and (occasionally) reading. No wonder Volodya is especially interested in texts concerning his favourite music style.

Volodya calls a string powerful if it starts with "heavy" and ends with "metal". Finding all powerful substrings (by substring Volodya means a subsequence of consecutive characters in a string) in a given text makes our hero especially joyful. Recently he felt an enormous fit of energy while reading a certain text. So Volodya decided to count all powerful substrings in this text and brag about it all day long. Help him in this difficult task. Two substrings are considered different if they appear at the different positions in the text.

For simplicity, let us assume that Volodya's text can be represented as a single string.

## 说明/提示

In the first sample the string "heavymetalisheavymetal" contains powerful substring "heavymetal" twice, also the whole string "heavymetalisheavymetal" is certainly powerful.

In the second sample the string "heavymetalismetal" contains two powerful substrings: "heavymetal" and "heavymetalismetal".

## 样例 #1

### 输入

```
heavymetalisheavymetal
```

### 输出

```
3```

## 样例 #2

### 输入

```
heavymetalismetal
```

### 输出

```
2```

## 样例 #3

### 输入

```
trueheavymetalissotruewellitisalsosoheavythatyoucanalmostfeeltheweightofmetalonyou
```

### 输出

```
3```

# 题解

## 作者：_tommysun_ (赞：2)

**思路**

本题直接用暴力肯定会T。

由于一串强字符需要以$heavy$开头，因此只需要计算$heavy$的数量，之后遇见$metal$就加上之前$heavy$的数量就可以了。

-----------------

本题截取字串可以用c++自带的substr函数，格式如下（a是原来的字符串，i是需要开始截取字串的下标，5是需要截取的字串的长度。）

``a.substr(i,5)``

**代码：**

```
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	string s,sub;
	int ans=0,heavy=0;
	cin>>s;
	for (int i=0;i+4<s.size();i++) 
	{
		sub=s.substr(i,5); //截取字串 
		if (sub=="heavy") //如果发现了heavy，计数器就加一。 
		{
			heavy++;
		}
		if (sub=="metal")
		{
			ans+=heavy; //只要有metal，就加上之前heavy的数量。即使之前没有heavy也没关系，计数器的初始状态为0。 
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：_Jonny_404 (赞：1)

本来是这么想的：先找出 `heavy` 的个数，再找出 `metal` 的个数，然后因为每个 `heavy` 都可以匹配一个 `metal` ，所以再乘起来就好了。

代码：
```cpp
#include<string>
#include<iostream>
using namespace std;

string s;
long long ans1,ans2;

int main()
{
	cin>>s;int len=s.size();
	for(int i=0;i<len;i++)
		if(s[i]=='h'&&s[i+1]=='e'&&s[i+2]=='a'&&s[i+3]=='v'&&s[i+4]=='y')//找到了"heavy"
			ans1++;
		else if(s[i]=='m'&&s[i+1]=='e'&&s[i+2]=='t'&&s[i+3]=='a'&&s[i+4]=='l')//找到了"metal" 
			ans2++;
	cout<<ans1*ans2<<endl; 
	return 0;
} 
```

但结果是样例 $1$ 就错了。

我们来分析一下为什么：

输入 $1$  
```
heavymetalisheavymetal
```
结果明显是 $3$，但上面代码运行后输出了 $4$，答案错误。

不难发现，有一个 `metal` 在另外一个 `heavy` 的前面，因此这两个单词无法组成“强字串”。所以需要换一种思路。

再来思考一下，可以发现，只要增加一个 `metal`，那么所有**在它前面**的 `heavy` 都可以与它匹配。这时只需要从前往后枚举，用 $ans1$ 记录到当前找到了的 `heavy` 的数量，每当找到一个 `metal`，就让 $ans2$ 加上 `heavy` 的数量也就是 $ans1$，这时就使这之前的所有 `heavy` 和这个 `metal` 进行了匹配，最后输出 $ans2$ 就行了。

AC 代码：

```cpp
#include<string>
#include<iostream>
using namespace std;

string s;
long long ans1,ans2;

int main()
{
	cin>>s;int len=s.size();
	for(int i=0;i<len;i++)
		if(s[i]=='h'&&s[i+1]=='e'&&s[i+2]=='a'&&s[i+3]=='v'&&s[i+4]=='y')//找到了"heavy"
			ans1++;
		else if(s[i]=='m'&&s[i+1]=='e'&&s[i+2]=='t'&&s[i+3]=='a'&&s[i+4]=='l')//找到了"metal" 
			ans2+=ans1;
	cout<<ans2<<endl; 
	return 0;
} 
```

---

## 作者：Zaku (赞：0)

### 温馨提示：
本题解极为新手向，请放心食用。此题是练习字符串操作的基础题，只有红题难度，请勿想复杂。

### 前置芝士：
知周所众，C++中有一个神器：STL。我们可以用STL中的```substr```来极为快捷地完成此题。它能够完成字符串的截取工作，格式如下:

 ```substr(string s,int start,int length);```
 
其中 $s$ 为需要截取的字符串，$start$ 为开始截取的位置，$length$ 为截取的长度。

**注意，如果不写截取长度，视为从第 $start$ 个字符开始截取后面所有的字符串；当 $start$ 等于0或1时，都视为从第一位开始截取。**

### 解题方法：
遍历读入的字符串，如果遇到“metal”，总子串数加上前面“heavy”的总数，每一个“heavy”代表一个不同强子字符串。
### 代码：
其实很简单，这里只放关键部分：
```cpp
string s,s1;cin>>s;
long long cnt=0,ans=0;//cnt计算heavy个数，ans计算子串总数
for(long long i=0;i<=s.size()-5;i++){
	s1=s.substr(i,5);//从i开始，截取长度为5的子串
	if(s1=="heavy")cnt++;//遇到“heavy”，计数器+1
	if(s1=="metal")ans+=cnt;//遇到“metal”，把前面“heavy”的数量加起来
}
cout<<ans;
```
### 警钟长鸣：不开```long long```见祖宗！

---

## 作者：dead_X (赞：0)

## 前言
随机跳题，发现没有题解，水之保咕值
## 思路
显然一个符合要求的字符串应该是 ``"heavy...metal"`` 的形式。

于是我们固定右端点，即对于每个 ``"metal"`` 考虑答案。

显然这个 ``"metal"`` 前面的任何 ``"heavy"`` 都是合法的，所以直接从左往右搜索一遍，记录之前 ``"heavy"`` 的个数即可。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
char ch[1000003];
bool f1(int x)
{
	if(ch[x-4]=='h'&&ch[x-3]=='e'&&ch[x-2]=='a'&&ch[x-1]=='v'&&ch[x]=='y') return 1;
	return 0;
}
bool f2(int x)
{
	if(ch[x-4]=='m'&&ch[x-3]=='e'&&ch[x-2]=='t'&&ch[x-1]=='a'&&ch[x]=='l') return 1;
	return 0;
}
int main(){
	scanf("%s",ch+1);
	int n=strlen(ch+1),cnt=0;
	long long ans=0;
	for(int i=5; i<=n; i++) if(f1(i)) ++cnt; else if(f2(i)) ans+=cnt;
	printf("%lld\n",ans);
	return 0;
} 
```

---

