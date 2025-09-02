# [ABC193E] Oversleeping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc193/tasks/abc193_e

街 $ A $ と街 $ B $ の間を往復する電車があります。 電車は時刻 $ 0 $ に街 $ A $ を出発した後、

- $ X $ 秒かけて街 $ B $ に移動
- 街 $ B $ で $ Y $ 秒停車
- $ X $ 秒かけて街 $ A $ に移動
- 街 $ A $ で $ Y $ 秒停車

を繰り返します。  
 より厳密には、これらは半開区間として扱います。すなわち、$ n\ =\ 0,\ 1,\ 2,\ \dots $ について、

- $ (2X\ +\ 2Y)n\ <\ =\ t\ <\ (2X\ +\ 2Y)n\ +\ X $ を満たす時刻 $ t $ には電車は街 $ B $ に移動している
- $ (2X\ +\ 2Y)n\ +\ X\ <\ =\ t\ <\ (2X\ +\ 2Y)n\ +\ X\ +\ Y $ を満たす時刻 $ t $ には電車は街 $ B $ で停車している
- $ (2X\ +\ 2Y)n\ +\ X\ +\ Y\ <\ =\ t\ <\ (2X\ +\ 2Y)n\ +\ 2X\ +\ Y $ を満たす時刻 $ t $ には電車は街 $ A $ に移動している
- $ (2X\ +\ 2Y)n\ +\ 2X\ +\ Y\ <\ =\ t\ <\ (2X\ +\ 2Y)(n\ +\ 1) $ を満たす時刻 $ t $ には電車は街 $ A $ で停車している

が満たされます。

高橋くんは電車に乗って時刻 $ 0 $ に街 $ A $ を出発し、街 $ B $ で電車を降りようと思っています。 高橋くんは時刻 $ 0 $ に街 $ A $ を出発した後、

- $ P $ 秒間眠っている
- $ Q $ 秒間起きている

を繰り返します。  
 これらも半開区間として扱います。すなわち、$ n\ =\ 0,\ 1,\ 2,\ \dots $ について、

- $ (P\ +\ Q)n\ <\ =\ t\ <\ (P\ +\ Q)n\ +\ P $ を満たす時刻 $ t $ には高橋くんは眠っている
- $ (P\ +\ Q)n\ +\ P\ <\ =\ t\ <\ (P\ +\ Q)(n\ +\ 1) $ を満たす時刻 $ t $ には高橋くんは起きている

が満たされます。

街 $ B $ に電車が停車しており、かつ、高橋くんが起きていれば高橋くんは街 $ B $ で電車を降りることができます。  
 高橋くんが街 $ B $ で電車を降りることができるか判定し、できる場合は、最短でいつになるか求めてください。  
 なお、この値はこの問題の制約下で整数になることが証明できます。

$ T $ 個のケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =\ T\ <\ =\ 10 $
- $ 1\ <\ = X\ <\ =\ 10^9 $
- $ 1\ <\ = Y\ <\ =\ 500 $
- $ 1\ <\ = P\ <\ =\ 10^9 $
- $ 1\ <\ = Q\ <\ =\ 500 $

### Sample Explanation 1

$ [a,\ b) $ で区間 $ a\ <\ =\ t\ <\ b $ を表すことにします。 $ 1 $ 個目のケースでは、電車が街 $ B $ で停車している時刻は $ [5,\ 7),\ [19,\ 21),\ [33,\ 35),\ \dots $ 、 高橋くんが起きている時刻は $ [7,\ 13),\ [20,\ 26),\ [33,\ 39),\ \dots $ なので、時刻 $ 20 $ に初めて街 $ B $ で電車を降りることが出来ます。

## 样例 #1

### 输入

```
3
5 2 7 6
1 1 3 1
999999999 1 1000000000 1```

### 输出

```
20
infinity
1000000000999999999```

# 题解

## 作者：dyj133446 (赞：11)

