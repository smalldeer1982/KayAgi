# [ABC400C] 2^a b^2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc400/tasks/abc400_c

当且仅当满足以下条件时，正整数 $X$ 被称为好整数：

- 存在正整数对 $(a, b)$，使得 $X = 2^a \times b^2$。

例如，$400$ 可以表示为 $400 = 2^2 \times 10^2$，因此它是一个好整数。

给定正整数 $N$，请计算 $1$ 以上 $N$ 以下（含）的好整数的个数。

## 说明/提示

### 约束条件

- $1 \leq N \leq 10^{18}$
- $N$ 为整数

### 样例解释 1

$1$ 以上 $20$ 以下的好整数有 $2, 4, 8, 16, 18$ 共 $5$ 个，因此输出 $5$。

### 样例解释 3

请注意输入可能超出 $32$ 位整数类型的表示范围。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
20```

### 输出

```
5```

## 样例 #2

### 输入

```
400```

### 输出

```
24```

## 样例 #3

### 输入

```
1234567890```

### 输出

```
42413```

# 题解

## 作者：szh_AK_all (赞：13)

为什么很多人没写出来这题啊。

考虑枚举 $2^a$，这个复杂度我们是很可以接受的，那么问题就转换成了我们要求有多少 $b$ 满足 $2^a \times b^2\le n$，也就是 $b^2\le \lfloor \frac{n}{2^a} \rfloor$，那么对 $\frac{n}{2^a}$ 开个根号便是 $b$ 的最大取值。但注意到这样计算可能会算重，例如当 $a=2,b=12$ 时，它代表着 $2^2\times 12^2=576$，而 $576$ 也可以表示为 $2^4\times 6^2$，还可以表示为 $2^6\times 3^2$，这提醒我们当 $b$ 为偶数时，我们就可以从 $b$ 中不断提出 $2^2$ 给 $a$，所以为了避免算重，我们可以倾定 $b$ 是奇数。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int n;
	cin >> n;
	int x = 1, ans = 0;
	while (1) {
		x *= 2;
		int k = n / x;
		if (!k)
			break;
		ans += (int)sqrtl(k) - ((int)sqrtl(k)) / 2;
	}
	cout << ans;
}
```

---

## 作者：sundingjia (赞：9)

# 前言

在此提供一种 $\operatorname{O}(1)$ 的解法。$11$ 行（不压行）可 AC。

# 题目大意

若存在正整数对 $(a,b)$ 满足 $2^a \times b^2 \le x$，则我们称 $x$ 是个好数。给定正整数 $n$，请问 $n$ 以内有多少个好数？

# 思路

## 结论

先上结论：一个数若等于一个正整数的平方的**两倍**或等于一个**正偶数**的平方，那么这个数是好数。反之亦然。

## 感性认知一下

注：未做特殊声明，以下所有数全部为**正整数**。

$2^1 \times b^2 = 2 \times b^2$

$2^2 \times b^2 = (b \times 2^1)^2$

$2^3 \times b^2 = 2 \times (b \times 2^1)^2$

$\dots$

以此类推：

$2^{2k} \times b^2 = (b \times 2^k)^2$，即一个**正偶数**的平方。

$2^{2k-1} \times b^2 =2 \times (b \times 2^{k-1})^2$，即一个正整数的平方的**两倍**。

由此，得出以上结论。

## 代码

得到这些，代码应该就不难写了吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n;
	cin>>n;
	long long tmp1=sqrtl(n)/2; //求等于正偶数平方的好数的个数。
	long long tmp2=sqrtl(n/2); //求等于正整数的平方的两倍的好数的个数。
	cout<<tmp1+tmp2;         
	return 0;
}
```

[赛时通过记录](https://atcoder.jp/contests/abc400/submissions/64516707)

# 警示后人

1. 十年 OI 一场空，不开 `long long` 见祖宗。
2. 建议开方用 `sqrtl`，不然有概率爆精度。

---

## 作者：wmrqwq (赞：6)

这是一篇视频题解。

![](bilibili:BV19BRdYdEHk?t=148)

[参考代码](https://atcoder.jp/contests/abc400/submissions/64514005)

---

## 作者：N1tr0us_Acid (赞：2)

有意思。

# $\texttt{Solution}$
因为 $n \le 10^{18}$，所以枚举 $b^2$ 会超时，所以考虑从 $2^a$ 入手。

先暴力求出最大的 $a$，然后对于每一个 $1 \le i \le a$，求出所有满足 $1\le b^2 \le \frac{n}{2^i}$ 且是**奇数**的 $b$ 的数量，这就是答案。

为什么只用求奇数？

显然，对于每一个 $b$ 是偶数的 $400$ 数，都可以把其变成如下形式：

$$2^a \times (2^mk)^2$$

其中 $k$ 是奇数。

不难发现，这个数其实等于 $2^{a+2m} \times k^2$，而因为 $k$ 是奇数，所以这个数将会被统计。

这样就避免了重复统计 $400$ 数。

# $\texttt{Code}$
```cpp

