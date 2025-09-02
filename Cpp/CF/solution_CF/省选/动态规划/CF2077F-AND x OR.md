# AND x OR

## 题目描述

假设你有两个长度均为 $k$ 的数组 $c$ 和 $d$。当且仅当 $c$ 可以通过以下操作任意次变换为 $d$ 时，称这对数组 $(c, d)$ 是好的：

- 选择两个不同的下标 $i$ 和 $j$（$1 \leq i, j \leq k$，$i \neq j$）以及一个非负整数 $x$（$0 \leq x < 2^{30}$）。然后执行以下变换：
  - $c_i := c_i \mathbin{\&} x$（其中 $\&$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)）
  - $c_j := c_j \mathbin{|} x$（其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)）

给定两个长度为 $n$ 的数组 $a$ 和 $b$，其中元素均为不超过 $m$ 的非负整数。你可以对这两个数组进行任意次以下两种操作：

1. 选择一个下标 $i$（$1 \leq i \leq n$），令 $a_i := a_i + 1$
2. 选择一个下标 $i$（$1 \leq i \leq n$），令 $b_i := b_i + 1$

注意在执行操作过程中，$a$ 和 $b$ 的元素可能会超过 $m$。

求使得数组对 $(a, b)$ 成为好的数组对所需的最小操作次数。

## 说明/提示

第一个测试用例中，已有 $a = b$。

第二个测试用例中，可以对下标 $i=2$ 执行两次操作 2。数组 $b$ 将变为 $[8, 8, 32]$，此时 $(a, b)$ 成为好的数组对。

