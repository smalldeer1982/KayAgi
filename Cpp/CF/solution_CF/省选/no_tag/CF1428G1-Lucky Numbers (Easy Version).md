# Lucky Numbers (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q=1 $ . You can make hacks only if all versions of the problem are solved.

Zookeeper has been teaching his $ q $ sheep how to write and how to add. The $ i $ -th sheep has to write exactly $ k $ non-negative integers with the sum $ n_i $ .

Strangely, sheep have superstitions about digits and believe that the digits $ 3 $ , $ 6 $ , and $ 9 $ are lucky. To them, the fortune of a number depends on the decimal representation of the number; the fortune of a number is equal to the sum of fortunes of its digits, and the fortune of a digit depends on its value and position and can be described by the following table. For example, the number $ 319 $ has fortune $ F_{2} + 3F_{0} $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428G1/2e5dc16252276b0ec85d4bf61f3eff843360d5df.png)Each sheep wants to maximize the sum of fortune among all its $ k $ written integers. Can you help them?

## 说明/提示

In the first test case, $ 57 = 9 + 9 + 39 $ . The three $ 9 $ 's contribute $ 1 \cdot 3 $ and $ 3 $ at the tens position contributes $ 2 \cdot 1 $ . Hence the sum of fortune is $ 11 $ .

In the second test case, $ 63 = 35 + 19 + 9 $ . The sum of fortune is $ 8 $ .

## 样例 #1

### 输入

```
3
1 2 3 4 5 6
1
57```

### 输出

```
11```

## 样例 #2

### 输入

```
3
1 2 3 4 5 6
1
63```

### 输出

```
8```

# 题解

## 作者：zhoukangyang (赞：9)

~~双倍经验题解~~

