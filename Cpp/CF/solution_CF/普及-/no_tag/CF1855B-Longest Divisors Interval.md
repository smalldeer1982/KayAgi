# Longest Divisors Interval

## 题目描述

Given a positive integer $ n $ , find the maximum size of an interval $ [l, r] $ of positive integers such that, for every $ i $ in the interval (i.e., $ l \leq i \leq r $ ), $ n $ is a multiple of $ i $ .

Given two integers $ l\le r $ , the size of the interval $ [l, r] $ is $ r-l+1 $ (i.e., it coincides with the number of integers belonging to the interval).

## 说明/提示

In the first test case, a valid interval with maximum size is $ [1, 1] $ (it's valid because $ n = 1 $ is a multiple of $ 1 $ ) and its size is $ 1 $ .

In the second test case, a valid interval with maximum size is $ [4, 5] $ (it's valid because $ n = 40 $ is a multiple of $ 4 $ and $ 5 $ ) and its size is $ 2 $ .

In the third test case, a valid interval with maximum size is $ [9, 11] $ .

In the fourth test case, a valid interval with maximum size is $ [8, 13] $ .

In the seventh test case, a valid interval with maximum size is $ [327869, 327871] $ .

## 样例 #1

### 输入

```
10
1
40
990990
4204474560
169958913706572972
365988220345828080
387701719537826430
620196883578129853
864802341280805662
1000000000000000000```

### 输出

```
1
2
3
6
4
22
3
1
2
2```

# 题解

## 作者：Czy_Lemon (赞：8)

### 题意：

给你一个正整数 $n$，让你求出最大的 $l-r+1$ 使得  $i \in [x \in \mathbb{N}^+ \mid l \leq x \leq r] \mid n$。

**举个直观的例子：**

当 $n=40$ 时，观察到 $40$ 的因子为 $1,2,4,5,8,10,20,40$ 其中最长连续的因子段之一为 $1,2$，也就是说 $l=1,r=2$，那么答案为 $2$。


### 解析：

可以发现，当一串长度大于 $1$ 的连续的自然数出现的时候，其中一定存在 $2$ 的倍数。当 $n$ 为奇数时，$n$ 的质因数中不存在偶数，没有质因数 $2$，所以 $n$ 的所有因数都不是 $2$ 的倍数。**也就是说当 $n$ 是奇数时答案为 $1$（长度不可能大于 $1$）。**

此时我们会发现推理好像卡住了，换一个思路。

这里会涉及到一个 _性质_ ：**一个长度大于等于 $x$ 的连续正整数区间内必定存在 $x$ 的倍数。**

假设我们选择 $[1,x]$ 这个区间，其中 $x$ 为从 $1$ 开始的第一个不是 $n$ 的因数的数的前一个数。我们可以证明到不会有比这个区间更优秀的区间。

**证明：**

利用反证法。假设存在一个更优的区间 $[l,r](l>1)$ 在满足 $i \in [x \in \mathbb{N}^+ \mid l \leq x \leq r] \mid n$ 时满足 $(r-l+1) > x$。只考虑正整数，将不等式变换为 $(r-l+1) \geq x+1$。\
可以根据上面的 _性质_ 得到，$l$ 到 $r$ 中一定存在 $x+1$ 的倍数，我们寻找 $x$ 时就已经确定了 $x+1$ 不是 $n$ 的因数，说明 $l$ 到 $r$ 中是 $x+1$ 的倍数的数一定不是 $n$ 的因数，进而得到“不能构造这样一个更优的区间”。

**证得。**

这样，这道题做出来了。我想说的一点是：想出这个结论，一定是通过**举例子**举出来的，然后加以证明，就结束了。

### 代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
int t,n;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		int ans=1;
		while(n%ans==0) ans++;
		printf("%lld\n",ans-1);
	}
	return 0;
}
```


---

## 作者：Scene (赞：7)


## 题意：

给定一个数 $n$，求一个连续区间 $[l,r]$ 使得 $n$ 是区间内每个数的倍数，最大化这个区间的长度（多组数据）。

## 思路:

逆向思考一波，（

如果一个数 $x$ 不是 $n$ 的因数，那么  $x$ 的倍数不能在区间内。

举个例子，比如 $n$ 是 $13$,$3$不是 $13$ 的因数，$3,6,9,12$ 也就不可能出现在区间内，也就是每隔$2$ 个数就有一个不能选在区间中。

![](https://cdn.luogu.com.cn/upload/image_hosting/9apgwadj.png)

也就是说，一个数 $x$ 不是 $n$ 的因数，那么这个区间长度就不可能超过 $x$，最长也只能到 $x-1$。

我们可以找到 $1,2,3,4,...$ 中第一个不是 $n$ 的因数的 $x$，易知 $1,2,3,...,x-1$ 都是符合要求的数。

既然最长只能到 $x-1$，那我们不就可以选择 $[1,x-1]$ 作为答案了。


## 喜闻乐见的代码时间（

```cpp
#include<bits/stdc++.h>
#define fo(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define Ts template<typename Ty,typename... Ar>
#define Tp template<typename Ty>
#define isdigit(c) ((c)>='0'&&(c)<='9')
#define ll long long
#define RS register
#define gc getchar
#define pc putchar
#define I inline
using namespace std;
Tp I Ty wmax(Ty a,Ty b){return a>=b? a:b;}
Tp I Ty wmin(Ty a,Ty b){return a<=b? a:b;}
namespace WrongIO
{
	Tp I void read(Ty &x){x=0;Ty opt=1;char c=gc();while(!isdigit(c)&&c!='-')c=gc();if(c=='-')opt=-1,c=gc();while(isdigit(c))x=(x<<3)+(x<<1),x+=c-'0',c=gc();x*=opt;return;}
	Tp I void write(Ty x){short OI_USE[50],OI_top=0;if(x<=0) if(x==0)pc('0');else pc('-'),x*=-1;while(x)OI_USE[++OI_top]=x%10,x/=10;while(OI_top--)pc(OI_USE[OI_top+1]+'0');return;}
    I void writec(char c[]){int len=strlen(c);for(int i=0;i<len;i++)pc(c[i]);}
    I void writes(string s){int len=s.length();for(int i=0;i<len;i++)pc(s[i]);}
    I void readc(char &c,int l,int r){c=gc(); while(c!=EOF&&(c<l||c>r)) c=gc();}
    I void readc(char &c,char val){c=gc();while(c!=EOF&&c!=val) c=gc();}
    I void readc(char val){char c;c=gc();while(c!=EOF&&c!=val) c=gc();}
    I void readls(string &s){char c=gc();while(c!='\n') s.push_back(c),c=gc();}
    Ts I void read(Ty &x,Ar &...y) {read(x),read(y...);}
} using namespace WrongIO;
//这是祖传514年的板子，不用管(
ll T;
int main()
{
	cin>>T;
	while(T--)
	{
		ll n; cin>>n; ll i=1;
		for(;i<=100;i++)
		{
			if(n%i!=0) break;
		}
		write(i-1),pc('\n'); //i即为第一个不是n的因数的数
	}
	return 0;
}

