# [ARC168C] Swap Characters

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc168/tasks/arc168_c

`A`, `B`, `C` からなる長さ $ N $ の文字列 $ S $ が与えられます．

以下の操作を $ 0 $ 回以上 $ K $ 回以下行うことを考えます．

- $ S $ 内の $ 2 $ 文字を自由に選び，入れ替える．
 
操作後の $ S $ としてあり得る文字列が何通りあるかを $ 998244353 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ 1\ \leq\ K\ \leq\ 100 $
- $ S $ は `A`, `B`, `C` からなる長さ $ N $ の文字列．
- 入力される値はすべて整数．
 
### Sample Explanation 1

以下のように $ 4 $ 通りの文字列が得られます． - $ S= $`ABC` : $ 0 $ 回の操作を行えばよい． - $ S= $`BAC` : $ 1,2 $ 文字目を入れ替える操作を行えばよい． - $ S= $`CBA` : $ 1,3 $ 文字目を入れ替える操作を行えばよい． - $ S= $`ACB` : $ 2,3 $ 文字目を入れ替える操作を行えばよい．

## 样例 #1

### 输入

```
3 1
ABC```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2
ABC```

### 输出

```
6```

## 样例 #3

### 输入

```
4 5
AAAA```

### 输出

```
1```

## 样例 #4

### 输入

```
30 10
CACCABAABBABABBCBBCAAACAAACCCA```

### 输出

```
42981885```

# 题解

## 作者：快乐的大童 (赞：7)

先考虑一个比较简单的问题：假如我们确定了最终的 $S$，从当前的 $S$ 操作到最终的 $S$ 的最小步数是多少？[题目链接](https://www.luogu.com.cn/problem/P1459)

考虑贪心，我们先尽可能的两两交换以满足条件（类似于 `b` 换 `a`，`a` 换 `b` 的情况），对于剩下的仍未满足条件的位置，用全排列交换（类似于 `a` 换 `b`，`b` 换 `c`，`c` 换 `a` 的情况）以满足条件。

以下令 $a\rightarrow b$ 代表 最初的 $S$ 中某一位置的字符为 $a$，最终的 $S$ 中该位置的字符为 $b$。

回到原问题上，考虑枚举 $a\rightarrow b,b\rightarrow a,a\rightarrow c,c\rightarrow a,b\rightarrow c,c\rightarrow b$ 的位置数，判断最小交换次数是否小于等于 $k$，然后加组合数的贡献即可。

时间复杂度 $O(k^6)$，显然过不去。

考虑另一种枚举方法，我们先枚举 $a,b$ 之间，$b,c$ 之间以及 $a,c$ 之间的交换次数（显然每次交换对最小步数的贡献为 $1$），设它们为 $A,B,C$。则 $a\rightarrow b,b\rightarrow a$ 的次数均为 $A$，$a\rightarrow c,c\rightarrow a$ 的次数均为 $C$，$b\rightarrow c,c\rightarrow b$ 的次数均为 $B$。

再枚举全排列交换次数（显然每次交换对最小步数的贡献为 $2$），设它为 $D$。

那么 $D$ 只可能被加到 $a\rightarrow b,b\rightarrow c,c\rightarrow a$ 或者 $a\rightarrow c,c \rightarrow b,b\rightarrow a$ 的次数里。剩下的情况都是这两种情况的其中一种的全排列。

那思路就清晰了：先枚举 $A,B,C,D$，再枚举 $D$ 被加到前者的情况里还是后者的情况里，每次加进答案的贡献数就是组合数。

注意两点：

- 枚举的时候要满足 $A+B+C+2D\le k$。
- 当 $D=0$ 时，$D$ 加进前者、后者的情况是一样的。为了避免算重，我们只需要算出其中一种。

时间复杂度 $O(k^4)$，但实际上有用的状态数只有七位数。

代码：[https://atcoder.jp/contests/arc168/submissions/47767071](https://atcoder.jp/contests/arc168/submissions/47767071)

---

## 作者：kimidonatsu (赞：3)

## 题意简述

给定一个长度为 $n$ 的由 $\texttt{ABC}$ 组成的字符串，可以进行 $0 \sim k$ 次操作：选择两个字符 $s_i$ 和 $s_j$，交换他们的位置。求最终得到的字符有多少种，答案对 $998244353$ 取模。

## 思路分析

如果常规地从正面思考会比较难解决问题，那么我们换一个角度思考：

已知一个目标字符串 $T$，求从原来的字符串 $s$ 变换至 $T$ 的最小操作数是多少？

设 $C[x][y]$ 为对应位置上 $S_i = x$ 而 $T_i = y$。每次交换可以使 $C[x][y]$ 和 $C[y][x]$ 分别减去 $1$，在尽可能的交换操作后，我们就可以接近甚至得到一个 $C[x][y] = 0$ 的情况。在这里，我们称这种操作为操作 1。

那么如果无法继续上面的操作怎么办呢？容易发现，$C[A][B] = C[B][C] = C[C][A]$，我们用 $\theta_1$ 表示它；还有 $C[A][C] = C[C][B] = C[B][A]$，我们再用 $\theta_2$ 来表示。由于 $\theta_1$ 和 $\theta_2$ 中至少有一个为 $0$，如果 $\theta_1 \gt 0$，那么我们可以用之前交换操作的思路将 $\theta_1$ 化简掉：

$$\texttt{ABC} \to \texttt{BAC} \to \texttt{BCA}$$

同理尽可能地这样操作显然也可以让 $C[x][y]$ 尽可能为 $0$，同样的对于 $\theta_2$ 我们也可以运用类似的思路化简 $\theta_2$。我们再把这种操作称为操作 2。

如果 $C[x][y]$ 固定了，那么上述最优的操作次数也固定了。

这里对于 $C[x][y]$ 有四方面的限制：

- 操作 1 中 $(x, y) = (\texttt{A}, \texttt{B}), (\texttt{A}, \texttt{C}), (\texttt{B}, \texttt{C})$ 的操作次数
- 操作 2 中 $\theta_1$（或者 $\theta_2$）的值。

考虑使用排列组合枚举所有可能的组合，因此需要考虑的总共数量为 $O(K^4)$。

因此，问题可以以 $O(N + K^4)$ 的时间复杂度解决。

参考代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int N = 2e5 + 5e4 + 5, Mod = 998244353;

int n, k;
i64 ans, cnt[5], fac[N], inv[N];
char s[N];

i64 Cal(i64 m, i64 a) {
	if (m < a) return 0;
	return fac[m] * inv[m - a] % Mod * inv[a] % Mod;
}

i64 qpow(i64 x, int p) {
	i64 res = 1;
	while (p) {
		if (p & 1) res = res * x % Mod;
		x = x * x % Mod, p >>= 1;
	}
	return res;
}

void solve() {
	scanf("%d %d %s", &n, &k, s);
	for (auto c : s) cnt[c - 'A']++;
	for (int i = 0; 2 * i <= k; i++)
		for (int a = 0; a + 2 * i <= k; a++)		// AB
			for (int b = 0; b + 2 * i + a <= k && i + a + b <= cnt[0]; b++)	// AC
				for (int c = 0; a + b + c + 2 * i <= k && i + a + c <= cnt[1] && i + b + c <= cnt[2]; c++) {	// BC
					i64 s = 1, ms = 1;
					s = Cal(cnt[0], i + a + b) % Mod * Cal(i + a + b, i + a) % Mod * Cal(cnt[2], i + b + c) % Mod * Cal(i + b + c, i + b) % Mod * Cal(cnt[1], i + a + c) % Mod * Cal(i + a + c, i + c) % Mod;
					ms *= Cal(cnt[0], i + a + b) % Mod * Cal(i + a + b, i + b) % Mod * Cal(cnt[2], i + b + c) % Mod * Cal(i + b + c, i + c) % Mod * Cal(cnt[1], i + a + c) % Mod * Cal(i + a + c, i + a) % Mod;
					ans = (ans + ms + (i == 0 ? 0 : 1) * s) % Mod;
				}
	printf("%lld\n", ans);
}

int main() {
	fac[0] = 1, n = 250000;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % Mod;
	inv[n] = qpow(fac[n], Mod - 2);
	for (int i = n - 1; ~i; i--)
		inv[i] = inv[i + 1] * (i + 1) % Mod;
	solve();
	return 0;
}

```


