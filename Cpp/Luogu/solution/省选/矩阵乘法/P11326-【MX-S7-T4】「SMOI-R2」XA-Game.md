# 【MX-S7-T4】「SMOI-R2」XA-Game

## 题目背景

原题链接：<https://oier.team/problems/S7D>。

## 题目描述

Alice 和 Bob 在玩一个游戏。

初始地，有一个长度为 $n$ 的 01 序列，位置编号为 $1,2,\dots,n$。双方轮流操作，Alice 先操作。  

Alice 的操作是任意选择序列中位置相邻的两个数，将它们合并为它们的**异或值**（即 C++ 中的 `^` 操作）。  

Bob 的操作是任意选择序列中位置相邻的两个数，将它们合并为它们的**与值**（即 C++ 中的 `&` 操作）。  

游戏将持续进行，直至序列中仅剩一个数。如果最后剩下的数是 $1$，Alice 获胜；否则，Bob 获胜。

在游戏开始前，Bob 施展了 $m$ 次魔法调整初始序列，第 $i$ 次魔法将第 $a_i$ 个位置的数改为 $v_i$。

Alice 想知道，如果双方都使用最优策略，有多少种可能的**初始序列**（在 Bob 施展魔法之前）能够让她赢得游戏。由于答案可能非常大，你需要将结果对质数 $10^9 + 7$ 取模。

## 说明/提示

**【样例解释 #1】**

第一组数据中，可以让 Alice 赢的序列有 $110$、$101$、$011$ 共 $3$ 种。

第二组数据中，可以让 Alice 赢的序列有 $10100$、$11100$、$10110$、$11110$、$10001$、$11001$、$00101$、$01101$、$10011$、$11011$、$00111$、$01111$ 共 $12$ 种。

其中序列 $11100$，在 Bob 实施完魔法后变成了 $10110$。Alice 第一次操作可以合并第四个数和第五个数，序列变成 $1011$，可以发现 Bob 无论怎么操作 Alice 都会赢。

**【样例 #2】**

见附件中的 `game/game2.in` 与 `game/game2.ans`。

该组样例满足测试点 $5\sim6$ 的约束条件。

**【样例 #3】**

见附件中的 `game/game3.in` 与 `game/game3.ans`。

该组样例满足测试点 $10\sim11$ 的约束条件。

**【样例 #4】**

见附件中的 `game/game4.in` 与 `game/game4.ans`。

该组样例满足测试点 $12\sim13$ 的约束条件。

**【样例 #5】**

见附件中的 `game/game5.in` 与 `game/game5.ans`。

该组样例满足测试点 $18\sim20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\le T\le5\times 10^5$，$1\le n\le 10^{15}$，$0\le m\le n$，$\sum m \le5\times 10^5$，$1\le a_i\le n$，$a_i < a_{i + 1}$，$v_i\in\{0,1\}$。

|测试点编号|$T\le$|$n\le$|$\sum m\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$40$|$20$|$40$|无|
|$2\sim4$|$10^3$|$5\times10^2$|$5\times10^5$|A|
|$5\sim6$|$10^3$|$5\times10^2$|$5\times10^5$|B|
|$7\sim9$|$10^3$|$5\times10^2$|$5\times10^5$|C|
|$10\sim11$|$2\times 10^5$|$10^6$|$0$|无|
|$12\sim13$|$2\times 10^5$|$10^6$|$2\times10^5$|无|
|$14$|$2\times 10^3$|$10^{15}$|$0$|无|
|$15\sim16$|$2\times 10^3$|$10^{15}$|$2\times10^3$|无|
|$17$|$5\times 10^5$|$10^{15}$|$0$|无|
|$18\sim20$|$5\times 10^5$|$10^{15}$|$5\times10^5$|无|

- 特殊性质 A：$n = m$。
- 特殊性质 B：$n = m$，且 $v_i=1$。
- 特殊性质 C：$n = m$，且 $v$ 中没有相邻的两个 $0$，即 $v_i + v_{i + 1} \ne 0$。

## 样例 #1

### 输入

```
5
3 0
5 2
2 0
4 1
6 3
1 0
2 1
4 1
1234 4
52 1
110 1
520 0
999 1
114514 0```

### 输出

```
3
12
32
27109943
596672839```

# 题解

