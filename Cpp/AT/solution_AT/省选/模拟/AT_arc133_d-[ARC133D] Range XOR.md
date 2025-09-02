# [ARC133D] Range XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc133/tasks/arc133_d

整数 $ L,R,V $ が与えられます． 次の条件を両方満たす整数の組 $ (l,r) $ の個数を $ 998244353 $ で割った余りを求めてください．

- $ L\ \leq\ l\ \leq\ r\ \leq\ R $
- $ l\ \oplus\ (l+1)\ \oplus\ \cdots\ \oplus\ r=V $

ただしここで，$ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表します．

  ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の非負整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ L\ \leq\ R\ \leq\ 10^{18} $
- $ 0\ \leq\ V\ \leq\ 10^{18} $
- 入力される値はすべて整数である

### Sample Explanation 1

条件を満たすのは，$ (l,r)=(1,2) $ と $ (l,r)=(3,3) $ の $ 2 $ つです．

## 样例 #1

### 输入

```
1 3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
10 20 0```

### 输出

```
6```

## 样例 #3

### 输入

```
1 1 1```

### 输出

```
1```

## 样例 #4

### 输入

```
12345 56789 34567```

### 输出

```
16950```

# 题解

## 作者：Phartial (赞：4)

牛逼逼题。

我们先考虑没有 $l\le r$ 的限制的情况，先做个前缀和，即 $s_i=\displaystyle\oplus_{i=0}^ni$，那么要统计的东西就变成了：

$$
\sum_{l=L-1}^{R-1}\sum_{r=L}^R[s_l\oplus s_r=v]
$$

但我们会发现这玩意没有对称性，很蛋疼，于是考虑强行把区间拉平得到

$$
\sum_{l=L-1}^{R}\sum_{r=L-1}^R[s_l\oplus s_r=v]
$$

考虑这玩意多算了哪些东西，可以发现，我们多算的部分是 $l=r$ 的部分（对应到一开始的式子不是合法情况），去掉这一部分后，我们会发现我们会同时统计 $(l,r)$ 与 $(r,l)$，因此再除以 $2$ 就得到了我们要的东西。

考虑做个前缀和，设

$$
S(n,m)=\sum_{l=0}^n\sum_{r=0}^m[s_l\oplus s_r=v]
$$

那么我们要求的东西就变成了 $S(R,R)-2S(L-2,R)+S(L-2,L-2)$，考虑如何求 $S(n,m)$ 即可。

考虑 $s_i$ 的计算，可以发现如下事实：

```
s[------00] =        0^------00 = ------00
s[------01] = ------00^------01 = 1
s[------10] =        1^------10 = ------11
s[------11] = ------11^------11 = 0
```

因此，我们有：

$$
s_i=\begin{cases}
  i & i\equiv0\pmod 4\\
  1 & i\equiv1\pmod 4\\
  i+1 & i\equiv2\pmod 4\\
  0 & i\equiv3\pmod 4
\end{cases}
$$

可以发现，对于 $l\equiv 1,3\pmod 4$ 或 $r\equiv 1,3\pmod 4$ 的情况，由于 $s_{l/r}$ 为常量，故可以直接计算。

可以发现当确定末两位后可以直接删掉后两位，那么就没有模 $4$ 的限制了。

对于剩下的内容，等价于求

$$
\sum_{l=0}^{\lfloor n/4\rfloor}\sum_{r=0}^{\lfloor m/4\rfloor}[l\oplus r=\lfloor v/4\rfloor]
$$

而这是一个 trivial 的数位 dp，硬冲就完了。

时间复杂度 $O(\log n)$

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kL = 60, kB[4] = {0, 1, 3, 0};
const LL kM = 998244353;

LL L, R, v, f[kL][2][2];

