# [ABC231E] Minimal payments

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_e

Atcoder 王国では $ A_1 $ 円, $ A_2 $ 円, $ \ldots $, $ A_N $ 円の $ N $ 種類の硬貨が使用されています。  
 ここで、$ 1=A_1\ <\ \ldots\ <\ A_N $ であり、全ての $ 1\leq\ i\ \leq\ N-1 $ に対し、$ A_{i+1} $ は $ A_i $ の倍数です。

硬貨のみを使って $ X $ 円を支払うとき、支払いに使う硬貨の枚数とお釣りでもらう硬貨の枚数の合計の最小値はいくつですか？

正確には、$ Y $ が $ X $ 以上の整数を自由に動く時、$ Y $ 円ちょうどを表すために必要な硬貨の枚数と、$ Y-X $ 円ちょうどを表すために必要な硬貨の枚数の和の最小値を求めてください。

## 说明/提示

### 制約

- 入力に含まれる値は全て整数である
- $ 1\ \leq\ N\ \leq\ 60 $
- $ 1=A_1\ <\ \ldots\ <\ A_N\ \leq\ 10^{18} $
- 全ての $ 1\leq\ i\ \leq\ N-1 $ で $ A_{i+1} $ は $ A_i $ の倍数である
- $ 1\leq\ X\ \leq\ 10^{18} $

### Sample Explanation 1

$ 100 $ 円硬貨 $ 1 $ 枚で支払いを行い、$ 10 $ 円硬貨 $ 1 $ 枚と $ 1 $ 円硬貨 $ 3 $ 枚をお釣りでもらうと、合計枚数は $ 5 $ 枚になります。

### Sample Explanation 2

$ 7 $ 円硬貨 $ 7 $ 枚で支払いを行うのが最適です。

## 样例 #1

### 输入

```
3 87
1 10 100```

### 输出

```
5```

## 样例 #2

### 输入

```
2 49
1 7```

### 输出

```
7```

## 样例 #3

### 输入

```
10 123456789012345678
1 100 10000 1000000 100000000 10000000000 1000000000000 100000000000000 10000000000000000 1000000000000000000```

### 输出

```
233```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_e)

### 思路

可以用**贪心**思想解决这道题。

首先发现 $A$ 单调递增且 $A_i$ 是 $A_{i-1}$ 倍数，所以我们倒序遍历 $A$，对于 $A_i$，使其最接近所剩的 $X$ 一定是最优的选择。

但是，对于找零和不找零两种情况，最优解暂时不能确定。需要分情况讨论当前步骤所需次数和剩下的钱：

- 如果不需要找零，那么当前所需使用的次数为 $\lfloor\frac{X}{A_i}\rfloor$，剩下的钱为 $X\bmod A_i$。
- 如果需要找零，次数即为不找零的次数 $+1$。需要用所付的钱减去剩下的钱，即为 $A_i(\lfloor\frac{X}{A_i}\rfloor+1)-X$。

不难发现，上述内容可以用搜索实现。

**注意事项**

- 不开 `long long` 见祖宗。
- 直接 dfs 会导致 TLE，记得记忆化。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=70;
int n,a[N];
map<int,map<int,int>>f;
int dfs(int x,int i){
	if(i==n)
		return x;
	if(f[x][i])//记忆化
		return f[x][i];
	int op1=x/a[i]+dfs(x%a[i],i+1);//不找零
	int op2=x/a[i]+1+dfs(a[i]*(x/a[i]+1)-x,i+1);//找零
	f[x][i]=min(op1,op2);//取最优解
	return f[x][i];
}
signed main(){
	n=read();
	int x=read();
	for(int i=n;i>=1;--i)//反转数组, 方便操作
		a[i]=read();
	printf("%lld\n",dfs(x,1));
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：6)

## Description

现有 $n$ 种硬币。

每个硬币的面额为 $A_1,A_2,...,A_n$。

现在，你想买价值为 $x$ 元钱的物品。

求你用出的硬币个数和商家找回的硬币个数的总和的最小值是多少。

