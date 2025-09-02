# [eJOI 2024] 足球决斗 / CF Duels

## 题目描述

基希讷乌，摩尔多瓦的首都，有两支各由 $N$ 名球员组成的足球队，进行一系列的对决。为了增加趣味，他们按照以下一对一的方式安排比赛：

- 总共有 $N$ 场对决，每场在不同的体育场进行。
- 每场对决将有两队中的一名球员对决。
- 每个球员将只参加一场对决。
- 每个体育场将为各自的对决胜利者提供一定金额的奖金。
- 技能等级更高的球员赢得对决。保证总有技能等级更高的球员。

在所有比赛结束后，冠军队是获得奖金总额超过对方球队的队伍。如果获得的奖金相同，则没有冠军。

你是第一支球队的经理，你的任务是安排你的 $N$ 名球员参加 $N$ 场对决获得冠军。

作为第一支足球队的经理，你拥有以下信息：

- $N$ 个整数，表示你队伍中球员的技能等级
- $N$ 个整数，表示对方队伍中球员的技能等级

作为经理，你还派了一名侦查员访问每个体育场。侦查员按从 $1$ 到 $N$ 的顺序访问体育场，首先访问体育场 $1$，然后是体育场 $2$，最后访问体育场 $N$。侦查员访问完体育场 $i$ 后，他会向你报告对方球队在体育场 $i$ 的对决球员的技能等级。

可能在侦查员访问了一些体育场之后，你已经可以预见你的球队将成为冠军。换句话说，有可能在侦查员访问了一些体育场后，你可以确定你能成为冠军。**你可能仍然需要等待侦查员访问剩余的体育场，以便为你的球队建立分配方案。**

你的任务是找出侦查员需要访问的最少体育场数量，以确保你的球队能够夺冠，或者确定不可能成为冠军。

## 说明/提示

**【样例 #1 解释】**
对于第一个样例，在侦查员分享体育场 $1$ 和 $2$ 的信息后，你仍不能保证成为冠军。原因是，如果对手按以下方式安排球员：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $8$ | $12$ | $3$ |

你最好的选择是打成平局：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 你的球员技能等级 | $6$ | $10$ | $1$ | $2$ | $4$ |

你将赢得体育场 $1,2,5$ 的比赛，获得奖金总额 $1+5+1=7$，而对手将赢得体育场 $3,4$ 的比赛，获得奖金总额 $4+3=7$。

在侦查员分享体育场 $1,2,3$ 的信息后，你可以确定你将成为冠军。原因是，如果对手按以下方式安排球员：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | 未知 | 未知 |

对手的两种选择是：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | $12$ | $8$ |
| 你的球员技能等级 | $6$ | $10$ | $4$ | $1$ | $2$ |

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | $8$ | $12$ |
| 你的球员技能等级 | $6$ | $10$ | $4$ | $1$ | $2$ |

我们可以注意到，在这两种情况下，我们的球队将在体育场 $1,2,3$ 获胜，获得奖金总额 $1+5+4=10$，而对手将获得奖金总额 $3+1=4$。由于 $10>4$，我们可以确定在这两种情况下我们都会获胜，因此最小答案是 $3$。

**【样例 2 解释】** 对于第二个样例，可以证明，在侦查员提供体育场 $1,2$ 的信息后，你将首次确定成为冠军。然而，与第一个样例不同，你不会有一个固定的获胜分配。相反，对于对手在体育场 $3, 4, 5, 6$ 中的不同安排，你需要有不同的应对策略来赢得冠军。

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$12$|$p_i=1,N\le10$|
|$2$|$16$|$p_i=1$|
|$3$|$14$|答案为 $0$ 或 $1$|
|$4$|$18$|答案为 $-1$ 或 $N-1$|
|$5$|$10$|$n\le5$|
|$6$|$30$|无|

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10^4,1 \le a_i,b_i \le 10^6$，且所有 $a_i,b_i$ 两两不同。

## 样例 #1

### 输入

```
5
1 5 4 3 1
5 9 3 12 8
1 10 4 2 6```

### 输出

```
3```

## 样例 #2

### 输入

