# [Algo Beat Contest 001 F] Foolish Math Homework

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| $\text{F - Foolish Math Homework}$  | $550$ |    [joe_zxq](https://www.luogu.com.cn/user/623577)    |      [fanchuanyu](https://www.luogu.com.cn/user/706256)      | [joe_zxq](https://www.luogu.com.cn/user/623577) |      [orchardist](https://www.luogu.com.cn/user/347582)      | [Link](https://www.luogu.com.cn/article/6ib0zaqc) by [fanchuanyu](https://www.luogu.com.cn/user/706256) |

## 题目描述

小 F 的数学老师 H 老师给小 F 留了一道数学作业。

> 给定 $a,b,c,d$ 的值，求有多少正整数对 $(x,y)$ 满足以下所有条件。这里，$\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公约数。
> - $x \le y$。
> - $a \le x \le b$。
> - $c \le y \le d$。
> - $y-x=\gcd(x,y)$。

小 F 觉得这个作业实在是太过愚蠢了，信心满满地写满了暴力，结果发现 $a,b,c,d \le 10^{12}$。你是**作业帮**，你需要帮小 F 完成作业。

## 说明/提示

#### 样例解释 #1

满足条件的 $(x,y)$ 如下所示：

- $(2,3)$
- $(2,4)$
- $(3,4)$
- $(3,6)$
- $(4,5)$
- $(4,6)$
- $(5,6)$

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le a \le b \le 10^{12}$，$1 \le c \le d \le 10^{12}$。

## 样例 #1

### 输入

```
2 5 3 7```

### 输出

```
7```

## 样例 #2

### 输入

```
1 100 1 100```

### 输出

```
382```

## 样例 #3

### 输入

```
114 514 191 9810```

### 输出

```
2433```

## 样例 #4

### 输入

```
21899 314099 61699 104699```

### 输出

```
493292```

# 题解

## 作者：__O_v_O__ (赞：5)

首先，我们可以使用差分，把问题转化成 $1\le x\le b$，$1\le y\le d$ 类型的问题。

考虑设 $\gcd(x,y)=g$，则 $x$ 和 $y$ 都可以表示成 $p\times g$ 和 $q\times g$ 的形式（其中 $p$ 与 $q$ 互质）。

原来的条件可以变为：$q-p=1$。显然，此时 $p$ 与 $q$ 一定互质。也就是说，对于一个 $g$，所有的 $x=p\times g,y=(p+1)\times g$ 都满足条件。

于是有了暴力做法：枚举 $g$，答案加上 $\min(\lfloor\frac{b}{g}\rfloor,\lfloor\frac{d}{g}\rfloor-1)$。

对于有下取整的求和，通常使用数论分块优化。这样，此题就在 $O(\sqrt{n})$ 的复杂度内解决。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
int sl(int x,int y){
	int an=0;
	for(int l=1,r;l<=min(x,y);l=r+1){
		r=min(x/(x/l),y/(y/l));
		an+=(r-l+1)*min(x/l,y/l-1);
	}
	return an;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>a>>b>>c>>d;
	cout<<sl(b,d)-sl(a-1,d)-sl(b,c-1)+sl(a-1,c-1);
	return 0;
}
```

---

## 作者：__liujy (赞：4)

这道题可以用差分还有整除分块写。

先说说在哪里差分，我们可以将这个过程抽象的转为求二维前缀和某一区间的和，这样就可以写出```s[b][d]-s[a-1][d]-s[b][c-1]+s[a-1][c-1]```了，接下来就只需要考虑怎么计算值了。

我们发现对于**满足所有条件**两个整数 $x$ 和 $y$，都可以表示成 $x=p\times \gcd(x,y)，y=q\times \gcd(x,y)$，因此 $p$ 和 $q$ 互质，如果它们不互质，那么就会有新的最大公因数。

因为 $y\ge x$，所以上述条件可以转为 $q-p=1$，因此 $q=p+1$，所以任意一个 $p\times \gcd(x,y)$ 与 $(p+1)\times \gcd(x,y)$ 都满足条件。

因此枚举 $\gcd(x,y)$ 是解决方法。

但这样做依旧不能拿到满分，需要用整除分块优化。

下面给出主体代码。
```cpp
inline LL work(LL x,LL y)
{
	LL ans=0;
	for(LL l=1,r;l<=min(x,y);l=r+1)
	{
		r=min(x/(x/l),y/(y/l));
		ans+=(r-l+1)*min(x/l,y/l-1);
	}
	return ans;
}
```

---

## 作者：zyn_ (赞：2)

显然差分，不妨设 $a=c=1$。~~怎么现在还有出题人通过设左边界考差分的？~~ 以下设 $x,y$ 满足 $x\le n$ 且 $y\le m$。（这样字母 $d$ 用来表示最大公约数）

设 $\gcd(x,y)=d$，则 $d\mid x$ 且 $d\mid y$。设 $x=dx'$，其中 $x'\in\Z^+$，由题 $y=x+\gcd(x,y)=x+d=d(x'+1)$。此时 $\gcd(x,y)=\gcd(dx',d(x'+1))=\gcd(dx',d)=d$，已经合题。

还要求 $x=dx'\le n$ 且 $y=d(x'+1)\le m$，于是 $x'\le \frac{n}{d}$ 且 $x'\le\frac{m}{d}-1$，故有 $\min(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor-1)$ 个 $x'$。于是数对 $(x,y)$ 的个数为

$$
A=\sum_{d=1}^{\min\{n,m\}}\min(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor-1)
$$

整除分块即可。

什么？你说你不会整除分块？或者，你问我同时出现了 $\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor$ 怎么整除分块？那么让我们看看整除分块的本质。

对于一个正整数 $n$，所有 $\lfloor\frac{n}{d}\rfloor$（$d=1,2,\dots,n$）只有 $O(\sqrt{n})$ 种不同取值。这是因为 $d\le \sqrt n$ 时只有 $\sqrt n$ 个数，$d\gt \sqrt n$ 时 $\frac{n}{d}\lt \sqrt n$，从而只有 $\sqrt n$ 个值。

这样，对于正整数 $n$，可以找到 $O(\sqrt n)$ 个分割点，使相邻两个分割点之间的 $\lfloor\frac{n}{d}\rfloor$ 值相同。现在有了两个正整数 $n,m$，那么就有 $O(\sqrt n+\sqrt m)$ 个分割点，相邻两个分割点之间的 $\lfloor\frac{n}{d}\rfloor$ 与 $\lfloor\frac{m}{d}\rfloor$ 的值**均**相同。这不就行了？算出所有分割点并排序即可。

其实有不用排序的写法，然而我直接用了 `sort` 并喜提[最劣解](https://www.luogu.com.cn/record/201860895)，险些超时……

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,c,d,s[10000009],t;
ll calc(ll x,ll y){
	if(x==0||y==0)return 0;
	t=0;
	for(ll l=1,r;l<=x;l=r+1)s[++t]=r=x/(x/l);
	for(ll l=1,r;l<=y;l=r+1)s[++t]=r=y/(y/l);
	sort(s+1,s+t+1);
	ll r=0,z;
	for(int i=1;i<=t&&s[i]<y;++i)r+=(s[i]-s[i-1])*min(x/s[i],y/s[i]-1);
	return r;
}
int main(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	printf("%lld\n",calc(b,d)-calc(a-1,d)-calc(b,c-1)+calc(a-1,c-1));
	return 0;
}
```

---

## 作者：x11223344 (赞：2)

若设 $\operatorname{f}(n,m)=\sum_{i=1}^{n}\sum_{j=1}^{m}[j-i=\gcd(i,j)]$，则答案为 $\operatorname{f}(b,d) - \operatorname{f}(a-1,d)-\operatorname{f}(b,c-1)+\operatorname{f}(a-1,c-1)$。  
又有
$$
\begin{aligned}\operatorname{f}(n,m)&=\sum_{d=1}^{\min(n,m)}\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=d][j-i=d]\\
&=\sum_{d=1}^{\min(n,m)}\sum_{i=1}^{\lfloor\frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}[\gcd(i,j)=1][j-i=1]\\
&=\sum_{d=1}^{\min(n,m)}\min(\lfloor\frac{n}{d}\rfloor, \lfloor\frac{m}{d}\rfloor-1)\end{aligned}
$$
但是，此时还无法通过此题，需要使用整除分块优化。

