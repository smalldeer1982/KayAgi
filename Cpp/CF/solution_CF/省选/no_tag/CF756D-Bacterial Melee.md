# Bacterial Melee

## 题目描述

Julia is conducting an experiment in her lab. She placed several luminescent bacterial colonies in a horizontal testtube. Different types of bacteria can be distinguished by the color of light they emit. Julia marks types of bacteria with small Latin letters "a", ..., "z".

The testtube is divided into $ n $ consecutive regions. Each region is occupied by a single colony of a certain bacteria type at any given moment. Hence, the population of the testtube at any moment can be described by a string of $ n $ Latin characters.

Sometimes a colony can decide to conquer another colony in one of the adjacent regions. When that happens, the attacked colony is immediately eliminated and replaced by a colony of the same type as the attacking colony, while the attacking colony keeps its type. Note that a colony can only attack its neighbours within the boundaries of the testtube. At any moment, at most one attack can take place.

For example, consider a testtube with population "babb". There are six options for an attack that may happen next:

- the first colony attacks the second colony ( $ 1→2 $ ), the resulting population is "bbbb";
- $ 2→1 $ , the result is "aabb";
- $ 2→3 $ , the result is "baab";
- $ 3→2 $ , the result is "bbbb" (note that the result is the same as the first option);
- $ 3→4 $ or $ 4→3 $ , the population does not change.

The pattern of attacks is rather unpredictable. Julia is now wondering how many different configurations of bacteria in the testtube she can obtain after a sequence of attacks takes place (it is possible that no attacks will happen at all). Since this number can be large, find it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the population can never change since all bacteria are of the same type.

In the second sample three configurations are possible: "ab" (no attacks), "aa" (the first colony conquers the second colony), and "bb" (the second colony conquers the first colony).

To get the answer for the third sample, note that more than one attack can happen.

## 样例 #1

### 输入

```
3
aaa
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
ab
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
babb
```

### 输出

```
11
```

## 样例 #4

### 输入

```
7
abacaba
```

### 输出

```
589
```

# 题解

## 作者：Poncirus (赞：5)

upd：不好意思交了两遍！！！第一遍代码粘错了，有劳管理员了！！！

---

已有的题解都是以具体字符作为 DP 状态，本篇使用了更加简明清晰的位置作为状态。

---

可以很简单的想到，最终字符串一定由原串中的部分字符，按照其在原串中的顺序，经过若干次重复得到。那么我们把一段连续的相同字符视为一个字符，得到的这个串就是原串的一个子序列。

所以我们只需要求出原串的不同子序列个数，再经过一定的排列组合就可以求出方案数。

比如，我们知道一个长度为 $n$ 的串中有 $k$ 个长度为 $m$ 的子序列，那么由插板法可得这 $k$ 个子序列会贡献 $C_{n-1}^{m-1}\times k$ 的方案数。

那么不同子序列个数怎么求呢？显而易见需要 DP，规定 $f_{i,j}$ 表示一个长度为 $i$ 的子序列最后一位为 $s_j$  的方案数，就可以直接 $f_{i,j}=\sum f_{i-1,k}$。

但这样做有一个问题，就是会重复计算。假如原串中在 $i$ 位置有一个 `'o'`，$i+1$ 位置又有一个 `'o'`，两个都可以从前面某个位置（假设为 $j$；假设 $j$ 上其中一个被计入方案数的合法子序列为 `"hyac"`），那么转移到 $i$ 时，计算了 `"hyaco"`，到了 $i+1$，依然可以从 $j$ 处得到 `"hyaco"`，就会重复计算。

那么怎么避免这一点呢？对于一个位置 $i$，假设其上一个相同字母的位置为 $last_i$，我们规定其仅可从 $(last_i,i)$ 进行转移即可（注意两边都是开区间）。

初始化是对于每一个没有前驱的 $i$，$f_{1,i}=1$。

实现上，因为 $n$ 的大小是 $5\times 10^3$，转移区间又是连续的，我们用一个前缀和进行优化即可。

还有一个实现上的细节就是开 `long long` 会全部爆空间，这个时候你可以像我的代码中所展示的那样全部开 `int`，因为唯一会爆 `int` 的是取模中的运算，你在这些运算中强转一下类型即可。

