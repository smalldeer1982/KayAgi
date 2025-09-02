# Parity Game

## 题目描述

你和北极熊 Alice 和北极熊 Bob 一起钓鱼。他们等鱼上钩等得很无聊，于是想到了一个游戏来消磨时间。首先，Alice 和 Bob 分别写下一个 01 串（只包含”0”和“1”的字符串）$a$ 和 $b$，然后你可以通过两种操作尝试将 $a$ 变成 $b$：

- 将 $parity(a)$ 添加到 $a$ 的末尾。例如：$1010 \rightarrow 10100$。

- 删除 $a$ 的第一个字符。例如：$1001 \rightarrow 001$。若 $a$ 为空串则无法进行此操作。

你可以进行任意多次操作。现在请你求出是否能将 $a$ 变为 $b$。

如果一个 01 串中有奇数个 $1$，那么这个 01 串的 $parity$ 值是 $1$，否则是 $0$。

## 样例 #1

### 输入

```
01011
0110
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0011
1110
```

### 输出

```
NO
```

# 题解

## 作者：Eternal_Blue (赞：6)

# ~~这道题看似很难，其实很水。。。~~ 
## 思路如下：
自己模拟几遍后，会发现如下结论：  
#### 记a串的1的个数为na，b串1的个数为nb，那么如果na>=nb，a串就一定可以转化为b串。
####  如果na为奇数且na+1>=nb，那么a串也一定可以转化为b串。
####  其他情况，a串一律无法转化为b串
###  以下是证明：
当na为偶数时，我们假设他开头没有前导零（因为有前导零也可以删掉），那么他开头一定是1（废话），这时候我们可以做两件事:  
1、把开头的1删掉  
2、在a串末尾加任意个0并把开头的1移动到末尾（例如：101-->010.....001）  
然后想一想就会发现，我们可以把这样的a串转化为任何有<=na个1的串  
  
当na为奇数时，可以把它看做一个有na+1个1的字符串，所以此时a串可以转化为任何一个有<=na个1的串  
  
###  程序实现其实很简单
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 100010
char str1[MAXN],str2[MAXN];
int i,j,k,m,n,a,b;
int main(){
	scanf("%s%s",str1+1,str2+1);
	n=strlen(str1+1),m=strlen(str2+1);
	a=b=0;
	for(i=1;i<=n;i++) a+=str1[i]-48;
	for(i=1;i<=m;i++) b+=str2[i]-48;
	a+=a%2;
	if(a>=b) printf("YES\n"); else printf("NO\n");
	return 0;
}
```

---

## 作者：Wind_Smiled (赞：1)

## 题意
你和北极熊 Alice 和北极熊 Bob 一起钓鱼。他们等鱼上钩等得很无聊，于是想到了一个游戏来消磨时间。首先，Alice 和 Bob 分别写下一个 01 串（只包含 $0$ 和 $1$ 的字符串）$a$ 和 $b$，然后你可以通过两种操作尝试将 $a$ 变成 $b$：

- 将 $parity(a)$ 添加到 $a$ 的末尾。例如：$1010 \rightarrow 10100$。

- 删除 $a$ 的第一个字符。例如：$1001 \rightarrow 001$。若 $a$ 为空串则无法进行此操作。

你可以进行任意多次操作。现在请你求出是否能将 $a$ 变为 $b$。

如果一个 01 串中有奇数个 $1$，那么这个 01 串的 $parity$ 值是 $1$，否则是 $0$。

## 分析
对于任意字符串 $a$,其对应 $parity(a)$ 或者为 $1$，或者为 $0$。

对于初始 $parity(a)=0$ 的情况，操作可以将 $0$ 添加至其末尾，或者删除第一个字符。

所以 $a$ 可以将其首位删去，放置最后一个 $0$。

如数据 $1$：

```
101
010
```
显然，符合上文所述。

有：

$101 \rightarrow 1010 \rightarrow 010$

如数据 $2$:

```
101
011
```

有：

$101 \rightarrow 01 \rightarrow 011$

再来一组找规律：

```
101
111
```

这一组则不行，因为只能添加 $0$。

即使删去了前端的 $1$，也只能在后面再加上一个 $1$，就还是当前情况。

除非你是：
```
101
001
```

这样的情况，会有：
$101 \rightarrow 01 \rightarrow 1 \rightarrow 11 \rightarrow 110 \rightarrow 1100 \rightarrow 100 \rightarrow 1001 \rightarrow 001$。

对于：
```
000
111
```

同样不行，理由同上，因为不可能添加 $1$。

而那时的 $parity(a)$ 就只能保持为 $0$，不可能改变。

观察，发现当初始 $parity(a)=0$ 时，只要 $a$ 中 $1$ 的数量大于等于 $b$ 中 $1$ 的个数即可构造成功。

对于初始 $parity(a)=1$ 的情况，操作可以将 $1$ 添加至其末尾，或者删除第一个字符。

如数据 $1$：

```
100
011
```

有：

$100 \rightarrow 1001 \rightarrow 001 \rightarrow 01 \rightarrow 011$

如数据 $2$:

```
100
101
```
有：

$100 \rightarrow 1001 \rightarrow 001 \rightarrow 01 \rightarrow 1 \rightarrow 10 \rightarrow 101$

但对于下列数据：

```
100
111
```

则不行，因为其只能添加一个 $1$，而 $1$ 的数量不能继续增加。就如同上一种情况一样。

观察，发现当初始 $parity(a)=1$ 时，只要 $a$ 中 $1$ 的数量加一大于等于 $b$ 中 $1$ 的个数即可构造成功。

所以结论推广：

设 $a_1$ 为 $a$ 中 $1$ 的数量，$b_1$ 为 $b$ 中 $1$ 的数量。

若有 $a_1 + parity(a) > b_1$，则可以构成 $b$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int lena,lenb,a1,b1;
int main(){
	cin>>a>>b;
	lena=a.length();
	lenb=b.length();
	for(int i=0;i<lena;i++){
		if(a[i]=='1'){
			a1++;
		}
	}
	a1+=a1&1;//&1用来取得 a1 是否为奇数，若为奇数，则可以增加一。 
	for(int i=0;i<lenb;i++){
		if(b[i]=='1'){
			b1++;
		}
	}
	if(a1>=b1){
		printf("YES");//符合则输出 
		return 0;//并结束程序 
	}
	printf("NO");//否则输出不可能 
	return 0;
}
```

