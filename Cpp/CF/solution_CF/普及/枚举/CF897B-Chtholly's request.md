# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100
```

### 输出

```
33
```

## 样例 #2

### 输入

```
5 30
```

### 输出

```
15
```

# 题解

## 作者：chengni (赞：8)

一道珂朵莉题

刚开始以为挺难的，但后来发现只能是偶数回文串。因为是偶数，所以必定由一个整数和它的倒序数所构成。

很明显这个整数决定了它的大小。

这样我们就可以推出所有的zcy数。

比如前十个zcy数为  

                11  22  33  44  55  66  77  88  99  1001

对应的前十个数为

                1   2   3   4   5   6   7   8   9    10
                
我们只需要将他们加起来就可以了。

因为n范围很小，只有1e5，复杂度是肯定够的。另外因为zcy数是两个整数拼在一起，大的数据需要开 long long 才能记录。

记得取模。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
	while(ch>'9' || ch<'0'){
        if(ch=='-') f=-1;
	    ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int main(){
	ll n=read(),p=read();
	ll sum=0;
	for(int i=1;i<=n;i++){
		ll tmp=i;
		int k=i;
		while(k){
			tmp=tmp*10+k%10;
			k/=10;
		}
		cout<<tmp<<endl;
		sum+=tmp;
		sum%=p;
	}
	cout<<sum;	
}

```

---

## 作者：XL4453 (赞：3)

	    在太阳西斜的这个世界里，置身天上之森。
        等这场战争结束之后，不归之人与望眼欲穿的人们，人人本着正义之名。
        长存不灭的过去，逐渐消逝的未来。
        我回来了，纵使日薄西山，即便看不到未来，此时此刻的光辉，盼君勿忘。


------------
解题思路：

考虑构造 zcy数 。

可以发现其实所有的 zcy数都是由前一半“翻折”过来形成的。易证明由小到大的枚举所有前一半的数构造而成的数也是从小到大的。然后就枚举所有前一半的数，并由此构造后一半的数即可。



------------
代码：

```cpp
#include<cstdio>
using namespace std;
long long n,MOD,ans,num,now;
int main(){
	scanf("%lld%lld",&n,&MOD);
	for(int i=1;i<=n;i++){
		num=i;
		now=i;
		while(now){
			num*=10;
			num+=now%10;
			now/=10;
		}
		ans=(ans+num%MOD)%MOD;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：EuphoricStar (赞：3)

来一篇纯 STL 题解。

由于题目中要求**回文数的位数必须是偶数**，所以很容易想到这样的构造回文数的方式：由任一自然数加它倒过来的数（不是倒数）。

我们可以使用头文件 `<sstream>` 中的 `stringstream` 实现字符串与整数互相转换，头文件 `<algorithm>` 中的 `reverse` 实现翻转字符串。

枚举 $1...k$ 之间的整数，将它输出到字符串流中，然后调用两次 `ss.str()`，并将其中一个翻转。

接下来将两个字符串拼接起来，初始化一个新的字符串流为拼接后的字符串，输入到整数 $n$ 中并累加（要边加边取模）

最后输出结果即可。

核心代码：

```cpp
        stringstream ss;
        ss << i;
        string s = ss.str(), t = ss.str();
        reverse(t.begin(), t.end());
        stringstream ss2(s + t);
        long long n;
        ss2 >> n;
        res = (res + n) % p;