时间复杂度 $\mathcal O(n^2)$，相对来说是一种不那么抽象的做法。

```cpp
#include <bits/stdc++.h>
namespace XSC062 {
const int mod = 1e9 + 7;
const int maxn = 5e3 + 5;
int n, res;
char s[maxn];
int fac[maxn];
int la[maxn], p[maxn];
int f[maxn][maxn], u[maxn][maxn];
int max(int x, int y) {
	return x > y ? x : y;
}
int qkp(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1)
			res = res * 1ll * x % mod;
		x = x * 1ll * x % mod;
		y >>= 1;
	}
	return res;
}
int inv(int x) {
	return qkp(x, mod - 2);
}
int A(int n, int m) {
	return fac[n] * 1ll * inv(fac[n - m]) % mod;
}
int C(int n, int m) {
	return A(n, m) * 1ll * inv(fac[m]) % mod;
}
int main() {
	scanf("%d %s", &n, s + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		la[i] = p[s[i] - 'a' + 1];
		if (!la[i]) f[1][i] = 1, ++res;
		u[1][i] = u[1][i - 1] + f[1][i];
		p[s[i] - 'a' + 1] = i;
		fac[i] = fac[i - 1] * 1ll *  i % mod;
	}
	for (int i = 2; i <= n; ++i) {
		int sum = 0;
		for (int j = i; j <= n; ++j) {
			int k = max(i - 1, la[j] + 1);
			if (k <= j - 1)
				f[i][j] = (u[i - 1][j - 1] - u[i - 1][k - 1]) % mod;
			u[i][j] = (u[i][j - 1] * 1ll + f[i][j]) % mod;
			sum = (sum * 1ll + f[i][j]) % mod;
		}
		res = (res + C(n - 1, i - 1) * 1ll * sum % mod) % mod;
	}
	res = (res + mod) % mod;
	printf("%d\n", res);
	return 0;
}
} // namespace XSC062
int main() {
	XSC062::main();
	return 0;
}
```

---

## 作者：BreakPlus (赞：4)

~~被 Daniel_lele 在伟大的神圣的 OICon 给 D 了，深深感受到自己的 $\mathcal{O}(|\sum| n^2)$ 做法的逊色以及我自己的可耻的菜。~~

### Step1. 观察性质

定义 $f(s)$ 表示字符串 $s$ 相邻去重后的结果。

若 $s$ 可以变换得到 $t$，当且仅当 $\exists a $ 为 $s$ 的子序列，$s.t.$ $f(a) = f(t)$。

### Step.2 大致方向

我们不难想到一个很容易的 DP，通过简单的计数在 $\mathcal{O}(n^2)$ 的时间复杂度内解决。但是我们发现一个很重要的问题：若相同的字符 **分开成为多段**，那么在计数的过程中，相同的方案会以其不同的 **段数编号** 为理由算重，这是我们要解决的问题。

### Step.3 解决问题

我们再次大致想出这样的方法：设 $f(i,j)$ 表示方案串的第 $i$ 个位置，最后的字符为 $j$ 的方案数，接下来暴力枚举这一段的长度以及下一个与之不同字符（放心，可以前缀和优化，所以先这样想着），貌似可以转移。

这个不大行。或者说，如果我们 **先枚举** $i$，这个思路是行不通的：比如字符串 ``aabaa``，这个字符 ``a`` 是在 ``b`` 前还是 ``b`` 后就不得而知，整个串中有多个字符 $j$，你怎么知道这是哪一段的？

咦，上面的问题能否通过 **按照段的顺序依次考虑** 解决？答案是肯定的。我们设 $f(i,j)$ 表示第 $i$ 个位置，最后的字符是 $j$ 的方案数。

我们在第一层循环枚举段，假设这一段的字符为 $k$，我们作以下步骤更新 $f$：

1. 按顺序枚举一个位置 $i$；
2. 将原有的 $f(i,k)$ 清零，重新计算；
3. 枚举这一段的长度以及上一个**不同的字符**进行转移。注意是字符，不是对应的段。特殊情况是 $1\sim i$ 位置上均是该字符。

