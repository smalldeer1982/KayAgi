# Subarray Sum

## 题目描述

输入三个整数，N，K，S。
请你找到一个N个元素的整数序列，其中每一个元素在1，10的9次方之间。这个序列满足K个子序列的和为S。

## 样例 #1

### 输入

```
4 2 3```

### 输出

```
1 2 3 4```

## 样例 #2

### 输入

```
5 3 100```

### 输出

```
50 50 50 30 70```

# 题解

## 作者：123456zmy (赞：6)

题意：  
你要构造一个长度为 $N$ 的序列，使得其中和为 $S$ 的子串正好有 $K$ 个。输出这个序列。
___
要使一个子串中的数和为 $S$，直接把 $K$ 个数设为 $S$ 再让其它的无论如何都凑不到 $S$ 是最简单的（~~至少我觉得是最简单的~~）。我用的方法是当 $S\ne10^9$ 时用 $10^9$ 填充，否则用 $1$ 填充，因为序列中数不超过 $10^5$ 个，所以后面的 $1$ 是绝对加不到 $10^9$ 的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,s;
int main()
{
	scanf("%d%d%d",&n,&k,&s);
	for(int i=1;i<=k;i++)printf("%d ",s);
	if(s<1000000000)
	{
		for(int i=k+1;i<=n;i++)printf("1000000000 ");
	}
	else for(int i=k+1;i<=n;i++)printf("1 ");
	putchar(10);
	return 0;
}

```

---

## 作者：超级玛丽王子 (赞：0)

AT 总喜欢搞一些奇奇怪怪的构造题。

乍一看这题好像挺难，仔细想想就会发现，想要满足正好 $K$ 个子序列和为 $S$，只需要构造 $K$ 个 $S$ 即可，剩下的数则选择比 $S$ 大的数即可。为了输出效率高，这里选择 $S+1$。这是基于以下两个事实：

- 这 $K$ 个数中任选一个都构成和为 $S$ 的子序列，这样的子序列恰有 $K$ 个；（充分性）
- 这 $N$ 个数中的任意 $i$ 个之和 （$i\ge 1$） 都大于 $S$；（完备性）

至此构造的证明就完毕了，但是实现还有一点细节，就是题目要求构造出的数不超过 $10^9$，那么如果给定的 $S=10^9$，$S+1$ 就不能构造了。但是，由于 $S$ 已经取到了可能的最大值，剩下的数无论取得多么小，和都会比 $S$ 大。因此，只需要构造 $K$ 个 $S$ 和 $N-K$ 个 $1$ 即可。（可以参考无穷大与任意有界函数的和都是无穷大）。

代码给定如下（使用了快读快输）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
inline int read() {
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	int x=0;
	while(ch>='0'&&ch<='9') x=(x*10)+(ch^48),ch=getchar();
	return x;
}
inline void write(int x) {
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline void wr(int x) {
	write(x);
	putchar(' ');
}
int n,k,s;
int main(void) {
    n=read(),k=read(),s=read();
    for(int i=0;i<k;++i) wr(s);
    for(int i=k;i<n;++i) wr(s==inf?1:s+1);
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15208263.html)

$\texttt{\color{red}upd~on~2021/9/1:}$修改了病句。

$\texttt{\color{red}upd~on~2021/9/2:}$统一了格式。

$\texttt{\color{red}upd~on~2021/9/7:}$修改了部分 $\LaTeX$。

## 前言

一道比较简单的题。（

~~完了完了完了要开学了要开学了。。。~~

## 题目大意

给定三个整数 $N,K,S$。

请你找到一个 $N$ 个元素的整数序列，其中每一个元素在区间 $[1,10^9]$ 内。这个序列满足 K 个子序列的和为 S。

## 分析

要求有 K 个子序列的和是 S，那么我们直接输出 K 个 S，剩下的我们就让它始终不能出现和为 S 就行了，那么可以再输出 $N - K$ 个 $10^9$，这可以在大部分情况下保证正确性。

上面仅仅是大部分情况下。

说一下特殊情况，比如说 `4 2 1000000000` 这样的例子，当 $S=10^9$ 时，我们则输出 $N - K$ 个 $10^9-1$ 即可。

## 代码

```cpp
//2021/8/30

#include <iostream>

#include <cstdio>

#define debug(c) cerr<<#c<<" = "<<c<<endl

namespace Newstd
{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				f=-1;ch=getchar();
			}
		}
		while(ch>='0' && ch<='9')
		{
			x=x*10+ch-48;ch=getchar();
		}
		return x*f;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