```

~~如果样例解释的给出的区间也是 $[1,x-1]$ 就好了（~~


---

## 作者：A_grasser (赞：4)

## 更新

看到其他题解指出的问题，修改了一些内容（捂脸）。

## 题意简化

求区间 $\left[l,r\right]$ 中的值都是 $n$ 的因数的最大长度。

## 需要注意的地方

1. 根据样例，开 `long long` 是很有必要的。

## 解法分析

一眼看过去，好像没什么好的想法。

那就找规律：

假设 $n=10$ 的时候，那么这段区间也就是 $1,2$ 这段，答案为 $2$。

假设 $n=15$ 的时候，那么这段区间也就是 $1,2,3$ 这段，答案为 $3$。

假设 $n=60$ 的时候，那么这段区间也就是 $1,2,3,4,5,6$ 这段，答案为 $6$。

对照一下，似乎只要从 $1$ 开始枚举，一直到 $n$ 不能整除它就完事了。

代码核心就变成了这个：

```cpp
long long r=1;
while(n%r==0){//当可以整除时，枚举 
	r++;
}
```
关于 $r$ 的初始值为什么是 $1$ 最优，区间 $\left[l,r\right]$ 为什么选 $\left[1,r\right]$，可以参考其他题解，他们写的很清楚了，这里就不细说了。感谢 panhongxuanyyds 与 Etinorally 指出的错误。

于是，一道看起来很难的题就进化成了水题。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件 
using namespace std;
int t;
long long n;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		scanf("%lld",&n);//读入n 
		long long r=1;
		while(n%r==0){//当可以整除时，枚举 
			r++;
		}
		printf("%lld\n",r-1);//当前r恰好是第一个不符合的，干掉 
	}
	return 0;
}
```

