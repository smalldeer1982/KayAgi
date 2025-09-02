# [ABC264F] Monochromatic Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc264/tasks/abc264_f

各マスが白または黒で塗られた $ H $ 行 $ W $ 列のグリッドがあります。 $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす整数の組 $ (i,\ j) $ について、 グリッドの上から $ i $ 行目、左から $ j $ 行目のマス（以下、単にマス $ (i,\ j) $ と呼ぶ）の色は $ A_{i,\ j} $ で表されます。 $ A_{i,\ j}\ =\ 0 $ のときマス $ (i,\ j) $ は白色、$ A_{i,\ j}\ =\ 1 $ のときマス $ (i,\ j) $ は黒色です。

「下記の $ 2 $ つの操作のどちらかを行うこと」を好きなだけ（ $ 0 $ 回でも良い）繰り返すことができます。

- $ 1\ \leq\ i\ \leq\ H $ を満たす整数を選び、$ R_i $ 円払った後、グリッドの上から $ i $ 行目にあるそれぞれのマスの色を反転させる（白色のマスは黒色に、黒色のマスは白色に塗り替える）。
- $ 1\ \leq\ j\ \leq\ W $ を満たす整数を選び、$ C_j $ 円払った後、グリッドの左から $ j $ 列目にあるそれぞれのマスの色を反転させる。

下記の条件を満たすようにするためにかかる合計費用の最小値を出力して下さい。

- マス $ (1,\ 1) $ から「現在いるマスの右隣もしくは下隣のマスに移動する」 ことを繰り返してマス $ (H,\ W) $ まで移動する経路であって、通るマス（マス $ (1,\ 1) $ とマス $ (H,\ W) $ も含む）の色がすべて同じであるようなものが存在する。

本問題の制約下において、有限回の操作によって上記の条件を満たすようにすることが可能であることが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 2000 $
- $ 1\ \leq\ R_i\ \leq\ 10^9 $
- $ 1\ \leq\ C_j\ \leq\ 10^9 $
- $ A_{i,\ j}\ \in\ \lbrace\ 0,\ 1\rbrace $
- 入力はすべて整数

### Sample Explanation 1

