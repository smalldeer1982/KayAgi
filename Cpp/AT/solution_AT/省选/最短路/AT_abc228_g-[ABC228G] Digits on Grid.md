# [ABC228G] Digits on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc228/tasks/abc228_g

縦 $ H $ 行、横 $ W $ 列のマス目があり、それぞれのマスには $ 1 $ から $ 9 $ のいずれかの数字が書かれています。 $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす整数の組 $ (i,\ j) $ それぞれについて、上から $ i $ 行目、 左から $ j $ 列目のマスに書かれた数字は $ c_{i,\ j} $ です。

高橋君と青木君はこのマス目を使って $ 2 $ 人で遊びます。 まず、高橋君がいずれか $ 1 $ つのマスを選び、そのマスにコマを置きます。その後、$ 2 $ 人は下記の手順 1. から 4. を $ N $ 回繰り返します。

1. 高橋君が次の $ 2 $ つのうちどちらか一方を行う。
  - 現在コマが置かれているマスと**同じ行**にある別のマスに、コマを移動する。
  - 何もしない。
2. 高橋君が、現在コマが置かれているマスに書かれた数字を黒板に書く。
3. 青木君が次の $ 2 $ つのうちどちらか一方を行う。
  - 現在コマが置かれているマスと**同じ列**にある別のマスに、コマを移動する。
  - 何もしない。
4. 青木君が、現在コマが置かれているマスに書かれた数字を黒板に書く。

その後、黒板には $ 2N $ 個の数字が書かれています。それらの数字を黒板に書かれたのが早い順番に並べたものを $ d_1,\ d_2,\ \ldots,\ d_{2N} $ とします。 $ 2 $ 人は $ 2N $ 個の数字をこの順番で繋げて $ 2N $ 桁の整数 $ X\ :=\ d_1d_2\ldots\ d_{2N} $ を作ります。

整数 $ X $ としてあり得るものが何通りあるかを、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 10 $
- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ c_{i,\ j}\ \leq\ 9 $
- 入力はすべて整数

### Sample Explanation 1

例えば、以下の進行が考えられます。 - まず高橋君がマス $ (1,\ 2) $ にコマを置く。 - 高橋君がコマをマス $ (1,\ 2) $ からマス $ (1,\ 1) $ に動かす。その後、マス $ (1,\ 1) $ に書かれた数字 $ 3 $ を黒板に書く。 - 青木君がコマをマス $ (1,\ 1) $ からマス $ (2,\ 1) $ に動かす。その後、マス $ (2,\ 1) $ に書かれた数字 $ 4 $ を黒板に書く。 この場合、$ X\ =\ 34 $ となります。 他の例として、以下の進行も考えられます。 - まず高橋君がマス $ (2,\ 2) $ にコマを置く。 - 高橋君がコマをマス $ (2,\ 2) $ から動かさず、マス $ (2,\ 2) $ に書かれた数字 $ 1 $ を黒板に書く。 - 青木君がコマをマス $ (2,\ 2) $ からマス $ (1,\ 2) $ に動かす。その後、マス $ (1,\ 2) $ に書かれた数字 $ 1 $ を黒板に書く。 この場合、$ X\ =\ 11 $ となります。 $ X $ としてあり得る整数は、上記の例で示した $ 34,\ 11 $ の他にも $ 33,\ 44,\ 43 $ があります。また、それら以外の整数が $ X $ となることはありえません。 $ X $ としてあり得る整数の個数は $ 5 $ 個であるので $ 5 $ を出力します。

### Sample Explanation 2

整数 $ X $ としてあり得るのは、$ 77777777 $ のみです。

### Sample Explanation 3

$ 998244353 $ で割った余りを出力することに注意して下さい。

## 样例 #1

### 输入

```
2 2 1
31
41```

### 输出

```
5```

## 样例 #2

### 输入

```
2 3 4
777
777```

### 输出

```
1```

## 样例 #3

### 输入

```
10 10 300
3181534389
4347471911
4997373645
5984584273
1917179465
3644463294
1234548423
6826453721
5892467783
1211598363```

### 输出

```
685516949```

# 题解

## 作者：vegetable_king (赞：5)

另外一种理解方式。

分别记原题中的 $H, W, N$ 为 $n, m, k$。

先考虑判定：给你一个长为 $2k$ 的串，判断是否能走出这个串。

