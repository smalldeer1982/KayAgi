# [AGC033E] Go around a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_e

円周が $ N $ 個の点によって $ N $ 等分され、それぞれが赤か青のいずれかで塗られているような円が、 `R` と `B` からなる長さ $ M $ の文字列 $ S $ をすべての点から生成するとは、以下の条件を満たすことを指します。

- 円周上の $ N $ 個の点のうち $ 1 $ つを任意に選び、その点上に駒を置く。
- 駒を時計回り、または反時計回りに隣合う点まで動かすことを $ M $ 回繰り返す。
- このとき最初にどの点を選んだとしても、うまく動かす向きを定めることで、$ i $ 回目に駒が通る円弧の色が $ S_i $ であるようにできる。

ただし、$ S_i $ は `R` のとき赤を、`B` のとき青を指すものとします。 また駒を動かす向きは、最初に選ぶ点ごとに変えられることに注意してください。

実際に `R` と `B` からなる長さ $ M $ の文字列 $ S $ が与えられます。 円周が $ N $ 等分されている円の各円弧を赤または青のいずれかで塗る $ 2^N $ 通りの方法のうち、 $ S $ をすべての点から生成するような塗り方の個数を $ 10^9+7 $ で割ったあまりを求めてください。

ただし、回転して一致するような塗り方も区別して数えます。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 2\ \times\ 10^5 $
- $ 1\ ≦\ M\ ≦\ 2\ \times\ 10^5 $
- $ |S|=M $
- $ S_i $ は `R` または `B`

### Sample Explanation 1

赤と青が交互に塗られているときのみ条件を満たします。 なので、このケースの答えは $ 2 $ となります。

## 样例 #1

### 输入

```
4 7
RBRRBRR```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
BBB```

### 输出

```
4```

## 样例 #3

### 输入

```
12 10
RRRRBRRRRB```

### 输出

```
78```

# 题解

## 作者：qwaszx (赞：10)

首先显然 RB 互换答案不变，所以只考虑 $S_1=R$ 的情况. 

如果 $S$ 全都是 $R$，那么这个时候的限制就是不存在相邻的 $B$. 设 $f_i$ 表示长度为 $i$ 的序列（注意不是环）的方案数，那么转移就枚举第 $i$ 个位置选什么，如果选了 $R$ 方案数是 $f_{i-1}$，否则相当于强制第 $i-1$ 位选 $R$，那么方案数是 $f_{i-2}$. 由于我们要求的是环，所以还要求首尾不同时是 $B$. 如果末尾是 $R$ 那么方案数是 $f_{n-1}$，否则相当于强制第 $n-1$ 和第 $1$ 个位置选 $R$，方案数是 $f_{n-3}$. 特判 $n<3$ 的情况.

否则，如果 $S$ 中存在 $B$，那么我们首先还是有不存在相邻的 $B$ 这一限制，并且至少有一个 $B$. 设 $S$ 的第一个 $B$ 之前有 $L$ 个 $R$. 用 $B$ 把环分成若干个极长的 $R$ 连续段，那么首先每个连续段长度必须是奇数，否则一段上的某个点到两端的距离同为奇数或同为偶数并且这两种情况一定都会出现，所以一定存在某个点不能走恰好 $L$ 步到端点. 然后另一个限制是长度不能超过 $L+1$，这个也比较显然，奇偶分类讨论即可. 对于 $S$ 中的其他 $R$ 极长连续段也有类似的限制，即如果某个连续段后面还有 $B$ 并且长度为奇数那么环中的极长 $R$ 连续段长度不能超过它. 有了这些限制之后可以直接 dp，把一个 $B$ 和后面跟着的极长 $R$ 连续段放在一起，那么每一段长度都是偶数，并且长度有上界，转移可以前缀和优化. 注意可以旋转，所以方案数还要乘上第一段的长度，这可以在 dp 初值中体现.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1000000007,N=5e5;
int f[N],p[N],nxt[N],n,m;
char st[N];
int qmod1(int x){return x>=mod?x-mod:x;}
int qmod2(int x){return x+(x>>31&mod);}
void solve1()
{
    f[0]=1,f[1]=2;
    if(n==1){cout<<1<<endl;return;}
    if(n==2){cout<<3<<endl;return;}
    for(int i=2;i<=n;i++)f[i]=qmod1(f[i-1]+f[i-2]);
    cout<<qmod1(f[n-1]+f[n-3])<<endl;
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",st+1);
    for(int i=1;i<=m;i++)p[i]=st[i]=='R';
    if(!p[1])for(int i=1;i<=m;i++)p[i]^=1;
    nxt[m+1]=m+1;for(int i=m;i>=1;i--)if(!p[i])nxt[i]=i;else nxt[i]=nxt[i+1];
    if(nxt[1]==m+1){solve1();return 0;}
    if(n&1){puts("0");return 0;}
    int mi=n;
    for(int i=1;i<=m;i++)
        if(nxt[i]!=m+1&&!p[i-1])
        {
            int len=nxt[i]-i;
            if(len&1)mi=min(mi,len);
        }
    mi=min(mi,nxt[1]);
    if(~mi&1)--mi;
    n>>=1;mi=(mi+1)>>1;
    int s=0;
    for(int i=1;i<=n;i++)
    {
        if(i>mi)s=qmod2(s-f[i-mi-1]);
        f[i]=s;if(i<=mi)f[i]=qmod1(f[i]+i*2);
        s=qmod1(s+f[i]);
    }
    cout<<f[n]<<endl;
}
```

