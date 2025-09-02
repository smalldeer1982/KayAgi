# [ARC065F] シャッフル

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc065/tasks/arc065_d

長さ $ N $ の `0`、`1` からなる文字列 $ S $ があります。あなたは、以下の操作を各 $ 1≦i≦M $ に対し $ i $ の昇順に行います。

- $ S $ のうち、左から $ l_i $ 文字目から $ r_i $ 文字目までの部分文字列を自由な順番で並び替える。

ただし、$ l_i $ は非減少です。

$ M $ 回の操作後の $ S $ としてありうるものの数を $ 1000000007(=\ 10^9+7) $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2≦N≦3000 $
- $ 1≦M≦3000 $
- $ S $ は`0`, `1` からなる。
- $ S $ の長さは $ N $ と等しい。
- $ 1≦l_i\ <\ r_i≦N $
- $ l_i\ ≦\ l_{i+1} $

### Sample Explanation 1

$ 1 $回目の操作後の $ S $ としてありうるものは、 `01001`, `00101`, `00011` の $ 3 $ つです。 $ 2 $回目の操作後の $ S $ としてありうるものは、 `01100`, `01010`, `01001`, `00011`, `00101`, `00110` の $ 6 $ つです。

## 样例 #1

### 输入

```
5 2
01001
2 4
3 5```

### 输出

```
6```

## 样例 #2

### 输入

```
9 3
110111110
1 4
4 6
6 9```

### 输出

```
26```

## 样例 #3

### 输入

```
11 6
00101000110
2 4
2 3
4 7
5 6
6 10
10 11```

### 输出

```
143```

# 题解

## 作者：RedBlackTree (赞：11)

【题目链接】