考虑 DP：$g_{p, i, j}$ 表示匹配了前 $p$ 个位置，是否能到达 $(i, j)$，状态数为 $O(knm)$，可以滚动数组变为 $O(nm)$。

考虑优化，因为每次可以在一行 / 一列内任意走动，所以只需要记录行 / 列。设 $g_{p, i}$ 表示匹配了前 $p$ 个位置，能否走到第 $i$ 行 / 列（$p$ 为偶数时代表行，否则代表列），状态数为 $O(k(n + m))$，可以滚动数组变为 $O(n + m)$。

回到原题，因为 $n, m$ 很小，所以可以直接将 $g$ 记入状态，做 dp 套 dp。即，设 $f_{i, s}$ 表示匹配了前 $i$ 个位置且 $g_i = s$ 的方案数。转移时枚举下一个字符是什么，并同时转移 $g$。

简单预处理即可做到 $O(bk2^{\max(n, m)})$，此处字符集大小 $b = 9$。

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[ABC228G] Digits on Grid](https://www.luogu.com.cn/problem/AT_abc228_g)
本题的难点在于很容易算重。

状压 DP。

设 $f_{i,S}$ 表示当前走了 $i$ 步，可能处于的行或列的状态为 $S$ 的方案数。

令 $g_{i,S}$ 表示可能处于行的状态为 $S$，下一步到达数字为 $i$ 的格子，可能到达的列的状态。

令 $h_{i,S}$ 表示可能处于列的状态为 $S$，下一步到达数字为 $i$ 的格子，可能到达的行的状态。

可得出转移如下：

 $$f_{i,S}\longrightarrow f_{i+1,g_{1,S}/h_{1,S}}$$ 

 $$f_{i,S}\longrightarrow f_{i+1,g_{2,S}/h_{2,S}}$$ 

 $$\cdots$$ 

 $$f_{i,S}\longrightarrow f_{i+1,g_{9,S}/h_{9,S}}$$ 

对于每一个最终状态，它都唯一对应了一种颜色序列，故可以做到不重复不遗漏地计数。

$h$ 和 $g$ 可以预处理，$f$ 可以依照上式递推，故时间复杂度为 $O\left(HW\left(2^H+2^W\right)+Pn\left(2^H+2^W\right)\right)$，其中 $P=10$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int n, m, K, ans, a[15][15], row[15][2005], column[15][2005], f[5][2005];

int main()
{
	cin >> n >> m >> K;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			char c;
			cin >> c;
			a[i][j] = c - '0';
		}
	for (int i = 0; i < (1 << n); i++)
		for (int j = 1; j <= n; j++)
			if (i & (1 << (j - 1)))
				for (int k = 1; k <= m; k++)
					row[a[j][k]][i] |= (1 << (k - 1));
	for (int i = 0; i < (1 << m); i++)
		for (int j = 1; j <= m; j++)
			if (i & (1 << (j - 1)))
				for (int k = 1; k <= n; k++)
					column[a[k][j]][i] |= (1 << (k - 1));
	f[1][(1 << n) - 1] = 1;
	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j < (1 << m); j++)
			f[0][j] = 0;
		for (int j = 1; j < (1 << n); j++)
			for (int k = 1; k <= 9; k++)
				f[0][row[k][j]] = (f[0][row[k][j]] + f[1][j]) % mod;
		for (int j = 0; j < (1 << n); j++)
			f[1][j] = 0;
		for (int j = 0; j < (1 << m); j++)
			for (int k = 1; k <= 9; k++)
				f[1][column[k][j]] = (f[1][column[k][j]] + f[0][j]) % mod;
	}
	for (int i = 1; i < (1 << n); i++)
		ans = (ans + f[1][i]) % mod;
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：Purslane (赞：1)

# Solution

你可能想设 $dp_{i,j,x}$ 表示当前在 $(i,j)$，移动了 $x$ 步的方案数，可惜会算重。

如何防止算重？注意到如果我们移动了一步后格子的种类是 $a$，那么可能有很多位置能满足。不过呢此时我们只关注**这些位置分布在哪些行**，因为下一步就可以移动到这一行的任何一列。

因此设 $dp_{S,x}$ 表示移动了 $x$ 步，当前位置可能所在行（或者列）的集合是 $S$ 的方案总数。

预处理每个集合对于每种颜色的后继即可。