LL _S(int i, LL n, bool ln, LL m, bool lm, LL v) {
  if (i == -1) {
    return 1;
  }
  LL &fs = f[i][ln][lm];
  if (~fs) {
    return fs;
  }
  fs = 0;
  for (int kn = 0, vn = (ln ? (n >> i & 1) : 1); kn <= vn; ++kn) {
    for (int km = 0, vm = (lm ? (m >> i & 1) : 1); km <= vm; ++km) {
      if ((kn ^ km) == (v >> i & 1)) {
        fs = (fs + _S(i - 1, n, ln && kn == vn, m, lm && km == vm, v)) % kM;
      }
    }
  }
  return fs;
}
LL bS(LL n, LL m, LL v) {
  for (int i = 0; i < kL; ++i) {
    for (int j = 0; j <= 1; ++j) {
      for (int k = 0; k <= 1; ++k) {
        f[i][j][k] = -1;
      }
    }
  }
  return _S(kL - 1, n, 1, m, 1, v);
}
LL S1(LL n, LL m) {
  if (n < 0 || m < 0) {
    return 0;
  }
  LL s = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      LL w = (v ^ kB[i] ^ kB[j]);
      if (w & 3) {
        continue;
      }
      w >>= 2;
      LL ci = (n >> 2) - ((n & 3) < i);
      LL cj = (m >> 2) - ((m & 3) < j);
      s = (s + bS((i & 1) ? 0 : ci, (j & 1) ? 0 : cj, w) * ((i & 1) ? (ci + 1) % kM : 1) % kM * ((j & 1) ? (cj + 1) % kM : 1) % kM) % kM;
    }
  }
  return s;
}
LL S2(LL l, LL r) { return (S1(r, r) - 2 * S1(l - 1, r) + S1(l - 1, l - 1) + 2 * kM) % kM; }

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> L >> R >> v;
  cout << (S2(L - 1, R) - (v == 0) * (R - L + 2) % kM + kM) * (kM + 1) / 2 % kM;
  return 0;
}
```


---

## 作者：LostKeyToReach (赞：1)

题目不是非常难，考验你的分类讨论能力。

首先，我们如何快速求出 $\displaystyle \bigoplus_{i = 0} ^ n i$？根据 [P3908](https://www.luogu.com.cn/problem/P3908) 我们可得；

$$
\bigoplus_{i=0}^{n} i =
\begin{cases}
n,& n\equiv 0\pmod4,\\
1,& n\equiv 1\pmod4,\\
n+1,& n\equiv 2\pmod4,\\
0,& n\equiv 3\pmod4.
\end{cases}
$$

我们令 $f(i)$ 为上式，那么原问题转换为求：

$$
\sum_{i = L - 1} ^ R \sum_{j = i + 1}^R [f(i) \oplus f(j) = V].
$$

接下来考虑将 $[L - 1, R]$ 中的所有数按照对 $4$ 取模的余数分组。设分成的组分别为 $G_0, G_1, G_2, G_3$，然后是一些较为繁琐的分类讨论。

1. $i, j$ 位于同一个组。

   - 对于 $G_1$ 和 $G_3$：由于都是常数，所以这部分贡献为 $\displaystyle{|G_1| \choose 2} +{|G_3| \choose 2}$。

   - $(G_0, G_2)$ 配对：就拿 $G_0$ 举例，我们可以将所有 $n \in G_0$ 都表示为 $a_0 + 4k$ 的形式，此时：
        $$
        \begin{aligned}
        f(a_0 + 4k) \oplus f(a_0 + 4l) &= (a_0 + 4k) \oplus (a_0 + 4l) \\
        &= 4[(\frac{a_0}{4} + k) \oplus (\frac{a_0}{4} + l)].
        \end{aligned}
        $$

    问题转换为在区间 $[u_0, u_0 + n_0 - 1]$ 求满足条件的 $(k, l)$ 对数量使得 $(u_0 + k) \oplus (u_0 + l) = \dfrac{V}{4}$，然后你发现这个东西做个数位 DP 就可以了。对于 $G_2$，我们容易发现 $a_0 + 1$ 为 $3$ 的倍数，加 $1$ 后可以化为 $G_0$ 的情况。

2. $i, j$ 在不同组。具体可以参考上述情况，其实是等价的，此处不再赘述，具体可以参考代码进行理解。
    
参考代码：

```cpp
#define MULTI_TEST 0
int dp[62][2][2][2], xx[62], ll[62], rr[62], tt[62];
constexpr int mod = 998244353;
int solve(int pos, bool tight, bool lo, bool hi) {
    if (pos == 61) return 1;
    if (dp[pos][tight][lo][hi] != -1)
        return dp[pos][tight][lo][hi];
    int ans = 0;
    int lim = tight ? xx[pos] : 1;
    For(i, 0, lim) {
        if ((lo && ((i ^ tt[pos]) < ll[pos])) ||
            (hi && ((i ^ tt[pos]) > rr[pos])))
            continue;
        ans += solve(pos + 1, tight && (i == lim),
            lo && ((i ^ tt[pos]) == ll[pos]), hi && ((i ^ tt[pos]) == rr[pos]));
        ans %= mod;
    }
    return dp[pos][tight][lo][hi] = ans;
}
Z Calc(int a, int b, int t, int l, int r) {
    For(i, 0, 60) xx[i] = b >> (60 - i) & 1, ll[i] = l >> (60 - i) & 1,
        rr[i] = r >> (60 - i) & 1, tt[i] = t >> (60 - i) & 1;
    For(i, 0, 61) For(j, 0, 1) For(k, 0, 1) For(l, 0, 1) dp[i][j][k][l] = -1;
    Z ans = solve(0, 1, 1, 1);
    if (!a) return ans;
    For(i, 0, 60) xx[i] = (a - 1) >> (60 - i) & 1;
    For(i, 0, 61) For(j, 0, 1) For(k, 0, 1) For(l, 0, 1) dp[i][j][k][l] = -1;
    return (ans -= solve(0, 1, 1, 1));
}
PII fxxk(int l, int r, int qwq) {
    int fr = l + qwq - l % 4 + (l % 4 > qwq) * 4;
    if (fr > r) return { 0, 0 };
    return { fr, (r - fr) / 4 + 1 };
}
bool check(int x, int a, int d, int cnt) {
    if (cnt <= 0 || x < a || (x - a) % d)
        return 0;
    return (x - a) / d < cnt;
}
int32_t main() {
#if MULTI_TEST == 1
#else
    int l, r, v;
    std::cin >> l >> r >> v;
    auto [f0, c0] = fxxk(l - 1, r, 0);
    auto [f1, c1] = fxxk(l - 1, r, 1);
    auto [f2, c2] = fxxk(l - 1, r, 2);
    auto [f3, c3] = fxxk(l - 1, r, 3);
    Z ans = 0;
    if (!v)
        ans += Z(c1) * Z(c1 - 1) / 2 + Z(c3) * Z(c3 - 1) / 2;
    if (c0 && v % 4 == 0)
        ans += (Calc(f0 / 4, f0 / 4 + c0 - 1, v / 4,
            f0 / 4, f0 / 4 + c0 - 1) - Z(v / 4 == 0) * c0) / 2;
    if (c2 && v % 4 == 0)
        ans += (Calc((f2 + 1) / 4, (f2 + 1) / 4 + c2 - 1, v / 4,
            (f2 + 1) / 4, (f2 + 1) / 4 + c2 - 1) - Z(v / 4 == 0) * c2) / 2;
    if (c0 && c1 && check(v ^ 1, f0, 4, c0))
        ans += c1;
    if (c0 && c3 && check(v, f0, 4, c0))
        ans += c3;
    if (c2 && c1 && check((v ^ 1) - 1, f2, 4, c2))
        ans += c1;
    if (c2 && c3 && check(v - 1, f2, 4, c2))
        ans += c3;
    if (c1 && c3 && v == 1)
        ans += Z(c1) * c3;
    if (c0 && c2 && v % 4 == 3)
        ans += Calc(f0 / 4, f0 / 4 + c0 - 1,
            (v - 3) / 4, (f2 + 1) / 4, (f2 + 1) / 4 + c2 - 1);
    std::cout << (LL)ans << "\n";
#endif
}
```

---

## 作者：LiveZoom (赞：1)

## Description

[link](https://atcoder.jp/contests/arc133/tasks/arc133_d)

## Solution

很明显要转换成前缀异或和来考虑。

设 $S_i=0\oplus1\oplus2\oplus\dots\oplus i$，那么 $l\oplus l+1\oplus \dots\oplus r=S_r\oplus S_{l-1}$。

所以题目就转化为求：$[L-1,R]$ 中存在多少个 $(l,r)$ 满足 $l< r$ 且 $S_r\oplus S_{l}=V$。

这个东西显然可以转化为 $[R,R]-[L-2,R]-[R,L-2]+[L-2,L-2]$.

但是这样还是有很多限制，不是很好做。所以可以先求不考虑 $l<r$ 的答案，最后除以 $2$ 即可。

如果 $S$ 没有任何规律是不可做的，但是这里的 $S$ 满足：
$$
S_i=
\begin{cases}
i\space\space\space\space\space\space&(i\bmod 4=0)\\
1\space\space\space\space\space\space&(i\bmod 4=1)\\
i+1\space\space\space\space\space\space&(i\bmod 4=2)\\
0\space\space\space\space\space\space&(i\bmod 4=3)
\end{cases}
$$
很明显 $i\bmod 4$ 是 $1$ 或 $3$ 就可以直接特判，是 $0$ 或 $2$ 的可以数位 dp 或者记忆化搜索。

由于这里状态很少，所以记忆化搜索会很快。

注：答案要对 $998244353$ 取模，翻译里面没写！

## Code

```cpp
#include <bits/stdc++.h>

