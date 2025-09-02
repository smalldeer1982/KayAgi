# Extreme Extension

## 题目描述

For an array $ b $ of $ n $ integers, the extreme value of this array is the minimum number of times (possibly, zero) the following operation has to be performed to make $ b $ non-decreasing:

- Select an index $ i $ such that $ 1 \le i \le |b| $ , where $ |b| $ is the current length of $ b $ .
- Replace $ b_i $ with two elements $ x $ and $ y $ such that $ x $ and $ y $ both are positive integers and $ x + y = b_i $ .
- This way, the array $ b $ changes and the next operation is performed on this modified array.

For example, if $ b = [2, 4, 3] $ and index $ 2 $ gets selected, then the possible arrays after this operation are $ [2, \underline{1}, \underline{3}, 3] $ , $ [2, \underline{2}, \underline{2}, 3] $ , or $ [2, \underline{3}, \underline{1}, 3] $ . And consequently, for this array, this single operation is enough to make it non-decreasing: $ [2, 4, 3] \rightarrow [2, \underline{2}, \underline{2}, 3] $ .

It's easy to see that every array of positive integers can be made non-decreasing this way.

YouKn0wWho has an array $ a $ of $ n $ integers. Help him find the sum of extreme values of all nonempty subarrays of $ a $ modulo $ 998\,244\,353 $ . If a subarray appears in $ a $ multiple times, its extreme value should be counted the number of times it appears.

An array $ d $ is a subarray of an array $ c $ if $ d $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

Let $ f(l, r) $ denote the extreme value of $ [a_l, a_{l+1}, \ldots, a_r] $ .

In the first test case,

- $ f(1, 3) = 3 $ , because YouKn0wWho can perform the following operations on the subarray $ [5, 4, 3] $ (the newly inserted elements are underlined): $ [5, 4, 3] \rightarrow [\underline{3}, \underline{2}, 4, 3] \rightarrow [3, 2, \underline{2}, \underline{2}, 3] \rightarrow [\underline{1}, \underline{2}, 2, 2, 2, 3] $ ;
- $ f(1, 2) = 1 $ , because $ [5, 4] \rightarrow [\underline{2}, \underline{3}, 4] $ ;
- $ f(2, 3) = 1 $ , because $ [4, 3] \rightarrow [\underline{1}, \underline{3}, 3] $ ;
- $ f(1, 1) = f(2, 2) = f(3, 3) = 0 $ , because they are already non-decreasing.

So the total sum of extreme values of all subarrays of $ a = 3 + 1 + 1 + 0 + 0 + 0 = 5 $ .

## 样例 #1

### 输入

```
4
3
5 4 3
4
3 2 1 4
1
69
8
7264 40515 28226 92776 35285 21709 75124 48163```

### 输出

```
5
9
0
117```

# 题解

## 作者：Alex_Wei (赞：14)

- Upd on 2022.3.22：进行一些小修补。
- Upd on 2022.7.2：修补事实性错误。