---

## 作者：CrTsIr400 (赞：3)

省流：

特性很自由，暴力行不通。

记录 A B C，特征来追踪。

暴力枚转移，循环写六重。

建成有向图，边权要清空。

入出很均衡，循环少两重。

简单组合算，代码五分钟！

---

hint1:

因为记录全部 $k$ 步骤生成的字符串种类，真的是天文数字，所以这条路显然行不通，观察一下特殊性质，发现 $K$ 很小，字符集很小。

考虑对于字符串 $S$，如何通过最少的操作次数来到达某个字符串 $T$。显然 $T$ 的 `A`,`B`,`C` 数量和 $S$ 的一样。

考虑利用交换的“二元关系”，再利用**字符集很小**的特性，来解决这道题目。

---

hint2:

首先，因为这个数列可以任意交换，它具有非常自由的特性，不妨给它排个序研究研究答案。

更进一步，发现只有 `A,B,C` 的个数才能影响答案。所以 $n$ 的范围其实是无关紧要的，原生的那个字符串也是无关紧要的，因为我不需要构造最后的方案，我只要一个数字。

---

hint3:

自然地想到，“有效”的交换，是怎么样的，不应该出现某个位交换许多次之后又回到自己的情况，这显然是不优的。

如果交换次数无限的话，答案就是一个多重集排列数。但是，我们的交换次数很有限，是不能乱来的。