#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;
int ans;

signed main() {
	cin >> n;

	int maxn = 0;

	while ((1ll << (maxn + 1)) <= n) {
		maxn ++; //暴力求出最大的 a
	}

	for (int i = 1; i <= maxn; i ++) {
		int p = (1ll << i);

		if(p > n) break;

		int las = n / p;

		if(las < 1) continue;

		int sq = sqrt(las);

        while (sq * sq <= las) sq ++;
		while (sq * sq > las) sq --; //调整 sq，防止超出限制

		ans += (sq + 1) / 2; //统计 1-sq 中的奇数数量
	}

	cout << ans << endl;

    return 0;
}
```

---

## 作者：2huk (赞：2)

只要确定 $a,b$ 就能确定这个数字 $2^a\times b^2$，于是考虑枚举一个值。注意到 $a \le \log n,b \le \sqrt n$，显然是要枚举 $a$ 的。

即，我们考虑求解有多少 $b$ 满足 $2^a \times b^2 \le n$。这是极易的，答案为 $\left \lfloor \sqrt \dfrac{n}{2^a} \right\rfloor$。

于是答案为 $\sum_{a=0}^{70}\left \lfloor \sqrt \dfrac{n}{2^a} \right\rfloor$。但是样例没过，这是因为 $288 = 2^5 \times 3^2 = 2^3 \times 6^2 = 2^1 \times 12^2$，一个数被算了三次。

怎么不重复的计数呢？注意到如果 $b$ 是个偶数，设 $b=2b_0$，那么 $2^a \times b^2 = 2^a \times (2b_0)^2 = 2^{a+2}\times b_0^2$，也就是说只要 $b$ 是偶数这个数字就会在另一种方式内被算到。而 $b=2b_0,b_0=2b_1,b_1=2b_2\dots$，最终那个数字肯定是奇数。于是，为了不算重，我们强制让 $b$ 为偶数即可。

那么 $1 \sim \left \lfloor \sqrt \dfrac{n}{2^a} \right\rfloor$ 中有多少奇数呢？除以二上取整即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
	int n;
	cin >> n;
	
	int res = 0;
	for (int a = 1, A = 2; A <= n; ++ a, A *= 2) {
		res += (sqrtl(n / A) + 1) / 2;
	}
	
	cout << res;
	
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：1)

注意看到我这道题到 $64:31$ 才 AC，还罚时一发。

$2^a$ 增长很快，可以枚举 $a$，计算 $b$ 的个数。

由不等式性质得：$2^a \times b^2 \le N$，$ b^2 \le \dfrac N {2^a}$。两边开平方，$b\le \sqrt{\dfrac N {2^a}}$。

然而，若把所有偶数 $b$ 都计入答案，则会有重复。理由很简单，设 $b=2c$，则：

$$2^a\times (2c)^2=2^a \times 2^2 \times c^2=2^(a+2) \times c^2$$

若 $a_1 = a+2 , b_1 = c$，则 $2^{a_1} \times b_1^2=2^a\times b^2$，重复。$b$ 为奇数时，没有此情况。

因此，合法的 $b$ 个数为 $\lceil \dfrac{\sqrt{\dfrac N {2^a}}} 2  \rceil$。

坑点：开根用 `sqrtl`，否则有浮点误差。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int n,su=0;
	inline int Get(int x){
		int y=sqrtl(x);
		if(y&1)return y/2+1;else return y/2;
	}
	inline void zyt(){
		n=r();
		for(ri i=2;i<=n;i*=2)su+=Get(n/i);
		w(su);
	}
}
signed main(){
	D1n0::zyt();
}
```

---

## 作者：cjx_AK (赞：1)

### 题意
好整数的定义：存在两个数 $a$ 和 $b$，使得 $n=2^a\times b^2$。

求 $1$ 到 $n$ 中好整数的个数。

### 思路
由于 $n>10^9$，显然不能直接枚举。

我们可以把好整数进行分解：$n=2^a\times b^2$，当 $a>2$ 时，$n=2^{a-2}\times(2\times b)^2$。
我们可以只计算 $b$ 的情况，也就是 $\frac{n}{2^a}$ 中平方数的个数。
这样的方法计算，会有重复的情况，也就是有重复的平方数，只需计算 $a=1$ 或 $a=2$ 的情况即可。

