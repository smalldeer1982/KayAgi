# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3```

# 题解

## 作者：沉石鱼惊旋 (赞：10)

# 题目翻译

**本题是一道 I/O 交互题。**

有 $1\sim n$ 的数各 $2$ 个（共 $2n$ 个），现在拿走 $3$ 个互不相同的数（还剩 $2n-3$ 个）。

你可以进行不超过 $150$ 次的询问 `xor l r` 表示询问数值大小在 $[l,r]$ 内的数的异或和。找出这 $3$ 个拿走的数之后用 `ans a b c` 回答这 $3$ 个数。

$3\leq n\leq 10^{18}$。

询问要求：询问的 `xor l r` 需要满足 $1\leq l\leq r\leq n$。如果超过 $150$ 次询问交互库会返回 $-1$。

# 题目思路

下文约定 $\oplus$ 表示按位异或。

先刻画一下这个询问的本质。我们知道了 $x\oplus x=0,0\oplus x = x$。故两两相同的数会被抵消，那么 `xor l r` 其实就是在询问**被拿走的 $3$ 个数**，值在 $[l,r]$ 内的数的异或和。

一个比较朴素的想法是，我们可以直接二分出这个最大的一个和最小的一个，就是找到第一个前缀异或 `xor 1 k` 不为 $0$，找一个后缀异或 `xor k n` 不为 $0$ 的值，然后通过整体询问 `xor 1 n`，异或这个最大最小，求出这个中间值。

这个做法算是对了一半。考虑什么时候这个二分是错的，就是当 $a\oplus b\oplus c=0$ 的时候，此时二分不具有单调性。由于题目保证两两不同，$a\oplus b$ 之类的情况是不可能发生的，只有 $a\oplus b\oplus c=0$ 的时候二分没有单调性。

那不妨对 $a\oplus b\oplus c=0$ 的情况单独做。考虑这种情况有什么特殊的性质。这其实是告诉我们，**每个二进制位有偶数个 $1$**。

那么，最高位不可能是 $3$ 个都为 $0$，一定是 $2$ 个 $1$。我们从大到小枚举这个最高位。即询问形如 `xor 1 2^k-1` 的操作。如果询问到的异或不为 $0$，就说明最小值就是这个异或。

找到了最小值，我们可以和上面一样，二分出最大的那个值。二分左边界设为最小值 $+1$ 即可。

这样的话其实只有一开始的一次 `xor 1 n` 和两轮 $\log$ 级别的询问。上限是 $121$ 次。

# 完整代码

