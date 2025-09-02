# Equations of Mathematical Magic

## 题目描述

给出 $ a $，判断方程 $ a-(a \oplus x)-x=0 $ 的解的个数。（其中 $ \oplus $ 为异或）

## 样例 #1

### 输入

```
3
0
2
1073741823
```

### 输出

```
1
2
1073741824
```

# 题解

## 作者：Sooke (赞：14)

### 解题思路

把 $a \oplus x$ 这项移到右边，我们得到：

$$a - x = a \oplus x$$

这道题巧妙在于，不同**二进制位**对答案的贡献**互不影响**。$\oplus$ 本身就是定义于二进制的运算，尽管某个二进制位 $-$ 运算可能会产生负数，但一旦有负数产生，就不会对答案产生贡献，更别提是否影响其他位的贡献了，以上通过**归纳法**可以证明。

于是，我们只需要关心 $a,\ x \in \{0,\ 1\}$ 时解的情况。考虑使用**列表法**：

||||||
| :-: | :-: | :-: | :-: | :-: |
| $\ \ \ \ \ \ $ $a$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $x$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $a - x$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $a \oplus x$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $a - x = a \oplus x$ $\ \ \ \ \ \ $ |
| $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ 满足 $\ \ \ \ \ \ $ |
| $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $-1$ $\ \ \ \ \ \ $ |  $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ 不满足 $\ \ \ \ \ \ $ |
| $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $  | $\ \ \ \ \ \ $ 满足 $\ \ \ \ \ \ $ |
| $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $1$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ $0$ $\ \ \ \ \ \ $ | $\ \ \ \ \ \ $ 满足 $\ \ \ \ \ \ $ |

容易发现，当 $a = 0$ 时，$x$ 只有一个解，当 $a = 1$ 时，$x$ 有两个解。

回到一般情况，因为每个二进制位的贡献互不影响，所以将它们的贡献相乘就是答案。因此，当某个二进制位 $= 0$，它的贡献 $= 1$，相当于没贡献，当某个二进制位 $= 1$，它的贡献 $= 2$。也就是说，只要知道 $a$ 的二进制中有多少位是 $1$，答案就是其 $2$ 的幂次方。

二进制中多少位是 $1$？暴力求吗？不！$\_\_builtin\_popcount$ 函数多方便！

### 代码实现

在 $\_\_builtin\_popcount$ 和~~原力压行~~的帮助下，代码看上去非常短。

```cpp
#include <iostream>

int main() {
    int n; std::cin >> n;
    while (std::cin >> n) { std::cout << (1 << __builtin_popcount(n)) << std::endl; }
    return 0;   
}
```

---

## 作者：communist (赞：5)

题目要求解$a-(a\oplus x)-x=0$的解$x$的个数

移项得$a-x=a\oplus x$

$a$的二进制形式，应该是一个$01$串，异或的过程是不能影响到两个不同的位的，所以我们按位考虑

如果这一位是$0$，那么$x$的这一位也应为$0$，使得异或后答案不会更大

如果这一位是$1$，那么$x$的这一位可以为$0$或$1$，对应到减法中就是没减和减掉

所以答案就是$2^{count~~1~~in~~a}$

```
#include<iostream>
#include<cstdio>
using namespace std;
int t,a;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&a);
		int ans=1;
		while(a)
		{
			if(a%2)
				ans*=2;
			a/=2;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1064B)

# 思路

首先我们需要解一下题目中的方程：

$$a- ( a \oplus x ) -x=0$$

$$a- ( a \oplus x ) = x$$

$$a \oplus x = a-x$$

接着，因为这是一道数论题，我们可以进行列表分析：

| $a$ | 答案 |
| :----------: | :----------: |
| 0 | 1 |
| 1 | 2 |
| 2 | 2 |
| 3 | 4 |
| 4 | 2 |
| 5 | 4 |
| 6 | 4 |
| 7 | 8 |
| 8 | 2 |
| 9 | 4 |

因为答案都是 2 的次幂，所以我们把答案简化为指数：

| $a$ | 答案的指数 |
| :----------: | :----------: |
| 0 | 0 |
| 1 | 1 |
| 2 | 1 |
| 3 | 2 |
| 4 | 1 |
| 5 | 2 |
| 6 | 2 |
| 7 | 3 |
| 8 | 1 |
| 9 | 2 |

我们能发现，每一个答案的底数都是 2，指数都是 $a$ 的二进制中 1 出现的次数，因此，我们可以很快的打出程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long power(int a,int n)//pow对于大数会以指数输出，所以我自己打了一个快速幂
{
	if(n==0)return 1;
	else if(n%2==1)return power(a,n-1)*a;
	else
	{
		long long temp=power(a,n/2);//10年OI一场空，不开 long long 见祖宗
		return temp*temp;
	}
}
int main() 
{
    register long long n,t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
    	cin>>n;
    	long long resl=0;//指数
    	while(n){if(n%2)resl++;n>>=1;}//查找个数，众所周知位运算>>1比普通运算/2要快
	cout<<power(2,resl)<<endl;
    }
    return 0;   
}
```


