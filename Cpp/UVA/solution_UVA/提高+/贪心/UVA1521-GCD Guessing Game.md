# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6```

### 输出

```
2```

# 题解

## 作者：STDquantum (赞：11)

这是一篇解释“为什么想到要选质数”以及“为什么选质数是对的”（也就是其他大佬面临的问题）的题解。

如果出错欢迎提出。

**UPD on 2020.10.15：更改了证明中错误的部分。感谢[SuperTNT](https://www.luogu.com.cn/user/283889)、[陈浩然](https://www.luogu.com.cn/user/249339)纠错，感谢[minxu](https://www.luogu.com.cn/user/251572)帮助完善证明。**

正解不是我想出来的，感谢[shame_djj](https://www.luogu.com.cn/user/162867)和[naive_wcx](https://www.luogu.com.cn/user/23138)大佬。

做这道题的时候思路可以是这样的，先考虑非最优的策略，再去想怎么优化它。

所以一开始想的时候，就是先从最大值（也就是 $n$）向下枚举。如果出现了它给出的数字（以下简称 $g$，代表 $\gcd$）和猜想的数字（以下简称 $x$）完全相同，也就是说明原数字（也就是答案数字（不是要求的那个答案），以下简称 $ans$）是 $x$ 的倍数，但是 $ans$ 又不可能比 $x$ 大，因为是一路枚举下来的，所以当 $g=x$ 就结束了。

最坏是 $n-1$ 次，对应的 $ans$ 是 $1$。这样的话会多出许多冗余步骤，那些步骤对求出 $ans$ 没有一点帮助。比如在 $n=12,ans=1$ 的情况下枚举完了 $12$，又去枚举一遍 $6$，对求解规模的缩小没有一点帮助（除了减了一）。

我们先对排除做一个定义吧，就是：猜想一个 $x=p_1^{k_1}p_2^{k_2}\dots p_m^{k_m}$，对方给出的 $g$ 中不包含某些因子，如 $p_1$，这就说明 $ans$ 中是没有 $p_1$ 这个因子的，否则的话 $p_1$ 一定能整除 $g$。这样我们就可以排除所有含 $p_1$ 这个因子的 $ans$，原本是 $n$ 的求解规模减少了 $\displaystyle\left\lfloor\frac n{p_1}\right\rfloor$（肯定比枚举这些被排除的数要优吧）。

当然我们可以发现最难找的肯定就是 $ans=1$，因为要排除所有其他的数才能让 $1$ 当做答案，而暴力枚举排除所有数显然是不行的。

接下来证明找到 $1$ 的步数一定是最坏步数，将以求解规模来解释这一问题。对于猜想 $x$，回答为 $g$，如果 $g$ 为 $1$，说明 $ans$ 中没有 $x$ 的质因子，其求解规模减小了 $\displaystyle \sum_{p\mid x}\left\lfloor\frac n{p}\right\rfloor$；反之说明 $ans$ 中有 $x$ 的质因子，相当于本次询问的是 $\displaystyle \frac xg$，回答是 $1$，求解规模从 $n$ 下降到了 $\displaystyle \left\lfloor\frac n{g}\right\rfloor$，也就是所有 $g$ 的倍数成为了现在的寻找答案的集合。对于求解规模的影响，会有 $\displaystyle n-\left\lfloor\frac n{g}\right\rfloor\ge \left\lfloor\frac n{p}\right\rfloor$，因此若每次给出的 $g$ 均为 $1$，求解规模缩小最慢。所以可以得到找到 $1$ 的步数就是最坏的步数。

所以一定不存在一个数需要排除的步数比 $1$ 大，这个问题也就转化为了**最少花多少步可以筛掉所有大于** $1$ **的数**。

那么，我们就是要找一个最优的方案让我们非常快速地把数筛掉，那么显然对于 $x=p_1^{k_1}p_2^{k_2}\dots p_m^{k_m}$，所有的 $k$ 都等于 $1$ 就好，因为筛掉数字只和质因子有关，和到底有多少没关系（所以对于前文 $n=12$ 的例子，$x=12$ 和 $x=6$ 对最坏答案的求解规模减小量的贡献是一样的，因为它们两个都只有 $2,3$ 两个质因子，所以也就没有必要把这两个数都枚举一遍）。

而 $n$ 内所有大于 $1$ 的数，是可以被所有 $[2,n]$ 内的质数筛掉的，所以现在问题就变成了 **用最少的询问次数，确定** $n$ **中不包含任何素因子**。

接下来就是贪心的事了，用质数来筛是最优的（详情见筛质数的算法，在筛出质数的同时筛了所有其他数），所以我们要把 $[2,n]$ 内所有质数以乘为运算符全塞进小于等于 $n$ 的数中，找一个最大的搭配一堆最小的就行。双指针维护一下（或者随便什么方法能贪心就行）。

但其实在本题所给的范围中，这样做与下面做法是等价的：每个小于 $\sqrt n$ 的素数，都与它能配对的最大素数配对，也就是最多两个素数打一下包。

这个做法我并不会证明，但是是对的，代码将在文末给出。

另外：还要说明一点，打包时选质数的顺序（从大到小）并不是实际操作的顺序，实际操作时需要小的质因子优先询问，也就是为了解决形如 $p^k$ 这种数（$k$ 较大）的筛查。

这样每次是 $O(p)$ 的（$p$ 为 $[1,n]$ 中质数的数量），总共 $O(Tp)$，可以通过本题（虽然没给 $T$ 但肯定是 $O($能过$)$）。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace STDquantum {

const int N = 1e4 + 10;
int num, prime[N];
bool isPrime[N];
inline void Get(int n) { // 线性筛质数
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) prime[++num] = i;
        for (int j = 1; j <= num && i * prime[j] <= n; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0) break;
        }
    }
}

