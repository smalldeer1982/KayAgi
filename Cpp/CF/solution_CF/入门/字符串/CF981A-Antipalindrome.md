# Antipalindrome

## 题目描述

A string is a palindrome if it reads the same from the left to the right and from the right to the left. For example, the strings "kek", "abacaba", "r" and "papicipap" are palindromes, while the strings "abb" and "iq" are not.

A substring $ s[l \ldots r] $ ( $ 1 \leq l \leq r \leq |s| $ ) of a string $ s = s_{1}s_{2} \ldots s_{|s|} $ is the string $ s_{l}s_{l + 1} \ldots s_{r} $ .

Anna does not like palindromes, so she makes her friends call her Ann. She also changes all the words she reads in a similar way. Namely, each word $ s $ is changed into its longest substring that is not a palindrome. If all the substrings of $ s $ are palindromes, she skips the word at all.

Some time ago Ann read the word $ s $ . What is the word she changed it into?

## 说明/提示

"mew" is not a palindrome, so the longest substring of it that is not a palindrome, is the string "mew" itself. Thus, the answer for the first example is $ 3 $ .

The string "uffuw" is one of the longest non-palindrome substrings (of length $ 5 $ ) of the string "wuffuw", so the answer for the second example is $ 5 $ .

All substrings of the string "qqqqqqqq" consist of equal characters so they are palindromes. This way, there are no non-palindrome substrings. Thus, the answer for the third example is $ 0 $ .

## 样例 #1

### 输入

```
mew
```

### 输出

```
3
```

## 样例 #2

### 输入

```
wuffuw
```

### 输出

```
5
```

## 样例 #3

### 输入

```
qqqqqqqq
```

### 输出

```
0
```

# 题解

## 作者：我和鱼过不去 (赞：5)

>The first line contains a non-empty string $s$ with length at most $50$ characters, containing lowercase English letters only.  

数据范围比较小，这里就直接上 $\operatorname{O}(n^2)$ 的做法。  
~~其实是我懒得想优化的方法。~~
### 思路
- 双重循环枚举子串的端点
- 判断是否为非回文串，并更新数据  

重点讲一下几个 string 类型的操作。

### substr函数
------------
例如：
```cpp
string str = "string";
cout<<str.substr(1,5); 
```
输出结果为 $\mathtt{trin}$。  
其中 $substr(i,j)$ 表示 **截取 $i$ ~ $j-1$ 的子串**。

### reverse函数
------------
快速翻转一个字符串：
```cpp
string str;
reverse(str.begin(),str.end());
```
接着就可以比较并判断了。
 
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int ans;
int main()
{
	cin>>str;
	for(int i=0;i<str.length();i++)  //双层循环枚举子串左右端点
    {
        for(int j=i+1;j<str.length();j++)
        {
            string a = str.substr(i,j-i+1);  //根据循环截取子串
            if(a.length()<=ans) continue;    //如果子串的长度不比当前答案长，那么就没有判断的必要了
            string b = a;
            reverse(b.begin(),b.end());
            if(a!=b) ans = a.length();     //能运行到这里，就可以直接赋值了
        }
    }
    cout<<ans;
	return 0;
}

```
~~string 类型真好用~~

---

## 作者：wjy2006 (赞：4)

这道题明显可以暴力，但我们可以想一想比暴力更优的办法。

首先，如果这个字符串 $S$ 本身就不是一个回文字串，答案显然就是 $S$ 自己的长度。

当 $S$ 的每一位都相等，易得答案为0。

但如果 $S$ 既是回文字串，而且每一位也并非完全相等，那该怎么办呢？

我们可以分析一下：



------------


如果 $S$ 是 ABBA 。

那么去掉最后的 A 之后，得到字符串 ABB 。要想让 ABB 对称，必须使 A=B ，但这样一来字符串就只能变成 AAA 类型了，不符合每一位并非完全相等的初始条件了，所以答案为原字符串长度 -1 。



------------


如果 $S$ 是 ABCBA 。

那么去掉最后的 A 之后，得到字符串 ABCB 。要想让 ABCB 对称，必须使 A=B ， B=C ，字符串就只能变成 AAAA 类型了，不符合每一位并非完全相等的初始条件了，所以答案为原字符串长度 -1 。



------------

综上所述，当 $S$ 既是回文字串，而且每一位也并非完全相等时，答案为 $S$ 自己的长度 -1 。


上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string S;
int main()
{
	bool flg=1;//记录S是否每一位都相等 
	cin>>S;
	int s=a.size();//记录 S 的长度 
	for(int i=0;i<s/2;i++){
		if(S[i]!=S[s-i-1]){//检测S是否回文 
			cout<<s;//发现不回文就输出S的长度 
			return 0;
		}
		if(S[i]!=S[i+1]) flg=0;//检测S是否每一位相等 
	}
	if(flg) cout<<0;
	else cout<<s-1;
	return 0;
}

```


