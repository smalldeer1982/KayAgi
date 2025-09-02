# [AGC066C] Delete AAB or BAA

## 题目描述

给定一个只包含 `A` 和 `B` 的字符串 $S$。

你可以对该字符串重复进行如下操作：

- 从 $S$ 中选择连续的 $3$ 个字符，这 $3$ 个字符等于 `AAB` 或 `BAA`，然后将这 $3$ 个字符从 $S$ 中删除（删除后剩余的字符会连接在一起）。

请你求出最多可以进行多少次这样的操作。

给定 $T$ 个测试用例，请分别输出每个测试用例的答案。

## 说明/提示

### 限制

- $1\leq T\leq 10^5$
- $S$ 只包含 `A` 和 `B` 字符。
- $1\leq |S|\leq 10^6$
- 所有测试用例的 $|S|$ 之和不超过 $10^6$。

### 样例解释 1

对于第 $1$、$2$ 个测试用例，最大化操作次数的一种方法如下：

- `AABAAAB` → `AAAB` → `A`
- `BAAAAABBA` → `BAAABA` → `BAA` → （空字符串）

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10
AABAAAB
BAAAAABBA
A
B
ABA
BAA
AAAAAA
AAAABB
AABABBAABBABAAAABBAA
BBAAAAABAAAAABABAABA```

### 输出

```
2
3
0
0
0
1
0
2
5
6```

# 题解

## 作者：Rainbow_qwq (赞：8)

考虑如何判定一个 `AB` 串是可以消空的，称能消空为合法串。

手玩样例会发现，直接贪心消是不行的，比如 `BAAABA -> ABA`,`BAAABA -> BAA`。

考虑一个区间 dp，设 $dp(l,r)$ 表示能否消空 $[l,r]$。有两种转移：

- 枚举从 $k$ 断开，判断能否消空 $[l,k],[k+1,r]$.
- 若 $s_l\ne s_r$，枚举 $s_k = \text{A}$，判断能否消空 $[l+1,k-1],[k+1,r-1]$，然后将 $(s_l,s_k,s_r)$ 一起消。

然后进行 dp，设 $f_i$ 表示前 $i$ 个字符最少消成几个字符。有转移：

- $f_i + 1 \to f_{i+1}$
- 若 $dp(i,j)=1$：$f_i\to f_j$

如果一个区间 $(i,j)$ 能从中间断开来消空，则自然可以不考虑它。考虑不可断开的合法串有什么性质。

可以得出不可断开的合法串的一些必要条件：

- 区间内 $\text{A}$ 的个数为 $\text{B}$ 的两倍。
- $s_l\ne s_r$。

surprisingly 根据打表 合法串/不合法串 的结果，这也是充要条件！具体的证明是：假设我们不删头尾的 A,B，中间共有 $2n-1$ 个 $\text{A}$ 和 $n-1$ 个 $\text{B}$。相当于 $2n-1$ 个 $\text{A}$ 放进 $n$ 个空隙，根据鸽巢原理，中间一定有一个 $\text{B}$ 旁边有两个 $\text{A}$。

设 $sum_i$ 表示前 $i$ 个位置中 $2\times count_A-count_B$，则只有 $sum_{l-1}=sum_r$ 且 $s_l\ne s_r$ 时可以转移。

记录前缀中 $sum=x,s=y$ 的最小 $f$，然后就可以 $O(n)$ dp 了。[Submission](https://atcoder.jp/contests/agc066/submissions/51960636)

```cpp
#define maxn 2000005
#define inf 0x3f3f3f3f

int n;
char s[maxn];
int sum[maxn];
bool dp[5005][5005];
int mn[maxn][2];
int f[maxn];

