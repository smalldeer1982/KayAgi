# 「Daily OI Round 3」Simple

## 题目背景

这是一道简单题。

## 题目描述

Acoipp 的某个软件的账号叫做 Svpoll，并且这款软件的账号与洛谷账号均不区分大小写，例如 $\texttt{SVPOLl}$ 和 $\texttt{svPOLL}$ 等价，$\texttt{aCoIPp}$ 和 $\texttt{Acoipp}$ 等价。

现在你想要知道某个账号名称是与 $\texttt{Acoipp}$ 等价，还是与 $\texttt{Svpoll}$ 等价，或者是与前两者都不等价。

## 说明/提示

#### 【样例解释 #1】

因为不区分大小写，所以 $\texttt{SVPOLL}$ 中的 $\texttt{V}$，$\texttt{P}$，$\texttt{O}$，$\texttt{L}$ 分别与 $\texttt{v}$，$\texttt{p}$，$\texttt{o}$，$\texttt{l}$ 等价，所以 $\texttt{SVPOLL}$ 与 $\texttt{Svpoll}$ 等价。

#### 【数据范围】

设 $|S|$ 为字符串长度，对于全部数据保证：$|S|=6$ 并且输入的字符串只包含大小写英文字母。

## 样例 #1

### 输入

```
SVPOLL```

### 输出

```
Genshin```

## 样例 #2

### 输入

```
ACoiPP```

### 输出

```
Luogu```

## 样例 #3

### 输入

```
RECOLL```

### 输出

```
Boring```

# 题解

## 作者：ACtheQ (赞：15)

字符串签到题目，~~（这算是本场比赛唯一一道能和 abc 对上难度的题了）~~。

题目一个简单的字符串大小写转换，不妨把所有的都转化为小写。

```
for(int i=0;i<s.size();i++)
{
	if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
}

```
接下来判断，注意要把判断的字符串也改成小写。

```c++

if(s=="acoipp") cout<<"Luogu";
else if(s=="svpoll") cout<<"Genshin";
else cout<<"Boring";

```

超级简单的签到题~~~

---

## 作者：Vct14 (赞：3)

既然不区分大小写，那么我们可以将其转换为大写再判断是否为 `SVPOLL` 或 `ACOIPP`。

字符串转大写方法可以见[此](https://www.luogu.com.cn/blog/Luogu-Official-Blog/solution-p8761)。这里主要介绍两种方法。

1. 使用 `toupper` 函数。它的功能是：若当前字母为小写，则将其转换为大写字母；否则原字符不变。详细说明见[此](https://www.runoob.com/cprogramming/c-function-toupper.html)。我们循环将字符串中的每一个字符转大写即可。
2. 使用 `transform` 函数。它的功能是将某操作应用于指定范围的每个元素。该函数的用法为 `transform(l1,r1,l2,op)`，`l1` 和 `r1` 分别指操作区间的开始和结尾，`l2` 指储存结果的容器，`op` 指要进行操作的一元函数对象。详细说明见[此](https://blog.csdn.net/zhang___bo/article/details/119389457)。这里我们需要使用 `towupper` 来转大写。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	string a;cin>>a;
	for(int i=0; i<6; i++) a[i]=toupper(a[i]);//转换
//	transform(a.begin(),a.end(),a.begin(),towupper);
	if(a=="SVPOLL") cout<<"Genshin";
	else if(a=="ACOIPP") cout<<"Luogu";
	else cout<<"Boring";
	return 0;
}
```

---

## 作者：KanaAqua_qwq (赞：1)

很简单的一道题。

### 思路：

将给出的账号名全部转为小写。


------------


### 代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main() {
	cin>>a;
	for(int i=0; i<a.length(); i++) {
		if(a[i]>='A'&&a[i]<='Z') {
			a[i]=a[i]+32;//转小写
		}
	}
	if(a=="acoipp") {//比较
		cout<<"Luogu"<<endl;
	} else if(a=="svpoll") {
		cout<<"Genshin"<<endl;
	} else {
		cout<<"Boring"<<endl;
	}
	return 0;
}
```




---

## 作者：Fp0cY1tZ6Nn4Rd_ (赞：1)

使用 `cctype` 这个头文件，代码会比较简洁。下面介绍里面的几个函数：
- `tolower(x)`：返回 `x` 的小写。
- `toupper(x)`：返回 `x` 的大写。
- `islower(x)`：判断 `x` 是否为小写字母。
- `isupper(x)`：判断 `x` 是否为大写字母。

使用这些函数，代码就会变得简洁得多。将整个字符串全部转为小写后判等即可。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cctype>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(isupper(s[i])) s[i]=tolower(s[i]);
//      if(islower(s[i])) s[i]=toupper(s[i]);
    }
    if(s=="acoipp") cout<<"Luogu\n";
    else if(s=="svpoll") cout<<"Genshin\n";
    else cout<<"Boring\n";
    return 0;
}
```

---

## 作者：newbieTroll (赞：1)

~~好吧我只会签到。~~

可以将输入的字符串全部转成小写，然后跟 `acoipp` 和 `svpoll` 分别比较即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	string s;
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;++i){
		if('A'<=s[i]&&s[i]<='Z'){
			s[i]+=32;
		}
	}if(s=="acoipp") cout<<"Luogu";
	else if(s=="svpoll") cout<<"Genshin";
	else cout<<"Boring";
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

将所有的字母转成小写即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s,a="acoipp",b="svpoll";
int main()
{
	cin>>s;
	int n=s.length();
	for(int i=0;i<n;i++)//转小写
		if(s[i]>='A'&&s[i]<='Z')
			s[i]=s[i]-'A'+'a';
	if(s==a) cout<<"Luogu";//string可以快速比较
	else if(s==b) cout<<"Genshin";
	else cout<<"Boring";
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[P10125 「Daily OI Round 3」Simple](https://www.luogu.com.cn/problem/P10125)

### 思路

我都不知道这题有什么好说的。

最快的方法就是把所有字符转化为大写字母然后挨个比对就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
std::string s;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>s;
    for(int i=0;i<s.size();++i)
        if('a'<=s[i]&&s[i]<='z')
            s[i]-=32;
    if(s=="SVPOLL") cout<<"Genshin";
    else if(s=="ACOIPP") cout<<"Luogu";
    else cout<<"Boring";
    return 0;
}
```

---

