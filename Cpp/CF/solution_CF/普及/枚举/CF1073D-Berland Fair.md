# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6
```

### 输出

```
6
```

# 题解

## 作者：Ynoi (赞：11)

此题其实不难

首先我们暴力的把每一次转一圈所消耗的钱算出来。

之后就用m对转一圈消耗的钱取膜，表示可以转这么多圈

由于每次膜数小于m，所以m每次至少变为原来一半，总时间复杂度nlogm

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define LL long long
LL n,m,s,ans,rs;
LL a[MAXN];

void rd()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
    { 
        cin >> a[i]; 
    }
}

int main()
{
    rd();
    while(s > 0)
    {
        s = 0;rs = 0;//s统计这样消耗的钱数，rs表示每次这样转能买多少糖
        for(int i = 1; i <= n; i ++)
            if(s+a[i] <= m)
            {
                s += a[i]; 
                rs ++;
            }
            if(s == 0) break;
            ans += m / s * rs;
            m %= s;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：信息向阳花木 (赞：4)

~~竟然在模拟赛上自己做出来了啊哈哈赶紧写篇题解。~~

这道题暴力一定会超时的。那么我们考虑下面一个问题：

如果转了一圈以后还能买的糖果数量和所需钱数和上一圈一样的话我们还需要再模拟一遍吗？

很显然不用了。

因此我们考虑先把每转一圈能买的糖果数量和所需钱数算出来，然后用 $O(1)$ 的时间复杂度算出在这种情况下总共花的钱数以及能买到的糖果数。在用 $O(n)$ 的时间复杂度暴力重新算一下当前每转一圈还能买的糖果数量和所需钱数，直到不能买了为止。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 200010;

typedef unsigned long long LL;

LL n;
LL t, res, sum, cnt;
LL a[N];

int main()
{
    scanf ("%llu%llu", &n, &t);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%llu", &a[i]);
        if(t - sum >= a[i])
        {
            sum += a[i];
            cnt ++;
        }
    }
    while (sum > 0 && t > 0)
    {
        res += t / sum * cnt; // 答案加上能走的圈数乘上每走一圈可以买到的糖果数。
        t %= sum;
        sum = 0; cnt = 0;
        for (int i = 1; i <= n; i ++ )
        {
            if(t - sum >= a[i])
            {
                sum += a[i];
                cnt ++;
            }
        }
    }
    printf("%llu\n", res);

    return 0;
}
```

注：代码中的几个变量意义如下：

* $cnt$ 表示当前走一圈能买到的糖果数。
* $sum$ 表示当前走一圈买 $cnt$ 颗糖果所需钱数。
* $t$ 表示现在还剩多少钱。

---

## 作者：SDLTF_凌亭风 (赞：2)

评分很奇怪，因为这题撑死橙题。

每次循环记录三个变量：一圈花费多少、能转几圈、这一圈要买多少商品。

