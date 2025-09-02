# Infinite Game

## 题目描述

Alice 和 Bob 正在玩一个由若干局组成的无限游戏。每一局由若干轮组成，每一轮有一名玩家获胜。第一个赢得两轮的玩家将赢得该局。因此，每一局的最终比分总是 $2:0$ 或 $2:1$，胜者为 Alice 或 Bob。

我们称一个游戏场景为一个由字符 'a' 和 'b' 组成的有限字符串 $s$。考虑一个由 $s$ 无限重复拼接而成的无限字符串：$sss\ldots$。假设 Alice 和 Bob 按照这个无限字符串从左到右进行每一轮。如果当前字符为 'a'，则 Alice 赢得该轮；如果为 'b'，则 Bob 赢得该轮。当有一名玩家赢得两轮时，该局结束，下一局从下一个字符开始。

定义 $a_i$ 为 Alice 在前 $i$ 局中赢得的局数。定义 $r$ 为比值 $\frac{a_i}{i}$ 在 $i \rightarrow \infty$ 时的极限。如果 $r > \frac{1}{2}$，我们称场景 $s$ 对 Alice 有利；如果 $r = \frac{1}{2}$，称为平局；如果 $r < \frac{1}{2}$，称场景对 Bob 有利。

现在给定一个只包含 'a'、'b' 和 '?' 的字符串 $s$。请统计将所有 '?' 替换为 'a' 或 'b' 所有可能的方案中，有多少种方案使得场景对 Alice 有利，有多少种方案为平局，有多少种方案对 Bob 有利。请将这三个数对 $998\,244\,353$ 取模后输出。

## 说明/提示

在第一个样例中，有四种替换问号的方式：