---

## 作者：zhylj (赞：5)

不妨令 $S_1=\mathtt R$，然后相应地改变其它 $S_i$。若所有 $S_i$ 都为 $\mathtt R$，则不能存在连续的两个 $\mathtt B$，不难用一个简单的 DP 求出。否则必须存在至少一个 $\mathtt B$，但每个 $\mathtt B$ 段也不能连续超过 $2$ 个。考虑 $S$ 中遇到的第一个 $\mathtt B$，假如存在一个长度 $\ge 2$ 的偶数 $\mathtt R$ 段，那其中必然同时存在到边界均为奇数或均为偶数的棋子的起始点，故在某一步时要么奇数没法到达，要么偶数的没法到达。所以环上不可能出现长度 $\ge 2$ 的为偶数的段。然后考虑这些奇数段的长度都要多长，注意到以后如果 $S$ 有个极长奇数 $\mathtt R$ 段，在经过这个 $\mathtt R$ 后，某个位于一端的棋子必须移动到当前所处环上奇数段的另一端，否则必须回到原点，于是记 $L$ 为开头的 $\mathtt R$ 段和所有奇数 $\mathtt R$ 段的最小值，则所有环上的 $\mathtt R$ 段的长度必须 $\ge L$。

不妨视 $\mathtt {BRRR\cdots R}$ 为一整段，那么每一段必然长度为偶数，记为 $2l$，所以若 $2\nmid N$ 则答案等于 $0$，则我们要将 $n=N/2$ 个有标号元素划分为若干个段，使得每段长度 $l\le L'=\lfloor L/2\rfloor + 1$，我们将首个位置钦定为 $\mathtt B$，然后最后给答案乘上第一段的长度即为所求，记 $f_i$ 表示前 $i$ 个位置划分成若干完整的段的方案数，枚举最后一段的长度即可转移，不难用前缀和优化，时间复杂度 $\mathcal O(N)$。

```cpp
const int N = 2e5 + 5, MOD = 1e9 + 7;

int n, _m, m, L, pre[N], f[N], d[N];
char _s[N], s[N];

int main() {
	rd(n, _m); L = n;
	scanf("%s", _s + 1);
	bool flag = true;
	for(int i = 1; i <= _m; ++i) {
		if(_s[i] == _s[1]) s[++m] = 'R';
		else {
			if(!m || s[m] != 'B') s[++m] = 'B';
			flag = false;
		}
		if(m) pre[m] = s[m - 1] == s[m] ? pre[m - 1] : m;
		else pre[m] = 1;
		if(m > 1 && s[m] == 'B' && s[m - 1] == 'R' && (m - pre[m - 1]) % 2)
			L = std::min(L, m - pre[m - 1]);
	}
	for(int i = 1; i <= m; ++i)
		if(s[i] == 'B') {
			L = std::min(L, i - 1 + (i % 2 == 1));
			break;
		}
	if(flag) {
		f[0] = 1; f[1] = 1;
		for(int i = 2; i <= n; ++i)
			f[i] = (f[i - 1] + f[i - 2]) % MOD;
		int ans = (f[n] + f[n - 1] - (n >= 3 ? f[n - 3] : 0) + MOD) % MOD;
		printf("%d\n", ans);
		continue;
	}
	if(n % 2 != 0) {
		printf("0\n");
		return 0;
	}
	n /= 2;
	L = (L + 1) / 2;
	for(int i = 1; i <= L; ++i) f[i] = 2 * i;
	for(int i = 1; i <= n; ++i) {
		d[i] = (d[i] + d[i - 1]) % MOD;
		f[i] = (f[i] + d[i]) % MOD;
		d[i + 1] = (d[i + 1] + f[i]) % MOD;
		d[i + L + 1] = (d[i + L + 1] - f[i] + MOD) % MOD;
	}
	printf("%d\n", f[n]);
	return 0;
}
```

