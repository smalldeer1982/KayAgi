# Financiers Game

## 题目描述

This problem has unusual memory constraint.

At evening, Igor and Zhenya the financiers became boring, so they decided to play a game. They prepared $ n $ papers with the income of some company for some time periods. Note that the income can be positive, zero or negative.

Igor and Zhenya placed the papers in a row and decided to take turns making moves. Igor will take the papers from the left side, Zhenya will take the papers from the right side. Igor goes first and takes $ 1 $ or $ 2 $ (on his choice) papers from the left. Then, on each turn a player can take $ k $ or $ k+1 $ papers from his side if the opponent took exactly $ k $ papers in the previous turn. Players can't skip moves. The game ends when there are no papers left, or when some of the players can't make a move.

Your task is to determine the difference between the sum of incomes on the papers Igor took and the sum of incomes on the papers Zhenya took, assuming both players play optimally. Igor wants to maximize the difference, Zhenya wants to minimize it.

## 说明/提示

In the first example it's profitable for Igor to take two papers from the left to have the sum of the incomes equal to $ 4 $ . Then Zhenya wouldn't be able to make a move since there would be only one paper, and he would be able to take only $ 2 $ or $ 3 $ ..

## 样例 #1

### 输入

```
3
1 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
-1 -2 -1 -2 -1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
-4 -2 4 5
```

### 输出

```
-13
```

# 题解

## 作者：ModestCoder_ (赞：4)

题意：

两个人分别从长度为n的数列的两端开始取数，如果前一个人取了k个数，后一个人必须取k或k+1个，第一个人最开始可以取1个或2个，不能操作时结束。

两个人都希望自己取到的数字之和尽量大，并保持绝对理智，求最后他们取到的数字之和之差。n≤4000。

Solution：

使用DP

$dp[l][r][k][0/1]$表示左侧第一个未取的数是第$l$个，右侧第一个未取的数是第$r$个，当前$k$的值和操作方。
时间复杂度$O(N^3)$

仔细分析，可以发现，k不会超过$\sqrt{N}$级别。
复杂度降到了$O(N^{2.5})$

进一步观察可以发现，i与n-j相差不会超过k级别。用这个差代替j。
复杂度降到了$O(N^2)$

所以这是可行的，直接记忆化即可。 但是状态弄下来空间还是开不下，因为实际访问的状态不超过$10^8$

可以把状态哈希一下。我开了30000000的空间也过了

哈希的模数我取了29999999，一开始用的19260817wa了。。。

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 4010
#define getsum(l, r) (sum[r] - sum[l - 1])
using namespace std;
int sum[maxn], dp[30000010], n;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int Hash(int a, int b, int c, int d){
	return ((((a * 4000ll) + b) * 100 + c) * 2 + d) % 29999999;
}

int dfs(int l, int r, int x, int k){
	if (r - l + 1 < x) return 0;
	if (r - l + 1 == x) return getsum(l, r) * (k ? -1 : 1);
	int sta = Hash(l, r, x, k);
	if (~dp[sta]) return dp[sta];
	int ans = 0;
	if (k){
		ans = dfs(l, r - x, x, 0) - getsum(r - x + 1, r);
		if (l <= r - x) ans = min(ans, dfs(l, r - x - 1, x + 1, 0) - getsum(r - x, r));
		return dp[sta] = ans;
	} else{
		ans = dfs(l + x, r, x, 1) + getsum(l, l + x - 1);
		if (l + x <= r) ans = max(ans, dfs(l + x + 1, r, x + 1, 1) + getsum(l, l + x));
		return dp[sta] = ans;
	}
}

