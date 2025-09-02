# Caesar Cipher

## 题目描述

输入一个由大写字母构成的字符串 $s$ ,求 $s$ 的每一个字母往后移 $k$ 位的结果。当字母移动后超出 $\texttt{Z}$ 时，回到字母表的开头  $\texttt{A}$ 继续移动。

## 样例 #1

### 输入

```
CODEFORCES
5
```

### 输出

```
HTIJKTWHJX
```

## 样例 #2

### 输入

```
WIXYZILWYM
6
```

### 输出

```
CODEFORCES
```

# 题解

## 作者：_Give_up_ (赞：6)

## 题目大意
用给出一个全是大写的字符串，让要求加密。每一个字符加 $k$，如果超出了二十六个字符的范围，就从头再数。

## 题目思路

这道题由于我们需要考虑越没越界，不能直接加，所以我们需要一个别的方法，我们知道 ASCII 码表中 $A$ 对应的值是 $65$，所以我们字符减 $65$，使得字符从 $0$ 记，再加上 $k$，再模 $26$，得到的数加上刚才减去的 $65$，就可以得到加密后的字符。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	int k;
	cin >> s >> k;
	int l=s.length();
	for (int i=0;i<l;i++)
		cout << char((s[i]+k-65)%26+65);
	cout << endl;
	return 0; 
}
```


---

## 作者：可爱的小于 (赞：2)

题意：给定一个字符串，要求把每位上的字符的值往后移动 $k$ 位即可。

思路：我们取出每位上的字符，把它的值加 `k`，如果这个字符值大于 `Z`，减去 `26` 就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k;
int main()
{
	cin>>s>>k;
	for(int i=0;i<s.size();i++){
	    s[i]+=k;
	    if(s[i]>'Z')s[i]-=26;
	}
	cout<<s<<endl;
	return 0;
}
```


---

## 作者：tommyfj (赞：2)

先提供一下题目翻译：

给定义一个长度不大于 $10$，不小于 $1$ 的字符串（所有字符均为大写英文字母）和密钥 $k$，求出加密后的字符串。（加密规则：所有字母均向后移动 $k$ 位，当当前字母大于 Z 时，回到字母表的开头 A 继续移动。）

hh，那不是太简单了？直接加 $k$ 不就得了？

是不是认为这就做完了？No！

当一个字母移动 $k$ 位后，结果可能会大于 Z（也就是不在字母表内），那我们可以用当前字母移动 $k$ 位后的结果 $-26$，就是`a[i] = char(a[i] + k - 26)`。

万一按你这么做后，结果不是字母表中的字母怎么办？

证明：

你看看题目，输入的字符只为大写字母，且 $1 \leq k \leq 25$，我们假设一个字母最大为 Z，$k$ 最大为 $25$，因为 Z 的 ASCII 码为 $90$，$90 + 25 - 26 = 90 - 1 = 89$，转成字符类型就是字母 Y，所以它是不会因此 WA 掉的。

代码展示：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char a[1005];
int k;
int main()
{
	cin.getline(a,1005);
    scanf("%d",&k);
	int len = strlen(a);
	for(int i = 0;i < len;i ++)
	{
        a[i] = char(a[i] + k);//向后移动k位。
        if (a[i] > 'Z')//如果字符超出26字母表，则需要对该字符进行特殊处理
        {
        	a[i] = char(a[i] - 26);//超了就从字母表从头开始
        }
        printf("%c",a[i]);
	}
	return 0;
}
```


---

## 作者：guozhetao (赞：1)

## 题目大意

给你一个全是大写字符串 $n$ 和一个数字 $k$，问将字符串的每一项先后移动 $k$ 位的新字符串（字母 Z 后面重新为 A）。保证 $k \leq 25$。
## 思路

利用 ASCII 码。

ASCII (( American Standard Code for Information Interchange ): 美国信息交换标准代码）是基于拉丁字母的一套电脑编码系统，主要用于显示现代英语和其他西欧语言。它是最通用的信息交换标准，并等同于国际标准 ISO/IEC 646 。 ASCII 第一次以规范标准的类型发表是在 1967 年，最后一次更新则是在 1986 年，到目前为止共定义了 128 个字符 。

我们将字符串的每一个字母都转化成数字，再加上 $k$，超过 $90$（Z 的 ASCII 码是 $90$）就减去 $26$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k;
int main() {
	cin>>s;
	scanf("%d",&k);
	k %= 26;
	for(int i = 0;i < s.size();i++) {
		int a = s[i];
		a += k;
		if(a > 90) {
			a -= 26;
		}
		cout<<char(a);
	}
}
```


---

## 作者：XKqwq (赞：1)

### $\texttt{Translation}$