```


---

## 作者：Sai0511 (赞：3)


**此题的感想：**~~这大概是最水的珂朵莉题了...~~       
虽然楼下思路和我是一样的，但是我想把这道题补充一下。                 
## 我的思路：                        
### 30分算法：大概能对4,5组数据（此题有30组数据）      

强行暴力枚举，定义一个循环变量$i$，$i$从$1$开始，检查这个数是否是回文数，如果是，则$t++$,当$t==k$时，退出循环，并输出$i$。这里的话主要程序我就不打出来了，放一个取此数的回文数的函数。 ** 我们知道，当一个数%10取到的肯定是**这个数的最后一位，于是我们可以再用**/=10**将这个数的最后一位砍掉，这样就可以取到这个数的回文数。                   
```cpp
int huiwen(int x){
	int s=0,shu;
    while(x>0){//当x>0时
    	shu=x%10;//取最后一位
        s=s*10+shu;//将其写入s中
        x/=10;//砍掉最后一位
    }
    return s;              
}
```                              
这时只要判断:           
```cpp
if(huiwen(i)==i) t++;
```                   
即可。时间复杂度：设第$k$个回文数为$N$,时间复杂度为$O(N)$            
### 100分做法（满分做法）          
题目中告诉我们了，这个数的位数一定为偶数。那么这个数一定可以写成：            
$\overline\text{abba}$或$\overline\text{abccba}$或$\overline\text{abcddcba}$......这样以此类推。我们可以发现，**将这个数砍一半，可以得到$\overline{ab}$,或者$\overline\text{abc}$**....以此类推，**这样取出来的$\overline{ab}$或者$\overline{abc}....$一定是具有递增性质的。**所以我们就可以定义一个循环$i$从$1$到$k$枚举，构造这个数，即可。         
**由于我们枚举的是这个数的前一半，而这个数的后一半就是这个数$reverse$一下，这样增加的复杂度是常事级别，所以不需要管它。**    
而我们知道，一个数肯定要先加上它的前一半。而$\overline{ab00...0}$其中$0$的个数是这个数的位数，刚好能存下接下来将将此数翻转的操作。
## 话不多说，上代码：      
```cpp
#include<bits/stdc++.h>
#define ll long long
//此处有坑，因为p可以达到10^9,不写long long会WA
using namespace std;
ll n,i,j,k,t,p,i1,s,s1,s2;
namespace Fastio{  //声明命名空间用来快速输入输出
	inline ll read(){//快速输入
		ll x=0;char c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)){x=x*10+c-48;c=getchar();}
		return x;
	}
	void write(ll x){//快速输出   
		if(x/10>0) write(x/10);
		putchar(x%10+48);
		return;
	}
}
using namespace Fastio;
int main(){
	k=read();p=read();//输入数据
	for(i=1;i<=k;i++){//枚举这个数的前一半
		j=1;//j的作用是取这个数的位数
		while(j<=i) j*=10;
		s=(i*j)%p;//先加上此数的前一半
		i1=i;s1=0;
		while(i1>0){//将前一半翻转。
			ll shu=i1%10;
			s1=s1*10+shu;
			i1/=10;
		}
		s=(s+s1)%p;//将前一半后一半合并
		s2=(s2+s)%p;  //加入总和
	}
	write(s2);//输出
}
```


---

## 作者：fjy666 (赞：2)

### 0x01 思路
对于一个**偶**回文数，我们可以把从中间劈开，把它分成 $\overline{(a)[\texttt{Reverse}(a)]}$ ，其中 $\texttt{Reverse(a)}$ 代表 $a$ 的倒序数，就是把 $a$ 翻过来读。  
- $\texttt{Reverse}(123) = 321$
- $\texttt{Reverse}(2424) = 4242$
- $\texttt{Reverse}(4235) = 5324$
- $\texttt{Reverse}(1020) = 201$

把回文数按顺序列出来：$\{11,22,33,44,55,66,77,88,99,1001,1111,1221......\}$ 。  
我们惊喜地发现：第 $i$ 个回文数就是 $\overline{(i)[\texttt{Reverse}(i)]}$ ！  
前 $k$ 个回文数只要枚举到 $k$ 即可。

不过，有一个注意点：怎么把 $i$ 和 $\texttt{Reverse}(i)$ 拼起来？  
为了叙述方便，定义 $S(i)$ 为 $i$ 的位数。  
是不是 $i \times 10^{S(\texttt{Reverse}(i))} + \texttt{Reverse}(i)$ ？  
**不是**。  
若 $i=10$ ,用上述方法算出来的是 $101$ ，而不是 $1001$。  
其实，问题出在 $S(\texttt{Reverse}(i))$ 上。  
若一个数有后缀 $0$ ，$S(\texttt{Reverse}(i) \neq S(i)$ ！  
所以，应该是 $i \times 10^{S(i)} + \texttt{Reverse}(i)$ 。

在我的代码中，$\texttt{Reverse(x)}$ 如文中所述， $\texttt{Log10\_}(x)$ 用来计算 $10^{S(i)}$。  

**时间复杂度**  
对于每个数 $i$ ，拼成回文数时间复杂度 $\Theta(\log_{10}i)$ ，累加结果 $\Theta(1)$ 。  
再加上 $\Theta(k)$ 的枚举复杂度，总时间复杂度为 $\Theta(k\times\log_{10}k)$ 。  
跑的飞快，目前 Rank 1 。

------------
```cpp
#include <cstdio>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define rtn return
typedef long long ll;
int Reverse(int x){
	int ans = 0;
	while(x){
		ans = ans * 10 + x % 10;
		x /= 10;
	}
	rtn ans;
}
int Log10_(int x){
	int ans = 1;
	while(x){
		ans = ans * 10;
		x /= 10;
	}
	rtn ans;
}
int main(){
	int k,p;
	scanf("%d%d",&k,&p);
	int ans = 0;
	fo(i,1,k)
		ans = ((ll)ans + (ll)i * Log10_(i) + Reverse(i)) % p;
	printf("%d",ans);
	rtn 0;
}
```

---

## 作者：Da_un (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF897B)
题意就是求出前 k 个长度为偶数的回文数的和，并输出其模 p 的结果。

## 思路
此题如果用暴力枚举的方法的话一定是过不了的，所以要换一种方法来优化。

回文数应该都知道，就是由一个数和它的倒过来的数拼接而成，又因为奇数加奇数为偶数，偶数加偶数也为偶数，所以任何一个数的回文数均为偶数长度，依照这个规律，直接按顺序找出 zcy 数即可。

还要注意的是，毕竟需要一个累加器，所以还是要开 long long 的，并且时刻注意取模。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring> 
#define ll long long
using namespace std;
ll k,p,u,ans;
inline ll read()//快读优化 
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	} 
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
} 
void work()
{
	for(ll i=1;i<=k;i++){//枚举前k个数，都符合要求 
		ll t=i,q=0,o=1;
		while(t){
			q=q*10+t%10;//求倒过来的数 
			t/=10; 
			o*=10;//用于回文数的拼接 
		}
		ll sum=i*o+q;//拼接 
		ans=ans%p+sum;//累加取模 
	}
}
int main()
{
	k=read(),p=read();
	work();
	printf("%lld",ans%p);//为了保险，输出时再模一次 
	return 0;
}
```