第三个测试用例中，可以对下标 $i=1$ 执行一次操作 2，再对下标 $i=2$ 执行一次操作 1。可以证明无法用少于 2 次操作使 $(a, b)$ 成为好的数组对。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4 3
0 1 2 3
0 1 2 3
3 32
8 9 32
8 6 32
5 64
5 7 16 32 64
4 8 16 32 64
4 11
9 1 4 3
8 11 6 2
5 10
7 9 5 4 2
3 10 6 5 9```

### 输出

```
0
2
2
0
1```

# 题解

## 作者：irris (赞：1)

> 有两个序列 $a_1, \ldots, a_n$ 和 $b_1, \ldots, b_n$。你可以执行若干次操作，每次选择 $1 \leq i \neq j \leq n$ 和 $0 \leq x < 2^{30}$，将 $a_i \gets a_i\;|\;x$，$a_j \gets a_j\;\&\;x$。如果 $a$ 能变成 $b$，则称 $(a, b)$ 是好的。为了让 $(a, b)$ 变成好的，你可以执行若干次修改，每次修改选择 $1 \leq i \leq n$，然后让 $a_i \gets a_i + 1$ 或 $b_i \gets b_i + 1$。询问最少多少次修改能够让 $(a, b)$ 变成好的。令 $m = \max(\max a_i, \max b_i)$，那么 $\sum n \leq 2\cdot 10^6$，$\sum m \leq 2\cdot 10^6$，$0 \leq a_i, b_i \leq m$。

我们不加证明地给出结论。有解的充要条件是：$\forall 1 \leq i \leq n$ 满足 $a_i = b_i$，或者 $\exists 1 \leq i \neq j \leq n$ 满足 $b_i \subseteq b_j$。充要性容易证明，因为每次操作 $(i, j)$ 一定会带来 $b_i \subseteq x \subseteq b_j$。而对于两个条件，前者是容易计算的。

对于后者，考虑枚举一对 $i, j$ 要钦定 $b'_i \subseteq b'_j$，计算所需的最小步数 $(b'_i - b_i) + (b'_j - b_j)$（显然初始时也有 $b_i \leq b_j$）。首先，最优解离 $b'_i$ 的形式形如 $b_i$ 的某个 $0$ 变为 $1$（设这是在第 $z$ 位上）且末尾的若干 $1$ 全部变为 $0$。此时如果 $b_j$ 原来第 $z$ 位为 $0$，那么需要调整为 $1$；或者 $b_j$ 原来第 $z$ 位为 $1$，而 $b_j$ 的更高位不是 $b_i$ 的超集，也需要进行若干次调整。但这显然不如 $b'_j$ 减少到第 $0 \sim (z - 1)$ 位都为 $1$ 的状态，且 $b'_i$ 减少 $1$，一定是不优的。所以若 $b'_i > b_i$ 且 $b'_j > b_j$，一定能够调整到更优的状态。于是最终一定有 $b'_i = b_i$ 或 $b'_j = b_j$。**这带来了另一个关键结论：对于后者情况下，只需要考虑某一个 $\boldsymbol{b_i}$ 增加。**

首先答案 $r = \mathcal O(\frac{m}{n})$，这是因为取排序后相邻的 $b_i, b_{i+1}$，答案一定不超过 $b_{i+1} - b_i$。考虑对每个 $1 \leq i \leq n$ 枚举 $b_i + x (0 \leq x \leq r)$ 并尝试更新当前答案，而这是容易的。判断 $b_i + x$ 是否是某个 $b_j$ 的子集，考虑预处理出 $f$ 数组表示每个数分别是多少个 $b_i$ 的子集（高维前缀和即可，$\mathcal O(m\log m)$），那么只需要判断 $f_{b_i+x} - [x = b_i]$ 是否大于 $0$ 即可；判断 $b_i + x$ 是否是某个 $b_j$ 的超集，同理预处理出 $g$ 数组，只需要判断 $g_{b_i+x} - [((x+b_i)\;\&\;b_i)=b_i]$ 是否大于 $0$ 即可。

时间复杂度 $\mathcal O(n\log n + m\log m)$，跑的飞快。

---

## 作者：未来姚班zyl (赞：1)

脑电波题。只能说这场题目顺序有点难崩。

考虑怎样的 $a$ 和 $b$ 是合法的。首先全部相等肯定合法。否则，考虑最后一次操作选择的位置 $i,j$，此时**必须**满足 $b_i$ 在二进制表示下是 $b_j$ 的子集，即 $b_i|b_j=b_j$。

然后我们发现一个非常强的性质，只要存在这样的 $b_i$ 和 $b_j$，无论 $a_i$ 和 $a_j$，我们都可以通过以下方法让这两个位置让 $a_i=b_i,a_j=b_j$。

- 操作 $(i,j,x=0)$，这个效果是让 $a_i=0$，$a_j$ 不变。
- 操作 $(i,j,x=2^{30}-1)$，这个效果是让 $a_j$ 变成全 $1$，$a_i$ 不变。
- 操作 $(j,i,x=b_i)$，这个操作是把两个数都变成 $b_i$。
- 操作 $(i,j,x=b_j)$，这个操作可以让 $a_j=b_j$，$a_i$ 保持不变。

这样我们就可以有两个万能位置 $i,j$，我们可以用其中一个万能位置把其它位置修改为任意值，最终让 $a$ 和 $b$ 相等。

这样的话，初始时 $a$ 和 $b$ 就相等，或者存在 $b_i|b_j=b_j$，其实就是 $a$ 与 $b$ 合法的充要条件。

前者可以直接算，考虑如何用 $+1$ 操作使得存在 $i,j$ 使得 $b_i|b_j=b_j$。

从值域上考虑，我们连 A 类边 $x\rightarrow x+1$，边权为 $1$，这个刻画 $+1$ 操作，对于 $x$ 的子集 $y$，连 B 类边 $y\rightarrow x$，边权为 $0$，这个刻画 $b_i$ 是 $b_j$ 的子集，所以只用从 $x$ 中扣掉一个 $1$ 即可。

这就相当于两个点 $x,y$，先走 A 类边，其中一个再走一段 B 类边，走到同一个点的最小花费，由于 $x,y$ 需不同，所以我们 dp 记最小值和次小值即可。

总复杂度 $O(n+m\log m)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define mid ((l+r)>>1)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define E(x) for(auto y:p[x])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=6e6+5,M=2e5+5,inf=(1LL<<31)-1;
const ll llf=1e18;
int n,a[N],b[N],m;
struct number{
	int id,k;
}dp[N],f[N],Dp[N],F[N];
vector<int>p[N];
inline void insert(int x,number k){
	if(k.k==llf)return;
	if(k.id==dp[x].id){
		dp[x].k=min(dp[x].k,k.k);
		return;
	}
	if(k.id==f[x].id){
		if(k.k<dp[x].k){
			swap(dp[x],f[x]);
			dp[x].k=min(dp[x].k,k.k);
		}else f[x].k=min(f[x].k,k.k);
		return;
	}
	if(dp[x].k>=k.k)f[x]=dp[x],dp[x]=k;
	else if(f[x].k>k.k)f[x]=k;
}
inline void Insert(int x,number k){
	if(k.k==llf)return;
	if(k.id==Dp[x].id){
		Dp[x].k=min(Dp[x].k,k.k);
		return;
	}
	if(k.id==F[x].id){
		if(k.k<Dp[x].k)swap(Dp[x],F[x]),Dp[x].k=min(Dp[x].k,k.k);
		else F[x].k=min(F[x].k,k.k);
		return;
	}
	if(Dp[x].k>=k.k)F[x]=Dp[x],Dp[x]=k;
	else if(F[x].k>k.k)F[x]=k;
}
inline int Calc(number a,number b){
	if(a.id==b.id)return llf;
	return a.k+b.k; 
}
inline void Main(){
	n=read(),m=read();
	repn(i)a[i]=read();
	repn(i)b[i]=read();
	int ans=0,Ans=llf;
	repn(i)ans+=abs(a[i]-b[i]);
	repn(i)p[b[i]].pb(i);
	rep(i,0,m<<1)dp[i]=f[i]=Dp[i]=F[i]={0,llf};
	rep(x,0,m<<1){
		for(auto nw:p[x])insert(x,{nw,0}),Insert(x,{nw,0});
		p[x].clear();
		if(x)insert(x,{dp[x-1].id,dp[x-1].k+1}),insert(x,{f[x-1].id,f[x-1].k+1}),Insert(x,{dp[x-1].id,dp[x-1].k+1}),Insert(x,{f[x-1].id,f[x-1].k+1});
		rep(i,0,22)if((x>>i)&1)Insert(x,Dp[x^(1<<i)]),Insert(x,F[x^(1<<i)]);
		Ans=min({Ans,Calc(dp[x],Dp[x]),Calc(dp[x],F[x]),Calc(f[x],Dp[x]),Calc(f[x],F[x])});
	}
	cout <<min(ans,Ans)<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}


```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题意

