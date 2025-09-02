# [AGC037A] Dividing a String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_a

英小文字からなる文字列 $ S $ が与えられます。以下の条件をみたす最大の正整数 $ K $ を求めてください。

- $ S $ の空でない $ K $ 個の文字列への分割 $ S=S_1S_2...S_K $ であって $ S_i\ \neq\ S_{i+1} $ ($ 1\ ≦\ i\ ≦\ K-1 $) を満たすものが存在する。

ただし、$ S_1,S_2,...,S_K $ をこの順に連結して得られる文字列のことを $ S_1S_2...S_K $ によって表しています。

## 说明/提示

### 制約

- $ 1\ ≦\ |S|\ ≦\ 2\ \times\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

例えば `aa`,`b`,`ba`,`a` と $ S $ を $ 4 $ つの文字列に分割することができます。

## 样例 #1

### 输入

```
aabbaa```

### 输出

```
4```

## 样例 #2

### 输入

```
aaaccacabaababc```

### 输出

```
12```

# 题解

## 作者：zct_sky (赞：5)

### 题意：
给定一个字符串 $S$,

将 $S$ 分成 $k$ 段，使相邻的两段不相同。

请你找出最大的 $k$。
### 思路：
一道很简单的贪心题。

因为只要使相邻的两段不相同，所以只需将 $S$ 从头到尾遍历一遍，如果前一个字符串和后一个字符串不同，则单独提取出来，并把 $ans+1$ 。

### 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
string a,b,s;
int l,ans;
int main(){
	cin>>s;//输入 
	l=s.length();
	for(int i=0;i<l;i++){
		a+=s[i];
		if(a!=b){//如果前一个字符串和后一个字符串不同
			b=a;//则提取出来 
			ans++;
			a="";
		}
	}
	cout<<ans;//输出 
	return 0;
} 
```

---

## 作者：phigy (赞：3)

题目要求将字符串 $S$ 划分成 $k$ 个互不相同的字符串 。

求最大的 $k$ 。

字符串长度一定要么是 $1$ 要么是 $2$ 。

因为 $1,2,1,2……$ 的分割相邻字符串显然不同 。

设 $DP[i][j]$ 表示前 $i$ 个划分且最后一段是以 $i$结尾的长度为 $j$的字符串 的最大段数 。



显然 $DP[i][1]>=DP[i][2]$ 。

若 $S[i]!=S[i-1]$ ，

$DP[i][1]=DP[i-1][1]+1$ ，

否则 $DP[i][1]=DP[i-1][2]+1$ ，

不论怎样 $DP[i][2]=DP[i-2][1]+1$ 。

发现其实否则那一条可以转化为 ： 

$DP[i][1]=DP[i-1][2]+1=DP[i-3][1]+2$ 。

所以设 $DP[i]$ 表示前 $i$ 个划分且最后一段是以 $i$结尾的字符串 的最大段数 。

若 $S[i]!=S[i-1]$ ，

$DP[i]=DP[i-1]+1$ ，

否则 $DP[i]=DP[i-3]+2$ ，

答案是 $DP[n]$ 。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=2e5+5;

char s[N];
int n,f[N];

int main() 
{
    int i,j,k;
	cin>>s+1;
    n=strlen(s+1);
	for(i=1;i<=n;i++)
    {
		if (s[i]==s[i-1]) 
        {
            f[i]=(i>=3)?f[i-3]+2:1;
        }
		else 
        {
            f[i]=f[i-1]+1;
	    }
    }
    cout<<f[n]<<endl;
    return 0;
}

```


而依照上述内容，楼上大佬贪心正确性显然成立。

---

## 作者：精神小伙！ (赞：2)

## 思路
这道题可以用贪心的思想做，只要前一个子串和后一个子串不一样，就把它单独提取出来，并且把 $ans$++ 。