---

## 作者：Firstly (赞：1)

这里给出一种与其余题解不一样的思路：使用队列配合 bfs 进行搜索操作。
## **解题思路：**

运用一般 bfs 的思路（只不过变成了字符串），先将整个字符串推进队列中，再不断搜索，掐头和去尾推进队列当中，当搜到非回文字符串时，返回字符串长度。

在这里，我们要介绍两个操作字符串的函数。

### **1. substr 函数**


------------
这个函数的作用是得到原字符串的一个部分。如：
```cpp
string s="hello";
cout<<s.substr(1,2)<<endl;
cout<<s.substr(0,2)<<endl;
```
其结果为：
```
el
he
```


注意： substr 函数内的两个参数中第一个是指得到的这一段字符串的起始下标（第一个字符下标为 0），第二个参数是指这一段字符串的长度，并非终止下标！！！

### **2. reverse 函数**


------------
这个函数能够非常简单地翻转一个字符串。它是一个无返回值的函数，且会在原字符串上进行操作。所以，当我们要将翻转以后的字符串与原字符串对比时，我们要先给原字符串找一个替身，然后才可进行对比。如：
```cpp
string s="hello";
string str=s;
reverse(str.begin(),str.end());// reverse 函数的用法
cout<<s<<endl;
cout<<str<<endl;
if(s==str)cout<<"YES"<<endl;//对比原字符串与翻转之后的字符串。
else cout<<"NO"<<endl;
```
其结果为：
```
hello
olleh
NO
```
讲解了那么多，相信大家应该都了解这两个函数的用法了吧！下面上代码：
## **Code：**


------------

```cpp
#include<iostream>//输入输出头文件
#include<cstring>//字符串部分头文件
#include<queue>//队列头文件
#include<algorithm>//reverse头文件
using namespace std;
string s;
int bfs(){
    queue<string>q;//队列
    q.push(s);
    while(!q.empty()){
        string now=q.front();
        q.pop();
        string ts=now;//给字符串找个替身
        reverse(ts.begin(),ts.end());//翻转字符串，得到原字符串now颠倒后的字符串
        if(ts!=now)return now.size();//因为搜索的字符串长度是递减的，所以第一个非回文字符串即为最长非回文字符串
        ts=now.substr(0,now.size()-1);//ts为除去最后一个字符的now字符串。
        q.push(ts);
        ts=now.substr(1,now.size()-1);//此时ts为除去第一个字符的now字符串。
        q.push(ts);
    }return 0;
}
int main(){
    cin>>s;
    bool flag=false;
    for(int i=1;i<s.size();i++){
		if(s[i]!=s[0]){flag=true;break;}
	}if(!flag){cout<<0;return 0;}//特判，如果在字符串中所有字符相同，则最长不回文字符串长度一定为0
    cout<<bfs();
    return 0;
}
```


---

## 作者：B_lhx (赞：1)

