# [USACO25OPEN] Lazy Sort P

## 题目背景

**本翻译使用 AI 生成。**

## 题目描述

农夫约翰（Farmer John）有 $N$（$2 \le N \le 5 \cdot 10^6$）头奶牛，他试图让它们依靠自身的懒惰性来排序一个长度为 $N$ 的非负整数数组 $A$。他有很多沉重的箱子，所以他把奶牛们排成一列，其中奶牛 $i+1$ 在奶牛 $i$ 的后面，并给奶牛 $i$ 分配 $a_i$（$0 \le a_i$）个箱子。

奶牛们天生就很懒，所以它们总是想把工作推给别人。从奶牛 $1$ 到 $N-1$，每头奶牛依次看向它后面的奶牛。如果奶牛 $i$ 的箱子严格多于奶牛 $i+1$，奶牛 $i$ 会认为这“不公平”，并把它的一个箱子交给奶牛 $i+1$。这个过程会一直重复，直到每头奶牛都满意为止。

然后，农夫约翰会记下每头奶牛 $i$ 持有的箱子数量 $b_i$，并用这些值创建一个数组 $B$。如果 $B = \text{sorted}(A)$（即 $A$ 排序后的结果），那么农夫约翰就会很高兴。不幸的是，农夫约翰忘记了 $A$ 中除了 $Q$（$2 \le Q \le \min(N, 100)$）个值之外的所有值。幸运的是，这些记住的值包括了他打算给第一头和最后一头奶牛的箱子数量。FJ 记住的每个值都以 $c_i\; v_i$ 的形式给出，表示 $a_{c_i} = v_i$（$1 \le c_i \le N$，$1 \le v_i \le 10^9$）。请确定有多少种不同的方法可以填补缺失的值，使得他在奶牛们完成懒惰排序后会感到高兴，结果对 $10^9 + 7$ 取模。

## 说明/提示

### 样例 1 解释

在这个例子中，FJ 记住了数组两端的值。数组 $[3, 2, 2]$ 和 $[3, 3, 2]$ 是有效的数组，它们会在懒惰排序结束时让 FJ 高兴。

### 测试点限制

- 测试点 3-4: $N,v_i\leq 100$；
- 测试点 5-6: $N\leq 100$ 且 $v_i\leq 10^6$；
- 测试点 7-9: $N\leq 2\times 10^5$ 且 $v_i\leq 10^6$；
- 测试点 10-12: $N\leq 2\times 10^5$；
- 测试点 13-15: 无额外限制。

## 样例 #1

### 输入

```
3 2
1 3
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
6 3
1 1
3 3
6 5```

### 输出

```
89```

# 题解

## 作者：沉石鱼惊旋 (赞：3)

# 做法

考虑先把 $B=\operatorname{sorted}(A)$ 的 $A$ 条件表示出来。

先分析 $n=2$ 的情况。此时只有 $a_1\leq a_2$ 或者 $a_1=a_2+1$ 的情况才是合法的。就是不需要操作或者一次操作可以交换。

同理扩展一下，这里我是手玩了几个然后猜猜猜猜出来的。相当于问 $A$ 能否被分成若干个区间，满足区间内极差不超过 $1$，并且上一个区间的 $\max$ $\leq$ 这个区间的 $\min$。就是区间内能够被排好，不同区间也不影响。

再分析一下这个东西，就是设 $p_i=\max\limits_{j=1}^i a_i$，需要满足 $p_i\leq a_i+1$。

然后有一个显然的 $\mathcal O(nV^2)$ 的 DP，设 $f_{i,j}$ 表示前 $i$ 个数 $p_i=j$ 的方案数，转移枚举第 $i$ 个数填什么，判断是否能成为前缀 $\max$。

这个 DP 再套一个前缀和优化可以做到 $\mathcal O(nV)$，我不知道怎么继续优化了，但是可以验证猜的结论。

然后我就因为不会了在机房被嘲笑了一上午（恼）。

接下来我们考虑如果知道了 $p$ 的序列能还原出多少个 $a$。

考虑 $p$ 的断层数量 $c$，就是前缀 $\max$ 的数量。设一共有 $c$ 个断层，那么有 $n-c$ 个位置是可以任选 $p_i$ 或 $p_i-1$ 的。这里贡献是 $2^{n-c}$。

但是这里我们只知道 $p$ 的首尾项，具体的断层数量 $c$ 我们要枚举。

