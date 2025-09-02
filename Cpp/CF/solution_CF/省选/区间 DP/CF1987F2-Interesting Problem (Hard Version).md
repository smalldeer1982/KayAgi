# Interesting Problem (Hard Version)

## 题目描述

这是该问题的困难版本。两种版本的唯一区别在于 $n$ 的限制。只有当你同时解决了两个版本的问题时，才能进行 Hack。

给定一个长度为 $n$ 的整数数组 $a$。

每次操作，你需要执行以下两步：

1. 选择一个下标 $i$，满足 $1 \le i < |a|$ 且 $a_i = i$。
2. 从数组中移除 $a_i$ 和 $a_{i+1}$，并将剩余部分拼接起来。

请你求出最多可以执行上述操作多少次。

## 说明/提示

在第一个测试用例中，一种可能的最优操作序列为 $[1, 5, \color{red}{3}, \color{red}{2}, 4] \rightarrow [\color{red}{1}, \color{red}{5}, 4] \rightarrow [4]$。

在第三个测试用例中，一种可能的最优操作序列为 $[1, \color{red}{2}, \color{red}{3}] \rightarrow [1]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
5
1 5 3 2 4
8
2 1 3 4 5 6 7 8
3
1 2 3
4
1 2 4 4
5
4 4 1 3 5
1
1```

### 输出

```
2
3
1
2
0
0```

# 题解

## 作者：KingPowers (赞：15)

场上瞪了一个小时一点不会，狠狠意识到我对区间 dp 一无所知。

考虑如果我们希望 $a_i$ 最终被选中过，那么它应当满足下面的条件：

- $a_i\le i$，因为我们只能删除，若 $a_i>i$ 不可能通过操作使 $a_i=i$。
- $a_i$ 与 $i$ 的奇偶性相同，因为我们每次操作只能删去相邻两个元素，操作不会改变下标的奇偶性。
- 需要在 $[1,i-1]$ 这段前缀中恰好删去 $\frac{i-a_i}{2}$ 个数使得 $a_i=i$。

结合第三条与数据范围，可以想到一个区间 dp：设 $f_{l,r}$ 表示要将区间 $[l,r]$ 删空，最少要在 $[1,l-1]$ 这段前缀内操作几次，转移前首先要判断 $a_l$ 是否可以被选中，因为不能通过操作前面的数使得 $a_l$ 被删去，然后设 $v=\frac{l-a_l}{2}$，转移考虑枚举断点 $k$，则 $\max\{v,f_{l,k},f_{k+1,r}-\frac{k-l+1}{2}\}\to f_{l,r}$ 即可。

还有一种特殊的转移，我们可以将 $a_l$ 与 $a_r$ 配对删除，条件为 $f_{l+1,r-1}\le \frac{l-a_l}{2}$。

随后考虑如何求答案，令 $g_i$ 表示 $[1,i]$ 里最多能操作几次，转移时枚举前缀 $[1,i]$ 的一段后缀 $[j,i]$，如果 $f_{j,i}\le g_{j-1}$ 即可有转移 $g_{j-1}+\frac{i-j+1}{2}\to g_i$，也就是代表 $[j,i]$ 这段能被删空。

时间复杂度 $O(n^3)$，但区间 dp 本身拥有很小常数且本题我们还只需要对长度为偶数的区间进行 dp，所以可以通过。

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 805, INF = 1e9;
int n, a[N], f[N][N], g[N];
void Solve(){
	cin >> n;
	For(i, 1, n) cin >> a[i];
	For(l, 1, n) For(r, 1, n) f[l][r] = INF;
	for(int len = 2; len <= n; len += 2)
		For(l, 1, n - len + 1){
			int r = l + len - 1, v = (l - a[l]) / 2;
			if((l % 2 != a[l] % 2) || l < a[l]) continue;
			if(len == 2 || f[l + 1][r - 1] * 2 <= (l - a[l])) f[l][r] = v;
			for(int k = l + 1; k <= r - 1; k += 2){
				int nv = max({v, f[l][k], f[k + 1][r] - (k - l + 1) / 2});
				f[l][r] = min(f[l][r], nv);
			}
		}
	For(i, 1, n){
		g[i] = g[i - 1];
		for(int len = 1; 2 * len <= i; len++)
			if(f[i - 2 * len + 1][i] <= g[i - 2 * len]) g[i] = max(g[i], g[i - 2 * len] + len);
	}
	cout << g[n] << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：Purslane (赞：12)

# Solution

吐槽：样例是真弱。

这题能评 `*2600`，样例功劳占一半。

------

考虑什么时候，和 $i$ 一起删除的元素不是**原序列中的后继**？

假设原序列中 $i$ 和 $j$ 一起删掉的。那么 $[i+1,j-1]$ 中的所有元素都被完全删光了。这启示我们使用区间 DP。

DP 的时候要维护什么信息？我们显然要关注 $l$ 到 $r$ 中所有元素能否被删光。

如果 $p_i=i$，我们就可以直接把 $i$ 和 $i+1$ 删了。如果 $p_i = i+1$ 呢？很抱歉，我们发现每个数在操作的过程中，$p_i-i$ 的奇偶性保持不变，所以永远删不掉。$p_i=i+2$ 呢？只要在 $i$ 的前面，有一对数被删掉了，$i$ 就可以顺势删了。

因此设 $dp_{l,r,x}$ 表示在区间 $[l,r]$ 前删了 $x$ 对数，能否将区间 $[l,r]$ 删完（当然要满足 $2 \mid r-l+1$）。

转移考虑 $r$ 和谁配对，假设和 $i$。那么要求：

- $l \equiv i \pmod 2$，基础的奇偶性限制；
- $dp_{l,i-1,x} = 1$，显然 $i$ 之前的元素要能被删光；
- $p_i \equiv i \pmod 2$ 且 $i \le p_i \le 2i+ 2x -l$，这样我们可以选择在 $i$ 之前恰好删了 $\dfrac{p_i-i}{2}$ 对数后转移到后半部分操作，然后再回到前半部分把删完；
- $dp_{l+1,r-1,\frac{p_i-i}{2}} = 1$，注意后半部分 $x$ 的限制有变化，因为他们需要在我们操作 $(l,r)$ 之前删光。

将 $dp$ 数组求出来之后，你就可以设 $f_{i,j}$ 表示序列中前 $i$ 个数，能否删 $j$ 对。转移的时候枚举极长的被删光的后缀即可。

这样你轻松得到了一个 $O(n^4)$ 的算法，且瓶颈在于计算 $dp$。

------

这种只有 $0/1$ 结果的 DP，优化的重要手段是发掘单调性。容易发现，$dp_{l,r,*}$ 关于 $*$ 是有单调性的，因此设 $dp_{l,r}$ 表示使得原先 $dp_{l,r,*}=1$ 的最小的 $*$。

这样转移就是 $O(n^3)$ 的了。

THUSC 2024 的 T3 也是类似的思路。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=800+10;
int T,n,a[MAXN],dp[MAXN][MAXN],Dp[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i];
		ffor(l,0,n+5) ffor(r,0,n+5) Dp[l][r]=0;
		ffor(l,0,n+5) ffor(r,0,n+5) ffor(del,0,n+5) dp[l][r]=0x3f3f3f3f;
		ffor(l,1,n) ffor(del,0,n) dp[l][l-1]=0;
		ffor(len,1,n/2) for(int l=1,r=len*2;r<=n;l++,r++) {
			ffor(lst,l,r) if((lst-l)%2==0) {
				if((a[lst]-lst)%2||a[lst]>lst) continue ;
				int psl=max(dp[l][lst-1],(l-a[lst])/2);
				if((lst-a[lst])/2>=dp[lst+1][r-1]) dp[l][r]=min(dp[l][r],psl);
			}
		}
		Dp[0][0]=1;
		ffor(i,1,n) {
			ffor(j,0,n) Dp[i][j]=Dp[i-1][j];
			ffor(l,1,i) if((i-l+1)%2==0) {
				int t=dp[l][i];
				ffor(X,t,n) if(Dp[l-1][X]) Dp[i][X+(i-l+1)/2]=1;
			}
		}
		int ans=0;
		ffor(j,0,n) if(Dp[n][j]) ans=j;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：4)

比较困难的区间 dp。

观察到如果要把一对 $(l,r)$ 一起消掉，那么必然会消掉 $[l,r]$ 这段区间中的所有数。因此考虑区间 dp。

观察到 $[l,r]$ 是否能消掉与后缀状态无关，所以设 $f_{l,r}$ 表示让 $[l,r]$ 消掉，$[1,l-1]$ 最少要消掉几对。转移时枚举与 $l$ 配对的点 $k$，则此时代价为 $\max(\frac{l-a_l}{2},f_{l,k},f_{k+1,r}-\frac{k-l+1}{2})$。首先，$a_l$ 本身肯定要能消掉，必然会满足 $l\ge a_l$，代价至少为 $\dfrac{l-a_l}{2}$，而 $[l,k]$ 也一定会删空，代价至少为 $f_{l,k}$，同理，$[k+1,r]$ 也会删空，但是注意到此时 $[l,k]$ 也是空的，可以对 $f_{k+1,r}$ 产生 $\dfrac{k-l+1}{2}$ 的贡献，因此要扣掉，才能得到 $[1,l-1]$ 这段前缀至少需要的代价。对所有情况取 $\min$ 即可。

然后设 $g_i$ 表示考虑 $[1,i]$，能进行的最多操作次数。显然有转移 $g_i=\max (g_{i-1},g_{j-1}+\frac{i-j+1}{2})$。后一项成立需要条件，即需要满足 $g_{j-1}\ge f_{j,i}$，这时一定存在一种操作序列，能让 $[j,i]$ 顺利消掉，否则一定不合法。这样总时间复杂度 $O(n^3)$。

---

## 作者：_Cheems (赞：2)

考虑两个区间 $[l,r],[l_2,r_2]$，假如有 $r<l_2$，那么对 $[l_2,r_2]$ 的操作必然不会影响 $[l,r]$。

所以假如 $[L,R]$ 的某些操作需要之前若干次操作才能进行，不妨设其最大值为 $k$，那么只要 $L$ 之前的操作次数不小于 $k$ 即可，我们可以前后交替操作。

所以只关心之前操作几次，显然之前操作次数越多越好，也就是从左到右操作会更优。

另外重要的一点是，我们选取的数对间一定不存在交叉，类比括号匹配。

综上，我们可以得到 dp 设计思路：先预处理出要将一个区间完全消掉的话，此前至少要操作多少次；然后线性 dp 扫一次即可。

具体而言，令 $f_{i,j}$ 表示之前至少操作几次，分类转移：

1. $a_i,a_j$ 匹配，前提是消掉 $a_i$ 的次数不能少于消掉 $[i+1,j-1]$ 的次数：$\max (f_{i+1,j-1},\frac{i-a_i}{2})\to f_{i,j}$。

2. 内部拼接：$\max(f_{i,k},f_{k+1,j}-\frac{k-i+1}2)\to f_{i,j}$。

线性 dp 是容易的，留给你自己实现。

复杂度 $O(n^3)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 8e2 + 5;
int T, n, a[N], f[N][N], g[N], inf;

signed main(){
	cin >> T;
	while(T--){
		scanf("%lld", &n);
		memset(f, 0x3f, sizeof f), memset(g, 0, sizeof g);
		for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), f[i][i - 1] = 0;
		f[n + 1][n] = 0;
		for(int len = 2; len <= n; len += 2)
			for(int l = 1; l + len - 1 <= n; ++l){
				int r = l + len - 1;
				if(l - a[l] >= 0 && (l - a[l]) % 2 == 0 && (l - a[l]) / 2 >= f[l + 1][r - 1])
					f[l][r] = max(f[l + 1][r - 1], (l - a[l]) / 2);
				for(int k = l; k < r; ++k) f[l][r] = min(f[l][r], max(f[l][k], f[k + 1][r] - (k - l + 1) / 2));
			}
		for(int i = 1; i <= n; ++i){
			g[i] = max(g[i], g[i - 1]);
			for(int j = 1; j <= i; ++j){
				if(g[j - 1] >= f[j][i])
					g[i] = max(g[i], g[j - 1] + (i - j + 1) / 2); 
			}
		}
		printf("%lld\n", g[n]);
	}
	return 0;
}
```

