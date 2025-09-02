# [ABC261E] Many Operations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc261/tasks/abc261_e

変数 $ X $ と、$ X $ の値を変更する $ N $ 種類の操作があります。操作 $ i $ は整数の組 $ (T_i,A_i) $ で表され、意味は次の通りです。

- $ T_i=1 $ のとき、$ X $ の値を $ X\ {\rm\ and}\ A_i $ に置き換える。
- $ T_i=2 $ のとき、$ X $ の値を $ X\ {\rm\ or}\ A_i $ に置き換える。
- $ T_i=3 $ のとき、$ X $ の値を $ X\ {\rm\ xor}\ A_i $ に置き換える。

変数 $ X $ を値 $ C $ で初期化した状態から、以下の処理を順に実行してください。

- 操作 $ 1 $ を行い、操作後の $ X $ の値を出力する。
- 続けて、操作 $ 1,2 $ を順に行い、操作後の $ X $ の値を出力する。
- 続けて、操作 $ 1,2,3 $ を順に行い、操作後の $ X $ の値を出力する。
- $ \vdots $
- 続けて、操作 $ 1,2,\ldots,N $ を順に行い、操作後の $ X $ の値を出力する。
 
$ {\rm\ and},\ {\rm\ or},\ {\rm\ xor} $ とは 非負整数 $ A,\ B $ の $ {\rm\ and},\ {\rm\ or},\ {\rm\ xor} $ は、以下のように定義されます。 - $ A\ {\rm\ and}\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち両方が $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
- $ A\ {\rm\ or}\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち少なくとも一方が $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
- $ A\ {\rm\ xor}\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうちちょうど一方が $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ {\rm\ and}\ 5\ =\ 1 $、 $ 3\ {\rm\ or}\ 5\ =\ 7 $、 $ 3\ {\rm\ xor}\ 5\ =\ 6 $ となります。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ T_i\ \leq\ 3 $
- $ 0\leq\ A_i\ \lt\ 2^{30} $
- $ 0\leq\ C\ \lt\ 2^{30} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

最初、$ X $ の値は $ 10 $ です。 - 操作 $ 1 $ を行うと $ X $ の値は $ 9 $ になります。 - 続けて操作 $ 1 $ を行うと $ X $ の値は $ 10 $ になり、さらに操作 $ 2 $ を行うと $ 15 $ になります。 - 続けて操作 $ 1 $ を行うと $ X $ の値は $ 12 $ になり、さらに操作 $ 2 $ を行うと $ 13 $ に、さらに続けて操作 $ 3 $ を行うと $ 12 $ になります。

## 样例 #1

### 输入

```
3 10
3 3
2 5
1 12```

### 输出

```
9
15
12```

## 样例 #2

### 输入

```
9 12
1 1
2 2
3 3
1 4
2 5
3 6
1 7
2 8
3 9```

### 输出

```
0
2
1
0
5
3
3
11
2```

# 题解

## 作者：liangbowen (赞：9)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc261_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17134234.html)

这题另外两篇题解写的啥啊，这里提供一个非常好理解的做法。

## 思路

对于这种一堆位运算的题目，我们很容易想到**按位考虑**。


准备两个 tag，一个是 $cov$ 表示是否有覆盖操作，一个是 $rev$ 表示是否有反转操作。作用见下文。（为了方便描述，我直接把每一位上的树称作原数了）

首先看 $\text{and}$ 的情况。我们分类：

+ 如果 $a_i = 0$，那么不管原数是什么，到这一步，原数必定会变成 $0$。所以 $cov=0$，$rev$ 清空。
+ 如果 $a_i = 1$，什么也不会发生。

$\text{or}$ 的情况是类似的：

+ 如果 $a_i = 0$，什么也不会发生。
+ 如果 $a_i = 1$，那么不管原数是什么，到这一步，原数必定会变成 $1$。所以 $cov=1$，$rev$ 清空。

最后是稍有不同的 $\text{xor}$ 操作。可以发现，这个操作不会产生覆盖，所以我们将会改变 $rev$。