为什么这样就不会算重了呢？首先，我们做到了按照字符本身考虑；其次，我们通过一次枚举段进行扩展，遵循了原字符串要求的顺序。

即使我们这样，可以发现，同一个字符在方案串 $t$ 中出现多次的情况依然可以被计算，因为我们仅仅保证了它们中间有隔开的字符。

### Step.4 代码实现

不建议观看，因为经过了前缀和优化。建议读者自行考虑。

```cpp
ll n, f[26][5005]; char str[5005];
ll table[256]; 
vector<char>vec;
ll node(ll x){
	if(x>=mod) return x-mod;
	return x;
}
void solve(){
	scanf("%lld%s",&n,(str+1));
	ll lst = 1, cnt = 0;
	vec.push_back('\0');
	for(ll i=1;i<=n;i++)
		if(i>1 && str[i]!=str[i-1]){
			vec.push_back(str[i-1]);
			++ cnt; table[str[i-1]] = cnt;
			lst = i;
		}
	vec.push_back(str[n]);
	ll sz = vec.size()-1;
	++ cnt; table[str[n]] = cnt;
	for(ll i=1;i<=sz;i++){
		long long all = 0;
		for(ll j=1;j<=n;j++){
			f[vec[i]-'a'][j] = node ( 1 + all ) ;
			for(ll l=0;l<=25;l++) if(vec[i] != l+'a') all += f[l][j];
			all %= mod;
		}
	}																
	ll ans=0;
	for(ll j=0;j<=25;j++){
		ans = (ans + f[j][n]) % mod;
	}
	printf("%lld\n", ans);
}
```

---

## 作者：1saunoya (赞：4)

首先定义一个状态 $dp_{j,c}$ 表示选了 $j$ 个位置最后一个字符是 $c$。
转移方程是

$dp_{j,c} = \sum dp_{j-1,k} [k \neq c]$
代表的是长度为 $j$ 的以 $c$ 结尾的方案数…


然后你发现，这个其实可以把 abc 变成 aab 的，所以很显然…是跟断点数量有关，假设你有 $m$ 个断点，你发现你选的这个其实是个组合数 $(^n_m)$ 其实证明就是当做断点来看，然后每次你枚举长度，倒序枚举，大概是01背包的那种想法，把不相同的全部加进来…这样就做完了。

```cpp
// by Isaunoya
#include<bits/stdc++.h>
using namespace std;
struct io {
	char buf[1 << 23 | 3], *s; int f;
	io() { f = 0, buf[fread(s = buf, 1, 1 << 23, stdin)] = '\n'; }
	io& operator >> (int&x) {
		for(x = f = 0; !isdigit(*s); ++s) f |= *s  == '-';
		while(isdigit(*s)) x = x * 10 + (*s++ ^ 48);
		return x = f ? -x : x, *this;
	}
};

const int maxn = 5e3 + 35;
const int mod = 1e9 + 7;

int C[maxn][maxn];
int dp[maxn][27];

int add(int x, int y) {
	return (x + y >= mod) ? (x + y - mod) : (x + y);
}
signed main() {
	string s;
	vector<int> a;
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int len; cin >> len; cin >> s;
	a.clear(); a.push_back(0);
	for(char x: s) {
		int c = x - 'a' + 1;
		if(c == a.back()) continue;
		a.push_back(c);
	}
	int n = len;
	C[0][0] = 1;
	for(int i = 1 ; i <= n ; i ++) {
		for(int j = 1 ; j <= i ; j ++) { C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]); }
	}
	dp[0][0] = 1;
	for(int i = 1 ; i < a.size() ; i ++) {
		for(int j = i ; j ; j --) {
			int x = a[i], ans = 0;
			for(int c = 0; c <= 26; c ++) { if(c ^ x) { ans = add(ans, dp[j - 1][c]); } }
			dp[j][x] = ans;
		}
	}
	int ans = 0;
	for(int i = 1 ; i < a.size(); i ++) {
		int tmp = 0;
		for(int c = 1 ; c <= 26 ; c ++) tmp = add(tmp, dp[i][c]);
		ans = add(ans, 1ll * C[n][i] * tmp % mod);
	}
	cout << ans << '\n'; 
	return 0;
}
```

