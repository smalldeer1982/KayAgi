# [ABC292G] Count Strictly Increasing Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_g

数字( `0123456789` )と `?` からなる長さ $ M $ の文字列の列 $ S_1,\ldots,S_N $ が与えられます。

`?` を独立に数字に置き換える方法は $ 10^q(q $ は $ S_1,\ldots,S_N $ に含まれる `?` の個数の合計$ ) $ 通りありますが、そのうち置き換え後の文字列をそれぞれ整数値とみなしたときに $ S_1\lt\ S_2\ \lt\ \ldots\ \lt\ S_N $ が成り立つようなものが何通りあるかを $ 998244353 $ で割った余りを求めてください。

なお、`?` を置き換えた後の $ S_i $ は先頭に $ 1 $ 個以上の `0` が連続していても構いません。例えば、`0000000292` を整数値とみなすと $ 292 $ となります。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 40 $
- $ 1\ \leq\ M\ \leq\ 40 $
- $ N,M $ は整数
- $ S_i $ は数字と `?` からなる長さ $ M $ の文字列
 
### Sample Explanation 1

条件を満たす置き換え方は以下の $ 4 $ 通りです。 - $ S_1 $ の $ 1 $ 文字目の `?` を `0` に、$ S_2 $ の $ 1,2 $ 文字目の `?` をそれぞれ `0`, `1` に置き換える。 - $ S_1 $ の $ 1 $ 文字目の `?` を `0` に、$ S_2 $ の $ 1,2 $ 文字目の `?` をそれぞれ `0`, `2` に置き換える。 - $ S_1 $ の $ 1 $ 文字目の `?` を `0` に、$ S_2 $ の $ 1,2 $ 文字目の `?` をそれぞれ `0`, `3` に置き換える。 - $ S_1 $ の $ 1 $ 文字目の `?` を `0` に、$ S_2 $ の $ 1,2 $ 文字目の `?` をそれぞれ `0`, `4` に置き換える。

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
3 2
?0
??
05```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1
0
0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10
1?22??37?4
1??8?0??49
3?02??8044
51?4?8?7??
5?9?20???2
68?7?6?800
?3??2???23
?442312158
??2??921?8
????5?96??```

### 输出

```
137811792```

# 题解

## 作者：EnofTaiPeople (赞：6)

### Part1 前言

题意：给定 $n$ 个 $m$ 位数 $a_i$，有 `?` 表示该位不确定，我们需要求出将每一个 `?` 转换成 $0\sim9$ 使得 $a_i<a_{i+1}$ 的方案数，$n,m\le40$。

要是 $m\le7$ 就好了！不过怎么可能？

当然如果每个数字的 `?` 都不超过 $7$ 也好啊！然而也不可能。

当然这道题还是小清新的。

### Part2 设计状态

考虑最高位的分布，首先一定不能存在逆序对。

我们可以简单认为是一段 $1$，一段 $2$，一直到一段 $9$，对于一段内的数字并没有得到严格偏序关系，所以我们需要它们在更低的位中得到严格偏序。

所以有很容易的想到了区间动态规划的形式：设 $f_{i,l,r}$ 表示考虑了第 $i$ 及以后的位数，区间 $[l,r]$ 达成严格偏序的方案数。

边界是 $f_{m,l,l}=\begin{cases}1,S_{l,m}\ne?\\10,S_{l,m}=?\end{cases}$，$f_{1,1,n}$ 是答案。

我们需要从 $f_{i+1,l,r}$ 转移到 $f_{i,l,r}$，分两种情况。

1. 区间 $[l,r]$ 在第 $i$ 位完全相等，那么之前就一定要保证严格偏序，从 $f_{i+1,l,r}$ 转移过来，需要考虑出现的非问号数字个数。

2. 区间 $[l,r]$ 在第 $i$ 位不完全相等，可以枚举最后一个完全相等区间。

### Part3 具体实现