> [CF1603C Extreme Extension](https://www.luogu.com.cn/problem/CF1603C)

数论分块优化 DP。

一个数如何分裂由后面分裂出来的数的最小值决定，显然贪心使分出来的数尽量均匀，例如若 $9$ 要裂成若干个比 $4$ 小的数，那么 $3, 3, 3$ 比 $2, 3, 4$ 更优。

从后往前考虑，对于每个数 $a_i$ 和值 $j\in [1, a_i]$，求出有多少以 $a_i$ 开头的子串根据上述贪心策略分裂出的最小值为 $j$，$j$ 由 $a_i$ 分裂零次或若干次得到，记为 $f_{i, j}$。

首先明确两点：

- $a_i$ 分裂成若干 $\leq v$ 的数，最少分裂次数为 $\left\lceil \dfrac {a_i} v \right\rceil - 1$，分裂成 $\left\lceil \dfrac {a_i} v \right\rceil$ 个数。
- $a_i$ 分裂成 $v$ 个数，这些数最小值的最大值为 $\left\lfloor \dfrac {a_i} v \right\rfloor$。

考虑转移。

注意到对于固定的分裂次数，分裂出的值也是确定的。考虑枚举使得分裂次数相同的区间 $[l, r]$，即 $a_i$ 整除 $[l, r]$ 内所有数向上取整的结果相同，可以通过向上取整的数论分块实现。

令 $c = \left\lceil \dfrac {a_i} l \right\rceil$ 表示分裂出的数的个数，则分裂出的数的最小值为 $v = \left\lfloor \dfrac {a_i} c \right\rfloor$。因此，$\sum\limits_{j = l} ^ r f_{i + 1, j}$ 转移到 $f_{i, v}$。

考虑在每个位置处统计该位置在所有子段中总分裂次数之和，则答案加上 $i\times (c - 1) \times f_{i , v}$。其含义为，共有 $f_{i, v}$ 个子段使得 $a_i$ 要分裂出 $c$ 个数，即分裂 $c - 1$ 次。同时，若子段 $[i, k]$ 在 $i$ 处分裂 $c - 1$ 次，则对于任意子段 $[x, k]$ 满足 $1\leq x\leq i$，$a_i$ 分裂的次数都是 $c - 1$，因为 $a_i$ 的分裂不受前面的数的影响。

注意，当 $c = 1$ 时，$f_{i, v}$ 即 $f_{i, a_i}$ 需要加上 $1$，表示新增以 $a_i$ 结尾的子段。

用 `vector` 存储所有 $f_i$ 并转移，时间复杂度 $\mathcal{O}(n\sqrt {a_i})$。滚动数组优化后空间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define fi first
#define se second
bool Mbe;
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, a[N];
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  vector<pii> cur, nw;
  cur.push_back({a[n], 1});
  int ans = 0;
  for(int i = n - 1; i; i--, cur = nw) {
    nw.clear(), reverse(cur.begin(), cur.end());
    for(int l = 1, r; l <= N; l = r + 1) {
      int split = (a[i] - 1) / l + 1;
      r = split > 1 ? (a[i] - 1) / (split - 1) : N;
      int val = split == 1;
      while(!cur.empty() && cur.back().fi <= r) add(val, cur.back().se), cur.pop_back();
      add(ans, 1ll * val * (split - 1) % mod * i % mod);
      nw.push_back({a[i] / split, val});
    }
  }
  cout << ans << "\n";
}
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  int T;
  cin >> T;
  while(T--) solve();
  return cerr << "Time: " << clock() << "\n", 0;
}
/*
2022/7/2
start coding at 19:27
finish debugging at 19:42
*/
```

---

## 作者：yyyyxh (赞：14)

### 题意简述

给定一个数列，每次可以把一个数分拆成两个正整数，求它的每个子数组变成不降数列的最小操作数之和

### 思路

首先观察题目性质：对于最后一个数，我们不可能选择分拆它，这样只会让前面数的上限更小，进一步地，我们不可能分拆 $a_i\leq a_{i+1}$ 的一段后缀

所以首先肯定是对 $a_i>a_{i+1}$ 的最靠后的值进行分拆，对于每一个这样的值，从后向前决策

考虑如何分拆最优：显然对于一个数 $a_i$ ，我们会把它分拆成多个正整数 $b_1\leq b_2 \leq \dots \leq b_k \leq a_{i+1}$ ，为了满足 $b_k\leq a_{i+1}$ ，要求 $k \geq \lceil \frac{a_i}{a_{i+1}}\rceil$ 

然后为了最大化 $b_1$ ，我们会拆得尽量平均，满足 $b_1 \geq \Big\lfloor\dfrac{a_i}{\lceil \frac{a_i}{a_{i+1}}\rceil}\Big\rfloor$

不难发现，这样一直取下去，是贪心的最优方案

现在题目还让我们对于每一个子数组求答案，可以考虑对于每一个结束位置从后往前暴力模拟，是 $\mathcal{O}(n^2)$ 的

再次观察到本题值域不大，以及对于已经决策过的后缀对前面的数的影响只是一个上限 $a_{i+1}$ ，所以考虑 DP ，对于每一个 $i$ 和 $a_{i+1}$ 的值设置状态 $f_{i,j}$ ，表示后缀分拆的方案数（为什么是方案数？因为直接对于题目中的操作数进行转移并不好统计最小的答案之和），然后再在转移时对于答案贡献 $k\times f_{i,j}\times i$（$k$ 是上文所述 $k$) ，其中乘上 $i$ 是因为我们 DP 的是后缀，但是要对 $i$ 个包含该后缀的子数组都有贡献

状态看起来是 $\mathcal{O}(n^2)$ 级别的，但考虑所有的 $k$ 都是像数论分块一样的式子，只有根号范围的取值，因此复杂度有保证

### Code

```cpp
#include <cstdio>
/*快读省略*/
const int _=100003;
const int P=998244353;
int n,res;
int f[_],g[_];
int a[_];
void upd(int &x,int y){if ((x+=y)>=P) x-=P;}
void solve(){
    n=read(); res=0;
    for (int i=1; i<=n; i++) a[i]=read();
    for (int i=n-1; i; i--){
        upd(f[a[i+1]],1);
        for (int l=1,r; l<=a[i+1]; l=r+1){
            int c=a[i+1]/l;
            r=a[i+1]/c;
            g[c]=f[c]; f[c]=0;
        }
        for (int l=1,r; l<=a[i+1]; l=r+1){
            int c=a[i+1]/l;
            r=a[i+1]/c;
            if (!g[c]) continue;
            int k=(a[i]+c-1)/c;
            upd(f[a[i]/k],g[c]);
            upd(res,1ll*g[c]*i%P*(k-1)%P);
        }
    }
    for (int l=1,r; l<=a[1]; l=r+1){
        int c=a[1]/l;
        r=a[1]/c;
        f[c]=0;
    }
    printf("%d\n",res);
}
int main(){
    int T=read();
    while (T--) solve();
    return 0;
}
```

### 后记

貌似是次劣解，由于直接把数论分块跑出来了……

官解的实现似乎用了两个 $vector$ 进行迭代，跑不满 $\mathcal{O}(n \sqrt {10^5})$ 的上界，因此快了不少，代码应该更好写

所以我的实现将就着参考一下吧……

感觉此题主要难在贪心的转化上，想到了贪心看一眼值域，DP 应该不难得出

果然是我贪心太菜

不会数论分块的可以 [OI wiki](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)

---

## 作者：KAMIYA_KINA (赞：8)

## Tag

动态规划，构造。

## Description

给定一个长度为 $n$ 的序列 $\{a_n\}$，求出其所有子区间的权值和。

定义一个序列的权值为最少的操作次数使得整个区间变成非降区间。

定义一个操作为选择一个元素，将其分裂成两个元素，要求这两个元素的和等于原来的元素。

$T$ 组询问。

$\texttt{data range:} n\leq 10^5,T\leq 10000,a_i\leq 10^5$。

## Solution

挺好玩的题，dp 的思路以前没见过。

先考虑怎么求出这个**权值**。

从前面往后面构造是困难的，因为后面的改变之后可能会影响前面的元素值需要改变，所以从后面往前面操作就可以了。

对于一组 $a_i,a_{i+1}$ 来说，如果 $a_i\leq a_{i+1}$ 就直接不用管他，如果 $a_i > a_{i+1}$ 那么就需要改变。

有一个改变的上界就是将整个 $a_i$ 分成 $a_i$ 个 $1$，但是这样显然不优，所以我们也有一个下界就是将这个 $a_i$ 分成若干个大小为 $a_{i+1}$ 的元素，不过这样的话最后一个元素可能会比较小，然后对后面不优，但是数量变多的话肯定不会使整体答案变优，所以只能调整最后一个元素的大小。

那么数量显然就是 $\left\lceil\dfrac{a_i}{a_{i+1}}\right\rceil$。

所以最后一个元素的大小就是 $\left\lfloor\dfrac{a_i}{\left\lceil\frac{a_i}{a_{i+1}}\right\rceil}\right\rfloor$。

所以有一个 $O(n^2)$ 的做法就是直接枚举每一个终点然后往前面搞就行了。

但是这样过不去，所以考虑优化。

还是继续思考从后往前做，那么对前面有影响的只是最后转移到该点，也就是 $\left\lfloor\dfrac{a_i}{\left\lceil\frac{a_i}{a_{i+1}}\right\rceil}\right\rfloor$ 的值，所以设 $f_{i,x}$ 表示所有的 $i \leq j$，首个元素为 $x$ 的方案数。

那么就可以想到转移：
$$
f_{i,x} = \sum_y f_{i+1,y}
$$
如果枚举每一个大于 $x$ 的 $y$ 的话显然也是 $O(n^2)$ 的，所以考虑优化这个复杂度。

对于上一个可以转移到当前的值来说，定然不多，所以可以用一个东西存起来，然后统计的时候直接统计就可以了。

如果说从 $x$ 转移到当前的话，那么那么就会有 $f_{i+1,x}$ 转移到 $f_{i,y}$，这里的 $y$ 等于 $\left\lfloor\dfrac{a_i}{\left\lceil\frac{a_i}{x}\right\rceil}\right\rfloor$。

根据整除分块的复杂度分析，这样的复杂度就是 $\sqrt n$ 的，这里 $n$ 和值域同阶。

统计答案就是直接加上当前分裂的数量 $-1$ 乘上当前的位置再乘上上一个位置的方案书就可以了。

然后直接做就可以了。

时间复杂度 $O(n\sqrt n)$ 。

## Code

```cpp
typedef long long ll;