#define int __int128

using namespace std;

const int kInf = 1e18, kR[] = {0, 1, 3, 0}, kLim[] = {kInf, 0, kInf, 0};

long long l, r, v;
map<tuple<int, int, int>, int> mp;

int solve(int a, int b, int v) {
  if (mp.count(make_tuple(a, b, v))) return mp[{a, b, v}];
  if (a < 0 || b < 0) return 0;
  if (!v) return min(a, b) + 1;
  int ret = 0;
  for (int i = 0; i <= 1; ++i) {
    int j = (v & 1) ^ i;
    if (a < i || b < j) continue;
    ret += solve((a - i) >> 1, (b - j) >> 1, v >> 1);
  }
  return mp[{a, b, v}] = ret;
}

int get(int a, int b, int v) {
  if (a < 0 || b < 0) return 0;
  int ret = 0;
  for (int r1 = 0; r1 < 4; ++r1) {
    for (int r2 = 0; r2 < 4; ++r2) {
      int vv = (v ^ kR[r1] ^ kR[r2]);
      if ((vv & 3) || a < r1 || b < r2) continue;
      int tmp = solve(min((a - r1) / 4, kLim[r1]), min((b - r2) / 4, kLim[r2]), vv >> 2), cnt = 1;
      if (r1 == 1) cnt *= (a - 1) / 4 + 1;
      else if (r1 == 3) cnt *= (a - 3) / 4 + 1;
      if (r2 == 1) cnt *= (b - 1) / 4 + 1;
      else if (r2 == 3) cnt *= (b - 3) / 4 + 1;
      ret += tmp * cnt;
      // cerr << r1 << ' ' << r2 << ' ' << tmp * cnt << ' ' << tmp << ' ' << cnt << '\n';

      // ret += solve(min(a / 4, kLim[r1]), min(b / 4, kLim[r2]), vv >> 2);
      // cerr << "***" << min((a - kR[r1]) / 4, kLim[r1]) << ' ' << min((b - kR[r2]) / 4, kLim[r2]) << '\n';
      // cerr << r1 << ' ' << r2 << ' ' << solve(min((a - kR[r1]) / 4, kLim[r1]), min((b - kR[r2]) / 4, kLim[r2]), vv >> 2) << '\n';
    }
  }
  return ret;
}