---

## 作者：JimmyF (赞：1)

此题解适用于初学者食用
~~（大佬自行跳过）~~。

题目就是让我们求前
$k$
个长度为偶数的回文数总和
$\bmod$
$p$
的结果。

分析一波：
其实每个回文数都是由一个数加它倒过来的数组成的。

举个例子：

		1  2  3  4  5  6  7  8  9   10   11   12
所对应的
$zcy$
数就是

		11 22 33 44 55 66 77 88 99 1001 1111 1221

那就生成
$zcy$
数即可。

记得开
$long$
$long$
，因为超出了
$int$
的范围。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,p,sum,g;
void work()
{
	for(long long i=1; ; i++)
	{
		long long t=i,h=0,q=1;
		while(t)
			h=h*10+t%10,q*=10,t/=10;  //拆分重组成倒过来的数
		long long ans=i*q+h;  //合并
		if(g>=k)break;    //判断是否在前k个
		++g;
		sum=sum%p+ans;	 //累加，记住边加边%
	}
} //生成zcy数
int main()
{
	cin>>k>>p;  //输入
	work();    //生成
	cout<<sum%p; //输出，记得再%一次
	return 0;  //完结撒花
}
```


---

## 作者：Eason_AC (赞：0)

## Content
我们将长度为偶数的回文数称作 zcy 数，比如 $11,1221$ 是 zcy 数，而 $34,121$ 不是。假设第 $i$ 个 zcy 数为 $a_i$，求 $\sum\limits_{i=1}^na_i$（前 $n$ 个 zcy 数的和）模 $p$ 后的结果。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant p\leqslant 10^9$。**
## Solution
在写题解之前做一个提醒：**这篇题解里的代码用 C++11 及以下的语言提交会出现 WA 的情况，需要用 C++14 及以上的语言提交。** 有可能是因为 C++14 及以上的语言里面的语句和 C++14 以下的语言的对应语句的效果不同。

以下是正文：

由于无论什么数乘以 $2$ 都是偶数，所以我们很容易发现，第 $i$ 个 zcy 数，即第 $i$ 个长度为偶数的回文数，其实就相当于将 $i$ 和 $i$ 反转过后的数拼接在一起得到的数，所以，我们考虑直接暴力求出 $i$ 翻转后得到的数 $i'$，然后设数字 $x$ 的长度为 $L_x$，那么第 $i$ 个 zcy 数就可以这样表示：$10^{L_x}\times i+i'$，然后直接暴力加，边加边取模即可。

如果您去 CF 官网上看这道题目的标签的话，你会发现里面有个“暴力”的标签，所以这道题目总的来说就是一点：暴力。
## Code
```cpp
ll ans;
int n, m;