---

## 作者：myee (赞：4)

### 前言

怎么题解里全是 dp。

这里有一个比较套路的 GF 做法。

### 思路

不妨总是令第一项为 $\tt R$。则，说明弧上不存在相邻的 $\tt B$。

如果串 $S$ 仅由 $\tt R$ 构成，则方案数即为不存在相邻 $\tt B$ 的方案数。这个答案显然就是 $\sum_k\binom{n-k}{k}+\sum_k\binom{n-k-2}{k}$。

否则，环上既有 $\tt B$ 又有 $\tt R$，不妨假设有 $k$ 个 $\tt B$，而 $\tt R$ 构成的联通块大小依次为 $a_1,a_2,\dots,a_k$，使得 $a_i\ge1\land\sum a=n-k$，且该序列若合法，则对答案的贡献为恰 $\frac{n}{k}$ 份。

考虑怎样的序列是合法的。

假设 $S$ 串中有 $t$ 个 $\tt B$，其把 $\tt R$ 序列分成了 $c_0\sim c_t$ 各段，其中 $c\ge0$。

首先，显然有 $a\le c_0+1\land2\nmid a$，而 $c_t$ 对答案没有影响。

然后，如果有 $2\nmid c_j(1\le j\le t-1)$，则说明该步必然走到了下一个（相对于上一个）$\tt R$ 联通块，且当前 $a\le c$；如果 $2|c_j(1\le j\le t-1)$，则该步必然是往回折返的，而没有其余限制。

由于对于每个节点 $a$，第一步向左 / 向右走都是要做到可行的，所以每种路线带来的限制都是要被计入的；且容易发现没有多余的限制。

所以其实总的限制就是

$$2\nmid a$$

$$1\le a\le\min\{c_0+[2|c_0],\min_{0<j<t,2\nmid c_j}c_j\}$$

$$\sum a=n-k$$

这样的方案有几种呢？设

$$a=1+2b$$

则

$$0\le b\le\frac{\min\{c_0+[2|c_0],\min_{0<j<t,2\nmid c_j}c_j\}-1}{2}$$

$$\sum b=\frac{n}{2}-k$$

设 $d=\frac{\min\{c_0+[2|c_0],\min_{0<j<t,2\nmid c_j}c_j\}-1}{2}$，则方案数即

$$[z^{n/2-k}] (\frac{1-z^{d+1}}{1-z})^k$$

从而答案即为

$$
n[z^{n/2}]\sum_k\frac{(z\frac{1-z^{d+1}}{1-z})^k}{k}
\\=n[z^{n/2}]\ln\frac{1}{1-z\frac{1-z^{d+1}}{1-z}}
$$

~~使用 MTT 即可做到 $O(n\log n)$。~~

MTT 太混乱邪恶了，考虑阳间一点的推导。

$$
n[z^{n/2}]\ln\frac{1}{1-z\frac{1-z^{d+1}}{1-z}}
\\=2[z^{n/2-1}] (\ln\frac{1}{1-z\frac{1-z^{d+1}}{1-z}})'
\\=2[z^{n/2-1}]\frac{1-(d+2)z^{d+1}+(d+1)z^{d+2}}{1-3z+2z^2+z^{d+2}-z^{d+3}}
$$

由于分母的非 $0$ 项很少，直接递推即可。

总复杂度 $O(n+m)$。

### Code

代码很好写。

