# Different is Good

## 题目描述

A wise man told Kerem "Different is good" once, so Kerem wants all things in his life to be different.

Kerem recently got a string $ s $ consisting of lowercase English letters. Since Kerem likes it when things are different, he wants all substrings of his string $ s $ to be distinct. Substring is a string formed by some number of consecutive characters of the string. For example, string "aba" has substrings "" (empty substring), "a", "b", "a", "ab", "ba", "aba".

If string $ s $ has at least two equal substrings then Kerem will change characters at some positions to some other lowercase English letters. Changing characters is a very tiring job, so Kerem want to perform as few changes as possible.

Your task is to find the minimum number of changes needed to make all the substrings of the given string distinct, or determine that it is impossible.

## 说明/提示

In the first sample one of the possible solutions is to change the first character to 'b'.

In the second sample, one may change the first character to 'a' and second character to 'b', so the string becomes "abko".

## 样例 #1

### 输入

```
2
aa
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
koko
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
murat
```

### 输出

```
0
```

# 题解

## 作者：江山_远方 (赞：3)

~~咳咳，真搞不懂这题为啥是绿题，橙题还差不多~~

废话不多说，闲话不多讲，简而言之，言而总之，今天我们来分析这道题

首先，我们知道了字符串长度，根据抽屉原理，假如长度>26，则放入'a'~'z'这26个抽屉里，必定至少有一个抽屉会装两个及两个以上字母，所以无论怎么变化都会失败。

而<=26个的，才可以成功，对于'a'~'z'，用桶记录一下个数，然后i->'a'~'z'循环，如果这个字母的个数>1 就要变换b[i]-1个字母，所以ans+=b[i-1],分析到这里，也差不多该上代码了，有请 Mr.代码 上场！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string st;
int b[200];
int main()
{
	cin>>n;
	getline(cin,st);
	getline(cin,st);
	if(n>26){cout<<-1;return 0;}
	for(int i=1;i<=n;i++)b[st[i-1]]++;
	for(int i='a';i<='z';i++)if(b[i]>1)ans+=b[i]-1;
	cout<<ans;
	return 0; 
} 
```
对 这样就可以AC了 又水一道绿题！

---

## 作者：Corsair (赞：1)

本蒟蒻第一次发题解，希望大家见谅，多多指教。
其实用个桶就过了，最后的判断是个坑。

------------

下面直接上代码：
```
#include<bits/stdc++.h>
using namespace std;
int l[100];//桶计数 
int main()
{
	char ch;
	int n,ans=0,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		l[ch-96]++;//放入桶计数 
	}
	for(int i=1;i<=26;i++)
	{	
		if(l[i]!=0) s++;//不能改变到的字母 
		if(l[i]>=2) ans+=l[i]-1;//要改变的字母的和 
	}
	if(ans+s>26) cout<<"-1"<<endl;//注意是>26 我在这被卡了几次 
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：jijidawang (赞：0)

## 题面简述

> 给你一个 $n$ 位字符串（全是小写字母）（$1\le n\le 10^5$）。让你求至少要多少次，才能让字符串中的字母都不相同（只能改变成字母）。 如果改变不了，输出 `-1`。

## 算法分析

如果字符串长度 $>26$ 显然不行。

我们所做的任务其实就是求原字符串长度 $-$ 去重后字符串长度。

### 玄学做法

排序后直接`for`循环遍历即可。

- 如果排序是快排：$\mathcal{O}(n\log n)$；
- 如果排序是计数：$\mathcal{O}(n)$，但是还不如用下面的方法；
- 如果排序是基数：$\mathcal{O}(n)$。

### 正确做法

我们可以离散化后用一个桶标记。

因为它们都是小写字母，离散化用`-'a'`代替就行。

### STL 大法

用 STL 的 `string`，它善意的提供了`size()`（`length()`）（取长度）函数，还有一个友好的`unique`（去重，按 STL 常态返回迭代器），所以我们可以一句话解决：
```cpp
cout<<(str.size()>26?-1:(unique(str.begin(),str.end())-str.begin()-str.length()));
```

---

## 作者：封禁用户 (赞：0)

题目传送门：[CF672B Different is Good](https://www.luogu.com.cn/problem/CF672B)

**题解：** 其实这题很简单，将字符串排一下序，假如前一个不等于下一个，$ans++$就好了。

**关于无解** ：因为小写字母只有$26$个，所以当$n$大于$26$的时候就输出"$-1$"。

$Code:$

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
   long long s=0;bool w=1;char ch=getchar();
   while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,ans;
string s;
int main(){
    n=read();
    if(n>26){//n>26，无解的情况
        printf("-1");
        return 0;
    }
    cin>>s;
    sort(s.begin(),s.end());//排一下序
    for(int i=0;i<n-1;i++)
        if(s[i]==s[i+1])ans++;
    printf("%d",ans);
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这一题非常的水。

想一想，每一个字母都不一样，那么最多怎么弄也只能弄到26个长度，对吧，毕竟只有26个字母，全用上长度为26。

如果长度小于26，那么再用一个bool数组来判断有没有出现过。出现过那么他就必须改变

代码如下↓↓↓

```
#include <bits/stdc++.h>
using namespace std;
char a[100005];
bool test[500];
int f=0,n;
int main()
{
    cin>>n;//输入这个字符串 
    for(int i=0;i<26;i++)//把26个字母的bool数组全部变为false 
    test[i]=false;
    cin>>a;
    if(strlen(a)>26)//长度>26就做不到了 
    {
    	cout<<"-1";//输出-1 
    	return 0;//千万不要忘了停掉程序 
	}
    for(int i=0;i<strlen(a);i++)
    {
        if(test[a[i]-'a']==false)//a~z的数组下标为0~25 
        test[a[i]-'a']=true;//没有出现过就标记一下 
        else//出现过了 
        f++;//他要改变，答案++ 
    }
    cout<<f;//输出变换的次数 
    return 0;
}
```

---

