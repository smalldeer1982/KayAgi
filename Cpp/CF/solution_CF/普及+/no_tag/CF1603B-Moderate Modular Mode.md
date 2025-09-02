# Moderate Modular Mode

## 题目描述

YouKn0wWho has two even integers $ x $ and $ y $ . Help him to find an integer $ n $ such that $ 1 \le n \le 2 \cdot 10^{18} $ and $ n \bmod x = y \bmod n $ . Here, $ a \bmod b $ denotes the remainder of $ a $ after division by $ b $ . If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 说明/提示

In the first test case, $ 4 \bmod 4 = 8 \bmod 4 = 0 $ .

In the second test case, $ 10 \bmod 4 = 2 \bmod 10 = 2 $ .

In the third test case, $ 420 \bmod 420 = 420 \bmod 420 = 0 $ .

## 样例 #1

### 输入

```
4
4 8
4 2
420 420
69420 42068```

### 输出

```
4
10
420
9969128```

# 题解

## 作者：pldzy (赞：8)

提供一种分类讨论的做法。

------------

### 思路

对于输入的 $x$ 和 $y$，会有一下三种情况：

1. $x>y$
	
    易得，此时 $n \gets x+y$ 是符合条件的：
    
    $(x + y) \mod x = y = y \mod (x +y)$
1. $x = y$

	 易得，此时 $n \gets x$ 是符合条件的（证明略）。
     
1. $x<y$
	
    我们发现，当 $x$ 和 $y$ 的差小于 $x$ 时，有 $n \gets x+\dfrac{y-x}{2}$ 是符合条件的。
    
    所以我们只要每次让 $x$ 和 $y$ 的值接近即可，也就是让 $x$ 的值翻倍但却不大于 $y$。
    
这样三种情况讨论完，这道题也就做出来了~

-----

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rint register int
int t, x, y;

int main () 
{
	scanf ("%d", &t);
	while (t--)
	{
		scanf ("%d %d", &x, &y);
		if (x > y) printf ("%d\n", x + y);
		if (x == y) printf ("%d\n", x); 
		if (x < y)
		{
			int s = x, tim = y / x;
			x = x * (tim + 1);
			if (x > y) x -= s;
			printf ("%d\n", (y - x) / 2 + x);
		}
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：6)

### 解题思路：

显然是构造题。

分两种情况，首先是 $x>y$，这一种非常简单，直接就是 $x+y$。因为 $(x+y)\bmod x=y=y \bmod (x+y)$。

后一种，也就是 $x\le y$ 的情况稍微复杂一点，~~不能直接猜~~。

发现如果要使得条件满足，一定有 $n\le y$，否则 $n \bmod x<y$，一定不满足。那么一定有 $n=y-k$，此时 $y-k \bmod x=y\bmod (y-k)=k$，化简，立刻有：$2\times k=y \bmod x$，即 $k=\dfrac{y \bmod x}{2}$ （注意这里呼应了题面中的一定为偶数），所以 $n=y-\dfrac{y\bmod x}{2}$。

---

~~考察了一元一次方程的求解，属于幼儿园题~~。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long T,x,y;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&x,&y);
		if(x>y)printf("%lld\n",x+y);
		else printf("%lld\n",(y-(y%x)/2));
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：4)

## 思路

~~遇事不决，大力分讨~~！

- 对于 $x>y$ 的情况：我们令 $n \bmod x=y \bmod n = y$，可以发现，$n = y+kx$ 且 $n>y$，这个时候 $n=x+y$ 即可。

- 对于 $x=y$ 的情况：$n=x$，这个时候 $n=x=y$，$n \bmod x = y \bmod n = 0$。