code：
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll sqr(ll x){
	ll q=sqrt(x);
	if((q+1)*(q+1)<=x)q=q+1;
	else if((q-1)*(q-1)<=x&&q*q>x)q=q-1;
	return q;
}
int main(){
cin>>n;
	cout<<sqr(n/2)+sqr(n/4);
	return 0;
}
```

---

## 作者：Tairitempest (赞：1)

## [ABC400C] 2^a b^2
有 $2^{2n+a}b^2=2^a(2^nb)^2$。

由上面的式子可以注意到 $a=1$ 和 $a=2$ 的情况会覆盖所有可能的情况，所以统计不超过 $\sqrt{\frac{n}{2}}$ 的整数数量和不超过 $\sqrt{\frac{n}{4}}$ 的整数数量的总和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main(){
	cin>>n;
	cout<<ll(sqrtl(n/2))+ll(sqrtl(n/4))<<endl;
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

## 思路

题目要求在 $1\sim N$ 中有多少数 $p$，使得 $p=2^ab^2$。

$N$ 很大，我们无法用枚举的方法罗列个数。由于 $b^2$ 的得数不好算，我们从 $2^a$ 入手。

为了让 $2^ab^2$ 不重复，所以我们令 $b$ 为奇数（因为偶数会让结果分解出 $2$，导致结果重复），每次让 $2$ 指数加一，只要 $b\le \sqrt{\dfrac{N}{2^a}}$，结果都是正确的。其中根号可以手搓 $O(\log n)$，$2^a\le N$，循环 $\log N$ 次。

综上时间复杂度为 $O((\log N)^2)=O(\log^2 N)$。

### 提示

1. 根号手搓可以用二分的方式，自己想一想。
2. 记得开 long long。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int wsqrt(long long x) {
    if (x < 0) return 0;
    int l = 0, r = x;
    int ans = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (mid == 0) {
            if (x >= 0) {
                ans = 0;
                l = mid + 1;
            } else r = mid - 1;
            continue;
        }
        if (mid <= x / mid) { // 防止溢出
            ans = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return ans;
}

signed main() {
    int N;
    cin >> N;
    int ans = 0,pow2 = 2; // 初始为2^1
    while (pow2 <= N) {
        int M = N / pow2;
        int maxn = wsqrt(M);
        int cnt = (maxn + 1) / 2;//统计合法奇数个数
        ans += cnt;
        pow2 *= 2;//2的指数个数加一
    }

    cout << ans << endl;
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

好整数必须满足其质因数分解中，除了 $2$ 的指数至少为 $1$ 外，其他质数的指数必须均为偶数。可以将好整数唯一地表示为 $X = 2^s\times k^2$，其中 $k$ 是奇数，$1\le s$。对于每个可能的 $s$，计算满足条件的 $k$ 的数目，然后累加所有可能 $s$ 的结果。参考代码：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define endl '\n'
#define itn int
#define pi pair<int,int>
#define int ll
using namespace std;
const int MOD1=1e9+7;
const int MOD2=998244353;
const int N=1e5+5;
inline void Solve(){
	int n;
	cin>>n;
	int s=0;
	while((1ll<<(s+1))<=n)s++;
	int ans=0;
	for(int i=1;i<=s;i++){
		int v=n>>i;
		if(v==0)break;
		int k=sqrt(v);
		while(k*k>v)k--;
		ans+=(k+1)/2;
	}
	cout<<ans;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=1;
    //cin>>T;
    while(T--)
    	Solve();
    return 0;
}

```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[ABC400C](https://www.luogu.com.cn/problem/AT_abc400_c)

## Statement

定义好数 $X$：

- $\exist a,b \in \N_+$，使得 $X = 2^a \times b^2$。

现给定 $N$，求 $1 \sim N$ 内的好数个数。

## Solution

考虑直接枚举 $a$，这样就是 $O(\log N)$ 级别的。

这样对于 $\forall a \in [1,\log N]$，对应的 $b$ 的取值可能的个数就有 $\sqrt{\frac{N}{2^a}}$ 种，但是请注意，这样有些数会选重。

假设 $x = 2^i \times a,y = 2^i \times b$，如果说 $b = 2^p \times a$，那么 $b$ 之后一定会被筛到，这样就会选重。

所以我们要的就是 $\sqrt{\frac{N}{2^a}}$ 中的奇数个数，也就是 $\frac{\sqrt{\frac{N}{2^a}} + 1}{2}$。

**注意精度**。

## Code

[Submission](https://atcoder.jp/contests/abc400/submissions/64572631)

---