CODE:


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
string s;
int main()
{
    int ans=0;
    string a=" ",b=" ";
    cin>>s;
    int len=s.size();
    for(int i=0;i<len;++i)
    {
    	a+=s[i];
    	if(a!=b)
    		ans++,b=a,a=" ";//只要不一样就提取，并把ans++
    }
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ShineEternal (赞：2)

[更护眼的阅读效果](https://blog.csdn.net/kkkksc03/article/details/105588843)。

## description

- 给定一个字符串 $S$，请你找出一个最大的 $k$，使得将这个字符串划分成 $k$ 段后能够保证相邻的两段不相同。

- $1\le |S| \le 2\times 10^5$，且保证 $S$ 串内均为小写字母。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution

我们贪心的进行划分，每次遇到一个和上一次不一样的串就可以单独提取出来一次了。

## code
```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
char s[200005];
int main()
{
	int cnt=0;
	scanf("%s",&s);
	int n=strlen(s);
	string a="",b="";
	for(int i=0;i<n;i++)
	{
		a+=s[i];
		if(a!=b)
		{
			b=a;
			cnt++;
			a="";
		}
	}
	printf("%d\n",cnt);
	return 0;
} 
```

---

## 作者：CmsMartin (赞：1)

## 写在前面

推广一下我的博客 [CmsBlog](http://116.62.168.66:8090)

## 题目描述

+ 给定一个字符串 $S$；

+ 将该字符串划定为 $k$ 段，保证每一段不同

+ 试求 $k$ 是多少

## 思路

本题适合我这样的萌新练习贪心大法

只需从头扫到尾，记录现在选择的字符串，再用一个变量记录上一个选择的字符串，如果现在选择的字符串与上一个选择的不同，直接 Ans++, 并将上一个选择的字符串改为现在选择的字符串，清空现在的字符串。

~~证明显然~~

## 参考程序


```cpp
#include <bits/stdc++.h>
using namespace std;

string S;

int Ans;

string Last , Now;

int main() {
	ios::sync_with_stdio(false);
	
	cin >> S;
	
	for(int i = 0; i < S.size(); i++) {
		Now += S[i];
		if(Last != Now) {
			Last = Now;
			++Ans;
			Now = "";
		}
	}
	
	cout << Ans << endl;
	
	return 0;
}
```


---

## 作者：TsH_GD (赞：0)

### 题目描述

* 给定一个字符串 $S$ 。

* 请你找出一个最大的 $k$ 。

* 使得将这个字符串划分成 $k$ 段后能够保证相邻的两段不相同。



## 思路


贪心的进行划分。

**每次遇到一个和上一次不一样的串就可以单独提取出来一次**。

 

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005];
int main(){
	int ans=0;
	scanf("%s",&s);
	int n=strlen(s);
	string s1="";
	string s2="";
	for(int i=0;i<n;i++){
		s1+=s[i];
		if(s1!=s2){
			s1=s2;
			ans++;
			s1="";
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：BlackPanda (赞：0)

 [题目传送门](https://www.luogu.com.cn/problem/AT5158)


------------
## 题目描述
- 给定一个字符串 $ S $
- 使得将这个字符串划分成 $ k $ 段后能够保证相邻的两段**不相同**。
- 求出最大的 $ K $


------------
## 我的思路
 这道题可以用贪心来做
 
先**遍历**一遍，然后划分，定义一个字符串来记录选择的子串，如果当前选择的子串和上一个选择的子串不同，**然后清空当前的字符串**，计数器累加，最后输出计数器。

 [**代码亲测有效**](https://www.luogu.com.cn/record/64166263)


------------

### 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string st,s1="",s2="";
int ans,i;
int main(){
	cin>>st;
	int len=st.length();
	while(i<len){
		s1=s1+st[i];
		if(s1!=s2){	//前后子串不一样 
		 	s2=s1,s1=""; 	//注意要清空	
			ans++;	//计数器累加 
		}
		i++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：fanersaiwenxue (赞：0)

## Describe

给定一个字符串 $ S $，请你找出一个最大的 $ K $，使得将这个字符串划分成 $ K $ 段后能够保证相邻的两段不相同。
$ 1≤∣S∣≤2×10^5 $，且保证 $ S $ 串内均为小写字母
感谢来自大佬 @ShineEternal 的翻译。
 
## Idea

既然题目上说了将一个长度为 $ S $ 的字符串分成最大的 $ K $ 份 , 那我们自然而然会想到 : 贪心 ( 不会 dp QWQ ...

每次读入字符 $ s $ 加入，如果和上一个字符串不同的话 , 更新段数即可。

## Working

首先将字符串 $ S $ 一个一个读入以保证 $ ans $ 值最大，再使用 $ x $ 保存每一个最新的字符串 , 将 $ x $ 串与 $ y $ 串作比较，如果不相同的话 , 更新 $ y $ 串并将 $ x $ 串清零以保证相邻性 , 之后更新 $ ans $ 值就 OK 了 。

因为题目上说了字符串全部为小写字母，所以为了防止死循环要加个判断是否为小写字母，如果不是小写字母说明字符串 $ s $ 输入完毕退出即可。

我认为也不是特别慢吧.. [这里](https://www.luogu.com.cn/record/59701419)

## ACcode

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string x,y;
char s;
int ans;
int main()
{
	while(cin>>s)
	{
		if(s>='a' && s<='z')
		{
			x+=s;
			if(x!=y)
			{
				y=x;
				ans++;
				x="";
			}
		}
		else break;
	}
	cout<<ans;
	return 0;
}
```

✿✿ヽ(°▽°)ノ✿

---

## 作者：jxbe6666 (赞：0)

这是一道关于字符串的好题
### 题意：
给定一个字符串 s1，求最多能分成几部分，使相邻两部分不相同。

-----

### 思路：
从题意中，我们发现了这道题的思路：**贪心**  
我们可以从 0 …s1.length() 去判断是否和上次相等，如果相等的话就加上当前字符。到下一次循环再进行比较。如果不相等的话，就把当前的字符串值记录下来，作为下一次的比较字符串。并且答案 ans++。  

-----

### AC Code ↓：

-----
```c++
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
string s1, last, now;
int ans;
inline void write(int x)
{ // 快输
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    cin >> s1;
    int len1 = s1.length();
    for (int i = 0; i < len1; i++)
    {
        now += s1[i];//不管如何都先加上当前字符
        if (now != last)//如果不同
        {
            last = now;
            now = "";
            ans++;//答案加一
        }
    }
    write(ans);
    I AK IOI
}

```

---

