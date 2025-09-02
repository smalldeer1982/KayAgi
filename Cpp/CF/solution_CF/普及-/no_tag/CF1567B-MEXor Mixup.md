# MEXor Mixup

## 题目描述

给你两个数字 $a$，$b$，问使得一个非负整数数组的 $\operatorname{MEX}$ 为 $a$ ，数组内所有数的 $\operatorname{XOR}$ 为 $b$ 的最短长度。

称不属于该数组的最小非负整数为该数组的 $\operatorname{MEX}$ ，数组的 $\operatorname{XOR}$ 为数组所有元素的按位异或。

## 说明/提示

$1\leq t \leq 5\cdot10^5,1\leq  a \leq 3\cdot10^5,0\leq b\leq 3\cdot10^5$

译者：@smyslenny

## 样例 #1

### 输入

```
5
1 1
2 1
2 0
1 10000
2 10000```

### 输出

```
3
2
3
2
3```

# 题解

## 作者：Cht_master (赞：5)

- 题意简述：给定一个可重集的 $\operatorname{MEX}$ 和 $\operatorname{XOR}$，求该可重集最少有几个元素。其中 $\operatorname {MEX}$ 指该可重集中的最小元素加 1，$\operatorname {XOR}$ 指该可重集所有元素的异或和 $(1\le T\le 5\cdot10^4,1\le \operatorname{MEX}\le 3\cdot10^5,0\le \operatorname{XOR}\le 3\cdot 10^5)$。

- 题解：显然 $[0,\operatorname{MEX}-1]$ 是必需要选择的，否则 $\operatorname{MEX}$ 会更小。通过 [Problem - B - Codeforces](https://codeforces.com/gym/102409/problem/B) 的解法可以 $\Theta(1)$ 预处理出 $[1,n]$ 的异或和，代码如下：

  ```cpp
  //打表也容易发现只有这4种情况.
  int PXOR(int n){
      	if(n%4==0)return n;
  		if(n%4==1)return 1;
  		if(n%4==2)return n+1;
  		if(n%4==3)return 0;
  }
  ```

  - 记答案为 $ans$ ，根据上文，$ans_{min}=\operatorname{MEX}$。令 $[0,\operatorname{MEX}-1]$ 的异或和为 $\operatorname{PXOR}$（在代码中为 `0^PXOR(MEX-1)` ），令 $\operatorname{PXOR}\bigoplus X=\operatorname{XOR}$，即我们需要某些异或和为 $X$ 的数来满足题意。

  - 根据异或的性质 $A \bigoplus B = C \Leftarrow\Rightarrow A = B \bigoplus C$，容易得到 $X=\operatorname{XOR}\bigoplus \operatorname{PXOR}$。

  - 现在进行分类讨论：
    - 若 $\operatorname{PXOR}=XOR$，则不需要再异或 $X$，$ans$ 不变。
    - 否则就需要 $X$，注意到 $X=\operatorname{MEX}$ 的特殊情况，这个时候必须把 $X$ 拆成不等于 $\operatorname{MEX}$ 的两个数，$ans$ 需要加 2；否则直接加 1 即可。

- The code：

  ```cpp
  //Water problem solution plus rating!!!
  #include<bits/stdc++.h>
  using namespace std;
  int PXOR(int n){
      	if(n%4==0)return n;
  		if(n%4==1)return 1;
  		if(n%4==2)return n+1;
  		if(n%4==3)return 0;
  }
  int main(){
  		int T,MEX,XOR,pxor,X,ans;scanf("%d",&T);
  		while(T--){
  			scanf("%d%d",&MEX,&XOR),ans=MEX;
  			pxor=0^PXOR(MEX-1),X=pxor^XOR;
  			if(pxor!=XOR){if(X==MEX)ans+=2;else ++ans;}
  			printf("%d\n",ans);
  		}
  		return 0;
  }
  ```

  

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1567B)

一句话题意：求一个非负整数数组的最小长度使得不属于该数组的最小非负整数为 $a$，且数组中所有元素的异或和为 $b$。

（按位异或：两个数相对应的二进制位如果相同则该位为 $0$，不同则该位为 $1$。）

由于不属于该数组的最小非负整数为 $a$，所以不难发现 $0$ 到 $a-1$ 是必须要选的，且 $a$ 无论如何不能选。于是答案最小为 $a$。

考虑第二个限制，可以处理出 $0$ 到 $a-1$ 的异或和，记这个异或和为 $s$。

如果 $s=b$，那么答案就是 $a$。