[更棒的体验](https://www.cnblogs.com/zkyJuruo/p/13834434.html)

这题没有压行就成 $\texttt{Hard Version}$ 最短代码解了（

要知道这题那么 $sb$ 就不啃 $D$ 和 $E$ 了。

## $\texttt{Solution}$
首先有一个非常简单但是错误的多重背包的想法：

让分拆出来的 $k$ 个数中，每一个数在十进制下每一位都是 $0, 3, 6$ 或 $9$，于是对于第 $x$ 位把 $3k$ 个大小为 $3 \times 10^x$, 价值为 $F_x$ 的物品丢进多重背包里面，然后输出答案。

这样子显然是不对的，例如输入的数不是 $3$ 的倍数就被卡掉了。因为还可能在某一位上价值是 $0$。然后考虑贪心，我们肯定要让这些位置上不是 $0, 3, 6, 9$ 的位置越少越好。

有一个很显然的结论：一定可以让某一位上价不是 $0, 3, 6, 9$ 的个数减少到 $1$。证明：如果有两个非 $0, 3, 6, 9$ 的数 $a$ 和 $b$。如果 $a + b > 9$, 那么可以变成 $9$ 和 $a+b-9$; 否则可以变成 $0$ 和 $a+b$。

那么我们只要对这不是 $0, 3, 6, 9$ 的那些位置进行特殊处理即可。为了方便，我们把这些位放在同一个数上。可以对于这些数提前统计他们的价值。然后对于剩下 $k-1$ 个数，按照前面所提到的错误做法，对于第 $x$ 位把 $3(k-1)$ 个大小为 $3 \times 10^x$, 价值为 $F_x$ 的物品丢进多重背包里面。但是这样子会 $TLE$, 然后改成二进制优化多重背包即可。~~不会二进制优化背包？[毙了吧](https://www.cnblogs.com/santiego/p/11183167.html)~~

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define L(i, j, k) for(int i = (j); i <= (k); i++) 
#define R(i, j, k) for(int i = (j); i >= (k); i--) 
#define ll long long 
const int N = 1e6 + 7; 
int n, m, k, sz, t, q;
ll p[6], f[N];
void Push(int v, ll w) { R(i, 1e6, v) f[i] = max(f[i], w + f[i - v]); }
void gg(int v, int w) {
	int now = min(k, (int)1e6 / v);
	for(int i = 1; i < now; i <<= 1) now -= i, Push(v * i, 1ll * w * i); 
	Push(v * now, 1ll * w * now);
}
int main() {
	scanf("%d", &k), sz = 1, k = 3 * (k - 1);
	L(i, 0, 5) scanf("%d", &p[i]);
	L(i, 0, 1e6) {
		int now = 0, x = i, s = x % 10;
		while(x) {
			if(s % 3 == 0) f[i] += 1ll * p[now] * (s / 3);
			x /= 10, ++now, s = x % 10;
		}
	}
	L(i, 0, 5) gg(sz * 3, p[i]), sz *= 10;
	scanf("%d", &q);
	while(q--) scanf("%d", &t), printf("%lld\n", f[t]);
	return 0;
}
```

---

## 作者：HC20050615 (赞：6)

# 题意
看翻译只能懂个大概（连数字都能写错）。然后自己用机翻看了一下，终于懂了。

没看懂题的可以看这里：

给定 $q$ 个位数不超过 $6$ 的数 $n_1\sim n_q$ ，将这每个数分为 $k$ 个数（$k$ 个数和为 $n$）。
对于每个数来讲，其权值为所有数位的权值之和。每个数在每个数位的权值如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/z7m9x4h8.png)

对于每个 $n$ ，使其分成的 $k$ 个数的权值最大，求最大权值。
# 分析
仔细观察我们可以发现：

一个 $9$ 所贡献的权值等同于三个 $3$ 贡献的权值。同理，一个 $6$ 所贡献的权值等同于两个 $3$ 贡献的权值。所以我们完全可以抛开 $3$ 和 $6$ 不看，将其全部转化为 $3$ 考虑。

又注意到其余数值的贡献均为 $0$ ，因此，我们要尽可能将 $n$ 分为很多个三。

我们对于每个分开来的数（将其定为 $a_1 \sim a_k$ ），都将其分成各个数位，因为每个数位的贡献均为单独计算的。

但是我们必须要将 $n$ 完全拆完，所以并不能使每个 $a_i$ 都成为由 $3$ 组成的数，所以一定要有数做不了贡献。但我们要尽可能将没有贡献的数的个数减小，这时我们可以发现，其实所有无法贡献的数可以完全集中在一个 $a_i$ 上，让另外的 $k-1$ 个数都可以做出贡献。

假设有两个数第 $i$ 位无法做出贡献，记这两个数该位上的数字分别为 $x$ 和 $y$：

1. 若 $x+y\le9$ ，则可使 $z=x+y$ 作为单独的一个数位，就可将两个无法贡献的数位变为一个。

2. 若 $x+y>9$ ，则可使 $w=9,z=x+y-9$ 代替原 $x,y$ 其中 $w$ 可以正常贡献，同样只有一个数位无法贡献。

因此，我们可以得到一个结论，每一位最多只有一个 $a_i$ 无法进行贡献。

我们可以将这每个无法进行贡献的数位全部转移在 $a_k$ 上，以保证其他的数均能表示为由 $3、6、9$ 构成的数。

这时，我们可以将这个问题转化为背包问题。

我们要分的空间为 $n$ ，每个物品的重量为 $3\times10^i$ ，其对应价值为 $f[i]$ ，每个物品有 $3\times(k-1)$ 个。

为什么是 $3*(k-1)$ 个呢？

因为最后的 $a_k$ 要用于装多出来的无法贡献的数。而对于每个数，其每位上都可以装 $0\sim3$ 个三（$0、3、6、9$），所以每一种三（指在各个数位上），只要装的个数小于等于 $3\times(k-1)$，就一定可以装下。

这就成为了一个多重背包，因为数据较大，所以要使用二进制优化才能通过。

那剩下的无法贡献的怎么办呢?

我们可以再弄一个必须装满分组背包，因为每个数位仅可以选（$0\sim9$），不可以重复。注意，其中的 $3、6、9$ 能够贡献，并不是一定无法贡献。

对于 $hard$ 版本，我们要先预处理每个 $n$ 的答案（$0 \sim 999999$），然后再输出。

所以其实两个版本难度差不多？怪不得都是黑的。。。
# Code
（代码有注释，如果还不是很懂的话可以看看代码）

~~个人认为码风还不错~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
long long p[6];//即原文f，因为个人习惯不想重名
int q;
long long f[1000001];//答案
long long w[1000001];
long long c[1000001];//每个物品的质量、体积
//这几个long long 一定要开，不开过不了（我就连交了3次）
int power=3;
int tot;
int main()
{
	cin>>k;
	for(int i=1;i<=999999;i++)
	{
		f[i]=-0x7ffffffffffff;//赋初值，因为必须装满，装不满的赋为极小值，0x7fffffff不够大，可以再多加几个f，不然要被Hake
	}
	for(int i=0;i<=5;i++)
	{
		cin>>p[i];
	}
	for(int i=0;i<=5;i++)
	{
		long long t=3*(k-1);
		long long now=1;
		while(t>now)
		{
			t-=now;
			w[++tot]=p[i]*now;
			c[tot]=power*now;
			now*=2;
		}
		w[++tot]=p[i]*t;
		c[tot]=power*t;
		power*=10;//二进制优化拆物品
	}
	for(int i=1;i<=tot;i++)
	{
		for(int j=999999;j>=c[i];j--)
		{
			f[j]=max(f[j],f[j-c[i]]+w[i]);//先多重背包
		}
	}
	power=1;
	for(int i=0;i<=5;i++)
	{
		for(int j=999999;j>=0;j--)
		{
			for(int x=1;x<=9;x++)
			{
				if(j<x*power)
				{
					break;
				}
				f[j]=max(f[j],f[j-x*power]+(!(x%3))*(x/3)*p[i]);
			}
		}	
		power*=10;
	}//分组背包，记得是要装满的
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int n;
		cin>>n;
		cout<<f[n]<<endl;//直接输出答案
	}
	return 0;
}
```

蒟蒻有生以来第一道黑题题解（~~说不定以后就不是了~~）

---

## 作者：Komorebi_03 (赞：3)

## 前置知识
很有难度的 DP 题。

要用到多重背包和分组背包的知识。

这两部分内容 OI-wiki 上都有详细的说明，这里给出[网址](https://oi-wiki.org/dp/knapsack/)。

## 思路
首先可以发现可以直接忽略 和 ，因为6可以表示为 $2 \times 3$，9可以表示为 $3 \times 3$。

还有一个发现是不能产生贡献的数位一定可以放在一个数里面，那么题目就可以转化为：有若干个物品 $i$ 为 $(3 \times 10^i,F_i)$，数量为 $3k-3$ 个，选出若干个物品再选上一个整数使重量为 $n$，且保证价值和最大。

设 $dp_x$ 表示选出若干个重量和为 $x$ 的物品的最大价值，需要多重背包来解决，并且可以用二进制分组或者单调队列进行优化。

然后考虑剩下的一个数，相当于有若干组物品，每组物品最多选一个，第 $i$ 组的物品分别是 $(1 \times 10^i,0)$，$(2 \times 10^i,0)$，$(3 \times 10^i,0)$ 以此类推，价值同理。

要求选出的物品价值和最大，这部分则需要分组背包来做。

G1 和 G2 的区别就在于询问的次数不同，也就是 $1$ 和 $10^5$ 的区别。

还有注意开 long long。

```cpp
//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 0x3f3f3f3f3f;
const int N = 1e6+10;
int K,q,num,sum,cnt,qwq=3,n[N],f[10],w[N],c[N],dp[N];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

signed main()
{
    K=read();
    for (int i=0;i<6;i++)
        f[i]=read();
    q=read();
    for (int i=1;i<=q;i++)
        n[i]=read();
    memset(dp,-INF,sizeof(dp));
    dp[0]=0;
    for (int i=0;i<6;i++)
    {
        num=3*(K-1);
        sum=1;
        while(num>sum)
        {
            num-=sum;
            w[++cnt]=f[i]*sum;
            c[cnt]=qwq*sum;
            sum*=2;
        }
        w[++cnt]=f[i]*num;
        c[cnt]=qwq*num;
        qwq*=10;
    }
    for(int i=1;i<=cnt;i++)
        for(int j=999999;j>=c[i];j--)
            dp[j]=max(dp[j],dp[j-c[i]]+w[i]);
    qwq=1;
    for(int i=0;i<=5;i++)
    {
    	for(int j=999999;j>=0;j--)
        {
       	    for(int k=1;k<=9;k++)
            {
            	if(j<k*qwq)
                    break;
                dp[j]=max(dp[j],dp[j-k*qwq]+(!(k%3))*(k/3)*f[i]);
            }
        }
        qwq*=10;
     }
     for(int i=1;i<=q;i++)
     	cout<<dp[n[i]]<<"\n";
    return 0;
    //Amireux_35
}
```


---

## 作者：Wilderness_ (赞：1)

个人认为是一道背包神题。

~~别看背包板子是橙，难起来也能恶心死人。~~
## 思路
首先，我们不难想出将这个数拆成多个各个数位均是 $3$ 的倍数的数，也不难发现若一个数不是 $3$ 的倍数，不可能做到如上拆分。所以，我们要想出一种使得拆出来的数数位为 $3$ 的倍数的位数尽可能的多（换句话说，即数位上不为 $3$ 的倍数的位数尽可能少）。

根据经验，我们可以得出一些结论：
- 若 $a+b>9(0<a\le9,\ 0<b\le9)$ 时，则 $a+b$ 可以被拆分为 $a+b-9$ 和 $9$。

我们根据这一结论，可以发现，不论原数被拆分多少个数，这些数同一数位上都至少有一种拆分满足：这些数的这一位上至多有一个不为 $3$ 的倍数。

既然每个数位上至多有一个不为 $3$ 的倍数，我们计算值的时候又发现 $0$ 对于答案的贡献为 $0\times f_i$，$3$ 对于答案的贡献为 $1\times f_i$，$6$ 对于答案的贡献为 $2\times f_i$，$9$ 对于答案的贡献为 $3\times f_i$，我们便可以将这些位置上为 $0,3,6,9$ 的数记下其含有 $3$ 的个数，则这个位置上最多会有 $(k-1)\times 3$ 个 $3$。

对于这些数位上为 $0,3,6,9$ 的数位，我们对其进行多重背包一样的操作，即：
> 给定一个大小为 $n$ 的背包，每种物品的大小是 $3\times 10^i$，价值为 $f_i$，每种物品最多有 $(k-1)\times3$ 个，求最大价值。

那么对于数位上不为 $0,3,6,9$ 的数位，我们对其进行特殊操作。因为每一位都不相同且同一数位上只能选一个 $0,1,2,3,4,5,6,7,8,9$ 中的数字，所以我们将其转化为一个分组背包：
>给定一个大小为 $n$ 的背包，共有 $6$ 组物品且每组物品中物品大小分别为 $j\times10^i$，其中每个物品的价值为 $f_i$，求最大价值。

然后就能过 Easy 版了。

对于 Hard 版，我们只要预处理 $0,1,2,\cdots,999999$ 每一个数分成 $k$ 个数的最大值即可。

## Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
#define M 1145141
#define Mn 999999//n最大为999999，所以每次逆向枚举时从999999开始枚举
using namespace std;
const ll tp[6]={1,10,100,1000,10000,100000};//避免计算10^(1~6)
ll k,q,cnt,f[6],w[M],c[M],dp[M];
int main()
{
	memset(dp,-INF,sizeof(dp));dp[0]=0;//应为分组背包必须装满，所以赋初值为-INF 
	scanf("%lld",&k);
    for(ll i=0;i<=5;++i)scanf("%lld",&f[i]);
    for(ll i=0;i<=5;++i)//对于每一位，多重背包二进制优化拆分
    {
		/*
			由于对于数字每一位，拆分后的数字中最多只有1个数的这一位不能被3整除（易证明），
			而其余每一个数位上都可以放0/1/2/3个'3'（'0'为0个'3'，'3'为1个'3'，'6'为2个'3'，'9'为3个'3'），
			所以每个数位最多能放有3*(k-1)个'3'。 
		*/
    	ll num=3*(k-1); 
        for(ll t=1;t<=num;t<<=1)
        {
			w[++cnt]=f[i]*t;
            c[cnt]=3*tp[i]*t;
			num-=t;
        }
        w[++cnt]=f[i]*num;
        c[cnt]=3*tp[i]*num;
    }
    for(ll i=1;i<=cnt;++i)//处理3的倍数部分，需要跑多重背包 
        for(ll j=Mn;j>=c[i];--j)
            dp[j]=max(dp[j],dp[j-c[i]]+w[i]);
    for(ll i=0;i<=5;++i)//处理非3倍数的部分，需要跑分组背包 
    	for(ll j=Mn;j>=0;--j)
       	    for(ll l=1;l<=9;++l)//枚举数每一位 
            	if(j>=l*tp[i])
            	{
            		if(l%3==0)dp[j]=max(dp[j],dp[j-l*tp[i]]+(l/3)*f[i]);//l能被3整除时别忘了加f[i]*l/3的值 
            		else dp[j]=max(dp[j],dp[j-l*tp[i]]);
				}
                	
    scanf("%lld",&q);
    for(ll i=1,x;i<=q;++i)scanf("%lld",&x),printf("%lld\n",dp[x]);
    return 0;
}
```

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/cf-1428-g2)

## [题意](https://codeforces.com/problemset/problem/1428/G1)
给定 $k, F_0, F_1, F_2, F_3, F_4, F_5$。

你要把一个位数最多 $5$ 位的数 $n$，拆成 $k$ 个数的和，对 $k$ 个数中的每一个数的第 $i$ 位是 $3$ 的 $u$
倍的话就会获得 $u \times F_i$ 的价值。一个方案的价值为所有价值之和。

你要让价值最大，求最大价值。

多组询问 $Q$ 次。

$1 \leq n \leq 10^6, Q = 1$

## 题解
每一位最多只有一个数不是 $3$ 的倍数，调整法证明。把不是 $3, 6, 9$ 的都放到最后一个数上，前 $k$ 个数就可以直接做多重背包求。

转化为背包大小为 $n$，每个物品重 $3 \times 10^i$，价值为 $F_i$，个数 $3 \cdot (k − 1)$ 个。然后用分组背包把后一个数的每一位加进去 $0 \to 9$ 都能选，但是只有 $3, 6, 9$ 才有贡献。

使用二进制拆分，时间复杂度 $\mathcal O(n \log k + Q)$。

## 代码
```cpp
// By rbtree (https://rbtr.ee)
// Please submit with C++14!
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#define ra _Read()

using tp = long long;
tp _Read();
using namespace std;
constexpr bool __MTCS__ = 0;
constexpr tp Hat_N = 1e6, pow3[] = {3, 30, 300, 3000, 30000, 300000};

array<tp, Hat_N + 3> f;

void update(tp c, tp v) {
  for (tp i = Hat_N; i >= c; --i) {
    f[i] = max(f[i], f[i - c] + v);
  }
}

namespace __SOL__ {
signed main() {
  tp n = ra * 3 - 3;
  array<tp, 6> a;
  for (tp i : {0, 1, 2, 3, 4, 5}) {
    a[i] = ra;
  }
  for (tp i = 0; i < Hat_N; ++i) {
    for (tp j = -1, k = i; k; k /= 10) {
      f[i] += (!(k % 10 % 3)) * (k % 10) / 3 * a[++j];
    }
  }
  for (tp i : {0, 1, 2, 3, 4, 5}) {
    tp hat = min(n, Hat_N / pow3[i]);
    for (tp j = 1; j < hat; j <<= 1) {
      hat -= j;
      update(pow3[i] * j, a[i] * j);
    }
    update(pow3[i] * hat, a[i] * hat);
  }
  for (n = ra; n--; printf("%lld\n", f[ra])) {
  }
  return 0;
}
}  // namespace __SOL__

signed main() {
  tp __MTCS__ = ::__MTCS__ ? ra : 1;
  while (__MTCS__--) {
    __SOL__::main();
  }
  return EXIT_SUCCESS;
}

tp _Read() {
  bool __neg(0);
  char __c(getchar());
  tp __val(0);
  for (; __c < 48 || __c > 57; __c = getchar()) {
    __neg = __c == 45;
  }
  for (; __c > 47 && __c < 58; __c = getchar()) {
    __val = __val * 10 + (__c & 15);
  }
  return __neg ? ~__val + 1 : __val;
}
```

---

## 作者：ywy_c_asm (赞：0)

这是一个完全不同的基于贪心填9的只能做$q=1$的垃圾做法……

这里需要用到在最优情况下的两个和**9**有关的性质：

1.在同一位上，不是9的数字和不超过9。

2.在同一位上，3或6最多只会出现一次。

这样是因为我们出于$k$的限制需要尽量少地填（填不满可以直接填0），3个3可以等效地合并成一个9，而多个和大于等于9的数可以在不改变和的情况下拆出9来，所以贪心填9一定是最优的。

于是，如果我知道了这位的数位和，就能用贪心填9的策略直接算出凑出这位的数位和的最优价值。那么这个看上去就可以dp了：$f[i][j]$表示仅考虑高$i$位，已经凑出来的和为$j$的最优价值，每次枚举这位的数位和即可。

直接这样是过不去的，因为越到低位，时间代价越高（因为对于每一位的$j$至多取到$\frac n{10^i}$）。对于第2位的dp就需要花费$\frac n {100}*\frac n {10}$的代价，但第3位则只需要$\frac n{1000}*\frac n{100}=10^7$的代价，那么现在我们就可以有这样一个平衡复杂度的思路，令$g[x]$为仅考虑最低的两位，把$x$凑出来的最优价值，那么我们就可以把它与从第3位开始的上面那个dp结合，即$ans=\max_{0<=x<=n}\{g[x]+f[3][\frac{n-x}{100}]\}$。~~也正是因为需要做max卷积的原因它只能做$q=1$的版本……~~

考虑$g[x]$如何求，根据上面那两个性质，我们可以枚举第一位以及第二位所有小于9的数字和以及占的位数，它们只会占0,1,2位（因为可能还会拆出一个有价值的6或3），$x$剩下的部分需要用若干个$9$或$90$凑出来。那么该如何分配9和90的个数呢？这也是可以贪心的。如果$f_1>=10f_0$，那么一个90比10个9更优，最大化90的个数。否则，与其在第二位填一个90还不如拆成第一位的如若干个9更优，最大化9的个数。这个可以用整除以及取模简单算出来。

显然我们需要保证$(n-x)\%100=0$，那么$x$的个数就是$\frac n {100}<=10^4$，对每个$x$枚举除了9之外的位的代价是$3*3*9*9=729$，再加上对3到6位的代价大概$10^7$的dp，这就可以过掉此题了。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<unordered_map>
#include<unordered_set>
#define ls(_o) (_o<<1)
#define rs(_o) ((_o<<1)|1)
#define N 1000010
#define p 998244353
#define inf 1234567890
#define ll long long
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333)if(c>='0'&&c<='9')break;
		n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return n;
		}
	}
	ll dp[6][N],val[6];
	void ywymain(){
		int k=get(),f0=get(),f1=get(),f2=get(),f3=get(),f4=get(),f5=get();
		val[0]=f0; val[1]=f1; val[2]=f2; val[3]=f3; val[4]=f4; val[5]=f5;
		int q=get(); while(q){
			q--; int n=get(),dk=100000;
			memset(dp,128,sizeof(dp));
			for(int i=0;i<=9*k&&i<=n/100000;i++){
				int bits=i/9,rem=i%9;
				if(k-bits<=1) dp[5][i]=bits*(ll)f5*3ll+(rem==3)*f5+(rem==6)*2ll*f5;
				else dp[5][i]=bits*(ll)f5*3ll+f5*(ll)min(k-bits,rem/3);
			}
			for(int i=4;i>=2;i--){
				for(int a=0;a<=9*k&&a<=n/(dk/10);a++){
					int bits=a/9,rem=a%9;
					ll ans;
					if(k-bits<=1) ans=bits*(ll)val[i]*3ll+(rem==3)*val[i]+(rem==6)*2ll*val[i];
					else ans=bits*(ll)val[i]*3ll+val[i]*(ll)min(k-bits,rem/3);
					for(int b=0;b<=n/dk;b++) if(dp[i+1][b]>=0) dp[i][a+b*10]=max(dp[i][a+b*10],dp[i+1][b]+ans);
				}
				dk/=10;
			}
			ll ans=0;
			for(int x=0;x<=99*k&&x<=n;x++){
				if((n-x)%100||dp[2][(n-x)/100]<0) continue;
				for(int a=0;a<9;a++){
					for(int b=0;b<9;b++){
						if(a*10+b>x||(x-a*10-b)%9) continue;
						int rem=x-a*10-b;
						for(int i=(a!=0);i<=2&&i<=k;i++){
							for(int j=(b!=0);j<=2&&j<=k;j++){
								if(90*(k-i)+9*(k-j)<rem) continue;
								ll rest=0;
								if(i<=1) rest+=(a==6)*2ll*f1+(a==3)*f1;
								else rest+=(a/3ll)*(ll)f1;
								if(j<=1) rest+=(b==6)*2ll*f0+(b==3)*f0;
								else rest+=(b/3ll)*(ll)f0;
								if(f1>=10ll*f0){
									int cnt9=max(rem%90,rem-90*(k-i))/9,cnt90=min(k-i,rem/90);
									if(cnt9>k-j) continue;									
									ans=max(ans,dp[2][(n-x)/100]+cnt9*(ll)f0*3ll+cnt90*(ll)f1*3ll+rest);
								}else{
									if(k-j<(rem%90)/9) continue;
									int cnt9=(rem%90)/9+((k-j-(rem%90)/9)/10)*10;
									cnt9=min(cnt9,rem/9);
									int cnt90=(rem-9*cnt9)/90;
									if(cnt9>k-j||cnt90>k-i) continue;
									ans=max(ans,dp[2][(n-x)/100]+cnt9*(ll)f0*3ll+cnt90*(ll)f1*3ll+rest);
								}
							}
						}
					}
				}
			}
			cout<<ans<<endl;
		}
	}
}
int main(){
	ywy::ywymain();
	return 0;
}
```

---