---

## 作者：BreakPlus (赞：2)

将一起删的数看成括号匹配，则一个完全被删除的极大连续段一定是一个合法的括号序列。

一种删除合法当且仅当：

+ 对于每个删数的位置（对应左括号） $x$，有 $x \ge a_x$ 且 $2 \mid x- a_x$ 且 $x-a_x \le 2t$，其中 $t$ 是 $x$ 前面的匹配的括号数量（即这个操作可以插入到前面的操作序列中）；

+ 外层的括号要比内层的括号后删除。

我们还可以发现一些性质：

+ 对于任意前缀，我们应当尽可能多地删数（最大化 $t$ 显然可以使条件更松）。

+ 对于一个极大的删除连续段，为了使最外层比最内层后删（最外层的删除时间是固定的），我们应该希望内层的东西更早删。这同时也让每一个 $x-a_x$ 尽量小。


考虑针对极大删除连续段设计 DP。设 $f(i,j)$ 表示删除区间 $[i,j]$ 中所有数被删除，在 $i$ 前面至少要删多少个数。

转移不难，读者可以自行思考。

```cpp
ll n,a[805];
ll f[805][805], dp[805];
void solve(){
	n=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	memset(f, 63, sizeof(f));
	for(ll i=1;i<=n+1;i++) f[i][i-1] = 0;
	for(ll i=n;i>=1;i--){
		for(ll j=i;j<=n;j++){
			if((i-a[i])%2==0 && i>=a[i] && (i-a[i])/2 >= f[i+1][j-1]){
				f[i][j] = (i-a[i])/2;
			}
			for(ll k=i;k<j;k++){
				f[i][j] = min(f[i][j], max(f[i][k], f[k+1][j] - (k-i+1)/2));
			}
		}
	}

	memset(dp, 128+64, sizeof(dp));
	dp[0] = 0;
	for(ll i=0;i<n;i++){
		dp[i+1] = max(dp[i], dp[i+1]);
		for(ll j=i+1; j<=n; j++){
			if(f[i+1][j] <= dp[i]){
				dp[j] = max(dp[j], dp[i] + (j-i)/2);
			}
		}
	}
	printf("%lld\n", dp[n]);
}
```

