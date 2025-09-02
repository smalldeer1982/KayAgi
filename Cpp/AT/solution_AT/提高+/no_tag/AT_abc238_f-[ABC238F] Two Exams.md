# [ABC238F] Two Exams

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc238/tasks/abc238_f

高橋王国にて、 $ 1 $ から $ N $ までの番号のついた $ N $ 人の国民が競技プログラミングの試験に参加しました。  
 試験は $ 2 $ 回からなり、人 $ i $ は $ 1 $ 回目の試験で $ P_i $ 位、 $ 2 $ 回目の試験で $ Q_i $ 位となりました。  
 なお、どちらの試験においても、複数人が同じ順位になることはありませんでした。すなわち、順位を表す数列 $ P,Q $ はそれぞれ $ (1,2,...,N) $ の順列です。

高橋王国の大統領であるいろはちゃんは、この試験の結果に基づいて、 $ N $ 人の中から競技プログラミングの世界大会に出場する $ K $ 人の代表を決めることになりました。  
 代表を決めるにあたって、以下が成立していなければなりません。

- 人 $ x $ が代表であり、人 $ y $ が代表でないような人の組 $ (x,y) $ であって、 $ P_x\ >\ P_y $ かつ $ Q_x\ >\ Q_y $ であるようなものが存在してはならない。
  - 言い換えると、 $ 2 $ 回の試験の双方で人 $ y $ が人 $ x $ よりも小さい順位を取っているにも拘らず、人 $ x $ が代表で人 $ y $ が代表でないということがあってはならない。

いろはちゃんは、ひとまず上記の条件を満たす代表の選び方の数を知りたいので、この数を求めてください。  
 ただし、この数は非常に大きくなる場合もあるので、 $ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 300 $
- $ 1\ \le\ K\ \le\ N $
- $ P,Q $ は $ (1,2,...,N) $ の順列である。

### Sample Explanation 1

\- 人 $ 1 $ と人 $ 2 $ を代表にすることは問題ありません。 - 人 $ 1 $ と人 $ 3 $ を代表にすると、双方の試験で人 $ 4 $ が人 $ 3 $ よりも小さい順位を取っているため、 $ (x,y)=(3,4) $ に対して問題文中の条件に違反します。 - 人 $ 1 $ と人 $ 4 $ を代表にすることは問題ありません。 - 人 $ 2 $ と人 $ 3 $ を代表にすると、 $ (x,y)=(3,1) $ に対して問題文中の条件に違反します。 - 人 $ 2 $ と人 $ 4 $ を代表にすることは問題ありません。 - 人 $ 3 $ と人 $ 4 $ を代表にすると、 $ (x,y)=(3,1) $ に対して問題文中の条件に違反します。 結局、求める答えは $ 3 $ 通りです。

### Sample Explanation 2

$ 33 $ 人から $ 16 $ 人を選ぶ $ \binom{33}{16}\ =\ 1166803110 $ 通りの全てにおいて、問題文中の条件を満たします。 よって、 $ 1166803110 $ を $ 998244353 $ で割った余りである $ 168558757 $ を出力することとなります。

## 样例 #1

### 输入

```
4 2
2 4 3 1
2 1 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
33 16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1```

### 输出

```
168558757```

## 样例 #3

### 输入

```
15 7
4 9 7 5 6 13 2 11 3 1 12 14 15 10 8
4 14 9 12 7 15 1 2 8 11 3 5 13 6 10```

### 输出

```
23```

# 题解

## 作者：JSQ_ (赞：3)

# 思路

首先按照 $P$ 从小到大排序，这样的话只用考虑 $Q$。

设 $f_{i,j,k}$ 表示从前 $i$ 个数中选 $j$ 个，其中未选的人的 $Q$ 值最小为 $k$。

考虑第 $i$ 个人选活不选：

* 选，需要满足 $Q_i < k$，因为 $P_i \ge k$，$f_{i,j,k}=f_{i-1,j-1,k}$。
* 不选，$f_{i,j,\min(k,Q_i)}=f_{i-1,j,k}$

最后答案为 $\sum^{n+1}_{i=1}{f_{n,K,i}}$。

时间复杂度为 $O(N^3)$

# 代码

```cpp
/*Code by Ji-Siqi*/
/*Begin*/
#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
using ll = long long;
using cint = const int;

cint N = 305;

ll f[N][N][N];

int main() {
	int n, K;
	pair <int, int> p[N];
	cin >> n >> K;
	for (int i = 1; i <= n; i++) 
		cin >> p[i].first;
	for (int i = 1; i <= n; i++) 
		cin >> p[i].second;
	sort(p + 1, p + n + 1);
	f[0][0][n + 1] = 1;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j <= K; j++) 
			for (int k = 1; k <= n + 1; k++) {
				if (p[i + 1].second < k && j != K) 
					f[i + 1][j + 1][k] = (f[i + 1][j + 1][k] + f[i][j][k]) % mod;
				f[i + 1][j][min(k, p[i + 1].second)] = (f[i + 1][j][min(k, p[i + 1].second)] + f[i][j][k]) % mod;
			}
	ll ans = 0;
	for (int i = 1; i <= n + 1; i++) 
		ans = (ans + f[n][K][i]) % mod;
	cout << ans;

	return 0;
}
/*End*/
```