---

暴力做法：

字符串 $T$ 也需要很大量的信息，所以我们不能完整记录它。

我们尝试构建出最终要求的字符串 $T$ 的**特征**，要求是这些特征已经能够**不重不漏**地描述一类字符串，利用这个特征，直接组合数计算一下就能得到答案。

尝试枚举 $S$ 中每种字符转移到 $T$ 中每种字符的方案。理所应当地，可以枚举 `A->B,A->C,B->A,B->C,C->A,C->B` 的变化次数，`A->A` 和 `B->B,C->C` 的这三种转移不用理（最优化的情况下，它不需要操作）。

一步步来，这个 $O(k^6)$ 的暴力已经涵盖了很多情况。但是直接弄答案似乎判定都不好判定。

---

考虑优化+抽象模型：

首先是可以把这些转移都写成建边的形式，每条边的边权为变化次数。

一张三个点的有向完全图没啥性质。但是怎么交换都要保证 $S$ 和 $T$ 中各字符的出现次数相等，所以尝试把这个条件改写一下。

也其实就是，$A$ 所有**出边的边权和等于所有入边的边权和**！这样枚举也许可以稍微剪枝？

剪掉的不是一点点啊，而是**两个循环**，时间复杂度直接变 $O(k^4)$ 了。

于是枚举 `A->B,A->C,B->A,B->C` 这四条边的边权之后，`C` 的入度算出来了，但是 `A` 的入度还差个 `C->A`，`B` 的入度还差个 `C->B`，**那么直接算啊**，因为入边权和等于出边权和，所以对于 `A,B` 而言，直接拿出来两条出边之和减一下 `B->A` 或 `A->B` 的边权不就行了。

这样处理是自然不重不漏的。

---

考虑在这个基础上直接算正解。我们已经知道了六条边的边权。

首先还需要判定一下，要最小化操作次数。

还是利用上面那个建边环的性质，然后交换两个东西就相当于把一对二元组两条边的边权减一。hint3 这里已经提示了，它是有效的交换，所以它肯定能构成最小化操作次数之一。并且时刻保证入度等于出度。

废话少点，就是把二元组每个最小值取出来，然后删掉这么多，加进答案里面，最后发现是一个边权相等的有向三元环，加上其中一个边权 \* 2 就行了。

这个显然用个 `if` 判断一下就行了。

---

到了最后我们的“特征”已经完备了，研究符合该特征的所有字符串 $T$ 的个数。