## 作者：larsr (赞：7)

现在我们观察一下 $\operatorname{xor}$ 和 $\operatorname{and}$ 的操作效果。

- $\operatorname{xor}$ ：
-  - $0\ 0\rarr 0$
-  - $0\ 1\rarr 1$
-  - $1\ 0\rarr 1$
-  - $1\ 1\rarr 0$
- $\operatorname{and}$ ：
-  - $0\ 0\rarr 0$
-  - $0\ 1\rarr 0$
-  - $1\ 0\rarr 0$
-  - $1\ 1\rarr 1$
 
可以发现一些性质：

- $\operatorname{xor}$ 操作完 $1$ 的数量只会减少 $0$ 和 $2$，也就是说 $1$ 的数量的奇偶性不变。
- 除了 $[0,0]$，$\operatorname{and}$ 操作完都会使 $1$ 的数量减少 $1$，也就是说 $1$ 的数量的奇偶性会变。

我们现在可以猜想如果每次 dalao 操作序列时都没有 $[0,0]$ 的部分，那么 dalao 的操作就变得可控了。想让这种情况成立，那么 LLL 每次操作时序列必须最多有一处连续的 $0$。如果初始时这种情况成立，那么每次这种情况都成立，因为 dalao 每次只能减少一个 $1$，最多能让 $[0,1,0]$ 变成 $[0,0]$，也就是说最多产生一处连续的 $0$。

可以知道 dalao 会操作 $\lfloor \frac{n-1}{2}\rfloor$ 次，那么初始时的 $1$ 的奇偶性要与 $\lfloor \frac{n-1}{2}\rfloor$ 不同。那么符合以下性质的 01 序列必然可以 LLL 赢：

- $1$ 的数量的奇偶性和 $\lfloor \frac{n-1}{2}\rfloor$ 不同。
- 最多有一处连续的 $0$。

证明完以上的序列成立，我们还要证明不满足以上条件的序列不成立。

如果不满足第一个条件，dalao 可以每次都减少一个 $1$。而只有序列是全 $0$ 时，dalao 才不能减少一个 $1$，但此时 LLL 已经必输了。

如果满足第一个条件不满足第二个条件，dalao 可以选择一个有一处连续的 $0$ 的时刻，选择这个连续的 $0$，其他时刻都减少一个 $1$。而只有序列是全 $0$ 时，dalao 才不能减少一个 $1$，但此时 LLL 已经必输了。

证明完以上，问题就变简单了。可以设状态 $f_{i,0/1,0/1,0/1}$ 代表有 $i$ 个数，最后一个数为 $0/1$，$1$ 的数量的奇偶性为 $0/1$，出现了 $0/1$ 处连续的 $0$，的 01 序列的数量。然后可以 $O(n)$ 递推出来，如果初始时预处理，那么可以获得 $65$ 分。

很明显可以用矩阵乘法加速，复杂度 $O((t+\sum m)V^3\log n)$，$V$ 代表矩阵边长，如果再带上线性算法可以获得 $80$ 分。

然后可以利用光速幂的思想优化到 $O((t+\sum m)V^2)$（不包括预处理），然后就可以 AC 了。

