# Internet Address

## 题目描述

Vasya is an active Internet user. One day he came across an Internet resource he liked, so he wrote its address in the notebook. We know that the address of the written resource has format:

 <protocol>://<domain>.ru\[/<context>\]where:

- <protocol> can equal either "http" (without the quotes) or "ftp" (without the quotes),
- <domain> is a non-empty string, consisting of lowercase English letters,
- the /<context> part may not be present. If it is present, then <context> is a non-empty string, consisting of lowercase English letters.

If string <context> isn't present in the address, then the additional character "/" isn't written. Thus, the address has either two characters "/" (the ones that go before the domain), or three (an extra one in front of the context).

When the boy came home, he found out that the address he wrote in his notebook had no punctuation marks. Vasya must have been in a lot of hurry and didn't write characters ":", "/", ".".

Help Vasya to restore the possible address of the recorded Internet resource.

## 说明/提示

In the second sample there are two more possible answers: "ftp://httpruru.ru" and "ftp://httpru.ru/ru".

## 样例 #1

### 输入

```
httpsunrux
```

### 输出

```
http://sun.ru/x
```

## 样例 #2

### 输入

```
ftphttprururu
```

### 输出

```
ftp://http.ru/ruru
```

# 题解

## 作者：qinshi0308 (赞：6)

### 这道题就是一道简单的模拟

#### 思路：
首先判断一下输入的网址开头是 ``` ftp://```还是```http://```

```cpp
int i=0;
if(arr[0]=='h'){
	cout<<"http://";
	i+=4;//因为前面占了四位，所以循环变量i+4
}else{
	cout<<"ftp://";
	i+=3;//同上，占了三位，+3
}
```
然后输出```http://```或```ftp://```后面的内容
```cpp
bool flag=1;
int x=i;
for(;i<len;i++){
	if(arr[i]=='r'&&arr[i+1]=='u'&&flag&&i!=x){
    /*如果当前字母是“r”并且下一个字母是“u”并且前面没输出过“ru”并且“ru”前面有字母，就输出*/
		flag=0;
		if(i==len-2){//如果是最后一个就不输出“/”
			cout<<".ru";
		}else{
			cout<<".ru/";
		}
		i++;
	}else{
		cout<<arr[i];//不满足条件，输出当前字母
	}
}
```
### 完整代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
char arr[100];
int main(){
	cin>>arr;
	int len=strlen(arr);
	int i=0;
	if(arr[0]=='h'){
		cout<<"http://";
		i+=4;
	}else{
		cout<<"ftp://";
		i+=3;
	}
	bool flag=1;
	int x=i;
	for(;i<len;i++){
		if(arr[i]=='r'&&arr[i+1]=='u'&&flag&&i!=x){
			flag=0;
			if(i==len-2){
				cout<<".ru";
			}else{
				cout<<".ru/";
			}
			i++;
		}else{
			cout<<arr[i];
		}
	}
	return 0;
}

```
### 于是，一道灰题就做完了
### the end

---

## 作者：_easy_ (赞：1)

# 思路
首先判断开头是 $\texttt{http}$ 还是 $\texttt{ftp}$。如果第一个是 $\texttt{h}$ 就是 $\texttt{http}$，否则就是 $\texttt{ftp}$。
```
if(s[0]=='f'){
	cout<<"ftp://";
	a=3;
}else{
	cout<<"http://";
	a=4;
}
```
其次直接输出 $\texttt{http}$ 或 $\texttt{ftp}$ 后一直到 $\texttt{.ru}$ 就行了。
```
for(;a<len;a++){
	if(s[a]=='r'&&s[a+1]=='u'){
		break;
	}else{
		cout<<s[a];
	}
}
```
最后只需要直接输出后面字符就行了。
```
cout<<"/";
while(a^len){
	a++;
	cout<<s[a];
}
```
# 代码
主要代码已分段给出，中间有一些想输出 $\texttt{.ru}$ 的次要代码没有给出。

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF245B)

# 题意简述

Vasya 在学校上信息课时发现了一个很有意思的网站，并把他记录了下来。然而，他实在是太粗心了，以至于等到他回到家才发现，他写下的网址没有打标点符号，只有由一大堆英文字母组成的字符串！

Vasya 只记得，他想要写下的网址的格式是 `<protocol>://<domain>.ru[/<context>]`，其中：

- `<protocol>` 可以是 `http`，也可以是 `ftp`。
- `<domain>` 是一个由小写字母构成的非空字符串。
- `/<context>` 可有可无。如果有这一部分的话，那么 `<context>` 是一个由小写字母构成的非空字符串。

现在，Vasya 会告诉你他写下的字符串 $s$，请你帮助 Vasya 还原出这个网址。如果有多个网址符合要求，你只需要告诉 Vasya 任意一个符合要求的网址即可。

# Solution

简单字符串题。

首先，判断出 `<protocol>` 部分是 `http` 还是 `ftp`。代码：

