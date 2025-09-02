# 選挙で勝とう (Let&#39;s Win the Election)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2022ho/tasks/joi2022ho_c

JOI 国は $ N $ 個の州からなり，それぞれ $ 1 $ から $ N $ までの番号が付けられている．$ 2022 $ 年，JOI 国では大統領選挙が開催されることになった．この選挙では各州で投票が行われ，勝った候補者がその州に割り当てられている $ 1 $ 票を獲得する．

さて，大統領選挙に出馬する理恵さんは，演説によって自身への信頼度を上げ，選挙で勝とうと考えた．演説により，具体的には次のことが起こる．

- 州 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) での合計演説時間が $ A_i $ 時間に達すると，その州に割り当てられている $ 1 $ 票を獲得できる．
- 州 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) での合計演説時間が $ B_i $ 時間に達すると，協力者 $ 1 $ 人を得ることができる．得られた協力者は，それ以降演説を行い，合計演説時間を増やすことができる．
- ただし，州 $ i $ からの協力者を得られない場合もあり，その場合は $ B_i\ =\ -1 $ として情報が与えられる．それ以外の場合は，$ B_i\ \geqq\ A_i $ であることが保証される．

なお，州 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) で獲得した協力者が州 $ i $ 以外で演説をすることや，$ 1 $ つの州で同時に $ 2 $ 人以上が演説をすることも可能である．たとえば，ある州で同時に $ 2 $ 人が $ x $ 時間演説をした場合，この州の合計演説時間は $ 2x $ 時間増加する．ただし，演説時間が整数である必要はない．また，州の間を移動する時間は無視できるものとする．

投票日が近いので，理恵さんは目標の $ K $ 票をできるだけ早く獲得したい．

州の数と各州の情報が与えられたとき，$ K $ 票を集めるまでにかかる時間の最小値を求めるプログラムを作成せよ．

- - - - - -

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 500 $．
- $ 1\ \leqq\ K\ \leqq\ N $．
- $ 1\ \leqq\ A_i\ \leqq\ 1\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ A_i\ \leqq\ B_i\ \leqq\ 1\,000 $ または $ B_i\ =\ -1 $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### 小課題

1. ($ 5 $ 点) $ B_i\ =\ -1 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
2. ($ 5 $ 点) $ B_i\ =\ -1 $ または $ B_i\ =\ A_i $ ($ 1\ \leqq\ i\ \leqq\ N $)．
3. ($ 11 $ 点) $ N\ \leqq\ 7 $．
4. ($ 12 $ 点) $ N\ \leqq\ 20 $．
5. ($ 33 $ 点) $ N\ \leqq\ 100 $．
6. ($ 11 $ 点) $ K\ =\ N $．
7. ($ 23 $ 点) 追加の制約はない．

- - - - - -

### Sample Explanation 1

以下のような順序で選挙活動を行うと，$ 5.5 $ 時間ですべての州の票を獲得することができる． 1. 理恵さんが州 $ 2 $ で $ 2 $ 時間演説を行い，その州の票を得る． 2. 理恵さんが州 $ 2 $ でさらに $ 1 $ 時間演説を行い，その州の協力者を得る． 3. 理恵さんと協力者 $ 1 $ 人が州 $ 3 $ で $ 2 $ 時間演説を行い，その州の票を得る． 4. 理恵さんと協力者 $ 1 $ 人が州 $ 1 $ で $ 0.5 $ 時間演説を行い，その州の票を得る． この入力例は小課題 $ 3,\ 4,\ 5,\ 6,\ 7 $ の制約を満たす． - - - - - -

### Sample Explanation 2

以下のような順序で選挙活動を行うと，$ 32 $ 時間で $ 4 $ 票を獲得することができる． 1. 理恵さんが州 $ 1 $ で $ 4 $ 時間演説を行い，その州の票を得る． 2. 理恵さんが州 $ 2 $ で $ 11 $ 時間演説を行い，その州の票を得る． 3. 理恵さんが州 $ 3 $ で $ 6 $ 時間演説を行い，その州の票を得る． 4. 理恵さんが州 $ 6 $ で $ 11 $ 時間演説を行い，その州の票を得る． この入力例は小課題 $ 1,\ 2,\ 3,\ 4,\ 5,\ 7 $ の制約を満たす． - - - - - -

### Sample Explanation 3

以下のような順序で選挙活動を行うと，$ 11.5 $ 時間で $ 3 $ 票を獲得することができる． 1. 理恵さんが州 $ 4 $ で $ 7 $ 時間演説を行い，その州の票と協力者を得る． 2. 理恵さんが州 $ 1 $ で $ 4 $ 時間演説を行い，その州の票を得る．同時に，協力者 $ 1 $ 人が州 $ 2 $ で $ 4 $ 時間演説を行う． 3. 理恵さんと協力者 $ 1 $ 人が州 $ 2 $ で $ 0.5 $ 時間演説を行い，その州の票を得る． この入力例は小課題 $ 2,\ 3,\ 4,\ 5,\ 7 $ の制約を満たす． - - - - - -