int main(){
	n = read();
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; ++i) sum[i] = read(), sum[i] += sum[i - 1];
	printf("%d\n", dfs(1, n, 1, 0));
	return 0;
}
```


---

## 作者：xfrvq (赞：3)

[$\tt Link$](/problem/CF729F)。

$n$ 这么小，意识到可能不是猜结论。考虑暴力动态规划。

设计状态：$i,j,k$ 代表左边取了 $i$ 个，右边取了 $j$ 个，现在的 $k$ 值。$f_{i,j,k}$ 和 $g_{i,j,k}$ 分别代表当前是 *MAXer* 取还是 *Miner* 取。

那转移大概就是说有 $k\gets k$ 和 $k\gets k+1$ 两种。形式化的转移：

$$
\begin{cases}
f_{i,j,k}=\min(g_{i,j-k,k}-\Sigma(j-k,j],g_{i,j-k-1,k+1}-\Sigma(j-k-1,j])\\
g_{i,j,k}=\min(g_{i+k,j,k}+\Sigma[i+k,i),g_{i+k+1,j,k+1}+\Sigma[i+k+1,i))
\end{cases}
$$

其中 $\Sigma[l,r]=\sum_{i=l}^ra_i$。

空间 $n^3$，这是显然开不下的。（接下来需要一点技巧）

由 $1+\cdots+\sqrt n=\mathcal O(n)$ 可知，$k$ 是 $\sqrt n$ 级别的，空间复杂度优化至 $\mathcal O(n^2\sqrt n)$。

然后再观察，发现 $i,j$ 的差也是 $\mathcal O(k)=\mathcal O(\sqrt n)$ 级别的，空间复杂度优化至 $\mathcal O(n^2)$。

这个题不是很好写 $\tt dp$，考虑写记忆化搜索。

$\tt dp$ 数组也不是很好开，可以对状态 $\{i,j,k\}$ 进行哈希，然后对 $10^7$ 级别的大数取模，然后就可以开下了。

---

## 作者：subcrip (赞：0)

题目中有这么一句话：

> This problem has unusual memory constraint.

遂发现空间给了 512MB。但我算了一下，直接 DP 连 100MB 也用不了，感觉很奇怪；然后写了个 DP 还真过了，并且疑似是题解区空间最小，感觉更奇怪了。

设 $dp_{ijkl}$ 表示 Igor 目前拿走了 $i$ 张纸、Zhenya 目前拿走了 $i+j$ 张纸、接下来可以选择拿走 $k$ 或 $k+1$ 张纸、且接下来该第 $l$ 个人操作时，答案是多少。

首先发现 $k$ 这一维可以滚动掉。又发现 Igor 和 Zhenya 拿走的纸张数量之差在任何时候都不可能超过 $O(\sqrt n)$，所以空间复杂度来到了 $O(n\sqrt n)$。当然，$j$ 可能是负的，所以我们把 $j$ 这一维开到上界的两倍大小、然后在计算时做一个平移就行了，仍然是 $O(n\sqrt n)$ 的。根据 CF 的评测记录，大概用了 50MB 左右的内存。

DP 转移比较简单啦。详见代码。

# Code

```cpp
constexpr int M = 100;
constexpr int N = 4010;
ll dp[N][4 * M + 3][2];
ll ndp[N][4 * M + 3][2];