想到这里其实已经不难了，不过状态是真的神秘，这里我设 $h_{L,R,l,r}$ 表示区间 $[l,r]$ 该位为 $[L,R]$ 形成严格偏序的方案数，然后就能 $h_{L,R,l,r}\leftarrow h_{L,R',l,k}h_{R,R,k+1,r}$，其中 $R'<R$，$k$ 在 $[l,r)$ 之间。

使用了前缀和优化，时间复杂度为 $O(c^2mn^3)$，但是跑不满，所以飞快，空间 $O(c^2n^2)$，其中 $c$ 为数字值域，本题 $c=10$。

跟同学把这场写完之后，他告诉我这道题其实只需要记该位数字的最大值，但需要再开一维表示只使用某一个数字的答案，这样的时间复杂度为 $O(cmn^3)$，空间 $O(cn^2)$，实际上效率差不多。

$O(c^2mn^3)$ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using pr=pair<int,int>;
const int N=45,M=998244353;
int n,m,f[N][N],g[N][N],h[11][11][N][N],w;
char s[N][N];
int main(){
    scanf("%d%d",&n,&m);
    int i,j,k,l,r,x,y,L,R;
    for(x=1;x<=n;++x)
        scanf("%s",s[x]+1);
    for(l=1;l<=n;++l)f[l][l]=1;
    for(i=m;i;--i){
        memcpy(g,f,sizeof(g));
        memset(f,0,sizeof(f));
        memset(h,0,sizeof(h));
        for(int _k=1;_k<=n;++_k)
            for(l=1,r=_k;r<=n;++l,++r){
                for(k=l,w=0;k<=r;++k)
                    if(s[k][i]!='?')w|=1<<(s[k][i]-'0');
                if(!w){
                    for(k=0;k<10;++k)
                        h[k][k][l][r]=g[l][r];
                }else if(w==(w&-w)){
                    w=__builtin_ctz(w);
                    h[w][w][l][r]=g[l][r];
                }
                for(k=l;k<r;++k){
                    for(L=0;L<10;++L)
                        for(R=L+1;R<10;++R)
                            h[L][R][l][r]=(ll(h[L][R-1][l][k])*h[R][R][k+1][r]+h[L][R][l][r])%M;
                }
                for(L=0;L<10;++L){
                    for(R=L+1;R<10;++R)
                        ((h[L][R][l][r]+=h[L][R-1][l][r])>=M)&&(h[L][R][l][r]-=M);
                    ((f[l][r]+=h[L][9][l][r])>=M)&&(f[l][r]-=M);
                }
            }
    }printf("%d\n",f[1][n]);
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：4)

## [ABC292G-Count Strictly Increasing Sequences](https://atcoder.jp/contests/abc292/tasks/abc292_g) 题解

题意：求确定所有问号为字母并且使得这些序列字典序严格递增的方案数。$n\le 40$。

套路1：这类保证字典序，要求计数的题目通常是设置一个区间DP+记忆化搜索解决问题。

分析：字典序具有一些特殊性质，比如决定两个字符串大小的，只有一个字符；其前面的所有字符必须相同，后面的所有字符无所谓。

这其实就是这些序列所形成的字典树的形态计数。

但是怎么表达一棵字典树呢？观察到了字典树每个节点它子树之中所覆盖的叶子节点必然是一段连续的区间，所以使用区间DP即可解决问题。

其实用区间表达一棵树的形式也是线段树的思想，不过本题不是很涉及到它的特殊结构（比如完全二叉树的性质），不管。

套路2：如何表达一个字典树上的节点呢？我们很容易想到设置 $f[l][r][k]$ 表示当前已经比较了前 $k$ 个字符并且当前节点的子树之中覆盖了 $[l,r]$ 区间的所有叶子节点的总方案数。

这题之中有涉及到字母的变换，可以一个个枚举字母，类似于背包的做法代入进去一个个处理颜色，但是码量比较大划不来。

套路3：重设状态，设 $f[l][r][k][c]$ 表示区间 $[l,r]$ 当前前 $k$ 个字符相同，而它应该取的最小值是 $c$，然后在 $[l,r]$ 区间也是使用背包的方法一个个处理，转移时候使用一个辅助数组 $g[k][i]$ 当作背包的数组表示用到了第 $k$ 种颜色而右端点为 $i$ 的方案数。

判断方案合法可以预处理，即判断 $[l,r]$ 区间有没有别的字母，这个时间复杂度不是瓶颈，所以实现得暴力一点也无所谓。初始值显然。

但是写个背包仍然划不来，毕竟有一些边界值的后顾之忧，码量和编码难度也比较大。

观察到背包的整个过程是一个这个 $(l,r,k,c)$ 节点分裂成多个儿子的过程，我们记忆化搜索就是往它的子树里面搜索然后再通过平等层级的合并方法合并答案。这个过程是形如一个点分多个儿子再将其答案合并起来，而我们的背包过程是枚举其分的大小然后一个个加起来。

所以采用“左儿子右兄弟”的记录法，这样 DP 其实只需要转移两个式子即可。

可以选一些 $c$ 这个数字，$f[l][r][k][c]=\sum_{i=l}^{r-1} f[l][i][k+1][0]+f[i+1][r][k][c+1]$。

可以全选 $c$ 这个数字，也可以全不选 $c$ 这个数字。这时的转移显然。

这个DP的过程显然采用记忆化搜索，因为简洁有力。

时间复杂度分析：$O(N^3M|C|)$（$|C|$ 为字符集大小）。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef int I;
const I N=42,M=42;
I f[N][N][M][10],n,m;
string s[N];
const I mod=998244353;
I mul(I x,I y){return 1ll*x*y%mod;}
I dfs(I l,I r,I k,I c){
	if(c==10)return 0;
	if(k==m+1)return l==r;I&ans=f[l][r][k][c];
	if(ans^-1)return ans;
	ans=dfs(l,r,k,c+1);
	for(I i=l;i<=r;++i)
		if(s[i][k-1]=='0'+c||s[i][k-1]=='?')
			ans=(ans+(1ll*dfs(l,i,k+1,0)*(i==r?1:dfs(i+1,r,k,c+1)%mod)))%mod;
		else break;
	return ans;}
I main(){
	cin>>n>>m;
	for(I i=1;i<=n;++i)
		cin>>s[i];
	memset(f,-1,sizeof(f));
	printf("%d\n",dfs(1,n,1,0));
	return 0;
}
```

## 

---

## 作者：ABookCD (赞：2)

[我的 ABC-292 全场题解](https://www.cnblogs.com/arizonayyds/articles/abc292.html)


#### Solution:

很直观的想法是数位 dp，考虑每一位的填数性质按位做，但发现不太好转移。

考虑再加维度，（毕竟 $n,m$ 很小）在状态定义中加入当前考虑的区间。

设计状态 $dp[now][l][r][st]$，表示当前考虑数的第 $i$ 位，当前位的值大于等于 $st$，在考虑第 $l$ 到第 $r$ 个数。

显然目标状态为 $dp[1][1][n][0]$。

考虑状态转移，在区间 $[l,r]$ 中，存在一个断点 $k$，将区间分成两部分。对于 $[l,k]$，我们让它们当前考虑的这一位 $now$ 的值相同，均为 $st$。接下来，我们把排序目标转移到下一位继续 dp。

对于 $[k+1,r]$，则它们当前位置已经比区间 $[l,k]$ 的数大了，相当于当前位 $now$ 的值要大于等于 $st+1$，继续 dp 即可。此时我们把区间割成了两部分，互不相干，满足区间 dp 的性质。

状态转移方程：
$$
dp[now][l][r][st]=(dp[now][l][r][st+1]+\sum\limits_{k\in [l,r] \land  (s[k]='?'\lor s[k]=st)}dp[now+1][l][k][0]\times dp[now][k+1][r][st+1])
$$
用记忆化搜索写，比较方便。

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
char a[45][45];
int dp[45][45][45][15];
int n,m;
int dfs(int now,int l,int r,int st){
	if(now>m){
		return (l==r);
	}
	if(l>r){
		return 1;
	}
	if(st>9){
		return 0;
	}
	if(dp[now][l][r][st]>=0) return dp[now][l][r][st];
	int ans=dfs(now,l,r,st+1);
	for(int i=l;i<=r;i++){
		if(a[i][now]!='?'&&a[i][now]!=st+'0') break;
		ans=(ans+dfs(now+1,l,i,0)*dfs(now,i+1,r,st+1)%mod)%mod;
	}
	dp[now][l][r][st]=ans;
	return ans;
}
signed main(){

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}
	memset(dp,-1,sizeof dp);
	cout<<dfs(1,1,n,0)<<endl;
	return 0;
}
```


---

## 作者：lingfunny (赞：2)

# ABC292

## G - Count Strictly Increasing Sequences

前面思路基本相同，我们先观察最高位，显然是一段 $0$，一段 $1$，不断往下接……

那么对于最高位相同的一段数字，我们要在次高位及之后满足严格偏序。

于是可以从低往高区间 dp：`f[i][l][r]` 表示填了第 $i$ 位及之后，$[l, r]$ 区间内的数构成严格偏序的方案数。

更新时，考虑刷表。我们枚举一个数字 $j = 0,1,\cdots,9$，然后刷 `f[i][l][r]`。

具体来说，枚举一段后缀 $(k, r]$ 选择了 $j$，从 `f[i][l][k] * f[i + 1][k + 1][r]` 转移过来即可。

最后一个边界需要注意是，上面的转移式少考虑了整个区间全选 $j$。这个特判就不多说了。

时间复杂度 $O(mn^3\times \vert \Sigma\vert)$。

```cpp
// Problem: G - Count Strictly Increasing Sequences
// URL: https://atcoder.jp/contests/abc292/tasks/abc292_g
// Group: AtCoder - AtCoder Beginner Contest 292
// Time: 2023-03-04 20:00
// Author: lingfunny

#include <bits/stdc++.h>
using LL = long long;
using uint = unsigned;
using namespace std;

constexpr int mod = 998244353;
// assume -mod <= x < 2mod
int normZ(int x) {
	if (x < 0) x += mod;
	if (x >= mod) x -= mod;
	return x;
}
template <typename T> T qpow(T x, LL k) {
	T res = 1;
	for (; k; k >>= 1, x *= x)
		if (k & 1) res *= x;
	return res;
}

struct Z {
	int x;
	Z(int x = 0) : x(normZ(x)) {}
	Z(LL x) : x(normZ(x % mod)) {}
	int val() const { return x; }
	Z operator-() const { return Z(normZ(mod - x)); }
	Z inv() const {
		assert(x != 0);
		return qpow(*this, mod - 2);
	}
	Z &operator*=(const Z &rhs) {
		x = (LL)x * rhs.x % mod;
		return *this;
	}
	Z &operator+=(const Z &rhs) {
		x = normZ(x + rhs.x);
		return *this;
	}
	Z &operator-=(const Z &rhs) {
		x = normZ(x - rhs.x);
		return *this;
	}
	Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
	friend Z operator*(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res *= rhs;
		return res;
	}
	friend Z operator+(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res += rhs;
		return res;
	}
	friend Z operator-(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res -= rhs;
		return res;
	}
	friend Z operator/(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res /= rhs;
		return res;
	}
};

const int mxn = 45;
Z f[mxn][mxn][mxn], g[mxn][mxn][mxn];
int n, m, c[mxn][mxn];
char s[mxn][mxn];

signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
		for (int j = m; j; --j) c[i][j] = c[i][j + 1] + (s[i][j] == '?');
	}
	for (int i = 1; i <= n; ++i) f[m + 1][i][i] = 1;
	// 10 * m * n *n * n
	for (int o = m; o >= 1; --o) {
		for (int v = 0; v <= 9; ++v) {
			memcpy(g[o], f[o], sizeof f[o]);
			for (int len = 1; len <= n; ++len)
				for (int l = 1, r; (r = l + len - 1) <= n; ++l) {
					bool check = true;
					for (int k = r; (check &= (s[k][o] == '?' || s[k][o] == v + '0')) && --k >= l;)
						if (check) f[o][l][r] += g[o][l][k] * f[o + 1][k + 1][r];
					if (check) f[o][l][r] += f[o + 1][l][r];
				}
		}
	}
	printf("%d\n", f[1][1][n].val());
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

我们发现，对于每一列中的一段区间，如果这段区间上一位相同，那么这一列一定是不递减的（因为要在后面确定偏序关系）。

于是我们可以设计一个状态 $f(pos,l,r,num)$ 表示第 $pos$ 列第 $l$ 到 $r$ 行都设为 $\ge num$ 数字的方案数。

转移时我们可以枚举 $k$，让 $[l,k]$ 全部设为 $num$，此时进入下一层，所以是 $f(pos + 1,l,k,0)$；那么剩下的 $[k + 1,r]$ 设为 $> num$ 的数字（也就是 $\ge num + 1$），所以是 $f(pos,k + 1,r,num+1)$。最后根据乘法原理把它们相乘。

最后 $f(pos,l,r,num)$ 的答案就是 $\displaystyle \sum_{k = l-1}^r f(pos + 1,l,k,0) \times f(pos,k + 1,r,num + 1)$。整个答案就是 $f(1, 1, n, 0)$。可以使用记搜。

一些细节：

- $k = l - 1$ 的原因是 $num$ 可以不选。不过就要特判 $l > r$ 的时候答案为 $1$。

- 由于题目要求 **严格递增**，所以在最后一位（$pos = m$）的时候只有 $l = r$（$l > r$）有答案，其他时候没有答案。

- 当矩阵的 $k$ 行 $i$ 列不是 $num$ 也不是 `?` 的时候，就不能再转移了。

- $num > 9$ 的时候就不能继续转移了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 45, mod = 998244353;

int f[N][N][N][11], n, m;
char jz[N][N];

int dfs( int pos, int l, int r, int num ) {
    if( l > r ) return 1;
    if( pos > m ) return l == r;
    if( num > 9 ) return 0;
    if( f[pos][l][r][num] != -1 ) return f[pos][l][r][num];
    int ans = 0;
    for( int k = l - 1; k <= r; ++k ) {
        if( k >= l && jz[k][pos] != '?' && jz[k][pos] != num + '0' ) break;
        ans += 1ll * dfs( pos + 1, l, k, 0 ) * dfs( pos, k + 1, r, num + 1 ) % mod;
        ans %= mod;
    }
    return f[pos][l][r][num] = ans;
}

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    memset( f, -1, sizeof f );
    cin >> n >> m;
    for( int i = 1; i <= n; ++i ) for( int j = 1; j <= m; ++j ) {
        cin >> jz[i][j];
    }
    cout << dfs( 1, 1, n, 0 ) << endl;
    return 0;
}
```

---