const int N = 1e5 + 1;
const int mod = 998244353;

int n;
int a[N], dp[2][N];
vector<int> v[2];

inline void chk(int &x) {x -= mod; x += x >> 31 & mod;}

inline void input() {
    v[0].clear();
    v[1].clear();
    memset(dp, 0, sizeof(dp));
    n = rd;
    for(int i = 1; i <= n; i++) a[i] = rd;
    return ;
}

inline void work() {
    int op = 1, ans = 0;
    for(int i = n; i >= 1; i--, op ^= 1) {
        v[op].push_back(a[i]);
        dp[op][a[i]] = 1;
        int lst = a[i];
        for(int x : v[op ^ 1]) {
            int y = dp[op ^ 1][x];
            int spt = (a[i] + x - 1) / x;
            int fst = a[i] / spt;
            chk(ans += (ll) i * (spt - 1) % mod * y % mod);//统计答案在这里。
            dp[op][fst] += y;
            if(fst != lst) {
                v[op].push_back(fst);
                lst = fst;
            }
        }
        for(int x : v[op ^ 1]) dp[op ^ 1][x] = 0;
        v[op ^ 1].clear();
    }
    cout << ans << '\n';
    return ;
}

inline void solve() {
    int t = rd;
    while(t--) {
        input();
        work();
    }
    return ;
}
```

## Final

注意清空数组。

---

## 作者：小超手123 (赞：2)


一个很有趣的题目，计数的过程很巧妙。

先分析一下 $a_i$ 和 $a_{i+1}$ 的关系。

- $a_i \le a_{i+1}$：不用处理。
- $a_i \ge a_{i+1}$：需要将 $a_i$ 拆成 $k$ 段，不难分析出 $k = \lceil \frac{a_i}{a_{i+1}} \rceil$，而最终拆完后的序列的第一个数为 $\lfloor \frac{a_i}{k} \rfloor$。

因此可以枚举每个后缀，暴力计算一下贡献，就得到了一个时间复杂度 $O(n^2)$ 的算法。

想一下为什么不好优化，因为不同的区间，每个 $a_i$ 所对应的 $a_{i+1}$ 是不一样的。根据整除分块的结论，$a_{i+1}$ 最多有 $\sqrt n$ 个值。

于是就可以记一个 $f_{i,j}$ 表示有多少个以 $i$ 为**左端点**的区间满足将它进行贪心拆分后得到的**第一个数**为 $j$。

这样的好处在于可以将 $a_i$ 后面的 $j$ 一起同时计算了。

对于一个 $f_{i+1,j}$ 它能转移到 $f_{i,l}$，其中 $l$ 表示把 $a_i$ 拆分后的第一个数。

于是做法就很明显了，开两个 vector 分别存储 $j,l$，每次把 $a_i$ 加入 vector，实时更新即可。

容易发现，$f_{i+1,j}$ 对答案的贡献为 $i\times (k-1) \times f_{i+1,j}$，因为有 $i \times f_{i+1,j}$ 个区间都会以这种方式（将 $a_i$ 拆成 $k$ 段）处理。

时间复杂度 $O(n\sqrt n)$。

End。  



---

## 作者：Purslane (赞：2)

# Solution

还是那句话，如果看到一个很奇怪的定义在区间上的函数 $f(l,r)$，还让你求 $\sum \sum f(i,j)$ 之类的和，你要干的第一件事实弄清楚 $f(l,r)$ 怎么算。

假设你拿到了一个 $b$ 数组。很显然，$b$ 的最后一个数不能拆，因为拆了反而会更劣（凭空多出了一次操作，而且可能使前面要拆更多次）。再考虑对倒数第二个数 $v$ 进行拆分，假设最后一个数为 $u$。

为了让每个数都小于等于 $u$，那么至少要拆成 $\lceil \frac{v}{u} \rceil$ 段。再由贪心的思想，如果我们拆了 $x$ 段，应该通过某种手段让第一个数为 $\lfloor \frac{v}{x} \rfloor$，这样可以使前面拆的段尽可能少。很显然这是能做到的。（先搞出 $x$ 段 $\lfloor \frac{v}{x} \rfloor$，再把余数加到后面几段上来。）

所以说，如果上一个数为 $u$，那么这一轮结束之后第一个数为 $\lfloor \frac{v}{\lceil \frac{v}{u} \rceil} \rfloor$。不断往前迭代，就处理了计算 $f$ 这个问题。

然后你注意到 $\lfloor \frac{v}{\lceil \frac{v}{u} \rceil} \rfloor$ 在 $v$ 一定 $u$ 不同的时候可能取值的种类只有 $O(\sqrt v)$ 量级。所以我们从不同的 $r$ 出发，扫描到某个点 $h$ 的时候只有 $O(\sqrt {a_h})$ 种拆分可能，把相同的情况进行压缩。一 一枚举它们。这时候每一种长度为 $x$ 的拆分都会对答案产生 $h(x-1)$ 的贡献。

因此从 $n$ 开始往前迭代可以做到 $O(n \sqrt V)$ 的复杂度。

[代码](https://codeforces.com/contest/1603/submission/212325196)

---

## 作者：KSToki (赞：2)

# 题目大意
给定一个数组 $a$，定义一次操作为将一个数分解为两个和为该数的正整数并放回原位，$f(l,r)$ 表示将 $a_l \cdots a_r$ 转化成不降序列的最少操作数，求 $\sum_{l=1}^{n}\sum_{r=l}^{n}f(l,r)$，答案对 $998244353$ 取模。
# 题目分析
题目中的操作一定不会把数变大，那么对于 $i$，贪心地，需要将 $a_i$ 分成尽量少的数，在这个前提下使分解出的数的最小值最大，则需要进行的操作数为 $\lceil\frac{a_i}{a_{i+1}}\rceil-1$，分解出的数的最小值最大为 $\lfloor\frac{a_i}{\lceil\frac{a_i}{a_{i+1}}\rceil}\rfloor$。

这下就有 $O(n^2)$ 暴力了，固定一个右端点，左端点一直往前扫就可以了。对暴力进行优化，左端点往前扫，容易知道这玩意是单调的，右端点越靠后限制不会越小，可以拿一个 `vector` 存下限制以及数量，计算完后把当前点加进去。看起来 `vector` 里还能存 $O(n)$ 的状态，还是 $O(n^2)$。

真的吗？

这个长得像只对暴力进行了常数优化的东西，直接将复杂度降到了 $O(n\sqrt n)$！

看到这一堆的整除和向上取整向下取整，以及值域与 $n$ 同阶，证明考虑整除分块，对于每个 $a_i$，等价于求 $\lfloor\frac{a_i}{\lceil\frac{a_i}{a_{i+1}}\rceil}\rfloor$ 的不同值的数量。套路的讨论以根号为分界线最终值的数量即可。

代码需要注意边界和清空，$O(n\sqrt nlogn)$ 不能通过，~~不要问我怎么知道的~~。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[100005];
const int mod=998244353; 
vector< pii >s,t;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n)
			a[i]=read();
		s.clear();
		s.pb(mp(a[n],1));
		int ans=0;
		Rof(i,n-1,1)
		{
			t.clear();
			for(auto j:s)
			{
				ans=(ans+1ll*j.se*(a[i]/j.fi+(a[i]%j.fi!=0)-1)%mod*i%mod)%mod;
				if(t.size()&&t.back().fi==a[i]/(a[i]/j.fi+(a[i]%j.fi!=0)))
					t[t.size()-1].se+=j.se;
				else
					t.pb(mp(a[i]/(a[i]/j.fi+(a[i]%j.fi!=0)),j.se));
			}
			if(t.size()&&t.back().fi==a[i])
				++t[t.size()-1].se;
			else
				t.pb(mp(a[i],1));
			s.swap(t);
		}
		putint(ans);
	}
	return 0;
}

```