除了 $2^{n-c}$ 的贡献，剩下的就是 $\binom{L-1}{c-1}\times\binom{V}{c-2}$ 即前缀 $\max$ 的出现的方案。$L$ 是长度，$V$ 是可选的值域范围。由于首尾确定，所以只有 $c-2$ 个可以自选。

这里 $V$ 可能很大，但是枚举的下指标 $c$ 是连续的，组合数可以从 $\binom{V}{0}$ 开始直接暴力算，每次算一下 $\binom{V}{c-1}$ 和 $\binom{V}{c}$ 的差的贡献。

这样我们就解决了 $q=2$ 时的问题。

其他情况相当于若干个 $q=2$ 合并起来。

设 $f_{i,j\in\{0,1\}}$ 表示 $p_i=a_i+j$ 时的方案数。转移就是 $f_{i,0}=f_{j,0}\times c(0,0)+f_{j,1}\times c(1,0)$ 和 $f_{i,0}=f_{j,0}\times c(0,1)+f_{j,1}\times c(1,1)$。

求出这个系数 $c$ 即可。

令长度为 $L$，首项为 $x$，末项为 $y$ 的 $p$，可以生成出的合法的 $a$ 的个数为 $F(L,x,y)$。

设此时有 $len=c_{i}-c_{i-1}+1,x=c_{i-1},y=c_i$。

则有：
$$
\begin{aligned}
c(0, 0) &= F(L, x, y) - F(L - 1, x, y)\\
c(0, 1) &= F(L - 1, x, y + 1)\\
c(1, 0) &= F(L, x + 1, y) - F(L - 1, x + 1, y)\\
c(1, 1) &= F(L - 1, x + 1, y + 1)\\
\end{aligned}
$$
$c(0,0)$ 考虑如果在 $c_i-1$ 的位置取到了 $p_{c_i-1}=y$，那么 $c_i$ 的位置不一定会取到 $y$，要减掉一部分方案。

$c(0,1)$ 考虑如果在 $c_i$ 的位置一定取不到 $p_{c_i}=y+1$，所以只能在 $[c_{i-1},c_i)$ 的位置出现了 $y+1$，区间长度小 $1$。

$c(1,0)$ 与 $c(1,1)$ 的推导类似上两个。

实现注意一下细节，因为 $n$ 很大多带个 $\log$ 可能就寄了。逆元和 $2^k$ 这种东西都要线性预处理出来。

# 代码

<https://www.luogu.com.cn/record/212386055>

```cpp
#include <bits/stdc++.h>
using namespace std;
template <int P>
class mod_int
{
    using Z = mod_int;

private:
    static int mo(int x) { return x < 0 ? x + P : x; }

public:
    int x;
    int val() const { return x; }
    mod_int() : x(0) {}
    template <class T>
    mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
    bool operator==(const Z &rhs) const { return x == rhs.x; }
    bool operator!=(const Z &rhs) const { return x != rhs.x; }
    Z operator-() const { return Z(x ? P - x : 0); }
    Z pow(long long k) const
    {
        Z res = 1, t = *this;
        while (k)
        {
            if (k & 1)
                res *= t;
            if (k >>= 1)
                t *= t;
        }
        return res;
    }
    Z &operator++()
    {
        x < P - 1 ? ++x : x = 0;
        return *this;
    }
    Z &operator--()
    {
        x ? --x : x = P - 1;
        return *this;
    }
    Z operator++(int)
    {
        Z ret = x;
        x < P - 1 ? ++x : x = 0;
        return ret;
    }
    Z operator--(int)
    {
        Z ret = x;
        x ? --x : x = P - 1;
        return ret;
    }
    Z inv() const { return pow(P - 2); }
    Z &operator+=(const Z &rhs)
    {
        (x += rhs.x) >= P && (x -= P);
        return *this;
    }
    Z &operator-=(const Z &rhs)
    {
        (x -= rhs.x) < 0 && (x += P);
        return *this;
    }
    Z operator-() { return -x; }
    Z &operator*=(const Z &rhs)
    {
        x = 1ULL * x * rhs.x % P;
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                  \
    friend T operator o(const Z &lhs, const Z &rhs) \
    {                                               \
        Z res = lhs;                                \
        return res o## = rhs;                       \
    }
    setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
        friend istream &
        operator>>(istream &is, mod_int &x)
    {
        long long tmp;
        is >> tmp;
        x = tmp;
        return is;
    }
    friend ostream &operator<<(ostream &os, const mod_int &x)
    {
        os << x.val();
        return os;
    }
};
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
const int P = 1000000007;
using Z = mod_int<P>;
int n, q;
int l, r;
int x, y;
Z ans = 1;
Z f[2];
Z g[2];
Z inv[5000020];
Z pw[5000020];
struct binom
{
    int n, i;
    Z r;
    void init(int m)
    {
        n = m;
        i = 0;
        r = 1;
    }
    Z C(int j)
    {
        if (n < 0 || j < 0 || n < j)
            return 0;
        while (i + 1 <= j)
        {
            i++;
            r *= n - i + 1;
            r *= inv[i];
        }
        return r;
    }
};
Z calc(int len, int x, int y)
{
    if (x > y)
        return 0;
    if (len == 1 && x != y)
        return 0;
    if (x == y)
        return pw[len - 1];
    Z s = 0;
    binom C1, C2;
    C1.init(len - 1);
    C2.init(y - x - 1);
    for (int c = 2; c <= min(y - x + 1, len); c++)
    {
        s += C1.C(c - 1) *
             C2.C(c - 2) *
             pw[len - c];
    }
    return s;
}
int main()
{
    read(n, q);
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = inv[P % i] * (P - P / i);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * 2;
    l = -1;
    f[0] = 1;
    while (q--)
    {
        read(r, y);
        if (~l)
        {
            memcpy(g, f, sizeof(g));
            memset(f, 0, sizeof(f));
            Z c00 = calc(r - l + 1, x, y) - calc(r - l, x, y);
            Z c01 = calc(r - l, x, y + 1);
            Z c10 = calc(r - l + 1, x + 1, y) - calc(r - l, x + 1, y);
            Z c11 = calc(r - l, x + 1, y + 1);
            f[0] += g[0] * c00;
            f[0] += g[1] * c10;
            f[1] += g[0] * c01;
            f[1] += g[1] * c11;
        }
        l = r;
        x = y;
    }
    cout << f[0] + f[1] << '\n';
    return 0;
}
```

