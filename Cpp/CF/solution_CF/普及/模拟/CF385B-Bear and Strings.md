# Bear and Strings

## 题目描述

The bear has a string $ s=s_{1}s_{2}...\ s_{|s|} $ (record $ |s| $ is the string's length), consisting of lowercase English letters. The bear wants to count the number of such pairs of indices $ i,j $ $ (1<=i<=j<=|s|) $ , that string $ x(i,j)=s_{i}s_{i+1}...\ s_{j} $ contains at least one string "bear" as a substring.

String $ x(i,j) $ contains string "bear", if there is such index $ k $ $ (i<=k<=j-3) $ , that $ s_{k}=b $ , $ s_{k+1}=e $ , $ s_{k+2}=a $ , $ s_{k+3}=r $ .

Help the bear cope with the given problem.

## 说明/提示

In the first sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9) $ .

In the second sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9),(1,10),(1,11),(2,10),(2,11),(3,10),(3,11),(4,10),(4,11),(5,10),(5,11),(6,10),(6,11),(7,10),(7,11) $ .

## 样例 #1

### 输入

```
bearbtear
```

### 输出

```
6
```

## 样例 #2

### 输入

```
bearaabearc
```

### 输出

```
20
```

# 题解

## 作者：IAKIOI123 (赞：6)