白色のマスを `0` 、黒色のマスを `1` で表します。 初期状態のグリッドに対し、$ R_2\ =\ 3 $ 円払って上から $ 2 $ 行目にあるそれぞれのマスを反転させると、 ``` 0100 0100 1010 ``` となります。さらに、$ C_2\ =\ 6 $ 円払って左から $ 2 $ 列目にあるそれぞれのマスを反転させると、 ``` 0000 0000 1110 ``` となり、マス $ (1,\ 1) $ からマス $ (3,\ 4) $ への移動経路であって通るマスの色がすべて同じであるようなものが存在する状態になります（例えば $ (1,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (2,\ 4)\ \rightarrow\ (3,\ 4) $ という経路）。 かかった合計費用は $ 3+6\ =\ 9 $ 円であり、このときが考えられる中で最小です。

## 样例 #1

### 输入

```
3 4
4 3 5
2 6 7 4
0100
1011
1010```

### 输出

```
9```

## 样例 #2

### 输入

```
15 20
29 27 79 27 30 4 93 89 44 88 70 75 96 3 78
39 97 12 53 62 32 38 84 49 93 53 26 13 25 2 76 32 42 34 18
01011100110000001111
10101111100010011000
11011000011010001010
00010100011111010100
11111001101010001011
01111001100101011100
10010000001110101110
01001011100100101000
11001000100101011000
01110000111011100101
00111110111110011111
10101111111011101101
11000011000111111001
00011101011110001101
01010000000001000000```

### 输出

```
125```

# 题解

## 作者：allenchoi (赞：6)

### 题意：  
你有一个 $n$ 行 $m$ 列的 $01$ 矩阵 $A$ ，你可以用 $a_i$ 的代价把第 $i$ 行“反转”，也可以用 $b_j$ 的代价把第 $j$ 列“反转”。以任意顺序进行任意次操作，使得最后有一条从 $(1,1)$ 到 $(n,m)$ 的最短路径，且这条路径上都是 $0$ 或都是 $1$ 。其中，“反转”指将这一行或这一列中的 $0$ 全部改为 $1$ ， $1$ 全部改为 $0$ 。  
### 科技：
大炮（DP）  
### 思路：  
很明显，一次操作等同于将这一行或这一列异或 $1$ ，于是就有两个性质：  
相同的操作用任何顺序都是等价的；  
一种操作实际上最多能做一次。  
于是我们可以在走到一半时考虑所处的一行或一列是否“反转”。  
设 $dp_{i,j,x,y}(x,y\in[0,1])$ ，表示走到了 $(i,j)$ ，行是否“反转”，列是否“反转”。  
考虑转移：  
如果是从 $(i - 1,j)$ 转移，则处于同一列，所以 $y$ 是一样的，至于 $x$ 取 $0$ 还是 $1$ ，需要看两次操作后 $A_{i,j}$ 与 $A_{i - 1,j}$ 是否相等。  
同理，如果是从 $(i,j - 1)$ 转移，在同一行，则 $x$ 不变， $y$ 的值根据情况而定。  
于是转移式就出来力：  
$dp_{i,j,x,y} = min(dp_{i - 1,j,x',y} + a_i \times x,dp_{i,j - 1,x,y'} + b_j \times y)$  
最后答案在 $dp_{n,m,0,0},dp_{n,m,0,1},dp_{n,m,1,0},dp_{n,m,1,1}$ 中取最小值。  
注意特殊处理第一行和第一列即可 AC 。  
### 代码：  
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
long long INF = 1e17;
int n,m,a[2010],b[2010],A[2010][2010];
long long dp[2010][2010][2][2];
char ch; 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for(int i = 1;i <= m;i++) scanf("%d",&b[i]);
	for(int i = 1;i <= n;i++)
	{
		scanf("\n");
		for(int j = 1;j <= m;j++)
		{
			scanf("%c",&ch);
			A[i][j] = ch - '0';
			dp[i][j][0][0] = dp[i][j][0][1] = dp[i][j][1][0] = dp[i][j][1][1] = INF;
		}
	}
	dp[1][1][0][0] = 0,dp[1][1][1][0] = a[1],dp[1][1][0][1] = b[1],dp[1][1][1][1] = a[1] + b[1];
	for(int j = 2;j <= m;j++)
		for(int x = 0;x <= 1;x++)
			for(int y = 0;y <= 1;y++)
				if((A[1][j] ^ x ^ y) == (A[1][j - 1] ^ x)) dp[1][j][x][y] = dp[1][j - 1][x][0] + b[j] * y;
				else dp[1][j][x][y] = dp[1][j - 1][x][1] + b[j] * y;
	for(int i = 2;i <= n;i++)
		for(int x = 0;x <= 1;x++)
			for(int y = 0;y <= 1;y++)
				if((A[i][1] ^ x ^ y) == (A[i - 1][1] ^ y)) dp[i][1][x][y] = dp[i - 1][1][0][y] + a[i] * x;
				else dp[i][1][x][y] = dp[i - 1][1][1][y] + a[i] * x;
	for(int i = 2;i <= n;i++)
		for(int j = 2;j <= m;j++)
			for(int x = 0;x <= 1;x++)
				for(int y = 0;y <= 1;y++)
				{
					if((A[i][j] ^ x ^ y) == (A[i][j - 1] ^ x)) dp[i][j][x][y] = min(dp[i][j][x][y],dp[i][j - 1][x][0] + b[j] * y);
					else dp[i][j][x][y] = min(dp[i][j][x][y],dp[i][j - 1][x][1] + b[j] * y);
					if((A[i][j] ^ x ^ y) == (A[i - 1][j] ^ y)) dp[i][j][x][y] = min(dp[i][j][x][y],dp[i - 1][j][0][y] + a[i] * x);
					else dp[i][j][x][y] = min(dp[i][j][x][y],dp[i - 1][j][1][y] + a[i] * x);
				}
	printf("%lld\n",min(min(dp[n][m][0][0],dp[n][m][0][1]),min(dp[n][m][1][0],dp[n][m][1][1])));
	return 0;
}
```

---

## 作者：KazamaRuri (赞：4)

## 题意

在 $n\times m$ （$1 \leq n,m \leq 2000$）的网格图中，每个格子有 $0,1$ 两种，有两种操作：

- 将第 $i$ 行元素全部异或 $1$，花费 $r_i$ 代价。
- 将第 $j$ 列元素全部异或 $1$，花费 $c_j$ 代价。

进行若干次上述操作后，使得图中存在一条从 $(1, 1)$ 到 $(n, m)$ 的路径（只能向下或向右走），路径上的颜色相同。

求最小代价。

## 分析

很典的 dp 题。

容易发现同一行或列做了两次反转操作就等于没做，又由于是先做操作再走，那每行每列只有做与不做两种可能，做更多次肯定不是最优的。

考虑把行列的修改情况加到状态里进行 dp，设计状态 $f_{i,j,0/1,0/1}$，第一个 01 表示第 $i$ 行变与不变，第二个就表示列的。这样设计的好处是转移时知道，$a_{i,j}$ 变化成了什么，以此就能保证路径上的点同色，这是因为知道了行列的变化情况。转移时注意，同行内转移保证变化情况相同，因为不能变走边操作，然后同行转移看列变化没有，变化了就要加上费用，同列同理。

## 代码

轻松得到以下代码：

```cpp
#include <iostream>
#include <cstring>
#define _min(x,y) (x>y?y:x)
using namespace std;
using ll= long long;
const int N=2005;
int n,m,r[N],c[N]; ll f[N][N][2][2]; char a[N][N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",r+i);
	for(int i=1;i<=m;i++) scanf("%d",c+i);
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			f[1][1][i][j]=i*r[1]+j*c[1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i==1&&j==1) continue;
			for(int p=0;p<2;p++) for(int q=0;q<2;q++)
			for(int u=0;u<2;u++) for(int v=0;v<2;v++){
				if(q==v&&(a[i][j]^p)==(a[i-1][j]^u))
					f[i][j][p][q]=_min(f[i][j][p][q],f[i-1][j][u][v]+p*r[i]);
				if(p==u&&(a[i][j]^q)==(a[i][j-1]^v))
					f[i][j][p][q]=_min(f[i][j][p][q],f[i][j-1][u][v]+q*c[j]);
			}
		}
	ll ans=0x3f3f3f3f3f3f3f3f;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			ans=min(ans,f[n][m][i][j]);
	return !printf("%lld",ans);
}
```

---

## 作者：Tsawke (赞：3)

# [[ABC264F] Monochromatic Path](https://www.luogu.com.cn/problem/AT_abc264_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC264F)

## 题面

给定一个 $ H $ 行 $ W $ 列的 $ 01 $ 矩阵。你可以花费 $ R_i $ 将矩阵第 $ i $ 行进行 $ 01 $ 反转，可以花费 $ C_j $ 将矩阵第 $ j $ 列进行 $ 01 $ 反转。你需要最小化花费，并使得从 $ (1, 1) $ 出发，只能向右或下走到达 $ (H, W) $ 至少有一条路径满足均为 $ 0 $ 或 $ 1 $。

## Solution

首先不难想到每一行或一列最多进行一次反转操作，否则是无用的。发现只能向右或向下，则无后效性，故可以尝试 DP。

设 $ dp(i, j, 0/1, 0/1) $ 表示处理到第 $ i $ 行 $ j $ 列，第 $ i $ 行和第 $ j $ 列是否反转的最小花费。

我们设当前状态为 $ dp(i, j, x, y) $，令 $ G_{i, j} $ 表示矩阵的元素，则对于向下走的下一步的转移比较显然：
$$
\begin{aligned}
dp(i, j, x, y) \rightarrow dp(i + 1, j, 0, y) &\quad G_{i, j} \oplus x \oplus y = G_{i + 1, j} \oplus y \\
dp(i, j, x, y) + R_{i + 1} \rightarrow dp(i + 1, j, 1, y) &\quad G_{i, j} \oplus x \oplus y \neq G_{i + 1, j} \oplus y
\end{aligned}
$$
对于向右走的下一步也同理可得。

初始值即为 $ dp(1, 1, 0, 0) \leftarrow 0, dp(1, 1, 1, 0) \leftarrow R_1, dp(1, 1, 0, 1) \leftarrow C_1, dp(1, 1, 1, 1) \leftarrow R_1 + C_1 $。

最终答案即为 $ \min\{dp(H, W, x, y)\} $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int H, W;
ll R[2100], C[2100];
ll dp[2100][2100][2][2];
bitset < 2100 > G[2100];

int main(){
    H = read(), W = read();
    for(int i = 1; i <= H; ++i)R[i] = read();
    for(int i = 1; i <= W; ++i)C[i] = read();
    for(int i = 1; i <= H; ++i)
        for(int j = 1; j <= W; ++j){
            char c = getchar(); while(!isdigit(c))c = getchar();
            G[i][j] = c == '1' ? true : false;
        }
    memset(dp, 0x3f, sizeof dp);
    dp[1][1][0][0] = 0, dp[1][1][1][0] = R[1], dp[1][1][0][1] = C[1], dp[1][1][1][1] = R[1] + C[1];
    for(int i = 1; i <= H; ++i)
        for(int j = 1; j <= W; ++j)
            for(int x = 0; x <= 1; ++x)
                for(int y = 0; y <= 1; ++y){
                    if((G[i][j] ^ x ^ y )== (G[i + 1][j] ^ y))dp[i + 1][j][0][y] = min(dp[i + 1][j][0][y], dp[i][j][x][y]);
                    else dp[i + 1][j][1][y] = min(dp[i + 1][j][1][y], dp[i][j][x][y] + R[i + 1]);
                    if((G[i][j] ^ x ^ y) == (G[i][j + 1] ^ x))dp[i][j + 1][x][0] = min(dp[i][j + 1][x][0], dp[i][j][x][y]);
                    else dp[i][j + 1][x][1] = min(dp[i][j + 1][x][1], dp[i][j][x][y] + C[j + 1]);
                }
    ll ans(LONG_LONG_MAX);
    for(int x = 0; x <= 1; ++x)for(int y = 0; y <= 1; ++y)ans = min(ans, dp[H][W][x][y]);
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_03 初稿

---

## 作者：wfc284 (赞：1)

异或 $1$ 就是取反。  
定义状态 $f_{i, j, p, q}$ 表示走到 $(i, j)$ 所需的最小花费。其中，$p \in \{0,1\}$ 表示第 $i$ 行没有/有被操作过，$q \in \{0,1\}$ 表示第 $j$ 列没有/有被操作过。  
然后考虑转移，即从上方格子或左方格子转移。  
当与上方格子同色时，对于 $\forall p \in \{0,1\}, \forall q \in \{0,1\}:$
$$ f_{i,j,p,q} \gets \min(f_{i,j,p,q},f_{i-1,j,p,q} + p \cdot r_i) $$  
否则，对于 $\forall p \in \{0,1\}, \forall q \in \{0,1\}:$
$$ f_{i,j,p,q} \gets \min(f_{i,j,p,q},f_{i-1,j,\neg p ,q} + p \cdot r_i) $$  
当与左方格子同色或异色时，同理。  
（具体见代码）  
边界情况，只需 `memset` 成无穷大，再处理 $(1, 1)$ 即可。
### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
#define int long long
using namespace std;
const int N = 2e3+2;

template<class T> bool vmin(T &a, T b) { return b < a ? (a = b, true) : false; }

int n, m, r[N], c[N];
char a[N][N];
int f[N][N][2][2];	//[2][2]：横向改不改 纵向改不改

signed main() {
	cin >> n >> m;
	for(re int i = 1; i <= n; ++i) cin >> r[i];
	for(re int j = 1; j <= m; ++j) cin >> c[j];
	for(re int i = 1; i <= n; ++i)
		for(re int j = 1; j <= m; ++j) cin >> a[i][j], a[i][j] -= 48;
	
	memset(f, inf, sizeof(f));
	f[1][1][0][0] = 0, f[1][1][0][1] = c[1], f[1][1][1][0] = r[1], f[1][1][1][1] = r[1]+c[1];
	for(re int i = 1, i <= n; ++i)
		for(re int j = 1; j <= m; ++j) {
			if(i == 1 && j == 1) continue;
			if(a[i][j] == a[i-1][j]) {
				f[i][j][0][0] = f[i-1][j][0][0];
				f[i][j][0][1] = f[i-1][j][0][1];
				f[i][j][1][0] = f[i-1][j][1][0] + r[i];
				f[i][j][1][1] = f[i-1][j][1][1] + r[i];
			} 
			else {
				f[i][j][0][0] = f[i-1][j][1][0];
				f[i][j][0][1] = f[i-1][j][1][1];
				f[i][j][1][0] = f[i-1][j][0][0] + r[i];
				f[i][j][1][1] = f[i-1][j][0][1] + r[i];
			}
			
			if(a[i][j] == a[i][j-1]) {
				vmin(f[i][j][0][0], f[i][j-1][0][0]);
				vmin(f[i][j][0][1], f[i][j-1][0][1] + c[j]);
				vmin(f[i][j][1][0], f[i][j-1][1][0]);
				vmin(f[i][j][1][1], f[i][j-1][1][1] + c[j]);
			}
			else {
				vmin(f[i][j][0][0], f[i][j-1][0][1]);
				vmin(f[i][j][0][1], f[i][j-1][0][0] + c[j]);
				vmin(f[i][j][1][0], f[i][j-1][1][1]);
				vmin(f[i][j][1][1], f[i][j-1][1][0] + c[j]);
			}
		}
	cout << min({f[n][m][0][0], f[n][m][0][1], f[n][m][1][0], f[n][m][1][1]});
	return 0;
}
```