我们称一个 $(c,d)$ 是好的当且仅当可以通过若干次如下操作使得 $\forall i,c_i=d_i$：一次操作选择三个数 $(i,j,x)$，$c_i\gets c_i\operatorname{and} x$，$c_j\gets c_j\operatorname{or} x$。

给定 $a,b$，每次可以选择一个 $i$ 操作 $a_i\gets a_i+1$ **或** $b_i\gets b_i+1$。问至少几次操作能使得 $(a,b)$ 是好的。

多测，$1\leq t\leq 10^4$，$1\leq n,m,\sum n,\sum m\leq 2\times 10^6$，$0\leq a_i\leq m$，$0\leq b_i\leq m$。

# 做法

我们称数 $x\subseteq y$ 当且仅当 $x\operatorname{and} y = x$。即 $x$ 的二进制表示被 $y$ 包含。

如果原本就存在 $a=b$ 那么 $(a,b)$ 就是好的。

否则至少需要一次操作。只要进行了一次操作，必然会有两个数 $i,j(i\neq j)$，满足 $b_i\subseteq b_j$。而且只要有 $b_i\subseteq b_j$ 则 $(a,b)$ 一定是好的。充分性可以构造证明。

令 $k\neq i$ 且 $k\neq j$。

1. 选择 $(k,i,0)$ 清空 $n-2$ 个 $a_k$。
1. 选择 $(i,k,b_k)$ 还原 $n-2$ 个 $a_k\gets b_k$。
1. 选择 $(i,j,0)$ 清空 $a_i$。
1. 选择 $(j,i,0)$ 清空 $a_j$。
1. 选择 $(j,i,b_i)$ 重设 $b_i$。
1. 选择 $(i,j,b_j)$ 重设 $b_j$。

由于 $b_i$ 是 $b_j$ 的子集，所以这样子一定对。

那么就是要求做至少几次操作能在 $b$ 中出现 $b_i\subseteq b_j$。

这个可以高维前缀 $\min$ 优化 DP 做。

但是我在 CF 评论区看到了一个也很牛的东西。<https://codeforces.com/blog/entry/140505?#comment-1255067>。

意思就是你暴力做，先从大到小枚举，把每个数的子集标记一下。如果目前这个数已经被标记那么答案就是 $0$。否则重复这个过程。做完之后再看一下 $b_i$ 最近的一个子集是谁，二者的差对答案 checkmin。

超集同理，从小到大排序。但是在标记超集之前先找一下最近的一个超集是谁。否则的话会导致出现一个数和自己的超集匹配了，但这是不合法的。

复杂度看起来是 $\mathcal O(3^{\log m})$ 的。但是这个『被标记那么答案就是 $0$』的剪枝不是很好算。你尝试卡一下能不能卡到 $\mathcal O(3^{\log m})$，发现要卡必须要是这些数互不为对方的子集。

