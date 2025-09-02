# Up the Strip (simplified version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

Note that the memory limit in this problem is lower than in others.

You have a vertical strip with $ n $ cells, numbered consecutively from $ 1 $ to $ n $ from top to bottom.

You also have a token that is initially placed in cell $ n $ . You will move the token up until it arrives at cell $ 1 $ .

Let the token be in cell $ x > 1 $ at some moment. One shift of the token can have either of the following kinds:

- Subtraction: you choose an integer $ y $ between $ 1 $ and $ x-1 $ , inclusive, and move the token from cell $ x $ to cell $ x - y $ .
- Floored division: you choose an integer $ z $ between $ 2 $ and $ x $ , inclusive, and move the token from cell $ x $ to cell $ \lfloor \frac{x}{z} \rfloor $ ( $ x $ divided by $ z $ rounded down).

Find the number of ways to move the token from cell $ n $ to cell $ 1 $ using one or more shifts, and print it modulo $ m $ . Note that if there are several ways to move the token from one cell to another in one shift, all these ways are considered distinct (check example explanation for a better understanding).

## 说明/提示

In the first test, there are three ways to move the token from cell $ 3 $ to cell $ 1 $ in one shift: using subtraction of $ y = 2 $ , or using division by $ z = 2 $ or $ z = 3 $ .

There are also two ways to move the token from cell $ 3 $ to cell $ 1 $ via cell $ 2 $ : first subtract $ y = 1 $ , and then either subtract $ y = 1 $ again or divide by $ z = 2 $ .

Therefore, there are five ways in total.

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
5```

## 样例 #2

### 输入

```
5 998244353```

### 输出

```
25```

## 样例 #3

### 输入

```
42 998244353```

### 输出

```
793019428```

# 题解

## 作者：henrytb (赞：9)

这道题分了简单版和正常版。我先想出了简单版，然后才做出了正常版。

### 简单版

题目中的数据范围是 $2\le n\le 2\cdot 10^5$，那么 $O(n\sqrt{n})$ 做法可过。

我们设 $f_i$ 表示从 $n$ 走到 $i$ 的方案数。

那么如果我们已经转移完了 $f_i$，$f_i$ 便可以转移到 $\left\lfloor\frac{i}{2}\right\rfloor,\left\lfloor\frac{i}{3}\right\rfloor,\cdots,\left\lfloor\frac{i}{i}\right\rfloor$。

这个式子很熟悉，我们可以 **整除分块**！

另外还要考虑通过减法到达 $i$ 的情况，在转移 $f_i$ 的时候我们加上后缀和即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,p;
int f[200005];
signed main() {
    scanf("%lld%lld",&n,&p);
    f[n]=1;
    rep(i,1,n-1) f[i]=0;
    int sum=1;
    int l=2,r;
    for(;l<=n;l=r+1) {
        r=n/(n/l);
        f[n/l]=(f[n/l]+(r-l+1)*f[n])%p;
    }
    per(i,n-1,1) {
        f[i]=(f[i]+sum)%p;
        l=2;
        for(;l<=i;l=r+1) {
            r=i/(i/l);
            f[i/l]=(f[i/l]+(r-l+1)*f[i])%p;
        }
        sum=(sum+f[i])%p;
    }
    printf("%lld\n",f[1]);
    return 0;
}
```

### 正常版

数据范围 $2\le n\le 4\cdot 10^6$，貌似不能 $O(n\sqrt{n})$ 了。

但是我们可以换个角度，不考虑 $f_i$ 可以转移到谁了，转而考虑谁能转移到 $f_i$。

通过减法转移到 $f_i$ 的显然是 $f_{i+1\sim n}$。

通过除以 $2$ 转移到 $f_i$ 的是 $f_{2i\sim 2i+1}$。

通过除以 $3$ 转移到 $f_i$ 的是 $f_{3i\sim 3i+2}$。

以此类推，通过除以 $z$ 转移到 $f_i$ 的是 $f_{zi\sim zi+z-1}$。

那么我们可以做一个 $f$ 的后缀和，然后对于每个 $f_i$ 枚举 $z$，使用后缀和转移。