void work()
{
	scanf("%s",s+1),n=strlen(s+1);
	For(i,1,n)sum[i]=sum[i-1]+(s[i]=='A'?1:-2);
	int sub=*min_element(sum,sum+n+1);
	For(i,0,n)sum[i]-=sub;
	
//	if(n>5000)exit(233);
//	For(i,1,n)dp[i][i-1]=1;
//	for(int len=3;len<=n;len+=3){
//		for(int i=1,j=len;j<=n;++i,++j){
//			dp[i][j]=0;
////			if(s[i]=='A' && s[j]=='A') continue;
////			if(s[i]=='B' && s[j]=='B') continue;
//			For(k,i,j-1) dp[i][j]|=(dp[i][k] && dp[k+1][j]);
//			for(int k=i+1;k<j;k+=3){
//				if(s[i]!=s[j] && s[k]=='A' && dp[i+1][k-1] && dp[k+1][j-1]){
//					dp[i][j]=1;
//					break;
//				}
//			}
////			else {
////				cout<<"i,j "<<i<<" "<<j<<"\n";
////				For(k,i,j)cout<<s[k];cout<<"\n";
////			}
//		}
//	}

	For(i,0,2*n+1) f[i]=mn[i][0]=mn[i][1]=inf;
	f[0]=0; mn[sum[0]][s[1]-'A']=0;
	For(i,1,n){
		f[i]=min(f[i],f[i-1]+1);
		f[i]=min(f[i],mn[sum[i]][!(s[i]-'A')]);
		if(i<n) mn[sum[i]][s[i+1]-'A']=min(mn[sum[i]][s[i+1]-'A'],f[i]);
	}
	cout<<(n-f[n])/3<<"\n";
}

signed main()
{
	int T=read();
	while(T--)work();
	return 0;
}
```

---

## 作者：251Sec (赞：6)

考虑刻画什么样的序列能够被删空，首先我们可以得到两个显然的必要条件：

1. A 的个数是 B 的两倍。
2. 序列的开头或结尾是 B。

（事实上这样并不太准确，比如 `AABBAA` 也是可以删空的，但是我们把它看作序列 `AAB` 和 `BAA` 的拼接，所以没有问题）

然后手玩几组小数据可以发现这似乎是充分的。考虑归纳证明：

- 长度为 $3$ 的情况下显然。
- 长度大于 $3$ 的情况，不妨设开头为 B，因为结尾为 B 的情况是对称的。序列形如一段 B 紧跟一段 A，再紧跟一段 B 和一段 A，以此循环。由于 A 的数量是 B 的两倍，所以至少存在一段 A 的长度至少为 $2$，直接找到这段 A 前面或者后面的 B 和它进行一次操作，可以发现这里进行操作的 B 一定存在方案不是开头那个 B，否则可以导出原串长度为 $3$。这样进行一次操作之后就转化成了长度更小的情况，则归纳成立。

有了这个结论之后，直接 $f(i)$ 代表前 $i$ 个字符至少剩下多少个字符，DP 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int o = 2e6;
int T, n;
char s[1000005];
int f[1000005], x[4000005], y[4000005];
int main() {
	scanf("%d", &T);
	memset(x, 0x3f, sizeof(x)), memset(y, 0x3f, sizeof(y));
	while (T--) {
		scanf("%s", s + 1), n = strlen(s + 1);
		int w = 0, minW = 0, maxW = 0;
		x[o] = 0;
		if (s[1] == 'B') y[o] = 0;
		for (int i = 1; i <= n; i++) {
			f[i] = f[i - 1] + 1, w += s[i] == 'A' ? 1 : -2;
			minW = min(minW, w), maxW = max(maxW, w);
			if (s[i] == 'B') f[i] = min(f[i], x[w + o]);
			else f[i] = min(f[i], y[w + o]);
			x[w + o] = min(x[w + o], f[i]);
			if (s[i + 1] == 'B') y[w + o] = min(y[w + o], f[i]);
		}
		for (int i = minW; i <= maxW; i++) x[i + o] = y[i + o] = 1e9;
		printf("%d\n", (n - f[n]) / 3);
	}
	return 0;
}
```

---