```cpp
#include<cstdio>
#include<cstring>
#define P 100000
#define N 500010
#define mod 1000000007
#define ll long long
#define zy(a,b,c) ((a)*4+(b)*2+(c))
using namespace std;
ll n, m, a[N], v[N];
struct mat
{
	ll a[8][8];
	mat operator *(mat x)
	{
		mat ans;
		memset(ans.a, 0, sizeof ans.a);
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
				for(int k = 0; k < 8; k++)
					ans[i][k] = (ans[i][k] + a[i][j] * x[j][k]) % mod;
		return ans;
	}
	ll* operator [](int x)
	{
		return a[x];
	}
};
mat a0, a1, ap, mul[P+10][3], danw;
//last number, sum of number 1 mod 2, number of [0,0]
void init()
{
	for(int i = 0; i < 8; i++)danw[i][i] = 1;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
			{
				if(i || !k)
				{
					a0[zy(i,j,k)][zy(0,j,k|(!i))] = 1;
					ap[zy(i,j,k)][zy(0,j,k|(!i))] = 1;
				}
				a1[zy(i,j,k)][zy(1,j^1,k)] = 1;
				ap[zy(i,j,k)][zy(1,j^1,k)] = 1;
			}
	for(int i = 0; i < 3; i++)
	{
		mul[0][i] = danw;
		mat x;
		if(!i)x = ap;
		else x = mul[P][i - 1];
		for(int j = 1; j <= P; j++) mul[j][i] = mul[j - 1][i] * x;
	}
}
ll f[8];
void pus(mat x)
{
	ll tmp[8];
	memset(tmp, 0, sizeof tmp);
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			tmp[j] = (tmp[j] + f[i] * x[i][j]) % mod;
	memcpy(f, tmp, sizeof f);
}
void appus(ll x)
{
	if(x % P != 0)pus(mul[x % P][0]);
	if((x / P) % P != 0)pus(mul[(x / P) % P][1]);
	if(x / P / P != 0)pus(mul[x / P / P][2]);
}
ll read()
{
	ll x = 0;
	char c = getchar();
	while(c < '0' || c > '9')c = getchar();
	while(c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
	return x;
}
void slove()
{
	n = read();
	m = read();
	memset(f, 0, sizeof f);
	f[zy(1,1,0)] = 1;
	ll ss = 1;
	for(int i = 1; i <= m; i++)
	{
		ss = ss * 2 % mod;
		a[i] = read();
		v[i] = read();
		appus(a[i] - a[i - 1] - 1);
		if(v[i] == 0)pus(a0);
		else pus(a1);
	}
	appus(n - a[m]);
	int w = (n - 1) / 2 % 2;
	ll ans = 0;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			ans = (ans + f[zy(i,w,j)]) % mod;
	printf("%lld\n", ans * ss % mod);
}
int main()
{
	init();
	int t;
	t = read();
	while(t--)slove();
	return 0;
}


```

---

## 作者：_Cheems (赞：2)

larsr 出的妙妙题。

要计数先判定。考察本题中两人操作的性质：

1. Alice 无论怎么操作，无法改变 $1$ 的数量的奇偶性。
2. Bob 操作会改变其奇偶性。但是对两个 $0$ 操作则不会改变奇偶性，有点类似于交换先后手。

当序列中不存在 $00$ 子串时，Alice 必然可以操作使得留给 Bob 的局面仍不存在 $00$ 子串（优先操作 $01$ 或 $10$，假如都是 $1$ 那也只会产生一个 $0$）。这种局面下，Bob 至多产生一个 $00$ 子串，但是 Alice 也可以将其消掉。那么 Bob 无法改变结果。

于是得出获胜充分条件：至多存在一个 $00$ 子串，且 $1$ 的数量奇偶性与 Bob 操作次数即 $\lfloor\frac{n-1}2\rfloor$ 不同。

现在证明它是必要条件：

* 假如 $1$ 数量奇偶性与其相同，Bob 维持现状不对 $00$ 操作即可，除非全是 $0$，但此时 Alice 必输。
* 否则，假如存在两个 $00$ 子串，那么 Bob 对其一操作后即可“交换先后手”，根据上一条的说明此时 Alice 必败。

对符合条件的序列计数，大力 dp 即可。$n$ 比较大，所以需要矩阵快速幂优化。但是邪恶的 larsr 还把普通快速幂卡掉了，可以借鉴光速幂的思想。最后，向量乘矩阵只需枚举一维，能有效优化常数。

单次复杂度 $O(L^2m)$，其中 $L$ 为矩阵大小，此题 $L=8$。
#### 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

#define ADD(a, b) a = (a + b) % mod 
#define LL long long
const int N = 5e5 + 5, M = 8, mod = 1e9 + 7, BAS = 1e5;
int T, m, v[N], mul, c[M];
LL n, a[N];

struct Matrix{
	int a[M][M];
	inline Matrix () {memset(a, 0, sizeof a);}
	inline Matrix operator * (const Matrix &B) const{
		Matrix C;
		for(int i = 0; i < M; ++i)
			for(int j = 0; j < M; ++j)
				for(int k = 0; k < M; ++k)
					ADD(C.a[i][j], 1ll * a[i][k] * B.a[k][j] % mod);
		return C;
	}
} I, M0, M1, M2, ANS;

