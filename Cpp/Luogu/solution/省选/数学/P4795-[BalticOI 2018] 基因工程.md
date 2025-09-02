# [BalticOI 2018] 基因工程

## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day2「[Genetics](https://boi18-day2-open.kattis.com/problems/boi18.genetics)」**

给定 $N$ 个长度为 $M$ 的只由 ``A``、``T``、``G`` 和 ``C`` 组成的字符串，分别编号为 $1\ldots N$，其中一个是模式串，其它 $N-1$ 个字符串与模式串都恰好有 $K$ 个字符不同，找到这个模式串。

## 说明/提示

## 限制与提示

|子任务|分值|数据范围|特殊约定|
|:----:|:--:|:------:|:------:|
|$1$   |$27$|$3\leqslant N,\,M\leqslant 100$|无|
|$2$   |$19$|$3\leqslant N,\,M\leqslant 1800$|所有字符串中只包含 ``A`` 和 ``C``|
|$3$   |$28$|$3\leqslant N,\,M\leqslant 4100$|所有字符串中只包含 ``A`` 和 ``C``|
|$4$   |$26$|$3\leqslant N,\,M\leqslant 4100$|无|


感谢 Hatsune_Miku 提供的翻译

## 样例 #1

### 输入

```
4 3 1
ACC
CCA
ACA
AAA```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4 3
CATT
CAAA
ATGA
TCTA```

### 输出

```
4
```

# 题解

## 作者：cyffff (赞：7)

### P4795 基因工程
 [_P4795 [BalticOI 2018]基因工程_](https://www.luogu.com.cn/problem/P4795)

我们知道有朴素的 $O(n^3)$ 的暴力，我又不会正解，于是我们来~~乱搞~~。

#### 思路
既然复杂度不会优化，那就优化常数。

朴素字符串匹配是 $O(n)$ 的，于是我们用一个 $4\times 4100$ 的 $\texttt{bitset}$ 维护每个字符串，其中 $4$ 代表的是字符集大小，$4100$ 代表的是字符串长度，第 $i,j$ 个数为 $1$ 的意义是第 $j$ 位的字符为第 $i$ 种字符。

但是这样还是会 $\texttt{TLE 91pts/94pts}$。

于是我们考虑随机打乱字符串，使其期望运行次数减小。

我们使用 `random_shuffle`  随机打乱字符串顺序。

然后就过了...

时间复杂度 $O(\dfrac {n^3}{w})$。

如果你过不了，那么你需要一些评测机波动~~和玄学~~。

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m,k;
struct node{
	char a[4105];
	int id;
}a[4105];
bitset<4105>b[4110][5];
inline int change(char ch){
	switch(ch){
		 case 'A': return 1;
		 case 'T': return 2;
		 case 'G': return 3;
		 case 'C': return 4;
	}
}
inline void read(char *a){
	char ch=getchar();
	while(ch<'A'||ch>'Z') ch=getchar();
	int len=0;
	while(ch>='A'&&ch<='Z') a[++len]=ch,ch=getchar();
}
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		read(a[i].a);
		a[i].id=i;
	}
	random_shuffle(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][change(a[i].a[j])].set(j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				int s=0;
				for(int p=1;p<=4;p++){
					s+=(b[i][p]&b[j][p]).count();
				}
				if(s+k!=m) goto nxt;
			}
		}
		printf("%d",a[i].id);
		return 0;
		nxt:;
	}
	return 0;
}
```
再见 $qwq$~

---

## 作者：Hatsune_Miku (赞：6)

### Genetics

### 基因工程