这个时候前面的那个排序就发挥它的作用了：可以方便我们的研究。

把序列分成三部分，`AA...AAA BB...BBB CC...CCC`，交换仅仅出现在这三部分之间。

我们先钦定 `A` 的前面几个换成 `B`，再后面几个换成 `C`，`B` 的前面几个换成 `A`，再后面几个换成 `C`，`C` 也是同理。这是一种方案。

显然其内部可以多重组合数，因为我每次的选择是完全自由的，所以里面是可以完全打乱的。

那么答案就是 $\binom{an}{ab,ac}\binom{bn}{ba,bc}\binom{cn}{ca,cb}$，这三个都是多重组合数。

时间复杂度 $O(n+k^4)$，因为这是 AT 的评测机，而且完完全全跑不满，就算跑满了也是稳稳过。

于是，这道花了我两个小时的题，就在五分钟的代码中轻快地结束了。

---

```cpp
#include<bits/stdc++.h>
#include<atcoder/modint>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
using MI=atcoder::modint998244353;
const I N=5e5+5;
MI fac[N],ifac[N],ans;
I k,n[3];string s;
MI C(I n,I m1,I m2){
	if(m1+m2>n)assert(0);
	return fac[n]*ifac[m1]*ifac[m2]*ifac[n-m1-m2];}
I calc(I a,I b,I c,I d,I e,I f){//这里需要注意一下，ab 是两个相对应的边权，顺序别搞错
	I u=min(a,b),v=min(c,d),w=min(e,f),s=u+v+w;
	a-=u;b-=u;c-=v;d-=v;e-=w;f-=w;
	assert(!a||!b);
	return s+2*(a+b);}//a和b二者有一个是0，所以要把两个方向都算上
I main(){
	ios::sync_with_stdio(0);cin.tie(0);
	fac[0]=ifac[0]=1;
	fo(i,1,N-1)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]/i;
	cin>>k;cin>>k;
	cin>>s;for(I i:s)if(isalpha(i))++n[i-'A'];
	fo(ab,0,min(k,n[0]))
	fo(ac,0,min(k,n[0]))if(ab+ac<=n[0])
	fo(ba,0,min(k,n[1]))
	fo(bc,0,min(k,n[1]))if(ba+bc<=n[1]){//注意枚举的范围，有讲究
		I ca=ab+ac-ba,cb=ba+bc-ab;
		if(ca+cb>n[2]||ca<0||cb<0)continue;//这里要特判一下
		if(calc(ab,ba,ac,ca,bc,cb)>k)continue;
		ans+=C(n[0],ab,ac)*C(n[1],ba,bc)*C(n[2],ca,cb);//没啥好讲的，多重组合数
	}printf("%d\n",ans.val());
	return 0;}
```

## 后记

敲题五分钟，调试半小时，还是在样例4不过的情况下卡了半小时。

原因：首先 $ab,ac,ba,bc,ca,cb$ 六个量的值域范围是在 $[0,an/bn/cn]$ 的，其次它们还需要满足 $\le k$，然后记得判断负数，然后记得最终判定可行的时候三元环要取两个方向的。

真的真的结束了。

---

## 作者：TernaryTree (赞：3)

这个太一眼了。

考虑让 $S$ 变成另一个串 $T$，计算每个相同位置上的字符到另一个不同字符的个数，即这样一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/t88ex6bl.png)

其中 $w(\text{XY})$ 表示有字符 $\text X$ 变成字符 $\text Y$。

显然 $\text{A}\to \text{B}$ 和 $\text{B}\to \text{A}$ 的个数可以通过交换互相消去，所以我们对于两条相反的边，可花费 $\min w$ 的代价同时减去 $\min w$。然后手摸几组，不难发现/证明剩下的是一定是一个边权全部相同的三元环。假设这个边权是 $k$，那么代价是 $2k$。

所以我们枚举一下 $k$ 和三个 $\min$ 即可。注意三元环的方向顺时针和逆时针都要算一遍，但是 $k=0$ 就不需要重复算。一个形如上面的图，其变成的字符串 $T$ 的方案数为

