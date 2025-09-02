# [AGC033D] Complexity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_d

**この問題のメモリ制限はいつもと異なります。注意してください。**

各マスが白か黒で塗られている長方形状のマス目に対して、 **複雑さ**  を以下のように定めます。

- すべてのマスが白、もしくはすべてのマスが黒のとき、複雑さは $ 0 $ である。
- そうでないとき、マス目のいずれかの辺に平行な直線でマス目を $ 2 $ つのマス目に分割し、それらのマス目の複雑さを $ c_1 $, $ c_2 $ とする。 分割の仕方は複数ありうるが、それらにおける $ \max(c_1,\ c_2) $ の最小値を $ m $ として、このマス目の複雑さを $ m+1 $ とする。

実際に縦 $ H $ 行、横 $ W $ 列の白黒に塗られたマス目が与えられます。 マス目の状態は $ A_{11} $ から $ A_{HW} $ の $ HW $ 個の文字で表されており、 上から $ i $ 行目、左から $ j $ 列目にあるマスが黒色のとき $ A_{ij} $ は `#`、 上から $ i $ 行目、左から $ j $ 列目にあるマスが白色のとき $ A_{ij} $ は `.` となっています。

与えられたマス目の複雑さを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ H,W\ ≦\ 185 $
- $ A_{ij} $ は `#` または `.`

### Sample Explanation 1

$ 1 $ 列目と $ 2 $ 列目の境目で $ 2 $ つのマス目に分割してみます。 $ 1 $ 列目だけからなるマス目の複雑さは $ 0 $、$ 2 $,$ 3 $ 列目からなるマス目の複雑さは $ 1 $ なので、 このマス目の複雑さは $ 2 $ 以下だと分かります。

## 样例 #1

### 输入

```
3 3
...
.##
.##```

### 输出

```
2```

## 样例 #2

### 输入

```
6 7
.####.#
#....#.
#....#.
#....#.
.####.#
#....##```

### 输出

```
4```

# 题解

## 作者：Leasier (赞：24)

首先，我们不难想到一个暴力 dp：设 $dp_{i, j, k, l}$ 表示左上角为 $(i, k)$、右下角为 $(j, l)$ 的矩形的复杂度。转移时直接分两种情况枚举分界点即可。时间复杂度为 $O(n^5)$，显然不能通过。

但此时我们注意到一个问题：答案是很小的，因为我们可以通过每次在两个维度之一上二分做到 $\leq \lceil \log_2 n \rceil + \lceil \log_2 m \rceil$ 的复杂度。

考虑**交换状态和答案**，改设 $dp_{i, j, k, l}$ 表示复杂度 $\leq i$ 时，左上角为 $(j, k)$，右上角为 $(j, l)$ 时右下角 $x$ 坐标的最大值。

初值：$dp_{0, i, j, k} = \max l$，其中左上角为 $(i, j)$、右下角为 $(l, k)$ 的矩形中所有元素颜色相同。

转移分为如下三种情况。

- 矩形 $(j, k, l)$ 复杂度 $\leq i - 1$ 时，其复杂度也一定 $\leq i$，则 $dp_{i, j, k, l} \leftarrow \max(dp_{i, j, k, l}, dp_{i - 1, j, k, l})$。
- 横着切一刀，此时我们贪心地一定会尽量从满足复杂度 $\leq i - 1$ 且最大的位置切开，则 $dp_{i, j, k, l} \leftarrow \max(dp_{i, j, k, l}, dp_{i - 1, dp_{i - 1, j, k, l} + 1, k, l})$。
- 竖着切一刀，此时我们需要枚举切点，则 $dp_{i, j, k, l} \leftarrow \max(dp_{i, j, k, l}, \displaystyle\max_{x = k}^{l - 1} \min(dp_{i - 1, j, k, x}, dp_{i - 1, j, x + 1, l}))$。

答案：$\min i$，其中 $dp_{i, 1, 1, m} = n$。

直接做的时间复杂度是 $O(nm^3 (\log n + \log m))$，看上去很不能过，但事实上它在 AT 上冲过了，最大用时不超过 3s（

但是这道题在今天的模拟赛中的数据范围达到了 $250$，这个做法过不去了……

要是我们能不枚举竖着的切点就好了！打印出切点会发现：**$i, j, k$ 不变时，$l$ 增大，切点 $x$ 单调不降**。

知道这一条性质后对切点双指针即可。时间复杂度为 $O(nm^2 (\log n + \log m))$。

证明：首先我们知道 $i, j, k$ 不变时，$l$ 增大，$dp_{i, j, k, l}$ 单调不降。

我们将 $dp_{i, j, k, x}, dp_{i, j, x + 1, l}$ 视为两个分别不降和不增的函数，当 $l$ 增大，第一个函数图像不变，但第二个函数图像下移，感性理解可知取 $\min$ 后最高点不会左移。