**翻译自 [BalticOI 2018 Day 2 题解](https://boi2018.progolymp.se/spoiler-day2.pdf)**

**感谢 rqy 与 zzq 等 dalao 的大力帮助，才能有下面比较通顺的翻译。**

这个问题有一个简单的三次方复杂度做法，还有一个优美的基于随机化的二次方解法（原文： ``probabilistic quadratic solution``）。我们将在稍后描述这个算法。

我们先从二进制字符集的情况开始。这种情况下，我们可以让数学更优美一些：我们把两个字母 ``A`` 和 ``C`` 看作数字 $1$ 和 $-1$。「计算两个字符串 $a$ 和 $b$ 之间的不同程度」这个问题与「给一个矩阵 $A$ 的两行做点值乘法」同构，即对于 $j=1\ldots M$，计算 $A_{i,\,j}\cdot A_{i',\,j}$ 的和（为了降低常数 — 我们令和式等于 $K'=M-2K$ 而不是 $K$）。

> （译者：如果不能理解括号里的内容，请参考下面的原文。）
> > (up to some constant factor and linear rescaling — instead of wanting sums to equal $K$, we want them to equal $K' = M = 2K$)

现在我们想要做的是检查对于所有满足 $b=a_{i'\neq i}$ 的行的点乘值是否为 $K'$。我们不需要针对所有的 $b$ 逐一进行计算，而是立即与其它行对比这个和的值。这有几种不同的实现，一个优美的方法是，为每一行选择一个随机的值 $w_i$，然后检查 $A\cdot(\sum_{i'}w_{i'}A_{i'})$ 与 $(\sum_{i'}w_{i'}-w_i)\cdot K'$ 是否相等（其中 $i$ 是我们正在检查的一行）。

> （译者：如果不能理解「检查 Foo 与 Bar 是否相等」，请参考下面的原文。）
> > ... and then check that the dot product against the combined sum $\sum_{i'}w_{i'}A_{i'}$ equals $(\sum_{i'}w_{i'}-w_i)\cdot K'$ (where $i$ is the row we're checking).

用稍微具象一点的数学术语来讲，并且推广到更大的字符集，我们在每一行中随机选取 $w_i$，然后对于每一列 $j$ 中的字母 $c\in\{A,\,C,\,G,\,T\}$，令 $D_c$ 表示第 $j$ 列中每行字母为 $c$ 的 $w_i$ 之和。接下来我们可以通过计算和式 $\sum_j\sum_{d\neq A_{i,\,j}}D_d$ 来依次比较第 $a_i$ 行与其它各行。如果这一行是答案，因为这一行与如第 $A_{i'}$ 行的其它各行恰好有 $K$ 个字符不同，所以这个式子就等于其它各行 $w_{i'}$ 的和式的 $K$ 倍。

如果这一行不是答案，和式很有可能不等于那个值。将一行中的任何一个 $w$ 修改为不同的值都会改变和式的值，如果我们将答案对 $2^{64}$ 取模，则出错的概率约为 $2^{-50}$。因此这个算法将以非常接近 100% 的概率通过测试。

有趣的一些东西：

 1. 要生成这题的测试数据非常麻烦。针对应该被卡掉的暴力，我们希望**几乎所有** 的行之间都有不为 $K$ 个的字符不同，但是要有一行恰好与所有其它各行有恰好 $K$ 个字符不同。出题人知道的唯一的恰好有相同个数元素不相同的矩阵有：单位矩阵 （其中 $N=M,\,K=2$）、常数矩阵（其中 $K=0$） 和广义 Hadmard 矩阵（其中 $N=M,\, K=N(1-1/A)$），以及它们三者的结合。其中 $A$ 表示 $|\Sigma|$。对于二进制字符集，Hadmard 矩阵被定义为一个大小为 $N\times M(N=M)$ 的 $0-1$ 矩阵，其中所有各行恰有 $N/2$ 个元素不同。对这种矩阵的研究已经十分深入，并且构造这个矩阵的一种简单的方法是递归：从矩阵
$$H=[1]$$
开始，重复地用
$$\begin{bmatrix}H&H\\H&H\oplus1\\\end{bmatrix}$$
替换掉 $H$。其中 $H\oplus1$ 表示 $H$ 的所有元素都异或 $1$。这会产生一个大小为 $2$ 的整数次幂的 Hadamard 矩阵。

 对于 $|\Sigma| = 4$ 我们可以做一些更复杂的工作，将 $H$ 用
$$\begin{bmatrix}H&H&H&H\\H&H\oplus1&H\oplus2&H\oplus3\\H&H\oplus2&H\oplus3&H\oplus1\\H&H\oplus3&H\oplus1&H\oplus2\\\end{bmatrix}$$
替代。

 对这个矩阵会产生正确的矩阵的证明留给读者作为练习（这个构造来自 $GF(4)$ 的乘法表，要求有较高的数学素养）。

 给定一个行与行之间都有 $K$ 个字符不同的矩阵，我们可以采用多种方式对矩阵进行一些扰动，以使答案唯一，例如复制矩阵的某些行或改变矩阵的一些二进制位。

 这些复杂的构造过程部分解释了限制部分 — 难以构造字符集大小不为 $2$ 的整数次幂的 Hadmard 矩阵。

 2. 存在一个复杂度低于 $O(n^3)$ 的解法：由于矩阵元素的取值集合为 $\{-1,\,1\}$，我们可以简单地计算 $A\cdot A^T$，然后从中寻找值为 $K$ 的元素，矩阵乘法在理论上可以在 $O(n^{2.373})$ 的时间复杂度内完成计算，虽然实现起来有些麻烦，并且常数巨大。


---

## 作者：Purslane (赞：5)

## Solution

新奇解法 .

给一个很直观的方法 : 对于每一个串 , 计算和它同位置不同的情况一共有多少种 , 记为 $x$ . 若 $x = k \times (n-1)$ 那么成立 .

显然这可以被 hack 掉 . 因为很有可能这不同的情况并不是每个串分 $k$ 个 . What should I do ?

随机 ! 给每个串随机赋一个权值 . 把所有东西加权就可以 .

看代码实现 :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4100+10;
int n,m,k,tot,w[MAXN],sum[MAXN][4];
map<char,int> mp={{'A',0},{'T',1},{'G',2},{'C',3}};
int Rand(void) {
	return rand()*1ll*rand();
}
string S[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	ffor(i,1,n) w[i]=Rand(),tot+=w[i];
	ffor(i,1,n) {
		cin>>S[i];S[i]='$'+S[i];
		ffor(j,1,m) ffor(k,0,3) if(mp[S[i][j]]!=k) sum[j][k]+=w[i];
	}
	ffor(i,1,n) {
		int ans=0;
		ffor(j,1,m) ans+=sum[j][mp[S[i][j]]];
		if(ans==(tot-w[i])*k) {cout<<i;break;}
	}
	return 0;
}

```


由于用了 STL , 开 O2 才能过 .

上面的这个 `sum[i][j]` 表示第 $i$ 列 , 字符不是 $j$ 的权值和 .

如果这份代码挂了 ( 毕竟是随机 ) 怎么办 ? 

你可以 :

- 跑 N 遍 . 显然这样还出错的概率几乎为 0 .

- 泰然处之 . 不就几个点吗 ! 有这运气让你家长买彩票中个大奖 , 你也不用学 OI 了 ( 不必为这个情况纠结 .

---

## 作者：Day_Dreamer_H (赞：4)

# P4795 题解
## 题目大意
讲的很清楚了，$n$ 个串里面有一个模式串，和其他所有的都恰好有 $k$ 个字母不同，求模式串编号（从 $1$ 到 $n$）。
## 思路
很快啊，啪的一下就是一份暴力，不过显然不行，是 $O(n^3)$ 的。

看了看数据范围，差不多 $O(n^2)$ 的样子。

就是说我们要在常数复杂度内求出两个字符串之间有多少个字符不一样咯。

有点像哈希的感觉？

那我们给第 $i$ 字符串附上一个随机值 $w_i$，然后定义一个数组 $d_{i,j}$ 表示第 $j$ 列有几个串是第 $i$ 种颜色，把它们的 $w$ 全部加起来。

这样有什么用捏？

你想想，如果一个串 $i$ 和另一个串 $j$ 的颜色有 $k$ 个不一样，那么就会加上 $k$ 次的 $w_j$。

那么对于一个串 $j$ 和所有串都有 $k$ 个不一样，岂不是 $k\times\sum\limits_{i\neq j}w_i$？

噫！好了！我会了！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k;
string s[4105];
long long w[4105];
long long sum;
long long d[4][4105];
mt19937 rng(1919810);
int h(char x){
	if(x == 'A')return 0;
	else if(x == 'T')return 1;
	else if(x == 'C')return 2;
	else if(x == 'G')return 3;
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&k);
	for(int i = 0;i<n;i++){
		cin>>s[i];
		w[i] = rng();
		sum+=w[i];
	}
	for(int i = 0;i<=3;i++){
		for(int j = 0;j<m;j++){
			for(int k = 0;k<n;k++){
				if(i!=h(s[k][j]))continue;
				d[i][j]+=w[k];
			}
		}
	}
	for(int i = 0;i<n;i++){
		long long cur = 0;
		for(int j = 0;j<m;j++){
			for(int k = 0;k<=3;k++){
				if(k == h(s[i][j]))continue;
				cur+=d[k][j];
			}
		}
		if(k*(sum-w[i]) == cur){
			cout<<i+1;
			return 0;
		}
	}
}
//A = 0,T = 1,C = 2,G = 3
```

---

## 作者：strcmp (赞：3)

多校联考原题。

给一个复杂度正确的类星战 Sum Hash 做法，$\Theta(nm)$。

设 $f_{i,\,j}$ 代表 $i$ 字符串和 $j$ 字符串有多少个位置不同。将 $i$ 位置字符是 $c$ 的串都塞进 $g_{c,\,i}$ 里面。

于是就是将所有 $g_{c,\,i}$ 内的 $f_{x,\,y}$ 互相减 $1$。最后查对于 $x$ 是不是 $f_{x,\,y}$ 都是 $n - k$ 就好了。

当然复杂度是错的，$f$ 的总和是 $n^2m$ 级别的，暴力减少肯定不对。

发现对于某一个 $x \in g_{c,\,i}$，$x$ 相当于要减去一个 $y \in g_{i,\,c}$ 的贡献。不难想到对于每个位置随机一个权值 $w_i$，先求出 $s \gets \sum w$，并令 $g_{c,\,i}$ 为集合内 $w$ 的总和。

注意到字符集很小，暴力枚举 $i$ 和对于 $x$ 串来说，$i$ 位置上那个跟 $s_i$ 不同的字符 $c$ 是什么，则令 $h \leftarrow h + g_{c,\,i}$。检查是否 $(s - w_i) \times k = h$ 即可。

然后你发现这个暴力枚举也没有什么必要，维护 $i$ 位置的总和就能复杂度消去 $|\Sigma|$ 了。

时间复杂度 $\Theta(nm)$，复杂度正确容易通过，而且字符集很大的时候这个做法也是可行的，扩展性很高，代码也极其好写。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
using ull = unsigned long long int;
constexpr ll inf = 1e11;
constexpr int maxn = 5e3 + 10, mx = 1e9, mod = 998244353; 
mt19937_64 rd(114514);
char s[maxn][maxn]; int n, m, k;
inline int id(char c) { return c == 'A' ? 0 : c == 'T' ? 1 : c == 'G' ? 2 : c == 'C' ? 3 : 4; }
char t[6] = { 'A', 'T', 'G', 'C' };
ull w[maxn], g[maxn], sum, f[4][maxn];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	rep(i, 1, n) scanf("%s", s[i] + 1), sum += (w[i] = rd());
	rep(i, 1, n) rep(j, 1, m) f[id(s[i][j])][j] += w[i], g[j] += w[i];
	rep(i, 1, n) {
		ull d = 0;
		rep(j, 1, m) d += g[j] - f[id(s[i][j])][j];
		if ((sum - w[i]) * k == d) printf("%d\n", i), exit(0);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路

不难想到 $O(N^2M)$ 的算法。

枚举每个字符串，并判断其是否合法即可。

然后这种复杂度显然超标的算法就能获得 `70` 分的好成绩。

考虑优化这个过程。

可以发现如果一个字符串合法，则所有字符串总共不同的位置个数之和一定为 $(N-1)\times K$。

在每个 $1$ 到 $M$ 位置上开个桶记录每个字符出现的次数，之后的每个位置与其不同的位置个数的答案就是 $N$ 减去与这一项字符相同的的串的个数。

然后还是 `TLE` 个一个点，拿了 `97` 分。

由于答案只有一个，所以可以在找到答案时跳出，于是想到随机化数列。

可以使有 `C++` 中的 `random_shuffle`。

这样跑得非常快，所有点均可以在一秒内跑过。

[AC 记录](https://www.luogu.com.cn/record/189213718)。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4105;
struct T
{
	int w;
	string s;
}s[N];
int cnt[N][4];
int get(char x)//得到字符x在数字中的映射
{
	if(x=='A')return 0;
	if(x=='T')return 1;
	if(x=='G')return 2;
	return 3;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i].s;
		s[i].w=i;
		for(int j=0;j<m;j++)
			cnt[j][get(s[i].s[j])]++;//计数
	}
	random_shuffle(s+1,s+n+1);
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=0;j<m;j++)
			for(int p=0;p<4;p++)//其实可以直接用(n-cnt[get(s[i].s[j])])的
				if(p!=get(s[i].s[j]))
					sum+=cnt[j][p];
		if(sum!=(n-1)*k)continue;
		bool flag=1;
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			int cnt=0;
			for(int p=0;p<m;p++)
				cnt+=s[i].s[p]!=s[j].s[p];//暴力
			if(cnt!=k)
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
		    cout<<s[i].w<<'\n';
		    return 0;//跳出
		}
	}
	return 0;
}
```

---

## 作者：LJ07 (赞：1)

做的很快乐。

首先一眼的随机化。肯定枚举每个串，关键在于如何快速而不失正确性的判断。

# 做法1

我们首先就有一个很显然的 $O(\frac{n^3}{w})$ 的做法。考虑给每个串搞出 $4$ 个 bitset。分别表示该位是否为 ```A``` 或 ```G``` 或 ```C``` 或 ```T```。简单异或即可。

可惜数据范围大了点。进行一个简单的随机打乱序列即可轻松拿到 $94$ 分。没通过一是因为非了点，二是因为字符集大小太小很容易卡掉。

复杂度最坏 $O(\frac{n^3}{w})$。

```cpp
const char ch[] = "ATGC";

int n, m, k, seq[N + 5];
char s[N + 5];
bitset<N> b[N + 5][4];
bool ok[N + 5];

int main()
{
	srand(time(NULL));
	rd(n, m, k);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		seq[i] = i;
		for (int j = 0; j < m; ++j) {
			for (int o = 0; o < 4; ++o) {
				b[i][o][j] = s[j] == ch[o];
			}
		}
	}
	random_shuffle(seq + 1, seq + 1 + n);
	
	for (int i = 1; i <= n; ++i) {
		if (ok[seq[i]]) {
			continue;
		}
		for (int j = 1; j <= n; ++j) {
			if (i == j) {
				continue;
			}
			int res = 0;
			for (int o = 0; o < 4; ++o) {
				res += (b[seq[i]][o] ^ b[seq[j]][o]).count();
			}
			if ((res >> 1) != k) {
				ok[seq[i]] = ok[seq[j]] = true;
				break;
			}
		}
		if (!ok[seq[i]]) {
			printf("%d\n", seq[i]);
			return 0;
		}
	}
    return 0;
}
```

# 做法2

想一下它的必要条件。发现差异的和是很容易统计的。

是不是一定有差异的和为 $(n-1)k$。

但是这也是很容易卡掉的。怎么办？随机分成 $B$ 组，每组分别判断。$B=30$ 即可通过此题。

复杂度 $O(Bn^2)$。$B$ 当然越大越正确性越高。

还有一种方法是随机赋权，不再赘述。

```cpp
const char ch[] = "ATGC";

int n, m, k, sz[T + 5], cnt[T + 5][N + 5][4], b[N + 5];
int str[N + 5][N + 5];
char s[N + 5];
bool ok[N + 5];

int main()
{
	srand(time(NULL));
	rd(n, m, k);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		b[i] = rand() % T;
		++sz[b[i]];
		for (int j = 0; j < m; ++j) {
			for (int o = 0; o < 4; ++o) {
				if (ch[o] == s[j]) {
					++cnt[b[i]][j][o];
					str[i][j] = o;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		bool flag = true;
		for (int o = 0; o < T; ++o) {
			int t = (m - k) * sz[o];
			if (b[i] == o) {
				t += k;
			}
			for (int j = 0; j < m; ++j) {
				t -= cnt[o][j][str[i][j]];
			}
			if (t) {
				flag = false;
				break;
			}
		}
		if (flag) {
			printf("%d\n", i);
			return 0;
		}
	}
    return 0;
}
```

---

## 作者：_3Zinc_ (赞：1)

题目传送门：[Click](https://www.luogu.com.cn/problem/P4795)。

墙裂推荐在[这里](https://www.cnblogs.com/TimelessWelkinBlog/p/17606860.html)看。

蒟蒻看见这道题，想了足足一个小时，过后顿有所悟，故作此篇。

首先，看到题目，光是数据就已经达到了 $\operatorname{O}(nm)$ 的级别，再看一看数据范围：$3 \leq n,m \leq 4,100$。显然是一道时间复杂度为 $\operatorname{O}(n,m)$ 级别的题目。

本蒟蒻首先观察了样例一，统计了每一列每种字符的出现次数：

```cpp
4 3 1
ACC
CCA
ACA
AAA
```

第一列有三个 `A` 和一个 `C`。第二列有三个 `C` 与一个 `A`。第三列有三个 `A` 与一个 `C`。

接着统计了一下答案即模式串，发现其第一个字符 `A` 出现 3 次，与其不同的只有一个字符串；第二个字符 `C` 出现 3 次，与其不同的只有一个字符串；第三个字符 `A` 出现 4 次，与其不同的只有一个字符串。

将所有与该串不同的字符串个数加起来，发现 $1+1+1$ 刚好为 $k \cdot (n-1)$，即每个非模式串与模式串不同的字符数乘上触模式串以外的字符串个数。

于是乎，第一份[代码](https://www.luogu.com.cn/record/119034221)产生了：[前往剪贴板](https://www.luogu.com.cn/paste/t9ebfdmd)

（喜提 $79 pts$）

为什么错了？（数据这么水，居然有 $79 pts$？）

来模拟一下样例二……发现输出 $1$！为什么？

稍微想一下，发现因为第 $2$ 个字符串和第 $1$ 个字符串有两个字符重复，在统计时，这两个字符会被认为是 $2,3$ 两串与 $1$ 相通的部分。总之，就是 $2$ 号字符串与 $3$ 号字符串，因为与 $1$ 号字符串相同的字符贡献都为 $1$ ，导致无法区分是 $2$ 号字符串与 $1$ 号字符串有两个字符相同，还是分别与 $1$ 号有一个字符相同。

怎么解决？很简单，只要让每个字符串的字符贡献不同，即取一个随机数，就可以区分这些情况。举个栗子，$2$ 号字符串贡献为 $1$，$3$ 号字符串贡献为 $2$，那么 $2$ 号字符串的两个字符与 $1$ 号字符串相同会有 $2$ 的贡献；而一个字符与 $2$ 号相同，另一个与 $3$ 相同，就会有 $3$ 的贡献。这样，就把几种情况区分开来了。

改进后的[代码](https://www.luogu.com.cn/record/119031909)：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MaxN=4105;
char s[MaxN][MaxN];
mt19937 rnd(998244353);
int n,m,k,opt[128];
typedef long long ll;
ll cnt[MaxN][4],w[MaxN],sum;

int main() {
	opt['A']=0,opt['G']=1,opt['T']=2,opt['C']=3;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) {
		scanf("%s",s[i]+1),w[i]=rnd();
		for(int j=1;j<=m;j++) cnt[j][opt[s[i][j]]]+=w[i];
		sum+=w[i];
	}
	for(int i=1;i<=n;i++) {
		ll res=0;
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++) {
				if(opt[s[i][j]]==k) continue;
				res+=cnt[j][k];
			}
		if(res==(sum-w[i])*k) {
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
```

这里使用了 `C++11` 里的随机数 `mt19937`，借鉴于[神犇的题解](https://www.luogu.com.cn/blog/Day-dreame/solution-p4795)。

~~这样，有成功地水了一篇题解。~~

---