$$
\dfrac{cnt(\text A)!}{w(\text{AB})!w(\text{AC})!(cnt(\text A)-w(\text{AB}) - w(\text{AC}))!}

\times 

\dfrac{cnt(\text B)!}{w(\text{BA})!w(\text{BC})!(cnt(\text B)-w(\text{BA}) - w(\text{BC}))!}

\times 

\dfrac{cnt(\text C)!}{w(\text{CA})!w(\text{CB})!(cnt(\text C)-w(\text{CA}) - w(\text{CB}))!}
$$

预处理阶乘及逆元即可。小常数 $\Theta(k^4)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r

using namespace std;
using pii = pair<int, int>;

const int maxn = 1e6 + 10;
const int maxc = 128;
const bool multidata = 0;
const int mod = 998244353;

int n, m, ans;
char s[maxn];
int cnt[maxc];
int f[maxc][maxc];
int fac[maxn];
int ifac[maxn];

int power(int a, int b) {
	int t = 1;
	while (b) {
		if (b & 1) t = t * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return t;
}

void fake_main() {
	cin >> n >> m >> s + 1;
	for (int i = 1; i <= n; i++) cnt[s[i]]++;
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], mod - 2);
	for (int i = n - 1; ~i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	for (int k = 0; k <= cnt['A'] && k <= cnt['B'] && k <= cnt['C'] && k * 2 <= m; k++) {
		for (int c = 0; c + k <= cnt['C'] && c <= cnt['B'] && c <= m - k * 2; c++) {
			for (int b = 0; b + k <= cnt['B'] && b <= cnt['A'] && b <= m - k * 2 - c; b++) {
				for (int a = 0; a + k <= cnt['A'] && a <= cnt['C'] && a <= m - k * 2 - b - c; a++) {
					int mn = a + b + c + k * 2;
					if (mn > m) continue;
					f['A']['B'] = b + k, f['B']['C'] = c + k, f['C']['A'] = a + k;
					f['B']['A'] = b, f['C']['B'] = c, f['A']['C'] = a;
					if (f['A']['B'] + f['A']['C'] > cnt['A']) continue;
					if (f['B']['A'] + f['B']['C'] > cnt['B']) continue;
					if (f['C']['A'] + f['C']['B'] > cnt['C']) continue;
					int mul = 1;
					mul = mul * fac[cnt['A']] % mod * ifac[f['A']['B']] % mod * ifac[f['A']['C']] % mod * ifac[cnt['A'] - f['A']['B'] - f['A']['C']] % mod;
					mul = mul * fac[cnt['B']] % mod * ifac[f['B']['A']] % mod * ifac[f['B']['C']] % mod * ifac[cnt['B'] - f['B']['A'] - f['B']['C']] % mod;
					mul = mul * fac[cnt['C']] % mod * ifac[f['C']['A']] % mod * ifac[f['C']['B']] % mod * ifac[cnt['C'] - f['C']['A'] - f['C']['B']] % mod;
					ans = (ans + mul) % mod;
				}
			}
		}
	}
	for (int k = 1; k <= cnt['A'] && k <= cnt['B'] && k <= cnt['C'] && k * 2 <= m; k++) {
		for (int c = 0; c + k <= cnt['B'] && c <= cnt['C'] && c <= m - k * 2; c++) {
			for (int b = 0; b + k <= cnt['A'] && b <= cnt['B'] && b <= m - k * 2 - c; b++) {
				for (int a = 0; a + k <= cnt['C'] && a <= cnt['A'] && a <= m - k * 2 - b - c; a++) {
					int mn = a + b + c + k * 2;
					if (mn > m) continue;
					f['A']['B'] = b, f['B']['C'] = c, f['C']['A'] = a;
					f['B']['A'] = b + k, f['C']['B'] = c + k, f['A']['C'] = a + k;
					if (f['A']['B'] + f['A']['C'] > cnt['A']) continue;
					if (f['B']['A'] + f['B']['C'] > cnt['B']) continue;
					if (f['C']['A'] + f['C']['B'] > cnt['C']) continue;
					int mul = 1;
					mul = mul * fac[cnt['A']] % mod * ifac[f['A']['B']] % mod * ifac[f['A']['C']] % mod * ifac[cnt['A'] - f['A']['B'] - f['A']['C']] % mod;
					mul = mul * fac[cnt['B']] % mod * ifac[f['B']['A']] % mod * ifac[f['B']['C']] % mod * ifac[cnt['B'] - f['B']['A'] - f['B']['C']] % mod;
					mul = mul * fac[cnt['C']] % mod * ifac[f['C']['A']] % mod * ifac[f['C']['B']] % mod * ifac[cnt['C'] - f['C']['A'] - f['C']['B']] % mod;
					ans = (ans + mul) % mod;
				}
			}
		}
	}
	cout << ans << endl;
}