int n, ans;
inline void main() {
    Get(N - 10);
    while (~scanf("%d", &n) && n) {
        ans = 0;
        int l = 1, r = num;
    	while (prime[r] > n) --r; // 让prime[r]降到[2,n]的范围
        for (int k; l <= r; --r, ++ans) {
            k = prime[r];
            while (k * prime[l] <= n) k *= prime[l++];
        }
        printf("%d\n", ans);
    }
}

}   // namespace STDquantum

int main() {
    STDquantum::main();
    return 0;
}
```

悄咪咪说一句，POJ上没有题面的4028和这题一毛一样……

---

本题中循环可以简化为如下形式：

```cpp
for (; l <= r; --r, ++ans) {
    if (prime[r] * prime[l] <= n) ++l;
}
```



---

## 作者：shame_djj (赞：6)

原题链接【[UVA 1521 GCD Guessing Game](https://www.luogu.org/problem/UVA1521)】

思路来自[JeraKrs大佬的博客](https://blog.csdn.net/keshuai19940722/article/details/38352765)。

贪心思路：筛出质数，用质数的积来枚举

为什么要用质数来枚举？

（~~嗯，好问题，但我也不知道~~~）

其实还是知道一点的。

枚举一个数，如果这个数是 n 的因子，那么再枚举时，就能从 n / 这个因子 的范围内来继续枚举。

对吧，这是非常简单而又非常正常的一个思路。

但为什么要枚举质因子呢？

比方说，有个因子是 m ，而这个 m 有两个质因子 a 和 b ，

请问是你枚举到 a * b 次数少，还是 a + b 少？

因此，枚举质因子，比枚举因子好

筛一下素数，枚举第几个因子显然就更优了

总之，大体思路如下：

		我们把 n 以内的质数都考虑一下，

		如果全都需要考虑，即 n 中不包含所有质因子，那这就是最坏情况了。

		但如果有当前的这个质因子，枚举的范围就变成了 n / 当前这个质因子，再这样枚举下去，自然猜的次数就要减小很多了。

因为有一个 n 的限制，每次枚举时，不超过 n 就好了。

于是这道稍微有点难（但不至于成为这个颜色）的题就被解决了

代码（~~和JeraKrs大佬的代码已经很像了QwQ~~）
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <deque>

using namespace std;
const int maxn = 1e4 + 10;

bool is[maxn] = {1, 1}, v[maxn];
int prime[maxn], tot, n;

void solve (int u, int x) {
    for (register int i = x; i >= 1; i --) {
        int k = prime[i];
        if (v[k] || k > u)
            continue;
        v[k] = 1;
        solve (u / k, i - 1);
        return ;
    }
}

void djj () {
    for (register int i = 2; i <= maxn - 10; i ++) {
        if (!is[i]) prime[++ tot] = i;
        for (register int j = 1; j <= tot && i * prime[j] <= maxn; j ++) {
            is[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break ;
        }
    }
}

void lxy () {
    for (; scanf ("%d", &n) == 1; ) {
        int ans = 0;
        memset (v, 0, sizeof v);
        for (register int i = tot; i >= 1; i --) {
            int u = prime[i];
            if (v[u] || u > n)
                continue ;
            ans ++;
            v[u] = 1;
            solve (n / u, i);
        }
        printf ("%d\n", ans);
    }
}

void djj_lxy () {
    djj (), lxy ();
}

int main() {
    djj_lxy ();
}

/*
6

2
*/

```