代码：
```cpp
#include <stdio.h>
#include <math.h>

int sum[187][187], dp[7][187][187][187];
char s[187][187];

inline int get_sum(int l1, int r1, int l2, int r2){
	return sum[r1][r2] - sum[r1][l2 - 1] - sum[l1 - 1][r2] + sum[l1 - 1][l2 - 1];
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int n, m, k;
	scanf("%d %d", &n, &m);
	k = ceil(log2(n)) + ceil(log2(m));
	for (int i = 1; i <= n; i++){
		scanf("%s", &s[i][1]);
		for (int j = 1; j <= m; j++){
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + (s[i][j] == '.' ? 1 : 0);
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			int pos = n;
			for (int x = j; x <= m; x++){
				while (pos >= i){
					int y = get_sum(i, pos, j, x);
					if (y == 0 || y == (pos - i + 1) * (x - j + 1)) break;
					pos--;
				}
				if (pos < i) break;
				dp[0][i][j][x] = pos;
			}
		}
	}
	if (dp[0][1][1][m] == n){
		printf("0");
		return 0;
	}
	for (int i = 1; i <= k; i++){
		int cur = i & 1, pre = cur ^ 1;
		for (int j = 1; j <= n; j++){
			for (int x = 1; x <= m; x++){
				int pos = x;
				for (int y = x; y <= m; y++){
					while (pos + 1 < y && min(dp[pre][j][x][pos], dp[pre][j][pos + 1][y]) <= min(dp[pre][j][x][pos + 1], dp[pre][j][pos + 2][y])) pos++;
					dp[cur][j][x][y] = max(dp[pre][j][x][y], max(dp[pre][dp[pre][j][x][y] + 1][x][y], min(dp[pre][j][x][pos], dp[pre][j][pos + 1][y])));
				}
			}
		}
		if (dp[cur][1][1][m] == n){
			printf("%d", i);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：逗逼领主 (赞：18)

一个显然的想法是设$dp[l][r][u][d]$为第$l$列至第$r$列与第$u$行至第$d$行内的矩形的复杂度. 一定跑不过, 考虑优化.

注意到答案至多为$log_2(n*m)$, 那么换一种状态, 设$dp[c][u][d][l]$为复杂度为$c$时在第$u$行与第$d$行之间从第$l$列开始向右延伸最右能延伸到第几列. 转移时分第$c$刀是横着切还是竖着切考虑.

如果是竖着切则转移显然为$dp[c][u][d][l]=dp[c-1][u][d][dp[c-1][u][d][l]+1]$.

如果横着切, 则有$dp[c][u][d][l]=max(min(dp[c][u][k][l],dp[c][k+1][d][l]))$, 其中$k\in [u,d-1]$. 然而暴力枚举转移是不行的, 注意到$(d-u)$越大时dp值越小, 那么可以二分最优的分割点使得上半边和下半边的dp值尽量接近即可.

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char ch[188][188];
int sum[188][188];
int dp[2][188][188][188];
bool eq(int x1,int y1,int x2,int y2)
{
    int siz=(x2-x1+1)*(y2-y1+1);
    int c1=sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
    return c1==siz||c1==0;
}
void init()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            sum[i][j]+=sum[i][j-1];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            sum[i][j]+=sum[i-1][j];
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
            for(int l=1,r;l<=m;l=r)
            {
                r=l;
                while(eq(i,l,j,r)&&r<=m)r++;
                for(int p=l;p<r;++p)dp[0][i][j][p]=r-1;
                if(l==r)dp[0][i][j][l]=l-1,r++;
            }
}
int find(int c,int u,int d,int L)
{
    int l=u,r=d-1,mid;
    int res=0;
    int v1,v2;
    while(l<=r)
    {
        mid=(l+r)/2;
        v1=dp[c][u][mid][L];
        v2=dp[c][mid+1][d][L];
        res=max(res,min(v1,v2));
        if(v1<v2)r=mid-1;
        else l=mid+1;
    }
    return res;
}
void DP(int c)
{
    int nv,lv;
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
            for(int l=1;l<=m;++l)
            {
                lv=dp[c^1][i][j][l];
                if(lv!=m)
                {
                    nv=dp[c^1][i][j][lv+1];
                    nv=max(nv,find(c^1,i,j,l));
                }
                else nv=m;
                dp[c][i][j][l]=nv;
            }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",ch[i]+1);
        for(int j=1;j<=m;++j)
            if(ch[i][j]=='#')sum[i][j]=1;
    }
    init();
    int ans=0;
    for(int i=1;dp[(i&1)^1][1][n][1]<m;++i) DP(i&1),ans=i;
    printf("%d\n",ans);
    return 0;
}

```



---

## 作者：小粉兔 (赞：15)

### 2019-11-22 补档

考虑一个朴素的 DP：$dp(\mathit{topleft}, \mathit{bottomright})$ 表示左上角为 $\mathit{topleft}$，右下角为 $\mathit{bottomright}$ 时这个矩形区域的权值。

状态数就是 $\mathcal O (H^2 W^2)$ 的了，考虑优化状态。

容易发现权值最大不超过 $\lceil \log_2 H \rceil + \lceil \log_2 W \rceil$，且在当 $(i + j) \bmod 2 = 0$ 时 $A_{ij}$ 为`.`否则为`#`，即黑白染色时取到上限。

那么记 $f(\mathit{complexity}, \mathit{top}, \mathit{bottom}, \mathit{left})$ 为满足 $dp(\mathit{topleft}, \mathit{bottomright}) \le \mathit{complexity}$ 的最大的 $\mathit{right}$ 值，如果不存在这样的 $\mathit{right}$ 则为 $\mathit{left} - 1$。

同理记 $g(\mathit{complexity}, \mathit{left}, \mathit{right}, \mathit{top})$ 为满足 $dp(\mathit{topleft}, b\mathit{ottomright}) \le \mathit{complexity}$ 的最大的 $\mathit{bottom}$ 值，如果不存在这样的 $\mathit{bottom}$ 则为 $\mathit{top} - 1$。