---

## 作者：W_s_W (赞：3)

### 更新：
1. 2023/7/31：该题解已审核通过，但表格存在格式错误，现已修改，麻烦重新审核。

### 思路：
从 $1$ 开始枚举，每次答案加一，找到第一个不是 $n$ 的因数的数退出枚举，输出答案。

---

### 证明：  
观察能整除 $3$ 的数的出现规律：  

|数字|1|2|3|4|5|6|7|8|9|10|11|12|  
|:-:|:-:| :-:| :-:| :-:| :-:| :-:| :-:| :-:| :-:| :-:| :-:| :-:|  
|能否整除 $3$|✗|✗|✓|✗|✗|✓|✗|✗|✓|✗|✗|✓|✗|✗|✓|  
  
显而易见，能否整除数字 $p$ 的规律是（从 $1$ 开始）：  
$p-1$ 个数不能整除 $p$，第 $p$ 个数字可以整除 $p$。  
$p-1$ 个数不能整除 $p$，第 $2p$ 个数字可以整除 $p$。  

根据上述循环，我们可以得出结论：  
在长度为 $p$ 的连续整数列中，必定存在一个数 $k$，使得 $p\mid k$。  

回到题目中，假设正确答案为 $x$，且存在一个符合题意的区间 $[l,r]$，使得 $l\ne1,r-l+1=x$。  
根据上面的结论：在长度为 $x$ 的连续整数列中，必定存在一个数 $k$，使得 $x\mid k$。简单来说就是区间 $[l,r]$ 内肯定有一个数能够整除 $x$。  
同理，区间 $[l,r-1]$ 内肯定有一个数能够整除 $x-1$。  
继续延展，得出：区间 $[l,r]$ 内肯定存在**某个**整数，能够整除 $[1,x]$ 的任意一个整数。  
因为区间 $[l,r]$ 内的任意一个整数都能被 $n$ 整除，所以区间 $[1,x]$ 内的任意一个整数也都能被 $n$ 整除。  
综上所述，符合题意的所有区间中，肯定存在区间 $[1,x]$。

---

### 代码和[提交记录](https://codeforces.com/contest/1855/submission/216275689)
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n;
long long cnt;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		cnt=0;
		if(n&1){
			puts("1");
			continue;
		}
		for(int i=1;n%i==0;i++)cnt++;
		printf("%lld\n",cnt);
	}
	return 0;
}
```

---

## 作者：panhongxuanyyds (赞：2)

# Problem

给出一个正整数 $n$，求出一个区间 $[l, r]$ 使得区间内的每一个整数都是 $n$ 的因数且该区间的大小最大。输出这个区间的大小。

多测。数据范围：$1 \le n \le 10^{18}$，$1 \le t \le 10^4$。

# Solution 1

考虑从 $1$ 开始枚举，找到第一个不是 $n$ 的因数的数 $x$，那么答案就是 $x - 1$（取 $[1, x - 1]$ 这个区间）。

下面的那篇题解没有给出详细的解释。我来补一下。

假设存在一个符合题意的区间 $[l, r]$ 满足 $r - l + 1 > x - 1$。则由于每 $x$ 个连续的自然数中必定有一个是 $x$ 的倍数，所以 $[l, r]$ 中必定存在一个 $x$ 的倍数，进而 $x$ 是 $n$ 的因数。但这与 $x$ 不是 $n$ 的因数矛盾，所以不存在区间 $[l, r]$ 比 $[1, x - 1]$ 更优。

# Code 1

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, m, x;
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n);
		x = 1;
		while (n % x == 0) {
			++x;
		}
		--x;
		printf("%lld\n", x);
	}
	return 0;
}
```