[Luogu AT2161 [ARC065D] シャッフル / Shuffling](https://www.luogu.com.cn/problem/AT2161)

【思路】

校队考试题，当时没做出来，~~教练把单调不减扔到了最下面导致没有看到~~。

因为 $l_i$ 单调不减，所以可以初步定义状态：

设 $dp[i]$ 表示考虑到前 $i$ 个字符的数量。

但我们发现没办法转移和求解，于是再加一维：

设 $dp[i][j]$ 为前 $i$ 位使用 $j$ 个 $1$ 时的数量。

于是可以推出状态转移方程：

$\begin{cases}
dp[i][j]+=dp[i-1][j]\\
dp[i][j]+=dp[i-1][j-1] &j>0
\end{cases}$

可我们发现 $1$ 也是不能随便放的，于是我们算出上界和下界就可以了（具体实现见代码）。

```cpp
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MAXN = 3005;
const int MOD = 1000000007;

int n, m;
int maxr[MAXN], pre[MAXN];
//maxr[i]维护从 i 点最远可以和哪里重新排列，pre[i]维护前 i 个点中 1 的数量 
int dp[MAXN][MAXN]; 
//前 i 位使用 j 个 1 时的答案数量
string s;

int main() {
	cin >> n >> m;
	cin >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++) {
		maxr[i] = i;
		//最开始可以保证自己可以到自己 
		pre[i] = pre[i - 1] + s[i] - '0';
		//因为是 0 和 1，所以求 1 的数量等价于前缀和 
	}
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		maxr[l] = max(maxr[l], r);
		//保存最远的点 
	}
	for (int i = 1; i <= n; i++) {
		maxr[i] = max(maxr[i], maxr[i - 1]);
		//会有之前的区间覆盖这个区间 
	}
	dp[0][0] = 1; 
	for (int i = 1; i <= n; i++) {
		int maxn = min(i, pre[maxr[i]]);
		//上界，最优情况为 i 个点全放 1，但存在将所有可以排列的点放到前面也填不满的情况 
		int minn = max(0, i - (maxr[i] - pre[maxr[i]]));
		//下界，最优情况为没有 1，但存在后面剩下的位置放不下所有 1，只能往前放的情况 
		for (int j = minn; j <= maxn; j++) {
			dp[i][j] += dp[i - 1][j];
			dp[i][j] %= MOD;
			//放 0 
			if (j) {
				dp[i][j] += dp[i - 1][j - 1];
				dp[i][j] %= MOD;
			}
			//放 1 
		}
	}
	cout << dp[n][pre[n]] << endl;
	return 0;
}
```

---

## 作者：Arghariza (赞：8)

### [ARC065D シャッフル / Shuffling](https://www.luogu.com.cn/problem/AT2161)

$n,m\le 3000$，明摆着 $O(n^2)$。

设 $f_{i,j}$ 表示考虑前 $i$ 位填了 $j$ 个 $1$ 的方案数。

显然有 $f_{i,j}\gets f_{i-1,j-1}+f_{i-1,j}$，关键是转移上下界如何确定，因为有些地方是不能放 $1$ 的。

于是可以预处理出每个 $i$，能随意排列到的最右端点 $r_i$；以及每个前缀 $1$ 的个数 $c_i$。

则转移中 $j$ 的下界的话你当然希望前 $i$ 个位尽量放 $0$，所以先把 $i$ 到 $r_i$ 尽量全放 $1$，于是 $l_j=\max\{0,i-(r_i-c_{r_i})\}$。

对于上界，你也当然希望前 $i$ 位尽量放 $1$，所以先把 $r_{c_i}$ 个 $1$ 都放 $i$ 里面，于是 $r_i=\min\{i,r_{c_i}\}$。

然后就可以愉快地转移啦！

[AC 记录](https://atcoder.jp/contests/arc065/submissions/35464170)

---

## 作者：傅天宇 (赞：7)

[luogu](https://www.luogu.com.cn/problem/AT2161)

[atcoder](https://atcoder.jp/contests/arc065/tasks/arc065_b)

考虑 $dp$，用 $f_{i,j}$ 表示操作到了第 $i$ 个区间，与第 $i+1$ 个区间所交的区间中有 $j$ 个 $1$ 时的不同的序列个数。

每次转移，只要考虑放置 $1$ 的位置的方案即可。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

const int MOD=1e9+7;
const int N=3005;

int n,m,sum[N],nt[N],f[N][N],pre[N],Ans=1,r[N],l[N];
char s[N];

signed main()
{
//	freopen("count.in","r",stdin);
//	freopen("count.out","w",stdout);
	cin>>n>>m;
	FOR(i,1,n) cin>>s[i];
	s[++n]='0';
	FOR(i,1,n)
	{
		sum[i]=sum[i-1]+(s[i]-'0');
		nt[i]=i;
	}
	FOR(i,1,m)
	{
		cin>>l[i]>>r[i];
		nt[l[i]]=max(nt[l[i]],r[i]);
	}
	FOR(i,1,n) nt[i]=max(nt[i],nt[i-1]);
	f[1][sum[nt[1]]]=1;
	FOR(i,2,n)
	{
		int tmp=sum[nt[i]]-sum[nt[i-1]];
		FOR(j,0,nt[i-1]-i+1) f[i][j+tmp]=(f[i-1][j]+f[i-1][j+1])%MOD;
	}
	cout<<f[n][0];
	return 0;
}
```



---

## 作者：Lynkcat (赞：5)

FTY 的做法太神仙了，我疯狂膜拜。

首先容易发现，可以将完全包含的区间全部去掉。

接下来设 $R_i$ 表示通过操作能走到 $i$ 位置的最远位置，这个可以轻松求出来，并且满足 $R_{i-1}\leq R_i$。

我们接下来去思考通过确定每个位置是 $0/1$ 来确定方案数。

接下来就是一个很神的 dp 状态设计，设 $dp_{i,j}$ 为确定了 $1\sim i-1$ 的取值后，$i\sim R_i$ 中有 $j$ 个 $1$ 的方案。


考虑 $i$ 向右移的时候会有多少个新增的 $1$ 能移到 $i$ 位置，显然为 $s_{R_{i}}-s_{R_{i-1}}$，$s_i$ 表示 $1\sim i$ 的 $1$ 的个数。

设 $x=s_{R_{i}}-s_{R_{i-1}}$，那么有  $dp_{i,j}=dp_{i-1,j-x}+dp_{i-1,j-x+1}$ ，第一种转移是 $i-1$ 的位置放 $0$，第二种表示放 $1$。

这样子转移需要判一些特殊情况，比如 $j-x> R_{i-1}-i+1$，这个时候是不能转移的，因为从上一个区间转移过来的最多的 $1$ 的个数一定是当前这个区间与上一个区间的交的长度。 

注意到这样子答案并不是 $dp_{n,0}$，因为第 $n$ 个位置放什么还没有确定过，所以要在原字符串后加上一个 $0$，答案为 $dp_{n+1,0}$。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 1000000007
#define int ll
#define N 5005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int tot;
pa E[N];
int ans;
int n,m;
char st[N];
int s[N],R[N];
int f[N][N];
signed main()
{
	n=read(),m=read();
	scanf("%s",st+1);
	st[++n]='0';
	for (int i=1;i<=n;i++)
		s[i]=s[i-1]+(st[i]=='1');
	for (int i=1;i<=n;i++) R[i]=i;
	for (int i=1;i<=m;i++) 
	{
		int l=read(),r=read();
		R[l]=max(R[l],r);
	}
	for (int i=1;i<=n;i++)
		R[i]=max(R[i],R[i-1]);
	f[1][s[R[1]]]=1;
	for (int i=2;i<=n;i++)
	{
		int x=s[R[i]]-s[R[i-1]];
		for (int j=x;j<=R[i]-i+1;j++)
		{
			if (j-x>R[i-1]-i+1) continue;
			if (j-x<=R[i-1]-(i-1)+1)
				f[i][j]=(f[i][j]+f[i-1][j-x])%mod;
			if (j-x+1<=R[i-1]-(i-1)+1)
				f[i][j]=(f[i][j]+f[i-1][j-x+1])%mod;
		}
	}
	writeln(f[n][0]);
	
}
/*

*/
```

这样写不比组合数牛多了（

疯狂膜拜疯狂膜拜 FTY。

---

## 作者：ReTF (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc065_d)

设 $f_{i,j}$ 表示第 $i$ 个区间含有 $j$ 个 $1$，确定 $l_i$ 之前的数的方案数。

若 $l_i>r_{i-1}$，则区间之间互相独立，可以将 $l_{i-1}$ 和 $r_{i-1}$ 之间的数全部确定，有转移

$$f_{i,S}=\sum_{j}f_{i-1,j}\dbinom{r_{i-1}-l_{i-1}+1}{j}$$

其中 $S$ 是串中 $l_i$ 到 $r_i$ 中 $1$ 的个数。

否则，若 $r_i\ge r_{i-1}$，则对第 $i$ 个区间的操作没有任何作用，可以直接跳过。

否则，有转移：

$$f_{i,j}=\sum_kf_{i-1,j-S+k}\dbinom{l_i-l_{i-1}}{k}$$

其中 $S$ 是串中 $r_{i-1}+1$ 到 $r_i$ 中 $1$ 的个数。

转移枚举 $k\le l_i-l_{i-1}$，因为 $l_i$ 的变化量不超过 $n$，所以复杂度是 $O(n^2)$ 的。

总复杂度为 $O(n^2)$。

---

## 作者：Piwry (赞：4)

拿组合数推了半天有点裂开...（

## 解析

考虑模拟整个过程。可以发现，若第 $i$ 个操作的区间与第 $i-1$ 个操作的区间**有交**，当第 $i$ 个操作执行后，区间 $[l_{i-1}, l_i-1]$ **就被确定了**（因为左端点递增）

于是我们考虑 dp。设 $dp(i, j)$ 表示处理到第 $i$ 个区间，$[1, l_i-1]$ 有 $j$ 个 $1$ 的方案数

每次转移就枚举 $[l_{i-1}, l_i-1]$ 放多少个 $1$，并用组合数算方案（给定$n$ 个 $0$、$m$ 个 $1$，求不同的排列数；其答案就为 $\frac {(n+m)!}{n!\cdot m!}$）

其中 $[l_{i-1}, l_i-1]$ 可以放的 $1$ 的数量的上下界是需要计算的：若 $[1, r_i]$ 有 $x$ 个 $1$，$[1, l_i-1]$ 有 $j$ 个 $1$，那么可以知道 $[l_{i-1}, l_i-1]$ 至多可以放 $(x-j)$ 个 $1$；下界的计算也类似

这样我们就需要做三层循环：一层枚举操作（$i$），一层枚举 $j$，一层枚举 $[l_{i-1}, l_i-1]$ 中 $1$ 的数量。考虑当第一层循环枚举 $i$ 期间，最内层循环进入次数的上界是 $n$ 次（很松），每次进入的执行次数的上界是 $|[l_{i-1}, l_i-1]|$；由于 $l_i$ 单调递增，因此算法总复杂度是 $O(n^2)$ 的

（事实上我在实现时还处理了第二次循环枚举的 $j$ 的上下界...不过 yy 下这应该只能使算法在平均情况下快些（存疑），最坏复杂度仍是 $O(n^2)$ 的）

注意有时候会遇到询问右端点递减的情况，我们需要对询问做处理；对每段右端点递减的询问只留下右端点最大的那个询问（可理解为去掉 “被覆盖” 的区间）。可以证明这和原来的询问是等价的。否则完全按刚才的方式 dp 会出问题

## CODE

解析中没提到的细节部分可以参考代码

```cpp
#include <cstdio>
#include <iostream>
using std::min;
using std::max;

const int MAXN =3020, M =1e9+7;

/*------------------------------Math------------------------------*/

int Pow(int x, int k){
	int ans =1;
	for(; k; x =1ll*x*x%M, k >>=1)
		if(k&1)
			ans =1ll*ans*x%M;
	return ans;
}

int fact[MAXN], fact_inv[MAXN];

void pre_fact(){
	fact[0] =1;
	for(int i =1; i < MAXN; ++i)
		fact[i] =1ll*i*fact[i-1]%M;
	fact_inv[MAXN-1] =Pow(fact[MAXN-1], M-2);
	for(int i =MAXN-2; i >= 0; --i)
		fact_inv[i] =1ll*(i+1)*fact_inv[i+1]%M;
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<3)+(x<<1)+(48^c), c =getchar();
	return (f) ? -x : x;
}

char s[MAXN];
int l[MAXN], r[MAXN];
int dp[MAXN][MAXN];/*处理到第 i 个区间，[1, l_i-1] 有 j 个 1，的方案数*/
int j_min[MAXN], j_max[MAXN];
int sum[MAXN];/*"1" 数量的前缀和*/

int main(){
	pre_fact();
	int n =read(), m =read();
	scanf("%s", s+1);
	int tot =0;
	for(int i =0; i < m; ++i){
		l[tot] =read(), r[tot] =read();
		if(tot == 0 || r[tot] > r[tot-1])/*去除 " 被覆盖 " 的区间*/
			++tot;
	}
	m =tot;
	
	for(int i =1; i <= n; ++i)
		sum[i] =sum[i-1]+s[i]-'0';
	
	l[m] =r[m] =n+1;
	int ans =1;
	for(int i =0; i <= m; ++i){/*总复杂度实质上是 n^2 的*/
		if(i == 0 || r[i-1] < l[i]){
			j_min[i] =j_max[i] =sum[l[i]-1];
			dp[i][sum[l[i]-1]] =1;
			if(i != 0){
				int res =0;
				int len =r[i-1]-l[i-1]+1;
				for(int j =j_min[i-1]; j <= j_max[i-1]; ++j)
					res =(res+1ll*dp[i-1][j]*fact[len]%M*fact_inv[sum[r[i-1]]-j]%M*fact_inv[len-(sum[r[i-1]]-j)]%M)%M;
				ans =1ll*ans*res%M;
			}
		}
		else{
			int len_l_r =r[i-1]-l[i-1]+1,
				len_l_l =l[i]-l[i-1];
			j_min[i] =0x3f3f3f3f;
			j_max[i] =-0x3f3f3f3f;
			for(int j =j_min[i-1]; j <= j_max[i-1]; ++j){
				/*"(len_l_r-(sum[r[i-1]]-j))": [l_{i-1}, r_{i-1}] 中 "0" 的个数*/
				/*"sum[r[i-1]]-j": [l_{i-1}, r_{i-1}] 中 "1" 的个数*/
				int k_min =max(0, len_l_l-(len_l_r-(sum[r[i-1]]-j))),
					k_max =min(len_l_l, sum[r[i-1]]-j);
				for(int k =k_min; k <= k_max; ++k){
					dp[i][j+k] =(dp[i][j+k]+1ll*dp[i-1][j]*fact[len_l_l]%M*fact_inv[k]%M*fact_inv[len_l_l-k]%M)%M;
					j_min[i] =min(j_min[i], j+k);
					j_max[i] =max(j_max[i], j+k);
				}
			}
		}
	}
	printf("%d", ans);
}
```

---

## 作者：Leasier (赞：2)

十分困难 /dk

------------

令 $R_i$ 表示所有满足 $l = i$ 的操作中，$r$ 的最大值，则我们只关心 $\forall R_i \neq 0, [i, R_i]$ 的操作。

注意到当只有一个操作 $[1, n]$ 时答案为 $C_n^{cnt}$（其中 $cnt$ 表示 $0$ 的个数），而组合数的递推式为 $C_n^m = C_{n - 1}^m + C_{n - 1}^{m - 1}$，考虑仿照此设计 dp。

设 $dp_{i, j}$ 表示重排后 $[1, i]$ 中有 $j$ 个 $0$ 的方案数。

考虑一个重排方案合法的条件：

- $\forall i \in [1, n]$， $[1, i]$ 中的 $0/1$ 个数均在前 $i$ 个数的 $0/1$ 个数最小 / 大值所框定的区间中。

前 $i$ 个数内的 $0/1$ 个数的最小 / 大值可以通过每次对 $[i, R_i]$ 贪心地升 / 降序排序求出，然后就不难框定 $j$ 的范围进行 dp 了。

时间复杂度视实现可能为 $O(n^2)$ 或 $O(n^2 \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int mod = 1e9 + 7;
int maxr[3007], pre0[3007], pre1[3007], dp[3007][3007];
char s[3007], temp[3007];

int main(){
	int n, m, cnt = 0;
	cin >> n >> m;
	cin >> &s[1];
	for (int i = 1; i <= m; i++){
		int l, r;
		cin >> l >> r;
		maxr[l] = max(maxr[l], r);
	}
	for (int i = 1; i <= n; i++){
		temp[i] = s[i];
	}
	for (int i = 1; i <= n; i++){
		if (maxr[i] != 0) sort(temp + i, temp + maxr[i] + 1);
		pre0[i] = pre0[i - 1] + (temp[i] == '0' ? 1 : 0);
	}
	for (int i = 1; i <= n; i++){
		temp[i] = s[i];
	}
	for (int i = 1; i <= n; i++){
		if (maxr[i] != 0) sort(temp + i, temp + maxr[i] + 1, greater<char>());
		pre1[i] = pre1[i - 1] + (temp[i] == '1' ? 1 : 0);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++){
		for (int j = i - pre1[i]; j <= pre0[i]; j++){
			dp[i][j] = dp[i - 1][j];
			if (j > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
		}
	}
	for (int i = 1; i <= n; i++){
		if (s[i] == '0') cnt++;
	}
	cout << dp[n][cnt];
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：1)


考虑 $O(n^2)$ 的 DP。设 $f_{i,j}$ 代表前 $i$ 个数填了 $j$ 个 $1$ 的方案数。转移显然是 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}$。

问题在于什么样的 $j$ 是合法的。预处理出每个左端点可以“支配”到的右端点，这部分以内是可以随便交换的。显然，如果存在一个可交换区间 $[l,r]$，那么 $\forall x\in [l,r]$，$x$ 都能够支配到 $r$。

扫描到第 $i$ 个位置时，$1$ 的个数最多是将支配范围内的 $1$ 全部搞过来（当然不能超过 $i$），最少是能扔出多少 $1$ 到支配范围就扔多少（当然不能少于 $0$），直接转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

int n, m, s[5005], R[3005]; 
char a[3005]; 
int f[3005][3005]; 

int main(void) {
    cin >> n >> m >> a + 1; 
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + (a[i] - '0'); 
    for (int i = 1; i <= m; ++i) {
        int l, r; cin >> l >> r; 
        R[l] = max(R[l], r);         
    }
    for (int i = 1; i <= n; ++i) R[i] = max({i, R[i], R[i - 1]}); 
    f[0][0] = 1; 
    for (int i = 1; i <= n; ++i) {
        int r = min(i, s[R[i]]); 
        for (int j = max(0, s[R[i]] + i - R[i]); j <= r; ++j)
            f[i][j] = (f[i - 1][j] + (j ? f[i - 1][j - 1] : 0)) % P; 
    }
    cout << f[n][s[n]] << "\n"; 
    return 0; 
}
```

---

## 作者：Crosser (赞：0)

## ARC065'F シャッフル (Shuffle)

$\text{*2300, dp, greedy.}$

虽然 AT 有 $2600$ 但是现在再回来看好像每一步都很简单。

数据范围启示我们写一个 $\mathcal O(n^2)$ 的算法。如果可以完全 shuffle，那么显然是一个 $C_{i,j}=C_{i-1,j}+C_{i-1,j-1}$ 的组合数，但是这里的 shuffle 加上了一些限制。

考虑沿用组合数的递推式：$dp_{i,j}$ 为前面 $i$ 位 $j$ 个 $1$ 的方案数，而我们要做的就是钦定能够被转移到的区间的上下界。

因为 $l_i$ 单调不减，所以显然可以得到每个元素向右所能走到最远的地方 $R_i$。在可控范围内使得 $1$ 最多或者最少就是上下界，这显然是贪心问题。

具体的，上界就是把 $1$ 往前放，因此上界为 $[1,R_i]$ 内 $1$ 的数量。

下界是把 $1$ 往后放，因此下界为 $i$ 除去 $[1,R_i]$ 内 $0$ 的数量。

因为可能有太多 $1$ 或者 $0$，所以记得与 $[0,i]$ 取交集。

注意不合法状态和边界状态和组合数处理都是同理的。
- $dp_{i,0}=dp_{i-1,0}$。
- $dp_{0,0}=1$。
- 不合法状态为 $0$。

**顺带一提**，官方题解使用了区间 dp 的理解方式，然后因为 $L$ 和 $R$ 相关把其中的一维优化掉了。看看这么想会不会帮助你理解这道题。

[AC Rec](https://www.luogu.com.cn/record/179061141).

---

## 作者：0xyz (赞：0)

妙妙题。

观察到有 $l_i\le l_{i+1}$，从而一定是从前到后逐渐固定。同时一定是 $O(n^2)$ 的算法。

我们假设 $f_{i,j}$ 代表最后前 $i$ 位恰有 $j$ 个 $1$ 的不同 $s[1…i]$ 个数。$s_i$ 可以等于 $0$ 和 $1$，从而 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}$。

但是我们有一些限制。我们前 $s[1…i]$ 最多多少个 $1$？我们使用贪心，我们操作所有 $[l_i,r_i]$ 时，尽量把所有 $1$ 集中在区间左侧即可。最少多少个 $1$？同理，我们操作所有 $[l_i,r_i]$ 时，尽量把所有 $0$ 集中在左边即可。因为是 $O(n^2)$ 的，所以一下就想到暴力。确定了前缀 $1$ 的个数的上下界后直接递推就可以了。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=3010,mod=1e9+7;
ll n,m,s[_],t[_],l[_],r[_],mn[_],mx[_],f[_][_];
string w;
int main(){
	cin>>n>>m>>w;
	for(ll i=1;i<=n;i++)s[i]=t[i]=w[i-1]-48;
	for(ll i=1;i<=m;i++)cin>>l[i]>>r[i];
	for(ll i=1;i<=m;i++){
		ll c1=0,j;
		for(j=l[i];j<=r[i];j++)c1+=s[j];
		for(j=l[i];c1--;j++)s[j]=1;
		for(;j<=r[i];j++)s[j]=0;
	}
	for(ll i=1;i<=n;i++)mx[i]=mx[i-1]+s[i];
	for(ll i=1;i<=m;i++){
		ll c0=0,j;
		for(j=l[i];j<=r[i];j++)c0+=1-t[j];
		for(j=l[i];c0--;j++)t[j]=0;
		for(;j<=r[i];j++)t[j]=1;
	}
	for(ll i=1;i<=n;i++)mn[i]=mn[i-1]+t[i];
	f[0][0]=1;
	for(ll i=1;i<=n;i++)
		for(ll j=mn[i];j<=mx[i];j++){
			f[i][j]=f[i-1][j];
			if(j)f[i][j]=(f[i][j]+f[i-1][j-1])%mod;
		}
	cout<<f[n][mn[n]]<<'\n';
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

$\text{Difficulty: }\color{#FF8000}\text{2652}$。

考虑 $dp_{i,j}$ 表示看到第 $i$ 位，前缀有 $j$ 个 $0$。

考虑看到每一位至少，至多有多少 $0$。记能和 $i$ 交换的最大位置 $k$。

不难发现想要至多 $0$ 只需要把 $k$ 前缀的所有 $0$ 放前面，至少相反。

只要将不符合要求的状态赋值为 $0$ 即可。

[提交记录](https://atcoder.jp/contests/arc065/submissions/40570389)。

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc065_d)
# 题目描述
一个 `01` 串 $s$，有 $M$ 次操作，对于每一次操作 $l_{i}$，$r_{i}$，可以将 $l_{i}$ 至 $r_{i}$ 的字串重新排列。求最后能出现多少个不同的串。

答案对 $10^{9}+7$ 取模。
# 题目分析
处理出对于每个 $i$，能排列到的最右端点 $r_i$；以及每个前缀 $1$ 的个数 $c_i$。

则转移中 $j$ 的下界即为前 $i$ 个位尽量放 $0$，把 $i$ 到 $r_i$ 尽量全放 $1$，于是：

$l_j=\max\{i-(r_i-c_{r_i}),0\}$。

对于上界，同理前 $i$ 位尽量放 $1$，所以 $r_{c_i}$ 个 $1$ 都放 $i$ 里面，于是：

$r_i=\min\{i,r_{c_i}\}$。

得到这两个边界之后就比较好实践了。~~码风不好这里就不放了。~~

---