然后十年 OI 一场空，按题意模拟即可。代码如下：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n, T, cnt, raw[200003], sgm;
signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> T;
	for (int i = 1; i <= n; ++i) cin >> raw[i], sgm += raw[i];
	int rnd = T / sgm; T -= rnd * sgm, cnt = rnd * n;
	if (!T) return (cout << rnd * n), 0;
	else {
		while (T > 0) {
			int newcost = 0, newrnd = 0, newcnt = 0;
			for (int i = 1; i <= n; ++i) if (T - newcost - raw[i] >= 0) (newcost += raw[i]), ++newcnt;
			if (newcost == 0) break;
			newrnd = T / newcost, T -= newcost * newrnd, cnt += newcnt * newrnd;
		}
	}
	cout << cnt;
}
```

---

## 作者：一扶苏一 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10220109.html)

## Description

给定 $n$ 个商店，他们围成一个圆圈，按照顺时针从 $1$ 到 $n$ 编号。你有 $T$ 元钱，从 $1$ 号点开始按照顺时针方向走，每到一个商店，只要钱够就必须买这个商店的物品。商店中物品是无限的，即多次到达可能多次购买。求会买多少件物品

## Input

第一行是一个整数 $n$

下面一行 $n$ 个整数 $a_i$，代表每个商店物品的价格

## Output

一行一个整数代表答案

## Hint

$1~\leq~n~\leq~2~\times~10^5~,~1~\leq~T~\leq~10^{18}~,~1~\leq~a_i~\leq~10^9$

## Solution

解法一：

显然在钱数充足是我们可以直接除一下得到我们可以转多少圈，$O(1)$ 统计这部分答案，然后把钱数取模即为这些圈转完后我们剩下的钱，这时的钱数是不足以转完一圈的。

下面我们考虑用这些钱可以连续走多远，即会到哪一个商店停下来。注意到这个值是可以二分的，具体的，我们维护一个前缀和，二分哪个位置的前缀和是最大的小于钱数的即可。然后剩下那个位置的商店显然再也不会被购买到了，于是可以将它直接删去，然后统计这一段连续走的位置的答案。删除这个位置后的前缀和可以用树状数组或线段树维护，一段区间中还剩多少个没有被删去的位置也可以树状数组维护。对于这个位置后面能连续走到哪里，我们依然可以二分这个值，以此类推直到一圈走完，然后从头开始重复流程即可。

注意到每次二分我们一定会删除一个位置，所以我们会二分 $O(n)$ 次，直接二分+树状数组/线段树的话，单次二分复杂度 $O(\log^2 n)$，总复杂度 $O(n \log^2 n)$。如果在线段树上二分，单次复杂度可以做到 $O(\log n)$，总复杂度 $O(n \log n)$。

~~但是天知道为什么我的两个log算法跑的比一个log的还快~~

解法二：

算出当前的钱数可以走多少圈的方法同上，然后考虑我们暴力跑一圈，统计有哪些位置的是不能被购买到的，直接删掉。然后用剩下的钱再取模。

注意到 $T$ 每次取模时的模数一定小于 $T$，而一个数被比自己小的数取模至少减少二分之一，证明上可以分模数大于或小于等于 $\frac{m}{2}$ 进行讨论。于是 $T$ 被取模 $O(\log T)$ 次，每次对应一次 $O(n)$ 的统计答案，于是总复杂度 $O(n \log T)$。

## Code

依据解法一写成。

$O(n \log^2n)$

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long  ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;

int n;
ll t, ans;
int MU[maxn];
ll tree[maxn], val[maxn];

inline int lowbit(ci x) {return x & (-x);}

ll ask(ll*, int);
int check(int, ll);
void update(ll*, int, ci);

signed main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(t);
	for (rg int i = 1; i <= n; ++i) {qr(MU[i]); update(tree, i, MU[i]); update(val, i, 1);}
	ll s = ask(tree, n); int cnt = n;
	while (cnt) {
		if (!t) break;
		ans += t / s * cnt; t %= s;
		int k = 0;
		do {
			int pre = k;
			k = check(k, t);
			if (k > n) {
				t -= ask(tree, n) - ask(tree, pre);
				ans += ask(val, n) - ask(val, pre);
				break;
			};
			update(tree, k, -MU[k]); update(val, k, -1); --cnt;
			t -= ask(tree, k - 1) - ask(tree, pre);
			s -= MU[k];
			ans += ask(val, k) - ask(val, pre);
		} while (cnt && t);
	}
	qw(ans, '\n', true);
}

void update(ll *ar, int x, ci v) {
	while (x <= n) {
		ar[x] += v;
		x += lowbit(x);
	}
}

ll ask(ll* ar, int x) {
	ll _ret = 0;
	while (x) {
		_ret += ar[x];
		x -= lowbit(x);
	}
	return _ret;
}

int check(int pre, ll x) {
	int l = pre, r = n + 1, mid = l, _ret = 0;
	while (l <= r) {
		mid = (l + r) >> 1;
		if ((ask(tree, mid) - ask(tree, pre)) <= x) _ret = mid, l = mid + 1;
		else r = mid - 1;
	}
	return _ret + 1;
}
```

$O(n \log n)$

