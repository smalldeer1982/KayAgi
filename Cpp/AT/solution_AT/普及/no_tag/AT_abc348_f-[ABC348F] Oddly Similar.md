# [ABC348F] Oddly Similar

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_f

$ N $ 個の長さ $ M $ の数列 $ A_1,\ A_2,\ \ldots,\ A_N $ があります。$ i $ 番目の数列は $ M $ 個の整数 $ A_{i,1},\ A_{i,2},\ \ldots,\ A_{i,M} $ で表されます。

それぞれの長さが $ M $ の数列 $ X,Y $ について、$ X_i\ =\ Y_i $ となるような $ i(1\ \leq\ i\ \leq\ M) $ の個数が奇数であるときに、$ X $ と $ Y $ は似ていると言います。

$ 1\ \leq\ i\ <\ j\ \leq\ N $ を満たす整数の組 $ (i,j) $ のうち、$ A_i $ と $ A_j $ が似ているものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ M\ \leq\ 2000 $
- $ 1\ \leq\ A_{i,j}\ \leq\ 999 $
- 入力は全て整数である。
 
### Sample Explanation 1

$ (i,j)\ =\ (1,2) $ は条件を満たします。なぜならば、$ A_{1,k}\ =\ A_{2,k} $ となるような $ k $ は $ k=1 $ の $ 1 $ 個だけだからです。 $ (i,j)\ =\ (1,3)\ ,(2,3) $ は条件を満たさないため、条件を満たす $ (i,j) $ の組は $ (1,2) $ だけです。

## 样例 #1

### 输入

```
3 3
1 2 3
1 3 4
2 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
6 5
8 27 27 10 24
27 8 2 4 5
15 27 26 17 24
27 27 27 27 27
27 7 22 11 27
19 27 27 27 27```

### 输出

```
5```

# 题解

## 作者：2huk (赞：9)

- 有 $n$ 个长度为 $m$ 的序列 $A_i$。如果两个序列 $X, Y$ 满足有奇数个 $i$ 满足 $X_i = Y_i$，那么 $X, Y$ 就是相似的。求有多少对 $(i,j )$ 满足 $1 \le i < j \le n$ 且 $A_i$ 和 $A_j$ 是相似的。
- $1 \le n, m \le 2000$，$1 \le a_{i, j} \le 999$。

直接暴力是 $\mathcal O(n^2m)$。听说卡常能过？

不难发现这个复杂度除以 $\omega = 64$ 是可以接受的，也就是提示我们用 bitset。

bitset 最后再用。先考虑怎么将数据用 bool 数组存储。

定义 bool 型的 $cnt_{j, k, i}$，若 $A_{i, j} = k$ 则 $cnt_{j, k, i} = 1$，否则 $cnt_{j, k, i} = 0$。这里 $i$ 指行，$j$ 指列，$k$ 指值。

考虑计算行 $i$ 的答案。更具体地，我们需要计算哪些行与 $i$ 是相似的。进一步地，我们定义 bool 型的 $f_j$ 表示 $A_i$ 和 $A_j$ 是否是相似的。开始计算前，所有 $f_j = 0$。

那么类似于暴力，我们需要枚举列 $j$。此时，显然我们已经明确了 $cnt_{j, a_{i, j}, i} = 1$。若我们求出了对于 $(i_1, i_2, \dots, i_p)$ 都满足 $cnt_{j, a_{i, j}, i_p} = 1$，也就是这些行的第 $j$ 列都是 $a_{i, j}$，也就是这些行与第 $i$ 行的第 $j$ 列都相同，那么这就意味着，$f_{i_1}, f_{i_2}, \dots, f_{i_p}$ 的值都会发生反转。

代码是这样的：

```cpp
const int N = 2001, M = 1000;
bool cnt[N][M][N], f[N];

for (int i = 1; i <= n; ++ i )
	for (int j = 1; j <= m; ++ j )
		cnt[j][a[i][j]][i] = 1;

for (int i = 1; i <= n; ++ i ) {
	for (int j = 1; j <= n; ++ j ) f[j] = 0;
	for (int j = 1; j <= m; ++ j )
		for (int k = 1; k <= n; ++ k ) {
			f[k] ^= cnt[j][a[i][j]][k];
			// 原写法是：if (cnt[j][a[i][j]][k]) f[k] ^= 1;
		}
	f[i] = 0;	// 显然自己和自己不能构成答案 
	for (int j = 1; j <= n; ++ j ) res += f[j];
}

printf("%d\n", res / 2);
```