signed main() {
	int T;
	if (multidata) cin >> T;
	else T = 1;
	while (T--) fake_main();
	return 0;
}


```

---

## 作者：August_Light (赞：1)

# [ARC168C] Swap Characters 题解

来一篇代码可读性较好的题解。

## 题意

给你一个长度为 $n$ 的字符串 $S$，字符集为 `ABC`。定义一次操作：在 $S$ 中自由选择两个字符并交换。执行 $0 \sim k$ 次操作，求操作后不同的 $S$ 个数。

对 $998244353$ 取模。

$n \le 2.5 \times 10^5, k \le 100$。

## 思路

注意到与答案有关的只是 $S$ 中 `A`、`B`、`C` 的个数。

1. 枚举 `A` 与 `B` 交换的次数 $i$。
2. 枚举 `A` 与 `C` 交换的次数 $j$。
3. 枚举 `B` 与 `C` 交换的次数 $k$。
4. 枚举轮换 `ABC` 的次数 $t$。
5. 用多重组合数直接计算即可。

注意轮换有两种：`ABC -> BCA` 与 `ABC -> CAB`。对于 $t \ne 0$ 的情况要分别计算。

时间复杂度 $O(n + k^4)$。AT 神机可以跑过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 250000 + 5;
const ll MOD = 998244353;

ll n, m;
ll a, b, c;

ll fac[MAXN], invfac[MAXN], inv[MAXN];
void init(ll n) {
    fac[0] = 1; fac[1] = 1;
    invfac[0] = 1; invfac[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i <= n; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invfac[i] = invfac[i-1] * inv[i] % MOD;
    }
}
ll C(ll n, ll a, ll b, ll c) { // 多重组合数
    if (a < 0 || b < 0 || c < 0) return 0;
    return fac[n] * invfac[a] % MOD * invfac[b] % MOD * invfac[c] % MOD;
}

int main() { ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m; init(250000);
    for (int i = 1; i <= n; i++) {
        char ch; cin >> ch;
        if (ch == 'A') a++;
        else if (ch == 'B') b++;
        else if (ch == 'C') c++;
    }
    ll ans = 0;
    for (ll i = 0; i <= m; i++) // AB 交换的次数
        for (ll j = 0; i + j <= m; j++) // AC 交换的次数
            for (ll k = 0; i + j + k <= m; k++) // BC 交换的次数
                for (ll t = 0; i + j + k + t * 2 <= m; t++) { // ABC 轮换的次数
                    ll prod1
                    = C(a, a-i-j-t, i, j+t)
                    * C(b, i+t, b-i-k-t, k) % MOD
                    * C(c, j, k+t, c-j-k-t) % MOD;
                    ll prod2
                    = C(a, a-i-j-t, i+t, j)
                    * C(b, i, b-i-k-t, k+t) % MOD
                    * C(c, j+t, k, c-j-k-t) % MOD;
                    if (t)
                        (ans += prod1 + prod2) %= MOD;
                    else
                        (ans += prod1) %= MOD;
                }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：XYQ_102 (赞：1)

考虑假设知道一个目标字符串 $T$，如何求由最开始知道的字符串 $S$ 求得需要的最少操作次数。

令 $C_{ca,cb}$ 表示有多少个对应位置上 $S_x = ca$ 而 $T_x = cb$。每次操作可以使得 $C_{ca,cb}$ 和 $C_{cb,ca}$ 分别减 $1$。

经过一定次数的操作后，必然可以得到某一些 $C_{ca,cb}$ 为 $0$，此时的考虑  $C$ 数组有何关系。

观察一下发现，$C_{A,B} = C_{B,C} = C_{C,A}$，$C_{B,A} = C_{C,B} = C_{A,C}$。对于一对没配对的 `ABC` 可以通过 `ABC` $\to$ `ACB` $\to$ `CAB` 这样用 $2$ 次操作，让三个对应的 $C$ 分别减去 $1$。

考虑限制这个 $C$ 数组在特定情况下分别计数。

发现需要考虑的有四个自由度：
1. 前一种操作的三对 $(x,y)=(A,B),(B,C),(A,C)$ 操作分别的进行次数；
2. 后一种操作的次数。

计数部分是一个较前面内容简单的组合数相乘，具体可以看代码。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using LF = double;
using pii = pair<int, int>;
#define fir first
#define sec second
#define mk make_pair

constexpr int N = 250005, M = 105, mod = 998244353;
int n, k;
LL fac[N], inv[N], cnt[5];
string s;
LL ans;

LL Cal(LL m, LL a) {
    if (m < a) return 0;
    return fac[m] * inv[m - a] % mod * inv[a] % mod;
}

void work() {
    cin >> n >> k >> s;
    for (auto c : s)
        cnt[c - 'A']++;
    for (int i = 0; 2 * i <= k; ++i)
        for (int a = 0; a + 2 * i <= k; ++a) // ab
            for (int b = 0; b + 2 * i + a <= k && i + a + b <= cnt[0]; ++b) // ac
                for (int c = 0; a + b + c + 2 * i <= k && i + a + c <= cnt[1] && i + b + c <= cnt[2]; ++c) { // bc
                    LL mans = 1, mas = 1;
                    mans = Cal(cnt[0], i + a + b) % mod * Cal(i + a + b, i + a) % mod * Cal(cnt[2], i + b + c) % mod * Cal(i + b + c, i + b) % mod * Cal(cnt[1], i + c + a) % mod * Cal(i + a + c, i + c) % mod;
                    mas *= Cal(cnt[0], i + a + b) % mod * Cal(i + a + b, i + b) % mod * Cal(cnt[2], i + b + c) % mod * Cal(i + b + c, i + c) % mod * Cal(cnt[1], i + c + a) % mod * Cal(i + a + c, i + a) % mod;
                    ans = (ans + mas + (i == 0 ? 0 : 1) * mans) % mod;
                }
    cout << ans << endl;
}

LL fpow(LL x, int b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * x % mod;
        x = x * x % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fac[0] = 1; n = 250000;
    for (int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; ~i; --i) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
    int T = 1;
    while (T--) work();
    return 0;
}
```

