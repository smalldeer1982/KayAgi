# Plus and Multiply

## 题目描述

There is an infinite set generated as follows:

- $ 1 $ is in this set.
- If $ x $ is in this set, $ x \cdot a $ and $ x+b $ both are in this set.

For example, when $ a=3 $ and $ b=6 $ , the five smallest elements of the set are:

- $ 1 $ ,
- $ 3 $ ( $ 1 $ is in this set, so $ 1\cdot a=3 $ is in this set),
- $ 7 $ ( $ 1 $ is in this set, so $ 1+b=7 $ is in this set),
- $ 9 $ ( $ 3 $ is in this set, so $ 3\cdot a=9 $ is in this set),
- $ 13 $ ( $ 7 $ is in this set, so $ 7+b=13 $ is in this set).

Given positive integers $ a $ , $ b $ , $ n $ , determine if $ n $ is in this set.

## 说明/提示

In the first test case, $ 24 $ is generated as follows:

- $ 1 $ is in this set, so $ 3 $ and $ 6 $ are in this set;
- $ 3 $ is in this set, so $ 9 $ and $ 8 $ are in this set;
- $ 8 $ is in this set, so $ 24 $ and $ 13 $ are in this set.

Thus we can see $ 24 $ is in this set.

The five smallest elements of the set in the second test case is described in statements. We can see that $ 10 $ isn't among them.

## 样例 #1

### 输入

```
5
24 3 5
10 3 6
2345 1 4
19260817 394 485
19260817 233 264```

### 输出

```
Yes
No
Yes
No
Yes```

# 题解

## 作者：lndjy (赞：22)

题目可以转化为 $n$ 是否可以写成 $a^x+yb$ 的形式。

证明：若 $a^x+yb$ 乘上了 $a$，结果为 $a^{x+1}+(ay)b$，仍然是这个形式。加上了 $b$ 同理。

而 $n=a^x+yb$ 可以转化为 $n\equiv a^x\pmod{b}$ 且 $n\ge a_x$。

枚举 $x$ 计算即可。$x$ 为指数，增长很快不会超时。

另外这题需要注意一些值为 $1$ 的细节。

```cpp
#include<iostream>
#include<map>
#define int long long 
using namespace std;
int a[205];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,a,b;
		cin>>n>>a>>b;
		if(a==1)
		{
			if(n%b==1||n==1||b==1) cout<<"Yes\n";
			else cout<<"No\n";
			continue;
		}
		int k=n%b;
		bool flg=0;
		for(int i=1;i<=n;i*=a)
		if(i%b==k) flg=1;
		if(flg) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```


---

## 作者：feicheng (赞：10)

## $\text{Description}$

定义一个拥有无穷元素的集合 $S$，满足如下条件：

- $1\in S$
- $x\in S\rightarrow x\times a \in S,x + b\in S$

给出 $n,a,b$，判断 $n$ 是否在集合中。

## $\text{Solution}$

我们发现，一个数如果在集合中，那么一定能表示成 $a^k + pb$ 的形式。

直接枚举指数 $k$，由于 $k$ 最大为 $\log_2 10^9$，所以复杂度可以接受。

对于 $1$ 的情况要特判。

代码并不难打，就不给了，记得开个 `long long`


---

## 作者：Wuyanru (赞：5)

题目大意：

现有一个包含无限个数字的集合，现有若干个规则：
1.  $ 1 $ 在这个集合中；
2.  如果数字 $ x $ 在这个集合中，那么 $ x\times a $ 与 $ x+b $ 都在这个集合中。

现有 $ t $ 组数据，每组数据给定数字 $ n $,$ a $ 和 $ b $,判断 $ n $ 是否在这个集合中。

因为 $ n $ 的最大值为 $ 10^{16} $,暴力或者 bfs 之类的应该都会超时了。

首先我们要想出一个重要的想法：

对于先进行加法，再进行乘法的操作，我们可以将顺序颠倒，将它变为先乘法，再加法的操作。

举个例子：

$$ \left(x+a\right)\times b=x\times b+\begin{matrix}\underbrace{a+a+a\cdots+a}\\b\text{个}\end{matrix} $$

这样子，我们就可以将任意顺序、任意次数的操作转化为先乘再加了。

所以，枚举一开始进行乘法的次数即可，时间复杂度为 $ \Theta\left(\log_{\small a}^{\small n}\right) $。

细节：
1.  数字开 long long；
2.  特判 $ a=1 $ 的情况。

AC 代码：

```
#include<cstdio>
using namespace std;
long long n,a,b;
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%lld%lld%lld",&n,&a,&b);
		bool flag=0;
		long long num=1;
		if(a==1) {
			if((n-1)%b==0)
				printf("Yes\n");
			else
				printf("No\n");
			continue;
		}
		while(num<=n) {
			if((n-num)%b==0) {
				flag=1;
				break;
			}
			num*=a;
		}
		if(flag)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```