# CF385B 题解
[**题目传送门**](https://www.luogu.com.cn/problem/CF385B)

[**博客食用更佳**](https://www.luogu.com.cn/blog/901459/solution-cf385b)

---
### 题目要求：
给定一个字符串，找出所有的子串$\ s_{i}s_{i+1}...s_{j}$，该子串包含 `bear` 这个单词，输出满足条件的子串个数。

---
题目也是非常的简单，我们只需先读入一个字符串 $s$，接着遍历一遍它的子串个数并输出就好了。

$\color{Limegreen}AC\:code$
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<map>
using namespace std;
string s;
int sum,ans;
int main(){
    getline(cin,s);
    int len=s.length();
    for(int i=0;i<=len-4;i++){
        if(s[i]=='b'&&s[i+1]=='e'&&s[i+2]=='a'&&s[i+3]=='r'){
            sum+=(i+1)*(len-3-i)-ans*(len-3-i);
            ans=i+1;
        }
    }
    cout<<sum<<endl;
    return 0;
}
```

[**AC记录**](https://www.luogu.com.cn/record/130859485)

---

## 作者：nxd_oxm (赞：2)

# 题意
本题说给一个字符串，问含有 ``bear`` 的 **字串** 有多少个。

# 思路
首先我们要找到每一个 ``bear``。

![](https://cdn.luogu.com.cn/upload/image_hosting/n87scth3.png)

所以算出每个 ``bear`` 左边和右边的字符个数。易知，左边有 $i$ 个字符，右边有 $len-i-4$ 个字符。所以每个 ``bear`` 都要给计数器加上 $i \times (len-i-4)$ 种情况。

但是有多个 ``bear`` 怎么办呢？我们看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/0aodyvuc.png)

所以说，针对两个相邻的 ``bear``，从第二个 ``bear`` 的 ``r`` 开始一直往后都是重复滴。

所以我们拿个变量存着上一个 ``bear`` 的左边字符个数，乘上当前 ``bear`` 右边字符个数，这些部分都是重复的，要减掉。

代码比较短，主要是思维和细节。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a;
	cin>>a;
	int ans=0,last=0;
	for(int i=0;i+3<a.size();i++){
		if(a[i]=='b'&&a[i+1]=='e'&&a[i+2]=='a'&&a[i+3]=='r'){
			ans+=(i+1)*((int)a.size()-i-3)-last*((int)a.size()-i-3);
			last=i+1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：naroto2022 (赞：2)

# CF385B 题解

### 思路

其实思路非常简单，就是遍历整个字符串，要是找到一个 `bear`，答案 $ans$ 就加上这个 `bear` 前面的字符个数 $\times$ `bear` 后面字符的个数，当然，如果这样，回合前面的 `bear` 重复，所以答案还要再减去上一个 `bear` 的个数。

### 说明

就不说明去重的了，就简单地说一下为啥找到一个 `bear`，答案 $ans$ 就加上这个 `bear` 前面的字符个数 $\times$ `bear` 后面字符的个数。

其实问题可以转化为这个长字符串中有几个连续字符组成的子串含我们找到的 `bear`，那在这个 `bear` 前面可以和它搭配的方法数为它前面有的字符数，同理，后面的搭配方法数就是后面有的字符数，有乘法原理，能和它搭配的方法数为 `bear` 前面的字符个数 $\times$ `bear` 后面字符的个数。

### 总结

1. 千万千万要去重！
2. 小小的组合。
3. 乘法原理。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
string s;
int ans,len,c;
//ans为答案，len为字符串长度。 
int main(){
    cin>>s;
    len=s.size();//求字符串的长度 
    for(int i=0; i<len-3; i++)
        if(s[i]=='b'&&s[i+1]=='e'&&s[i+2]=='a'&&s[i+3]=='r'){//找到了一个"bear"。 
            ans+=(i+1)*(len-i-3)-c*(len-i-3);//加上这次计算的结果并且减去与上一次重复的部分。 
            c=i+1;//更新c的值。 
        }
    cout<<ans;
    return 0;
}
```


---

## 作者：SUNCHAOYI (赞：2)

这道题需要求字符串的子串中包含 `bear` 的个数。

最简单的算法是枚举子串的起始位置与结束位置，如果包含 `bear`，就将答案的数量 $+1$。但是分析复杂度可知，两层循环加上字符串的截取与查找，是无法通过总长度 $s = 5000$ 的，因此我们就要考虑每一个 `bear` 字串对答案的贡献。

```cpp
for (int i = 0;i < str.size ();++i)
{
	for (int j = i + 1;j < str.size ();++j)
		{
		string _n = str.substr (i,j - i + 1);
		if (_n.find("bear") != -1) ans++;
	}
}
```

遍历整个序列，如果查找到 `bear`，就会对后面的子串产生影响。从第 $i$ 位查找到最后，如果包含 `bear`，那么只要另外子串包含这个 `bear`，那么就会是答案增加。但同时要记得去除重复计算的部分，因此就有：枚举到第 $i$ 位，若包含 `bear`(从第 $i$ 位到最后)，则答案会增加整个字符串的长度 $- \ i \ - \ 3 \ - \ $ `bear` 第一次出现的位置。这样就减少了一层循环，可以通过此题。

```cpp
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
int main ()
{
	string str;int ans = 0;
	cin>>str;
	for (register int i = 0;i < str.size ();++i)
	{
		string d1 = str.substr (i,str.size () - i);
		if (d1.find("bear") != -1) ans += str.size() - i - 3 - d1.find("bear");
	}
	printf ("%d\n",ans);
	return 0;
}
```

---

## 作者：__main__ (赞：2)

每找到一个`bear`，`ans`就加上`bear`前面字符的数量乘上后面字符的数量。

因为会重复计算，所以还要减去上一个`bear`的个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int len = s.size(), ans = 0, pos = 0;
    for (int i = 0; i < len - 3; ++i)
    {
        if (s[i] == 'b' && s[i + 1] == 'e' && s[i + 2] == 'a' && s[i + 3] == 'r')
        {
            ans += (i + 1) * (len - i - 3) - pos * (len - i - 3);
            pos = i + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：ckk11288 (赞：0)

思路：每找到一个“bear”就加上它前面的字符数×后面的字符数
由于此做法不能避免重复计算，所以要减去上一个“bear”的个数。
```
#include<bits/stdc++.h>
using namespace std;
char s[10101];
int sum=0,i,c,l;
int main()
{
	gets(s);
	l=strlen(s);//求字符数组长度
	for(i=0;i<l;i++)
	{
		if(s[i]=='b'&&s[i+1]=='e'&&s[i+2]=='a'&&s[i+3]=='r')
		{
			sum+=(i+1)*(l-i-3)-c*(l-i-3);//加上这次计算的结果，并减去与上一次计算的重复部分
			c=i+1;//更新c的值，即记录上一次
		}
	}
	cout<<sum<<endl;
	return 0;
}
```

---