```cpp
#include <ctime>
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	int buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = int(x % 10 + '0');} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;
const int maxt = 400010;

int n;
ll t, ans;
int tree[maxn], MU[maxn];

struct Tree {
	Tree *ls, *rs;
	int l, r;
	ll v;
	
	inline void pushup() {
		this->v = this->ls ? (this->rs ? this->ls->v + this->rs->v : this->ls->v) : this->rs->v;
	}
};
Tree *pool[maxt], qwq[maxt], *rot;
int top;

inline int lowbit(ci x) {return x & -x;}

int check(int, ll);
void buildpool();
void build(Tree*, ci, ci);
void update(int, ci);
void update(Tree*, ci);
ll ask(Tree*, ci, ci);
int ask(int);
int ask(Tree*, cl);

signed main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(t); ll s = 0; 
	for (rg int i = 1; i <= n; ++i) {qr(MU[i]); s+= MU[i]; update(i, 1);}
	int cnt = n;
	buildpool();
	build(rot, 1, n);
	while (cnt) {
		if (!t) break;
		ans += t / s * cnt; t %= s;
		int k = 0;
		do {
			int pre = k;
			k = check(k, t);
			if (k > n) {
				t -= ask(rot, pre + 1, n);
				ans += ask(n) - ask(pre);
				break;
			};
			update(rot, k); update(k, -1); --cnt;
			t -= ask(rot, pre, k - 1);
			s -= MU[k];
			ans += ask(k) - ask(pre);
		} while (cnt && t);
	}
	qw(ans, '\n', true);
}


int check(int pre, ll x) {
	x += ask(rot, 1, pre);
	ll s = ask(rot, 1, n);
	if (s <= x) return n + 1;
	return ask(rot, x);
}

void buildpool() {
	for (rg int i = 0; i < maxt; ++i) pool[i] = qwq + i;
	rot = pool[maxt - 1];  top = maxt - 2;
}

void build(Tree *u, ci l, ci r) {
	u->l = l; u->r = r;
	if (l == r) {u->v = MU[l]; return;}
	int mid = (l + r) >> 1;
	if (l <= mid) build(u->ls = pool[top--], l, mid);
	if (mid < r) build(u->rs = pool[top--], mid + 1, r);
	u->pushup();
}

void update(int x,ci v) {
	while (x <= n) {
		tree[x] += v;
		x += lowbit(x);
	}
}

void update(Tree* u, ci x) {
	if ((u->l > x) || (u->r < x)) return;
	if (u->l == u->r) {u->v = 0; return;}
	if (u->ls) update(u->ls, x);
	if (u->rs) update(u->rs, x);
	u->pushup();
}

int ask(int x) {
	int _ret = 0;
	while (x) {
		_ret += tree[x];
		x -= lowbit(x);
	}
	return _ret;
}

ll ask(Tree *u, ci l, ci r) {
	if ((u->l > r) || (u->r < l)) return 0;
	if ((u->l >= l) && (u->r <= r)) return u->v;
	return u->ls ? (u->rs ? ask(u->ls, l, r) + ask(u->rs, l, r) : ask(u->ls, l, r)) : ask(u->rs, l, r);
}

int ask(Tree *u, cl v) {
	if (u->l == u->r) return u->l;
	if (u->ls->v <= v) return ask(u->rs, v - u->ls->v);
	else return ask(u->ls, v);
}
```

## Summary

该define int ll就要define啊= =要不然可能会fst的很惨= =

一个数对比自己小的数取模一次至少减少一半。

---

## 作者：JMercury (赞：2)

有一些集市按顺序围成一圈，每个集市上都卖糖果且有不同的价格。一个人从1号集市出发，如果钱够就买一个糖果，然后走到下一个集市，否则直接走到下一个集市，直到没有糖果可买为止。求最终可以买多少糖果

感觉和约瑟夫有点像是不是？首先可以注意到两个事实

1.如果钱充足，那么走一圈可以买到一定数量的糖果

2.如果走到某一个集市时不能买糖果，那么就不可能在这个集市买糖果了

所以我们先考虑可以走多少个一整圈；不能走一整圈后，用$O(n)$的复杂度走一圈，把不能买到糖果的地方淘汰出去。重复这两个步骤即可

~~复杂度？鬼知道，所以应该会被hack（反正比赛跑过了x~~

附上AC代码

```cpp
#include<bits/stdc++.h>
typedef long long LL;
const LL maxn=200010;
using namespace std;

LL n,tot;
LL a[maxn],nn,ns; 
///nn是当前走一圈可以买到糖果的数量，ns是当前走一圈的花费
bool vis[maxn];
LL ans;

int main()
{
    scanf("%I64d%I64d",&n,&tot);
    for(LL i=1;i<=n;i++) scanf("%I64d",&a[i]),ns+=a[i],nn++;
    while(1)
    {
        ans+=nn*(tot/ns),tot%=ns;
        bool b=false; ///寻找还有没有可以买糖果的集市
        for(LL i=1;i<=n;i++)
        {
            if(vis[i]) continue;
            if(tot>=a[i]) tot-=a[i],ans++,b=true;
            else vis[i]=true,nn--,ns-=a[i];
        }
        if(!b) break;
    }
    printf("%I64d",ans);
    return 0;
}
```


---

## 作者：傅思维666 (赞：1)

## 题解：

~~不太明白这题为啥是个紫题~~

**题目大意：**

给定一个长度为$N$的序列，有一个数$K$，每次遍历序列时如果$K\ge a_i$，那么，$ans++$，$K-=a_i$。如果位置为$N$，下一次遍历会返回$1$.问$ans$最后是多少。

（来自国赛金牌集训队大佬$Winniechen$的模拟赛）

考试的时候就想到了这样的思路：

