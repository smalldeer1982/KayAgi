# Boxes and Balls

## 题目描述

There are $ n $ boxes placed in a line. The boxes are numbered from $ 1 $ to $ n $ . Some boxes contain one ball inside of them, the rest are empty. At least one box contains a ball and at least one box is empty.

In one move, you have to choose a box with a ball inside and an adjacent empty box and move the ball from one box into another. Boxes $ i $ and $ i+1 $ for all $ i $ from $ 1 $ to $ n-1 $ are considered adjacent to each other. Boxes $ 1 $ and $ n $ are not adjacent.

How many different arrangements of balls exist after exactly $ k $ moves are performed? Two arrangements are considered different if there is at least one such box that it contains a ball in one of them and doesn't contain a ball in the other one.

Since the answer might be pretty large, print its remainder modulo $ 10^9+7 $ .

## 说明/提示

In the first example, there are the following possible arrangements:

- 0 1 1 0 — obtained after moving the ball from box $ 1 $ to box $ 2 $ ;
- 1 0 0 1 — obtained after moving the ball from box $ 3 $ to box $ 4 $ ;
- 1 1 0 0 — obtained after moving the ball from box $ 3 $ to box $ 2 $ .

In the second example, there are the following possible arrangements:

- 1 0 1 0 — three ways to obtain that: just reverse the operation performed during the first move;
- 0 1 0 1 — obtained from either of the first two arrangements after the first move.

## 样例 #1

### 输入

```
4 1
1 0 1 0```

### 输出

```
3```

## 样例 #2

### 输入

```
4 2
1 0 1 0```

### 输出

```
2```

## 样例 #3

### 输入

```
10 6
1 0 0 1 0 0 0 1 1 1```

### 输出

```
69```

# 题解

## 作者：Alex_Wei (赞：18)

### *[CF1845E Boxes and Balls](https://www.luogu.com.cn/problem/CF1845E)

用序列 $b$ 描述球的状态，其中 $b_1 < b_2 < \cdots < b_{|b|}$ 表示所有有球的位置。

设初始状态为 $a$。考虑状态 $b$ 合法的充要条件。

首先球的个数 $c$ 不变，因此 $|a| = |b| = c$。

求出从 $a$ 变成 $b$ 的最小步数 $f(b) = \sum_{i = 1} ^ c |a_i - b_i|$，如果 $f(b) > k$ 则不合法。否则我们可以让一个球反复横跳，使得恰好操作 $f(b) + 2t$（$t\in \mathbb N$）次也可以达到状态 $b$。因此若 $k - f(b)$ 是偶数，则状态合法。否则 $k - f(b)$ 是奇数，而每次操作必然改变 $\sum b_i$ 的奇偶性，所以恰好操作 $k$ 次时 $\sum a_i$ 和 $\sum b_i$ 奇偶性不同，一定不合法。

因此，一个状态合法当且仅当 $|a| = |b|$ 且 $f(b)\leq k$ 且 $2\mid k - f(b)$。

设 $f_{i, j, s}$ 表示考虑到第 $i$ 个位置，已经放了 $j$ 个球且当前 $f$ 值为 $s$ 的方案数，枚举 $i + 1$ 是否放球转移到 $f_{i + 1, j, s}$ 和 $f_{i + 1, j + 1, s + |i + 1 - b_{j + 1}|}$。复杂度是 $\mathcal{O}(n ^ 3)$，不够优秀。

关于不降序列对应位置距离之和，有经典套路：**在每个间隔处统计答案**。设 $z(b, i)$ 表示方案 $b$ 相较于原方案，在 $i$ 前缀多出的球的个数。若 $z(b, i) < 0$ 说明 $a$ 比 $b$ 在 $i$ 前缀多出 $-z(b, i)$ 个球。那么需要有 $|z(b, i)|$ 个球通过位置 $i\sim i + 1$ 之间的间隔，$f(b) = \sum |z(b, i)|$。