## Solution

注意数据特征：给定的钱币面额单调递增，并且每张面额的这一项是上一项的倍数，一定有解，且可以贪心。

此处假设价格单位为元。

此时就分为了两种情况：你刚刚好付出了和 $x$ 元的货物的所需价钱，或者你付出了离 $x$ 元的货物最近的价钱的硬币，然后找零。

考虑分类讨论。

首先是**不找零**的情况：

价值为 $x$ 的物品，可以先拿把面额最大的硬币付款，这样可以尽量减少所需的硬币，那么 $x$ 就会剩下 $x \bmod A_i$，剩下的钱可以再继续分配到价值第二大的货币，直到用到了最小面额的硬币，因为 $A_1$ 一定是 $1$，可以直接加到结果中。

到这时侯你会发现，这是一个搜索的过程，整个不找零的表达式应该为：$\dfrac{x}{A_i} +$dfs$(x \bmod A_i)$，终止条件为如果遍历完直接返回剩下的金额。

然后是**找零**的情况：

价值为 $x$ 的物品，我们知道用 $\dfrac{x}{A_i}$ 可以得出在当前金额下的硬币最多可以付多少个让个数不超过 $x$ 元，那么我们可以推断出，如果你再多支付一枚同样金额的硬币，价格将会刚好超过(或等于)所付金额。

第二步，再多一枚硬币的基础上算出你多付的钱，减去 $x$，可以得出你多付的钱，此处仍然可以对多付的价格再次进行如上操作，直到余下的钱分配到所有的金额中，直接返回剩余金额为止。

表达式为 $\dfrac{x}{A_i}+$dfs$((\dfrac{x}{A_i} + 1) \times A_i - x) + 1$。

最后，取找零和不找零的最小值，返回并输出答案即可。

但是时间复杂度过高，考虑用 map 储存每一种情况，及每个金额对应的组合的方案。

## Code

```cpp
// 2023/4/14 Accept__

#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

const int Accept__ = 66;
const int kMaxN = Accept__;

ll n, x, a[kMaxN];
map<ll, map<ll, ll> > f;

ll dfs(ll x, ll i) {
    if (!i) 
        return x;
    if (f[x][i]) 
        return f[x][i];
    ll otp = x / a[i] + dfs(x % a[i], i - 1); // otp = one-time payment, 一次性付清 
    ll change = x / a[i] + dfs((x / a[i] + 1) * a[i] - x, i - 1) + 1; // 找零
    f[x][i] = min(otp, change); // 找零和一次性之间取最小 
    return f[x][i];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> x;
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    cout << dfs(x, n - 1);

    return 0;
}
```


---

## 作者：chengning0909 (赞：5)

# abc 231 e

## 题意

有 $n$ 种硬币，面值分别为 $A_1, A_2, \dots A_N$ 元，其中 $1 = A_1  < A_2 < A_3 \dots < A_N$，并且对于 $1 \le i \le N - 1$ 的所有 $i$ 都有 $A_{i + 1}$ 是 $A_i$ 的倍数。

现在要用这些硬币支付 $X$ 元，请你求出支付和找零的硬币数量的和的最小值。

- $1 \le N \le 60$。

- $1 = A_1 < \dots < A_N \le 10 ^ {18}$。

- $1 \le X \le 10 ^ {18}$。

## 思路

首先，这个题目有一个很明显会超时还有可能会爆空间的做法，**完全背包**。

$dp_i$ 表示凑出 $i$ 元的最少硬币数量。

转移为：

$$dp_i = \min _ {j = 1} ^ n \{dp_{i - a_j} + 1\}$$

因为支付的钱数最多为 $2 \times X$ 元（如果支付 $2 \times X$ 元，就需要找零 $X$ 元，也是凑出 $X$ 元，还需要额外加上凑出 $2 \times X$ 元的硬币数量，很明显会比直接凑出 $X$ 元更差），所以空间复杂度为 $O(2 \times X)$。