最后放一点碎碎念，为了不污染文章本体就放到 [云剪贴板](https://www.luogu.com.cn/paste/30hk5rcq) 了。

---

## 作者：Albert_Wei (赞：1)

我们定义一个删除的 `AAB` 或 `BAA` 所对应的区间 $[l_i, r_i]$ 为该串最靠前与最靠后元素所夹成的区间。我们发现区间之间要么并列，要么嵌套。我们称 $[l, r]$ 为合法区间当且仅当 $[l, r]$ 可以被删空且存在一个删除串所对应的区间为 $[l, r]$ （即 $l, r$ 在同一次操作中被删除）。这么定义是为了避免 $[l, r]$ 有并列的区间所拼成，导致性质被破坏。我们下证明一个区间合法的充要条件是：

1. $B$ 的个数为 $\dfrac{r - l + 1}{3}$。
2. $s_l = B$ 或 $s_r = B$。

必要性显然。充分性依然考虑对区间长度归纳。$len = 3$ 时显然。若 $len - 3$ 时成立，$len$ 时：我们容易发现存在长度 $\ge 2$ 的 $A$ 连续段。由于总共 $B$ 的个数 $\ge 2$，显然可以找到连续段的一段删除 `AAB` 或 `BAA` 后仍保证开头或结尾有 $B$。

考虑 dp，由于 $B$ 的个数为 $\dfrac{r - l + 1}{3}$，将 $B$ 视为 $-2$，$A$ 视为 $1$，在前缀和相等的位置进行转移即可。需要维护转移点后一个元素是否为 $B$。

---

## 作者：tobie (赞：1)

好题！

我们考虑一下什么样的简单序列会被删空。这里“简单序列”的定义就是任何拆分方案都无法分别删空整个序列。

考虑必要性探路。

1. `A` 的个数是 `B` 的个数的两倍，因为每次都删去两个 `A` 和一个 `B`。
2. 开头或结尾有一个 `B`。因为每次删除一定有一个 `B` 在开头或结尾。

手模几组样例发现者好像是充分的。证明可以考虑归纳法。

首先 $n=3$ 满足条件 $1$ 的只有 `AAB` 和 `BAA`，正确性显然。

假如 $n=3k$ 成立，下证 $n=3k+3$ 成立。

首先，一定可以找到一段长度大于 $2$ 的连续 `A` 段。那么这个 `A` 段的左右两侧一定可以找到一个 `B`，使得 `B` 不在最左或最右，此时删掉这三个字符，此时串长变为 $3k$，并且依旧满足上文的两条限制。

所以这就可以 dp 了。令 $dp_{i}$ 表示前 $i$ 个元素的答案，那么有

$$dp_i=dp_j+\frac {i-j} 3$$

转移条件是 $i\equiv j\pmod 3$ 且 $(j,i]$ 中 `A` 的个数为 `B` 的两倍，以及 $s_i$ 和 $s_{j+1}$ 中至少有一个 `B`。这可以开一个数组使时间复杂度降为 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000009;
char s[N];
int n,sum[N],dp[N],mx[3][N*3][2];
void gx(int &x,int y){if(y>x) x=y;}
void work()
{
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=0;i<=n*3;i++)
	for(int j=0;j<3;j++)
	for(int k=0;k<2;k++)
	mx[j][i][k]=-998244353;
	sum[0]=n;
	gx(mx[0][sum[0]][s[1]=='B'],dp[0]);
	for(int i=1;i<=n;i++)
	{
		dp[i]=dp[i-1];
		if(s[i]=='A') sum[i]=sum[i-1]-1;
		else sum[i]=sum[i-1]+2;
		if(s[i]=='A') gx(dp[i],mx[i%3][sum[i]][1]+i/3);
		else gx(dp[i],max(mx[i%3][sum[i]][0],mx[i%3][sum[i]][1])+i/3);
		gx(mx[i%3][sum[i]][s[i+1]=='B'],dp[i]-i/3);
	}
	printf("%d\n",dp[n]);
}
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--) work();
}
```

---

## 作者：ZnPdCo (赞：1)

这题评黑我觉得有点过了。其实还是比较好想的。

考虑一个区间怎么才能被消除掉：它满足可以分成若干个满足以下条件的子串：每个子串都满足 $\tt A$ 的数量是 $\tt B$ 的两倍，左端点**或**右端点是 $\tt B$。

证明可以让时间倒流，我们在这个字符串内不断添加 $\tt AAB$ 或 $\tt BAA$。

如果一个字符串是空字符串，添加 $\tt AAB$ 或 $\tt BAA$ 明显符合。

如果一个字符串符合条件，那么在两端添加 $\tt AAB$ 或 $\tt BAA$ 相当于添加了一个新的符合条件的子串，如果在中间添加 $\tt AAB$ 或 $\tt BAA$，字符串两端的字符仍旧不变，依旧符合。

所以通过归纳法可以证明。

---

所以我们设 $x_i$ 表示 $1\sim i$ 中 $\tt B$ 的数量的两倍减去 $\tt A$ 的数量。若 $x_l=x_r$，则 $[l+1,r]$ 明显是一个可以被消除掉的字符串。

所以我们容易设 $f_i$ 表示处理到第 $i$ 个字符，最少不删掉的字符的数量，明显我们需要最小化它。

那么有转移方程：
$$
f_i=\begin{cases}
f_{i-1}+1 \\
f_j & x_i=x_j,s_{j+1}={\tt B} \\
f_j & x_i=x_j,s_{i}={\tt B}
\end{cases}
$$
对于第二、三种情况，我们可以用两个 `map` 来储存每种 $x$ 下的最小 $f$ 值。

这里不使用 $f_i$ 表示最多不删除的字符数量的原因是因为不太好打。

```cpp
void solve() {
	map<ll, ll> ha, hb;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(ll i = 1; i <= n; i ++) {
		a[i] = a[i - 1], b[i] = b[i - 1];
		if(s[i] == 'A') {
			a[i] ++;
		}
		else {
			b[i] ++;
		}
		x[i] = a[i] - 2 * b[i];
		ha[x[i]] = hb[x[i]] = inf;
	}
	ha[0] = hb[0] = inf;
	for(ll i = 1; i <= n; i ++) {
		f[i] = inf;
	}
	if(s[1] == 'A') {
		ha[0] = 0;
	} else {
		hb[0] = 0;
	}
	for(ll i = 1; i <= n; i ++) {
		f[i] = min(f[i], f[i - 1] + 1);
		if(s[i] == 'A') {
			f[i] = min(f[i], hb[x[i]]);
		} else {
			f[i] = min(f[i], ha[x[i]]);
			f[i] = min(f[i], hb[x[i]]);
		}
		if(s[i + 1] == 'A') {
			ha[x[i]] = min(ha[x[i]], f[i]);
		} else {
			hb[x[i]] = min(hb[x[i]], f[i]);
		}
	}
	print((n - f[n]) / 3);
	putchar('\n');
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给定一个只包含字符 `A` 和 `B` 的字符串，每次可以删除连续的 `AAB` 或者 `BAA`，然后两边会接上，求最大操作次数。

## 题目分析

首先求最大操作次数等同于求最小的剩余字符数。删除的字符在原串中体现为若干个子串，故可以设计状态 $dp_i$ 表示只考虑前 $i$ 个字符最少可以剩下多少个字符，则有转移：

- 保留第 $i$ 个字符，$dp_{i-1}+1\rightarrow dp_i$。

- 删除一段子串 $[j,i]$，$dp_{j-1}\rightarrow dp_i$。

考虑怎样的子串能够删除，称能被删除的字符串是合法的。

结论：一个字符串 $S$ 是合法的，当且仅当其可以划分为若干个子串，使得每一个子串中 `A` 的个数是 `B` 的两倍，且端点中至少有 $1$ 个 `B`，证明如下：

充分性：考虑从空串中不断添加 `AAB` 或 `BAA` 来得到合法串，首先 `AAB` 和 `BAA` 是合法的。假设 $T$ 是合法的，则如果将新串插入 $T$ 中间，则新的 $T$ 依旧合法，否则，将新串与 $T$ 分开，则新的 $T$ 也是合法的。

必要性：考虑分成每个子串后子串内如何消除。将端点上的一个 `B` 先无视，则剩下的 `A` 的个数 $x$ 与剩下的 `B` 的个数 $y$ 始终满足 $x=2y+2>y+1$，将 `B` 视为隔板，则有 $y+1$ 个空，根据鸽巢原理，总会有一个空中有至少 $2$ 个连续的 `A`，只需要用它们把相邻的 `B` 消除，最终剩下 $2$ 个 `A` 和端点的 `B` 消除。

所以，转移时我们要考虑的子串只需要满足 `A` 的个数是 `B` 的两倍，端点中至少有一个 `B` 即可，第一个要求可以用前缀和处理，第二个要求只需分别钦定左端点和右端点为 `B` 两种情况即可 $O(n)$ 完成。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =3e6+5,M=3e6+5,inf=(1LL<<31)-1,del=1e6,mod=1e9+7;
const ll llf=1e18;
string s;
int n,p[N],dp[N],f[N],g[N]; 
inline void Main(){
	cin >>s,n=s.length(),s='#'+s;
	repn(i)p[i]=p[i-1]+(s[i]=='B'?2:-1);
	rep(i,del-n,del+2*n)f[i]=g[i]=inf;
	f[del]=0;
	if(s[1]=='B')g[del]=0;
	repn(i){
		dp[i]=dp[i-1]+1;
		if(s[i]=='B')dp[i]=min(dp[i],f[p[i]]);
		dp[i]=min(dp[i],g[p[i]]);
		if(i<n){
			if(s[i+1]=='B')g[p[i]]=min(g[p[i]],dp[i]);
		}
		f[p[i]]=min(f[p[i]],dp[i]);
	}
	cout <<(n-dp[n])/3<<'\n';
} 
signed main(){
	p[0]=del;
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：bamboo12345 (赞：0)

题意：给出一个字符串，每次可以删除一个 AAB 或者 BAA，求最多能删除多少次。

做法：

agc 的题都要猜结论，我们考虑什么样的串可以全删，直接打表。

首先我们发现 A 的数量一定是 B 的两倍，这个显然是必要条件，但是很显然不是充分的，比如 ABA 这个串就爆炸了，所以我们猜两端不能相等，但是 AABBAA 这样的串又可以消除。

但是我们发现，AABBAA 这样的串我们可以分成 AAB 和 BAA 这样的两个串分别删除，不需要一次删除，所以不考虑也是正确的。

证明一下这个结论，不知道为什么这个结论还需要证。

我们考虑第一个字符和最后一个字符因为相等一定不能同时消除，那么第一个字符被消除时肯定是一个前缀的都被消了，把这个前缀挪出来就行了。

我们考虑证明这个结论：只要一个串满足 A 的个数是 B 的两倍且两端不同就可以完全删除。

我们考虑除去两端的 AB 之后，那么一共剩下 $2n-1$ 个 A 和 $n-1$ 个 B，那么根据抽屉原理显然有一个 B 的其中一边有两个 A，那么直接删除就可以归纳证明了。

会了这个之后，我们令 A 的权为 $2$，B 的权为 $-1$，那么一段能删除的就要求和为 $0$。

我们考虑 dp，$dp_{i}$ 代表前 $i$ 个最少保留多少个字符，那么首先 $dp_{i} = dp_{i-1}+1$，然后我们考虑把 $i$ 连着的段删除，我们先预处理权的前缀和，我们开一个 `map` 记录前缀和为 $x$，下一个字符为 A/B 的 dp 值最大是多少，直接转移即可。

给出代码：

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int dp[maxn], mn[maxn * 4][2], n;
string s;
void solve() {
	cin >> s, n = s.size(), s = ' ' + s;
	for (int i = 0; i <= 3 * n; i++)
		mn[i][0] = mn[i][1] = 2e9;
	int sum = 0;
	mn[n][s[1] - 'A'] = 0; 
	for (int i = 1; i <= n; i++) {
		sum += (s[i] == 'A' ? -1 : 2);
		dp[i] = dp[i - 1] + 1;
		dp[i] = min(dp[i], mn[sum + n][1 - (s[i] - 'A')]);
		if(i < n)
			mn[sum + n][s[i + 1] - 'A'] = min(mn[sum + n][s[i + 1] - 'A'], dp[i]);
		//cout << dp[i] << endl;
	}
	cout << (n - dp[n]) / 3 << endl;
}
signed main() {
	int T; cin >> T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc066_c)

**题目大意**

> 给定一个长度为 $n$ 的字符串 $S$，每次删除一个 AAB 或 BAA 子串，问最多删除多少次。
>
> 数据范围：$n\le 10^6$。

**思路分析**

先考虑什么样的子串能被删空。

首先我们要求 A 的数量是 B 的两倍且两端至少有一个 B。

然后尝试证明这个条件是充要的：设 B 数量 $k$ 个，用 B 分割整个序列，那么有 $k$ 个空（有一个端点是 B）插 $2k$ 个 A，那么至少有一段空里 A 数量 $\ge 2$。

观察这段空，如果 $k>1$ 那么这段空至少有一个邻居是 B 且不在端点上（或者原串两端点都是 B），那么这样删掉这个 B 和段内的两个 A 就可以保持这个性质递归。

因此我们可以 dp，$dp_i=\max\left\{ dp_j+\dfrac{i-j}3\mid S_{(j,i]}\text{ is valid}\right\}$。

判定是否合法可以把 A 当 $-1$ B 当 1 求前缀和，用桶维护 $(sum_j,j\bmod 3,S_{j+1})$  对应的最大 $dp_{j}-j$ 桶优化即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5,inf=1e9;
char str[MAXN];
int dp[MAXN],f[MAXN*3][3][2];
void upd(int &x,int y) { x=x<y?y:x; }
void solve() {
	scanf("%s",str+1);
	int n=strlen(str+1);
	for(int i=1;i<=n;++i) dp[i]=-inf;
	for(int i=0;i<=3*n;++i) {
		for(int x:{0,1,2}) f[i][x][0]=f[i][x][1]=-inf;
	}
	dp[0]=f[n][0][str[1]=='B']=0;
	for(int i=1,s=n;i<=n;++i) {
		s+=(str[i]=='A'?-1:2);
		dp[i]=max(dp[i-1],f[s][i%3][1]+i);
		if(str[i]=='B') upd(dp[i],f[s][i%3][0]+i);
		if(i<n) upd(f[s][i%3][str[i+1]=='B'],dp[i]-i);
	}
	printf("%d\n",dp[n]/3);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：RockyYue (赞：0)

#### 题意

给定字符串 $s$，每次可以从中删除 `AAB` 或 `BAA`，删除后前后拼接，求最终剩下的最小字符数，要求 $O(|S|)$。

#### 解法
- DP 要 $O(n)$，从朴素方法优化。

  - 设 $f_{i,j}$ 为 $s_{[i,j]}$ 至少余下的字符数，$g_{i,j}$ 为在这一段内操作，是否能完全删除这一段。	

  - 对于 $g$ 的转移，要么是分成两段每段可行，要么是有操作需要的元素必须横跨两端，即对 $s_i,s_j$ 和中间 $s_k$ 有一次操作，需要合并后使其相邻，而 $(i,j,k)$ 操作可行充要为 $s_i\neq s_j,s_k=A$。
  - 于是 $g_{i,j}\stackrel{\lor}\longleftarrow (g_{i,k} \land g_{k,j}) \lor (legal(i,j,k) \land  g_{i+1,k-1} \land g_{k+1,j-1})$。
  - 对于 $f$，同样只需要考虑以上两种，即 $f_{i,j}\stackrel{\max}\longleftarrow \max(f_{l,k}+f_{k+1,r},legal(i,j,k)(f_{i+1,k-1}+f_{k+1,j-1}+1))$。
  - 此方法 $O(n^3)$。

- 区间 DP 优化 $O(n)$，则只记录结尾位置作状态。设 $f_i$ 为 $s_{[1,i]}$ 至少余下的字符数。

- 分析转移，第一种为直接继承 $f_j(j<i)$，即 $s_{[j+1,i]}$ 不操作。这种转移可以处理任意一个 $s_{1\dots i}$ 后缀不操作的情况，唯独不能处理的就是操作 $i$ 的情况。

- 若操作 $(i,j,k)(k<j<i)$，需要将 $s_{(k,j)}$ 和 $s_{(j,i)}$ 全部消掉，贡献为 $f_{k-1}+\frac{i-k+1}{3}$。

- 发现 $j,k$ 中一个都不能枚举，尝试简化合法条件：$s_{[k,i]}$ 可以消。贡献可以写成 $f_{k-1}-\frac{k}{3}+C(i)$，于是与 $j$ 无关，$f_{k-1}-\frac{k}{3}$ 应记录。
- 瓶颈在于，一段是否可以消的查询，先前的 $g_{i,j}$ 需要 $O(n^2)$ 预处理，其转移可归纳为，先分成若干段，再首尾消，分出来的两段再分别分成若干段每段首位消，直到所有串消至空串，则成功。
- 考虑什么样的串不能首尾消：首尾相同或首尾不同但中间没有 `A`。又有对于 `A` 的数量，只有为 `B` 两倍时串才可能合法。考虑对一个合法串首位消时如何选择中间 `A` 使两边合法，发现满足 $A,B$ 个数条件的中间位必然存在。
- 得出结论：一个单位合法串充要条件为首尾不同且 `A` 个数为 `B` 两倍，每个合法串可以由若干单位合法串首尾相接。
- 对于每个 $k$，记录 $s_k$ 和 $cntA_{k-1}-2cntB_{k-1}$（$cnt$ 为个数前缀和），可以 $O(n)$。

---