[CF submission 289523319](https://codeforces.com/contest/2036/submission/289523319)

这个 `xor_n` 函数是我一开始看错题导致的。我以为还要求一个 $1\sim n$ 的数的异或和。iee。略过即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll xor_n(ll n)
{
    ll t = n & 3;
    if (t & 1)
        return t / 2 ^ 1;
    return t / 2 ^ n;
}
ll query(ll l, ll r)
{
    cout << "xor " << l << ' ' << r << '\n';
    ll x;
    cin >> x;
    return x;
}
void solve()
{
    ll n;
    cin >> n;
    ll axbxc = query(1, n);
    if (axbxc == 0)
    {
        for (int i = 60; i >= 0; i--)
        {
            if ((1LL << i) - 1 > n)
                continue;
            ll t = query(1, (1LL << i) - 1);
            if (t)
            {
                ll a = t;
                ll L = a + 1, R = n;
                ll c = 1;
                while (L <= R)
                {
                    ll mid = L + R >> 1;
                    if (query(mid, n))
                        L = (c = mid) + 1;
                    else
                        R = mid - 1;
                }
                cout << "ans " << a << ' ' << (axbxc ^ a ^ c) << ' ' << c << endl;
                return;
            }
        }
    }
    else
    {
        ll L = 1, R = n, a = n;
        while (L <= R)
        {
            ll mid = L + R >> 1;
            if (query(1, mid))
                R = (a = mid) - 1;
            else
                L = mid + 1;
        }
        L = 1, R = n;
        ll c = 1;
        while (L <= R)
        {
            ll mid = L + R >> 1;
            if (query(mid, n))
                L = (c = mid) + 1;
            else
                R = mid - 1;
        }
        cout << "ans " << a << ' ' << (axbxc ^ a ^ c) << ' ' << c << endl;
    }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：luogu_gza (赞：5)

评分 2400 虚高啊，纯粹是因为没人写。

首先不难注意到 $q(1,n)=a \oplus b \oplus c$。

如果 $q(1,n)>0$ 我们用二分求出 $a$ 和 $b$ 然后 $c=q(1,n) \oplus a \oplus b$

如果 $q(1,n)=0$，不妨假设 $a<b<c$，那么我们考虑一定存在一位使得 $a$ 这一位是 $0$，$b$ 这一位是 $1$，$c$ 这一位是 $1$，我们可以先二分出 $a$，然后得到了 $q(a+1,n)$ 是多少（肯定 $>0$），套用 $q(1,n)>0$ 的方法即可。

来自我在一个群的口胡记录。

---

## 作者：MrPython (赞：3)

本题两种情况分类讨论。设有 $x<y<z$。

当 $x \oplus y \oplus z \neq 0$ 时，$1$ 到 $x-1$ 的所有数都是 $0$。我们可以二分出第一个 $i$ 使得 $\operatorname{ask}(1,i)\neq0$，$x$ 即为 $i$。询问次数为 $\log_2 n$。

当 $x \oplus y \oplus z = 0$ 时，直接二分就不好使了。不过仔细分析一些例子可以发现：一定可以找到一个 $p$，满足 $x<k$ 且 $k\le y<z$。$k$ 最大不超过 $\log_2 n$，直接枚举即可。
> 证明：当答案的某位是 $0$ 时，$x,y,z$ 中有零个或两个当前位为 $1$。考虑 $z$ 的最高位 $p$，其为 $1$，那么 $x$ 或 $y$ 中有且只有一个第 $p$ 位也为 $1$。为了保证 $x<y$，我们选择 $y$ 的第 $p$ 位为 $1$，而 $x$ 的第 $p$ 位为 $0$。这时，便有 $x<2^p\le y<z$。

找到 $x$ 后，$y$ 和 $z$ 一定在 $[x+1,n]$ 中，在该区间内用类似的方法二分出 $b$，则最后一个数就一定在 $[b+1,n]$ 中，直接问一次就好了。

使用 C++20，希望参选本题最优美代码奖。
```cpp
#include <algorithm>
#include <iostream>
#include <ranges>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
uli ask(uli l, uli r) {
  fout << "xor " << l << ' ' << r << endl;
  uli ans;
  fin >> ans;
  return ans;
}
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    uli n;
    fin >> n;
    uli x = ask(1, n) == 0
                ? [n] {
                    for (uli i = 2; i < n; i *= 2) {
                      uli res = ask(1, i - 1);
                      if (res != 0) return res;
                    }
                    exit(300);
                  }()
                : [n] {
                    auto view = ranges::views::iota(1ull, n + 1) |
                                ranges::views::transform(
                                    [](uli v) -> bool { return ask(1, v); });
                    auto it = ranges::lower_bound(view, true);
                    return uli(it - view.begin()) + 1ull;
                  }();
    uli y = [n, x] {
      auto view = ranges::views::iota(x + 1, n + 1) |
                  ranges::views::transform(
                      [x](uli v) -> bool { return ask(x + 1, v); });
      auto it = ranges::lower_bound(view, true);
      return uli(it - view.begin()) + (x + 1);
    }();
    uli z = ask(y + 1, n);
    fout << "ans " << x << ' ' << y << ' ' << z << endl;
  }
  return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

假设缺失的三个数为 $a<b<c$，先询问 $1\sim n$ 可得到 $s=a\oplus b\oplus c$。

若 $s\ne 0$，那么可以二分出 $c$，因为询问 $[1,c)$ 的结果不会是 $s$。求出 $c$ 后可以仿照刚刚的方法二分出 $b$，因为询问 $[1,b)$ 的结果不会是 $s\oplus c$。

麻烦的是 $s=0$，这时候感觉啥信息都没得到。但其实这表明 $a,b,c$ 三个数在二进制下的任何一位上 $1$ 都出现偶数次，而它们每个数自身的最高位一定为 $1$。所以可以从高到低枚举最高位 $i$ 查询 $[1,2^i)$，第一次不为 $0$ 的值即为 $a$，因为 $b\oplus c=a$。得到 $a$ 之后就可以仿照前面二分出 $b$ 得到 $c$ 了。

# Code

```cpp
#include<bits/stdc++.h>
int T;
long long n,s,x;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		if(n==3){
			puts("ans 1 2 3");fflush(stdout);
			continue;
		}
		printf("xor 1 %lld\n",n);fflush(stdout);
		scanf("%lld",&s);
		if(s){
			long long l=1,r=n,res;
			while(l<=r){
				long long mid=l+r>>1;
				printf("xor 1 %lld\n",mid);fflush(stdout);
				scanf("%lld",&x);
				if(s==x)res=mid,r=mid-1;
				else l=mid+1;
			}
			long long c=res;
			s^=res;
			l=1;r=res-1;
			while(l<=r){
				long long mid=l+r>>1;
				printf("xor 1 %lld\n",mid);fflush(stdout);
				scanf("%lld",&x);
				if(s==x)res=mid,r=mid-1;
				else l=mid+1;
			}
			printf("ans %lld %lld %lld\n",s^res,res,c);fflush(stdout);
		}else{
			for(int i=60;~i;--i){
				if((1ll<<i)-1>n)continue;
				printf("xor 1 %lld\n",(1ll<<i)-1);fflush(stdout);
				scanf("%lld",&x);
				if(!x)continue;
				long long c=x;
				long long l=x+1,r=n,res;
				printf("xor %lld %lld\n",x+1,n);fflush(stdout);
				scanf("%lld",&s);
				while(l<=r){
					long long mid=l+r>>1;
					printf("xor %lld %lld\n",mid,n);fflush(stdout);
					scanf("%lld",&x);
					if(s==x)res=mid,l=mid+1;
					else r=mid-1;
				}
				printf("ans %lld %lld %lld\n",s^res,res,c);fflush(stdout);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：1)

XorForces。每日被 Hack。

首先考虑异或的性质：

**壹** 若 $x\oplus y=0$，则 $x=y$。

**壹.证明** 若 $x\oplus y=0$，则 $x$ 和 $y$ 二进制表示下每一位的值都相同，显然只有两个数完全相同时才能有这样的性质。因此得证。

**贰** 若 $x\oplus y\neq0$，则 $x\neq y$。

**贰.证明** 若 $x\oplus y\neq 0$，则令 $z=x\oplus y$ 且 $z$ 的第 $i$ 位的值不为 $0$。此时 $x$ 的第 $i$ 位的值和 $y$ 的第 $i$ 位的值不同。因此 $x$ 和 $y$ 的值不能相等。因此得证。

**叁** 若 $x\oplus y\oplus z=0$ 且 $x,y,z$ 互不相同，则钦定 $x<y<z$，设 $\text{High}(x)$ 表示 $x$ 二进制表示下最高的为 $1$ 位是第几位。则必有 $\text{High}(x)<\text{High}(y)=\text{High}(z)$。

**叁.证明**

首先 $\text{High}(x)$ 函数在 $x\in\mathbb{N}$ 上单调不递减。证明显然。

若 $\text{High}(y)<\text{High}(z)$，则 $\text{High}(z)$ 位上必然只有一个 $1$，异或完后这一位的值还是 $1$，无法清零。若 $\text{High}(x)=\text{High}(y)=\text{High}(z)$ 则 $\text{High}(z)$ 位上必然有 $3$ 个 $1$，无法清零。因此当且仅当 $\text{High}(x)<\text{High}(y)=\text{High}(z)$ 时 $\text{High}(z)$ 位有 $2$ 个 $1$ 可以清零，**有可能**满足 $x\oplus y\oplus z=0$ 的条件。

------

考虑开始做这个题。令三个只有一次出现的数的值分别为 $A,B,C$ 并满足 $A<B<C$。则：

+ $\text{xor}(1,n)\neq 0$ 即 $A\oplus B\oplus C\neq0$。则此时在给定集合 $S=\lbrace A,B,C\rbrace$ 中任选子集 $S'\sube S$ 且 $S'\neq\emptyset$，均满足 $S'_0\oplus S'_1\oplus\ldots\oplus S'_{k-1}\neq 0$（$k=|S'|$）。因此直接在值域上先后以前缀 / 后缀二分答案，可以在 $2\log V$ 次询问内得出结果。然后询问 $[A+1,C-1]$ 这个值域区间，即可以得到 $B$ 的值。
+ $\text{xor}(1,n)=0$ 即 $A\oplus B\oplus C=0$。则此时上面的贪心二分做法显然可以被 hack 掉。根据上面的**结论叁**可以得知若 $A\oplus B\oplus C=0$ 且 $A<B<C$ 则 $\text{High}(A)<\text{High}(B)=\text{High}(C)$。因此考虑 $\log V$ 次询问按位枚举得到 $A$ 的最高位。此时该前缀值域内有且仅有 $A$ 一个元素。然后一次询问得到 $A$ 的值。剩下的后缀值域区间内有 $B$，$C$ 两个不相同的元素且满足 $B<C$。因此直接在后缀值域的前缀上贪心二分 $\log V$ 次询问找出 $B$ 的值，随后对剩余的后缀值域一次询问得出 $C$ 的值即可。

总询问次数为 $2\log V\approx 120$ 级别，附带常数不超过 $2$，总询问次数最多为 $120+2=122<150$ 次，可以通过问题。

代码：

```cpp
namespace ttq012 {

int op(int x) {
    if (x % 4 == 0) {
        return x;
    } else if (x % 4 == 1) {
        return 1;
    } else if (x % 4 == 2) {
        return x + 1;
    } else {
        return 0;
    }
}
int calc(int l, int r) {
    return op(l - 1) ^ op(r);
}
mt19937_64 mt(time(0));
int n;
void run() {
    int T = read();
    while (T--) {
        n = read();
        cout << "xor 1 " << n << endl;
        int o ; cin >> o;
        vector<int> result;
        if (o != 0) {
            int l = 1, r = n, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                cout << "xor 1 " << mid << endl;
                int o ; cin >> o;
                if (!o) {
                    l = mid + 1;
                } else {
                    r = mid - 1, best = mid;
                }
            }
            assert(~best);
            result.eb(best);
            l = 1, r = n, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                cout << "xor " << mid << ' ' << n << endl;
                int o ; cin >> o;
                if (!o) {
                    r = mid - 1;
                } else {
                    l = mid + 1, best = mid;
                }
            }
            assert(~best);
            result.eb(best);
            cout << "xor " << result[0] + 1 << ' ' << result[1] - 1 << endl;
            int o ; cin >> o;
            result.eb(o);
        } else {
            int now = 0;
            for (int i = 60; ~i; --i) {
                if (now + (1ll << i) - 1 <= n) {
                    cout << "xor 1 " << now + (1ll << i) - 1 << endl;
                    int o ; cin >> o;
                    if (o) {
                        now = 1ll << i;
                        break;
                    }
                }
            }
            --now;
            cout << "xor " << 1 << ' ' << now << endl;
            cin >> now;
            result.eb(now);
            int l = now + 1, r = n, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                cout << "xor " << now + 1 << ' ' << mid << endl;
                int o ; cin >> o;
                if (!o) {
                    l = mid + 1;
                } else {
                    r = mid - 1, best = mid;
                }
            }
            result.eb(best);
            cout << "xor " << result[1] + 1 << ' ' << n << endl;
            int o ; cin >> o;
            result.eb(o);
        }
        cout << "ans ";
        sort(result.begin(), result.end());
        for (auto &x : result) {
            cout << x << ' ';
        }
        cout << endl;
    }
}

}


signed main() {
    ttq012::run();
    return 0;
}

/*



*/
```

---

## 作者：wly09 (赞：0)

题解行文按照本人做题时的思路。

记三个答案为 $a,b,c,a<b<c$。

## 三个数异或和非零

首先，出现两次的数相当于没有出现，因此一个比较一眼的思路是二分前缀异或的前缀零结尾的位置，下一个位置显然就是 $a$ 的位置。

$b$ 的做法一样，起点改成 $a+1$ 就行；$c$ 问一次就好了。

但是你发现若 $a,b,c$ 的异或和恰好为 $0$，刚才的做法就炸了。

我们在最开始询问一次整个值域，确定三个数的异或和，对上述情况单独处理。

## 三个数异或和为零

我们注意到 $a,b,c$ 任意一位不可能均为 $1$，否则与 $a\oplus b\oplus c$ 矛盾（这里 $\oplus$ 表示二进制按位异或）。同样的，任意一位不能只有一个 $1$。那么显然 $b,c$ 位数相同且大于 $a$ 的位数。

记 $b,c$ 的位数均为 $k$，则显然 $a\le 2^{k-1}-1<b<c\le 2^{k}-1$，那么询问 $[1,2^{k-1}-1]$ 的结果一定是 $a$；如果询问区间中 $2$ 的指数变为 $k$ 或更大的数，询问结果一定是零。

因此，我们从大到小枚举 $i$，每次询问 $[1,2^i-1]$，询问到的第一个非零值就是 $a$。

接下来的过程与“三个数异或和为零”的做法类似，不再重复。

一些不清楚的细节参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int64_t fast_log2(int64_t x) { return 63 - __builtin_clzll(x); }

int64_t ask(int64_t l, int64_t r) {
  cout << "xor " << l << ' ' << r << endl;
  int64_t v;
  cin >> v;
  if (v == -1)
    exit(1);
  return v;
}

int64_t bs(int64_t st, int64_t n) {
  int64_t l = st - 1, r = n;
  while (l < r) {
    int64_t mid = ((r - l + 1) >> 1) + l;
    if (ask(st, mid))
      r = mid - 1;
    else
      l = mid;
  }
  return l + 1;
}

void solve0(int64_t n) {
  int64_t x = (1ll << fast_log2(n)) - 1;
  int64_t a, st;
  for (;; x >>= 1) {
    if (x == 1) { a = 1, st = 2; break; }
    int64_t ans = ask(1, x);
    if (ans) { a = ans, st = x + 1; break; }
  }
  int64_t b = bs(st, n);
  int64_t c = a ^ b;
  cout << "ans " << a << ' ' << b << ' ' << c << endl;
}

void solve() {
  int64_t n;
  cin >> n;
  int64_t sum = ask(1, n);
  if (sum == 0) return solve0(n);
  int64_t l = 0, r = n;
  int64_t x = bs(1, n);
  int64_t y = bs(x + 1, n);
  int64_t z = sum ^ x ^ y;
  cout << "ans " << x << ' ' << y << ' ' << z << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
```

---

## 作者：CJ_Fu (赞：0)

## [CF2036G Library of Magic](https://codeforces.com/problemset/problem/2036/F)

交互题。现有一个 $1\sim n$ 的整数序列，每个数有 2 个，在该序列里选走 3 个不同的数，求出选走的这些数。可以向交互库发起不超过 $150$ 次询问形如：
- `xor l r` 返回数值在 $[l,r]$ 之间的数的异或和。

$n\le 10^{18}$

需要一定智慧的一题。

考虑到异或有性质 $x\oplus x=0$，所以区间 $[l,r]$ 的数的异或和其实就是区间内被选走的数的异或和。

不妨设选走的这 3 个数分别为 $a<b<c$。查一次 $[1,n]$ 的异或和可以得到 $t=a\oplus b\oplus c$ 的值。据此分类讨论：
- $t\neq 0$。这种比较好考虑。对于这个数列的前缀异或和序列 $p$，具有一定的单调性，即 $p_1\sim p_{a-1}=0,p_{a}\sim p_{b-1}=a,p_{b}\sim p_{c-1}=a\oplus b,p_{c}\sim p_{n}=t$。我们不关心具体数值，只关心其是否大于 0，即可二分出 $a$ 的位置。同理也可根据其后缀异或序列单调性求出 $c$。进而算出 $b=a\oplus c\oplus t$。
- $t=0$。这就不能用上面的方法了，因为 $p$ 不单调了（形如 `00001111000`，1 表示大于 0 的数）。考虑从 $t=0$ 上获取信息。   
    即 $a\oplus b\oplus c=0,a=b\oplus c$。由于上述问题，对于一个区间 $[l,r]$ 中的断点 $mid$，可能会出现 $mid$ 左右的异或和均为 0 的情况。但是事实是一边有 3 个数，另一边没数（不可能出现两边都有数的情况，因为 3 个数都不同，任意 2 个数异或都一定不为 0）。我们需要找到一个 $mid$ 能让我们在这种情况下也能正确的判断哪一边有数。  
    当我们取 $mid=2^x-1,x=\lfloor\log_2 (r-l+1)\rfloor$ 时，所有 $[mid+1,r]$ 的数中任取两个数的异或和均 $\le mid$（二进制下位数相等且最高位都为 1，异或完就少了一位，即 $<2^x$），即 $b,c>mid,a\le mid$，不合法；任取 $[l,mid]$ 中的两个数，由于位数不够，异或完还是 $<2^x$，所以合法，此时我们就把范围缩小到了 $[l,mid]$，循环做这件事直到出现某一边异或和不为 0，即转化为 $t\neq 0$ 的情况。

综上查询次数最劣为为做两遍二分，$120$ 次左右。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n;
bool check(int l,int r){
    cout<<"xor "<<l<<' '<<r<<'\n';
    cout.flush();
    int ret;
    cin>>ret;
    return ret;
}
void solve(){
    ck1=ckn=0;
    cin>>n;
    if(n==3){
        cout<<"ans 1 2 3\n";
        cout.flush();
        return;
    }
    cout<<"xor 1 "<<n<<'\n';
    cout.flush();
    int ret;
    cin>>ret;
    if(ret){
        int l=1,r=n,posl=1,posr=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(1,mid)){
                r=mid-1;
                posl=mid;
            }else{
                l=mid+1;
            }
        }
        l=1,r=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid,n)){
                l=mid+1;
                posr=mid;
            }else{
                r=mid-1;
            }
        }
        cout<<"ans "<<posl<<' '<<(ret^posl^posr)<<' '<<posr<<'\n';
        cout.flush();
    }else{
        int mx=log2(n),nmid=0;
        for(int i=mx;i>=1;i--){
            int r=min((1ll<<(i+1))-1,n),l=(1ll<<i);
            if(check(l,r)){
                nmid=l;
                break;
            }
        }
        int l=1,r=nmid,posl=nmid,posr=nmid;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(1,mid)){
                r=mid-1;
                posl=mid;
            }else{
                l=mid+1;
            }
        }
        l=nmid,r=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid,n)){
                l=mid+1;
                posr=mid;
            }else{
                r=mid-1;
            }
        }
        cout<<"ans "<<posl<<' '<<(posl^posr)<<' '<<posr<<'\n';
        cout.flush();
    }
}
signed main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：luqyou (赞：0)

# 思路

令 $a \le b \le c$。

考虑分情况讨论。

首先用一次询问得出 $a \bigoplus b \bigoplus c$ 的值。（下文记为 $x$）

接下来，若 $x = 0$，则说明 $a$ 的最高位一定与 $b,c$ 不同。所以我们可以询问所有 $[1,2^k-1]$，最小的非 $0$ 的 $k$ 的询问结果即 $a$ 的值。然后进行一次二分不难得出 $b,c$ 的值。

若 $x \neq 0$，则可以先通过一次二分得出 $a$，再通过一次二分得出 $b,c$。

# code

```cpp
void solve(){
    cin>>n;
    int l=1,r=n,pl=0,pr=0,num=ask(1,n);
    if(num==0){
        int x=0;
        for(int i=1;(1ll<<i)-1<=n;i++){
            if(ask(1,(1ll<<i)-1)){
                x=ask(1,(1ll<<i)-1);
                break;
            }
        }
        int l=x+1,r=n,res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(ask(x+1,mid)==x) r=mid-1;
            else res=mid,l=mid+1;
        }
        cout<<"ans "<<x<<" "<<(res+1)<<" "<<(x^(res+1))<<endl;
        return ;
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(ask(mid,n)==num) pl=mid,l=mid+1;
        else r=mid-1;
    }
    int num1=ask(pl+1,n);
    l=pl+1,r=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ask(mid,n)==num1) pr=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<"ans "<<pl<<" "<<pr<<" "<<(num^pl^pr)<<endl;
}
```

---

## 作者：Hoks (赞：0)

## 前言
小号 div3。

卡 G，10 发。

最后 $5$ min 意识到但还是傻逼写错了，赛后一发过。
## 思路分析
首先可以比较容易的想到二分。

先对整个查询出值，然后二分一次左端点，二分一次右端点。

然后最后异或一下得出来中间的那个值。

询问次数是 $2\log n$ 显然是没事的。

然后交上去挂死了。

这个时候我们发现有一种情况下 $a\oplus b\oplus c=0$ 时。

这时没有单调性不能二分。

但我们还是要用 $\log n$ 搞出来第一个数，这样就可以用二分 $\log n$ 解决剩下的两个数。

考虑观察性质。

我们发现若 $a<b<c$ 且 $a\oplus b\oplus c=0$，那么 $b,c$ 的最高位相等，且与 $a$ 的最高位不相等。

证明略，比较显然。

所以我们直接对于 $[1,2^i]$ 询问直到找到非 $0$，此时左端点就确定了，代价是 $\log n$，再去二分右端点就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e6+10,V=2e6,M=1e3+10,INF=1e18,p=13331,mod=1e9+7;
int n,m,q,cnt;char op[N];map<pair<int,int>,int>mp;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='<'||c=='>'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int ask(int l,int r)
{
    if(l>r) swap(l,r);l=max(l,1ll);r=min(r,n);
    if(mp.count({l,r})) return mp[{l,r}];
    printf("xor %lld %lld\n",l,r);fflush(stdout);cnt++;int x;cin>>x;
    if(x==-1) exit(0);return mp[{l,r}]=x;
}
inline void solve()
{
    cin>>n;mp.clear();int l=1,r=n,L,R,res=0,x=ask(l,r);
    if(x)
    {
        while(l<=r)
            if(ask(mid,n)==x) res=mid,l=mid+1;
            else r=mid-1;L=res;l=1,r=n;
        while(l<=r)
            if(ask(1,mid)==x) res=mid,r=mid-1;
            else l=mid+1;R=res;
        x=ask(L+1,R-1);
        printf("ans %lld %lld %lld\n",L,x,R);fflush(stdout);return;
    }int i=2;
    for(;i<=n;i*=2) if(ask(1,i-1)) break;i--;L=ask(1,i);
    l=i+1,r=n;x=ask(i+1,n);
    while(l<=r)
        if(ask(i+1,mid)==x) res=mid,r=mid-1;
        else l=mid+1;R=res;x=ask(1,n)^L^R;
    printf("ans %lld %lld %lld\n",L,x,R);fflush(stdout);
}
signed main()
{
    int T=1;
    cin>>T;
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：wmrqwq (赞：0)

这题 *2400 纯唐吧，感觉 *1800 差不多。

# 题目链接

[CF2036G Library of Magic(*2400)](https://luogu.com.cn/problem/CF2036G)

# 解题思路

注：$\oplus$ 表示异或运算。

首先我们想一个通解，就是先二分出第一个数和第三个数，然后第二个数就是所有数的异或和异或上这两个数，操作次数为 $2 \times \log n + 1$，可以通过。

但是有个情况特别难受，就是可能会出现中间有数字但是询问结果为 $0$ 的情况。

考虑何时会出现这种情况。

由于题目里保证删的数字不同，因此显然查询结果为 $0$ 时这个区间中只含 $0$ 或 $3$ 个数字。

于是我们先判断是否有 $ans1 \oplus ans2 \oplus ans3 = 0$，若不是，我们可以直接套用上述二分的做法。

否则，由于这三个数的异或和为 $0$，因此我们可以找到含有**最高**二进制位的两个数字，那么此时我们可以二分出这两个数字中的其中一个数字，另一个数字可以通过这两个数的异或和异或查询出来的数确定，剩下一个数可以通过所有数的异或和异或这两个数字的异或和确定。

操作次数 $2 \times \log n + 1$，可以通过。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n;
ll ans[10];
ll get(ll x,ll y)
{
	ll S=0;
	forl(i,1,3)
		if(x<=ans[i] && ans[i]<=y)
			S^=ans[i];
	return S;
}
ll ask(ll x,ll y)
{
	if(x>n)
		return 0;
	Min(y,n);
	cout<<"xor "<<x<<' '<<y<<endl;
	ll z;
	cin>>z;
//	z=get(x,y);
	return z;
}
void print(ll x,ll y,ll z){
	cout<<"ans "<<x<<' '<<y<<' '<<z<<endl;
}
ll pw(ll x){
	return 1ll<<x;
}
void solve()
{
    _clear();
	cin>>n;
	ans[1]=1;
	ans[2]=2;
	ans[3]=3;
	if(n==3)
	{
		print(1,2,3);
		return ;
	}
	if(ask(1,n)==0)
	{
//		cout<<"AWaDa!\n";
		forr(i,61,0)
		{
			ll num=ask(pw(i),pw(i+1)-1);
			if(num!=0 && !(num&pw(i)))
			{
		//		cout<<i<<endl;
				ll L=pw(i),R=pw(i+1)-1;
				while(L<R)
				{
					ll Mid=(L+R)/2;
					ll num=ask(pw(i),Mid);
					if(num==0)
						L=Mid+1;
					else if(ask(pw(i),Mid)&pw(i))
						R=Mid;
					else
						R=Mid;
				}
				ll _1=L,_2=num^L,_3=_1^_2;
				print(_1,_2,_3);
				return ;
			}
		}
		exit(-1);
	}
	else
	{
		ll all=ask(1,n);
		ll _1=0,_2=0,_3=0;
		ll L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(ask(1,Mid)==0)
				L=Mid+1;
			else
				R=Mid;
		}
		_1=L;
		L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R+1)/2;
			if(ask(Mid,n)==0)
				R=Mid-1;
			else
				L=Mid;
		}
		_3=L;
		_2=all^_1^_3;
		print(_1,_2,_3);
	}
}
int main()
{
    _t_=1;
    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