但是 $X$ 有 $10 ^ {18}$ 那么大，根本不能用数组存下来，所以我们可以用 **map** 来实现。

但是，就算空间的问题解决了，时间也救不回来。

`dp` 的时间复杂度为 $O(2 \times X)$，也就是 $O(X)$。

计算答案的时间复杂度为 $O(X)$。

总时间复杂度为 $O(X)$，完全无法接受。

所以，我们要考虑其他方法。

其实可以发现，题目中几乎所有条件我们都用上了，但还有一句话：**对于 $1 \le i \le N - 1$ 的所有 $i$ 都有 $A_{i + 1}$ 是 $A_i$ 的倍数。** 这句话我们一直都没有用上，那么，这又代表了什么呢？

题目里还有一个条件： $1 = A_1 < A_2 < A_3 \dots < A_N$
。

这代表着任何一个数都可以被表示出来，而又有 $A_{i + 1}$ 是 $A_i$ 的倍数这个条件，所以可以发现，我们可以将 $X$ 变成一个不知道是什么进制的数，而它对应的硬币数量就是他各位数字之和。

所以我们可以列这样一个表格：

令 $B_i = A_{i + 1} \div A_i (1 \le i \le N - 1)$ 

|   位号   |                   N                   |   $\dots$   |                    2                     |                1                |           0            |
| :------: | :-----------------------------------: | :---------: | :--------------------------------------: | :-----------------------------: | :--------------------: |
| **位权** |               **$A_N$**               | **$\dots$** |                **$A_3$**                 |            **$A_2$**            |       **$A_1$**        |
| **数值** | **$C_N = x \div B_1 \dots \div B_N$** | **$\dots$** | **$C_3 = x \div B_1 \div B_2 \mod B_3$** | **$C_2 = X \div B_1 \mod B_2$** | **$C_1 = X \mod B_1$** |

所以，对于第 $i$ 位来说，这意味可以选择用 $C_i$ 个 $A_i$，也可以用 $1$ 个 $A_{i + 1}$ 和 $B_i - C_i$ 个 $A_i$。

$dp_{i, 0 / 1}$ 表示用前 $i$ 种硬币凑出（不出）前 $i$ 位所用的硬币的最小数量（描述的很奇怪）

所以有转移：

$$dp_{i, 0} = \min \{dp_{i - 1, 0}, dp_{i - 1, 1}\} + C_i$$

来解释一下吧，就是如果第 $i$ 位要用 $C_i$ 个 $A_i$ 来凑的话，那么就直接取上一位的最小硬币数量，再加上 $C_i$ 即可。

那么，这里就有一个问题了，如果第 $i - 1$ 位是用 $1$ 个 $A_i$ 和 $B_{i - 1} - C_{i - 1}$ 个 $A_{i - 1}$ 凑出来的话，$dp_{i - 1, 1}$ 不应该在加 $1$ 吗？

这么想也没问题，主要是写法的不同，我是把这个 $1$ 放在 $dp_{i - 1, 1}$ 中加的。

$$dp_{i, 1} = \min \{dp_{i - 1, 0} + 1, dp_{i - 1, 1} - 1\} + B_i - C_i$$

我们先看 $dp_{i - 1, 0} + 1$，这里的 $dp_{i - 1, 0}$ 就是第 $i - 1$ 位不借位的最少硬币数量，再 $+ 1$ 则是因为当前这一位要再借一位。

再看 $dp_{i - 1, 1} - 1$，这个就有一点点不好懂了。

我们先将这个转移换一种方式写出来：

$$dp_{i, 1} = \min \{dp_{i - 1, 0} + 1 + B_i - C_i, dp_{i - 1, 1} - 1 + B_i - C_i\}$$

其实这个式子应该是 $dp_{i - 1, 1} - 1 + 1 + (B_i - C_i - 1)$，第一个 $- 1$ 是因为在前 $i - 1$ 位已经借过一次了，而这里又要借，所以要把之前借的那一位先去掉，$+ 1$ 是因为又要再借一位，$B_i - C_i - 1$ 是第 $i$ 种硬币需要找零的数量，因为第 $i - 1$ 位借了一个，所以第 $i$ 位所需要的硬币数量就变成 $C_i + 1$ 了，所以就是 $B_i - (C_i + 1)$，也就是 $B_i - C_i - 1$。