---

## 作者：appear_hope (赞：2)

题意简化：

给定长度为 $n$ 的序列 $P$ 和 $Q$，在这 $1 \sim n$ 中选择 $k$ 个整数 $x$，使得不存在一个没有被选的整数 $y$，$P_y < P_x$ 且 $Q_y < Q_x$，问有多少种方案。

直接求解过于复杂，我们可以通过排序的方式消掉一维条件，然后现在只有 $Q_x < Q_y$ 这一条件。

考虑状态设计：

状态：$(i, j, s)$ 表示考虑到排序后第 $i$ 个整数，选择了 $j$ 个数字，在前 $i$ 个整数中没被选择的整数 $y$ 的 $\min \{Q_y \}$ 为 $s$。

转移：

$(i, j, s) \to (i + 1, j + 1, s)$，其中 $Q_{i + 1} < s, j + 1 < n,i + 1 \le n$。

选择第 $i$ 个整数，因为 $P$ 序列已经排好序了，所以要想选择第 $i$ 个整数只能 $Q_i < s$ 才是合法状态。

$(i, j, s) \to (i + 1, j, \min \{ s, Q_{i + 1} \})$，其中 $i + 1 \le n$。

不选择第 $i$ 个整数。

拓扑序：

$i$ 从小到大。

时空复杂度：

时间复杂度：$O(n ^ 3)$。

空间复杂度：$O(n ^ 3)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define pir pair<int, int>

using namespace std;

const int N = 305;
const int mod = 1e9 + 7;

pir a[N];
int n, k, ans, dp[N][N][N];

int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i].first;
	}
	for(int i = 1; i <= n; i++){
		cin >> a[i].second;
	}
	sort(a + 1, a + n + 1, [](const pir &a, const pir &b){ return a.first < b.first; });
	dp[0][0][n + 1] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= k; j++){
			for(int s = 1; s <= n + 1; s++){
				if(a[i + 1].second < s && j < k){
					dp[i + 1][j + 1][s] = (dp[i + 1][j + 1][s] + dp[i][j][s]) % mod;
				}
				dp[i + 1][j][min(s, a[i + 1].second)] = (dp[i + 1][j][min(s, a[i + 1].second)] + dp[i][j][s]) % mod;
			}
		}
	}
	for(int i = 1; i <= n + 1; i++){ // n 可能等于 k，注意细节
		ans = (ans + dp[n][k][i]) % mod;
	}
	cout << ans;
	return 0;
}
```

切勿抄袭。

---

## 作者：_Kenma_ (赞：1)

# AT_abc238_f 解题报告

## 前言

一道 AT 风格的 AT 计数题。

## 思路分析

考虑朴素 DP。设 $f_{i,j,min_p,min_q}$ 表示在前 $i$ 个数中选 $j$ 个，未选择的数中，$p$ 的最小值为 $min_p$，$q$ 的最小值为 $min_q$。考虑每个数选或不选转移即可。

但是这样做的复杂度是 $O(n^3k)$ 的。考虑优化掉一维。

注意到 $p$ 和 $q$ 都是排列，考虑将 $p$ 升序排序，这样 $i$ 的大小可以代表 $p_i$ 的大小。相应地，设 $f_{i,j,min_q}$，各变量含义同上。

考虑怎样转移，不难发现：

$$f_{i,j,k}=f_{i,j,k}+f_{i-1,j-1,k} \cdot [q_i<k]$$

$$f_{i,j,min(q_i,k)}=f_{i,j,min(q_i,k)}+f_{i-1,j,k}$$

第一个柿子是选 $q_i$ 的情况，第二个是不选的情况。注意转移的合法性。

边界为：$f_{0,0,n+1}=1$。

这样我们把复杂度优化到了 $O(n^2k)$。可以通过本题。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,k,ans,f[305][305][305];
struct node{
	int p,q;
}h[305];
bool cmp(node a,node b){
	return a.p<b.p;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>h[i].p;
	}
	for(int i=1;i<=n;i++){
		cin>>h[i].q;
	}
	sort(h+1,h+1+n,cmp);
	f[0][0][n+1]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(i,k);j++){
			for(int t=1;t<=n+1;t++){
				if(h[i].q<t && j) f[i][j][t]=(f[i][j][t]+f[i-1][j-1][t])%mod;
				f[i][j][min(t,h[i].q)]=(f[i][j][min(t,h[i].q)]+f[i-1][j][t])%mod;
			}
		}
	}
	for(int i=1;i<=n+1;i++){
		ans=(ans+f[n][k][i])%mod;
	} 
	cout<<ans;
	return 0;
}
```
## 后记

一道不错的 DP 题，DP 转移比较自然，瓶颈在于排序。

但是我只独立想出了 $O(n^3k)$。

---

## 作者：2020luke (赞：1)

# [[ABC238F] Two Exams](https://www.luogu.com.cn/problem/AT_abc238_f)

## 思路解析