先跑前缀和，然后比较$K$和$sum[N]$的值，以$N$为单位来跑，这样就省时间，什么时候不能继续减了，就一直从$1-N$跑，直到$K$一个数也不能再减为止，输出$ans$，有了下面这份代码：

```c++
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=2*1e5+1;
ll n,k,ans,minn=1e9+10;
ll a[maxn];
ll sum[maxn];
int main()
{
    //freopen("fairs.in","r",stdin);
    //freopen("fairs.out","w",stdout);
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
        minn=min(minn,a[i]);
    }
    while(k>=sum[n])
    {
        ans+=n;
        k-=sum[n];
    }
    while(k>=minn)
    {
        for(int i=1;i<=n;i++)
            if(k>=a[i])
            {
                ans++;
                k-=a[i];
            }
    }
    printf("%lld",ans);
    return 0;
}
```

期望得分：100，实际得分：100.

但是机房有很多大佬不相信本蒟蒻能切这道题，所以他们来check了我的代码，后来分析复杂度，得出我的确切不掉这题，只是$Winniechen$的数据很水罢了。不服气的我找到了原题提交...

然后T了。~~（真香）~~

后来苦思冥想，思路没有变，但是想到了这份暴力枚举代码的种种优化：

首先，不用跑前缀和，因为我们只能用到$sum[N]$，开前缀数组纯属浪费空间。

其次，不用用while循环一次一次减，只需要用一个乘法算式即可。

然后，不用每次都从$1 - N$枚举，因为如果$K$不能减去这个数，它就永远也不可能再能减去这个数，所以用标记数组，碰到减不下去的就直接标记，以后遍历的时候就可以跳过了。

为了实现以上思路，需要用一个”死循环“以及一个flag变量标记，具体细节不讲了，请看官们直接欣赏代码：

```c++
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=1e5*2+1;
ll n,k;
ll a[maxn];
bool v[maxn];
ll sum,ans,tot;
int main()
{
    scanf("%lld%lld",&n,&k);
    tot=n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    while(1)
    {
        ans+=tot*(k/sum);
        k%=sum;
        int flag=0;
        for(int i=1;i<=n;i++)
        {
            if(v[i])
                continue;
            if(k>=a[i])
            {
                ans++;
                k-=a[i];
                flag=1;
            }
            else
            {
                v[i]=1;
                sum-=a[i];
                tot--;
            }
        }
        if(flag==0)
            break;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Hanx16Kira (赞：0)

# Berland Fair

[Luogu CF1073D](https://www.luogu.com.cn/problem/CF1073D)

[Codeforces 1073D](https://codeforces.com/problemset/problem/1073/D)

## Solution

话说我这个应该不是最优解第一，应该只是第一页而已，不过好像因为计时的方式改变了导致我的耗时低于第二，最慢点 62ms。

[提交记录](https://www.luogu.com.cn/record/90770461)

假设在环内转圈，那么这个环中权值最大的位置一定是第一个买不到的（可能买不起停下的位置不是在最大的位置，但是既然更小的位置都买不起了，最大的一定也买不起），考虑用优先队列维护这样一个权值最大的值，记队内元素的和为 $sum$，那么会发现如果 $T\ge sum$，就意味着当前一定能够绕全部一圈，并且转的圈数也是可以通过数学方式计算的，为 $\displaystyle\lfloor\frac T {sum} \rfloor$，每一圈对答案的贡献就是队列长 `q.size()`。

如果此时 $T< sum$，就说明有的点不可能再买得到了，所以就把这些点从优先队列的队头踢掉，踢出队列的同时将这些点对于队列元素之和 $sum$ 的贡献剔除。会发现此时可能仍然可能出现 $T<sum$ 的情况，并且队头元素是小于 $T$ 的，因此这时候需要在序列中枚举一遍（不用担心已经删掉的点影响结果，因为删掉的点的权值一定大于现在的 $T$，因此不会对答案产生影响）。看代码可能更好理解。

因为每个元素只会进队出队一次，队列是优先队列，因此时间复杂度为 $\mathcal O(n(\log n + \log m))$ 的（$\log m$ 是因为每次取模至少变成原来的 $0.5$ 倍），可能因为优先队列舍去了很多无用状态，所以常数很小，跑的飞快。

**Code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int _SIZE = 2e5;
int n, T, a[_SIZE + 5], ans, sum;
priority_queue<int> q;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> T;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i]; q.push(a[i]); // 每个点入队
	}
	while (!q.empty()) {
		if (T >= sum) ans += T / sum * q.size(), T %= sum; // 可以转整圈
		while (!q.empty() && T < q.top()) sum -= q.top(), q.pop(); // 踢掉不可能再做贡献的点
		for (int i = 1; i <= n; i++) if (a[i] <= T) T -= a[i], ans++; // 枚举散点，需要注意这部分不能放到循环外
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：fengxiaoyi (赞：0)

这题只需一轮一轮的模拟，直至再也买不起糖果为止。

定义两个变量：$s,w$，其中 $s$ 表示当前这一轮买糖果消耗的钱，$w$ 表示买糖果的个数。

接着枚举店铺，如果：
$$s+a_i\le t$$
则：
~~~cpp
s+=a[i];
w++;
~~~
然后判断，如果 $s$ 不等于 $0$,则（ans表示糖果个数）
~~~cpp
ans+=t/s*w;
t%=s;

~~~
### 什么时候才算所有糖果都买不起？

我们只要判断在枚举完店铺后，判断 $s$ 是不是大于 $0$ 即可（因为如果 $s=0$ 就代表没有买糖果，不过这个是在循环的判断条件里做的）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[200010],ans,s=1,w;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(s>0){//判断所有糖果是否买不起。
		s=w=0;
		for(int i=1;i<=n;i++){
			if(s+a[i]<=t){
				s+=a[i];
				w++;
			}
		}
		if(s==0){
			continue;
		}
		ans+=t/s*w;
		t%=s;
	}
	cout<<ans<<endl;
	r0;
}
```