时间复杂度 $O(n\log n)$，$\log$ 的来历是调和级数。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,p;
int f[4000005],sum[4000005];
signed main() {
    scanf("%lld%lld",&n,&p);
    f[n]=1;
    sum[n]=1;
    rep(i,1,n-1) f[i]=0;
    per(i,n-1,1) {
        f[i]=(f[i]+sum[i+1])%p;
        for(int j=2;i*j<=n;++j) {
            // i*j ~ i*j+(j-1)
            f[i]=(f[i]+sum[i*j]-sum[min(i*j+j,n+1)])%p;
            f[i]=(f[i]+p)%p;
        }
        sum[i]=(sum[i+1]+f[i])%p;
    }
    printf("%lld\n",f[1]);
    return 0;
}
```

---

## 作者：一只书虫仔 (赞：2)

#### Description

> 给定一个数 $n$，每次可以对他进行一个操作，有两种操作：
>
> - $n \leftarrow n-t$，$t \in [1,n)$；
> - $n \leftarrow \lfloor\frac n t\rfloor$，$t \in (1,n]$。
>
> 求有多少种方案使得 $n$ 变为 $1$。

#### Solution

考虑暴力 dp，设 $f_i$ 为有多少种方案使得 $i$ 变为 $1$，考虑转移方程：

- 考虑减法：

$$f_i=f_i+\sum\limits_{j=1}^{i-1}f_j$$

- 考虑除法：

$$f_i=f_i+\sum\limits_{j=2}^{i}f_{\left\lfloor\frac i j\right\rfloor}$$

暴力计算时间复杂度 $\mathcal O(n^2)$，肯定不行，考虑优化。

- 对于减法，就是一个前缀和，加上优化即可；
- 对于除法，$\left\lfloor\dfrac i j\right\rfloor$ 只有 $\sqrt i$ 个，因此考虑整除分块优化。

因此复杂度为 $\mathcal O(n \sqrt n)$。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, m;
long long f[200015];
long long sf[200015];

int main () {
	scanf("%lld%lld", &n, &m);
	f[1] = 1;
	sf[1] = 1;
	for (long long i = 2; i <= n; i++) {
		f[i] += sf[i - 1];
		f[i] %= m;
		long long r;
		for (long long l = 2; l <= i; l = r + 1) {
			r = (i / (i / l));
			long long cnt = r - l + 1;
			long long tmp = f[i / l];
			tmp *= cnt;
			tmp %= m;
			f[i] += tmp;
			f[i] %= m;
		}
		sf[i] = sf[i - 1] + f[i];
		sf[i] %= m; 
	}
	printf("%lld", f[n] % m);
	return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[数论分块](https://oi-wiki.org//math/number-theory/mobius/#_3)

显然可以 dp。

设 $dp_{i, j}$ 表示从 $i$ 开始，这次采用第 $j$ 种运算（$j = 1$ 表示减法，$j = 2$ 表示除法），显然可以得到转移方程：

1. $dp_{i, 1} = \displaystyle\sum_{j = 1}^{i - 1} (dp_{j, 1} + dp_{j, 2})$

2. $dp_{i, 2} = \displaystyle\sum_{j = 2}^i (dp_{\lfloor \frac{i}{j} \rfloor, 1} + dp_{\lfloor \frac{i}{j} \rfloor, 2})$

答案：$dp_{n, 1} + dp_{n, 2}$。

用数论分块优化 $dp_{i, 2}$ 的计算即可。时间复杂度为 $O(n \sqrt{n})$。

注意涉及 $dp_{1, i}$ 的情况的处理。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

ll dp[200007][7], sum[200007][7];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (register int i = 2; i <= n; i++){
		int half_i = i / 2;
		dp[i][1] = (sum[i - 1][1] + sum[i - 1][2] + 1) % m;
		dp[i][2] = i - half_i;
		for (register int j = 2, k; j <= half_i; j = k + 1){
			int ti = i / j;
			k = i / ti;
			dp[i][2] = (dp[i][2] + (dp[ti][1] + dp[ti][2]) * (k - j + 1) % m) % m;
		}
		sum[i][1] = (sum[i - 1][1] + dp[i][1]) % m;
		sum[i][2] = (sum[i - 1][2] + dp[i][2]) % m;
	}
	printf("%lld", (dp[n][1] + dp[n][2]) % m);
	return 0;
}
```

---

## 作者：Zxsoul (赞：1)


这是一道DP+整除分块的优化类题目，我还是第一次见，这场比赛收获太大了，

当然这个题目的难点我也看出来了，非常精髓。

首先我的第一个思路是：

设 $f[i]$ 表示 $n$ 到 $i$ 号点的方案数，然后按照题目意思顺理成章的得到了转移方程
$$
f[i]\to f[\lfloor\frac{i}{z}\rfloor]
\\ f[i] \to f[i-y]
$$
  然后暴力枚举就好了，然后观察是否可以优化，显然不能，因为这种转移的方向就决定了不可以优化，

然后第二思路出现了：

