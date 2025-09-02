# Bear and Company

## 题目描述

Bear Limak prepares problems for a programming competition. Of course, it would be unprofessional to mention the sponsor name in the statement. Limak takes it seriously and he is going to change some words. To make it still possible to read, he will try to modify each word as little as possible.

Limak has a string $ s $ that consists of uppercase English letters. In one move he can swap two adjacent letters of the string. For example, he can transform a string "ABBC" into "BABC" or "ABCB" in one move.

Limak wants to obtain a string without a substring "VK" (i.e. there should be no letter 'V' immediately followed by letter 'K'). It can be easily proved that it's possible for any initial string $ s $ .

What is the minimum possible number of moves Limak can do?

## 说明/提示

In the first sample, the initial string is "VKVK". The minimum possible number of moves is $ 3 $ . One optimal sequence of moves is:

1. Swap two last letters. The string becomes "VKKV".
2. Swap first two letters. The string becomes "KVKV".
3. Swap the second and the third letter. The string becomes "KKVV". Indeed, this string doesn't have a substring "VK".

In the second sample, there are two optimal sequences of moves. One is "BVVKV" $ → $ "VBVKV" $ → $ "VVBKV". The other is "BVVKV" $ → $ "BVKVV" $ → $ "BKVVV".

In the fifth sample, no swaps are necessary.

## 样例 #1

### 输入

```
4
VKVK
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
BVVKV
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
VVKEVKK
```

### 输出

```
3
```

## 样例 #4

### 输入

```
20
VKVKVVVKVOVKVQKKKVVK
```

### 输出

```
8
```

## 样例 #5

### 输入

```
5
LIMAK
```

### 输出

```
0
```

# 题解

## 作者：quanjun (赞：5)

题目大意：给你一个长度为 $n(1 \le n \le 75)$ 的字符串，每一步操作你可以交换字符串中相邻的两个元素。求最少的操作步数，使得字符串中不包含子串 “VK”。  

解题思路：  

因为除了 'V' 和 'K' 以外的所有字符的效果都是一样的，所以我们可以把其它的字符都视为 'X'。  

我们会从左往右一步步构造出最终的字符串。令 $dp[v][k][x]$ 表示构造一个包含 $v$ 个字符 'V'，$k$ 个字符 'K' 以及 $x$ 个字符 'X' 的字符串前缀所需要的操作次数（这个字符串前缀对应的长度为 $v+k+v$）。但是这个状态是不完整的，我们还需要开一个维度来确保 'V' 和 'K' 有没有连接到一起（确保不存在 'V' 后面紧跟着一个 'K' 的情况出现）。所以我们需要再开一个维度来确保这个长度为 $v+k+x$ 的字符串前缀的最后一个字符是不是 'V'。于是，最终定义的状态为 $dp[v][k][x][lastLetter]$（或者可以表述成 $dp[v][k][x][is\_the\_last\_letter\_V]$）$\Rightarrow$ 它表示构造一个包含 $v$ 个字符 'V'、$k$ 个字符 'K'、$x$ 个字符 'X' 且最后一个字符是不是 'V' 的字符串前缀需要的最少交换次数。  

要从当前状态转移到下一个状态，我们需要考虑下一个 'K'（也就是初始状态下的第 $k+1$ 个字符 'K'）的位置，下一个 'V' 个位置，以及下一个 'X' 的位置。当然，如果当前状态的最后一个字符是 'V'，我们的下一个状态的最后一个字符不能是 'K'。  

也就是说，如果当前状态是 $dp[v][k][x][i]$ （当前有字符串前缀有 $v$ 个字符 'V'，$k$ 个字符 $K$，$x$ 个字符 'X'，$i=1$ 表示前缀的最后一个字符是 'V'，$i=0$ 表示前缀的最后一个字符不是 'V'）的话，则它可以扩展出如下状态（假设字符 'V' 的总数为 $V$，字符 'K' 的总数为 $K$，其他字符（视为 'X'）的总数为 $X$）：  
- 如果 $v \lt V$，则可以扩展到状态 $dp[v+1][k][x][1]$（将第 $v+1$ 个 'V' 移动到第 $v+k+x+1$ 个位置）；
- 如果 $k \lt K$，则可以扩展到状态 $dp[v][k+1][x][0]$（将第 $k+1$ 个 'K' 移动到第 $v+k+x+1$ 个位置）；
- 如果 $x \lt X$，则可以扩展到状态 $dp[v][k][x+1][0]$（将第 $x+1$ 个 'X' 移动到第 $v+k+x+1$ 个位置）。  

