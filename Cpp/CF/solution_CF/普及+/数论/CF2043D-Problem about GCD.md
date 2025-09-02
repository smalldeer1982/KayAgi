# Problem about GCD

## 题目描述

给出三个整数 $l,r,G$，要求找到一个数对 $A,B$ 满足 $l\le A\le B\le r$ 且 $\gcd (A,B) = G$，并且满足 $\left\vert A-B \right\vert$ 最大。

如果有多组解，选择 $A$ 的值最小的一个。

## 说明/提示

$1\le t\le 10^3$

$1\le l\le r\le 10^{18}$

$1\le G\le 10^{18}$

## 样例 #1

### 输入

```
4
4 8 2
4 8 3
4 8 4
5 7 6```

### 输出

```
4 6
-1 -1
4 8
6 6```

# 题解

## 作者：sintle (赞：11)

## 题目链接

- [CF2043D Problem about GCD](http://codeforces.com/problemset/problem/2043/D)
- [洛谷站内链接](https://www.luogu.com.cn/problem/CF2043D)

## 题意简述

给出三个整数 $l,r,G$，要求找到一个数对 $A,B$ 满足 $l\le A\le B\le r$ 且 $\gcd (A,B) = G$，并且满足 $\left\vert A-B \right\vert$ 最大。

如果有多组解，选择 $A$ 的值最小的一个。

## 解题思路

首先 $A,B$ 肯定都是 $G$ 的倍数，所以直接将 $l,r$ 转化为 $\left\lceil \dfrac{l}{G} \right\rceil,\left\lfloor \dfrac{r}{G} \right\rfloor$，在该区间内求最远互质点对，设为 $(x ,y)$，则 $(A,B)=(x\times G,y\times G)$。

关于如何求区间内最远互质点对，可以参考 [Atcoder arc137_a](https://atcoder.jp/contests/arc137/tasks/arc137_a)（[站内链接](https://www.luogu.com.cn/problem/AT_arc137_a)）。

如果直接暴力枚举 $\left\vert x-y \right\vert$ 和 $x$，理论复杂度达到了惊人的 $O((r-l)\log a)$，看上去是不能通过的。

但是其实并不会遍历那么多次，参考上面给出的题解可知在题目给出的 $1\times 10^{18}$ 数据范围内复杂度并没有很高。

所以尽管并未算出实际复杂度期望，但是我们暴力枚举仍然可以通过本题。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

long long T , l , r , g;

long long gcd(long long aa , long long bb) {return bb ? gcd(bb , aa % bb) : aa;}

void solve()
{
    long long len = r - l;
    while(len >= 0)
    {
        for(long long i = l ; i <= r - len ; i++) if(gcd(i , i + len) == 1) {cout << i * g << " " << (i + len) * g << '\n'; return;}
        len--;
    }
    cout << -1 << " " << -1 << '\n';
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> T;
    while(T--)
    {
        cin >> l >> r >> g;
        l += g - 1; l /= g; r /= g;
        solve();
    }
    return 0;
}
```

## 补充

以下是不严谨的关于该代码时间复杂度的证明。 

### 参考资料

- [维基百科 克拉梅尔猜想](https://zh.wikipedia.org/wiki/%E5%85%8B%E6%8B%89%E6%A2%85%E7%88%BE%E7%8C%9C%E6%83%B3)

### 证明

在维基百科的这一条目中提到，托马斯·雷·奈斯利使用了公式 $R=\dfrac{\log p_n}{\sqrt{p_{n+1}-p_n}}$ 来计算素数间隙与克拉梅尔猜想相契合的程度，对于现在已知最大的素数间隙， $R$ 的值依然保持在 $1.13$ 左右。

因此该题目中最大的素数间隙（设其为 $g(i)$，且 $p_i$ 表示最大的质数间隙对应的质数对中较小的那一个）在 $(\dfrac{\log p_i}{1.13})^2$ 左右，因此即使我们并不确定 $i$ 的具体值，$g(i)$ 的值一定不会超过 $(\dfrac{\log 1e18}{1.13})^2$，而该式的值约为 $60$。

在该题目中，能够构造出的最坏情况为 $l,r$ 分别距离 $x,y$ 为 $g(i)$，此时上述代码的时间复杂度为 $g(i)^2$。

又因为我们已经证明了 $g(i)$ 的值并不会超过 $60$，所以上述代码的最坏时间复杂度为 $O(Tg(i)^2)$，不超过 $3.6\times 10^6$，显然可以通过本题。

---

## 作者：bsdsdb (赞：7)

题意：给定 $l,r,g$，求 $x,y$ 满足（或报告不存在）：

- $\gcd(x,y)=g$；
- $y-x$ 最大化。

令 $l'\gets\left\lceil\dfrac{l}{g}\right\rceil,r'\gets\left\lfloor\dfrac{r}{g}\right\rfloor$，则问题就变为了求 $[l',r']$ 内的差最大互质对。$l'=r'$ 无解，否则至少有解 $(l',l'+1)$，可以枚举：

```python
// python
for leng in range(r - l, 0, -1):
    for x in range(l, r - leng + 1):
        y = x + leng
        if math.gcd(x, y) == 1:
            print(leng)
            sys.exit(0)
```

如果能证明 $\forall l<r\le 10^{18}:\exist x,y:x\in[l,l+k_1],y\in[r-k_2,r]:\gcd(x,y)=1$ 的话，枚举量就是 $\mathcal O((k_1+k_2)^2)$，总复杂度就是 $\mathcal O((k_1+k_2)^2\log r)$。接下来我们证明 $k_1=5,k_2=16$ 是合法的。

- $[l,l+5]$ 内必有数和 $30$ 互质。

  证：他们模 $6$ 的余数肯定是 $0,1,2,3,4,5$。如果余 $1$ 的那个是 $5$ 的倍数，那么余 $5$ 的那个就不是 $5$ 的倍数；如果余 $5$ 的那个是 $5$ 的倍数，那么余 $1$ 的那个就不是 $5$ 的倍数。

- 记这个数为 $a$，他的所有质因数记作一个单调递增的序列 $\{p_m\}$，那么 $m\le12,p_1$ 到 $p_m$ 分别大于等于 $7,11,13,\cdots,47$。

  证：$7\times11\times13\times17\times19\times23\times29\times31\times37\times41\times43\times47\times53=1\ 086\ 305\ 282\ 573\ 001\ 491>10^{18}$。

- $[r-16,r]$ 这 $17$ 个数内必有一个数不是任何一个 $p_i$ 的倍数。

  记 $f(x)$ 为连续 $17$ 个数可能的最多的 $x$ 的倍数的数量，也就是 $f(x):=\left\lceil\frac{17}{x}\right\rceil$，则：

$$
\begin{aligned}
\sum_{i=1}^mf(p_i)\le\ &f(7)+f(11)+\cdots+f(47)\\\
&=3+2+2+1+1+1+1+1+1+1+1+1\\
&=16
\end{aligned}
$$

也就是说，连续 $17$ 个数里最多有 $16$ 个数是 $p_i$ 的倍数，还有一个不是任何 $p_i$ 的倍数，也就是和 $[l,l+5]$ 中的某个数互质。

~~其实理论上还可以用模拟退火做，但是我只卡到了第 10 个数据点~~

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
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
using namespace chrono;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
// #define LOCAL
mt19937_64 rd(ll(11451491918102023));
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

const ll rdpyl = 3;

ll l, r, g, _T;
/* used in simulate annealing
chrono::high_resolution_clock::time_point st;

inline pll f(ll x, ll y) {
	if (__gcd(x, y) == 1) {
		return mkp(abs(x - y), -min(x, y));
	} else {
		return mkp(0, 0);
	}
}

inline ldb rdr() {
	return ldb(1) * rd() / ((__int128(1) << 64) - 1);
}
inline ll rnd(ll x, ll y) {
	x = min(x, r);
	if (x == y) {
		return x;
	}
	ll nr = rd() % (y - x) + x;
	if (nr < l) {
		return min(l + ll((rd() % 18) / 10), r);
	}
	if (nr > r) {
		return max(r - ll(rd() % rdpyl), l);
	}
	return nr;
}
*/

int mian(ll t) {
	read(l), read(r), read(g);
	if ((l + g - 1) / g * g > r) {
		puts("-1 -1");
		return 0;
	}
	l = (l + g - 1) / g, r = r / g;
	if (l == 1 && r == 1) {
		write(g), space(), write(g), enter();
		return 0;
	}
	if (l >= r) {
		puts("-1 -1");
		return 0;
	}
	for (ll len = r - l + 1; len >= 1; --len) {
		for (ll x = l; x + len - 1 <= r; ++x) {
			ll y = x + len - 1;
			if (__gcd(x, y) == 1) {
				write(x * g), space(), write(y * g), enter();
				return 0;
			}
		}
	}
	/* simulate annealing method:
	ll ansx, ansy, curx, cury;
	ll initpyl = 30;
	if (r - l <= initpyl) {
		ansx = curx = l, ansy = cury = r;
	} else {
		ansx = curx = l + (initpyl >> 1), ansy = cury = r - (initpyl >> 1);
	}
	pll fa = f(ansx, ansy), fc = f(curx, cury);
	for (ldb _T = initpyl; _T >= 0.9; _T *= 0.95) {
		ll T = _T;
		ll x = rnd(curx - T, curx + (T >> 1));
		ll y;
		if (fa.first) {
			y = rnd(x + fa.first, cury + T);
		} else {
			y = rnd(cury - T, cury + T);
		}
		if (y < x) {
			swap(x, y);
		}
		pll ff = f(x, y);
		if (ff > fa) {
			ansx = x, ansy = y, fa = ff;
		}
		if ((ff > fc) || (rdr() < exp(ldb(-1) * abs(ff.first - fc.first) / T))) {
			curx = x, cury = y, fc = ff;
		}
	}
	ll rdfy = 15;
	while (duration_cast<microseconds>(high_resolution_clock().now() - st).count() < t * 950) {
		ll x = rnd(ansx - rdfy, ansx + (rdfy >> 1));
		ll y;
		if (fa.first) {
			y = rnd(x + fa.first, ansy + rdfy);
		} else {
			rnd(ansy - rdfy, ansy + rdfy);
		}
		if (y < x) {
			swap(x, y);
		}
		pll ff = f(x, y);
		if (ff > fa) {
			ansx = x, ansy = y, fa = ff;
		}
	}
	if (ansx > l && __gcd(ansx - 1, ansy - 1) == 1) {
		--ansx, --ansy;
		if (ansx > l && __gcd(ansx - 1, ansy - 1) == 1) {
			--ansx, --ansy;
		}
	}
	
	write(ansx * g), space(), write(ansy * g), enter();
	*/
	return 0;
}
int main() {
//	st = high_resolution_clock().now();
	ll T;
	read(T);
	_T = T;
	while (T--) {
		rd = mt19937_64(345675342698ll);
		mian(_T - T);
	}
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

## 作者：Coding_JuRuo (赞：1)

## 题目链接

[Codeforces 2043D](https://codeforces.com/problemset/problem/2043/D)

## 题目大意

找到两整数 $a,b$ 满足 $l\le a\le b\le r$ $(1)$ 且 $\gcd(a,b)=g$ $(2)$，求 $b-a$ 的最大值。

## 思路分析

首先 $a,b$ 的最大公因数为 $g$，说明 $a,b$ 都是 $g$ 的倍数，即 $\dfrac{a}{g},\dfrac{b}{g}$ 都为整数，我们将 $(1)$ 式同除以 $g$，可得

$$
\dfrac{l}{g}\le\dfrac{a}{g}\le\dfrac{b}{g}\le\dfrac{r}{g}
$$

显然 $\dfrac{a}{g},\dfrac{b}{g}$ 都是整数，这导致它们不可能等于分数，所以不等式

$$
\biggm\lceil\dfrac{l}{g}\biggm\rceil\le \dfrac{a}{g}\le \dfrac{b}{g}\le\biggm\lfloor\dfrac{r}{g}\biggm\rfloor
$$

也应成立。

我们再计 $L=\biggm\lceil\dfrac{l}{g}\biggm\rceil,R=\biggm\lfloor\dfrac{r}{g}\biggm\rfloor,A=\dfrac{a}{g},B=\dfrac{b}{g}$，则可得

$$
L\le A\le B\le R
$$

同时由 $(2)$ 式及 $\dfrac{a}{g},\dfrac{b}{g}$ 都为整数，可得

$$
\gcd\bigg(\dfrac{a}{g},\dfrac{b}{g}\bigg)=1
$$

即

$$
\gcd(A,B)=1
$$

这就转化为 Atcoder arc137_a（[blog](https://www.luogu.com/article/tmuwwlyt)），暴力枚举即可

## 代码精讲

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t;
ll l,r,g;

ll gcd(ll a,ll b){
    if (b==0) return a;
    return gcd(b,a%b);
}
void calc(ll l,ll r,ll g){
    l=(l+g-1)/g,r/=g;
    for (ll i=r-l;i>=0;--i){
        for (ll j=l;j<=r-i;++j){
            if (gcd(j,j+i)==1){
                printf("%lld %lld\n",j*g,(j+i)*g); // 别忘记再把除掉的 g 乘回来
                return;
            }
        }
    }
    printf("-1 -1\n");
}
int main(){
    scanf("%d",&t);
    while (t--){
        scanf("%lld%lld%lld",&l,&r,&g);
        calc(l,r,g);
    }
    return 0;
}
```

---