# Solution 2

我的赛时做法。

盲猜结论：答案区间的左右端点肯定不会太大（因为直觉上一个数越大，能整除 $n$ 的概率就越低）。

所以我们设定一个阈值，在这个范围内找最大的合法区间。

为了不 TLE，我取的阈值是 $5000$，赛时一发 AC。

# Code 2

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, m, x, ans;
ll rd() {
	char ch = getchar();
	ll s = 0, w = 1;
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			w = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		s = (s << 3) + (s << 1) + (ch ^ 48);
		ch = getchar();
	}
	return (s * w);
}
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n);
		x = 0;
		ans = 0;
		for (ll i = 1; i <= 5000; ++i) {
			if (n % i == 0) {
				++x;
				ans = max(ans, x);
			}
			else {
				x = 0;
			}
		}
		printf("%lld\n", ans);
	}
    return 0;
}
```


---

## 作者：_Only_this (赞：2)

### CF1855B Longest Divisors Interval 题解

------------

$T$ 组数据，每组给定一个 $n$，找最大的区间 $\left[l,r\right]$，使得 $n$ 为区间所有数的倍数。

------------

这题是个结论题吧。

如果有 $k$ 个数连乘，那么这 $k$ 个数的乘积一定是 $k$ 的倍数，因为这 $k$ 个数中一定有一个数有 $k$ 的因子。

因此，只需找到第一个不是 $n$ 的因子 $x$，输出 $x-1$ 即可。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e6+5;
int T;
ll n;
inline ll Solve(){
	if(n<3){
		return n;
	}
	for(int i=2;i<=n;i++){
		if(n%i!=0){
			return i-1;
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		printf("%lld\n",Solve());
	}
	return 0;
}
```


---

## 作者：Iniaugoty (赞：1)

## problem

求出一个区间，使其中所有整数都是 $n$ 的因数，最大化区间长度。

## solution

由容斥原理和模运算的一些性质，易知，$[l,r]$ 都整除 $n$ 是 $[1,r-l+1]$ 都整除 $n$ 的充分不必要条件。证明略。

因此，贪心地从 $1$ 开始枚举一段连续的整除 $n$ 的数即可。

## code

```cpp
std::cin >> n;
int ans = 0;
while (n % ++ans == 0);
std::cout << ans - 1 << "\n";
```

---

## 作者：tang_mx (赞：1)

这题纯纯简单题，但是身为蒟蒻的我一直没发现这个题的解法，~~打了一个小时暴力~~用了很长时间。

## 题意

给定一个正整数 $n$，求一个正整数区间 $[l,r]$ 的最大值，使得对于区间内的每一个 $i$，都满足 $n$ 是 $i$ 的倍数。

## 分析

可能思路有点麻烦，但是是对的。

这个题唯一的难点就是考虑这个区间的左端点 $l$ 从哪里开始枚举，如果要跑暴力的话，那超时都超到姥姥家了。因此我们直接举例子从它的因数的分布情况来入手。

比如说 $n=1716$ 时，它的因数有 ${1,2,3,4,6,11,12,13}$ 等等，通过分析发现，一个数（质数除外）的因数约大分布的越散，这是因为除了质因数之外，它的因数都可以由更小的数相乘得到。

考虑到这一点，题目就好做了，不管所求的 $[l,r]$ 的左右端点有多大，只要它之间的数不全是质数（不过这种区间应该不存在吧？），那么就一定能从分布更密集的小数中找到它的因数。因此当区间 $[l,r]$ 中的 $l$ 从 $1$ 开始枚举时，这个区间的长度一定最大。