- 对于 $x<y$ 的情况：假设 $n=y-k$，那么 $(y-k) \bmod x = y \bmod (y-k) = k$。

	设 $y-k = ax+k$，易得 $y=ax+2k$。所以 $y \bmod x = 2k$，$k = \dfrac{y \bmod x}{2}$，又因为 $x,y$ 是偶数，恰好满足条件。
    
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int T; cin>>T;
	while(T--){
		int x,y; cin>>x>>y;
		if(x>y) cout<<x+y<<endl;
		else if(x==y) cout<<x<<endl;
		else cout<<y-(y%x)/2<<endl;
	}return 0;
}
```

---

## 作者：Alex_Wei (赞：4)

> CF1603B. [Moderate Modular Mode](https://codeforces.ml/problemset/problem/1603/B) *1600

分两种情况讨论：

- 若 $x>y$ 则 $n=x+y$ 符合条件，因为 $(x+y)\bmod x=y$ 且 $y\bmod (x+y)=y$。
- 否则有 $x\leq y$，考虑设 $d$ 为 $\leq y$ 且是 $x$ 的倍数的最大数，此时 $d\bmod x=0$ 而 $y\bmod d=y-d$：因为保证了 $x\leq y$ 所以一定有 $2d>y$ 即 $1\leq\dfrac{y}{d}<2$ 否则 $2d$ 也符合条件，故 $y\bmod d=y-\left\lfloor\dfrac{y}d\right\rfloor\times d=y-d$。考虑将 $d$ 增加 $1$ 会发生什么：$d\bmod x$ 增加 $1$，而 $y\bmod d$ 会减少 $1$。接下来就很简单了：因为 $x,y$ 都是偶数所以 $y\bmod d$ 的初值也一定是偶数，令 $\gets d+\dfrac{y\bmod d}2$ 即可。

```cpp
int main(){
	int T; cin >> T;
	while(T--) {
		ll x, y, d; cin >> x >> y;
		if(x > y) cout << x + y << endl;
		else d = y / x * x, cout << d + (y % d / 2) << endl;
	}
    return 0;
}

---

## 作者：Daidly (赞：1)

有趣的题。

$t=10^5,n=1.2\times10^{18}$，要不然就是 $O(t\log n)$，要不然就是 $O(t)$，看起来不像是带 $\log$ 题，思考 $O(1)$ 结论。

$n\bmod x=y\bmod n$

- 若 $x>y$，$(x+y)\bmod x=y\bmod (x+y)$，输出 $x+y$ 即可。

- 若 $x\leq y$：

则 $x\leq n$ 证明：若 $x>n$，则 $n\bmod x=n>y \bmod n$ 不满足题意。

则 $y\ge n$ 证明：若 $y<n$，则 $x\leq y<n,y\bmod n=y\ge x>n \bmod x$ 不满足题意。

所以有 $x\leq n \leq y$。

那么具体 $n$ 为几呢？

设 $y=k\times x+y \bmod x$。

数形结合，数轴上 $n$ 点左边是 $k\times x$ 右边是 $y$，并且 $n\bmod x=y\bmod n$，考虑到 $n-k\times x=y-n$ 满足，则 $n=y-\frac{y \bmod x}{2}$，保证除尽。

下图是 Editorial 中的图，可以更好地理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/yo1vryoa.png)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

int t,x,y;

