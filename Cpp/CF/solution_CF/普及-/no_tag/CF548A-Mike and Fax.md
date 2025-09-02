# Mike and Fax

## 题目描述

While Mike was walking in the subway, all the stuff in his back-bag dropped on the ground. There were several fax messages among them. He concatenated these strings in some order and now he has string $ s $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF548A/8e6eb6a5966077211062d31ebdd4df5e9f389a77.png)He is not sure if this is his own back-bag or someone else's. He remembered that there were exactly $ k $ messages in his own bag, each was a palindrome string and all those strings had the same length.

He asked you to help him and tell him if he has worn his own back-bag. Check if the given string $ s $ is a concatenation of $ k $ palindromes of the same length.

## 说明/提示

Palindrome is a string reading the same forward and backward.

In the second sample, the faxes in his back-bag can be "saddas" and "tavvat".

## 样例 #1

### 输入

```
saba
2
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
saddastavvat
2
```

### 输出

```
YES
```

# 题解

## 作者：Wendy_Hello_qwq (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF548A)
##  一、题目大意
给定一个字符串，给定一个整数 $k$ 。

求这个字符串是否能被平分成 $k$ 等份，并且每一份都是回文字符串，而且每份的长度相同。能的话输出 `YES`，不能的话输出 `NO`。

## 二、主题思路
- **首先**，要先判断这个字符串能不能被 $k$ 整除(也就是能不能被平均分成 $k$ 等份)，如果不能，那么直接输出 `NO` 就好了。  
- **其次**，用一个变量 $len$ 来保存每段的长度，由于可以平均分，直接用长度除以 $k$ 即可得到 $len$。  
- **接下来**，用一个函数 `substr(start,len)` 来提取每一段的字符串，这个函数表示从 $start$ 的位置开始取，取长度为 $len$ 的字符串。  
- **然后**，取出字符串后，用一个判断是否回文的函数判断字符串即可。  
## 三、上代码
```cpp
#include <cstring>
#include <iostream>
using namespace std;
string s1;
int k, len, f;
// 判断回文字符串的函数。 
bool hw (string);
int main()
{
	cin >> s1 >> k;
	// 由于分成同等份，如果字符串的长度不能被平均分成 k 份，那么一定不符合规则，直接输出 NO。
	if (s1.size() % k != 0)
	{
		cout << "NO";
		return 0;
	}
	// 其中的一份字符串的长度就是整个字符串的长度除以 k。 
	len = s1.size() / k;
	// 循环整个字符串，每次加同等份。 
	for (int i = 0; i <= s1.size(); i += len)
	{
		// 复制字符串的函数，变量. substr(start, len) 表示从 start。的位置开始复制，复制 len 位。 
		string str = s1.substr(i, len);
		// 如果不是回文字符串。 
		if (hw (str) == false)
		{
			// 输出 NO，结束。 
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
// 简单的判断回文字符串的函数。 
bool hw (string s2)
{
	for (int i = 0; i < s2.size(); i++)
	{
		if (s2[i] != s2[s2.size() - i - 1])
			return false;
	}
	return true;
}
```
完结撒花！

---

## 作者：lichenzhen (赞：8)

## 题目大意
就是判断一个字符串是不是恰好存在 $k$ 个子字符串是回文串，并且所有子字符串的长度要一样长。

## 题目解法
一道比较简单的字符串的题目，根据题意模拟即可。

我们把字符串的长度定义为 $len$。

首先，判断字符的长度能否被 $k$ 整除，如果字符串长度不能被 $k$ 整除，则不可能存在 $k$ 个子字符串一样长，此时输出`NO`即可。

如果字符串长度可以被 $k$ 整除，检查子字符串是否都是回文（这里可以把判断是否回文写成一个函数）。

如何找到每一个子字符串并判断呢？我们定义一个变量为 $subLen$，存储 $len \div k$，这就是每个子字符串的长度。之后循环扫每个子字符串，每轮循环将循环变量增加 $subLen$。

每个子字符串如何单独拿出来？这里我用了一个函数`substr()`主要功能是复制子字符串，要求从指定位置开始，并具有指定的长度。

### 参考代码