---

## 作者：冷却心 (赞：2)

题意较为简洁，在此不再赘述。

我们设满足条件的某一对 $x,y$ 的最大公约数是 $g$，则有 $k_1,k_2$ 使得 $x=k_1g,y=k_2g$，并且需满足 $k_1,k_2$ 互质，又因为 $y-x=g$，则 $k_2-k_1=1$，显然任意满足这个条件的 $k_1,k_2$ 都是互质的，因为是相邻的正整数。

考虑一个暴力，我们枚举 $g$，然后统计满足条件的 $k_1$ 个数，因为 $k_1$ 确定的时候 $k_2$ 也确定了。我们有：

$$
\left\{\begin{aligned}
A\leq x&=k_1 g\leq B,\\
C\leq y&=(k_1+1) g\leq D.\\
\end{aligned}\right.
$$

$$
\max\left(\left\lceil\frac{A}{g}\right\rceil,\left\lceil\frac{C}{g}\right\rceil - 1\right)\leq k_1 \leq \min\left(\left\lfloor\frac{B}{g}\right\rfloor,\left\lfloor\frac{D}{g}\right\rfloor - 1\right).
$$

然后就得出了满足条件的 $k_1$ 个数，注意下界可能大于上界，要对 $0$ 取 $\max$。

也就是说，我们的答案为：

$$
\text{Answer}=\sum_{g=1}^{\max(A,B,C,D)}\max\left(0,\min\left(\left\lfloor\frac{B}{g}\right\rfloor,\left\lfloor\frac{D}{g}\right\rfloor - 1\right) -\max\left(\left\lceil\frac{A}{g}\right\rceil,\left\lceil\frac{C}{g}\right\rceil - 1\right) + 1\right).
$$

*这里枚举 $g$ 的上界事实上可以再进行缩小，但是无关紧要。*

我们观察到这是一个下取整和上取整的求和式，考虑直接套一个四维的数论分块做即可。代码很短。时间复杂度 $O(\sqrt{\max(A,B,C,D)})$。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL A, B, C, D;
LL Ceil(LL x, LL y) { return x / y + (x % y > 0); }
LL Calc(LL x) {
	return min(B / x, D / x - 1) - max(Ceil(A, x), Ceil(C, x) - 1) + 1;
} // 计算 g = x 时满足条件的 k_1 个数。
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> A >> B >> C >> D; LL Ans = 0;
	for (LL l = 1, r; l <= max({A, B, C, D}); l = r + 1) {
		r = max({A, B, C, D});
		if (l == A || l == C) r = l;
		if (l < A) r = min(r, (A - 1) / ((A - 1) / l));
		if (l < C) r = min(r, (C - 1) / ((C - 1) / l));
		if (l <= B) r = min(r, B / (B / l));
		if (l <= D) r = min(r, D / (D / l));
        // 以上是四维的数论分块。
		Ans += (r - l + 1) * max(0ll, Calc(l));
	} cout << Ans << "\n";
	return 0;
}
```

---

## 作者：joe_zxq (赞：2)

原作者是 fcy。

---

设 $ans$ 为给定值对应的答案，根据简单容斥得：
$$
ans(a,b,c,d)=ans(1,b,1,d)-ans(1,a-1,1,d)-ans(1,b,1,c-1)+ans(1,c-1,1,d-1)
$$
则问题转化为 $1\le x \le n$ 且 $1 \le y \le m$，使得
$$
y-x=\gcd(x,y)
$$
同时除以 $\gcd(x,y)$ 得
$$
\frac{y}{\gcd(x,y)}-\frac{x}{\gcd(x,y)}=1
$$
显然，$\frac{x}{\gcd(x,y)}$ 与 $\frac{y}{\gcd(x,y)}$ 为连续自然数。
则
$$
\sum_{x=1}^n\sum_{y=1}^{m}[y-x=gcd(x,y)]=\sum_{g=1}^{\min(n,m)}\min(\frac{n}{g},\frac{m}{g}-1)
$$
考虑数论分块，枚举区间 $[l,r]$ 使得 $\lfloor\frac{n}{l}\rfloor=\lfloor\frac{n}{r}\rfloor$ 且 $\lfloor\frac{m}{l}\rfloor=\lfloor\frac{m}{r}\rfloor$。则它对答案贡献为 $\min(\lfloor\frac{m}{l}\rfloor-1,\lfloor\frac{n}{l}\rfloor)$。

二维数论分块后求和即可，$\sum_{g=1}^{\min(n,m)}\min(\frac{n}{g},\frac{m}{g}-1)$ 即为所求。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll calc(ll n, ll m) {
	ll t = min(n, m);
	ll l = 1, r, res = 0;
	while (l <= t) {
		r = min({n / (n / l), m / (m / l), t});
		ll a1 = n / l, a2 = m / l;
		res += min(a1, a2 - 1) * (r - l + 1);
		l = r + 1;
	}
	return res;
}

int main() {
	ll l1, r1, l2, r2;
	cin >> l1 >> r1 >> l2 >> r2;
	cout << calc(l1 - 1, l2 - 1) + calc(r1, r2) - calc(l1 - 1, r2) - calc(r1, l2 - 1);
	return 0;
}
```