```cpp
const ullt Mod=1e9+7;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    std::vector<uint>V{0};
    uint n;scanf("%u",&n);
    {
        chr c;
        do c=getchar();while(c!='R'&&c!='B');
        chr o=c;
        do
        {
            if(o==c)V.back()++;else V.push_back(0);
            c=getchar();
        }
        while(c=='R'||c=='B');
        V.pop_back();
    }
    if(V.empty())
    {
        modint a(2),b(1);
        while(n--)std::swap(a+=b,b);
        a.println();return 0;
    }
    if(n&1)return puts("0"),0;
    uint d=V[0]/2;for(auto s:V)if(s&1)_min(d,s/2);
    static modint P[100005];
    P[0]=1,P[d+1]=-modint(d+2),P[d+2]=d+1;
    for(uint i=1;i<n/2;i++)
    {
        P[i]+=3*P[i-1];
        if(i>=2)P[i]-=2*P[i-2];
        if(i>=d+2)P[i]-=P[i-d-2];
        if(i>=d+3)P[i]+=P[i-d-3];
    }
    (P[n/2-1]*2).println();
    return 0;
}
```


---

## 作者：翼德天尊 (赞：4)

设给定字符串为 $S$，构造串为 $T$。

不妨设 $S_1=R$，若为 $B$，则取反整个 $S$，两串等价。

此时 $T$ 中显然不能存在相邻的 $B$，否则只需要在开始时将棋子放在 $B$ 之间即可使得 $S_1$ 无法取得。由此可知 $T$ 一定是由若干个「连续 $R$ 加单独 $B$」 组成的。

考虑策略会是怎样的，设初始放棋子的位置左侧有 $x$ 个 $R$，右侧有 $y$ 个 $R$，则如果当前 $S$ 开头一段 $R$ 长度为奇数 $k$，我们会挑 $x,y$ 中为奇数且不大于 $k$ 的一个作为方向前进，因为我们需要保证在走完这段 $S$ 中的 $R$ 之前走到棋子所在 $R$ 段的边界，且在走完时刚好在边界，这意味着我们要做出两个限制：

- $T$ 中每一段 $R$ 的长度必须为奇数，否则无法保证 $x,y$ 奇偶性不同，导致有部分初始位置无法选择奇偶性正确的方向。
- $T$ 中每一段 $R$ 的长度必须不大于 $k$（具体来说，当 $k$ 为奇数时，不大于 $k$，当 $k$ 为偶数时，不大于 $k+1$），否则无法走到边界。

除此之外，发现我们每次走完 $S$ 中的一段 $B$ 后走到一段新的 $R$ 时，若该 $R$ 段为偶数，则显然棋子可以左右横跳，对其没有任何限制；若为奇数 $k$，则还需满足 $T$ 中所有 $R$ 段长度都不大于 $k$。

注意此时我们有一点需要特殊判断，即当 $S$ 中全为 $R$ 时，由于无需走到 $R$ 段边界，故没有任何限制，单独做 dp 计数有多少环由若干无限制 $R$ 段和单独 $B$ 组成即可。

而对于非全 $R$ 的情况，我们先综上所述找到 $R$ 段长度的上界，然后设 $dp_i$ 表示状态，枚举最后一段段长转移即可，注意由于两种方案旋转后相同不算一种方案，所以我们还需要将每一种方案乘上开头段的长度。