ll digitnum(ll x) {
	ll p = x, ans = 0;
	while(p) {
		ans++;
		p /= 10;
	}
	return ans;
}
ll turn(ll x) {
	ll p = x, ans = 0, digit[27] = {0};
	while(p) {
		digit[++digit[0]] = p % 10;
		p /= 10;
	}
	_forll(i, 1, digit[0])	ans += digit[i] * (ll)pow(10, digit[0] - i);
	return ans;
}

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(n), getint(m);
	_for(i, 1, n) {
		int len = digitnum(i), rev = turn(i);
		ll tmp = ((ll)pow(10, len) * i + rev) % m;
		ans = (ans + tmp % m) % m;
	}
	writell(ans);
	return 0;
}
```

---

## 作者：智子·起源 (赞：0)

### 提供广东部分地区最适合的码风+最简单的理解方式

---

### 题目理解

这道题，题目意思很简单。就是要你求出前k个数位个数是偶数的回文数的和mod p。

数据范围：k<=100000，p是int范围以内

---

### 明确思路

首先，根据k可以确定，绝对不可以暴力查找回文数。因为第100000个回文数是非常大的。

那我们不妨把我们要的回文数做出来。（构造就是这个意思）

一个数：123

反过来：321

可以拼成回文数：123321

因为回文数这里局限与偶数为，所以大大降低了构造的难度。

从1~100000范围内进行构造即可，由于数据太大，（最大的回文数：100000000001）要开long long。

### code

#### 红蝶在此，抄袭可耻。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,f[100000+5],fn,ans;
long long s,t;
int main()
{
  scanf("%d%d",&n,&q);
  for(int i=1;i<=100000;i++)//最大范围
  {
    s=i,t=i;
    while(s>0)
    {
      t=t*10+s%10;
      s/=10;
    }
    fn++;
    f[fn]=t;//构造
    if(fn==n)//如果当前回文数个数达到k
    {
      for(int j=1;j<=n;j++)ans=(ans+f[j])%q;
      cout<<ans;//累加并输出
      return 0;//over
    }
  }
  return 0;
}
```


---