---

## 作者：cosf (赞：0)

还是挺好想的，正好和标答想到差不多一块去了。

我们令 $dp_{i, j, 0/1, 0/1}$ 表示，走到 $(i, j)$ 时，是否朝右（$1$ 朝右），是否将朝的那列或行翻转（$1$ 翻转）时的最小花费。

那么，我们需要算两次：是否将 $(1, 1)$ 翻转。

两种情况类似，这里讨论不将 $(1, 1)$ 翻转的情况。

那么，初始情况可以表述为：

$$
\begin{cases}
dp_{1, 1, 0, 0} = 0\\
dp_{1, 1, 0, 1} = r_1 + c_1\\
dp_{1, 1, 1, 0} = 0\\
dp_{1, 1, 1, 1} = r_1 + c_1\\
\end{cases}
$$

当然，为了方便写代码，我们可以构建虚拟的点 $(0, 1)$ 和 $(1, 0)$，这样可以少写几个判断边界的 `if`：

$$
\begin{cases}
dp_{0, 1, 0, 0} = 0\\
dp_{0, 1, 0, 1} = c_1\\
dp_{1, 0, 1, 0} = 0\\
dp_{1, 0, 1, 1} = r_1\\
\end{cases}
$$

转移就比较复杂了。如果 $a_{i, j} = 0$，则 $dp_{i, j, 0, 0}$ 与 $dp_{i, j, 1, 0}$ 是等价的，有：