---

## 作者：Polarisx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11684)。

## 思路

$y-x=\gcd(x,y)$ 相当于 $y-x=\gcd(x,y-x)$，即 $y-x\mid x$，那么答案就是

$$
\begin{aligned}
& \ \ \ \ \ \sum_{x=a}^b \sum_{u\mid x} [c\le u+x\le d]\\
&=\sum_{u=1}^b \sum_{x=\lceil a/u \rceil}^{b/u}[c\le u(1+x)\le d]\\
&=\sum_{u=1}^b \sum_{x=\lceil a/u \rceil}^{b/u}[c/u-1\le x\le d/u-1]
\end{aligned}
$$

对 $a,b,c,d$ 数论分块即可。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll a,b,c,d,ans,m;
inline ll up(ll n,ll r){
	ll k=(n+r-1)/r;
	return (n+k-1)/k;
}
inline ll down(ll n,ll l){
	return n/(n/l);
}

int main(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	vector<ll>seq;
	m=max(a,c);
	for(ll r=m,l;r>=1;r=l-1){
		l=max(up(a,r),up(c,r));
		seq.emplace_back(r);
	}
	m=min(b,d);
	for(ll l=1,r=0;l<=m;l=r+1){
		seq.emplace_back(r);
		r=min(down(b,l),down(d,l));
	}
	seq.emplace_back(m);
	sort(seq.begin(),seq.end());
	for(int i=1;i<seq.size();i++){
		ll l=seq[i-1]+1;
		ll k1=min(b/l,d/l-1);
		ll k2=max(a/l+(a%l!=0),c/l+(c%l!=0)-1);
		ans+=(seq[i]-seq[i-1])*max(k1-k2+1,0ll);
	}
	printf("%lld",ans);

	system("pause"); 
	return 0;
}
```

---

## 作者：Loyal_Soldier (赞：1)

### 思路

设 $\text{calc}(a, b)$ 表示满足 $x\le y, 1\le x\le a, 1\le y\le b, y - x = \gcd(x, y)$ 限制的正整数数对的数量，根据容斥原理可得最终答案为 $\text{calc}(b, d) - \text{calc}(a - 1, d) - \text{calc}(b, c - 1) + \text{calc}(a - 1, c - 1)$。

我们发现，满足限制的数对 $(x, y)$ 都满足 $x = p\times \gcd(x, y), y = q\times \gcd(x, y)$，并且 $q - p = 1$。因此，对于所有形如 $(p\times \gcd(x, y), (p + 1)\times \gcd(x, y))$ 的数对都满足条件。

那么，只需要枚举 $\gcd(x, y)$ 就行了，设当前枚举的 $\gcd(x, y)$ 为 $g$，则答案增加 $\min(\lfloor \frac{a}{g}\rfloor,  \lfloor \frac{b}{g}\rfloor - 1)$。但是直接枚举会超时，需要整除分块优化。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int a, b, c, d; 
int calc(int x, int y)
{
	int ans = 0;
	for(int l = 1, r;l <= min(x, y);l = r + 1)
	{
		r = min(x / (x / l), y / (y / l));
		ans += (r - l + 1) * min(x / l, y / l - 1);
	}//整除分块
	return ans;
}
signed main()
{
	cin >> a >> b >> c >> d;
	cout << calc(b, d) - calc(a - 1, d) - calc(b, c - 1) + calc(a - 1, c - 1);//容斥
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

本题解称原题中的 $a,b,c,d$ 为 $l_1,r_1,l_2,r_2$。

设 $cal_{r_1,r_2}$ 表示 $x\in[1,r_1],y\in[1,r_2]$ 部分的答案，则容斥可得最终答案为 $cal_{r_1, r_2} - cal_{l_1 - 1, r_2} - cal_{r_1, l_2 - 1} + cal_{l_1 - 1, l_2 - 1}$。问题转化为如何求 $cal$。

设 $(x,y)=g$，则 $x=ga,y=gb,(a,b)=1$。进而 $y-x=gb-ga=g(b-a)$。令 $g(b-a)=g$ 得 $b-a=1$。注意到此时 $(a,b)=1$ 恒成立，故 $(x,y)$ 符合题意的充要条件为 $\exist x=kg,y=(k+1)g$。进而得到对于一个 $g$，贡献为 $\min(\lfloor r_1/g\rfloor,\lfloor r_2/g\rfloor-1)$。数论分块求和，时间复杂度为 $O(\sqrt r)$。

```cpp
ll l1, r1, l2, r2;