**本题再次启发我们在无从下手时，要仔细分析题目性质，通过增加限制减少决策的方式，解决转化后的问题。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int mod=1e9+7;
int n,m;
char s[N];
ll dp[N],sum[N],f[N][2];
bool flag1,flag2;
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	n=read(),m=read();
    scanf("%s",s+1);
    if (s[1]=='B'){
        for (int i=1;i<=m;i++)
            s[i]=(s[i]=='B')?'R':'B';
    }
    int minn=1e9;
    for (int i=1,len=0,hav=1;i<=m;i++){
        if (s[i]=='B'){
            if (len&1||hav) minn=min(minn,len);
            len=0,hav=0;
        }else ++len;
        if (s[i]=='B') flag1=1;
        else if (s[i]=='R') flag2=1;
    }
    if (!flag1||!flag2){
        ll ans=0;
        f[1][0]=1;
        for (int i=2;i<=n;i++)
            f[i][0]=(f[i-1][0]+f[i-1][1])%mod,f[i][1]=f[i-1][0];
        ans=(f[n][0]+f[n][1])%mod;
        f[1][0]=0,f[1][1]=1;
        for (int i=2;i<=n;i++)
            f[i][0]=(f[i-1][0]+f[i-1][1])%mod,f[i][1]=f[i-1][0];
        ans=(ans+f[n][0])%mod;
        cout<<ans<<"\n";
        return 0;
    }
    if (n&1){
        puts("0");
        return 0;
    }
    n/=2,minn=minn/2+1;
    for (int i=1;i<=minn;i++) dp[i]=2*i;
    for (int i=1;i<=n;i++){
        dp[i]=(dp[i]+sum[i-1])%mod;
        if (i-minn-1>=0) dp[i]=(dp[i]-sum[i-minn-1]+mod)%mod;
        sum[i]=(sum[i-1]+dp[i])%mod;
        // cout<<dp[i]<<"\n";
    }
    cout<<dp[n]<<"\n";
	return 0;
}
```

---

## 作者：xht (赞：2)

## [Go around a Circle](https://atcoder.jp/contests/agc033/tasks/agc033_e)

### 题意

- 有一个圆被 $n$ 个点分成了等长的 $n$ 段，每段的颜色为 `R` 或者 `B`。注意，染色方案旋转不同构。
- 给定一个长度为 $m$ 的只包含 `R` 和 `B` 的字符串 $s$，求出有多少种染色方案，满足将棋子放在任意一个点上，都存在一种进行 $m$ 次操作的方案，每次操作选择将棋子顺时针或逆时针移动一段，使得经过的第 $i$ 段为 $s_i$。
- $n,m \le 2 \times 10^5$，答案对 $10^9+7$ 取模。

### 题解

不妨设 $s_1$ 为 `R`，若不是则交换 `R` 和 `B`，那么圆上显然不存在连续两段为 `B`。

若 $s$ 中没有 `B`，则问题等价于圆上不存在两个连续的 `B` 的方案数，直接 DP 即可，接下来不考虑这种情况。

由于不存在连续两段为 `B`，因此我们可以当作圆上若干个非空 `R` 段被 `B` 隔开。

记 $s$ 中每一个极大的相同字符段长度为 $c_{1\dots k}$，我们容易得到若干条件：

1. 圆上每一个 `R` 段的长度都为奇数。
2. 圆上每一个 `R` 段的长度都不超过 $c_1 + 1$。
3. 若 $k$ 为奇数，即 $s$ 中最后一段为 `R`，则可以将 $s$ 中的这一段直接去掉，也就是直接将 $k$ 减 $1$。
4. 对于 $i \in [2,k]$ 且 $i$ 为奇数，若 $c_i$ 为奇数，则圆上每一个 `R` 段的长度都不超过 $c_i$。

可以证明这些条件为充要条件。

于是问题变成每一段的长度为奇数且不超过一个定值，可以使用前缀和优化 DP 解决，时间复杂度 $\mathcal O(n)$。

### 代码

```cpp
const int N = 2e5 + 7;
int n, m, c[N], k, w;
char s[N];

namespace k1 {
	modint f[N][2][2];
	inline void main() {
		f[1][0][0] = f[1][1][1] = 1;
		for (int i = 1; i < n; i++)
			f[i+1][0][0] = f[i][0][0] + f[i][0][1],
			f[i+1][0][1] = f[i][0][0],
			f[i+1][1][0] = f[i][1][0] + f[i][1][1],
			f[i+1][1][1] = f[i][1][0];
		print(f[n][0][0] + f[n][0][1] + f[n][1][0]);
	}
}

modint f[N], g[N], ans;