这样的复杂度还是 $\mathcal O(n^2m)$ 的。但是我们就可以将其中的 bool 数组换成 bitset 加速了。具体的，可以发现对于每一个 $f_{1 \sim n}$ 和 $cnt_{j, k, 1 \sim n}$ 都是一维的 bool 数组。我们可以将这些一维数组改为 bitset。

那么中间 `for (int k = 1; k <= n; ++ k ) f[k] ^= cnt[j][a[i][j]][k];` 就可以改为 `f ^= cnt[j][a[i][j]];` 了。总复杂度降低为 $\mathcal O\left( \frac {n^2m}{\omega} \right)$。

[完整代码](https://atcoder.jp/contests/abc348/submissions/52136946)。

---

## 作者：aCssen (赞：5)

### Solution

首先按照题意，能得到一个非常简单的，$\mathcal{O}(N^2M)$ 的暴力。

发现题目的数据范围非常暧昧，于是搬上一个火车头，然后啪的一下，就过了。

### Code
仅展示核心部分：
```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```

---

## 作者：JuRuoOIer (赞：5)

# 题解 ABC348F - Oddly Similar

前排提示：本题解包括 **暴力** 和 **`bitset`** 两种做法。

### 题意

已提交翻译。

定义两个长度相同的数组 $x,y$ 是相似的，当且仅当存在奇数个 $i$ 使得 $x_i=y_i$。

给定 $n$ 个长为 $m$ 的数组 $a_1,a_2,...,a_n$，求有多少无序数对 $(i,j)$（$1 \le i,j \le n$），使得 $a_i$ 和 $a_j$ 是相似的。

数据范围：$1 \le n,m \le 2000,0 \le a_i \le 999$。

### 暴力

比完赛我偶然点开[榜一大哥](https://atcoder.jp/users/maspy)的[代码](https://atcoder.jp/contests/abc348/submissions/52084002)，然后发现了这个~~让我眼前一黑的~~东西：

```cpp
void solve() {
  LL(N, M);
  FOR(i, N) FOR(j, M) { read(A[i][j]); }
  ll ANS = 0;
  FOR(b, N) FOR(a, b) {
    int cnt = 0;
    FOR(c, M) cnt += (A[a][c] == A[b][c]);
    if (cnt % 2 == 1) ANS++;
  }
  print(ANS);
}
```

本题纯暴力，带上快读快输和 O3 优化（在开头加上 `#pragma GCC optimize(3)`）就可以跑进 $1$ 秒，但其时间复杂度其实是 $O(n^2m)$ 的。~~我的 $1882$ 表现分啊……~~

### `bitset`

但是 CCF 的老爷机肯定没有这么快，而且人家不给你开 O3，所以我们不可能止步于此。

考虑刚才的暴力：枚举两个数组，然后暴力统计其中相同的元素个数。这个东西看上去不太能优化了……

注：为了方便，接下来的内容中，
- “列”代表所有数组中的同一位置，即第 $k$ 列表示 $a_{1,k},a_{2,k},...,a_{n,k}$。
- $cnt_i$ 表示当前正在考虑 $a_j$，有多少个 $k$ 使得 $a_{i,k}=a_{j,k}$。

既然优化不了，就考虑换个暴力，但此时我们枚举每一个数组 $a_i$ 后枚举每一列，并求出这一列对其他所有 $cnt_i$ 的贡献。

但现在它还是一个 $O(n^2m)$ 的暴力，我们需要优化它。注意到我们还没用上 $0 \le a_{i,j} \le 999$ 的条件，所以我们试图用上它。

注意到我们只需要 $cnt_i$ 的**奇偶性**，所以 $+1$ 就可以看成 $\oplus1$，而一堆数进行异或就能自然而然地想到 `bitset`。具体地，
- 对于每一列 $j$ 的每个可能的数值 $k$（$0$ 到 $999$），都维护一个长度为 $n$ 的 `bitset`，其中第 $i$（从 $1$ 开始）位为 $0$ 代表 $a_{i,j}\neq k$，为 $1$ 代表 $a_{i,j}=k$。
- 每次最外层枚举到一个新的数组时，我们都维护一个长为 $n$ 的、每一位都是 $0$ 的 `bitset`，表示 $cnt_1,cnt_2,...,cnt_n$ 的奇偶性。
- 枚举到每一列时，就将这个 `bitset` 异或上我们刚才预处理出的对应的那个 `bitset`。
- 最后 `popcount` 一下并判一下当前枚举的那一行是否有贡献即可。

这样，时间复杂度就优化成了 $O\left(\dfrac{n^2m}{w}\right)$，足以通过本题。

---

## 作者：ma_niu_bi (赞：3)

### 题意

给定 $n$ 个长度为 $m$ 的序列。

定义两个序列是相似的，当且仅当两个序列中相等的元素个数为奇数。求 $n$ 个序列中，相似的序列对数。

### 思路

考虑暴力统计，时间复杂度 $O(n^2m)$ 。

发现枚举两个序列是不可优化的，考虑优化判断两个序列相似的过程。

我们只需求出两个序列中相等的元素个数，可以将两个序列对应异或，得到的异或序列中 $0$ 的个数即原序列中相等的元素个数。

看到异或可以想到使用 ```bitset``` 优化。但 ```bitset``` 只能维护 $0$ 或 $1$ 。可将每个数变为二进制，```bitset``` 维护每一位的情况，再将每一位的异或结果再或一次，即每一位异或结果都为 $0$ 才能为 $0$ 。统计最后序列中 $0$ 的个数是否为奇数即可。 

时间复杂度 $O(\frac{n^2m\log W}{w})$ 。

其中 $W$ 为序列值域，$w$ 为 ```bitset``` 常数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
int n, m, ans;
int a[N][N];
bitset <N> b[N][11]; 
bitset <N> t;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) 
        for (int j = 1; j <= m; j ++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i ++) 
        for (int j = 1; j <= m; j ++) 
            for (int k = 0; k <= 10; k ++)
                b[i][k][j] = a[i][j] >> k & 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            t = b[i][0] ^ b[j][0];
            for (int k = 1; k <= 10; k ++) 
                t |= b[i][k] ^ b[j][k];
            if ((m - t.count()) & 1) ans ++;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Magus (赞：3)

## 前言

你说得对，但是官解是暴力。

## 题意

称一个长度相同的数列是相似的，当且仅当存在奇数个 $i$ 使得  $x_i = y_i$。

现在给定 $n$ 个长度为 $m$ 的数列 $A_1,A_2,\cdots,A_n$，求有多少对数列是相似的。

## 题解

数据范围 $1 \leq n,m \leq 2000$，暴力复杂度 $O(n^2m)$。

实际上根本没有 $8 \times 10^9$，因为 $i<j$ 所以最多跑 $4 \times 10^9$，由于时限两秒所以一秒只用跑 $2 \times 10^9$，常数极小的情况下我们可以选择相信 AT 神机，实在不行那就开个  `O3` 吧。

于是我们暴力。

因为 $A_{i,j}$ 是大于 $0$ 的，所以将 $cnt$ 初始赋为 $0$，然后枚举每一个数列里的元素，如果是奇数次返回就是 $1$，反之为 $0$，最后将每一次枚举两个数列得到的结果累加即可。

（$⊕$ 是异或符号，在 `C++` 里写作 `^`。$a⊕b$ 的意思就是，如果 $a,b$ 两个值不相同，则异或结果为 $1$。如果 $a,b$ 两个值相同，异或结果为 $0$。）

## Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int maxn=2e3+10;
int n,m,cnt,ans,arr[maxn][maxn];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>arr[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cnt=0;
			for(int k=1;k<=m;k++)
			{
				cnt^=(arr[i][k]==arr[j][k]);
			}
			ans+=cnt;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：2)

难绷，F 题玩的就是个暴力。

$O(n^2m)$ 的做法很好想吧，暴力枚举每一位，再枚举每一对，记录相同位的数量，再累加答案即可。

很明显，$O(n^2m)$ 不能一秒内过掉，但是换个语言呢？譬如 `C++ 20 (Clang 16.0.6)`。

代码来自官方题解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)