对于 $s≠b$，因为 $b=s ⊕ (s ⊕ b)$ ，所以如果 $s⊕b≠a$，在数组中添加一个 $s⊕b$ 即可，答案为 $a+1$。

但是对于 $s⊕b=a$，就需要添加至少两个数 $c,d$，使得 $c⊕d=s⊕b$，显然这样的两个数是能找到的，那么此时答案就是 $a+2$。

然后有一个小科技，根据 $n \bmod 4$ 的值可以 $O(1)$ 预处理出 $0$ 到 $n$ 的异或和（见代码中 pd 函数）。

使用这个科技，时间复杂度就是 $O(t)$ 的。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned long long
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
int pd(int n)
{
	if(n%4==0)
		back n;
	if(n%4==1)
		back 1;
	if(n%4==2)
		back n+1;
	if(n%4==3)
		back 0;
}
ll t,a,b;
int main()
{
	t=read();
	while(t--)
	{
		a=read(),b=read();
		if(pd(a-1)==b)
		{
			cout<<a<<"\n";
			continue;
		}
		if((pd(a-1)^b)!=a)
			cout<<a+1<<"\n";
		else
			cout<<a+2<<"\n";		
	}
	back 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1567B)

### 思路

最小值为 $a$，说明从 $0$ 到 $a-1$ 一定必须选。

所以答案最小为 $a$。

设 $p_i$ 为从 $0$ 至 $i$ 所有的数的异或（即 $0 \operatorname{xor} 1 \operatorname{xor} 2 \operatorname{xor} ... \operatorname{xor} i$）。

若 $p_{a-1}=b$，则直接输出 $a$（$0 \operatorname{xor} 1 \operatorname{xor} 2 \operatorname{xor} ... \operatorname{xor} a-1$）。

否则，由于异或具有已知 $a \operatorname{xor} b=c$，则 $c \operatorname{xor} b=a$，$a \operatorname{xor} c=b$ 的性质，可以推算出最后一个需要添加到序列中的数 $k$，然后根据情况：

1. $k\neq a$，输出 $a+1$。

2. $k=a$，输出 $a+2$。（序列中不能有 $a$）

写出来之后，有些代码出现了 $\operatorname{UKE}$（实际上是 $\operatorname{TLE}$）的现象，原因是这些代码有这一行：

```
for(int i=1;i<a;i++)p^=i;
```

这一行的时间复杂度是 $\operatorname{O}(a)$，再加上前面 $t$ 次询问，则总时间复杂度是 $\operatorname{O}(at)$。

将 $1\leq t\leq5\times10^5,1\leq a\leq3\times10^5$ 代入，则总时间复杂度是 $\operatorname{O}(1.5\times10^{11})$，严重超时。

所以我们需要寻求更快的解法：

$a=1,p_1=1$

$a=2,p_2=3$

$a=3,p_3=0$

$a=4,p_4=4$

$a=5,p_5=1$

$a=6,p_6=7$

$a=7,p_7=0$

$a=8,p_8=8$

$\forall k(k\geq0)$，则

$a=4k+1,p_a=1$

$a=4k+2,p_a=a+1$

$a=4k+3,p_a=0$

$a=4k,p_a=a$

则求 $p_i$ 的函数显而易见：

```
long long y(int k){
	if(k%4==1)return 1;
	if(k%4==2)return k+1;
	if(k%4==3)return 0;
	if(k%4==0)return k;
}
```

依此写出代码，此题终。

```
#include<iostream>
using namespace std;
long long a,b,t,ans,p;
long long y(int k){
	if(k%4==1)return 1;
	if(k%4==2)return k+1;
	if(k%4==3)return 0;
	if(k%4==0)return k;
}
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;p=0;
		if(y(a-1)==b){
			cout<<a<<endl;
		}
		else{
			if((y(a-1)^b)!=a)cout<<a+1<<endl;
			else cout<<a+2<<endl;
		}
	}
	return 0;
}
```


---

## 作者：JWRuixi (赞：0)

- 题意

给定一个数列的 mex 和异或和，求数列最短长度。

最多$50000$ 组数据。

- 解法

首先什么是数列 mex? 就是不在数列中的最小正整数。

考虑到因为给定 mex 所以显然 $[0,a-1]$ 必在数列中。