$$
\begin{cases}
dp_{i, j, 0, 0} = dp_{i, j, 1, 0} = \min\{dp_{i - 1, j, 0, 0}, dp_{i, j - 1, 1, 0}\}\\
dp_{i, j, 0, 1} = dp_{i, j, 1, 1} = \min\{dp_{i - 1, j, 0, 1} + r_i, dp_{i, j - 1, 1, 1} + c_j\}\\
\end{cases}
$$

如果 $a_{i, j} = 1$，则 $dp_{i, j, 0, 0}$ 与 $dp_{i, j, 1, 1}$ 是等价的，有：

$$
\begin{cases}
dp_{i, j, 0, 0} = dp_{i, j, 1, 1} = \min\{dp_{i - 1, j, 0, 0} + r_i, dp_{i, j - 1, 1, 1}\}\\
dp_{i, j, 0, 1} = dp_{i, j, 1, 0} = \min\{dp_{i - 1, j, 0, 1}, dp_{i, j - 1, 1, 0} + c_j\}\\
\end{cases}
$$

答案即 $\min\{dp_{h, w, 0/1, 0/1}\}$。

状态有点多，注意不要写错。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 2005

using ll = long long;

int h, w;

string m[MAXN];

ll r[MAXN], c[MAXN];

ll dp[MAXN][MAXN][2][2]; // h, w, dir, rep