那么将一个字符转移到第 $v+k+x+1$ 个位置需要交换几次呢？  

可以发现，之前的状态是 $dp[v][k][x][i]$，所以前 $v$ 个 'V'、前 $k$ 个 'K'、前 $x$ 个 'X' 的位置我们不用管，假设要转移的字符一开始在第 $p$ 个位置，则它对应的交换次数是：  

第 $v+1$ 个 'V' 开始所有初始位置 $\lt p$ 的字符 'V' 个数 + 第 $k+1$ 个 'K' 开始所有初始位置 $\lt p$ 的字符 'K' 个数 + 第 $x+1$ 个 'X' 开始所有初始位置 $\lt p$ 的字符个数 之和。

这就是转移的代价。  

计算转移的代价可以有更快地解法，不过我们就算以 $O(n)$ 的算法解决也可以过，那么遍历 'V'、'K'、'X' 以及计算转移的代价，总时间复杂度 $O(n^4)$ 可以解决这个问题。  

示例程序：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 77;
int n, dp[maxn][maxn][maxn][2], V, K, X;
char s[maxn];
vector<int> vec_v, vec_k, vec_x;

int cal_swap_time(int v, int k, int x, int p) {
    int cnt = 0;
    for (int i = v; i < V && vec_v[i] < p; i ++) cnt ++;
    for (int i = k; i < K && vec_k[i] < p; i ++) cnt ++;
    for (int i = x; i < X && vec_x[i] < p; i ++) cnt ++;
    return cnt;
}

void chkmin(int &a, int b) {
    a = min(a, b);
}

int main() {
    scanf("%d%s", &n, s+1);
    for (int i = 1; i <= n; i ++) {
        if (s[i] == 'V') vec_v.push_back(i);
        else if (s[i] == 'K') vec_k.push_back(i);
        else vec_x.push_back(i);
    }
    V = vec_v.size();
    K = vec_k.size();
    X = vec_x.size();
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    for (int v = 0; v <= V; v ++) {
        for (int k = 0; k <= K; k ++) {
            for (int x = 0; x <= X; x ++) {
                for (int i = 0; i < 2; i ++) {
                    int tmp = dp[v][k][x][i];
                    if (v < V) chkmin(dp[v+1][k][x][1], tmp + cal_swap_time(v, k, x, vec_v[v]));
                    if (k < K && i==0) chkmin(dp[v][k+1][x][0], tmp + cal_swap_time(v, k, x, vec_k[k]));
                    if (x < X) chkmin(dp[v][k][x+1][0], tmp + cal_swap_time(v, k, x, vec_x[x]));
                }
            }
        }
    }
    printf("%d\n", min(dp[V][K][X][0], dp[V][K][X][1]));
    return 0;
}
```

---

## 作者：duyi (赞：4)

# CF771D Bear and Company

显然在本题里，除 $\texttt{V}$, $\texttt{K}$ 外的其他字符都是等价的，不妨将它们全都看做 $\texttt{C}$。于是串里就只剩 $\texttt{V}$, $\texttt{K}$, $\texttt{C}$ 三种字符。

同时容易发现，每种字符内部的相对顺序自始至终不会改变，因为交换相同的字符后，串不会发生变化，还白白浪费一次操作。

如果确定了一个结果串，那么从原串到结果串的最小操作次数就可以被求出来。因为根据“同种字符相对顺序不变”的性质，我们可以知道原串里每个字符，要移动到新串里什么位置。于是相当于给一个排列做冒泡排序，最小操作次数就是这个排列的逆序对数。

问题转化为，求一个所需操作次数最小的、合法的结果串。用 DP 来构造这个结果串。设 $\text{dp}(i,j,k,t)$ 表示考虑了结果串的前 $i+j+k$ 个字符，其中有 $i$ 个 $\texttt{C}$，$j$ 个 $\texttt{V}$，$k$ 个 $\texttt{K}$，最后一个字符是 $t$ 时，这前 $i+j+k$ 个字符内部贡献的逆序对数（也就是最小操作次数）。

转移时，我们枚举下一位是什么。为了保证合法，当 $t = \texttt{V}$ 时，下一个字符不能是 $\texttt{K}$。转移的代价就是前 $i+j+k$ 个字符与新字符构成的逆序对数，即前面有多少个在原串里出现位置 $ > $ 新字符在原串里出现位置的字符。这可以预处理出来，预处理的复杂度显然低于 $O(n^3)$。DP 复杂度为 $O(n^3)$，所以总时间复杂度 $O(n^3)$。

参考代码：

```cpp
// problem: CF771D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 75;
const int INF = 1e9;
int n;
char s[MAXN + 5];
int pos_c[MAXN + 5], pos_v[MAXN + 5], pos_k[MAXN + 5], cnt_c, cnt_v, cnt_k;
int cost_c[MAXN + 5][MAXN + 5], cost_v[MAXN + 5][MAXN + 5], cost_k[MAXN + 5][MAXN + 5];
int dp[MAXN + 5][MAXN + 5][MAXN + 5][3];