---

## 作者：masonpop (赞：1)

纯数学做法。几乎没有任何 DP 相关。

感觉做法还挺厉害的。

肯定要寻找序列合法的条件，直接给出结论：考虑其差分数组 $d$，则合法等价于，$d$ 中的负项均为 $-1$，且去掉 $0$ 之后不能有相邻的 $-1$。

考虑对每一段求方案数，然后段之间的拼接就是维护一个 $f_{0/1}$ 状物即可。可以抽象为，求 $f(L,S)$ 表示长度为 $L$ 的合法差分序列且和为 $S$ 的方案数。这里合法的定义和上面一样。

容易发现 $0$ 是没有用的，最后插进去即可。然后序列会被 $-1$ 分成若干段，大概有四种情况且都差不多。这里只考虑开头为 $-1$ 且末尾不是的情况。

考虑枚举 $-1$ 的个数 $k$ 和非 $0$ 正数的个数 $c$，则经过一些插板可以得到答案式

$$\begin{aligned}\sum\limits_{k}\sum\limits_{c}\dbinom{S+k-1}{c-1}\dbinom{c-1}{k-1}\dbinom{L}{k+c}\end{aligned}$$

只考虑对 $c$ 的那一维循环优化，所以以下默认 $k$ 为定值。前两项显然是可以合并的，于是转化为

$$\begin{aligned}\sum\limits_{c}\dbinom{S+k-1}{k-1}\dbinom{S}{c-k}\dbinom{L}{k+c}\end{aligned}$$

前一项是定值，后面两项是范德蒙德卷积的形式，结束了。

暴力计算组合数是平方的，优化也很简单，随便拿个什么东西维护一下枚举 $k$ 时组合数的值即可。

由于实力原因赛时只写完了暴力计算组合数的版本，不保证后面一部分实现正确，但是过了暴力那一档所以式子应该是对的。