这样子就可以实现转移，具体方式是：以 $\mathit{complexity}$ 为阶段，每次从上一个阶段转移而来（可以滚动数组）。  
先考虑 $f$ 只算劈成左右两半的方案的贡献，$g$ 只算劈成上下两半的方案的贡献，这样子可以直接以 $f(\mathit{top}, \mathit{bottom}, \mathit{left}) = f'(\mathit{top}, \mathit{bottom}, f'(\mathit{top}, \mathit{bottom}, \mathit{left}) + 1)$ 的方式进行转移。$g$ 同理，最后再固定 $\mathit{topleft}$，利用双指针进行合并即可。

时间复杂度为 $\mathcal O (W H (W + H) \log WH)$，[评测链接](https://atcoder.jp/contests/agc033/submissions/8560968)。

---

## 作者：10circle (赞：9)

没想到交换 dp 一维和值域这个 trick，于是来提供暴力做法。

考虑暴力 dp：设 $f _ {l, r, u, d}$ 表示子矩阵左右边界为 $l, r$，上下边界为 $u, d$ 的混乱值。直接转移，是枚举如何切的，时间复杂度 $O(n ^ 5)$，空间复杂度 $O(n ^ 4)$。

显然时间和空间都过不去阿！

所以开始优化：

- 时间上：  
  发现转移是有单调性的：如果矩阵 $A$ 被矩阵 $B$ 完全包含，那么 $A$ 的混乱值小于等于 $B$。  
  所以转移时可以二分优化，时间复杂度变成 $O(n ^ 4 \log n)$。  
  在二分时，也有一个优化：在切开的两个矩阵混乱值相同时，此时一定取到最优，所以可以直接退出二分。
- 空间上：  
  发现左右边界是一个区间，而区间共有 $\dfrac{n(n + 1)}{2}$ 个，所以可以只记录区间，这样空间总共变成了原来的 $\dfrac{1}{4}$。  
  而且又发现答案在 `unsigned char` 范围内，于是每个 dp 值只用 $1$ 个字节了。
  总的一算：大约是 $\dfrac{185 ^ 4}{4}$ 字节，约为 280MB，在范围内。

但是这样并不能通过。几乎跑满的四次方乘老哥在五秒内跑过 $n=185$，还不是一种现代艺术。

考虑继续优化：  
不能从优化转移入手，因为它确实没法优化。  
于是，尝试减少状态！

考虑弃用递推，转而使用记忆化搜索：这样可以不计算所有无用状态。  

然后就过了。不太会说明其状态数复杂度与常数，但是实际测试能过，而且很快。

[代码](https://atcoder.jp/contests/agc033/submissions/39122845)。



---

## 作者：Alex_Wei (赞：7)

> [AT4927 [AGC033D] Complexity](https://www.luogu.com.cn/problem/AT4927)

设 $f_{i, j, k, l}$ 表示以 $(i, j)$ 为左上角，$(k, l)$ 为右下角的矩形的混乱度，直接做时空复杂度至少 $n ^ 4$，无法接受。

因为每次在矩形中间切一刀使得矩形大小减半，混乱度加 $1$，所以答案为 $\log$ 级别。进一步地，固定左边界 $j$，上边界 $i$ 和下边界 $k$，当 $l$ 向右移动时，混乱度不降。显然，若矩形 $A$ 包含矩形 $B$，则 $A$ 的混乱度不小于 $B$ 的混乱度。根据这个单调性，设 $f_{i, j, k, a}$ 表示使得混乱度不大于 $a$ 的最大的 $l$。$a$ 这一维只有 $\log$，且可以滚动数组优化掉。

初始化 $f_{i, j, k} = l$ 当且仅当对应矩形字符全部相等，且 $l + 1$ 对应矩形字符不全相等。枚举 $i, j$，随着 $k$ 递增 $l$ 不降，可以 $n ^ 3$ 预处理。

考虑横着切。枚举左边界 $j$，上边界 $i$，下边界 $k$。若再枚举切割位置 $p$，则复杂度 $n ^ 4$。但我们注意到转移形如 $f_{i, j, k} = \max\limits_{p = i} ^ {k - 1} \min(f_{i, j, p}, f_{p + 1, j, k})$，因为 $f_{i, j, p}$ 在固定 $i, j$ 时关于 $p$ 单调，$f_{p + 1, j, k}$ 在固定 $j, k$ 时关于 $p$ 单调，在固定 $p, j$ 时关于 $k$ 单调，所以当 $k$ 递增时，决策点 $p$ 单调不降。反证法结合单调性容易证明。因此不需要二分决策点，用指针维护即可。

竖着切就太简单了，枚举 $i, j, k$，则 $f_{i, f_{i, j, k} + 1, k}$ 贡献到新的 $f_{i, j, k}$。

时间复杂度 $\mathcal{O}(n ^ 3\log n)$，比题解区 $n ^ 3\log ^ 2 n$ 的做法时间复杂度更优，$n ^ 3\log n$ 但需要两个 DP 数组的做法更简洁。代码和题解略有不同。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 185 + 5;
int n, m, p[N][N], q[N][N], f[N][N][N], ff[N][N][N];
char t[N][N];
int calcp(int a, int b, int c, int d) {
  return p[c][d] - p[a - 1][d] - p[c][b - 1] + p[a - 1][b - 1];
}
int calcq(int a, int b, int c, int d) {
  return q[c][d] - q[a - 1][d] - q[c][b - 1] + q[a - 1][b - 1];
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> t[i] + 1;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + (t[i][j] == '#');
      q[i][j] = q[i - 1][j] + q[i][j - 1] - q[i - 1][j - 1] + (t[i][j] == '.');
    }
  for(int k = 1; k <= m; k++)
    for(int l = 1; l <= n; l++) {
      int bound = m;
      for(int r = l; r <= n; r++) {
        while(calcp(l, k, r, bound) && calcq(l, k, r, bound)) bound--;
        f[k][l][r] = bound;
      }
    }
  for(int i = 0; ; i++) {
    if(f[1][1][n] == m) cout << i << "\n", exit(0);
    for(int k = 1; k <= m; k++)
      for(int l = 1; l <= n; l++) {
        int p = l;
        for(int r = l; r <= n; r++) {
          auto val = [&](int p) {return min(f[k][l][p], f[k][p + 1][r]);};
          while(p + 1 < r && val(p) <= val(p + 1)) p++;
          ff[k][l][r] = max(val(p), max(f[k][l][r], f[f[k][l][r] + 1][l][r]));
        }
      }
    swap(f, ff);
  }
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/27
author: Alex_Wei
start coding at 7:05
finish debugging at 7:51
*/
```

---

## 作者：GreenDay (赞：5)

## [AGC033D] Complexity 题解

给定一个 $N$ 行 $M$ 列的字符矩阵。我们定义一个字符矩阵的凌乱度为：
- 若这个字符矩阵中所有字符都相同，则凌乱度为 0。
- 否则，则考虑所有的沿水平或者竖直方向的直线，将字符矩阵分成两个不为空的部分，设两个部分的凌乱度分别为 $a$ 和 $b$，则整个字符矩阵的凌乱度为 $\max(a,b)+1$的最小值。

请你求出，给出的字符矩阵的凌乱度是多少。

[题面](https://www.luogu.com.cn/problem/AT4927) [代码](https://atcoder.jp/contests/agc033/submissions/12933109)

$1 \leq N, M \leq 185$。

$5s +512MB$

---

首先，我们有一个非常naive的$O(N^5) \text{DP}$:设$dp_{(a,b),(c,d)}$表示处理完某个区间矩形的代价和，转移是$O(N)$的暴力。

其次，我们有一个比较naive的$O(N^4) - O(n^4 \log N)\text{DP}$，我们发现转移具有单调性，可以用二分 or 双指针优化。

看似没有办法了？

这个时候我们需要用到$DP$优化的一个小技巧，**改变状态的设定**。我们把原先dp的值压入状态，状态变为dp的值。这种做法适用于最优化类的DP，而且发现答案不大的情况。

注意到答案的范围大约是$O(logN)$的，考虑如下的构造，会使答案最大化。

```
.#.#.#.#
#.#.#.#.
.#.#.#.#
#.#.#.#.
.#.#.#.#
#.#.#.#.
.#.#.#.#
#.#.#.#.
```

同样大小的$N,M$,答案一定不会劣于上述情况，所以$ans\le \lceil  logN +logM\rceil$。


我们设$down_{ans,h,l,r}$表示如果答案是$ans$,矩形的上端在$(h,l),(h,r)$处，下端可以延伸的最大位置。

我们设$right_{ans,h,l,r}$表示如果答案是$ans$,矩形的左端在$(l,h),(r,h)$，右端可以延伸的最大位置。


所以结合说结合双指针or二分，我们可以做到$O(N^3\log N)-O(N^3 \log^2 N)$的时间复杂度。

DP数组的第一维是可以滚动数组优化，空间复杂度$O(N^3)$，可以通过。


---

## 作者：xht (赞：3)

## [Complexity](https://atcoder.jp/contests/agc033/tasks/agc033_d)

### 题意

- 给定一个 $n$ 行 $m$ 列的字符矩阵，每个位置上要么为 `.` 要么为 `#`。
- 定义一个字符矩阵的凌乱度为：
  - 若所有字符都相同，则凌乱度为 $0$。
  - 否则，考虑所有的沿水平或者竖直方向的直线，将字符矩阵分成两个不为空的部分，设两个部分的凌乱度分别为 $a$ 和 $b$，则凌乱度为 $\max(a,b)+1$ 的最小值。
- 要求给定的字符矩阵的凌乱度是多少。
- $n,m \leq 185$。

### 题解

一个显而易见的 DP 是，将每个子矩阵当作一个状态，枚举直线转移，时间复杂度 $\mathcal O(n^5)$。

注意到凌乱度的最大值是 $\mathcal O(\log n)$ 的，于是设 $f_{i,u,d,l}$ 表示 $(u,d,l)$ 的情况下凌乱度为 $i$ 的最大 $r$，同理 $g_{i,u,l,r}$ 表示 $(u,l,r)$ 的情况下凌乱度为 $i$ 的最大 $d$。

此时转移可以双指针，时间复杂度 $\mathcal O(n^3\log n)$，注意滚动数组优化空间。

### 代码

```cpp
const int N = 187;
int n, m, w;
char a[N][N];
int f[N][N][N], g[N][N][N], F[N], G[N];

int main() {
	rd(n, m);
	for (int i = 1; i <= n; i++) rds(a[i], m);
	int tn = n - 1, tm = m - 1;
	while (tn) ++w, tn >>= 1;
	while (tm) ++w, tm >>= 1;
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++) {
			f[l][r][m+1] = m;
			for (int j = m; j; j--)
				if (!(l == r || (a[l][j] == a[r][j] && f[l][r-1][j] >= j))) f[l][r][j] = j - 1;
				else f[l][r][j] = a[l][j] == a[l][j+1] ? f[l][r][j+1] : j;
		}
	for (int l = 1; l <= m; l++)
		for (int r = l; r <= m; r++) {
			g[l][r][n+1] = n;
			for (int i = n; i; i--)
				if (!(l == r || (a[i][l] == a[i][r] && g[l][r-1][i] >= i))) g[l][r][i] = i - 1;
				else g[l][r][i] = a[i][l] == a[i+1][l] ? g[l][r][i+1] : i;
		}
	if (f[1][n][1] == m) return print(0), 0;
	for (int k = 1; k <= w; k++) {
		for (int l = 1; l <= n; l++)
			for (int r = l; r <= n; r++)
				for (int j = 1; j <= m; j++)
					f[l][r][j] = f[l][r][f[l][r][j]+1];
		for (int l = 1; l <= m; l++)
			for (int r = l; r <= m; r++)
				for (int i = 1; i <= n; i++)
					g[l][r][i] = g[l][r][g[l][r][i]+1];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				for (int p = i; p <= n; p++) F[p] = f[i][p][j];
				for (int p = j; p <= m; p++) G[p] = g[j][p][i];
				F[n+1] = j - 1, G[m+1] = i - 1;
				for (int p = i; p <= n; p++)
					for (int w = F[p]; w > F[p+1]; w--)
						g[j][w][i] = max(g[j][w][i], p);
				for (int p = j; p <= m; p++)
					for (int w = G[p]; w > G[p+1]; w--)
						f[i][w][j] = max(f[i][w][j], p);
			}
		if (f[1][n][1] == m) return print(k), 0;
	}
	return 0;
}
```

---

## 作者：myee (赞：2)

### 前言

不懂，感觉这场的 C 题我反倒想了很久，而这题则一眼秒了。

说明思维能力还是不够。/fn

### 思路

设 $x\in[l,r),y\in[u,d)$ 矩阵的凌乱度为 $a_{l,r,u,d}$，容易发现 $a_{l,r,u,d}\le\lceil\log_2(r-l)\rceil+\lceil\log_2(d-u)\rceil$。

设

$$f_{v,l,u,d}=\max\{r|a_{l,r,u,d}\le v\}$$

容易发现有效的状态数只有 $O(n^2m\log(nm))$ 个。

边界的预处理是容易的，考虑转移。

则

$$f_{v+1,l,u,d}=\max\{f_{v,f_{v,l,u,d},u,d},\max_m\min\{f_{v,l,u,m},f_{v,l,m,d}\}\}$$

前一半的贡献容易计算，考虑后一部分。

注意到 $v,l$ 都是一致的，为方便描述，我们接下来使用 $f_{u,d}$ 直接表示之。

也即

$$f_{u,d}'\leftarrow\max_m\min\{f_{u,m},f_{m,d}\}$$

注意到 $f$ 具有**区间包含单调性**，于是随着 $m$ 增长，$f_{u,m}$ 递减，$f_{m,d}$ 递增。

于是这个函数是关于 $m$ 先减再增的。

容易发现，当 $u$ 确定时，对 $f_{u,d}'$ 的 dp 中谷底处 $m$ 位置随着 $d$ 的增长不减，使用双指针即可维护。

~~然而直接暴力 dp [能过](https://atcoder.jp/contests/agc033/submissions/40931667)，怎么会是呢？~~

直到某时刻 $f_{v,0,0,n}=m$ 时终止 dp 即可。

总复杂度 $O(n^3\log n)$（认为 $n,m$ 同阶）。

### Code

代码很好写。

滚动了数组所以跑得很快。

```cpp
uint Dp[205][205][205];
chr C[205][205];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n,m;scanf("%u%u",&n,&m);
    for(uint i=0;i<n;i++)scanf("%s",C[i]);
    for(uint i=m;~i;i--)for(uint l=0;l<=n;l++)for(uint r=l;r<=n;r++)
        Dp[i][l][r]=l==r?m:i;
    for(uint i=m-1;~i;i--)for(uint p=0;p<n;p++)
        Dp[i][p][p+1]=C[p][i]==C[p][i+1]?Dp[i+1][p][p+1]:i+1;
    for(uint i=m-1;~i;i--)for(uint r=2;r<=n;r++)for(uint l=r-2;~l;l--)
        if(C[l][i]==C[l+1][i])Dp[i][l][r]=std::min(Dp[i][l][l+1],Dp[i][l+1][r]);
    // for(uint i=0;i<m;i++)for(uint l=0;l<=n;l++)for(uint r=l+1;r<=n;r++)
    //     if(Dp[i][l][r]>i)printf("%u %u %u %u\n",l+1,r,i+1,Dp[i][l][r]);
    uint v=0;
    while(Dp[0][0][n]!=m){
        v++;
        for(uint l=0;l<m;l++)for(uint u=0;u<n;u++)
            for(uint d=n,p=n;d>u;d--)
            {
                if(p>=d)p=d-1;
                while(p>u&&Dp[l][u][p]<Dp[l][p][d])p--;
                Dp[l][u][d]=Dp[Dp[l][u][d]][u][d];
                _max(Dp[l][u][d],std::min(Dp[l][u][p],Dp[l][p][d]));
                _max(Dp[l][u][d],std::min(Dp[l][u][p+1],Dp[l][p+1][d]));
            }
            // for(uint d=n;d>u;d--){
            //     Dp[l][u][d]=Dp[Dp[l][u][d]][u][d];
            //     for(uint p=u+1;p<d;p++)
            //         _max(Dp[l][u][d],std::min(Dp[l][u][p],Dp[l][p][d]));
            // }
    }
    printf("%u\n",v);
    return 0;
}
```


---

## 作者：小木虫 (赞：2)

### Preface  
包含一些 trick 的 dp 好题。  
### Problem  
- 给定一个 $N$ 行 $M$ 列的字符矩阵。
- 我们定义一个字符矩阵的凌乱度为：
  - 若这个字符矩阵中所有字符都相同，则凌乱度为 $0$。
  - 否则，则考虑所有的沿水平或者竖直方向的直线，将字符矩阵分成两个不为空的部分，设两个部分的凌乱度分别为 $a$ 和 $b$，则整个字符矩阵的凌乱度为 $\max(a,b)+1$ 的最小值。
- 请你求出，给出的字符矩阵的凌乱度是多少。
- $1 \leq N, M \leq 185$。

### Solution  

看题后易得一个复杂度爆炸的四维 dp：  
$dp_{i,j,k,z}$ 记录一个矩形的左上角和右下角，dp 其最小凌乱度。  
很显然这个 dp 仅仅是状态就已经达到了 $O(n^4)$，完全无法通过此题。  

但是聪明的你一定靠着分治的思想发现了这个过程可以像二维线段树的建树过程。  
也就是先将 $n$ 行 $m$ 列的矩阵通过 $\log n$ 次的二分变为 1 行 $m$ 列的矩阵。再通过 $\log m$ 次的二分变为一个点，这样构造出的答案是 $\log n+\log m$ 的，且与矩阵内容无关，那么我们就知道对于任意矩阵，答案一定不超过这个值，这个值很小，启示了我们可以在上面做些手脚，使查询答案变为找到答案状态最小的合法状态。  

我们尝试将答案放进状态里，现在这个状态变为了：  
$$dp_{x_1,y_1,x_2,y_2,s}$$  
代表一个矩形能不能通过 $s$ 凌乱度的分割变得合法。现在这个数组的值变为只有两个值的布尔值了，然后我们现在要将状态中的一个值压进数组的值里，如果能压进去的话状态将变为 $O(n^3\log n)$ 的。  
于是我们将 $x_2$ 取出，放进数组值里，很显然在其它三个参数确定的情况下最大化 $x_2$ 是最优的，现在状态的意义就变为了在 $s$ 的凌乱度下，确定了两个上端点后最大的矩形的下边。  

在下文我们将 $x_1$ 称为 $y$，将 $s$ 称为 $x$，将 $y_1,y_2$ 称为 $l,r$。  
接下来我们考虑转移，首先是横着切的情况，我们发现按照贪心思想最优的一刀一定是切在 $l,r,dp_{x-1,y,l,r}+1$ 这条线上的。  
那么横着切的转移方程为：$dp_{x,y,l,r}=dp_{x-1,dp_{x-1,y,l,r}+1,l,r}$  
竖着切的转移就没有那么简单了，我们在朴素转移下需要枚举断点，即：  
$dp_{x,y,l,r}=\min(dp_{x-1,y,l,k},dp_{x-1,y,k+1,r}),(k<r)$  
这个柿子复杂度太高了，根据贪心，一个子矩形的最小凌乱度一定小于等于其父矩形，也就是说 $\min$ 两端不可能在 $k$ 变化时同时增大或缩小，我们现在要让 $\min$ 的两端尽量平衡，且在过程中我们知道哪边重了，这样我们可以二分优化转移，当左边大的时候 $L=mid+1$ ，反之则 $R=mid$。  

最后复杂度变为 $O(n^3\log ^2n)$，常数较小，可以通过。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200;
int n,m;char c[N][N];
int dp[25][N][N][N];
int down[N][N][N];
bool vis[25][N][N][N];
int dfs(int x,int y,int l,int r){
	if(vis[x][y][l][r])
		return dp[x][y][l][r];
	dp[x][y][l][r]=down[y][l][r];
	vis[x][y][l][r]=1;
	if(x==0)return dp[x][y][l][r];
	if(dfs(x-1,y,l,r)!=-1e9){
		if(dfs(x-1,y,l,r)==n)dp[x][y][l][r]=n;
		else dp[x][y][l][r]=
			max(dp[x][y][l][r],dfs(x-1,dfs(x-1,y,l,r)+1,l,r));
	}
	if(l==r)return dp[x][y][l][r];
	int L=l;int R=r-1;
	while(L<R){
		int mid=(L+R)/2;
		dp[x][y][l][r]=
			max(dp[x][y][l][r],min(dfs(x-1,y,l,mid),dfs(x-1,y,mid+1,r)));
		if(dfs(x-1,y,l,mid)>dfs(x-1,y,mid+1,r))
			L=mid+1;
		else R=mid;
	}
	dp[x][y][l][r]=
		max(dp[x][y][l][r],min(dfs(x-1,y,l,L),dfs(x-1,y,L+1,r)));
	return dp[x][y][l][r];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>(c[i]+1);
	for(int i=n;i>=1;i--){
		for(int l=1;l<=m;l++){
			for(int r=l;r<=m;r++){
				if(l==r||c[i][r]==c[i][r-1]){
					down[i][l][r]=i;
					if(c[i][r]==c[i+1][r])
						down[i][l][r]=max(down[i][l][r],down[i+1][l][r]);
				}	
				else{
					for(int k=r;k<=m;k++)down[i][l][k]=-1e9;
					break;
				}
			}
		}
	}
//	for(int i=n;i>=1;i--){
//		for(int l=1;l<=m;l++){
//			for(int r=l;r<=m;r++){
//				cout<<i<<" "<<l<<" "<<r<<" "<<down[i][l][r]<<endl;
//			}
//		}
//	}
	for(int i=0;i<=16;i++){
		//cout<<dfs(i,1,1,m)<<endl;
		if(dfs(i,1,1,m)==n){
			cout<<i;return 0;
		}
	}
	return 0;
}
```


---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Atcoder 题面传送门](https://atcoder.jp/contests/agc033/tasks/agc033_d) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT4927)

首先 $n^5$ 的暴力非常容易想，设 $dp_{a,b,c,d}$ 表示以 $(a,b)$ 为左上角，$(c,d)$ 为右下角的矩阵的 complexity。枚举断点转移即可，时间复杂度 $n^5$。

我们考虑优化这个 $dp$，首先比较明显的一点：这个 $dp$ 状态满足单调性，也就是说 $\forall d_1<d_2,dp_{a,b,c,d_1}\le dp_{a,b,c,d_2}$，也就是说对于某个 $dp$ 状态 $dp_{a,b,c,d}$，假设最大的满足 $dp_{a,b,c,k}<dp_{a,b,k+1,d}$ 的 $k$ 为 $r$，那么我们从行处切开的决策点 $k$ 要么为 $r$，要么为 $r+1$，这个异常好想，于是我们可以二分这个 $r$ 然后从 $r$ 和 $r+1$ 转移即可，时间复杂度 $n^4\log n$，用双针也可优化到 $n^4$。

不过仅仅进行这个优化是远远不够的，我们还需进一步优化。这一步就有亿点考验观察力了，不难发现这个答案不会太大，手玩几组数据可看出这个答案最大不过 $\log n$ 级别（当然如果硬要说理的话用二维线段树的思想也可以解释），也就是说我们 $dp$ 数组的值域最大大概在 $16$ 左右。所以我们可以很自然地想到一个类似于函数里面“交换定义域和值域”的思路：将答案放入 $dp$ 状态中。

我们重新设计 $dp$ 状态。设 $f_{x,l,r,c}$ 表示最大的 $y$ 满足 $dp_{x,y,l,r}\leq c$。转移分两种情况，横着切或者竖着切。如果我们横着切，那么我们肯定会贪心地选择最大的 $dp_{x,y,l,r}\leq c-1$ 的 $y$ 作为分割点，也就是说 $f_{x,l,r,c}\leftarrow f_{f_{x,l,r,c-1}+1,l,r,c}$。如果我们竖着切，考虑枚举断点 $k$ 并从 $k$ 与 $k+1$ 之间切开，那么 $dp_{x,y,l,r}\leq c$ 就意味着 $dp_{x,y,l,k}\leq c-1,dp_{x,y,k+1,r}\leq c-1$，故我们用 $\min(f_{x,l,k,c-1},f_{x,k+1,r,c-1})$ 更新 $f_{x,l,r,c}$。这样暴力更新还是 $n^4\log n$ 的。不过还是按照之前的套路，由 $dp$ 数组满足单调性也可推出 $f$ 数组也满足单调性，即 $\forall r_1<r_2,f_{x,l,r_1,c}\ge f_{x,l,r_2,c}$，于是我们二分断点转移即可，复杂度就降到了 $n^3\log^2n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=185;
const int MAXANS=17;
int n,m,sum[MAXN+5][MAXN+5];char s[MAXN+5][MAXN+5];
int f[MAXN+5][MAXN+5][MAXN+5][MAXANS+1];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(s[i][j]=='.');
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=j;k<=m;k++){
		int l=i,r=n,p=i-1;
		while(l<=r){
			int mid=l+r>>1,ss=sum[mid][k]-sum[mid][j-1]-sum[i-1][k]+sum[i-1][j-1];
			if(ss==0||ss==(mid-i+1)*(k-j+1)) p=mid,l=mid+1;
			else r=mid-1;
		} f[i][j][k][0]=p;
	}
	for(int p=1;p<=MAXANS;p++) for(int i=1;i<=n;i++) for(int len=1;len<=m;len++)
		for(int j1=1,j2=len;j2<=m;j1++,j2++){
			f[i][j1][j2][p]=f[i][j1][j2][p-1];
			chkmax(f[i][j1][j2][p],f[f[i][j1][j2][p-1]+1][j1][j2][p-1]);
			if(f[i][j1][j2][p]==n) continue;
			int l=j1,r=j2-1;
			while(l<=r){
				int mid=l+r>>1;
				chkmax(f[i][j1][j2][p],min(f[i][j1][mid][p-1],f[i][mid+1][j2][p-1]));
				if(f[i][j1][mid][p-1]<f[i][mid+1][j2][p-1]) r=mid-1;
				else l=mid+1;
			}
		}
	int ans=-1;
	for(int i=0;i<=MAXANS;i++) if(f[1][1][m][i]<n) chkmax(ans,i);
	printf("%d\n",ans+1);
	return 0;
}
```



---

## 作者：FjswYuzu (赞：1)

首先这个限制非常的奇怪……似乎在暗示什么。

分析一下这个答案的上界，是 $O(\log n+\log m)$ 的。构造方法是每次取中间一半，两边合并。

直接 DP 是时间是 $O(n^5)$ 的，具体为定义 $dp_{i,j,k,l}$ 表示 $(i,j),(k,l)$ 构成的矩形的最小复杂度和，很不优秀。注意到 $dp_{i,j,k,l} \leq dp_{i,j,k,l+1}$（其他维度同理），这样就可以二分变成 $O(n^4 \log n)$。

陷入困境。注意到我们可以直接枚举答案，然后只记录之前的三维，$f_{i,j,k}$ 表示 $(i,j),(k,f_{i,j,k})$ 构成的最大的矩阵，满足复杂度不大于当前枚举的复杂度 $c$。

合并的话分左右合并和上下合并。左右合并可以直接合并，上下合并的话会麻烦一点，暴力是枚举短点，可惜过不了；注意到 $f_{i,j,k} \geq f_{i,j,k+1}$，$f_{i-1,j,k} \leq f_{i,j,k}$。我们现在更新 $f_{i,j,k}$，将 $f_{i,j,i...k}$ 和 $f_{i...k,j,k}$ 看作两个函数 $f,g$，其中 $f$ 单调不增，$g$ 单调不减，实际更新的值为 $\min(f(x),g(x))$。这样就可以二分找到两个函数的交点，这个值周围的值一定是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char s[205][205];
int sum[205][205];
int f[205][205][205],g[205][205][205];
inline bool isFull(int xp,int yp,int xq,int yq)
{
	int c=sum[xq][yq]-sum[xp-1][yq]-sum[xq][yp-1]+sum[xp-1][yp-1];
	int d=(xq-xp+1)*(yq-yp+1);
	return c==d || c==0;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)	scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)	for(int j=1;j<=m;++j)	sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+int(s[i][j]=='#');
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			for(int k=i;k<=n;++k)
			{
				int p=j-1,l=j,r=m;
				while(l<=r)
				{
					int mid=(l+r)>>1;
					if(isFull(i,j,k,mid))	p=mid,l=mid+1;
					else	r=mid-1;
				}
				f[i][j][k]=p;
			}
		}
	}
	if(f[1][1][n]==m)	return puts("0")&0;
	for(int C=1;;++C)
	{
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				for(int k=i;k<=n;++k)
				{
					if(f[i][j][k]==m)	g[i][j][k]=m;
					else	g[i][j][k]=f[i][f[i][j][k]+1][k];
				}
			}
		}
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				for(int k=i;k<=n;++k)
				{
					int l=i,r=k-1;
					while(l<=r)
					{
						int mid=(l+r)>>1;
						g[i][j][k]=max(g[i][j][k],min(f[i][j][mid],f[mid+1][j][k]));
						if(f[i][j][mid]<f[mid+1][j][k])	r=mid-1;
						else	l=mid+1;
					}
				}
			}
		}
		for(int i=1;i<=n;++i)	for(int j=1;j<=m;++j)	for(int k=1;k<=n;++k)	f[i][j][k]=g[i][j][k];
		if(f[1][1][n]==m)	return printf("%d\n",C)&0;
	}
	return 0;
}
```

---

## 作者：关怀他人 (赞：0)

### AGC 033D
#### Solution
不难发现如果每次从中间分，$\log m+\log m$次就变成$1\times 1$的格子，代价是$0$，所以答案最多是$\log +\log m$。

因此可以将值放进状态中，设$dp[i][j1][j2][k]$表示左上角是$(i,j1)$，右上角是$(i,j2)$ ，用$k$的代价，往下最长能延伸到哪行。

转移的时候考虑横着切还是竖着切。
+ 横着切：$f[i][j1][j2][k]=dp [dp[i][j1][j2][k−1]+1][j1][j2][k−1]$
+ 竖着切：设$[j1,j3]$和$[j3+1,j2]$为分出的两部分，那么$dp[i][j1][j3][k−1]$和$dp[i][j3+1][j2][k−1]$的最小值是这样分的答案，那么$f[i][j1][j2][k]$即为最小值中的最大值。至此我们得出了$\mathcal O(m)$的暴力转移。
而因为dp值明显随矩阵增大而增大，所以可二分$j3$。即考虑二分找出最大的$min(dp[i][j1][j3][k−1],dp[i][j3+1][j2][k−1])$，左比右大往左，反过来则往右。

初始化出所有$k=0$的情况即可。

时间复杂度$\mathcal O(n^3\log^2 n)$，但因常数较小，能过。
#### Code
```cpp
int n,m;
int pre[MAXN][MAXN],f[MAXN][MAXN][MAXN][LOG];
char s[MAXN][MAXN];