int main(void){
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    short A[M][N];
    rep(i,N) rep(j,M) cin >> A[j][i];
    bool cnt[N][N];
    rep(i,N) rep(j,N) cnt[i][j]=false;
    rep(i,M){
        rep(j,N) for(int k=j+1;k<N;k++) cnt[j][k]^=(A[i][j]==A[i][k]);
    }
    int ans=0;
    rep(i,N) for(int j=i+1;j<N;j++) ans+=cnt[i][j];
    cout << ans << endl;
}
```

比我使用的 `bitset` 都快。

---

## 作者：cancan123456 (赞：1)

笑点解析：[$O(n^2m)$ 的算法可以直接通过此题](https://atcoder.jp/contests/abc348/editorial/9752)，且用时为我代码的约 $\dfrac13$。

简单 bitset 应用题。

考虑枚举 $i$, 对于每个 $i$ 计算与 $A_i$ 相似的 $A_k$ 的个数。

对于一个 $i$，枚举 $j$ 并维护一个 bitset，该 bitset 的第 $k$ 项表示 $A_i$ 前 $j$ 项与 $A_k$ 前 $j$ 项是否相似，则我们需要对 $A_{x,j}=A_{i,j}$ 的所有 $x$，将 bitset 对应位翻转，预处理这样的 $x$ 的集合即可。

时空复杂度均为 $O\left(\dfrac{nm\max A_i}{w}\right)$，可以通过此题。

```cpp
#include <cstdio>
#include <bitset>
using namespace std;
const int N = 2005, W = 1005;
int a[N][N];
bitset < N > res, p[W][N];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			p[a[i][j]][j][i] = true;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			res[j] = false;
		}
		for (int j = 1; j <= m; j++) {
			res ^= p[a[i][j]][j];
		}
		ans += res.count();
		if (m % 2 == 1) {
			ans--;
		}
	}
	printf("%d", ans / 2);
	return 0;
}
```

---

## 作者：Milthm (赞：1)

这题未免有点太抽象了。

如果你按照题意模拟，时间复杂度是 $O(n^2m)$ 的，也就是 $8\times 10^9$，显然过不去。但是呢，因为题目要求枚举的 $(i,j)$ 要满足 $i<j$，所以实际上只有 $4\times 10^9$ 量级。因为题目时限 $2$ 秒，所以一秒只要跑 $2\times 10^9$ 量级。

结合~~生活实际~~ AT 的机子得知，在这种很小的常数下，AT 的机子可以做到一秒 $2\times 10^9$，所以我们直接按照题意模拟就能过了。

### AC code

可以采用快读、bool 表达式和三目运算符的方式减少常数。

代码跑的很快，最大的点才 $598$ 毫秒。

```cpp
#include<bits/stdc++.h>
#define N 2005
using namespace std;
int read(){
	int ans=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans;
}
int n,m,a[N][N],ans,qwq;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)a[i][j]=read();
	}
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			qwq=0;
			for(int k=1;k<=m;++k)qwq+=(a[i][k]==a[j][k]);
			qwq%2?++ans:0;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：破壁人罗辑 (赞：1)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc348_f)/[AtCoder](https://atcoder.jp/contests/abc348/tasks/abc348_f)

## 题目大意

给出 $N$ 个数列（$1\leq N\leq2000$），每个数列含有 $M$ 个正整数（$1\leq M\leq2000$，且数列中正整数 $A$ 的大小满足 $1\leq A\leq999$），求满足第 $i$ 个数列和第 $j$ 个数列正好有奇数个位置对应数字相同且 $1\leq i<j\leq N$ 的数对 $(i,j)$ 的个数。

## 解题思路

最简单的方式是 $O(MN^2)$ 统计每个数列和其它数列的相同元素个数，然后加和，会超时。

我们可以记下第 $i$ 位的数字为 $A$ 的数列，设 $k_{a,i}$ 表示第 $i$ 位为 $a$ 的数列数量，所以每一次我们不需要遍历其它 $N-1$ 个数组进行比较，只需要遍历 $k_{A,i}$ 个数组，时间复杂度为 $O(MNk_{max})$，在所有数组全部相同时会退化为 $O(MN^2)$，也会超时。

因为我们只需要关注奇偶性，不需要关注具体的相同数字数量，我们不需要统计数量，只需要统计每次比较的异或和。

我们注意到 $A\leq999$，所以我们可以使用 `bitset<2000>` 来进行优化，设 $b_{a,i}$ 表示第 $i$ 位数字为 $a$ 的状态，其中二进制第 $j$ 位为 $1$ 表示数组 $j$ 的第 $i$ 位数字为 $a$，为 $0$ 表示数组 $j$ 的第 $i$ 位数字不为 $a$，则对于每一个数组我们只需要将 $b_{A_1,1},b_{A_2,2},\cdots,b_{A_M,M}$ 进行异或，然后统计非零的二进制位的个数即可，时间复杂度 $O(N(N+M))$。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<2000> ai[1000][2000],t[2000];
int a[2000][2000];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++){
		scanf("%d",&a[i][j]);
		ai[a[i][j]][j][i]=1;
	}
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)t[i]^=ai[a[i][j]][j];
		for(int j=0;j<i;j++)ans+=t[i][j];
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：1)