```cpp
#include <string>
#include <iostream>
using namespace std;
//判断字符串是否是回文的函数 
bool isPalindrome(string s1)
{
    int len=s1.size();
    for(int i=0;i<len/2;i++)
        if (s1[i]!=s1[len-1-i])
            return false;
    return true;
}
string s;
int main()
{
    int k;
    cin>>s>>k; 
    int len=s.size();//求字符串 s 的长度 
    if(len%k!=0){//判断字符的长度能否被 k 整除
    	cout<<"NO";
    	return 0;
	}
    //检查子字符串是否都是回文
    int subLen=len/k;
    bool allPalindrome=true;  //标记是否所有子字符串都是回文
    for(int i=0;i<len;i+=subLen)
	{
        string subs=s.substr(i,subLen);//将子字符串提取出来
		if(!isPalindrome(subs))//判断子字符串是否回文,如果不是标记一下，跳出循环 
		{
            allPalindrome=false;
            break;
        }
    }
    cout<<((allPalindrome)?"YES":"NO");
    return 0;
}
```


---

## 作者：qusia_MC (赞：2)

不多废话，直接开始。
# 分析
一个字符串 $s$ 是不是由 $k$ 个长度相等的回文字符串组成。
# 思路
很水，直接模拟。以下设 $size$ 为 $s$ 的长度。

有以下几点要注意：

- 如果非 $k\mid siz e$ 则无解。

- 判断时注意回文字符串判法。

# code
```
#include<bits/stdc++.h>
using namespace std;
bool ifhw(string l)
{
    for(int i=0;i<ceil(1.0*l.size()/2);i++)//一半就够了
    {
        if(l[i]!=l[l.size()-i-1])return 0;//前后字符不一样，也可以双指针
    }
    return 1;
}
int main()
{
    string s;int k;
    cin>>s;
    cin>>k;//输入
    int size=s.size();
    if(size%k!=0)//不能整除，就分不了
    {
        cout<<"NO";return 0;
    }
        k=size/k;
        for(int i=0;i<size;i+=k)
        {
            string m=s.substr(i,k);//提取出字串
            if(!ifhw(m))//不是回文直接输出不行
            {
                 cout<<"NO";
                 return 0;
            }
        }
    cout<<"YES";//重重考验都通过就行了
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## Description

给你一个字符串 $s$，问是否满足将 $s$ 分成 $k$ 等份后，每份都是回文串。若满足，输出 `YES`，否则输出 `NO`。

## Solution

如果 $s$ 的长度不能被 $k$ 整除，肯定无法分成 $k$ 等份，直接输出 `NO`。

然后模拟，把 $s$ 分成 $k$ 等份，依次判断每一份是不是回文串，只要有任意一份不是回文串，直接输出 `NO`，否则输出 `YES`。提取每一小份的字符串可以用 `substr` 函数，用法很简单，如下，`s.substr(pos,n)` 代表获取字符串 $s$ 从第 $pos$ 位开始，长度为 $n$ 的字符串。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int k;
bool judge(string s){//判断回文串
	for(int i=0;i<s.size();i++){
		if(s[i]!=s[s.size()-i-1])
			return 0;
	}
	return 1;
}
signed main(){
	cin>>s>>k;
	if(s.size()%k!=0){//无法k等分
		cout<<"NO";
		return 0;
	}
	int len=s.size()/k;//len表示每一小份的长度
	for(int i=0;i<s.size();i+=len){//枚举每一小份的起点
		string t=s.substr(i,len);//提取
		if(!judge(t)){//这一份不是回文串
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF548A)

这道题是要我们判断一个字符串是否能刚好按照顺序分解为 $k$ 个回文字符串。解决这道题需要解决两步：一、先判断字符串的长度是否是 $k$ 的倍数，满足“恰好”这一条件；二、如满足一，再依次判断每个子串是否是回文字符串。第二步可以用两种方法做。
## 第一种
```c
for(int i=0;i<(s.size()/2);i++)
{
	if(s[i]!=s[s.size()-i-1])//对应判断
	{
		cout<<"NO";
		return 0;
	}
}
cout<<"YES";
return 0;
```
## 第二种
```c
string s1="",s2="";
int len=(s.size()%2==0?s.size()/2:s.size()/2+1);
for(int i=0;i<len;i++)
	s1+=s[i];
int len1=(s.size()%2==0?len+1:len);
for(int j=(s.size()-1);j>=len1-1;j--)
	s2+=s[j];
if(s1!=s2)
	cout<<"NO";
else
	cout<<"YES";
