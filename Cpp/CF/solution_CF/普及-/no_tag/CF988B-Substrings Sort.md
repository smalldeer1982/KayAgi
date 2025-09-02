# Substrings Sort

## 题目描述

给定一个数n和n个字符串，求一个重新排列，对于新排列中的每个字符串
都满足在它前面的串都是它的子串。 


感谢@南方不败 提供翻译

## 样例 #1

### 输入

```
5
a
aba
abacaba
ba
aba
```

### 输出

```
YES
a
ba
aba
aba
abacaba
```

## 样例 #2

### 输入

```
5
a
abacaba
ba
aba
abab
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
qwerty
qwerty
qwerty
```

### 输出

```
YES
qwerty
qwerty
qwerty
```

# 题解

## 作者：Egg_eating_master (赞：3)

感觉楼下的做法太复杂了

首先，如果字符串$a$是$b$的子串，那么$a$的长度一定不超过$b$。

根据这个结论，我们想到，把所有字符串排一次序，然后对于每一个$s_i$，都循环判它之前所有的$s_j$是不是它的子串就好了。

但这个做法还可以优化。

在前$i$个字符串满足题意时，$s_1$~$s_{i-1}$一定都是$s_i$的子串。

那么，如果$s_i$也是$s_{i+1}$的子串，对于任意的$s_j(j<i)$，因为因为$s_j$是$s_i$的子串，所以$s_j$是$s_{i+1}$的子串。

那么，只需要判断$s_i$是否是$s_{i+1}$的子串就行了。

Q：如何快速判断？

A：字符串自带的$find$函数！

代码实现实际上很简单。
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s[101];
bool cmp(string a,string b){
	return a.size()<b.size()
	     ||a.size()==b.size()&&a<b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	    cin>>s[i];
	sort(s+1,s+1+n,cmp);//先给所有字符串排序
	for(int i=2;i<=n;i++){
		int x=s[i].find(s[i-1]);
		if(x==-1){//如果s[i-1]不是s[i]的子串
			cout<<"NO"<<endl;//那么直接输出NO
			return 0;//拜拜了您嘞
		}
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++)
	    cout<<s[i]<<endl;//根据题意输出就行了
	return 0;//Happy Ending~
} 
```


---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF988B)

# 前排芝士：
[sort 排序](https://baike.baidu.com/item/sort%E5%87%BD%E6%95%B0/11042699?fr=aladdin)

[ASCII 码](https://baike.baidu.com/item/ASCII/309296?fr=aladdin)
# 思路：

将每个字符串按照某些条件排序，看前一个字符串是否是当前字符串的子串，如果不是则直接输出

判断的详细注释见代码

# AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(string s1,string s2){//自定义排序函数 
	if(s1.size()!=s2.size()){//当两个字符串长度不相等 
		return s1.size()<s2.size();//将长度小的排在前面 
	}else{//两个字符串长度相等 
		return s1<s2;//将 ASCII 小的字符串排在前面 
	}
}
int main(){
	int n;
	string a[105];
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=2;i<=n;i++){//从 2 开始枚举 
		if(a[i].find(a[i-1])==-1){//在此字符串中找不到前一个字符串 
			cout<<"NO\n";//直接输出 
			return 0;//结束程序 
		}
	}
	cout<<"YES\n";//新排列中的每个字符串都满足在它前面的串都是它的子串 
	for(int i=1;i<=n;i++)cout<<a[i]<<endl;//输出每一个字符串 
	return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：0)

前排芝士：

Q ：字符串是按什么排的？

A ：一般情况下使用 STL 的 `sort` 来按字典序排序。

本题是要先保证长度一样，长度不一样排前面，一样的话再按字典序排。

其中自定义的 `cmp` 函数可以这么写：

```cpp
bool cmp (string a, string b)
{
	if (a.length() != b.length()) return a.length() < b.length();
	return a < b;
}
```

排序时再这么写：

`sort(s + 1, s + n + 1, cmp);`

思路分析：

我们观察到样例是按短到长的，无论咋样都先排序！然后再一个个串判断是否包含。

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool cmp (string a, string b)
{
	if (a.length() != b.length()) return a.length() < b.length();
	return a < b;
}
string s[105];

int main()
{
    int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	    cin >> s[i];
	sort(s + 1, s + n + 1, cmp);
	for (int i = 2; i <= n; i++)
	{
		if (s[i].find(s[i - 1]) == -1)
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	for (int i = 1; i <= n; i++)
	    cout << s[i] << endl;
	return 0;
}
```

新手泄题解，望通过。

---

## 作者：shAdomOvO (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF988B)

这道题其实并不难，只要想到方法，很容易写出来。

### 排序方式
```cpp
bool cmp(string m,string n){
	return m.size()<n.size();
}
```
### 思路

首先，要进行排序，因为后面的要包含前面的所有字符串，所以前面字符串的

长度肯定会小于等于后面字符串的串的长度，所以把小字符串放在前面。

而因为长度相等的字符串只有一样才能包含，所以一样长度的如何排序没有影响。

最后在从后往前扫，是否都包含就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[110];
int n,i,j,t,tt;
bool aa=true;
bool cmp(string m,string n){
	return m.size()<n.size();
}
int main(){
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,cmp);//排序
	for(i=n;i>=1;i--){//判断是否包含
		for(j=i-1;j>=1;j--){
			int alen=a[i].size();
			int blen=a[j].size();
			for(int k=0;k<=alen-blen;k++){
				aa=true;
				for(t=k,tt=0;tt<blen;t++,tt++){
					if(a[i][t]!=a[j][tt]){
						aa=false;
						break;
					}
				}
				if(aa==true)break;
			}
			if(aa==false){//如果有一个不包含，可以直接结束程序
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<"YES"<<endl;
	for(i=1;i<=n;i++)cout<<a[i]<<endl;
	return 0;//完结撒花
} 
```








---

## 作者：Dream_It_Possible (赞：0)

cf暴力题，无脑暴力即可。

对于每个字符串，如果符合要求，那定是按长度排过序的序列，我们就可以对他们的长度sort,然后两两比对。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
string s[105];
bool cmp(string A,string B)
{
	return A.size()<B.size();
}
int main()
{
	int n,i,j,k;
	cin>>n;
	for (i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	sort(s+1,s+n+1,cmp);
	for (i=2;i<=n;i++)
	{
		int ok=0;
		for (j=0;j<s[i].size()-s[i-1].size()+1;j++)
		{
			int l=j,bo=0;
			for (k=0;k<s[i-1].size();k++,l++)
			{
				if (s[i][l]==s[i-1][k])
				{
					;
				}
				else
				{
					bo=1;
					break;
				}
			}
			if (bo==0)
			{
				ok=1;
				break;
			}
		}
		if (ok==0)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES"<<endl;
	for (i=1;i<=n;i++)
	cout<<s[i]<<endl;
	return 0;
}
```

---