[CF981A Antipalindrome](https://www.luogu.com.cn/problem/CF981A)
==

思路:~~暴力出奇迹~~直接模拟+枚举+剪枝

```
#include<bits/stdc++.h> 
using namespace std;
char s[256],ss[256];//两个字符串
bool f(){//判断是否是“非回文串”
	for(int i = 0;i<strlen(ss)/2;i++){//循环
		if(ss[i]!=ss[strlen(ss)-1-i]){//如果有一项不对应就不可能是回文串
			return true;//返回
		} 
	}
	return false;//如果运行到现在还没有被返回true那就是false了
}
int main(){	
	cin>>s;//输入
	int sum=0;//最长子串的长度
	for(int i = 0;i<strlen(s);i++){//二层循环嵌套，分别枚举左右端点
		for(int j = i+sum;j<strlen(s);j++){//j=i+sum剪枝是因为如果长度不如已有的长就没必要运行下去了
			for(int k = i;k<=j;k++){//把s的子串复制到ss
				ss[k-i]=s[k];
			}
			if(f()){//如果不是回文串
				sum=max(sum,j-i+1);//更新最小值
			}
		}
	}
	cout<<sum;//输出
	return 0;
}
```


---

## 作者：__白衣渡江__ (赞：1)

玄妙的题······

这题有 $\operatorname{O}(n^3)$ 做法，$\operatorname{O}(n^2)$ 做法，$\operatorname{O}(n)$ 做法emm······

其他两篇题解分别讲了 $\operatorname{O}(n^3)$ 和 $\operatorname{O}(n)$，这篇题解就来讲 $\operatorname{O}(n^2)$ （滑稽）。

首先，设原串为 $S$。

要是 $S$ 不是回文串，直接输出总长度（滑稽）。

要是 $S$ 是回文串：

考虑最后求出的最长非回文子串。

要是首尾两个字符都在串里，那么显然是原串，而原串是回文的，矛盾。

**因此，要么最终串不包含首字母要么不包含尾字母。**

而去掉首字母的 $S$ 与去掉尾字母的 $S$，翻转一下即可得到彼此。

**于是他们最长非回文子串的长度相等。**

那就无所谓了，统一删最后一个吧。

接着递归求解（其实是循环枚举膜你）即可。

好了，这就是这题的 $\operatorname{O}(n^2)$ 解法。

优化一下可以得到线性算法，但有人讲了，就不再讲一遍了。

最后是简单易懂的 $Go$ 代码：

```go
package main
import "fmt"
var s string
func ispal(r int)bool{
    for i:=0;i<r-1-i;i++{
        if s[i]!=s[r-1-i]{
            return false
        }
    }
    return true
}
func main(){
    fmt.Scanf("%s",&s)
    for i:=len(s);i>0;i--{
        if !ispal(i){
            fmt.Println(i)
            return
        }
    }
    fmt.Println(0)
}
```

Over.

祝大家AC！

---

## 作者：ytcccf (赞：0)

### 题意简述

给定一段字符串，求这段字符串中最长的不回文字符串。(题意翻译已经不能再简洁了，赞）

### 题目分析

题目难度：入门

$\text{AC code}$ 时间复杂度为 $\Theta(n^3)$


### 解题思路 

由于给定的字符串长度很小，所以不需使用高级的算法，暴力枚举子串的左端点以及右端点，之后再暴力判断子串是否回文，更新答案即可 $\text{AC}$ 此题。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
char str[100010];
bool check(int x,int y)//判断是否为回文字符串 
{
	for(int i=x;i<=y;i++)
	{
		if(str[i]!=str[y+x-i]) return false;//有不一样的就返回false 
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);//cin、cout加速 
	cin>>str;
	int n=strlen(str),ans=0;
	for(int i=0;i<n;i++)//枚举子串左端点 
	{
		for(int j=i;j<n;j++)//右端点 
		{
			if(!check(i,j)) ans=max(ans,j-i+1);//如果不是回文串且长度比ans大就将ans更新  
		}
	}
	cout<<ans<<endl; 
	return 0;//完结撒花~ 
}

```

---

## 作者：Daniel_yao (赞：0)



# 题目大意

给定一串字符串，求一个最长且不回文的子串（注意：题目要求子串长度为 $1$ 的子串属于回文子串，见样例三）。

### 解题思路

- 暴力枚举所有子串，再把子串倒序存储进行比较；
- 判断子串是否回文，并且更新最大值；


双重循环枚举子串的左右端点，倒序存储是否判断回文并维护最大值。

```cpp
for(int i = 0;i < s.size();i++){//枚举左端点
		string num = "", sum = "";//定义string类型的变量分别存储正序和倒序的子串
		len = 1;
		for(int j = i+1;j < s.size();j++){//枚举右端点
			num += s[j];
			sum = "";
			for(int k = j;k >= i;k--){//倒序存储子串
				sum += s[k];
			}
			if(num != sum){//如果正序子串不等于倒序子串（意思是这个子串不是回文数）
				len++;
				maxi = max(maxi, len);//更新最大值
			}
		} 
	}
```
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len, maxi = 0;
int main(){
	cin >> s;
	for(int i = 0;i < s.size();i++){
		string num = "", sum = "";
		len = 1;
		for(int j = i+1;j < s.size();j++){
			num += s[j];
			sum = "";
			for(int k = j;k >= i;k--){
				sum += s[k];
			}
			if(num != sum){
				len++;
				maxi = max(maxi, len);
			}
		} 
	}
	cout << maxi;
	return 0;
}
```
这种是 $O(N^3)$ 的做法，当然还有 $O(N^2)$ 的做法，但题目的数据范围很小，所以这种方法就可以了。

---

## 作者：dhclientqwq (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/dhclient/p/15738287.html)

水题一道，分三种情况:

- 如果给你的字符串不是一个回文串的话，那就不需要删除，直接输出这个长度就好了，因为这就是最长的不是回文的字符串。

- 如果给你的是一个回文串的话，那么只需要删除一个字符就可以让这个字符串变成不是回文的，所以输出 $len-1$ 就好了。

- 如果像样例 3 一样的情况，直接输出 0 。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int len,n;
string str;
 
bool check()
{
  int sum = 0;
  for(int i=0,j=n-1;i<=j;i++,j--) {
    if(str[i] != str[j])return true;
  }
  return false;
}
 
int main()
{
  cin>>str;
  len = str.length();
  n = len;
  int flag = 0;
  while(1) {
    if(check()) {
      flag = 1;
      break;
    }
    if(n == 0) break;
    n--;
  }
  cout<<n;
  return 0;
}
```

---

## 作者：happybob (赞：0)

这里给出一个不用substr的写法，复杂度与大家都是差不多的，暴力枚举，但其实数据大一点暴力可能会T的

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

string s, tmp = "";

bool pd(string x)//判断是否不是回文
{
    string y = x;
    reverse(y.begin(), y.end());
    return x != y;
}

int main()
{
    cin >> s;
    int ans = 0;
    int len = s.length() - 1;
    for(int i = 0; i <= len; i++)
    {
        tmp = "";//清空
        for(int j = i; j <= len; j++)
        {
            tmp += s[j];
            if(pd(tmp))
            {
                ans = ans > j - i + 1 ? ans : j - i + 1;//三目运算符
            }
        }
    }
    cout << ans << endl;;
    return 0;
}
```

---

## 作者：RBI_GL (赞：0)

### 题意：

求一个字符串中最长的不回文字符串。

----



### 思路：

读入字符串，二重循环枚举，如果找到非回文串，就记录长度，每次更新答案来取到最大值即可。

注意：字符串 $i$ ~ $j$ 的长度是 $j$ − $ i +1$

-----


### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
string a;
int len;
int ans = 0;
int x;

bool hw(string a) { //判定回文串函数
	for(int i=0; i<a.size()/2; i++) {
		if(a[i]!=a[a.size()-1-i]) return false;
	}
	return true;
}

int main() {
	cin>>a;
	len = a.size();
	for(int i=0; i<len; i++) {
		for(int j=i+1; j<len; j++) { //枚举搜索
			if(hw(a.substr(i,j-i+1)) == false) { //如果 i~j 是非回文串
				x = j-i+1;
				ans = max(ans,x); //取最大值
			}
		}
	}
	cout<<ans; //输出答案 
	return 0;
}
```

-------




### 其他：

$substr$ 函数的用法：

一：形式：$substr(start, length)$ 

二：使用方法：返回一个从指定位置开始，并具有指定长度的子字符串。


三：参数：


- $start$：必选。所需的子字符串的起始位置。字符串中第一个字符的索引为 0。


- $length$：可选项。返回的子字符串中包含的字符数。




---

## 作者：houpingze (赞：0)

~~本题阔以暴力枚举~~

 思路：枚举$i$~$j$（$i$和$j$皆小于$s.size()$，且$i<j$），看看这个字符串从$i$~$j$是不是非回文，如果是，打擂台取长度最大值。

~~没看懂？再看一遍~~

PS：字符串$i$~$j$的长度是$j-i+1$

## AC CODE:

```cpp
#include<bits/stdc++.h> 
using namespace std;
int m;
bool hw(string a){
	for(int i=0;i<a.size()/2;i++){
		if(a[i]!=a[a.size()-1-i]) return false;
	}
	return true;
}//判断回文代码
int main(){
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		for(int j=i+1;j<s.size();j++){//枚举i~j
			if(hw(s.substr(i,j-i+1))==false){//如果i~j是非回文串
				int x=j-i+1;
				m=max(m,x);//打擂台取最大值
			}
		}
	}
	cout<<m;//输出
	return 0;
}

```

完结撒花~~~


---

## 作者：RioBlu (赞：0)

本题就是找一个**最长**非**回文字符串**的长度

由于最长字符串长度为$50$

可以**暴力枚举**

# 上代码
```
#include<bits/stdc++.h>
using namespace std;
string a;
int ans;
bool pan(int z,int y)//判断是否是回文字符串
{
    string zs,ys;
    for(int s=z;s<=y;s++)
    {
        zs=a[s]+zs;
    }
    for(int s=y;s>=z;s--)
    {
        ys=a[s]+ys;
    }
    if(zs==ys)return 0;
    else
    return 1;
}
int main()
{
    cin>>a;
    for(int s=0;s<a.size();s++)
    {
        for(int v=s+1;v<a.size();v++)
        {
            if(pan(s,v)&&v-s>ans)//v-s未加1输出会补上
            {
                ans=v-s;
            }
        }
    }
    if(pan(0,a.size())&&ans!=0)//记住特判一个全是一个字符的！
    cout<<ans+1<<endl;
    else
    cout<<0<<endl;
}
```

---

