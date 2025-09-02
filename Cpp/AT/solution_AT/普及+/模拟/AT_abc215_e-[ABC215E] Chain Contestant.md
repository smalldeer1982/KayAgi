# [ABC215E] Chain Contestant

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc215/tasks/abc215_e

別世界の AtCoder では現在、 AAC, ..., AJC の $ 10 $ 種類のコンテストが開催されており、これから $ N $ 回のコンテストが開催されます。  
 各コンテストの種類は文字列 $ S $ として与えられ、 $ S $ の $ i $ 文字目が $ x $ なら $ i $ 回目には A$ x $C が開催されます。  
 シカの AtCoDeer くんは、 $ N $ 個のコンテストから $ 1 $ 個以上いくつか選んで、以下の条件を満たすように選んで出場します。

- 出るコンテストを順番を保ったまま抜き出したとき、コンテストの種類ごとにひとかたまりとなっている。
  - 厳密には、 AtCoDeer くんが $ x $ 個のコンテストに出場し、そのうち $ i $ 回目のコンテストの種類が $ T_i $ であるとき、全ての $ 1\ \le\ i\ <\ j\ <\ k\ \le\ x $ を満たす整数組 $ (i,j,k) $ に対して、 $ T_i=T_k $ であるならば $ T_i=T_j $ でなければならない。

AtCoDeer くんが出場するコンテストの選び方として考えられるものの総数を $ 998244353 $ で割った余りを求めてください。  
 ただし、 $ 2 $ つのコンテストの選び方が異なるとは、あるコンテスト $ c $ が存在して、片方の選び方では $ c $ に出場するがもう片方の選び方では出場しないということを指します。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 1000 $
- $ |S|=N $
- $ S $ は `A` から `J` までの英大文字のみからなる

### Sample Explanation 1

例えば、 $ 1,3 $ 回目のコンテストに出場する、 $ 2,4 $ 回目のコンテストに出場するという選び方は条件を満たします。 一方、 $ 1,2,3,4 $ 回目のコンテストに出場する場合、 ABC への出場がひとかたまりになっておらず、整数組 $ (i,j,k)=(1,2,3) $ について条件に違反します。 また、全てのコンテストに出場しないということも認められません。 問題文の条件に適する出場するコンテストの選び方は $ 13 $ 通りあります。

### Sample Explanation 2

総数を $ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
4
BGBH```

### 输出

```
13```

## 样例 #2

### 输入

```
100
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBIEIJEIJIJCGCCFGIEBIHFCGFBFAEJIEJAJJHHEBBBJJJGJJJCCCBAAADCEHIIFEHHBGF```

### 输出

```
330219020```

# 题解

## 作者：AlicX (赞：4)

## Solution 

考场 `(s&w)==w` 写成了 `s&w==w` 调了 1h，警钟敲烂。

先转化一下题目条件：对于一个满足条件的子集，相同的元素一定连续出现。

然后不难想到定义 $f_{i,j}$ 表示前 $i$ 个元素，以字符 $j$ 结尾的方案数，但是没法转移，所以重新定义 $f_{i,s,j}$ 表示前 $i$ 个元素，取过的元素集合为 $s$，以字符 $j$ 结尾的方案数。

转移无非两种情况：

1. $a_i$ 这种字符在前面出现过，$f_{i,j,a_i}=f_{i-1,j,a_i}$。

2. $a_i$ 这种字符在前面并未出现过，$f_{i,j,a_i}=\sum\limits_{p=1}^{10}\sum\limits_{k=1}^{i-1}f_{k,j,p}$。

发现其中的 $\sum\limits_{k=1}^{i-1}f_{k,j,p}$ 可以用前缀和优化，于是总的时间复杂度为 $O(nm2^m)$，其中 $m$ 为 $10$，即为 `A` 到 `J` 的字符数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1010,M=1<<11,K=11,Mod=998244353;  
int n; 
char a[N]; 
int f[N][M][K],g[N][K];   
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); } 
	return x*f;
} 
signed main(){ 
//	freopen("chain.in","r",stdin); 
//	freopen("chain.out","w",stdout); 
	n=read(); int ans=0; 
	for(int i=1,x;i<=n;i++) cin>>a[i],x=a[i]-'A',f[i][1<<x][x]=1;  
	int p=a[1]-'A'; g[1<<p][p]=1; 
	for(int i=2;i<=n;i++){ 
		int x=a[i]-'A',w=1<<x; 
		for(int s=0;s<M;s++){ 
			if((s&w)==w){ 
				f[i][s][x]=(f[i][s][x]+g[s][x])%Mod; 
				continue; 
			} int sx=s|w;  
			for(int j=0;j<K;j++) if(j!=x) f[i][sx][x]=(f[i][sx][x]+g[s][j])%Mod; 
		} for(int s=0;s<M;s++) for(int j=0;j<K;j++) g[s][j]=(g[s][j]+f[i][s][j])%Mod; 	
	} for(int i=1;i<=n;i++){ 
		for(int s=0;s<M;s++){ 
			for(int j=0;j<K;j++){ 
				ans=(ans+f[i][s][j])%Mod; 
			} 
		} 
	} printf("%lld\n",ans); 
	return 0;
} /*

*/ 
```