int main()
{
    cin >> h >> w;
    for (int i = 1; i <= h; i++)
    {
        cin >> r[i];
    }
    for (int i = 1; i <= w; i++)
    {
        cin >> c[i];
    }
    for (int i = 1; i <= h; i++)
    {
        cin >> m[i];
        m[i] = " " + m[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][1][0][0] = dp[1][0][1][0] = 0;
    dp[0][1][0][1] = c[1];
    dp[1][0][1][1] = r[1];
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            if (m[i][j] == '0')
            {
                dp[i][j][0][0] = dp[i][j][1][0] = min({dp[i][j][0][0], dp[i - 1][j][0][0], dp[i][j - 1][1][0]});
                dp[i][j][0][1] = dp[i][j][1][1] = min({dp[i][j][0][1], dp[i - 1][j][0][1] + r[i], dp[i][j - 1][1][1] + c[j]});
            }
            else
            {
                dp[i][j][0][0] = dp[i][j][1][1] = min({dp[i][j][0][0], dp[i - 1][j][0][0] + r[i], dp[i][j - 1][1][1]});
                dp[i][j][0][1] = dp[i][j][1][0] = min({dp[i][j][0][1], dp[i - 1][j][0][1], dp[i][j - 1][1][0] + c[j]});
            }
        }
    }
    ll res = min({dp[h][w][0][0], dp[h][w][0][1], dp[h][w][1][0], dp[h][w][1][1]});
    memset(dp, 0x3f, sizeof(dp));
    dp[0][1][0][0] = dp[1][0][1][0] = 0;
    dp[0][1][0][1] = c[1];
    dp[1][0][1][1] = r[1];
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            if (m[i][j] == '1')
            {
                dp[i][j][0][0] = dp[i][j][1][0] = min({dp[i][j][0][0], dp[i - 1][j][0][0], dp[i][j - 1][1][0]});
                dp[i][j][0][1] = dp[i][j][1][1] = min({dp[i][j][0][1], dp[i - 1][j][0][1] + r[i], dp[i][j - 1][1][1] + c[j]});
            }
            else
            {
                dp[i][j][0][0] = dp[i][j][1][1] = min({dp[i][j][0][0], dp[i - 1][j][0][0] + r[i], dp[i][j - 1][1][1]});
                dp[i][j][0][1] = dp[i][j][1][0] = min({dp[i][j][0][1], dp[i - 1][j][0][1], dp[i][j - 1][1][0] + c[j]});
            }
        }
    }
    cout << min({res, dp[h][w][0][0], dp[h][w][0][1], dp[h][w][1][0], dp[h][w][1][1]}) << endl;
    return 0;
}