具体地，当 $a_i = 1$，说明会进行一次反转，所以 $rev$ 增加。

---

于是在每一步过后，我们都有当前的 $cov$ 与 $rev$。

如果存在 $cov$，那么可以理解为，今后的全部操作，原数都直接在这里开始。所以直接把原数变成 $cov$。

覆盖完后直接 $rev$ 即可。每一步计算完后存入 $ans_i$ 的对应位置。

所以另外那两篇题解搞 $\text{bitset}$ 和 DP 是在干什么？

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
int op[N], a[N], ans[N];
int main()
{
	int n, val;
	scanf("%d%d", &n, &val);
	for (int i = 1; i <= n; i++) scanf("%d%d", &op[i], &a[i]);
	for (int d = 0; d <= 30; d++)
	{
		bool sum = (val & (1 << d)); int cov = -114514, rev = 0;
		for (int i = 1; i <= n; i++)
		{
			bool x = (a[i] & (1 << d));
			if (op[i] == 1) {sum &= x; if (x == 0) cov = 0, rev = 0;}
			if (op[i] == 2) {sum |= x; if (x == 1) cov = 1, rev = 0;}
			if (op[i] == 3) {/*sum ^= x;*/ if (x == 1) rev++;}
			
			if (cov != -114514) sum = cov;
			if (rev & 1) sum ^= 1;
			if (sum) ans[i] += (1 << d);
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：2)

## [ABC261E](https://atcoder.jp/contests/abc261/tasks/abc261_e) 题解
### 题目大意
直接摘录题目翻译了。~~反正是我翻译的~~

我们有一个正整数 $X$，当然还有 $N$ 条位运算操作，按照 $T_i\ A_i$ 输入，其中
+ $T_i=1$ 表示该操作为 $\operatorname{and}$；

+ $T_i=2$ 表示该操作为 $\operatorname{or}$；

+ $T_i=3$ 表示该操作为 $\operatorname{xor}$。

第 $i$ 条操作把当前的 $X$ 执行 $1,2,\cdots ,i$ 共 $i$ 条操作。 执行完成后输出 $X$ 的值。

### 暴力解法
我们对于 $X$ 按照题意进行暴力操作。复杂度 $O(N^2)$，因为这不是本文讨论终点，所以不详细展开。
### 正解
我们深知，位运算下每一位是互不影响的。所以我们把每一位分离讨论。
***
定义 $\operatorname{calc}(t,a,b)$ 表示按照题意对 $a$ 和 $b$ 执行 $t$ 号位运算。

定义 $F[k,p,t]$ 表示某个二进制数的第 $p$ 位为 $k(0\leq k\leq 1)$，当前处理完前 $i$ 个； $b[i,p]$ 表示二进制数 $i$ 的二进制第 $p$ 位。明显有递推式 $F[k,p,t]=\operatorname{calc}(T_i,F[k,p,t-1],b[A_i,p])$。
***
有了 $F$ 和 $b$，这道题就解决了一半。

我们可以把每次操作完后的答案赋值给输入的 $X$。

接下去，我们按照题意模拟：

令 $B$ 为 $\log R$，其中 $R$ 是 $A_i$ 的范围。

对于 $\forall i\in [1,n]$ ，答案显然为 $\sum^{B-1}_{p=0} 2^p\times f[b[c,p],p,i]$。

至此，本题已得到完美解决。

### 代码
时间复杂度 $O(N\cdot B)$。

[code link](https://atcoder.jp/contests/abc261/submissions/33467276)

---

## 作者：normalpcer (赞：1)

朴素的做法是拆位考虑。若干次操作之后，一个位上可能的变化有以下几种：
- 不变。
- 反转。
- 赋值为 $0$。
- 赋值为 $1$。

于是有以下的拆位做法：
```cpp
if (type == 1) {
    // and
    // & 0 是无条件赋值为 0，& 1 不变
    for (i32 i = 0; i < maxBits; i++) {
        if ((value & (1U << i)) == 0)  bits[i] = Assign0;
    }
} else if (type == 2) {
    // or
    // | 1 为无条件赋值为 1
    for (i32 i = 0; i < maxBits; i++) {
        if (value & (1U << i))  bits[i] = Assign1;
    }
} else if (type == 3) {
    // xor
    for (i32 i = 0; i < maxBits; i++) {
        if (value & (1U << i)) {
            bits[i] = [&]() -> ModifyType {
                switch (bits[i]) {
                case Assign0:  return Assign1;
                case Assign1:  return Assign0;
                case Invert:  return None;
                case None:  return Invert;
                default:  assert(false), __builtin_unreachable();
                }
            }();
        }
    }
}
```

我们可以使用两个整数的每一位 `assignBit`、`invertBit` 来表示这一位的变化方式。
- `00`：不变。
- `01`：反转。
- `10`：赋 $0$。
- `11`：赋 $1$。

修改只需要按照如下方式：
```cpp
if (type == 1) {
    // value 所有为 0 的位赋 0
    assignBits |= ~value;
    invertBits &= value;
} else if (type == 2) {
    // value 为 1 的位赋 1
    assignBits |= value;
    invertBits |= value;
} else if (type == 3) {
    invertBits ^= value;
}
```

接下来获取答案。需要赋值为 $1$ 和 $0$ 的位（`assignBit` 对应位为 $1$）分别进行赋值，其他的（`assignBit` 对应位为 $0$，`invertBit` 对应位为 $1$）通过异或反转即可。

代码如下：
```cpp
using i32 = int;
void solve() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    i32 N, C;  std::cin >> N >> C;

    // 记录每一位上的修改
    i32 assignBits = 0;
    i32 invertBits = 0;
    // 00：不变；01：反转；10：赋 0；11：赋 1

    i32 ans = C;
    for (i32 _ = 0; _ < N; _++) {
        i32 type, value;  std::cin >> type >> value;
        if (type == 1) {
            // value 所有为 0 的位赋 0
            assignBits |= ~value;
            invertBits &= value;
        } else if (type == 2) {
            // value 为 1 的位赋 1
            assignBits |= value;
            invertBits |= value;
        } else if (type == 3) {
            invertBits ^= value;
        }

        ans |= assignBits & invertBits;
        ans &= ~(assignBits & ~invertBits);
        ans ^= (~assignBits & invertBits);
        std::cout << ans << endl;
    }
}
```

---

## 作者：chengning0909 (赞：1)

# abc 261 e

## 题意

给定变量 $X$，有 $N$ 种操作，第 $i$ 次操作用一个数对 $(T_i, A_i)$ 描述：

- $T_i = 1, 2, 3$ 分别表示将 $X$ 替换为 $X \ and \ A_i, X \ or \ A_i$ 和 $X \ xor \ A_i$。

将 $X$ 初始化为 $C$，并做以下事情：

- 对 $X$ 做操作 $1$，并输出。

- 对 $X$ 做操作 $1, 2$，并输出。

- $\dots$

- 对 $X$ 做操作 $1, 2, \dots, N$，并输出。

## 思路

如果我们每次都从头开始做，时间复杂度会达到 $O(N ^ 2)$，会超时，那么我们应该怎么优化呢？

因为这里是位运算，所以我们可以考虑从每一位入手。

令 $f_{0 / 1, i, j}$ 表示 $X$ 的第 $i$ 位为 $0 / 1$，做到第 $j$ 次操作时的答案。

那么，每次询问只要枚举当前的 $X$ 的每一位，将答案合并起来即可。

## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int n, c, t[N], a[N], f[2][35][N], l;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> t[i] >> a[i];
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 30; j++) {
      f[i][j][0] = i;
      for (int k = 1; k <= n; k++) {
        int v = (a[k] >> j) & 1;
        if (t[k] == 1) {
          f[i][j][k] = f[i][j][k - 1] & v;
        } else if (t[k] == 2) {
          f[i][j][k] = f[i][j][k - 1] | v;
        } else {
          f[i][j][k] = f[i][j][k - 1] ^ v;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int ans = 0;
    for (int j = 0, k = c; j < 30; j++, k >>= 1) {
      ans += f[k & 1][j][i] * (1 << j);
    }
    cout << ans << '\n';
    c = ans;
  }
  return 0;
}
```

---

## 作者：Tsawke (赞：1)

# [[ABC261E] Many Operations](https://www.luogu.com.cn/problem/AT_abc261_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC261E)

## 题面

给定正整数 $ X $，给定 $ n $ 条运算，每条包含 $ T_i, A_i $，代表若：

$ T_i = 1 $，则 $ X \leftarrow X \land A_i $。

$ T_i = 2 $，则 $ X \leftarrow X \lor A_i $。

$ T_i = 3 $，则 $ X \leftarrow X \oplus A_i $。

对于第 $ i $ 条运算，会顺序执行 $ [1, i] $ 的所有运算，求最终 $ X $ 的值。

## Solution

发现这个执行类似前缀和，但对于不同的初始的数执行这些按位操作的时候结果是不同的，或者说其不能直接合并，所以不能一般地做前缀和。

不难发现按位运算的性质，即每一位之间都是独立的，不会像加法那样由进位操作，所以不难想到对于每一位分开考虑，显然初始时对应位只能为 $ 0 $ 或 $ 1 $，分别做一下前缀和即可。然后按位将 $ X $ 拆分并分别运算再组合即可。

同时显然我们可以通过 `bitset` 的构造函数来快速将十进制转二进制，并通过 `bitset` 的 `to_ulong()` 函数转为 `unsigned long`，并通过 bitset 加速按位运算。

最终复杂度 $ O(n\dfrac{\log X}{w}) $，因为此处 $ \log $ 最大不超过 $ 32 $，所以我们可以认为复杂度是线性的，即 $ O(n) $。

Update：复杂度还是 $ O(n\log X) $ 的，因为最后计算法案的时候还有个枚举。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;



template < typename T = int >
inline T read(void);

int X, N;
int T[210000];
bitset < 32 > A[210000];
bitset < 32 > sum0[210000], sum1[210000];

int main(){
    sum0[0].reset(), sum1[0].set();
    N = read(), X = read();
    for(int i = 1; i <= N; ++i){
        T[i] = read(), A[i] = bitset < 32 >(read());
        switch(T[i]){
            case 1:{
                sum0[i] = sum0[i - 1] & A[i];
                sum1[i] = sum1[i - 1] & A[i];
                break;
            }
            case 2:{
                sum0[i] = sum0[i - 1] | A[i];
                sum1[i] = sum1[i - 1] | A[i];
                break;
            }
            case 3:{
                sum0[i] = sum0[i - 1] ^ A[i];
                sum1[i] = sum1[i - 1] ^ A[i];
                break;
            }
            default:break;
        }
    }
    bitset < 32 > ans(X);
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 32; ++j)
            ans[j] = ans[j] ? sum1[i][j] : sum0[i][j];
        printf("%lu\n", ans.to_ulong());
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_24 初稿

update-2022_12_24 修改一个错误

---

## 作者：LionBlaze (赞：0)

注意到各位独立，考虑对于每一位考虑。

问题也就转化为了 $X$ 和 $A_i$ 都是一位二进制整数的情况，这种情况非常简单，我们只需要用 $f_{i,j}$ 表示原本 $X=i$，经过前 $j$ 次操作（即，$1,2,3,\dots,j$）之后变成了什么，其中 $0 \le i \le 1$。转移也非常简单，令 $\operatorname{aox}$ 为当前位运算操作，那么有 $f_{i,j}=f_{i,j-1} \operatorname{aox}A_i$ 即可。

什么你问答案怎么处理？显然 $i=1\dots N$，每一次 $X \gets f_{X,i}$ 即可。

然后做完了。

```cpp
#include <cstdio>

using namespace std;

int f[200005][35][5];

int main()
{
	int n, c;
	scanf("%d%d", &n, &c);
	for (int i = 0; i < 30; i++)
	{
		f[0][i][0] = 0;
		f[0][i][1] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int t, a;
		scanf("%d%d", &t, &a);
		for (int j = 0; j < 30; j++)
		{
			int r = a >> j & 1;
			if (t == 1)
			{
				f[i][j][0] = f[i - 1][j][0] & r;
				f[i][j][1] = f[i - 1][j][1] & r;
			}
			if (t == 2)
			{
				f[i][j][0] = f[i - 1][j][0] | r;
				f[i][j][1] = f[i - 1][j][1] | r;
			}
			if (t == 3)
			{
				f[i][j][0] = f[i - 1][j][0] ^ r;
				f[i][j][1] = f[i - 1][j][1] ^ r;
			}
		}
		for (int j = 0; j < 30; j++)
		{
			c = c & (0x7fffffff - (1 << j)) | ((f[i][j][(c >> j) & 1]) << j);
		}
		printf("%d\n", c);
	}
	return 0;
}
```

[sub](https://atcoder.jp/contests/abc261/submissions/66015073)。

考虑优化（常数）。

我们是逐位考虑的，能不能打包到一起？当然是可以的。

我们用 $k_{i,0}$ 表示“开始时全都是 $0$，经过 $i$ 次操作会变成什么样”，$k_{i,1}$ 同理（开始时是 $2^{30}-1$）。

什么你问怎么处理答案？如果 $X$ 的某一位为 $0$ 就用 $k_{i,0}$ 转移，为 $1$ 就用 $k_{i,1}$，然后滚动数组处理 $k$ 即可，只需要两个辅助变量。

至此，我们就是用高超的位运算技巧解决了这题。实际上速度也快了很多。

```cpp
#include <cstdio>

using namespace std;

int main()
{
	int n, c;
	scanf("%d%d", &n, &c);
	int k0 = 0, k1 = 0x7fffffff;
	for (int i = 1; i <= n; i++)
	{
		int t, a;
		scanf("%d%d", &t, &a);
		if (t == 1) { k0 &= a; k1 &= a; }
		if (t == 2) { k0 |= a; k1 |= a; }
		if (t == 3) { k0 ^= a; k1 ^= a; }
		c = (~c & k0) + (c & k1); // 这里 + 改成 | 或者 ^ 也行，毕竟没有交集
		printf("%d\n", c);
	}
	return 0;
}
```

[44ms](https://atcoder.jp/contests/abc261/submissions/66021428)。

显然所有的变量都是非负数，我们可以使用 `unsigned` 代替 `int`，用上卡常小技巧还能再快一截（这个技巧也可以用到快速读入中）。

[37ms](https://atcoder.jp/contests/abc261/submissions/66021470)。

---

## 作者：wfc284 (赞：0)

这里考虑 $t_{i,j,k}$ 为第 $i$ 次操作，第 $k$ 位的输入值为 $j \in \{0,1\}$，第 $k$ 位的结果。  
然后 $t_{i,j,k}$ 中的 $i$ 是一轮一轮更新的，直接去掉。$k$ 可以状压，也去掉。于是只剩 $t_j$。  
即把 $x$ 拆成了 $30$ 个数位，处理每一位经历一堆操作之后的结果。对于某一位，若当前位是 $0$，则将当前位赋值为 $t_0$；否则将当前位赋值为 $t_1$。  
具体见代码。
### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
using namespace std;
const int s = (1 << 30) - 1;

int x, n, opt, a;
int t[2], tmp;

signed main() {
	cin >> n >> x;
	t[0] = 0, t[1] = s;
	while(n--) {
		scanf("%d%d", &opt. &a);
		tmp = 0;
		for(re int i = 0; i < 30; ++i){
			int c = a & 1 << i;
			if(opt == 1) t[0] &= s ^ 1 << i | c, t[1] &= s ^ 1 << i | c;	//不用s的话会把其他位全清空
			else if(opt == 2) t[0] |= c, t[1] |= c;
			else t[0] ^= c, t[1] ^= c;
			tmp |= t[x >> i & 1] & (1 << i);
		}
		x = tmp;
		printf("%d\n", x);
	}
	return 0;
}
```

---

## 作者：2020luke (赞：0)

# [[ABC261E] Many Operations](https://www.luogu.com.cn/problem/AT_abc261_e) 题解

## 思路解析

首先可以发现，如果直接按照题目要求跑肯定会炸，于是考虑优化。

考虑预处理，发现操作有很多重复的，所以可以考虑把每一个数经过所有操作后的值都预处理下来，但这样会有 $2^{30}$ 个数，显然空间也会炸。

然后我们又想可以不需要求所有的数经过操作后的值，可以把每个数拆成 $30$ 个二进制位，然后分别考虑每一个二进制位开始时的情况和对应的结束时的答案。

最后在需要查询时遍历每一位，把每一位上对应二进制的值取出来再相加即可。

还有就是尽量不要用我的代码的实现去写，看上去十分丑陋不便于调试，可以直接用 `bitset` 或整形变量存储，没必要使用 dp。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, c;
int f[2][N][32];
signed main() {
	cin >> n >> c;
	for(int i = 0; i <= 30; i++) f[1][0][i] = 1;
	for(int i = 1, op, x; i <= n; i++) {
		cin >> op >> x;
		for(int j = 0; j <= 30; j++) {
			int t = ((x >> j) & 1);
			for(int k = 0; k < 2; k++) {
				if(op == 1) f[k][i][j] = f[k][i - 1][j] & t;
				else if(op == 2) f[k][i][j] = f[k][i - 1][j] | t;
				else if(op == 3) f[k][i][j] = f[k][i - 1][j] ^ t;
			}
		}
		int res = 0;
		for(int j = 0; j <= 30; j++) {
			int t = ((c >> j) & 1);
			res += (f[t][i][j] << j);
		} c = res;
		cout << res << '\n';
	}
	return 0;
}
```

---

## 作者：Glacial_Shine (赞：0)

# 题目大意

有一个变量 $x$ 和 $n$ 种操作，第 $i$ 中操作有一对数 $T_i$，$A_i$，含义如下：

- 若 $T_i = 1$，则 $x = x \operatorname{ans} A_i$。
- 若 $T_i = 2$，则 $x = x \operatorname{or} A_i$。
- 若 $T_i = 3$，则 $x = x \operatorname{xor} A_i$。

 按如下规则进行操作：

- 执行操作 $1$，输出 $x$。
- 执行操作 $1$，$2$，输出 $x$。

 

- 执行操作 $1$，$2$，$\cdots$，$n$，输出 $x$。

# 思路

如果把  看作一个数来处理并不是很好处理，我们把  变为二进制数，一位一位看。

考虑 DP，我们设 $f_{i, j, 0/1}$ 表示执行完操作 $1,2,\cdots ,i$，第 $i$ 位原先是 $0/1$，现在的状态。

于是可以就可以直接按照规则处理。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, c, t[200005], a[200005], f[200005][35][2];
int pd(int t, int a, int b) {
    if (t == 1)
        return a & b;
    if (t == 2)
        return a | b;
    return a ^ b;
}
int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &t[i], &a[i]);
    for (int i = 1; i <= 31; i++)
        f[0][i][1] = 1;
    for (int i = 1, op; i <= n; i++) {
        op = a[i];
        for (int j = 1; j <= 30; j++, op = op >> 1) {
            f[i][j][0] = pd(t[i], f[i - 1][j][0], op & 1);
            f[i][j][1] = pd(t[i], f[i - 1][j][1], op & 1);
        }
    }
    int ans = c, last;
    for (int i = 1; i <= n; i++) {
        last = ans, ans = 0;
        for (int j = 1; j <= 30; j++)
            if (f[i][j][(last >> (j - 1)) & 1])
                ans += (1 << (j - 1));
        printf("%d\n", ans);
    }
    return 0;
}
```


---