感谢观看！

---

## 作者：XYY1411 (赞：4)



# Plus and Multiply

提交地址：[洛谷 CF1542B](https://www.luogu.com.cn/problem/CF1542B)，[CodeForces CF1542B](http://codeforces.com/problemset/problem/1542/B)

## 题目大意

有一个集合：

  - $1$ 在集合中。
  - 如果 $x$ 在集合中，那么 $x \cdot a$ 和  $x + b$ 在集合中。

给定 $a, b, n$ 判断 $n$ 是否在集合中。

## 分析

我们发现，有 $(a^{x_1} + y_1 \cdot b) \cdot a^{x_2} + y_2 \cdot b = a^{x_1 + x_2} + b \cdot (y_1 \cdot a^{x_2} + y_2)$，由于 $x$ 和 $y$ 是我们任意取的，那么 $y_1 \cdot a^{x_2} + y_2$ 可以用一个 $y$ 来表示，则上式化简为 $a^x + b \cdot y = n$。

将上式转化为 $n - a^x \equiv 0 \pmod b$， 这样我们直接枚举指数 $x$ 即可，复杂度为 $\Omicron(\log_an)$。

## $\rm\color{green}code$

```cpp
#include <cctype>
#include <cstdio>
using namespace std;
typedef long long ll;
template <typename T = int>
inline T qread() {
    T n = 0;
    bool flag = false;
    char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') flag = true, c = getchar();
    while (isdigit(c)) n = (n << 3) + (n << 1) + (c ^ 48), c = getchar();
    return flag ? -n : n;
}
int t;
ll a, b, n;
bool flag;
int main() {
    t = qread();
    while (t--) {
        n = qread<ll>(), a = qread<ll>(), b = qread<ll>();
        if (a == 1) { // 注意这里要特判，如果 a 为一不特判会死循环
            puts((n - 1) % b == 0 ? "Yes" : "No");
            continue;
        }
        flag = false;
        for (ll i = 1; i <= n; i *= a)
            if ((n - i) % b == 0) {
                flag = true;
                break;
            }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}
```

---

## 作者：123456Mm (赞：2)

题意略。

这是一道思维题。

可以证明， $x\times a$ 和 $x+b$ 两种操作的位置时无关紧
要的，因此可以优先处理乘操作。

只要判断对于 $a^x\leq n$ , $(n-a^x) \mod b $ 是否等于0。

注意特判，当 $a=1$ 时可能出现死循环，因而要进行特判。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n,a,b;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>a>>b;
		long long x=1;
		bool flag=false;
		if(a==1){
			if((n-1)%b==0){
				cout<<"Yes"<<endl;
			}
			else cout<<"No"<<endl;
			continue;
		}
		while(x<=n){
			if((n-x)%b==0){
				flag=true;
				cout<<"Yes"<<endl;
				break;
			}
			x*=a;
		}
		if(!flag){
			cout<<"No"<<endl;
		}
	}
} 
```


---

## 作者：VinstaG173 (赞：2)

再在判断时忘记考虑 $1 \bmod{1}$ 我就……我就干什么呢……好像也想不到干什么了（~~nz是不可能的~~

之前在做题的时候也是被 $1 \bmod{1}$ 卡了，这次又没长记性（

首先我们发现只有两种操作 $\times a$ 与 $+b$，然后考虑这两种操作有什么比较容易处理的地方。首先它们都不会将原数变小，且 $+b$ 会将之严格变大。为了方便，我们分两类讨论。

首先 $a=1$ 时，显然得到的数都模 $b$ 余 $1$，且所有模 $b$ 余 $1$ 的正整数都可以得到。

然后当 $a \neq 1$ 时，此时操作一定会让得到的数严格增大。上面的过程会提示我们处理模 $b$ 的余数。显然 $+b$ 操作不影响这个余数，而 $\times a$ 会使这个余数变成原来的余数 $\times a$ 再取模 $b$。

显然有 $\times a$ 的次数是有限的且是 $\log$ 级别的。所以只要看看 $[1,n]$ 中 $a$ 的幂中有没有模 $b$ 与 $n$ 同余的即可，如果有则先把 $1$ 变成 $a^k$ 再一直 $+b$ 就能得到 $n$。时间复杂度 $O(\log_a{n})$。

Code:
```cpp
#include<cstdio>
#define rg register
#define ll long long
int t;
ll pw,fl;
ll n,a,b;
int main()
{
	scanf(" %d",&t);
	while(t--)
	{
		scanf(" %lld %lld %lld",&n,&a,&b);
		if(a==1)
		{
			puts(((n-1)%b==0)?"Yes":"No");
			continue;
		}
		pw=1,fl=0;
		while(pw<=n)
		{
			if((n-pw)%b==0)
			{
				fl=1;
				break;
			}
			pw*=a;
		}
		puts((fl)?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：2)

## 题意

给定一个 $n$，请问他是否分解为 $a^x+by$ 的形式？

## 分析

如果我们把这个条件，在模 $b$ 意义下讨论，事情就有意思起来了。

实际上，这样就相当于是 $n\equiv a^x\pmod b$。

这种情况下，随着 $x$ 的增长，作为指数，整体值会很快地变大，所以单纯地枚举 $x$ 可以再限定时间内枚举完毕。

但是值为 $1$ 的时候还是需要单独讨论。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int T,n,a,b;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>a>>b;
		if(a==1){
			if(n%b==1||n==1||b==1)puts("Yes");
			else puts("No");
		}else{
    		int f=0;
    		for(int i=1;i<=n;i*=a)
    		    if(i%b==n%b)f=1;
    		if(f)puts("Yes");
    		else puts("No");
		}
	}return 0;
}
```

---

## 作者：Cocoly1990 (赞：1)

先观察题目，我们可以发现，对于一个已在集合内的数 $x$，有两种操作

1.把 $ax$ 加入集合

2.把 $x+b$ 加入集合

又因为初始在集合内的只有 $1$，所以最终能在集合中的数一定能表示成 $a^x+by$.

那么判断一个数是否在集合中仅需判断其是否能表示成上述形式，有一个非常重要的性质，就是在模 $b$ 的意义下，$n$ 和 $a^x$ 相等. 

显然该数会随 $x$ 的增长指数级增长，所以只需要枚举 $a$，判断 $n$ 和 $a^x$ 在膜 $b$ 意义下的关系即可。特别的，当 $a=1$ 时记得特判

---

## 作者：CSP_Sept (赞：1)

### Description

给定 $a,b$ 和集合 $S$，规定：

- $1\in S$
- 若 $x\in S$，则 $ax\in S,x+b\in S$。

给定 $n$，询问是否有 $n\in S$。

### Solution

对于一个整数 $x$，我们若先把它加上 $b$，再乘上 $a$，会得到 $ax+ab$。

这样是等价于先把 $x$ 乘上 $a$，再加上 $a$ 个 $b$ 的。

所以我们把所有加上 $b$ 的操作移到最后。

开始的时候疯狂构造 $a^k$，使得 $(n-a^k)\bmod b=0$。

若 $a^k>n$，则输出 `No`。

注意特判 $a=1$ 的情况。

### Code

[121227572](http://codeforces.com/contest/1542/submission/121227572)

---

## 作者：BorisDimitri (赞：1)

# 题意
有一个集合，初始时只有 $1$ 一个元素。

这个集合有一个性质： **若 $x$ 在集合中，则 $x\times a$ 和 $x+b$ 都在集合中。** ($a$ 与 $b$ 为给出的常数)。

给出 $t$ 个询问，回答 $n$ 是否在常数为 $a,b$ 的集合中。

# 分析
我们来模拟一下这个集合生成的过程。

>1. 因为集合中有 $1$ ,我们把 $1 \times a$ 和 $1 + b$ 放入集合中。 
$$Set :1,a,1+b$$
>
>2. 因为集合中有 $a$ ,所以我们将 $a \times a$ 和 $a + b$ 放入集合中。
>
>$$Set :1,a,1+b,a^2,a+b$$
>
>3. 因为集合中有 $1+b$ ,所以我们将 $a \times (1+b)$ 和 $1+2b$ 放入集合中。
>
>$$Set :1,a,1+b,a^2,a+b,a + ab, 2b + 1$$
>
>4. 因为集合中有 $a^2$ ,所以我们将 $a^3$ 和 $a^2 + b$ 放入集合中。
>
>$$Set :1,a,1+b,a^2,a+b,a + ab, 2b + 1,a^3,a^2+b$$

我们发现，这个集合中的所有数都可以表示为 $a^{k_1}+k_2 \times b + c$ ($c$ 取 $0$ 或 $1$)。

所以我们只需要枚举 $a^{k_1}$ ，那么就看看 $(n-c)$ 是否可以被 $b$ 整除，是则输出 `Yes`,否则输出 `No`。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long      LL;
const LL Mod = 1e9 + 7;

inline bool solve(LL n, LL a, LL b)
{
	if(a == 1) return (n-1) % b == 0;
    for(register LL i=1,x;i<=n;i*=a)
    {
    	x = n - i;
    	if(x % b == 0) return 1;
    }
    	
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    
    LL t;
    cin>>t;
    
    while(t--)
    {
    	LL n,a,b;
    	cin>>n>>a>>b;
    	
    	if(solve(n,a,b)) cout<<"Yes"<<endl;
    	else cout<<"No"<<endl;
    }
    
    return 0;
}
```

---