void print(int x) {
  if (x < 10) {
    cout << (long long)x;
    return;
  }
  print(x / 10);
  cout << (long long)(x % 10);
}

void dickdreamer() {
  long long ll, rr, vv;
  cin >> ll >> rr >> vv;
  int l, r, v;
  l = ll, r = rr, v = vv;
  --l;
  int ans = get(r, r, v) - get(l - 1, r, v) - get(r, l - 1, v) + get(l - 1, l - 1, v);
  // cerr << ans << '\n';
  if (!v) ans -= r - l + 1;
  assert(ans % 2 == 0);
  ans /= 2;
  print(ans % 998244353);
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) dickdreamer();
  // cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's';
  return 0;
}
```



---

## 作者：intel_core (赞：0)

先把 $L-1$，然后计算 $s_l\oplus s_r=V$ 的个数，其中 $s_l$ 表示 $1,2,\cdots,l$ 的异或和。

考虑 $s_i$ 在第 $k$ 位上的值 $(k>0)$：

* 若 $i$ 在第 $k$ 位上为 $0$，那么 $\le l$ 的数中就有 $\lfloor \frac{i}{2^{k+1}}\rfloor 2^k$ 个数第 $k$ 位为 $1$，所以第 $k$ 位显然为 $0$。

* 若 $i$ 在第 $k$ 位上为 $1$，那么 $\le l$ 的数中就有 $\lfloor \frac{i}{2^{k+1}}\rfloor 2^k+l \bmod 2^k+1$ 个数第 $k$ 位为 $1$，所以第 $k$ 位与第 $0$ 位取值相反。

又因为 $s_l$ 最后一位的取值显然之和 $l\bmod 4$ 有关，综上可以直接数位 DP 计算答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
#define int long long
#define y0 le0n
void add(int &x,int y){x=(x+y)%MOD;}
int L,R,V,f[70][2][2][2][2][2],vis[70][2][2][2][2][2];

int x0,y0;
int dfs(int k,int b1,int b2,int b3,int lastx,int lasty){
	int nowx=(L>>k)&1,nowy=(R>>k)&1,tmp=(V>>k)&1;
	if(vis[k][b1][b2][b3][lastx][lasty])return f[k][b1][b2][b3][lastx][lasty];
	if(!k){
		vis[k][b1][b2][b3][lastx][lasty]=1;
		if(!b1&&nowx>x0)return 0;
		if(!b2&&x0>y0)return 0;
		if(!b3&&y0>nowy)return 0;
		if(!b2&&x0==y0)return 0;
		int x=x0^lastx,y=y0^lasty;
		if((x^y)!=tmp)return 0; 
		return f[k][b1][b2][b3][lastx][lasty]=1;
	}
	int res=0;
	vis[k][b1][b2][b3][lastx][lasty]=1;
	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++){
			if(!b1&&nowx>x)continue;
			if(!b2&&x>y)continue;
			if(!b3&&y>nowy)continue;
			int v1=(!x)?0:(x0^1),v2=(!y)?0:(y0^1);
			if((v1^v2)!=tmp)continue;
			int ok1=b1|(nowx<x),ok2=b2|(x<y),ok3=b3|(y<nowy);
			add(res,dfs(k-1,ok1,ok2,ok3,x,y));
		}
	return f[k][b1][b2][b3][lastx][lasty]=res;
}

signed main(){
	cin>>L>>R>>V;L--;
	int ans=0;
	for(x0=0;x0<2;x0++)
		for(y0=0;y0<2;y0++){
			memset(f,0,sizeof(f));
			memset(vis,0,sizeof(vis));
			add(ans,dfs(60,0,0,0,0,0));
		}
	cout<<ans<<endl; 
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

非常有意思的紫题，我模拟赛场切了！呜呜呜，太感动了！

约定一个记号，$x_i$ 表示 $x$ 在二进制下第 $i$ 位是啥，下标以 $0$ 开始，比如 $(6)_{10}=(110)_2$，所以 $6_0=0$。

然后我们思考咋求 $sum_x=\bigoplus\limits_{i=1}^xi$。

考虑拆位，对于显然每一位的前缀和都存在循环节，第 $k$ 位循环节长度为 $2^{k+1}$，以下我们默认 $x<2^{k+1}$，因为不然你可以通过取模使 $x\in[0,2^{k+1})$。

我们不考虑第 $0$ 位因为不符合下面的规律。
$$
(sum_x)_k=
\begin{cases}
0(x<2^k)\\
[2|x](2^k\leq x<2^{k+1})
\end{cases}
$$

证明其实也不难，规律打个表不难发现，还是要强调 $k=0$ 时循环节是 $0110$ 而不是上面这个东西。

前缀和是好求的，所以这题要前缀和作差是必然的，问题变成求 $(l,r)$ 的数对数量，满足 $l\in[L-1,R-1],r\in[L,R],l<r,sum_r\oplus sum_l=v$。

因为 $l$ 和 $r$ 的范围都是区间而不是一个形如 $[0,lim]$ 的前缀，这是复杂的，所以我们考虑拆成前缀形式，我们设 $F_{lim1,lim2}$ 表示 $l\in[0,lim1],r\in[0,lim2]$ 情况下的合法数对。

那么答案显然是：
$$
Ans=F_{r-1,r}-F_{l-2,r}-F_{r-1,l-1}+F_{l-2,l-1}
$$
这就是个二维前缀和，大家自己理解一下，然后考虑 $F_{lim1,lim2}$ 咋求。

由于现在是个前缀，比较守序善良，你只需要保证小于这个 $lim$ 就行，这就和正常的数位 DP 比较像了，我们现在重新规定这俩玩意是 $L,R$ 主要是和下面的变量名重了。

你发现上面那个规律的式子取值其实只和这一位和第 $0$ 位有关，因为循环节长度为 $2^{k+1}$，所以当前位以后的都可以模掉不管，然后显然当前位的取值决定了 $x$ 与 $2^k$ 的大小关系。

而第 $0$ 位呢，决定了奇偶性，而且第 $0$ 位的循环节与第 $1$ 位有关，所以啊，第 $0$ 位十分重要，但是你又不能低位到高位，所以你只能先枚举 $l,r$ 的第一位，再从高位到低位数位 DP。

状态为 $f_{i,0/1,0/1,0/1}$ 分别表示当前处理到第几位，$l$ 是否卡着上界，$r$ 是否卡着上界，$l$ 目前是否与 $r$ 相等。

大力 DP 即可，处理完第 $1$ 位直接和第 $0$ 位拼接即可。

时间复杂度可过，按道理来说是 $\mathcal O(\log R)$ 的，但是一车子常数似乎不好忽视。

```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const LL N=65;
const LL M=60;
const LL mod=998244353;
LL l,r,v,f[N][2][2][2],pw[N];
LL gt(LL x,LL k)
{
    return (x>>k)&1;
}
LL dfs(LL x,LL lim1,LL lim2,LL lim3,LL fir1,LL fir2,LL L,LL R)
{//lim1 对 l 限制，lim2 对 r 限制，lim3 对 l<r
    
    if(f[x][lim1][lim2][lim3]!=-1)return f[x][lim1][lim2][lim3];
//    cout<<x<<' '<<lim1<<' '<<lim2<<' '<<lim3<<' '<<fir1<<' '<<fir2<<' '<<L<<' '<<R<<endl;
    LL ans=0;
    for(LL i=0;i<=1;i++)
    {
        for(LL j=0;j<=1;j++)
        {
            if(lim1&&gt(L,x)<i)continue;
            if(lim2&&gt(R,x)<j)continue;
            if(lim3&&i>j)continue;
            LL t=0;
            if(!fir1)t^=i;
            if(!fir2)t^=j;//判断奇偶性，与 2^k 大小的关系
            if(t!=gt(v,x))continue;
            if(x==1)
            {
                if(lim1&&gt(L,x)==i&&gt(L,0)<fir1)continue;//注意考虑第1位的影响
                if(lim2&&gt(R,x)==j&&gt(R,0)<fir2)continue;
                if(lim3&&i==j&&fir1>=fir2)continue;//注意这俩玩意是不能相等的，所以等于也不行
                LL t=i^fir1^fir2^j;
                if(t!=gt(v,0))continue;
                ans=(ans+1)%mod;
            }        
            else
            {
                ans=(ans+dfs(x-1,lim1&(gt(L,x)==i),lim2&(gt(R,x)==j),lim3&(i==j),fir1,fir2,L,R))%mod;
            }   
        }

    }
    return f[x][lim1][lim2][lim3]=ans;
}
LL work(LL L,LL R)
{
    if(L<0||R<0)return 0;
    LL ans=0;
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<=1;j++)//枚举第一位
        {
            memset(f,-1,sizeof(f));
            ans=(ans+dfs(M,1,1,1,i,j,L,R))%mod;
        }
    }
    return ans;
}
int main()
{
    scanf("%lld%lld%lld",&l,&r,&v);
    LL ans=(work(r-1,r)+work(l-2,l-1)-work(l-2,r)-work(r-1,l-1)+mod+mod)%mod;
    printf("%lld",ans);
}
```

---