（~~鬼畜的码风，但这好像能证明我没有直接抄人家的~~）

几个小点：

		1、用 for 循环代替 whlie 循环，能快上不少

		2、看到楼上题解用了 deque ，觉得非常难受，大家最好能手写就手写，STL（不开 O2 ）可慢了

新 Noip 越来越近了，祝大家 rp ++

也希望自己能更努力一些，加油！！

---

## 作者：SuperTNT (赞：3)

# [题解]UVA1521 GCD Gussing Game

## 问题

1. 最优策略是什么 ？

2. 为什么这样是最好的 ？ 

## 思考

* 对于问题 $1$ ， 我们发现每次询问一个数字 $x$ ， 如果返回的 $gcd(x,p) = t (t > 1)$ ， 那么问题规模就下降到了 $\lfloor{\frac {n}{t}} \rfloor$  ，相当于继续寻找 $t$ 在 $n$ 里的倍数， 这显然是比 $gcd(x,p) = 1$ 时更优
* 因此在 $n$ 比较大时，通过一次询问降低问题规模要比回答 $1$ 更优 ， 在 $n$ 比较小的时候我们可以通过自己推式子或打个程序得出结论发现不会比 $1$ 情况更坏
* 此时我们便将问题转化为如何使在猜测的数是 $1$  的情况下更优，即最少次数遍历 $n$ 以内所有质数
* 考虑两个质数 $a,b $  ， 若不存在 $a$ 使得 $ab \le n$ 则只能单独筛掉 $b$ ，反之可以一次筛掉两个 ，这道题便解决了
* 预处理复杂度为$O(n)$  ， 单次询问时间复杂度为 $O(m)$ （其中 $m$ 为 $[1,n]$ 中 质数个数）

## 代码

```c++
#include<bits/stdc++.h>

#define re register

namespace TNT
{
    const int MAXN = 1e4;

    int prime[MAXN],tot;
    bool mindiv[MAXN + 10];
    inline void TNT()
    {
        for(re int i = 2 ;i <= MAXN;++i)
        {
            if(!mindiv[i])
                prime[++tot] = i;
            
            for(re int j = 1; j <= tot && prime[j] * i <= MAXN;++j)
            {
                mindiv[i * prime[j]] = 1;

                if(!(i % prime[j]))
                    break;
            }
        }
    }

    inline void main()
    {
        TNT();

        int n;

        while(~scanf("%d", &n) && n)
        {
            int ans = 0;
						
            int l = 1,r = std::upper_bound(prime + 1,prime + 1 + tot,n) - prime - 1;            
            
            
            while(l <= r)
            {
                if(prime[l] * prime[r] <= n)
                    ++ans,++l,--r;
                else
                    ++ans,--r;               
            }

            printf("%d\n",ans);
        }
        return;
    }
}

int main()
{
    TNT::main();
    return 0;
}
```



## 参考

