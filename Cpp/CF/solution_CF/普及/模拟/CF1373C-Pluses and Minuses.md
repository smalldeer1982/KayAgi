# Pluses and Minuses

## 题目描述

You are given a string $ s $ consisting only of characters + and -. You perform some process with this string. This process can be described by the following pseudocode:

 ```
res = 0
for init = 0 to inf
    cur = init
    ok = true
    for i = 1 to |s|
        res = res + 1
        if s[i] == '+'
            cur = cur + 1
        else
            cur = cur - 1
        if cur < 0
            ok = false
            break
    if ok
        break
```


Note that the $ inf $ denotes infinity, and the characters of the string are numbered from $ 1 $ to $ |s| $ .

You have to calculate the value of the $ res $ after the process ends.

## 样例 #1

### 输入

```
3
--+-
---
++--+-```

### 输出

```
7
9
6```

# 题解

## 作者：Lyz09 (赞：2)

## CF1373C 题解

[（洛谷）原题传送门](https://www.luogu.com.cn/problem/CF1373C) 

[（CF）原题传送门](https://codeforces.com/contest/1373/problem/C) 

# 思路

首先要思考这个伪代码究竟在干什么，所以要先分析伪代码。

## 伪代码翻译（C++版）

```cpp
res=0
for(int init=0;;init++)//init为预估多出来的数量。 
{
    int cur=init
    bool ok=true
    for(int i=0;i<s.size();i++)//遍历字符串。
    {
        res++;
        if(s[i]=='+')
         cur++;
        else
         cur--;
        if(cur<0)//多出来的减号多于预估值。 
        {
        	ok=false;
        	break;
		}
	}
    if(ok)
     break
}
```

伪代码大致意思：从头开始遍历字符串，当在位置 $i$ （ $i$ 从 $1$ 开始）时，如果 $s_i$ 为 $-$ 号，则将 $res$ 加上 $i$ ,如果 $s_i$ 为 $+$ 号，则抵消掉后面最靠近自己的 $-$ 号（不可以重复抵消）。

既然已经知道了伪代码的作用，那接下来就很简单了。只需要根据伪代码的意思来计算 $res$ 的值就行了。这时候可能会有同学问：为什么不能直接模拟？~~当然不行！~~ 直接模拟肯定会超时，接近于 $O(10^{12})$ 。

# 代码

根据上面的思路，即可想到用一个变量 $l$ 来存储算式表达的值，用 $g$ 来存储 $l$ 到达何值时 $res$ 加上 $i$ 。

这样，代码部分就完成了。

## AC  CODE
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long ans,len,t,g,l;//最好开 long long 。
char s[1000001];//存储字符串，也可以用 string 类型来存储。
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		scanf("%s",&s);
		len=strlen(s);
		l=0;
		ans=0;
		g=-1;
		for(int i=0;i<len;i++)//枚举每个位置（每个 i ）
		{
			if(s[i]=='-')
			 l--;
			else
			 l++;//抵消减号。
			if(l==g)
			{
				g--;//因为减号在不被抵消的情况下会让 l 的值越来越小，所以每当答案被加上一次的时候， g 都要减 1 。
				ans+=i+1;//因为这里的位置是从 0 开始的，所以要 +1 。
			}
		}
		printf("%lld\n",ans+len); //加上 len 是因为在伪代码中只有 cur 在大于 0 是才会退出，还会再遍历一遍字符串，所以要加上 len 。
	}
}
```


---

## 作者：Keith_2006 (赞：1)

## CF1373C Pluses and Minuses 题解

#### 一道有点奇怪的题目，不过难度不是很高。

### 题目大意

给你一串伪代码，输入一串仅包含 `+` 和 `-` 的字符串，求按照伪代码执行后变量 `res` 的值。

---

### 题目分析

显然，如果只是把伪代码翻译成 C++ 代码，那么一定会超时。

所以要考虑伪代码在究竟干什么。

我们发现，如果在内层循环中，**没有出现 $cur<0$ 的情况**，那么这段代码就会 break 出去然后结束。

再考虑 $cur$ 值如何变化。容易发现，在内层循环中遍历字符串，出现加号则 `cur++`，出现减号则`cur--`。

如果把加号看成 $1$，减号看成 $-1$，那么对这个字符串做**前缀和**的结果就是 $cur$ 在那一位的值。

结合外层循环的代码，可知**如果在某一时刻，$init+cur<0$，将会退出内层循环继续执行程序**。此时 $res$ 增加的值就是出现 $init+cur<0$ 的位置。

---

### 代码实现

根据上面的分析，我们只需要找到每一个小于 $0$ 的前缀和数组值（这样才有可能因为这个值而跳出内层循环），记录第一次出现的位置并把它加到答案上。

因为最后一次遍历会遍历整个字符串，所以答案还要加上 $n$。

注意结果要开 `long long`。

附上丑陋的代码（似乎可以简化很多）

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>

#define ll long long

using namespace std;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}

const int N=1e6+5;

int s[N],first[N*2];

int main() {
	int t=read();
	while (t--) {
		memset(first,0,sizeof(first)); //多组数据别忘了 memset
		memset(s,0,sizeof(s));
		char c[N];
		scanf("%s",c+1);
		int n=strlen(c+1);
		for (int i=1;i<=n;i++) {
			if (c[i]=='+') s[i]=s[i-1]+1;
			else s[i]=s[i-1]-1;
		}
		ll ans=0;
		for (int i=1;i<=n;i++) {
			if (s[i]<0&&!first[-s[i]]) {
				first[-s[i]]=i; //对数组值取相反数存下来当做标记
				ans+=(ll)i;
			}
		}
		ans+=(ll)n;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

完结撒花 qwq

如果对你有帮助的话不妨点个赞，有问题也可以尽管提出。



---

## 作者：_jimmywang_ (赞：1)

### 题意：

给出下列程序（翻译成c++版的）：

```cpp
int res=0;
for(int init=0;;init++){
	int cur=init;
	bool ok=true;
	for(int i=0;i<s.size();i++){
		res++;
		if(s[i]=='+')cur++;
		else cur--;
		if(cur<0){
			ok=false;
			break;
		}
	}
	if(ok)break;
}
```
然后给定字符串$s$,求程序结束后$res$的值。

### 分析：

我们发现这个程序，其实就是当$c_i$(前缀和)$+cur<0$时，$res+=i+1$

比如样例1：

```
  原串：-  -  +  -
  翻译：-1 -1 1 -1