```
第二种方法是将一个字符串分成了两个字符串。其中一个是原字符串从开头到中间所形成的字符串，另一个是原字符串从末尾到中间所形成的字符串。代码中的三目操作符是为了区分两种情况。一、当字符串长度为奇数时，那么如上所说的两个“中间”指的是原字符串的正中间。如当字符串为 ```abcba``` 时，长度为奇数，则以 c 为中间，分为 ```abc``` 和 ```abc```（```cba``` 倒过来）两个字符串。它们完全相同，所以输出为 ```YES```；二、当字符串长度为偶数时，那么第一个“中间”指的是字符串长度除以二，第二个“中间”指的是字符串长度减字符串长度除以二。如当字符串为 ```abcd``` 时，长度为偶数。分为 ```ab``` 和 ```dc```（```cd``` 倒过来）两个字符。由于它们不相等，所以输出为 ```NO```。
## 代码如下
```c
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int k;
    cin>>k;
    if(s.size()%k!=0)
    {
        cout<<"NO";
        return 0;
    }
    for(int i=0;i<s.size();i+=(s.size()/k))
    {
        string s1="",s2="";
		int len=((s.size()/k)%2==0?(s.size()/k)/2:(s.size()/k)/2+1);
		for(int j=0;j<len;j++)
			s1+=s[i+j];
		int len1=((s.size()/k)%2==0?len+1:len);
		for(int j=(s.size()/k-1);j>=len1-1;j--)
			s2+=s[i+j];
		if(s1!=s2)
		{
		cout<<"NO";
		return 0;
		}
    }
    cout<<"YES";
    return 0;
}
```
打字不易，给个赞吧！
[我的博客](https://www.luogu.com.cn/blog/jdsndjknddb/)


---

## 作者：zsh_haha (赞：1)

### 题目大意

这道题大概意思就是：给定一个字符串 $s$，把 $s$ **恰好**分成 $k$ 等份，并且每一份都是回文串，如果 $s$ 满足条则输出 `YES`，否则输出 `NO`。

### 解题思路

首先，判断 $s$ 的长度是否能被 $k$ 整除，若不能，直接输出 `NO`。

然后，把 $s$ 分成 $k$ 份字符串，判断每份是否**都**回文，是的输出 `YES`，否则输出 `NO`。

### AC 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main(){
	char a[1001];
	cin>>a;
	int k;
	cin>>k;
	int l=strlen(a);
	if(l%k!=0){//不能恰好分成 k 份 
		cout<<"NO";
		return 0;
	}
	int t=l/k,tt=k;
	int i=0;
	char b[1001];
	while(tt--){
		for(int j=1;j<=t;j++){//截取每份字符串 
			b[j]=a[i++];
		}
		for(int j=1;j<=t/2;j++){
			if(b[j]!=b[t-j+1]){//判断回文 
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<"YES";
    return 0;
}
```

---

## 作者：qlqaq (赞：0)

### CF548A Mike and Fax题解
题目上说有 $k$ 个子字符串，我们就可以把字符串分成 $k$ 份，如果分不成 $k$ 份（也就是说长度不是 $k$ 的倍数）的话，直接输出```NO```。之后，我们循环枚举字符串中的 $k$ 个子字符串，一次判断是否回文即可。

### 代码

