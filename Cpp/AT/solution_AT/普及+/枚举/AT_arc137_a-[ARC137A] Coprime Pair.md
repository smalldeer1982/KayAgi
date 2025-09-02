# [ARC137A] Coprime Pair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc137/tasks/arc137_a

整数 $ L,R $ ($ L\ <\ R $) が与えられます．

すぬけ君は，以下の条件を両方満たす整数の組 $ (x,y) $ を探しています．

- $ L\ \leq\ x\ <\ y\ \leq\ R $
- $ \gcd(x,y)=1 $

条件を満たす組において，$ (y-x) $ がとりうる最大の値を求めてください． なお，問題の制約より，条件を満たす組が少なくとも一つ存在することが証明できます．

## 说明/提示

### 制約

- $ 1\ \leq\ L\ <\ R\ \leq\ 10^{18} $
- 入力される値はすべて整数

### Sample Explanation 1

$ (x,y)=(2,4) $ とすると，$ \gcd(x,y)=2 $ となってしまい，条件を満たしません． $ (x,y)=(2,3) $ とすれば条件を満たし，このとき $ (y-x) $ の値は $ 1 $ です． $ (y-x) $ の値がこれより大きくなることはないため，答えは $ 1 $ です．

## 样例 #1

### 输入

```
2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
14 21```

### 输出

```
5```

## 样例 #3

### 输入

```
1 100```

### 输出

```
99```

# 题解

## 作者：Hagasei (赞：6)