参考来源：[STDquantum 的博客](https://www.luogu.com.cn/blog/STDquantum/solution-uva1521)

​					[杜宇飞大牛：NEERC 11-13 题目选讲](https://www.doc88.com/p-7364584446751.html)



---

## 作者：naive_wcx (赞：3)

# Description
给定正整数$n(n≤10000)$，小$A$在心中想一个$≤n$的正整数，小$B$每次猜一个正整数（他知道上界是$n$），小$A$告诉他他猜的数和心中想的数的最大公约数，问小$B$要猜多少次才能猜出这个数。
# Solution
先讲结论：筛出$n$以内的素数表，对于最后面的质数，贪心地找前面的质数使得乘积不超过$n$，然后删去这些数字知道所有数字少于两个。

Why？

~~（我也不知道）~~

但是我可以感性的说明一下：考虑答案的下界，显然，对于每一次猜测的结果，如果不是$1$，那么一定会使次数减少，所以最差的情况就是对于所有的猜测小$A$的反馈都是1。继续考虑，如果猜测的数字不是质数，那么显然会出现冗余的猜测，徒增次数，那么每一次猜一些质数的乘积一定是最好的选择。于是这个策略就出来了。

时间复杂度$O(n)$，跑$1e7$问题也不大。

# Code
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 10000000;
bool check[maxn + 10];
deque <int> prime;
int n;
int main()
{
	freopen("gcd.in", "r", stdin);
	freopen("gcd.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		if(!check[i]) prime.push_back(i);
		for(int j = 0; j < prime.size() && i * prime[j] <= maxn; j++) {
			check[prime[j] * i] = 1;
			if(i % prime[j] == 0) break;
		}
	}
	int ans = 0;
	while(!prime.empty()) {
		while(prime.size() >= 2 && prime.front() * prime.back() <= n) {
			prime.back() *= prime.front();
			prime.pop_front();
		}
		prime.pop_back();
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Silence_World (赞：0)

# 思路

题意简单易懂，但关键的一点是多组数据别忘了，我最后加了个多组数据  $n$ 定义在里面，UKE 了一直没发现 QAQ。

整体思路大概就是把 $n$ 以内的所有素数筛出来（很简单吧），然后每次用素数数组中第一个与最后一个相乘且这个值要小于 $n$（稍后会给出个人证明），存到最后，不难想到双端队列，每次删除最后一个，结果加一，直到没有。

# 证明

此处均为个人见解，可能有很多不准确的地方，勿喷，可以私信告诉我修改。

首先对于任意一个 $p$，既然题中要求每次告诉你一个最大公约数让你猜数，不难想到最坏情况就是好几个同数或者好几个数使其与 $q$ 的最大公约数相同，但题中要求在最坏情况中求出至少情况，也就是将此题转化成了一个从最坏解中求最优解的情况，也就意味着在最坏的情况下，求最优解，那我们既然知道了最坏情况，我们思考什么情况最优，但我们考虑如果有几个数是倍数，是否会浪费了一次机会，我们就假设有一个数 $a$，使得 $ax=b$ 且 $x>0$，那这就此时我们先猜 $b$，结果为 $\gcd(b,q)$，我们再考虑带 $a$，显然的把 $x$ 乘掉并不影响结果，也就变成了 $\gcd(b,q)$，好啦，啪一下，步数加一，舍掉，那现在就只剩素数了，我们思考为什么要素数相乘（虽然我也不会证），每次猜一个数都会使范围缩小，大概意思就是确定一个具体的边界，使其有更优的策略去猜数，综上所述，结论应该是成立的（要不然怎么过的）。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool a[100000001];
deque<int>b;
int n;
signed  main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	while(cin>>n and n) {
		for(int i=2; i<=n; i++) {
			if(!a[i]) {
				b.push_back(i);
			}
			for(int j=0; j<b.size() and i*b[j]<=10000005; j++) {
				a[i*b[j]]=1;
				if(i%b[j]==0) {
					break;
				}
			}
		}
		int cnt=0;
		while(!b.empty()) {
			while(b.size()>=2 and b.front()*b.back()<=n) {
				b.back()*=b.front();
				b.pop_front();
			}
			b.pop_back();
			cnt++;
		}
		cout<<cnt<<endl;
	}

	return 0;
}
```


---