---

## 作者：decoqwq (赞：0)

昨晚$cf$只切了四道题的蒟蒻来写个题解

这道题很简单啊...比$C$简单多了

首先我们考虑暴力枚举，一个一个转圈圈，肯定是超时

然后大家都会想到一个优化，就是把所有点的总和找到，然后找当前钱可以把一圈买多少遍，然后把钱对总和取模再暴力救星

可是这样会被卡死，如果我只有一个的价钱是$1e8$，其他都是$1$，暴力极限还是会循环$1e8$次左右

我们接着前面的思路，如果当前点的价钱已经大于剩下的钱数，我们就把$sum$减去这个点的价钱，再用刚才的方法，把剩下的钱除以这个值，看其他的东西还能够买几圈，然后取模就行了

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
ll n,t;
ll a[200020];
ll sum;
int main()
{
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    ll ans=0;
    ll pp=t/sum;
    ans+=pp*n;
    t=t-pp*sum;
    int flag=0;
    int i=1;
    int now=n;
    while(1)
    {
        if(i==1)
        {
            flag=0;
        }
        if(a[i]<=t)
        {
            t-=a[i];
            flag=1;
            ans++;
        }
        else
        {
            sum-=a[i];
            if(!sum)
            {
                break;
            }
            now--;
            ll qaq=t/sum;
            ans+=now*qaq;
            t=t-qaq*sum;
        }
        if(i==n&&!flag)
        {
            break;
        }
        else if(i==n)
        {
            i=1;
            continue;
        }
        i++;
    }
    cout<<ans;
}
```

---

## 作者：ustze (赞：0)

题意：$Polycarp$有$T$元钱，有$n$个商铺，每家商铺出售相同的糖果，价格为$a[i]$元，$Polycarp$现在按$1,2,...n,1,2..$的顺序访问每家商铺，如果他手上的钱$>=a[i]$，他就购买一个糖果，并前往下一家店（买不起就直接前往下一家店）。问他一共能买到多少个糖果？
题目还是比较简单的，作为$D$题来说很水，考虑到如果他这一次访问第$i$家时买不起，那他以后就都买不起了，所以我们可以用一个链表维护这$n$家商铺，当他手上的钱不够时，就把这家店从链表里删除。具体细节看代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
int n;ll T;
ll a[N];int nxt[N],la[N];
int main()
{
    scanf("%d%I64d",&n,&T);
    ll sum=0,mn=2147483647;
    for(int i=1;i<=n;i++) scanf("%I64d",&a[i]),sum+=a[i],nxt[i]=i+1,la[i]=i-1,mn=min(mn,a[i]);
    ll ans=0,num=n;int st=1;
    while(T>=mn) 
    {
        ans+=(T/sum)*num;T%=sum; //当T足够大时每家店都可以买，减小枚举量
        if(T<mn) break;
        for(int i=st,flag=0;i!=n+1;i=nxt[i])
            if(T>=a[i]){
                T-=a[i];ans++;if(T<mn) break;
                if(!flag) st=i,flag=1;
            }
            else nxt[la[i]]=nxt[i],la[nxt[i]]=la[i],sum-=a[i],num--;
    }
    printf("%I64d",ans);
    return 0;
}
```

---