[平方代码](https://usaco.org/current/viewsource.php?sid=7351820)。

upd：正解代码也是对的，但是多个 $\log$。考虑使用一些手法，发现把组合数倒过来推就行了。这样只需要处理 $1\sim n$ 的逆元。有点 dirty work 虽然。

[线性代码](https://www.luogu.com.cn/paste/x7uh23rt)。这部分的可读性极差，建议理解前面的内容后自己手推一下。

---

## 作者：Purslane (赞：0)

# Solution

简单计数题。

首先考虑判定一个序列是否合法。

注意如果我们选择了 $i$ 使得 $a_i \leftarrow a_i-1$，$a_{i+1} \leftarrow a_{i+1}+1$。在 $a_{i+1} \neq a_i-1$ 的情况下，一定有操作前的序列 $\{a\}$ 的字典序（比较可重集，从大到小比较）比 $\{a'\}$ 大。而字典序在操作后显然不会变大，这样不就倒闭了吗。

所以要求任意时刻，若操作了 $i$ 一定有 $a_i - 1 = a_{i+1}$。

这个等价于：$a_i \ge \max_{1 \le j < i} a_j + 1$（对 $i=1$ 没有限制。）

这样会想到一个 DP：设 $dp_{i,j}$ 表示，前 $i$ 个数的最大值为 $j$。

转移是 $dp_{i,j} = 2 dp_{i-1,j} + \sum_{k < j}dp_{i-1,k}$。

有限制的情况稍微处理一下就行，这样得到了 $O(n V)$ 的做法。考虑优化。

只在关键点处记录 $dp_{i,0/1}$ 表示，当前最大值是 $a_i$ 还是 $a_i+1$。

考虑关键点之间的转移。如果转移到 $a_i$ 上，那么枚举最大值何时变为 $a_i$（其实只有在 $i$ 和不在 $i$ 两种本质不同的手段）。枚举之后，钦定 $(lst,i)$ 中某 $k$ 个时间点发生了最大值变化，最大值怎么变的就是一个组合数。而其他位置都能带来 $2$ 的贡献，再乘上二的幂即可。

如果转移到 $a_{i}+1$ 上，反而更加简单，因为你不用枚举是否在 $i$ 发生了最大值变化。

复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e6+10,MOD=1e9+7,MAXM=100+10;
int n,q,c[MAXM],v[MAXM],frac[MAXN],inv[MAXN],pw[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int dp[MAXM][2];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q; frac[0]=1;ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2); roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	pw[0]=1; ffor(i,1,n) pw[i]=pw[i-1]*2%MOD;
	ffor(i,1,q) cin>>c[i]>>v[i];
	dp[1][0]=1;
	ffor(i,2,q) {
		ffor(lst,0,1) {
			if(v[i-1]+lst<v[i]) {
				//在 (v[i-1]+lst,v[i]) 中钦定 t 个数
				//在 (c[i-1],c[i]) 中钦定 t 个位置
				//乘上 2^{c[i]-c[i-1]-1-t}
				int len1=v[i]-v[i-1]-lst-1,len2=c[i]-c[i-1]-1,mul=1;
				ffor(t,0,min(len1,len2)) {
					dp[i][0]=(dp[i][0]+mul*inv[t]%MOD*inv[t]%MOD*pw[len2-t]%MOD*dp[i-1][lst])%MOD;
					mul=mul*(len1-t)%MOD*(len2-t)%MOD;
				}
			}
			//Case 2. 在中间变为最大值，包括之前 
			if(v[i-1]+lst<=v[i]) {
				//在 (v[i-1]+lst,v[i]) 中钦定 t 个数
				//在 (c[i-1],c[i]) 中钦定 t+1 个位置
				//乘上 2^{c[i]-c[i-1]-t-2} 
				if(v[i-1]+lst==v[i]) dp[i][0]=(dp[i][0]+dp[i-1][lst]*pw[c[i]-c[i-1]-1])%MOD;
				else {
					int len1=v[i]-v[i-1]-lst-1,len2=c[i]-c[i-1]-1,mul=len2;
					ffor(t,0,min(len1,len2-1)) {
						dp[i][0]=(dp[i][0]+mul*inv[t]%MOD*inv[t+1]%MOD*pw[len2-t-1]%MOD*dp[i-1][lst])%MOD;
						mul=mul*(len1-t)%MOD*(len2-t-1)%MOD;
					}
				}
			}
			//转移到 1
			if(v[i-1]+lst<=v[i]+1) {
				//在 (v[i-1]+lst,v[i]] 中钦定 t 个数
				//在 (c[i-1],c[i]) 中钦定 t+1 个位置
				//乘上 2^{c[i]-c[i-1]-t-2} 
				if(v[i-1]+lst==v[i]+1) dp[i][1]=(dp[i][1]+dp[i-1][lst]*pw[c[i]-c[i-1]-1])%MOD;
				else {
					int len1=v[i]-v[i-1]-lst,len2=c[i]-c[i-1]-1,mul=len2;
					ffor(t,0,min(len1,len2-1)) {
						dp[i][1]=(dp[i][1]+mul*inv[t]%MOD*inv[t+1]%MOD*pw[len2-t-1]%MOD*dp[i-1][lst])%MOD;
						mul=mul*(len1-t)%MOD*(len2-t-1)%MOD;
					}
				}
			}
		}
	}
	cout<<(dp[q][0]+dp[q][1])%MOD;
	return 0;
}
```

---