inline void MUL(const Matrix &B){
	memset(c, 0, sizeof c);
	for(int j = 0; j < M; ++j)
		for(int k = 0; k < M; ++k)
			ADD(c[j], 1ll * ANS.a[0][k] * B.a[k][j] % mod);
	for(int j = 0; j < M; ++j) ANS.a[0][j] = c[j];
}

namespace VeryFastPow{
	Matrix Mul[3][BAS + 5];
	inline void init(){
		for(int i = 0; i < 3; ++i){
			Matrix MM = (!i ? M2 : Mul[i - 1][BAS]);
			Mul[i][0] = I; 
			for(int j = 1; j <= BAS; ++j) Mul[i][j] = Mul[i][j - 1] * MM; 
		}
	} 
	inline void qstp(LL k){
		if(k % BAS) MUL(Mul[0][k % BAS]);
		if((k / BAS) % BAS) MUL(Mul[1][(k / BAS) % BAS]);
		if(k / BAS / BAS) MUL(Mul[2][k / BAS / BAS]);
	}
};

inline int id(int a, int b, int c) {return a * 4 + b * 2 + c;}
inline void init(){
	for(int i = 0; i < M; ++i) I.a[i][i] = 1;
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k){
				// 0
				if(!j || i) ++M0.a[id(i, j, k)][id(0, j | (i == 0), k)];
				// 1
				++M1.a[id(i, j, k)][id(1, j, k ^ 1)];
			}
	for(int i = 0; i < M; ++i)
		for(int j = 0; j < M; ++j)
			M2.a[i][j] = M1.a[i][j] + M0.a[i][j];
}
signed main(){
	init(), VeryFastPow::init();
	
	cin >> T;
	while(T--){
		scanf("%lld%d", &n, &m), mul = 1;
		for(int i = 1; i <= m; ++i) mul = 2ll * mul % mod, scanf("%lld%d", &a[i], &v[i]);
		
		for(int i = 0; i < 8; ++i) ANS.a[0][i] = 0;
		ANS.a[0][id(1, 0, 0)] = true; 
		for(int i = 1; i <= m; ++i) VeryFastPow::qstp(a[i] - a[i - 1] - 1), MUL(v[i] ? M1 : M0);	 
		VeryFastPow::qstp(n - a[m]);
		
		int ans = 0;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				ADD(ans, ANS.a[0][id(i, j, (((n - 1) / 2) & 1) ^ 1)]);
		printf("%d\n", 1ll * ans * mul % mod);		
	}
	return 0;
}
```

---

## 作者：Corzica (赞：1)

感觉，不如 T3。

考虑一个状态最终的胜负情况。

二进制下的异或可以看做加法，我们能得到这个序列最后的加和。所以 Alice 的操作不会改变最终的答案。

Bob 的操作只有在相邻两数均为 0 的情况下不会改变，因为每一个人的操作次数固定，所以我们能够知道 Bob 操作奇数/偶数次的时候 Alice 获胜。

如果需要 Bob 操作奇数次 $(0,0)$，我们可以说这种情况下一定输。因为 Bob 可以一直不操作 $(0,0)$，而如果 Bob 不得不操作 $(0,0)$，那么此时序列全为 0，Bob 已经赢了。

考虑其他情况下，如何要让 Bob 操作偶数次 $(0,0)$，首先想到一定是操作了 0 次，否则操作1 次之后 Bob 可以直接执行上述策略。

把所有 0,1 缩成一段，Alice 能赢当且仅当序列中最多有一个长度等于 2 的 0 段，不存在长度大于 2 的零段。

我们这时可以 dp 解决，分别设上一个是什么，有没有出现过长度为 2 的 0 段和所有数的和。暴力矩阵快速幂复杂度为 $O(8^3\sum m\log n)$。

使用光速幂的思路，预处出 $1$ 到 $10^5$，$10^5 \times 1$ 到 $10^5 \times 10^5$，$10^{10} \times 1$ 到 $10^{10} \times 10^5$ 的值。可以在常数次合并下得到矩阵，复杂度为 $O(8^2\sum m+8^3 \times 10^5)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, n, m;
const int mod = 1000000007;
struct Matrix {
	int h, l, data[10][10];
	inline Matrix operator* (const Matrix& p)const {
		Matrix ans;
		ans.h = h, ans.l = p.l;
		static __int128 op;
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= p.l; j++) {
				op = 0;
				for (int k = 1; k <= l; k++) {
					op = op + data[i][k] * 1ll * p.data[k][j];
				}
				ans.data[i][j] = op % mod;
			}
		}
		return ans;
	}
};
Matrix f[100005], ff[100005], fff[100005];
Matrix ans, aans;
long long p, q;
inline void solve(long long p) {
	if (p % 100000) ans = ans * f[p % 100000];
	if ((p / 100000) % 100000) ans = ans * ff[(p / 100000) % 100000];
	if ((p / 10000000000ll)) ans = ans * fff[p / 10000000000ll];
}
inline int ksm(int p, int q) {
	int base = 1;
	while (q) {
		if (q & 1)base = base * 1ll * p % mod;
		q >>= 1;
		p = p * 1ll * p % mod;
	}
	return base;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	f[1].h = f[1].l = 8;
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				f[1].data[i * 4 + 2 * j + k + 1][1 * 4 + 2 * j + (k ^ 1) + 1]++;
				if (i == 0) {
					if (j == 0) {
						f[1].data[i * 4 + 2 * j + k + 1][2 * 1 + k + 1]++;
					}
				} else {
					f[1].data[i * 4 + 2 * j + k + 1][2 * j + k + 1]++;
				}
			}
		}
	}
	for (int i = 2; i <= 100000; i++) {
		f[i] = f[i - 1] * f[1];
	}
	ff[1] = f[100000];
	for (int i = 2; i <= 100000; i++) {
		ff[i] = ff[i - 1] * ff[1];
	}
	fff[1] = ff[100000];
	for (int i = 2; i <= 100000; i++) {
		fff[i] = fff[i - 1] * fff[1];
	}
	cin >> t;
	while (t--) {
		cin >> n >> m;
		memset(ans.data, 0, sizeof(ans.data));
		ans.h = 1, ans.l = 8;
		ans.data[1][5] = 1;
		long long lst = 0;
		for (int i = 1; i <= m; i++) {
			cin >> p >> q;
			solve(p - lst - 1);
			lst = p;
			aans = ans;
			memset(ans.data, 0, sizeof(ans.data));
			for (int j = 0; j <= 1; j++) {
				for (int u = 0; u <= 1; u++) {
					for (int v = 0; v <= 1; v++) {
						if (q) {
							ans.data[1][1 * 4 + 2 * u + (v ^ 1) + 1] = (ans.data[1][1 * 4 + 2 * u + ( v ^ 1) + 1] + aans.data[1][j * 4 + u * 2 + v + 1]) % mod;
						} else {
							if (j == 1) {
								ans.data[1][2 * u + v  + 1] = (ans.data[1][2 * u + v  + 1] + aans.data[1][j * 4 + u * 2 + v + 1]) % mod;
							} else if (u == 0) {
								ans.data[1][2 + v  + 1] = (ans.data[1][2 + v  + 1] + aans.data[1][j * 4 + u * 2 + v + 1]) % mod;
							}
						}
					}
				}
			}
		}
		solve(n - lst);
		long long cnt = 0, ct = 1 ^ (((n - 1) / 2) & 1);
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				cnt = (cnt + ans.data[1][j * 4 + 2 * k + ct + 1]) % mod;
			}
		}
		cout << cnt * 1ll * ksm(2, m) % mod << "\n";
	}
}


```