- $s = \mathtt{aa}$：Alice 每局都以 $2:0$ 获胜——对 Alice 有利；
- $s = \mathtt{ab}$：Alice 和 Bob 轮流以 $2:1$ 获胜——平局；
- $s = \mathtt{ba}$：Bob 和 Alice 轮流以 $2:1$ 获胜——平局；
- $s = \mathtt{bb}$：Bob 每局都以 $2:0$ 获胜——对 Bob 有利。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
??```

### 输出

```
1
2
1```

## 样例 #2

### 输入

```
?aa?b```

### 输出

```
1
3
0```

## 样例 #3

### 输入

```
a???ba```

### 输出

```
4
3
1```

## 样例 #4

### 输入

```
????????```

### 输出

```
121
14
121```

## 样例 #5

### 输入

```
ba????a?a???abbb?```

### 输出

```
216
57
239```

## 样例 #6

### 输入

```
a????a??????b??abbababbbb?a?aaa????bb```

### 输出

```
97833
28387
135924```

## 样例 #7

### 输入

```
??????????????a????????????????b?????```

### 输出

```
484121060
448940322
484613337```

# 题解

## 作者：Alex_Wei (赞：10)

在 $s$ 无穷拼接的过程中，对于每个 $s$，在执行它对应的比赛之前，只有初始比分会改变。初始比分共四种状态，分别记为 $0, 1, 2, 3$。

现在，我们只要知道初始比分 $i$ 经过 $s$ 之后的最终比分 $j$ 以及 A 获胜的轮数减去 B 获胜的轮数 $k$，就可以确定 $s$ 对应的 $r$ 值：从 $0$ 开始，经过一段 $\rho$ 型路径到达一个环，设 $\Delta$ 为环上所有 $k$ 值之和，若 $\Delta > 0$，则 $r > \frac 1 2$；若 $\Delta = 0$，则 $r = \frac 1 2$（尽管前面会有不在环上的路径，但当轮数趋于正无穷时，它对比值的贡献几乎不存在）；若 $\Delta < 0$，则 $r < \frac 1 2$。

$i\to (j, k)$ 形成了映射 $f$，我们求出使得经过 $s$ 后对应关系为 $f$ 的 $s$ 的数量。对于某个映射 $f$，在其后添加 $a$ 或 $b$，会得到不同的新的映射 $f_1, f_2$。我们将涉及到的 $f$ 用一个数表示（相当于离散化），再进行 DP。内层映射的转移是直接模拟，所以应该算不上 DP 套 DP，就是一个简单的 DP 自动机。

看似状态数为 $\mathcal{O}(n ^ 4)$ 并带有常数 $4 ^ 4 = 256$，但看上去就很跑不满。最终状态数 $\mathcal S$ 只有不到 $10 ^ 6$ 种，而时间复杂度为 $\mathcal{O}(n\mathcal S)$（可能还要算上离散化的 $\mathcal{S} \log \mathcal{S}$），可以接受。[代码](https://codeforces.com/contest/1785/submission/192577785)。

另一种时间复杂度更可观的做法：直接枚举环上的所有点（$2 ^ 4$ 种情况），这样就不需要对每个 $i$ 维护对应的 $k$，而是直接维护环上的点的 $\sum k$，统计答案时检查一下是否合法即可。

时间复杂度 $\mathcal{O}(n ^ 2)$ 并带有常数 $2 ^ 4\times 4 ^ 4 = 4096$。懒得写了。

---

## 作者：_Diu_ (赞：10)

T 宝你干嘛哎呦，把火题藏后面。由于我太蠢了，想 D 想半天没发现 EF 都比 D 火，C 还 fst 了，导致神秘掉分。/ll

套路题，dp 套 dp，或者说叫自动机 dp。

这种计数题先考虑如何走一轮。我们发现只有四个有用状态：`0:0`, `1:0`, `0:1`, `1:1`，假设这四个点分别是 $0,1,2,3$。然后我们可以容易在上面跑。

我们发现最终一定会形成一个环，因为问的是极限，所以前面在进环之前的若干次循环并不需要计入答案。

如果我们简单地想从 $0$ 开始走，走完一次再重新走，这样是不对的，因为我们要保证中间每个 `?` 的选择是一样的。所以我们容易想到对起点在四个状态的情况分别记录。设 $f_{i,a,b,c,d}$ 表示走了 $i$ 步，起点为 $0,1,2,3$ 分别走到 $a,b,c,d$ 的方案数。

考虑统计对应 `Alice` 的胜场减去 `Bob` 的胜场。由于只有最终的环有贡献，并不好统计，所以可以考虑枚举最终的环上的点集 $s$，容易发现这些点在一个大循环上只出现一次。所以我们增加一维 $j$ 记录对应的胜场，然后统计答案即可。

复杂度 $O(n^2)$，自动机状态常数为 $4^4\times 2^4$，能够通过。空间可能不太够，建议滚动数组压掉一维。评价：感觉比 D 火。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=410,p=998244353;
int n,f[2*N][4][4][4][4],g[2*N][4][4][4][4],to[4][2],val[4][2];
char str[N];
int ans[3];
void add(int &x,int y){x+=y;if(x>=p)x-=p;}
signed main(){
	scanf("%s",str+1),n=strlen(str+1);
	to[0][0]=1,to[0][1]=2;
	to[1][0]=0;
	to[1][1]=3,to[2][0]=3;
	to[2][1]=0;
	to[3][0]=to[3][1]=0;
	for(int s=0;s<16;s++){
		memset(f,0,sizeof(f));
		f[N][0][1][2][3]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<2*N;j++){
				for(int a=0;a<4;a++)for(int b=0;b<4;b++)for(int c=0;c<4;c++)for(int d=0;d<4;d++){
					if(!f[j][a][b][c][d])continue;
					for(int k=0;k<2;k++){
						if(str[i]-'a'!=k&&str[i]!='?')continue;
						int na=to[a][k],nb=to[b][k],nc=to[c][k],nd=to[d][k];
						int nj=((s&1)&&(a&(k+1)))+((s&2)&&(b&(k+1)))+((s&4)&&(c&(k+1)))+((s&8)&&(d&(k+1)));
						nj=(k?j+nj:j-nj);
						add(g[nj][na][nb][nc][nd],f[j][a][b][c][d]);
					}
				}
			}
			for(int j=0;j<2*N;j++)
				for(int a=0;a<4;a++)for(int b=0;b<4;b++)for(int c=0;c<4;c++)for(int d=0;d<4;d++)
					f[j][a][b][c][d]=g[j][a][b][c][d],g[j][a][b][c][d]=0;
		}
		for(int a=0;a<4;a++)for(int b=0;b<4;b++)for(int c=0;c<4;c++)for(int d=0;d<4;d++){
			int tol[4]={a,b,c,d};
			int x=0;
			for(int _=0;_<5;_++)x=tol[x];
			int st=0;
			for(int _=0;_<5;_++)st|=1<<x,x=tol[x];
			if(st!=s)continue;
			for(int j=0;j<2*N;j++)add(ans[(j>=N)+(j>N)],f[j][a][b][c][d]);
		}
	}
	printf("No Copy:%d\n%d\n%d\n",ans[0],ans[1],ans[2]);
}
```