> @[irris](https://www.luogu.com.cn/user/419487)：看起来可以构造到 $\mathcal O(2.828^{\log m})$。把 $[0, 2^{20})$ 里所有 $\operatorname{popcount} = 10$ 的数拿出来。渐进意义一下就是这个复杂度。

这个算一下是 $10^9$ 量级的。时限 5 秒随便跑。

但是事实上我用 C++ 写了一发（原作者写的 Go 跑得慢可能只是因为语言问题）直接没卡常最优解了。。。

# 代码

<https://codeforces.com/contest/2077/submission/311013601>

```cpp
#include <bits/stdc++.h>
using namespace std;
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
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
typedef long long ll;
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
void solve()
{
    int n, m;
    read(n, m);
    int a[n + 1];
    int b[n + 1];
    const int V = (m << 1) + 20;
    for (int i = 1; i <= n; i++)
        read(a[i]);
    for (int i = 1; i <= n; i++)
        read(b[i]);
    ll s = 0;
    for (int i = 1; i <= n; i++)
        s += abs(a[i] - b[i]);
    if (!s)
        return cout << s << '\n', void();
    sort(b + 1, b + n + 1);
    bool f[V] = {};
    for (int i = n; i >= 1; i--)
    {
        if (f[b[i]])
            return cout << 0 << '\n', void();
        for (int S = b[i]; S > 0; S = (S - 1) & b[i])
            f[S] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = b[i] + 1; j <= min((ll)V, b[i] + s); j++)
        {
            if (f[j])
            {
                chkmn(s, (ll)j - b[i]);
                break;
            }
        }
    }
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        if (f[b[i]])
            return cout << 0 << '\n', void();
        for (int j = b[i] + 1; j <= min((ll)V, b[i] + s); j++)
        {
            if (f[j])
            {
                chkmn(s, (ll)j - b[i]);
                break;
            }
        }
        for (int S = b[i]; S < V; S = (S + 1) | b[i])
            f[S] = 1;
    }
    cout << s << '\n';
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

## 作者：ForgotMe (赞：0)

无语了，我只能说这题比 E 还简单，不知道为啥放在 F。

首先其实很容易看出序列对 $(a,b)$ good 的充要条件：

满足以下两者其一即可

- $\forall 1\le i\le n,a_i=b_i$。

- $\exist 1\le i,j\le n,i\ne j,b_j|b_i=b_i$，即在二进制下存在包含关系。

证明其实是容易的：

- 先证明充分性：如果满足第一个条件，显然 good。如果满足第二个条件，注意到容易将一个数变成 $0$ 且不影响其他数，考虑先把一个数变成 $0$，然后通过或操作变成目标值，但是做或操作时同时要选择一个数做与操作，这会导致在变最后一个数时出现问题。假设在二进制下存在包含关系的对为 $(x,y)$，那么考虑将 $a_y$ 最后一个变成 $b_y$，且在做或操作时选择 $a_x$ 做与操作，因为 $b_x|b_y=b_y$，那么这不会使已经变好了的 $a_x$ 发生改变。

- 再证明必要性：在最后一步操作 $(i,j)$ 时，必定有 $a_i|x=b_i$，$a_j \operatorname{and} x=b_j$，显然 $b_i,b_j$ 形成了二进制上的包含关系。

接下来考虑计算答案，第一个条件的答案容易计算，就是 $\sum_{i=1}^n |a_i-b_i|$，第二个条件的答案就和 $a$ 无关了，只考虑 $b$。

容易想到枚举最后具有包含关系的两个值 $X,Y(X|Y=Y)$，显然 $X,Y$ 最后一定是 $\mathcal{O}(m)$ 级别的，那么相当于从小于等于 $X$ 的数中选一个数 $v_1$，从小于等于 $Y$ 的数中选一个数 $v_2$，最小化 $X+Y-v_1-v_2$，一个需要注意的点是 $v_1$ 的标号不能等于 $v_2$ 的标号，即不能选相同的数（为啥这里说标号呢，因为输入里 $b$ 中可能就有相同值的数，这时候靠标号区分）。如果没有这个标号不同的限制，显然让 $v_1,v_2$ 选可选的数中最大的，然后做一个类似于子集最值的东西就做完了。但是如果有标号不同的限制，可选的数中需要考虑最大/次大（钦定最大与次大的标号不同）。这时候将答案分为三部分：

- $X$ 选最大 + $Y$ 选最大，且两者最大的标号不能一样。
- $X$ 选次大 + $Y$ 选最大。
- $X$ 选最大 + $Y$ 选次大。

注意后两种不需要保证其选的两个数标号不同，因为一旦相同，两者都选最大一定合法且答案更小。

后两种情况容易统计，就按照没有限制时做就行。

考虑第一种情况如何统计，由于每个状态选的数固定，即一定都是最大的。考虑对于每个状态 $Y$，维护出其所有真子集 $X$ 中 $X-v$（$v$ 是 $X$ 能选的最大值）的最小值/次小值（要求最小值中选的 $v$ 的标号与次小值中选的 $v$ 的标号不同），这个显然是可以维护的，跑一个类似于子集最值的东西即可。最后枚举状态 $Y$，先看最小值合不合法，不合法就选次小值，否则选最小值，统计答案即可。

时间复杂度 $\mathcal{O}(n+m\log m)$。

参考代码：https://www.luogu.com.cn/paste/88ytqjzl

代码中维护最小值/次小值的部分为了与前者保持一致，对其做了取负处理从而维护最大值/次大值。

---