---

## 作者：Exp10re (赞：0)

这么二进制。

简单结论题。

## 解题思路

移项得到 $a-x=(a \oplus x)$。

简单分析，对于其每一个二进制位 $a_i$ 以及 $x_i$：

- $a_i=1,x_i=1$，此时 $a_i-x_i=0,a_i \oplus x_i=0$，符合题意。
- $a_i=1,x_i=0$，此时 $a_i-x_i=1,a_i \oplus x_i=1$，符合题意。
- $a_i=0,x_i=1$，此时 $a_i-x_i$ 会产生一次退位，$a_i \oplus x_i=1$，一个比原式小，一个比原式大，不符合题意。
- $a_i=0,x_i=0$，此时 $a_i-x_i=0,a_i \oplus x_i=0$，符合题意。

综上所述，对于其每一个二进制位 $a_i$ 以及 $x_i$：

- 当 $a_i=1$ 时，$x_i$ 任取 $1$ 或 $0$。
- 当 $a_i=0$ 时，$x_i$ 必须取 $0$。

即可得出方案数 $=2^{popcnt(a)}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long popcnt(long long x)
{
	long long cnt=0;
	while(x>0)
	{
		cnt+=x&1;
		x/=2;
	}
	return cnt;
}
void work()
{
	long long n;
	scanf("%lld",&n);
	printf("%lld\n",(1<<popcnt(n)));
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：xin700 (赞：0)


这个题目说实话是没有想到的。

$xor$ 的贡献是与位置无关的。

所以我们似乎只需要看 $a,x\in\{1,0\}$ 的情况就能进行归纳了。

然后发现当 $a$ 的二进制位为 $0$ 的时候，贡献为 $1$，因为要相乘来计算贡献，所以这个的贡献就是不计的。

我们还发现当 $a$ 的某一位是 $1$ 的时候贡献是 $2$，所以我们的目标就是算出来：
$$
2^{popcnt(a)}
$$

代码：
```cpp
#include<bits/stdc++.h>
using std::cout; using std::endl;
#define try(i,a,b) for(register signed i=a;i<=b;++i)
#define throw(i,a,b) for(register signed i=a;i>=b;--i)
#define go(i,x) for(register signed i=head[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
namespace xin_io
{
	#define file(a) FILE *FI = freopen(#a".in","r",stdin); FI = freopen(#a".out","w",stdout)
	#define sb(x) cout<<#x" = "<<x<<' '
	#define jb(x) cout<<#x" = "<<x<<endl
	#define debug cout<<"debug"<<endl
	#define gc() p1 == p2 and (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? EOF : *p1++
	#define scanf ak = scanf
	char buf[1<<20],*p1 = buf,*p2 = buf; int ak; typedef long long ll; typedef unsigned long long ull;
	class xin_stream{public:template<typename type>inline xin_stream &operator >> (type &s)
	{
		register int f = 0;s = 0; register char ch = gc();
		while(!isdigit(ch)) {f |= ch == '-'; ch = gc();}
		while( isdigit(ch)) s = (s << 1) + (s << 3) + (ch  xor 48),ch = gc(); return s = f ? -s : s,*this;
	}}io;
}
using namespace xin_io;static const int maxn = 1e6+10,inf = 1e9+7;const ll llinf = 1e18+7;
#define int long long
auto max = [](int x,int y) -> int{return x > y ? x : y;}; auto min = [](int x,int y) -> int{return x < y ? x : y;};
namespace xin
{
	inline short main()
	{
		auto popcnt = [](int x) -> int
		{
			int ret = 0;
			while(x) {ret += (x & 1),x >>= 1;}
			return ret;
		};
		int T;io >> T;
		while(T--)
		{
			register int a; io >> a;
			printf("%lld\n",(1ll << popcnt(a)));
		}
		return 0;
	}
}
signed main() {return xin::main();}
```

---