所以总时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

---

## 作者：rainygame (赞：3)

模拟赛考到了，考场上差点没有调出来。

首先考虑一个更弱的问题：假设有无限种货币分别为 $10^0,10^1,10^2,\dots$，然后需要买 $x$ 元的物品。

那么对于 $x$ 的从低到高第 $i$ 位（假设为 $k$），有两种选择：

1. 支付 $k$ 个 $10^i$ 元的硬币。
2. 支付 $1$ 个 $10^{i+1}$ 元的硬币，并找回 $10-k$ 个 $10^i$ 元的硬币。

考虑 DP，定义状态 $f_{i,0/1}$ 表示选完了第 $i$ 位，且第 $i$ 位的策略是不进位/进位。

那么有状态转移方程（设第 $i$ 位的数为 $k$）：

$$
\begin{aligned}
f_{i,0}&=\min\{f_{i-1,0}+k,f_{i-1,1}+k+1\}\\
f_{i,1}&=\min\{f_{i-1,0}+(10-k),f_{i,1}+(10-k)+1\}
\end{aligned}
$$

我们已经解决了这个更弱的问题，分析一下原题难在哪里：

1. 只有有限种货币。
2. 每一位进制不一样。

对于第二个问题，我们考虑分解的时候对于第 $i$ 位，进制为 $\dfrac{A_{i+1}}{A_i}$，然后把上式的 $10$ 改为 $\dfrac{A_{i+1}}{A_i}$ 即可。

对于第一个问题，我们考虑转进制的时候如果转到第 $n$ 位了就直接停止，剩下的 $X$ 就只能用 $A_n$ 的来支付。