---

## 作者：UnyieldingTrilobite (赞：6)

首先这个题的比分非常的简单，实际上只有四种：$0:0$，$0:1$，$1:0$，$1:1$。通过状压，我们不妨把这四种比分编号为 $0$ 到 $3$ 的整数。我们考虑，每次从任意一种比分状态出发，遍历一轮 $s$ 之后一定会进入到另一个比分状态，并产生若干次双方的胜负。这样的话我们其实可以把题目里这个无限走 $s$ 的流程简化：每次在自动机上从一个状态（遍历一轮 $s$）跳到下一个状态，并统计双方胜负（我们不妨就把这样跳一次状态导致 Alice 比 Bob 多出的胜场次数作为这个转移的边权）。由于最后会走无限次 $s$，我们实际上只需要考虑在跳自动机的过程中进入环之后，环上边的权值之和是正是负（或者是零）就可以了。

如此一来，我们便不难想到一个简单的 dp。设计状态 $f(i,\{u_0,u_1,u_2,u_3\},\{w_0,w_1,w_2,w_3\})$，表示当前考虑到第 $i$ 个 $s$ 位，四个状态当前的转移目标是 $u$ 集合，转移边权是 $w$ 集合。这样的状态数是 $O(n^5)$ 的，考虑到每一种 $w$ 都可以达到关于 $n$ 的线性。根据 t 宝的说法，这个算法在控制好常数的前提下是能冲过去的。

但是我们显然不满足于此。我们意识到一件事情：既然只关心边权之和，那为什么不把它加好塞在状态里，而是关注每一个 $w$ 的值？我们回顾之前的说法，这是因为我们实际上要统计的是环上的边权和，而最后哪些边在环上是要根据 $u$ 去算的。那我们实际上会考虑到另一种思路——预先钦定好哪些边在环上（$2^4=16$ 种方案，虽然实际上不到），最后根据 $u$ 去检查一下环上是不是确实是这些边，这样一来我们的 $w$ 就可以整个四合一加成 $s$ 放进状态了。代价是，我们需要跑 $16$ 次 dp，而不是一次结束。现在我们的状态是：$f(i,\{u_0,u_1,u_2,u_3\},s\})$，其中 $s$ 就是钦定的边的 $w$ 之和。现在我们的 dp 就是平方而不是五次方了，尽管这个常数大得稍微有那么一些离谱（毛估估一下的话，$2^{18}$ 吧）。

代码建议可以写，挺好玩的。

```cpp
#include <bits/stdc++.h>

#include <atcoder/modint>
using namespace std;
typedef atcoder::modint998244353 mint;
constexpr int N = 209, A = 4;
typedef mint dparr[A][A][A][A][N << 3];
int n, b;
string s;
mint ans[3];
int trans(int& x, char c) {
  x ^= x == 0b11 ? x : (1 << (c & 1));
  return x ? 0 : (c & 1) ? -1 : 1;
}
int trans(int x[], char c, int t) {
  int ans = 0;
  for (int i = 0; i < A; ++i) {
    int w = trans(x[i], c);
    if (t >> i & 1) ans += w;
  }
  return ans;
}
#define enum_state()                              \
  int x[A]{};                                     \
  for (x[0b00] = 0; x[0b00] < A; ++x[0b00])       \
    for (x[0b01] = 0; x[0b01] < A; ++x[0b01])     \
      for (x[0b10] = 0; x[0b10] < A; ++x[0b10])   \
        for (x[0b11] = 0; x[0b11] < A; ++x[0b11]) \
          for (int sx = 0; sx <= (b << 1); ++sx)  \
            if (mint w = f[x[0b00]][x[0b01]][x[0b10]][x[0b11]][sx]; w.val())
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> s, n = s.length(), b = n << 2;
  for (int t = 1; t < (1 << A); ++t) {
    dparr f;
    f[0b00][0b01][0b10][0b11][b] = 1;
    for (char ch : s) {
      dparr g;
      enum_state() {
        auto transf = [&](char c) {
          int y[A];
          memcpy(y, x, sizeof x);
          int sy = trans(y, c, t) + sx;
          g[y[0b00]][y[0b01]][y[0b10]][y[0b11]][sy] += w;
        };
        if (ch != 'b') transf('a');
        if (ch != 'a') transf('b');
      }
      memcpy(f, g, sizeof f);
    }
    enum_state() {
      bool vst[A]{};
      int p = 0b00, q = 0;
      while (true) {
        if (!vst[p])
          vst[p] = true;
        else if (q >> p & 1)
          break;
        else
          q |= 1 << p;
        p = x[p];
      }
      if (t != q) continue;
      ans[sx > b ? 2 : sx == b] += w;
    }
  }
  return cout << ans[0].val() << '\n'
              << ans[1].val() << '\n'
              << ans[2].val() << endl,
         0;
}
```