复杂度 $O(k2^n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=998244353;
int n,m,k,dp[2][1025],a[15][15],row[10][1025],column[10][1025];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	ffor(i,1,n) {
		string S; cin>>S;
		ffor(j,1,m) a[i][j]=S[j-1]-'0';	
	}
	ffor(s,0,(1<<n)-1) ffor(i,1,n) if(s&(1<<i-1)) ffor(j,1,m) row[a[i][j]][s]|=(1<<j-1);
	ffor(s,0,(1<<m)-1) ffor(j,1,m) if(s&(1<<j-1)) ffor(i,1,n) column[a[i][j]][s]|=(1<<i-1);
	dp[1][(1<<n)-1]=1;
	ffor(i,1,k) {
		memset(dp[0],0,sizeof(dp[0]));
		ffor(s,1,(1<<n)-1) ffor(col,0,9) dp[0][row[col][s]]=(dp[0][row[col][s]]+dp[1][s])%MOD;
		memset(dp[1],0,sizeof(dp[1]));
		ffor(s,1,(1<<m)-1) ffor(col,0,9) dp[1][column[col][s]]=(dp[1][column[col][s]]+dp[0][s])%MOD;
	}
	int ans=0;
	ffor(s,1,(1<<n)-1) ans=(ans+dp[1][s])%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

？这啥啊，不会。

考虑行和列分别作为左部点和右部点建二分图（实际上这个建图只是辅助理解，不需要显式建图），每个左部点和每个右部点，边权为格子中的数。

容易想到一个 dp，设 $f_{i, j}$ 为走了 $i$ 步，当前在点 $j$，走过的所有边权组成的不同整数的数量。但是你会发现根本没法做，因为不同的状态有可能包含相同的整数，很尴尬。

然后就是奇妙的部分了。更改状态为 $f_{i, S}$ 表示走了 $i$ 步，不同整数的数量，使得**所有走过这些整数的路径的终点集合为 $S$ 的方案数**。注意到如果 $S$ 不同，那走过的整数一定不同。因此这个状态设计是没问题的。

转移是平凡的。枚举下一步填的位，沿着边权为它的边走，即可得知终点集合。

注意到若 $i$ 为偶数，$S$ 为左部点集子集；若 $i$ 为奇数，$S$ 为右部点集子集。所以朴素实现的时间复杂度是 $O(10N (2^H + 2^W) HW)$。显然可以预处理一些东西做到更优，但是这个复杂度足以通过了。

[code](https://atcoder.jp/contests/abc228/submissions/43005744)

---

## 作者：不知名用户 (赞：0)

题意：有一个 $n\times m$ 网格，格子上是 $0\sim9$ 的数字。走 $2k$ 步，任选起点。奇数步只能移动到同行，偶数步只能移动到同列。把每一步走到的数字写下来形成一个长度为 $2k$ 的序列，问序列有几种形态。

考虑 DP。$f_{S,k}$ 表示走了偶数步，到的行集合是 $S$（状压）。值：对于一种可能的序列 $a$，它有很多走法，记这些走法的可能终点所在行并集为 $S_a$，$f_{S,i}=\sum[S_a=S]$。考虑转移：选择下一个走到的数。记 $g_{S,i}$ 表示当前在的行集合为 $S$，在同行移动，下一个走到的数为 $i$ 时可能到达的列的集合。可以求出来对于单独一行然后转移。记 $h_{S,k}$ 表示走到的列的集合为 $S$，其余要求和 $f$ 相同。则有转移：$f_{S,k}\to h_{g_{S,*},k+1}(0\le*\le9)$。发现可以滚动数组。列的转移同理，不再赘述。复杂度 $\Theta(nm+10k2^n)$，$10$ 表示值域。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10, mod = 998244353;
char s[N][N+3];
int tr[1<<N][N], tc[1<<N][N], r[1<<N], c[1<<N];
void add(int &x, int y){x=((x+y)%mod+mod)%mod;}

int main()
{
	int n, m, k, i, j, a;
	scanf("%d%d%d", &n, &m, &k);
	for(i=0;i<n;i++) scanf("%s", s[i]);
	for(i=0;i<n;i++) for(j=0;j<m;j++) a = s[i][j] - '0', tr[1<<i][a] |= 1 << j, tc[1<<j][a] |= 1 << i;
	for(i=0;i<(1<<n);i++) for(j=0;j<N;j++)
		tr[i][j] = tr[i&-i][j] | tr[i^(i&-i)][j];
	for(i=0;i<(1<<m);i++) for(j=0;j<N;j++)
		tc[i][j] = tc[i&-i][j] | tc[i^(i&-i)][j];
	r[(1<<n)-1] = 1;
	while(k--)
	{
		memset(c,0,sizeof c);
		for(i=1;i<(1<<n);i++) for(j=0;j<N;j++) add(c[tr[i][j]],r[i]);
		memset(r,0,sizeof r);
		for(i=1;i<(1<<m);i++) for(j=0;j<N;j++) add(r[tc[i][j]],c[i]);
	}
	int ans = 0;
	for(i=1;i<(1<<n);i++) add(ans,r[i]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：To_our_starry_sea (赞：0)

### Solution
非常好的 dp 套 dp 题。

首先，我们思考怎样一个过程，可以不重不漏地描述这两个人移动棋子的过程。考虑当前当前序列的最后一个数 $a$，我们难以记录其的具体位置，却可以容易的考虑其处在哪一行（列），进而可以预处理出其下一步所在的行（列）。

具体的设 $H_{now,S}$ 表示序列最后一个数为 $now$，当前可以处在集合 $S$ 中的行时，其接下来可以处在的列。类似的我们可以给出 $L_{now,S}$ 给出关于关于列的定义。注意到，序列中数字仅与每次操作经过的行（列）有关，因此我们设 $dp_{i,0/1,S}$ 表示第 $i$ 轮可以处在集合 $S$ 中的行（列）时序列的种类。而由上文可知，$dp_{i,0,S}$ 只能向 $dp_{i,1,H_{now,S}}$ 转移，而 $dp_{i,1,S}$ 只能向 $dp_{i + 1,0,L_{now,S}}$ 转移，可以发现轮数这一维可以优化掉。

时间复杂度预处理为 $O((2^H + 2^W)HW)$，dp 过程为 $O(n|\Sigma|(2^H + 2^W))$，其中 $|\Sigma|$ 为 $9$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 998244353;
const int MAXN = 15;
const int MAXK = 305;
const int MAXM = (1 << 11) + 5;
int n, m, k, a[MAXN][MAXN], H[MAXN][MAXM], L[MAXN][MAXM];
ll dp1[MAXM], dp2[MAXM];
inline void init() {
		for (int S = 0; S <= (1 << n) - 1; S++) {
		for (int i = 1; i <= n; i++) {
			if (S & (1 << (i - 1))) {
				for (int j = 1; j <= m; j++) H[a[i][j]][S] |= (1 << (j - 1));
			}
		}
	}
	for (int S = 0; S <= (1 << m) - 1; S++) {
		for (int j = 1; j <= m; j++) {
			if (S & (1 << (j - 1))) {
				for (int i = 1; i <= n; i++) L[a[i][j]][S] |= (1 << (i - 1));
			}
		}
	}
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		for (int j = 1; j <= m; j++) a[i][j] = s[j - 1] - '0';
	}
    init();
	dp2[(1 << n) - 1] = 1;
	for (int T = 1; T <= k; T++) {
		memset(dp1, 0, sizeof(dp1));
		for (int S = 1; S <= (1 << n) - 1; S++) {
			for (int now = 1; now <= 9; now++) dp1[H[now][S]] = (dp1[H[now][S]] + dp2[S]) % MOD;
		}
		memset(dp2, 0, sizeof(dp2));
		for (int S = 1; S <= (1 << m) - 1; S++) {
			for (int now = 1; now <= 9; now++) dp2[L[now][S]] = (dp2[L[now][S]] + dp1[S]) % MOD;
		}
	}
	ll ans = 0;
	for (int S = 1; S <= (1 << n) - 1; S++) ans = (ans + dp2[S]) % MOD;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

### AT_abc228_g

[题目链接](https://www.luogu.com.cn/problem/AT_abc228_g)

先观察一个合法的序列是怎么来的。初始找到颜色为 $a_1$ 的行，再在这些行中找颜色为 $a_2$ 的列，再从这些列中找颜色为 $a_3$ 的行......可以观察到，每次转移只跟在哪些行/列有关，且是一个序列唯一对应一种这样的操作集合。那么设 $f_{i,st}$ 为序列前 $i$ 个数当前行/列状态为 $st$ 的方案数。转移直接枚举下一位颜色，即 $\forall 1\le c \le 9,f_{i,st} [\cup_{\exist j\in st,a_{j,k}=c} k=st'] \to f_{i+1,st'}$。复杂度 $\Theta(2^{\max(h,w)} n \max(h,w)c)$。

---