int GetSum(int a,int b,int c,int d){
    return pre[c][d] - pre[a - 1][d] - pre[c][b - 1] + pre[a - 1][b - 1];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)
        scanf("%s",s[i] + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++)
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (s[i][j] == '.');
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            for(int k = j;k <= m;k++){
                int l = i,r = n,res = i - 1;
                while(l <= r){
                    int mid = (l + r) >> 1;
                    int t = GetSum(i,j,mid,k);
                    if(t == 0 || t == (mid - i + 1) * (k - j + 1)){
                        res = mid;
                        l = mid + 1;
                    }else
                        r = mid - 1;
                }
                f[i][j][k][0] = res;
            }
        }
    }
    int k;
    for(k = 1;f[1][1][m][k - 1] < n;k++){
        for(int len = 1;len <= m;len++){
            for(int i = 1;i <= n;i++){
                for(int j1 = 1,j2 = len;j2<= m;j1++,j2++){
                    f[i][j1][j2][k] = f[i][j1][j2][k - 1];
                    checkMax(f[i][j1][j2][k],f[f[i][j1][j2][k - 1] + 1][j1][j2][k - 1]);
                    if(f[i][j1][j2][k] == n) continue;
                    int l = j1,r = j2 - 1,res = 0;
                    while(l <= r){
                        int mid = (l + r) >> 1;
                        int x = f[i][j1][mid][k - 1],y = f[i][mid + 1][j2][k - 1];
                        checkMax(res,min(x,y));
                        if(x < y)
                            r = mid - 1;
                        else
                            l = mid + 1;
                    }
                    checkMax(f[i][j1][j2][k],res);
                }
            }
        }
    }
    printf("%d\n",k - 1);
    return 0;
}
```

---