官方题解居然是暴力，差评！！！

直接暴力是 $O(n^2m)$ 的，会超时。考虑 bitset 优化。

竖着考虑每一位都有哪些相同的值，将每一个相同的块用 bitset 表示出来并全都异或一遍即可。

```cpp
for(int cur=1;cur<=m;cur++){// 考虑每一位
  for(int v=1;v<1000;v++)id[v].clear();// id[x] 表示这一位值为 x 的都有哪些，是一个 vector
  for(int i=1;i<=n;i++)id[a[i][cur]].push_back(i);
  for(int v=1;v<1000;v++){
    bitset<2005>tmp;
    for(auto i:id[v])tmp.set(i);// bitset 表示
    for(auto i:id[v])ans[i]^=tmp;// 全异或上
  }
}
int tot=0;
for(int i=1;i<=n;i++)ans[i][i]=0,tot+=ans[i].count();// 记得把自己到自己设为 0
cout<<tot/2<<"\n";
```

---

## 作者：coderJerry (赞：0)

### 题目描述：[传送门](https://www.luogu.com.cn/problem/AT_abc348_f)
### 题目分析
就这？$550$ 分！

直接按照题意模拟，暴力枚举所有序列中元素相等的个数并判断统计。

而且加一行火车头就可以完全避免卡常问题了。
### AC 代码
```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
int n,m,a[2010][2010],ans=0;
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);cout.tie(nullptr);
  cin>>n>>m;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      cin>>a[i][j];
    }
  }
  for(int i=1;i<=n;++i){
    for(int j=i+1;j<=n;++j){
      int cnt=0;
      for(int k=1;k<=m;++k){
        if(a[i][k]==a[j][k]) ++cnt;
      }
      if(cnt%2==1) ++ans;
    }
  }
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定 $n$ 个长度为 $m$ 的序列，第 $i$ 个序列的第 $j$ 个数为 $a_{i,j}$。

定义两个序列 $(x,y)$ 相似当且仅当：

- $\sum_{i=1}^m [a_{x,i}=a_{y,i}]$ 的值为奇数。

求有多少对序列相似。

### 思路：

因为 $n,m$ 很小，考虑暴力枚举数对 $(x,y)$，现在瓶颈是求 $\sum_{i=1}^m [a_{x,i}=a_{y,i}]$ 的值。

注意到，如果值域是 $0/1$ 的话，那么就是两个序列 $\operatorname{xor}$ 之后 $0$ 的个数；但是此时值域是 $999$，也很小，考虑转化为 $0/1$ 序列。

先考虑将每个数拆分为二进制，记 $s_{k,i,j}$ 表示 $a_{i,j}$ 二进制下第 $k$ 位的值，可以用 `bitset` 维护。

因为两个数相同当且仅当二进制下每一位都相同，即每一位按位异或的值都为 $0$，即按位或的值 $\ne 1$。

那么考虑令：

$$t=\operatorname{or}_{i=0}^{10} s_{k,x} \operatorname{xor} s_{k,y}$$

将 $t$ 拆分为二进制后，前 $m-1$ 个数中 $0$ 的个数就是相同的个数，判一下是否是奇数即可。

时间复杂度为 $O(\frac{N^2M \log W}{w})$（$W$ 表值域，$w$ 表 `bitset` 的优化。）.

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2020;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans;
ll a[N][N];
bitset<N> s[11][N];
bitset<N> t;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			for(int k=0;k<10;k++)
			  s[k][i][j]=(a[i][j]>>k)&1ll;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			t=s[0][i]^s[0][j];
			for(int k=1;k<10;k++)
			  t|=s[k][i]^s[k][j];
//			for(int l=1;l<=m;l++)
//			  cerr<<t[l];
//			cerr<<'\n';
			if((m-t.count())&1ll)
			  ans++;
		}
	}
	write(ans);
	return 0;
}

```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_f)