### 题目大意  
[题目传送门](https://www.luogu.com.cn/problem/AT_abc193_e)  
多组数据。一个人坐公交从 $A$ 站坐到 $B$ 站，公交车先用 $x$ 秒到 $B$ 站，然后在 $B$ 站停 $y$ 秒，再用 $x$ 秒到 $A$ 站，再在 $A$ 站停 $y$ 秒，如此循环往复。而这个人先睡眠 $p$ 秒，再醒来 $q$ 秒，如此循环往复。求这个人最早何时能在 $B$ 站下车，若永远不能，输出 $infinity$。
### 题目分析  
令公交车往返两地 $a$ 次，此人已循环过程 $b$ 次，公交车停在 $B$ 地 $m$ 秒，此人醒来 $n$ 秒下车，可得等式：  
$2a(x+y)+x+m=b(p+q)+p+n$  
经整理得：  
$2a(x+y)+(-b)(p+q)=(p+n)-(x+m)$  
于是我们想到**扩欧**。  
先解方程 $2a(x+y)+(-b)(p+q)=\gcd(2(x+y),p+q)$  
令 $i=x+m,j=p+n$  
枚举 $i,j$，求出 $a$ 的最小正整数解，代入第一个式子求解，取最小值输出，时间复杂度 $O(yq+\log(\max(2(x+y),p+q))$。  
### AC代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag;
long long t,x,y,p,q,d,a,b,minn=0x7fffffffffffffff;
long long ans;
void Exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		d=a,x=1,y=0;
		return;
	}
	Exgcd(b,a%b,x,y);
	long long tx=x;
	x=y;
	y=tx-a/b*y;
}
int main()
{
	cin>>t;
	for(int t1=1;t1<=t;t1++)
	{
		cin>>x>>y>>p>>q;
		minn=0x7fffffffffffffff;
		flag=0;
		Exgcd(2*(x+y),p+q,a,b);
		for(long long i=x;i<x+y;i++)
		{
			for(long long j=p;j<p+q;j++)
			{
				if((j-i)%d!=0)continue;
				flag=1;
				long long k=(j-i)/d;
				long long aa=a*k;
				aa=(aa%((p+q)/d)+((p+q)/d))%((p+q)/d);
				minn=min(minn,aa*2*(x+y)+i);
			}
		}
		if(!flag)cout<<"infinity";
		else cout<<minn;
		cout<<'\n';
	}
	return 0;
}
```  
## 别慌，还有优化  
我们可以直接枚举 $j-i$,算出最小的 $i$ 代入求最小值，时间复杂度 $O(y+q+\log(\max(2*(x+y),p+q))$。  
代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag;
long long t,x,p,d,a,b,minn=0x7fffffffffffffff;
int y,q;
long long ans;
void Exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		d=a,x=1,y=0;
		return;
	}
	Exgcd(b,a%b,x,y);
	long long tx=x;
	x=y;
	y=tx-a/b*y;
}
int main()
{
	cin>>t;
	for(int t1=1;t1<=t;t1++)
	{
		cin>>x>>y>>p>>q;
		minn=0x7fffffffffffffff;
		flag=0;
		Exgcd(2*(x+y),p+q,a,b);
		for(long long i=p-(x+y-1);i<=p+q-1-x;i++)
		{
			if(i%d!=0)continue;
			flag=1;
			long long k=i/d;
			long long aa=a*k;
			aa=(aa%((p+q)/d)+((p+q)/d))%((p+q)/d);
			if(i>=p-x)minn=min(minn,aa*2*(x+y)+x);
			else minn=min(minn,aa*2*(x+y)+x+(p-x-i));
		}
		if(!flag)cout<<"infinity";
		else cout<<minn;
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：Laoshan_PLUS (赞：3)

~~考场上死也想不来，烦死了，什么丿题~~

------------

### 题意

公交在 A 站和 B 站之间来回，最开始从 A 站出发，每次路程上用 $X$ 秒，在站点停 $Y$ 秒。而乔坤每次先睡眠 $P$ 秒，再醒来 $Q$ 秒，如此循环往复。求这个人最早何时能在 B 站下车，若永远不能，输出 `infinity`。

### 解析

设公交往返两站 $a$ 次，停在 B 站 $m$ 秒；乔坤已睡 $b$ 个回合，醒来 $n$ 秒，则：
$$
2a(X+Y)+X+m=b(P+Q)+P+n
$$

整理得：
$$
2a(X+Y)-b(P+Q)=(P+n)-(X+m)
$$

回忆起 **扩展欧几里得** 可以求解形如 $ax+by=\gcd(a,b)$ 的方程，所以我们可以先跑一遍扩欧解方程 $2a(X+Y)+(-b)(P+Q)=\gcd(2(X+Y),P+Q)$，解出 $a$ 和 $b$ 的值。

观察一下题面的数据范围，~~非常的智慧~~：
$$
\begin{aligned}
& 1\le T\le 10 \\
& 1\le X\le10^9 \\
& 1\le Y\le500 \\
& 1\le P\le10^9 \\
& 1\le Q\le500
\end{aligned}
$$

这让我们可以干什么呢？可以枚举！

因为公交每次停靠的时间不多于 $500$，乔坤每次醒来的时间不多于 $500$，这说明 $m,n\le500$，又因为 $T\le10$，所以我们可以直接枚举 $m,n$。令 $d=\gcd(2\times(X+Y),P+Q),t=\dfrac{P+Q}{d}$，我们要求解的答案就是：
$$
\min_{X\le i\le X+Y-1,\ P\le j\le P+Q-1,\ d\ \mid\  a\times(j-i)}\left\{2\left(\frac{a\times(j-i)}{d}\bmod t\right)\left(X+Y\right)+i\right\}
$$

~~突然发现 LaTeX 真高大上~~

### 实现

代码就呼之欲出了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int res = exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int x, y, p, q;
		cin >> x >> y >> p >> q;
		int ans = LONG_LONG_MAX, a, b;
		int d = exgcd(2 * (x + y), p + q, a, b);
		for (int i = x; i < x + y; i++)
			for (int j = p; j < p + q; j++)
				if ((j - i) % d == 0) {
					int k = a * (j - i) / d, t = (p + q) / d;
					k = (k % t + t) % t;
					ans = min(ans, (k << 1) * (x + y) + i);
				}
		if (ans == LONG_LONG_MAX) cout << "infinity\n";
		else cout << ans << '\n';
	}
	return 0;
}
```