---

## 作者：RainWetPeopleStart (赞：1)

机房大佬 [AK_400](https://www.luogu.com.cn/user/1024004) 还在发力。

首先，观察发现最后删掉的一定是若干段区间，再加上 $n\le 800$，考虑区间 DP。

直接设 $f_{l,r}$ 表示考虑 $[l,r]$ 的答案是不现实的，因为操作涉及两个连续的数，这样不好刻画“连续”。

我们发现可以让 $f$ 只维护一个区间的情况，最后用 DP 把这些区间组合起来。

记 $f_{l,r,k}$ 表示能否把区间 $[l,r]$ 删完，且 $[1,l-1]$ 中被删了 $k$ 个数。

我们不关心前面是否真的能删 $k$ 个数，只关心这 $k$ 个数对 $[l,r]$ 的影响。

转移有三种：

1. 合并两个区间：用 $f_{l,x,k}\wedge f_{x+1,r,k+(x-l+1)}$ 更新 $f_{l,r,k}$。

2. 延伸一个区间：用 $f_{l+1,r-1,k}\wedge (a_{l}=l-k)$ 更新 $f_{l,r,k}$。

3. 从左边删：用 $f_{l,r,k-1}$ 更新 $f_{l,r,k}$。

上面的转移可行是由于我们可以任意规定删除顺序，就是从后往前删满足条件的位置。

直接做是 $O(n^4)$ 的。

发现有第三种转移决定了 $f_{l,r,*}$ 一定是一段 $0$ 跟一段 $1$。

优化状态，定义 $f_{l,r}$ 表示 $[1,l-1]$ 中最少删几个才能把 $[l,r]$ 删完。

沿用上文的转移，有：

1. 合并两个区间：用 $\max(f_{l,x},f_{x+1,r}-(x-l+1))$ 更新 $f_{l,r,k}$。

2. 延伸一个区间：用满足 $f_{l+1,r-1}\le k\wedge (a_{l}=l-k)$ 的 $k$ 更新 $f_{l,r,k}$。（这里要求 $k$ 是偶数）

最后的 DP 是简单的，我的做法是记 $g_{i,j}$ 表示前 $i$ 个数中是否可以删 $j$ 个，转移就枚举右端点并用 $f$ 判断是否合法就行。

复杂度 $O(n^3)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1987F2)