因为序列递增，所以 $z(b, i)$ 和 $z(b, i + 1)$ 相差不超过 $1$。根据等差数列求和公式，$\max |z(b, i)| = \mathcal{O}(\sqrt k)$。

设 $f_{i, j, s}$ 表示考虑到第 $i$ 个位置，$z(b, i) = j$ 且 $\sum_{p = 1} ^ i |z(b, i)| = s$ 的方案数，枚举 $i + 1$ 是否放球，求出 $z(b, i + 1)$，然后将 $s$ 加上 $|z(b, i + 1)|$。

答案即 $\sum f_{n, 0, k - 2t}$。时间复杂度 $\mathcal{O}(n ^ 2\sqrt n)$。[代码](https://codeforces.com/contest/1845/submission/211558765)。

类似题目：CF1615F。

---

## 作者：Register_int (赞：9)

赛时没过。我不好意思说我学过 dp。

显然是 dp。先偷个懒，如果 $1$ 比 $0$ 多就取反再算。设计状态 $dp_{i,j,l}$ 表示：用 $l$ 步使得前 $i$ 个位置有 $j$ 个 $1$。可以发现移动前后所有 $1$ 的相对位置不变，所以转移时可以直接钦定第 $j$ 个 $1$ 移到 $i$。设第 $j$ 个 $1$ 的位置是 $p_j$，那么有转移 $dp_{i,j,l}\leftarrow dp_{i-1,j,l}+dp_{i-1,j-1,l-|p_j-i|}$。暴力转移加滚动数组即可 $O(n^2k)$。

~~然而我人傻常数大过不去~~，所以考虑压缩一下状态。可以发现，要将 $x$ 个 $1$ 挪出前 $i$ 格，至少需要 $x^2$ 步，反之同理。所以，前 $i$ 格在操作过后 $1$ 的个数与原来相差的值最大为 $O(\sqrt k)$。在这个范围里转移即可，时间复杂度 $O(nk^{\frac32})$。

最后要注意，我们可以浪费偶数步进行反复横跳。所以答案还要累加上与 $k$ 同奇偶性的值。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1.5e3 + 10;
const int mod = 1e9 + 7;

int n, m, a[MAXN];

int s[MAXN], b, p[MAXN], tot;

ll dp[MAXN][MAXN], ans;

int main() {
	scanf("%d%d", &n, &m), **dp = 1;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), tot += a[i];
	if (tot << 1 > n) for (int i = 1; i <= n; i++) a[i] ^= 1; tot = 0;
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i], a[i] && (p[++tot] = i); b = sqrt(tot) * 3;
	for (int i = 1; i <= n; i++) {
		for (int j = min({ i, tot, s[i] + b }), x; j >= s[i] - b && j; j--) {
			x = abs(p[j] - i);
			for (int k = x; k <= m; k++) dp[j][k] = (dp[j][k] + dp[j - 1][k - x]) % mod;
		}
	}
	for (int i = m; i >= 0; i -= 2) ans = (ans + dp[tot][i]) % mod;
	printf("%lld", ans);
}
```

---

## 作者：honglan0301 (赞：6)

## 题目分析

直接考虑结果序列有什么性质。容易发现小球们的相对位置永远不会变，于是记开头的序列前缀和为 $s_i=\sum\limits_{j=1}^i a_i$，结尾序列前缀和为 $s'_i=\sum\limits_{j=1}^i a'_i$，则需要的最小操作次数为 $\sum |s_i-s'_i|$，并且显然在奇偶性相同的前提下用更多次操作也没有问题（可以通过来回动某个小球来实现）。

于是题目转化成了对满足 $\sum|s_i-s'_i|\leq k,\ \sum |s_i-s'_i|\equiv k \pmod 2$ 且 $s'_0=0,s'_n=s_n$ 且对于 $\forall i$ 均有 $s'_i-s'_{i-1}\in \{0,1\}$ 的序列计数。

因为 $|s_i-s'_i|$ 彼此独立，故很容易想到一个 $O(n^3)$ 的暴力 $\text{dp}$，即设 $f_{i,j,k}$ 表示填完了前 $i$ 个数，此时 $s'_i=j$，$\sum\limits_{p=1}^i |s_p-s'_p|=k$ 的方案数。其转移为

$$f_{i,j,k}=f_{i-1,j,k-|s_i-j|}+f_{i-1,j-1,k-|s_i-j|}$$

视题目 $n,k$ 同级，此时直接滚动掉第一维后空间 $O(n^2)$，时间 $O(n^3)$，加上一些优化能卡过。

接下来考虑正解的优化，其实也很简单。我们还有一个重要的条件没用上，即对于 $\forall i$ 均有 $s_i-s_{i-1}\in \{0,1\},\ s'_i-s'_{i-1}\in \{0,1\}$。这个条件很强地要求了在上述 $\text{dp}$ 中 $|s_{i}-j|$ 至多在 $O(\sqrt k)$ 级别，否则因为 $||s_i-s'_i|-|s_j-s'_j||\leq |i-j|$，$\sum |s_i-s'_i|$ 会超过 $k$。于是转移的时候只考虑这一部分，总时间复杂度变为 $O(n^2\sqrt n)$，可以通过本题。

## 代码

```cpp
bool ck(int num,int x)
{
	if(num>a[x]+50||num<a[x]-50) return 0; return 1;
}

