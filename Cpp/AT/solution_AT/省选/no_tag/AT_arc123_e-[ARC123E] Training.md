# [ARC123E] Training

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc123/tasks/arc123_e

$ X $ さんと $ Y $ さんの $ 2 $ 人のプログラマが、競技プログラミングを始めることになりました。

競技プログラミングの実力は、「レベル」と呼ばれる正の整数で表され、はじめ $ X $ さんのレベルは $ A_X $、$ Y $ さんのレベルは $ A_Y $ です。$ 2 $ 人はこれから練習メニューをこなすことで、レベルを上げていきます。

$ 2 $ 人のレベルの上がり方について、次のことが分かっています：

- $ X $ さんはちょうど $ B_X $ 個の練習メニューをこなすたびに、レベルがひとつ上がります。
- $ Y $ さんはちょうど $ B_Y $ 個の練習メニューをこなすたびに、レベルがひとつ上がります。

$ n\ =\ 1,\ 2,\ \ldots,\ N $ のうちで次を満たすものはいくつあるかを答えてください。

- $ 2 $ 人がちょうど $ n $ 個ずつの練習メニューをこなした場合、$ 2 $ 人の最終的なレベルは等しくなる。

一つの入力ファイルにつき、$ T $ 個のテストケースに答えてください。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 2\times\ 10^5 $
- $ 1\leq\ N\leq\ 10^{9} $
- $ 1\leq\ A_X,\ B_X,\ A_Y,\ B_Y\ \leq\ 10^6 $

### Sample Explanation 1

ひとつめのテストケースについて説明します。 $ n\ =\ 1,\ 2,\ \ldots,\ 10 $ に対して、$ n $ 個の練習メニューをこなした場合の $ 2 $ 人のレベルは次のようになります： - $ X $ さんのレベル：$ 5,\ 5,\ 6,\ 6,\ 6,\ 7,\ 7,\ 7,\ 8,\ 8 $ - $ Y $ さんのレベル：$ 4,\ 5,\ 5,\ 6,\ 6,\ 7,\ 7,\ 8,\ 8,\ 9 $ $ 6 $ 個の $ n $ （$ n\ =\ 2,\ 4,\ 5,\ 6,\ 7,\ 9 $）の場合に $ 2 $ 人のレベルが等しくなります。したがって答えは $ 6 $ となります。

## 样例 #1

### 输入

```
5
10 5 3 4 2
5 5 3 4 2
100 5 3 4 2
10 5 3 4 3
10 5 10 5 9```

### 输出

```
6
3
6
0
9```

# 题解

## 作者：EuphoricStar (赞：3)

不妨假设 $B_X \le B_Y$。设 $f(x) = A_X + \frac{x}{B_X}, g(x) = A_Y + \frac{x}{B_Y}, F(x) = \left\lfloor{f(x)}\right\rfloor, G(x) = \left\lfloor{g(x)}\right\rfloor$，题目即求 $\sum\limits_{x=1}^n [F(x) = G(x)]$。

我一开始尝试化简式子，然后发现不能合并两个下取整的分数。

然后尝试二分 $F(x) - G(x) = 0$ 的区间，很快也发现不行，因为 $F(x) - G(x)$ 不单调，有可能出现 $0,1,0,1$ 反复横跳的情况。

其实与其考虑 $F(x) - G(x)$，不如先考虑 $f(x) - g(x)$，它是斜率 $\ge 0$ 的直线。我们发现：

- $f(x) - g(x) \in (-1,0], F(x) - G(x) \in \{-1,0\}$；
- $f(x) - g(x) \in (0,1], F(x) - G(x) \in \{0,1\}$。

而满足 $f(x) - g(x) \in (-1,0]$ 和 $f(x) - g(x) \in (0,1]$ 的区间可以二分得到。接下来以第一种情况为例（第二种情况是对称的），考虑如何计算。

现在问题仍然是求 $\sum\limits_{x=l}^r [F(x) - G(x) = 0]$，但是 $F(x) - G(x) \in \{-1,0\}$。考虑计算 $\sum\limits_{x=l}^r F(x) - G(x)$，设结果为 $k$，发现 $\sum\limits_{x=l}^r [F(x) - G(x) = -1] = -k$，这样 $\sum\limits_{x=l}^r [F(x) - G(x) = 0] = r - l + 1 + k$，**就把区间里求多少数的值等于某个数的问题转化成了区间求和**。

接下来问题变成了求 $\sum\limits_{x=l}^r F(x) - G(x) = (\sum\limits_{x=l}^r A_X + \left\lfloor\frac{i}{B_X}\right\rfloor) - (\sum\limits_{x=l}^r A_Y + \left\lfloor\frac{i}{B_Y}\right\rfloor)$。这个就爱怎么做怎么做了，~~虽然你闲得蛋疼也可以类欧（~~