```
6
6 1 21 22 23 24
1 12 6 8 10 11
2 3 4 5 7 9```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 3
3 4 6
2 1 7```

### 输出

```
0```

## 样例 #4

### 输入

```
3
1 1 3
3 4 6
2 1 5```

### 输出

```
-1```

# 题解

## 作者：_ayaka_ (赞：2)

### 思路

首先我们明白，未被看到的体育场完全可以当作最劣情况考虑。那么最劣的情况奖金数量和对方的技能等级顺序排列。遂我们可以构造出看完前 $k$ 个球场后最劣的情况：

- 对于前 $k$ 个球场，$p$ 和 $b$ 不变；
- 对于后 $n-k$ 个球场，$p$ 和 $b$ 皆顺序排序。

随后考虑我方如何获得最大奖金。枚举我方能力小的到能力大的，用优先队列存储第 $i$ 名球员可以成功获得奖金的体育场，把第 $i$ 名球员安放到他打得过且奖金最高的场地即可。由于后面的球员一定也能前往前面的球员可以前往的体育场，因此正确性得以证明。

具体做法就是二分至多能看完的体育场数量 $k$，然后对于当前的 $k$ 暴力构造出最劣的情况跑即可。构造情况和给球员找场地的复杂度为 $O(n \log n)$，总复杂度 $O(n \log^2 n)$。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, p[500005], a[500005], b[500005], x[500005], y[500005], l, r, sum, ans;
struct node {
	int p, b;
} c[500005];
bool cmp(node x, node y) {
	return x.b < y.b;
}
priority_queue<int, vector<int>, less<int>> q;//较大的元素会被优先取出 
bool check(int k) {
	int res = 0;
	while (!q.empty()) q.pop();
	for (int i = 1; i <= n; i++) {
		x[i] = p[i];
		y[i] = b[i];
	}
	sort(x + k + 1, x + n + 1);
	sort(y + k + 1, y + n + 1);
	for (int i = 1; i <= n; i++) {
		c[i] = {x[i], y[i]};
	}
	sort(c + 1, c + n + 1, cmp);
	for (int i = 1, j = 1; i <= n; i++) {
		while (c[j].b < a[i] && j != n + 1) {
			q.push(c[j++].p);//把所有打得过的放入优先队列 
		}
		if (!q.empty()) {
			res += q.top();
			q.pop();
		}//若没有可放的就让这个球员凑数就好了，因此不用计算贡献 
	}
	if (sum < res * 2) return 1;
	return 0;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> p[i], sum += p[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	if (!check(n)) {
		cout << "-1";
		return 0;
	}//特判无法获胜的情况 
	l = 0, r = n, ans = n;
	while (l <= r) {
		int mid = ((l + r) >> 1);
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else {
			l = mid + 1;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

显然得到的信息越多越容易确定胜利，因此答案具有单调性，考虑二分并检验得到信息的场馆数量 $mid$。

因为我们可以在比赛开始后再安排双方球员的对阵关系，所以不确定性来源于一对对阵取得的收益来自哪个场馆不确定。然后就是经典的田忌赛马策略：将双方球员和场馆按权值升序排列，逐一考虑己方队员，考虑他能战胜的所有对手并分情况讨论。若选择的对手来自已知的场馆那么收益是确定的，这种情况容易处理。若选择的对手来自未知的场馆，则取其中的最小收益累加。考虑完所有球员后判断能否取得冠军。若最小收益足以战胜对手则说明能否获胜与对方的安排无关，可以必胜，因为我们考虑了对方采取最佳的安排将我方收益最小化时的情况。

用一个大根堆维护所有可能的对阵情况，每次取出堆顶对阵方案即可。

```cpp
const ll N = 5e4 + 10;
ll n, sum, a[N], v[N];
pll sta[N], player[N];
pqueue(ll, less) pq;

#define jump1 for(;a[i]>player[p1].fi and p1<=n;p1++)
#define jump2 while(sta[p2].se<=k and p2<=n)p2++;

bool check(ll k) {
	myclear(pq);
	ll pts = 0, p1 = 1, p2 = 1;
	jump2;

	rep(i, 1, n) {
		jump1{
			if (player[p1].se <= k)
				pq.push(v[player[p1].se]);
			else {
				pq.push(sta[p2].fi);
				p2++;
				jump2;
			}
		}

		if (pq.size()) {
			pts += pq.top();
			pq.pop();
		}
	}

//	cout << "pts=" << pts << '\n';
//	pause;
	return pts > sum - pts;
}