---

## 作者：lfxxx (赞：0)

有趣的贪心结合 dp 的题目。

考虑对于一个序列怎么算答案，因为要对于每个子区间算答案所以我们猜测算答案的方式很简单，考虑贪心，从后往前考虑，你希望后缀的第一个位置尽可能大以放松对前面的限制，同时你希望代价尽可能小，而两者是可以结合的，代价尽可能小的情况下把一个位置上的数均匀分开即可满足两者，那么唯一的限制就是不能大于上一个数，这限制了我们至少要把这个数均分成多少个部分。因此，从后往前贪心即可处理对于一个数组计算答案。

对于所有子区间计算答案可以考虑从后往前用类似扫描线的办法 dp，注意到 dp 状态和把 $a_i$ 均分若干部分后，每个部分的大小种类是同级的，因此是 $O(\sqrt V)$ 级别，双指针暴力维护转移即可做到 $O(n \sqrt V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 1e5+114;
int cnt[maxn];
int a[maxn],n;
int f(int x,int y){
    if(y==0) return 1e9;
    return (x+y-1)/y;
}
void work(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int ans=0;
    cnt[1]=1;
    for(int i=n-1;i>=1;i--){
        vector< pair<int,int> > vec;
        for(int j=1;j<=a[i+1];j=f(a[i+1],f(a[i+1],j)-1)){
            vec.push_back(make_pair(j,cnt[j]));
            cnt[j]=0;
        }
        vector< pair<int,int> > ins;
        for(int j=1;j<=a[i];j=f(a[i],f(a[i],j)-1)){
            ins.push_back(make_pair(j,0));
        }
        int lst=-1;
        for(int j=0;j<ins.size();j++){
            while(lst+1<vec.size()&&a[i+1]/vec[lst+1].first>=f(a[i],ins[j].first)) lst++,ins[j].second=(1ll*ins[j].second+1ll*vec[lst].second)%mod;
        }
        ins[0].second=(ins[0].second+1)%mod;
        for(pair<int,int> now:ins){
            cnt[now.first]=now.second;
            ans=(1ll*ans+1ll*now.second*(now.first-1)%mod*i%mod)%mod;
        }
    }
    cout<<ans<<"\n";
    for(int i=1;i<=a[1];i=f(a[1],f(a[1],i)-1)) cnt[i]=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

## 作者：rainygame (赞：0)

简单贪心题调了 1h，是不是废了。

可以发现 $a_i$ 会分成连续的一段，因为只有一段的第一个数和最后一个数的有用的，所以分别设为 $x_i,y_i$。

> 性质 1：尽量平均一定不劣，且 $a_i$ 拆分的方式是 $O(\sqrt V)$ 级别的。
>
> 证明：前者显然。设分为 $d$ 个，则 $x_i=\lfloor\dfrac{a_i}{d}\rfloor,y_i=\lceil\dfrac{a_i}{d}\rceil$，由于 $0\le y_i-x_i\le 1$ 且 $x_i$ 种类数的 $O(\sqrt V)$ 级别的，所以拆分方式也是 $O(\sqrt V)$ 级别的。
>
> 由此也可以推得“对于一定的 $(x_i,y_i)$ 一定有唯一的拆分使得操作次数最少”。

> 性质 2：对于一个已经完成最优拆分的子段 $[l,r]$，在 $[l-1,r]$ 的最优拆分中，$[l,r]$ 这部分不会改变。
>
> 证明：如果 $a_{l-1}$ 加入后满足不降，那么不需要改变；否则如果改变 $[l,r]$ 部分的拆分，那么一定是使得 $x_l$ 变大，但如果可以更大，那么为什么在 $[l,r]$ 的最优拆分中没有呢？（如果可以变大，那么拆分的个数也会变少，答案更优）

所以对于一个 $a_i$ 的贡献，只需要考虑所有 $[1,r]$ 子段中 $a_i$ 的贡献，最后在乘上 $i$ 即可。现在的目标是对于每个 $r$，维护 $i\in[1,r]$ 的 $a_i$ 在 $[1,r]$ 的贡献。

可以发现在 $r$ 增长的时候，$x_i$ 一定不增，因为 $x_i$ 的改变一定是由于 $a_r$ 太小造成的（$a_r$ 很大就不用改变了）。如果发现 $a_r < y_{r-1}$，那么直接暴力从后往前依次调整，直到到了某个地方不用调整了。由于调整只会使 $x$ 越来越小，所以调整的总次数是 $O(n\sqrt V)$。

注意不能提前整除分块，否则空间会变为 $O(n\sqrt V)$。正确的做法是在调整的同时整除分块，然后还要把之前的删除，这样空间复杂度变为 $O(n)$。

代码比较好写，但是有细节。[submission](https://codeforces.com/contest/1603/submission/310530058)

---

## 作者：jasonliujiahua (赞：0)

# CF1603C

## 题目描述


对于一个数列，定义一次操作为选择数列中任何一个元素 $a_i$ ，将这个位置替换成两个**正整数** $x,y$ 满足 $x+y=a_i$。

定义一个数列的极端值为将这个数列变成**不降**数列的最小操作次数。

给定一个长度为 $n$ 的数列 $a$（$1\leq a_i\leq 10^5$），让你求它的所有非空子段的极端值之和，对 $\text{998244353}$ 取模。

一个测试点中有多组数据，保证所有数据 $n$ 的规模总和不超过 $10^5$。

## Solution
### Step 1：暴力
首先显然最后一个数一定不应该操作，因此考虑枚举子段的结尾。然后，可以将 $[l,r]$ 是最长不降数列充要地转化为：
$$\forall i\in[l,r],a'_i\le \min_{j=i+1}^r a'_j$$

其中 $a'_x$ 表示 $a_x$ 操作后剩下的所有数中的任意一个。从右往左遍历，此时已知 $mn_{i+1}=\min_{j=i+1}^r a'_j$，则 $i$ 的贡献就变成了将 $a_i$ 操作为小于等于 $mn_{i+1}$ 的最少操作次数 $g(a_i,mn_{i+1})$。

接下来求 $g(x,y)$。显然 $g(x,y)+1$ 个数加起来是 $x$，且这些数都小于等于 $y$，因此只需让这些数尽量大，就可以让 $g(x,y)$ 尽量小。因此让这些数尽量取 $y$ 即可，则易得 $g(x,y)=\left \lfloor \frac{x-1}{y} \right \rfloor$。

接下来求 $mn_i$。这时我们确定了 $g(a_i,mn_{i+1})$，则所有数的分配应当最均匀才能使得 $mn_i$ 最大，以减少之后的操作。由于有 $g(a_i,mn_{i+1})+1$ 个数，因此可得

$$mn_i=\left \lfloor \frac{a_i}{g(a_i,mn_{i+1})+1} \right \rfloor=\left \lfloor \frac{a_i}{\left \lfloor \frac{a_i-1}{mn_{i-1}} \right \rfloor+1} \right \rfloor$$

由于当 $l'\in [1,l-1]$ 时，以上在 $l$ 处算的值还要被重新算一遍，因此算贡献时应乘上 $l$。

至此，已得 $\mathcal{O(n^2)}$ 的暴力。


### Step 3：优化

对位置 $i$ 有影响的只有 $mn_{i+1}$，因此考虑只枚举 $i$，观察是否可以算出 $mn_{i+1}$。接下来观察 $mn_i=\left \lfloor \frac{a_i}{\left \lfloor \frac{a_i-1}{mn_{i+1}} \right \rfloor+1} \right \rfloor$，在 $i$ 一定时，$mn_i$ 只有 $\mathcal{O(\sqrt n)}$ 种取值，因此考虑将其放在下标上，计算其出现次数。

具体地，令 $dp_{i,j}$ 表示末尾在 $[i+1,n]$ 时有多少种情况可以使得 $mn_i=j$。有转移：
$$dp_{i,j}=\sum_{w=mn_{i+1},j=mn_i} dp_{i+1,w}$$

这样就可以让 $mn_{i-1}$ 相等的值一起处理。需要滚动数组优化一下空间，时间复杂度 $\mathcal{O(n\sqrt n)}$。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10,p=998244353;
int t,n,ans,a[maxn],dp[2][maxn],vis[2][maxn];
vector<int> v[2]; 
void init()
{
	ans=0;
	for(int i=1;i<maxn;i++) dp[0][i]=dp[1][i]=vis[0][i]=vis[1][i]=0;
	v[0].clear(),v[1].clear();
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
}
void work()
{
	int op=1;
	for(int i=n;i;i--,op^=1)
	{
		v[op].push_back(a[i]);
		vis[op][a[i]]=1;
		dp[op][a[i]]=1;
		for(int j=0;j<v[op^1].size();j++)
		{
			int B=v[op^1][j];
			ans=(ans+(a[i]-1)/B*i%p*dp[op^1][B]%p)%p;
			int A=a[i]/((a[i]+B-1)/B);
			dp[op][A]+=dp[op^1][B];
			if(vis[op][A]) continue;
			vis[op][A]=1;
			v[op].push_back(A);	
		}
		for(int j=0;j<v[op^1].size();j++) dp[op^1][v[op^1][j]]=vis[op^1][v[op^1][j]]=0;
		v[op^1].clear();
	}
	cout<<ans<<"\n";
}
signed main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		init();
		work();
	}
	return 0;
} 

```

---