signed main()
{
	cin>>n>>k; for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1]; dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=min(a[n],a[i]+50);j>=max(0,a[i]-50);j--)
		{
			for(int q=k;q>=abs(a[i]-j);q--)
			{
				dp[j][q]=ck(j,i-1)*dp[j][q-abs(a[i]-j)]+ck(j-1,i-1)*((j>0)?dp[j-1][q-abs(a[i]-j)]:0);
				if(dp[j][q]>=mod) dp[j][q]-=mod;
			}
			for(int q=abs(a[i]-j)-1;q>=0;q--) dp[j][q]=0;
		}
	}
	for(int i=k;i>=0;i-=2) ans+=dp[a[n]][i],ans%=mod; cout<<ans<<endl;//
}
```


---

## 作者：Leasier (赞：1)

首先把 $k$ 乘 $2$，则我们要求 $cnt \leq k, (k - cnt) \bmod 4 = 0$，其中 $cnt$ 表示最终第 $i$ 个 $0$ 与原有第 $i$ 个 $0$ 的位置绝对值之差和最终第 $i$ 个 $1$ 与原有第 $i$ 个 $1$ 的位置绝对值之差的和。

考虑 dp，设 $dp_{i, j, x}$ 表示考虑了前 $i$ 个数，填入了 $j$ 个 $0$，已填部分对 $cnt$ 的贡献为 $x$ 的方案数。转移等略去。

直接暴力的时间复杂度为 $O(n^2 k)$，显然不能通过。

本题 5s 的时限让人浮想联翩，我们不妨猜想这个 dp 的状态数是不满的，然后写一发就过了……？

注意到若 $j$ 与原有前 $i$ 个数中的 $0$ 的个数之差的绝对值为 $\Delta$，则有效的 $x \geq S_1(\Delta)$（其中 $S_1(n) = \frac{n(n + 1)}{2}$），于是有效的 $j$ 只有 $O(\sqrt{k})$ 个。

于是时间复杂度实为 $O(nk \sqrt{k})$，可以通过。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;
int cnt[7], pos[7][1507], dp[2][1507][3007], vis[2][1507][3007];
vector<pair<int, int> > v[7];

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

int main(){
	int n, k, lst, ans = 0;
	cin >> n >> k;
	k *= 2;
	for (register int i = 1; i <= n; i++){
		int a;
		cin >> a;
		pos[a][++cnt[a]] = i;
	}
	dp[0][0][0] = 1;
	vis[0][0][0] = 0;
	v[0].push_back(make_pair(0, 0));
	for (register int i = 1; i <= n; i++){
		int cur = i & 1, pre = cur ^ 1;
		for (register vector<pair<int, int> >::iterator j = v[pre].begin(); j != v[pre].end(); j++){
			if (j->first < cnt[0]){
				int x = j->first + 1, y = j->second + abs(i - pos[0][x]);
				if (y <= k){
					if (vis[cur][x][y] < i){
						vis[cur][x][y] = i;
						dp[cur][x][y] = 0;
						v[cur].push_back(make_pair(x, y));
					}
					add(dp[cur][x][y], dp[pre][j->first][j->second]);
				}
			}
			if (i - j->first - 1 < cnt[1]){
				int x = j->second + abs(i - pos[1][i - j->first]);
				if (x <= k){
					if (vis[cur][j->first][x] < i){
						vis[cur][j->first][x] = i;
						dp[cur][j->first][x] = 0;
						v[cur].push_back(make_pair(j->first, x));
					}
					add(dp[cur][j->first][x], dp[pre][j->first][j->second]);
				}
			}
		}
		v[pre].clear();
	}
	lst = n & 1;
	for (register int i = k; i >= 0; i -= 4){
		if (vis[lst][cnt[0]][i]) add(ans, dp[lst][cnt[0]][i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：KingPowers (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1845E)

下文记题目中的 $k$ 为 $m$。

我们记初始时小球的局面为 $a$，$m$ 次操作后小球的局面为 $b$，考虑什么情况下 $b$ 是合法的。

不妨先求出将 $a$ 操作成 $b$ 的最小操作数，记为 $cnt$，那么显然当且仅当 $cnt\le m$ 且 $cnt\equiv m\pmod 2$ 时 $b$ 合法， 因为我们可以通过在相邻两个 $01$ 之间来回交换刷次数。

至于到底如何计算出最小操作数，我们考虑统计每个位置会被多少个小球跨过：分别记 $s$ 和 $s'$ 为 $a$ 和 $b$ 的前缀和数组，则最小操作数 $cnt=\sum|s_i'-s_i|$。

现在我们可以将问题转化为，给定一个 $01$ 序列 $a$，求有多少个 $01$ 序列 $b$ 满足如下条件：

- $s'_n=k$。
- $\sum|s_i'-s_i|\le k$。
- $\sum|s_i'-s_i|\equiv k\pmod 2$。

这种形式看上去就很可做了，设 $f[i][j][k]$ 表示填了前 $i$ 个数，当前一共填了 $j$ 个 $1$，$\sum|s_i'-s_i|=k$ 的方案数，转移考虑枚举当前位填 $0$ 还是 $1$：

$$
f[i][j][k]=f[i-1][j][k-|j-s_i|]+f[i-1][j-1][k-|j-s_i|]
$$

直接做时间复杂度是 $O(n^2m)$ 的，难以通过。

我们考虑 $|s_i'-s_i|$ 的实质是跨过 $i$ 的小球数量。我们假设有 $x$ 个小球要从 $i$ 的一边跨到另一边，那么我们的操作数最低也是一个等差数列的形式，是 $O(x^2)$ 的，所以 $|s_i'-s_i|$ 的取值是 $O(\sqrt m)$ 的，在 dp 时只枚举 $j$ 为这些值即可。

现在时间复杂度是 $O(nm\sqrt m)$ 的了，可以通过，但是需要滚动数组优化空间，而且我在 CF 上竟然还差点没跑过去。

```cpp
int n,m,ans,a[N],s[N],dp[2][N][N];
void add(int &x,int y){
	if((x=x+y)>=mod) x-=mod;
}
void Main(){
	cin>>n>>m;
	For(i,1,n) cin>>a[i];
	For(i,1,n) s[i]=s[i-1]+a[i];
	dp[0][0][0]=1;
	For(i,1,n){
		int now=i&1,lst=now^1;
		memset(dp[now],0,sizeof(dp[now]));
		For(j,max(0,s[i]-50),min(s[n],s[i]+50))
			For(k,abs(s[i]-j),m){
				add(dp[now][j][k],dp[lst][j][k-abs(s[i]-j)]);
				if(j) add(dp[now][j][k],dp[lst][j-1][k-abs(s[i]-j)]);
			}
	}
	for(int i=m;i>=0;i-=2) add(ans,dp[n&1][s[n]][i]);
	cout<<ans<<'\n';
}
```

---

## 作者：BreakPlus (赞：1)

ooc 选手花一整场时间切了这题正解。第一次完善了这个 trick 的做。

----

首先如果可以移动 $k$ 次达成，那么移动 $k+2$ 次也可以达成。

原题操作等价于看作 $1$ 的移动。如果这题转化一下，也可以看作 $1$ 的移动：把相邻两个相同的数反转。只需要将每个偶数位异或 $1$ 即可。

给每个 $1$ 标号，发现移动之后，每个 $1$ 还是按照原来的顺序排列。设原的序列有 $k$ 个 $1$，意味着我们要在原序列里重新任意地放置 $k$ 个 $1$。

我们考虑一边放置一边计数移动次数。具体地，我们考虑 dp 维护当前状态的**最小移动次数**。我们发现原序列的 $1$ 和新序列的 $1$ 按顺序作差即为最小移动次数。**我们把这个差看作一条线段。**

而新放置的一个 $1$ 可以作为一条线段的起点或终点，原来的 $1$ 也可以。这要取决于在这个位置之前，新放置的 $1$ 多还是原来的 $1$ 多。如果是前者多，说明还有一些新放置的 $1$ 作为起点，还没找到终点，此时如果来了一个
原来的 $1$，就一定是终点了。

这启示我们再维护一个**差值**：新放置的 $1$ 的个数减去原来的 $1$ 的个数。

在 dp 的同时，如何计算这些**线段的总长**？如果遇到起点就减坐标，遇到终点就加坐标，**起伏太大，状态数太多**。而我们考虑一个点被多少线段经过，每次加这个值，就可以避免起伏（长度总和不降）。

你发现，我们要维护当前位置、当前总长、差值，那不是 $\mathcal{O}(nk^2)$ 了吗？和暴力 dp 相比有啥优越性可言？事实上，差值不会超过 $B = \sqrt{k}$。因为，如果我们有 $B$ 个起点，$B$ 个终点，由于没有两个点是重合的，就算挨在一起，也要有 $B^2$ 的总长。复杂度降到了 $\mathcal{O}(nk^{1.5})$。

这道题要不是暴力 dp 过了，真不止 *2500……要敢于尝试新的 dp 状态，并发现可以优化的性质。

记得滚动数组优化一下空间。

```cpp
ll n,K,a[1505],f[2][85][3005];
ll Abs(ll x){
	return x<0?-x:x;
}
void solve(){
	n=read(), K=read();
	ll B = sqrt(K);
	for(ll i=1;i<=n;i++) a[i]=read();
	f[0][B][0]=1;
	for(ll i=0, op=0;i<n;i++, op^=1) {
		memset(f[op^1],0,sizeof(f[op^1]));
		for(ll j=-B;j<=B;j++)
			for(ll k=0;k<=K;k++){
				if(!a[i+1]){
					f[op^1][j+B][k+Abs(j)] =(f[op^1][j+B][k+Abs(j)] + f[op][j+B][k]) % mod;
					if(j<B){
						f[op^1][j+1+B][k+Abs(j)] = (f[op^1][j+1+B][k+Abs(j)] + f[op][j+B][k]) % mod;
					}
				}else{
					if(j>-B) f[op^1][j-1+B][k+Abs(j)] =(f[op^1][j-1+B][k+Abs(j)] + f[op][j+B][k]) % mod;  
					f[op^1][j+B][k+Abs(j)] =(f[op^1][j+B][k+Abs(j)] + f[op][j+B][k]) % mod; 
				}
			}
	}
	ll ans = 0;
	for(ll k=0;k<=K;k++){
		if((k&1) == (K&1)) ans = (ans + f[n&1][B][k]) % mod;
	} 
	printf("%lld\n", ans);
}
```

---

## 作者：Purslane (赞：1)

# Solution

对于每个 $i \le k$ 可以尝试求出最少移动 $i$ 次可以形成多少种局面。之后可以通过 $\frac{k-i}{2}$ 次对于某个空格子的反复横跳使得移动了恰巧 $k$ 次。由此可知，$k \equiv i \pmod 2$ 是必须成立的。

再考虑移动到一个状态需要的最短步数。很容易发现两个小球并不能互相穿过，也就是初始状态和末状态必须一一对应。那么设原状态每个球的位置是 $pos_i$，新状态每个球的位置是 $pos'_i$，那么最短步数就是 $\sum |pos_i-pos'_i|$。

动态规划最基本的状态以及转移是很容易处理的。设 $dp_{i,j,l}$ 表示最终状态前 $i$ 个盒子放了 $j$ 个球，目前移动的最短距离为 $l$ 的方案数。转移的时候枚举这个盒子放不放球，就可以做到 $O(n^2k)$，不足以通过本题。

但是注意到如果我们要把区间 $[1,x]$ 中移走 $h$ 个球，那么最优状态肯定是 $x+1,x+2,\dots,x+h$ 这些位置放了球，那么每个球至少移动了 $h$ 步，也就是说总数不少于 $h^2$ 步。这个必须 $\le k$，也就是说 $h\le \sqrt k$，反之亦然。这意味着 $j$ 的范围是 $[pre_i - \sqrt k,pre_i+\sqrt k]$。这样对于每个 $i$ 我们只需要枚举 $O(\sqrt k)$ 个 $j$，时间复杂度为 $O(nk\sqrt k)$。

不过我这样写过不了。$j$ 应当小于等于 $i$ 且大于等于 $tot-n+i$。加上这个限制就可以跑到洛谷截止目前的速度 rank 3。

代码：
```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1500+10,MOD=1e9+7;
int n,k,bl,id,a[MAXN],pos[MAXN],dp[2][MAXN][MAXN],pre[MAXN]; 
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k; ffor(i,1,n) cin>>a[i]; ffor(i,1,n) if(a[i]) pos[++id]=i; ffor(i,1,n) pre[i]=pre[i-1]+a[i];
	bl=sqrt(k); pos[id+1]=n+k+k+k+k+n+n+k;
	dp[0][0][0]=1;
	ffor(i,1,n) {
		int L=max({0,pre[i]-bl,id-n+i}),R=min({i,id,pre[i]+bl}),st=i&1;
		ffor(j,L,R) ffor(v,0,k) dp[st][j][v]=0;
		int ll=max({0,pre[i-1]-bl,id-n+i-1}),rr=min({i-1,id,pre[i-1]+bl});
	    ffor(sum,ll,rr) {
			ffor(j,0,k) {
				dp[st][sum][j]=(dp[st][sum][j]+dp[st^1][sum][j])%MOD;
				if(j+abs(i-pos[sum+1])<=k) dp[st][sum+1][j+abs(i-pos[sum+1])]=(dp[st][sum+1][j+abs(i-pos[sum+1])]+dp[st^1][sum][j])%MOD;
			}
		}
	}
	int ans=0;
	ffor(i,0,k) if((k-i)%2==0) ans=(ans+dp[n&1][id][i])%MOD;
	cout<<ans;
	return 0;
}
```

---

