# [AGC014A] Cookie Exchanges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc014/tasks/agc014_a

高橋君と青木君とすぬけ君はそれぞれクッキーを $ A,B,C $ 個持っています。

この $ 3 $ 人はお互いにクッキーを交換することにしました。具体的には、以下の操作を繰り返します。

- $ 3 $ 人は同時に、各々が持っているクッキーを半分ずつに分けて、残りの $ 2 $ 人にそれぞれ一方を渡す。

ただし、誰かの持っているクッキーの個数が奇数個になったら、そこで操作を繰り返すのをやめます。

さて、クッキーの交換は何回行うことができるでしょうか。 ただし、無限に続けられる場合もあることに注意してください。

## 说明/提示

### 制約

- $ 1\ ≦\ A,B,C\ ≦\ 10^9 $

### Sample Explanation 1

はじめ、高橋君と青木君とすぬけ君はそれぞれクッキーを $ 4,12,20 $ 個持っており、 - $ 1 $ 回目の操作後は、高橋君と青木君とすぬけ君はそれぞれクッキーを $ 16,12,8 $ 個持っている。 - $ 2 $ 回目の操作後は、高橋君と青木君とすぬけ君はそれぞれクッキーを $ 10,12,14 $ 個持っている。 - $ 3 $ 回目の操作後は、高橋君と青木君とすぬけ君はそれぞれクッキーを $ 13,12,11 $ 個持っている。 $ 3 $ 回目の操作後に高橋君とすぬけ君の持っているクッキーの個数が奇数個になるので、求める回数は $ 3 $ 回となります。

## 样例 #1

### 输入

```
4 12 20```

### 输出

```
3```

## 样例 #2

### 输入

```
14 14 14```

### 输出

```
-1```

## 样例 #3

### 输入

```
454 414 444```

### 输出

```
1```

# 题解

## 作者：Seauy (赞：4)

## 1. Abstract

记一次变换为 $(A,B,C)\to (\frac{A+B}{2},\frac{B+C}{2},\frac{C+A}{2})$，值域为 $v$，连续变换至多 $O(\log v)$ 次就能得到 $A=B=C$。

## 2. 简略的证明

我们可以稍微写出 $(A,B,C)$ 变换几步后的结果：$(\frac{A+B}{2},\frac{B+C}{2},\frac{C+A}{2}), \ (\frac{2A+B+C}{4},\frac{A+2B+C}{4},\frac{A+B+2C}{4}) ,\ (\frac{2A+3B+3C}{8},\frac{3A+2B+3C}{8},\frac{3A+3B+2C}{8}) \dots $

设变换了 $n$ 次，那么分母肯定是 $2^n$，分子上 $A,B,C$ 的系数在三元组里是对称的，且有两个系数是相等的。设特殊的系数为 $f_n$，另外两个相同的系数为 $g_n$，可以得到递推式

$$ f_0=1,g_0=0 $$

$$ f_n=2g_{n-1} $$

$$ g_n=f_{n-1}+g_{n-1} $$

可以推得 $|f_n-g_n| \leq 1$。我们再考察三元组中两个数的差，不妨取 $\frac{f_nA+g_nB+g_nC}{2^n}$ 与 $\frac{g_nA+f_nB+g_nC}{2^n}$，做差后发现

$$ |\frac{f_nA+g_nB+g_nC}{2^n}-\frac{g_nA+f_nB+g_nC}{2^n}|=|\frac{(f_n-g_n)A+(g_n-f_n)B}{2^n}|=|\frac{A-B}{2^n}| $$

如果发现变换时三元组中出现了奇数，那么在变换中途就能输出花的步数，也就是说如果能继续变换一定保证 $|\frac{A-B}{2^n}|$ 为整数，要使得差不为整数就要操作 $O(\log \max\{|A-B|,|B-C|,|C-A|\})=O(\log v)$ 次，而 $A=B=C$ 时就可以输出 $-1$ 了，因此直接模拟复杂度是 $O(\log v)$ 的。

## 3. 不重要的代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a,b,c;
int ans;

ll RAND(int x)
{
	ll ret=0;
	for(int i=1;i<=x;i++) ret=ret*10+rand()%10;
	return ret;
}

int main()
{
	/*a=1,b=0,c=1;
	printf("(%lld,%lld,%lld) mod %lld = (%lld,%lld,%lld)\n",a,b,b,c,a%c,b%c,b%c);
	for(int i=1;i<=20;i++)
	{
		ll A=2*b,B=a+b;
		a=A,b=B;
		c<<=1;
		printf("(%lld,%lld,%lld) mod %lld = (%lld,%lld,%lld)\n",a,b,b,c,a%c,b%c,b%c);
	}
	srand(unsigned(time(0)));
	a=RAND(6)*1024,b=RAND(6)*1024,c=RAND(6)*1024;
	printf("%lld %lld %lld\n",a,b,c);
	for(int i=1;i<=40;i++)
	{
		//if(a&1 || b&1 || c&1) break;
		ll A=a,B=b,C=c;
		a=(B+C)>>1;
		b=(A+C)>>1;
		c=(A+B)>>1;
		printf("%lld %lld %lld\n",a,b,c); 
	}*/
	scanf("%lld %lld %lld",&a,&b,&c);
	while(1)
	{
		if(a&1 || b&1 || c&1) break;
		if(a==b && b==c) return printf("-1\n"),0;
		ll A=a,B=b,C=c;
		a=(B+C)>>1;
		b=(A+C)>>1;
		c=(A+B)>>1;
		++ans;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：火车司机 (赞：3)

## 简要分析

~~这题直接按照题意暴搜就可以了，这为什么不会超时呢，小编也很惊讶，但事实就是这样~~

讲一下为什么可以自信地打个暴搜交上去

题意中提到有可能会无限循环，因此可以想到暴力去找循环节

既然要使暴力找循环节判无解通过此题，那么当没有循环节的时候，相似的搜索规模也必然能通过此题

~~更多的是一种做题直觉吧~~

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int a, b, c;
struct node
{
	int a, b, c;
	inline bool operator<(const node &x) const
	{
		return a ^ x.a ? a < x.a : b ^ x.b ? b < x.b : c < x.c;
	}
	inline bool operator!=(const node &x) const
	{
		return a != x.a && b != x.b && c != x.c;
	}
} t;
map<node, bool> mp;
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
signed main()
{
	read(a), read(b), read(c);
	if ((a & 1) || (b & 1) || (c & 1))
	{
		puts("0");
		return 0;
	}
	for (ri i = 1, ta, tb, tc;; ++i)
	{
		ta = a >> 1, tb = b >> 1, tc = c >> 1;
		a = tb + tc, b = ta + tc, c = ta + tb;
		if ((a & 1) || (b & 1) || (c & 1))
		{
			print(i);
			return 0;
		}
		if (a > b)
			a ^= b ^= a ^= b;
		if (a > c)
			a ^= c ^= a ^= c;
		if (b > c)
			b ^= c ^= b ^= c;
		t = (node){a, b, c};
		if (mp[t])
		{
			puts("-1");
			return 0;
		}
		mp[t] = 1;
	}
	return 0;
}
```


---