---

## 作者：liangbowen (赞：4)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc215_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17454445.html)

萌萌 DP 题。

## 思路

题目就是在说从 $a$ 里面按顺序掏出来一些字母，使得相同的字母都是相邻的（比如 `AABBBBCD` 可行，`AAABBCAA` 不行）。

看起来很不可做，突破口在于 $\text{A} \sim \text{J}$ 一共只有 $10$ 个字母，考虑**状压**。

---

设 $dp_{i,s}$ 表示选第 $i$ 个字母，当前选取的子集为 $s$（二进制状压），方案数。

直接刷表。对于子集 $s$ 中的一个已选位 $i$，枚举 $i < j \le n$：

+ 如果 $a_i = a_j$，说明可以将 $s$ 扩充上 $a_j$，所以 $dp_{j,s} \gets dp_{i,s}$。
+ 如果 $a_j \ne a_j$，分两种情况：
  + $a_j$ 已经在 $s$ 里出现过。由于 $a_i \ne a_j$，所以 $a_j$ 与它之前的伙伴并不相邻，不合法。
  + $a_j$ 并没有出现过。于是可以新开一个伙伴的组合，即 $dp_{j, s \cap a_i} \gets dp_{i, s}$。

初始化 $dp_{i, \{a_i\}} = 1$，答案即 $\sum\limits_{} dp_{i, s}$。

## 代码