int main() {
	rd(n, m), rds(s, m);
	for (int l = 1, r = 1; l <= m; l = ++r) {
		while (r < m && s[r+1] == s[l]) ++r;
		c[++k] = r - l + 1;
	}
	if (k == 1) return k1::main(), 0;
	if (n & 1) return print(0), 0;
	w = c[1] + !(c[1] & 1), k -= k & 1;
	for (int i = 3; i <= k; i += 2)
		if (c[i] & 1) w = min(w, c[i]);
	n >>= 1, w >>= 1;
	f[1] = g[1] = 1;
	for (int i = 2; i <= n; i++)
		g[i] = g[i-1] + (f[i] = g[i-1] - (i - w - 2 >= 0 ? g[i-w-2] : 0));
	for (int i = 0; i <= min(n, w); i++) ans += f[n-i] * (i + 1);
	print(ans + ans);
	return 0;
}
```

---

## 作者：bamboo12345 (赞：0)

不是很困难的观察题。

题意：很简单了，不再赘述。

做法：

首先先直接钦定遍历序列第一个为 $R$，如果不是就把这个环反色即可，假设我们遍历序列分成了 $m$ 个连续段，分别为 $c_1,c_2,\cdots ,c_m$。

如果一个串全都是 $R$，那么只要环上没有相邻的 $B$ 即可，随便 dp 就可以做。

那么我们开始手玩找性质，注意是对于任意的位置都要满足遍历序列而不是存在，我看错题想了半天。

首先我们发现，我们肯定不能有连续的 $B$，要不然我们从 $B$ 中间开始直接爆炸了。

其次我们考虑每一个 $R$ 段，我们可以先把 $n=3,4$ 的情况画下来，$n$ 是开头这个段的长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/tgyerfea.png)

我们考虑 $n=4$，发现一个很严重的问题，当我们从任意一个点开始的时候，如果我们下面有一个 $B$，我们想出这个连续段的时候，往左往右需要步数的奇偶性是一样的，这样无论你遍历序列开头的连续 $R$ 段是偶数长还是奇数长，我都能找到一个位置让你直接爆掉，所以每一个 $R$ 段都得是奇数。

然后从奇偶性上就没什么好分析的了，我们考虑长度限制，我们记 $R$ 连续段长度为 $len$。

首先对于开始段，当 $c_1$ 为奇数的时候，我要求从第一个点往右走一定要能走出去，从左边是出不去的，所以要求 $len\le c_1$；对于 $c_1$ 为偶数的时候，要求从第二个点往右走一定要能走出去，所以要求 $len\le c_1+1$。

对于 $B$ 连续段，我们直接左右横跳就可以了。

然后考虑后面的 $R$ 连续段 $c_x$ 有什么要求，如果是偶数长我们直接反复横跳就行了，因为我们刚从一个 $B$ 过来。如果是奇数长度，你可以先反复横跳再往前冲过去，但是再怎么样必须要 $len\le c_x$，要不然冲不过去了。

所以总的限制只有两个，就是要求 $len\le \min(c_1+c_1\bmod 2,\min\limits_{i=2,2\mid c_i}^m c_i)$，且 $len$ 为奇数。

那么这个东西一看就很 poly，我们令 $t$ 为后面一长坨的那个限制，考虑我们现在有 $k$ 个段，那么我们的贡献就还会乘上一个 $\frac{n}k$，因为你考虑一种方式他旋转后会有 $n$ 种，但是你有 $k$ 种环长划分方式可以分出来，所以是 $\frac n k$，可以手玩一下感受一下。

那么总的柿子就是 $(x\sum\limits_{i=1,2\nmid i}^t x^i)^k[x^n]$。

解释一下，里面的和式是 $R$ 连续段的方案，而外面的 $x$ 是我们直接每个连续段带一个 $B$ 这么考虑。

我们考虑令 $d=\frac{t-1}{2}$，那么柿子就可以化为 $(x\frac{1-x^{d+1}}{1-x})^k[x^{\frac{n}{2}}]$，最后乘上我们的贡献得到总和为；

$$n[x^{\frac n 2}]\sum_{k=1}\frac{(x\frac{1-x^{d+1}}{1-x})^k}{k}$$

后面那个东西是 $\ln(1-x)$ 的泰勒展开，我们还原回去：

$$n[x^{\frac n 2}]\ln(\frac{1}{1 - x\frac{1-x^{d+1}}{1-x} })$$

然后我们考虑对后面这个柿子求导，原式就等于下面这个式子：

$$2[x^{\frac n 2-1}](\ln(\frac{1}{1 - x\frac{1-x^{d+1}}{1-x} }))^{'}$$

$$2[x^{n/2-1}](\frac{1-(d+2)x^{d+1}+(d+1)x^{d+2}}{1-3x+2x^2+x^{d+2}-x^{d+3}})$$

直接对着这个式子求就可以了。

---

