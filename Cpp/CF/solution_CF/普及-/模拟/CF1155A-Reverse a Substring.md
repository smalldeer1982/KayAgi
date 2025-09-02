# Reverse a Substring

## 题目描述

给定一个**仅含小写字母**的字符串$s$，其长度为$n$

我们定义子串为一个字符串中连续的一段，比如```acab```是```abacaba```的子串（位置是```3~6```），而```aa```和```d```不是。所以对于一个字符串$s$，它的位置为$[l,r]$的子串可以表示成$s[l;r]$，即$s_ls_{l+1}...s_r$

您需要指定$s$的**一个**子串并翻转这个子串，使得新字符串的字典序比原来的字符串$s$小。注意不是最小。

如果可以满足题意，输出```YES```，再输出反转的区间。否则输出```NO```

我们认为字符串$x<y$当且仅当存在一个 $i$ $(1 \leq i\leq min(|x| ,|y|))$，使得 $x_i < y_i$ 并且$x_j =y_j (1 \leq j < i)$ 此处的绝对值符号```|x|``` 指的是字符串长度。在某些语言中您可以用 $<$ 运算符比较字符串字典序

## 说明/提示

样例$1$中，翻转后的字符串是```aacabba```

## 样例 #1

### 输入

```
7
abacaba
```

### 输出

```
YES
2 5
```

## 样例 #2

### 输入

```
6
aabcfg
```

### 输出

```
NO
```

# 题解

## 作者：StudyingFather (赞：3)

首先，假如字符串的字典序达到最小（即后面一个字母都不小于前面一个字母），那显然答案是`NO`。

否则，就一定存在一个 $ i $ ，使得 $ s_{i-1}>s_i $ 。我们只需将这两个字母交换顺序，就一定能使字符串的字典序最小。

```cpp
#include <stdio.h>
char s[300005];
int main()
{
 int n;
 scanf("%d",&n);
 scanf("%s",s+1);
 for(int i=1;i<=n;i++)
  if(s[i-1]>s[i])
  {
   puts("YES");
   printf("%d %d\n",i-1,i);
   return 0;
  }
 puts("NO");
 return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：1)

思路分析：

题目要求使得新字符串的字典序比原来的字符串 $s$ 小，**而不是最小。**

那么只有字符串是升序时才无解，输出 `NO`。否则找到逆序对就满足题目要求，输出 `YES`。

参考代码：

代码超短，不用想太复杂。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    string s;
    cin >> n >> s;
    for (int i = 0; i <= n - 2; i++)
    {
        if (s[i] > s[i + 1])
        {
            cout << "YES" << endl << i + 1 << " " << i + 2 << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
```


---

## 作者：力巴尔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1155A)

题目中的这句话很重要：使得新字符串的字典序比原来的字符串 $s$ 小，注意不是最小。

那么显然，如果这个字符串是升序的，就输出 NO，

否则就输出 YES，只要找到一个逆序对就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    string s;
    cin>>n>>s;
    for (int i = 0;i <= n - 2;i++)
        if (s[i] > s[i + 1])
        {
            puts("YES");
            cout<<i + 1<<" "<<i + 2;
            return 0;
        }
    puts("NO");
}
```

### 答应我，这次一定

---

## 作者：AC_Dolphin (赞：0)

题意：给一个长为n的字符串s，可以选择一个子串并把它翻转，如果翻转后形成的字符串s'<s（字典序），那么就输出yes，并输出子串的左右下标，如果找不到，就输出no


显然，如果s满足$s_{i+1}>=s_i$，那么就一定不可以，因为翻转之后最后一个字符肯定要比原来s这个位置的大，肯定s'>=s

所以只要判断一下，如果每一个$1<=i<=n-1$，都满足$s_{i+1}>=s_i$，那么就输出no,否则输出yes，可以找到第一个$s_{i+1}<s_i$的i值并将i,i+1输出就是答案了。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN=100010;
int n;
string s;
bool flag=false;
inline int read(){
    int f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
int main(){
    cin>>n;
    cin>>s;
    for(int i=0;i<s.length()-1;i++){
        if(s[i]>s[i+1]){
            flag=true;
            break;
        }
    }
    if(flag==false){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    for(int i=0;i<s.length()-1;i++){
        if(s[i]>s[i+1]){
            cout<<i+1<<" "<<i+2<<endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：冒泡ioa (赞：0)

> [博客链接](http://bubbleioa.top/archives/872)

如果字符大小非严格单增，显然无解，如果出现前面字符大于后面的字符的情况，输出它们的位置即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;string str;

int main(){
	cin>>n>>str;char last=str[0];int pos=0;
	for(int i=1;i<str.length();i++){
		if(last==str[i]){pos=i;continue;}
		if(last<str[i]){last=str[i];pos=i;}
		else {
			printf("YES\n%d %d",pos+1,i+1);
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：xh39 (赞：0)

理解题意,这句话很重要:Note that it is not necessary to obtain the minimum possible string,意思是没有必要获得字典序最小的字符串。

所以如果全部是升序就无法对换,否则对换降序的那两个,时间复杂度O(n-1)

代码好短啊......
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	int i,n;
	cin>>n>>s;
	for(i=1;i<n;i++){ //s[-1]不能取。
		if(s[i]<s[i-1]){
			cout<<"YES"<<endl;
			cout<<i<<" "<<i+1; //因为是从零开始的i-1就变成了i,i就变成了i+1。
			return 0; //结束程序。
		}
	}
	cout<<"NO";//说明没有任何一个降序的,即为升序。
	return 0;
}
```


---