**题目大意**

> 给定 $a_1\sim a_n$，每次可以选定一个 $a_i=i$ 的元素并删除 $a_i,a_{i+1}$，求最多操作次数。
>
> 数据范围：$n\le 800$。

**思路分析**

假如我们只删除 $a_i$，这是简单的，由于每个元素独立，因此可以任意交换删除元素的顺序。

设 $dp_{i}$ 表示 $[1,i]$ 中最多删除 $j$ 个元素，那么我们想要删除 $i$，就需要先在 $[1,i-1]$ 中删除 $i-a_i$ 个元素。

由于第 $i$ 个元素删除不影响前面的元素，因此可以任意插入在前面的操作之间，只需要 $i-dp_i\le a_i\le i$ 即可。

回到原问题，此时如果删除 $a_i$ 可能会导致某个 $j>i$ 的 $a_j$ 被删除，这要求 $[i+1,j-1]$ 已经被删除了。

因此我们可以把删除的元素看成若干个匹配的括号，容易发现每个连续的子段都是合法括号序列，以其为单位进行 dp。

我们求出 $f_{l,r}$ 表示想把 $a[l,r]$ 删空，至少要在 $a[1,l-1]$ 中删除多少元素，转移为：

- 在外面加一对括号：即先删 $a[l+1,r-1]$，再删 $a_l$。
- 连接两个括号序列：即并行删除 $a[l,k],a[k+1,r]$。

求出 $f_{l,r}$ 后用 $dp_{l-1}$ 判断能否一次性删除 $[l,r]$。

时间复杂度 $\mathcal O(n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=805;
int n,a[MAXN],f[MAXN][MAXN],dp[MAXN];
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;++i) f[i+1][i]=0;
	for(int len=2;len<=n;len+=2) for(int l=1,r=len;r<=n;++l,++r) {
		if((l-a[l])%2==0&&f[l+1][r-1]<=(l-a[l])/2) f[l][r]=(l-a[l])/2;
		for(int k=l+1;k<r;k+=2) f[l][r]=min(f[l][r],max(f[l][k],f[k+1][r]-(k-l+1)/2));
	}
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;++i) {
		dp[i]=dp[i-1];
		for(int j=i-1;j>0;j-=2) {
			if(dp[j-1]>=f[j][i]) dp[i]=max(dp[i],dp[j-1]+(i-j+1)/2);
		}
	}
	printf("%d\n",dp[n]);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