```
#include <bits/stdc++.h>
using namespace std;
string a;
int k;
bool add(string a) {
	int l=a.size();
	bool f=1;
	for(int i=0,j=l-1;i<=j;i++,j--){
		if(a[i]!=a[j])f=0;
	}
	return f;
}
int main() {
    cin>>a>>k;
    int l=a.size();
    if(l%k!=0){
    	cout<<"NO";
    	return 0;
	}
    int s=l/k;
    for(int i=0;i<l;i+=s) {
    	string a1=a.substr(i,s);
    	if(add(a1)==false){
    		cout<<"NO";
    		return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF548A)

- 首先，题目说是要分成 $k$ 份字符串，那么当 $k$ 不为字符串长度的因数时（此时无法分成 $k$ 个串），就可以输出 `NO` 然后退出程序。
- 之后，我们可以将字符串分成若干个小段，单独判断每一个小段是否是一个回文串，如果某一个小段不是回文串，则直接输出 `NO` 然后退出程序。

参考代码：

```
#include <bits/stdc++.h>
using namespace std;
string s;
int k;
bool hw (string st) {
	int len=st.size();
	for (int i=0;i<len;i++) 
		if (st[i]!=st[len-i-1]) return false;
	return true;
}
int main() {
    cin>>s>>k;
    int len=s.size();
    if (len%k!=0) {cout<<"NO",exit (0);};
    int lk=len/k;//每一个小串的长度为lk。
    for (int i=0;i<len;i+=lk) {
    	string st=s.substr (i,lk);//截取一小段字符串。
    	if (hw (st)==false) {cout<<"NO",exit (0);}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：lgydkkyd (赞：0)

# 题意
这道题告诉我们一个字符串和一个数 $k$ 之后，让我们求该字符串能否均分为 $k$ 个回文串。
# 思路分析
首先，既然要均分，那么字符串长度必须是 $k$ 的倍数，否则不可能满足要求。其次，依次判断 $k$ 个字符串，用类似于双指针的方法从两端向中间遍历，如果两个指针上的字符不同，也不满足条件。结束遍历后，如果程序还在运行说明该字符串满足要求。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k;
int main(){
	cin>>s>>k;
	if(s.size()%k!=0){//无法均分 
		printf("NO");
		return 0;
	}
	for(int i=0;i<s.size();i+=s.size()/k){//遍历 k 段子字符串 
		for(int j=i,l=i+s.size()/k-1;j<=l;j++,l--){//判断是否是回文串 
			if(s[j]!=s[l]){//不是回文串 
				printf("NO");
				return 0;
			}
		}
	}
	printf("YES");//是回文串 
	return 0;
}
```

---

## 作者：一只小菜包 (赞：0)

### 分析
这道题大概意思就是：给定一个字符串 $s$，把 $s$ 分成 $k$ 等份，并且每份都是回文串，如果 $s$ 满足条件则输出 ```YES```，否则输出 ```NO```。

大水题。定义一个判断回文串的函数，然后再取子串判断一下就行了。

### 代码
```cpp
#include<bits/stdc++.h>  
using namespace std;  
bool hw(const string& s) {  
    for (size_t i = 0; i < s.size() / 2; i++) {  
        if (s[i] != s[s.size() - i - 1]) {  
            return false;  
        }  
    }  
    return true;  
}  
int main() {  
    string s;  
    int k;  
    cin >> s >> k;  
    if (s.size() % k != 0) {  
        cout << "NO" << endl;  
        return 0;  
    }  
    size_t len = s.size() / k;  
    for (size_t i = 0; i < s.size(); i += len) { 
        if (!hw(s.substr(i, len))) {  
            cout << "NO" << endl;  
            return 0;  
        }  
    }  
    cout << "YES" << endl;  
    return 0;  
}
```

---

## 作者：mzyc_yang2021 (赞：0)

题意：给你一个字符串和一个整数 $k$，判断字符串是否由一些回文串组成，并且这些回文串的长度都要是 $k$。

思路：假如这个字符串长度是 $l$，那么我们可以判断 $l$ 是否可以整除 $k$。
若不可以，那我们就可以直接输出 NO。因为如果不可以，说明这个字符串就算是回文串组成，那它们的长度也不相同。接着考虑下一步。因为其每个回文子串的长度都一样，所以我们可以把字符串分成 $k$ 个子串，判断每个子串是否都是回文串就可以了。这里判断回文串的方法是使用左右指针遍历子串。

虽然我在洛谷上没过（一直显示等待），但是在原站上是[过了的](https://codeforces.com/problemset/submission/548/164826790)。

代码（加解释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1010];
int k,f;
bool cmp(int l,int r)
{
	int i=l,j=r; // 左右指针
	while(i<j)
	{
		if(s[i]!=s[j]) return false; // 若不一样，说明不是回文串，返回否
		i++,j--; // 左指针加一，右指针减一
	}
	return true;
}
int main()
{
	cin>>s+1>>k; // 从一开始读入，更方便
	int l=strlen(s+1);
	if(l%k!=0){cout<<"NO";return 0;} // 上述特判
	int len=l/k,i=1;
	while(i<l) // 分成k个子串，i就代表每个子串的第一个字符的下标
	{
		if(!(cmp(i,i+len-1))) f=1; // f若为一，说明不是，否则是
		i+=len;
	}
	if(f==0) cout<<"YES";
	else cout<<"NO"; // 输出
	return 0;
}
```

---

