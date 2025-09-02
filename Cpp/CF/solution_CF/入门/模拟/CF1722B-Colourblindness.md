# Colourblindness

## 题目描述

Vasya has a grid with $ 2 $ rows and $ n $ columns. He colours each cell red, green, or blue.

Vasya is colourblind and can't distinguish green from blue. Determine if Vasya will consider the two rows of the grid to be coloured the same.

## 说明/提示

In the first test case, Vasya sees the second cell of each row as the same because the second cell of the first row is green and the second cell of the second row is blue, so he can't distinguish these two cells. The rest of the rows are equal in colour. Therefore, Vasya will say that the two rows are coloured the same, even though they aren't.

In the second test case, Vasya can see that the two rows are different.

In the third test case, every cell is green or blue, so Vasya will think they are the same.

## 样例 #1

### 输入

```
6
2
RG
RB
4
GRBG
GBGB
5
GGGGG
BBBBB
7
BBBBBBB
RRRRRRR
8
RGBRRGBR
RGGRRBGR
1
G
G```

### 输出

```
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：DANIEL_x_ (赞：2)

## 思路：
给出了两个由 ```RGB``` 组成的字符串。

思路就是如果这两个字符串中出现了 ```G```，那就换成 ```B```， 然后在对比两个字符串

复杂度：$O(n)$ 能过。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T,n;string s1,s2;
    cin>>T;
	while(t--){
		cin>>n>>s1>>s2;
		int len=s1.size();
		for(int i=0;i<len;++i)
        		if(s1[i]=='G')
                		s1[i]='B';
		for(int i=0;i<len;++i)
        		if(s2[i]=='G')
                		s2[i]='B';
		if(s1==s2)
        		puts("YES");
		else 
        		puts("NO");
	}
	return 0;
}//没有快读，快写
```


---

## 作者：pokefunc (赞：0)

### 题意

给定两个由 `RGB` 组成的字符串，`R`代表红色，`G` 代表绿色，`B` 代表蓝色。`Vasya` 有色盲症因此他无法分辨蓝色和绿色。问这两个字符串在 `Vasya` 眼里是否相同。

### 题解

既然 `G` 和 `B` 是没有区别的，那么直接把 `G` 全部改成 `B` 或者 `B` 全部改成 `G` 判是否相等就完了。

### AC CODE

```cpp
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
int main(){
	int t=read();
	while(t--){
		int n;
		string s1,s2;
		cin>>n>>s1>>s2;
		int size=s1.size();
		for(int i=0;i<size;++i)if(s1[i]=='G')s1[i]='B';
		for(int i=0;i<size;++i)if(s2[i]=='G')s2[i]='B';
		if(s1==s2)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：XKqwq (赞：0)

### $\texttt{0.Translation}$

给你 $T$ 个 $2 \times n$ 的表格，每个表格用两个长度为 $n$ 的字符串表示，每个字符是 $\texttt{R}$、$\texttt{G}$、$\texttt{B}$ 中的一个。如果把 $\texttt{G}$ 和 $\texttt{B}$ 视为一个字符。对于每一个表格，请回答第一行与第二行是否完全相同。

### $\texttt{1.Key}$

既然把 $\texttt{G}$ 和 $\texttt{B}$ 视为一个字符，那么判断的时候可以当成一个字符来判断，或者把 $\texttt{G}$ 和 $\texttt{B}$ 统一换成一个字符再判断。

### $\texttt{2.Code}$

有错误请回复。

```cpp
#include <bits/stdc++.h>
using namespace std;

int T,n;
string s1,s2;
int main(){
	cin>>T;
	while(T--){
		bool flag=1;
		cin>>n>>s1>>s2;
		for(int i=0;i<n;i++){
			if(s1[i]=='B') s1[i]='G'; // 统一换成 G
			if(s2[i]=='B') s2[i]='G';
			if(s1[i]!=s2[i]){
				puts("NO");
				flag=0;
				break;
			}
			
		}if(flag) puts("YES");
	}
	return 0;
}
//AC!!!

```






---

## 作者：Lantrol (赞：0)

题目要求判断两个字符串是否相同。字符串中 `G` 和 `B` 会被视为相等。

既然视为相等，那么我们就扫一遍字符串暴力替换。把 `G` 和 `B` 替换为相同的字母，然后判断两个字符串是否相等。复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	string s1,s2;
	int n;
	cin>>n>>s1>>s2;
	for(int i=0;i<n;i++){
		if(s1[i]=='G'){
			s1[i]='B';
		}
		if(s2[i]=='G'){
			s2[i]='B';
		}
	}
	if(s1==s2){
		cout<<"YES"<<endl;
	}
	else{
		cout<<"NO"<<endl;
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```


---

## 作者：Kedit2007 (赞：0)

## 题目大意

给定两个字符串，仅包含 ```R```, ```G```, ```B``` 三种字符。判断在认为 ```G``` 和 ```B``` 相同的情况下两个字符串是否相同。

## 思路

直接按照题面模拟即可。一个比较好码的做法是把所有的 ```G``` 全都替换成 ```B``` 后直接判断相等。

## 参考代码

```cpp
bool Colorblindness(string a, string b)
{
	for (auto& c : a)
	{
		if (c == 'G') c = 'B';
	}
	for (auto& c : b)
	{
		if (c == 'G') c = 'B';
	}
	return a == b;
}
```

---