```

---

## 作者：Ivan422 (赞：0)

题目大意：给出一个棋盘，定义一次操作为对一行或一列每一个格子上的数异或 $1$，一次操作有各种代价。要进行若干次操作后有一条从左上角到右下角的路径上每一个元素相等，求满足条件的最小代价。

思路：考虑动态规划。

状态设计：我们会发现对同一行和同一列操作两次其实就相当于没操作，于是就有了设置状态 $f_{i,j,k,l}$，其中 $0\leq k,l \leq 1$。含义就是格子 $a_{i,j}$ 是否在第 $i$ 行以及第 $j$ 列进行操作，保证操作完之后可以从左上角走到 $i$ 行 $j$ 列，并保存最小值。

初始化：求最小值，自然先是把数组最大化。并且先要把起点的状态初始化。即 $f_{1,1,0,0}=0$，$f_{1,1,1,0}=r_1$，$f_{1,1,0,1}=c_1$，$f_{1,1,1,1}=r_1+c_1$。

状态转移：往下走，列不变，即转移时的 $l$ 不变。接着，我们求出当前的异或结果是否满足转移，即 $a_{i,j}\oplus k \oplus l$ 是否等于 $a_{i+1,j}\oplus l$。如果等于则直接转移，取较小值即可。如果不等于就要考虑对行进行修改，加上代价再取最小值即可。

状态转移：往右走，行不变，即转移时的 $k$ 不变。同理，求出是否满足转移，即 $a_{i,j}\oplus k \oplus l$ 是否等于 $a_{i+1,j}\oplus k$。同上，如果等于则直接转移，取最小值即可。如果不等于就要考虑对行进行修改，加上代价再取最小值即可。

接着就有一个问题了，不能在移动时修改。如何解释这个问题呢？我们可以把移动看作是许多次下移和许多次右移拼接的，而这就不存在一列两次走到或一行两次走到，加上在一次下移或一次右移对应的异或操作是不能更改的，转移就没有问题了。

答案：即在第 $n$ 行第 $m$ 列时的四种答案的最小值，即在 $f_{n,m,0,0}$，$f_{n,m,1,0}$，$f_{n,m,0,1}$，$f_{n,m,1,1}$ 中取最小值即可。

注意事项：最大结果会爆 `int` 所以要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=2e3+10;
int n,m,r[N],c[N],a[N][N],f[N][N][2][2];
char ch;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>r[i];
    for(int i=1;i<=m;i++)cin>>c[i];
    for(int i=1;i<=n;i++){for(int j=1;j<=m;j++){
        cin>>ch;
        a[i][j]=ch-'0';
    }}
    memset(f,0x3f,sizeof(f));
    f[1][1][0][0]=0;f[1][1][1][0]=r[1];f[1][1][0][1]=c[1];f[1][1][1][1]=r[1]+c[1];
    for(int i=1;i<=n;i++){for(int j=1;j<=m;j++){
        for(int k=0;k<=1;k++){for(int l=0;l<=1;l++){
            if(i<n&&a[i][j]^k^l==a[i+1][j]^l)f[i+1][j][0][l]=min(f[i+1][j][0][l],f[i][j][k][l]);
            if(i<n&&a[i][j]^k^l!=a[i+1][j]^l)f[i+1][j][1][l]=min(f[i+1][j][1][l],f[i][j][k][l]+r[i+1]);
            if(j<m&&a[i][j]^k^l==a[i][j+1]^k)f[i][j+1][k][0]=min(f[i][j+1][k][0],f[i][j][k][l]);
            if(j<m&&a[i][j]^k^l!=a[i][j+1]^k)f[i][j+1][k][1]=min(f[i][j+1][k][1],f[i][j][k][l]+c[j+1]);
        }}
    }}
    cout<<min({f[n][m][0][0],f[n][m][1][0],f[n][m][0][1],f[n][m][1][1]});
    return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
若忽略操作，易知 DP。考虑操作带来的影响：

由于每次只会往右 / 下移动一格，影响当前格子颜色的操作只会有当前行 / 列的操作。故补充状态为 $dp_{i,j,a,b}$ 表示 $(1,1)\to(i,j)$，行 $i$ 是 / 否操作，列 $j$ 是 / 否操作。

转移时，只需枚举上一格的状态，判断是否可以转移，统计好花费即可。
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#include<memory.h>
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 2000;
namespace IO {
	const int bufsize = 230005;
	char gtchar()
	{
		static char buf[bufsize], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2)? EOF: *p1++;
	}
	int read()
	{
		int ret = 0;
		char ch = gtchar();
		while(!isdigit(ch)) ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		return ret;
	}
}using IO::read;
int n, m, r[maxn + 5], c[maxn + 5];
ll dp[maxn + 5][maxn + 5][2][2];
char ch, mp[maxn + 5][maxn + 5];
void chmn(ll &a, ll b) {if(b < a) a = b;}
ll min(ll &a, ll b) {return a > b? b: a;}
int main()
{
// 	freopen("path.in", "r", stdin);
// 	freopen("path.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) r[i] = read();
	for(int i = 1; i <= m; i++) c[i] = read();
	memset(dp, 0x3f, sizeof dp);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++, ch = IO::gtchar())
		{
			while(!isdigit(ch)) ch = IO::gtchar();
			mp[i][j] = ch;
			if(i == 1 && j == 1)
			{
				dp[1][1][0][0] = 0;
				dp[1][1][0][1] = c[1];
				dp[1][1][1][0] = r[1];
				dp[1][1][1][1] = r[1] + c[1];
				continue;
			}
			for(int ii = 0; ii <= 1; ii++)
			{
				for(int jj = 0; jj <= 1; jj++)
				{
					char t = mp[i][j] ^ ii ^ jj;
					if(i > 1) chmn(dp[i][j][ii][jj], dp[i - 1][j][mp[i - 1][j] ^ jj ^ t][jj] + (ii? r[i]: 0));
					if(j > 1) chmn(dp[i][j][ii][jj], dp[i][j - 1][ii][mp[i][j - 1] ^ ii ^ t] + (jj? c[j]: 0));
				}
			}
		}
	printf("%lld\n", min(dp[n][m][0][0], min(dp[n][m][0][1], min(dp[n][m][1][0], dp[n][m][1][1]))));
	return 0;
}
```