### Sample Explanation 4

この入力例は小課題 $ 3,\ 4,\ 5,\ 7 $ の制約を満たす． - - - - - -

### Sample Explanation 5

この入力例は小課題 $ 4,\ 5,\ 7 $ の制約を満たす．

## 样例 #1

### 输入

```
3
3
1 5
2 3
4 5```

### 输出

```
5.500000000000000```

## 样例 #2

### 输入

```
7
4
4 -1
11 -1
6 -1
12 -1
36 -1
11 -1
20 -1```

### 输出

```
32.000000000000000```

## 样例 #3

### 输入

```
5
3
4 -1
5 -1
6 -1
7 7
8 8```

### 输出

```
11.500000000000000```

## 样例 #4

### 输入

```
7
5
28 36
11 57
20 35
19 27
31 33
25 56
38 51```

### 输出

```
62.166666666666664```

## 样例 #5

### 输入

```
20
14
106 277
175 217
170 227
164 245
118 254
139 261
142 270
185 200
162 241
153 239
128 264
103 299
147 248
158 236
160 232
183 205
194 197
135 260
153 234
128 260```

### 输出

```
644.203571428571422```

# 题解

## 作者：__Louis__ (赞：1)

## 题解：AT_joi2022ho_c 選挙で勝とう (Let&#39;s Win the Election)

### 题目描述

一共有 $n$ 个人，你需要获得 $k$ 张选票。

每个人需要与你谈话 $a_i$ 个小时才会给你选票。

当然，如果你与这个人谈话时间超过了 $b_i$，他便会和你一起和别人谈话（意思是你获得选票的速度提升了 $1$）

$b_i$ 为 $-1$ 时表示这个人不能帮你谈话。现在问最小时间。

### 思路

首先，肯定是先拉人再去找选票。

然后很容易想到贪心，但是是错的，因为有一些人选 $a_i$ 比选 $b_i$ 要更划算。

所以考虑 dp。

首先，我们先枚举我们选多少个 $b_i$，转移的时候 $a_i$ 就知道其具体的时间。

设$dp_{i,j,k}$ 表示前 $i$ 个人中选了 $j$ 个 $b_i$，$k$ 个 $a_i$。 转移分为选 $a_i$，$b_i$ 和不选。

但是这样 dp 就是 $O(n^3)$，加上枚举多少人来帮忙就已经超时了。

于是，我们考虑性质。在最后一个 $b_i$ 之前，是不可能不选的，不然最后一个换到不选的坑定更优。

于是，改变 $dp_{i,j}$ 表示前面 $i$ 个人中选了 $j$ 个 $b_i$。 然后从 $dp_{i,cnt}$ 转移到答案即可。

复杂度 $O(n^3)$，瓶颈在 dp。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9 
const int maxn=1000;
struct node{
	int x,da;
}arr[maxn];
double dp[maxn][maxn];
bool cmp(node a,node b){
	return a.da<b.da;
}
int min_[maxn][maxn];
void init(int n){
	priority_queue<int> q;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=i;j<=n;j++){
			q.push(arr[j].x);
			sum+=arr[j].x;
		}
		for(int j=n-i+1;j>=1;j--){
			min_[i][j]=sum;
			sum-=q.top();
			q.pop();
		}
	}
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int cnt=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&arr[i].x,&arr[i].da);
		if(arr[i].da==-1) arr[i].da=inf;	
		else cnt++;
	}
	sort(arr+1,arr+1+n,cmp);
	init(n);
	
	double ans=1e9;
	for(int f=0;f<=cnt;f++){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=cnt;j++){
				dp[i][j]=1e9;
			}
		}
		dp[0][0]=0;
		int per=f+1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=min(i,f);j++){
				dp[i][j]=min(dp[i][j],dp[i-1][j]+arr[i].x*1.0/per);
				if(j!=0)
				dp[i][j]=min(dp[i][j],dp[i-1][j-1]+arr[i].da*1.0/j);
			}
		}
		for(int i=f;i<=k;i++){
			ans=min(ans,dp[i][f]+min_[i+1][k-i]*1.0/per);
		}
		
	}
	printf("%.2lf",ans);
} 