void solve() {

    read(int, n);
    readvec(int, a, n);
    vector<ll> ps(n + 1);
    for (int i = 1; i <= n; ++i) {
        ps[i] = ps[i - 1] + a[i - 1];
    }

    for (int k = M; k; --k) {
        for (int i = n; ~i; --i) {
            for (int j = 4 * M + 2; ~j; --j) {
                int right = i + j - 2 * M;
                if (right < 0 or right > n) continue;
                if (i + right < 0 or i + right > n) continue;
                if (0 <= i + k + right and i + k + right <= n) {
                    if (j - k >= 0) {
                        ndp[i][j][0] = ndp[i + k][j - k][1] + ps[i + k] - ps[i];
                    }
                    if (j + k < 4 * M) {
                        ndp[i][j][1] = ndp[i][j + k][0] - (ps[n - right] - ps[n - right - k]);
                    }
                    if (i + k + right + 1 <= n) {
                        if (j - k - 1 >= 0) {
                            chmax(ndp[i][j][0], dp[i + k + 1][j - k - 1][1] + ps[i + k + 1] - ps[i]);
                        }
                        if (j + k + 1 < 4 * M) {
                            chmin(ndp[i][j][1], dp[i][j + k + 1][0] - (ps[n - right] - ps[n - right - k - 1]));
                        }
                    }
                }
            }
        }
        swap(dp, ndp);
    }

    cout << dp[0][2 * M][0] << '\n';
}
```

---

## 作者：Avakos (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF729F)

考虑动态规划。$f_{i,j,k}$ 表示左边已取了 $i$ 个，右边已取了 $j$ 个，当前的 $k$ 值。$f$ 数值为答案数值。

不妨设 Igor 和 Zhenya 各操作一次为一轮，第 $p$ 轮中 Igor 取了 $a_p$ 个数，Zhenya 取了 $b_p$ 个数。那么有 $a_p \leq b_p \leq a_{p+1}$，$a_1 \in [1,2]$。因此如果 $i<=j$ 则当前为 Igor 操作，反之为 Zhenya 操作。经简单观察可发现 $k \leq \sqrt{2 \times n}$，以此为基础求 $a_p-b_p$ 的和可以得到 $i$ 与 $j$ 的差为 $O(\sqrt{n})$ 级别。因此这个 dp 的时空复杂度均为 $O(N^2)$。

但是空间还是不太好开，因此需要一个更精细的实现。

考虑用记忆化搜索进行倒推，那么有状态转移方程为：

$$f_{i,j,k}=\begin{cases} \max(f_{i+k,j,k}+\sum_{l=i+1}^{i+k}a_l,f_{i+k+1,j,k+1}+\sum_{l=i+1}^{i+k+1}a_l) & i \leq j \\ \min(f_{i,j+k,k}-\sum_{l=n-j-k+1}^{n-j}a_l,f_{i,j+k+1,k+1}-\sum_{l=n-j-k}^{n-j}a_l) & i>j \end{cases}$$

同时在每次从 $k$ 和 $k+1$ 中转移时总是先从 $k$ 转移，这样对于同一个 $(i,j)$，较小的 $k$ 初次被访问的时刻也较早，因此第一次访问到的就是 $k$ 的最小值。设这个最小值为 $c_{i,j}$，考虑开一个 vector 存 $f$，则 $(i,j,k)$ 对应的下标为 $(i,j,k-c_{i,j})$。具体见代码。

code：

```
#include<bits/stdc++.h>
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define DU double
#define rep(i,x,n) for(int i=(x);i<=(n);i++)
#define nep(i,x,n) for(int i=(x);i>=(n);i--)
using namespace std;
const int N=4010;
int n,a[N],s[N],minx[2100][2100],siz[2100][2100];
//minx 为文中 c
vector<int>f[2100][2100];
inline int read(){
	int s=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s*f;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline int dp(int x,int y,int k){
	if(n-x-y<k) return 0;
	if(!minx[x][y]) minx[x][y]=k;
	int id=k-minx[x][y];
	if(siz[x][y]>id) return f[x][y][id];
	siz[x][y]++;
	if(x<=y){
		int t=dp(x+k,y,k)+s[x+k]-s[x];
		if(n-x-y>=k+1) t=max(t,dp(x+k+1,y,k+1)+s[x+k+1]-s[x]);
		f[x][y].push_back(t);return t;
	}
	else{
		int t=dp(x,y+k,k)-s[n-y]+s[n-y-k];
		if(n-x-y>=k+1) t=min(t,dp(x,y+k+1,k+1)-s[n-y]+s[n-y-k-1]);
		f[x][y].push_back(t);return t;
	}
}
inline void Solve(){
	n=read();rep(i,1,n) a[i]=read(),s[i]=s[i-1]+a[i];
	print(dp(0,0,1)),puts("");
}
int main(){
	int Tests=1;
	while(Tests--) Solve();
	return 0;
}
```

---

## 作者：OtoriEmu (赞：0)

注：重新对格式进行了检查，没有找到任何的错误。如果这次有格式不正确的地方，烦请在反馈中指出，谢谢。

有一个暴力的 DP 定义，即定义 $dp_{l,r,c,0/1}$ 表示 A 选了 $l$ 个，B 选了 $r$ 个，上一次选的人是 A 或 B 并且选择了 $c$ 个。

这个状态数量怎么想都是 $O(n^3)$ 的，太不科学了！现在的想法就是去解决这个**状态数量过多**的问题。

然而这个问题实在是太一般了……找不到很好的性质优化。那从 DP 的范围入手：$l,r,c$ 每一维都是 $O(n)$ 的，肯定不优秀，限制一下这些东西的范围。

考虑 B 取完（即一整轮之后）两个人取的数的差。可以发现一整轮之后两个人取的数的差值最多变化 $1$。进而分析 $c$ 的上限，发现 $c$ 的上限就是 $O(\sqrt n)$（因为以 $1,1,2,2,\cdots$ 的方法取的话，取到 $O(\sqrt n)$ 就溢出了）。这样就做到状态 $O(n^2)$ 了。

重新定义 DP 为：$dp_{c,d,l,0/1}$ 表示 A/B 作为上一次的人选了 $c$ 个，现在 $A,B$ 选的数的差为 $d$（这个值的**绝对值**不超过 $O(\sqrt n)$），A 总共选了 $l$ 个的情况。这个转移非常的暴力，并且可以用记忆化搜索实现，所以代码难度并不高。

但是，这个题竟然卡空间！？

首先是 $l$ 这一维可以缩小到 $\dfrac{n+\sqrt n}{2}$，因为两个人选的数的差并不大。这样可以做到 600MiB。

同时注意到除非 A 刚选，那 A 选的数的个数肯定不会大于 B 选的个数，这样就顺带把 $0/1$ 一维辨认操作手省掉了（当然实际上实现的细节有一点小差异，并不重要）。这样通过此题就绰绰有余了！实际提交因为记忆化搜索的原因，空间占用到了约 430MiB，其实用不上什么哈希表。

参考代码实现：[先輩わ怖い！](https://www.luogu.com.cn/paste/etogf5xt)，下面给出关键代码。

```cpp
const int Cur=90;
int n,a[4005],sum[4005];
inline int getSum(int l,int r){return sum[r]-sum[l-1];}
bool vis[92][362][2202];
int dp[92][362][2202];
int Solve(int lst,int c,int l,int op)
{
	int r=l+c;
	int L=l+1,R=n-r;
	if(R-L+1<lst)	return 0;
	if(vis[lst][c+Cur][l])	return dp[lst][c+Cur][l];
	vis[lst][c+Cur][l]=true;
	if(!op)
	{
		int ans=-1e9;
		ans=max(ans,Solve(lst,c-lst,l+lst,op^1)+getSum(L,L+lst-1));
		if(R-L+1>=lst+1)	ans=max(ans,Solve(lst+1,c-lst-1,l+lst+1,op^1)+getSum(L,L+lst));
		return dp[lst][c+Cur][l]=ans;
	}
	else
	{
		int ans=1e9;
		ans=min(ans,Solve(lst,c+lst,l,op^1)-getSum(R-lst+1,R));
		if(R-L+1>=lst+1)	ans=min(ans,Solve(lst+1,c+lst+1,l,op^1)-getSum(R-lst,R));
		return dp[lst][c+Cur][l]=ans;
	}
}
```



---