这题很麻烦，因为有两个维度。所以可以想到先按照第一维排序，这样就不需要考虑第二维的问题。其次再发现数据范围小，可以想到能用 dp 做，接下来就考虑如何 dp。首先我们要知道我们遍历到了第几个公民，同时还要知道还剩下几个代表名额，同时我们还需要思考第二维对选择代表的影响。于是想到 $f_{i,j,k}$ 表示考虑完了前 $i$ 个人，选了 $j$ 个公民做代表，在没有被选为代表的人中第二维的值最小的值是 $k$。原因是我们已经按照第一位排好了序，当前的人在第一维上的排名一定落后于第二维是 $k$ 的人，如果当前人在第二维上依然落后于 $k$，就必定不可以选。

然后考虑状态转移，分为选和不选两种情况。

- 如果不选，$j$ 不变，但需要更新 $k$，所以可得 $f_{i,j,\min(k,q_{i})} \gets f_{i-1,j,k}$

- 如果选，则 $j$ 需要加一，同时比较 $q_{i}$ 和 $k$，可得 $f_{i,j,k} \gets f_{i-1,j-1,k}$

最后的答案就是 $\sum_{i=1}^{n+1}f_{n,m,i}$。

细节：初始时没有一个人不选，$k$ 为 $n+1$，以及统计答案时也有可能没有一个人不选，记得遍历到 $n+1$。

时间复杂度：第一维枚举每一个人，第二维枚举选几个人，第三维枚举当前最小值，因此为 $O(mn^{2})$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define fir first
#define sec second
const int N = 310, mod = 998244353;
int n, m, f[N][N][N];
PII a[N];
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].fir; 
	}
	for(int i = 1; i <= n; i++) {
		cin >> a[i].sec;
	}
	sort(a + 1, a + n + 1, [](PII x, PII y) { return x.fir < y.fir;});
	f[0][0][n + 1] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			for(int k = 1; k <= n + 1; k++) {
				f[i][j][min(a[i].sec, k)] = (f[i][j][min(a[i].sec, k)] + f[i - 1][j][k]) % mod;	//不选的情况
				if(j > 0 && a[i].sec < k) {	//判断，不能使当前人的排名落后于 k
					f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k]) % mod; //选的情况
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n + 1; i++) ans = (ans + f[n][m][i]) % mod;	//统计以每一个数结尾的情况
	cout << ans;
	return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先对于这种题目多半是要先以 $a_i$ 排序的，这样我们可以消除 $a_i$ 的限制，只需要考虑 $b_i$ 的限制即可。

定义 $dp_{i,j}$ 表示在前 $i$ 个人中选 $j$ 个人的合法方案数。但是这样不知道前面选取人的 $b_i$ 的大小。

因此，重新定义 $dp_{i,j,k}$ 表示在前 $i$ 个人中选 $j$ 个人，且在没有选的人中 $\min(b_p) = k$ 的合法方案数。

对于第 $i$ 个人，有两种情况：

1. 不选，那么容易得到状态转移方程 $dp_{i,j,\min(k,b_i)} = dp_{i - 1,j,k}$。

2. 选，那么状态转移方程为 $dp_{i,j + 1,k} = dp_{i - 1,j,k}$。

答案就是 $\sum_{i = 1}^{n + 1}dp_{n,m,i}$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 310,mod = 998244353;
int n,m,ans;
int dp[N][N][N];
pii arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++) arr[i].fst = read();
	for (re int i = 1;i <= n;i++) arr[i].snd = read();
	sort(arr + 1,arr + n + 1);
	dp[0][0][n + 1] = 1;
	for (re int i = 1;i <= n;i++){
		for (re int j = 0;j <= min(i,m);j++){
			for (re int k = 1;k <= n + 1;k++){
				dp[i][j][min(k,arr[i].snd)] = (dp[i][j][min(k,arr[i].snd)] + dp[i - 1][j][k]) % mod;
				if (k > arr[i].snd) dp[i][j + 1][k] = (dp[i][j + 1][k] + dp[i - 1][j][k]) % mod;
			}
		}
	}
	for (re int i = 1;i <= n + 1;i++) ans = (ans + dp[n][m][i]) % mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：apiad (赞：1)

$n$ 是 $300$ 级别，送给你的是 $O(n^3)$ 时间复杂度的解法，首先考虑区间 Dp，我们可以先按照 $a$ 这一维度排序，然后就只用考虑 $b$ 这边了。$dp_{i,j,x}$ 代表的是考虑到第 $i$ 个点，选了 $j$ 人了，此时未选择的人中 $b_i$ 最小是 $x$。转移的方式是：如果可以新加入人：$dp_{i+1,j+1,x}$ 加上 $dp_{i,j,x}$。如果不加人：$dp_{i+1,j,\min(x,b_{i+1})}$ 加上 $dp_{i,j,k}$。最后的答案是 $\sum_{i=0}^{n+1} dp_{n,k,i}$。状态表示中写了 $b_i$ 但实际上排序的需要，我们可以开一个 pair 来解决。[link](https://atcoder.jp/contests/abc238/submissions/50708939)。

---

