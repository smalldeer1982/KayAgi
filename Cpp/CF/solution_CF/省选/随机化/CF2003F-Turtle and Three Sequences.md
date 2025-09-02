# Turtle and Three Sequences

## 题目描述

小猪给了小乌龟 3 个长度为 $n \ (1 \le n\le3000)$ 的序列 $a,b,c$，乌龟要在 $1\sim n$ 中选出 $m \ (1 \le m ≤ 5)$ 个下标 $p_1 \sim p_m$，满足如下条件：

* $p$ 是 $1\sim n$ 的子序列。

* $\forall 1\le i\le n, a\large_{p_i} \small \normalsize\le a\large_{p_i + 1} $，即得到的 $a$ 序列严格不降。
* $\forall 1\le i, j\le n \ (i\ne j), b\large_{p_i}\normalsize \ne b\large_{p_j}$ ，即得到的 $b$ 序列两两不同。

你需要帮助小乌龟求出可能的 $\sum\limits^m_{i=1} c\large_{p_i}$ 的最大值，或者告诉他满足以上条件的子序列 $p$ 不存在 。

其中子序列的定义是，从原序列中删去若干 $(0\sim n)$ 个元素，则新的序列是原序列的子序列。

## 说明/提示

在第一个样例中，我们可以选择 $p=[1,2]$，则答案为 $1+4=5$。我们不能选择 $p=[2,4]$ 因为 $a_2>a_4$ ，不满足第一个条件。我们也不能选择 $p=[2,3]$ 因为 $b_2=b_3$ ，不满足第二个条件。我们可以选择 $p=[1,4]$，但答案为 $4$ ，不是最大的。

在第二个样例中 我们可以选择 $p=[4,6,7]$。

在第三个样例中，我们选不到满足条件的 $p$ 。

## 样例 #1

### 输入

```
4 2
2 3 4 2
1 3 3 2
1 4 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
7 3
1 4 5 2 3 6 7
1 2 2 1 1 3 2
1 5 6 7 3 2 4```

### 输出

```
13```

## 样例 #3

### 输入

```
5 3
1 2 3 4 5
1 1 2 1 2
5 4 3 2 1```

### 输出

```
-1```

# 题解

## 作者：Super_Cube (赞：2)

# Solution

奇妙算法之 color-coding。

如果 $b_i\in[1,m]$，我想你能很轻易地做出此题。设 $dp_{i,j,k}$ 表示前 $i$ 个数里已选过的 $b$ 集合为 $j$，$a$ 最大值为 $k$，转移为 $dp_{i,j,k}=\max\left(dp_{i-1,j,k},c_i+\displaystyle\max_{b_i\not\in x,x\cup \{b_i\}=j}\max_{y\le j}dp_{i-1,x,y}\right)$，可利用树状数组优化至 $O(n2^m\log n)$。

现在问题是 $b_i$ 的范围过大，无法状压。这时候 color-coding 就来了：把 $b_i$ 随机映射至 $[1,m]$ 中，再跑上面那个算法。现在得到的答案一定不优于原问题，但是多跑几遍得到最优解的概率就会上升，于是打个卡时，这题就做完了。

---

## 作者：AVENGER_M (赞：2)

## 前言

非常套路的随机化算法题，使我 $43$ 发抽中 $3.302\times 10^{-7}$ 的错误率。

## 正解

不说套路怎么想出来的了。套路是：给每个值随机染上一个 $[0,m)$ 的颜色 $v$，那么如果这个长度为 $m$ 的序列的 $b$ 值并非两两不同，显然它们的颜色无法取遍 $[0,m)$。

然后设 $f_{i,j,S}$ 为考虑前 $i$ 个值（这个可以滚掉），当前序列颜色状态为 $S$，序列最后一项是 $j$（不存在就是 $1$）的权值最大值。那么：

$$\forall S,v_{b_i}\not\in S,\max_{t=1}^{a_i} f_{i-1,t,S}\rightarrow f_{i,a_i,S+2^{v_{b_i}}}$$

树状数组维护即可，实现极为简易。

如果最终答案是 $-1$，那么再怎么随机化也不可能随机出有解的情况，正确率为 $1$。否则，假设我们随机化尝试了 $T$ 次，那么每次最终答案的序列被染上不同的颜色概率就是 $\frac{m!}{m^m}\ge \frac{120}{625}$，这种情况下这个序列会被计入答案。