[code](https://atcoder.jp/contests/arc123/submissions/40996641)

---

## 作者：BreakPlus (赞：1)

题意稍微转化一下就是求 $n$ 的个数，满足 $\lfloor\dfrac{n}{B_X}\rfloor - \lfloor\dfrac{n}{B_Y}\rfloor = A_Y - A_X$，不妨设**后者**为 $w$。

先判掉一些 corner case。

+ 当 $B_X = B_Y$ 时，答案为 $n \times \left[ A_X = B_X \right]$；
+ 当 $w$ 与 $(B_X - B_Y)$ 异号，答案为 $0$。
------
不妨设 $A_X \ge A_Y$，$B_X > B_Y$。

假设有一个很大的桶数组 $T$，给每个下标为 $B_Y$ 倍数的地方打个 $+1$ 的标记，每个下标为 $B_X$ 的倍数的地方打一个 $-1$ 的标记。我们将下标 $0$ 也纳入考虑范围。

令 $P_i = \sum \limits_{k=0}^i T_k$，那么一个 $n$ 满足条件相当于 $P_i = w$。

发现若一个有标记处 $x$ 满足 $P_x = w$，那么令最小的严格大于 $x$ 的有标记处 $x'$，则 $n \in [x, x')$ 均满足 $P_n = w$。

----
若仅考虑所有被打上 $+1$ 标记的位置，其 $P$ 的值严格不减；$-1$ 标记处同理。

因此对 $+1$ 标记和 $-1$ 标记分开计算。

如对于所有 $+1$ 标记，二分出满足 $P_x = w$ 的地方（必然构成一个连续段），对于每一个满足的 $x'$，找到其对应的下一个标记 $x'$（注意，既有可能是 $+1$ 标记，又有可能是 $-1$ 标记），则对答案的贡献就是 $\sum x' - \sum x$。

对于 $-1$ 标记类似。

----

发现会有算重的地方：若一个标记处满足条件，既有 $+1$ 标记，又有 $-1$ 标记，则这样的标记最多只有一个（可能是 $0$），那以它开始的一段满足条件的区间被算重。特判一下即可。

最后对于 $w=0$ 的情况，答案要减 $1$（算入了 $n=0$）。

```cpp
ll n,ax,bx,ay,by;
ll calc(ll N){
	return N/by - N/bx;
}
ll getsum(ll l,ll r,ll d){
	ll xs = (r - l) / d + 1;
	return (l + r) * xs / 2;
}
void solve(){
	n=read(), ax=read(), bx=read(), ay=read(), by=read();
	if(ax < ay) swap(ax, ay), swap(bx, by);
	else if(ax == ay && bx < by) swap(bx, by);
	ll w = ax - ay;
	if(ax == ay && bx == by){
		printf("%lld\n", n);
		return;
	}
	if(bx == by && ax != ay){
		puts("0");
		return;
	}
	if(bx < by && w > 0) {
		puts("0");
		return;
	}
	ll ans = 0;


	ll l=0, r=n/by, L=r+1, R=0;
	while(l <= r){
		ll mid = (l+r) >> 1;
		if(calc(mid * by) >= w){
			if(calc(mid * by) == w) L = mid;
			r = mid - 1;
		}else l = mid + 1;
	}
	l=0, r=n/by;
	while(l <= r){
		ll mid = (l+r) >> 1;
		if(calc(mid * by) <= w){
			if(calc(mid * by) == w) R = mid;
			l = mid + 1;
		}else r = mid - 1;
	}
	if(L <= R){
		ans -= getsum(L * by, R * by, by);
		ll st = (L * by + bx) / bx * bx;
		ll ed = (R * by) / bx * bx;
		ans += getsum(st, ed, bx);
		ans += min({n+1, (R + 1) * by, (R * by + bx) / bx * bx});
	}


	l=0, r=n/bx, L=r+1, R=0;
	while(l <= r){
		ll mid = (l+r) >> 1;
		if(calc(mid * bx) >= w){
			if(calc(mid * bx) == w) L = mid;
			r = mid - 1;
		}else l = mid + 1;
	}
	l=0, r=n/bx;
	while(l <= r){
		ll mid = (l+r) >> 1;
		if(calc(mid * bx) <= w){
			if(calc(mid * bx) == w) R = mid;
			l = mid + 1;
		}else r = mid - 1;
	}
	if(L <= R){
		ans -= getsum(L * bx, R * bx, bx);
		ll st = (L * bx + by) / by * by;
		ll ed = (R * bx) / by * by;
		ans += getsum(st, ed, by);
		ans += min(n+1, (R * bx + by) / by * by);
	}


	ll p = bx * by / __gcd(bx, by);
	l=0, r=n/p; ll pt = -1;
	while(l <= r){
		ll mid = (l+r) >> 1;
		if(calc(mid * p) <= w){
			if(calc(mid * p) == w) pt = mid;
			l = mid + 1;
		}else r = mid - 1;
	}
	if(pt != -1){
		ll L = pt * p, R = min(n+1, L + by);
		ans -= R-L;
	}
	printf("%lld\n", ans - (w==0));
}
```

---

## 作者：shiruoyu114514 (赞：0)

我们令 $f(i)$ 为 $A$ 在第 $i$ 天的等级，$g(i)$ 为 $B$ 的。

首先考虑一下没有天数上限怎么做。

我们考虑直接计算 $\sum \limits_{L} \sum \limits_i [f(i)=L][g(i)=L]$。