---

## 作者：roBotic (赞：0)

考虑一个 naive 的问题。
>已知三种字符互相交换分别有 $ab,ac,ba,bc,ca,cb$ 个，那么得到的字符串有多少种。

显然设分别一共有 $A,B,C$ 个字符 $\mathtt{A,B,C}$，则总方案数为：

$$\binom{A}{ab}\times\binom{A-ab}{ac}\times\binom{B}{ba}\times\binom{B-ba}{bc}\times\binom{C}{ca}\times\binom{C-ca}{cb}.$$

再考虑一个 naive 的问题叫做：

> 想把字符串 $S$ 变成 $T$，对应位置三种字符的互相变化各有 $ab,ac,ba,bc,ca,cb$ 个，那么最少需要几次交换。

贪心处理，首先 $ab$ 和 $ba$ 可以每次用一次交换处理掉 $\min(ab,ba)$ 对，$ac$ 和 $ca$，$bc$ 和 $cb$ 同理。然后会发现只会剩下 $ab,bc,ca$ 或者 $cb,ba,ac$ 这三种，并且数量相等，需要每次两次交换做完。

于是我们可以枚举 $ab$ 和 $ba$，$ac$ 和 $ca$，$bc$ 和 $cb$ 互换的个数以及最后一次 $ab,bc,ca$ 或者 $cb,ba,ac$ 的个数，设这四个数分别是 $i,j,k,l$，那么总操作次数是 $i+j+k+2l$，判断是否小于等于 $K$，然后用最开始的方法组合计数即可。