int main() {
	cin >> n;

	rep(i, 1, n) {
		cin >> v[i];
		sta[i] = {v[i], i};
		sum += v[i];
	}

	sort(sta + 1, sta + n + 1);

	rep(i, 1, n) {
		cin >> player[i].fi;
		player[i].se = i;
	}

	sort(player + 1, player + n + 1);

	rep(i, 1, n) cin >> a[i];

	sort(a + 1, a + n + 1);

	ll l = 0, r = n, ans = -1;

	while (l <= r) {
		ll mid = (l + r) / 2;

		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else
			l = mid + 1;
	}

	cout << ans;
}
```

---

## 作者：chenly8128 (赞：1)

## 思路：

### 二分

根据套路：知道的多一定不劣于知道的少，所以答案满足单调性，可以二分答案，求最小值。

因此，可以设目前**需要判断是否能赢**的答案为 $x$。

- 对于前 $x$ 个比赛场地，一切都已知。

- 对于剩下的场地，考虑**最劣情况**：对方剩余所有选手，按照剩余场地的奖金大小，升序排布。这样我方能拿到的奖金最少。

所以，可以只考虑这种最劣情况。

### 贪心

贪心地对所有场地的奖金降序排序，优先考虑是否能赢下目前奖金最大的比赛，如果可以那么一定要赢下。否则放弃，按照田忌赛马理论，补一个技术最差的上去凑数。

统计一下总的奖金数目，看看有没有过半就行了。

## 实现

所以在每次判断过程中，需要排序。算上二分答案，总的复杂度 $O(n \log^2 n)$。


```cpp

// Author: chenly8128
// Created: 2025-04-27 10:31:26

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
const int MAXN = 5e4+10;
set <int> s1,s2;
int n,x;
ll sum;
struct point {
	int p,k;
	bool operator < (const point& b) const {
		return p > b.p;
	}
} v[MAXN];
vector <point> q;
vector <int> t;
bool check (int x) {
	s2 = s1;
	q.clear();t.clear();
	for (int i = 1;i <= x;i++) q.push_back(v[i]);
	for (int i = x+1;i <= n;i++) {
		q.push_back((point){v[i].p,-1});
		t.push_back(v[i].k);
	}
	sort(t.begin(),t.end(),greater<int>());
	sort(q.begin(),q.end());
	int st = 0;
	ll res = 0;
	for (int i = 0;i < n;i++) {
		if (q[i].k == -1) q[i].k = t[st++];
		auto it = s2.upper_bound(q[i].k);
		if (it != s2.end() && (*it) == q[i].k) it++;
		if (it != s2.end()) {
			s2.erase(it);
			res += q[i].p;
		}
	}
	return res > sum - res;
}
int main (void) {
	n = read();
	for (int i = 1;i <= n;i++) {
		v[i].p = read();
		sum += v[i].p;
	}
	for (int i = 1;i <= n;i++) v[i].k = read();
	for (int i = 1;i <= n;i++) s1.insert(x = read());
	int l = 0,r = n+1;
	while (l < r) {
		int mid = (l+r) >> 1;
		if (check (mid)) r = mid;
		else l = mid+1;
	}
	printf ("%d\n",r <= n ? r : -1);
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

一个简单题，但是由于翻译过于**数据删除**，浪费 1h，望周知。

显然答案满足单调性，考虑二分答案 $mid$。

按照能力值从小到大考虑我方球员与他方球员的对战，设当前我方球员能力值为 $a_u$，那么我们考虑找到所有 $b_i < a_u$ 的他方球员 $i$：

- 由于我们需要满足无论 $i > mid$ 的 $b_i$ 如何排我们都有必胜方案，所以我们只需要找到最优策略下的最小收益即可。

- 若 $i \le mid$，那么其对战位置已经确定，与其打的奖金是 $p_i$。

- 否则其对战位置没有确定，那么找到 $j > mid$ 的一个 $p_j$，使得这个体育场没有被使用过且奖金最小；那么与 $i$ 对打的最小奖金为 $p_j$。

那么 $i$ 就与能打赢的人中收益最大的人打（因为是最优策略），维护一个大根堆即可。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e4 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll sum;
int n;
int a[N], w[N];
pair<int, int> p[N], h[N];
inline bool check(int mid){
	ll now = 0;
	priority_queue<int> Q;
	int p1 = 1, p2 = 1;
	while(p[p2].se <= mid && p2 <= n)
	  ++p2;
	for(int i = 1; i <= n; ++i){
		while(p1 <= n && h[p1].fi < a[i]){
			if(h[p1].se <= mid)
			  Q.push(w[h[p1].se]);
			else{
				Q.push(p[p2++].fi);
				while(p[p2].se <= mid && p2 <= n)
				  ++p2;
			}
			++p1;
		}
		if(Q.size()){
			now += Q.top();
			Q.pop();
		}
	}
	return now > (sum - now);
}
bool End;
int main(){
	n = read();
	for(int i = 1; i <= n; ++i){
		p[i].fi = w[i] = read();
		p[i].se = i;
		sum += w[i];
	}
	for(int i = 1; i <= n; ++i){
		h[i].fi = read();
		h[i].se = i;
	}
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	sort(p + 1, p + n + 1), sort(h + 1, h + n + 1), sort(a + 1, a + n + 1);
	int l = 0, r = n, ans = -1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)){
			ans = mid;
			r = mid - 1;
		}
		else
		  l = mid + 1;
	}
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