区间求异或和的技巧可参照 [Problem B](https://codeforces.com/gym/102409/problem/B) 中的 trick，即可做到 $O(1)$。

由于异或有结合律，所以可以大胆假设加入一个 $b ⨁ sum$，即可，特例就是当这个值为 $a$ 时，需要再加一。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		for (; !isdigit(c); c = getchar()) {
			if (c == '-') f = -1;
		}
		for (; isdigit(c); c = getchar()) {
			x = (x << 1) + (x << 3) + c - '0';
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

int t, a, b;

int sxor (int rhs) {
	if (rhs % 4 == 0) return rhs;
	if (rhs % 4 == 1) return 1;
	if (rhs % 4 == 2) return rhs + 1;
	if (rhs % 4 == 3) return 0;
}

int main () {
	t = read();
	while (t--) {
		a = read(), b = read();
		int p = sxor(a - 1);
		if (b == p) write(a);
		else if ((p ^ b) == a) write(a + 2);
		else write(a + 1);
		puts("");
	}
}
```

---

## 作者：I_am_Accepted (赞：0)

### 题意

给出一个序列的 $\operatorname{MEX}$ 和 $\operatorname{XOR}$，求原序列的最小长度。

### 分析

由于 $\operatorname{MEX}$ 的定义，序列里 $0\to\operatorname{MEX}-1$ 的数必取，而且 $\operatorname{MEX}$ 必不取。

我们设 $0\to i$ 的异或和为 $pre_i$。

若 $pre_{mex-1}=\operatorname{XOR}$，则显然序列中 $0\to\operatorname{MEX}-1$ 的数全取一遍即为答案。

否则我们设 $m=pre_{mex-1} \ xor \ \operatorname{XOR}$。

若 $m\ne \operatorname{MEX}$，则序列中取 $0\to\operatorname{MEX}-1$ 的数各一遍和 $m$ 即为答案。

若 $m=\operatorname{MEX}$，则序列中不能取 $m$， $0\to\operatorname{MEX}-1$ 的数各一遍和异或为 $m$ 的任意两个正整数即为答案。

可以证明这个方案是最优的。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(register int i=j;i<=k;i++)
#define N 400000
int a,b,c;
int pre[N+10];//0~i的异或和 
void init(){
	pre[0]=0;
	For(i,1,N){
		pre[i]=pre[i-1]^i;
	}
}
signed main(){
	IOS;
	init();
	int T;
	cin>>T;
	while(T--){
		cin>>a>>b;
		c=pre[a-1]^b;
		if(c==0)
			cout<<a<<endl;
		else if(c==a)
			cout<<a+2<<endl;
		else
			cout<<a+1<<endl;
	}
    return 0;
}
```

---

## 作者：feicheng (赞：0)

## $\text{Description}$

给你两个数字 $a$，$b$，问使得一个非负整数数组的 $\operatorname{MEX}$ 为 $a$ ，数组内所有数的 $\operatorname{XOR}$ 为 $b$ 的最短长度。

称不属于该数组的最小非负整数为该数组的 $\operatorname{MEX}$ ，数组的 $\operatorname{XOR}$ 为数组所有元素的按位异或。

**限制**

$1\le a\le 3\times 10^5,0\le b\le 3\times 10^5,1\le T\le 5\times 10^5$

## $\text{Solution}$

首先，要使 $\text{mex}$ 为 $a$，则需要数列中包含 $0\sim a
-1$，记 $s = \displaystyle\bigoplus_{i=0}^{a-1}i$，则我们需要在序列中再添加一项 $s\oplus b$，这样序列的异或和就是 $b$ 了。

需要注意的细节：

- 如果 $s=b$，就不需要添加，答案为 $a$。
- 如果 $s\oplus b = a$，需要添加两项，答案为 $a+2$。
- 剩下的答案为 $a+1$。
- 由于 $T$ 比较大， 我们需要预处理前缀异或和。
 
## Code

```cpp

int a,b ;
int sum[300005] ;

inline void solve() {
    in(a,b) ;

    int x = sum[a - 1] ^ b;

    if (x == 0) 
        out('\n',a) ;
    else if (x == a) 
        out('\n',a + 2) ;
    else 
        out('\n',a + 1) ;
}

int main(int argc, const char **argv) {
#ifdef hpy
    freopen("std.in", "r", stdin);
    freopen("std.ans", "w", stdout);
#endif
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int t ;

    for (int i = 1; i <= 300000; ++i) 
        sum[i] = sum[i - 1] ^ i ;

    in(t) ;

    for (; t; --t) 
        solve() ; 

    std::cerr << "This program costs " << clock() << " ms" ;
    return 0 ;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，无论如何，$0$ 到 $a-1$ 都必须在这个数列里，并且 $a$ 不在。

首先算出 $0\bigoplus1\bigoplus2\bigoplus......\bigoplus a-1$，也就是 $0$ 到 $a-1$ 的异或和。设为 $s$。

设答案为 $ans$。

+ 如果 $s=b$，则 $ans=a$。

+ 如果 $s\not=b$，说明还要至少一个数。

	+ 如果 $s\bigoplus a=b$，则 $ans=a+2$，毕竟要想凑到 $b$ 要两个数。
    
   + 否则，$ans=a+1$。
   
注意，这个数列可以有重复的数字。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int a,b;
int s;
int ans;
inline int asksum(int x){
	if(x==1)return 1;
	if(x==2)return 3;
	int y=x%4;
	if(y==0)return x;
	if(y==1)return 1;
	if(y==2)return x+1;
	return 0;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1567B_1.in","r",stdin);
	freopen("CF1567B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&a,&b);
		s=asksum(a-1);
		if(s==b){
			printf("%d\n",a);
			continue;
		}
		if((s^b)!=a){
			printf("%d\n",a+1);
			continue;
		}
		printf("%d\n",a+2);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57606833)

By **dengziyue**

---

## 作者：unputdownable (赞：0)

## 题意简述

你需要构造一个数组，使它的 $\text{MEX}$ 值（即最小的未出现的非负整数）是 $a$，它所有元素的异或和是 $b$。

你只需输出它的最小可能的长度即可。

## 题解

首先 $\text{MEX}$ 值是 $a$ 代表数组中至少要出现 $0$ 到 $a-1$ 之间的所有 $a$ 个整数各一遍，所以答案至少为 $a$。

现在考虑异或和，

设 $0$ 到 $a-1$ 之间的所有 $a$ 个整数的异或和为 $s$，

设 $d=s \oplus b$，那么我们需要添加一些异或和为 $d$ 的数

分类讨论：

- 如果 $d=0$，即 $s=b$，那么答案就是 $a$，无需再添加数。
- 如果 $d \neq a$，那么我们再添加一个 $d$ 在数组中也是合法的（并没有说要互不相同），此时答案是 $a+1$。
- 如果 $d=a$，由于我们没法往数组里添加 $a$，否则 $\text{MEX}$ 值会变大，所以至少要添加两个数，如 $2^x$ 和 $2^x+a$ 等，此时答案是 $a+2$。

异或出来判断一下即可。

注意不能每次 $O(a)$ 求异或和，需要预处理异或前缀和。

[**Code**](https://codeforces.com/contest/1567/submission/127932205)

---

## 作者：dottle (赞：0)

预处理 $0\sim i$ 的异或和为 $f_i$。对于每次询问，令 $x={\rm MEX},y={\rm XOR}$。首先 $0\sim x-1$ 都要选，这就 $x$ 个了，然后你考虑加入若干个数调整异或值,但注意不能加入 $x$。
1. 若 $f_{x-1}=y$，那么不必加；
2. 若 $f_{x-1}\oplus y\ne x$，那么只需要加入 $f_{x-1}\oplus y$ 这一个数；
3. 否则，你必须要加入两个数，使得他们的异或值为 $x$，这样的数显然是可以找到的。

上述三种情况的答案分别为 $x,x+1,x+2$。

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

原题传送门：[戳我](https://www.luogu.com.cn/problem/CF1567B)。

首先，题目定义了两种操作：MEX 和 XOR。

这里 MEX 是序列中所不包含的非负整数的最小值，

XOR 是序列的异或和。

现在要求序列的 MEX 为 $a$，而 XOR 为 $b$，求序列的最小长度。

因为 MEX 为 $a$ 的限制，所以我们需要选取 $0$ ~ $a-1$ 的所有整数。

设 $0$ ~ $a-1$ 的异或和为 $c$，

然后为了使序列的异或和为 $b$，我们需要在序列中加入 $b \oplus c$，$ans=a+1$。

这里就出现了 $2$ 种特殊情况：

1. $b \oplus c = a$，这样我们就可以任选 $2$ 个不为 $a$ 且异或和为 $a$ 的数，$ans=a+2$

2. $b=c$，这样我们不用加入数就可以满足限制，因此 $ans=a$。

然后对于 $0$ ~ $a-1$ 的异或和，我们可以用前缀异或和处理。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int T,a,b,ans;
int f[N]; 
int main(){
    for(int i=2;i<=300000;i++)
        f[i]=f[i-1]^(i-1);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&a,&b);
        if((f[a]^b)==a) ans=a+2;
        else if(f[a]==b) ans=a;
        else ans=a+1;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