```cpp
if(s[0]=='h') printf("http://");
else if(s[0]=='f') printf("ftp://");
```

然后，从此位置一直判断，直到找到 `.ru` 为止，将前边的字符全部当作 `<domain>` 部分输出。代码：

```cpp
for(int i=0; i<s.size(); i++) {
		if(s[i]=='r'&&s[i+1]=='u') break;
		else cout<<s[i];
}
```
最后，判断后面还有没有字符，即有没有 `/<context>` 部分，如果没有，结束程序；如果有，输出。代码：

```cpp
if(sum==s.size()-1) return 0;
printf("/");
for(int i=sum+1; i<s.size(); i++) cout<<s[i];
```

核心程序都放出来了，完整代码就不放了。

By 2022.7.4 蒟蒻的第二十三篇题解

---

## 作者：TheCliffSwallow (赞：0)

### 思路
简单模拟，先判断是 `ftp` 开头还是 `http` 开头，并用一变量记录位置。
```cpp
if(str[0]=='h'){
	cout<<"http://";
	sta=4;
}
else{
	cout<<"ftp://";
	sta=3;
}
```
再从这个位置开始一直输出到 `.ru`，因为有多种情况且输出任意一种情况即可，所以我们找到一种情况后就可以跳出循环。
```cpp
for(int i=sta+1;i<sz-1;i++){
	if(str[i]=='r'&&str[i+1]=='u'){
		for(int j=sta;j<i;j++){
			cout<<str[j];
		}
		cout<<".ru";
		now=i+2;
		break;
	}
}
```
最后判断是否有 `/<context>` 并选择输出即可。
```cpp
if(now<=sz-1){
	cout<<'/';
	for(int i=now;i<sz;i++){
		cout<<str[i];
	}
}
```
### 完整代码
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
using namespace std;
string str;
int sta,now;//sta 记录 http 或 ftp 之后的那个位置，now 记录 ru 及之前字符串长度
int main(){
	std::ios::sync_with_stdio(false);
	cin>>str;
	int sz=str.size();
	if(str[0]=='h'){
		cout<<"http://";
		sta=4;
	}
	else{
		cout<<"ftp://";
		sta=3;
	}
	for(int i=sta+1;i<sz-1;i++){
		if(str[i]=='r'&&str[i+1]=='u'){//判断是否是 ru
			for(int j=sta;j<i;j++){
				cout<<str[j];
			}
			cout<<".ru";
			now=i+2;
			break;//找到一种情况就可以跳出循环了
		}
	}
	if(now<=sz-1){//判断是否还有 context
		cout<<'/';//放在判断里，如果没有 context 不能输出多余的‘/’
		for(int i=now;i<sz;i++){
			cout<<str[i];
		}
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

**Solution**

简单模拟题。

如果第一个字符是 `f` 那么就是 `ftp`，否则就是 `http`。然后枚举到第一个为 `ru` 的地方，中间的就是 `domain` 部分。`ru` 后面的部分全都看做是 `context` 部分即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    int st = 0;
    if (s[0] == 'f') {
        st = 3;
        printf ("ftp://");
    }
    else {
        st = 4;
        printf ("http://");
    }
    int id = 0x3f3f3f3f;
    for (int i = st + 1; i < (int) s.size() - 1; i ++) {
        if (s[i] == 'r' && s[i + 1] == 'u') {
            for (int j = st; j < i; j ++) cout << s[j];
            cout << ".ru";
            id = i + 2;
            break;
        }
    }
    if (id <= (int) s.size() - 1) {
        cout << '/';
        for (int i = id; i < (int) s.size(); i ++) cout << s[i];
    }
    cout << '\n';
    return 0;
}

```


---

## 作者：A524 (赞：0)

题目大意：地址的正确形式为“$ <....>://<....>.ru/<....> $”，$ <....> $表示一些小写字母，第一个$ <....> $只为“$ http $”或“$ ftp $”。第二个$ <....> $不能为空。第三个$ <....> $如果为空，则前面“$ / $”不用输出。现在给你一个没有任何标点的地址，让你求出该地址的其中一种正确形式。

思路：直接进行模拟。注意：第二个$ <....> $不能为空，所以，查找"$ ru $"最好从后往前查询，防止第二个$ <....> $为空（我就是这样错了一次....）。还要注意：第三个$ <....> $如果为空，则前面“$ / $”不用输出。

贴上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[55];int n,i;
int main(){
	scanf("%s",s);n=strlen(s);
	if (s[0]=='f'&&s[1]=='t'&&s[2]=='p')
		printf("ftp://"),i=4;
	else printf("http://"),i=5;
	printf("%c",s[i-1]);i++;
	for (;i<n;i++)
		if (s[i-1]=='r'&&s[i]=='u')
		 	break;
		else printf("%c",s[i-1]);
	if (i!=n-1) printf(".ru/");
	else printf(".ru");
	for (i++;i<n;i++)
		printf("%c",s[i]);
	return 0;
}
```


---