状态设计不变，改一下转移方向
$$
f[i]=\sum f[i\times z]+\sum f[i+y]
$$
经观察发现后面是一个后缀和，而前面却不对，因为题目中存在向下取整的情况，所以这个转移时错误的。

接下来就是正解的思路：

首先是状态设计的更改，$f[i]$ 表示 $1$ 到 $i$  的方案数，显然和之前的设计完全相反，然后状态的设计：
$$
f[i]=\sum f(i-y)+\sum (f\lfloor\frac{i}{z}\rfloor) 
$$
观察发现这个柿子很优美，一个前缀和，一个整除分块，直接优化就可以过了

时间复杂度在 $O(n\sqrt n)$

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
const int B=3e5+10;
int f[B];
int n;
int mod;
int sum[B];
int read() {int x; scanf("%lld",&x); return x;}
signed main()
{
	n=read(); mod=read();
	f[1]=1; sum[1]=1;
	for (int i=2;i<=n;i++)
	{
		int last,res=0;
		for (int j=1;j<=i;j=last+1)
		{
			int a=i/j;
			last=i/a;
			res=res%mod+f[a]*(last-(j-1))%mod;
		}
		f[i]=f[i]%mod+res%mod;
		f[i]=f[i]%mod+sum[i-1]%mod;
		sum[i]=(sum[i-1]%mod+f[i]%mod+mod)%mod; 
	}
	printf("%lld",f[n]%mod);
}