ll cal(ll r1, ll r2) {
	ll ret = 0;

	for (ll l = 1, r; l <= r1 and l <= r2; l = r + 1) {
		r = min(r1 / (r1 / l), r2 / (r2 / l));
		ret += (r - l + 1) * min(r1 / l, r2 / l - 1);
	}

	return ret;
}

int main() {
	cin >> l1 >> r1 >> l2 >> r2;
	cout << cal(r1, r2) - cal(l1 - 1, r2) - cal(r1, l2 - 1) + cal(l1 - 1, l2 - 1);
}
```

代码宏定义在我个人空间自取。

---

## 作者：Redshift_Shine (赞：0)

确实挺 Foolish 的。

首先有一个经典结论：

对于任何正整数 $x,k$，使得 $\lfloor\frac{k}{y}\rfloor<\lfloor\frac{k}{x}\rfloor$ 的最小的 $y$ 为 $\lfloor\frac{k}{\lfloor\frac{k}{x}\rfloor}\rfloor+1$。

然后是一个对于这一题的结论：

对于正整数 $x,y$ 满足 $x<y$，$y-x=\gcd(x,y)$ 当且仅当存在正整数 $v$ 满足 $x=v\times \gcd(x,y)$ 且 $y=x+\gcd(x,y)$。读者自证不难。

于是一个显然的思路就出现了。枚举 $v$ 的值，使用除法判断 $x$ 和 $y$ 分别可取的 $\gcd(x,y)$ 区间求交即可。但是范围在 $10^{12}$，显然不够。

考虑整除分块，计算会让某个区间边界发生改变的最小 $v$ 值，做乘法加速即可。

时间复杂度 $O(\sqrt{a}+\sqrt{b}+\sqrt{c}+\sqrt{d})$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
using ll = long long;
ll a, b, c, d, res;
const ll linf = 1e18;
void run()
{
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	a--, c--;
	for (ll i = 1, nxt = 0; i <= max({a, b, c, d});)
	{
		nxt = min({a < i ? linf : a / (a / i) + 1, b < i ? linf : b / (b / i) + 1, c < i + 1 ? linf : c / (c / (i + 1)),
				   d < i + 1 ? linf : d / (d / (i + 1))});
		// printf("%lld %lld %lld\n", i, res, nxt);
		res += (nxt - i) * max(0ll, min(b / i, d / (i + 1)) - max(a / i, c / (i + 1)));
		i = nxt;
	}

	printf("%lld\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```