[https://atcoder.jp/contests/arc168/submissions/62934840](https://atcoder.jp/contests/arc168/submissions/62934840)。

---

## 作者：madfallen (赞：0)

DoctorWang 模拟赛 T3。

用 $123$ 代替 $ABC$ 。显然对原字符串的任意排列求答案都是一样的，因此我们只记录三种字符的个数 $c_1$ , $c_2$ , $c_3$ 。

在若干次操作后，记在最初字符串中值为 $P$ ，现字符串中值为 $Q$ 的下标数为 $f(P,Q)$ ，则 

$$\forall i=1,2,3,\sum_{j=1,2,3}f(i,j)=c_i$$

于是当前操作方案的贡献可以用三个多重排列数之积得到：

$$\prod_{i=1,2,3}\frac{c_i!}{\prod_{j=1,2,3}f(i,j)!}$$

$f(i,j)$ 是容易通过操作方案得到的。将所有操作方法的贡献相加即为答案。

怎么枚举操作方法？记 `P->Q` 为向把 `P` 换到在最初字符串中为 `Q` 的位置，则操作方法有 `A->B`，`B->C`，`C->A`， `B->A`，`C->B`，`A->C` 共 $6$ 种，复杂度 $O(k^6)$，无法接受。

注意到后三种轮换可以用全排列轮换（`ABC->BCA` 或 `ABC->CAB`）加上前面三种来刻画，这样是 $O(k^4)$ 的。如开头所说我们不关心顺序，枚举这四种操作的数量即可。

实际上循环次数仅约为 $\frac{k^4}{4!}$，可以轻松跑进 100ms。

```c++
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=3e5;
const int mod=998244353;
int n,k,A,B,C;
int jc[N+5]={1},invjc[N+5]={1};
inline int ksm(int a,int b){
	int res=1;
	for(;b;b>>=1){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
	}
	return res;
}
inline int inv(int x){
	return ksm(x,mod-2);
}
inline void init(int n){
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%mod;
	for(int i=1;i<=n;i++)invjc[i]=inv(jc[i]);
}
struct arr{
	int ar[3];
	arr(){};
	arr(int ar0,int ar1,int ar2){
		this->ar[0]=ar0;
		this->ar[1]=ar1;
		this->ar[2]=ar2;
	}
};
inline int multiP(int tot,arr x){//多重排列
	return (x.ar[0]>=0)*(x.ar[1]>=0)*(x.ar[2]>=0)*jc[tot]*invjc[x.ar[0]]%mod*invjc[x.ar[1]]%mod*invjc[x.ar[2]]%mod;
}
signed main(){
	cin>>n>>k;
	init(n);
	for(int i=1;i<=n;i++){
		char S;cin>>S;
		switch(S){
			case 'A':A++;break;
			case 'B':B++;break;
			case 'C':C++;break;
		}
	}
	int wsn=0;
	for(int i=0;i<=k;i++){
		for(int j=0;i+j<=k;j++){
			for(int p=0;i+j+p<=k;p++){
				for(int q=0;i+j+p+q*2<=k;q++){
					auto aP=arr(A-i-j-q,i,j+q);//第一种全排列轮换
					auto bP=arr(i+q,B-i-p-q,p);
					auto cP=arr(j,p+q,C-j-p-q);
					wsn+=multiP(A,aP)*multiP(B,bP)%mod*multiP(C,cP)%mod;
					if(q>0){//第二种全排列轮换
						aP=arr(A-i-j-q,i+q,j);
						bP=arr(i,B-i-p-q,p+q);
						cP=arr(j+q,p,C-j-p-q);
						wsn+=multiP(A,aP)*multiP(B,bP)%mod*multiP(C,cP)%mod;
					}
					ans%=mod;
				}
			}
		}
	}
	cout<<wsn;
}
```

---