---

## 作者：Graphcity (赞：2)

先进行大胆猜想：游戏最后会进行循环。

证明：考虑每轮末尾有几个字符未被匹配，显然这是数字只能是 0,1,2 中的一个。根据抽屉原理，至多跑 4 轮就会有一个断点跟之前的一样。

所以我们就需要考虑这个循环中 Alice 和 Bob 的胜负比较。不妨使用动态规划解决问题。

首先要用信息表示一个匹配。发现未完成匹配的串至多只有五种：空串，`a`，`b`，`ab`，`ba`。我们用数字 $0\sim 4$ 来表示这个状态。转移则需要使用 DP 套 DP，预处理出每一种状态后接一个字符的状态和胜负情况。

设 $f_{i,j,k_{1\cdots m}}$ 表示 $m$ 轮后进入循环，当前在第 $i$ 个字符，Alice 比 Bob 多胜 $j$ 局，每一轮当前的状态为 $k_{1\cdots m}$。初始状态为 $f_{0,0,\{0,k_{2\cdots m}\}}$，终止状态为 $f_{n,j,\{k_{2\cdots m},p\}}$。其中 $p$ 为 $0$ 或 $k_{2\cdots m}$ 中的一个。

精细分析发现 3 轮就可以跑完。时间复杂度 $O(n^25^4)$，但是合法状态极少，可以直接跑过去。