**但是你先别急！**
我同时把这个问题丢给了 DeepSeek R1，他在长达 $557$ 秒的思考后一发入魂，直接写出了比我的程序快 $3$ 倍的代码！接下来是他写的题解：
```c++
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int K = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    
    ll ans = 0;
    
    // Step 1: Process small m (1 <= m <= K)
    for (ll m = 1; m <= K; ++m) {
        if (m > b) break;
        ll ceil_am = (a + m - 1) / m;
        ll ceil_cm1 = (c + m) / (m + 1);
        ll lower_g = max(ceil_am, ceil_cm1);
        ll floor_bm = b / m;
        ll floor_dm1 = d / (m + 1);
        ll upper_g = min(floor_bm, floor_dm1);
        if (upper_g >= lower_g) {
            ans += upper_g - lower_g + 1;
        }
    }
    
    // Step 2: Process large m (m > K) by iterating g0
    ll max_g0 = b / (K + 1);
    for (ll g0 = 1; g0 <= max_g0; ++g0) {
        ll ceil_ag0 = (a + g0 - 1) / g0;
        ll ceil_cg0_minus1 = (c - 1) / g0;
        ll m_low = max({ceil_ag0, ceil_cg0_minus1, K + 1LL});
        ll floor_bg0 = b / g0;
        ll floor_dg0_minus1 = (d / g0) - 1;
        ll m_high = min(floor_bg0, floor_dg0_minus1);
        if (m_high >= m_low) {
            ans += m_high - m_low + 1;
        }
    }
    
    cout << ans << '\n';
    
    return 0;
}
```
1. **问题分析**：题目要求找到满足特定条件的正整数对 $(x, y)$，其中 $y - x$ 等于它们的最大公约数，且 $x$ 和 $y$ 分别在给定区间内。
2. **数学推导**：将 $x$ 和 $y$ 表示为 $x = gm$ 和 $y = g(m+1)$，其中 $g$ 是它们的最大公约数。这样问题转化为找到满足条件的 $(g, m)$ 对。
3. **分块处理**：
    - **小 $m$ 处理**：直接枚举 $m$ 从 $1$ 到 $K$（取 $10^6$），计算每个 $m$ 对应的 $g$ 的范围。
    - **大 $m$ 处理**：枚举可能的 $g$ 值，计算对应的 $m$ 范围，避免直接枚举大 $m$。