那么总时间复杂度就是 $O(Tn2^m\log n)$，错误率是 $(1-\frac{m!}{m^m})^T\le(\frac{505}{625})^T$。

相信树状数组的常数（其实还有一半常数，因为每个位置只用转移 $2^{m-1}$ 个状态），取 $T=140$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int T=140,n,m,a[3005],b[3005],c[3005],ky[3005],tr[3005][32],infn=30000005,ans=-30000005;
mt19937 mt(0x4247AABC),mtt(random_device{}());

void addbit(int x,int v,int lc){
	for(;x<=n;x+=(x&-x))if(tr[x][lc]<v)tr[x][lc]=v;
}

int querybit(int x,int lc){
	int ca=-infn;for(;x;x&=(x-1))if(ca<tr[x][lc])ca=tr[x][lc];
	return ca;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	while(T--){
		for(int i=1;i<=n;i++)ky[i]=(mt()^mtt())%m;
		for(int i=1;i<=n;i++)for(int z=0;z<(1<<m);z++)tr[i][z]=-infn;
		addbit(1,0,0);
		for(int i=1;i<=n;i++){
			int oo=ky[b[i]];for(int z=0;z<(1<<m);z++)if(z&(1<<oo))addbit(a[i],querybit(a[i],z^(1<<oo))+c[i],z);
		}
		ans=max(ans,querybit(n,(1<<m)-1));
	}
	cout<<(ans<0?-1:ans);
	return 0;
}
```

## 花絮

照理来说取 $T=70$ 就能稳过这道题了，但是由于 [mt19937](https://codeforces.com/contest/2003/submission/322185342)······

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2003F)

**题目大意**

> 给定 $n$ 元素，每个元素有高度、颜色、权值，选出 $m$ 个元素满足高度递增，颜色不同，且权值和最大。
>
> 数据范围 $n\le 3000,m\le 5$。

**思路分析**

这种选出不同颜色的元素的题可以考虑 random-coloring，即给每种颜色随机映射到 $[1,m]$ 中，然后计算此问题的答案。

此时可以状压 dp，$f_{i,s}$ 表示选择了元素 $i$，出现过的颜色集合为 $s$ 时的最大权值，树状数组优化转移。

对于最优解，可能被映射到 $m^m$ 中颜色序列中，其中两两颜色不同的序列有 $m!$ 个，因此期望随机 $\dfrac{m^m}{m!}$ 次即可。

时间复杂度 $\mathcal O\left(2^mn\log n\times\dfrac{m^m}{m!}\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3005,inf=1e9,T=400;
mt19937 rnd(time(0));
int n,m,a[MAXN],b[MAXN],c[MAXN],o[MAXN];
struct FenwickTree {
	int tr[MAXN],s;
	void init() { memset(tr,-0x3f,sizeof(tr)); }
	void upd(int x,int v) { for(;x<=n;x+=x&-x) tr[x]=max(tr[x],v); }
	int qry(int x) { for(s=-inf;x;x&=x-1) s=max(s,tr[x]); return s; }
}	F[32];
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]);
	int ans=-1;
	for(int _=0;_<T;++_) {
		for(int s=0;s<(1<<m);++s) F[s].init();
		F[0].upd(1,0);
		for(int i=1;i<=n;++i) o[i]=rnd()%m;
		for(int i=1;i<=n;++i) {
			for(int s=0;s<(1<<m);++s) if(!(s>>o[b[i]]&1)){
				int z=F[s].qry(a[i])+c[i];
				F[s|1<<o[b[i]]].upd(a[i],z);
			}
		}
		ans=max(ans,F[(1<<m)-1].qry(n));
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：rizynvu (赞：1)

[cnblogs](https://www.cnblogs.com/fiosiate/p/18831601)。

首先分析一下这题的限制 $p_i < p_{i + 1}, a_{p_i} < a_{p_{i + 1}}$ 和 $b_{p_i} \not= b_{p_j}$。  
相比之下，前两个限制更简单，因为其只限制于相邻的两数之间，而后一个限制要对所有 $i, j$ 满足，只知道 $b_{p_{i - 1}}$ 是不够的。

对于这种 $\not =$ 的限制，一个想法是[暴力钦定一些相同的情况（贝尔数）容斥](https://pjudge.ac/contest/1937/problem/21896)，但因为这个题是最值相关，容斥在此也没有办法。  
考虑这个限制为什么会很难处理，因为必须要知道前缀选的 $b$ 的信息，但是这个状态数是 $\binom{n}{m} + \binom{n}{m - 1} + \cdots + \binom{n}{0}$ 的，数量太过庞大所以不能直接用。

所以发现其实问题都出在这个 $\binom{n}{m}$ 中的 $n$，也就是 $b$ 的种类数，本质上就是因为种类过多导致所需信息太多。  
那一个想法就是考虑**减少种类数使得所需的信息在可控的范围内**。

于是可以考虑把 $b$ 的值域限定在 $[0, B)$ 这 $B$ 个数中。  
因为 $b_i = b_j$ 肯定是不能被选在一起的，所以如果 $b$ 的值相同被限定后的值也必须相同，所以这个限定就可以当作是从 $b$ 的值域到 $[0, B)$ 的映射。  

但是又有问题，如何映射，又如何保证最优解会出现？  
此时的一个做法是**随机映射**，考虑最优解的 $m$ 个值，那么其 $b$ 的映射的方案数为 $B^m$；若该最优解可以表示出，那么这 $m$ 个值对应的 $b$ 的值就应该不同，对应方案数为 $\binom{B}{m}\times m!$。  
于是可以得到一个单次随机出最优解的概率：$\frac{\binom{B}{m}\times m!}{B^m}$。单次正确的概率可能不大，于是考虑多随几次，随机个 $T$ 次，正确率就变为 $1 - \bigg(1 - \frac{\binom{B}{m}\times m!}{B^m}\bigg)^T$（其实因为要求每个测试点都正确，所以通过的概率应该还需要有一个测试点的次方）。

接下来考虑把 $b$ 的值域映射到了 $[0, B)$ 后如何处理答案。  
此时再考虑 $p_i < p_{i + 1}, a_{p_i} < a_{p_{i + 1}}$ 的限制，考虑 DP，设计 $f_{i, s}$ 表示考虑了 $[1, i]$ 并且选的最后一个为 $i$，$b$ 中选的集合为 $s$ 的最大权值。  
转移就直接考虑这些限制即可：$f_{i, s}\leftarrow f_{j, s - \{b_i\}} + c_i(j < i, a_j\le a_i, b_i\in s)$。  
平衡这个查询和加入的复杂度，用一个树状数组优化即可。

最后时间复杂度 $\mathcal{O}(T2^Bn\log n)$，正确率 $1 - \bigg(1 - \frac{\binom{B}{m}\times m!}{B^m}\bigg)^T$，可以取 $B = 7, T = 150$。

```cpp
#include<bits/stdc++.h>
constexpr int maxn = 3e3 + 2, B = 7;
using arr = std::array<int, 1 << B>;
inline arr max(const arr &a, const arr &b) {
    arr c;
    for (int i = 0; i < (1 << B); i++) c[i] = std::max(a[i], b[i]);
    return c; 
}
int n, m;
arr tr[maxn];
inline void clear() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << B); j++) {
            tr[i][j] = j == 0 ? 0 : (int)-1e9;
        }
    }
}
inline void add(int x, const arr &y) {
    for (; x <= n; x += x & -x) tr[x] = max(tr[x], y);
}
inline arr query(int x) {
    arr y = tr[x];
    for (; x >= 1; x -= x & -x) y = max(y, tr[x]);
    return y;
}
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int a[maxn], b_[maxn], c[maxn];
int pb[maxn], b[maxn];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b_[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    int ans = -1;
    for (int t = 0; t < 150; t++) {
        for (int i = 1; i <= n; i++) pb[i] = rnd() % B;
        for (int i = 1; i <= n; i++) b[i] = pb[b_[i]];
        clear();
        for (int i = 1; i <= n; i++) {
            arr f = query(a[i]);
            for (int s = 0; s < (1 << B); s++) {
                if (~ s >> b[i] & 1) {
                    f[s | (1 << b[i])] = std::max(f[s | (1 << b[i])], f[s] + c[i]);
                }
            }
            add(a[i], f);
        }
        const arr f = query(n);
        for (int s = 0; s < (1 << B); s++) {
            if (__builtin_popcount(s) == m) {
                ans = std::max(ans, f[s]);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：TTpandaS (赞：1)

正好半年前了解过 Color-Coding 这个算法，但是当时报了这场 CF 没打 :(。不过说实话评 *2800 可能是因为 E1 E2 挡住了很多人导致没多少人做？

因为要求所选择 $b_i$ 互不相同，所以最后选取的 $b_i$ 一共会有 $m$ 种。首先考虑 $b_i$ 值域只有 $m$，那么就可以状压当前已选择的种类。设 $dp_{i,j}$ 表示选择了 $i$，选择之后已选择的 $b_i$ 为 $j$ 的最大值。那么 $dp_{i,j}= \max_{a_k \leq a_i \wedge k \in j} dp_{k,j-2^{b_k}}+c_i$。用树状数组维护每种已选种类以 $a_i$ 为下标的前缀最大值即可，时间复杂度 $O(n 2^m \log n)$。

考虑 $b_i$ 更大的情况。将 $n$ 看作颜色种类，将颜色随机映射到 $[0,m)$ 中。设最后答案颜色集合唯一，那么能得到正确答案的随机映射概率就为 $\dfrac{m!}{m^m}$，为 $3.84 \% $，所以跑几百次就能很大概率得到正确答案了。

[color-coding 论文](https://dl.acm.org/doi/pdf/10.1145/210332.210337)。

---

## 作者：ddxrS_loves_zxr (赞：1)

实际上，看到要选出 $m$ 种不同的颜色，且 $m\le 5$ 就可以想到将每种颜色随机映射到 $1$ 到 $m$ 中，这样子得出来的答案不会更优，而当答案选择的 $m$ 种颜色恰好被映射到了不同的颜色上时会取到最优解，正确的概率为 $\frac{m!}{m^m}$，当 $m=5$ 时是 $0.0384$。

我们可以做 $k$ 次随机化，这样子做 $k$ 次后还无法得出正确答案的概率为 $(1-\frac{m!}{m^m})^k$，当 $k$ 取 $200$ 时只有大约 $0.000397$ 的错误概率，可以接受。

现在 $b$ 就只有 $m$ 种取值，可以直接状压。

具体的，我们设 $dp_{i,s}$ 表示选了第 $i$ 个数，选了的颜色集合为 $s$ 的最优方案。

转移有 $dp_{i,s}=\max_{j=1}^{j<i}([a_j\le a_i]dp_{j,t})+c_i$。

其中集合 $t$ 满足 $t\in s\wedge s\setminus t=\{b_i\}$。

直接暴力是 $O(n^22^m)$ 的，可以用树状数组维护前缀最大值来优化。

时间复杂度 $O(kn2^m\log n)$。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int K = 200, N = 3005;
mt19937 rnd(114514);
int n, m;
int a[N], b[N], c[N], col[N];
int bit[N][1 << 5], dp[N][1 << 5], ans = -1;
void add(int x, int s, int y) {for(; x <= n; x += x & -x) bit[x][s] = max(bit[x][s], y);}
int ask(int x, int s) {int ans = 0xf3f3f3f3; for(; x; x -= x & -x) ans = max(bit[x][s], ans); return ans;}
void solve() {
	memset(dp, 0xf3, sizeof dp), memset(bit, 0xf3, sizeof bit);
	dp[0][0] = 0, add(1, 0, 0);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (1 << m); j++) {
			if(j & (1 << col[b[i]])) continue;
			int k = j | (1 << col[b[i]]);
			dp[i][k] = ask(a[i], j) + c[i];
			add(a[i], k, dp[i][k]);
		}
		ans = max(ans, dp[i][(1 << m) - 1]);
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= K; i++) {
		for(int j = 1; j <= n; j++) col[j] = rnd() % m;
		solve();
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Alear (赞：0)

传送门：[洛谷](https://www.luogu.com.cn/problem/CF2003F)，[CF](https://codeforces.com/contest/2003/problem/F)。

和 color-coding 稍微有点不一样，但是同样是利用随机化的算法，权当分享一下思路。

将 $b_i$ 理解为颜色，则每种颜色只能选择一个。如果我们给颜色规定一个权值 $col$，要求在较小的颜色一定要在较大颜色左边，则我们可以得到一个转移方程:

$$ 
 dp_{i,k}=\min\limits_{\substack{j<i\\a_j\leq a_i\\col_{b_j} < col_{b_i}}} dp_{j,k-1} 

$$

其中 $dp_{i,k}$ 表示以 $i$ 结尾，选择了 $k$ 个元素的最大答案。使用二维树状数组可以做到 $O(nm\log^2 n)$。

对于随机规定的权值，最坏情况下也有 $\frac{1}{m!}$ 的概率与答案的顺序相同，求出最优解。当 $m=5$ 是，这个概率大小约为 $0.83 \%$，单次不如 color-coding，但是我们可以多跑几遍，取 $T=500$，成功率约为 $98.48\%$。

不算特别可以接受的概率，毕竟 CF 的测试点有上百个，不过这又不是 OI 赛制，脸黑可以多交几次，或者打一个卡时。笔者实测是四次过三次。

时间复杂度 $O(Tnm\log^n)$

[code](https://codeforces.com/contest/2003/submission/286282120)

---

## 作者：Purslane (赞：0)

# Solution

并不困难，但是要有这个意识。

容易设计出 $O(n b^m \log n)$ 的简单 $\rm DP$，设 $dp_{i,S}$ 为选了第 $i$ 个数和它之前的某些数，$b$ 出现的集合是 $S$ 的最大价值。

$b$ 是 $O(n)$ 的，不好。

但是随机映射一下，让 $b=8$，这时候单次的正确率达到了 $\dfrac{8 \times 7 \times 6 \times 5 \times 4}{8^5}$，约等于 $20\%$。

进行 $40$ 次即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10;
int n,m,ans=-1,a[MAXN],b[MAXN],c[MAXN],dp[MAXN][257],pre[MAXN][257],col[MAXN]; 
void update(int pos,int st,int val) {
	pos++;
	while(pos<=n+1) pre[pos][st]=max(pre[pos][st],val),pos+=pos&-pos;
	return ;
}
int query(int pos,int st) {
	pos++;
	int ans=-0x3f3f3f3f;
	while(pos) ans=max(ans,pre[pos][st]),pos-=pos&-pos;
	return ans;	
}
mt19937 myrand(time(NULL));
void solve(void) {
	memset(dp,-0x3f,sizeof(dp)),memset(pre,-0x3f,sizeof(pre));
	dp[0][0]=0,update(0,0,0);
	ffor(i,1,n) col[i]=myrand()%8;
	ffor(i,1,n) {
		ffor(s,0,255) if(s&(1<<col[b[i]])) {
			dp[i][s]=query(a[i],s-(1<<col[b[i]]))+c[i];
			update(a[i],s,dp[i][s]);
		}
	}
	ffor(i,1,n) ffor(s,0,255) if(__builtin_popcount(s)==m) ans=max(ans,dp[i][s]);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) cin>>c[i];
	ffor(i,1,40) solve();
	cout<<ans;
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

看到 $m \leq 5$ 和 $b_i$ 要求两两不同，我想到了假期计划那题。

不过枚举 $p_2,p_4$ 的话要解决一个静态二维前若干大，复杂度肯定炸了。

但是你考虑那题有一个随机化做法。

我们把 $b_i$ 随机映射到 $[0,m)$ 上，再去求解原问题就有 $\frac{m!}{m^m}$ 的机率得到正确答案。当 $b_i < m$ 时求解原问题可以直接把最长上升子序列的做法外面套一个装压，是 $O(2^m \times n \log n)$ 的。

考虑像这样随机跑 $1000$ 次，错误率便降到了可接受的量级。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e3+114;
const int maxv = (1<<5);
int tr[maxn][maxv];
int a[maxn],b[maxn],c[maxn],key[maxn];
int n,m;
mt19937 rd(time(0));
void ins(int u,int c,int v){
    while(u<=n) tr[u][v]=max(tr[u][v],c),u+=(u&(-u));
}
int ask(int u,int v){
    int res=-INT_MAX;
    while(u>0) res=max(res,tr[u][v]),u-=(u&(-u));
    return res;
}
int ans=-1;
void work(){
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxv;j++) tr[i][j]=-INT_MAX;
    ins(1,0,0);
    for(int i=1;i<=n;i++) key[i]=rd()%m;
    for(int i=1;i<=n;i++){
        for(int lst=0;lst<(1<<m);lst++){
            if(!((1<<key[b[i]])&lst)){
                int now=(1<<key[b[i]])+lst;
                int dp=ask(a[i],lst)+c[i];
                if(dp<0) continue;
                ins(a[i],dp,now);
            }
        }
    }
    ans=max(ans,ask(n,(1<<m)-1));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=1000;i++) work();
    cout<<ans<<'\n';
    return 0;
}

```

---