void init_cost() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt_c; ++j) {
			// 前 j 个 c 中, 有多少 > i
			cost_c[i][j] = cost_c[i][j - 1] + (pos_c[j] > i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt_v; ++j) {
			cost_v[i][j] = cost_v[i][j - 1] + (pos_v[j] > i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt_k; ++j) {
			cost_k[i][j] = cost_k[i][j - 1] + (pos_k[j] > i);
		}
	}
}
void init_dp_value() {
	for (int i = 0; i <= cnt_c; ++i) {
		for (int j = 0; j <= cnt_v; ++j) {
			for (int k = 0; k <= cnt_k; ++k) {
				for (int t = 0; t < 3; ++t) {
					dp[i][j][k][t] = INF;
				}
			}
		}
	}
}
int dp_work() {
	dp[0][0][0][0] = 0;
	for (int i = 0; i <= cnt_c; ++i) {
		for (int j = 0; j <= cnt_v; ++j) {
			for (int k = 0; k <= cnt_k; ++k) {
				for (int t = 0; t < 3; ++t) if (dp[i][j][k][t] != INF) {
					if (i < cnt_c) {
						ckmin(dp[i + 1][j][k][0], dp[i][j][k][t] + cost_v[pos_c[i + 1]][j] + cost_k[pos_c[i + 1]][k]);
					}
					if (j < cnt_v) {
						ckmin(dp[i][j + 1][k][1], dp[i][j][k][t] + cost_c[pos_v[j + 1]][i] + cost_k[pos_v[j + 1]][k]);
					}
					if (k < cnt_k && t != 1) {
						ckmin(dp[i][j][k + 1][2], dp[i][j][k][t] + cost_c[pos_k[k + 1]][i] + cost_v[pos_k[k + 1]][j]);
					}
				}
			}
		}
	}
	int ans = INF;
	for (int t = 0; t < 3; ++t) ckmin(ans, dp[cnt_c][cnt_v][cnt_k][t]);
	return ans;
}
int main() {
	cin >> n;
	cin >> (s + 1);
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'V') {
			pos_v[++cnt_v] = i;
		} else if (s[i] == 'K') {
			pos_k[++cnt_k] = i;
		} else {
			pos_c[++cnt_c] = i;
		}
	}
	
	init_cost();
	init_dp_value();
	int ans = dp_work();
	cout << ans << endl;
	return 0;
}
```









---

## 作者：chenxia25 (赞：3)

**[Portal]( https://www.luogu.com.cn/problem/CF771D )**

被 tzc 拉来做这题，然后他好像不太会，然而我自己 AC 了（（

至于为什么要单独写一篇题解呢，因为这题一个重要结论是我 baidu 出来的（

感谢 tzc 让我会了这样一个普遍性结论（

---

注意到这个字符串里面只分三种字符：$\texttt V$，$\texttt K$，和两个都不是的。这启示我们弄个三维 DP 分别记录三种字符的个数。然后因为相邻字符对有限制，所以还要再弄一维记录当前最后一个字符是啥。那么多项式算法的雏形就出来了。

然后一个难点在于：将一个字符串重新排列得到另一个字符串，那么如何算原串到新串的最小交换次数。

- 「这题难点就在如何算移动次数」
- 「告诉你个秘密：一个数列冒泡排序的次数等于逆序对数」（没错这个就是我 bfs 出来的，当年 NOIOL R1T2 好像也是这个结论，然后我当时不会，百撕不得其姐，后面有时间补吧。这个证明其实非常好证，就是说有逆序对那么一定会有相邻逆序对（这个是显然的吧，反证即可），那么任意一次有效交换都恰好消掉一个逆序对（就是此相邻逆序对），那不证完了么）
- 「然后转化一下就可以算这题的移动次数了（」

至于如何转化，我们考虑将它的重排看成一个置换 $a$，那么最小交换次数显然就是 $a$ 的逆序对数（这看似是一个挺常用的套路）。但是本题中字符串里可能有相同元素，那怎么知道它重排后到底哪个是原先的哪个位置呢？这也很简单，只需要贪心的，对于每个字符，在新串中把所有等于它的位置的 $a$ 值按照原串里面所有它的位置从小到大顺着排即可，这样显然可以控制逆序对最少化。

然后这个就是 DP 可以算的了。我们每次枚举上一个字符转移，然后算上当前位置作为逆序对中右边那个的贡献，显然只跟之前的三种字符的个数有关。具体怎么算我们可以在三种字符的位置序列里面二分，但也可以预处理，做到三方复杂度。

**_[code]( https://www.luogu.com.cn/paste/mecd62fj )_**



---

## 作者：lijunxi20231818 (赞：2)

[CF 传送门](https://codeforces.com/contest/771/problem/D)

# 前言

写题解时 remote judge 已经挂了，故提交在 codeforces 上。

[AC 记录](https://codeforces.com/contest/771/submission/289342514)

![](https://cdn.luogu.com.cn/upload/image_hosting/uygzm7zz.png)

# 解法


## 性质

1) 一个显然的性质：所有不是 `V` 或 `C` 的字母都是等效的，我们可以进行统一，为了方便阅读，我们统一为 `_`。

2) 求交换的次数就是逆序对个数，我们可以一点点加入字符，计算新字符和已经考虑字符的贡献即可，考虑动态规划。

## dp 设计

$dp_{o,v,k}$ 表示已经考虑了 $o$ 个字符 `_`，$v$ 个字符 `V`，$k$ 个字符 `K` 时的最小交换次数。

可以理解为我们新建一个队列，每次“考虑一个字符”即在队列中加入一个字符。

又合法的字符串要求没有字串 `VK`，我们加入第四个状态 $type$ 记录这个串的最后一位是什么。

> $type=0$，表示最后一位是 `_`。
>
> $type=1$，表示最后一位是 `V`。
>
> $type=2$，表示最后一位是 `K`。

最后的 dp 状态就是 $dp_{o,v,k,type}$。

## dp 转移

我们枚举 $4$ 个状态，用 $dp_{o,v,k,type}$ 向 $dp_{o+1,v,k,0}$，$dp_{o,v+1,k,1}$，$dp_{o,v,k+1,2}$ 转移。

接下来考虑如何计算加入（新考虑）一个字符时，新字符的贡献。

方便叙述，记这个字符的位置为 $nxt$。

根据性质 $2$ 我们要计算的是逆序对个数：

---

~~证明~~解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/dqj14i4r.png)

(图中 `V1` 表示从前往后第 $1$ 个 `V`)

如图所示，假设当前状态为 $v=2,k=4,o=2$，接下来考虑加入 `V3` 到队尾，此时我们要将 `V3` 转到 `_2`、`K5`、`K6` 的后面，相当于求 `V3` 和**队中字符**构成的逆序对个数，对于此时的 `V3` 而言，贡献是 $2$。（此时 $o=2$ 没有考虑 `_3`，故不要计算 `_3`）

具体而言，是在已经考虑的 $o + v + k$ 个字符中，统计位置 $\gt nxt$ 的字符个数。

但是，在一个所以字符都相同的字串（如 `VVVVV`）中交换是**没有意义**的，于是我们排除掉与新字符同类的贡献。

---

以上的内容可以通过维护前缀和的方式预处理：
```cpp
void init_sum(){
  //pos[type][i]表示type型字符中，从前往后第i个的位置
	rep(i, 1, n){
		rep(j, 1, cnt[0]){
			sum[0][i][j] = sum[0][i][j - 1] + (pos[0][j] > i);
		}
	}
	rep(i, 1, n){
		rep(j, 1, cnt[1]){
			sum[1][i][j] = sum[1][i][j - 1] + (pos[1][j] > i);
		}
	}
	rep(i, 1, n){
		rep(j, 1, cnt[2]){
			sum[2][i][j] = sum[2][i][j - 1] + (pos[2][j] > i);
		}
	}
}
```
然后我们枚举 $4$ 个状态，转移即可。

注意新字符为 `K` 时要判断前一个是否是 `V` 实现就是判断 $type$ 是否是 $1$。

```cpp
void init_dp(){
	rep(_, 0, cnt[0]){
		rep(v, 0, cnt[1]){
			rep(k, 0, cnt[2]){
				rep(type, 0, 2){
                    //当前已经是inf时不转移
					if(dp[_][v][k][type] >= 0x3f3f3f3f) continue;
                    //cnt[type]表示type类字符的个数，要判断还有没有能加的type类
					if(_ < cnt[0]){
						int nxt = pos[0][_ + 1];
						dp[_ + 1][v][k][0] = min(dp[_ + 1][v][k][0], dp[_][v][k][type] + sum[1][nxt][v] + sum[2][nxt][k]);
					}
					if(v < cnt[1]){
						int nxt = pos[1][v + 1];
						dp[_][v + 1][k][1] = min(dp[_][v + 1][k][1], dp[_][v][k][type] + sum[0][nxt][_] + sum[2][nxt][k]);
					}
					if(k < cnt[2] && type != 1){//注意判断type
						int nxt = pos[2][k + 1];
						dp[_][v][k + 1][2] = min(dp[_][v][k + 1][2], dp[_][v][k][type] + sum[0][nxt][_] + sum[1][nxt][v]);
					}
				}
			}
		}
	}
}
```

最后的 $ans$ 取 $\min _{type=0}^2 dp_{cnt[0],cnt[1],cnt[2],type}$ 即可。

## dp 初始化

$dp_{0,0,0,0}$ 为 $0$，其他全部 $+\infty$。

## 警钟长鸣(易错)
$dp$ 初始值的 $type$ 状态值不能和 `V` 对应的状态值相等！！！！！否则第一次递推时 `K` 会判定为不可取！！！！！

如果你的 `V` 对应的 $type$ 为 $0$，则要**特别注意**。

# 代码实现

**注：代码中的状态 `_` 即为文中的 $o$。**

```cpp
#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i <= r; i++)
using namespace std;
const int maxn = 80;
int n, ans = INT_MAX;
char s[maxn];
int id(char c){//求字符c的type值
	if(c == '_') return 0;
	if(c == 'V') return 1;
	if(c == 'K') return 2; 
}
int pos[3][maxn], cnt[3], sum[3][maxn][maxn];//对于id字母，在前j个这个字母中，位置>i的个数 
int dp[maxn][maxn][maxn][3];
void init_sum(){
	rep(i, 1, n){
		rep(j, 1, cnt[0]){
			sum[0][i][j] = sum[0][i][j - 1] + (pos[0][j] > i);
		}
	}
	rep(i, 1, n){
		rep(j, 1, cnt[1]){
			sum[1][i][j] = sum[1][i][j - 1] + (pos[1][j] > i);
		}
	}
	rep(i, 1, n){
		rep(j, 1, cnt[2]){
			sum[2][i][j] = sum[2][i][j - 1] + (pos[2][j] > i);
		}
	}
}
void init_dp(){
	rep(_, 0, cnt[0]){
		rep(v, 0, cnt[1]){
			rep(k, 0, cnt[2]){
				rep(type, 0, 2){
					if(dp[_][v][k][type] >= 0x3f3f3f3f) continue;
					if(_ < cnt[0]){
						int nxt = pos[0][_ + 1];//新字符的位置
						dp[_ + 1][v][k][0] = min(dp[_ + 1][v][k][0], dp[_][v][k][type] + sum[1][nxt][v] + sum[2][nxt][k]);
					}
					if(v < cnt[1]){
						int nxt = pos[1][v + 1];
						dp[_][v + 1][k][1] = min(dp[_][v + 1][k][1], dp[_][v][k][type] + sum[0][nxt][_] + sum[2][nxt][k]);
					}
					if(k < cnt[2] && type != 1){
						int nxt = pos[2][k + 1];
						dp[_][v][k + 1][2] = min(dp[_][v][k + 1][2], dp[_][v][k][type] + sum[0][nxt][_] + sum[1][nxt][v]);
					}
				}
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	cin >> (s + 1);
	rep(i, 1, n) if(s[i] != 'K' && s[i] != 'V') s[i] = '_';
	rep(i, 1, n){
		int add = id(s[i]);
		pos[add][++cnt[add]] = i;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0][0] = 0;
    //警钟长鸣
	init_sum();
	init_dp();
	for(int type = 0; type < 3; type++){
		ans = min(ans, dp[cnt[0]][cnt[1]][cnt[2]][type]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：bloodstalk (赞：2)

# Solution

DP 好题，模拟赛出了这个题的 $O(n^3)$ 加强版。

这题首先需要知道一个经典结论：**一个数列冒泡排序的次数等于逆序对数**。考虑证明：

首先证明如果数列有逆序对，那么一定有相邻逆序对，这个你可以通过反证法，证明存在逆序对但不存在相邻逆序对这种情形不会出现。那么任意一种有效交换都将消去任意一组相邻逆序对，然后就证完了。

通过这个，我们把这个结论转化一下，就能得到这个题 DP 的转移代价了。

容易发现，这个题除了 $V,K$ 这两个字符外，其余的字符都可以看成是一种字符（我们设其为 $Z$），所以一共有三种字符，我们通过对这三种字符设计 DP 来刻画 DP 状态。

还有一个我赛时没想出来的点，但是也很容易理解，就是你的终止状态中，每种字符内部的相对顺序一定不会改变，因为交换了，状态相同，操作次数增加，一定不优秀，根据这两个性质，我们可以尝试刻画状态了。

设 $f_{i,j,k}$ 表示 $Z$ 这种字母考虑到前 $i$ 个，$V$ 这种字符考虑到前 $j$ 个，$K$ 这种字符考虑到前 $k$ 个时，一共 $i+j+k$ 个字符进行重排到合法状态的最小操作数。

但是仔细想一下，你会发现这个刻画并不完整，因为我们不能在一个串尾是 $V$ 的地方再放一个 $K$，所以增设一维 $f_{i,j,k,t}$ 表示 .....，且末尾的字符是 $t$ 的最小操作数。

考虑转移可以转移到哪里：

* 若 $i<|Z|$($|Z|$ 表示这种字符有几个，下面同理)，那么 $f_{i+1,j,k,1}$ 可由 $f_{i,j,k,t}$ 转移而来（将第 $i+1$ 个字符 $Z$ 放到 $i+j+k+1$ 这个位置上，后面也是同理）；

* 若 $j<|V|$，那么 $f_{i,j+1,k,2}$ 可由 $f_{i,j,k,t}$ 转移而来；

* 若 $k<|K|$ 且 $t \not= 2$，那么 $f_{i,j,k+1,3}$ 可由 $f_{i,j,k,t}$ 转移而来。

再考虑转移的代价是什么，由于我们现在已经把字符 $Z$ 的前 $i$ 个字符，字符 $V$ 的前 $j$ 个字符，字符 $K$ 的前 $k$ 个字符通过一系列操作放到了答案串的前 $i+j+k$ 个位置上，这些字符的贡献我们已经在 $f_{i,j,k,t}$ 中计算出来了。那么我们要把 $x$ 这个字符放到第 $i+j+k+1$ 个位置上，考虑它的贡献时，就不需要管这 $i+j+k$ 个字符了。我们设字符 $x$ 出现的位置是 $p$,那么，这个字符的转移花费即为：

从第 $i+1$ 个字符 $Z$ 开始，原位置 $<p$ 的个数 $+$ 从第 $j+1$ 个字符 $Y$ 开始，原位置 $<p$ 的个数 $+$ 从第 $k+1$ 个字符 $K$ 开始，原位置 $<p$ 的个数，这就是我们将 $x$ 放到 $i+j+k+1$ 这个位置的时候，需要交换的次数，这也就是一个逆序对数。而这个东西你可以通过一个类似于 $cost_{i,j}$ 表示在前 $j$ 个某种相同字符中有多少个位置 $>i$，这个你可以 $O(n^2)$ 预处理，转移的时候就可以 $O(1)$ 计算了，综上，时间复杂度就是 DP 的时候的 $O(n^3)$，并且跑不满；空间复杂度 $O(n^3)$，可以简单滚动数组优化到 $O(n^2)$，所以这题出到 $1000$ 也是可行的。

# Code
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
#define fir first
#define sec second
#define pii std::pair<int,int>
const int N = 1e3 + 5;
const int INF = 1e9;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,cnt1,cnt2,cnt3;
int f[2][N][N][4];
int vec[4][N],cost[4][N][N];
char ch[N];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void Init()
{
	for(re int i=1;i<=n;i++)
	{
		if(ch[i] == 'Z') cnt1++ , vec[1][cnt1] = i;
		if(ch[i] == 'V') cnt2++ , vec[2][cnt2] = i;
		if(ch[i] == 'K') cnt3++ , vec[3][cnt3] = i;
	}
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=cnt1;j++)//在前 j 个某种相同字符中有多少个位置 > i
			cost[1][i][j] = cost[1][i][j-1] + (vec[1][j] > i);
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=cnt2;j++)
			cost[2][i][j] = cost[2][i][j-1] + (vec[2][j] > i);
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=cnt3;j++)
			cost[3][i][j] = cost[3][i][j-1] + (vec[3][j] > i);
}

signed main()
{
	n = read();
	cin >> (ch+1);
	for(re int i=1;i<=n;i++) if(ch[i] != 'V' && ch[i] != 'K') ch[i] = 'Z';
	Init();
	memset(f , 0x3f , sizeof f);
	int now = 1;
	f[0][0][0][1] = 0;
	for(re int i=0;i<=cnt1;i++)
	{
		now ^= 1;
		for(re int j=0;j<=cnt2;j++)
			for(re int k=0;k<=cnt3;k++)
				for(re int t=1;t<=3;t++)
				{
					if(f[now][j][k][t] >= 0x3f3f3f3f) continue;
					if(i < cnt1)//Z
						f[now^1][j][k][1] = min(f[now^1][j][k][1],f[now][j][k][t]+cost[2][vec[1][i+1]][j]+cost[3][vec[1][i+1]][k]);
					if(j < cnt2)//V
						f[now][j+1][k][2] = min(f[now][j+1][k][2],f[now][j][k][t]+cost[1][vec[2][j+1]][i]+cost[3][vec[2][j+1]][k]);
					if(k < cnt3 && t != 2)
						f[now][j][k+1][3] = min(f[now][j][k+1][3],f[now][j][k][t]+cost[1][vec[3][k+1]][i]+cost[2][vec[3][k+1]][j]);
				}
	}
	int ans = INF;
	for(re int t=1;t<=3;t++) ans = min(ans,f[now][cnt2][cnt3][t]);
	cout << ans;
 	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

gitgud #2

将：

 1. `V` 为 1 类字符
 2. `K` 为 2 类字符
 3. 其余为 0 类字符

进而将每一个位置进行标号，从 $0$ 至 $n-1$。  

**引理**：如果钦定最终方案，则最少步数为最终排列的逆序对个数。  
**证明**：考虑倒着走，最少步数解法里，任何一个相邻交换会修改恰好一个逆序对（可以抽象为冒泡排序过程。）

**引理**：类型内相对顺序在最优解里不会改变。  
**证明**：对于任意类，如果这一类标号为 $x_0,x_1,\dots,x_k$ 其中 $x_i<x_{i+1}$，则对于任何排列 $[\pi_0,\pi_2,\dots,\pi_k]$ 所有 $[\dots,x_{\pi_0},\dots,x_{\pi_1},\dots,\dots,\dots,x_{\pi_k},\dots]$ 必定均合法或均不合法；$[\dots,x_0,\dots,x_1,\dots,\dots,\dots,x_k,\dots]$ 逆序对数肯定最低。

于是如果钦定一个 012 串（例如 02111）那么肯定可以推到对应标号以及逆序对数。

考虑逐个构造答案 012 串。  
令 $dp_{x\ y\ z\ i}$ 为前 $x+y+z$ 字符里有 $x$ 个 $0$，$y$ 个 $1$，$z$ 个 $2$，最后字符为 $i$ 的最少逆序对个数。

则 $dp_{x\ y\ z\ i}=\min(dp_{x-[i=0]\ y-[i=1]\ z-[i=2]\ j})+C(x,y,z,i)$，其中 $j$ 为所有 $0\le j\le2$ 使得 $i$ 可以在 $j$ 后面，并且 $C$ 是 $i$ 放在第 $x+y+z$ 字符所产生的逆序对数量。

通过预处理第 $i$ 类型的第 $j$ 出现位置，我们可以知道这 $i$ 对应原串的什么标号。令这值为 $ld$。则所有别的类型里的出现在 $ld$ 后面但是属于 $x\ y\ z$ 会产生逆序对，这数量为 $C$。

总共时间复杂度 $O(n^3/27)$。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int cn[3];
int iv[3][75],ps[3][75];
int dp[75][75][75][3];

int dfs(int x,int y,int z,int i){
	if(!(x+y+z))return 0;
	int c=(i==0)?x:((i==1)?y:z);
	int ld=ps[i][c-1];
	if(!c)return 1e9;
	int g=0;
	if(x&&ps[0][x-1]>ld)g+=x-iv[0][ld];
	if(y&&ps[1][y-1]>ld)g+=y-iv[1][ld];
	if(z&&ps[2][z-1]>ld)g+=z-iv[2][ld];
	// cout<<x<<' '<<y<<' '<<z<<' '<<i<<' '<<ld<<' '<<g<<' '<<iv[2][ld]<<endl;
	if(dp[x][y][z][i]!=-1)return dp[x][y][z][i];
	int X=x-(i==0),Y=y-(i==1),Z=z-(i==2);c=1e9;
	rep(j,3)if(i!=2||j!=1)c=min(c,dfs(X,Y,Z,j));
	return dp[x][y][z][i]=c+g;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;cin>>n;
	rep(i,n){
		char c;cin>>c;
		if(c=='V')iv[1][i]++,ps[1][cn[1]++]=i;
		else if(c=='K')iv[2][i]++,ps[2][cn[2]++]=i;
		else iv[0][i]++,ps[0][cn[0]++]=i;
	}
	rep1(i,n-1)rep(j,3)iv[j][i]+=iv[j][i-1];
	// rep(i,n)rep(j,3)iv[j][i]=cn[j]-iv[j][i];
	memset(dp,-1,sizeof dp);
	int x=1e9;
	rep(i,3)x=min(x,dfs(cn[0],cn[1],cn[2],i));
	cout<<x<<endl;
}
```

---

## 作者：__ycx2010__ (赞：0)

### CF771D. Bear and Company

### 题目描述

给定长度为 $n$ 的字符串，每次操作可以交换相邻两个位置字符，求最少操作次数使得字符串不包含子串 `VK`。

$n\leq 75$。

### 思路

首先对于不是 $V$ 或 $K$ 的，用 $Z$ 代替。

发现相同字符之间不改变顺序，如果我们有了最终的状态 $T$，那么 $T$ 中第 $i$ 个 $j$ 字符与 $S$ 中第 $i$ 个 $j$ 字符相对应，$S_{p1} \longleftrightarrow T_{p2}$，设 $a_{p2}=p1$。

于是从 $S$ 到 $T$ 的最小步数为 $a$ 的逆序对个数。

综上，设 $f_{i,j,k}$ 表示 $T$ 中前 $i+j+k$ 个字符中有 $i$ 个 $V$，$j$ 个 $K$，$k$ 个 $Z$ 情况下最小的逆序对数，简单 dp 即可，复杂度 $O(n^3)$。

[submission](https://codeforces.com/contest/771/submission/292429791)

---