**本题解是对 $\mathcal{O}(N^2 M)$ 做法的补充说明。如果卡不过去可以来这里挑错。**

- 记得开全火车头，能优化十几毫秒。

- 不要用 `f^=(...)`，这样会慢，把它替换成 if 语句会更快。

- 用 c++17 来提交。

- 要把**所有**变量都开成 int，因为转换变量类型需要时间。

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc348_f)

麻了，官解是暴力。

这里提供的是 bitset 做法。

首先，如果两个数相同，那么这两个数按位异或后每一位一定为 $0$。

那么可以开 $n\times 11$ 个 bitset $b$，$b_{i,j}$ 表示第 $i$ 个序列的所有数字二进制下的第 $j$ 位上的数。

然后先暴力枚举 $i$ 和 $j$ 表示选择两个序列，接下来枚举位数 $k$，把 $b_{i,k}$ 和 $b_{j,k}$ 相异或，存储到 $c_k$ 中。

最后把所有的 $c_k$ 进行或运算，以此来查出有哪些位置在某一位当中相异或得到 $1$，当然的，或完之后这些位置上是 $1$。

然后用函数统计 $1$ 的个数，再用 $m$ 减去就是 $0$ 的个数，也就是两个序列每一位相异或后都为 $0$ 的位置的数量，也就是两个序列中同位置上的数相同的位置的数量。