---

## 作者：dream10 (赞：1)

## Solution

首先对于一个固定的 $01$ 串进行分析 Alice 的胜利条件。

Alice 的操作不改变 $1$ 的奇偶性，Bob 的操作只有 $00$ 会改变奇偶性。而且 Bob 肯定有方法做 $00$ 以外的操作，否则是全 $0$ 串。

假设 Bob 全部都进行 $00$ 以外的操作，那么会改变 $\lfloor \frac{n-1}{2} \rfloor$ 次奇偶。而且如果 Bob 可以选择 00 的话，他必然可以决定最后的结果，所以不能让 Bob 有操作00 的机会。所以必要条件是 

- $1$ 的个数和 $\lfloor \frac{n-1}{2} \rfloor$ 奇偶性不同。
- 没有多于一次出现 00 子串。

而且这两个条件还是充要的。

然后进行 dp，$dp_{i,0/1,0/1,0/1}$ 表示前 $i$ 个数，最后一个数是 $0/1$，出现过 $00$ 的次数，$1$ 的个数的奇偶性。

然后矩阵光速幂优化。 $O((T+\sum m)8^2)$ （向量乘矩阵）

提醒下，ans 向量设初值的时候要让他结尾是 $4$，否则会多算 $00$。

```
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &a){
    #define gc getchar()
    char c;a=0;int f=1;
    while(!isdigit(c=gc))if(c=='-')f=-1;
    do a=a*10+c-'0';
    while(isdigit(c=gc));
    a*=f;
}
template<typename T>
void write(T a){
    if(a<0)putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> PII;
typedef pair<ll,int> PLI;
typedef __int128 lll;
mt19937 eg;
const int P=1000000007;
ll qpow(ll a,ll b){ll c=1;for(;b;b>>=1,a=a*a%P)if(b&1)c=c*a%P;return c;}
ll n,m;
const int MAXN=500010;
struct Node{
    ll a;int v;
}a[MAXN];
struct Vec{
    ll a[8];
    Vec(){memset(a,0,sizeof a);}
};
struct Mat{
    ll a[8][8];
    Mat(){
        memset(a,0,sizeof a);
    }
    void _1(){
        memset(a,0,sizeof a);
        for(int i=0;i<8;++i)a[i][i]=1;
    }
};
Mat operator * (Mat A,Mat B){
    Mat C;
    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j)
            for(int k=0;k<8;++k)
                C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j])%P;
    return C;
}
Vec operator * (Vec A,Mat B){
    Vec C;
    for(int j=0;j<8;++j)
        for(int k=0;k<8;++k)
            C.a[j]=(C.a[j]+A.a[k]*B.a[k][j])%P;
    return C;
}
Mat pre[4][65536];
int T;
signed main(){
    // freopen("game5.in","r",stdin);
    // freopen("game.out","w",stdout);
    eg.seed(chrono::system_clock::now().time_since_epoch().count());
    pre[0][0]._1();
    pre[0][1].a[0][2]=1;
    pre[0][1].a[0][5]=1;
    pre[0][1].a[1][3]=1;
    pre[0][1].a[1][4]=1;
    pre[0][1].a[2][7]=1;
    pre[0][1].a[3][6]=1;
    pre[0][1].a[4][0]=1;
    pre[0][1].a[4][5]=1;
    pre[0][1].a[5][1]=1;
    pre[0][1].a[5][4]=1;
    pre[0][1].a[6][2]=1;
    pre[0][1].a[6][7]=1;
    pre[0][1].a[7][3]=1;
    pre[0][1].a[7][6]=1;
    for(int i=2;i<65536;++i)pre[0][i]=pre[0][1]*pre[0][i-1];
    pre[1][0]._1();pre[1][1]=pre[0][65535]*pre[0][1];
    for(int i=2;i<65536;++i)pre[1][i]=pre[1][1]*pre[1][i-1];
    pre[2][0]._1();pre[2][1]=pre[1][65535]*pre[1][1];
    for(int i=2;i<65536;++i)pre[2][i]=pre[2][1]*pre[2][i-1];
    pre[3][0]._1();pre[3][1]=pre[2][65535]*pre[2][1];
    for(int i=2;i<65536;++i)pre[3][i]=pre[3][1]*pre[3][i-1];
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;++i)read(a[i].a),read(a[i].v);
        ll res=0;
        Vec ans;
        ans.a[4]=1;
        a[0].a=0;
        a[m+1].a=n;
        for(int i=1;i<=m+1;++i){
            ll c=a[i].a-a[i-1].a;
            ans=ans*pre[0][c&65535]*pre[1][c>>16&65535]*pre[2][c>>32&65535]*pre[3][c>>48&65535];
            if(i==m+1)continue;
            if(a[i].v==1)for(int j=0;j<4;++j)ans.a[j]=0;
            else for(int j=4;j<8;++j)ans.a[j]=0;
        }
        for(int i=0;i<8;++i)
            if((i&1)!=(((n-1)/2)&1))
                res=(res+ans.a[i])%P;
        res=res*qpow(2,m)%P;
        printf("%lld\n",res);
    }
    return 0;
}
```

---