[Code](https://www.luogu.com.cn/paste/9a6ni7f0)



---

## 作者：Leasier (赞：1)

首先考虑 $s$ 固定的情况。

走到某一步时，设当前对局状态 $X \in \{[], [a], [b], [ab]\}$，当前 Bob 的得分减去 Alice 的得分为 $w$。

每读入字符串下一位时，作如下转移：

- $[] + a = [a]$，$\Delta w = 0$。
- $[] + b = [b]$，$\Delta w = 0$。
- $[a] + a = []$，$\Delta w = -1$。
- $[a] + b = [ab]$，$\Delta w = 0$。
- $[b] + a = [ab]$，$\Delta w = 0$。
- $[b] + b = [0]$，$\Delta w = 1$。
- $[ab] + a = []$，$\Delta w = -1$。
- $[ab] + b = []$，$\Delta w = 1$。

设初始状态为 $X$ 时走完这一个字符串变为 $f(X)$，总 $\Delta w$ 为 $g(X)$，则连边 $X \to f(X)$，找到**从 $X$ 出发所达的环上的 $g$ 值之和**，判断其与 $0$ 的大小即可。

时间复杂度为 $O(n)$。

------------

考虑 $s$ 不固定的一般情况。

一个最简单的想法是：设 $dp_{i, (j_0, k_0), (j_1, k_1), (j_2, k_2), (j_3, k_3)}$ 表示在 $s$ 上已经走了前 $i$ 步，初始 $X$ 的四种取值对应现在的新值和 $\Delta w$。

但这样的话状态数就已经达到了大常数 $O(n^5)$，显然不能通过。

注意到我们所求的是环上的和，考虑**枚举环上的所有 $X$**（只有 $15$ 种情况），这样一来在 dp 时我们只需记录我们所钦定的那些 $X$ 对应的 $\Delta w$ 之和。

时间复杂度降至大常数 $O(n^2)$，可以通过。

代码：
```cpp
#include <stdio.h>
#include <string.h>

const int mod = 998244353;
int bit[257][7], strans[7][7], sval[7][7], trans[257][7], val[257][7], dp[207][807][257];
char s[207];

inline void clear(int n, int m){
	int base = n * m;
	for (register int i = 0; i <= n; i++){
		int up = i * m;
		for (register int j = -up; j <= up; j++){
			for (register int k = 0; k < 256; k++){
				dp[i][j + base][k] = 0;
			}
		}
	}
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

int main(){
	int n, ans1 = 0, ans2 = 0, ans3 = 0;
	scanf("%s", &s[1]);
	n = strlen(&s[1]);
	for (register int i = 0; i < 256; i++){
		bit[i][0] = i & 3;
		bit[i][1] = i >> 2 & 3;
		bit[i][2] = i >> 4 & 3;
		bit[i][3] = i >> 6 & 3;
	}
	strans[0][0] = 1;
	sval[0][0] = 0;
	strans[0][1] = 2;
	sval[0][1] = 0;
	strans[1][0] = 0;
	sval[1][0] = -1;
	strans[1][1] = 3;
	sval[1][1] = 0;
	strans[2][0] = 3;
	sval[2][0] = 0;
	strans[2][1] = 0;
	sval[2][1] = 1;
	strans[3][0] = 0;
	sval[3][0] = -1;
	strans[3][1] = 0;
	sval[3][1] = 1;
	for (register int i = 0; i < 256; i++){
		for (register int j = 0; j <= 1; j++){
			for (register int k = 0; k < 4; k++){
				trans[i][j] |= strans[bit[i][k]][j] << (k * 2);
			}
		}
	}
	for (register int i = 1; i < 16; i++){
		int popcnt = __builtin_popcount(i), base = n * popcnt;
		for (register int j = 0; j < 256; j++){
			for (register int k = 0; k <= 1; k++){
				val[j][k] = 0;
				for (register int l = 0; l < 4; l++){
					if (i >> l & 1) val[j][k] += sval[bit[j][l]][k];
				}
			}
		}
		clear(n, popcnt);
		dp[0][base][228] = 1;
		for (register int j = 0; j < n; j++){
			int up = j * popcnt;
			for (register int k = -up; k <= up; k++){
				for (register int l = 0; l < 256; l++){
					if (dp[j][k + base][l] != 0){
						for (register int x = 0; x <= 1; x++){
							if (s[j + 1] != (x ^ 1) + 'a') add(dp[j + 1][k + val[l][x] + base][trans[l][x]], dp[j][k + base][l]);
						}
					}
				}
			}
		}
		for (register int j = 0; j < 256; j++){
			int go = 0, vis = 0;
			bool flag = true;
			while (!(i >> go & 1)){
				if (vis >> go & 1){
					flag = false;
					break;
				}
				vis |= 1 << go;
				go = bit[j][go];
			}
			if (flag){
				int beg = go;
				vis = 0;
				for (register int k = 1; k <= popcnt; k++){
					vis |= 1 << go;
					go = bit[j][go];
				}
				if (beg == go && vis == i){
					for (register int k = -base; k < 0; k++){
						add(ans1, dp[n][k + base][j]);
					}
					add(ans2, dp[n][base][j]);
					for (register int k = 1; k <= base; k++){
						add(ans3, dp[n][k + base][j]);
					}
				}
			}
		}
	}
	printf("%d\n", ans1);
	printf("%d\n", ans2);
	printf("%d", ans3);
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

很没感觉的一道题。

首先特判掉 $n\le 2$。

在 $s$ 无穷拼接的过程中，我们考虑一个周期一个周期地匹配，由于每局比赛的长度是 $2$ 或者 $3$，因此每个周期开始的时候，把上个周期剩下的零头匹配完之后起始匹配位置只可能是 $0$ 或 $1$ 或 $2$，并且对于一个起始匹配位置 $i(0\le i\le 2)$，从这个位置开始匹配一轮以后到下个周期，存在唯一后继 $to_i$。而计算题目中那个极限是否 $\ge 0$，就等价于将 $i\to to_i$ 连边以后，$0$ 所在连通块的环内的部分是 Alice 赢的多还是 Bob 赢的多。

我们枚举有效部分的起始位置集合（共 $2^3$ 种），再枚举前三位的值（共 $2^3$ 种），然后考虑 DP：$dp_{i,j,a,b,c}$ 表示目前考虑到前 $i$ 位，有效部分中 Alice 胜场次数减去 Bob 胜场次数 $=j$，起始位置为 $0,1,2$ 的匹配方案目前状态分别为 $a,b,c$（$0:0,1:0,0:1,1:1$ 共四种）的方案数，这样最后统计答案的时候可以通过 $a,b,c$ 算出 $to_i$，进而检查起始位置集合是否真的是我们枚举的 mask，如果是就把 DP 值计入答案的贡献即可。

时间复杂度 $O(n^2·4096)$，但是常数很小所以过了。

```cpp
const int MAXN=200;
const int DLT=605;
const int MOD=998244353;
void add(int &x,int v){(x+=v)>=MOD&&(x-=MOD);}
int n;char s[MAXN+5];
int dp[MAXN+5][MAXN*6+10][4][4][4];
void trans0(int &j,int &A,int &B,int &C,int msk_in){
	if(A==1||A==3){A=0;if(msk_in&1)--j;}else A|=1;
	if(B==1||B==3){B=0;if(msk_in>>1&1)--j;}else B|=1;
	if(C==1||C==3){C=0;if(msk_in>>2&1)--j;}else C|=1;
}
void trans1(int &j,int &A,int &B,int &C,int msk_in){
	if(A==2||A==3){A=0;if(msk_in&1)++j;}else A|=2;
	if(B==2||B==3){B=0;if(msk_in>>1&1)++j;}else B|=2;
	if(C==2||C==3){C=0;if(msk_in>>2&1)++j;}else C|=2;
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	if(n==1){
		int A=0,B=0,C=0;
		if(s[1]!='a')B++;
		if(s[1]!='b')A++;
		printf("%d\n%d\n%d\n",A,C,B);
		return 0;
	}if(n==2){
		int A=0,B=0,C=0;
		if(s[1]!='a'&&s[2]!='a')B++;
		if(s[1]!='b'&&s[2]!='b')A++;
		if(s[1]!='a'&&s[2]!='b')C++;
		if(s[1]!='b'&&s[2]!='a')C++;
		printf("%d\n%d\n%d\n",A,C,B);
		return 0;
	}
	int res1=0,res2=0,res3=0;
	for(int msk_in=1;msk_in<8;msk_in++){
		int cnt=__builtin_popcount(msk_in);
		for(int fst3=0;fst3<8;fst3++){
			bool flg=1;
			for(int i=1;i<=3;i++){
				if(s[i]=='b'&&(fst3>>(i-1)&1))flg=0;
				if(s[i]=='a'&&!(fst3>>(i-1)&1))flg=0;
			}
			if(!flg)continue;memset(dp,0,sizeof(dp));
			int ini_j=0,ini_A=0,ini_B=0,ini_C=0,cmask=0;
			for(int i=0;i<3;i++){
				cmask|=(1<<i);cmask&=msk_in;
				if(fst3>>i&1)trans1(ini_j,ini_A,ini_B,ini_C,cmask);
				else trans0(ini_j,ini_A,ini_B,ini_C,cmask);
				if(!i)ini_B=ini_C=0;else if(i==1)ini_C=0;
			}
//			if(fst3==6&&msk_in==2){
//				printf("!! %d %d %d %d\n",ini_j,ini_A,ini_B,ini_C);
//			}
			dp[3][ini_j+DLT][ini_A][ini_B][ini_C]=1;
			for(int i=4;i<=n;i++)for(int j=-i*cnt;j<=i*cnt;j++)
				for(int A=0;A<4;A++)for(int B=0;B<4;B++)for(int C=0;C<4;C++){
					if(dp[i-1][j+DLT][A][B][C]){
						if(s[i]!='b'){
							int tj=j,tA=A,tB=B,tC=C;
							trans1(tj,tA,tB,tC,msk_in);
							add(dp[i][tj+DLT][tA][tB][tC],dp[i-1][j+DLT][A][B][C]);
						}
						if(s[i]!='a'){
							int tj=j,tA=A,tB=B,tC=C;
							trans0(tj,tA,tB,tC,msk_in);
							add(dp[i][tj+DLT][tA][tB][tC],dp[i-1][j+DLT][A][B][C]);
						}
					}
				}
			for(int A=0;A<4;A++)for(int B=0;B<4;B++)for(int C=0;C<4;C++){
				for(int j=-cnt*n;j<=cnt*n;j++)if(dp[n][j+DLT][A][B][C]){
					int tj=j,tA=A,tB=B,tC=C;
					static int to[3];memset(to,-1,sizeof(to));
					int tmp_msk_in=msk_in;
					if(tA==0)to[0]=0,tmp_msk_in&=6;
					if(tB==0)to[1]=0,tmp_msk_in&=5;
					if(tC==0)to[2]=0,tmp_msk_in&=3;
					for(int k=0;k<2;k++){
						if(fst3>>k&1)trans1(tj,tA,tB,tC,tmp_msk_in);
						else trans0(tj,tA,tB,tC,tmp_msk_in);
						if(tA==0&&!~to[0])to[0]=k+1,tmp_msk_in&=6;
						if(tB==0&&!~to[1])to[1]=k+1,tmp_msk_in&=5;
						if(tC==0&&!~to[2])to[2]=k+1,tmp_msk_in&=3;
					}
					static bool vis[3];memset(vis,0,sizeof(vis));
					int cur=0,msk=0;while(!vis[cur])vis[cur]=1,cur=to[cur];
					for(int _=0;_<3;_++)msk|=(1<<cur),cur=to[cur];
					if(msk==msk_in){
//						printf("! %d %d %d %d %d %d way=%d %d\n",msk_in,fst3,j,A,B,C,dp[n][j+DLT][A][B][C],tj);
						if(tj>0)add(res1,dp[n][j+DLT][A][B][C]);
						else if(tj==0)add(res2,dp[n][j+DLT][A][B][C]);
						else add(res3,dp[n][j+DLT][A][B][C]);
					}
				}
			}
		}
	}
	printf("%d\n%d\n%d\n",res1,res2,res3);
	return 0;
}

```


---

## 作者：User_Unauthorized (赞：0)

首先考虑若确定 $s$ 后如何计算答案。

发现比分只有 $\left(0 : 0\right), \left(0 : 1\right), \left(1 : 0\right), \left(1 : 1\right)$ 四种状态。我们不妨对于每种状态以其作为初始状态来按 $s$ 进行一轮游戏并得到终点状态和在这一轮游戏中 Alice 的得分与 Bob 得分的差以作为边权，按其建边可以得到一个内向基环树森林。由于我们求的是比分之比的极限，因此我们只需要考虑从 $\left(0 : 0\right)$ 出发可以到达的环上的边权即可。

考虑对这个内向基环树森林进行计数，考虑到只有四条边和四个节点，因此我们考虑将其压入状态，设 $f\left({i, \left\{u_0, u_1, u_2, u_3\right\}, \left\{w_0, w_1, w_2, w_3\right\}}\right)$ 表示考虑 $S\left[1, i\right]$ 且四个状态指向的状态依次为 $u_0, u_1, u_2, u_3$ 且边权依次为 $w_0, w_1, w_2, w_3$ 的方案数。不难发现这个 DP 的时间复杂度为 $\mathcal{O}(n^4)$，无法接受。考虑如何优化。

发现影响复杂度的主要是对边权的统计，考虑压缩这些状态。发现我们实际上要求的是环上的边权和，又考虑到节点个数很少，因此我们可以枚举环上的节点然后只记录环上的边权和。设 $f\left(i, \left\{u_0, u_1, u_2, u_3\right\}, s\right)$ 表示考虑 $S\left[1, i\right]$ 且四个状态指向的状态依次为 $u_0, u_1, u_2, u_3$ 且环上边权之和为 $s$ 的方案数，这样通过预处理转移边和边权即可实现快速转移。

复杂度为 $\mathcal{O}(n^2)$，常数大约为 $2^4 \times 4^4$。

---