------------

2024/1/3 upd. 修正部分 LaTeX 格式。

2024/3/10 upd. 修正部分内容。

---

## 作者：tabelog_AFO (赞：2)

[ABC193E] Oversleeping / [洛谷](https://www.luogu.com.cn/problem/AT_abc193_e) / [AtCoder](https://atcoder.jp/contests/abc193/tasks/abc193_e)

[更好的阅读体验](https://www.luogu.com.cn/blog/tabelog/solution-at-abc193-e)

#### 题目大意
多组数据。一个人坐公交从 A 站坐到 B 站，公交车先用 $x$ 秒到 B 站，然后在 B 站停 $y$ 秒，再用 $x$ 秒到 A 站，再在 A 站停 $y$ 秒，如此循环往复。而这个人先睡眠 $p$ 秒，再醒来 $q$ 秒，如此循环往复。求这个人最早何时能在 B 站下车，若永远不能，输出`infinity`。

#### 思路
可以看出是中国剩余定理。

冷知识：可以直接运用 AtCoder 提供的`math`库里的`crt()`函数就可以了。

#### 复杂度
- 时间复杂度 $\Theta(txp)$
- 空间复杂度 $\Theta(t)$

#### 代码
```cpp
#include <bits/stdc++.h> 
#include <atcoder/math>
using namespace std;
typedef long long ll;
int main() {
    int t;
    cin>>t;
    while (t--) {
        ll x,y,p,q;
        cin>>x>>y>>p>>q;
        ll ans=LLONG_MAX;
        for (ll i=x;i<x+y;i++) {
            for (ll j=p;j<p+q;j++) {
                auto [t,lcm]=atcoder::crt({i,j},{(x+y)*2,p+q});
                if (lcm==0) continue;
                ans=min(ans,t);
            }
        }
        if (ans==LLONG_MAX) cout<<"infinity\n";
        else cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：ForgetOIDuck (赞：1)

### 思路：
设公交车在 A,B 站内往返了 $ m $ 次，这次进行到第 $ a $ 秒；这人睡着睡醒 $ n $ 次，这次进行到第 $ b $ 秒。

则可以列出方程
 $$ 
2m(x+y)+a=n(p+q)+b\\
\downarrow\\
2m(x+y)-n(p+q)=b-a
 $$ 
。

设 $ d=\gcd(2(x+y),p+q) $，由此可得 $ b-a $ 必须是 $ d $ 的倍数。


并且我们可以通过求方程
 $$ 
2m(x+y)-n(p+q)=d
 $$ 
的解来求 $ m,n $ 的最小解。

设 $ b-a=kd $，则 $ k=\dfrac{b-a}{d} $，原方程变为
 $$ 
2km(x+y)-nk(p+q)=kd
 $$ 

发现 $ y,q\le500 $，而 $ x\le a<x+y $， $ p\le b<p+q $，所以 $ a,b $ 的取值范围是很小的，可以枚举 $ a,b $ 来确定 $ m $ 的最小非负整数解，进而带入第一个式子求出最小答案。

设 $ 2(x+y)=t_1d$，$p+q=t_2d $，原式变为
 $$ 
kmt_1-nkt_2=k
 $$ 
。

考虑能将 $ km $ 最多减去多少以达到 $ km $ 的最小非负整数解，设为 $ t $。

相应地，需要将 $ n $ 减去某个数以保持等式成立，设为 $ t^\prime $。

原式变为
 $$ 
(km-t)t_1-(kn-t^\prime)t_2=k\\
\downarrow\\
kmt_1-tt_1-knt_2+t^\prime t_2=1=kmt_1-knt_2\\
\downarrow\\
tt_1=t^\prime t_2\\
\downarrow\\
t^\prime=\dfrac{t t_1}{t_2}
 $$ 
。

由于 $ t_1,t_2 $ 互质，所以 $ t $ 必须为 $ t_2 $ 的倍数，设 $ t=k^\prime t_2 $。

则 $ m $ 的最小值为 $ km-t=km-k^\prime t_2 $。

因为这些数都是非负整数，所以 $ m $ 的最小值可以表示为 $ km \mod t_2 $。设最小值为 $ m^\prime $。

答案为 $ 2m^\prime(x+y)+i $。

时间复杂度 $ O(\log n+n^2) $。

### AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t, x, y, p, q, ans;
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll t, d = exgcd(b, a % b, x, t);
	y = x - a / b * t;
	x = t;
	return d;
}
int main() {
	cin >> t;
	while (t -- ) {
		cin >> x >> y >> p >> q;
		ll a, b, d = exgcd(2 * (x + y), p + q, a, b);
		//cout << a << ',' << b << endl;
		ans = 0x3f3f3f3f3f3f3f3f;
		for (ll i = x; i < x + y; i ++ ) for (ll j = p; j < p + q; j ++ ) {
			if ((j - i) % d) continue;
			ll k = (j - i) / d, t = (p + q) / d, na = ((a * k) % t + t) % t;
			ans = min(ans, na * 2 * (x + y) + i);
		}
		if (ans == 0x3f3f3f3f3f3f3f3f) puts("infinity");
		else cout << ans << endl;
	}
}
```

---

## 作者：cloud2764scallop_eve (赞：1)

## 前置芝士
exgcd 或 excrt。
## 解法一：exgcd
这道题的说明异常明显，对题目中给出的式子进行计算推导，最终是可以化成 exgcd 中类似于 $ax + by = \gcd(a, b)$ 的形式的。但是因为~~我太菜了~~，不会具体的推导过程与证明，所以可以看看[这篇题解](https://www.luogu.com.cn/blog/dongyinjie001/solution-at-abc193e)。
### 代码
需要注意的是，由于数据无比大，所以要定义 `const long long INF = 0x3f3f3f3f3f3f3f3f`。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF = 0x3f3f3f3f3f3f3f3f;
bool flag;
ll x, y, q, p, d, a, b, ans;
void Exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		d = a, x = 1, y = 0;
		return;
	}
	Exgcd(b, a % b, x, y);
	ll t = x;
	x = y, y = t - a / b * y;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld%lld", &x, &y, &p, &q);
		ans = INF, flag = 0;
		Exgcd(2 * (x + y), p + q, a, b);
		for (ll i = p - (x + y - 1); i <= p + q - 1 - x; i++) {
			if (i % d != 0) continue;
			flag = 1;
			ll k = i / d, t = a * k;
			t = (t % ((p + q) / d) + ((p + q) / d)) % ((p + q) / d);
			if (i >= p - x) ans = min(ans, t * 2 * (x + y) + x);
			else ans = min(ans, t * 2 * (x + y) + x + (p - x - i));
		}
		if (!flag) puts("infinity");
		else printf("%lld\n", ans);
	}
	return 0;
}
```
## 解法二：excrt
为了方便表示，我们设高桥下车的时间为 $t$。

观察题目中要求，其实有两点：  
1. 火车恰好在 B 站；
2. 高桥醒着。

那么就有了 $t$ 需要满足的条件：
$\begin{cases}
t \equiv x + i \pmod{(2x + 2y)}\\
t \equiv P + j \pmod{(P + Q)}
\end{cases}$

这是一个区间，不过所幸数据很小，可以直接不加优化枚举。

由于没有说明 $2x+2y$ 和 $P + Q$ 互质，所以是 excrt。
### 代码
同样，请注意 `INF` 的赋值与**多测清零和赋值**。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7, INF = 0x3f3f3f3f3f3f3f3f;
ll x, y, p, q, ans;
ll a[15],b[15];
ll qmul(ll a, ll b, ll mod) {
	ll res = 0;
	while (b) {
		if (b & 1) res = (res + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return res;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll t = x;
	x = y, y = t - (a / b) * y;
	return d;
}
ll excrt(ll n, ll ai[], ll bi[]) {
	ll x, y;
	ll m = bi[1], ans = ai[1];
	for (int i = 2; i <= n; i++) {
		ll a = m, b = bi[i], c = (ai[i] - ans % b + b) % b;
		ll gcd = exgcd(a, b, x, y), bg = b / gcd;
		if (c % gcd != 0) return -1;
		x = qmul(x, c / gcd, bg);
		ans += x * m;
		m *= bg;
		ans = (ans % m + m) % m;
	}
	return (ans % m + m) % m;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		bool flag = 0;
		ans = INF;
		scanf("%lld%lld%lld%lld", &x, &y, &p, &q);
		for (int i = x ; i < x + y ; i++) {
			for (int j = p ; j < p + q ; j++) {
				a[1] = i, b[1] = 2 * (x + y);
				a[2] = j, b[2] = p + q;
				ll res = excrt(2, a, b);
				if (res == -1) continue;
				flag = 1;
				ans = min(ans, res);
			}
		}
		if (!flag) puts("infinity");
		else printf("%lld\n", ans);
	}
	return 0;
}
```
> 这里的两重循环也是可以像法一一样化为一重的，~~但我太懒了~~，可以自行尝试。

---