判断一下这个数的奇偶性就行，如果是奇数就把答案加一。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
int a[2010][2010];
bitset<2010> b[2010][15];
int ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
		for(int j=0;j<=10;j++)
			for(int k=0;k<m;k++)
				b[i][j][k]=(bool)(a[i][k+1]&(1<<j));
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			bitset<2010> c[15],d;
			for(int k=0;k<=10;k++)
				c[k]=b[i][k]^b[j][k];
			for(int k=0;k<=10;k++) d|=c[k];
			int sum=m-d.count();
			if(sum&1) ans++;
		}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简介

我们可以转换统计思路：对每一列数字相同的数列进行统计，最后再进行汇总。注意到 $N$、$M$、值域都极小，我们考虑使用 bitset。

具体而言，我们对于每一列进行扫描，使用一个 bitset 数组 $b$ 统计在这一列上，所对应元素的值相同的数列。同时，我们再开一个统计答案的 bitset 数组 $ans$，统计在这个数列之前，哪几个数列有着奇数个与其相同的元素。我们利用 bitset 之间可以异或的特点，设当前的位置为 $(i, j)$，在当前列扫描到当前数列时，将 $ans_i$ 异或上 $b_{a_{i, j}}$，就能在 $ans_i$ 中留下到这一列为止，与当前数列相同元素个数为奇数的数列。异或之后，只要将 $b_{a_{i, j}}$ 修改为真即可。

最后答案即为每一个 $ans$ bitset 中 $1$ 的个数。

## 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;

const int N = 2005;

int n, m, a[N][N];