---

## 作者：zifanwang (赞：3)

给一个 $O(n^2)$ 的做法。

考虑从左到右扫描最终得到的字符串，如果当前的字符和前一个字符相同，就删掉这个字符。由题意可知，最终得到的字符串一定是 $s$ 的一个**子序列**。

我们定义状态 $dp[i][j]$ 表示：当前子序列的最后一个字符是 $s[i]$，已经填完了最终字符串的前 $j$ 个字符，方案数是多少。

为了不重复计算子序列，我们再定义 $ls[i][j]$ 表示 $s$ 的前 $i$ 个字符里所有为 $j$ 的字符中最靠后的字符的位置。下面是求 $ls$ 数组的方法：

```cpp
for(int i=1;i<=n;++i){
	for(int j=0;j<26;++j)ls[i][j]=ls[i-1][j];
	ls[i][s[i]-'a']=i;
}
```

那接下来怎么求出 $dp[i][j]$ 呢？我们可以把这 $j$ 个字符全部填 $s[i]$ 方案数是 $1$，接下来我们可以枚举子序列的上一个字符 $k$，我们可以得出转移方程：

$$
dp[i][j]=1+\sum_{0\le k<25\land k\neq s[i]}\sum_{l=1}^{j-1}dp[ls[i-1][k]][l]
$$

我们可以用一个前缀和优化做到 $O(26\cdot n^2)$，维护 $d[i][j]$ 表示 $\sum_{k=1}^{j}dp[i][k]$。

那么怎么再优化到 $O(n^2)$ 呢？

我们可以再维护一个 $f[j]$ 表示 $\sum_{i=0}^{25}dp[i][j]$ 和一个 $ds[i]$ 表示 $\sum_{j=1}^{i}f[j]$。

下面是最终的转移方程：
$$
dp[i][j]=1+ds[j-1]-d[i][j-1]
$$

代码：
```cpp
#include<bits/stdc++.h>
#define mxn 5003
#define md 1000000007
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
int n,m,sum,f[mxn],dp[26][mxn],d[26][mxn],ds[mxn];
char s[mxn],t[mxn];
signed main(){
	scanf("%d%s",&m,t+1);
	rep(i,1,m)if(t[i]!=t[i-1])s[++n]=t[i];
	rep(i,1,n){
		int x=s[i]-'a';
		rep(j,1,m){
			sum=f[j],f[j]=(f[j]-dp[x][j])%md;
			dp[x][j]=(ds[j-1]-d[x][j-1]+1)%md;
			d[x][j]=(dp[x][j]+d[x][j-1])%md;
			f[j]=(f[j]+dp[x][j])%md;
			ds[j]=(ds[j-1]+f[j])%md;
		}
	}
	cout<<(f[m]+md)%md;
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：1)

这是一种时空 $O(n^2)$ 的新做法。

考虑到字符串是原串的子序列中每个字符经过若干次重复得到。

那么我们定义 $dp_{i,j}$ 表示前 $i$ 个字符中，已经选出了 $j$ 个字符得到的答案。显然，根据隔板法，若此时不取，答案为 $C_{n-1}^{j-1}$。

注意到  `ab` 其实可以扩展到 `aab` 的情况，所以子序列中不可能出现连续的两个相同的字符。

注意到不同位置的 `ab` 和 `ab` 等价，我们只需要考虑一个 `ab` 即可。

这样问题就转化成了一个子序列计数问题。

考虑这样一个串 `abb` 对于 `a`，后面可以接 $2/3$ 号位的 `b`，但是根据上述描述，这两种情况是等价的，此时，我们不妨钦定 `a` 接后面第一次出现的 $b$。

我们直接转移到后面接的 $25$ 种字符即可，时间复杂度 $O(|\sum|n^2)$。

[这样就过了](https://codeforces.com/contest/756/submission/232497621)，但是显然不够优秀，我们考虑优化。

定义 $nxt_{i,j}$ 表示 $i$ 后第一次出现字符的位置。（根据上述方法，显然不含 $i$）

那么注意到 $nxt_i$ 和 $nxt_{i'}$（其中 $i'$ 表示的是后面出现的字符中，第一个与 $i$ 不同的位置）唯一的区别点就在于 $nxt_{i'}$，于是我们考虑从 $i'$ 进行转移。

容斥一下，发现 $i'$ 和 $i$ 在转移上的区别就是 $(i,j)$ 不能转移到 $(nxt_{i',s_i},j+1)$，但是 $(i',j)$ 可以，剪掉即可。$(i,j)$ 可以转移到 $(i',j+1)$，但是 $(i',j)$ 不可以，加上即可。

最后注意 $j=0$ 的情况要单独转移，因为我们 $i$ 是强制取了的，不会出现 $dp_{i,0}(i>0)$ 的情况。

[code](https://codeforces.com/contest/756/submission/232499781)

不要开 `#define int long long`，要 MLE。