代码和[赛时记录](https://codeforces.com/contest/1855/submission/216314085)
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

inline ll read(){
	ll x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

const int N=2e5+10;

int t,sum,ans;
ll n;

int main(){
	t=read();
	while(t--){
		n=read();
		sum=0,ans=1;
		for(ll i=1;;i++){
		    while(!(n%i)){
		    	sum++;i++;
			}
			if(ans<sum)ans=sum;
			sum=0;
			break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Zkl21 (赞：0)

## 题目大意
给定一个数 $n(1\le n\le 10^{18})$，求区间 $[l,r]$ 的最大长度，满足对于 $l\le i\le r$，都有 $n$ 为 $i$ 的倍数。
## 思路
从简单问题想起，如果 $n$ 是奇数，答案是多少？

显然是 $1$。不难看出，因为 $n$ 没有 $2$ 这个因子，因此它一定不是所有偶数的倍数。

同样，如果 $n$ 不是 $3$ 的倍数，那么答案也不会超过 $2$。从另一种角度解释，因为对于连续的三个数，其中一定有一个数是 $3$ 的倍数，因此由于 $n$ 没有 $3$ 这个因子，答案显然也不会超过 $2$。

不难推广得出，如果 $n$ 不是 $x$ 的倍数，那么答案一定不会超过 $x$。根据这个结论，我们直接从 $1$ 开始遍历所有数字，一旦遇到其中一个数 $x$ 不是 $n$ 的倍数，那么显然答案就是我们之前遍历的数的个数，输出即可。

## 代码
有了结论之后，代码非常简单。
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		ll n,res=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			if(n%i==0)res++;
			else break;
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：xxxxxxxb (赞：0)

## 题目大意
对于一个给定的正整数 $n$，求出一个区间 $[l,r]$ 使得对于任意 $ l \le i \le r $，$i$ 是 $n$ 的因数。
## 分析
如果一个数不被 2 整除，那么他的因子必然也不被 2 整除。

如果一个数不被 3 整除，那么他的因子必然也不被 3 整除。

我们猜想如果 $n$ 不被 $x$ 整除，那么他的因子也必然不被 $x$ 整除。

事实上，设 $n = a_1a_2\dots a_k$，$n$ 不被 $x$ 整除，若有一因子 $a_i$ 被 $x$ 整除，即 $a_i=mx$，那么从而就有 $n=a_1a_2\dots a_{i-1}\times mx \times a{i+1}\dots a_{k}$，从而有 $x$ 整除 $n$。

同时，任意一个合法区间 $[l,r]$ 的长度必然小于 $x$。

所以这一题我们可以直接找出最小的 $x,x\nmid n$，$x-1$ 即为要输出的答案；同时，我们也一定能够构造出一个合法区间：$[1,x-1]$。

AC代码如下：

```cpp
#include <bits/stdc++.h>
#include <climits>


void sol() {
    long long n;
    std::cin >> n;
    if(n==1) {
        std::cout << 1 << '\n';
        return;
    }
    for(long long i = 1;i <= LONG_LONG_MAX;++i) {
    //注意这里，可能1-n全是n的因子，所以要枚举到n+1
        if(n%i!=0) {
            std::cout << i-1 << '\n';
            return ;
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        sol();
    }
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

求 $n$ 最多能被多少个连续正整数都整除。

**分析**

由整除递推性，即若 $a|b,b|c$，则有 $a|c$。所以假如有一个数整除 $n$，它所有因数都整除 $n$，所以为了使能整除 $n$ 的连续自然数，尽可能多，应从尽可能小的数开始，也就是从 $1$ 开始，看它到多少不再整除 $n$ 就可以了。由于 $(1,2,3,4,\dots,41)$ 的最小公倍数已经大于 $10^{18}$，所以复杂度没问题。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	long long n,tp;
	cin>>t;
	while(t--)
	{
		tp=1;
		cin>>n;
		while(n%tp==0) tp++;
		cout<<tp-1<<endl;
	}
	return 0;
}

---

## 作者：Hisaishi_Kanade (赞：0)

前一篇题解没有证明从 $1$ 开始的必然是最大的。

设存在一个 $[l,r]$ 满足条件，其中 $l>1$。

其实相当于 $\text{lcm}(l,l+1,\cdots,r)\mid n$。

我们发现，$[l,r]$ 中必然存在 $1$ 的倍数，$2$ 的倍数，直到 $r-l+1$ 的倍数。这个是类似于 CSP-J 2021 的第一题。

所以对于 $1\le i\le r-l+1$，存在 $i\mid n$。

所以 $\text{lcm}(1,2,\cdots,r-l+1)\mid n$，即 $[1,r-l+1]$。它的长度和 $[l,r]$ 相同。所以可以证明 $[1,r]$ 这种东西不劣于 $[l^\prime,r^\prime]$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
long long t,n,i,cnt;
int p[100005];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%lld",&n);
		int cnt=1;
		while(n%cnt==0)++cnt;
		printf("%lld\n",cnt-1);
	}
	return 0;
}
```

---

## 作者：__ex (赞：0)

这篇题解争取讲清楚一点 QaQ

对于任意一个区间 $[l,r]$，必定有 $\forall i\in[1,r-l+1]$，都 $\exists j\in[l,r]$，使得 $j\bmod i=0$，即 $j$ 是 $i$ 的倍数。

- 因为模 $i$ 意义下的正整数每 $i$ 个一次循环，只要 $i$ 小于区间长度，在区间内一定有至少一个 $0$。

所以对于区间 $[l,r]$，若 $\forall i\in[l,r]$ 都满足 $i|n$，那么对于 $\forall i\in[1,r-l+1]$，也一定满足。

- 因为对于 $\forall i\in[1,r-l+1]$，都能在 $[l,r]$ 中找到 $i$ 的倍数。

所以 $l=1$ 时一定最优。

~~想清楚的话难度和 C2 差不多吧~~

**code**

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>inline T read(){
    T a=0;bool s=0;
    char ch=getchar();
    while(ch>'9' || ch<'0'){
        if(ch=='-')s^=1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        a=(a<<3)+(a<<1)+(ch^48);
        ch=getchar();
    }
    return s?-a:a;
}
const int mn=1e5+10;
int t;ll n;
ll gcd(ll a,ll b)
    {return b?gcd(b,a%b):a;}
int main(){
    t=read<int>();
    for(int cas=1;cas<=t;cas++){
        n=read<ll>();
        ll now=1,cnt;
        for(cnt=1;!(n%now);cnt++)
            now=now/gcd(now,cnt)*cnt;
        printf("%lld\n",cnt-2);
    }
    // while(1)getchar();
    return 0;
}
```



---

## 作者：WhitD (赞：0)

## 题意简述
给定 $T$ 个 $n$，对于每个给定的 $n$，需要求出一段连续的区间，使区间内每个数都是 $n$ 的因数，求最大区间长度。
## 思路
假设 $n=630$，那么 $n=3\times5\times6\times7$，最大区间长度为 $3$。但是我们发现，$n$ 既然可以被 $6$ 整除，那一定可以被 $1,2,3$ 整除，并且 $1,2,3$ 的长度恰好为所求的 $3$。

因此我们就每次从 $1$ 开始枚举，一直枚举到 $n$ 不能整除的数，此时该数减去一就是所求答案。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long T,n;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;;i++)
			if(n%i!=0)
			{
				cout<<i-1<<endl;//此时的i已经不满足，因此需要减一
				break;
			}
	}
	return 0;
}
```


---

## 作者：jiangchen1234 (赞：0)

看到一篇题解没有，就来冲一发题解。

### 题意
$t$ 组数据，给你一个数 $n$，求出最大的区间 $[l,r]$ 使得，$n$ 是区间内所有的数的倍数。
### 思路
看到这里，首先想到了贪心，咋贪呢？

我们把自然数集列出来。
 
>$1,2,3,4,5,6,7,8\cdots$

如果 $n$ 是 $6$ 的倍数，就一定要满足被 $2,3$ 整除。

所以，只要从 $1$ 开始搜，到不能被 $n$ 整除时停止。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define rg register
int t,cnt,i;
il int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
signed main(){
	t = read();
	while(t--){
		cnt = read();
		i = 1;//从一开始搜 
		while(true){
			if(!(cnt % i)){
				i++;
			}else{
				break;
			}
		}
		printf("%lld\n",i - 1);//应为当前的i是不满足要求的，要减1 
	}
	return 0;
}
```


---