时间复杂度 $O(n+\log X)$，题解区最优。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, x, k, cnt, flag, base;
int a[61], b[61];
int f[61][2];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> x;
    for (int i(1); i<=n; ++i) cin >> a[i];
    if (n == 1){
    	cout << x;
    	return 0;
	}
	
	while (x && cnt < n-1){
		++cnt;
		b[cnt] = x % (a[cnt+1]/a[cnt]);
		x /= (a[cnt+1]/a[cnt]);
	}
	
	f[1][0] = b[1];
	f[1][1] = a[2]-b[1];
	for (int i(2); i<n; ++i){
		f[i][0] = min(f[i-1][0]+b[i], f[i-1][1]+b[i]+1);
		f[i][1] = min(f[i-1][0]+a[i+1]/a[i]-b[i], f[i-1][1]+a[i+1]/a[i]-b[i]-1);
	}
	f[n][0] = min(f[n-1][0]+b[n], f[n-1][1]+b[n]+1);
	cout << f[n][0]+x;

    return 0;
}
```


---

## 作者：i_love_tym (赞：3)

# 题目大意

你有 $n$ 种硬币，第 $i$ 种硬币的面值为 $a_i$。

你需要购买一个价格为 $x$ 的商品。

请你求你用出的硬币个数与商家找回的硬币个数之和最小是多少。

# 大致思路

由于我们希望使用的硬币数越小越好，所以应该优先使用面值较大的硬币。

所以我们可以先将硬币的面值排个序。

接着，定义函数 $\operatorname{dfs}(x,i)$ 表示目前遍历到了第 $i$  个硬币，还需付 $x$ 元。

由于有两种情况：找零/不找零。

我们可以得出两种情况对应的柿子：

- 不找零 ： $\dfrac{x}{a_i}+\operatorname{dfs}(x \bmod a_i , i-1)$。

- 找零 ：  $\dfrac{x}{a_i}+\operatorname{dfs}(\dfrac{x}{a_i}+1 \times a_i -x,i-1)+1$。

但是我们重复算了一种情况很多次，所以我们可以为 $\operatorname{dfs}$ 函数加上记忆化。

即定义 $f_{i,j}$ 表示 $\operatorname{dfs}(i,j)$ 的值，这样就不会 TLE 了。

---

## 作者：_shine_ (赞：0)

首先明确一个事：因为 ：
>保证对于 $\forall\ 1\le i\le n-1$，$A_{i+1}$ 是 $A_i$ 的**倍数**。

所以说要使所有硬币花费数量最小，则应该要从大到小枚举。

用 $f_{i,j}$ 表示为当前已经枚举到第 $i$ 个面额，并且到现在还剩下 $j$ 元待付款（或商家找零），则在这里 $f_{i,j}$ 就有两种情况：
1. 当前面额不找零（有可能在之后再找零），则 $f_{i,j}=f_{i-1,j\bmod a_i}+\frac{j}{a_i}$。
1. 直接找零继续处理（要计算商家找零的部分），则 $f_{i,j}=f_{i-1,\left(\frac{j}{a_i}+1\right)\times a_i-j}+\frac{j}{a_i}+1$。

因为没法简单的通过循环来解，所以这里使用记忆化搜索，定义的搜索参数与 $f$ 数组相同。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e2+10;
int n,m,a[maxn];map<int,map<int,int> >f;
int dfs(int x,int y){
//	puts("hi");cout << x << " " << y << endl;
	if(y==0){f[x][y]=0;return 0;}//递归出口。
	if(f[x][y]!=0)return f[x][y];//防止多次运算，既然有值了，则肯定是遍历过的，则也应该是最优的
	if(x==1 && y!=0)f[x][y]=dfs(x-1,y%a[x])+y/a[x];//因为已经到最低的面额了，所以不可能用更低的面额去找零了，所以这里只能直接付款，同时因为面额是倍数的条件，也使得最低的面额必定是有解的，如果最低的都无解，则更高面额的钞票也会无解。
	else{
//		puts("now");
		f[x][y]=min(dfs(x-1,y%a[x])+y/a[x],dfs(x-1,(y/a[x]+1)*a[x]-y)+y/a[x]+1);//直接付和找零两种情况。
//		cout << x << " " << y << " " << f[x][y] << endl;
	}
	return f[x][y];
} 
signed main(){
	scanf("%lld%lld",&n,&m);for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	printf("%lld\n",dfs(n,m));
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_e)

一道贪心题。

感觉很裸啊，模拟赛时随便乱写了个暴力递归就能过。每次找最接近钱数 $x$ 的面额 $num$，如果比钱数少那么答案为剩下 $x \bmod num$ 钱数的答案加上 $x \div num$。否则答案则为剩下 $num-x$ 钱数的答案加上 $1$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll n, m;
ll a[65];
ll ans(ll x) {
	if (x == 0) return 0;
	ll minn = 1e18, num;
	for (int i = 1; i <= n; i++) {
		if (llabs(x - a[i]) < minn) {
			minn = llabs(x - a[i]);
			num = a[i];
		}
	}
	if (num > x) return ans(num - x) + 1;
	return ans(x % num) + x / num;
}
int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cout << ans(m);
	return 0;
}
```


---

## 作者：zdq20110120 (赞：0)

## [原题戳这里](https://www.luogu.com.cn/problem/AT_abc231_e)

不难看出，这是一道 __贪心__ 的水题。

### 解题思路
每次寻找最接近钱数 $x$ 的面额 $y$：
- 如果 $y \leq x$ 那么答案为 $x \bmod y$ 的答案 $+ x \div y$。
- 如果 $y \geq x$ 那么答案为 $num - x$ 的答案 $+ 1$。

### 代码主要板块
```cpp
ll f(ll x) {
	if (x == 0) return 0;
	ll mn = LONG_LONG_MAX, num;
	for (int i = 1; i <= n; i++) {
		if (abs(x - a[i]) < mn) {
			mn = abs(x - a[i]);
			num = a[i];
		}
	}
	if (num > x) return f(num - x) + 1;
	return f(x % num) + x / num;
}
```

---