---

## 作者：LCat90 (赞：0)

这个操作本质上是覆盖，我们意识到每个字符出现多次影响是不大的。所以我们考虑忽略它们，现在就考虑对一个相邻位置都不同的字符串进行操作。
  
具体来说，对于一个子序列 $b$，我们可以将其操作成为连续的一段，然后使用这一段来确定最终的 $S$，方法：令 $b_i+1$ 到 $b_{i+1}$ 均为 $b_{i+1}$。
  
现在就要计算长度为 $1$ 到 $n$ 的子序列的个数，对应上该子序列填充到整个串中的方案，这个方案数要熟练记忆，是 $C_{n-1}^{m-1}$。  
  
然后就是用 DP 求子序列的个数。转移的 $b_i\to b_{i+1}$ 之间不能有 $s_{i+1}$，因为我们枚举的是子序列的个数。假设可以，对于 $b_i$，它可以给 $(b_i,b_{i+1}]$ 中的 $s_{i+1}$ 贡献，但是 $s_{i+1}$ 相等，于是重复了。
  
所以我们的转移要从上一个相同字符位置加 $1$ 到这里。设 $dp_{i,j}$ 表示子序列长度为 $i$，最后一位为 $s_j$ 的方案数。转移式：$dp_{i,j}=\sum dp_{i-1,k}$，其中 $k$ 满足上述条件。
  
DP 的转移看上去是立方，实际上是 $O(26n^2)$ 的。但是我们可以前缀和优化到 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3 + 5, Mod = 1e9 + 7;
int n, dp[N][N], fac[N], ifac[N], lst[N][30], pre[N][N], ans, oh[N];
int qkpow(int a, int b) {
	if(b == 0) return 1;
	if(b & 1) return a * qkpow(a, b - 1) % Mod;
	int t = qkpow(a, b >> 1);
	return t * t % Mod;
} 
string s; 
int C(int n, int m) { return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }
signed main() {	
	cin >> n >> s; fac[0] = 1;
	for(int i = 1;i <= n; ++i) fac[i] = fac[i - 1] * i % Mod; 
	ifac[n] = qkpow(fac[n], Mod - 2);
	for(int i = n - 1;i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % Mod;
	s = " " + s;
	for(int i = 1;i <= n; ++i) {
		for(int j = 0;j < 26; ++j) lst[i][j] = lst[i - 1][j];
        oh[i] = lst[i - 1][s[i] - 'a'];
		lst[i][s[i] - 'a'] = i;
		if(!lst[i - 1][s[i] - 'a']) dp[1][i] = 1, ans ++;
        pre[1][i] = pre[1][i - 1] + dp[1][i];
	}
	for(int i = 2;i <= n; ++i) { // 长度 
		int sum = 0;
		for(int j = i;j <= n; ++j) {
			int x = oh[j] + 1; 
			x = max(x, i - 1);
            if(x <= j - 1) dp[i][j] = (pre[i - 1][j - 1] - pre[i - 1][x - 1]) % Mod;
			pre[i][j] = (pre[i][j - 1] + dp[i][j]) % Mod;
			sum = (sum + dp[i][j]) % Mod;
		} 
		ans = (ans + C(n - 1, i - 1) * sum % Mod) % Mod;
	}
	cout << ans;
	return 0;
}
```

---