```

---

## 作者：Leeb (赞：1)

贪心+DP。

首先，一定是所有协作者同时在同一个州演讲，这样才最优。

然后，假设我们已经知道所有州的方案（支持、支持+协作、反对），那我们一定是先按照从小到大的顺序拿下所有“支持+协作”州，这样最优。

然后我们先考虑枚举“支持+协作”州的数量，然后 dp。

设 $f_{i, j, k}$ 表示考虑到第 $i$ 个州，有 $j$ 个支持州，有 $k$ 个“支持+协作”州，即 $k$ 个协作者的最优时间方案。dp 的时间复杂度为 $O(n^3)$，再加上枚举“支持+协作”州的数量，总时间复杂度 $O(n^4)$。考虑优化。

经过一番探索，我们可以发现：当两个“支持+协作”州之间有反对州时，将反对州与后面一个“支持+协作”州位置交换一定会更优。进一步得到：两个“支持+协作”州之间一定没有反对州。那我们就可以去枚举最后一个“支持+协作”州的位置 $i$，这样就省去了之前 $k$ 那一维，最后一个“支持+协作州”后面的答案就是 $[i + 1, n]$ 中选择 $k - i$ 个 $a_i$ 的最小和，这部分可以使用背包预处理。dp 的复杂度也降到了 $O(n^2)$，总的时间复杂度为 $O(n^3)$。可以通过。

参考代码：
```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 505
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define PII pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, k, cntb; double ans, f[N][N], v[N][N];
struct Node {
	int a, b;
	inline bool operator < (const Node &oth) const {
		return b < oth.b;
	}
} a[N];
inline int in() {
	int a = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = 1; ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
	if (f) return ~a + 1;
	return a;
}
inline void print(int x) {
	if (x < 0) putchar('-'), x = ~x + 1;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
	print(x);
	putchar(ch);
}
inline void init() {
	n = in(), k = in(); ans = inf;
	for (int i = 1; i <= n; ++i) {
		a[i].a = in(), a[i].b = in();
		cntb += (a[i].b != -1);
		a[i].b = (a[i].b != -1) ? a[i].b : inf;
	}
}
inline void work() {
	stable_sort(a + 1, a + 1 + n); mem(v, 0x7f);
	for (int i = 1; i <= n + 1; ++i) v[i][0] = 0;
	for (int i = n; i; --i) {
		for (int j = 1; j <= n - i + 1; ++j)
			v[i][j] = min({ inf * 1.0, v[i + 1][j], v[i + 1][j - 1] + a[i].a });
	}
	cntb = min(k, cntb);
	for (int cb = 0; cb <= cntb; ++cb) {
		mem(f, 0x7f);
		f[0][0] = 0;
		for (int i = 1; i <= k; ++i) {
			for (int j = 0; j <= cb; ++j) {
				f[i][j] = min(f[i][j], f[i - 1][j] + 1.0 * a[i].a / (cb + 1));
				if (j > 0) f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1.0 * a[i].b / j);
			}
		}
		for (int i = cb; i <= k; ++i) ans = min(ans, f[i][cb] + 1.0 * v[i + 1][k - i] / (cb + 1));
	}
	printf("%.6lf\n", ans);
}
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	// ios::sync_with_stdio(0);
	// cin.tie(0), cout.tie(0);
	int t = 1;
	while (t--) {
		init();
		work();
	}
	return 0;
}
```
还有，有没有大佬能解释下为什么 `double` 数组 `memset` 一定要赋成 `0x7f` 才不会挂？一开始赋的 `0x3f` 就过不了

---

## 作者：Otue (赞：0)

首先要先把协作者买出来，再对于之后的州把买的协作者全部用上。则我们可以先枚举需要的协作者数量 $x$，可以知道的是：我们枚举选择哪些 $x$ 个协作者，再在剩下的州中选择 $A_i$ 最小的 $K-x$ 个州即可。则考虑 dp。我们对 $B_i$ 进行排序后，协作者就只在前 $K$ 个进行买卖。

我们可以发现：当两个协作州之间有反对州时，将反对州与后面一个协作州位置交换一定会更优。则定义 $f_{i,j}$ 表示前 $i$ 个州，选 $j$ 个协作州的最小代价，且前 $i$ 个州要么协作要么投票。

dp 复杂度 $O(n^2)$，总复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)

const int N = 505;
int n, k, sum[N][N], cnt;
double dp[N][N], res = 2e9;

struct edge {
	int a, b;
}ed[N];

signed main() {
	cin >> n >> k;
	_for(i, 1, n) cin >> ed[i].a >> ed[i].b;
	_for(i, 1, n) {
		cnt += (ed[i].b != -1);
		if (ed[i].b == -1) ed[i].b = 2e9;
	}
	sort(ed + 1, ed + n + 1, [](edge x, edge y) {
		return x.b < y.b;
	});
	memset(sum, 0x3f, sizeof sum);
	_for(i, 1, n + 1) sum[i][0] = 0;
	_pfor(i, n, 1) {
		_for(j, 1, n - i + 1) {
			sum[i][j] = min(sum[i + 1][j], sum[i + 1][j - 1] + ed[i].a);
		}
	}
	cnt = min(cnt, k);
	_for(cas, 0, cnt) {
		memset(dp, 0x7f, sizeof dp);
		dp[0][0] = 0;
		_for(i, 1, k) {
			_for(j, 0, cas) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1.0 * ed[i].a / (cas + 1));
				if (j) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1.0 * ed[i].b / j);
			}
		}
		_for(i, cas, k) res = min(res, dp[i][cas] + 1.0 * sum[i + 1][k - i] / (cas + 1));
	}
	printf("%.15lf", res);
}
```

---