int main(void)
{
	int n,k,s;
	
	scanf("%d%d%d",&n,&k,&s);
	
	for(register int i=1;i<=k;i++)
	{
		printf("%d ",s);
	}
	
	for(register int i=k+1;i<=n;i++)
	{
		if(s==1e9)
		{
			printf("99999999 ");
		}
		
		else
		{
			printf("1000000000 ");
		}
	}
	
	return 0;
}
```

---

## 作者：零殇 (赞：0)

#### 题意

给定 $n$，$k$，$s$，构造一个长度为 $n$，**严格** $k$ 个子序列并且序列和为 $s$，的序列。

#### 思路

因为一个序列最简单的子序列就是它的一个元素，因此我们可以构造一个长度为 $k$ 且只包含 $s$ 的序列。

那么剩下的怎么办？

我们可以剩下的任何一个元素都大于 $s$，即 $s+1$。

但因为每个元素都不能大于 $10^9$，因为 $n$ 的范围在 $1$ 到 $10^5$ 之间，所以这个时候我们把剩下的全部变成 $1$ 就可以了。

上代码：
```
#include<bits/stdc++.h>
const int inf=1e9;
using namespace std;
int n,k,s;
int main() {
	scanf("%d%d%d",&n,&k,&s);
	for(int i=1;i<=k;i++)
		printf("%d ",s);
	for(int i=k+1;i<=n;i++)
		printf("%d ",s==inf?1:s+1);
	printf("\n");
	return 0;
}
```
完结撒花~


---

## 作者：yaolibo (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT5749)

## 题意解释：
要求构造一个长度为 $N$ 的序列 $a$，

满足 $1\le a_i\le10^9(1\le i\le N)$

且存在 $k$ 个不同子序列使每个子序列元素和均等于 $S$。

## 思路：
因为是一道构造题，我们一定需要找到一种简单而又普遍的构造方法。

容易发现，序列中的每个元素都是一个子序列。

那么就把题目简化为：

**构造一个序列，满足有 $k$ 个数值为 $S$，剩下的数的和不等于 $S$。**

所以考虑将前 $k$ 个数赋为 $S$，后 $(n-k)$ 个数赋为极大值，即所需构造序列值域的最大值 $10^9$，这样就能使后 $(n-k)$ 个数的和一定不等于 $S$。

但还是需要特判特殊情况，即 $S=10^9$ 的情况。

此时则将后 $(n-k)$ 个数赋为极小值 $1$，因为序列元素个数最多为 $10^5$ 个，所以后 $(n-k)$ 个数的和一定不会超过 $10^5$，满足条件。

总结如下：

$$
\boxed{\begin{aligned}a_i&=\begin{cases}S&(i \in [1,k])\\\begin{aligned}\begin{cases}10^9&(S<10^9)\\1&(S=10^9)\end{cases}\end{aligned}&(i \in [k+1,n])\end{cases}\end{aligned}
}$$

这个时候就可以很容易的将代码打出来了。

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int Inf = 1e9;
int n, k, s, i;
int main() {
    scanf("%d%d%d", &n, &k, &s);
    for (i = 1; i <= k; i++) printf("%d ", s);
    if (s < Inf) for (i = k + 1; i <= n; i++) printf("%d ", Inf);
    else for (i = k + 1; i <= n; i++) printf("1 ");
    return 0;
}
```

## 结束~Over~

---

## 作者：king_xbz (赞：0)

这道题大概的意思是要求找到一个$n$个元素的序列,满足该序列有$K$个子序列的和为$S$.

很显然啊,子序列的最短长度为$1$,且一个序列最多能分为$n$个长度为$1$的子序列.

我们还可以知道,这道题目的数据范围最大也就是$1e9$,那么我们直接构造输出$K$个$S$和$N-K$个$10^9$即可.

得到这样的代码:

```cpp
int main()
{
	int n,k,s;
	cin>>n>>k>>s;
	for(fint i=1;i<=k;i++)
	cout<<s<<" ";
	for(fint i=k+1;i<=n;i++)
	cout<<"1000000000"<<" ";
	return 0;
}
```

然后就在第三个点错了,为什么呢?因为加入$s=10^9$,那么后面在填充$1e9$的话就方案超标,所以我们需要填永远不会超标的数,比如$1$

完整AC代码:

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 3475894
using namespace std;
int main()
{
	int n,k,s;
	cin>>n>>k>>s;
	for(fint i=1;i<=k;i++)
	cout<<s<<" ";
	for(fint i=k+1;i<=n;i++)
	if(s==1e9)
	cout<<"1"<<" ";
	else
	cout<<"1000000000"<<" ";
	return 0;
}
```

---

## 作者：happybob (赞：0)

因为这里说的满足k个子序列和为s，只需要输出k个s，然后用其他数填充接下来的

至于用什么数呢？随便……

乱敲一个长一点的数就行了

代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k, s;
    cin >> n >> k >> s;
    for(register int i = 1; i <= k; i++) cout << s << " ";
    for(register int i = 1; i <= n - k; i++)
    {
        cout << "19283 ";
    }
    cout << endl;
    return 0;
}
```

这份代码已经AC了，但是如果想真正过掉那种专门hack这种的数据点，那么直接用$\large 10 ^ 9$填充。

---

## 作者：pengyule (赞：0)

国外网站上常常出现这种题目，网站上的官方题解往往是“我们发现某某构造方式（特殊）一定保证有解”，因此我们的工作就是去想怎样的特殊构造方式可以容易地满足要求。

对于这道题，显然这个序列中有 $k$ 个数是 $s$，剩下的数用不可能再得到 $s$ 的数来补充就好。我们想到，填 $s+1$ 一定是可以的；但注意需要特判一下，当 $s=10^9$ 时，$10^9+1$ 是越过条件限制的，这时就应该填一切小于 $10^9$ 的正整数，而为了方便代码实现，我们一律填 $(s+1)\bmod 10^9+1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,k,s;
    cin>>n>>k>>s;
    for(int i=1;i<=k;i++) cout<<s<<' ';
    for(int i=k+1;i<=n;i++) cout<<((s+1)%1000000000+1)<<' ';
    return 0;
}
```

---