4. **优化**：
    - **快速计算上下界**：利用整数除法和取模运算快速计算上下界。
    - **提前终止**：当 $m$ 超过 $b$ 时提前终止循环，减少不必要的计算。

该方法通过分块处理，有效减少了计算量，确保在大数据范围内高效运行。

---

## 作者：Genius_Star (赞：0)

### 思路：

根据辗转相除法，若 $y - x = \gcd(x, y)$，则 $x \bmod (y - x) = 0$。

那么 $(x, y)$ 满足条件当且仅当 $x \bmod (y - x) = 0$；此时设 $x \le a, y \le b$。


那么若：

$$x = k(y - x)$$

$$y = \frac{(k +1)x}{k} \le b$$

则只要 $k$ 是 $x$ 的约数就必然会存在一个 $y$，但是要使得 $y \le B$，故式子如下：


$$\sum_{x = 1}^a \sum_{d | x} [\frac{(d + 1)x}{d} \le b]$$

考虑枚举这个约数，令 $x = id$，会发现分母被消掉了，就很好：

$$\sum_{d = 1}^a \sum_{x = 1}^{\lfloor \frac{a}{d} \rfloor} [x(d+1) \le b]$$

后面显然可以通过除法计算：

$$\sum_{d = 1}^a \min(\lfloor \frac{b}{(d + 1)} \rfloor, \lfloor \frac{a}{d} \rfloor)$$

然后数论分块即可。

时间复杂度为 $O(\sqrt{W})$。

---