std::bitset<N> b[1005], ans[N];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j)
            std::cin >> a[i][j];
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i < 1000; ++i) b[i].reset();
        for (int i = 1; i <= n; ++i) {
            ans[i] ^= b[a[i][j]];
            b[a[i][j]][i] = true;
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) res += ans[i].count();
    std::cout << res;
    return 0;
}
```

---

## 作者：small_john (赞：0)

## 思路

bitset 好题，还是挺简单的。

首先我们把第 $i$ 位为 $j$ 的序列丢进一个 bitset 里（这个 bitset 的第 $k$ 位为一则表示第 $k$ 个序列第 $i$ 位为 $j$），记为 $s_{i,j}$。

考虑对第 $x$ 个序列计数。我们可以 $a_x$ 的遍历每一位 $i$，把 $s_{i,a_{x,i}}$ 异或起来，把结果记为 $vis$。那么序列 $y$ 满足条件当且仅当 $vis$ 的第 $y$ 位为一（奇数个一异或起来才是一）。

模拟上述做法即可，时间复杂度 $O(\frac{nmV}{\omega})$，其中 $V$ 表示值域。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e3+5;
bitset<N> s[N][N/2];
int n,m; 
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);	
	read(n),read(m);
	int ans = 0;
	for(int i = 1;i<=n;i++)
	{
		bitset<N> ss;
		for(int j = 1,x;j<=m;j++)
		{
			read(x);
			ss^=s[j][x];
			s[j][x][i] = 1;
		}
		ans+=ss.count();
	}
	write(ans);
	return 0;
}
```

---

## 作者：g1ove (赞：0)

题意：给出长度为 $M$ 的 $N$ 个序列，定义两个序列 $(A,B)$ 是相似的，仅当有奇数个 $i$ ，使得 $A_i=B_i$。

求所有 $1\le i<j\le n$ 的整数对 $(i,j)$ 中，有多少对是相似的。

$N,M\le 2000,A_{i,j}\le 999$
## Solution
看到数据这么小我们直接往暴力方面想。

最原始的想法是枚举所有 $(i,j)$ ，暴力判断，时间复杂度 $O(nm^2)$ ，应该是过不了的，考虑优化暴力算法。

一种很快想到的思路是，固定 $i$ ，寻找有多少个 $j$ 是满足相似的。

于是我们优化暴力的方向就出来了：把所有满足 $A_{i,j}=x$ 的数全部塞进 `vector` 里面，$d_{j,x}$ 存储有哪些行满足第 $j$ 个数是 $x$ 。然后枚举 $i$ 行时遍历这一行   $d_{j,A_{i,j}}$ ，把所有满足第 $j$ 列是 $A_{i,j}$ 的行都打上一次标记，那么最终有效答案就是被打了奇数次标记的行。

这样的时间复杂度如果出题人特意卡，是会到 $O(n^2m)$ 的。应该还是过不去的。

我们仔细思考一下，实际上，加奇数次比较难处理，不如把加变为异或运算，这样，只需要判断最终有多少行结果是 $1$ 即可。

再次思考，这个东西是不是可以使用位运算优化一下？我们把所有 `vector` 都压缩成一个 $n$ 位的二进制数，那么，最终我们实际上是在异或上一些二进制数后最终有多少个 $1$ 。

这个东西可以使用 `bitset` 来优化，于是就做完了，最后记得特判一下 $m$ 为奇数的情况，因为这样统计答案时会统计到 $(i,i)$，是不合法的，要删除。由于计算时 $(i,j)$ 和 $(j,i)$ 都统计了一次，所以答案再除个 $2$ 即可。

时间空间复杂度均为 $O(\frac{n^2m}{w})$。

[赛时 code](https://atcoder.jp/contests/abc348/submissions/52104663)

---

## 作者：HHH6666666666 (赞：0)

逆天题。

直接比较的复杂度是 $O(n^2m)$，此时根据官方题解卡卡常搞点奇怪优化就能艹过。

由于此题只用求奇偶，且值域较小，更推荐的方法是使用 `std::bitset` 将其优化为 $O(\frac{n^2m}{w})$，此题常数较小，这个复杂度基本稳过。对于每一列每一种值开一个关于行的 `bitset` 然后异或即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2010;
const int MAXV = 1010;

int n, m;
int a[MAXN][MAXN];
bitset<MAXN> b[MAXN][MAXV];

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            b[j][a[i][j]][i] = true;
        }
    }
    bitset<MAXN> tl, temp;
    for (int i = 1; i <= n; ++i) tl[i] = true;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        temp.reset(); tl[i] = false;
        for (int j = 1; j <= m; ++j)
            temp ^= b[j][a[i][j]];
        temp &= tl;
        ans += temp.count();
    }
    cout << ans << endl;
    return 0;
}

```

---