可以发现其对应到数轴上就分别是一个长度为 $B_x$ 与 $B_y$ 的区间。这两个区间一个每次会移动 $B_x$ 位一个会移动 $B_y$ 位。不妨设 $B_x < B_y$，并且令 $\Delta = B_y-B_x$。则 $x$ 到 $y$ 的移动会经历这四个阶段（令两个区间分别为 $[l_x,r_x]$ 与 $[l_y,r_y]$），每个阶段中的每次移动都会给答案产生贡献：

1. $r_x<l_y$：此时贡献为 $0$。
2. $l_x<l_y \le r_x$：可以算出初始的贡献值 $s$，并且每次都会令 $s \leftarrow s+\Delta$。
3. $l_y \le l_x \le r_x \le r_y$：每次的贡献值为 $B_x$
4. $l_x \le r_y <r_x$：可以算出初始的贡献值 $s$，并且每次都会令 $s \leftarrow s-\Delta$。
5. $r_y<l_x$：贡献为 $0$。

需要注意的是，这五个阶段可能并不都出现。当没有天数上限的时候，直接对着算即可。

现在有了天数上限，则可以算出 $n$ 是在哪个阶段的哪个点，单独处理那一个等级即可。

时间复杂度 $O(T)$。

---

## 作者：APJifengc (赞：0)

题意无非就是要你求 $i \in [1, n]$，有多少满足 $a + \lfloor\frac{i}{b} \rfloor = c + \lfloor\frac{i}{d}\rfloor$。

首先移项，得 $a - c = \lfloor\frac{i}{d}\rfloor - \lfloor\frac{i}{b} \rfloor$。

底函数没啥好分析的办法，就直接拆成不等式。

我们有 $\alpha - 1 < \lfloor\alpha\rfloor \le \alpha$，于是上面的式子推一推就可以得到 $a - c = \lfloor\frac{i}{d}\rfloor - \lfloor\frac{i}{b} \rfloor \in (\frac{i}{d} - \frac{i}{b} - 1, \frac{i}{d} - \frac{i}{b} + 1)$。

此时我们发现一件事情，就是这个区间是很紧的，这个区间内最多有两个整数。因此，如果我们找出 $i$ 的一个可能的区间，那么应当会更好统计答案。

再变换一下，把不等号反过来，就能得到 $\frac{i}{d} - \frac{i}{b} \in (a-c-1, a-c+1), i \in (\frac{bd(a-c-1)}{b-d}, \frac{bd(a-c+1)}{b - d})$。

此时考虑将 $i$ 分为若干个区间来考虑。假如 $\frac{i}{d} - \frac{i}{b} \in (a-c, a-c+1)$ 时，那么原不等式中满足条件的整数有 $a-c, a-c+1$ 两种。同理，$\frac{i}{d} - \frac{i}{b} \in (a-c - 1, a-c)$ 中有 $a-c-1, a-c$，$\frac{i}{d} - \frac{i}{b} = a-c$ 中有 $a-c$。

最后一个情况先判掉。那么我们可以确定每个区间中仅有两个可能的整数，而我们发现，$\lfloor\frac{i}{a}\rfloor$ 这个函数是容易计算前缀和的。那么我们就可以计算出这个区间的和，然后解方程即可得知有多少个 $a-c$，这便是我们要找的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, a, b, c, d;
long long sum(int n, int a) {
    if (n < 0) return 0;
    int b = n / a - 1, c = n % a + 1;
    return 1ll * a * b * (b + 1) / 2 + 1ll * c * (b + 1);
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
        if (b == d) {
            printf("%d\n", a == c ? n : 0);
            continue;
        }
        if (1ll * (a - c) * (b - d) < 0) {
            printf("0\n");
            continue;
        }
        if (b < d) swap(a, c), swap(b, d);
        int ans = 0;
        // case 1: i(1/d-1/b) = a-c
        if (1ll * b * d * (a - c) % (b - d) == 0) {
            if (1ll * b * d * (a - c) / (b - d) <= n
                && 1ll * b * d * (a - c) / (b - d) >= 1)
                ans++;
        }
        // case 2: i(1/d-1/b) \in (a-c, a-c+1)
        {
            long long l = min(1ll * b * d * (a - c) / (b - d) + 1, n + 1ll);
            long long r = min((1ll * b * d * (a - c + 1) - 1) / (b - d), n + 0ll);
            int m = r - l + 1;
            int s = sum(r, d) - sum(l - 1, d) - sum(r, b) + sum(l - 1, b) - 1ll * m * (a - c);
            ans += m - s;
        }
        // case 3: i(1/d-1/b) \in (a-c-1, a-c)
        {
            long long l = min(max(1ll * b * d * (a - c - 1) / (b - d) + 1, 1ll), n + 1ll);
            long long r = min(max((1ll * b * d * (a - c) - 1) / (b - d), 0ll), n + 0ll);
            int m = r - l + 1;
            int s = sum(r, d) - sum(l - 1, d) - sum(r, b) + sum(l - 1, b) - 1ll * m * (a - c - 1);
            ans += s;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