```

---

## 作者：cszhpdx (赞：1)

容易想到 $f_i$ 表示走到 $i$ 的方案数和转移方程（一开始我这个蒟蒻居然还觉着是刷表呢
$$
f_x=(\sum_{i=x+1}^nf_i)+(\sum\{f_y | x=\lfloor \frac{y}{k} \rfloor\})
$$
第一项很好求，维护一个后缀和，难点主要是在第二项

我们可以枚举 $k$ ，这时我们的 $k$ 固定下来了，显然 $y\in [xk,xk+k)$ 这样余数会被下取整抹掉，这样的话我们可以用后缀和维护这一段的和，于是我们的状态数是 $O(n)$ 的，转移是枚举一个 $k$ ，是 $O(\log_2 n)$ 的，总的复杂度就是 $O(n\log_2n)$ 

（考试的时候还推出一个没什么用的结论，就是 $[xk,xk+k)$ 之间的数不会因为第二个操作而互相影响，因为 $2xy \ge xk+k$ 以后可能用得到吧）

代码：

```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rp(i, e) rps(i, 1, e)
#define pr(i, e) prs(i, e, 1)
#define rp0(i, e) rps(i, 0, (e)-1)
#define pr0(i, e) prs(i, (e)-1, 0)
#define rpg(i, x) for(int i=head[x];i;i=e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
const int NR=2e5+10;
typedef long long LL;
LL n, p, f[NR], s[NR];
int main()
{
	cin>>n>>p;
	f[n]=s[n]=1;
	pr(i, n-1) {
		f[i]=s[i+1];
		for(LL j=2;i*j<=n;j++) {
			f[i]=(f[i]+(s[i*j]+p-s[min(i*j+j, n+1)]))%p; 
		}
		s[i]=(s[i+1]+f[i])%p;
	}
	cout<<f[1];
	return 0;
}
```

后记：这题本来考场上推出来了，以为复杂度是 $O(n\sqrt n)$ 现在才知道有调和级数这个东西，所以没敢提交 D2 ，后悔啊，要是内会提交了我的 rating 就起飞了

---

## 作者：James0602 (赞：0)

# 题目大意

一开始在 $n$ 这个格子，然后每次可以从 $x$ 到达 $1$ ~ $x$ 的任意一个格子，或者说选择一个 $z$ ,到达 $\lfloor\frac{x}{z}\rfloor$ 这个格子。

# 解题思路

首先很自然的想到要用 dp ，设 $f_i$ 表示从 $n$ 到达第 $i$ 格的方案数。

可以按照题意转移，但是 $n^2$ 显然是不现实的。

考虑优化，可以给个前缀和，然后对于第二个操作我们用数论分块来解决。

时间复杂度 $O(n\sqrt n)$ 

### code
```cpp
#include<cstdio>
#define ll long long
using namespace std;
int n;
ll m,f[4000005];
int main(){
	scanf("%d%lld",&n,&m);
	f[n]=1;
	ll sum=0;
    //主动转移
	for (int i=n;i>1;--i){
		f[i]+=sum;f[i]%=m;
		sum+=f[i];sum%=m;
		for (int l=2,r=0;l<=i;l=r+1){//数论分块
			r=i/(i/l);
			f[i/l]=(f[i/l]+f[i]*(ll)(r-l+1)%m)%m;
		}
	}
	printf("%lld",(f[1]+sum)%m);
	return 0;
}
```

那这样D1就可以做出来了，但我们考虑能不能更优。

我们换个思路，考虑被动转移。

对于 $f_i$ 来说，它是等于 

$$\sum_{j=i+1}^nf_j+\sum_{z}\sum_{j=i+1}^nf_j[\lfloor\frac{j}{z}\rfloor==i]$$

考虑对于后面那部分，对于 $z$ 来说，我们可以枚举，然后对于后面枚举的 $z$ ,我们可以用前缀和优化，因为我们可以算出来对于当前的 $z$ ,有贡献的 $j$ 所在的区间，且一定是连续的。

然后对于枚举的 $z$ ，其实就是 $\frac{n}{1}+\frac{n}{2}+···+\frac{n}{n}=nlogn$ ，即总时间复杂度为 $O(nlogn)$

具体细节看代码。

### code
```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
const int N=4e6+5;
int n;
ll P,s[N],f[N];
int main(){
	scanf("%d%lld",&n,&P);
	f[n]=1;s[n]=1;
	for (int i=n-1;i>=1;--i){
		f[i]=s[i+1];
		for (int z=2;z*i<=n;++z)
			f[i]=(f[i]+(s[i*z]-s[min(i*z+z,n+1)]+P)%P)%P;//所在区间为[i*z,i*z+z-1]
		s[i]=(s[i+1]+f[i])%P;
	}
	printf("%lld",f[1]);
	return 0;
}
```

---

## 作者：dalao_see_me (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1561D1)
## 题目大意
给一个数 $n$，每次可以让它变为区间 $[1,n)$ 中的任意一数，也可以让它变为 $\lfloor\frac{n}{t}\rfloor$，其中 $t\in(1,n]$。问从 $n$ 变为 $1$ 的方案数（需要取模）。
## 做法
我们考虑 dp。

设 $f_i$ 为从 $i$ 转移到 $1$ 的方案数。

根据题目条件，我们可以得出如下式子：
$$
f_i=\sum_{j=1}^{i-1}f_j+\sum_{j=2}^if_{\lfloor\frac{i}{j}\rfloor}
$$
前半部分，可以用前缀和优化为 $O(1)$。

后半部分，可以用整除分块优化为 $O(\sqrt n)$。

什么是整除分块？

对于 $\lfloor\frac{n}{i}\rfloor$（其中 $n,i$ 是正整数），最多只有 $O(\sqrt n)$ 种取值。

如何证明？~~读者自证不难。~~

考虑 $i>\sqrt n$ 时，$\lfloor\frac{n}{i}\rfloor<\sqrt n$，于是最多只有 $O(\sqrt n)$ 个值。

考虑 $i\le\sqrt n$ 时，由于 $i$ 本身仅有 $O(\sqrt n)$ 种取值，所以该部分也仅有 $O(\sqrt n)$ 个值。

综合一下，一共就是 $O(\sqrt n)$ 种取值。然后就进入了代码时间。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int f[N], s[N];//s为前缀和
int n, mod = 998244353;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
signed main() {
	n = read();
	f[1] = 1; s[1] = 1;
	for (register int i = 2; i <= n; i++) {
		f[i] = s[i - 1];
		for (register int l = 2, r; l <= i; l = r + 1) {//整除分块
			r = i / (i / l);
			f[i] = (f[i] + f[i / l] * (r - l + 1) % mod) % mod;
		}
		s[i] = (s[i - 1] + f[i]) % mod;
	}
	printf("%lld", f[n]);
	return 0;
}
```

---

## 作者：Cocoly1990 (赞：0)

唔大家都是整除分块，复杂度都是 $\mathcal{O\left(n\sqrt{n}\right)}$ 的，我这篇文章主要讲一个 $\mathcal{O\left(n\log^2n\right)}$ 的，对，为什么会多带一个 $\log$，我会稍微总结一下我的赛时脑瘫操作。

赛时硬刚 C，结果题意读错了，最后一个小时来看 D1，心想这不是个一眼题吗，随便转移一下然后优化一下就好了。

那么，重点就在于如何转移，大部分的题解都是正向转移，不如考虑倒向转移，定义 $f_i$ 为令牌移到 $i$ 时的状态数。

$$f_i=\sum_{k=i+1}^nf_k+\sum_{j=2}^{j\times i\leq n}\sum_{k=j\times i}^{\min\left(n , j \times i + j - 1\right)}f_k$$