---

## 作者：mi_Y13c (赞：0)

### 算法
#### (动态规划) $O(HW)$
记 `dp[i][j][x][y]` 表示当我们走到方格 $(i,j)$ 时， 已将第 $i$ 行翻转 $x$ 次、第 $j$ 行翻转 $y$ 次的最小费用

由于走到方格 $(i,j)$ 时，可以选择翻转第 $i$ 行也可以不翻转第 $i$ 行，所以此时第 $i$ 行可以翻转 $0$ 次或 $1$ 次；类似地，此时第 $j$ 列可以翻转 $0$ 次或 $ 1$ 次

于是我们可以令 $k=2y+x$ 将行列的翻转情况进行合并

### 代码
```
#include <bits/extc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::vector;
using std::string;
using ll = long long;

inline void chmin(ll& x, ll y) { if (x > y) x = y; }

ll dp[2005][2005][4];

int main() {
    int h, w;
    cin >> h >> w;

    vector<int> r(h), c(w);
    rep(i, h) cin >> r[i];
    rep(i, w) cin >> c[i];

    vector<string> a(h);
    rep(i, h) cin >> a[i];

    const ll INF = 1e18;
    rep(i, h)rep(j, w)rep(k, 4) dp[i][j][k] = INF;
    rep(k, 4) {
        ll co = 0;
        if (k&1) co += r[0];
        if (k&2) co += c[0];
        dp[0][0][k] = co;
    }

    rep(i, h)rep(j, w)rep(k, 4) {
        int x = a[i][j]-'0';
        if (k&1) x ^= 1;
        if (k&2) x ^= 1;

        if (i+1 < h) { 
            int nk = k&2, y = a[i+1][j]-'0';
            if (k&2) y ^= 1;
            ll co = 0;
            if (x != y) co += r[i+1], nk |= 1;
            chmin(dp[i+1][j][nk], dp[i][j][k]+co);
        }
        if (j+1 < w) { 
            int nk = k&1, y = a[i][j+1]-'0';
            if (k&1) y ^= 1;
            ll co = 0;
            if (x != y) co += c[j+1], nk |= 2;
            chmin(dp[i][j+1][nk], dp[i][j][k]+co);
        }
    }

    ll ans = INF;
    rep(k, 4) chmin(ans, dp[h-1][w-1][k]);

    cout << ans << '\n';

    return 0;
}
```