给出一个由大写字母构成的字符串，求每一位后移 $k$ 个字母后的字符串。

### $\texttt{Solution}$

直接模拟即可。

注意如果后移 $k$ 位时超出了大写字母的范围时，需要从 $\texttt{A}$ 开始。

我们可以先将字符串的 ASCII 码减去 $65$，也就是
$\texttt{{A,B,C}}\cdots \texttt{Z}$ 分别对应着 ${1,2,3\cdots 26}$。

这时把 ASCII 码加上 $k$，再 $\bmod{26}$，转换成字符输出就可以了。

### $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std; 

int k,l;
string s;

int main(){
	cin>>s>>k;
	l=s.size();//好习惯，避免循环里每次都要判断
	for(int i=0;i<l;i++){
		s[i]=(s[i]-'A'+k)%26+'A';//这里可以直接输出。
	}
	cout<<s;
	return 0;
}
```


---

## 作者：wangyi_c (赞：0)

[你谷题目传送门](https://www.luogu.com.cn/problem/CF153C)

[CF题目传送门](http://codeforces.com/problemset/problem/153/C)

## 1. 题目大意

类似于一个凯撒密码。给出一个字符串和 $k$，输出每个字符往后移动 $k$ 位后的字符串。

## 2. 思路讲解 

这道题，就是按着题目意思模拟就可以了，每一位都往后移，但是要注意超过最大的 $Z$ 时要模上 $26$，不然会出现乱码，保证在 $A$ 到 $Z$ 之中，类似一个环形问题。

## 3. AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
string str;
int k;
signed main(){
	cin>>str;
	cin>>k;
	for(int i=0;i<str.size();i++){
		int a=str[i]-'A';//转换成数字再加并取模
		a+=k;
		a%=26;//模上26，保证在A到Z的区间内
		cout<<char(a+'A');//输出字符
	}
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：多喝岩浆 (赞：0)

我们惊奇的发现，这题就是把字符串中所字符往后移 $ k $ 位，然后输出就好了，代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define PP pair <int, int>
using namespace std;
string a;
int k;
int main () {///////
	cin >> a >> k;
	for (int i = 0; i < a.size (); i ++ ) 
		cout << char ((a[i] - 'A' + k) % 26 + 'A');
	return 0;
}
```


---

## 作者：jimmyfj (赞：0)

**题目大意 :** 现在给你一个全部是由大写字母构成的字符串，让你对其进行加密，加密的方法是这样的，将这一位上的大写字母替换成该大写字母 $k$ 位后的大写字母，以此类推，请你输出经过加密后的字符串。

本题思路 : 定义两个 $string$ 类型的字符串 $s$ 和 $str$，把 $26$ 个大写字母存在字符串 $s$ 里面，然后将输入的字符串 $str$ 遍历一遍。每到一个位置 $i$，在字符串 $s$ 中找出与 $str_{i}$ 相同字母的位置 $j$，然后将 $str_{i}$ 上的字母替换为 $s_{(j+k)\bmod 26}$，最后输出就可以了。

参考代码 :
```cpp
#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std;
string str;
string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int k;
int main()
{
    cin >> str;//初始字符串
    scanf("%d", &k);
    for(int i = 0; i < str.size(); i ++)
    {
    	for(int j = 0; j < s.size(); j ++)
    	{
    		if(s[j] == str[i])//寻找相同的字母
    		{
    			str[i] = s[(j + k) % 26];//替换成k位后的字母
    			break;
			}
		}
	}
    
	for(int i = 0; i < str.size(); i ++) cout << str[i];//加密后的字符串
    
    return 0;
}
```

---

## 作者：lmz_ (赞：0)

希望管理员看到以后把这题评橙。

首先，我们需要知道一个大写字母是第多少个字母，我们设这个字符变量为 $x$，那么这个字母就是第 $x-65+1$ 个字符。

然后，题目让我们右移 $k$ 位，那么就用这个值 $+k$，为了防止出界，我们还要用这个结果对 $26$ 取模。

最后，我们只要再加上 $64$ 就可以输出了。

---

## 作者：_lmz_ (赞：0)

## 题目大意：
给你一个字符串，以及一个整数 $k (0 \leq k \leq 25)$，让你把字符串的每一个字符加上 $k$。
## 题目思路：
因为加上 $k$ 以后可能不是字母了，所以我们需要把它减去 $65$ 之后加上 $k$ 后对 $26$ 取模，最后再加上 $65$，把它变回字符。
## 代码：
```cpp
string str;
int k;
/*中间框架部分自己打*/
cin>>str;
cin>>k;
for(int i=0;i<str.size();i++)
    str[i]=char(str[i]-'A'+k)%26+'A';
cout<<str;
return 0;
```

---