上面的柿子没什么好讲了吧，基础的状态转移。考虑优化。

讲下赛时思路，我简单看了一下，这每次加的 $f_k$ 都是一段连续的区间哎，不如树状数组维护吧。

然后成功获得了一个带 $\log$ 的数据结构。

其实完全不必要那么麻烦，因为所谓的单点修改操作其实是有序添加的，也就是只会往队列的末尾添加，所以写一个 $\mathcal{O}\left(1\right)$ 的前缀和维护就好了。

下面计算时间复杂度，前面的部分 $\mathcal{O}\left(n\right)$ 维护，后面的是个显然的调和级数， $\mathcal{O}\left(n\log n\right)$ 可做。

贴一个 $\mathcal{O\left(n\log^2n\right)}$ 的代码，可以通过 D1，至于 D2 把维护方式改一下就好了。

可是我赛时并没有通过此题，原因很简单，我没开 ll，本来也没什么问题，因为模数在 $10^9$，可是我在维护树状数组的时候取模操作没做好，所以，这场 CF 上坟了。

总结一下失误点，一是能用前缀和维护的写你妈树状数组，模数太大保险一点要开 ll。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std ;
int tree[2000007] , n , m , ch , x , y , Mod ;
int lowbit(int x)
{
    return x & (- x) ;
}
int sum(int x)
{
    int ans = 0 ;
    while(x)
    {
        ans += tree[x] % Mod ;
        x -= lowbit(x) ;
    }
    return ans ;
}
void add(int x , int num)
{
    while(x <= n)
    {
        tree[x] += num % Mod ;
        tree[x] %= Mod ;
        x += lowbit(x) ;
    }
}
int query(int x , int y)
{
    //if(x > y) swap(x , y) ;
    return sum(y) % Mod - sum(x - 1) % Mod ;
}
signed main()
{
    cin >> n >> Mod ;
    add(n , 1) ;
    //cout << query(n , n) ;
    for(int i = n - 1 ; i >= 1 ; i --)
    {
        // dp[i] = dp[i + 1 ~ n] + dp[1]
        // 3 -> 1 2->1 1 -> 2 + 
        m = 0 ;
        m = query(i + 1 , n) % Mod ;
        //cout << m << " " ;
        int j ;
        for(j = 2 ; j * i <= n ; j ++) m += query(min(n , j * i) , min(n , j * i + j - 1)) % Mod ;
        //if(j * i <= n) m += query(j * i , min(n , j * i + j - 1)) ;
        //cout << m << endl ;
        add(i , m % Mod) ;
    }
    cout << (sum(1) + Mod) % Mod ;
    return 0 ;
}
```

---

## 作者：wanggiaoxing (赞：0)

### 分析算法
这题有取模，显然不能直接暴力，我们可以考虑 $dp$ 来求答案，具体来说 $dp[i]$ 表示到 $i$ 的方案数.$dp[i]=(\sum \sum dp[i*k+x])+(\sum dp[j])$.

其中第一部分的求和中 $2\leqslant k\leqslant n/i$，$0\leqslant x\leqslant k-1$,第二部分的求和中 $i+1\leqslant k\leqslant n$.

第二部分的求和显然可以前缀和优化,第一部分直接暴力求就好了，不会超时。因为它每一次的复杂在 $\log(n)$ 左右。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int n,mod,dp[200005],sum[2000005];
signed main()
{
    n=read(),mod=read();
    sum[n]=dp[n]=1;
    for(int i=n-1;i>=1;i--){
        dp[i]=sum[i+1];
        for(int j=n/i;j>=2;j--)
            dp[i]=(dp[i]+sum[i*j]-sum[i*j+j])%mod;
        sum[i]=(dp[i]+sum[i+1])%mod;
    }
    printf("%d",(dp[1]+mod)%mod);
    return 0;
}
```

















---

## 作者：anda (赞：0)

这题首先想到从小往大递推，每次枚举乘数，然后我们发现被除数除以乘数等于枚举数的是连续的一段，可以用差分维护，时间复杂度调和级数。
然后对于减法操作也是一段区间，直接差分就行了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[8000001];
signed main(){
scanf("%lld%lld",&n,&m);
f[1]=1;
for(int i=1;i<=n;i++){
	f[i]=(f[i]+f[i-1])%m;
	f[i+1]=(f[i+1]+f[i])%m;
	for(int j=2;i*j<=n;j++)f[i*j]=(f[i*j]+f[i])%m,f[i*j+j]=(f[i*j+j]-f[i])%m;
	f[1]=0;
}
cout<<(f[n]+m)%m;
return 0;
}
```


---