前缀和：-1 -2 -1 -2 (-inf)
```
那么$cur=0$时，$cur+c_0<0$,于是$res+=0+1$

$cur=1$时，$cur+c_1<0$,于是$res+=1+1$

$cur=2$时，$cur+c_5<0$,但是5>3，于是$res+=3+1$

所以总和就是7.

那么，我们设置断点，再在断点处加上就行了。

其实就几句话：

```
f(i,0,s.size()-1)c[i]=max((ll)0,-c[i]);
ll mx=0;
f(i,0,s.size()-1)if(c[i]>mx)ans+=i+1,mx=c[i];
```
然后加上s.size()就好了

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll t;
ll c[1000010];
int main(){
	t=d;
	while(t--){
		string s;
		cin>>s;
		memset(c,0,sizeof(c));
		ll ans=0;
		f(i,0,s.size()-1){if(s[i]=='-')c[i]=c[i-1]-1;else c[i]=c[i-1]+1;}
		f(i,0,s.size()-1)c[i]=max((ll)0,-c[i]);
		ll mx=0,cmp=0;
		f(i,0,s.size()-1)if(c[i]>mx)ans+=i+1,mx=c[i];
		cout<<ans+s.size()<<endl;
	}
	return 0;
}
```


---

## 作者：cyh_toby (赞：1)

# 题意

原题：[CF1373C 【Pluses and Minuses】](https://www.luogu.com.cn/problem/CF1373C)

# 分析

把题目给的伪代码稍微转化一下，就是说，对于给定的 $01$ 序列 $a$ 的前缀和序列 $s$ ，从前往后遍历，一旦遇到一个位置 $i$ ，使得 $s_i < 0$ ，就把整个 $s$ 序列通通加上 $1$ （即把这个小于 $0$ 的地方补上去，使之大于等于 $0$ ；而由于是 $01$ 串的前缀和，只需要加 $1$ 达成目的），然后答案 $res$ 加上 $i$ 。

其中”把整个序列通通加上 $1$“ 可以用题目中 $cur$ 的方式处理。

将上述转化为代码即可，算法时间复杂度线性。

# 源码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;
typedef long long ll;

int n;
char s[N];
ll ans;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		
		scanf("%s", s+1);
		n = strlen(s+1);
		int sum = 0, cur = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i] == '+')
				sum++;
			else
				sum--;
			if (sum + cur < 0) {
				ans += i;
				cur++;
			}
		}
		
		printf("%lld\n", ans + n);
	}
	
	return 0;
}
```

---

## 作者：b6e0_ (赞：0)

[CF题面传送门](https://codeforces.com/contest/1373/problem/C) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1373C) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1373C)

这段伪代码用C++来表示就是：
```cpp
res=0;
for(init=0;;init++)
{
	cur=init;
	ok=true;
	for(i=0;i<s.size();i++)
	{
		res++;
		if(s[i]=='+')
			cur++;
		else
			cur--;
		if(cur<0)
		{
			ok=false;
			break;
		}
	}
	if(ok)
		break;
}
//最终要你输出这段程序中的res变量
```
要是模拟这段程序，时间复杂度为$O(|s|^2)$，肯定超时。理解程序意思，发现外循环每一次其实在找`-`的个数减去`+`的个数为$-1,-2,-3\cdots$的位置。很明显，这些位置是单调的，扫一遍就可以了，并不用像伪代码里一样一次又一次地循环找。

具体实现细节看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		int i,sum=0,fi=-1,ans=0;//sum为+的个数减-的个数，fi为当前要找的差，ans为最终答案
		cin>>s;
		for(i=0;i<s.size();i++)
		{
			if(s[i]=='+')
				sum++;
			else
				sum--;
			if(sum==fi)//找到了
			{
				ans+=i+1;
				fi--;
			}
		}
		cout<<ans+s.size()<<endl;//伪代码中最后一次循环是从头扫到尾的，所以要额外加上|s|
	}
	return 0;
}
```
时间复杂度为$O(|s|)$。

---