int main(){
	t=read();
	while(t--){
		x=read(),y=read();
		if(x>y)print(x+y),puts("");
		else print(y-y%x/2),puts("");
	}
	return 0;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

给定两个偶数 $x,y$。

求一个 $n \in [1,2\times10^{18}]$ 满足 $n \bmod x = y \bmod n$。

$t$ 组数据。

对于 $100\%$ 的数据，$1 \leq t \leq 10^5,2 \leq x,y \leq 10^9$。


### 解题思路

当 $x > y$ 时，$(x + y) \bmod x=y \bmod x=y \bmod (x + y)$，所以 $x+y$ 即为答案。

当 $x=y$ 时，$x,y$ 即为答案。

当 $x<y$ 时，很明显 $x \leq n \leq y$。

证明：

如果 $n < x$，那么 $n \bmod x=n$，但 $y \bmod n < n$，不成立，$x \leq n$。

如果 $n >y$，那么 $y \bmod n=y$，但 $n \bmod x < x$，此时 $x \leq y$，不成立，$n \leq y$。

考虑设 $d$ 为 $\leq y$ 且是 $x$ 的倍数的最大数，那么有 $2d>y$。

所以 $1 \leq \frac{y}{d} < 2$，那么 $y \bmod d = y - \left\lfloor \frac{y}{d} \right\rfloor \times d=y-d$。

又因为 $d$ 增加 $1$ 会使 $d\bmod x$ 增加 $1$，而 $y\bmod d$ 会减少 $1$。

所以当 $d$ 增加 $\frac{y \ mod \ d}{2}$ 时，$d \bmod x=y \bmod d$。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, x, y;

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &x, &y);
		if(x > y)
			cout << x + y << "\n";
		else
		{
			int d = y / x * x;
			cout << d + (y % d) / 2 << "\n";
		}
	}
	return 0;
}
```



---

## 作者：KAMIYA_KINA (赞：0)

## Tag

构造。

## Description

给定两个正偶数 $x,y$，求一个整数 $n$ 满足 $n\%x = y\%n$ 。

$T$ 组询问。

$\texttt{data range:} T\leq 10^5,x,y\leq 10^9$。

## Solution

当 $x>y$ 的时候，很容易构造出 $n=x+y$ 就是答案。

对于 $x\leq y$ 的时候，很明显 $x \leq n \leq y$。

证明：

如果 $n < x$，那么 $n\%x =n$，但 $y\%n < n$，所以不成立。

如果 $n>y$，那么 $y\%n=y$，但 $n\%x < x$，此时 $x\leq y$，所以不成立。

得证。

那么只用找一下 $n$ 的位置就可以了。

如果 $n\ge y-y\%x$ 的话，这个问题就转化为了求 $y-y\%x$ 到 $y$ 的中点就可以了，由于 $x,y$ 都是偶数，所以这个中点一定是一个整数，所以直接输出来就行了。

## Code

```cpp
inline void solve() {
    int t = rd;
    while(t--) {
        int x = rd, y = rd;
        if(x <= y) {
            cout << y - (y % x) / 2 << '\n';
        } else cout << x + y << '\n';
        
    }
    return ;
}
```





---

## 作者：Presentation_Emitter (赞：0)

~~小分类讨论，比 julian 水多了，建议红~~

题目大意：求出一个 $n$ 满足 $n \bmod x=y \bmod n$，多组测试。

首先 $y \equiv 0(\bmod ~x)$ 时显然 $n=y$。

对于其它情况：

- $x \gt y$ 时，使 $n \gt x$，则 $n \bmod x=y$，$n$ 取 $x+y$ 即可。
- $x \lt y$ 时，使 $x \lt n \lt y$（$x,y$ 为偶数，因此必定有解），设 $r=y \bmod x$，则 $n=y-\dfrac{r}{2}$ 即可。

代码略。

---

## 作者：KSToki (赞：0)

### 题目大意
给定两个**偶数** $x$ 和 $y$（$2\le x,y\le 10^9$），需要找到一个正整数 $n$，要求 $1\le n \le 2\times 10^{18}$，$n \bmod x=y\bmod n$。
### 题目分析
首先从一些特殊情况入手，当 $y<x$ 时，令 $n=x+y$，则 $n \bmod x=y\bmod n=y$；当 $y$ 是 $x$ 的倍数时可令 $n=y$，则 $n \bmod x=y\bmod n=0$。此时只剩下 $y>x$ 且 $y$ 不是 $x$ 的倍数的情况，并且到现在并没有使用到偶数的条件。

简化一下，假如现在不是模运算，而是减法，那么答案可以是 $\frac{x+y}{2}$，这样 $n-x=y-n=\frac{y-x}{2}$，这样已经非常接近正确答案了，由于 $n \bmod x<x$，可将 $n$ 一直加 $x$ 直到 $y-n<x$，唯一出错的情况为 $y$ 是 $x$ 的倍数，已经被特判了。具体化的说，令 $t=\lfloor\frac{y}{x}\rfloor$，则 $n=\frac{tx+y}{2}$，需要用偶数的条件保证计算出的 $n$ 是整数。

代码就很简单了。
### 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,x,y; 
int main()
{
	T=read();
	while(T--)
	{
		x=read();
		y=read();
		if(y<x)
			putint(x+y);
		else if(x==y)
			putint(x);
		else
		{
			if(y%x==0)
				putint(y);
			else
			{
				int t=y/x;
				putll((1ll*t*x+y)/2);
			}
		}
	}
	return 0;
}
```


---

## 作者：kirky_wang (赞：0)

## 解析
这题主要是推过程，代码很简单。
#### 思路
找规律，发现
当 $x = y$ 时，输出 $x$ 就行了

当 $x > y$ 时，输出 $x + y$ 就可以了，这样可以满足

比较特殊的情况

当 $x < y $ 时，输出 $(y%x)/2+y/x∗x$ 因为都是偶数，所以相除的余数肯定也是偶数所以可以除以二，这样可以使它们的结果刚好是余数的一半。


## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{
	int q; 
	cin >> q;
	while (q -- )
	{
		int x, y;
		cin >> x >> y;
		if (x == y) cout << x << endl;
		else if (x > y) cout << x + y << endl;
		else if (x < y) cout << y % x / 2 + y / x * x << endl;
	}
	return 0;
}
```


---