对[这个讨论](https://www.luogu.com.cn/discuss/1028210)思想的总结。

一个暴力思路：枚举答案，枚举对应距离点对，跑 gcd 判断合法性。

若答案为 $d$，则复杂度是 $\Theta\left((r-l-d)^2\log r\right)$。下面论证这为什么可过。

考虑一个充分条件：我们枚举到了（$l$ 的下一个质数）和（$r$ 的上一个质数），因为 d 至少是 1，所以前述两数一定不等，从而两不等质数一定互质。

于是 $r-l-d$ 就至多是（$l$ 到下一个质数的距离）+（$r$ 到上一个质数的距离）。设 $N$ 是大于 $10^{18}$ 的最小质数，则前述二距离都一定小于 $N$ 以内的最大的相邻质数间距 $g_N$，于是 $r-l-d$ 就不会超过 $2g_N$。

我们当然希望知道 $g_k$ 数列的数量级，但可惜这是未解决问题，目前的估计大约是 $\Theta(\log^2k)$，更多信息可在[这里](https://en.wikipedia.org/wiki/Prime_gap)找到。不过我们是搞计算机的，不用管也管不了这么多麻烦的渐进复杂度，直接在刚刚的链接里查表得 $g_N=1442$。在数值上算出运算量是 $(2g_N)^2\ln N\approx3.4\times10^8$。时间限制两秒，这是可过的。

上面的每一步放缩都在往大放，而且放得特别夸张，所以这个上界应该是特别松的，但算出来的运算量依然是可承受的，故上算法可过。

（噢，在数值上算运算次数的话，注意到前面那个平方实则是自然数列前缀和，所以要除以二，不过无所谓，因为这步也是在往大放缩。）

---

## 作者：Drifty (赞：4)

### Solution

直接暴力，但是考虑从大到小枚举区间长度，有解了直接退出。

乍一看是会跑到 $O(d^2)$（我们记 $r - l + 1 = d$）的，但是实际上会发现只要两个数都是质数就会推出，由于我们是从边缘往中间找的，因此会发现实际上很快就会撞到这两个质数，由于质数的间隔最大是 $\log^2 d$ 级别的，因此枚举量实际上只有 $O(\log^4 d)$。

由于数据好且实现常数小，实际上跑得飞快。

upd：对于之前没有认真考虑枚举量导致的复杂度错误，现已修改，非常抱歉。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    i64 l, r; cin >> l >> r;
    for (i64 len = r - l; len >= 0; len --) 
        for (i64 i = l; i <= r - len; i ++) 
            if (__gcd(i, i + len) == 1) return cout << len << '\n', 0;
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

## 思路

直接暴力即可，虽然时间复杂度看似是 $O((r - l + 1)^2)$，但是，我们发现，如若从两边向中间找，非常快就可以找到。根据[素数定理（PNT）](https://baike.baidu.com/item/%E7%B4%A0%E6%95%B0%E5%AE%9A%E7%90%86/1972457)我们可以得出，素数数量大约在 $\frac{x}{\ln(x)}$（设 $x = r - l + 1$），素数的间隔大约在 $\ln(x)$ 左右，那么在最坏的情况下，也就是说 $l - 1$ 与 $r + 1$ 分别为素数，这样我们要枚举 $(\ln(x)) ^ 2$ 次，时间复杂度就是 $O((\ln(x)) ^ 2) \approx O(\log^2 x)$。可以通过。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int l, r, ans = 1;
	cin >> l >> r;
	if (l == 1) return cout << r - l << '\n', 0;
	for (int i = l; ans < r - i; i++) 
		for (int j = r; ans < j - i; j--)
			if (__gcd(i, j) == 1) ans = j - i;
// ans 记录最值，若 i,j 最大估计都小于 ans，就不用枚举了
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：bsdsdb (赞：1)

题意：求属于 $[l,r]$ 的 $x,y$，满足：

- $\gcd(x,y)=1$；
- $y-x$ 最大。

## 法一：枚举

```python
for leng in range(r - l, 0, -1):
    for x in range(l, r - leng + 1):
        y = x + leng
        if math.gcd(x, y) == 1:
            print(leng)
            sys.exit(0)
```

复杂度证明：

如果 $k$ 满足 $\forall l<r<10^{18}:\exist x,y:x\in[l,l+k),y\in(y-k,y],\gcd(x,y)=1$，那么复杂度显然是 $\mathcal O(k^2\log r)$。设 $p$ 是最小的大于等于 $l$ 的质数，即 $p=\min\{x\mid x\ge l,x\text{ is prime}\}$，那么 $r$ 和 $r-1$ 至少有一个和 $p$ 互质。由 [Prime gap - Wikipedia](https://en.wikipedia.org/wiki/Prime_gap) 可知，$10^{18}$ 以内的最大相邻质数间隔为 $1442$，也就是说在 $l<10^{18}$ 时有 $p-l<1442$，也就是说 $k<1442$。

$[l,l+6),(r-17,r]$ 也是可以的，见 [link](https://www.luogu.com.cn/article/ae0403et)。

## 法二：模拟退火

细节见[这里](https://lglg.top/1027569)。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937_64 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ll l, r;

inline ll f(ll x, ll y) {
	if (__gcd(x, y) == 1) {
		return abs(x - y);
	} else {
		return 0;
	}
}

inline ldb rdr() {
	return ldb(1) * rd() / ((__int128(1) << 64) - 1);
}
inline ll rnd(ll x, ll y) {
	return min(max(ll(rd() % (y - x) + x), l), r);
}

int main() {
	auto st = clock();
	read(l), read(r);
	ll ansx = l, ansy = r, curx = l, cury = r, fa = f(ansx, ansy), fc = f(curx, cury);
	for (ll T = 1e18; T; T *= 0.999) {
		ll x = rnd(curx - T, curx + T);
		ll y = rnd(cury - T, cury + T);
		if (y < x) {
			swap(x, y);
		}
		ll ff = f(x, y);
		if (ff > fa) {
			ansx = x, ansy = y, fa = ff;
		}
		if ((ff > fc) || (rdr() < exp(ldb(-1) * abs(ff - fc) / T))) {
			curx = x, cury = y, fc = ff;
		}
	}
	ll rdfy = 10;
	// cerr << ansx << ' ' << ansy << endl;
	while (ldb(clock() - st) / CLOCKS_PER_SEC < 1.99) {
		ll x = rnd(ansx - rdfy, ansx + rdfy);
		ll y = rnd(ansy - rdfy, ansy + rdfy);
		if (y < x) {
			swap(x, y);
		}
		ll ff = f(x, y);
		if (ff > fa) {
			// cerr << x << ' ' << y << endl;
			ansx = x, ansy = y, fa = ff;
		}
	}
	write(ansy - ansx), enter();
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