---

## 作者：Cappuccino_mjj (赞：0)

~~刚开始不知道为啥想用广搜做。。。~~

## [题目传送门](https://www.luogu.com.cn/problem/CF297A)
题目意思：

给你两个 01 串，问能否经过题目给的操作后使得第一个串变得与第二个串一样。

---

思路：

这其实是一道思维题。自己搞几个样例看看就能发现规律了。

那怎么做呢？就是将两个串的 ``1`` 的个数分别记录，然后判断第一个串是否还能加一个 ``1``（即第一个串的 ``1`` 的个数是否是奇数）。是奇数第一个串的计数器再加一。

最后判断第一个串的 ``1`` 的个数是否大于第二个串的即可。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,x) for(auto i:x)
string a,b;
int cnt1,cnt2;
int main()
{
	cin>>a>>b;
	FOR(i,a)if(i=='1')cnt1++;
	FOR(i,b)if(i=='1')cnt2++;
	cnt1+=cnt1%2;
	if(cnt1>=cnt2)
		cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

完美撒花~

---

## 作者：Shadow_T (赞：0)

### 前言：
[题目传送门](https://www.luogu.com.cn/problem/CF297A)
### 题目分析：
首先统计出 $a,b$ 中字符 $1$ 的数量 $suma,sumb$。

然后计算出 $\operatorname{parity}(a)$：直接循环统计 $1$ 的个数 $cnt$，然后将 $cnt$ 取余 $2$，再将现在的 $cnt$ 转换成字母连接在 $a$ 后面。

如果 $\operatorname{parity}=1$，那么 $a$ 就不能加 $1$ 了，也就是只能使用操作 $2$，那么如果 $suma \leq sumb$，那么输出 ```YES```，否则输出 ```NO```。

如果 $\operatorname{parity}(a)=0$，那么 $a$ 可以用 $1$ 次 $\operatorname{parity}(a)$，即：$suma \leq sumb-1$ 输出 ```YES```，反之输出 ```NO```。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b;
int main()
{
	cin>>a>>b;
	int suma=0,sumb=0;
	for(int i=0;a[i];i++)
	if(a[i]=='1') suma++;
	for(int i=0;b[i];i++)
	if(b[i]=='1') sumb++;
	if(suma%2==0)
	if(suma>=sumb) cout<<"YES";
	else cout<<"NO";
	if(suma%2==1)
	if(suma+1>=sumb) cout<<"YES"; 
	else cout<<"NO";
	return 0;//完结散花 
} 
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题意传送门](https://www.luogu.com.cn/problem/CF297A)

不说废话了，直接开始吧！

## 思路

根据第一个操作：

将 $parity(a)$ 添加到 $a$ 的末尾。

可以得知最多在原 01 串中添加一个 $1$。

所以是否能将 01 串 $a$ 改为 01 串 $b$，关键在于 $1$ 的数量是否够。

而各种情况还是要从 $parity(a)$ 开始谈起。

为了解说方便，我把 01 串 $a$ 中 $1$ 的个数称为 $cnta$，将 01 串 $b$ 中 $1$ 的个数称为 $cntb$。

### 情况一：$parity(a)=0$

也就是意味着 01 串 $a$ 中 再也无法添加 $1$。

此时如果 $cnta \geq cntb$，那么 $a$ 可以改为 $b$。

### 情况二：$parity(a)=1$
也就是意味着 01 串 $a$ 中可以添加一个 $1$。

此时如果 $cnta+1 \geq cntb$，那么 $a$ 可以改成 $b$。

上代码！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main(){
	cin>>a>>b;
	int lena=a.size(),lenb=b.size();
	int cnta=0,cntb=0;
	for(int i=0;i<lena;i++)
	{
		if(a[i]=='1')
			cnta++;
	}
	for(int i=0;i<lenb;i++)
	{
		if(b[i]=='1')
			cntb++;
	}
	if(cnta%2==0)//添加不了任何1 
	{
		if(cnta>=cntb)
			cout<<"YES";
		else
			cout<<"NO";
	}
	else if(cnta%2==1)//能加一个1
	{
		if(cnta+1>=cntb)
			cout<<"YES"	;
		else
			cout<<"NO";
	} 
	return 0;
} 
```





---

## 作者：Zero_s (赞：0)

第一眼看，这是个数学问题，应该不会很简单吧……

实际上——真的很简单！！！

## 解法：

首先，我们先把输入的字符串 $a$ 中 $1$ 的个数记作 $x$，而字符串 $b$ 中 $1$ 的个数记作 $y$。

如何算出 $x$ 和 $y$ 呢？我建了一个函数，当然，大家也可以直接写在主函数里面。

```cpp
inline int read()
{
	char ch=getchar();
	int x=0;//初始化
	while(ch!='1'&&ch!='0') ch=getchar();
    		//判断ch是不是1或0，若都不是，继续输入ch
	while(ch=='0'||ch=='1')
	{//当ch是1或0时，开始计数
		x+=ch^48;
	//‘1’^48=1,‘0’^48=0
		ch=getchar();//继续输入字符ch
	}
	return x;//返回计数x
}
```

要求 $x$ 和 $y$，其实直接 ``x=read(),y=read()`` 就好了。

解决了之后怎么办呢？——没思路了吗？
### 不要被数学吓到了，这道题目我们可以先分类讨论！
第一种可能：$x$ 是 $2$ 的倍数。那么，$a$ 串就可以在末尾加上任意多个 $0$，然后删除开头的 $1$，这时候，$x$ 是奇数。  
1. 我们就可以在 $a$ 串末尾加上一个 $1$，$x$ 不变。
2. 我们可以删除 $a$ 串的所有前导 $0$ 和第一个 $1$，这样，$x=x-2$

所以，当 $x$ 是偶数是，串 $a$ 可以变成任意的长度，$1$ 的数量 $\le x$ 的串。

第二种可能：$x$ 是奇数。
1. 在 $a$ 串末尾加上 $1$，$x=x+1$,变成偶数。
2. 删除 $a$ 串所有前导 $0$ 和第一个 $1$，$x=x-1$，也变成偶数。

总结：当 $x$ 为偶数时，只要 $x>y$ 就可以让 $a$ 变成 $b$。当 $x$ 为奇数时，$x+1>y$ 就可以让 $a$ 变成 $b$。

我们发现,当 $x$ 为偶数时，$x\mod2=0$，反之，$x\mod2=1$，所以，我们只需要判断 $x+x\mod2$ 是否大于 $y$ 就好了。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
inline int read()
{
	char ch=getchar();
	int x=0;
	while(ch!='1'&&ch!='0') ch=getchar();
	while(ch=='0'||ch=='1')
	{
		x+=ch^48;
		ch=getchar();
	}
	return x;
}
int main()
{
	a=read(),b=read();
	puts(a+a%2>=b? "YES":"NO");
	return 0;
}
```





---

## 作者：tanghg (赞：0)

这道题是一道贪心。

### 分两种情况考虑：

#### 当 $\operatorname{parity}(a)$ 为偶数时：

先说结论:

$$\operatorname{parity}(a)\geq \operatorname{parity}(b)$$ 

时成立。

比如把最前面的 $0$ 给去掉后第一个是 $1$ 了，然后可以把$1$ 去掉，这样 $\operatorname{parity}(a)$ 就成奇数了，然后可以在最后添加 $1$ 这样来来回回的 $1$ 可以默认它是不变的，多余的删掉不加就行了。于是只要有足够多的 $1$ 保证可以变成 b 即可。

#### 当 $\operatorname{parity}(a)$ 为奇数时：

可以理解成比上面的情况多了一个 $1$， 只要把它去掉就可以按照上面的结论进行了。

也就是 $\operatorname{parity}(a)+1\geq \operatorname{parity}(b)$。

#### 代码：

```
#include <iostream>
using namespace std;
typedef long long ll;
ll parity(string a){
    ll num=0;
    for (int i = 0; i <a.length() ; ++i) {
        if(a[i]=='1'){
            num++;
        }
    }
    return num;
}
int main() {
    string a,b;
    cin>>a>>b;
    ll A= parity(a),B= parity(b);
    if(A%2==0){
        if(A>=B){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
    }else{
        if(A+1>=B){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
    }
    return 0;
}

```

---

## 作者：PeterBei (赞：0)

这题还是挺简单的。

$parity(a)$ 只有在 $01$ 串中有奇数个 $1$ 时才能添加 $1$，而即使是添加也只能添加一个，并且除了 $1$ 的数量以外的差异都可以通过删减 $0$ 来调整 $1$ 的位置。所以这题只要对两个字符串中 $1$ 的数量进行检查和比较就行了。

有一点需要额外注意，如果原本 $a$ 字符串中一的数量就是奇数，那就要提前将 $parity(a)$ 所产生的 $1$ 加入 $a$ 串中再进行比较。

程序运用了一些位运算的写法，比普通的比较要快得多，如果看不懂请自行百度。

原代码：

```
#include<iostream>
#include<cstring>
using namespace std;

char a[1010], b[1010];
int cnt1 = 0, cnt2 = 0;

int mian()
{
    cin >> a >> b;

    for(int i = 0; i < strlen(a); i++)
    {
        if(a[i] - '0')
        {
            cnt1++;
        }
    }
    for(int i = 0; i < strlen(b); i++)
    {
        if(b[i] - '0')
        {
            cnt2++;
        }
    }

    if(((cnt1 & 1) && cnt1 + 1 >= cnt2) || cnt1 >= cnt2)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### P.S.
xtw 不会做橙题石锤。  

### Description.
给定一个 01 串 $S$，每次可以做如下两个操作，问能否变成 $T$。  
- 删掉 01 串开头地数
- 在结尾加入当前串的 $\oplus$ 和。  

### Solution.
首先观察发现，如果当前有偶数个一，那么一的数量永远不能增加。  
原因：你只能在后面插入零，只有删除一个一才能多插入一个一。  

观察发现，每一个偶数个 `1` 的串可以变成和它 `1` 数量相同的任意一个 01 串。  
原因：你每次可以往它后面插入任意多个 `0`，在每一个你想要的瞬间你可以对前缀删 `1` 然后末尾插入 `1`。  

同时，奇数的情况也可以，因为你可以先插入一个 `1` 变成偶数然后再删了它。  

所以结论就是：如果初始串的最大 `1` 数量大于等于结束串的 `1` 数量，就为 `YES`，否则是 `NO`。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
char a[100005],b[100005];int n,at,bt;
int main()
{
	scanf("%s",a+1),n=strlen(a+1);for(int i=1;i<=n;i++) at+=a[i]=='1';
	scanf("%s",b+1),n=strlen(b+1);for(int i=1;i<=n;i++) bt+=b[i]=='1';
	return at+=at&1,puts(at>=bt?"YES":"NO"),0;
}
```

---