时间复杂度 $O(n^2 2^T)$，$T$ 是 $a$ 出现的不同字母数。注意到代码里的两层枚举都有剪枝，所以实际跑起来飞快。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 998244353;
int dp[1005][(1 << 10) + 5]; //dp[i][j] : 当前选第 i 个字母，选取子集为 j，方案数
int main()
{
	int n; string a;
	cin >> n >> a;
	for (char &x : a) x -= 'a';
	a = '%' + a;
	
	for (int i = 1; i <= n; i++) dp[i][1 << a[i]] = 1;
	for (int s = 0; s < (1 << 10); s++)
		for (int i = 1; i <= n; i++)
			if (s & (1 << a[i]))
				for (int j = i + 1; j <= n; j++) {
					if (a[i] == a[j])             (dp[j][s] += dp[i][s]) %= mod;
					else if (!(s & (1 << a[j])))  (dp[j][s | (1 << a[j])] += dp[i][s]) %= mod;
				}
	int ans = 0;
	for (int s = 0; s < (1 << 10); s++)
		for (int i = 1; i <= n; i++)
			ans = (ans + dp[i][s]) % mod;
	cout << ans;
}
```

希望能帮助到大家！

---

## 作者：_zzzzzzy_ (赞：1)

## 思路
考虑状压 DP，我们设 $dp[i][ch][st]$ 表示在前 $i$ 个里面选 $ch$ 表示选的序列以 $ch$ 结尾，$st$ 表示选的字母的状态，范围是 $2^{10}$。

先转移不选第 $i$ 个点的，可以写出转移式 $dp[i][ch][st]=dp[i-1][ch][st]$。

然后转移选第 $i$ 个点的，枚举转移的状态 $st$，我们再分成两种情况，如果选过那一种字符，就只存在一种转移 $dp[i][ch][st]=dp[i][ch][st]+dp[i-1][ch][st]$，表示将第 $i$ 个字符接在后面，显然只能最后一个字符是 $ch$ 才能进行转移，然后考虑没有选过的情况，这种好想的多就不解释了，$dp[i][ch][st|(1<<ch)]=dp[i][ch][st|(1<<ch)]+dp[i-1][x][st]$，这里的 $x$ 表示的是暴力枚举的字符串的最后的那一个字符。

最后一步就是初始化，我们可以想到当我们不选时显然是有一种情况的 $dp[0][0][0]=1$，最后记得减去 $dp[0][0][0]$，因为不能有空串。

当然这个 DP 还可用滚动数组来优化掉一维，但因为没有超空间就没优化。

[代码](https://atcoder.jp/contests/abc215/submissions/39559766)

---

## 作者：Cyx20110930 (赞：1)

**本题是状压好题。**

一看 $n=1000$ 不能暴力枚举选或不选，否则是一个 $O(2^n)$，这得 T 到飞起，那么就想到用状压。

状压，本质是 dp，只是将一个繁琐的状态转为一个简单的数或简洁的字符串，是一种优化。

本题状压是考虑让 A~J 的状态转为 01 字符串，代码就不放了。

三维 dp，数组是 dp[看的当前比赛][最后一场比赛][每种比赛是否打过]，$O(1000\times10\times2^{10})=O(10240000)$，但其实跑不满，所以不用担心复杂度。

**核心部分：如果相同就可以放后面，如果没打过也可以放后面或单独作为开头。**

代码就不放了，应该说的很明白了。

---

## 作者：CuFeO4 (赞：0)

发现字符串中只有 $10$ 个字母，考虑状压。

设 $f_{i,S}$ 表示**强制选择**第 $i$ 个字符中，已经选择的子集为 $S$ 的方案数。

考虑转移，加入当前选择的为 $i$，考虑向 $j$ 转移。

1. 如果 $a_i=a_j$，那么有 $f_{j,S} \leftarrow f_{i,S}$。
2. 如果 $a_i\ne a_j$，那么当且仅当 $a_j$ 不在 $S$ 中时，$f_{j,S\cup a_j}\leftarrow f_{i,s}$。

依照上文模拟即可。

[code](https://atcoder.jp/contests/abc215/submissions/61680880)。

---

## 作者：Meickol (赞：0)

挺好的一道状压 DP 题，差点没能单出。

关键是要注意到题目中给定字符串的字符只有 $10$ 种，这也是我们解决本题的前提。

设 $\large f_{i,j,k}$ 表示前 $i$ 个数中已选择的数的集合为 $j$ 且最后一个位置选择的数为 $k$ 的方案总数。

设当前第 $i$ 个数为 $x$，我们转移基于选择第 $i$ 个数与不选第 $i$ 个数进行转移。

**情况一：选择第 $i$ 个数。为保证转移合法，存在两种情况：**

- 在前面的数中没有选择过 $x$ 这个数。
- 在前面的数中选择了 $x$，当且仅当前面选择了 $x$ 的位置只有 $i-1$ 这个位置。

**情况二：不选择第 $i$ 个数。**

- 那么前面的数可以任选。



思路就讲完了，代码实现时注意一些细节即可，就不多赘述了。

**参考代码**

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=1e3+5,MOD=998244353;
int n;
LL f[N][1<<10][10];
void solve(){
	cin>>n;
	string s;
	cin>>s;
	s=" "+s;
	int maxj=(1<<10)-1;
	rep(i,1,n){
		int x=s[i]-'A';
		rep(j,0,maxj){
			rep(k,0,9) f[i][j][k]+=f[i-1][j][k],f[i][j][k]%=MOD;
			if(!((j>>x)&1)) continue;
			f[i][j][x]+=f[i-1][j][x],f[i][j][x]%=MOD;
			rep(k,0,9) if(k!=x) f[i][j][x]+=f[i-1][j-(1<<x)][k],f[i][j][x]%=MOD;
		}
		f[i][1<<x][x]++;
	}
	LL ans=0;
	rep(j,0,maxj){
		rep(k,0,9){
			ans+=f[n][j][k];
			ans%=MOD;
		}
	}
	cout<<ans;
}
```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_abc215_e)；[AtCoder](https://atcoder.jp/contests/abc215/tasks/abc215_e)。

最慢的点才跑 $2$ ms 的题解确定不看一看？

[更 good 的 reading experience](https://www.cnblogs.com/XuYueming/p/18374856)。

## 题意简述

给定长度为 $n$ 的字符串 $s$，其中 $s_i \in \Omega$，求有多少子序列 $T$ 满足任意 $x \in \Omega$，其在 $T$ 出现的位置为连续一段，当然，对 $998244353$ 取模。

$n \leq 10^5$，$|\Omega| \leq 14$，时间 $1$ 秒，空间 $5$ MB。

（嗯……其实原题 $n \leq 10^3$，$|\Omega| \leq 10$，时间 $2$ 秒，空间 $1$ GB。）

## 题目分析

一眼状压 DP。因为我们需要知道之前选过的字符集合，以及当前上一位选出来的字符是什么。所以我们考虑记 $f_{i, \mathcal{S}}$ 表示考虑前 $i$ 位，必选 $i$，选出的字符集合为 $\mathcal{S}$ 的方案数。注意区分集合 $\mathcal{S}$ 和字符串 $s$。有如下两种转移：

1. 当前字符是子序列第一位：
    直接 $f_{i, \lbrace s_i \rbrace} = 1$。
1. 当前字符不是子序列第一位：
    那么肯定是从 $j \in [1, i - 1]$ 拼接来的。枚举 $j$ 处选出的字符集合 $\mathcal{S}$，根据上一次选出的最后一位 $s_j$，结合题目要求有如下转移：

    $$
    f_{i, \mathcal{S} \cup \lbrace s_i \rbrace} \gets f_{i, \mathcal{S} \cup \lbrace s_i \rbrace} + \begin{cases}
    f_{j, \mathcal{S}}  & \text{ if } s_i = s_j \\
    f_{j, \mathcal{S}}  & \text{ if } s_i \neq s_j \land s_i \not \in \mathcal{S}  \\
    0  & \text{ otherwise }
    \end{cases}
    $$

    解释一下吧，第一种情况是直接接在 $j$ 之后，第二种情况是新开一段。

答案就是 $\sum \limits _ {i = 1} ^ n \sum \limits _ {\mathcal{S} \subseteq \Omega} f_{i, \mathcal{S}}$。

这样，时间复杂度是 $\Theta(n ^ 2 2 ^ {|\Omega|})$，~~菜爆了~~，无论时空都不优秀。优化思路是先把 $\Theta(n)$ 地枚举 $j$ 优化掉。自然想到可以滚一滚，删除 $i$ 这一维，但是这样我们不好判断上一次选出来的字符是什么，所以再加上一维 $k$ 表示上一次选出来的是哪一种字符。

类似 01 背包，我们每次需要让 $\mathcal{S}$ 从 $\Omega \rightarrow \varnothing$，即代码实现上的从大到小枚举。类似得到转移方程。对于每一个包含 $s_i$ 的 $\mathcal{S}$，计算 $f_{\mathcal{S}, s_i}$。

1. $f_{\mathcal{S}, s_i} \gets f_{\mathcal{S}, s_i} + f_{\mathcal{S}, s_i}$：
    表示选出 $s_i$，有 $f_{\mathcal{S}, s_i}$ 种方案，又由于 $f$ 被滚了，是类似前缀和的操作，所以累加上去。
1. $f_{\mathcal{S}, s_i} \gets f_{\mathcal{S}, s_i} + f_{\mathcal{S} \setminus \lbrace s_i \rbrace, k}$：
    表示新开一段，其中 $k \in \mathcal{S} \setminus \lbrace s_i \rbrace$。

注意到，我们还有把当前字符选出来成为第一位这一操作，由于滚动数组，我们不能再上述操作前修改，而是再上述操作后使 $f_{\lbrace s_i \rbrace, s_i} \gets f_{\lbrace s_i \rbrace, s_i} + 1$。

统计答案显然是 $\sum \limits _ {\mathcal{S} \subseteq \Omega} \sum \limits _ {i \in \mathcal{S}} f_{\mathcal{S}, i}$。

时间复杂度优化到 $\Theta(n |\Omega| 2^{|\Omega}|)$，还是不够。

发现瓶颈在枚举 $k$ 的过程中。我们发现对于 $k \not \in \mathcal{S} \setminus \lbrace s_i \rbrace$ 的情况，由于 $f_{\mathcal{S} \setminus \lbrace s_i \rbrace, k} = 0$，并不会对答案产生影响。所以等价于求 $\sum \limits _ {k \in \Omega} f_{\mathcal{S} \setminus \lbrace s_i \rbrace, k}$。所以，我们同时维护 $g_{\mathcal{S}}$ 表示 $\sum \limits _ {k \in \Omega} f_{\mathcal{S}, k}$ 就能快速转移了。

答案便是 $\sum \limits _ {\mathcal{S} \subseteq \Omega} g_{\mathcal{S}}$。

时间复杂度 $\Theta(n 2 ^ {|\Omega|})$，就差一点点了，似乎差一个 $\cfrac{1}{2}$ 的常数，上哪找去呢？

发现，枚举对于每一个包含 $s_i$ 的 $\mathcal{S}$ 是 $\Theta(n)$ 的，但是我们完全可以只枚举 $\mathcal{T} \subseteq \Omega \setminus \lbrace s_i \rbrace$，而 $\mathcal{S} = \mathcal{T} \cup \lbrace s_i \rbrace$，这样就有了一个 $\cfrac{1}{2}$ 的常数，能够通过。

当然，聪明的读者肯定会发现，空间也可以有一个 $\cfrac{1}{2}$ 的常数，因为只有对于 $k \in \mathcal{S}$ 的 $f_{\mathcal{S}, k}$ 才是有效的，程序二进制上体现为这一位一定为 $1$，我们可以扣掉 $\mathcal{S}$ 在 $k$ 位的 $1$，然后把之后的比特位向前挪动一格，这样就能节约空间。

## 代码

快到飞起的[提交记录](https://atcoder.jp/contests/abc215/submissions/57148690)。为了观感，以下是没有卡空间的代码。

```cpp
#include <cstdio>
using namespace std;

using mint = int;
using sint = long long;

constexpr const mint mod = 998244353;

constexpr inline mint add(const mint a, const mint b) {
    return a + b >= mod ? a + b - mod : a + b;
}

template <typename... Types>
inline mint& toadd(mint &a, Types... b) {
    return a = add(a, b...);
}

const int N = 1010, M = 10;

int n, val[N];
char str[N];

mint dp[1 << M][M], g[1 << M];

signed main() {
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; ++i) val[i] = str[i] - 'A';
    dp[1 << val[1]][val[1]] = 1;
    g[1 << val[1]] = 1;
    for (int i = 2; i <= n; ++i) {
        int ST = ((1 << M) - 1) ^ 1 << val[i];
        for (int S = ST; ; S = (S - 1) & ST) {
            int st = S | 1 << val[i];
            toadd(g[st], dp[st][val[i]]);
            toadd(g[st], g[st ^ 1 << val[i]]);
            toadd(dp[st][val[i]], dp[st][val[i]]);
            toadd(dp[st][val[i]], g[st ^ 1 << val[i]]);
            if (!S) break;
        }
        toadd(dp[1 << val[i]][val[i]], 1);
        toadd(g[1 << val[i]], 1);
    }
    mint ans = 0;
    for (int st = 0; st < 1 << M; ++st)
        toadd(ans, g[st]);
    printf("%d", ans);
    return 0;
}
```

## 后记

一道大水题，但是完全可以优化，别的题解都太劣了。以及本来想申请撤下一篇题解的，但是发现他已经被禁用专栏了，乐。

希望我的题解能给大家带来启示和帮助。

---

