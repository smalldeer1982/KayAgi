# Beautiful Sequence

## 题目描述

我们称一个整数序列为美丽的（beautiful），当且仅当满足以下条件：
- 序列长度至少为 $3$；
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[1, 2]$、$[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（不改变剩余元素的顺序）得到的新序列。

给定一个大小为 $n$ 的整数数组 $a$，其中每个元素均为 $1$ 到 $3$ 之间的整数。你的任务是计算数组 $a$ 中美丽子序列的数量。由于答案可能很大，请将其对 $998244353$ 取模后输出。

## 说明/提示

在示例的第一个测试用例中，以下子序列是美丽的：
- $[a_3, a_4, a_7]$；
- $[a_3, a_5, a_7]$；
- $[a_3, a_4, a_5, a_7]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
7
3 2 1 2 2 1 3
4
3 1 2 2
3
1 2 3
9
1 2 3 2 1 3 2 2 3```

### 输出

```
3
0
1
22```

# 题解

## 作者：arrow_king (赞：11)

观察性质发现，合法的序列只有可能是 $1,2,2,\dots,2,3$，其中至少有一个 $2$。

一个朴素的想法是枚举所有的 $1$ 和所有的 $3$，记它们之间 $2$ 的数量是 $c$，则他们的贡献是 $2^c-1$。但是这样的时间复杂度是 $O(n^2)$，无法通过。

考虑对每个 $1$ 求出其后面所有 $3$ 的总贡献。记 $s_i$ 表示 $i$ 位置之前 $2$ 的数量，那么 $i\sim j$ 之间的贡献是 $2^{s_j-s_{i-1}}-1$。再设 $p_i$ 表示 $i$ 后面 $3$ 的数量。考虑一个位置 $i$ 的贡献：

$$
\begin{aligned}
\sum_{j>i,a_j=3}(2^{s_j-s_{i-1}}-1)&=\sum_{j>i,a_j=3}2^{s_j-s_{i-1}}-p_i\\
&=\dfrac{1}{2^{s_{i-1}}}\sum_{j>i,a_j=3}2^{s_j}-p_i
\end{aligned}
$$

只需要维护 $[a_i=3]2^{s_i}$ 的后缀和即可，复杂度 $O(n\log\mathrm{mod})$。

---

## 作者：Eous (赞：7)

### 题意

定义一个“美丽”的序列为：除第 $1$ 个数，每个数左边都有至少 $1$ 个比它小，除最后一个数，每个数右边都有至少 $1$ 个比它大。给定一个只由 $\{1,2,3\}$ 组成的数组，求有多少个“美丽”的子串。

### 题解

我们看到只会有 $\{1,2,3\}$ 出现，想到从这里入手。因为在数组里不会有比 $1$ 更小的数，所以 $1$ 只会是子序列的左端点。同理可得 $3$ 只会是子序列的右端点。而它们俩中间夹的 $2$ 会和它们组成一个合法子序列。如果一对 $1$ 和 $3$ 中间夹了 $k$ 个 $2$，那么合法的子串数量就是 $2^k - 1$。现在我们就有 $O(n^2)$ 做法：循环每个 $1$，对于每个 $1$ 循环找到它后面的每个 $3$ 并统计 $1$ 和这个 $3$ 之间夹了多少个 $2$，然后统计答案。

我们还得想如何把它变成 $O(n)$ 或者 $O(n \log n)$ 的做法。我们掏一个样例：`1 2 3 2 1 3 2 2 3`。对于每个 $1$，我们把它对于答案的贡献写出来。

$$
\begin{aligned}
\text{第一个 1} \quad & 2^1 + 2^2 + 2^4 - 3 \\
\text{第二个 1} \quad & 2^0 + 2^2 - 2 \\
\end{aligned}
$$

现在我们需要人类智慧。我们发现后面减的数就是这个 $1$ 后面 $3$ 的个数。再把后面减掉的数先扔掉，发现就是一堆 $2^k$ 相加。结合样例分析：每个 $3$ 会使贡献的项数增加 $1$，每个 $2$ 会使贡献乘 $2$。那么我们从后往前循环，记录 $cnt$ 表示出现了多少个 $3$，$now$ 表示现在如果出现一个 $1$ 需要计算答案，它贡献的 $2^k$ 部分是多少。那么我们按照如下过程模拟：

- 遇到 $3$ 就 $cnt \leftarrow cnt + 1，now \leftarrow now + 2^0$。
- 遇到 $1$ 就把答案增加 $now - cnt$。
- 遇到 $2$ 就 $now \leftarrow now \times 2$。

这样我们就成功的搞出了一个 $O(n)$ 的人类智慧解法。

### 代码

```cpp
#include<bits/extc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int n;
void solve()
{
    cin >> n;
    vector<int>a(n + 5);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int cnt = 0,ans = 0,now = 0;
    for (int i = n; i >= 1; i--)
    {//从后往前循环，模拟即可
        if (a[i] == 3)
        {
            cnt++;
            now++;
        }
        else if (a[i] == 1)
            ans = (ans + now - cnt + mod) % mod;
        else
            now = (now << 1) % mod;
    }
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：6)

[CF2069C](https://www.luogu.com.cn/problem/CF2069C)

## Statement

我们定义一个序列为美丽的当它满足：

- 序列长度至少为 $3$。
- 除第一个元素外，每个元素左侧都有一个小于它的元素。
- 除最后一个元素外，每个元素右侧都有一个大于它的元素。

给定长度 $n$ 的数组 $a$，求 $a$ 的所有子序列中美丽的子序列的个数，答案对 $998244353$ 取模。

$n \leq 2 \times 10^5,a_i \in [1,3]$。

## Solution

我们拥有人类智慧。

看到 $a_i \in [1,3]$ 我们试试考虑算贡献，记产生正贡献 / 负贡献分别为 $G,F$。

$1$ 开头 $3$ 结尾中间全是 $2$ 的子序列满足条件。

- 对于 $a_i = 2$，它对于左右两边的 $1,3$ 均有贡献，可以插在中间，所以更新 $G \leftarrow G \times 2$。
- 对于 $a_i = 3$，它对于左边的 $1,2$ 有贡献，但是右边毫无贡献，只能作为末尾，更新 $G \leftarrow G + 1,F \leftarrow F + 1$。
- 对于 $a_i = 1$，同理只能作为开头，这时更新答案 $ans \leftarrow ans + G - F$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 33, MOD = 998244353;
int T, n, A[MAXN];

signed main() {
	scanf ("%lld", &T);
	while (T --) {
		scanf ("%lld", &n);
		for (int i = 1; i <= n; i ++)
			scanf ("%lld", &A[i]);
		int F = 0, G = 0, Ans = 0;
		for (int i = n; i; i --) {
			if (A[i] == 2) {
				G = (G << 1) % MOD;
			} else if (A[i] == 3) {
				F ++, G ++;
			} else {
				Ans = (Ans + G - F + MOD) % MOD;
			}
		}
		printf ("%lld\n", Ans);
	}	
	return 0;
}
```

---

## 作者：yvbf (赞：3)

![](bilibili:BV1DkAzetEX9?t=534)

---

## 作者：_xguagua_Firefly_ (赞：3)

### 分析

由美丽数列的定义得，一个美丽数列一定是形如 $[1,2,2,\ldots,2,3]$ 的。由此启发我们来枚举每一对可以匹配的 $1,3$。

然后我们发现，子序列也是可以算作美丽数列的，设一共有 $k$ 个 $2$，则美丽数列的数量为 $\sum _ {i = 1} ^ {k} C _ {k} ^ {i} = 2 ^ {k} - 1$。

运用前缀和的思想，我们记 $sum _ {i} = \sum _ {j = 1} ^ {i} [a _ {j} = 2]$，则我们可以枚举每一对 $1$ 和 $3$，然后计算答案。

上面这个算法是 $\Omicron(n ^ {2})$，无法通过此题，考虑优化。

我们发现，每一个 $3$ 会和前面所有 $1$ 匹配，记 $cnt _ {i} = \sum _ {j = 1} ^ {i} [a _ {j} = 1]$，若 $1$ 的位置为 $p$，$3$ 的位置为 $pos$，则贡献为 $2 ^ {sum _ {pos} - sum _ {p _ {1}}} + \ldots + 2 ^ {sum _ {pos} - sum _ {p _ {cnt _ {pos}}}} - cnt _ {pos}$。

我们可以把每一项的 $2 ^ {sum _ {pos}}$ 提出来，后面就是 $\sum _ {i = 1} ^ {cnt _ {pos}} 2 ^ {-sum _ {p _ i}} = \sum _ {i = 1} ^ {cnt _ {pos}} (2 ^ {sum _ {p _ i}}) ^ {-1}$，然后再用前缀和，记 $invsum _ {i}$ 表示 $\sum _ {j = 1} ^ {i} (2 ^ {sum _ {j}}) ^ {-1} \times [a _ {j} = 1]$，则我们只需要枚举所有的 $a _ {i} = 3$，然后将 $2 ^ {sum _ {i}} \times invsum _ {i} - cnt _ {i}$ 计入答案即可。

时间复杂度为 $\Omicron(n)$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MOD = 998244353,MAXN = 2e5 + 24;
int T;
int n;
inline int qpow(int b,int p)
{
    int res = 1;
    while(p)
    {
        if(p & 1)
            res = res * b % MOD;
        b = b * b % MOD;
        p >>= 1;
    }
    return res;
}
#define inv(x) qpow(x,MOD - 2)
inline void Solve()
{
    cin >> n;
    vector<int> a(n + 1,0),sum(n + 1,0),invsum(n + 1,0),cnt(n + 1,0);
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + (a[i] == 2);
    }
    for(int i = 1;i <= n;i++)
    {
        invsum[i] = invsum[i - 1];
        cnt[i] = cnt[i - 1] + (a[i] == 1);
        if(a[i] == 1)
            invsum[i] = (invsum[i] + inv(qpow(2,sum[i]))) % MOD;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
    {
        if(a[i] == 3)
            ans = (ans + qpow(2,sum[i]) * invsum[i] % MOD - cnt[i] + MOD) % MOD;
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
        Solve();
}
```

---

## 作者：_mi_ka_ (赞：2)

[题目传送门](https://codeforces.com/contest/2069/problem/C)

## 题目大意

有一个只有 $1、2、3$ 组成的序列 $a$，找**漂亮子序列**（对于非首元素，左边都有比它小的元素，非尾元素，右边都有比它大的元素）的个数，答案对 $998244353$ 取模。

## 解题思路

对于只有 $1、2、3$ 组成的序列，不难想出这个漂亮子序列的形式：首元素是 $1$，尾元素是 $3$，中间必须全是 $2$。

对于每一个 $1$，遍历它后面的这个序列时，当它遇到 $3$ 时，它和这个 $3$ 对答案的贡献为 $2^{cnt2}-1$（$cnt2$ 为当前 $1$ 和当前 $3$ 之间的 $2$ 的个数）。则这个 $1$ 对答案的总贡献为
$$\sum_{i=1}^{n}[a_i=1]\sum_{j=i+1}^{n}[a_j=3](2^{cnt2_{i,j}}-1)$$

其中 $[bool]$ 为这个布尔表达式的值。

显然这个式子是需要 $n^2$ 的复杂度实现的，如何简化时间复杂度呢？

考虑将第一个 $1$ 所贡献的答案求出为 $ans1$，在遍历时想要在 $ans1$ 的基础上进行运算得出后面的 $1$ 对答案的贡献：

- 用一个 $3$ 的个数的后缀 $cnt3$ 代表 $a_i$ 后面的 $3$ 的个数，显然每遇到一个 $3$，$cnt3$ 的个数减一；
- 每遇到一个 $2$，对于这个 $2$ 后面的每个 $3$，它对答案的贡献都要从 $2^{cnt2}-1$ 变为 $2^{cnt2-1}-1$，操作为 $-1$ 再 $\times \frac{1}{2}$。则遇到这个 $2$，对 $ans1$ 的总变化为 $-cnt3$ 再 $\times \frac{1}{2}$。
- 每遇到一个 $1$，此时的 $ans1$ 就是它对答案的变化，直接加到答案上即可。

预处理求出 $ans1$ 和 $cnt3$ 的时间复杂度为 $O(n)$，遍历序列的复杂度为 $O(n\log m)$，其中 $m$ 为模数 $998244353$。

总时间复杂度 $O(n\log m)$。

## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n;
int a[200005]; 
int re()//快读 
void wr(int x)//快写 
int ksm(int a,int b)//快速幂 
{
    int ans=1;
    for(;b;a*=a,a%=mod,b>>=1)
        if(b&1)
            ans*=a,ans%=mod;
    return ans;
}
signed main(){
    int T=re();
    while (T--)
    {
        int n=re(),ans=0;
        for(int i=1;i<=n;i++)
            a[i]=re();
        int cnt2=0,cnt3=0;
        int ans1=0,pos=n;//pos为第一个1的位置 
        for(int i=1;i<=n;i++)
            if(a[i]==1)
            {
                pos=i;
                break;
            }
        for(int i=pos;i<=n;i++)
            if(a[i]==2)
                cnt2++;
            else if(a[i]==3)
            {
                ans1+=ksm(2,cnt2)-1;//这个3对答案的贡献 
                ans1%=mod;
                cnt3++;
            }
        ans+=ans1;
        for(int i=pos+1;i<=n;i++)
            if(a[i]==2)//遇到2 
                ans1-=cnt3,ans%=mod,ans+=mod,ans%=mod,ans1*=ksm(2,mod-2),ans1%=mod;
            else if(a[i]==1)
                ans+=ans1,ans%=mod;
            else
                cnt3--;//遇到3 
        wr(ans),puts("");
	}
    return 0;
}
```

---

## 作者：Eason_cyx (赞：2)

困难题。一个重要的性质是 $\color{red}\bf{1 \le a_i \le 3}$。那么考虑从这入手，设 $f_{1/2/3}$ 表示当前考虑的这个数是 $1/2/3$ 时的方案数。

然后？你会发现这里说的一个数前面有数比他大有点怪，仔细考虑一下。假设 $a_x$ 前面比它小的离他最近的是 $ap_x$。那么不难发现 $ap_{ap_{ap_{\dots}}} = 1$。所以第一个数一定比后面所有数小，同理最后一个数一定比前面所有数大。又因为 $a_i$ 的范围，所以只能 $a_1=1,a_{\text{siz}}=3$，剩下的是 $2$。那么计算方案数就不难了，有转移方程：

$$f_i=f_i + f_{i-1} + [i = 2] \times f_i$$

（其实本来是 $f_{i,1/2/3}$ 的，这里直接滚动数组了）

---

## 作者：Engulf (赞：2)

较优秀且不用动脑子的做法。

根据题目定义发现，值域为 $\{1, 2, 3\}$ 时，合法的子序列只能为 $1, \underbrace{2, 2 \cdots 2}_{t 个}, 3$，且 $t \ge 1$。

考虑动态规划，设 $f_i$ 表示以 $a_i$ 结尾的是合法子序列的 **前缀** 的数量，根据定义得到转移如下：
- 若 $a_i = 1$，$f_i = 1$，因为 $1$ 只能有一个且必须是第一个；
- 若 $a_i = 2$，$f_i = \sum\limits_{j=1}^{i-1} f_j\cdot[a_j=1\vee a_j=2]$，$2$ 可以接在 $2$ 或 $1$ 的后面；
- 若 $a_i = 3$，$f_i = \sum\limits_{j=1}^{i-1} f_j\cdot[a_j=2]$，因为 $3$ 只能有一个且必须是最后一个，所以只能接在 $2$ 的后面。

其中函数 $[P]$ 在命题 $P$ 为真时值为 $1$，$P$ 为假时值为 $0$。

最终的答案是合法的子序列数量，即以 $3$ 结尾的 $f_i$ 之和 $\sum\limits_{i=1}^n f_i\cdot[a_i=3]$。

朴素地做是 $\Theta(n^2)$ 的，发现简单地使用前缀和优化就能做到 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5, mod = 998244353;

int n;
int a[N], f[N];
int pre[N][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (a[i] == 1) f[i] = 1;
            else if (a[i] == 2) f[i] = (pre[i - 1][1] + pre[i - 1][2]) % mod;
            else f[i] = pre[i - 1][2];
            for (int j = 1; j <= 3; j++)
                pre[i][j] = (pre[i - 1][j] + (j == a[i] ? f[i] : 0)) % mod;
            if (a[i] == 3) ans = (ans + f[i]) % mod;
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

题目三个条件。如果有 $1\le a_{i}\le 3$ 的话，那么如果我们对于每个位置都要这样满足，中间位置就只能填 $2$，因为左边和右边需要比它小和比它大的数。其次，左边只能填 $1$，否则第二个数就只能填 $3$ 或者根本不能填，这时候，右边再想找到一个比它大的数是不可能的，但是我们限长为 $3$，所以不合法。容易发现右边也等价的只能填 $3$。于是做由尾挂点即可。

具体统计，我们针对每一个 $3$ 统计与前面所有的 $1$ 中间 $2$ 的个数，对于每一个 $2$ 的个数 $k$，算 $2^k-1$ 加入答案即可。

但是这样太慢了，考虑优化，于是我们考虑继承，如果新加入了一个 $2$，那么之前所有的 $1$ 和后面 $3$ 对答案的预备贡献都要加一乘二再减一（当然，所有 $1$ 最开始的预备贡献是 $0$），当然可以用线段树，但是我们发现 $(x+1)\times 2 - 1=2x+1$，并且由结合律（我们可以把所有当前 $1$ 的预备贡献都加起来，一起做运算），所以我们可以直接算，因为我们除了 $1$，没有预备贡献，所以我们需要记录 $1$ 的个数。

这题我们观察了性质，手玩了样例，运用了挂点的统计方法，运用了结合律。

Code：

```cpp
// Problem: C. Beautiful Sequence
// Contest: Codeforces - Educational Codeforces Round 174 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/2069/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int X = 998244353;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n + 10);
        upp(i, 1, n) cin >> a[i];
        int last = 0, ans = 0, cnt = 0;
        upp(i, 1, n) {
            if (a[i] == 1) cnt++;
            if (a[i] == 2) (((last *= 2) %= X) += cnt) %= X;
            if (a[i] == 3) ans += last;
        }
        cout << (ans + X) % X << endl;
    }
    return 0;
}
```

---

## 作者：Magallan_forever (赞：0)

#### 简要说明题意：

若一个序列长度至少为 $3$，且对于除第一个元素外的所有元素，左侧均有一个更小值，对于除最后一个元素外的所有元素，右侧均有一个更大值，那么这个序列就是一个“漂亮的”序列。

现在给出含 $n$ 个元素的序列 $a$，满足 $1 \leq a_i \leq 3$。求 $a$ 有多少个（可不连续的）子序列是“漂亮的”序列，答案对 $998244353$ 取模。

#### 题目分析：

一个“漂亮的”序列，第一个元素一定是最小值，最后一个元素一定是最大值（如果最小/最大值位于中部，左侧/右侧一定没有更小/更大值了，矛盾。）。

并且题目又保证 $1 \leq a_i \leq 3$。那就说明，**“漂亮的”序列一定是 $1,2,2,\dots,3$ 的形式**。

那就好解决了，对于每一个 $1$，我们找后面的每一个 $3$，假如有 $k$ 个 $3$，每个 $3$ 与 $1$ 之间有 $b_i$ 个 $2$，这个 $1$ 对答案的贡献就是 $\displaystyle{\sum_{i=1}^k{(2^{b_i}-1)}=\sum_{i=1}^k{2^{b_i}}-k}$（也就是 $2$ 的非空子集），我们可以考虑从左到右扫描，用线段树直接在每个 $3$ 的位置维护 $2^{b_i}$。

$a_i=1$ 就记录答案（区间 $[i,n]$ 的和），$a_i=2$ 就将 $b$ 序列 $-1$，也就是全体答案除以 $2$（实际上是乘 $499122177$，$2$ 在模 $998244353$ 意义下的逆元）。$a_i=3$ 则修改当前的 $k$ 值。

单次修改为 $O(\log_2n)$，时间复杂度 $O(\sum{n\log_2n})$ 是建树和扫描的复杂度。

还有一些实现细节，具体看代码注释：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int mod=998244353,rev2=499122177;
int fp(int a,int b,int mod){
    int ans=1;
    for(;b;a=(long long)a*a%mod,b>>=1) if(b&1) ans=(long long)ans*a%mod;
    return ans;
}
int a[200001],tot[200001]={1};
//维护的修改操作：区间乘
//维护的查询操作：区间加
struct node{
    int l,r,cnt,tag;
    node(int l_=0,int r_=0) :l(l_),r(r_),cnt(0),tag(1) {}
}tree[800001];
void push_down(int p){
    if(!tree[p].tag) return;
    int tag=tree[p].tag;
    tree[p].tag=1;
    tree[p<<1].cnt=(long long)tree[p<<1].cnt*tag%mod,tree[(p<<1)|1].cnt=(long long)tree[(p<<1)|1].cnt*tag%mod;
    tree[p<<1].tag=(long long)tree[p<<1].tag*tag%mod,tree[(p<<1)|1].tag=(long long)tree[(p<<1)|1].tag*tag%mod;
}
void push_up(int p){
    tree[p].cnt=(tree[p<<1].cnt+tree[(p<<1)|1].cnt)%mod;
}
void build(int p,int l,int r){
    tree[p]=node(l,r);
    if(l==r) if(a[l]==3) tree[p].cnt=tot[l];//建树只记录a_i=3的情况
    if(l^r) build(p<<1,l,(l+r)>>1),build((p<<1)|1,((l+r)>>1)+1,r),push_up(p);
}
void modify(int p,int l,int r){
    if(l<=tree[p].l&&tree[p].r<=r){
        tree[p].cnt=(long long)tree[p].cnt*rev2%mod;
        tree[p].tag=(long long)tree[p].tag*rev2%mod;
        return;
    }
    int mid=(tree[p].l+tree[p].r)>>1;
    push_down(p);
    if(l<=mid) modify(p<<1,l,r);
    if(mid<r) modify((p<<1)|1,l,r);
    push_up(p);
}
int query(int p,int l,int r){
    if(l<=tree[p].l&&tree[p].r<=r) return tree[p].cnt;
    int mid=(tree[p].l+tree[p].r)>>1,ans=0;
    push_down(p);
    if(l<=mid) ans+=query(p<<1,l,r),ans%=mod;
    if(mid<r) ans+=query((p<<1)|1,l,r),ans%=mod;
    return push_up(p),ans;
}
int main(){
    int T,n,cnt3,ans;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n),cnt3=0,ans=0;
        //读入，统计2^b_i和3的个数
        for(int i=1;i<=n;++i) scanf("%d",a+i),tot[i]=(tot[i-1]<<(a[i]==2))%mod,cnt3+=(a[i]==3);
        build(1,1,n);
        for(int i=1;i<=n;++i){
	        //这里query(1,i,n)在取模后有可能小于cnt3导致答案为负数，需要加一次mod
            if(a[i]==1) ans+=query(1,i,n)-cnt3,ans<0?ans=(ans+mod)%mod:ans%=mod;
            if(a[i]==2) modify(1,i,n);
            if(a[i]==3) --cnt3;
            // printf("i=%d ans=%d\n",i,ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

提供一种应该没人写的做法。

## 思路分析

考虑最终合法的字符串，形如：

$$1,2,2,2,\cdots,2,2,2,3$$

然后考虑对于每对 $1,3$  对答案的贡献是，它们中间 $2$ 的个数，记为 $cnt$，$2^{cnt}-1$。

然后考虑从左往右扫，每次遇到 $1$ 往数据结构里加入一个 $1$，遇到 $2$ 全局乘 $2$，遇到 $3$ 计算答案。

可以用线段树维护，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t,n,a[200005],cnt,ans;
int val[400005],tag[400005],ls[400005],rs[400005],dcnt,rt;
void pushup(int x){
	val[x]=(val[ls[x]]+val[rs[x]])%mod;
}
void pushdown(int x){
	if(tag[x]==1) return;
	val[ls[x]]=val[ls[x]]*tag[x]%mod;
	val[rs[x]]=val[rs[x]]*tag[x]%mod;
	tag[ls[x]]=tag[ls[x]]*tag[x]%mod;
	tag[rs[x]]=tag[rs[x]]*tag[x]%mod;
	tag[x]=1;
}
void build(int l,int r,int &x){
	x=++dcnt;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,ls[x]);
	build(mid+1,r,rs[x]);
	pushup(x);
}
void modify1(int l,int r,int pos,int k,int x){
	if(l==r){
		val[x]=k;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(x);
	if(pos<=mid) modify1(l,mid,pos,k,ls[x]);
	else modify1(mid+1,r,pos,k,rs[x]);
	pushup(x); 
}
void modify2(int l,int r,int ql,int qr,int k,int x){
	if(ql<=l && r<=qr){
		val[x]=val[x]*k%mod;
		tag[x]=tag[x]*k%mod;
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(ql<=mid) modify2(l,mid,ql,qr,k,ls[x]);
	if(qr>=mid+1) modify2(mid+1,r,ql,qr,k,rs[x]);
	pushup(x);
}
int query(int l,int r,int ql,int qr,int x){
	if(ql<=l && r<=qr) return val[x];
	pushdown(x);
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid) ans=(ans+query(l,mid,ql,qr,ls[x]))%mod;
	if(qr>=mid+1) ans=(ans+query(mid+1,r,ql,qr,rs[x]))%mod;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		build(1,n,rt);
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1){
				modify1(1,n,i,1,rt);
				cnt++;
			}else if(a[i]==2){
				modify2(1,n,1,i,2,rt);
			}else{
				ans=(ans+query(1,n,1,i,rt)-cnt+mod)%mod;
		    }
		}
		cout<<ans<<'\n';
		ans=0;
		for(int i=1;i<=dcnt;i++){
			val[i]=tag[i]=ls[i]=rs[i]=0;
		}
		dcnt=cnt=0;
	}
}
```

---