---

## 作者：chengning0909 (赞：0)

# abc 264 f

## 题意

有一个 $N \times M$ 的矩阵，每个格子是黑色或者白色的。

如果 $A_{i, j} = 0$，格子 $(i, j)$ 是白色的，否则，格子 $(i, j)$ 是黑色的。

可以按顺序执行以下操作若干次：

- 选择一个整数 $i \ (1 \le i \le N)$，用 $R_i$ 的代价将第 $i$ 行的所有格子的颜色取反。

- 选择一个整数 $j \ (i \le j \le M)$，用 $C_j$ 的代价将第 $j$ 列的所有格子的颜色取反。

请求出满足以下要求的最小代价：

- 在矩阵上只能向右或者向下走。存在一条从格子 $(1, 1)$ 到格子 $(N, M)$ 的路径，使得路径上的所有格子颜色相同。

## 思路

首先，可以肯定的是，每一行或者每一列都最多只会被取反一次，如果取反两次，那么就会变回原来的样子，白白浪费了很多代价。

那么，就可以想到一种状态：$dp_{x, y, 0 / 1, 0 / 1}$ 表示走到 $(x, y)$ 且第 $x$ 行翻或不翻，第 $y$ 列翻或不翻时的最小代价。

我们可以通过异或操作得到往右走是否需要翻转下一列以及往下走是否需要翻转下一行，进行转移即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2010, M = N;

int n, m, r[N], c[M];
long long dp[N][M][2][2], ans = 9e18;
bool a[N][M];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> r[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char ch;
      cin >> ch, a[i][j] = ch - '0';
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          dp[i][j][k][l] = 9e18;
        }
      }
    }
  }
  for (int k = 0; k < 2; k++) {
    for (int l = 0; l < 2; l++) {
      dp[1][1][k][l] = k * r[1] + l * c[1];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          int z = a[i][j] ^ l ^ a[i][j + 1];
          dp[i][j + 1][k][z] = min(dp[i][j + 1][k][z], dp[i][j][k][l] + z * c[j + 1]);
          z = a[i][j] ^ k ^ a[i + 1][j];
          dp[i + 1][j][z][l] = min(dp[i + 1][j][z][l], dp[i][j][k][l] + z * r[i + 1]);
          if (i == n && j == m) {
            ans = min(ans, dp[i][j][k][l]);
          }
        }
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

