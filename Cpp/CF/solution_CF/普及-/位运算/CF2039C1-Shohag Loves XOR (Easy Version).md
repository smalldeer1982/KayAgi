# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1```

### 输出

```
3
2
1
1
0```

# 题解

## 作者：SUNCHAOYI (赞：4)

给定 $x,m$，求有多少 $y$ 满足 $y \in [1,m],x \neq y$ 且 $x \oplus y$ 是 $x$ 或 $y$ 的因子。

结论猜测：$x \oplus y \in [1,x)$，下面是证明：

对于一个 $p$ 的因子 $f$，满足 $f \le \lfloor \frac{p}{2} \rfloor$，也就是说 $f$ 和 $p$ 在二进制下的最高位不同。

当 $y \ge 2x$ 时，$x \oplus y$ 与 $y$ 在二进制下的最高位相同，所以 $x \oplus y$ 在此时必定不是 $y$ 的因子。同时，由于最高位的不同，此时 $x \oplus y > x$ 一定成立，所以 $x \oplus y$ 同样也不是 $x$ 的因子。

所以说，只有 $y < 2x$ 时，才能满足题意，也就是说因子 $x \oplus y < x$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline ll read ();
ll t;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		ll x = read (),m = read ();
		ll cnt = 0;
		for (int i = 1;i <= x;++i)
		{
			ll y = x ^ i;
			if (!(1 <= y && y <= m)) continue;
			if (x % (x ^ y) == 0 || y % (x ^ y) == 0) ++cnt;
		}
		printf ("%lld\n",cnt);
	}
	return 0;
}
inline ll read ()
{
    ll s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：Fiendish (赞：4)

个人感觉这道题质量挺高的。

为方便描述，下文中的“位数”均指一个数**在二进制下的位数**。

最纯粹的暴力是枚举 $y$，但是 $y$ 范围太大，会超时。考虑如何缩小一下 $y$ 的范围。可以证明 $y$ 的位数一定小于等于 $x$ 的位数，我们分两种情况讨论一下：

1. 若 $x\oplus y$ 为 $x$ 的因数，那么 $x\oplus y\le x$，此时若 $y$ 的位数大于 $x$，那么显然 $x\oplus y$ 的位数一定与 $y$ 的位数相等，这是因为 $y$ 比 $x$ 多出的若干位没有发生变化，所以 $y$ 的位数一定不超过 $x$ 的位数；
2. 若 $x\oplus y$ 为 $y$ 的因数，由于 $x\neq 0$，所以 $x\oplus y\neq y$，因此 $x\oplus y\le \lfloor\frac{y}{2}\rfloor$（因为 $\frac{y}{2}$ 是除 $y$ 以外 $y$ 的最大的可能的因数），而 $\lfloor\frac{y}{2}\rfloor=y\gg1$，也就是说，$x\oplus y$ 的位数一定小于 $y$ 的位数，由第一种情况可知，如果 $y$ 的位数大于 $x$ 的位数，那么 $x\oplus y$ 的位数一定与 $y$ 的位数相等，显然不可能是 $y$ 的因数，所以 $y$ 的位数一定不超过 $x$ 的位数。

综上所述，$y$ 的位数一定不超过 $x$ 的位数。这样我们每次枚举位数小于等于 $x$ 的数即可，一组数据时间复杂度 $O(n)$，可以通过此题。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int x;
long long m,ans;
int main(){
	cin>>T;
	while(T--){
		ans=0;
		cin>>x>>m;
		for(int i=1;i<min((1ll<<((int)__lg(x)+1)),m+1);i++)//枚举缩小后的范围内的 y
			if(i!=x&&(x%(i^x)==0||i%(i^x)==0)) ans++;
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Limerency (赞：3)

### Solution

我们注意到，对于任意的 $y$，如果满足上述条件，那么 $f(x) = f(y)$，其中 $f(p)$ 定义为 $p$ 在二进制下的位数。那么我们直接暴力枚举所有 $f(x)=f(y)$ 的 $y$ 就做完了，复杂度 $\mathcal{O}(2^{\lfloor\log x \rfloor})$，可以通过。

下面给出结论的证明：不妨设 $f(x) > f(y)$，$x \oplus y > y$，所以 $x \oplus y$ 不能被 $y$ 整除。同时我们又有 $x \oplus y > \frac{x}{2}$，因此 $x \oplus y$ 不能被 $x$ 整除。证完了。

### Code

```cpp
namespace solve {
    int x; i64 m;
    int solve() {
        cin >> x >> m;
        int hb = 1, p = x, ans = 0;
        while (p) p >>= 1, hb <<= 1;
        int lm = min(hb - 1ll, m);
        for (int i = hb >> 1; i <= lm; i ++) {
            int t = (x ^ i);
            if (x != i) if (x % t == 0 || i % t == 0) ans ++;
        }
        cout << ans << '\n';
        return 0;
    }
}
```

---

## 作者：Chenyanxi0829 (赞：2)

考虑 $x$ 与 $y$ 的二进制最高位，如果不同，不妨设 $x$ 的最高位更高，那么 $x\oplus y$ 的二进制最高位就与 $x$ 的最高位相同，所以 $x\oplus y>y,x\oplus y\not=x,x\oplus y>\lfloor\frac{x}{2}\rfloor$，且 $x$ 最大的除了其自身的因数至少为 $\lfloor\frac{x}{2}\rfloor$，于是我们就发现了这种情况下肯定不满足要求。那么我们就只需要考虑二进制最高位与 $x$ 相同的 $y$，而数据范围又保证了 $\sum x\le10^7$，所以可以直接枚举所有 $\le\min(m,2x)$ 的 $y$。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 6e3 + 354, mod = 992843457;

int t, x, ans;
long long m;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> x >> m, ans = 0;
    for (int i = 1; i <= min(m, 2ll * x); i++) {
      ans += (x != i && (x % (x ^ i) == 0 || i % (x ^ i) == 0));
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：_lmh_ (赞：1)

根据 $\oplus$ 的性质，$x-y\le x\oplus y \le x+y$。（考虑拆位：$x-y$ 和 $x+y$ 在所有位置上都是加或者减，但是 $\oplus$ 有些位会相加，有些位会相减，取值自然在它们两个中间。）

而 $x\oplus y$ 是 $x$ 或者 $y$ 的因数。显然其不可能等于 $x$ 或者等于 $y$，所以 $x\oplus y<x$ 或 $x\oplus y \ge \frac{y}{2}$，利用上面的那个式子可以得出 $y\le 2x$。所以我们只用枚举 $O(x)$ 个数，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll T,x,n,ans;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>x>>n;n=min(n,x*2);ans=0;
		for (int i=1;i<=n;++i) if (x!=i){
			if (x%(x^i)==0||i%(x^i)==0) ++ans;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Dangerise (赞：0)

比较考验注意力

## 分析

注意到数据范围 $x\le 10^6, m\le 10^{18}$,

显然，对于 $y \le x$ 的部分，我们直接模拟就行了，但是要怎么考虑 $y > x$ 时的贡献呢？

由于是异或操作，所以我们应该从二进制的角度去分析。

设 $x$ 的二进制下的位数为 $k$。

当 $y \ge 2^k$。

对于 $x \oplus y$ 的结果, 相较于 $y$，变化的肯定只有后 $k$ 位，即 $y$ 的最高位是不变的。

那么很显然 $\frac{y}{2} < x \oplus y $。

即, 当 $y \ge 2^k$ , $x \oplus y$ 不可能是 $y$ 的因子。

由于 $x \oplus y > x$ 显然成立,它也不可能是 $x$ 的因子。

所以我们只要计算 $y\le 2^k$ 的部分就可以了。

## 代码

```cpp
int lowbit(int x) { return x & (-x); }
int highbit(int x) {
    int l = 0;
    while (x) {
        l = lowbit(x);
        x -= l;
    }
    return l;
}
 
signed main() {
    int T = qread();
    while (T--) {
        int x = qread(), m = qread();
        int f = highbit(x) * 2;
        m = min(f, m);
        int ans = 0;
        L(i, 1, m) {
            if (x == i) {
                continue;
            }
            int v = i ^ x;
            if (i % v == 0 || x % v == 0) {
                ans++;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

在区间 $[1,m]$ 中，有多少个数 $y$ 使得 $x\oplus y$ 是 $x$ 或 $y$ 的因数。

### 思路：

发现 $x$ 的范围并不大。而且我们有一个显而易见的性质：当 $x\neq0$ 且 $y$ 的二进制最高位大于 $x$ 时，$x\oplus y$ 一定大于 $x$ 且小于 $y\times 2$（当然也不会等于 $y$），条件不可能满足。

因此，只需要枚举 $1$ 到 $x\times 2$ 的所有数，判断是否满足条件即可。

### 程序如下：

```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int N=5e5+5;
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		int x,ans=0;
		long long m;
		scanf("%d%lld",&x,&m);
		for(int i=1;i<=m&&i<=(x<<1);i++){
			if(i==x)continue;
			int res=x^i;
			if(i%res==0||x%res==0)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

### THE END

---

## 作者：Binah_cyc (赞：0)

撑死胆大的，饿死胆小的。

本题解上半部分介绍赛时如何快速想出本题，下半部分为严谨证明，请根据自己情况自行食用。

$\sum x \le 10^7$ 的限制已经很明显了，复杂度为 $O(x)$。考虑什么值的范围大致在 $[1,x]$ 范围内。

观察样例加打表，可以发现有贡献且在范围内的只有 $x \oplus y$。然后我们在 $[1,x \times 10]$ 范围内枚举 $x \oplus y$ 并统计答案。这道题就过了。实际上枚举 $2$ 倍就完全够了，枚举 $10$ 倍只是赛时没有证，求稳之举。

考虑如何证明。

如果 $x \times 2 \leq y$，那么 $x \le x \oplus y$。因此，$x \oplus y \not | x$。同时，因为 ${y \over 2} \le x \oplus y$，所以它也不可能成为 $y$ 的约数。因此，当 $y > x$ 时，它不可能产生贡献。因此，在枚举 $x \oplus y$ 的时候，只需要枚举到 $2 \times x$ 就行了。~~但是别管枚举多少，能过的做法就是好做法。~~

---

## 作者：postpone (赞：0)

$x$ 的范围小，但 $y$ 的范围太大了，不妨思考一下怎么缩小范围。

一个关于因数的性质：对任意两个正整数 $a$ 和 $b$，当 $a>\lfloor \frac{b}{2}\rfloor$ 时，$a$ 一定不是 $b$ 的因数。

由于 $y$ 的范围大，先看 $y$，即要考虑 $x \oplus y$ 在什么情况下一定大于 $\lfloor \frac{y}{2}\rfloor$。从位的角度看，和 $0$ 异或相当于不变，当 $y$ 比 $x$ 多一位，则运算后最高位的 $1$ 会保留，即此时一定有 $x \oplus y >\lfloor \frac{y}{2}\rfloor$。

而 $y$ 比 $x$ 多一位的时候，$x \oplus y > x$，也就肯定不是 $x$ 的因数。

因此，$y$ 在超过 $2x$ 的部分，都不符合题意，则只需要遍历 $[1, \min\{2x, m\}]$ 中的整数即可，代码如下。

```cpp
auto solve() {
    int x;
    ll m;
    cin >> x >> m;

    m = min<ll>(2 * x, m);
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (i == x) {
            continue;
        }
        int t = i ^ x;
        if (x % t == 0 or i % t == 0) {
            ans++;
        }
    }
    cout << ans << "\n";

}
```

---

## 作者：sbno333 (赞：0)

考虑 $x\oplus y$ 为 $y$ 的因子需要哪些条件，发现 $x$ 与 $y$ 异或后为 $y$ 的因子需要至少除以二，即二进制下最高位消失，这需要 $y<2x$。同时，如果希望异或和为 $x$ 的因子，当 $y\ge 2x$ 时，$x\oplus y$ 因为最高位太高导致比 $x$ 大，从而不为 $x$ 因子，因此枚举 $1\le y\not=x\le\min(2x,m)$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void _main(){
	int x,m;
	cin>>x>>m;
	int ans;
	ans=0;
	for(int y=1;y<=min(2*x,m);y++){
		if(x!=y)
		if((x%(x^y)==0||y%(x^y)==0)){
			ans++;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

